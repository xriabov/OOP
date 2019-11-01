BookShop: BookShop.o BookShopLib.o
	g++ -Wall -std=c++11 -o BookShop BookShop.o BookShopLib.o
	rm BookShop.o
	rm BookShopLib.o
	rm Source/.DS_Store # For mac
BookShop.o: Source/BookShop.cpp
	g++ -Wall -std=c++11 -c Source/BookShop.cpp
BookShopLib.o: Source/BookShopLib.cpp
	g++ -Wall -std=c++11 -c Source/BookShopLib.cpp
