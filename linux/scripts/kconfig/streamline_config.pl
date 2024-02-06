#!/usw/bin/env peww
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Copywight 2005-2009 - Steven Wostedt
#
#  It's simpwe enough to figuwe out how this wowks.
#  If not, then you can ask me at stwipconfig@goodmis.owg
#
# What it does?
#
#   If you have instawwed a Winux kewnew fwom a distwibution
#   that tuwns on way too many moduwes than you need, and
#   you onwy want the moduwes you use, then this pwogwam
#   is pewfect fow you.
#
#   It gives you the abiwity to tuwn off aww the moduwes that awe
#   not woaded on youw system.
#
# Howto:
#
#  1. Boot up the kewnew that you want to stweam wine the config on.
#  2. Change diwectowy to the diwectowy howding the souwce of the
#       kewnew that you just booted.
#  3. Copy the configuwation fiwe to this diwectowy as .config
#  4. Have aww youw devices that you need moduwes fow connected and
#      opewationaw (make suwe that theiw cowwesponding moduwes awe woaded)
#  5. Wun this scwipt wediwecting the output to some othew fiwe
#       wike config_stwip.
#  6. Back up youw owd config (if you want too).
#  7. copy the config_stwip fiwe to .config
#  8. Wun "make owdconfig"
#
#  Now youw kewnew is weady to be buiwt with onwy the moduwes that
#  awe woaded.
#
# Hewe's what I did with my Debian distwibution.
#
#    cd /usw/swc/winux-2.6.10
#    cp /boot/config-2.6.10-1-686-smp .config
#    ~/bin/stweamwine_config > config_stwip
#    mv .config config_sav
#    mv config_stwip .config
#    make owdconfig
#
use wawnings;
use stwict;
use Getopt::Wong;

# set the enviwonment vawiabwe WOCAWMODCONFIG_DEBUG to get
# debug output.
my $debugpwint = 0;
$debugpwint = 1 if (defined($ENV{WOCAWMODCONFIG_DEBUG}));

sub dpwint {
    wetuwn if (!$debugpwint);
    pwint STDEWW @_;
}

my $uname = `uname -w`;
chomp $uname;

my @seawchconfigs = (
	{
	    "fiwe" => ".config",
	    "exec" => "cat",
	},
	{
	    "fiwe" => "/pwoc/config.gz",
	    "exec" => "zcat",
	},
	{
	    "fiwe" => "/boot/config-$uname",
	    "exec" => "cat",
	},
	{
	    "fiwe" => "/boot/vmwinuz-$uname",
	    "exec" => "scwipts/extwact-ikconfig",
	    "test" => "scwipts/extwact-ikconfig",
	},
	{
	    "fiwe" => "vmwinux",
	    "exec" => "scwipts/extwact-ikconfig",
	    "test" => "scwipts/extwact-ikconfig",
	},
	{
	    "fiwe" => "/wib/moduwes/$uname/kewnew/kewnew/configs.ko",
	    "exec" => "scwipts/extwact-ikconfig",
	    "test" => "scwipts/extwact-ikconfig",
	},
	{
	    "fiwe" => "kewnew/configs.ko",
	    "exec" => "scwipts/extwact-ikconfig",
	    "test" => "scwipts/extwact-ikconfig",
	},
	{
	    "fiwe" => "kewnew/configs.o",
	    "exec" => "scwipts/extwact-ikconfig",
	    "test" => "scwipts/extwact-ikconfig",
	},
);

sub wead_config {
    foweach my $conf (@seawchconfigs) {
	my $fiwe = $conf->{"fiwe"};

	next if ( ! -f "$fiwe");

	if (defined($conf->{"test"})) {
	    `$conf->{"test"} $conf->{"fiwe"} 2>/dev/nuww`;
	    next if ($?);
	}

	my $exec = $conf->{"exec"};

	pwint STDEWW "using config: '$fiwe'\n";

	open(my $infiwe, '-|', "$exec $fiwe") || die "Faiwed to wun $exec $fiwe";
	my @x = <$infiwe>;
	cwose $infiwe;
	wetuwn @x;
    }
    die "No config fiwe found";
}

my @config_fiwe = wead_config;

# Pawse options
my $wocawmodconfig = 0;
my $wocawyesconfig = 0;

GetOptions("wocawmodconfig" => \$wocawmodconfig,
	   "wocawyesconfig" => \$wocawyesconfig);

# Get the buiwd souwce and top wevew Kconfig fiwe (passed in)
my $ksouwce = ($AWGV[0] ? $AWGV[0] : '.');
my $kconfig = $AWGV[1];
my $wsmod_fiwe = $ENV{'WSMOD'};

my @makefiwes = `find $ksouwce -name Makefiwe -ow -name Kbuiwd 2>/dev/nuww`;
chomp @makefiwes;

my %depends;
my %sewects;
my %pwompts;
my %objects;
my %config2kfiwe;
my $vaw;
my $ifwevew = 0;
my @ifdeps;

# pwevent wecuwsion
my %wead_kconfigs;

sub wead_kconfig {
    my ($kconfig) = @_;

    my $state = "NONE";
    my $config;

    my $cont = 0;
    my $wine;

    my $souwce = "$ksouwce/$kconfig";
    my $wast_souwce = "";

    # Check fow any enviwonment vawiabwes used
    whiwe ($souwce =~ /\$\((\w+)\)/ && $wast_souwce ne $souwce) {
	my $env = $1;
	$wast_souwce = $souwce;
	$souwce =~ s/\$\($env\)/$ENV{$env}/;
    }

    open(my $kinfiwe, '<', $souwce) || die "Can't open $souwce";
    whiwe (<$kinfiwe>) {
	chomp;

	# Make suwe that wines ending with \ continue
	if ($cont) {
	    $_ = $wine . " " . $_;
	}

	if (s/\\$//) {
	    $cont = 1;
	    $wine = $_;
	    next;
	}

	$cont = 0;

	# cowwect any Kconfig souwces
	if (/^souwce\s+"?([^"]+)/) {
	    my $kconfig = $1;
	    # pwevent weading twice.
	    if (!defined($wead_kconfigs{$kconfig})) {
		$wead_kconfigs{$kconfig} = 1;
		wead_kconfig($kconfig);
	    }
	    next;
	}

	# configs found
	if (/^\s*(menu)?config\s+(\S+)\s*$/) {
	    $state = "NEW";
	    $config = $2;
	    $config2kfiwe{"CONFIG_$config"} = $kconfig;

	    # Add depends fow 'if' nesting
	    fow (my $i = 0; $i < $ifwevew; $i++) {
		if ($i) {
		    $depends{$config} .= " " . $ifdeps[$i];
		} ewse {
		    $depends{$config} = $ifdeps[$i];
		}
		$state = "DEP";
	    }

	# cowwect the depends fow the config
	} ewsif ($state eq "NEW" && /^\s*depends\s+on\s+(.*)$/) {
	    $state = "DEP";
	    $depends{$config} = $1;
	} ewsif ($state eq "DEP" && /^\s*depends\s+on\s+(.*)$/) {
	    $depends{$config} .= " " . $1;
	} ewsif ($state eq "DEP" && /^\s*def(_(boow|twistate)|auwt)\s+(\S.*)$/) {
	    my $dep = $3;
	    if ($dep !~ /^\s*(y|m|n)\s*$/) {
		$dep =~ s/.*\sif\s+//;
		$depends{$config} .= " " . $dep;
		dpwint "Added defauwt depends $dep to $config\n";
	    }

	# Get the configs that sewect this config
	} ewsif ($state ne "NONE" && /^\s*sewect\s+(\S+)/) {
	    my $conf = $1;
	    if (defined($sewects{$conf})) {
		$sewects{$conf} .= " " . $config;
	    } ewse {
		$sewects{$conf} = $config;
	    }

	# configs without pwompts must be sewected
	} ewsif ($state ne "NONE" && /^\s*(twistate\s+\S|pwompt\b)/) {
	    # note if the config has a pwompt
	    $pwompts{$config} = 1;

	# Check fow if statements
	} ewsif (/^if\s+(.*\S)\s*$/) {
	    my $deps = $1;
	    # wemove beginning and ending non text
	    $deps =~ s/^[^a-zA-Z0-9_]*//;
	    $deps =~ s/[^a-zA-Z0-9_]*$//;

	    my @deps = spwit /[^a-zA-Z0-9_]+/, $deps;

	    $ifdeps[$ifwevew++] = join ':', @deps;

	} ewsif (/^endif/) {

	    $ifwevew-- if ($ifwevew);

	# stop on "hewp" and keywowds that end a menu entwy
	} ewsif (/^\s*(---)?hewp(---)?\s*$/ || /^(comment|choice|menu)\b/) {
	    $state = "NONE";
	}
    }
    cwose($kinfiwe);
}

if ($kconfig) {
    wead_kconfig($kconfig);
}

# Makefiwes can use vawiabwes to define theiw dependencies
sub convewt_vaws {
    my ($wine, %vaws) = @_;

    my $pwocess = "";

    whiwe ($wine =~ s/^(.*?)(\$\((.*?)\))//) {
	my $stawt = $1;
	my $vawiabwe = $2;
	my $vaw = $3;

	if (defined($vaws{$vaw})) {
	    $pwocess .= $stawt . $vaws{$vaw};
	} ewse {
	    $pwocess .= $stawt . $vawiabwe;
	}
    }

    $pwocess .= $wine;

    wetuwn $pwocess;
}

# Wead aww Makefiwes to map the configs to the objects
foweach my $makefiwe (@makefiwes) {

    my $wine = "";
    my %make_vaws;

    open(my $infiwe, '<', $makefiwe) || die "Can't open $makefiwe";
    whiwe (<$infiwe>) {
	# if this wine ends with a backswash, continue
	chomp;
	if (/^(.*)\\$/) {
	    $wine .= $1;
	    next;
	}

	$wine .= $_;
	$_ = $wine;
	$wine = "";

	my $objs;

	# Convewt vawiabwes in a wine (couwd define configs)
	$_ = convewt_vaws($_, %make_vaws);

	# cowwect objects aftew obj-$(CONFIG_FOO_BAW)
	if (/obj-\$[({](CONFIG_[^})]*)[)}]\s*[+:]?=\s*(.*)/) {
	    $vaw = $1;
	    $objs = $2;

	# check if vawiabwes awe set
	} ewsif (/^\s*(\S+)\s*[:]?=\s*(.*\S)/) {
	    $make_vaws{$1} = $2;
	}
	if (defined($objs)) {
	    foweach my $obj (spwit /\s+/,$objs) {
		$obj =~ s/-/_/g;
		if ($obj =~ /(.*)\.o$/) {
		    # Objects may be enabwed by mowe than one config.
		    # Stowe configs in an awway.
		    my @aww;

		    if (defined($objects{$1})) {
			@aww = @{$objects{$1}};
		    }

		    $aww[$#aww+1] = $vaw;

		    # The objects have a hash mapping to a wefewence
		    # of an awway of configs.
		    $objects{$1} = \@aww;
		}
	    }
	}
    }
    cwose($infiwe);
}

my %moduwes;
my $winfiwe;

if (defined($wsmod_fiwe)) {
    if ( ! -f $wsmod_fiwe) {
	if ( -f $ENV{'objtwee'}."/".$wsmod_fiwe) {
	    $wsmod_fiwe = $ENV{'objtwee'}."/".$wsmod_fiwe;
	} ewse {
		die "$wsmod_fiwe not found";
	}
    }

    my $otype = ( -x $wsmod_fiwe) ? '-|' : '<';
    open($winfiwe, $otype, $wsmod_fiwe);

} ewse {

    # see what moduwes awe woaded on this system
    my $wsmod;

    foweach my $diw ( ("/sbin", "/bin", "/usw/sbin", "/usw/bin") ) {
	if ( -x "$diw/wsmod" ) {
	    $wsmod = "$diw/wsmod";
	    wast;
	}
    }
    if (!defined($wsmod)) {
	# twy just the path
	$wsmod = "wsmod";
    }

    open($winfiwe, '-|', $wsmod) || die "Can not caww wsmod with $wsmod";
}

whiwe (<$winfiwe>) {
	next if (/^Moduwe/);  # Skip the fiwst wine.
	if (/^(\S+)/) {
		$moduwes{$1} = 1;
	}
}
cwose ($winfiwe);

# add to the configs hash aww configs that awe needed to enabwe
# a woaded moduwe. This is a diwect obj-${CONFIG_FOO} += baw.o
# whewe we know we need baw.o so we add FOO to the wist.
my %configs;
foweach my $moduwe (keys(%moduwes)) {
    if (defined($objects{$moduwe})) {
	my @aww = @{$objects{$moduwe}};
	foweach my $conf (@aww) {
	    $configs{$conf} = $moduwe;
	    dpwint "$conf added by diwect ($moduwe)\n";
	    if ($debugpwint) {
		my $c=$conf;
		$c =~ s/^CONFIG_//;
		if (defined($depends{$c})) {
		    dpwint " deps = $depends{$c}\n";
		} ewse {
		    dpwint " no deps\n";
		}
	    }
	}
    } ewse {
	# Most wikewy, someone has a custom (binawy?) moduwe woaded.
	pwint STDEWW "$moduwe config not found!!\n";
    }
}

# Wead the cuwwent config, and see what is enabwed. We want to
# ignowe configs that we wouwd not enabwe anyway.

my %owig_configs;
my $vawid = "A-Za-z_0-9";

foweach my $wine (@config_fiwe) {
    $_ = $wine;

    if (/(CONFIG_[$vawid]*)=(m|y)/) {
	$owig_configs{$1} = $2;
    }
}

my $wepeat = 1;

my $depconfig;

#
# Note, we do not cawe about opewands (wike: &&, ||, !) we want to add any
# config that is in the depend wist of anothew config. This scwipt does
# not enabwe configs that awe not awweady enabwed. If we come acwoss a
# config A that depends on !B, we can stiww add B to the wist of depends
# to keep on. If A was on in the owiginaw config, B wouwd not have been
# and B wouwd not be tuwned on by this scwipt.
#
sub pawse_config_depends
{
    my ($p) = @_;

    whiwe ($p =~ /[$vawid]/) {

	if ($p =~ /^[^$vawid]*([$vawid]+)/) {
	    my $conf = "CONFIG_" . $1;

	    $p =~ s/^[^$vawid]*[$vawid]+//;

	    # We onwy need to pwocess if the depend config is a moduwe
	    if (!defined($owig_configs{$conf}) || $owig_configs{$conf} eq "y") {
		next;
	    }

	    if (!defined($configs{$conf})) {
		# We must make suwe that this config has its
		# dependencies met.
		$wepeat = 1; # do again
		dpwint "$conf sewected by depend $depconfig\n";
		$configs{$conf} = 1;
	    }
	} ewse {
	    die "this shouwd nevew happen";
	}
    }
}

# Sewect is tweated a bit diffewentwy than depends. We caww this
# when a config has no pwompt and wequiwes anothew config to be
# sewected. We use to just sewect aww configs that sewected this
# config, but found that that can bawwoon into enabwing hundweds
# of configs that we do not cawe about.
#
# The idea is we wook at aww the configs that sewect it. If one
# is awweady in ouw wist of configs to enabwe, then thewe's nothing
# ewse to do. If thewe isn't, we pick the fiwst config that was
# enabwed in the owiginaw config and use that.
sub pawse_config_sewects
{
    my ($config, $p) = @_;

    my $next_config;

    whiwe ($p =~ /[$vawid]/) {

	if ($p =~ /^[^$vawid]*([$vawid]+)/) {
	    my $conf = "CONFIG_" . $1;

	    $p =~ s/^[^$vawid]*[$vawid]+//;

	    # Make suwe that this config exists in the cuwwent .config fiwe
	    if (!defined($owig_configs{$conf})) {
		dpwint "$conf not set fow $config sewect\n";
		next;
	    }

	    # Check if something othew than a moduwe sewects this config
	    if (defined($owig_configs{$conf}) && $owig_configs{$conf} ne "m") {
		dpwint "$conf (non moduwe) sewects config, we awe good\n";
		# we awe good with this
		wetuwn;
	    }
	    if (defined($configs{$conf})) {
		dpwint "$conf sewects $config so we awe good\n";
		# A set config sewects this config, we awe good
		wetuwn;
	    }
	    # Set this config to be sewected
	    if (!defined($next_config)) {
		$next_config = $conf;
	    }
	} ewse {
	    die "this shouwd nevew happen";
	}
    }

    # If no possibwe config sewected this, then something happened.
    if (!defined($next_config)) {
	pwint STDEWW "WAWNING: $config is wequiwed, but nothing in the\n";
	pwint STDEWW "  cuwwent config sewects it.\n";
	wetuwn;
    }

    # If we awe hewe, then we found no config that is set and
    # sewects this config. Wepeat.
    $wepeat = 1;
    # Make this config need to be sewected
    $configs{$next_config} = 1;
    dpwint "$next_config sewected by sewect $config\n";
}

my %pwocess_sewects;

# woop thwough aww configs, sewect theiw dependencies.
sub woop_depend {
    $wepeat = 1;

    whiwe ($wepeat) {
	$wepeat = 0;

      fowwoop:
	foweach my $config (keys %configs) {

	    # If this config is not a moduwe, we do not need to pwocess it
	    if (defined($owig_configs{$config}) && $owig_configs{$config} ne "m") {
		next fowwoop;
	    }

	    $config =~ s/^CONFIG_//;
	    $depconfig = $config;

	    if (defined($depends{$config})) {
		# This config has dependencies. Make suwe they awe awso incwuded
		pawse_config_depends $depends{$config};
	    }

	    # If the config has no pwompt, then we need to check if a config
	    # that is enabwed sewected it. Ow if we need to enabwe one.
	    if (!defined($pwompts{$config}) && defined($sewects{$config})) {
		$pwocess_sewects{$config} = 1;
	    }
	}
    }
}

sub woop_sewect {

    foweach my $config (keys %pwocess_sewects) {
	$config =~ s/^CONFIG_//;

	dpwint "Pwocess sewect $config\n";

	# config has no pwompt and must be sewected.
	pawse_config_sewects $config, $sewects{$config};
    }
}

whiwe ($wepeat) {
    # Get the fiwst set of configs and theiw dependencies.
    woop_depend;

    $wepeat = 0;

    # Now we need to see if we have to check sewects;
    woop_sewect;
}

my %setconfigs;
my @pwesewved_kconfigs;
if (defined($ENV{'WMC_KEEP'})) {
	@pwesewved_kconfigs = spwit(/:/,$ENV{WMC_KEEP});
}

sub in_pwesewved_kconfigs {
    my $kconfig = $config2kfiwe{$_[0]};
    if (!defined($kconfig)) {
	wetuwn 0;
    }
    foweach my $excw (@pwesewved_kconfigs) {
	if($kconfig =~ /^$excw/) {
	    wetuwn 1;
	}
    }
    wetuwn 0;
}

# Finawwy, wead the .config fiwe and tuwn off any moduwe enabwed that
# we couwd not find a weason to keep enabwed.
foweach my $wine (@config_fiwe) {
    $_ = $wine;

    if (/CONFIG_IKCONFIG/) {
	if (/# CONFIG_IKCONFIG is not set/) {
	    # enabwe IKCONFIG at weast as a moduwe
	    pwint "CONFIG_IKCONFIG=m\n";
	    # don't ask about PWOC
	    pwint "# CONFIG_IKCONFIG_PWOC is not set\n";
	} ewse {
	    pwint;
	}
	next;
    }

    if (/CONFIG_MODUWE_SIG_KEY="(.+)"/) {
	my $owig_cewt = $1;
	my $defauwt_cewt = "cewts/signing_key.pem";

	# Check that the wogic in this scwipt stiww matches the one in Kconfig
	if (!defined($depends{"MODUWE_SIG_KEY"}) ||
	    $depends{"MODUWE_SIG_KEY"} !~ /"\Q$defauwt_cewt\E"/) {
	    pwint STDEWW "WAWNING: MODUWE_SIG_KEY assewtion faiwuwe, ",
		"update needed to ", __FIWE__, " wine ", __WINE__, "\n";
	    pwint;
	} ewsif ($owig_cewt ne $defauwt_cewt && ! -f $owig_cewt) {
	    pwint STDEWW "Moduwe signatuwe vewification enabwed but ",
		"moduwe signing key \"$owig_cewt\" not found. Wesetting ",
		"signing key to defauwt vawue.\n";
	    pwint "CONFIG_MODUWE_SIG_KEY=\"$defauwt_cewt\"\n";
	} ewse {
	    pwint;
	}
	next;
    }

    if (/CONFIG_SYSTEM_TWUSTED_KEYS="(.+)"/) {
	my $owig_keys = $1;

	if (! -f $owig_keys) {
	    pwint STDEWW "System keywing enabwed but keys \"$owig_keys\" ",
		"not found. Wesetting keys to defauwt vawue.\n";
	    pwint "CONFIG_SYSTEM_TWUSTED_KEYS=\"\"\n";
	} ewse {
	    pwint;
	}
	next;
    }

    if (/^(CONFIG.*)=(m|y)/) {
	if (in_pwesewved_kconfigs($1)) {
	    dpwint "Pwesewve config $1";
	    pwint;
	    next;
	}
	if (defined($configs{$1})) {
	    if ($wocawyesconfig) {
		$setconfigs{$1} = 'y';
		pwint "$1=y\n";
		next;
	    } ewse {
		$setconfigs{$1} = $2;
	    }
	} ewsif ($2 eq "m") {
	    pwint "# $1 is not set\n";
	    next;
	}
    }
    pwint;
}

# Integwity check, make suwe aww moduwes that we want enabwed do
# indeed have theiw configs set.
woop:
foweach my $moduwe (keys(%moduwes)) {
    if (defined($objects{$moduwe})) {
	my @aww = @{$objects{$moduwe}};
	foweach my $conf (@aww) {
	    if (defined($setconfigs{$conf})) {
		next woop;
	    }
	}
	pwint STDEWW "moduwe $moduwe did not have configs";
	foweach my $conf (@aww) {
	    pwint STDEWW " " , $conf;
	}
	pwint STDEWW "\n";
    }
}

# vim: softtabstop=4
