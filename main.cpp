
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

struct Patient {
    std::string nom;
    std::string prenom;
    int age;
    std::string date_arrivee;
    std::string date_sortie;
    std::string maladie;
};

void saisir_patient(std::vector<Patient>& patients) {
    Patient p;
    std::cout << "Nom: ";
    std::cin >> p.nom;
    std::cout << "Prenom: ";
    std::cin >> p.prenom;
    std::cout << "Age: ";
    std::cin >> p.age;
    std::cout << "Date d'arrivee (jj/mm/aaaa): ";
    std::cin >> p.date_arrivee;
    std::cout << "Maladie:";
    std::cin.ignore();
    std::getline(std::cin, p.maladie);
    p.date_sortie = "";
    patients.push_back(p);
}

void recherche_patient(std::vector<Patient>& patients) {
    std::string nom, prenom;
    std::cout << "Nom: ";
    std::cin >> nom;
    std::cout << "Prenom: ";
    std::cin >> prenom;

    for (auto& p : patients) {
        if (p.nom == nom && p.prenom == prenom) {
            std::cout << "Date de sortie (jj/mm/aaaa): ";
            std::cin >> p.date_sortie;
            return;
        }
    }

std::cout<<"Patient non trouve."<<std::endl;
}

void modifier_patient(std::vector<Patient>& patients) {
std::string nom, prenom;
std::cout<<"Nom : ";
std::cin>>nom;
std::cout<<"Prenom : ";
std::cin>>prenom;

for(auto& p : patients){
if(p.nom==nom && p.prenom==prenom){
int choix = 0;
while(choix!=6){
std::cout<<"1. Modifier le nom"<<std::endl;
std::cout<<"2. Modifier le prenom"<<std::endl;
std::cout<<"3. Modifier l'age"<<std::endl;
std::cout<<"4. Modifier la date d'arrivee"<<std::endl;
std::cout<<"5. Modifier la maladie"<<std::endl;
std::cout<<"6. Quitter"<<std::endl;
std::cin>>choix;
switch(choix){
case 1:
std::cout<<"Nouveau nom : ";
std::cin>>p.nom;
break;
case 2:
std::cout<<"Nouveau prenom : ";
std::cin>>p.prenom;
break;
case 3:
std::cout<<"Nouvel age : ";
std::cin>>p.age;
break;
case 4:
std::cout<<"Nouvelle date d'arrivee : ";
std::cin>>p.date_arrivee;
break;
case 5:
std::cout<<"Nouvelle maladie : ";
std::cin.ignore();
getline(std::cin, p.maladie);
break; }
}
return; }
}

std::cout<<"Patient non trouve."<<std::endl; }

void afficher_patient(const Patient& p) {
std::cout<<"Nom : "<<p.nom<<std::endl;
std::cout<<"Prenom : "<<p.prenom<<std::endl;
std::cout<<"Age : "<<p.age<<std::endl;
std::cout<<"Date d'arrivee : "<<p.date_arrivee<<std::endl;
if(p.date_sortie!=""){
std::cout<<"Date de sortie : "<<p.date_sortie<<std::endl; }
else{
std::cout<<"Date de sortie : N/A"<<std::endl;}
std::cout<<"Maladie : "<<p.maladie<<std::endl;}

void afficher_tous_les_patients(const std::vector<Patient>& patients) {
    for (const auto& p : patients) {
        afficher_patient(p);
        std::cout << "---" << std::endl;
    }
}

void sauvegarder_dans_fichier(const char* filename, const Patient& p){
// Ouvrir le fichier en mode append

std::ofstream file(filename, std::ios_base::app);


// Ecrire les informations du patient dans le fichier
file<<p.nom<<"\n";
file<<p.prenom<<"\n";
file<<p.age<<"\n";
file<<p.date_arrivee<<"\n";

// Si la date de sortie est vide, ecrire N/A
if(p.date_sortie==""){
file<<"N/A\n";
}
else{
file<<p.date_sortie<<"\n";
}

file<<p.maladie<<"\n";

// Fermer le fichier
file.close();
}

void charger_depuis_fichier(const char* filename, std::vector<Patient>& patients){
// Ouvrir le fichier en mode lecture
std::ifstream file(filename);
if(!file.is_open()) return;

// Lire les informations des patients depuis le fichier
while(!file.eof()){
Patient p;

// Lire les informations du patient
std:getline(file, p.nom);
if(p.nom=="") break; // Fin du fichier
std::getline(file, p.prenom);
file>>p.age; file.ignore();
std::getline(file, p.date_arrivee);
std::getline(file, p.date_sortie);
if(p.date_sortie=="N/A"){
p.date_sortie="";
}
std::getline(file, p.maladie);

// Ajouter le patient à la liste des patients
patients.push_back(p);
}

// Fermer le fichier
file.close();
}

int main(){
const char* filename = "patients.txt";
std::vector<Patient> patients;

// Charger les données depuis le fichier
charger_depuis_fichier(filename, patients);

int choix = 0;

while(choix!=6){
    std::cout<<std::endl<<"Menu"<<
    std::endl<<"1. Saisir un patient"<<
    std::endl<<"2. Rechercher un patient"<<
    std::endl<<"3. Modifier un patient"<<
    std::endl<<"4. Afficher un patient"<<
    std::endl<<"5. Afficher tous les patients"<<
    std::endl<<"6. Quitter"<<std::endl;
    std::cin>>choix;

    if ( choix >7)
    {
     while (!(std::cin >> choix) || choix >= 10) {
        std::cout << "Erreur! Entrez un entier < 7: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    }

    switch(choix){
        case 1:
                saisir_patient(patients);
                sauvegarder_dans_fichier(filename, patients.back());
        break;

        case 2:
            recherche_patient(patients);
        break;

        case 3:
            modifier_patient(patients);
        break;

        case 4:
            {
                std::string nom, prenom;
                std::cout<<"Nom : "; std::cin>>nom; std::cout<<"Prenom : "; std::cin>>prenom; for(const auto& p : patients)
                {
                if(p.nom==nom && p.prenom==prenom){
                afficher_patient(p); break; }
               }
        break;}

        case 5:
            afficher_tous_les_patients(patients);
        break; }
}

return 0;
}
