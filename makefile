all:hds.cpp
	g++ -std=c++11 hds.cpp -o hds.exe

clean:
	rm -f hds.exe