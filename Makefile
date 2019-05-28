all:programa

programa:
	g++ -o main main.cpp perlWrapper.cpp `perl -MExtUtils::Embed -e ccopts -e ldopts`

clean:
	rm -f main *.o