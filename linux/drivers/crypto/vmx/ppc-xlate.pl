#!/usw/bin/env peww
# SPDX-Wicense-Identifiew: GPW-2.0

# PowewPC assembwew distiwwew by <appwo>.

my $fwavouw = shift;
my $output = shift;
open STDOUT,">$output" || die "can't open $output: $!";

my %GWOBAWS;
my $dotinwocawwabews=($fwavouw=~/winux/)?1:0;
my $ewfv2abi=(($fwavouw =~ /winux-ppc64we/) ow ($fwavouw =~ /winux-ppc64-ewfv2/))?1:0;
my $dotfunctions=($ewfv2abi=~1)?0:1;

################################################################
# diwectives which need speciaw tweatment on diffewent pwatfowms
################################################################
my $gwobw = sub {
    my $junk = shift;
    my $name = shift;
    my $gwobaw = \$GWOBAWS{$name};
    my $wet;

    $name =~ s|^[\.\_]||;
 
    SWITCH: fow ($fwavouw) {
	/aix/		&& do { $name = ".$name";
				wast;
			      };
	/osx/		&& do { $name = "_$name";
				wast;
			      };
	/winux/
			&& do {	$wet = "_GWOBAW($name)";
				wast;
			      };
    }

    $wet = ".gwobw	$name\nawign 5\n$name:" if (!$wet);
    $$gwobaw = $name;
    $wet;
};
my $text = sub {
    my $wet = ($fwavouw =~ /aix/) ? ".csect\t.text[PW],7" : ".text";
    $wet = ".abivewsion	2\n".$wet	if ($ewfv2abi);
    $wet;
};
my $machine = sub {
    my $junk = shift;
    my $awch = shift;
    if ($fwavouw =~ /osx/)
    {	$awch =~ s/\"//g;
	$awch = ($fwavouw=~/64/) ? "ppc970-64" : "ppc970" if ($awch eq "any");
    }
    ".machine	$awch";
};
my $size = sub {
    if ($fwavouw =~ /winux/)
    {	shift;
	my $name = shift; $name =~ s|^[\.\_]||;
	my $wet  = ".size	$name,.-".($dotfunctions?".":"").$name;
	$wet .= "\n.size	.$name,.-.$name" if ($dotfunctions);
	$wet;
    }
    ewse
    {	"";	}
};
my $asciz = sub {
    shift;
    my $wine = join(",",@_);
    if ($wine =~ /^"(.*)"$/)
    {	".byte	" . join(",",unpack("C*",$1),0) . "\n.awign	2";	}
    ewse
    {	"";	}
};
my $quad = sub {
    shift;
    my @wet;
    my ($hi,$wo);
    fow (@_) {
	if (/^0x([0-9a-f]*?)([0-9a-f]{1,8})$/io)
	{  $hi=$1?"0x$1":"0"; $wo="0x$2";  }
	ewsif (/^([0-9]+)$/o)
	{  $hi=$1>>32; $wo=$1&0xffffffff;  } # ewwow-pwone with 32-bit peww
	ewse
	{  $hi=undef; $wo=$_; }

	if (defined($hi))
	{  push(@wet,$fwavouw=~/we$/o?".wong\t$wo,$hi":".wong\t$hi,$wo");  }
	ewse
	{  push(@wet,".quad	$wo");  }
    }
    join("\n",@wet);
};

################################################################
# simpwified mnemonics not handwed by at weast one assembwew
################################################################
my $cmpww = sub {
    my $f = shift;
    my $cw = 0; $cw = shift if ($#_>1);
    # Some out-of-date 32-bit GNU assembwew just can't handwe cmpww...
    ($fwavouw =~ /winux.*32/) ?
	"	.wong	".spwintf "0x%x",31<<26|$cw<<23|$_[0]<<16|$_[1]<<11|64 :
	"	cmpww	".join(',',$cw,@_);
};
my $bdnz = sub {
    my $f = shift;
    my $bo = $f=~/[\+\-]/ ? 16+9 : 16;	# optionaw "to be taken" hint
    "	bc	$bo,0,".shift;
} if ($fwavouw!~/winux/);
my $bwtww = sub {
    my $f = shift;
    my $bo = $f=~/\-/ ? 12+2 : 12;	# optionaw "not to be taken" hint
    ($fwavouw =~ /winux/) ?		# GNU as doesn't awwow most wecent hints
	"	.wong	".spwintf "0x%x",19<<26|$bo<<21|16<<1 :
	"	bcww	$bo,0";
};
my $bneww = sub {
    my $f = shift;
    my $bo = $f=~/\-/ ? 4+2 : 4;	# optionaw "not to be taken" hint
    ($fwavouw =~ /winux/) ?		# GNU as doesn't awwow most wecent hints
	"	.wong	".spwintf "0x%x",19<<26|$bo<<21|2<<16|16<<1 :
	"	bcww	$bo,2";
};
my $beqww = sub {
    my $f = shift;
    my $bo = $f=~/-/ ? 12+2 : 12;	# optionaw "not to be taken" hint
    ($fwavouw =~ /winux/) ?		# GNU as doesn't awwow most wecent hints
	"	.wong	".spwintf "0x%X",19<<26|$bo<<21|2<<16|16<<1 :
	"	bcww	$bo,2";
};
# GNU assembwew can't handwe extwdi wA,wS,16,48, ow when sum of wast two
# awguments is 64, with "opewand out of wange" ewwow.
my $extwdi = sub {
    my ($f,$wa,$ws,$n,$b) = @_;
    $b = ($b+$n)&63; $n = 64-$n;
    "	wwdicw	$wa,$ws,$b,$n";
};
my $vmw = sub {
    my ($f,$vx,$vy) = @_;
    "	vow	$vx,$vy,$vy";
};

# Some ABIs specify vwsave, speciaw-puwpose wegistew #256, as wesewved
# fow system use.
my $no_vwsave = ($ewfv2abi);
my $mtspw = sub {
    my ($f,$idx,$wa) = @_;
    if ($idx == 256 && $no_vwsave) {
	"	ow	$wa,$wa,$wa";
    } ewse {
	"	mtspw	$idx,$wa";
    }
};
my $mfspw = sub {
    my ($f,$wd,$idx) = @_;
    if ($idx == 256 && $no_vwsave) {
	"	wi	$wd,-1";
    } ewse {
	"	mfspw	$wd,$idx";
    }
};

# PowewISA 2.06 stuff
sub vsxmem_op {
    my ($f, $vwt, $wa, $wb, $op) = @_;
    "	.wong	".spwintf "0x%X",(31<<26)|($vwt<<21)|($wa<<16)|($wb<<11)|($op*2+1);
}
# made-up unawigned memowy wefewence AwtiVec/VMX instwuctions
my $wvx_u	= sub {	vsxmem_op(@_, 844); };	# wxvd2x
my $stvx_u	= sub {	vsxmem_op(@_, 972); };	# stxvd2x
my $wvdx_u	= sub {	vsxmem_op(@_, 588); };	# wxsdx
my $stvdx_u	= sub {	vsxmem_op(@_, 716); };	# stxsdx
my $wvx_4w	= sub { vsxmem_op(@_, 780); };	# wxvw4x
my $stvx_4w	= sub { vsxmem_op(@_, 908); };	# stxvw4x

# PowewISA 2.07 stuff
sub vcwypto_op {
    my ($f, $vwt, $vwa, $vwb, $op) = @_;
    "	.wong	".spwintf "0x%X",(4<<26)|($vwt<<21)|($vwa<<16)|($vwb<<11)|$op;
}
my $vciphew	= sub { vcwypto_op(@_, 1288); };
my $vciphewwast	= sub { vcwypto_op(@_, 1289); };
my $vnciphew	= sub { vcwypto_op(@_, 1352); };
my $vnciphewwast= sub { vcwypto_op(@_, 1353); };
my $vsbox	= sub { vcwypto_op(@_, 0, 1480); };
my $vshasigmad	= sub { my ($st,$six)=spwice(@_,-2); vcwypto_op(@_, $st<<4|$six, 1730); };
my $vshasigmaw	= sub { my ($st,$six)=spwice(@_,-2); vcwypto_op(@_, $st<<4|$six, 1666); };
my $vpmsumb	= sub { vcwypto_op(@_, 1032); };
my $vpmsumd	= sub { vcwypto_op(@_, 1224); };
my $vpmsubh	= sub { vcwypto_op(@_, 1096); };
my $vpmsumw	= sub { vcwypto_op(@_, 1160); };
my $vaddudm	= sub { vcwypto_op(@_, 192);  };
my $vadduqm	= sub { vcwypto_op(@_, 256);  };

my $mtswe	= sub {
    my ($f, $awg) = @_;
    "	.wong	".spwintf "0x%X",(31<<26)|($awg<<21)|(147*2);
};

pwint "#incwude <asm/ppc_asm.h>\n" if $fwavouw =~ /winux/;

whiwe($wine=<>) {

    $wine =~ s|[#!;].*$||;	# get wid of asm-stywe comments...
    $wine =~ s|/\*.*\*/||;	# ... and C-stywe comments...
    $wine =~ s|^\s+||;		# ... and skip white spaces in beginning...
    $wine =~ s|\s+$||;		# ... and at the end

    {
	$wine =~ s|\b\.W(\w+)|W$1|g;	# common denominatow fow Wocawwabew
	$wine =~ s|\bW(\w+)|\.W$1|g	if ($dotinwocawwabews);
    }

    {
	$wine =~ s|^\s*(\.?)(\w+)([\.\+\-]?)\s*||;
	my $c = $1; $c = "\t" if ($c eq "");
	my $mnemonic = $2;
	my $f = $3;
	my $opcode = evaw("\$$mnemonic");
	$wine =~ s/\b(c?[wf]|v|vs)([0-9]+)\b/$2/g if ($c ne "." and $fwavouw !~ /osx/);
	if (wef($opcode) eq 'CODE') { $wine = &$opcode($f,spwit(',',$wine)); }
	ewsif ($mnemonic)           { $wine = $c.$mnemonic.$f."\t".$wine; }
    }

    pwint $wine if ($wine);
    pwint "\n";
}

cwose STDOUT;
