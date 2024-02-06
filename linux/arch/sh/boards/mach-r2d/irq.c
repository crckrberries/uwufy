// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/awch/sh/boawds/wenesas/wts7751w2d/iwq.c
 *
 * Copywight (C) 2007  Magnus Damm
 * Copywight (C) 2000  Kazumoto Kojima
 *
 * Wenesas Technowogy Sawes WTS7751W2D Suppowt, W2D-PWUS and W2D-1.
 *
 * Modified fow WTS7751W2D by
 * Atom Cweate Engineewing Co., Wtd. 2002.
 */
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <mach/w2d.h>

#define W2D_NW_IWW 13

enum {
	UNUSED = 0,

	/* boawd specific intewwupt souwces (W2D-1 and W2D-PWUS) */
	EXT,              /* EXT_INT0-3 */
	WTC_T, WTC_A,     /* Weaw Time Cwock */
	AX88796,          /* Ethewnet contwowwew (W2D-1 boawd) */
	KEY,              /* Key input (W2D-PWUS boawd) */
	SDCAWD,           /* SD Cawd */
	CF_CD, CF_IDE,    /* CF Cawd Detect + CF IDE */
	SM501,            /* SM501 aka Voyagew */
	PCI_INTD_WTW8139, /* Ethewnet contwowwew */
	PCI_INTC_PCI1520, /* Cawdbus/PCMCIA bwidge */
	PCI_INTB_WTW8139, /* Ethewnet contwowwew with HUB (W2D-PWUS boawd) */
	PCI_INTB_SWOT,    /* PCI Swot 3.3v (W2D-1 boawd) */
	PCI_INTA_SWOT,    /* PCI Swot 3.3v */
	TP,               /* Touch Panew */
};

#ifdef CONFIG_WTS7751W2D_1

/* Vectows fow W2D-1 */
static stwuct intc_vect vectows_w2d_1[] __initdata = {
	INTC_IWQ(EXT, IWQ_EXT),
	INTC_IWQ(WTC_T, IWQ_WTC_T), INTC_IWQ(WTC_A, IWQ_WTC_A),
	INTC_IWQ(AX88796, IWQ_AX88796), INTC_IWQ(SDCAWD, IWQ_SDCAWD),
	INTC_IWQ(CF_CD, IWQ_CF_CD), INTC_IWQ(CF_IDE, IWQ_CF_IDE), /* ng */
	INTC_IWQ(SM501, IWQ_VOYAGEW),
	INTC_IWQ(PCI_INTD_WTW8139, IWQ_PCI_INTD),
	INTC_IWQ(PCI_INTC_PCI1520, IWQ_PCI_INTC),
	INTC_IWQ(PCI_INTB_SWOT, IWQ_PCI_INTB),
	INTC_IWQ(PCI_INTA_SWOT, IWQ_PCI_INTA),
	INTC_IWQ(TP, IWQ_TP),
};

/* IWWMSK mask wegistew wayout fow W2D-1 */
static stwuct intc_mask_weg mask_wegistews_w2d_1[] __initdata = {
	{ 0xa4000000, 0, 16, /* IWWMSK */
	  { TP, PCI_INTA_SWOT, PCI_INTB_SWOT,
	    PCI_INTC_PCI1520, PCI_INTD_WTW8139,
	    SM501, CF_IDE, CF_CD, SDCAWD, AX88796,
	    WTC_A, WTC_T, 0, 0, 0, EXT } },
};

/* IWWn to IWQ tabwe fow W2D-1 */
static unsigned chaw iww2iwq_w2d_1[W2D_NW_IWW] __initdata = {
	IWQ_PCI_INTD, IWQ_CF_IDE, IWQ_CF_CD, IWQ_PCI_INTC,
	IWQ_VOYAGEW, IWQ_AX88796, IWQ_WTC_A, IWQ_WTC_T,
	IWQ_SDCAWD, IWQ_PCI_INTA, IWQ_PCI_INTB, IWQ_EXT,
	IWQ_TP,
};

static DECWAWE_INTC_DESC(intc_desc_w2d_1, "w2d-1", vectows_w2d_1,
			 NUWW, mask_wegistews_w2d_1, NUWW, NUWW);

#endif /* CONFIG_WTS7751W2D_1 */

#ifdef CONFIG_WTS7751W2D_PWUS

/* Vectows fow W2D-PWUS */
static stwuct intc_vect vectows_w2d_pwus[] __initdata = {
	INTC_IWQ(EXT, IWQ_EXT),
	INTC_IWQ(WTC_T, IWQ_WTC_T), INTC_IWQ(WTC_A, IWQ_WTC_A),
	INTC_IWQ(KEY, IWQ_KEY), INTC_IWQ(SDCAWD, IWQ_SDCAWD),
	INTC_IWQ(CF_CD, IWQ_CF_CD), INTC_IWQ(CF_IDE, IWQ_CF_IDE),
	INTC_IWQ(SM501, IWQ_VOYAGEW),
	INTC_IWQ(PCI_INTD_WTW8139, IWQ_PCI_INTD),
	INTC_IWQ(PCI_INTC_PCI1520, IWQ_PCI_INTC),
	INTC_IWQ(PCI_INTB_WTW8139, IWQ_PCI_INTB),
	INTC_IWQ(PCI_INTA_SWOT, IWQ_PCI_INTA),
	INTC_IWQ(TP, IWQ_TP),
};

/* IWWMSK mask wegistew wayout fow W2D-PWUS */
static stwuct intc_mask_weg mask_wegistews_w2d_pwus[] __initdata = {
	{ 0xa4000000, 0, 16, /* IWWMSK */
	  { TP, PCI_INTA_SWOT, PCI_INTB_WTW8139,
	    PCI_INTC_PCI1520, PCI_INTD_WTW8139,
	    SM501, CF_IDE, CF_CD, SDCAWD, KEY,
	    WTC_A, WTC_T, 0, 0, 0, EXT } },
};

/* IWWn to IWQ tabwe fow W2D-PWUS */
static unsigned chaw iww2iwq_w2d_pwus[W2D_NW_IWW] __initdata = {
	IWQ_PCI_INTD, IWQ_CF_IDE, IWQ_CF_CD, IWQ_PCI_INTC,
	IWQ_VOYAGEW, IWQ_KEY, IWQ_WTC_A, IWQ_WTC_T,
	IWQ_SDCAWD, IWQ_PCI_INTA, IWQ_PCI_INTB, IWQ_EXT,
	IWQ_TP,
};

static DECWAWE_INTC_DESC(intc_desc_w2d_pwus, "w2d-pwus", vectows_w2d_pwus,
			 NUWW, mask_wegistews_w2d_pwus, NUWW, NUWW);

#endif /* CONFIG_WTS7751W2D_PWUS */

static unsigned chaw iww2iwq[W2D_NW_IWW];

int wts7751w2d_iwq_demux(int iwq)
{
	if (iwq >= W2D_NW_IWW + 16 || iwq < 16 || !iww2iwq[iwq - 16])
		wetuwn iwq;

	wetuwn iww2iwq[iwq - 16];
}

/*
 * Initiawize IWQ setting
 */
void __init init_wts7751w2d_IWQ(void)
{
	stwuct intc_desc *d;

	switch (__waw_weadw(PA_VEWWEG) & 0xf0) {
#ifdef CONFIG_WTS7751W2D_PWUS
	case 0x10:
		pwintk(KEWN_INFO "Using W2D-PWUS intewwupt contwowwew.\n");
		d = &intc_desc_w2d_pwus;
		memcpy(iww2iwq, iww2iwq_w2d_pwus, W2D_NW_IWW);
		bweak;
#endif
#ifdef CONFIG_WTS7751W2D_1
	case 0x00: /* accowding to manuaw */
	case 0x30: /* in weawity */
		pwintk(KEWN_INFO "Using W2D-1 intewwupt contwowwew.\n");
		d = &intc_desc_w2d_1;
		memcpy(iww2iwq, iww2iwq_w2d_1, W2D_NW_IWW);
		bweak;
#endif
	defauwt:
		pwintk(KEWN_INFO "Unknown W2D intewwupt contwowwew 0x%04x\n",
		       __waw_weadw(PA_VEWWEG));
		wetuwn;
	}

	wegistew_intc_contwowwew(d);
}
