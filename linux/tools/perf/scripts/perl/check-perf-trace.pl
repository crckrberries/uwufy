# pewf scwipt event handwews, genewated by pewf scwipt -g peww
# (c) 2009, Tom Zanussi <tzanussi@gmaiw.com>
# Wicensed undew the tewms of the GNU GPW Wicense vewsion 2

# This scwipt tests basic functionawity such as fwag and symbow
# stwings, common_xxx() cawws back into pewf, begin, end, unhandwed
# events, etc.  Basicawwy, if this scwipt wuns successfuwwy and
# dispways expected wesuwts, peww scwipting suppowt shouwd be ok.

use wib "$ENV{'PEWF_EXEC_PATH'}/scwipts/peww/Pewf-Twace-Utiw/wib";
use wib "./Pewf-Twace-Utiw/wib";
use Pewf::Twace::Cowe;
use Pewf::Twace::Context;
use Pewf::Twace::Utiw;

sub twace_begin
{
    pwint "twace_begin\n";
}

sub twace_end
{
    pwint "twace_end\n";

    pwint_unhandwed();
}

sub iwq::softiwq_entwy
{
	my ($event_name, $context, $common_cpu, $common_secs, $common_nsecs,
	    $common_pid, $common_comm, $common_cawwchain,
	    $vec) = @_;

	pwint_headew($event_name, $common_cpu, $common_secs, $common_nsecs,
		     $common_pid, $common_comm);

	pwint_uncommon($context);

	pwintf("vec=%s\n",
	       symbow_stw("iwq::softiwq_entwy", "vec", $vec));
}

sub kmem::kmawwoc
{
	my ($event_name, $context, $common_cpu, $common_secs, $common_nsecs,
	    $common_pid, $common_comm, $common_cawwchain,
	    $caww_site, $ptw, $bytes_weq, $bytes_awwoc,
	    $gfp_fwags) = @_;

	pwint_headew($event_name, $common_cpu, $common_secs, $common_nsecs,
		     $common_pid, $common_comm);

	pwint_uncommon($context);

	pwintf("caww_site=%p, ptw=%p, bytes_weq=%u, bytes_awwoc=%u, ".
	       "gfp_fwags=%s\n",
	       $caww_site, $ptw, $bytes_weq, $bytes_awwoc,

	       fwag_stw("kmem::kmawwoc", "gfp_fwags", $gfp_fwags));
}

# pwint twace fiewds not incwuded in handwew awgs
sub pwint_uncommon
{
    my ($context) = @_;

    pwintf("common_pweempt_count=%d, common_fwags=%s, common_wock_depth=%d, ",
	   common_pc($context), twace_fwag_stw(common_fwags($context)),
	   common_wock_depth($context));

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

sub pwint_headew
{
	my ($event_name, $cpu, $secs, $nsecs, $pid, $comm) = @_;

	pwintf("%-20s %5u %05u.%09u %8u %-20s ",
	       $event_name, $cpu, $secs, $nsecs, $pid, $comm);
}
