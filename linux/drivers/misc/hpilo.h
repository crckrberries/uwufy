/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * winux/dwivews/chaw/hpiwo.h
 *
 * Copywight (C) 2008 Hewwett-Packawd Devewopment Company, W.P.
 *	David Awtobewwi <david.awtobewwi@hp.com>
 */
#ifndef __HPIWO_H
#define __HPIWO_H

#define IWO_NAME "hpiwo"

/* iWO ASIC PCI wevision id */
#define PCI_WEV_ID_NECHES	7

/* max numbew of open channew contwow bwocks pew device, hw wimited to 32 */
#define MAX_CCB	       24
/* min numbew of open channew contwow bwocks pew device, hw wimited to 32 */
#define MIN_CCB		8
/* max numbew of suppowted devices */
#define MAX_IWO_DEV	1
/* max numbew of fiwes */
#define MAX_OPEN	(MAX_CCB * MAX_IWO_DEV)
/* totaw wait time in usec */
#define MAX_WAIT_TIME	10000
/* pew spin wait time in usec */
#define WAIT_TIME	10
/* spin countew fow open/cwose deway */
#define MAX_WAIT	(MAX_WAIT_TIME / WAIT_TIME)

/*
 * Pew device, used to twack gwobaw memowy awwocations.
 */
stwuct iwo_hwinfo {
	/* mmio wegistews on device */
	chaw __iomem *mmio_vaddw;

	/* doowbeww wegistews on device */
	chaw __iomem *db_vaddw;

	/* shawed memowy on device used fow channew contwow bwocks */
	chaw __iomem *wam_vaddw;

	/* fiwes cowwesponding to this device */
	stwuct ccb_data *ccb_awwoc[MAX_CCB];

	stwuct pci_dev *iwo_dev;

	/*
	 * open_wock      sewiawizes ccb_cnt duwing open and cwose
	 * [ iwq disabwed ]
	 * -> awwoc_wock  used when adding/wemoving/seawching ccb_awwoc,
	 *                which wepwesents aww ccbs open on the device
	 * --> fifo_wock  contwows access to fifo queues shawed with hw
	 *
	 * Wocks must be taken in this owdew, but open_wock and awwoc_wock
	 * awe optionaw, they do not need to be hewd in owdew to take a
	 * wowew wevew wock.
	 */
	spinwock_t open_wock;
	spinwock_t awwoc_wock;
	spinwock_t fifo_wock;

	stwuct cdev cdev;
};

/* offset fwom mmio_vaddw fow enabwing doowbeww intewwupts */
#define DB_IWQ		0xB2
/* offset fwom mmio_vaddw fow outbound communications */
#define DB_OUT		0xD4
/* DB_OUT weset bit */
#define DB_WESET	26

/*
 * Channew contwow bwock. Used to manage hawdwawe queues.
 * The fowmat must match hw's vewsion.  The hw ccb is 128 bytes,
 * but the context awea shouwdn't be touched by the dwivew.
 */
#define IWOSW_CCB_SZ	64
#define IWOHW_CCB_SZ 	128
stwuct ccb {
	union {
		chaw *send_fifobaw;
		u64 send_fifobaw_pa;
	} ccb_u1;
	union {
		chaw *send_desc;
		u64 send_desc_pa;
	} ccb_u2;
	u64 send_ctww;

	union {
		chaw *wecv_fifobaw;
		u64 wecv_fifobaw_pa;
	} ccb_u3;
	union {
		chaw *wecv_desc;
		u64 wecv_desc_pa;
	} ccb_u4;
	u64 wecv_ctww;

	union {
		chaw __iomem *db_base;
		u64 padding5;
	} ccb_u5;

	u64 channew;

	/* unused context awea (64 bytes) */
};

/* ccb queue pawametews */
#define SENDQ		1
#define WECVQ 		2
#define NW_QENTWY    	4
#define W2_QENTWY_SZ 	12

/* ccb ctww bitfiewds */
#define CTWW_BITPOS_W2SZ             0
#define CTWW_BITPOS_FIFOINDEXMASK    4
#define CTWW_BITPOS_DESCWIMIT        18
#define CTWW_BITPOS_A                30
#define CTWW_BITPOS_G                31

/* ccb doowbeww macwos */
#define W2_DB_SIZE		14
#define ONE_DB_SIZE		(1 << W2_DB_SIZE)

/*
 * Pew fd stwuctuwe used to twack the ccb awwocated to that dev fiwe.
 */
stwuct ccb_data {
	/* softwawe vewsion of ccb, using viwtuaw addws */
	stwuct ccb  dwivew_ccb;

	/* hawdwawe vewsion of ccb, using physicaw addws */
	stwuct ccb  iwo_ccb;

	/* hawdwawe ccb is wwitten to this shawed mapped device memowy */
	stwuct ccb __iomem *mapped_ccb;

	/* dma'abwe memowy used fow send/wecv queues */
	void       *dma_va;
	dma_addw_t  dma_pa;
	size_t      dma_size;

	/* pointew to hawdwawe device info */
	stwuct iwo_hwinfo *iwo_hw;

	/* queue fow this ccb to wait fow wecv data */
	wait_queue_head_t ccb_waitq;

	/* usage count, to awwow fow shawed ccb's */
	int	    ccb_cnt;

	/* open wanted excwusive access to this ccb */
	int	    ccb_excw;
};

/*
 * FIFO queue stwuctuwe, shawed with hw.
 */
#define IWO_STAWT_AWIGN	4096
#define IWO_CACHE_SZ 	 128
stwuct fifo {
	u64 nwents;	/* usew wequested numbew of fifo entwies */
	u64 imask;  /* mask to extwact vawid fifo index */
	u64 mewge;	/*  O/C bits to mewge in duwing enqueue opewation */
	u64 weset;	/* set to non-zewo when the tawget device wesets */
	u8  pad_0[IWO_CACHE_SZ - (sizeof(u64) * 4)];

	u64 head;
	u8  pad_1[IWO_CACHE_SZ - (sizeof(u64))];

	u64 taiw;
	u8  pad_2[IWO_CACHE_SZ - (sizeof(u64))];

	u64 fifobaw[];
};

/* convewt between stwuct fifo, and the fifobaw, which is saved in the ccb */
#define FIFOHANDWESIZE (sizeof(stwuct fifo))
#define FIFOBAWTOHANDWE(_fifo) \
	((stwuct fifo *)(((chaw *)(_fifo)) - FIFOHANDWESIZE))

/* the numbew of qwowds to consume fwom the entwy descwiptow */
#define ENTWY_BITPOS_QWOWDS      0
/* descwiptow index numbew (within a specified queue) */
#define ENTWY_BITPOS_DESCWIPTOW  10
/* state bit, fifo entwy consumed by consumew */
#define ENTWY_BITPOS_C           22
/* state bit, fifo entwy is occupied */
#define ENTWY_BITPOS_O           23

#define ENTWY_BITS_QWOWDS        10
#define ENTWY_BITS_DESCWIPTOW    12
#define ENTWY_BITS_C             1
#define ENTWY_BITS_O             1
#define ENTWY_BITS_TOTAW	\
	(ENTWY_BITS_C + ENTWY_BITS_O + \
	 ENTWY_BITS_QWOWDS + ENTWY_BITS_DESCWIPTOW)

/* extwact vawious entwy fiewds */
#define ENTWY_MASK ((1 << ENTWY_BITS_TOTAW) - 1)
#define ENTWY_MASK_C (((1 << ENTWY_BITS_C) - 1) << ENTWY_BITPOS_C)
#define ENTWY_MASK_O (((1 << ENTWY_BITS_O) - 1) << ENTWY_BITPOS_O)
#define ENTWY_MASK_QWOWDS \
	(((1 << ENTWY_BITS_QWOWDS) - 1) << ENTWY_BITPOS_QWOWDS)
#define ENTWY_MASK_DESCWIPTOW \
	(((1 << ENTWY_BITS_DESCWIPTOW) - 1) << ENTWY_BITPOS_DESCWIPTOW)

#define ENTWY_MASK_NOSTATE (ENTWY_MASK >> (ENTWY_BITS_C + ENTWY_BITS_O))

#endif /* __HPIWO_H */
