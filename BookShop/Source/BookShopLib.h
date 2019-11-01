#include <string>
#include <vector>
#include <fstream>
#include <tuple>

class Produkt 
{
    private:
        float cena;
        int id;
    public:
    	Produkt(float c, int i);

        float Cena() { return cena; }
        int Id() { return id; }
};

class Kniha
{
    private:
        float cena;
        int id; 
        std::string nazov;
        std::string autor;
    public:
    	Kniha(std::ifstream *file);

        float Cena() { return cena; }
        int Id() { return id; }
        std::string Nazov() { return nazov; }
        std::string Autor() { return autor; }
};

class Zakaznik
{
    private:
        std::string meno;
        std::string priezvisko;
        float rozpocet;
        std::vector<Produkt*> kupeneKnihy;
    public:
    	Zakaznik(std::string name, std::string surname, float money);
        Zakaznik();

        std::string Meno() { return meno; }
        std::string Priezvisko() { return priezvisko; }
        float Rozpocet() { return rozpocet; }
        std::vector<Produkt*> KupeneKnihy() { return kupeneKnihy; }

        bool buyBook(Produkt *kniha);
        void print(std::vector<Kniha*> book);
};

class Knihkupectvo
{
    private:
        std::string nazov;
        std::vector<Produkt*> produkty;
        float zisk;
        
    public:
    	Knihkupectvo(std::ifstream &file);
    	~Knihkupectvo();

        std::string Nazov() { return nazov; }
        std::vector<Produkt*> Produkty() { return produkty; }
        float Zisk() { return zisk; }

        bool buyBook(int idx);
};

class Search
{
    private:
    	static std::string _getString();
    	// Return index of an element in a vector
    	static int _contains(int idx, std::vector<int> vect);
        static int _contains(int idx, std::vector<std::tuple<int,int>> vect); // Tuple - {shopId, prodId}
    public:
    	static Kniha* find(std::vector<Kniha*> book, int flag);

        static void shop(Kniha* chosenBook, std::vector<Knihkupectvo*> &shop, Zakaznik &customer);
};