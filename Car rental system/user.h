#ifndef  USER_H
#define USER_H

using namespace std;

class User {
public:
	User() : username(""), password(""), userID(""), name(""), contact("") {};
	~User() {};

	int obtainInfo();
	int checkInfo(const string&);

	void viewVehicles();
	void searchAVehicle();

protected:
	string username, password, userID, name, contact;
};

int User::obtainInfo() {
	system("cls");
	cout << "\n\n\tAccount portal:-" << endl;
	cout << "\t------------------------------------------------" << endl;
	cout << "\tEnter username [-1 to return] \t: ";
	getline(cin, username);
	if (username == "-1") {
		return 0;
	}
	cout << "\n\tEnter password\t\t\t: ";
	getline(cin, password);
	return 1;
}

int User::checkInfo(const string& filename) {
	string line, user, pass;
	ifstream file;
	file.open(filename);

	while (getline(file, line)) {
		stringstream lineObj(line);
		getline(lineObj, user, '|');
		getline(lineObj, pass, '|');

		if (username == user && password == pass) {
			getline(lineObj, userID, '|');
			getline(lineObj, name, '|');
			getline(lineObj, contact, '|');
			file.close();
			return 1;
		}
	}

	file.close();
	cout << "\n\tInvalid user credential.\n\n\t[Press enter to continue]" << endl;
	while (getchar() != '\n');
	return 0;
}

void User::viewVehicles() {
	Vehicle v;
	int ctr;
	string line;

	system("cls");
	cout << "\n\n\tVehicle view:-" << endl;
	cout << "\t------------------------------------------------" << endl;
	cout << "\n\tVehicle list:-" << endl;

	ifstream File;
	File.open("Resource/Vehicle.txt");

	ctr = 0;
	while (getline(File, line)) {
		stringstream lineObj(line);
		getline(lineObj, v.vehicleID, '|');
		getline(lineObj, v.brand, '|');
		getline(lineObj, v.model, '|');
		getline(lineObj, v.seatCapacity, '|');
		getline(lineObj, v.transmission, '|');
		getline(lineObj, v.color, '|');
		getline(lineObj, v.farePerDay, '|');
		getline(lineObj, v.availability, '|');
		if (ctr != 0) {
			cout << "\n\tVehicle #" << ctr <<
				"\n\tVehicle ID\t: " << v.vehicleID <<
				"\n\tBrand\t\t: " << v.brand <<
				"\n\tModel\t\t: " << v.model <<
				"\n\tSeat capacity\t: " << v.seatCapacity <<
				"\n\tTransmission\t: " << v.transmission <<
				"\n\tColor\t\t: " << v.color <<
				"\n\tFare per day\t: RM " << v.farePerDay <<
				"\n\tAvailability\t: " << v.availability <<
				"\n\n\t------------------------------------------------" << endl;
		}
		ctr++;
	}
	cout << "\n\n\t[Press enter to continue]";
	while (getchar() != '\n');
	File.close();
}

void User::searchAVehicle() {
	Vehicle v;
	bool flg = false;
	string inputvehicleID, line;

	system("cls");
	cout << "\n\n\tVehicle search:-" << endl;
	cout << "\t------------------------------------------------" << endl;
	cout << "\n\tVehicle ID [-1 to return] : ";
	getline(cin, inputvehicleID);
	if (inputvehicleID == "-1") {
		return;
	}

	ifstream File;
	File.open("Resource/Vehicle.txt");

	while (getline(File, line)) {
		stringstream lineObj(line);
		getline(lineObj, v.vehicleID, '|');
		getline(lineObj, v.brand, '|');
		getline(lineObj, v.model, '|');
		getline(lineObj, v.seatCapacity, '|');
		getline(lineObj, v.transmission, '|');
		getline(lineObj, v.color, '|');
		getline(lineObj, v.farePerDay, '|');
		getline(lineObj, v.availability, '|');
		if (inputvehicleID == v.vehicleID) {
			flg = true;
			cout <<
				"\n\tVehicle ID\t: " << v.vehicleID <<
				"\n\tBrand\t\t: " << v.brand <<
				"\n\tModel\t\t: " << v.model <<
				"\n\tSeat capacity\t: " << v.seatCapacity <<
				"\n\tTransmission\t: " << v.transmission <<
				"\n\tColor\t\t: " << v.color <<
				"\n\tFare per day\t: RM " << v.farePerDay <<
				"\n\tAvailability\t: " << v.availability <<
				"\n\n\t[Press enter to continue]";
			while (getchar() != '\n');
			break;
		}
	}
	File.close();

	if (flg == false) {
		cout << "\n\n\tVehicle is not found!\n\t[Press enter to continue]";
		while (getchar() != '\n');
	}
}

class Admin : public User {
public:
	Admin() {};
	~Admin() {};

	int authenticate();

	int adminMenu();

	void editUser();
	void deleteUser();

	void addVehicle();
	void editVehicle();
	void deleteVehicle();
	void viewVehicle();
	void searchVehicle();

	void viewBooking();
	void editBooking();

	void reportAnalysis();

	void setUsername(string& inputUsername)	{ username = inputUsername; };
	void setPassword(string& inputPassword)	{ password = inputPassword; };
	void setUserID(string& inputUserID)		{ userID = inputUserID;		};
	void setName(string& inputName)			{ name = inputName;			};
	void setContact(string& inputContact)	{ contact = inputContact;	};

	string getUsername()	{ return username; };
	string getPassword()	{ return password; };
	string getUserID()		{ return userID; };
	string getName()		{ return name; };
	string getContact()		{ return contact; };
};

int Admin::authenticate() {
	if (obtainInfo() == 0) {
		return 0;
	}
	return checkInfo("Resource/AdminInfo.txt");
}

class Customer : public User {
public:
	Customer() {};
	~Customer() {};

	int authenticate();

	int customerMenu();

	void regUser();
	void viewVehicle();
	void searchVehicle();
	void bookVehicle();
	void pickUpAndReturn();
	void review();

	void setUsername(string& inputUsername) { username = inputUsername; };
	void setPassword(string& inputPassword) { password = inputPassword; };
	void setUserID(string& inputUserID)		{ userID = inputUserID; };
	void setName(string& inputName)			{ name = inputName; };
	void setContact(string& inputContact)	{ contact = inputContact; };

	string getUsername()	{ return username; };
	string getPassword()	{ return password; };
	string getUserID()		{ return userID; };
	string getName()		{ return name; };
	string getContact()		{ return contact; };
};

int Customer::authenticate() {
	if (obtainInfo() == 0) {
		return 0;
	}
	return checkInfo("Resource/CustomerInfo.txt");
}

string changeFare(const string vehicleID, const string duration) {
	string line;

	ifstream File;
	File.open("Resource/Vehicle.txt");

	Vehicle v;
	int fare = 0;
	bool flg = false;

	while (getline(File, line)) {
		stringstream lineObj(line);
		getline(lineObj, v.vehicleID, '|');
		getline(lineObj, v.brand, '|');
		getline(lineObj, v.model, '|');
		getline(lineObj, v.seatCapacity, '|');
		getline(lineObj, v.transmission, '|');
		getline(lineObj, v.color, '|');
		getline(lineObj, v.farePerDay, '|');
		getline(lineObj, v.availability, '|');
		if (vehicleID == v.vehicleID) {
			fare = stoi(duration) * stoi(v.farePerDay);
			break;
		}
	}
	File.close();
	return to_string(fare) + ".00";
}

string calStartEnd(string startDate, string duration) {
	struct tm tm_start = {};
	istringstream ss_start(startDate);

	// Parse the start date (assuming the format is YYYY-MM-DD)
	ss_start >> get_time(&tm_start, "%Y-%m-%d");

	// Extract year, month, and day from the start date
	int startYear = tm_start.tm_year + 1900; // Years since 1900
	int startMonth = tm_start.tm_mon + 1;     // Months are 0-11
	int startDay = tm_start.tm_mday;

	// Parse the duration to get the number of days
	int daysToAdd;
	istringstream ss_duration(duration);
	ss_duration >> daysToAdd;

	// Calculate the end date by adding the duration to the start date
	int endYear = startYear;
	int endMonth = startMonth;
	int endDay = startDay + daysToAdd - 1;

	// Handle cases where the day exceeds the number of days in the month
	while (endDay > 31) {
		// Adjust the end month and subtract the days from the current month
		endMonth++;
		endDay -= 31;

		// Handle cases where the month exceeds 12
		if (endMonth > 12) {
			endYear++;
			endMonth = 1; // Reset month to 1 for January
		}
	}

	// Format the start and end dates as a single string
	ostringstream ss_dates;
	ss_dates << startYear << "-" << (startMonth < 10 ? "0" : "") << startMonth << "-" << (startDay < 10 ? "0" : "") << startDay << " "
		<< endYear << "-" << (endMonth < 10 ? "0" : "") << endMonth << "-" << (endDay < 10 ? "0" : "") << endDay;
	string dateRange = ss_dates.str();

	return dateRange;
}

string getStartDate(string startEndDate) {
	string startDate, endDate;
	istringstream ss(startEndDate);
	ss >> startDate >> endDate;
	return startDate;
}

#endif