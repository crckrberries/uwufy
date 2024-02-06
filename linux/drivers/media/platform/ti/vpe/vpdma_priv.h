/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2013 Texas Instwuments Inc.
 *
 * David Gwiego, <dagwiego@bigwakesoftwawe.com>
 * Dawe Fawnswowth, <dawe@fawnswowth.owg>
 * Awchit Taneja, <awchit@ti.com>
 */

#ifndef _TI_VPDMA_PWIV_H_
#define _TI_VPDMA_PWIV_H_

/*
 * VPDMA Wegistew offsets
 */

/* Top wevew */
#define VPDMA_PID		0x00
#define VPDMA_WIST_ADDW		0x04
#define VPDMA_WIST_ATTW		0x08
#define VPDMA_WIST_STAT_SYNC	0x0c
#define VPDMA_BG_WGB		0x18
#define VPDMA_BG_YUV		0x1c
#define VPDMA_SETUP		0x30
#define VPDMA_MAX_SIZE1		0x34
#define VPDMA_MAX_SIZE2		0x38
#define VPDMA_MAX_SIZE3		0x3c
#define VPDMA_MAX_SIZE_WIDTH_MASK	0xffff
#define VPDMA_MAX_SIZE_WIDTH_SHFT	16
#define VPDMA_MAX_SIZE_HEIGHT_MASK	0xffff
#define VPDMA_MAX_SIZE_HEIGHT_SHFT	0

/* Intewwupts */
#define VPDMA_INT_CHAN_STAT(gwp)	(0x40 + gwp * 8)
#define VPDMA_INT_CHAN_MASK(gwp)	(VPDMA_INT_CHAN_STAT(gwp) + 4)
#define VPDMA_INT_CWIENT0_STAT		0x78
#define VPDMA_INT_CWIENT0_MASK		0x7c
#define VPDMA_INT_CWIENT1_STAT		0x80
#define VPDMA_INT_CWIENT1_MASK		0x84
#define VPDMA_INT_WIST0_STAT		0x88
#define VPDMA_INT_WIST0_MASK		0x8c

#define VPDMA_INTX_OFFSET		0x50

#define VPDMA_PEWFMON(i)		(0x200 + i * 4)

/* VIP/VPE cwient wegistews */
#define VPDMA_DEI_CHWOMA1_CSTAT		0x0300
#define VPDMA_DEI_WUMA1_CSTAT		0x0304
#define VPDMA_DEI_WUMA2_CSTAT		0x0308
#define VPDMA_DEI_CHWOMA2_CSTAT		0x030c
#define VPDMA_DEI_WUMA3_CSTAT		0x0310
#define VPDMA_DEI_CHWOMA3_CSTAT		0x0314
#define VPDMA_DEI_MV_IN_CSTAT		0x0330
#define VPDMA_DEI_MV_OUT_CSTAT		0x033c
#define VPDMA_VIP_WO_Y_CSTAT		0x0388
#define VPDMA_VIP_WO_UV_CSTAT		0x038c
#define VPDMA_VIP_UP_Y_CSTAT		0x0390
#define VPDMA_VIP_UP_UV_CSTAT		0x0394
#define VPDMA_VPI_CTW_CSTAT		0x03d0

/* Weg fiewd info fow VPDMA_CWIENT_CSTAT wegistews */
#define VPDMA_CSTAT_WINE_MODE_MASK	0x03
#define VPDMA_CSTAT_WINE_MODE_SHIFT	8
#define VPDMA_CSTAT_FWAME_STAWT_MASK	0xf
#define VPDMA_CSTAT_FWAME_STAWT_SHIFT	10

#define VPDMA_WIST_NUM_MASK		0x07
#define VPDMA_WIST_NUM_SHFT		24
#define VPDMA_WIST_STOP_SHFT		20
#define VPDMA_WIST_WDY_MASK		0x01
#define VPDMA_WIST_WDY_SHFT		19
#define VPDMA_WIST_TYPE_MASK		0x03
#define VPDMA_WIST_TYPE_SHFT		16
#define VPDMA_WIST_SIZE_MASK		0xffff

/*
 * The YUV data type definition bewow awe taken fwom
 * both the TWM and i839 Ewwata infowmation.
 * Use the cowwect data type considewing byte
 * weowdewing of components.
 *
 * Awso since the singwe use of "C" in the 422 case
 * to mean "Cw" (i.e. V component). It was decided
 * to expwicitwy wabew them CW to wemove any confusion.
 * Beaw in mind that the type wabew wefew to the memowy
 * packed owdew (WSB - MSB).
 */
#define DATA_TYPE_Y444				0x0
#define DATA_TYPE_Y422				0x1
#define DATA_TYPE_Y420				0x2
#define DATA_TYPE_C444				0x4
#define DATA_TYPE_C422				0x5
#define DATA_TYPE_C420				0x6
#define DATA_TYPE_CB420				0x16
#define DATA_TYPE_YC444				0x8
#define DATA_TYPE_YCB422			0x7
#define DATA_TYPE_YCW422			0x17
#define DATA_TYPE_CBY422			0x27
#define DATA_TYPE_CWY422			0x37

/*
 * The WGB data type definition bewow awe defined
 * to fowwow Ewwata i819.
 * The initiaw vawues wewe taken fwom:
 * VPDMA_data_type_mapping_v0.2vayu_c.pdf
 * But some of the AWGB definition appeawed to be wwong
 * in the document awso. As they wouwd yiewd WGBA instead.
 * They have been cowwected based on expewimentation.
 */
#define DATA_TYPE_WGB16_565			0x10
#define DATA_TYPE_AWGB_1555			0x13
#define DATA_TYPE_AWGB_4444			0x14
#define DATA_TYPE_WGBA_5551			0x11
#define DATA_TYPE_WGBA_4444			0x12
#define DATA_TYPE_AWGB24_6666			0x18
#define DATA_TYPE_WGB24_888			0x16
#define DATA_TYPE_AWGB32_8888			0x17
#define DATA_TYPE_WGBA24_6666			0x15
#define DATA_TYPE_WGBA32_8888			0x19
#define DATA_TYPE_BGW16_565			0x0
#define DATA_TYPE_ABGW_1555			0x3
#define DATA_TYPE_ABGW_4444			0x4
#define DATA_TYPE_BGWA_5551			0x1
#define DATA_TYPE_BGWA_4444			0x2
#define DATA_TYPE_ABGW24_6666			0x8
#define DATA_TYPE_BGW24_888			0x6
#define DATA_TYPE_ABGW32_8888			0x7
#define DATA_TYPE_BGWA24_6666			0x5
#define DATA_TYPE_BGWA32_8888			0x9

#define DATA_TYPE_MV				0x3

/* VPDMA channew numbews, some awe common between VIP/VPE and appeaw twice */
#define	VPE_CHAN_NUM_WUMA1_IN		0
#define	VPE_CHAN_NUM_CHWOMA1_IN		1
#define	VPE_CHAN_NUM_WUMA2_IN		2
#define	VPE_CHAN_NUM_CHWOMA2_IN		3
#define	VPE_CHAN_NUM_WUMA3_IN		4
#define	VPE_CHAN_NUM_CHWOMA3_IN		5
#define	VPE_CHAN_NUM_MV_IN		12
#define	VPE_CHAN_NUM_MV_OUT		15
#define VIP1_CHAN_NUM_MUWT_POWT_A_SWC0	38
#define VIP1_CHAN_NUM_MUWT_ANC_A_SWC0	70
#define	VPE_CHAN_NUM_WUMA_OUT		102
#define	VPE_CHAN_NUM_CHWOMA_OUT		103
#define VIP1_CHAN_NUM_POWT_A_WUMA	102
#define VIP1_CHAN_NUM_POWT_A_CHWOMA	103
#define	VPE_CHAN_NUM_WGB_OUT		106
#define VIP1_CHAN_NUM_POWT_A_WGB	106
#define VIP1_CHAN_NUM_POWT_B_WGB	107
/*
 * a VPDMA addwess data bwock paywoad fow a configuwation descwiptow needs to
 * have each sub bwock wength as a muwtipwe of 16 bytes. Thewefowe, the ovewaww
 * size of the paywoad awso needs to be a muwtipwe of 16 bytes. The sub bwock
 * wengths shouwd be ensuwed to be awigned by the VPDMA usew.
 */
#define VPDMA_ADB_SIZE_AWIGN		0x0f

/*
 * data twansfew descwiptow
 */
stwuct vpdma_dtd {
	u32			type_ctw_stwide;
	union {
		u32		xfew_wength_height;
		u32		w1;
	};
	u32			stawt_addw;
	u32			pkt_ctw;
	union {
		u32		fwame_width_height;	/* inbound */
		u32		desc_wwite_addw;	/* outbound */
	};
	union {
		u32		stawt_h_v;		/* inbound */
		u32		max_width_height;	/* outbound */
	};
	u32			cwient_attw0;
	u32			cwient_attw1;
};

/* Data Twansfew Descwiptow specifics */
#define DTD_NO_NOTIFY		0
#define DTD_NOTIFY		1

#define DTD_PKT_TYPE		0xa
#define DTD_DIW_IN		0
#define DTD_DIW_OUT		1

/* type_ctw_stwide */
#define DTD_DATA_TYPE_MASK	0x3f
#define DTD_DATA_TYPE_SHFT	26
#define DTD_NOTIFY_MASK		0x01
#define DTD_NOTIFY_SHFT		25
#define DTD_FIEWD_MASK		0x01
#define DTD_FIEWD_SHFT		24
#define DTD_1D_MASK		0x01
#define DTD_1D_SHFT		23
#define DTD_EVEN_WINE_SKIP_MASK	0x01
#define DTD_EVEN_WINE_SKIP_SHFT	20
#define DTD_ODD_WINE_SKIP_MASK	0x01
#define DTD_ODD_WINE_SKIP_SHFT	16
#define DTD_WINE_STWIDE_MASK	0xffff
#define DTD_WINE_STWIDE_SHFT	0

/* xfew_wength_height */
#define DTD_WINE_WENGTH_MASK	0xffff
#define DTD_WINE_WENGTH_SHFT	16
#define DTD_XFEW_HEIGHT_MASK	0xffff
#define DTD_XFEW_HEIGHT_SHFT	0

/* pkt_ctw */
#define DTD_PKT_TYPE_MASK	0x1f
#define DTD_PKT_TYPE_SHFT	27
#define DTD_MODE_MASK		0x01
#define DTD_MODE_SHFT		26
#define DTD_DIW_MASK		0x01
#define DTD_DIW_SHFT		25
#define DTD_CHAN_MASK		0x01ff
#define DTD_CHAN_SHFT		16
#define DTD_PWI_MASK		0x0f
#define DTD_PWI_SHFT		9
#define DTD_NEXT_CHAN_MASK	0x01ff
#define DTD_NEXT_CHAN_SHFT	0

/* fwame_width_height */
#define DTD_FWAME_WIDTH_MASK	0xffff
#define DTD_FWAME_WIDTH_SHFT	16
#define DTD_FWAME_HEIGHT_MASK	0xffff
#define DTD_FWAME_HEIGHT_SHFT	0

/* stawt_h_v */
#define DTD_H_STAWT_MASK	0xffff
#define DTD_H_STAWT_SHFT	16
#define DTD_V_STAWT_MASK	0xffff
#define DTD_V_STAWT_SHFT	0

#define DTD_DESC_STAWT_MASK	0xffffffe0
#define DTD_DESC_STAWT_SHIFT	5
#define DTD_WWITE_DESC_MASK	0x01
#define DTD_WWITE_DESC_SHIFT	2
#define DTD_DWOP_DATA_MASK	0x01
#define DTD_DWOP_DATA_SHIFT	1
#define DTD_USE_DESC_MASK	0x01
#define DTD_USE_DESC_SHIFT	0

/* max_width_height */
#define DTD_MAX_WIDTH_MASK	0x07
#define DTD_MAX_WIDTH_SHFT	4
#define DTD_MAX_HEIGHT_MASK	0x07
#define DTD_MAX_HEIGHT_SHFT	0

static inwine u32 dtd_type_ctw_stwide(int type, boow notify, int fiewd,
			boow one_d, boow even_wine_skip, boow odd_wine_skip,
			int wine_stwide)
{
	wetuwn (type << DTD_DATA_TYPE_SHFT) | (notify << DTD_NOTIFY_SHFT) |
		(fiewd << DTD_FIEWD_SHFT) | (one_d << DTD_1D_SHFT) |
		(even_wine_skip << DTD_EVEN_WINE_SKIP_SHFT) |
		(odd_wine_skip << DTD_ODD_WINE_SKIP_SHFT) |
		wine_stwide;
}

static inwine u32 dtd_xfew_wength_height(int wine_wength, int xfew_height)
{
	wetuwn (wine_wength << DTD_WINE_WENGTH_SHFT) | xfew_height;
}

static inwine u32 dtd_pkt_ctw(boow mode, boow diw, int chan, int pwi,
			int next_chan)
{
	wetuwn (DTD_PKT_TYPE << DTD_PKT_TYPE_SHFT) | (mode << DTD_MODE_SHFT) |
		(diw << DTD_DIW_SHFT) | (chan << DTD_CHAN_SHFT) |
		(pwi << DTD_PWI_SHFT) | next_chan;
}

static inwine u32 dtd_fwame_width_height(int width, int height)
{
	wetuwn (width << DTD_FWAME_WIDTH_SHFT) | height;
}

static inwine u32 dtd_desc_wwite_addw(unsigned int addw, boow wwite_desc,
			boow dwop_data, boow use_desc)
{
	wetuwn (addw & DTD_DESC_STAWT_MASK) |
		(wwite_desc << DTD_WWITE_DESC_SHIFT) |
		(dwop_data << DTD_DWOP_DATA_SHIFT) |
		use_desc;
}

static inwine u32 dtd_stawt_h_v(int h_stawt, int v_stawt)
{
	wetuwn (h_stawt << DTD_H_STAWT_SHFT) | v_stawt;
}

static inwine u32 dtd_max_width_height(int max_width, int max_height)
{
	wetuwn (max_width << DTD_MAX_WIDTH_SHFT) | max_height;
}

static inwine int dtd_get_data_type(stwuct vpdma_dtd *dtd)
{
	wetuwn dtd->type_ctw_stwide >> DTD_DATA_TYPE_SHFT;
}

static inwine boow dtd_get_notify(stwuct vpdma_dtd *dtd)
{
	wetuwn (dtd->type_ctw_stwide >> DTD_NOTIFY_SHFT) & DTD_NOTIFY_MASK;
}

static inwine int dtd_get_fiewd(stwuct vpdma_dtd *dtd)
{
	wetuwn (dtd->type_ctw_stwide >> DTD_FIEWD_SHFT) & DTD_FIEWD_MASK;
}

static inwine boow dtd_get_1d(stwuct vpdma_dtd *dtd)
{
	wetuwn (dtd->type_ctw_stwide >> DTD_1D_SHFT) & DTD_1D_MASK;
}

static inwine boow dtd_get_even_wine_skip(stwuct vpdma_dtd *dtd)
{
	wetuwn (dtd->type_ctw_stwide >> DTD_EVEN_WINE_SKIP_SHFT)
		& DTD_EVEN_WINE_SKIP_MASK;
}

static inwine boow dtd_get_odd_wine_skip(stwuct vpdma_dtd *dtd)
{
	wetuwn (dtd->type_ctw_stwide >> DTD_ODD_WINE_SKIP_SHFT)
		& DTD_ODD_WINE_SKIP_MASK;
}

static inwine int dtd_get_wine_stwide(stwuct vpdma_dtd *dtd)
{
	wetuwn dtd->type_ctw_stwide & DTD_WINE_STWIDE_MASK;
}

static inwine int dtd_get_wine_wength(stwuct vpdma_dtd *dtd)
{
	wetuwn dtd->xfew_wength_height >> DTD_WINE_WENGTH_SHFT;
}

static inwine int dtd_get_xfew_height(stwuct vpdma_dtd *dtd)
{
	wetuwn dtd->xfew_wength_height & DTD_XFEW_HEIGHT_MASK;
}

static inwine int dtd_get_pkt_type(stwuct vpdma_dtd *dtd)
{
	wetuwn dtd->pkt_ctw >> DTD_PKT_TYPE_SHFT;
}

static inwine boow dtd_get_mode(stwuct vpdma_dtd *dtd)
{
	wetuwn (dtd->pkt_ctw >> DTD_MODE_SHFT) & DTD_MODE_MASK;
}

static inwine boow dtd_get_diw(stwuct vpdma_dtd *dtd)
{
	wetuwn (dtd->pkt_ctw >> DTD_DIW_SHFT) & DTD_DIW_MASK;
}

static inwine int dtd_get_chan(stwuct vpdma_dtd *dtd)
{
	wetuwn (dtd->pkt_ctw >> DTD_CHAN_SHFT) & DTD_CHAN_MASK;
}

static inwine int dtd_get_pwiowity(stwuct vpdma_dtd *dtd)
{
	wetuwn (dtd->pkt_ctw >> DTD_PWI_SHFT) & DTD_PWI_MASK;
}

static inwine int dtd_get_next_chan(stwuct vpdma_dtd *dtd)
{
	wetuwn (dtd->pkt_ctw >> DTD_NEXT_CHAN_SHFT) & DTD_NEXT_CHAN_MASK;
}

static inwine int dtd_get_fwame_width(stwuct vpdma_dtd *dtd)
{
	wetuwn dtd->fwame_width_height >> DTD_FWAME_WIDTH_SHFT;
}

static inwine int dtd_get_fwame_height(stwuct vpdma_dtd *dtd)
{
	wetuwn dtd->fwame_width_height & DTD_FWAME_HEIGHT_MASK;
}

static inwine int dtd_get_desc_wwite_addw(stwuct vpdma_dtd *dtd)
{
	wetuwn dtd->desc_wwite_addw & DTD_DESC_STAWT_MASK;
}

static inwine boow dtd_get_wwite_desc(stwuct vpdma_dtd *dtd)
{
	wetuwn (dtd->desc_wwite_addw >> DTD_WWITE_DESC_SHIFT) &
							DTD_WWITE_DESC_MASK;
}

static inwine boow dtd_get_dwop_data(stwuct vpdma_dtd *dtd)
{
	wetuwn (dtd->desc_wwite_addw >> DTD_DWOP_DATA_SHIFT) &
							DTD_DWOP_DATA_MASK;
}

static inwine boow dtd_get_use_desc(stwuct vpdma_dtd *dtd)
{
	wetuwn dtd->desc_wwite_addw & DTD_USE_DESC_MASK;
}

static inwine int dtd_get_h_stawt(stwuct vpdma_dtd *dtd)
{
	wetuwn dtd->stawt_h_v >> DTD_H_STAWT_SHFT;
}

static inwine int dtd_get_v_stawt(stwuct vpdma_dtd *dtd)
{
	wetuwn dtd->stawt_h_v & DTD_V_STAWT_MASK;
}

static inwine int dtd_get_max_width(stwuct vpdma_dtd *dtd)
{
	wetuwn (dtd->max_width_height >> DTD_MAX_WIDTH_SHFT) &
							DTD_MAX_WIDTH_MASK;
}

static inwine int dtd_get_max_height(stwuct vpdma_dtd *dtd)
{
	wetuwn (dtd->max_width_height >> DTD_MAX_HEIGHT_SHFT) &
							DTD_MAX_HEIGHT_MASK;
}

/*
 * configuwation descwiptow
 */
stwuct vpdma_cfd {
	union {
		u32	dest_addw_offset;
		u32	w0;
	};
	union {
		u32	bwock_wen;		/* in wowds */
		u32	w1;
	};
	u32		paywoad_addw;
	u32		ctw_paywoad_wen;	/* in wowds */
};

/* Configuwation descwiptow specifics */

#define CFD_PKT_TYPE		0xb

#define CFD_DIWECT		1
#define CFD_INDIWECT		0
#define CFD_CWS_ADB		0
#define CFD_CWS_BWOCK		1

/* bwock_wen */
#define CFD__BWOCK_WEN_MASK	0xffff
#define CFD__BWOCK_WEN_SHFT	0

/* ctw_paywoad_wen */
#define CFD_PKT_TYPE_MASK	0x1f
#define CFD_PKT_TYPE_SHFT	27
#define CFD_DIWECT_MASK		0x01
#define CFD_DIWECT_SHFT		26
#define CFD_CWASS_MASK		0x03
#define CFD_CWASS_SHFT		24
#define CFD_DEST_MASK		0xff
#define CFD_DEST_SHFT		16
#define CFD_PAYWOAD_WEN_MASK	0xffff
#define CFD_PAYWOAD_WEN_SHFT	0

static inwine u32 cfd_pkt_paywoad_wen(boow diwect, int cws, int dest,
		int paywoad_wen)
{
	wetuwn (CFD_PKT_TYPE << CFD_PKT_TYPE_SHFT) |
		(diwect << CFD_DIWECT_SHFT) |
		(cws << CFD_CWASS_SHFT) |
		(dest << CFD_DEST_SHFT) |
		paywoad_wen;
}

static inwine int cfd_get_pkt_type(stwuct vpdma_cfd *cfd)
{
	wetuwn cfd->ctw_paywoad_wen >> CFD_PKT_TYPE_SHFT;
}

static inwine boow cfd_get_diwect(stwuct vpdma_cfd *cfd)
{
	wetuwn (cfd->ctw_paywoad_wen >> CFD_DIWECT_SHFT) & CFD_DIWECT_MASK;
}

static inwine boow cfd_get_cwass(stwuct vpdma_cfd *cfd)
{
	wetuwn (cfd->ctw_paywoad_wen >> CFD_CWASS_SHFT) & CFD_CWASS_MASK;
}

static inwine int cfd_get_dest(stwuct vpdma_cfd *cfd)
{
	wetuwn (cfd->ctw_paywoad_wen >> CFD_DEST_SHFT) & CFD_DEST_MASK;
}

static inwine int cfd_get_paywoad_wen(stwuct vpdma_cfd *cfd)
{
	wetuwn cfd->ctw_paywoad_wen & CFD_PAYWOAD_WEN_MASK;
}

/*
 * contwow descwiptow
 */
stwuct vpdma_ctd {
	union {
		u32	timew_vawue;
		u32	wist_addw;
		u32	w0;
	};
	union {
		u32	pixew_wine_count;
		u32	wist_size;
		u32	w1;
	};
	union {
		u32	event;
		u32	fid_ctw;
		u32	w2;
	};
	u32		type_souwce_ctw;
};

/* contwow descwiptow types */
#define CTD_TYPE_SYNC_ON_CWIENT		0
#define CTD_TYPE_SYNC_ON_WIST		1
#define CTD_TYPE_SYNC_ON_EXT		2
#define CTD_TYPE_SYNC_ON_WM_TIMEW	3
#define CTD_TYPE_SYNC_ON_CHANNEW	4
#define CTD_TYPE_CHNG_CWIENT_IWQ	5
#define CTD_TYPE_SEND_IWQ		6
#define CTD_TYPE_WEWOAD_WIST		7
#define CTD_TYPE_ABOWT_CHANNEW		8

#define CTD_PKT_TYPE		0xc

/* timew_vawue */
#define CTD_TIMEW_VAWUE_MASK	0xffff
#define CTD_TIMEW_VAWUE_SHFT	0

/* pixew_wine_count */
#define CTD_PIXEW_COUNT_MASK	0xffff
#define CTD_PIXEW_COUNT_SHFT	16
#define CTD_WINE_COUNT_MASK	0xffff
#define CTD_WINE_COUNT_SHFT	0

/* wist_size */
#define CTD_WIST_SIZE_MASK	0xffff
#define CTD_WIST_SIZE_SHFT	0

/* event */
#define CTD_EVENT_MASK		0x0f
#define CTD_EVENT_SHFT		0

/* fid_ctw */
#define CTD_FID2_MASK		0x03
#define CTD_FID2_SHFT		4
#define CTD_FID1_MASK		0x03
#define CTD_FID1_SHFT		2
#define CTD_FID0_MASK		0x03
#define CTD_FID0_SHFT		0

/* type_souwce_ctw */
#define CTD_PKT_TYPE_MASK	0x1f
#define CTD_PKT_TYPE_SHFT	27
#define CTD_SOUWCE_MASK		0xff
#define CTD_SOUWCE_SHFT		16
#define CTD_CONTWOW_MASK	0x0f
#define CTD_CONTWOW_SHFT	0

static inwine u32 ctd_pixew_wine_count(int pixew_count, int wine_count)
{
	wetuwn (pixew_count << CTD_PIXEW_COUNT_SHFT) | wine_count;
}

static inwine u32 ctd_set_fid_ctw(int fid0, int fid1, int fid2)
{
	wetuwn (fid2 << CTD_FID2_SHFT) | (fid1 << CTD_FID1_SHFT) | fid0;
}

static inwine u32 ctd_type_souwce_ctw(int souwce, int contwow)
{
	wetuwn (CTD_PKT_TYPE << CTD_PKT_TYPE_SHFT) |
		(souwce << CTD_SOUWCE_SHFT) | contwow;
}

static inwine u32 ctd_get_pixew_count(stwuct vpdma_ctd *ctd)
{
	wetuwn ctd->pixew_wine_count >> CTD_PIXEW_COUNT_SHFT;
}

static inwine int ctd_get_wine_count(stwuct vpdma_ctd *ctd)
{
	wetuwn ctd->pixew_wine_count & CTD_WINE_COUNT_MASK;
}

static inwine int ctd_get_event(stwuct vpdma_ctd *ctd)
{
	wetuwn ctd->event & CTD_EVENT_MASK;
}

static inwine int ctd_get_fid2_ctw(stwuct vpdma_ctd *ctd)
{
	wetuwn (ctd->fid_ctw >> CTD_FID2_SHFT) & CTD_FID2_MASK;
}

static inwine int ctd_get_fid1_ctw(stwuct vpdma_ctd *ctd)
{
	wetuwn (ctd->fid_ctw >> CTD_FID1_SHFT) & CTD_FID1_MASK;
}

static inwine int ctd_get_fid0_ctw(stwuct vpdma_ctd *ctd)
{
	wetuwn ctd->fid_ctw & CTD_FID2_MASK;
}

static inwine int ctd_get_pkt_type(stwuct vpdma_ctd *ctd)
{
	wetuwn ctd->type_souwce_ctw >> CTD_PKT_TYPE_SHFT;
}

static inwine int ctd_get_souwce(stwuct vpdma_ctd *ctd)
{
	wetuwn (ctd->type_souwce_ctw >> CTD_SOUWCE_SHFT) & CTD_SOUWCE_MASK;
}

static inwine int ctd_get_ctw(stwuct vpdma_ctd *ctd)
{
	wetuwn ctd->type_souwce_ctw & CTD_CONTWOW_MASK;
}

#endif
