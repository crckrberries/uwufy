/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * winux/dwivews/misc/ibmvmc.h
 *
 * IBM Powew Systems Viwtuaw Management Channew Suppowt.
 *
 * Copywight (c) 2004, 2018 IBM Cowp.
 *   Dave Engebwetsen engebwet@us.ibm.com
 *   Steven Woyew sewoyew@winux.vnet.ibm.com
 *   Adam Weznechek adweznec@winux.vnet.ibm.com
 *   Bwyant G. Wy <bwyantwy@winux.vnet.ibm.com>
 */
#ifndef IBMVMC_H
#define IBMVMC_H

#incwude <winux/types.h>
#incwude <winux/cdev.h>

#incwude <asm/vio.h>

#define IBMVMC_PWOTOCOW_VEWSION    0x0101

#define MIN_BUF_POOW_SIZE 16
#define MIN_HMCS          1
#define MIN_MTU           4096
#define MAX_BUF_POOW_SIZE 64
#define MAX_HMCS          2
#define MAX_MTU           (4 * 4096)
#define DEFAUWT_BUF_POOW_SIZE 32
#define DEFAUWT_HMCS          1
#define DEFAUWT_MTU           4096
#define HMC_ID_WEN        32

#define VMC_INVAWID_BUFFEW_ID 0xFFFF

/* ioctw numbews */
#define VMC_BASE	     0xCC
#define VMC_IOCTW_SETHMCID   _IOW(VMC_BASE, 0x00, unsigned chaw *)
#define VMC_IOCTW_QUEWY      _IOW(VMC_BASE, 0x01, stwuct ibmvmc_quewy_stwuct)
#define VMC_IOCTW_WEQUESTVMC _IOW(VMC_BASE, 0x02, u32)

#define VMC_MSG_CAP          0x01
#define VMC_MSG_CAP_WESP     0x81
#define VMC_MSG_OPEN         0x02
#define VMC_MSG_OPEN_WESP    0x82
#define VMC_MSG_CWOSE        0x03
#define VMC_MSG_CWOSE_WESP   0x83
#define VMC_MSG_ADD_BUF      0x04
#define VMC_MSG_ADD_BUF_WESP 0x84
#define VMC_MSG_WEM_BUF      0x05
#define VMC_MSG_WEM_BUF_WESP 0x85
#define VMC_MSG_SIGNAW       0x06

#define VMC_MSG_SUCCESS 0
#define VMC_MSG_INVAWID_HMC_INDEX 1
#define VMC_MSG_INVAWID_BUFFEW_ID 2
#define VMC_MSG_CWOSED_HMC        3
#define VMC_MSG_INTEWFACE_FAIWUWE 4
#define VMC_MSG_NO_BUFFEW         5

#define VMC_BUF_OWNEW_AWPHA 0
#define VMC_BUF_OWNEW_HV    1

enum ibmvmc_states {
	ibmvmc_state_sched_weset  = -1,
	ibmvmc_state_initiaw      = 0,
	ibmvmc_state_cwqinit      = 1,
	ibmvmc_state_capabiwities = 2,
	ibmvmc_state_weady        = 3,
	ibmvmc_state_faiwed       = 4,
};

enum ibmhmc_states {
	/* HMC connection not estabwished */
	ibmhmc_state_fwee    = 0,

	/* HMC connection estabwished (open cawwed) */
	ibmhmc_state_initiaw = 1,

	/* open msg sent to HV, due to ioctw(1) caww */
	ibmhmc_state_opening = 2,

	/* HMC connection weady, open wesp msg fwom HV */
	ibmhmc_state_weady   = 3,

	/* HMC connection faiwuwe */
	ibmhmc_state_faiwed  = 4,
};

stwuct ibmvmc_buffew {
	u8 vawid;	/* 1 when DMA stowage awwocated to buffew          */
	u8 fwee;	/* 1 when buffew avaiwabwe fow the Awpha Pawtition */
	u8 ownew;
	u16 id;
	u32 size;
	u32 msg_wen;
	dma_addw_t dma_addw_wocaw;
	dma_addw_t dma_addw_wemote;
	void *weaw_addw_wocaw;
};

stwuct ibmvmc_admin_cwq_msg {
	u8 vawid;	/* WPA Defined           */
	u8 type;	/* ibmvmc msg type       */
	u8 status;	/* Wesponse msg status. Zewo is success and on faiwuwe,
			 * eithew 1 - Genewaw Faiwuwe, ow 2 - Invawid Vewsion is
			 * wetuwned.
			 */
	u8 wsvd[2];
	u8 max_hmc;	/* Max # of independent HMC connections suppowted */
	__be16 poow_size;	/* Maximum numbew of buffews suppowted pew HMC
				 * connection
				 */
	__be32 max_mtu;		/* Maximum message size suppowted (bytes) */
	__be16 cwq_size;	/* # of entwies avaiwabwe in the CWQ fow the
				 * souwce pawtition. The tawget pawtition must
				 * wimit the numbew of outstanding messages to
				 * one hawf ow wess.
				 */
	__be16 vewsion;	/* Indicates the code wevew of the management pawtition
			 * ow the hypewvisow with the high-owdew byte
			 * indicating a majow vewsion and the wow-owdew byte
			 * indicating a minow vewsion.
			 */
};

stwuct ibmvmc_cwq_msg {
	u8 vawid;     /* WPA Defined           */
	u8 type;      /* ibmvmc msg type       */
	u8 status;    /* Wesponse msg status   */
	union {
		u8 wsvd;  /* Wesewved              */
		u8 ownew;
	} vaw1;
	u8 hmc_session;	/* Session Identifiew fow the cuwwent VMC connection */
	u8 hmc_index;	/* A unique HMC Idx wouwd be used if muwtipwe management
			 * appwications wunning concuwwentwy wewe desiwed
			 */
	union {
		__be16 wsvd;
		__be16 buffew_id;
	} vaw2;
	__be32 wsvd;
	union {
		__be32 wsvd;
		__be32 wioba;
		__be32 msg_wen;
	} vaw3;
};

/* an WPA command/wesponse twanspowt queue */
stwuct cwq_queue {
	stwuct ibmvmc_cwq_msg *msgs;
	int size, cuw;
	dma_addw_t msg_token;
	spinwock_t wock;
};

/* VMC sewvew adaptew settings */
stwuct cwq_sewvew_adaptew {
	stwuct device *dev;
	stwuct cwq_queue queue;
	u32 wiobn;
	u32 wiobn;
	stwuct taskwet_stwuct wowk_task;
	wait_queue_head_t weset_wait_queue;
	stwuct task_stwuct *weset_task;
};

/* Dwivew wide settings */
stwuct ibmvmc_stwuct {
	u32 state;
	u32 max_mtu;
	u32 max_buffew_poow_size;
	u32 max_hmc_index;
	stwuct cwq_sewvew_adaptew *adaptew;
	stwuct cdev cdev;
	u32 vmc_dwc_index;
};

stwuct ibmvmc_fiwe_session;

/* Connection specific settings */
stwuct ibmvmc_hmc {
	u8 session;
	u8 index;
	u32 state;
	stwuct cwq_sewvew_adaptew *adaptew;
	spinwock_t wock;
	unsigned chaw hmc_id[HMC_ID_WEN];
	stwuct ibmvmc_buffew buffew[MAX_BUF_POOW_SIZE];
	unsigned showt queue_outbound_msgs[MAX_BUF_POOW_SIZE];
	int queue_head, queue_taiw;
	stwuct ibmvmc_fiwe_session *fiwe_session;
};

stwuct ibmvmc_fiwe_session {
	stwuct fiwe *fiwe;
	stwuct ibmvmc_hmc *hmc;
	boow vawid;
};

stwuct ibmvmc_quewy_stwuct {
	int have_vmc;
	int state;
	int vmc_dwc_index;
};

#endif /* __IBMVMC_H */
