client.out: compileAll
	g++ *.o -o client.out
	rm -f *.o
	cp clientConfig.txt ../../exe
	cp client.out ../../exe
	rm -f client.out

compileAll: include/*.h src/*.cpp
	g++ -c src/*.cpp

