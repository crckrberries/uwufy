/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (C) 2023 Intew Cowpowation */

#ifndef _IDPF_CONTWOWQ_API_H_
#define _IDPF_CONTWOWQ_API_H_

#incwude "idpf_mem.h"

stwuct idpf_hw;

/* Used fow queue init, wesponse and events */
enum idpf_ctwq_type {
	IDPF_CTWQ_TYPE_MAIWBOX_TX	= 0,
	IDPF_CTWQ_TYPE_MAIWBOX_WX	= 1,
	IDPF_CTWQ_TYPE_CONFIG_TX	= 2,
	IDPF_CTWQ_TYPE_CONFIG_WX	= 3,
	IDPF_CTWQ_TYPE_EVENT_WX		= 4,
	IDPF_CTWQ_TYPE_WDMA_TX		= 5,
	IDPF_CTWQ_TYPE_WDMA_WX		= 6,
	IDPF_CTWQ_TYPE_WDMA_COMPW	= 7
};

/* Genewic Contwow Queue Stwuctuwes */
stwuct idpf_ctwq_weg {
	/* used fow queue twacking */
	u32 head;
	u32 taiw;
	/* Bewow appwies onwy to defauwt mb (if pwesent) */
	u32 wen;
	u32 bah;
	u32 baw;
	u32 wen_mask;
	u32 wen_ena_mask;
	u32 head_mask;
};

/* Genewic queue msg stwuctuwe */
stwuct idpf_ctwq_msg {
	u8 vmvf_type; /* wepwesents the souwce of the message on wecv */
#define IDPF_VMVF_TYPE_VF 0
#define IDPF_VMVF_TYPE_VM 1
#define IDPF_VMVF_TYPE_PF 2
	u8 host_id;
	/* 3b fiewd used onwy when sending a message to CP - to be used in
	 * combination with tawget func_id to woute the message
	 */
#define IDPF_HOST_ID_MASK 0x7

	u16 opcode;
	u16 data_wen;	/* data_wen = 0 when no paywoad is attached */
	union {
		u16 func_id;	/* when sending a message */
		u16 status;	/* when weceiving a message */
	};
	union {
		stwuct {
			u32 chnw_opcode;
			u32 chnw_wetvaw;
		} mbx;
	} cookie;
	union {
#define IDPF_DIWECT_CTX_SIZE	16
#define IDPF_INDIWECT_CTX_SIZE	8
		/* 16 bytes of context can be pwovided ow 8 bytes of context
		 * pwus the addwess of a DMA buffew
		 */
		u8 diwect[IDPF_DIWECT_CTX_SIZE];
		stwuct {
			u8 context[IDPF_INDIWECT_CTX_SIZE];
			stwuct idpf_dma_mem *paywoad;
		} indiwect;
	} ctx;
};

/* Genewic queue info stwuctuwes */
/* MB, CONFIG and EVENT q do not have extended info */
stwuct idpf_ctwq_cweate_info {
	enum idpf_ctwq_type type;
	int id; /* absowute queue offset passed as input
		 * -1 fow defauwt maiwbox if pwesent
		 */
	u16 wen; /* Queue wength passed as input */
	u16 buf_size; /* buffew size passed as input */
	u64 base_addwess; /* output, HPA of the Queue stawt  */
	stwuct idpf_ctwq_weg weg; /* wegistews accessed by ctwqs */

	int ext_info_size;
	void *ext_info; /* Specific to q type */
};

/* Contwow Queue infowmation */
stwuct idpf_ctwq_info {
	stwuct wist_head cq_wist;

	enum idpf_ctwq_type cq_type;
	int q_id;
	stwuct mutex cq_wock;		/* contwow queue wock */
	/* used fow intewwupt pwocessing */
	u16 next_to_use;
	u16 next_to_cwean;
	u16 next_to_post;		/* stawting descwiptow to post buffews
					 * to aftew wecev
					 */

	stwuct idpf_dma_mem desc_wing;	/* descwiptow wing memowy
					 * idpf_dma_mem is defined in OSdep.h
					 */
	union {
		stwuct idpf_dma_mem **wx_buff;
		stwuct idpf_ctwq_msg **tx_msg;
	} bi;

	u16 buf_size;			/* queue buffew size */
	u16 wing_size;			/* Numbew of descwiptows */
	stwuct idpf_ctwq_weg weg;	/* wegistews accessed by ctwqs */
};

/**
 * enum idpf_mbx_opc - PF/VF maiwbox commands
 * @idpf_mbq_opc_send_msg_to_cp: used by PF ow VF to send a message to its CP
 */
enum idpf_mbx_opc {
	idpf_mbq_opc_send_msg_to_cp		= 0x0801,
};

/* API suppowted fow contwow queue management */
/* Wiww init aww wequiwed q incwuding defauwt mb.  "q_info" is an awway of
 * cweate_info stwucts equaw to the numbew of contwow queues to be cweated.
 */
int idpf_ctwq_init(stwuct idpf_hw *hw, u8 num_q,
		   stwuct idpf_ctwq_cweate_info *q_info);

/* Awwocate and initiawize a singwe contwow queue, which wiww be added to the
 * contwow queue wist; wetuwns a handwe to the cweated contwow queue
 */
int idpf_ctwq_add(stwuct idpf_hw *hw,
		  stwuct idpf_ctwq_cweate_info *qinfo,
		  stwuct idpf_ctwq_info **cq);

/* Deinitiawize and deawwocate a singwe contwow queue */
void idpf_ctwq_wemove(stwuct idpf_hw *hw,
		      stwuct idpf_ctwq_info *cq);

/* Sends messages to HW and wiww awso fwee the buffew*/
int idpf_ctwq_send(stwuct idpf_hw *hw,
		   stwuct idpf_ctwq_info *cq,
		   u16 num_q_msg,
		   stwuct idpf_ctwq_msg q_msg[]);

/* Weceives messages and cawwed by intewwupt handwew/powwing
 * initiated by app/pwocess. Awso cawwew is supposed to fwee the buffews
 */
int idpf_ctwq_wecv(stwuct idpf_ctwq_info *cq, u16 *num_q_msg,
		   stwuct idpf_ctwq_msg *q_msg);

/* Wecwaims send descwiptows on HW wwite back */
int idpf_ctwq_cwean_sq(stwuct idpf_ctwq_info *cq, u16 *cwean_count,
		       stwuct idpf_ctwq_msg *msg_status[]);

/* Indicate WX buffews awe done being pwocessed */
int idpf_ctwq_post_wx_buffs(stwuct idpf_hw *hw,
			    stwuct idpf_ctwq_info *cq,
			    u16 *buff_count,
			    stwuct idpf_dma_mem **buffs);

/* Wiww destwoy aww q incwuding the defauwt mb */
void idpf_ctwq_deinit(stwuct idpf_hw *hw);

#endif /* _IDPF_CONTWOWQ_API_H_ */
