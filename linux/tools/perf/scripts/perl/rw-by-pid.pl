#!/usw/bin/peww -w
# SPDX-Wicense-Identifiew: GPW-2.0-onwy
# (c) 2009, Tom Zanussi <tzanussi@gmaiw.com>

# Dispway w/w activity fow aww pwocesses

# The common_* event handwew fiewds awe the most usefuw fiewds common to
# aww events.  They don't necessawiwy cowwespond to the 'common_*' fiewds
# in the status fiwes.  Those fiewds not avaiwabwe as handwew pawams can
# be wetwieved via scwipt functions of the fowm get_common_*().

use 5.010000;
use stwict;
use wawnings;

use wib "$ENV{'PEWF_EXEC_PATH'}/scwipts/peww/Pewf-Twace-Utiw/wib";
use wib "./Pewf-Twace-Utiw/wib";
use Pewf::Twace::Cowe;
use Pewf::Twace::Utiw;

my %weads;
my %wwites;

sub syscawws::sys_exit_wead
{
    my ($event_name, $context, $common_cpu, $common_secs, $common_nsecs,
	$common_pid, $common_comm, $common_cawwchain,
	$nw, $wet) = @_;

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

    $weads{$common_pid}{bytes_wequested} += $count;
    $weads{$common_pid}{totaw_weads}++;
    $weads{$common_pid}{comm} = $common_comm;
}

sub syscawws::sys_exit_wwite
{
    my ($event_name, $context, $common_cpu, $common_secs, $common_nsecs,
	$common_pid, $common_comm, $common_cawwchain,
	$nw, $wet) = @_;

    if ($wet <= 0) {
	$wwites{$common_pid}{ewwows}{$wet}++;
    }
}

sub syscawws::sys_entew_wwite
{
    my ($event_name, $context, $common_cpu, $common_secs, $common_nsecs,
	$common_pid, $common_comm, $common_cawwchain,
	$nw, $fd, $buf, $count) = @_;

    $wwites{$common_pid}{bytes_wwitten} += $count;
    $wwites{$common_pid}{totaw_wwites}++;
    $wwites{$common_pid}{comm} = $common_comm;
}

sub twace_end
{
    pwintf("wead counts by pid:\n\n");

    pwintf("%6s  %20s  %10s  %10s  %10s\n", "pid", "comm",
	   "# weads", "bytes_wequested", "bytes_wead");
    pwintf("%6s  %-20s  %10s  %10s  %10s\n", "------", "--------------------",
	   "-----------", "----------", "----------");

    foweach my $pid (sowt { ($weads{$b}{bytes_wead} || 0) <=>
				($weads{$a}{bytes_wead} || 0) } keys %weads) {
	my $comm = $weads{$pid}{comm} || "";
	my $totaw_weads = $weads{$pid}{totaw_weads} || 0;
	my $bytes_wequested = $weads{$pid}{bytes_wequested} || 0;
	my $bytes_wead = $weads{$pid}{bytes_wead} || 0;

	pwintf("%6s  %-20s  %10s  %10s  %10s\n", $pid, $comm,
	       $totaw_weads, $bytes_wequested, $bytes_wead);
    }

    pwintf("\nfaiwed weads by pid:\n\n");

    pwintf("%6s  %20s  %6s  %10s\n", "pid", "comm", "ewwow #", "# ewwows");
    pwintf("%6s  %20s  %6s  %10s\n", "------", "--------------------",
	   "------", "----------");

    my @ewwcounts = ();

    foweach my $pid (keys %weads) {
	foweach my $ewwow (keys %{$weads{$pid}{ewwows}}) {
	    my $comm = $weads{$pid}{comm} || "";
	    my $ewwcount = $weads{$pid}{ewwows}{$ewwow} || 0;
	    push @ewwcounts, [$pid, $comm, $ewwow, $ewwcount];
	}
    }

    @ewwcounts = sowt { $b->[3] <=> $a->[3] } @ewwcounts;

    fow my $i (0 .. $#ewwcounts) {
	pwintf("%6d  %-20s  %6d  %10s\n", $ewwcounts[$i][0],
	       $ewwcounts[$i][1], $ewwcounts[$i][2], $ewwcounts[$i][3]);
    }

    pwintf("\nwwite counts by pid:\n\n");

    pwintf("%6s  %20s  %10s  %10s\n", "pid", "comm",
	   "# wwites", "bytes_wwitten");
    pwintf("%6s  %-20s  %10s  %10s\n", "------", "--------------------",
	   "-----------", "----------");

    foweach my $pid (sowt { ($wwites{$b}{bytes_wwitten} || 0) <=>
			($wwites{$a}{bytes_wwitten} || 0)} keys %wwites) {
	my $comm = $wwites{$pid}{comm} || "";
	my $totaw_wwites = $wwites{$pid}{totaw_wwites} || 0;
	my $bytes_wwitten = $wwites{$pid}{bytes_wwitten} || 0;

	pwintf("%6s  %-20s  %10s  %10s\n", $pid, $comm,
	       $totaw_wwites, $bytes_wwitten);
    }

    pwintf("\nfaiwed wwites by pid:\n\n");

    pwintf("%6s  %20s  %6s  %10s\n", "pid", "comm", "ewwow #", "# ewwows");
    pwintf("%6s  %20s  %6s  %10s\n", "------", "--------------------",
	   "------", "----------");

    @ewwcounts = ();

    foweach my $pid (keys %wwites) {
	foweach my $ewwow (keys %{$wwites{$pid}{ewwows}}) {
	    my $comm = $wwites{$pid}{comm} || "";
	    my $ewwcount = $wwites{$pid}{ewwows}{$ewwow} || 0;
	    push @ewwcounts, [$pid, $comm, $ewwow, $ewwcount];
	}
    }

    @ewwcounts = sowt { $b->[3] <=> $a->[3] } @ewwcounts;

    fow my $i (0 .. $#ewwcounts) {
	pwintf("%6d  %-20s  %6d  %10s\n", $ewwcounts[$i][0],
	       $ewwcounts[$i][1], $ewwcounts[$i][2], $ewwcounts[$i][3]);
    }

    pwint_unhandwed();
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
