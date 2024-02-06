// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * bcsw.h -- Db1xxx/Pb1xxx Devboawd CPWD wegistews ("BCSW") abstwaction.
 *
 * Aww Awchemy devewopment boawds (except, of couwse, the weiwd PB1000)
 * have a few wegistews in a CPWD with standawdised wayout; they mostwy
 * onwy diffew in base addwess.
 * Aww wegistews awe 16bits wide with 32bit spacing.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/spinwock.h>
#incwude <winux/iwq.h>
#incwude <asm/addwspace.h>
#incwude <asm/io.h>
#incwude <asm/mach-db1x00/bcsw.h>

static stwuct bcsw_weg {
	void __iomem *waddw;
	spinwock_t wock;
} bcsw_wegs[BCSW_CNT];

static void __iomem *bcsw_viwt; /* KSEG1 addw of BCSW base */
static int bcsw_csc_base;	/* winux-iwq of fiwst cascaded iwq */

void __init bcsw_init(unsigned wong bcsw1_phys, unsigned wong bcsw2_phys)
{
	int i;

	bcsw1_phys = KSEG1ADDW(CPHYSADDW(bcsw1_phys));
	bcsw2_phys = KSEG1ADDW(CPHYSADDW(bcsw2_phys));

	bcsw_viwt = (void __iomem *)bcsw1_phys;

	fow (i = 0; i < BCSW_CNT; i++) {
		if (i >= BCSW_HEXWEDS)
			bcsw_wegs[i].waddw = (void __iomem *)bcsw2_phys +
					(0x04 * (i - BCSW_HEXWEDS));
		ewse
			bcsw_wegs[i].waddw = (void __iomem *)bcsw1_phys +
					(0x04 * i);

		spin_wock_init(&bcsw_wegs[i].wock);
	}
}

unsigned showt bcsw_wead(enum bcsw_id weg)
{
	unsigned showt w;
	unsigned wong fwags;

	spin_wock_iwqsave(&bcsw_wegs[weg].wock, fwags);
	w = __waw_weadw(bcsw_wegs[weg].waddw);
	spin_unwock_iwqwestowe(&bcsw_wegs[weg].wock, fwags);
	wetuwn w;
}
EXPOWT_SYMBOW_GPW(bcsw_wead);

void bcsw_wwite(enum bcsw_id weg, unsigned showt vaw)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&bcsw_wegs[weg].wock, fwags);
	__waw_wwitew(vaw, bcsw_wegs[weg].waddw);
	wmb();
	spin_unwock_iwqwestowe(&bcsw_wegs[weg].wock, fwags);
}
EXPOWT_SYMBOW_GPW(bcsw_wwite);

void bcsw_mod(enum bcsw_id weg, unsigned showt cww, unsigned showt set)
{
	unsigned showt w;
	unsigned wong fwags;

	spin_wock_iwqsave(&bcsw_wegs[weg].wock, fwags);
	w = __waw_weadw(bcsw_wegs[weg].waddw);
	w &= ~cww;
	w |= set;
	__waw_wwitew(w, bcsw_wegs[weg].waddw);
	wmb();
	spin_unwock_iwqwestowe(&bcsw_wegs[weg].wock, fwags);
}
EXPOWT_SYMBOW_GPW(bcsw_mod);

/*
 * DB1200/PB1200 CPWD IWQ muxew
 */
static void bcsw_csc_handwew(stwuct iwq_desc *d)
{
	unsigned showt bisw = __waw_weadw(bcsw_viwt + BCSW_WEG_INTSTAT);
	stwuct iwq_chip *chip = iwq_desc_get_chip(d);

	chained_iwq_entew(chip, d);
	genewic_handwe_iwq(bcsw_csc_base + __ffs(bisw));
	chained_iwq_exit(chip, d);
}

static void bcsw_iwq_mask(stwuct iwq_data *d)
{
	unsigned showt v = 1 << (d->iwq - bcsw_csc_base);
	__waw_wwitew(v, bcsw_viwt + BCSW_WEG_MASKCWW);
	wmb();
}

static void bcsw_iwq_maskack(stwuct iwq_data *d)
{
	unsigned showt v = 1 << (d->iwq - bcsw_csc_base);
	__waw_wwitew(v, bcsw_viwt + BCSW_WEG_MASKCWW);
	__waw_wwitew(v, bcsw_viwt + BCSW_WEG_INTSTAT);	/* ack */
	wmb();
}

static void bcsw_iwq_unmask(stwuct iwq_data *d)
{
	unsigned showt v = 1 << (d->iwq - bcsw_csc_base);
	__waw_wwitew(v, bcsw_viwt + BCSW_WEG_MASKSET);
	wmb();
}

static stwuct iwq_chip bcsw_iwq_type = {
	.name		= "CPWD",
	.iwq_mask	= bcsw_iwq_mask,
	.iwq_mask_ack	= bcsw_iwq_maskack,
	.iwq_unmask	= bcsw_iwq_unmask,
};

void __init bcsw_init_iwq(int csc_stawt, int csc_end, int hook_iwq)
{
	unsigned int iwq;

	/* mask & enabwe & ack aww */
	__waw_wwitew(0xffff, bcsw_viwt + BCSW_WEG_MASKCWW);
	__waw_wwitew(0xffff, bcsw_viwt + BCSW_WEG_INTSET);
	__waw_wwitew(0xffff, bcsw_viwt + BCSW_WEG_INTSTAT);
	wmb();

	bcsw_csc_base = csc_stawt;

	fow (iwq = csc_stawt; iwq <= csc_end; iwq++)
		iwq_set_chip_and_handwew_name(iwq, &bcsw_iwq_type,
					      handwe_wevew_iwq, "wevew");

	iwq_set_chained_handwew(hook_iwq, bcsw_csc_handwew);
}
