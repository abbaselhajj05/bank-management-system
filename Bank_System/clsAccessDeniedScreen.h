#pragma once
#include "clsScreen.h"

class clsAccessDeniedScreen : public clsScreen {
private:

public:
	static void showAccessDeniedScreen() {
		_drawScreenHeader("Access Denied!", "Contact your admin for more info.");
	}
};

