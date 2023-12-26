#pragma once
#include <stdexcept>
#include <iostream>
#include <cmath>
#include "VanillaOption.h"
#include "OptionType.h"
#include "DigitalOption.h"


class BlackScholesPricer 
{
    private:
    #pragma region attributes
        Option* option;
        double asset_price;
        double interest_rate;
        double volatility;
        bool vanilla; //true for VanillaOption and false for DigitalOption
    #pragma endregion

    public:
        // BlackScholes Pricer constructor
            BlackScholesPricer(VanillaOption* option, double asset_price, double interest_rate, double volatility)
                : option(option), asset_price(asset_price), interest_rate(interest_rate), volatility(volatility), vanilla(true) {}

            BlackScholesPricer(DigitalOption* option, double asset_price, double interest_rate, double volatility)
            : option(option), asset_price(asset_price), interest_rate(interest_rate), volatility(volatility), vanilla(false) {}
 
        /// <summary>
        /// 
        /// </summary>
        /// <returns> the price of the option </returns>
        double operator()();

        /// <summary>
        /// Delta method to calculate the Delta of the option
        /// </summary>
        /// <returns> the Delta of the option </returns>
        double delta();
};

/// <summary>
/// Distribution function of the normal law
/// </summary>
/// <param name="x"> a double </param>
/// <returns> the value of the distribution function of the normal law </returns>
double N(double x);