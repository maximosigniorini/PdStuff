#include "m_pd.h"
#include <stdio.h> 
#include <sys/shm.h> 
#include <sys/stat.h> 

typedef struct shmem
{
  t_object x_obj;
  int segment_id;
  t_float *share_memory; 
  int segment_size; 
} t_shmem;

static inline t_float min(t_float x1,t_float x2)
{
	if (x1 <= x2) {
		return x1;
	} else {
		return x2;
	}
}

int shmem_set_tab(t_shmem *x, t_symbol *table, int src_offset, int dest_offset, int size)
{
	int npoints, i, index_max;
	t_garray *a;
    t_word *vec;

	i=0;
	t_symbol *s = table;
	if (!(a = (t_garray *)pd_findbyclass(s, garray_class)))
		pd_error(x, "%s: no such array", s->s_name);
	else if (!garray_getfloatwords(a, &npoints, &vec))
		pd_error(x, "%s: bad template for tabread", s->s_name);
	else {
		index_max = min(x->segment_size-dest_offset, npoints-src_offset);
		index_max = min(index_max, size);
		for (i=0; i < index_max; i++)
			x->share_memory[i+dest_offset] = vec[i+src_offset].w_float;
	}
	// post("copied=%d", i);
	return(i);
}

void shmem_set(t_shmem *x, t_symbol *unused, int argc, t_atom *argv)
{
    int i, j, index_max, shmem_offset, array_offset, size;

	if (argc < 1) {
		pd_error(x, "shmem usage : [memset table_name [table_name []]< or [memset src_offset data [dest_offset]< (data can be a float, a list, or a table name)");
		return;
	}

	if (argv[0].a_type == A_SYMBOL) {
		i = 0;
		j = 0;
		while (argv[i].a_type == A_SYMBOL) {
			j += shmem_set_tab(x, atom_getsymbolarg(i,argc,argv), 0, j, x->segment_size);
			i++;
		}
	}
	else if ((argc > 1) && (argv[0].a_type == A_FLOAT) ) {
		shmem_offset = atom_getfloatarg(0,argc,argv);
		if (shmem_offset < 0) shmem_offset=0;

		if (argv[1].a_type == A_SYMBOL) { // argument is an arrayname
			array_offset = 0;
			size = x->segment_size;
			if ((argc > 2) && (argv[2].a_type == A_FLOAT))
				array_offset = atom_getfloatarg(2,argc,argv);
			if (array_offset < 0) array_offset=0;
			if ((argc > 3) && (argv[2].a_type == A_FLOAT))
				size = atom_getfloatarg(3,argc,argv);
			shmem_set_tab(x, atom_getsymbolarg(1,argc,argv), array_offset, shmem_offset, size);
		}
		else if (argv[1].a_type == A_FLOAT) { // argument is a float
			index_max = x->segment_size - shmem_offset;
			if (index_max > argc-1) index_max = argc-1;
			for (i=0; i<index_max ; i++)
				x->share_memory[i+shmem_offset]=atom_getfloatarg(i+1, argc, argv);
		}
	}
}

int shmem_dump_tab(t_shmem *x, t_symbol *table, int src_offset, int dest_offset, int size)
{
	t_garray *a;
    t_word *vec;
    int i, index_max, vecsize;
    
    t_symbol *s = table;
    i=0;
    
    if (!(a = (t_garray *)pd_findbyclass(s, garray_class)))
        pd_error(x, "%s: no such array", s->s_name);
    else if (!garray_getfloatwords(a, &vecsize, &vec)) 
        pd_error(x, "%s: bad template for tabwrite", s->s_name);
	else { 
		
		index_max = min(x->segment_size-src_offset, vecsize-dest_offset);
		index_max=min(index_max, size);
		for (i=0; i<index_max; i++)
			vec[i+dest_offset].w_float = x->share_memory[i+src_offset];
	}	
	garray_redraw(a);

	// post("copied=%d", i);
	return(i);
}

void shmem_dump(t_shmem *x, t_symbol *unused, int argc, t_atom *argv)
{
    int i, j, shmem_offset, dest_offset, size;

	if (argc < 1) {
		pd_error(x, "shmem usage : [memdump table_name [table_name []]< or [memset src_offset table_name [dest_offset [size]]<");
		return;
	}

	if (argv[0].a_type == A_SYMBOL) {
		i = 0;
		j = 0;
		while (argv[i].a_type == A_SYMBOL) {
			j += shmem_dump_tab(x, atom_getsymbolarg(i,argc,argv), j, 0, x->segment_size);
			i++;
		}
	}
	else if ((argc > 1) && (argv[0].a_type == A_FLOAT) ) {
	   	shmem_offset = atom_getfloatarg(0,argc,argv);
		if (shmem_offset < 0) shmem_offset = 0;
		// if (shmem_offset > x->segment_size-1) i = x->segment_size-1;
		// post("i=%d", offset);

		t_symbol *s = atom_getsymbolarg(1,argc,argv);
		dest_offset = 0;
		size = x->segment_size;
		if ((argc >= 3) && ( argv[2].a_type == A_FLOAT )){
			dest_offset = atom_getfloatarg(2,argc,argv);
		}
		if ((argc >= 4) && ( argv[3].a_type == A_FLOAT )){
			size = atom_getfloatarg(3,argc,argv);
		}
		shmem_dump_tab(x, s, shmem_offset, dest_offset, size);
    }	
}

void shmem_read(t_shmem *x, t_float index)
{
    int shmem_offset;
	
	shmem_offset = index;
	if (shmem_offset < 0) shmem_offset = 0;
	if (shmem_offset > x->segment_size-1) shmem_offset = x->segment_size-1;
	// post("i=%d", offset);	
	outlet_float(x->x_obj.ob_outlet, x->share_memory[shmem_offset]);
}

t_class *shmem_class;

void *shmem_new( t_floatarg id,  t_floatarg size)
{  
    struct shmid_ds shmbuffer; 
    // post ("id, size: %f, %f", id, size); 
    t_shmem *x = (t_shmem *)pd_new(shmem_class);

    x->segment_size = (int)size;
    x->segment_id  =  shmget  ((int)id,  sizeof(t_float)*x->segment_size, 
        IPC_CREAT | S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH); 
    if(x->segment_id>0) {
        x->share_memory = (t_float*) shmat (x->segment_id, 0, 0); 
        // post("shmem memory attached at address %p\n", x->share_memory); 

        shmctl (x->segment_id, IPC_STAT, &shmbuffer); 
        // post ("segment size: %d\n", shmbuffer.shm_segsz); 

	    if ((int)shmbuffer.shm_segsz < (int)sizeof(t_float)*x->segment_size) {
	        // there was a problem, set object meme size to 0
	        error("could not allocate shmem memory Id : %d, size %d", (int)id,  x->segment_size );
	        x->segment_size = 0;
   		}
	}
	else {
		error("could not allocate shmem memory Id : %d, size %d", (int)id,  x->segment_size );
        x->segment_size = 0;
	}

    outlet_new(&x->x_obj, 0);
    return (void *)x;
}

void shmem_free(t_shmem *x)
{
	shmdt (x->share_memory);
	shmctl (x->segment_id, IPC_RMID, 0); 
}

void shmem_clear(t_shmem *x)
{
	int i;
	for (i=0; i<x->segment_size; i++)
		x->share_memory[i] = 0;
}

void shmem_setup(void)
{
    shmem_class = class_new(gensym("shmem"), (t_newmethod)shmem_new, (t_method)shmem_free,
        sizeof(t_shmem), 0, A_DEFFLOAT, A_DEFFLOAT, 0);
    class_addmethod(shmem_class, (t_method)shmem_set, gensym("memset"), A_GIMME, 0);
    class_addmethod(shmem_class, (t_method)shmem_dump, gensym("memdump"), A_GIMME, 0);
    class_addmethod(shmem_class, (t_method)shmem_clear, gensym("memclear"), 0);
    class_addmethod(shmem_class, (t_method)shmem_read, gensym("memread"),A_DEFFLOAT, 0);
}

