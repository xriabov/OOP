#include "BookShopLib.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>

//
// Produkt
//
Produkt::Produkt(float c, int i)
{
	cena = c;
	id = i;
}

//
// Kniha
//
Kniha::Kniha(std::ifstream *file)
{
	*file >> id;
    file->ignore();
    std::getline(*file, nazov);
    std::getline(*file, autor);
    *file >> cena;
    file->ignore();
}

//
// Zakaznik
//
Zakaznik::Zakaznik()
{
	std::cout << "Enter your name:" << std::endl;
    std::cin >> meno;

    std::cout << "Enter your surname:" << std::endl;
    std::cin >> priezvisko;

    std::cout << "How much money do you have?" << std::endl;
    std::cin >> rozpocet;

    std::cin.ignore();
}
Zakaznik::Zakaznik(std::string name, std::string surname, float money)
{
	meno = name;
    priezvisko = surname;
    rozpocet = money;
}

bool Zakaznik::buyBook(Produkt *kniha)
{
	if(kniha->Cena() <= rozpocet)
    {
        kupeneKnihy.push_back(kniha);
        rozpocet -= kniha->Cena();
        return true;
    }
    return false;
}
void Zakaznik::print(std::vector<Kniha*> book)
{
    int idx;
    std::cout << meno << " " << priezvisko << std::endl
              << "Money left: " << rozpocet << " euro" << std::endl;
    for(int i = 0; i < kupeneKnihy.size(); i++)
    {
        idx = kupeneKnihy[i]->Id();
        std::cout << i+1 << ": " << book[idx]->Nazov() << " by " 
                  << book[idx]->Autor() << " for "
                  << kupeneKnihy[i]->Cena() << " euro" << std::endl;
    }
}


// Knihkupectvo
Knihkupectvo::Knihkupectvo(std::ifstream &file)
{
    int id;
    float cena;
    int num;
    Produkt* prod;

    std::getline(file, nazov);

    file >> num;
    file.ignore();
    
    for(int i = 0; i < num; i++)
    {
        file >> id;
        file.ignore();

        file >> cena;
        file.ignore();

        prod = new Produkt(cena, id);
        produkty.push_back(prod);
    }
}
Knihkupectvo::~Knihkupectvo()
{
	for(int i = 0; i < produkty.size(); i++)
        delete produkty[i];
}

bool Knihkupectvo::buyBook(int idx)
{
	if(idx < 0 || idx >= produkty.size())
        return false;

    zisk += produkty[idx]->Cena();
    return true;
}

//
// Search
//
// Private
std::string Search::_getString()
{
	std::cout << "Enter search string: " << std::endl;
	std::string str;
	std::getline(std::cin, str);
	return str;
}
int Search::_contains(int idx, std::vector<int> vect)
{
	for(int i = 0; i < vect.size(); i++)
		if (vect[i] == idx)
			return true;
	return false;
}
int Search::_contains(int idx, std::vector<std::tuple<int,int>> vect)
{
    for(int i = 0; i < vect.size(); i++)
        if(std::get<0>(vect[i]) == idx)
            return i;
    return -1;
}
// Public
Kniha* Search::find(std::vector<Kniha*> book, int flag)
{
	std::string searchStr = _getString();
	std::vector<int> indices;

	if(flag != 1 && flag != 2)
		return NULL;

	for(int i = 0; i < book.size(); i++)
		if((flag == 1) ? (book[i]->Nazov().find(searchStr) != std::string::npos) : (book[i]->Autor().find(searchStr) != std::string::npos))
		{
			indices.push_back(book[i]->Id());
			std::cout << book[i]->Id() << "\t" << book[i]->Nazov() << " by " << book[i]->Autor() << std::endl;
		}
	
    if(indices.size() != 0)
    {
        std::cout << "Choose the book you want:" << std::endl;
    	int idx = 0;
        do
   		   std::cin >> idx;
   	    while(!Search::_contains(idx, indices));
        std::cin.ignore();

        for(int i = 0; i < book.size(); i++)
            if(book[i]->Id() == idx)
                return book[i];
    }
	return NULL;
}

void Search::shop(Kniha* chosenBook, std::vector<Knihkupectvo*> &shop, Zakaznik &customer)
{
    int i, j, shopId;
    int id;
    std::vector<std::tuple<int,int>> shopToProdMap; // {ShopId, ProdId}[]
    for(i = 0; i < shop.size(); i++)
    {
        for(j = 0; j < shop[i]->Produkty().size(); j++)
            if(shop[i]->Produkty()[j]->Id() == chosenBook->Id())
            {
                std::cout << i << "\t" << shop[i]->Nazov() << ": " << shop[i]->Produkty()[j]->Cena() << " euro" << std::endl;
                shopToProdMap.push_back(std::make_tuple(i, j));
            }
    }
    if(shopToProdMap.size() == 0) 
        return;
    do        
    {
        std::cin >> shopId;
        id = Search::_contains(shopId, shopToProdMap); // There I understood that a dictionary would be better than a vector, but it was too lte
    }
    while(id == -1);
    std::cin.ignore();

    // Extract product
    if(customer.buyBook(shop[shopId]->Produkty()[std::get<1>(shopToProdMap[id])]))
        shop[shopId]->buyBook(std::get<1>(shopToProdMap[id]));
}