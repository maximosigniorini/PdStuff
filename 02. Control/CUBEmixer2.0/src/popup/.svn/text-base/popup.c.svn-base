/* Popup menu widget for PD                                              *
* Based on button from GGEE by Guenter Geiger                           *
* Copyright Ben Bogart 2004 ben@ekran.org                               * 

  * This program is distributed under the terms of the GNU General Public *
  * License                                                               *
  
    * popup is free software; you can redistribute it and/or modify         *
    * it under the terms of the GNU General Public License as published by  *
    * the Free Software Foundation; either version 2 of the License, or     *
    * (at your option) any later version.                                   *
    
      * popup is distributed in the hope that it will be useful,              *
      * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
      * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
* GNU General Public License for more details.                          */


/* JMZ changelog
* - only 1 out/inlet
*   inlet2 ---> symbolmethod of inlet1
*   outlet2 --> outlet1 outputs now a list "<index> <name>"
*
* - omit the bang-output
* - removed "draw_hanlde"
* - changed the DEBUG thingy
*/

/* TM changed DEBUG to //post("DEBUG
moved popup_widgetbehavior methods to setup routine
variable visible into first line of routine popup_set
*/



#include <m_pd.h>
#include <g_canvas.h>
#include <stdio.h>
#include <string.h>


#ifdef NT
#pragma warning( disable : 4244 )
#pragma warning( disable : 4305 )
#endif

#if PD_MINOR_VERSION < 37
#define t_rtext t_text
#endif

#ifndef IOWIDTH 
#define IOWIDTH 4
#endif

#define MAX_OPTIONS 100

typedef struct _popup
{
  t_object    x_obj;
  t_glist    *x_glist;
  t_symbol   *x_sym;
  int         x_height;
  int         x_width;
  int         x_selected_option_index;
  int         x_num_options;   
  t_symbol   *x_bkgd_colour;
  t_symbol   *x_top_entry_name;
  t_symbol  **x_options;
  int         x_max_options;
  int         x_initialized; /* 1 when we are allowed to draw, 0 otherwise */
  int         x_disabled; /* when disabled, graphical chosing is prohibited */
  int         x_column_break_height; /*  */
} t_popup;

/* widget helper functions */

/* Append " x " to the following line to show debugging messages */


t_widgetbehavior popup_widgetbehavior;

static void draw_inlets(t_popup *x, t_glist *glist, int firsttime, int nin, int nout)
{
  /* outlets */
  int n = nin;
  int nplus, i;
  nplus = (n == 1 ? 1 : n-1);
  //post("DEBUG: draw inlet");
  for (i = 0; i < n; i++)
  {
    int onset = text_xpix(&x->x_obj, glist) + (x->x_width - IOWIDTH) * i / nplus;
    if (firsttime)
      sys_vgui(".x%x.c create rectangle %d %d %d %d -tags {%xo%d %xo}\n",
      glist_getcanvas(glist),
      onset, text_ypix(&x->x_obj, glist) + x->x_height,
      onset + IOWIDTH, text_ypix(&x->x_obj, glist) + x->x_height+1,
      x, i, x);
    else
      sys_vgui(".x%x.c coords %xo%d %d %d %d %d\n",
      glist_getcanvas(glist), x, i,
      onset, text_ypix(&x->x_obj, glist) + x->x_height,
      onset + IOWIDTH, text_ypix(&x->x_obj, glist) + x->x_height+1);
  }
  /* inlets */
  n = nout; 
  nplus = (n == 1 ? 1 : n-1);
  for (i = 0; i < n; i++)
  {
    int onset = text_xpix(&x->x_obj, glist) + (x->x_width - IOWIDTH) * i / nplus;
    if (firsttime)
      sys_vgui(".x%x.c create rectangle %d %d %d %d -tags {%xi%d %xi}\n",
      glist_getcanvas(glist),
      onset, text_ypix(&x->x_obj, glist)-2,
      onset + IOWIDTH, text_ypix(&x->x_obj, glist)-1,
      x, i, x);
    else
      sys_vgui(".x%x.c coords %xi%d %d %d %d %d\n",
      glist_getcanvas(glist), x, i,
      onset, text_ypix(&x->x_obj, glist),
      onset + IOWIDTH, text_ypix(&x->x_obj, glist)-1);
    
  }
  //post("DEBUG: draw inlet end");
}


static void create_widget(t_popup *x, t_glist *glist)
{
  //post("DEBUG: create_widget start");
  
  char text[MAXPDSTRING];
  int len,i,j;
  t_symbol *temp_name;
  t_canvas *canvas=glist_getcanvas(glist);
  
  /* Create menubutton and empty menu widget -- maybe the menu should be created elseware?*/
  
  /* draw using the last name if it was selected otherwise use default name. */
  if(x->x_selected_option_index < 0)
  {
    temp_name = x->x_top_entry_name;
  } else {
    temp_name = x->x_options[x->x_selected_option_index];
  }
  
  /* Seems we have to delete the widget in case it already exists (Provided by Guenter)*/
  if(x->x_initialized)
  {
    sys_vgui("destroy .x%x.c.s%x\n",glist_getcanvas(glist),x);
    
    sys_vgui("set %xw .x%x.c.s%x ; menubutton $%xw -relief raised -background \"%s\" -text \"%s\" -direction flush -menu $%xw.menu ; menu $%xw.menu -tearoff 0\n",
      x, canvas, x, x, x->x_bkgd_colour->s_name, temp_name->s_name, x, x);
    
    for(i=0 ; i<x->x_num_options ; i++)
    {
      j = i % x->x_column_break_height;
      if(j == 0)
        j = 1;
      else
        j = 0;
      if(i == 0)
        j = 0;
      sys_vgui(".x%x.c.s%x.menu add command -columnbreak %d -label \"%s\" -command {.x%x.c.s%x configure -text \"%s\" ; popup_sel%x \"%d\"} \n", 
        canvas, x, j, x->x_options[i]->s_name, canvas, x, x->x_options[i]->s_name, x, i);
    }
  }
  
  //post("DEBUG: id: .x%x.c.s%x", canvas, x);
  //post("DEBUG: create_widget end");
}

static void popup_drawme(t_popup *x, t_glist *glist, int firsttime)
{
  t_canvas *canvas=glist_getcanvas(glist);
  //post("DEBUG: drawme start");
  
  /* by drawing, we "initialize" the popup */
  x->x_initialized=1;
  
  //post("DEBUG: drawme %d",firsttime);
  if (firsttime) {
    //post("DEBUG: glist %x canvas %x",x->x_glist,canvas);
    create_widget(x,glist);        
    x->x_glist = canvas;
    sys_vgui(".x%x.c create window %d %d -width %d -height %d -anchor nw -window .x%x.c.s%x -tags %xS\n", 
      canvas,text_xpix(&x->x_obj, glist), text_ypix(&x->x_obj, glist), x->x_width, x->x_height, x->x_glist,x,x);
    
  }     
  else {
    sys_vgui(".x%x.c coords %xS %d %d\n",
      canvas, x,
      text_xpix(&x->x_obj, glist), text_ypix(&x->x_obj, glist));
  }
  draw_inlets(x, glist, firsttime, 1,1);
  sys_vgui(".x%x.c.s%x configure -state \"%s\"\n", canvas, x, x->x_disabled?"disabled":"active");
  
  
  // Output a bang to first outlet when we're ready to receive float messages the first time!. 
  // Too bad this is NOT always the first time... window shading makes the bang go out again. :(
  
  //post("DEBUG: drawme end");
}


static void popup_erase(t_popup* x,t_glist* glist)
{
  int n;
  
  //post("DEBUG: erase start");
  if(x->x_initialized){
    sys_vgui("destroy .x%x.c.s%x\n",glist_getcanvas(glist),x);
    
    sys_vgui(".x%x.c delete %xS\n",glist_getcanvas(glist), x);
    
    /* inlets and outlets */
    
    sys_vgui(".x%x.c delete %xi\n",glist_getcanvas(glist),x); /* Added tag for all inlets of one instance */
    sys_vgui(".x%x.c delete %xo\n",glist_getcanvas(glist),x); /* Added tag for all outlets of one instance */
    sys_vgui(".x%x.c delete  %xhandle\n",glist_getcanvas(glist),x,0);
  }
  
  //post("DEBUG: erase end");
}



/* ------------------------ popup widgetbehaviour----------------------------- */


static void popup_getrect(t_gobj *z, t_glist *owner,
                          int *xp1, int *yp1, int *xp2, int *yp2)
{
  //post("DEBUG: getrect start");
  
  int width, height;
  t_popup* s = (t_popup*)z;
  
  width = s->x_width;
  height = s->x_height+2;
  *xp1 = text_xpix(&s->x_obj, owner);
  *yp1 = text_ypix(&s->x_obj, owner) - 1;
  *xp2 = text_xpix(&s->x_obj, owner) + width;
  *yp2 = text_ypix(&s->x_obj, owner) + height;
  
  //post("DEBUG: getrect end");
}

static void popup_displace(t_gobj *z, t_glist *glist,
                           int dx, int dy)
{
  t_popup *x = (t_popup *)z;
  //post("DEBUG: displace start");
  x->x_obj.te_xpix += dx;
  x->x_obj.te_ypix += dy;
  if (glist_isvisible(glist))
  {
    if(x->x_initialized)sys_vgui(".x%x.c coords %xSEL %d %d %d %d\n",
      glist_getcanvas(glist), x,
      text_xpix(&x->x_obj, glist), text_ypix(&x->x_obj, glist)-1,
      text_xpix(&x->x_obj, glist) + x->x_width, text_ypix(&x->x_obj, glist) + x->x_height);
    
    popup_drawme(x, glist, 0);
    canvas_fixlinesfor(glist_getcanvas(glist),(t_text*) x);
  }
  //post("DEBUG: displace end");
}

static void popup_select(t_gobj *z, t_glist *glist, int state)
{
  //post("DEBUG: select start");
  
  t_popup *x = (t_popup *)z;
  if(x->x_initialized){
    if (state) {
    sys_vgui(".x%x.c create rectangle \
      %d %d %d %d -tags %xSEL -outline blue\n",
      glist_getcanvas(glist),
      text_xpix(&x->x_obj, glist), text_ypix(&x->x_obj, glist)-1,
      text_xpix(&x->x_obj, glist) + x->x_width, text_ypix(&x->x_obj, glist) + x->x_height,
      x);
    }
    else {
      sys_vgui(".x%x.c delete %xSEL\n",
        glist_getcanvas(glist), x);
    }
  }
  
  //post("DEBUG: select end");
}

static void popup_activate(t_gobj *z, t_glist *glist, int state)
{
  //post("DEBUG: activate commented out!");
  
  /* What does this do, why commented out? 
  t_text *x = (t_text *)z;
  t_rtext *y = glist_findrtext(glist, x);
  if (z->g_pd != gatom_class) rtext_activate(y, state);*/
}

static void popup_delete(t_gobj *z, t_glist *glist)
{
  //post("DEBUG: delete start");
  
  t_text *x = (t_text *)z;
  //canvas_deletelinesfor(glist_getcanvas(glist), x);
  canvas_deletelinesfor(glist, x);
  
  //post("DEBUG: delete end");
}


static void popup_vis(t_gobj *z, t_glist *glist, int vis)
{
  t_popup* s = (t_popup*)z;
  t_rtext *y;
  //post("DEBUG: vis start");
  //post("DEBUG: vis: %d",vis);
  if (vis) {
#ifdef PD_MINOR_VERSION
    y = (t_rtext *) rtext_new(glist, (t_text *)z);
#else
    y = (t_rtext *) rtext_new(glist, (t_text *)z,0,0);
#endif
    popup_drawme(s, glist, 1);
  }
  else {
    y = glist_findrtext(glist, (t_text *)z);
    popup_erase(s,glist);
    rtext_free(y);
  }
  
  //post("DEBUG: vis end");
}

static void popup_save(t_gobj *z, t_binbuf *b);

static void popup_output(t_popup* x, t_floatarg popup_index)
{
  //post("DEBUG: output start");
  t_atom ap[2];
  SETFLOAT (ap,  (t_float)popup_index);
  SETSYMBOL(ap+1,x->x_options[(int)popup_index]);
  
  x->x_selected_option_index = popup_index;
  outlet_list(x->x_obj.ob_outlet, &s_list, 2, ap);
}


static void popup_save(t_gobj *z, t_binbuf *b)
{
  //post("DEBUG: save start");
  
  int i;
  t_popup *x = (t_popup *)z;
  
  binbuf_addv(b, "ssiisiiss", gensym("#X"),gensym("obj"),
    x->x_obj.te_xpix, x->x_obj.te_ypix ,  
    gensym("popup"), x->x_width, x->x_height, x->x_bkgd_colour, x->x_top_entry_name);
  /* Loop for menu items */
  for(i=0 ; i<x->x_num_options ; i++)
  {
    binbuf_addv(b, "s", x->x_options[i]);
  }
  binbuf_addv(b, ";");
  
  //post("DEBUG: save end");
}

/* function to change the popup's menu */
static void popup_options(t_popup* x, t_symbol *s, int argc, t_atom *argv)
{
  //post("DEBUG: options start");
  
  int i, j;
  int visible=(x->x_glist)?glist_isvisible(x->x_glist):0;
  
  x->x_num_options = argc;
  
  /* delete old menu items */
  if(visible)sys_vgui(".x%x.c.s%x.menu delete 0 end \n", x->x_glist, x);
  
  if(argc > x->x_max_options)
  {/* resize the options-array */
    if(x->x_options)
      freebytes(x->x_options, sizeof(t_symbol*)*x->x_max_options);
    x->x_max_options = argc;
    x->x_options = (t_symbol**)getbytes(sizeof(t_symbol*)*x->x_max_options);
  }
  
  for(i=0 ; i<argc ; i++)
  {
    j = i % x->x_column_break_height;
    if(j == 0)
      j = 1;
    else
      j = 0;
    if(i == 0)
      j = 0;
    x->x_options[i] = atom_getsymbol(argv+i);
    if(visible)sys_vgui(".x%x.c.s%x.menu add command -columnbreak %d -label \"%s\" -command {.x%x.c.s%x configure -text \"%s\" ; popup_sel%x \"%d\"} \n", 
      x->x_glist, x, j, x->x_options[i]->s_name, x->x_glist, x, x->x_options[i]->s_name, x, i);
  }
  
  //post("DEBUG: options end");
}

static void popup_size(t_popup* x, t_symbol *s, int argc, t_atom *argv)
{
  int h=20, w=100;
  
  if((argc == 1)&&(argv[0].a_type == A_FLOAT))
  {
    w = (int)atom_getintarg(0, argc, argv);
    h = 25;
  }
  else if((argc > 1)&&(argv[0].a_type == A_FLOAT)&&(argv[1].a_type == A_FLOAT))
  {
    w = (int)atom_getintarg(0, argc, argv);
    h = (int)atom_getintarg(1, argc, argv);
  }

  if(w < 1)
    w = 1;
  if(h < 1)
    h = 1;

  x->x_width = w;
  x->x_height = h;
}

/* function to change colour of popup background */
static void popup_bgcolour(t_popup* x, t_symbol* col)
{
  int visible=(x->x_glist)?glist_isvisible(x->x_glist):0;
  //post("DEBUG: bgcolour start");
  
  x->x_bkgd_colour = col;
  if(visible)sys_vgui(".x%x.c.s%x configure -background \"%s\"\n", x->x_glist, x, col->s_name);
}

/* Function to change name of popup */
static void popup_name(t_popup* x, t_symbol *name)
{
  int visible=(x->x_glist)?glist_isvisible(x->x_glist):0;
  //post("DEBUG: name start");
  
  x->x_top_entry_name = name;
  if(visible)sys_vgui(".x%x.c.s%x configure -text \"%s\"\n", x->x_glist, x, name->s_name);
}



static void popup_column_break_height(t_popup* x, t_floatarg cbh)
{
  int i=(int)cbh;

  if(i < 1)
    i = 1;
  x->x_column_break_height = i;
}


/* Function to select a menu option by inlet */
static void popup_iselect(t_popup* x, t_floatarg item)
{
  //post("DEBUG: iselect start");
  int visible=(x->x_glist)?glist_isvisible(x->x_glist):0;
  
  int i=(int)item;
  if( i<x->x_num_options && i>=0)
  {
    if(visible)sys_vgui(".x%x.c.s%x configure -text \"%s\" ; popup_sel%x \"%d\" \n",
      glist_getcanvas(x->x_glist), x, x->x_options[i]->s_name,x, i);
    else popup_output(x, i);
    
  } else {
    pd_error(x, "popup: Valid menu selections are from %d to %d\npopup: You entered %d.", 0, x->x_num_options-1, i);
  }
  
  //post("DEBUG: iselect end");
}

/* Function to choose value via symbol name */
static void popup_symselect(t_popup* x, t_symbol *s)
{
  int i,match=0;
  int visible=(x->x_glist)?glist_isvisible(x->x_glist):0;
  
  /* Compare inlet symbol to each option */
  for(i=0; i<x->x_num_options; i++)
  {
    if(x->x_options[i]->s_name == s->s_name)
    {
      if(visible)sys_vgui(".x%x.c.s%x configure -text \"%s\" ; popup_sel%x \"%d\" \n",
        glist_getcanvas(x->x_glist), x, x->x_options[i]->s_name,x, i);
      else popup_output(x, i);
      match = 1;
      break;
    }
  }
  
  if(match != 1)
    post("popup: '%s' is not an available option.", s->s_name);
  
}

/* Function to choose value via name/index but without outputting it*/
static void popup_set(t_popup* x, t_symbol *S, int argc, t_atom*argv)
{
  int visible;

  if(!argc)
    return;

  visible=(x->x_glist)?glist_isvisible(x->x_glist):0;
  
  if(argv->a_type==A_FLOAT)
  {
    int i=atom_getint(argv);
    if( i<x->x_num_options && i>=0)
    {
      x->x_selected_option_index = i;
      if(visible)
        sys_vgui(".x%x.c.s%x configure -text \"%s\"\n",
        glist_getcanvas(x->x_glist), x, x->x_options[i]->s_name);
    } else {
      pd_error(x, "popup: Valid menu selections are from %d to %d\npopup: You entered %d.", 0, x->x_num_options-1, i);
    }
  } else if(argv->a_type==A_SYMBOL)
  {
    int i;
    t_symbol*s=atom_getsymbol(argv);
    /* Compare inlet symbol to each option */
    for(i=0; i<x->x_num_options; i++)
    {
      if(x->x_options[i]->s_name == s->s_name)
      {
        x->x_selected_option_index = i;
        if(visible)sys_vgui(".x%x.c.s%x configure -text \"%s\"\n",
          glist_getcanvas(x->x_glist), x, x->x_options[i]->s_name);
        return;
      }
    }
    post("popup: '%s' is not an available option.", s->s_name);
  } else 
  {
    pd_error(x, "popup: can only 'set' symbols or floats");
  }
}

/* Function to append symbols to popup list */
static void popup_append(t_popup* x, t_symbol *s, int argc, t_atom *argv)
{
  //post("DEBUG: append start");
  
  int i, j, new_mum_options;
  int visible=(x->x_glist)?glist_isvisible(x->x_glist):0;
  
  new_mum_options = x->x_num_options + argc;
  if(new_mum_options > x->x_max_options)
  {
    t_symbol **mem_beg_options;
    int new_max_options = 2 * new_mum_options;
    //post("DEBUG: resizing options");
    mem_beg_options = (t_symbol **)getbytes(sizeof(t_symbol*)*new_max_options);
    if(mem_beg_options)
    {
      memcpy(mem_beg_options, x->x_options, sizeof(t_symbol*)*x->x_max_options);
      freebytes(x->x_options, sizeof(t_symbol*)*x->x_max_options);
      x->x_max_options = new_max_options;
      x->x_options = mem_beg_options;
    }
    else
    {
      error("popup: no memory for options");
      return;
    }
  }
  
  for(i=x->x_num_options ; i<new_mum_options ; i++)
  {
    j = i % x->x_column_break_height;
    if(j == 0)
      j = 1;
    else
      j = 0;
    if(i == 0)
      j = 0;
    x->x_options[i] = atom_getsymbol(argv+i-x->x_num_options);
    if(visible)sys_vgui(".x%x.c.s%x.menu add command -columnbreak %d -label \"%s\" -command {.x%x.c.s%x configure -text \"%s\" ; popup_sel%x \"%d\"} \n",
      x->x_glist, x, j, x->x_options[i]->s_name, x->x_glist, x, x->x_options[i]->s_name, x, i);
  }
  
  x->x_num_options = new_mum_options;
  
  //post("DEBUG: append end");
}

static void popup_disable(t_popup*x, t_float f){
  x->x_disabled=(f>0.f);
  if(x->x_glist && glist_isvisible(x->x_glist)){
    t_canvas *canvas=glist_getcanvas(x->x_glist);
    sys_vgui(".x%x.c.s%x configure -state \"%s\"\n", canvas, x, x->x_disabled?"disabled":"active");
  }
}



static t_class *popup_class;

static void popup_free(t_popup*x)
{
  if(x->x_options)freebytes(x->x_options, sizeof(t_symbol*)*x->x_max_options);
}


static void *popup_new(t_symbol *s, int argc, t_atom *argv)
{
  //post("DEBUG: popup new start");
  
  t_popup *x = (t_popup *)pd_new(popup_class);
  int i;
  char buf[256];
  
  x->x_glist = (t_glist*)NULL;
  x->x_selected_option_index = -1;
  x->x_max_options=MAX_OPTIONS;
  x->x_column_break_height = MAX_OPTIONS;
  x->x_width = 124;
  x->x_height = 25;
  x->x_num_options = 1; 
  x->x_bkgd_colour = gensym("#ffffff");
  x->x_top_entry_name = gensym("popup");
  x->x_initialized=0;
  x->x_disabled=0;
  x->x_num_options = argc-4;
  if(x->x_num_options > x->x_max_options)
  {
    x->x_max_options = x->x_num_options + 20;
  }
  x->x_options = (t_symbol **)getbytes(sizeof(t_symbol*)*x->x_max_options);
  x->x_options[0] = gensym("option");

  switch(argc){
  case 0: break; /* just use default values */
  case 1:
    post("popup: You must enter at least 5 arguments. Default values used.\n\nArguments:\npopup [width] [height] [colour] [name] [option-1] [option-2] ...");   
    break;
  default:
    /* Copy args into structure */    
    for(i=0 ; i<x->x_num_options ; i++)
    {
      x->x_options[i] = atom_getsymbol( argv+(i+4) );
    }
  case 4:
    x->x_top_entry_name = atom_getsymbol(argv+3);
  case 3:
    x->x_bkgd_colour = atom_getsymbol(argv+2);
  case 2:
    x->x_width =atom_getint(argv+0);
    x->x_height=atom_getint(argv+1);
    break;
  }
  
  /* Bind the recieve "popup%p" to the widget outlet*/
  sprintf(buf, "popup%p", x);
  x->x_sym = gensym(buf);
  pd_bind(&x->x_obj.ob_pd, x->x_sym);
  
  /* define proc in tcl/tk where "popup%p" is the receive, "output" is the method, and "$index" is an argument. */
  sys_vgui("proc popup_sel%x {index} {\n pd [concat popup%p output $index \\;]\n }\n", x, x);
  
  /* Add symbol inlet (hard to say how this actually works?? */
  outlet_new(&x->x_obj, &s_list);
  
  //post("DEBUG: popup new end");
  
  return(x);
}

void popup_setup(void) {  
//post("DEBUG: setup start");
  popup_class = class_new(gensym("popup"), (t_newmethod)popup_new, (t_method)popup_free,
        sizeof(t_popup),0,A_GIMME,0);
  
  class_addfloat(popup_class,  (t_method)popup_iselect);
  class_addsymbol(popup_class, (t_method)popup_symselect);
  class_addmethod(popup_class, (t_method)popup_output, gensym("output"), A_DEFFLOAT, 0);
  class_addmethod(popup_class, (t_method)popup_name, gensym("name"), A_DEFSYMBOL, 0);
  class_addmethod(popup_class, (t_method)popup_options, gensym("options"), A_GIMME, 0);
  class_addmethod(popup_class, (t_method)popup_bgcolour, gensym("bgcolour"), A_DEFSYMBOL, 0);
  class_addmethod(popup_class, (t_method)popup_append, gensym("append"), A_GIMME, 0);
  class_addmethod(popup_class, (t_method)popup_disable, gensym("disable"), A_FLOAT, 0);// jz
  class_addmethod(popup_class, (t_method)popup_set, gensym("set"), A_GIMME, 0);
  class_addmethod(popup_class, (t_method)popup_column_break_height, gensym("column_break_height"), A_DEFFLOAT, 0);
  class_addmethod(popup_class, (t_method)popup_size, gensym("size"), A_GIMME, 0);
  
  popup_widgetbehavior.w_getrectfn    = popup_getrect;
  popup_widgetbehavior.w_displacefn   = popup_displace;
  popup_widgetbehavior.w_selectfn     = popup_select;
  popup_widgetbehavior.w_activatefn   = popup_activate;
  popup_widgetbehavior.w_deletefn     = popup_delete;
  popup_widgetbehavior.w_visfn        = popup_vis;
#if PD_MINOR_VERSION < 37
  popup_widgetbehavior.w_savefn       = popup_save;
#endif
  popup_widgetbehavior.w_clickfn      = NULL;
#if PD_MINOR_VERSION < 37
  popup_widgetbehavior.w_propertiesfn = NULL;
#endif
  
  
  class_setwidget(popup_class,&popup_widgetbehavior);
#if PD_MINOR_VERSION >= 37
  class_setsavefn(popup_class,&popup_save);
#endif
  
  post("Popup v0.2 Ben Bogart.\nCVS: $Revision$ $Date$");
}
