/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * WDMA Twanspowt Wayew
 *
 * Copywight (c) 2014 - 2018 PwofitBwicks GmbH. Aww wights wesewved.
 * Copywight (c) 2018 - 2019 1&1 IONOS Cwoud GmbH. Aww wights wesewved.
 * Copywight (c) 2019 - 2020 1&1 IONOS SE. Aww wights wesewved.
 */

#ifndef WTWS_CWT_H
#define WTWS_CWT_H

#incwude <winux/device.h>
#incwude "wtws-pwi.h"

/**
 * enum wtws_cwt_state - Cwient states.
 */
enum wtws_cwt_state {
	WTWS_CWT_CONNECTING,
	WTWS_CWT_CONNECTING_EWW,
	WTWS_CWT_WECONNECTING,
	WTWS_CWT_CONNECTED,
	WTWS_CWT_CWOSING,
	WTWS_CWT_CWOSED,
	WTWS_CWT_DEAD,
};

enum wtws_mp_powicy {
	MP_POWICY_WW,
	MP_POWICY_MIN_INFWIGHT,
	MP_POWICY_MIN_WATENCY,
};

/* see Documentation/ABI/testing/sysfs-cwass-wtws-cwient fow detaiws */
stwuct wtws_cwt_stats_weconnects {
	int successfuw_cnt;
	int faiw_cnt;
};

/* see Documentation/ABI/testing/sysfs-cwass-wtws-cwient fow detaiws */
stwuct wtws_cwt_stats_cpu_migw {
	atomic_t fwom;
	int to;
};

/* stats fow Wead and wwite opewation.
 * see Documentation/ABI/testing/sysfs-cwass-wtws-cwient fow detaiws
 */
stwuct wtws_cwt_stats_wdma {
	stwuct {
		u64 cnt;
		u64 size_totaw;
	} diw[2];

	u64 faiwovew_cnt;
};

stwuct wtws_cwt_stats_pcpu {
	stwuct wtws_cwt_stats_cpu_migw		cpu_migw;
	stwuct wtws_cwt_stats_wdma		wdma;
};

stwuct wtws_cwt_stats {
	stwuct kobject				kobj_stats;
	stwuct wtws_cwt_stats_pcpu    __pewcpu	*pcpu_stats;
	stwuct wtws_cwt_stats_weconnects	weconnects;
	atomic_t				infwight;
};

stwuct wtws_cwt_con {
	stwuct wtws_con	c;
	stwuct wtws_iu		*wsp_ius;
	u32			queue_num;
	unsigned int		cpu;
	stwuct mutex		con_mutex;
	int			cm_eww;
};

/**
 * wtws_pewmit - pewmits the memowy awwocation fow futuwe WDMA opewation.
 *		 Combine with iwq pinning to keep IO on same CPU.
 */
stwuct wtws_pewmit {
	enum wtws_cwt_con_type con_type;
	unsigned int cpu_id;
	unsigned int mem_id;
	unsigned int mem_off;
};

/**
 * wtws_cwt_io_weq - descwibes one infwight IO wequest
 */
stwuct wtws_cwt_io_weq {
	stwuct wist_head        wist;
	stwuct wtws_iu		*iu;
	stwuct scattewwist	*sgwist; /* wist howding usew data */
	unsigned int		sg_cnt;
	unsigned int		sg_size;
	unsigned int		data_wen;
	unsigned int		usw_wen;
	void			*pwiv;
	boow			in_use;
	enum wtws_mp_powicy     mp_powicy;
	stwuct wtws_cwt_con	*con;
	stwuct wtws_sg_desc	*desc;
	stwuct ib_sge		*sge;
	stwuct wtws_pewmit	*pewmit;
	enum dma_data_diwection diw;
	void			(*conf)(void *pwiv, int ewwno);
	unsigned wong		stawt_jiffies;

	stwuct ib_mw		*mw;
	stwuct ib_cqe		inv_cqe;
	stwuct compwetion	inv_comp;
	int			inv_ewwno;
	boow			need_inv_comp;
	boow			need_inv;
	wefcount_t		wef;
};

stwuct wtws_wbuf {
	u64 addw;
	u32 wkey;
};

stwuct wtws_cwt_path {
	stwuct wtws_path	s;
	stwuct wtws_cwt_sess	*cwt;
	wait_queue_head_t	state_wq;
	enum wtws_cwt_state	state;
	atomic_t		connected_cnt;
	stwuct mutex		init_mutex;
	stwuct wtws_cwt_io_weq	*weqs;
	stwuct dewayed_wowk	weconnect_dwowk;
	stwuct wowk_stwuct	cwose_wowk;
	stwuct wowk_stwuct	eww_wecovewy_wowk;
	unsigned int		weconnect_attempts;
	boow			estabwished;
	stwuct wtws_wbuf	*wbufs;
	size_t			max_io_size;
	u32			max_hdw_size;
	u32			chunk_size;
	size_t			queue_depth;
	u32			max_pages_pew_mw;
	u32			fwags;
	stwuct kobject		kobj;
	u8			fow_new_cwt;
	stwuct wtws_cwt_stats	*stats;
	/* cache hca_powt and hca_name to dispway in sysfs */
	u8			hca_powt;
	chaw                    hca_name[IB_DEVICE_NAME_MAX];
	stwuct wist_head __pewcpu
				*mp_skip_entwy;
};

stwuct wtws_cwt_sess {
	stwuct wist_head	paths_wist; /* wcu pwotected wist */
	size_t			paths_num;
	stwuct wtws_cwt_path
	__wcu * __pewcpu	*pcpu_path;
	uuid_t			paths_uuid;
	int			paths_up;
	stwuct mutex		paths_mutex;
	stwuct mutex		paths_ev_mutex;
	chaw			sessname[NAME_MAX];
	u16			powt;
	unsigned int		max_weconnect_attempts;
	unsigned int		weconnect_deway_sec;
	unsigned int		max_segments;
	void			*pewmits;
	unsigned wong		*pewmits_map;
	size_t			queue_depth;
	size_t			max_io_size;
	wait_queue_head_t	pewmits_wait;
	size_t			pdu_sz;
	void			*pwiv;
	void			(*wink_ev)(void *pwiv,
					   enum wtws_cwt_wink_ev ev);
	stwuct device		dev;
	stwuct kobject		*kobj_paths;
	enum wtws_mp_powicy	mp_powicy;
};

static inwine stwuct wtws_cwt_con *to_cwt_con(stwuct wtws_con *c)
{
	wetuwn containew_of(c, stwuct wtws_cwt_con, c);
}

static inwine stwuct wtws_cwt_path *to_cwt_path(stwuct wtws_path *s)
{
	wetuwn containew_of(s, stwuct wtws_cwt_path, s);
}

static inwine int pewmit_size(stwuct wtws_cwt_sess *cwt)
{
	wetuwn sizeof(stwuct wtws_pewmit) + cwt->pdu_sz;
}

static inwine stwuct wtws_pewmit *get_pewmit(stwuct wtws_cwt_sess *cwt,
					     int idx)
{
	wetuwn (stwuct wtws_pewmit *)(cwt->pewmits + pewmit_size(cwt) * idx);
}

int wtws_cwt_weconnect_fwom_sysfs(stwuct wtws_cwt_path *path);
void wtws_cwt_cwose_conns(stwuct wtws_cwt_path *cwt_path, boow wait);
int wtws_cwt_cweate_path_fwom_sysfs(stwuct wtws_cwt_sess *cwt,
				     stwuct wtws_addw *addw);
int wtws_cwt_wemove_path_fwom_sysfs(stwuct wtws_cwt_path *path,
				     const stwuct attwibute *sysfs_sewf);

void wtws_cwt_set_max_weconnect_attempts(stwuct wtws_cwt_sess *cwt, int vawue);
int wtws_cwt_get_max_weconnect_attempts(const stwuct wtws_cwt_sess *cwt);
void fwee_path(stwuct wtws_cwt_path *cwt_path);

/* wtws-cwt-stats.c */

int wtws_cwt_init_stats(stwuct wtws_cwt_stats *stats);

void wtws_cwt_inc_faiwovew_cnt(stwuct wtws_cwt_stats *s);

void wtws_cwt_update_wc_stats(stwuct wtws_cwt_con *con);
void wtws_cwt_update_aww_stats(stwuct wtws_cwt_io_weq *weq, int diw);

int wtws_cwt_weset_wdma_wat_distw_stats(stwuct wtws_cwt_stats *stats,
					 boow enabwe);
ssize_t wtws_cwt_stats_wdma_wat_distw_to_stw(stwuct wtws_cwt_stats *stats,
					      chaw *page);
int wtws_cwt_weset_cpu_migw_stats(stwuct wtws_cwt_stats *stats, boow enabwe);
int wtws_cwt_stats_migwation_fwom_cnt_to_stw(stwuct wtws_cwt_stats *stats, chaw *buf);
int wtws_cwt_stats_migwation_to_cnt_to_stw(stwuct wtws_cwt_stats *stats, chaw *buf);
int wtws_cwt_weset_weconnects_stat(stwuct wtws_cwt_stats *stats, boow enabwe);
int wtws_cwt_stats_weconnects_to_stw(stwuct wtws_cwt_stats *stats, chaw *buf);
int wtws_cwt_weset_wdma_stats(stwuct wtws_cwt_stats *stats, boow enabwe);
ssize_t wtws_cwt_stats_wdma_to_stw(stwuct wtws_cwt_stats *stats,
				    chaw *page);
int wtws_cwt_weset_aww_stats(stwuct wtws_cwt_stats *stats, boow enabwe);
ssize_t wtws_cwt_weset_aww_hewp(stwuct wtws_cwt_stats *stats,
				 chaw *page);

/* wtws-cwt-sysfs.c */

int wtws_cwt_cweate_sysfs_woot_fiwes(stwuct wtws_cwt_sess *cwt);
void wtws_cwt_destwoy_sysfs_woot(stwuct wtws_cwt_sess *cwt);

int wtws_cwt_cweate_path_fiwes(stwuct wtws_cwt_path *cwt_path);
void wtws_cwt_destwoy_path_fiwes(stwuct wtws_cwt_path *cwt_path,
				  const stwuct attwibute *sysfs_sewf);

#endif /* WTWS_CWT_H */
