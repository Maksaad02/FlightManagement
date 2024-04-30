#include <iostream>
#include <string>
#include <deque>
#include <set>
#include <algorithm>
#include <map>
using namespace std;

// Structure pour stocker la date
struct Date {
    int jour;
    int mois;
    int annee;
};

// Classe Passager
class Passager {
private:
    int idPassager;
    string nom;
    string telephone;
    string passeport;
        int reservations; // Ajout d'un compteur de réservations pour fonctionnalité 2

public:
    // Constructeur
    Passager(int id, const string& n, const string& tel, const string& pass) : idPassager(id), nom(n), telephone(tel), passeport(pass), reservations(0) {}

//Getter method for the idPassager 
    int getIdPassager() const{
        return idPassager;
    }

// Getter method for the name attribute
    string getNom() const {
        return nom;
    }
   
    bool operator<(const Passager& other) const {
        return idPassager < other.idPassager;
    }

 // Méthode pour obtenir le nombre de réservations
    int getNombreReservations() const {
        return reservations;
    }

    // Méthode pour incrémenter le nombre de réservations
    void incrementerReservations() {
        reservations++;
    }

    // Méthode FacturePaiement
    void FacturePaiement() const {
        // Implémentation de la méthode
        // Affichage de la facture de paiement
        cout << "Facture de paiement pour le passager " << nom << " (ID: " << idPassager << ")" << endl;
        // ......zid les details dial la facture
     
    }
};

// Classe Paiement
class Paiement {
private:
    int idPaiement;
    double montant;
    Date datePaiement;
    string methodePaiement;
public:
    // Constructeur
    Paiement(int id, double mont, const Date& date, const string& methodeP) : idPaiement(id), montant(mont), datePaiement(date), methodePaiement(methodeP) {}
    // Autres méthodes, etc.
};

// Classe Vol
class Vol {
private:
    string numeroVol;
    string aeroportDepart;
    string aeroportArrivee;
    Date dateDepart;
    Date dateArrivee;
    int placesDisponibles;
    double prix;
public:
    // Constructeur
    Vol(const string& num, const string& dep, const string& arr, const Date& dateDep, const Date& dateArr, int places, double pri) : numeroVol(num), aeroportDepart(dep), aeroportArrivee(arr), dateDepart(dateDep), dateArrivee(dateArr), placesDisponibles(places), prix(pri) {}

    // Méthodes pour accéder/modifier les attributs
    void setNumeroVol(const string& num) { numeroVol = num; }
    void setAeroportDepart(const string& dep) { aeroportDepart = dep; }
    void setAeroportArrivee(const string& arr) { aeroportArrivee = arr; }
    void setDateDepart(const Date& date) { dateDepart = date; }
    void setDateArrivee(const Date& date) { dateArrivee = date; }
    void setPlacesDisponibles(int places) { placesDisponibles = places; }
    void setPrix(double pri) { prix = pri; }

    string getNumeroVol() const {
        return  numeroVol;
    }
    // Getter pour obtenir la date de départ
    Date getDateDepart() const {
        return dateDepart;
    }

    // Getter pour obtenir le nombre de places disponibles
    int getPlacesDisponibles() const {
        return placesDisponibles;
    }

    // Méthode pour augmenter le prix du vol de 10%
    void augmenterPrix() {
        prix *= 1.1;
    }
};


// Fonction pour comparer les dates
bool comparerDates(const Date& d1, const Date& d2) {
    if (d1.annee != d2.annee)
        return d1.annee < d2.annee;
    if (d1.mois != d2.mois)
        return d1.mois < d2.mois;
    return d1.jour < d2.jour;
}


// Classe VolEconomique
class VolEconomique : public Vol {
    // Aucun attribut supplémentaire nécessaire
};

// Classe VolBusiness
class VolBusiness : public Vol {
private:
    std::string confort;
public:
    VolBusiness(const string& num, const string& dep, const string& arr, const Date& depDate, const Date& arrDate, int places, double pri, const string& conf) : Vol(num, dep, arr, depDate, arrDate, places, pri), confort(conf) {}
        // Autres méthodes, etc.
                        // ***confort getter needed
    // Constructeur, méthodes, etc.
};

// Classe Reservation
class Reservation {
private:
    int idReservation;
    Date dateReservation;
    const Passager* passager;
    Vol* vol;
    Paiement* paiement;
public:
    // Constructor
    Reservation(int id, Date& date, const Passager* p, Vol* v, Paiement* pay)
        : idReservation(id), dateReservation(date), passager(p), vol(v), paiement(pay) {}
};

int main() {

    deque<Vol> listeVols;

    // Demander à l'utilisateur de remplir les vols
    int nombreVols;
    cout << "Combien de vols souhaitez-vous ajouter ? ";
    cin >> nombreVols;

    for (int i = 0; i < nombreVols; ++i) {
        string numeroVol, aeroportDepart, aeroportArrivee;
        Date dateDepart, dateArrivee;
        int placesDisponibles;
        double prix;

        cout << "Vol #" << i + 1 << ":" << endl;
        cout << "Numéro de vol : ";
        cin >> numeroVol;
        cout << "Aéroport de départ : ";
        cin >> aeroportDepart;
        cout << "Aéroport d'arrivée : ";
        cin >> aeroportArrivee;
        cout << "Date de départ (jour mois annee) : ";
        cin >> dateDepart.jour >> dateDepart.mois >> dateDepart.annee;
        cout << "Date d'arrivée (jour mois annee) : ";
        cin >> dateArrivee.jour >> dateArrivee.mois >> dateArrivee.annee;
        cout << "Nombre de places disponibles : ";
        cin >> placesDisponibles;
        cout << "Prix : ";
        cin >> prix;

        // Créer le vol et l'ajouter à la liste
        Vol vol(numeroVol, aeroportDepart, aeroportArrivee, dateDepart, dateArrivee, placesDisponibles, prix);
        listeVols.push_back(vol);
    }

    // Trier la liste des vols par date de départ
    sort(listeVols.begin(), listeVols.end(), [](const Vol& v1, const Vol& v2) {
        return comparerDates(v1.getDateDepart(), v2.getDateDepart());
    });

    // Permettre à l'utilisateur de modifier/supprimer un vol
    cout << "Voulez-vous modifier ou supprimer un vol ? (m/s) ";
    char choix;
    cin >> choix;
    if (choix == 'm') { // Modification
        // Demander à l'utilisateur le numéro du vol à modifier
        string numeroVol;
        cout << "Entrez le numéro du vol à modifier : ";
        cin >> numeroVol;

        // Rechercher le vol dans la liste
        bool trouve = false;
        for (Vol& vol : listeVols) {
            if (vol.getNumeroVol() == numeroVol) {
                // Demander à l'utilisateur de saisir les nouvelles informations
                string newNumeroVol, newAeroportDepart, newAeroportArrivee;
                Date newDateDepart, newDateArrivee;
                int newPlacesDisponibles;
                double newPrix;

                cout << "Entrez le nouveau numéro de vol : ";
                cin >> newNumeroVol;
                cout << "Entrez le nouvel aéroport de départ : ";
                cin >> newAeroportDepart;
                cout << "Entrez le nouvel aéroport d'arrivée : ";
                cin >> newAeroportArrivee;
                cout << "Entrez la nouvelle date de départ (jour mois annee) : ";
                cin >> newDateDepart.jour >> newDateDepart.mois >> newDateDepart.annee;
                cout << "Entrez la nouvelle date d'arrivée (jour mois annee) : ";
                cin >> newDateArrivee.jour >> newDateArrivee.mois >> newDateArrivee.annee;
                cout << "Entrez le nouveau nombre de places disponibles : ";
                cin >> newPlacesDisponibles;
                cout << "Entrez le nouveau prix : ";
                cin >> newPrix;

                // Modifier les informations du vol
                vol.setNumeroVol(newNumeroVol);
                vol.setAeroportDepart(newAeroportDepart);
                vol.setAeroportArrivee(newAeroportArrivee);
                vol.setDateDepart(newDateDepart);
                vol.setDateArrivee(newDateArrivee);
                vol.setPlacesDisponibles(newPlacesDisponibles);
                vol.setPrix(newPrix);

                trouve = true;
                break;
            }
        }

        if (!trouve) {
            cout << "Vol non trouvé !" << endl;
        }
    } else if (choix == 's') { // Suppression
        // Demander à l'utilisateur le numéro du vol à supprimer
        string numeroVol;
        cout << "Entrez le numéro du vol à supprimer : ";
        cin >> numeroVol;

        // Rechercher le vol dans la liste
        auto it = find_if(listeVols.begin(), listeVols.end(), [&numeroVol](const Vol& vol) {
            return vol.getNumeroVol() == numeroVol;
        });

        if (it != listeVols.end()) {
            listeVols.erase(it);
            cout << "Vol supprimé avec succès !" << endl;
        } else {
            cout << "Vol non trouvé !" << endl;
        }
    } else {
        cout << "Choix invalide !" << endl;
    }

    
    
    
    // Afficher le nombre de places qui restent dans chaque vol dont la date de départ est dans 3 mois
        Date currentDate = {20, 4, 2024}; // Date actuelle (jour, mois, année)

        cout << "Nombre de places restantes dans les vols dont la date de départ est dans 3 mois :" << endl;
        for (const Vol& vol : listeVols) {
            Date troisMoisPlusTard = {currentDate.jour, currentDate.mois + 3, currentDate.annee};

            if (vol.getDateDepart().annee == troisMoisPlusTard.annee &&
                vol.getDateDepart().mois == troisMoisPlusTard.mois &&
                vol.getDateDepart().jour >= currentDate.jour) {
                cout << "Vol " << vol.getNumeroVol() << " : " << vol.getPlacesDisponibles() << " places restantes." << endl;
            } else if (vol.getDateDepart().annee == troisMoisPlusTard.annee &&
                       vol.getDateDepart().mois > troisMoisPlusTard.mois &&
                       currentDate.mois + 3 <= 12) {
                cout << "Vol " << vol.getNumeroVol() << " : " << vol.getPlacesDisponibles() << " places restantes." << endl;
            } else if (vol.getDateDepart().annee > troisMoisPlusTard.annee) {
                cout << "Vol " << vol.getNumeroVol() << " : " << vol.getPlacesDisponibles() << " places restantes." << endl;
            }
        }

        // Augmenter le prix du vol de 10% si la date du départ est dans deux mois
        cout << "Augmentation de prix pour les vols dont la date de départ est dans deux mois :" << endl;
        for (Vol& vol : listeVols) {
            Date deuxMoisPlusTard = {currentDate.jour, currentDate.mois + 2, currentDate.annee};

            if (vol.getDateDepart().annee == deuxMoisPlusTard.annee &&
                vol.getDateDepart().mois == deuxMoisPlusTard.mois &&
                vol.getDateDepart().jour >= currentDate.jour) {
                vol.augmenterPrix();
                cout << "Prix du vol " << vol.getNumeroVol() << " augmenté de 10%." << endl;
            } else if (vol.getDateDepart().annee == deuxMoisPlusTard.annee &&
                       vol.getDateDepart().mois > deuxMoisPlusTard.mois &&
                       currentDate.mois + 2 <= 12) {
                vol.augmenterPrix();
                cout << "Prix du vol " << vol.getNumeroVol() << " augmenté de 10%." << endl;
            } else if (vol.getDateDepart().annee > deuxMoisPlusTard.annee) {
                vol.augmenterPrix();
                cout << "Prix du vol " << vol.getNumeroVol() << " augmenté de 10%." << endl;
            }
        }


         // Création de l'ensemble des passagers
    set <Passager> ensemblePassagers;

    // Demander à l'utilisateur de remplir l'ensemble des passagers
    int nombrePassagers;
    cout << "Combien de passagers souhaitez-vous ajouter ? ";
    cin >> nombrePassagers;

    for (int i = 0; i < nombrePassagers; ++i) {
        int idPassager;
        string nom, telephone, passeport;

        cout << "Passager #" << i + 1 << ":" << endl;
        cout << "ID du passager : ";
        cin >> idPassager;
        cout << "Nom du passager : ";
        cin >> nom;
        cout << "Numéro de téléphone : ";
        cin >> telephone;
        cout << "Numéro de passeport : ";
        cin >> passeport;

        // Créer le passager et l'ajouter à l'ensemble
        Passager passager(idPassager, nom, telephone, passeport);
        ensemblePassagers.insert(passager);
    }

    // Afficher le nombre de réservations effectuées par un passager
    for (const Passager& passager : ensemblePassagers) {
        cout << "Passager " << passager.getNom() << " : " << passager.getNombreReservations() << " réservations." << endl;
    }

    // Réduction de 20% sur le total à payer si le nombre de réservations est supérieur à 5
    for (const Passager& passager : ensemblePassagers) {

        if (passager.getNombreReservations() > 5) {
            // Appliquer la réduction sur le total à payer du passager
            // Code pour appliquer la réduction
        }
    }

    // Afficher la facture de paiement pour chaque passager
    for (const Passager& passager : ensemblePassagers) {
        passager.FacturePaiement();
    }




// Dans la fonction main après la saisie des vols et des passagers

// Créer un map pour stocker les réservations
std::map<int, Reservation> mapReservations;

// Demander à l'utilisateur de remplir le map avec les réservations
int nombreReservations;
cout << "Combien de réservations souhaitez-vous ajouter ? ";
cin >> nombreReservations;

for (int i = 0; i < nombreReservations; ++i) {
    int idReservation;
    Date dateReservation;
    const Passager* passager = nullptr; // Initialisation à nullptr pour le cas où le passager n'est pas trouvé   ***const pour ne pas modifier dans l'objet original
    Vol* vol = nullptr; // Initialisation à nullptr pour le cas où le vol n'est pas trouvé
    Paiement* paiement = nullptr; // Initialisation à nullptr pour le cas où le paiement n'est pas trouvé

    cout << "Réservation #" << i + 1 << ":" << endl;
    cout << "ID de la réservation : ";
    cin >> idReservation;
    cout << "Date de la réservation (jour mois annee) : ";
    cin >> dateReservation.jour >> dateReservation.mois >> dateReservation.annee;

    // Demander à l'utilisateur de saisir l'ID du passager
    int idPassager;
    cout << "ID du passager : ";
    cin >> idPassager;

    // Rechercher le passager correspondant dans l'ensemble des passagers
    for (const Passager& p : ensemblePassagers) {
        if (p.getIdPassager() == idPassager) {
            passager = &p;
            break;
        }
    }

    if (passager == nullptr) {
        cout << "Passager non trouvé !" << endl;
        // Gérer le cas où le passager n'est pas trouvé
        continue; // Passer à la prochaine itération de la boucle
    }

    // Demander à l'utilisateur de saisir le numéro du vol
    string numeroVol;
    cout << "Numéro du vol : ";
    cin >> numeroVol;

    // Rechercher le vol correspondant dans la liste des vols
    for ( Vol& v : listeVols) {
        if (v.getNumeroVol() == numeroVol) {
            vol = &v;
            break;
        }
    }

    if (vol == nullptr) {
        cout << "Vol non trouvé !" << endl;
        // Gérer le cas où le vol n'est pas trouvé
        continue; // Passer à la prochaine itération de la boucle
    }

//     // Demander à l'utilisateur de saisir les informations sur le paiement (à compléter selon vos besoins)

//     // Créer l'objet réservation avec les informations saisies
//     Reservation reservation(idReservation, dateReservation, passager, vol, paiement);

//     // Stocker la réservation dans le map associée à son ID
//     mapReservations[idReservation] = reservation;
}


        return 0;
    }