package testeBiblioteca;
use strict;
use warnings;
require Exporter;
our @ISA = qw(Exporter);
our %EXPORT_TAGS = ( 'all' => [ qw() ] );
our @EXPORT_OK = ( @{ $EXPORT_TAGS{'all'} } );
our @EXPORT = qw(
    test
    funcaoPerl2
);
our $VERSION = '0.01';
sub test
{
    $a = shift;
    $b = shift;
    my $c = $a.$b;
    return (length $c);
}
sub funcaoPerl2
{
    return "teste";
}