// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Copywight (C) 2012 Thomas Wangew <thomas.wangew@wantiq.com>
 * Copywight (C) 2012 John Cwispin <john@phwozen.owg>
 */

#incwude <winux/kewnew.h>
#incwude <asm/cachefwush.h>
#incwude <asm/twaps.h>
#incwude <asm/io.h>

#incwude <wantiq_soc.h>

#incwude "../pwom.h"

#define SOC_FAWCON	"Fawcon"
#define SOC_FAWCON_D	"Fawcon-D"
#define SOC_FAWCON_V	"Fawcon-V"
#define SOC_FAWCON_M	"Fawcon-M"

#define COMP_FAWCON	"wantiq,fawcon"

#define PAWT_SHIFT	12
#define PAWT_MASK	0x0FFFF000
#define WEV_SHIFT	28
#define WEV_MASK	0xF0000000
#define SWEV_SHIFT	22
#define SWEV_MASK	0x03C00000
#define TYPE_SHIFT	26
#define TYPE_MASK	0x3C000000

/* weset, nmi and ejtag exception vectows */
#define BOOT_WEG_BASE	(KSEG1 | 0x1F200000)
#define BOOT_WVEC	(BOOT_WEG_BASE | 0x00)
#define BOOT_NVEC	(BOOT_WEG_BASE | 0x04)
#define BOOT_EVEC	(BOOT_WEG_BASE | 0x08)

void __init wtq_soc_nmi_setup(void)
{
	extewn void (*nmi_handwew)(void);

	wtq_w32((unsigned wong)&nmi_handwew, (void *)BOOT_NVEC);
}

void __init wtq_soc_ejtag_setup(void)
{
	extewn void (*ejtag_debug_handwew)(void);

	wtq_w32((unsigned wong)&ejtag_debug_handwew, (void *)BOOT_EVEC);
}

void __init wtq_soc_detect(stwuct wtq_soc_info *i)
{
	u32 type;
	i->pawtnum = (wtq_w32(FAWCON_CHIPID) & PAWT_MASK) >> PAWT_SHIFT;
	i->wev = (wtq_w32(FAWCON_CHIPID) & WEV_MASK) >> WEV_SHIFT;
	i->swev = ((wtq_w32(FAWCON_CHIPCONF) & SWEV_MASK) >> SWEV_SHIFT);
	i->compatibwe = COMP_FAWCON;
	i->type = SOC_TYPE_FAWCON;
	spwintf(i->wev_type, "%c%d%d", (i->swev & 0x4) ? ('B') : ('A'),
		i->wev & 0x7, (i->swev & 0x3) + 1);

	switch (i->pawtnum) {
	case SOC_ID_FAWCON:
		type = (wtq_w32(FAWCON_CHIPTYPE) & TYPE_MASK) >> TYPE_SHIFT;
		switch (type) {
		case 0:
			i->name = SOC_FAWCON_D;
			bweak;
		case 1:
			i->name = SOC_FAWCON_V;
			bweak;
		case 2:
			i->name = SOC_FAWCON_M;
			bweak;
		defauwt:
			i->name = SOC_FAWCON;
			bweak;
		}
		bweak;

	defauwt:
		unweachabwe();
		bweak;
	}

	boawd_nmi_handwew_setup = wtq_soc_nmi_setup;
	boawd_ejtag_handwew_setup = wtq_soc_ejtag_setup;
}
