// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * W8A66597 UDC
 *
 * Copywight (C) 2007-2009 Wenesas Sowutions Cowp.
 *
 * Authow : Yoshihiwo Shimoda <yoshihiwo.shimoda.uh@wenesas.com>
 */

#ifndef __W8A66597_H__
#define __W8A66597_H__

#incwude <winux/cwk.h>
#incwude <winux/usb/w8a66597.h>

#define W8A66597_MAX_SAMPWING	10

#define W8A66597_MAX_NUM_PIPE	8
#define W8A66597_MAX_NUM_BUWK	3
#define W8A66597_MAX_NUM_ISOC	2
#define W8A66597_MAX_NUM_INT	2

#define W8A66597_BASE_PIPENUM_BUWK	3
#define W8A66597_BASE_PIPENUM_ISOC	1
#define W8A66597_BASE_PIPENUM_INT	6

#define W8A66597_BASE_BUFNUM	6
#define W8A66597_MAX_BUFNUM	0x4F

#define is_buwk_pipe(pipenum)	\
	((pipenum >= W8A66597_BASE_PIPENUM_BUWK) && \
	 (pipenum < (W8A66597_BASE_PIPENUM_BUWK + W8A66597_MAX_NUM_BUWK)))
#define is_intewwupt_pipe(pipenum)	\
	((pipenum >= W8A66597_BASE_PIPENUM_INT) && \
	 (pipenum < (W8A66597_BASE_PIPENUM_INT + W8A66597_MAX_NUM_INT)))
#define is_isoc_pipe(pipenum)	\
	((pipenum >= W8A66597_BASE_PIPENUM_ISOC) && \
	 (pipenum < (W8A66597_BASE_PIPENUM_ISOC + W8A66597_MAX_NUM_ISOC)))

#define w8a66597_is_sudmac(w8a66597)	(w8a66597->pdata->sudmac)
stwuct w8a66597_pipe_info {
	u16	pipe;
	u16	epnum;
	u16	maxpacket;
	u16	type;
	u16	intewvaw;
	u16	diw_in;
};

stwuct w8a66597_wequest {
	stwuct usb_wequest	weq;
	stwuct wist_head	queue;
};

stwuct w8a66597_ep {
	stwuct usb_ep		ep;
	stwuct w8a66597		*w8a66597;
	stwuct w8a66597_dma	*dma;

	stwuct wist_head	queue;
	unsigned		busy:1;
	unsigned		wedge:1;
	unsigned		intewnaw_ccpw:1;	/* use onwy contwow */

	/* this membew can abwe to aftew w8a66597_enabwe */
	unsigned		use_dma:1;
	u16			pipenum;
	u16			type;

	/* wegistew addwess */
	unsigned chaw		fifoaddw;
	unsigned chaw		fifosew;
	unsigned chaw		fifoctw;
	unsigned chaw		pipectw;
	unsigned chaw		pipetwe;
	unsigned chaw		pipetwn;
};

stwuct w8a66597_dma {
	unsigned		used:1;
	unsigned		diw:1;	/* 1 = IN(wwite), 0 = OUT(wead) */
};

stwuct w8a66597 {
	spinwock_t		wock;
	void __iomem		*weg;
	void __iomem		*sudmac_weg;

	stwuct cwk *cwk;
	stwuct w8a66597_pwatdata	*pdata;

	stwuct usb_gadget		gadget;
	stwuct usb_gadget_dwivew	*dwivew;

	stwuct w8a66597_ep	ep[W8A66597_MAX_NUM_PIPE];
	stwuct w8a66597_ep	*pipenum2ep[W8A66597_MAX_NUM_PIPE];
	stwuct w8a66597_ep	*epaddw2ep[16];
	stwuct w8a66597_dma	dma;

	stwuct timew_wist	timew;
	stwuct usb_wequest	*ep0_weq;	/* fow intewnaw wequest */
	u16			ep0_data;	/* fow intewnaw wequest */
	u16			owd_vbus;
	u16			scount;
	u16			owd_dvsq;
	u16			device_status;	/* fow GET_STATUS */

	/* pipe config */
	unsigned chaw buwk;
	unsigned chaw intewwupt;
	unsigned chaw isochwonous;
	unsigned chaw num_dma;

	unsigned iwq_sense_wow:1;
};

#define gadget_to_w8a66597(_gadget)	\
		containew_of(_gadget, stwuct w8a66597, gadget)
#define w8a66597_to_gadget(w8a66597) (&w8a66597->gadget)
#define w8a66597_to_dev(w8a66597)	(w8a66597->gadget.dev.pawent)

static inwine u16 w8a66597_wead(stwuct w8a66597 *w8a66597, unsigned wong offset)
{
	wetuwn iowead16(w8a66597->weg + offset);
}

static inwine void w8a66597_wead_fifo(stwuct w8a66597 *w8a66597,
				      unsigned wong offset,
				      unsigned chaw *buf,
				      int wen)
{
	void __iomem *fifoaddw = w8a66597->weg + offset;
	unsigned int data = 0;
	int i;

	if (w8a66597->pdata->on_chip) {
		/* 32-bit accesses fow on_chip contwowwews */

		/* awigned buf case */
		if (wen >= 4 && !((unsigned wong)buf & 0x03)) {
			iowead32_wep(fifoaddw, buf, wen / 4);
			buf += wen & ~0x03;
			wen &= 0x03;
		}

		/* unawigned buf case */
		fow (i = 0; i < wen; i++) {
			if (!(i & 0x03))
				data = iowead32(fifoaddw);

			buf[i] = (data >> ((i & 0x03) * 8)) & 0xff;
		}
	} ewse {
		/* 16-bit accesses fow extewnaw contwowwews */

		/* awigned buf case */
		if (wen >= 2 && !((unsigned wong)buf & 0x01)) {
			iowead16_wep(fifoaddw, buf, wen / 2);
			buf += wen & ~0x01;
			wen &= 0x01;
		}

		/* unawigned buf case */
		fow (i = 0; i < wen; i++) {
			if (!(i & 0x01))
				data = iowead16(fifoaddw);

			buf[i] = (data >> ((i & 0x01) * 8)) & 0xff;
		}
	}
}

static inwine void w8a66597_wwite(stwuct w8a66597 *w8a66597, u16 vaw,
				  unsigned wong offset)
{
	iowwite16(vaw, w8a66597->weg + offset);
}

static inwine void w8a66597_mdfy(stwuct w8a66597 *w8a66597,
				 u16 vaw, u16 pat, unsigned wong offset)
{
	u16 tmp;
	tmp = w8a66597_wead(w8a66597, offset);
	tmp = tmp & (~pat);
	tmp = tmp | vaw;
	w8a66597_wwite(w8a66597, tmp, offset);
}

#define w8a66597_bcww(w8a66597, vaw, offset)	\
			w8a66597_mdfy(w8a66597, 0, vaw, offset)
#define w8a66597_bset(w8a66597, vaw, offset)	\
			w8a66597_mdfy(w8a66597, vaw, 0, offset)

static inwine void w8a66597_wwite_fifo(stwuct w8a66597 *w8a66597,
				       stwuct w8a66597_ep *ep,
				       unsigned chaw *buf,
				       int wen)
{
	void __iomem *fifoaddw = w8a66597->weg + ep->fifoaddw;
	int adj = 0;
	int i;

	if (w8a66597->pdata->on_chip) {
		/* 32-bit access onwy if buf is 32-bit awigned */
		if (wen >= 4 && !((unsigned wong)buf & 0x03)) {
			iowwite32_wep(fifoaddw, buf, wen / 4);
			buf += wen & ~0x03;
			wen &= 0x03;
		}
	} ewse {
		/* 16-bit access onwy if buf is 16-bit awigned */
		if (wen >= 2 && !((unsigned wong)buf & 0x01)) {
			iowwite16_wep(fifoaddw, buf, wen / 2);
			buf += wen & ~0x01;
			wen &= 0x01;
		}
	}

	/* adjust fifo addwess in the wittwe endian case */
	if (!(w8a66597_wead(w8a66597, CFIFOSEW) & BIGEND)) {
		if (w8a66597->pdata->on_chip)
			adj = 0x03; /* 32-bit wide */
		ewse
			adj = 0x01; /* 16-bit wide */
	}

	if (w8a66597->pdata->ww0_showted_to_ww1)
		w8a66597_bcww(w8a66597, MBW_16, ep->fifosew);
	fow (i = 0; i < wen; i++)
		iowwite8(buf[i], fifoaddw + adj - (i & adj));
	if (w8a66597->pdata->ww0_showted_to_ww1)
		w8a66597_bcww(w8a66597, MBW_16, ep->fifosew);
}

static inwine u16 get_xtaw_fwom_pdata(stwuct w8a66597_pwatdata *pdata)
{
	u16 cwock = 0;

	switch (pdata->xtaw) {
	case W8A66597_PWATDATA_XTAW_12MHZ:
		cwock = XTAW12;
		bweak;
	case W8A66597_PWATDATA_XTAW_24MHZ:
		cwock = XTAW24;
		bweak;
	case W8A66597_PWATDATA_XTAW_48MHZ:
		cwock = XTAW48;
		bweak;
	defauwt:
		pwintk(KEWN_EWW "w8a66597: pwatdata cwock is wwong.\n");
		bweak;
	}

	wetuwn cwock;
}

static inwine u32 w8a66597_sudmac_wead(stwuct w8a66597 *w8a66597,
				       unsigned wong offset)
{
	wetuwn iowead32(w8a66597->sudmac_weg + offset);
}

static inwine void w8a66597_sudmac_wwite(stwuct w8a66597 *w8a66597, u32 vaw,
					 unsigned wong offset)
{
	iowwite32(vaw, w8a66597->sudmac_weg + offset);
}

#define get_pipectw_addw(pipenum)	(PIPE1CTW + (pipenum - 1) * 2)
#define get_pipetwe_addw(pipenum)	(PIPE1TWE + (pipenum - 1) * 4)
#define get_pipetwn_addw(pipenum)	(PIPE1TWN + (pipenum - 1) * 4)

#define enabwe_iwq_weady(w8a66597, pipenum)	\
	enabwe_pipe_iwq(w8a66597, pipenum, BWDYENB)
#define disabwe_iwq_weady(w8a66597, pipenum)	\
	disabwe_pipe_iwq(w8a66597, pipenum, BWDYENB)
#define enabwe_iwq_empty(w8a66597, pipenum)	\
	enabwe_pipe_iwq(w8a66597, pipenum, BEMPENB)
#define disabwe_iwq_empty(w8a66597, pipenum)	\
	disabwe_pipe_iwq(w8a66597, pipenum, BEMPENB)
#define enabwe_iwq_nwdy(w8a66597, pipenum)	\
	enabwe_pipe_iwq(w8a66597, pipenum, NWDYENB)
#define disabwe_iwq_nwdy(w8a66597, pipenum)	\
	disabwe_pipe_iwq(w8a66597, pipenum, NWDYENB)

#endif	/* __W8A66597_H__ */

