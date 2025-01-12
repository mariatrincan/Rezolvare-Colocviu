#include<iostream>
#include<string>
#include<vector>
#include <algorithm>
#include <exception>
using namespace std;

class Eroare : public exception {

    public:
    virtual const char* what() const throw() {
        return "Eroare";
    }
};

class Proba {
protected:
    int lungime;
    string tip_masura;
    int dt;
    string denumire_proba;
    string tip_proba;

public:
      Proba() {}
      string DenumireProba() {return denumire_proba;}
      virtual int Estimare()=0;
      virtual void getDate()=0;
      string Tip_Proba() {return tip_proba;}
      friend istream& operator>>(istream& in, Proba& p);
};
istream& operator>>(istream& in, Proba& p) {
    cout<<"Numele probei: ";
    in>>p.denumire_proba;
    return in;
}

class Sprint : public Proba {
    public:
        int Estimare() ;
        void getDate();
        Sprint() {lungime=100; tip_masura= "m"; tip_proba="Sprint";}
        ~Sprint() {}
};
int Sprint::Estimare() {
    if (dt<10) return 10;
    else return 90/dt;
}
void Sprint::getDate() {
    cin>> *this;
    cout<<"Timpul probei: ";
    cin>>dt;
}

class Cros : public Proba {
    public:
        int Estimare();
        void getDate();
        Cros() {lungime=100; tip_masura= "km"; tip_proba="Cros";}
        ~Cros() {}
};

int Cros::Estimare() {
    if (dt<30) return 10;
    else return 120/dt;
}

void Cros::getDate() {
    cin>>*this;
    cout<<"Timpul probei: ";
    cin>>dt;
}

class Semi_maraton : public Proba {
    public:
    int Estimare();
    void getDate();
    Semi_maraton() {lungime=21; tip_masura="km"; tip_proba="Semi_maraton";}
    ~Semi_maraton() {}
};

int Semi_maraton::Estimare() {
    if (dt>50) return 10;
    else return dt/5;

}

void Semi_maraton::getDate() {
    cin>>*this;
    cout<<"Distanta probei: ";
    cin>>dt;
}

class Maraton : public Proba {
    public:
    int Estimare();
    void getDate();
    Maraton() {lungime=42; tip_masura= "km"; tip_proba="Maraton";}
    ~Maraton() {}
};

int Maraton::Estimare() {
    if (dt>50) return 10;
    else return dt/5;
}

void Maraton::getDate() {
    cin>>*this;
    cout<<"Distanta probei: ";
    cin>>dt;
}

class Candidat {
private:
    string nume;
    string prenume;
    string data_nasterii;
    Proba* proba;
    int val;
public:
    Proba* TipuldeProba() {return proba;}
    int getVal() const { return val;}
    friend istream& operator>>(istream& in, Candidat& candidat);
    friend ostream& operator<<(ostream& os, Candidat& candidat);
    Candidat() {}
    ~Candidat() {}
};
ostream& operator<<(ostream& os, Candidat& candidat) {
    os<<"Nume si prenume candidat: "<<candidat.nume<<" "<<candidat.prenume<<endl<<"Data nasterii: "<<candidat.data_nasterii<<endl<<"Participant la:"<<candidat.proba->Tip_Proba()<<" "<<candidat.proba->DenumireProba()<<endl;
    os<<"Valoarea candidatului: "<<candidat.val<<endl;
    return os;
}

istream& operator>>(istream& in, Candidat& candidat) {
    cout<<"Nume: ";
    in>>candidat.nume;
    cout<<"Prenume: ";
    in>>candidat.prenume;
    cout<<"Data nasterii: ";
    in>>candidat.data_nasterii;
    cout<<"Participant la proba:(1-sprint, 2-cros, 3-semi-maraton, 4-maraton): ";
    int input;
    cin>>input;
    switch (input) {
        case 1:
            candidat.proba = new Sprint();
            candidat.proba->getDate();
            break;
        case 2:
            candidat.proba = new Cros();
            candidat.proba->getDate();
            break;
        case 3:
            candidat.proba = new Semi_maraton();
            candidat.proba->getDate();
            break;
        case 4:
            candidat.proba = new Maraton();
            candidat.proba->getDate();
            break;
        default:
            cout<<"Proba a fost aleasa gresit!"<<endl;
    }
    candidat.val=candidat.proba->Estimare();
    return in;
}


class Meniu_Interactiv {
    private:
    int nr_candidati;
    const string cod_admin;
    vector<Candidat> candidati;
    vector<Candidat> admis;
    Meniu_Interactiv() : cod_admin("admin"), nr_candidati(0) {}
    ~Meniu_Interactiv() {}

    public:
        static Meniu_Interactiv& instance() {
            static Meniu_Interactiv* newMeniu_Interactiv= new Meniu_Interactiv();
            return *newMeniu_Interactiv;
        }

    void run();
};

void Meniu_Interactiv::run() {
    cout<<"Meniu Interactiv: "<<endl;
    while (1) {

        try {
            cout<<"1. Adaugati numarul de candidati"<<endl;
            cout<<"2. Icheiati inscrierile pentru a afisa numarul de candidati admisi"<<endl;
            cout<<"3. Iesire program"<<endl;
            int input;
            cin>>input;
            string parola_admin;
            switch (input) {
                case 1:
                    cout<<"Numarul de candidati: ";
                    int nr,i;
                    cin>>nr;
                    if (nr<=0)
                        throw Eroare();
                    for (i=0; i<nr; i++ ) {
                        candidati.push_back(Candidat());
                        cin>>candidati[nr_candidati];
                        nr_candidati++;
                    }
                break;
                case 2:
                    cout<<"Cod admin: ";
                    cin>>parola_admin;
                    if (parola_admin=="admin") {
                        if(nr_candidati > 500) {
                            sort(candidati.begin(), candidati.end(), [](Candidat& c1, Candidat& c2) {
                                return c1.getVal() < c2.getVal();
                            });
                            for(int i = 0 ; i < 500; i++){
                                cout << candidati[i];
                            }
                        } else {
                            throw Eroare();
                        }
                    }

                break;
                case 3:
                     cout<<"Iesire din program"<<endl;
                     return;
            }

            }     catch (const Eroare& err) {
                cout<<err.what()<<endl;
            }
        }


    }

    int main () {

        Meniu_Interactiv :: instance().run();
        return 0;
    }