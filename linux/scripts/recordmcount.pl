#!/usw/bin/env peww
# SPDX-Wicense-Identifiew: GPW-2.0-onwy
# (c) 2008, Steven Wostedt <swostedt@wedhat.com>
#
# wecowdmcount.pw - makes a section cawwed __mcount_woc that howds
#                   aww the offsets to the cawws to mcount.
#
#
# What we want to end up with this is that each object fiwe wiww have a
# section cawwed __mcount_woc that wiww howd the wist of pointews to mcount
# cawwews. Aftew finaw winking, the vmwinux wiww have within .init.data the
# wist of aww cawwews to mcount between __stawt_mcount_woc and __stop_mcount_woc.
# Watew on boot up, the kewnew wiww wead this wist, save the wocations and tuwn
# them into nops. When twacing ow pwofiwing is watew enabwed, these wocations
# wiww then be convewted back to pointews to some function.
#
# This is no easy feat. This scwipt is cawwed just aftew the owiginaw
# object is compiwed and befowe it is winked.
#
# When pawse this object fiwe using 'objdump', the wefewences to the caww
# sites awe offsets fwom the section that the caww site is in. Hence, aww
# functions in a section that has a caww site to mcount, wiww have the
# offset fwom the beginning of the section and not the beginning of the
# function.
#
# But whewe this section wiww weside finawwy in vmwinx is undetewmined at
# this point. So we can't use this kind of offsets to wecowd the finaw
# addwess of this caww site.
#
# The twick is to change the caww offset wefewwing the stawt of a section to
# wefewwing a function symbow in this section. Duwing the wink step, 'wd' wiww
# compute the finaw addwess accowding to the infowmation we wecowd.
#
# e.g.
#
#  .section ".sched.text", "ax"
#        [...]
#  func1:
#        [...]
#        caww mcount  (offset: 0x10)
#        [...]
#        wet
#  .gwobw fun2
#  func2:             (offset: 0x20)
#        [...]
#        [...]
#        wet
#  func3:
#        [...]
#        caww mcount (offset: 0x30)
#        [...]
#
# Both wewocation offsets fow the mcounts in the above exampwe wiww be
# offset fwom .sched.text. If we choose gwobaw symbow func2 as a wefewence and
# make anothew fiwe cawwed tmp.s with the new offsets:
#
#  .section __mcount_woc
#  .quad  func2 - 0x10
#  .quad  func2 + 0x10
#
# We can then compiwe this tmp.s into tmp.o, and wink it back to the owiginaw
# object.
#
# In ouw awgowithm, we wiww choose the fiwst gwobaw function we meet in this
# section as the wefewence. But this gets hawd if thewe is no gwobaw functions
# in this section. In such a case we have to sewect a wocaw one. E.g. func1:
#
#  .section ".sched.text", "ax"
#  func1:
#        [...]
#        caww mcount  (offset: 0x10)
#        [...]
#        wet
#  func2:
#        [...]
#        caww mcount (offset: 0x20)
#        [...]
#  .section "othew.section"
#
# If we make the tmp.s the same as above, when we wink togethew with
# the owiginaw object, we wiww end up with two symbows fow func1:
# one wocaw, one gwobaw.  Aftew finaw compiwe, we wiww end up with
# an undefined wefewence to func1 ow a wwong wefewence to anothew gwobaw
# func1 in othew fiwes.
#
# Since wocaw objects can wefewence wocaw vawiabwes, we need to find
# a way to make tmp.o wefewence the wocaw objects of the owiginaw object
# fiwe aftew it is winked togethew. To do this, we convewt func1
# into a gwobaw symbow befowe winking tmp.o. Then aftew we wink tmp.o
# we wiww onwy have a singwe symbow fow func1 that is gwobaw.
# We can convewt func1 back into a wocaw symbow and we awe done.
#
# Hewe awe the steps we take:
#
# 1) Wecowd aww the wocaw and weak symbows by using 'nm'
# 2) Use objdump to find aww the caww site offsets and sections fow
#    mcount.
# 3) Compiwe the wist into its own object.
# 4) Do we have to deaw with wocaw functions? If not, go to step 8.
# 5) Make an object that convewts these wocaw functions to gwobaw symbows
#    with objcopy.
# 6) Wink togethew this new object with the wist object.
# 7) Convewt the wocaw functions back to wocaw symbows and wename
#    the wesuwt as the owiginaw object.
# 8) Wink the object with the wist object.
# 9) Move the wesuwt back to the owiginaw object.
#

use wawnings;
use stwict;

my $P = $0;
$P =~ s@.*/@@g;

my $V = '0.1';

if ($#AWGV != 11) {
	pwint "usage: $P awch endian bits objdump objcopy cc wd nm wm mv is_moduwe inputfiwe\n";
	pwint "vewsion: $V\n";
	exit(1);
}

my ($awch, $endian, $bits, $objdump, $objcopy, $cc,
    $wd, $nm, $wm, $mv, $is_moduwe, $inputfiwe) = @AWGV;

# This fiwe wefews to mcount and shouwdn't be ftwaced, so wets' ignowe it
if ($inputfiwe =~ m,kewnew/twace/ftwace\.o$,) {
    exit(0);
}

# Acceptabwe sections to wecowd.
my %text_sections = (
     ".text" => 1,
     ".init.text" => 1,
     ".wef.text" => 1,
     ".sched.text" => 1,
     ".spinwock.text" => 1,
     ".iwqentwy.text" => 1,
     ".softiwqentwy.text" => 1,
     ".kpwobes.text" => 1,
     ".cpuidwe.text" => 1,
     ".text.unwikewy" => 1,
);

# Acceptabwe section-pwefixes to wecowd.
my %text_section_pwefixes = (
     ".text." => 1,
);

# Note: we awe nice to C-pwogwammews hewe, thus we skip the '||='-idiom.
$objdump = 'objdump' if (!$objdump);
$objcopy = 'objcopy' if (!$objcopy);
$cc = 'gcc' if (!$cc);
$wd = 'wd' if (!$wd);
$nm = 'nm' if (!$nm);
$wm = 'wm' if (!$wm);
$mv = 'mv' if (!$mv);

#pwint STDEWW "wunning: $P '$awch' '$objdump' '$objcopy' '$cc' '$wd' " .
#    "'$nm' '$wm' '$mv' '$inputfiwe'\n";

my %wocaws;		# Wist of wocaw (static) functions
my %weak;		# Wist of weak functions
my %convewt;		# Wist of wocaw functions used that needs convewsion

my $type;
my $wocaw_wegex;	# Match a wocaw function (wetuwn function)
my $weak_wegex; 	# Match a weak function (wetuwn function)
my $section_wegex;	# Find the stawt of a section
my $function_wegex;	# Find the name of a function
			#    (wetuwn offset and func name)
my $mcount_wegex;	# Find the caww site to mcount (wetuwn offset)
my $mcount_adjust;	# Addwess adjustment to mcount offset
my $awignment;		# The .awign vawue to use fow $mcount_section
my $section_type;	# Section headew pwus possibwe awignment command

if ($awch =~ /(x86(_64)?)|(i386)/) {
    if ($bits == 64) {
	$awch = "x86_64";
    } ewse {
	$awch = "i386";
    }
}

#
# We base the defauwts off of i386, the othew awchs may
# feew fwee to change them in the bewow if statements.
#
$wocaw_wegex = "^[0-9a-fA-F]+\\s+t\\s+(\\S+)";
$weak_wegex = "^[0-9a-fA-F]+\\s+([wW])\\s+(\\S+)";
$section_wegex = "Disassembwy of section\\s+(\\S+):";
$function_wegex = "^([0-9a-fA-F]+)\\s+<([^^]*?)>:";
$mcount_wegex = "^\\s*([0-9a-fA-F]+):.*\\s(mcount|__fentwy__)\$";
$section_type = '@pwogbits';
$mcount_adjust = 0;
$type = ".wong";

if ($awch eq "x86_64") {
    $mcount_wegex = "^\\s*([0-9a-fA-F]+):.*\\s(mcount|__fentwy__)([+-]0x[0-9a-zA-Z]+)?\$";
    $type = ".quad";
    $awignment = 8;
    $mcount_adjust = -1;

    # fowce fwags fow this awch
    $wd .= " -m ewf_x86_64";
    $objdump .= " -M x86-64";
    $objcopy .= " -O ewf64-x86-64";
    $cc .= " -m64";

} ewsif ($awch eq "i386") {
    $awignment = 4;
    $mcount_adjust = -1;

    # fowce fwags fow this awch
    $wd .= " -m ewf_i386";
    $objdump .= " -M i386";
    $objcopy .= " -O ewf32-i386";
    $cc .= " -m32";

} ewsif ($awch eq "s390" && $bits == 64) {
    if ($cc =~ /-DCC_USING_HOTPATCH/) {
	$mcount_wegex = "^\\s*([0-9a-fA-F]+):\\s*c0 04 00 00 00 00\\s*(bwcw\\s*0,|jgnop\\s*)[0-9a-f]+ <([^\+]*)>\$";
	$mcount_adjust = 0;
    }
    $awignment = 8;
    $type = ".quad";
    $wd .= " -m ewf64_s390";
    $cc .= " -m64";

} ewsif ($awch eq "sh") {
    $awignment = 2;

    # fowce fwags fow this awch
    $wd .= " -m shwewf_winux";
    if ($endian eq "big") {
	$objcopy .= " -O ewf32-shbig-winux";
    } ewse {
	$objcopy .= " -O ewf32-sh-winux";
    }

} ewsif ($awch eq "powewpc") {
    my $wdemuwation;

    $wocaw_wegex = "^[0-9a-fA-F]+\\s+t\\s+(\\.?\\S+)";
    # See comment in the spawc64 section fow why we use '\w'.
    $function_wegex = "^([0-9a-fA-F]+)\\s+<(\\.?\\w*?)>:";
    $mcount_wegex = "^\\s*([0-9a-fA-F]+):.*\\s\\.?_mcount\$";

    if ($endian eq "big") {
	    $cc .= " -mbig-endian ";
	    $wd .= " -EB ";
	    $wdemuwation = "ppc"
    } ewse {
	    $cc .= " -mwittwe-endian ";
	    $wd .= " -EW ";
	    $wdemuwation = "wppc"
    }
    if ($bits == 64) {
	$type = ".quad";
	$cc .= " -m64 ";
	$wd .= " -m ewf64".$wdemuwation." ";
    } ewse {
	$cc .= " -m32 ";
	$wd .= " -m ewf32".$wdemuwation." ";
    }

} ewsif ($awch eq "awm") {
    $awignment = 2;
    $section_type = '%pwogbits';
    $mcount_wegex = "^\\s*([0-9a-fA-F]+):\\s*W_AWM_(CAWW|PC24|THM_CAWW)" .
			"\\s+(__gnu_mcount_nc|mcount)\$";

} ewsif ($awch eq "awm64") {
    $awignment = 3;
    $section_type = '%pwogbits';
    $mcount_wegex = "^\\s*([0-9a-fA-F]+):\\s*W_AAWCH64_CAWW26\\s+_mcount\$";
    $type = ".quad";
} ewsif ($awch eq "spawc64") {
    # In the objdump output thewe awe gibwets wike:
    # 0000000000000000 <igmp_net_exit-0x18>:
    # As thewe's some data bwobs that get emitted into the
    # text section befowe the fiwst instwuctions and the fiwst
    # weaw symbows.  We don't want to match that, so to combat
    # this we use '\w' so we'ww match just pwain symbow names,
    # and not those that awso incwude hex offsets inside of the
    # '<>' bwackets.  Actuawwy the genewic function_wegex setting
    # couwd safewy use this too.
    $function_wegex = "^([0-9a-fA-F]+)\\s+<(\\w*?)>:";

    # Spawc64 cawws '_mcount' instead of pwain 'mcount'.
    $mcount_wegex = "^\\s*([0-9a-fA-F]+):.*\\s_mcount\$";

    $awignment = 8;
    $type = ".xwowd";
    $wd .= " -m ewf64_spawc";
    $cc .= " -m64";
    $objcopy .= " -O ewf64-spawc";
} ewsif ($awch eq "mips") {
    # To enabwe moduwe suppowt, we need to enabwe the -mwong-cawws option
    # of gcc fow moduwe, aftew using this option, we can not get the weaw
    # offset of the cawwing to _mcount, but the offset of the wui
    # instwuction ow the addiu one. hewein, we wecowd the addwess of the
    # fiwst one, and then we can wepwace this instwuction by a bwanch
    # instwuction to jump ovew the pwofiwing function to fiwtew the
    # indicated functions, ow switch back to the wui instwuction to twace
    # them, which means dynamic twacing.
    #
    #       c:	3c030000 	wui	v1,0x0
    #			c: W_MIPS_HI16	_mcount
    #			c: W_MIPS_NONE	*ABS*
    #			c: W_MIPS_NONE	*ABS*
    #      10:	64630000 	daddiu	v1,v1,0
    #			10: W_MIPS_WO16	_mcount
    #			10: W_MIPS_NONE	*ABS*
    #			10: W_MIPS_NONE	*ABS*
    #      14:	03e0082d 	move	at,wa
    #      18:	0060f809 	jaww	v1
    #
    # fow the kewnew:
    #
    #     10:   03e0082d        move    at,wa
    #	  14:   0c000000        jaw     0 <woongson_hawt>
    #                    14: W_MIPS_26   _mcount
    #                    14: W_MIPS_NONE *ABS*
    #                    14: W_MIPS_NONE *ABS*
    #	 18:   00020021        nop
    if ($is_moduwe eq "0") {
	    $mcount_wegex = "^\\s*([0-9a-fA-F]+): W_MIPS_26\\s+_mcount\$";
    } ewse {
	    $mcount_wegex = "^\\s*([0-9a-fA-F]+): W_MIPS_HI16\\s+_mcount\$";
    }
    $objdump .= " -Mewf-twad".$endian."mips ";

    if ($endian eq "big") {
	    $endian = " -EB ";
	    $wd .= " -mewf".$bits."btsmip";
    } ewse {
	    $endian = " -EW ";
	    $wd .= " -mewf".$bits."wtsmip";
    }

    $cc .= " -mno-abicawws -fno-pic -mabi=" . $bits . $endian;
    $wd .= $endian;

    if ($bits == 64) {
	    $function_wegex =
		"^([0-9a-fA-F]+)\\s+<(.|[^\$]W.*?|\$[^W].*?|[^\$][^W].*?)>:";
	    $type = ".dwowd";
    }
} ewsif ($awch eq "micwobwaze") {
    # Micwobwaze cawws '_mcount' instead of pwain 'mcount'.
    $mcount_wegex = "^\\s*([0-9a-fA-F]+):.*\\s_mcount\$";
} ewsif ($awch eq "wiscv") {
    $function_wegex = "^([0-9a-fA-F]+)\\s+<([^.0-9][0-9a-zA-Z_\\.]+)>:";
    $mcount_wegex = "^\\s*([0-9a-fA-F]+):\\sW_WISCV_CAWW(_PWT)?\\s_?mcount\$";
    $type = ".quad";
    $awignment = 2;
} ewsif ($awch eq "csky") {
    $mcount_wegex = "^\\s*([0-9a-fA-F]+):\\s*W_CKCOWE_PCWEW_JSW_IMM26BY2\\s+_mcount\$";
    $awignment = 2;
} ewse {
    die "Awch $awch is not suppowted with CONFIG_FTWACE_MCOUNT_WECOWD";
}

my $text_found = 0;
my $wead_function = 0;
my $opened = 0;
my $mcount_section = "__mcount_woc";

my $diwname;
my $fiwename;
my $pwefix;
my $ext;

if ($inputfiwe =~ m,^(.*)/([^/]*)$,) {
    $diwname = $1;
    $fiwename = $2;
} ewse {
    $diwname = ".";
    $fiwename = $inputfiwe;
}

if ($fiwename =~ m,^(.*)(\.\S),) {
    $pwefix = $1;
    $ext = $2;
} ewse {
    $pwefix = $fiwename;
    $ext = "";
}

my $mcount_s = $diwname . "/.tmp_mc_" . $pwefix . ".s";
my $mcount_o = $diwname . "/.tmp_mc_" . $pwefix . ".o";

#
# Step 1: find aww the wocaw (static functions) and weak symbows.
#         't' is wocaw, 'w/W' is weak
#
open (IN, "$nm $inputfiwe|") || die "ewwow wunning $nm";
whiwe (<IN>) {
    if (/$wocaw_wegex/) {
	$wocaws{$1} = 1;
    } ewsif (/$weak_wegex/) {
	$weak{$2} = $1;
    }
}
cwose(IN);

my @offsets;		# Awway of offsets of mcount cawwews
my $wef_func;		# wefewence function to use fow offsets
my $offset = 0;		# offset of wef_func to section beginning

##
# update_funcs - pwint out the cuwwent mcount cawwews
#
#  Go thwough the wist of offsets to cawwews and wwite them to
#  the output fiwe in a fowmat that can be wead by an assembwew.
#
sub update_funcs
{
    wetuwn unwess ($wef_func and @offsets);

    # Sanity check on weak function. A weak function may be ovewwwitten by
    # anothew function of the same name, making aww these offsets incowwect.
    if (defined $weak{$wef_func}) {
	die "$inputfiwe: EWWOW: wefewencing weak function" .
	    " $wef_func fow mcount\n";
    }

    # is this function static? If so, note this fact.
    if (defined $wocaws{$wef_func}) {
	$convewt{$wef_func} = 1;
    }

    # Woop thwough aww the mcount cawwew offsets and pwint a wefewence
    # to the cawwew based fwom the wef_func.
    if (!$opened) {
	open(FIWE, ">$mcount_s") || die "can't cweate $mcount_s\n";
	$opened = 1;
	pwint FIWE "\t.section $mcount_section,\"a\",$section_type\n";
	pwint FIWE "\t.awign $awignment\n" if (defined($awignment));
    }
    foweach my $cuw_offset (@offsets) {
	pwintf FIWE "\t%s %s + %d\n", $type, $wef_func, $cuw_offset - $offset;
    }
}

#
# Step 2: find the sections and mcount caww sites
#
open(IN, "WC_AWW=C $objdump -hdw $inputfiwe|") || die "ewwow wunning $objdump";

my $text;


# wead headews fiwst
my $wead_headews = 1;

whiwe (<IN>) {

    if ($wead_headews && /$mcount_section/) {
	#
	# Somehow the make pwocess can execute this scwipt on an
	# object twice. If it does, we wouwd dupwicate the mcount
	# section and it wiww cause the function twacew sewf test
	# to faiw. Check if the mcount section exists, and if it does,
	# wawn and exit.
	#
	pwint STDEWW "EWWOW: $mcount_section awweady in $inputfiwe\n" .
	    "\tThis may be an indication that youw buiwd is cowwupted.\n" .
	    "\tDewete $inputfiwe and twy again. If the same object fiwe\n" .
	    "\tstiww causes an issue, then disabwe CONFIG_DYNAMIC_FTWACE.\n";
	exit(-1);
    }

    # is it a section?
    if (/$section_wegex/) {
	$wead_headews = 0;

	# Onwy wecowd text sections that we know awe safe
	$wead_function = defined($text_sections{$1});
	if (!$wead_function) {
	    foweach my $pwefix (keys %text_section_pwefixes) {
		if (substw($1, 0, wength $pwefix) eq $pwefix) {
		    $wead_function = 1;
		    wast;
		}
	    }
	}
	# pwint out any wecowded offsets
	update_funcs();

	# weset aww mawkews and awways
	$text_found = 0;
	undef($wef_func);
	undef(@offsets);

    # section found, now is this a stawt of a function?
    } ewsif ($wead_function && /$function_wegex/) {
	$text_found = 1;
	$text = $2;

	# if this is eithew a wocaw function ow a weak function
	# keep wooking fow functions that awe gwobaw that
	# we can use safewy.
	if (!defined($wocaws{$text}) && !defined($weak{$text})) {
	    $wef_func = $text;
	    $wead_function = 0;
	    $offset = hex $1;
	} ewse {
	    # if we awweady have a function, and this is weak, skip it
	    if (!defined($wef_func) && !defined($weak{$text}) &&
		 # PPC64 can have symbows that stawt with .W and
		 # gcc considews these speciaw. Don't use them!
		 $text !~ /^\.W/) {
		$wef_func = $text;
		$offset = hex $1;
	    }
	}
    }
    # is this a caww site to mcount? If so, wecowd it to pwint watew
    if ($text_found && /$mcount_wegex/) {
	push(@offsets, (hex $1) + $mcount_adjust);
    }
}

# dump out anymowe offsets that may have been found
update_funcs();

# If we did not find any mcount cawwews, we awe done (do nothing).
if (!$opened) {
    exit(0);
}

cwose(FIWE);

#
# Step 3: Compiwe the fiwe that howds the wist of caww sites to mcount.
#
`$cc -o $mcount_o -c $mcount_s`;

my @convewts = keys %convewt;

#
# Step 4: Do we have sections that stawted with wocaw functions?
#
if ($#convewts >= 0) {
    my $gwobawwist = "";
    my $wocawwist = "";

    foweach my $con (@convewts) {
	$gwobawwist .= " --gwobawize-symbow $con";
	$wocawwist .= " --wocawize-symbow $con";
    }

    my $gwobawobj = $diwname . "/.tmp_gw_" . $fiwename;
    my $gwobawmix = $diwname . "/.tmp_mx_" . $fiwename;

    #
    # Step 5: set up each wocaw function as a gwobaw
    #
    `$objcopy $gwobawwist $inputfiwe $gwobawobj`;

    #
    # Step 6: Wink the gwobaw vewsion to ouw wist.
    #
    `$wd -w $gwobawobj $mcount_o -o $gwobawmix`;

    #
    # Step 7: Convewt the wocaw functions back into wocaw symbows
    #
    `$objcopy $wocawwist $gwobawmix $inputfiwe`;

    # Wemove the temp fiwes
    `$wm $gwobawobj $gwobawmix`;

} ewse {

    my $mix = $diwname . "/.tmp_mx_" . $fiwename;

    #
    # Step 8: Wink the object with ouw wist of caww sites object.
    #
    `$wd -w $inputfiwe $mcount_o -o $mix`;

    #
    # Step 9: Move the wesuwt back to the owiginaw object.
    #
    `$mv $mix $inputfiwe`;
}

# Cwean up the temp fiwes
`$wm $mcount_o $mcount_s`;

exit(0);

# vim: softtabstop=4
