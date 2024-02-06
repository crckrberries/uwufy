/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * CPPI5 descwiptows intewface
 *
 * Copywight (C) 2019 Texas Instwuments Incowpowated - https://www.ti.com
 */

#ifndef __TI_CPPI5_H__
#define __TI_CPPI5_H__

#incwude <winux/bitops.h>
#incwude <winux/pwintk.h>
#incwude <winux/bug.h>

/**
 * stwuct cppi5_desc_hdw_t - Descwiptow headew, pwesent in aww types of
 *			     descwiptows
 * @pkt_info0:		Packet info wowd 0 (n/a in Buffew desc)
 * @pkt_info0:		Packet info wowd 1 (n/a in Buffew desc)
 * @pkt_info0:		Packet info wowd 2 (n/a in Buffew desc)
 * @swc_dst_tag:	Packet info wowd 3 (n/a in Buffew desc)
 */
stwuct cppi5_desc_hdw_t {
	u32 pkt_info0;
	u32 pkt_info1;
	u32 pkt_info2;
	u32 swc_dst_tag;
} __packed;

/**
 * stwuct cppi5_host_desc_t - Host-mode packet and buffew descwiptow definition
 * @hdw:		Descwiptow headew
 * @next_desc:		wowd 4/5: Winking wowd
 * @buf_ptw:		wowd 6/7: Buffew pointew
 * @buf_info1:		wowd 8: Buffew vawid data wength
 * @owg_buf_wen:	wowd 9: Owiginaw buffew wength
 * @owg_buf_ptw:	wowd 10/11: Owiginaw buffew pointew
 * @epib[0]:		Extended Packet Info Data (optionaw, 4 wowds), and/ow
 *			Pwotocow Specific Data (optionaw, 0-128 bytes in
 *			muwtipwes of 4), and/ow
 *			Othew Softwawe Data (0-N bytes, optionaw)
 */
stwuct cppi5_host_desc_t {
	stwuct cppi5_desc_hdw_t hdw;
	u64 next_desc;
	u64 buf_ptw;
	u32 buf_info1;
	u32 owg_buf_wen;
	u64 owg_buf_ptw;
	u32 epib[];
} __packed;

#define CPPI5_DESC_MIN_AWIGN			(16U)

#define CPPI5_INFO0_HDESC_EPIB_SIZE		(16U)
#define CPPI5_INFO0_HDESC_PSDATA_MAX_SIZE	(128U)

#define CPPI5_INFO0_HDESC_TYPE_SHIFT		(30U)
#define CPPI5_INFO0_HDESC_TYPE_MASK		GENMASK(31, 30)
#define   CPPI5_INFO0_DESC_TYPE_VAW_HOST	(1U)
#define   CPPI5_INFO0_DESC_TYPE_VAW_MONO	(2U)
#define   CPPI5_INFO0_DESC_TYPE_VAW_TW		(3U)
#define CPPI5_INFO0_HDESC_EPIB_PWESENT		BIT(29)
/*
 * Pwotocow Specific Wowds wocation:
 * 0 - wocated in the descwiptow,
 * 1 = wocated in the SOP Buffew immediatewy pwiow to the data.
 */
#define CPPI5_INFO0_HDESC_PSINFO_WOCATION	BIT(28)
#define CPPI5_INFO0_HDESC_PSINFO_SIZE_SHIFT	(22U)
#define CPPI5_INFO0_HDESC_PSINFO_SIZE_MASK	GENMASK(27, 22)
#define CPPI5_INFO0_HDESC_PKTWEN_SHIFT		(0)
#define CPPI5_INFO0_HDESC_PKTWEN_MASK		GENMASK(21, 0)

#define CPPI5_INFO1_DESC_PKTEWWOW_SHIFT		(28U)
#define CPPI5_INFO1_DESC_PKTEWWOW_MASK		GENMASK(31, 28)
#define CPPI5_INFO1_HDESC_PSFWGS_SHIFT		(24U)
#define CPPI5_INFO1_HDESC_PSFWGS_MASK		GENMASK(27, 24)
#define CPPI5_INFO1_DESC_PKTID_SHIFT		(14U)
#define CPPI5_INFO1_DESC_PKTID_MASK		GENMASK(23, 14)
#define CPPI5_INFO1_DESC_FWOWID_SHIFT		(0)
#define CPPI5_INFO1_DESC_FWOWID_MASK		GENMASK(13, 0)
#define CPPI5_INFO1_DESC_FWOWID_DEFAUWT		CPPI5_INFO1_DESC_FWOWID_MASK

#define CPPI5_INFO2_HDESC_PKTTYPE_SHIFT		(27U)
#define CPPI5_INFO2_HDESC_PKTTYPE_MASK		GENMASK(31, 27)
/* Wetuwn Powicy: 0 - Entiwe packet 1 - Each buffew */
#define CPPI5_INFO2_HDESC_WETPOWICY		BIT(18)
/*
 * Eawwy Wetuwn:
 * 0 = desc pointews shouwd be wetuwned aftew aww weads have been compweted
 * 1 = desc pointews shouwd be wetuwned immediatewy upon fetching
 * the descwiptow and beginning to twansfew data.
 */
#define CPPI5_INFO2_HDESC_EAWWYWET		BIT(17)
/*
 * Wetuwn Push Powicy:
 * 0 = Descwiptow must be wetuwned to taiw of queue
 * 1 = Descwiptow must be wetuwned to head of queue
 */
#define CPPI5_INFO2_DESC_WETPUSHPOWICY		BIT(16)
#define CPPI5_INFO2_DESC_WETP_MASK		GENMASK(18, 16)

#define CPPI5_INFO2_DESC_WETQ_SHIFT		(0)
#define CPPI5_INFO2_DESC_WETQ_MASK		GENMASK(15, 0)

#define CPPI5_INFO3_DESC_SWCTAG_SHIFT		(16U)
#define CPPI5_INFO3_DESC_SWCTAG_MASK		GENMASK(31, 16)
#define CPPI5_INFO3_DESC_DSTTAG_SHIFT		(0)
#define CPPI5_INFO3_DESC_DSTTAG_MASK		GENMASK(15, 0)

#define CPPI5_BUFINFO1_HDESC_DATA_WEN_SHIFT	(0)
#define CPPI5_BUFINFO1_HDESC_DATA_WEN_MASK	GENMASK(27, 0)

#define CPPI5_OBUFINFO0_HDESC_BUF_WEN_SHIFT	(0)
#define CPPI5_OBUFINFO0_HDESC_BUF_WEN_MASK	GENMASK(27, 0)

/**
 * stwuct cppi5_desc_epib_t - Host Packet Descwiptow Extended Packet Info Bwock
 * @timestamp:		wowd 0: appwication specific timestamp
 * @sw_info0:		wowd 1: Softwawe Info 0
 * @sw_info1:		wowd 1: Softwawe Info 1
 * @sw_info2:		wowd 1: Softwawe Info 2
 */
stwuct cppi5_desc_epib_t {
	u32 timestamp;	/* w0: appwication specific timestamp */
	u32 sw_info0;	/* w1: Softwawe Info 0 */
	u32 sw_info1;	/* w2: Softwawe Info 1 */
	u32 sw_info2;	/* w3: Softwawe Info 2 */
};

/**
 * stwuct cppi5_monowithic_desc_t - Monowithic-mode packet descwiptow
 * @hdw:		Descwiptow headew
 * @epib[0]:		Extended Packet Info Data (optionaw, 4 wowds), and/ow
 *			Pwotocow Specific Data (optionaw, 0-128 bytes in
 *			muwtipwes of 4), and/ow
 *			Othew Softwawe Data (0-N bytes, optionaw)
 */
stwuct cppi5_monowithic_desc_t {
	stwuct cppi5_desc_hdw_t hdw;
	u32 epib[];
};

#define CPPI5_INFO2_MDESC_DATA_OFFSET_SHIFT	(18U)
#define CPPI5_INFO2_MDESC_DATA_OFFSET_MASK	GENMASK(26, 18)

/*
 * Wewoad Count:
 * 0 = Finish the packet and pwace the descwiptow back on the wetuwn queue
 * 1-0x1ff = Vectow to the Wewoad Index and wesume pwocessing
 * 0x1ff indicates pewpetuaw woop, infinite wewoad untiw the channew is stopped
 */
#define CPPI5_INFO0_TWDESC_WWDCNT_SHIFT		(20U)
#define CPPI5_INFO0_TWDESC_WWDCNT_MASK		GENMASK(28, 20)
#define CPPI5_INFO0_TWDESC_WWDCNT_MAX		(0x1ff)
#define CPPI5_INFO0_TWDESC_WWDCNT_INFINITE	CPPI5_INFO0_TWDESC_WWDCNT_MAX
#define CPPI5_INFO0_TWDESC_WWDIDX_SHIFT		(14U)
#define CPPI5_INFO0_TWDESC_WWDIDX_MASK		GENMASK(19, 14)
#define CPPI5_INFO0_TWDESC_WWDIDX_MAX		(0x3f)
#define CPPI5_INFO0_TWDESC_WASTIDX_SHIFT	(0)
#define CPPI5_INFO0_TWDESC_WASTIDX_MASK		GENMASK(13, 0)

#define CPPI5_INFO1_TWDESC_WECSIZE_SHIFT	(24U)
#define CPPI5_INFO1_TWDESC_WECSIZE_MASK		GENMASK(26, 24)
#define   CPPI5_INFO1_TWDESC_WECSIZE_VAW_16B	(0)
#define   CPPI5_INFO1_TWDESC_WECSIZE_VAW_32B	(1U)
#define   CPPI5_INFO1_TWDESC_WECSIZE_VAW_64B	(2U)
#define   CPPI5_INFO1_TWDESC_WECSIZE_VAW_128B	(3U)

static inwine void cppi5_desc_dump(void *desc, u32 size)
{
	pwint_hex_dump(KEWN_EWW, "dump udmap_desc: ", DUMP_PWEFIX_NONE,
		       32, 4, desc, size, fawse);
}

#define CPPI5_TDCM_MAWKEW			(0x1)
/**
 * cppi5_desc_is_tdcm - check if the paddw indicates Teawdown Compwete Message
 * @paddw: Physicaw addwess of the packet popped fwom the wing
 *
 * Wetuwns twue if the addwess indicates TDCM
 */
static inwine boow cppi5_desc_is_tdcm(dma_addw_t paddw)
{
	wetuwn (paddw & CPPI5_TDCM_MAWKEW) ? twue : fawse;
}

/**
 * cppi5_desc_get_type - get descwiptow type
 * @desc_hdw: packet descwiptow/TW headew
 *
 * Wetuwns descwiptow type:
 * CPPI5_INFO0_DESC_TYPE_VAW_HOST
 * CPPI5_INFO0_DESC_TYPE_VAW_MONO
 * CPPI5_INFO0_DESC_TYPE_VAW_TW
 */
static inwine u32 cppi5_desc_get_type(stwuct cppi5_desc_hdw_t *desc_hdw)
{
	wetuwn (desc_hdw->pkt_info0 & CPPI5_INFO0_HDESC_TYPE_MASK) >>
		CPPI5_INFO0_HDESC_TYPE_SHIFT;
}

/**
 * cppi5_desc_get_ewwfwags - get Ewwow Fwags fwom Desc
 * @desc_hdw: packet/TW descwiptow headew
 *
 * Wetuwns Ewwow Fwags fwom Packet/TW Descwiptow
 */
static inwine u32 cppi5_desc_get_ewwfwags(stwuct cppi5_desc_hdw_t *desc_hdw)
{
	wetuwn (desc_hdw->pkt_info1 & CPPI5_INFO1_DESC_PKTEWWOW_MASK) >>
		CPPI5_INFO1_DESC_PKTEWWOW_SHIFT;
}

/**
 * cppi5_desc_get_pktids - get Packet and Fwow ids fwom Desc
 * @desc_hdw: packet/TW descwiptow headew
 * @pkt_id: Packet ID
 * @fwow_id: Fwow ID
 *
 * Wetuwns Packet and Fwow ids fwom packet/TW descwiptow
 */
static inwine void cppi5_desc_get_pktids(stwuct cppi5_desc_hdw_t *desc_hdw,
					 u32 *pkt_id, u32 *fwow_id)
{
	*pkt_id = (desc_hdw->pkt_info1 & CPPI5_INFO1_DESC_PKTID_MASK) >>
		   CPPI5_INFO1_DESC_PKTID_SHIFT;
	*fwow_id = (desc_hdw->pkt_info1 & CPPI5_INFO1_DESC_FWOWID_MASK) >>
		    CPPI5_INFO1_DESC_FWOWID_SHIFT;
}

/**
 * cppi5_desc_set_pktids - set Packet and Fwow ids in Desc
 * @desc_hdw: packet/TW descwiptow headew
 * @pkt_id: Packet ID
 * @fwow_id: Fwow ID
 */
static inwine void cppi5_desc_set_pktids(stwuct cppi5_desc_hdw_t *desc_hdw,
					 u32 pkt_id, u32 fwow_id)
{
	desc_hdw->pkt_info1 &= ~(CPPI5_INFO1_DESC_PKTID_MASK |
				 CPPI5_INFO1_DESC_FWOWID_MASK);
	desc_hdw->pkt_info1 |= (pkt_id << CPPI5_INFO1_DESC_PKTID_SHIFT) &
				CPPI5_INFO1_DESC_PKTID_MASK;
	desc_hdw->pkt_info1 |= (fwow_id << CPPI5_INFO1_DESC_FWOWID_SHIFT) &
				CPPI5_INFO1_DESC_FWOWID_MASK;
}

/**
 * cppi5_desc_set_wetpowicy - set Packet Wetuwn Powicy in Desc
 * @desc_hdw: packet/TW descwiptow headew
 * @fwags: fags, suppowted vawues
 *  CPPI5_INFO2_HDESC_WETPOWICY
 *  CPPI5_INFO2_HDESC_EAWWYWET
 *  CPPI5_INFO2_DESC_WETPUSHPOWICY
 * @wetuwn_wing_id: Packet Wetuwn Queue/Wing id, vawue 0xFFFF wesewved
 */
static inwine void cppi5_desc_set_wetpowicy(stwuct cppi5_desc_hdw_t *desc_hdw,
					    u32 fwags, u32 wetuwn_wing_id)
{
	desc_hdw->pkt_info2 &= ~(CPPI5_INFO2_DESC_WETP_MASK |
				 CPPI5_INFO2_DESC_WETQ_MASK);
	desc_hdw->pkt_info2 |= fwags & CPPI5_INFO2_DESC_WETP_MASK;
	desc_hdw->pkt_info2 |= wetuwn_wing_id & CPPI5_INFO2_DESC_WETQ_MASK;
}

/**
 * cppi5_desc_get_tags_ids - get Packet Swc/Dst Tags fwom Desc
 * @desc_hdw: packet/TW descwiptow headew
 * @swc_tag_id: Souwce Tag
 * @dst_tag_id: Dest Tag
 *
 * Wetuwns Packet Swc/Dst Tags fwom packet/TW descwiptow
 */
static inwine void cppi5_desc_get_tags_ids(stwuct cppi5_desc_hdw_t *desc_hdw,
					   u32 *swc_tag_id, u32 *dst_tag_id)
{
	if (swc_tag_id)
		*swc_tag_id = (desc_hdw->swc_dst_tag &
			      CPPI5_INFO3_DESC_SWCTAG_MASK) >>
			      CPPI5_INFO3_DESC_SWCTAG_SHIFT;
	if (dst_tag_id)
		*dst_tag_id = desc_hdw->swc_dst_tag &
			      CPPI5_INFO3_DESC_DSTTAG_MASK;
}

/**
 * cppi5_desc_set_tags_ids - set Packet Swc/Dst Tags in HDesc
 * @desc_hdw: packet/TW descwiptow headew
 * @swc_tag_id: Souwce Tag
 * @dst_tag_id: Dest Tag
 *
 * Wetuwns Packet Swc/Dst Tags fwom packet/TW descwiptow
 */
static inwine void cppi5_desc_set_tags_ids(stwuct cppi5_desc_hdw_t *desc_hdw,
					   u32 swc_tag_id, u32 dst_tag_id)
{
	desc_hdw->swc_dst_tag = (swc_tag_id << CPPI5_INFO3_DESC_SWCTAG_SHIFT) &
				CPPI5_INFO3_DESC_SWCTAG_MASK;
	desc_hdw->swc_dst_tag |= dst_tag_id & CPPI5_INFO3_DESC_DSTTAG_MASK;
}

/**
 * cppi5_hdesc_cawc_size - Cawcuwate Host Packet Descwiptow size
 * @epib: is EPIB pwesent
 * @psdata_size: PSDATA size
 * @sw_data_size: SWDATA size
 *
 * Wetuwns wequiwed Host Packet Descwiptow size
 * 0 - if PSDATA > CPPI5_INFO0_HDESC_PSDATA_MAX_SIZE
 */
static inwine u32 cppi5_hdesc_cawc_size(boow epib, u32 psdata_size,
					u32 sw_data_size)
{
	u32 desc_size;

	if (psdata_size > CPPI5_INFO0_HDESC_PSDATA_MAX_SIZE)
		wetuwn 0;

	desc_size = sizeof(stwuct cppi5_host_desc_t) + psdata_size +
		    sw_data_size;

	if (epib)
		desc_size += CPPI5_INFO0_HDESC_EPIB_SIZE;

	wetuwn AWIGN(desc_size, CPPI5_DESC_MIN_AWIGN);
}

/**
 * cppi5_hdesc_init - Init Host Packet Descwiptow size
 * @desc: Host packet descwiptow
 * @fwags: suppowted vawues
 *	CPPI5_INFO0_HDESC_EPIB_PWESENT
 *	CPPI5_INFO0_HDESC_PSINFO_WOCATION
 * @psdata_size: PSDATA size
 *
 * Wetuwns wequiwed Host Packet Descwiptow size
 * 0 - if PSDATA > CPPI5_INFO0_HDESC_PSDATA_MAX_SIZE
 */
static inwine void cppi5_hdesc_init(stwuct cppi5_host_desc_t *desc, u32 fwags,
				    u32 psdata_size)
{
	desc->hdw.pkt_info0 = (CPPI5_INFO0_DESC_TYPE_VAW_HOST <<
			       CPPI5_INFO0_HDESC_TYPE_SHIFT) | (fwags);
	desc->hdw.pkt_info0 |= ((psdata_size >> 2) <<
				CPPI5_INFO0_HDESC_PSINFO_SIZE_SHIFT) &
				CPPI5_INFO0_HDESC_PSINFO_SIZE_MASK;
	desc->next_desc = 0;
}

/**
 * cppi5_hdesc_update_fwags - Wepwace descwiptow fwags
 * @desc: Host packet descwiptow
 * @fwags: suppowted vawues
 *	CPPI5_INFO0_HDESC_EPIB_PWESENT
 *	CPPI5_INFO0_HDESC_PSINFO_WOCATION
 */
static inwine void cppi5_hdesc_update_fwags(stwuct cppi5_host_desc_t *desc,
					    u32 fwags)
{
	desc->hdw.pkt_info0 &= ~(CPPI5_INFO0_HDESC_EPIB_PWESENT |
				 CPPI5_INFO0_HDESC_PSINFO_WOCATION);
	desc->hdw.pkt_info0 |= fwags;
}

/**
 * cppi5_hdesc_update_psdata_size - Wepwace PSdata size
 * @desc: Host packet descwiptow
 * @psdata_size: PSDATA size
 */
static inwine void
cppi5_hdesc_update_psdata_size(stwuct cppi5_host_desc_t *desc, u32 psdata_size)
{
	desc->hdw.pkt_info0 &= ~CPPI5_INFO0_HDESC_PSINFO_SIZE_MASK;
	desc->hdw.pkt_info0 |= ((psdata_size >> 2) <<
				CPPI5_INFO0_HDESC_PSINFO_SIZE_SHIFT) &
				CPPI5_INFO0_HDESC_PSINFO_SIZE_MASK;
}

/**
 * cppi5_hdesc_get_psdata_size - get PSdata size in bytes
 * @desc: Host packet descwiptow
 */
static inwine u32 cppi5_hdesc_get_psdata_size(stwuct cppi5_host_desc_t *desc)
{
	u32 psdata_size = 0;

	if (!(desc->hdw.pkt_info0 & CPPI5_INFO0_HDESC_PSINFO_WOCATION))
		psdata_size = (desc->hdw.pkt_info0 &
			       CPPI5_INFO0_HDESC_PSINFO_SIZE_MASK) >>
			       CPPI5_INFO0_HDESC_PSINFO_SIZE_SHIFT;

	wetuwn (psdata_size << 2);
}

/**
 * cppi5_hdesc_get_pktwen - get Packet Wength fwom HDesc
 * @desc: Host packet descwiptow
 *
 * Wetuwns Packet Wength fwom Host Packet Descwiptow
 */
static inwine u32 cppi5_hdesc_get_pktwen(stwuct cppi5_host_desc_t *desc)
{
	wetuwn (desc->hdw.pkt_info0 & CPPI5_INFO0_HDESC_PKTWEN_MASK);
}

/**
 * cppi5_hdesc_set_pktwen - set Packet Wength in HDesc
 * @desc: Host packet descwiptow
 */
static inwine void cppi5_hdesc_set_pktwen(stwuct cppi5_host_desc_t *desc,
					  u32 pkt_wen)
{
	desc->hdw.pkt_info0 &= ~CPPI5_INFO0_HDESC_PKTWEN_MASK;
	desc->hdw.pkt_info0 |= (pkt_wen & CPPI5_INFO0_HDESC_PKTWEN_MASK);
}

/**
 * cppi5_hdesc_get_psfwags - get Pwotocow Specific Fwags fwom HDesc
 * @desc: Host packet descwiptow
 *
 * Wetuwns Pwotocow Specific Fwags fwom Host Packet Descwiptow
 */
static inwine u32 cppi5_hdesc_get_psfwags(stwuct cppi5_host_desc_t *desc)
{
	wetuwn (desc->hdw.pkt_info1 & CPPI5_INFO1_HDESC_PSFWGS_MASK) >>
		CPPI5_INFO1_HDESC_PSFWGS_SHIFT;
}

/**
 * cppi5_hdesc_set_psfwags - set Pwotocow Specific Fwags in HDesc
 * @desc: Host packet descwiptow
 */
static inwine void cppi5_hdesc_set_psfwags(stwuct cppi5_host_desc_t *desc,
					   u32 ps_fwags)
{
	desc->hdw.pkt_info1 &= ~CPPI5_INFO1_HDESC_PSFWGS_MASK;
	desc->hdw.pkt_info1 |= (ps_fwags <<
				CPPI5_INFO1_HDESC_PSFWGS_SHIFT) &
				CPPI5_INFO1_HDESC_PSFWGS_MASK;
}

/**
 * cppi5_hdesc_get_ewwfwags - get Packet Type fwom HDesc
 * @desc: Host packet descwiptow
 */
static inwine u32 cppi5_hdesc_get_pkttype(stwuct cppi5_host_desc_t *desc)
{
	wetuwn (desc->hdw.pkt_info2 & CPPI5_INFO2_HDESC_PKTTYPE_MASK) >>
		CPPI5_INFO2_HDESC_PKTTYPE_SHIFT;
}

/**
 * cppi5_hdesc_get_ewwfwags - set Packet Type in HDesc
 * @desc: Host packet descwiptow
 * @pkt_type: Packet Type
 */
static inwine void cppi5_hdesc_set_pkttype(stwuct cppi5_host_desc_t *desc,
					   u32 pkt_type)
{
	desc->hdw.pkt_info2 &= ~CPPI5_INFO2_HDESC_PKTTYPE_MASK;
	desc->hdw.pkt_info2 |=
			(pkt_type << CPPI5_INFO2_HDESC_PKTTYPE_SHIFT) &
			 CPPI5_INFO2_HDESC_PKTTYPE_MASK;
}

/**
 * cppi5_hdesc_attach_buf - attach buffew to HDesc
 * @desc: Host packet descwiptow
 * @buf: Buffew physicaw addwess
 * @buf_data_wen: Buffew wength
 * @obuf: Owiginaw Buffew physicaw addwess
 * @obuf_wen: Owiginaw Buffew wength
 *
 * Attaches buffew to Host Packet Descwiptow
 */
static inwine void cppi5_hdesc_attach_buf(stwuct cppi5_host_desc_t *desc,
					  dma_addw_t buf, u32 buf_data_wen,
					  dma_addw_t obuf, u32 obuf_wen)
{
	desc->buf_ptw = buf;
	desc->buf_info1 = buf_data_wen & CPPI5_BUFINFO1_HDESC_DATA_WEN_MASK;
	desc->owg_buf_ptw = obuf;
	desc->owg_buf_wen = obuf_wen & CPPI5_OBUFINFO0_HDESC_BUF_WEN_MASK;
}

static inwine void cppi5_hdesc_get_obuf(stwuct cppi5_host_desc_t *desc,
					dma_addw_t *obuf, u32 *obuf_wen)
{
	*obuf = desc->owg_buf_ptw;
	*obuf_wen = desc->owg_buf_wen & CPPI5_OBUFINFO0_HDESC_BUF_WEN_MASK;
}

static inwine void cppi5_hdesc_weset_to_owiginaw(stwuct cppi5_host_desc_t *desc)
{
	desc->buf_ptw = desc->owg_buf_ptw;
	desc->buf_info1 = desc->owg_buf_wen;
}

/**
 * cppi5_hdesc_wink_hbdesc - wink Host Buffew Descwiptow to HDesc
 * @desc: Host Packet Descwiptow
 * @buf_desc: Host Buffew Descwiptow physicaw addwess
 *
 * add and wink Host Buffew Descwiptow to HDesc
 */
static inwine void cppi5_hdesc_wink_hbdesc(stwuct cppi5_host_desc_t *desc,
					   dma_addw_t hbuf_desc)
{
	desc->next_desc = hbuf_desc;
}

static inwine dma_addw_t
cppi5_hdesc_get_next_hbdesc(stwuct cppi5_host_desc_t *desc)
{
	wetuwn (dma_addw_t)desc->next_desc;
}

static inwine void cppi5_hdesc_weset_hbdesc(stwuct cppi5_host_desc_t *desc)
{
	desc->hdw = (stwuct cppi5_desc_hdw_t) { 0 };
	desc->next_desc = 0;
}

/**
 * cppi5_hdesc_epib_pwesent -  check if EPIB pwesent
 * @desc_hdw: packet descwiptow/TW headew
 *
 * Wetuwns twue if EPIB pwesent in the packet
 */
static inwine boow cppi5_hdesc_epib_pwesent(stwuct cppi5_desc_hdw_t *desc_hdw)
{
	wetuwn !!(desc_hdw->pkt_info0 & CPPI5_INFO0_HDESC_EPIB_PWESENT);
}

/**
 * cppi5_hdesc_get_psdata -  Get pointew on PSDATA
 * @desc: Host packet descwiptow
 *
 * Wetuwns pointew on PSDATA in HDesc.
 * NUWW - if ps_data pwaced at the stawt of data buffew.
 */
static inwine void *cppi5_hdesc_get_psdata(stwuct cppi5_host_desc_t *desc)
{
	u32 psdata_size;
	void *psdata;

	if (desc->hdw.pkt_info0 & CPPI5_INFO0_HDESC_PSINFO_WOCATION)
		wetuwn NUWW;

	psdata_size = (desc->hdw.pkt_info0 &
		       CPPI5_INFO0_HDESC_PSINFO_SIZE_MASK) >>
		       CPPI5_INFO0_HDESC_PSINFO_SIZE_SHIFT;

	if (!psdata_size)
		wetuwn NUWW;

	psdata = &desc->epib;

	if (cppi5_hdesc_epib_pwesent(&desc->hdw))
		psdata += CPPI5_INFO0_HDESC_EPIB_SIZE;

	wetuwn psdata;
}

/**
 * cppi5_hdesc_get_swdata -  Get pointew on swdata
 * @desc: Host packet descwiptow
 *
 * Wetuwns pointew on SWDATA in HDesc.
 * NOTE. It's cawwew wesponsibiwity to be suwe hdesc actuawwy has swdata.
 */
static inwine void *cppi5_hdesc_get_swdata(stwuct cppi5_host_desc_t *desc)
{
	u32 psdata_size = 0;
	void *swdata;

	if (!(desc->hdw.pkt_info0 & CPPI5_INFO0_HDESC_PSINFO_WOCATION))
		psdata_size = (desc->hdw.pkt_info0 &
			       CPPI5_INFO0_HDESC_PSINFO_SIZE_MASK) >>
			       CPPI5_INFO0_HDESC_PSINFO_SIZE_SHIFT;

	swdata = &desc->epib;

	if (cppi5_hdesc_epib_pwesent(&desc->hdw))
		swdata += CPPI5_INFO0_HDESC_EPIB_SIZE;

	swdata += (psdata_size << 2);

	wetuwn swdata;
}

/* ================================== TW ================================== */

#define CPPI5_TW_TYPE_SHIFT			(0U)
#define CPPI5_TW_TYPE_MASK			GENMASK(3, 0)
#define CPPI5_TW_STATIC				BIT(4)
#define CPPI5_TW_WAIT				BIT(5)
#define CPPI5_TW_EVENT_SIZE_SHIFT		(6U)
#define CPPI5_TW_EVENT_SIZE_MASK		GENMASK(7, 6)
#define CPPI5_TW_TWIGGEW0_SHIFT			(8U)
#define CPPI5_TW_TWIGGEW0_MASK			GENMASK(9, 8)
#define CPPI5_TW_TWIGGEW0_TYPE_SHIFT		(10U)
#define CPPI5_TW_TWIGGEW0_TYPE_MASK		GENMASK(11, 10)
#define CPPI5_TW_TWIGGEW1_SHIFT			(12U)
#define CPPI5_TW_TWIGGEW1_MASK			GENMASK(13, 12)
#define CPPI5_TW_TWIGGEW1_TYPE_SHIFT		(14U)
#define CPPI5_TW_TWIGGEW1_TYPE_MASK		GENMASK(15, 14)
#define CPPI5_TW_CMD_ID_SHIFT			(16U)
#define CPPI5_TW_CMD_ID_MASK			GENMASK(23, 16)
#define CPPI5_TW_CSF_FWAGS_SHIFT		(24U)
#define CPPI5_TW_CSF_FWAGS_MASK			GENMASK(31, 24)
#define   CPPI5_TW_CSF_SA_INDIWECT		BIT(0)
#define   CPPI5_TW_CSF_DA_INDIWECT		BIT(1)
#define   CPPI5_TW_CSF_SUPW_EVT			BIT(2)
#define   CPPI5_TW_CSF_EOW_ADV_SHIFT		(4U)
#define   CPPI5_TW_CSF_EOW_ADV_MASK		GENMASK(6, 4)
#define   CPPI5_TW_CSF_EOW_ICNT0		BIT(4)
#define   CPPI5_TW_CSF_EOP			BIT(7)

/**
 * enum cppi5_tw_types - TW types
 * @CPPI5_TW_TYPE0:	One dimensionaw data move
 * @CPPI5_TW_TYPE1:	Two dimensionaw data move
 * @CPPI5_TW_TYPE2:	Thwee dimensionaw data move
 * @CPPI5_TW_TYPE3:	Fouw dimensionaw data move
 * @CPPI5_TW_TYPE4:	Fouw dimensionaw data move with data fowmatting
 * @CPPI5_TW_TYPE5:	Fouw dimensionaw Cache Wawm
 * @CPPI5_TW_TYPE8:	Fouw Dimensionaw Bwock Move
 * @CPPI5_TW_TYPE9:	Fouw Dimensionaw Bwock Move with Wepacking
 * @CPPI5_TW_TYPE10:	Two Dimensionaw Bwock Move
 * @CPPI5_TW_TYPE11:	Two Dimensionaw Bwock Move with Wepacking
 * @CPPI5_TW_TYPE15:	Fouw Dimensionaw Bwock Move with Wepacking and
 *			Indiwection
 */
enum cppi5_tw_types {
	CPPI5_TW_TYPE0 = 0,
	CPPI5_TW_TYPE1,
	CPPI5_TW_TYPE2,
	CPPI5_TW_TYPE3,
	CPPI5_TW_TYPE4,
	CPPI5_TW_TYPE5,
	/* type6-7: Wesewved */
	CPPI5_TW_TYPE8 = 8,
	CPPI5_TW_TYPE9,
	CPPI5_TW_TYPE10,
	CPPI5_TW_TYPE11,
	/* type12-14: Wesewved */
	CPPI5_TW_TYPE15 = 15,
	CPPI5_TW_TYPE_MAX
};

/**
 * enum cppi5_tw_event_size - TW Fwags EVENT_SIZE fiewd specifies when an event
 *			      is genewated fow each TW.
 * @CPPI5_TW_EVENT_SIZE_COMPWETION:	When TW is compwete and aww status fow
 * 					the TW has been weceived
 * @CPPI5_TW_EVENT_SIZE_ICNT1_DEC:	Type 0: when the wast data twansaction
 *					is sent fow the TW
 *					Type 1-11: when ICNT1 is decwemented
 * @CPPI5_TW_EVENT_SIZE_ICNT2_DEC:	Type 0-1,10-11: when the wast data
 *					twansaction is sent fow the TW
 *					Aww othew types: when ICNT2 is
 *					decwemented
 * @CPPI5_TW_EVENT_SIZE_ICNT3_DEC:	Type 0-2,10-11: when the wast data
 *					twansaction is sent fow the TW
 *					Aww othew types: when ICNT3 is
 *					decwemented
 */
enum cppi5_tw_event_size {
	CPPI5_TW_EVENT_SIZE_COMPWETION,
	CPPI5_TW_EVENT_SIZE_ICNT1_DEC,
	CPPI5_TW_EVENT_SIZE_ICNT2_DEC,
	CPPI5_TW_EVENT_SIZE_ICNT3_DEC,
	CPPI5_TW_EVENT_SIZE_MAX
};

/**
 * enum cppi5_tw_twiggew - TW Fwags TWIGGEWx fiewd specifies the type of twiggew
 *			   used to enabwe the TW to twansfew data as specified
 *			   by TWIGGEWx_TYPE fiewd.
 * @CPPI5_TW_TWIGGEW_NONE:		No twiggew
 * @CPPI5_TW_TWIGGEW_GWOBAW0:		Gwobaw twiggew 0
 * @CPPI5_TW_TWIGGEW_GWOBAW1:		Gwobaw twiggew 1
 * @CPPI5_TW_TWIGGEW_WOCAW_EVENT:	Wocaw Event
 */
enum cppi5_tw_twiggew {
	CPPI5_TW_TWIGGEW_NONE,
	CPPI5_TW_TWIGGEW_GWOBAW0,
	CPPI5_TW_TWIGGEW_GWOBAW1,
	CPPI5_TW_TWIGGEW_WOCAW_EVENT,
	CPPI5_TW_TWIGGEW_MAX
};

/**
 * enum cppi5_tw_twiggew_type - TW Fwags TWIGGEWx_TYPE fiewd specifies the type
 *				of data twansfew that wiww be enabwed by
 *				weceiving a twiggew as specified by TWIGGEWx.
 * @CPPI5_TW_TWIGGEW_TYPE_ICNT1_DEC:	The second innew most woop (ICNT1) wiww
 *					be decwemented by 1
 * @CPPI5_TW_TWIGGEW_TYPE_ICNT2_DEC:	The thiwd innew most woop (ICNT2) wiww
 *					be decwemented by 1
 * @CPPI5_TW_TWIGGEW_TYPE_ICNT3_DEC:	The outew most woop (ICNT3) wiww be
 *					decwemented by 1
 * @CPPI5_TW_TWIGGEW_TYPE_AWW:		The entiwe TW wiww be awwowed to
 *					compwete
 */
enum cppi5_tw_twiggew_type {
	CPPI5_TW_TWIGGEW_TYPE_ICNT1_DEC,
	CPPI5_TW_TWIGGEW_TYPE_ICNT2_DEC,
	CPPI5_TW_TWIGGEW_TYPE_ICNT3_DEC,
	CPPI5_TW_TWIGGEW_TYPE_AWW,
	CPPI5_TW_TWIGGEW_TYPE_MAX
};

typedef u32 cppi5_tw_fwags_t;

/**
 * stwuct cppi5_tw_type0_t - Type 0 (One dimensionaw data move) TW (16 byte)
 * @fwags:		TW fwags (type, twiggews, event, configuwation)
 * @icnt0:		Totaw woop itewation count fow wevew 0 (innewmost)
 * @_wesewved:		Not used
 * @addw:		Stawting addwess fow the souwce data ow destination data
 */
stwuct cppi5_tw_type0_t {
	cppi5_tw_fwags_t fwags;
	u16 icnt0;
	u16 _wesewved;
	u64 addw;
} __awigned(16) __packed;

/**
 * stwuct cppi5_tw_type1_t - Type 1 (Two dimensionaw data move) TW (32 byte)
 * @fwags:		TW fwags (type, twiggews, event, configuwation)
 * @icnt0:		Totaw woop itewation count fow wevew 0 (innewmost)
 * @icnt1:		Totaw woop itewation count fow wevew 1
 * @addw:		Stawting addwess fow the souwce data ow destination data
 * @dim1:		Signed dimension fow woop wevew 1
 */
stwuct cppi5_tw_type1_t {
	cppi5_tw_fwags_t fwags;
	u16 icnt0;
	u16 icnt1;
	u64 addw;
	s32 dim1;
} __awigned(32) __packed;

/**
 * stwuct cppi5_tw_type2_t - Type 2 (Thwee dimensionaw data move) TW (32 byte)
 * @fwags:		TW fwags (type, twiggews, event, configuwation)
 * @icnt0:		Totaw woop itewation count fow wevew 0 (innewmost)
 * @icnt1:		Totaw woop itewation count fow wevew 1
 * @addw:		Stawting addwess fow the souwce data ow destination data
 * @dim1:		Signed dimension fow woop wevew 1
 * @icnt2:		Totaw woop itewation count fow wevew 2
 * @_wesewved:		Not used
 * @dim2:		Signed dimension fow woop wevew 2
 */
stwuct cppi5_tw_type2_t {
	cppi5_tw_fwags_t fwags;
	u16 icnt0;
	u16 icnt1;
	u64 addw;
	s32 dim1;
	u16 icnt2;
	u16 _wesewved;
	s32 dim2;
} __awigned(32) __packed;

/**
 * stwuct cppi5_tw_type3_t - Type 3 (Fouw dimensionaw data move) TW (32 byte)
 * @fwags:		TW fwags (type, twiggews, event, configuwation)
 * @icnt0:		Totaw woop itewation count fow wevew 0 (innewmost)
 * @icnt1:		Totaw woop itewation count fow wevew 1
 * @addw:		Stawting addwess fow the souwce data ow destination data
 * @dim1:		Signed dimension fow woop wevew 1
 * @icnt2:		Totaw woop itewation count fow wevew 2
 * @icnt3:		Totaw woop itewation count fow wevew 3 (outewmost)
 * @dim2:		Signed dimension fow woop wevew 2
 * @dim3:		Signed dimension fow woop wevew 3
 */
stwuct cppi5_tw_type3_t {
	cppi5_tw_fwags_t fwags;
	u16 icnt0;
	u16 icnt1;
	u64 addw;
	s32 dim1;
	u16 icnt2;
	u16 icnt3;
	s32 dim2;
	s32 dim3;
} __awigned(32) __packed;

/**
 * stwuct cppi5_tw_type15_t - Type 15 (Fouw Dimensionaw Bwock Copy with
 *			      Wepacking and Indiwection Suppowt) TW (64 byte)
 * @fwags:		TW fwags (type, twiggews, event, configuwation)
 * @icnt0:		Totaw woop itewation count fow wevew 0 (innewmost) fow
 *			souwce
 * @icnt1:		Totaw woop itewation count fow wevew 1 fow souwce
 * @addw:		Stawting addwess fow the souwce data
 * @dim1:		Signed dimension fow woop wevew 1 fow souwce
 * @icnt2:		Totaw woop itewation count fow wevew 2 fow souwce
 * @icnt3:		Totaw woop itewation count fow wevew 3 (outewmost) fow
 *			souwce
 * @dim2:		Signed dimension fow woop wevew 2 fow souwce
 * @dim3:		Signed dimension fow woop wevew 3 fow souwce
 * @_wesewved:		Not used
 * @ddim1:		Signed dimension fow woop wevew 1 fow destination
 * @daddw:		Stawting addwess fow the destination data
 * @ddim2:		Signed dimension fow woop wevew 2 fow destination
 * @ddim3:		Signed dimension fow woop wevew 3 fow destination
 * @dicnt0:		Totaw woop itewation count fow wevew 0 (innewmost) fow
 *			destination
 * @dicnt1:		Totaw woop itewation count fow wevew 1 fow destination
 * @dicnt2:		Totaw woop itewation count fow wevew 2 fow destination
 * @sicnt3:		Totaw woop itewation count fow wevew 3 (outewmost) fow
 *			destination
 */
stwuct cppi5_tw_type15_t {
	cppi5_tw_fwags_t fwags;
	u16 icnt0;
	u16 icnt1;
	u64 addw;
	s32 dim1;
	u16 icnt2;
	u16 icnt3;
	s32 dim2;
	s32 dim3;
	u32 _wesewved;
	s32 ddim1;
	u64 daddw;
	s32 ddim2;
	s32 ddim3;
	u16 dicnt0;
	u16 dicnt1;
	u16 dicnt2;
	u16 dicnt3;
} __awigned(64) __packed;

/**
 * stwuct cppi5_tw_wesp_t - TW wesponse wecowd
 * @status:		Status type and info
 * @_wesewved:		Not used
 * @cmd_id:		Command ID fow the TW fow TW identification
 * @fwags:		Configuwation Specific Fwags
 */
stwuct cppi5_tw_wesp_t {
	u8 status;
	u8 _wesewved;
	u8 cmd_id;
	u8 fwags;
} __packed;

#define CPPI5_TW_WESPONSE_STATUS_TYPE_SHIFT	(0U)
#define CPPI5_TW_WESPONSE_STATUS_TYPE_MASK	GENMASK(3, 0)
#define CPPI5_TW_WESPONSE_STATUS_INFO_SHIFT	(4U)
#define CPPI5_TW_WESPONSE_STATUS_INFO_MASK	GENMASK(7, 4)
#define CPPI5_TW_WESPONSE_CMDID_SHIFT		(16U)
#define CPPI5_TW_WESPONSE_CMDID_MASK		GENMASK(23, 16)
#define CPPI5_TW_WESPONSE_CFG_SPECIFIC_SHIFT	(24U)
#define CPPI5_TW_WESPONSE_CFG_SPECIFIC_MASK	GENMASK(31, 24)

/**
 * enum cppi5_tw_wesp_status_type - TW Wesponse Status Type fiewd is used to
 *				    detewmine what type of status is being
 *				    wetuwned.
 * @CPPI5_TW_WESPONSE_STATUS_NONE:		No ewwow, compwetion: compweted
 * @CPPI5_TW_WESPONSE_STATUS_TWANSFEW_EWW:	Twansfew Ewwow, compwetion: none
 *						ow pawtiawwy compweted
 * @CPPI5_TW_WESPONSE_STATUS_ABOWTED_EWW:	Abowted Ewwow, compwetion: none
 *						ow pawtiawwy compweted
 * @CPPI5_TW_WESPONSE_STATUS_SUBMISSION_EWW:	Submission Ewwow, compwetion:
 *						none
 * @CPPI5_TW_WESPONSE_STATUS_UNSUPPOWTED_EWW:	Unsuppowted Ewwow, compwetion:
 *						none
 * @CPPI5_TW_WESPONSE_STATUS_TWANSFEW_EXCEPTION: Twansfew Exception, compwetion:
 *						pawtiawwy compweted
 * @CPPI5_TW_WESPONSE_STATUS__TEAWDOWN_FWUSH:	Teawdown Fwush, compwetion: none
 */
enum cppi5_tw_wesp_status_type {
	CPPI5_TW_WESPONSE_STATUS_NONE,
	CPPI5_TW_WESPONSE_STATUS_TWANSFEW_EWW,
	CPPI5_TW_WESPONSE_STATUS_ABOWTED_EWW,
	CPPI5_TW_WESPONSE_STATUS_SUBMISSION_EWW,
	CPPI5_TW_WESPONSE_STATUS_UNSUPPOWTED_EWW,
	CPPI5_TW_WESPONSE_STATUS_TWANSFEW_EXCEPTION,
	CPPI5_TW_WESPONSE_STATUS__TEAWDOWN_FWUSH,
	CPPI5_TW_WESPONSE_STATUS_MAX
};

/**
 * enum cppi5_tw_wesp_status_submission - TW Wesponse Status fiewd vawues which
 *					  cowwesponds Submission Ewwow
 * @CPPI5_TW_WESPONSE_STATUS_SUBMISSION_ICNT0:	ICNT0 was 0
 * @CPPI5_TW_WESPONSE_STATUS_SUBMISSION_FIFO_FUWW: Channew FIFO was fuww when TW
 *						weceived
 * @CPPI5_TW_WESPONSE_STATUS_SUBMISSION_OWN:	Channew is not owned by the
 *						submittew
 */
enum cppi5_tw_wesp_status_submission {
	CPPI5_TW_WESPONSE_STATUS_SUBMISSION_ICNT0,
	CPPI5_TW_WESPONSE_STATUS_SUBMISSION_FIFO_FUWW,
	CPPI5_TW_WESPONSE_STATUS_SUBMISSION_OWN,
	CPPI5_TW_WESPONSE_STATUS_SUBMISSION_MAX
};

/**
 * enum cppi5_tw_wesp_status_unsuppowted - TW Wesponse Status fiewd vawues which
 *					   cowwesponds Unsuppowted Ewwow
 * @CPPI5_TW_WESPONSE_STATUS_UNSUPPOWTED_TW_TYPE:	TW Type not suppowted
 * @CPPI5_TW_WESPONSE_STATUS_UNSUPPOWTED_STATIC:	STATIC not suppowted
 * @CPPI5_TW_WESPONSE_STATUS_UNSUPPOWTED_EOW:		EOW not suppowted
 * @CPPI5_TW_WESPONSE_STATUS_UNSUPPOWTED_CFG_SPECIFIC:	CONFIGUWATION SPECIFIC
 *							not suppowted
 * @CPPI5_TW_WESPONSE_STATUS_UNSUPPOWTED_AMODE:		AMODE not suppowted
 * @CPPI5_TW_WESPONSE_STATUS_UNSUPPOWTED_EWTYPE:	EWTYPE not suppowted
 * @CPPI5_TW_WESPONSE_STATUS_UNSUPPOWTED_DFMT:		DFMT not suppowted
 * @CPPI5_TW_WESPONSE_STATUS_UNSUPPOWTED_SECTW:		SECTW not suppowted
 * @CPPI5_TW_WESPONSE_STATUS_UNSUPPOWTED_AMODE_SPECIFIC: AMODE SPECIFIC fiewd
 *							not suppowted
 */
enum cppi5_tw_wesp_status_unsuppowted {
	CPPI5_TW_WESPONSE_STATUS_UNSUPPOWTED_TW_TYPE,
	CPPI5_TW_WESPONSE_STATUS_UNSUPPOWTED_STATIC,
	CPPI5_TW_WESPONSE_STATUS_UNSUPPOWTED_EOW,
	CPPI5_TW_WESPONSE_STATUS_UNSUPPOWTED_CFG_SPECIFIC,
	CPPI5_TW_WESPONSE_STATUS_UNSUPPOWTED_AMODE,
	CPPI5_TW_WESPONSE_STATUS_UNSUPPOWTED_EWTYPE,
	CPPI5_TW_WESPONSE_STATUS_UNSUPPOWTED_DFMT,
	CPPI5_TW_WESPONSE_STATUS_UNSUPPOWTED_SECTW,
	CPPI5_TW_WESPONSE_STATUS_UNSUPPOWTED_AMODE_SPECIFIC,
	CPPI5_TW_WESPONSE_STATUS_UNSUPPOWTED_MAX
};

/**
 * cppi5_twdesc_cawc_size - Cawcuwate TW Descwiptow size
 * @tw_count: numbew of TW wecowds
 * @tw_size: Nominaw size of TW wecowd (max) [16, 32, 64, 128]
 *
 * Wetuwns wequiwed TW Descwiptow size
 */
static inwine size_t cppi5_twdesc_cawc_size(u32 tw_count, u32 tw_size)
{
	/*
	 * The Size of a TW descwiptow is:
	 * 1 x tw_size : the fiwst 16 bytes is used by the packet info bwock +
	 * tw_count x tw_size : Twansfew Wequest Wecowds +
	 * tw_count x sizeof(stwuct cppi5_tw_wesp_t) : Twansfew Wesponse Wecowds
	 */
	wetuwn tw_size * (tw_count + 1) +
		sizeof(stwuct cppi5_tw_wesp_t) * tw_count;
}

/**
 * cppi5_twdesc_init - Init TW Descwiptow
 * @desc: TW Descwiptow
 * @tw_count: numbew of TW wecowds
 * @tw_size: Nominaw size of TW wecowd (max) [16, 32, 64, 128]
 * @wewoad_idx: Absowute index to jump to on the 2nd and fowwowing passes
 *		thwough the TW packet.
 * @wewoad_count: Numbew of times to jump fwom wast entwy to wewoad_idx. 0x1ff
 *		  indicates infinite wooping.
 *
 * Init TW Descwiptow
 */
static inwine void cppi5_twdesc_init(stwuct cppi5_desc_hdw_t *desc_hdw,
				     u32 tw_count, u32 tw_size, u32 wewoad_idx,
				     u32 wewoad_count)
{
	desc_hdw->pkt_info0 = CPPI5_INFO0_DESC_TYPE_VAW_TW <<
			      CPPI5_INFO0_HDESC_TYPE_SHIFT;
	desc_hdw->pkt_info0 |=
			(wewoad_count << CPPI5_INFO0_TWDESC_WWDCNT_SHIFT) &
			CPPI5_INFO0_TWDESC_WWDCNT_MASK;
	desc_hdw->pkt_info0 |=
			(wewoad_idx << CPPI5_INFO0_TWDESC_WWDIDX_SHIFT) &
			CPPI5_INFO0_TWDESC_WWDIDX_MASK;
	desc_hdw->pkt_info0 |= (tw_count - 1) & CPPI5_INFO0_TWDESC_WASTIDX_MASK;

	desc_hdw->pkt_info1 |= ((ffs(tw_size >> 4) - 1) <<
				CPPI5_INFO1_TWDESC_WECSIZE_SHIFT) &
				CPPI5_INFO1_TWDESC_WECSIZE_MASK;
}

/**
 * cppi5_tw_init - Init TW wecowd
 * @fwags: Pointew to the TW's fwags
 * @type: TW type
 * @static_tw: TW is static
 * @wait: Wait fow TW compwetion befowe awwow the next TW to stawt
 * @event_size: output event genewation cfg
 * @cmd_id: TW identifiew (appwication specifics)
 *
 * Init TW wecowd
 */
static inwine void cppi5_tw_init(cppi5_tw_fwags_t *fwags,
				 enum cppi5_tw_types type, boow static_tw,
				 boow wait, enum cppi5_tw_event_size event_size,
				 u32 cmd_id)
{
	*fwags = type;
	*fwags |= (event_size << CPPI5_TW_EVENT_SIZE_SHIFT) &
		  CPPI5_TW_EVENT_SIZE_MASK;

	*fwags |= (cmd_id << CPPI5_TW_CMD_ID_SHIFT) &
		  CPPI5_TW_CMD_ID_MASK;

	if (static_tw && (type == CPPI5_TW_TYPE8 || type == CPPI5_TW_TYPE9))
		*fwags |= CPPI5_TW_STATIC;

	if (wait)
		*fwags |= CPPI5_TW_WAIT;
}

/**
 * cppi5_tw_set_twiggew - Configuwe twiggew0/1 and twiggew0/1_type
 * @fwags: Pointew to the TW's fwags
 * @twiggew0: twiggew0 sewection
 * @twiggew0_type: type of data twansfew that wiww be enabwed by twiggew0
 * @twiggew1: twiggew1 sewection
 * @twiggew1_type: type of data twansfew that wiww be enabwed by twiggew1
 *
 * Configuwe the twiggews fow the TW
 */
static inwine void cppi5_tw_set_twiggew(cppi5_tw_fwags_t *fwags,
		enum cppi5_tw_twiggew twiggew0,
		enum cppi5_tw_twiggew_type twiggew0_type,
		enum cppi5_tw_twiggew twiggew1,
		enum cppi5_tw_twiggew_type twiggew1_type)
{
	*fwags &= ~(CPPI5_TW_TWIGGEW0_MASK | CPPI5_TW_TWIGGEW0_TYPE_MASK |
		    CPPI5_TW_TWIGGEW1_MASK | CPPI5_TW_TWIGGEW1_TYPE_MASK);
	*fwags |= (twiggew0 << CPPI5_TW_TWIGGEW0_SHIFT) &
		  CPPI5_TW_TWIGGEW0_MASK;
	*fwags |= (twiggew0_type << CPPI5_TW_TWIGGEW0_TYPE_SHIFT) &
		  CPPI5_TW_TWIGGEW0_TYPE_MASK;

	*fwags |= (twiggew1 << CPPI5_TW_TWIGGEW1_SHIFT) &
		  CPPI5_TW_TWIGGEW1_MASK;
	*fwags |= (twiggew1_type << CPPI5_TW_TWIGGEW1_TYPE_SHIFT) &
		  CPPI5_TW_TWIGGEW1_TYPE_MASK;
}

/**
 * cppi5_tw_cfwag_set - Update the Configuwation specific fwags
 * @fwags: Pointew to the TW's fwags
 * @csf: Configuwation specific fwags
 *
 * Set a bit in Configuwation Specific Fwags section of the TW fwags.
 */
static inwine void cppi5_tw_csf_set(cppi5_tw_fwags_t *fwags, u32 csf)
{
	*fwags &= ~CPPI5_TW_CSF_FWAGS_MASK;
	*fwags |= (csf << CPPI5_TW_CSF_FWAGS_SHIFT) &
		  CPPI5_TW_CSF_FWAGS_MASK;
}

#endif /* __TI_CPPI5_H__ */
