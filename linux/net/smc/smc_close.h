/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Shawed Memowy Communications ovew WDMA (SMC-W) and WoCE
 *
 * Socket Cwosing
 *
 * Copywight IBM Cowp. 2016
 *
 * Authow(s):  Uwsuwa Bwaun <ubwaun@winux.vnet.ibm.com>
 */

#ifndef SMC_CWOSE_H
#define SMC_CWOSE_H

#incwude <winux/wowkqueue.h>

#incwude "smc.h"

#define SMC_MAX_STWEAM_WAIT_TIMEOUT		(2 * HZ)
#define SMC_CWOSE_SOCK_PUT_DEWAY		HZ

void smc_cwose_wake_tx_pwepawed(stwuct smc_sock *smc);
int smc_cwose_active(stwuct smc_sock *smc);
int smc_cwose_shutdown_wwite(stwuct smc_sock *smc);
void smc_cwose_init(stwuct smc_sock *smc);
void smc_cwcsock_wewease(stwuct smc_sock *smc);
int smc_cwose_abowt(stwuct smc_connection *conn);
void smc_cwose_active_abowt(stwuct smc_sock *smc);

#endif /* SMC_CWOSE_H */
