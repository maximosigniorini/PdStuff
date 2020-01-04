#!/bin/bash
# Egregore source
# Launching script
# chdh - 2015
# v2.0


# CHANGE TO DEBUG=1 TO HAVE INFORMATIONS IN LOG.TXT
debug=0

# DOWNLOAD PATCH FUNCTION - NOT USED IN V2.0
function do_loop_download {
    if [[ $debug = 0 ]]; then
        while [ 0 ]; do
            "$DIR"/src/bin/Pd-0.46-2.app/Contents/Resources/bin/pd -noprefs -noadc -nodac -nogui -send "debug "$debug"" -open "../../../../../abs/param_down_sub.pd"
        done
    else
        while [ 0 ]; do
            echo "STARTING param down sub pd">>../log.txt
            "$DIR"/src/bin/Pd-0.46-2.app/Contents/Resources/bin/pd -noprefs -noadc -nodac -nogui -send "debug "$debug"" -open "../../../../../abs/param_down_sub.pd" 2>> ../log.txt
            echo "////////////////////////////// CRASH"
            echo $(date)
            echo "CRASH : param_down_sub : $(date)">>../log.txt
        done
    fi
}

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR

# PREVENT RESUME
rm -Rf ~/Library/Saved\ Application\ State/org.puredata*
defaults write org.puredata NSQuitAlwaysKeepsWindows -int 0
defaults write org.puredata NSQuitAlwaysKeepsWindows -bool false
defaults write org.puredata.pd.wish NSQuitAlwaysKeepsWindows -int 0
defaults write org.puredata.pd.wish NSQuitAlwaysKeepsWindows -bool false

# PRINT HARDWARE INFO TO LOG
if [[ $debug = 1 ]]; then
    echo "////////////////////////////// START : $(date)" >> ../log.txt
    echo "osx : $(uname -a)" >> ../log.txt
    echo "HARDWARE" >> ../log.txt
    echo "$(sysctl hw)" >> ../log.txt
fi

# LAUNCH DONWLOAD PATCH
# do_loop_download &
# pid_loop=$!

# LAUNCH MAIN PATCH
if [[ $debug = 1 ]]; then
    echo "STARTING main pd">>../log.txt
    "$DIR"/src/bin/Pd-0.46-2.app/Contents/Resources/bin/pd -stderr -noprefs -r 48000 -audioaddoutdev "Built-in Output" -noadc -audiobuf 50 -blocksize 128 -midiindev 1 -send "debug "$debug"" -send "os osx" -open "../../../../../egregore.pd" 2>> ../log.txt
else
    "$DIR"/src/bin/Pd-0.46-2.app/Contents/Resources/bin/pd -noprefs -r 48000 -audioaddoutdev "Built-in Output" -noadc -audiobuf 50 -blocksize 128 -midiindev 1 -send "debug "$debug"" -send "os osx" -open "../../../../../egregore.pd"
fi

# KILLALL WHEN FINISH
# kill $pid_loop
# pid_pd=`ps ax | grep abs/param_down_sub | grep -v grep | awk '{print $1}'`
# kill $pid_pd
killall egregore_source
if [[ $debug = 1 ]]; then
    echo "////////////////////////////// STOP: $(date)" >>../log.txt
fi
exit 0
