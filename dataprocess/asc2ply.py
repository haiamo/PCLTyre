import time
 
from sys import argv
#script,filename = argv
# filename = raw_input("please input filename: ")
# print ("the input file name is:%r." %filename)
 
def convert(filename):
    print ("the input file name is:%r." %filename)    
    start = time.time()
    print("open the file.....")
    file = open(filename,"r+")
    count = 0
 
    for line in file:
        count = count + 1
    print("size is %d" %count)
    file.close()
 
    #output = open("out.ply","w+")
    f_prefix = filename.split('.')[0]
    output_filename = '{prefix}.ply'.format(prefix=f_prefix)
    output = open(output_filename,"w+")
 
    list1 = ['ply\n','format ascii 1.0\n','comment author:tony he\n','element vertex ']
    list2 = ['\n','property float x\n','property float y\n', "property float z\n", "end_header\n"]
    output.writelines(list1)
    output.write(str(count))
    output.writelines(list2)
 
    file1 = open(filename,"r")
    #all = file1.read()
    for line in file1:
        curline=line.split(' ')
        outstr=curline[0]+' '+curline[1]+' '+curline[2]
        output.write(outstr)
        if not('\n' in curline[2]):
            output.write('\n')
    output.close()
    file1.close()
 
    end = time.time()
    print("run time is:",end-start)
 
import os
items = os.listdir(".")
newlist = []
for names in items:
    if names.endswith(".asc"):
        newlist.append(names)
for i in newlist:
    convert(i)
