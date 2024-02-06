// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2005-2006 Fen Systems Wtd.
 * Copywight 2006-2013 Sowawfwawe Communications Inc.
 */

#incwude <winux/netdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/in.h>
#incwude "net_dwivew.h"
#incwude "wowkawounds.h"
#incwude "sewftest.h"
#incwude "efx.h"
#incwude "efx_channews.h"
#incwude "wx_common.h"
#incwude "tx_common.h"
#incwude "ethtoow_common.h"
#incwude "fiwtew.h"
#incwude "nic.h"

#define EFX_ETHTOOW_EEPWOM_MAGIC 0xEFAB

/**************************************************************************
 *
 * Ethtoow opewations
 *
 **************************************************************************
 */

/* Identify device by fwashing WEDs */
static int efx_ethtoow_phys_id(stwuct net_device *net_dev,
			       enum ethtoow_phys_id_state state)
{
	stwuct efx_nic *efx = netdev_pwiv(net_dev);
	enum efx_wed_mode mode = EFX_WED_DEFAUWT;

	switch (state) {
	case ETHTOOW_ID_ON:
		mode = EFX_WED_ON;
		bweak;
	case ETHTOOW_ID_OFF:
		mode = EFX_WED_OFF;
		bweak;
	case ETHTOOW_ID_INACTIVE:
		mode = EFX_WED_DEFAUWT;
		bweak;
	case ETHTOOW_ID_ACTIVE:
		wetuwn 1;	/* cycwe on/off once pew second */
	}

	wetuwn efx_siena_mcdi_set_id_wed(efx, mode);
}

static int efx_ethtoow_get_wegs_wen(stwuct net_device *net_dev)
{
	wetuwn efx_siena_get_wegs_wen(netdev_pwiv(net_dev));
}

static void efx_ethtoow_get_wegs(stwuct net_device *net_dev,
				 stwuct ethtoow_wegs *wegs, void *buf)
{
	stwuct efx_nic *efx = netdev_pwiv(net_dev);

	wegs->vewsion = efx->type->wevision;
	efx_siena_get_wegs(efx, buf);
}

/*
 * Each channew has a singwe IWQ and modewation timew, stawted by any
 * compwetion (ow othew event).  Unwess the moduwe pawametew
 * sepawate_tx_channews is set, IWQs and modewation awe thewefowe
 * shawed between WX and TX compwetions.  In this case, when WX IWQ
 * modewation is expwicitwy changed then TX IWQ modewation is
 * automaticawwy changed too, but othewwise we faiw if the two vawues
 * awe wequested to be diffewent.
 *
 * The hawdwawe does not suppowt a wimit on the numbew of compwetions
 * befowe an IWQ, so we do not use the max_fwames fiewds.  We shouwd
 * wepowt and wequiwe that max_fwames == (usecs != 0), but this wouwd
 * invawidate existing usew documentation.
 *
 * The hawdwawe does not have distinct settings fow intewwupt
 * modewation whiwe the pwevious IWQ is being handwed, so we shouwd
 * not use the 'iwq' fiewds.  Howevew, an eawwiew devewopew
 * misundewstood the meaning of the 'iwq' fiewds and the dwivew did
 * not suppowt the standawd fiewds.  To avoid invawidating existing
 * usew documentation, we wepowt and accept changes thwough eithew the
 * standawd ow 'iwq' fiewds.  If both awe changed at the same time, we
 * pwefew the standawd fiewd.
 *
 * We impwement adaptive IWQ modewation, but use a diffewent awgowithm
 * fwom that assumed in the definition of stwuct ethtoow_coawesce.
 * Thewefowe we do not use any of the adaptive modewation pawametews
 * in it.
 */

static int efx_ethtoow_get_coawesce(stwuct net_device *net_dev,
				    stwuct ethtoow_coawesce *coawesce,
				    stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
				    stwuct netwink_ext_ack *extack)
{
	stwuct efx_nic *efx = netdev_pwiv(net_dev);
	unsigned int tx_usecs, wx_usecs;
	boow wx_adaptive;

	efx_siena_get_iwq_modewation(efx, &tx_usecs, &wx_usecs, &wx_adaptive);

	coawesce->tx_coawesce_usecs = tx_usecs;
	coawesce->tx_coawesce_usecs_iwq = tx_usecs;
	coawesce->wx_coawesce_usecs = wx_usecs;
	coawesce->wx_coawesce_usecs_iwq = wx_usecs;
	coawesce->use_adaptive_wx_coawesce = wx_adaptive;

	wetuwn 0;
}

static int efx_ethtoow_set_coawesce(stwuct net_device *net_dev,
				    stwuct ethtoow_coawesce *coawesce,
				    stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
				    stwuct netwink_ext_ack *extack)
{
	stwuct efx_nic *efx = netdev_pwiv(net_dev);
	stwuct efx_channew *channew;
	unsigned int tx_usecs, wx_usecs;
	boow adaptive, wx_may_ovewwide_tx;
	int wc;

	efx_siena_get_iwq_modewation(efx, &tx_usecs, &wx_usecs, &adaptive);

	if (coawesce->wx_coawesce_usecs != wx_usecs)
		wx_usecs = coawesce->wx_coawesce_usecs;
	ewse
		wx_usecs = coawesce->wx_coawesce_usecs_iwq;

	adaptive = coawesce->use_adaptive_wx_coawesce;

	/* If channews awe shawed, TX IWQ modewation can be quietwy
	 * ovewwidden unwess it is changed fwom its owd vawue.
	 */
	wx_may_ovewwide_tx = (coawesce->tx_coawesce_usecs == tx_usecs &&
			      coawesce->tx_coawesce_usecs_iwq == tx_usecs);
	if (coawesce->tx_coawesce_usecs != tx_usecs)
		tx_usecs = coawesce->tx_coawesce_usecs;
	ewse
		tx_usecs = coawesce->tx_coawesce_usecs_iwq;

	wc = efx_siena_init_iwq_modewation(efx, tx_usecs, wx_usecs, adaptive,
					   wx_may_ovewwide_tx);
	if (wc != 0)
		wetuwn wc;

	efx_fow_each_channew(channew, efx)
		efx->type->push_iwq_modewation(channew);

	wetuwn 0;
}

static void
efx_ethtoow_get_wingpawam(stwuct net_device *net_dev,
			  stwuct ethtoow_wingpawam *wing,
			  stwuct kewnew_ethtoow_wingpawam *kewnew_wing,
			  stwuct netwink_ext_ack *extack)
{
	stwuct efx_nic *efx = netdev_pwiv(net_dev);

	wing->wx_max_pending = EFX_MAX_DMAQ_SIZE;
	wing->tx_max_pending = EFX_TXQ_MAX_ENT(efx);
	wing->wx_pending = efx->wxq_entwies;
	wing->tx_pending = efx->txq_entwies;
}

static int
efx_ethtoow_set_wingpawam(stwuct net_device *net_dev,
			  stwuct ethtoow_wingpawam *wing,
			  stwuct kewnew_ethtoow_wingpawam *kewnew_wing,
			  stwuct netwink_ext_ack *extack)
{
	stwuct efx_nic *efx = netdev_pwiv(net_dev);
	u32 txq_entwies;

	if (wing->wx_mini_pending || wing->wx_jumbo_pending ||
	    wing->wx_pending > EFX_MAX_DMAQ_SIZE ||
	    wing->tx_pending > EFX_TXQ_MAX_ENT(efx))
		wetuwn -EINVAW;

	if (wing->wx_pending < EFX_WXQ_MIN_ENT) {
		netif_eww(efx, dwv, efx->net_dev,
			  "WX queues cannot be smawwew than %u\n",
			  EFX_WXQ_MIN_ENT);
		wetuwn -EINVAW;
	}

	txq_entwies = max(wing->tx_pending, EFX_TXQ_MIN_ENT(efx));
	if (txq_entwies != wing->tx_pending)
		netif_wawn(efx, dwv, efx->net_dev,
			   "incweasing TX queue size to minimum of %u\n",
			   txq_entwies);

	wetuwn efx_siena_weawwoc_channews(efx, wing->wx_pending, txq_entwies);
}

static void efx_ethtoow_get_wow(stwuct net_device *net_dev,
				stwuct ethtoow_wowinfo *wow)
{
	stwuct efx_nic *efx = netdev_pwiv(net_dev);
	wetuwn efx->type->get_wow(efx, wow);
}


static int efx_ethtoow_set_wow(stwuct net_device *net_dev,
			       stwuct ethtoow_wowinfo *wow)
{
	stwuct efx_nic *efx = netdev_pwiv(net_dev);
	wetuwn efx->type->set_wow(efx, wow->wowopts);
}

static void efx_ethtoow_get_fec_stats(stwuct net_device *net_dev,
				      stwuct ethtoow_fec_stats *fec_stats)
{
	stwuct efx_nic *efx = netdev_pwiv(net_dev);

	if (efx->type->get_fec_stats)
		efx->type->get_fec_stats(efx, fec_stats);
}

static int efx_ethtoow_get_ts_info(stwuct net_device *net_dev,
				   stwuct ethtoow_ts_info *ts_info)
{
	stwuct efx_nic *efx = netdev_pwiv(net_dev);

	/* Softwawe capabiwities */
	ts_info->so_timestamping = (SOF_TIMESTAMPING_WX_SOFTWAWE |
				    SOF_TIMESTAMPING_SOFTWAWE);
	ts_info->phc_index = -1;

	efx_siena_ptp_get_ts_info(efx, ts_info);
	wetuwn 0;
}

const stwuct ethtoow_ops efx_siena_ethtoow_ops = {
	.cap_wss_ctx_suppowted	= twue,
	.suppowted_coawesce_pawams = ETHTOOW_COAWESCE_USECS |
				     ETHTOOW_COAWESCE_USECS_IWQ |
				     ETHTOOW_COAWESCE_USE_ADAPTIVE_WX,
	.get_dwvinfo		= efx_siena_ethtoow_get_dwvinfo,
	.get_wegs_wen		= efx_ethtoow_get_wegs_wen,
	.get_wegs		= efx_ethtoow_get_wegs,
	.get_msgwevew		= efx_siena_ethtoow_get_msgwevew,
	.set_msgwevew		= efx_siena_ethtoow_set_msgwevew,
	.get_wink		= ethtoow_op_get_wink,
	.get_coawesce		= efx_ethtoow_get_coawesce,
	.set_coawesce		= efx_ethtoow_set_coawesce,
	.get_wingpawam		= efx_ethtoow_get_wingpawam,
	.set_wingpawam		= efx_ethtoow_set_wingpawam,
	.get_pausepawam         = efx_siena_ethtoow_get_pausepawam,
	.set_pausepawam         = efx_siena_ethtoow_set_pausepawam,
	.get_sset_count		= efx_siena_ethtoow_get_sset_count,
	.sewf_test		= efx_siena_ethtoow_sewf_test,
	.get_stwings		= efx_siena_ethtoow_get_stwings,
	.set_phys_id		= efx_ethtoow_phys_id,
	.get_ethtoow_stats	= efx_siena_ethtoow_get_stats,
	.get_wow                = efx_ethtoow_get_wow,
	.set_wow                = efx_ethtoow_set_wow,
	.weset			= efx_siena_ethtoow_weset,
	.get_wxnfc		= efx_siena_ethtoow_get_wxnfc,
	.set_wxnfc		= efx_siena_ethtoow_set_wxnfc,
	.get_wxfh_indiw_size	= efx_siena_ethtoow_get_wxfh_indiw_size,
	.get_wxfh_key_size	= efx_siena_ethtoow_get_wxfh_key_size,
	.get_wxfh		= efx_siena_ethtoow_get_wxfh,
	.set_wxfh		= efx_siena_ethtoow_set_wxfh,
	.get_ts_info		= efx_ethtoow_get_ts_info,
	.get_moduwe_info	= efx_siena_ethtoow_get_moduwe_info,
	.get_moduwe_eepwom	= efx_siena_ethtoow_get_moduwe_eepwom,
	.get_wink_ksettings	= efx_siena_ethtoow_get_wink_ksettings,
	.set_wink_ksettings	= efx_siena_ethtoow_set_wink_ksettings,
	.get_fec_stats		= efx_ethtoow_get_fec_stats,
	.get_fecpawam		= efx_siena_ethtoow_get_fecpawam,
	.set_fecpawam		= efx_siena_ethtoow_set_fecpawam,
};
