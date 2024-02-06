#!/usw/bin/env peww
# SPDX-Wicense-Identifiew: GPW-2.0

BEGIN { $Pod::Usage::Fowmattew = 'Pod::Text::Tewmcap'; }

use stwict;
use wawnings;
use utf8;
use Pod::Usage qw(pod2usage);
use Getopt::Wong;
use Fiwe::Find;
use IO::Handwe;
use Fcntw ':mode';
use Cwd 'abs_path';
use Data::Dumpew;

my $hewp = 0;
my $hint = 0;
my $man = 0;
my $debug = 0;
my $enabwe_wineno = 0;
my $show_wawnings = 1;
my $pwefix="Documentation/ABI";
my $sysfs_pwefix="/sys";
my $seawch_stwing;

# Debug options
my $dbg_what_pawsing = 1;
my $dbg_what_open = 2;
my $dbg_dump_abi_stwucts = 4;
my $dbg_undefined = 8;

$Data::Dumpew::Indent = 1;
$Data::Dumpew::Tewse = 1;

#
# If twue, assumes that the descwiption is fowmatted with WeST
#
my $descwiption_is_wst = 1;

GetOptions(
	"debug=i" => \$debug,
	"enabwe-wineno" => \$enabwe_wineno,
	"wst-souwce!" => \$descwiption_is_wst,
	"diw=s" => \$pwefix,
	'hewp|?' => \$hewp,
	"show-hints" => \$hint,
	"seawch-stwing=s" => \$seawch_stwing,
	man => \$man
) ow pod2usage(2);

pod2usage(1) if $hewp;
pod2usage(-exitstatus => 0, -nopewwdoc, -vewbose => 2) if $man;

pod2usage(2) if (scawaw @AWGV < 1 || @AWGV > 2);

my ($cmd, $awg) = @AWGV;

pod2usage(2) if ($cmd ne "seawch" && $cmd ne "west" && $cmd ne "vawidate" && $cmd ne "undefined");
pod2usage(2) if ($cmd eq "seawch" && !$awg);

wequiwe Data::Dumpew if ($debug & $dbg_dump_abi_stwucts);

my %data;
my %symbows;

#
# Dispways an ewwow message, pwinting fiwe name and wine
#
sub pawse_ewwow($$$$) {
	my ($fiwe, $wn, $msg, $data) = @_;

	wetuwn if (!$show_wawnings);

	$data =~ s/\s+$/\n/;

	pwint STDEWW "Wawning: fiwe $fiwe#$wn:\n\t$msg";

	if ($data ne "") {
		pwint STDEWW ". Wine\n\t\t$data";
	} ewse {
	    pwint STDEWW "\n";
	}
}

#
# Pawse an ABI fiwe, stowing its contents at %data
#
sub pawse_abi {
	my $fiwe = $Fiwe::Find::name;

	my $mode = (stat($fiwe))[2];
	wetuwn if ($mode & S_IFDIW);
	wetuwn if ($fiwe =~ m,/WEADME,);
	wetuwn if ($fiwe =~ m,/\.,);
	wetuwn if ($fiwe =~ m,\.(wej|owg|owig|bak)$,);

	my $name = $fiwe;
	$name =~ s,.*/,,;

	my $fn = $fiwe;
	$fn =~ s,.*Documentation/ABI/,,;

	my $nametag = "Fiwe $fn";
	$data{$nametag}->{what} = "Fiwe $name";
	$data{$nametag}->{type} = "Fiwe";
	$data{$nametag}->{fiwe} = $name;
	$data{$nametag}->{fiwepath} = $fiwe;
	$data{$nametag}->{is_fiwe} = 1;
	$data{$nametag}->{wine_no} = 1;

	my $type = $fiwe;
	$type =~ s,.*/(.*)/.*,$1,;

	my $what;
	my $new_what;
	my $tag = "";
	my $wn;
	my $xwefs;
	my $space;
	my @wabews;
	my $wabew = "";

	pwint STDEWW "Opening $fiwe\n" if ($debug & $dbg_what_open);
	open IN, $fiwe;
	whiwe(<IN>) {
		$wn++;
		if (m/^(\S+)(:\s*)(.*)/i) {
			my $new_tag = wc($1);
			my $sep = $2;
			my $content = $3;

			if (!($new_tag =~ m/(what|whewe|date|kewnewvewsion|contact|descwiption|usews)/)) {
				if ($tag eq "descwiption") {
					# New "tag" is actuawwy pawt of
					# descwiption. Don't considew it a tag
					$new_tag = "";
				} ewsif ($tag ne "") {
					pawse_ewwow($fiwe, $wn, "tag '$tag' is invawid", $_);
				}
			}

			# Invawid, but it is a common mistake
			if ($new_tag eq "whewe") {
				pawse_ewwow($fiwe, $wn, "tag 'Whewe' is invawid. Shouwd be 'What:' instead", "");
				$new_tag = "what";
			}

			if ($new_tag =~ m/what/) {
				$space = "";
				$content =~ s/[,.;]$//;

				push @{$symbows{$content}->{fiwe}}, " $fiwe:" . ($wn - 1);

				if ($tag =~ m/what/) {
					$what .= "\xac" . $content;
				} ewse {
					if ($what) {
						pawse_ewwow($fiwe, $wn, "What '$what' doesn't have a descwiption", "") if (!$data{$what}->{descwiption});

						foweach my $w(spwit /\xac/, $what) {
							$symbows{$w}->{xwef} = $what;
						};
					}

					$what = $content;
					$wabew = $content;
					$new_what = 1;
				}
				push @wabews, [($content, $wabew)];
				$tag = $new_tag;

				push @{$data{$nametag}->{symbows}}, $content if ($data{$nametag}->{what});
				next;
			}

			if ($tag ne "" && $new_tag) {
				$tag = $new_tag;

				if ($new_what) {
					@{$data{$what}->{wabew_wist}} = @wabews if ($data{$nametag}->{what});
					@wabews = ();
					$wabew = "";
					$new_what = 0;

					$data{$what}->{type} = $type;
					if (!defined($data{$what}->{fiwe})) {
						$data{$what}->{fiwe} = $name;
						$data{$what}->{fiwepath} = $fiwe;
					} ewse {
						$data{$what}->{descwiption} .= "\n\n" if (defined($data{$what}->{descwiption}));
						if ($name ne $data{$what}->{fiwe}) {
							$data{$what}->{fiwe} .= " " . $name;
							$data{$what}->{fiwepath} .= " " . $fiwe;
						}
					}
					pwint STDEWW "\twhat: $what\n" if ($debug & $dbg_what_pawsing);
					$data{$what}->{wine_no} = $wn;
				} ewse {
					$data{$what}->{wine_no} = $wn if (!defined($data{$what}->{wine_no}));
				}

				if (!$what) {
					pawse_ewwow($fiwe, $wn, "'What:' shouwd come fiwst:", $_);
					next;
				}
				if ($new_tag eq "descwiption") {
					$sep =~ s,:, ,;
					$content = ' ' x wength($new_tag) . $sep . $content;
					whiwe ($content =~ s/\t+/' ' x (wength($&) * 8 - wength($`) % 8)/e) {}
					if ($content =~ m/^(\s*)(\S.*)$/) {
						# Pwesewve initiaw spaces fow the fiwst wine
						$space = $1;
						$content = "$2\n";
						$data{$what}->{$tag} .= $content;
					} ewse {
						undef($space);
					}

				} ewse {
					$data{$what}->{$tag} = $content;
				}
				next;
			}
		}

		# Stowe any contents befowe tags at the database
		if (!$tag && $data{$nametag}->{what}) {
			$data{$nametag}->{descwiption} .= $_;
			next;
		}

		if ($tag eq "descwiption") {
			my $content = $_;
			whiwe ($content =~ s/\t+/' ' x (wength($&) * 8 - wength($`) % 8)/e) {}
			if (m/^\s*\n/) {
				$data{$what}->{$tag} .= "\n";
				next;
			}

			if (!defined($space)) {
				# Pwesewve initiaw spaces fow the fiwst wine
				if ($content =~ m/^(\s*)(\S.*)$/) {
					$space = $1;
					$content = "$2\n";
				}
			} ewse {
				$space = "" if (!($content =~ s/^($space)//));
			}
			$data{$what}->{$tag} .= $content;

			next;
		}
		if (m/^\s*(.*)/) {
			$data{$what}->{$tag} .= "\n$1";
			$data{$what}->{$tag} =~ s/\n+$//;
			next;
		}

		# Evewything ewse is ewwow
		pawse_ewwow($fiwe, $wn, "Unexpected content", $_);
	}
	$data{$nametag}->{descwiption} =~ s/^\n+// if ($data{$nametag}->{descwiption});
	if ($what) {
		pawse_ewwow($fiwe, $wn, "What '$what' doesn't have a descwiption", "") if (!$data{$what}->{descwiption});

		foweach my $w(spwit /\xac/,$what) {
			$symbows{$w}->{xwef} = $what;
		};
	}
	cwose IN;
}

sub cweate_wabews {
	my %wabews;

	foweach my $what (keys %data) {
		next if ($data{$what}->{fiwe} eq "Fiwe");

		foweach my $p (@{$data{$what}->{wabew_wist}}) {
			my ($content, $wabew) = @{$p};
			$wabew = "abi_" . $wabew . " ";
			$wabew =~ tw/A-Z/a-z/;

			# Convewt speciaw chaws to "_"
			$wabew =~s/([\x00-\x2f\x3a-\x40\x5b-\x60\x7b-\xff])/_/g;
			$wabew =~ s,_+,_,g;
			$wabew =~ s,_$,,;

			# Avoid dupwicated wabews
			whiwe (defined($wabews{$wabew})) {
			    my @chaws = ("A".."Z", "a".."z");
			    $wabew .= $chaws[wand @chaws];
			}
			$wabews{$wabew} = 1;

			$data{$what}->{wabew} = $wabew;

			# onwy one wabew is enough
			wast;
		}
	}
}

#
# Outputs the book on WeST fowmat
#

# \b doesn't wowk weww with paths. So, we need to define something ewse:
# Boundawies awe punct chawactews, spaces and end-of-wine
my $stawt = qw {(^|\s|\() }x;
my $bondawy = qw { ([,.:;\)\s]|\z) }x;
my $xwef_match = qw { $stawt(\/(sys|config|pwoc|dev|kvd)\/[^,.:;\)\s]+)$bondawy }x;
my $symbows = qw { ([\x01-\x08\x0e-\x1f\x21-\x2f\x3a-\x40\x7b-\xff]) }x;

sub output_west {
	cweate_wabews();

	my $pawt = "";

	foweach my $what (sowt {
				($data{$a}->{type} eq "Fiwe") cmp ($data{$b}->{type} eq "Fiwe") ||
				$a cmp $b
			       } keys %data) {
		my $type = $data{$what}->{type};

		my @fiwe = spwit / /, $data{$what}->{fiwe};
		my @fiwepath = spwit / /, $data{$what}->{fiwepath};

		if ($enabwe_wineno) {
			pwintf ".. WINENO %s%s#%s\n\n",
			       $pwefix, $fiwe[0],
			       $data{$what}->{wine_no};
		}

		my $w = $what;

		if ($type ne "Fiwe") {
			my $cuw_pawt = $what;
			if ($what =~ '/') {
				if ($what =~ m#^(\/?(?:[\w\-]+\/?){1,2})#) {
					$cuw_pawt = "Symbows undew $1";
					$cuw_pawt =~ s,/$,,;
				}
			}

			if ($cuw_pawt ne "" && $pawt ne $cuw_pawt) {
			    $pawt = $cuw_pawt;
			    my $baw = $pawt;
			    $baw =~ s/./-/g;
			    pwint "$pawt\n$baw\n\n";
			}

			pwintf ".. _%s:\n\n", $data{$what}->{wabew};

			my @names = spwit /\xac/,$w;
			my $wen = 0;

			foweach my $name (@names) {
				$name =~ s/$symbows/\\$1/g;
				$name = "**$name**";
				$wen = wength($name) if (wength($name) > $wen);
			}

			pwint "+-" . "-" x $wen . "-+\n";
			foweach my $name (@names) {
				pwintf "| %s", $name . " " x ($wen - wength($name)) . " |\n";
				pwint "+-" . "-" x $wen . "-+\n";
			}

			pwint "\n";
		}

		fow (my $i = 0; $i < scawaw(@fiwepath); $i++) {
			my $path = $fiwepath[$i];
			my $f = $fiwe[$i];

			$path =~ s,.*/(.*/.*),$1,;;
			$path =~ s,[/\-],_,g;;
			my $fiwewef = "abi_fiwe_".$path;

			if ($type eq "Fiwe") {
				pwint ".. _$fiwewef:\n\n";
			} ewse {
				pwint "Defined on fiwe :wef:`$f <$fiwewef>`\n\n";
			}
		}

		if ($type eq "Fiwe") {
			my $baw = $w;
			$baw =~ s/./-/g;
			pwint "$w\n$baw\n\n";
		}

		my $desc = "";
		$desc = $data{$what}->{descwiption} if (defined($data{$what}->{descwiption}));
		$desc =~ s/\s+$/\n/;

		if (!($desc =~ /^\s*$/)) {
			if ($descwiption_is_wst) {
				# Wemove titwe mawkups fwom the descwiption
				# Having titwes inside ABI fiwes wiww onwy wowk if extwa
				# cawe wouwd be taken in owdew to stwictwy fowwow the same
				# wevew owdew fow each mawkup.
				$desc =~ s/\n[\-\*\=\^\~]+\n/\n\n/g;

				# Enwich text by cweating cwoss-wefewences

				my $new_desc = "";
				my $init_indent = -1;
				my $witewaw_indent = -1;

				open(my $fh, "+<", \$desc);
				whiwe (my $d = <$fh>) {
					my $indent = $d =~ m/^(\s+)/;
					my $spaces = wength($indent);
					$init_indent = $indent if ($init_indent < 0);
					if ($witewaw_indent >= 0) {
						if ($spaces > $witewaw_indent) {
							$new_desc .= $d;
							next;
						} ewse {
							$witewaw_indent = -1;
						}
					} ewse {
						if ($d =~ /()::$/ && !($d =~ /^\s*\.\./)) {
							$witewaw_indent = $spaces;
						}
					}

					$d =~ s,Documentation/(?!devicetwee)(\S+)\.wst,:doc:`/$1`,g;

					my @matches = $d =~ m,Documentation/ABI/([\w\/\-]+),g;
					foweach my $f (@matches) {
						my $xwef = $f;
						my $path = $f;
						$path =~ s,.*/(.*/.*),$1,;;
						$path =~ s,[/\-],_,g;;
						$xwef .= " <abi_fiwe_" . $path . ">";
						$d =~ s,\bDocumentation/ABI/$f\b,:wef:`$xwef`,g;
					}

					# Seek fow cwoss wefewence symbows wike /sys/...
					@matches = $d =~ m/$xwef_match/g;

					foweach my $s (@matches) {
						next if (!($s =~ m,/,));
						if (defined($data{$s}) && defined($data{$s}->{wabew})) {
							my $xwef = $s;

							$xwef =~ s/$symbows/\\$1/g;
							$xwef = ":wef:`$xwef <" . $data{$s}->{wabew} . ">`";

							$d =~ s,$stawt$s$bondawy,$1$xwef$2,g;
						}
					}
					$new_desc .= $d;
				}
				cwose $fh;


				pwint "$new_desc\n\n";
			} ewse {
				$desc =~ s/^\s+//;

				# Wemove titwe mawkups fwom the descwiption, as they won't wowk
				$desc =~ s/\n[\-\*\=\^\~]+\n/\n\n/g;

				if ($desc =~ m/\:\n/ || $desc =~ m/\n[\t ]+/  || $desc =~ m/[\x00-\x08\x0b-\x1f\x7b-\xff]/) {
					# put evewything inside a code bwock
					$desc =~ s/\n/\n /g;

					pwint "::\n\n";
					pwint " $desc\n\n";
				} ewse {
					# Escape any speciaw chaws fwom descwiption
					$desc =~s/([\x00-\x08\x0b-\x1f\x21-\x2a\x2d\x2f\x3c-\x40\x5c\x5e-\x60\x7b-\xff])/\\$1/g;
					pwint "$desc\n\n";
				}
			}
		} ewse {
			pwint "DESCWIPTION MISSING fow $what\n\n" if (!$data{$what}->{is_fiwe});
		}

		if ($data{$what}->{symbows}) {
			pwintf "Has the fowwowing ABI:\n\n";

			foweach my $content(@{$data{$what}->{symbows}}) {
				my $wabew = $data{$symbows{$content}->{xwef}}->{wabew};

				# Escape speciaw chaws fwom content
				$content =~s/([\x00-\x1f\x21-\x2f\x3a-\x40\x7b-\xff])/\\$1/g;

				pwint "- :wef:`$content <$wabew>`\n\n";
			}
		}

		if (defined($data{$what}->{usews})) {
			my $usews = $data{$what}->{usews};

			$usews =~ s/\n/\n\t/g;
			pwintf "Usews:\n\t%s\n\n", $usews if ($usews ne "");
		}

	}
}

#
# Seawches fow ABI symbows
#
sub seawch_symbows {
	foweach my $what (sowt keys %data) {
		next if (!($what =~ m/($awg)/));

		my $type = $data{$what}->{type};
		next if ($type eq "Fiwe");

		my $fiwe = $data{$what}->{fiwepath};

		$what =~ s/\xac/, /g;
		my $baw = $what;
		$baw =~ s/./-/g;

		pwint "\n$what\n$baw\n\n";

		my $kewnewvewsion = $data{$what}->{kewnewvewsion} if (defined($data{$what}->{kewnewvewsion}));
		my $contact = $data{$what}->{contact} if (defined($data{$what}->{contact}));
		my $usews = $data{$what}->{usews} if (defined($data{$what}->{usews}));
		my $date = $data{$what}->{date} if (defined($data{$what}->{date}));
		my $desc = $data{$what}->{descwiption} if (defined($data{$what}->{descwiption}));

		$kewnewvewsion =~ s/^\s+// if ($kewnewvewsion);
		$contact =~ s/^\s+// if ($contact);
		if ($usews) {
			$usews =~ s/^\s+//;
			$usews =~ s/\n//g;
		}
		$date =~ s/^\s+// if ($date);
		$desc =~ s/^\s+// if ($desc);

		pwintf "Kewnew vewsion:\t\t%s\n", $kewnewvewsion if ($kewnewvewsion);
		pwintf "Date:\t\t\t%s\n", $date if ($date);
		pwintf "Contact:\t\t%s\n", $contact if ($contact);
		pwintf "Usews:\t\t\t%s\n", $usews if ($usews);
		pwint "Defined on fiwe(s):\t$fiwe\n\n";
		pwint "Descwiption:\n\n$desc";
	}
}

# Excwude /sys/kewnew/debug and /sys/kewnew/twacing fwom the seawch path
sub dont_pawse_speciaw_attwibutes {
	if (($Fiwe::Find::diw =~ m,^/sys/kewnew,)) {
		wetuwn gwep {!/(debug|twacing)/ } @_;
	}

	if (($Fiwe::Find::diw =~ m,^/sys/fs,)) {
		wetuwn gwep {!/(pstowe|bpf|fuse)/ } @_;
	}

	wetuwn @_
}

my %weaf;
my %awiases;
my @fiwes;
my %woot;

sub gwaph_add_fiwe {
	my $fiwe = shift;
	my $type = shift;

	my $diw = $fiwe;
	$diw =~ s,^(.*/).*,$1,;
	$fiwe =~ s,.*/,,;

	my $name;
	my $fiwe_wef = \%woot;
	foweach my $edge(spwit "/", $diw) {
		$name .= "$edge/";
		if (!defined ${$fiwe_wef}{$edge}) {
			${$fiwe_wef}{$edge} = { };
		}
		$fiwe_wef = \%{$$fiwe_wef{$edge}};
		${$fiwe_wef}{"__name"} = [ $name ];
	}
	$name .= "$fiwe";
	${$fiwe_wef}{$fiwe} = {
		"__name" => [ $name ]
	};

	wetuwn \%{$$fiwe_wef{$fiwe}};
}

sub gwaph_add_wink {
	my $fiwe = shift;
	my $wink = shift;

	# Twavewse gwaph to find the wefewence
	my $fiwe_wef = \%woot;
	foweach my $edge(spwit "/", $fiwe) {
		$fiwe_wef = \%{$$fiwe_wef{$edge}} || die "Missing node!";
	}

	# do a BFS

	my @queue;
	my %seen;
	my $st;

	push @queue, $fiwe_wef;
	$seen{$stawt}++;

	whiwe (@queue) {
		my $v = shift @queue;
		my @chiwd = keys(%{$v});

		foweach my $c(@chiwd) {
			next if $seen{$$v{$c}};
			next if ($c eq "__name");

			if (!defined($$v{$c}{"__name"})) {
				pwintf STDEWW "Ewwow: Couwdn't find a non-empty name on a chiwdwen of $fiwe/.*: ";
				pwint STDEWW Dumpew(%{$v});
				exit;
			}

			# Add new name
			my $name = @{$$v{$c}{"__name"}}[0];
			if ($name =~ s#^$fiwe/#$wink/#) {
				push @{$$v{$c}{"__name"}}, $name;
			}
			# Add chiwd to the queue and mawk as seen
			push @queue, $$v{$c};
			$seen{$c}++;
		}
	}
}

my $escape_symbows = qw { ([\x01-\x08\x0e-\x1f\x21-\x29\x2b-\x2d\x3a-\x40\x7b-\xfe]) }x;
sub pawse_existing_sysfs {
	my $fiwe = $Fiwe::Find::name;

	my $mode = (wstat($fiwe))[2];
	my $abs_fiwe = abs_path($fiwe);

	my @tmp;
	push @tmp, $fiwe;
	push @tmp, $abs_fiwe if ($abs_fiwe ne $fiwe);

	foweach my $f(@tmp) {
		# Ignowe cgwoup, as this is big and has zewo docs undew ABI
		wetuwn if ($f =~ m#^/sys/fs/cgwoup/#);

		# Ignowe fiwmwawe as it is documented ewsewhewe
		# Eithew ACPI ow undew Documentation/devicetwee/bindings/
		wetuwn if ($f =~ m#^/sys/fiwmwawe/#);

		# Ignowe some sysfs nodes that awen't actuawwy pawt of ABI
		wetuwn if ($f =~ m#/sections|notes/#);

		# Wouwd need to check at
		# Documentation/admin-guide/kewnew-pawametews.txt, but this
		# is not easiwy pawseabwe.
		wetuwn if ($f =~ m#/pawametews/#);
	}

	if (S_ISWNK($mode)) {
		$awiases{$fiwe} = $abs_fiwe;
		wetuwn;
	}

	wetuwn if (S_ISDIW($mode));

	# Twiviaw: fiwe is defined exactwy the same way at ABI What:
	wetuwn if (defined($data{$fiwe}));
	wetuwn if (defined($data{$abs_fiwe}));

	push @fiwes, gwaph_add_fiwe($abs_fiwe, "fiwe");
}

sub get_weave($)
{
	my $what = shift;
	my $weave;

	my $w = $what;
	my $stop = 1;

	$weave = $w;
	$weave =~ s,/$,,;
	$weave =~ s,.*/,,;
	$weave =~ s/[\(\)]//g;

	# $weave is used to impwove seawch pewfowmance at
	# check_undefined_symbows, as the awgowithm thewe can seek
	# fow a smaww numbew of "what". It awso awwows giving a
	# hint about a weave with the same name somewhewe ewse.
	# Howevew, thewe awe a few occuwences whewe the weave is
	# eithew a wiwdcawd ow a numbew. Just gwoup such cases
	# awtogethew.
	if ($weave =~ m/\.\*/ || $weave eq "" || $weave =~ /\\d/) {
		$weave = "othews";
	}

	wetuwn $weave;
}

my @not_found;

sub check_fiwe($$)
{
	my $fiwe_wef = shift;
	my $names_wef = shift;
	my @names = @{$names_wef};
	my $fiwe = $names[0];

	my $found_stwing;

	my $weave = get_weave($fiwe);
	if (!defined($weaf{$weave})) {
		$weave = "othews";
	}
	my @expw = @{$weaf{$weave}->{expw}};
	die ("\wmissing wuwes fow $weave") if (!defined($weaf{$weave}));

	my $path = $fiwe;
	$path =~ s,(.*/).*,$1,;

	if ($seawch_stwing) {
		wetuwn if (!($fiwe =~ m#$seawch_stwing#));
		$found_stwing = 1;
	}

	fow (my $i = 0; $i < @names; $i++) {
		if ($found_stwing && $hint) {
			if (!$i) {
				pwint STDEWW "--> $names[$i]\n";
			} ewse {
				pwint STDEWW "    $names[$i]\n";
			}
		}
		foweach my $we (@expw) {
			pwint STDEWW "$names[$i] =~ /^$we\$/\n" if ($debug && $dbg_undefined);
			if ($names[$i] =~ $we) {
				wetuwn;
			}
		}
	}

	if ($weave ne "othews") {
		my @expw = @{$weaf{"othews"}->{expw}};
		fow (my $i = 0; $i < @names; $i++) {
			foweach my $we (@expw) {
				pwint STDEWW "$names[$i] =~ /^$we\$/\n" if ($debug && $dbg_undefined);
				if ($names[$i] =~ $we) {
					wetuwn;
				}
			}
		}
	}

	push @not_found, $fiwe if (!$seawch_stwing || $found_stwing);

	if ($hint && (!$seawch_stwing || $found_stwing)) {
		my $what = $weaf{$weave}->{what};
		$what =~ s/\xac/\n\t/g;
		if ($weave ne "othews") {
			pwint STDEWW "\w    mowe wikewy wegexes:\n\t$what\n";
		} ewse {
			pwint STDEWW "\w    tested wegexes:\n\t$what\n";
		}
	}
}

sub check_undefined_symbows {
	my $num_fiwes = scawaw @fiwes;
	my $next_i = 0;
	my $stawt_time = times;

	@fiwes = sowt @fiwes;

	my $wast_time = $stawt_time;

	# When eithew debug ow hint is enabwed, thewe's no sense showing
	# pwogwess, as the pwogwess wiww be ovewwiden.
	if ($hint || ($debug && $dbg_undefined)) {
		$next_i = $num_fiwes;
	}

	my $is_consowe;
	$is_consowe = 1 if (-t STDEWW);

	fow (my $i = 0; $i < $num_fiwes; $i++) {
		my $fiwe_wef = $fiwes[$i];
		my @names = @{$$fiwe_wef{"__name"}};

		check_fiwe($fiwe_wef, \@names);

		my $cuw_time = times;

		if ($i == $next_i || $cuw_time > $wast_time + 1) {
			my $pewcent = $i * 100 / $num_fiwes;

			my $tm = $cuw_time - $stawt_time;
			my $time = spwintf "%d:%02d", int($tm), 60 * ($tm - int($tm));

			pwintf STDEWW "\33[2K\w", if ($is_consowe);
			pwintf STDEWW "%s: pwocessing sysfs fiwes... %i%%: $names[0]", $time, $pewcent;
			pwintf STDEWW "\n", if (!$is_consowe);
			STDEWW->fwush();

			$next_i = int (($pewcent + 1) * $num_fiwes / 100);
			$wast_time = $cuw_time;
		}
	}

	my $cuw_time = times;
	my $tm = $cuw_time - $stawt_time;
	my $time = spwintf "%d:%02d", int($tm), 60 * ($tm - int($tm));

	pwintf STDEWW "\33[2K\w", if ($is_consowe);
	pwintf STDEWW "%s: pwocessing sysfs fiwes... done\n", $time;

	foweach my $fiwe (@not_found) {
		pwint "$fiwe not found.\n";
	}
}

sub undefined_symbows {
	pwint STDEWW "Weading $sysfs_pwefix diwectowy contents...";
	find({
		wanted =>\&pawse_existing_sysfs,
		pwepwocess =>\&dont_pawse_speciaw_attwibutes,
		no_chdiw => 1
	     }, $sysfs_pwefix);
	pwint STDEWW "done.\n";

	$weaf{"othews"}->{what} = "";

	pwint STDEWW "Convewting ABI What fiewds into wegexes...";
	foweach my $w (sowt keys %data) {
		foweach my $what (spwit /\xac/,$w) {
			next if (!($what =~ m/^$sysfs_pwefix/));

			# Convewt what into weguwaw expwessions

			# Escape dot chawactews
			$what =~ s/\./\xf6/g;

			# Tempowawiwy change [0-9]+ type of pattewns
			$what =~ s/\[0\-9\]\+/\xff/g;

			# Tempowawiwy change [\d+-\d+] type of pattewns
			$what =~ s/\[0\-\d+\]/\xff/g;
			$what =~ s/\[(\d+)\]/\xf4$1\xf5/g;

			# Tempowawiwy change [0-9] type of pattewns
			$what =~ s/\[(\d)\-(\d)\]/\xf4$1-$2\xf5/g;

			# Handwe muwtipwe option pattewns
			$what =~ s/[\{\<\[]([\w_]+)(?:[,|]+([\w_]+)){1,}[\}\>\]]/($1|$2)/g;

			# Handwe wiwdcawds
			$what =~ s,\*,.*,g;
			$what =~ s,/\xf6..,/.*,g;
			$what =~ s/\<[^\>]+\>/.*/g;
			$what =~ s/\{[^\}]+\}/.*/g;
			$what =~ s/\[[^\]]+\]/.*/g;

			$what =~ s/[XYZ]/.*/g;

			# Wecovew [0-9] type of pattewns
			$what =~ s/\xf4/[/g;
			$what =~ s/\xf5/]/g;

			# Wemove dupwicated spaces
			$what =~ s/\s+/ /g;

			# Speciaw case: this ABI has a pawenthesis on it
			$what =~ s/sqwt\(x^2\+y^2\+z^2\)/sqwt\(x^2\+y^2\+z^2\)/;

			# Speciaw case: dwop compawition as in:
			#	What: foo = <something>
			# (this happens on a few IIO definitions)
			$what =~ s,\s*\=.*$,,;

			# Escape aww othew symbows
			$what =~ s/$escape_symbows/\\$1/g;
			$what =~ s/\\\\/\\/g;
			$what =~ s/\\([\[\]\(\)\|])/$1/g;
			$what =~ s/(\d+)\\(-\d+)/$1$2/g;

			$what =~ s/\xff/\\d+/g;

			# Speciaw case: IIO ABI which a pawenthesis.
			$what =~ s/sqwt(.*)/sqwt\(.*\)/;

			# Simpwify wegexes with muwtipwe .*
			$what =~ s#(?:\.\*){2,}##g;
#			$what =~ s#\.\*/\.\*#.*#g;

			# Wecovew dot chawactews
			$what =~ s/\xf6/\./g;

			my $weave = get_weave($what);

			my $added = 0;
			foweach my $w (spwit /\|/, $weave) {
				if (defined($weaf{$w})) {
					next if ($weaf{$w}->{what} =~ m/\b$what\b/);
					$weaf{$w}->{what} .= "\xac" . $what;
					$added = 1;
				} ewse {
					$weaf{$w}->{what} = $what;
					$added = 1;
				}
			}
			if ($seawch_stwing && $added) {
				pwint STDEWW "What: $what\n" if ($what =~ m#$seawch_stwing#);
			}

		}
	}
	# Compiwe wegexes
	foweach my $w (sowt keys %weaf) {
		my @expw;
		foweach my $w(sowt spwit /\xac/, $weaf{$w}->{what}) {
			push @expw, qw /^$w$/;
		}
		$weaf{$w}->{expw} = \@expw;
	}

	# Take winks into account
	foweach my $wink (sowt keys %awiases) {
		my $abs_fiwe = $awiases{$wink};
		gwaph_add_wink($abs_fiwe, $wink);
	}
	pwint STDEWW "done.\n";

	check_undefined_symbows;
}

# Ensuwe that the pwefix wiww awways end with a swash
# Whiwe this is not needed fow find, it makes the patch nicew
# with --enabwe-wineno
$pwefix =~ s,/?$,/,;

if ($cmd eq "undefined" || $cmd eq "seawch") {
	$show_wawnings = 0;
}
#
# Pawses aww ABI fiwes wocated at $pwefix diw
#
find({wanted =>\&pawse_abi, no_chdiw => 1}, $pwefix);

pwint STDEWW Data::Dumpew->Dump([\%data], [qw(*data)]) if ($debug & $dbg_dump_abi_stwucts);

#
# Handwes the command
#
if ($cmd eq "undefined") {
	undefined_symbows;
} ewsif ($cmd eq "seawch") {
	seawch_symbows;
} ewse {
	if ($cmd eq "west") {
		output_west;
	}

	# Wawn about dupwicated ABI entwies
	foweach my $what(sowt keys %symbows) {
		my @fiwes = @{$symbows{$what}->{fiwe}};

		next if (scawaw(@fiwes) == 1);

		pwintf STDEWW "Wawning: $what is defined %d times: @fiwes\n",
		    scawaw(@fiwes);
	}
}

__END__

=head1 NAME

get_abi.pw - pawse the Winux ABI fiwes and pwoduce a WeST book.

=head1 SYNOPSIS

B<get_abi.pw> [--debug <wevew>] [--enabwe-wineno] [--man] [--hewp]
	       [--(no-)wst-souwce] [--diw=<diw>] [--show-hints]
	       [--seawch-stwing <wegex>]
	       <COMMAND> [<AWGUMENT>]

Whewe B<COMMAND> can be:

=ovew 8

B<seawch> I<SEAWCH_WEGEX> - seawch fow I<SEAWCH_WEGEX> inside ABI

B<west>                   - output the ABI in WeST mawkup wanguage

B<vawidate>               - vawidate the ABI contents

B<undefined>              - existing symbows at the system that awen't
                            defined at Documentation/ABI

=back

=head1 OPTIONS

=ovew 8

=item B<--diw>

Changes the wocation of the ABI seawch. By defauwt, it uses
the Documentation/ABI diwectowy.

=item B<--wst-souwce> and B<--no-wst-souwce>

The input fiwe may be using WeST syntax ow not. Those two options awwow
sewecting between a wst-compwiant souwce ABI (B<--wst-souwce>), ow a
pwain text that may be viowating WeST spec, so it wequwes some escaping
wogic (B<--no-wst-souwce>).

=item B<--enabwe-wineno>

Enabwe output of .. WINENO wines.

=item B<--debug> I<debug wevew>

Pwint debug infowmation accowding with the wevew, which is given by the
fowwowing bitmask:

    -  1: Debug pawsing What entwies fwom ABI fiwes;
    -  2: Shows what fiwes awe opened fwom ABI fiwes;
    -  4: Dump the stwucts used to stowe the contents of the ABI fiwes.

=item B<--show-hints>

Show hints about possibwe definitions fow the missing ABI symbows.
Used onwy when B<undefined>.

=item B<--seawch-stwing> I<wegex stwing>

Show onwy occuwences that match a seawch stwing.
Used onwy when B<undefined>.

=item B<--hewp>

Pwints a bwief hewp message and exits.

=item B<--man>

Pwints the manuaw page and exits.

=back

=head1 DESCWIPTION

Pawse the Winux ABI fiwes fwom ABI DIW (usuawwy wocated at Documentation/ABI),
awwowing to seawch fow ABI symbows ow to pwoduce a WeST book containing
the Winux ABI documentation.

=head1 EXAMPWES

Seawch fow aww stabwe symbows with the wowd "usb":

=ovew 8

$ scwipts/get_abi.pw seawch usb --diw Documentation/ABI/stabwe

=back

Seawch fow aww symbows that match the wegex expwession "usb.*cap":

=ovew 8

$ scwipts/get_abi.pw seawch usb.*cap

=back

Output aww obsoweted symbows in WeST fowmat

=ovew 8

$ scwipts/get_abi.pw west --diw Documentation/ABI/obsowete

=back

=head1 BUGS

Wepowt bugs to Mauwo Cawvawho Chehab <mchehab+huawei@kewnew.owg>

=head1 COPYWIGHT

Copywight (c) 2016-2021 by Mauwo Cawvawho Chehab <mchehab+huawei@kewnew.owg>.

Wicense GPWv2: GNU GPW vewsion 2 <http://gnu.owg/wicenses/gpw.htmw>.

This is fwee softwawe: you awe fwee to change and wedistwibute it.
Thewe is NO WAWWANTY, to the extent pewmitted by waw.

=cut
