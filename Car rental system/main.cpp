#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <string>
#include <cstring>
#include <cstdio>
#include <Windows.h>	// For sleep function
#include <fstream>		// For file stream
#include <sstream>		// For stringstream (Objectifying string for manipulation)
#include <iomanip>		// For customer id formatting
#include <cstdlib>		// For srand
#include <vector>		// For variable size array
#include <ctime>
#include <map>
#include <random>
#include <chrono>
#include <thread>

#include "items.h"
#include "user.h"
#include "AdminFunctions.h"
#include "CustomerFunctions.h"

using namespace std;

int main() {
	string opt;
	do {
		system("cls");
		cout << "\n\n\tWelcome to HORIZON [Car Rental Platform]" << endl;
		cout << "\t------------------------------------------------" << endl;
		cout << "\tPlease enter your authorization:" << endl;
		cout << "\t1. Administrator\n\t2. Customer\n\n\tOption [-1 to exit]: ";
		getline(cin, opt);

		if (opt == "1") {
			Admin admin;
			if (admin.authenticate()) {
				int opt;
				do {
					opt = admin.adminMenu();
					switch (opt) {
					case 1:
						admin.editUser();
						break;
					case 2:
						admin.deleteUser();
						break;
					case 3:
						admin.addVehicle();
						break;
					case 4:
						admin.editVehicle();
						break;
					case 5:
						admin.deleteVehicle();
						break;
					case 6:
						admin.viewVehicle();
						break;
					case 7:
						admin.searchVehicle();
						break;
					case 8:
						admin.viewBooking();
						break;
					case 9:
						admin.editBooking();
						break;
					case 10:
						admin.reportAnalysis();
						break;
					case -1:
						break;
					default:
						cout << "\n\tInvalid input.\n\n\t[Press enter to continue]" << endl;
						while (getchar() != '\n');
						break;
					}
				} while (opt != -1);
			};
		}
		else if (opt == "2") {
			system("cls");
			cout << "\n\n\tCustomer account portal:-" << endl;
			cout << "\t------------------------------------------------" << endl;
			cout << "\tPlease select account:" << endl;
			cout << "\t1. Login\n\t2. Register\n\n\tOption [-1 to exit]: ";
			getline(cin, opt);

			if (opt == "1") {
				Customer customer;
				if (customer.authenticate()) {
					int opt = 0;
					do {
						opt = customer.customerMenu();
						switch (opt) {
						case 1:
							customer.viewVehicle();
							break;
						case 2:
							customer.searchVehicle();
							break;
						case 3:
							customer.bookVehicle();
							break;
						case 4:
							customer.pickUpAndReturn();
							break;
						case 5:
							customer.review();
							break;
						case -1:
							break;
						default:
							cout << "\n\tInvalid input.\n\n\t[Press enter to continue]" << endl;
							while (getchar() != '\n');
							break;
						}
					} while (opt != -1);
				}
			}
			else if (opt == "2") {
				Customer customer;
				customer.regUser();
			}
			else if (opt == "-1") {
				opt = "0";
			}
			else {
				cout << "\n\tInvalid input.\n\n\t[Press enter to continue]" << endl;
				while (getchar() != '\n');
			}
		}
		else if (opt == "-1") {
			cout << "\n\tSystem has been shut down.";
		}
		else {
			cout << "\n\tInvalid input.\n\n\t[Press enter to continue]" << endl;
			while (getchar() != '\n');
		}
	} while (opt != "-1");
	
	return 0;
}