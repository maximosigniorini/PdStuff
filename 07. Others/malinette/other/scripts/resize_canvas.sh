#! /bin/sh
# Reset all sizes and position of the main patch and examples patches
# to display it at the same size and position


# Change the first line of the MALINETTE.pd patch
cp ../../MALINETTE-en.pd f.back
cp ../../MALINETTE-fr.pd f2.back
sed '1 s/^.*$/#N canvas 0 0 150 687 10;/g' f.back > ../../MALINETTE-en.pd
sed '1 s/^.*$/#N canvas 0 0 150 687 10;/g' f2.back > ../../MALINETTE-fr.pd
rm f.back
rm f2.back

# Change the first line of the examples/basics patchs
for file in ../../examples/basics-en/*.pd
do
	cp $file f.back
	sed '1 s/^.*$/#N canvas 151 22 800 687 10;/g' f.back > $file
done
rm f.back

# Change the first line of the examples/basics patchs
for file in ../../examples/basics-fr/*.pd
do
	cp $file f.back
	sed '1 s/^.*$/#N canvas 151 22 800 687 10;/g' f.back > $file
done
rm f.back


# Change the first line of the examples/basics patchs
for file in ../../projects/default/*.pd
do
	cp $file f.back
	sed '1 s/^.*$/#N canvas 151 22 800 687 10;/g' f.back > $file
done
rm f.back
