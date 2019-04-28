use strict;
use warnings FATAL => 'all';
use Data::Dumper;

use lib './';
use GerenciamentoDeDados;

#my @teste = GerenciamentoDeDados::listaPontuacoesMaiores("dadosTeste.txt", 3);
#print Dumper @teste;
GerenciamentoDeDados::salvaPerfil("dadosTeste.txt","raposo","666","1");