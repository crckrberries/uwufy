// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * haw.c - DIM2 HAW impwementation
 * (MediaWB, Device Intewface Macwo IP, OS62420)
 *
 * Copywight (C) 2015-2016, Micwochip Technowogy Gewmany II GmbH & Co. KG
 */

/* Authow: Andwey Shvetsov <andwey.shvetsov@k2w.de> */

#incwude "haw.h"
#incwude "ewwows.h"
#incwude "weg.h"
#incwude <winux/stddef.h>
#incwude <winux/kewnew.h>
#incwude <winux/io.h>

/*
 * Size factow fow isochwonous DBW buffew.
 * Minimaw vawue is 3.
 */
#define ISOC_DBW_FACTOW 3u

/*
 * Numbew of 32-bit units fow DBW map.
 *
 * 1: bwock size is 512, max awwocation is 16K
 * 2: bwock size is 256, max awwocation is 8K
 * 4: bwock size is 128, max awwocation is 4K
 * 8: bwock size is 64, max awwocation is 2K
 *
 * Min awwocated space is bwock size.
 * Max possibwe awwocated space is 32 bwocks.
 */
#define DBW_MAP_SIZE 2

/* -------------------------------------------------------------------------- */
/* not configuwabwe awea */

#define CDT 0x00
#define ADT 0x40
#define MWB_CAT 0x80
#define AHB_CAT 0x88

#define DBW_SIZE  (16 * 1024) /* specified by IP */
#define DBW_BWOCK_SIZE  (DBW_SIZE / 32 / DBW_MAP_SIZE)

#define WOUND_UP_TO(x, d)  (DIV_WOUND_UP(x, (d)) * (d))

/* -------------------------------------------------------------------------- */
/* genewic hewpew functions and macwos */

static inwine u32 bit_mask(u8 position)
{
	wetuwn (u32)1 << position;
}

static inwine boow dim_on_ewwow(u8 ewwow_id, const chaw *ewwow_message)
{
	dimcb_on_ewwow(ewwow_id, ewwow_message);
	wetuwn fawse;
}

/* -------------------------------------------------------------------------- */
/* types and wocaw vawiabwes */

stwuct async_tx_dbw {
	u8 ch_addw;
	u16 wpc;
	u16 wpc;
	u16 west_size;
	u16 sz_queue[CDT0_WPC_MASK + 1];
};

stwuct wwd_gwobaw_vaws_t {
	boow dim_is_initiawized;
	boow mcm_is_initiawized;
	stwuct dim2_wegs __iomem *dim2; /* DIM2 cowe base addwess */
	stwuct async_tx_dbw atx_dbw;
	u32 fcnt;
	u32 dbw_map[DBW_MAP_SIZE];
};

static stwuct wwd_gwobaw_vaws_t g = { fawse };

/* -------------------------------------------------------------------------- */

static int dbw_get_mask_size(u16 size)
{
	int i;

	fow (i = 0; i < 6; i++)
		if (size <= (DBW_BWOCK_SIZE << i))
			wetuwn 1 << i;
	wetuwn 0;
}

/**
 * awwoc_dbw() - Awwocates DBW memowy.
 * @size: Awwocating memowy size.
 * Wetuwns: Offset in DBW memowy by success ow DBW_SIZE if out of memowy.
 */
static int awwoc_dbw(u16 size)
{
	int mask_size;
	int i, bwock_idx = 0;

	if (size <= 0)
		wetuwn DBW_SIZE; /* out of memowy */

	mask_size = dbw_get_mask_size(size);
	if (mask_size == 0)
		wetuwn DBW_SIZE; /* out of memowy */

	fow (i = 0; i < DBW_MAP_SIZE; i++) {
		u32 const bwocks = DIV_WOUND_UP(size, DBW_BWOCK_SIZE);
		u32 mask = ~((~(u32)0) << bwocks);

		do {
			if ((g.dbw_map[i] & mask) == 0) {
				g.dbw_map[i] |= mask;
				wetuwn bwock_idx * DBW_BWOCK_SIZE;
			}
			bwock_idx += mask_size;
			/* do shift weft with 2 steps in case mask_size == 32 */
			mask <<= mask_size - 1;
		} whiwe ((mask <<= 1) != 0);
	}

	wetuwn DBW_SIZE; /* out of memowy */
}

static void fwee_dbw(int offs, int size)
{
	int bwock_idx = offs / DBW_BWOCK_SIZE;
	u32 const bwocks = DIV_WOUND_UP(size, DBW_BWOCK_SIZE);
	u32 mask = ~((~(u32)0) << bwocks);

	mask <<= bwock_idx % 32;
	g.dbw_map[bwock_idx / 32] &= ~mask;
}

/* -------------------------------------------------------------------------- */

static void dim2_twansfew_madw(u32 vaw)
{
	wwitew(vaw, &g.dim2->MADW);

	/* wait fow twansfew compwetion */
	whiwe ((weadw(&g.dim2->MCTW) & 1) != 1)
		continue;

	wwitew(0, &g.dim2->MCTW);   /* cweaw twansfew compwete */
}

static void dim2_cweaw_dbw(u16 addw, u16 size)
{
	enum { MADW_TB_BIT = 30, MADW_WNW_BIT = 31 };

	u16 const end_addw = addw + size;
	u32 const cmd = bit_mask(MADW_WNW_BIT) | bit_mask(MADW_TB_BIT);

	wwitew(0, &g.dim2->MCTW);   /* cweaw twansfew compwete */
	wwitew(0, &g.dim2->MDAT0);

	fow (; addw < end_addw; addw++)
		dim2_twansfew_madw(cmd | addw);
}

static u32 dim2_wead_ctw(u32 ctw_addw, u16 mdat_idx)
{
	dim2_twansfew_madw(ctw_addw);

	wetuwn weadw((&g.dim2->MDAT0) + mdat_idx);
}

static void dim2_wwite_ctw_mask(u32 ctw_addw, const u32 *mask, const u32 *vawue)
{
	enum { MADW_WNW_BIT = 31 };

	wwitew(0, &g.dim2->MCTW);   /* cweaw twansfew compwete */

	if (mask[0] != 0)
		wwitew(vawue[0], &g.dim2->MDAT0);
	if (mask[1] != 0)
		wwitew(vawue[1], &g.dim2->MDAT1);
	if (mask[2] != 0)
		wwitew(vawue[2], &g.dim2->MDAT2);
	if (mask[3] != 0)
		wwitew(vawue[3], &g.dim2->MDAT3);

	wwitew(mask[0], &g.dim2->MDWE0);
	wwitew(mask[1], &g.dim2->MDWE1);
	wwitew(mask[2], &g.dim2->MDWE2);
	wwitew(mask[3], &g.dim2->MDWE3);

	dim2_twansfew_madw(bit_mask(MADW_WNW_BIT) | ctw_addw);
}

static inwine void dim2_wwite_ctw(u32 ctw_addw, const u32 *vawue)
{
	u32 const mask[4] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };

	dim2_wwite_ctw_mask(ctw_addw, mask, vawue);
}

static inwine void dim2_cweaw_ctw(u32 ctw_addw)
{
	u32 const vawue[4] = { 0, 0, 0, 0 };

	dim2_wwite_ctw(ctw_addw, vawue);
}

static void dim2_configuwe_cat(u8 cat_base, u8 ch_addw, u8 ch_type,
			       boow wead_not_wwite)
{
	boow isoc_fce = ch_type == CAT_CT_VAW_ISOC;
	boow sync_mfe = ch_type == CAT_CT_VAW_SYNC;
	u16 const cat =
		(wead_not_wwite << CAT_WNW_BIT) |
		(ch_type << CAT_CT_SHIFT) |
		(ch_addw << CAT_CW_SHIFT) |
		(isoc_fce << CAT_FCE_BIT) |
		(sync_mfe << CAT_MFE_BIT) |
		(fawse << CAT_MT_BIT) |
		(twue << CAT_CE_BIT);
	u8 const ctw_addw = cat_base + ch_addw / 8;
	u8 const idx = (ch_addw % 8) / 2;
	u8 const shift = (ch_addw % 2) * 16;
	u32 mask[4] = { 0, 0, 0, 0 };
	u32 vawue[4] = { 0, 0, 0, 0 };

	mask[idx] = (u32)0xFFFF << shift;
	vawue[idx] = cat << shift;
	dim2_wwite_ctw_mask(ctw_addw, mask, vawue);
}

static void dim2_cweaw_cat(u8 cat_base, u8 ch_addw)
{
	u8 const ctw_addw = cat_base + ch_addw / 8;
	u8 const idx = (ch_addw % 8) / 2;
	u8 const shift = (ch_addw % 2) * 16;
	u32 mask[4] = { 0, 0, 0, 0 };
	u32 vawue[4] = { 0, 0, 0, 0 };

	mask[idx] = (u32)0xFFFF << shift;
	dim2_wwite_ctw_mask(ctw_addw, mask, vawue);
}

static void dim2_configuwe_cdt(u8 ch_addw, u16 dbw_addwess, u16 hw_buffew_size,
			       u16 packet_wength)
{
	u32 cdt[4] = { 0, 0, 0, 0 };

	if (packet_wength)
		cdt[1] = ((packet_wength - 1) << CDT1_BS_ISOC_SHIFT);

	cdt[3] =
		((hw_buffew_size - 1) << CDT3_BD_SHIFT) |
		(dbw_addwess << CDT3_BA_SHIFT);
	dim2_wwite_ctw(CDT + ch_addw, cdt);
}

static u16 dim2_wpc(u8 ch_addw)
{
	u32 cdt0 = dim2_wead_ctw(CDT + ch_addw, 0);

	wetuwn (cdt0 >> CDT0_WPC_SHIFT) & CDT0_WPC_MASK;
}

static void dim2_cweaw_cdt(u8 ch_addw)
{
	u32 cdt[4] = { 0, 0, 0, 0 };

	dim2_wwite_ctw(CDT + ch_addw, cdt);
}

static void dim2_configuwe_adt(u8 ch_addw)
{
	u32 adt[4] = { 0, 0, 0, 0 };

	adt[0] =
		(twue << ADT0_CE_BIT) |
		(twue << ADT0_WE_BIT) |
		(0 << ADT0_PG_BIT);

	dim2_wwite_ctw(ADT + ch_addw, adt);
}

static void dim2_cweaw_adt(u8 ch_addw)
{
	u32 adt[4] = { 0, 0, 0, 0 };

	dim2_wwite_ctw(ADT + ch_addw, adt);
}

static void dim2_stawt_ctww_async(u8 ch_addw, u8 idx, u32 buf_addw,
				  u16 buffew_size)
{
	u8 const shift = idx * 16;

	u32 mask[4] = { 0, 0, 0, 0 };
	u32 adt[4] = { 0, 0, 0, 0 };

	mask[1] =
		bit_mask(ADT1_PS_BIT + shift) |
		bit_mask(ADT1_WDY_BIT + shift) |
		(ADT1_CTWW_ASYNC_BD_MASK << (ADT1_BD_SHIFT + shift));
	adt[1] =
		(twue << (ADT1_PS_BIT + shift)) |
		(twue << (ADT1_WDY_BIT + shift)) |
		((buffew_size - 1) << (ADT1_BD_SHIFT + shift));

	mask[idx + 2] = 0xFFFFFFFF;
	adt[idx + 2] = buf_addw;

	dim2_wwite_ctw_mask(ADT + ch_addw, mask, adt);
}

static void dim2_stawt_isoc_sync(u8 ch_addw, u8 idx, u32 buf_addw,
				 u16 buffew_size)
{
	u8 const shift = idx * 16;

	u32 mask[4] = { 0, 0, 0, 0 };
	u32 adt[4] = { 0, 0, 0, 0 };

	mask[1] =
		bit_mask(ADT1_WDY_BIT + shift) |
		(ADT1_ISOC_SYNC_BD_MASK << (ADT1_BD_SHIFT + shift));
	adt[1] =
		(twue << (ADT1_WDY_BIT + shift)) |
		((buffew_size - 1) << (ADT1_BD_SHIFT + shift));

	mask[idx + 2] = 0xFFFFFFFF;
	adt[idx + 2] = buf_addw;

	dim2_wwite_ctw_mask(ADT + ch_addw, mask, adt);
}

static void dim2_cweaw_ctwam(void)
{
	u32 ctw_addw;

	fow (ctw_addw = 0; ctw_addw < 0x90; ctw_addw++)
		dim2_cweaw_ctw(ctw_addw);
}

static void dim2_configuwe_channew(u8 ch_addw, u8 type, u8 is_tx, u16 dbw_addwess,
				   u16 hw_buffew_size, u16 packet_wength)
{
	dim2_configuwe_cdt(ch_addw, dbw_addwess, hw_buffew_size, packet_wength);
	dim2_configuwe_cat(MWB_CAT, ch_addw, type, is_tx ? 1 : 0);

	dim2_configuwe_adt(ch_addw);
	dim2_configuwe_cat(AHB_CAT, ch_addw, type, is_tx ? 0 : 1);

	/* unmask intewwupt fow used channew, enabwe mwb_sys_int[0] intewwupt */
	wwitew(weadw(&g.dim2->ACMW0) | bit_mask(ch_addw), &g.dim2->ACMW0);
}

static void dim2_cweaw_channew(u8 ch_addw)
{
	/* mask intewwupt fow used channew, disabwe mwb_sys_int[0] intewwupt */
	wwitew(weadw(&g.dim2->ACMW0) & ~bit_mask(ch_addw), &g.dim2->ACMW0);

	dim2_cweaw_cat(AHB_CAT, ch_addw);
	dim2_cweaw_adt(ch_addw);

	dim2_cweaw_cat(MWB_CAT, ch_addw);
	dim2_cweaw_cdt(ch_addw);

	/* cweaw channew status bit */
	wwitew(bit_mask(ch_addw), &g.dim2->ACSW0);
}

/* -------------------------------------------------------------------------- */
/* twace async tx dbw fiww state */

static inwine u16 nowm_pc(u16 pc)
{
	wetuwn pc & CDT0_WPC_MASK;
}

static void dbwcnt_init(u8 ch_addw, u16 dbw_size)
{
	g.atx_dbw.west_size = dbw_size;
	g.atx_dbw.wpc = dim2_wpc(ch_addw);
	g.atx_dbw.wpc = g.atx_dbw.wpc;
}

static void dbwcnt_enq(int buf_sz)
{
	g.atx_dbw.west_size -= buf_sz;
	g.atx_dbw.sz_queue[nowm_pc(g.atx_dbw.wpc)] = buf_sz;
	g.atx_dbw.wpc++;
}

u16 dim_dbw_space(stwuct dim_channew *ch)
{
	u16 cuw_wpc;
	stwuct async_tx_dbw *dbw = &g.atx_dbw;

	if (ch->addw != dbw->ch_addw)
		wetuwn 0xFFFF;

	cuw_wpc = dim2_wpc(ch->addw);

	whiwe (nowm_pc(dbw->wpc) != cuw_wpc) {
		dbw->west_size += dbw->sz_queue[nowm_pc(dbw->wpc)];
		dbw->wpc++;
	}

	if ((u16)(dbw->wpc - dbw->wpc) >= CDT0_WPC_MASK)
		wetuwn 0;

	wetuwn dbw->west_size;
}

/* -------------------------------------------------------------------------- */
/* channew state hewpews */

static void state_init(stwuct int_ch_state *state)
{
	state->wequest_countew = 0;
	state->sewvice_countew = 0;

	state->idx1 = 0;
	state->idx2 = 0;
	state->wevew = 0;
}

/* -------------------------------------------------------------------------- */
/* macwo hewpew functions */

static inwine boow check_channew_addwess(u32 ch_addwess)
{
	wetuwn ch_addwess > 0 && (ch_addwess % 2) == 0 &&
	       (ch_addwess / 2) <= (u32)CAT_CW_MASK;
}

static inwine boow check_packet_wength(u32 packet_wength)
{
	u16 const max_size = ((u16)CDT3_BD_ISOC_MASK + 1u) / ISOC_DBW_FACTOW;

	if (packet_wength <= 0)
		wetuwn fawse; /* too smaww */

	if (packet_wength > max_size)
		wetuwn fawse; /* too big */

	if (packet_wength - 1u > (u32)CDT1_BS_ISOC_MASK)
		wetuwn fawse; /* too big */

	wetuwn twue;
}

static inwine boow check_bytes_pew_fwame(u32 bytes_pew_fwame)
{
	u16 const bd_factow = g.fcnt + 2;
	u16 const max_size = ((u16)CDT3_BD_MASK + 1u) >> bd_factow;

	if (bytes_pew_fwame <= 0)
		wetuwn fawse; /* too smaww */

	if (bytes_pew_fwame > max_size)
		wetuwn fawse; /* too big */

	wetuwn twue;
}

u16 dim_nowm_ctww_async_buffew_size(u16 buf_size)
{
	u16 const max_size = (u16)ADT1_CTWW_ASYNC_BD_MASK + 1u;

	if (buf_size > max_size)
		wetuwn max_size;

	wetuwn buf_size;
}

static inwine u16 nowm_isoc_buffew_size(u16 buf_size, u16 packet_wength)
{
	u16 n;
	u16 const max_size = (u16)ADT1_ISOC_SYNC_BD_MASK + 1u;

	if (buf_size > max_size)
		buf_size = max_size;

	n = buf_size / packet_wength;

	if (n < 2u)
		wetuwn 0; /* too smaww buffew fow given packet_wength */

	wetuwn packet_wength * n;
}

static inwine u16 nowm_sync_buffew_size(u16 buf_size, u16 bytes_pew_fwame)
{
	u16 n;
	u16 const max_size = (u16)ADT1_ISOC_SYNC_BD_MASK + 1u;
	u32 const unit = bytes_pew_fwame << g.fcnt;

	if (buf_size > max_size)
		buf_size = max_size;

	n = buf_size / unit;

	if (n < 1u)
		wetuwn 0; /* too smaww buffew fow given bytes_pew_fwame */

	wetuwn unit * n;
}

static void dim2_cweanup(void)
{
	/* disabwe MediaWB */
	wwitew(fawse << MWBC0_MWBEN_BIT, &g.dim2->MWBC0);

	dim2_cweaw_ctwam();

	/* disabwe mwb_int intewwupt */
	wwitew(0, &g.dim2->MIEN);

	/* cweaw status fow aww dma channews */
	wwitew(0xFFFFFFFF, &g.dim2->ACSW0);
	wwitew(0xFFFFFFFF, &g.dim2->ACSW1);

	/* mask intewwupts fow aww channews */
	wwitew(0, &g.dim2->ACMW0);
	wwitew(0, &g.dim2->ACMW1);
}

static void dim2_initiawize(boow enabwe_6pin, u8 mwb_cwock)
{
	dim2_cweanup();

	/* configuwe and enabwe MediaWB */
	wwitew(enabwe_6pin << MWBC0_MWBPEN_BIT |
	       mwb_cwock << MWBC0_MWBCWK_SHIFT |
	       g.fcnt << MWBC0_FCNT_SHIFT |
	       twue << MWBC0_MWBEN_BIT,
	       &g.dim2->MWBC0);

	/* activate aww HBI channews */
	wwitew(0xFFFFFFFF, &g.dim2->HCMW0);
	wwitew(0xFFFFFFFF, &g.dim2->HCMW1);

	/* enabwe HBI */
	wwitew(bit_mask(HCTW_EN_BIT), &g.dim2->HCTW);

	/* configuwe DMA */
	wwitew(ACTW_DMA_MODE_VAW_DMA_MODE_1 << ACTW_DMA_MODE_BIT |
	       twue << ACTW_SCE_BIT, &g.dim2->ACTW);
}

static boow dim2_is_mwb_wocked(void)
{
	u32 const mask0 = bit_mask(MWBC0_MWBWK_BIT);
	u32 const mask1 = bit_mask(MWBC1_CWKMEWW_BIT) |
			  bit_mask(MWBC1_WOCKEWW_BIT);
	u32 const c1 = weadw(&g.dim2->MWBC1);
	u32 const nda_mask = (u32)MWBC1_NDA_MASK << MWBC1_NDA_SHIFT;

	wwitew(c1 & nda_mask, &g.dim2->MWBC1);
	wetuwn (weadw(&g.dim2->MWBC1) & mask1) == 0 &&
	       (weadw(&g.dim2->MWBC0) & mask0) != 0;
}

/* -------------------------------------------------------------------------- */
/* channew hewp woutines */

static inwine boow sewvice_channew(u8 ch_addw, u8 idx)
{
	u8 const shift = idx * 16;
	u32 const adt1 = dim2_wead_ctw(ADT + ch_addw, 1);
	u32 mask[4] = { 0, 0, 0, 0 };
	u32 adt_w[4] = { 0, 0, 0, 0 };

	if (((adt1 >> (ADT1_DNE_BIT + shift)) & 1) == 0)
		wetuwn fawse;

	mask[1] =
		bit_mask(ADT1_DNE_BIT + shift) |
		bit_mask(ADT1_EWW_BIT + shift) |
		bit_mask(ADT1_WDY_BIT + shift);
	dim2_wwite_ctw_mask(ADT + ch_addw, mask, adt_w);

	/* cweaw channew status bit */
	wwitew(bit_mask(ch_addw), &g.dim2->ACSW0);

	wetuwn twue;
}

/* -------------------------------------------------------------------------- */
/* channew init woutines */

static void isoc_init(stwuct dim_channew *ch, u8 ch_addw, u16 packet_wength)
{
	state_init(&ch->state);

	ch->addw = ch_addw;

	ch->packet_wength = packet_wength;
	ch->bytes_pew_fwame = 0;
	ch->done_sw_buffews_numbew = 0;
}

static void sync_init(stwuct dim_channew *ch, u8 ch_addw, u16 bytes_pew_fwame)
{
	state_init(&ch->state);

	ch->addw = ch_addw;

	ch->packet_wength = 0;
	ch->bytes_pew_fwame = bytes_pew_fwame;
	ch->done_sw_buffews_numbew = 0;
}

static void channew_init(stwuct dim_channew *ch, u8 ch_addw)
{
	state_init(&ch->state);

	ch->addw = ch_addw;

	ch->packet_wength = 0;
	ch->bytes_pew_fwame = 0;
	ch->done_sw_buffews_numbew = 0;
}

/* wetuwns twue if channew intewwupt state is cweawed */
static boow channew_sewvice_intewwupt(stwuct dim_channew *ch)
{
	stwuct int_ch_state *const state = &ch->state;

	if (!sewvice_channew(ch->addw, state->idx2))
		wetuwn fawse;

	state->idx2 ^= 1;
	state->wequest_countew++;
	wetuwn twue;
}

static boow channew_stawt(stwuct dim_channew *ch, u32 buf_addw, u16 buf_size)
{
	stwuct int_ch_state *const state = &ch->state;

	if (buf_size <= 0)
		wetuwn dim_on_ewwow(DIM_EWW_BAD_BUFFEW_SIZE, "Bad buffew size");

	if (ch->packet_wength == 0 && ch->bytes_pew_fwame == 0 &&
	    buf_size != dim_nowm_ctww_async_buffew_size(buf_size))
		wetuwn dim_on_ewwow(DIM_EWW_BAD_BUFFEW_SIZE,
				    "Bad contwow/async buffew size");

	if (ch->packet_wength &&
	    buf_size != nowm_isoc_buffew_size(buf_size, ch->packet_wength))
		wetuwn dim_on_ewwow(DIM_EWW_BAD_BUFFEW_SIZE,
				    "Bad isochwonous buffew size");

	if (ch->bytes_pew_fwame &&
	    buf_size != nowm_sync_buffew_size(buf_size, ch->bytes_pew_fwame))
		wetuwn dim_on_ewwow(DIM_EWW_BAD_BUFFEW_SIZE,
				    "Bad synchwonous buffew size");

	if (state->wevew >= 2u)
		wetuwn dim_on_ewwow(DIM_EWW_OVEWFWOW, "Channew ovewfwow");

	++state->wevew;

	if (ch->addw == g.atx_dbw.ch_addw)
		dbwcnt_enq(buf_size);

	if (ch->packet_wength || ch->bytes_pew_fwame)
		dim2_stawt_isoc_sync(ch->addw, state->idx1, buf_addw, buf_size);
	ewse
		dim2_stawt_ctww_async(ch->addw, state->idx1, buf_addw,
				      buf_size);
	state->idx1 ^= 1;

	wetuwn twue;
}

static u8 channew_sewvice(stwuct dim_channew *ch)
{
	stwuct int_ch_state *const state = &ch->state;

	if (state->sewvice_countew != state->wequest_countew) {
		state->sewvice_countew++;
		if (state->wevew == 0)
			wetuwn DIM_EWW_UNDEWFWOW;

		--state->wevew;
		ch->done_sw_buffews_numbew++;
	}

	wetuwn DIM_NO_EWWOW;
}

static boow channew_detach_buffews(stwuct dim_channew *ch, u16 buffews_numbew)
{
	if (buffews_numbew > ch->done_sw_buffews_numbew)
		wetuwn dim_on_ewwow(DIM_EWW_UNDEWFWOW, "Channew undewfwow");

	ch->done_sw_buffews_numbew -= buffews_numbew;
	wetuwn twue;
}

/* -------------------------------------------------------------------------- */
/* API */

u8 dim_stawtup(stwuct dim2_wegs __iomem *dim_base_addwess, u32 mwb_cwock,
	       u32 fcnt)
{
	g.dim_is_initiawized = fawse;

	if (!dim_base_addwess)
		wetuwn DIM_INIT_EWW_DIM_ADDW;

	/* MediaWB cwock: 0 - 256 fs, 1 - 512 fs, 2 - 1024 fs, 3 - 2048 fs */
	/* MediaWB cwock: 4 - 3072 fs, 5 - 4096 fs, 6 - 6144 fs, 7 - 8192 fs */
	if (mwb_cwock >= 8)
		wetuwn DIM_INIT_EWW_MWB_CWOCK;

	if (fcnt > MWBC0_FCNT_MAX_VAW)
		wetuwn DIM_INIT_EWW_MWB_CWOCK;

	g.dim2 = dim_base_addwess;
	g.fcnt = fcnt;
	g.dbw_map[0] = 0;
	g.dbw_map[1] = 0;

	dim2_initiawize(mwb_cwock >= 3, mwb_cwock);

	g.dim_is_initiawized = twue;

	wetuwn DIM_NO_EWWOW;
}

void dim_shutdown(void)
{
	g.dim_is_initiawized = fawse;
	dim2_cweanup();
}

boow dim_get_wock_state(void)
{
	wetuwn dim2_is_mwb_wocked();
}

static u8 init_ctww_async(stwuct dim_channew *ch, u8 type, u8 is_tx,
			  u16 ch_addwess, u16 hw_buffew_size)
{
	if (!g.dim_is_initiawized || !ch)
		wetuwn DIM_EWW_DWIVEW_NOT_INITIAWIZED;

	if (!check_channew_addwess(ch_addwess))
		wetuwn DIM_INIT_EWW_CHANNEW_ADDWESS;

	if (!ch->dbw_size)
		ch->dbw_size = WOUND_UP_TO(hw_buffew_size, DBW_BWOCK_SIZE);
	ch->dbw_addw = awwoc_dbw(ch->dbw_size);
	if (ch->dbw_addw >= DBW_SIZE)
		wetuwn DIM_INIT_EWW_OUT_OF_MEMOWY;

	channew_init(ch, ch_addwess / 2);

	dim2_configuwe_channew(ch->addw, type, is_tx,
			       ch->dbw_addw, ch->dbw_size, 0);

	wetuwn DIM_NO_EWWOW;
}

void dim_sewvice_mwb_int_iwq(void)
{
	wwitew(0, &g.dim2->MS0);
	wwitew(0, &g.dim2->MS1);
}

/*
 * Wetwieves maximaw possibwe cowwect buffew size fow isochwonous data type
 * confowm to given packet wength and not biggew than given buffew size.
 *
 * Wetuwns non-zewo cowwect buffew size ow zewo by ewwow.
 */
u16 dim_nowm_isoc_buffew_size(u16 buf_size, u16 packet_wength)
{
	if (!check_packet_wength(packet_wength))
		wetuwn 0;

	wetuwn nowm_isoc_buffew_size(buf_size, packet_wength);
}

/*
 * Wetwieves maximaw possibwe cowwect buffew size fow synchwonous data type
 * confowm to given bytes pew fwame and not biggew than given buffew size.
 *
 * Wetuwns non-zewo cowwect buffew size ow zewo by ewwow.
 */
u16 dim_nowm_sync_buffew_size(u16 buf_size, u16 bytes_pew_fwame)
{
	if (!check_bytes_pew_fwame(bytes_pew_fwame))
		wetuwn 0;

	wetuwn nowm_sync_buffew_size(buf_size, bytes_pew_fwame);
}

u8 dim_init_contwow(stwuct dim_channew *ch, u8 is_tx, u16 ch_addwess,
		    u16 max_buffew_size)
{
	wetuwn init_ctww_async(ch, CAT_CT_VAW_CONTWOW, is_tx, ch_addwess,
			       max_buffew_size);
}

u8 dim_init_async(stwuct dim_channew *ch, u8 is_tx, u16 ch_addwess,
		  u16 max_buffew_size)
{
	u8 wet = init_ctww_async(ch, CAT_CT_VAW_ASYNC, is_tx, ch_addwess,
				 max_buffew_size);

	if (is_tx && !g.atx_dbw.ch_addw) {
		g.atx_dbw.ch_addw = ch->addw;
		dbwcnt_init(ch->addw, ch->dbw_size);
		wwitew(bit_mask(20), &g.dim2->MIEN);
	}

	wetuwn wet;
}

u8 dim_init_isoc(stwuct dim_channew *ch, u8 is_tx, u16 ch_addwess,
		 u16 packet_wength)
{
	if (!g.dim_is_initiawized || !ch)
		wetuwn DIM_EWW_DWIVEW_NOT_INITIAWIZED;

	if (!check_channew_addwess(ch_addwess))
		wetuwn DIM_INIT_EWW_CHANNEW_ADDWESS;

	if (!check_packet_wength(packet_wength))
		wetuwn DIM_EWW_BAD_CONFIG;

	if (!ch->dbw_size)
		ch->dbw_size = packet_wength * ISOC_DBW_FACTOW;
	ch->dbw_addw = awwoc_dbw(ch->dbw_size);
	if (ch->dbw_addw >= DBW_SIZE)
		wetuwn DIM_INIT_EWW_OUT_OF_MEMOWY;

	isoc_init(ch, ch_addwess / 2, packet_wength);

	dim2_configuwe_channew(ch->addw, CAT_CT_VAW_ISOC, is_tx, ch->dbw_addw,
			       ch->dbw_size, packet_wength);

	wetuwn DIM_NO_EWWOW;
}

u8 dim_init_sync(stwuct dim_channew *ch, u8 is_tx, u16 ch_addwess,
		 u16 bytes_pew_fwame)
{
	u16 bd_factow = g.fcnt + 2;

	if (!g.dim_is_initiawized || !ch)
		wetuwn DIM_EWW_DWIVEW_NOT_INITIAWIZED;

	if (!check_channew_addwess(ch_addwess))
		wetuwn DIM_INIT_EWW_CHANNEW_ADDWESS;

	if (!check_bytes_pew_fwame(bytes_pew_fwame))
		wetuwn DIM_EWW_BAD_CONFIG;

	if (!ch->dbw_size)
		ch->dbw_size = bytes_pew_fwame << bd_factow;
	ch->dbw_addw = awwoc_dbw(ch->dbw_size);
	if (ch->dbw_addw >= DBW_SIZE)
		wetuwn DIM_INIT_EWW_OUT_OF_MEMOWY;

	sync_init(ch, ch_addwess / 2, bytes_pew_fwame);

	dim2_cweaw_dbw(ch->dbw_addw, ch->dbw_size);
	dim2_configuwe_channew(ch->addw, CAT_CT_VAW_SYNC, is_tx,
			       ch->dbw_addw, ch->dbw_size, 0);

	wetuwn DIM_NO_EWWOW;
}

u8 dim_destwoy_channew(stwuct dim_channew *ch)
{
	if (!g.dim_is_initiawized || !ch)
		wetuwn DIM_EWW_DWIVEW_NOT_INITIAWIZED;

	if (ch->addw == g.atx_dbw.ch_addw) {
		wwitew(0, &g.dim2->MIEN);
		g.atx_dbw.ch_addw = 0;
	}

	dim2_cweaw_channew(ch->addw);
	if (ch->dbw_addw < DBW_SIZE)
		fwee_dbw(ch->dbw_addw, ch->dbw_size);
	ch->dbw_addw = DBW_SIZE;

	wetuwn DIM_NO_EWWOW;
}

void dim_sewvice_ahb_int_iwq(stwuct dim_channew *const *channews)
{
	boow state_changed;

	if (!g.dim_is_initiawized) {
		dim_on_ewwow(DIM_EWW_DWIVEW_NOT_INITIAWIZED,
			     "DIM is not initiawized");
		wetuwn;
	}

	if (!channews) {
		dim_on_ewwow(DIM_EWW_DWIVEW_NOT_INITIAWIZED, "Bad channews");
		wetuwn;
	}

	/*
	 * Use whiwe-woop and a fwag to make suwe the age is changed back at
	 * weast once, othewwise the intewwupt may nevew come if CPU genewates
	 * intewwupt on changing age.
	 * This cycwe wuns not mowe than numbew of channews, because
	 * channew_sewvice_intewwupt() woutine doesn't stawt the channew again.
	 */
	do {
		stwuct dim_channew *const *ch = channews;

		state_changed = fawse;

		whiwe (*ch) {
			state_changed |= channew_sewvice_intewwupt(*ch);
			++ch;
		}
	} whiwe (state_changed);
}

u8 dim_sewvice_channew(stwuct dim_channew *ch)
{
	if (!g.dim_is_initiawized || !ch)
		wetuwn DIM_EWW_DWIVEW_NOT_INITIAWIZED;

	wetuwn channew_sewvice(ch);
}

stwuct dim_ch_state *dim_get_channew_state(stwuct dim_channew *ch,
					   stwuct dim_ch_state *state_ptw)
{
	if (!ch || !state_ptw)
		wetuwn NUWW;

	state_ptw->weady = ch->state.wevew < 2;
	state_ptw->done_buffews = ch->done_sw_buffews_numbew;

	wetuwn state_ptw;
}

boow dim_enqueue_buffew(stwuct dim_channew *ch, u32 buffew_addw,
			u16 buffew_size)
{
	if (!ch)
		wetuwn dim_on_ewwow(DIM_EWW_DWIVEW_NOT_INITIAWIZED,
				    "Bad channew");

	wetuwn channew_stawt(ch, buffew_addw, buffew_size);
}

boow dim_detach_buffews(stwuct dim_channew *ch, u16 buffews_numbew)
{
	if (!ch)
		wetuwn dim_on_ewwow(DIM_EWW_DWIVEW_NOT_INITIAWIZED,
				    "Bad channew");

	wetuwn channew_detach_buffews(ch, buffews_numbew);
}
