#include<iostream>
using namespace std;

class Vehicle
{
protected:
    int vehicleID;
    string manufacturer;
    string model;
    int year;
    static int totalVehicles;

public:
    Vehicle()
    {
        vehicleID = 0;
        manufacturer = "";
        model = "";
        year = 0;
        totalVehicles++;
    }

    Vehicle(int id, string manu, string mod, int yr)
    {
        vehicleID = id;
        manufacturer = manu;
        model = mod;
        year = yr;
        totalVehicles++;
    }

    virtual void display()
    {
        cout <<"Vehicle ID: " << vehicleID<<endl;
        cout <<"Manufacturer: " << manufacturer<<endl;
        cout <<"Model: " << model<<endl;
        cout <<"Year: " << year << endl;
    }

    int getID()
    {
        return vehicleID;
    }

    static int getTotalVehicles()
    {
        return totalVehicles;
    }

    virtual ~Vehicle() {}
};

int Vehicle::totalVehicles = 0;

class Car : public Vehicle
{
private:
    string fuelType;

public:
    Car(int id, string manu, string mod, int yr, string fuel)
        : Vehicle(id, manu, mod, yr)
    {
        fuelType = fuel;
    }

    void display()
    {
        Vehicle::display();
        cout << "Fuel Type: " << fuelType << endl;
    }
};

class ElectricCar : public Car
{
private:
    int batteryCapacity;

public:
    ElectricCar(int id, string manu, string mod, int yr, string fuel, int battery)
        : Car(id, manu, mod, yr, fuel)
    {
        batteryCapacity = battery;
    }

    void display()
    {
        Car::display();
        cout << "Battery Capacity: " << batteryCapacity << " kWh" << endl;
    }
};

class SportsCar : public ElectricCar
{
    int topSpeed;

public:
    SportsCar(int id, string manu, string mod, int yr, string fuel, int battery, int speed)
        : ElectricCar(id, manu, mod, yr, fuel, battery)
    {
        topSpeed = speed;
    }

    void display()
    {
        ElectricCar::display();
        cout << "Top Speed: " << topSpeed << " km/h" << endl;
    }
};

class Sedan : public Car
{
public:
    Sedan(int id, string manu, string mod, int yr, string fuel)
        : Car(id, manu, mod, yr, fuel) {}
};

class SUV : public Car
{
public:
    SUV(int id, string manu, string mod, int yr, string fuel)
        : Car(id, manu, mod, yr, fuel) {}
};

class Aircraft
{
private:
    int flightRange;

public:
    Aircraft(int range)
    {
        flightRange = range;
    }

    void displayAircraft()
    {
        cout << "Flight Range: " << flightRange << " km" << endl;
    }
};

class FlyingCar : public Car, public Aircraft
{
public:
    FlyingCar(int id, string manu, string mod, int yr, string fuel, int range)
        : Car(id, manu, mod, yr, fuel), Aircraft(range) {}

    void display()
    {
        Car::display();
        displayAircraft();
    }
};

class VehicleRegistry
{
    Vehicle* vehicles[50];
    int count;

public:
    VehicleRegistry()
    {
        count = 0;
    }

    void addVehicle(Vehicle* v)
    {
        vehicles[count++] = v;
    }

    void displayAll()
    {
        for(int i = 0; i < count; i++)
        {
            vehicles[i]->display();
            cout << "----------------------\n";
        }
    }

    void searchByID(int id)
    {
        for(int i = 0; i < count; i++)
        {
            if(vehicles[i]->getID() == id)
            {
                vehicles[i]->display();
                return;
            }
        }
        cout << "Vehicle Not Found!\n";
    }
};

int main()
{
    VehicleRegistry registry;
    int choice;

    do
    {
        cout << "===== Vehicle Registry Menu ====="<<endl;
        cout << "1. Add Vehicle"<<endl;
        cout << "2. View All Vehicles"<<endl;
        cout << "3. Search by ID"<<endl;
        cout << "4. Exit"<<endl;
        cout << "Enter Choice: "<<endl;
        cin >> choice;

        if(choice == 1)
        {
            int type;
            cout <<endl<<"1.Car  2.ElectricCar  3.SportsCar  4.FlyingCar  5.Sedan  6.SUV"<<endl;
            cin >> type;

            int id, yr, battery, speed, range;
            string manu, mod, fuel;

            cout << "Enter ID: "; cin >> id;
            cout << "Enter Manufacturer: "; cin >> manu;
            cout << "Enter Model: "; cin >> mod;
            cout << "Enter Year: "; cin >> yr;

            switch(type)
            {
                case 1:
                    cout << "Enter Fuel Type: "; cin >> fuel;
                    registry.addVehicle(new Car(id, manu, mod, yr, fuel));
                    break;

                case 2:
                    cout << "Enter Fuel Type: "; cin >> fuel;
                    cout << "Enter Battery Capacity: "; cin >> battery;
                    registry.addVehicle(new ElectricCar(id, manu, mod, yr, fuel, battery));
                    break;

                case 3:
                    cout << "Enter Fuel Type: "; cin >> fuel;
                    cout << "Enter Battery Capacity: "; cin >> battery;
                    cout << "Enter Top Speed: "; cin >> speed;
                    registry.addVehicle(new SportsCar(id, manu, mod, yr, fuel, battery, speed));
                    break;

                case 4:
                    cout << "Enter Fuel Type: "; cin >> fuel;
                    cout << "Enter Flight Range: "; cin >> range;
                    registry.addVehicle(new FlyingCar(id, manu, mod, yr, fuel, range));
                    break;

                case 5:
                    cout << "Enter Fuel Type: "; cin >> fuel;
                    registry.addVehicle(new Sedan(id, manu, mod, yr, fuel));
                    break;

                case 6:
                    cout << "Enter Fuel Type: "; cin >> fuel;
                    registry.addVehicle(new SUV(id, manu, mod, yr, fuel));
                    break;

                default:
                    cout << "Invalid Type!\n";
            }
        }
        else if(choice == 2)
            registry.displayAll();

        else if(choice == 3)
        {
            int id;
            cout << "Enter ID to Search: ";
            cin >> id;
            registry.searchByID(id);
        }

    } while(choice != 4);

    cout <<endl<<"Total Vehicles Created: " << Vehicle::getTotalVehicles() << endl;

    return 0;
}
