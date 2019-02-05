![MICKYE](https://raw.githubusercontent.com/QuantumSheep/mickye/master/logo.png)

# L'idée

A la base, ce projet était plus destiné à un amusement qu'à un logiciel pour notre cursus à l'ESGI. Le projet de programmation avec le langage C étant arrivé, nous nous sommes dit, « pourquoi pas ? ».

L’idée mère était de produire un outil facilitant la connexion à un Shell à distance et de pouvoir prendre le contrôle du Shell d'une cible. Le tout faisant référence à notre intérêt pour la sécurité informatique ainsi qu’à la sensibilisation des soucis personnels que peut générer le monde du digital.

Nous avons décalé cette idée en un outil moins intrusif qu'un malware en adaptant l’ouverture d'un Shell à distance à une interface graphique, dans l’optique d’être utilisé dans la gestion et l'administration de serveurs ou de machines à distance.

Nous voilà donc avec MICKYE, plus précisément Master Interface Control Key for Yogourt Exploitation. Le nom vient d'un mélange de Mickey (le logiciel étant un RAT) et d’un manque cruel d’imagination, « Mickey » étant une marque déposée.



# Bibliothèques

Pour la réalisation de ce projet, nous sommes passés par diverses bibliothèques, certaines natives au C, plus précisément à `gcc`, le compilateur utilisé durant notre projet, et d'autres externes au C pour nous faciliter l'intégration d'une interface graphique tel que `GTK` ou encore pour communiquer avec un système de gestion de base de données.



**Bibliothèques notables natives au C:**

- unistd.h - Fournit un ensemble de fonctions natives aux systèmes POSIX

- pthread.h - Création de threads et de mutex
- arpa/inet.h - Fonctions et constantes liés au protocole internet (IP)
- sys/socket.h - Gestion des sockets



**Bibliothèques externes:**

- GTK - Création d'interface graphie
  - VTE - Fournit un émulateur de terminal intégré à GTK
- SQLite3 - Création et gestion de base de données SQLite3



# Fonctionnement TCP

Lors de son lancement, le client va écouter à l'infini en attendant que sa connexion soit acceptée par le serveur cible. Le serveur quant à lui va attendre toute demande de connexion de la part d'un client.

Lorsqu'une connexion est établie entre le client et le serveur, le client va créer deux threads: un pour la lecture constante de son flux `stdout`, qui sera envoyé au serveur et un autre pour l'écriture des commandes qu'envoi le serveur vers son flux `stdin`. De son côté, le serveur aura un seul thread permettant à la lecture des données envoyés par le client, la plupart du temps, des retours de commande.

Pour l'envoi des commandes du serveur au client, l'émulateur de terminal écrira sur le flux dés qu'une commande sera envoyé par l'utilisateur.



L'utilisation des threads est cruciale lorsque des actions simultanées sont requises, la lecture et l'écriture devant fonctionner en même temps pour améliorer la fluidité du programme.



# Interface graphique

Nous avons utilisé GTK en tant que bibliothèque graphique, celle-ci étant très bien documenté et rependue dans la création d'interfaces graphiques, surtout sous les distributions UNIX (Linux, FreeBSD, ...), GTK fonctionnant très bien avec le serveur X, système de fenêtrage utilisé dans ceux-ci.

GTK intègre nativement une fonctionnalité de génération de l'interface depuis un fichier XML, celui-ci ayant une syntaxe proche du HTML avec des classes, des ids, etc...



![Interface](https://raw.githubusercontent.com/QuantumSheep/mickye/master/papers/img/full-interface.png)



## Evènements

Pour parler concrètement du fonctionnement des évènements sur GTK, chaque action sur l'interface est un nouveau thread, sinon l'interface se boquerais à chaque action en attendant qu'elle se termine, le logiciel fonctionnant de manière bloquante.



# Enregistrements des journaux

Le logiciel enregistrera certaines actions dans un fichier `.log`, cette fonctionnalité est une précaution pour régler tout problème qui serait survenu. 

L'emplacement des journaux est défini dans le fichier de configuration.



# Terminaux

L'utilisateur a accès à deux terminaux. Celui intégré à l'interface principale viens de la bibliothèque VTE qui s'ajoute à GTK. Il fonctionne comme un terminal normal et lancera le Shell par défaut de l'utilisateur.

![Terminal](https://raw.githubusercontent.com/QuantumSheep/mickye/master/papers/img/integrated-terminal.png)



Le second terminal est disponible lors de la connexion à un client, il recevra les données du client et pourra envoyer des commandes. Cet émulateur de terminal est assez spécifique puisque les commandes ne se font pas au même endroit que l'arrivée du texte.



![Terminal](https://raw.githubusercontent.com/QuantumSheep/mickye/master/papers/img/sub-terminal.png)





# Liste des clients

Les clients connectés au serveur TCP son listés à droite de l'interface. En faisant clique droit sur eux, un menu s'affiche répertoriant les diverses actions possibles pour ce client.