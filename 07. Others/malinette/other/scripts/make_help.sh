#! /bin/sh
# Write descriptions of abstractions into a html file and the contextual menu (tclplugin)

# File output
filehtml="../../docs/OVERVIEW.html" 
filemenu="../tclplugins/menutree.txt" 

# Write into files
cat header.html > $filehtml
echo "{malinette \n" > $filemenu

# Initialize counters
nb=0
y=0

# Scan list of folders
for folder in "in" "out" "video" "audio" "numbers"     
do	
	echo "{ $folder \n {" >> $filemenu
	echo "<li class=\"bloc\"><div class=\"grid_block\"><h2>$folder</h2><ul>" >> $filehtml
	#echo "<h3>$folder</h3><ul>" >> $filehtml

	for file in ../../abstractions/$folder/*-help.pd
	do
		patch=$(basename $file)
		patch="${patch%%-help.pd}"
		description=$(cat $file | tr "\n" " " | sed -nr 's/.*#X text .* \\; -----* \\;(.*)/\1/p' | cut -d ";" -f1 | sed 's/\\//')
		nb=`expr "$nb" + 1`
		y=`expr "$nb" \\* 40 `
		y=`expr "$y" + 40`
		echo "<li><strong>$patch</strong> : $description</li>" >> $filehtml
		echo "$patch" >> $filemenu
	done
	echo "</ul></div></li>" >> $filehtml
	echo "}}\n" >> $filemenu
done

echo "}" >> $filemenu
cat footer.html >> $filehtml
