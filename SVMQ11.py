#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Mar  9 20:57:15 2020

@author: aditiwalia
"""

#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Mar  8 23:54:32 2020

@author: aditiwalia
"""

# Classification template

# Importing the libraries
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import plotly.graph_objs as go
from sklearn.metrics import accuracy_score

import numpy as np
from ipywidgets import interact

# Importing the dataset
dataset = pd.read_csv('sample.csv')
X = dataset.iloc[:, [1,2,3]].values
y = dataset.iloc[:, 4].values
# Splitting the dataset into the Training set and Test set
from sklearn.model_selection import train_test_split
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size = 0.50,shuffle=False,random_state=0,stratify=None)

# Feature Scaling
from sklearn.preprocessing import StandardScaler
sc = StandardScaler()
X_train = sc.fit_transform(X_train)
X_test = sc.transform(X_test)

# Fitting SVM to the Training set
from sklearn.svm import SVC
from sklearn.metrics import confusion_matrix
C_value=[1,2,3,4]
sigma_value=[2,3,4,5]
for i in range(0,len(C_value)):
    for j in range(0,len(sigma_value)):
        classifier = SVC(C=C_value[i],kernel = 'rbf',degree=3,gamma=1/(2*(sigma_value[j]*sigma_value[j])))
        classifier.fit(X_train, y_train)
        # Predicting the Test set results
        y_pred = classifier.predict(X_test)
        # Making the Confusion Matrix
        cm = confusion_matrix(y_test, y_pred)
        total_right_predictions=cm[0][0]+cm[1][1]
        accuracy=float(total_right_predictions/len(X_test))
        print("For C=",C_value[i], "and p=", sigma_value[j], "accuracy is ", accuracy*100)
        #print("accuracy score is",accuracy_score(y_test,y_pred))
        #print("accuracy score is",accuracy_score(y_test,y_pred,normalize=False))

