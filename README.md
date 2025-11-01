# 📇 Contact Manager / 📋 Gestionnaire de Contacts en C

A simple **C** program to manage personal information (first name, last name, age, job, phone number, and email). Data is stored in a text file (`saveInfos.txt`) and can be added, displayed, or deleted.

Un programme simple en **C** pour gérer des informations personnelles (prénom, nom, âge, métier, numéro et email). Les données sont stockées dans un fichier texte (`saveInfos.txt`) et peuvent être ajoutées, affichées ou supprimées.

---

## 🚧 Updates and Roadmap of the Project


### Update V1.0.5 - The Day 1 Update

* (Done) Could only add two people to the file
* (Done) Function `delete_file`: was deleting the file even when saying no
* (Done) Fucntion 'show_info': cant read the file when the program was just launched, even if the file has content

### Update V1.1 - Searching 'n Looking (30/10/2025)

* (done) Function `find_info` in the works (bool type used in the wrong way)

### Update V1.5 - Overhaul of the Project (December 2025)

* Function 'modify_people', 'orga_people', 'pick_info', 'total_people' in the works (modify a single information from a person)
* Will be using a struct array to store people in memory before writing them to the file
* Quality of life updates (updating ways of coding, small errors)
* 
### Update V2 - A Cool Local Interface (January 2026)

* Using Raylib 5.0 to completely change the looks for the project


## ✨ Features / Fonctionnalités

* ➕ Add a person with their personal information / Ajouter une personne avec ses informations personnelles
* 📖 Read all stored information / 📖 Lire toutes les informations enregistrées
* 🗑️ Delete all existing data (the file remains) / 🗑️ Supprimer toutes les données existantes (le fichier reste présent)
* 💻 Simple interactive console interface / 💻 Interface console simple et interactive

---

## 🗂️ Data Structure / Structure des données

The program uses a `Person` structure / Le programme utilise une structure `Person` :

```c
typedef struct {
    int age;
    char firstname[50];
    char lastname[50];
    char job[50];
    char number[50];
    char email[50];
} Person;
```

Each person is saved in `saveInfos.txt` in the format / Chaque personne est sauvegardée dans le fichier `saveInfos.txt` sous le format :

```
firstname lastname age job number email
```

---

## ⚙️ Requirements / Prérequis

* 🖥️ C compiler (GCC, Clang, etc.) / 🖥️ Compilateur C (GCC, Clang ou autre)
* 💻 Command-line environment compatible OS / 💻 Système d’exploitation compatible avec la ligne de commande

---

## 🛠️ Installation & Compilation / Installation et Compilation

1. Clone the repository or download the `main.c` file / Clonez le dépôt ou téléchargez le fichier `main.c`

2. Compile the program / Compilez le programme :

```bash
gcc -o contact_manager main.c
```

3. Run the program / Exécutez le programme :

```bash
./contact_manager
```

---

## 📝 Usage / Utilisation

At launch, the program displays a menu / Au lancement, le programme affiche un menu :

```
(in coming when the overhaul is finished)
```
---

## 💡 Example / Exemple

```
(in coming whent the overhaul is finished)
```
---

## 🤝 Contribution / Contribution

Contributions are welcome! / Les contributions sont les bienvenues !

Possible ideas / Idées possibles :

* ⚠️ Improve input error handling / Améliorer la gestion des erreurs de saisie
* 📊 Add sorting or filtering of contacts / Ajouter un tri ou filtrage des contacts

---

## 📜 License / Licence

This project is licensed under the MIT License / Ce projet est sous licence MIT
