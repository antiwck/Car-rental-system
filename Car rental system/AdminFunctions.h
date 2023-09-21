#ifndef ADMIN_FUNCTION_H
#define ADMIN_FUNCTION_H

int Admin::adminMenu() {
	string opt;
	int optInt;
	system("cls");
	cout << "\n\n\tAdmin menu:-" << endl;
	cout << "\t------------------------------------------------" << endl;
	cout << "\tPlease select one of the following operations:-\n\n\t1. Edit user\n\n\t2. Delete user\n\n\t3. Add vehicle\n\n\t4. Edit vehicle\n\n\t5. Delete vehicle\n\n\t6. View vehicle\n\n\t7. Search vehicle\n\n\t8. View booking\n\n\t9. Modify booking\n\n\t10. Report analysis" << endl;
	cout << "\n\tOption [-1 to exit]: ";
	getline(cin, opt);
	try {
		optInt = stoi(opt);
	}
	catch (...) {
		return 0;
	}
	return optInt;
}

void Admin::editUser() {
	string inputuser, line, tmp;
	system("cls");
	cout << "\n\n\tUser edit:-" << endl;
	cout << "\t------------------------------------------------" << endl;
	cout << "\tUsername [-1 to return] : ";
	getline(cin, inputuser);
	if (inputuser == "-1") {
		return;
	}

	ifstream file;
	ofstream file2;
	file.open("Resource/CustomerInfo.txt");
	file2.open("Resource/temporary.txt");

	Customer c;
	bool flg = false;
	int opt;

	while (getline(file, line)) {
		stringstream lineobj(line);
		getline(lineobj, tmp, '|');
		c.setUsername(tmp);
		getline(lineobj, tmp, '|');
		c.setPassword(tmp);
		getline(lineobj, tmp, '|');
		c.setUserID(tmp);
		getline(lineobj, tmp, '|');
		c.setName(tmp);
		getline(lineobj, tmp, '|');
		c.setContact(tmp);
		if (inputuser == c.getUsername()) {
			flg = true;
			cout << "\n\n\tWhich aspect would you like to edit?\n\t1. Username\n\t2. Password\n\t3. Name\n\t4. Contact\n\n\tOption: ";
			cin >> opt;
			cin.ignore();
			switch (opt) {
			case 1:
				cout << "\n\tNew username	: ";
				getline(cin, tmp);
				c.setUsername(tmp);
				break;
			case 2:
				cout << "\n\tNew password: ";
				getline(cin, tmp);
				c.setPassword(tmp);
				break;
			case 3:
				cout << "\n\tNew name: ";
				getline(cin, tmp);
				c.setName(tmp);
				break;
			case 4:
				cout << "\n\tNew contact: ";
				getline(cin, tmp);
				c.setContact(tmp);
				break;
			default:
				cout << "\n\tInvalid input.";
				break;
			}
			string data = c.getUsername() + '|' + c.getPassword() + '|' + c.getUserID() + '|' + c.getName() + '|' + c.getContact() + "\n";
			file2 << data;
			cout << "\n\n\tCustomer updated information:-\n\n\tUsername\t: " << c.getUsername() << "\n\tPassword\t: " << c.getPassword() << "\n\tUser ID\t\t: " << c.getUserID() << "\n\tName\t\t: " << c.getName() << "\n\tContact\t\t: " << c.getContact() << "\n\n\t[Press enter to continue]";
			while (getchar() != '\n');
		}
		else {
			file2 << line << endl;
		}
	}
	file.close();
	file2.close();
	remove("Resource/CustomerInfo.txt");
	rename("Resource/temporary.txt", "Resource/CustomerInfo.txt");

	if (flg == false) {
		cout << "\n\n\tCustomer is not found!\n\n\t[Press enter to continue]";
		while (getchar() != '\n');
	}
}

void Admin::deleteUser() {
	string inputuser, line, tmp;
	system("cls");
	cout << "\n\n\tUser delete:-" << endl;
	cout << "\t------------------------------------------------" << endl;
	cout << "\tUsername [-1 to return] : ";
	getline(cin, inputuser);
	if (inputuser == "-1") {
		return;
	}

	ifstream file;
	ofstream file2;
	file.open("Resource/CustomerInfo.txt");
	file2.open("Resource/temporary.txt");

	Customer c;
	bool flg = false;
	int opt;

	while (getline(file, line)) {
		stringstream lineobj(line);
		getline(lineobj, tmp, '|');
		c.setUsername(tmp);
		getline(lineobj, tmp, '|');
		c.setPassword(tmp);
		getline(lineobj, tmp, '|');
		c.setUserID(tmp);
		getline(lineobj, tmp, '|');
		c.setName(tmp);
		getline(lineobj, tmp, '|');
		c.setContact(tmp);
		if (inputuser == c.getUserID()) {
			flg = true;
			
			cout << "\n\n\tCustomer to be deleted:-\n\n\tUsername\t: " << c.getUsername() << "\n\tPassword\t: " << c.getPassword() << "\n\tUser ID\t\t: " << c.getUserID() << "\n\tName\t\t: " << c.getName() << "\n\tContact\t\t: " << c.getContact() << "\n\n\t[Press 1 to confirm, -1 to abort]: ";
			cin >> opt;
			cin.ignore();
			if (opt == -1) {
				file2 << line << endl;
				cout << "\n\n\tCustomer has been deleted!\n\n\t[press enter to continue]";
				while (getchar() != '\n');
			}
			else if (opt == 1) {
				NULL;
			}
			else {
				file2 << line << endl;
				cout << "\n\n\tSelection invalid! Abort delete process.";
				while (getchar() != '\n');
			}
			
		}
		else {
			file2 << line << endl;
		}
	}
	file.close();
	file2.close();
	remove("Resource/CustomerInfo.txt");
	rename("Resource/temporary.txt", "Resource/CustomerInfo.txt");

	if (flg == false) {
		cout << "\n\n\tCustomer is not found!\n\n\t[press enter to continue]";
		while (getchar() != '\n');
	}
}

string generateVehicleID() {
	vector<std::string> lines;
	string line;
	ifstream File("Resource/Vehicle.txt");
	while (getline(File, line)) {
		lines.push_back(line);
	}
	File.close();

	string secondToLastLine = lines[lines.size() - 1];
	string lastVehicleID, newVehicleID;

	stringstream lineObj(secondToLastLine);
	getline(lineObj, lastVehicleID, '|');

	int lastIDNumber;
	stringstream iss(lastVehicleID.substr(2));
	iss >> lastIDNumber;

	// Increment the numeric part and format it back to "aXX"
	ostringstream oss;
	oss << "a" << std::setfill('0') << std::setw(2) << lastIDNumber + 1;

	newVehicleID = oss.str();
	return newVehicleID;
}

void Admin::addVehicle() {
	string opt = "0";

	Vehicle v;

	do {
		system("cls");
		cout << "\n\n\tVehicle Entry Form" << endl;
		cout << "\t------------------------------------------------" << endl;
		cout << "\tBrand\t\t\t: ";
		getline(cin, v.brand);
		cout << "\tModel\t\t\t: ";
		getline(cin, v.model);
		cout << "\tSeat capacity\t\t: ";
		getline(cin, v.seatCapacity);
		cout << "\tTransmission [A/M] \t: ";
		string tmp;
		getline(cin, tmp);
		if (tmp == "A" or tmp == "a") {
			v.transmission = "Automatic";
		}
		else if (tmp == "M" or tmp == "m") {
			v.transmission = "Automatic";
		}
		else {
			v.transmission = "Error";
		}
		cout << "\tColor\t\t\t: ";
		getline(cin, v.color);
		cout << "\tFare per day\t\t: ";
		getline(cin, v.farePerDay);
		if (v.farePerDay.substr(v.farePerDay.length() - 3) != ".00") {
			v.farePerDay = v.farePerDay + ".00";
		}

		v.vehicleID = generateVehicleID();

		cout << "\n\tCar entry information:- [Please ensure detail is correct]" << endl;
		cout << "\tVehicle ID\t\t: " << v.vehicleID << endl;
		cout << "\tBrand\t\t: " << v.brand << endl;
		cout << "\tModel\t\t: " << v.model << endl;
		cout << "\tSeat capacity\t: " << v.seatCapacity<< endl;
		cout << "\tTransmission\t: " << v.transmission << endl;
		cout << "\tColor\t\t: " << v.color << endl;
		cout << "\tFare per day\t: RM " << v.farePerDay<< endl;

		cout << "\n\tOption:- " << endl;
		cout << "\t1. Confirm and save\n\t2. Retry\n\t3. Exit without saving \n\tOption		:";
		getline(cin, opt);

		if (opt == "1") {
			string data;
			data = v.vehicleID + "|" + v.brand + "|" + v.model + "|" + v.seatCapacity + "|" + v.transmission + "|" + v.color + "|" + v.farePerDay;
			ofstream File;
			File.open("Resource/Vehicle.txt", ios::app);
			File << data << endl;
			File.close();
			cout << "\n\n\tVehicle has been added!\n\n\t[press enter to continue]";
			while (getchar() != '\n');
			return;
		}
		else if (opt == "3") {
			return;
		}
	} while (opt != "1" or opt != "3");
}

void Admin::editVehicle() {
	string inputvehicle, line;
	system("cls");
	cout << "\n\n\tVehicle edit:-" << endl;
	cout << "\t------------------------------------------------" << endl;
	cout << "\tVehicle ID [-1 to return] : ";
	getline(cin, inputvehicle);
	if (inputvehicle == "-1") {
		return;
	}

	ifstream file;
	ofstream file2;
	file.open("Resource/Vehicle.txt");
	file2.open("Resource/temporary.txt");

	Vehicle v;
	bool flg = false;
	int opt;

	while (getline(file, line)) {
		stringstream lineobj(line);
		getline(lineobj, v.vehicleID, '|');
		getline(lineobj, v.brand, '|');
		getline(lineobj, v.model, '|');
		getline(lineobj, v.seatCapacity, '|');
		getline(lineobj, v.transmission, '|');
		getline(lineobj, v.color, '|');
		getline(lineobj, v.farePerDay, '|');
		getline(lineobj, v.availability, '|');
		if (inputvehicle == v.vehicleID) {
			flg = true;
			cout << "\n\n\tWhich aspect would you like to edit?\n\t1. Brand\n\t2. Model\n\t3. Seat capacity\n\t4. Transmission\n\t5. Color\n\t6. Fare per day\n\n\tOption: ";
			cin >> opt;
			cin.ignore();
			switch (opt) {
			case 1:
				cout << "\n\tBrand\t\t: ";
				getline(cin, v.brand);
				break;
			case 2:
				cout << "\n\tModel\t\t: ";
				getline(cin, v.model);
				break;
			case 3:
				cout << "\n\tSeat capacity\t: ";
				getline(cin, v.seatCapacity);
				break;
			case 4:
				cout << "\n\tTransmission\t: ";
				getline(cin, v.transmission);
				break;
			case 5:
				cout << "\n\tColor\t\t: ";
				getline(cin, v.color);
				break;
			case 6:
				cout << "\n\tFare per day\t: RM ";
				getline(cin, v.farePerDay);
				if (v.farePerDay.substr(v.farePerDay.length() - 3) != ".00") {
					v.farePerDay = v.farePerDay + ".00";
				}
				break;
			default:
				cout << "\n\tInvalid input.";
				break;
			}
			string data = v.vehicleID + "|" + v.brand + "|" + v.model + "|" + v.seatCapacity + "|" + v.transmission + "|" + v.color + "|" + v.farePerDay + "|" + v.availability + "\n";
			file2 << data;
			cout << "\n\n\tVehicle updated information:-\n\n\tVehicle ID\t: " << v.vehicleID << "\n\tBrand\t\t: " << v.brand << "\n\tModel\t\t: " << v.model << "\n\tSeat capacity\t: " << v.seatCapacity 
				<< "\n\tTransmission\t: " << v.transmission << "\n\tColor\t\t: " << v.color << "\n\tFare per day\t: " << v.farePerDay << "\n\n\t[Press enter to continue]";
			while (getchar() != '\n');
		}
		else {
			file2 << line << endl;
		}
	}
	file.close();
	file2.close();
	remove("Resource/Vehicle.txt");
	rename("Resource/temporary.txt", "Resource/Vehicle.txt");

	if (flg == false) {
		cout << "\n\n\tVehicle is not found!\n\n\t[Press enter to continue]";
		while (getchar() != '\n');
	}
}

void Admin::deleteVehicle() {
	string inputvehicle, line;
	system("cls");
	cout << "\n\n\tVehicle delete:-" << endl;
	cout << "\t------------------------------------------------" << endl;
	cout << "\tVehicle ID [-1 to return] : ";
	getline(cin, inputvehicle);
	if (inputvehicle == "-1") {
		return;
	}

	ifstream file;
	ofstream file2;
	file.open("Resource/Vehicle.txt");
	file2.open("Resource/temporary.txt");

	Vehicle v;
	bool flg = false;
	int opt;

	while (getline(file, line)) {
		stringstream lineobj(line);
		getline(lineobj, v.vehicleID, '|');
		getline(lineobj, v.brand, '|');
		getline(lineobj, v.model, '|');
		getline(lineobj, v.seatCapacity, '|');
		getline(lineobj, v.transmission, '|');
		getline(lineobj, v.color, '|');
		getline(lineobj, v.farePerDay, '|');
		getline(lineobj, v.availability, '|');
		if (inputvehicle == v.vehicleID) {
			flg = true;

			cout << "\n\n\tVehicle to be deleted:-\n\n\tVehicle ID\t: " << v.vehicleID << "\n\tBrand\t\t: " << v.brand << "\n\tModel\t\t: " << v.model << "\n\tSeat capacity\t: " 
				<< v.seatCapacity << "\n\tTransmission\t: " << v.transmission << "\n\tColor\t\t: " << v.color << "\n\tFare per day\t: RM " << v.farePerDay << "\n\n\t[Press 1 to confirm, -1 to abort]: ";
			cin >> opt;
			cin.ignore();
			if (opt == -1) {
				cout << "\n\n\tVehicle has been deleted!\n\n\t[press enter to continue]";
				while (getchar() != '\n');
				file2 << line << endl;
			}
			else if (opt == 1) {
				NULL;
			}
			else {
				file2 << line << endl;
				cout << "\n\n\tSelection invalid! Abort delete process.";
				while (getchar() != '\n');
			}

		}
		else {
			file2 << line << endl;
		}
	}
	file.close();
	file2.close();
	remove("Resource/Vehicle.txt");
	rename("Resource/temporary.txt", "Resource/Vehicle.txt");

	if (flg == false) {
		cout << "\n\n\tVehicle is not found!\n\n\t[press enter to continue]";
		while (getchar() != '\n');
	}
}

void Admin::viewVehicle() {
	viewVehicles();
}

void Admin::searchVehicle() {
	searchAVehicle();
}

void Admin::viewBooking() {
	Booking b;
	int ctr;
	string line;

	system("cls");
	cout << "\n\n\tBooking view:-" << endl;
	cout << "\t------------------------------------------------" << endl;
	cout << "\n\tBooking list:-" << endl;

	ifstream File;
	File.open("Resource/BookingHistory.txt");

	ctr = 0;
	while (getline(File, line)) {
		stringstream lineObj(line);
		getline(lineObj, b.bookingID, '|');
		getline(lineObj, b.vehicleID, '|');
		getline(lineObj, b.customerID, '|');
		getline(lineObj, b.duration, '|');
		getline(lineObj, b.startDateEndDate, '|');
		getline(lineObj, b.fare, '|');
		getline(lineObj, b.pickUpPoint, '|');
		getline(lineObj, b.review, '|');
		if (ctr != 0) {
			cout << "\n\tBooking #" << ctr <<
				"\n\tBooking ID\t\t: " << b.bookingID <<
				"\n\tVehicle ID\t\t: " << b.vehicleID <<
				"\n\tCustomer ID\t\t: " << b.customerID <<
				"\n\tDuration\t\t: " << b.duration <<
				"\n\tStart date and end data\t: " << b.startDateEndDate <<
				"\n\tFare\t\t\t: " << b.fare <<
				"\n\tPick up point\t\t: " << b.pickUpPoint <<
				"\n\tReview\t\t\t: " << b.review <<
				"\n\n\t------------------------------------------------" << endl;
		}
		ctr++;
	}
	cout << "\n\n\t[Press enter to continue]";
	while (getchar() != '\n');
	File.close();
}

void Admin::editBooking() {
	string inputbooking, line, newInfo;
	system("cls");
	cout << "\n\n\tBooking edit:-" << endl;
	cout << "\t------------------------------------------------" << endl;
	cout << "\tBooking ID [-1 to return] : ";
	getline(cin, inputbooking);
	if (inputbooking == "-1") {
		return;
	}

	ifstream file;
	ofstream file2;
	file.open("Resource/BookingHistory.txt");
	file2.open("Resource/temporary.txt");

	Booking b;
	bool flg = false;
	int opt;

	while (getline(file, line)) {
		stringstream lineObj(line);
		string startDate, endDate;
		getline(lineObj, b.bookingID, '|');
		getline(lineObj, b.vehicleID, '|');
		getline(lineObj, b.customerID, '|');
		getline(lineObj, b.duration, '|');
		getline(lineObj, b.startDateEndDate, '|');
		getline(lineObj, b.fare, '|');
		getline(lineObj, b.pickUpPoint, '|');
		getline(lineObj, b.review, '|');
		if (inputbooking == b.bookingID) {
			flg = true;
			cout << "\n\n\tWhich aspect would you like to edit?\n\t1. Vehicle ID\n\t2. Customer ID\n\t3. Duration\n\t4. Start date\n\t5. Pick up point\n\n\tOption: ";
			cin >> opt;
			cin.ignore();
			switch (opt) {
			case 1:
				cout << "\n\tVehicle ID\t\t: ";
				getline(cin, b.vehicleID);
				b.fare = changeFare(b.vehicleID, b.duration);
				break;
			case 2:
				cout << "\n\tCustomer ID\t\t: ";
				getline(cin, b.customerID);
				break;
			case 3:
				cout << "\n\tDuration\t: ";
				getline(cin, b.duration);
				b.fare = changeFare(b.vehicleID, b.duration);
				startDate = getStartDate(b.startDateEndDate);
				b.startDateEndDate = calStartEnd(startDate, b.duration);
				break;
			case 4:
				cout << "\n\tStart date (YYYY-MM-DD): ";
				getline(cin, startDate);
				b.startDateEndDate = calStartEnd(startDate, b.duration);
				break;
			case 5:
				cout << "\n\tPick up point\t\t: ";
				getline(cin, b.pickUpPoint);
				break;
			default:
				cout << "\n\tInvalid input.";
				break;
			}
			string data = b.bookingID + "|" + b.vehicleID + "|" + b.customerID + "|" + b.duration + "|" + b.startDateEndDate + "|" + b.fare + "|" + b.pickUpPoint + "|" + b.review + "\n";
			file2 << data;
			cout << "\n\n\tBooking updated information:-\n\n\tBooking ID\t\t: " << b.bookingID << "\n\tVehicle ID\t\t: " << b.vehicleID << "\n\tCustomer ID\t\t: " 
				<< b.customerID << "\n\tDuration\t\t: " << b.duration << "\n\tStart date and end date\t: " << b.startDateEndDate << "\n\tFare\t\t\t: " << b.fare 
				<< "\n\tPick up point\t\t: " << b.pickUpPoint << "\n\tReview\t\t\t: " << b.review << "\n\n\t[Press enter to continue]";
			while (getchar() != '\n');
		}
		else {
			file2 << line << endl;
		}
	}
	file.close();
	file2.close();
	remove("Resource/BookingHistory.txt");
	rename("Resource/temporary.txt", "Resource/BookingHistory.txt");

	if (flg == false) {
		cout << "\n\n\tBooking is not found!\n\n\t[Press enter to continue]";
		while (getchar() != '\n');
	}
}

void Admin::reportAnalysis() {
	// Monthly revenue: Map of month to revenue
	map<string, double> monthlyRevenue;

	// Monthly revenue by vehicle type: Map of month to a map of vehicle type to revenue
	map<string, map<string, double>> monthlyRevenueByVehicle;

	// Total revenue by vehicle type: Map of vehicle type to total revenue
	map<string, double> totalRevenueByVehicle;

	ifstream file("Resource/BookingHistory.txt");
	string line;
	double fare;
	int ctr = 0;

	while (getline(file, line)) {
		if (ctr != 0) {
			// Parse line to extract booking date, vehicle ID, and fare
			istringstream lineObj(line);
			Booking b;
			getline(lineObj, b.bookingID, '|');
			getline(lineObj, b.vehicleID, '|');
			getline(lineObj, b.customerID, '|');
			getline(lineObj, b.duration, '|');
			getline(lineObj, b.startDateEndDate, '|');
			getline(lineObj, b.fare, '|');
			getline(lineObj, b.pickUpPoint, '|');
			getline(lineObj, b.review, '|');

			// Extract the month from the booking date (assuming YYYY-MM-DD format)
			string month = b.startDateEndDate.substr(0, 7);

			// Convert fare string to a double
			fare = stod(b.fare);

			// Update monthly revenue
			monthlyRevenue[month] += fare;

			// Update monthly revenue by vehicle type
			monthlyRevenueByVehicle[month][b.vehicleID] += fare;

			// Update total revenue by vehicle type
			totalRevenueByVehicle[b.vehicleID] += fare;
		}
		ctr++;
	}

	file.close();

	cout << "\n\n\tMonthly Revenue Summary:" << endl;
	for (const auto& entry : monthlyRevenue) {
		cout << "\n\t" << entry.first << ": RM " << entry.second << endl;

		// Print monthly revenue by vehicle type for this month
		const string& month = entry.first;
		const map<string, double>& monthlyByVehicle = monthlyRevenueByVehicle[month];
		for (const auto& vehicleEntry : monthlyByVehicle) {
			cout << "\t" << vehicleEntry.first << ": RM " << vehicleEntry.second << endl;
		}
	}

	cout << "\n\n\tTotal Revenue by Vehicle Type:" << endl;
	for (const auto& entry : totalRevenueByVehicle) {
		cout << "\t" << entry.first << ": RM " << entry.second << endl;
	}

	cout << "\n\n\t[press enter to continue]";
	while (getchar() != '\n');
}

# endif
