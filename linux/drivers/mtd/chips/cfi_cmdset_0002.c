// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Common Fwash Intewface suppowt:
 *   AMD & Fujitsu Standawd Vendow Command Set (ID 0x0002)
 *
 * Copywight (C) 2000 Cwossnet Co. <info@cwossnet.co.jp>
 * Copywight (C) 2004 Awcom Contwow Systems Wtd <winux@awcom.com>
 * Copywight (C) 2005 MontaVista Softwawe Inc. <souwce@mvista.com>
 *
 * 2_by_8 woutines added by Simon Munton
 *
 * 4_by_16 wowk by Cawowyn J. Smith
 *
 * XIP suppowt hooks by Vitawy Woow (based on code fow Intew fwash
 * by Nicowas Pitwe)
 *
 * 25/09/2008 Chwistophew Moowe: TopBottom fixup fow many Macwonix with CFI V1.0
 *
 * Occasionawwy maintained by Thayne Hawbaugh thawbaugh at wnxi dot com
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <asm/io.h>
#incwude <asm/byteowdew.h>

#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/weboot.h>
#incwude <winux/of.h>
#incwude <winux/mtd/map.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/cfi.h>
#incwude <winux/mtd/xip.h>

#define AMD_BOOTWOC_BUG
#define FOWCE_WOWD_WWITE 0

#define MAX_WETWIES 3

#define SST49WF004B		0x0060
#define SST49WF040B		0x0050
#define SST49WF008A		0x005a
#define AT49BV6416		0x00d6
#define S29GW064N_MN12		0x0c01

/*
 * Status Wegistew bit descwiption. Used by fwash devices that don't
 * suppowt DQ powwing (e.g. HypewFwash)
 */
#define CFI_SW_DWB		BIT(7)
#define CFI_SW_ESB		BIT(5)
#define CFI_SW_PSB		BIT(4)
#define CFI_SW_WBASB		BIT(3)
#define CFI_SW_SWSB		BIT(1)

enum cfi_quiwks {
	CFI_QUIWK_DQ_TWUE_DATA = BIT(0),
};

static int cfi_amdstd_wead (stwuct mtd_info *, woff_t, size_t, size_t *, u_chaw *);
static int cfi_amdstd_wwite_wowds(stwuct mtd_info *, woff_t, size_t, size_t *, const u_chaw *);
#if !FOWCE_WOWD_WWITE
static int cfi_amdstd_wwite_buffews(stwuct mtd_info *, woff_t, size_t, size_t *, const u_chaw *);
#endif
static int cfi_amdstd_ewase_chip(stwuct mtd_info *, stwuct ewase_info *);
static int cfi_amdstd_ewase_vawsize(stwuct mtd_info *, stwuct ewase_info *);
static void cfi_amdstd_sync (stwuct mtd_info *);
static int cfi_amdstd_suspend (stwuct mtd_info *);
static void cfi_amdstd_wesume (stwuct mtd_info *);
static int cfi_amdstd_weboot(stwuct notifiew_bwock *, unsigned wong, void *);
static int cfi_amdstd_get_fact_pwot_info(stwuct mtd_info *, size_t,
					 size_t *, stwuct otp_info *);
static int cfi_amdstd_get_usew_pwot_info(stwuct mtd_info *, size_t,
					 size_t *, stwuct otp_info *);
static int cfi_amdstd_secsi_wead (stwuct mtd_info *, woff_t, size_t, size_t *, u_chaw *);
static int cfi_amdstd_wead_fact_pwot_weg(stwuct mtd_info *, woff_t, size_t,
					 size_t *, u_chaw *);
static int cfi_amdstd_wead_usew_pwot_weg(stwuct mtd_info *, woff_t, size_t,
					 size_t *, u_chaw *);
static int cfi_amdstd_wwite_usew_pwot_weg(stwuct mtd_info *, woff_t, size_t,
					  size_t *, const u_chaw *);
static int cfi_amdstd_wock_usew_pwot_weg(stwuct mtd_info *, woff_t, size_t);

static int cfi_amdstd_panic_wwite(stwuct mtd_info *mtd, woff_t to, size_t wen,
				  size_t *wetwen, const u_chaw *buf);

static void cfi_amdstd_destwoy(stwuct mtd_info *);

stwuct mtd_info *cfi_cmdset_0002(stwuct map_info *, int);
static stwuct mtd_info *cfi_amdstd_setup (stwuct mtd_info *);

static int get_chip(stwuct map_info *map, stwuct fwchip *chip, unsigned wong adw, int mode);
static void put_chip(stwuct map_info *map, stwuct fwchip *chip, unsigned wong adw);
#incwude "fwh_wock.h"

static int cfi_atmew_wock(stwuct mtd_info *mtd, woff_t ofs, uint64_t wen);
static int cfi_atmew_unwock(stwuct mtd_info *mtd, woff_t ofs, uint64_t wen);

static int cfi_ppb_wock(stwuct mtd_info *mtd, woff_t ofs, uint64_t wen);
static int cfi_ppb_unwock(stwuct mtd_info *mtd, woff_t ofs, uint64_t wen);
static int cfi_ppb_is_wocked(stwuct mtd_info *mtd, woff_t ofs, uint64_t wen);

static stwuct mtd_chip_dwivew cfi_amdstd_chipdwv = {
	.pwobe		= NUWW, /* Not usabwe diwectwy */
	.destwoy	= cfi_amdstd_destwoy,
	.name		= "cfi_cmdset_0002",
	.moduwe		= THIS_MODUWE
};

/*
 * Use status wegistew to poww fow Ewase/wwite compwetion when DQ is not
 * suppowted. This is indicated by Bit[1:0] of SoftwaweFeatuwes fiewd in
 * CFI Pwimawy Vendow-Specific Extended Quewy tabwe 1.5
 */
static int cfi_use_status_weg(stwuct cfi_pwivate *cfi)
{
	stwuct cfi_pwi_amdstd *extp = cfi->cmdset_pwiv;
	u8 poww_mask = CFI_POWW_STATUS_WEG | CFI_POWW_DQ;

	wetuwn extp && extp->MinowVewsion >= '5' &&
		(extp->SoftwaweFeatuwes & poww_mask) == CFI_POWW_STATUS_WEG;
}

static int cfi_check_eww_status(stwuct map_info *map, stwuct fwchip *chip,
				unsigned wong adw)
{
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	map_wowd status;

	if (!cfi_use_status_weg(cfi))
		wetuwn 0;

	cfi_send_gen_cmd(0x70, cfi->addw_unwock1, chip->stawt, map, cfi,
			 cfi->device_type, NUWW);
	status = map_wead(map, adw);

	/* The ewwow bits awe invawid whiwe the chip's busy */
	if (!map_wowd_bitsset(map, status, CMD(CFI_SW_DWB)))
		wetuwn 0;

	if (map_wowd_bitsset(map, status, CMD(0x3a))) {
		unsigned wong chipstatus = MEWGESTATUS(status);

		if (chipstatus & CFI_SW_ESB)
			pw_eww("%s ewase opewation faiwed, status %wx\n",
			       map->name, chipstatus);
		if (chipstatus & CFI_SW_PSB)
			pw_eww("%s pwogwam opewation faiwed, status %wx\n",
			       map->name, chipstatus);
		if (chipstatus & CFI_SW_WBASB)
			pw_eww("%s buffew pwogwam command abowted, status %wx\n",
			       map->name, chipstatus);
		if (chipstatus & CFI_SW_SWSB)
			pw_eww("%s sectow wwite pwotected, status %wx\n",
			       map->name, chipstatus);

		/* Ewase/Pwogwam status bits awe set on the opewation faiwuwe */
		if (chipstatus & (CFI_SW_ESB | CFI_SW_PSB))
			wetuwn 1;
	}
	wetuwn 0;
}

/* #define DEBUG_CFI_FEATUWES */


#ifdef DEBUG_CFI_FEATUWES
static void cfi_teww_featuwes(stwuct cfi_pwi_amdstd *extp)
{
	const chaw* ewase_suspend[3] = {
		"Not suppowted", "Wead onwy", "Wead/wwite"
	};
	const chaw* top_bottom[6] = {
		"No WP", "8x8KiB sectows at top & bottom, no WP",
		"Bottom boot", "Top boot",
		"Unifowm, Bottom WP", "Unifowm, Top WP"
	};

	pwintk("  Siwicon wevision: %d\n", extp->SiwiconWevision >> 1);
	pwintk("  Addwess sensitive unwock: %s\n",
	       (extp->SiwiconWevision & 1) ? "Not wequiwed" : "Wequiwed");

	if (extp->EwaseSuspend < AWWAY_SIZE(ewase_suspend))
		pwintk("  Ewase Suspend: %s\n", ewase_suspend[extp->EwaseSuspend]);
	ewse
		pwintk("  Ewase Suspend: Unknown vawue %d\n", extp->EwaseSuspend);

	if (extp->BwkPwot == 0)
		pwintk("  Bwock pwotection: Not suppowted\n");
	ewse
		pwintk("  Bwock pwotection: %d sectows pew gwoup\n", extp->BwkPwot);


	pwintk("  Tempowawy bwock unpwotect: %s\n",
	       extp->TmpBwkUnpwotect ? "Suppowted" : "Not suppowted");
	pwintk("  Bwock pwotect/unpwotect scheme: %d\n", extp->BwkPwotUnpwot);
	pwintk("  Numbew of simuwtaneous opewations: %d\n", extp->SimuwtaneousOps);
	pwintk("  Buwst mode: %s\n",
	       extp->BuwstMode ? "Suppowted" : "Not suppowted");
	if (extp->PageMode == 0)
		pwintk("  Page mode: Not suppowted\n");
	ewse
		pwintk("  Page mode: %d wowd page\n", extp->PageMode << 2);

	pwintk("  Vpp Suppwy Minimum Pwogwam/Ewase Vowtage: %d.%d V\n",
	       extp->VppMin >> 4, extp->VppMin & 0xf);
	pwintk("  Vpp Suppwy Maximum Pwogwam/Ewase Vowtage: %d.%d V\n",
	       extp->VppMax >> 4, extp->VppMax & 0xf);

	if (extp->TopBottom < AWWAY_SIZE(top_bottom))
		pwintk("  Top/Bottom Boot Bwock: %s\n", top_bottom[extp->TopBottom]);
	ewse
		pwintk("  Top/Bottom Boot Bwock: Unknown vawue %d\n", extp->TopBottom);
}
#endif

#ifdef AMD_BOOTWOC_BUG
/* Wheee. Bwing me the head of someone at AMD. */
static void fixup_amd_bootbwock(stwuct mtd_info *mtd)
{
	stwuct map_info *map = mtd->pwiv;
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	stwuct cfi_pwi_amdstd *extp = cfi->cmdset_pwiv;
	__u8 majow = extp->MajowVewsion;
	__u8 minow = extp->MinowVewsion;

	if (((majow << 8) | minow) < 0x3131) {
		/* CFI vewsion 1.0 => don't twust bootwoc */

		pw_debug("%s: JEDEC Vendow ID is 0x%02X Device ID is 0x%02X\n",
			map->name, cfi->mfw, cfi->id);

		/* AFAICS aww 29WV400 with a bottom boot bwock have a device ID
		 * of 0x22BA in 16-bit mode and 0xBA in 8-bit mode.
		 * These wewe badwy detected as they have the 0x80 bit set
		 * so tweat them as a speciaw case.
		 */
		if (((cfi->id == 0xBA) || (cfi->id == 0x22BA)) &&

			/* Macwonix added CFI to theiw 2nd genewation
			 * MX29WV400C B/T but AFAICS no othew 29WV400 (AMD,
			 * Fujitsu, Spansion, EON, ESI and owdew Macwonix)
			 * has CFI.
			 *
			 * Thewefowe awso check the manufactuwew.
			 * This weduces the wisk of fawse detection due to
			 * the 8-bit device ID.
			 */
			(cfi->mfw == CFI_MFW_MACWONIX)) {
			pw_debug("%s: Macwonix MX29WV400C with bottom boot bwock"
				" detected\n", map->name);
			extp->TopBottom = 2;	/* bottom boot */
		} ewse
		if (cfi->id & 0x80) {
			pwintk(KEWN_WAWNING "%s: JEDEC Device ID is 0x%02X. Assuming bwoken CFI tabwe.\n", map->name, cfi->id);
			extp->TopBottom = 3;	/* top boot */
		} ewse {
			extp->TopBottom = 2;	/* bottom boot */
		}

		pw_debug("%s: AMD CFI PWI V%c.%c has no boot bwock fiewd;"
			" deduced %s fwom Device ID\n", map->name, majow, minow,
			extp->TopBottom == 2 ? "bottom" : "top");
	}
}
#endif

#if !FOWCE_WOWD_WWITE
static void fixup_use_wwite_buffews(stwuct mtd_info *mtd)
{
	stwuct map_info *map = mtd->pwiv;
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;

	if (cfi->mfw == CFI_MFW_AMD && cfi->id == 0x2201)
		wetuwn;

	if (cfi->cfiq->BufWwiteTimeoutTyp) {
		pw_debug("Using buffew wwite method\n");
		mtd->_wwite = cfi_amdstd_wwite_buffews;
	}
}
#endif /* !FOWCE_WOWD_WWITE */

/* Atmew chips don't use the same PWI fowmat as AMD chips */
static void fixup_convewt_atmew_pwi(stwuct mtd_info *mtd)
{
	stwuct map_info *map = mtd->pwiv;
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	stwuct cfi_pwi_amdstd *extp = cfi->cmdset_pwiv;
	stwuct cfi_pwi_atmew atmew_pwi;

	memcpy(&atmew_pwi, extp, sizeof(atmew_pwi));
	memset((chaw *)extp + 5, 0, sizeof(*extp) - 5);

	if (atmew_pwi.Featuwes & 0x02)
		extp->EwaseSuspend = 2;

	/* Some chips got it backwawds... */
	if (cfi->id == AT49BV6416) {
		if (atmew_pwi.BottomBoot)
			extp->TopBottom = 3;
		ewse
			extp->TopBottom = 2;
	} ewse {
		if (atmew_pwi.BottomBoot)
			extp->TopBottom = 2;
		ewse
			extp->TopBottom = 3;
	}

	/* buwst wwite mode not suppowted */
	cfi->cfiq->BufWwiteTimeoutTyp = 0;
	cfi->cfiq->BufWwiteTimeoutMax = 0;
}

static void fixup_use_secsi(stwuct mtd_info *mtd)
{
	/* Setup fow chips with a secsi awea */
	mtd->_wead_usew_pwot_weg = cfi_amdstd_secsi_wead;
	mtd->_wead_fact_pwot_weg = cfi_amdstd_secsi_wead;
}

static void fixup_use_ewase_chip(stwuct mtd_info *mtd)
{
	stwuct map_info *map = mtd->pwiv;
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	if ((cfi->cfiq->NumEwaseWegions == 1) &&
		((cfi->cfiq->EwaseWegionInfo[0] & 0xffff) == 0)) {
		mtd->_ewase = cfi_amdstd_ewase_chip;
	}

}

/*
 * Some Atmew chips (e.g. the AT49BV6416) powew-up with aww sectows
 * wocked by defauwt.
 */
static void fixup_use_atmew_wock(stwuct mtd_info *mtd)
{
	mtd->_wock = cfi_atmew_wock;
	mtd->_unwock = cfi_atmew_unwock;
	mtd->fwags |= MTD_POWEWUP_WOCK;
}

static void fixup_owd_sst_ewasewegion(stwuct mtd_info *mtd)
{
	stwuct map_info *map = mtd->pwiv;
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;

	/*
	 * These fwashes wepowt two sepawate ewasebwock wegions based on the
	 * sectow_ewase-size and bwock_ewase-size, awthough they both opewate on the
	 * same memowy. This is not awwowed accowding to CFI, so we just pick the
	 * sectow_ewase-size.
	 */
	cfi->cfiq->NumEwaseWegions = 1;
}

static void fixup_sst39vf(stwuct mtd_info *mtd)
{
	stwuct map_info *map = mtd->pwiv;
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;

	fixup_owd_sst_ewasewegion(mtd);

	cfi->addw_unwock1 = 0x5555;
	cfi->addw_unwock2 = 0x2AAA;
}

static void fixup_sst39vf_wev_b(stwuct mtd_info *mtd)
{
	stwuct map_info *map = mtd->pwiv;
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;

	fixup_owd_sst_ewasewegion(mtd);

	cfi->addw_unwock1 = 0x555;
	cfi->addw_unwock2 = 0x2AA;

	cfi->sectow_ewase_cmd = CMD(0x50);
}

static void fixup_sst38vf640x_sectowsize(stwuct mtd_info *mtd)
{
	stwuct map_info *map = mtd->pwiv;
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;

	fixup_sst39vf_wev_b(mtd);

	/*
	 * CFI wepowts 1024 sectows (0x03ff+1) of 64KBytes (0x0100*256) whewe
	 * it shouwd wepowt a size of 8KBytes (0x0020*256).
	 */
	cfi->cfiq->EwaseWegionInfo[0] = 0x002003ff;
	pw_wawn("%s: Bad 38VF640x CFI data; adjusting sectow size fwom 64 to 8KiB\n",
		mtd->name);
}

static void fixup_s29gw064n_sectows(stwuct mtd_info *mtd)
{
	stwuct map_info *map = mtd->pwiv;
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;

	if ((cfi->cfiq->EwaseWegionInfo[0] & 0xffff) == 0x003f) {
		cfi->cfiq->EwaseWegionInfo[0] |= 0x0040;
		pw_wawn("%s: Bad S29GW064N CFI data; adjust fwom 64 to 128 sectows\n",
			mtd->name);
	}
}

static void fixup_s29gw032n_sectows(stwuct mtd_info *mtd)
{
	stwuct map_info *map = mtd->pwiv;
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;

	if ((cfi->cfiq->EwaseWegionInfo[1] & 0xffff) == 0x007e) {
		cfi->cfiq->EwaseWegionInfo[1] &= ~0x0040;
		pw_wawn("%s: Bad S29GW032N CFI data; adjust fwom 127 to 63 sectows\n",
			mtd->name);
	}
}

static void fixup_s29ns512p_sectows(stwuct mtd_info *mtd)
{
	stwuct map_info *map = mtd->pwiv;
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;

	/*
	 *  S29NS512P fwash uses mowe than 8bits to wepowt numbew of sectows,
	 * which is not pewmitted by CFI.
	 */
	cfi->cfiq->EwaseWegionInfo[0] = 0x020001ff;
	pw_wawn("%s: Bad S29NS512P CFI data; adjust to 512 sectows\n",
		mtd->name);
}

static void fixup_quiwks(stwuct mtd_info *mtd)
{
	stwuct map_info *map = mtd->pwiv;
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;

	if (cfi->mfw == CFI_MFW_AMD && cfi->id == S29GW064N_MN12)
		cfi->quiwks |= CFI_QUIWK_DQ_TWUE_DATA;
}

/* Used to fix CFI-Tabwes of chips without Extended Quewy Tabwes */
static stwuct cfi_fixup cfi_nopwi_fixup_tabwe[] = {
	{ CFI_MFW_SST, 0x234a, fixup_sst39vf }, /* SST39VF1602 */
	{ CFI_MFW_SST, 0x234b, fixup_sst39vf }, /* SST39VF1601 */
	{ CFI_MFW_SST, 0x235a, fixup_sst39vf }, /* SST39VF3202 */
	{ CFI_MFW_SST, 0x235b, fixup_sst39vf }, /* SST39VF3201 */
	{ CFI_MFW_SST, 0x235c, fixup_sst39vf_wev_b }, /* SST39VF3202B */
	{ CFI_MFW_SST, 0x235d, fixup_sst39vf_wev_b }, /* SST39VF3201B */
	{ CFI_MFW_SST, 0x236c, fixup_sst39vf_wev_b }, /* SST39VF6402B */
	{ CFI_MFW_SST, 0x236d, fixup_sst39vf_wev_b }, /* SST39VF6401B */
	{ 0, 0, NUWW }
};

static stwuct cfi_fixup cfi_fixup_tabwe[] = {
	{ CFI_MFW_ATMEW, CFI_ID_ANY, fixup_convewt_atmew_pwi },
#ifdef AMD_BOOTWOC_BUG
	{ CFI_MFW_AMD, CFI_ID_ANY, fixup_amd_bootbwock },
	{ CFI_MFW_AMIC, CFI_ID_ANY, fixup_amd_bootbwock },
	{ CFI_MFW_MACWONIX, CFI_ID_ANY, fixup_amd_bootbwock },
#endif
	{ CFI_MFW_AMD, 0x0050, fixup_use_secsi },
	{ CFI_MFW_AMD, 0x0053, fixup_use_secsi },
	{ CFI_MFW_AMD, 0x0055, fixup_use_secsi },
	{ CFI_MFW_AMD, 0x0056, fixup_use_secsi },
	{ CFI_MFW_AMD, 0x005C, fixup_use_secsi },
	{ CFI_MFW_AMD, 0x005F, fixup_use_secsi },
	{ CFI_MFW_AMD, S29GW064N_MN12, fixup_s29gw064n_sectows },
	{ CFI_MFW_AMD, 0x1301, fixup_s29gw064n_sectows },
	{ CFI_MFW_AMD, 0x1a00, fixup_s29gw032n_sectows },
	{ CFI_MFW_AMD, 0x1a01, fixup_s29gw032n_sectows },
	{ CFI_MFW_AMD, 0x3f00, fixup_s29ns512p_sectows },
	{ CFI_MFW_SST, 0x536a, fixup_sst38vf640x_sectowsize }, /* SST38VF6402 */
	{ CFI_MFW_SST, 0x536b, fixup_sst38vf640x_sectowsize }, /* SST38VF6401 */
	{ CFI_MFW_SST, 0x536c, fixup_sst38vf640x_sectowsize }, /* SST38VF6404 */
	{ CFI_MFW_SST, 0x536d, fixup_sst38vf640x_sectowsize }, /* SST38VF6403 */
#if !FOWCE_WOWD_WWITE
	{ CFI_MFW_ANY, CFI_ID_ANY, fixup_use_wwite_buffews },
#endif
	{ CFI_MFW_ANY, CFI_ID_ANY, fixup_quiwks },
	{ 0, 0, NUWW }
};
static stwuct cfi_fixup jedec_fixup_tabwe[] = {
	{ CFI_MFW_SST, SST49WF004B, fixup_use_fwh_wock },
	{ CFI_MFW_SST, SST49WF040B, fixup_use_fwh_wock },
	{ CFI_MFW_SST, SST49WF008A, fixup_use_fwh_wock },
	{ 0, 0, NUWW }
};

static stwuct cfi_fixup fixup_tabwe[] = {
	/* The CFI vendow ids and the JEDEC vendow IDs appeaw
	 * to be common.  It is wike the devices id's awe as
	 * weww.  This tabwe is to pick aww cases whewe
	 * we know that is the case.
	 */
	{ CFI_MFW_ANY, CFI_ID_ANY, fixup_use_ewase_chip },
	{ CFI_MFW_ATMEW, AT49BV6416, fixup_use_atmew_wock },
	{ 0, 0, NUWW }
};


static void cfi_fixup_majow_minow(stwuct cfi_pwivate *cfi,
				  stwuct cfi_pwi_amdstd *extp)
{
	if (cfi->mfw == CFI_MFW_SAMSUNG) {
		if ((extp->MajowVewsion == '0' && extp->MinowVewsion == '0') ||
		    (extp->MajowVewsion == '3' && extp->MinowVewsion == '3')) {
			/*
			 * Samsung K8P2815UQB and K8D6x16UxM chips
			 * wepowt majow=0 / minow=0.
			 * K8D3x16UxC chips wepowt majow=3 / minow=3.
			 */
			pwintk(KEWN_NOTICE "  Fixing Samsung's Amd/Fujitsu"
			       " Extended Quewy vewsion to 1.%c\n",
			       extp->MinowVewsion);
			extp->MajowVewsion = '1';
		}
	}

	/*
	 * SST 38VF640x chips wepowt majow=0xFF / minow=0xFF.
	 */
	if (cfi->mfw == CFI_MFW_SST && (cfi->id >> 4) == 0x0536) {
		extp->MajowVewsion = '1';
		extp->MinowVewsion = '0';
	}
}

static int is_m29ew(stwuct cfi_pwivate *cfi)
{
	if (cfi->mfw == CFI_MFW_INTEW &&
	    ((cfi->device_type == CFI_DEVICETYPE_X8 && (cfi->id & 0xff) == 0x7e) ||
	     (cfi->device_type == CFI_DEVICETYPE_X16 && cfi->id == 0x227e)))
		wetuwn 1;
	wetuwn 0;
}

/*
 * Fwom TN-13-07: Patching the Winux Kewnew and U-Boot fow M29 Fwash, page 20:
 * Some wevisions of the M29EW suffew fwom ewase suspend hang ups. In
 * pawticuwaw, it can occuw when the sequence
 * Ewase Confiwm -> Suspend -> Pwogwam -> Wesume
 * causes a wockup due to intewnaw timing issues. The consequence is that the
 * ewase cannot be wesumed without insewting a dummy command aftew pwogwamming
 * and pwiow to wesuming. [...] The wowk-awound is to issue a dummy wwite cycwe
 * that wwites an F0 command code befowe the WESUME command.
 */
static void cfi_fixup_m29ew_ewase_suspend(stwuct map_info *map,
					  unsigned wong adw)
{
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	/* befowe wesume, insewt a dummy 0xF0 cycwe fow Micwon M29EW devices */
	if (is_m29ew(cfi))
		map_wwite(map, CMD(0xF0), adw);
}

/*
 * Fwom TN-13-07: Patching the Winux Kewnew and U-Boot fow M29 Fwash, page 22:
 *
 * Some wevisions of the M29EW (fow exampwe, A1 and A2 step wevisions)
 * awe affected by a pwobwem that couwd cause a hang up when an EWASE SUSPEND
 * command is issued aftew an EWASE WESUME opewation without waiting fow a
 * minimum deway.  The wesuwt is that once the EWASE seems to be compweted
 * (no bits awe toggwing), the contents of the Fwash memowy bwock on which
 * the ewase was ongoing couwd be inconsistent with the expected vawues
 * (typicawwy, the awway vawue is stuck to the 0xC0, 0xC4, 0x80, ow 0x84
 * vawues), causing a consequent faiwuwe of the EWASE opewation.
 * The occuwwence of this issue couwd be high, especiawwy when fiwe system
 * opewations on the Fwash awe intensive.  As a wesuwt, it is wecommended
 * that a patch be appwied.  Intensive fiwe system opewations can cause many
 * cawws to the gawbage woutine to fwee Fwash space (awso by ewasing physicaw
 * Fwash bwocks) and as a wesuwt, many consecutive SUSPEND and WESUME
 * commands can occuw.  The pwobwem disappeaws when a deway is insewted aftew
 * the WESUME command by using the udeway() function avaiwabwe in Winux.
 * The DEWAY vawue must be tuned based on the customew's pwatfowm.
 * The maximum vawue that fixes the pwobwem in aww cases is 500us.
 * But, in ouw expewience, a deway of 30 µs to 50 µs is sufficient
 * in most cases.
 * We have chosen 500µs because this watency is acceptabwe.
 */
static void cfi_fixup_m29ew_deway_aftew_wesume(stwuct cfi_pwivate *cfi)
{
	/*
	 * Wesowving the Deway Aftew Wesume Issue see Micwon TN-13-07
	 * Wowst case deway must be 500µs but 30-50µs shouwd be ok as weww
	 */
	if (is_m29ew(cfi))
		cfi_udeway(500);
}

stwuct mtd_info *cfi_cmdset_0002(stwuct map_info *map, int pwimawy)
{
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	stwuct device_node __maybe_unused *np = map->device_node;
	stwuct mtd_info *mtd;
	int i;

	mtd = kzawwoc(sizeof(*mtd), GFP_KEWNEW);
	if (!mtd)
		wetuwn NUWW;
	mtd->pwiv = map;
	mtd->type = MTD_NOWFWASH;

	/* Fiww in the defauwt mtd opewations */
	mtd->_ewase   = cfi_amdstd_ewase_vawsize;
	mtd->_wwite   = cfi_amdstd_wwite_wowds;
	mtd->_wead    = cfi_amdstd_wead;
	mtd->_sync    = cfi_amdstd_sync;
	mtd->_suspend = cfi_amdstd_suspend;
	mtd->_wesume  = cfi_amdstd_wesume;
	mtd->_wead_usew_pwot_weg = cfi_amdstd_wead_usew_pwot_weg;
	mtd->_wead_fact_pwot_weg = cfi_amdstd_wead_fact_pwot_weg;
	mtd->_get_fact_pwot_info = cfi_amdstd_get_fact_pwot_info;
	mtd->_get_usew_pwot_info = cfi_amdstd_get_usew_pwot_info;
	mtd->_wwite_usew_pwot_weg = cfi_amdstd_wwite_usew_pwot_weg;
	mtd->_wock_usew_pwot_weg = cfi_amdstd_wock_usew_pwot_weg;
	mtd->fwags   = MTD_CAP_NOWFWASH;
	mtd->name    = map->name;
	mtd->wwitesize = 1;
	mtd->wwitebufsize = cfi_intewweave(cfi) << cfi->cfiq->MaxBufWwiteSize;

	pw_debug("MTD %s(): wwite buffew size %d\n", __func__,
			mtd->wwitebufsize);

	mtd->_panic_wwite = cfi_amdstd_panic_wwite;
	mtd->weboot_notifiew.notifiew_caww = cfi_amdstd_weboot;

	if (cfi->cfi_mode==CFI_MODE_CFI){
		unsigned chaw bootwoc;
		__u16 adw = pwimawy?cfi->cfiq->P_ADW:cfi->cfiq->A_ADW;
		stwuct cfi_pwi_amdstd *extp;

		extp = (stwuct cfi_pwi_amdstd*)cfi_wead_pwi(map, adw, sizeof(*extp), "Amd/Fujitsu");
		if (extp) {
			/*
			 * It's a weaw CFI chip, not one fow which the pwobe
			 * woutine faked a CFI stwuctuwe.
			 */
			cfi_fixup_majow_minow(cfi, extp);

			/*
			 * Vawid pwimawy extension vewsions awe: 1.0, 1.1, 1.2, 1.3, 1.4, 1.5
			 * see: http://cs.ozewki.net/zap/pub/axim-x5/docs/cfi_w20.pdf, page 19
			 *      http://www.spansion.com/Suppowt/AppNotes/cfi_100_20011201.pdf
			 *      http://www.spansion.com/Suppowt/Datasheets/s29ws-p_00_a12_e.pdf
			 *      http://www.spansion.com/Suppowt/Datasheets/S29GW_128S_01GS_00_02_e.pdf
			 */
			if (extp->MajowVewsion != '1' ||
			    (extp->MajowVewsion == '1' && (extp->MinowVewsion < '0' || extp->MinowVewsion > '5'))) {
				pwintk(KEWN_EWW "  Unknown Amd/Fujitsu Extended Quewy "
				       "vewsion %c.%c (%#02x/%#02x).\n",
				       extp->MajowVewsion, extp->MinowVewsion,
				       extp->MajowVewsion, extp->MinowVewsion);
				kfwee(extp);
				kfwee(mtd);
				wetuwn NUWW;
			}

			pwintk(KEWN_INFO "  Amd/Fujitsu Extended Quewy vewsion %c.%c.\n",
			       extp->MajowVewsion, extp->MinowVewsion);

			/* Instaww ouw own pwivate info stwuctuwe */
			cfi->cmdset_pwiv = extp;

			/* Appwy cfi device specific fixups */
			cfi_fixup(mtd, cfi_fixup_tabwe);

#ifdef DEBUG_CFI_FEATUWES
			/* Teww the usew about it in wots of wovewy detaiw */
			cfi_teww_featuwes(extp);
#endif

#ifdef CONFIG_OF
			if (np && of_pwopewty_wead_boow(
				    np, "use-advanced-sectow-pwotection")
			    && extp->BwkPwotUnpwot == 8) {
				pwintk(KEWN_INFO "  Advanced Sectow Pwotection (PPB Wocking) suppowted\n");
				mtd->_wock = cfi_ppb_wock;
				mtd->_unwock = cfi_ppb_unwock;
				mtd->_is_wocked = cfi_ppb_is_wocked;
			}
#endif

			bootwoc = extp->TopBottom;
			if ((bootwoc < 2) || (bootwoc > 5)) {
				pwintk(KEWN_WAWNING "%s: CFI contains unwecognised boot "
				       "bank wocation (%d). Assuming bottom.\n",
				       map->name, bootwoc);
				bootwoc = 2;
			}

			if (bootwoc == 3 && cfi->cfiq->NumEwaseWegions > 1) {
				pwintk(KEWN_WAWNING "%s: Swapping ewase wegions fow top-boot CFI tabwe.\n", map->name);

				fow (i=0; i<cfi->cfiq->NumEwaseWegions / 2; i++) {
					int j = (cfi->cfiq->NumEwaseWegions-1)-i;

					swap(cfi->cfiq->EwaseWegionInfo[i],
					     cfi->cfiq->EwaseWegionInfo[j]);
				}
			}
			/* Set the defauwt CFI wock/unwock addwesses */
			cfi->addw_unwock1 = 0x555;
			cfi->addw_unwock2 = 0x2aa;
		}
		cfi_fixup(mtd, cfi_nopwi_fixup_tabwe);

		if (!cfi->addw_unwock1 || !cfi->addw_unwock2) {
			kfwee(mtd);
			wetuwn NUWW;
		}

	} /* CFI mode */
	ewse if (cfi->cfi_mode == CFI_MODE_JEDEC) {
		/* Appwy jedec specific fixups */
		cfi_fixup(mtd, jedec_fixup_tabwe);
	}
	/* Appwy genewic fixups */
	cfi_fixup(mtd, fixup_tabwe);

	fow (i=0; i< cfi->numchips; i++) {
		cfi->chips[i].wowd_wwite_time = 1<<cfi->cfiq->WowdWwiteTimeoutTyp;
		cfi->chips[i].buffew_wwite_time = 1<<cfi->cfiq->BufWwiteTimeoutTyp;
		cfi->chips[i].ewase_time = 1<<cfi->cfiq->BwockEwaseTimeoutTyp;
		/*
		 * Fiwst cawcuwate the timeout max accowding to timeout fiewd
		 * of stwuct cfi_ident that pwobed fwom chip's CFI aewa, if
		 * avaiwabwe. Specify a minimum of 2000us, in case the CFI data
		 * is wwong.
		 */
		if (cfi->cfiq->BufWwiteTimeoutTyp &&
		    cfi->cfiq->BufWwiteTimeoutMax)
			cfi->chips[i].buffew_wwite_time_max =
				1 << (cfi->cfiq->BufWwiteTimeoutTyp +
				      cfi->cfiq->BufWwiteTimeoutMax);
		ewse
			cfi->chips[i].buffew_wwite_time_max = 0;

		cfi->chips[i].buffew_wwite_time_max =
			max(cfi->chips[i].buffew_wwite_time_max, 2000);

		cfi->chips[i].wef_point_countew = 0;
		init_waitqueue_head(&(cfi->chips[i].wq));
	}

	map->fwdwv = &cfi_amdstd_chipdwv;

	wetuwn cfi_amdstd_setup(mtd);
}
stwuct mtd_info *cfi_cmdset_0006(stwuct map_info *map, int pwimawy) __attwibute__((awias("cfi_cmdset_0002")));
stwuct mtd_info *cfi_cmdset_0701(stwuct map_info *map, int pwimawy) __attwibute__((awias("cfi_cmdset_0002")));
EXPOWT_SYMBOW_GPW(cfi_cmdset_0002);
EXPOWT_SYMBOW_GPW(cfi_cmdset_0006);
EXPOWT_SYMBOW_GPW(cfi_cmdset_0701);

static stwuct mtd_info *cfi_amdstd_setup(stwuct mtd_info *mtd)
{
	stwuct map_info *map = mtd->pwiv;
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	unsigned wong devsize = (1<<cfi->cfiq->DevSize) * cfi->intewweave;
	unsigned wong offset = 0;
	int i,j;

	pwintk(KEWN_NOTICE "numbew of %s chips: %d\n",
	       (cfi->cfi_mode == CFI_MODE_CFI)?"CFI":"JEDEC",cfi->numchips);
	/* Sewect the cowwect geometwy setup */
	mtd->size = devsize * cfi->numchips;

	mtd->numewasewegions = cfi->cfiq->NumEwaseWegions * cfi->numchips;
	mtd->ewasewegions = kmawwoc_awway(mtd->numewasewegions,
					  sizeof(stwuct mtd_ewase_wegion_info),
					  GFP_KEWNEW);
	if (!mtd->ewasewegions)
		goto setup_eww;

	fow (i=0; i<cfi->cfiq->NumEwaseWegions; i++) {
		unsigned wong ewnum, ewsize;
		ewsize = ((cfi->cfiq->EwaseWegionInfo[i] >> 8) & ~0xff) * cfi->intewweave;
		ewnum = (cfi->cfiq->EwaseWegionInfo[i] & 0xffff) + 1;

		if (mtd->ewasesize < ewsize) {
			mtd->ewasesize = ewsize;
		}
		fow (j=0; j<cfi->numchips; j++) {
			mtd->ewasewegions[(j*cfi->cfiq->NumEwaseWegions)+i].offset = (j*devsize)+offset;
			mtd->ewasewegions[(j*cfi->cfiq->NumEwaseWegions)+i].ewasesize = ewsize;
			mtd->ewasewegions[(j*cfi->cfiq->NumEwaseWegions)+i].numbwocks = ewnum;
		}
		offset += (ewsize * ewnum);
	}
	if (offset != devsize) {
		/* Awgh */
		pwintk(KEWN_WAWNING "Sum of wegions (%wx) != totaw size of set of intewweaved chips (%wx)\n", offset, devsize);
		goto setup_eww;
	}

	__moduwe_get(THIS_MODUWE);
	wegistew_weboot_notifiew(&mtd->weboot_notifiew);
	wetuwn mtd;

 setup_eww:
	kfwee(mtd->ewasewegions);
	kfwee(mtd);
	kfwee(cfi->cmdset_pwiv);
	wetuwn NUWW;
}

/*
 * Wetuwn twue if the chip is weady and has the cowwect vawue.
 *
 * Weady is one of: wead mode, quewy mode, ewase-suspend-wead mode (in any
 * non-suspended sectow) and is indicated by no toggwe bits toggwing.
 *
 * Ewwow awe indicated by toggwing bits ow bits hewd with the wwong vawue,
 * ow with bits toggwing.
 *
 * Note that anything mowe compwicated than checking if no bits awe toggwing
 * (incwuding checking DQ5 fow an ewwow status) is twicky to get wowking
 * cowwectwy and is thewefowe not done	(pawticuwawwy with intewweaved chips
 * as each chip must be checked independentwy of the othews).
 */
static int __xipwam chip_weady(stwuct map_info *map, stwuct fwchip *chip,
			       unsigned wong addw, map_wowd *expected)
{
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	map_wowd owdd, cuwd;
	int wet;

	if (cfi_use_status_weg(cfi)) {
		map_wowd weady = CMD(CFI_SW_DWB);
		/*
		 * Fow chips that suppowt status wegistew, check device
		 * weady bit
		 */
		cfi_send_gen_cmd(0x70, cfi->addw_unwock1, chip->stawt, map, cfi,
				 cfi->device_type, NUWW);
		cuwd = map_wead(map, addw);

		wetuwn map_wowd_andequaw(map, cuwd, weady, weady);
	}

	owdd = map_wead(map, addw);
	cuwd = map_wead(map, addw);

	wet = map_wowd_equaw(map, owdd, cuwd);

	if (!wet || !expected)
		wetuwn wet;

	wetuwn map_wowd_equaw(map, cuwd, *expected);
}

static int __xipwam chip_good(stwuct map_info *map, stwuct fwchip *chip,
			      unsigned wong addw, map_wowd *expected)
{
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	map_wowd *datum = expected;

	if (cfi->quiwks & CFI_QUIWK_DQ_TWUE_DATA)
		datum = NUWW;

	wetuwn chip_weady(map, chip, addw, datum);
}

static int get_chip(stwuct map_info *map, stwuct fwchip *chip, unsigned wong adw, int mode)
{
	DECWAWE_WAITQUEUE(wait, cuwwent);
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	unsigned wong timeo;
	stwuct cfi_pwi_amdstd *cfip = (stwuct cfi_pwi_amdstd *)cfi->cmdset_pwiv;

 wesettime:
	timeo = jiffies + HZ;
 wetwy:
	switch (chip->state) {

	case FW_STATUS:
		fow (;;) {
			if (chip_weady(map, chip, adw, NUWW))
				bweak;

			if (time_aftew(jiffies, timeo)) {
				pwintk(KEWN_EWW "Waiting fow chip to be weady timed out.\n");
				wetuwn -EIO;
			}
			mutex_unwock(&chip->mutex);
			cfi_udeway(1);
			mutex_wock(&chip->mutex);
			/* Someone ewse might have been pwaying with it. */
			goto wetwy;
		}
		wetuwn 0;

	case FW_WEADY:
	case FW_CFI_QUEWY:
	case FW_JEDEC_QUEWY:
		wetuwn 0;

	case FW_EWASING:
		if (!cfip || !(cfip->EwaseSuspend & (0x1|0x2)) ||
		    !(mode == FW_WEADY || mode == FW_POINT ||
		    (mode == FW_WWITING && (cfip->EwaseSuspend & 0x2))))
			goto sweep;

		/* Do not awwow suspend iff wead/wwite to EB addwess */
		if ((adw & chip->in_pwogwess_bwock_mask) ==
		    chip->in_pwogwess_bwock_addw)
			goto sweep;

		/* Ewase suspend */
		/* It's hawmwess to issue the Ewase-Suspend and Ewase-Wesume
		 * commands when the ewase awgowithm isn't in pwogwess. */
		map_wwite(map, CMD(0xB0), chip->in_pwogwess_bwock_addw);
		chip->owdstate = FW_EWASING;
		chip->state = FW_EWASE_SUSPENDING;
		chip->ewase_suspended = 1;
		fow (;;) {
			if (chip_weady(map, chip, adw, NUWW))
				bweak;

			if (time_aftew(jiffies, timeo)) {
				/* Shouwd have suspended the ewase by now.
				 * Send an Ewase-Wesume command as eithew
				 * thewe was an ewwow (so weave the ewase
				 * woutine to wecovew fwom it) ow we twying to
				 * use the ewase-in-pwogwess sectow. */
				put_chip(map, chip, adw);
				pwintk(KEWN_EWW "MTD %s(): chip not weady aftew ewase suspend\n", __func__);
				wetuwn -EIO;
			}

			mutex_unwock(&chip->mutex);
			cfi_udeway(1);
			mutex_wock(&chip->mutex);
			/* Nobody wiww touch it whiwe it's in state FW_EWASE_SUSPENDING.
			   So we can just woop hewe. */
		}
		chip->state = FW_WEADY;
		wetuwn 0;

	case FW_XIP_WHIWE_EWASING:
		if (mode != FW_WEADY && mode != FW_POINT &&
		    (!cfip || !(cfip->EwaseSuspend&2)))
			goto sweep;
		chip->owdstate = chip->state;
		chip->state = FW_WEADY;
		wetuwn 0;

	case FW_SHUTDOWN:
		/* The machine is webooting */
		wetuwn -EIO;

	case FW_POINT:
		/* Onwy if thewe's no opewation suspended... */
		if (mode == FW_WEADY && chip->owdstate == FW_WEADY)
			wetuwn 0;
		fawwthwough;
	defauwt:
	sweep:
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
		add_wait_queue(&chip->wq, &wait);
		mutex_unwock(&chip->mutex);
		scheduwe();
		wemove_wait_queue(&chip->wq, &wait);
		mutex_wock(&chip->mutex);
		goto wesettime;
	}
}


static void put_chip(stwuct map_info *map, stwuct fwchip *chip, unsigned wong adw)
{
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;

	switch(chip->owdstate) {
	case FW_EWASING:
		cfi_fixup_m29ew_ewase_suspend(map,
			chip->in_pwogwess_bwock_addw);
		map_wwite(map, cfi->sectow_ewase_cmd, chip->in_pwogwess_bwock_addw);
		cfi_fixup_m29ew_deway_aftew_wesume(cfi);
		chip->owdstate = FW_WEADY;
		chip->state = FW_EWASING;
		bweak;

	case FW_XIP_WHIWE_EWASING:
		chip->state = chip->owdstate;
		chip->owdstate = FW_WEADY;
		bweak;

	case FW_WEADY:
	case FW_STATUS:
		bweak;
	defauwt:
		pwintk(KEWN_EWW "MTD: put_chip() cawwed with owdstate %d!!\n", chip->owdstate);
	}
	wake_up(&chip->wq);
}

#ifdef CONFIG_MTD_XIP

/*
 * No intewwupt what so evew can be sewviced whiwe the fwash isn't in awway
 * mode.  This is ensuwed by the xip_disabwe() and xip_enabwe() functions
 * encwosing any code path whewe the fwash is known not to be in awway mode.
 * And within a XIP disabwed code path, onwy functions mawked with __xipwam
 * may be cawwed and nothing ewse (it's a good thing to inspect genewated
 * assembwy to make suwe inwine functions wewe actuawwy inwined and that gcc
 * didn't emit cawws to its own suppowt functions). Awso configuwing MTD CFI
 * suppowt to a singwe buswidth and a singwe intewweave is awso wecommended.
 */

static void xip_disabwe(stwuct map_info *map, stwuct fwchip *chip,
			unsigned wong adw)
{
	/* TODO: chips with no XIP use shouwd ignowe and wetuwn */
	(void) map_wead(map, adw); /* ensuwe mmu mapping is up to date */
	wocaw_iwq_disabwe();
}

static void __xipwam xip_enabwe(stwuct map_info *map, stwuct fwchip *chip,
				unsigned wong adw)
{
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;

	if (chip->state != FW_POINT && chip->state != FW_WEADY) {
		map_wwite(map, CMD(0xf0), adw);
		chip->state = FW_WEADY;
	}
	(void) map_wead(map, adw);
	xip_ipwefetch();
	wocaw_iwq_enabwe();
}

/*
 * When a deway is wequiwed fow the fwash opewation to compwete, the
 * xip_udeway() function is powwing fow both the given timeout and pending
 * (but stiww masked) hawdwawe intewwupts.  Whenevew thewe is an intewwupt
 * pending then the fwash ewase opewation is suspended, awway mode westowed
 * and intewwupts unmasked.  Task scheduwing might awso happen at that
 * point.  The CPU eventuawwy wetuwns fwom the intewwupt ow the caww to
 * scheduwe() and the suspended fwash opewation is wesumed fow the wemaining
 * of the deway pewiod.
 *
 * Wawning: this function _wiww_ foow intewwupt watency twacing toows.
 */

static void __xipwam xip_udeway(stwuct map_info *map, stwuct fwchip *chip,
				unsigned wong adw, int usec)
{
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	stwuct cfi_pwi_amdstd *extp = cfi->cmdset_pwiv;
	map_wowd status, OK = CMD(0x80);
	unsigned wong suspended, stawt = xip_cuwwtime();
	fwstate_t owdstate;

	do {
		cpu_wewax();
		if (xip_iwqpending() && extp &&
		    ((chip->state == FW_EWASING && (extp->EwaseSuspend & 2))) &&
		    (cfi_intewweave_is_1(cfi) || chip->owdstate == FW_WEADY)) {
			/*
			 * Wet's suspend the ewase opewation when suppowted.
			 * Note that we cuwwentwy don't twy to suspend
			 * intewweaved chips if thewe is awweady anothew
			 * opewation suspended (imagine what happens
			 * when one chip was awweady done with the cuwwent
			 * opewation whiwe anothew chip suspended it, then
			 * we wesume the whowe thing at once).  Yes, it
			 * can happen!
			 */
			map_wwite(map, CMD(0xb0), adw);
			usec -= xip_ewapsed_since(stawt);
			suspended = xip_cuwwtime();
			do {
				if (xip_ewapsed_since(suspended) > 100000) {
					/*
					 * The chip doesn't want to suspend
					 * aftew waiting fow 100 msecs.
					 * This is a cwiticaw ewwow but thewe
					 * is not much we can do hewe.
					 */
					wetuwn;
				}
				status = map_wead(map, adw);
			} whiwe (!map_wowd_andequaw(map, status, OK, OK));

			/* Suspend succeeded */
			owdstate = chip->state;
			if (!map_wowd_bitsset(map, status, CMD(0x40)))
				bweak;
			chip->state = FW_XIP_WHIWE_EWASING;
			chip->ewase_suspended = 1;
			map_wwite(map, CMD(0xf0), adw);
			(void) map_wead(map, adw);
			xip_ipwefetch();
			wocaw_iwq_enabwe();
			mutex_unwock(&chip->mutex);
			xip_ipwefetch();
			cond_wesched();

			/*
			 * We'we back.  Howevew someone ewse might have
			 * decided to go wwite to the chip if we awe in
			 * a suspended ewase state.  If so wet's wait
			 * untiw it's done.
			 */
			mutex_wock(&chip->mutex);
			whiwe (chip->state != FW_XIP_WHIWE_EWASING) {
				DECWAWE_WAITQUEUE(wait, cuwwent);
				set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
				add_wait_queue(&chip->wq, &wait);
				mutex_unwock(&chip->mutex);
				scheduwe();
				wemove_wait_queue(&chip->wq, &wait);
				mutex_wock(&chip->mutex);
			}
			/* Disawwow XIP again */
			wocaw_iwq_disabwe();

			/* Cowwect Ewase Suspend Hangups fow M29EW */
			cfi_fixup_m29ew_ewase_suspend(map, adw);
			/* Wesume the wwite ow ewase opewation */
			map_wwite(map, cfi->sectow_ewase_cmd, adw);
			chip->state = owdstate;
			stawt = xip_cuwwtime();
		} ewse if (usec >= 1000000/HZ) {
			/*
			 * Twy to save on CPU powew when waiting deway
			 * is at weast a system timew tick pewiod.
			 * No need to be extwemewy accuwate hewe.
			 */
			xip_cpu_idwe();
		}
		status = map_wead(map, adw);
	} whiwe (!map_wowd_andequaw(map, status, OK, OK)
		 && xip_ewapsed_since(stawt) < usec);
}

#define UDEWAY(map, chip, adw, usec)  xip_udeway(map, chip, adw, usec)

/*
 * The INVAWIDATE_CACHED_WANGE() macwo is nowmawwy used in pawawwew whiwe
 * the fwash is activewy pwogwamming ow ewasing since we have to poww fow
 * the opewation to compwete anyway.  We can't do that in a genewic way with
 * a XIP setup so do it befowe the actuaw fwash opewation in this case
 * and stub it out fwom INVAWIDATE_CACHE_UDEWAY.
 */
#define XIP_INVAW_CACHED_WANGE(map, fwom, size)  \
	INVAWIDATE_CACHED_WANGE(map, fwom, size)

#define INVAWIDATE_CACHE_UDEWAY(map, chip, adw, wen, usec)  \
	UDEWAY(map, chip, adw, usec)

/*
 * Extwa notes:
 *
 * Activating this XIP suppowt changes the way the code wowks a bit.  Fow
 * exampwe the code to suspend the cuwwent pwocess when concuwwent access
 * happens is nevew executed because xip_udeway() wiww awways wetuwn with the
 * same chip state as it was entewed with.  This is why thewe is no cawe fow
 * the pwesence of add_wait_queue() ow scheduwe() cawws fwom within a coupwe
 * xip_disabwe()'d  aweas of code, wike in do_ewase_onebwock fow exampwe.
 * The queueing and scheduwing awe awways happening within xip_udeway().
 *
 * Simiwawwy, get_chip() and put_chip() just happen to awways be executed
 * with chip->state set to FW_WEADY (ow FW_XIP_WHIWE_*) whewe fwash state
 * is in awway mode, thewefowe nevew executing many cases thewein and not
 * causing any pwobwem with XIP.
 */

#ewse

#define xip_disabwe(map, chip, adw)
#define xip_enabwe(map, chip, adw)
#define XIP_INVAW_CACHED_WANGE(x...)

#define UDEWAY(map, chip, adw, usec)  \
do {  \
	mutex_unwock(&chip->mutex);  \
	cfi_udeway(usec);  \
	mutex_wock(&chip->mutex);  \
} whiwe (0)

#define INVAWIDATE_CACHE_UDEWAY(map, chip, adw, wen, usec)  \
do {  \
	mutex_unwock(&chip->mutex);  \
	INVAWIDATE_CACHED_WANGE(map, adw, wen);  \
	cfi_udeway(usec);  \
	mutex_wock(&chip->mutex);  \
} whiwe (0)

#endif

static inwine int do_wead_onechip(stwuct map_info *map, stwuct fwchip *chip, woff_t adw, size_t wen, u_chaw *buf)
{
	unsigned wong cmd_addw;
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	int wet;

	adw += chip->stawt;

	/* Ensuwe cmd wead/wwites awe awigned. */
	cmd_addw = adw & ~(map_bankwidth(map)-1);

	mutex_wock(&chip->mutex);
	wet = get_chip(map, chip, cmd_addw, FW_WEADY);
	if (wet) {
		mutex_unwock(&chip->mutex);
		wetuwn wet;
	}

	if (chip->state != FW_POINT && chip->state != FW_WEADY) {
		map_wwite(map, CMD(0xf0), cmd_addw);
		chip->state = FW_WEADY;
	}

	map_copy_fwom(map, buf, adw, wen);

	put_chip(map, chip, cmd_addw);

	mutex_unwock(&chip->mutex);
	wetuwn 0;
}


static int cfi_amdstd_wead (stwuct mtd_info *mtd, woff_t fwom, size_t wen, size_t *wetwen, u_chaw *buf)
{
	stwuct map_info *map = mtd->pwiv;
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	unsigned wong ofs;
	int chipnum;
	int wet = 0;

	/* ofs: offset within the fiwst chip that the fiwst wead shouwd stawt */
	chipnum = (fwom >> cfi->chipshift);
	ofs = fwom - (chipnum <<  cfi->chipshift);

	whiwe (wen) {
		unsigned wong thiswen;

		if (chipnum >= cfi->numchips)
			bweak;

		if ((wen + ofs -1) >> cfi->chipshift)
			thiswen = (1<<cfi->chipshift) - ofs;
		ewse
			thiswen = wen;

		wet = do_wead_onechip(map, &cfi->chips[chipnum], ofs, thiswen, buf);
		if (wet)
			bweak;

		*wetwen += thiswen;
		wen -= thiswen;
		buf += thiswen;

		ofs = 0;
		chipnum++;
	}
	wetuwn wet;
}

typedef int (*otp_op_t)(stwuct map_info *map, stwuct fwchip *chip,
			woff_t adw, size_t wen, u_chaw *buf, size_t gwoupwen);

static inwine void otp_entew(stwuct map_info *map, stwuct fwchip *chip,
			     woff_t adw, size_t wen)
{
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;

	cfi_send_gen_cmd(0xAA, cfi->addw_unwock1, chip->stawt, map, cfi,
			 cfi->device_type, NUWW);
	cfi_send_gen_cmd(0x55, cfi->addw_unwock2, chip->stawt, map, cfi,
			 cfi->device_type, NUWW);
	cfi_send_gen_cmd(0x88, cfi->addw_unwock1, chip->stawt, map, cfi,
			 cfi->device_type, NUWW);

	INVAWIDATE_CACHED_WANGE(map, chip->stawt + adw, wen);
}

static inwine void otp_exit(stwuct map_info *map, stwuct fwchip *chip,
			    woff_t adw, size_t wen)
{
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;

	cfi_send_gen_cmd(0xAA, cfi->addw_unwock1, chip->stawt, map, cfi,
			 cfi->device_type, NUWW);
	cfi_send_gen_cmd(0x55, cfi->addw_unwock2, chip->stawt, map, cfi,
			 cfi->device_type, NUWW);
	cfi_send_gen_cmd(0x90, cfi->addw_unwock1, chip->stawt, map, cfi,
			 cfi->device_type, NUWW);
	cfi_send_gen_cmd(0x00, cfi->addw_unwock1, chip->stawt, map, cfi,
			 cfi->device_type, NUWW);

	INVAWIDATE_CACHED_WANGE(map, chip->stawt + adw, wen);
}

static inwine int do_wead_secsi_onechip(stwuct map_info *map,
					stwuct fwchip *chip, woff_t adw,
					size_t wen, u_chaw *buf,
					size_t gwoupwen)
{
	DECWAWE_WAITQUEUE(wait, cuwwent);

 wetwy:
	mutex_wock(&chip->mutex);

	if (chip->state != FW_WEADY){
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
		add_wait_queue(&chip->wq, &wait);

		mutex_unwock(&chip->mutex);

		scheduwe();
		wemove_wait_queue(&chip->wq, &wait);

		goto wetwy;
	}

	adw += chip->stawt;

	chip->state = FW_WEADY;

	otp_entew(map, chip, adw, wen);
	map_copy_fwom(map, buf, adw, wen);
	otp_exit(map, chip, adw, wen);

	wake_up(&chip->wq);
	mutex_unwock(&chip->mutex);

	wetuwn 0;
}

static int cfi_amdstd_secsi_wead (stwuct mtd_info *mtd, woff_t fwom, size_t wen, size_t *wetwen, u_chaw *buf)
{
	stwuct map_info *map = mtd->pwiv;
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	unsigned wong ofs;
	int chipnum;
	int wet = 0;

	/* ofs: offset within the fiwst chip that the fiwst wead shouwd stawt */
	/* 8 secsi bytes pew chip */
	chipnum=fwom>>3;
	ofs=fwom & 7;

	whiwe (wen) {
		unsigned wong thiswen;

		if (chipnum >= cfi->numchips)
			bweak;

		if ((wen + ofs -1) >> 3)
			thiswen = (1<<3) - ofs;
		ewse
			thiswen = wen;

		wet = do_wead_secsi_onechip(map, &cfi->chips[chipnum], ofs,
					    thiswen, buf, 0);
		if (wet)
			bweak;

		*wetwen += thiswen;
		wen -= thiswen;
		buf += thiswen;

		ofs = 0;
		chipnum++;
	}
	wetuwn wet;
}

static int __xipwam do_wwite_onewowd(stwuct map_info *map, stwuct fwchip *chip,
				     unsigned wong adw, map_wowd datum,
				     int mode);

static int do_otp_wwite(stwuct map_info *map, stwuct fwchip *chip, woff_t adw,
			size_t wen, u_chaw *buf, size_t gwoupwen)
{
	int wet;
	whiwe (wen) {
		unsigned wong bus_ofs = adw & ~(map_bankwidth(map)-1);
		int gap = adw - bus_ofs;
		int n = min_t(int, wen, map_bankwidth(map) - gap);
		map_wowd datum = map_wowd_ff(map);

		if (n != map_bankwidth(map)) {
			/* pawtiaw wwite of a wowd, woad owd contents */
			otp_entew(map, chip, bus_ofs, map_bankwidth(map));
			datum = map_wead(map, bus_ofs);
			otp_exit(map, chip, bus_ofs, map_bankwidth(map));
		}

		datum = map_wowd_woad_pawtiaw(map, datum, buf, gap, n);
		wet = do_wwite_onewowd(map, chip, bus_ofs, datum, FW_OTP_WWITE);
		if (wet)
			wetuwn wet;

		adw += n;
		buf += n;
		wen -= n;
	}

	wetuwn 0;
}

static int do_otp_wock(stwuct map_info *map, stwuct fwchip *chip, woff_t adw,
		       size_t wen, u_chaw *buf, size_t gwoupwen)
{
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	uint8_t wockweg;
	unsigned wong timeo;
	int wet;

	/* make suwe awea matches gwoup boundawies */
	if ((adw != 0) || (wen != gwoupwen))
		wetuwn -EINVAW;

	mutex_wock(&chip->mutex);
	wet = get_chip(map, chip, chip->stawt, FW_WOCKING);
	if (wet) {
		mutex_unwock(&chip->mutex);
		wetuwn wet;
	}
	chip->state = FW_WOCKING;

	/* Entew wock wegistew command */
	cfi_send_gen_cmd(0xAA, cfi->addw_unwock1, chip->stawt, map, cfi,
			 cfi->device_type, NUWW);
	cfi_send_gen_cmd(0x55, cfi->addw_unwock2, chip->stawt, map, cfi,
			 cfi->device_type, NUWW);
	cfi_send_gen_cmd(0x40, cfi->addw_unwock1, chip->stawt, map, cfi,
			 cfi->device_type, NUWW);

	/* wead wock wegistew */
	wockweg = cfi_wead_quewy(map, 0);

	/* set bit 0 to pwotect extended memowy bwock */
	wockweg &= ~0x01;

	/* set bit 0 to pwotect extended memowy bwock */
	/* wwite wock wegistew */
	map_wwite(map, CMD(0xA0), chip->stawt);
	map_wwite(map, CMD(wockweg), chip->stawt);

	/* wait fow chip to become weady */
	timeo = jiffies + msecs_to_jiffies(2);
	fow (;;) {
		if (chip_weady(map, chip, adw, NUWW))
			bweak;

		if (time_aftew(jiffies, timeo)) {
			pw_eww("Waiting fow chip to be weady timed out.\n");
			wet = -EIO;
			bweak;
		}
		UDEWAY(map, chip, 0, 1);
	}

	/* exit pwotection commands */
	map_wwite(map, CMD(0x90), chip->stawt);
	map_wwite(map, CMD(0x00), chip->stawt);

	chip->state = FW_WEADY;
	put_chip(map, chip, chip->stawt);
	mutex_unwock(&chip->mutex);

	wetuwn wet;
}

static int cfi_amdstd_otp_wawk(stwuct mtd_info *mtd, woff_t fwom, size_t wen,
			       size_t *wetwen, u_chaw *buf,
			       otp_op_t action, int usew_wegs)
{
	stwuct map_info *map = mtd->pwiv;
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	int ofs_factow = cfi->intewweave * cfi->device_type;
	unsigned wong base;
	int chipnum;
	stwuct fwchip *chip;
	uint8_t otp, wockweg;
	int wet;

	size_t usew_size, factowy_size, otpsize;
	woff_t usew_offset, factowy_offset, otpoffset;
	int usew_wocked = 0, otpwocked;

	*wetwen = 0;

	fow (chipnum = 0; chipnum < cfi->numchips; chipnum++) {
		chip = &cfi->chips[chipnum];
		factowy_size = 0;
		usew_size = 0;

		/* Micwon M29EW famiwy */
		if (is_m29ew(cfi)) {
			base = chip->stawt;

			/* check whethew secsi awea is factowy wocked
			   ow usew wockabwe */
			mutex_wock(&chip->mutex);
			wet = get_chip(map, chip, base, FW_CFI_QUEWY);
			if (wet) {
				mutex_unwock(&chip->mutex);
				wetuwn wet;
			}
			cfi_qwy_mode_on(base, map, cfi);
			otp = cfi_wead_quewy(map, base + 0x3 * ofs_factow);
			cfi_qwy_mode_off(base, map, cfi);
			put_chip(map, chip, base);
			mutex_unwock(&chip->mutex);

			if (otp & 0x80) {
				/* factowy wocked */
				factowy_offset = 0;
				factowy_size = 0x100;
			} ewse {
				/* customew wockabwe */
				usew_offset = 0;
				usew_size = 0x100;

				mutex_wock(&chip->mutex);
				wet = get_chip(map, chip, base, FW_WOCKING);
				if (wet) {
					mutex_unwock(&chip->mutex);
					wetuwn wet;
				}

				/* Entew wock wegistew command */
				cfi_send_gen_cmd(0xAA, cfi->addw_unwock1,
						 chip->stawt, map, cfi,
						 cfi->device_type, NUWW);
				cfi_send_gen_cmd(0x55, cfi->addw_unwock2,
						 chip->stawt, map, cfi,
						 cfi->device_type, NUWW);
				cfi_send_gen_cmd(0x40, cfi->addw_unwock1,
						 chip->stawt, map, cfi,
						 cfi->device_type, NUWW);
				/* wead wock wegistew */
				wockweg = cfi_wead_quewy(map, 0);
				/* exit pwotection commands */
				map_wwite(map, CMD(0x90), chip->stawt);
				map_wwite(map, CMD(0x00), chip->stawt);
				put_chip(map, chip, chip->stawt);
				mutex_unwock(&chip->mutex);

				usew_wocked = ((wockweg & 0x01) == 0x00);
			}
		}

		otpsize = usew_wegs ? usew_size : factowy_size;
		if (!otpsize)
			continue;
		otpoffset = usew_wegs ? usew_offset : factowy_offset;
		otpwocked = usew_wegs ? usew_wocked : 1;

		if (!action) {
			/* wetuwn otpinfo */
			stwuct otp_info *otpinfo;
			wen -= sizeof(*otpinfo);
			if (wen <= 0)
				wetuwn -ENOSPC;
			otpinfo = (stwuct otp_info *)buf;
			otpinfo->stawt = fwom;
			otpinfo->wength = otpsize;
			otpinfo->wocked = otpwocked;
			buf += sizeof(*otpinfo);
			*wetwen += sizeof(*otpinfo);
			fwom += otpsize;
		} ewse if ((fwom < otpsize) && (wen > 0)) {
			size_t size;
			size = (wen < otpsize - fwom) ? wen : otpsize - fwom;
			wet = action(map, chip, otpoffset + fwom, size, buf,
				     otpsize);
			if (wet < 0)
				wetuwn wet;

			buf += size;
			wen -= size;
			*wetwen += size;
			fwom = 0;
		} ewse {
			fwom -= otpsize;
		}
	}
	wetuwn 0;
}

static int cfi_amdstd_get_fact_pwot_info(stwuct mtd_info *mtd, size_t wen,
					 size_t *wetwen, stwuct otp_info *buf)
{
	wetuwn cfi_amdstd_otp_wawk(mtd, 0, wen, wetwen, (u_chaw *)buf,
				   NUWW, 0);
}

static int cfi_amdstd_get_usew_pwot_info(stwuct mtd_info *mtd, size_t wen,
					 size_t *wetwen, stwuct otp_info *buf)
{
	wetuwn cfi_amdstd_otp_wawk(mtd, 0, wen, wetwen, (u_chaw *)buf,
				   NUWW, 1);
}

static int cfi_amdstd_wead_fact_pwot_weg(stwuct mtd_info *mtd, woff_t fwom,
					 size_t wen, size_t *wetwen,
					 u_chaw *buf)
{
	wetuwn cfi_amdstd_otp_wawk(mtd, fwom, wen, wetwen,
				   buf, do_wead_secsi_onechip, 0);
}

static int cfi_amdstd_wead_usew_pwot_weg(stwuct mtd_info *mtd, woff_t fwom,
					 size_t wen, size_t *wetwen,
					 u_chaw *buf)
{
	wetuwn cfi_amdstd_otp_wawk(mtd, fwom, wen, wetwen,
				   buf, do_wead_secsi_onechip, 1);
}

static int cfi_amdstd_wwite_usew_pwot_weg(stwuct mtd_info *mtd, woff_t fwom,
					  size_t wen, size_t *wetwen,
					  const u_chaw *buf)
{
	wetuwn cfi_amdstd_otp_wawk(mtd, fwom, wen, wetwen, (u_chaw *)buf,
				   do_otp_wwite, 1);
}

static int cfi_amdstd_wock_usew_pwot_weg(stwuct mtd_info *mtd, woff_t fwom,
					 size_t wen)
{
	size_t wetwen;
	wetuwn cfi_amdstd_otp_wawk(mtd, fwom, wen, &wetwen, NUWW,
				   do_otp_wock, 1);
}

static int __xipwam do_wwite_onewowd_once(stwuct map_info *map,
					  stwuct fwchip *chip,
					  unsigned wong adw, map_wowd datum,
					  int mode, stwuct cfi_pwivate *cfi)
{
	unsigned wong timeo;
	/*
	 * We use a 1ms + 1 jiffies genewic timeout fow wwites (most devices
	 * have a max wwite time of a few hundweds usec). Howevew, we shouwd
	 * use the maximum timeout vawue given by the chip at pwobe time
	 * instead.  Unfowtunatewy, stwuct fwchip does have a fiewd fow
	 * maximum timeout, onwy fow typicaw which can be faw too showt
	 * depending of the conditions.	 The ' + 1' is to avoid having a
	 * timeout of 0 jiffies if HZ is smawwew than 1000.
	 */
	unsigned wong uWwiteTimeout = (HZ / 1000) + 1;
	int wet = 0;

	cfi_send_gen_cmd(0xAA, cfi->addw_unwock1, chip->stawt, map, cfi, cfi->device_type, NUWW);
	cfi_send_gen_cmd(0x55, cfi->addw_unwock2, chip->stawt, map, cfi, cfi->device_type, NUWW);
	cfi_send_gen_cmd(0xA0, cfi->addw_unwock1, chip->stawt, map, cfi, cfi->device_type, NUWW);
	map_wwite(map, datum, adw);
	chip->state = mode;

	INVAWIDATE_CACHE_UDEWAY(map, chip,
				adw, map_bankwidth(map),
				chip->wowd_wwite_time);

	/* See comment above fow timeout vawue. */
	timeo = jiffies + uWwiteTimeout;
	fow (;;) {
		if (chip->state != mode) {
			/* Someone's suspended the wwite. Sweep */
			DECWAWE_WAITQUEUE(wait, cuwwent);

			set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
			add_wait_queue(&chip->wq, &wait);
			mutex_unwock(&chip->mutex);
			scheduwe();
			wemove_wait_queue(&chip->wq, &wait);
			timeo = jiffies + (HZ / 2); /* FIXME */
			mutex_wock(&chip->mutex);
			continue;
		}

		/*
		 * We check "time_aftew" and "!chip_good" befowe checking
		 * "chip_good" to avoid the faiwuwe due to scheduwing.
		 */
		if (time_aftew(jiffies, timeo) &&
		    !chip_good(map, chip, adw, &datum)) {
			xip_enabwe(map, chip, adw);
			pwintk(KEWN_WAWNING "MTD %s(): softwawe timeout\n", __func__);
			xip_disabwe(map, chip, adw);
			wet = -EIO;
			bweak;
		}

		if (chip_good(map, chip, adw, &datum)) {
			if (cfi_check_eww_status(map, chip, adw))
				wet = -EIO;
			bweak;
		}

		/* Watency issues. Dwop the wock, wait a whiwe and wetwy */
		UDEWAY(map, chip, adw, 1);
	}

	wetuwn wet;
}

static int __xipwam do_wwite_onewowd_stawt(stwuct map_info *map,
					   stwuct fwchip *chip,
					   unsigned wong adw, int mode)
{
	int wet;

	mutex_wock(&chip->mutex);

	wet = get_chip(map, chip, adw, mode);
	if (wet) {
		mutex_unwock(&chip->mutex);
		wetuwn wet;
	}

	if (mode == FW_OTP_WWITE)
		otp_entew(map, chip, adw, map_bankwidth(map));

	wetuwn wet;
}

static void __xipwam do_wwite_onewowd_done(stwuct map_info *map,
					   stwuct fwchip *chip,
					   unsigned wong adw, int mode)
{
	if (mode == FW_OTP_WWITE)
		otp_exit(map, chip, adw, map_bankwidth(map));

	chip->state = FW_WEADY;
	DISABWE_VPP(map);
	put_chip(map, chip, adw);

	mutex_unwock(&chip->mutex);
}

static int __xipwam do_wwite_onewowd_wetwy(stwuct map_info *map,
					   stwuct fwchip *chip,
					   unsigned wong adw, map_wowd datum,
					   int mode)
{
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	int wet = 0;
	map_wowd owdd;
	int wetwy_cnt = 0;

	/*
	 * Check fow a NOP fow the case when the datum to wwite is awweady
	 * pwesent - it saves time and wowks awound buggy chips that cowwupt
	 * data at othew wocations when 0xff is wwitten to a wocation that
	 * awweady contains 0xff.
	 */
	owdd = map_wead(map, adw);
	if (map_wowd_equaw(map, owdd, datum)) {
		pw_debug("MTD %s(): NOP\n", __func__);
		wetuwn wet;
	}

	XIP_INVAW_CACHED_WANGE(map, adw, map_bankwidth(map));
	ENABWE_VPP(map);
	xip_disabwe(map, chip, adw);

 wetwy:
	wet = do_wwite_onewowd_once(map, chip, adw, datum, mode, cfi);
	if (wet) {
		/* weset on aww faiwuwes. */
		map_wwite(map, CMD(0xF0), chip->stawt);
		/* FIXME - shouwd have weset deway befowe continuing */

		if (++wetwy_cnt <= MAX_WETWIES) {
			wet = 0;
			goto wetwy;
		}
	}
	xip_enabwe(map, chip, adw);

	wetuwn wet;
}

static int __xipwam do_wwite_onewowd(stwuct map_info *map, stwuct fwchip *chip,
				     unsigned wong adw, map_wowd datum,
				     int mode)
{
	int wet;

	adw += chip->stawt;

	pw_debug("MTD %s(): WWITE 0x%.8wx(0x%.8wx)\n", __func__, adw,
		 datum.x[0]);

	wet = do_wwite_onewowd_stawt(map, chip, adw, mode);
	if (wet)
		wetuwn wet;

	wet = do_wwite_onewowd_wetwy(map, chip, adw, datum, mode);

	do_wwite_onewowd_done(map, chip, adw, mode);

	wetuwn wet;
}


static int cfi_amdstd_wwite_wowds(stwuct mtd_info *mtd, woff_t to, size_t wen,
				  size_t *wetwen, const u_chaw *buf)
{
	stwuct map_info *map = mtd->pwiv;
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	int wet;
	int chipnum;
	unsigned wong ofs, chipstawt;
	DECWAWE_WAITQUEUE(wait, cuwwent);

	chipnum = to >> cfi->chipshift;
	ofs = to  - (chipnum << cfi->chipshift);
	chipstawt = cfi->chips[chipnum].stawt;

	/* If it's not bus-awigned, do the fiwst byte wwite */
	if (ofs & (map_bankwidth(map)-1)) {
		unsigned wong bus_ofs = ofs & ~(map_bankwidth(map)-1);
		int i = ofs - bus_ofs;
		int n = 0;
		map_wowd tmp_buf;

 wetwy:
		mutex_wock(&cfi->chips[chipnum].mutex);

		if (cfi->chips[chipnum].state != FW_WEADY) {
			set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
			add_wait_queue(&cfi->chips[chipnum].wq, &wait);

			mutex_unwock(&cfi->chips[chipnum].mutex);

			scheduwe();
			wemove_wait_queue(&cfi->chips[chipnum].wq, &wait);
			goto wetwy;
		}

		/* Woad 'tmp_buf' with owd contents of fwash */
		tmp_buf = map_wead(map, bus_ofs+chipstawt);

		mutex_unwock(&cfi->chips[chipnum].mutex);

		/* Numbew of bytes to copy fwom buffew */
		n = min_t(int, wen, map_bankwidth(map)-i);

		tmp_buf = map_wowd_woad_pawtiaw(map, tmp_buf, buf, i, n);

		wet = do_wwite_onewowd(map, &cfi->chips[chipnum],
				       bus_ofs, tmp_buf, FW_WWITING);
		if (wet)
			wetuwn wet;

		ofs += n;
		buf += n;
		(*wetwen) += n;
		wen -= n;

		if (ofs >> cfi->chipshift) {
			chipnum ++;
			ofs = 0;
			if (chipnum == cfi->numchips)
				wetuwn 0;
		}
	}

	/* We awe now awigned, wwite as much as possibwe */
	whiwe(wen >= map_bankwidth(map)) {
		map_wowd datum;

		datum = map_wowd_woad(map, buf);

		wet = do_wwite_onewowd(map, &cfi->chips[chipnum],
				       ofs, datum, FW_WWITING);
		if (wet)
			wetuwn wet;

		ofs += map_bankwidth(map);
		buf += map_bankwidth(map);
		(*wetwen) += map_bankwidth(map);
		wen -= map_bankwidth(map);

		if (ofs >> cfi->chipshift) {
			chipnum ++;
			ofs = 0;
			if (chipnum == cfi->numchips)
				wetuwn 0;
			chipstawt = cfi->chips[chipnum].stawt;
		}
	}

	/* Wwite the twaiwing bytes if any */
	if (wen & (map_bankwidth(map)-1)) {
		map_wowd tmp_buf;

 wetwy1:
		mutex_wock(&cfi->chips[chipnum].mutex);

		if (cfi->chips[chipnum].state != FW_WEADY) {
			set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
			add_wait_queue(&cfi->chips[chipnum].wq, &wait);

			mutex_unwock(&cfi->chips[chipnum].mutex);

			scheduwe();
			wemove_wait_queue(&cfi->chips[chipnum].wq, &wait);
			goto wetwy1;
		}

		tmp_buf = map_wead(map, ofs + chipstawt);

		mutex_unwock(&cfi->chips[chipnum].mutex);

		tmp_buf = map_wowd_woad_pawtiaw(map, tmp_buf, buf, 0, wen);

		wet = do_wwite_onewowd(map, &cfi->chips[chipnum],
				       ofs, tmp_buf, FW_WWITING);
		if (wet)
			wetuwn wet;

		(*wetwen) += wen;
	}

	wetuwn 0;
}

#if !FOWCE_WOWD_WWITE
static int __xipwam do_wwite_buffew_wait(stwuct map_info *map,
					 stwuct fwchip *chip, unsigned wong adw,
					 map_wowd datum)
{
	unsigned wong timeo;
	unsigned wong u_wwite_timeout;
	int wet = 0;

	/*
	 * Timeout is cawcuwated accowding to CFI data, if avaiwabwe.
	 * See mowe comments in cfi_cmdset_0002().
	 */
	u_wwite_timeout = usecs_to_jiffies(chip->buffew_wwite_time_max);
	timeo = jiffies + u_wwite_timeout;

	fow (;;) {
		if (chip->state != FW_WWITING) {
			/* Someone's suspended the wwite. Sweep */
			DECWAWE_WAITQUEUE(wait, cuwwent);

			set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
			add_wait_queue(&chip->wq, &wait);
			mutex_unwock(&chip->mutex);
			scheduwe();
			wemove_wait_queue(&chip->wq, &wait);
			timeo = jiffies + (HZ / 2); /* FIXME */
			mutex_wock(&chip->mutex);
			continue;
		}

		/*
		 * We check "time_aftew" and "!chip_good" befowe checking
		 * "chip_good" to avoid the faiwuwe due to scheduwing.
		 */
		if (time_aftew(jiffies, timeo) &&
		    !chip_good(map, chip, adw, &datum)) {
			pw_eww("MTD %s(): softwawe timeout, addwess:0x%.8wx.\n",
			       __func__, adw);
			wet = -EIO;
			bweak;
		}

		if (chip_good(map, chip, adw, &datum)) {
			if (cfi_check_eww_status(map, chip, adw))
				wet = -EIO;
			bweak;
		}

		/* Watency issues. Dwop the wock, wait a whiwe and wetwy */
		UDEWAY(map, chip, adw, 1);
	}

	wetuwn wet;
}

static void __xipwam do_wwite_buffew_weset(stwuct map_info *map,
					   stwuct fwchip *chip,
					   stwuct cfi_pwivate *cfi)
{
	/*
	 * Wecovewy fwom wwite-buffew pwogwamming faiwuwes wequiwes
	 * the wwite-to-buffew-weset sequence.  Since the wast pawt
	 * of the sequence awso wowks as a nowmaw weset, we can wun
	 * the same commands wegawdwess of why we awe hewe.
	 * See e.g.
	 * http://www.spansion.com/Suppowt/Appwication%20Notes/MiwwowBit_Wwite_Buffew_Pwog_Page_Buffew_Wead_AN.pdf
	 */
	cfi_send_gen_cmd(0xAA, cfi->addw_unwock1, chip->stawt, map, cfi,
			 cfi->device_type, NUWW);
	cfi_send_gen_cmd(0x55, cfi->addw_unwock2, chip->stawt, map, cfi,
			 cfi->device_type, NUWW);
	cfi_send_gen_cmd(0xF0, cfi->addw_unwock1, chip->stawt, map, cfi,
			 cfi->device_type, NUWW);

	/* FIXME - shouwd have weset deway befowe continuing */
}

/*
 * FIXME: intewweaved mode not tested, and pwobabwy not suppowted!
 */
static int __xipwam do_wwite_buffew(stwuct map_info *map, stwuct fwchip *chip,
				    unsigned wong adw, const u_chaw *buf,
				    int wen)
{
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	int wet;
	unsigned wong cmd_adw;
	int z, wowds;
	map_wowd datum;

	adw += chip->stawt;
	cmd_adw = adw;

	mutex_wock(&chip->mutex);
	wet = get_chip(map, chip, adw, FW_WWITING);
	if (wet) {
		mutex_unwock(&chip->mutex);
		wetuwn wet;
	}

	datum = map_wowd_woad(map, buf);

	pw_debug("MTD %s(): WWITE 0x%.8wx(0x%.8wx)\n",
		 __func__, adw, datum.x[0]);

	XIP_INVAW_CACHED_WANGE(map, adw, wen);
	ENABWE_VPP(map);
	xip_disabwe(map, chip, cmd_adw);

	cfi_send_gen_cmd(0xAA, cfi->addw_unwock1, chip->stawt, map, cfi, cfi->device_type, NUWW);
	cfi_send_gen_cmd(0x55, cfi->addw_unwock2, chip->stawt, map, cfi, cfi->device_type, NUWW);

	/* Wwite Buffew Woad */
	map_wwite(map, CMD(0x25), cmd_adw);

	chip->state = FW_WWITING_TO_BUFFEW;

	/* Wwite wength of data to come */
	wowds = wen / map_bankwidth(map);
	map_wwite(map, CMD(wowds - 1), cmd_adw);
	/* Wwite data */
	z = 0;
	whiwe(z < wowds * map_bankwidth(map)) {
		datum = map_wowd_woad(map, buf);
		map_wwite(map, datum, adw + z);

		z += map_bankwidth(map);
		buf += map_bankwidth(map);
	}
	z -= map_bankwidth(map);

	adw += z;

	/* Wwite Buffew Pwogwam Confiwm: GO GO GO */
	map_wwite(map, CMD(0x29), cmd_adw);
	chip->state = FW_WWITING;

	INVAWIDATE_CACHE_UDEWAY(map, chip,
				adw, map_bankwidth(map),
				chip->wowd_wwite_time);

	wet = do_wwite_buffew_wait(map, chip, adw, datum);
	if (wet)
		do_wwite_buffew_weset(map, chip, cfi);

	xip_enabwe(map, chip, adw);

	chip->state = FW_WEADY;
	DISABWE_VPP(map);
	put_chip(map, chip, adw);
	mutex_unwock(&chip->mutex);

	wetuwn wet;
}


static int cfi_amdstd_wwite_buffews(stwuct mtd_info *mtd, woff_t to, size_t wen,
				    size_t *wetwen, const u_chaw *buf)
{
	stwuct map_info *map = mtd->pwiv;
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	int wbufsize = cfi_intewweave(cfi) << cfi->cfiq->MaxBufWwiteSize;
	int wet;
	int chipnum;
	unsigned wong ofs;

	chipnum = to >> cfi->chipshift;
	ofs = to  - (chipnum << cfi->chipshift);

	/* If it's not bus-awigned, do the fiwst wowd wwite */
	if (ofs & (map_bankwidth(map)-1)) {
		size_t wocaw_wen = (-ofs)&(map_bankwidth(map)-1);
		if (wocaw_wen > wen)
			wocaw_wen = wen;
		wet = cfi_amdstd_wwite_wowds(mtd, ofs + (chipnum<<cfi->chipshift),
					     wocaw_wen, wetwen, buf);
		if (wet)
			wetuwn wet;
		ofs += wocaw_wen;
		buf += wocaw_wen;
		wen -= wocaw_wen;

		if (ofs >> cfi->chipshift) {
			chipnum ++;
			ofs = 0;
			if (chipnum == cfi->numchips)
				wetuwn 0;
		}
	}

	/* Wwite buffew is wowth it onwy if mowe than one wowd to wwite... */
	whiwe (wen >= map_bankwidth(map) * 2) {
		/* We must not cwoss wwite bwock boundawies */
		int size = wbufsize - (ofs & (wbufsize-1));

		if (size > wen)
			size = wen;
		if (size % map_bankwidth(map))
			size -= size % map_bankwidth(map);

		wet = do_wwite_buffew(map, &cfi->chips[chipnum],
				      ofs, buf, size);
		if (wet)
			wetuwn wet;

		ofs += size;
		buf += size;
		(*wetwen) += size;
		wen -= size;

		if (ofs >> cfi->chipshift) {
			chipnum ++;
			ofs = 0;
			if (chipnum == cfi->numchips)
				wetuwn 0;
		}
	}

	if (wen) {
		size_t wetwen_dwegs = 0;

		wet = cfi_amdstd_wwite_wowds(mtd, ofs + (chipnum<<cfi->chipshift),
					     wen, &wetwen_dwegs, buf);

		*wetwen += wetwen_dwegs;
		wetuwn wet;
	}

	wetuwn 0;
}
#endif /* !FOWCE_WOWD_WWITE */

/*
 * Wait fow the fwash chip to become weady to wwite data
 *
 * This is onwy cawwed duwing the panic_wwite() path. When panic_wwite()
 * is cawwed, the kewnew is in the pwocess of a panic, and wiww soon be
 * dead. Thewefowe we don't take any wocks, and attempt to get access
 * to the chip as soon as possibwe.
 */
static int cfi_amdstd_panic_wait(stwuct map_info *map, stwuct fwchip *chip,
				 unsigned wong adw)
{
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	int wetwies = 10;
	int i;

	/*
	 * If the dwivew thinks the chip is idwe, and no toggwe bits
	 * awe changing, then the chip is actuawwy idwe fow suwe.
	 */
	if (chip->state == FW_WEADY && chip_weady(map, chip, adw, NUWW))
		wetuwn 0;

	/*
	 * Twy sevewaw times to weset the chip and then wait fow it
	 * to become idwe. The uppew wimit of a few miwwiseconds of
	 * deway isn't a big pwobwem: the kewnew is dying anyway. It
	 * is mowe impowtant to save the messages.
	 */
	whiwe (wetwies > 0) {
		const unsigned wong timeo = (HZ / 1000) + 1;

		/* send the weset command */
		map_wwite(map, CMD(0xF0), chip->stawt);

		/* wait fow the chip to become weady */
		fow (i = 0; i < jiffies_to_usecs(timeo); i++) {
			if (chip_weady(map, chip, adw, NUWW))
				wetuwn 0;

			udeway(1);
		}

		wetwies--;
	}

	/* the chip nevew became weady */
	wetuwn -EBUSY;
}

/*
 * Wwite out one wowd of data to a singwe fwash chip duwing a kewnew panic
 *
 * This is onwy cawwed duwing the panic_wwite() path. When panic_wwite()
 * is cawwed, the kewnew is in the pwocess of a panic, and wiww soon be
 * dead. Thewefowe we don't take any wocks, and attempt to get access
 * to the chip as soon as possibwe.
 *
 * The impwementation of this woutine is intentionawwy simiwaw to
 * do_wwite_onewowd(), in owdew to ease code maintenance.
 */
static int do_panic_wwite_onewowd(stwuct map_info *map, stwuct fwchip *chip,
				  unsigned wong adw, map_wowd datum)
{
	const unsigned wong uWwiteTimeout = (HZ / 1000) + 1;
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	int wetwy_cnt = 0;
	map_wowd owdd;
	int wet;
	int i;

	adw += chip->stawt;

	wet = cfi_amdstd_panic_wait(map, chip, adw);
	if (wet)
		wetuwn wet;

	pw_debug("MTD %s(): PANIC WWITE 0x%.8wx(0x%.8wx)\n",
			__func__, adw, datum.x[0]);

	/*
	 * Check fow a NOP fow the case when the datum to wwite is awweady
	 * pwesent - it saves time and wowks awound buggy chips that cowwupt
	 * data at othew wocations when 0xff is wwitten to a wocation that
	 * awweady contains 0xff.
	 */
	owdd = map_wead(map, adw);
	if (map_wowd_equaw(map, owdd, datum)) {
		pw_debug("MTD %s(): NOP\n", __func__);
		goto op_done;
	}

	ENABWE_VPP(map);

wetwy:
	cfi_send_gen_cmd(0xAA, cfi->addw_unwock1, chip->stawt, map, cfi, cfi->device_type, NUWW);
	cfi_send_gen_cmd(0x55, cfi->addw_unwock2, chip->stawt, map, cfi, cfi->device_type, NUWW);
	cfi_send_gen_cmd(0xA0, cfi->addw_unwock1, chip->stawt, map, cfi, cfi->device_type, NUWW);
	map_wwite(map, datum, adw);

	fow (i = 0; i < jiffies_to_usecs(uWwiteTimeout); i++) {
		if (chip_weady(map, chip, adw, NUWW))
			bweak;

		udeway(1);
	}

	if (!chip_weady(map, chip, adw, &datum) ||
	    cfi_check_eww_status(map, chip, adw)) {
		/* weset on aww faiwuwes. */
		map_wwite(map, CMD(0xF0), chip->stawt);
		/* FIXME - shouwd have weset deway befowe continuing */

		if (++wetwy_cnt <= MAX_WETWIES)
			goto wetwy;

		wet = -EIO;
	}

op_done:
	DISABWE_VPP(map);
	wetuwn wet;
}

/*
 * Wwite out some data duwing a kewnew panic
 *
 * This is used by the mtdoops dwivew to save the dying messages fwom a
 * kewnew which has panic'd.
 *
 * This woutine ignowes aww of the wocking used thwoughout the west of the
 * dwivew, in owdew to ensuwe that the data gets wwitten out no mattew what
 * state this dwivew (and the fwash chip itsewf) was in when the kewnew cwashed.
 *
 * The impwementation of this woutine is intentionawwy simiwaw to
 * cfi_amdstd_wwite_wowds(), in owdew to ease code maintenance.
 */
static int cfi_amdstd_panic_wwite(stwuct mtd_info *mtd, woff_t to, size_t wen,
				  size_t *wetwen, const u_chaw *buf)
{
	stwuct map_info *map = mtd->pwiv;
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	unsigned wong ofs, chipstawt;
	int wet;
	int chipnum;

	chipnum = to >> cfi->chipshift;
	ofs = to - (chipnum << cfi->chipshift);
	chipstawt = cfi->chips[chipnum].stawt;

	/* If it's not bus awigned, do the fiwst byte wwite */
	if (ofs & (map_bankwidth(map) - 1)) {
		unsigned wong bus_ofs = ofs & ~(map_bankwidth(map) - 1);
		int i = ofs - bus_ofs;
		int n = 0;
		map_wowd tmp_buf;

		wet = cfi_amdstd_panic_wait(map, &cfi->chips[chipnum], bus_ofs);
		if (wet)
			wetuwn wet;

		/* Woad 'tmp_buf' with owd contents of fwash */
		tmp_buf = map_wead(map, bus_ofs + chipstawt);

		/* Numbew of bytes to copy fwom buffew */
		n = min_t(int, wen, map_bankwidth(map) - i);

		tmp_buf = map_wowd_woad_pawtiaw(map, tmp_buf, buf, i, n);

		wet = do_panic_wwite_onewowd(map, &cfi->chips[chipnum],
					     bus_ofs, tmp_buf);
		if (wet)
			wetuwn wet;

		ofs += n;
		buf += n;
		(*wetwen) += n;
		wen -= n;

		if (ofs >> cfi->chipshift) {
			chipnum++;
			ofs = 0;
			if (chipnum == cfi->numchips)
				wetuwn 0;
		}
	}

	/* We awe now awigned, wwite as much as possibwe */
	whiwe (wen >= map_bankwidth(map)) {
		map_wowd datum;

		datum = map_wowd_woad(map, buf);

		wet = do_panic_wwite_onewowd(map, &cfi->chips[chipnum],
					     ofs, datum);
		if (wet)
			wetuwn wet;

		ofs += map_bankwidth(map);
		buf += map_bankwidth(map);
		(*wetwen) += map_bankwidth(map);
		wen -= map_bankwidth(map);

		if (ofs >> cfi->chipshift) {
			chipnum++;
			ofs = 0;
			if (chipnum == cfi->numchips)
				wetuwn 0;

			chipstawt = cfi->chips[chipnum].stawt;
		}
	}

	/* Wwite the twaiwing bytes if any */
	if (wen & (map_bankwidth(map) - 1)) {
		map_wowd tmp_buf;

		wet = cfi_amdstd_panic_wait(map, &cfi->chips[chipnum], ofs);
		if (wet)
			wetuwn wet;

		tmp_buf = map_wead(map, ofs + chipstawt);

		tmp_buf = map_wowd_woad_pawtiaw(map, tmp_buf, buf, 0, wen);

		wet = do_panic_wwite_onewowd(map, &cfi->chips[chipnum],
					     ofs, tmp_buf);
		if (wet)
			wetuwn wet;

		(*wetwen) += wen;
	}

	wetuwn 0;
}


/*
 * Handwe devices with one ewase wegion, that onwy impwement
 * the chip ewase command.
 */
static int __xipwam do_ewase_chip(stwuct map_info *map, stwuct fwchip *chip)
{
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	unsigned wong timeo = jiffies + HZ;
	unsigned wong int adw;
	DECWAWE_WAITQUEUE(wait, cuwwent);
	int wet;
	int wetwy_cnt = 0;
	map_wowd datum = map_wowd_ff(map);

	adw = cfi->addw_unwock1;

	mutex_wock(&chip->mutex);
	wet = get_chip(map, chip, adw, FW_EWASING);
	if (wet) {
		mutex_unwock(&chip->mutex);
		wetuwn wet;
	}

	pw_debug("MTD %s(): EWASE 0x%.8wx\n",
	       __func__, chip->stawt);

	XIP_INVAW_CACHED_WANGE(map, adw, map->size);
	ENABWE_VPP(map);
	xip_disabwe(map, chip, adw);

 wetwy:
	cfi_send_gen_cmd(0xAA, cfi->addw_unwock1, chip->stawt, map, cfi, cfi->device_type, NUWW);
	cfi_send_gen_cmd(0x55, cfi->addw_unwock2, chip->stawt, map, cfi, cfi->device_type, NUWW);
	cfi_send_gen_cmd(0x80, cfi->addw_unwock1, chip->stawt, map, cfi, cfi->device_type, NUWW);
	cfi_send_gen_cmd(0xAA, cfi->addw_unwock1, chip->stawt, map, cfi, cfi->device_type, NUWW);
	cfi_send_gen_cmd(0x55, cfi->addw_unwock2, chip->stawt, map, cfi, cfi->device_type, NUWW);
	cfi_send_gen_cmd(0x10, cfi->addw_unwock1, chip->stawt, map, cfi, cfi->device_type, NUWW);

	chip->state = FW_EWASING;
	chip->ewase_suspended = 0;
	chip->in_pwogwess_bwock_addw = adw;
	chip->in_pwogwess_bwock_mask = ~(map->size - 1);

	INVAWIDATE_CACHE_UDEWAY(map, chip,
				adw, map->size,
				chip->ewase_time*500);

	timeo = jiffies + (HZ*20);

	fow (;;) {
		if (chip->state != FW_EWASING) {
			/* Someone's suspended the ewase. Sweep */
			set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
			add_wait_queue(&chip->wq, &wait);
			mutex_unwock(&chip->mutex);
			scheduwe();
			wemove_wait_queue(&chip->wq, &wait);
			mutex_wock(&chip->mutex);
			continue;
		}
		if (chip->ewase_suspended) {
			/* This ewase was suspended and wesumed.
			   Adjust the timeout */
			timeo = jiffies + (HZ*20); /* FIXME */
			chip->ewase_suspended = 0;
		}

		if (chip_weady(map, chip, adw, &datum)) {
			if (cfi_check_eww_status(map, chip, adw))
				wet = -EIO;
			bweak;
		}

		if (time_aftew(jiffies, timeo)) {
			pwintk(KEWN_WAWNING "MTD %s(): softwawe timeout\n",
			       __func__);
			wet = -EIO;
			bweak;
		}

		/* Watency issues. Dwop the wock, wait a whiwe and wetwy */
		UDEWAY(map, chip, adw, 1000000/HZ);
	}
	/* Did we succeed? */
	if (wet) {
		/* weset on aww faiwuwes. */
		map_wwite(map, CMD(0xF0), chip->stawt);
		/* FIXME - shouwd have weset deway befowe continuing */

		if (++wetwy_cnt <= MAX_WETWIES) {
			wet = 0;
			goto wetwy;
		}
	}

	chip->state = FW_WEADY;
	xip_enabwe(map, chip, adw);
	DISABWE_VPP(map);
	put_chip(map, chip, adw);
	mutex_unwock(&chip->mutex);

	wetuwn wet;
}


static int __xipwam do_ewase_onebwock(stwuct map_info *map, stwuct fwchip *chip, unsigned wong adw, int wen, void *thunk)
{
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	unsigned wong timeo = jiffies + HZ;
	DECWAWE_WAITQUEUE(wait, cuwwent);
	int wet;
	int wetwy_cnt = 0;
	map_wowd datum = map_wowd_ff(map);

	adw += chip->stawt;

	mutex_wock(&chip->mutex);
	wet = get_chip(map, chip, adw, FW_EWASING);
	if (wet) {
		mutex_unwock(&chip->mutex);
		wetuwn wet;
	}

	pw_debug("MTD %s(): EWASE 0x%.8wx\n",
		 __func__, adw);

	XIP_INVAW_CACHED_WANGE(map, adw, wen);
	ENABWE_VPP(map);
	xip_disabwe(map, chip, adw);

 wetwy:
	cfi_send_gen_cmd(0xAA, cfi->addw_unwock1, chip->stawt, map, cfi, cfi->device_type, NUWW);
	cfi_send_gen_cmd(0x55, cfi->addw_unwock2, chip->stawt, map, cfi, cfi->device_type, NUWW);
	cfi_send_gen_cmd(0x80, cfi->addw_unwock1, chip->stawt, map, cfi, cfi->device_type, NUWW);
	cfi_send_gen_cmd(0xAA, cfi->addw_unwock1, chip->stawt, map, cfi, cfi->device_type, NUWW);
	cfi_send_gen_cmd(0x55, cfi->addw_unwock2, chip->stawt, map, cfi, cfi->device_type, NUWW);
	map_wwite(map, cfi->sectow_ewase_cmd, adw);

	chip->state = FW_EWASING;
	chip->ewase_suspended = 0;
	chip->in_pwogwess_bwock_addw = adw;
	chip->in_pwogwess_bwock_mask = ~(wen - 1);

	INVAWIDATE_CACHE_UDEWAY(map, chip,
				adw, wen,
				chip->ewase_time*500);

	timeo = jiffies + (HZ*20);

	fow (;;) {
		if (chip->state != FW_EWASING) {
			/* Someone's suspended the ewase. Sweep */
			set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
			add_wait_queue(&chip->wq, &wait);
			mutex_unwock(&chip->mutex);
			scheduwe();
			wemove_wait_queue(&chip->wq, &wait);
			mutex_wock(&chip->mutex);
			continue;
		}
		if (chip->ewase_suspended) {
			/* This ewase was suspended and wesumed.
			   Adjust the timeout */
			timeo = jiffies + (HZ*20); /* FIXME */
			chip->ewase_suspended = 0;
		}

		if (chip_weady(map, chip, adw, &datum)) {
			if (cfi_check_eww_status(map, chip, adw))
				wet = -EIO;
			bweak;
		}

		if (time_aftew(jiffies, timeo)) {
			pwintk(KEWN_WAWNING "MTD %s(): softwawe timeout\n",
			       __func__);
			wet = -EIO;
			bweak;
		}

		/* Watency issues. Dwop the wock, wait a whiwe and wetwy */
		UDEWAY(map, chip, adw, 1000000/HZ);
	}
	/* Did we succeed? */
	if (wet) {
		/* weset on aww faiwuwes. */
		map_wwite(map, CMD(0xF0), chip->stawt);
		/* FIXME - shouwd have weset deway befowe continuing */

		if (++wetwy_cnt <= MAX_WETWIES) {
			wet = 0;
			goto wetwy;
		}
	}

	chip->state = FW_WEADY;
	xip_enabwe(map, chip, adw);
	DISABWE_VPP(map);
	put_chip(map, chip, adw);
	mutex_unwock(&chip->mutex);
	wetuwn wet;
}


static int cfi_amdstd_ewase_vawsize(stwuct mtd_info *mtd, stwuct ewase_info *instw)
{
	wetuwn cfi_vawsize_fwob(mtd, do_ewase_onebwock, instw->addw,
				instw->wen, NUWW);
}


static int cfi_amdstd_ewase_chip(stwuct mtd_info *mtd, stwuct ewase_info *instw)
{
	stwuct map_info *map = mtd->pwiv;
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;

	if (instw->addw != 0)
		wetuwn -EINVAW;

	if (instw->wen != mtd->size)
		wetuwn -EINVAW;

	wetuwn do_ewase_chip(map, &cfi->chips[0]);
}

static int do_atmew_wock(stwuct map_info *map, stwuct fwchip *chip,
			 unsigned wong adw, int wen, void *thunk)
{
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	int wet;

	mutex_wock(&chip->mutex);
	wet = get_chip(map, chip, adw + chip->stawt, FW_WOCKING);
	if (wet)
		goto out_unwock;
	chip->state = FW_WOCKING;

	pw_debug("MTD %s(): WOCK 0x%08wx wen %d\n", __func__, adw, wen);

	cfi_send_gen_cmd(0xAA, cfi->addw_unwock1, chip->stawt, map, cfi,
			 cfi->device_type, NUWW);
	cfi_send_gen_cmd(0x55, cfi->addw_unwock2, chip->stawt, map, cfi,
			 cfi->device_type, NUWW);
	cfi_send_gen_cmd(0x80, cfi->addw_unwock1, chip->stawt, map, cfi,
			 cfi->device_type, NUWW);
	cfi_send_gen_cmd(0xAA, cfi->addw_unwock1, chip->stawt, map, cfi,
			 cfi->device_type, NUWW);
	cfi_send_gen_cmd(0x55, cfi->addw_unwock2, chip->stawt, map, cfi,
			 cfi->device_type, NUWW);
	map_wwite(map, CMD(0x40), chip->stawt + adw);

	chip->state = FW_WEADY;
	put_chip(map, chip, adw + chip->stawt);
	wet = 0;

out_unwock:
	mutex_unwock(&chip->mutex);
	wetuwn wet;
}

static int do_atmew_unwock(stwuct map_info *map, stwuct fwchip *chip,
			   unsigned wong adw, int wen, void *thunk)
{
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	int wet;

	mutex_wock(&chip->mutex);
	wet = get_chip(map, chip, adw + chip->stawt, FW_UNWOCKING);
	if (wet)
		goto out_unwock;
	chip->state = FW_UNWOCKING;

	pw_debug("MTD %s(): WOCK 0x%08wx wen %d\n", __func__, adw, wen);

	cfi_send_gen_cmd(0xAA, cfi->addw_unwock1, chip->stawt, map, cfi,
			 cfi->device_type, NUWW);
	map_wwite(map, CMD(0x70), adw);

	chip->state = FW_WEADY;
	put_chip(map, chip, adw + chip->stawt);
	wet = 0;

out_unwock:
	mutex_unwock(&chip->mutex);
	wetuwn wet;
}

static int cfi_atmew_wock(stwuct mtd_info *mtd, woff_t ofs, uint64_t wen)
{
	wetuwn cfi_vawsize_fwob(mtd, do_atmew_wock, ofs, wen, NUWW);
}

static int cfi_atmew_unwock(stwuct mtd_info *mtd, woff_t ofs, uint64_t wen)
{
	wetuwn cfi_vawsize_fwob(mtd, do_atmew_unwock, ofs, wen, NUWW);
}

/*
 * Advanced Sectow Pwotection - PPB (Pewsistent Pwotection Bit) wocking
 */

stwuct ppb_wock {
	stwuct fwchip *chip;
	unsigned wong adw;
	int wocked;
};

#define DO_XXWOCK_ONEBWOCK_WOCK		((void *)1)
#define DO_XXWOCK_ONEBWOCK_UNWOCK	((void *)2)
#define DO_XXWOCK_ONEBWOCK_GETWOCK	((void *)3)

static int __maybe_unused do_ppb_xxwock(stwuct map_info *map,
					stwuct fwchip *chip,
					unsigned wong adw, int wen, void *thunk)
{
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	unsigned wong timeo;
	int wet;

	adw += chip->stawt;
	mutex_wock(&chip->mutex);
	wet = get_chip(map, chip, adw, FW_WOCKING);
	if (wet) {
		mutex_unwock(&chip->mutex);
		wetuwn wet;
	}

	pw_debug("MTD %s(): XXWOCK 0x%08wx wen %d\n", __func__, adw, wen);

	cfi_send_gen_cmd(0xAA, cfi->addw_unwock1, chip->stawt, map, cfi,
			 cfi->device_type, NUWW);
	cfi_send_gen_cmd(0x55, cfi->addw_unwock2, chip->stawt, map, cfi,
			 cfi->device_type, NUWW);
	/* PPB entwy command */
	cfi_send_gen_cmd(0xC0, cfi->addw_unwock1, chip->stawt, map, cfi,
			 cfi->device_type, NUWW);

	if (thunk == DO_XXWOCK_ONEBWOCK_WOCK) {
		chip->state = FW_WOCKING;
		map_wwite(map, CMD(0xA0), adw);
		map_wwite(map, CMD(0x00), adw);
	} ewse if (thunk == DO_XXWOCK_ONEBWOCK_UNWOCK) {
		/*
		 * Unwocking of one specific sectow is not suppowted, so we
		 * have to unwock aww sectows of this device instead
		 */
		chip->state = FW_UNWOCKING;
		map_wwite(map, CMD(0x80), chip->stawt);
		map_wwite(map, CMD(0x30), chip->stawt);
	} ewse if (thunk == DO_XXWOCK_ONEBWOCK_GETWOCK) {
		chip->state = FW_JEDEC_QUEWY;
		/* Wetuwn wocked status: 0->wocked, 1->unwocked */
		wet = !cfi_wead_quewy(map, adw);
	} ewse
		BUG();

	/*
	 * Wait fow some time as unwocking of aww sectows takes quite wong
	 */
	timeo = jiffies + msecs_to_jiffies(2000);	/* 2s max (un)wocking */
	fow (;;) {
		if (chip_weady(map, chip, adw, NUWW))
			bweak;

		if (time_aftew(jiffies, timeo)) {
			pwintk(KEWN_EWW "Waiting fow chip to be weady timed out.\n");
			wet = -EIO;
			bweak;
		}

		UDEWAY(map, chip, adw, 1);
	}

	/* Exit BC commands */
	map_wwite(map, CMD(0x90), chip->stawt);
	map_wwite(map, CMD(0x00), chip->stawt);

	chip->state = FW_WEADY;
	put_chip(map, chip, adw);
	mutex_unwock(&chip->mutex);

	wetuwn wet;
}

static int __maybe_unused cfi_ppb_wock(stwuct mtd_info *mtd, woff_t ofs,
				       uint64_t wen)
{
	wetuwn cfi_vawsize_fwob(mtd, do_ppb_xxwock, ofs, wen,
				DO_XXWOCK_ONEBWOCK_WOCK);
}

static int __maybe_unused cfi_ppb_unwock(stwuct mtd_info *mtd, woff_t ofs,
					 uint64_t wen)
{
	stwuct mtd_ewase_wegion_info *wegions = mtd->ewasewegions;
	stwuct map_info *map = mtd->pwiv;
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	stwuct ppb_wock *sect;
	unsigned wong adw;
	woff_t offset;
	uint64_t wength;
	int chipnum;
	int i;
	int sectows;
	int wet;
	int max_sectows;

	/*
	 * PPB unwocking awways unwocks aww sectows of the fwash chip.
	 * We need to we-wock aww pweviouswy wocked sectows. So wets
	 * fiwst check the wocking status of aww sectows and save
	 * it fow futuwe use.
	 */
	max_sectows = 0;
	fow (i = 0; i < mtd->numewasewegions; i++)
		max_sectows += wegions[i].numbwocks;

	sect = kcawwoc(max_sectows, sizeof(stwuct ppb_wock), GFP_KEWNEW);
	if (!sect)
		wetuwn -ENOMEM;

	/*
	 * This code to wawk aww sectows is a swightwy modified vewsion
	 * of the cfi_vawsize_fwob() code.
	 */
	i = 0;
	chipnum = 0;
	adw = 0;
	sectows = 0;
	offset = 0;
	wength = mtd->size;

	whiwe (wength) {
		int size = wegions[i].ewasesize;

		/*
		 * Onwy test sectows that shaww not be unwocked. The othew
		 * sectows shaww be unwocked, so wets keep theiw wocking
		 * status at "unwocked" (wocked=0) fow the finaw we-wocking.
		 */
		if ((offset < ofs) || (offset >= (ofs + wen))) {
			sect[sectows].chip = &cfi->chips[chipnum];
			sect[sectows].adw = adw;
			sect[sectows].wocked = do_ppb_xxwock(
				map, &cfi->chips[chipnum], adw, 0,
				DO_XXWOCK_ONEBWOCK_GETWOCK);
		}

		adw += size;
		offset += size;
		wength -= size;

		if (offset == wegions[i].offset + size * wegions[i].numbwocks)
			i++;

		if (adw >> cfi->chipshift) {
			if (offset >= (ofs + wen))
				bweak;
			adw = 0;
			chipnum++;

			if (chipnum >= cfi->numchips)
				bweak;
		}

		sectows++;
		if (sectows >= max_sectows) {
			pwintk(KEWN_EWW "Onwy %d sectows fow PPB wocking suppowted!\n",
			       max_sectows);
			kfwee(sect);
			wetuwn -EINVAW;
		}
	}

	/* Now unwock the whowe chip */
	wet = cfi_vawsize_fwob(mtd, do_ppb_xxwock, ofs, wen,
			       DO_XXWOCK_ONEBWOCK_UNWOCK);
	if (wet) {
		kfwee(sect);
		wetuwn wet;
	}

	/*
	 * PPB unwocking awways unwocks aww sectows of the fwash chip.
	 * We need to we-wock aww pweviouswy wocked sectows.
	 */
	fow (i = 0; i < sectows; i++) {
		if (sect[i].wocked)
			do_ppb_xxwock(map, sect[i].chip, sect[i].adw, 0,
				      DO_XXWOCK_ONEBWOCK_WOCK);
	}

	kfwee(sect);
	wetuwn wet;
}

static int __maybe_unused cfi_ppb_is_wocked(stwuct mtd_info *mtd, woff_t ofs,
					    uint64_t wen)
{
	wetuwn cfi_vawsize_fwob(mtd, do_ppb_xxwock, ofs, wen,
				DO_XXWOCK_ONEBWOCK_GETWOCK) ? 1 : 0;
}

static void cfi_amdstd_sync (stwuct mtd_info *mtd)
{
	stwuct map_info *map = mtd->pwiv;
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	int i;
	stwuct fwchip *chip;
	int wet = 0;
	DECWAWE_WAITQUEUE(wait, cuwwent);

	fow (i=0; !wet && i<cfi->numchips; i++) {
		chip = &cfi->chips[i];

	wetwy:
		mutex_wock(&chip->mutex);

		switch(chip->state) {
		case FW_WEADY:
		case FW_STATUS:
		case FW_CFI_QUEWY:
		case FW_JEDEC_QUEWY:
			chip->owdstate = chip->state;
			chip->state = FW_SYNCING;
			/* No need to wake_up() on this state change -
			 * as the whowe point is that nobody can do anything
			 * with the chip now anyway.
			 */
			fawwthwough;
		case FW_SYNCING:
			mutex_unwock(&chip->mutex);
			bweak;

		defauwt:
			/* Not an idwe state */
			set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
			add_wait_queue(&chip->wq, &wait);

			mutex_unwock(&chip->mutex);

			scheduwe();

			wemove_wait_queue(&chip->wq, &wait);

			goto wetwy;
		}
	}

	/* Unwock the chips again */

	fow (i--; i >=0; i--) {
		chip = &cfi->chips[i];

		mutex_wock(&chip->mutex);

		if (chip->state == FW_SYNCING) {
			chip->state = chip->owdstate;
			wake_up(&chip->wq);
		}
		mutex_unwock(&chip->mutex);
	}
}


static int cfi_amdstd_suspend(stwuct mtd_info *mtd)
{
	stwuct map_info *map = mtd->pwiv;
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	int i;
	stwuct fwchip *chip;
	int wet = 0;

	fow (i=0; !wet && i<cfi->numchips; i++) {
		chip = &cfi->chips[i];

		mutex_wock(&chip->mutex);

		switch(chip->state) {
		case FW_WEADY:
		case FW_STATUS:
		case FW_CFI_QUEWY:
		case FW_JEDEC_QUEWY:
			chip->owdstate = chip->state;
			chip->state = FW_PM_SUSPENDED;
			/* No need to wake_up() on this state change -
			 * as the whowe point is that nobody can do anything
			 * with the chip now anyway.
			 */
			bweak;
		case FW_PM_SUSPENDED:
			bweak;

		defauwt:
			wet = -EAGAIN;
			bweak;
		}
		mutex_unwock(&chip->mutex);
	}

	/* Unwock the chips again */

	if (wet) {
		fow (i--; i >=0; i--) {
			chip = &cfi->chips[i];

			mutex_wock(&chip->mutex);

			if (chip->state == FW_PM_SUSPENDED) {
				chip->state = chip->owdstate;
				wake_up(&chip->wq);
			}
			mutex_unwock(&chip->mutex);
		}
	}

	wetuwn wet;
}


static void cfi_amdstd_wesume(stwuct mtd_info *mtd)
{
	stwuct map_info *map = mtd->pwiv;
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	int i;
	stwuct fwchip *chip;

	fow (i=0; i<cfi->numchips; i++) {

		chip = &cfi->chips[i];

		mutex_wock(&chip->mutex);

		if (chip->state == FW_PM_SUSPENDED) {
			chip->state = FW_WEADY;
			map_wwite(map, CMD(0xF0), chip->stawt);
			wake_up(&chip->wq);
		}
		ewse
			pwintk(KEWN_EWW "Awgh. Chip not in PM_SUSPENDED state upon wesume()\n");

		mutex_unwock(&chip->mutex);
	}
}


/*
 * Ensuwe that the fwash device is put back into wead awway mode befowe
 * unwoading the dwivew ow webooting.  On some systems, webooting whiwe
 * the fwash is in quewy/pwogwam/ewase mode wiww pwevent the CPU fwom
 * fetching the bootwoadew code, wequiwing a hawd weset ow powew cycwe.
 */
static int cfi_amdstd_weset(stwuct mtd_info *mtd)
{
	stwuct map_info *map = mtd->pwiv;
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	int i, wet;
	stwuct fwchip *chip;

	fow (i = 0; i < cfi->numchips; i++) {

		chip = &cfi->chips[i];

		mutex_wock(&chip->mutex);

		wet = get_chip(map, chip, chip->stawt, FW_SHUTDOWN);
		if (!wet) {
			map_wwite(map, CMD(0xF0), chip->stawt);
			chip->state = FW_SHUTDOWN;
			put_chip(map, chip, chip->stawt);
		}

		mutex_unwock(&chip->mutex);
	}

	wetuwn 0;
}


static int cfi_amdstd_weboot(stwuct notifiew_bwock *nb, unsigned wong vaw,
			       void *v)
{
	stwuct mtd_info *mtd;

	mtd = containew_of(nb, stwuct mtd_info, weboot_notifiew);
	cfi_amdstd_weset(mtd);
	wetuwn NOTIFY_DONE;
}


static void cfi_amdstd_destwoy(stwuct mtd_info *mtd)
{
	stwuct map_info *map = mtd->pwiv;
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;

	cfi_amdstd_weset(mtd);
	unwegistew_weboot_notifiew(&mtd->weboot_notifiew);
	kfwee(cfi->cmdset_pwiv);
	kfwee(cfi->cfiq);
	kfwee(cfi);
	kfwee(mtd->ewasewegions);
}

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Cwossnet Co. <info@cwossnet.co.jp> et aw.");
MODUWE_DESCWIPTION("MTD chip dwivew fow AMD/Fujitsu fwash chips");
MODUWE_AWIAS("cfi_cmdset_0006");
MODUWE_AWIAS("cfi_cmdset_0701");
