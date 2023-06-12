Suive les instructions suivantes pour le fonctionnement du programme "sim_mesure_courant.py"

Tout d'abord installer et configurer socat.

Ensuite on demarre les port virtuels avec cette commande : 

socat -d -d pty,raw,echo=0,link=/dev/ttySCT pty,raw,echo=0

Une fois lancé on obtien ce type de résultat : 

root@raspberrypi:/home/pi/sct013/finale# socat -d -d pty,raw,echo=0,link=/dev/ttySCT pty,raw,echo=0
2023/06/12 05:53:38 socat[20039] N PTY is /dev/pts/2
2023/06/12 05:53:38 socat[20039] N PTY is /dev/pts/3
2023/06/12 05:53:38 socat[20039] N starting data transfer loop with FDs [5,5] and [7,7]


Il est important de noter les ports disponibles pour la suite, dans mon cas c'est le port 2 et 3.


La prochaine étape est de modifier la ligne 7 (ser = serial.Serial('/dev/pts/5', 38400)), si besoin 
remplacer "/dev/pts/5" par le numero de port demarré par socat, par exemple 3 pour mon cas



En derniere étape on envoi des valeur alleatoires au port 2 (pour mon cas encore une fois, cela ne sera pas la meme chose pour tout le monde)

>> while true; do echo $((RANDOM % 21)) > /dev/pts/1; sleep 1; done

Donc la on doit remplacer "/dev/pts/1" par "/dev/pts/2".

UNE FOIS CELA FAIT, ON EXECUTE LE SCRIPT EN PYTHON3 

"python3 sim_mesure_courant.py"


