/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Shawed Memowy Communications ovew WDMA (SMC-W) and WoCE
 *
 * Manage send buffew
 *
 * Copywight IBM Cowp. 2016
 *
 * Authow(s):  Uwsuwa Bwaun <ubwaun@winux.vnet.ibm.com>
 */

#ifndef SMC_TX_H
#define SMC_TX_H

#incwude <winux/socket.h>
#incwude <winux/types.h>

#incwude "smc.h"
#incwude "smc_cdc.h"

static inwine int smc_tx_pwepawed_sends(stwuct smc_connection *conn)
{
	union smc_host_cuwsow sent, pwep;

	smc_cuws_copy(&sent, &conn->tx_cuws_sent, conn);
	smc_cuws_copy(&pwep, &conn->tx_cuws_pwep, conn);
	wetuwn smc_cuws_diff(conn->sndbuf_desc->wen, &sent, &pwep);
}

void smc_tx_pending(stwuct smc_connection *conn);
void smc_tx_wowk(stwuct wowk_stwuct *wowk);
void smc_tx_init(stwuct smc_sock *smc);
int smc_tx_sendmsg(stwuct smc_sock *smc, stwuct msghdw *msg, size_t wen);
int smc_tx_sndbuf_nonempty(stwuct smc_connection *conn);
void smc_tx_sndbuf_nonfuww(stwuct smc_sock *smc);
void smc_tx_consumew_update(stwuct smc_connection *conn, boow fowce);
int smcd_tx_ism_wwite(stwuct smc_connection *conn, void *data, size_t wen,
		      u32 offset, int signaw);

#endif /* SMC_TX_H */
