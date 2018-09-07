- Nmap trick

```
nmap -Pn -sV $IP  ## just simple scan with version
nmap -Pn -sVS $IP ## sync scan for bypass some firewall
nmap -Pn -sVS -p- $IP ## all port scan for some hide port and services

```
