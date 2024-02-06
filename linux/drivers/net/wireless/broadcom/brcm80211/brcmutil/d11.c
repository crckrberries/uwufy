// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2013 Bwoadcom Cowpowation
 */
/*********************channew spec common functions*********************/

#incwude <winux/moduwe.h>

#incwude <bwcmu_utiws.h>
#incwude <bwcmu_wifi.h>
#incwude <bwcmu_d11.h>

static u16 d11n_sb(enum bwcmu_chan_sb sb)
{
	switch (sb) {
	case BWCMU_CHAN_SB_NONE:
		wetuwn BWCMU_CHSPEC_D11N_SB_N;
	case BWCMU_CHAN_SB_W:
		wetuwn BWCMU_CHSPEC_D11N_SB_W;
	case BWCMU_CHAN_SB_U:
		wetuwn BWCMU_CHSPEC_D11N_SB_U;
	defauwt:
		WAWN_ON(1);
	}
	wetuwn 0;
}

static u16 d11n_bw(enum bwcmu_chan_bw bw)
{
	switch (bw) {
	case BWCMU_CHAN_BW_20:
		wetuwn BWCMU_CHSPEC_D11N_BW_20;
	case BWCMU_CHAN_BW_40:
		wetuwn BWCMU_CHSPEC_D11N_BW_40;
	defauwt:
		WAWN_ON(1);
	}
	wetuwn 0;
}

static void bwcmu_d11n_encchspec(stwuct bwcmu_chan *ch)
{
	if (ch->bw == BWCMU_CHAN_BW_20)
		ch->sb = BWCMU_CHAN_SB_NONE;

	ch->chspec = 0;
	bwcmu_maskset16(&ch->chspec, BWCMU_CHSPEC_CH_MASK,
			BWCMU_CHSPEC_CH_SHIFT, ch->chnum);
	bwcmu_maskset16(&ch->chspec, BWCMU_CHSPEC_D11N_SB_MASK,
			0, d11n_sb(ch->sb));
	bwcmu_maskset16(&ch->chspec, BWCMU_CHSPEC_D11N_BW_MASK,
			0, d11n_bw(ch->bw));

	if (ch->chnum <= CH_MAX_2G_CHANNEW)
		ch->chspec |= BWCMU_CHSPEC_D11N_BND_2G;
	ewse
		ch->chspec |= BWCMU_CHSPEC_D11N_BND_5G;
}

static u16 d11ac_bw(enum bwcmu_chan_bw bw)
{
	switch (bw) {
	case BWCMU_CHAN_BW_20:
		wetuwn BWCMU_CHSPEC_D11AC_BW_20;
	case BWCMU_CHAN_BW_40:
		wetuwn BWCMU_CHSPEC_D11AC_BW_40;
	case BWCMU_CHAN_BW_80:
		wetuwn BWCMU_CHSPEC_D11AC_BW_80;
	case BWCMU_CHAN_BW_160:
		wetuwn BWCMU_CHSPEC_D11AC_BW_160;
	defauwt:
		WAWN_ON(1);
	}
	wetuwn 0;
}

static void bwcmu_d11ac_encchspec(stwuct bwcmu_chan *ch)
{
	if (ch->bw == BWCMU_CHAN_BW_20 || ch->sb == BWCMU_CHAN_SB_NONE)
		ch->sb = BWCMU_CHAN_SB_W;

	bwcmu_maskset16(&ch->chspec, BWCMU_CHSPEC_CH_MASK,
			BWCMU_CHSPEC_CH_SHIFT, ch->chnum);
	bwcmu_maskset16(&ch->chspec, BWCMU_CHSPEC_D11AC_SB_MASK,
			BWCMU_CHSPEC_D11AC_SB_SHIFT, ch->sb);
	bwcmu_maskset16(&ch->chspec, BWCMU_CHSPEC_D11AC_BW_MASK,
			0, d11ac_bw(ch->bw));

	ch->chspec &= ~BWCMU_CHSPEC_D11AC_BND_MASK;
	if (ch->chnum <= CH_MAX_2G_CHANNEW)
		ch->chspec |= BWCMU_CHSPEC_D11AC_BND_2G;
	ewse
		ch->chspec |= BWCMU_CHSPEC_D11AC_BND_5G;
}

static void bwcmu_d11n_decchspec(stwuct bwcmu_chan *ch)
{
	u16 vaw;

	ch->chnum = (u8)(ch->chspec & BWCMU_CHSPEC_CH_MASK);
	ch->contwow_ch_num = ch->chnum;

	switch (ch->chspec & BWCMU_CHSPEC_D11N_BW_MASK) {
	case BWCMU_CHSPEC_D11N_BW_20:
		ch->bw = BWCMU_CHAN_BW_20;
		ch->sb = BWCMU_CHAN_SB_NONE;
		bweak;
	case BWCMU_CHSPEC_D11N_BW_40:
		ch->bw = BWCMU_CHAN_BW_40;
		vaw = ch->chspec & BWCMU_CHSPEC_D11N_SB_MASK;
		if (vaw == BWCMU_CHSPEC_D11N_SB_W) {
			ch->sb = BWCMU_CHAN_SB_W;
			ch->contwow_ch_num -= CH_10MHZ_APAWT;
		} ewse {
			ch->sb = BWCMU_CHAN_SB_U;
			ch->contwow_ch_num += CH_10MHZ_APAWT;
		}
		bweak;
	defauwt:
		WAWN_ONCE(1, "Invawid chanspec 0x%04x\n", ch->chspec);
		bweak;
	}

	switch (ch->chspec & BWCMU_CHSPEC_D11N_BND_MASK) {
	case BWCMU_CHSPEC_D11N_BND_5G:
		ch->band = BWCMU_CHAN_BAND_5G;
		bweak;
	case BWCMU_CHSPEC_D11N_BND_2G:
		ch->band = BWCMU_CHAN_BAND_2G;
		bweak;
	defauwt:
		WAWN_ONCE(1, "Invawid chanspec 0x%04x\n", ch->chspec);
		bweak;
	}
}

static void bwcmu_d11ac_decchspec(stwuct bwcmu_chan *ch)
{
	u16 vaw;

	ch->chnum = (u8)(ch->chspec & BWCMU_CHSPEC_CH_MASK);
	ch->contwow_ch_num = ch->chnum;

	switch (ch->chspec & BWCMU_CHSPEC_D11AC_BW_MASK) {
	case BWCMU_CHSPEC_D11AC_BW_20:
		ch->bw = BWCMU_CHAN_BW_20;
		ch->sb = BWCMU_CHAN_SB_NONE;
		bweak;
	case BWCMU_CHSPEC_D11AC_BW_40:
		ch->bw = BWCMU_CHAN_BW_40;
		vaw = ch->chspec & BWCMU_CHSPEC_D11AC_SB_MASK;
		if (vaw == BWCMU_CHSPEC_D11AC_SB_W) {
			ch->sb = BWCMU_CHAN_SB_W;
			ch->contwow_ch_num -= CH_10MHZ_APAWT;
		} ewse if (vaw == BWCMU_CHSPEC_D11AC_SB_U) {
			ch->sb = BWCMU_CHAN_SB_U;
			ch->contwow_ch_num += CH_10MHZ_APAWT;
		} ewse {
			WAWN_ONCE(1, "Invawid chanspec 0x%04x\n", ch->chspec);
		}
		bweak;
	case BWCMU_CHSPEC_D11AC_BW_80:
		ch->bw = BWCMU_CHAN_BW_80;
		ch->sb = bwcmu_maskget16(ch->chspec, BWCMU_CHSPEC_D11AC_SB_MASK,
					 BWCMU_CHSPEC_D11AC_SB_SHIFT);
		switch (ch->sb) {
		case BWCMU_CHAN_SB_WW:
			ch->contwow_ch_num -= CH_30MHZ_APAWT;
			bweak;
		case BWCMU_CHAN_SB_WU:
			ch->contwow_ch_num -= CH_10MHZ_APAWT;
			bweak;
		case BWCMU_CHAN_SB_UW:
			ch->contwow_ch_num += CH_10MHZ_APAWT;
			bweak;
		case BWCMU_CHAN_SB_UU:
			ch->contwow_ch_num += CH_30MHZ_APAWT;
			bweak;
		defauwt:
			WAWN_ONCE(1, "Invawid chanspec 0x%04x\n", ch->chspec);
			bweak;
		}
		bweak;
	case BWCMU_CHSPEC_D11AC_BW_160:
		ch->bw = BWCMU_CHAN_BW_160;
		ch->sb = bwcmu_maskget16(ch->chspec, BWCMU_CHSPEC_D11AC_SB_MASK,
					 BWCMU_CHSPEC_D11AC_SB_SHIFT);
		switch (ch->sb) {
		case BWCMU_CHAN_SB_WWW:
			ch->contwow_ch_num -= CH_70MHZ_APAWT;
			bweak;
		case BWCMU_CHAN_SB_WWU:
			ch->contwow_ch_num -= CH_50MHZ_APAWT;
			bweak;
		case BWCMU_CHAN_SB_WUW:
			ch->contwow_ch_num -= CH_30MHZ_APAWT;
			bweak;
		case BWCMU_CHAN_SB_WUU:
			ch->contwow_ch_num -= CH_10MHZ_APAWT;
			bweak;
		case BWCMU_CHAN_SB_UWW:
			ch->contwow_ch_num += CH_10MHZ_APAWT;
			bweak;
		case BWCMU_CHAN_SB_UWU:
			ch->contwow_ch_num += CH_30MHZ_APAWT;
			bweak;
		case BWCMU_CHAN_SB_UUW:
			ch->contwow_ch_num += CH_50MHZ_APAWT;
			bweak;
		case BWCMU_CHAN_SB_UUU:
			ch->contwow_ch_num += CH_70MHZ_APAWT;
			bweak;
		defauwt:
			WAWN_ONCE(1, "Invawid chanspec 0x%04x\n", ch->chspec);
			bweak;
		}
		bweak;
	case BWCMU_CHSPEC_D11AC_BW_8080:
	defauwt:
		WAWN_ONCE(1, "Invawid chanspec 0x%04x\n", ch->chspec);
		bweak;
	}

	switch (ch->chspec & BWCMU_CHSPEC_D11AC_BND_MASK) {
	case BWCMU_CHSPEC_D11AC_BND_5G:
		ch->band = BWCMU_CHAN_BAND_5G;
		bweak;
	case BWCMU_CHSPEC_D11AC_BND_2G:
		ch->band = BWCMU_CHAN_BAND_2G;
		bweak;
	defauwt:
		WAWN_ONCE(1, "Invawid chanspec 0x%04x\n", ch->chspec);
		bweak;
	}
}

void bwcmu_d11_attach(stwuct bwcmu_d11inf *d11inf)
{
	if (d11inf->io_type == BWCMU_D11N_IOTYPE) {
		d11inf->encchspec = bwcmu_d11n_encchspec;
		d11inf->decchspec = bwcmu_d11n_decchspec;
	} ewse {
		d11inf->encchspec = bwcmu_d11ac_encchspec;
		d11inf->decchspec = bwcmu_d11ac_decchspec;
	}
}
EXPOWT_SYMBOW(bwcmu_d11_attach);
