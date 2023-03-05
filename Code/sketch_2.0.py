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
             if len(Z)>15:
                 print ("----------")
                 print ("          \tCT1\tCT2\tCT3") 
                 print ("RealPower:\t%s\t%s\t%s" % (Z[1], Z[6], Z[11]))
                 print ("AppaPower:\t%s\t%s\t%s" % (Z[2], Z[7], Z[12]))
                 print ("Irms     :\t%s\t%s\t%s" % (Z[3], Z[8], Z[13]))
                 print ("Vrms     :\t%s\t%s\t%s" % (Z[4], Z[9], Z[14]))
                 print ("PowerFact:\t%s\t%s\t%s" % (Z[5], Z[10], Z[15]))
 
 
 except KeyboardInterrupt:
        ser.close()