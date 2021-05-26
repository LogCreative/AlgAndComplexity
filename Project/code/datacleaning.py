# 要添加一个新单元，输入 '# %%'
# 要添加一个新的标记单元，输入 '# %% [markdown]'
# %%
import pandas as pd


# %%
bandwidth = pd.read_excel('ToyData.xlsx',sheet_name='Inter-Datacenter Links').set_index('Bandwidth/MBps').replace('-',0)
dcd = pd.read_excel('ToyData.xlsx',sheet_name='Data Center Details')
slot = dcd.loc[:,['DC','Num of Slots']].dropna(how='any').set_index('DC')
location = dcd.loc[:,['Data Partition','Location']].set_index('Data Partition')


# %%
RQ = pd.read_excel('ToyData.xlsx',sheet_name='Job List').iloc[:,1:].dropna(how='all')
RQ.set_index(list(RQ)[0],inplace=True)
pre = RQ[list(RQ)[-1]].dropna()
exe = RQ[list(RQ)[-2]]
RQ = RQ.iloc[:,0:-2].fillna(0)


# %%
pre = pre.apply(lambda x: x.replace("{","").replace("}","")).str.split(", ",expand=True).transpose()


# %%
import re


# %%
dag = {}
for c in list(pre):
    for l in pre.index.to_list():
        cell = pre[c][l]
        if(cell and cell!= " "):
            edge = re.search(r'\((?P<start>.+),(?P<end>.+)\)',cell,re.S).groupdict()
            if(edge['start'] in dag):
                dag[edge['start']].append(edge['end'])
            else:
                dag[edge['start']] = [edge['end']]

# isolated node
for l in RQ.index.to_list():
    if(l not in dag):
        dag[l] = []


# %%
# topological sort
topo_order = []

def dfs(key):
    if(key in topo_order):
        return
    topo_order.append(key)
    if(key in dag):
        for child in dag[key]:
            dfs(child)

for key in dag:
    dfs(key)

# BFS through topological order
stage = {}
visitqueue = list()
for node in topo_order:
    visitqueue.append(node)
    while(len(visitqueue)>0):
        top = visitqueue.pop(0)
        if(top not in stage):
            stage[top] = 0
        if(top in dag):
            for child in dag[top]:
                visitqueue.append(child)
                if((child not in stage) or (stage[top] + 1 > stage[child])):
                    stage[child] = stage[top] + 1

# group every class of job in every stage
jobs = {}
for tjob in stage:
    jobattr = re.search(r'(\w+)(\d+)',tjob).groups()
    jobclass = jobattr[0]
    jobstage = stage[tjob]
    if(jobclass not in jobs):
        jobs[jobclass] = []
    if(len(jobs[jobclass])<=jobstage):
        jobs[jobclass].append([])
    jobs[jobclass][jobstage].append(tjob)

jobs


# %%
import numpy as np
import gurobipy as gp
from gurobipy import GRB


# %%
m = gp.model('geodata')

# boolean matrix for choosing position of
# the job slot

# minimize average time

# subject to:
# (1) allocated
# (2) not exceed the number of slot
# (3) calculate time on every job

for jobclass in jobs:
    for stage in jobs[jobclass]:
        for job in stage:
            max(
            exe[job] + # transmition time locally,
            exe[job] + # transmition from other
            )


