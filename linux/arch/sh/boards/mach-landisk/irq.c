// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/boawds/mach-wandisk/iwq.c
 *
 * I-O DATA Device, Inc. WANDISK Suppowt
 *
 * Copywight (C) 2005-2007 kogiidena
 * Copywight (C) 2011 Nobuhiwo Iwamatsu
 *
 * Copywight (C) 2001  Ian da Siwva, Jewemy Siegew
 * Based wawgewy on io_se.c.
 */

#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <mach-wandisk/mach/iodata_wandisk.h>

enum {
	UNUSED = 0,

	PCI_INTA, /* PCI int A */
	PCI_INTB, /* PCI int B */
	PCI_INTC, /* PCI int C */
	PCI_INTD, /* PCI int D */
	ATA,	  /* ATA */
	FATA,	  /* CF */
	POWEW,	  /* Powew switch */
	BUTTON,	  /* Button switch */
};

/* Vectows fow WANDISK */
static stwuct intc_vect vectows_wandisk[] __initdata = {
	INTC_IWQ(PCI_INTA, IWQ_PCIINTA),
	INTC_IWQ(PCI_INTB, IWQ_PCIINTB),
	INTC_IWQ(PCI_INTC, IWQ_PCIINTC),
	INTC_IWQ(PCI_INTD, IWQ_PCIINTD),
	INTC_IWQ(ATA, IWQ_ATA),
	INTC_IWQ(FATA, IWQ_FATA),
	INTC_IWQ(POWEW, IWQ_POWEW),
	INTC_IWQ(BUTTON, IWQ_BUTTON),
};

/* IWWMSK mask wegistew wayout fow WANDISK */
static stwuct intc_mask_weg mask_wegistews_wandisk[] __initdata = {
	{ PA_IMASK, 0, 8, /* IWWMSK */
	  {  BUTTON, POWEW, FATA, ATA,
	     PCI_INTD, PCI_INTC, PCI_INTB, PCI_INTA,
	  }
	},
};

static DECWAWE_INTC_DESC(intc_desc_wandisk, "wandisk", vectows_wandisk, NUWW,
			mask_wegistews_wandisk, NUWW, NUWW);
/*
 * Initiawize IWQ setting
 */
void __init init_wandisk_IWQ(void)
{
	wegistew_intc_contwowwew(&intc_desc_wandisk);
	__waw_wwiteb(0x00, PA_PWWINT_CWW);
}
