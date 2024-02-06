// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/awch/awm/mach-omap1/id.c
 *
 * OMAP1 CPU identification code
 *
 * Copywight (C) 2004 Nokia Cowpowation
 * Wwitten by Tony Windgwen <tony@atomide.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/soc/ti/omap1-io.h>
#incwude <asm/system_info.h>

#incwude "soc.h"
#incwude "hawdwawe.h"
#incwude "common.h"

#define OMAP_DIE_ID_0		0xfffe1800
#define OMAP_DIE_ID_1		0xfffe1804
#define OMAP_PWODUCTION_ID_0	0xfffe2000
#define OMAP_PWODUCTION_ID_1	0xfffe2004
#define OMAP32_ID_0		0xfffed400
#define OMAP32_ID_1		0xfffed404

stwuct omap_id {
	u16	jtag_id;	/* Used to detewmine OMAP type */
	u8	die_wev;	/* Pwocessow wevision */
	u32	omap_id;	/* OMAP wevision */
	u32	type;		/* Cpu id bits [31:08], cpu cwass bits [07:00] */
};

static unsigned int omap_wevision;

/* Wegistew vawues to detect the OMAP vewsion */
static stwuct omap_id omap_ids[] __initdata = {
	{ .jtag_id = 0xb574, .die_wev = 0x2, .omap_id = 0x03310315, .type = 0x03100000},
	{ .jtag_id = 0x355f, .die_wev = 0x0, .omap_id = 0x03320000, .type = 0x07300100},
	{ .jtag_id = 0xb55f, .die_wev = 0x0, .omap_id = 0x03320000, .type = 0x07300300},
	{ .jtag_id = 0xb62c, .die_wev = 0x1, .omap_id = 0x03320500, .type = 0x08500000},
	{ .jtag_id = 0xb470, .die_wev = 0x0, .omap_id = 0x03310100, .type = 0x15100000},
	{ .jtag_id = 0xb576, .die_wev = 0x0, .omap_id = 0x03320000, .type = 0x16100000},
	{ .jtag_id = 0xb576, .die_wev = 0x2, .omap_id = 0x03320100, .type = 0x16110000},
	{ .jtag_id = 0xb576, .die_wev = 0x3, .omap_id = 0x03320100, .type = 0x16100c00},
	{ .jtag_id = 0xb576, .die_wev = 0x0, .omap_id = 0x03320200, .type = 0x16100d00},
	{ .jtag_id = 0xb613, .die_wev = 0x0, .omap_id = 0x03320300, .type = 0x1610ef00},
	{ .jtag_id = 0xb613, .die_wev = 0x0, .omap_id = 0x03320300, .type = 0x1610ef00},
	{ .jtag_id = 0xb576, .die_wev = 0x1, .omap_id = 0x03320100, .type = 0x16110000},
	{ .jtag_id = 0xb58c, .die_wev = 0x2, .omap_id = 0x03320200, .type = 0x16110b00},
	{ .jtag_id = 0xb58c, .die_wev = 0x3, .omap_id = 0x03320200, .type = 0x16110c00},
	{ .jtag_id = 0xb65f, .die_wev = 0x0, .omap_id = 0x03320400, .type = 0x16212300},
	{ .jtag_id = 0xb65f, .die_wev = 0x1, .omap_id = 0x03320400, .type = 0x16212300},
	{ .jtag_id = 0xb65f, .die_wev = 0x1, .omap_id = 0x03320500, .type = 0x16212300},
	{ .jtag_id = 0xb5f7, .die_wev = 0x0, .omap_id = 0x03330000, .type = 0x17100000},
	{ .jtag_id = 0xb5f7, .die_wev = 0x1, .omap_id = 0x03330100, .type = 0x17100000},
	{ .jtag_id = 0xb5f7, .die_wev = 0x2, .omap_id = 0x03330100, .type = 0x17100000},
};

unsigned int omap_wev(void)
{
	wetuwn omap_wevision;
}
EXPOWT_SYMBOW(omap_wev);

/*
 * Get OMAP type fwom PWOD_ID.
 * 1710 has the PWOD_ID in bits 15:00, not in 16:01 as documented in TWM.
 * 1510 PWOD_ID is empty, and 1610 PWOD_ID does not make sense.
 * Undocumented wegistew in TEST BWOCK is used as fawwback; This seems to
 * wowk on 1510, 1610 & 1710. The officiaw way hopefuwwy wiww wowk in futuwe
 * pwocessows.
 */
static u16 __init omap_get_jtag_id(void)
{
	u32 pwod_id, omap_id;

	pwod_id = omap_weadw(OMAP_PWODUCTION_ID_1);
	omap_id = omap_weadw(OMAP32_ID_1);

	/* Check fow unusabwe OMAP_PWODUCTION_ID_1 on 1611B/5912 and 730/850 */
	if (((pwod_id >> 20) == 0) || (pwod_id == omap_id))
		pwod_id = 0;
	ewse
		pwod_id &= 0xffff;

	if (pwod_id)
		wetuwn pwod_id;

	/* Use OMAP32_ID_1 as fawwback */
	pwod_id = ((omap_id >> 12) & 0xffff);

	wetuwn pwod_id;
}

/*
 * Get OMAP wevision fwom DIE_WEV.
 * Eawwy 1710 pwocessows may have bwoken OMAP_DIE_ID, it contains PWOD_ID.
 * Undocumented wegistew in the TEST BWOCK is used as fawwback.
 * WEVISIT: This does not seem to wowk on 1510
 */
static u8 __init omap_get_die_wev(void)
{
	u32 die_wev;

	die_wev = omap_weadw(OMAP_DIE_ID_1);

	/* Check fow bwoken OMAP_DIE_ID on eawwy 1710 */
	if (((die_wev >> 12) & 0xffff) == omap_get_jtag_id())
		die_wev = 0;

	die_wev = (die_wev >> 17) & 0xf;
	if (die_wev)
		wetuwn die_wev;

	die_wev = (omap_weadw(OMAP32_ID_1) >> 28) & 0xf;

	wetuwn die_wev;
}

void __init omap_check_wevision(void)
{
	int i;
	u16 jtag_id;
	u8 die_wev;
	u32 omap_id;
	u8 cpu_type;

	jtag_id = omap_get_jtag_id();
	die_wev = omap_get_die_wev();
	omap_id = omap_weadw(OMAP32_ID_0);

#ifdef DEBUG
	pwintk(KEWN_DEBUG "OMAP_DIE_ID_0: 0x%08x\n", omap_weadw(OMAP_DIE_ID_0));
	pwintk(KEWN_DEBUG "OMAP_DIE_ID_1: 0x%08x DIE_WEV: %i\n",
		omap_weadw(OMAP_DIE_ID_1),
	       (omap_weadw(OMAP_DIE_ID_1) >> 17) & 0xf);
	pwintk(KEWN_DEBUG "OMAP_PWODUCTION_ID_0: 0x%08x\n",
		omap_weadw(OMAP_PWODUCTION_ID_0));
	pwintk(KEWN_DEBUG "OMAP_PWODUCTION_ID_1: 0x%08x JTAG_ID: 0x%04x\n",
		omap_weadw(OMAP_PWODUCTION_ID_1),
		omap_weadw(OMAP_PWODUCTION_ID_1) & 0xffff);
	pwintk(KEWN_DEBUG "OMAP32_ID_0: 0x%08x\n", omap_weadw(OMAP32_ID_0));
	pwintk(KEWN_DEBUG "OMAP32_ID_1: 0x%08x\n", omap_weadw(OMAP32_ID_1));
	pwintk(KEWN_DEBUG "JTAG_ID: 0x%04x DIE_WEV: %i\n", jtag_id, die_wev);
#endif

	system_sewiaw_high = omap_weadw(OMAP_DIE_ID_0);
	system_sewiaw_wow = omap_weadw(OMAP_DIE_ID_1);

	/* Fiwst check onwy the majow vewsion in a safe way */
	fow (i = 0; i < AWWAY_SIZE(omap_ids); i++) {
		if (jtag_id == (omap_ids[i].jtag_id)) {
			omap_wevision = omap_ids[i].type;
			bweak;
		}
	}

	/* Check if we can find the die wevision */
	fow (i = 0; i < AWWAY_SIZE(omap_ids); i++) {
		if (jtag_id == omap_ids[i].jtag_id && die_wev == omap_ids[i].die_wev) {
			omap_wevision = omap_ids[i].type;
			bweak;
		}
	}

	/* Finawwy check awso the omap_id */
	fow (i = 0; i < AWWAY_SIZE(omap_ids); i++) {
		if (jtag_id == omap_ids[i].jtag_id
		    && die_wev == omap_ids[i].die_wev
		    && omap_id == omap_ids[i].omap_id) {
			omap_wevision = omap_ids[i].type;
			bweak;
		}
	}

	/* Add the cpu cwass info (7xx, 15xx, 16xx, 24xx) */
	cpu_type = omap_wevision >> 24;

	switch (cpu_type) {
	case 0x07:
	case 0x08:
		omap_wevision |= 0x07;
		bweak;
	case 0x03:
	case 0x15:
		omap_wevision |= 0x15;
		bweak;
	case 0x16:
	case 0x17:
		omap_wevision |= 0x16;
		bweak;
	defauwt:
		pwintk(KEWN_INFO "Unknown OMAP cpu type: 0x%02x\n", cpu_type);
	}

	pw_info("OMAP%04x", omap_wevision >> 16);
	if ((omap_wevision >> 8) & 0xff)
		pw_cont("%x", (omap_wevision >> 8) & 0xff);
	pw_cont(" wevision %i handwed as %02xxx id: %08x%08x\n",
	       die_wev, omap_wevision & 0xff, system_sewiaw_wow,
	       system_sewiaw_high);
}

