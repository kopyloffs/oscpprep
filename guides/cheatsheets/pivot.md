# Pivoting


## SSH
```
ssh -L 9999$LOCALIP:$PORT5 $USER@$REMOTEIP  # local port forward

ssh -D $LOCALIP:$PORT $USER@$REMOTEIP # remote port forward

```


## Meterpreter
```
portfwd add –l 3389 –p 3389 –r target-host ##Forwards 3389 (RDP) to 3389 on the compromised machine running the Meterpreter shell
portfwd delete –l 3389 –p 3389 –r target-host ##Forwards 3389 (RDP) to 3389 on the compromised machine running the Meterpreter shell
portfwd flush # Meterpreter delete all port forwards
portfwd list #Meterpreter list active port forwards
run autoroute -s 192.168.15.0/24 #Use Meterpreters autoroute script to add the route for specified subnet 192.168.15.0
run autoroute -p #Meterpreter list all active routes
route #Meterpreter view available networks the compromised host can access
route add 192.168.14.0 255.255.255.0 3 #Meterpreter add route for 192.168.14.0/24 via Session number.
route delete 192.168.14.0 255.255.255.0 3 #Meterpreter delete route for 192.168.14.0/24 via Session number.
route flush # Meterpreter delete all routes

```
