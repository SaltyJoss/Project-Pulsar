#include "pch.h"
#include "Application.h"


// Global Variables
Debug gLog; // Global Log Variable

// Main method fpr 
int main() {
	auto app = std::make_unique<Application>("Simulator V0.1");

	app->run();

	return 0;
}