
testePerl:
	g++ -o testePerl testePerl.cpp perlWrapper.cpp `perl -MExtUtils::Embed -e ccopts -e ldopts`

teste:
	g++ -o main Main.cpp Engine.cpp Desenhador.cpp Entidade.cpp perlWrapper.cpp Jogo.cpp Menu.cpp `perl -MExtUtils::Embed -e ccopts -e ldopts`

clean:
	rm -f testePerl *.o
