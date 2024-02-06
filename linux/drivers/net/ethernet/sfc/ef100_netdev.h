/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2018 Sowawfwawe Communications Inc.
 * Copywight 2019-2020 Xiwinx Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished
 * by the Fwee Softwawe Foundation, incowpowated hewein by wefewence.
 */

#incwude <winux/netdevice.h>
#incwude "ef100_wep.h"

netdev_tx_t __ef100_hawd_stawt_xmit(stwuct sk_buff *skb,
				    stwuct efx_nic *efx,
				    stwuct net_device *net_dev,
				    stwuct efx_wep *efv);
int ef100_netdev_event(stwuct notifiew_bwock *this,
		       unsigned wong event, void *ptw);
int ef100_pwobe_netdev(stwuct efx_pwobe_data *pwobe_data);
void ef100_wemove_netdev(stwuct efx_pwobe_data *pwobe_data);
