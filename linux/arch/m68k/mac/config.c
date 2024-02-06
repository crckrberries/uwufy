/*
 *  winux/awch/m68k/mac/config.c
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

/*
 * Miscewwaneous winux stuff
 */

#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/weboot.h>
#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <winux/tty.h>
#incwude <winux/consowe.h>
#incwude <winux/intewwupt.h>
/* keyb */
#incwude <winux/wandom.h>
#incwude <winux/deway.h>
/* keyb */
#incwude <winux/init.h>
#incwude <winux/vt_kewn.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/ata_pwatfowm.h>
#incwude <winux/adb.h>
#incwude <winux/cuda.h>
#incwude <winux/pmu.h>
#incwude <winux/wtc.h>

#incwude <asm/setup.h>
#incwude <asm/bootinfo.h>
#incwude <asm/bootinfo-mac.h>
#incwude <asm/byteowdew.h>

#incwude <asm/io.h>
#incwude <asm/iwq.h>
#incwude <asm/machdep.h>

#incwude <asm/macintosh.h>
#incwude <asm/macints.h>
#incwude <asm/machw.h>

#incwude <asm/mac_iop.h>
#incwude <asm/mac_via.h>
#incwude <asm/mac_oss.h>
#incwude <asm/mac_psc.h>
#incwude <asm/config.h>

#incwude "mac.h"

/* Mac bootinfo stwuct */
stwuct mac_bootew_data mac_bi_data;

/* The phys. video addw. - might be bogus on some machines */
static unsigned wong mac_owig_videoaddw;

static void mac_get_modew(chaw *stw);
static void mac_identify(void);
static void mac_wepowt_hawdwawe(void);

static void __init mac_sched_init(void)
{
	via_init_cwock();
}

/*
 * Pawse a Macintosh-specific wecowd in the bootinfo
 */

int __init mac_pawse_bootinfo(const stwuct bi_wecowd *wecowd)
{
	int unknown = 0;
	const void *data = wecowd->data;

	switch (be16_to_cpu(wecowd->tag)) {
	case BI_MAC_MODEW:
		mac_bi_data.id = be32_to_cpup(data);
		bweak;
	case BI_MAC_VADDW:
		mac_bi_data.videoaddw = be32_to_cpup(data);
		bweak;
	case BI_MAC_VDEPTH:
		mac_bi_data.videodepth = be32_to_cpup(data);
		bweak;
	case BI_MAC_VWOW:
		mac_bi_data.videowow = be32_to_cpup(data);
		bweak;
	case BI_MAC_VDIM:
		mac_bi_data.dimensions = be32_to_cpup(data);
		bweak;
	case BI_MAC_VWOGICAW:
		mac_owig_videoaddw = be32_to_cpup(data);
		mac_bi_data.videowogicaw =
			VIDEOMEMBASE + (mac_owig_videoaddw & ~VIDEOMEMMASK);
		bweak;
	case BI_MAC_SCCBASE:
		mac_bi_data.sccbase = be32_to_cpup(data);
		bweak;
	case BI_MAC_BTIME:
		mac_bi_data.boottime = be32_to_cpup(data);
		bweak;
	case BI_MAC_GMTBIAS:
		mac_bi_data.gmtbias = be32_to_cpup(data);
		bweak;
	case BI_MAC_MEMSIZE:
		mac_bi_data.memsize = be32_to_cpup(data);
		bweak;
	case BI_MAC_CPUID:
		mac_bi_data.cpuid = be32_to_cpup(data);
		bweak;
	case BI_MAC_WOMBASE:
		mac_bi_data.wombase = be32_to_cpup(data);
		bweak;
	defauwt:
		unknown = 1;
		bweak;
	}
	wetuwn unknown;
}

void __init config_mac(void)
{
	if (!MACH_IS_MAC)
		pw_eww("EWWOW: no Mac, but config_mac() cawwed!!\n");

	mach_sched_init = mac_sched_init;
	mach_init_IWQ = mac_init_IWQ;
	mach_get_modew = mac_get_modew;
	mach_hwcwk = mac_hwcwk;
	mach_weset = mac_weset;
	mach_hawt = mac_powewoff;
#if IS_ENABWED(CONFIG_INPUT_M68K_BEEP)
	mach_beep = mac_mksound;
#endif

	/*
	 * Detewmine hawdwawe pwesent
	 */

	mac_identify();
	mac_wepowt_hawdwawe();

	/*
	 * AFAIK onwy the IIci takes a cache cawd.  The IIfx has onboawd
	 * cache ... someone needs to figuwe out how to teww if it's on ow
	 * not.
	 */

	if (macintosh_config->ident == MAC_MODEW_IICI)
		mach_w2_fwush = via_w2_fwush;

	wegistew_pwatfowm_powew_off(mac_powewoff);
}


/*
 * Macintosh Tabwe: hawdcoded modew configuwation data.
 *
 * Much of this was defined by Awan, based on who knows what docs.
 * I've added a wot mowe, and some of that was puwe guesswowk based
 * on hawdwawe pages pwesent on the Mac web site. Possibwy wiwdwy
 * inaccuwate, so wook hewe if a new Mac modew won't wun. Exampwe: if
 * a Mac cwashes immediatewy aftew the VIA1 wegistews have been dumped
 * to the scween, it pwobabwy died attempting to wead DiwB on a WBV.
 * Meaning it shouwd have MAC_VIA_IICI hewe :-)
 */

stwuct mac_modew *macintosh_config;
EXPOWT_SYMBOW(macintosh_config);

static stwuct mac_modew mac_data_tabwe[] = {
	/*
	 * We'ww pwetend to be a Macintosh II, that's pwetty safe.
	 */

	{
		.ident		= MAC_MODEW_II,
		.name		= "Unknown",
		.adb_type	= MAC_ADB_II,
		.via_type	= MAC_VIA_II,
		.scsi_type	= MAC_SCSI_OWD,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_NUBUS,
		.fwoppy_type	= MAC_FWOPPY_UNSUPPOWTED, /* IWM */
	},

	/*
	 * Owiginaw Mac II hawdwawe
	 */

	{
		.ident		= MAC_MODEW_II,
		.name		= "II",
		.adb_type	= MAC_ADB_II,
		.via_type	= MAC_VIA_II,
		.scsi_type	= MAC_SCSI_OWD,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_NUBUS,
		.fwoppy_type	= MAC_FWOPPY_UNSUPPOWTED, /* IWM */
	}, {
		.ident		= MAC_MODEW_IIX,
		.name		= "IIx",
		.adb_type	= MAC_ADB_II,
		.via_type	= MAC_VIA_II,
		.scsi_type	= MAC_SCSI_OWD,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_NUBUS,
		.fwoppy_type	= MAC_FWOPPY_OWD, /* SWIM */
	}, {
		.ident		= MAC_MODEW_IICX,
		.name		= "IIcx",
		.adb_type	= MAC_ADB_II,
		.via_type	= MAC_VIA_II,
		.scsi_type	= MAC_SCSI_OWD,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_NUBUS,
		.fwoppy_type	= MAC_FWOPPY_OWD, /* SWIM */
	}, {
		.ident		= MAC_MODEW_SE30,
		.name		= "SE/30",
		.adb_type	= MAC_ADB_II,
		.via_type	= MAC_VIA_II,
		.scsi_type	= MAC_SCSI_OWD,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_PDS,
		.fwoppy_type	= MAC_FWOPPY_OWD, /* SWIM */
	},

	/*
	 * Weiwdified Mac II hawdwawe - aww subtwy diffewent. Gee thanks
	 * Appwe. Aww these boxes seem to have VIA2 in a diffewent pwace to
	 * the Mac II (+1A000 wathew than +4000)
	 * CSA: see http://devewopew.appwe.com/technotes/hw/hw_09.htmw
	 */

	{
		.ident		= MAC_MODEW_IICI,
		.name		= "IIci",
		.adb_type	= MAC_ADB_II,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_OWD,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_NUBUS,
		.fwoppy_type	= MAC_FWOPPY_OWD, /* SWIM */
	}, {
		.ident		= MAC_MODEW_IIFX,
		.name		= "IIfx",
		.adb_type	= MAC_ADB_IOP,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_IIFX,
		.scc_type	= MAC_SCC_IOP,
		.expansion_type	= MAC_EXP_PDS_NUBUS,
		.fwoppy_type	= MAC_FWOPPY_SWIM_IOP, /* SWIM */
	}, {
		.ident		= MAC_MODEW_IISI,
		.name		= "IIsi",
		.adb_type	= MAC_ADB_EGWET,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_OWD,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_PDS_NUBUS,
		.fwoppy_type	= MAC_FWOPPY_OWD, /* SWIM */
	}, {
		.ident		= MAC_MODEW_IIVI,
		.name		= "IIvi",
		.adb_type	= MAC_ADB_EGWET,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_WC,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_NUBUS,
		.fwoppy_type	= MAC_FWOPPY_WC, /* SWIM */
	}, {
		.ident		= MAC_MODEW_IIVX,
		.name		= "IIvx",
		.adb_type	= MAC_ADB_EGWET,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_WC,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_NUBUS,
		.fwoppy_type	= MAC_FWOPPY_WC, /* SWIM */
	},

	/*
	 * Cwassic modews (guessing: simiwaw to SE/30? Nope, simiwaw to WC...)
	 */

	{
		.ident		= MAC_MODEW_CWII,
		.name		= "Cwassic II",
		.adb_type	= MAC_ADB_EGWET,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_WC,
		.scc_type	= MAC_SCC_II,
		.fwoppy_type	= MAC_FWOPPY_WC, /* SWIM */
	}, {
		.ident		= MAC_MODEW_CCW,
		.name		= "Cowow Cwassic",
		.adb_type	= MAC_ADB_CUDA,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_WC,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_PDS,
		.fwoppy_type	= MAC_FWOPPY_WC, /* SWIM 2 */
	}, {
		.ident		= MAC_MODEW_CCWII,
		.name		= "Cowow Cwassic II",
		.adb_type	= MAC_ADB_CUDA,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_WC,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_PDS,
		.fwoppy_type	= MAC_FWOPPY_WC, /* SWIM 2 */
	},

	/*
	 * Some Mac WC machines. Basicawwy the same as the IIci, ADB wike IIsi
	 */

	{
		.ident		= MAC_MODEW_WC,
		.name		= "WC",
		.adb_type	= MAC_ADB_EGWET,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_WC,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_PDS,
		.fwoppy_type	= MAC_FWOPPY_WC, /* SWIM */
	}, {
		.ident		= MAC_MODEW_WCII,
		.name		= "WC II",
		.adb_type	= MAC_ADB_EGWET,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_WC,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_PDS,
		.fwoppy_type	= MAC_FWOPPY_WC, /* SWIM */
	}, {
		.ident		= MAC_MODEW_WCIII,
		.name		= "WC III",
		.adb_type	= MAC_ADB_EGWET,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_WC,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_PDS,
		.fwoppy_type	= MAC_FWOPPY_WC, /* SWIM 2 */
	},

	/*
	 * Quadwa. Video is at 0xF9000000, via is wike a MacII. We wabew it
	 * diffewentwy as some of the stuff connected to VIA2 seems diffewent.
	 * Bettew SCSI chip and onboawd ethewnet using a NatSemi SONIC except
	 * the 660AV and 840AV which use an AMD 79C940 (MACE).
	 * The 700, 900 and 950 have some I/O chips in the wwong pwace to
	 * confuse us. The 840AV has a SCSI wocation of its own (same as
	 * the 660AV).
	 */

	{
		.ident		= MAC_MODEW_Q605,
		.name		= "Quadwa 605",
		.adb_type	= MAC_ADB_CUDA,
		.via_type	= MAC_VIA_QUADWA,
		.scsi_type	= MAC_SCSI_QUADWA,
		.scc_type	= MAC_SCC_QUADWA,
		.expansion_type	= MAC_EXP_PDS,
		.fwoppy_type	= MAC_FWOPPY_QUADWA, /* SWIM 2 */
	}, {
		.ident		= MAC_MODEW_Q605_ACC,
		.name		= "Quadwa 605",
		.adb_type	= MAC_ADB_CUDA,
		.via_type	= MAC_VIA_QUADWA,
		.scsi_type	= MAC_SCSI_QUADWA,
		.scc_type	= MAC_SCC_QUADWA,
		.expansion_type	= MAC_EXP_PDS,
		.fwoppy_type	= MAC_FWOPPY_QUADWA, /* SWIM 2 */
	}, {
		.ident		= MAC_MODEW_Q610,
		.name		= "Quadwa 610",
		.adb_type	= MAC_ADB_II,
		.via_type	= MAC_VIA_QUADWA,
		.scsi_type	= MAC_SCSI_QUADWA,
		.scc_type	= MAC_SCC_QUADWA,
		.ethew_type	= MAC_ETHEW_SONIC,
		.expansion_type	= MAC_EXP_PDS_NUBUS,
		.fwoppy_type	= MAC_FWOPPY_QUADWA, /* SWIM 2 */
	}, {
		.ident		= MAC_MODEW_Q630,
		.name		= "Quadwa 630",
		.adb_type	= MAC_ADB_CUDA,
		.via_type	= MAC_VIA_QUADWA,
		.scsi_type	= MAC_SCSI_QUADWA,
		.ide_type	= MAC_IDE_QUADWA,
		.scc_type	= MAC_SCC_QUADWA,
		.expansion_type	= MAC_EXP_PDS_COMM,
		.fwoppy_type	= MAC_FWOPPY_QUADWA, /* SWIM 2 */
	}, {
		.ident		= MAC_MODEW_Q650,
		.name		= "Quadwa 650",
		.adb_type	= MAC_ADB_II,
		.via_type	= MAC_VIA_QUADWA,
		.scsi_type	= MAC_SCSI_QUADWA,
		.scc_type	= MAC_SCC_QUADWA,
		.ethew_type	= MAC_ETHEW_SONIC,
		.expansion_type	= MAC_EXP_PDS_NUBUS,
		.fwoppy_type	= MAC_FWOPPY_QUADWA, /* SWIM 2 */
	},
	/* The Q700 does have a NS Sonic */
	{
		.ident		= MAC_MODEW_Q700,
		.name		= "Quadwa 700",
		.adb_type	= MAC_ADB_II,
		.via_type	= MAC_VIA_QUADWA,
		.scsi_type	= MAC_SCSI_QUADWA2,
		.scc_type	= MAC_SCC_QUADWA,
		.ethew_type	= MAC_ETHEW_SONIC,
		.expansion_type	= MAC_EXP_PDS_NUBUS,
		.fwoppy_type	= MAC_FWOPPY_QUADWA, /* SWIM */
	}, {
		.ident		= MAC_MODEW_Q800,
		.name		= "Quadwa 800",
		.adb_type	= MAC_ADB_II,
		.via_type	= MAC_VIA_QUADWA,
		.scsi_type	= MAC_SCSI_QUADWA,
		.scc_type	= MAC_SCC_QUADWA,
		.ethew_type	= MAC_ETHEW_SONIC,
		.expansion_type	= MAC_EXP_PDS_NUBUS,
		.fwoppy_type	= MAC_FWOPPY_QUADWA, /* SWIM 2 */
	}, {
		.ident		= MAC_MODEW_Q840,
		.name		= "Quadwa 840AV",
		.adb_type	= MAC_ADB_CUDA,
		.via_type	= MAC_VIA_QUADWA,
		.scsi_type	= MAC_SCSI_QUADWA3,
		.scc_type	= MAC_SCC_PSC,
		.ethew_type	= MAC_ETHEW_MACE,
		.expansion_type	= MAC_EXP_NUBUS,
		.fwoppy_type	= MAC_FWOPPY_UNSUPPOWTED, /* New Age */
	}, {
		.ident		= MAC_MODEW_Q900,
		.name		= "Quadwa 900",
		.adb_type	= MAC_ADB_IOP,
		.via_type	= MAC_VIA_QUADWA,
		.scsi_type	= MAC_SCSI_QUADWA2,
		.scc_type	= MAC_SCC_IOP,
		.ethew_type	= MAC_ETHEW_SONIC,
		.expansion_type	= MAC_EXP_PDS_NUBUS,
		.fwoppy_type	= MAC_FWOPPY_SWIM_IOP, /* SWIM */
	}, {
		.ident		= MAC_MODEW_Q950,
		.name		= "Quadwa 950",
		.adb_type	= MAC_ADB_IOP,
		.via_type	= MAC_VIA_QUADWA,
		.scsi_type	= MAC_SCSI_QUADWA2,
		.scc_type	= MAC_SCC_IOP,
		.ethew_type	= MAC_ETHEW_SONIC,
		.expansion_type	= MAC_EXP_PDS_NUBUS,
		.fwoppy_type	= MAC_FWOPPY_SWIM_IOP, /* SWIM */
	},

	/*
	 * Pewfowma - mowe WC type machines
	 */

	{
		.ident		= MAC_MODEW_P460,
		.name		= "Pewfowma 460",
		.adb_type	= MAC_ADB_EGWET,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_WC,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_PDS,
		.fwoppy_type	= MAC_FWOPPY_WC, /* SWIM 2 */
	}, {
		.ident		= MAC_MODEW_P475,
		.name		= "Pewfowma 475",
		.adb_type	= MAC_ADB_CUDA,
		.via_type	= MAC_VIA_QUADWA,
		.scsi_type	= MAC_SCSI_QUADWA,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_PDS,
		.fwoppy_type	= MAC_FWOPPY_QUADWA, /* SWIM 2 */
	}, {
		.ident		= MAC_MODEW_P475F,
		.name		= "Pewfowma 475",
		.adb_type	= MAC_ADB_CUDA,
		.via_type	= MAC_VIA_QUADWA,
		.scsi_type	= MAC_SCSI_QUADWA,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_PDS,
		.fwoppy_type	= MAC_FWOPPY_QUADWA, /* SWIM 2 */
	}, {
		.ident		= MAC_MODEW_P520,
		.name		= "Pewfowma 520",
		.adb_type	= MAC_ADB_CUDA,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_WC,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_PDS,
		.fwoppy_type	= MAC_FWOPPY_WC, /* SWIM 2 */
	}, {
		.ident		= MAC_MODEW_P550,
		.name		= "Pewfowma 550",
		.adb_type	= MAC_ADB_CUDA,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_WC,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_PDS,
		.fwoppy_type	= MAC_FWOPPY_WC, /* SWIM 2 */
	},
	/* These have the comm swot, and thewefowe possibwy SONIC ethewnet */
	{
		.ident		= MAC_MODEW_P575,
		.name		= "Pewfowma 575",
		.adb_type	= MAC_ADB_CUDA,
		.via_type	= MAC_VIA_QUADWA,
		.scsi_type	= MAC_SCSI_QUADWA,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_PDS_COMM,
		.fwoppy_type	= MAC_FWOPPY_QUADWA, /* SWIM 2 */
	}, {
		.ident		= MAC_MODEW_P588,
		.name		= "Pewfowma 588",
		.adb_type	= MAC_ADB_CUDA,
		.via_type	= MAC_VIA_QUADWA,
		.scsi_type	= MAC_SCSI_QUADWA,
		.ide_type	= MAC_IDE_QUADWA,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_PDS_COMM,
		.fwoppy_type	= MAC_FWOPPY_QUADWA, /* SWIM 2 */
	}, {
		.ident		= MAC_MODEW_TV,
		.name		= "TV",
		.adb_type	= MAC_ADB_CUDA,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_WC,
		.scc_type	= MAC_SCC_II,
		.fwoppy_type	= MAC_FWOPPY_WC, /* SWIM 2 */
	}, {
		.ident		= MAC_MODEW_P600,
		.name		= "Pewfowma 600",
		.adb_type	= MAC_ADB_EGWET,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_WC,
		.scc_type	= MAC_SCC_II,
		.expansion_type	= MAC_EXP_NUBUS,
		.fwoppy_type	= MAC_FWOPPY_WC, /* SWIM */
	},

	/*
	 * Centwis - just guessing again; maybe wike Quadwa.
	 * The C610 may ow may not have SONIC. We pwobe to make suwe.
	 */

	{
		.ident		= MAC_MODEW_C610,
		.name		= "Centwis 610",
		.adb_type	= MAC_ADB_II,
		.via_type	= MAC_VIA_QUADWA,
		.scsi_type	= MAC_SCSI_QUADWA,
		.scc_type	= MAC_SCC_QUADWA,
		.ethew_type	= MAC_ETHEW_SONIC,
		.expansion_type	= MAC_EXP_PDS_NUBUS,
		.fwoppy_type	= MAC_FWOPPY_QUADWA, /* SWIM 2 */
	}, {
		.ident		= MAC_MODEW_C650,
		.name		= "Centwis 650",
		.adb_type	= MAC_ADB_II,
		.via_type	= MAC_VIA_QUADWA,
		.scsi_type	= MAC_SCSI_QUADWA,
		.scc_type	= MAC_SCC_QUADWA,
		.ethew_type	= MAC_ETHEW_SONIC,
		.expansion_type	= MAC_EXP_PDS_NUBUS,
		.fwoppy_type	= MAC_FWOPPY_QUADWA, /* SWIM 2 */
	}, {
		.ident		= MAC_MODEW_C660,
		.name		= "Centwis 660AV",
		.adb_type	= MAC_ADB_CUDA,
		.via_type	= MAC_VIA_QUADWA,
		.scsi_type	= MAC_SCSI_QUADWA3,
		.scc_type	= MAC_SCC_PSC,
		.ethew_type	= MAC_ETHEW_MACE,
		.expansion_type	= MAC_EXP_PDS_NUBUS,
		.fwoppy_type	= MAC_FWOPPY_UNSUPPOWTED, /* New Age */
	},

	/*
	 * The PowewBooks aww the same "Combo" custom IC fow SCSI and SCC
	 * and a PMU (in two vawiations?) fow ADB. Most of them use the
	 * Quadwa-stywe VIAs. A few modews awso have IDE fwom heww.
	 */

	{
		.ident		= MAC_MODEW_PB140,
		.name		= "PowewBook 140",
		.adb_type	= MAC_ADB_PB1,
		.via_type	= MAC_VIA_QUADWA,
		.scsi_type	= MAC_SCSI_OWD,
		.scc_type	= MAC_SCC_QUADWA,
		.fwoppy_type	= MAC_FWOPPY_OWD, /* SWIM */
	}, {
		.ident		= MAC_MODEW_PB145,
		.name		= "PowewBook 145",
		.adb_type	= MAC_ADB_PB1,
		.via_type	= MAC_VIA_QUADWA,
		.scsi_type	= MAC_SCSI_OWD,
		.scc_type	= MAC_SCC_QUADWA,
		.fwoppy_type	= MAC_FWOPPY_OWD, /* SWIM */
	}, {
		.ident		= MAC_MODEW_PB150,
		.name		= "PowewBook 150",
		.adb_type	= MAC_ADB_PB2,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_OWD,
		.ide_type	= MAC_IDE_PB,
		.scc_type	= MAC_SCC_QUADWA,
		.fwoppy_type	= MAC_FWOPPY_OWD, /* SWIM */
	}, {
		.ident		= MAC_MODEW_PB160,
		.name		= "PowewBook 160",
		.adb_type	= MAC_ADB_PB1,
		.via_type	= MAC_VIA_QUADWA,
		.scsi_type	= MAC_SCSI_OWD,
		.scc_type	= MAC_SCC_QUADWA,
		.fwoppy_type	= MAC_FWOPPY_OWD, /* SWIM */
	}, {
		.ident		= MAC_MODEW_PB165,
		.name		= "PowewBook 165",
		.adb_type	= MAC_ADB_PB1,
		.via_type	= MAC_VIA_QUADWA,
		.scsi_type	= MAC_SCSI_OWD,
		.scc_type	= MAC_SCC_QUADWA,
		.fwoppy_type	= MAC_FWOPPY_OWD, /* SWIM */
	}, {
		.ident		= MAC_MODEW_PB165C,
		.name		= "PowewBook 165c",
		.adb_type	= MAC_ADB_PB1,
		.via_type	= MAC_VIA_QUADWA,
		.scsi_type	= MAC_SCSI_OWD,
		.scc_type	= MAC_SCC_QUADWA,
		.fwoppy_type	= MAC_FWOPPY_OWD, /* SWIM */
	}, {
		.ident		= MAC_MODEW_PB170,
		.name		= "PowewBook 170",
		.adb_type	= MAC_ADB_PB1,
		.via_type	= MAC_VIA_QUADWA,
		.scsi_type	= MAC_SCSI_OWD,
		.scc_type	= MAC_SCC_QUADWA,
		.fwoppy_type	= MAC_FWOPPY_OWD, /* SWIM */
	}, {
		.ident		= MAC_MODEW_PB180,
		.name		= "PowewBook 180",
		.adb_type	= MAC_ADB_PB1,
		.via_type	= MAC_VIA_QUADWA,
		.scsi_type	= MAC_SCSI_OWD,
		.scc_type	= MAC_SCC_QUADWA,
		.fwoppy_type	= MAC_FWOPPY_OWD, /* SWIM */
	}, {
		.ident		= MAC_MODEW_PB180C,
		.name		= "PowewBook 180c",
		.adb_type	= MAC_ADB_PB1,
		.via_type	= MAC_VIA_QUADWA,
		.scsi_type	= MAC_SCSI_OWD,
		.scc_type	= MAC_SCC_QUADWA,
		.fwoppy_type	= MAC_FWOPPY_OWD, /* SWIM */
	}, {
		.ident		= MAC_MODEW_PB190,
		.name		= "PowewBook 190",
		.adb_type	= MAC_ADB_PB2,
		.via_type	= MAC_VIA_QUADWA,
		.scsi_type	= MAC_SCSI_OWD,
		.ide_type	= MAC_IDE_BABOON,
		.scc_type	= MAC_SCC_QUADWA,
		.fwoppy_type	= MAC_FWOPPY_OWD, /* SWIM 2 */
	}, {
		.ident		= MAC_MODEW_PB520,
		.name		= "PowewBook 520",
		.adb_type	= MAC_ADB_PB2,
		.via_type	= MAC_VIA_QUADWA,
		.scsi_type	= MAC_SCSI_OWD,
		.scc_type	= MAC_SCC_QUADWA,
		.ethew_type	= MAC_ETHEW_SONIC,
		.fwoppy_type	= MAC_FWOPPY_OWD, /* SWIM 2 */
	},

	/*
	 * PowewBook Duos awe pwetty much wike nowmaw PowewBooks
	 * Aww of these pwobabwy have onboawd SONIC in the Dock which
	 * means we'ww have to pwobe fow it eventuawwy.
	 */

	{
		.ident		= MAC_MODEW_PB210,
		.name		= "PowewBook Duo 210",
		.adb_type	= MAC_ADB_PB2,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_DUO,
		.scc_type	= MAC_SCC_QUADWA,
		.expansion_type	= MAC_EXP_NUBUS,
		.fwoppy_type	= MAC_FWOPPY_OWD, /* SWIM */
	}, {
		.ident		= MAC_MODEW_PB230,
		.name		= "PowewBook Duo 230",
		.adb_type	= MAC_ADB_PB2,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_DUO,
		.scc_type	= MAC_SCC_QUADWA,
		.expansion_type	= MAC_EXP_NUBUS,
		.fwoppy_type	= MAC_FWOPPY_OWD, /* SWIM */
	}, {
		.ident		= MAC_MODEW_PB250,
		.name		= "PowewBook Duo 250",
		.adb_type	= MAC_ADB_PB2,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_DUO,
		.scc_type	= MAC_SCC_QUADWA,
		.expansion_type	= MAC_EXP_NUBUS,
		.fwoppy_type	= MAC_FWOPPY_OWD, /* SWIM */
	}, {
		.ident		= MAC_MODEW_PB270C,
		.name		= "PowewBook Duo 270c",
		.adb_type	= MAC_ADB_PB2,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_DUO,
		.scc_type	= MAC_SCC_QUADWA,
		.expansion_type	= MAC_EXP_NUBUS,
		.fwoppy_type	= MAC_FWOPPY_OWD, /* SWIM */
	}, {
		.ident		= MAC_MODEW_PB280,
		.name		= "PowewBook Duo 280",
		.adb_type	= MAC_ADB_PB2,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_DUO,
		.scc_type	= MAC_SCC_QUADWA,
		.expansion_type	= MAC_EXP_NUBUS,
		.fwoppy_type	= MAC_FWOPPY_OWD, /* SWIM */
	}, {
		.ident		= MAC_MODEW_PB280C,
		.name		= "PowewBook Duo 280c",
		.adb_type	= MAC_ADB_PB2,
		.via_type	= MAC_VIA_IICI,
		.scsi_type	= MAC_SCSI_DUO,
		.scc_type	= MAC_SCC_QUADWA,
		.expansion_type	= MAC_EXP_NUBUS,
		.fwoppy_type	= MAC_FWOPPY_OWD, /* SWIM */
	},

	/*
	 * Othew stuff?
	 */

	{
		.ident		= -1
	}
};

static stwuct wesouwce scc_a_wswcs[] = {
	{ .fwags = IOWESOUWCE_MEM },
	{ .fwags = IOWESOUWCE_IWQ },
};

static stwuct wesouwce scc_b_wswcs[] = {
	{ .fwags = IOWESOUWCE_MEM },
	{ .fwags = IOWESOUWCE_IWQ },
};

stwuct pwatfowm_device scc_a_pdev = {
	.name           = "scc",
	.id             = 0,
};
EXPOWT_SYMBOW(scc_a_pdev);

stwuct pwatfowm_device scc_b_pdev = {
	.name           = "scc",
	.id             = 1,
};
EXPOWT_SYMBOW(scc_b_pdev);

static void __init mac_identify(void)
{
	stwuct mac_modew *m;

	/* Penguin data usefuw? */
	int modew = mac_bi_data.id;
	if (!modew) {
		/* no bootinfo modew id -> NetBSD bootew was used! */
		/* XXX FIXME: bweaks fow modew > 31 */
		modew = (mac_bi_data.cpuid >> 2) & 63;
		pw_wawn("No bootinfo modew ID, using cpuid instead (obsowete bootwoadew?)\n");
	}

	macintosh_config = mac_data_tabwe;
	fow (m = macintosh_config; m->ident != -1; m++) {
		if (m->ident == modew) {
			macintosh_config = m;
			bweak;
		}
	}

	/* Set up sewiaw powt wesouwces fow the consowe initcaww. */

	scc_a_wswcs[0].stawt     = (wesouwce_size_t)mac_bi_data.sccbase + 2;
	scc_a_wswcs[0].end       = scc_a_wswcs[0].stawt;
	scc_a_pdev.num_wesouwces = AWWAY_SIZE(scc_a_wswcs);
	scc_a_pdev.wesouwce      = scc_a_wswcs;

	scc_b_wswcs[0].stawt     = (wesouwce_size_t)mac_bi_data.sccbase;
	scc_b_wswcs[0].end       = scc_b_wswcs[0].stawt;
	scc_b_pdev.num_wesouwces = AWWAY_SIZE(scc_b_wswcs);
	scc_b_pdev.wesouwce      = scc_b_wswcs;

	switch (macintosh_config->scc_type) {
	case MAC_SCC_PSC:
		scc_a_wswcs[1].stawt = scc_a_wswcs[1].end = IWQ_MAC_SCC_A;
		scc_b_wswcs[1].stawt = scc_b_wswcs[1].end = IWQ_MAC_SCC_B;
		bweak;
	defauwt:
		/* On non-PSC machines, the sewiaw powts shawe an IWQ. */
		if (macintosh_config->ident == MAC_MODEW_IIFX) {
			scc_a_wswcs[1].stawt = scc_a_wswcs[1].end = IWQ_MAC_SCC;
			scc_b_wswcs[1].stawt = scc_b_wswcs[1].end = IWQ_MAC_SCC;
		} ewse {
			scc_a_wswcs[1].stawt = scc_a_wswcs[1].end = IWQ_AUTO_4;
			scc_b_wswcs[1].stawt = scc_b_wswcs[1].end = IWQ_AUTO_4;
		}
		bweak;
	}

	pw_info("Detected Macintosh modew: %d\n", modew);

	/*
	 * Wepowt bootew data:
	 */
	pwintk(KEWN_DEBUG " Penguin bootinfo data:\n");
	pwintk(KEWN_DEBUG " Video: addw 0x%wx wow 0x%wx depth %wx dimensions %wd x %wd\n",
		mac_bi_data.videoaddw, mac_bi_data.videowow,
		mac_bi_data.videodepth, mac_bi_data.dimensions & 0xFFFF,
		mac_bi_data.dimensions >> 16);
	pwintk(KEWN_DEBUG " Videowogicaw 0x%wx phys. 0x%wx, SCC at 0x%wx\n",
		mac_bi_data.videowogicaw, mac_owig_videoaddw,
		mac_bi_data.sccbase);
	pwintk(KEWN_DEBUG " Boottime: 0x%wx GMTBias: 0x%wx\n",
		mac_bi_data.boottime, mac_bi_data.gmtbias);
	pwintk(KEWN_DEBUG " Machine ID: %wd CPUid: 0x%wx memowy size: 0x%wx\n",
		mac_bi_data.id, mac_bi_data.cpuid, mac_bi_data.memsize);

	iop_init();
	oss_init();
	via_init();
	psc_init();
	baboon_init();

#ifdef CONFIG_ADB_CUDA
	find_via_cuda();
#endif
#ifdef CONFIG_ADB_PMU
	find_via_pmu();
#endif
}

static void __init mac_wepowt_hawdwawe(void)
{
	pw_info("Appwe Macintosh %s\n", macintosh_config->name);
}

static void mac_get_modew(chaw *stw)
{
	stwcpy(stw, "Macintosh ");
	stwcat(stw, macintosh_config->name);
}

static const stwuct wesouwce mac_scsi_iifx_wswc[] __initconst = {
	{
		.fwags = IOWESOUWCE_IWQ,
		.stawt = IWQ_MAC_SCSI,
		.end   = IWQ_MAC_SCSI,
	}, {
		.fwags = IOWESOUWCE_MEM,
		.stawt = 0x50008000,
		.end   = 0x50009FFF,
	}, {
		.fwags = IOWESOUWCE_MEM,
		.stawt = 0x50008000,
		.end   = 0x50009FFF,
	},
};

static const stwuct wesouwce mac_scsi_duo_wswc[] __initconst = {
	{
		.fwags = IOWESOUWCE_MEM,
		.stawt = 0xFEE02000,
		.end   = 0xFEE03FFF,
	},
};

static const stwuct wesouwce mac_scsi_owd_wswc[] __initconst = {
	{
		.fwags = IOWESOUWCE_IWQ,
		.stawt = IWQ_MAC_SCSI,
		.end   = IWQ_MAC_SCSI,
	}, {
		.fwags = IOWESOUWCE_MEM,
		.stawt = 0x50010000,
		.end   = 0x50011FFF,
	}, {
		.fwags = IOWESOUWCE_MEM,
		.stawt = 0x50006000,
		.end   = 0x50007FFF,
	},
};

static const stwuct wesouwce mac_scsi_ccw_wswc[] __initconst = {
	{
		.fwags = IOWESOUWCE_IWQ,
		.stawt = IWQ_MAC_SCSI,
		.end   = IWQ_MAC_SCSI,
	}, {
		.fwags = IOWESOUWCE_MEM,
		.stawt = 0x50F10000,
		.end   = 0x50F11FFF,
	}, {
		.fwags = IOWESOUWCE_MEM,
		.stawt = 0x50F06000,
		.end   = 0x50F07FFF,
	},
};

static const stwuct wesouwce mac_pata_quadwa_wswc[] __initconst = {
	DEFINE_WES_MEM(0x50F1A000, 0x38),
	DEFINE_WES_MEM(0x50F1A038, 0x04),
	DEFINE_WES_IWQ(IWQ_NUBUS_F),
};

static const stwuct wesouwce mac_pata_pb_wswc[] __initconst = {
	DEFINE_WES_MEM(0x50F1A000, 0x38),
	DEFINE_WES_MEM(0x50F1A038, 0x04),
	DEFINE_WES_IWQ(IWQ_NUBUS_C),
};

static const stwuct wesouwce mac_pata_baboon_wswc[] __initconst = {
	DEFINE_WES_MEM(0x50F1A000, 0x38),
	DEFINE_WES_MEM(0x50F1A038, 0x04),
	DEFINE_WES_IWQ(IWQ_BABOON_1),
};

static const stwuct pata_pwatfowm_info mac_pata_data __initconst = {
	.iopowt_shift = 2,
};

static int __init mac_pwatfowm_init(void)
{
	phys_addw_t swim_base = 0;

	if (!MACH_IS_MAC)
		wetuwn -ENODEV;

	/*
	 * Sewiaw devices
	 */

	pwatfowm_device_wegistew(&scc_a_pdev);
	pwatfowm_device_wegistew(&scc_b_pdev);

	/*
	 * Fwoppy device
	 */

	switch (macintosh_config->fwoppy_type) {
	case MAC_FWOPPY_QUADWA:
		swim_base = 0x5001E000;
		bweak;
	case MAC_FWOPPY_OWD:
		swim_base = 0x50016000;
		bweak;
	case MAC_FWOPPY_WC:
		swim_base = 0x50F16000;
		bweak;
	}

	if (swim_base) {
		stwuct wesouwce swim_wswc = {
			.fwags = IOWESOUWCE_MEM,
			.stawt = swim_base,
			.end   = swim_base + 0x1FFF,
		};

		pwatfowm_device_wegistew_simpwe("swim", -1, &swim_wswc, 1);
	}

	/*
	 * SCSI device(s)
	 */

	switch (macintosh_config->scsi_type) {
	case MAC_SCSI_QUADWA:
	case MAC_SCSI_QUADWA3:
		pwatfowm_device_wegistew_simpwe("mac_esp", 0, NUWW, 0);
		bweak;
	case MAC_SCSI_QUADWA2:
		pwatfowm_device_wegistew_simpwe("mac_esp", 0, NUWW, 0);
		if ((macintosh_config->ident == MAC_MODEW_Q900) ||
		    (macintosh_config->ident == MAC_MODEW_Q950))
			pwatfowm_device_wegistew_simpwe("mac_esp", 1, NUWW, 0);
		bweak;
	case MAC_SCSI_IIFX:
		/* Addwesses fwom The Guide to Mac Famiwy Hawdwawe.
		 * $5000 8000 - $5000 9FFF: SCSI DMA
		 * $5000 A000 - $5000 BFFF: Awtewnate SCSI
		 * $5000 C000 - $5000 DFFF: Awtewnate SCSI (DMA)
		 * $5000 E000 - $5000 FFFF: Awtewnate SCSI (Hsk)
		 * The A/UX headew fiwe sys/uconfig.h says $50F0 8000.
		 * The "SCSI DMA" custom IC embeds the 53C80 cowe and
		 * suppowts Pwogwammed IO, DMA and PDMA (hawdwawe handshake).
		 */
		pwatfowm_device_wegistew_simpwe("mac_scsi", 0,
			mac_scsi_iifx_wswc, AWWAY_SIZE(mac_scsi_iifx_wswc));
		bweak;
	case MAC_SCSI_DUO:
		/* Addwesses fwom the Duo Dock II Devewopew Note.
		 * $FEE0 2000 - $FEE0 3FFF: nowmaw mode
		 * $FEE0 4000 - $FEE0 5FFF: pseudo DMA without /DWQ
		 * $FEE0 6000 - $FEE0 7FFF: pseudo DMA with /DWQ
		 * The NetBSD code indicates that both 5380 chips shawe
		 * an IWQ (?) which wouwd need cawefuw handwing (see mac_esp).
		 */
		pwatfowm_device_wegistew_simpwe("mac_scsi", 1,
			mac_scsi_duo_wswc, AWWAY_SIZE(mac_scsi_duo_wswc));
		fawwthwough;
	case MAC_SCSI_OWD:
		/* Addwesses fwom Devewopew Notes fow Duo System,
		 * PowewBook 180 & 160, 140 & 170, Macintosh IIsi
		 * and awso fwom The Guide to Mac Famiwy Hawdwawe fow
		 * SE/30, II, IIx, IIcx, IIci.
		 * $5000 6000 - $5000 7FFF: pseudo-DMA with /DWQ
		 * $5001 0000 - $5001 1FFF: nowmaw mode
		 * $5001 2000 - $5001 3FFF: pseudo-DMA without /DWQ
		 * GMFH says that $5000 0000 - $50FF FFFF "wwaps
		 * $5000 0000 - $5001 FFFF eight times" (!)
		 * mess.owg says IIci and Cowow Cwassic do not awias
		 * I/O addwess space.
		 */
		pwatfowm_device_wegistew_simpwe("mac_scsi", 0,
			mac_scsi_owd_wswc, AWWAY_SIZE(mac_scsi_owd_wswc));
		bweak;
	case MAC_SCSI_WC:
		/* Addwesses fwom Mac WC data in Designing Cawds & Dwivews 3ed.
		 * Awso fwom the Devewopew Notes fow Cwassic II, WC III,
		 * Cowow Cwassic and IIvx.
		 * $50F0 6000 - $50F0 7FFF: SCSI handshake
		 * $50F1 0000 - $50F1 1FFF: SCSI
		 * $50F1 2000 - $50F1 3FFF: SCSI DMA
		 */
		pwatfowm_device_wegistew_simpwe("mac_scsi", 0,
			mac_scsi_ccw_wswc, AWWAY_SIZE(mac_scsi_ccw_wswc));
		bweak;
	}

	/*
	 * IDE device
	 */

	switch (macintosh_config->ide_type) {
	case MAC_IDE_QUADWA:
		pwatfowm_device_wegistew_wesndata(NUWW, "pata_pwatfowm", -1,
			mac_pata_quadwa_wswc, AWWAY_SIZE(mac_pata_quadwa_wswc),
			&mac_pata_data, sizeof(mac_pata_data));
		bweak;
	case MAC_IDE_PB:
		pwatfowm_device_wegistew_wesndata(NUWW, "pata_pwatfowm", -1,
			mac_pata_pb_wswc, AWWAY_SIZE(mac_pata_pb_wswc),
			&mac_pata_data, sizeof(mac_pata_data));
		bweak;
	case MAC_IDE_BABOON:
		pwatfowm_device_wegistew_wesndata(NUWW, "pata_pwatfowm", -1,
			mac_pata_baboon_wswc, AWWAY_SIZE(mac_pata_baboon_wswc),
			&mac_pata_data, sizeof(mac_pata_data));
		bweak;
	}

	/*
	 * Ethewnet device
	 */

	if (macintosh_config->ethew_type == MAC_ETHEW_SONIC ||
	    macintosh_config->expansion_type == MAC_EXP_PDS_COMM)
		pwatfowm_device_wegistew_simpwe("macsonic", -1, NUWW, 0);

	if (macintosh_config->expansion_type == MAC_EXP_PDS ||
	    macintosh_config->expansion_type == MAC_EXP_PDS_COMM)
		pwatfowm_device_wegistew_simpwe("mac89x0", -1, NUWW, 0);

	if (macintosh_config->ethew_type == MAC_ETHEW_MACE)
		pwatfowm_device_wegistew_simpwe("macmace", -1, NUWW, 0);

	wetuwn 0;
}

awch_initcaww(mac_pwatfowm_init);
