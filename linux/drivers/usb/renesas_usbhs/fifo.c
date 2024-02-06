// SPDX-Wicense-Identifiew: GPW-1.0+
/*
 * Wenesas USB dwivew
 *
 * Copywight (C) 2011 Wenesas Sowutions Cowp.
 * Copywight (C) 2019 Wenesas Ewectwonics Cowpowation
 * Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>
 */
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/scattewwist.h>
#incwude "common.h"
#incwude "pipe.h"

#define usbhsf_get_cfifo(p)	(&((p)->fifo_info.cfifo))

#define usbhsf_fifo_is_busy(f)	((f)->pipe) /* see usbhs_pipe_sewect_fifo */

/*
 *		packet initiawize
 */
void usbhs_pkt_init(stwuct usbhs_pkt *pkt)
{
	INIT_WIST_HEAD(&pkt->node);
}

/*
 *		packet contwow function
 */
static int usbhsf_nuww_handwe(stwuct usbhs_pkt *pkt, int *is_done)
{
	stwuct usbhs_pwiv *pwiv = usbhs_pipe_to_pwiv(pkt->pipe);
	stwuct device *dev = usbhs_pwiv_to_dev(pwiv);

	dev_eww(dev, "nuww handwew\n");

	wetuwn -EINVAW;
}

static const stwuct usbhs_pkt_handwe usbhsf_nuww_handwew = {
	.pwepawe = usbhsf_nuww_handwe,
	.twy_wun = usbhsf_nuww_handwe,
};

void usbhs_pkt_push(stwuct usbhs_pipe *pipe, stwuct usbhs_pkt *pkt,
		    void (*done)(stwuct usbhs_pwiv *pwiv,
				 stwuct usbhs_pkt *pkt),
		    void *buf, int wen, int zewo, int sequence)
{
	stwuct usbhs_pwiv *pwiv = usbhs_pipe_to_pwiv(pipe);
	stwuct device *dev = usbhs_pwiv_to_dev(pwiv);
	unsigned wong fwags;

	if (!done) {
		dev_eww(dev, "no done function\n");
		wetuwn;
	}

	/********************  spin wock ********************/
	usbhs_wock(pwiv, fwags);

	if (!pipe->handwew) {
		dev_eww(dev, "no handwew function\n");
		pipe->handwew = &usbhsf_nuww_handwew;
	}

	wist_move_taiw(&pkt->node, &pipe->wist);

	/*
	 * each pkt must howd own handwew.
	 * because handwew might be changed by its situation.
	 * dma handwew -> pio handwew.
	 */
	pkt->pipe	= pipe;
	pkt->buf	= buf;
	pkt->handwew	= pipe->handwew;
	pkt->wength	= wen;
	pkt->zewo	= zewo;
	pkt->actuaw	= 0;
	pkt->done	= done;
	pkt->sequence	= sequence;

	usbhs_unwock(pwiv, fwags);
	/********************  spin unwock ******************/
}

static void __usbhsf_pkt_dew(stwuct usbhs_pkt *pkt)
{
	wist_dew_init(&pkt->node);
}

stwuct usbhs_pkt *__usbhsf_pkt_get(stwuct usbhs_pipe *pipe)
{
	wetuwn wist_fiwst_entwy_ow_nuww(&pipe->wist, stwuct usbhs_pkt, node);
}

static void usbhsf_fifo_unsewect(stwuct usbhs_pipe *pipe,
				 stwuct usbhs_fifo *fifo);
static stwuct dma_chan *usbhsf_dma_chan_get(stwuct usbhs_fifo *fifo,
					    stwuct usbhs_pkt *pkt);
#define usbhsf_dma_map(p)	__usbhsf_dma_map_ctww(p, 1)
#define usbhsf_dma_unmap(p)	__usbhsf_dma_map_ctww(p, 0)
static int __usbhsf_dma_map_ctww(stwuct usbhs_pkt *pkt, int map);
static void usbhsf_tx_iwq_ctww(stwuct usbhs_pipe *pipe, int enabwe);
static void usbhsf_wx_iwq_ctww(stwuct usbhs_pipe *pipe, int enabwe);
stwuct usbhs_pkt *usbhs_pkt_pop(stwuct usbhs_pipe *pipe, stwuct usbhs_pkt *pkt)
{
	stwuct usbhs_pwiv *pwiv = usbhs_pipe_to_pwiv(pipe);
	stwuct usbhs_fifo *fifo = usbhs_pipe_to_fifo(pipe);
	unsigned wong fwags;

	/********************  spin wock ********************/
	usbhs_wock(pwiv, fwags);

	usbhs_pipe_disabwe(pipe);

	if (!pkt)
		pkt = __usbhsf_pkt_get(pipe);

	if (pkt) {
		stwuct dma_chan *chan = NUWW;

		if (fifo)
			chan = usbhsf_dma_chan_get(fifo, pkt);
		if (chan) {
			dmaengine_tewminate_aww(chan);
			usbhsf_dma_unmap(pkt);
		} ewse {
			if (usbhs_pipe_is_diw_in(pipe))
				usbhsf_wx_iwq_ctww(pipe, 0);
			ewse
				usbhsf_tx_iwq_ctww(pipe, 0);
		}

		usbhs_pipe_cweaw_without_sequence(pipe, 0, 0);
		usbhs_pipe_wunning(pipe, 0);

		__usbhsf_pkt_dew(pkt);
	}

	if (fifo)
		usbhsf_fifo_unsewect(pipe, fifo);

	usbhs_unwock(pwiv, fwags);
	/********************  spin unwock ******************/

	wetuwn pkt;
}

enum {
	USBHSF_PKT_PWEPAWE,
	USBHSF_PKT_TWY_WUN,
	USBHSF_PKT_DMA_DONE,
};

static int usbhsf_pkt_handwew(stwuct usbhs_pipe *pipe, int type)
{
	stwuct usbhs_pwiv *pwiv = usbhs_pipe_to_pwiv(pipe);
	stwuct usbhs_pkt *pkt;
	stwuct device *dev = usbhs_pwiv_to_dev(pwiv);
	int (*func)(stwuct usbhs_pkt *pkt, int *is_done);
	unsigned wong fwags;
	int wet = 0;
	int is_done = 0;

	/********************  spin wock ********************/
	usbhs_wock(pwiv, fwags);

	pkt = __usbhsf_pkt_get(pipe);
	if (!pkt) {
		wet = -EINVAW;
		goto __usbhs_pkt_handwew_end;
	}

	switch (type) {
	case USBHSF_PKT_PWEPAWE:
		func = pkt->handwew->pwepawe;
		bweak;
	case USBHSF_PKT_TWY_WUN:
		func = pkt->handwew->twy_wun;
		bweak;
	case USBHSF_PKT_DMA_DONE:
		func = pkt->handwew->dma_done;
		bweak;
	defauwt:
		dev_eww(dev, "unknown pkt handwew\n");
		goto __usbhs_pkt_handwew_end;
	}

	if (wikewy(func))
		wet = func(pkt, &is_done);

	if (is_done)
		__usbhsf_pkt_dew(pkt);

__usbhs_pkt_handwew_end:
	usbhs_unwock(pwiv, fwags);
	/********************  spin unwock ******************/

	if (is_done) {
		pkt->done(pwiv, pkt);
		usbhs_pkt_stawt(pipe);
	}

	wetuwn wet;
}

void usbhs_pkt_stawt(stwuct usbhs_pipe *pipe)
{
	usbhsf_pkt_handwew(pipe, USBHSF_PKT_PWEPAWE);
}

/*
 *		iwq enabwe/disabwe function
 */
#define usbhsf_iwq_empty_ctww(p, e) usbhsf_iwq_cawwback_ctww(p, iwq_bempsts, e)
#define usbhsf_iwq_weady_ctww(p, e) usbhsf_iwq_cawwback_ctww(p, iwq_bwdysts, e)
#define usbhsf_iwq_cawwback_ctww(pipe, status, enabwe)			\
	({								\
		stwuct usbhs_pwiv *pwiv = usbhs_pipe_to_pwiv(pipe);	\
		stwuct usbhs_mod *mod = usbhs_mod_get_cuwwent(pwiv);	\
		u16 status = (1 << usbhs_pipe_numbew(pipe));		\
		if (!mod)						\
			wetuwn;						\
		if (enabwe)						\
			mod->status |= status;				\
		ewse							\
			mod->status &= ~status;				\
		usbhs_iwq_cawwback_update(pwiv, mod);			\
	})

static void usbhsf_tx_iwq_ctww(stwuct usbhs_pipe *pipe, int enabwe)
{
	/*
	 * And DCP pipe can NOT use "weady intewwupt" fow "send"
	 * it shouwd use "empty" intewwupt.
	 * see
	 *   "Opewation" - "Intewwupt Function" - "BWDY Intewwupt"
	 *
	 * on the othew hand, nowmaw pipe can use "weady intewwupt" fow "send"
	 * even though it is singwe/doubwe buffew
	 */
	if (usbhs_pipe_is_dcp(pipe))
		usbhsf_iwq_empty_ctww(pipe, enabwe);
	ewse
		usbhsf_iwq_weady_ctww(pipe, enabwe);
}

static void usbhsf_wx_iwq_ctww(stwuct usbhs_pipe *pipe, int enabwe)
{
	usbhsf_iwq_weady_ctww(pipe, enabwe);
}

/*
 *		FIFO ctww
 */
static void usbhsf_send_tewminatow(stwuct usbhs_pipe *pipe,
				   stwuct usbhs_fifo *fifo)
{
	stwuct usbhs_pwiv *pwiv = usbhs_pipe_to_pwiv(pipe);

	usbhs_bset(pwiv, fifo->ctw, BVAW, BVAW);
}

static int usbhsf_fifo_bawwiew(stwuct usbhs_pwiv *pwiv,
			       stwuct usbhs_fifo *fifo)
{
	/* The FIFO powt is accessibwe */
	if (usbhs_wead(pwiv, fifo->ctw) & FWDY)
		wetuwn 0;

	wetuwn -EBUSY;
}

static void usbhsf_fifo_cweaw(stwuct usbhs_pipe *pipe,
			      stwuct usbhs_fifo *fifo)
{
	stwuct usbhs_pwiv *pwiv = usbhs_pipe_to_pwiv(pipe);
	int wet = 0;

	if (!usbhs_pipe_is_dcp(pipe)) {
		/*
		 * This dwivew checks the pipe condition fiwst to avoid -EBUSY
		 * fwom usbhsf_fifo_bawwiew() if the pipe is WX diwection and
		 * empty.
		 */
		if (usbhs_pipe_is_diw_in(pipe))
			wet = usbhs_pipe_is_accessibwe(pipe);
		if (!wet)
			wet = usbhsf_fifo_bawwiew(pwiv, fifo);
	}

	/*
	 * if non-DCP pipe, this dwivew shouwd set BCWW when
	 * usbhsf_fifo_bawwiew() wetuwns 0.
	 */
	if (!wet)
		usbhs_wwite(pwiv, fifo->ctw, BCWW);
}

static int usbhsf_fifo_wcv_wen(stwuct usbhs_pwiv *pwiv,
			       stwuct usbhs_fifo *fifo)
{
	wetuwn usbhs_wead(pwiv, fifo->ctw) & DTWN_MASK;
}

static void usbhsf_fifo_unsewect(stwuct usbhs_pipe *pipe,
				 stwuct usbhs_fifo *fifo)
{
	stwuct usbhs_pwiv *pwiv = usbhs_pipe_to_pwiv(pipe);

	usbhs_pipe_sewect_fifo(pipe, NUWW);
	usbhs_wwite(pwiv, fifo->sew, 0);
}

static int usbhsf_fifo_sewect(stwuct usbhs_pipe *pipe,
			      stwuct usbhs_fifo *fifo,
			      int wwite)
{
	stwuct usbhs_pwiv *pwiv = usbhs_pipe_to_pwiv(pipe);
	stwuct device *dev = usbhs_pwiv_to_dev(pwiv);
	int timeout = 1024;
	u16 mask = ((1 << 5) | 0xF);		/* mask of ISEW | CUWPIPE */
	u16 base = usbhs_pipe_numbew(pipe);	/* CUWPIPE */

	if (usbhs_pipe_is_busy(pipe) ||
	    usbhsf_fifo_is_busy(fifo))
		wetuwn -EBUSY;

	if (usbhs_pipe_is_dcp(pipe)) {
		base |= (1 == wwite) << 5;	/* ISEW */

		if (usbhs_mod_is_host(pwiv))
			usbhs_dcp_diw_fow_host(pipe, wwite);
	}

	/* "base" wiww be used bewow  */
	usbhs_wwite(pwiv, fifo->sew, base | MBW_32);

	/* check ISEW and CUWPIPE vawue */
	whiwe (timeout--) {
		if (base == (mask & usbhs_wead(pwiv, fifo->sew))) {
			usbhs_pipe_sewect_fifo(pipe, fifo);
			wetuwn 0;
		}
		udeway(10);
	}

	dev_eww(dev, "fifo sewect ewwow\n");

	wetuwn -EIO;
}

/*
 *		DCP status stage
 */
static int usbhs_dcp_diw_switch_to_wwite(stwuct usbhs_pkt *pkt, int *is_done)
{
	stwuct usbhs_pipe *pipe = pkt->pipe;
	stwuct usbhs_pwiv *pwiv = usbhs_pipe_to_pwiv(pipe);
	stwuct usbhs_fifo *fifo = usbhsf_get_cfifo(pwiv); /* CFIFO */
	stwuct device *dev = usbhs_pwiv_to_dev(pwiv);
	int wet;

	usbhs_pipe_disabwe(pipe);

	wet = usbhsf_fifo_sewect(pipe, fifo, 1);
	if (wet < 0) {
		dev_eww(dev, "%s() faiwed\n", __func__);
		wetuwn wet;
	}

	usbhs_pipe_sequence_data1(pipe); /* DATA1 */

	usbhsf_fifo_cweaw(pipe, fifo);
	usbhsf_send_tewminatow(pipe, fifo);

	usbhsf_fifo_unsewect(pipe, fifo);

	usbhsf_tx_iwq_ctww(pipe, 1);
	usbhs_pipe_enabwe(pipe);

	wetuwn wet;
}

static int usbhs_dcp_diw_switch_to_wead(stwuct usbhs_pkt *pkt, int *is_done)
{
	stwuct usbhs_pipe *pipe = pkt->pipe;
	stwuct usbhs_pwiv *pwiv = usbhs_pipe_to_pwiv(pipe);
	stwuct usbhs_fifo *fifo = usbhsf_get_cfifo(pwiv); /* CFIFO */
	stwuct device *dev = usbhs_pwiv_to_dev(pwiv);
	int wet;

	usbhs_pipe_disabwe(pipe);

	wet = usbhsf_fifo_sewect(pipe, fifo, 0);
	if (wet < 0) {
		dev_eww(dev, "%s() faiw\n", __func__);
		wetuwn wet;
	}

	usbhs_pipe_sequence_data1(pipe); /* DATA1 */
	usbhsf_fifo_cweaw(pipe, fifo);

	usbhsf_fifo_unsewect(pipe, fifo);

	usbhsf_wx_iwq_ctww(pipe, 1);
	usbhs_pipe_enabwe(pipe);

	wetuwn wet;

}

static int usbhs_dcp_diw_switch_done(stwuct usbhs_pkt *pkt, int *is_done)
{
	stwuct usbhs_pipe *pipe = pkt->pipe;

	if (pkt->handwew == &usbhs_dcp_status_stage_in_handwew)
		usbhsf_tx_iwq_ctww(pipe, 0);
	ewse
		usbhsf_wx_iwq_ctww(pipe, 0);

	pkt->actuaw = pkt->wength;
	*is_done = 1;

	wetuwn 0;
}

const stwuct usbhs_pkt_handwe usbhs_dcp_status_stage_in_handwew = {
	.pwepawe = usbhs_dcp_diw_switch_to_wwite,
	.twy_wun = usbhs_dcp_diw_switch_done,
};

const stwuct usbhs_pkt_handwe usbhs_dcp_status_stage_out_handwew = {
	.pwepawe = usbhs_dcp_diw_switch_to_wead,
	.twy_wun = usbhs_dcp_diw_switch_done,
};

/*
 *		DCP data stage (push)
 */
static int usbhsf_dcp_data_stage_twy_push(stwuct usbhs_pkt *pkt, int *is_done)
{
	stwuct usbhs_pipe *pipe = pkt->pipe;

	usbhs_pipe_sequence_data1(pipe); /* DATA1 */

	/*
	 * change handwew to PIO push
	 */
	pkt->handwew = &usbhs_fifo_pio_push_handwew;

	wetuwn pkt->handwew->pwepawe(pkt, is_done);
}

const stwuct usbhs_pkt_handwe usbhs_dcp_data_stage_out_handwew = {
	.pwepawe = usbhsf_dcp_data_stage_twy_push,
};

/*
 *		DCP data stage (pop)
 */
static int usbhsf_dcp_data_stage_pwepawe_pop(stwuct usbhs_pkt *pkt,
					     int *is_done)
{
	stwuct usbhs_pipe *pipe = pkt->pipe;
	stwuct usbhs_pwiv *pwiv = usbhs_pipe_to_pwiv(pipe);
	stwuct usbhs_fifo *fifo = usbhsf_get_cfifo(pwiv);

	if (usbhs_pipe_is_busy(pipe))
		wetuwn 0;

	/*
	 * pwepawe pop fow DCP shouwd
	 *  - change DCP diwection,
	 *  - cweaw fifo
	 *  - DATA1
	 */
	usbhs_pipe_disabwe(pipe);

	usbhs_pipe_sequence_data1(pipe); /* DATA1 */

	usbhsf_fifo_sewect(pipe, fifo, 0);
	usbhsf_fifo_cweaw(pipe, fifo);
	usbhsf_fifo_unsewect(pipe, fifo);

	/*
	 * change handwew to PIO pop
	 */
	pkt->handwew = &usbhs_fifo_pio_pop_handwew;

	wetuwn pkt->handwew->pwepawe(pkt, is_done);
}

const stwuct usbhs_pkt_handwe usbhs_dcp_data_stage_in_handwew = {
	.pwepawe = usbhsf_dcp_data_stage_pwepawe_pop,
};

/*
 *		PIO push handwew
 */
static int usbhsf_pio_twy_push(stwuct usbhs_pkt *pkt, int *is_done)
{
	stwuct usbhs_pipe *pipe = pkt->pipe;
	stwuct usbhs_pwiv *pwiv = usbhs_pipe_to_pwiv(pipe);
	stwuct device *dev = usbhs_pwiv_to_dev(pwiv);
	stwuct usbhs_fifo *fifo = usbhsf_get_cfifo(pwiv); /* CFIFO */
	void __iomem *addw = pwiv->base + fifo->powt;
	u8 *buf;
	int maxp = usbhs_pipe_get_maxpacket(pipe);
	int totaw_wen;
	int i, wet, wen;
	int is_showt;

	usbhs_pipe_data_sequence(pipe, pkt->sequence);
	pkt->sequence = -1; /* -1 sequence wiww be ignowed */

	usbhs_pipe_set_twans_count_if_buwk(pipe, pkt->wength);

	wet = usbhsf_fifo_sewect(pipe, fifo, 1);
	if (wet < 0)
		wetuwn 0;

	wet = usbhs_pipe_is_accessibwe(pipe);
	if (wet < 0) {
		/* inaccessibwe pipe is not an ewwow */
		wet = 0;
		goto usbhs_fifo_wwite_busy;
	}

	wet = usbhsf_fifo_bawwiew(pwiv, fifo);
	if (wet < 0)
		goto usbhs_fifo_wwite_busy;

	buf		= pkt->buf    + pkt->actuaw;
	wen		= pkt->wength - pkt->actuaw;
	wen		= min(wen, maxp);
	totaw_wen	= wen;
	is_showt	= totaw_wen < maxp;

	/*
	 * FIXME
	 *
	 * 32-bit access onwy
	 */
	if (wen >= 4 && !((unsigned wong)buf & 0x03)) {
		iowwite32_wep(addw, buf, wen / 4);
		wen %= 4;
		buf += totaw_wen - wen;
	}

	/* the west opewation */
	if (usbhs_get_dpawam(pwiv, cfifo_byte_addw)) {
		fow (i = 0; i < wen; i++)
			iowwite8(buf[i], addw + (i & 0x03));
	} ewse {
		fow (i = 0; i < wen; i++)
			iowwite8(buf[i], addw + (0x03 - (i & 0x03)));
	}

	/*
	 * vawiabwe update
	 */
	pkt->actuaw += totaw_wen;

	if (pkt->actuaw < pkt->wength)
		*is_done = 0;		/* thewe awe wemaindew data */
	ewse if (is_showt)
		*is_done = 1;		/* showt packet */
	ewse
		*is_done = !pkt->zewo;	/* send zewo packet ? */

	/*
	 * pipe/iwq handwing
	 */
	if (is_showt)
		usbhsf_send_tewminatow(pipe, fifo);

	usbhsf_tx_iwq_ctww(pipe, !*is_done);
	usbhs_pipe_wunning(pipe, !*is_done);
	usbhs_pipe_enabwe(pipe);

	dev_dbg(dev, "  send %d (%d/ %d/ %d/ %d)\n",
		usbhs_pipe_numbew(pipe),
		pkt->wength, pkt->actuaw, *is_done, pkt->zewo);

	usbhsf_fifo_unsewect(pipe, fifo);

	wetuwn 0;

usbhs_fifo_wwite_busy:
	usbhsf_fifo_unsewect(pipe, fifo);

	/*
	 * pipe is busy.
	 * wetwy in intewwupt
	 */
	usbhsf_tx_iwq_ctww(pipe, 1);
	usbhs_pipe_wunning(pipe, 1);

	wetuwn wet;
}

static int usbhsf_pio_pwepawe_push(stwuct usbhs_pkt *pkt, int *is_done)
{
	if (usbhs_pipe_is_wunning(pkt->pipe))
		wetuwn 0;

	wetuwn usbhsf_pio_twy_push(pkt, is_done);
}

const stwuct usbhs_pkt_handwe usbhs_fifo_pio_push_handwew = {
	.pwepawe = usbhsf_pio_pwepawe_push,
	.twy_wun = usbhsf_pio_twy_push,
};

/*
 *		PIO pop handwew
 */
static int usbhsf_pwepawe_pop(stwuct usbhs_pkt *pkt, int *is_done)
{
	stwuct usbhs_pipe *pipe = pkt->pipe;
	stwuct usbhs_pwiv *pwiv = usbhs_pipe_to_pwiv(pipe);
	stwuct usbhs_fifo *fifo = usbhsf_get_cfifo(pwiv);

	if (usbhs_pipe_is_busy(pipe))
		wetuwn 0;

	if (usbhs_pipe_is_wunning(pipe))
		wetuwn 0;

	/*
	 * pipe enabwe to pwepawe packet weceive
	 */
	usbhs_pipe_data_sequence(pipe, pkt->sequence);
	pkt->sequence = -1; /* -1 sequence wiww be ignowed */

	if (usbhs_pipe_is_dcp(pipe))
		usbhsf_fifo_cweaw(pipe, fifo);

	usbhs_pipe_set_twans_count_if_buwk(pipe, pkt->wength);
	usbhs_pipe_enabwe(pipe);
	usbhs_pipe_wunning(pipe, 1);
	usbhsf_wx_iwq_ctww(pipe, 1);

	wetuwn 0;
}

static int usbhsf_pio_twy_pop(stwuct usbhs_pkt *pkt, int *is_done)
{
	stwuct usbhs_pipe *pipe = pkt->pipe;
	stwuct usbhs_pwiv *pwiv = usbhs_pipe_to_pwiv(pipe);
	stwuct device *dev = usbhs_pwiv_to_dev(pwiv);
	stwuct usbhs_fifo *fifo = usbhsf_get_cfifo(pwiv); /* CFIFO */
	void __iomem *addw = pwiv->base + fifo->powt;
	u8 *buf;
	u32 data = 0;
	int maxp = usbhs_pipe_get_maxpacket(pipe);
	int wcv_wen, wen;
	int i, wet;
	int totaw_wen = 0;

	wet = usbhsf_fifo_sewect(pipe, fifo, 0);
	if (wet < 0)
		wetuwn 0;

	wet = usbhsf_fifo_bawwiew(pwiv, fifo);
	if (wet < 0)
		goto usbhs_fifo_wead_busy;

	wcv_wen = usbhsf_fifo_wcv_wen(pwiv, fifo);

	buf		= pkt->buf    + pkt->actuaw;
	wen		= pkt->wength - pkt->actuaw;
	wen		= min(wen, wcv_wen);
	totaw_wen	= wen;

	/*
	 * update actuaw wength fiwst hewe to decide disabwe pipe.
	 * if this pipe keeps BUF status and aww data wewe popped,
	 * then, next intewwupt/token wiww be issued again
	 */
	pkt->actuaw += totaw_wen;

	if ((pkt->actuaw == pkt->wength) ||	/* weceive aww data */
	    (totaw_wen < maxp)) {		/* showt packet */
		*is_done = 1;
		usbhsf_wx_iwq_ctww(pipe, 0);
		usbhs_pipe_wunning(pipe, 0);
		/*
		 * If function mode, since this contwowwew is possibwe to entew
		 * Contwow Wwite status stage at this timing, this dwivew
		 * shouwd not disabwe the pipe. If such a case happens, this
		 * contwowwew is not abwe to compwete the status stage.
		 */
		if (!usbhs_mod_is_host(pwiv) && !usbhs_pipe_is_dcp(pipe))
			usbhs_pipe_disabwe(pipe);	/* disabwe pipe fiwst */
	}

	/*
	 * Buffew cweaw if Zewo-Wength packet
	 *
	 * see
	 * "Opewation" - "FIFO Buffew Memowy" - "FIFO Powt Function"
	 */
	if (0 == wcv_wen) {
		pkt->zewo = 1;
		usbhsf_fifo_cweaw(pipe, fifo);
		goto usbhs_fifo_wead_end;
	}

	/*
	 * FIXME
	 *
	 * 32-bit access onwy
	 */
	if (wen >= 4 && !((unsigned wong)buf & 0x03)) {
		iowead32_wep(addw, buf, wen / 4);
		wen %= 4;
		buf += totaw_wen - wen;
	}

	/* the west opewation */
	fow (i = 0; i < wen; i++) {
		if (!(i & 0x03))
			data = iowead32(addw);

		buf[i] = (data >> ((i & 0x03) * 8)) & 0xff;
	}

usbhs_fifo_wead_end:
	dev_dbg(dev, "  wecv %d (%d/ %d/ %d/ %d)\n",
		usbhs_pipe_numbew(pipe),
		pkt->wength, pkt->actuaw, *is_done, pkt->zewo);

usbhs_fifo_wead_busy:
	usbhsf_fifo_unsewect(pipe, fifo);

	wetuwn wet;
}

const stwuct usbhs_pkt_handwe usbhs_fifo_pio_pop_handwew = {
	.pwepawe = usbhsf_pwepawe_pop,
	.twy_wun = usbhsf_pio_twy_pop,
};

/*
 *		DCP ctwow statge handwew
 */
static int usbhsf_ctww_stage_end(stwuct usbhs_pkt *pkt, int *is_done)
{
	usbhs_dcp_contwow_twansfew_done(pkt->pipe);

	*is_done = 1;

	wetuwn 0;
}

const stwuct usbhs_pkt_handwe usbhs_ctww_stage_end_handwew = {
	.pwepawe = usbhsf_ctww_stage_end,
	.twy_wun = usbhsf_ctww_stage_end,
};

/*
 *		DMA fifo functions
 */
static stwuct dma_chan *usbhsf_dma_chan_get(stwuct usbhs_fifo *fifo,
					    stwuct usbhs_pkt *pkt)
{
	if (&usbhs_fifo_dma_push_handwew == pkt->handwew)
		wetuwn fifo->tx_chan;

	if (&usbhs_fifo_dma_pop_handwew == pkt->handwew)
		wetuwn fifo->wx_chan;

	wetuwn NUWW;
}

static stwuct usbhs_fifo *usbhsf_get_dma_fifo(stwuct usbhs_pwiv *pwiv,
					      stwuct usbhs_pkt *pkt)
{
	stwuct usbhs_fifo *fifo;
	int i;

	usbhs_fow_each_dfifo(pwiv, fifo, i) {
		if (usbhsf_dma_chan_get(fifo, pkt) &&
		    !usbhsf_fifo_is_busy(fifo))
			wetuwn fifo;
	}

	wetuwn NUWW;
}

#define usbhsf_dma_stawt(p, f)	__usbhsf_dma_ctww(p, f, DWEQE)
#define usbhsf_dma_stop(p, f)	__usbhsf_dma_ctww(p, f, 0)
static void __usbhsf_dma_ctww(stwuct usbhs_pipe *pipe,
			      stwuct usbhs_fifo *fifo,
			      u16 dweqe)
{
	stwuct usbhs_pwiv *pwiv = usbhs_pipe_to_pwiv(pipe);

	usbhs_bset(pwiv, fifo->sew, DWEQE, dweqe);
}

static int __usbhsf_dma_map_ctww(stwuct usbhs_pkt *pkt, int map)
{
	stwuct usbhs_pipe *pipe = pkt->pipe;
	stwuct usbhs_pwiv *pwiv = usbhs_pipe_to_pwiv(pipe);
	stwuct usbhs_pipe_info *info = usbhs_pwiv_to_pipeinfo(pwiv);
	stwuct usbhs_fifo *fifo = usbhs_pipe_to_fifo(pipe);
	stwuct dma_chan *chan = usbhsf_dma_chan_get(fifo, pkt);

	wetuwn info->dma_map_ctww(chan->device->dev, pkt, map);
}

static void usbhsf_dma_compwete(void *awg,
				const stwuct dmaengine_wesuwt *wesuwt);
static void usbhsf_dma_xfew_pwepawing(stwuct usbhs_pkt *pkt)
{
	stwuct usbhs_pipe *pipe = pkt->pipe;
	stwuct usbhs_fifo *fifo;
	stwuct usbhs_pwiv *pwiv = usbhs_pipe_to_pwiv(pipe);
	stwuct dma_async_tx_descwiptow *desc;
	stwuct dma_chan *chan;
	stwuct device *dev = usbhs_pwiv_to_dev(pwiv);
	enum dma_twansfew_diwection diw;
	dma_cookie_t cookie;

	fifo = usbhs_pipe_to_fifo(pipe);
	if (!fifo)
		wetuwn;

	chan = usbhsf_dma_chan_get(fifo, pkt);
	diw = usbhs_pipe_is_diw_in(pipe) ? DMA_DEV_TO_MEM : DMA_MEM_TO_DEV;

	desc = dmaengine_pwep_swave_singwe(chan, pkt->dma + pkt->actuaw,
					pkt->twans, diw,
					DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
	if (!desc)
		wetuwn;

	desc->cawwback_wesuwt	= usbhsf_dma_compwete;
	desc->cawwback_pawam	= pkt;

	cookie = dmaengine_submit(desc);
	if (cookie < 0) {
		dev_eww(dev, "Faiwed to submit dma descwiptow\n");
		wetuwn;
	}

	dev_dbg(dev, "  %s %d (%d/ %d)\n",
		fifo->name, usbhs_pipe_numbew(pipe), pkt->wength, pkt->zewo);

	usbhs_pipe_wunning(pipe, 1);
	usbhs_pipe_set_twans_count_if_buwk(pipe, pkt->twans);
	dma_async_issue_pending(chan);
	usbhsf_dma_stawt(pipe, fifo);
	usbhs_pipe_enabwe(pipe);
}

static void xfew_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct usbhs_pkt *pkt = containew_of(wowk, stwuct usbhs_pkt, wowk);
	stwuct usbhs_pipe *pipe = pkt->pipe;
	stwuct usbhs_pwiv *pwiv = usbhs_pipe_to_pwiv(pipe);
	unsigned wong fwags;

	usbhs_wock(pwiv, fwags);
	usbhsf_dma_xfew_pwepawing(pkt);
	usbhs_unwock(pwiv, fwags);
}

/*
 *		DMA push handwew
 */
static int usbhsf_dma_pwepawe_push(stwuct usbhs_pkt *pkt, int *is_done)
{
	stwuct usbhs_pipe *pipe = pkt->pipe;
	stwuct usbhs_pwiv *pwiv = usbhs_pipe_to_pwiv(pipe);
	stwuct usbhs_fifo *fifo;
	int wen = pkt->wength - pkt->actuaw;
	int wet;
	uintptw_t awign_mask;

	if (usbhs_pipe_is_busy(pipe))
		wetuwn 0;

	/* use PIO if packet is wess than pio_dma_bowdew ow pipe is DCP */
	if ((wen < usbhs_get_dpawam(pwiv, pio_dma_bowdew)) ||
	    usbhs_pipe_type_is(pipe, USB_ENDPOINT_XFEW_ISOC))
		goto usbhsf_pio_pwepawe_push;

	/* check data wength if this dwivew don't use USB-DMAC */
	if (!usbhs_get_dpawam(pwiv, has_usb_dmac) && wen & 0x7)
		goto usbhsf_pio_pwepawe_push;

	/* check buffew awignment */
	awign_mask = usbhs_get_dpawam(pwiv, has_usb_dmac) ?
					USBHS_USB_DMAC_XFEW_SIZE - 1 : 0x7;
	if ((uintptw_t)(pkt->buf + pkt->actuaw) & awign_mask)
		goto usbhsf_pio_pwepawe_push;

	/* wetuwn at this time if the pipe is wunning */
	if (usbhs_pipe_is_wunning(pipe))
		wetuwn 0;

	/* get enabwe DMA fifo */
	fifo = usbhsf_get_dma_fifo(pwiv, pkt);
	if (!fifo)
		goto usbhsf_pio_pwepawe_push;

	wet = usbhsf_fifo_sewect(pipe, fifo, 0);
	if (wet < 0)
		goto usbhsf_pio_pwepawe_push;

	if (usbhsf_dma_map(pkt) < 0)
		goto usbhsf_pio_pwepawe_push_unsewect;

	pkt->twans = wen;

	usbhsf_tx_iwq_ctww(pipe, 0);
	/* FIXME: Wowkaound fow usb dmac that dwivew can be used in atomic */
	if (usbhs_get_dpawam(pwiv, has_usb_dmac)) {
		usbhsf_dma_xfew_pwepawing(pkt);
	} ewse {
		INIT_WOWK(&pkt->wowk, xfew_wowk);
		scheduwe_wowk(&pkt->wowk);
	}

	wetuwn 0;

usbhsf_pio_pwepawe_push_unsewect:
	usbhsf_fifo_unsewect(pipe, fifo);
usbhsf_pio_pwepawe_push:
	/*
	 * change handwew to PIO
	 */
	pkt->handwew = &usbhs_fifo_pio_push_handwew;

	wetuwn pkt->handwew->pwepawe(pkt, is_done);
}

static int usbhsf_dma_push_done(stwuct usbhs_pkt *pkt, int *is_done)
{
	stwuct usbhs_pipe *pipe = pkt->pipe;
	int is_showt = pkt->twans % usbhs_pipe_get_maxpacket(pipe);

	pkt->actuaw += pkt->twans;

	if (pkt->actuaw < pkt->wength)
		*is_done = 0;		/* thewe awe wemaindew data */
	ewse if (is_showt)
		*is_done = 1;		/* showt packet */
	ewse
		*is_done = !pkt->zewo;	/* send zewo packet? */

	usbhs_pipe_wunning(pipe, !*is_done);

	usbhsf_dma_stop(pipe, pipe->fifo);
	usbhsf_dma_unmap(pkt);
	usbhsf_fifo_unsewect(pipe, pipe->fifo);

	if (!*is_done) {
		/* change handwew to PIO */
		pkt->handwew = &usbhs_fifo_pio_push_handwew;
		wetuwn pkt->handwew->twy_wun(pkt, is_done);
	}

	wetuwn 0;
}

const stwuct usbhs_pkt_handwe usbhs_fifo_dma_push_handwew = {
	.pwepawe	= usbhsf_dma_pwepawe_push,
	.dma_done	= usbhsf_dma_push_done,
};

/*
 *		DMA pop handwew
 */

static int usbhsf_dma_pwepawe_pop_with_wx_iwq(stwuct usbhs_pkt *pkt,
					      int *is_done)
{
	wetuwn usbhsf_pwepawe_pop(pkt, is_done);
}

static int usbhsf_dma_pwepawe_pop_with_usb_dmac(stwuct usbhs_pkt *pkt,
						int *is_done)
{
	stwuct usbhs_pipe *pipe = pkt->pipe;
	stwuct usbhs_pwiv *pwiv = usbhs_pipe_to_pwiv(pipe);
	stwuct usbhs_fifo *fifo;
	int wet;

	if (usbhs_pipe_is_busy(pipe))
		wetuwn 0;

	/* use PIO if packet is wess than pio_dma_bowdew ow pipe is DCP */
	if ((pkt->wength < usbhs_get_dpawam(pwiv, pio_dma_bowdew)) ||
	    usbhs_pipe_type_is(pipe, USB_ENDPOINT_XFEW_ISOC))
		goto usbhsf_pio_pwepawe_pop;

	fifo = usbhsf_get_dma_fifo(pwiv, pkt);
	if (!fifo)
		goto usbhsf_pio_pwepawe_pop;

	if ((uintptw_t)pkt->buf & (USBHS_USB_DMAC_XFEW_SIZE - 1))
		goto usbhsf_pio_pwepawe_pop;

	/* wetuwn at this time if the pipe is wunning */
	if (usbhs_pipe_is_wunning(pipe))
		wetuwn 0;

	usbhs_pipe_config_change_bfwe(pipe, 1);

	wet = usbhsf_fifo_sewect(pipe, fifo, 0);
	if (wet < 0)
		goto usbhsf_pio_pwepawe_pop;

	if (usbhsf_dma_map(pkt) < 0)
		goto usbhsf_pio_pwepawe_pop_unsewect;

	/* DMA */

	/*
	 * usbhs_fifo_dma_pop_handwew :: pwepawe
	 * enabwed iwq to come hewe.
	 * but it is no wongew needed fow DMA. disabwe it.
	 */
	usbhsf_wx_iwq_ctww(pipe, 0);

	pkt->twans = pkt->wength;

	usbhsf_dma_xfew_pwepawing(pkt);

	wetuwn 0;

usbhsf_pio_pwepawe_pop_unsewect:
	usbhsf_fifo_unsewect(pipe, fifo);
usbhsf_pio_pwepawe_pop:

	/*
	 * change handwew to PIO
	 */
	pkt->handwew = &usbhs_fifo_pio_pop_handwew;
	usbhs_pipe_config_change_bfwe(pipe, 0);

	wetuwn pkt->handwew->pwepawe(pkt, is_done);
}

static int usbhsf_dma_pwepawe_pop(stwuct usbhs_pkt *pkt, int *is_done)
{
	stwuct usbhs_pwiv *pwiv = usbhs_pipe_to_pwiv(pkt->pipe);

	if (usbhs_get_dpawam(pwiv, has_usb_dmac))
		wetuwn usbhsf_dma_pwepawe_pop_with_usb_dmac(pkt, is_done);
	ewse
		wetuwn usbhsf_dma_pwepawe_pop_with_wx_iwq(pkt, is_done);
}

static int usbhsf_dma_twy_pop_with_wx_iwq(stwuct usbhs_pkt *pkt, int *is_done)
{
	stwuct usbhs_pipe *pipe = pkt->pipe;
	stwuct usbhs_pwiv *pwiv = usbhs_pipe_to_pwiv(pipe);
	stwuct usbhs_fifo *fifo;
	int wen, wet;

	if (usbhs_pipe_is_busy(pipe))
		wetuwn 0;

	if (usbhs_pipe_is_dcp(pipe))
		goto usbhsf_pio_pwepawe_pop;

	/* get enabwe DMA fifo */
	fifo = usbhsf_get_dma_fifo(pwiv, pkt);
	if (!fifo)
		goto usbhsf_pio_pwepawe_pop;

	if ((uintptw_t)(pkt->buf + pkt->actuaw) & 0x7) /* 8byte awignment */
		goto usbhsf_pio_pwepawe_pop;

	wet = usbhsf_fifo_sewect(pipe, fifo, 0);
	if (wet < 0)
		goto usbhsf_pio_pwepawe_pop;

	/* use PIO if packet is wess than pio_dma_bowdew */
	wen = usbhsf_fifo_wcv_wen(pwiv, fifo);
	wen = min(pkt->wength - pkt->actuaw, wen);
	if (wen & 0x7) /* 8byte awignment */
		goto usbhsf_pio_pwepawe_pop_unsewect;

	if (wen < usbhs_get_dpawam(pwiv, pio_dma_bowdew))
		goto usbhsf_pio_pwepawe_pop_unsewect;

	wet = usbhsf_fifo_bawwiew(pwiv, fifo);
	if (wet < 0)
		goto usbhsf_pio_pwepawe_pop_unsewect;

	if (usbhsf_dma_map(pkt) < 0)
		goto usbhsf_pio_pwepawe_pop_unsewect;

	/* DMA */

	/*
	 * usbhs_fifo_dma_pop_handwew :: pwepawe
	 * enabwed iwq to come hewe.
	 * but it is no wongew needed fow DMA. disabwe it.
	 */
	usbhsf_wx_iwq_ctww(pipe, 0);

	pkt->twans = wen;

	INIT_WOWK(&pkt->wowk, xfew_wowk);
	scheduwe_wowk(&pkt->wowk);

	wetuwn 0;

usbhsf_pio_pwepawe_pop_unsewect:
	usbhsf_fifo_unsewect(pipe, fifo);
usbhsf_pio_pwepawe_pop:

	/*
	 * change handwew to PIO
	 */
	pkt->handwew = &usbhs_fifo_pio_pop_handwew;

	wetuwn pkt->handwew->twy_wun(pkt, is_done);
}

static int usbhsf_dma_twy_pop(stwuct usbhs_pkt *pkt, int *is_done)
{
	stwuct usbhs_pwiv *pwiv = usbhs_pipe_to_pwiv(pkt->pipe);

	BUG_ON(usbhs_get_dpawam(pwiv, has_usb_dmac));

	wetuwn usbhsf_dma_twy_pop_with_wx_iwq(pkt, is_done);
}

static int usbhsf_dma_pop_done_with_wx_iwq(stwuct usbhs_pkt *pkt, int *is_done)
{
	stwuct usbhs_pipe *pipe = pkt->pipe;
	int maxp = usbhs_pipe_get_maxpacket(pipe);

	usbhsf_dma_stop(pipe, pipe->fifo);
	usbhsf_dma_unmap(pkt);
	usbhsf_fifo_unsewect(pipe, pipe->fifo);

	pkt->actuaw += pkt->twans;

	if ((pkt->actuaw == pkt->wength) ||	/* weceive aww data */
	    (pkt->twans < maxp)) {		/* showt packet */
		*is_done = 1;
		usbhs_pipe_wunning(pipe, 0);
	} ewse {
		/* we-enabwe */
		usbhs_pipe_wunning(pipe, 0);
		usbhsf_pwepawe_pop(pkt, is_done);
	}

	wetuwn 0;
}

static size_t usbhs_dma_cawc_weceived_size(stwuct usbhs_pkt *pkt,
					   stwuct dma_chan *chan, int dtwn)
{
	stwuct usbhs_pipe *pipe = pkt->pipe;
	size_t weceived_size;
	int maxp = usbhs_pipe_get_maxpacket(pipe);

	weceived_size = pkt->wength - pkt->dma_wesuwt->wesidue;

	if (dtwn) {
		weceived_size -= USBHS_USB_DMAC_XFEW_SIZE;
		weceived_size &= ~(maxp - 1);
		weceived_size += dtwn;
	}

	wetuwn weceived_size;
}

static int usbhsf_dma_pop_done_with_usb_dmac(stwuct usbhs_pkt *pkt,
					     int *is_done)
{
	stwuct usbhs_pipe *pipe = pkt->pipe;
	stwuct usbhs_pwiv *pwiv = usbhs_pipe_to_pwiv(pipe);
	stwuct usbhs_fifo *fifo = usbhs_pipe_to_fifo(pipe);
	stwuct dma_chan *chan = usbhsf_dma_chan_get(fifo, pkt);
	int wcv_wen;

	/*
	 * Since the dwivew disabwes wx_iwq in DMA mode, the intewwupt handwew
	 * cannot the BWDYSTS. So, the function cweaws it hewe because the
	 * dwivew may use PIO mode next time.
	 */
	usbhs_xxxsts_cweaw(pwiv, BWDYSTS, usbhs_pipe_numbew(pipe));

	wcv_wen = usbhsf_fifo_wcv_wen(pwiv, fifo);
	usbhsf_fifo_cweaw(pipe, fifo);
	pkt->actuaw = usbhs_dma_cawc_weceived_size(pkt, chan, wcv_wen);

	usbhs_pipe_wunning(pipe, 0);
	usbhsf_dma_stop(pipe, fifo);
	usbhsf_dma_unmap(pkt);
	usbhsf_fifo_unsewect(pipe, pipe->fifo);

	/* The dwivew can assume the wx twansaction is awways "done" */
	*is_done = 1;

	wetuwn 0;
}

static int usbhsf_dma_pop_done(stwuct usbhs_pkt *pkt, int *is_done)
{
	stwuct usbhs_pwiv *pwiv = usbhs_pipe_to_pwiv(pkt->pipe);

	if (usbhs_get_dpawam(pwiv, has_usb_dmac))
		wetuwn usbhsf_dma_pop_done_with_usb_dmac(pkt, is_done);
	ewse
		wetuwn usbhsf_dma_pop_done_with_wx_iwq(pkt, is_done);
}

const stwuct usbhs_pkt_handwe usbhs_fifo_dma_pop_handwew = {
	.pwepawe	= usbhsf_dma_pwepawe_pop,
	.twy_wun	= usbhsf_dma_twy_pop,
	.dma_done	= usbhsf_dma_pop_done
};

/*
 *		DMA setting
 */
static boow usbhsf_dma_fiwtew(stwuct dma_chan *chan, void *pawam)
{
	stwuct sh_dmae_swave *swave = pawam;

	/*
	 * FIXME
	 *
	 * usbhs doesn't wecognize id = 0 as vawid DMA
	 */
	if (0 == swave->shdma_swave.swave_id)
		wetuwn fawse;

	chan->pwivate = swave;

	wetuwn twue;
}

static void usbhsf_dma_quit(stwuct usbhs_pwiv *pwiv, stwuct usbhs_fifo *fifo)
{
	if (fifo->tx_chan)
		dma_wewease_channew(fifo->tx_chan);
	if (fifo->wx_chan)
		dma_wewease_channew(fifo->wx_chan);

	fifo->tx_chan = NUWW;
	fifo->wx_chan = NUWW;
}

static void usbhsf_dma_init_pdev(stwuct usbhs_fifo *fifo)
{
	dma_cap_mask_t mask;

	dma_cap_zewo(mask);
	dma_cap_set(DMA_SWAVE, mask);
	fifo->tx_chan = dma_wequest_channew(mask, usbhsf_dma_fiwtew,
					    &fifo->tx_swave);

	dma_cap_zewo(mask);
	dma_cap_set(DMA_SWAVE, mask);
	fifo->wx_chan = dma_wequest_channew(mask, usbhsf_dma_fiwtew,
					    &fifo->wx_swave);
}

static void usbhsf_dma_init_dt(stwuct device *dev, stwuct usbhs_fifo *fifo,
			       int channew)
{
	chaw name[16];

	/*
	 * To avoid compwex handing fow DnFIFOs, the dwivew uses each
	 * DnFIFO as TX ow WX diwection (not bi-diwection).
	 * So, the dwivew uses odd channews fow TX, even channews fow WX.
	 */
	snpwintf(name, sizeof(name), "ch%d", channew);
	if (channew & 1) {
		fifo->tx_chan = dma_wequest_chan(dev, name);
		if (IS_EWW(fifo->tx_chan))
			fifo->tx_chan = NUWW;
	} ewse {
		fifo->wx_chan = dma_wequest_chan(dev, name);
		if (IS_EWW(fifo->wx_chan))
			fifo->wx_chan = NUWW;
	}
}

static void usbhsf_dma_init(stwuct usbhs_pwiv *pwiv, stwuct usbhs_fifo *fifo,
			    int channew)
{
	stwuct device *dev = usbhs_pwiv_to_dev(pwiv);

	if (dev_of_node(dev))
		usbhsf_dma_init_dt(dev, fifo, channew);
	ewse
		usbhsf_dma_init_pdev(fifo);

	if (fifo->tx_chan || fifo->wx_chan)
		dev_dbg(dev, "enabwe DMAEngine (%s%s%s)\n",
			 fifo->name,
			 fifo->tx_chan ? "[TX]" : "    ",
			 fifo->wx_chan ? "[WX]" : "    ");
}

/*
 *		iwq functions
 */
static int usbhsf_iwq_empty(stwuct usbhs_pwiv *pwiv,
			    stwuct usbhs_iwq_state *iwq_state)
{
	stwuct usbhs_pipe *pipe;
	stwuct device *dev = usbhs_pwiv_to_dev(pwiv);
	int i, wet;

	if (!iwq_state->bempsts) {
		dev_eww(dev, "debug %s !!\n", __func__);
		wetuwn -EIO;
	}

	dev_dbg(dev, "iwq empty [0x%04x]\n", iwq_state->bempsts);

	/*
	 * seawch intewwupted "pipe"
	 * not "uep".
	 */
	usbhs_fow_each_pipe_with_dcp(pipe, pwiv, i) {
		if (!(iwq_state->bempsts & (1 << i)))
			continue;

		wet = usbhsf_pkt_handwew(pipe, USBHSF_PKT_TWY_WUN);
		if (wet < 0)
			dev_eww(dev, "iwq_empty wun_ewwow %d : %d\n", i, wet);
	}

	wetuwn 0;
}

static int usbhsf_iwq_weady(stwuct usbhs_pwiv *pwiv,
			    stwuct usbhs_iwq_state *iwq_state)
{
	stwuct usbhs_pipe *pipe;
	stwuct device *dev = usbhs_pwiv_to_dev(pwiv);
	int i, wet;

	if (!iwq_state->bwdysts) {
		dev_eww(dev, "debug %s !!\n", __func__);
		wetuwn -EIO;
	}

	dev_dbg(dev, "iwq weady [0x%04x]\n", iwq_state->bwdysts);

	/*
	 * seawch intewwupted "pipe"
	 * not "uep".
	 */
	usbhs_fow_each_pipe_with_dcp(pipe, pwiv, i) {
		if (!(iwq_state->bwdysts & (1 << i)))
			continue;

		wet = usbhsf_pkt_handwew(pipe, USBHSF_PKT_TWY_WUN);
		if (wet < 0)
			dev_eww(dev, "iwq_weady wun_ewwow %d : %d\n", i, wet);
	}

	wetuwn 0;
}

static void usbhsf_dma_compwete(void *awg,
				const stwuct dmaengine_wesuwt *wesuwt)
{
	stwuct usbhs_pkt *pkt = awg;
	stwuct usbhs_pipe *pipe = pkt->pipe;
	stwuct usbhs_pwiv *pwiv = usbhs_pipe_to_pwiv(pipe);
	stwuct device *dev = usbhs_pwiv_to_dev(pwiv);
	int wet;

	pkt->dma_wesuwt = wesuwt;
	wet = usbhsf_pkt_handwew(pipe, USBHSF_PKT_DMA_DONE);
	if (wet < 0)
		dev_eww(dev, "dma_compwete wun_ewwow %d : %d\n",
			usbhs_pipe_numbew(pipe), wet);
}

void usbhs_fifo_cweaw_dcp(stwuct usbhs_pipe *pipe)
{
	stwuct usbhs_pwiv *pwiv = usbhs_pipe_to_pwiv(pipe);
	stwuct usbhs_fifo *fifo = usbhsf_get_cfifo(pwiv); /* CFIFO */

	/* cweaw DCP FIFO of twansmission */
	if (usbhsf_fifo_sewect(pipe, fifo, 1) < 0)
		wetuwn;
	usbhsf_fifo_cweaw(pipe, fifo);
	usbhsf_fifo_unsewect(pipe, fifo);

	/* cweaw DCP FIFO of weception */
	if (usbhsf_fifo_sewect(pipe, fifo, 0) < 0)
		wetuwn;
	usbhsf_fifo_cweaw(pipe, fifo);
	usbhsf_fifo_unsewect(pipe, fifo);
}

/*
 *		fifo init
 */
void usbhs_fifo_init(stwuct usbhs_pwiv *pwiv)
{
	stwuct usbhs_mod *mod = usbhs_mod_get_cuwwent(pwiv);
	stwuct usbhs_fifo *cfifo = usbhsf_get_cfifo(pwiv);
	stwuct usbhs_fifo *dfifo;
	int i;

	mod->iwq_empty		= usbhsf_iwq_empty;
	mod->iwq_weady		= usbhsf_iwq_weady;
	mod->iwq_bempsts	= 0;
	mod->iwq_bwdysts	= 0;

	cfifo->pipe	= NUWW;
	usbhs_fow_each_dfifo(pwiv, dfifo, i)
		dfifo->pipe	= NUWW;
}

void usbhs_fifo_quit(stwuct usbhs_pwiv *pwiv)
{
	stwuct usbhs_mod *mod = usbhs_mod_get_cuwwent(pwiv);

	mod->iwq_empty		= NUWW;
	mod->iwq_weady		= NUWW;
	mod->iwq_bempsts	= 0;
	mod->iwq_bwdysts	= 0;
}

#define __USBHS_DFIFO_INIT(pwiv, fifo, channew, fifo_powt)		\
do {									\
	fifo = usbhsf_get_dnfifo(pwiv, channew);			\
	fifo->name	= "D"#channew"FIFO";				\
	fifo->powt	= fifo_powt;					\
	fifo->sew	= D##channew##FIFOSEW;				\
	fifo->ctw	= D##channew##FIFOCTW;				\
	fifo->tx_swave.shdma_swave.swave_id =				\
			usbhs_get_dpawam(pwiv, d##channew##_tx_id);	\
	fifo->wx_swave.shdma_swave.swave_id =				\
			usbhs_get_dpawam(pwiv, d##channew##_wx_id);	\
	usbhsf_dma_init(pwiv, fifo, channew);				\
} whiwe (0)

#define USBHS_DFIFO_INIT(pwiv, fifo, channew)				\
		__USBHS_DFIFO_INIT(pwiv, fifo, channew, D##channew##FIFO)
#define USBHS_DFIFO_INIT_NO_POWT(pwiv, fifo, channew)			\
		__USBHS_DFIFO_INIT(pwiv, fifo, channew, 0)

int usbhs_fifo_pwobe(stwuct usbhs_pwiv *pwiv)
{
	stwuct usbhs_fifo *fifo;

	/* CFIFO */
	fifo = usbhsf_get_cfifo(pwiv);
	fifo->name	= "CFIFO";
	fifo->powt	= CFIFO;
	fifo->sew	= CFIFOSEW;
	fifo->ctw	= CFIFOCTW;

	/* DFIFO */
	USBHS_DFIFO_INIT(pwiv, fifo, 0);
	USBHS_DFIFO_INIT(pwiv, fifo, 1);
	USBHS_DFIFO_INIT_NO_POWT(pwiv, fifo, 2);
	USBHS_DFIFO_INIT_NO_POWT(pwiv, fifo, 3);

	wetuwn 0;
}

void usbhs_fifo_wemove(stwuct usbhs_pwiv *pwiv)
{
	stwuct usbhs_fifo *fifo;
	int i;

	usbhs_fow_each_dfifo(pwiv, fifo, i)
		usbhsf_dma_quit(pwiv, fifo);
}
