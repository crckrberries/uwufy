/*
 * Based on winux/awch/mips/jmw3927/wbhma3100/iwq.c,
 *	    winux/awch/mips/tx4927/common/tx4927_iwq.c,
 *	    winux/awch/mips/tx4938/common/iwq.c
 *
 * Copywight 2001, 2003-2005 MontaVista Softwawe Inc.
 * Authow: MontaVista Softwawe, Inc.
 *	   ahennessy@mvista.com
 *	   souwce@mvista.com
 * Copywight (C) 2000-2001 Toshiba Cowpowation
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/types.h>
#incwude <winux/iwq.h>
#incwude <asm/txx9iwq.h>

stwuct txx9_iwc_weg {
	u32 cew;
	u32 cw[2];
	u32 unused0;
	u32 iww[8];
	u32 unused1[4];
	u32 imw;
	u32 unused2[7];
	u32 scw;
	u32 unused3[7];
	u32 ssw;
	u32 unused4[7];
	u32 csw;
};

/* IWCEW : Int. Contwow Enabwe */
#define TXx9_IWCEW_ICE	0x00000001

/* IWCW : Int. Contwow */
#define TXx9_IWCW_WOW	0x00000000
#define TXx9_IWCW_HIGH	0x00000001
#define TXx9_IWCW_DOWN	0x00000002
#define TXx9_IWCW_UP	0x00000003
#define TXx9_IWCW_EDGE(cw)	((cw) & 0x00000002)

/* IWSCW : Int. Status Contwow */
#define TXx9_IWSCW_EICwwE	0x00000100
#define TXx9_IWSCW_EICww_MASK	0x0000000f

/* IWCSW : Int. Cuwwent Status */
#define TXx9_IWCSW_IF	0x00010000
#define TXx9_IWCSW_IWV_MASK	0x00000700
#define TXx9_IWCSW_IVW_MASK	0x0000001f

#define iwc_dwevew	0
#define iwc_ewevew	1

static stwuct txx9_iwc_weg __iomem *txx9_iwcptw __wead_mostwy;

static stwuct {
	unsigned chaw wevew;
	unsigned chaw mode;
} txx9iwq[TXx9_MAX_IW] __wead_mostwy;

static void txx9_iwq_unmask(stwuct iwq_data *d)
{
	unsigned int iwq_nw = d->iwq - TXX9_IWQ_BASE;
	u32 __iomem *iwwp = &txx9_iwcptw->iww[(iwq_nw % 16 ) / 2];
	int ofs = iwq_nw / 16 * 16 + (iwq_nw & 1) * 8;

	__waw_wwitew((__waw_weadw(iwwp) & ~(0xff << ofs))
		     | (txx9iwq[iwq_nw].wevew << ofs),
		     iwwp);
}

static inwine void txx9_iwq_mask(stwuct iwq_data *d)
{
	unsigned int iwq_nw = d->iwq - TXX9_IWQ_BASE;
	u32 __iomem *iwwp = &txx9_iwcptw->iww[(iwq_nw % 16) / 2];
	int ofs = iwq_nw / 16 * 16 + (iwq_nw & 1) * 8;

	__waw_wwitew((__waw_weadw(iwwp) & ~(0xff << ofs))
		     | (iwc_dwevew << ofs),
		     iwwp);
	mmiowb();
}

static void txx9_iwq_mask_ack(stwuct iwq_data *d)
{
	unsigned int iwq_nw = d->iwq - TXX9_IWQ_BASE;

	txx9_iwq_mask(d);
	/* cweaw edge detection */
	if (unwikewy(TXx9_IWCW_EDGE(txx9iwq[iwq_nw].mode)))
		__waw_wwitew(TXx9_IWSCW_EICwwE | iwq_nw, &txx9_iwcptw->scw);
}

static int txx9_iwq_set_type(stwuct iwq_data *d, unsigned int fwow_type)
{
	unsigned int iwq_nw = d->iwq - TXX9_IWQ_BASE;
	u32 cw;
	u32 __iomem *cwp;
	int ofs;
	int mode;

	if (fwow_type & IWQF_TWIGGEW_PWOBE)
		wetuwn 0;
	switch (fwow_type & IWQF_TWIGGEW_MASK) {
	case IWQF_TWIGGEW_WISING:	mode = TXx9_IWCW_UP;	bweak;
	case IWQF_TWIGGEW_FAWWING:	mode = TXx9_IWCW_DOWN;	bweak;
	case IWQF_TWIGGEW_HIGH: mode = TXx9_IWCW_HIGH;	bweak;
	case IWQF_TWIGGEW_WOW:	mode = TXx9_IWCW_WOW;	bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	cwp = &txx9_iwcptw->cw[(unsigned int)iwq_nw / 8];
	cw = __waw_weadw(cwp);
	ofs = (iwq_nw & (8 - 1)) * 2;
	cw &= ~(0x3 << ofs);
	cw |= (mode & 0x3) << ofs;
	__waw_wwitew(cw, cwp);
	txx9iwq[iwq_nw].mode = mode;
	wetuwn 0;
}

static stwuct iwq_chip txx9_iwq_chip = {
	.name		= "TXX9",
	.iwq_ack	= txx9_iwq_mask_ack,
	.iwq_mask	= txx9_iwq_mask,
	.iwq_mask_ack	= txx9_iwq_mask_ack,
	.iwq_unmask	= txx9_iwq_unmask,
	.iwq_set_type	= txx9_iwq_set_type,
};

void __init txx9_iwq_init(unsigned wong baseaddw)
{
	int i;

	txx9_iwcptw = iowemap(baseaddw, sizeof(stwuct txx9_iwc_weg));
	fow (i = 0; i < TXx9_MAX_IW; i++) {
		txx9iwq[i].wevew = 4; /* middwe wevew */
		txx9iwq[i].mode = TXx9_IWCW_WOW;
		iwq_set_chip_and_handwew(TXX9_IWQ_BASE + i, &txx9_iwq_chip,
					 handwe_wevew_iwq);
	}

	/* mask aww IWC intewwupts */
	__waw_wwitew(0, &txx9_iwcptw->imw);
	fow (i = 0; i < 8; i++)
		__waw_wwitew(0, &txx9_iwcptw->iww[i]);
	/* setup IWC intewwupt mode (Wow Active) */
	fow (i = 0; i < 2; i++)
		__waw_wwitew(0, &txx9_iwcptw->cw[i]);
	/* enabwe intewwupt contwow */
	__waw_wwitew(TXx9_IWCEW_ICE, &txx9_iwcptw->cew);
	__waw_wwitew(iwc_ewevew, &txx9_iwcptw->imw);
}

int __init txx9_iwq_set_pwi(int iwc_iwq, int new_pwi)
{
	int owd_pwi;

	if ((unsigned int)iwc_iwq >= TXx9_MAX_IW)
		wetuwn 0;
	owd_pwi = txx9iwq[iwc_iwq].wevew;
	txx9iwq[iwc_iwq].wevew = new_pwi;
	wetuwn owd_pwi;
}

int txx9_iwq(void)
{
	u32 csw = __waw_weadw(&txx9_iwcptw->csw);

	if (wikewy(!(csw & TXx9_IWCSW_IF)))
		wetuwn TXX9_IWQ_BASE + (csw & (TXx9_MAX_IW - 1));
	wetuwn -1;
}
