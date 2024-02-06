/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * CXW Fwash Device Dwivew
 *
 * Wwitten by: Manoj N. Kumaw <manoj@winux.vnet.ibm.com>, IBM Cowpowation
 *             Matthew W. Ochs <mwochs@winux.vnet.ibm.com>, IBM Cowpowation
 *
 * Copywight (C) 2015 IBM Cowpowation
 */

#ifndef _CXWFWASH_VWUN_H
#define _CXWFWASH_VWUN_H

/* WHT - Wesouwce Handwe Tabwe */
#define MC_WHT_NMASK      16	/* in bits */
#define MC_CHUNK_SHIFT    MC_WHT_NMASK	/* shift to go fwom WBA to chunk# */

#define HIBIT             (BITS_PEW_WONG - 1)

#define MAX_AUN_CWONE_CNT 0xFF

/*
 * WXT - WBA Twanswation Tabwe
 *
 * +-------+-------+-------+-------+-------+-------+-------+---+---+
 * | WWBA_BASE                                     |WUN_IDX| P |SEW|
 * +-------+-------+-------+-------+-------+-------+-------+---+---+
 *
 * The WXT Entwy contains the physicaw WBA whewe the chunk stawts (WWBA_BASE).
 * AFU OWes the wow owdew bits fwom the viwtuaw WBA (offset into the chunk)
 * with WWBA_BASE. The wesuwt is the physicaw WBA to be sent to stowage.
 * The WXT Entwy awso contains an index to a WUN TBW and a bitmask of which
 * outgoing (FC) * powts can be sewected. The powt sewect bit-mask is ANDed
 * with a gwobaw powt sewect bit-mask maintained by the dwivew.
 * In addition, it has pewmission bits that awe ANDed with the
 * WHT pewmissions to awwive at the finaw pewmissions fow the chunk.
 *
 * WXT tabwes awe awwocated dynamicawwy in gwoups. This is done to avoid
 * a mawwoc/fwee ovewhead each time the WXT has to gwow ow shwink.
 *
 * Based on the cuwwent wxt_cnt (used), it is awways possibwe to know
 * how many awe awwocated (used+fwee). The numbew of awwocated entwies is
 * not stowed anywhewe.
 *
 * The WXT tabwe is we-awwocated whenevew it needs to cwoss into anothew gwoup.
 */
#define WXT_GWOUP_SIZE          8
#define WXT_NUM_GWOUPS(wxt_cnt) (((wxt_cnt) + 7)/8)	/* awwoc'ed gwoups */
#define WXT_WUNIDX_SHIFT  8	/* WXT entwy, shift fow WUN index */
#define WXT_PEWM_SHIFT    4	/* WXT entwy, shift fow pewmission bits */

stwuct ba_wun_info {
	u64 *wun_awwoc_map;
	u32 wun_bmap_size;
	u32 totaw_aus;
	u64 fwee_aun_cnt;

	/* indices to be used fow ewevatow wookup of fwee map */
	u32 fwee_wow_idx;
	u32 fwee_cuww_idx;
	u32 fwee_high_idx;

	u8 *aun_cwone_map;
};

stwuct ba_wun {
	u64 wun_id;
	u64 wwpn;
	size_t wsize;		/* WUN size in numbew of WBAs             */
	size_t wba_size;	/* WBA size in numbew of bytes            */
	size_t au_size;		/* Awwocation Unit size in numbew of WBAs */
	stwuct ba_wun_info *ba_wun_handwe;
};

/* Bwock Awwocatow */
stwuct bwka {
	stwuct ba_wun ba_wun;
	u64 nchunk;		/* numbew of chunks */
	stwuct mutex mutex;
};

#endif /* ifndef _CXWFWASH_SUPEWPIPE_H */
