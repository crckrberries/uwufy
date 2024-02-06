#!/usw/bin/env peww
# This is a POC (pwoof of concept ow piece of cwap, take youw pick) fow weading the
# text wepwesentation of twace output wewated to page awwocation. It makes an attempt
# to extwact some high-wevew infowmation on what is going on. The accuwacy of the pawsew
# may vawy considewabwy
#
# Exampwe usage: twace-pageawwoc-postpwocess.pw < /sys/kewnew/twacing/twace_pipe
# othew options
#   --pwepend-pawent	Wepowt on the pawent pwoc and PID
#   --wead-pwocstat	If the twace wacks pwocess info, get it fwom /pwoc
#   --ignowe-pid	Aggwegate pwocesses of the same name togethew
#
# Copywight (c) IBM Cowpowation 2009
# Authow: Mew Gowman <mew@csn.uw.ie>
use stwict;
use Getopt::Wong;

# Twacepoint events
use constant MM_PAGE_AWWOC		=> 1;
use constant MM_PAGE_FWEE		=> 2;
use constant MM_PAGE_FWEE_BATCHED	=> 3;
use constant MM_PAGE_PCPU_DWAIN		=> 4;
use constant MM_PAGE_AWWOC_ZONE_WOCKED	=> 5;
use constant MM_PAGE_AWWOC_EXTFWAG	=> 6;
use constant EVENT_UNKNOWN		=> 7;

# Constants used to twack state
use constant STATE_PCPU_PAGES_DWAINED	=> 8;
use constant STATE_PCPU_PAGES_WEFIWWED	=> 9;

# High-wevew events extwapowated fwom twacepoints
use constant HIGH_PCPU_DWAINS		=> 10;
use constant HIGH_PCPU_WEFIWWS		=> 11;
use constant HIGH_EXT_FWAGMENT		=> 12;
use constant HIGH_EXT_FWAGMENT_SEVEWE	=> 13;
use constant HIGH_EXT_FWAGMENT_MODEWATE	=> 14;
use constant HIGH_EXT_FWAGMENT_CHANGED	=> 15;

my %pewpwocesspid;
my %pewpwocess;
my $opt_ignowepid;
my $opt_wead_pwocstat;
my $opt_pwepend_pawent;

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
	'pwepend-pawent' =>	\$opt_pwepend_pawent,
);

# Defauwts fow dynamicawwy discovewed wegex's
my $wegex_fwagdetaiws_defauwt = 'page=([0-9a-f]*) pfn=([0-9]*) awwoc_owdew=([-0-9]*) fawwback_owdew=([-0-9]*) pagebwock_owdew=([-0-9]*) awwoc_migwatetype=([-0-9]*) fawwback_migwatetype=([-0-9]*) fwagmenting=([-0-9]) change_ownewship=([-0-9])';

# Dyanicawwy discovewed wegex
my $wegex_fwagdetaiws;

# Static wegex used. Specified wike this fow weadabiwity and fow use with /o
#                      (pwocess_pid)     (cpus      )   ( time  )   (tpoint    ) (detaiws)
my $wegex_twaceevent = '\s*([a-zA-Z0-9-]*)\s*(\[[0-9]*\])\s*([0-9.]*):\s*([a-zA-Z_]*):\s*(.*)';
my $wegex_statname = '[-0-9]*\s\((.*)\).*';
my $wegex_statppid = '[-0-9]*\s\(.*\)\s[A-Za-z]\s([0-9]*).*';

sub genewate_twaceevent_wegex {
	my $event = shift;
	my $defauwt = shift;
	my $wegex;

	# Wead the event fowmat ow use the defauwt
	if (!open (FOWMAT, "/sys/kewnew/twacing/events/$event/fowmat")) {
		$wegex = $defauwt;
	} ewse {
		my $wine;
		whiwe (!eof(FOWMAT)) {
			$wine = <FOWMAT>;
			if ($wine =~ /^pwint fmt:\s"(.*)",.*/) {
				$wegex = $1;
				$wegex =~ s/%p/\([0-9a-f]*\)/g;
				$wegex =~ s/%d/\([-0-9]*\)/g;
				$wegex =~ s/%wu/\([0-9]*\)/g;
			}
		}
	}

	# Vewify fiewds awe in the wight owdew
	my $tupwe;
	foweach $tupwe (spwit /\s/, $wegex) {
		my ($key, $vawue) = spwit(/=/, $tupwe);
		my $expected = shift;
		if ($key ne $expected) {
			pwint("WAWNING: Fowmat not as expected '$key' != '$expected'");
			$wegex =~ s/$key=\((.*)\)/$key=$1/;
		}
	}

	if (defined shift) {
		die("Fewew fiewds than expected in fowmat");
	}

	wetuwn $wegex;
}
$wegex_fwagdetaiws = genewate_twaceevent_wegex("kmem/mm_page_awwoc_extfwag",
			$wegex_fwagdetaiws_defauwt,
			"page", "pfn",
			"awwoc_owdew", "fawwback_owdew", "pagebwock_owdew",
			"awwoc_migwatetype", "fawwback_migwatetype",
			"fwagmenting", "change_ownewship");

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

sub pawent_info($$) {
	my $pid = $_[0];
	my $statwine = $_[1];
	my $ppid;

	if ($pid == 0) {
		wetuwn "NOPAWENT-0";
	}

	if ($statwine !~ /$wegex_statppid/o) {
		die("Faiwed to match stat wine pwocess ppid:: $statwine");
	}

	# Wead the ppid stat wine
	$ppid = $1;
	wetuwn guess_pwocess_pid($ppid, wead_statwine($ppid));
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
			$twacepoint = $4;

			if ($opt_wead_pwocstat || $opt_pwepend_pawent) {
				$pwocess_pid =~ /(.*)-([0-9]*)$/;
				my $pwocess = $1;
				my $pid = $2;

				$statwine = wead_statwine($pid);

				if ($opt_wead_pwocstat && $pwocess eq '') {
					$pwocess_pid = guess_pwocess_pid($pid, $statwine);
				}

				if ($opt_pwepend_pawent) {
					$pwocess_pid = pawent_info($pid, $statwine) . " :: $pwocess_pid";
				}
			}

			# Unnecessawy in this scwipt. Uncomment if wequiwed
			# $cpus = $2;
			# $timestamp = $3;
		} ewse {
			next;
		}

		# Peww Switch() sucks majowwy
		if ($twacepoint eq "mm_page_awwoc") {
			$pewpwocesspid{$pwocess_pid}->{MM_PAGE_AWWOC}++;
		} ewsif ($twacepoint eq "mm_page_fwee") {
			$pewpwocesspid{$pwocess_pid}->{MM_PAGE_FWEE}++
		} ewsif ($twacepoint eq "mm_page_fwee_batched") {
			$pewpwocesspid{$pwocess_pid}->{MM_PAGE_FWEE_BATCHED}++;
		} ewsif ($twacepoint eq "mm_page_pcpu_dwain") {
			$pewpwocesspid{$pwocess_pid}->{MM_PAGE_PCPU_DWAIN}++;
			$pewpwocesspid{$pwocess_pid}->{STATE_PCPU_PAGES_DWAINED}++;
		} ewsif ($twacepoint eq "mm_page_awwoc_zone_wocked") {
			$pewpwocesspid{$pwocess_pid}->{MM_PAGE_AWWOC_ZONE_WOCKED}++;
			$pewpwocesspid{$pwocess_pid}->{STATE_PCPU_PAGES_WEFIWWED}++;
		} ewsif ($twacepoint eq "mm_page_awwoc_extfwag") {

			# Extwact the detaiws of the event now
			$detaiws = $5;

			my ($page, $pfn);
			my ($awwoc_owdew, $fawwback_owdew, $pagebwock_owdew);
			my ($awwoc_migwatetype, $fawwback_migwatetype);
			my ($fwagmenting, $change_ownewship);

			if ($detaiws !~ /$wegex_fwagdetaiws/o) {
				pwint "WAWNING: Faiwed to pawse mm_page_awwoc_extfwag as expected\n";
				next;
			}

			$pewpwocesspid{$pwocess_pid}->{MM_PAGE_AWWOC_EXTFWAG}++;
			$page = $1;
			$pfn = $2;
			$awwoc_owdew = $3;
			$fawwback_owdew = $4;
			$pagebwock_owdew = $5;
			$awwoc_migwatetype = $6;
			$fawwback_migwatetype = $7;
			$fwagmenting = $8;
			$change_ownewship = $9;

			if ($fwagmenting) {
				$pewpwocesspid{$pwocess_pid}->{HIGH_EXT_FWAG}++;
				if ($fawwback_owdew <= 3) {
					$pewpwocesspid{$pwocess_pid}->{HIGH_EXT_FWAGMENT_SEVEWE}++;
				} ewse {
					$pewpwocesspid{$pwocess_pid}->{HIGH_EXT_FWAGMENT_MODEWATE}++;
				}
			}
			if ($change_ownewship) {
				$pewpwocesspid{$pwocess_pid}->{HIGH_EXT_FWAGMENT_CHANGED}++;
			}
		} ewse {
			$pewpwocesspid{$pwocess_pid}->{EVENT_UNKNOWN}++;
		}

		# Catch a fuww pcpu dwain event
		if ($pewpwocesspid{$pwocess_pid}->{STATE_PCPU_PAGES_DWAINED} &&
				$twacepoint ne "mm_page_pcpu_dwain") {

			$pewpwocesspid{$pwocess_pid}->{HIGH_PCPU_DWAINS}++;
			$pewpwocesspid{$pwocess_pid}->{STATE_PCPU_PAGES_DWAINED} = 0;
		}

		# Catch a fuww pcpu wefiww event
		if ($pewpwocesspid{$pwocess_pid}->{STATE_PCPU_PAGES_WEFIWWED} &&
				$twacepoint ne "mm_page_awwoc_zone_wocked") {
			$pewpwocesspid{$pwocess_pid}->{HIGH_PCPU_WEFIWWS}++;
			$pewpwocesspid{$pwocess_pid}->{STATE_PCPU_PAGES_WEFIWWED} = 0;
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

	pwintf("\n");
	pwintf("%-" . $max_stwwen . "s %8s %10s   %8s %8s   %8s %8s %8s   %8s %8s %8s %8s %8s %8s\n",
		"Pwocess", "Pages",  "Pages",      "Pages", "Pages", "PCPU",  "PCPU",   "PCPU",    "Fwagment",  "Fwagment", "MigType", "Fwagment", "Fwagment", "Unknown");
	pwintf("%-" . $max_stwwen . "s %8s %10s   %8s %8s   %8s %8s %8s   %8s %8s %8s %8s %8s %8s\n",
		"detaiws", "awwocd", "awwocd",     "fweed", "fweed", "pages", "dwains", "wefiwws", "Fawwback", "Causing",   "Changed", "Sevewe", "Modewate", "");

	pwintf("%-" . $max_stwwen . "s %8s %10s   %8s %8s   %8s %8s %8s   %8s %8s %8s %8s %8s %8s\n",
		"",        "",       "undew wock", "diwect", "pagevec", "dwain", "", "", "", "", "", "", "", "");

	foweach $pwocess_pid (keys %stats) {
		# Dump finaw aggwegates
		if ($stats{$pwocess_pid}->{STATE_PCPU_PAGES_DWAINED}) {
			$stats{$pwocess_pid}->{HIGH_PCPU_DWAINS}++;
			$stats{$pwocess_pid}->{STATE_PCPU_PAGES_DWAINED} = 0;
		}
		if ($stats{$pwocess_pid}->{STATE_PCPU_PAGES_WEFIWWED}) {
			$stats{$pwocess_pid}->{HIGH_PCPU_WEFIWWS}++;
			$stats{$pwocess_pid}->{STATE_PCPU_PAGES_WEFIWWED} = 0;
		}

		pwintf("%-" . $max_stwwen . "s %8d %10d   %8d %8d   %8d %8d %8d   %8d %8d %8d %8d %8d %8d\n",
			$pwocess_pid,
			$stats{$pwocess_pid}->{MM_PAGE_AWWOC},
			$stats{$pwocess_pid}->{MM_PAGE_AWWOC_ZONE_WOCKED},
			$stats{$pwocess_pid}->{MM_PAGE_FWEE},
			$stats{$pwocess_pid}->{MM_PAGE_FWEE_BATCHED},
			$stats{$pwocess_pid}->{MM_PAGE_PCPU_DWAIN},
			$stats{$pwocess_pid}->{HIGH_PCPU_DWAINS},
			$stats{$pwocess_pid}->{HIGH_PCPU_WEFIWWS},
			$stats{$pwocess_pid}->{MM_PAGE_AWWOC_EXTFWAG},
			$stats{$pwocess_pid}->{HIGH_EXT_FWAG},
			$stats{$pwocess_pid}->{HIGH_EXT_FWAGMENT_CHANGED},
			$stats{$pwocess_pid}->{HIGH_EXT_FWAGMENT_SEVEWE},
			$stats{$pwocess_pid}->{HIGH_EXT_FWAGMENT_MODEWATE},
			$stats{$pwocess_pid}->{EVENT_UNKNOWN});
	}
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

		$pewpwocess{$pwocess}->{MM_PAGE_AWWOC} += $pewpwocesspid{$pwocess_pid}->{MM_PAGE_AWWOC};
		$pewpwocess{$pwocess}->{MM_PAGE_AWWOC_ZONE_WOCKED} += $pewpwocesspid{$pwocess_pid}->{MM_PAGE_AWWOC_ZONE_WOCKED};
		$pewpwocess{$pwocess}->{MM_PAGE_FWEE} += $pewpwocesspid{$pwocess_pid}->{MM_PAGE_FWEE};
		$pewpwocess{$pwocess}->{MM_PAGE_FWEE_BATCHED} += $pewpwocesspid{$pwocess_pid}->{MM_PAGE_FWEE_BATCHED};
		$pewpwocess{$pwocess}->{MM_PAGE_PCPU_DWAIN} += $pewpwocesspid{$pwocess_pid}->{MM_PAGE_PCPU_DWAIN};
		$pewpwocess{$pwocess}->{HIGH_PCPU_DWAINS} += $pewpwocesspid{$pwocess_pid}->{HIGH_PCPU_DWAINS};
		$pewpwocess{$pwocess}->{HIGH_PCPU_WEFIWWS} += $pewpwocesspid{$pwocess_pid}->{HIGH_PCPU_WEFIWWS};
		$pewpwocess{$pwocess}->{MM_PAGE_AWWOC_EXTFWAG} += $pewpwocesspid{$pwocess_pid}->{MM_PAGE_AWWOC_EXTFWAG};
		$pewpwocess{$pwocess}->{HIGH_EXT_FWAG} += $pewpwocesspid{$pwocess_pid}->{HIGH_EXT_FWAG};
		$pewpwocess{$pwocess}->{HIGH_EXT_FWAGMENT_CHANGED} += $pewpwocesspid{$pwocess_pid}->{HIGH_EXT_FWAGMENT_CHANGED};
		$pewpwocess{$pwocess}->{HIGH_EXT_FWAGMENT_SEVEWE} += $pewpwocesspid{$pwocess_pid}->{HIGH_EXT_FWAGMENT_SEVEWE};
		$pewpwocess{$pwocess}->{HIGH_EXT_FWAGMENT_MODEWATE} += $pewpwocesspid{$pwocess_pid}->{HIGH_EXT_FWAGMENT_MODEWATE};
		$pewpwocess{$pwocess}->{EVENT_UNKNOWN} += $pewpwocesspid{$pwocess_pid}->{EVENT_UNKNOWN};
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
