files: main A B C

main: main.cpp
	g++ main.cpp -o main

A: A.cpp
	g++ A.cpp -o A

B: B.cpp
	g++ B.cpp -o B

C: C.cpp
	g++  C.cpp -o C

clean:
	rm A B C main