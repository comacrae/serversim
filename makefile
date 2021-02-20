#Makefile
#Colin MacRae 
passserver.exe: passserver.o  
	g++ -std=c++11 -lcrypt passserver.o driver.cpp -o passserver.exe
	
passserver.o : passserver.h passserver.cpp hashtable.h
	g++ -c -std=c++11 -lcrypt passserver.h passserver.cpp hashtable.h
	

hashtable.h : hashtable.hpp
	g++ -c -std=c++11 hashtable.h 
	
clean:
	rm *.gch *.o passserver.exe
