## 🔒 SSHBruteforcer – Outil de Force Brute SSH Éducatif

Ce dépôt contient un outil de force brute SSH écrit en C++, conçu pour tester des mots de passe sur un serveur SSH de manière éducative. Que vous soyez un passionné de sécurité informatique ou un étudiant explorant les concepts de réseau, cet outil est idéal pour apprendre et expérimenter ! 🔐💻

⚠️ **Note importante** : Cet outil est destiné uniquement à des fins éducatives. Ne l’utilisez pas sur des serveurs que vous ne possédez pas ou sans autorisation explicite.

---

### ✨ Fonctionnalités

✅ **Force Brute SSH** : Teste une liste de mots de passe sur un serveur SSH via `libssh`.  
✅ **Personnalisation** : Configurez l’IP, l’utilisateur, le port, le délai entre tentatives et la limite d’essais.  
✅ **Journalisation** : Enregistre les tentatives dans un fichier `bruteforce_log.txt`.  
✅ **Interruption** : Arrêt propre avec `Ctrl+C`.  
✅ **Validation** : Vérifie que l’adresse IP est valide avant de commencer.  
✅ **Interface** : Interface interactive en ligne de commande (CLI) avec couleurs pour une meilleure lisibilité.

---

## 🚀 Installation

### Prérequis
Ce projet a été développé et testé sur **Windows** avec **MSYS2 MinGW64**. Suivez ces étapes pour configurer votre environnement :

1️⃣ **Installer MSYS2**  
- Téléchargez MSYS2 sur [msys2.org](https://www.msys2.org/).  
- Suivez les instructions d’installation.  
- Ouvrez le terminal **MSYS2 MinGW 64-bit** (important : utilisez cet environnement).

2️⃣ **Mettre à jour MSYS2**  
Dans le terminal MSYS2 MinGW 64-bit :  
```bash
pacman -Syu
```
Si on vous demande de fermer et relancer le terminal, faites-le et relancez la commande.

3️⃣ **Installer les dépendances**  
Installez les outils et bibliothèques nécessaires :  
```bash
pacman -S mingw-w64-x86_64-gcc    # Compilateur GCC
pacman -S mingw-w64-x86_64-libssh # Bibliothèque libssh pour SSH
```

4️⃣ **Vérifier les installations**  
Assurez-vous que tout est correctement installé :  
```bash
gcc --version
```

---

### Cloner et Compiler

1️⃣ **Cloner le dépôt**  
```bash
git clone https://github.com/x86wdd/sshbruteforcer.git
```

2️⃣ **Naviguer vers le dossier du projet**  
```bash
cd /c/Users/Ryuji/Documents/Projets/ProjetsGithub/SSHBruteforcer
```

3️⃣ **Compiler le projet**  
```bash
g++ -o ssh_bruteforce sshbruteforcer.cpp -lssh
```
Cela générera l’exécutable `ssh_bruteforce.exe`.

---

## 🌐 Exécution

### Option 1 : Lancer depuis MSYS2 MinGW64 (Recommandé)  
Le terminal MSYS2 configure automatiquement les chemins pour les DLLs, rendant cette méthode la plus simple :  
```bash
./ssh_bruteforce
```

### Option 2 : Lancer depuis l’Explorateur Windows ou CMD  
Vous pourriez rencontrer une erreur de DLL (`libssh.dll not found`). Voici comment corriger :  

1️⃣ **Ajouter le chemin des DLL au PATH**  
Ajoutez temporairement le chemin :  
```cmd
set PATH=%PATH%;C:\msys64\mingw64\bin
```  
Ou ajoutez `C:\msys64\mingw64\bin` au PATH de manière permanente via les paramètres Windows :  
- Cherchez "Modifier les variables d’environnement" dans le menu Démarrer.  
- Sous "Variables système", trouvez `Path`, cliquez sur "Modifier", et ajoutez `C:\msys64\mingw64\bin`.  

2️⃣ **Lancer le programme**  
```cmd
cd C:\Users\Ryuji\Documents\Projets\ProjetsGithub\SSHBruteforcer
ssh_bruteforce.exe
```

**Alternative** : Copiez `libssh.dll` depuis `C:\msys64\mingw64\bin` dans le dossier où se trouve `ssh_bruteforce.exe`.

### Exemple d’utilisation

- **Mode interactif**  
  Lancez le programme :  
  ```bash
  ./ssh_bruteforce
  ```  
  Entrez les informations demandées :  
  ```
  Force Brute SSH - Par wdd
  Github : x86wdd
  Mise à jour : 08.04.2025
  Adresse IP du serveur (ex. 192.168.1.1) : 127.0.0.1
  Nom d'utilisateur : testuser
  Chemin du fichier de mots de passe : /c/Users/Ryuji/test_wordlist.txt
  Port SSH (par défaut 22) : 22
  Délai entre tentatives (en ms, ex. 1000 pour 1s) : 1000
  Limite de tentatives (0 pour aucune limite) : 0
  ```  
  Résultat attendu (si `test123` est dans la wordlist) :  
  ```
  Tentative #1 : [ÉCHEC] Tentative : password - Incorrect.
  Tentative #2 : [SUCCÈS] Mot de passe trouvé : test123
  ```

---

💡 **Puissant et éducatif – parfait pour explorer la sécurité SSH !** 🚀
