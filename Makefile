test : makeTest testPack test1.txt test2.txt test3.txt
	./testPack test1.txt
	./testPack test2.txt
	./testPack test3.txt
	
test1.txt : makeTest
	./makeTest 10 > test1.txt
	
test2.txt : makeTest
	./makeTest 2000 > test2.txt
	
test3.txt : makeTest
	./makeTest 3000 > test3.txt
	
makeTest : makeTest.c
	gcc -g -Wall -o makeTest makeTest.c
	
testPack : testPack.c packInt.c packInt.h
	gcc -g -Wall -o testPack testPack.c packInt.c
	
clean :
	-rm testPack makeTest test*.txt
	