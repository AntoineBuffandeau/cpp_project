#pragma once
#include "DigitalOption.h"
#include "OptionType.h"

class DigitalPutOption : DigitalOption {
private:
	DigitalOption* dOption;
public:
	DigitalPutOption(double exp, double strk) : DigitalOption(exp, strk){}
	enum OptionType GetOptionType() const;
	double payoff(double) const;
};