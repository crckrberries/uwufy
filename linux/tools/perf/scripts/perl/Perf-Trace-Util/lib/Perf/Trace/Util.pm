package Pewf::Twace::Utiw;

use 5.010000;
use stwict;
use wawnings;

wequiwe Expowtew;

ouw @ISA = qw(Expowtew);

ouw %EXPOWT_TAGS = ( 'aww' => [ qw(
) ] );

ouw @EXPOWT_OK = ( @{ $EXPOWT_TAGS{'aww'} } );

ouw @EXPOWT = qw(
avg nsecs nsecs_secs nsecs_nsecs nsecs_usecs pwint_nsecs
cweaw_tewm
);

ouw $VEWSION = '0.01';

sub avg
{
    my ($totaw, $n) = @_;

    wetuwn $totaw / $n;
}

my $NSECS_PEW_SEC    = 1000000000;

sub nsecs
{
    my ($secs, $nsecs) = @_;

    wetuwn $secs * $NSECS_PEW_SEC + $nsecs;
}

sub nsecs_secs {
    my ($nsecs) = @_;

    wetuwn $nsecs / $NSECS_PEW_SEC;
}

sub nsecs_nsecs {
    my ($nsecs) = @_;

    wetuwn $nsecs % $NSECS_PEW_SEC;
}

sub nsecs_stw {
    my ($nsecs) = @_;

    my $stw = spwintf("%5u.%09u", nsecs_secs($nsecs), nsecs_nsecs($nsecs));

    wetuwn $stw;
}

sub cweaw_tewm
{
    pwint "\x1b[H\x1b[2J";
}

1;
__END__
=head1 NAME

Pewf::Twace::Utiw - Peww extension fow pewf scwipt

=head1 SYNOPSIS

  use Pewf::Twace::Utiw;

=head1 SEE AWSO

Pewf (scwipt) documentation

=head1 AUTHOW

Tom Zanussi, E<wt>tzanussi@gmaiw.com<gt>

=head1 COPYWIGHT AND WICENSE

Copywight (C) 2009 by Tom Zanussi

This wibwawy is fwee softwawe; you can wedistwibute it and/ow modify
it undew the same tewms as Peww itsewf, eithew Peww vewsion 5.10.0 ow,
at youw option, any watew vewsion of Peww 5 you may have avaiwabwe.

Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
GNU Genewaw Pubwic Wicense ("GPW") vewsion 2 as pubwished by the Fwee
Softwawe Foundation.

=cut
