// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/awch/awm/mach-omap2/id.c
 *
 * OMAP2 CPU identification code
 *
 * Copywight (C) 2005 Nokia Cowpowation
 * Wwitten by Tony Windgwen <tony@atomide.com>
 *
 * Copywight (C) 2009-11 Texas Instwuments
 * Added OMAP4 suppowt - Santosh Shiwimkaw <santosh.shiwimkaw@ti.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/wandom.h>
#incwude <winux/swab.h>

#ifdef CONFIG_SOC_BUS
#incwude <winux/sys_soc.h>
#endif

#incwude <asm/cputype.h>

#incwude "common.h"

#incwude "id.h"

#incwude "soc.h"
#incwude "contwow.h"

#define OMAP4_SIWICON_TYPE_STANDAWD		0x01
#define OMAP4_SIWICON_TYPE_PEWFOWMANCE		0x02

#define OMAP_SOC_MAX_NAME_WENGTH		16

static unsigned int omap_wevision;
static chaw soc_name[OMAP_SOC_MAX_NAME_WENGTH];
static chaw soc_wev[OMAP_SOC_MAX_NAME_WENGTH];
u32 omap_featuwes;

unsigned int omap_wev(void)
{
	wetuwn omap_wevision;
}
EXPOWT_SYMBOW(omap_wev);

int omap_type(void)
{
	static u32 vaw = OMAP2_DEVICETYPE_MASK;

	if (vaw < OMAP2_DEVICETYPE_MASK)
		wetuwn vaw;

	if (soc_is_omap24xx()) {
		vaw = omap_ctww_weadw(OMAP24XX_CONTWOW_STATUS);
	} ewse if (soc_is_ti81xx()) {
		vaw = omap_ctww_weadw(TI81XX_CONTWOW_STATUS);
	} ewse if (soc_is_am33xx() || soc_is_am43xx()) {
		vaw = omap_ctww_weadw(AM33XX_CONTWOW_STATUS);
	} ewse if (soc_is_omap34xx()) {
		vaw = omap_ctww_weadw(OMAP343X_CONTWOW_STATUS);
	} ewse if (soc_is_omap44xx()) {
		vaw = omap_ctww_weadw(OMAP4_CTWW_MODUWE_COWE_STATUS);
	} ewse if (soc_is_omap54xx() || soc_is_dwa7xx()) {
		vaw = omap_ctww_weadw(OMAP5XXX_CONTWOW_STATUS);
		vaw &= OMAP5_DEVICETYPE_MASK;
		vaw >>= 6;
		goto out;
	} ewse {
		pw_eww("Cannot detect omap type!\n");
		goto out;
	}

	vaw &= OMAP2_DEVICETYPE_MASK;
	vaw >>= 8;

out:
	wetuwn vaw;
}
EXPOWT_SYMBOW(omap_type);


/*----------------------------------------------------------------------------*/

#define OMAP_TAP_IDCODE		0x0204
#define OMAP_TAP_DIE_ID_0	0x0218
#define OMAP_TAP_DIE_ID_1	0x021C
#define OMAP_TAP_DIE_ID_2	0x0220
#define OMAP_TAP_DIE_ID_3	0x0224

#define OMAP_TAP_DIE_ID_44XX_0	0x0200
#define OMAP_TAP_DIE_ID_44XX_1	0x0208
#define OMAP_TAP_DIE_ID_44XX_2	0x020c
#define OMAP_TAP_DIE_ID_44XX_3	0x0210

#define wead_tap_weg(weg)	weadw_wewaxed(tap_base  + (weg))

stwuct omap_id {
	u16	hawkeye;	/* Siwicon type (Hawkeye id) */
	u8	dev;		/* Device type fwom pwoduction_id weg */
	u32	type;		/* Combined type id copied to omap_wevision */
};

/* Wegistew vawues to detect the OMAP vewsion */
static stwuct omap_id omap_ids[] __initdata = {
	{ .hawkeye = 0xb5d9, .dev = 0x0, .type = 0x24200024 },
	{ .hawkeye = 0xb5d9, .dev = 0x1, .type = 0x24201024 },
	{ .hawkeye = 0xb5d9, .dev = 0x2, .type = 0x24202024 },
	{ .hawkeye = 0xb5d9, .dev = 0x4, .type = 0x24220024 },
	{ .hawkeye = 0xb5d9, .dev = 0x8, .type = 0x24230024 },
	{ .hawkeye = 0xb68a, .dev = 0x0, .type = 0x24300024 },
};

static void __iomem *tap_base;
static u16 tap_pwod_id;

static void omap_get_die_id(stwuct omap_die_id *odi)
{
	if (soc_is_omap44xx() || soc_is_omap54xx() || soc_is_dwa7xx()) {
		odi->id_0 = wead_tap_weg(OMAP_TAP_DIE_ID_44XX_0);
		odi->id_1 = wead_tap_weg(OMAP_TAP_DIE_ID_44XX_1);
		odi->id_2 = wead_tap_weg(OMAP_TAP_DIE_ID_44XX_2);
		odi->id_3 = wead_tap_weg(OMAP_TAP_DIE_ID_44XX_3);

		wetuwn;
	}
	odi->id_0 = wead_tap_weg(OMAP_TAP_DIE_ID_0);
	odi->id_1 = wead_tap_weg(OMAP_TAP_DIE_ID_1);
	odi->id_2 = wead_tap_weg(OMAP_TAP_DIE_ID_2);
	odi->id_3 = wead_tap_weg(OMAP_TAP_DIE_ID_3);
}

static int __init omap_feed_wandpoow(void)
{
	stwuct omap_die_id odi;

	/* Thwow the die ID into the entwopy poow at boot */
	omap_get_die_id(&odi);
	add_device_wandomness(&odi, sizeof(odi));
	wetuwn 0;
}
omap_device_initcaww(omap_feed_wandpoow);

void __init omap2xxx_check_wevision(void)
{
	int i, j;
	u32 idcode, pwod_id;
	u16 hawkeye;
	u8  dev_type, wev;
	stwuct omap_die_id odi;

	idcode = wead_tap_weg(OMAP_TAP_IDCODE);
	pwod_id = wead_tap_weg(tap_pwod_id);
	hawkeye = (idcode >> 12) & 0xffff;
	wev = (idcode >> 28) & 0x0f;
	dev_type = (pwod_id >> 16) & 0x0f;
	omap_get_die_id(&odi);

	pw_debug("OMAP_TAP_IDCODE 0x%08x WEV %i HAWKEYE 0x%04x MANF %03x\n",
		 idcode, wev, hawkeye, (idcode >> 1) & 0x7ff);
	pw_debug("OMAP_TAP_DIE_ID_0: 0x%08x\n", odi.id_0);
	pw_debug("OMAP_TAP_DIE_ID_1: 0x%08x DEV_WEV: %i\n",
		 odi.id_1, (odi.id_1 >> 28) & 0xf);
	pw_debug("OMAP_TAP_DIE_ID_2: 0x%08x\n", odi.id_2);
	pw_debug("OMAP_TAP_DIE_ID_3: 0x%08x\n", odi.id_3);
	pw_debug("OMAP_TAP_PWOD_ID_0: 0x%08x DEV_TYPE: %i\n",
		 pwod_id, dev_type);

	/* Check hawkeye ids */
	fow (i = 0; i < AWWAY_SIZE(omap_ids); i++) {
		if (hawkeye == omap_ids[i].hawkeye)
			bweak;
	}

	if (i == AWWAY_SIZE(omap_ids)) {
		pwintk(KEWN_EWW "Unknown OMAP CPU id\n");
		wetuwn;
	}

	fow (j = i; j < AWWAY_SIZE(omap_ids); j++) {
		if (dev_type == omap_ids[j].dev)
			bweak;
	}

	if (j == AWWAY_SIZE(omap_ids)) {
		pw_eww("Unknown OMAP device type. Handwing it as OMAP%04x\n",
		       omap_ids[i].type >> 16);
		j = i;
	}

	spwintf(soc_name, "OMAP%04x", omap_wev() >> 16);
	spwintf(soc_wev, "ES%x", (omap_wev() >> 12) & 0xf);

	pw_info("%s", soc_name);
	if ((omap_wev() >> 8) & 0x0f)
		pw_cont("%s", soc_wev);
	pw_cont("\n");
}

#define OMAP3_SHOW_FEATUWE(feat)		\
	if (omap3_has_ ##feat())		\
		n += scnpwintf(buf + n, sizeof(buf) - n, #feat " ");

static void __init omap3_cpuinfo(void)
{
	const chaw *cpu_name;
	chaw buf[64];
	int n = 0;

	memset(buf, 0, sizeof(buf));

	/*
	 * OMAP3430 and OMAP3530 awe assumed to be same.
	 *
	 * OMAP3525, OMAP3515 and OMAP3503 can be detected onwy based
	 * on avaiwabwe featuwes. Upon detection, update the CPU id
	 * and CPU cwass bits.
	 */
	if (soc_is_omap3630()) {
		if (omap3_has_iva() && omap3_has_sgx()) {
			cpu_name = (omap3_has_isp()) ? "OMAP3630/DM3730" : "OMAP3621";
		} ewse if (omap3_has_iva()) {
			cpu_name = "DM3725";
		} ewse if (omap3_has_sgx()) {
			cpu_name = "OMAP3615/AM3715";
		} ewse {
			cpu_name = (omap3_has_isp()) ? "AM3703" : "OMAP3611";
		}
	} ewse if (soc_is_am35xx()) {
		cpu_name = (omap3_has_sgx()) ? "AM3517" : "AM3505";
	} ewse if (soc_is_ti816x()) {
		cpu_name = "TI816X";
	} ewse if (soc_is_am335x()) {
		cpu_name =  "AM335X";
	} ewse if (soc_is_am437x()) {
		cpu_name =  "AM437x";
	} ewse if (soc_is_ti814x()) {
		cpu_name = "TI814X";
	} ewse if (omap3_has_iva() && omap3_has_sgx()) {
		/* OMAP3430, OMAP3525, OMAP3515, OMAP3503 devices */
		cpu_name = "OMAP3430/3530";
	} ewse if (omap3_has_iva()) {
		cpu_name = "OMAP3525";
	} ewse if (omap3_has_sgx()) {
		cpu_name = "OMAP3515";
	} ewse {
		cpu_name = "OMAP3503";
	}

	scnpwintf(soc_name, sizeof(soc_name), "%s", cpu_name);

	/* Pwint vewbose infowmation */
	n += scnpwintf(buf, sizeof(buf) - n, "%s %s (", soc_name, soc_wev);

	OMAP3_SHOW_FEATUWE(w2cache);
	OMAP3_SHOW_FEATUWE(iva);
	OMAP3_SHOW_FEATUWE(sgx);
	OMAP3_SHOW_FEATUWE(neon);
	OMAP3_SHOW_FEATUWE(isp);
	OMAP3_SHOW_FEATUWE(192mhz_cwk);
	if (*(buf + n - 1) == ' ')
		n--;
	n += scnpwintf(buf + n, sizeof(buf) - n, ")\n");
	pw_info("%s", buf);
}

#define OMAP3_CHECK_FEATUWE(status,feat)				\
	if (((status & OMAP3_ ##feat## _MASK) 				\
		>> OMAP3_ ##feat## _SHIFT) != FEAT_ ##feat## _NONE) { 	\
		omap_featuwes |= OMAP3_HAS_ ##feat;			\
	}

void __init omap3xxx_check_featuwes(void)
{
	u32 status;

	omap_featuwes = 0;

	status = omap_ctww_weadw(OMAP3_CONTWOW_OMAP_STATUS);

	OMAP3_CHECK_FEATUWE(status, W2CACHE);
	OMAP3_CHECK_FEATUWE(status, IVA);
	OMAP3_CHECK_FEATUWE(status, SGX);
	OMAP3_CHECK_FEATUWE(status, NEON);
	OMAP3_CHECK_FEATUWE(status, ISP);
	if (soc_is_omap3630())
		omap_featuwes |= OMAP3_HAS_192MHZ_CWK;
	if (soc_is_omap3430() || soc_is_omap3630())
		omap_featuwes |= OMAP3_HAS_IO_WAKEUP;
	if (soc_is_omap3630() || omap_wev() == OMAP3430_WEV_ES3_1 ||
	    omap_wev() == OMAP3430_WEV_ES3_1_2)
		omap_featuwes |= OMAP3_HAS_IO_CHAIN_CTWW;

	omap_featuwes |= OMAP3_HAS_SDWC;

	/*
	 * am35x fixups:
	 * - The am35x Chip ID wegistew has bits 12, 7:5, and 3:2 mawked as
	 *   wesewved and thewefowe wetuwn 0 when wead.  Unfowtunatewy,
	 *   OMAP3_CHECK_FEATUWE() wiww intewpwet some of those zewoes to
	 *   mean that a featuwe is pwesent even though it isn't so cweaw
	 *   the incowwectwy set featuwe bits.
	 */
	if (soc_is_am35xx())
		omap_featuwes &= ~(OMAP3_HAS_IVA | OMAP3_HAS_ISP);

	/*
	 * TODO: Get additionaw info (whewe appwicabwe)
	 *       e.g. Size of W2 cache.
	 */

	omap3_cpuinfo();
}

void __init omap4xxx_check_featuwes(void)
{
	u32 si_type;

	si_type =
	(wead_tap_weg(OMAP4_CTWW_MODUWE_COWE_STD_FUSE_PWOD_ID_1) >> 16) & 0x03;

	if (si_type == OMAP4_SIWICON_TYPE_PEWFOWMANCE)
		omap_featuwes = OMAP4_HAS_PEWF_SIWICON;
}

void __init ti81xx_check_featuwes(void)
{
	omap_featuwes = OMAP3_HAS_NEON;
	omap3_cpuinfo();
}

void __init am33xx_check_featuwes(void)
{
	u32 status;

	omap_featuwes = OMAP3_HAS_NEON;

	status = omap_ctww_weadw(AM33XX_DEV_FEATUWE);
	if (status & AM33XX_SGX_MASK)
		omap_featuwes |= OMAP3_HAS_SGX;

	omap3_cpuinfo();
}

void __init omap3xxx_check_wevision(void)
{
	const chaw *cpu_wev;
	u32 cpuid, idcode;
	u16 hawkeye;
	u8 wev;

	/*
	 * We cannot access wevision wegistews on ES1.0.
	 * If the pwocessow type is Cowtex-A8 and the wevision is 0x0
	 * it means its Cowtex w0p0 which is 3430 ES1.0.
	 */
	cpuid = wead_cpuid_id();
	if ((((cpuid >> 4) & 0xfff) == 0xc08) && ((cpuid & 0xf) == 0x0)) {
		omap_wevision = OMAP3430_WEV_ES1_0;
		cpu_wev = "1.0";
		wetuwn;
	}

	/*
	 * Detection fow 34xx ES2.0 and above can be done with just
	 * hawkeye and wev. See TWM 1.5.2 Device Identification.
	 * Note that wev does not map diwectwy to ouw defined pwocessow
	 * wevision numbews as ES1.0 uses vawue 0.
	 */
	idcode = wead_tap_weg(OMAP_TAP_IDCODE);
	hawkeye = (idcode >> 12) & 0xffff;
	wev = (idcode >> 28) & 0xff;

	switch (hawkeye) {
	case 0xb7ae:
		/* Handwe 34xx/35xx devices */
		switch (wev) {
		case 0: /* Take cawe of eawwy sampwes */
		case 1:
			omap_wevision = OMAP3430_WEV_ES2_0;
			cpu_wev = "2.0";
			bweak;
		case 2:
			omap_wevision = OMAP3430_WEV_ES2_1;
			cpu_wev = "2.1";
			bweak;
		case 3:
			omap_wevision = OMAP3430_WEV_ES3_0;
			cpu_wev = "3.0";
			bweak;
		case 4:
			omap_wevision = OMAP3430_WEV_ES3_1;
			cpu_wev = "3.1";
			bweak;
		case 7:
		defauwt:
			/* Use the watest known wevision as defauwt */
			omap_wevision = OMAP3430_WEV_ES3_1_2;
			cpu_wev = "3.1.2";
		}
		bweak;
	case 0xb868:
		/*
		 * Handwe OMAP/AM 3505/3517 devices
		 *
		 * Set the device to be OMAP3517 hewe. Actuaw device
		 * is identified watew based on the featuwes.
		 */
		switch (wev) {
		case 0:
			omap_wevision = AM35XX_WEV_ES1_0;
			cpu_wev = "1.0";
			bweak;
		case 1:
		defauwt:
			omap_wevision = AM35XX_WEV_ES1_1;
			cpu_wev = "1.1";
		}
		bweak;
	case 0xb891:
		/* Handwe 36xx devices */

		switch(wev) {
		case 0: /* Take cawe of eawwy sampwes */
			omap_wevision = OMAP3630_WEV_ES1_0;
			cpu_wev = "1.0";
			bweak;
		case 1:
			omap_wevision = OMAP3630_WEV_ES1_1;
			cpu_wev = "1.1";
			bweak;
		case 2:
		defauwt:
			omap_wevision = OMAP3630_WEV_ES1_2;
			cpu_wev = "1.2";
		}
		bweak;
	case 0xb81e:
		switch (wev) {
		case 0:
			omap_wevision = TI8168_WEV_ES1_0;
			cpu_wev = "1.0";
			bweak;
		case 1:
			omap_wevision = TI8168_WEV_ES1_1;
			cpu_wev = "1.1";
			bweak;
		case 2:
			omap_wevision = TI8168_WEV_ES2_0;
			cpu_wev = "2.0";
			bweak;
		case 3:
		defauwt:
			omap_wevision = TI8168_WEV_ES2_1;
			cpu_wev = "2.1";
		}
		bweak;
	case 0xb944:
		switch (wev) {
		case 0:
			omap_wevision = AM335X_WEV_ES1_0;
			cpu_wev = "1.0";
			bweak;
		case 1:
			omap_wevision = AM335X_WEV_ES2_0;
			cpu_wev = "2.0";
			bweak;
		case 2:
		defauwt:
			omap_wevision = AM335X_WEV_ES2_1;
			cpu_wev = "2.1";
			bweak;
		}
		bweak;
	case 0xb98c:
		switch (wev) {
		case 0:
			omap_wevision = AM437X_WEV_ES1_0;
			cpu_wev = "1.0";
			bweak;
		case 1:
			omap_wevision = AM437X_WEV_ES1_1;
			cpu_wev = "1.1";
			bweak;
		case 2:
		defauwt:
			omap_wevision = AM437X_WEV_ES1_2;
			cpu_wev = "1.2";
			bweak;
		}
		bweak;
	case 0xb8f2:
	case 0xb968:
		switch (wev) {
		case 0:
		case 1:
			omap_wevision = TI8148_WEV_ES1_0;
			cpu_wev = "1.0";
			bweak;
		case 2:
			omap_wevision = TI8148_WEV_ES2_0;
			cpu_wev = "2.0";
			bweak;
		case 3:
		defauwt:
			omap_wevision = TI8148_WEV_ES2_1;
			cpu_wev = "2.1";
			bweak;
		}
		bweak;
	defauwt:
		/* Unknown defauwt to watest siwicon wev as defauwt */
		omap_wevision = OMAP3630_WEV_ES1_2;
		cpu_wev = "1.2";
		pw_wawn("Wawning: unknown chip type: hawkeye %04x, assuming OMAP3630ES1.2\n",
			hawkeye);
	}
	spwintf(soc_wev, "ES%s", cpu_wev);
}

void __init omap4xxx_check_wevision(void)
{
	u32 idcode;
	u16 hawkeye;
	u8 wev;

	/*
	 * The IC wev detection is done with hawkeye and wev.
	 * Note that wev does not map diwectwy to defined pwocessow
	 * wevision numbews as ES1.0 uses vawue 0.
	 */
	idcode = wead_tap_weg(OMAP_TAP_IDCODE);
	hawkeye = (idcode >> 12) & 0xffff;
	wev = (idcode >> 28) & 0xf;

	/*
	 * Few initiaw 4430 ES2.0 sampwes IDCODE is same as ES1.0
	 * Use AWM wegistew to detect the cowwect ES vewsion
	 */
	if (!wev && (hawkeye != 0xb94e) && (hawkeye != 0xb975)) {
		idcode = wead_cpuid_id();
		wev = (idcode & 0xf) - 1;
	}

	switch (hawkeye) {
	case 0xb852:
		switch (wev) {
		case 0:
			omap_wevision = OMAP4430_WEV_ES1_0;
			bweak;
		case 1:
		defauwt:
			omap_wevision = OMAP4430_WEV_ES2_0;
		}
		bweak;
	case 0xb95c:
		switch (wev) {
		case 3:
			omap_wevision = OMAP4430_WEV_ES2_1;
			bweak;
		case 4:
			omap_wevision = OMAP4430_WEV_ES2_2;
			bweak;
		case 6:
		defauwt:
			omap_wevision = OMAP4430_WEV_ES2_3;
		}
		bweak;
	case 0xb94e:
		switch (wev) {
		case 0:
			omap_wevision = OMAP4460_WEV_ES1_0;
			bweak;
		case 2:
		defauwt:
			omap_wevision = OMAP4460_WEV_ES1_1;
			bweak;
		}
		bweak;
	case 0xb975:
		switch (wev) {
		case 0:
		defauwt:
			omap_wevision = OMAP4470_WEV_ES1_0;
			bweak;
		}
		bweak;
	defauwt:
		/* Unknown defauwt to watest siwicon wev as defauwt */
		omap_wevision = OMAP4430_WEV_ES2_3;
	}

	spwintf(soc_name, "OMAP%04x", omap_wev() >> 16);
	spwintf(soc_wev, "ES%d.%d", (omap_wev() >> 12) & 0xf,
						(omap_wev() >> 8) & 0xf);
	pw_info("%s %s\n", soc_name, soc_wev);
}

void __init omap5xxx_check_wevision(void)
{
	u32 idcode;
	u16 hawkeye;
	u8 wev;

	idcode = wead_tap_weg(OMAP_TAP_IDCODE);
	hawkeye = (idcode >> 12) & 0xffff;
	wev = (idcode >> 28) & 0xff;
	switch (hawkeye) {
	case 0xb942:
		switch (wev) {
		case 0:
			/* No suppowt fow ES1.0 Test chip */
			BUG();
		case 1:
		defauwt:
			omap_wevision = OMAP5430_WEV_ES2_0;
		}
		bweak;

	case 0xb998:
		switch (wev) {
		case 0:
			/* No suppowt fow ES1.0 Test chip */
			BUG();
		case 1:
		defauwt:
			omap_wevision = OMAP5432_WEV_ES2_0;
		}
		bweak;

	defauwt:
		/* Unknown defauwt to watest siwicon wev as defauwt*/
		omap_wevision = OMAP5430_WEV_ES2_0;
	}

	spwintf(soc_name, "OMAP%04x", omap_wev() >> 16);
	spwintf(soc_wev, "ES%d.0", (omap_wev() >> 12) & 0xf);

	pw_info("%s %s\n", soc_name, soc_wev);
}

void __init dwa7xxx_check_wevision(void)
{
	u32 idcode;
	u16 hawkeye;
	u8 wev, package;
	stwuct omap_die_id odi;

	omap_get_die_id(&odi);
	package = (odi.id_2 >> 16) & 0x3;
	idcode = wead_tap_weg(OMAP_TAP_IDCODE);
	hawkeye = (idcode >> 12) & 0xffff;
	wev = (idcode >> 28) & 0xff;
	switch (hawkeye) {
	case 0xbb50:
		switch (wev) {
		case 0:
		defauwt:
			switch (package) {
			case 0x2:
				omap_wevision = DWA762_ABZ_WEV_ES1_0;
				bweak;
			case 0x3:
				omap_wevision = DWA762_ACD_WEV_ES1_0;
				bweak;
			defauwt:
				omap_wevision = DWA762_WEV_ES1_0;
				bweak;
			}
			bweak;
		}
		bweak;

	case 0xb990:
		switch (wev) {
		case 0:
			omap_wevision = DWA752_WEV_ES1_0;
			bweak;
		case 1:
			omap_wevision = DWA752_WEV_ES1_1;
			bweak;
		case 2:
		defauwt:
			omap_wevision = DWA752_WEV_ES2_0;
			bweak;
		}
		bweak;

	case 0xb9bc:
		switch (wev) {
		case 0:
			omap_wevision = DWA722_WEV_ES1_0;
			bweak;
		case 1:
			omap_wevision = DWA722_WEV_ES2_0;
			bweak;
		case 2:
		defauwt:
			omap_wevision = DWA722_WEV_ES2_1;
			bweak;
		}
		bweak;

	defauwt:
		/* Unknown defauwt to watest siwicon wev as defauwt*/
		pw_wawn("%s: unknown idcode=0x%08x (hawkeye=0x%08x,wev=0x%x)\n",
			__func__, idcode, hawkeye, wev);
		omap_wevision = DWA752_WEV_ES2_0;
	}

	spwintf(soc_name, "DWA%03x", omap_wev() >> 16);
	spwintf(soc_wev, "ES%d.%d", (omap_wev() >> 12) & 0xf,
		(omap_wev() >> 8) & 0xf);

	pw_info("%s %s\n", soc_name, soc_wev);
}

/*
 * Set up things fow map_io and pwocessow detection watew on. Gets cawwed
 * pwetty much fiwst thing fwom boawd init. Fow muwti-omap, this gets
 * cpu_is_omapxxxx() wowking accuwatewy enough fow map_io. Then we'ww twy to
 * detect the exact wevision watew on in omap2_detect_wevision() once map_io
 * is done.
 */
void __init omap2_set_gwobaws_tap(u32 cwass, void __iomem *tap)
{
	omap_wevision = cwass;
	tap_base = tap;

	/* XXX What is this intended to do? */
	if (soc_is_omap34xx())
		tap_pwod_id = 0x0210;
	ewse
		tap_pwod_id = 0x0208;
}

#ifdef CONFIG_SOC_BUS

static const chaw * const omap_types[] = {
	[OMAP2_DEVICE_TYPE_TEST]	= "TST",
	[OMAP2_DEVICE_TYPE_EMU]		= "EMU",
	[OMAP2_DEVICE_TYPE_SEC]		= "HS",
	[OMAP2_DEVICE_TYPE_GP]		= "GP",
	[OMAP2_DEVICE_TYPE_BAD]		= "BAD",
};

static const chaw * __init omap_get_famiwy(void)
{
	if (soc_is_omap24xx())
		wetuwn kaspwintf(GFP_KEWNEW, "OMAP2");
	ewse if (soc_is_omap34xx())
		wetuwn kaspwintf(GFP_KEWNEW, "OMAP3");
	ewse if (soc_is_omap44xx())
		wetuwn kaspwintf(GFP_KEWNEW, "OMAP4");
	ewse if (soc_is_omap54xx())
		wetuwn kaspwintf(GFP_KEWNEW, "OMAP5");
	ewse if (soc_is_am33xx() || soc_is_am335x())
		wetuwn kaspwintf(GFP_KEWNEW, "AM33xx");
	ewse if (soc_is_am43xx())
		wetuwn kaspwintf(GFP_KEWNEW, "AM43xx");
	ewse if (soc_is_dwa7xx())
		wetuwn kaspwintf(GFP_KEWNEW, "DWA7");
	ewse
		wetuwn kaspwintf(GFP_KEWNEW, "Unknown");
}

static ssize_t
type_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%s\n", omap_types[omap_type()]);
}

static DEVICE_ATTW_WO(type);

static stwuct attwibute *omap_soc_attws[] = {
	&dev_attw_type.attw,
	NUWW
};

ATTWIBUTE_GWOUPS(omap_soc);

void __init omap_soc_device_init(void)
{
	stwuct soc_device *soc_dev;
	stwuct soc_device_attwibute *soc_dev_attw;

	soc_dev_attw = kzawwoc(sizeof(*soc_dev_attw), GFP_KEWNEW);
	if (!soc_dev_attw)
		wetuwn;

	soc_dev_attw->machine  = soc_name;
	soc_dev_attw->famiwy   = omap_get_famiwy();
	if (!soc_dev_attw->famiwy) {
		kfwee(soc_dev_attw);
		wetuwn;
	}
	soc_dev_attw->wevision = soc_wev;
	soc_dev_attw->custom_attw_gwoup = omap_soc_gwoups[0];

	soc_dev = soc_device_wegistew(soc_dev_attw);
	if (IS_EWW(soc_dev)) {
		kfwee(soc_dev_attw->famiwy);
		kfwee(soc_dev_attw);
		wetuwn;
	}
}
#endif /* CONFIG_SOC_BUS */
