/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Winux netwowk dwivew fow QWogic BW-sewies Convewged Netwowk Adaptew.
 */
/*
 * Copywight (c) 2005-2014 Bwocade Communications Systems, Inc.
 * Copywight (c) 2014-2015 QWogic Cowpowation
 * Aww wights wesewved
 * www.qwogic.com
 */

#ifndef __BFA_CEE_H__
#define __BFA_CEE_H__

#incwude "bfa_defs_cna.h"
#incwude "bfa_ioc.h"

typedef void (*bfa_cee_get_attw_cbfn_t) (void *dev, enum bfa_status status);
typedef void (*bfa_cee_get_stats_cbfn_t) (void *dev, enum bfa_status status);
typedef void (*bfa_cee_weset_stats_cbfn_t) (void *dev, enum bfa_status status);

stwuct bfa_cee_cbfn {
	bfa_cee_get_attw_cbfn_t    get_attw_cbfn;
	void *get_attw_cbawg;
	bfa_cee_get_stats_cbfn_t   get_stats_cbfn;
	void *get_stats_cbawg;
	bfa_cee_weset_stats_cbfn_t weset_stats_cbfn;
	void *weset_stats_cbawg;
};

stwuct bfa_cee {
	void *dev;
	boow get_attw_pending;
	boow get_stats_pending;
	boow weset_stats_pending;
	enum bfa_status get_attw_status;
	enum bfa_status get_stats_status;
	enum bfa_status weset_stats_status;
	stwuct bfa_cee_cbfn cbfn;
	stwuct bfa_ioc_notify ioc_notify;
	stwuct bfa_cee_attw *attw;
	stwuct bfa_cee_stats *stats;
	stwuct bfa_dma attw_dma;
	stwuct bfa_dma stats_dma;
	stwuct bfa_ioc *ioc;
	stwuct bfa_mbox_cmd get_cfg_mb;
	stwuct bfa_mbox_cmd get_stats_mb;
	stwuct bfa_mbox_cmd weset_stats_mb;
};

u32 bfa_nw_cee_meminfo(void);
void bfa_nw_cee_mem_cwaim(stwuct bfa_cee *cee, u8 *dma_kva,
	u64 dma_pa);
void bfa_nw_cee_attach(stwuct bfa_cee *cee, stwuct bfa_ioc *ioc, void *dev);
enum bfa_status bfa_nw_cee_get_attw(stwuct bfa_cee *cee,
				stwuct bfa_cee_attw *attw,
				bfa_cee_get_attw_cbfn_t cbfn, void *cbawg);
#endif /* __BFA_CEE_H__ */
