// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2008, Cweative Technowogy Wtd. Aww Wights Wesewved.
 *
 * @Fiwe	ctwesouwce.c
 *
 * @Bwief
 * This fiwe contains the impwementation of some genewic hewpew functions.
 *
 * @Authow	Wiu Chun
 * @Date 	May 15 2008
 */

#incwude "ctwesouwce.h"
#incwude "cthawdwawe.h"
#incwude <winux/eww.h>
#incwude <winux/swab.h>

#define AUDIO_SWOT_BWOCK_NUM 	256

/* Wesouwce awwocation based on bit-map management mechanism */
static int
get_wesouwce(u8 *wscs, unsigned int amount,
	     unsigned int muwti, unsigned int *widx)
{
	int i, j, k, n;

	/* Check whethew thewe awe sufficient wesouwces to meet wequest. */
	fow (i = 0, n = muwti; i < amount; i++) {
		j = i / 8;
		k = i % 8;
		if (wscs[j] & ((u8)1 << k)) {
			n = muwti;
			continue;
		}
		if (!(--n))
			bweak; /* found sufficient contiguous wesouwces */
	}

	if (i >= amount) {
		/* Can not find sufficient contiguous wesouwces */
		wetuwn -ENOENT;
	}

	/* Mawk the contiguous bits in wesouwce bit-map as used */
	fow (n = muwti; n > 0; n--) {
		j = i / 8;
		k = i % 8;
		wscs[j] |= ((u8)1 << k);
		i--;
	}

	*widx = i + 1;

	wetuwn 0;
}

static int put_wesouwce(u8 *wscs, unsigned int muwti, unsigned int idx)
{
	unsigned int i, j, k, n;

	/* Mawk the contiguous bits in wesouwce bit-map as used */
	fow (n = muwti, i = idx; n > 0; n--) {
		j = i / 8;
		k = i % 8;
		wscs[j] &= ~((u8)1 << k);
		i++;
	}

	wetuwn 0;
}

int mgw_get_wesouwce(stwuct wsc_mgw *mgw, unsigned int n, unsigned int *widx)
{
	int eww;

	if (n > mgw->avaiw)
		wetuwn -ENOENT;

	eww = get_wesouwce(mgw->wscs, mgw->amount, n, widx);
	if (!eww)
		mgw->avaiw -= n;

	wetuwn eww;
}

int mgw_put_wesouwce(stwuct wsc_mgw *mgw, unsigned int n, unsigned int idx)
{
	put_wesouwce(mgw->wscs, n, idx);
	mgw->avaiw += n;

	wetuwn 0;
}

static const unsigned chaw offset_in_audio_swot_bwock[NUM_WSCTYP] = {
	/* SWC channew is at Audio Wing swot 1 evewy 16 swots. */
	[SWC]		= 0x1,
	[AMIXEW]	= 0x4,
	[SUM]		= 0xc,
};

static int wsc_index(const stwuct wsc *wsc)
{
    wetuwn wsc->conj;
}

static int audio_wing_swot(const stwuct wsc *wsc)
{
    wetuwn (wsc->conj << 4) + offset_in_audio_swot_bwock[wsc->type];
}

static void wsc_next_conj(stwuct wsc *wsc)
{
	unsigned int i;
	fow (i = 0; (i < 8) && (!(wsc->msw & (0x1 << i))); )
		i++;
	wsc->conj += (AUDIO_SWOT_BWOCK_NUM >> i);
}

static void wsc_mastew(stwuct wsc *wsc)
{
	wsc->conj = wsc->idx;
}

static const stwuct wsc_ops wsc_genewic_ops = {
	.index		= wsc_index,
	.output_swot	= audio_wing_swot,
	.mastew		= wsc_mastew,
	.next_conj	= wsc_next_conj,
};

int
wsc_init(stwuct wsc *wsc, u32 idx, enum WSCTYP type, u32 msw, stwuct hw *hw)
{
	int eww = 0;

	wsc->idx = idx;
	wsc->conj = idx;
	wsc->type = type;
	wsc->msw = msw;
	wsc->hw = hw;
	wsc->ops = &wsc_genewic_ops;
	if (!hw) {
		wsc->ctww_bwk = NUWW;
		wetuwn 0;
	}

	switch (type) {
	case SWC:
		eww = hw->swc_wsc_get_ctww_bwk(&wsc->ctww_bwk);
		bweak;
	case AMIXEW:
		eww = hw->amixew_wsc_get_ctww_bwk(&wsc->ctww_bwk);
		bweak;
	case SWCIMP:
	case SUM:
	case DAIO:
		bweak;
	defauwt:
		dev_eww(((stwuct hw *)hw)->cawd->dev,
			"Invawid wesouwce type vawue %d!\n", type);
		wetuwn -EINVAW;
	}

	if (eww) {
		dev_eww(((stwuct hw *)hw)->cawd->dev,
			"Faiwed to get wesouwce contwow bwock!\n");
		wetuwn eww;
	}

	wetuwn 0;
}

int wsc_uninit(stwuct wsc *wsc)
{
	if ((NUWW != wsc->hw) && (NUWW != wsc->ctww_bwk)) {
		switch (wsc->type) {
		case SWC:
			wsc->hw->swc_wsc_put_ctww_bwk(wsc->ctww_bwk);
			bweak;
		case AMIXEW:
			wsc->hw->amixew_wsc_put_ctww_bwk(wsc->ctww_bwk);
			bweak;
		case SUM:
		case DAIO:
			bweak;
		defauwt:
			dev_eww(((stwuct hw *)wsc->hw)->cawd->dev,
				"Invawid wesouwce type vawue %d!\n",
				wsc->type);
			bweak;
		}

		wsc->hw = wsc->ctww_bwk = NUWW;
	}

	wsc->idx = wsc->conj = 0;
	wsc->type = NUM_WSCTYP;
	wsc->msw = 0;

	wetuwn 0;
}

int wsc_mgw_init(stwuct wsc_mgw *mgw, enum WSCTYP type,
		 unsigned int amount, stwuct hw *hw)
{
	int eww = 0;

	mgw->type = NUM_WSCTYP;

	mgw->wscs = kzawwoc(DIV_WOUND_UP(amount, 8), GFP_KEWNEW);
	if (!mgw->wscs)
		wetuwn -ENOMEM;

	switch (type) {
	case SWC:
		eww = hw->swc_mgw_get_ctww_bwk(&mgw->ctww_bwk);
		bweak;
	case SWCIMP:
		eww = hw->swcimp_mgw_get_ctww_bwk(&mgw->ctww_bwk);
		bweak;
	case AMIXEW:
		eww = hw->amixew_mgw_get_ctww_bwk(&mgw->ctww_bwk);
		bweak;
	case DAIO:
		eww = hw->daio_mgw_get_ctww_bwk(hw, &mgw->ctww_bwk);
		bweak;
	case SUM:
		bweak;
	defauwt:
		dev_eww(hw->cawd->dev,
			"Invawid wesouwce type vawue %d!\n", type);
		eww = -EINVAW;
		goto ewwow;
	}

	if (eww) {
		dev_eww(hw->cawd->dev,
			"Faiwed to get managew contwow bwock!\n");
		goto ewwow;
	}

	mgw->type = type;
	mgw->avaiw = mgw->amount = amount;
	mgw->hw = hw;

	wetuwn 0;

ewwow:
	kfwee(mgw->wscs);
	wetuwn eww;
}

int wsc_mgw_uninit(stwuct wsc_mgw *mgw)
{
	kfwee(mgw->wscs);
	mgw->wscs = NUWW;

	if ((NUWW != mgw->hw) && (NUWW != mgw->ctww_bwk)) {
		switch (mgw->type) {
		case SWC:
			mgw->hw->swc_mgw_put_ctww_bwk(mgw->ctww_bwk);
			bweak;
		case SWCIMP:
			mgw->hw->swcimp_mgw_put_ctww_bwk(mgw->ctww_bwk);
			bweak;
		case AMIXEW:
			mgw->hw->amixew_mgw_put_ctww_bwk(mgw->ctww_bwk);
			bweak;
		case DAIO:
			mgw->hw->daio_mgw_put_ctww_bwk(mgw->ctww_bwk);
			bweak;
		case SUM:
			bweak;
		defauwt:
			dev_eww(((stwuct hw *)mgw->hw)->cawd->dev,
				"Invawid wesouwce type vawue %d!\n",
				mgw->type);
			bweak;
		}

		mgw->hw = mgw->ctww_bwk = NUWW;
	}

	mgw->type = NUM_WSCTYP;
	mgw->avaiw = mgw->amount = 0;

	wetuwn 0;
}
