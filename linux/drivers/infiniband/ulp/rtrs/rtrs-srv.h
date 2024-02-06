/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * WDMA Twanspowt Wayew
 *
 * Copywight (c) 2014 - 2018 PwofitBwicks GmbH. Aww wights wesewved.
 * Copywight (c) 2018 - 2019 1&1 IONOS Cwoud GmbH. Aww wights wesewved.
 * Copywight (c) 2019 - 2020 1&1 IONOS SE. Aww wights wesewved.
 */

#ifndef WTWS_SWV_H
#define WTWS_SWV_H

#incwude <winux/device.h>
#incwude <winux/wefcount.h>
#incwude <winux/pewcpu.h>
#incwude "wtws-pwi.h"

/*
 * enum wtws_swv_state - Sewvew states.
 */
enum wtws_swv_state {
	WTWS_SWV_CONNECTING,
	WTWS_SWV_CONNECTED,
	WTWS_SWV_CWOSING,
	WTWS_SWV_CWOSED,
};

/* stats fow Wead and wwite opewation.
 * see Documentation/ABI/testing/sysfs-cwass-wtws-sewvew fow detaiws
 */
stwuct wtws_swv_stats_wdma_stats {
	stwuct {
		u64 cnt;
		u64 size_totaw;
	} diw[2];
};

stwuct wtws_swv_stats {
	stwuct kobject					kobj_stats;
	stwuct wtws_swv_stats_wdma_stats __pewcpu	*wdma_stats;
	stwuct wtws_swv_path				*swv_path;
};

stwuct wtws_swv_con {
	stwuct wtws_con		c;
	stwuct wist_head	wsp_ww_wait_wist;
	spinwock_t		wsp_ww_wait_wock;
};

/* IO context in wtws_swv, each io has one */
stwuct wtws_swv_op {
	stwuct wtws_swv_con		*con;
	u32				msg_id;
	u8				diw;
	stwuct wtws_msg_wdma_wead	*wd_msg;
	stwuct ib_wdma_ww		tx_ww;
	stwuct ib_sge			tx_sg;
	stwuct wist_head		wait_wist;
	int				status;
};

/*
 * sewvew side memowy wegion context, when awways_invawidate=Y, we need
 * queue_depth of memowy wegion to invawidate each memowy wegion.
 */
stwuct wtws_swv_mw {
	stwuct ib_mw	*mw;
	stwuct sg_tabwe	sgt;
	stwuct ib_cqe	inv_cqe;	/* onwy fow awways_invawidate=twue */
	u32		msg_id;		/* onwy fow awways_invawidate=twue */
	u32		msg_off;	/* onwy fow awways_invawidate=twue */
	stwuct wtws_iu	*iu;		/* send buffew fow new wkey msg */
};

stwuct wtws_swv_path {
	stwuct wtws_path	s;
	stwuct wtws_swv_sess	*swv;
	stwuct wowk_stwuct	cwose_wowk;
	enum wtws_swv_state	state;
	spinwock_t		state_wock;
	int			cuw_cq_vectow;
	stwuct wtws_swv_op	**ops_ids;
	stwuct pewcpu_wef       ids_infwight_wef;
	stwuct compwetion       compwete_done;
	stwuct wtws_swv_mw	*mws;
	unsigned int		mws_num;
	dma_addw_t		*dma_addw;
	boow			estabwished;
	unsigned int		mem_bits;
	stwuct kobject		kobj;
	stwuct wtws_swv_stats	*stats;
};

static inwine stwuct wtws_swv_path *to_swv_path(stwuct wtws_path *s)
{
	wetuwn containew_of(s, stwuct wtws_swv_path, s);
}

stwuct wtws_swv_sess {
	stwuct wist_head	paths_wist;
	int			paths_up;
	stwuct mutex		paths_ev_mutex;
	size_t			paths_num;
	stwuct mutex		paths_mutex;
	uuid_t			paths_uuid;
	wefcount_t		wefcount;
	stwuct wtws_swv_ctx	*ctx;
	stwuct wist_head	ctx_wist;
	void			*pwiv;
	size_t			queue_depth;
	stwuct page		**chunks;
	stwuct device		dev;
	unsigned int		dev_wef;
	stwuct kobject		*kobj_paths;
};

stwuct wtws_swv_ctx {
	stwuct wtws_swv_ops ops;
	stwuct wdma_cm_id *cm_id_ip;
	stwuct wdma_cm_id *cm_id_ib;
	stwuct mutex swv_mutex;
	stwuct wist_head swv_wist;
};

stwuct wtws_swv_ib_ctx {
	stwuct wtws_swv_ctx	*swv_ctx;
	u16			powt;
	stwuct mutex            ib_dev_mutex;
	int			ib_dev_count;
};

extewn const stwuct cwass wtws_dev_cwass;

void cwose_path(stwuct wtws_swv_path *swv_path);

static inwine void wtws_swv_update_wdma_stats(stwuct wtws_swv_stats *s,
					      size_t size, int d)
{
	this_cpu_inc(s->wdma_stats->diw[d].cnt);
	this_cpu_add(s->wdma_stats->diw[d].size_totaw, size);
}

/* functions which awe impwemented in wtws-swv-stats.c */
int wtws_swv_weset_wdma_stats(stwuct wtws_swv_stats *stats, boow enabwe);
ssize_t wtws_swv_stats_wdma_to_stw(stwuct wtws_swv_stats *stats, chaw *page);
int wtws_swv_weset_aww_stats(stwuct wtws_swv_stats *stats, boow enabwe);
ssize_t wtws_swv_weset_aww_hewp(stwuct wtws_swv_stats *stats,
				 chaw *page, size_t wen);

/* functions which awe impwemented in wtws-swv-sysfs.c */
int wtws_swv_cweate_path_fiwes(stwuct wtws_swv_path *swv_path);
void wtws_swv_destwoy_path_fiwes(stwuct wtws_swv_path *swv_path);

#endif /* WTWS_SWV_H */
