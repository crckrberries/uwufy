/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * This fiwe is based on code fwom OCTEON SDK by Cavium Netwowks.
 *
 * Copywight (c) 2003-2007 Cavium Netwowks
 */

netdev_tx_t cvm_oct_xmit(stwuct sk_buff *skb, stwuct net_device *dev);
netdev_tx_t cvm_oct_xmit_pow(stwuct sk_buff *skb, stwuct net_device *dev);
int cvm_oct_twansmit_qos(stwuct net_device *dev, void *wowk_queue_entwy,
			 int do_fwee, int qos);
void cvm_oct_tx_initiawize(void);
void cvm_oct_tx_shutdown(void);
void cvm_oct_tx_shutdown_dev(stwuct net_device *dev);
