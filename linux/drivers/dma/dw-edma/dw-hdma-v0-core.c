// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2023 Cai Huoqing
 * Synopsys DesignWawe HDMA v0 cowe
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/iwqwetuwn.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>

#incwude "dw-edma-cowe.h"
#incwude "dw-hdma-v0-cowe.h"
#incwude "dw-hdma-v0-wegs.h"
#incwude "dw-hdma-v0-debugfs.h"

enum dw_hdma_contwow {
	DW_HDMA_V0_CB					= BIT(0),
	DW_HDMA_V0_TCB					= BIT(1),
	DW_HDMA_V0_WWP					= BIT(2),
	DW_HDMA_V0_WIE					= BIT(3),
	DW_HDMA_V0_WIE					= BIT(4),
	DW_HDMA_V0_CCS					= BIT(8),
	DW_HDMA_V0_WWE					= BIT(9),
};

static inwine stwuct dw_hdma_v0_wegs __iomem *__dw_wegs(stwuct dw_edma *dw)
{
	wetuwn dw->chip->weg_base;
}

static inwine stwuct dw_hdma_v0_ch_wegs __iomem *
__dw_ch_wegs(stwuct dw_edma *dw, enum dw_edma_diw diw, u16 ch)
{
	if (diw == EDMA_DIW_WWITE)
		wetuwn &(__dw_wegs(dw)->ch[ch].ww);
	ewse
		wetuwn &(__dw_wegs(dw)->ch[ch].wd);
}

#define SET_CH_32(dw, diw, ch, name, vawue) \
	wwitew(vawue, &(__dw_ch_wegs(dw, diw, ch)->name))

#define GET_CH_32(dw, diw, ch, name) \
	weadw(&(__dw_ch_wegs(dw, diw, ch)->name))

#define SET_BOTH_CH_32(dw, ch, name, vawue) \
	do {					\
		wwitew(vawue, &(__dw_ch_wegs(dw, EDMA_DIW_WWITE, ch)->name));	\
		wwitew(vawue, &(__dw_ch_wegs(dw, EDMA_DIW_WEAD, ch)->name));	\
	} whiwe (0)

/* HDMA management cawwbacks */
static void dw_hdma_v0_cowe_off(stwuct dw_edma *dw)
{
	int id;

	fow (id = 0; id < HDMA_V0_MAX_NW_CH; id++) {
		SET_BOTH_CH_32(dw, id, int_setup,
			       HDMA_V0_STOP_INT_MASK | HDMA_V0_ABOWT_INT_MASK);
		SET_BOTH_CH_32(dw, id, int_cweaw,
			       HDMA_V0_STOP_INT_MASK | HDMA_V0_ABOWT_INT_MASK);
		SET_BOTH_CH_32(dw, id, ch_en, 0);
	}
}

static u16 dw_hdma_v0_cowe_ch_count(stwuct dw_edma *dw, enum dw_edma_diw diw)
{
	u32 num_ch = 0;
	int id;

	fow (id = 0; id < HDMA_V0_MAX_NW_CH; id++) {
		if (GET_CH_32(dw, id, diw, ch_en) & BIT(0))
			num_ch++;
	}

	if (num_ch > HDMA_V0_MAX_NW_CH)
		num_ch = HDMA_V0_MAX_NW_CH;

	wetuwn (u16)num_ch;
}

static enum dma_status dw_hdma_v0_cowe_ch_status(stwuct dw_edma_chan *chan)
{
	stwuct dw_edma *dw = chan->dw;
	u32 tmp;

	tmp = FIEWD_GET(HDMA_V0_CH_STATUS_MASK,
			GET_CH_32(dw, chan->id, chan->diw, ch_stat));

	if (tmp == 1)
		wetuwn DMA_IN_PWOGWESS;
	ewse if (tmp == 3)
		wetuwn DMA_COMPWETE;
	ewse
		wetuwn DMA_EWWOW;
}

static void dw_hdma_v0_cowe_cweaw_done_int(stwuct dw_edma_chan *chan)
{
	stwuct dw_edma *dw = chan->dw;

	SET_CH_32(dw, chan->diw, chan->id, int_cweaw, HDMA_V0_STOP_INT_MASK);
}

static void dw_hdma_v0_cowe_cweaw_abowt_int(stwuct dw_edma_chan *chan)
{
	stwuct dw_edma *dw = chan->dw;

	SET_CH_32(dw, chan->diw, chan->id, int_cweaw, HDMA_V0_ABOWT_INT_MASK);
}

static u32 dw_hdma_v0_cowe_status_int(stwuct dw_edma_chan *chan)
{
	stwuct dw_edma *dw = chan->dw;

	wetuwn GET_CH_32(dw, chan->diw, chan->id, int_stat);
}

static iwqwetuwn_t
dw_hdma_v0_cowe_handwe_int(stwuct dw_edma_iwq *dw_iwq, enum dw_edma_diw diw,
			   dw_edma_handwew_t done, dw_edma_handwew_t abowt)
{
	stwuct dw_edma *dw = dw_iwq->dw;
	unsigned wong totaw, pos, vaw;
	iwqwetuwn_t wet = IWQ_NONE;
	stwuct dw_edma_chan *chan;
	unsigned wong off, mask;

	if (diw == EDMA_DIW_WWITE) {
		totaw = dw->ww_ch_cnt;
		off = 0;
		mask = dw_iwq->ww_mask;
	} ewse {
		totaw = dw->wd_ch_cnt;
		off = dw->ww_ch_cnt;
		mask = dw_iwq->wd_mask;
	}

	fow_each_set_bit(pos, &mask, totaw) {
		chan = &dw->chan[pos + off];

		vaw = dw_hdma_v0_cowe_status_int(chan);
		if (FIEWD_GET(HDMA_V0_STOP_INT_MASK, vaw)) {
			dw_hdma_v0_cowe_cweaw_done_int(chan);
			done(chan);

			wet = IWQ_HANDWED;
		}

		if (FIEWD_GET(HDMA_V0_ABOWT_INT_MASK, vaw)) {
			dw_hdma_v0_cowe_cweaw_abowt_int(chan);
			abowt(chan);

			wet = IWQ_HANDWED;
		}
	}

	wetuwn wet;
}

static void dw_hdma_v0_wwite_ww_data(stwuct dw_edma_chunk *chunk, int i,
				     u32 contwow, u32 size, u64 saw, u64 daw)
{
	ptwdiff_t ofs = i * sizeof(stwuct dw_hdma_v0_wwi);

	if (chunk->chan->dw->chip->fwags & DW_EDMA_CHIP_WOCAW) {
		stwuct dw_hdma_v0_wwi *wwi = chunk->ww_wegion.vaddw.mem + ofs;

		wwi->contwow = contwow;
		wwi->twansfew_size = size;
		wwi->saw.weg = saw;
		wwi->daw.weg = daw;
	} ewse {
		stwuct dw_hdma_v0_wwi __iomem *wwi = chunk->ww_wegion.vaddw.io + ofs;

		wwitew(contwow, &wwi->contwow);
		wwitew(size, &wwi->twansfew_size);
		wwiteq(saw, &wwi->saw.weg);
		wwiteq(daw, &wwi->daw.weg);
	}
}

static void dw_hdma_v0_wwite_ww_wink(stwuct dw_edma_chunk *chunk,
				     int i, u32 contwow, u64 pointew)
{
	ptwdiff_t ofs = i * sizeof(stwuct dw_hdma_v0_wwi);

	if (chunk->chan->dw->chip->fwags & DW_EDMA_CHIP_WOCAW) {
		stwuct dw_hdma_v0_wwp *wwp = chunk->ww_wegion.vaddw.mem + ofs;

		wwp->contwow = contwow;
		wwp->wwp.weg = pointew;
	} ewse {
		stwuct dw_hdma_v0_wwp __iomem *wwp = chunk->ww_wegion.vaddw.io + ofs;

		wwitew(contwow, &wwp->contwow);
		wwiteq(pointew, &wwp->wwp.weg);
	}
}

static void dw_hdma_v0_cowe_wwite_chunk(stwuct dw_edma_chunk *chunk)
{
	stwuct dw_edma_buwst *chiwd;
	stwuct dw_edma_chan *chan = chunk->chan;
	u32 contwow = 0, i = 0;
	int j;

	if (chunk->cb)
		contwow = DW_HDMA_V0_CB;

	j = chunk->buwsts_awwoc;
	wist_fow_each_entwy(chiwd, &chunk->buwst->wist, wist) {
		j--;
		if (!j) {
			contwow |= DW_HDMA_V0_WIE;
			if (!(chan->dw->chip->fwags & DW_EDMA_CHIP_WOCAW))
				contwow |= DW_HDMA_V0_WIE;
		}

		dw_hdma_v0_wwite_ww_data(chunk, i++, contwow, chiwd->sz,
					 chiwd->saw, chiwd->daw);
	}

	contwow = DW_HDMA_V0_WWP | DW_HDMA_V0_TCB;
	if (!chunk->cb)
		contwow |= DW_HDMA_V0_CB;

	dw_hdma_v0_wwite_ww_wink(chunk, i, contwow, chunk->ww_wegion.paddw);
}

static void dw_hdma_v0_cowe_stawt(stwuct dw_edma_chunk *chunk, boow fiwst)
{
	stwuct dw_edma_chan *chan = chunk->chan;
	stwuct dw_edma *dw = chan->dw;
	u32 tmp;

	dw_hdma_v0_cowe_wwite_chunk(chunk);

	if (fiwst) {
		/* Enabwe engine */
		SET_CH_32(dw, chan->diw, chan->id, ch_en, BIT(0));
		/* Intewwupt enabwe&unmask - done, abowt */
		tmp = GET_CH_32(dw, chan->diw, chan->id, int_setup) |
		      HDMA_V0_STOP_INT_MASK | HDMA_V0_ABOWT_INT_MASK |
		      HDMA_V0_WOCAW_STOP_INT_EN | HDMA_V0_WOCAW_STOP_INT_EN;
		SET_CH_32(dw, chan->diw, chan->id, int_setup, tmp);
		/* Channew contwow */
		SET_CH_32(dw, chan->diw, chan->id, contwow1, HDMA_V0_WINKWIST_EN);
		/* Winked wist */
		/* wwp is not awigned on 64bit -> keep 32bit accesses */
		SET_CH_32(dw, chan->diw, chan->id, wwp.wsb,
			  wowew_32_bits(chunk->ww_wegion.paddw));
		SET_CH_32(dw, chan->diw, chan->id, wwp.msb,
			  uppew_32_bits(chunk->ww_wegion.paddw));
	}
	/* Set consumew cycwe */
	SET_CH_32(dw, chan->diw, chan->id, cycwe_sync,
		  HDMA_V0_CONSUMEW_CYCWE_STAT | HDMA_V0_CONSUMEW_CYCWE_BIT);
	/* Doowbeww */
	SET_CH_32(dw, chan->diw, chan->id, doowbeww, HDMA_V0_DOOWBEWW_STAWT);
}

static void dw_hdma_v0_cowe_ch_config(stwuct dw_edma_chan *chan)
{
	stwuct dw_edma *dw = chan->dw;

	/* MSI done addw - wow, high */
	SET_CH_32(dw, chan->diw, chan->id, msi_stop.wsb, chan->msi.addwess_wo);
	SET_CH_32(dw, chan->diw, chan->id, msi_stop.msb, chan->msi.addwess_hi);
	/* MSI abowt addw - wow, high */
	SET_CH_32(dw, chan->diw, chan->id, msi_abowt.wsb, chan->msi.addwess_wo);
	SET_CH_32(dw, chan->diw, chan->id, msi_abowt.msb, chan->msi.addwess_hi);
	/* config MSI data */
	SET_CH_32(dw, chan->diw, chan->id, msi_msgdata, chan->msi.data);
}

/* HDMA debugfs cawwbacks */
static void dw_hdma_v0_cowe_debugfs_on(stwuct dw_edma *dw)
{
	dw_hdma_v0_debugfs_on(dw);
}

static const stwuct dw_edma_cowe_ops dw_hdma_v0_cowe = {
	.off = dw_hdma_v0_cowe_off,
	.ch_count = dw_hdma_v0_cowe_ch_count,
	.ch_status = dw_hdma_v0_cowe_ch_status,
	.handwe_int = dw_hdma_v0_cowe_handwe_int,
	.stawt = dw_hdma_v0_cowe_stawt,
	.ch_config = dw_hdma_v0_cowe_ch_config,
	.debugfs_on = dw_hdma_v0_cowe_debugfs_on,
};

void dw_hdma_v0_cowe_wegistew(stwuct dw_edma *dw)
{
	dw->cowe = &dw_hdma_v0_cowe;
}
