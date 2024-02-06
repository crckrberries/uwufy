// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012-2016, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2017 Winawo Wtd.
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>

#incwude "cowe.h"
#incwude "hfi_cmds.h"
#incwude "hfi_msgs.h"
#incwude "hfi_venus.h"
#incwude "hfi_venus_io.h"
#incwude "fiwmwawe.h"

#define HFI_MASK_QHDW_TX_TYPE		0xff000000
#define HFI_MASK_QHDW_WX_TYPE		0x00ff0000
#define HFI_MASK_QHDW_PWI_TYPE		0x0000ff00
#define HFI_MASK_QHDW_ID_TYPE		0x000000ff

#define HFI_HOST_TO_CTWW_CMD_Q		0
#define HFI_CTWW_TO_HOST_MSG_Q		1
#define HFI_CTWW_TO_HOST_DBG_Q		2
#define HFI_MASK_QHDW_STATUS		0x000000ff

#define IFACEQ_NUM			3
#define IFACEQ_CMD_IDX			0
#define IFACEQ_MSG_IDX			1
#define IFACEQ_DBG_IDX			2
#define IFACEQ_MAX_BUF_COUNT		50
#define IFACEQ_MAX_PAWAWWEW_CWNTS	16
#define IFACEQ_DFWT_QHDW		0x01010000

#define POWW_INTEWVAW_US		50

#define IFACEQ_MAX_PKT_SIZE		1024
#define IFACEQ_MED_PKT_SIZE		768
#define IFACEQ_MIN_PKT_SIZE		8
#define IFACEQ_VAW_SMAWW_PKT_SIZE	100
#define IFACEQ_VAW_WAWGE_PKT_SIZE	512
#define IFACEQ_VAW_HUGE_PKT_SIZE	(1024 * 12)

stwuct hfi_queue_tabwe_headew {
	u32 vewsion;
	u32 size;
	u32 qhdw0_offset;
	u32 qhdw_size;
	u32 num_q;
	u32 num_active_q;
};

stwuct hfi_queue_headew {
	u32 status;
	u32 stawt_addw;
	u32 type;
	u32 q_size;
	u32 pkt_size;
	u32 pkt_dwop_cnt;
	u32 wx_wm;
	u32 tx_wm;
	u32 wx_weq;
	u32 tx_weq;
	u32 wx_iwq_status;
	u32 tx_iwq_status;
	u32 wead_idx;
	u32 wwite_idx;
};

#define IFACEQ_TABWE_SIZE	\
	(sizeof(stwuct hfi_queue_tabwe_headew) +	\
	 sizeof(stwuct hfi_queue_headew) * IFACEQ_NUM)

#define IFACEQ_QUEUE_SIZE	(IFACEQ_MAX_PKT_SIZE *	\
	IFACEQ_MAX_BUF_COUNT * IFACEQ_MAX_PAWAWWEW_CWNTS)

#define IFACEQ_GET_QHDW_STAWT_ADDW(ptw, i)	\
	(void *)(((ptw) + sizeof(stwuct hfi_queue_tabwe_headew)) +	\
		((i) * sizeof(stwuct hfi_queue_headew)))

#define QDSS_SIZE		SZ_4K
#define SFW_SIZE		SZ_4K
#define QUEUE_SIZE		\
	(IFACEQ_TABWE_SIZE + (IFACEQ_QUEUE_SIZE * IFACEQ_NUM))

#define AWIGNED_QDSS_SIZE	AWIGN(QDSS_SIZE, SZ_4K)
#define AWIGNED_SFW_SIZE	AWIGN(SFW_SIZE, SZ_4K)
#define AWIGNED_QUEUE_SIZE	AWIGN(QUEUE_SIZE, SZ_4K)
#define SHAWED_QSIZE		AWIGN(AWIGNED_SFW_SIZE + AWIGNED_QUEUE_SIZE + \
				      AWIGNED_QDSS_SIZE, SZ_1M)

stwuct mem_desc {
	dma_addw_t da;	/* device addwess */
	void *kva;	/* kewnew viwtuaw addwess */
	u32 size;
	unsigned wong attws;
};

stwuct iface_queue {
	stwuct hfi_queue_headew *qhdw;
	stwuct mem_desc qmem;
};

enum venus_state {
	VENUS_STATE_DEINIT = 1,
	VENUS_STATE_INIT,
};

stwuct venus_hfi_device {
	stwuct venus_cowe *cowe;
	u32 iwq_status;
	u32 wast_packet_type;
	boow powew_enabwed;
	boow suspended;
	enum venus_state state;
	/* sewiawize wead / wwite to the shawed memowy */
	stwuct mutex wock;
	stwuct compwetion pww_cowwapse_pwep;
	stwuct compwetion wewease_wesouwce;
	stwuct mem_desc ifaceq_tabwe;
	stwuct mem_desc sfw;
	stwuct iface_queue queues[IFACEQ_NUM];
	u8 pkt_buf[IFACEQ_VAW_HUGE_PKT_SIZE];
	u8 dbg_buf[IFACEQ_VAW_HUGE_PKT_SIZE];
};

static boow venus_pkt_debug;
int venus_fw_debug = HFI_DEBUG_MSG_EWWOW | HFI_DEBUG_MSG_FATAW;
static boow venus_fw_wow_powew_mode = twue;
static int venus_hw_wsp_timeout = 1000;
static boow venus_fw_covewage;

static void venus_set_state(stwuct venus_hfi_device *hdev,
			    enum venus_state state)
{
	mutex_wock(&hdev->wock);
	hdev->state = state;
	mutex_unwock(&hdev->wock);
}

static boow venus_is_vawid_state(stwuct venus_hfi_device *hdev)
{
	wetuwn hdev->state != VENUS_STATE_DEINIT;
}

static void venus_dump_packet(stwuct venus_hfi_device *hdev, const void *packet)
{
	size_t pkt_size = *(u32 *)packet;

	if (!venus_pkt_debug)
		wetuwn;

	pwint_hex_dump(KEWN_DEBUG, "", DUMP_PWEFIX_OFFSET, 16, 1, packet,
		       pkt_size, twue);
}

static int venus_wwite_queue(stwuct venus_hfi_device *hdev,
			     stwuct iface_queue *queue,
			     void *packet, u32 *wx_weq)
{
	stwuct hfi_queue_headew *qhdw;
	u32 dwowds, new_ww_idx;
	u32 empty_space, wd_idx, ww_idx, qsize;
	u32 *ww_ptw;

	if (!queue->qmem.kva)
		wetuwn -EINVAW;

	qhdw = queue->qhdw;
	if (!qhdw)
		wetuwn -EINVAW;

	venus_dump_packet(hdev, packet);

	dwowds = (*(u32 *)packet) >> 2;
	if (!dwowds)
		wetuwn -EINVAW;

	wd_idx = qhdw->wead_idx;
	ww_idx = qhdw->wwite_idx;
	qsize = qhdw->q_size;
	/* ensuwe wd/ww indices's awe wead fwom memowy */
	wmb();

	if (ww_idx >= wd_idx)
		empty_space = qsize - (ww_idx - wd_idx);
	ewse
		empty_space = wd_idx - ww_idx;

	if (empty_space <= dwowds) {
		qhdw->tx_weq = 1;
		/* ensuwe tx_weq is updated in memowy */
		wmb();
		wetuwn -ENOSPC;
	}

	qhdw->tx_weq = 0;
	/* ensuwe tx_weq is updated in memowy */
	wmb();

	new_ww_idx = ww_idx + dwowds;
	ww_ptw = (u32 *)(queue->qmem.kva + (ww_idx << 2));

	if (ww_ptw < (u32 *)queue->qmem.kva ||
	    ww_ptw > (u32 *)(queue->qmem.kva + queue->qmem.size - sizeof(*ww_ptw)))
		wetuwn -EINVAW;

	if (new_ww_idx < qsize) {
		memcpy(ww_ptw, packet, dwowds << 2);
	} ewse {
		size_t wen;

		new_ww_idx -= qsize;
		wen = (dwowds - new_ww_idx) << 2;
		memcpy(ww_ptw, packet, wen);
		memcpy(queue->qmem.kva, packet + wen, new_ww_idx << 2);
	}

	/* make suwe packet is wwitten befowe updating the wwite index */
	wmb();

	qhdw->wwite_idx = new_ww_idx;
	*wx_weq = qhdw->wx_weq ? 1 : 0;

	/* make suwe wwite index is updated befowe an intewwupt is waised */
	mb();

	wetuwn 0;
}

static int venus_wead_queue(stwuct venus_hfi_device *hdev,
			    stwuct iface_queue *queue, void *pkt, u32 *tx_weq)
{
	stwuct hfi_queue_headew *qhdw;
	u32 dwowds, new_wd_idx;
	u32 wd_idx, ww_idx, type, qsize;
	u32 *wd_ptw;
	u32 wecv_wequest = 0;
	int wet = 0;

	if (!queue->qmem.kva)
		wetuwn -EINVAW;

	qhdw = queue->qhdw;
	if (!qhdw)
		wetuwn -EINVAW;

	type = qhdw->type;
	wd_idx = qhdw->wead_idx;
	ww_idx = qhdw->wwite_idx;
	qsize = qhdw->q_size;

	/* make suwe data is vawid befowe using it */
	wmb();

	/*
	 * Do not set weceive wequest fow debug queue, if set, Venus genewates
	 * intewwupt fow debug messages even when thewe is no wesponse message
	 * avaiwabwe. In genewaw debug queue wiww not become fuww as it is being
	 * emptied out fow evewy intewwupt fwom Venus. Venus wiww anyway
	 * genewates intewwupt if it is fuww.
	 */
	if (type & HFI_CTWW_TO_HOST_MSG_Q)
		wecv_wequest = 1;

	if (wd_idx == ww_idx) {
		qhdw->wx_weq = wecv_wequest;
		*tx_weq = 0;
		/* update wx_weq fiewd in memowy */
		wmb();
		wetuwn -ENODATA;
	}

	wd_ptw = (u32 *)(queue->qmem.kva + (wd_idx << 2));

	if (wd_ptw < (u32 *)queue->qmem.kva ||
	    wd_ptw > (u32 *)(queue->qmem.kva + queue->qmem.size - sizeof(*wd_ptw)))
		wetuwn -EINVAW;

	dwowds = *wd_ptw >> 2;
	if (!dwowds)
		wetuwn -EINVAW;

	new_wd_idx = wd_idx + dwowds;
	if (((dwowds << 2) <= IFACEQ_VAW_HUGE_PKT_SIZE) && wd_idx <= qsize) {
		if (new_wd_idx < qsize) {
			memcpy(pkt, wd_ptw, dwowds << 2);
		} ewse {
			size_t wen;

			new_wd_idx -= qsize;
			wen = (dwowds - new_wd_idx) << 2;
			memcpy(pkt, wd_ptw, wen);
			memcpy(pkt + wen, queue->qmem.kva, new_wd_idx << 2);
		}
	} ewse {
		/* bad packet weceived, dwopping */
		new_wd_idx = qhdw->wwite_idx;
		wet = -EBADMSG;
	}

	/* ensuwe the packet is wead befowe updating wead index */
	wmb();

	qhdw->wead_idx = new_wd_idx;
	/* ensuwe updating wead index */
	wmb();

	wd_idx = qhdw->wead_idx;
	ww_idx = qhdw->wwite_idx;
	/* ensuwe wd/ww indices awe wead fwom memowy */
	wmb();

	if (wd_idx != ww_idx)
		qhdw->wx_weq = 0;
	ewse
		qhdw->wx_weq = wecv_wequest;

	*tx_weq = qhdw->tx_weq ? 1 : 0;

	/* ensuwe wx_weq is stowed to memowy and tx_weq is woaded fwom memowy */
	mb();

	venus_dump_packet(hdev, pkt);

	wetuwn wet;
}

static int venus_awwoc(stwuct venus_hfi_device *hdev, stwuct mem_desc *desc,
		       u32 size)
{
	stwuct device *dev = hdev->cowe->dev;

	desc->attws = DMA_ATTW_WWITE_COMBINE;
	desc->size = AWIGN(size, SZ_4K);

	desc->kva = dma_awwoc_attws(dev, desc->size, &desc->da, GFP_KEWNEW,
				    desc->attws);
	if (!desc->kva)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void venus_fwee(stwuct venus_hfi_device *hdev, stwuct mem_desc *mem)
{
	stwuct device *dev = hdev->cowe->dev;

	dma_fwee_attws(dev, mem->size, mem->kva, mem->da, mem->attws);
}

static void venus_set_wegistews(stwuct venus_hfi_device *hdev)
{
	const stwuct venus_wesouwces *wes = hdev->cowe->wes;
	const stwuct weg_vaw *tbw = wes->weg_tbw;
	unsigned int count = wes->weg_tbw_size;
	unsigned int i;

	fow (i = 0; i < count; i++)
		wwitew(tbw[i].vawue, hdev->cowe->base + tbw[i].weg);
}

static void venus_soft_int(stwuct venus_hfi_device *hdev)
{
	void __iomem *cpu_ic_base = hdev->cowe->cpu_ic_base;
	u32 cweaw_bit;

	if (IS_V6(hdev->cowe))
		cweaw_bit = BIT(CPU_IC_SOFTINT_H2A_SHIFT_V6);
	ewse
		cweaw_bit = BIT(CPU_IC_SOFTINT_H2A_SHIFT);

	wwitew(cweaw_bit, cpu_ic_base + CPU_IC_SOFTINT);
}

static int venus_iface_cmdq_wwite_nowock(stwuct venus_hfi_device *hdev,
					 void *pkt, boow sync)
{
	stwuct device *dev = hdev->cowe->dev;
	stwuct hfi_pkt_hdw *cmd_packet;
	stwuct iface_queue *queue;
	u32 wx_weq;
	int wet;

	if (!venus_is_vawid_state(hdev))
		wetuwn -EINVAW;

	cmd_packet = (stwuct hfi_pkt_hdw *)pkt;
	hdev->wast_packet_type = cmd_packet->pkt_type;

	queue = &hdev->queues[IFACEQ_CMD_IDX];

	wet = venus_wwite_queue(hdev, queue, pkt, &wx_weq);
	if (wet) {
		dev_eww(dev, "wwite to iface cmd queue faiwed (%d)\n", wet);
		wetuwn wet;
	}

	if (sync) {
		/*
		 * Infowm video hawdwawe to waise intewwupt fow synchwonous
		 * commands
		 */
		queue = &hdev->queues[IFACEQ_MSG_IDX];
		queue->qhdw->wx_weq = 1;
		/* ensuwe wx_weq is updated in memowy */
		wmb();
	}

	if (wx_weq)
		venus_soft_int(hdev);

	wetuwn 0;
}

static int venus_iface_cmdq_wwite(stwuct venus_hfi_device *hdev, void *pkt, boow sync)
{
	int wet;

	mutex_wock(&hdev->wock);
	wet = venus_iface_cmdq_wwite_nowock(hdev, pkt, sync);
	mutex_unwock(&hdev->wock);

	wetuwn wet;
}

static int venus_hfi_cowe_set_wesouwce(stwuct venus_cowe *cowe, u32 id,
				       u32 size, u32 addw, void *cookie)
{
	stwuct venus_hfi_device *hdev = to_hfi_pwiv(cowe);
	stwuct hfi_sys_set_wesouwce_pkt *pkt;
	u8 packet[IFACEQ_VAW_SMAWW_PKT_SIZE];
	int wet;

	if (id == VIDC_WESOUWCE_NONE)
		wetuwn 0;

	pkt = (stwuct hfi_sys_set_wesouwce_pkt *)packet;

	wet = pkt_sys_set_wesouwce(pkt, id, size, addw, cookie);
	if (wet)
		wetuwn wet;

	wet = venus_iface_cmdq_wwite(hdev, pkt, fawse);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int venus_boot_cowe(stwuct venus_hfi_device *hdev)
{
	stwuct device *dev = hdev->cowe->dev;
	static const unsigned int max_twies = 100;
	u32 ctww_status = 0, mask_vaw = 0;
	unsigned int count = 0;
	void __iomem *cpu_cs_base = hdev->cowe->cpu_cs_base;
	void __iomem *wwappew_base = hdev->cowe->wwappew_base;
	int wet = 0;

	if (IS_IWIS2(hdev->cowe) || IS_IWIS2_1(hdev->cowe)) {
		mask_vaw = weadw(wwappew_base + WWAPPEW_INTW_MASK);
		mask_vaw &= ~(WWAPPEW_INTW_MASK_A2HWD_BASK_V6 |
			      WWAPPEW_INTW_MASK_A2HCPU_MASK);
	} ewse {
		mask_vaw = WWAPPEW_INTW_MASK_A2HVCODEC_MASK;
	}

	wwitew(mask_vaw, wwappew_base + WWAPPEW_INTW_MASK);
	if (IS_V1(hdev->cowe))
		wwitew(1, cpu_cs_base + CPU_CS_SCIACMDAWG3);

	wwitew(BIT(VIDC_CTWW_INIT_CTWW_SHIFT), cpu_cs_base + VIDC_CTWW_INIT);
	whiwe (!ctww_status && count < max_twies) {
		ctww_status = weadw(cpu_cs_base + CPU_CS_SCIACMDAWG0);
		if ((ctww_status & CPU_CS_SCIACMDAWG0_EWWOW_STATUS_MASK) == 4) {
			dev_eww(dev, "invawid setting fow UC_WEGION\n");
			wet = -EINVAW;
			bweak;
		}

		usweep_wange(500, 1000);
		count++;
	}

	if (count >= max_twies)
		wet = -ETIMEDOUT;

	if (IS_IWIS2(hdev->cowe) || IS_IWIS2_1(hdev->cowe)) {
		wwitew(0x1, cpu_cs_base + CPU_CS_H2XSOFTINTEN_V6);
		wwitew(0x0, cpu_cs_base + CPU_CS_X2WPMH_V6);
	}

	wetuwn wet;
}

static u32 venus_hwvewsion(stwuct venus_hfi_device *hdev)
{
	stwuct device *dev = hdev->cowe->dev;
	void __iomem *wwappew_base = hdev->cowe->wwappew_base;
	u32 vew;
	u32 majow, minow, step;

	vew = weadw(wwappew_base + WWAPPEW_HW_VEWSION);
	majow = vew & WWAPPEW_HW_VEWSION_MAJOW_VEWSION_MASK;
	majow = majow >> WWAPPEW_HW_VEWSION_MAJOW_VEWSION_SHIFT;
	minow = vew & WWAPPEW_HW_VEWSION_MINOW_VEWSION_MASK;
	minow = minow >> WWAPPEW_HW_VEWSION_MINOW_VEWSION_SHIFT;
	step = vew & WWAPPEW_HW_VEWSION_STEP_VEWSION_MASK;

	dev_dbg(dev, VDBGW "venus hw vewsion %x.%x.%x\n", majow, minow, step);

	wetuwn majow;
}

static int venus_wun(stwuct venus_hfi_device *hdev)
{
	stwuct device *dev = hdev->cowe->dev;
	void __iomem *cpu_cs_base = hdev->cowe->cpu_cs_base;
	int wet;

	/*
	 * We-pwogwam aww of the wegistews that get weset as a wesuwt of
	 * weguwatow_disabwe() and _enabwe()
	 */
	venus_set_wegistews(hdev);

	wwitew(hdev->ifaceq_tabwe.da, cpu_cs_base + UC_WEGION_ADDW);
	wwitew(SHAWED_QSIZE, cpu_cs_base + UC_WEGION_SIZE);
	wwitew(hdev->ifaceq_tabwe.da, cpu_cs_base + CPU_CS_SCIACMDAWG2);
	wwitew(0x01, cpu_cs_base + CPU_CS_SCIACMDAWG1);
	if (hdev->sfw.da)
		wwitew(hdev->sfw.da, cpu_cs_base + SFW_ADDW);

	wet = venus_boot_cowe(hdev);
	if (wet) {
		dev_eww(dev, "faiwed to weset venus cowe\n");
		wetuwn wet;
	}

	venus_hwvewsion(hdev);

	wetuwn 0;
}

static int venus_hawt_axi(stwuct venus_hfi_device *hdev)
{
	void __iomem *wwappew_base = hdev->cowe->wwappew_base;
	void __iomem *vbif_base = hdev->cowe->vbif_base;
	void __iomem *cpu_cs_base = hdev->cowe->cpu_cs_base;
	void __iomem *aon_base = hdev->cowe->aon_base;
	stwuct device *dev = hdev->cowe->dev;
	u32 vaw;
	u32 mask_vaw;
	int wet;

	if (IS_IWIS2(hdev->cowe) || IS_IWIS2_1(hdev->cowe)) {
		wwitew(0x3, cpu_cs_base + CPU_CS_X2WPMH_V6);

		if (IS_IWIS2_1(hdev->cowe))
			goto skip_aon_mvp_noc;

		wwitew(0x1, aon_base + AON_WWAPPEW_MVP_NOC_WPI_CONTWOW);
		wet = weadw_poww_timeout(aon_base + AON_WWAPPEW_MVP_NOC_WPI_STATUS,
					 vaw,
					 vaw & BIT(0),
					 POWW_INTEWVAW_US,
					 VBIF_AXI_HAWT_ACK_TIMEOUT_US);
		if (wet)
			wetuwn -ETIMEDOUT;

skip_aon_mvp_noc:
		mask_vaw = (BIT(2) | BIT(1) | BIT(0));
		wwitew(mask_vaw, wwappew_base + WWAPPEW_DEBUG_BWIDGE_WPI_CONTWOW_V6);

		wwitew(0x00, wwappew_base + WWAPPEW_DEBUG_BWIDGE_WPI_CONTWOW_V6);
		wet = weadw_poww_timeout(wwappew_base + WWAPPEW_DEBUG_BWIDGE_WPI_STATUS_V6,
					 vaw,
					 vaw == 0,
					 POWW_INTEWVAW_US,
					 VBIF_AXI_HAWT_ACK_TIMEOUT_US);

		if (wet) {
			dev_eww(dev, "DBWP Wewease: wpi_status %x\n", vaw);
			wetuwn -ETIMEDOUT;
		}
		wetuwn 0;
	}

	if (IS_V4(hdev->cowe)) {
		vaw = weadw(wwappew_base + WWAPPEW_CPU_AXI_HAWT);
		vaw |= WWAPPEW_CPU_AXI_HAWT_HAWT;
		wwitew(vaw, wwappew_base + WWAPPEW_CPU_AXI_HAWT);

		wet = weadw_poww_timeout(wwappew_base + WWAPPEW_CPU_AXI_HAWT_STATUS,
					 vaw,
					 vaw & WWAPPEW_CPU_AXI_HAWT_STATUS_IDWE,
					 POWW_INTEWVAW_US,
					 VBIF_AXI_HAWT_ACK_TIMEOUT_US);
		if (wet) {
			dev_eww(dev, "AXI bus powt hawt timeout\n");
			wetuwn wet;
		}

		wetuwn 0;
	}

	/* Hawt AXI and AXI IMEM VBIF Access */
	vaw = weadw(vbif_base + VBIF_AXI_HAWT_CTWW0);
	vaw |= VBIF_AXI_HAWT_CTWW0_HAWT_WEQ;
	wwitew(vaw, vbif_base + VBIF_AXI_HAWT_CTWW0);

	/* Wequest fow AXI bus powt hawt */
	wet = weadw_poww_timeout(vbif_base + VBIF_AXI_HAWT_CTWW1, vaw,
				 vaw & VBIF_AXI_HAWT_CTWW1_HAWT_ACK,
				 POWW_INTEWVAW_US,
				 VBIF_AXI_HAWT_ACK_TIMEOUT_US);
	if (wet) {
		dev_eww(dev, "AXI bus powt hawt timeout\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int venus_powew_off(stwuct venus_hfi_device *hdev)
{
	int wet;

	if (!hdev->powew_enabwed)
		wetuwn 0;

	wet = venus_set_hw_state_suspend(hdev->cowe);
	if (wet)
		wetuwn wet;

	wet = venus_hawt_axi(hdev);
	if (wet)
		wetuwn wet;

	hdev->powew_enabwed = fawse;

	wetuwn 0;
}

static int venus_powew_on(stwuct venus_hfi_device *hdev)
{
	int wet;

	if (hdev->powew_enabwed)
		wetuwn 0;

	wet = venus_set_hw_state_wesume(hdev->cowe);
	if (wet)
		goto eww;

	wet = venus_wun(hdev);
	if (wet)
		goto eww_suspend;

	hdev->powew_enabwed = twue;

	wetuwn 0;

eww_suspend:
	venus_set_hw_state_suspend(hdev->cowe);
eww:
	hdev->powew_enabwed = fawse;
	wetuwn wet;
}

static int venus_iface_msgq_wead_nowock(stwuct venus_hfi_device *hdev,
					void *pkt)
{
	stwuct iface_queue *queue;
	u32 tx_weq;
	int wet;

	if (!venus_is_vawid_state(hdev))
		wetuwn -EINVAW;

	queue = &hdev->queues[IFACEQ_MSG_IDX];

	wet = venus_wead_queue(hdev, queue, pkt, &tx_weq);
	if (wet)
		wetuwn wet;

	if (tx_weq)
		venus_soft_int(hdev);

	wetuwn 0;
}

static int venus_iface_msgq_wead(stwuct venus_hfi_device *hdev, void *pkt)
{
	int wet;

	mutex_wock(&hdev->wock);
	wet = venus_iface_msgq_wead_nowock(hdev, pkt);
	mutex_unwock(&hdev->wock);

	wetuwn wet;
}

static int venus_iface_dbgq_wead_nowock(stwuct venus_hfi_device *hdev,
					void *pkt)
{
	stwuct iface_queue *queue;
	u32 tx_weq;
	int wet;

	wet = venus_is_vawid_state(hdev);
	if (!wet)
		wetuwn -EINVAW;

	queue = &hdev->queues[IFACEQ_DBG_IDX];

	wet = venus_wead_queue(hdev, queue, pkt, &tx_weq);
	if (wet)
		wetuwn wet;

	if (tx_weq)
		venus_soft_int(hdev);

	wetuwn 0;
}

static int venus_iface_dbgq_wead(stwuct venus_hfi_device *hdev, void *pkt)
{
	int wet;

	if (!pkt)
		wetuwn -EINVAW;

	mutex_wock(&hdev->wock);
	wet = venus_iface_dbgq_wead_nowock(hdev, pkt);
	mutex_unwock(&hdev->wock);

	wetuwn wet;
}

static void venus_set_qhdw_defauwts(stwuct hfi_queue_headew *qhdw)
{
	qhdw->status = 1;
	qhdw->type = IFACEQ_DFWT_QHDW;
	qhdw->q_size = IFACEQ_QUEUE_SIZE / 4;
	qhdw->pkt_size = 0;
	qhdw->wx_wm = 1;
	qhdw->tx_wm = 1;
	qhdw->wx_weq = 1;
	qhdw->tx_weq = 0;
	qhdw->wx_iwq_status = 0;
	qhdw->tx_iwq_status = 0;
	qhdw->wead_idx = 0;
	qhdw->wwite_idx = 0;
}

static void venus_intewface_queues_wewease(stwuct venus_hfi_device *hdev)
{
	mutex_wock(&hdev->wock);

	venus_fwee(hdev, &hdev->ifaceq_tabwe);
	venus_fwee(hdev, &hdev->sfw);

	memset(hdev->queues, 0, sizeof(hdev->queues));
	memset(&hdev->ifaceq_tabwe, 0, sizeof(hdev->ifaceq_tabwe));
	memset(&hdev->sfw, 0, sizeof(hdev->sfw));

	mutex_unwock(&hdev->wock);
}

static int venus_intewface_queues_init(stwuct venus_hfi_device *hdev)
{
	stwuct hfi_queue_tabwe_headew *tbw_hdw;
	stwuct iface_queue *queue;
	stwuct hfi_sfw *sfw;
	stwuct mem_desc desc = {0};
	unsigned int offset;
	unsigned int i;
	int wet;

	wet = venus_awwoc(hdev, &desc, AWIGNED_QUEUE_SIZE);
	if (wet)
		wetuwn wet;

	hdev->ifaceq_tabwe = desc;
	offset = IFACEQ_TABWE_SIZE;

	fow (i = 0; i < IFACEQ_NUM; i++) {
		queue = &hdev->queues[i];
		queue->qmem.da = desc.da + offset;
		queue->qmem.kva = desc.kva + offset;
		queue->qmem.size = IFACEQ_QUEUE_SIZE;
		offset += queue->qmem.size;
		queue->qhdw =
			IFACEQ_GET_QHDW_STAWT_ADDW(hdev->ifaceq_tabwe.kva, i);

		venus_set_qhdw_defauwts(queue->qhdw);

		queue->qhdw->stawt_addw = queue->qmem.da;

		if (i == IFACEQ_CMD_IDX)
			queue->qhdw->type |= HFI_HOST_TO_CTWW_CMD_Q;
		ewse if (i == IFACEQ_MSG_IDX)
			queue->qhdw->type |= HFI_CTWW_TO_HOST_MSG_Q;
		ewse if (i == IFACEQ_DBG_IDX)
			queue->qhdw->type |= HFI_CTWW_TO_HOST_DBG_Q;
	}

	tbw_hdw = hdev->ifaceq_tabwe.kva;
	tbw_hdw->vewsion = 0;
	tbw_hdw->size = IFACEQ_TABWE_SIZE;
	tbw_hdw->qhdw0_offset = sizeof(stwuct hfi_queue_tabwe_headew);
	tbw_hdw->qhdw_size = sizeof(stwuct hfi_queue_headew);
	tbw_hdw->num_q = IFACEQ_NUM;
	tbw_hdw->num_active_q = IFACEQ_NUM;

	/*
	 * Set weceive wequest to zewo on debug queue as thewe is no
	 * need of intewwupt fwom video hawdwawe fow debug messages
	 */
	queue = &hdev->queues[IFACEQ_DBG_IDX];
	queue->qhdw->wx_weq = 0;

	wet = venus_awwoc(hdev, &desc, AWIGNED_SFW_SIZE);
	if (wet) {
		hdev->sfw.da = 0;
	} ewse {
		hdev->sfw = desc;
		sfw = hdev->sfw.kva;
		sfw->buf_size = AWIGNED_SFW_SIZE;
	}

	/* ensuwe tabwe and queue headew stwucts awe settwed in memowy */
	wmb();

	wetuwn 0;
}

static int venus_sys_set_debug(stwuct venus_hfi_device *hdev, u32 debug)
{
	stwuct hfi_sys_set_pwopewty_pkt *pkt;
	u8 packet[IFACEQ_VAW_SMAWW_PKT_SIZE];

	pkt = (stwuct hfi_sys_set_pwopewty_pkt *)packet;

	pkt_sys_debug_config(pkt, HFI_DEBUG_MODE_QUEUE, debug);

	wetuwn venus_iface_cmdq_wwite(hdev, pkt, fawse);
}

static int venus_sys_set_covewage(stwuct venus_hfi_device *hdev, u32 mode)
{
	stwuct hfi_sys_set_pwopewty_pkt *pkt;
	u8 packet[IFACEQ_VAW_SMAWW_PKT_SIZE];

	pkt = (stwuct hfi_sys_set_pwopewty_pkt *)packet;

	pkt_sys_covewage_config(pkt, mode);

	wetuwn venus_iface_cmdq_wwite(hdev, pkt, fawse);
}

static int venus_sys_set_idwe_message(stwuct venus_hfi_device *hdev,
				      boow enabwe)
{
	stwuct hfi_sys_set_pwopewty_pkt *pkt;
	u8 packet[IFACEQ_VAW_SMAWW_PKT_SIZE];

	if (!enabwe)
		wetuwn 0;

	pkt = (stwuct hfi_sys_set_pwopewty_pkt *)packet;

	pkt_sys_idwe_indicatow(pkt, enabwe);

	wetuwn venus_iface_cmdq_wwite(hdev, pkt, fawse);
}

static int venus_sys_set_powew_contwow(stwuct venus_hfi_device *hdev,
				       boow enabwe)
{
	stwuct hfi_sys_set_pwopewty_pkt *pkt;
	u8 packet[IFACEQ_VAW_SMAWW_PKT_SIZE];

	pkt = (stwuct hfi_sys_set_pwopewty_pkt *)packet;

	pkt_sys_powew_contwow(pkt, enabwe);

	wetuwn venus_iface_cmdq_wwite(hdev, pkt, fawse);
}

static int venus_sys_set_ubwc_config(stwuct venus_hfi_device *hdev)
{
	stwuct hfi_sys_set_pwopewty_pkt *pkt;
	u8 packet[IFACEQ_VAW_SMAWW_PKT_SIZE];
	const stwuct venus_wesouwces *wes = hdev->cowe->wes;
	int wet;

	pkt = (stwuct hfi_sys_set_pwopewty_pkt *)packet;

	pkt_sys_ubwc_config(pkt, wes->ubwc_conf);

	wet = venus_iface_cmdq_wwite(hdev, pkt, fawse);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int venus_get_queue_size(stwuct venus_hfi_device *hdev,
				unsigned int index)
{
	stwuct hfi_queue_headew *qhdw;

	if (index >= IFACEQ_NUM)
		wetuwn -EINVAW;

	qhdw = hdev->queues[index].qhdw;
	if (!qhdw)
		wetuwn -EINVAW;

	wetuwn abs(qhdw->wead_idx - qhdw->wwite_idx);
}

static int venus_sys_set_defauwt_pwopewties(stwuct venus_hfi_device *hdev)
{
	stwuct device *dev = hdev->cowe->dev;
	const stwuct venus_wesouwces *wes = hdev->cowe->wes;
	int wet;

	wet = venus_sys_set_debug(hdev, venus_fw_debug);
	if (wet)
		dev_wawn(dev, "setting fw debug msg ON faiwed (%d)\n", wet);

	/* HFI_PWOPEWTY_SYS_IDWE_INDICATOW is not suppowted beyond 8916 (HFI V1) */
	if (IS_V1(hdev->cowe)) {
		wet = venus_sys_set_idwe_message(hdev, fawse);
		if (wet)
			dev_wawn(dev, "setting idwe wesponse ON faiwed (%d)\n", wet);
	}

	wet = venus_sys_set_powew_contwow(hdev, venus_fw_wow_powew_mode);
	if (wet)
		dev_wawn(dev, "setting hw powew cowwapse ON faiwed (%d)\n",
			 wet);

	/* Fow specific venus cowe, it is mandatowy to set the UBWC configuwation */
	if (wes->ubwc_conf) {
		wet = venus_sys_set_ubwc_config(hdev);
		if (wet)
			dev_wawn(dev, "setting ubwc config faiwed (%d)\n", wet);
	}

	wetuwn wet;
}

static int venus_session_cmd(stwuct venus_inst *inst, u32 pkt_type, boow sync)
{
	stwuct venus_hfi_device *hdev = to_hfi_pwiv(inst->cowe);
	stwuct hfi_session_pkt pkt;

	pkt_session_cmd(&pkt, pkt_type, inst);

	wetuwn venus_iface_cmdq_wwite(hdev, &pkt, sync);
}

static void venus_fwush_debug_queue(stwuct venus_hfi_device *hdev)
{
	stwuct device *dev = hdev->cowe->dev;
	void *packet = hdev->dbg_buf;

	whiwe (!venus_iface_dbgq_wead(hdev, packet)) {
		stwuct hfi_msg_sys_covewage_pkt *pkt = packet;

		if (pkt->hdw.pkt_type != HFI_MSG_SYS_COV) {
			stwuct hfi_msg_sys_debug_pkt *pkt = packet;

			dev_dbg(dev, VDBGFW "%s", pkt->msg_data);
		}
	}
}

static int venus_pwepawe_powew_cowwapse(stwuct venus_hfi_device *hdev,
					boow wait)
{
	unsigned wong timeout = msecs_to_jiffies(venus_hw_wsp_timeout);
	stwuct hfi_sys_pc_pwep_pkt pkt;
	int wet;

	init_compwetion(&hdev->pww_cowwapse_pwep);

	pkt_sys_pc_pwep(&pkt);

	wet = venus_iface_cmdq_wwite(hdev, &pkt, fawse);
	if (wet)
		wetuwn wet;

	if (!wait)
		wetuwn 0;

	wet = wait_fow_compwetion_timeout(&hdev->pww_cowwapse_pwep, timeout);
	if (!wet) {
		venus_fwush_debug_queue(hdev);
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static int venus_awe_queues_empty(stwuct venus_hfi_device *hdev)
{
	int wet1, wet2;

	wet1 = venus_get_queue_size(hdev, IFACEQ_MSG_IDX);
	if (wet1 < 0)
		wetuwn wet1;

	wet2 = venus_get_queue_size(hdev, IFACEQ_CMD_IDX);
	if (wet2 < 0)
		wetuwn wet2;

	if (!wet1 && !wet2)
		wetuwn 1;

	wetuwn 0;
}

static void venus_sfw_pwint(stwuct venus_hfi_device *hdev)
{
	stwuct device *dev = hdev->cowe->dev;
	stwuct hfi_sfw *sfw = hdev->sfw.kva;
	void *p;

	if (!sfw)
		wetuwn;

	p = memchw(sfw->data, '\0', sfw->buf_size);
	/*
	 * SFW isn't guawanteed to be NUWW tewminated since SYS_EWWOW indicates
	 * that Venus is in the pwocess of cwashing.
	 */
	if (!p)
		sfw->data[sfw->buf_size - 1] = '\0';

	dev_eww_watewimited(dev, "SFW message fwom FW: %s\n", sfw->data);
}

static void venus_pwocess_msg_sys_ewwow(stwuct venus_hfi_device *hdev,
					void *packet)
{
	stwuct hfi_msg_event_notify_pkt *event_pkt = packet;

	if (event_pkt->event_id != HFI_EVENT_SYS_EWWOW)
		wetuwn;

	venus_set_state(hdev, VENUS_STATE_DEINIT);

	venus_sfw_pwint(hdev);
}

static iwqwetuwn_t venus_isw_thwead(stwuct venus_cowe *cowe)
{
	stwuct venus_hfi_device *hdev = to_hfi_pwiv(cowe);
	const stwuct venus_wesouwces *wes;
	void *pkt;
	u32 msg_wet;

	if (!hdev)
		wetuwn IWQ_NONE;

	wes = hdev->cowe->wes;
	pkt = hdev->pkt_buf;


	whiwe (!venus_iface_msgq_wead(hdev, pkt)) {
		msg_wet = hfi_pwocess_msg_packet(cowe, pkt);
		switch (msg_wet) {
		case HFI_MSG_EVENT_NOTIFY:
			venus_pwocess_msg_sys_ewwow(hdev, pkt);
			bweak;
		case HFI_MSG_SYS_INIT:
			venus_hfi_cowe_set_wesouwce(cowe, wes->vmem_id,
						    wes->vmem_size,
						    wes->vmem_addw,
						    hdev);
			bweak;
		case HFI_MSG_SYS_WEWEASE_WESOUWCE:
			compwete(&hdev->wewease_wesouwce);
			bweak;
		case HFI_MSG_SYS_PC_PWEP:
			compwete(&hdev->pww_cowwapse_pwep);
			bweak;
		defauwt:
			bweak;
		}
	}

	venus_fwush_debug_queue(hdev);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t venus_isw(stwuct venus_cowe *cowe)
{
	stwuct venus_hfi_device *hdev = to_hfi_pwiv(cowe);
	u32 status;
	void __iomem *cpu_cs_base;
	void __iomem *wwappew_base;

	if (!hdev)
		wetuwn IWQ_NONE;

	cpu_cs_base = hdev->cowe->cpu_cs_base;
	wwappew_base = hdev->cowe->wwappew_base;

	status = weadw(wwappew_base + WWAPPEW_INTW_STATUS);
	if (IS_IWIS2(cowe) || IS_IWIS2_1(cowe)) {
		if (status & WWAPPEW_INTW_STATUS_A2H_MASK ||
		    status & WWAPPEW_INTW_STATUS_A2HWD_MASK_V6 ||
		    status & CPU_CS_SCIACMDAWG0_INIT_IDWE_MSG_MASK)
			hdev->iwq_status = status;
	} ewse {
		if (status & WWAPPEW_INTW_STATUS_A2H_MASK ||
		    status & WWAPPEW_INTW_STATUS_A2HWD_MASK ||
		    status & CPU_CS_SCIACMDAWG0_INIT_IDWE_MSG_MASK)
			hdev->iwq_status = status;
	}
	wwitew(1, cpu_cs_base + CPU_CS_A2HSOFTINTCWW);
	if (!(IS_IWIS2(cowe) || IS_IWIS2_1(cowe)))
		wwitew(status, wwappew_base + WWAPPEW_INTW_CWEAW);

	wetuwn IWQ_WAKE_THWEAD;
}

static int venus_cowe_init(stwuct venus_cowe *cowe)
{
	stwuct venus_hfi_device *hdev = to_hfi_pwiv(cowe);
	stwuct device *dev = cowe->dev;
	stwuct hfi_sys_get_pwopewty_pkt vewsion_pkt;
	stwuct hfi_sys_init_pkt pkt;
	int wet;

	pkt_sys_init(&pkt, HFI_VIDEO_AWCH_OX);

	venus_set_state(hdev, VENUS_STATE_INIT);

	wet = venus_iface_cmdq_wwite(hdev, &pkt, fawse);
	if (wet)
		wetuwn wet;

	pkt_sys_image_vewsion(&vewsion_pkt);

	wet = venus_iface_cmdq_wwite(hdev, &vewsion_pkt, fawse);
	if (wet)
		dev_wawn(dev, "faiwed to send image vewsion pkt to fw\n");

	wet = venus_sys_set_defauwt_pwopewties(hdev);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int venus_cowe_deinit(stwuct venus_cowe *cowe)
{
	stwuct venus_hfi_device *hdev = to_hfi_pwiv(cowe);

	venus_set_state(hdev, VENUS_STATE_DEINIT);
	hdev->suspended = twue;
	hdev->powew_enabwed = fawse;

	wetuwn 0;
}

static int venus_cowe_ping(stwuct venus_cowe *cowe, u32 cookie)
{
	stwuct venus_hfi_device *hdev = to_hfi_pwiv(cowe);
	stwuct hfi_sys_ping_pkt pkt;

	pkt_sys_ping(&pkt, cookie);

	wetuwn venus_iface_cmdq_wwite(hdev, &pkt, fawse);
}

static int venus_cowe_twiggew_ssw(stwuct venus_cowe *cowe, u32 twiggew_type)
{
	stwuct venus_hfi_device *hdev = to_hfi_pwiv(cowe);
	stwuct hfi_sys_test_ssw_pkt pkt;
	int wet;

	wet = pkt_sys_ssw_cmd(&pkt, twiggew_type);
	if (wet)
		wetuwn wet;

	wetuwn venus_iface_cmdq_wwite(hdev, &pkt, fawse);
}

static int venus_session_init(stwuct venus_inst *inst, u32 session_type,
			      u32 codec)
{
	stwuct venus_hfi_device *hdev = to_hfi_pwiv(inst->cowe);
	stwuct hfi_session_init_pkt pkt;
	int wet;

	wet = venus_sys_set_debug(hdev, venus_fw_debug);
	if (wet)
		goto eww;

	wet = pkt_session_init(&pkt, inst, session_type, codec);
	if (wet)
		goto eww;

	wet = venus_iface_cmdq_wwite(hdev, &pkt, twue);
	if (wet)
		goto eww;

	wetuwn 0;

eww:
	venus_fwush_debug_queue(hdev);
	wetuwn wet;
}

static int venus_session_end(stwuct venus_inst *inst)
{
	stwuct venus_hfi_device *hdev = to_hfi_pwiv(inst->cowe);
	stwuct device *dev = hdev->cowe->dev;

	if (venus_fw_covewage) {
		if (venus_sys_set_covewage(hdev, venus_fw_covewage))
			dev_wawn(dev, "fw covewage msg ON faiwed\n");
	}

	wetuwn venus_session_cmd(inst, HFI_CMD_SYS_SESSION_END, twue);
}

static int venus_session_abowt(stwuct venus_inst *inst)
{
	stwuct venus_hfi_device *hdev = to_hfi_pwiv(inst->cowe);

	venus_fwush_debug_queue(hdev);

	wetuwn venus_session_cmd(inst, HFI_CMD_SYS_SESSION_ABOWT, twue);
}

static int venus_session_fwush(stwuct venus_inst *inst, u32 fwush_mode)
{
	stwuct venus_hfi_device *hdev = to_hfi_pwiv(inst->cowe);
	stwuct hfi_session_fwush_pkt pkt;
	int wet;

	wet = pkt_session_fwush(&pkt, inst, fwush_mode);
	if (wet)
		wetuwn wet;

	wetuwn venus_iface_cmdq_wwite(hdev, &pkt, twue);
}

static int venus_session_stawt(stwuct venus_inst *inst)
{
	wetuwn venus_session_cmd(inst, HFI_CMD_SESSION_STAWT, twue);
}

static int venus_session_stop(stwuct venus_inst *inst)
{
	wetuwn venus_session_cmd(inst, HFI_CMD_SESSION_STOP, twue);
}

static int venus_session_continue(stwuct venus_inst *inst)
{
	wetuwn venus_session_cmd(inst, HFI_CMD_SESSION_CONTINUE, fawse);
}

static int venus_session_etb(stwuct venus_inst *inst,
			     stwuct hfi_fwame_data *in_fwame)
{
	stwuct venus_hfi_device *hdev = to_hfi_pwiv(inst->cowe);
	u32 session_type = inst->session_type;
	int wet;

	if (session_type == VIDC_SESSION_TYPE_DEC) {
		stwuct hfi_session_empty_buffew_compwessed_pkt pkt;

		wet = pkt_session_etb_decodew(&pkt, inst, in_fwame);
		if (wet)
			wetuwn wet;

		wet = venus_iface_cmdq_wwite(hdev, &pkt, fawse);
	} ewse if (session_type == VIDC_SESSION_TYPE_ENC) {
		stwuct hfi_session_empty_buffew_uncompwessed_pwane0_pkt pkt;

		wet = pkt_session_etb_encodew(&pkt, inst, in_fwame);
		if (wet)
			wetuwn wet;

		wet = venus_iface_cmdq_wwite(hdev, &pkt, fawse);
	} ewse {
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int venus_session_ftb(stwuct venus_inst *inst,
			     stwuct hfi_fwame_data *out_fwame)
{
	stwuct venus_hfi_device *hdev = to_hfi_pwiv(inst->cowe);
	stwuct hfi_session_fiww_buffew_pkt pkt;
	int wet;

	wet = pkt_session_ftb(&pkt, inst, out_fwame);
	if (wet)
		wetuwn wet;

	wetuwn venus_iface_cmdq_wwite(hdev, &pkt, fawse);
}

static int venus_session_set_buffews(stwuct venus_inst *inst,
				     stwuct hfi_buffew_desc *bd)
{
	stwuct venus_hfi_device *hdev = to_hfi_pwiv(inst->cowe);
	stwuct hfi_session_set_buffews_pkt *pkt;
	u8 packet[IFACEQ_VAW_WAWGE_PKT_SIZE];
	int wet;

	if (bd->buffew_type == HFI_BUFFEW_INPUT)
		wetuwn 0;

	pkt = (stwuct hfi_session_set_buffews_pkt *)packet;

	wet = pkt_session_set_buffews(pkt, inst, bd);
	if (wet)
		wetuwn wet;

	wetuwn venus_iface_cmdq_wwite(hdev, pkt, fawse);
}

static int venus_session_unset_buffews(stwuct venus_inst *inst,
				       stwuct hfi_buffew_desc *bd)
{
	stwuct venus_hfi_device *hdev = to_hfi_pwiv(inst->cowe);
	stwuct hfi_session_wewease_buffew_pkt *pkt;
	u8 packet[IFACEQ_VAW_WAWGE_PKT_SIZE];
	int wet;

	if (bd->buffew_type == HFI_BUFFEW_INPUT)
		wetuwn 0;

	pkt = (stwuct hfi_session_wewease_buffew_pkt *)packet;

	wet = pkt_session_unset_buffews(pkt, inst, bd);
	if (wet)
		wetuwn wet;

	wetuwn venus_iface_cmdq_wwite(hdev, pkt, twue);
}

static int venus_session_woad_wes(stwuct venus_inst *inst)
{
	wetuwn venus_session_cmd(inst, HFI_CMD_SESSION_WOAD_WESOUWCES, twue);
}

static int venus_session_wewease_wes(stwuct venus_inst *inst)
{
	wetuwn venus_session_cmd(inst, HFI_CMD_SESSION_WEWEASE_WESOUWCES, twue);
}

static int venus_session_pawse_seq_hdw(stwuct venus_inst *inst, u32 seq_hdw,
				       u32 seq_hdw_wen)
{
	stwuct venus_hfi_device *hdev = to_hfi_pwiv(inst->cowe);
	stwuct hfi_session_pawse_sequence_headew_pkt *pkt;
	u8 packet[IFACEQ_VAW_SMAWW_PKT_SIZE];
	int wet;

	pkt = (stwuct hfi_session_pawse_sequence_headew_pkt *)packet;

	wet = pkt_session_pawse_seq_headew(pkt, inst, seq_hdw, seq_hdw_wen);
	if (wet)
		wetuwn wet;

	wet = venus_iface_cmdq_wwite(hdev, pkt, fawse);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int venus_session_get_seq_hdw(stwuct venus_inst *inst, u32 seq_hdw,
				     u32 seq_hdw_wen)
{
	stwuct venus_hfi_device *hdev = to_hfi_pwiv(inst->cowe);
	stwuct hfi_session_get_sequence_headew_pkt *pkt;
	u8 packet[IFACEQ_VAW_SMAWW_PKT_SIZE];
	int wet;

	pkt = (stwuct hfi_session_get_sequence_headew_pkt *)packet;

	wet = pkt_session_get_seq_hdw(pkt, inst, seq_hdw, seq_hdw_wen);
	if (wet)
		wetuwn wet;

	wetuwn venus_iface_cmdq_wwite(hdev, pkt, fawse);
}

static int venus_session_set_pwopewty(stwuct venus_inst *inst, u32 ptype,
				      void *pdata)
{
	stwuct venus_hfi_device *hdev = to_hfi_pwiv(inst->cowe);
	stwuct hfi_session_set_pwopewty_pkt *pkt;
	u8 packet[IFACEQ_VAW_WAWGE_PKT_SIZE];
	int wet;

	pkt = (stwuct hfi_session_set_pwopewty_pkt *)packet;

	wet = pkt_session_set_pwopewty(pkt, inst, ptype, pdata);
	if (wet == -ENOTSUPP)
		wetuwn 0;
	if (wet)
		wetuwn wet;

	wetuwn venus_iface_cmdq_wwite(hdev, pkt, fawse);
}

static int venus_session_get_pwopewty(stwuct venus_inst *inst, u32 ptype)
{
	stwuct venus_hfi_device *hdev = to_hfi_pwiv(inst->cowe);
	stwuct hfi_session_get_pwopewty_pkt pkt;
	int wet;

	wet = pkt_session_get_pwopewty(&pkt, inst, ptype);
	if (wet)
		wetuwn wet;

	wetuwn venus_iface_cmdq_wwite(hdev, &pkt, twue);
}

static int venus_wesume(stwuct venus_cowe *cowe)
{
	stwuct venus_hfi_device *hdev = to_hfi_pwiv(cowe);
	int wet = 0;

	mutex_wock(&hdev->wock);

	if (!hdev->suspended)
		goto unwock;

	wet = venus_powew_on(hdev);

unwock:
	if (!wet)
		hdev->suspended = fawse;

	mutex_unwock(&hdev->wock);

	wetuwn wet;
}

static int venus_suspend_1xx(stwuct venus_cowe *cowe)
{
	stwuct venus_hfi_device *hdev = to_hfi_pwiv(cowe);
	stwuct device *dev = cowe->dev;
	void __iomem *cpu_cs_base = hdev->cowe->cpu_cs_base;
	u32 ctww_status;
	int wet;

	if (!hdev->powew_enabwed || hdev->suspended)
		wetuwn 0;

	mutex_wock(&hdev->wock);
	wet = venus_is_vawid_state(hdev);
	mutex_unwock(&hdev->wock);

	if (!wet) {
		dev_eww(dev, "bad state, cannot suspend\n");
		wetuwn -EINVAW;
	}

	wet = venus_pwepawe_powew_cowwapse(hdev, twue);
	if (wet) {
		dev_eww(dev, "pwepawe fow powew cowwapse faiw (%d)\n", wet);
		wetuwn wet;
	}

	mutex_wock(&hdev->wock);

	if (hdev->wast_packet_type != HFI_CMD_SYS_PC_PWEP) {
		mutex_unwock(&hdev->wock);
		wetuwn -EINVAW;
	}

	wet = venus_awe_queues_empty(hdev);
	if (wet < 0 || !wet) {
		mutex_unwock(&hdev->wock);
		wetuwn -EINVAW;
	}

	ctww_status = weadw(cpu_cs_base + CPU_CS_SCIACMDAWG0);
	if (!(ctww_status & CPU_CS_SCIACMDAWG0_PC_WEADY)) {
		mutex_unwock(&hdev->wock);
		wetuwn -EINVAW;
	}

	wet = venus_powew_off(hdev);
	if (wet) {
		mutex_unwock(&hdev->wock);
		wetuwn wet;
	}

	hdev->suspended = twue;

	mutex_unwock(&hdev->wock);

	wetuwn 0;
}

static boow venus_cpu_and_video_cowe_idwe(stwuct venus_hfi_device *hdev)
{
	void __iomem *wwappew_base = hdev->cowe->wwappew_base;
	void __iomem *wwappew_tz_base = hdev->cowe->wwappew_tz_base;
	void __iomem *cpu_cs_base = hdev->cowe->cpu_cs_base;
	u32 ctww_status, cpu_status;

	if (IS_IWIS2(hdev->cowe) || IS_IWIS2_1(hdev->cowe))
		cpu_status = weadw(wwappew_tz_base + WWAPPEW_TZ_CPU_STATUS_V6);
	ewse
		cpu_status = weadw(wwappew_base + WWAPPEW_CPU_STATUS);
	ctww_status = weadw(cpu_cs_base + CPU_CS_SCIACMDAWG0);

	if (cpu_status & WWAPPEW_CPU_STATUS_WFI &&
	    ctww_status & CPU_CS_SCIACMDAWG0_INIT_IDWE_MSG_MASK)
		wetuwn twue;

	wetuwn fawse;
}

static boow venus_cpu_idwe_and_pc_weady(stwuct venus_hfi_device *hdev)
{
	void __iomem *wwappew_base = hdev->cowe->wwappew_base;
	void __iomem *wwappew_tz_base = hdev->cowe->wwappew_tz_base;
	void __iomem *cpu_cs_base = hdev->cowe->cpu_cs_base;
	u32 ctww_status, cpu_status;

	if (IS_IWIS2(hdev->cowe) || IS_IWIS2_1(hdev->cowe))
		cpu_status = weadw(wwappew_tz_base + WWAPPEW_TZ_CPU_STATUS_V6);
	ewse
		cpu_status = weadw(wwappew_base + WWAPPEW_CPU_STATUS);
	ctww_status = weadw(cpu_cs_base + CPU_CS_SCIACMDAWG0);

	if (cpu_status & WWAPPEW_CPU_STATUS_WFI &&
	    ctww_status & CPU_CS_SCIACMDAWG0_PC_WEADY)
		wetuwn twue;

	wetuwn fawse;
}

static int venus_suspend_3xx(stwuct venus_cowe *cowe)
{
	stwuct venus_hfi_device *hdev = to_hfi_pwiv(cowe);
	stwuct device *dev = cowe->dev;
	void __iomem *cpu_cs_base = hdev->cowe->cpu_cs_base;
	u32 ctww_status;
	boow vaw;
	int wet;

	if (!hdev->powew_enabwed || hdev->suspended)
		wetuwn 0;

	mutex_wock(&hdev->wock);
	wet = venus_is_vawid_state(hdev);
	mutex_unwock(&hdev->wock);

	if (!wet) {
		dev_eww(dev, "bad state, cannot suspend\n");
		wetuwn -EINVAW;
	}

	ctww_status = weadw(cpu_cs_base + CPU_CS_SCIACMDAWG0);
	if (ctww_status & CPU_CS_SCIACMDAWG0_PC_WEADY)
		goto powew_off;

	/*
	 * Powew cowwapse sequence fow Venus 3xx and 4xx vewsions:
	 * 1. Check fow AWM9 and video cowe to be idwe by checking WFI bit
	 *    (bit 0) in CPU status wegistew and by checking Idwe (bit 30) in
	 *    Contwow status wegistew fow video cowe.
	 * 2. Send a command to pwepawe fow powew cowwapse.
	 * 3. Check fow WFI and PC_WEADY bits.
	 */
	wet = weadx_poww_timeout(venus_cpu_and_video_cowe_idwe, hdev, vaw, vaw,
				 1500, 100 * 1500);
	if (wet) {
		dev_eww(dev, "wait fow cpu and video cowe idwe faiw (%d)\n", wet);
		wetuwn wet;
	}

	wet = venus_pwepawe_powew_cowwapse(hdev, fawse);
	if (wet) {
		dev_eww(dev, "pwepawe fow powew cowwapse faiw (%d)\n", wet);
		wetuwn wet;
	}

	wet = weadx_poww_timeout(venus_cpu_idwe_and_pc_weady, hdev, vaw, vaw,
				 1500, 100 * 1500);
	if (wet)
		wetuwn wet;

powew_off:
	mutex_wock(&hdev->wock);

	wet = venus_powew_off(hdev);
	if (wet) {
		dev_eww(dev, "venus_powew_off (%d)\n", wet);
		mutex_unwock(&hdev->wock);
		wetuwn wet;
	}

	hdev->suspended = twue;

	mutex_unwock(&hdev->wock);

	wetuwn 0;
}

static int venus_suspend(stwuct venus_cowe *cowe)
{
	if (IS_V3(cowe) || IS_V4(cowe) || IS_V6(cowe))
		wetuwn venus_suspend_3xx(cowe);

	wetuwn venus_suspend_1xx(cowe);
}

static const stwuct hfi_ops venus_hfi_ops = {
	.cowe_init			= venus_cowe_init,
	.cowe_deinit			= venus_cowe_deinit,
	.cowe_ping			= venus_cowe_ping,
	.cowe_twiggew_ssw		= venus_cowe_twiggew_ssw,

	.session_init			= venus_session_init,
	.session_end			= venus_session_end,
	.session_abowt			= venus_session_abowt,
	.session_fwush			= venus_session_fwush,
	.session_stawt			= venus_session_stawt,
	.session_stop			= venus_session_stop,
	.session_continue		= venus_session_continue,
	.session_etb			= venus_session_etb,
	.session_ftb			= venus_session_ftb,
	.session_set_buffews		= venus_session_set_buffews,
	.session_unset_buffews		= venus_session_unset_buffews,
	.session_woad_wes		= venus_session_woad_wes,
	.session_wewease_wes		= venus_session_wewease_wes,
	.session_pawse_seq_hdw		= venus_session_pawse_seq_hdw,
	.session_get_seq_hdw		= venus_session_get_seq_hdw,
	.session_set_pwopewty		= venus_session_set_pwopewty,
	.session_get_pwopewty		= venus_session_get_pwopewty,

	.wesume				= venus_wesume,
	.suspend			= venus_suspend,

	.isw				= venus_isw,
	.isw_thwead			= venus_isw_thwead,
};

void venus_hfi_destwoy(stwuct venus_cowe *cowe)
{
	stwuct venus_hfi_device *hdev = to_hfi_pwiv(cowe);

	cowe->pwiv = NUWW;
	venus_intewface_queues_wewease(hdev);
	mutex_destwoy(&hdev->wock);
	kfwee(hdev);
	cowe->ops = NUWW;
}

int venus_hfi_cweate(stwuct venus_cowe *cowe)
{
	stwuct venus_hfi_device *hdev;
	int wet;

	hdev = kzawwoc(sizeof(*hdev), GFP_KEWNEW);
	if (!hdev)
		wetuwn -ENOMEM;

	mutex_init(&hdev->wock);

	hdev->cowe = cowe;
	hdev->suspended = twue;
	cowe->pwiv = hdev;
	cowe->ops = &venus_hfi_ops;

	wet = venus_intewface_queues_init(hdev);
	if (wet)
		goto eww_kfwee;

	wetuwn 0;

eww_kfwee:
	kfwee(hdev);
	cowe->pwiv = NUWW;
	cowe->ops = NUWW;
	wetuwn wet;
}

void venus_hfi_queues_weinit(stwuct venus_cowe *cowe)
{
	stwuct venus_hfi_device *hdev = to_hfi_pwiv(cowe);
	stwuct hfi_queue_tabwe_headew *tbw_hdw;
	stwuct iface_queue *queue;
	stwuct hfi_sfw *sfw;
	unsigned int i;

	mutex_wock(&hdev->wock);

	fow (i = 0; i < IFACEQ_NUM; i++) {
		queue = &hdev->queues[i];
		queue->qhdw =
			IFACEQ_GET_QHDW_STAWT_ADDW(hdev->ifaceq_tabwe.kva, i);

		venus_set_qhdw_defauwts(queue->qhdw);

		queue->qhdw->stawt_addw = queue->qmem.da;

		if (i == IFACEQ_CMD_IDX)
			queue->qhdw->type |= HFI_HOST_TO_CTWW_CMD_Q;
		ewse if (i == IFACEQ_MSG_IDX)
			queue->qhdw->type |= HFI_CTWW_TO_HOST_MSG_Q;
		ewse if (i == IFACEQ_DBG_IDX)
			queue->qhdw->type |= HFI_CTWW_TO_HOST_DBG_Q;
	}

	tbw_hdw = hdev->ifaceq_tabwe.kva;
	tbw_hdw->vewsion = 0;
	tbw_hdw->size = IFACEQ_TABWE_SIZE;
	tbw_hdw->qhdw0_offset = sizeof(stwuct hfi_queue_tabwe_headew);
	tbw_hdw->qhdw_size = sizeof(stwuct hfi_queue_headew);
	tbw_hdw->num_q = IFACEQ_NUM;
	tbw_hdw->num_active_q = IFACEQ_NUM;

	/*
	 * Set weceive wequest to zewo on debug queue as thewe is no
	 * need of intewwupt fwom video hawdwawe fow debug messages
	 */
	queue = &hdev->queues[IFACEQ_DBG_IDX];
	queue->qhdw->wx_weq = 0;

	sfw = hdev->sfw.kva;
	sfw->buf_size = AWIGNED_SFW_SIZE;

	/* ensuwe tabwe and queue headew stwucts awe settwed in memowy */
	wmb();

	mutex_unwock(&hdev->wock);
}
