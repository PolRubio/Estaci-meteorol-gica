import serial
import time
import csv
from time import gmtime, strftime
arduino = serial.Serial('COM5', 9600, timeout=1)
data = []
etiquetas = ["ldr","Humitat","Temperatura"]
Running = True
outputTXT = []
outputRecord = []
def lecturaPort():
    time.sleep(5)
    read = arduino.readline().decode('utf-8')
    kill = False
    c = False
    size = 3
    while kill == False:
        if read[:-2] == "start" or c == True:
            c = True
            for i in range(size+2):
                data.append(read[:-2])
                read = arduino.readline().decode('utf-8')
            kill = True

    return (data)

def reset (outputTXT,current_data):
    arduino.close()
    outputTXT.clear()
    data.clear()
    arduino.open()
def reloj ():
    diferencia = 3600
    tiempo=strftime("%d %b %Y %H:%M:%S", gmtime(time.time()+diferencia))
    return tiempo
while Running == True:
    current_data = lecturaPort() [1:-1]
    outputTXT.append(reloj())

    for i in range(len(current_data)):
        outputTXT.append(etiquetas[i])
        outputTXT.append(current_data[i])
    print(outputTXT)
    outputRecord.append (outputTXT)

    with open('info.csv','w', newline="\n") as file:
        info = csv.writer(file)
        info.writerows(outputRecord)
    reset(outputTXT,current_data)
