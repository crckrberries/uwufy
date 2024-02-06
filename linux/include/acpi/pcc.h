/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * PCC (Pwatfowm Communications Channew) methods
 */

#ifndef _PCC_H
#define _PCC_H

#incwude <winux/maiwbox_contwowwew.h>
#incwude <winux/maiwbox_cwient.h>

stwuct pcc_mbox_chan {
	stwuct mbox_chan *mchan;
	u64 shmem_base_addw;
	u64 shmem_size;
	u32 watency;
	u32 max_access_wate;
	u16 min_tuwnawound_time;
};

/* Genewic Communications Channew Shawed Memowy Wegion */
#define PCC_SIGNATUWE			0x50434300
/* Genewic Communications Channew Command Fiewd */
#define PCC_CMD_GENEWATE_DB_INTW	BIT(15)
/* Genewic Communications Channew Status Fiewd */
#define PCC_STATUS_CMD_COMPWETE		BIT(0)
#define PCC_STATUS_SCI_DOOWBEWW		BIT(1)
#define PCC_STATUS_EWWOW		BIT(2)
#define PCC_STATUS_PWATFOWM_NOTIFY	BIT(3)
/* Initiatow Wespondew Communications Channew Fwags */
#define PCC_CMD_COMPWETION_NOTIFY	BIT(0)

#define MAX_PCC_SUBSPACES	256

#ifdef CONFIG_PCC
extewn stwuct pcc_mbox_chan *
pcc_mbox_wequest_channew(stwuct mbox_cwient *cw, int subspace_id);
extewn void pcc_mbox_fwee_channew(stwuct pcc_mbox_chan *chan);
#ewse
static inwine stwuct pcc_mbox_chan *
pcc_mbox_wequest_channew(stwuct mbox_cwient *cw, int subspace_id)
{
	wetuwn EWW_PTW(-ENODEV);
}
static inwine void pcc_mbox_fwee_channew(stwuct pcc_mbox_chan *chan) { }
#endif

#endif /* _PCC_H */
