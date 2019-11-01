#include <iostream>
#include <cstdlib>
#include <time.h>

class Building
{
protected:
	int num;
	int floors;
public:
	Building(int num, int floors)
	{
		this->num = num;
		this->floors = floors;
	}

	Building() { }
	virtual ~Building() { }

	int GetNum() { return num; }
	int GetFloors() { return floors; }

	virtual void Print()
	{
		std::cout << num << ", Building" << std::endl 
				  << floors << " floors, " << std::endl << std::endl;
	}
};

class FamilyBuilding : public Building
{
private:
	double houseArea;
	double gardenArea;
public:
	FamilyBuilding(int num, int floors, double houseArea, double gardenArea) : Building(num, floors)
	{
		this->houseArea = houseArea;
		this->gardenArea = gardenArea;
	}

	double GetHouseArea() { return houseArea; }
	double GetGardenArea() { return gardenArea; }

	void Print()
	{
		std::cout << num << ", Family House" << std::endl
				  << floors << " floors, " << houseArea 
				  << " m2(house), " << gardenArea 
				  << " m2(garden), " << std::endl << std::endl;
	}
};

class ApartmentBuilding : public Building
{
private:
	int flats;
public:
	ApartmentBuilding(int num, int floors, int flats) : Building(num, floors)
	{
		this->flats = flats;
	}

	int GetFlats() { return flats; }

	void Print()
	{
		std::cout << num << ", Apartment Building" << std::endl  
				  << floors << " floors, " << flats << " flats" << std::endl << std::endl;
	}
};

class CompanyBuilding : public Building
{
protected:
	int employees;
	double dailyReturn;
public:
	CompanyBuilding(int num, int floors, int employees, double dailyReturn) : Building(num, floors)
	{
		this->employees = employees;
		this->dailyReturn = dailyReturn;
	}

	int GetEmployees() { return employees; }
	double GetDailyReturn() { return dailyReturn; }

	void Print()
	{
		std::cout << num << ", Company Building" << std::endl
				  << floors << " floors, " << employees 
				  << " employees, " << dailyReturn 
				  << " Euro per day, " << std::endl << std::endl;
	}
};

class Offices : public CompanyBuilding
{
private:
	int departments;
public:
	Offices(int num, int floors, int employees, double dailyReturn, int departments) : CompanyBuilding(num, floors, employees, dailyReturn)
	{
		this->departments = departments;
	}

	int GetDepartments() { return departments; }

	void Print()
	{
		std::cout << num << ", Fabric" << std::endl
				  << floors << " floors, " << employees 
				  << " employees, " << dailyReturn 
				  << " Euro per day, " << departments 
				  << " departments" << std::endl << std::endl;
	}
};

class Fabric : public CompanyBuilding
{
private:
	double area;
public:
	Fabric(int num, int floors, int employees, double dailyReturn, double area) : CompanyBuilding(num,floors,employees,dailyReturn)
	{
		this->area = area;
	}
	double GetArea() { return area; }

	void Print()
	{
		std::cout << num << ", Fabric" << std::endl
				  << floors << " floors, " << employees 
				  << " employees, " << dailyReturn 
				  << " Euro per day, " << area 
				  << " m2" << std::endl << std::endl;
	}
};

class Street
{
private:
	int len;
	Building** buildings;
public:
	Street(int len, Building** buildings)
	{
		this->len = len;
		this->buildings = buildings;
	}

	Street(int num1, int num2, int num3, int num4)
	{
		int i;
		int num = num1+num2+num3+num4;
		len = num;
		
		int *addresses = new int[num];

		for(i = 0; i < num; i++)
			addresses[i] = 0;

		buildings = new Building*[num];

		for(i = 0, num = 0; i < num1; i++, num++)
			buildings[num] = new FamilyBuilding(genAddr(addresses), 
				rand()%3+1, ((double)(rand()%10000))/100, ((double)(rand()%1000))/100);
		for(i = 0; i < num2; i++, num++)
			buildings[num] = new ApartmentBuilding(genAddr(addresses),
				rand()%20+5, rand()%5+4);
		for(i = 0; i < num3; i++, num++)
			buildings[num] = new Offices(genAddr(addresses), rand()%20+1,
				rand()%100+5, ((double)(rand()%1000000))/100, rand()%10+1);
		for(i = 0; i < num4; i++, num++)
			buildings[num] = new Fabric(genAddr(addresses), rand()%5+1,
				rand()%500+20, ((double)(rand()%1000000))/100, (double)(rand()%10000)/100);
	}

	~Street()
	{
		for(int i = 0; i < len; i++)
			delete buildings[i];
		delete[] buildings;
	}

	Building** GetBuildings() { return buildings; }
	int GetLen() { return len; }
	void PrintStreet()
	{
		for(int i = 0; i < len; i++)
			buildings[i]->Print();
	}

	int genAddr(int *addresses)
	{
		int addr;
		do
			addr = rand()%len;
		while(addresses[addr] != 0);
		addresses[addr] = 1;
		return addr+1;
	}
}; 

int main()
{
	srand(time(NULL));

	Street s = Street(rand()%10, rand()%10, rand()%10, rand()%10);
	s.PrintStreet();

	return 0;
}