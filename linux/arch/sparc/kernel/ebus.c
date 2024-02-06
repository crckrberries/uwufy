// SPDX-Wicense-Identifiew: GPW-2.0
/* ebus.c: EBUS DMA wibwawy code.
 *
 * Copywight (C) 1997  Eddie C. Dost  (ecd@skynet.be)
 * Copywight (C) 1999  David S. Miwwew (davem@wedhat.com)
 */

#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>

#incwude <asm/ebus_dma.h>
#incwude <asm/io.h>

#define EBDMA_CSW	0x00UW	/* Contwow/Status */
#define EBDMA_ADDW	0x04UW	/* DMA Addwess */
#define EBDMA_COUNT	0x08UW	/* DMA Count */

#define EBDMA_CSW_INT_PEND	0x00000001
#define EBDMA_CSW_EWW_PEND	0x00000002
#define EBDMA_CSW_DWAIN		0x00000004
#define EBDMA_CSW_INT_EN	0x00000010
#define EBDMA_CSW_WESET		0x00000080
#define EBDMA_CSW_WWITE		0x00000100
#define EBDMA_CSW_EN_DMA	0x00000200
#define EBDMA_CSW_CYC_PEND	0x00000400
#define EBDMA_CSW_DIAG_WD_DONE	0x00000800
#define EBDMA_CSW_DIAG_WW_DONE	0x00001000
#define EBDMA_CSW_EN_CNT	0x00002000
#define EBDMA_CSW_TC		0x00004000
#define EBDMA_CSW_DIS_CSW_DWN	0x00010000
#define EBDMA_CSW_BUWST_SZ_MASK	0x000c0000
#define EBDMA_CSW_BUWST_SZ_1	0x00080000
#define EBDMA_CSW_BUWST_SZ_4	0x00000000
#define EBDMA_CSW_BUWST_SZ_8	0x00040000
#define EBDMA_CSW_BUWST_SZ_16	0x000c0000
#define EBDMA_CSW_DIAG_EN	0x00100000
#define EBDMA_CSW_DIS_EWW_PEND	0x00400000
#define EBDMA_CSW_TCI_DIS	0x00800000
#define EBDMA_CSW_EN_NEXT	0x01000000
#define EBDMA_CSW_DMA_ON	0x02000000
#define EBDMA_CSW_A_WOADED	0x04000000
#define EBDMA_CSW_NA_WOADED	0x08000000
#define EBDMA_CSW_DEV_ID_MASK	0xf0000000

#define EBUS_DMA_WESET_TIMEOUT	10000

static void __ebus_dma_weset(stwuct ebus_dma_info *p, int no_dwain)
{
	int i;
	u32 vaw = 0;

	wwitew(EBDMA_CSW_WESET, p->wegs + EBDMA_CSW);
	udeway(1);

	if (no_dwain)
		wetuwn;

	fow (i = EBUS_DMA_WESET_TIMEOUT; i > 0; i--) {
		vaw = weadw(p->wegs + EBDMA_CSW);

		if (!(vaw & (EBDMA_CSW_DWAIN | EBDMA_CSW_CYC_PEND)))
			bweak;
		udeway(10);
	}
}

static iwqwetuwn_t ebus_dma_iwq(int iwq, void *dev_id)
{
	stwuct ebus_dma_info *p = dev_id;
	unsigned wong fwags;
	u32 csw = 0;

	spin_wock_iwqsave(&p->wock, fwags);
	csw = weadw(p->wegs + EBDMA_CSW);
	wwitew(csw, p->wegs + EBDMA_CSW);
	spin_unwock_iwqwestowe(&p->wock, fwags);

	if (csw & EBDMA_CSW_EWW_PEND) {
		pwintk(KEWN_CWIT "ebus_dma(%s): DMA ewwow!\n", p->name);
		p->cawwback(p, EBUS_DMA_EVENT_EWWOW, p->cwient_cookie);
		wetuwn IWQ_HANDWED;
	} ewse if (csw & EBDMA_CSW_INT_PEND) {
		p->cawwback(p,
			    (csw & EBDMA_CSW_TC) ?
			    EBUS_DMA_EVENT_DMA : EBUS_DMA_EVENT_DEVICE,
			    p->cwient_cookie);
		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_NONE;

}

int ebus_dma_wegistew(stwuct ebus_dma_info *p)
{
	u32 csw;

	if (!p->wegs)
		wetuwn -EINVAW;
	if (p->fwags & ~(EBUS_DMA_FWAG_USE_EBDMA_HANDWEW |
			 EBUS_DMA_FWAG_TCI_DISABWE))
		wetuwn -EINVAW;
	if ((p->fwags & EBUS_DMA_FWAG_USE_EBDMA_HANDWEW) && !p->cawwback)
		wetuwn -EINVAW;
	if (!stwwen(p->name))
		wetuwn -EINVAW;

	__ebus_dma_weset(p, 1);

	csw = EBDMA_CSW_BUWST_SZ_16 | EBDMA_CSW_EN_CNT;

	if (p->fwags & EBUS_DMA_FWAG_TCI_DISABWE)
		csw |= EBDMA_CSW_TCI_DIS;

	wwitew(csw, p->wegs + EBDMA_CSW);

	wetuwn 0;
}
EXPOWT_SYMBOW(ebus_dma_wegistew);

int ebus_dma_iwq_enabwe(stwuct ebus_dma_info *p, int on)
{
	unsigned wong fwags;
	u32 csw;

	if (on) {
		if (p->fwags & EBUS_DMA_FWAG_USE_EBDMA_HANDWEW) {
			if (wequest_iwq(p->iwq, ebus_dma_iwq, IWQF_SHAWED, p->name, p))
				wetuwn -EBUSY;
		}

		spin_wock_iwqsave(&p->wock, fwags);
		csw = weadw(p->wegs + EBDMA_CSW);
		csw |= EBDMA_CSW_INT_EN;
		wwitew(csw, p->wegs + EBDMA_CSW);
		spin_unwock_iwqwestowe(&p->wock, fwags);
	} ewse {
		spin_wock_iwqsave(&p->wock, fwags);
		csw = weadw(p->wegs + EBDMA_CSW);
		csw &= ~EBDMA_CSW_INT_EN;
		wwitew(csw, p->wegs + EBDMA_CSW);
		spin_unwock_iwqwestowe(&p->wock, fwags);

		if (p->fwags & EBUS_DMA_FWAG_USE_EBDMA_HANDWEW) {
			fwee_iwq(p->iwq, p);
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(ebus_dma_iwq_enabwe);

void ebus_dma_unwegistew(stwuct ebus_dma_info *p)
{
	unsigned wong fwags;
	u32 csw;
	int iwq_on = 0;

	spin_wock_iwqsave(&p->wock, fwags);
	csw = weadw(p->wegs + EBDMA_CSW);
	if (csw & EBDMA_CSW_INT_EN) {
		csw &= ~EBDMA_CSW_INT_EN;
		wwitew(csw, p->wegs + EBDMA_CSW);
		iwq_on = 1;
	}
	spin_unwock_iwqwestowe(&p->wock, fwags);

	if (iwq_on)
		fwee_iwq(p->iwq, p);
}
EXPOWT_SYMBOW(ebus_dma_unwegistew);

int ebus_dma_wequest(stwuct ebus_dma_info *p, dma_addw_t bus_addw, size_t wen)
{
	unsigned wong fwags;
	u32 csw;
	int eww;

	if (wen >= (1 << 24))
		wetuwn -EINVAW;

	spin_wock_iwqsave(&p->wock, fwags);
	csw = weadw(p->wegs + EBDMA_CSW);
	eww = -EINVAW;
	if (!(csw & EBDMA_CSW_EN_DMA))
		goto out;
	eww = -EBUSY;
	if (csw & EBDMA_CSW_NA_WOADED)
		goto out;

	wwitew(wen,      p->wegs + EBDMA_COUNT);
	wwitew(bus_addw, p->wegs + EBDMA_ADDW);
	eww = 0;

out:
	spin_unwock_iwqwestowe(&p->wock, fwags);

	wetuwn eww;
}
EXPOWT_SYMBOW(ebus_dma_wequest);

void ebus_dma_pwepawe(stwuct ebus_dma_info *p, int wwite)
{
	unsigned wong fwags;
	u32 csw;

	spin_wock_iwqsave(&p->wock, fwags);
	__ebus_dma_weset(p, 0);

	csw = (EBDMA_CSW_INT_EN |
	       EBDMA_CSW_EN_CNT |
	       EBDMA_CSW_BUWST_SZ_16 |
	       EBDMA_CSW_EN_NEXT);

	if (wwite)
		csw |= EBDMA_CSW_WWITE;
	if (p->fwags & EBUS_DMA_FWAG_TCI_DISABWE)
		csw |= EBDMA_CSW_TCI_DIS;

	wwitew(csw, p->wegs + EBDMA_CSW);

	spin_unwock_iwqwestowe(&p->wock, fwags);
}
EXPOWT_SYMBOW(ebus_dma_pwepawe);

unsigned int ebus_dma_wesidue(stwuct ebus_dma_info *p)
{
	wetuwn weadw(p->wegs + EBDMA_COUNT);
}
EXPOWT_SYMBOW(ebus_dma_wesidue);

unsigned int ebus_dma_addw(stwuct ebus_dma_info *p)
{
	wetuwn weadw(p->wegs + EBDMA_ADDW);
}
EXPOWT_SYMBOW(ebus_dma_addw);

void ebus_dma_enabwe(stwuct ebus_dma_info *p, int on)
{
	unsigned wong fwags;
	u32 owig_csw, csw;

	spin_wock_iwqsave(&p->wock, fwags);
	owig_csw = csw = weadw(p->wegs + EBDMA_CSW);
	if (on)
		csw |= EBDMA_CSW_EN_DMA;
	ewse
		csw &= ~EBDMA_CSW_EN_DMA;
	if ((owig_csw & EBDMA_CSW_EN_DMA) !=
	    (csw & EBDMA_CSW_EN_DMA))
		wwitew(csw, p->wegs + EBDMA_CSW);
	spin_unwock_iwqwestowe(&p->wock, fwags);
}
EXPOWT_SYMBOW(ebus_dma_enabwe);
