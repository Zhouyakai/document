#!/usr/bin/python
# -*- coding: UTF-8 -*-

import socket
# 建立一个服务端
import sys 
import os

serverAddr = '/home/yakai/study/02_UNIX_socket/py_server/py_server' # 套接字存放路径及名称
# serverAddr = '/home/jy/tmp/hhh_socket' # 套接字存放路径及名称
server = socket.socket(socket.AF_UNIX,socket.SOCK_STREAM)
print(server)

if os.path.exists(serverAddr):
        os.unlink(serverAddr)# 如果套接字存在，则删除

server.bind(serverAddr) #绑定要监听的端口

if server.listen(5): #最多监听5个客户端
        print >> sys.stderr, 'socket.listen error'
# server.listen(5) #开始监听 表示可以使用五个链接排队
# print(server.listen(5))

while True:# conn就是客户端链接过来而在服务端为期生成的一个链接实例
        print ('waiting for connecting')
        conn,addr = server.accept() #等待链接,多个链接的时候就会出现问题,其实返回了两个值
        print(conn,addr)
        flag = 1
        while True:
                if flag==1:
                        conn.send('Hi! I am python. I am glad to hear you!'.encode()) #然后再发送数据
                        flag = 2
                
                try:
                        # data = conn.recv(1024)  #接收数据
                        data = conn.recv(1024)[0:30] #!
                        # print(data)
                        data = data.decode("utf-8", errors='replace')

                        # print(type(data))
                        #因为data = conn.recv(1024)[0:30]收了30个bytes，为了可以能够在后面的判断里可以相等起来，这里把多余的空位手动补全了
                        a = b'1\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00'
                        a = a.decode("utf-8", errors='replace')
                        # print(type(a))
                        if a==data :#如果收到的信息是“1”就做出点不一样的花样
                                print("wow")
                                conn.send('Hi! I am python. I am sad to hear you!'.encode()) #然后再发送数据
                                
                        else:
                                print('In python:',data) #打印接收到的数据
                
                        #如果server不给client回应,则client不会继续发消息,!!:要看read和write的顺序
                        conn.send('Hi! I am python. I am happy to hear you!'.encode()) #然后再发送数据

                        # conn.send(data.upper()) #然后再发送数据
                        
                except ConnectionResetError as e:
                        print('关闭了正在占线的链接！')
                        break
        conn.close()

