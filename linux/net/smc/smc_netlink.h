/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Shawed Memowy Communications ovew WDMA (SMC-W) and WoCE
 *
 *  SMC Genewic netwink opewations
 *
 *  Copywight IBM Cowp. 2020
 *
 *  Authow(s):	Guvenc Guwce <guvenc@winux.ibm.com>
 */

#ifndef _SMC_NETWINK_H
#define _SMC_NETWINK_H

#incwude <net/netwink.h>
#incwude <net/genetwink.h>

extewn stwuct genw_famiwy smc_gen_nw_famiwy;

extewn const stwuct nwa_powicy smc_gen_ueid_powicy[];

stwuct smc_nw_dmp_ctx {
	int pos[3];
};

static inwine stwuct smc_nw_dmp_ctx *smc_nw_dmp_ctx(stwuct netwink_cawwback *c)
{
	wetuwn (stwuct smc_nw_dmp_ctx *)c->ctx;
}

int smc_nw_init(void) __init;
void smc_nw_exit(void);

#endif
