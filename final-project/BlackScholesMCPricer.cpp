#include "BlackScholesMCPricer.h"
#include"BlackScholesPricer.h"
#include "Option.h"
#include "AsianOption.h"
#include "VanillaOption.h"
#include "MT.h"
#include <cmath>
#include <vector>


void BlackScholesMCPricer::generate(int nb_paths)
{    
    //timeStepsVect =     
    if (option->isAsianOption())
    {
        timeStepsVect = ((AsianOption*)option)->getTimeSteps();
    }
    else
    {
        //timeStepsVect[timeStepsVect.size()]
        
        timeStepsVect = {option->getExpiry()}; //� la place du 1 : maturity � r�cup de ?
        //ici on d�finit le vecteur time steps d'une option europ�enne --> juste 2 time steps
    }
    
    
    double avgPrice = 0;
    double payoff = 0;
    double sumPayoffs = 0;
    

    // M�thode pour g�n�rer des chemins
    for (int i = 0; i < nb_paths; ++i) {
        //de k=1 � n
        // calcul de S_t0
        double pathPrice = initialPrice;
        
        std::vector<double> prices;

        pathPrice = pathPrice * exp((interestRate - 0.5 * volatility * volatility)*timeStepsVect[0] + volatility*sqrt(timeStepsVect[0])*MT::rand_norm());
        prices.push_back(pathPrice);
        // Formule de Black-Scholes pour g�n�rer des chemins
        for (int k = 1; k < timeStepsVect.size(); k++) {

            // Formule de Black-Scholes pour g�n�rer des chemins
            double drift = exp((interestRate - 0.5 * volatility * volatility) * (timeStepsVect[k] - timeStepsVect[k - 1]));
            double diffusion = exp(volatility * sqrt(timeStepsVect[k] - timeStepsVect[k - 1]) * MT::rand_norm());

            pathPrice = pathPrice * drift * diffusion;
            prices.push_back(pathPrice);
        }

        payoff = option->payoffPath(prices);
        payoffs.push_back(payoff);
    }
    
    
    //Ici on fait la moyenne des prix du SJ
    //priceSJ = sumPaths / numberPaths;

    for (int j = 0; j < payoffs.size(); j++)
    {
        sumPayoffs += payoffs[j] ;  //pour actualiser
    }

    double price = exp(-interestRate * option->getExpiry())*1/payoffs.size()*sumPayoffs;
    
    double squaredSum = 0.0;
    for (int i = 0; i < payoffs.size(); ++i) {
        squaredSum = squaredSum + pow(payoffs[i],2);
    }
    empVar = squaredSum/payoffs.size() - sumPayoffs / payoffs.size();
    numberPaths = payoffs.size();
    finalPrice = price;
}

double BlackScholesMCPricer::operator()()
{
    if (numberPaths == 0) {
        //throw std::invalid_argument(" numberPaths doit �tre diff�rent de 0."); // comment� car cause bug, � r�gler
    }
    return finalPrice;
}

std::vector<double> BlackScholesMCPricer::confidenceInterval()
{
    double lowerBound = finalPrice - 1.96 * (sqrt(empVar) / std::sqrt(numberPaths));
    double upperBound = finalPrice + 1.96 * (sqrt(empVar) / std::sqrt(numberPaths));
    return { lowerBound, upperBound };
}



