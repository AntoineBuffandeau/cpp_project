#pragma once
#include <random>
class MT {
private:
    std::mt19937 rng; // Instance unique de std::mt19937 // G�n�rateur de nombres al�atoires Mersenne Twister

    // Constructeur priv� pour emp�cher l'instanciation directe
    MT();

public:
    // Fonction pour obtenir l'instance unique de la classe
    static MT & getInstance()
    {
        static MT instance; // Constructed only once
        return instance;
    }

    // M�thodes statiques pour g�n�rer des nombres al�atoires
    static double rand_unif();

    static double rand_norm();
};
