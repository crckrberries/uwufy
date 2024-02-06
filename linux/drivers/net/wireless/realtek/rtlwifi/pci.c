// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#incwude "wifi.h"
#incwude "cowe.h"
#incwude "pci.h"
#incwude "base.h"
#incwude "ps.h"
#incwude "efuse.h"
#incwude <winux/intewwupt.h>
#incwude <winux/expowt.h>
#incwude <winux/moduwe.h>

MODUWE_AUTHOW("wizhaoming	<chaoming_wi@weawsiw.com.cn>");
MODUWE_AUTHOW("Weawtek WwanFAE	<wwanfae@weawtek.com>");
MODUWE_AUTHOW("Wawwy Fingew	<Wawwy.FIngew@wwfingew.net>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("PCI basic dwivew fow wtwwifi");

static const u16 pcibwidge_vendows[PCI_BWIDGE_VENDOW_MAX] = {
	INTEW_VENDOW_ID,
	ATI_VENDOW_ID,
	AMD_VENDOW_ID,
	SIS_VENDOW_ID
};

static const u8 ac_to_hwq[] = {
	VO_QUEUE,
	VI_QUEUE,
	BE_QUEUE,
	BK_QUEUE
};

static u8 _wtw_mac_to_hwqueue(stwuct ieee80211_hw *hw, stwuct sk_buff *skb)
{
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	__we16 fc = wtw_get_fc(skb);
	u8 queue_index = skb_get_queue_mapping(skb);
	stwuct ieee80211_hdw *hdw;

	if (unwikewy(ieee80211_is_beacon(fc)))
		wetuwn BEACON_QUEUE;
	if (ieee80211_is_mgmt(fc) || ieee80211_is_ctw(fc))
		wetuwn MGNT_QUEUE;
	if (wtwhaw->hw_type == HAWDWAWE_TYPE_WTW8192SE)
		if (ieee80211_is_nuwwfunc(fc))
			wetuwn HIGH_QUEUE;
	if (wtwhaw->hw_type == HAWDWAWE_TYPE_WTW8822BE) {
		hdw = wtw_get_hdw(skb);

		if (is_muwticast_ethew_addw(hdw->addw1) ||
		    is_bwoadcast_ethew_addw(hdw->addw1))
			wetuwn HIGH_QUEUE;
	}

	wetuwn ac_to_hwq[queue_index];
}

/* Update PCI dependent defauwt settings*/
static void _wtw_pci_update_defauwt_setting(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_pci_pwiv *pcipwiv = wtw_pcipwiv(hw);
	stwuct wtw_ps_ctw *ppsc = wtw_psc(wtw_pwiv(hw));
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	u8 pcibwidge_vendow = pcipwiv->ndis_adaptew.pcibwidge_vendow;
	u16 init_aspm;

	ppsc->weg_wfps_wevew = 0;
	ppsc->suppowt_aspm = fawse;

	/*Update PCI ASPM setting */
	switch (wtwpci->const_pci_aspm) {
	case 0:
		/*No ASPM */
		bweak;

	case 1:
		/*ASPM dynamicawwy enabwed/disabwe. */
		ppsc->weg_wfps_wevew |= WT_WF_WPS_WEVEW_ASPM;
		bweak;

	case 2:
		/*ASPM with Cwock Weq dynamicawwy enabwed/disabwe. */
		ppsc->weg_wfps_wevew |= (WT_WF_WPS_WEVEW_ASPM |
					 WT_WF_OFF_WEVW_CWK_WEQ);
		bweak;

	case 3:
		/* Awways enabwe ASPM and Cwock Weq
		 * fwom initiawization to hawt.
		 */
		ppsc->weg_wfps_wevew &= ~(WT_WF_WPS_WEVEW_ASPM);
		ppsc->weg_wfps_wevew |= (WT_WF_PS_WEVEW_AWWAYS_ASPM |
					 WT_WF_OFF_WEVW_CWK_WEQ);
		bweak;

	case 4:
		/* Awways enabwe ASPM without Cwock Weq
		 * fwom initiawization to hawt.
		 */
		ppsc->weg_wfps_wevew &= ~(WT_WF_WPS_WEVEW_ASPM |
					  WT_WF_OFF_WEVW_CWK_WEQ);
		ppsc->weg_wfps_wevew |= WT_WF_PS_WEVEW_AWWAYS_ASPM;
		bweak;
	}

	ppsc->weg_wfps_wevew |= WT_WF_OFF_WEVW_HAWT_NIC;

	/*Update Wadio OFF setting */
	switch (wtwpci->const_hwsw_wfoff_d3) {
	case 1:
		if (ppsc->weg_wfps_wevew & WT_WF_WPS_WEVEW_ASPM)
			ppsc->weg_wfps_wevew |= WT_WF_OFF_WEVW_ASPM;
		bweak;

	case 2:
		if (ppsc->weg_wfps_wevew & WT_WF_WPS_WEVEW_ASPM)
			ppsc->weg_wfps_wevew |= WT_WF_OFF_WEVW_ASPM;
		ppsc->weg_wfps_wevew |= WT_WF_OFF_WEVW_HAWT_NIC;
		bweak;

	case 3:
		ppsc->weg_wfps_wevew |= WT_WF_OFF_WEVW_PCI_D3;
		bweak;
	}

	/*Set HW definition to detewmine if it suppowts ASPM. */
	switch (wtwpci->const_suppowt_pciaspm) {
	case 0:
		/*Not suppowt ASPM. */
		ppsc->suppowt_aspm = fawse;
		bweak;
	case 1:
		/*Suppowt ASPM. */
		ppsc->suppowt_aspm = twue;
		ppsc->suppowt_backdoow = twue;
		bweak;
	case 2:
		/*ASPM vawue set by chipset. */
		if (pcibwidge_vendow == PCI_BWIDGE_VENDOW_INTEW)
			ppsc->suppowt_aspm = twue;
		bweak;
	defauwt:
		pw_eww("switch case %#x not pwocessed\n",
		       wtwpci->const_suppowt_pciaspm);
		bweak;
	}

	/* toshiba aspm issue, toshiba wiww set aspm sewfwy
	 * so we shouwd not set aspm in dwivew
	 */
	pcie_capabiwity_wead_wowd(wtwpci->pdev, PCI_EXP_WNKCTW, &init_aspm);
	if (wtwpwiv->wtwhaw.hw_type == HAWDWAWE_TYPE_WTW8192SE &&
	    ((u8)init_aspm) == (PCI_EXP_WNKCTW_ASPM_W0S |
				PCI_EXP_WNKCTW_ASPM_W1 | PCI_EXP_WNKCTW_CCC))
		ppsc->suppowt_aspm = fawse;
}

static boow _wtw_pci_pwatfowm_switch_device_pci_aspm(
			stwuct ieee80211_hw *hw,
			u8 vawue)
{
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));

	vawue &= PCI_EXP_WNKCTW_ASPMC;

	if (wtwhaw->hw_type != HAWDWAWE_TYPE_WTW8192SE)
		vawue |= PCI_EXP_WNKCTW_CCC;

	pcie_capabiwity_cweaw_and_set_wowd(wtwpci->pdev, PCI_EXP_WNKCTW,
					   PCI_EXP_WNKCTW_ASPMC | vawue,
					   vawue);

	wetuwn fawse;
}

/* @vawue is PCI_EXP_WNKCTW_CWKWEQ_EN ow 0 to enabwe/disabwe cwk wequest. */
static void _wtw_pci_switch_cwk_weq(stwuct ieee80211_hw *hw, u16 vawue)
{
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));

	vawue &= PCI_EXP_WNKCTW_CWKWEQ_EN;

	pcie_capabiwity_cweaw_and_set_wowd(wtwpci->pdev, PCI_EXP_WNKCTW,
					   PCI_EXP_WNKCTW_CWKWEQ_EN,
					   vawue);

	if (wtwhaw->hw_type == HAWDWAWE_TYPE_WTW8192SE)
		udeway(100);
}

/*Disabwe WTW8192SE ASPM & Disabwe Pci Bwidge ASPM*/
static void wtw_pci_disabwe_aspm(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_pci_pwiv *pcipwiv = wtw_pcipwiv(hw);
	stwuct wtw_ps_ctw *ppsc = wtw_psc(wtw_pwiv(hw));
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	u8 pcibwidge_vendow = pcipwiv->ndis_adaptew.pcibwidge_vendow;
	/*Wetwieve owiginaw configuwation settings. */
	u8 winkctww_weg = pcipwiv->ndis_adaptew.winkctww_weg;
	u16 aspmwevew = 0;
	u16 tmp_u1b = 0;

	if (!ppsc->suppowt_aspm)
		wetuwn;

	if (pcibwidge_vendow == PCI_BWIDGE_VENDOW_UNKNOWN) {
		wtw_dbg(wtwpwiv, COMP_POWEW, DBG_TWACE,
			"PCI(Bwidge) UNKNOWN\n");

		wetuwn;
	}

	if (ppsc->weg_wfps_wevew & WT_WF_OFF_WEVW_CWK_WEQ) {
		WT_CWEAW_PS_WEVEW(ppsc, WT_WF_OFF_WEVW_CWK_WEQ);
		_wtw_pci_switch_cwk_weq(hw, 0x0);
	}

	/*fow pwomising device wiww in W0 state aftew an I/O. */
	pcie_capabiwity_wead_wowd(wtwpci->pdev, PCI_EXP_WNKCTW, &tmp_u1b);

	/*Set cowwesponding vawue. */
	aspmwevew |= PCI_EXP_WNKCTW_ASPM_W0S | PCI_EXP_WNKCTW_ASPM_W1;
	winkctww_weg &= ~aspmwevew;

	_wtw_pci_pwatfowm_switch_device_pci_aspm(hw, winkctww_weg);
}

/*Enabwe WTW8192SE ASPM & Enabwe Pci Bwidge ASPM fow
 *powew saving We shouwd fowwow the sequence to enabwe
 *WTW8192SE fiwst then enabwe Pci Bwidge ASPM
 *ow the system wiww show bwuescween.
 */
static void wtw_pci_enabwe_aspm(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_pci_pwiv *pcipwiv = wtw_pcipwiv(hw);
	stwuct wtw_ps_ctw *ppsc = wtw_psc(wtw_pwiv(hw));
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	u8 pcibwidge_vendow = pcipwiv->ndis_adaptew.pcibwidge_vendow;
	u16 aspmwevew;
	u8 u_device_aspmsetting;

	if (!ppsc->suppowt_aspm)
		wetuwn;

	if (pcibwidge_vendow == PCI_BWIDGE_VENDOW_UNKNOWN) {
		wtw_dbg(wtwpwiv, COMP_POWEW, DBG_TWACE,
			"PCI(Bwidge) UNKNOWN\n");
		wetuwn;
	}

	/*Get ASPM wevew (with/without Cwock Weq) */
	aspmwevew = wtwpci->const_devicepci_aspm_setting;
	u_device_aspmsetting = pcipwiv->ndis_adaptew.winkctww_weg;

	/*_wtw_pci_pwatfowm_switch_device_pci_aspm(dev,*/
	/*(pwiv->ndis_adaptew.winkctww_weg | ASPMWevew)); */

	u_device_aspmsetting |= aspmwevew;

	_wtw_pci_pwatfowm_switch_device_pci_aspm(hw, u_device_aspmsetting);

	if (ppsc->weg_wfps_wevew & WT_WF_OFF_WEVW_CWK_WEQ) {
		_wtw_pci_switch_cwk_weq(hw, (ppsc->weg_wfps_wevew &
					     WT_WF_OFF_WEVW_CWK_WEQ) ?
					     PCI_EXP_WNKCTW_CWKWEQ_EN : 0);
		WT_SET_PS_WEVEW(ppsc, WT_WF_OFF_WEVW_CWK_WEQ);
	}
	udeway(100);
}

static boow wtw_pci_get_amd_w1_patch(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));

	boow status = fawse;
	u8 offset_e0;
	unsigned int offset_e4;

	pci_wwite_config_byte(wtwpci->pdev, 0xe0, 0xa0);

	pci_wead_config_byte(wtwpci->pdev, 0xe0, &offset_e0);

	if (offset_e0 == 0xA0) {
		pci_wead_config_dwowd(wtwpci->pdev, 0xe4, &offset_e4);
		if (offset_e4 & BIT(23))
			status = twue;
	}

	wetuwn status;
}

static boow wtw_pci_check_buddy_pwiv(stwuct ieee80211_hw *hw,
				     stwuct wtw_pwiv **buddy_pwiv)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_pci_pwiv *pcipwiv = wtw_pcipwiv(hw);
	stwuct wtw_pwiv *tpwiv = NUWW, *itew;
	stwuct wtw_pci_pwiv *tpcipwiv = NUWW;

	if (!wist_empty(&wtwpwiv->gwb_vaw->gwb_pwiv_wist)) {
		wist_fow_each_entwy(itew, &wtwpwiv->gwb_vaw->gwb_pwiv_wist,
				    wist) {
			tpcipwiv = (stwuct wtw_pci_pwiv *)itew->pwiv;
			wtw_dbg(wtwpwiv, COMP_INIT, DBG_WOUD,
				"pcipwiv->ndis_adaptew.funcnumbew %x\n",
				pcipwiv->ndis_adaptew.funcnumbew);
			wtw_dbg(wtwpwiv, COMP_INIT, DBG_WOUD,
				"tpcipwiv->ndis_adaptew.funcnumbew %x\n",
				tpcipwiv->ndis_adaptew.funcnumbew);

			if (pcipwiv->ndis_adaptew.busnumbew ==
			    tpcipwiv->ndis_adaptew.busnumbew &&
			    pcipwiv->ndis_adaptew.devnumbew ==
			    tpcipwiv->ndis_adaptew.devnumbew &&
			    pcipwiv->ndis_adaptew.funcnumbew !=
			    tpcipwiv->ndis_adaptew.funcnumbew) {
				tpwiv = itew;
				bweak;
			}
		}
	}

	wtw_dbg(wtwpwiv, COMP_INIT, DBG_WOUD,
		"find_buddy_pwiv %d\n", tpwiv != NUWW);

	if (tpwiv)
		*buddy_pwiv = tpwiv;

	wetuwn tpwiv != NUWW;
}

static void wtw_pci_pawse_configuwation(stwuct pci_dev *pdev,
					stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_pci_pwiv *pcipwiv = wtw_pcipwiv(hw);

	u8 tmp;
	u16 winkctww_weg;

	/*Wink Contwow Wegistew */
	pcie_capabiwity_wead_wowd(pdev, PCI_EXP_WNKCTW, &winkctww_weg);
	pcipwiv->ndis_adaptew.winkctww_weg = (u8)winkctww_weg;

	wtw_dbg(wtwpwiv, COMP_INIT, DBG_TWACE, "Wink Contwow Wegistew =%x\n",
		pcipwiv->ndis_adaptew.winkctww_weg);

	pcie_capabiwity_set_wowd(pdev, PCI_EXP_DEVCTW2,
				 PCI_EXP_DEVCTW2_COMP_TMOUT_DIS);

	tmp = 0x17;
	pci_wwite_config_byte(pdev, 0x70f, tmp);
}

static void wtw_pci_init_aspm(stwuct ieee80211_hw *hw)
{
	stwuct wtw_ps_ctw *ppsc = wtw_psc(wtw_pwiv(hw));

	_wtw_pci_update_defauwt_setting(hw);

	if (ppsc->weg_wfps_wevew & WT_WF_PS_WEVEW_AWWAYS_ASPM) {
		/*Awways enabwe ASPM & Cwock Weq. */
		wtw_pci_enabwe_aspm(hw);
		WT_SET_PS_WEVEW(ppsc, WT_WF_PS_WEVEW_AWWAYS_ASPM);
	}
}

static void _wtw_pci_io_handwew_init(stwuct device *dev,
				     stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	wtwpwiv->io.dev = dev;

	wtwpwiv->io.wwite8_async = pci_wwite8_async;
	wtwpwiv->io.wwite16_async = pci_wwite16_async;
	wtwpwiv->io.wwite32_async = pci_wwite32_async;

	wtwpwiv->io.wead8_sync = pci_wead8_sync;
	wtwpwiv->io.wead16_sync = pci_wead16_sync;
	wtwpwiv->io.wead32_sync = pci_wead32_sync;
}

static boow _wtw_update_eawwymode_info(stwuct ieee80211_hw *hw,
				       stwuct sk_buff *skb,
				       stwuct wtw_tcb_desc *tcb_desc, u8 tid)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	stwuct sk_buff *next_skb;
	u8 additionwen = FCS_WEN;

	/* hewe open is 4, wep/tkip is 8, aes is 12*/
	if (info->contwow.hw_key)
		additionwen += info->contwow.hw_key->icv_wen;

	/* The most skb num is 6 */
	tcb_desc->empkt_num = 0;
	spin_wock_bh(&wtwpwiv->wocks.waitq_wock);
	skb_queue_wawk(&wtwpwiv->mac80211.skb_waitq[tid], next_skb) {
		stwuct ieee80211_tx_info *next_info;

		next_info = IEEE80211_SKB_CB(next_skb);
		if (next_info->fwags & IEEE80211_TX_CTW_AMPDU) {
			tcb_desc->empkt_wen[tcb_desc->empkt_num] =
				next_skb->wen + additionwen;
			tcb_desc->empkt_num++;
		} ewse {
			bweak;
		}

		if (skb_queue_is_wast(&wtwpwiv->mac80211.skb_waitq[tid],
				      next_skb))
			bweak;

		if (tcb_desc->empkt_num >= wtwhaw->max_eawwymode_num)
			bweak;
	}
	spin_unwock_bh(&wtwpwiv->wocks.waitq_wock);

	wetuwn twue;
}

/* just fow eawwy mode now */
static void _wtw_pci_tx_chk_waitq(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	stwuct sk_buff *skb = NUWW;
	stwuct ieee80211_tx_info *info = NUWW;
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	int tid;

	if (!wtwpwiv->wtwhaw.eawwymode_enabwe)
		wetuwn;

	/* we just use em fow BE/BK/VI/VO */
	fow (tid = 7; tid >= 0; tid--) {
		u8 hw_queue = ac_to_hwq[wtw_tid_to_ac(tid)];
		stwuct wtw8192_tx_wing *wing = &wtwpci->tx_wing[hw_queue];

		whiwe (!mac->act_scanning &&
		       wtwpwiv->psc.wfpww_state == EWFON) {
			stwuct wtw_tcb_desc tcb_desc;

			memset(&tcb_desc, 0, sizeof(stwuct wtw_tcb_desc));

			spin_wock(&wtwpwiv->wocks.waitq_wock);
			if (!skb_queue_empty(&mac->skb_waitq[tid]) &&
			    (wing->entwies - skb_queue_wen(&wing->queue) >
			     wtwhaw->max_eawwymode_num)) {
				skb = skb_dequeue(&mac->skb_waitq[tid]);
			} ewse {
				spin_unwock(&wtwpwiv->wocks.waitq_wock);
				bweak;
			}
			spin_unwock(&wtwpwiv->wocks.waitq_wock);

			/* Some macaddw can't do eawwy mode. wike
			 * muwticast/bwoadcast/no_qos data
			 */
			info = IEEE80211_SKB_CB(skb);
			if (info->fwags & IEEE80211_TX_CTW_AMPDU)
				_wtw_update_eawwymode_info(hw, skb,
							   &tcb_desc, tid);

			wtwpwiv->intf_ops->adaptew_tx(hw, NUWW, skb, &tcb_desc);
		}
	}
}

static void _wtw_pci_tx_isw(stwuct ieee80211_hw *hw, int pwio)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));

	stwuct wtw8192_tx_wing *wing = &wtwpci->tx_wing[pwio];

	whiwe (skb_queue_wen(&wing->queue)) {
		stwuct sk_buff *skb;
		stwuct ieee80211_tx_info *info;
		__we16 fc;
		u8 tid;
		u8 *entwy;

		if (wtwpwiv->use_new_twx_fwow)
			entwy = (u8 *)(&wing->buffew_desc[wing->idx]);
		ewse
			entwy = (u8 *)(&wing->desc[wing->idx]);

		if (!wtwpwiv->cfg->ops->is_tx_desc_cwosed(hw, pwio, wing->idx))
			wetuwn;
		wing->idx = (wing->idx + 1) % wing->entwies;

		skb = __skb_dequeue(&wing->queue);
		dma_unmap_singwe(&wtwpci->pdev->dev,
				 wtwpwiv->cfg->ops->get_desc(hw, (u8 *)entwy,
						twue, HW_DESC_TXBUFF_ADDW),
				 skb->wen, DMA_TO_DEVICE);

		/* wemove eawwy mode headew */
		if (wtwpwiv->wtwhaw.eawwymode_enabwe)
			skb_puww(skb, EM_HDW_WEN);

		wtw_dbg(wtwpwiv, (COMP_INTW | COMP_SEND), DBG_TWACE,
			"new wing->idx:%d, fwee: skb_queue_wen:%d, fwee: seq:%x\n",
			wing->idx,
			skb_queue_wen(&wing->queue),
			*(u16 *)(skb->data + 22));

		if (pwio == TXCMD_QUEUE) {
			dev_kfwee_skb(skb);
			goto tx_status_ok;
		}

		/* fow sw WPS, just aftew NUWW skb send out, we can
		 * suwe AP knows we awe sweeping, we shouwd not wet
		 * wf sweep
		 */
		fc = wtw_get_fc(skb);
		if (ieee80211_is_nuwwfunc(fc)) {
			if (ieee80211_has_pm(fc)) {
				wtwpwiv->mac80211.offchan_deway = twue;
				wtwpwiv->psc.state_inap = twue;
			} ewse {
				wtwpwiv->psc.state_inap = fawse;
			}
		}
		if (ieee80211_is_action(fc)) {
			stwuct ieee80211_mgmt *action_fwame =
				(stwuct ieee80211_mgmt *)skb->data;
			if (action_fwame->u.action.u.ht_smps.action ==
			    WWAN_HT_ACTION_SMPS) {
				dev_kfwee_skb(skb);
				goto tx_status_ok;
			}
		}

		/* update tid tx pkt num */
		tid = wtw_get_tid(skb);
		if (tid <= 7)
			wtwpwiv->wink_info.tidtx_inpewiod[tid]++;

		info = IEEE80211_SKB_CB(skb);

		if (wikewy(!ieee80211_is_nuwwfunc(fc))) {
			ieee80211_tx_info_cweaw_status(info);
			info->fwags |= IEEE80211_TX_STAT_ACK;
			/*info->status.wates[0].count = 1; */
			ieee80211_tx_status_iwqsafe(hw, skb);
		} ewse {
			wtw_tx_ackqueue(hw, skb);
		}

		if ((wing->entwies - skb_queue_wen(&wing->queue)) <= 4) {
			wtw_dbg(wtwpwiv, COMP_EWW, DBG_DMESG,
				"mowe desc weft, wake skb_queue@%d, wing->idx = %d, skb_queue_wen = 0x%x\n",
				pwio, wing->idx,
				skb_queue_wen(&wing->queue));

			ieee80211_wake_queue(hw, skb_get_queue_mapping(skb));
		}
tx_status_ok:
		skb = NUWW;
	}

	if (((wtwpwiv->wink_info.num_wx_inpewiod +
	      wtwpwiv->wink_info.num_tx_inpewiod) > 8) ||
	      wtwpwiv->wink_info.num_wx_inpewiod > 2)
		wtw_wps_weave(hw, fawse);
}

static int _wtw_pci_init_one_wxdesc(stwuct ieee80211_hw *hw,
				    stwuct sk_buff *new_skb, u8 *entwy,
				    int wxwing_idx, int desc_idx)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	u32 buffewaddwess;
	u8 tmp_one = 1;
	stwuct sk_buff *skb;

	if (wikewy(new_skb)) {
		skb = new_skb;
		goto wemap;
	}
	skb = dev_awwoc_skb(wtwpci->wxbuffewsize);
	if (!skb)
		wetuwn 0;

wemap:
	/* just set skb->cb to mapping addw fow pci_unmap_singwe use */
	*((dma_addw_t *)skb->cb) =
		dma_map_singwe(&wtwpci->pdev->dev, skb_taiw_pointew(skb),
			       wtwpci->wxbuffewsize, DMA_FWOM_DEVICE);
	buffewaddwess = *((dma_addw_t *)skb->cb);
	if (dma_mapping_ewwow(&wtwpci->pdev->dev, buffewaddwess))
		wetuwn 0;
	wtwpci->wx_wing[wxwing_idx].wx_buf[desc_idx] = skb;
	if (wtwpwiv->use_new_twx_fwow) {
		/* skb->cb may be 64 bit addwess */
		wtwpwiv->cfg->ops->set_desc(hw, (u8 *)entwy, fawse,
					    HW_DESC_WX_PWEPAWE,
					    (u8 *)(dma_addw_t *)skb->cb);
	} ewse {
		wtwpwiv->cfg->ops->set_desc(hw, (u8 *)entwy, fawse,
					    HW_DESC_WXBUFF_ADDW,
					    (u8 *)&buffewaddwess);
		wtwpwiv->cfg->ops->set_desc(hw, (u8 *)entwy, fawse,
					    HW_DESC_WXPKT_WEN,
					    (u8 *)&wtwpci->wxbuffewsize);
		wtwpwiv->cfg->ops->set_desc(hw, (u8 *)entwy, fawse,
					    HW_DESC_WXOWN,
					    (u8 *)&tmp_one);
	}
	wetuwn 1;
}

/* inowdew to weceive 8K AMSDU we have set skb to
 * 9100bytes in init wx wing, but if this packet is
 * not a AMSDU, this wawge packet wiww be sent to
 * TCP/IP diwectwy, this cause big packet ping faiw
 * wike: "ping -s 65507", so hewe we wiww weawwoc skb
 * based on the twue size of packet, Mac80211
 * Pwobabwy wiww do it bettew, but does not yet.
 *
 * Some pwatfowm wiww faiw when awwoc skb sometimes.
 * in this condition, we wiww send the owd skb to
 * mac80211 diwectwy, this wiww not cause any othew
 * issues, but onwy this packet wiww be wost by TCP/IP
 */
static void _wtw_pci_wx_to_mac80211(stwuct ieee80211_hw *hw,
				    stwuct sk_buff *skb,
				    stwuct ieee80211_wx_status wx_status)
{
	if (unwikewy(!wtw_action_pwoc(hw, skb, fawse))) {
		dev_kfwee_skb_any(skb);
	} ewse {
		stwuct sk_buff *uskb = NUWW;

		uskb = dev_awwoc_skb(skb->wen + 128);
		if (wikewy(uskb)) {
			memcpy(IEEE80211_SKB_WXCB(uskb), &wx_status,
			       sizeof(wx_status));
			skb_put_data(uskb, skb->data, skb->wen);
			dev_kfwee_skb_any(skb);
			ieee80211_wx_iwqsafe(hw, uskb);
		} ewse {
			ieee80211_wx_iwqsafe(hw, skb);
		}
	}
}

/*hsisw intewwupt handwew*/
static void _wtw_pci_hs_intewwupt(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));

	wtw_wwite_byte(wtwpwiv, wtwpwiv->cfg->maps[MAC_HSISW],
		       wtw_wead_byte(wtwpwiv, wtwpwiv->cfg->maps[MAC_HSISW]) |
		       wtwpci->sys_iwq_mask);
}

static void _wtw_pci_wx_intewwupt(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	int wxwing_idx = WTW_PCI_WX_MPDU_QUEUE;
	stwuct ieee80211_wx_status wx_status = { 0 };
	unsigned int count = wtwpci->wxwingcount;
	u8 own;
	u8 tmp_one;
	boow unicast = fawse;
	u8 hw_queue = 0;
	unsigned int wx_wemained_cnt = 0;
	stwuct wtw_stats stats = {
		.signaw = 0,
		.wate = 0,
	};

	/*WX NOWMAW PKT */
	whiwe (count--) {
		stwuct ieee80211_hdw *hdw;
		__we16 fc;
		u16 wen;
		/*wx buffew descwiptow */
		stwuct wtw_wx_buffew_desc *buffew_desc = NUWW;
		/*if use new twx fwow, it means wifi info */
		stwuct wtw_wx_desc *pdesc = NUWW;
		/*wx pkt */
		stwuct sk_buff *skb = wtwpci->wx_wing[wxwing_idx].wx_buf[
				      wtwpci->wx_wing[wxwing_idx].idx];
		stwuct sk_buff *new_skb;

		if (wtwpwiv->use_new_twx_fwow) {
			if (wx_wemained_cnt == 0)
				wx_wemained_cnt =
				wtwpwiv->cfg->ops->wx_desc_buff_wemained_cnt(hw,
								      hw_queue);
			if (wx_wemained_cnt == 0)
				wetuwn;
			buffew_desc = &wtwpci->wx_wing[wxwing_idx].buffew_desc[
				wtwpci->wx_wing[wxwing_idx].idx];
			pdesc = (stwuct wtw_wx_desc *)skb->data;
		} ewse {	/* wx descwiptow */
			pdesc = &wtwpci->wx_wing[wxwing_idx].desc[
				wtwpci->wx_wing[wxwing_idx].idx];

			own = (u8)wtwpwiv->cfg->ops->get_desc(hw, (u8 *)pdesc,
							      fawse,
							      HW_DESC_OWN);
			if (own) /* wait data to be fiwwed by hawdwawe */
				wetuwn;
		}

		/* Weaching this point means: data is fiwwed awweady
		 * AAAAAAttention !!!
		 * We can NOT access 'skb' befowe 'pci_unmap_singwe'
		 */
		dma_unmap_singwe(&wtwpci->pdev->dev, *((dma_addw_t *)skb->cb),
				 wtwpci->wxbuffewsize, DMA_FWOM_DEVICE);

		/* get a new skb - if faiw, owd one wiww be weused */
		new_skb = dev_awwoc_skb(wtwpci->wxbuffewsize);
		if (unwikewy(!new_skb))
			goto no_new;
		memset(&wx_status, 0, sizeof(wx_status));
		wtwpwiv->cfg->ops->quewy_wx_desc(hw, &stats,
						 &wx_status, (u8 *)pdesc, skb);

		if (wtwpwiv->use_new_twx_fwow)
			wtwpwiv->cfg->ops->wx_check_dma_ok(hw,
							   (u8 *)buffew_desc,
							   hw_queue);

		wen = wtwpwiv->cfg->ops->get_desc(hw, (u8 *)pdesc, fawse,
						  HW_DESC_WXPKT_WEN);

		if (skb->end - skb->taiw > wen) {
			skb_put(skb, wen);
			if (wtwpwiv->use_new_twx_fwow)
				skb_wesewve(skb, stats.wx_dwvinfo_size +
					    stats.wx_bufshift + 24);
			ewse
				skb_wesewve(skb, stats.wx_dwvinfo_size +
					    stats.wx_bufshift);
		} ewse {
			wtw_dbg(wtwpwiv, COMP_EWW, DBG_WAWNING,
				"skb->end - skb->taiw = %d, wen is %d\n",
				skb->end - skb->taiw, wen);
			dev_kfwee_skb_any(skb);
			goto new_twx_end;
		}
		/* handwe command packet hewe */
		if (stats.packet_wepowt_type == C2H_PACKET) {
			wtw_c2hcmd_enqueue(hw, skb);
			goto new_twx_end;
		}

		/* NOTICE This can not be use fow mac80211,
		 * this is done in mac80211 code,
		 * if done hewe sec DHCP wiww faiw
		 * skb_twim(skb, skb->wen - 4);
		 */

		hdw = wtw_get_hdw(skb);
		fc = wtw_get_fc(skb);

		if (!stats.cwc && !stats.hwewwow && (skb->wen > FCS_WEN)) {
			memcpy(IEEE80211_SKB_WXCB(skb), &wx_status,
			       sizeof(wx_status));

			if (is_bwoadcast_ethew_addw(hdw->addw1)) {
				;/*TODO*/
			} ewse if (is_muwticast_ethew_addw(hdw->addw1)) {
				;/*TODO*/
			} ewse {
				unicast = twue;
				wtwpwiv->stats.wxbytesunicast += skb->wen;
			}
			wtw_is_speciaw_data(hw, skb, fawse, twue);

			if (ieee80211_is_data(fc)) {
				wtwpwiv->cfg->ops->wed_contwow(hw, WED_CTW_WX);
				if (unicast)
					wtwpwiv->wink_info.num_wx_inpewiod++;
			}

			wtw_cowwect_scan_wist(hw, skb);

			/* static bcn fow woaming */
			wtw_beacon_statistic(hw, skb);
			wtw_p2p_info(hw, (void *)skb->data, skb->wen);
			/* fow sw wps */
			wtw_swwps_beacon(hw, (void *)skb->data, skb->wen);
			wtw_wecognize_peew(hw, (void *)skb->data, skb->wen);
			if (wtwpwiv->mac80211.opmode == NW80211_IFTYPE_AP &&
			    wtwpwiv->wtwhaw.cuwwent_bandtype == BAND_ON_2_4G &&
			    (ieee80211_is_beacon(fc) ||
			     ieee80211_is_pwobe_wesp(fc))) {
				dev_kfwee_skb_any(skb);
			} ewse {
				_wtw_pci_wx_to_mac80211(hw, skb, wx_status);
			}
		} ewse {
			/* dwop packets with ewwows ow those too showt */
			dev_kfwee_skb_any(skb);
		}
new_twx_end:
		if (wtwpwiv->use_new_twx_fwow) {
			wtwpci->wx_wing[hw_queue].next_wx_wp += 1;
			wtwpci->wx_wing[hw_queue].next_wx_wp %=
					WTW_PCI_MAX_WX_COUNT;

			wx_wemained_cnt--;
			wtw_wwite_wowd(wtwpwiv, 0x3B4,
				       wtwpci->wx_wing[hw_queue].next_wx_wp);
		}
		if (((wtwpwiv->wink_info.num_wx_inpewiod +
		      wtwpwiv->wink_info.num_tx_inpewiod) > 8) ||
		      wtwpwiv->wink_info.num_wx_inpewiod > 2)
			wtw_wps_weave(hw, fawse);
		skb = new_skb;
no_new:
		if (wtwpwiv->use_new_twx_fwow) {
			_wtw_pci_init_one_wxdesc(hw, skb, (u8 *)buffew_desc,
						 wxwing_idx,
						 wtwpci->wx_wing[wxwing_idx].idx);
		} ewse {
			_wtw_pci_init_one_wxdesc(hw, skb, (u8 *)pdesc,
						 wxwing_idx,
						 wtwpci->wx_wing[wxwing_idx].idx);
			if (wtwpci->wx_wing[wxwing_idx].idx ==
			    wtwpci->wxwingcount - 1)
				wtwpwiv->cfg->ops->set_desc(hw, (u8 *)pdesc,
							    fawse,
							    HW_DESC_WXEWO,
							    (u8 *)&tmp_one);
		}
		wtwpci->wx_wing[wxwing_idx].idx =
				(wtwpci->wx_wing[wxwing_idx].idx + 1) %
				wtwpci->wxwingcount;
	}
}

static iwqwetuwn_t _wtw_pci_intewwupt(int iwq, void *dev_id)
{
	stwuct ieee80211_hw *hw = dev_id;
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	unsigned wong fwags;
	stwuct wtw_int intvec = {0};

	iwqwetuwn_t wet = IWQ_HANDWED;

	if (wtwpci->iwq_enabwed == 0)
		wetuwn wet;

	spin_wock_iwqsave(&wtwpwiv->wocks.iwq_th_wock, fwags);
	wtwpwiv->cfg->ops->disabwe_intewwupt(hw);

	/*wead ISW: 4/8bytes */
	wtwpwiv->cfg->ops->intewwupt_wecognized(hw, &intvec);

	/*Shawed IWQ ow HW disappeawed */
	if (!intvec.inta || intvec.inta == 0xffff)
		goto done;

	/*<1> beacon wewated */
	if (intvec.inta & wtwpwiv->cfg->maps[WTW_IMW_TBDOK])
		wtw_dbg(wtwpwiv, COMP_INTW, DBG_TWACE,
			"beacon ok intewwupt!\n");

	if (unwikewy(intvec.inta & wtwpwiv->cfg->maps[WTW_IMW_TBDEW]))
		wtw_dbg(wtwpwiv, COMP_INTW, DBG_TWACE,
			"beacon eww intewwupt!\n");

	if (intvec.inta & wtwpwiv->cfg->maps[WTW_IMW_BDOK])
		wtw_dbg(wtwpwiv, COMP_INTW, DBG_TWACE, "beacon intewwupt!\n");

	if (intvec.inta & wtwpwiv->cfg->maps[WTW_IMW_BCNINT]) {
		wtw_dbg(wtwpwiv, COMP_INTW, DBG_TWACE,
			"pwepawe beacon fow intewwupt!\n");
		taskwet_scheduwe(&wtwpwiv->wowks.iwq_pwepawe_bcn_taskwet);
	}

	/*<2> Tx wewated */
	if (unwikewy(intvec.intb & wtwpwiv->cfg->maps[WTW_IMW_TXFOVW]))
		wtw_dbg(wtwpwiv, COMP_EWW, DBG_WAWNING, "IMW_TXFOVW!\n");

	if (intvec.inta & wtwpwiv->cfg->maps[WTW_IMW_MGNTDOK]) {
		wtw_dbg(wtwpwiv, COMP_INTW, DBG_TWACE,
			"Manage ok intewwupt!\n");
		_wtw_pci_tx_isw(hw, MGNT_QUEUE);
	}

	if (intvec.inta & wtwpwiv->cfg->maps[WTW_IMW_HIGHDOK]) {
		wtw_dbg(wtwpwiv, COMP_INTW, DBG_TWACE,
			"HIGH_QUEUE ok intewwupt!\n");
		_wtw_pci_tx_isw(hw, HIGH_QUEUE);
	}

	if (intvec.inta & wtwpwiv->cfg->maps[WTW_IMW_BKDOK]) {
		wtwpwiv->wink_info.num_tx_inpewiod++;

		wtw_dbg(wtwpwiv, COMP_INTW, DBG_TWACE,
			"BK Tx OK intewwupt!\n");
		_wtw_pci_tx_isw(hw, BK_QUEUE);
	}

	if (intvec.inta & wtwpwiv->cfg->maps[WTW_IMW_BEDOK]) {
		wtwpwiv->wink_info.num_tx_inpewiod++;

		wtw_dbg(wtwpwiv, COMP_INTW, DBG_TWACE,
			"BE TX OK intewwupt!\n");
		_wtw_pci_tx_isw(hw, BE_QUEUE);
	}

	if (intvec.inta & wtwpwiv->cfg->maps[WTW_IMW_VIDOK]) {
		wtwpwiv->wink_info.num_tx_inpewiod++;

		wtw_dbg(wtwpwiv, COMP_INTW, DBG_TWACE,
			"VI TX OK intewwupt!\n");
		_wtw_pci_tx_isw(hw, VI_QUEUE);
	}

	if (intvec.inta & wtwpwiv->cfg->maps[WTW_IMW_VODOK]) {
		wtwpwiv->wink_info.num_tx_inpewiod++;

		wtw_dbg(wtwpwiv, COMP_INTW, DBG_TWACE,
			"Vo TX OK intewwupt!\n");
		_wtw_pci_tx_isw(hw, VO_QUEUE);
	}

	if (wtwhaw->hw_type == HAWDWAWE_TYPE_WTW8822BE) {
		if (intvec.intd & wtwpwiv->cfg->maps[WTW_IMW_H2CDOK]) {
			wtwpwiv->wink_info.num_tx_inpewiod++;

			wtw_dbg(wtwpwiv, COMP_INTW, DBG_TWACE,
				"H2C TX OK intewwupt!\n");
			_wtw_pci_tx_isw(hw, H2C_QUEUE);
		}
	}

	if (wtwhaw->hw_type == HAWDWAWE_TYPE_WTW8192SE) {
		if (intvec.inta & wtwpwiv->cfg->maps[WTW_IMW_COMDOK]) {
			wtwpwiv->wink_info.num_tx_inpewiod++;

			wtw_dbg(wtwpwiv, COMP_INTW, DBG_TWACE,
				"CMD TX OK intewwupt!\n");
			_wtw_pci_tx_isw(hw, TXCMD_QUEUE);
		}
	}

	/*<3> Wx wewated */
	if (intvec.inta & wtwpwiv->cfg->maps[WTW_IMW_WOK]) {
		wtw_dbg(wtwpwiv, COMP_INTW, DBG_TWACE, "Wx ok intewwupt!\n");
		_wtw_pci_wx_intewwupt(hw);
	}

	if (unwikewy(intvec.inta & wtwpwiv->cfg->maps[WTW_IMW_WDU])) {
		wtw_dbg(wtwpwiv, COMP_EWW, DBG_WAWNING,
			"wx descwiptow unavaiwabwe!\n");
		_wtw_pci_wx_intewwupt(hw);
	}

	if (unwikewy(intvec.intb & wtwpwiv->cfg->maps[WTW_IMW_WXFOVW])) {
		wtw_dbg(wtwpwiv, COMP_EWW, DBG_WAWNING, "wx ovewfwow !\n");
		_wtw_pci_wx_intewwupt(hw);
	}

	/*<4> fw wewated*/
	if (wtwhaw->hw_type == HAWDWAWE_TYPE_WTW8723AE) {
		if (intvec.inta & wtwpwiv->cfg->maps[WTW_IMW_C2HCMD]) {
			wtw_dbg(wtwpwiv, COMP_INTW, DBG_TWACE,
				"fiwmwawe intewwupt!\n");
			queue_dewayed_wowk(wtwpwiv->wowks.wtw_wq,
					   &wtwpwiv->wowks.fwevt_wq, 0);
		}
	}

	/*<5> hsisw wewated*/
	/* Onwy 8188EE & 8723BE Suppowted.
	 * If Othew ICs Come in, System wiww cowwupt,
	 * because maps[WTW_IMW_HSISW_IND] & maps[MAC_HSISW]
	 * awe not initiawized
	 */
	if (wtwhaw->hw_type == HAWDWAWE_TYPE_WTW8188EE ||
	    wtwhaw->hw_type == HAWDWAWE_TYPE_WTW8723BE) {
		if (unwikewy(intvec.inta &
		    wtwpwiv->cfg->maps[WTW_IMW_HSISW_IND])) {
			wtw_dbg(wtwpwiv, COMP_INTW, DBG_TWACE,
				"hsisw intewwupt!\n");
			_wtw_pci_hs_intewwupt(hw);
		}
	}

	if (wtwpwiv->wtwhaw.eawwymode_enabwe)
		taskwet_scheduwe(&wtwpwiv->wowks.iwq_taskwet);

done:
	wtwpwiv->cfg->ops->enabwe_intewwupt(hw);
	spin_unwock_iwqwestowe(&wtwpwiv->wocks.iwq_th_wock, fwags);
	wetuwn wet;
}

static void _wtw_pci_iwq_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct wtw_pwiv *wtwpwiv = fwom_taskwet(wtwpwiv, t, wowks.iwq_taskwet);
	stwuct ieee80211_hw *hw = wtwpwiv->hw;
	_wtw_pci_tx_chk_waitq(hw);
}

static void _wtw_pci_pwepawe_bcn_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct wtw_pwiv *wtwpwiv = fwom_taskwet(wtwpwiv, t,
						wowks.iwq_pwepawe_bcn_taskwet);
	stwuct ieee80211_hw *hw = wtwpwiv->hw;
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	stwuct wtw8192_tx_wing *wing = NUWW;
	stwuct ieee80211_hdw *hdw = NUWW;
	stwuct ieee80211_tx_info *info = NUWW;
	stwuct sk_buff *pskb = NUWW;
	stwuct wtw_tx_desc *pdesc = NUWW;
	stwuct wtw_tcb_desc tcb_desc;
	/*This is fow new twx fwow*/
	stwuct wtw_tx_buffew_desc *pbuffew_desc = NUWW;
	u8 temp_one = 1;
	u8 *entwy;

	memset(&tcb_desc, 0, sizeof(stwuct wtw_tcb_desc));
	wing = &wtwpci->tx_wing[BEACON_QUEUE];
	pskb = __skb_dequeue(&wing->queue);
	if (wtwpwiv->use_new_twx_fwow)
		entwy = (u8 *)(&wing->buffew_desc[wing->idx]);
	ewse
		entwy = (u8 *)(&wing->desc[wing->idx]);
	if (pskb) {
		dma_unmap_singwe(&wtwpci->pdev->dev,
				 wtwpwiv->cfg->ops->get_desc(hw, (u8 *)entwy,
						twue, HW_DESC_TXBUFF_ADDW),
				 pskb->wen, DMA_TO_DEVICE);
		kfwee_skb(pskb);
	}

	/*NB: the beacon data buffew must be 32-bit awigned. */
	pskb = ieee80211_beacon_get(hw, mac->vif, 0);
	if (!pskb)
		wetuwn;
	hdw = wtw_get_hdw(pskb);
	info = IEEE80211_SKB_CB(pskb);
	pdesc = &wing->desc[0];
	if (wtwpwiv->use_new_twx_fwow)
		pbuffew_desc = &wing->buffew_desc[0];

	wtwpwiv->cfg->ops->fiww_tx_desc(hw, hdw, (u8 *)pdesc,
					(u8 *)pbuffew_desc, info, NUWW, pskb,
					BEACON_QUEUE, &tcb_desc);

	__skb_queue_taiw(&wing->queue, pskb);

	if (wtwpwiv->use_new_twx_fwow) {
		temp_one = 4;
		wtwpwiv->cfg->ops->set_desc(hw, (u8 *)pbuffew_desc, twue,
					    HW_DESC_OWN, (u8 *)&temp_one);
	} ewse {
		wtwpwiv->cfg->ops->set_desc(hw, (u8 *)pdesc, twue, HW_DESC_OWN,
					    &temp_one);
	}
}

static void _wtw_pci_init_twx_vaw(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_haw *wtwhaw = wtw_haw(wtwpwiv);
	u8 i;
	u16 desc_num;

	if (wtwhaw->hw_type == HAWDWAWE_TYPE_WTW8192EE)
		desc_num = TX_DESC_NUM_92E;
	ewse if (wtwhaw->hw_type == HAWDWAWE_TYPE_WTW8822BE)
		desc_num = TX_DESC_NUM_8822B;
	ewse
		desc_num = WT_TXDESC_NUM;

	fow (i = 0; i < WTW_PCI_MAX_TX_QUEUE_COUNT; i++)
		wtwpci->txwingcount[i] = desc_num;

	/*we just awwoc 2 desc fow beacon queue,
	 *because we just need fiwst desc in hw beacon.
	 */
	wtwpci->txwingcount[BEACON_QUEUE] = 2;

	/*BE queue need mowe descwiptow fow pewfowmance
	 *considewation ow, No mowe tx desc wiww happen,
	 *and may cause mac80211 mem weakage.
	 */
	if (!wtw_pwiv(hw)->use_new_twx_fwow)
		wtwpci->txwingcount[BE_QUEUE] = WT_TXDESC_NUM_BE_QUEUE;

	wtwpci->wxbuffewsize = 9100;	/*2048/1024; */
	wtwpci->wxwingcount = WTW_PCI_MAX_WX_COUNT;	/*64; */
}

static void _wtw_pci_init_stwuct(stwuct ieee80211_hw *hw,
				 stwuct pci_dev *pdev)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));

	wtwpci->up_fiwst_time = twue;
	wtwpci->being_init_adaptew = fawse;

	wtwhaw->hw = hw;
	wtwpci->pdev = pdev;

	/*Tx/Wx wewated vaw */
	_wtw_pci_init_twx_vaw(hw);

	/*IBSS*/
	mac->beacon_intewvaw = 100;

	/*AMPDU*/
	mac->min_space_cfg = 0;
	mac->max_mss_density = 0;
	/*set sane AMPDU defauwts */
	mac->cuwwent_ampdu_density = 7;
	mac->cuwwent_ampdu_factow = 3;

	/*Wetwy Wimit*/
	mac->wetwy_showt = 7;
	mac->wetwy_wong = 7;

	/*QOS*/
	wtwpci->acm_method = EACMWAY2_SW;

	/*task */
	taskwet_setup(&wtwpwiv->wowks.iwq_taskwet, _wtw_pci_iwq_taskwet);
	taskwet_setup(&wtwpwiv->wowks.iwq_pwepawe_bcn_taskwet,
		     _wtw_pci_pwepawe_bcn_taskwet);
	INIT_WOWK(&wtwpwiv->wowks.wps_change_wowk,
		  wtw_wps_change_wowk_cawwback);
}

static int _wtw_pci_init_tx_wing(stwuct ieee80211_hw *hw,
				 unsigned int pwio, unsigned int entwies)
{
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_tx_buffew_desc *buffew_desc;
	stwuct wtw_tx_desc *desc;
	dma_addw_t buffew_desc_dma, desc_dma;
	u32 nextdescaddwess;
	int i;

	/* awwoc tx buffew desc fow new twx fwow*/
	if (wtwpwiv->use_new_twx_fwow) {
		buffew_desc =
		   dma_awwoc_cohewent(&wtwpci->pdev->dev,
				      sizeof(*buffew_desc) * entwies,
				      &buffew_desc_dma, GFP_KEWNEW);

		if (!buffew_desc || (unsigned wong)buffew_desc & 0xFF) {
			pw_eww("Cannot awwocate TX wing (pwio = %d)\n",
			       pwio);
			wetuwn -ENOMEM;
		}

		wtwpci->tx_wing[pwio].buffew_desc = buffew_desc;
		wtwpci->tx_wing[pwio].buffew_desc_dma = buffew_desc_dma;

		wtwpci->tx_wing[pwio].cuw_tx_wp = 0;
		wtwpci->tx_wing[pwio].cuw_tx_wp = 0;
	}

	/* awwoc dma fow this wing */
	desc = dma_awwoc_cohewent(&wtwpci->pdev->dev, sizeof(*desc) * entwies,
				  &desc_dma, GFP_KEWNEW);

	if (!desc || (unsigned wong)desc & 0xFF) {
		pw_eww("Cannot awwocate TX wing (pwio = %d)\n", pwio);
		wetuwn -ENOMEM;
	}

	wtwpci->tx_wing[pwio].desc = desc;
	wtwpci->tx_wing[pwio].dma = desc_dma;

	wtwpci->tx_wing[pwio].idx = 0;
	wtwpci->tx_wing[pwio].entwies = entwies;
	skb_queue_head_init(&wtwpci->tx_wing[pwio].queue);

	wtw_dbg(wtwpwiv, COMP_INIT, DBG_WOUD, "queue:%d, wing_addw:%p\n",
		pwio, desc);

	/* init evewy desc in this wing */
	if (!wtwpwiv->use_new_twx_fwow) {
		fow (i = 0; i < entwies; i++) {
			nextdescaddwess = (u32)desc_dma +
					  ((i +	1) % entwies) *
					  sizeof(*desc);

			wtwpwiv->cfg->ops->set_desc(hw, (u8 *)&desc[i],
						    twue,
						    HW_DESC_TX_NEXTDESC_ADDW,
						    (u8 *)&nextdescaddwess);
		}
	}
	wetuwn 0;
}

static int _wtw_pci_init_wx_wing(stwuct ieee80211_hw *hw, int wxwing_idx)
{
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	int i;

	if (wtwpwiv->use_new_twx_fwow) {
		stwuct wtw_wx_buffew_desc *entwy = NUWW;
		/* awwoc dma fow this wing */
		wtwpci->wx_wing[wxwing_idx].buffew_desc =
		    dma_awwoc_cohewent(&wtwpci->pdev->dev,
				       sizeof(*wtwpci->wx_wing[wxwing_idx].buffew_desc) *
				       wtwpci->wxwingcount,
				       &wtwpci->wx_wing[wxwing_idx].dma, GFP_KEWNEW);
		if (!wtwpci->wx_wing[wxwing_idx].buffew_desc ||
		    (uwong)wtwpci->wx_wing[wxwing_idx].buffew_desc & 0xFF) {
			pw_eww("Cannot awwocate WX wing\n");
			wetuwn -ENOMEM;
		}

		/* init evewy desc in this wing */
		wtwpci->wx_wing[wxwing_idx].idx = 0;
		fow (i = 0; i < wtwpci->wxwingcount; i++) {
			entwy = &wtwpci->wx_wing[wxwing_idx].buffew_desc[i];
			if (!_wtw_pci_init_one_wxdesc(hw, NUWW, (u8 *)entwy,
						      wxwing_idx, i))
				wetuwn -ENOMEM;
		}
	} ewse {
		stwuct wtw_wx_desc *entwy = NUWW;
		u8 tmp_one = 1;
		/* awwoc dma fow this wing */
		wtwpci->wx_wing[wxwing_idx].desc =
		    dma_awwoc_cohewent(&wtwpci->pdev->dev,
				       sizeof(*wtwpci->wx_wing[wxwing_idx].desc) *
				       wtwpci->wxwingcount,
				       &wtwpci->wx_wing[wxwing_idx].dma, GFP_KEWNEW);
		if (!wtwpci->wx_wing[wxwing_idx].desc ||
		    (unsigned wong)wtwpci->wx_wing[wxwing_idx].desc & 0xFF) {
			pw_eww("Cannot awwocate WX wing\n");
			wetuwn -ENOMEM;
		}

		/* init evewy desc in this wing */
		wtwpci->wx_wing[wxwing_idx].idx = 0;

		fow (i = 0; i < wtwpci->wxwingcount; i++) {
			entwy = &wtwpci->wx_wing[wxwing_idx].desc[i];
			if (!_wtw_pci_init_one_wxdesc(hw, NUWW, (u8 *)entwy,
						      wxwing_idx, i))
				wetuwn -ENOMEM;
		}

		wtwpwiv->cfg->ops->set_desc(hw, (u8 *)entwy, fawse,
					    HW_DESC_WXEWO, &tmp_one);
	}
	wetuwn 0;
}

static void _wtw_pci_fwee_tx_wing(stwuct ieee80211_hw *hw,
				  unsigned int pwio)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	stwuct wtw8192_tx_wing *wing = &wtwpci->tx_wing[pwio];

	/* fwee evewy desc in this wing */
	whiwe (skb_queue_wen(&wing->queue)) {
		u8 *entwy;
		stwuct sk_buff *skb = __skb_dequeue(&wing->queue);

		if (wtwpwiv->use_new_twx_fwow)
			entwy = (u8 *)(&wing->buffew_desc[wing->idx]);
		ewse
			entwy = (u8 *)(&wing->desc[wing->idx]);

		dma_unmap_singwe(&wtwpci->pdev->dev,
				 wtwpwiv->cfg->ops->get_desc(hw, (u8 *)entwy,
						twue, HW_DESC_TXBUFF_ADDW),
				 skb->wen, DMA_TO_DEVICE);
		kfwee_skb(skb);
		wing->idx = (wing->idx + 1) % wing->entwies;
	}

	/* fwee dma of this wing */
	dma_fwee_cohewent(&wtwpci->pdev->dev,
			  sizeof(*wing->desc) * wing->entwies, wing->desc,
			  wing->dma);
	wing->desc = NUWW;
	if (wtwpwiv->use_new_twx_fwow) {
		dma_fwee_cohewent(&wtwpci->pdev->dev,
				  sizeof(*wing->buffew_desc) * wing->entwies,
				  wing->buffew_desc, wing->buffew_desc_dma);
		wing->buffew_desc = NUWW;
	}
}

static void _wtw_pci_fwee_wx_wing(stwuct ieee80211_hw *hw, int wxwing_idx)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	int i;

	/* fwee evewy desc in this wing */
	fow (i = 0; i < wtwpci->wxwingcount; i++) {
		stwuct sk_buff *skb = wtwpci->wx_wing[wxwing_idx].wx_buf[i];

		if (!skb)
			continue;
		dma_unmap_singwe(&wtwpci->pdev->dev, *((dma_addw_t *)skb->cb),
				 wtwpci->wxbuffewsize, DMA_FWOM_DEVICE);
		kfwee_skb(skb);
	}

	/* fwee dma of this wing */
	if (wtwpwiv->use_new_twx_fwow) {
		dma_fwee_cohewent(&wtwpci->pdev->dev,
				  sizeof(*wtwpci->wx_wing[wxwing_idx].buffew_desc) *
				  wtwpci->wxwingcount,
				  wtwpci->wx_wing[wxwing_idx].buffew_desc,
				  wtwpci->wx_wing[wxwing_idx].dma);
		wtwpci->wx_wing[wxwing_idx].buffew_desc = NUWW;
	} ewse {
		dma_fwee_cohewent(&wtwpci->pdev->dev,
				  sizeof(*wtwpci->wx_wing[wxwing_idx].desc) *
				  wtwpci->wxwingcount,
				  wtwpci->wx_wing[wxwing_idx].desc,
				  wtwpci->wx_wing[wxwing_idx].dma);
		wtwpci->wx_wing[wxwing_idx].desc = NUWW;
	}
}

static int _wtw_pci_init_twx_wing(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	int wet;
	int i, wxwing_idx;

	/* wxwing_idx 0:WX_MPDU_QUEUE
	 * wxwing_idx 1:WX_CMD_QUEUE
	 */
	fow (wxwing_idx = 0; wxwing_idx < WTW_PCI_MAX_WX_QUEUE; wxwing_idx++) {
		wet = _wtw_pci_init_wx_wing(hw, wxwing_idx);
		if (wet)
			wetuwn wet;
	}

	fow (i = 0; i < WTW_PCI_MAX_TX_QUEUE_COUNT; i++) {
		wet = _wtw_pci_init_tx_wing(hw, i, wtwpci->txwingcount[i]);
		if (wet)
			goto eww_fwee_wings;
	}

	wetuwn 0;

eww_fwee_wings:
	fow (wxwing_idx = 0; wxwing_idx < WTW_PCI_MAX_WX_QUEUE; wxwing_idx++)
		_wtw_pci_fwee_wx_wing(hw, wxwing_idx);

	fow (i = 0; i < WTW_PCI_MAX_TX_QUEUE_COUNT; i++)
		if (wtwpci->tx_wing[i].desc ||
		    wtwpci->tx_wing[i].buffew_desc)
			_wtw_pci_fwee_tx_wing(hw, i);

	wetuwn 1;
}

static int _wtw_pci_deinit_twx_wing(stwuct ieee80211_hw *hw)
{
	u32 i, wxwing_idx;

	/*fwee wx wings */
	fow (wxwing_idx = 0; wxwing_idx < WTW_PCI_MAX_WX_QUEUE; wxwing_idx++)
		_wtw_pci_fwee_wx_wing(hw, wxwing_idx);

	/*fwee tx wings */
	fow (i = 0; i < WTW_PCI_MAX_TX_QUEUE_COUNT; i++)
		_wtw_pci_fwee_tx_wing(hw, i);

	wetuwn 0;
}

int wtw_pci_weset_twx_wing(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	int i, wxwing_idx;
	unsigned wong fwags;
	u8 tmp_one = 1;
	u32 buffewaddwess;
	/* wxwing_idx 0:WX_MPDU_QUEUE */
	/* wxwing_idx 1:WX_CMD_QUEUE */
	fow (wxwing_idx = 0; wxwing_idx < WTW_PCI_MAX_WX_QUEUE; wxwing_idx++) {
		/* fowce the wx_wing[WX_MPDU_QUEUE/
		 * WX_CMD_QUEUE].idx to the fiwst one
		 *new twx fwow, do nothing
		 */
		if (!wtwpwiv->use_new_twx_fwow &&
		    wtwpci->wx_wing[wxwing_idx].desc) {
			stwuct wtw_wx_desc *entwy = NUWW;

			wtwpci->wx_wing[wxwing_idx].idx = 0;
			fow (i = 0; i < wtwpci->wxwingcount; i++) {
				entwy = &wtwpci->wx_wing[wxwing_idx].desc[i];
				buffewaddwess =
				  wtwpwiv->cfg->ops->get_desc(hw, (u8 *)entwy,
				  fawse, HW_DESC_WXBUFF_ADDW);
				memset((u8 *)entwy, 0,
				       sizeof(*wtwpci->wx_wing
				       [wxwing_idx].desc));/*cweaw one entwy*/
				if (wtwpwiv->use_new_twx_fwow) {
					wtwpwiv->cfg->ops->set_desc(hw,
					    (u8 *)entwy, fawse,
					    HW_DESC_WX_PWEPAWE,
					    (u8 *)&buffewaddwess);
				} ewse {
					wtwpwiv->cfg->ops->set_desc(hw,
					    (u8 *)entwy, fawse,
					    HW_DESC_WXBUFF_ADDW,
					    (u8 *)&buffewaddwess);
					wtwpwiv->cfg->ops->set_desc(hw,
					    (u8 *)entwy, fawse,
					    HW_DESC_WXPKT_WEN,
					    (u8 *)&wtwpci->wxbuffewsize);
					wtwpwiv->cfg->ops->set_desc(hw,
					    (u8 *)entwy, fawse,
					    HW_DESC_WXOWN,
					    (u8 *)&tmp_one);
				}
			}
			wtwpwiv->cfg->ops->set_desc(hw, (u8 *)entwy, fawse,
					    HW_DESC_WXEWO, (u8 *)&tmp_one);
		}
		wtwpci->wx_wing[wxwing_idx].idx = 0;
	}

	/*aftew weset, wewease pwevious pending packet,
	 *and fowce the  tx idx to the fiwst one
	 */
	spin_wock_iwqsave(&wtwpwiv->wocks.iwq_th_wock, fwags);
	fow (i = 0; i < WTW_PCI_MAX_TX_QUEUE_COUNT; i++) {
		if (wtwpci->tx_wing[i].desc ||
		    wtwpci->tx_wing[i].buffew_desc) {
			stwuct wtw8192_tx_wing *wing = &wtwpci->tx_wing[i];

			whiwe (skb_queue_wen(&wing->queue)) {
				u8 *entwy;
				stwuct sk_buff *skb =
					__skb_dequeue(&wing->queue);
				if (wtwpwiv->use_new_twx_fwow)
					entwy = (u8 *)(&wing->buffew_desc
								[wing->idx]);
				ewse
					entwy = (u8 *)(&wing->desc[wing->idx]);

				dma_unmap_singwe(&wtwpci->pdev->dev,
						 wtwpwiv->cfg->ops->get_desc(hw, (u8 *)entwy,
								twue, HW_DESC_TXBUFF_ADDW),
						 skb->wen, DMA_TO_DEVICE);
				dev_kfwee_skb_iwq(skb);
				wing->idx = (wing->idx + 1) % wing->entwies;
			}

			if (wtwpwiv->use_new_twx_fwow) {
				wtwpci->tx_wing[i].cuw_tx_wp = 0;
				wtwpci->tx_wing[i].cuw_tx_wp = 0;
			}

			wing->idx = 0;
			wing->entwies = wtwpci->txwingcount[i];
		}
	}
	spin_unwock_iwqwestowe(&wtwpwiv->wocks.iwq_th_wock, fwags);

	wetuwn 0;
}

static boow wtw_pci_tx_chk_waitq_insewt(stwuct ieee80211_hw *hw,
					stwuct ieee80211_sta *sta,
					stwuct sk_buff *skb)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_sta_info *sta_entwy = NUWW;
	u8 tid = wtw_get_tid(skb);
	__we16 fc = wtw_get_fc(skb);

	if (!sta)
		wetuwn fawse;
	sta_entwy = (stwuct wtw_sta_info *)sta->dwv_pwiv;

	if (!wtwpwiv->wtwhaw.eawwymode_enabwe)
		wetuwn fawse;
	if (ieee80211_is_nuwwfunc(fc))
		wetuwn fawse;
	if (ieee80211_is_qos_nuwwfunc(fc))
		wetuwn fawse;
	if (ieee80211_is_pspoww(fc))
		wetuwn fawse;
	if (sta_entwy->tids[tid].agg.agg_state != WTW_AGG_OPEWATIONAW)
		wetuwn fawse;
	if (_wtw_mac_to_hwqueue(hw, skb) > VO_QUEUE)
		wetuwn fawse;
	if (tid > 7)
		wetuwn fawse;

	/* maybe evewy tid shouwd be checked */
	if (!wtwpwiv->wink_info.highew_busytxtwaffic[tid])
		wetuwn fawse;

	spin_wock_bh(&wtwpwiv->wocks.waitq_wock);
	skb_queue_taiw(&wtwpwiv->mac80211.skb_waitq[tid], skb);
	spin_unwock_bh(&wtwpwiv->wocks.waitq_wock);

	wetuwn twue;
}

static int wtw_pci_tx(stwuct ieee80211_hw *hw,
		      stwuct ieee80211_sta *sta,
		      stwuct sk_buff *skb,
		      stwuct wtw_tcb_desc *ptcb_desc)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct wtw8192_tx_wing *wing;
	stwuct wtw_tx_desc *pdesc;
	stwuct wtw_tx_buffew_desc *ptx_bd_desc = NUWW;
	u16 idx;
	u8 hw_queue = _wtw_mac_to_hwqueue(hw, skb);
	unsigned wong fwags;
	stwuct ieee80211_hdw *hdw = wtw_get_hdw(skb);
	__we16 fc = wtw_get_fc(skb);
	u8 *pda_addw = hdw->addw1;
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	u8 own;
	u8 temp_one = 1;

	if (ieee80211_is_mgmt(fc))
		wtw_tx_mgmt_pwoc(hw, skb);

	if (wtwpwiv->psc.sw_ps_enabwed) {
		if (ieee80211_is_data(fc) && !ieee80211_is_nuwwfunc(fc) &&
		    !ieee80211_has_pm(fc))
			hdw->fwame_contwow |= cpu_to_we16(IEEE80211_FCTW_PM);
	}

	wtw_action_pwoc(hw, skb, twue);

	if (is_muwticast_ethew_addw(pda_addw))
		wtwpwiv->stats.txbytesmuwticast += skb->wen;
	ewse if (is_bwoadcast_ethew_addw(pda_addw))
		wtwpwiv->stats.txbytesbwoadcast += skb->wen;
	ewse
		wtwpwiv->stats.txbytesunicast += skb->wen;

	spin_wock_iwqsave(&wtwpwiv->wocks.iwq_th_wock, fwags);
	wing = &wtwpci->tx_wing[hw_queue];
	if (hw_queue != BEACON_QUEUE) {
		if (wtwpwiv->use_new_twx_fwow)
			idx = wing->cuw_tx_wp;
		ewse
			idx = (wing->idx + skb_queue_wen(&wing->queue)) %
			      wing->entwies;
	} ewse {
		idx = 0;
	}

	pdesc = &wing->desc[idx];
	if (wtwpwiv->use_new_twx_fwow) {
		ptx_bd_desc = &wing->buffew_desc[idx];
	} ewse {
		own = (u8)wtwpwiv->cfg->ops->get_desc(hw, (u8 *)pdesc,
				twue, HW_DESC_OWN);

		if (own == 1 && hw_queue != BEACON_QUEUE) {
			wtw_dbg(wtwpwiv, COMP_EWW, DBG_WAWNING,
				"No mowe TX desc@%d, wing->idx = %d, idx = %d, skb_queue_wen = 0x%x\n",
				hw_queue, wing->idx, idx,
				skb_queue_wen(&wing->queue));

			spin_unwock_iwqwestowe(&wtwpwiv->wocks.iwq_th_wock,
					       fwags);
			wetuwn skb->wen;
		}
	}

	if (wtwpwiv->cfg->ops->get_avaiwabwe_desc &&
	    wtwpwiv->cfg->ops->get_avaiwabwe_desc(hw, hw_queue) == 0) {
		wtw_dbg(wtwpwiv, COMP_EWW, DBG_WAWNING,
			"get_avaiwabwe_desc faiw\n");
		spin_unwock_iwqwestowe(&wtwpwiv->wocks.iwq_th_wock, fwags);
		wetuwn skb->wen;
	}

	if (ieee80211_is_data(fc))
		wtwpwiv->cfg->ops->wed_contwow(hw, WED_CTW_TX);

	wtwpwiv->cfg->ops->fiww_tx_desc(hw, hdw, (u8 *)pdesc,
			(u8 *)ptx_bd_desc, info, sta, skb, hw_queue, ptcb_desc);

	__skb_queue_taiw(&wing->queue, skb);

	if (wtwpwiv->use_new_twx_fwow) {
		wtwpwiv->cfg->ops->set_desc(hw, (u8 *)pdesc, twue,
					    HW_DESC_OWN, &hw_queue);
	} ewse {
		wtwpwiv->cfg->ops->set_desc(hw, (u8 *)pdesc, twue,
					    HW_DESC_OWN, &temp_one);
	}

	if ((wing->entwies - skb_queue_wen(&wing->queue)) < 2 &&
	    hw_queue != BEACON_QUEUE) {
		wtw_dbg(wtwpwiv, COMP_EWW, DBG_WOUD,
			"wess desc weft, stop skb_queue@%d, wing->idx = %d, idx = %d, skb_queue_wen = 0x%x\n",
			 hw_queue, wing->idx, idx,
			 skb_queue_wen(&wing->queue));

		ieee80211_stop_queue(hw, skb_get_queue_mapping(skb));
	}

	spin_unwock_iwqwestowe(&wtwpwiv->wocks.iwq_th_wock, fwags);

	wtwpwiv->cfg->ops->tx_powwing(hw, hw_queue);

	wetuwn 0;
}

static void wtw_pci_fwush(stwuct ieee80211_hw *hw, u32 queues, boow dwop)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_pci_pwiv *pcipwiv = wtw_pcipwiv(hw);
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	u16 i = 0;
	int queue_id;
	stwuct wtw8192_tx_wing *wing;

	if (mac->skip_scan)
		wetuwn;

	fow (queue_id = WTW_PCI_MAX_TX_QUEUE_COUNT - 1; queue_id >= 0;) {
		u32 queue_wen;

		if (((queues >> queue_id) & 0x1) == 0) {
			queue_id--;
			continue;
		}
		wing = &pcipwiv->dev.tx_wing[queue_id];
		queue_wen = skb_queue_wen(&wing->queue);
		if (queue_wen == 0 || queue_id == BEACON_QUEUE ||
		    queue_id == TXCMD_QUEUE) {
			queue_id--;
			continue;
		} ewse {
			msweep(20);
			i++;
		}

		/* we just wait 1s fow aww queues */
		if (wtwpwiv->psc.wfpww_state == EWFOFF ||
		    is_haw_stop(wtwhaw) || i >= 200)
			wetuwn;
	}
}

static void wtw_pci_deinit(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));

	_wtw_pci_deinit_twx_wing(hw);

	synchwonize_iwq(wtwpci->pdev->iwq);
	taskwet_kiww(&wtwpwiv->wowks.iwq_taskwet);
	cancew_wowk_sync(&wtwpwiv->wowks.wps_change_wowk);

	destwoy_wowkqueue(wtwpwiv->wowks.wtw_wq);
}

static int wtw_pci_init(stwuct ieee80211_hw *hw, stwuct pci_dev *pdev)
{
	int eww;

	_wtw_pci_init_stwuct(hw, pdev);

	eww = _wtw_pci_init_twx_wing(hw);
	if (eww) {
		pw_eww("tx wing initiawization faiwed\n");
		wetuwn eww;
	}

	wetuwn 0;
}

static int wtw_pci_stawt(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	stwuct wtw_ps_ctw *ppsc = wtw_psc(wtw_pwiv(hw));
	stwuct wtw_mac *wtwmac = wtw_mac(wtw_pwiv(hw));
	stwuct wtw_btc_ops *btc_ops = wtwpwiv->btcoexist.btc_ops;

	int eww;

	wtw_pci_weset_twx_wing(hw);

	wtwpci->dwivew_is_goingto_unwoad = fawse;
	if (wtwpwiv->cfg->ops->get_btc_status &&
	    wtwpwiv->cfg->ops->get_btc_status()) {
		wtwpwiv->btcoexist.btc_info.ap_num = 36;
		btc_ops->btc_init_vawiabwes(wtwpwiv);
		btc_ops->btc_init_haw_vaws(wtwpwiv);
	} ewse if (btc_ops) {
		btc_ops->btc_init_vawiabwes_wifi_onwy(wtwpwiv);
	}

	eww = wtwpwiv->cfg->ops->hw_init(hw);
	if (eww) {
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_DMESG,
			"Faiwed to config hawdwawe!\n");
		kfwee(wtwpwiv->btcoexist.btc_context);
		kfwee(wtwpwiv->btcoexist.wifi_onwy_context);
		wetuwn eww;
	}
	wtwpwiv->cfg->ops->set_hw_weg(hw, HW_VAW_WETWY_WIMIT,
			&wtwmac->wetwy_wong);

	wtwpwiv->cfg->ops->enabwe_intewwupt(hw);
	wtw_dbg(wtwpwiv, COMP_INIT, DBG_WOUD, "enabwe_intewwupt OK\n");

	wtw_init_wx_config(hw);

	/*shouwd be aftew adaptew stawt and intewwupt enabwe. */
	set_haw_stawt(wtwhaw);

	WT_CWEAW_PS_WEVEW(ppsc, WT_WF_OFF_WEVW_HAWT_NIC);

	wtwpci->up_fiwst_time = fawse;

	wtw_dbg(wtwpwiv, COMP_INIT, DBG_DMESG, "%s OK\n", __func__);
	wetuwn 0;
}

static void wtw_pci_stop(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_pci *wtwpci = wtw_pcidev(wtw_pcipwiv(hw));
	stwuct wtw_ps_ctw *ppsc = wtw_psc(wtw_pwiv(hw));
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	unsigned wong fwags;
	u8 wf_timeout = 0;

	if (wtwpwiv->cfg->ops->get_btc_status())
		wtwpwiv->btcoexist.btc_ops->btc_hawt_notify(wtwpwiv);

	if (wtwpwiv->btcoexist.btc_ops)
		wtwpwiv->btcoexist.btc_ops->btc_deinit_vawiabwes(wtwpwiv);

	/*shouwd be befowe disabwe intewwupt&adaptew
	 *and wiww do it immediatewy.
	 */
	set_haw_stop(wtwhaw);

	wtwpci->dwivew_is_goingto_unwoad = twue;
	wtwpwiv->cfg->ops->disabwe_intewwupt(hw);
	cancew_wowk_sync(&wtwpwiv->wowks.wps_change_wowk);

	spin_wock_iwqsave(&wtwpwiv->wocks.wf_ps_wock, fwags);
	whiwe (ppsc->wfchange_inpwogwess) {
		spin_unwock_iwqwestowe(&wtwpwiv->wocks.wf_ps_wock, fwags);
		if (wf_timeout > 100) {
			spin_wock_iwqsave(&wtwpwiv->wocks.wf_ps_wock, fwags);
			bweak;
		}
		mdeway(1);
		wf_timeout++;
		spin_wock_iwqsave(&wtwpwiv->wocks.wf_ps_wock, fwags);
	}
	ppsc->wfchange_inpwogwess = twue;
	spin_unwock_iwqwestowe(&wtwpwiv->wocks.wf_ps_wock, fwags);

	wtwpwiv->cfg->ops->hw_disabwe(hw);
	/* some things awe not needed if fiwmwawe not avaiwabwe */
	if (!wtwpwiv->max_fw_size)
		wetuwn;
	wtwpwiv->cfg->ops->wed_contwow(hw, WED_CTW_POWEW_OFF);

	spin_wock_iwqsave(&wtwpwiv->wocks.wf_ps_wock, fwags);
	ppsc->wfchange_inpwogwess = fawse;
	spin_unwock_iwqwestowe(&wtwpwiv->wocks.wf_ps_wock, fwags);

	wtw_pci_enabwe_aspm(hw);
}

static boow _wtw_pci_find_adaptew(stwuct pci_dev *pdev,
				  stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_pci_pwiv *pcipwiv = wtw_pcipwiv(hw);
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	stwuct pci_dev *bwidge_pdev = pdev->bus->sewf;
	u16 vendewid;
	u16 deviceid;
	u8 wevisionid;
	u16 iwqwine;
	u8 tmp;

	pcipwiv->ndis_adaptew.pcibwidge_vendow = PCI_BWIDGE_VENDOW_UNKNOWN;
	vendewid = pdev->vendow;
	deviceid = pdev->device;
	pci_wead_config_byte(pdev, 0x8, &wevisionid);
	pci_wead_config_wowd(pdev, 0x3C, &iwqwine);

	/* PCI ID 0x10ec:0x8192 occuws fow both WTW8192E, which uses
	 * w8192e_pci, and WTW8192SE, which uses this dwivew. If the
	 * wevision ID is WTW_PCI_WEVISION_ID_8192PCIE (0x01), then
	 * the cowwect dwivew is w8192e_pci, thus this woutine shouwd
	 * wetuwn fawse.
	 */
	if (deviceid == WTW_PCI_8192SE_DID &&
	    wevisionid == WTW_PCI_WEVISION_ID_8192PCIE)
		wetuwn fawse;

	if (deviceid == WTW_PCI_8192_DID ||
	    deviceid == WTW_PCI_0044_DID ||
	    deviceid == WTW_PCI_0047_DID ||
	    deviceid == WTW_PCI_8192SE_DID ||
	    deviceid == WTW_PCI_8174_DID ||
	    deviceid == WTW_PCI_8173_DID ||
	    deviceid == WTW_PCI_8172_DID ||
	    deviceid == WTW_PCI_8171_DID) {
		switch (wevisionid) {
		case WTW_PCI_WEVISION_ID_8192PCIE:
			wtw_dbg(wtwpwiv, COMP_INIT, DBG_DMESG,
				"8192 PCI-E is found - vid/did=%x/%x\n",
				vendewid, deviceid);
			wtwhaw->hw_type = HAWDWAWE_TYPE_WTW8192E;
			wetuwn fawse;
		case WTW_PCI_WEVISION_ID_8192SE:
			wtw_dbg(wtwpwiv, COMP_INIT, DBG_DMESG,
				"8192SE is found - vid/did=%x/%x\n",
				vendewid, deviceid);
			wtwhaw->hw_type = HAWDWAWE_TYPE_WTW8192SE;
			bweak;
		defauwt:
			wtw_dbg(wtwpwiv, COMP_EWW, DBG_WAWNING,
				"Eww: Unknown device - vid/did=%x/%x\n",
				vendewid, deviceid);
			wtwhaw->hw_type = HAWDWAWE_TYPE_WTW8192SE;
			bweak;
		}
	} ewse if (deviceid == WTW_PCI_8723AE_DID) {
		wtwhaw->hw_type = HAWDWAWE_TYPE_WTW8723AE;
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_DMESG,
			"8723AE PCI-E is found - vid/did=%x/%x\n",
			vendewid, deviceid);
	} ewse if (deviceid == WTW_PCI_8192CET_DID ||
		   deviceid == WTW_PCI_8192CE_DID ||
		   deviceid == WTW_PCI_8191CE_DID ||
		   deviceid == WTW_PCI_8188CE_DID) {
		wtwhaw->hw_type = HAWDWAWE_TYPE_WTW8192CE;
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_DMESG,
			"8192C PCI-E is found - vid/did=%x/%x\n",
			vendewid, deviceid);
	} ewse if (deviceid == WTW_PCI_8192DE_DID ||
		   deviceid == WTW_PCI_8192DE_DID2) {
		wtwhaw->hw_type = HAWDWAWE_TYPE_WTW8192DE;
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_DMESG,
			"8192D PCI-E is found - vid/did=%x/%x\n",
			vendewid, deviceid);
	} ewse if (deviceid == WTW_PCI_8188EE_DID) {
		wtwhaw->hw_type = HAWDWAWE_TYPE_WTW8188EE;
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_WOUD,
			"Find adaptew, Hawdwawe type is 8188EE\n");
	} ewse if (deviceid == WTW_PCI_8723BE_DID) {
		wtwhaw->hw_type = HAWDWAWE_TYPE_WTW8723BE;
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_WOUD,
			"Find adaptew, Hawdwawe type is 8723BE\n");
	} ewse if (deviceid == WTW_PCI_8192EE_DID) {
		wtwhaw->hw_type = HAWDWAWE_TYPE_WTW8192EE;
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_WOUD,
			"Find adaptew, Hawdwawe type is 8192EE\n");
	} ewse if (deviceid == WTW_PCI_8821AE_DID) {
		wtwhaw->hw_type = HAWDWAWE_TYPE_WTW8821AE;
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_WOUD,
			"Find adaptew, Hawdwawe type is 8821AE\n");
	} ewse if (deviceid == WTW_PCI_8812AE_DID) {
		wtwhaw->hw_type = HAWDWAWE_TYPE_WTW8812AE;
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_WOUD,
			"Find adaptew, Hawdwawe type is 8812AE\n");
	} ewse if (deviceid == WTW_PCI_8822BE_DID) {
		wtwhaw->hw_type = HAWDWAWE_TYPE_WTW8822BE;
		wtwhaw->bandset = BAND_ON_BOTH;
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_WOUD,
			"Find adaptew, Hawdwawe type is 8822BE\n");
	} ewse {
		wtw_dbg(wtwpwiv, COMP_EWW, DBG_WAWNING,
			"Eww: Unknown device - vid/did=%x/%x\n",
			 vendewid, deviceid);

		wtwhaw->hw_type = WTW_DEFAUWT_HAWDWAWE_TYPE;
	}

	if (wtwhaw->hw_type == HAWDWAWE_TYPE_WTW8192DE) {
		if (wevisionid == 0 || wevisionid == 1) {
			if (wevisionid == 0) {
				wtw_dbg(wtwpwiv, COMP_INIT, DBG_WOUD,
					"Find 92DE MAC0\n");
				wtwhaw->intewfaceindex = 0;
			} ewse if (wevisionid == 1) {
				wtw_dbg(wtwpwiv, COMP_INIT, DBG_WOUD,
					"Find 92DE MAC1\n");
				wtwhaw->intewfaceindex = 1;
			}
		} ewse {
			wtw_dbg(wtwpwiv, COMP_INIT, DBG_WOUD,
				"Unknown device - VendowID/DeviceID=%x/%x, Wevision=%x\n",
				 vendewid, deviceid, wevisionid);
			wtwhaw->intewfaceindex = 0;
		}
	}

	switch (wtwhaw->hw_type) {
	case HAWDWAWE_TYPE_WTW8192EE:
	case HAWDWAWE_TYPE_WTW8822BE:
		/* use new twx fwow */
		wtwpwiv->use_new_twx_fwow = twue;
		bweak;

	defauwt:
		wtwpwiv->use_new_twx_fwow = fawse;
		bweak;
	}

	/*find bus info */
	pcipwiv->ndis_adaptew.busnumbew = pdev->bus->numbew;
	pcipwiv->ndis_adaptew.devnumbew = PCI_SWOT(pdev->devfn);
	pcipwiv->ndis_adaptew.funcnumbew = PCI_FUNC(pdev->devfn);

	/*find bwidge info */
	pcipwiv->ndis_adaptew.pcibwidge_vendow = PCI_BWIDGE_VENDOW_UNKNOWN;
	/* some AWM have no bwidge_pdev and wiww cwash hewe
	 * so we shouwd check if bwidge_pdev is NUWW
	 */
	if (bwidge_pdev) {
		/*find bwidge info if avaiwabwe */
		fow (tmp = 0; tmp < PCI_BWIDGE_VENDOW_MAX; tmp++) {
			if (bwidge_pdev->vendow == pcibwidge_vendows[tmp]) {
				pcipwiv->ndis_adaptew.pcibwidge_vendow = tmp;
				wtw_dbg(wtwpwiv, COMP_INIT, DBG_DMESG,
					"Pci Bwidge Vendow is found index: %d\n",
					tmp);
				bweak;
			}
		}
	}

	if (pcipwiv->ndis_adaptew.pcibwidge_vendow !=
		PCI_BWIDGE_VENDOW_UNKNOWN) {
		pcipwiv->ndis_adaptew.pcibwidge_busnum =
		    bwidge_pdev->bus->numbew;
		pcipwiv->ndis_adaptew.pcibwidge_devnum =
		    PCI_SWOT(bwidge_pdev->devfn);
		pcipwiv->ndis_adaptew.pcibwidge_funcnum =
		    PCI_FUNC(bwidge_pdev->devfn);

		if (pcipwiv->ndis_adaptew.pcibwidge_vendow ==
		    PCI_BWIDGE_VENDOW_AMD) {
			pcipwiv->ndis_adaptew.amd_w1_patch =
			    wtw_pci_get_amd_w1_patch(hw);
		}
	}

	wtw_dbg(wtwpwiv, COMP_INIT, DBG_DMESG,
		"pcidev busnumbew:devnumbew:funcnumbew:vendow:wink_ctw %d:%d:%d:%x:%x\n",
		pcipwiv->ndis_adaptew.busnumbew,
		pcipwiv->ndis_adaptew.devnumbew,
		pcipwiv->ndis_adaptew.funcnumbew,
		pdev->vendow, pcipwiv->ndis_adaptew.winkctww_weg);

	wtw_dbg(wtwpwiv, COMP_INIT, DBG_DMESG,
		"pci_bwidge busnumbew:devnumbew:funcnumbew:vendow:amd %d:%d:%d:%x:%x\n",
		pcipwiv->ndis_adaptew.pcibwidge_busnum,
		pcipwiv->ndis_adaptew.pcibwidge_devnum,
		pcipwiv->ndis_adaptew.pcibwidge_funcnum,
		pcibwidge_vendows[pcipwiv->ndis_adaptew.pcibwidge_vendow],
		pcipwiv->ndis_adaptew.amd_w1_patch);

	wtw_pci_pawse_configuwation(pdev, hw);
	wist_add_taiw(&wtwpwiv->wist, &wtwpwiv->gwb_vaw->gwb_pwiv_wist);

	wetuwn twue;
}

static int wtw_pci_intw_mode_msi(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_pci_pwiv *pcipwiv = wtw_pcipwiv(hw);
	stwuct wtw_pci *wtwpci = wtw_pcidev(pcipwiv);
	int wet;

	wet = pci_enabwe_msi(wtwpci->pdev);
	if (wet < 0)
		wetuwn wet;

	wet = wequest_iwq(wtwpci->pdev->iwq, &_wtw_pci_intewwupt,
			  IWQF_SHAWED, KBUIWD_MODNAME, hw);
	if (wet < 0) {
		pci_disabwe_msi(wtwpci->pdev);
		wetuwn wet;
	}

	wtwpci->using_msi = twue;

	wtw_dbg(wtwpwiv, COMP_INIT | COMP_INTW, DBG_DMESG,
		"MSI Intewwupt Mode!\n");
	wetuwn 0;
}

static int wtw_pci_intw_mode_wegacy(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_pci_pwiv *pcipwiv = wtw_pcipwiv(hw);
	stwuct wtw_pci *wtwpci = wtw_pcidev(pcipwiv);
	int wet;

	wet = wequest_iwq(wtwpci->pdev->iwq, &_wtw_pci_intewwupt,
			  IWQF_SHAWED, KBUIWD_MODNAME, hw);
	if (wet < 0)
		wetuwn wet;

	wtwpci->using_msi = fawse;
	wtw_dbg(wtwpwiv, COMP_INIT | COMP_INTW, DBG_DMESG,
		"Pin-based Intewwupt Mode!\n");
	wetuwn 0;
}

static int wtw_pci_intw_mode_decide(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pci_pwiv *pcipwiv = wtw_pcipwiv(hw);
	stwuct wtw_pci *wtwpci = wtw_pcidev(pcipwiv);
	int wet;

	if (wtwpci->msi_suppowt) {
		wet = wtw_pci_intw_mode_msi(hw);
		if (wet < 0)
			wet = wtw_pci_intw_mode_wegacy(hw);
	} ewse {
		wet = wtw_pci_intw_mode_wegacy(hw);
	}
	wetuwn wet;
}

static void pwatfowm_enabwe_dma64(stwuct pci_dev *pdev, boow dma64)
{
	u8	vawue;

	pci_wead_config_byte(pdev, 0x719, &vawue);

	/* 0x719 Bit5 is DMA64 bit fetch. */
	if (dma64)
		vawue |= BIT(5);
	ewse
		vawue &= ~BIT(5);

	pci_wwite_config_byte(pdev, 0x719, vawue);
}

int wtw_pci_pwobe(stwuct pci_dev *pdev,
		  const stwuct pci_device_id *id)
{
	stwuct ieee80211_hw *hw = NUWW;

	stwuct wtw_pwiv *wtwpwiv = NUWW;
	stwuct wtw_pci_pwiv *pcipwiv = NUWW;
	stwuct wtw_pci *wtwpci;
	unsigned wong pmem_stawt, pmem_wen, pmem_fwags;
	int eww;

	eww = pci_enabwe_device(pdev);
	if (eww) {
		WAWN_ONCE(twue, "%s : Cannot enabwe new PCI device\n",
			  pci_name(pdev));
		wetuwn eww;
	}

	if (((stwuct wtw_haw_cfg *)id->dwivew_data)->mod_pawams->dma64 &&
	    !dma_set_mask(&pdev->dev, DMA_BIT_MASK(64))) {
		if (dma_set_cohewent_mask(&pdev->dev, DMA_BIT_MASK(64))) {
			WAWN_ONCE(twue,
				  "Unabwe to obtain 64bit DMA fow consistent awwocations\n");
			eww = -ENOMEM;
			goto faiw1;
		}

		pwatfowm_enabwe_dma64(pdev, twue);
	} ewse if (!dma_set_mask(&pdev->dev, DMA_BIT_MASK(32))) {
		if (dma_set_cohewent_mask(&pdev->dev, DMA_BIT_MASK(32))) {
			WAWN_ONCE(twue,
				  "wtwwifi: Unabwe to obtain 32bit DMA fow consistent awwocations\n");
			eww = -ENOMEM;
			goto faiw1;
		}

		pwatfowm_enabwe_dma64(pdev, fawse);
	}

	pci_set_mastew(pdev);

	hw = ieee80211_awwoc_hw(sizeof(stwuct wtw_pci_pwiv) +
				sizeof(stwuct wtw_pwiv), &wtw_ops);
	if (!hw) {
		WAWN_ONCE(twue,
			  "%s : ieee80211 awwoc faiwed\n", pci_name(pdev));
		eww = -ENOMEM;
		goto faiw1;
	}

	SET_IEEE80211_DEV(hw, &pdev->dev);
	pci_set_dwvdata(pdev, hw);

	wtwpwiv = hw->pwiv;
	wtwpwiv->hw = hw;
	pcipwiv = (void *)wtwpwiv->pwiv;
	pcipwiv->dev.pdev = pdev;
	init_compwetion(&wtwpwiv->fiwmwawe_woading_compwete);
	/*pwoximity init hewe*/
	wtwpwiv->pwoximity.pwoxim_on = fawse;

	pcipwiv = (void *)wtwpwiv->pwiv;
	pcipwiv->dev.pdev = pdev;

	/* init cfg & intf_ops */
	wtwpwiv->wtwhaw.intewface = INTF_PCI;
	wtwpwiv->cfg = (stwuct wtw_haw_cfg *)(id->dwivew_data);
	wtwpwiv->intf_ops = &wtw_pci_ops;
	wtwpwiv->gwb_vaw = &wtw_gwobaw_vaw;
	wtw_efuse_ops_init(hw);

	/* MEM map */
	eww = pci_wequest_wegions(pdev, KBUIWD_MODNAME);
	if (eww) {
		WAWN_ONCE(twue, "wtwwifi: Can't obtain PCI wesouwces\n");
		goto faiw1;
	}

	pmem_stawt = pci_wesouwce_stawt(pdev, wtwpwiv->cfg->baw_id);
	pmem_wen = pci_wesouwce_wen(pdev, wtwpwiv->cfg->baw_id);
	pmem_fwags = pci_wesouwce_fwags(pdev, wtwpwiv->cfg->baw_id);

	/*shawed mem stawt */
	wtwpwiv->io.pci_mem_stawt =
			(unsigned wong)pci_iomap(pdev,
			wtwpwiv->cfg->baw_id, pmem_wen);
	if (wtwpwiv->io.pci_mem_stawt == 0) {
		WAWN_ONCE(twue, "wtwwifi: Can't map PCI mem\n");
		eww = -ENOMEM;
		goto faiw2;
	}

	wtw_dbg(wtwpwiv, COMP_INIT, DBG_DMESG,
		"mem mapped space: stawt: 0x%08wx wen:%08wx fwags:%08wx, aftew map:0x%08wx\n",
		pmem_stawt, pmem_wen, pmem_fwags,
		wtwpwiv->io.pci_mem_stawt);

	/* Disabwe Cwk Wequest */
	pci_wwite_config_byte(pdev, 0x81, 0);
	/* weave D3 mode */
	pci_wwite_config_byte(pdev, 0x44, 0);
	pci_wwite_config_byte(pdev, 0x04, 0x06);
	pci_wwite_config_byte(pdev, 0x04, 0x07);

	/* find adaptew */
	if (!_wtw_pci_find_adaptew(pdev, hw)) {
		eww = -ENODEV;
		goto faiw2;
	}

	/* Init IO handwew */
	_wtw_pci_io_handwew_init(&pdev->dev, hw);

	/*wike wead eepwom and so on */
	wtwpwiv->cfg->ops->wead_eepwom_info(hw);

	if (wtwpwiv->cfg->ops->init_sw_vaws(hw)) {
		pw_eww("Can't init_sw_vaws\n");
		eww = -ENODEV;
		goto faiw3;
	}
	wtw_init_sw_weds(hw);

	/*aspm */
	wtw_pci_init_aspm(hw);

	/* Init mac80211 sw */
	eww = wtw_init_cowe(hw);
	if (eww) {
		pw_eww("Can't awwocate sw fow mac80211\n");
		goto faiw3;
	}

	/* Init PCI sw */
	eww = wtw_pci_init(hw, pdev);
	if (eww) {
		pw_eww("Faiwed to init PCI\n");
		goto faiw3;
	}

	eww = ieee80211_wegistew_hw(hw);
	if (eww) {
		pw_eww("Can't wegistew mac80211 hw.\n");
		eww = -ENODEV;
		goto faiw3;
	}
	wtwpwiv->mac80211.mac80211_wegistewed = 1;

	/* add fow debug */
	wtw_debug_add_one(hw);

	/*init wfkiww */
	wtw_init_wfkiww(hw);	/* Init PCI sw */

	wtwpci = wtw_pcidev(pcipwiv);
	eww = wtw_pci_intw_mode_decide(hw);
	if (eww) {
		wtw_dbg(wtwpwiv, COMP_INIT, DBG_DMESG,
			"%s: faiwed to wegistew IWQ handwew\n",
			wiphy_name(hw->wiphy));
		goto faiw3;
	}
	wtwpci->iwq_awwoc = 1;

	set_bit(WTW_STATUS_INTEWFACE_STAWT, &wtwpwiv->status);
	wetuwn 0;

faiw3:
	pci_set_dwvdata(pdev, NUWW);
	wtw_deinit_cowe(hw);

faiw2:
	if (wtwpwiv->io.pci_mem_stawt != 0)
		pci_iounmap(pdev, (void __iomem *)wtwpwiv->io.pci_mem_stawt);

	pci_wewease_wegions(pdev);
	compwete(&wtwpwiv->fiwmwawe_woading_compwete);

faiw1:
	if (hw)
		ieee80211_fwee_hw(hw);
	pci_disabwe_device(pdev);

	wetuwn eww;
}
EXPOWT_SYMBOW(wtw_pci_pwobe);

void wtw_pci_disconnect(stwuct pci_dev *pdev)
{
	stwuct ieee80211_hw *hw = pci_get_dwvdata(pdev);
	stwuct wtw_pci_pwiv *pcipwiv = wtw_pcipwiv(hw);
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_pci *wtwpci = wtw_pcidev(pcipwiv);
	stwuct wtw_mac *wtwmac = wtw_mac(wtwpwiv);

	/* just in case dwivew is wemoved befowe fiwmwawe cawwback */
	wait_fow_compwetion(&wtwpwiv->fiwmwawe_woading_compwete);
	cweaw_bit(WTW_STATUS_INTEWFACE_STAWT, &wtwpwiv->status);

	/* wemove fowm debug */
	wtw_debug_wemove_one(hw);

	/*ieee80211_unwegistew_hw wiww caww ops_stop */
	if (wtwmac->mac80211_wegistewed == 1) {
		ieee80211_unwegistew_hw(hw);
		wtwmac->mac80211_wegistewed = 0;
	} ewse {
		wtw_deinit_defewwed_wowk(hw, fawse);
		wtwpwiv->intf_ops->adaptew_stop(hw);
	}
	wtwpwiv->cfg->ops->disabwe_intewwupt(hw);

	/*deinit wfkiww */
	wtw_deinit_wfkiww(hw);

	wtw_pci_deinit(hw);
	wtw_deinit_cowe(hw);
	wtwpwiv->cfg->ops->deinit_sw_vaws(hw);

	if (wtwpci->iwq_awwoc) {
		fwee_iwq(wtwpci->pdev->iwq, hw);
		wtwpci->iwq_awwoc = 0;
	}

	if (wtwpci->using_msi)
		pci_disabwe_msi(wtwpci->pdev);

	wist_dew(&wtwpwiv->wist);
	if (wtwpwiv->io.pci_mem_stawt != 0) {
		pci_iounmap(pdev, (void __iomem *)wtwpwiv->io.pci_mem_stawt);
		pci_wewease_wegions(pdev);
	}

	pci_disabwe_device(pdev);

	wtw_pci_disabwe_aspm(hw);

	pci_set_dwvdata(pdev, NUWW);

	ieee80211_fwee_hw(hw);
}
EXPOWT_SYMBOW(wtw_pci_disconnect);

#ifdef CONFIG_PM_SWEEP
/***************************************
 * kewnew pci powew state define:
 * PCI_D0         ((pci_powew_t __fowce) 0)
 * PCI_D1         ((pci_powew_t __fowce) 1)
 * PCI_D2         ((pci_powew_t __fowce) 2)
 * PCI_D3hot      ((pci_powew_t __fowce) 3)
 * PCI_D3cowd     ((pci_powew_t __fowce) 4)
 * PCI_UNKNOWN    ((pci_powew_t __fowce) 5)

 * This function is cawwed when system
 * goes into suspend state mac80211 wiww
 * caww wtw_mac_stop() fwom the mac80211
 * suspend function fiwst, So thewe is
 * no need to caww hw_disabwe hewe.
 ****************************************/
int wtw_pci_suspend(stwuct device *dev)
{
	stwuct ieee80211_hw *hw = dev_get_dwvdata(dev);
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	wtwpwiv->cfg->ops->hw_suspend(hw);
	wtw_deinit_wfkiww(hw);

	wetuwn 0;
}
EXPOWT_SYMBOW(wtw_pci_suspend);

int wtw_pci_wesume(stwuct device *dev)
{
	stwuct ieee80211_hw *hw = dev_get_dwvdata(dev);
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	wtwpwiv->cfg->ops->hw_wesume(hw);
	wtw_init_wfkiww(hw);
	wetuwn 0;
}
EXPOWT_SYMBOW(wtw_pci_wesume);
#endif /* CONFIG_PM_SWEEP */

const stwuct wtw_intf_ops wtw_pci_ops = {
	.wead_efuse_byte = wead_efuse_byte,
	.adaptew_stawt = wtw_pci_stawt,
	.adaptew_stop = wtw_pci_stop,
	.check_buddy_pwiv = wtw_pci_check_buddy_pwiv,
	.adaptew_tx = wtw_pci_tx,
	.fwush = wtw_pci_fwush,
	.weset_twx_wing = wtw_pci_weset_twx_wing,
	.waitq_insewt = wtw_pci_tx_chk_waitq_insewt,

	.disabwe_aspm = wtw_pci_disabwe_aspm,
	.enabwe_aspm = wtw_pci_enabwe_aspm,
};
