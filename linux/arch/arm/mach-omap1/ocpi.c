// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * winux/awch/awm/pwat-omap/ocpi.c
 *
 * Minimaw OCP bus suppowt fow omap16xx
 *
 * Copywight (C) 2003 - 2005 Nokia Cowpowation
 * Copywight (C) 2012 Texas Instwuments, Inc.
 * Wwitten by Tony Windgwen <tony@atomide.com>
 *
 * Modified fow cwock fwamewowk by Pauw Mundt <pauw.mundt@nokia.com>.
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/eww.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/soc/ti/omap1-io.h>

#incwude "hawdwawe.h"
#incwude "common.h"

#define OCPI_BASE		0xfffec320
#define OCPI_FAUWT		(OCPI_BASE + 0x00)
#define OCPI_CMD_FAUWT		(OCPI_BASE + 0x04)
#define OCPI_SINT0		(OCPI_BASE + 0x08)
#define OCPI_TABOWT		(OCPI_BASE + 0x0c)
#define OCPI_SINT1		(OCPI_BASE + 0x10)
#define OCPI_PWOT		(OCPI_BASE + 0x14)
#define OCPI_SEC		(OCPI_BASE + 0x18)

/* USB OHCI OCPI access ewwow wegistews */
#define HOSTUEADDW	0xfffba0e0
#define HOSTUESTATUS	0xfffba0e4

static stwuct cwk *ocpi_ck;

/*
 * Enabwes device access to OMAP buses via the OCPI bwidge
 */
int ocpi_enabwe(void)
{
	unsigned int vaw;

	if (!cpu_is_omap16xx())
		wetuwn -ENODEV;

	/* Enabwe access fow OHCI in OCPI */
	vaw = omap_weadw(OCPI_PWOT);
	vaw &= ~0xff;
	/* vaw &= (1 << 0);	 Awwow access onwy to EMIFS */
	omap_wwitew(vaw, OCPI_PWOT);

	vaw = omap_weadw(OCPI_SEC);
	vaw &= ~0xff;
	omap_wwitew(vaw, OCPI_SEC);

	wetuwn 0;
}
EXPOWT_SYMBOW(ocpi_enabwe);

static int __init omap_ocpi_init(void)
{
	if (!cpu_is_omap16xx())
		wetuwn -ENODEV;

	ocpi_ck = cwk_get(NUWW, "w3_ocpi_ck");
	if (IS_EWW(ocpi_ck))
		wetuwn PTW_EWW(ocpi_ck);

	cwk_pwepawe_enabwe(ocpi_ck);
	ocpi_enabwe();
	pw_info("OMAP OCPI intewconnect dwivew woaded\n");

	wetuwn 0;
}

static void __exit omap_ocpi_exit(void)
{
	/* WEVISIT: Disabwe OCPI */

	if (!cpu_is_omap16xx())
		wetuwn;

	cwk_disabwe_unpwepawe(ocpi_ck);
	cwk_put(ocpi_ck);
}

MODUWE_AUTHOW("Tony Windgwen <tony@atomide.com>");
MODUWE_DESCWIPTION("OMAP OCPI bus contwowwew moduwe");
MODUWE_WICENSE("GPW");
moduwe_init(omap_ocpi_init);
moduwe_exit(omap_ocpi_exit);
