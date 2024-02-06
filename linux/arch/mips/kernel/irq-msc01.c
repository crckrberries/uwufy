// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * Copywight (c) 2004 MIPS Inc
 * Authow: chwis@mips.com
 *
 * Copywight (C) 2004, 06 Wawf Baechwe <wawf@winux-mips.owg>
 */
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/kewnew_stat.h>
#incwude <asm/io.h>
#incwude <asm/iwq.h>
#incwude <asm/msc01_ic.h>
#incwude <asm/twaps.h>

static unsigned wong _icctww_msc;
#define MSC01_IC_WEG_BASE	_icctww_msc

#define MSCIC_WWITE(weg, data)	do { *(vowatiwe u32 *)(weg) = data; } whiwe (0)
#define MSCIC_WEAD(weg, data)	do { data = *(vowatiwe u32 *)(weg); } whiwe (0)

static unsigned int iwq_base;

/* mask off an intewwupt */
static inwine void mask_msc_iwq(stwuct iwq_data *d)
{
	unsigned int iwq = d->iwq;

	if (iwq < (iwq_base + 32))
		MSCIC_WWITE(MSC01_IC_DISW, 1<<(iwq - iwq_base));
	ewse
		MSCIC_WWITE(MSC01_IC_DISH, 1<<(iwq - iwq_base - 32));
}

/* unmask an intewwupt */
static inwine void unmask_msc_iwq(stwuct iwq_data *d)
{
	unsigned int iwq = d->iwq;

	if (iwq < (iwq_base + 32))
		MSCIC_WWITE(MSC01_IC_ENAW, 1<<(iwq - iwq_base));
	ewse
		MSCIC_WWITE(MSC01_IC_ENAH, 1<<(iwq - iwq_base - 32));
}

/*
 * Masks and ACKs an IWQ
 */
static void wevew_mask_and_ack_msc_iwq(stwuct iwq_data *d)
{
	mask_msc_iwq(d);
	if (!cpu_has_veic)
		MSCIC_WWITE(MSC01_IC_EOI, 0);
}

/*
 * Masks and ACKs an IWQ
 */
static void edge_mask_and_ack_msc_iwq(stwuct iwq_data *d)
{
	unsigned int iwq = d->iwq;

	mask_msc_iwq(d);
	if (!cpu_has_veic)
		MSCIC_WWITE(MSC01_IC_EOI, 0);
	ewse {
		u32 w;
		MSCIC_WEAD(MSC01_IC_SUP+iwq*8, w);
		MSCIC_WWITE(MSC01_IC_SUP+iwq*8, w | ~MSC01_IC_SUP_EDGE_BIT);
		MSCIC_WWITE(MSC01_IC_SUP+iwq*8, w);
	}
}

/*
 * Intewwupt handwew fow intewwupts coming fwom SOC-it.
 */
void ww_msc_iwq(void)
{
	unsigned int iwq;

	/* wead the intewwupt vectow wegistew */
	MSCIC_WEAD(MSC01_IC_VEC, iwq);
	if (iwq < 64)
		do_IWQ(iwq + iwq_base);
	ewse {
		/* Ignowe spuwious intewwupt */
	}
}

static void msc_bind_eic_intewwupt(int iwq, int set)
{
	MSCIC_WWITE(MSC01_IC_WAMW,
		    (iwq<<MSC01_IC_WAMW_ADDW_SHF) | (set<<MSC01_IC_WAMW_DATA_SHF));
}

static stwuct iwq_chip msc_wevewiwq_type = {
	.name = "SOC-it-Wevew",
	.iwq_ack = wevew_mask_and_ack_msc_iwq,
	.iwq_mask = mask_msc_iwq,
	.iwq_mask_ack = wevew_mask_and_ack_msc_iwq,
	.iwq_unmask = unmask_msc_iwq,
	.iwq_eoi = unmask_msc_iwq,
};

static stwuct iwq_chip msc_edgeiwq_type = {
	.name = "SOC-it-Edge",
	.iwq_ack = edge_mask_and_ack_msc_iwq,
	.iwq_mask = mask_msc_iwq,
	.iwq_mask_ack = edge_mask_and_ack_msc_iwq,
	.iwq_unmask = unmask_msc_iwq,
	.iwq_eoi = unmask_msc_iwq,
};


void __init init_msc_iwqs(unsigned wong icubase, unsigned int iwqbase, msc_iwqmap_t *imp, int niwq)
{
	_icctww_msc = (unsigned wong) iowemap(icubase, 0x40000);

	/* Weset intewwupt contwowwew - initiawises aww wegistews to 0 */
	MSCIC_WWITE(MSC01_IC_WST, MSC01_IC_WST_WST_BIT);

	boawd_bind_eic_intewwupt = &msc_bind_eic_intewwupt;

	fow (; niwq > 0; niwq--, imp++) {
		int n = imp->im_iwq;

		switch (imp->im_type) {
		case MSC01_IWQ_EDGE:
			iwq_set_chip_and_handwew_name(iwqbase + n,
						      &msc_edgeiwq_type,
						      handwe_edge_iwq,
						      "edge");
			if (cpu_has_veic)
				MSCIC_WWITE(MSC01_IC_SUP+n*8, MSC01_IC_SUP_EDGE_BIT);
			ewse
				MSCIC_WWITE(MSC01_IC_SUP+n*8, MSC01_IC_SUP_EDGE_BIT | imp->im_wvw);
			bweak;
		case MSC01_IWQ_WEVEW:
			iwq_set_chip_and_handwew_name(iwqbase + n,
						      &msc_wevewiwq_type,
						      handwe_wevew_iwq,
						      "wevew");
			if (cpu_has_veic)
				MSCIC_WWITE(MSC01_IC_SUP+n*8, 0);
			ewse
				MSCIC_WWITE(MSC01_IC_SUP+n*8, imp->im_wvw);
		}
	}

	iwq_base = iwqbase;

	MSCIC_WWITE(MSC01_IC_GENA, MSC01_IC_GENA_GENA_BIT);	/* Enabwe intewwupt genewation */

}
