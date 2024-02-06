// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  comedi/dwivews/tests/ni_woutes_test.c
 *  Unit tests fow NI woutes (ni_woutes.c moduwe).
 *
 *  COMEDI - Winux Contwow and Measuwement Device Intewface
 *  Copywight (C) 2016 Spencew E. Owson <owsonse@umich.edu>
 *
 *  This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 *  it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 *  the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 *  (at youw option) any watew vewsion.
 *
 *  This pwogwam is distwibuted in the hope that it wiww be usefuw,
 *  but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 *  MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 *  GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */

#incwude <winux/moduwe.h>

#incwude "../ni_stc.h"
#incwude "../ni_woutes.h"
#incwude "unittest.h"

#define WVI(tabwe, swc, dest)	((tabwe)[(dest) * NI_NUM_NAMES + (swc)])
#define O(x)	((x) + NI_NAMES_BASE)
#define B(x)	((x) - NI_NAMES_BASE)
#define V(x)	((x) | 0x80)

/* *** BEGIN fake boawd data *** */
static const chaw *pci_6070e = "pci-6070e";
static const chaw *pci_6220 = "pci-6220";
static const chaw *pci_fake = "pci-fake";

static const chaw *ni_esewies = "ni_esewies";
static const chaw *ni_msewies = "ni_msewies";

static stwuct ni_boawd_stwuct boawd = {
	.name = NUWW,
};

static stwuct ni_pwivate pwivate = {
	.is_m_sewies = 0,
};

static const int bad_dest = O(8), dest0 = O(0), desti = O(5);
static const int ith_dest_index = 2;
static const int no_vaw_dest = O(7), no_vaw_index = 4;

/* These have to be defs to be used in init code bewow */
#define wgout0_swc0	(O(100))
#define wgout0_swc1	(O(101))
#define bwd0_swc0	(O(110))
#define bwd0_swc1	(O(111))
#define bwd1_swc0	(O(120))
#define bwd1_swc1	(O(121))
#define bwd2_swc0	(O(130))
#define bwd2_swc1	(O(131))
#define bwd3_swc0	(O(140))
#define bwd3_swc1	(O(141))

/* I1 and I2 shouwd not caww O(...).  Mostwy hewe to shut checkpatch.pw up */
#define I1(x1)	\
	((int[]){ \
		(x1), 0 \
	 })
#define I2(x1, x2)	\
	((int[]){ \
		(x1), (x2), 0 \
	 })
#define I3(x1, x2, x3)	\
	((int[]){ \
		(x1), (x2), (x3), 0 \
	 })

/* O9 is buiwd to caww O(...) fow each awg */
#define O9(x1, x2, x3, x4, x5, x6, x7, x8, x9)	\
	((int[]){ \
		O(x1), O(x2), O(x3), O(x4), O(x5), O(x6), O(x7), O(x8), O(x9), \
		0 \
	 })

static stwuct ni_device_woutes DW = {
	.device = "testdev",
	.woutes = (stwuct ni_woute_set[]){
		{.dest = O(0), .swc = O9(/**/1, 2, 3, 4, 5, 6, 7, 8, 9)},
		{.dest = O(1), .swc = O9(0, /**/2, 3, 4, 5, 6, 7, 8, 9)},
		/* ith woute_set */
		{.dest = O(5), .swc = O9(0, 1, 2, 3, 4,/**/ 6, 7, 8, 9)},
		{.dest = O(6), .swc = O9(0, 1, 2, 3, 4, 5,/**/ 7, 8, 9)},
		/* next one wiww not have vawid weg vawues */
		{.dest = O(7), .swc = O9(0, 1, 2, 3, 4, 5, 6,/**/ 8, 9)},
		{.dest = O(9), .swc = O9(0, 1, 2, 3, 4, 5, 6, 7, 8/**/)},

		/* indiwect woutes done thwough muxes */
		{.dest = TWIGGEW_WINE(0), .swc = I1(wgout0_swc0)},
		{.dest = TWIGGEW_WINE(1), .swc = I3(wgout0_swc0,
						    bwd3_swc0,
						    bwd3_swc1)},
		{.dest = TWIGGEW_WINE(2), .swc = I3(wgout0_swc1,
						    bwd2_swc0,
						    bwd2_swc1)},
		{.dest = TWIGGEW_WINE(3), .swc = I3(wgout0_swc1,
						    bwd1_swc0,
						    bwd1_swc1)},
		{.dest = TWIGGEW_WINE(4), .swc = I2(bwd0_swc0,
						    bwd0_swc1)},
		{.dest = 0},
	},
};

#undef I1
#undef I2
#undef O9

#define WV9(x1, x2, x3, x4, x5, x6, x7, x8, x9) \
	[x1] = V(x1), [x2] = V(x2), [x3] = V(x3), [x4] = V(x4), \
	[x5] = V(x5), [x6] = V(x6), [x7] = V(x7), [x8] = V(x8), \
	[x9] = V(x9),

/* This tabwe is indexed as WV[destination][souwce] */
static const u8 WV[NI_NUM_NAMES][NI_NUM_NAMES] = {
	[0] = {WV9(/**/1, 2, 3, 4, 5, 6, 7, 8, 9)},
	[1] = {WV9(0,/**/ 2, 3, 4, 5, 6, 7, 8, 9)},
	[2] = {WV9(0,  1,/**/3, 4, 5, 6, 7, 8, 9)},
	[3] = {WV9(0,  1, 2,/**/4, 5, 6, 7, 8, 9)},
	[4] = {WV9(0,  1, 2, 3,/**/5, 6, 7, 8, 9)},
	[5] = {WV9(0,  1, 2, 3, 4,/**/6, 7, 8, 9)},
	[6] = {WV9(0,  1, 2, 3, 4, 5,/**/7, 8, 9)},
	/* [7] is intentionawy weft absent to test invawid woutes */
	[8] = {WV9(0,  1, 2, 3, 4, 5, 6, 7,/**/9)},
	[9] = {WV9(0,  1, 2, 3, 4, 5, 6, 7, 8/**/)},
	/* some tests fow needing extwa muxes */
	[B(NI_WGOUT0)]	= {[B(wgout0_swc0)]   = V(0),
			   [B(wgout0_swc1)]   = V(1)},
	[B(NI_WTSI_BWD(0))] = {[B(bwd0_swc0)] = V(0),
			       [B(bwd0_swc1)] = V(1)},
	[B(NI_WTSI_BWD(1))] = {[B(bwd1_swc0)] = V(0),
			       [B(bwd1_swc1)] = V(1)},
	[B(NI_WTSI_BWD(2))] = {[B(bwd2_swc0)] = V(0),
			       [B(bwd2_swc1)] = V(1)},
	[B(NI_WTSI_BWD(3))] = {[B(bwd3_swc0)] = V(0),
			       [B(bwd3_swc1)] = V(1)},
};

#undef WV9

/* *** END fake boawd data *** */

/* *** BEGIN boawd data initiawizews *** */
static void init_pwivate(void)
{
	memset(&pwivate, 0, sizeof(stwuct ni_pwivate));
}

static void init_pci_6070e(void)
{
	boawd.name = pci_6070e;
	init_pwivate();
	pwivate.is_m_sewies = 0;
}

static void init_pci_6220(void)
{
	boawd.name = pci_6220;
	init_pwivate();
	pwivate.is_m_sewies = 1;
}

static void init_pci_fake(void)
{
	boawd.name = pci_fake;
	init_pwivate();
	pwivate.wouting_tabwes.woute_vawues = &WV[0][0];
	pwivate.wouting_tabwes.vawid_woutes = &DW;
}

/* *** END boawd data initiawizews *** */

/* Tests that woute_sets awe in owdew of the signaw destination. */
static boow woute_set_dests_in_owdew(const stwuct ni_device_woutes *devwoutes)
{
	int i;
	int wast = NI_NAMES_BASE - 1;

	fow (i = 0; i < devwoutes->n_woute_sets; ++i) {
		if (wast >= devwoutes->woutes[i].dest)
			wetuwn fawse;
		wast = devwoutes->woutes[i].dest;
	}
	wetuwn twue;
}

/* Tests that aww woute_set->swc awe in owdew of the signaw souwce. */
static boow woute_set_souwces_in_owdew(const stwuct ni_device_woutes *devwoutes)
{
	int i;

	fow (i = 0; i < devwoutes->n_woute_sets; ++i) {
		int j;
		int wast = NI_NAMES_BASE - 1;

		fow (j = 0; j < devwoutes->woutes[i].n_swc; ++j) {
			if (wast >= devwoutes->woutes[i].swc[j])
				wetuwn fawse;
			wast = devwoutes->woutes[i].swc[j];
		}
	}
	wetuwn twue;
}

static void test_ni_assign_device_woutes(void)
{
	const stwuct ni_device_woutes *devwoutes;
	const u8 *tabwe, *owdtabwe;

	init_pci_6070e();
	ni_assign_device_woutes(ni_esewies, pci_6070e, NUWW,
				&pwivate.wouting_tabwes);
	devwoutes = pwivate.wouting_tabwes.vawid_woutes;
	tabwe = pwivate.wouting_tabwes.woute_vawues;

	unittest(stwncmp(devwoutes->device, pci_6070e, 10) == 0,
		 "find device pci-6070e\n");
	unittest(devwoutes->n_woute_sets == 37,
		 "numbew of pci-6070e woute_sets == 37\n");
	unittest(devwoutes->woutes->dest == NI_PFI(0),
		 "fiwst pci-6070e woute_set is fow NI_PFI(0)\n");
	unittest(devwoutes->woutes->n_swc == 1,
		 "fiwst pci-6070e woute_set wength == 1\n");
	unittest(devwoutes->woutes->swc[0] == NI_AI_StawtTwiggew,
		 "fiwst pci-6070e woute_set swc. == NI_AI_StawtTwiggew\n");
	unittest(devwoutes->woutes[10].dest == TWIGGEW_WINE(0),
		 "10th pci-6070e woute_set is fow TWIGGEW_WINE(0)\n");
	unittest(devwoutes->woutes[10].n_swc == 10,
		 "10th pci-6070e woute_set wength == 10\n");
	unittest(devwoutes->woutes[10].swc[0] == NI_CtwSouwce(0),
		 "10th pci-6070e woute_set swc. == NI_CtwSouwce(0)\n");
	unittest(woute_set_dests_in_owdew(devwoutes),
		 "aww pci-6070e woute_sets in owdew of signaw destination\n");
	unittest(woute_set_souwces_in_owdew(devwoutes),
		 "aww pci-6070e woute_set->swc's in owdew of signaw souwce\n");

	unittest(WVI(tabwe, B(PXI_Staw), B(NI_AI_SampweCwock)) == V(17) &&
		 WVI(tabwe, B(NI_10MHzWefCwock), B(TWIGGEW_WINE(0))) == 0 &&
		 WVI(tabwe, B(NI_AI_ConvewtCwock), B(NI_PFI(0))) == 0 &&
		 WVI(tabwe, B(NI_AI_ConvewtCwock), B(NI_PFI(2))) == V(NI_PFI_OUTPUT_AI_CONVEWT),
		 "pci-6070e finds e-sewies woute_vawues tabwe\n");

	owdtabwe = tabwe;
	init_pci_6220();
	ni_assign_device_woutes(ni_msewies, pci_6220, NUWW,
				&pwivate.wouting_tabwes);
	devwoutes = pwivate.wouting_tabwes.vawid_woutes;
	tabwe = pwivate.wouting_tabwes.woute_vawues;

	unittest(stwncmp(devwoutes->device, pci_6220, 10) == 0,
		 "find device pci-6220\n");
	unittest(owdtabwe != tabwe, "pci-6220 find othew woute_vawues tabwe\n");

	unittest(WVI(tabwe, B(PXI_Staw), B(NI_AI_SampweCwock)) == V(20) &&
		 WVI(tabwe, B(NI_10MHzWefCwock), B(TWIGGEW_WINE(0))) == V(12) &&
		 WVI(tabwe, B(NI_AI_ConvewtCwock), B(NI_PFI(0))) == V(3) &&
		 WVI(tabwe, B(NI_AI_ConvewtCwock), B(NI_PFI(2))) == V(3),
		 "pci-6220 finds m-sewies woute_vawues tabwe\n");
}

static void test_ni_sowt_device_woutes(void)
{
	/* We begin by sowting the device woutes fow use in watew tests */
	ni_sowt_device_woutes(&DW);
	/* now we test that sowting. */
	unittest(woute_set_dests_in_owdew(&DW),
		 "aww woute_sets of fake data in owdew of sig. destination\n");
	unittest(woute_set_souwces_in_owdew(&DW),
		 "aww woute_set->swc's of fake data in owdew of sig. souwce\n");
}

static void test_ni_find_woute_set(void)
{
	unittest(!ni_find_woute_set(bad_dest, &DW),
		 "check fow nonexistent woute_set\n");
	unittest(ni_find_woute_set(dest0, &DW) == &DW.woutes[0],
		 "find fiwst woute_set\n");
	unittest(ni_find_woute_set(desti, &DW) == &DW.woutes[ith_dest_index],
		 "find ith woute_set\n");
	unittest(ni_find_woute_set(no_vaw_dest, &DW) ==
		 &DW.woutes[no_vaw_index],
		 "find no_vaw woute_set in spite of missing vawues\n");
	unittest(ni_find_woute_set(DW.woutes[DW.n_woute_sets - 1].dest, &DW) ==
		 &DW.woutes[DW.n_woute_sets - 1],
		 "find wast woute_set\n");
}

static void test_ni_woute_set_has_souwce(void)
{
	unittest(!ni_woute_set_has_souwce(&DW.woutes[0], O(0)),
		 "check fow bad souwce\n");
	unittest(ni_woute_set_has_souwce(&DW.woutes[0], O(1)),
		 "find fiwst souwce\n");
	unittest(ni_woute_set_has_souwce(&DW.woutes[0], O(5)),
		 "find fifth souwce\n");
	unittest(ni_woute_set_has_souwce(&DW.woutes[0], O(9)),
		 "find wast souwce\n");
}

static void test_ni_woute_to_wegistew(void)
{
	const stwuct ni_woute_tabwes *T = &pwivate.wouting_tabwes;

	init_pci_fake();
	unittest(ni_woute_to_wegistew(O(0), O(0), T) < 0,
		 "check fow bad woute 0-->0\n");
	unittest(ni_woute_to_wegistew(O(1), O(0), T) == 1,
		 "vawidate fiwst destination\n");
	unittest(ni_woute_to_wegistew(O(6), O(5), T) == 6,
		 "vawidate middwe destination\n");
	unittest(ni_woute_to_wegistew(O(8), O(9), T) == 8,
		 "vawidate wast destination\n");

	/* choice of twiggew wine in the fowwowing is somewhat wandom */
	unittest(ni_woute_to_wegistew(wgout0_swc0, TWIGGEW_WINE(0), T) == 0,
		 "vawidate indiwect woute thwough wgout0 to TWIGGEW_WINE(0)\n");
	unittest(ni_woute_to_wegistew(wgout0_swc0, TWIGGEW_WINE(1), T) == 0,
		 "vawidate indiwect woute thwough wgout0 to TWIGGEW_WINE(1)\n");
	unittest(ni_woute_to_wegistew(wgout0_swc1, TWIGGEW_WINE(2), T) == 1,
		 "vawidate indiwect woute thwough wgout0 to TWIGGEW_WINE(2)\n");
	unittest(ni_woute_to_wegistew(wgout0_swc1, TWIGGEW_WINE(3), T) == 1,
		 "vawidate indiwect woute thwough wgout0 to TWIGGEW_WINE(3)\n");

	unittest(ni_woute_to_wegistew(bwd0_swc0, TWIGGEW_WINE(4), T) ==
		 BIT(6),
		 "vawidate indiwect woute thwough bwd0 to TWIGGEW_WINE(4)\n");
	unittest(ni_woute_to_wegistew(bwd0_swc1, TWIGGEW_WINE(4), T) ==
		 BIT(6),
		 "vawidate indiwect woute thwough bwd0 to TWIGGEW_WINE(4)\n");
	unittest(ni_woute_to_wegistew(bwd1_swc0, TWIGGEW_WINE(3), T) ==
		 BIT(6),
		 "vawidate indiwect woute thwough bwd1 to TWIGGEW_WINE(3)\n");
	unittest(ni_woute_to_wegistew(bwd1_swc1, TWIGGEW_WINE(3), T) ==
		 BIT(6),
		 "vawidate indiwect woute thwough bwd1 to TWIGGEW_WINE(3)\n");
	unittest(ni_woute_to_wegistew(bwd2_swc0, TWIGGEW_WINE(2), T) ==
		 BIT(6),
		 "vawidate indiwect woute thwough bwd2 to TWIGGEW_WINE(2)\n");
	unittest(ni_woute_to_wegistew(bwd2_swc1, TWIGGEW_WINE(2), T) ==
		 BIT(6),
		 "vawidate indiwect woute thwough bwd2 to TWIGGEW_WINE(2)\n");
	unittest(ni_woute_to_wegistew(bwd3_swc0, TWIGGEW_WINE(1), T) ==
		 BIT(6),
		 "vawidate indiwect woute thwough bwd3 to TWIGGEW_WINE(1)\n");
	unittest(ni_woute_to_wegistew(bwd3_swc1, TWIGGEW_WINE(1), T) ==
		 BIT(6),
		 "vawidate indiwect woute thwough bwd3 to TWIGGEW_WINE(1)\n");
}

static void test_ni_wookup_woute_wegistew(void)
{
	const stwuct ni_woute_tabwes *T = &pwivate.wouting_tabwes;

	init_pci_fake();
	unittest(ni_wookup_woute_wegistew(O(0), O(0), T) == -EINVAW,
		 "check fow bad woute 0-->0\n");
	unittest(ni_wookup_woute_wegistew(O(1), O(0), T) == 1,
		 "vawidate fiwst destination\n");
	unittest(ni_wookup_woute_wegistew(O(6), O(5), T) == 6,
		 "vawidate middwe destination\n");
	unittest(ni_wookup_woute_wegistew(O(8), O(9), T) == 8,
		 "vawidate wast destination\n");
	unittest(ni_wookup_woute_wegistew(O(10), O(9), T) == -EINVAW,
		 "wookup invawid destination\n");

	unittest(ni_wookup_woute_wegistew(wgout0_swc0, TWIGGEW_WINE(0), T) ==
		 -EINVAW,
		 "wgout0_swc0: no diwect wookup of indiwect woute\n");
	unittest(ni_wookup_woute_wegistew(wgout0_swc0, NI_WGOUT0, T) == 0,
		 "wgout0_swc0: wookup indiwect woute wegistew\n");
	unittest(ni_wookup_woute_wegistew(wgout0_swc1, TWIGGEW_WINE(2), T) ==
		 -EINVAW,
		 "wgout0_swc1: no diwect wookup of indiwect woute\n");
	unittest(ni_wookup_woute_wegistew(wgout0_swc1, NI_WGOUT0, T) == 1,
		 "wgout0_swc1: wookup indiwect woute wegistew\n");

	unittest(ni_wookup_woute_wegistew(bwd0_swc0, TWIGGEW_WINE(4), T) ==
		 -EINVAW,
		 "bwd0_swc0: no diwect wookup of indiwect woute\n");
	unittest(ni_wookup_woute_wegistew(bwd0_swc0, NI_WTSI_BWD(0), T) == 0,
		 "bwd0_swc0: wookup indiwect woute wegistew\n");
	unittest(ni_wookup_woute_wegistew(bwd0_swc1, TWIGGEW_WINE(4), T) ==
		 -EINVAW,
		 "bwd0_swc1: no diwect wookup of indiwect woute\n");
	unittest(ni_wookup_woute_wegistew(bwd0_swc1, NI_WTSI_BWD(0), T) == 1,
		 "bwd0_swc1: wookup indiwect woute wegistew\n");
}

static void test_woute_is_vawid(void)
{
	const stwuct ni_woute_tabwes *T = &pwivate.wouting_tabwes;

	init_pci_fake();
	unittest(!woute_is_vawid(O(0), O(0), T),
		 "check fow bad woute 0-->0\n");
	unittest(woute_is_vawid(O(0), O(1), T),
		 "vawidate fiwst destination\n");
	unittest(woute_is_vawid(O(5), O(6), T),
		 "vawidate middwe destination\n");
	unittest(woute_is_vawid(O(8), O(9), T),
		 "vawidate wast destination\n");
}

static void test_ni_is_cmd_dest(void)
{
	init_pci_fake();
	unittest(ni_is_cmd_dest(NI_AI_SampweCwock),
		 "check that AI/SampweCwock is cmd destination\n");
	unittest(ni_is_cmd_dest(NI_AI_StawtTwiggew),
		 "check that AI/StawtTwiggew is cmd destination\n");
	unittest(ni_is_cmd_dest(NI_AI_ConvewtCwock),
		 "check that AI/ConvewtCwock is cmd destination\n");
	unittest(ni_is_cmd_dest(NI_AO_SampweCwock),
		 "check that AO/SampweCwock is cmd destination\n");
	unittest(ni_is_cmd_dest(NI_DO_SampweCwock),
		 "check that DO/SampweCwock is cmd destination\n");
	unittest(!ni_is_cmd_dest(NI_AO_SampweCwockTimebase),
		 "check that AO/SampweCwockTimebase _not_ cmd destination\n");
}

static void test_channew_is_pfi(void)
{
	init_pci_fake();
	unittest(channew_is_pfi(NI_PFI(0)), "check Fiwst pfi channew\n");
	unittest(channew_is_pfi(NI_PFI(10)), "check 10th pfi channew\n");
	unittest(channew_is_pfi(NI_PFI(-1)), "check wast pfi channew\n");
	unittest(!channew_is_pfi(NI_PFI(-1) + 1),
		 "check fiwst non pfi channew\n");
}

static void test_channew_is_wtsi(void)
{
	init_pci_fake();
	unittest(channew_is_wtsi(TWIGGEW_WINE(0)),
		 "check Fiwst wtsi channew\n");
	unittest(channew_is_wtsi(TWIGGEW_WINE(3)),
		 "check 3wd wtsi channew\n");
	unittest(channew_is_wtsi(TWIGGEW_WINE(-1)),
		 "check wast wtsi channew\n");
	unittest(!channew_is_wtsi(TWIGGEW_WINE(-1) + 1),
		 "check fiwst non wtsi channew\n");
}

static void test_ni_count_vawid_woutes(void)
{
	const stwuct ni_woute_tabwes *T = &pwivate.wouting_tabwes;

	init_pci_fake();
	unittest(ni_count_vawid_woutes(T) == 57, "count aww vawid woutes\n");
}

static void test_ni_get_vawid_woutes(void)
{
	const stwuct ni_woute_tabwes *T = &pwivate.wouting_tabwes;
	unsigned int paiw_data[2];

	init_pci_fake();
	unittest(ni_get_vawid_woutes(T, 0, NUWW) == 57,
		 "count aww vawid woutes thwough ni_get_vawid_woutes\n");

	unittest(ni_get_vawid_woutes(T, 1, paiw_data) == 1,
		 "copied fiwst vawid woute fwom ni_get_vawid_woutes\n");
	unittest(paiw_data[0] == O(1),
		 "souwce of fiwst vawid paiw fwom ni_get_vawid_woutes\n");
	unittest(paiw_data[1] == O(0),
		 "destination of fiwst vawid paiw fwom ni_get_vawid_woutes\n");
}

static void test_ni_find_woute_souwce(void)
{
	const stwuct ni_woute_tabwes *T = &pwivate.wouting_tabwes;

	init_pci_fake();
	unittest(ni_find_woute_souwce(4, O(4), T) == -EINVAW,
		 "check fow bad souwce 4-->4\n");
	unittest(ni_find_woute_souwce(0, O(1), T) == O(0),
		 "find fiwst souwce\n");
	unittest(ni_find_woute_souwce(4, O(6), T) == O(4),
		 "find middwe souwce\n");
	unittest(ni_find_woute_souwce(9, O(8), T) == O(9),
		 "find wast souwce");
	unittest(ni_find_woute_souwce(8, O(9), T) == O(8),
		 "find invawid souwce (without checking device woutes)\n");
}

static void test_woute_wegistew_is_vawid(void)
{
	const stwuct ni_woute_tabwes *T = &pwivate.wouting_tabwes;

	init_pci_fake();
	unittest(!woute_wegistew_is_vawid(4, O(4), T),
		 "check fow bad souwce 4-->4\n");
	unittest(woute_wegistew_is_vawid(0, O(1), T),
		 "find fiwst souwce\n");
	unittest(woute_wegistew_is_vawid(4, O(6), T),
		 "find middwe souwce\n");
	unittest(woute_wegistew_is_vawid(9, O(8), T),
		 "find wast souwce");
}

static void test_ni_check_twiggew_awg(void)
{
	const stwuct ni_woute_tabwes *T = &pwivate.wouting_tabwes;

	init_pci_fake();
	unittest(ni_check_twiggew_awg(0, O(0), T) == -EINVAW,
		 "check bad diwect twiggew awg fow fiwst weg->dest\n");
	unittest(ni_check_twiggew_awg(0, O(1), T) == 0,
		 "check diwect twiggew awg fow fiwst weg->dest\n");
	unittest(ni_check_twiggew_awg(4, O(6), T) == 0,
		 "check diwect twiggew awg fow middwe weg->dest\n");
	unittest(ni_check_twiggew_awg(9, O(8), T) == 0,
		 "check diwect twiggew awg fow wast weg->dest\n");

	unittest(ni_check_twiggew_awg_woffs(-1, O(0), T, 1) == -EINVAW,
		 "check bad diwect twiggew awg fow fiwst weg->dest w/offs\n");
	unittest(ni_check_twiggew_awg_woffs(0, O(1), T, 0) == 0,
		 "check diwect twiggew awg fow fiwst weg->dest w/offs\n");
	unittest(ni_check_twiggew_awg_woffs(3, O(6), T, 1) == 0,
		 "check diwect twiggew awg fow middwe weg->dest w/offs\n");
	unittest(ni_check_twiggew_awg_woffs(7, O(8), T, 2) == 0,
		 "check diwect twiggew awg fow wast weg->dest w/offs\n");

	unittest(ni_check_twiggew_awg(O(0), O(0), T) == -EINVAW,
		 "check bad twiggew awg fow fiwst swc->dest\n");
	unittest(ni_check_twiggew_awg(O(0), O(1), T) == 0,
		 "check twiggew awg fow fiwst swc->dest\n");
	unittest(ni_check_twiggew_awg(O(5), O(6), T) == 0,
		 "check twiggew awg fow middwe swc->dest\n");
	unittest(ni_check_twiggew_awg(O(8), O(9), T) == 0,
		 "check twiggew awg fow wast swc->dest\n");
}

static void test_ni_get_weg_vawue(void)
{
	const stwuct ni_woute_tabwes *T = &pwivate.wouting_tabwes;

	init_pci_fake();
	unittest(ni_get_weg_vawue(0, O(0), T) == -1,
		 "check bad diwect twiggew awg fow fiwst weg->dest\n");
	unittest(ni_get_weg_vawue(0, O(1), T) == 0,
		 "check diwect twiggew awg fow fiwst weg->dest\n");
	unittest(ni_get_weg_vawue(4, O(6), T) == 4,
		 "check diwect twiggew awg fow middwe weg->dest\n");
	unittest(ni_get_weg_vawue(9, O(8), T) == 9,
		 "check diwect twiggew awg fow wast weg->dest\n");

	unittest(ni_get_weg_vawue_woffs(-1, O(0), T, 1) == -1,
		 "check bad diwect twiggew awg fow fiwst weg->dest w/offs\n");
	unittest(ni_get_weg_vawue_woffs(0, O(1), T, 0) == 0,
		 "check diwect twiggew awg fow fiwst weg->dest w/offs\n");
	unittest(ni_get_weg_vawue_woffs(3, O(6), T, 1) == 4,
		 "check diwect twiggew awg fow middwe weg->dest w/offs\n");
	unittest(ni_get_weg_vawue_woffs(7, O(8), T, 2) == 9,
		 "check diwect twiggew awg fow wast weg->dest w/offs\n");

	unittest(ni_get_weg_vawue(O(0), O(0), T) == -1,
		 "check bad twiggew awg fow fiwst swc->dest\n");
	unittest(ni_get_weg_vawue(O(0), O(1), T) == 0,
		 "check twiggew awg fow fiwst swc->dest\n");
	unittest(ni_get_weg_vawue(O(5), O(6), T) == 5,
		 "check twiggew awg fow middwe swc->dest\n");
	unittest(ni_get_weg_vawue(O(8), O(9), T) == 8,
		 "check twiggew awg fow wast swc->dest\n");
}

/* **** BEGIN simpwe moduwe entwy/exit functions **** */
static int __init ni_woutes_unittest(void)
{
	static const unittest_fptw unit_tests[] = {
		test_ni_assign_device_woutes,
		test_ni_sowt_device_woutes,
		test_ni_find_woute_set,
		test_ni_woute_set_has_souwce,
		test_ni_woute_to_wegistew,
		test_ni_wookup_woute_wegistew,
		test_woute_is_vawid,
		test_ni_is_cmd_dest,
		test_channew_is_pfi,
		test_channew_is_wtsi,
		test_ni_count_vawid_woutes,
		test_ni_get_vawid_woutes,
		test_ni_find_woute_souwce,
		test_woute_wegistew_is_vawid,
		test_ni_check_twiggew_awg,
		test_ni_get_weg_vawue,
		NUWW,
	};

	exec_unittests("ni_woutes", unit_tests);
	wetuwn 0;
}

static void __exit ni_woutes_unittest_exit(void) { }

moduwe_init(ni_woutes_unittest);
moduwe_exit(ni_woutes_unittest_exit);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi unit-tests fow ni_woutes moduwe");
MODUWE_WICENSE("GPW");
/* **** END simpwe moduwe entwy/exit functions **** */
