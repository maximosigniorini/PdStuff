
#MALINETTE PLUGINS
#DESCRIPTION : ce plugin tcl utilise kiosk (configuration avec le fichier kiosk cfg.), aussi il change les couleurs en mode edit, un menu add sur le popup du clic droit, la fonction triple clic qui rajoute un objet et possibilité de fleches en mode edit)


### KIOSK

# META NAME Kiosk
# META DESCRIPTION all windows in fullscreen mode
# META DESCRIPTION main window invisible
# META DESCRIPTION no keybindings
# META AUTHOR IOhannes m zmölnig <zmoelnig@iem.at>

package require Tcl 8.5
package require Tk
package require pdwindow 0.1

namespace eval ::kiosk:: {
    variable ::kiosk::config
}

## default values
set ::kiosk::config(KioskNewWindow) False
set ::kiosk::config(ShowMenu) False
set ::kiosk::config(FullScreen) False
set ::kiosk::config(HideMain) True
set ::kiosk::config(WindowTitle) "Pd KIOSK"
set ::kiosk::config(HidePopup) True
set ::kiosk::config(ScrollBars) False
set ::kiosk::config(QuitOnClose) True
set ::kiosk::config(PreventClose) True
set ::kiosk::config(Bindings) False
set ::kiosk::config(QuitBinding) True
set ::kiosk::config(GeometryMain) ""

proc ::kiosk::readconfig {{fname kiosk.cfg}} {
  if {[file exists $fname]} {
    set fp [open $fname r]
  } else {
      set fname [file join $::current_plugin_loadpath $fname]
      if {[file exists $fname]} {
          set fp [open $fname r]
      } else {
          puts "kiosk.cfg not found"
          return False
      }
  }
  while {![eof $fp]} {
      set data [gets $fp]
      if { [string is list $data ] } {
          if { [llength $data ] > 1 } {
              set ::kiosk::config([lindex $data 0]) [lindex $data 1]
          }
      }
  }


 return True
}

# this is just an empty menu
menu .kioskmenu


## KIOSkify a window
proc ::kiosk::makekiosk {mywin} {
## refuse to kioskify the main Pd window
    if { $mywin == ".pdwindow" } { return; }
#    puts "KIOSKing $mywin"

#remove menu
    if { $::kiosk::config(ShowMenu) } { } {
        $mywin configure -menu .kioskmenu; 
    }

# make fullscreen
    if { $::kiosk::config(FullScreen) } {
    	wm attributes $mywin -fullscreen 1
    }

# set the title of the window 
# (makes mostly sense in non-fullscren...)
    
if { $::kiosk::config(WindowTitle) != "" } {
        wm title $mywin $::kiosk::config(WindowTitle)
    }

# close pd if the window is closed (or no close at all)
    if { $::kiosk::config(PreventClose) } {
        # prevent WindowClose using Alt-F4 or clicking on the "x"
        wm protocol $mywin WM_DELETE_WINDOW ";"
    } {
        # if we do allow closing of windows, we might want to Quit as well
        if { $::kiosk::config(QuitOnClose) } {
            #wm protocol $mywin WM_DELETE_WINDOW "pdsend \"pd quit\""
            bind $mywin <Destroy> "pdsend \"pd quit\""
        }
    }

    set mycnv [tkcanvas_name $mywin ]

# remove all special key/mouse bindings from the window
    if { $::kiosk::config(QuitBinding) } { } {
#         bind $mycnv <Control-Key-w> {}
#         bind $mycnv <Control-Shift-Key-W> {}
#         bind all <Control-Key-w> {}
#         bind all <Control-Shift-Key-W> {}

        bind $mycnv <Control-Key-q> {}
        bind $mycnv <Control-Shift-Key-Q> {}
        bind all <Control-Key-q> {}
        bind all <Control-Shift-Key-Q> {}
    }
# remove all special key/mouse bindings from the window
    if { $::kiosk::config(Bindings) } { } {
        bindtags $mywin ""
        bindtags $mycnv "$mycnv"
# rebind ordinary keypress events
        bind $mycnv <KeyPress>         {::pd_bindings::sendkey %W 1 %K %A 0}
        bind $mycnv <KeyRelease>       {::pd_bindings::sendkey %W 0 %K %A 0}
        bind $mycnv <Shift-KeyPress>   {::pd_bindings::sendkey %W 1 %K %A 1}
        bind $mycnv <Shift-KeyRelease> {::pd_bindings::sendkey %W 0 %K %A 1}
    }
}


######################################

## read the default configuration file "kiosk.cfg"
::kiosk::readconfig 


###### do some global KIOSK-settings

## set the geometry of the Pd window
if { $::kiosk::config(GeometryMain) != "" } {
    wm geometry .pdwindow =$::kiosk::config(GeometryMain)
}
## hide the Pd window
if { $::kiosk::config(HideMain) } {
    set ::stderr 1 
    wm state .pdwindow withdraw
}

## don't show popup menu on right-click
if { $::kiosk::config(HidePopup) }  {
 proc ::pdtk_canvas::pdtk_canvas_popup {mytoplevel xcanvas ycanvas hasproperties hasopen} { }
}

if { $::kiosk::config(ScrollBars) } { } {
    proc ::pdtk_canvas::pdtk_canvas_getscroll {tkcanvas} { }
}

# do the KIOSK-setting per existing window (those windows loaded at startup)
foreach kioskwin [array names ::loaded] { 
    ::kiosk::makekiosk $kioskwin 
}

# do the KIOSKification for newly created windows as well
if { $::kiosk::config(KioskNewWindow) }  {
 ## not the most elegant way: KIOSKifying each window as it get's focus
 bind PatchWindow <FocusIn> "+::kiosk::makekiosk %W"

}

pdtk_post "loaded: Malinette Tcl-guiplugin 0.01\n"

###############################################################
################### TCL custom ############################
################################################

namespace eval ::editmode_look {
    # array of the original background colors for each window
    array set original_color {}
}

proc ::editmode_look::set_cords_by_editmode {mytoplevel} {
    variable original_color
    if {$mytoplevel eq ".pdwindow"} {return}
    set tkcanvas [tkcanvas_name $mytoplevel]
    # if the mytoplevel sent to us doesn't currently have a window, silently quit
    if { ! [winfo exists $mytoplevel] } {return}
    # if the array doesn't have this instance, get the current color
    if {[array get original_color $mytoplevel] eq ""} {
        set original_color($mytoplevel) [$tkcanvas cget -background]
    }


#### EDIT MODE ####
    if {$::editmode($mytoplevel) == 1} {
        $tkcanvas itemconfigure graph -fill black
        $tkcanvas itemconfigure array -fill black
        $tkcanvas itemconfigure array -activefill orange
        $tkcanvas itemconfigure label -fill black
        #$tkcanvas itemconfigure msg -activefill orange
        #$tkcanvas itemconfigure atom -activefill orange
        $tkcanvas itemconfigure cord -fill "#888888"
        $tkcanvas itemconfigure {inlet || outlet} -outline orange
        $tkcanvas raise {inlet || outlet || cord}
        # store the background color, in case its been changed
        set original_color($mytoplevel) [$tkcanvas cget -background]
        $tkcanvas configure -background "#FFFFFF"
    } else {
#### ACTION MODE ####
        $tkcanvas itemconfigure graph -fill grey 
        $tkcanvas itemconfigure array -fill black
        $tkcanvas itemconfigure array -activefill red
        $tkcanvas itemconfigure label -fill "#777777"
        #$tkcanvas itemconfigure msg -activefill orange
        #$tkcanvas itemconfigure atom -activefill orange
        $tkcanvas itemconfigure cord -fill "#D8D8D8"			
        $tkcanvas itemconfigure {inlet || outlet} -outline grey
        #EFFACE LES SORTIES ET ENTREES
        #$tkcanvas lower {inlet || outlet || cord}
        $tkcanvas configure -background $original_color($mytoplevel)
    }
}

bind PatchWindow <<EditMode>> {+::editmode_look::set_cords_by_editmode %W}
bind PatchWindow <<Loaded>> {+::editmode_look::set_cords_by_editmode %W}

###### FLECHES :::  this plugin adds arrowheads to the ends of cords when in editmode in
# order to show the direction that the messages are flowing

proc add_arrows_to_cords {mytoplevel} {
    if { ! [winfo exists $mytoplevel] } {return}
    if {$mytoplevel eq ".pdwindow"} {return}
    set tkcanvas [tkcanvas_name $mytoplevel]
    if {$::editmode($mytoplevel) == 1} {
		#Decomment to active arrows
		#$tkcanvas itemconfigure cord -arrow last
        $tkcanvas itemconfigure cord -arrow none
    } else {
        $tkcanvas itemconfigure cord -arrow none
    }
}

bind PatchWindow <<EditMode>> {+add_arrows_to_cords %W}


############ TRIPLE CLIC = creation objet :(uncomment the lines below if u want to activate :)
###proc process_tripleclick {window} {
###set mytoplevel [winfo toplevel $window]
###if {[winfo class $mytoplevel] == "PatchWindow" && $::editmode($mytoplevel)} {
###::pd_connect::pdsend "$mytoplevel obj"
###}
###}
###bind all <Triple-ButtonRelease-1> {process_tripleclick %W}


###### MENU SUR CLIC DROIT : for more info: http://tcl.tk/man/tcl8.5/TkCmd/menu.htm
#.menubar.put clone .popup.create normal
#.popup insert 0 cascade -label [_ "Put"] -menu .popup.create
#.popup.create configure -tearoff 1


###### CATEGORIE DANS POPUP #######
# This plug generates a menu tree for selecting objects from a single
# structured textfile.  The format of the textfile is nested Tcl lists
# defined using {} brackets.

package require pd_menus

namespace eval category_menu {
}

proc category_menu::load_menutree {} {
    # load object -> tags mapping from file in Pd's path
    set testfile [file join $::current_plugin_loadpath menutree.txt]
    set f [open $testfile]
    set menutree [read $f]
#    set menutree [regsub -all {([\{\s])\-([\s\}])} [read $f] {\1\\\\-\2}]
    close $f
    unset f        
    return $menutree
}

proc category_menu::create {mymenu} {
    set menutree [load_menutree]
    $mymenu add separator
    foreach categorylist $menutree {
        set category [lindex $categorylist 0]
        menu $mymenu.$category
        $mymenu add cascade -label $category -menu $mymenu.$category
        foreach subcategorylist [lrange $categorylist 1 end] {
            set subcategory [lindex $subcategorylist 0]
            menu $mymenu.$category.$subcategory
            $mymenu.$category add cascade -label $subcategory -menu $mymenu.$category.$subcategory
            foreach item [lindex $subcategorylist end] {
                # replace the normal dash with a Unicode minus so that Tcl doesn't
                # interpret the dash in the -label to make it a separator
                $mymenu.$category.$subcategory add command \
                    -label [regsub -all {^\-$} $item {?}] \
                    -command \
                    "pdsend \"\$::focused_window obj \$::popup_xcanvas \$::popup_ycanvas $item\""
            }
        }
    }
}

category_menu::create .popup
