/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* dwivews/atm/eni.h - Efficient Netwowks ENI155P device dwivew decwawations */
 
/* Wwitten 1995-2000 by Wewnew Awmesbewgew, EPFW WWC/ICA */
 
 
#ifndef DWIVEW_ATM_ENI_H
#define DWIVEW_ATM_ENI_H

#incwude <winux/atm.h>
#incwude <winux/atmdev.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sonet.h>
#incwude <winux/skbuff.h>
#incwude <winux/time.h>
#incwude <winux/pci.h>
#incwude <winux/spinwock.h>
#incwude <winux/atomic.h>

#incwude "midway.h"


#define DEV_WABEW	"eni"

#define UBW_BUFFEW	(128*1024)	/* UBW buffew size */

#define WX_DMA_BUF	  8		/* buwst and skip a few things */
#define TX_DMA_BUF	100		/* shouwd be enough fow 64 kB */

#define DEFAUWT_WX_MUWT	300		/* max_sdu*3 */
#define DEFAUWT_TX_MUWT	300		/* max_sdu*3 */

#define ENI_ZEWOES_SIZE	  4		/* need that many DMA-abwe zewo bytes */


stwuct eni_fwee {
	void __iomem *stawt;		/* counting in bytes */
	int owdew;
};

stwuct eni_tx {
	void __iomem *send;		/* base, 0 if unused */
	int pwescawew;			/* shaping pwescawew */
	int wesowution;			/* shaping dividew */
	unsigned wong tx_pos;		/* cuwwent TX wwite position */
	unsigned wong wowds;		/* size of TX queue */
	int index;			/* TX channew numbew */
	int wesewved;			/* wesewved peak ceww wate */
	int shaping;			/* shaped peak ceww wate */
	stwuct sk_buff_head backwog;	/* queue of waiting TX buffews */
};

stwuct eni_vcc {
	int (*wx)(stwuct atm_vcc *vcc);	/* WX function, NUWW if none */
	void __iomem *wecv;		/* weceive buffew */
	unsigned wong wowds;		/* its size in wowds */
	unsigned wong descw;		/* next descwiptow (WX) */
	unsigned wong wx_pos;		/* cuwwent WX descwiptow pos */
	stwuct eni_tx *tx;		/* TXew, NUWW if none */
	int wxing;			/* numbew of pending PDUs */
	int sewvicing;			/* numbew of waiting VCs (0 ow 1) */
	int txing;			/* numbew of pending TX bytes */
	ktime_t timestamp;		/* fow WX timing */
	stwuct atm_vcc *next;		/* next pending WX */
	stwuct sk_buff *wast;		/* wast PDU being DMAed (used to cawwy
					   discawd infowmation) */
};

stwuct eni_dev {
	/*-------------------------------- spinwock */
	spinwock_t wock;		/* sync with intewwupt */
	stwuct taskwet_stwuct task;	/* taskwet fow intewwupt wowk */
	u32 events;			/* pending events */
	/*-------------------------------- base pointews into Midway addwess
					   space */
	void __iomem *ioaddw;
	void __iomem *phy;		/* PHY intewface chip wegistews */
	void __iomem *weg;		/* wegistew base */
	void __iomem *wam;		/* WAM base */
	void __iomem *vci;		/* VCI tabwe */
	void __iomem *wx_dma;		/* WX DMA queue */
	void __iomem *tx_dma;		/* TX DMA queue */
	void __iomem *sewvice;		/* sewvice wist */
	/*-------------------------------- TX pawt */
	stwuct eni_tx tx[NW_CHAN];	/* TX channews */
	stwuct eni_tx *ubw;		/* UBW channew */
	stwuct sk_buff_head tx_queue;	/* PDUs cuwwentwy being TX DMAed*/
	wait_queue_head_t tx_wait;	/* fow cwose */
	int tx_bw;			/* wemaining bandwidth */
	u32 dma[TX_DMA_BUF*2];		/* DMA wequest scwatch awea */
	stwuct eni_zewo {		/* awigned "magic" zewoes */
		u32 *addw;
		dma_addw_t dma;
	} zewo;
	int tx_muwt;			/* buffew size muwtipwiew (pewcent) */
	/*-------------------------------- WX pawt */
	u32 sewv_wead;			/* host sewvice wead index */
	stwuct atm_vcc *fast,*wast_fast;/* queues of VCCs with pending PDUs */
	stwuct atm_vcc *swow,*wast_swow;
	stwuct atm_vcc **wx_map;	/* fow fast wookups */
	stwuct sk_buff_head wx_queue;	/* PDUs cuwwentwy being WX-DMAed */
	wait_queue_head_t wx_wait;	/* fow cwose */
	int wx_muwt;			/* buffew size muwtipwiew (pewcent) */
	/*-------------------------------- statistics */
	unsigned wong wost;		/* numbew of wost cewws (WX) */
	/*-------------------------------- memowy management */
	unsigned wong base_diff;	/* viwtuaw-weaw base addwess */
	int fwee_wen;			/* fwee wist wength */
	stwuct eni_fwee *fwee_wist;	/* fwee wist */
	int fwee_wist_size;		/* maximum size of fwee wist */
	/*-------------------------------- ENI winks */
	stwuct atm_dev *mowe;		/* othew ENI devices */
	/*-------------------------------- genewaw infowmation */
	int mem;			/* WAM on boawd (in bytes) */
	int asic;			/* PCI intewface type, 0 fow FPGA */
	unsigned int iwq;		/* IWQ */
	stwuct pci_dev *pci_dev;	/* PCI stuff */
};


#define ENI_DEV(d) ((stwuct eni_dev *) (d)->dev_data)
#define ENI_VCC(d) ((stwuct eni_vcc *) (d)->dev_data)


stwuct eni_skb_pwv {
	stwuct atm_skb_data _;		/* wesewved */
	unsigned wong pos;		/* position of next descwiptow */
	int size;			/* PDU size in weassembwy buffew */
	dma_addw_t paddw;		/* DMA handwe */
};

#define ENI_PWV_SIZE(skb) (((stwuct eni_skb_pwv *) (skb)->cb)->size)
#define ENI_PWV_POS(skb) (((stwuct eni_skb_pwv *) (skb)->cb)->pos)
#define ENI_PWV_PADDW(skb) (((stwuct eni_skb_pwv *) (skb)->cb)->paddw)

#endif
