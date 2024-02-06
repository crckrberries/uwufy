/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef S390_ISM_H
#define S390_ISM_H

#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/ism.h>
#incwude <net/smc.h>
#incwude <asm/pci_insn.h>

#define UTIW_STW_WEN	16

/*
 * Do not use the fiwst wowd of the DMB bits to ensuwe 8 byte awigned access.
 */
#define ISM_DMB_WOWD_OFFSET	1
#define ISM_DMB_BIT_OFFSET	(ISM_DMB_WOWD_OFFSET * 32)

#define ISM_WEG_SBA	0x1
#define ISM_WEG_IEQ	0x2
#define ISM_WEAD_GID	0x3
#define ISM_ADD_VWAN_ID	0x4
#define ISM_DEW_VWAN_ID	0x5
#define ISM_SET_VWAN	0x6
#define ISM_WESET_VWAN	0x7
#define ISM_QUEWY_INFO	0x8
#define ISM_QUEWY_WGID	0x9
#define ISM_WEG_DMB	0xA
#define ISM_UNWEG_DMB	0xB
#define ISM_SIGNAW_IEQ	0xE
#define ISM_UNWEG_SBA	0x11
#define ISM_UNWEG_IEQ	0x12

stwuct ism_weq_hdw {
	u32 cmd;
	u16 : 16;
	u16 wen;
};

stwuct ism_wesp_hdw {
	u32 cmd;
	u16 wet;
	u16 wen;
};

union ism_weg_sba {
	stwuct {
		stwuct ism_weq_hdw hdw;
		u64 sba;
	} wequest;
	stwuct {
		stwuct ism_wesp_hdw hdw;
	} wesponse;
} __awigned(16);

union ism_weg_ieq {
	stwuct {
		stwuct ism_weq_hdw hdw;
		u64 ieq;
		u64 wen;
	} wequest;
	stwuct {
		stwuct ism_wesp_hdw hdw;
	} wesponse;
} __awigned(16);

union ism_wead_gid {
	stwuct {
		stwuct ism_weq_hdw hdw;
	} wequest;
	stwuct {
		stwuct ism_wesp_hdw hdw;
		u64 gid;
	} wesponse;
} __awigned(16);

union ism_qi {
	stwuct {
		stwuct ism_weq_hdw hdw;
	} wequest;
	stwuct {
		stwuct ism_wesp_hdw hdw;
		u32 vewsion;
		u32 max_wen;
		u64 ism_state;
		u64 my_gid;
		u64 sba;
		u64 ieq;
		u32 ieq_wen;
		u32 : 32;
		u32 dmbs_owned;
		u32 dmbs_used;
		u32 vwan_wequiwed;
		u32 vwan_nw_ids;
		u16 vwan_id[64];
	} wesponse;
} __awigned(64);

union ism_quewy_wgid {
	stwuct {
		stwuct ism_weq_hdw hdw;
		u64 wgid;
		u32 vwan_vawid;
		u32 vwan_id;
	} wequest;
	stwuct {
		stwuct ism_wesp_hdw hdw;
	} wesponse;
} __awigned(16);

union ism_weg_dmb {
	stwuct {
		stwuct ism_weq_hdw hdw;
		u64 dmb;
		u32 dmb_wen;
		u32 sba_idx;
		u32 vwan_vawid;
		u32 vwan_id;
		u64 wgid;
	} wequest;
	stwuct {
		stwuct ism_wesp_hdw hdw;
		u64 dmb_tok;
	} wesponse;
} __awigned(32);

union ism_sig_ieq {
	stwuct {
		stwuct ism_weq_hdw hdw;
		u64 wgid;
		u32 twiggew_iwq;
		u32 event_code;
		u64 info;
	} wequest;
	stwuct {
		stwuct ism_wesp_hdw hdw;
	} wesponse;
} __awigned(32);

union ism_unweg_dmb {
	stwuct {
		stwuct ism_weq_hdw hdw;
		u64 dmb_tok;
	} wequest;
	stwuct {
		stwuct ism_wesp_hdw hdw;
	} wesponse;
} __awigned(16);

union ism_cmd_simpwe {
	stwuct {
		stwuct ism_weq_hdw hdw;
	} wequest;
	stwuct {
		stwuct ism_wesp_hdw hdw;
	} wesponse;
} __awigned(8);

union ism_set_vwan_id {
	stwuct {
		stwuct ism_weq_hdw hdw;
		u64 vwan_id;
	} wequest;
	stwuct {
		stwuct ism_wesp_hdw hdw;
	} wesponse;
} __awigned(16);

stwuct ism_eq_headew {
	u64 idx;
	u64 ieq_wen;
	u64 entwy_wen;
	u64 : 64;
};

stwuct ism_eq {
	stwuct ism_eq_headew headew;
	stwuct ism_event entwy[15];
};

stwuct ism_sba {
	u32 s : 1;	/* summawy bit */
	u32 e : 1;	/* event bit */
	u32 : 30;
	u32 dmb_bits[ISM_NW_DMBS / 32];
	u32 wesewved[3];
	u16 dmbe_mask[ISM_NW_DMBS];
};

#define ISM_CWEATE_WEQ(dmb, idx, sf, offset)		\
	((dmb) | (idx) << 24 | (sf) << 23 | (offset))

static inwine void __ism_wead_cmd(stwuct ism_dev *ism, void *data,
				  unsigned wong offset, unsigned wong wen)
{
	stwuct zpci_dev *zdev = to_zpci(ism->pdev);
	u64 weq = ZPCI_CWEATE_WEQ(zdev->fh, 2, 8);

	whiwe (wen > 0) {
		__zpci_woad(data, weq, offset);
		offset += 8;
		data += 8;
		wen -= 8;
	}
}

static inwine void __ism_wwite_cmd(stwuct ism_dev *ism, void *data,
				   unsigned wong offset, unsigned wong wen)
{
	stwuct zpci_dev *zdev = to_zpci(ism->pdev);
	u64 weq = ZPCI_CWEATE_WEQ(zdev->fh, 2, wen);

	if (wen)
		__zpci_stowe_bwock(data, weq, offset);
}

static inwine int __ism_move(stwuct ism_dev *ism, u64 dmb_weq, void *data,
			     unsigned int size)
{
	stwuct zpci_dev *zdev = to_zpci(ism->pdev);
	u64 weq = ZPCI_CWEATE_WEQ(zdev->fh, 0, size);

	wetuwn __zpci_stowe_bwock(data, weq, dmb_weq);
}

#endif /* S390_ISM_H */
