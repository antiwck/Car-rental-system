#ifndef CUSTOMER_FUNCTION_H
#define CUSTOMER_FUNCTION_H

int Customer::customerMenu() {
	string opt;
	int optInt;
	system("cls");
	cout << "\n\n\tCustomer menu:-" << endl;
	cout << "\t------------------------------------------------" << endl;
	cout << "\tPlease select one of the following operations:-\n\n\t1. View vehicle\n\n\t2. Search vehicle\n\n\t3. Book vehicle\n\n\t4. Pick up and return\n\n\t5. Review" << endl;
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

string generateCustomerID() {
	vector<string> lines;
	string line;
	ifstream File("Resource/CustomerInfo.txt");
	while (getline(File, line)) {
		lines.push_back(line);
	}
	File.close();

	string secondToLastLine = lines[lines.size() - 1];
	string temp, lastUserID, newUserID;

	stringstream lineObj(secondToLastLine);
	getline(lineObj, temp, '|');
	getline(lineObj, temp, '|');
	getline(lineObj, lastUserID, '|');
	getline(lineObj, temp, '|');
	getline(lineObj, temp, '|');

	int lastIDNumber;
	stringstream iss(lastUserID.substr(3));
	iss >> lastIDNumber;

	// Increment the numeric part and format it back to "wckXXXXXX"
	ostringstream oss;
	oss << "wck" << std::setfill('0') << std::setw(6) << lastIDNumber + 1;

	newUserID = oss.str();
	return newUserID;
}

void Customer::regUser() {
	string opt = "0";

	do {
		system("cls");
		cout << "\n\n\tRegistration Form" << endl;
		cout << "\t------------------------------------------------" << endl;
		cout << "\tUsername	: ";
		cin >> username;
		cout << "\tPassword	: ";
		cin >> password;
		cin.ignore();
		cout << "\tName		: ";
		getline(cin, name);
		cout << "\tContact	\t: ";
		getline(cin, contact);

		userID = generateCustomerID();

		cout << "\n\tRegistration information:- [Please ensure detail is correct]" << endl;
		cout << "\tUsername	: " << username << endl;
		cout << "\tPassword	: " << password << endl;
		cout << "\tUser ID	\t: " << userID << endl;
		cout << "\tName		: " << name << endl;
		cout << "\tContact	\t: " << contact << endl;

		cout << "\n\tOption:- " << endl;
		cout << "\t1. Confirm and save\n\t2. Retry\n\t3. Exit without saving \n\tOption		:";
		getline(cin, opt);
		
		if (opt == "1") {
			string data;
			data = username + "|" + password + "|" + userID + "|" + name + "|" + contact;
			ofstream File;
			File.open("Resource/CustomerInfo.txt", ios::app);
			File << data << endl;
			File.close();
			return;
		}
		else if (opt == "3") {
			return;
		}
	} while (opt != "1" or opt != "3");	
}

void Customer::viewVehicle() {
	viewVehicles();
}

void Customer::searchVehicle() {
	searchAVehicle();
}

bool isVehicleAvailable(const string& vehicleID) {
	ifstream file("Resource/Vehicle.txt");
	string line;
	while (getline(file, line)) {
		stringstream lineObj(line);
		string id, brand, model, seatCapacity, transmission, color, farePerDay, availability;
		getline(lineObj, id, '|');
		getline(lineObj, brand, '|');
		getline(lineObj, model, '|');
		getline(lineObj, seatCapacity, '|');
		getline(lineObj, transmission, '|');
		getline(lineObj, color, '|');
		getline(lineObj, farePerDay, '|');
		getline(lineObj, availability, '|');
		if (id == vehicleID && availability == "available") {
			file.close();
			return true; // Vehicle is available
		}
	}
	file.close();
	return false; // Vehicle is not available
}

double calculateFare(const string& vehicleID, const string& duration) {
	ifstream file("Resource/Vehicle.txt");
	string line;
	double fare = 0.0;
	while (getline(file, line)) {
		stringstream lineObj(line);
		string id, brand, model, seatCapacity, transmission, color, farePerDay, availability;
		getline(lineObj, id, '|');
		getline(lineObj, brand, '|');
		getline(lineObj, model, '|');
		getline(lineObj, seatCapacity, '|');
		getline(lineObj, transmission, '|');
		getline(lineObj, color, '|');
		getline(lineObj, farePerDay, '|');
		getline(lineObj, availability, '|');
		if (id == vehicleID) {
			double farePerDayDouble = stod(farePerDay);
			double durationDouble = stod(duration);
			fare = farePerDayDouble * durationDouble;
			break;
		}
	}
	file.close();
	return fare;
}

void updateVehicleStatus(const string& vehicleID, bool isAvailable) {
	ifstream inputFile("Resource/Vehicle.txt");
	ofstream outputFile("Resource/temporary.txt");
	string line;
	while (getline(inputFile, line)) {
		stringstream lineObj(line);
		string id, brand, model, seatCapacity, transmission, color, farePerDay, availability;
		getline(lineObj, id, '|');
		getline(lineObj, brand, '|');
		getline(lineObj, model, '|');
		getline(lineObj, seatCapacity, '|');
		getline(lineObj, transmission, '|');
		getline(lineObj, color, '|');
		getline(lineObj, farePerDay, '|');
		getline(lineObj, availability, '|');
		if (id == vehicleID) {
			availability = (isAvailable ? "available" : "not-available");
		}
		string updatedLine = id + '|' + brand + '|' + model + '|' + seatCapacity + '|' + transmission + '|' + color + '|' + farePerDay + '|' + availability + '\n';
		outputFile << updatedLine;
	}
	inputFile.close();
	outputFile.close();
	remove("Resource/Vehicle.txt");
	rename("Resource/temporary.txt", "Resource/Vehicle.txt");
}

string generateUniqueBookingID() {
	string id, line;
	stringstream ss;
	bool flg;
	srand(time(NULL));
	do {
		flg = false;
		// To generate five random alphabet and six random number
		char alphabet[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
							  'h', 'i', 'j', 'k', 'l', 'm', 'n',
							  'o', 'p', 'q', 'r', 's', 't', 'u',
							  'v', 'w', 'x', 'y', 'z' };
		for (int i = 0; i < 4; i++) {
			id = id + alphabet[rand() % 26];
		}
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<int> distribution(0, 9999);
		int random_number = distribution(gen);
		ss;
		ss << setw(4) << setfill('0') << random_number;
		id = id + ss.str();
		ifstream File;
		File.open("BookingHistory.txt");

		while (getline(File, line)) {
			if (line.substr(0, 7) == id) {
				flg = true;
			}
		}
	} while (flg);
	return id;
}

string autoGeneratePickUp() {
	ifstream file("Resource/pickUpLocation.txt");
	vector<string> locations;
	string line;
	while (getline(file, line)) {
		locations.push_back(line);
	}
	file.close();
	srand(static_cast<unsigned int>(time(nullptr)));
	int randomIndex = rand() % locations.size();
	return locations[randomIndex];
};


void writeBookingHistory(const string& vehicleID, const string& userID, const string& duration, const string& startEndDate, const string& pickUpPoint, const stringstream& fare) {
	ofstream file("Resource/BookingHistory.txt", ios::app);
	if (file.is_open()) {
		string bookingID = generateUniqueBookingID();

		// Get the current date and time
		time_t now = time(0);
		tm* localTime = localtime(&now);
		string currentDate = to_string(localTime->tm_year + 1900) + "-" + to_string(localTime->tm_mon + 1) + "-" + to_string(localTime->tm_mday);

		// Write booking information to the file with a default review "-"
		file << bookingID << '|' << vehicleID << '|' << userID << '|' << duration << '|' << startEndDate << '|'  << fare.str() << '|' << pickUpPoint << '|' << "-" << endl;

		file.close();
	}
}

void Customer::bookVehicle() {
	string vehicleID, duration, startDate;
	cout << "\n\n\tBook a Vehicle:-" << endl;
	cout << "\t------------------------------------------------" << endl;

	// Get vehicle ID from the user
	cout << "\tEnter Vehicle ID: ";
	getline(cin, vehicleID);

	// Get booking duration from the user
	cout << "\n\tEnter Booking Duration (in days): ";
	getline(cin, duration);

	// Get booking start date from the user (format: YYYY-MM-DD)
	cout << "\n\tEnter Booking Start Date (YYYY-MM-DD): ";
	getline(cin, startDate);

	// Check vehicle availability
	if (!isVehicleAvailable(vehicleID)) {
		cout << "\n\tVehicle with ID " << vehicleID << " is not available for booking." << endl;
		while (getchar() != '\n');
		return;
	}

	// Calculate the fare based on duration and fare per day
	double fare = calculateFare(vehicleID, duration);
	stringstream Fare;
	Fare << setprecision(2) << fare;

	// Update vehicle status to not available
	updateVehicleStatus(vehicleID, false);

	string startEnd = calStartEnd(startDate, duration);
	string pickUpPoint = autoGeneratePickUp();

	// Display booking details
	cout << "\n\tBooking successful!" << endl;
	cout << "\tVehicle ID\t\t: " << vehicleID << endl;
	cout << "\tDuration\t\t: " << duration << " days" << endl;
	cout << "\tStart and end date\t: " << startEnd << endl;
	cout << "\tTotal Fare\t\t: RM " << fare << endl;

	writeBookingHistory(vehicleID, getUserID(), duration, startEnd, pickUpPoint, Fare);

	cout << "\n\t[Press enter to continue]";
	while (getchar() != '\n');
}

void Customer::pickUpAndReturn() {
	string customerID = getUserID(), line;

	ifstream file("Resource/BookingHistory.txt");

	if (!file.is_open()) {
		std::cerr << "Error: Unable to open BookingHistory.txt" << std::endl;
		cout << "\n\t[Press enter to continue]";
		while (getchar() != '\n');
		return;
	}

	bool foundBooking = false;
	Booking b;

	while (getline(file, line)) {
		istringstream lineObj(line);
		getline(lineObj, b.bookingID, '|');
		getline(lineObj, b.vehicleID, '|');
		getline(lineObj, b.customerID, '|');
		getline(lineObj, b.duration, '|');
		getline(lineObj, b.startDateEndDate, '|');
		getline(lineObj, b.fare, '|');
		getline(lineObj, b.pickUpPoint, '|');
		getline(lineObj, b.review, '|');
		if (b.customerID == customerID and b.review == "-") {
			foundBooking = true;
			break;
		}
	}

	file.close();

	if (!foundBooking) {
		cout << "\n\n\tNo matching booking with customer ID " << customerID << " and review '-' found." << endl;
		while (getchar() != '\n');
	}
	else {
		cout << "\n\n\tPick up and drop off location for your " << b.vehicleID << " is at " << b.pickUpPoint << ".\n\n\t[Press enter to continue]";
		while (getchar() != '\n');
	}
}

void updateBookingHistory(const std::string& bookingID, const std::string& review) {
	ifstream file;
	ofstream file2;
	file.open("Resource/BookingHistory.txt");
	file2.open("Resource/temporary.txt");

	if (!file.is_open()) {
		std::cerr << "Error: Unable to open BookingHistory.txt" << std::endl;
		cout << "\n\t[Press enter to continue]";
		while (getchar() != '\n');
		return;
	}

	string line;

	// Read the file line by line and update the corresponding booking's review
	while (getline(file, line)) {
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
		if (bookingID == b.bookingID) {
			file2 << b.bookingID + '|' + b.vehicleID + '|' + b.customerID + '|' + b.duration + '|' + b.startDateEndDate + '|' + b.fare + '|' + b.pickUpPoint + '|' + review + "\n";
		}
		else {
			file2 << line + '\n';
		}
	}
	file.close();
	file2.close();

	//remove("Resource/BookingHistory.txt");
	//rename("Resource/temporary.txt", "Resource/BookingHistory.txt");
	if (std::remove("Resource/BookingHistory.txt") != 0) {
		std::cerr << "Error: Unable to delete BookingHistory.txt" << std::endl;
	}	// Handle the error, e.g., by displaying a message or logging it.

	if (std::rename("Resource/temporary.txt", "Resource/BookingHistory.txt") != 0) {
		std::cerr << "Error: Unable to rename temporary2.txt" << std::endl;
		// Handle the error, e.g., by displaying a message or logging it.
	}

}

void Customer::review() {
	string userID = getUserID();
	ifstream file("Resource/BookingHistory.txt");

	if (!file.is_open()) {
		cerr << "Error: Unable to open BookingHistory.txt" << endl;
		cout << "\n\t[Press enter to continue]";
		while (getchar() != '\n');
		return;
	}

	string line;

	bool foundBooking = false;

	while (getline(file, line)) {
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
		if (b.customerID == userID and b.review == "-") {
			foundBooking = true;
			string userReview;
			do {
				cout << "\n\n\tPending review for booking: " << b.bookingID << endl;
				cout << "\n\tEnter your review (0 to 5): ";
				getline(cin, userReview);
				if (userReview != "0" && userReview != "1" && userReview != "2" && userReview != "3" && userReview != "4" && userReview != "5") {
					cout << "\n\tInvalid input. Please enter a rating between 0 and 5." << endl;
				}
			} while (userReview != "0" and userReview != "1" and userReview != "2" and userReview != "3" and userReview != "4" and userReview != "5");

			// Set the availability of the corresponding vehicle to "available" in "vehicle.txt"
			updateVehicleStatus(b.vehicleID, true);
			file.close();

			// Update the booking line with the review
			updateBookingHistory(b.bookingID, userReview);

			cout << "\n\n\tReview submitted successfully." << endl;
			foundBooking = true;
			cout << "\n\t[Press enter to continue]";
			while (getchar() != '\n');
			break;
		}
	}

	file.close();

	if (!foundBooking) {
		std::cout << "No matching booking with user ID " << userID << " and review '-' found." << std::endl;
		cout << "\n\t[Press enter to continue]";
		while (getchar() != '\n');
	}
}

# endif
