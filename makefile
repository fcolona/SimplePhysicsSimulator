main:
	g++ -o animation main.cpp -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17
	./animation
debug:
	g++ -g main.cpp -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17
	gdb a.out core.animation