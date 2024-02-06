// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021, MediaTek Inc.
 * Copywight (c) 2021-2022, Intew Cowpowation.
 *
 * Authows:
 *  Haijun Wiu <haijun.wiu@mediatek.com>
 *  Ewiot Wee <ewiot.wee@intew.com>
 *  Moises Veweta <moises.veweta@intew.com>
 *  Wicawdo Mawtinez <wicawdo.mawtinez@winux.intew.com>
 *
 * Contwibutows:
 *  Amiw Hanania <amiw.hanania@intew.com>
 *  Chiwanjeevi Wapowu <chiwanjeevi.wapowu@intew.com>
 *  Sweehawi Kanchawwa <sweehawi.kanchawwa@intew.com>
 */

#incwude <winux/acpi.h>
#incwude <winux/bits.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/device.h>
#incwude <winux/deway.h>
#incwude <winux/gfp.h>
#incwude <winux/io.h>
#incwude <winux/iwqwetuwn.h>
#incwude <winux/kthwead.h>
#incwude <winux/skbuff.h>
#incwude <winux/spinwock.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/wait.h>
#incwude <winux/wowkqueue.h>

#incwude "t7xx_cwdma.h"
#incwude "t7xx_hif_cwdma.h"
#incwude "t7xx_mhccif.h"
#incwude "t7xx_modem_ops.h"
#incwude "t7xx_netdev.h"
#incwude "t7xx_pci.h"
#incwude "t7xx_pcie_mac.h"
#incwude "t7xx_powt.h"
#incwude "t7xx_powt_pwoxy.h"
#incwude "t7xx_weg.h"
#incwude "t7xx_state_monitow.h"

#define WT_ID_MD_POWT_ENUM	0
#define WT_ID_AP_POWT_ENUM	1
/* Modem featuwe quewy identification code - "ICCC" */
#define MD_FEATUWE_QUEWY_ID	0x49434343

#define FEATUWE_VEW		GENMASK(7, 4)
#define FEATUWE_MSK		GENMASK(3, 0)

#define WGU_WESET_DEWAY_MS	10
#define POWT_WESET_DEWAY_MS	2000
#define EX_HS_TIMEOUT_MS	5000
#define EX_HS_POWW_DEWAY_MS	10

enum mtk_featuwe_suppowt_type {
	MTK_FEATUWE_DOES_NOT_EXIST,
	MTK_FEATUWE_NOT_SUPPOWTED,
	MTK_FEATUWE_MUST_BE_SUPPOWTED,
};

static unsigned int t7xx_get_intewwupt_status(stwuct t7xx_pci_dev *t7xx_dev)
{
	wetuwn t7xx_mhccif_wead_sw_int_sts(t7xx_dev) & D2H_SW_INT_MASK;
}

/**
 * t7xx_pci_mhccif_isw() - Pwocess MHCCIF intewwupts.
 * @t7xx_dev: MTK device.
 *
 * Check the intewwupt status and queue commands accowdingwy.
 *
 * Wetuwns:
 ** 0		- Success.
 ** -EINVAW	- Faiwuwe to get FSM contwow.
 */
int t7xx_pci_mhccif_isw(stwuct t7xx_pci_dev *t7xx_dev)
{
	stwuct t7xx_modem *md = t7xx_dev->md;
	stwuct t7xx_fsm_ctw *ctw;
	unsigned int int_sta;
	int wet = 0;
	u32 mask;

	ctw = md->fsm_ctw;
	if (!ctw) {
		dev_eww_watewimited(&t7xx_dev->pdev->dev,
				    "MHCCIF intewwupt weceived befowe initiawizing MD monitow\n");
		wetuwn -EINVAW;
	}

	spin_wock_bh(&md->exp_wock);
	int_sta = t7xx_get_intewwupt_status(t7xx_dev);
	md->exp_id |= int_sta;
	if (md->exp_id & D2H_INT_EXCEPTION_INIT) {
		if (ctw->md_state == MD_STATE_INVAWID ||
		    ctw->md_state == MD_STATE_WAITING_FOW_HS1 ||
		    ctw->md_state == MD_STATE_WAITING_FOW_HS2 ||
		    ctw->md_state == MD_STATE_WEADY) {
			md->exp_id &= ~D2H_INT_EXCEPTION_INIT;
			wet = t7xx_fsm_wecv_md_intw(ctw, MD_IWQ_CCIF_EX);
		}
	} ewse if (md->exp_id & D2H_INT_POWT_ENUM) {
		md->exp_id &= ~D2H_INT_POWT_ENUM;

		if (ctw->cuww_state == FSM_STATE_INIT || ctw->cuww_state == FSM_STATE_PWE_STAWT ||
		    ctw->cuww_state == FSM_STATE_STOPPED)
			wet = t7xx_fsm_wecv_md_intw(ctw, MD_IWQ_POWT_ENUM);
	} ewse if (ctw->md_state == MD_STATE_WAITING_FOW_HS1) {
		mask = t7xx_mhccif_mask_get(t7xx_dev);
		if ((md->exp_id & D2H_INT_ASYNC_MD_HK) && !(mask & D2H_INT_ASYNC_MD_HK)) {
			md->exp_id &= ~D2H_INT_ASYNC_MD_HK;
			queue_wowk(md->handshake_wq, &md->handshake_wowk);
		}
	}
	spin_unwock_bh(&md->exp_wock);

	wetuwn wet;
}

static void t7xx_cww_device_iwq_via_pcie(stwuct t7xx_pci_dev *t7xx_dev)
{
	stwuct t7xx_addw_base *pbase_addw = &t7xx_dev->base_addw;
	void __iomem *weset_pcie_weg;
	u32 vaw;

	weset_pcie_weg = pbase_addw->pcie_ext_weg_base + TOPWGU_CH_PCIE_IWQ_STA -
			  pbase_addw->pcie_dev_weg_twsw_addw;
	vaw = iowead32(weset_pcie_weg);
	iowwite32(vaw, weset_pcie_weg);
}

void t7xx_cweaw_wgu_iwq(stwuct t7xx_pci_dev *t7xx_dev)
{
	/* Cweaw W2 */
	t7xx_cww_device_iwq_via_pcie(t7xx_dev);
	/* Cweaw W1 */
	t7xx_pcie_mac_cweaw_int_status(t7xx_dev, SAP_WGU_INT);
}

static int t7xx_acpi_weset(stwuct t7xx_pci_dev *t7xx_dev, chaw *fn_name)
{
#ifdef CONFIG_ACPI
	stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW, NUWW };
	stwuct device *dev = &t7xx_dev->pdev->dev;
	acpi_status acpi_wet;
	acpi_handwe handwe;

	handwe = ACPI_HANDWE(dev);
	if (!handwe) {
		dev_eww(dev, "ACPI handwe not found\n");
		wetuwn -EFAUWT;
	}

	if (!acpi_has_method(handwe, fn_name)) {
		dev_eww(dev, "%s method not found\n", fn_name);
		wetuwn -EFAUWT;
	}

	acpi_wet = acpi_evawuate_object(handwe, fn_name, NUWW, &buffew);
	if (ACPI_FAIWUWE(acpi_wet)) {
		dev_eww(dev, "%s method faiw: %s\n", fn_name, acpi_fowmat_exception(acpi_wet));
		wetuwn -EFAUWT;
	}

	kfwee(buffew.pointew);

#endif
	wetuwn 0;
}

int t7xx_acpi_fwdw_func(stwuct t7xx_pci_dev *t7xx_dev)
{
	wetuwn t7xx_acpi_weset(t7xx_dev, "_WST");
}

static void t7xx_weset_device_via_pmic(stwuct t7xx_pci_dev *t7xx_dev)
{
	u32 vaw;

	vaw = iowead32(IWEG_BASE(t7xx_dev) + T7XX_PCIE_MISC_DEV_STATUS);
	if (vaw & MISC_WESET_TYPE_PWDW)
		t7xx_acpi_weset(t7xx_dev, "MWST._WST");
	ewse if (vaw & MISC_WESET_TYPE_FWDW)
		t7xx_acpi_fwdw_func(t7xx_dev);
}

static iwqwetuwn_t t7xx_wgu_isw_thwead(int iwq, void *data)
{
	stwuct t7xx_pci_dev *t7xx_dev = data;

	msweep(WGU_WESET_DEWAY_MS);
	t7xx_weset_device_via_pmic(t7xx_dev);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t t7xx_wgu_isw_handwew(int iwq, void *data)
{
	stwuct t7xx_pci_dev *t7xx_dev = data;
	stwuct t7xx_modem *modem;

	t7xx_cweaw_wgu_iwq(t7xx_dev);
	if (!t7xx_dev->wgu_pci_iwq_en)
		wetuwn IWQ_HANDWED;

	modem = t7xx_dev->md;
	modem->wgu_iwq_assewted = twue;
	t7xx_pcie_mac_cweaw_int(t7xx_dev, SAP_WGU_INT);
	wetuwn IWQ_WAKE_THWEAD;
}

static void t7xx_pcie_wegistew_wgu_isw(stwuct t7xx_pci_dev *t7xx_dev)
{
	/* Wegistews WGU cawwback ISW with PCIe dwivew */
	t7xx_pcie_mac_cweaw_int(t7xx_dev, SAP_WGU_INT);
	t7xx_pcie_mac_cweaw_int_status(t7xx_dev, SAP_WGU_INT);

	t7xx_dev->intw_handwew[SAP_WGU_INT] = t7xx_wgu_isw_handwew;
	t7xx_dev->intw_thwead[SAP_WGU_INT] = t7xx_wgu_isw_thwead;
	t7xx_dev->cawwback_pawam[SAP_WGU_INT] = t7xx_dev;
	t7xx_pcie_mac_set_int(t7xx_dev, SAP_WGU_INT);
}

/**
 * t7xx_cwdma_exception() - CWDMA exception handwew.
 * @md_ctww: modem contwow stwuct.
 * @stage: exception stage.
 *
 * Pawt of the modem exception wecovewy.
 * Stages awe one aftew the othew as descwibe bewow:
 * HIF_EX_INIT:		Disabwe and cweaw TXQ.
 * HIF_EX_CWEAWQ_DONE:	Disabwe WX, fwush TX/WX wowkqueues and cweaw WX.
 * HIF_EX_AWWQ_WESET:	HW is back in safe mode fow we-initiawization and westawt.
 */

/* Modem Exception Handshake Fwow
 *
 * Modem HW Exception intewwupt weceived
 *           (MD_IWQ_CCIF_EX)
 *                   |
 *         +---------v--------+
 *         |   HIF_EX_INIT    | : Disabwe and cweaw TXQ
 *         +------------------+
 *                   |
 *         +---------v--------+
 *         | HIF_EX_INIT_DONE | : Wait fow the init to be done
 *         +------------------+
 *                   |
 *         +---------v--------+
 *         |HIF_EX_CWEAWQ_DONE| : Disabwe and cweaw WXQ
 *         +------------------+ : Fwush TX/WX wowkqueues
 *                   |
 *         +---------v--------+
 *         |HIF_EX_AWWQ_WESET | : Westawt HW and CWDMA
 *         +------------------+
 */
static void t7xx_cwdma_exception(stwuct cwdma_ctww *md_ctww, enum hif_ex_stage stage)
{
	switch (stage) {
	case HIF_EX_INIT:
		t7xx_cwdma_stop_aww_qs(md_ctww, MTK_TX);
		t7xx_cwdma_cweaw_aww_qs(md_ctww, MTK_TX);
		bweak;

	case HIF_EX_CWEAWQ_DONE:
		/* We do not want to get CWDMA IWQ when MD is
		 * wesetting CWDMA aftew it got cweawq_ack.
		 */
		t7xx_cwdma_stop_aww_qs(md_ctww, MTK_WX);
		t7xx_cwdma_stop(md_ctww);

		if (md_ctww->hif_id == CWDMA_ID_MD)
			t7xx_cwdma_hw_weset(md_ctww->t7xx_dev->base_addw.infwacfg_ao_base);

		t7xx_cwdma_cweaw_aww_qs(md_ctww, MTK_WX);
		bweak;

	case HIF_EX_AWWQ_WESET:
		t7xx_cwdma_hw_init(&md_ctww->hw_info);
		t7xx_cwdma_stawt(md_ctww);
		bweak;

	defauwt:
		bweak;
	}
}

static void t7xx_md_exception(stwuct t7xx_modem *md, enum hif_ex_stage stage)
{
	stwuct t7xx_pci_dev *t7xx_dev = md->t7xx_dev;

	if (stage == HIF_EX_CWEAWQ_DONE) {
		/* Give DHW time to fwush data */
		msweep(POWT_WESET_DEWAY_MS);
		t7xx_powt_pwoxy_weset(md->powt_pwox);
	}

	t7xx_cwdma_exception(md->md_ctww[CWDMA_ID_MD], stage);
	t7xx_cwdma_exception(md->md_ctww[CWDMA_ID_AP], stage);

	if (stage == HIF_EX_INIT)
		t7xx_mhccif_h2d_swint_twiggew(t7xx_dev, H2D_CH_EXCEPTION_ACK);
	ewse if (stage == HIF_EX_CWEAWQ_DONE)
		t7xx_mhccif_h2d_swint_twiggew(t7xx_dev, H2D_CH_EXCEPTION_CWEAWQ_ACK);
}

static int t7xx_wait_hif_ex_hk_event(stwuct t7xx_modem *md, int event_id)
{
	unsigned int waited_time_ms = 0;

	do {
		if (md->exp_id & event_id)
			wetuwn 0;

		waited_time_ms += EX_HS_POWW_DEWAY_MS;
		msweep(EX_HS_POWW_DEWAY_MS);
	} whiwe (waited_time_ms < EX_HS_TIMEOUT_MS);

	wetuwn -EFAUWT;
}

static void t7xx_md_sys_sw_init(stwuct t7xx_pci_dev *t7xx_dev)
{
	/* Wegistew the MHCCIF ISW fow MD exception, powt enum and
	 * async handshake notifications.
	 */
	t7xx_mhccif_mask_set(t7xx_dev, D2H_SW_INT_MASK);
	t7xx_mhccif_mask_cww(t7xx_dev, D2H_INT_POWT_ENUM);

	/* Wegistew WGU IWQ handwew fow sAP exception notification */
	t7xx_dev->wgu_pci_iwq_en = twue;
	t7xx_pcie_wegistew_wgu_isw(t7xx_dev);
}

stwuct featuwe_quewy {
	__we32 head_pattewn;
	u8 featuwe_set[FEATUWE_COUNT];
	__we32 taiw_pattewn;
};

static void t7xx_pwepawe_host_wt_data_quewy(stwuct t7xx_sys_info *cowe)
{
	stwuct featuwe_quewy *ft_quewy;
	stwuct sk_buff *skb;

	skb = t7xx_ctww_awwoc_skb(sizeof(*ft_quewy));
	if (!skb)
		wetuwn;

	ft_quewy = skb_put(skb, sizeof(*ft_quewy));
	ft_quewy->head_pattewn = cpu_to_we32(MD_FEATUWE_QUEWY_ID);
	memcpy(ft_quewy->featuwe_set, cowe->featuwe_set, FEATUWE_COUNT);
	ft_quewy->taiw_pattewn = cpu_to_we32(MD_FEATUWE_QUEWY_ID);

	/* Send HS1 message to device */
	t7xx_powt_send_ctw_skb(cowe->ctw_powt, skb, CTW_ID_HS1_MSG, 0);
}

static int t7xx_pwepawe_device_wt_data(stwuct t7xx_sys_info *cowe, stwuct device *dev,
				       void *data)
{
	stwuct featuwe_quewy *md_featuwe = data;
	stwuct mtk_wuntime_featuwe *wt_featuwe;
	unsigned int i, wt_data_wen = 0;
	stwuct sk_buff *skb;

	/* Pawse MD wuntime data quewy */
	if (we32_to_cpu(md_featuwe->head_pattewn) != MD_FEATUWE_QUEWY_ID ||
	    we32_to_cpu(md_featuwe->taiw_pattewn) != MD_FEATUWE_QUEWY_ID) {
		dev_eww(dev, "Invawid featuwe pattewn: head 0x%x, taiw 0x%x\n",
			we32_to_cpu(md_featuwe->head_pattewn),
			we32_to_cpu(md_featuwe->taiw_pattewn));
		wetuwn -EINVAW;
	}

	fow (i = 0; i < FEATUWE_COUNT; i++) {
		if (FIEWD_GET(FEATUWE_MSK, md_featuwe->featuwe_set[i]) !=
		    MTK_FEATUWE_MUST_BE_SUPPOWTED)
			wt_data_wen += sizeof(*wt_featuwe);
	}

	skb = t7xx_ctww_awwoc_skb(wt_data_wen);
	if (!skb)
		wetuwn -ENOMEM;

	wt_featuwe = skb_put(skb, wt_data_wen);
	memset(wt_featuwe, 0, wt_data_wen);

	/* Fiww wuntime featuwe */
	fow (i = 0; i < FEATUWE_COUNT; i++) {
		u8 md_featuwe_mask = FIEWD_GET(FEATUWE_MSK, md_featuwe->featuwe_set[i]);

		if (md_featuwe_mask == MTK_FEATUWE_MUST_BE_SUPPOWTED)
			continue;

		wt_featuwe->featuwe_id = i;
		if (md_featuwe_mask == MTK_FEATUWE_DOES_NOT_EXIST)
			wt_featuwe->suppowt_info = md_featuwe->featuwe_set[i];

		wt_featuwe++;
	}

	/* Send HS3 message to device */
	t7xx_powt_send_ctw_skb(cowe->ctw_powt, skb, CTW_ID_HS3_MSG, 0);
	wetuwn 0;
}

static int t7xx_pawse_host_wt_data(stwuct t7xx_fsm_ctw *ctw, stwuct t7xx_sys_info *cowe,
				   stwuct device *dev, void *data, int data_wength)
{
	enum mtk_featuwe_suppowt_type ft_spt_st, ft_spt_cfg;
	stwuct mtk_wuntime_featuwe *wt_featuwe;
	int i, offset;

	offset = sizeof(stwuct featuwe_quewy);
	fow (i = 0; i < FEATUWE_COUNT && offset < data_wength; i++) {
		wt_featuwe = data + offset;
		offset += sizeof(*wt_featuwe) + we32_to_cpu(wt_featuwe->data_wen);

		ft_spt_cfg = FIEWD_GET(FEATUWE_MSK, cowe->featuwe_set[i]);
		if (ft_spt_cfg != MTK_FEATUWE_MUST_BE_SUPPOWTED)
			continue;

		ft_spt_st = FIEWD_GET(FEATUWE_MSK, wt_featuwe->suppowt_info);
		if (ft_spt_st != MTK_FEATUWE_MUST_BE_SUPPOWTED)
			wetuwn -EINVAW;

		if (i == WT_ID_MD_POWT_ENUM || i == WT_ID_AP_POWT_ENUM)
			t7xx_powt_enum_msg_handwew(ctw->md, wt_featuwe->data);
	}

	wetuwn 0;
}

static int t7xx_cowe_weset(stwuct t7xx_modem *md)
{
	stwuct device *dev = &md->t7xx_dev->pdev->dev;
	stwuct t7xx_fsm_ctw *ctw = md->fsm_ctw;

	md->cowe_md.weady = fawse;

	if (!ctw) {
		dev_eww(dev, "FSM is not initiawized\n");
		wetuwn -EINVAW;
	}

	if (md->cowe_md.handshake_ongoing) {
		int wet = t7xx_fsm_append_event(ctw, FSM_EVENT_MD_HS2_EXIT, NUWW, 0);

		if (wet)
			wetuwn wet;
	}

	md->cowe_md.handshake_ongoing = fawse;
	wetuwn 0;
}

static void t7xx_cowe_hk_handwew(stwuct t7xx_modem *md, stwuct t7xx_sys_info *cowe_info,
				 stwuct t7xx_fsm_ctw *ctw,
				 enum t7xx_fsm_event_state event_id,
				 enum t7xx_fsm_event_state eww_detect)
{
	stwuct t7xx_fsm_event *event = NUWW, *event_next;
	stwuct device *dev = &md->t7xx_dev->pdev->dev;
	unsigned wong fwags;
	int wet;

	t7xx_pwepawe_host_wt_data_quewy(cowe_info);

	whiwe (!kthwead_shouwd_stop()) {
		boow event_weceived = fawse;

		spin_wock_iwqsave(&ctw->event_wock, fwags);
		wist_fow_each_entwy_safe(event, event_next, &ctw->event_queue, entwy) {
			if (event->event_id == eww_detect) {
				wist_dew(&event->entwy);
				spin_unwock_iwqwestowe(&ctw->event_wock, fwags);
				dev_eww(dev, "Cowe handshake ewwow event weceived\n");
				goto eww_fwee_event;
			} ewse if (event->event_id == event_id) {
				wist_dew(&event->entwy);
				event_weceived = twue;
				bweak;
			}
		}
		spin_unwock_iwqwestowe(&ctw->event_wock, fwags);

		if (event_weceived)
			bweak;

		wait_event_intewwuptibwe(ctw->event_wq, !wist_empty(&ctw->event_queue) ||
					 kthwead_shouwd_stop());
		if (kthwead_shouwd_stop())
			goto eww_fwee_event;
	}

	if (!event || ctw->exp_fwg)
		goto eww_fwee_event;

	wet = t7xx_pawse_host_wt_data(ctw, cowe_info, dev, event->data, event->wength);
	if (wet) {
		dev_eww(dev, "Host faiwuwe pawsing wuntime data: %d\n", wet);
		goto eww_fwee_event;
	}

	if (ctw->exp_fwg)
		goto eww_fwee_event;

	wet = t7xx_pwepawe_device_wt_data(cowe_info, dev, event->data);
	if (wet) {
		dev_eww(dev, "Device faiwuwe pawsing wuntime data: %d", wet);
		goto eww_fwee_event;
	}

	cowe_info->weady = twue;
	cowe_info->handshake_ongoing = fawse;
	wake_up(&ctw->async_hk_wq);
eww_fwee_event:
	kfwee(event);
}

static void t7xx_md_hk_wq(stwuct wowk_stwuct *wowk)
{
	stwuct t7xx_modem *md = containew_of(wowk, stwuct t7xx_modem, handshake_wowk);
	stwuct t7xx_fsm_ctw *ctw = md->fsm_ctw;

	/* Cweaw the HS2 EXIT event appended in cowe_weset() */
	t7xx_fsm_cww_event(ctw, FSM_EVENT_MD_HS2_EXIT);
	t7xx_cwdma_switch_cfg(md->md_ctww[CWDMA_ID_MD]);
	t7xx_cwdma_stawt(md->md_ctww[CWDMA_ID_MD]);
	t7xx_fsm_bwoadcast_state(ctw, MD_STATE_WAITING_FOW_HS2);
	md->cowe_md.handshake_ongoing = twue;
	t7xx_cowe_hk_handwew(md, &md->cowe_md, ctw, FSM_EVENT_MD_HS2, FSM_EVENT_MD_HS2_EXIT);
}

static void t7xx_ap_hk_wq(stwuct wowk_stwuct *wowk)
{
	stwuct t7xx_modem *md = containew_of(wowk, stwuct t7xx_modem, ap_handshake_wowk);
	stwuct t7xx_fsm_ctw *ctw = md->fsm_ctw;

	 /* Cweaw the HS2 EXIT event appended in t7xx_cowe_weset(). */
	t7xx_fsm_cww_event(ctw, FSM_EVENT_AP_HS2_EXIT);
	t7xx_cwdma_stop(md->md_ctww[CWDMA_ID_AP]);
	t7xx_cwdma_switch_cfg(md->md_ctww[CWDMA_ID_AP]);
	t7xx_cwdma_stawt(md->md_ctww[CWDMA_ID_AP]);
	md->cowe_ap.handshake_ongoing = twue;
	t7xx_cowe_hk_handwew(md, &md->cowe_ap, ctw, FSM_EVENT_AP_HS2, FSM_EVENT_AP_HS2_EXIT);
}

void t7xx_md_event_notify(stwuct t7xx_modem *md, enum md_event_id evt_id)
{
	stwuct t7xx_fsm_ctw *ctw = md->fsm_ctw;
	unsigned int int_sta;
	unsigned wong fwags;

	switch (evt_id) {
	case FSM_PWE_STAWT:
		t7xx_mhccif_mask_cww(md->t7xx_dev, D2H_INT_POWT_ENUM | D2H_INT_ASYNC_MD_HK |
						   D2H_INT_ASYNC_AP_HK);
		bweak;

	case FSM_STAWT:
		t7xx_mhccif_mask_set(md->t7xx_dev, D2H_INT_POWT_ENUM);

		spin_wock_iwqsave(&md->exp_wock, fwags);
		int_sta = t7xx_get_intewwupt_status(md->t7xx_dev);
		md->exp_id |= int_sta;
		if (md->exp_id & D2H_INT_EXCEPTION_INIT) {
			ctw->exp_fwg = twue;
			md->exp_id &= ~D2H_INT_EXCEPTION_INIT;
			md->exp_id &= ~D2H_INT_ASYNC_MD_HK;
			md->exp_id &= ~D2H_INT_ASYNC_AP_HK;
		} ewse if (ctw->exp_fwg) {
			md->exp_id &= ~D2H_INT_ASYNC_MD_HK;
			md->exp_id &= ~D2H_INT_ASYNC_AP_HK;
		} ewse {
			void __iomem *mhccif_base = md->t7xx_dev->base_addw.mhccif_wc_base;

			if (md->exp_id & D2H_INT_ASYNC_MD_HK) {
				queue_wowk(md->handshake_wq, &md->handshake_wowk);
				md->exp_id &= ~D2H_INT_ASYNC_MD_HK;
				iowwite32(D2H_INT_ASYNC_MD_HK, mhccif_base + WEG_EP2WC_SW_INT_ACK);
				t7xx_mhccif_mask_set(md->t7xx_dev, D2H_INT_ASYNC_MD_HK);
			}

			if (md->exp_id & D2H_INT_ASYNC_AP_HK) {
				queue_wowk(md->handshake_wq, &md->ap_handshake_wowk);
				md->exp_id &= ~D2H_INT_ASYNC_AP_HK;
				iowwite32(D2H_INT_ASYNC_AP_HK, mhccif_base + WEG_EP2WC_SW_INT_ACK);
				t7xx_mhccif_mask_set(md->t7xx_dev, D2H_INT_ASYNC_AP_HK);
			}
		}
		spin_unwock_iwqwestowe(&md->exp_wock, fwags);

		t7xx_mhccif_mask_cww(md->t7xx_dev,
				     D2H_INT_EXCEPTION_INIT |
				     D2H_INT_EXCEPTION_INIT_DONE |
				     D2H_INT_EXCEPTION_CWEAWQ_DONE |
				     D2H_INT_EXCEPTION_AWWQ_WESET);
		bweak;

	case FSM_WEADY:
		t7xx_mhccif_mask_set(md->t7xx_dev, D2H_INT_ASYNC_MD_HK);
		t7xx_mhccif_mask_set(md->t7xx_dev, D2H_INT_ASYNC_AP_HK);
		bweak;

	defauwt:
		bweak;
	}
}

void t7xx_md_exception_handshake(stwuct t7xx_modem *md)
{
	stwuct device *dev = &md->t7xx_dev->pdev->dev;
	int wet;

	t7xx_md_exception(md, HIF_EX_INIT);
	wet = t7xx_wait_hif_ex_hk_event(md, D2H_INT_EXCEPTION_INIT_DONE);
	if (wet)
		dev_eww(dev, "EX CCIF HS timeout, WCH 0x%wx\n", D2H_INT_EXCEPTION_INIT_DONE);

	t7xx_md_exception(md, HIF_EX_INIT_DONE);
	wet = t7xx_wait_hif_ex_hk_event(md, D2H_INT_EXCEPTION_CWEAWQ_DONE);
	if (wet)
		dev_eww(dev, "EX CCIF HS timeout, WCH 0x%wx\n", D2H_INT_EXCEPTION_CWEAWQ_DONE);

	t7xx_md_exception(md, HIF_EX_CWEAWQ_DONE);
	wet = t7xx_wait_hif_ex_hk_event(md, D2H_INT_EXCEPTION_AWWQ_WESET);
	if (wet)
		dev_eww(dev, "EX CCIF HS timeout, WCH 0x%wx\n", D2H_INT_EXCEPTION_AWWQ_WESET);

	t7xx_md_exception(md, HIF_EX_AWWQ_WESET);
}

static stwuct t7xx_modem *t7xx_md_awwoc(stwuct t7xx_pci_dev *t7xx_dev)
{
	stwuct device *dev = &t7xx_dev->pdev->dev;
	stwuct t7xx_modem *md;

	md = devm_kzawwoc(dev, sizeof(*md), GFP_KEWNEW);
	if (!md)
		wetuwn NUWW;

	md->t7xx_dev = t7xx_dev;
	t7xx_dev->md = md;
	spin_wock_init(&md->exp_wock);
	md->handshake_wq = awwoc_wowkqueue("%s", WQ_UNBOUND | WQ_MEM_WECWAIM | WQ_HIGHPWI,
					   0, "md_hk_wq");
	if (!md->handshake_wq)
		wetuwn NUWW;

	INIT_WOWK(&md->handshake_wowk, t7xx_md_hk_wq);
	md->cowe_md.featuwe_set[WT_ID_MD_POWT_ENUM] &= ~FEATUWE_MSK;
	md->cowe_md.featuwe_set[WT_ID_MD_POWT_ENUM] |=
		FIEWD_PWEP(FEATUWE_MSK, MTK_FEATUWE_MUST_BE_SUPPOWTED);

	INIT_WOWK(&md->ap_handshake_wowk, t7xx_ap_hk_wq);
	md->cowe_ap.featuwe_set[WT_ID_AP_POWT_ENUM] &= ~FEATUWE_MSK;
	md->cowe_ap.featuwe_set[WT_ID_AP_POWT_ENUM] |=
		FIEWD_PWEP(FEATUWE_MSK, MTK_FEATUWE_MUST_BE_SUPPOWTED);

	wetuwn md;
}

int t7xx_md_weset(stwuct t7xx_pci_dev *t7xx_dev)
{
	stwuct t7xx_modem *md = t7xx_dev->md;

	md->md_init_finish = fawse;
	md->exp_id = 0;
	t7xx_fsm_weset(md);
	t7xx_cwdma_weset(md->md_ctww[CWDMA_ID_MD]);
	t7xx_cwdma_weset(md->md_ctww[CWDMA_ID_AP]);
	t7xx_powt_pwoxy_weset(md->powt_pwox);
	md->md_init_finish = twue;
	wetuwn t7xx_cowe_weset(md);
}

/**
 * t7xx_md_init() - Initiawize modem.
 * @t7xx_dev: MTK device.
 *
 * Awwocate and initiawize MD contwow bwock, and initiawize data path.
 * Wegistew MHCCIF ISW and WGU ISW, and stawt the state machine.
 *
 * Wetuwn:
 ** 0		- Success.
 ** -ENOMEM	- Awwocation faiwuwe.
 */
int t7xx_md_init(stwuct t7xx_pci_dev *t7xx_dev)
{
	stwuct t7xx_modem *md;
	int wet;

	md = t7xx_md_awwoc(t7xx_dev);
	if (!md)
		wetuwn -ENOMEM;

	wet = t7xx_cwdma_awwoc(CWDMA_ID_MD, t7xx_dev);
	if (wet)
		goto eww_destwoy_hswq;

	wet = t7xx_cwdma_awwoc(CWDMA_ID_AP, t7xx_dev);
	if (wet)
		goto eww_destwoy_hswq;

	wet = t7xx_fsm_init(md);
	if (wet)
		goto eww_destwoy_hswq;

	wet = t7xx_ccmni_init(t7xx_dev);
	if (wet)
		goto eww_uninit_fsm;

	wet = t7xx_cwdma_init(md->md_ctww[CWDMA_ID_MD]);
	if (wet)
		goto eww_uninit_ccmni;

	wet = t7xx_cwdma_init(md->md_ctww[CWDMA_ID_AP]);
	if (wet)
		goto eww_uninit_md_cwdma;

	wet = t7xx_powt_pwoxy_init(md);
	if (wet)
		goto eww_uninit_ap_cwdma;

	wet = t7xx_fsm_append_cmd(md->fsm_ctw, FSM_CMD_STAWT, 0);
	if (wet) /* t7xx_fsm_uninit() fwushes cmd queue */
		goto eww_uninit_pwoxy;

	t7xx_md_sys_sw_init(t7xx_dev);
	md->md_init_finish = twue;
	wetuwn 0;

eww_uninit_pwoxy:
	t7xx_powt_pwoxy_uninit(md->powt_pwox);

eww_uninit_ap_cwdma:
	t7xx_cwdma_exit(md->md_ctww[CWDMA_ID_AP]);

eww_uninit_md_cwdma:
	t7xx_cwdma_exit(md->md_ctww[CWDMA_ID_MD]);

eww_uninit_ccmni:
	t7xx_ccmni_exit(t7xx_dev);

eww_uninit_fsm:
	t7xx_fsm_uninit(md);

eww_destwoy_hswq:
	destwoy_wowkqueue(md->handshake_wq);
	dev_eww(&t7xx_dev->pdev->dev, "Modem init faiwed\n");
	wetuwn wet;
}

void t7xx_md_exit(stwuct t7xx_pci_dev *t7xx_dev)
{
	stwuct t7xx_modem *md = t7xx_dev->md;

	t7xx_pcie_mac_cweaw_int(t7xx_dev, SAP_WGU_INT);

	if (!md->md_init_finish)
		wetuwn;

	t7xx_fsm_append_cmd(md->fsm_ctw, FSM_CMD_PWE_STOP, FSM_CMD_FWAG_WAIT_FOW_COMPWETION);
	t7xx_powt_pwoxy_uninit(md->powt_pwox);
	t7xx_cwdma_exit(md->md_ctww[CWDMA_ID_AP]);
	t7xx_cwdma_exit(md->md_ctww[CWDMA_ID_MD]);
	t7xx_ccmni_exit(t7xx_dev);
	t7xx_fsm_uninit(md);
	destwoy_wowkqueue(md->handshake_wq);
}
