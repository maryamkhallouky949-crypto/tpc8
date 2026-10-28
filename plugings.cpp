
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <cctype>

using namespace std;
class CorrecteurOrthographique;
class TraducteurAnglais;

class AnalyseurStyle;
class Plugin {
public:
    virtual string nom() const = 0;
    virtual string traiter(const string& texte) = 0;

    virtual ~Plugin() {}


    static unique_ptr<Plugin> creerPlugin(const string& type);
};


class CorrecteurOrthographique : public Plugin {
public:
    string nom() const override {
        return "Correcteur orthographique";
    }

     string traiter(const string& texte) override {
    string resultat = texte;

    vector<pair<string, string>> traductions = {
        {"bonjour", "hello"},
        {"Bonjour", "Hello"},
        {"monde", "world"},
        {"ordinateur", "computer"},
        {"maison", "house"},
        {"livre", "book"},
        {"chat", "cat"},
        {"merci", "thank you"},
        {"ami", "friend"}
    };


        for (const auto& traduction : traductions) {
            size_t position = 0;

            while ((position = resultat.find(
                traduction.first, position
            )) != string::npos) {
                resultat.replace(
                    position,
                    traduction.first.length(),
                    traduction.second
                );

                position += traduction.second.length();
            }
        }

        if (resultat.rfind("bonjor ", 0) == 0) {
            resultat.replace(0, 6, "bonjour");
        }

        if (resultat.rfind("bonjourr ", 0) == 0) {
            resultat.replace(0, 8, "bonjour");
        }

        return resultat;
    }
};

class TraducteurAnglais : public Plugin {
public:
    string nom() const override {
        return "Traducteur anglais";
    }

   string traiter(const string& texte) override {
    string resultat = texte;

    vector<pair<string, string>> traductions = {
        {"bonjour", "hello"},
        {"Bonjour", "Hello"},
        {"monde", "world"},
        {"ordinateur", "computer"},
        {"maison", "house"},
        {"livre", "book"},
        {"chat", "cat"},
        {"merci", "thank you"},
        {"ami", "friend"}
    };

        for (const auto& traduction : traductions) {
            size_t position = 0;

            while ((position = resultat.find(
                traduction.first, position
            )) != string::npos) {
                resultat.replace(
                    position,
                    traduction.first.length(),
                    traduction.second
                );

                position += traduction.second.length();
            }
        }

        return resultat;
    }
};
class AnalyseurStyle : public Plugin {
public:
    string nom() const override {
        return "Analyseur de style";
    }

    string traiter(const string& texte) override {
        int nombreLongues = 0;
        int longueur = 0;

        for (char caractere : texte) {
            if (caractere == '.' ||
                caractere == '!' ||
                caractere == '?') {

                if (longueur > 100) {
                    nombreLongues++;
                }

                longueur = 0;
            } else {
                longueur++;
            }
        }
        if (longueur > 100) {
            nombreLongues++;
        }

        string resultat = texte;

        if (nombreLongues > 0) {
            resultat += "[Analyse de style : ";
            resultat += to_string(nombreLongues);
            resultat += " phrase(s) trop longue(s).]";
        } else {
            resultat += "[Analyse de style : aucune phrase trop longue.]";
        }

        return resultat;
    }
};
unique_ptr<Plugin> Plugin::creerPlugin(const string& type) {
    if (type == "correcteur") {
        return make_unique<CorrecteurOrthographique>();
    }

    if (type == "traducteur") {
        return make_unique<TraducteurAnglais>();
    }

    if (type == "analyseur") {
        return make_unique<AnalyseurStyle>();
    }

    return nullptr;
}

int main() {
    string texte;

    cout << "Entrez un texte : ";
    getline(cin, texte);

    vector<unique_ptr<Plugin>> plugins;

    plugins.push_back(Plugin::creerPlugin("correcteur"));
    plugins.push_back(Plugin::creerPlugin("traducteur"));
    plugins.push_back(Plugin::creerPlugin("analyseur"));

    cout << " Traitement du texte";

    for (const auto& plugin : plugins) {
        if (plugin != nullptr) {
            texte = plugin->traiter(texte);

            cout << "\nPlugin applique : "
                 << plugin->nom() << endl;

            cout << "Texte obtenu :\n"
                 << texte << endl;
        }
    }

    return 0;
}
