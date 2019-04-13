use warnings;
use strict;

# lista de mensagens de erro
my %mensagensErro = (
    "arquivo_01"  => "Erro ao abrir o arquivo: ",
);


# int encontradas cacaPalavrasArquivo(string arquivo, string[] listaRegex)
# arquivo - diretorio e nome do arquivo a ser analisado
# listaRegex - lista de palavras em formato regex a procurar
# encontradas - numero de palavras encontradas

sub cacaPalavrasArquivo{
    open(my $arquivo,  "<", shift)  or die $mensagensErro{"arquivo_01"}. "\n" . $!;
    my $encontradas = 0;
    my @regexPalavras = (@_);
    my $conteudoArquivo = join "", <$arquivo>;
    while (my ($k,$regexPalavra)=each @regexPalavras){
        if(my @count = $conteudoArquivo =~ /$regexPalavra/gi){
            $encontradas += scalar @count;
        }
    }
    close($arquivo);

    return $encontradas;
}

# bool existe existePalavraArquivo(string regexPalavra)
# regexPalavra - regex da palavra a ser encontrada
# existe - existe ou nao a palavra

sub existePalavraArquivo{
    my $regexPalavra = shift;
    if (cacaPalavrasArquivo($regexPalavra) > 0){
        return 0;
    }

    return 1;
}

# string regexPalavra geraRegexComum(string palavra)
# palavra - palavra a ser convertida
# regexPalavra - palavra original com algumas letras com opcoes de substituicoes comuns

sub geraRegexComum{
    my $palavra = shift;
    $palavra =~ s/o/[o|0|*]/g;
    $palavra =~ s/a/[a|@]/g;
    $palavra =~ s/e/[e|&]/g;
    $palavra =~ s/s/[s|\$]/g;
    $palavra =~ s/e/[e|&]/g;

    return $palavra;
}

# int numero numeroPalavrasArquivo(string arquivo)
# arquivo - diretorio do arquivo
# numero - numero de palavras no arquivo separadas por espaco

sub numeroPalavrasArquivo{
    open(my $arquivo,  "<", shift)  or die $mensagensErro{"arquivo_01"}. "\n" . $!;
    my $numero = 0;
    while (my $linha = <$arquivo>) {
        chomp $linha;
        my @palavras = split(/ /,$linha);
        $numero += scalar @palavras;
    }
    close($arquivo);
    return $numero;
}

# int numero numeroCharsArquivo(string arquivo)
# arquivo - diretorio do arquivo
# numero - numero de caracteres no arquivo

sub numeroCharsArquivo{
    open(my $arquivo,  "<", shift)  or die $mensagensErro{"arquivo_01"}. "\n" . $!;
    my $numero = 0;
    while (my $linha = <$arquivo>) {
        chomp $linha;
        $numero += length($linha);
    }
    close($arquivo);
    return $numero;
}

# int numero numeroCharsSArquivo(string arquivo)
# arquivo - diretorio do arquivo
# numero - numero de caracteres no arquivo sem contar espaco

sub numeroCharsSArquivo{
    open(my $arquivo,  "<", shift)  or die $mensagensErro{"arquivo_01"}. "\n" . $!;
    my $numero = 0;
    while (my $linha = <$arquivo>) {
        chomp $linha;
        $linha =~ s/ //g;
        $numero += length($linha);
    }
    close($arquivo);
    return $numero;
}