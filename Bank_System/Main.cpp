#include <iostream>
#include "clsLoginScreen.h"
#include "clsCurrency.h"
using namespace std;

int main() {
	
	while (true) {
		if (!clsLoginScreen::showLoginScreen())
			break;
	}

	/*clsCurrency* currency1 = clsCurrency::findByCode("lbp");

	if (currency1) {
		currency1->updateRate(1515);
		_printCurrency(currency1);
	}
		
	else cout << "\nCurrency Not Found!\n";

	clsCurrency* currency2 = clsCurrency::findByCountry("egypt");

	if (currency2)
		_printCurrency(currency2);
	else cout << "\nCurrency Not Found!\n";*/

	return 0;
}