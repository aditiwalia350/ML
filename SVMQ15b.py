#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Mar  9 23:15:30 2020

@author: aditiwalia
"""

import numpy as np
import random
X=np.array([[3,3],[3,4],[2,3],[1,1],[1,3],[2,2]])

'''order=[[1,2],[2,3],[3,4],[4,5],[5,6],[1,3],[2,4],[3,5],[4,6],[1,4],[2,5],[3,6],[1,5],[2,6],
       [1,6],[2,1],[3,2],[4,3],[5,4],[6,5], [3,1],[4,2],[5,3],[6,4],
       [4,1],[5,2],[6,3], [5,1],[6,2],[6,1]]'''
order=[]
for check in range(1,3001):
    for check_i in range(1,7):
        check_j=random.randrange(1,7)
        order.append([check_i,check_j])
print(order)
        
        
    
lambdaa=np.array([0.0,0.0,0.0,0.0,0.0,0.0])
lambdaa_old=np.array([0.0,0.0,0.0,0.0,0.0,0.0])
b=np.array([0.0,0.0,0.0,0.0,0.0,0.0])
F = np.array([0.0, 0.0, 0.0, 0.0, 0.0, 0.0])
E = np.array([0.0, 0.0, 0.0, 0.0, 0.0, 0.0])

#Y=np.array([3,4,3,1,3,2])
Z=np.array([1,1,1,-1,-1,-1])
C=2.5
epsilon=0.00001
bias=0.0
for passes in range(0,3000):
    #lambdaa=np.zeros((1,6))
    for lambdaorder in range(0,len(order)):
        i=order[lambdaorder][0]-1
        #print("i",i)
        j=order[lambdaorder][1]-1
        #print("j",j)
        if(i!=j):
            d=2*(np.dot(X[i],X[j]))-np.dot(X[i],X[i])-np.dot(X[j],X[j])
            if np.abs(d)>epsilon:
                F[i]=0
                for iteration in range(0,len(X)):
                    F[i]=F[i]+lambdaa[iteration]*Z[iteration]*(np.dot(X[iteration],X[i]))
                F[i]=F[i]+bias
                F[j]=0
                for iteration in range(0,len(X)):
                    F[j]=F[j]+lambdaa[iteration]*Z[iteration]*(np.dot(X[iteration],X[j]))
                F[j]=F[j]+bias
                
                E[i]=F[i]-Z[i]
                E[j]=F[j]-Z[j]
                lambdaa_old[i]=lambdaa[i]
                lambdaa_old[j]=lambdaa[j]
                lambdaa[j]=lambdaa[j]-(Z[j]*(E[i]-E[j]))/d
                if Z[i]==Z[j]:
                    l=max(0,lambdaa[i]+lambdaa[j]-C)
                    h=min(C,lambdaa[i]+lambdaa[j])
                else:
                    l=max(0,lambdaa[j]-lambdaa[i])
                    h=min(C,C+lambdaa[j]-lambdaa[i])
                    
                if(lambdaa[j]>h):
                    lambdaa[j]=h
                elif(l<=lambdaa[j] and lambdaa[j]<=h):
                    lambdaa[j]=lambdaa[j]
                elif(lambdaa[j]<l):
                    lambdaa[j]=l
                    
                lambdaa[i]=lambdaa[i]+Z[i]*Z[j]*(lambdaa_old[j]-lambdaa[j])
                b[i]=bias-E[i]-(Z[i]*(lambdaa[i]-lambdaa_old[i])*(np.dot(X[i],X[i])))-(Z[j]*(lambdaa[j]-lambdaa_old[j])*(np.dot(X[i],X[j])))
                b[j]=bias-E[j]-(Z[i]*(lambdaa[i]-lambdaa_old[i])*np.dot(X[i],X[j]))-(Z[j]*(lambdaa[j]-lambdaa_old[j])*np.dot(X[j],X[j]))
                
                if (0<lambdaa[i] and lambdaa[i]<C):
                    bias=b[i]
                elif(0<lambdaa[j] and lambdaa[j]<C):
                    bias=b[j]
                else:
                    bias=(b[i]+b[j])/2

    print("lambdaa values at iteration ",passes, " are ", lambdaa)
    print("b is", bias)
    
    if(np.equal(lambdaa,lambdaa_old).all()):
        print("Breaking at pass", passes, "as both lambda and lambda old are same")
        break
    else:
        continue

w_i=0.0
w_j=0.0
for count in range(0,6):
    w_i+=lambdaa[count]*Z[count]*X[count][0]
    w_j+=lambdaa[count]*Z[count]*X[count][1]
print("w1 is",w_i," w2 is ",w_j)
print(Z)
from matplotlib import pyplot as plt
color= ['r' if c == -1. else 'g' for c in Z]
plt.scatter(X[:, 0], X[:, 1], c=color)
        
slope=-1*(w_i/w_j)
x_coordinate=np.linspace(0, 4)
y_coordinate=slope * x_coordinate - (bias) / w_j
plt.plot(x_coordinate, y_coordinate)
plt.show()

            
            
        
        
            
        
        