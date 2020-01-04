#!/bin/sh
# the next line restarts using tclsh \
exec tclsh "$0" "$@"

set FORCE false

set PLUGINDIR  "plugins";
set PLUGINFILE "plugins.txt";

set GUIPATCH "GUI.pd";
set DSPPATCH "DSP.pd";

set OUT_GUIPATCH "GUI/inchan/plugin/EFF_PLUG_IN.pd";
set OUT_DSPPATCH "DSP/abs/EFF_PLUG_IN~.pd";

proc usage {} {
    upvar \#0 argv0 myname;
    puts "$myname \[-f\] \[-h\] \[\<plugindir\>\]";
    exit 1
}

proc parse_arguments {} {
    upvar \#0 FORCE force;
    upvar \#0 argv args;
    upvar \#0 PLUGINDIR pdir;
    foreach a $args {
        switch -regexp -- [string trim "$a"] {
            "^(-f|--force)$" {
                set force true;
            }
            "^(-h|--help)$" {
                usage;
            }
            default {
                set pdir "$a";
            }
        }
    }
}

proc checkPlugin {p} {
    upvar \#0 GUIPATCH GUIPATCH
    upvar \#0 DSPPATCH DSPPATCH

    set gui "$p/$GUIPATCH"
    set dsp "$p/$DSPPATCH"

    if {[file exists $gui]&&[file exists $dsp]} {
        return [file tail $p];
    }
}

proc listPlugins {d} {
    upvar \#0 GUIPATCH GUIPATCH
    set pluginlist {};
    foreach p [glob -nocomplain "$d/*/$GUIPATCH"] {
        lappend pluginlist [checkPlugin [file dirname $p]]
    }
    return "$pluginlist";
}

proc generateGUIpatch {outpatch plugins} {
    puts $outpatch "\#N canvas 0 0 450 300 10;";
    set connector 0;
    foreach plugin $plugins {
        puts $outpatch "\#X obj 60 [expr {100+25*$connector}] inchan/plugin/plugin ${plugin} \\\$1 \\\$2;"
        incr connector;
    }
}

proc generateDSPpatch {outpatch plugins} {
    puts $outpatch "\#N canvas 0 0 450 300 10;";
    puts $outpatch "\#X obj 0   0 inlet~;"
    puts $outpatch "\#X obj 0 200 outlet~;"
    puts $outpatch "\#X obj 0  50 CUBEmixer_plugin0~ \\\$0 \\\$1 \\\$2;";
    set connector 0;
    foreach plugin $plugins {
        puts $outpatch "\#X obj 60 [expr {100+25*$connector}] CUBEmixer_plugin~ \\\$0 ${plugin} \\\$1 \\\$2;"
        incr connector;
    }

    puts $outpatch "\#X connect 0 0 2 0;";
    puts $outpatch "\#X connect 2 0 1 0;";

    for {set i 0} {$i < $connector} {incr i} {
        puts $outpatch "\#X connect 0 0 [expr {3+$i}] 0;";
        puts $outpatch "\#X connect [expr {3+$i}] 0 1 0;";
    }
}

proc generatePluginsFile {outfile plugins} {
      foreach plugin $plugins {
          puts $outfile $plugin
      }  
}

parse_arguments

if {[file isdirectory "$PLUGINDIR"]} {} {
    usage
}

if { "$GUIPATCH" == "" } {
    puts "no gui-patch defined!";
    exit -2;
}

if { "$DSPPATCH" == "" } {
    puts "no dsp-patch defined!";
    exit -2;
}

set PLUGINFILE "${PLUGINDIR}/${PLUGINFILE}";
if {[file exists "${PLUGINFILE}"]} {
    if { "$FORCE" } { } {
        puts "${PLUGINFILE} already exists"
        exit -4
    }
}

#checkPlugin "plugins/COMPANDER"
#puts [ listPlugins $PLUGINDIR ];
set pluginlist [ listPlugins $PLUGINDIR ];
set numplugins [ llength $pluginlist ]

if { $numplugins > 0 } {
    set guipatch [open $OUT_GUIPATCH w];
    set dsppatch [open $OUT_DSPPATCH w];
    set txtfile [open $PLUGINFILE w];

    generateGUIpatch    $guipatch $pluginlist;
    generateDSPpatch    $dsppatch $pluginlist;
    generatePluginsFile $txtfile $pluginlist;
    
    close $guipatch
    close $dsppatch
    close $txtfile

    puts "generated patches for [llength $pluginlist] plugins in '$PLUGINDIR'";
} {
    puts "no plugins found in '$PLUGINDIR'";
    exit -5;
}
# parse_args $@

# if [ -e "${PLUGINFILE}" ] && [ -z "${FORCE}" ]; then
#  echo "${PLUGINFILE} already exists!"
#  echo "not overriding unless you specify \"-f\""
#  echo
#  exit -2
# fi

# if [ "${PLUGINFILE}" ]; then
#  list_plugins > ${PLUGINFILE}

# generateGUIpatch ${PLUGINFILE} > ${OUT_GUIPATCH} 
# generateDSPpatch ${PLUGINFILE} > ${OUT_DSPPATCH} 

# else 
#  list_plugins
# fi



