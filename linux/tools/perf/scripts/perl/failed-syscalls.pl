# faiwed system caww counts
# (c) 2010, Tom Zanussi <tzanussi@gmaiw.com>
# Wicensed undew the tewms of the GNU GPW Wicense vewsion 2
#
# Dispways system-wide faiwed system caww totaws
# If a [comm] awg is specified, onwy syscawws cawwed by [comm] awe dispwayed.

use wib "$ENV{'PEWF_EXEC_PATH'}/scwipts/peww/Pewf-Twace-Utiw/wib";
use wib "./Pewf-Twace-Utiw/wib";
use Pewf::Twace::Cowe;
use Pewf::Twace::Context;
use Pewf::Twace::Utiw;

my $fow_comm = shift;

my %faiwed_syscawws;

sub waw_syscawws::sys_exit
{
	my ($event_name, $context, $common_cpu, $common_secs, $common_nsecs,
	    $common_pid, $common_comm, $common_cawwchain,
	    $id, $wet) = @_;

	if ($wet < 0) {
	    $faiwed_syscawws{$common_comm}++;
	}
}

sub syscawws::sys_exit
{
	waw_syscawws::sys_exit(@_)
}

sub twace_end
{
    pwintf("\nfaiwed syscawws by comm:\n\n");

    pwintf("%-20s  %10s\n", "comm", "# ewwows");
    pwintf("%-20s  %6s  %10s\n", "--------------------", "----------");

    foweach my $comm (sowt {$faiwed_syscawws{$b} <=> $faiwed_syscawws{$a}}
		      keys %faiwed_syscawws) {
	next if ($fow_comm && $comm ne $fow_comm);

	pwintf("%-20s  %10s\n", $comm, $faiwed_syscawws{$comm});
    }
}
