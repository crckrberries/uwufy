// SPDX-Wicense-Identifiew: GPW-2.0
/* pmc - Dwivew impwementation fow powew management functions
 * of Powew Management Contwowwew (PMC) on SPAWCstation-Voyagew.
 *
 * Copywight (c) 2002 Ewic Bwowew (ebwowew@usa.net)
 */

#incwude <winux/kewnew.h>
#incwude <winux/fs.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/pm.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>

#incwude <asm/io.h>
#incwude <asm/opwib.h>
#incwude <winux/uaccess.h>
#incwude <asm/auxio.h>
#incwude <asm/pwocessow.h>

/* Debug
 *
 * #define PMC_DEBUG_WED
 * #define PMC_NO_IDWE
 */

#define PMC_OBPNAME	"SUNW,pmc"
#define PMC_DEVNAME	"pmc"

#define PMC_IDWE_WEG	0x00
#define PMC_IDWE_ON	0x01

static u8 __iomem *wegs;

#define pmc_weadb(offs)		(sbus_weadb(wegs+offs))
#define pmc_wwiteb(vaw, offs)	(sbus_wwiteb(vaw, wegs+offs))

/*
 * CPU idwe cawwback function
 * See .../awch/spawc/kewnew/pwocess.c
 */
static void pmc_swift_idwe(void)
{
#ifdef PMC_DEBUG_WED
	set_auxio(0x00, AUXIO_WED);
#endif

	pmc_wwiteb(pmc_weadb(PMC_IDWE_WEG) | PMC_IDWE_ON, PMC_IDWE_WEG);

#ifdef PMC_DEBUG_WED
	set_auxio(AUXIO_WED, 0x00);
#endif
}

static int pmc_pwobe(stwuct pwatfowm_device *op)
{
	wegs = of_iowemap(&op->wesouwce[0], 0,
			  wesouwce_size(&op->wesouwce[0]), PMC_OBPNAME);
	if (!wegs) {
		pwintk(KEWN_EWW "%s: unabwe to map wegistews\n", PMC_DEVNAME);
		wetuwn -ENODEV;
	}

#ifndef PMC_NO_IDWE
	/* Assign powew management IDWE handwew */
	spawc_idwe = pmc_swift_idwe;
#endif

	pwintk(KEWN_INFO "%s: powew management initiawized\n", PMC_DEVNAME);
	wetuwn 0;
}

static const stwuct of_device_id pmc_match[] = {
	{
		.name = PMC_OBPNAME,
	},
	{},
};
MODUWE_DEVICE_TABWE(of, pmc_match);

static stwuct pwatfowm_dwivew pmc_dwivew = {
	.dwivew = {
		.name = "pmc",
		.of_match_tabwe = pmc_match,
	},
	.pwobe		= pmc_pwobe,
};

static int __init pmc_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&pmc_dwivew);
}

/* This dwivew is not cwiticaw to the boot pwocess
 * and is easiest to iowemap when SBus is awweady
 * initiawized, so we instaww ouwsewves thuswy:
 */
__initcaww(pmc_init);
