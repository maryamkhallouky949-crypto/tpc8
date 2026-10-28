
#include <iostream>
#include <string>
using namespace std;


class SortieAudio {
public:
    virtual void ouvrir() = 0;
    virtual void jouer(const string& son) = 0;
    virtual void fermer() = 0;

    
    virtual ~SortieAudio() {
        cout << "Destruction d'une sortie audio" << endl;
    }
};


class HautParleur : public SortieAudio {
public:
    void ouvrir() override {
        cout << "Haut-parleur ouvert." << endl;
    }

    void jouer(const string& son) override {
        cout << "Haut-parleur : lecture de " << son << endl;
    }

    void fermer() override {
        cout << "Haut-parleur ferme." << endl;
    }
};
class CasqueBT : public SortieAudio {
public:
    void ouvrir() override {
        cout << "Casque Bluetooth connecte." << endl;
    }

    void jouer(const string& son) override {
        cout << "Casque Bluetooth : lecture de " << son << endl;
    }

    void fermer() override {
        cout << "Casque Bluetooth deconnecte." << endl;
    }
};

class SortieHDMI : public SortieAudio {
public:
    void ouvrir() override {
        cout << "Sortie HDMI activee." << endl;
    }

    void jouer(const string& son) override {
        cout << "HDMI : lecture de " << son << endl;
    }

    void fermer() override {
        cout << "Sortie HDMI desactivee." << endl;
    }
};
void tester(SortieAudio* sortie) {
    sortie->ouvrir();
    sortie->jouer("musique.mp3");
    sortie->fermer();

}

int main() {

    SortieAudio* sorties[3];

    sorties[0] = new HautParleur();
    sorties[1] = new CasqueBT();
    sorties[2] = new SortieHDMI();

    for (int i = 0; i < 3; i++) {
        tester(sorties[i]);
    }
    for (int i = 0; i < 3; i++) {
        delete sorties[i];
    }

    return 0;
}
