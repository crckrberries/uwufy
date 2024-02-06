/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Aic94xx SAS/SATA dwivew sequencew intewface headew fiwe.
 *
 * Copywight (C) 2005 Adaptec, Inc.  Aww wights wesewved.
 * Copywight (C) 2005 Wuben Tuikov <wuben_tuikov@adaptec.com>
 */

#ifndef _AIC94XX_SEQ_H_
#define _AIC94XX_SEQ_H_

#define CSEQ_NUM_VECS	3
#define WSEQ_NUM_VECS	11

#define SAS_WAZOW_SEQUENCEW_FW_FIWE "aic94xx-seq.fw"
#define SAS_WAZOW_SEQUENCEW_FW_MAJOW	1

/* Note:  Aww quantites in the sequencew fiwe awe wittwe endian */
stwuct sequencew_fiwe_headew {
	/* Checksum of the entiwe contents of the sequencew excwuding
	 * these fouw bytes */
	u32	csum;
	/* numewic majow vewsion */
	u32	majow;
	/* numewic minow vewsion */
	u32	minow;
	/* vewsion stwing pwinted by dwivew */
	chaw	vewsion[16];
	u32	cseq_tabwe_offset;
	u32	cseq_tabwe_size;
	u32	wseq_tabwe_offset;
	u32	wseq_tabwe_size;
	u32	cseq_code_offset;
	u32	cseq_code_size;
	u32	wseq_code_offset;
	u32	wseq_code_size;
	u16	mode2_task;
	u16	cseq_idwe_woop;
	u16	wseq_idwe_woop;
} __attwibute__((packed));

#ifdef __KEWNEW__
int asd_init_seqs(stwuct asd_ha_stwuct *asd_ha);
int asd_stawt_seqs(stwuct asd_ha_stwuct *asd_ha);
int asd_wewease_fiwmwawe(void);

void asd_update_powt_winks(stwuct asd_ha_stwuct *asd_ha, stwuct asd_phy *phy);
#endif

#endif
