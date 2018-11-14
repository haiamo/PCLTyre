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
 
    #output = open("out.pcd","w+")
    f_prefix = filename.split('.')[0]
    output_filename = '{prefix}.pcd'.format(prefix=f_prefix)
    output = open(output_filename,"w+")
 
    list = ['# .PCD v0.7 - Point Cloud Data file format\n','VERSION 0.7\n','FIELDS x y z intensity\n','SIZE 4 4 4 4\n','TYPE F F F F\n','COUNT 1 1 1 1\n', "VIEWPOINT 0 0 0 1 0 0 0\n"]
    output.writelines(list)
    output.write('WIDTH ')
    output.write(str(count))
    output.write('\nHEIGHT ')
    output.write(str(1))
    output.write('\nPOINTS ')
    output.write(str(count))
    output.write('\nDATA ascii\n')
 
    file1 = open(filename,"r")
    all = file1.read()
    output.write(all)
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
