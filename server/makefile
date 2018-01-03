server.out: compileAll
	g++ *.o -o server.out -lpthread
	rm -f *.o
	cp serverConfig.txt ../../exe
	cp server.out ../../exe
	rm -f server.out

compileAll: include/*.h src/*.cpp
	g++ -c src/*.cpp

