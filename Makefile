all:programa

programa:
	g++ -o testePerl testePerl.cpp perlWrapper.cpp `perl -MExtUtils::Embed -e ccopts -e ldopts`

clean:
	rm -f testePerl *.o