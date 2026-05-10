# IHM Client

## Description

Ce projet est une interface client pour la partie IHM Client du projet de chat local. Il permet aux utilisateurs d'interagir avec l'application via une interface graphique depuis laquelle il faut indiquer l'adresse IP du serveur et le port de connexion. De plus, il faut indiquer un pseudo et un mot de passe pour se connecter au serveur, qu'il faut avoir préalablement ajouté à la base de données du serveur.

Une fois connecté, l'utilisateur peut envoyer des messages à d'autres utilisateurs connectés au serveur, ainsi que recevoir des messages de ces derniers. De plus, il peut envoyer des messages dans un chat global, qui est visible par tous les utilisateurs connectés au serveur.

## Installation et utilisation

Pour exécuter l'interface Client : 

1. Ouvrir un terminal à la racine du projet
2. Exécuter la commande suivante :
```bash
./build.sh
```
3. Puis démarrer l'application avec la commande suivante :
```bash
./applab_ihm_client
```