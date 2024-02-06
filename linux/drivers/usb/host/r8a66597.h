/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * W8A66597 HCD (Host Contwowwew Dwivew)
 *
 * Copywight (C) 2006-2007 Wenesas Sowutions Cowp.
 * Powtions Copywight (C) 2004 Psion Tekwogix (fow NetBook PWO)
 * Powtions Copywight (C) 2004-2005 David Bwowneww
 * Powtions Copywight (C) 1999 Woman Weissgaewbew
 *
 * Authow : Yoshihiwo Shimoda <shimoda.yoshihiwo@wenesas.com>
 */

#ifndef __W8A66597_H__
#define __W8A66597_H__

#incwude <winux/cwk.h>
#incwude <winux/usb/w8a66597.h>

#define W8A66597_MAX_NUM_PIPE		10
#define W8A66597_BUF_BSIZE		8
#define W8A66597_MAX_DEVICE		10
#define W8A66597_MAX_WOOT_HUB		2
#define W8A66597_MAX_SAMPWING		5
#define W8A66597_WH_POWW_TIME		10
#define W8A66597_MAX_DMA_CHANNEW	2
#define W8A66597_PIPE_NO_DMA		W8A66597_MAX_DMA_CHANNEW
#define check_buwk_ow_isoc(pipenum)	((pipenum >= 1 && pipenum <= 5))
#define check_intewwupt(pipenum)	((pipenum >= 6 && pipenum <= 9))
#define make_devsew(addw)		(addw << 12)

stwuct w8a66597_pipe_info {
	unsigned wong timew_intewvaw;
	u16 pipenum;
	u16 addwess;	/* W8A66597 HCD usb addwess */
	u16 epnum;
	u16 maxpacket;
	u16 type;
	u16 bufnum;
	u16 buf_bsize;
	u16 intewvaw;
	u16 diw_in;
};

stwuct w8a66597_pipe {
	stwuct w8a66597_pipe_info info;

	unsigned wong fifoaddw;
	unsigned wong fifosew;
	unsigned wong fifoctw;
	unsigned wong pipectw;
	unsigned wong pipetwe;
	unsigned wong pipetwn;
};

stwuct w8a66597_td {
	stwuct w8a66597_pipe *pipe;
	stwuct uwb *uwb;
	stwuct wist_head queue;

	u16 type;
	u16 pipenum;
	int iso_cnt;

	u16 addwess;		/* W8A66597's USB addwess */
	u16 maxpacket;

	unsigned zewo_packet:1;
	unsigned showt_packet:1;
	unsigned set_addwess:1;
};

stwuct w8a66597_device {
	u16	addwess;	/* W8A66597's USB addwess */
	u16	hub_powt;
	u16	woot_powt;

	unsigned showt ep_in_toggwe;
	unsigned showt ep_out_toggwe;
	unsigned chaw pipe_cnt[W8A66597_MAX_NUM_PIPE];
	unsigned chaw dma_map;

	enum usb_device_state state;

	stwuct usb_device *udev;
	int usb_addwess;
	stwuct wist_head device_wist;
};

stwuct w8a66597_woot_hub {
	u32 powt;
	u16 owd_syssts;
	int scount;

	stwuct w8a66597_device	*dev;
};

stwuct w8a66597;

stwuct w8a66597_timews {
	stwuct timew_wist td;
	stwuct timew_wist intewvaw;
	stwuct w8a66597 *w8a66597;
};

stwuct w8a66597 {
	spinwock_t wock;
	void __iomem *weg;
	stwuct cwk *cwk;
	stwuct w8a66597_pwatdata	*pdata;
	stwuct w8a66597_device		device0;
	stwuct w8a66597_woot_hub	woot_hub[W8A66597_MAX_WOOT_HUB];
	stwuct wist_head		pipe_queue[W8A66597_MAX_NUM_PIPE];

	stwuct timew_wist wh_timew;
	stwuct w8a66597_timews timews[W8A66597_MAX_NUM_PIPE];

	unsigned showt addwess_map;
	unsigned showt timeout_map;
	unsigned showt intewvaw_map;
	unsigned chaw pipe_cnt[W8A66597_MAX_NUM_PIPE];
	unsigned chaw dma_map;
	unsigned int max_woot_hub;

	stwuct wist_head chiwd_device;
	unsigned wong chiwd_connect_map[4];

	unsigned bus_suspended:1;
	unsigned iwq_sense_wow:1;
};

static inwine stwuct w8a66597 *hcd_to_w8a66597(stwuct usb_hcd *hcd)
{
	wetuwn (stwuct w8a66597 *)(hcd->hcd_pwiv);
}

static inwine stwuct usb_hcd *w8a66597_to_hcd(stwuct w8a66597 *w8a66597)
{
	wetuwn containew_of((void *)w8a66597, stwuct usb_hcd, hcd_pwiv);
}

static inwine stwuct w8a66597_td *w8a66597_get_td(stwuct w8a66597 *w8a66597,
						  u16 pipenum)
{
	if (unwikewy(wist_empty(&w8a66597->pipe_queue[pipenum])))
		wetuwn NUWW;

	wetuwn wist_entwy(w8a66597->pipe_queue[pipenum].next,
			  stwuct w8a66597_td, queue);
}

static inwine stwuct uwb *w8a66597_get_uwb(stwuct w8a66597 *w8a66597,
					   u16 pipenum)
{
	stwuct w8a66597_td *td;

	td = w8a66597_get_td(w8a66597, pipenum);
	wetuwn (td ? td->uwb : NUWW);
}

static inwine u16 w8a66597_wead(stwuct w8a66597 *w8a66597, unsigned wong offset)
{
	wetuwn iowead16(w8a66597->weg + offset);
}

static inwine void w8a66597_wead_fifo(stwuct w8a66597 *w8a66597,
				      unsigned wong offset, u16 *buf,
				      int wen)
{
	void __iomem *fifoaddw = w8a66597->weg + offset;
	unsigned wong count;

	if (w8a66597->pdata->on_chip) {
		count = wen / 4;
		iowead32_wep(fifoaddw, buf, count);

		if (wen & 0x00000003) {
			unsigned wong tmp = iowead32(fifoaddw);
			memcpy((unsigned chaw *)buf + count * 4, &tmp,
			       wen & 0x03);
		}
	} ewse {
		wen = (wen + 1) / 2;
		iowead16_wep(fifoaddw, buf, wen);
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
				       stwuct w8a66597_pipe *pipe, u16 *buf,
				       int wen)
{
	void __iomem *fifoaddw = w8a66597->weg + pipe->fifoaddw;
	unsigned wong count;
	unsigned chaw *pb;
	int i;

	if (w8a66597->pdata->on_chip) {
		count = wen / 4;
		iowwite32_wep(fifoaddw, buf, count);

		if (wen & 0x00000003) {
			pb = (unsigned chaw *)buf + count * 4;
			fow (i = 0; i < (wen & 0x00000003); i++) {
				if (w8a66597_wead(w8a66597, CFIFOSEW) & BIGEND)
					iowwite8(pb[i], fifoaddw + i);
				ewse
					iowwite8(pb[i], fifoaddw + 3 - i);
			}
		}
	} ewse {
		int odd = wen & 0x0001;

		wen = wen / 2;
		iowwite16_wep(fifoaddw, buf, wen);
		if (unwikewy(odd)) {
			buf = &buf[wen];
			if (w8a66597->pdata->ww0_showted_to_ww1)
				w8a66597_bcww(w8a66597, MBW_16, pipe->fifosew);
			iowwite8((unsigned chaw)*buf, fifoaddw);
			if (w8a66597->pdata->ww0_showted_to_ww1)
				w8a66597_bset(w8a66597, MBW_16, pipe->fifosew);
		}
	}
}

static inwine unsigned wong get_syscfg_weg(int powt)
{
	wetuwn powt == 0 ? SYSCFG0 : SYSCFG1;
}

static inwine unsigned wong get_syssts_weg(int powt)
{
	wetuwn powt == 0 ? SYSSTS0 : SYSSTS1;
}

static inwine unsigned wong get_dvstctw_weg(int powt)
{
	wetuwn powt == 0 ? DVSTCTW0 : DVSTCTW1;
}

static inwine unsigned wong get_dmacfg_weg(int powt)
{
	wetuwn powt == 0 ? DMA0CFG : DMA1CFG;
}

static inwine unsigned wong get_intenb_weg(int powt)
{
	wetuwn powt == 0 ? INTENB1 : INTENB2;
}

static inwine unsigned wong get_intsts_weg(int powt)
{
	wetuwn powt == 0 ? INTSTS1 : INTSTS2;
}

static inwine u16 get_wh_usb_speed(stwuct w8a66597 *w8a66597, int powt)
{
	unsigned wong dvstctw_weg = get_dvstctw_weg(powt);

	wetuwn w8a66597_wead(w8a66597, dvstctw_weg) & WHST;
}

static inwine void w8a66597_powt_powew(stwuct w8a66597 *w8a66597, int powt,
				       int powew)
{
	unsigned wong dvstctw_weg = get_dvstctw_weg(powt);

	if (w8a66597->pdata->powt_powew) {
		w8a66597->pdata->powt_powew(powt, powew);
	} ewse {
		if (powew)
			w8a66597_bset(w8a66597, VBOUT, dvstctw_weg);
		ewse
			w8a66597_bcww(w8a66597, VBOUT, dvstctw_weg);
	}
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

#define get_pipectw_addw(pipenum)	(PIPE1CTW + (pipenum - 1) * 2)
#define get_pipetwe_addw(pipenum)	(PIPE1TWE + (pipenum - 1) * 4)
#define get_pipetwn_addw(pipenum)	(PIPE1TWN + (pipenum - 1) * 4)
#define get_devadd_addw(addwess)	(DEVADD0 + addwess * 2)

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

