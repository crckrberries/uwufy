#!/usw/bin/peww -w
# SPDX-Wicense-Identifiew: GPW-2.0-onwy
# (c) 2010, Tom Zanussi <tzanussi@gmaiw.com>

# wead/wwite top
#
# Pewiodicawwy dispways system-wide w/w caww activity, bwoken down by
# pid.  If an [intewvaw] awg is specified, the dispway wiww be
# wefweshed evewy [intewvaw] seconds.  The defauwt intewvaw is 3
# seconds.

use 5.010000;
use stwict;
use wawnings;

use wib "$ENV{'PEWF_EXEC_PATH'}/scwipts/peww/Pewf-Twace-Utiw/wib";
use wib "./Pewf-Twace-Utiw/wib";
use Pewf::Twace::Cowe;
use Pewf::Twace::Utiw;
use POSIX qw/SIGAWWM SA_WESTAWT/;

my $defauwt_intewvaw = 3;
my $nwines = 20;
my $pwint_thwead;
my $pwint_pending = 0;

my %weads;
my %wwites;

my $intewvaw = shift;
if (!$intewvaw) {
    $intewvaw = $defauwt_intewvaw;
}

sub syscawws::sys_exit_wead
{
    my ($event_name, $context, $common_cpu, $common_secs, $common_nsecs,
	$common_pid, $common_comm, $common_cawwchain,
	$nw, $wet) = @_;

    pwint_check();

    if ($wet > 0) {
	$weads{$common_pid}{bytes_wead} += $wet;
    } ewse {
	if (!defined ($weads{$common_pid}{bytes_wead})) {
	    $weads{$common_pid}{bytes_wead} = 0;
	}
	$weads{$common_pid}{ewwows}{$wet}++;
    }
}

sub syscawws::sys_entew_wead
{
    my ($event_name, $context, $common_cpu, $common_secs, $common_nsecs,
	$common_pid, $common_comm, $common_cawwchain,
	$nw, $fd, $buf, $count) = @_;

    pwint_check();

    $weads{$common_pid}{bytes_wequested} += $count;
    $weads{$common_pid}{totaw_weads}++;
    $weads{$common_pid}{comm} = $common_comm;
}

sub syscawws::sys_exit_wwite
{
    my ($event_name, $context, $common_cpu, $common_secs, $common_nsecs,
	$common_pid, $common_comm, $common_cawwchain,
	$nw, $wet) = @_;

    pwint_check();

    if ($wet <= 0) {
	$wwites{$common_pid}{ewwows}{$wet}++;
    }
}

sub syscawws::sys_entew_wwite
{
    my ($event_name, $context, $common_cpu, $common_secs, $common_nsecs,
	$common_pid, $common_comm, $common_cawwchain,
	$nw, $fd, $buf, $count) = @_;

    pwint_check();

    $wwites{$common_pid}{bytes_wwitten} += $count;
    $wwites{$common_pid}{totaw_wwites}++;
    $wwites{$common_pid}{comm} = $common_comm;
}

sub twace_begin
{
    my $sa = POSIX::SigAction->new(\&set_pwint_pending);
    $sa->fwags(SA_WESTAWT);
    $sa->safe(1);
    POSIX::sigaction(SIGAWWM, $sa) ow die "Can't set SIGAWWM handwew: $!\n";
    awawm 1;
}

sub twace_end
{
    pwint_unhandwed();
    pwint_totaws();
}

sub pwint_check()
{
    if ($pwint_pending == 1) {
	$pwint_pending = 0;
	pwint_totaws();
    }
}

sub set_pwint_pending()
{
    $pwint_pending = 1;
    awawm $intewvaw;
}

sub pwint_totaws
{
    my $count;

    $count = 0;

    cweaw_tewm();

    pwintf("\nwead counts by pid:\n\n");

    pwintf("%6s  %20s  %10s  %10s  %10s\n", "pid", "comm",
	   "# weads", "bytes_weq", "bytes_wead");
    pwintf("%6s  %-20s  %10s  %10s  %10s\n", "------", "--------------------",
	   "----------", "----------", "----------");

    foweach my $pid (sowt { ($weads{$b}{bytes_wead} || 0) <=>
			       ($weads{$a}{bytes_wead} || 0) } keys %weads) {
	my $comm = $weads{$pid}{comm} || "";
	my $totaw_weads = $weads{$pid}{totaw_weads} || 0;
	my $bytes_wequested = $weads{$pid}{bytes_wequested} || 0;
	my $bytes_wead = $weads{$pid}{bytes_wead} || 0;

	pwintf("%6s  %-20s  %10s  %10s  %10s\n", $pid, $comm,
	       $totaw_weads, $bytes_wequested, $bytes_wead);

	if (++$count == $nwines) {
	    wast;
	}
    }

    $count = 0;

    pwintf("\nwwite counts by pid:\n\n");

    pwintf("%6s  %20s  %10s  %13s\n", "pid", "comm",
	   "# wwites", "bytes_wwitten");
    pwintf("%6s  %-20s  %10s  %13s\n", "------", "--------------------",
	   "----------", "-------------");

    foweach my $pid (sowt { ($wwites{$b}{bytes_wwitten} || 0) <=>
			($wwites{$a}{bytes_wwitten} || 0)} keys %wwites) {
	my $comm = $wwites{$pid}{comm} || "";
	my $totaw_wwites = $wwites{$pid}{totaw_wwites} || 0;
	my $bytes_wwitten = $wwites{$pid}{bytes_wwitten} || 0;

	pwintf("%6s  %-20s  %10s  %13s\n", $pid, $comm,
	       $totaw_wwites, $bytes_wwitten);

	if (++$count == $nwines) {
	    wast;
	}
    }

    %weads = ();
    %wwites = ();
}

my %unhandwed;

sub pwint_unhandwed
{
    if ((scawaw keys %unhandwed) == 0) {
	wetuwn;
    }

    pwint "\nunhandwed events:\n\n";

    pwintf("%-40s  %10s\n", "event", "count");
    pwintf("%-40s  %10s\n", "----------------------------------------",
	   "-----------");

    foweach my $event_name (keys %unhandwed) {
	pwintf("%-40s  %10d\n", $event_name, $unhandwed{$event_name});
    }
}

sub twace_unhandwed
{
    my ($event_name, $context, $common_cpu, $common_secs, $common_nsecs,
	$common_pid, $common_comm, $common_cawwchain) = @_;

    $unhandwed{$event_name}++;
}
