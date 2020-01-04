#include "m_pd.h"

#define max(a,b) ( ((a) > (b)) ? (a) : (b) ) 
#define min(a,b) ( ((a) < (b)) ? (a) : (b) ) 

#define mix(a,b,x) (x*b + (1-x)*a)

typedef struct rendu_egregore
{
  t_object x_ob;
  t_float dataX[4][377], dataY[4][377];
  t_int t, tm1,tm2,tm3; // time index
  t_float points[4];
} t_rendu_egregore;

void rendu_egregore_color(t_rendu_egregore *x, t_symbol *dstX, t_symbol *dstY)
{
    t_garray *a;
    t_word *vec;
	int i, j, vecsize;

// compute dstX (color Red)
	if (!(a = (t_garray *)pd_findbyclass(dstX, garray_class)))
		pd_error(x, "%s: no such array", dstX->s_name);
	else if (!garray_getfloatwords(a, &vecsize, &vec))
		pd_error(x, "%s: bad template for tabwrite", dstX->s_name);
	else
	{
		for (i=0; i < 377 ; i++)
		{				
			vec[21*i].w_float = 0;
			for(j=1; j< 21; j++)
			{
				vec[21*i+j].w_float = 1;
			}
            vec[21*(i+1)].w_float = 0;
		}
		garray_redraw(a);
	}

// compute dstY (color Green and blue)
	if (!(a = (t_garray *)pd_findbyclass(dstY, garray_class)))
		pd_error(x, "%s: no such array", dstY->s_name);
	else if (!garray_getfloatwords(a, &vecsize, &vec))
		pd_error(x, "%s: bad template for tabwrite", dstY->s_name);
	else
	{
		for (i=0; i < 377 ; i++)
		{				
			vec[21*i].w_float = 0;
			for(j=1; j< 21; j++)
			{
				if (i != 147)
					vec[21*i+j].w_float = 1;
				else
					vec[21*i+j].w_float = 0;
			}
            vec[21*(i+1)].w_float = 0;
		}
		garray_redraw(a);
	}
}

void rendu_egregore_update(t_rendu_egregore *x, t_symbol *srcX, t_symbol *srcY, t_symbol *dstX, t_symbol *dstY)
{
    t_garray *a;
    t_word *vec;
	int taille_max, i, j, vecsize;
	t_float k, tmp1, tmp2, tmp3;

// increase time
	x->t = (x->t + 1) % 4;
	x->tm1 = (x->t + 3) % 4;
	x->tm2 = (x->t + 2) % 4;
	x->tm3 = (x->t + 1) % 4;

// copy srxX to dataX[t]
	if (!(a = (t_garray *)pd_findbyclass(srcX, garray_class)))
		pd_error(x, "%s: no such array", srcX->s_name);
	else if (!garray_getfloatwords(a, &vecsize, &vec))
		pd_error(x, "%s: bad template for tabread", srcX->s_name);
	else 
    {
		taille_max = min(377,vecsize);
		// post("i=%d", index_max);
		for (i=0; i<taille_max; i++)
			x->dataX[x->t][i] = vec[i].w_float;
    }

// copy srxY to dataY[t]
	if (!(a = (t_garray *)pd_findbyclass(srcY, garray_class)))
		pd_error(x, "%s: no such array", srcY->s_name);
	else if (!garray_getfloatwords(a, &vecsize, &vec))
		pd_error(x, "%s: bad template for tabread", srcY->s_name);
	else 
    {
		taille_max = min(377,vecsize);
		// post("i=%d", index_max);
		for (i=0; i<taille_max; i++)
			x->dataY[x->t][i] = vec[i].w_float;
    }

// compute dstX
	if (!(a = (t_garray *)pd_findbyclass(dstX, garray_class)))
		pd_error(x, "%s: no such array", dstX->s_name);
	else if (!garray_getfloatwords(a, &vecsize, &vec))
		pd_error(x, "%s: bad template for tabwrite", dstX->s_name);
	else
	{
		for (i=0; i < 377 ; i++)
		{
			for(j=0; j< 21; j++)
			{
				k = (float)j/21;
				// compute a besier curve
				tmp1 = mix(x->dataX[x->t  ][i],x->dataX[x->tm1][i],k);
				tmp2 = mix(x->dataX[x->tm1][i],x->dataX[x->tm2][i],k);
				tmp3 = mix(x->dataX[x->tm2][i],x->dataX[x->tm3][i],k);

				tmp1 = mix(tmp1, tmp2,k);
				tmp2 = mix(tmp2, tmp3,k);

				tmp1 = mix(tmp1, tmp2,k);
				vec[21*i+j].w_float = tmp1;
			}
		}
		garray_redraw(a);
	}

// compute dstY
	if (!(a = (t_garray *)pd_findbyclass(dstY, garray_class)))
		pd_error(x, "%s: no such array", dstY->s_name);
	else if (!garray_getfloatwords(a, &vecsize, &vec))
		pd_error(x, "%s: bad template for tabwrite", dstY->s_name);
	else
	{
		for (i=0; i < 377 ; i++)
		{
			for(j=0; j< 21; j++)
			{
				k = (float)j/21;
				// compute a besier curve
				tmp1 = mix(x->dataY[x->t  ][i],x->dataY[x->tm1][i],k);
				tmp2 = mix(x->dataY[x->tm1][i],x->dataY[x->tm2][i],k);
				tmp3 = mix(x->dataY[x->tm2][i],x->dataY[x->tm3][i],k);

				tmp1 = mix(tmp1, tmp2,k);
				tmp2 = mix(tmp2, tmp3,k);

				tmp1 = mix(tmp1, tmp2,k);
				vec[21*i+j].w_float = tmp1;
			}
		}
		garray_redraw(a);
	}
}

t_class *rendu_egregore_class;

void *rendu_egregore_new(void)
{
    t_rendu_egregore *x = (t_rendu_egregore *)pd_new(rendu_egregore_class);
	x->t = 3;
	x->tm1 = 2;
	x->tm2 = 1;
	x->tm3 = 0;

    return (void *)x;
}

void rendu_egregore_setup(void)
{
    post("rendu_egregore : loading external");
    rendu_egregore_class = class_new(gensym("rendu_egregore"), (t_newmethod)rendu_egregore_new, 0, sizeof(t_rendu_egregore), 0, 0);
    class_addmethod(rendu_egregore_class, (t_method)rendu_egregore_update, gensym("update"), A_DEFSYMBOL, A_DEFSYMBOL, A_DEFSYMBOL, A_DEFSYMBOL, 0);
    class_addmethod(rendu_egregore_class, (t_method)rendu_egregore_color, gensym("color"), A_DEFSYMBOL, A_DEFSYMBOL, 0);
}

