#pragma once
#include <stdexcept>
#include <iostream>
#include <cmath>
#include "Option.h"
#include "MT.h"
#include <vector>

class BlackScholesMCPricer {
private:
    Option* option;
    double initialPrice;
    double interestRate;
    double volatility;
    int numberPaths; //unsigned pour que ce soit que des valeurs non n�gatives
    double currentEstimate;

public:
    BlackScholesMCPricer(Option* option, double initialPrice, double interestRate, double volatility)
        : option(option), initialPrice(initialPrice), interestRate(interestRate), volatility(volatility), numberPaths(0), currentEstimate(0.0){}

    int getNbPaths() const
    {
        return numberPaths;
    }

    void generate(int nb_paths)
    {// M�thode pour g�n�rer des chemins

        for (int i = 0; i < nb_paths; ++i) {
            double path = initialPrice;

            // Formule de Black-Scholes pour g�n�rer des chemins
            double drift = exp((interestRate - 0.5 * volatility * volatility) * 1.0);
            double diffusion = exp(volatility * sqrt(1.0) * MT::rand_norm());

            path = path * drift * diffusion;

            // Mettre � jour le nombre de chemins g�n�r�s
            numberPaths++;

            //UPDATES the current estimate of the price of the option
            //m�thode existante dans la classe BS Pricer ? TEST
            double optionPrice; //= option->computeOptionPrice(path);
            currentEstimate = ((currentEstimate * numberPaths) + optionPrice) / (numberPaths + 1);
        }
    }

    double operator()()
    {
        if (numberPaths == 0) {
            throw std::runtime_error("Current estimate is undefined. No paths have been generated.");
        }
        return currentEstimate;
    }

    
};
