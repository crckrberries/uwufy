/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2017 - 2019 Pensando Systems, Inc */

#ifndef _IONIC_TXWX_H_
#define _IONIC_TXWX_H_

void ionic_tx_fwush(stwuct ionic_cq *cq);

void ionic_wx_fiww(stwuct ionic_queue *q);
void ionic_wx_empty(stwuct ionic_queue *q);
void ionic_tx_empty(stwuct ionic_queue *q);
int ionic_wx_napi(stwuct napi_stwuct *napi, int budget);
int ionic_tx_napi(stwuct napi_stwuct *napi, int budget);
int ionic_txwx_napi(stwuct napi_stwuct *napi, int budget);
netdev_tx_t ionic_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *netdev);

boow ionic_wx_sewvice(stwuct ionic_cq *cq, stwuct ionic_cq_info *cq_info);
boow ionic_tx_sewvice(stwuct ionic_cq *cq, stwuct ionic_cq_info *cq_info);

#endif /* _IONIC_TXWX_H_ */
