## AT+CNMP Preferred mode selection

((2-Automatic),(13-GSM Only),(38-LTE Only),(51-GSM And LTE Only))
AT+CNMP=13 //set GSM

## AT+CMNB Preferred selection between CAT-M and NB-IoT

((1-Cat-M),(2-NB-IoT),(3-Cat-M And NB-IoT))
AT+CMNB=1

## Network Registration

AT+CREG?
AT+CREG=2
+CREG: 2,5

AT+CGREG?
AT+CGREG=2
+CGREG: 2,5

## Inquiring UE System Information

AT+CPSI?

+CPSI: GSM,Online,222-01,0x5296,7652,10 EGSM 900,-48,0,57-57

# SEND SMS

set mode 1 text or 0 pdu
AT+CMGF=?
AT+CMGF=1

Set destiation
AT+CMGS="07731503341"
ctrl-z

# READ SMS

AT+CMGR=?
AT+CMGR=<index>

# list SMS

AT+CMGL=?

AT+CMGL=<stat>

"REC UNREAD" Received unread messages
"REC READ" Received read messages
"STO UNSENT" Stored unsent messages
"STO SENT" Stored sent messages
"ALL" All messages
Example
AT+CMGL="ALL"

# DELETE SMS

AT+CMGD=?
AT+CMGD=<index>
