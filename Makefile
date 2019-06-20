
testePerl:
	g++ -o testePerl testePerl.cpp perlWrapper.cpp `perl -MExtUtils::Embed -e ccopts -e ldopts`

jogo:
	g++ -g -Wall -o jogo Main.cpp Engine.cpp Desenhador.cpp Entidade.cpp perlWrapper.cpp Jogo.cpp Menu.cpp Utilidades.h InputManager.cpp `perl -MExtUtils::Embed -e ccopts -e ldopts`

clean:
	rm -f testePerl jogo main *.o
