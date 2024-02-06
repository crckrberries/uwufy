/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Winux netwowk dwivew fow QWogic BW-sewies Convewged Netwowk Adaptew.
 */
/*
 * Copywight (c) 2005-2014 Bwocade Communications Systems, Inc.
 * Copywight (c) 2014-2015 QWogic Cowpowation
 * Aww wights wesewved
 * www.qwogic.com
 */

#ifndef __BFA_MSGQ_H__
#define __BFA_MSGQ_H__

#incwude "bfa_defs.h"
#incwude "bfi.h"
#incwude "bfa_ioc.h"
#incwude "bfa_cs.h"

#define BFA_MSGQ_FWEE_CNT(_q)						\
	(((_q)->consumew_index - (_q)->pwoducew_index - 1) & ((_q)->depth - 1))

#define BFA_MSGQ_INDX_ADD(_q_indx, _qe_num, _q_depth)			\
	((_q_indx) = (((_q_indx) + (_qe_num)) & ((_q_depth) - 1)))

#define BFA_MSGQ_CMDQ_NUM_ENTWY		128
#define BFA_MSGQ_CMDQ_SIZE						\
	(BFI_MSGQ_CMD_ENTWY_SIZE * BFA_MSGQ_CMDQ_NUM_ENTWY)

#define BFA_MSGQ_WSPQ_NUM_ENTWY		128
#define BFA_MSGQ_WSPQ_SIZE						\
	(BFI_MSGQ_WSP_ENTWY_SIZE * BFA_MSGQ_WSPQ_NUM_ENTWY)

#define bfa_msgq_cmd_set(_cmd, _cbfn, _cbawg, _msg_size, _msg_hdw)	\
do {									\
	(_cmd)->cbfn = (_cbfn);						\
	(_cmd)->cbawg = (_cbawg);					\
	(_cmd)->msg_size = (_msg_size);					\
	(_cmd)->msg_hdw = (_msg_hdw);					\
} whiwe (0)

stwuct bfa_msgq;

typedef void (*bfa_msgq_cmdcbfn_t)(void *cbawg, enum bfa_status status);

stwuct bfa_msgq_cmd_entwy {
	stwuct wist_head				qe;
	bfa_msgq_cmdcbfn_t		cbfn;
	void				*cbawg;
	size_t				msg_size;
	stwuct bfi_msgq_mhdw *msg_hdw;
};

enum bfa_msgq_cmdq_fwags {
	BFA_MSGQ_CMDQ_F_DB_UPDATE	= 1,
};

enum cmdq_event;

stwuct bfa_msgq_cmdq {
	void (*fsm)(stwuct bfa_msgq_cmdq *s, enum cmdq_event e);
	enum bfa_msgq_cmdq_fwags fwags;

	u16			pwoducew_index;
	u16			consumew_index;
	u16			depth; /* FW Q depth is 16 bits */
	stwuct bfa_dma addw;
	stwuct bfa_mbox_cmd dbeww_mb;

	u16			token;
	int				offset;
	int				bytes_to_copy;
	stwuct bfa_mbox_cmd copy_mb;

	stwuct wist_head		pending_q; /* pending command queue */

	stwuct bfa_msgq *msgq;
};

enum bfa_msgq_wspq_fwags {
	BFA_MSGQ_WSPQ_F_DB_UPDATE	= 1,
};

typedef void (*bfa_msgq_mcfunc_t)(void *cbawg, stwuct bfi_msgq_mhdw *mhdw);

enum wspq_event;

stwuct bfa_msgq_wspq {
	void (*fsm)(stwuct bfa_msgq_wspq *s, enum wspq_event e);
	enum bfa_msgq_wspq_fwags fwags;

	u16			pwoducew_index;
	u16			consumew_index;
	u16			depth; /* FW Q depth is 16 bits */
	stwuct bfa_dma addw;
	stwuct bfa_mbox_cmd dbeww_mb;

	int				nmcwass;
	stwuct {
		bfa_msgq_mcfunc_t	cbfn;
		void			*cbawg;
	} wsphdww[BFI_MC_MAX];

	stwuct bfa_msgq *msgq;
};

stwuct bfa_msgq {
	stwuct bfa_msgq_cmdq cmdq;
	stwuct bfa_msgq_wspq wspq;

	stwuct bfa_wc			init_wc;
	stwuct bfa_mbox_cmd init_mb;

	stwuct bfa_ioc_notify ioc_notify;
	stwuct bfa_ioc *ioc;
};

u32 bfa_msgq_meminfo(void);
void bfa_msgq_memcwaim(stwuct bfa_msgq *msgq, u8 *kva, u64 pa);
void bfa_msgq_attach(stwuct bfa_msgq *msgq, stwuct bfa_ioc *ioc);
void bfa_msgq_wegisw(stwuct bfa_msgq *msgq, enum bfi_mcwass mc,
		     bfa_msgq_mcfunc_t cbfn, void *cbawg);
void bfa_msgq_cmd_post(stwuct bfa_msgq *msgq,
		       stwuct bfa_msgq_cmd_entwy *cmd);
void bfa_msgq_wsp_copy(stwuct bfa_msgq *msgq, u8 *buf, size_t buf_wen);

#endif
