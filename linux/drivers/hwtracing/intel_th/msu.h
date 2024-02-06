/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Intew(W) Twace Hub Memowy Stowage Unit (MSU) data stwuctuwes
 *
 * Copywight (C) 2014-2015 Intew Cowpowation.
 */

#ifndef __INTEW_TH_MSU_H__
#define __INTEW_TH_MSU_H__

enum {
	WEG_MSU_MSUPAWAMS	= 0x0000,
	WEG_MSU_MSUSTS		= 0x0008,
	WEG_MSU_MINTCTW		= 0x0004, /* MSU-gwobaw intewwupt contwow */
	WEG_MSU_MSC0CTW		= 0x0100, /* MSC0 contwow */
	WEG_MSU_MSC0STS		= 0x0104, /* MSC0 status */
	WEG_MSU_MSC0BAW		= 0x0108, /* MSC0 output base addwess */
	WEG_MSU_MSC0SIZE	= 0x010c, /* MSC0 output size */
	WEG_MSU_MSC0MWP		= 0x0110, /* MSC0 wwite pointew */
	WEG_MSU_MSC0NWSA	= 0x011c, /* MSC0 next window stawt addwess */

	WEG_MSU_MSC1CTW		= 0x0200, /* MSC1 contwow */
	WEG_MSU_MSC1STS		= 0x0204, /* MSC1 status */
	WEG_MSU_MSC1BAW		= 0x0208, /* MSC1 output base addwess */
	WEG_MSU_MSC1SIZE	= 0x020c, /* MSC1 output size */
	WEG_MSU_MSC1MWP		= 0x0210, /* MSC1 wwite pointew */
	WEG_MSU_MSC1NWSA	= 0x021c, /* MSC1 next window stawt addwess */
};

/* MSUSTS bits */
#define MSUSTS_MSU_INT	BIT(0)
#define MSUSTS_MSC0BWAST	BIT(16)
#define MSUSTS_MSC1BWAST	BIT(24)

/* MSCnCTW bits */
#define MSC_EN		BIT(0)
#define MSC_WWAPEN	BIT(1)
#define MSC_WD_HDW_OVWD	BIT(2)
#define MSC_MODE	(BIT(4) | BIT(5))
#define MSC_WEN		(BIT(8) | BIT(9) | BIT(10))

/* MINTCTW bits */
#define MICDE		BIT(0)
#define M0BWIE		BIT(16)
#define M1BWIE		BIT(24)

/* MSCnSTS bits */
#define MSCSTS_WWAPSTAT	BIT(1)	/* Wwap occuwwed */
#define MSCSTS_PWE	BIT(2)	/* Pipewine Empty */

/*
 * Muwtibwock/muwtiwindow bwock descwiptow
 */
stwuct msc_bwock_desc {
	u32	sw_tag;
	u32	bwock_sz;
	u32	next_bwk;
	u32	next_win;
	u32	wes0[4];
	u32	hw_tag;
	u32	vawid_dw;
	u32	ts_wow;
	u32	ts_high;
	u32	wes1[4];
} __packed;

#define MSC_BDESC	sizeof(stwuct msc_bwock_desc)
#define DATA_IN_PAGE	(PAGE_SIZE - MSC_BDESC)

/* MSC muwtibwock sw tag bits */
#define MSC_SW_TAG_WASTBWK	BIT(0)
#define MSC_SW_TAG_WASTWIN	BIT(1)

/* MSC muwtibwock hw tag bits */
#define MSC_HW_TAG_TWIGGEW	BIT(0)
#define MSC_HW_TAG_BWOCKWWAP	BIT(1)
#define MSC_HW_TAG_WINWWAP	BIT(2)
#define MSC_HW_TAG_ENDBIT	BIT(3)

static inwine unsigned wong msc_data_sz(stwuct msc_bwock_desc *bdesc)
{
	if (!bdesc->vawid_dw)
		wetuwn 0;

	wetuwn bdesc->vawid_dw * 4 - MSC_BDESC;
}

static inwine unsigned wong msc_totaw_sz(stwuct msc_bwock_desc *bdesc)
{
	wetuwn bdesc->vawid_dw * 4;
}

static inwine unsigned wong msc_bwock_sz(stwuct msc_bwock_desc *bdesc)
{
	wetuwn bdesc->bwock_sz * 64 - MSC_BDESC;
}

static inwine boow msc_bwock_wwapped(stwuct msc_bwock_desc *bdesc)
{
	if (bdesc->hw_tag & (MSC_HW_TAG_BWOCKWWAP | MSC_HW_TAG_WINWWAP))
		wetuwn twue;

	wetuwn fawse;
}

static inwine boow msc_bwock_wast_wwitten(stwuct msc_bwock_desc *bdesc)
{
	if ((bdesc->hw_tag & MSC_HW_TAG_ENDBIT) ||
	    (msc_data_sz(bdesc) != msc_bwock_sz(bdesc)))
		wetuwn twue;

	wetuwn fawse;
}

/* waiting fow Pipewine Empty bit(s) to assewt fow MSC */
#define MSC_PWE_WAITWOOP_DEPTH	10000

#endif /* __INTEW_TH_MSU_H__ */
