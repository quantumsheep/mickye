![MICKYE](https://raw.githubusercontent.com/QuantumSheep/mickye/master/logo.png)

# Manuel d’utilisation

Ce manuel est destiné à vous guidez dans l’utilisation du logiciel « Mickye », un projet de C fait à l’esgi pour l’année 2019.

# Disclaimer

Veuillez noter que cette application a été développer par eux passionnés de programmation dans un seul et unique but éducationnel, **tout détournement de l’usage de cette application à d’autres fins qu'éducationnel n’est en rien l’affaire des créateurs.**

# Prérequis

Afin de pouvoir utiliser le projet il vous faudra tout d’abord un système d’exploitation baser sur un noyau Linux, **avec un environnement graphique d’installé pour le serveur mais pas pour le client.**

Pour le moment les tests exécutez ont démontrés que le logiciel est compatible avec :
- Debian : 100 %
- Ubuntu : 100 %

**Les librairies sont disponibles dans les fichiers d’installation du projet.**

En termes de librairies, il vous faudra disposer de :
- **GTK** (Pour l’interface graphique)
- **VTE** (Pour l’émulation de votre terminal)
- **SQLite3** (Pour gérer la base de donnée locale)
- **GCC** (pour compiler le projet)
- **MAKE** (pour compiler le projet)

Vous devrez disposez également :
D’une carte réseau fonctionnelle.
D’une connexion à un réseau (LAN ou WAN)

Si vous désirez utiliser Mickye dans une optique WAN, n’oubliez pas d’établir des **règles de redirection de port.**

Le PORT par défaut est le port **3000**
L’adresse du serveur par défaut coté serveur est **127.0.0.1**
L’adresse liée au logiciel client par défaut est **127.0.0.1**

N’hésitez pas à modifier les adresses et/ou les ports pour un usage plus spécifique depuis le fichier de configuration `options.conf` situé à la base du projet, avant de le compiler.


# Installation

**Toutes les étapes d’installation sont obligatoires.**

Tout d’abord il vous faudra récupérer le projet depuis ce lien si ce n’est pas déjà fait :

__**https://github.com/QuantumSheep/mickye/archive/master.zip**__

Ensuite il vous faudra décompressez l’archive zip (à chacun sa méthode)

Déplacez-vous dans le dossier du projet précédemment extrait à l’aide de cd.

Lancez ensuite `./install_dep.sh` il s’agit du script bash d’installation de l’ensemble des dépendances liées au projet.

Une fois les dépendances installées sans erreurs, vous pouvez commencer la compilation du client et du serveur :
- Déplacez-vous dans `/client` puis lancez la commande de compilation `make`.
- Déplacez-vous dans `/server` puis lancez la commande de compilation `make`
- Ou rentrez `cd client && make && cd ../server && make`
- Ou lancez `build.sh`

Enfin, une fois la compilation terminée, vous pouvez commencer à utiliser Mickye.

Entrez la commande `./mickye_server` depuis `/server`. Si tout s’est déroulé correctement, vous devriez avoir une interface comme celle-ci qui viens de s’ouvrir :

![SERVEUR](https://raw.githubusercontent.com/QuantumSheep/mickye/master/papers/img/terminal-debian.png)

Entrez la commande `./mickye_client` depuis `/client` de même si tout s’est bien déroulé, vous devriez avoir un message comme celui-ci depuis votre invite de commande :

![CLIENT](https://raw.githubusercontent.com/QuantumSheep/mickye/master/papers/img/client-debian.png)

# Utilisation

![SERVEURWITHCLIENTS](https://raw.githubusercontent.com/QuantumSheep/mickye/master/papers/img/terminal-with-client-debian.png)

__**Start server :**__
Permet de lancer le serveur d’écoute. Si un client est exécuté vers votre L’IP du serveur (127.0.0.1 par défaut), il se liera au serveur.

__**Stop server :**__
Permet de stopper le serveur d’écoute. Si un ou plusieurs clients sont connectés, il coupera la connexion et les retirera de la liste.

__**Connect to client :**__
Une fois avoir sélectionner un client dans la liste à l’aide d’un clic gauche, le bouton « connect to client » permettra d’établir une connexion vers le client sélectionné. Faisant ainsi apparaître son terminal (voir pages suivantes). Si une erreur ce produit, elle sera affichée dans la partie de logs (voir items du dessous)

__**Découpage de droite (partie haute) :**__
Correspond à la liste des différents clients, vous pouvez y sélectionner, renommer, supprimer un client et vous y connecter à l’aide d’un clic droit (voir pages suivantes)

__**Découpage de droite (partie basse) :**__
Correspond à la liste des logs reçu pour chaque action de l’application.

![POPUP](https://raw.githubusercontent.com/QuantumSheep/mickye/master/papers/img/popup-debian.png)

Une fois un clic droit effectué sur un client de la liste un menu déroulant s’ouvre.

__**Connect to the selected client :**__
Essaye d’établir une connexion vers le client sélectionné, ouvre son terminal correspondant s’il n’y a pas d’erreur sinon, inscrit l’erreur dans la liste des logs (voir pages du dessus).

__**Rename selected client :**__
Lance une pop-up vous permettant de renommer le client sélectionné s’il n’y a pas d’erreur sinon, inscrit l’erreur dans la liste des logs (voir pages du dessus).

__**Remove selected client :**__
Essaye de supprimer un client et de clore la connexion établie avec lui s’il n’y a pas d’erreur sinon, inscrit l’erreur dans la liste des logs (voir pages du dessus).

![RENAME](https://raw.githubusercontent.com/QuantumSheep/mickye/master/papers/img/rename-debian.png)

__**Pop-up de renommage :**__
Rentrer un nom pour le client sélectionné, puis appuyer sur entrer, essayera de renommer le client. Sinon, renverra une erreur dans la partie de logs (voir pages du dessus).

![TERMINAL](https://raw.githubusercontent.com/QuantumSheep/mickye/master/papers/img/terminal-debian.png)

Voici une fenêtre de terminal client.

Depuis cette fenêtre vous pouvez exécuter n’importe qu’elle commande sur la machine du client cible.

N’importe qu’elle commande mis à part :
	Les commandes incluant un lien graphique ou tty comme :
		Les commandes SU ou SUDO (si le client n’est pas lancé en root)

La commande `exit` tuera la fenêtre de terminal, et fermera la connexion avec le client.