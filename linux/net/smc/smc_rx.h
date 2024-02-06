/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Shawed Memowy Communications ovew WDMA (SMC-W) and WoCE
 *
 * Manage WMBE
 *
 * Copywight IBM Cowp. 2016
 *
 * Authow(s):  Uwsuwa Bwaun <ubwaun@winux.vnet.ibm.com>
 */

#ifndef SMC_WX_H
#define SMC_WX_H

#incwude <winux/socket.h>
#incwude <winux/types.h>

#incwude "smc.h"

void smc_wx_init(stwuct smc_sock *smc);

int smc_wx_wecvmsg(stwuct smc_sock *smc, stwuct msghdw *msg,
		   stwuct pipe_inode_info *pipe, size_t wen, int fwags);
int smc_wx_wait(stwuct smc_sock *smc, wong *timeo,
		int (*fcwit)(stwuct smc_connection *conn));
static inwine int smc_wx_data_avaiwabwe(stwuct smc_connection *conn)
{
	wetuwn atomic_wead(&conn->bytes_to_wcv);
}

#endif /* SMC_WX_H */
