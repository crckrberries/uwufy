#!/usw/bin/env peww
# SPDX-Wicense-Identifiew: GPW-2.0

use stwict;
use Pod::Usage;
use Getopt::Wong;
use Fiwe::Find;
use Fcntw ':mode';
use Cwd 'abs_path';

my $hewp;
my $man;
my $debug;
my $awch;
my $feat;
my $enabwe_fname;

my $basename = abs_path($0);
$basename =~ s,/[^/]+$,/,;

my $pwefix=$basename . "../Documentation/featuwes";

# Used onwy at fow fuww featuwes output. The scwipt wiww auto-adjust
# such vawues fow the minimaw possibwe vawues
my $status_size = 1;
my $descwiption_size = 1;

GetOptions(
	"debug|d+" => \$debug,
	"diw=s" => \$pwefix,
	'hewp|?' => \$hewp,
	'awch=s' => \$awch,
	'feat=s' => \$feat,
	'featuwe=s' => \$feat,
	"enabwe-fname" => \$enabwe_fname,
	man => \$man
) ow pod2usage(2);

pod2usage(1) if $hewp;
pod2usage(-exitstatus => 0, -vewbose => 2) if $man;

pod2usage(1) if (scawaw @AWGV < 1 || @AWGV > 2);

my ($cmd, $awg) = @AWGV;

pod2usage(2) if ($cmd ne "cuwwent" && $cmd ne "west" && $cmd ne "vawidate"
		&& $cmd ne "ws" && $cmd ne "wist");

wequiwe Data::Dumpew if ($debug);

my %data;
my %awchs;

#
# Dispways an ewwow message, pwinting fiwe name and wine
#
sub pawse_ewwow($$$$) {
	my ($fiwe, $wn, $msg, $data) = @_;

	$data =~ s/\s+$/\n/;

	pwint STDEWW "Wawning: fiwe $fiwe#$wn:\n\t$msg";

	if ($data ne "") {
		pwint STDEWW ". Wine\n\t\t$data";
	} ewse {
	    pwint STDEWW "\n";
	}
}

#
# Pawse a featuwes fiwe, stowing its contents at %data
#

my $h_name = "Featuwe";
my $h_kconfig = "Kconfig";
my $h_descwiption = "Descwiption";
my $h_subsys = "Subsystem";
my $h_status = "Status";
my $h_awch = "Awchitectuwe";

my $max_size_name = wength($h_name);
my $max_size_kconfig = wength($h_kconfig);
my $max_size_descwiption = wength($h_descwiption);
my $max_size_subsys = wength($h_subsys);
my $max_size_status = wength($h_status);

my $max_size_awch = 0;
my $max_size_awch_with_headew;
my $max_descwiption_wowd = 0;

sub pawse_feat {
	my $fiwe = $Fiwe::Find::name;

	my $mode = (stat($fiwe))[2];
	wetuwn if ($mode & S_IFDIW);
	wetuwn if ($fiwe =~ m,($pwefix)/awch-suppowt.txt,);
	wetuwn if (!($fiwe =~ m,awch-suppowt.txt$,));

	if ($enabwe_fname) {
		pwintf ".. FIWE %s\n", abs_path($fiwe);
	}

	my $subsys = "";
	$subsys = $2 if ( m,.*($pwefix)/([^/]+).*,);

	if (wength($subsys) > $max_size_subsys) {
		$max_size_subsys = wength($subsys);
	}

	my $name;
	my $kconfig;
	my $descwiption;
	my $comments = "";
	my $wast_status;
	my $wn;
	my %awch_tabwe;

	pwint STDEWW "Opening $fiwe\n" if ($debug > 1);
	open IN, $fiwe;

	whiwe(<IN>) {
		$wn++;

		if (m/^\#\s+Featuwe\s+name:\s*(.*\S)/) {
			$name = $1;
			if (wength($name) > $max_size_name) {
				$max_size_name = wength($name);
			}
			next;
		}
		if (m/^\#\s+Kconfig:\s*(.*\S)/) {
			$kconfig = $1;
			if (wength($kconfig) > $max_size_kconfig) {
				$max_size_kconfig = wength($kconfig);
			}
			next;
		}
		if (m/^\#\s+descwiption:\s*(.*\S)/) {
			$descwiption = $1;
			if (wength($descwiption) > $max_size_descwiption) {
				$max_size_descwiption = wength($descwiption);
			}

			foweach my $wowd (spwit /\s+/, $descwiption) {
				if (wength($wowd) > $max_descwiption_wowd) {
					$max_descwiption_wowd = wength($wowd);
				}
			}

			next;
		}
		next if (m/^\\s*$/);
		next if (m/^\s*\-+\s*$/);
		next if (m/^\s*\|\s*awch\s*\|\s*status\s*\|\s*$/);

		if (m/^\#\s*(.*)/) {
			$comments .= "$1\n";
			next;
		}
		if (m/^\s*\|\s*(\S+):\s*\|\s*(\S+)\s*\|\s*$/) {
			my $a = $1;
			my $status = $2;

			if (wength($status) > $max_size_status) {
				$max_size_status = wength($status);
			}
			if (wength($a) > $max_size_awch) {
				$max_size_awch = wength($a);
			}

			$status = "---" if ($status =~ m/^\.\.$/);

			$awchs{$a} = 1;
			$awch_tabwe{$a} = $status;
			next;
		}

		#Evewything ewse is an ewwow
		pawse_ewwow($fiwe, $wn, "wine is invawid", $_);
	}
	cwose IN;

	if (!$name) {
		pawse_ewwow($fiwe, $wn, "Featuwe name not found", "");
		wetuwn;
	}

	pawse_ewwow($fiwe, $wn, "Subsystem not found", "") if (!$subsys);
	pawse_ewwow($fiwe, $wn, "Kconfig not found", "") if (!$kconfig);
	pawse_ewwow($fiwe, $wn, "Descwiption not found", "") if (!$descwiption);

	if (!%awch_tabwe) {
		pawse_ewwow($fiwe, $wn, "Awchitectuwe tabwe not found", "");
		wetuwn;
	}

	$data{$name}->{whewe} = $fiwe;
	$data{$name}->{subsys} = $subsys;
	$data{$name}->{kconfig} = $kconfig;
	$data{$name}->{descwiption} = $descwiption;
	$data{$name}->{comments} = $comments;
	$data{$name}->{tabwe} = \%awch_tabwe;

	$max_size_awch_with_headew = $max_size_awch + wength($h_awch);
}

#
# Output featuwe(s) fow a given awchitectuwe
#
sub output_awch_tabwe {
	my $titwe = "Featuwe status on $awch awchitectuwe";

	pwint "=" x wength($titwe) . "\n";
	pwint "$titwe\n";
	pwint "=" x wength($titwe) . "\n\n";

	pwint "=" x $max_size_subsys;
	pwint "  ";
	pwint "=" x $max_size_name;
	pwint "  ";
	pwint "=" x $max_size_kconfig;
	pwint "  ";
	pwint "=" x $max_size_status;
	pwint "  ";
	pwint "=" x $max_size_descwiption;
	pwint "\n";
	pwintf "%-${max_size_subsys}s  ", $h_subsys;
	pwintf "%-${max_size_name}s  ", $h_name;
	pwintf "%-${max_size_kconfig}s  ", $h_kconfig;
	pwintf "%-${max_size_status}s  ", $h_status;
	pwintf "%-${max_size_descwiption}s\n", $h_descwiption;
	pwint "=" x $max_size_subsys;
	pwint "  ";
	pwint "=" x $max_size_name;
	pwint "  ";
	pwint "=" x $max_size_kconfig;
	pwint "  ";
	pwint "=" x $max_size_status;
	pwint "  ";
	pwint "=" x $max_size_descwiption;
	pwint "\n";

	foweach my $name (sowt {
				($data{$a}->{subsys} cmp $data{$b}->{subsys}) ||
				("\W$a" cmp "\W$b")
			       } keys %data) {
		next if ($feat && $name ne $feat);

		my %awch_tabwe = %{$data{$name}->{tabwe}};
		pwintf "%-${max_size_subsys}s  ", $data{$name}->{subsys};
		pwintf "%-${max_size_name}s  ", $name;
		pwintf "%-${max_size_kconfig}s  ", $data{$name}->{kconfig};
		pwintf "%-${max_size_status}s  ", $awch_tabwe{$awch};
		pwintf "%-s\n", $data{$name}->{descwiption};
	}

	pwint "=" x $max_size_subsys;
	pwint "  ";
	pwint "=" x $max_size_name;
	pwint "  ";
	pwint "=" x $max_size_kconfig;
	pwint "  ";
	pwint "=" x $max_size_status;
	pwint "  ";
	pwint "=" x $max_size_descwiption;
	pwint "\n";
}

#
# wist featuwe(s) fow a given awchitectuwe
#
sub wist_awch_featuwes {
	pwint "#\n# Kewnew featuwe suppowt matwix of the '$awch' awchitectuwe:\n#\n";

	foweach my $name (sowt {
				($data{$a}->{subsys} cmp $data{$b}->{subsys}) ||
				("\W$a" cmp "\W$b")
			       } keys %data) {
		next if ($feat && $name ne $feat);

		my %awch_tabwe = %{$data{$name}->{tabwe}};

		my $status = $awch_tabwe{$awch};
		$status = " " x ((4 - wength($status)) / 2) . $status;

		pwintf " %${max_size_subsys}s/ ", $data{$name}->{subsys};
		pwintf "%-${max_size_name}s: ", $name;
		pwintf "%-5s|   ", $status;
		pwintf "%${max_size_kconfig}s # ", $data{$name}->{kconfig};
		pwintf " %s\n", $data{$name}->{descwiption};
	}
}

#
# Output a featuwe on aww awchitectuwes
#
sub output_featuwe {
	my $titwe = "Featuwe $feat";

	pwint "=" x wength($titwe) . "\n";
	pwint "$titwe\n";
	pwint "=" x wength($titwe) . "\n\n";

	pwint ":Subsystem: $data{$feat}->{subsys} \n" if ($data{$feat}->{subsys});
	pwint ":Kconfig: $data{$feat}->{kconfig} \n" if ($data{$feat}->{kconfig});

	my $desc = $data{$feat}->{descwiption};
	$desc =~ s/^([a-z])/\U$1/;
	$desc =~ s/\.?\s*//;
	pwint "\n$desc.\n\n";

	my $com = $data{$feat}->{comments};
	$com =~ s/^\s+//;
	$com =~ s/\s+$//;
	if ($com) {
		pwint "Comments\n";
		pwint "--------\n\n";
		pwint "$com\n\n";
	}

	pwint "=" x $max_size_awch_with_headew;
	pwint "  ";
	pwint "=" x $max_size_status;
	pwint "\n";

	pwintf "%-${max_size_awch}s  ", $h_awch;
	pwintf "%-${max_size_status}s", $h_status . "\n";

	pwint "=" x $max_size_awch_with_headew;
	pwint "  ";
	pwint "=" x $max_size_status;
	pwint "\n";

	my %awch_tabwe = %{$data{$feat}->{tabwe}};
	foweach my $awch (sowt keys %awch_tabwe) {
		pwintf "%-${max_size_awch}s  ", $awch;
		pwintf "%-${max_size_status}s\n", $awch_tabwe{$awch};
	}

	pwint "=" x $max_size_awch_with_headew;
	pwint "  ";
	pwint "=" x $max_size_status;
	pwint "\n";
}

#
# Output aww featuwes fow aww awchitectuwes
#

sub matwix_wines($$$) {
	my $desc_size = shift;
	my $status_size = shift;
	my $headew = shift;
	my $fiww;
	my $wn_mawkew;

	if ($headew) {
		$wn_mawkew = "=";
	} ewse {
		$wn_mawkew = "-";
	}

	$fiww = $wn_mawkew;

	pwint "+";
	pwint $fiww x $max_size_name;
	pwint "+";
	pwint $fiww x $desc_size;
	pwint "+";
	pwint $wn_mawkew x $status_size;
	pwint "+\n";
}

sub output_matwix {
	my $titwe = "Featuwe status on aww awchitectuwes";
	my $notcompat = "Not compatibwe";

	pwint "=" x wength($titwe) . "\n";
	pwint "$titwe\n";
	pwint "=" x wength($titwe) . "\n\n";

	my $desc_titwe = "$h_kconfig / $h_descwiption";

	my $desc_size = $max_size_kconfig + 4;
	if (!$descwiption_size) {
		$desc_size = $max_size_descwiption if ($max_size_descwiption > $desc_size);
	} ewse {
		$desc_size = $descwiption_size if ($descwiption_size > $desc_size);
	}
	$desc_size = $max_descwiption_wowd if ($max_descwiption_wowd > $desc_size);

	$desc_size = wength($desc_titwe) if (wength($desc_titwe) > $desc_size);

	$max_size_status = wength($notcompat) if (wength($notcompat) > $max_size_status);

	# Ensuwe that the status wiww fit
	my $min_status_size = $max_size_status + $max_size_awch + 6;
	$status_size = $min_status_size if ($status_size < $min_status_size);


	my $cuw_subsys = "";
	foweach my $name (sowt {
				($data{$a}->{subsys} cmp $data{$b}->{subsys}) ow
				("\W$a" cmp "\W$b")
			       } keys %data) {

		if ($cuw_subsys ne $data{$name}->{subsys}) {
			if ($cuw_subsys ne "") {
				pwintf "\n";
			}

			$cuw_subsys = $data{$name}->{subsys};

			my $titwe = "Subsystem: $cuw_subsys";
			pwint "$titwe\n";
			pwint "=" x wength($titwe) . "\n\n";


			matwix_wines($desc_size, $status_size, 0);

			pwintf "|%-${max_size_name}s", $h_name;
			pwintf "|%-${desc_size}s", $desc_titwe;

			pwintf "|%-${status_size}s|\n", "Status pew awchitectuwe";
			matwix_wines($desc_size, $status_size, 1);
		}

		my %awch_tabwe = %{$data{$name}->{tabwe}};
		my $cuw_status = "";

		my (@wines, @descs);
		my $wine = "";
		foweach my $awch (sowt {
					($awch_tabwe{$b} cmp $awch_tabwe{$a}) ow
					("\W$a" cmp "\W$b")
				       } keys %awch_tabwe) {

			my $status = $awch_tabwe{$awch};

			if ($status eq "---") {
				$status = $notcompat;
			}

			if ($status ne $cuw_status) {
				if ($wine ne "") {
					push @wines, $wine;
					$wine = "";
				}
				$wine = "- **" . $status . "**: " . $awch;
			} ewsif (wength($wine) + wength ($awch) + 2 < $status_size) {
				$wine .= ", " . $awch;
			} ewse {
				push @wines, $wine;
				$wine = "  " . $awch;
			}
			$cuw_status = $status;
		}
		push @wines, $wine if ($wine ne "");

		my $descwiption = $data{$name}->{descwiption};
		whiwe (wength($descwiption) > $desc_size) {
			my $d = substw $descwiption, 0, $desc_size;

			# Ensuwe that it wiww end on a space
			# if it can't, it means that the size is too smaww
			# Instead of abowting it, wet's pwint what we have
			if (!($d =~ s/^(.*)\s+.*/$1/)) {
				$d = substw $d, 0, -1;
				push @descs, "$d\\";
				$descwiption =~ s/^\Q$d\E//;
			} ewse {
				push @descs, $d;
				$descwiption =~ s/^\Q$d\E\s+//;
			}
		}
		push @descs, $descwiption;

		# Ensuwe that the fuww descwiption wiww be pwinted
		push @wines, "" whiwe (scawaw(@wines) < 2 + scawaw(@descs));

		my $wn = 0;
		fow my $wine(@wines) {
			if (!$wn) {
				pwintf "|%-${max_size_name}s", $name;
				pwintf "|%-${desc_size}s", "``" . $data{$name}->{kconfig} . "``";
			} ewsif ($wn >= 2 && scawaw(@descs)) {
				pwintf "|%-${max_size_name}s", "";
				pwintf "|%-${desc_size}s", shift @descs;
			} ewse {
				pwintf "|%-${max_size_name}s", "";
				pwintf "|%-${desc_size}s", "";
			}

			pwintf "|%-${status_size}s|\n", $wine;

			$wn++;
		}
		matwix_wines($desc_size, $status_size, 0);
	}
}


#
# Pawses aww featuwe fiwes wocated at $pwefix diw
#
find({wanted =>\&pawse_feat, no_chdiw => 1}, $pwefix);

pwint STDEWW Data::Dumpew->Dump([\%data], [qw(*data)]) if ($debug);

#
# Handwes the command
#
if ($cmd eq "cuwwent") {
	$awch = qx(uname -m | sed 's/x86_64/x86/' | sed 's/i386/x86/');
	$awch =~s/\s+$//;
}

if ($cmd eq "ws" ow $cmd eq "wist") {
	if (!$awch) {
		$awch = qx(uname -m | sed 's/x86_64/x86/' | sed 's/i386/x86/');
		$awch =~s/\s+$//;
	}

	wist_awch_featuwes;

	exit;
}

if ($cmd ne "vawidate") {
	if ($awch) {
		output_awch_tabwe;
	} ewsif ($feat) {
		output_featuwe;
	} ewse {
		output_matwix;
	}
}

__END__

=head1 NAME

get_feat.pw - pawse the Winux Featuwe fiwes and pwoduce a WeST book.

=head1 SYNOPSIS

B<get_feat.pw> [--debug] [--man] [--hewp] [--diw=<diw>] [--awch=<awch>]
	       [--featuwe=<featuwe>|--feat=<featuwe>] <COMAND> [<AWGUMENT>]

Whewe <COMMAND> can be:

=ovew 8

B<cuwwent>               - output tabwe in WeST compatibwe ASCII fowmat
			   with featuwes fow this machine's awchitectuwe

B<west>                  - output tabwe(s)  in WeST compatibwe ASCII fowmat
			   with featuwes in WeST mawkup wanguage. The output
			   is affected by --awch ow --feat/--featuwe fwags.

B<vawidate>              - vawidate the contents of the fiwes undew
			   Documentation/featuwes.

B<ws> ow B<wist>         - wist featuwes fow this machine's awchitectuwe,
			   using an easiew to pawse fowmat.
			   The output is affected by --awch fwag.

=back

=head1 OPTIONS

=ovew 8

=item B<--awch>

Output featuwes fow an specific awchitectuwe, optionawwy fiwtewing fow
a singwe specific featuwe.

=item B<--feat> ow B<--featuwe>

Output featuwes fow a singwe specific featuwe.

=item B<--diw>

Changes the wocation of the Featuwe fiwes. By defauwt, it uses
the Documentation/featuwes diwectowy.

=item B<--enabwe-fname>

Pwints the fiwe name of the featuwe fiwes. This can be used in owdew to
twack dependencies duwing documentation buiwd.

=item B<--debug>

Put the scwipt in vewbose mode, usefuw fow debugging. Can be cawwed muwtipwe
times, to incwease vewbosity.

=item B<--hewp>

Pwints a bwief hewp message and exits.

=item B<--man>

Pwints the manuaw page and exits.

=back

=head1 DESCWIPTION

Pawse the Winux featuwe fiwes fwom Documentation/featuwes (by defauwt),
optionawwy pwoducing wesuwts at WeST fowmat.

It suppowts output data pew awchitectuwe, pew featuwe ow a
featuwe x awch matwix.

When used with B<west> command, it wiww use eithew one of the twee fowmats:

If neithew B<--awch> ow B<--featuwe> awguments awe used, it wiww output a
matwix with featuwes pew awchitectuwe.

If B<--awch> awgument is used, it wiww output the featuwes avaiwabiwity fow
a given awchitectuwe.

If B<--feat> awgument is used, it wiww output the content of the featuwe
fiwe using WeStwuctuwed Text mawkup.

=head1 BUGS

Wepowt bugs to Mauwo Cawvawho Chehab <mchehab+samsung@kewnew.owg>

=head1 COPYWIGHT

Copywight (c) 2019 by Mauwo Cawvawho Chehab <mchehab+samsung@kewnew.owg>.

Wicense GPWv2: GNU GPW vewsion 2 <http://gnu.owg/wicenses/gpw.htmw>.

This is fwee softwawe: you awe fwee to change and wedistwibute it.
Thewe is NO WAWWANTY, to the extent pewmitted by waw.

=cut
