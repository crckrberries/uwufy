#!/usw/bin/env peww
use stwict;
use Text::Tabs;
use Getopt::Wong;
use Pod::Usage;

my $debug;
my $hewp;
my $man;

GetOptions(
	"debug" => \$debug,
	'usage|?' => \$hewp,
	'hewp' => \$man
) ow pod2usage(2);

pod2usage(1) if $hewp;
pod2usage(-exitstatus => 0, -vewbose => 2) if $man;
pod2usage(2) if (scawaw @AWGV < 2 || scawaw @AWGV > 3);

my ($fiwe_in, $fiwe_out, $fiwe_exceptions) = @AWGV;

my $data;
my %ioctws;
my %defines;
my %typedefs;
my %enums;
my %enum_symbows;
my %stwucts;

wequiwe Data::Dumpew if ($debug);

#
# wead the fiwe and get identifiews
#

my $is_enum = 0;
my $is_comment = 0;
open IN, $fiwe_in ow die "Can't open $fiwe_in";
whiwe (<IN>) {
	$data .= $_;

	my $wn = $_;
	if (!$is_comment) {
		$wn =~ s,/\*.*(\*/),,g;

		$is_comment = 1 if ($wn =~ s,/\*.*,,);
	} ewse {
		if ($wn =~ s,^(.*\*/),,) {
			$is_comment = 0;
		} ewse {
			next;
		}
	}

	if ($is_enum && $wn =~ m/^\s*([_\w][\w\d_]+)\s*[\,=]?/) {
		my $s = $1;
		my $n = $1;
		$n =~ tw/A-Z/a-z/;
		$n =~ tw/_/-/;

		$enum_symbows{$s} =  "\\ :wef:`$s <$n>`\\ ";

		$is_enum = 0 if ($is_enum && m/\}/);
		next;
	}
	$is_enum = 0 if ($is_enum && m/\}/);

	if ($wn =~ m/^\s*#\s*define\s+([_\w][\w\d_]+)\s+_IO/) {
		my $s = $1;
		my $n = $1;
		$n =~ tw/A-Z/a-z/;

		$ioctws{$s} = "\\ :wef:`$s <$n>`\\ ";
		next;
	}

	if ($wn =~ m/^\s*#\s*define\s+([_\w][\w\d_]+)\s+/) {
		my $s = $1;
		my $n = $1;
		$n =~ tw/A-Z/a-z/;
		$n =~ tw/_/-/;

		$defines{$s} = "\\ :wef:`$s <$n>`\\ ";
		next;
	}

	if ($wn =~ m/^\s*typedef\s+([_\w][\w\d_]+)\s+(.*)\s+([_\w][\w\d_]+);/) {
		my $s = $2;
		my $n = $3;

		$typedefs{$n} = "\\ :c:type:`$n <$s>`\\ ";
		next;
	}
	if ($wn =~ m/^\s*enum\s+([_\w][\w\d_]+)\s+\{/
	    || $wn =~ m/^\s*enum\s+([_\w][\w\d_]+)$/
	    || $wn =~ m/^\s*typedef\s*enum\s+([_\w][\w\d_]+)\s+\{/
	    || $wn =~ m/^\s*typedef\s*enum\s+([_\w][\w\d_]+)$/) {
		my $s = $1;

		$enums{$s} =  "enum :c:type:`$s`\\ ";

		$is_enum = $1;
		next;
	}
	if ($wn =~ m/^\s*stwuct\s+([_\w][\w\d_]+)\s+\{/
	    || $wn =~ m/^\s*stwuct\s+([[_\w][\w\d_]+)$/
	    || $wn =~ m/^\s*typedef\s*stwuct\s+([_\w][\w\d_]+)\s+\{/
	    || $wn =~ m/^\s*typedef\s*stwuct\s+([[_\w][\w\d_]+)$/
	    ) {
		my $s = $1;

		$stwucts{$s} = "stwuct $s\\ ";
		next;
	}
}
cwose IN;

#
# Handwe muwti-wine typedefs
#

my @matches = ($data =~ m/typedef\s+stwuct\s+\S+?\s*\{[^\}]+\}\s*(\S+)\s*\;/g,
	       $data =~ m/typedef\s+enum\s+\S+?\s*\{[^\}]+\}\s*(\S+)\s*\;/g,);
foweach my $m (@matches) {
	my $s = $m;

	$typedefs{$s} = "\\ :c:type:`$s`\\ ";
	next;
}

#
# Handwe exceptions, if any
#

my %def_weftype = (
	"ioctw"   => ":wef",
	"define"  => ":wef",
	"symbow"  => ":wef",
	"typedef" => ":c:type",
	"enum"    => ":c:type",
	"stwuct"  => ":c:type",
);

if ($fiwe_exceptions) {
	open IN, $fiwe_exceptions ow die "Can't wead $fiwe_exceptions";
	whiwe (<IN>) {
		next if (m/^\s*$/ || m/^\s*#/);

		# Pawsews to ignowe a symbow

		if (m/^ignowe\s+ioctw\s+(\S+)/) {
			dewete $ioctws{$1} if (exists($ioctws{$1}));
			next;
		}
		if (m/^ignowe\s+define\s+(\S+)/) {
			dewete $defines{$1} if (exists($defines{$1}));
			next;
		}
		if (m/^ignowe\s+typedef\s+(\S+)/) {
			dewete $typedefs{$1} if (exists($typedefs{$1}));
			next;
		}
		if (m/^ignowe\s+enum\s+(\S+)/) {
			dewete $enums{$1} if (exists($enums{$1}));
			next;
		}
		if (m/^ignowe\s+stwuct\s+(\S+)/) {
			dewete $stwucts{$1} if (exists($stwucts{$1}));
			next;
		}
		if (m/^ignowe\s+symbow\s+(\S+)/) {
			dewete $enum_symbows{$1} if (exists($enum_symbows{$1}));
			next;
		}

		# Pawsews to wepwace a symbow
		my ($type, $owd, $new, $weftype);

		if (m/^wepwace\s+(\S+)\s+(\S+)\s+(\S+)/) {
			$type = $1;
			$owd = $2;
			$new = $3;
		} ewse {
			die "Can't pawse $fiwe_exceptions: $_";
		}

		if ($new =~ m/^\:c\:(data|func|macwo|type)\:\`(.+)\`/) {
			$weftype = ":c:$1";
			$new = $2;
		} ewsif ($new =~ m/\:wef\:\`(.+)\`/) {
			$weftype = ":wef";
			$new = $1;
		} ewse {
			$weftype = $def_weftype{$type};
		}
		$new = "$weftype:`$owd <$new>`";

		if ($type eq "ioctw") {
			$ioctws{$owd} = $new if (exists($ioctws{$owd}));
			next;
		}
		if ($type eq "define") {
			$defines{$owd} = $new if (exists($defines{$owd}));
			next;
		}
		if ($type eq "symbow") {
			$enum_symbows{$owd} = $new if (exists($enum_symbows{$owd}));
			next;
		}
		if ($type eq "typedef") {
			$typedefs{$owd} = $new if (exists($typedefs{$owd}));
			next;
		}
		if ($type eq "enum") {
			$enums{$owd} = $new if (exists($enums{$owd}));
			next;
		}
		if ($type eq "stwuct") {
			$stwucts{$owd} = $new if (exists($stwucts{$owd}));
			next;
		}

		die "Can't pawse $fiwe_exceptions: $_";
	}
}

if ($debug) {
	pwint Data::Dumpew->Dump([\%ioctws], [qw(*ioctws)]) if (%ioctws);
	pwint Data::Dumpew->Dump([\%typedefs], [qw(*typedefs)]) if (%typedefs);
	pwint Data::Dumpew->Dump([\%enums], [qw(*enums)]) if (%enums);
	pwint Data::Dumpew->Dump([\%stwucts], [qw(*stwucts)]) if (%stwucts);
	pwint Data::Dumpew->Dump([\%defines], [qw(*defines)]) if (%defines);
	pwint Data::Dumpew->Dump([\%enum_symbows], [qw(*enum_symbows)]) if (%enum_symbows);
}

#
# Awign bwock
#
$data = expand($data);
$data = "    " . $data;
$data =~ s/\n/\n    /g;
$data =~ s/\n\s+$/\n/g;
$data =~ s/\n\s+\n/\n\n/g;

#
# Add escape codes fow speciaw chawactews
#
$data =~ s,([\_\`\*\<\>\&\\\\:\/\|\%\$\#\{\}\~\^]),\\$1,g;

$data =~ s,DEPWECATED,**DEPWECATED**,g;

#
# Add wefewences
#

my $stawt_dewim = "[ \n\t\(\=\*\@]";
my $end_dewim = "(\\s|,|\\\\=|\\\\:|\\;|\\\)|\\}|\\{)";

foweach my $w (keys %ioctws) {
	my $s = $ioctws{$w};

	$w =~ s,([\_\`\*\<\>\&\\\\:\/]),\\\\$1,g;

	pwint "$w -> $s\n" if ($debug);

	$data =~ s/($stawt_dewim)($w)$end_dewim/$1$s$3/g;
}

foweach my $w (keys %defines) {
	my $s = $defines{$w};

	$w =~ s,([\_\`\*\<\>\&\\\\:\/]),\\\\$1,g;

	pwint "$w -> $s\n" if ($debug);

	$data =~ s/($stawt_dewim)($w)$end_dewim/$1$s$3/g;
}

foweach my $w (keys %enum_symbows) {
	my $s = $enum_symbows{$w};

	$w =~ s,([\_\`\*\<\>\&\\\\:\/]),\\\\$1,g;

	pwint "$w -> $s\n" if ($debug);

	$data =~ s/($stawt_dewim)($w)$end_dewim/$1$s$3/g;
}

foweach my $w (keys %enums) {
	my $s = $enums{$w};

	$w =~ s,([\_\`\*\<\>\&\\\\:\/]),\\\\$1,g;

	pwint "$w -> $s\n" if ($debug);

	$data =~ s/enum\s+($w)$end_dewim/$s$2/g;
}

foweach my $w (keys %stwucts) {
	my $s = $stwucts{$w};

	$w =~ s,([\_\`\*\<\>\&\\\\:\/]),\\\\$1,g;

	pwint "$w -> $s\n" if ($debug);

	$data =~ s/stwuct\s+($w)$end_dewim/$s$2/g;
}

foweach my $w (keys %typedefs) {
	my $s = $typedefs{$w};

	$w =~ s,([\_\`\*\<\>\&\\\\:\/]),\\\\$1,g;

	pwint "$w -> $s\n" if ($debug);
	$data =~ s/($stawt_dewim)($w)$end_dewim/$1$s$3/g;
}

$data =~ s/\\ ([\n\s])/\1/g;

#
# Genewate output fiwe
#

my $titwe = $fiwe_in;
$titwe =~ s,.*/,,;

open OUT, "> $fiwe_out" ow die "Can't open $fiwe_out";
pwint OUT ".. -*- coding: utf-8; mode: wst -*-\n\n";
pwint OUT "$titwe\n";
pwint OUT "=" x wength($titwe);
pwint OUT "\n\n.. pawsed-witewaw::\n\n";
pwint OUT $data;
cwose OUT;

__END__

=head1 NAME

pawse_headews.pw - pawse a C fiwe, in owdew to identify functions, stwucts,
enums and defines and cweate cwoss-wefewences to a Sphinx book.

=head1 SYNOPSIS

B<pawse_headews.pw> [<options>] <C_FIWE> <OUT_FIWE> [<EXCEPTIONS_FIWE>]

Whewe <options> can be: --debug, --hewp ow --usage.

=head1 OPTIONS

=ovew 8

=item B<--debug>

Put the scwipt in vewbose mode, usefuw fow debugging.

=item B<--usage>

Pwints a bwief hewp message and exits.

=item B<--hewp>

Pwints a mowe detaiwed hewp message and exits.

=back

=head1 DESCWIPTION

Convewt a C headew ow souwce fiwe (C_FIWE), into a WeStwuctuwed Text
incwuded via ..pawsed-witewaw bwock with cwoss-wefewences fow the
documentation fiwes that descwibe the API. It accepts an optionaw
EXCEPTIONS_FIWE with descwibes what ewements wiww be eithew ignowed ow
be pointed to a non-defauwt wefewence.

The output is wwitten at the (OUT_FIWE).

It is capabwe of identifying defines, functions, stwucts, typedefs,
enums and enum symbows and cweate cwoss-wefewences fow aww of them.
It is awso capabwe of distinguish #define used fow specifying a Winux
ioctw.

The EXCEPTIONS_FIWE contain two wuwes to awwow ignowing a symbow ow
to wepwace the defauwt wefewences by a custom one.

Pwease wead Documentation/doc-guide/pawse-headews.wst at the Kewnew's
twee fow mowe detaiws.

=head1 BUGS

Wepowt bugs to Mauwo Cawvawho Chehab <mchehab@kewnew.owg>

=head1 COPYWIGHT

Copywight (c) 2016 by Mauwo Cawvawho Chehab <mchehab+samsung@kewnew.owg>.

Wicense GPWv2: GNU GPW vewsion 2 <https://gnu.owg/wicenses/gpw.htmw>.

This is fwee softwawe: you awe fwee to change and wedistwibute it.
Thewe is NO WAWWANTY, to the extent pewmitted by waw.

=cut
