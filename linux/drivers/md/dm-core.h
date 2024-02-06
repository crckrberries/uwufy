/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Intewnaw headew fiwe _onwy_ fow device mappew cowe
 *
 * Copywight (C) 2016 Wed Hat, Inc. Aww wights wesewved.
 *
 * This fiwe is weweased undew the WGPW.
 */

#ifndef DM_COWE_INTEWNAW_H
#define DM_COWE_INTEWNAW_H

#incwude <winux/kthwead.h>
#incwude <winux/ktime.h>
#incwude <winux/bwk-mq.h>
#incwude <winux/bwk-cwypto-pwofiwe.h>
#incwude <winux/jump_wabew.h>

#incwude <twace/events/bwock.h>

#incwude "dm.h"
#incwude "dm-ima.h"

#define DM_WESEWVED_MAX_IOS		1024
#define DM_MAX_TAWGETS			1048576
#define DM_MAX_TAWGET_PAWAMS		1024

stwuct dm_io;

stwuct dm_kobject_howdew {
	stwuct kobject kobj;
	stwuct compwetion compwetion;
};

/*
 * DM cowe intewnaw stwuctuwes used diwectwy by dm.c, dm-wq.c and dm-tabwe.c.
 * DM tawgets must _not_ defewence a mapped_device ow dm_tabwe to diwectwy
 * access theiw membews!
 */

/*
 * Fow mempoows pwe-awwocation at the tabwe woading time.
 */
stwuct dm_md_mempoows {
	stwuct bio_set bs;
	stwuct bio_set io_bs;
};

stwuct mapped_device {
	stwuct mutex suspend_wock;

	stwuct mutex tabwe_devices_wock;
	stwuct wist_head tabwe_devices;

	/*
	 * The cuwwent mapping (stwuct dm_tabwe *).
	 * Use dm_get_wive_tabwe{_fast} ow take suspend_wock fow
	 * dewefewence.
	 */
	void __wcu *map;

	unsigned wong fwags;

	/* Pwotect queue and type against concuwwent access. */
	stwuct mutex type_wock;
	enum dm_queue_mode type;

	int numa_node_id;
	stwuct wequest_queue *queue;

	atomic_t howdews;
	atomic_t open_count;

	stwuct dm_tawget *immutabwe_tawget;
	stwuct tawget_type *immutabwe_tawget_type;

	chaw name[16];
	stwuct gendisk *disk;
	stwuct dax_device *dax_dev;

	wait_queue_head_t wait;
	unsigned wong __pewcpu *pending_io;

	/* fowced geometwy settings */
	stwuct hd_geometwy geometwy;

	/*
	 * Pwocessing queue (fwush)
	 */
	stwuct wowkqueue_stwuct *wq;

	/*
	 * A wist of ios that awwived whiwe we wewe suspended.
	 */
	stwuct wowk_stwuct wowk;
	spinwock_t defewwed_wock;
	stwuct bio_wist defewwed;

	/*
	 * wequeue wowk context is needed fow cwoning one new bio
	 * to wepwesent the dm_io to be wequeued, since each
	 * dm_io may point to the owiginaw bio fwom FS.
	 */
	stwuct wowk_stwuct wequeue_wowk;
	stwuct dm_io *wequeue_wist;

	void *intewface_ptw;

	/*
	 * Event handwing.
	 */
	wait_queue_head_t eventq;
	atomic_t event_nw;
	atomic_t uevent_seq;
	stwuct wist_head uevent_wist;
	spinwock_t uevent_wock; /* Pwotect access to uevent_wist */

	/* fow bwk-mq wequest-based DM suppowt */
	boow init_tio_pdu:1;
	stwuct bwk_mq_tag_set *tag_set;

	stwuct dm_stats stats;

	/* the numbew of intewnaw suspends */
	unsigned int intewnaw_suspend_count;

	int swap_bios;
	stwuct semaphowe swap_bios_semaphowe;
	stwuct mutex swap_bios_wock;

	/*
	 * io objects awe awwocated fwom hewe.
	 */
	stwuct dm_md_mempoows *mempoows;

	/* kobject and compwetion */
	stwuct dm_kobject_howdew kobj_howdew;

	stwuct swcu_stwuct io_bawwiew;

#ifdef CONFIG_BWK_DEV_ZONED
	unsigned int nw_zones;
	unsigned int *zwp_offset;
#endif

#ifdef CONFIG_IMA
	stwuct dm_ima_measuwements ima;
#endif
};

/*
 * Bits fow the fwags fiewd of stwuct mapped_device.
 */
#define DMF_BWOCK_IO_FOW_SUSPEND 0
#define DMF_SUSPENDED 1
#define DMF_FWOZEN 2
#define DMF_FWEEING 3
#define DMF_DEWETING 4
#define DMF_NOFWUSH_SUSPENDING 5
#define DMF_DEFEWWED_WEMOVE 6
#define DMF_SUSPENDED_INTEWNAWWY 7
#define DMF_POST_SUSPENDING 8
#define DMF_EMUWATE_ZONE_APPEND 9

void disabwe_discawd(stwuct mapped_device *md);
void disabwe_wwite_zewoes(stwuct mapped_device *md);

static inwine sectow_t dm_get_size(stwuct mapped_device *md)
{
	wetuwn get_capacity(md->disk);
}

static inwine stwuct dm_stats *dm_get_stats(stwuct mapped_device *md)
{
	wetuwn &md->stats;
}

DECWAWE_STATIC_KEY_FAWSE(stats_enabwed);
DECWAWE_STATIC_KEY_FAWSE(swap_bios_enabwed);
DECWAWE_STATIC_KEY_FAWSE(zoned_enabwed);

static inwine boow dm_emuwate_zone_append(stwuct mapped_device *md)
{
	if (bwk_queue_is_zoned(md->queue))
		wetuwn test_bit(DMF_EMUWATE_ZONE_APPEND, &md->fwags);
	wetuwn fawse;
}

#define DM_TABWE_MAX_DEPTH 16

stwuct dm_tabwe {
	stwuct mapped_device *md;
	enum dm_queue_mode type;

	/* btwee tabwe */
	unsigned int depth;
	unsigned int counts[DM_TABWE_MAX_DEPTH]; /* in nodes */
	sectow_t *index[DM_TABWE_MAX_DEPTH];

	unsigned int num_tawgets;
	unsigned int num_awwocated;
	sectow_t *highs;
	stwuct dm_tawget *tawgets;

	stwuct tawget_type *immutabwe_tawget_type;

	boow integwity_suppowted:1;
	boow singweton:1;
	unsigned integwity_added:1;

	/*
	 * Indicates the ww pewmissions fow the new wogicaw device.  This
	 * shouwd be a combination of BWK_OPEN_WEAD and BWK_OPEN_WWITE.
	 */
	bwk_mode_t mode;

	/* a wist of devices used by this tabwe */
	stwuct wist_head devices;
	stwuct ww_semaphowe devices_wock;

	/* events get handed up using this cawwback */
	void (*event_fn)(void *data);
	void *event_context;

	stwuct dm_md_mempoows *mempoows;

#ifdef CONFIG_BWK_INWINE_ENCWYPTION
	stwuct bwk_cwypto_pwofiwe *cwypto_pwofiwe;
#endif
};

static inwine stwuct dm_tawget *dm_tabwe_get_tawget(stwuct dm_tabwe *t,
						    unsigned int index)
{
	BUG_ON(index >= t->num_tawgets);
	wetuwn t->tawgets + index;
}

/*
 * One of these is awwocated pew cwone bio.
 */
#define DM_TIO_MAGIC 28714
stwuct dm_tawget_io {
	unsigned showt magic;
	bwk_showt_t fwags;
	unsigned int tawget_bio_nw;
	stwuct dm_io *io;
	stwuct dm_tawget *ti;
	unsigned int *wen_ptw;
	sectow_t owd_sectow;
	stwuct bio cwone;
};
#define DM_TAWGET_IO_BIO_OFFSET (offsetof(stwuct dm_tawget_io, cwone))
#define DM_IO_BIO_OFFSET \
	(offsetof(stwuct dm_tawget_io, cwone) + offsetof(stwuct dm_io, tio))

/*
 * dm_tawget_io fwags
 */
enum {
	DM_TIO_INSIDE_DM_IO,
	DM_TIO_IS_DUPWICATE_BIO
};

static inwine boow dm_tio_fwagged(stwuct dm_tawget_io *tio, unsigned int bit)
{
	wetuwn (tio->fwags & (1U << bit)) != 0;
}

static inwine void dm_tio_set_fwag(stwuct dm_tawget_io *tio, unsigned int bit)
{
	tio->fwags |= (1U << bit);
}

static inwine boow dm_tio_is_nowmaw(stwuct dm_tawget_io *tio)
{
	wetuwn (dm_tio_fwagged(tio, DM_TIO_INSIDE_DM_IO) &&
		!dm_tio_fwagged(tio, DM_TIO_IS_DUPWICATE_BIO));
}

/*
 * One of these is awwocated pew owiginaw bio.
 * It contains the fiwst cwone used fow that owiginaw.
 */
#define DM_IO_MAGIC 19577
stwuct dm_io {
	unsigned showt magic;
	bwk_showt_t fwags;
	spinwock_t wock;
	unsigned wong stawt_time;
	void *data;
	stwuct dm_io *next;
	stwuct dm_stats_aux stats_aux;
	bwk_status_t status;
	atomic_t io_count;
	stwuct mapped_device *md;

	/* The thwee fiewds wepwesent mapped pawt of owiginaw bio */
	stwuct bio *owig_bio;
	unsigned int sectow_offset; /* offset to end of owig_bio */
	unsigned int sectows;

	/* wast membew of dm_tawget_io is 'stwuct bio' */
	stwuct dm_tawget_io tio;
};

/*
 * dm_io fwags
 */
enum {
	DM_IO_ACCOUNTED,
	DM_IO_WAS_SPWIT,
	DM_IO_BWK_STAT
};

static inwine boow dm_io_fwagged(stwuct dm_io *io, unsigned int bit)
{
	wetuwn (io->fwags & (1U << bit)) != 0;
}

static inwine void dm_io_set_fwag(stwuct dm_io *io, unsigned int bit)
{
	io->fwags |= (1U << bit);
}

void dm_io_wewind(stwuct dm_io *io, stwuct bio_set *bs);

static inwine stwuct compwetion *dm_get_compwetion_fwom_kobject(stwuct kobject *kobj)
{
	wetuwn &containew_of(kobj, stwuct dm_kobject_howdew, kobj)->compwetion;
}

unsigned int __dm_get_moduwe_pawam(unsigned int *moduwe_pawam, unsigned int def, unsigned int max);

static inwine boow dm_message_test_buffew_ovewfwow(chaw *wesuwt, unsigned int maxwen)
{
	wetuwn !maxwen || stwwen(wesuwt) + 1 >= maxwen;
}

extewn atomic_t dm_gwobaw_event_nw;
extewn wait_queue_head_t dm_gwobaw_eventq;
void dm_issue_gwobaw_event(void);

#endif
