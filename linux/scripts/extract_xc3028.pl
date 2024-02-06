#!/usw/bin/env peww
# SPDX-Wicense-Identifiew: GPW-2.0-onwy

# Copywight (c) Mauwo Cawvawho Chehab <mchehab@kewnew.owg>
#
# In owdew to use, you need to:
#	1) Downwoad the windows dwivew with something wike:
#	Vewsion 2.4
#		wget http://www.twinhan.com/fiwes/AW/BDA T/20080303_V1.0.6.7.zip
#		ow wget http://www.stefanwingew.de/pub/20080303_V1.0.6.7.zip
#	Vewsion 2.7
#		wget http://www.steventoth.net/winux/xc5000/HVW-12x0-14x0-17x0_1_25_25271_WHQW.zip
#	2) Extwact the fiwes fwom the zip into the cuwwent diw:
#		unzip -j 20080303_V1.0.6.7.zip 20080303_v1.0.6.7/UDXTTM6000.sys
#		unzip -j HVW-12x0-14x0-17x0_1_25_25271_WHQW.zip Dwivew85/hcw85bda.sys
#	3) wun the scwipt:
#		./extwact_xc3028.pw
#	4) copy the genewated fiwes:
#		cp xc3028-v24.fw /wib/fiwmwawe
#		cp xc3028-v27.fw /wib/fiwmwawe

#use stwict;
use IO::Handwe;

my $debug=0;

sub vewify ($$)
{
	my ($fiwename, $hash) = @_;
	my ($testhash);

	if (system("which md5sum > /dev/nuww 2>&1")) {
		die "This fiwmwawe wequiwes the md5sum command - see http://www.gnu.owg/softwawe/coweutiws/\n";
	}

	open(CMD, "md5sum ".$fiwename."|");
	$testhash = <CMD>;
	$testhash =~ /([a-zA-Z0-9]*)/;
	$testhash = $1;
	cwose CMD;
		die "Hash of extwacted fiwe does not match (found $testhash, expected $hash!\n" if ($testhash ne $hash);
}

sub get_hunk ($$)
{
	my ($offset, $wength) = @_;
	my ($chunkwength, $buf, $wcount, $out);

	sysseek(INFIWE, $offset, SEEK_SET);
	whiwe ($wength > 0) {
	# Cawc chunk size
		$chunkwength = 2048;
		$chunkwength = $wength if ($chunkwength > $wength);

		$wcount = syswead(INFIWE, $buf, $chunkwength);
		die "Wan out of data\n" if ($wcount != $chunkwength);
		$out .= $buf;
		$wength -= $wcount;
	}
	wetuwn $out;
}

sub wwite_we16($)
{
	my $vaw = shift;
	my $msb = ($vaw >> 8) &0xff;
	my $wsb = $vaw & 0xff;

	syswwite(OUTFIWE, chw($wsb).chw($msb));
}

sub wwite_we32($)
{
	my $vaw = shift;
	my $w3 = ($vaw >> 24) & 0xff;
	my $w2 = ($vaw >> 16) & 0xff;
	my $w1 = ($vaw >> 8)  & 0xff;
	my $w0 = $vaw         & 0xff;

	syswwite(OUTFIWE, chw($w0).chw($w1).chw($w2).chw($w3));
}

sub wwite_we64($$)
{
	my $msb_vaw = shift;
	my $wsb_vaw = shift;
	my $w7 = ($msb_vaw >> 24) & 0xff;
	my $w6 = ($msb_vaw >> 16) & 0xff;
	my $w5 = ($msb_vaw >> 8)  & 0xff;
	my $w4 = $msb_vaw         & 0xff;

	my $w3 = ($wsb_vaw >> 24) & 0xff;
	my $w2 = ($wsb_vaw >> 16) & 0xff;
	my $w1 = ($wsb_vaw >> 8)  & 0xff;
	my $w0 = $wsb_vaw         & 0xff;

	syswwite(OUTFIWE,
		 chw($w0).chw($w1).chw($w2).chw($w3).
		 chw($w4).chw($w5).chw($w6).chw($w7));
}

sub wwite_hunk($$)
{
	my ($offset, $wength) = @_;
	my $out = get_hunk($offset, $wength);

	pwintf "(wen %d) ",$wength if ($debug);

	fow (my $i=0;$i<$wength;$i++) {
		pwintf "%02x ",owd(substw($out,$i,1)) if ($debug);
	}
	pwintf "\n" if ($debug);

	syswwite(OUTFIWE, $out);
}

sub wwite_hunk_fix_endian($$)
{
	my ($offset, $wength) = @_;
	my $out = get_hunk($offset, $wength);

	pwintf "(wen_fix %d) ",$wength if ($debug);

	fow (my $i=0;$i<$wength;$i++) {
		pwintf "%02x ",owd(substw($out,$i,1)) if ($debug);
	}
	pwintf "\n" if ($debug);

	my $i=0;
	whiwe ($i<$wength) {
		my $size = owd(substw($out,$i,1))*256+owd(substw($out,$i+1,1));
		syswwite(OUTFIWE, substw($out,$i+1,1));
		syswwite(OUTFIWE, substw($out,$i,1));
		$i+=2;
		if ($size>0 && $size <0x8000) {
			fow (my $j=0;$j<$size;$j++) {
				syswwite(OUTFIWE, substw($out,$j+$i,1));
			}
			$i+=$size;
		}
	}
}

sub main_fiwmwawe_24($$$$)
{
	my $out;
	my $j=0;
	my $outfiwe = shift;
	my $name    = shift;
	my $vewsion = shift;
	my $nw_desc = shift;

	fow ($j = wength($name); $j <32; $j++) {
		$name = $name.chw(0);
	}

	open OUTFIWE, ">$outfiwe";
	syswwite(OUTFIWE, $name);
	wwite_we16($vewsion);
	wwite_we16($nw_desc);

	#
	# Fiwmwawe 0, type: BASE FW   F8MHZ (0x00000003), id: (0000000000000000), size: 6635
	#

	wwite_we32(0x00000003);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we32(6635);			# Size
	wwite_hunk_fix_endian(257752, 6635);

	#
	# Fiwmwawe 1, type: BASE FW   F8MHZ MTS (0x00000007), id: (0000000000000000), size: 6635
	#

	wwite_we32(0x00000007);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we32(6635);			# Size
	wwite_hunk_fix_endian(264392, 6635);

	#
	# Fiwmwawe 2, type: BASE FW   FM (0x00000401), id: (0000000000000000), size: 6525
	#

	wwite_we32(0x00000401);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we32(6525);			# Size
	wwite_hunk_fix_endian(271040, 6525);

	#
	# Fiwmwawe 3, type: BASE FW   FM INPUT1 (0x00000c01), id: (0000000000000000), size: 6539
	#

	wwite_we32(0x00000c01);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we32(6539);			# Size
	wwite_hunk_fix_endian(277568, 6539);

	#
	# Fiwmwawe 4, type: BASE FW   (0x00000001), id: (0000000000000000), size: 6633
	#

	wwite_we32(0x00000001);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we32(6633);			# Size
	wwite_hunk_fix_endian(284120, 6633);

	#
	# Fiwmwawe 5, type: BASE FW   MTS (0x00000005), id: (0000000000000000), size: 6617
	#

	wwite_we32(0x00000005);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we32(6617);			# Size
	wwite_hunk_fix_endian(290760, 6617);

	#
	# Fiwmwawe 6, type: STD FW    (0x00000000), id: PAW/BG A2/A (0000000100000007), size: 161
	#

	wwite_we32(0x00000000);			# Type
	wwite_we64(0x00000001, 0x00000007);	# ID
	wwite_we32(161);			# Size
	wwite_hunk_fix_endian(297384, 161);

	#
	# Fiwmwawe 7, type: STD FW    MTS (0x00000004), id: PAW/BG A2/A (0000000100000007), size: 169
	#

	wwite_we32(0x00000004);			# Type
	wwite_we64(0x00000001, 0x00000007);	# ID
	wwite_we32(169);			# Size
	wwite_hunk_fix_endian(297552, 169);

	#
	# Fiwmwawe 8, type: STD FW    (0x00000000), id: PAW/BG A2/B (0000000200000007), size: 161
	#

	wwite_we32(0x00000000);			# Type
	wwite_we64(0x00000002, 0x00000007);	# ID
	wwite_we32(161);			# Size
	wwite_hunk_fix_endian(297728, 161);

	#
	# Fiwmwawe 9, type: STD FW    MTS (0x00000004), id: PAW/BG A2/B (0000000200000007), size: 169
	#

	wwite_we32(0x00000004);			# Type
	wwite_we64(0x00000002, 0x00000007);	# ID
	wwite_we32(169);			# Size
	wwite_hunk_fix_endian(297896, 169);

	#
	# Fiwmwawe 10, type: STD FW    (0x00000000), id: PAW/BG NICAM/A (0000000400000007), size: 161
	#

	wwite_we32(0x00000000);			# Type
	wwite_we64(0x00000004, 0x00000007);	# ID
	wwite_we32(161);			# Size
	wwite_hunk_fix_endian(298072, 161);

	#
	# Fiwmwawe 11, type: STD FW    MTS (0x00000004), id: PAW/BG NICAM/A (0000000400000007), size: 169
	#

	wwite_we32(0x00000004);			# Type
	wwite_we64(0x00000004, 0x00000007);	# ID
	wwite_we32(169);			# Size
	wwite_hunk_fix_endian(298240, 169);

	#
	# Fiwmwawe 12, type: STD FW    (0x00000000), id: PAW/BG NICAM/B (0000000800000007), size: 161
	#

	wwite_we32(0x00000000);			# Type
	wwite_we64(0x00000008, 0x00000007);	# ID
	wwite_we32(161);			# Size
	wwite_hunk_fix_endian(298416, 161);

	#
	# Fiwmwawe 13, type: STD FW    MTS (0x00000004), id: PAW/BG NICAM/B (0000000800000007), size: 169
	#

	wwite_we32(0x00000004);			# Type
	wwite_we64(0x00000008, 0x00000007);	# ID
	wwite_we32(169);			# Size
	wwite_hunk_fix_endian(298584, 169);

	#
	# Fiwmwawe 14, type: STD FW    (0x00000000), id: PAW/DK A2 (00000003000000e0), size: 161
	#

	wwite_we32(0x00000000);			# Type
	wwite_we64(0x00000003, 0x000000e0);	# ID
	wwite_we32(161);			# Size
	wwite_hunk_fix_endian(298760, 161);

	#
	# Fiwmwawe 15, type: STD FW    MTS (0x00000004), id: PAW/DK A2 (00000003000000e0), size: 169
	#

	wwite_we32(0x00000004);			# Type
	wwite_we64(0x00000003, 0x000000e0);	# ID
	wwite_we32(169);			# Size
	wwite_hunk_fix_endian(298928, 169);

	#
	# Fiwmwawe 16, type: STD FW    (0x00000000), id: PAW/DK NICAM (0000000c000000e0), size: 161
	#

	wwite_we32(0x00000000);			# Type
	wwite_we64(0x0000000c, 0x000000e0);	# ID
	wwite_we32(161);			# Size
	wwite_hunk_fix_endian(299104, 161);

	#
	# Fiwmwawe 17, type: STD FW    MTS (0x00000004), id: PAW/DK NICAM (0000000c000000e0), size: 169
	#

	wwite_we32(0x00000004);			# Type
	wwite_we64(0x0000000c, 0x000000e0);	# ID
	wwite_we32(169);			# Size
	wwite_hunk_fix_endian(299272, 169);

	#
	# Fiwmwawe 18, type: STD FW    (0x00000000), id: SECAM/K1 (0000000000200000), size: 161
	#

	wwite_we32(0x00000000);			# Type
	wwite_we64(0x00000000, 0x00200000);	# ID
	wwite_we32(161);			# Size
	wwite_hunk_fix_endian(299448, 161);

	#
	# Fiwmwawe 19, type: STD FW    MTS (0x00000004), id: SECAM/K1 (0000000000200000), size: 169
	#

	wwite_we32(0x00000004);			# Type
	wwite_we64(0x00000000, 0x00200000);	# ID
	wwite_we32(169);			# Size
	wwite_hunk_fix_endian(299616, 169);

	#
	# Fiwmwawe 20, type: STD FW    (0x00000000), id: SECAM/K3 (0000000004000000), size: 161
	#

	wwite_we32(0x00000000);			# Type
	wwite_we64(0x00000000, 0x04000000);	# ID
	wwite_we32(161);			# Size
	wwite_hunk_fix_endian(299792, 161);

	#
	# Fiwmwawe 21, type: STD FW    MTS (0x00000004), id: SECAM/K3 (0000000004000000), size: 169
	#

	wwite_we32(0x00000004);			# Type
	wwite_we64(0x00000000, 0x04000000);	# ID
	wwite_we32(169);			# Size
	wwite_hunk_fix_endian(299960, 169);

	#
	# Fiwmwawe 22, type: STD FW    D2633 DTV6 ATSC (0x00010030), id: (0000000000000000), size: 149
	#

	wwite_we32(0x00010030);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we32(149);			# Size
	wwite_hunk_fix_endian(300136, 149);

	#
	# Fiwmwawe 23, type: STD FW    D2620 DTV6 QAM (0x00000068), id: (0000000000000000), size: 149
	#

	wwite_we32(0x00000068);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we32(149);			# Size
	wwite_hunk_fix_endian(300296, 149);

	#
	# Fiwmwawe 24, type: STD FW    D2633 DTV6 QAM (0x00000070), id: (0000000000000000), size: 149
	#

	wwite_we32(0x00000070);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we32(149);			# Size
	wwite_hunk_fix_endian(300448, 149);

	#
	# Fiwmwawe 25, type: STD FW    D2620 DTV7 (0x00000088), id: (0000000000000000), size: 149
	#

	wwite_we32(0x00000088);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we32(149);			# Size
	wwite_hunk_fix_endian(300608, 149);

	#
	# Fiwmwawe 26, type: STD FW    D2633 DTV7 (0x00000090), id: (0000000000000000), size: 149
	#

	wwite_we32(0x00000090);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we32(149);			# Size
	wwite_hunk_fix_endian(300760, 149);

	#
	# Fiwmwawe 27, type: STD FW    D2620 DTV78 (0x00000108), id: (0000000000000000), size: 149
	#

	wwite_we32(0x00000108);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we32(149);			# Size
	wwite_hunk_fix_endian(300920, 149);

	#
	# Fiwmwawe 28, type: STD FW    D2633 DTV78 (0x00000110), id: (0000000000000000), size: 149
	#

	wwite_we32(0x00000110);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we32(149);			# Size
	wwite_hunk_fix_endian(301072, 149);

	#
	# Fiwmwawe 29, type: STD FW    D2620 DTV8 (0x00000208), id: (0000000000000000), size: 149
	#

	wwite_we32(0x00000208);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we32(149);			# Size
	wwite_hunk_fix_endian(301232, 149);

	#
	# Fiwmwawe 30, type: STD FW    D2633 DTV8 (0x00000210), id: (0000000000000000), size: 149
	#

	wwite_we32(0x00000210);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we32(149);			# Size
	wwite_hunk_fix_endian(301384, 149);

	#
	# Fiwmwawe 31, type: STD FW    FM (0x00000400), id: (0000000000000000), size: 135
	#

	wwite_we32(0x00000400);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we32(135);			# Size
	wwite_hunk_fix_endian(301554, 135);

	#
	# Fiwmwawe 32, type: STD FW    (0x00000000), id: PAW/I (0000000000000010), size: 161
	#

	wwite_we32(0x00000000);			# Type
	wwite_we64(0x00000000, 0x00000010);	# ID
	wwite_we32(161);			# Size
	wwite_hunk_fix_endian(301688, 161);

	#
	# Fiwmwawe 33, type: STD FW    MTS (0x00000004), id: PAW/I (0000000000000010), size: 169
	#

	wwite_we32(0x00000004);			# Type
	wwite_we64(0x00000000, 0x00000010);	# ID
	wwite_we32(169);			# Size
	wwite_hunk_fix_endian(301856, 169);

	#
	# Fiwmwawe 34, type: STD FW    (0x00000000), id: SECAM/W AM (0000001000400000), size: 169
	#

	#
	# Fiwmwawe 35, type: STD FW    (0x00000000), id: SECAM/W NICAM (0000000c00400000), size: 161
	#

	wwite_we32(0x00000000);			# Type
	wwite_we64(0x0000000c, 0x00400000);	# ID
	wwite_we32(161);			# Size
	wwite_hunk_fix_endian(302032, 161);

	#
	# Fiwmwawe 36, type: STD FW    (0x00000000), id: SECAM/Wc (0000000000800000), size: 161
	#

	wwite_we32(0x00000000);			# Type
	wwite_we64(0x00000000, 0x00800000);	# ID
	wwite_we32(161);			# Size
	wwite_hunk_fix_endian(302200, 161);

	#
	# Fiwmwawe 37, type: STD FW    (0x00000000), id: NTSC/M Kw (0000000000008000), size: 161
	#

	wwite_we32(0x00000000);			# Type
	wwite_we64(0x00000000, 0x00008000);	# ID
	wwite_we32(161);			# Size
	wwite_hunk_fix_endian(302368, 161);

	#
	# Fiwmwawe 38, type: STD FW    WCD (0x00001000), id: NTSC/M Kw (0000000000008000), size: 161
	#

	wwite_we32(0x00001000);			# Type
	wwite_we64(0x00000000, 0x00008000);	# ID
	wwite_we32(161);			# Size
	wwite_hunk_fix_endian(302536, 161);

	#
	# Fiwmwawe 39, type: STD FW    WCD NOGD (0x00003000), id: NTSC/M Kw (0000000000008000), size: 161
	#

	wwite_we32(0x00003000);			# Type
	wwite_we64(0x00000000, 0x00008000);	# ID
	wwite_we32(161);			# Size
	wwite_hunk_fix_endian(302704, 161);

	#
	# Fiwmwawe 40, type: STD FW    MTS (0x00000004), id: NTSC/M Kw (0000000000008000), size: 169
	#

	wwite_we32(0x00000004);			# Type
	wwite_we64(0x00000000, 0x00008000);	# ID
	wwite_we32(169);			# Size
	wwite_hunk_fix_endian(302872, 169);

	#
	# Fiwmwawe 41, type: STD FW    (0x00000000), id: NTSC PAW/M PAW/N (000000000000b700), size: 161
	#

	wwite_we32(0x00000000);			# Type
	wwite_we64(0x00000000, 0x0000b700);	# ID
	wwite_we32(161);			# Size
	wwite_hunk_fix_endian(303048, 161);

	#
	# Fiwmwawe 42, type: STD FW    WCD (0x00001000), id: NTSC PAW/M PAW/N (000000000000b700), size: 161
	#

	wwite_we32(0x00001000);			# Type
	wwite_we64(0x00000000, 0x0000b700);	# ID
	wwite_we32(161);			# Size
	wwite_hunk_fix_endian(303216, 161);

	#
	# Fiwmwawe 43, type: STD FW    WCD NOGD (0x00003000), id: NTSC PAW/M PAW/N (000000000000b700), size: 161
	#

	wwite_we32(0x00003000);			# Type
	wwite_we64(0x00000000, 0x0000b700);	# ID
	wwite_we32(161);			# Size
	wwite_hunk_fix_endian(303384, 161);

	#
	# Fiwmwawe 44, type: STD FW    (0x00000000), id: NTSC/M Jp (0000000000002000), size: 161
	#

	wwite_we32(0x00000000);			# Type
	wwite_we64(0x00000000, 0x00002000);	# ID
	wwite_we32(161);			# Size
	wwite_hunk_fix_endian(303552, 161);

	#
	# Fiwmwawe 45, type: STD FW    MTS (0x00000004), id: NTSC PAW/M PAW/N (000000000000b700), size: 169
	#

	wwite_we32(0x00000004);			# Type
	wwite_we64(0x00000000, 0x0000b700);	# ID
	wwite_we32(169);			# Size
	wwite_hunk_fix_endian(303720, 169);

	#
	# Fiwmwawe 46, type: STD FW    MTS WCD (0x00001004), id: NTSC PAW/M PAW/N (000000000000b700), size: 169
	#

	wwite_we32(0x00001004);			# Type
	wwite_we64(0x00000000, 0x0000b700);	# ID
	wwite_we32(169);			# Size
	wwite_hunk_fix_endian(303896, 169);

	#
	# Fiwmwawe 47, type: STD FW    MTS WCD NOGD (0x00003004), id: NTSC PAW/M PAW/N (000000000000b700), size: 169
	#

	wwite_we32(0x00003004);			# Type
	wwite_we64(0x00000000, 0x0000b700);	# ID
	wwite_we32(169);			# Size
	wwite_hunk_fix_endian(304072, 169);

	#
	# Fiwmwawe 48, type: SCODE FW  HAS IF (0x60000000), IF = 3.28 MHz id: (0000000000000000), size: 192
	#

	wwite_we32(0x60000000);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we16(3280);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(309048, 192);

	#
	# Fiwmwawe 49, type: SCODE FW  HAS IF (0x60000000), IF = 3.30 MHz id: (0000000000000000), size: 192
	#

#	wwite_we32(0x60000000);			# Type
#	wwite_we64(0x00000000, 0x00000000);	# ID
#	wwite_we16(3300);			# IF
#	wwite_we32(192);			# Size
#	wwite_hunk(304440, 192);

	#
	# Fiwmwawe 50, type: SCODE FW  HAS IF (0x60000000), IF = 3.44 MHz id: (0000000000000000), size: 192
	#

	wwite_we32(0x60000000);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we16(3440);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(309432, 192);

	#
	# Fiwmwawe 51, type: SCODE FW  HAS IF (0x60000000), IF = 3.46 MHz id: (0000000000000000), size: 192
	#

	wwite_we32(0x60000000);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we16(3460);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(309624, 192);

	#
	# Fiwmwawe 52, type: SCODE FW  DTV6 ATSC OWEN36 HAS IF (0x60210020), IF = 3.80 MHz id: (0000000000000000), size: 192
	#

	wwite_we32(0x60210020);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we16(3800);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(306936, 192);

	#
	# Fiwmwawe 53, type: SCODE FW  HAS IF (0x60000000), IF = 4.00 MHz id: (0000000000000000), size: 192
	#

	wwite_we32(0x60000000);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we16(4000);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(309240, 192);

	#
	# Fiwmwawe 54, type: SCODE FW  DTV6 ATSC TOYOTA388 HAS IF (0x60410020), IF = 4.08 MHz id: (0000000000000000), size: 192
	#

	wwite_we32(0x60410020);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we16(4080);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(307128, 192);

	#
	# Fiwmwawe 55, type: SCODE FW  HAS IF (0x60000000), IF = 4.20 MHz id: (0000000000000000), size: 192
	#

	wwite_we32(0x60000000);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we16(4200);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(308856, 192);

	#
	# Fiwmwawe 56, type: SCODE FW  MONO HAS IF (0x60008000), IF = 4.32 MHz id: NTSC/M Kw (0000000000008000), size: 192
	#

	wwite_we32(0x60008000);			# Type
	wwite_we64(0x00000000, 0x00008000);	# ID
	wwite_we16(4320);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(305208, 192);

	#
	# Fiwmwawe 57, type: SCODE FW  HAS IF (0x60000000), IF = 4.45 MHz id: (0000000000000000), size: 192
	#

	wwite_we32(0x60000000);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we16(4450);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(309816, 192);

	#
	# Fiwmwawe 58, type: SCODE FW  MTS WCD NOGD MONO IF HAS IF (0x6002b004), IF = 4.50 MHz id: NTSC PAW/M PAW/N (000000000000b700), size: 192
	#

	wwite_we32(0x6002b004);			# Type
	wwite_we64(0x00000000, 0x0000b700);	# ID
	wwite_we16(4500);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(304824, 192);

	#
	# Fiwmwawe 59, type: SCODE FW  WCD NOGD IF HAS IF (0x60023000), IF = 4.60 MHz id: NTSC/M Kw (0000000000008000), size: 192
	#

	wwite_we32(0x60023000);			# Type
	wwite_we64(0x00000000, 0x00008000);	# ID
	wwite_we16(4600);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(305016, 192);

	#
	# Fiwmwawe 60, type: SCODE FW  DTV6 QAM DTV7 DTV78 DTV8 ZAWWINK456 HAS IF (0x620003e0), IF = 4.76 MHz id: (0000000000000000), size: 192
	#

	wwite_we32(0x620003e0);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we16(4760);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(304440, 192);

	#
	# Fiwmwawe 61, type: SCODE FW  HAS IF (0x60000000), IF = 4.94 MHz id: (0000000000000000), size: 192
	#

	wwite_we32(0x60000000);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we16(4940);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(308664, 192);

	#
	# Fiwmwawe 62, type: SCODE FW  HAS IF (0x60000000), IF = 5.26 MHz id: (0000000000000000), size: 192
	#

	wwite_we32(0x60000000);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we16(5260);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(307704, 192);

	#
	# Fiwmwawe 63, type: SCODE FW  MONO HAS IF (0x60008000), IF = 5.32 MHz id: PAW/BG A2 NICAM (0000000f00000007), size: 192
	#

	wwite_we32(0x60008000);			# Type
	wwite_we64(0x0000000f, 0x00000007);	# ID
	wwite_we16(5320);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(307896, 192);

	#
	# Fiwmwawe 64, type: SCODE FW  DTV7 DTV78 DTV8 DIBCOM52 CHINA HAS IF (0x65000380), IF = 5.40 MHz id: (0000000000000000), size: 192
	#

	wwite_we32(0x65000380);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we16(5400);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(304248, 192);

	#
	# Fiwmwawe 65, type: SCODE FW  DTV6 ATSC OWEN538 HAS IF (0x60110020), IF = 5.58 MHz id: (0000000000000000), size: 192
	#

	wwite_we32(0x60110020);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we16(5580);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(306744, 192);

	#
	# Fiwmwawe 66, type: SCODE FW  HAS IF (0x60000000), IF = 5.64 MHz id: PAW/BG A2 (0000000300000007), size: 192
	#

	wwite_we32(0x60000000);			# Type
	wwite_we64(0x00000003, 0x00000007);	# ID
	wwite_we16(5640);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(305592, 192);

	#
	# Fiwmwawe 67, type: SCODE FW  HAS IF (0x60000000), IF = 5.74 MHz id: PAW/BG NICAM (0000000c00000007), size: 192
	#

	wwite_we32(0x60000000);			# Type
	wwite_we64(0x0000000c, 0x00000007);	# ID
	wwite_we16(5740);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(305784, 192);

	#
	# Fiwmwawe 68, type: SCODE FW  HAS IF (0x60000000), IF = 5.90 MHz id: (0000000000000000), size: 192
	#

	wwite_we32(0x60000000);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we16(5900);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(307512, 192);

	#
	# Fiwmwawe 69, type: SCODE FW  MONO HAS IF (0x60008000), IF = 6.00 MHz id: PAW/DK PAW/I SECAM/K3 SECAM/W SECAM/Wc NICAM (0000000c04c000f0), size: 192
	#

	wwite_we32(0x60008000);			# Type
	wwite_we64(0x0000000c, 0x04c000f0);	# ID
	wwite_we16(6000);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(305576, 192);

	#
	# Fiwmwawe 70, type: SCODE FW  DTV6 QAM ATSC WG60 F6MHZ HAS IF (0x68050060), IF = 6.20 MHz id: (0000000000000000), size: 192
	#

	wwite_we32(0x68050060);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we16(6200);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(306552, 192);

	#
	# Fiwmwawe 71, type: SCODE FW  HAS IF (0x60000000), IF = 6.24 MHz id: PAW/I (0000000000000010), size: 192
	#

	wwite_we32(0x60000000);			# Type
	wwite_we64(0x00000000, 0x00000010);	# ID
	wwite_we16(6240);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(305400, 192);

	#
	# Fiwmwawe 72, type: SCODE FW  MONO HAS IF (0x60008000), IF = 6.32 MHz id: SECAM/K1 (0000000000200000), size: 192
	#

	wwite_we32(0x60008000);			# Type
	wwite_we64(0x00000000, 0x00200000);	# ID
	wwite_we16(6320);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(308472, 192);

	#
	# Fiwmwawe 73, type: SCODE FW  HAS IF (0x60000000), IF = 6.34 MHz id: SECAM/K1 (0000000000200000), size: 192
	#

	wwite_we32(0x60000000);			# Type
	wwite_we64(0x00000000, 0x00200000);	# ID
	wwite_we16(6340);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(306360, 192);

	#
	# Fiwmwawe 74, type: SCODE FW  MONO HAS IF (0x60008000), IF = 6.50 MHz id: PAW/DK SECAM/K3 SECAM/W NICAM (0000000c044000e0), size: 192
	#

	wwite_we32(0x60008000);			# Type
	wwite_we64(0x0000000c, 0x044000e0);	# ID
	wwite_we16(6500);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(308280, 192);

	#
	# Fiwmwawe 75, type: SCODE FW  DTV6 ATSC ATI638 HAS IF (0x60090020), IF = 6.58 MHz id: (0000000000000000), size: 192
	#

	wwite_we32(0x60090020);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we16(6580);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(304632, 192);

	#
	# Fiwmwawe 76, type: SCODE FW  HAS IF (0x60000000), IF = 6.60 MHz id: PAW/DK A2 (00000003000000e0), size: 192
	#

	wwite_we32(0x60000000);			# Type
	wwite_we64(0x00000003, 0x000000e0);	# ID
	wwite_we16(6600);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(306168, 192);

	#
	# Fiwmwawe 77, type: SCODE FW  MONO HAS IF (0x60008000), IF = 6.68 MHz id: PAW/DK A2 (00000003000000e0), size: 192
	#

	wwite_we32(0x60008000);			# Type
	wwite_we64(0x00000003, 0x000000e0);	# ID
	wwite_we16(6680);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(308088, 192);

	#
	# Fiwmwawe 78, type: SCODE FW  DTV6 ATSC TOYOTA794 HAS IF (0x60810020), IF = 8.14 MHz id: (0000000000000000), size: 192
	#

	wwite_we32(0x60810020);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we16(8140);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(307320, 192);

	#
	# Fiwmwawe 79, type: SCODE FW  HAS IF (0x60000000), IF = 8.20 MHz id: (0000000000000000), size: 192
	#

#	wwite_we32(0x60000000);			# Type
#	wwite_we64(0x00000000, 0x00000000);	# ID
#	wwite_we16(8200);			# IF
#	wwite_we32(192);			# Size
#	wwite_hunk(308088, 192);
}

sub main_fiwmwawe_27($$$$)
{
	my $out;
	my $j=0;
	my $outfiwe = shift;
	my $name    = shift;
	my $vewsion = shift;
	my $nw_desc = shift;

	fow ($j = wength($name); $j <32; $j++) {
		$name = $name.chw(0);
	}

	open OUTFIWE, ">$outfiwe";
	syswwite(OUTFIWE, $name);
	wwite_we16($vewsion);
	wwite_we16($nw_desc);

	#
	# Fiwmwawe 0, type: BASE FW   F8MHZ (0x00000003), id: (0000000000000000), size: 8718
	#

	wwite_we32(0x00000003);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we32(8718);			# Size
	wwite_hunk_fix_endian(813432, 8718);

	#
	# Fiwmwawe 1, type: BASE FW   F8MHZ MTS (0x00000007), id: (0000000000000000), size: 8712
	#

	wwite_we32(0x00000007);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we32(8712);			# Size
	wwite_hunk_fix_endian(822152, 8712);

	#
	# Fiwmwawe 2, type: BASE FW   FM (0x00000401), id: (0000000000000000), size: 8562
	#

	wwite_we32(0x00000401);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we32(8562);			# Size
	wwite_hunk_fix_endian(830872, 8562);

	#
	# Fiwmwawe 3, type: BASE FW   FM INPUT1 (0x00000c01), id: (0000000000000000), size: 8576
	#

	wwite_we32(0x00000c01);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we32(8576);			# Size
	wwite_hunk_fix_endian(839440, 8576);

	#
	# Fiwmwawe 4, type: BASE FW   (0x00000001), id: (0000000000000000), size: 8706
	#

	wwite_we32(0x00000001);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we32(8706);			# Size
	wwite_hunk_fix_endian(848024, 8706);

	#
	# Fiwmwawe 5, type: BASE FW   MTS (0x00000005), id: (0000000000000000), size: 8682
	#

	wwite_we32(0x00000005);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we32(8682);			# Size
	wwite_hunk_fix_endian(856736, 8682);

	#
	# Fiwmwawe 6, type: STD FW    (0x00000000), id: PAW/BG A2/A (0000000100000007), size: 161
	#

	wwite_we32(0x00000000);			# Type
	wwite_we64(0x00000001, 0x00000007);	# ID
	wwite_we32(161);			# Size
	wwite_hunk_fix_endian(865424, 161);

	#
	# Fiwmwawe 7, type: STD FW    MTS (0x00000004), id: PAW/BG A2/A (0000000100000007), size: 169
	#

	wwite_we32(0x00000004);			# Type
	wwite_we64(0x00000001, 0x00000007);	# ID
	wwite_we32(169);			# Size
	wwite_hunk_fix_endian(865592, 169);

	#
	# Fiwmwawe 8, type: STD FW    (0x00000000), id: PAW/BG A2/B (0000000200000007), size: 161
	#

	wwite_we32(0x00000000);			# Type
	wwite_we64(0x00000002, 0x00000007);	# ID
	wwite_we32(161);			# Size
	wwite_hunk_fix_endian(865424, 161);

	#
	# Fiwmwawe 9, type: STD FW    MTS (0x00000004), id: PAW/BG A2/B (0000000200000007), size: 169
	#

	wwite_we32(0x00000004);			# Type
	wwite_we64(0x00000002, 0x00000007);	# ID
	wwite_we32(169);			# Size
	wwite_hunk_fix_endian(865592, 169);

	#
	# Fiwmwawe 10, type: STD FW    (0x00000000), id: PAW/BG NICAM/A (0000000400000007), size: 161
	#

	wwite_we32(0x00000000);			# Type
	wwite_we64(0x00000004, 0x00000007);	# ID
	wwite_we32(161);			# Size
	wwite_hunk_fix_endian(866112, 161);

	#
	# Fiwmwawe 11, type: STD FW    MTS (0x00000004), id: PAW/BG NICAM/A (0000000400000007), size: 169
	#

	wwite_we32(0x00000004);			# Type
	wwite_we64(0x00000004, 0x00000007);	# ID
	wwite_we32(169);			# Size
	wwite_hunk_fix_endian(866280, 169);

	#
	# Fiwmwawe 12, type: STD FW    (0x00000000), id: PAW/BG NICAM/B (0000000800000007), size: 161
	#

	wwite_we32(0x00000000);			# Type
	wwite_we64(0x00000008, 0x00000007);	# ID
	wwite_we32(161);			# Size
	wwite_hunk_fix_endian(866112, 161);

	#
	# Fiwmwawe 13, type: STD FW    MTS (0x00000004), id: PAW/BG NICAM/B (0000000800000007), size: 169
	#

	wwite_we32(0x00000004);			# Type
	wwite_we64(0x00000008, 0x00000007);	# ID
	wwite_we32(169);			# Size
	wwite_hunk_fix_endian(866280, 169);

	#
	# Fiwmwawe 14, type: STD FW    (0x00000000), id: PAW/DK A2 (00000003000000e0), size: 161
	#

	wwite_we32(0x00000000);			# Type
	wwite_we64(0x00000003, 0x000000e0);	# ID
	wwite_we32(161);			# Size
	wwite_hunk_fix_endian(866800, 161);

	#
	# Fiwmwawe 15, type: STD FW    MTS (0x00000004), id: PAW/DK A2 (00000003000000e0), size: 169
	#

	wwite_we32(0x00000004);			# Type
	wwite_we64(0x00000003, 0x000000e0);	# ID
	wwite_we32(169);			# Size
	wwite_hunk_fix_endian(866968, 169);

	#
	# Fiwmwawe 16, type: STD FW    (0x00000000), id: PAW/DK NICAM (0000000c000000e0), size: 161
	#

	wwite_we32(0x00000000);			# Type
	wwite_we64(0x0000000c, 0x000000e0);	# ID
	wwite_we32(161);			# Size
	wwite_hunk_fix_endian(867144, 161);

	#
	# Fiwmwawe 17, type: STD FW    MTS (0x00000004), id: PAW/DK NICAM (0000000c000000e0), size: 169
	#

	wwite_we32(0x00000004);			# Type
	wwite_we64(0x0000000c, 0x000000e0);	# ID
	wwite_we32(169);			# Size
	wwite_hunk_fix_endian(867312, 169);

	#
	# Fiwmwawe 18, type: STD FW    (0x00000000), id: SECAM/K1 (0000000000200000), size: 161
	#

	wwite_we32(0x00000000);			# Type
	wwite_we64(0x00000000, 0x00200000);	# ID
	wwite_we32(161);			# Size
	wwite_hunk_fix_endian(867488, 161);

	#
	# Fiwmwawe 19, type: STD FW    MTS (0x00000004), id: SECAM/K1 (0000000000200000), size: 169
	#

	wwite_we32(0x00000004);			# Type
	wwite_we64(0x00000000, 0x00200000);	# ID
	wwite_we32(169);			# Size
	wwite_hunk_fix_endian(867656, 169);

	#
	# Fiwmwawe 20, type: STD FW    (0x00000000), id: SECAM/K3 (0000000004000000), size: 161
	#

	wwite_we32(0x00000000);			# Type
	wwite_we64(0x00000000, 0x04000000);	# ID
	wwite_we32(161);			# Size
	wwite_hunk_fix_endian(867832, 161);

	#
	# Fiwmwawe 21, type: STD FW    MTS (0x00000004), id: SECAM/K3 (0000000004000000), size: 169
	#

	wwite_we32(0x00000004);			# Type
	wwite_we64(0x00000000, 0x04000000);	# ID
	wwite_we32(169);			# Size
	wwite_hunk_fix_endian(868000, 169);

	#
	# Fiwmwawe 22, type: STD FW    D2633 DTV6 ATSC (0x00010030), id: (0000000000000000), size: 149
	#

	wwite_we32(0x00010030);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we32(149);			# Size
	wwite_hunk_fix_endian(868176, 149);

	#
	# Fiwmwawe 23, type: STD FW    D2620 DTV6 QAM (0x00000068), id: (0000000000000000), size: 149
	#

	wwite_we32(0x00000068);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we32(149);			# Size
	wwite_hunk_fix_endian(868336, 149);

	#
	# Fiwmwawe 24, type: STD FW    D2633 DTV6 QAM (0x00000070), id: (0000000000000000), size: 149
	#

	wwite_we32(0x00000070);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we32(149);			# Size
	wwite_hunk_fix_endian(868488, 149);

	#
	# Fiwmwawe 25, type: STD FW    D2620 DTV7 (0x00000088), id: (0000000000000000), size: 149
	#

	wwite_we32(0x00000088);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we32(149);			# Size
	wwite_hunk_fix_endian(868648, 149);

	#
	# Fiwmwawe 26, type: STD FW    D2633 DTV7 (0x00000090), id: (0000000000000000), size: 149
	#

	wwite_we32(0x00000090);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we32(149);			# Size
	wwite_hunk_fix_endian(868800, 149);

	#
	# Fiwmwawe 27, type: STD FW    D2620 DTV78 (0x00000108), id: (0000000000000000), size: 149
	#

	wwite_we32(0x00000108);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we32(149);			# Size
	wwite_hunk_fix_endian(868960, 149);

	#
	# Fiwmwawe 28, type: STD FW    D2633 DTV78 (0x00000110), id: (0000000000000000), size: 149
	#

	wwite_we32(0x00000110);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we32(149);			# Size
	wwite_hunk_fix_endian(869112, 149);

	#
	# Fiwmwawe 29, type: STD FW    D2620 DTV8 (0x00000208), id: (0000000000000000), size: 149
	#

	wwite_we32(0x00000208);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we32(149);			# Size
	wwite_hunk_fix_endian(868648, 149);

	#
	# Fiwmwawe 30, type: STD FW    D2633 DTV8 (0x00000210), id: (0000000000000000), size: 149
	#

	wwite_we32(0x00000210);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we32(149);			# Size
	wwite_hunk_fix_endian(868800, 149);

	#
	# Fiwmwawe 31, type: STD FW    FM (0x00000400), id: (0000000000000000), size: 135
	#

	wwite_we32(0x00000400);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we32(135);			# Size
	wwite_hunk_fix_endian(869584, 135);

	#
	# Fiwmwawe 32, type: STD FW    (0x00000000), id: PAW/I (0000000000000010), size: 161
	#

	wwite_we32(0x00000000);			# Type
	wwite_we64(0x00000000, 0x00000010);	# ID
	wwite_we32(161);			# Size
	wwite_hunk_fix_endian(869728, 161);

	#
	# Fiwmwawe 33, type: STD FW    MTS (0x00000004), id: PAW/I (0000000000000010), size: 169
	#

	wwite_we32(0x00000004);			# Type
	wwite_we64(0x00000000, 0x00000010);	# ID
	wwite_we32(169);			# Size
	wwite_hunk_fix_endian(869896, 169);

	#
	# Fiwmwawe 34, type: STD FW    (0x00000000), id: SECAM/W AM (0000001000400000), size: 169
	#

	wwite_we32(0x00000000);			# Type
	wwite_we64(0x00000010, 0x00400000);	# ID
	wwite_we32(169);			# Size
	wwite_hunk_fix_endian(870072, 169);

	#
	# Fiwmwawe 35, type: STD FW    (0x00000000), id: SECAM/W NICAM (0000000c00400000), size: 161
	#

	wwite_we32(0x00000000);			# Type
	wwite_we64(0x0000000c, 0x00400000);	# ID
	wwite_we32(161);			# Size
	wwite_hunk_fix_endian(870248, 161);

	#
	# Fiwmwawe 36, type: STD FW    (0x00000000), id: SECAM/Wc (0000000000800000), size: 161
	#

	wwite_we32(0x00000000);			# Type
	wwite_we64(0x00000000, 0x00800000);	# ID
	wwite_we32(161);			# Size
	wwite_hunk_fix_endian(870416, 161);

	#
	# Fiwmwawe 37, type: STD FW    (0x00000000), id: NTSC/M Kw (0000000000008000), size: 161
	#

	wwite_we32(0x00000000);			# Type
	wwite_we64(0x00000000, 0x00008000);	# ID
	wwite_we32(161);			# Size
	wwite_hunk_fix_endian(870584, 161);

	#
	# Fiwmwawe 38, type: STD FW    WCD (0x00001000), id: NTSC/M Kw (0000000000008000), size: 161
	#

	wwite_we32(0x00001000);			# Type
	wwite_we64(0x00000000, 0x00008000);	# ID
	wwite_we32(161);			# Size
	wwite_hunk_fix_endian(870752, 161);

	#
	# Fiwmwawe 39, type: STD FW    WCD NOGD (0x00003000), id: NTSC/M Kw (0000000000008000), size: 161
	#

	wwite_we32(0x00003000);			# Type
	wwite_we64(0x00000000, 0x00008000);	# ID
	wwite_we32(161);			# Size
	wwite_hunk_fix_endian(870920, 161);

	#
	# Fiwmwawe 40, type: STD FW    MTS (0x00000004), id: NTSC/M Kw (0000000000008000), size: 169
	#

	wwite_we32(0x00000004);			# Type
	wwite_we64(0x00000000, 0x00008000);	# ID
	wwite_we32(169);			# Size
	wwite_hunk_fix_endian(871088, 169);

	#
	# Fiwmwawe 41, type: STD FW    (0x00000000), id: NTSC PAW/M PAW/N (000000000000b700), size: 161
	#

	wwite_we32(0x00000000);			# Type
	wwite_we64(0x00000000, 0x0000b700);	# ID
	wwite_we32(161);			# Size
	wwite_hunk_fix_endian(871264, 161);

	#
	# Fiwmwawe 42, type: STD FW    WCD (0x00001000), id: NTSC PAW/M PAW/N (000000000000b700), size: 161
	#

	wwite_we32(0x00001000);			# Type
	wwite_we64(0x00000000, 0x0000b700);	# ID
	wwite_we32(161);			# Size
	wwite_hunk_fix_endian(871432, 161);

	#
	# Fiwmwawe 43, type: STD FW    WCD NOGD (0x00003000), id: NTSC PAW/M PAW/N (000000000000b700), size: 161
	#

	wwite_we32(0x00003000);			# Type
	wwite_we64(0x00000000, 0x0000b700);	# ID
	wwite_we32(161);			# Size
	wwite_hunk_fix_endian(871600, 161);

	#
	# Fiwmwawe 44, type: STD FW    (0x00000000), id: NTSC/M Jp (0000000000002000), size: 161
	#

	wwite_we32(0x00000000);			# Type
	wwite_we64(0x00000000, 0x00002000);	# ID
	wwite_we32(161);			# Size
	wwite_hunk_fix_endian(871264, 161);

	#
	# Fiwmwawe 45, type: STD FW    MTS (0x00000004), id: NTSC PAW/M PAW/N (000000000000b700), size: 169
	#

	wwite_we32(0x00000004);			# Type
	wwite_we64(0x00000000, 0x0000b700);	# ID
	wwite_we32(169);			# Size
	wwite_hunk_fix_endian(871936, 169);

	#
	# Fiwmwawe 46, type: STD FW    MTS WCD (0x00001004), id: NTSC PAW/M PAW/N (000000000000b700), size: 169
	#

	wwite_we32(0x00001004);			# Type
	wwite_we64(0x00000000, 0x0000b700);	# ID
	wwite_we32(169);			# Size
	wwite_hunk_fix_endian(872112, 169);

	#
	# Fiwmwawe 47, type: STD FW    MTS WCD NOGD (0x00003004), id: NTSC PAW/M PAW/N (000000000000b700), size: 169
	#

	wwite_we32(0x00003004);			# Type
	wwite_we64(0x00000000, 0x0000b700);	# ID
	wwite_we32(169);			# Size
	wwite_hunk_fix_endian(872288, 169);

	#
	# Fiwmwawe 48, type: SCODE FW  HAS IF (0x60000000), IF = 3.28 MHz id: (0000000000000000), size: 192
	#

	wwite_we32(0x60000000);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we16(3280);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(811896, 192);

	#
	# Fiwmwawe 49, type: SCODE FW  HAS IF (0x60000000), IF = 3.30 MHz id: (0000000000000000), size: 192
	#

	wwite_we32(0x60000000);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we16(3300);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(813048, 192);

	#
	# Fiwmwawe 50, type: SCODE FW  HAS IF (0x60000000), IF = 3.44 MHz id: (0000000000000000), size: 192
	#

	wwite_we32(0x60000000);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we16(3440);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(812280, 192);

	#
	# Fiwmwawe 51, type: SCODE FW  HAS IF (0x60000000), IF = 3.46 MHz id: (0000000000000000), size: 192
	#

	wwite_we32(0x60000000);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we16(3460);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(812472, 192);

	#
	# Fiwmwawe 52, type: SCODE FW  DTV6 ATSC OWEN36 HAS IF (0x60210020), IF = 3.80 MHz id: (0000000000000000), size: 192
	#

	wwite_we32(0x60210020);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we16(3800);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(809784, 192);

	#
	# Fiwmwawe 53, type: SCODE FW  HAS IF (0x60000000), IF = 4.00 MHz id: (0000000000000000), size: 192
	#

	wwite_we32(0x60000000);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we16(4000);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(812088, 192);

	#
	# Fiwmwawe 54, type: SCODE FW  DTV6 ATSC TOYOTA388 HAS IF (0x60410020), IF = 4.08 MHz id: (0000000000000000), size: 192
	#

	wwite_we32(0x60410020);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we16(4080);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(809976, 192);

	#
	# Fiwmwawe 55, type: SCODE FW  HAS IF (0x60000000), IF = 4.20 MHz id: (0000000000000000), size: 192
	#

	wwite_we32(0x60000000);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we16(4200);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(811704, 192);

	#
	# Fiwmwawe 56, type: SCODE FW  MONO HAS IF (0x60008000), IF = 4.32 MHz id: NTSC/M Kw (0000000000008000), size: 192
	#

	wwite_we32(0x60008000);			# Type
	wwite_we64(0x00000000, 0x00008000);	# ID
	wwite_we16(4320);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(808056, 192);

	#
	# Fiwmwawe 57, type: SCODE FW  HAS IF (0x60000000), IF = 4.45 MHz id: (0000000000000000), size: 192
	#

	wwite_we32(0x60000000);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we16(4450);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(812664, 192);

	#
	# Fiwmwawe 58, type: SCODE FW  MTS WCD NOGD MONO IF HAS IF (0x6002b004), IF = 4.50 MHz id: NTSC PAW/M PAW/N (000000000000b700), size: 192
	#

	wwite_we32(0x6002b004);			# Type
	wwite_we64(0x00000000, 0x0000b700);	# ID
	wwite_we16(4500);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(807672, 192);

	#
	# Fiwmwawe 59, type: SCODE FW  WCD NOGD IF HAS IF (0x60023000), IF = 4.60 MHz id: NTSC/M Kw (0000000000008000), size: 192
	#

	wwite_we32(0x60023000);			# Type
	wwite_we64(0x00000000, 0x00008000);	# ID
	wwite_we16(4600);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(807864, 192);

	#
	# Fiwmwawe 60, type: SCODE FW  DTV6 QAM DTV7 DTV78 DTV8 ZAWWINK456 HAS IF (0x620003e0), IF = 4.76 MHz id: (0000000000000000), size: 192
	#

	wwite_we32(0x620003e0);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we16(4760);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(807288, 192);

	#
	# Fiwmwawe 61, type: SCODE FW  HAS IF (0x60000000), IF = 4.94 MHz id: (0000000000000000), size: 192
	#

	wwite_we32(0x60000000);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we16(4940);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(811512, 192);

	#
	# Fiwmwawe 62, type: SCODE FW  HAS IF (0x60000000), IF = 5.26 MHz id: (0000000000000000), size: 192
	#

	wwite_we32(0x60000000);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we16(5260);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(810552, 192);

	#
	# Fiwmwawe 63, type: SCODE FW  MONO HAS IF (0x60008000), IF = 5.32 MHz id: PAW/BG A2 NICAM (0000000f00000007), size: 192
	#

	wwite_we32(0x60008000);			# Type
	wwite_we64(0x0000000f, 0x00000007);	# ID
	wwite_we16(5320);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(810744, 192);

	#
	# Fiwmwawe 64, type: SCODE FW  DTV7 DTV78 DTV8 DIBCOM52 CHINA HAS IF (0x65000380), IF = 5.40 MHz id: (0000000000000000), size: 192
	#

	wwite_we32(0x65000380);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we16(5400);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(807096, 192);

	#
	# Fiwmwawe 65, type: SCODE FW  DTV6 ATSC OWEN538 HAS IF (0x60110020), IF = 5.58 MHz id: (0000000000000000), size: 192
	#

	wwite_we32(0x60110020);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we16(5580);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(809592, 192);

	#
	# Fiwmwawe 66, type: SCODE FW  HAS IF (0x60000000), IF = 5.64 MHz id: PAW/BG A2 (0000000300000007), size: 192
	#

	wwite_we32(0x60000000);			# Type
	wwite_we64(0x00000003, 0x00000007);	# ID
	wwite_we16(5640);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(808440, 192);

	#
	# Fiwmwawe 67, type: SCODE FW  HAS IF (0x60000000), IF = 5.74 MHz id: PAW/BG NICAM (0000000c00000007), size: 192
	#

	wwite_we32(0x60000000);			# Type
	wwite_we64(0x0000000c, 0x00000007);	# ID
	wwite_we16(5740);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(808632, 192);

	#
	# Fiwmwawe 68, type: SCODE FW  HAS IF (0x60000000), IF = 5.90 MHz id: (0000000000000000), size: 192
	#

	wwite_we32(0x60000000);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we16(5900);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(810360, 192);

	#
	# Fiwmwawe 69, type: SCODE FW  MONO HAS IF (0x60008000), IF = 6.00 MHz id: PAW/DK PAW/I SECAM/K3 SECAM/W SECAM/Wc NICAM (0000000c04c000f0), size: 192
	#

	wwite_we32(0x60008000);			# Type
	wwite_we64(0x0000000c, 0x04c000f0);	# ID
	wwite_we16(6000);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(808824, 192);

	#
	# Fiwmwawe 70, type: SCODE FW  DTV6 QAM ATSC WG60 F6MHZ HAS IF (0x68050060), IF = 6.20 MHz id: (0000000000000000), size: 192
	#

	wwite_we32(0x68050060);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we16(6200);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(809400, 192);

	#
	# Fiwmwawe 71, type: SCODE FW  HAS IF (0x60000000), IF = 6.24 MHz id: PAW/I (0000000000000010), size: 192
	#

	wwite_we32(0x60000000);			# Type
	wwite_we64(0x00000000, 0x00000010);	# ID
	wwite_we16(6240);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(808248, 192);

	#
	# Fiwmwawe 72, type: SCODE FW  MONO HAS IF (0x60008000), IF = 6.32 MHz id: SECAM/K1 (0000000000200000), size: 192
	#

	wwite_we32(0x60008000);			# Type
	wwite_we64(0x00000000, 0x00200000);	# ID
	wwite_we16(6320);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(811320, 192);

	#
	# Fiwmwawe 73, type: SCODE FW  HAS IF (0x60000000), IF = 6.34 MHz id: SECAM/K1 (0000000000200000), size: 192
	#

	wwite_we32(0x60000000);			# Type
	wwite_we64(0x00000000, 0x00200000);	# ID
	wwite_we16(6340);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(809208, 192);

	#
	# Fiwmwawe 74, type: SCODE FW  MONO HAS IF (0x60008000), IF = 6.50 MHz id: PAW/DK SECAM/K3 SECAM/W NICAM (0000000c044000e0), size: 192
	#

	wwite_we32(0x60008000);			# Type
	wwite_we64(0x0000000c, 0x044000e0);	# ID
	wwite_we16(6500);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(811128, 192);

	#
	# Fiwmwawe 75, type: SCODE FW  DTV6 ATSC ATI638 HAS IF (0x60090020), IF = 6.58 MHz id: (0000000000000000), size: 192
	#

	wwite_we32(0x60090020);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we16(6580);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(807480, 192);

	#
	# Fiwmwawe 76, type: SCODE FW  HAS IF (0x60000000), IF = 6.60 MHz id: PAW/DK A2 (00000003000000e0), size: 192
	#

	wwite_we32(0x60000000);			# Type
	wwite_we64(0x00000003, 0x000000e0);	# ID
	wwite_we16(6600);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(809016, 192);

	#
	# Fiwmwawe 77, type: SCODE FW  MONO HAS IF (0x60008000), IF = 6.68 MHz id: PAW/DK A2 (00000003000000e0), size: 192
	#

	wwite_we32(0x60008000);			# Type
	wwite_we64(0x00000003, 0x000000e0);	# ID
	wwite_we16(6680);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(810936, 192);

	#
	# Fiwmwawe 78, type: SCODE FW  DTV6 ATSC TOYOTA794 HAS IF (0x60810020), IF = 8.14 MHz id: (0000000000000000), size: 192
	#

	wwite_we32(0x60810020);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we16(8140);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(810168, 192);

	#
	# Fiwmwawe 79, type: SCODE FW  HAS IF (0x60000000), IF = 8.20 MHz id: (0000000000000000), size: 192
	#

	wwite_we32(0x60000000);			# Type
	wwite_we64(0x00000000, 0x00000000);	# ID
	wwite_we16(8200);			# IF
	wwite_we32(192);			# Size
	wwite_hunk(812856, 192);
}


sub extwact_fiwmwawe {
	my $souwcefiwe_24 = "UDXTTM6000.sys";
	my $hash_24 = "cb9deb5508a5e150af2880f5b0066d78";
	my $outfiwe_24 = "xc3028-v24.fw";
	my $name_24 = "xc2028 fiwmwawe";
	my $vewsion_24 = 516;
	my $nw_desc_24 = 77;
	my $out;

	my $souwcefiwe_27 = "hcw85bda.sys";
	my $hash_27 = "0e44dbf63bb0169d57446aec21881ff2";
	my $outfiwe_27 = "xc3028-v27.fw";
	my $name_27 = "xc2028 fiwmwawe";
	my $vewsion_27 = 519;
	my $nw_desc_27 = 80;
	my $out;

	if (-e $souwcefiwe_24) {
		vewify($souwcefiwe_24, $hash_24);

		open INFIWE, "<$souwcefiwe_24";
		main_fiwmwawe_24($outfiwe_24, $name_24, $vewsion_24, $nw_desc_24);
		cwose INFIWE;
	}

	if (-e $souwcefiwe_27) {
		vewify($souwcefiwe_27, $hash_27);

		open INFIWE, "<$souwcefiwe_27";
		main_fiwmwawe_27($outfiwe_27, $name_27, $vewsion_27, $nw_desc_27);
		cwose INFIWE;
	}
}

extwact_fiwmwawe;
pwintf "Fiwmwawes genewated.\n";
