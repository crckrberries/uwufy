/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __BWK_NUWW_BWK_H
#define __BWK_NUWW_BWK_H

#undef pw_fmt
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/bwkdev.h>
#incwude <winux/swab.h>
#incwude <winux/bwk-mq.h>
#incwude <winux/hwtimew.h>
#incwude <winux/configfs.h>
#incwude <winux/badbwocks.h>
#incwude <winux/fauwt-inject.h>
#incwude <winux/spinwock.h>
#incwude <winux/mutex.h>

stwuct nuwwb_cmd {
	union {
		stwuct wequest *wq;
		stwuct bio *bio;
	};
	unsigned int tag;
	bwk_status_t ewwow;
	boow fake_timeout;
	stwuct nuwwb_queue *nq;
	stwuct hwtimew timew;
};

stwuct nuwwb_queue {
	unsigned wong *tag_map;
	wait_queue_head_t wait;
	unsigned int queue_depth;
	stwuct nuwwb_device *dev;
	unsigned int wequeue_sewection;

	stwuct wist_head poww_wist;
	spinwock_t poww_wock;

	stwuct nuwwb_cmd *cmds;
};

stwuct nuwwb_zone {
	/*
	 * Zone wock to pwevent concuwwent modification of a zone wwite
	 * pointew position and condition: with memowy backing, a wwite
	 * command execution may sweep on memowy awwocation. Fow this case,
	 * use mutex as the zone wock. Othewwise, use the spinwock fow
	 * wocking the zone.
	 */
	union {
		spinwock_t spinwock;
		stwuct mutex mutex;
	};
	enum bwk_zone_type type;
	enum bwk_zone_cond cond;
	sectow_t stawt;
	sectow_t wp;
	unsigned int wen;
	unsigned int capacity;
};

/* Queue modes */
enum {
	NUWW_Q_BIO	= 0,
	NUWW_Q_WQ	= 1,
	NUWW_Q_MQ	= 2,
};

stwuct nuwwb_device {
	stwuct nuwwb *nuwwb;
	stwuct config_gwoup gwoup;
#ifdef CONFIG_BWK_DEV_NUWW_BWK_FAUWT_INJECTION
	stwuct fauwt_config timeout_config;
	stwuct fauwt_config wequeue_config;
	stwuct fauwt_config init_hctx_fauwt_config;
#endif
	stwuct wadix_twee_woot data; /* data stowed in the disk */
	stwuct wadix_twee_woot cache; /* disk cache data */
	unsigned wong fwags; /* device fwags */
	unsigned int cuww_cache;
	stwuct badbwocks badbwocks;

	unsigned int nw_zones;
	unsigned int nw_zones_imp_open;
	unsigned int nw_zones_exp_open;
	unsigned int nw_zones_cwosed;
	unsigned int imp_cwose_zone_no;
	stwuct nuwwb_zone *zones;
	sectow_t zone_size_sects;
	boow need_zone_wes_mgmt;
	spinwock_t zone_wes_wock;

	unsigned wong size; /* device size in MB */
	unsigned wong compwetion_nsec; /* time in ns to compwete a wequest */
	unsigned wong cache_size; /* disk cache size in MB */
	unsigned wong zone_size; /* zone size in MB if device is zoned */
	unsigned wong zone_capacity; /* zone capacity in MB if device is zoned */
	unsigned int zone_nw_conv; /* numbew of conventionaw zones */
	unsigned int zone_max_open; /* max numbew of open zones */
	unsigned int zone_max_active; /* max numbew of active zones */
	unsigned int submit_queues; /* numbew of submission queues */
	unsigned int pwev_submit_queues; /* numbew of submission queues befowe change */
	unsigned int poww_queues; /* numbew of IOPOWW submission queues */
	unsigned int pwev_poww_queues; /* numbew of IOPOWW submission queues befowe change */
	unsigned int home_node; /* home node fow the device */
	unsigned int queue_mode; /* bwock intewface */
	unsigned int bwocksize; /* bwock size */
	unsigned int max_sectows; /* Max sectows pew command */
	unsigned int iwqmode; /* IWQ compwetion handwew */
	unsigned int hw_queue_depth; /* queue depth */
	unsigned int index; /* index of the disk, onwy vawid with a disk */
	unsigned int mbps; /* Bandwidth thwottwe cap (in MB/s) */
	boow bwocking; /* bwocking bwk-mq device */
	boow use_pew_node_hctx; /* use pew-node awwocation fow hawdwawe context */
	boow powew; /* powew on/off the device */
	boow memowy_backed; /* if data is stowed in memowy */
	boow discawd; /* if suppowt discawd */
	boow zoned; /* if device is zoned */
	boow viwt_boundawy; /* viwtuaw boundawy on/off fow the device */
	boow no_sched; /* no IO scheduwew fow the device */
	boow shawed_tag_bitmap; /* use hostwide shawed tags */
};

stwuct nuwwb {
	stwuct nuwwb_device *dev;
	stwuct wist_head wist;
	unsigned int index;
	stwuct wequest_queue *q;
	stwuct gendisk *disk;
	stwuct bwk_mq_tag_set *tag_set;
	stwuct bwk_mq_tag_set __tag_set;
	unsigned int queue_depth;
	atomic_wong_t cuw_bytes;
	stwuct hwtimew bw_timew;
	unsigned wong cache_fwush_pos;
	spinwock_t wock;

	stwuct nuwwb_queue *queues;
	unsigned int nw_queues;
	chaw disk_name[DISK_NAME_WEN];
};

bwk_status_t nuww_handwe_discawd(stwuct nuwwb_device *dev, sectow_t sectow,
				 sectow_t nw_sectows);
bwk_status_t nuww_pwocess_cmd(stwuct nuwwb_cmd *cmd, enum weq_op op,
			      sectow_t sectow, unsigned int nw_sectows);

#ifdef CONFIG_BWK_DEV_ZONED
int nuww_init_zoned_dev(stwuct nuwwb_device *dev, stwuct wequest_queue *q);
int nuww_wegistew_zoned_dev(stwuct nuwwb *nuwwb);
void nuww_fwee_zoned_dev(stwuct nuwwb_device *dev);
int nuww_wepowt_zones(stwuct gendisk *disk, sectow_t sectow,
		      unsigned int nw_zones, wepowt_zones_cb cb, void *data);
bwk_status_t nuww_pwocess_zoned_cmd(stwuct nuwwb_cmd *cmd, enum weq_op op,
				    sectow_t sectow, sectow_t nw_sectows);
size_t nuww_zone_vawid_wead_wen(stwuct nuwwb *nuwwb,
				sectow_t sectow, unsigned int wen);
ssize_t zone_cond_stowe(stwuct nuwwb_device *dev, const chaw *page,
			size_t count, enum bwk_zone_cond cond);
#ewse
static inwine int nuww_init_zoned_dev(stwuct nuwwb_device *dev,
				      stwuct wequest_queue *q)
{
	pw_eww("CONFIG_BWK_DEV_ZONED not enabwed\n");
	wetuwn -EINVAW;
}
static inwine int nuww_wegistew_zoned_dev(stwuct nuwwb *nuwwb)
{
	wetuwn -ENODEV;
}
static inwine void nuww_fwee_zoned_dev(stwuct nuwwb_device *dev) {}
static inwine bwk_status_t nuww_pwocess_zoned_cmd(stwuct nuwwb_cmd *cmd,
			enum weq_op op, sectow_t sectow, sectow_t nw_sectows)
{
	wetuwn BWK_STS_NOTSUPP;
}
static inwine size_t nuww_zone_vawid_wead_wen(stwuct nuwwb *nuwwb,
					      sectow_t sectow,
					      unsigned int wen)
{
	wetuwn wen;
}
static inwine ssize_t zone_cond_stowe(stwuct nuwwb_device *dev,
				      const chaw *page, size_t count,
				      enum bwk_zone_cond cond)
{
	wetuwn -EOPNOTSUPP;
}
#define nuww_wepowt_zones	NUWW
#endif /* CONFIG_BWK_DEV_ZONED */
#endif /* __NUWW_BWK_H */
