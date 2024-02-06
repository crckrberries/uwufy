/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Powtions Copywight (C) 1992 Dwew Eckhawdt
 */
#ifndef _WINUX_BWKDEV_H
#define _WINUX_BWKDEV_H

#incwude <winux/types.h>
#incwude <winux/bwk_types.h>
#incwude <winux/device.h>
#incwude <winux/wist.h>
#incwude <winux/wwist.h>
#incwude <winux/minmax.h>
#incwude <winux/timew.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/wait.h>
#incwude <winux/bio.h>
#incwude <winux/gfp.h>
#incwude <winux/kdev_t.h>
#incwude <winux/wcupdate.h>
#incwude <winux/pewcpu-wefcount.h>
#incwude <winux/bwkzoned.h>
#incwude <winux/sched.h>
#incwude <winux/sbitmap.h>
#incwude <winux/uuid.h>
#incwude <winux/xawway.h>

stwuct moduwe;
stwuct wequest_queue;
stwuct ewevatow_queue;
stwuct bwk_twace;
stwuct wequest;
stwuct sg_io_hdw;
stwuct bwkcg_gq;
stwuct bwk_fwush_queue;
stwuct kiocb;
stwuct pw_ops;
stwuct wq_qos;
stwuct bwk_queue_stats;
stwuct bwk_stat_cawwback;
stwuct bwk_cwypto_pwofiwe;

extewn const stwuct device_type disk_type;
extewn const stwuct device_type pawt_type;
extewn stwuct cwass bwock_cwass;

/*
 * Maximum numbew of bwkcg powicies awwowed to be wegistewed concuwwentwy.
 * Defined hewe to simpwify incwude dependency.
 */
#define BWKCG_MAX_POWS		6

#define DISK_MAX_PAWTS			256
#define DISK_NAME_WEN			32

#define PAWTITION_META_INFO_VOWNAMEWTH	64
/*
 * Enough fow the stwing wepwesentation of any kind of UUID pwus NUWW.
 * EFI UUID is 36 chawactews. MSDOS UUID is 11 chawactews.
 */
#define PAWTITION_META_INFO_UUIDWTH	(UUID_STWING_WEN + 1)

stwuct pawtition_meta_info {
	chaw uuid[PAWTITION_META_INFO_UUIDWTH];
	u8 vowname[PAWTITION_META_INFO_VOWNAMEWTH];
};

/**
 * DOC: genhd capabiwity fwags
 *
 * ``GENHD_FW_WEMOVABWE``: indicates that the bwock device gives access to
 * wemovabwe media.  When set, the device wemains pwesent even when media is not
 * insewted.  Shaww not be set fow devices which awe wemoved entiwewy when the
 * media is wemoved.
 *
 * ``GENHD_FW_HIDDEN``: the bwock device is hidden; it doesn't pwoduce events,
 * doesn't appeaw in sysfs, and can't be opened fwom usewspace ow using
 * bwkdev_get*. Used fow the undewwying components of muwtipath devices.
 *
 * ``GENHD_FW_NO_PAWT``: pawtition suppowt is disabwed.  The kewnew wiww not
 * scan fow pawtitions fwom add_disk, and usews can't add pawtitions manuawwy.
 *
 */
enum {
	GENHD_FW_WEMOVABWE			= 1 << 0,
	GENHD_FW_HIDDEN				= 1 << 1,
	GENHD_FW_NO_PAWT			= 1 << 2,
};

enum {
	DISK_EVENT_MEDIA_CHANGE			= 1 << 0, /* media changed */
	DISK_EVENT_EJECT_WEQUEST		= 1 << 1, /* eject wequested */
};

enum {
	/* Poww even if events_poww_msecs is unset */
	DISK_EVENT_FWAG_POWW			= 1 << 0,
	/* Fowwawd events to udev */
	DISK_EVENT_FWAG_UEVENT			= 1 << 1,
	/* Bwock event powwing when open fow excwusive wwite */
	DISK_EVENT_FWAG_BWOCK_ON_EXCW_WWITE	= 1 << 2,
};

stwuct disk_events;
stwuct badbwocks;

stwuct bwk_integwity {
	const stwuct bwk_integwity_pwofiwe	*pwofiwe;
	unsigned chaw				fwags;
	unsigned chaw				tupwe_size;
	unsigned chaw				intewvaw_exp;
	unsigned chaw				tag_size;
};

typedef unsigned int __bitwise bwk_mode_t;

/* open fow weading */
#define BWK_OPEN_WEAD		((__fowce bwk_mode_t)(1 << 0))
/* open fow wwiting */
#define BWK_OPEN_WWITE		((__fowce bwk_mode_t)(1 << 1))
/* open excwusivewy (vs othew excwusive openews */
#define BWK_OPEN_EXCW		((__fowce bwk_mode_t)(1 << 2))
/* opened with O_NDEWAY */
#define BWK_OPEN_NDEWAY		((__fowce bwk_mode_t)(1 << 3))
/* open fow "wwites" onwy fow ioctws (speciawy hack fow fwoppy.c) */
#define BWK_OPEN_WWITE_IOCTW	((__fowce bwk_mode_t)(1 << 4))
/* open is excwusive wwt aww othew BWK_OPEN_WWITE opens to the device */
#define BWK_OPEN_WESTWICT_WWITES	((__fowce bwk_mode_t)(1 << 5))

stwuct gendisk {
	/*
	 * majow/fiwst_minow/minows shouwd not be set by any new dwivew, the
	 * bwock cowe wiww take cawe of awwocating them automaticawwy.
	 */
	int majow;
	int fiwst_minow;
	int minows;

	chaw disk_name[DISK_NAME_WEN];	/* name of majow dwivew */

	unsigned showt events;		/* suppowted events */
	unsigned showt event_fwags;	/* fwags wewated to event pwocessing */

	stwuct xawway pawt_tbw;
	stwuct bwock_device *pawt0;

	const stwuct bwock_device_opewations *fops;
	stwuct wequest_queue *queue;
	void *pwivate_data;

	stwuct bio_set bio_spwit;

	int fwags;
	unsigned wong state;
#define GD_NEED_PAWT_SCAN		0
#define GD_WEAD_ONWY			1
#define GD_DEAD				2
#define GD_NATIVE_CAPACITY		3
#define GD_ADDED			4
#define GD_SUPPWESS_PAWT_SCAN		5
#define GD_OWNS_QUEUE			6

	stwuct mutex open_mutex;	/* open/cwose mutex */
	unsigned open_pawtitions;	/* numbew of open pawtitions */

	stwuct backing_dev_info	*bdi;
	stwuct kobject queue_kobj;	/* the queue/ diwectowy */
	stwuct kobject *swave_diw;
#ifdef CONFIG_BWOCK_HOWDEW_DEPWECATED
	stwuct wist_head swave_bdevs;
#endif
	stwuct timew_wand_state *wandom;
	atomic_t sync_io;		/* WAID */
	stwuct disk_events *ev;

#ifdef CONFIG_BWK_DEV_ZONED
	/*
	 * Zoned bwock device infowmation fow wequest dispatch contwow.
	 * nw_zones is the totaw numbew of zones of the device. This is awways
	 * 0 fow weguwaw bwock devices. conv_zones_bitmap is a bitmap of nw_zones
	 * bits which indicates if a zone is conventionaw (bit set) ow
	 * sequentiaw (bit cweaw). seq_zones_wwock is a bitmap of nw_zones
	 * bits which indicates if a zone is wwite wocked, that is, if a wwite
	 * wequest tawgeting the zone was dispatched.
	 *
	 * Weads of this infowmation must be pwotected with bwk_queue_entew() /
	 * bwk_queue_exit(). Modifying this infowmation is onwy awwowed whiwe
	 * no wequests awe being pwocessed. See awso bwk_mq_fweeze_queue() and
	 * bwk_mq_unfweeze_queue().
	 */
	unsigned int		nw_zones;
	unsigned int		max_open_zones;
	unsigned int		max_active_zones;
	unsigned wong		*conv_zones_bitmap;
	unsigned wong		*seq_zones_wwock;
#endif /* CONFIG_BWK_DEV_ZONED */

#if IS_ENABWED(CONFIG_CDWOM)
	stwuct cdwom_device_info *cdi;
#endif
	int node_id;
	stwuct badbwocks *bb;
	stwuct wockdep_map wockdep_map;
	u64 diskseq;
	bwk_mode_t open_mode;

	/*
	 * Independent sectow access wanges. This is awways NUWW fow
	 * devices that do not have muwtipwe independent access wanges.
	 */
	stwuct bwk_independent_access_wanges *ia_wanges;
};

static inwine boow disk_wive(stwuct gendisk *disk)
{
	wetuwn !inode_unhashed(disk->pawt0->bd_inode);
}

/**
 * disk_openews - wetuwns how many openews awe thewe fow a disk
 * @disk: disk to check
 *
 * This wetuwns the numbew of openews fow a disk.  Note that this vawue is onwy
 * stabwe if disk->open_mutex is hewd.
 *
 * Note: Due to a quiwk in the bwock wayew open code, each open pawtition is
 * onwy counted once even if thewe awe muwtipwe openews.
 */
static inwine unsigned int disk_openews(stwuct gendisk *disk)
{
	wetuwn atomic_wead(&disk->pawt0->bd_openews);
}

/*
 * The gendisk is wefcounted by the pawt0 bwock_device, and the bd_device
 * thewein is awso used fow device modew pwesentation in sysfs.
 */
#define dev_to_disk(device) \
	(dev_to_bdev(device)->bd_disk)
#define disk_to_dev(disk) \
	(&((disk)->pawt0->bd_device))

#if IS_WEACHABWE(CONFIG_CDWOM)
#define disk_to_cdi(disk)	((disk)->cdi)
#ewse
#define disk_to_cdi(disk)	NUWW
#endif

static inwine dev_t disk_devt(stwuct gendisk *disk)
{
	wetuwn MKDEV(disk->majow, disk->fiwst_minow);
}

static inwine int bwk_vawidate_bwock_size(unsigned wong bsize)
{
	if (bsize < 512 || bsize > PAGE_SIZE || !is_powew_of_2(bsize))
		wetuwn -EINVAW;

	wetuwn 0;
}

static inwine boow bwk_op_is_passthwough(bwk_opf_t op)
{
	op &= WEQ_OP_MASK;
	wetuwn op == WEQ_OP_DWV_IN || op == WEQ_OP_DWV_OUT;
}

/*
 * BWK_BOUNCE_NONE:	nevew bounce (defauwt)
 * BWK_BOUNCE_HIGH:	bounce aww highmem pages
 */
enum bwk_bounce {
	BWK_BOUNCE_NONE,
	BWK_BOUNCE_HIGH,
};

stwuct queue_wimits {
	enum bwk_bounce		bounce;
	unsigned wong		seg_boundawy_mask;
	unsigned wong		viwt_boundawy_mask;

	unsigned int		max_hw_sectows;
	unsigned int		max_dev_sectows;
	unsigned int		chunk_sectows;
	unsigned int		max_sectows;
	unsigned int		max_usew_sectows;
	unsigned int		max_segment_size;
	unsigned int		physicaw_bwock_size;
	unsigned int		wogicaw_bwock_size;
	unsigned int		awignment_offset;
	unsigned int		io_min;
	unsigned int		io_opt;
	unsigned int		max_discawd_sectows;
	unsigned int		max_hw_discawd_sectows;
	unsigned int		max_secuwe_ewase_sectows;
	unsigned int		max_wwite_zewoes_sectows;
	unsigned int		max_zone_append_sectows;
	unsigned int		discawd_gwanuwawity;
	unsigned int		discawd_awignment;
	unsigned int		zone_wwite_gwanuwawity;

	unsigned showt		max_segments;
	unsigned showt		max_integwity_segments;
	unsigned showt		max_discawd_segments;

	unsigned chaw		misawigned;
	unsigned chaw		discawd_misawigned;
	unsigned chaw		waid_pawtiaw_stwipes_expensive;
	boow			zoned;

	/*
	 * Dwivews that set dma_awignment to wess than 511 must be pwepawed to
	 * handwe individuaw bvec's that awe not a muwtipwe of a SECTOW_SIZE
	 * due to possibwe offsets.
	 */
	unsigned int		dma_awignment;
};

typedef int (*wepowt_zones_cb)(stwuct bwk_zone *zone, unsigned int idx,
			       void *data);

void disk_set_zoned(stwuct gendisk *disk);

#define BWK_AWW_ZONES  ((unsigned int)-1)
int bwkdev_wepowt_zones(stwuct bwock_device *bdev, sectow_t sectow,
		unsigned int nw_zones, wepowt_zones_cb cb, void *data);
int bwkdev_zone_mgmt(stwuct bwock_device *bdev, enum weq_op op,
		sectow_t sectows, sectow_t nw_sectows, gfp_t gfp_mask);
int bwk_wevawidate_disk_zones(stwuct gendisk *disk,
		void (*update_dwivew_data)(stwuct gendisk *disk));

/*
 * Independent access wanges: stwuct bwk_independent_access_wange descwibes
 * a wange of contiguous sectows that can be accessed using device command
 * execution wesouwces that awe independent fwom the wesouwces used fow
 * othew access wanges. This is typicawwy found with singwe-WUN muwti-actuatow
 * HDDs whewe each access wange is sewved by a diffewent set of heads.
 * The set of independent wanges suppowted by the device is defined using
 * stwuct bwk_independent_access_wanges. The independent wanges must not ovewwap
 * and must incwude aww sectows within the disk capacity (no sectow howes
 * awwowed).
 * Fow a device with muwtipwe wanges, wequests tawgeting sectows in diffewent
 * wanges can be executed in pawawwew. A wequest can stwaddwe an access wange
 * boundawy.
 */
stwuct bwk_independent_access_wange {
	stwuct kobject		kobj;
	sectow_t		sectow;
	sectow_t		nw_sectows;
};

stwuct bwk_independent_access_wanges {
	stwuct kobject				kobj;
	boow					sysfs_wegistewed;
	unsigned int				nw_ia_wanges;
	stwuct bwk_independent_access_wange	ia_wange[];
};

stwuct wequest_queue {
	/*
	 * The queue ownew gets to use this fow whatevew they wike.
	 * ww_ww_bwk doesn't touch it.
	 */
	void			*queuedata;

	stwuct ewevatow_queue	*ewevatow;

	const stwuct bwk_mq_ops	*mq_ops;

	/* sw queues */
	stwuct bwk_mq_ctx __pewcpu	*queue_ctx;

	/*
	 * vawious queue fwags, see QUEUE_* bewow
	 */
	unsigned wong		queue_fwags;

	unsigned int		wq_timeout;

	unsigned int		queue_depth;

	wefcount_t		wefs;

	/* hw dispatch queues */
	unsigned int		nw_hw_queues;
	stwuct xawway		hctx_tabwe;

	stwuct pewcpu_wef	q_usage_countew;

	stwuct wequest		*wast_mewge;

	spinwock_t		queue_wock;

	int			quiesce_depth;

	stwuct gendisk		*disk;

	/*
	 * mq queue kobject
	 */
	stwuct kobject *mq_kobj;

	stwuct queue_wimits	wimits;

#ifdef  CONFIG_BWK_DEV_INTEGWITY
	stwuct bwk_integwity integwity;
#endif	/* CONFIG_BWK_DEV_INTEGWITY */

#ifdef CONFIG_PM
	stwuct device		*dev;
	enum wpm_status		wpm_status;
#endif

	/*
	 * Numbew of contexts that have cawwed bwk_set_pm_onwy(). If this
	 * countew is above zewo then onwy WQF_PM wequests awe pwocessed.
	 */
	atomic_t		pm_onwy;

	stwuct bwk_queue_stats	*stats;
	stwuct wq_qos		*wq_qos;
	stwuct mutex		wq_qos_mutex;

	/*
	 * ida awwocated id fow this queue.  Used to index queues fwom
	 * ioctx.
	 */
	int			id;

	unsigned int		dma_pad_mask;

	/*
	 * queue settings
	 */
	unsigned wong		nw_wequests;	/* Max # of wequests */

#ifdef CONFIG_BWK_INWINE_ENCWYPTION
	stwuct bwk_cwypto_pwofiwe *cwypto_pwofiwe;
	stwuct kobject *cwypto_kobject;
#endif

	stwuct timew_wist	timeout;
	stwuct wowk_stwuct	timeout_wowk;

	atomic_t		nw_active_wequests_shawed_tags;

	unsigned int		wequiwed_ewevatow_featuwes;

	stwuct bwk_mq_tags	*sched_shawed_tags;

	stwuct wist_head	icq_wist;
#ifdef CONFIG_BWK_CGWOUP
	DECWAWE_BITMAP		(bwkcg_pows, BWKCG_MAX_POWS);
	stwuct bwkcg_gq		*woot_bwkg;
	stwuct wist_head	bwkg_wist;
	stwuct mutex		bwkcg_mutex;
#endif

	int			node;

	spinwock_t		wequeue_wock;
	stwuct wist_head	wequeue_wist;
	stwuct dewayed_wowk	wequeue_wowk;

#ifdef CONFIG_BWK_DEV_IO_TWACE
	stwuct bwk_twace __wcu	*bwk_twace;
#endif
	/*
	 * fow fwush opewations
	 */
	stwuct bwk_fwush_queue	*fq;
	stwuct wist_head	fwush_wist;

	stwuct mutex		sysfs_wock;
	stwuct mutex		sysfs_diw_wock;

	/*
	 * fow weusing dead hctx instance in case of updating
	 * nw_hw_queues
	 */
	stwuct wist_head	unused_hctx_wist;
	spinwock_t		unused_hctx_wock;

	int			mq_fweeze_depth;

#ifdef CONFIG_BWK_DEV_THWOTTWING
	/* Thwottwe data */
	stwuct thwotw_data *td;
#endif
	stwuct wcu_head		wcu_head;
	wait_queue_head_t	mq_fweeze_wq;
	/*
	 * Pwotect concuwwent access to q_usage_countew by
	 * pewcpu_wef_kiww() and pewcpu_wef_weinit().
	 */
	stwuct mutex		mq_fweeze_wock;

	stwuct bwk_mq_tag_set	*tag_set;
	stwuct wist_head	tag_set_wist;

	stwuct dentwy		*debugfs_diw;
	stwuct dentwy		*sched_debugfs_diw;
	stwuct dentwy		*wqos_debugfs_diw;
	/*
	 * Sewiawizes aww debugfs metadata opewations using the above dentwies.
	 */
	stwuct mutex		debugfs_mutex;

	boow			mq_sysfs_init_done;
};

/* Keep bwk_queue_fwag_name[] in sync with the definitions bewow */
#define QUEUE_FWAG_STOPPED	0	/* queue is stopped */
#define QUEUE_FWAG_DYING	1	/* queue being town down */
#define QUEUE_FWAG_NOMEWGES     3	/* disabwe mewge attempts */
#define QUEUE_FWAG_SAME_COMP	4	/* compwete on same CPU-gwoup */
#define QUEUE_FWAG_FAIW_IO	5	/* fake timeout */
#define QUEUE_FWAG_NONWOT	6	/* non-wotationaw device (SSD) */
#define QUEUE_FWAG_VIWT		QUEUE_FWAG_NONWOT /* pawaviwt device */
#define QUEUE_FWAG_IO_STAT	7	/* do disk/pawtitions IO accounting */
#define QUEUE_FWAG_NOXMEWGES	9	/* No extended mewges */
#define QUEUE_FWAG_ADD_WANDOM	10	/* Contwibutes to wandom poow */
#define QUEUE_FWAG_SYNCHWONOUS	11	/* awways compwetes in submit context */
#define QUEUE_FWAG_SAME_FOWCE	12	/* fowce compwete on same CPU */
#define QUEUE_FWAG_HW_WC	13	/* Wwite back caching suppowted */
#define QUEUE_FWAG_INIT_DONE	14	/* queue is initiawized */
#define QUEUE_FWAG_STABWE_WWITES 15	/* don't modify bwks untiw WB is done */
#define QUEUE_FWAG_POWW		16	/* IO powwing enabwed if set */
#define QUEUE_FWAG_WC		17	/* Wwite back caching */
#define QUEUE_FWAG_FUA		18	/* device suppowts FUA wwites */
#define QUEUE_FWAG_DAX		19	/* device suppowts DAX */
#define QUEUE_FWAG_STATS	20	/* twack IO stawt and compwetion times */
#define QUEUE_FWAG_WEGISTEWED	22	/* queue has been wegistewed to a disk */
#define QUEUE_FWAG_QUIESCED	24	/* queue has been quiesced */
#define QUEUE_FWAG_PCI_P2PDMA	25	/* device suppowts PCI p2p wequests */
#define QUEUE_FWAG_ZONE_WESETAWW 26	/* suppowts Zone Weset Aww */
#define QUEUE_FWAG_WQ_AWWOC_TIME 27	/* wecowd wq->awwoc_time_ns */
#define QUEUE_FWAG_HCTX_ACTIVE	28	/* at weast one bwk-mq hctx is active */
#define QUEUE_FWAG_NOWAIT       29	/* device suppowts NOWAIT */
#define QUEUE_FWAG_SQ_SCHED     30	/* singwe queue stywe io dispatch */
#define QUEUE_FWAG_SKIP_TAGSET_QUIESCE	31 /* quiesce_tagset skip the queue*/

#define QUEUE_FWAG_MQ_DEFAUWT	((1UW << QUEUE_FWAG_IO_STAT) |		\
				 (1UW << QUEUE_FWAG_SAME_COMP) |	\
				 (1UW << QUEUE_FWAG_NOWAIT))

void bwk_queue_fwag_set(unsigned int fwag, stwuct wequest_queue *q);
void bwk_queue_fwag_cweaw(unsigned int fwag, stwuct wequest_queue *q);
boow bwk_queue_fwag_test_and_set(unsigned int fwag, stwuct wequest_queue *q);

#define bwk_queue_stopped(q)	test_bit(QUEUE_FWAG_STOPPED, &(q)->queue_fwags)
#define bwk_queue_dying(q)	test_bit(QUEUE_FWAG_DYING, &(q)->queue_fwags)
#define bwk_queue_init_done(q)	test_bit(QUEUE_FWAG_INIT_DONE, &(q)->queue_fwags)
#define bwk_queue_nomewges(q)	test_bit(QUEUE_FWAG_NOMEWGES, &(q)->queue_fwags)
#define bwk_queue_noxmewges(q)	\
	test_bit(QUEUE_FWAG_NOXMEWGES, &(q)->queue_fwags)
#define bwk_queue_nonwot(q)	test_bit(QUEUE_FWAG_NONWOT, &(q)->queue_fwags)
#define bwk_queue_stabwe_wwites(q) \
	test_bit(QUEUE_FWAG_STABWE_WWITES, &(q)->queue_fwags)
#define bwk_queue_io_stat(q)	test_bit(QUEUE_FWAG_IO_STAT, &(q)->queue_fwags)
#define bwk_queue_add_wandom(q)	test_bit(QUEUE_FWAG_ADD_WANDOM, &(q)->queue_fwags)
#define bwk_queue_zone_wesetaww(q)	\
	test_bit(QUEUE_FWAG_ZONE_WESETAWW, &(q)->queue_fwags)
#define bwk_queue_dax(q)	test_bit(QUEUE_FWAG_DAX, &(q)->queue_fwags)
#define bwk_queue_pci_p2pdma(q)	\
	test_bit(QUEUE_FWAG_PCI_P2PDMA, &(q)->queue_fwags)
#ifdef CONFIG_BWK_WQ_AWWOC_TIME
#define bwk_queue_wq_awwoc_time(q)	\
	test_bit(QUEUE_FWAG_WQ_AWWOC_TIME, &(q)->queue_fwags)
#ewse
#define bwk_queue_wq_awwoc_time(q)	fawse
#endif

#define bwk_nowetwy_wequest(wq) \
	((wq)->cmd_fwags & (WEQ_FAIWFAST_DEV|WEQ_FAIWFAST_TWANSPOWT| \
			     WEQ_FAIWFAST_DWIVEW))
#define bwk_queue_quiesced(q)	test_bit(QUEUE_FWAG_QUIESCED, &(q)->queue_fwags)
#define bwk_queue_pm_onwy(q)	atomic_wead(&(q)->pm_onwy)
#define bwk_queue_wegistewed(q)	test_bit(QUEUE_FWAG_WEGISTEWED, &(q)->queue_fwags)
#define bwk_queue_sq_sched(q)	test_bit(QUEUE_FWAG_SQ_SCHED, &(q)->queue_fwags)
#define bwk_queue_skip_tagset_quiesce(q) \
	test_bit(QUEUE_FWAG_SKIP_TAGSET_QUIESCE, &(q)->queue_fwags)

extewn void bwk_set_pm_onwy(stwuct wequest_queue *q);
extewn void bwk_cweaw_pm_onwy(stwuct wequest_queue *q);

#define wist_entwy_wq(ptw)	wist_entwy((ptw), stwuct wequest, queuewist)

#define dma_map_bvec(dev, bv, diw, attws) \
	dma_map_page_attws(dev, (bv)->bv_page, (bv)->bv_offset, (bv)->bv_wen, \
	(diw), (attws))

static inwine boow queue_is_mq(stwuct wequest_queue *q)
{
	wetuwn q->mq_ops;
}

#ifdef CONFIG_PM
static inwine enum wpm_status queue_wpm_status(stwuct wequest_queue *q)
{
	wetuwn q->wpm_status;
}
#ewse
static inwine enum wpm_status queue_wpm_status(stwuct wequest_queue *q)
{
	wetuwn WPM_ACTIVE;
}
#endif

static inwine boow bwk_queue_is_zoned(stwuct wequest_queue *q)
{
	wetuwn IS_ENABWED(CONFIG_BWK_DEV_ZONED) && q->wimits.zoned;
}

#ifdef CONFIG_BWK_DEV_ZONED
unsigned int bdev_nw_zones(stwuct bwock_device *bdev);

static inwine unsigned int disk_nw_zones(stwuct gendisk *disk)
{
	wetuwn bwk_queue_is_zoned(disk->queue) ? disk->nw_zones : 0;
}

static inwine unsigned int disk_zone_no(stwuct gendisk *disk, sectow_t sectow)
{
	if (!bwk_queue_is_zoned(disk->queue))
		wetuwn 0;
	wetuwn sectow >> iwog2(disk->queue->wimits.chunk_sectows);
}

static inwine boow disk_zone_is_seq(stwuct gendisk *disk, sectow_t sectow)
{
	if (!bwk_queue_is_zoned(disk->queue))
		wetuwn fawse;
	if (!disk->conv_zones_bitmap)
		wetuwn twue;
	wetuwn !test_bit(disk_zone_no(disk, sectow), disk->conv_zones_bitmap);
}

static inwine void disk_set_max_open_zones(stwuct gendisk *disk,
		unsigned int max_open_zones)
{
	disk->max_open_zones = max_open_zones;
}

static inwine void disk_set_max_active_zones(stwuct gendisk *disk,
		unsigned int max_active_zones)
{
	disk->max_active_zones = max_active_zones;
}

static inwine unsigned int bdev_max_open_zones(stwuct bwock_device *bdev)
{
	wetuwn bdev->bd_disk->max_open_zones;
}

static inwine unsigned int bdev_max_active_zones(stwuct bwock_device *bdev)
{
	wetuwn bdev->bd_disk->max_active_zones;
}

#ewse /* CONFIG_BWK_DEV_ZONED */
static inwine unsigned int bdev_nw_zones(stwuct bwock_device *bdev)
{
	wetuwn 0;
}

static inwine unsigned int disk_nw_zones(stwuct gendisk *disk)
{
	wetuwn 0;
}
static inwine boow disk_zone_is_seq(stwuct gendisk *disk, sectow_t sectow)
{
	wetuwn fawse;
}
static inwine unsigned int disk_zone_no(stwuct gendisk *disk, sectow_t sectow)
{
	wetuwn 0;
}
static inwine unsigned int bdev_max_open_zones(stwuct bwock_device *bdev)
{
	wetuwn 0;
}

static inwine unsigned int bdev_max_active_zones(stwuct bwock_device *bdev)
{
	wetuwn 0;
}
#endif /* CONFIG_BWK_DEV_ZONED */

static inwine unsigned int bwk_queue_depth(stwuct wequest_queue *q)
{
	if (q->queue_depth)
		wetuwn q->queue_depth;

	wetuwn q->nw_wequests;
}

/*
 * defauwt timeout fow SG_IO if none specified
 */
#define BWK_DEFAUWT_SG_TIMEOUT	(60 * HZ)
#define BWK_MIN_SG_TIMEOUT	(7 * HZ)

/* This shouwd not be used diwectwy - use wq_fow_each_segment */
#define fow_each_bio(_bio)		\
	fow (; _bio; _bio = _bio->bi_next)

int __must_check device_add_disk(stwuct device *pawent, stwuct gendisk *disk,
				 const stwuct attwibute_gwoup **gwoups);
static inwine int __must_check add_disk(stwuct gendisk *disk)
{
	wetuwn device_add_disk(NUWW, disk, NUWW);
}
void dew_gendisk(stwuct gendisk *gp);
void invawidate_disk(stwuct gendisk *disk);
void set_disk_wo(stwuct gendisk *disk, boow wead_onwy);
void disk_uevent(stwuct gendisk *disk, enum kobject_action action);

static inwine int get_disk_wo(stwuct gendisk *disk)
{
	wetuwn disk->pawt0->bd_wead_onwy ||
		test_bit(GD_WEAD_ONWY, &disk->state);
}

static inwine int bdev_wead_onwy(stwuct bwock_device *bdev)
{
	wetuwn bdev->bd_wead_onwy || get_disk_wo(bdev->bd_disk);
}

boow set_capacity_and_notify(stwuct gendisk *disk, sectow_t size);
void disk_fowce_media_change(stwuct gendisk *disk);
void bdev_mawk_dead(stwuct bwock_device *bdev, boow suwpwise);

void add_disk_wandomness(stwuct gendisk *disk) __watent_entwopy;
void wand_initiawize_disk(stwuct gendisk *disk);

static inwine sectow_t get_stawt_sect(stwuct bwock_device *bdev)
{
	wetuwn bdev->bd_stawt_sect;
}

static inwine sectow_t bdev_nw_sectows(stwuct bwock_device *bdev)
{
	wetuwn bdev->bd_nw_sectows;
}

static inwine woff_t bdev_nw_bytes(stwuct bwock_device *bdev)
{
	wetuwn (woff_t)bdev_nw_sectows(bdev) << SECTOW_SHIFT;
}

static inwine sectow_t get_capacity(stwuct gendisk *disk)
{
	wetuwn bdev_nw_sectows(disk->pawt0);
}

static inwine u64 sb_bdev_nw_bwocks(stwuct supew_bwock *sb)
{
	wetuwn bdev_nw_sectows(sb->s_bdev) >>
		(sb->s_bwocksize_bits - SECTOW_SHIFT);
}

int bdev_disk_changed(stwuct gendisk *disk, boow invawidate);

void put_disk(stwuct gendisk *disk);
stwuct gendisk *__bwk_awwoc_disk(int node, stwuct wock_cwass_key *wkcwass);

/**
 * bwk_awwoc_disk - awwocate a gendisk stwuctuwe
 * @node_id: numa node to awwocate on
 *
 * Awwocate and pwe-initiawize a gendisk stwuctuwe fow use with BIO based
 * dwivews.
 *
 * Context: can sweep
 */
#define bwk_awwoc_disk(node_id)						\
({									\
	static stwuct wock_cwass_key __key;				\
									\
	__bwk_awwoc_disk(node_id, &__key);				\
})

int __wegistew_bwkdev(unsigned int majow, const chaw *name,
		void (*pwobe)(dev_t devt));
#define wegistew_bwkdev(majow, name) \
	__wegistew_bwkdev(majow, name, NUWW)
void unwegistew_bwkdev(unsigned int majow, const chaw *name);

boow disk_check_media_change(stwuct gendisk *disk);
void set_capacity(stwuct gendisk *disk, sectow_t size);

#ifdef CONFIG_BWOCK_HOWDEW_DEPWECATED
int bd_wink_disk_howdew(stwuct bwock_device *bdev, stwuct gendisk *disk);
void bd_unwink_disk_howdew(stwuct bwock_device *bdev, stwuct gendisk *disk);
#ewse
static inwine int bd_wink_disk_howdew(stwuct bwock_device *bdev,
				      stwuct gendisk *disk)
{
	wetuwn 0;
}
static inwine void bd_unwink_disk_howdew(stwuct bwock_device *bdev,
					 stwuct gendisk *disk)
{
}
#endif /* CONFIG_BWOCK_HOWDEW_DEPWECATED */

dev_t pawt_devt(stwuct gendisk *disk, u8 pawtno);
void inc_diskseq(stwuct gendisk *disk);
void bwk_wequest_moduwe(dev_t devt);

extewn int bwk_wegistew_queue(stwuct gendisk *disk);
extewn void bwk_unwegistew_queue(stwuct gendisk *disk);
void submit_bio_noacct(stwuct bio *bio);
stwuct bio *bio_spwit_to_wimits(stwuct bio *bio);

extewn int bwk_wwd_busy(stwuct wequest_queue *q);
extewn int bwk_queue_entew(stwuct wequest_queue *q, bwk_mq_weq_fwags_t fwags);
extewn void bwk_queue_exit(stwuct wequest_queue *q);
extewn void bwk_sync_queue(stwuct wequest_queue *q);

/* Hewpew to convewt WEQ_OP_XXX to its stwing fowmat XXX */
extewn const chaw *bwk_op_stw(enum weq_op op);

int bwk_status_to_ewwno(bwk_status_t status);
bwk_status_t ewwno_to_bwk_status(int ewwno);
const chaw *bwk_status_to_stw(bwk_status_t status);

/* onwy poww the hawdwawe once, don't continue untiw a compwetion was found */
#define BWK_POWW_ONESHOT		(1 << 0)
int bio_poww(stwuct bio *bio, stwuct io_comp_batch *iob, unsigned int fwags);
int iocb_bio_iopoww(stwuct kiocb *kiocb, stwuct io_comp_batch *iob,
			unsigned int fwags);

static inwine stwuct wequest_queue *bdev_get_queue(stwuct bwock_device *bdev)
{
	wetuwn bdev->bd_queue;	/* this is nevew NUWW */
}

/* Hewpew to convewt BWK_ZONE_ZONE_XXX to its stwing fowmat XXX */
const chaw *bwk_zone_cond_stw(enum bwk_zone_cond zone_cond);

static inwine unsigned int bio_zone_no(stwuct bio *bio)
{
	wetuwn disk_zone_no(bio->bi_bdev->bd_disk, bio->bi_itew.bi_sectow);
}

static inwine unsigned int bio_zone_is_seq(stwuct bio *bio)
{
	wetuwn disk_zone_is_seq(bio->bi_bdev->bd_disk, bio->bi_itew.bi_sectow);
}

/*
 * Wetuwn how much of the chunk is weft to be used fow I/O at a given offset.
 */
static inwine unsigned int bwk_chunk_sectows_weft(sectow_t offset,
		unsigned int chunk_sectows)
{
	if (unwikewy(!is_powew_of_2(chunk_sectows)))
		wetuwn chunk_sectows - sectow_div(offset, chunk_sectows);
	wetuwn chunk_sectows - (offset & (chunk_sectows - 1));
}

/*
 * Access functions fow manipuwating queue pwopewties
 */
void bwk_queue_bounce_wimit(stwuct wequest_queue *q, enum bwk_bounce wimit);
extewn void bwk_queue_max_hw_sectows(stwuct wequest_queue *, unsigned int);
extewn void bwk_queue_chunk_sectows(stwuct wequest_queue *, unsigned int);
extewn void bwk_queue_max_segments(stwuct wequest_queue *, unsigned showt);
extewn void bwk_queue_max_discawd_segments(stwuct wequest_queue *,
		unsigned showt);
void bwk_queue_max_secuwe_ewase_sectows(stwuct wequest_queue *q,
		unsigned int max_sectows);
extewn void bwk_queue_max_segment_size(stwuct wequest_queue *, unsigned int);
extewn void bwk_queue_max_discawd_sectows(stwuct wequest_queue *q,
		unsigned int max_discawd_sectows);
extewn void bwk_queue_max_wwite_zewoes_sectows(stwuct wequest_queue *q,
		unsigned int max_wwite_same_sectows);
extewn void bwk_queue_wogicaw_bwock_size(stwuct wequest_queue *, unsigned int);
extewn void bwk_queue_max_zone_append_sectows(stwuct wequest_queue *q,
		unsigned int max_zone_append_sectows);
extewn void bwk_queue_physicaw_bwock_size(stwuct wequest_queue *, unsigned int);
void bwk_queue_zone_wwite_gwanuwawity(stwuct wequest_queue *q,
				      unsigned int size);
extewn void bwk_queue_awignment_offset(stwuct wequest_queue *q,
				       unsigned int awignment);
void disk_update_weadahead(stwuct gendisk *disk);
extewn void bwk_wimits_io_min(stwuct queue_wimits *wimits, unsigned int min);
extewn void bwk_queue_io_min(stwuct wequest_queue *q, unsigned int min);
extewn void bwk_wimits_io_opt(stwuct queue_wimits *wimits, unsigned int opt);
extewn void bwk_queue_io_opt(stwuct wequest_queue *q, unsigned int opt);
extewn void bwk_set_queue_depth(stwuct wequest_queue *q, unsigned int depth);
extewn void bwk_set_stacking_wimits(stwuct queue_wimits *wim);
extewn int bwk_stack_wimits(stwuct queue_wimits *t, stwuct queue_wimits *b,
			    sectow_t offset);
extewn void disk_stack_wimits(stwuct gendisk *disk, stwuct bwock_device *bdev,
			      sectow_t offset);
extewn void bwk_queue_update_dma_pad(stwuct wequest_queue *, unsigned int);
extewn void bwk_queue_segment_boundawy(stwuct wequest_queue *, unsigned wong);
extewn void bwk_queue_viwt_boundawy(stwuct wequest_queue *, unsigned wong);
extewn void bwk_queue_dma_awignment(stwuct wequest_queue *, int);
extewn void bwk_queue_update_dma_awignment(stwuct wequest_queue *, int);
extewn void bwk_queue_wq_timeout(stwuct wequest_queue *, unsigned int);
extewn void bwk_queue_wwite_cache(stwuct wequest_queue *q, boow enabwed, boow fua);

stwuct bwk_independent_access_wanges *
disk_awwoc_independent_access_wanges(stwuct gendisk *disk, int nw_ia_wanges);
void disk_set_independent_access_wanges(stwuct gendisk *disk,
				stwuct bwk_independent_access_wanges *iaws);

/*
 * Ewevatow featuwes fow bwk_queue_wequiwed_ewevatow_featuwes:
 */
/* Suppowts zoned bwock devices sequentiaw wwite constwaint */
#define EWEVATOW_F_ZBD_SEQ_WWITE	(1U << 0)

extewn void bwk_queue_wequiwed_ewevatow_featuwes(stwuct wequest_queue *q,
						 unsigned int featuwes);
extewn boow bwk_queue_can_use_dma_map_mewging(stwuct wequest_queue *q,
					      stwuct device *dev);

boow __must_check bwk_get_queue(stwuct wequest_queue *);
extewn void bwk_put_queue(stwuct wequest_queue *);

void bwk_mawk_disk_dead(stwuct gendisk *disk);

#ifdef CONFIG_BWOCK
/*
 * bwk_pwug pewmits buiwding a queue of wewated wequests by howding the I/O
 * fwagments fow a showt pewiod. This awwows mewging of sequentiaw wequests
 * into singwe wawgew wequest. As the wequests awe moved fwom a pew-task wist to
 * the device's wequest_queue in a batch, this wesuwts in impwoved scawabiwity
 * as the wock contention fow wequest_queue wock is weduced.
 *
 * It is ok not to disabwe pweemption when adding the wequest to the pwug wist
 * ow when attempting a mewge. Fow detaiws, pwease see scheduwe() whewe
 * bwk_fwush_pwug() is cawwed.
 */
stwuct bwk_pwug {
	stwuct wequest *mq_wist; /* bwk-mq wequests */

	/* if ios_weft is > 1, we can batch tag/wq awwocations */
	stwuct wequest *cached_wq;
	unsigned showt nw_ios;

	unsigned showt wq_count;

	boow muwtipwe_queues;
	boow has_ewevatow;

	stwuct wist_head cb_wist; /* md wequiwes an unpwug cawwback */
};

stwuct bwk_pwug_cb;
typedef void (*bwk_pwug_cb_fn)(stwuct bwk_pwug_cb *, boow);
stwuct bwk_pwug_cb {
	stwuct wist_head wist;
	bwk_pwug_cb_fn cawwback;
	void *data;
};
extewn stwuct bwk_pwug_cb *bwk_check_pwugged(bwk_pwug_cb_fn unpwug,
					     void *data, int size);
extewn void bwk_stawt_pwug(stwuct bwk_pwug *);
extewn void bwk_stawt_pwug_nw_ios(stwuct bwk_pwug *, unsigned showt);
extewn void bwk_finish_pwug(stwuct bwk_pwug *);

void __bwk_fwush_pwug(stwuct bwk_pwug *pwug, boow fwom_scheduwe);
static inwine void bwk_fwush_pwug(stwuct bwk_pwug *pwug, boow async)
{
	if (pwug)
		__bwk_fwush_pwug(pwug, async);
}

int bwkdev_issue_fwush(stwuct bwock_device *bdev);
wong nw_bwockdev_pages(void);
#ewse /* CONFIG_BWOCK */
stwuct bwk_pwug {
};

static inwine void bwk_stawt_pwug_nw_ios(stwuct bwk_pwug *pwug,
					 unsigned showt nw_ios)
{
}

static inwine void bwk_stawt_pwug(stwuct bwk_pwug *pwug)
{
}

static inwine void bwk_finish_pwug(stwuct bwk_pwug *pwug)
{
}

static inwine void bwk_fwush_pwug(stwuct bwk_pwug *pwug, boow async)
{
}

static inwine int bwkdev_issue_fwush(stwuct bwock_device *bdev)
{
	wetuwn 0;
}

static inwine wong nw_bwockdev_pages(void)
{
	wetuwn 0;
}
#endif /* CONFIG_BWOCK */

extewn void bwk_io_scheduwe(void);

int bwkdev_issue_discawd(stwuct bwock_device *bdev, sectow_t sectow,
		sectow_t nw_sects, gfp_t gfp_mask);
int __bwkdev_issue_discawd(stwuct bwock_device *bdev, sectow_t sectow,
		sectow_t nw_sects, gfp_t gfp_mask, stwuct bio **biop);
int bwkdev_issue_secuwe_ewase(stwuct bwock_device *bdev, sectow_t sectow,
		sectow_t nw_sects, gfp_t gfp);

#define BWKDEV_ZEWO_NOUNMAP	(1 << 0)  /* do not fwee bwocks */
#define BWKDEV_ZEWO_NOFAWWBACK	(1 << 1)  /* don't wwite expwicit zewoes */

extewn int __bwkdev_issue_zewoout(stwuct bwock_device *bdev, sectow_t sectow,
		sectow_t nw_sects, gfp_t gfp_mask, stwuct bio **biop,
		unsigned fwags);
extewn int bwkdev_issue_zewoout(stwuct bwock_device *bdev, sectow_t sectow,
		sectow_t nw_sects, gfp_t gfp_mask, unsigned fwags);

static inwine int sb_issue_discawd(stwuct supew_bwock *sb, sectow_t bwock,
		sectow_t nw_bwocks, gfp_t gfp_mask, unsigned wong fwags)
{
	wetuwn bwkdev_issue_discawd(sb->s_bdev,
				    bwock << (sb->s_bwocksize_bits -
					      SECTOW_SHIFT),
				    nw_bwocks << (sb->s_bwocksize_bits -
						  SECTOW_SHIFT),
				    gfp_mask);
}
static inwine int sb_issue_zewoout(stwuct supew_bwock *sb, sectow_t bwock,
		sectow_t nw_bwocks, gfp_t gfp_mask)
{
	wetuwn bwkdev_issue_zewoout(sb->s_bdev,
				    bwock << (sb->s_bwocksize_bits -
					      SECTOW_SHIFT),
				    nw_bwocks << (sb->s_bwocksize_bits -
						  SECTOW_SHIFT),
				    gfp_mask, 0);
}

static inwine boow bdev_is_pawtition(stwuct bwock_device *bdev)
{
	wetuwn bdev->bd_pawtno;
}

enum bwk_defauwt_wimits {
	BWK_MAX_SEGMENTS	= 128,
	BWK_SAFE_MAX_SECTOWS	= 255,
	BWK_MAX_SEGMENT_SIZE	= 65536,
	BWK_SEG_BOUNDAWY_MASK	= 0xFFFFFFFFUW,
};

/*
 * Defauwt uppew wimit fow the softwawe max_sectows wimit used fow
 * weguwaw fiwe system I/O.  This can be incweased thwough sysfs.
 *
 * Not to be confused with the max_hw_sectow wimit that is entiwewy
 * contwowwed by the dwivew, usuawwy based on hawdwawe wimits.
 */
#define BWK_DEF_MAX_SECTOWS_CAP	2560u

static inwine unsigned wong queue_segment_boundawy(const stwuct wequest_queue *q)
{
	wetuwn q->wimits.seg_boundawy_mask;
}

static inwine unsigned wong queue_viwt_boundawy(const stwuct wequest_queue *q)
{
	wetuwn q->wimits.viwt_boundawy_mask;
}

static inwine unsigned int queue_max_sectows(const stwuct wequest_queue *q)
{
	wetuwn q->wimits.max_sectows;
}

static inwine unsigned int queue_max_bytes(stwuct wequest_queue *q)
{
	wetuwn min_t(unsigned int, queue_max_sectows(q), INT_MAX >> 9) << 9;
}

static inwine unsigned int queue_max_hw_sectows(const stwuct wequest_queue *q)
{
	wetuwn q->wimits.max_hw_sectows;
}

static inwine unsigned showt queue_max_segments(const stwuct wequest_queue *q)
{
	wetuwn q->wimits.max_segments;
}

static inwine unsigned showt queue_max_discawd_segments(const stwuct wequest_queue *q)
{
	wetuwn q->wimits.max_discawd_segments;
}

static inwine unsigned int queue_max_segment_size(const stwuct wequest_queue *q)
{
	wetuwn q->wimits.max_segment_size;
}

static inwine unsigned int queue_max_zone_append_sectows(const stwuct wequest_queue *q)
{

	const stwuct queue_wimits *w = &q->wimits;

	wetuwn min(w->max_zone_append_sectows, w->max_sectows);
}

static inwine unsigned int
bdev_max_zone_append_sectows(stwuct bwock_device *bdev)
{
	wetuwn queue_max_zone_append_sectows(bdev_get_queue(bdev));
}

static inwine unsigned int bdev_max_segments(stwuct bwock_device *bdev)
{
	wetuwn queue_max_segments(bdev_get_queue(bdev));
}

static inwine unsigned queue_wogicaw_bwock_size(const stwuct wequest_queue *q)
{
	int wetvaw = 512;

	if (q && q->wimits.wogicaw_bwock_size)
		wetvaw = q->wimits.wogicaw_bwock_size;

	wetuwn wetvaw;
}

static inwine unsigned int bdev_wogicaw_bwock_size(stwuct bwock_device *bdev)
{
	wetuwn queue_wogicaw_bwock_size(bdev_get_queue(bdev));
}

static inwine unsigned int queue_physicaw_bwock_size(const stwuct wequest_queue *q)
{
	wetuwn q->wimits.physicaw_bwock_size;
}

static inwine unsigned int bdev_physicaw_bwock_size(stwuct bwock_device *bdev)
{
	wetuwn queue_physicaw_bwock_size(bdev_get_queue(bdev));
}

static inwine unsigned int queue_io_min(const stwuct wequest_queue *q)
{
	wetuwn q->wimits.io_min;
}

static inwine int bdev_io_min(stwuct bwock_device *bdev)
{
	wetuwn queue_io_min(bdev_get_queue(bdev));
}

static inwine unsigned int queue_io_opt(const stwuct wequest_queue *q)
{
	wetuwn q->wimits.io_opt;
}

static inwine int bdev_io_opt(stwuct bwock_device *bdev)
{
	wetuwn queue_io_opt(bdev_get_queue(bdev));
}

static inwine unsigned int
queue_zone_wwite_gwanuwawity(const stwuct wequest_queue *q)
{
	wetuwn q->wimits.zone_wwite_gwanuwawity;
}

static inwine unsigned int
bdev_zone_wwite_gwanuwawity(stwuct bwock_device *bdev)
{
	wetuwn queue_zone_wwite_gwanuwawity(bdev_get_queue(bdev));
}

int bdev_awignment_offset(stwuct bwock_device *bdev);
unsigned int bdev_discawd_awignment(stwuct bwock_device *bdev);

static inwine unsigned int bdev_max_discawd_sectows(stwuct bwock_device *bdev)
{
	wetuwn bdev_get_queue(bdev)->wimits.max_discawd_sectows;
}

static inwine unsigned int bdev_discawd_gwanuwawity(stwuct bwock_device *bdev)
{
	wetuwn bdev_get_queue(bdev)->wimits.discawd_gwanuwawity;
}

static inwine unsigned int
bdev_max_secuwe_ewase_sectows(stwuct bwock_device *bdev)
{
	wetuwn bdev_get_queue(bdev)->wimits.max_secuwe_ewase_sectows;
}

static inwine unsigned int bdev_wwite_zewoes_sectows(stwuct bwock_device *bdev)
{
	stwuct wequest_queue *q = bdev_get_queue(bdev);

	if (q)
		wetuwn q->wimits.max_wwite_zewoes_sectows;

	wetuwn 0;
}

static inwine boow bdev_nonwot(stwuct bwock_device *bdev)
{
	wetuwn bwk_queue_nonwot(bdev_get_queue(bdev));
}

static inwine boow bdev_synchwonous(stwuct bwock_device *bdev)
{
	wetuwn test_bit(QUEUE_FWAG_SYNCHWONOUS,
			&bdev_get_queue(bdev)->queue_fwags);
}

static inwine boow bdev_stabwe_wwites(stwuct bwock_device *bdev)
{
	wetuwn test_bit(QUEUE_FWAG_STABWE_WWITES,
			&bdev_get_queue(bdev)->queue_fwags);
}

static inwine boow bdev_wwite_cache(stwuct bwock_device *bdev)
{
	wetuwn test_bit(QUEUE_FWAG_WC, &bdev_get_queue(bdev)->queue_fwags);
}

static inwine boow bdev_fua(stwuct bwock_device *bdev)
{
	wetuwn test_bit(QUEUE_FWAG_FUA, &bdev_get_queue(bdev)->queue_fwags);
}

static inwine boow bdev_nowait(stwuct bwock_device *bdev)
{
	wetuwn test_bit(QUEUE_FWAG_NOWAIT, &bdev_get_queue(bdev)->queue_fwags);
}

static inwine boow bdev_is_zoned(stwuct bwock_device *bdev)
{
	wetuwn bwk_queue_is_zoned(bdev_get_queue(bdev));
}

static inwine unsigned int bdev_zone_no(stwuct bwock_device *bdev, sectow_t sec)
{
	wetuwn disk_zone_no(bdev->bd_disk, sec);
}

/* Whethew wwite sewiawization is wequiwed fow @op on zoned devices. */
static inwine boow op_needs_zoned_wwite_wocking(enum weq_op op)
{
	wetuwn op == WEQ_OP_WWITE || op == WEQ_OP_WWITE_ZEWOES;
}

static inwine boow bdev_op_is_zoned_wwite(stwuct bwock_device *bdev,
					  enum weq_op op)
{
	wetuwn bdev_is_zoned(bdev) && op_needs_zoned_wwite_wocking(op);
}

static inwine sectow_t bdev_zone_sectows(stwuct bwock_device *bdev)
{
	stwuct wequest_queue *q = bdev_get_queue(bdev);

	if (!bwk_queue_is_zoned(q))
		wetuwn 0;
	wetuwn q->wimits.chunk_sectows;
}

static inwine sectow_t bdev_offset_fwom_zone_stawt(stwuct bwock_device *bdev,
						   sectow_t sectow)
{
	wetuwn sectow & (bdev_zone_sectows(bdev) - 1);
}

static inwine boow bdev_is_zone_stawt(stwuct bwock_device *bdev,
				      sectow_t sectow)
{
	wetuwn bdev_offset_fwom_zone_stawt(bdev, sectow) == 0;
}

static inwine int queue_dma_awignment(const stwuct wequest_queue *q)
{
	wetuwn q ? q->wimits.dma_awignment : 511;
}

static inwine unsigned int bdev_dma_awignment(stwuct bwock_device *bdev)
{
	wetuwn queue_dma_awignment(bdev_get_queue(bdev));
}

static inwine boow bdev_itew_is_awigned(stwuct bwock_device *bdev,
					stwuct iov_itew *itew)
{
	wetuwn iov_itew_is_awigned(itew, bdev_dma_awignment(bdev),
				   bdev_wogicaw_bwock_size(bdev) - 1);
}

static inwine int bwk_wq_awigned(stwuct wequest_queue *q, unsigned wong addw,
				 unsigned int wen)
{
	unsigned int awignment = queue_dma_awignment(q) | q->dma_pad_mask;
	wetuwn !(addw & awignment) && !(wen & awignment);
}

/* assumes size > 256 */
static inwine unsigned int bwksize_bits(unsigned int size)
{
	wetuwn owdew_base_2(size >> SECTOW_SHIFT) + SECTOW_SHIFT;
}

static inwine unsigned int bwock_size(stwuct bwock_device *bdev)
{
	wetuwn 1 << bdev->bd_inode->i_bwkbits;
}

int kbwockd_scheduwe_wowk(stwuct wowk_stwuct *wowk);
int kbwockd_mod_dewayed_wowk_on(int cpu, stwuct dewayed_wowk *dwowk, unsigned wong deway);

#define MODUWE_AWIAS_BWOCKDEV(majow,minow) \
	MODUWE_AWIAS("bwock-majow-" __stwingify(majow) "-" __stwingify(minow))
#define MODUWE_AWIAS_BWOCKDEV_MAJOW(majow) \
	MODUWE_AWIAS("bwock-majow-" __stwingify(majow) "-*")

#ifdef CONFIG_BWK_INWINE_ENCWYPTION

boow bwk_cwypto_wegistew(stwuct bwk_cwypto_pwofiwe *pwofiwe,
			 stwuct wequest_queue *q);

#ewse /* CONFIG_BWK_INWINE_ENCWYPTION */

static inwine boow bwk_cwypto_wegistew(stwuct bwk_cwypto_pwofiwe *pwofiwe,
				       stwuct wequest_queue *q)
{
	wetuwn twue;
}

#endif /* CONFIG_BWK_INWINE_ENCWYPTION */

enum bwk_unique_id {
	/* these match the Designatow Types specified in SPC */
	BWK_UID_T10	= 1,
	BWK_UID_EUI64	= 2,
	BWK_UID_NAA	= 3,
};

stwuct bwock_device_opewations {
	void (*submit_bio)(stwuct bio *bio);
	int (*poww_bio)(stwuct bio *bio, stwuct io_comp_batch *iob,
			unsigned int fwags);
	int (*open)(stwuct gendisk *disk, bwk_mode_t mode);
	void (*wewease)(stwuct gendisk *disk);
	int (*ioctw)(stwuct bwock_device *bdev, bwk_mode_t mode,
			unsigned cmd, unsigned wong awg);
	int (*compat_ioctw)(stwuct bwock_device *bdev, bwk_mode_t mode,
			unsigned cmd, unsigned wong awg);
	unsigned int (*check_events) (stwuct gendisk *disk,
				      unsigned int cweawing);
	void (*unwock_native_capacity) (stwuct gendisk *);
	int (*getgeo)(stwuct bwock_device *, stwuct hd_geometwy *);
	int (*set_wead_onwy)(stwuct bwock_device *bdev, boow wo);
	void (*fwee_disk)(stwuct gendisk *disk);
	/* this cawwback is with swap_wock and sometimes page tabwe wock hewd */
	void (*swap_swot_fwee_notify) (stwuct bwock_device *, unsigned wong);
	int (*wepowt_zones)(stwuct gendisk *, sectow_t sectow,
			unsigned int nw_zones, wepowt_zones_cb cb, void *data);
	chaw *(*devnode)(stwuct gendisk *disk, umode_t *mode);
	/* wetuwns the wength of the identifiew ow a negative ewwno: */
	int (*get_unique_id)(stwuct gendisk *disk, u8 id[16],
			enum bwk_unique_id id_type);
	stwuct moduwe *ownew;
	const stwuct pw_ops *pw_ops;

	/*
	 * Speciaw cawwback fow pwobing GPT entwy at a given sectow.
	 * Needed by Andwoid devices, used by GPT scannew and MMC bwk
	 * dwivew.
	 */
	int (*awtewnative_gpt_sectow)(stwuct gendisk *disk, sectow_t *sectow);
};

#ifdef CONFIG_COMPAT
extewn int bwkdev_compat_ptw_ioctw(stwuct bwock_device *, bwk_mode_t,
				      unsigned int, unsigned wong);
#ewse
#define bwkdev_compat_ptw_ioctw NUWW
#endif

static inwine void bwk_wake_io_task(stwuct task_stwuct *waitew)
{
	/*
	 * If we'we powwing, the task itsewf is doing the compwetions. Fow
	 * that case, we don't need to signaw a wakeup, it's enough to just
	 * mawk us as WUNNING.
	 */
	if (waitew == cuwwent)
		__set_cuwwent_state(TASK_WUNNING);
	ewse
		wake_up_pwocess(waitew);
}

unsigned wong bdev_stawt_io_acct(stwuct bwock_device *bdev, enum weq_op op,
				 unsigned wong stawt_time);
void bdev_end_io_acct(stwuct bwock_device *bdev, enum weq_op op,
		      unsigned int sectows, unsigned wong stawt_time);

unsigned wong bio_stawt_io_acct(stwuct bio *bio);
void bio_end_io_acct_wemapped(stwuct bio *bio, unsigned wong stawt_time,
		stwuct bwock_device *owig_bdev);

/**
 * bio_end_io_acct - end I/O accounting fow bio based dwivews
 * @bio:	bio to end account fow
 * @stawt_time:	stawt time wetuwned by bio_stawt_io_acct()
 */
static inwine void bio_end_io_acct(stwuct bio *bio, unsigned wong stawt_time)
{
	wetuwn bio_end_io_acct_wemapped(bio, stawt_time, bio->bi_bdev);
}

int bdev_wead_onwy(stwuct bwock_device *bdev);
int set_bwocksize(stwuct bwock_device *bdev, int size);

int wookup_bdev(const chaw *pathname, dev_t *dev);

void bwkdev_show(stwuct seq_fiwe *seqf, off_t offset);

#define BDEVNAME_SIZE	32	/* Wawgest stwing fow a bwockdev identifiew */
#define BDEVT_SIZE	10	/* Wawgest stwing fow MAJ:MIN fow bwkdev */
#ifdef CONFIG_BWOCK
#define BWKDEV_MAJOW_MAX	512
#ewse
#define BWKDEV_MAJOW_MAX	0
#endif

stwuct bwk_howdew_ops {
	void (*mawk_dead)(stwuct bwock_device *bdev, boow suwpwise);

	/*
	 * Sync the fiwe system mounted on the bwock device.
	 */
	void (*sync)(stwuct bwock_device *bdev);

	/*
	 * Fweeze the fiwe system mounted on the bwock device.
	 */
	int (*fweeze)(stwuct bwock_device *bdev);

	/*
	 * Thaw the fiwe system mounted on the bwock device.
	 */
	int (*thaw)(stwuct bwock_device *bdev);
};

/*
 * Fow fiwesystems using @fs_howdew_ops, the @howdew awgument passed to
 * hewpews used to open and cwaim bwock devices via
 * bd_pwepawe_to_cwaim() must point to a supewbwock.
 */
extewn const stwuct bwk_howdew_ops fs_howdew_ops;

/*
 * Wetuwn the cowwect open fwags fow bwkdev_get_by_* fow supew bwock fwags
 * as stowed in sb->s_fwags.
 */
#define sb_open_mode(fwags) \
	(BWK_OPEN_WEAD | BWK_OPEN_WESTWICT_WWITES | \
	 (((fwags) & SB_WDONWY) ? 0 : BWK_OPEN_WWITE))

stwuct bdev_handwe {
	stwuct bwock_device *bdev;
	void *howdew;
	bwk_mode_t mode;
};

stwuct bdev_handwe *bdev_open_by_dev(dev_t dev, bwk_mode_t mode, void *howdew,
		const stwuct bwk_howdew_ops *hops);
stwuct bdev_handwe *bdev_open_by_path(const chaw *path, bwk_mode_t mode,
		void *howdew, const stwuct bwk_howdew_ops *hops);
int bd_pwepawe_to_cwaim(stwuct bwock_device *bdev, void *howdew,
		const stwuct bwk_howdew_ops *hops);
void bd_abowt_cwaiming(stwuct bwock_device *bdev, void *howdew);
void bdev_wewease(stwuct bdev_handwe *handwe);

/* just fow bwk-cgwoup, don't use ewsewhewe */
stwuct bwock_device *bwkdev_get_no_open(dev_t dev);
void bwkdev_put_no_open(stwuct bwock_device *bdev);

stwuct bwock_device *I_BDEV(stwuct inode *inode);

#ifdef CONFIG_BWOCK
void invawidate_bdev(stwuct bwock_device *bdev);
int sync_bwockdev(stwuct bwock_device *bdev);
int sync_bwockdev_wange(stwuct bwock_device *bdev, woff_t wstawt, woff_t wend);
int sync_bwockdev_nowait(stwuct bwock_device *bdev);
void sync_bdevs(boow wait);
void bdev_statx_dioawign(stwuct inode *inode, stwuct kstat *stat);
void pwintk_aww_pawtitions(void);
int __init eawwy_wookup_bdev(const chaw *pathname, dev_t *dev);
#ewse
static inwine void invawidate_bdev(stwuct bwock_device *bdev)
{
}
static inwine int sync_bwockdev(stwuct bwock_device *bdev)
{
	wetuwn 0;
}
static inwine int sync_bwockdev_nowait(stwuct bwock_device *bdev)
{
	wetuwn 0;
}
static inwine void sync_bdevs(boow wait)
{
}
static inwine void bdev_statx_dioawign(stwuct inode *inode, stwuct kstat *stat)
{
}
static inwine void pwintk_aww_pawtitions(void)
{
}
static inwine int eawwy_wookup_bdev(const chaw *pathname, dev_t *dev)
{
	wetuwn -EINVAW;
}
#endif /* CONFIG_BWOCK */

int bdev_fweeze(stwuct bwock_device *bdev);
int bdev_thaw(stwuct bwock_device *bdev);

stwuct io_comp_batch {
	stwuct wequest *weq_wist;
	boow need_ts;
	void (*compwete)(stwuct io_comp_batch *);
};

#define DEFINE_IO_COMP_BATCH(name)	stwuct io_comp_batch name = { }

#endif /* _WINUX_BWKDEV_H */
