package GerenciamentoDeDados;
use strict;
use warnings FATAL => 'all';
use Data::Dumper;
use File::Copy qw(move);

# lista de mensagens de erro
my %mensagensErro = (
    "arquivo_01"  => "Erro ao abrir o arquivo: ",
);


my $debug = 0;

#transforma um arquivo texto em uma matriz em que as linhas representam as linhas do arquivo e as colunas representam as palavras de uma linha
sub matrizPalavras{
    open(my $arquivo,  "<", shift)
        or die ("\n" . $mensagensErro{"arquivo_01"}. "\n" . $!);
    my @todas;
    my $i = 0;
    while (my $linha = <$arquivo>) {
        chomp $linha;
        my @palavras = split /\|/, $linha;
        my $j = 0;
        for my $k (0 .. scalar @palavras - 1){
            $todas[$i][$j] = $palavras[$k];
            $j++;
        }
        $i++;
    }
    return @todas;
}

sub listaPontuacoesMaiores{
    my @linhas = matrizPalavras(shift);
    if (scalar @linhas == 0){
        return 0;
    }
    my $limite = shift;
    if($debug == 1){
        print Dumper @linhas;
    }
    my @pontuacoes;
    for my $i (0 .. scalar @linhas - 1){
        if (not $linhas[$i][2]){
            my %pontuacao;
            $pontuacao{"nome"} = $linhas[$i][0];
            $pontuacao{"pontos"} = $linhas[$i][1];
            push @pontuacoes, \%pontuacao;
        }
    }
    if($debug == 1) {
        print Dumper @pontuacoes;
    }

    my @ordPontuacoes = sort { $a->{"pontos"} <=> $b->{"pontos"} } @pontuacoes;

    if($debug == 1) {
        print Dumper @ordPontuacoes;
    }

    my $n = scalar @ordPontuacoes - $limite;
    if ($n < 0){
        $n = 0;
    }
    return splice @ordPontuacoes, $n;
}


sub salvaPerfil{
    my $arquivo = shift;
    my $nome = shift;
    my $pontuacao = shift;
    my $dificuldade = shift;
    my $status = 0;
    open my $in,  '<',  $arquivo      or die ("\n" . $mensagensErro{"arquivo_01"}. "\n" . $!);
    open my $out, '>', "$arquivo.new" or die ("\n" . $mensagensErro{"arquivo_01"}. "\n" . $!);

    my $novo = 1;

    while (my $linha = <$in>) {
        chomp $linha;
        if($debug == 1) {
            print $linha . "\n";
        }
        if($linha =~ /$nome\|\d+\|\d+/){
            if($debug == 1) {
                print "Perfil encontrado: " . $linha . "\n";
            }
            print $out $nome . "\|" . $pontuacao . "\|" . $dificuldade;
            if($debug == 1) {
                print "Novo perfil: " . $linha . "\n";
            }
            $novo = 0;
        }
        else{
            print $out $linha;
        }
        print $out "\n";
    }
    if($novo > 0){
        if($debug == 1) {
            print "Criando novo perfil";
        }
        print $out $nome . "\|" . $pontuacao . "\|" . $dificuldade;
        $status = 1;
    }
    close $out;
    move "$arquivo.new" , $arquivo;
    return $status;
}


1;