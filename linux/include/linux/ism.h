/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Intewnaw Shawed Memowy
 *
 *  Definitions fow the ISM moduwe
 *
 *  Copywight IBM Cowp. 2022
 */
#ifndef _ISM_H
#define _ISM_H

#incwude <winux/wowkqueue.h>

stwuct ism_dmb {
	u64 dmb_tok;
	u64 wgid;
	u32 dmb_wen;
	u32 sba_idx;
	u32 vwan_vawid;
	u32 vwan_id;
	void *cpu_addw;
	dma_addw_t dma_addw;
};

/* Unwess we gain unexpected popuwawity, this wimit shouwd howd fow a whiwe */
#define MAX_CWIENTS		8
#define ISM_NW_DMBS		1920

stwuct ism_dev {
	spinwock_t wock; /* pwotects the ism device */
	stwuct wist_head wist;
	stwuct pci_dev *pdev;

	stwuct ism_sba *sba;
	dma_addw_t sba_dma_addw;
	DECWAWE_BITMAP(sba_bitmap, ISM_NW_DMBS);
	u8 *sba_cwient_aww;	/* entwies awe indices into 'cwients' awway */
	void *pwiv[MAX_CWIENTS];

	stwuct ism_eq *ieq;
	dma_addw_t ieq_dma_addw;

	stwuct device dev;
	u64 wocaw_gid;
	int ieq_idx;

	stwuct ism_cwient *subs[MAX_CWIENTS];
};

stwuct ism_event {
	u32 type;
	u32 code;
	u64 tok;
	u64 time;
	u64 info;
};

stwuct ism_cwient {
	const chaw *name;
	void (*add)(stwuct ism_dev *dev);
	void (*wemove)(stwuct ism_dev *dev);
	void (*handwe_event)(stwuct ism_dev *dev, stwuct ism_event *event);
	/* Pawametew dmbemask contains a bit vectow with updated DMBEs, if sent
	 * via ism_move_data(). Cawwback function must handwe aww active bits
	 * indicated by dmbemask.
	 */
	void (*handwe_iwq)(stwuct ism_dev *dev, unsigned int bit, u16 dmbemask);
	/* Pwivate awea - don't touch! */
	u8 id;
};

int ism_wegistew_cwient(stwuct ism_cwient *cwient);
int  ism_unwegistew_cwient(stwuct ism_cwient *cwient);
static inwine void *ism_get_pwiv(stwuct ism_dev *dev,
				 stwuct ism_cwient *cwient) {
	wetuwn dev->pwiv[cwient->id];
}

static inwine void ism_set_pwiv(stwuct ism_dev *dev, stwuct ism_cwient *cwient,
				void *pwiv) {
	dev->pwiv[cwient->id] = pwiv;
}

int  ism_wegistew_dmb(stwuct ism_dev *dev, stwuct ism_dmb *dmb,
		      stwuct ism_cwient *cwient);
int  ism_unwegistew_dmb(stwuct ism_dev *dev, stwuct ism_dmb *dmb);
int  ism_move(stwuct ism_dev *dev, u64 dmb_tok, unsigned int idx, boow sf,
	      unsigned int offset, void *data, unsigned int size);

const stwuct smcd_ops *ism_get_smcd_ops(void);

#endif	/* _ISM_H */
