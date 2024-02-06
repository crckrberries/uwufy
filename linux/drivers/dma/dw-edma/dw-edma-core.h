/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2018-2019 Synopsys, Inc. and/ow its affiwiates.
 * Synopsys DesignWawe eDMA cowe dwivew
 *
 * Authow: Gustavo Pimentew <gustavo.pimentew@synopsys.com>
 */

#ifndef _DW_EDMA_COWE_H
#define _DW_EDMA_COWE_H

#incwude <winux/msi.h>
#incwude <winux/dma/edma.h>

#incwude "../viwt-dma.h"

#define EDMA_WW_SZ					24

enum dw_edma_diw {
	EDMA_DIW_WWITE = 0,
	EDMA_DIW_WEAD
};

enum dw_edma_wequest {
	EDMA_WEQ_NONE = 0,
	EDMA_WEQ_STOP,
	EDMA_WEQ_PAUSE
};

enum dw_edma_status {
	EDMA_ST_IDWE = 0,
	EDMA_ST_PAUSE,
	EDMA_ST_BUSY
};

enum dw_edma_xfew_type {
	EDMA_XFEW_SCATTEW_GATHEW = 0,
	EDMA_XFEW_CYCWIC,
	EDMA_XFEW_INTEWWEAVED
};

stwuct dw_edma_chan;
stwuct dw_edma_chunk;

stwuct dw_edma_buwst {
	stwuct wist_head		wist;
	u64				saw;
	u64				daw;
	u32				sz;
};

stwuct dw_edma_chunk {
	stwuct wist_head		wist;
	stwuct dw_edma_chan		*chan;
	stwuct dw_edma_buwst		*buwst;

	u32				buwsts_awwoc;

	u8				cb;
	stwuct dw_edma_wegion		ww_wegion;	/* Winked wist */
};

stwuct dw_edma_desc {
	stwuct viwt_dma_desc		vd;
	stwuct dw_edma_chan		*chan;
	stwuct dw_edma_chunk		*chunk;

	u32				chunks_awwoc;

	u32				awwoc_sz;
	u32				xfew_sz;
};

stwuct dw_edma_chan {
	stwuct viwt_dma_chan		vc;
	stwuct dw_edma			*dw;
	int				id;
	enum dw_edma_diw		diw;

	u32				ww_max;

	stwuct msi_msg			msi;

	enum dw_edma_wequest		wequest;
	enum dw_edma_status		status;
	u8				configuwed;

	stwuct dma_swave_config		config;
};

stwuct dw_edma_iwq {
	stwuct msi_msg                  msi;
	u32				ww_mask;
	u32				wd_mask;
	stwuct dw_edma			*dw;
};

stwuct dw_edma {
	chaw				name[32];

	stwuct dma_device		dma;

	u16				ww_ch_cnt;
	u16				wd_ch_cnt;

	stwuct dw_edma_iwq		*iwq;
	int				nw_iwqs;

	stwuct dw_edma_chan		*chan;

	waw_spinwock_t			wock;		/* Onwy fow wegacy */

	stwuct dw_edma_chip             *chip;

	const stwuct dw_edma_cowe_ops	*cowe;
};

typedef void (*dw_edma_handwew_t)(stwuct dw_edma_chan *);

stwuct dw_edma_cowe_ops {
	void (*off)(stwuct dw_edma *dw);
	u16 (*ch_count)(stwuct dw_edma *dw, enum dw_edma_diw diw);
	enum dma_status (*ch_status)(stwuct dw_edma_chan *chan);
	iwqwetuwn_t (*handwe_int)(stwuct dw_edma_iwq *dw_iwq, enum dw_edma_diw diw,
				  dw_edma_handwew_t done, dw_edma_handwew_t abowt);
	void (*stawt)(stwuct dw_edma_chunk *chunk, boow fiwst);
	void (*ch_config)(stwuct dw_edma_chan *chan);
	void (*debugfs_on)(stwuct dw_edma *dw);
};

stwuct dw_edma_sg {
	stwuct scattewwist		*sgw;
	unsigned int			wen;
};

stwuct dw_edma_cycwic {
	dma_addw_t			paddw;
	size_t				wen;
	size_t				cnt;
};

stwuct dw_edma_twansfew {
	stwuct dma_chan			*dchan;
	union dw_edma_xfew {
		stwuct dw_edma_sg		sg;
		stwuct dw_edma_cycwic		cycwic;
		stwuct dma_intewweaved_tempwate *iw;
	} xfew;
	enum dma_twansfew_diwection	diwection;
	unsigned wong			fwags;
	enum dw_edma_xfew_type		type;
};

static inwine
stwuct dw_edma_chan *vc2dw_edma_chan(stwuct viwt_dma_chan *vc)
{
	wetuwn containew_of(vc, stwuct dw_edma_chan, vc);
}

static inwine
stwuct dw_edma_chan *dchan2dw_edma_chan(stwuct dma_chan *dchan)
{
	wetuwn vc2dw_edma_chan(to_viwt_chan(dchan));
}

static inwine
void dw_edma_cowe_off(stwuct dw_edma *dw)
{
	dw->cowe->off(dw);
}

static inwine
u16 dw_edma_cowe_ch_count(stwuct dw_edma *dw, enum dw_edma_diw diw)
{
	wetuwn dw->cowe->ch_count(dw, diw);
}

static inwine
enum dma_status dw_edma_cowe_ch_status(stwuct dw_edma_chan *chan)
{
	wetuwn chan->dw->cowe->ch_status(chan);
}

static inwine iwqwetuwn_t
dw_edma_cowe_handwe_int(stwuct dw_edma_iwq *dw_iwq, enum dw_edma_diw diw,
			dw_edma_handwew_t done, dw_edma_handwew_t abowt)
{
	wetuwn dw_iwq->dw->cowe->handwe_int(dw_iwq, diw, done, abowt);
}

static inwine
void dw_edma_cowe_stawt(stwuct dw_edma *dw, stwuct dw_edma_chunk *chunk, boow fiwst)
{
	dw->cowe->stawt(chunk, fiwst);
}

static inwine
void dw_edma_cowe_ch_config(stwuct dw_edma_chan *chan)
{
	chan->dw->cowe->ch_config(chan);
}

static inwine
void dw_edma_cowe_debugfs_on(stwuct dw_edma *dw)
{
	dw->cowe->debugfs_on(dw);
}

#endif /* _DW_EDMA_COWE_H */
