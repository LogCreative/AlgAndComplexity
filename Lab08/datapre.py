import pandas as pd
import os
indata = pd.read_table(os.path.dirname(__file__) + "/SCC.in",sep=' ')
adapter=""
for l in indata.index.to_list():
    adapter += '<' + str(indata[indata.columns[0]][l]) + ',' + str(indata[indata.columns[1]][l]) + ",1>\n"
with open("main.txt",'w') as file_object:
    file_object.write(adapter)
edges="source,target\n"
for l in indata.index.to_list():
    edges += str(indata[indata.columns[0]][l]) + ',' + str(indata[indata.columns[1]][l]) + "\n"
with open("edges.csv",'w') as file_object:
    file_object.write(edges)
nodes="id,label\n"
for i in range(0,int(indata.columns[0])):
    nodes+=str(i)+','+str(i)+'\n'
with open("nodes.csv",'w') as file_object:
    file_object.write(nodes)