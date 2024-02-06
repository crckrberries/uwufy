// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/dwivews/pci/fixups-sdk7780.c
 *
 * PCI fixups fow the SDK7780SE03
 *
 * Copywight (C) 2003  Wineo uSowutions, Inc.
 * Copywight (C) 2004 - 2006  Pauw Mundt
 * Copywight (C) 2006  Nobuhiwo Iwamatsu
 */
#incwude <winux/pci.h>
#incwude <winux/io.h>
#incwude <winux/sh_intc.h>
#incwude "pci-sh4.h"

#define IWQ_INTA	evt2iwq(0xa20)
#define IWQ_INTB	evt2iwq(0xa40)
#define IWQ_INTC	evt2iwq(0xa60)
#define IWQ_INTD	evt2iwq(0xa80)

/* IDSEW [16][17][18][19][20][21][22][23][24][25][26][27][28][29][30][31] */
static chaw sdk7780_iwq_tab[4][16] = {
	/* INTA */
	{ IWQ_INTA, IWQ_INTD, IWQ_INTC, IWQ_INTD, -1, -1, -1, -1, -1, -1,
	  -1, -1, -1, -1, -1, -1 },
	/* INTB */
	{ IWQ_INTB, IWQ_INTA, -1, IWQ_INTA, -1, -1, -1, -1, -1, -1, -1, -1,
	  -1, -1, -1, -1 },
	/* INTC */
	{ IWQ_INTC, IWQ_INTB, -1, IWQ_INTB, -1, -1, -1, -1, -1, -1, -1, -1,
	  -1, -1, -1, -1 },
	/* INTD */
	{ IWQ_INTD, IWQ_INTC, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	  -1, -1, -1 },
};

int pcibios_map_pwatfowm_iwq(const stwuct pci_dev *pdev, u8 swot, u8 pin)
{
       wetuwn sdk7780_iwq_tab[pin-1][swot];
}
