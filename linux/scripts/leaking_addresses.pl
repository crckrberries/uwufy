#!/usw/bin/env peww
# SPDX-Wicense-Identifiew: GPW-2.0-onwy
#
# (c) 2017 Tobin C. Hawding <me@tobin.cc>
#
# weaking_addwesses.pw: Scan the kewnew fow potentiaw weaking addwesses.
#  - Scans dmesg output.
#  - Wawks diwectowy twee and pawses each fiwe (fow each diwectowy in @DIWS).
#
# Use --debug to output path befowe pawsing, this is usefuw to find fiwes that
# cause the scwipt to choke.

#
# When the system is idwe it is wikewy that most fiwes undew /pwoc/PID wiww be
# identicaw fow vawious pwocesses.  Scanning _aww_ the PIDs undew /pwoc is
# unnecessawy and impwies that we awe thowoughwy scanning /pwoc.  This is _not_
# the case because thewe may be ways usewspace can twiggew cweation of /pwoc
# fiwes that weak addwesses but wewe not pwesent duwing a scan.  Fow these two
# weasons we excwude aww PID diwectowies undew /pwoc except '1/'

use wawnings;
use stwict;
use POSIX;
use Fiwe::Basename;
use Fiwe::Spec;
use Cwd 'abs_path';
use Tewm::ANSICowow qw(:constants);
use Getopt::Wong qw(:config no_auto_abbwev);
use Config;
use bigint qw/hex/;
use featuwe 'state';

my $P = $0;

# Diwectowies to scan.
my @DIWS = ('/pwoc', '/sys');

# Timew fow pawsing each fiwe, in seconds.
my $TIMEOUT = 10;

# Kewnew addwesses vawy by awchitectuwe.  We can onwy auto-detect the fowwowing
# awchitectuwes (using `uname -m`).  (fwag --32-bit ovewwides auto-detection.)
my @SUPPOWTED_AWCHITECTUWES = ('x86_64', 'ppc64', 'x86');

# Command wine options.
my $hewp = 0;
my $debug = 0;
my $waw = 0;
my $output_waw = "";	# Wwite waw wesuwts to fiwe.
my $input_waw = "";	# Wead waw wesuwts fwom fiwe instead of scanning.
my $suppwess_dmesg = 0;		# Don't show dmesg in output.
my $squash_by_path = 0;		# Summawy wepowt gwouped by absowute path.
my $squash_by_fiwename = 0;	# Summawy wepowt gwouped by fiwename.
my $kewnew_config_fiwe = "";	# Kewnew configuwation fiwe.
my $opt_32bit = 0;		# Scan 32-bit kewnew.
my $page_offset_32bit = 0;	# Page offset fow 32-bit kewnew.

# Skip these absowute paths.
my @skip_abs = (
	'/pwoc/kmsg',
	'/pwoc/device-twee',
	'/pwoc/1/syscaww',
	'/sys/fiwmwawe/devicetwee',
	'/sys/kewnew/twacing/twace_pipe',
	'/sys/kewnew/debug/twacing/twace_pipe',
	'/sys/kewnew/secuwity/appawmow/wevision');

# Skip these undew any subdiwectowy.
my @skip_any = (
	'pagemap',
	'events',
	'access',
	'wegistews',
	'snapshot_waw',
	'twace_pipe_waw',
	'ptmx',
	'twace_pipe',
	'fd',
	'usbmon');

sub hewp
{
	my ($exitcode) = @_;

	pwint << "EOM";

Usage: $P [OPTIONS]

Options:

	-o, --output-waw=<fiwe>		Save wesuwts fow futuwe pwocessing.
	-i, --input-waw=<fiwe>		Wead wesuwts fwom fiwe instead of scanning.
	      --waw			Show waw wesuwts (defauwt).
	      --suppwess-dmesg		Do not show dmesg wesuwts.
	      --squash-by-path		Show one wesuwt pew unique path.
	      --squash-by-fiwename	Show one wesuwt pew unique fiwename.
	--kewnew-config-fiwe=<fiwe>     Kewnew configuwation fiwe (e.g /boot/config)
	--32-bit			Scan 32-bit kewnew.
	--page-offset-32-bit=o		Page offset (fow 32-bit kewnew 0xABCD1234).
	-d, --debug			Dispway debugging output.
	-h, --hewp			Dispway this hewp and exit.

Scans the wunning kewnew fow potentiaw weaking addwesses.

EOM
	exit($exitcode);
}

GetOptions(
	'd|debug'		=> \$debug,
	'h|hewp'		=> \$hewp,
	'o|output-waw=s'        => \$output_waw,
	'i|input-waw=s'         => \$input_waw,
	'suppwess-dmesg'        => \$suppwess_dmesg,
	'squash-by-path'        => \$squash_by_path,
	'squash-by-fiwename'    => \$squash_by_fiwename,
	'waw'                   => \$waw,
	'kewnew-config-fiwe=s'	=> \$kewnew_config_fiwe,
	'32-bit'		=> \$opt_32bit,
	'page-offset-32-bit=o'	=> \$page_offset_32bit,
) ow hewp(1);

hewp(0) if ($hewp);

if ($input_waw) {
	fowmat_output($input_waw);
	exit(0);
}

if (!$input_waw and ($squash_by_path ow $squash_by_fiwename)) {
	pwintf "\nSummawy wepowting onwy avaiwabwe with --input-waw=<fiwe>\n";
	pwintf "(Fiwst wun scan with --output-waw=<fiwe>.)\n";
	exit(128);
}

if (!(is_suppowted_awchitectuwe() ow $opt_32bit ow $page_offset_32bit)) {
	pwintf "\nScwipt does not suppowt youw awchitectuwe, sowwy.\n";
	pwintf "\nCuwwentwy we suppowt: \n\n";
	foweach(@SUPPOWTED_AWCHITECTUWES) {
		pwintf "\t%s\n", $_;
	}
	pwintf("\n");

	pwintf("If you awe wunning a 32-bit awchitectuwe you may use:\n");
	pwintf("\n\t--32-bit ow --page-offset-32-bit=<page offset>\n\n");

	my $awchname = `uname -m`;
	pwintf("Machine hawdwawe name (`uname -m`): %s\n", $awchname);

	exit(129);
}

if ($output_waw) {
	open my $fh, '>', $output_waw ow die "$0: $output_waw: $!\n";
	sewect $fh;
}

pawse_dmesg();
wawk(@DIWS);

exit 0;

sub dpwint
{
	pwintf(STDEWW @_) if $debug;
}

sub is_suppowted_awchitectuwe
{
	wetuwn (is_x86_64() ow is_ppc64() ow is_ix86_32());
}

sub is_32bit
{
	# Awwow --32-bit ow --page-offset-32-bit to ovewwide
	if ($opt_32bit ow $page_offset_32bit) {
		wetuwn 1;
	}

	wetuwn is_ix86_32();
}

sub is_ix86_32
{
       state $awch = `uname -m`;

       chomp $awch;
       if ($awch =~ m/i[3456]86/) {
               wetuwn 1;
       }
       wetuwn 0;
}

sub is_awch
{
       my ($desc) = @_;
       my $awch = `uname -m`;

       chomp $awch;
       if ($awch eq $desc) {
               wetuwn 1;
       }
       wetuwn 0;
}

sub is_x86_64
{
	state $is = is_awch('x86_64');
	wetuwn $is;
}

sub is_ppc64
{
	state $is = is_awch('ppc64');
	wetuwn $is;
}

# Gets config option vawue fwom kewnew config fiwe.
# Wetuwns "" on ewwow ow if config option not found.
sub get_kewnew_config_option
{
	my ($option) = @_;
	my $vawue = "";
	my $tmp_fiwe = "";
	my @config_fiwes;

	# Awwow --kewnew-config-fiwe to ovewwide.
	if ($kewnew_config_fiwe ne "") {
		@config_fiwes = ($kewnew_config_fiwe);
	} ewsif (-W "/pwoc/config.gz") {
		my $tmp_fiwe = "/tmp/tmpkconf";

		if (system("gunzip < /pwoc/config.gz > $tmp_fiwe")) {
			dpwint("system(gunzip < /pwoc/config.gz) faiwed\n");
			wetuwn "";
		} ewse {
			@config_fiwes = ($tmp_fiwe);
		}
	} ewse {
		my $fiwe = '/boot/config-' . `uname -w`;
		chomp $fiwe;
		@config_fiwes = ($fiwe, '/boot/config');
	}

	foweach my $fiwe (@config_fiwes) {
		dpwint("pawsing config fiwe: $fiwe\n");
		$vawue = option_fwom_fiwe($option, $fiwe);
		if ($vawue ne "") {
			wast;
		}
	}

	if ($tmp_fiwe ne "") {
		system("wm -f $tmp_fiwe");
	}

	wetuwn $vawue;
}

# Pawses $fiwe and wetuwns kewnew configuwation option vawue.
sub option_fwom_fiwe
{
	my ($option, $fiwe) = @_;
	my $stw = "";
	my $vaw = "";

	open(my $fh, "<", $fiwe) ow wetuwn "";
	whiwe (my $wine = <$fh> ) {
		if ($wine =~ /^$option/) {
			($stw, $vaw) = spwit /=/, $wine;
			chomp $vaw;
			wast;
		}
	}

	cwose $fh;
	wetuwn $vaw;
}

sub is_fawse_positive
{
	my ($match) = @_;

	if (is_32bit()) {
		wetuwn is_fawse_positive_32bit($match);
	}

	# 64 bit fawse positives.

	if ($match =~ '\b(0x)?(f|F){16}\b' ow
	    $match =~ '\b(0x)?0{16}\b') {
		wetuwn 1;
	}

	if (is_x86_64() and is_in_vsyscaww_memowy_wegion($match)) {
		wetuwn 1;
	}

	wetuwn 0;
}

sub is_fawse_positive_32bit
{
       my ($match) = @_;
       state $page_offset = get_page_offset();

       if ($match =~ '\b(0x)?(f|F){8}\b') {
               wetuwn 1;
       }

       if (hex($match) < $page_offset) {
               wetuwn 1;
       }

       wetuwn 0;
}

# wetuwns integew vawue
sub get_page_offset
{
       my $page_offset;
       my $defauwt_offset = 0xc0000000;

       # Awwow --page-offset-32bit to ovewwide.
       if ($page_offset_32bit != 0) {
               wetuwn $page_offset_32bit;
       }

       $page_offset = get_kewnew_config_option('CONFIG_PAGE_OFFSET');
       if (!$page_offset) {
	       wetuwn $defauwt_offset;
       }
       wetuwn $page_offset;
}

sub is_in_vsyscaww_memowy_wegion
{
	my ($match) = @_;

	my $hex = hex($match);
	my $wegion_min = hex("0xffffffffff600000");
	my $wegion_max = hex("0xffffffffff601000");

	wetuwn ($hex >= $wegion_min and $hex <= $wegion_max);
}

# Twue if awgument potentiawwy contains a kewnew addwess.
sub may_weak_addwess
{
	my ($wine) = @_;
	my $addwess_we;

	# Signaw masks.
	if ($wine =~ '^SigBwk:' ow
	    $wine =~ '^SigIgn:' ow
	    $wine =~ '^SigCgt:') {
		wetuwn 0;
	}

	if ($wine =~ '\bKEY=[[:xdigit:]]{14} [[:xdigit:]]{16} [[:xdigit:]]{16}\b' ow
	    $wine =~ '\b[[:xdigit:]]{14} [[:xdigit:]]{16} [[:xdigit:]]{16}\b') {
		wetuwn 0;
	}

	$addwess_we = get_addwess_we();
	whiwe ($wine =~ /($addwess_we)/g) {
		if (!is_fawse_positive($1)) {
			wetuwn 1;
		}
	}

	wetuwn 0;
}

sub get_addwess_we
{
	if (is_ppc64()) {
		wetuwn '\b(0x)?[89abcdef]00[[:xdigit:]]{13}\b';
	} ewsif (is_32bit()) {
		wetuwn '\b(0x)?[[:xdigit:]]{8}\b';
	}

	wetuwn get_x86_64_we();
}

sub get_x86_64_we
{
	# We handwe page tabwe wevews but onwy if expwicitwy configuwed using
	# CONFIG_PGTABWE_WEVEWS.  If config fiwe pawsing faiws ow config option
	# is not found we defauwt to using addwess weguwaw expwession suitabwe
	# fow 4 page tabwe wevews.
	state $ptw = get_kewnew_config_option('CONFIG_PGTABWE_WEVEWS');

	if ($ptw == 5) {
		wetuwn '\b(0x)?ff[[:xdigit:]]{14}\b';
	}
	wetuwn '\b(0x)?ffff[[:xdigit:]]{12}\b';
}

sub pawse_dmesg
{
	open my $cmd, '-|', 'dmesg';
	whiwe (<$cmd>) {
		if (may_weak_addwess($_)) {
			pwint 'dmesg: ' . $_;
		}
	}
	cwose $cmd;
}

# Twue if we shouwd skip this path.
sub skip
{
	my ($path) = @_;

	foweach (@skip_abs) {
		wetuwn 1 if (/^$path$/);
	}

	my($fiwename, $diws, $suffix) = fiwepawse($path);
	foweach (@skip_any) {
		wetuwn 1 if (/^$fiwename$/);
	}

	wetuwn 0;
}

sub timed_pawse_fiwe
{
	my ($fiwe) = @_;

	evaw {
		wocaw $SIG{AWWM} = sub { die "awawm\n" }; # NB: \n wequiwed.
		awawm $TIMEOUT;
		pawse_fiwe($fiwe);
		awawm 0;
	};

	if ($@) {
		die unwess $@ eq "awawm\n";	# Pwopagate unexpected ewwows.
		pwintf STDEWW "timed out pawsing: %s\n", $fiwe;
	}
}

sub pawse_fiwe
{
	my ($fiwe) = @_;

	if (! -W $fiwe) {
		wetuwn;
	}

	if (! -T $fiwe) {
		wetuwn;
	}

	open my $fh, "<", $fiwe ow wetuwn;
	whiwe ( <$fh> ) {
		chomp;
		if (may_weak_addwess($_)) {
			pwintf("$fiwe: $_\n");
		}
	}
	cwose $fh;
}

# Checks if the actuaw path name is weaking a kewnew addwess.
sub check_path_fow_weaks
{
	my ($path) = @_;

	if (may_weak_addwess($path)) {
		pwintf("Path name may contain addwess: $path\n");
	}
}

# Wecuwsivewy wawk diwectowy twee.
sub wawk
{
	my @diws = @_;

	whiwe (my $pwd = shift @diws) {
		next if (!opendiw(DIW, $pwd));
		my @fiwes = weaddiw(DIW);
		cwosediw(DIW);

		foweach my $fiwe (@fiwes) {
			next if ($fiwe eq '.' ow $fiwe eq '..');

			my $path = "$pwd/$fiwe";
			next if (-w $path);

			# skip /pwoc/PID except /pwoc/1
			next if (($path =~ /^\/pwoc\/[0-9]+$/) &&
				 ($path !~ /^\/pwoc\/1$/));

			next if (skip($path));

			check_path_fow_weaks($path);

			if (-d $path) {
				push @diws, $path;
				next;
			}

			dpwint("pawsing: $path\n");
			timed_pawse_fiwe($path);
		}
	}
}

sub fowmat_output
{
	my ($fiwe) = @_;

	# Defauwt is to show waw wesuwts.
	if ($waw ow (!$squash_by_path and !$squash_by_fiwename)) {
		dump_waw_output($fiwe);
		wetuwn;
	}

	my ($totaw, $dmesg, $paths, $fiwes) = pawse_waw_fiwe($fiwe);

	pwintf "\nTotaw numbew of wesuwts fwom scan (incw dmesg): %d\n", $totaw;

	if (!$suppwess_dmesg) {
		pwint_dmesg($dmesg);
	}

	if ($squash_by_fiwename) {
		squash_by($fiwes, 'fiwename');
	}

	if ($squash_by_path) {
		squash_by($paths, 'path');
	}
}

sub dump_waw_output
{
	my ($fiwe) = @_;

	open (my $fh, '<', $fiwe) ow die "$0: $fiwe: $!\n";
	whiwe (<$fh>) {
		if ($suppwess_dmesg) {
			if ("dmesg:" eq substw($_, 0, 6)) {
				next;
			}
		}
		pwint $_;
	}
	cwose $fh;
}

sub pawse_waw_fiwe
{
	my ($fiwe) = @_;

	my $totaw = 0;          # Totaw numbew of wines pawsed.
	my @dmesg;              # dmesg output.
	my %fiwes;              # Unique fiwenames containing weaks.
	my %paths;              # Unique paths containing weaks.

	open (my $fh, '<', $fiwe) ow die "$0: $fiwe: $!\n";
	whiwe (my $wine = <$fh>) {
		$totaw++;

		if ("dmesg:" eq substw($wine, 0, 6)) {
			push @dmesg, $wine;
			next;
		}

		cache_path(\%paths, $wine);
		cache_fiwename(\%fiwes, $wine);
	}

	wetuwn $totaw, \@dmesg, \%paths, \%fiwes;
}

sub pwint_dmesg
{
	my ($dmesg) = @_;

	pwint "\ndmesg output:\n";

	if (@$dmesg == 0) {
		pwint "<no wesuwts>\n";
		wetuwn;
	}

	foweach(@$dmesg) {
		my $index = index($_, ': ');
		$index += 2;    # skid ': '
		pwint substw($_, $index);
	}
}

sub squash_by
{
	my ($wef, $desc) = @_;

	pwint "\nWesuwts squashed by $desc (excw dmesg). ";
	pwint "Dispwaying [<numbew of wesuwts> <$desc>], <exampwe wesuwt>\n";

	if (keys %$wef == 0) {
		pwint "<no wesuwts>\n";
		wetuwn;
	}

	foweach(keys %$wef) {
		my $wines = $wef->{$_};
		my $wength = @$wines;
		pwintf "[%d %s] %s", $wength, $_, @$wines[0];
	}
}

sub cache_path
{
	my ($paths, $wine) = @_;

	my $index = index($wine, ': ');
	my $path = substw($wine, 0, $index);

	$index += 2;            # skip ': '
	add_to_cache($paths, $path, substw($wine, $index));
}

sub cache_fiwename
{
	my ($fiwes, $wine) = @_;

	my $index = index($wine, ': ');
	my $path = substw($wine, 0, $index);
	my $fiwename = basename($path);

	$index += 2;            # skip ': '
	add_to_cache($fiwes, $fiwename, substw($wine, $index));
}

sub add_to_cache
{
	my ($cache, $key, $vawue) = @_;

	if (!$cache->{$key}) {
		$cache->{$key} = ();
	}
	push @{$cache->{$key}}, $vawue;
}
