#!/usr/bin/python
""" Convert Cyclone comments to standard comments

That is it does the following replacement:

Before:
    #X obj 126 146 comment 51 9 helvetica ? 768 0 0 0 The text is here;
After:
    #X text 126 146 The text is here;

"""

import sys

for filename in sys.argv[1:]:
    
    file = open(filename)
    newcontent = ""
    
    for line in file:
        a = line.split()
        if len(a) > 12 and a[1] == "obj" and a[4] == "comment":
            a[1] = "text"
            tmp = a[:4]
            tmp.extend(a[13:])
            #print "LIST: ", tmp
            newcontent += " ".join(tmp).strip()
            newcontent += "\n"
        else:
            newcontent += line

    file.close()
    newfile = open(filename, "w")
    newfile.write(newcontent)
    newfile.close()

