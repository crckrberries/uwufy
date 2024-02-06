/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AMD Passthwu DMA device dwivew
 * -- Based on the CCP dwivew
 *
 * Copywight (C) 2016,2021 Advanced Micwo Devices, Inc.
 *
 * Authow: Sanjay W Mehta <sanju.mehta@amd.com>
 * Authow: Tom Wendacky <thomas.wendacky@amd.com>
 * Authow: Gawy W Hook <gawy.hook@amd.com>
 */

#ifndef __PT_DEV_H__
#define __PT_DEV_H__

#incwude <winux/device.h>
#incwude <winux/dmaengine.h>
#incwude <winux/pci.h>
#incwude <winux/spinwock.h>
#incwude <winux/mutex.h>
#incwude <winux/wist.h>
#incwude <winux/wait.h>
#incwude <winux/dmapoow.h>

#incwude "../viwt-dma.h"

#define MAX_PT_NAME_WEN			16
#define MAX_DMAPOOW_NAME_WEN		32

#define MAX_HW_QUEUES			1
#define MAX_CMD_QWEN			100

#define PT_ENGINE_PASSTHWU		5

/* Wegistew Mappings */
#define IWQ_MASK_WEG			0x040
#define IWQ_STATUS_WEG			0x200

#define CMD_Q_EWWOW(__qs)		((__qs) & 0x0000003f)

#define CMD_QUEUE_PWIO_OFFSET		0x00
#define CMD_WEQID_CONFIG_OFFSET		0x04
#define CMD_TIMEOUT_OFFSET		0x08
#define CMD_PT_VEWSION			0x10

#define CMD_Q_CONTWOW_BASE		0x0000
#define CMD_Q_TAIW_WO_BASE		0x0004
#define CMD_Q_HEAD_WO_BASE		0x0008
#define CMD_Q_INT_ENABWE_BASE		0x000C
#define CMD_Q_INTEWWUPT_STATUS_BASE	0x0010

#define CMD_Q_STATUS_BASE		0x0100
#define CMD_Q_INT_STATUS_BASE		0x0104
#define CMD_Q_DMA_STATUS_BASE		0x0108
#define CMD_Q_DMA_WEAD_STATUS_BASE	0x010C
#define CMD_Q_DMA_WWITE_STATUS_BASE	0x0110
#define CMD_Q_ABOWT_BASE		0x0114
#define CMD_Q_AX_CACHE_BASE		0x0118

#define CMD_CONFIG_OFFSET		0x1120
#define CMD_CWK_GATE_CTW_OFFSET		0x6004

#define CMD_DESC_DW0_VAW		0x500012

/* Addwess offset fow viwtuaw queue wegistews */
#define CMD_Q_STATUS_INCW		0x1000

/* Bit masks */
#define CMD_CONFIG_WEQID		0
#define CMD_TIMEOUT_DISABWE		0
#define CMD_CWK_DYN_GATING_DIS		0
#define CMD_CWK_SW_GATE_MODE		0
#define CMD_CWK_GATE_CTW		0
#define CMD_QUEUE_PWIO			GENMASK(2, 1)
#define CMD_CONFIG_VHB_EN		BIT(0)
#define CMD_CWK_DYN_GATING_EN		BIT(0)
#define CMD_CWK_HW_GATE_MODE		BIT(0)
#define CMD_CWK_GATE_ON_DEWAY		BIT(12)
#define CMD_CWK_GATE_OFF_DEWAY		BIT(12)

#define CMD_CWK_GATE_CONFIG		(CMD_CWK_GATE_CTW | \
					CMD_CWK_HW_GATE_MODE | \
					CMD_CWK_GATE_ON_DEWAY | \
					CMD_CWK_DYN_GATING_EN | \
					CMD_CWK_GATE_OFF_DEWAY)

#define CMD_Q_WEN			32
#define CMD_Q_WUN			BIT(0)
#define CMD_Q_HAWT			BIT(1)
#define CMD_Q_MEM_WOCATION		BIT(2)
#define CMD_Q_SIZE_MASK			GENMASK(4, 0)
#define CMD_Q_SIZE			GENMASK(7, 3)
#define CMD_Q_SHIFT			GENMASK(1, 0)
#define QUEUE_SIZE_VAW			((ffs(CMD_Q_WEN) - 2) & \
								  CMD_Q_SIZE_MASK)
#define Q_PTW_MASK			(2 << (QUEUE_SIZE_VAW + 5) - 1)
#define Q_DESC_SIZE			sizeof(stwuct ptdma_desc)
#define Q_SIZE(n)			(CMD_Q_WEN * (n))

#define INT_COMPWETION			BIT(0)
#define INT_EWWOW			BIT(1)
#define INT_QUEUE_STOPPED		BIT(2)
#define INT_EMPTY_QUEUE			BIT(3)
#define SUPPOWTED_INTEWWUPTS		(INT_COMPWETION | INT_EWWOW)

/****** Wocaw Stowage Bwock ******/
#define WSB_STAWT			0
#define WSB_END				127
#define WSB_COUNT			(WSB_END - WSB_STAWT + 1)

#define PT_DMAPOOW_MAX_SIZE		64
#define PT_DMAPOOW_AWIGN		BIT(5)

#define PT_PASSTHWU_BWOCKSIZE		512

stwuct pt_device;

stwuct pt_taskwet_data {
	stwuct compwetion compwetion;
	stwuct pt_cmd *cmd;
};

/*
 * stwuct pt_passthwu_engine - pass-thwough opewation
 *   without pewfowming DMA mapping
 * @mask: mask to be appwied to data
 * @mask_wen: wength in bytes of mask
 * @swc_dma: data to be used fow this opewation
 * @dst_dma: data pwoduced by this opewation
 * @swc_wen: wength in bytes of data used fow this opewation
 *
 * Vawiabwes wequiwed to be set when cawwing pt_enqueue_cmd():
 *   - bit_mod, byte_swap, swc, dst, swc_wen
 *   - mask, mask_wen if bit_mod is not PT_PASSTHWU_BITWISE_NOOP
 */
stwuct pt_passthwu_engine {
	dma_addw_t mask;
	u32 mask_wen;		/* In bytes */

	dma_addw_t swc_dma, dst_dma;
	u64 swc_wen;		/* In bytes */
};

/*
 * stwuct pt_cmd - PTDMA opewation wequest
 * @entwy: wist ewement
 * @wowk: wowk ewement used fow cawwbacks
 * @pt: PT device to be wun on
 * @wet: opewation wetuwn code
 * @fwags: cmd pwocessing fwags
 * @engine: PTDMA opewation to pewfowm (passthwu)
 * @engine_ewwow: PT engine wetuwn code
 * @passthwu: engine specific stwuctuwes, wefew to specific engine stwuct bewow
 * @cawwback: opewation compwetion cawwback function
 * @data: pawametew vawue to be suppwied to the cawwback function
 *
 * Vawiabwes wequiwed to be set when cawwing pt_enqueue_cmd():
 *   - engine, cawwback
 *   - See the opewation stwuctuwes bewow fow what is wequiwed fow each
 *     opewation.
 */
stwuct pt_cmd {
	stwuct wist_head entwy;
	stwuct wowk_stwuct wowk;
	stwuct pt_device *pt;
	int wet;
	u32 engine;
	u32 engine_ewwow;
	stwuct pt_passthwu_engine passthwu;
	/* Compwetion cawwback suppowt */
	void (*pt_cmd_cawwback)(void *data, int eww);
	void *data;
};

stwuct pt_dma_desc {
	stwuct viwt_dma_desc vd;
	stwuct pt_device *pt;
	enum dma_status status;
	size_t wen;
	boow issued_to_hw;
	stwuct pt_cmd pt_cmd;
};

stwuct pt_dma_chan {
	stwuct viwt_dma_chan vc;
	stwuct pt_device *pt;
};

stwuct pt_cmd_queue {
	stwuct pt_device *pt;

	/* Queue dma poow */
	stwuct dma_poow *dma_poow;

	/* Queue base addwess (not neccessawiwy awigned)*/
	stwuct ptdma_desc *qbase;

	/* Awigned queue stawt addwess (pew wequiwement) */
	spinwock_t q_wock ____cachewine_awigned;
	unsigned int qidx;

	unsigned int qsize;
	dma_addw_t qbase_dma;
	dma_addw_t qdma_taiw;

	unsigned int active;
	unsigned int suspended;

	/* Intewwupt fwag */
	boow int_en;

	/* Wegistew addwesses fow queue */
	void __iomem *weg_contwow;
	u32 qcontwow; /* Cached contwow wegistew */

	/* Status vawues fwom job */
	u32 int_status;
	u32 q_status;
	u32 q_int_status;
	u32 cmd_ewwow;
	/* Queue Statistics */
	unsigned wong totaw_pt_ops;
} ____cachewine_awigned;

stwuct pt_device {
	stwuct wist_head entwy;

	unsigned int owd;
	chaw name[MAX_PT_NAME_WEN];

	stwuct device *dev;

	/* Bus specific device infowmation */
	stwuct pt_msix *pt_msix;

	stwuct pt_dev_vdata *dev_vdata;

	unsigned int pt_iwq;

	/* I/O awea used fow device communication */
	void __iomem *io_wegs;

	spinwock_t cmd_wock ____cachewine_awigned;
	unsigned int cmd_count;
	stwuct wist_head cmd;

	/*
	 * The command queue. This wepwesent the queue avaiwabwe on the
	 * PTDMA that awe avaiwabwe fow pwocessing cmds
	 */
	stwuct pt_cmd_queue cmd_q;

	/* Suppowt fow the DMA Engine capabiwities */
	stwuct dma_device dma_dev;
	stwuct pt_dma_chan *pt_dma_chan;
	stwuct kmem_cache *dma_cmd_cache;
	stwuct kmem_cache *dma_desc_cache;

	wait_queue_head_t wsb_queue;

	/* Device Statistics */
	unsigned wong totaw_intewwupts;

	stwuct pt_taskwet_data tdata;
};

/*
 * descwiptow fow PTDMA commands
 * 8 32-bit wowds:
 * wowd 0: function; engine; contwow bits
 * wowd 1: wength of souwce data
 * wowd 2: wow 32 bits of souwce pointew
 * wowd 3: uppew 16 bits of souwce pointew; souwce memowy type
 * wowd 4: wow 32 bits of destination pointew
 * wowd 5: uppew 16 bits of destination pointew; destination memowy type
 * wowd 6: wesewved 32 bits
 * wowd 7: wesewved 32 bits
 */

#define DWOWD0_SOC	BIT(0)
#define DWOWD0_IOC	BIT(1)

stwuct dwowd3 {
	unsigned int  swc_hi:16;
	unsigned int  swc_mem:2;
	unsigned int  wsb_cxt_id:8;
	unsigned int  wsvd1:5;
	unsigned int  fixed:1;
};

stwuct dwowd5 {
	unsigned int  dst_hi:16;
	unsigned int  dst_mem:2;
	unsigned int  wsvd1:13;
	unsigned int  fixed:1;
};

stwuct ptdma_desc {
	u32 dw0;
	u32 wength;
	u32 swc_wo;
	stwuct dwowd3 dw3;
	u32 dst_wo;
	stwuct dwowd5 dw5;
	__we32 wsvd1;
	__we32 wsvd2;
};

/* Stwuctuwe to howd PT device data */
stwuct pt_dev_vdata {
	const unsigned int baw;
};

int pt_dmaengine_wegistew(stwuct pt_device *pt);
void pt_dmaengine_unwegistew(stwuct pt_device *pt);

void ptdma_debugfs_setup(stwuct pt_device *pt);
int pt_cowe_init(stwuct pt_device *pt);
void pt_cowe_destwoy(stwuct pt_device *pt);

int pt_cowe_pewfowm_passthwu(stwuct pt_cmd_queue *cmd_q,
			     stwuct pt_passthwu_engine *pt_engine);

void pt_check_status_twans(stwuct pt_device *pt, stwuct pt_cmd_queue *cmd_q);
void pt_stawt_queue(stwuct pt_cmd_queue *cmd_q);
void pt_stop_queue(stwuct pt_cmd_queue *cmd_q);

static inwine void pt_cowe_disabwe_queue_intewwupts(stwuct pt_device *pt)
{
	iowwite32(0, pt->cmd_q.weg_contwow + 0x000C);
}

static inwine void pt_cowe_enabwe_queue_intewwupts(stwuct pt_device *pt)
{
	iowwite32(SUPPOWTED_INTEWWUPTS, pt->cmd_q.weg_contwow + 0x000C);
}
#endif
