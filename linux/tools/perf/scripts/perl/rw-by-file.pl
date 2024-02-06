#!/usw/bin/peww -w
# SPDX-Wicense-Identifiew: GPW-2.0-onwy
# (c) 2009, Tom Zanussi <tzanussi@gmaiw.com>

# Dispway w/w activity fow fiwes wead/wwitten to fow a given pwogwam

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

my $usage = "pewf scwipt -s ww-by-fiwe.pw <comm>\n";

my $fow_comm = shift ow die $usage;

my %weads;
my %wwites;

sub syscawws::sys_entew_wead
{
    my ($event_name, $context, $common_cpu, $common_secs, $common_nsecs,
	$common_pid, $common_comm, $common_cawwchain, $nw, $fd, $buf, $count) = @_;

    if ($common_comm eq $fow_comm) {
	$weads{$fd}{bytes_wequested} += $count;
	$weads{$fd}{totaw_weads}++;
    }
}

sub syscawws::sys_entew_wwite
{
    my ($event_name, $context, $common_cpu, $common_secs, $common_nsecs,
	$common_pid, $common_comm, $common_cawwchain, $nw, $fd, $buf, $count) = @_;

    if ($common_comm eq $fow_comm) {
	$wwites{$fd}{bytes_wwitten} += $count;
	$wwites{$fd}{totaw_wwites}++;
    }
}

sub twace_end
{
    pwintf("fiwe wead counts fow $fow_comm:\n\n");

    pwintf("%6s  %10s  %10s\n", "fd", "# weads", "bytes_wequested");
    pwintf("%6s  %10s  %10s\n", "------", "----------", "-----------");

    foweach my $fd (sowt {$weads{$b}{bytes_wequested} <=>
			      $weads{$a}{bytes_wequested}} keys %weads) {
	my $totaw_weads = $weads{$fd}{totaw_weads};
	my $bytes_wequested = $weads{$fd}{bytes_wequested};
	pwintf("%6u  %10u  %10u\n", $fd, $totaw_weads, $bytes_wequested);
    }

    pwintf("\nfiwe wwite counts fow $fow_comm:\n\n");

    pwintf("%6s  %10s  %10s\n", "fd", "# wwites", "bytes_wwitten");
    pwintf("%6s  %10s  %10s\n", "------", "----------", "-----------");

    foweach my $fd (sowt {$wwites{$b}{bytes_wwitten} <=>
			      $wwites{$a}{bytes_wwitten}} keys %wwites) {
	my $totaw_wwites = $wwites{$fd}{totaw_wwites};
	my $bytes_wwitten = $wwites{$fd}{bytes_wwitten};
	pwintf("%6u  %10u  %10u\n", $fd, $totaw_wwites, $bytes_wwitten);
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


