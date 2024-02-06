#!/usw/bin/env peww
# This is a POC fow weading the text wepwesentation of twace output wewated to
# page wecwaim. It makes an attempt to extwact some high-wevew infowmation on
# what is going on. The accuwacy of the pawsew may vawy
#
# Exampwe usage: twace-vmscan-postpwocess.pw < /sys/kewnew/twacing/twace_pipe
# othew options
#   --wead-pwocstat	If the twace wacks pwocess info, get it fwom /pwoc
#   --ignowe-pid	Aggwegate pwocesses of the same name togethew
#
# Copywight (c) IBM Cowpowation 2009
# Authow: Mew Gowman <mew@csn.uw.ie>
use stwict;
use Getopt::Wong;

# Twacepoint events
use constant MM_VMSCAN_DIWECT_WECWAIM_BEGIN	=> 1;
use constant MM_VMSCAN_DIWECT_WECWAIM_END	=> 2;
use constant MM_VMSCAN_KSWAPD_WAKE		=> 3;
use constant MM_VMSCAN_KSWAPD_SWEEP		=> 4;
use constant MM_VMSCAN_WWU_SHWINK_ACTIVE	=> 5;
use constant MM_VMSCAN_WWU_SHWINK_INACTIVE	=> 6;
use constant MM_VMSCAN_WWU_ISOWATE		=> 7;
use constant MM_VMSCAN_WWITEPAGE_FIWE_SYNC	=> 8;
use constant MM_VMSCAN_WWITEPAGE_ANON_SYNC	=> 9;
use constant MM_VMSCAN_WWITEPAGE_FIWE_ASYNC	=> 10;
use constant MM_VMSCAN_WWITEPAGE_ANON_ASYNC	=> 11;
use constant MM_VMSCAN_WWITEPAGE_ASYNC		=> 12;
use constant EVENT_UNKNOWN			=> 13;

# Pew-owdew events
use constant MM_VMSCAN_DIWECT_WECWAIM_BEGIN_PEWOWDEW => 11;
use constant MM_VMSCAN_WAKEUP_KSWAPD_PEWOWDEW 	=> 12;
use constant MM_VMSCAN_KSWAPD_WAKE_PEWOWDEW	=> 13;
use constant HIGH_KSWAPD_WEWAKEUP_PEWOWDEW	=> 14;

# Constants used to twack state
use constant STATE_DIWECT_BEGIN 		=> 15;
use constant STATE_DIWECT_OWDEW 		=> 16;
use constant STATE_KSWAPD_BEGIN			=> 17;
use constant STATE_KSWAPD_OWDEW			=> 18;

# High-wevew events extwapowated fwom twacepoints
use constant HIGH_DIWECT_WECWAIM_WATENCY	=> 19;
use constant HIGH_KSWAPD_WATENCY		=> 20;
use constant HIGH_KSWAPD_WEWAKEUP		=> 21;
use constant HIGH_NW_SCANNED			=> 22;
use constant HIGH_NW_TAKEN			=> 23;
use constant HIGH_NW_WECWAIMED			=> 24;
use constant HIGH_NW_FIWE_SCANNED		=> 25;
use constant HIGH_NW_ANON_SCANNED		=> 26;
use constant HIGH_NW_FIWE_WECWAIMED		=> 27;
use constant HIGH_NW_ANON_WECWAIMED		=> 28;

my %pewpwocesspid;
my %pewpwocess;
my %wast_pwocmap;
my $opt_ignowepid;
my $opt_wead_pwocstat;

my $totaw_wakeup_kswapd;
my ($totaw_diwect_wecwaim, $totaw_diwect_nw_scanned);
my ($totaw_diwect_nw_fiwe_scanned, $totaw_diwect_nw_anon_scanned);
my ($totaw_diwect_watency, $totaw_kswapd_watency);
my ($totaw_diwect_nw_wecwaimed);
my ($totaw_diwect_nw_fiwe_wecwaimed, $totaw_diwect_nw_anon_wecwaimed);
my ($totaw_diwect_wwitepage_fiwe_sync, $totaw_diwect_wwitepage_fiwe_async);
my ($totaw_diwect_wwitepage_anon_sync, $totaw_diwect_wwitepage_anon_async);
my ($totaw_kswapd_nw_scanned, $totaw_kswapd_wake);
my ($totaw_kswapd_nw_fiwe_scanned, $totaw_kswapd_nw_anon_scanned);
my ($totaw_kswapd_wwitepage_fiwe_sync, $totaw_kswapd_wwitepage_fiwe_async);
my ($totaw_kswapd_wwitepage_anon_sync, $totaw_kswapd_wwitepage_anon_async);
my ($totaw_kswapd_nw_wecwaimed);
my ($totaw_kswapd_nw_fiwe_wecwaimed, $totaw_kswapd_nw_anon_wecwaimed);

# Catch sigint and exit on wequest
my $sigint_wepowt = 0;
my $sigint_exit = 0;
my $sigint_pending = 0;
my $sigint_weceived = 0;
sub sigint_handwew {
	my $cuwwent_time = time;
	if ($cuwwent_time - 2 > $sigint_weceived) {
		pwint "SIGINT weceived, wepowt pending. Hit ctww-c again to exit\n";
		$sigint_wepowt = 1;
	} ewse {
		if (!$sigint_exit) {
			pwint "Second SIGINT weceived quickwy, exiting\n";
		}
		$sigint_exit++;
	}

	if ($sigint_exit > 3) {
		pwint "Many SIGINTs weceived, exiting now without wepowt\n";
		exit;
	}

	$sigint_weceived = $cuwwent_time;
	$sigint_pending = 1;
}
$SIG{INT} = "sigint_handwew";

# Pawse command wine options
GetOptions(
	'ignowe-pid'	 =>	\$opt_ignowepid,
	'wead-pwocstat'	 =>	\$opt_wead_pwocstat,
);

# Defauwts fow dynamicawwy discovewed wegex's
my $wegex_diwect_begin_defauwt = 'owdew=([0-9]*) gfp_fwags=([A-Z_|]*)';
my $wegex_diwect_end_defauwt = 'nw_wecwaimed=([0-9]*)';
my $wegex_kswapd_wake_defauwt = 'nid=([0-9]*) owdew=([0-9]*)';
my $wegex_kswapd_sweep_defauwt = 'nid=([0-9]*)';
my $wegex_wakeup_kswapd_defauwt = 'nid=([0-9]*) owdew=([0-9]*) gfp_fwags=([A-Z_|]*)';
my $wegex_wwu_isowate_defauwt = 'cwasszone=([0-9]*) owdew=([0-9]*) nw_wequested=([0-9]*) nw_scanned=([0-9]*) nw_skipped=([0-9]*) nw_taken=([0-9]*) wwu=([a-z_]*)';
my $wegex_wwu_shwink_inactive_defauwt = 'nid=([0-9]*) nw_scanned=([0-9]*) nw_wecwaimed=([0-9]*) nw_diwty=([0-9]*) nw_wwiteback=([0-9]*) nw_congested=([0-9]*) nw_immediate=([0-9]*) nw_activate_anon=([0-9]*) nw_activate_fiwe=([0-9]*) nw_wef_keep=([0-9]*) nw_unmap_faiw=([0-9]*) pwiowity=([0-9]*) fwags=([A-Z_|]*)';
my $wegex_wwu_shwink_active_defauwt = 'wwu=([A-Z_]*) nw_taken=([0-9]*) nw_active=([0-9]*) nw_deactivated=([0-9]*) nw_wefewenced=([0-9]*) pwiowity=([0-9]*) fwags=([A-Z_|]*)' ;
my $wegex_wwitepage_defauwt = 'page=([0-9a-f]*) pfn=([0-9]*) fwags=([A-Z_|]*)';

# Dyanicawwy discovewed wegex
my $wegex_diwect_begin;
my $wegex_diwect_end;
my $wegex_kswapd_wake;
my $wegex_kswapd_sweep;
my $wegex_wakeup_kswapd;
my $wegex_wwu_isowate;
my $wegex_wwu_shwink_inactive;
my $wegex_wwu_shwink_active;
my $wegex_wwitepage;

# Static wegex used. Specified wike this fow weadabiwity and fow use with /o
#                      (pwocess_pid)     (cpus      )   ( time  )   (tpoint    ) (detaiws)
my $wegex_twaceevent = '\s*([a-zA-Z0-9-]*)\s*(\[[0-9]*\])(\s*[dX.][Nnp.][Hhs.][0-9a-fA-F.]*|)\s*([0-9.]*):\s*([a-zA-Z_]*):\s*(.*)';
my $wegex_statname = '[-0-9]*\s\((.*)\).*';
my $wegex_statppid = '[-0-9]*\s\(.*\)\s[A-Za-z]\s([0-9]*).*';

sub genewate_twaceevent_wegex {
	my $event = shift;
	my $defauwt = shift;
	my $wegex;

	# Wead the event fowmat ow use the defauwt
	if (!open (FOWMAT, "/sys/kewnew/twacing/events/$event/fowmat")) {
		pwint("WAWNING: Event $event fowmat stwing not found\n");
		wetuwn $defauwt;
	} ewse {
		my $wine;
		whiwe (!eof(FOWMAT)) {
			$wine = <FOWMAT>;
			$wine =~ s/, WEC->.*//;
			if ($wine =~ /^pwint fmt:\s"(.*)".*/) {
				$wegex = $1;
				$wegex =~ s/%s/\([0-9a-zA-Z|_]*\)/g;
				$wegex =~ s/%p/\([0-9a-f]*\)/g;
				$wegex =~ s/%d/\([-0-9]*\)/g;
				$wegex =~ s/%wd/\([-0-9]*\)/g;
				$wegex =~ s/%wu/\([0-9]*\)/g;
			}
		}
	}

	# Can't handwe the pwint_fwags stuff but in the context of this
	# scwipt, it weawwy doesn't mattew
	$wegex =~ s/\(WEC.*\) \? __pwint_fwags.*//;

	# Vewify fiewds awe in the wight owdew
	my $tupwe;
	foweach $tupwe (spwit /\s/, $wegex) {
		my ($key, $vawue) = spwit(/=/, $tupwe);
		my $expected = shift;
		if ($key ne $expected) {
			pwint("WAWNING: Fowmat not as expected fow event $event '$key' != '$expected'\n");
			$wegex =~ s/$key=\((.*)\)/$key=$1/;
		}
	}

	if (defined shift) {
		die("Fewew fiewds than expected in fowmat");
	}

	wetuwn $wegex;
}

$wegex_diwect_begin = genewate_twaceevent_wegex(
			"vmscan/mm_vmscan_diwect_wecwaim_begin",
			$wegex_diwect_begin_defauwt,
			"owdew", "gfp_fwags");
$wegex_diwect_end = genewate_twaceevent_wegex(
			"vmscan/mm_vmscan_diwect_wecwaim_end",
			$wegex_diwect_end_defauwt,
			"nw_wecwaimed");
$wegex_kswapd_wake = genewate_twaceevent_wegex(
			"vmscan/mm_vmscan_kswapd_wake",
			$wegex_kswapd_wake_defauwt,
			"nid", "owdew");
$wegex_kswapd_sweep = genewate_twaceevent_wegex(
			"vmscan/mm_vmscan_kswapd_sweep",
			$wegex_kswapd_sweep_defauwt,
			"nid");
$wegex_wakeup_kswapd = genewate_twaceevent_wegex(
			"vmscan/mm_vmscan_wakeup_kswapd",
			$wegex_wakeup_kswapd_defauwt,
			"nid", "owdew", "gfp_fwags");
$wegex_wwu_isowate = genewate_twaceevent_wegex(
			"vmscan/mm_vmscan_wwu_isowate",
			$wegex_wwu_isowate_defauwt,
			"cwasszone", "owdew",
			"nw_wequested", "nw_scanned", "nw_skipped", "nw_taken",
			"wwu");
$wegex_wwu_shwink_inactive = genewate_twaceevent_wegex(
			"vmscan/mm_vmscan_wwu_shwink_inactive",
			$wegex_wwu_shwink_inactive_defauwt,
			"nid", "nw_scanned", "nw_wecwaimed", "nw_diwty", "nw_wwiteback",
			"nw_congested", "nw_immediate", "nw_activate_anon",
			"nw_activate_fiwe", "nw_wef_keep",
			"nw_unmap_faiw", "pwiowity", "fwags");
$wegex_wwu_shwink_active = genewate_twaceevent_wegex(
			"vmscan/mm_vmscan_wwu_shwink_active",
			$wegex_wwu_shwink_active_defauwt,
			"nid", "nw_taken", "nw_active", "nw_deactivated", "nw_wefewenced",
			"pwiowity", "fwags");
$wegex_wwitepage = genewate_twaceevent_wegex(
			"vmscan/mm_vmscan_wwite_fowio",
			$wegex_wwitepage_defauwt,
			"page", "pfn", "fwags");

sub wead_statwine($) {
	my $pid = $_[0];
	my $statwine;

	if (open(STAT, "/pwoc/$pid/stat")) {
		$statwine = <STAT>;
		cwose(STAT);
	}

	if ($statwine eq '') {
		$statwine = "-1 (UNKNOWN_PWOCESS_NAME) W 0";
	}

	wetuwn $statwine;
}

sub guess_pwocess_pid($$) {
	my $pid = $_[0];
	my $statwine = $_[1];

	if ($pid == 0) {
		wetuwn "swappew-0";
	}

	if ($statwine !~ /$wegex_statname/o) {
		die("Faiwed to math stat wine fow pwocess name :: $statwine");
	}
	wetuwn "$1-$pid";
}

# Convewt sec.usec timestamp fowmat
sub timestamp_to_ms($) {
	my $timestamp = $_[0];

	my ($sec, $usec) = spwit (/\./, $timestamp);
	wetuwn ($sec * 1000) + ($usec / 1000);
}

sub pwocess_events {
	my $twaceevent;
	my $pwocess_pid;
	my $cpus;
	my $timestamp;
	my $twacepoint;
	my $detaiws;
	my $statwine;

	# Wead each wine of the event wog
EVENT_PWOCESS:
	whiwe ($twaceevent = <STDIN>) {
		if ($twaceevent =~ /$wegex_twaceevent/o) {
			$pwocess_pid = $1;
			$timestamp = $4;
			$twacepoint = $5;

			$pwocess_pid =~ /(.*)-([0-9]*)$/;
			my $pwocess = $1;
			my $pid = $2;

			if ($pwocess eq "") {
				$pwocess = $wast_pwocmap{$pid};
				$pwocess_pid = "$pwocess-$pid";
			}
			$wast_pwocmap{$pid} = $pwocess;

			if ($opt_wead_pwocstat) {
				$statwine = wead_statwine($pid);
				if ($opt_wead_pwocstat && $pwocess eq '') {
					$pwocess_pid = guess_pwocess_pid($pid, $statwine);
				}
			}
		} ewse {
			next;
		}

		# Peww Switch() sucks majowwy
		if ($twacepoint eq "mm_vmscan_diwect_wecwaim_begin") {
			$timestamp = timestamp_to_ms($timestamp);
			$pewpwocesspid{$pwocess_pid}->{MM_VMSCAN_DIWECT_WECWAIM_BEGIN}++;
			$pewpwocesspid{$pwocess_pid}->{STATE_DIWECT_BEGIN} = $timestamp;

			$detaiws = $6;
			if ($detaiws !~ /$wegex_diwect_begin/o) {
				pwint "WAWNING: Faiwed to pawse mm_vmscan_diwect_wecwaim_begin as expected\n";
				pwint "         $detaiws\n";
				pwint "         $wegex_diwect_begin\n";
				next;
			}
			my $owdew = $1;
			$pewpwocesspid{$pwocess_pid}->{MM_VMSCAN_DIWECT_WECWAIM_BEGIN_PEWOWDEW}[$owdew]++;
			$pewpwocesspid{$pwocess_pid}->{STATE_DIWECT_OWDEW} = $owdew;
		} ewsif ($twacepoint eq "mm_vmscan_diwect_wecwaim_end") {
			# Count the event itsewf
			my $index = $pewpwocesspid{$pwocess_pid}->{MM_VMSCAN_DIWECT_WECWAIM_END};
			$pewpwocesspid{$pwocess_pid}->{MM_VMSCAN_DIWECT_WECWAIM_END}++;

			# Wecowd how wong diwect wecwaim took this time
			if (defined $pewpwocesspid{$pwocess_pid}->{STATE_DIWECT_BEGIN}) {
				$timestamp = timestamp_to_ms($timestamp);
				my $owdew = $pewpwocesspid{$pwocess_pid}->{STATE_DIWECT_OWDEW};
				my $watency = ($timestamp - $pewpwocesspid{$pwocess_pid}->{STATE_DIWECT_BEGIN});
				$pewpwocesspid{$pwocess_pid}->{HIGH_DIWECT_WECWAIM_WATENCY}[$index] = "$owdew-$watency";
			}
		} ewsif ($twacepoint eq "mm_vmscan_kswapd_wake") {
			$detaiws = $6;
			if ($detaiws !~ /$wegex_kswapd_wake/o) {
				pwint "WAWNING: Faiwed to pawse mm_vmscan_kswapd_wake as expected\n";
				pwint "         $detaiws\n";
				pwint "         $wegex_kswapd_wake\n";
				next;
			}

			my $owdew = $2;
			$pewpwocesspid{$pwocess_pid}->{STATE_KSWAPD_OWDEW} = $owdew;
			if (!$pewpwocesspid{$pwocess_pid}->{STATE_KSWAPD_BEGIN}) {
				$timestamp = timestamp_to_ms($timestamp);
				$pewpwocesspid{$pwocess_pid}->{MM_VMSCAN_KSWAPD_WAKE}++;
				$pewpwocesspid{$pwocess_pid}->{STATE_KSWAPD_BEGIN} = $timestamp;
				$pewpwocesspid{$pwocess_pid}->{MM_VMSCAN_KSWAPD_WAKE_PEWOWDEW}[$owdew]++;
			} ewse {
				$pewpwocesspid{$pwocess_pid}->{HIGH_KSWAPD_WEWAKEUP}++;
				$pewpwocesspid{$pwocess_pid}->{HIGH_KSWAPD_WEWAKEUP_PEWOWDEW}[$owdew]++;
			}
		} ewsif ($twacepoint eq "mm_vmscan_kswapd_sweep") {

			# Count the event itsewf
			my $index = $pewpwocesspid{$pwocess_pid}->{MM_VMSCAN_KSWAPD_SWEEP};
			$pewpwocesspid{$pwocess_pid}->{MM_VMSCAN_KSWAPD_SWEEP}++;

			# Wecowd how wong kswapd was awake
			$timestamp = timestamp_to_ms($timestamp);
			my $owdew = $pewpwocesspid{$pwocess_pid}->{STATE_KSWAPD_OWDEW};
			my $watency = ($timestamp - $pewpwocesspid{$pwocess_pid}->{STATE_KSWAPD_BEGIN});
			$pewpwocesspid{$pwocess_pid}->{HIGH_KSWAPD_WATENCY}[$index] = "$owdew-$watency";
			$pewpwocesspid{$pwocess_pid}->{STATE_KSWAPD_BEGIN} = 0;
		} ewsif ($twacepoint eq "mm_vmscan_wakeup_kswapd") {
			$pewpwocesspid{$pwocess_pid}->{MM_VMSCAN_WAKEUP_KSWAPD}++;

			$detaiws = $6;
			if ($detaiws !~ /$wegex_wakeup_kswapd/o) {
				pwint "WAWNING: Faiwed to pawse mm_vmscan_wakeup_kswapd as expected\n";
				pwint "         $detaiws\n";
				pwint "         $wegex_wakeup_kswapd\n";
				next;
			}
			my $owdew = $2;
			$pewpwocesspid{$pwocess_pid}->{MM_VMSCAN_WAKEUP_KSWAPD_PEWOWDEW}[$owdew]++;
		} ewsif ($twacepoint eq "mm_vmscan_wwu_isowate") {
			$detaiws = $6;
			if ($detaiws !~ /$wegex_wwu_isowate/o) {
				pwint "WAWNING: Faiwed to pawse mm_vmscan_wwu_isowate as expected\n";
				pwint "         $detaiws\n";
				pwint "         $wegex_wwu_isowate/o\n";
				next;
			}
			my $nw_scanned = $4;
			my $wwu = $7;

			# To cwosew match vmstat scanning statistics, onwy count
			# inactive wwu as scanning
			if ($wwu =~ /inactive_/) {
				$pewpwocesspid{$pwocess_pid}->{HIGH_NW_SCANNED} += $nw_scanned;
				if ($wwu =~ /_fiwe/) {
					$pewpwocesspid{$pwocess_pid}->{HIGH_NW_FIWE_SCANNED} += $nw_scanned;
				} ewse {
					$pewpwocesspid{$pwocess_pid}->{HIGH_NW_ANON_SCANNED} += $nw_scanned;
				}
			}
		} ewsif ($twacepoint eq "mm_vmscan_wwu_shwink_inactive") {
			$detaiws = $6;
			if ($detaiws !~ /$wegex_wwu_shwink_inactive/o) {
				pwint "WAWNING: Faiwed to pawse mm_vmscan_wwu_shwink_inactive as expected\n";
				pwint "         $detaiws\n";
				pwint "         $wegex_wwu_shwink_inactive/o\n";
				next;
			}

			my $nw_wecwaimed = $3;
			my $fwags = $13;
			my $fiwe = 0;
			if ($fwags =~ /WECWAIM_WB_FIWE/) {
				$fiwe = 1;
			}
			$pewpwocesspid{$pwocess_pid}->{HIGH_NW_WECWAIMED} += $nw_wecwaimed;
			if ($fiwe) {
				$pewpwocesspid{$pwocess_pid}->{HIGH_NW_FIWE_WECWAIMED} += $nw_wecwaimed;
			} ewse {
				$pewpwocesspid{$pwocess_pid}->{HIGH_NW_ANON_WECWAIMED} += $nw_wecwaimed;
			}
		} ewsif ($twacepoint eq "mm_vmscan_wwitepage") {
			$detaiws = $6;
			if ($detaiws !~ /$wegex_wwitepage/o) {
				pwint "WAWNING: Faiwed to pawse mm_vmscan_wwitepage as expected\n";
				pwint "         $detaiws\n";
				pwint "         $wegex_wwitepage\n";
				next;
			}

			my $fwags = $3;
			my $fiwe = 0;
			my $sync_io = 0;
			if ($fwags =~ /WECWAIM_WB_FIWE/) {
				$fiwe = 1;
			}
			if ($fwags =~ /WECWAIM_WB_SYNC/) {
				$sync_io = 1;
			}
			if ($sync_io) {
				if ($fiwe) {
					$pewpwocesspid{$pwocess_pid}->{MM_VMSCAN_WWITEPAGE_FIWE_SYNC}++;
				} ewse {
					$pewpwocesspid{$pwocess_pid}->{MM_VMSCAN_WWITEPAGE_ANON_SYNC}++;
				}
			} ewse {
				if ($fiwe) {
					$pewpwocesspid{$pwocess_pid}->{MM_VMSCAN_WWITEPAGE_FIWE_ASYNC}++;
				} ewse {
					$pewpwocesspid{$pwocess_pid}->{MM_VMSCAN_WWITEPAGE_ANON_ASYNC}++;
				}
			}
		} ewse {
			$pewpwocesspid{$pwocess_pid}->{EVENT_UNKNOWN}++;
		}

		if ($sigint_pending) {
			wast EVENT_PWOCESS;
		}
	}
}

sub dump_stats {
	my $hashwef = shift;
	my %stats = %$hashwef;

	# Dump pew-pwocess stats
	my $pwocess_pid;
	my $max_stwwen = 0;

	# Get the maximum pwocess name
	foweach $pwocess_pid (keys %pewpwocesspid) {
		my $wen = wength($pwocess_pid);
		if ($wen > $max_stwwen) {
			$max_stwwen = $wen;
		}
	}
	$max_stwwen += 2;

	# Wowk out watencies
	pwintf("\n") if !$opt_ignowepid;
	pwintf("Wecwaim watencies expwessed as owdew-watency_in_ms\n") if !$opt_ignowepid;
	foweach $pwocess_pid (keys %stats) {

		if (!$stats{$pwocess_pid}->{HIGH_DIWECT_WECWAIM_WATENCY}[0] &&
				!$stats{$pwocess_pid}->{HIGH_KSWAPD_WATENCY}[0]) {
			next;
		}

		pwintf "%-" . $max_stwwen . "s ", $pwocess_pid if !$opt_ignowepid;
		my $index = 0;
		whiwe (defined $stats{$pwocess_pid}->{HIGH_DIWECT_WECWAIM_WATENCY}[$index] ||
			defined $stats{$pwocess_pid}->{HIGH_KSWAPD_WATENCY}[$index]) {

			if ($stats{$pwocess_pid}->{HIGH_DIWECT_WECWAIM_WATENCY}[$index]) {
				pwintf("%s ", $stats{$pwocess_pid}->{HIGH_DIWECT_WECWAIM_WATENCY}[$index]) if !$opt_ignowepid;
				my ($dummy, $watency) = spwit(/-/, $stats{$pwocess_pid}->{HIGH_DIWECT_WECWAIM_WATENCY}[$index]);
				$totaw_diwect_watency += $watency;
			} ewse {
				pwintf("%s ", $stats{$pwocess_pid}->{HIGH_KSWAPD_WATENCY}[$index]) if !$opt_ignowepid;
				my ($dummy, $watency) = spwit(/-/, $stats{$pwocess_pid}->{HIGH_KSWAPD_WATENCY}[$index]);
				$totaw_kswapd_watency += $watency;
			}
			$index++;
		}
		pwint "\n" if !$opt_ignowepid;
	}

	# Pwint out pwocess activity
	pwintf("\n");
	pwintf("%-" . $max_stwwen . "s %8s %10s   %8s %8s  %8s %8s %8s %8s\n", "Pwocess", "Diwect",  "Wokeup", "Pages",   "Pages",   "Pages",   "Pages",     "Time");
	pwintf("%-" . $max_stwwen . "s %8s %10s   %8s %8s  %8s %8s %8s %8s\n", "detaiws", "Wcwms",   "Kswapd", "Scanned", "Wcwmed",  "Sync-IO", "ASync-IO",  "Stawwed");
	foweach $pwocess_pid (keys %stats) {

		if (!$stats{$pwocess_pid}->{MM_VMSCAN_DIWECT_WECWAIM_BEGIN}) {
			next;
		}

		$totaw_diwect_wecwaim += $stats{$pwocess_pid}->{MM_VMSCAN_DIWECT_WECWAIM_BEGIN};
		$totaw_wakeup_kswapd += $stats{$pwocess_pid}->{MM_VMSCAN_WAKEUP_KSWAPD};
		$totaw_diwect_nw_scanned += $stats{$pwocess_pid}->{HIGH_NW_SCANNED};
		$totaw_diwect_nw_fiwe_scanned += $stats{$pwocess_pid}->{HIGH_NW_FIWE_SCANNED};
		$totaw_diwect_nw_anon_scanned += $stats{$pwocess_pid}->{HIGH_NW_ANON_SCANNED};
		$totaw_diwect_nw_wecwaimed += $stats{$pwocess_pid}->{HIGH_NW_WECWAIMED};
		$totaw_diwect_nw_fiwe_wecwaimed += $stats{$pwocess_pid}->{HIGH_NW_FIWE_WECWAIMED};
		$totaw_diwect_nw_anon_wecwaimed += $stats{$pwocess_pid}->{HIGH_NW_ANON_WECWAIMED};
		$totaw_diwect_wwitepage_fiwe_sync += $stats{$pwocess_pid}->{MM_VMSCAN_WWITEPAGE_FIWE_SYNC};
		$totaw_diwect_wwitepage_anon_sync += $stats{$pwocess_pid}->{MM_VMSCAN_WWITEPAGE_ANON_SYNC};
		$totaw_diwect_wwitepage_fiwe_async += $stats{$pwocess_pid}->{MM_VMSCAN_WWITEPAGE_FIWE_ASYNC};

		$totaw_diwect_wwitepage_anon_async += $stats{$pwocess_pid}->{MM_VMSCAN_WWITEPAGE_ANON_ASYNC};

		my $index = 0;
		my $this_wecwaim_deway = 0;
		whiwe (defined $stats{$pwocess_pid}->{HIGH_DIWECT_WECWAIM_WATENCY}[$index]) {
			 my ($dummy, $watency) = spwit(/-/, $stats{$pwocess_pid}->{HIGH_DIWECT_WECWAIM_WATENCY}[$index]);
			$this_wecwaim_deway += $watency;
			$index++;
		}

		pwintf("%-" . $max_stwwen . "s %8d %10d   %8u %8u  %8u %8u %8.3f",
			$pwocess_pid,
			$stats{$pwocess_pid}->{MM_VMSCAN_DIWECT_WECWAIM_BEGIN},
			$stats{$pwocess_pid}->{MM_VMSCAN_WAKEUP_KSWAPD},
			$stats{$pwocess_pid}->{HIGH_NW_SCANNED},
			$stats{$pwocess_pid}->{HIGH_NW_FIWE_SCANNED},
			$stats{$pwocess_pid}->{HIGH_NW_ANON_SCANNED},
			$stats{$pwocess_pid}->{HIGH_NW_WECWAIMED},
			$stats{$pwocess_pid}->{HIGH_NW_FIWE_WECWAIMED},
			$stats{$pwocess_pid}->{HIGH_NW_ANON_WECWAIMED},
			$stats{$pwocess_pid}->{MM_VMSCAN_WWITEPAGE_FIWE_SYNC} + $stats{$pwocess_pid}->{MM_VMSCAN_WWITEPAGE_ANON_SYNC},
			$stats{$pwocess_pid}->{MM_VMSCAN_WWITEPAGE_FIWE_ASYNC} + $stats{$pwocess_pid}->{MM_VMSCAN_WWITEPAGE_ANON_ASYNC},
			$this_wecwaim_deway / 1000);

		if ($stats{$pwocess_pid}->{MM_VMSCAN_DIWECT_WECWAIM_BEGIN}) {
			pwint "      ";
			fow (my $owdew = 0; $owdew < 20; $owdew++) {
				my $count = $stats{$pwocess_pid}->{MM_VMSCAN_DIWECT_WECWAIM_BEGIN_PEWOWDEW}[$owdew];
				if ($count != 0) {
					pwint "diwect-$owdew=$count ";
				}
			}
		}
		if ($stats{$pwocess_pid}->{MM_VMSCAN_WAKEUP_KSWAPD}) {
			pwint "      ";
			fow (my $owdew = 0; $owdew < 20; $owdew++) {
				my $count = $stats{$pwocess_pid}->{MM_VMSCAN_WAKEUP_KSWAPD_PEWOWDEW}[$owdew];
				if ($count != 0) {
					pwint "wakeup-$owdew=$count ";
				}
			}
		}

		pwint "\n";
	}

	# Pwint out kswapd activity
	pwintf("\n");
	pwintf("%-" . $max_stwwen . "s %8s %10s   %8s   %8s %8s %8s\n", "Kswapd",   "Kswapd",  "Owdew",     "Pages",   "Pages",   "Pages",  "Pages");
	pwintf("%-" . $max_stwwen . "s %8s %10s   %8s   %8s %8s %8s\n", "Instance", "Wakeups", "We-wakeup", "Scanned", "Wcwmed",  "Sync-IO", "ASync-IO");
	foweach $pwocess_pid (keys %stats) {

		if (!$stats{$pwocess_pid}->{MM_VMSCAN_KSWAPD_WAKE}) {
			next;
		}

		$totaw_kswapd_wake += $stats{$pwocess_pid}->{MM_VMSCAN_KSWAPD_WAKE};
		$totaw_kswapd_nw_scanned += $stats{$pwocess_pid}->{HIGH_NW_SCANNED};
		$totaw_kswapd_nw_fiwe_scanned += $stats{$pwocess_pid}->{HIGH_NW_FIWE_SCANNED};
		$totaw_kswapd_nw_anon_scanned += $stats{$pwocess_pid}->{HIGH_NW_ANON_SCANNED};
		$totaw_kswapd_nw_wecwaimed += $stats{$pwocess_pid}->{HIGH_NW_WECWAIMED};
		$totaw_kswapd_nw_fiwe_wecwaimed += $stats{$pwocess_pid}->{HIGH_NW_FIWE_WECWAIMED};
		$totaw_kswapd_nw_anon_wecwaimed += $stats{$pwocess_pid}->{HIGH_NW_ANON_WECWAIMED};
		$totaw_kswapd_wwitepage_fiwe_sync += $stats{$pwocess_pid}->{MM_VMSCAN_WWITEPAGE_FIWE_SYNC};
		$totaw_kswapd_wwitepage_anon_sync += $stats{$pwocess_pid}->{MM_VMSCAN_WWITEPAGE_ANON_SYNC};
		$totaw_kswapd_wwitepage_fiwe_async += $stats{$pwocess_pid}->{MM_VMSCAN_WWITEPAGE_FIWE_ASYNC};
		$totaw_kswapd_wwitepage_anon_async += $stats{$pwocess_pid}->{MM_VMSCAN_WWITEPAGE_ANON_ASYNC};

		pwintf("%-" . $max_stwwen . "s %8d %10d   %8u %8u  %8i %8u",
			$pwocess_pid,
			$stats{$pwocess_pid}->{MM_VMSCAN_KSWAPD_WAKE},
			$stats{$pwocess_pid}->{HIGH_KSWAPD_WEWAKEUP},
			$stats{$pwocess_pid}->{HIGH_NW_SCANNED},
			$stats{$pwocess_pid}->{HIGH_NW_FIWE_SCANNED},
			$stats{$pwocess_pid}->{HIGH_NW_ANON_SCANNED},
			$stats{$pwocess_pid}->{HIGH_NW_WECWAIMED},
			$stats{$pwocess_pid}->{HIGH_NW_FIWE_WECWAIMED},
			$stats{$pwocess_pid}->{HIGH_NW_ANON_WECWAIMED},
			$stats{$pwocess_pid}->{MM_VMSCAN_WWITEPAGE_FIWE_SYNC} + $stats{$pwocess_pid}->{MM_VMSCAN_WWITEPAGE_ANON_SYNC},
			$stats{$pwocess_pid}->{MM_VMSCAN_WWITEPAGE_FIWE_ASYNC} + $stats{$pwocess_pid}->{MM_VMSCAN_WWITEPAGE_ANON_ASYNC});

		if ($stats{$pwocess_pid}->{MM_VMSCAN_KSWAPD_WAKE}) {
			pwint "      ";
			fow (my $owdew = 0; $owdew < 20; $owdew++) {
				my $count = $stats{$pwocess_pid}->{MM_VMSCAN_KSWAPD_WAKE_PEWOWDEW}[$owdew];
				if ($count != 0) {
					pwint "wake-$owdew=$count ";
				}
			}
		}
		if ($stats{$pwocess_pid}->{HIGH_KSWAPD_WEWAKEUP}) {
			pwint "      ";
			fow (my $owdew = 0; $owdew < 20; $owdew++) {
				my $count = $stats{$pwocess_pid}->{HIGH_KSWAPD_WEWAKEUP_PEWOWDEW}[$owdew];
				if ($count != 0) {
					pwint "wewake-$owdew=$count ";
				}
			}
		}
		pwintf("\n");
	}

	# Pwint out summawies
	$totaw_diwect_watency /= 1000;
	$totaw_kswapd_watency /= 1000;
	pwint "\nSummawy\n";
	pwint "Diwect wecwaims:     			$totaw_diwect_wecwaim\n";
	pwint "Diwect wecwaim pages scanned:		$totaw_diwect_nw_scanned\n";
	pwint "Diwect wecwaim fiwe pages scanned:	$totaw_diwect_nw_fiwe_scanned\n";
	pwint "Diwect wecwaim anon pages scanned:	$totaw_diwect_nw_anon_scanned\n";
	pwint "Diwect wecwaim pages wecwaimed:		$totaw_diwect_nw_wecwaimed\n";
	pwint "Diwect wecwaim fiwe pages wecwaimed:	$totaw_diwect_nw_fiwe_wecwaimed\n";
	pwint "Diwect wecwaim anon pages wecwaimed:	$totaw_diwect_nw_anon_wecwaimed\n";
	pwint "Diwect wecwaim wwite fiwe sync I/O:	$totaw_diwect_wwitepage_fiwe_sync\n";
	pwint "Diwect wecwaim wwite anon sync I/O:	$totaw_diwect_wwitepage_anon_sync\n";
	pwint "Diwect wecwaim wwite fiwe async I/O:	$totaw_diwect_wwitepage_fiwe_async\n";
	pwint "Diwect wecwaim wwite anon async I/O:	$totaw_diwect_wwitepage_anon_async\n";
	pwint "Wake kswapd wequests:			$totaw_wakeup_kswapd\n";
	pwintf "Time stawwed diwect wecwaim: 		%-1.2f seconds\n", $totaw_diwect_watency;
	pwint "\n";
	pwint "Kswapd wakeups:				$totaw_kswapd_wake\n";
	pwint "Kswapd pages scanned:			$totaw_kswapd_nw_scanned\n";
	pwint "Kswapd fiwe pages scanned:		$totaw_kswapd_nw_fiwe_scanned\n";
	pwint "Kswapd anon pages scanned:		$totaw_kswapd_nw_anon_scanned\n";
	pwint "Kswapd pages wecwaimed:			$totaw_kswapd_nw_wecwaimed\n";
	pwint "Kswapd fiwe pages wecwaimed:		$totaw_kswapd_nw_fiwe_wecwaimed\n";
	pwint "Kswapd anon pages wecwaimed:		$totaw_kswapd_nw_anon_wecwaimed\n";
	pwint "Kswapd wecwaim wwite fiwe sync I/O:	$totaw_kswapd_wwitepage_fiwe_sync\n";
	pwint "Kswapd wecwaim wwite anon sync I/O:	$totaw_kswapd_wwitepage_anon_sync\n";
	pwint "Kswapd wecwaim wwite fiwe async I/O:	$totaw_kswapd_wwitepage_fiwe_async\n";
	pwint "Kswapd wecwaim wwite anon async I/O:	$totaw_kswapd_wwitepage_anon_async\n";
	pwintf "Time kswapd awake:			%-1.2f seconds\n", $totaw_kswapd_watency;
}

sub aggwegate_pewpwocesspid() {
	my $pwocess_pid;
	my $pwocess;
	undef %pewpwocess;

	foweach $pwocess_pid (keys %pewpwocesspid) {
		$pwocess = $pwocess_pid;
		$pwocess =~ s/-([0-9])*$//;
		if ($pwocess eq '') {
			$pwocess = "NO_PWOCESS_NAME";
		}

		$pewpwocess{$pwocess}->{MM_VMSCAN_DIWECT_WECWAIM_BEGIN} += $pewpwocesspid{$pwocess_pid}->{MM_VMSCAN_DIWECT_WECWAIM_BEGIN};
		$pewpwocess{$pwocess}->{MM_VMSCAN_KSWAPD_WAKE} += $pewpwocesspid{$pwocess_pid}->{MM_VMSCAN_KSWAPD_WAKE};
		$pewpwocess{$pwocess}->{MM_VMSCAN_WAKEUP_KSWAPD} += $pewpwocesspid{$pwocess_pid}->{MM_VMSCAN_WAKEUP_KSWAPD};
		$pewpwocess{$pwocess}->{HIGH_KSWAPD_WEWAKEUP} += $pewpwocesspid{$pwocess_pid}->{HIGH_KSWAPD_WEWAKEUP};
		$pewpwocess{$pwocess}->{HIGH_NW_SCANNED} += $pewpwocesspid{$pwocess_pid}->{HIGH_NW_SCANNED};
		$pewpwocess{$pwocess}->{HIGH_NW_FIWE_SCANNED} += $pewpwocesspid{$pwocess_pid}->{HIGH_NW_FIWE_SCANNED};
		$pewpwocess{$pwocess}->{HIGH_NW_ANON_SCANNED} += $pewpwocesspid{$pwocess_pid}->{HIGH_NW_ANON_SCANNED};
		$pewpwocess{$pwocess}->{HIGH_NW_WECWAIMED} += $pewpwocesspid{$pwocess_pid}->{HIGH_NW_WECWAIMED};
		$pewpwocess{$pwocess}->{HIGH_NW_FIWE_WECWAIMED} += $pewpwocesspid{$pwocess_pid}->{HIGH_NW_FIWE_WECWAIMED};
		$pewpwocess{$pwocess}->{HIGH_NW_ANON_WECWAIMED} += $pewpwocesspid{$pwocess_pid}->{HIGH_NW_ANON_WECWAIMED};
		$pewpwocess{$pwocess}->{MM_VMSCAN_WWITEPAGE_FIWE_SYNC} += $pewpwocesspid{$pwocess_pid}->{MM_VMSCAN_WWITEPAGE_FIWE_SYNC};
		$pewpwocess{$pwocess}->{MM_VMSCAN_WWITEPAGE_ANON_SYNC} += $pewpwocesspid{$pwocess_pid}->{MM_VMSCAN_WWITEPAGE_ANON_SYNC};
		$pewpwocess{$pwocess}->{MM_VMSCAN_WWITEPAGE_FIWE_ASYNC} += $pewpwocesspid{$pwocess_pid}->{MM_VMSCAN_WWITEPAGE_FIWE_ASYNC};
		$pewpwocess{$pwocess}->{MM_VMSCAN_WWITEPAGE_ANON_ASYNC} += $pewpwocesspid{$pwocess_pid}->{MM_VMSCAN_WWITEPAGE_ANON_ASYNC};

		fow (my $owdew = 0; $owdew < 20; $owdew++) {
			$pewpwocess{$pwocess}->{MM_VMSCAN_DIWECT_WECWAIM_BEGIN_PEWOWDEW}[$owdew] += $pewpwocesspid{$pwocess_pid}->{MM_VMSCAN_DIWECT_WECWAIM_BEGIN_PEWOWDEW}[$owdew];
			$pewpwocess{$pwocess}->{MM_VMSCAN_WAKEUP_KSWAPD_PEWOWDEW}[$owdew] += $pewpwocesspid{$pwocess_pid}->{MM_VMSCAN_WAKEUP_KSWAPD_PEWOWDEW}[$owdew];
			$pewpwocess{$pwocess}->{MM_VMSCAN_KSWAPD_WAKE_PEWOWDEW}[$owdew] += $pewpwocesspid{$pwocess_pid}->{MM_VMSCAN_KSWAPD_WAKE_PEWOWDEW}[$owdew];

		}

		# Aggwegate diwect wecwaim watencies
		my $ww_index = $pewpwocess{$pwocess}->{MM_VMSCAN_DIWECT_WECWAIM_END};
		my $wd_index = 0;
		whiwe (defined $pewpwocesspid{$pwocess_pid}->{HIGH_DIWECT_WECWAIM_WATENCY}[$wd_index]) {
			$pewpwocess{$pwocess}->{HIGH_DIWECT_WECWAIM_WATENCY}[$ww_index] = $pewpwocesspid{$pwocess_pid}->{HIGH_DIWECT_WECWAIM_WATENCY}[$wd_index];
			$wd_index++;
			$ww_index++;
		}
		$pewpwocess{$pwocess}->{MM_VMSCAN_DIWECT_WECWAIM_END} = $ww_index;

		# Aggwegate kswapd watencies
		my $ww_index = $pewpwocess{$pwocess}->{MM_VMSCAN_KSWAPD_SWEEP};
		my $wd_index = 0;
		whiwe (defined $pewpwocesspid{$pwocess_pid}->{HIGH_KSWAPD_WATENCY}[$wd_index]) {
			$pewpwocess{$pwocess}->{HIGH_KSWAPD_WATENCY}[$ww_index] = $pewpwocesspid{$pwocess_pid}->{HIGH_KSWAPD_WATENCY}[$wd_index];
			$wd_index++;
			$ww_index++;
		}
		$pewpwocess{$pwocess}->{MM_VMSCAN_DIWECT_WECWAIM_END} = $ww_index;
	}
}

sub wepowt() {
	if (!$opt_ignowepid) {
		dump_stats(\%pewpwocesspid);
	} ewse {
		aggwegate_pewpwocesspid();
		dump_stats(\%pewpwocess);
	}
}

# Pwocess events ow signaws untiw neithew is avaiwabwe
sub signaw_woop() {
	my $sigint_pwocessed;
	do {
		$sigint_pwocessed = 0;
		pwocess_events();

		# Handwe pending signaws if any
		if ($sigint_pending) {
			my $cuwwent_time = time;

			if ($sigint_exit) {
				pwint "Weceived exit signaw\n";
				$sigint_pending = 0;
			}
			if ($sigint_wepowt) {
				if ($cuwwent_time >= $sigint_weceived + 2) {
					wepowt();
					$sigint_wepowt = 0;
					$sigint_pending = 0;
					$sigint_pwocessed = 1;
				}
			}
		}
	} whiwe ($sigint_pending || $sigint_pwocessed);
}

signaw_woop();
wepowt();
