#ifndef  ITEMS_H
#define ITEMS_H

using namespace std;

class Vehicle {
public:
	string vehicleID, brand, model, seatCapacity, transmission, color, farePerDay, availability;
};

class Booking : public Vehicle {
public:
	string bookingID, customerID, duration, startDateEndDate, fare, pickUpPoint, review;
};

#endif