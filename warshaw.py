import time
import ttn
import csv
import os
from flask import Flask, render_template
from multiprocessing import Process, Pool, Manager

app = Flask(__name__)


app_id = "warsawtrials1"
access_key = "ttn-account-v2.VQ1WAtGmaW7crNlM05tOBD5GfWjaVoTdNguCZMuJtdM"



global C_A
C_A = 0
global t_A
t_A = 0
global C_B
C_B = 0
global t_B
t_B = 0
global C_C
C_C = 0
global t_C
t_C = 0

def uplink_callback(msg, client):
  global C_A
  global C_B
  global C_C
  global t_A
  global t_B
  global t_C
  node=str(msg.dev_id)
  node=node.split("e")[1]
  node=float(node)
  node=int(node)
  print(node)
  u = str(msg.payload_fields)
  u = u.split("'")[1]
  u=float(u)
  u=int(u)
  print(u)
  if(node==1):
    C_A=C_A+u
    print("C_A={}".format(C_A))
  if(node==2):
    C_B=C_B+u
    C_A=C_A-1
    t_A=t_A+u
    print("C_B={}".format(C_B))
  if(node==3):
    C_C=C_C+u
    C_B=C_B-1
    t_B=t_B+u
    print("C_C={}".format(C_C))
  if(node==3):
    C_C=C_C-1
    t_C=t_C+u
  
  with open('storage.csv', 'w') as csvfile:
     spamwriter = csv.writer(csvfile, delimiter=' ', quotechar='|', quoting=csv.QUOTE_MINIMAL)
     spamwriter.writerow([C_A,C_B,C_C,t_A, t_B, t_C])

def func1():
     while(True):
       print("-----func1 opn------------")
       handler = ttn.HandlerClient(app_id, access_key)
       mqtt_client = handler.data()
       mqtt_client.set_uplink_callback(uplink_callback)
       mqtt_client.connect()
       time.sleep(28800)
       
       mqtt_client.close()
       print("-----func1 close------------")
       
def func2():
  while(True):
    print("-----func2 opn------------")
    app.run()

@app.route("/")
def index():
      global i  
      a=[]   
      with open('storage.csv', newline='') as csvfile:
        spamreader = csv.reader(csvfile, delimiter=' ', quotechar='|')
        i=0
        for row in spamreader: 
          a=row
      print("--------------func2 clse-----------------")
      return render_template('dashboard4.html', C_A = a[0],C_B=a[1],C_C=a[2],t_A=a[3],t_B=a[4],t_C=a[5])

	
       
if __name__ == "__main__":
      p1 = Process(target=func1)
      p1.start()
      p2 = Process(target=func2)
      p2.start()
      p1.join()
      p2.join()


   
    
    
       






