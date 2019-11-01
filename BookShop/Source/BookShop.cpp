#include "BookShopLib.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>

int main()
{   

    std::ifstream shops, books;
    int shopnum, booknum;
    int i;

    shops.open("shops.txt");
    books.open("books.txt");
    if(!shops || !books)
        return 1;

    std::vector<Knihkupectvo*> shop;
    std::vector<Kniha*> book;
    Zakaznik customer;
    
    // Load shops and books from text file
    shops >> shopnum;
    shops.ignore();
    books >> booknum;
    books.ignore();
    for(i = 0; i < shopnum; i++)
	    shop.push_back(new Knihkupectvo(shops));
    for(i = 0; i < booknum; i++)
        book.push_back(new Kniha(&books)); 
    

    int choice;
    Kniha *chosenBook;
    while(true)
    {
        std::cout << "1 - Search by name\n"
                  << "2 - Search by author\n"
                  << "3 - Exit" << std::endl;

        std::cin >> choice;
        std::cin.ignore();

        if(choice == 3)
            break;

        if(choice == 1 || choice == 2)
        {
            chosenBook = Search::find(book, choice);
            if(!chosenBook)
                break;
           Search::shop(chosenBook, shop, customer);
        }
    }


    // Print Shops and Customer data
    customer.print(book);
    std::cout << "--------------------" << std::endl;
    for(i = 0; i < shop.size(); i++)
        std::cout << shop[i]->Nazov() << ": " << shop[i]->Zisk() << " euro" << std::endl;

    shops.close();
    books.close();

    return 0;
}
