#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Mar 12 00:54:36 2020

@author: aditiwalia
"""

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
from sklearn.metrics import confusion_matrix
import numpy as np
from ipywidgets import interact
from sklearn.svm import SVC
from sklearn.metrics import confusion_matrix
initial_X=[1,2,3]

# Importing the dataset
dataset = pd.read_csv('sample.csv')
X = dataset.iloc[:, initial_X].values
print("check")
#print(X)
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

classifier = SVC(C=1,kernel = 'linear')
classifier.fit(X_train, y_train)
print("Weight of HMM:",classifier.coef_[0][0])
print("Weight of SSD:",classifier.coef_[0][1])
print("Weight of OGS:",classifier.coef_[0][2])

# Predicting the Test set results
y_pred = classifier.predict(X_test)
# Making the Confusion Matrix
    
cm = confusion_matrix(y_test, y_pred)
print("confusion matrix",cm)
total_right_predictions=cm[0][0]+cm[1][1]
accuracy=float(total_right_predictions/len(X_test))
print("For C=3 and p=2 accuracy is ",accuracy*100)

    
    
            
    
        
