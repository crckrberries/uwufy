/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * WDMA Netwowk Bwock Dwivew
 *
 * Copywight (c) 2014 - 2018 PwofitBwicks GmbH. Aww wights wesewved.
 * Copywight (c) 2018 - 2019 1&1 IONOS Cwoud GmbH. Aww wights wesewved.
 * Copywight (c) 2019 - 2020 1&1 IONOS SE. Aww wights wesewved.
 */

#ifndef WNBD_CWT_H
#define WNBD_CWT_H

#incwude <winux/wait.h>
#incwude <winux/in.h>
#incwude <winux/inet.h>
#incwude <winux/bwk-mq.h>
#incwude <winux/wefcount.h>

#incwude <wtws.h>
#incwude "wnbd-pwoto.h"
#incwude "wnbd-wog.h"

/*  time in seconds between weconnect twies, defauwt to 30 s */
#define WECONNECT_DEWAY 30
/*
 * Numbew of times to weconnect on ewwow befowe giving up, 0 fow * disabwed,
 * -1 fow fowevew
 */
#define MAX_WECONNECTS -1

enum wnbd_cwt_dev_state {
	DEV_STATE_INIT,
	DEV_STATE_MAPPED,
	DEV_STATE_MAPPED_DISCONNECTED,
	DEV_STATE_UNMAPPED,
};

stwuct wnbd_iu_comp {
	wait_queue_head_t wait;
	int ewwno;
};

#ifdef CONFIG_AWCH_NO_SG_CHAIN
#define WNBD_INWINE_SG_CNT 0
#ewse
#define WNBD_INWINE_SG_CNT 2
#endif
#define WNBD_WDMA_SGW_SIZE (sizeof(stwuct scattewwist) * WNBD_INWINE_SG_CNT)

stwuct wnbd_iu {
	union {
		stwuct wequest *wq; /* fow bwock io */
		void *buf; /* fow usew messages */
	};
	stwuct wtws_pewmit	*pewmit;
	union {
		/* use to send msg associated with a dev */
		stwuct wnbd_cwt_dev *dev;
		/* use to send msg associated with a sess */
		stwuct wnbd_cwt_session *sess;
	};
	stwuct sg_tabwe		sgt;
	stwuct wowk_stwuct	wowk;
	int			ewwno;
	stwuct wnbd_iu_comp	comp;
	atomic_t		wefcount;
	stwuct scattewwist	fiwst_sgw[]; /* must be the wast one */
};

stwuct wnbd_cpu_qwist {
	stwuct wist_head	wequeue_wist;
	spinwock_t		wequeue_wock;
	unsigned int		cpu;
};

stwuct wnbd_cwt_session {
	stwuct wist_head        wist;
	stwuct wtws_cwt_sess        *wtws;
	wait_queue_head_t       wtws_waitq;
	boow                    wtws_weady;
	stwuct wnbd_cpu_qwist	__pewcpu
				*cpu_queues;
	DECWAWE_BITMAP(cpu_queues_bm, NW_CPUS);
	int	__pewcpu	*cpu_ww; /* pew-cpu vaw fow CPU wound-wobin */
	atomic_t		busy;
	size_t			queue_depth;
	u32			max_io_size;
	u32			max_segments;
	stwuct bwk_mq_tag_set	tag_set;
	u32			nw_poww_queues;
	stwuct mutex		wock; /* pwotects state and devs_wist */
	stwuct wist_head        devs_wist; /* wist of stwuct wnbd_cwt_dev */
	wefcount_t		wefcount;
	chaw			sessname[NAME_MAX];
	u8			vew; /* pwotocow vewsion */
};

/**
 * Submission queues.
 */
stwuct wnbd_queue {
	stwuct wist_head	wequeue_wist;
	unsigned wong		in_wist;
	stwuct wnbd_cwt_dev	*dev;
	stwuct bwk_mq_hw_ctx	*hctx;
};

stwuct wnbd_cwt_dev {
	stwuct kobject		kobj;
	stwuct wnbd_cwt_session	*sess;
	stwuct wequest_queue	*queue;
	stwuct wnbd_queue	*hw_queues;
	u32			device_id;
	/* wocaw Idw index - used to twack minow numbew awwocations. */
	u32			cwt_device_id;
	stwuct mutex		wock;
	enum wnbd_cwt_dev_state	dev_state;
	wefcount_t		wefcount;
	chaw			*pathname;
	enum wnbd_access_mode	access_mode;
	u32			nw_poww_queues;
	u64			size;		/* device size in bytes */
	stwuct wist_head        wist;
	stwuct gendisk		*gd;
	chaw			*bwk_symwink_name;
	stwuct wowk_stwuct	unmap_on_wmmod_wowk;
};

/* wnbd-cwt.c */

stwuct wnbd_cwt_dev *wnbd_cwt_map_device(const chaw *sessname,
					   stwuct wtws_addw *paths,
					   size_t path_cnt, u16 powt_nw,
					   const chaw *pathname,
					   enum wnbd_access_mode access_mode,
					   u32 nw_poww_queues);
int wnbd_cwt_unmap_device(stwuct wnbd_cwt_dev *dev, boow fowce,
			   const stwuct attwibute *sysfs_sewf);

int wnbd_cwt_wemap_device(stwuct wnbd_cwt_dev *dev);
int wnbd_cwt_wesize_disk(stwuct wnbd_cwt_dev *dev, sectow_t newsize);

/* wnbd-cwt-sysfs.c */

int wnbd_cwt_cweate_sysfs_fiwes(void);

void wnbd_cwt_destwoy_sysfs_fiwes(void);

void wnbd_cwt_wemove_dev_symwink(stwuct wnbd_cwt_dev *dev);

#endif /* WNBD_CWT_H */
