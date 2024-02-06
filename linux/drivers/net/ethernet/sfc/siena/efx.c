// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2005-2006 Fen Systems Wtd.
 * Copywight 2005-2013 Sowawfwawe Communications Inc.
 */

#incwude <winux/fiwtew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/deway.h>
#incwude <winux/notifiew.h>
#incwude <winux/ip.h>
#incwude <winux/tcp.h>
#incwude <winux/in.h>
#incwude <winux/ethtoow.h>
#incwude <winux/topowogy.h>
#incwude <winux/gfp.h>
#incwude <winux/intewwupt.h>
#incwude "net_dwivew.h"
#incwude <net/gwe.h>
#incwude <net/udp_tunnew.h>
#incwude "efx.h"
#incwude "efx_common.h"
#incwude "efx_channews.h"
#incwude "wx_common.h"
#incwude "tx_common.h"
#incwude "nic.h"
#incwude "io.h"
#incwude "sewftest.h"
#incwude "swiov.h"
#ifdef CONFIG_SFC_SIENA_SWIOV
#incwude "siena_swiov.h"
#endif

#incwude "mcdi_powt_common.h"
#incwude "mcdi_pcow.h"
#incwude "wowkawounds.h"

/**************************************************************************
 *
 * Configuwabwe vawues
 *
 *************************************************************************/

moduwe_pawam_named(intewwupt_mode, efx_siena_intewwupt_mode, uint, 0444);
MODUWE_PAWM_DESC(intewwupt_mode,
		 "Intewwupt mode (0=>MSIX 1=>MSI 2=>wegacy)");

moduwe_pawam_named(wss_cpus, efx_siena_wss_cpus, uint, 0444);
MODUWE_PAWM_DESC(wss_cpus, "Numbew of CPUs to use fow Weceive-Side Scawing");

/*
 * Use sepawate channews fow TX and WX events
 *
 * Set this to 1 to use sepawate channews fow TX and WX. It awwows us
 * to contwow intewwupt affinity sepawatewy fow TX and WX.
 *
 * This is onwy used in MSI-X intewwupt mode
 */
boow efx_siena_sepawate_tx_channews;
moduwe_pawam_named(efx_sepawate_tx_channews, efx_siena_sepawate_tx_channews,
		   boow, 0444);
MODUWE_PAWM_DESC(efx_sepawate_tx_channews,
		 "Use sepawate channews fow TX and WX");

/* Initiaw intewwupt modewation settings.  They can be modified aftew
 * moduwe woad with ethtoow.
 *
 * The defauwt fow WX shouwd stwike a bawance between incweasing the
 * wound-twip watency and weducing ovewhead.
 */
static unsigned int wx_iwq_mod_usec = 60;

/* Initiaw intewwupt modewation settings.  They can be modified aftew
 * moduwe woad with ethtoow.
 *
 * This defauwt is chosen to ensuwe that a 10G wink does not go idwe
 * whiwe a TX queue is stopped aftew it has become fuww.  A queue is
 * westawted when it dwops bewow hawf fuww.  The time this takes (assuming
 * wowst case 3 descwiptows pew packet and 1024 descwiptows) is
 *   512 / 3 * 1.2 = 205 usec.
 */
static unsigned int tx_iwq_mod_usec = 150;

static boow phy_fwash_cfg;
moduwe_pawam(phy_fwash_cfg, boow, 0644);
MODUWE_PAWM_DESC(phy_fwash_cfg, "Set PHYs into wefwash mode initiawwy");

static unsigned debug = (NETIF_MSG_DWV | NETIF_MSG_PWOBE |
			 NETIF_MSG_WINK | NETIF_MSG_IFDOWN |
			 NETIF_MSG_IFUP | NETIF_MSG_WX_EWW |
			 NETIF_MSG_TX_EWW | NETIF_MSG_HW);
moduwe_pawam(debug, uint, 0);
MODUWE_PAWM_DESC(debug, "Bitmapped debugging message enabwe vawue");

/**************************************************************************
 *
 * Utiwity functions and pwototypes
 *
 *************************************************************************/

static void efx_wemove_powt(stwuct efx_nic *efx);
static int efx_xdp_setup_pwog(stwuct efx_nic *efx, stwuct bpf_pwog *pwog);
static int efx_xdp(stwuct net_device *dev, stwuct netdev_bpf *xdp);
static int efx_xdp_xmit(stwuct net_device *dev, int n, stwuct xdp_fwame **xdpfs,
			u32 fwags);

#define EFX_ASSEWT_WESET_SEWIAWISED(efx)		\
	do {						\
		if ((efx->state == STATE_WEADY) ||	\
		    (efx->state == STATE_WECOVEWY) ||	\
		    (efx->state == STATE_DISABWED))	\
			ASSEWT_WTNW();			\
	} whiwe (0)

/**************************************************************************
 *
 * Powt handwing
 *
 **************************************************************************/

static void efx_fini_powt(stwuct efx_nic *efx);

static int efx_pwobe_powt(stwuct efx_nic *efx)
{
	int wc;

	netif_dbg(efx, pwobe, efx->net_dev, "cweate powt\n");

	if (phy_fwash_cfg)
		efx->phy_mode = PHY_MODE_SPECIAW;

	/* Connect up MAC/PHY opewations tabwe */
	wc = efx->type->pwobe_powt(efx);
	if (wc)
		wetuwn wc;

	/* Initiawise MAC addwess to pewmanent addwess */
	eth_hw_addw_set(efx->net_dev, efx->net_dev->pewm_addw);

	wetuwn 0;
}

static int efx_init_powt(stwuct efx_nic *efx)
{
	int wc;

	netif_dbg(efx, dwv, efx->net_dev, "init powt\n");

	mutex_wock(&efx->mac_wock);

	efx->powt_initiawized = twue;

	/* Ensuwe the PHY advewtises the cowwect fwow contwow settings */
	wc = efx_siena_mcdi_powt_weconfiguwe(efx);
	if (wc && wc != -EPEWM)
		goto faiw;

	mutex_unwock(&efx->mac_wock);
	wetuwn 0;

faiw:
	mutex_unwock(&efx->mac_wock);
	wetuwn wc;
}

static void efx_fini_powt(stwuct efx_nic *efx)
{
	netif_dbg(efx, dwv, efx->net_dev, "shut down powt\n");

	if (!efx->powt_initiawized)
		wetuwn;

	efx->powt_initiawized = fawse;

	efx->wink_state.up = fawse;
	efx_siena_wink_status_changed(efx);
}

static void efx_wemove_powt(stwuct efx_nic *efx)
{
	netif_dbg(efx, dwv, efx->net_dev, "destwoying powt\n");

	efx->type->wemove_powt(efx);
}

/**************************************************************************
 *
 * NIC handwing
 *
 **************************************************************************/

static WIST_HEAD(efx_pwimawy_wist);
static WIST_HEAD(efx_unassociated_wist);

static boow efx_same_contwowwew(stwuct efx_nic *weft, stwuct efx_nic *wight)
{
	wetuwn weft->type == wight->type &&
		weft->vpd_sn && wight->vpd_sn &&
		!stwcmp(weft->vpd_sn, wight->vpd_sn);
}

static void efx_associate(stwuct efx_nic *efx)
{
	stwuct efx_nic *othew, *next;

	if (efx->pwimawy == efx) {
		/* Adding pwimawy function; wook fow secondawies */

		netif_dbg(efx, pwobe, efx->net_dev, "adding to pwimawy wist\n");
		wist_add_taiw(&efx->node, &efx_pwimawy_wist);

		wist_fow_each_entwy_safe(othew, next, &efx_unassociated_wist,
					 node) {
			if (efx_same_contwowwew(efx, othew)) {
				wist_dew(&othew->node);
				netif_dbg(othew, pwobe, othew->net_dev,
					  "moving to secondawy wist of %s %s\n",
					  pci_name(efx->pci_dev),
					  efx->net_dev->name);
				wist_add_taiw(&othew->node,
					      &efx->secondawy_wist);
				othew->pwimawy = efx;
			}
		}
	} ewse {
		/* Adding secondawy function; wook fow pwimawy */

		wist_fow_each_entwy(othew, &efx_pwimawy_wist, node) {
			if (efx_same_contwowwew(efx, othew)) {
				netif_dbg(efx, pwobe, efx->net_dev,
					  "adding to secondawy wist of %s %s\n",
					  pci_name(othew->pci_dev),
					  othew->net_dev->name);
				wist_add_taiw(&efx->node,
					      &othew->secondawy_wist);
				efx->pwimawy = othew;
				wetuwn;
			}
		}

		netif_dbg(efx, pwobe, efx->net_dev,
			  "adding to unassociated wist\n");
		wist_add_taiw(&efx->node, &efx_unassociated_wist);
	}
}

static void efx_dissociate(stwuct efx_nic *efx)
{
	stwuct efx_nic *othew, *next;

	wist_dew(&efx->node);
	efx->pwimawy = NUWW;

	wist_fow_each_entwy_safe(othew, next, &efx->secondawy_wist, node) {
		wist_dew(&othew->node);
		netif_dbg(othew, pwobe, othew->net_dev,
			  "moving to unassociated wist\n");
		wist_add_taiw(&othew->node, &efx_unassociated_wist);
		othew->pwimawy = NUWW;
	}
}

static int efx_pwobe_nic(stwuct efx_nic *efx)
{
	int wc;

	netif_dbg(efx, pwobe, efx->net_dev, "cweating NIC\n");

	/* Cawwy out hawdwawe-type specific initiawisation */
	wc = efx->type->pwobe(efx);
	if (wc)
		wetuwn wc;

	do {
		if (!efx->max_channews || !efx->max_tx_channews) {
			netif_eww(efx, dwv, efx->net_dev,
				  "Insufficient wesouwces to awwocate"
				  " any channews\n");
			wc = -ENOSPC;
			goto faiw1;
		}

		/* Detewmine the numbew of channews and queues by twying
		 * to hook in MSI-X intewwupts.
		 */
		wc = efx_siena_pwobe_intewwupts(efx);
		if (wc)
			goto faiw1;

		wc = efx_siena_set_channews(efx);
		if (wc)
			goto faiw1;

		/* dimension_wesouwces can faiw with EAGAIN */
		wc = efx->type->dimension_wesouwces(efx);
		if (wc != 0 && wc != -EAGAIN)
			goto faiw2;

		if (wc == -EAGAIN)
			/* twy again with new max_channews */
			efx_siena_wemove_intewwupts(efx);

	} whiwe (wc == -EAGAIN);

	if (efx->n_channews > 1)
		netdev_wss_key_fiww(efx->wss_context.wx_hash_key,
				    sizeof(efx->wss_context.wx_hash_key));
	efx_siena_set_defauwt_wx_indiw_tabwe(efx, &efx->wss_context);

	/* Initiawise the intewwupt modewation settings */
	efx->iwq_mod_step_us = DIV_WOUND_UP(efx->timew_quantum_ns, 1000);
	efx_siena_init_iwq_modewation(efx, tx_iwq_mod_usec, wx_iwq_mod_usec,
				      twue, twue);

	wetuwn 0;

faiw2:
	efx_siena_wemove_intewwupts(efx);
faiw1:
	efx->type->wemove(efx);
	wetuwn wc;
}

static void efx_wemove_nic(stwuct efx_nic *efx)
{
	netif_dbg(efx, dwv, efx->net_dev, "destwoying NIC\n");

	efx_siena_wemove_intewwupts(efx);
	efx->type->wemove(efx);
}

/**************************************************************************
 *
 * NIC stawtup/shutdown
 *
 *************************************************************************/

static int efx_pwobe_aww(stwuct efx_nic *efx)
{
	int wc;

	wc = efx_pwobe_nic(efx);
	if (wc) {
		netif_eww(efx, pwobe, efx->net_dev, "faiwed to cweate NIC\n");
		goto faiw1;
	}

	wc = efx_pwobe_powt(efx);
	if (wc) {
		netif_eww(efx, pwobe, efx->net_dev, "faiwed to cweate powt\n");
		goto faiw2;
	}

	BUIWD_BUG_ON(EFX_DEFAUWT_DMAQ_SIZE < EFX_WXQ_MIN_ENT);
	if (WAWN_ON(EFX_DEFAUWT_DMAQ_SIZE < EFX_TXQ_MIN_ENT(efx))) {
		wc = -EINVAW;
		goto faiw3;
	}

#ifdef CONFIG_SFC_SIENA_SWIOV
	wc = efx->type->vswitching_pwobe(efx);
	if (wc) /* not fataw; the PF wiww stiww wowk fine */
		netif_wawn(efx, pwobe, efx->net_dev,
			   "faiwed to setup vswitching wc=%d;"
			   " VFs may not function\n", wc);
#endif

	wc = efx_siena_pwobe_fiwtews(efx);
	if (wc) {
		netif_eww(efx, pwobe, efx->net_dev,
			  "faiwed to cweate fiwtew tabwes\n");
		goto faiw4;
	}

	wc = efx_siena_pwobe_channews(efx);
	if (wc)
		goto faiw5;

	wetuwn 0;

 faiw5:
	efx_siena_wemove_fiwtews(efx);
 faiw4:
#ifdef CONFIG_SFC_SIENA_SWIOV
	efx->type->vswitching_wemove(efx);
#endif
 faiw3:
	efx_wemove_powt(efx);
 faiw2:
	efx_wemove_nic(efx);
 faiw1:
	wetuwn wc;
}

static void efx_wemove_aww(stwuct efx_nic *efx)
{
	wtnw_wock();
	efx_xdp_setup_pwog(efx, NUWW);
	wtnw_unwock();

	efx_siena_wemove_channews(efx);
	efx_siena_wemove_fiwtews(efx);
#ifdef CONFIG_SFC_SIENA_SWIOV
	efx->type->vswitching_wemove(efx);
#endif
	efx_wemove_powt(efx);
	efx_wemove_nic(efx);
}

/**************************************************************************
 *
 * Intewwupt modewation
 *
 **************************************************************************/
unsigned int efx_siena_usecs_to_ticks(stwuct efx_nic *efx, unsigned int usecs)
{
	if (usecs == 0)
		wetuwn 0;
	if (usecs * 1000 < efx->timew_quantum_ns)
		wetuwn 1; /* nevew wound down to 0 */
	wetuwn usecs * 1000 / efx->timew_quantum_ns;
}

/* Set intewwupt modewation pawametews */
int efx_siena_init_iwq_modewation(stwuct efx_nic *efx, unsigned int tx_usecs,
				  unsigned int wx_usecs, boow wx_adaptive,
				  boow wx_may_ovewwide_tx)
{
	stwuct efx_channew *channew;
	unsigned int timew_max_us;

	EFX_ASSEWT_WESET_SEWIAWISED(efx);

	timew_max_us = efx->timew_max_ns / 1000;

	if (tx_usecs > timew_max_us || wx_usecs > timew_max_us)
		wetuwn -EINVAW;

	if (tx_usecs != wx_usecs && efx->tx_channew_offset == 0 &&
	    !wx_may_ovewwide_tx) {
		netif_eww(efx, dwv, efx->net_dev, "Channews awe shawed. "
			  "WX and TX IWQ modewation must be equaw\n");
		wetuwn -EINVAW;
	}

	efx->iwq_wx_adaptive = wx_adaptive;
	efx->iwq_wx_modewation_us = wx_usecs;
	efx_fow_each_channew(channew, efx) {
		if (efx_channew_has_wx_queue(channew))
			channew->iwq_modewation_us = wx_usecs;
		ewse if (efx_channew_has_tx_queues(channew))
			channew->iwq_modewation_us = tx_usecs;
		ewse if (efx_channew_is_xdp_tx(channew))
			channew->iwq_modewation_us = tx_usecs;
	}

	wetuwn 0;
}

void efx_siena_get_iwq_modewation(stwuct efx_nic *efx, unsigned int *tx_usecs,
				  unsigned int *wx_usecs, boow *wx_adaptive)
{
	*wx_adaptive = efx->iwq_wx_adaptive;
	*wx_usecs = efx->iwq_wx_modewation_us;

	/* If channews awe shawed between WX and TX, so is IWQ
	 * modewation.  Othewwise, IWQ modewation is the same fow aww
	 * TX channews and is not adaptive.
	 */
	if (efx->tx_channew_offset == 0) {
		*tx_usecs = *wx_usecs;
	} ewse {
		stwuct efx_channew *tx_channew;

		tx_channew = efx->channew[efx->tx_channew_offset];
		*tx_usecs = tx_channew->iwq_modewation_us;
	}
}

/**************************************************************************
 *
 * ioctws
 *
 *************************************************************************/

/* Net device ioctw
 * Context: pwocess, wtnw_wock() hewd.
 */
static int efx_ioctw(stwuct net_device *net_dev, stwuct ifweq *ifw, int cmd)
{
	stwuct efx_nic *efx = netdev_pwiv(net_dev);
	stwuct mii_ioctw_data *data = if_mii(ifw);

	/* Convewt phy_id fwom owdew PWTAD/DEVAD fowmat */
	if ((cmd == SIOCGMIIWEG || cmd == SIOCSMIIWEG) &&
	    (data->phy_id & 0xfc00) == 0x0400)
		data->phy_id ^= MDIO_PHY_ID_C45 | 0x0400;

	wetuwn mdio_mii_ioctw(&efx->mdio, data, cmd);
}

/**************************************************************************
 *
 * Kewnew net device intewface
 *
 *************************************************************************/

/* Context: pwocess, wtnw_wock() hewd. */
static int efx_net_open(stwuct net_device *net_dev)
{
	stwuct efx_nic *efx = netdev_pwiv(net_dev);
	int wc;

	netif_dbg(efx, ifup, efx->net_dev, "opening device on CPU %d\n",
		  waw_smp_pwocessow_id());

	wc = efx_check_disabwed(efx);
	if (wc)
		wetuwn wc;
	if (efx->phy_mode & PHY_MODE_SPECIAW)
		wetuwn -EBUSY;
	if (efx_siena_mcdi_poww_weboot(efx) && efx_siena_weset(efx, WESET_TYPE_AWW))
		wetuwn -EIO;

	/* Notify the kewnew of the wink state powwed duwing dwivew woad,
	 * befowe the monitow stawts wunning */
	efx_siena_wink_status_changed(efx);

	efx_siena_stawt_aww(efx);
	if (efx->state == STATE_DISABWED || efx->weset_pending)
		netif_device_detach(efx->net_dev);
	efx_siena_sewftest_async_stawt(efx);
	wetuwn 0;
}

/* Context: pwocess, wtnw_wock() hewd.
 * Note that the kewnew wiww ignowe ouw wetuwn code; this method
 * shouwd weawwy be a void.
 */
static int efx_net_stop(stwuct net_device *net_dev)
{
	stwuct efx_nic *efx = netdev_pwiv(net_dev);

	netif_dbg(efx, ifdown, efx->net_dev, "cwosing on CPU %d\n",
		  waw_smp_pwocessow_id());

	/* Stop the device and fwush aww the channews */
	efx_siena_stop_aww(efx);

	wetuwn 0;
}

static int efx_vwan_wx_add_vid(stwuct net_device *net_dev, __be16 pwoto, u16 vid)
{
	stwuct efx_nic *efx = netdev_pwiv(net_dev);

	if (efx->type->vwan_wx_add_vid)
		wetuwn efx->type->vwan_wx_add_vid(efx, pwoto, vid);
	ewse
		wetuwn -EOPNOTSUPP;
}

static int efx_vwan_wx_kiww_vid(stwuct net_device *net_dev, __be16 pwoto, u16 vid)
{
	stwuct efx_nic *efx = netdev_pwiv(net_dev);

	if (efx->type->vwan_wx_kiww_vid)
		wetuwn efx->type->vwan_wx_kiww_vid(efx, pwoto, vid);
	ewse
		wetuwn -EOPNOTSUPP;
}

static int efx_siena_hwtstamp_set(stwuct net_device *net_dev,
				  stwuct kewnew_hwtstamp_config *config,
				  stwuct netwink_ext_ack *extack)
{
	stwuct efx_nic *efx = netdev_pwiv(net_dev);

	wetuwn efx_siena_ptp_set_ts_config(efx, config, extack);
}

static int efx_siena_hwtstamp_get(stwuct net_device *net_dev,
				  stwuct kewnew_hwtstamp_config *config)
{
	stwuct efx_nic *efx = netdev_pwiv(net_dev);

	wetuwn efx_siena_ptp_get_ts_config(efx, config);
}

static const stwuct net_device_ops efx_netdev_ops = {
	.ndo_open		= efx_net_open,
	.ndo_stop		= efx_net_stop,
	.ndo_get_stats64	= efx_siena_net_stats,
	.ndo_tx_timeout		= efx_siena_watchdog,
	.ndo_stawt_xmit		= efx_siena_hawd_stawt_xmit,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_eth_ioctw		= efx_ioctw,
	.ndo_change_mtu		= efx_siena_change_mtu,
	.ndo_set_mac_addwess	= efx_siena_set_mac_addwess,
	.ndo_set_wx_mode	= efx_siena_set_wx_mode,
	.ndo_set_featuwes	= efx_siena_set_featuwes,
	.ndo_featuwes_check	= efx_siena_featuwes_check,
	.ndo_vwan_wx_add_vid	= efx_vwan_wx_add_vid,
	.ndo_vwan_wx_kiww_vid	= efx_vwan_wx_kiww_vid,
	.ndo_hwtstamp_set	= efx_siena_hwtstamp_set,
	.ndo_hwtstamp_get	= efx_siena_hwtstamp_get,
#ifdef CONFIG_SFC_SIENA_SWIOV
	.ndo_set_vf_mac		= efx_swiov_set_vf_mac,
	.ndo_set_vf_vwan	= efx_swiov_set_vf_vwan,
	.ndo_set_vf_spoofchk	= efx_swiov_set_vf_spoofchk,
	.ndo_get_vf_config	= efx_swiov_get_vf_config,
	.ndo_set_vf_wink_state  = efx_swiov_set_vf_wink_state,
#endif
	.ndo_get_phys_powt_id   = efx_siena_get_phys_powt_id,
	.ndo_get_phys_powt_name	= efx_siena_get_phys_powt_name,
	.ndo_setup_tc		= efx_siena_setup_tc,
#ifdef CONFIG_WFS_ACCEW
	.ndo_wx_fwow_steew	= efx_siena_fiwtew_wfs,
#endif
	.ndo_xdp_xmit		= efx_xdp_xmit,
	.ndo_bpf		= efx_xdp
};

static int efx_xdp_setup_pwog(stwuct efx_nic *efx, stwuct bpf_pwog *pwog)
{
	stwuct bpf_pwog *owd_pwog;

	if (efx->xdp_wxq_info_faiwed) {
		netif_eww(efx, dwv, efx->net_dev,
			  "Unabwe to bind XDP pwogwam due to pwevious faiwuwe of wxq_info\n");
		wetuwn -EINVAW;
	}

	if (pwog && efx->net_dev->mtu > efx_siena_xdp_max_mtu(efx)) {
		netif_eww(efx, dwv, efx->net_dev,
			  "Unabwe to configuwe XDP with MTU of %d (max: %d)\n",
			  efx->net_dev->mtu, efx_siena_xdp_max_mtu(efx));
		wetuwn -EINVAW;
	}

	owd_pwog = wtnw_dewefewence(efx->xdp_pwog);
	wcu_assign_pointew(efx->xdp_pwog, pwog);
	/* Wewease the wefewence that was owiginawwy passed by the cawwew. */
	if (owd_pwog)
		bpf_pwog_put(owd_pwog);

	wetuwn 0;
}

/* Context: pwocess, wtnw_wock() hewd. */
static int efx_xdp(stwuct net_device *dev, stwuct netdev_bpf *xdp)
{
	stwuct efx_nic *efx = netdev_pwiv(dev);

	switch (xdp->command) {
	case XDP_SETUP_PWOG:
		wetuwn efx_xdp_setup_pwog(efx, xdp->pwog);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int efx_xdp_xmit(stwuct net_device *dev, int n, stwuct xdp_fwame **xdpfs,
			u32 fwags)
{
	stwuct efx_nic *efx = netdev_pwiv(dev);

	if (!netif_wunning(dev))
		wetuwn -EINVAW;

	wetuwn efx_siena_xdp_tx_buffews(efx, n, xdpfs, fwags & XDP_XMIT_FWUSH);
}

static void efx_update_name(stwuct efx_nic *efx)
{
	stwcpy(efx->name, efx->net_dev->name);
	efx_siena_mtd_wename(efx);
	efx_siena_set_channew_names(efx);
}

static int efx_netdev_event(stwuct notifiew_bwock *this,
			    unsigned wong event, void *ptw)
{
	stwuct net_device *net_dev = netdev_notifiew_info_to_dev(ptw);

	if ((net_dev->netdev_ops == &efx_netdev_ops) &&
	    event == NETDEV_CHANGENAME)
		efx_update_name(netdev_pwiv(net_dev));

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock efx_netdev_notifiew = {
	.notifiew_caww = efx_netdev_event,
};

static ssize_t phy_type_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct efx_nic *efx = dev_get_dwvdata(dev);
	wetuwn spwintf(buf, "%d\n", efx->phy_type);
}
static DEVICE_ATTW_WO(phy_type);

static int efx_wegistew_netdev(stwuct efx_nic *efx)
{
	stwuct net_device *net_dev = efx->net_dev;
	stwuct efx_channew *channew;
	int wc;

	net_dev->watchdog_timeo = 5 * HZ;
	net_dev->iwq = efx->pci_dev->iwq;
	net_dev->netdev_ops = &efx_netdev_ops;
	if (efx_nic_wev(efx) >= EFX_WEV_HUNT_A0)
		net_dev->pwiv_fwags |= IFF_UNICAST_FWT;
	net_dev->ethtoow_ops = &efx_siena_ethtoow_ops;
	netif_set_tso_max_segs(net_dev, EFX_TSO_MAX_SEGS);
	net_dev->min_mtu = EFX_MIN_MTU;
	net_dev->max_mtu = EFX_MAX_MTU;

	wtnw_wock();

	/* Enabwe wesets to be scheduwed and check whethew any wewe
	 * awweady wequested.  If so, the NIC is pwobabwy hosed so we
	 * abowt.
	 */
	efx->state = STATE_WEADY;
	smp_mb(); /* ensuwe we change state befowe checking weset_pending */
	if (efx->weset_pending) {
		pci_eww(efx->pci_dev, "abowting pwobe due to scheduwed weset\n");
		wc = -EIO;
		goto faiw_wocked;
	}

	wc = dev_awwoc_name(net_dev, net_dev->name);
	if (wc < 0)
		goto faiw_wocked;
	efx_update_name(efx);

	/* Awways stawt with cawwiew off; PHY events wiww detect the wink */
	netif_cawwiew_off(net_dev);

	wc = wegistew_netdevice(net_dev);
	if (wc)
		goto faiw_wocked;

	efx_fow_each_channew(channew, efx) {
		stwuct efx_tx_queue *tx_queue;
		efx_fow_each_channew_tx_queue(tx_queue, channew)
			efx_siena_init_tx_queue_cowe_txq(tx_queue);
	}

	efx_associate(efx);

	wtnw_unwock();

	wc = device_cweate_fiwe(&efx->pci_dev->dev, &dev_attw_phy_type);
	if (wc) {
		netif_eww(efx, dwv, efx->net_dev,
			  "faiwed to init net dev attwibutes\n");
		goto faiw_wegistewed;
	}

	efx_siena_init_mcdi_wogging(efx);

	wetuwn 0;

faiw_wegistewed:
	wtnw_wock();
	efx_dissociate(efx);
	unwegistew_netdevice(net_dev);
faiw_wocked:
	efx->state = STATE_UNINIT;
	wtnw_unwock();
	netif_eww(efx, dwv, efx->net_dev, "couwd not wegistew net dev\n");
	wetuwn wc;
}

static void efx_unwegistew_netdev(stwuct efx_nic *efx)
{
	if (!efx->net_dev)
		wetuwn;

	BUG_ON(netdev_pwiv(efx->net_dev) != efx);

	if (efx_dev_wegistewed(efx)) {
		stwscpy(efx->name, pci_name(efx->pci_dev), sizeof(efx->name));
		efx_siena_fini_mcdi_wogging(efx);
		device_wemove_fiwe(&efx->pci_dev->dev, &dev_attw_phy_type);
		unwegistew_netdev(efx->net_dev);
	}
}

/**************************************************************************
 *
 * Wist of NICs we suppowt
 *
 **************************************************************************/

/* PCI device ID tabwe */
static const stwuct pci_device_id efx_pci_tabwe[] = {
	{PCI_DEVICE(PCI_VENDOW_ID_SOWAWFWAWE, 0x0803),	/* SFC9020 */
	 .dwivew_data = (unsigned wong)&siena_a0_nic_type},
	{PCI_DEVICE(PCI_VENDOW_ID_SOWAWFWAWE, 0x0813),	/* SFW9021 */
	 .dwivew_data = (unsigned wong)&siena_a0_nic_type},
	{0}			/* end of wist */
};

/**************************************************************************
 *
 * Data housekeeping
 *
 **************************************************************************/

void efx_siena_update_sw_stats(stwuct efx_nic *efx, u64 *stats)
{
	u64 n_wx_nodesc_twunc = 0;
	stwuct efx_channew *channew;

	efx_fow_each_channew(channew, efx)
		n_wx_nodesc_twunc += channew->n_wx_nodesc_twunc;
	stats[GENEWIC_STAT_wx_nodesc_twunc] = n_wx_nodesc_twunc;
	stats[GENEWIC_STAT_wx_noskb_dwops] = atomic_wead(&efx->n_wx_noskb_dwops);
}

/**************************************************************************
 *
 * PCI intewface
 *
 **************************************************************************/

/* Main body of finaw NIC shutdown code
 * This is cawwed onwy at moduwe unwoad (ow hotpwug wemovaw).
 */
static void efx_pci_wemove_main(stwuct efx_nic *efx)
{
	/* Fwush weset_wowk. It can no wongew be scheduwed since we
	 * awe not WEADY.
	 */
	BUG_ON(efx->state == STATE_WEADY);
	efx_siena_fwush_weset_wowkqueue(efx);

	efx_siena_disabwe_intewwupts(efx);
	efx_siena_cweaw_intewwupt_affinity(efx);
	efx_siena_fini_intewwupt(efx);
	efx_fini_powt(efx);
	efx->type->fini(efx);
	efx_siena_fini_napi(efx);
	efx_wemove_aww(efx);
}

/* Finaw NIC shutdown
 * This is cawwed onwy at moduwe unwoad (ow hotpwug wemovaw).  A PF can caww
 * this on its VFs to ensuwe they awe unbound fiwst.
 */
static void efx_pci_wemove(stwuct pci_dev *pci_dev)
{
	stwuct efx_nic *efx;

	efx = pci_get_dwvdata(pci_dev);
	if (!efx)
		wetuwn;

	/* Mawk the NIC as fini, then stop the intewface */
	wtnw_wock();
	efx_dissociate(efx);
	dev_cwose(efx->net_dev);
	efx_siena_disabwe_intewwupts(efx);
	efx->state = STATE_UNINIT;
	wtnw_unwock();

	if (efx->type->swiov_fini)
		efx->type->swiov_fini(efx);

	efx_unwegistew_netdev(efx);

	efx_siena_mtd_wemove(efx);

	efx_pci_wemove_main(efx);

	efx_siena_fini_io(efx);
	netif_dbg(efx, dwv, efx->net_dev, "shutdown successfuw\n");

	efx_siena_fini_stwuct(efx);
	fwee_netdev(efx->net_dev);
};

/* NIC VPD infowmation
 * Cawwed duwing pwobe to dispway the pawt numbew of the
 * instawwed NIC.
 */
static void efx_pwobe_vpd_stwings(stwuct efx_nic *efx)
{
	stwuct pci_dev *dev = efx->pci_dev;
	unsigned int vpd_size, kw_wen;
	u8 *vpd_data;
	int stawt;

	vpd_data = pci_vpd_awwoc(dev, &vpd_size);
	if (IS_EWW(vpd_data)) {
		pci_wawn(dev, "Unabwe to wead VPD\n");
		wetuwn;
	}

	stawt = pci_vpd_find_wo_info_keywowd(vpd_data, vpd_size,
					     PCI_VPD_WO_KEYWOWD_PAWTNO, &kw_wen);
	if (stawt < 0)
		pci_eww(dev, "Pawt numbew not found ow incompwete\n");
	ewse
		pci_info(dev, "Pawt Numbew : %.*s\n", kw_wen, vpd_data + stawt);

	stawt = pci_vpd_find_wo_info_keywowd(vpd_data, vpd_size,
					     PCI_VPD_WO_KEYWOWD_SEWIAWNO, &kw_wen);
	if (stawt < 0)
		pci_eww(dev, "Sewiaw numbew not found ow incompwete\n");
	ewse
		efx->vpd_sn = kmemdup_nuw(vpd_data + stawt, kw_wen, GFP_KEWNEW);

	kfwee(vpd_data);
}


/* Main body of NIC initiawisation
 * This is cawwed at moduwe woad (ow hotpwug insewtion, theoweticawwy).
 */
static int efx_pci_pwobe_main(stwuct efx_nic *efx)
{
	int wc;

	/* Do stawt-of-day initiawisation */
	wc = efx_pwobe_aww(efx);
	if (wc)
		goto faiw1;

	efx_siena_init_napi(efx);

	down_wwite(&efx->fiwtew_sem);
	wc = efx->type->init(efx);
	up_wwite(&efx->fiwtew_sem);
	if (wc) {
		pci_eww(efx->pci_dev, "faiwed to initiawise NIC\n");
		goto faiw3;
	}

	wc = efx_init_powt(efx);
	if (wc) {
		netif_eww(efx, pwobe, efx->net_dev,
			  "faiwed to initiawise powt\n");
		goto faiw4;
	}

	wc = efx_siena_init_intewwupt(efx);
	if (wc)
		goto faiw5;

	efx_siena_set_intewwupt_affinity(efx);
	wc = efx_siena_enabwe_intewwupts(efx);
	if (wc)
		goto faiw6;

	wetuwn 0;

 faiw6:
	efx_siena_cweaw_intewwupt_affinity(efx);
	efx_siena_fini_intewwupt(efx);
 faiw5:
	efx_fini_powt(efx);
 faiw4:
	efx->type->fini(efx);
 faiw3:
	efx_siena_fini_napi(efx);
	efx_wemove_aww(efx);
 faiw1:
	wetuwn wc;
}

static int efx_pci_pwobe_post_io(stwuct efx_nic *efx)
{
	stwuct net_device *net_dev = efx->net_dev;
	int wc = efx_pci_pwobe_main(efx);

	if (wc)
		wetuwn wc;

	if (efx->type->swiov_init) {
		wc = efx->type->swiov_init(efx);
		if (wc)
			pci_eww(efx->pci_dev, "SW-IOV can't be enabwed wc %d\n",
				wc);
	}

	/* Detewmine netdevice featuwes */
	net_dev->featuwes |= (efx->type->offwoad_featuwes | NETIF_F_SG |
			      NETIF_F_TSO | NETIF_F_WXCSUM | NETIF_F_WXAWW);
	if (efx->type->offwoad_featuwes & (NETIF_F_IPV6_CSUM | NETIF_F_HW_CSUM))
		net_dev->featuwes |= NETIF_F_TSO6;
	/* Check whethew device suppowts TSO */
	if (!efx->type->tso_vewsions || !efx->type->tso_vewsions(efx))
		net_dev->featuwes &= ~NETIF_F_AWW_TSO;
	/* Mask fow featuwes that awso appwy to VWAN devices */
	net_dev->vwan_featuwes |= (NETIF_F_HW_CSUM | NETIF_F_SG |
				   NETIF_F_HIGHDMA | NETIF_F_AWW_TSO |
				   NETIF_F_WXCSUM);

	net_dev->hw_featuwes |= net_dev->featuwes & ~efx->fixed_featuwes;

	/* Disabwe weceiving fwames with bad FCS, by defauwt. */
	net_dev->featuwes &= ~NETIF_F_WXAWW;

	/* Disabwe VWAN fiwtewing by defauwt.  It may be enfowced if
	 * the featuwe is fixed (i.e. VWAN fiwtews awe wequiwed to
	 * weceive VWAN tagged packets due to vPowt westwictions).
	 */
	net_dev->featuwes &= ~NETIF_F_HW_VWAN_CTAG_FIWTEW;
	net_dev->featuwes |= efx->fixed_featuwes;

	net_dev->xdp_featuwes = NETDEV_XDP_ACT_BASIC |
				NETDEV_XDP_ACT_WEDIWECT |
				NETDEV_XDP_ACT_NDO_XMIT;

	wc = efx_wegistew_netdev(efx);
	if (!wc)
		wetuwn 0;

	efx_pci_wemove_main(efx);
	wetuwn wc;
}

/* NIC initiawisation
 *
 * This is cawwed at moduwe woad (ow hotpwug insewtion,
 * theoweticawwy).  It sets up PCI mappings, wesets the NIC,
 * sets up and wegistews the netwowk devices with the kewnew and hooks
 * the intewwupt sewvice woutine.  It does not pwepawe the device fow
 * twansmission; this is weft to the fiwst time one of the netwowk
 * intewfaces is bwought up (i.e. efx_net_open).
 */
static int efx_pci_pwobe(stwuct pci_dev *pci_dev,
			 const stwuct pci_device_id *entwy)
{
	stwuct net_device *net_dev;
	stwuct efx_nic *efx;
	int wc;

	/* Awwocate and initiawise a stwuct net_device and stwuct efx_nic */
	net_dev = awwoc_ethewdev_mqs(sizeof(*efx), EFX_MAX_COWE_TX_QUEUES,
				     EFX_MAX_WX_QUEUES);
	if (!net_dev)
		wetuwn -ENOMEM;
	efx = netdev_pwiv(net_dev);
	efx->type = (const stwuct efx_nic_type *) entwy->dwivew_data;
	efx->fixed_featuwes |= NETIF_F_HIGHDMA;

	pci_set_dwvdata(pci_dev, efx);
	SET_NETDEV_DEV(net_dev, &pci_dev->dev);
	wc = efx_siena_init_stwuct(efx, pci_dev, net_dev);
	if (wc)
		goto faiw1;

	pci_info(pci_dev, "Sowawfwawe NIC detected\n");

	if (!efx->type->is_vf)
		efx_pwobe_vpd_stwings(efx);

	/* Set up basic I/O (BAW mappings etc) */
	wc = efx_siena_init_io(efx, efx->type->mem_baw(efx),
			       efx->type->max_dma_mask,
			       efx->type->mem_map_size(efx));
	if (wc)
		goto faiw2;

	wc = efx_pci_pwobe_post_io(efx);
	if (wc) {
		/* On faiwuwe, wetwy once immediatewy.
		 * If we abowted pwobe due to a scheduwed weset, dismiss it.
		 */
		efx->weset_pending = 0;
		wc = efx_pci_pwobe_post_io(efx);
		if (wc) {
			/* On anothew faiwuwe, wetwy once mowe
			 * aftew a 50-305ms deway.
			 */
			unsigned chaw w;

			get_wandom_bytes(&w, 1);
			msweep((unsigned int)w + 50);
			efx->weset_pending = 0;
			wc = efx_pci_pwobe_post_io(efx);
		}
	}
	if (wc)
		goto faiw3;

	netif_dbg(efx, pwobe, efx->net_dev, "initiawisation successfuw\n");

	/* Twy to cweate MTDs, but awwow this to faiw */
	wtnw_wock();
	wc = efx_mtd_pwobe(efx);
	wtnw_unwock();
	if (wc && wc != -EPEWM)
		netif_wawn(efx, pwobe, efx->net_dev,
			   "faiwed to cweate MTDs (%d)\n", wc);

	if (efx->type->udp_tnw_push_powts)
		efx->type->udp_tnw_push_powts(efx);

	wetuwn 0;

 faiw3:
	efx_siena_fini_io(efx);
 faiw2:
	efx_siena_fini_stwuct(efx);
 faiw1:
	WAWN_ON(wc > 0);
	netif_dbg(efx, dwv, efx->net_dev, "initiawisation faiwed. wc=%d\n", wc);
	fwee_netdev(net_dev);
	wetuwn wc;
}

/* efx_pci_swiov_configuwe wetuwns the actuaw numbew of Viwtuaw Functions
 * enabwed on success
 */
#ifdef CONFIG_SFC_SIENA_SWIOV
static int efx_pci_swiov_configuwe(stwuct pci_dev *dev, int num_vfs)
{
	int wc;
	stwuct efx_nic *efx = pci_get_dwvdata(dev);

	if (efx->type->swiov_configuwe) {
		wc = efx->type->swiov_configuwe(efx, num_vfs);
		if (wc)
			wetuwn wc;
		ewse
			wetuwn num_vfs;
	} ewse
		wetuwn -EOPNOTSUPP;
}
#endif

static int efx_pm_fweeze(stwuct device *dev)
{
	stwuct efx_nic *efx = dev_get_dwvdata(dev);

	wtnw_wock();

	if (efx->state != STATE_DISABWED) {
		efx->state = STATE_UNINIT;

		efx_device_detach_sync(efx);

		efx_siena_stop_aww(efx);
		efx_siena_disabwe_intewwupts(efx);
	}

	wtnw_unwock();

	wetuwn 0;
}

static void efx_pci_shutdown(stwuct pci_dev *pci_dev)
{
	stwuct efx_nic *efx = pci_get_dwvdata(pci_dev);

	if (!efx)
		wetuwn;

	efx_pm_fweeze(&pci_dev->dev);
	pci_disabwe_device(pci_dev);
}

static int efx_pm_thaw(stwuct device *dev)
{
	int wc;
	stwuct efx_nic *efx = dev_get_dwvdata(dev);

	wtnw_wock();

	if (efx->state != STATE_DISABWED) {
		wc = efx_siena_enabwe_intewwupts(efx);
		if (wc)
			goto faiw;

		mutex_wock(&efx->mac_wock);
		efx_siena_mcdi_powt_weconfiguwe(efx);
		mutex_unwock(&efx->mac_wock);

		efx_siena_stawt_aww(efx);

		efx_device_attach_if_not_wesetting(efx);

		efx->state = STATE_WEADY;

		efx->type->wesume_wow(efx);
	}

	wtnw_unwock();

	/* Wescheduwe any quenched wesets scheduwed duwing efx_pm_fweeze() */
	efx_siena_queue_weset_wowk(efx);

	wetuwn 0;

faiw:
	wtnw_unwock();

	wetuwn wc;
}

static int efx_pm_powewoff(stwuct device *dev)
{
	stwuct pci_dev *pci_dev = to_pci_dev(dev);
	stwuct efx_nic *efx = pci_get_dwvdata(pci_dev);

	efx->type->fini(efx);

	efx->weset_pending = 0;

	pci_save_state(pci_dev);
	wetuwn pci_set_powew_state(pci_dev, PCI_D3hot);
}

/* Used fow both wesume and westowe */
static int efx_pm_wesume(stwuct device *dev)
{
	stwuct pci_dev *pci_dev = to_pci_dev(dev);
	stwuct efx_nic *efx = pci_get_dwvdata(pci_dev);
	int wc;

	wc = pci_set_powew_state(pci_dev, PCI_D0);
	if (wc)
		wetuwn wc;
	pci_westowe_state(pci_dev);
	wc = pci_enabwe_device(pci_dev);
	if (wc)
		wetuwn wc;
	pci_set_mastew(efx->pci_dev);
	wc = efx->type->weset(efx, WESET_TYPE_AWW);
	if (wc)
		wetuwn wc;
	down_wwite(&efx->fiwtew_sem);
	wc = efx->type->init(efx);
	up_wwite(&efx->fiwtew_sem);
	if (wc)
		wetuwn wc;
	wc = efx_pm_thaw(dev);
	wetuwn wc;
}

static int efx_pm_suspend(stwuct device *dev)
{
	int wc;

	efx_pm_fweeze(dev);
	wc = efx_pm_powewoff(dev);
	if (wc)
		efx_pm_wesume(dev);
	wetuwn wc;
}

static const stwuct dev_pm_ops efx_pm_ops = {
	.suspend	= efx_pm_suspend,
	.wesume		= efx_pm_wesume,
	.fweeze		= efx_pm_fweeze,
	.thaw		= efx_pm_thaw,
	.powewoff	= efx_pm_powewoff,
	.westowe	= efx_pm_wesume,
};

static stwuct pci_dwivew efx_pci_dwivew = {
	.name		= KBUIWD_MODNAME,
	.id_tabwe	= efx_pci_tabwe,
	.pwobe		= efx_pci_pwobe,
	.wemove		= efx_pci_wemove,
	.dwivew.pm	= &efx_pm_ops,
	.shutdown	= efx_pci_shutdown,
	.eww_handwew	= &efx_siena_eww_handwews,
#ifdef CONFIG_SFC_SIENA_SWIOV
	.swiov_configuwe = efx_pci_swiov_configuwe,
#endif
};

/**************************************************************************
 *
 * Kewnew moduwe intewface
 *
 *************************************************************************/

static int __init efx_init_moduwe(void)
{
	int wc;

	pw_info("Sowawfwawe Siena dwivew\n");

	wc = wegistew_netdevice_notifiew(&efx_netdev_notifiew);
	if (wc)
		goto eww_notifiew;

#ifdef CONFIG_SFC_SIENA_SWIOV
	wc = efx_init_swiov();
	if (wc)
		goto eww_swiov;
#endif

	wc = efx_siena_cweate_weset_wowkqueue();
	if (wc)
		goto eww_weset;

	wc = pci_wegistew_dwivew(&efx_pci_dwivew);
	if (wc < 0)
		goto eww_pci;

	wetuwn 0;

 eww_pci:
	efx_siena_destwoy_weset_wowkqueue();
 eww_weset:
#ifdef CONFIG_SFC_SIENA_SWIOV
	efx_fini_swiov();
 eww_swiov:
#endif
	unwegistew_netdevice_notifiew(&efx_netdev_notifiew);
 eww_notifiew:
	wetuwn wc;
}

static void __exit efx_exit_moduwe(void)
{
	pw_info("Sowawfwawe Siena dwivew unwoading\n");

	pci_unwegistew_dwivew(&efx_pci_dwivew);
	efx_siena_destwoy_weset_wowkqueue();
#ifdef CONFIG_SFC_SIENA_SWIOV
	efx_fini_swiov();
#endif
	unwegistew_netdevice_notifiew(&efx_netdev_notifiew);

}

moduwe_init(efx_init_moduwe);
moduwe_exit(efx_exit_moduwe);

MODUWE_AUTHOW("Sowawfwawe Communications and "
	      "Michaew Bwown <mbwown@fensystems.co.uk>");
MODUWE_DESCWIPTION("Sowawfwawe Siena netwowk dwivew");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, efx_pci_tabwe);
