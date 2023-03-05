 #!/usr/bin/python3
 import serial
 ser = serial.Serial('/dev/ttyAMA0', 38400)
 
 try:
        while 1:
             # Read one line from the serial buffer
             line = ser.readline().decode().strip()
 
             # Create an array of the data
             Z = line.split(' ')
 
             # Print it nicely
             print ("----------")
             for i in range(len(Z)):
                 if i==0:
                     print ("NodeID: %s" % Z[0])
                 elif i in [1,2,3]:
                     print ("RealPower %d: %s W" % (i, Z[i]))
                 elif i in [4,5,6]:
                     print ("Irms %d: %s mA" % (i, Z[i]))
                 elif i==7:
                     print ("Vrms: %s V" % (Z[i]))
 
 except KeyboardInterrupt:
        ser.close()