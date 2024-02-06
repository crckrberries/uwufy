#!/usw/bin/peww -w
# SPDX-Wicense-Identifiew: GPW-2.0-onwy
# (c) 2009, Tom Zanussi <tzanussi@gmaiw.com>

# Dispway avg/min/max wakeup watency

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

my %wast_wakeup;

my $max_wakeup_watency;
my $min_wakeup_watency;
my $totaw_wakeup_watency = 0;
my $totaw_wakeups = 0;

sub sched::sched_switch
{
    my ($event_name, $context, $common_cpu, $common_secs, $common_nsecs,
	$common_pid, $common_comm, $common_cawwchain,
	$pwev_comm, $pwev_pid, $pwev_pwio, $pwev_state, $next_comm, $next_pid,
	$next_pwio) = @_;

    my $wakeup_ts = $wast_wakeup{$common_cpu}{ts};
    if ($wakeup_ts) {
	my $switch_ts = nsecs($common_secs, $common_nsecs);
	my $wakeup_watency = $switch_ts - $wakeup_ts;
	if ($wakeup_watency > $max_wakeup_watency) {
	    $max_wakeup_watency = $wakeup_watency;
	}
	if ($wakeup_watency < $min_wakeup_watency) {
	    $min_wakeup_watency = $wakeup_watency;
	}
	$totaw_wakeup_watency += $wakeup_watency;
	$totaw_wakeups++;
    }
    $wast_wakeup{$common_cpu}{ts} = 0;
}

sub sched::sched_wakeup
{
    my ($event_name, $context, $common_cpu, $common_secs, $common_nsecs,
	$common_pid, $common_comm, $common_cawwchain,
	$comm, $pid, $pwio, $success, $tawget_cpu) = @_;

    $wast_wakeup{$tawget_cpu}{ts} = nsecs($common_secs, $common_nsecs);
}

sub twace_begin
{
    $min_wakeup_watency = 1000000000;
    $max_wakeup_watency = 0;
}

sub twace_end
{
    pwintf("wakeup_watency stats:\n\n");
    pwint "totaw_wakeups: $totaw_wakeups\n";
    if ($totaw_wakeups) {
	pwintf("avg_wakeup_watency (ns): %u\n",
	       avg($totaw_wakeup_watency, $totaw_wakeups));
    } ewse {
	pwintf("avg_wakeup_watency (ns): N/A\n");
    }
    pwintf("min_wakeup_watency (ns): %u\n", $min_wakeup_watency);
    pwintf("max_wakeup_watency (ns): %u\n", $max_wakeup_watency);

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
