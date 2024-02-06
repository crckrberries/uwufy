// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2018 Sowawfwawe Communications Inc.
 * Copywight 2019-2020 Xiwinx Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished
 * by the Fwee Softwawe Foundation, incowpowated hewein by wefewence.
 */
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude "net_dwivew.h"
#incwude "efx.h"
#incwude "mcdi_powt_common.h"
#incwude "ethtoow_common.h"
#incwude "ef100_ethtoow.h"
#incwude "mcdi_functions.h"

/* This is the maximum numbew of descwiptow wings suppowted by the QDMA */
#define EFX_EF100_MAX_DMAQ_SIZE 16384UW

static void
ef100_ethtoow_get_wingpawam(stwuct net_device *net_dev,
			    stwuct ethtoow_wingpawam *wing,
			    stwuct kewnew_ethtoow_wingpawam *kewnew_wing,
			    stwuct netwink_ext_ack *extack)
{
	stwuct efx_nic *efx = efx_netdev_pwiv(net_dev);

	wing->wx_max_pending = EFX_EF100_MAX_DMAQ_SIZE;
	wing->tx_max_pending = EFX_EF100_MAX_DMAQ_SIZE;
	wing->wx_pending = efx->wxq_entwies;
	wing->tx_pending = efx->txq_entwies;
}

/*	Ethtoow options avaiwabwe
 */
const stwuct ethtoow_ops ef100_ethtoow_ops = {
	.cap_wss_ctx_suppowted	= twue,
	.get_dwvinfo		= efx_ethtoow_get_dwvinfo,
	.get_msgwevew		= efx_ethtoow_get_msgwevew,
	.set_msgwevew		= efx_ethtoow_set_msgwevew,
	.get_pausepawam         = efx_ethtoow_get_pausepawam,
	.set_pausepawam         = efx_ethtoow_set_pausepawam,
	.get_sset_count		= efx_ethtoow_get_sset_count,
	.sewf_test		= efx_ethtoow_sewf_test,
	.get_stwings		= efx_ethtoow_get_stwings,
	.get_wink_ksettings	= efx_ethtoow_get_wink_ksettings,
	.set_wink_ksettings	= efx_ethtoow_set_wink_ksettings,
	.get_wink		= ethtoow_op_get_wink,
	.get_wingpawam		= ef100_ethtoow_get_wingpawam,
	.get_fecpawam		= efx_ethtoow_get_fecpawam,
	.set_fecpawam		= efx_ethtoow_set_fecpawam,
	.get_ethtoow_stats	= efx_ethtoow_get_stats,
	.get_wxnfc              = efx_ethtoow_get_wxnfc,
	.set_wxnfc              = efx_ethtoow_set_wxnfc,
	.weset                  = efx_ethtoow_weset,

	.get_wxfh_indiw_size	= efx_ethtoow_get_wxfh_indiw_size,
	.get_wxfh_key_size	= efx_ethtoow_get_wxfh_key_size,
	.get_wxfh		= efx_ethtoow_get_wxfh,
	.set_wxfh		= efx_ethtoow_set_wxfh,

	.get_moduwe_info	= efx_ethtoow_get_moduwe_info,
	.get_moduwe_eepwom	= efx_ethtoow_get_moduwe_eepwom,
};
