package GerenciamentoDeDados;
use strict;
use warnings FATAL => 'all';
use Data::Dumper;
use File::Copy qw(move);

# lista de mensagens de erro
my %mensagensErro = (
    "arquivo_01"                => "Erro ao abrir o arquivo: ",
    "ok"                        => "Tudo funcionou como esperado",
    "nome_sem_jogo"             => "Nao foi encontrada uma partida associada ao nome",
    "dificuldade_sem_jogo"      => "Nao foi encontrada uma partida com essa dificuldade",
    "pontuacao_nao_encontrada"  => "Nao foi encontraf nenhuma pontuacao associada ao nome e a dificuldade especificada",
    "partidas_nao_encontradas"  => "Nao foram encontradas paridas associadas ao nome e a restricao"
);

my $debug = 0;

#transforma um arquivo texto em uma matriz em que as linhas representam as linhas do arquivo e as colunas representam as palavras de uma linha
sub matrizPalavras {
    open(my $arquivo, "<", shift)
        or die("\n" . $mensagensErro{"arquivo_01"} . "\n" . $!);
    my @todas;
    my $i = 0;
    while (my $linha = <$arquivo>) {
        chomp $linha;
        if (substr($linha, 0, 1) ne "#" && $linha =~ m/(\|\d+\|\d+)$|(\|\d+)$/) {
            my @palavras = split /\|/, $linha;
            my $j = 0;
            for my $k (0 .. scalar @palavras - 1) {
                $todas[$i][$j] = $palavras[$k];
                $j++;
            }
            $i++;
        }
    }
    return @todas;
}

sub listaPontuacoesMaiores {
    my @linhas = matrizPalavras(shift);
    if (scalar @linhas == 0) {
        return 0;
    }
    my $limite = shift;
    if ($debug == 1) {
        print Dumper @linhas;
    }
    my @pontuacoes;
    for my $i (0 .. scalar @linhas - 1) {
        if (not $linhas[$i][2]) {
            my %pontuacao;
            $pontuacao{"nome"} = $linhas[$i][0];
            $pontuacao{"pontos"} = $linhas[$i][1];
            push @pontuacoes, \%pontuacao;
        }
    }
    if ($debug == 1) {
        print Dumper @pontuacoes;
    }

    my @ordPontuacoes = sort {$a->{"pontos"} <=> $b->{"pontos"}} @pontuacoes;

    if ($debug == 1) {
        print Dumper @ordPontuacoes;
    }

    my $n = scalar @ordPontuacoes - $limite;
    if ($n < 0) {
        $n = 0;
    }
    return splice @ordPontuacoes, $n;
}


sub salvaPerfil {
    my $arquivo = shift;
    my $nome = shift;
    my $pontuacao = shift;
    my $dificuldade = shift;
    my $status = 0;
    open my $in, '<', $arquivo or die("\n" . $mensagensErro{"arquivo_01"} . "\n" . $!);
    open my $out, '>', "$arquivo.new" or die("\n" . $mensagensErro{"arquivo_01"} . "\n" . $!);

    my $novo = 1;

    while (my $linha = <$in>) {
        chomp $linha;
        if ($debug == 1) {
            print $linha . "\n";
        }
        if ($linha =~ /$nome\|\d+\|\d+/) {
            if ($debug == 1) {
                print "Perfil encontrado: " . $linha . "\n";
            }
            print $out $nome . "\|" . $pontuacao . "\|" . $dificuldade;
            if ($debug == 1) {
                print "Novo perfil: " . $linha . "\n";
            }
            $novo = 0;
        }
        else {
            print $out $linha;
        }
        print $out "\n";
    }
    if ($novo > 0) {
        if ($debug == 1) {
            print "Criando novo perfil";
        }
        print $out $nome . "\|" . $pontuacao . "\|" . $dificuldade;
        $status = 1;
    }
    close $out;
    move "$arquivo.new", $arquivo;
    return $status;
}

# sub leJogoEmAndamento (nome, dificuldade, arquivo de dados)
#  Recebe: Nome do jogador (nome do perfil)
#          Dificuldade desejada do jogo
#          Arquivo de dados para a matriz de palavras
#
#  Retorna: Pontuacao atual da partida
#           Codigo de erro
sub leJogoEmAndamento {
    my $nome = $_[0];
    my $pontuacao = -1;
    my $dificuldade = $_[1];
    my @linhas = matrizPalavras($_[2]);
    my $chaveErro = "pontuacao_nao_encontrada";


    #validar dados de entrada;
    for my $i (0 .. scalar @linhas) {
        if (defined $linhas[$i][2] && $dificuldade == $linhas[$i][2]) {
            if ($linhas[$i][0] eq $nome) {
              # validar pontuacao;
                $pontuacao = $linhas[$i][1];
                $chaveErro = "ok";
            }
            else {
                #jogos que nao correspondem ao nome
            }
        }
        else {
            #jogos terminados (sem dificuldade definida)
        }
    }
    return $pontuacao, $chaveErro;
}

# sub listaPontuacoesDeJogador (nome, nivelDeRestricao, matriz de palvras )
#  Recebe: Nome do jogador em qualquer formato
#          Nivel de restricao na procura do nome. Diferencia pedro de P3dr0 de Pedro ou não
#          Matriz de palavras referente ao arquivo de dados
#
#  Retorna: Lista das pontuacoes (array de pontuacoes)
#
#
#  Falta: ver se vamos listar as partidas nao terminadas (sim)
#
sub listaPontuacoesDeJogador {
    my $nome = $_[0];
    my @partidas = 0;
    my $restricao = $_[1];
    my @linhas = matrizPalavras($_[2]);
    my $chaveErro = "ok";
    my $nomeIterador;
    my $pontuacaoIterador;
    my $i;

    #validar dados de entrada

    if ($restricao == 1) {
        $nome =~ tr/A-Z/a-z/;
        $nome =~ tr/@/a/;
        $nome =~ tr/&/e/;
        $nome =~ tr/3/e/;
        $nome =~ tr/1/i/;
        $nome =~ tr/0/o/;
    }
    elsif ($restricao == 2) {
        $nome =~ tr/A-Z/a-z/;
    }
    elsif ($restricao == 3) {
      #nao faz nada
    }
    else {
      #erro
    }

    for $i (0 .. scalar @linhas) {
        $nomeIterador = $linhas[$i][0];
        $pontuacaoIterador = $linhas[$i][1];
        if (defined $nomeIterador && defined $pontuacaoIterador) {
            if ($restricao == 2) {
                $nomeIterador =~ tr/A-Z/a-z/;
            }

            if ($restricao == 1) {
                $nomeIterador =~ tr/A-Z/a-z/;
                $nomeIterador =~ tr/@/a/;
                $nomeIterador =~ tr/&/e/;
                $nomeIterador =~ tr/3/e/;
                $nomeIterador =~ tr/1/i/;
                $nomeIterador =~ tr/0/o/;
            }

            if ($nomeIterador =~ m/$nome/) {
                push(@partidas, $pontuacaoIterador);
            }
        } #if (defined $nomeIterador)
        else {
        }

        if (@partidas == 0) {
            $chaveErro = "partidas_nao_encontradas";
        }
    }
    return @partidas;
}
#Le um arquivo e converte para um vetor de linhas (strings)
sub arquivoToVetor{
    open(my $arquivo, "<", shift)
        or die("\n" . $mensagensErro{"arquivo_01"} . "\n" . $!);
    my @vetor;
    while (my $linha = <$arquivo>) {
        chomp $linha;
        push @vetor, $linha;
    }
    return @vetor;
}

#Simplesmente imprime um vetor linha por linha
sub printVector{
    my @vetor = @_;
    for my $i(0 .. scalar @vetor - 1){
        print $vetor[$i] . "\n";
    }
}

#Converte uma aparencia de base para lvl 1
sub converteLvl1{
    my @aparencia = @_;
    for my $i(0 .. scalar @aparencia - 1){
        $aparencia[$i] =~ s/\|/\:/g;
        $aparencia[$i] =~ s/\=/\+/g;
        $aparencia[$i] =~ s/o/0/g;
        my ($trailing) = $aparencia[$i] =~ /^\s*/g;
        $aparencia[$i] =~ s/^\s*/\#/g;
        $aparencia[$i] =~ s/\s/\*/g;
        $aparencia[$i] =~ s/\#/$trailing/g;
    }
    return @aparencia;
}

sub converteLvl2{
    my @aparencia = @_;
    for my $i(0 .. scalar @aparencia - 1){
        $aparencia[$i] =~ s/\|/\!/g;
        $aparencia[$i] =~ s/\*/O/g;
        $aparencia[$i] =~ s/\=/\*/g;
        $aparencia[$i] =~ s/\_/=/g;
        my ($trailing) = $aparencia[$i] =~ /^\s*/g;
        $aparencia[$i] =~ s/^\s*/\%/g;
        $aparencia[$i] =~ s/\s/\#/g;
        $aparencia[$i] =~ s/\%/$trailing/g;

    }
    return @aparencia;
}

sub configuraAparencia{
    my $arquivoP = shift;
    my $arquivoO = shift;
    my @aparencias;
    my @aparenciaBaseP = arquivoToVetor($arquivoP);
    $aparencias[0][0] = \@aparenciaBaseP;
    my @aparenciaLvl1P = converteLvl1(@aparenciaBaseP);
    $aparencias[0][1] = \@aparenciaLvl1P;
    my @aparenciaLvl2P = converteLvl2(@aparenciaBaseP);
    $aparencias[0][2] = \@aparenciaLvl2P;
    my @aparenciaBaseO = arquivoToVetor($arquivoO);
    $aparencias[1][0] = \@aparenciaBaseO;
    my @aparenciaLvl1O = converteLvl1(@aparenciaBaseO);
    $aparencias[1][1] = \@aparenciaLvl1O;
    my @aparenciaLvl2O = converteLvl2(@aparenciaBaseO);
    $aparencias[1][2] = \@aparenciaLvl2O;
    return @aparencias;
}
1;
