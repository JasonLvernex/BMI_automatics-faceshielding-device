# _*_ coding:utf-8 _*_
#this is a Softmax classifier created by Jason Lyu
from csv import reader
import numpy as np
import os
import tensorflow as tf
np.random.seed(1337)  # for reproducibility
from keras.datasets import mnist
from keras.utils import  np_utils
from keras.models import Sequential
from keras.layers import Dense,Activation,Conv2D,MaxPooling2D,Flatten,Dropout
from keras.optimizers import  Adam
from keras.optimizers import RMSprop
import pandas as pd
from sklearn.model_selection import KFold
from keras.layers.embeddings import Embedding
from keras.utils.vis_utils import plot_model
import matplotlib.pyplot as plt
import pydotplus
import csv

#data reading
##filename=input("请输入文件名： ")
##with open(filename,'rt',encoding='UTF-8')as raw_data:
##    readers=reader(raw_data,delimiter=',')
##    x=list(readers)
##    data=np.array(x)
##    print(data)
##    print(data.shape)
##y_data=[i[0] for i in data[1:]]
#print(y_data)
#print(len(data[1:]))
#print(data[1:])
#x_data=[[] for x in range(0,24)]#np.empty(24)
##data_list=data.copy()
##x_data=[[] for x in range(0,len(data[1:]))]

#print(data_list[1])
#for x in range(1,len(data[1:])+1):
#    print(x)
#    for i in range(1,25):#data_list[x]:
        #print(i[x])
 #       x_data[i-1].append(data_list[x][i])
##for x in range(1,len(data[1:])+1):
##    for i in range(1, 25):  # data_list[x]:
##        x_data[x-1].append(data_list[x][i])
#print(x_data)
#print(len(x_data))
#file names selection:
#'C://Users//lenovo//Desktop//feature extraction_matlab//1128-5.csv'
data=pd.read_csv('C://Users//lenovo//Desktop//feature extraction_matlab//1213-3-A.csv')
x=data[data.columns[1:]]
y=data.iloc[:,0]
print(data.head())
print(type(x))
print(y)

#training
#download the mnist to the path if it is the first time to be called
#X shape(60,000 28x28), y shape(10,000,)


#KFold

kf=KFold(n_splits=2,shuffle=True)    #分成几个组
#kf.shuffle()
kf.get_n_splits(x)
print(kf)
for train_index,test_index in kf.split(x):
    #print("Train Index:",train_index,",Test Index:",test_index)
    X_train,X_test=x.iloc[train_index,],x.iloc[test_index,]
    Y_train,Y_test=y.iloc[train_index,],y.iloc[test_index,]

#another way to split the data
#from sklearn.model_selection import train_test_split

#x_train, x_test, y_train, y_test = train_test_split(X, Y, test_size=0.20, random_state=0)
#x_test, x_valid, y_test, y_valid = train_test_split(x_test, y_test, test_size=0.5, random_state=0)

    #print(X_train,X_test,y_train,y_test)
#X_train=x[0:2500]
#X_test=x[2501:]
#Y_train=y[0:2500]
#Y_test=y[2501:]

#data pre-processing

Y_train=np_utils.to_categorical(Y_train,num_classes=2)
Y_test=np_utils.to_categorical(Y_test,num_classes=2)
print(Y_test.shape)
print(Y_test)
print(X_test.shape)

#another way to build neural net
model=Sequential()#used to be relu
model.add(Dense(64,input_dim=32,activation='sigmoid'))
model.add(Dropout(0.02))
model.add(Dense(2,activation='softmax'))
#first layer:28*28 input out is 32 features, second:out put is 10 features, softmax to classify
#another way to define your optimizer
rmsprop=RMSprop(learning_rate=0.001,rho=0.9,epsilon=1e-08)
#we add metrics to get more results you want to see
model.compile(optimizer=rmsprop,loss='categorical_crossentropy',metrics=['accuracy'])#loss='binary_crossentropy'
print('training----')
#another way to train the model
history =model.fit(X_train,Y_train,epochs=40,batch_size=50,validation_data=(X_test,Y_test)) #each time 32 datas with two rounds
print('\ntesting-----')
#evaluate the model with metrics we defined earlier

loss,accuracy=model.evaluate(X_test,Y_test)

print('test loss=',loss)
print('test accuracy=',accuracy)

plot_model(model, to_file='model_test.png',show_shapes=True)
model.summary()

#weight_Dense_1,bias_Dense_1 = model.get_layer('dense_input').get_weights()
weight_2,bias_2 = model.get_layer('dense').get_weights()
#weight_3,bias_3 = model.get_layer('activation').get_weights()
weight_4,bias_4 = model.get_layer('dense_1').get_weights()
#weight_5,bias_5 = model.get_layer('activation_1').get_weights()
#print('w1=',weight_Dense_1,'b1=',bias_Dense_1)
print('w2=',weight_2,'b2=',bias_2)
#print('w3=',weight_3,'b3=',bias_3)
print('w4=',weight_4,'b4=',bias_4)
#print('w5=',weight_5,'b5=',bias_5)

def figure(history):
    acc = history.history['accuracy']
    val_acc = history.history['val_accuracy']
    loss = history.history['loss']
    val_loss = history.history['val_loss']
    epochs = range(len(acc))
    plt.plot(epochs, acc, 'bo', label='Training accuracy')
    plt.plot(epochs, val_acc, 'b', label='test accuracy')
    plt.title('Training and validation accuracy')
    plt.legend()
    plt.savefig('Training and test accuracy.png')
    plt.figure()

    plt.plot(epochs, loss, 'bo', label='Training loss')
    plt.plot(epochs, val_loss, 'b', label='test loss')
    plt.title('Training and test loss')
    plt.legend()
    plt.savefig('Training and test loss')
    plt.show()


def write_csv_file(path, head, data):
    try:
        with open(path, 'w') as csv_file:
            writer = csv.writer(csv_file, dialect='excel')

            if head is not None:
                writer.writerow(head)

            for row in data:
                writer.writerow(row)

            print("Write a CSV file to path %s Successful." % path)
    except Exception as e:
        print("Write an CSV file to path: %s, Case: %s" % (path, e))


figure(history)
#write_csv_file('C:\\Users\\lenovo\\Desktop\\feature extraction_matlab\\1213-3-A-w.csv',None,weight_2)
