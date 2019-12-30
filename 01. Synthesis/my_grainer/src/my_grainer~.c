/*my_grainer by Oscar Pablo Di Liscia*/
/*glissando of the grains, blocking console messages and grain pause/restart were added by
Damián Anache, 06/01/2016 */
/*odiliscia@unq.edu.ar pdiliscia@iuna.edu.ar*/
/*granular synthesis external for pd*/
/*Last version 01-08-2016*/
#include "m_pd.h"
#include <math.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
todo:
	shuffle mode random selection
	include seeding from system time
	redo print function
*/
/******************************************************************/
/******************************************************************/
static t_class *my_grainer_tilde_class;
/******************************************************************/
/*CONSTANTS*/
/******************************************************************/
#define PI    3.14159265358979323846264338327
#define PI2   6.28318530717958647692528676654
#define DEG90 1.570796326794896619231321691635
#define DEG45 (DEG90 / 2.)
#define DEG135 DEG90 + DEG45
/*first and second order scalers for Ambisonics encoding, FuMa Set*/		
#define ASCAL  0.707106781 /* 1/sqrt(2) */
#define ASCAL2 0.726184377 /* sqrt(135/256)*/
#define ASCAL3 2.598076211 /* sqrt(27/4)*/
#define MONO 1
#define IPAN 2
#define AMBI 4
#define AMBI2 9
#define AMBI3 16
#define MAX_OUTPUTS 17
/*distance*/
#define MIN_DIST 1.
#define MAX_DIST 50.
#define MAXDELAY 0.147058824  /* 50mts/340 mts/seg */ 
#define SOUND_SPEED 340.
#define MIN_SOUND_SPEED 300.
#define DIST_EXP 1.
	
/*general misc*/
#define TRUE  1
#define FALSE 0
#define MIN_GAP  (t_float)0.001
#define MIN_DUR  (t_float)0.001
#define MAX_GRAINS 100
#define MAX_TABLES 24
#define GTAB 1
#define ATAB 2
#define	REP 0
#define SHU 1
#define	NOLOOP	0
#define	LOOPF	1
#define	LOOPFB	2
#define	MAX_AUDIO_TABLES	24

/********************************************************/
/*MACROS*/
/********************************************************/
/*conversions*/
/*dB value from linear value*/
#define LIN2dB(x) (double)(20. * log10(x))
/*compute oscilator increment from frequency*/ 
#define ITOF(frec, L, sr)  frec * ((t_float)L/(t_float)sr)
/*compute an increment of s semitones*/
#define S2INCR(s) (pow(2.,(double)s/12.))
/*convert angles*/
#define DEG2RAD(deg) (deg/360.)* PI2
#define RAD2DEG(rad) (rad/PI2) * 360.
/*get a random value between 0 and "range"*/
#define RAND_FLOAT(range)  range*((t_float)rand()/ (t_float)RAND_MAX)
/*get a random value between -range and range*/
#define BIRAND_FLOAT(range)  (range*2.*((t_float)rand()/ (t_float)RAND_MAX)) - range
/*get an int random value between 0 and "range-1"*/
#define RAND_INT(range) rand()%range 
/********************************************************/
/*DATA STRUCTURES*/
/********************************************************/
/******************************************************************/
typedef struct {
	double  	index;
	double		incr;
	int		fros;
	int 		ends;
	int		durs;
	int		LT;		/*loop type */
	int		Ldir; 		/*loop direction */
	t_float 		gliss;		/*incr mutiplier for glissandi */
	t_float		glissrnd;   	/*random deviation for glissandi*/
	int 		nt;		/*this is the table number in the table array*/
}OSCIL;

typedef struct { 
  	int    size;       	/*grain size in samples*/
  	t_float  incr;       	/*increment for the grain table*/
  	t_float  amp;		/*grain amplitude*/
  	t_float  incra;      	/*increment for the amp table so it fits the grain duration*/
  	t_float  azi;	     	/*azimuth angle in radians*/
  	t_float  ele;	     	/*elevation angle in radians*/
	t_float  dist;		/*distance in meters*/
  	t_float  gch[MAX_OUTPUTS];     /*gain values for each channel*/
  	int    s_count;    	/*internal sample counter*/
  	OSCIL  *gosc;      	/*oscilator for the grain*/
  	OSCIL  *aosc;      	/*oscilator for the amplitude func*/
	int	delflag;
  	t_float  *delbuf;		/*delay buffer*/
  	int    delpo;		/*delay reading pointer*/
  	int    delsi;		/*delay size in samples*/
	t_float  dry;		/*output sample delayed*/
	t_float  send;		/*output sample non-delayed*/
	t_float  distaten;	/*auxiliar variable for distance attenuation*/

} GRAIN;
/******************************************************************/
typedef struct {
	t_symbol *name;	//array name
	t_word	*table;	//table vector
	int	size;	//table size
}TABLE;
/******************************************************************/					
typedef struct _my_grainer_tilde {
	t_object x_obj;
	t_sample f;
	GRAIN	**g;			/*a pointer to an array of pointers of GRAIN structures*/
  	int	ng;			/*number of grain pointers currently allocated*/
	
	TABLE gtab[MAX_AUDIO_TABLES];	/*audio table structure array*/
	TABLE atab[MAX_AUDIO_TABLES];	/*envelope table structure array*/
	int 	ngt;			/*number of available audio tables*/
	int 	net;			/*number of available envelope tables*/
	int 	ngtact;			/*index of active grain table*/
	int 	netact;			/*index of active envelope table*/

	int	nch;			/*number of audio output channels*/
	int	active;			/*active flag*/
	int	pause;			/*pause flag*/
	t_float	sr;			/*sampling rate*/	
	int 	post_ctrl;		/*enables and disables console posts*/

	int	dosend;			/*enables and disables reverberation send*/

	t_float	sound_speed;		/*actual sound speed*/
	t_float	max_dist;		/*maximal distance*/
	t_float	dist_exp;		/*distance exponent*/
	int	delflag;
	///////////////////////////////////////////////////////////
	/*GRAINER PARAMETERS*/
	t_float agr;			/*grain amplitude*/
  	t_float agrnd;			/*grain amplitude random deviation in percent of the grain amplitude*/
	t_float fgr;            		/*grain frequency scaler*/
	t_float fgrnd;          		/*grain increment random deviation percent*/
	t_float sgr;            		/*grain size in secs.*/
	t_float sgrnd;          		/*grain size random deviation in percent of grain size (0=invariant, 1=100%)*/
  
	t_float stgr;           		/*where to start the grain in the table, in seconds*/  
	t_float stgrnd;         		/*starting point random deviation in percent of the table (0=invariant, 1=100%)*/
	t_float engr;			/*where to end the grain in the audio table, in seconds table 0=read the table modulo size*/
	t_float engrnd;			/*ending point random deviation in percent of the table (0=invariant, 1=100%)*/
	int   loop_type;		/*0=noloop 1=forward, 2=forward-backward, use if needed
					Note that when loop_type=0, engr and engrnd are not taken in account*/
	int   loop_direction;		/*internal temporary value for forward-backward loop type*/

	t_float gli;			/*incr mutiplier for glissandi */
	t_float glir;			/*incr mutiplier for glissandi random deviation percent*/ 		 		

	t_float gagr;           		/*gap between grains in secs.*/
	t_float gagrnd;         		/*gap random deviation in percent of the gap 0=invariant, 1=gap, 2=twice, etc.*/
	int   gap_samps;      		/*actual gap in samples*/
	t_float azgr;			/*azimuth center, in radians 0 (0 Deg.) to PI (90 Deg.) for stereo*/
	t_float azgrnd; 			/*azimuth center random deviation in degrees*/
	t_float elgr;			/*elevation center, in radians 0 (0 Deg.) to PI (90 Deg.) for stereo*/
	t_float elgrnd; 			/*elevation center random deviation in degrees*/
	t_float digr;			/*grain distance*/
	t_float digrnd;			/*grain distance random deviation*/
	t_float *devt; 			/*frequency deviation table for random selection*/
	t_float *gapt;			/*gap table for random selection*/
	t_float *durt;			/*dur table for random selection*/
	t_float *ptrt;			/*ptr audio table for random selection*/
	t_float *pdt;			/*size of the starting points and durs table*/
	int   gtat[MAX_TABLES];		/*number of audio table for random selection*/
	int   atat[MAX_TABLES];		/*number of envelope table for random selection*/
	int   devtsize;			/*size of the freq. deviation table (0 will cause to use random dev according to fgr*/
	int   gaptsize;			/*size of the gap   table (0 will cause to use random gap according to gagr)*/
	int   durtsize;			/*size of the dur table (0 will cause to use random size according to sgr)*/
	int   ptrtsize;			/*size of the starting points table (0 will cause to use random start according to stgr)*/
	int   pdtsize;			/*size of the starting points and durs table*/
	int   gtatsize;			/*size of the audio table numbers (0 will cause to use the last table in use)*/
	int   atatsize;			/*size of the envelope table numbers (0 will cause to use the last table in use)*/
	int   gap_count;      		/*gap samples counter*/
  	t_float osig[MAX_OUTPUTS];   	/*array to store the output, may be stereo (intensity panning) or (Ambisonic B Format) 4, 9 16 channels*/
					/*WARNING: osig[nch] is used to store the reverb send*/
} t_my_grainer_tilde;
/******************************************************************/	
/************** FUNCTION PROTOTYPES *******************************/
/******************************************************************/
/*OSCIL*/
OSCIL   *set_oscil(int start, int end, int LT, int Ldir, t_float gliss, t_float glissrnd, double incr, t_my_grainer_tilde *x, int which);
t_float   goscil(OSCIL *oscil, t_float amp, t_my_grainer_tilde *x );
t_float   aoscil(OSCIL *oscil, t_float amp, t_my_grainer_tilde *x );
/*GRAIN*/
void  my_grainer_tilde_tables(t_my_grainer_tilde *x, t_symbol *name, int which, char *type) ;
t_float set_birand_val(t_float base, t_float rdev);
void  compute_gap(t_my_grainer_tilde *x);
void  set_pan_gains(t_my_grainer_tilde *x, GRAIN *g);
GRAIN *grain_setup(t_my_grainer_tilde *x);
void  grain_sinth(GRAIN *g, t_my_grainer_tilde *x);
void  grainer_setup(t_my_grainer_tilde *x);
void  grainer(GRAIN ***g, t_my_grainer_tilde *x);
void  display_grainer_params(t_my_grainer_tilde *x);
void  charray_print(int size, t_float *data, char *str);
void  gap_restart(t_my_grainer_tilde *x);
t_float *set_dval_sel(t_my_grainer_tilde *x, t_symbol *string, t_int argc, t_atom *argv, int *lsize, char *what);

/******************************************************************/
void my_grainer_tilde_destroy(t_my_grainer_tilde *x);
/******************************************************************/
/******************************************************************/
/******************************************************************/
/******************************************************************/
t_float *set_dval_sel(t_my_grainer_tilde *x, t_symbol *string, t_int argc, t_atom *argv, int *lsize, char *what)
{
int i;
t_float *pointer=NULL;

/*
if(argc < 2 && argc !=0) {
	if(x->post_ctrl)
		post(" my_grainer~: %s list must have at least two vales, no action taken", what);
	return(NULL);
}
*/


*lsize=argc;

	if(!*lsize) {
		if(x->post_ctrl)
			post(" my_grainer~: %s list unset", what);
		return(NULL);
	}
	else {
		pointer=(t_float*)malloc(*lsize * sizeof(t_float));
		if(!pointer) {
			if(x->post_ctrl)
				post(" my_grainer~: could not allocate %s list", what);
			*lsize=0;			
			return(NULL);
		}	
		for(i=0; i < *lsize; ++i) {
			pointer[i]=(t_float)fabs(atom_getfloat(&argv[i]));	
		}
	}

if(x->post_ctrl)
	post(" my_grainer~: %s list set, size=%d", what, *lsize);
return(pointer);
}
/******************************************************************/
void my_grainer_tilde_grainer_setup(t_my_grainer_tilde *x)
{
  int i;

  if(x->g) { /*must keep previous setup parameters*/
	if(x->ngt && x->net) {
		x->active=1;
		x->pause=0;
		return;
	}
  }
  else {
  	if(x->ngt && x->net) {
		/*allocate first grain*/
		x->g=(GRAIN**)malloc(sizeof(GRAIN*)); 
		x->ng=1; 
		x->g[0]=(GRAIN*)grain_setup(x);
		x->active=1;
		x->pause=0;
		post(" my_grainer~: initialized");
	}  	
  }
  return;
}
/******************************************************************/
void my_grainer_tilde_usegtn(t_my_grainer_tilde *x, t_float f)
{
	int index=(int)f;

	if(!x->gtab[index].size) {
		post(" my_grainer~: non allocated grain table requested, use the 'gtab' method to allocate it first");
		return;
	}
	x->ngtact=index;
	/*if random selection of tables by a list was active, set it inactive forcing the list size to 0*/	
	if(x->gtatsize) {	
		x->gtatsize=0;
		post(" my_grainer~: random selection of grain tables unset ");
	}	
	return;
}
/******************************************************************/
void my_grainer_tilde_useatn(t_my_grainer_tilde *x, t_float f)
{
	int index=(int)f;

	if(!x->atab[index].size) {
		post(" my_grainer~: non allocated envelope table requested, use the 'atab' method to allocate it first");
		return;
	}
	x->netact=index;	
	return;
}
/******************************************************************/
void my_grainer_tilde_any(t_my_grainer_tilde *x, t_symbol *string, t_int argc, t_atom *argv)
{
  int i, aux=0;
  t_float f;
  t_symbol *temp, *temp2;
  
  /*stop*/
  if(strcmp(string->s_name, "stop") == 0) {
    x->active=0;
    post(" my_grainer~: stopped");
    return;
  }
  /*start*/
  if(strcmp(string->s_name, "start") == 0) {
    if(x->g && x->ngt && x->net) {
      x->active=1;					
      post(" my_grainer~: active");
    }
    return;
  }
	
  /*audio table*/
  if(strcmp(string->s_name, "gtab") == 0) {
	temp2=atom_getsymbol(&argv[0]);
	my_grainer_tilde_tables(x, temp2, GTAB, "audio");
	return;
  }

  /*envelope table*/
  if(strcmp(string->s_name, "atab") == 0) {
	temp2=atom_getsymbol(&argv[0]);
	my_grainer_tilde_tables(x, temp2, ATAB, "envelope");
	return;
  }

  /*activate / deactivate reverberation send*/
  /*
  if(strcmp(string->s_name, "revsend") == 0) {
    	f=atom_getfloat(&argv[0]);
	i=(int)f;
	if(i != 1. && i != 0.) {
		post("my_grainer~: unknown revsend value %i (only 0 or 1 are available)", i);
		return;
	}
	x->dosend=i;	
	if(i)	post("my_grainer~: reverberation send is enable");
	else  post("my_grainer~: reverberation send is disable");
	return;
  }
  */

  /*pause*/
  if(strcmp(string->s_name, "pause") == 0) {
    	f=atom_getfloat(&argv[0]);
	i=(int)f;
	if(i != 1. && i != 0.) {
		post(" my_grainer~: unknown pause value %i (only 0 or 1 are available)", i);
		return;
	}
	x->pause=i;	
	if (x->post_ctrl){
		if(i) post(" my_grainer~: paused");
		else post(" my_grainer~: resumed");
	}	
	return;
  }

  /*seed*/
  if(strcmp(string->s_name, "seed") == 0) {
    f= atom_getfloat(&argv[0]);  
    if (x->post_ctrl) post(" my_grainer~: seeding with %f", f);
    srand(f);
    return;
  }
  
  /*print*/
  if(strcmp(string->s_name, "print") == 0) {
    display_grainer_params(x);
    return;
  }
	
  /*grain gap*/
  if(strcmp(string->s_name, "ga") == 0) {
		f= fabs(atom_getfloat(&argv[0]));  
    x->gagr=(f < MIN_GAP? MIN_GAP : f);
    return;
  }
  /*grain gap random deviation*/
  if(strcmp(string->s_name, "gar") == 0) {
  	x->gagrnd= fabs(atom_getfloat(&argv[0]));
    return;
  }
  /*grain size*/
  if(strcmp(string->s_name, "gs") == 0) {
  	f= fabs(atom_getfloat(&argv[0]));
		x->sgr=(f < MIN_DUR? MIN_DUR : f);
    return;
  }
  /*grain size random deviation*/
  if(strcmp(string->s_name, "gsr") == 0) {
  	x->sgrnd= fabs(atom_getfloat(&argv[0]));
    return;
  }
  /*grain frequency scaler (increment)*/
  if(strcmp(string->s_name, "gf") == 0) {
  	x->fgr= atom_getfloat(&argv[0]);
    return;
  }
  /*grain frequency scaler (increment)random deviation*/
  if(strcmp(string->s_name, "gfr") == 0) {
  	x->fgrnd= fabs(atom_getfloat(&argv[0]));
    return;
  }
  /*grain table starting point (seconds)*/
  if(strcmp(string->s_name, "gst") == 0) {
  	x->stgr= fabs(atom_getfloat(&argv[0]));
    return;
  }
  /*grain table starting point random deviation*/
  if(strcmp(string->s_name, "gstr") == 0) {
  	x->stgrnd= fabs(atom_getfloat(&argv[0]));
    return;
  }
 /*grain table ending point (seconds)*/
  if(strcmp(string->s_name, "gen") == 0) {
  	x->engr= fabs(atom_getfloat(&argv[0]));
    return;
  }
  /*grain table ending point random deviation*/
  if(strcmp(string->s_name, "genr") == 0) {
  	x->engrnd= fabs(atom_getfloat(&argv[0]));
    return;
  }
  /*loop type*/
  if(strcmp(string->s_name, "loop_t") == 0) {
  	f=atom_getfloat(&argv[0]);
	if(f > 2. || f < 0.) {
		post(" my_grainer~: unknown loop_type option %f (only 0, 1 or 2 are available)", f);
		return;
	}	
  	x->loop_type= (int)f;
	x->loop_direction=0;
    	if(x->post_ctrl)post(" my_grainer~: loop type set to: %d", (int)f);
	return;
  }
  /*glissando added by Damián Anache, 06/01/2016*/
  if(strcmp(string->s_name, "gli") == 0) {
	f=atom_getfloat(&argv[0]);
	if(f < 0. ) {
		post(" my_grainer~: wrong gliss value %f (only positive values are allowed)", f);
		return;
	}
	x->gli= f;	
	if(x->post_ctrl)post(" my_grainer~: new glissandi multiplier: %f", f);
	return;
  }
  /*glissando random deviation added by Damián Anache, 06/01/2016*/
  if(strcmp(string->s_name, "glir") == 0) {
	f=atom_getfloat(&argv[0]);
	if(f < 0. ) {
		post(" my_grainer~: wrong gliss random deviation value %f (only positive values are allowed)", f);
		return;
	}
	x->glir= f;	
	if(x->post_ctrl)post(" my_grainer~: new glissandi random deviation: %f", f);
	return;
  }
  /*grain amp */
  if(strcmp(string->s_name, "ag") == 0) {
  	x->agr= fabs(atom_getfloat(&argv[0]));
    return;
  }
  /*grain amp random deviation*/
  if(strcmp(string->s_name, "agr") == 0) {
  	x->agrnd= fabs(atom_getfloat(&argv[0]));
    return;
  }
  /*grain azimuth */
  if(strcmp(string->s_name, "az") == 0) {
	x->azgr=DEG2RAD(atom_getfloat(&argv[0]));
    return;
  }
  /*grain azimuth random deviation*/
  if(strcmp(string->s_name, "azr") == 0) { 
	x->azgrnd=DEG2RAD(atom_getfloat(&argv[0]));
    return;
  }
  /*grain elevation */
  if(strcmp(string->s_name, "el") == 0) {
    x->elgr=DEG2RAD(atom_getfloat(&argv[0]));
    return;
  }
  /*grain elevation random deviation*/
  if(strcmp(string->s_name, "elr") == 0) {
    x->elgrnd=DEG2RAD(atom_getfloat(&argv[0]));
    return;
  }
  /*grain distance */
  if(strcmp(string->s_name, "dis") == 0) {
  	x->digr= fabs(atom_getfloat(&argv[0]));
    return;
  }
  /*grain distance random deviation*/
  if(strcmp(string->s_name, "disr") == 0) {
  	x->digrnd= fabs(atom_getfloat(&argv[0]));
    return;
  }

/*grain frequency deviation list*/
if(strcmp(string->s_name, "pitch_table") == 0) {
	x->devtsize=0;
	if(x->devt) free(x->devt);
	x->devt=(t_float*)set_dval_sel(x, string, argc, argv, &x->devtsize, "pitch");
	for(i=0; i < x->devtsize; ++i) {
		x->devt[i]=S2INCR(x->devt[i]);
	}
return; 
}
/*gap values selection list*/
if(strcmp(string->s_name, "gap_table") == 0) {
	x->gaptsize=0;
	if(x->gapt) free(x->gapt);
	x->gapt=(t_float*)set_dval_sel(x, string, argc, argv, &x->gaptsize, "gap");
return; 
}
/*dur values selection list*/
if(strcmp(string->s_name, "dur_table") == 0) {
	x->durtsize=0;
	if(x->durt) free(x->durt);
	x->durt=(t_float*)set_dval_sel(x, string, argc, argv, &x->durtsize, "size");
	x->pdtsize=0;
return; 
}
/*file access time values selection list*/
if(strcmp(string->s_name, "ptr_table") == 0) {
	x->ptrtsize=0;
	if(x->ptrt) free(x->ptrt);
	x->ptrt=(t_float*)set_dval_sel(x, string, argc, argv, &x->ptrtsize, "audio table access times");
	x->pdtsize=0;
return; 
}
/*file access time values and dur selection list*/
/*the number of elements must be in pairs time dur, time dur...etc.*/
if(strcmp(string->s_name, "ptr_dur_table") == 0) {
	if(argc % 2 != 0) {
		if(x->post_ctrl)
			post(" my_grainer~: warning, final duration value is missing, ommiting last access time value");
		aux=1;
	}
	if(argc-aux > 0 && argc-aux <= 3 ) {
		if(x->post_ctrl)
			post(" my_grainer~: list must have at least two pairs of time and duration values \n no action taken");
		return;		
	}
	x->pdtsize=0;
	if(x->pdt) free(x->pdt);
	x->pdt=(t_float*)set_dval_sel(x, string, argc-aux, argv, &x->pdtsize, "audio table access and size times");
	/*must set x->ptrtsize=0 and x->durtsize=0*/
	x->ptrtsize=x->durtsize=0;
return; 
}

/*audio table numbers selection list*/
  if(strcmp(string->s_name, "gtab_table") == 0) {
	x->gtatsize=(argc < MAX_TABLES? argc : MAX_TABLES); /*clip list to MAX_TABLES if needed*/
	if(x->post_ctrl)post(" my_grainer~: audio table random selection table set, size=%d", x->gtatsize);
	/*the unset message is not needed, since a set_ntg or gtab messages will do it*/
	for(i=0; i < x->gtatsize; ++i) {
		aux= (int)fabs(atom_getfloat(&argv[i]));
		if(!x->gtab[aux].size) {
			x->gtatsize=0;
			post(" my_grainer~: non allocated grain table requested, use the 'gtab' method to allocate it first");
			return;
		}
		x->gtat[i]=aux; 	
	}	
  return;
  }

 /*gap_restart added by Damián Anache, 06/01/2016*/
  if(strcmp(string->s_name, "gap_restart") == 0) {
	gap_restart(x);
 	return;
  }

 /*block_console_messages added by Damián Anache, 06/01/2016*/
  if(strcmp(string->s_name, "post_ctrl") == 0) {
    	f=atom_getfloat(&argv[0]);
	i=(int)f;
	if(i != 1. && i != 0.) {
		post("my_grainer~: unknown post_ctrl value %i (only 0 or 1 are available)", i);
		return;
	}
	x->post_ctrl=i;	
	if(i)	post("my_grainer~: console posts are enable");
	else  post("my_grainer~: console posts are disable");
	return;
  }

/*sound speed*/
 if(strcmp(string->s_name, "sound_speed") == 0) {
    	x->sound_speed=atom_getfloat(&argv[0]);
	if(x->sound_speed <= MIN_SOUND_SPEED) {
		post("my_grainer~: ilegal sound speed requested (%f m/s), minimal is (%fm/s) using default value (340 m/s)", x->sound_speed, MIN_SOUND_SPEED);
		x->sound_speed=SOUND_SPEED;
	}
	else
		post("my_grainer~: sound speed changed, now is %f m/s", x->sound_speed);	
	return;
 }
/*distance exponent*/
 if(strcmp(string->s_name, "dist_exp") == 0) {
    	x->dist_exp=atom_getfloat(&argv[0]);
	if(x->dist_exp <=0.) {
		post("my_grainer~: ilegal dist_exp requested (%f), using default value (1)", x->dist_exp);
		x->dist_exp=1.;
	}
	else
		post("my_grainer~: dist_exp changed, now is %f", x->dist_exp);	
	return;
 }
/*delay on-off*/
  if(strcmp(string->s_name, "dist_delay") == 0) {
    	f=atom_getfloat(&argv[0]);
	i=(int)f;
	if(i != 1. && i != 0.) {
		post("my_grainer~: unknown dist_delay value %i (only 0 or 1 are available)", i);
		return;
	}
	x->delflag=i;	
	if(i)	post("my_grainer~: distance delay simulation on");
	else    post("my_grainer~: distance delay simulation off");
	return;
  }


return;
}
/*******************************************************************/
void my_grainer_tilde_tables(t_my_grainer_tilde *x, t_symbol *name, int which, char *type) 
{
t_garray *a;
int size=0, i, chflag=TRUE, tloc=0;
int *ngt, *ngtact;
TABLE *gtab;

if(which==GTAB) {
	ngt=	&x->ngt;
	ngtact=	&x->ngtact;
	gtab=	x->gtab;
}
else{
	ngt=	&x->net;
	ngtact=	&x->netact;
	gtab=	x->atab;
}
	
if (!(a = (t_garray *)pd_findbyclass(name, garray_class))) {
	if (*name->s_name) {
      	pd_error(x, " my_grainer~: ERROR, %s: no such array", name->s_name);
		gtab[*ngtact].size=0;
		return;
	}
}

/*first check if it is an already used array name*/
for(i=0; i < *ngt; i++) {
	if(strcmp(gtab[i].name->s_name,name->s_name)==0) {
		*ngtact=i; 
		chflag=FALSE;
		break;
	}
}
if(chflag && *ngt==MAX_AUDIO_TABLES) {	/*do nothing if maximal audio tables is reach*/
	if(x->post_ctrl)post(" my_grainer~: maximal number of audio tables (%d) reached, no action taken ", MAX_AUDIO_TABLES);
	return;
}
	
/*if random selection of tables by a list was active, set it inactive forcing the list size to 0*/	
if(which==GTAB) {	
	if(x->gtatsize) {	
		x->gtatsize=0;
		post(" my_grainer~: random selection of grain tables unset ");
	}
}	

if(*ngt && !chflag) {	/*use an already allocated table (set active table in position "i")*/	
	tloc=*ngtact;	
}
if(chflag) {	/*allocate a new table (set active table to the last one and increment the number of tables)*/
	tloc=*ngt;
}

size = garray_npoints(a);
if (!garray_getfloatwords(a, &size, &gtab[tloc].table)) {
	pd_error(x, " my_grainer~ ERROR, %s: bad template for my_grainer~", name->s_name);
	gtab[tloc].size=0;
	return;
}

gtab[tloc].size=size;
gtab[tloc].name=name;

if(chflag) {
	*ngtact=*ngt;
	*ngt+=1;	   
	if(x->post_ctrl)post(" my_grainer~: new %s table loaded is %s, %d samples ", type, gtab[tloc].name->s_name, gtab[tloc].size);
	if(x->post_ctrl)post("              the number of active %s tables is %d, the current active table is %d (%s) ", type, *ngt, *ngtact, gtab[tloc].name->s_name);
	
}
else {
	if(x->post_ctrl)post(" my_grainer~: warning, %s table %s, overwritten %d samples ", type, gtab[tloc].name->s_name, gtab[tloc].size);
	if(x->post_ctrl)post("              the number of active %s tables is %d, the current active table is %d (%s) ", type, *ngt, *ngtact, gtab[tloc].name->s_name);

}

my_grainer_tilde_grainer_setup(x); 	
garray_usedindsp(a);
	
return;
}
/******************************************************************/
t_int *my_grainer_tilde_perform_ambi3(t_int *w)
{
  t_my_grainer_tilde *x = (t_my_grainer_tilde *)(w[1]);
  t_sample  *W =    (t_sample *)(w[2]);
  t_sample  *X =    (t_sample *)(w[3]);
  t_sample  *Y =    (t_sample *)(w[4]);
  t_sample  *Z =    (t_sample *)(w[5]);
  t_sample  *R =    (t_sample *)(w[6]);
  t_sample  *S =    (t_sample *)(w[7]);
  t_sample  *T =    (t_sample *)(w[8]);
  t_sample  *U =    (t_sample *)(w[9]);
  t_sample  *V =    (t_sample *)(w[10]);
  t_sample  *K =    (t_sample *)(w[11]);
  t_sample  *L =    (t_sample *)(w[12]);
  t_sample  *M =    (t_sample *)(w[13]);
  t_sample  *N =    (t_sample *)(w[14]);
  t_sample  *O =    (t_sample *)(w[15]);
  t_sample  *P =    (t_sample *)(w[16]);
  t_sample  *Q =    (t_sample *)(w[17]);

  t_sample  *rsend =(t_sample *)(w[18]);
  int        n =    (int) (w[19]);

  if(!x->ngt || !x->net || !x->active ) goto zero;

  while(n--) {
      	grainer(&x->g, x);
      	*W++     = x->osig[0];
      	*X++     = x->osig[1];
      	*Y++     = x->osig[2];
      	*Z++     = x->osig[3];
	*R++     = x->osig[4];
       	*S++     = x->osig[5];
	*T++     = x->osig[6];
	*U++     = x->osig[7];
	*V++     = x->osig[8];
      	*K++     = x->osig[9];
      	*L++     = x->osig[10];
	*M++     = x->osig[11];
       	*N++     = x->osig[12];
	*O++     = x->osig[13];
	*P++     = x->osig[14];
	*Q++     = x->osig[15];
      	*rsend++ = x->osig[16];
  }
  return (w+20);
  zero:
  while(n--) {
     	*W++     = 0.;
       	*X++     = 0.;
	*Y++     = 0.;
	*Z++     = 0.;
	*R++     = 0.;
       	*S++     = 0.;
	*T++     = 0.;
	*U++     = 0.;
	*V++     = 0.;
	*K++     = 0.;
	*M++     = 0.;
	*N++     = 0.;
       	*L++     = 0.;
	*O++     = 0.;
	*P++     = 0.;
	*Q++     = 0.;
	*rsend++ = 0.;
  }  
  return (w+20);
}
/******************************************************************/
t_int *my_grainer_tilde_perform_ambi2(t_int *w)
{
  t_my_grainer_tilde *x = (t_my_grainer_tilde *)(w[1]);
  t_sample  *W =    (t_sample *)(w[2]);
  t_sample  *X =    (t_sample *)(w[3]);
  t_sample  *Y =    (t_sample *)(w[4]);
  t_sample  *Z =    (t_sample *)(w[5]);
  t_sample  *R =    (t_sample *)(w[6]);
  t_sample  *S =    (t_sample *)(w[7]);
  t_sample  *T =    (t_sample *)(w[8]);
  t_sample  *U =    (t_sample *)(w[9]);
  t_sample  *V =    (t_sample *)(w[10]);

  t_sample  *rsend =(t_sample *)(w[11]);
  int        n 	   =(int) (w[12]);

  if(!x->ngt || !x->net || !x->active ) goto zero;

  while(n--) {
      	grainer(&x->g, x);
      	*W++     = x->osig[0]; 
	*X++     = x->osig[1];    	
	*Y++     = x->osig[2];
      	*Z++     = x->osig[3];
	*R++     = x->osig[4];
       	*S++     = x->osig[5];
	*T++     = x->osig[6];
	*U++     = x->osig[7];
	*V++     = x->osig[8];
      	*rsend++ = x->osig[9];
  }
  return (w+13);
  zero:
  
  while(n--) {
     	*W++     = 0.;
       	*X++     = 0.;
	*Y++     = 0.;
	*Z++     = 0.;
	*R++     = 0.;
       	*S++     = 0.;
	*T++     = 0.;
	*U++     = 0.;
	*V++     = 0.;
	*rsend++ = 0.;
  }  
  return (w+13);
}
/******************************************************************/
t_int *my_grainer_tilde_perform_ambi(t_int *w)
{
  t_my_grainer_tilde *x = (t_my_grainer_tilde *)(w[1]);
  t_sample  *W =    (t_sample *)(w[2]);
  t_sample  *X =    (t_sample *)(w[3]);
  t_sample  *Y =    (t_sample *)(w[4]);
  t_sample  *Z =    (t_sample *)(w[5]);
  t_sample  *rsend =(t_sample *)(w[6]);
  int        n =    (int) (w[7]);

  if(!x->ngt || !x->net || !x->active ) goto zero;

  while(n--) {
      grainer(&x->g, x);
      	*W++     = x->osig[0];
      	*X++     = x->osig[1];
	*Y++     = x->osig[2];
	*Z++     = x->osig[3];
	*rsend++ = x->osig[4];
  }
  return (w+8);
  zero:
  while(n--) {
     	*W++     = 0.;
      	*X++     = 0.;
	*Y++     = 0.;
	*Z++     = 0.;
	*rsend++ = 0.;
  }  
  return (w+8);
}
/******************************************************************/
t_int *my_grainer_tilde_perform_ipan(t_int *w)
{
	t_my_grainer_tilde *x = (t_my_grainer_tilde *)(w[1]);

	t_sample  *out1 =    (t_sample *)(w[2]);
 	t_sample  *out2 =    (t_sample *)(w[3]);
	t_sample  *rsend =   (t_sample *)(w[4]);  	
	int n  =    (int) (w[5]);

	if(!x->ngt || !x->net || !x->active ) goto zero;

	while(n--) {
      	grainer(&x->g, x);
	      	*out1++  = x->osig[0];
      		*out2++  = x->osig[1];
		*rsend++ = x->osig[2];
    	}
	return (w+6);
	
	zero:
	while(n--) {
	      	*out1++  = 0.;
	      	*out2++  = 0.;
	      	*rsend++ = 0.;
	}
	return (w+6);
}
/******************************************************************/
t_int *my_grainer_tilde_perform_mono(t_int *w)
{
	t_my_grainer_tilde *x = (t_my_grainer_tilde *)(w[1]);
	t_sample  *out   =    (t_sample *)(w[2]);
	t_sample  *rsend =    (t_sample *)(w[3]);
	int          n   =    (int) (w[4]);

	if(!x->ngt || !x->net || !x->active) goto zero;

	while(n--) {
      	grainer(&x->g, x);
      		*out++   = x->osig[0];
		*rsend++ = x->osig[1];
	}
 	return (w+5);

 	zero:
	while(n--) {
      		*out++  =0.;
		*rsend++=0.;
	}
 	return (w+5);
}
/******************************************************************/
void my_grainer_tilde_dsp(t_my_grainer_tilde *x, t_signal **sp)
{
	int i, size;
	t_garray *a;


	/*it seems that we do not have other way of checking whether an array is alive*/
	for(i=0; i < x->ngt; i++) {
		if (!(a = (t_garray *)pd_findbyclass(x->gtab[i].name, garray_class))) {
			/*if a table was deleted we set its size to 0, so that the oscillator that is using it will know*/			
			x->gtab[i].size=0;
			return;
  		}
		size = garray_npoints(a);
		if(size < x->gtab[i].size) {
			x->gtab[i].size=size; /*did the user overwrite the audio table?*/
		}
	}
	for(i=0; i < x->net; i++) { /*ditto...*/
		if (!(a = (t_garray *)pd_findbyclass(x->atab[i].name, garray_class))) {
			x->atab[i].size=0;
			return;
			
  		}
		size = garray_npoints(a);
		if(size < x->gtab[i].size) {
			x->atab[i].size=size; /*ditto..*/
		}	
	}
	/*now, if everything seems to be OK, we call the corresponding perform function*/
	switch(x->nch) {
 	 	case (MONO): { /* mono */ 
			dsp_add(my_grainer_tilde_perform_mono, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
			break;
		}	
 		case (IPAN): { /* stereo intensity panning */ 
			dsp_add(my_grainer_tilde_perform_ipan, 5, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[0]->s_n);
			break;
		}	
  	 	case (AMBI): {  /* ambisonic B format, first order */
			dsp_add(my_grainer_tilde_perform_ambi, 7, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[4]->s_vec, sp[0]->s_n);
			break;	
		}
		case (AMBI2): {  /* ambisonic B format, second order */
			dsp_add(my_grainer_tilde_perform_ambi2, 12, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[4]->s_vec, sp[5]->s_vec,
			sp[6]->s_vec, sp[7]->s_vec, sp[8]->s_vec, sp[9]->s_vec, sp[0]->s_n);
			break;	
		}
		case (AMBI3): {  /* ambisonic B format, third order */
			dsp_add(my_grainer_tilde_perform_ambi3, 19, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[4]->s_vec, sp[5]->s_vec,
			sp[6]->s_vec, sp[7]->s_vec, sp[8]->s_vec, sp[9]->s_vec, sp[10]->s_vec, sp[11]->s_vec, sp[12]->s_vec, sp[13]->s_vec, sp[14]->s_vec,
			sp[15]->s_vec, sp[16]->s_vec, sp[0]->s_n);
			break;	
		}
		default: {
			break;
		}
	}
}
/******************************************************************/
/******************************************************************/
void *my_grainer_tilde_new(t_floatarg f)
{ 
int i;

t_my_grainer_tilde *x = (t_my_grainer_tilde *)pd_new(my_grainer_tilde_class);
  
grainer_setup(x);

x->nch=(int)f;

/* AUDIO OUTLETS*/
if(x->nch !=MONO && x->nch !=IPAN && x->nch !=AMBI && x->nch !=AMBI2 && x->nch !=AMBI3) {	
	x->nch=IPAN; /*default is stereo intensity panning*/
}
for(i=0; i < x->nch+1; ++i) {     
/*there will be nch+1 signal outlets because the nth+1 outlet is for the reverb send*/
	outlet_new(&x->x_obj, &s_signal);
}
	
switch(x->nch) {
	case(MONO): {
		post(" my_grainer~: mono output set ");
		break;	
	}
	case(IPAN): {
		post(" my_grainer~: stereo output set (Intensity Panning)");
		break;	
	}
	case(AMBI): {
		post(" my_grainer~: output set to First order Ambisonic B format \n signal outlets: W, X, Y, Z, Reverb_send");
		break;	
	}
	case(AMBI2): {
		post(" my_grainer~: output set to Second order Ambisonic B format \n signal outlets: W, X, Y, Z, R, S, T, U, V, Reverb_send");	
		break;	
	}
	case(AMBI3): {
		post(" my_grainer~: output set to Third order Ambisonic B format \n signal outlets: W, X, Y, Z, R, S, T, U, V, K, L, M, N, O, P, Q, Reverb_send");	
		break;	
	}
	default: {
		break;
	}
}
return (void *)x;
}
/******************************************************************/
/******************************************************************/
void my_grainer_tilde_setup() {

	my_grainer_tilde_class = class_new(gensym("my_grainer~"),
				     (t_newmethod)my_grainer_tilde_new,
				     (t_method)my_grainer_tilde_destroy, sizeof(t_my_grainer_tilde),
				     CLASS_DEFAULT, A_DEFFLOAT, 0);	

	class_addanything(my_grainer_tilde_class, my_grainer_tilde_any);
	class_addmethod(my_grainer_tilde_class,(t_method)my_grainer_tilde_dsp, gensym("dsp"),0);
	class_addmethod(my_grainer_tilde_class, (t_method)my_grainer_tilde_usegtn,
        gensym("usegtn"), A_DEFFLOAT, 0);
	class_addmethod(my_grainer_tilde_class, (t_method)my_grainer_tilde_useatn,
        gensym("useatn"), A_DEFFLOAT, 0);
  	post("\n my_grainer~ external V.3.2 September. 2016 \n Pablo Di Liscia \n UNQ");
	return;
}
/******************************************************************/
void my_grainer_tilde_destroy(t_my_grainer_tilde *x) 
{
int i;
	for(i=0; i<x->ng; ++i){
		if(x->g[i]->delbuf)
			freebytes(x->g[i]->delbuf, sizeof(t_float)*x->g[i]->delsi);
	}
	if(x->gapt) freebytes(x->gapt, sizeof(t_float)*x->gaptsize);
	if(x->durt) freebytes(x->durt, sizeof(t_float)*x->durtsize);
	if(x->ptrt) freebytes(x->ptrt, sizeof(t_float)*x->ptrtsize);
	if(x->pdt)  freebytes(x->pdt, sizeof(t_float)*x->pdtsize);

	if(x->g) freebytes(x->g, sizeof(GRAIN)*x->ng);	
}
/******************************************************************/
/******************************************************************/
/**************DEFINITIONS OF THE AUDIO FUNCTIONS *****************/
/******************************************************************/
OSCIL *set_oscil(int start, int end, int LT, int Ldir, t_float gliss, t_float glissrnd, double incr, t_my_grainer_tilde *x, int which)
{
OSCIL *oscil;

oscil=(OSCIL*) malloc(sizeof(OSCIL));
  
if(which==GTAB) {							/*audio oscillator*/
	oscil->incr		= incr;
	oscil->index		= (double)start;	 		/*initial phase in samples*/		  
	oscil->fros		= start; 				/*initial read point in samples*/
	oscil->ends		= end; 					/*ending read point in samples*/
	oscil->durs 		= oscil->ends - oscil->fros; 		/*loop size in samples*/
	oscil->LT		= LT;					/*loop type, see the macros for this*/
	oscil->Ldir		= Ldir;					/*loop direction*/
	/*step size for reaching (incr * gliss value) at the end of the grain*/		
	oscil->gliss	= ((incr*(gliss+BIRAND_FLOAT(glissrnd)))-incr)/(x->sgr*x->sr);
	/*set grain table */		
	if(!x->gtatsize) {		
		oscil->nt	= x->ngtact;				/*current active table number*/
	}	
	else {
		oscil->nt=x->gtat[RAND_INT(x->gtatsize)];		/*random selection*/			
	}
	
}
else {									/*envelope oscillator*/
	oscil->index	= 0.;
	oscil->incr	= incr;
	oscil->nt	= x->netact;					/*table number*/
}
return(oscil);
}
/********************************************************/
t_float goscil(OSCIL *oscil, t_float amp, t_my_grainer_tilde *x )
{
/*table-lookup oscillator with loops forward and forward-backward*/
t_float output=0.;
int   curr, next;

/*check if the table requested remains alive*/
if(x->gtab[oscil->nt].size==0) {
	return(0.);	
}

/*put the oscillator index in range according its loop type*/
switch(oscil->LT) {
	case NOLOOP: {
		while ( oscil->index >= (double)x->gtab[oscil->nt].size ) oscil->index -= x->gtab[oscil->nt].size ;
		while ( oscil->index < 0.) oscil->index += (double)x->gtab[oscil->nt].size ;
		curr= (int) oscil->index;
		next= (int) oscil->index == x->gtab[oscil->nt].size-1? 0 : (int)oscil->index + 1;
		break;
	}  
	case LOOPF: {
		/*this checking is necessary as the user may overwrite the active table and change its size*/
		if(oscil->fros >= x->gtab[oscil->nt].size || oscil->fros < 0 || oscil->ends >= x->gtab[oscil->nt].size || oscil->ends < 0) {
			oscil->LT=NOLOOP;
			x->loop_type=NOLOOP;
			return(0.);	
		}
		while ( oscil->index >= (double)oscil->ends ) oscil->index -= (double)oscil->durs ;
  		while ( oscil->index <  (double)oscil->fros ) oscil->index += (double)oscil->durs ;			
		curr= (int) oscil->index;
		next= (int) oscil->index == oscil->ends-1? oscil->fros : (int)oscil->index + 1;		
		break;
	}	
	case LOOPFB: {
		/*this checking is necessary as the user may have overwritten the active table and changed its size*/
		if(oscil->fros >= x->gtab[oscil->nt].size || oscil->fros < 0 || oscil->ends >= x->gtab[oscil->nt].size || oscil->ends < 0) {
			oscil->LT=NOLOOP;
				x->loop_type=NOLOOP;
			return(0.);	
		}
		if (oscil->Ldir == 0){
			if ( oscil->index + oscil->incr >= oscil->ends - 1. ) oscil->Ldir = 1;
		}
		else	{
			if ( oscil->index - oscil->incr <= oscil->fros ) oscil->Ldir = 0;
		}
		while ( oscil->index >= (double)oscil->ends ) oscil->index -= (double)oscil->durs ;
  	      	while ( oscil->index <  (double)oscil->fros ) oscil->index += (double)oscil->durs ;			
		curr= (int) oscil->index;
		next= (int) oscil->index == oscil->ends-1? oscil->fros : (int)oscil->index + 1;		
		break;
	}
	default: {
		break;
	}
}
/*get the right sample value by linear interpolation*/
output=x->gtab[oscil->nt].table[curr].w_float + ((oscil->index-(double)curr)*(x->gtab[oscil->nt].table[next].w_float - x->gtab[oscil->nt].table[curr].w_float));
	
if (oscil->Ldir) oscil->index-=oscil->incr;
else oscil->index+=oscil->incr;

if (oscil->gliss !=1.) { 
	oscil->incr+=oscil->gliss;
}
return(amp*output);

}
/********************************************************/
t_float aoscil(OSCIL *oscil, t_float amp, t_my_grainer_tilde *x )
{
/*this is a simple table-lookup oscillator*/
t_float output=0.;
int   curr, next;

if(x->atab[oscil->nt].size==0) {
	return(0.);
}

while ( oscil->index >= (double)x->atab[oscil->nt].size ) oscil->index -= (double)x->atab[oscil->nt].size ;
while ( oscil->index < 0. ) oscil->index += (double)x->atab[oscil->nt].size ;
curr= (int) oscil->index;
next= (int) oscil->index == x->atab[oscil->nt].size-1? curr : (int)oscil->index + 1;

output=x->atab[oscil->nt].table[curr].w_float + ((oscil->index-(double)curr)*(x->atab[oscil->nt].table[next].w_float - x->atab[oscil->nt].table[curr].w_float));
oscil->index+=oscil->incr;

return(amp*output);
}
/********************************************************************/
t_float set_birand_val(t_float base, t_float rdev)
{
t_float val;
if(rdev <= 0.) return(base);
val= base + BIRAND_FLOAT(rdev);
val= val <=0.? base : val;  
return(val);
}
/********************************************************************/
void set_pan_gains(t_my_grainer_tilde *x, GRAIN *g)
{
/*auxiliar variables*/
t_float cosazi, sinazi,cosele, sinele, sin2ele, coselepow2, azi2;
t_float sinpow2t5, coselepow3, azi3, sinelepow2, sinpow2t5m1;

/*compute angles and gains for each output channel according the output type*/
if(x->nch != MONO) {

	/*compute grain azimuth angle*/
	g->azi= x->azgr + BIRAND_FLOAT(x->azgrnd);
	
	/*do we have stereo output?*/		
	if(x->nch == IPAN) {
		g->azi=g->azi < DEG45?  DEG45 :g->azi; 	/*keep in range*/
		g->azi=g->azi > DEG135? DEG135:g->azi;
		g->azi-=DEG45;
		g->gch[0]=sin(g->azi); /*pre calculate gains for each channel*/
		g->gch[1]=cos(g->azi); /*according to intensity panning*/
		return;			
	}
		
	/*If we are here, it is because we need the Ambisonics setup*/
	/*compute and check angles first*/
	/*keep in range for Ambisonic azimuth*/
	g->azi-=DEG90;
	while(g->azi < 0.) g->azi+=PI2; /*wrap around azimuth angle if needed*/
	while(g->azi > PI2)g->azi-=PI2;
	/*compute grain elevation angle*/ 
	g->ele= x->elgr + BIRAND_FLOAT(x->elgrnd);
	while(g->ele < 0.) g->ele+=PI2; /*wrap around elevation angle if needed*/
	while(g->ele > PI2)g->ele-=PI2;

	/*pre-compute the gains for each ambisonic first order B Format signal
	we use here the FuMa set (SN3D*normalization factors) for encoding
	See http://www.blueripplesound.com/b-format
	first, pre-compute cosine and sine of elevation and azimuth, to save operations
	*/
	cosazi=cos(g->azi);
	sinazi=sin(g->azi);
	cosele=cos(g->ele);
	sinele=sin(g->ele);
	/* 
	W	0	sqrt(1/2)	
	X	1	cos(A)cos(E)
	Y	1	sin(A)cos(E)	
	Z	1	sin(E)	
	*/
	g->gch[0]=ASCAL;			/*W signal*/
	g->gch[1]=(cosazi*cosele);		/*X signal*/
	g->gch[2]=(sinazi*cosele);		/*Y signal*/
	g->gch[3]=sinele;			/*Z signal*/
	if(x->nch == AMBI) return;
				
	/*Ditto, pre-compute and add the remaining gains for each ambisonic second order B Format signal*/
	/*first, pre-compute some factors to save operations*/
	azi2   	=g->azi*2.;				
	sin2ele	=sin(g->ele*2.);
	coselepow2=cosele*cosele;
	sinelepow2=sinele*sinele;
	/* 
	R	2	(1/2)(3sin(E)sin(E)-1)	
	S	2	cos(A)sin(2E)	
	T	2	sin(A)sin(2E)	
	U	2	cos(2A)cos(E)cos(E)	
	V	2	sin(2A)cos(E)cos(E)	
	*/
	g->gch[4]=(3.*sinelepow2-1.)/2.;	/*R signal*/
	g->gch[5]=(cosazi*sin2ele);		/*S signal*/
	g->gch[6]=(sinazi*sin2ele);		/*T signal*/
	g->gch[7]=(cos(azi2)*coselepow2);	/*U signal*/
	g->gch[8]=(sin(azi2)*coselepow2);	/*V signal*/
	if(x->nch == AMBI2) return;
	
	/*Ditto, pre-compute and add the remaining gains for each ambisonic third order B Format signal*/
	/*first, pre-compute some factors to save operations*/	
	sinpow2t5	=sinelepow2*5.;
	sinpow2t5m1	=sinpow2t5-1.;
	coselepow3	=coselepow2*2.;
	azi3		=3.*g->azi;
	
	/* 
	K	3	(1/2)sin(E)(5sin(E)sin(E)-3)	
	L	3	sqrt(135/256)cos(A)cos(E)(5sin(E)sin(E)-1)	
	M	3	sqrt(135/256)sin(A)cos(E)(5sin(E)sin(E)-1)	
	N	3	sqrt(27/4)cos(2A)sin(E)cos(E)cos(E)	
	O	3	sqrt(27/4)sin(2A)sin(E)cos(E)cos(E)	
	P	3	cos(3A)cos(E)cos(E)cos(E)	
	Q	3	sin(3A)cos(E)cos(E)cos(E)	
	*/
	g->gch[9] =(0.5*sinele*(sinpow2t5-3.));  		/*K signal*/		
	g->gch[10]=(ASCAL2*(g->gch[1])*sinpow2t5m1);		/*L signal*/
	g->gch[11]=(ASCAL2*(g->gch[2])*sinpow2t5m1);		/*M signal*/
	g->gch[12]=(ASCAL3*(g->gch[7])*sinele);			/*N signal*/
	g->gch[13]=(ASCAL3*(g->gch[8])*sinele);			/*O signal*/
	g->gch[14]=(cos(azi3)*coselepow3);			/*P signal*/
	g->gch[15]=(sin(azi3)*coselepow3);			/*Q signal*/	
	return;
	}
	
else {
	g->gch[0]=1.;		/*mono needs no angles*/
}
return;
}
/********************************************************************/
GRAIN *grain_setup(t_my_grainer_tilde *x)
{
	t_float from=0., end=0., tabledur=(t_float)x->gtab[x->ngtact].size/x->sr, gli=x->gli, glir=x->glir;
	t_float faux;	
	/*the loop type must be a local variable of each grain oscillator, 
	otherwise when changed, the oscillators of the current active grains 
	may crash.*/
	int loop_type=x->loop_type, loop_direction=x->loop_direction, aux=0, i;
	GRAIN *g;

	/*allocate memory for the pointer*/
	g=(GRAIN *)malloc(sizeof(GRAIN));

	/*compute grain size in samples*/
	if(!x->pdtsize) {

		faux=x->durtsize? set_birand_val(x->durt[RAND_INT(x->durtsize)],x->sgrnd) : set_birand_val(x->sgr, x->sgrnd); 	
		if(faux == 0.) faux=MIN_DUR;
		if(faux <  0.) faux*=-1.;
		g->size=floor(faux*(t_float)x->sr);
		/*compute phase offset for the grain table lookup from stgr*/
		if(x->ptrtsize) {
			from=set_birand_val(x->ptrt[RAND_INT(x->ptrtsize)],x->stgrnd);
			loop_type=NOLOOP; /*loop type not available in list selection mode*/
			loop_direction=0;
		}
		else {
  			from= (x->stgr + BIRAND_FLOAT(x->stgrnd));
		}
	}
	else{
		aux=RAND_INT(x->pdtsize);
		if(aux%2 == 0 ) aux+=1; /*aux must be odd*/  
		faux	=	set_birand_val(x->pdt[aux],x->sgrnd);
		if(faux == 0.) 	faux=MIN_DUR;
		if(faux <  0.) 	faux*=-1.;
		g->size=floor(faux*(t_float)x->sr);
		from	=      set_birand_val(x->pdt[aux-1],x->stgrnd);
		loop_type=NOLOOP; /*overwrite the loop type variable here*/
		loop_direction=0;	
	}
	
	/*check here some possibly wrong conditions*/
	/*from can't be less than zero neither >= tabledur*/
	if(from < 0. || from >= tabledur)  from=0.;
	/*compute end for the grain table lookup from engr*/
	end= (x->engr + BIRAND_FLOAT(x->engrnd));
	/*end can't be <= 0. neither >=tabledur, neither <=from*/
	/*if any of there conditions are met, we set it to zero and set the loop
	flag to NO_LOOP*/  
	if(end <= 0. || end > tabledur || end <= from) {
  		end=tabledur; /*not sure if this is really needed*/
		loop_type=NOLOOP; /*overwrite the loop type variable here*/
		loop_direction=0;
	}		
	
	/*compute increment to -possibly- change the frequency of the grain*/
	if(x->devtsize) {
		g->incr=x->fgr*(set_birand_val(x->devt[RAND_INT(x->devtsize)], x->fgrnd));
	}
	else {
		g->incr=set_birand_val(x->fgr, x->fgrnd);
	}
  	
	/*compute the increment for the envelope oscil so as it fits the grain duration*/
  	g->incra=(t_float)x->atab[x->netact].size/(t_float)g->size;
  
	/*compute grain amp*/
	g->amp= set_birand_val(x->agr, x->agrnd);
	
	/*compute grain distance*/
	g->dist=set_birand_val(x->digr, x->digrnd);
	g->dist=(g->dist < MIN_DIST ? MIN_DIST : g->dist);
	g->dist=(g->dist > MAX_DIST ? MAX_DIST : g->dist);
	g->distaten=pow(g->dist,x->dist_exp);	/*apply distance exponent for amplitude attenuation*/
	
	/*compute delay parameters and allocate memory for its buffer*/
	g->delbuf=NULL;	/*must initialize!*/
	if(x->dosend) {	
		if(x->delflag) {	
			g->delsi=(floor) ((g->dist / x->sound_speed) * x->sr);
			g->delpo=0;
			g->delbuf=(t_float*) malloc(g->delsi*sizeof(t_float));
			if(g->delbuf) {	
				for(i=0; i < g->delsi; i++) {
					g->delbuf[i]=0.;
				}
			g->delflag=TRUE;
			}
			else {
				post(" my_grainer~: could not allocate delay buffer. Delay suppressed");
				g->delflag=FALSE;
				x->delflag=FALSE; /*this is only because something REALLY bad may be happening*/
			}
		}
		else {
			g->delflag=0;
		}
	}

	/*compute gain factors according to the angular panning technique*/
	set_pan_gains(x, g);

	/*initialize the sample counter and the total samps used*/
	/*must increase it by delsize samples*/
	g->s_count  =g->size;
	if(g->delflag) {	
		g->s_count  +=g->delsi;
	}
	/*set the two needed oscilators*/
	g->gosc=set_oscil(floor(from*x->sr),floor(end*x->sr)-1, loop_type, loop_direction, gli, glir, (double)g->incr, x, GTAB);
	g->aosc=set_oscil(0, 0, NOLOOP, 0, 1.,0., (double)g->incra, x, ATAB);
	return(g);
}
/********************************************************************/
void grain_sinth(GRAIN *g, t_my_grainer_tilde *x)
{

if(--g->s_count) {
	if(g->delsi <= 0 || !g->delflag) {		/*delay is OFF*/
		g->send=(goscil(g->gosc, aoscil(g->aosc, g->amp, x),x));
		g->dry=g->send/g->distaten;
		return;
	}
	else {						/*delay is ON*/
		if(g->s_count > g->delsi) {
			g->send=(goscil(g->gosc, aoscil(g->aosc, g->amp, x),x)); /*send signal with neither amp scaling nor delay*/	
			if(++g->delpo >= g->delsi) g->delpo=0;
			g->dry=g->delbuf[g->delpo] / g->distaten;		/*dry signal with both distance scaling and delay*/
			g->delbuf[g->delpo]=g->send;
			return;
		}
		else {							
			if(++g->delpo >= g->delsi) g->delpo=0;
			g->dry=g->delbuf[g->delpo] / g->distaten;
			g->delbuf[g->delpo]=0.;
			return;
		}	
	}
}
return; 
}
/********************************************************************/
void compute_gap(t_my_grainer_tilde *x)
{
t_float aux;

aux= x->gaptsize? set_birand_val(x->gapt[RAND_INT(x->gaptsize)], x->gagrnd) : set_birand_val(x->gagr, x->gagrnd);

if(aux == 0.) aux= MIN_GAP;
if(aux <  0.) aux= -aux;

x->gap_samps= floor(aux*(t_float)x->sr);

return;
}
/********************************************************************/
void grainer_setup(t_my_grainer_tilde *x )
{
int i;

x->g=0;
x->ngt=0;
x->net=0;
x->ngtact=0;
x->netact=0;

for(i=0; i < MAX_AUDIO_TABLES; ++i) { 
	x->gtab[i].size=0;
	x->atab[i].size=0;
}

x->devtsize=x->gaptsize=x->durtsize=x->ptrtsize=x->gtatsize=x->atatsize=x->pdtsize=0;
x->gapt=x->durt=x->devt=x->ptrt=x->pdt=NULL;

x->active=0;
x->pause=0;
x->sr=sys_getsr();
x->post_ctrl=1;

x->sound_speed	=SOUND_SPEED;
x->max_dist	=MAX_DIST;
x->dist_exp	=DIST_EXP;
x->dosend	=1;


/*set default values*/
x->gagr=0.05;  x->gagrnd=0.0;      	/*gap between grains and its random deviation*/
x->agr=1.;     x->agrnd=0.0;	  	/*grain amplitude and its random deviation*/
x->fgr=1.;     x->fgrnd=0.0;    	/*grain frequency and its random deviation*/
x->sgr=0.1;    x->sgrnd=0.0;    	/*grain dur and its random deviation*/
x->stgr=0.0;   x->stgrnd=0.0;   	/*grain starting point on the table and its random deviation*/
x->engr=0.0;   x->engrnd=0.0;    	/*grain ending point on the table and its random deviation*/
  
x->loop_type=NOLOOP;			/*loop type*/	
x->loop_direction=0;			/*loop direction, aux variable*/
x->gli=1.0;				/*glissando parameters*/
x->glir=0.0;

x->delflag	=TRUE;

if(x->nch < AMBI) {
	x->azgr  =DEG2RAD(90.);		/*azimut angle of the grains and its random deviation*/
	x->azgrnd=0.0;
} 					
else {					/*Ambisonics angles convention are different*/
	x->azgr  =0.0;			/*azimut angle of the grains and its random deviation*/
	x->azgrnd=0.0;
	x->elgr  =0.0;			/*elevation angle of the grains and its random deviation*/
	x->elgrnd=0.0;	 		
}
x->digr=1.0;				/*distance of the grains and its random deviation*/
x->digrnd=0.0;
	
/*compute the gap for the first grain*/
compute_gap(x); 
x->gap_count=x->gap_samps;


return;
}


/********************************************************************/
inline void grainer(GRAIN ***g, t_my_grainer_tilde *x)
{
  int i, k;
  t_float grain=0.;
  int new=FALSE;		

  /*first, check if grainer is not paused*/
  if(x->pause == 0) {
	/*then, check if we need to create a new grain*/
  	if(!x->gap_count--) { 			/*we do!*/
		for(i=0; i<x->ng; ++i) {         	/*try to find out an unused GRAIN pointer*/  
      			if(!(*g)[i]->s_count) {	/*gotcha*/
				if((*g)[i]->delflag) free((*g)[i]->delbuf);
				free((*g)[i]);          /*free it*/
				(*g)[i]=grain_setup(x); /*use its pointer to create new grain*/
    				new=TRUE;
    				break;
      			}
    		}
    		/*if we did not found an unused GRAIN pointer, we need a new one*/
    		if(!new){
      			x->ng++;                                 			/*increment grain counter*/
      			(*g) =  (GRAIN **) realloc ((*g), sizeof(GRAIN *) * x->ng );	/*realloc memory*/
      			(*g)[x->ng-1]=grain_setup(x);            			/*a new grain has born!*/
    		}
	    	/*compute the samples of a new gap and set gap counter*/
      		compute_gap(x); 
		x->gap_count=x->gap_samps;
  	}
  }

  /*now, compute the active grains*/
  /*mute first the output variables*/
  for(k=0; k < x->nch+1; k++) {
		x->osig[k]=0.;
  }
  /*compute the output from the sum of active grains and do spatial distribution*/
  for(i=0; i< x->ng; i++) {
    	if((*g)[i]->s_count) { 				/*check if the grain is alive and decrement its sample counter*/
		grain_sinth((*g)[i], x);			/*synthesize the grain*/
		if(x->dosend) {
      			x->osig[x->nch]+=(*g)[i]->send;		/*put the plain output in the reverb send, if requested*/
		}		
		for(k=0; k < x->nch; k++) {			/*distribute the grain signal over the available output channels*/
		x->osig[k]+=(*g)[i]->dry*((*g)[i]->gch[k]); 
		}
  	}
  }
  return;
}
/*************************************************************************************/
void display_grainer_params(t_my_grainer_tilde *x )
{
	char *str=NULL;
	int i;

	str=(char*)malloc(1024*sizeof(char));


  	post("\nmy_grainer~ actual parameters **********************************");

	if(x->active)
		post("  grainer is active \t\t\t"); 
	else
		post("  grainer is stopped \t\t\t"); 
	if(x->pause)
		post("  state: paused \t\t\t"); 
	else
		post("  state: running \t\t\t");

	post("  sampling rate \t\t\t%f", 	 x->sr); 
	
	post("  Allocated audio tables \t\t\t%d", 	 x->ngt);
	if(x->ngt) {
		post("  Last active audio table \t\t\t%s", 	 x->gtab[x->ngtact].name->s_name);
		for(i=0; i<x->ngt; i++) {
			if(x->gtab[i].size)
				post("  Audio table   \t\t\t#%d is %s (%d samples)", 	i, x->gtab[i].name->s_name, x->gtab[i].size);
			else
				post("  Deleted Audio table   \t\t\t#%d is %s", 	i, x->gtab[i].name->s_name);
  		}
	}
	post("  Allocated envelope tables \t\t\t%d", 	 x->net);
	if(x->net) {
		post("  Last active envelope table \t\t\t%s", 	 x->atab[x->netact].name->s_name);

		for(i=0; i<x->net; i++) {
			if(x->atab[i].size)
				post("  Envelope table   \t\t\t#%d is %s (%d samples)", 	i, x->atab[i].name->s_name, x->atab[i].size);
			else
				post("  Deleted envelope table   \t\t\t#%d is %s", 	i, x->atab[i].name->s_name);
  		}
	}

 	post("\n  grain size (segs.) \t\t\t%f",   x->sgr); 
 	post("  size  rnd. dev. \t\t\t%f",	 x->sgrnd);
	if(x->durtsize) {
		charray_print(x->durtsize, x->durt, str);
		post("  Discrete values mode selection for grain size set");
		post("  Array size: \t\t\t%d \n  Array values:\t\t\t%s", x->durtsize, str);
	}	

 	post("\n  gap  size in segs. \t\t\t%f",   x->gagr); 
 	post("  gap size in samples \t\t\t%d",   x->gap_samps);
	post("  gap size rnd. dev. \t\t\t%f",   x->gagrnd);
	
	if(x->gaptsize) {
		charray_print(x->gaptsize, x->gapt, str);
		post("  Discrete values mode selection for gap times set");
		post("  Array size: \t\t\t%d \n  Array values:\t\t\t%s", x->gaptsize, str);
	}

	post("\n  table start \t\t\t%f",   x->stgr); 
	post("  table start rnd. dev. \t\t\t%f",   x->stgrnd);
	if(x->ptrtsize) {
		charray_print(x->ptrtsize, x->ptrt, str);
		post("  Discrete values mode selection for grain starting times set");
		post("  Array size: \t\t\t%d \n  Array values:\t\t\t%s", x->ptrtsize, str);
	}
	post("\n  table end \t\t\t%f",   x->engr); 
	post("  table end rnd. dev. \t\t\t%f",   x->engrnd);
	switch(x->loop_type) {
		case NOLOOP:
						post("  Loop Type: \t\t\tNo Loop");
						break;
		case LOOPF:
						post("  Loop Type: \t\t\tForward Loop");
						break;
		case LOOPFB:
						post("  Loop Type: \t\t\tForward-Backward Loop");
						break;
	}

  	post("\n  freq. scaler \t\t\t%f",   x->fgr); 
	post("  freq. rnd. dev. \t\t\t%f",   x->fgrnd);
	if(x->devtsize) {
		charray_print(x->devtsize, x->devt, str);
		post("  Discrete values mode selection for frequency deviation set");
		post("  Array size: \t\t\t%d \n  Array values:\t\t\t%s", x->devtsize, str);
	}

	post("\n  amp. scaler \t\t\t%f",   x->agr); 
	post("  amp. rnd. dev. \t\t\t%f",   x->agrnd);
  
	if(x->nch==MONO) {
		post("\n  output type \t\t\tMono");
	}
	if(x->nch==IPAN) {
		post("\n  output type \t\t\tStereo IP"); 
	}
	if(x->nch==AMBI) {
		post("\n  output type \t\t\tAmbisonic first Order B Format");
	}

	post("  grain dist. \t\t\t%f",   x->digr); 
	post("  grain dist. rnd. dev. \t\t\t%f",   x->digrnd);	 
	if(x->nch==IPAN || x->nch>=AMBI) {
		post("  azimuth center \t\t\t%f",   RAD2DEG(x->azgr)); 
  		post("  az. rnd. dev. \t\t\t%f",   RAD2DEG(x->azgrnd));  
		if(x->nch>=AMBI) {
			post("  elevation center \t\t\t%f", RAD2DEG(x->elgr)); 
			post("  el. rnd. dev. \t\t\t%f", RAD2DEG(x->elgrnd));
		}
	}

	if(str) {
		free(str);
	}

  	post("  ***************************************************************");
 
}

/******************************************************************/
void charray_print(int size, t_float *data, char *str)
{
	int i;
	char *num;

  	num=(char*)malloc(32*sizeof(char));
	*str=0;
	for(i=0; i<size; ++i) {	
		*num=0;	
		sprintf(num, "%8.5f", fabs(data[i]));
		strcat(str, num);
	}
	free(num);
	return;
}

/******************************************************************/
void gap_restart(t_my_grainer_tilde *x ) /*added by Damián Anache, 06/01/2016*/
{
	x->gap_count=x->gap_samps;
	if(x->post_ctrl)post(" my_grainer~ gap counter is restarted"); 
}
