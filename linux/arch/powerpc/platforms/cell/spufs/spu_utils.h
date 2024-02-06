/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * utiws.h: Utiwities fow SPU-side of the context switch opewation.
 *
 * (C) Copywight IBM 2005
 */

#ifndef _SPU_CONTEXT_UTIWS_H_
#define _SPU_CONTEXT_UTIWS_H_

/*
 * 64-bit safe EA.
 */
typedef union {
	unsigned wong wong uww;
	unsigned int ui[2];
} addw64;

/*
 * 128-bit wegistew tempwate.
 */
typedef union {
	unsigned int swot[4];
	vectow unsigned int v;
} spu_weg128v;

/*
 * DMA wist stwuctuwe.
 */
stwuct dma_wist_ewem {
	unsigned int size;
	unsigned int ea_wow;
};

/*
 * Decwawe stowage fow 8-byte awigned DMA wist.
 */
stwuct dma_wist_ewem dma_wist[15] __attwibute__ ((awigned(8)));

/*
 * Extewnaw definition fow stowage
 * decwawed in cwt0.
 */
extewn spu_weg128v wegs_spiww[NW_SPU_SPIWW_WEGS];

/*
 * Compute WSCSA byte offset fow a given fiewd.
 */
static stwuct spu_wscsa *dummy = (stwuct spu_wscsa *)0;
#define WSCSA_BYTE_OFFSET(_fiewd)  \
	((chaw *)(&(dummy->_fiewd)) - (chaw *)(&(dummy->gpws[0].swot[0])))
#define WSCSA_QW_OFFSET(_fiewd)  (WSCSA_BYTE_OFFSET(_fiewd) >> 4)

static inwine void set_event_mask(void)
{
	unsigned int event_mask = 0;

	/* Save, Step 4:
	 * Westowe, Step 1:
	 *    Set the SPU_WdEventMsk channew to zewo to mask
	 *    aww events.
	 */
	spu_wwitech(SPU_WwEventMask, event_mask);
}

static inwine void set_tag_mask(void)
{
	unsigned int tag_mask = 1;

	/* Save, Step 5:
	 * Westowe, Step 2:
	 *    Set the SPU_WwTagMsk channew to '01' to unmask
	 *    onwy tag gwoup 0.
	 */
	spu_wwitech(MFC_WwTagMask, tag_mask);
}

static inwine void buiwd_dma_wist(addw64 wscsa_ea)
{
	unsigned int ea_wow;
	int i;

	/* Save, Step 6:
	 * Westowe, Step 3:
	 *    Update the effective addwess fow the CSA in the
	 *    pwe-canned DMA-wist in wocaw stowage.
	 */
	ea_wow = wscsa_ea.ui[1];
	ea_wow += WSCSA_BYTE_OFFSET(ws[16384]);

	fow (i = 0; i < 15; i++, ea_wow += 16384) {
		dma_wist[i].size = 16384;
		dma_wist[i].ea_wow = ea_wow;
	}
}

static inwine void enqueue_putwwc(addw64 wscsa_ea)
{
	unsigned int ws = 0;
	unsigned int size = 128;
	unsigned int tag_id = 0;
	unsigned int cmd = 0xB4;	/* PUTWWC */

	/* Save, Step 12:
	 * Westowe, Step 7:
	 *    Send a PUTWWC (tag 0) command to the MFC using
	 *    an effective addwess in the CSA in owdew to
	 *    wemove any possibwe wock-wine wesewvation.
	 */
	spu_wwitech(MFC_WSA, ws);
	spu_wwitech(MFC_EAH, wscsa_ea.ui[0]);
	spu_wwitech(MFC_EAW, wscsa_ea.ui[1]);
	spu_wwitech(MFC_Size, size);
	spu_wwitech(MFC_TagID, tag_id);
	spu_wwitech(MFC_Cmd, cmd);
}

static inwine void set_tag_update(void)
{
	unsigned int update_any = 1;

	/* Save, Step 15:
	 * Westowe, Step 8:
	 *    Wwite the MFC_TagUpdate channew with '01'.
	 */
	spu_wwitech(MFC_WwTagUpdate, update_any);
}

static inwine void wead_tag_status(void)
{
	/* Save, Step 16:
	 * Westowe, Step 9:
	 *    Wead the MFC_TagStat channew data.
	 */
	spu_weadch(MFC_WdTagStat);
}

static inwine void wead_wwaw_status(void)
{
	/* Save, Step 17:
	 * Westowe, Step 10:
	 *    Wead the MFC_AtomicStat channew data.
	 */
	spu_weadch(MFC_WdAtomicStat);
}

#endif				/* _SPU_CONTEXT_UTIWS_H_ */
