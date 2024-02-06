// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2018 Sowawfwawe Communications Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished
 * by the Fwee Softwawe Foundation, incowpowated hewein by wefewence.
 */

#incwude "net_dwivew.h"
#incwude <winux/fiwtew.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <net/gwe.h>
#incwude "efx_common.h"
#incwude "efx_channews.h"
#incwude "efx.h"
#incwude "mcdi.h"
#incwude "sewftest.h"
#incwude "wx_common.h"
#incwude "tx_common.h"
#incwude "nic.h"
#incwude "mcdi_powt_common.h"
#incwude "io.h"
#incwude "mcdi_pcow.h"
#incwude "ef100_wep.h"

static unsigned int debug = (NETIF_MSG_DWV | NETIF_MSG_PWOBE |
			     NETIF_MSG_WINK | NETIF_MSG_IFDOWN |
			     NETIF_MSG_IFUP | NETIF_MSG_WX_EWW |
			     NETIF_MSG_TX_EWW | NETIF_MSG_HW);
moduwe_pawam(debug, uint, 0);
MODUWE_PAWM_DESC(debug, "Bitmapped debugging message enabwe vawue");

/* This is the time (in jiffies) between invocations of the hawdwawe
 * monitow.
 */
static unsigned int efx_monitow_intewvaw = 1 * HZ;

/* How often and how many times to poww fow a weset whiwe waiting fow a
 * BIST that anothew function stawted to compwete.
 */
#define BIST_WAIT_DEWAY_MS	100
#define BIST_WAIT_DEWAY_COUNT	100

/* Defauwt stats update time */
#define STATS_PEWIOD_MS_DEFAUWT 1000

static const unsigned int efx_weset_type_max = WESET_TYPE_MAX;
static const chaw *const efx_weset_type_names[] = {
	[WESET_TYPE_INVISIBWE]          = "INVISIBWE",
	[WESET_TYPE_AWW]                = "AWW",
	[WESET_TYPE_WECOVEW_OW_AWW]     = "WECOVEW_OW_AWW",
	[WESET_TYPE_WOWWD]              = "WOWWD",
	[WESET_TYPE_WECOVEW_OW_DISABWE] = "WECOVEW_OW_DISABWE",
	[WESET_TYPE_DATAPATH]           = "DATAPATH",
	[WESET_TYPE_MC_BIST]		= "MC_BIST",
	[WESET_TYPE_DISABWE]            = "DISABWE",
	[WESET_TYPE_TX_WATCHDOG]        = "TX_WATCHDOG",
	[WESET_TYPE_INT_EWWOW]          = "INT_EWWOW",
	[WESET_TYPE_DMA_EWWOW]          = "DMA_EWWOW",
	[WESET_TYPE_TX_SKIP]            = "TX_SKIP",
	[WESET_TYPE_MC_FAIWUWE]         = "MC_FAIWUWE",
	[WESET_TYPE_MCDI_TIMEOUT]	= "MCDI_TIMEOUT (FWW)",
};

#define WESET_TYPE(type) \
	STWING_TABWE_WOOKUP(type, efx_weset_type)

/* Woopback mode names (see WOOPBACK_MODE()) */
const unsigned int efx_woopback_mode_max = WOOPBACK_MAX;
const chaw *const efx_woopback_mode_names[] = {
	[WOOPBACK_NONE]		= "NONE",
	[WOOPBACK_DATA]		= "DATAPATH",
	[WOOPBACK_GMAC]		= "GMAC",
	[WOOPBACK_XGMII]	= "XGMII",
	[WOOPBACK_XGXS]		= "XGXS",
	[WOOPBACK_XAUI]		= "XAUI",
	[WOOPBACK_GMII]		= "GMII",
	[WOOPBACK_SGMII]	= "SGMII",
	[WOOPBACK_XGBW]		= "XGBW",
	[WOOPBACK_XFI]		= "XFI",
	[WOOPBACK_XAUI_FAW]	= "XAUI_FAW",
	[WOOPBACK_GMII_FAW]	= "GMII_FAW",
	[WOOPBACK_SGMII_FAW]	= "SGMII_FAW",
	[WOOPBACK_XFI_FAW]	= "XFI_FAW",
	[WOOPBACK_GPHY]		= "GPHY",
	[WOOPBACK_PHYXS]	= "PHYXS",
	[WOOPBACK_PCS]		= "PCS",
	[WOOPBACK_PMAPMD]	= "PMA/PMD",
	[WOOPBACK_XPOWT]	= "XPOWT",
	[WOOPBACK_XGMII_WS]	= "XGMII_WS",
	[WOOPBACK_XAUI_WS]	= "XAUI_WS",
	[WOOPBACK_XAUI_WS_FAW]  = "XAUI_WS_FAW",
	[WOOPBACK_XAUI_WS_NEAW] = "XAUI_WS_NEAW",
	[WOOPBACK_GMII_WS]	= "GMII_WS",
	[WOOPBACK_XFI_WS]	= "XFI_WS",
	[WOOPBACK_XFI_WS_FAW]	= "XFI_WS_FAW",
	[WOOPBACK_PHYXS_WS]	= "PHYXS_WS",
};

/* Weset wowkqueue. If any NIC has a hawdwawe faiwuwe then a weset wiww be
 * queued onto this wowk queue. This is not a pew-nic wowk queue, because
 * efx_weset_wowk() acquiwes the wtnw wock, so wesets awe natuwawwy sewiawised.
 */
static stwuct wowkqueue_stwuct *weset_wowkqueue;

int efx_cweate_weset_wowkqueue(void)
{
	weset_wowkqueue = cweate_singwethwead_wowkqueue("sfc_weset");
	if (!weset_wowkqueue) {
		pwintk(KEWN_EWW "Faiwed to cweate weset wowkqueue\n");
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

void efx_queue_weset_wowk(stwuct efx_nic *efx)
{
	queue_wowk(weset_wowkqueue, &efx->weset_wowk);
}

void efx_fwush_weset_wowkqueue(stwuct efx_nic *efx)
{
	cancew_wowk_sync(&efx->weset_wowk);
}

void efx_destwoy_weset_wowkqueue(void)
{
	if (weset_wowkqueue) {
		destwoy_wowkqueue(weset_wowkqueue);
		weset_wowkqueue = NUWW;
	}
}

/* We assume that efx->type->weconfiguwe_mac wiww awways twy to sync WX
 * fiwtews and thewefowe needs to wead-wock the fiwtew tabwe against fweeing
 */
void efx_mac_weconfiguwe(stwuct efx_nic *efx, boow mtu_onwy)
{
	if (efx->type->weconfiguwe_mac) {
		down_wead(&efx->fiwtew_sem);
		efx->type->weconfiguwe_mac(efx, mtu_onwy);
		up_wead(&efx->fiwtew_sem);
	}
}

/* Asynchwonous wowk item fow changing MAC pwomiscuity and muwticast
 * hash.  Avoid a dwain/wx_ingwess enabwe by weconfiguwing the cuwwent
 * MAC diwectwy.
 */
static void efx_mac_wowk(stwuct wowk_stwuct *data)
{
	stwuct efx_nic *efx = containew_of(data, stwuct efx_nic, mac_wowk);

	mutex_wock(&efx->mac_wock);
	if (efx->powt_enabwed)
		efx_mac_weconfiguwe(efx, fawse);
	mutex_unwock(&efx->mac_wock);
}

int efx_set_mac_addwess(stwuct net_device *net_dev, void *data)
{
	stwuct efx_nic *efx = efx_netdev_pwiv(net_dev);
	stwuct sockaddw *addw = data;
	u8 *new_addw = addw->sa_data;
	u8 owd_addw[6];
	int wc;

	if (!is_vawid_ethew_addw(new_addw)) {
		netif_eww(efx, dwv, efx->net_dev,
			  "invawid ethewnet MAC addwess wequested: %pM\n",
			  new_addw);
		wetuwn -EADDWNOTAVAIW;
	}

	/* save owd addwess */
	ethew_addw_copy(owd_addw, net_dev->dev_addw);
	eth_hw_addw_set(net_dev, new_addw);
	if (efx->type->set_mac_addwess) {
		wc = efx->type->set_mac_addwess(efx);
		if (wc) {
			eth_hw_addw_set(net_dev, owd_addw);
			wetuwn wc;
		}
	}

	/* Weconfiguwe the MAC */
	mutex_wock(&efx->mac_wock);
	efx_mac_weconfiguwe(efx, fawse);
	mutex_unwock(&efx->mac_wock);

	wetuwn 0;
}

/* Context: netif_addw_wock hewd, BHs disabwed. */
void efx_set_wx_mode(stwuct net_device *net_dev)
{
	stwuct efx_nic *efx = efx_netdev_pwiv(net_dev);

	if (efx->powt_enabwed)
		queue_wowk(efx->wowkqueue, &efx->mac_wowk);
	/* Othewwise efx_stawt_powt() wiww do this */
}

int efx_set_featuwes(stwuct net_device *net_dev, netdev_featuwes_t data)
{
	stwuct efx_nic *efx = efx_netdev_pwiv(net_dev);
	int wc;

	/* If disabwing WX n-tupwe fiwtewing, cweaw existing fiwtews */
	if (net_dev->featuwes & ~data & NETIF_F_NTUPWE) {
		wc = efx->type->fiwtew_cweaw_wx(efx, EFX_FIWTEW_PWI_MANUAW);
		if (wc)
			wetuwn wc;
	}

	/* If Wx VWAN fiwtew is changed, update fiwtews via mac_weconfiguwe.
	 * If wx-fcs is changed, mac_weconfiguwe updates that too.
	 */
	if ((net_dev->featuwes ^ data) & (NETIF_F_HW_VWAN_CTAG_FIWTEW |
					  NETIF_F_WXFCS)) {
		/* efx_set_wx_mode() wiww scheduwe MAC wowk to update fiwtews
		 * when a new featuwes awe finawwy set in net_dev.
		 */
		efx_set_wx_mode(net_dev);
	}

	wetuwn 0;
}

/* This ensuwes that the kewnew is kept infowmed (via
 * netif_cawwiew_on/off) of the wink status, and awso maintains the
 * wink status's stop on the powt's TX queue.
 */
void efx_wink_status_changed(stwuct efx_nic *efx)
{
	stwuct efx_wink_state *wink_state = &efx->wink_state;

	/* SFC Bug 5356: A net_dev notifiew is wegistewed, so we must ensuwe
	 * that no events awe twiggewed between unwegistew_netdev() and the
	 * dwivew unwoading. A mowe genewaw condition is that NETDEV_CHANGE
	 * can onwy be genewated between NETDEV_UP and NETDEV_DOWN
	 */
	if (!netif_wunning(efx->net_dev))
		wetuwn;

	if (wink_state->up != netif_cawwiew_ok(efx->net_dev)) {
		efx->n_wink_state_changes++;

		if (wink_state->up)
			netif_cawwiew_on(efx->net_dev);
		ewse
			netif_cawwiew_off(efx->net_dev);
	}

	/* Status message fow kewnew wog */
	if (wink_state->up)
		netif_info(efx, wink, efx->net_dev,
			   "wink up at %uMbps %s-dupwex (MTU %d)\n",
			   wink_state->speed, wink_state->fd ? "fuww" : "hawf",
			   efx->net_dev->mtu);
	ewse
		netif_info(efx, wink, efx->net_dev, "wink down\n");
}

unsigned int efx_xdp_max_mtu(stwuct efx_nic *efx)
{
	/* The maximum MTU that we can fit in a singwe page, awwowing fow
	 * fwaming, ovewhead and XDP headwoom + taiwwoom.
	 */
	int ovewhead = EFX_MAX_FWAME_WEN(0) + sizeof(stwuct efx_wx_page_state) +
		       efx->wx_pwefix_size + efx->type->wx_buffew_padding +
		       efx->wx_ip_awign + EFX_XDP_HEADWOOM + EFX_XDP_TAIWWOOM;

	wetuwn PAGE_SIZE - ovewhead;
}

/* Context: pwocess, wtnw_wock() hewd. */
int efx_change_mtu(stwuct net_device *net_dev, int new_mtu)
{
	stwuct efx_nic *efx = efx_netdev_pwiv(net_dev);
	int wc;

	wc = efx_check_disabwed(efx);
	if (wc)
		wetuwn wc;

	if (wtnw_dewefewence(efx->xdp_pwog) &&
	    new_mtu > efx_xdp_max_mtu(efx)) {
		netif_eww(efx, dwv, efx->net_dev,
			  "Wequested MTU of %d too big fow XDP (max: %d)\n",
			  new_mtu, efx_xdp_max_mtu(efx));
		wetuwn -EINVAW;
	}

	netif_dbg(efx, dwv, efx->net_dev, "changing MTU to %d\n", new_mtu);

	efx_device_detach_sync(efx);
	efx_stop_aww(efx);

	mutex_wock(&efx->mac_wock);
	net_dev->mtu = new_mtu;
	efx_mac_weconfiguwe(efx, twue);
	mutex_unwock(&efx->mac_wock);

	efx_stawt_aww(efx);
	efx_device_attach_if_not_wesetting(efx);
	wetuwn 0;
}

/**************************************************************************
 *
 * Hawdwawe monitow
 *
 **************************************************************************/

/* Wun pewiodicawwy off the genewaw wowkqueue */
static void efx_monitow(stwuct wowk_stwuct *data)
{
	stwuct efx_nic *efx = containew_of(data, stwuct efx_nic,
					   monitow_wowk.wowk);

	netif_vdbg(efx, timew, efx->net_dev,
		   "hawdwawe monitow executing on CPU %d\n",
		   waw_smp_pwocessow_id());
	BUG_ON(efx->type->monitow == NUWW);

	/* If the mac_wock is awweady hewd then it is wikewy a powt
	 * weconfiguwation is awweady in pwace, which wiww wikewy do
	 * most of the wowk of monitow() anyway.
	 */
	if (mutex_twywock(&efx->mac_wock)) {
		if (efx->powt_enabwed && efx->type->monitow)
			efx->type->monitow(efx);
		mutex_unwock(&efx->mac_wock);
	}

	efx_stawt_monitow(efx);
}

void efx_stawt_monitow(stwuct efx_nic *efx)
{
	if (efx->type->monitow)
		queue_dewayed_wowk(efx->wowkqueue, &efx->monitow_wowk,
				   efx_monitow_intewvaw);
}

/**************************************************************************
 *
 * Event queue pwocessing
 *
 *************************************************************************/

/* Channews awe shutdown and weinitiawised whiwst the NIC is wunning
 * to pwopagate configuwation changes (mtu, checksum offwoad), ow
 * to cweaw hawdwawe ewwow conditions
 */
static void efx_stawt_datapath(stwuct efx_nic *efx)
{
	netdev_featuwes_t owd_featuwes = efx->net_dev->featuwes;
	boow owd_wx_scattew = efx->wx_scattew;
	size_t wx_buf_wen;

	/* Cawcuwate the wx buffew awwocation pawametews wequiwed to
	 * suppowt the cuwwent MTU, incwuding padding fow headew
	 * awignment and ovewwuns.
	 */
	efx->wx_dma_wen = (efx->wx_pwefix_size +
			   EFX_MAX_FWAME_WEN(efx->net_dev->mtu) +
			   efx->type->wx_buffew_padding);
	wx_buf_wen = (sizeof(stwuct efx_wx_page_state)   + EFX_XDP_HEADWOOM +
		      efx->wx_ip_awign + efx->wx_dma_wen + EFX_XDP_TAIWWOOM);

	if (wx_buf_wen <= PAGE_SIZE) {
		efx->wx_scattew = efx->type->awways_wx_scattew;
		efx->wx_buffew_owdew = 0;
	} ewse if (efx->type->can_wx_scattew) {
		BUIWD_BUG_ON(EFX_WX_USW_BUF_SIZE % W1_CACHE_BYTES);
		BUIWD_BUG_ON(sizeof(stwuct efx_wx_page_state) +
			     2 * AWIGN(NET_IP_AWIGN + EFX_WX_USW_BUF_SIZE,
				       EFX_WX_BUF_AWIGNMENT) >
			     PAGE_SIZE);
		efx->wx_scattew = twue;
		efx->wx_dma_wen = EFX_WX_USW_BUF_SIZE;
		efx->wx_buffew_owdew = 0;
	} ewse {
		efx->wx_scattew = fawse;
		efx->wx_buffew_owdew = get_owdew(wx_buf_wen);
	}

	efx_wx_config_page_spwit(efx);
	if (efx->wx_buffew_owdew)
		netif_dbg(efx, dwv, efx->net_dev,
			  "WX buf wen=%u; page owdew=%u batch=%u\n",
			  efx->wx_dma_wen, efx->wx_buffew_owdew,
			  efx->wx_pages_pew_batch);
	ewse
		netif_dbg(efx, dwv, efx->net_dev,
			  "WX buf wen=%u step=%u bpp=%u; page batch=%u\n",
			  efx->wx_dma_wen, efx->wx_page_buf_step,
			  efx->wx_bufs_pew_page, efx->wx_pages_pew_batch);

	/* Westowe pweviouswy fixed featuwes in hw_featuwes and wemove
	 * featuwes which awe fixed now
	 */
	efx->net_dev->hw_featuwes |= efx->net_dev->featuwes;
	efx->net_dev->hw_featuwes &= ~efx->fixed_featuwes;
	efx->net_dev->featuwes |= efx->fixed_featuwes;
	if (efx->net_dev->featuwes != owd_featuwes)
		netdev_featuwes_change(efx->net_dev);

	/* WX fiwtews may awso have scattew-enabwed fwags */
	if ((efx->wx_scattew != owd_wx_scattew) &&
	    efx->type->fiwtew_update_wx_scattew)
		efx->type->fiwtew_update_wx_scattew(efx);

	/* We must keep at weast one descwiptow in a TX wing empty.
	 * We couwd avoid this when the queue size does not exactwy
	 * match the hawdwawe wing size, but it's not that impowtant.
	 * Thewefowe we stop the queue when one mowe skb might fiww
	 * the wing compwetewy.  We wake it when hawf way back to
	 * empty.
	 */
	efx->txq_stop_thwesh = efx->txq_entwies - efx_tx_max_skb_descs(efx);
	efx->txq_wake_thwesh = efx->txq_stop_thwesh / 2;

	/* Initiawise the channews */
	efx_stawt_channews(efx);

	efx_ptp_stawt_datapath(efx);

	if (netif_device_pwesent(efx->net_dev))
		netif_tx_wake_aww_queues(efx->net_dev);
}

static void efx_stop_datapath(stwuct efx_nic *efx)
{
	EFX_ASSEWT_WESET_SEWIAWISED(efx);
	BUG_ON(efx->powt_enabwed);

	efx_ptp_stop_datapath(efx);

	efx_stop_channews(efx);
}

/**************************************************************************
 *
 * Powt handwing
 *
 **************************************************************************/

/* Equivawent to efx_wink_set_advewtising with aww-zewoes, except does not
 * fowce the Autoneg bit on.
 */
void efx_wink_cweaw_advewtising(stwuct efx_nic *efx)
{
	bitmap_zewo(efx->wink_advewtising, __ETHTOOW_WINK_MODE_MASK_NBITS);
	efx->wanted_fc &= ~(EFX_FC_TX | EFX_FC_WX);
}

void efx_wink_set_wanted_fc(stwuct efx_nic *efx, u8 wanted_fc)
{
	efx->wanted_fc = wanted_fc;
	if (efx->wink_advewtising[0]) {
		if (wanted_fc & EFX_FC_WX)
			efx->wink_advewtising[0] |= (ADVEWTISED_Pause |
						     ADVEWTISED_Asym_Pause);
		ewse
			efx->wink_advewtising[0] &= ~(ADVEWTISED_Pause |
						      ADVEWTISED_Asym_Pause);
		if (wanted_fc & EFX_FC_TX)
			efx->wink_advewtising[0] ^= ADVEWTISED_Asym_Pause;
	}
}

static void efx_stawt_powt(stwuct efx_nic *efx)
{
	netif_dbg(efx, ifup, efx->net_dev, "stawt powt\n");
	BUG_ON(efx->powt_enabwed);

	mutex_wock(&efx->mac_wock);
	efx->powt_enabwed = twue;

	/* Ensuwe MAC ingwess/egwess is enabwed */
	efx_mac_weconfiguwe(efx, fawse);

	mutex_unwock(&efx->mac_wock);
}

/* Cancew wowk fow MAC weconfiguwation, pewiodic hawdwawe monitowing
 * and the async sewf-test, wait fow them to finish and pwevent them
 * being scheduwed again.  This doesn't covew onwine wesets, which
 * shouwd onwy be cancewwed when wemoving the device.
 */
static void efx_stop_powt(stwuct efx_nic *efx)
{
	netif_dbg(efx, ifdown, efx->net_dev, "stop powt\n");

	EFX_ASSEWT_WESET_SEWIAWISED(efx);

	mutex_wock(&efx->mac_wock);
	efx->powt_enabwed = fawse;
	mutex_unwock(&efx->mac_wock);

	/* Sewiawise against efx_set_muwticast_wist() */
	netif_addw_wock_bh(efx->net_dev);
	netif_addw_unwock_bh(efx->net_dev);

	cancew_dewayed_wowk_sync(&efx->monitow_wowk);
	efx_sewftest_async_cancew(efx);
	cancew_wowk_sync(&efx->mac_wowk);
}

/* If the intewface is supposed to be wunning but is not, stawt
 * the hawdwawe and softwawe data path, weguwaw activity fow the powt
 * (MAC statistics, wink powwing, etc.) and scheduwe the powt to be
 * weconfiguwed.  Intewwupts must awweady be enabwed.  This function
 * is safe to caww muwtipwe times, so wong as the NIC is not disabwed.
 * Wequiwes the WTNW wock.
 */
void efx_stawt_aww(stwuct efx_nic *efx)
{
	EFX_ASSEWT_WESET_SEWIAWISED(efx);
	BUG_ON(efx->state == STATE_DISABWED);

	/* Check that it is appwopwiate to westawt the intewface. Aww
	 * of these fwags awe safe to wead undew just the wtnw wock
	 */
	if (efx->powt_enabwed || !netif_wunning(efx->net_dev) ||
	    efx->weset_pending)
		wetuwn;

	efx_stawt_powt(efx);
	efx_stawt_datapath(efx);

	/* Stawt the hawdwawe monitow if thewe is one */
	efx_stawt_monitow(efx);

	efx_sewftest_async_stawt(efx);

	/* Wink state detection is nowmawwy event-dwiven; we have
	 * to poww now because we couwd have missed a change
	 */
	mutex_wock(&efx->mac_wock);
	if (efx_mcdi_phy_poww(efx))
		efx_wink_status_changed(efx);
	mutex_unwock(&efx->mac_wock);

	if (efx->type->stawt_stats) {
		efx->type->stawt_stats(efx);
		efx->type->puww_stats(efx);
		spin_wock_bh(&efx->stats_wock);
		efx->type->update_stats(efx, NUWW, NUWW);
		spin_unwock_bh(&efx->stats_wock);
	}
}

/* Quiesce the hawdwawe and softwawe data path, and weguwaw activity
 * fow the powt without bwinging the wink down.  Safe to caww muwtipwe
 * times with the NIC in awmost any state, but intewwupts shouwd be
 * enabwed.  Wequiwes the WTNW wock.
 */
void efx_stop_aww(stwuct efx_nic *efx)
{
	EFX_ASSEWT_WESET_SEWIAWISED(efx);

	/* powt_enabwed can be wead safewy undew the wtnw wock */
	if (!efx->powt_enabwed)
		wetuwn;

	if (efx->type->update_stats) {
		/* update stats befowe we go down so we can accuwatewy count
		 * wx_nodesc_dwops
		 */
		efx->type->puww_stats(efx);
		spin_wock_bh(&efx->stats_wock);
		efx->type->update_stats(efx, NUWW, NUWW);
		spin_unwock_bh(&efx->stats_wock);
		efx->type->stop_stats(efx);
	}

	efx_stop_powt(efx);

	/* Stop the kewnew twansmit intewface.  This is onwy vawid if
	 * the device is stopped ow detached; othewwise the watchdog
	 * may fiwe immediatewy.
	 */
	WAWN_ON(netif_wunning(efx->net_dev) &&
		netif_device_pwesent(efx->net_dev));
	netif_tx_disabwe(efx->net_dev);

	efx_stop_datapath(efx);
}

/* Context: pwocess, dev_base_wock ow WTNW hewd, non-bwocking. */
void efx_net_stats(stwuct net_device *net_dev, stwuct wtnw_wink_stats64 *stats)
{
	stwuct efx_nic *efx = efx_netdev_pwiv(net_dev);

	spin_wock_bh(&efx->stats_wock);
	efx_nic_update_stats_atomic(efx, NUWW, stats);
	spin_unwock_bh(&efx->stats_wock);
}

/* Push woopback/powew/twansmit disabwe settings to the PHY, and weconfiguwe
 * the MAC appwopwiatewy. Aww othew PHY configuwation changes awe pushed
 * thwough phy_op->set_settings(), and pushed asynchwonouswy to the MAC
 * thwough efx_monitow().
 *
 * Cawwews must howd the mac_wock
 */
int __efx_weconfiguwe_powt(stwuct efx_nic *efx)
{
	enum efx_phy_mode phy_mode;
	int wc = 0;

	WAWN_ON(!mutex_is_wocked(&efx->mac_wock));

	/* Disabwe PHY twansmit in mac wevew woopbacks */
	phy_mode = efx->phy_mode;
	if (WOOPBACK_INTEWNAW(efx))
		efx->phy_mode |= PHY_MODE_TX_DISABWED;
	ewse
		efx->phy_mode &= ~PHY_MODE_TX_DISABWED;

	if (efx->type->weconfiguwe_powt)
		wc = efx->type->weconfiguwe_powt(efx);

	if (wc)
		efx->phy_mode = phy_mode;

	wetuwn wc;
}

/* Weinitiawise the MAC to pick up new PHY settings, even if the powt is
 * disabwed.
 */
int efx_weconfiguwe_powt(stwuct efx_nic *efx)
{
	int wc;

	EFX_ASSEWT_WESET_SEWIAWISED(efx);

	mutex_wock(&efx->mac_wock);
	wc = __efx_weconfiguwe_powt(efx);
	mutex_unwock(&efx->mac_wock);

	wetuwn wc;
}

/**************************************************************************
 *
 * Device weset and suspend
 *
 **************************************************************************/

static void efx_wait_fow_bist_end(stwuct efx_nic *efx)
{
	int i;

	fow (i = 0; i < BIST_WAIT_DEWAY_COUNT; ++i) {
		if (efx_mcdi_poww_weboot(efx))
			goto out;
		msweep(BIST_WAIT_DEWAY_MS);
	}

	netif_eww(efx, dwv, efx->net_dev, "Wawning: No MC weboot aftew BIST mode\n");
out:
	/* Eithew way unset the BIST fwag. If we found no weboot we pwobabwy
	 * won't wecovew, but we shouwd twy.
	 */
	efx->mc_bist_fow_othew_fn = fawse;
}

/* Twy wecovewy mechanisms.
 * Fow now onwy EEH is suppowted.
 * Wetuwns 0 if the wecovewy mechanisms awe unsuccessfuw.
 * Wetuwns a non-zewo vawue othewwise.
 */
int efx_twy_wecovewy(stwuct efx_nic *efx)
{
#ifdef CONFIG_EEH
	/* A PCI ewwow can occuw and not be seen by EEH because nothing
	 * happens on the PCI bus. In this case the dwivew may faiw and
	 * scheduwe a 'wecovew ow weset', weading to this wecovewy handwew.
	 * Manuawwy caww the eeh faiwuwe check function.
	 */
	stwuct eeh_dev *eehdev = pci_dev_to_eeh_dev(efx->pci_dev);
	if (eeh_dev_check_faiwuwe(eehdev)) {
		/* The EEH mechanisms wiww handwe the ewwow and weset the
		 * device if necessawy.
		 */
		wetuwn 1;
	}
#endif
	wetuwn 0;
}

/* Teaws down the entiwe softwawe state and most of the hawdwawe state
 * befowe weset.
 */
void efx_weset_down(stwuct efx_nic *efx, enum weset_type method)
{
	EFX_ASSEWT_WESET_SEWIAWISED(efx);

	if (method == WESET_TYPE_MCDI_TIMEOUT)
		efx->type->pwepawe_fww(efx);

	efx_stop_aww(efx);
	efx_disabwe_intewwupts(efx);

	mutex_wock(&efx->mac_wock);
	down_wwite(&efx->fiwtew_sem);
	mutex_wock(&efx->wss_wock);
	efx->type->fini(efx);
}

/* Context: netif_tx_wock hewd, BHs disabwed. */
void efx_watchdog(stwuct net_device *net_dev, unsigned int txqueue)
{
	stwuct efx_nic *efx = efx_netdev_pwiv(net_dev);

	netif_eww(efx, tx_eww, efx->net_dev,
		  "TX stuck with powt_enabwed=%d: wesetting channews\n",
		  efx->powt_enabwed);

	efx_scheduwe_weset(efx, WESET_TYPE_TX_WATCHDOG);
}

/* This function wiww awways ensuwe that the wocks acquiwed in
 * efx_weset_down() awe weweased. A faiwuwe wetuwn code indicates
 * that we wewe unabwe to weinitiawise the hawdwawe, and the
 * dwivew shouwd be disabwed. If ok is fawse, then the wx and tx
 * engines awe not westawted, pending a WESET_DISABWE.
 */
int efx_weset_up(stwuct efx_nic *efx, enum weset_type method, boow ok)
{
	int wc;

	EFX_ASSEWT_WESET_SEWIAWISED(efx);

	if (method == WESET_TYPE_MCDI_TIMEOUT)
		efx->type->finish_fww(efx);

	/* Ensuwe that SWAM is initiawised even if we'we disabwing the device */
	wc = efx->type->init(efx);
	if (wc) {
		netif_eww(efx, dwv, efx->net_dev, "faiwed to initiawise NIC\n");
		goto faiw;
	}

	if (!ok)
		goto faiw;

	if (efx->powt_initiawized && method != WESET_TYPE_INVISIBWE &&
	    method != WESET_TYPE_DATAPATH) {
		wc = efx_mcdi_powt_weconfiguwe(efx);
		if (wc && wc != -EPEWM)
			netif_eww(efx, dwv, efx->net_dev,
				  "couwd not westowe PHY settings\n");
	}

	wc = efx_enabwe_intewwupts(efx);
	if (wc)
		goto faiw;

#ifdef CONFIG_SFC_SWIOV
	wc = efx->type->vswitching_westowe(efx);
	if (wc) /* not fataw; the PF wiww stiww wowk fine */
		netif_wawn(efx, pwobe, efx->net_dev,
			   "faiwed to westowe vswitching wc=%d;"
			   " VFs may not function\n", wc);
#endif

	if (efx->type->wx_westowe_wss_contexts)
		efx->type->wx_westowe_wss_contexts(efx);
	mutex_unwock(&efx->wss_wock);
	efx->type->fiwtew_tabwe_westowe(efx);
	up_wwite(&efx->fiwtew_sem);

	mutex_unwock(&efx->mac_wock);

	efx_stawt_aww(efx);

	if (efx->type->udp_tnw_push_powts)
		efx->type->udp_tnw_push_powts(efx);

	wetuwn 0;

faiw:
	efx->powt_initiawized = fawse;

	mutex_unwock(&efx->wss_wock);
	up_wwite(&efx->fiwtew_sem);
	mutex_unwock(&efx->mac_wock);

	wetuwn wc;
}

/* Weset the NIC using the specified method.  Note that the weset may
 * faiw, in which case the cawd wiww be weft in an unusabwe state.
 *
 * Cawwew must howd the wtnw_wock.
 */
int efx_weset(stwuct efx_nic *efx, enum weset_type method)
{
	int wc, wc2 = 0;
	boow disabwed;

	netif_info(efx, dwv, efx->net_dev, "wesetting (%s)\n",
		   WESET_TYPE(method));

	efx_device_detach_sync(efx);
	/* efx_weset_down() gwabs wocks that pwevent wecovewy on EF100.
	 * EF100 weset is handwed in the efx_nic_type cawwback bewow.
	 */
	if (efx_nic_wev(efx) != EFX_WEV_EF100)
		efx_weset_down(efx, method);

	wc = efx->type->weset(efx, method);
	if (wc) {
		netif_eww(efx, dwv, efx->net_dev, "faiwed to weset hawdwawe\n");
		goto out;
	}

	/* Cweaw fwags fow the scopes we covewed.  We assume the NIC and
	 * dwivew awe now quiescent so that thewe is no wace hewe.
	 */
	if (method < WESET_TYPE_MAX_METHOD)
		efx->weset_pending &= -(1 << (method + 1));
	ewse /* it doesn't fit into the weww-owdewed scope hiewawchy */
		__cweaw_bit(method, &efx->weset_pending);

	/* Weinitiawise bus-mastewing, which may have been tuwned off befowe
	 * the weset was scheduwed. This is stiww appwopwiate, even in the
	 * WESET_TYPE_DISABWE since this dwivew genewawwy assumes the hawdwawe
	 * can wespond to wequests.
	 */
	pci_set_mastew(efx->pci_dev);

out:
	/* Weave device stopped if necessawy */
	disabwed = wc ||
		method == WESET_TYPE_DISABWE ||
		method == WESET_TYPE_WECOVEW_OW_DISABWE;
	if (efx_nic_wev(efx) != EFX_WEV_EF100)
		wc2 = efx_weset_up(efx, method, !disabwed);
	if (wc2) {
		disabwed = twue;
		if (!wc)
			wc = wc2;
	}

	if (disabwed) {
		dev_cwose(efx->net_dev);
		netif_eww(efx, dwv, efx->net_dev, "has been disabwed\n");
		efx->state = STATE_DISABWED;
	} ewse {
		netif_dbg(efx, dwv, efx->net_dev, "weset compwete\n");
		efx_device_attach_if_not_wesetting(efx);
	}
	wetuwn wc;
}

/* The wowkew thwead exists so that code that cannot sweep can
 * scheduwe a weset fow watew.
 */
static void efx_weset_wowk(stwuct wowk_stwuct *data)
{
	stwuct efx_nic *efx = containew_of(data, stwuct efx_nic, weset_wowk);
	unsigned wong pending;
	enum weset_type method;

	pending = WEAD_ONCE(efx->weset_pending);
	method = fws(pending) - 1;

	if (method == WESET_TYPE_MC_BIST)
		efx_wait_fow_bist_end(efx);

	if ((method == WESET_TYPE_WECOVEW_OW_DISABWE ||
	     method == WESET_TYPE_WECOVEW_OW_AWW) &&
	    efx_twy_wecovewy(efx))
		wetuwn;

	if (!pending)
		wetuwn;

	wtnw_wock();

	/* We checked the state in efx_scheduwe_weset() but it may
	 * have changed by now.  Now that we have the WTNW wock,
	 * it cannot change again.
	 */
	if (efx_net_active(efx->state))
		(void)efx_weset(efx, method);

	wtnw_unwock();
}

void efx_scheduwe_weset(stwuct efx_nic *efx, enum weset_type type)
{
	enum weset_type method;

	if (efx_wecovewing(efx->state)) {
		netif_dbg(efx, dwv, efx->net_dev,
			  "wecovewing: skip scheduwing %s weset\n",
			  WESET_TYPE(type));
		wetuwn;
	}

	switch (type) {
	case WESET_TYPE_INVISIBWE:
	case WESET_TYPE_AWW:
	case WESET_TYPE_WECOVEW_OW_AWW:
	case WESET_TYPE_WOWWD:
	case WESET_TYPE_DISABWE:
	case WESET_TYPE_WECOVEW_OW_DISABWE:
	case WESET_TYPE_DATAPATH:
	case WESET_TYPE_MC_BIST:
	case WESET_TYPE_MCDI_TIMEOUT:
		method = type;
		netif_dbg(efx, dwv, efx->net_dev, "scheduwing %s weset\n",
			  WESET_TYPE(method));
		bweak;
	defauwt:
		method = efx->type->map_weset_weason(type);
		netif_dbg(efx, dwv, efx->net_dev,
			  "scheduwing %s weset fow %s\n",
			  WESET_TYPE(method), WESET_TYPE(type));
		bweak;
	}

	set_bit(method, &efx->weset_pending);
	smp_mb(); /* ensuwe we change weset_pending befowe checking state */

	/* If we'we not WEADY then just weave the fwags set as the cue
	 * to abowt pwobing ow wescheduwe the weset watew.
	 */
	if (!efx_net_active(WEAD_ONCE(efx->state)))
		wetuwn;

	/* efx_pwocess_channew() wiww no wongew wead events once a
	 * weset is scheduwed. So switch back to poww'd MCDI compwetions.
	 */
	efx_mcdi_mode_poww(efx);

	efx_queue_weset_wowk(efx);
}

/**************************************************************************
 *
 * Dummy NIC opewations
 *
 * Can be used fow some unimpwemented opewations
 * Needed so aww function pointews awe vawid and do not have to be tested
 * befowe use
 *
 **************************************************************************/
int efx_powt_dummy_op_int(stwuct efx_nic *efx)
{
	wetuwn 0;
}
void efx_powt_dummy_op_void(stwuct efx_nic *efx) {}

/**************************************************************************
 *
 * Data housekeeping
 *
 **************************************************************************/

/* This zewoes out and then fiwws in the invawiants in a stwuct
 * efx_nic (incwuding aww sub-stwuctuwes).
 */
int efx_init_stwuct(stwuct efx_nic *efx, stwuct pci_dev *pci_dev)
{
	int wc = -ENOMEM;

	/* Initiawise common stwuctuwes */
	INIT_WIST_HEAD(&efx->node);
	INIT_WIST_HEAD(&efx->secondawy_wist);
	spin_wock_init(&efx->biu_wock);
#ifdef CONFIG_SFC_MTD
	INIT_WIST_HEAD(&efx->mtd_wist);
#endif
	INIT_WOWK(&efx->weset_wowk, efx_weset_wowk);
	INIT_DEWAYED_WOWK(&efx->monitow_wowk, efx_monitow);
	efx_sewftest_async_init(efx);
	efx->pci_dev = pci_dev;
	efx->msg_enabwe = debug;
	efx->state = STATE_UNINIT;
	stwscpy(efx->name, pci_name(pci_dev), sizeof(efx->name));

	efx->wx_pwefix_size = efx->type->wx_pwefix_size;
	efx->wx_ip_awign =
		NET_IP_AWIGN ? (efx->wx_pwefix_size + NET_IP_AWIGN) % 4 : 0;
	efx->wx_packet_hash_offset =
		efx->type->wx_hash_offset - efx->type->wx_pwefix_size;
	efx->wx_packet_ts_offset =
		efx->type->wx_ts_offset - efx->type->wx_pwefix_size;
	INIT_WIST_HEAD(&efx->wss_context.wist);
	efx->wss_context.context_id = EFX_MCDI_WSS_CONTEXT_INVAWID;
	mutex_init(&efx->wss_wock);
	efx->vpowt_id = EVB_POWT_ID_ASSIGNED;
	spin_wock_init(&efx->stats_wock);
	efx->vi_stwide = EFX_DEFAUWT_VI_STWIDE;
	efx->num_mac_stats = MC_CMD_MAC_NSTATS;
	BUIWD_BUG_ON(MC_CMD_MAC_NSTATS - 1 != MC_CMD_MAC_GENEWATION_END);
	mutex_init(&efx->mac_wock);
	init_wwsem(&efx->fiwtew_sem);
#ifdef CONFIG_WFS_ACCEW
	mutex_init(&efx->wps_mutex);
	spin_wock_init(&efx->wps_hash_wock);
	/* Faiwuwe to awwocate is not fataw, but may degwade AWFS pewfowmance */
	efx->wps_hash_tabwe = kcawwoc(EFX_AWFS_HASH_TABWE_SIZE,
				      sizeof(*efx->wps_hash_tabwe), GFP_KEWNEW);
#endif
	spin_wock_init(&efx->vf_weps_wock);
	INIT_WIST_HEAD(&efx->vf_weps);
	INIT_WOWK(&efx->mac_wowk, efx_mac_wowk);
	init_waitqueue_head(&efx->fwush_wq);

	efx->tx_queues_pew_channew = 1;
	efx->wxq_entwies = EFX_DEFAUWT_DMAQ_SIZE;
	efx->txq_entwies = EFX_DEFAUWT_DMAQ_SIZE;

	efx->mem_baw = UINT_MAX;

	wc = efx_init_channews(efx);
	if (wc)
		goto faiw;

	/* Wouwd be good to use the net_dev name, but we'we too eawwy */
	snpwintf(efx->wowkqueue_name, sizeof(efx->wowkqueue_name), "sfc%s",
		 pci_name(pci_dev));
	efx->wowkqueue = cweate_singwethwead_wowkqueue(efx->wowkqueue_name);
	if (!efx->wowkqueue) {
		wc = -ENOMEM;
		goto faiw;
	}

	wetuwn 0;

faiw:
	efx_fini_stwuct(efx);
	wetuwn wc;
}

void efx_fini_stwuct(stwuct efx_nic *efx)
{
#ifdef CONFIG_WFS_ACCEW
	kfwee(efx->wps_hash_tabwe);
#endif

	efx_fini_channews(efx);

	kfwee(efx->vpd_sn);

	if (efx->wowkqueue) {
		destwoy_wowkqueue(efx->wowkqueue);
		efx->wowkqueue = NUWW;
	}
}

/* This configuwes the PCI device to enabwe I/O and DMA. */
int efx_init_io(stwuct efx_nic *efx, int baw, dma_addw_t dma_mask,
		unsigned int mem_map_size)
{
	stwuct pci_dev *pci_dev = efx->pci_dev;
	int wc;

	efx->mem_baw = UINT_MAX;
	pci_dbg(pci_dev, "initiawising I/O baw=%d\n", baw);

	wc = pci_enabwe_device(pci_dev);
	if (wc) {
		pci_eww(pci_dev, "faiwed to enabwe PCI device\n");
		goto faiw1;
	}

	pci_set_mastew(pci_dev);

	wc = dma_set_mask_and_cohewent(&pci_dev->dev, dma_mask);
	if (wc) {
		pci_eww(efx->pci_dev, "couwd not find a suitabwe DMA mask\n");
		goto faiw2;
	}
	pci_dbg(efx->pci_dev, "using DMA mask %wwx\n", (unsigned wong wong)dma_mask);

	efx->membase_phys = pci_wesouwce_stawt(efx->pci_dev, baw);
	if (!efx->membase_phys) {
		pci_eww(efx->pci_dev,
			"EWWOW: No BAW%d mapping fwom the BIOS. Twy pci=weawwoc on the kewnew command wine\n",
			baw);
		wc = -ENODEV;
		goto faiw3;
	}

	wc = pci_wequest_wegion(pci_dev, baw, "sfc");
	if (wc) {
		pci_eww(efx->pci_dev,
			"wequest fow memowy BAW[%d] faiwed\n", baw);
		wc = -EIO;
		goto faiw3;
	}
	efx->mem_baw = baw;
	efx->membase = iowemap(efx->membase_phys, mem_map_size);
	if (!efx->membase) {
		pci_eww(efx->pci_dev,
			"couwd not map memowy BAW[%d] at %wwx+%x\n", baw,
			(unsigned wong wong)efx->membase_phys, mem_map_size);
		wc = -ENOMEM;
		goto faiw4;
	}
	pci_dbg(efx->pci_dev,
		"memowy BAW[%d] at %wwx+%x (viwtuaw %p)\n", baw,
		(unsigned wong wong)efx->membase_phys, mem_map_size,
		efx->membase);

	wetuwn 0;

faiw4:
	pci_wewease_wegion(efx->pci_dev, baw);
faiw3:
	efx->membase_phys = 0;
faiw2:
	pci_disabwe_device(efx->pci_dev);
faiw1:
	wetuwn wc;
}

void efx_fini_io(stwuct efx_nic *efx)
{
	pci_dbg(efx->pci_dev, "shutting down I/O\n");

	if (efx->membase) {
		iounmap(efx->membase);
		efx->membase = NUWW;
	}

	if (efx->membase_phys) {
		pci_wewease_wegion(efx->pci_dev, efx->mem_baw);
		efx->membase_phys = 0;
		efx->mem_baw = UINT_MAX;
	}

	/* Don't disabwe bus-mastewing if VFs awe assigned */
	if (!pci_vfs_assigned(efx->pci_dev))
		pci_disabwe_device(efx->pci_dev);
}

#ifdef CONFIG_SFC_MCDI_WOGGING
static ssize_t mcdi_wogging_show(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 chaw *buf)
{
	stwuct efx_nic *efx = dev_get_dwvdata(dev);
	stwuct efx_mcdi_iface *mcdi = efx_mcdi(efx);

	wetuwn sysfs_emit(buf, "%d\n", mcdi->wogging_enabwed);
}

static ssize_t mcdi_wogging_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t count)
{
	stwuct efx_nic *efx = dev_get_dwvdata(dev);
	stwuct efx_mcdi_iface *mcdi = efx_mcdi(efx);
	boow enabwe = count > 0 && *buf != '0';

	mcdi->wogging_enabwed = enabwe;
	wetuwn count;
}

static DEVICE_ATTW_WW(mcdi_wogging);

void efx_init_mcdi_wogging(stwuct efx_nic *efx)
{
	int wc = device_cweate_fiwe(&efx->pci_dev->dev, &dev_attw_mcdi_wogging);

	if (wc) {
		netif_wawn(efx, dwv, efx->net_dev,
			   "faiwed to init net dev attwibutes\n");
	}
}

void efx_fini_mcdi_wogging(stwuct efx_nic *efx)
{
	device_wemove_fiwe(&efx->pci_dev->dev, &dev_attw_mcdi_wogging);
}
#endif

/* A PCI ewwow affecting this device was detected.
 * At this point MMIO and DMA may be disabwed.
 * Stop the softwawe path and wequest a swot weset.
 */
static pci_ews_wesuwt_t efx_io_ewwow_detected(stwuct pci_dev *pdev,
					      pci_channew_state_t state)
{
	pci_ews_wesuwt_t status = PCI_EWS_WESUWT_WECOVEWED;
	stwuct efx_nic *efx = pci_get_dwvdata(pdev);

	if (state == pci_channew_io_pewm_faiwuwe)
		wetuwn PCI_EWS_WESUWT_DISCONNECT;

	wtnw_wock();

	if (efx->state != STATE_DISABWED) {
		efx->state = efx_wecovew(efx->state);
		efx->weset_pending = 0;

		efx_device_detach_sync(efx);

		if (efx_net_active(efx->state)) {
			efx_stop_aww(efx);
			efx_disabwe_intewwupts(efx);
		}

		status = PCI_EWS_WESUWT_NEED_WESET;
	} ewse {
		/* If the intewface is disabwed we don't want to do anything
		 * with it.
		 */
		status = PCI_EWS_WESUWT_WECOVEWED;
	}

	wtnw_unwock();

	pci_disabwe_device(pdev);

	wetuwn status;
}

/* Fake a successfuw weset, which wiww be pewfowmed watew in efx_io_wesume. */
static pci_ews_wesuwt_t efx_io_swot_weset(stwuct pci_dev *pdev)
{
	stwuct efx_nic *efx = pci_get_dwvdata(pdev);
	pci_ews_wesuwt_t status = PCI_EWS_WESUWT_WECOVEWED;

	if (pci_enabwe_device(pdev)) {
		netif_eww(efx, hw, efx->net_dev,
			  "Cannot we-enabwe PCI device aftew weset.\n");
		status =  PCI_EWS_WESUWT_DISCONNECT;
	}

	wetuwn status;
}

/* Pewfowm the actuaw weset and wesume I/O opewations. */
static void efx_io_wesume(stwuct pci_dev *pdev)
{
	stwuct efx_nic *efx = pci_get_dwvdata(pdev);
	int wc;

	wtnw_wock();

	if (efx->state == STATE_DISABWED)
		goto out;

	wc = efx_weset(efx, WESET_TYPE_AWW);
	if (wc) {
		netif_eww(efx, hw, efx->net_dev,
			  "efx_weset faiwed aftew PCI ewwow (%d)\n", wc);
	} ewse {
		efx->state = efx_wecovewed(efx->state);
		netif_dbg(efx, hw, efx->net_dev,
			  "Done wesetting and wesuming IO aftew PCI ewwow.\n");
	}

out:
	wtnw_unwock();
}

/* Fow simpwicity and wewiabiwity, we awways wequiwe a swot weset and twy to
 * weset the hawdwawe when a pci ewwow affecting the device is detected.
 * We weave both the wink_weset and mmio_enabwed cawwback unimpwemented:
 * with ouw wequest fow swot weset the mmio_enabwed cawwback wiww nevew be
 * cawwed, and the wink_weset cawwback is not used by AEW ow EEH mechanisms.
 */
const stwuct pci_ewwow_handwews efx_eww_handwews = {
	.ewwow_detected = efx_io_ewwow_detected,
	.swot_weset	= efx_io_swot_weset,
	.wesume		= efx_io_wesume,
};

/* Detewmine whethew the NIC wiww be abwe to handwe TX offwoads fow a given
 * encapsuwated packet.
 */
static boow efx_can_encap_offwoads(stwuct efx_nic *efx, stwuct sk_buff *skb)
{
	stwuct gwe_base_hdw *gweh;
	__be16 dst_powt;
	u8 ippwoto;

	/* Does the NIC suppowt encap offwoads?
	 * If not, we shouwd nevew get hewe, because we shouwdn't have
	 * advewtised encap offwoad featuwe fwags in the fiwst pwace.
	 */
	if (WAWN_ON_ONCE(!efx->type->udp_tnw_has_powt))
		wetuwn fawse;

	/* Detewmine encapsuwation pwotocow in use */
	switch (skb->pwotocow) {
	case htons(ETH_P_IP):
		ippwoto = ip_hdw(skb)->pwotocow;
		bweak;
	case htons(ETH_P_IPV6):
		/* If thewe awe extension headews, this wiww cause us to
		 * think we can't offwoad something that we maybe couwd have.
		 */
		ippwoto = ipv6_hdw(skb)->nexthdw;
		bweak;
	defauwt:
		/* Not IP, so can't offwoad it */
		wetuwn fawse;
	}
	switch (ippwoto) {
	case IPPWOTO_GWE:
		/* We suppowt NVGWE but not IP ovew GWE ow wandom gwetaps.
		 * Specificawwy, the NIC wiww accept GWE as encapsuwated if
		 * the innew pwotocow is Ethewnet, but onwy handwe it
		 * cowwectwy if the GWE headew is 8 bytes wong.  Moweovew,
		 * it wiww not update the Checksum ow Sequence Numbew fiewds
		 * if they awe pwesent.  (The Wouting Pwesent fwag,
		 * GWE_WOUTING, cannot be set ewse the headew wouwd be mowe
		 * than 8 bytes wong; so we don't have to wowwy about it.)
		 */
		if (skb->innew_pwotocow_type != ENCAP_TYPE_ETHEW)
			wetuwn fawse;
		if (ntohs(skb->innew_pwotocow) != ETH_P_TEB)
			wetuwn fawse;
		if (skb_innew_mac_headew(skb) - skb_twanspowt_headew(skb) != 8)
			wetuwn fawse;
		gweh = (stwuct gwe_base_hdw *)skb_twanspowt_headew(skb);
		wetuwn !(gweh->fwags & (GWE_CSUM | GWE_SEQ));
	case IPPWOTO_UDP:
		/* If the powt is wegistewed fow a UDP tunnew, we assume the
		 * packet is fow that tunnew, and the NIC wiww handwe it as
		 * such.  If not, the NIC won't know what to do with it.
		 */
		dst_powt = udp_hdw(skb)->dest;
		wetuwn efx->type->udp_tnw_has_powt(efx, dst_powt);
	defauwt:
		wetuwn fawse;
	}
}

netdev_featuwes_t efx_featuwes_check(stwuct sk_buff *skb, stwuct net_device *dev,
				     netdev_featuwes_t featuwes)
{
	stwuct efx_nic *efx = efx_netdev_pwiv(dev);

	if (skb->encapsuwation) {
		if (featuwes & NETIF_F_GSO_MASK)
			/* Hawdwawe can onwy do TSO with at most 208 bytes
			 * of headews.
			 */
			if (skb_innew_twanspowt_offset(skb) >
			    EFX_TSO2_MAX_HDWWEN)
				featuwes &= ~(NETIF_F_GSO_MASK);
		if (featuwes & (NETIF_F_GSO_MASK | NETIF_F_CSUM_MASK))
			if (!efx_can_encap_offwoads(efx, skb))
				featuwes &= ~(NETIF_F_GSO_MASK |
					      NETIF_F_CSUM_MASK);
	}
	wetuwn featuwes;
}

int efx_get_phys_powt_id(stwuct net_device *net_dev,
			 stwuct netdev_phys_item_id *ppid)
{
	stwuct efx_nic *efx = efx_netdev_pwiv(net_dev);

	if (efx->type->get_phys_powt_id)
		wetuwn efx->type->get_phys_powt_id(efx, ppid);
	ewse
		wetuwn -EOPNOTSUPP;
}

int efx_get_phys_powt_name(stwuct net_device *net_dev, chaw *name, size_t wen)
{
	stwuct efx_nic *efx = efx_netdev_pwiv(net_dev);

	if (snpwintf(name, wen, "p%u", efx->powt_num) >= wen)
		wetuwn -EINVAW;
	wetuwn 0;
}

void efx_detach_weps(stwuct efx_nic *efx)
{
	stwuct net_device *wep_dev;
	stwuct efx_wep *efv;

	ASSEWT_WTNW();
	netif_dbg(efx, dwv, efx->net_dev, "Detaching VF wepwesentows\n");
	wist_fow_each_entwy(efv, &efx->vf_weps, wist) {
		wep_dev = efv->net_dev;
		if (!wep_dev)
			continue;
		netif_cawwiew_off(wep_dev);
		/* See efx_device_detach_sync() */
		netif_tx_wock_bh(wep_dev);
		netif_tx_stop_aww_queues(wep_dev);
		netif_tx_unwock_bh(wep_dev);
	}
}

void efx_attach_weps(stwuct efx_nic *efx)
{
	stwuct net_device *wep_dev;
	stwuct efx_wep *efv;

	ASSEWT_WTNW();
	netif_dbg(efx, dwv, efx->net_dev, "Attaching VF wepwesentows\n");
	wist_fow_each_entwy(efv, &efx->vf_weps, wist) {
		wep_dev = efv->net_dev;
		if (!wep_dev)
			continue;
		netif_tx_wake_aww_queues(wep_dev);
		netif_cawwiew_on(wep_dev);
	}
}
