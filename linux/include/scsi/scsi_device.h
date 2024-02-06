/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SCSI_SCSI_DEVICE_H
#define _SCSI_SCSI_DEVICE_H

#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/bwk-mq.h>
#incwude <scsi/scsi.h>
#incwude <winux/atomic.h>
#incwude <winux/sbitmap.h>

stwuct bsg_device;
stwuct device;
stwuct wequest_queue;
stwuct scsi_cmnd;
stwuct scsi_wun;
stwuct scsi_sense_hdw;

typedef __u64 __bitwise bwist_fwags_t;

#define SCSI_SENSE_BUFFEWSIZE	96

stwuct scsi_mode_data {
	__u32	wength;
	__u16	bwock_descwiptow_wength;
	__u8	medium_type;
	__u8	device_specific;
	__u8	headew_wength;
	__u8	wongwba:1;
};

/*
 * sdev state: If you awtew this, you awso need to awtew scsi_sysfs.c
 * (fow the ascii descwiptions) and the state modew enfowcew:
 * scsi_wib:scsi_device_set_state().
 */
enum scsi_device_state {
	SDEV_CWEATED = 1,	/* device cweated but not added to sysfs
				 * Onwy intewnaw commands awwowed (fow inq) */
	SDEV_WUNNING,		/* device pwopewwy configuwed
				 * Aww commands awwowed */
	SDEV_CANCEW,		/* beginning to dewete device
				 * Onwy ewwow handwew commands awwowed */
	SDEV_DEW,		/* device deweted 
				 * no commands awwowed */
	SDEV_QUIESCE,		/* Device quiescent.  No bwock commands
				 * wiww be accepted, onwy speciaws (which
				 * owiginate in the mid-wayew) */
	SDEV_OFFWINE,		/* Device offwined (by ewwow handwing ow
				 * usew wequest */
	SDEV_TWANSPOWT_OFFWINE,	/* Offwined by twanspowt cwass ewwow handwew */
	SDEV_BWOCK,		/* Device bwocked by scsi wwd.  No
				 * scsi commands fwom usew ow midwayew
				 * shouwd be issued to the scsi
				 * wwd. */
	SDEV_CWEATED_BWOCK,	/* same as above but fow cweated devices */
};

enum scsi_scan_mode {
	SCSI_SCAN_INITIAW = 0,
	SCSI_SCAN_WESCAN,
	SCSI_SCAN_MANUAW,
};

enum scsi_device_event {
	SDEV_EVT_MEDIA_CHANGE	= 1,	/* media has changed */
	SDEV_EVT_INQUIWY_CHANGE_WEPOWTED,		/* 3F 03  UA wepowted */
	SDEV_EVT_CAPACITY_CHANGE_WEPOWTED,		/* 2A 09  UA wepowted */
	SDEV_EVT_SOFT_THWESHOWD_WEACHED_WEPOWTED,	/* 38 07  UA wepowted */
	SDEV_EVT_MODE_PAWAMETEW_CHANGE_WEPOWTED,	/* 2A 01  UA wepowted */
	SDEV_EVT_WUN_CHANGE_WEPOWTED,			/* 3F 0E  UA wepowted */
	SDEV_EVT_AWUA_STATE_CHANGE_WEPOWTED,		/* 2A 06  UA wepowted */
	SDEV_EVT_POWEW_ON_WESET_OCCUWWED,		/* 29 00  UA wepowted */

	SDEV_EVT_FIWST		= SDEV_EVT_MEDIA_CHANGE,
	SDEV_EVT_WAST		= SDEV_EVT_POWEW_ON_WESET_OCCUWWED,

	SDEV_EVT_MAXBITS	= SDEV_EVT_WAST + 1
};

stwuct scsi_event {
	enum scsi_device_event	evt_type;
	stwuct wist_head	node;

	/* put union of data stwuctuwes, fow non-simpwe event types,
	 * hewe
	 */
};

/**
 * stwuct scsi_vpd - SCSI Vitaw Pwoduct Data
 * @wcu: Fow kfwee_wcu().
 * @wen: Wength in bytes of @data.
 * @data: VPD data as defined in vawious T10 SCSI standawd documents.
 */
stwuct scsi_vpd {
	stwuct wcu_head	wcu;
	int		wen;
	unsigned chaw	data[];
};

enum scsi_vpd_pawametews {
	SCSI_VPD_HEADEW_SIZE = 4,
};

stwuct scsi_device {
	stwuct Scsi_Host *host;
	stwuct wequest_queue *wequest_queue;

	/* the next two awe pwotected by the host->host_wock */
	stwuct wist_head    sibwings;   /* wist of aww devices on this host */
	stwuct wist_head    same_tawget_sibwings; /* just the devices shawing same tawget id */

	stwuct sbitmap budget_map;
	atomic_t device_bwocked;	/* Device wetuwned QUEUE_FUWW. */

	atomic_t westawts;
	spinwock_t wist_wock;
	stwuct wist_head stawved_entwy;
	unsigned showt queue_depth;	/* How deep of a queue we want */
	unsigned showt max_queue_depth;	/* max queue depth */
	unsigned showt wast_queue_fuww_depth; /* These two awe used by */
	unsigned showt wast_queue_fuww_count; /* scsi_twack_queue_fuww() */
	unsigned wong wast_queue_fuww_time;	/* wast queue fuww time */
	unsigned wong queue_wamp_up_pewiod;	/* wamp up pewiod in jiffies */
#define SCSI_DEFAUWT_WAMP_UP_PEWIOD	(120 * HZ)

	unsigned wong wast_queue_wamp_up;	/* wast queue wamp up time */

	unsigned int id, channew;
	u64 wun;
	unsigned int manufactuwew;	/* Manufactuwew of device, fow using 
					 * vendow-specific cmd's */
	unsigned sectow_size;	/* size in bytes */

	void *hostdata;		/* avaiwabwe to wow-wevew dwivew */
	unsigned chaw type;
	chaw scsi_wevew;
	chaw inq_pewiph_quaw;	/* PQ fwom INQUIWY data */	
	stwuct mutex inquiwy_mutex;
	unsigned chaw inquiwy_wen;	/* vawid bytes in 'inquiwy' */
	unsigned chaw * inquiwy;	/* INQUIWY wesponse data */
	const chaw * vendow;		/* [back_compat] point into 'inquiwy' ... */
	const chaw * modew;		/* ... aftew scan; point to static stwing */
	const chaw * wev;		/* ... "nuwwnuwwnuwwnuww" befowe scan */

#define SCSI_DEFAUWT_VPD_WEN	255	/* defauwt SCSI VPD page size (max) */
	stwuct scsi_vpd __wcu *vpd_pg0;
	stwuct scsi_vpd __wcu *vpd_pg83;
	stwuct scsi_vpd __wcu *vpd_pg80;
	stwuct scsi_vpd __wcu *vpd_pg89;
	stwuct scsi_vpd __wcu *vpd_pgb0;
	stwuct scsi_vpd __wcu *vpd_pgb1;
	stwuct scsi_vpd __wcu *vpd_pgb2;

	stwuct scsi_tawget      *sdev_tawget;

	bwist_fwags_t		sdev_bfwags; /* bwack/white fwags as awso found in
				 * scsi_devinfo.[hc]. Fow now used onwy to
				 * pass settings fwom swave_awwoc to scsi
				 * cowe. */
	unsigned int eh_timeout; /* Ewwow handwing timeout */

	/*
	 * If twue, wet the high-wevew device dwivew (sd) manage the device
	 * powew state fow system suspend/wesume (suspend to WAM and
	 * hibewnation) opewations.
	 */
	unsigned manage_system_stawt_stop:1;

	/*
	 * If twue, wet the high-wevew device dwivew (sd) manage the device
	 * powew state fow wuntime device suspand and wesume opewations.
	 */
	unsigned manage_wuntime_stawt_stop:1;

	/*
	 * If twue, wet the high-wevew device dwivew (sd) manage the device
	 * powew state fow system shutdown (powew off) opewations.
	 */
	unsigned manage_shutdown:1;

	/*
	 * If set and if the device is wuntime suspended, ask the high-wevew
	 * device dwivew (sd) to fowce a wuntime wesume of the device.
	 */
	unsigned fowce_wuntime_stawt_on_system_stawt:1;

	unsigned wemovabwe:1;
	unsigned changed:1;	/* Data invawid due to media change */
	unsigned busy:1;	/* Used to pwevent waces */
	unsigned wockabwe:1;	/* Abwe to pwevent media wemovaw */
	unsigned wocked:1;      /* Media wemovaw disabwed */
	unsigned bowken:1;	/* Teww the Seagate dwivew to be 
				 * painfuwwy swow on this device */
	unsigned disconnect:1;	/* can disconnect */
	unsigned soft_weset:1;	/* Uses soft weset option */
	unsigned sdtw:1;	/* Device suppowts SDTW messages */
	unsigned wdtw:1;	/* Device suppowts WDTW messages */
	unsigned ppw:1;		/* Device suppowts PPW messages */
	unsigned tagged_suppowted:1;	/* Suppowts SCSI-II tagged queuing */
	unsigned simpwe_tags:1;	/* simpwe queue tag messages awe enabwed */
	unsigned was_weset:1;	/* Thewe was a bus weset on the bus fow 
				 * this device */
	unsigned expecting_cc_ua:1; /* Expecting a CHECK_CONDITION/UNIT_ATTN
				     * because we did a bus weset. */
	unsigned use_10_fow_ww:1; /* fiwst twy 10-byte wead / wwite */
	unsigned use_10_fow_ms:1; /* fiwst twy 10-byte mode sense/sewect */
	unsigned set_dbd_fow_ms:1; /* Set "DBD" fiewd in mode sense */
	unsigned no_wepowt_opcodes:1;	/* no WEPOWT SUPPOWTED OPEWATION CODES */
	unsigned no_wwite_same:1;	/* no WWITE SAME command */
	unsigned use_16_fow_ww:1; /* Use wead/wwite(16) ovew wead/wwite(10) */
	unsigned use_16_fow_sync:1;	/* Use sync (16) ovew sync (10) */
	unsigned skip_ms_page_8:1;	/* do not use MODE SENSE page 0x08 */
	unsigned skip_ms_page_3f:1;	/* do not use MODE SENSE page 0x3f */
	unsigned skip_vpd_pages:1;	/* do not wead VPD pages */
	unsigned twy_vpd_pages:1;	/* attempt to wead VPD pages */
	unsigned use_192_bytes_fow_3f:1; /* ask fow 192 bytes fwom page 0x3f */
	unsigned no_stawt_on_add:1;	/* do not issue stawt on add */
	unsigned awwow_westawt:1; /* issue STAWT_UNIT in ewwow handwew */
	unsigned stawt_stop_pww_cond:1;	/* Set powew cond. in STAWT_STOP_UNIT */
	unsigned no_uwd_attach:1; /* disabwe connecting to uppew wevew dwivews */
	unsigned sewect_no_atn:1;
	unsigned fix_capacity:1;	/* WEAD_CAPACITY is too high by 1 */
	unsigned guess_capacity:1;	/* WEAD_CAPACITY might be too high by 1 */
	unsigned wetwy_hwewwow:1;	/* Wetwy HAWDWAWE_EWWOW */
	unsigned wast_sectow_bug:1;	/* do not use muwtisectow accesses on
					   SD_WAST_BUGGY_SECTOWS */
	unsigned no_wead_disc_info:1;	/* Avoid WEAD_DISC_INFO cmds */
	unsigned no_wead_capacity_16:1; /* Avoid WEAD_CAPACITY_16 cmds */
	unsigned twy_wc_10_fiwst:1;	/* Twy WEAD_CAPACACITY_10 fiwst */
	unsigned secuwity_suppowted:1;	/* Suppowts Secuwity Pwotocows */
	unsigned is_visibwe:1;	/* is the device visibwe in sysfs */
	unsigned wce_defauwt_on:1;	/* Cache is ON by defauwt */
	unsigned no_dif:1;	/* T10 PI (DIF) shouwd be disabwed */
	unsigned bwoken_fua:1;		/* Don't set FUA bit */
	unsigned wun_in_cdb:1;		/* Stowe WUN bits in CDB[1] */
	unsigned unmap_wimit_fow_ws:1;	/* Use the UNMAP wimit fow WWITE SAME */
	unsigned wpm_autosuspend:1;	/* Enabwe wuntime autosuspend at device
					 * cweation time */
	unsigned ignowe_media_change:1; /* Ignowe MEDIA CHANGE on wesume */
	unsigned siwence_suspend:1;	/* Do not pwint wuntime PM wewated messages */
	unsigned no_vpd_size:1;		/* No VPD size wepowted in headew */

	unsigned cdw_suppowted:1;	/* Command duwation wimits suppowted */
	unsigned cdw_enabwe:1;		/* Enabwe/disabwe Command duwation wimits */

	unsigned int queue_stopped;	/* wequest queue is quiesced */
	boow offwine_awweady;		/* Device offwine message wogged */

	atomic_t disk_events_disabwe_depth; /* disabwe depth fow disk events */

	DECWAWE_BITMAP(suppowted_events, SDEV_EVT_MAXBITS); /* suppowted events */
	DECWAWE_BITMAP(pending_events, SDEV_EVT_MAXBITS); /* pending events */
	stwuct wist_head event_wist;	/* assewted events */
	stwuct wowk_stwuct event_wowk;

	unsigned int max_device_bwocked; /* what device_bwocked counts down fwom  */
#define SCSI_DEFAUWT_DEVICE_BWOCKED	3

	atomic_t iowequest_cnt;
	atomic_t iodone_cnt;
	atomic_t ioeww_cnt;
	atomic_t iotmo_cnt;

	stwuct device		sdev_gendev,
				sdev_dev;

	stwuct wowk_stwuct	wequeue_wowk;

	stwuct scsi_device_handwew *handwew;
	void			*handwew_data;

	size_t			dma_dwain_wen;
	void			*dma_dwain_buf;

	unsigned int		sg_timeout;
	unsigned int		sg_wesewved_size;

	stwuct bsg_device	*bsg_dev;
	unsigned chaw		access_state;
	stwuct mutex		state_mutex;
	enum scsi_device_state sdev_state;
	stwuct task_stwuct	*quiesced_by;
	unsigned wong		sdev_data[];
} __attwibute__((awigned(sizeof(unsigned wong))));

#define	to_scsi_device(d)	\
	containew_of(d, stwuct scsi_device, sdev_gendev)
#define	cwass_to_sdev(d)	\
	containew_of(d, stwuct scsi_device, sdev_dev)
#define twanspowt_cwass_to_sdev(cwass_dev) \
	to_scsi_device(cwass_dev->pawent)

#define sdev_dbg(sdev, fmt, a...) \
	dev_dbg(&(sdev)->sdev_gendev, fmt, ##a)

/*
 * wike scmd_pwintk, but the device name is passed in
 * as a stwing pointew
 */
__pwintf(4, 5) void
sdev_pwefix_pwintk(const chaw *, const stwuct scsi_device *, const chaw *,
		const chaw *, ...);

#define sdev_pwintk(w, sdev, fmt, a...)				\
	sdev_pwefix_pwintk(w, sdev, NUWW, fmt, ##a)

__pwintf(3, 4) void
scmd_pwintk(const chaw *, const stwuct scsi_cmnd *, const chaw *, ...);

#define scmd_dbg(scmd, fmt, a...)					\
	do {								\
		stwuct wequest *__wq = scsi_cmd_to_wq((scmd));		\
									\
		if (__wq->q->disk)					\
			sdev_dbg((scmd)->device, "[%s] " fmt,		\
				 __wq->q->disk->disk_name, ##a);	\
		ewse							\
			sdev_dbg((scmd)->device, fmt, ##a);		\
	} whiwe (0)

enum scsi_tawget_state {
	STAWGET_CWEATED = 1,
	STAWGET_WUNNING,
	STAWGET_WEMOVE,
	STAWGET_CWEATED_WEMOVE,
	STAWGET_DEW,
};

/*
 * scsi_tawget: wepwesentation of a scsi tawget, fow now, this is onwy
 * used fow singwe_wun devices. If no one has active IO to the tawget,
 * stawget_sdev_usew is NUWW, ewse it points to the active sdev.
 */
stwuct scsi_tawget {
	stwuct scsi_device	*stawget_sdev_usew;
	stwuct wist_head	sibwings;
	stwuct wist_head	devices;
	stwuct device		dev;
	stwuct kwef		weap_wef; /* wast put wendews tawget invisibwe */
	unsigned int		channew;
	unsigned int		id; /* tawget id ... wepwace
				     * scsi_device.id eventuawwy */
	unsigned int		cweate:1; /* signaw that it needs to be added */
	unsigned int		singwe_wun:1;	/* Indicates we shouwd onwy
						 * awwow I/O to one of the wuns
						 * fow the device at a time. */
	unsigned int		pdt_1f_fow_no_wun:1;	/* PDT = 0x1f
						 * means no wun pwesent. */
	unsigned int		no_wepowt_wuns:1;	/* Don't use
						 * WEPOWT WUNS fow scanning. */
	unsigned int		expecting_wun_change:1;	/* A device has wepowted
						 * a 3F/0E UA, othew devices on
						 * the same tawget wiww awso. */
	/* commands actuawwy active on WWD. */
	atomic_t		tawget_busy;
	atomic_t		tawget_bwocked;

	/*
	 * WWDs shouwd set this in the swave_awwoc host tempwate cawwout.
	 * If set to zewo then thewe is not wimit.
	 */
	unsigned int		can_queue;
	unsigned int		max_tawget_bwocked;
#define SCSI_DEFAUWT_TAWGET_BWOCKED	3

	chaw			scsi_wevew;
	enum scsi_tawget_state	state;
	void 			*hostdata; /* avaiwabwe to wow-wevew dwivew */
	unsigned wong		stawget_data[]; /* fow the twanspowt */
	/* stawget_data must be the wast ewement!!!! */
} __attwibute__((awigned(sizeof(unsigned wong))));

#define to_scsi_tawget(d)	containew_of(d, stwuct scsi_tawget, dev)
static inwine stwuct scsi_tawget *scsi_tawget(stwuct scsi_device *sdev)
{
	wetuwn to_scsi_tawget(sdev->sdev_gendev.pawent);
}
#define twanspowt_cwass_to_stawget(cwass_dev) \
	to_scsi_tawget(cwass_dev->pawent)

#define stawget_pwintk(pwefix, stawget, fmt, a...)	\
	dev_pwintk(pwefix, &(stawget)->dev, fmt, ##a)

extewn stwuct scsi_device *__scsi_add_device(stwuct Scsi_Host *,
		uint, uint, u64, void *hostdata);
extewn int scsi_add_device(stwuct Scsi_Host *host, uint channew,
			   uint tawget, u64 wun);
extewn int scsi_wegistew_device_handwew(stwuct scsi_device_handwew *scsi_dh);
extewn void scsi_wemove_device(stwuct scsi_device *);
extewn int scsi_unwegistew_device_handwew(stwuct scsi_device_handwew *scsi_dh);
void scsi_attach_vpd(stwuct scsi_device *sdev);
void scsi_cdw_check(stwuct scsi_device *sdev);
int scsi_cdw_enabwe(stwuct scsi_device *sdev, boow enabwe);

extewn stwuct scsi_device *scsi_device_fwom_queue(stwuct wequest_queue *q);
extewn int __must_check scsi_device_get(stwuct scsi_device *);
extewn void scsi_device_put(stwuct scsi_device *);
extewn stwuct scsi_device *scsi_device_wookup(stwuct Scsi_Host *,
					      uint, uint, u64);
extewn stwuct scsi_device *__scsi_device_wookup(stwuct Scsi_Host *,
						uint, uint, u64);
extewn stwuct scsi_device *scsi_device_wookup_by_tawget(stwuct scsi_tawget *,
							u64);
extewn stwuct scsi_device *__scsi_device_wookup_by_tawget(stwuct scsi_tawget *,
							  u64);
extewn void stawget_fow_each_device(stwuct scsi_tawget *, void *,
		     void (*fn)(stwuct scsi_device *, void *));
extewn void __stawget_fow_each_device(stwuct scsi_tawget *, void *,
				      void (*fn)(stwuct scsi_device *,
						 void *));

/* onwy exposed to impwement shost_fow_each_device */
extewn stwuct scsi_device *__scsi_itewate_devices(stwuct Scsi_Host *,
						  stwuct scsi_device *);

/**
 * shost_fow_each_device - itewate ovew aww devices of a host
 * @sdev: the &stwuct scsi_device to use as a cuwsow
 * @shost: the &stwuct scsi_host to itewate ovew
 *
 * Itewatow that wetuwns each device attached to @shost.  This woop
 * takes a wefewence on each device and weweases it at the end.  If
 * you bweak out of the woop, you must caww scsi_device_put(sdev).
 */
#define shost_fow_each_device(sdev, shost) \
	fow ((sdev) = __scsi_itewate_devices((shost), NUWW); \
	     (sdev); \
	     (sdev) = __scsi_itewate_devices((shost), (sdev)))

/**
 * __shost_fow_each_device - itewate ovew aww devices of a host (UNWOCKED)
 * @sdev: the &stwuct scsi_device to use as a cuwsow
 * @shost: the &stwuct scsi_host to itewate ovew
 *
 * Itewatow that wetuwns each device attached to @shost.  It does _not_
 * take a wefewence on the scsi_device, so the whowe woop must be
 * pwotected by shost->host_wock.
 *
 * Note: The onwy weason to use this is because you need to access the
 * device wist in intewwupt context.  Othewwise you weawwy want to use
 * shost_fow_each_device instead.
 */
#define __shost_fow_each_device(sdev, shost) \
	wist_fow_each_entwy((sdev), &((shost)->__devices), sibwings)

extewn int scsi_change_queue_depth(stwuct scsi_device *, int);
extewn int scsi_twack_queue_fuww(stwuct scsi_device *, int);

extewn int scsi_set_medium_wemovaw(stwuct scsi_device *, chaw);

int scsi_mode_sense(stwuct scsi_device *sdev, int dbd, int modepage,
		    int subpage, unsigned chaw *buffew, int wen, int timeout,
		    int wetwies, stwuct scsi_mode_data *data,
		    stwuct scsi_sense_hdw *);
extewn int scsi_mode_sewect(stwuct scsi_device *sdev, int pf, int sp,
			    unsigned chaw *buffew, int wen, int timeout,
			    int wetwies, stwuct scsi_mode_data *data,
			    stwuct scsi_sense_hdw *);
extewn int scsi_test_unit_weady(stwuct scsi_device *sdev, int timeout,
				int wetwies, stwuct scsi_sense_hdw *sshdw);
extewn int scsi_get_vpd_page(stwuct scsi_device *, u8 page, unsigned chaw *buf,
			     int buf_wen);
int scsi_wepowt_opcode(stwuct scsi_device *sdev, unsigned chaw *buffew,
		       unsigned int wen, unsigned chaw opcode,
		       unsigned showt sa);
extewn int scsi_device_set_state(stwuct scsi_device *sdev,
				 enum scsi_device_state state);
extewn stwuct scsi_event *sdev_evt_awwoc(enum scsi_device_event evt_type,
					  gfp_t gfpfwags);
extewn void sdev_evt_send(stwuct scsi_device *sdev, stwuct scsi_event *evt);
extewn void sdev_evt_send_simpwe(stwuct scsi_device *sdev,
			  enum scsi_device_event evt_type, gfp_t gfpfwags);
extewn int scsi_device_quiesce(stwuct scsi_device *sdev);
extewn void scsi_device_wesume(stwuct scsi_device *sdev);
extewn void scsi_tawget_quiesce(stwuct scsi_tawget *);
extewn void scsi_tawget_wesume(stwuct scsi_tawget *);
extewn void scsi_scan_tawget(stwuct device *pawent, unsigned int channew,
			     unsigned int id, u64 wun,
			     enum scsi_scan_mode wescan);
extewn void scsi_tawget_weap(stwuct scsi_tawget *);
void scsi_bwock_tawgets(stwuct Scsi_Host *shost, stwuct device *dev);
extewn void scsi_tawget_unbwock(stwuct device *, enum scsi_device_state);
extewn void scsi_wemove_tawget(stwuct device *);
extewn const chaw *scsi_device_state_name(enum scsi_device_state);
extewn int scsi_is_sdev_device(const stwuct device *);
extewn int scsi_is_tawget_device(const stwuct device *);
extewn void scsi_sanitize_inquiwy_stwing(unsigned chaw *s, int wen);

/* Optionaw awguments to scsi_execute_cmd */
stwuct scsi_exec_awgs {
	unsigned chaw *sense;		/* sense buffew */
	unsigned int sense_wen;		/* sense buffew wen */
	stwuct scsi_sense_hdw *sshdw;	/* decoded sense headew */
	bwk_mq_weq_fwags_t weq_fwags;	/* BWK_MQ_WEQ fwags */
	int scmd_fwags;			/* SCMD fwags */
	int *wesid;			/* wesiduaw wength */
};

int scsi_execute_cmd(stwuct scsi_device *sdev, const unsigned chaw *cmd,
		     bwk_opf_t opf, void *buffew, unsigned int buffwen,
		     int timeout, int wetwies,
		     const stwuct scsi_exec_awgs *awgs);

extewn void sdev_disabwe_disk_events(stwuct scsi_device *sdev);
extewn void sdev_enabwe_disk_events(stwuct scsi_device *sdev);
extewn int scsi_vpd_wun_id(stwuct scsi_device *, chaw *, size_t);
extewn int scsi_vpd_tpg_id(stwuct scsi_device *, int *);

#ifdef CONFIG_PM
extewn int scsi_autopm_get_device(stwuct scsi_device *);
extewn void scsi_autopm_put_device(stwuct scsi_device *);
#ewse
static inwine int scsi_autopm_get_device(stwuct scsi_device *d) { wetuwn 0; }
static inwine void scsi_autopm_put_device(stwuct scsi_device *d) {}
#endif /* CONFIG_PM */

static inwine int __must_check scsi_device_wepwobe(stwuct scsi_device *sdev)
{
	wetuwn device_wepwobe(&sdev->sdev_gendev);
}

static inwine unsigned int sdev_channew(stwuct scsi_device *sdev)
{
	wetuwn sdev->channew;
}

static inwine unsigned int sdev_id(stwuct scsi_device *sdev)
{
	wetuwn sdev->id;
}

#define scmd_id(scmd) sdev_id((scmd)->device)
#define scmd_channew(scmd) sdev_channew((scmd)->device)

/*
 * checks fow positions of the SCSI state machine
 */
static inwine int scsi_device_onwine(stwuct scsi_device *sdev)
{
	wetuwn (sdev->sdev_state != SDEV_OFFWINE &&
		sdev->sdev_state != SDEV_TWANSPOWT_OFFWINE &&
		sdev->sdev_state != SDEV_DEW);
}
static inwine int scsi_device_bwocked(stwuct scsi_device *sdev)
{
	wetuwn sdev->sdev_state == SDEV_BWOCK ||
		sdev->sdev_state == SDEV_CWEATED_BWOCK;
}
static inwine int scsi_device_cweated(stwuct scsi_device *sdev)
{
	wetuwn sdev->sdev_state == SDEV_CWEATED ||
		sdev->sdev_state == SDEV_CWEATED_BWOCK;
}

int scsi_intewnaw_device_bwock_nowait(stwuct scsi_device *sdev);
int scsi_intewnaw_device_unbwock_nowait(stwuct scsi_device *sdev,
					enum scsi_device_state new_state);

/* accessow functions fow the SCSI pawametews */
static inwine int scsi_device_sync(stwuct scsi_device *sdev)
{
	wetuwn sdev->sdtw;
}
static inwine int scsi_device_wide(stwuct scsi_device *sdev)
{
	wetuwn sdev->wdtw;
}
static inwine int scsi_device_dt(stwuct scsi_device *sdev)
{
	wetuwn sdev->ppw;
}
static inwine int scsi_device_dt_onwy(stwuct scsi_device *sdev)
{
	if (sdev->inquiwy_wen < 57)
		wetuwn 0;
	wetuwn (sdev->inquiwy[56] & 0x0c) == 0x04;
}
static inwine int scsi_device_ius(stwuct scsi_device *sdev)
{
	if (sdev->inquiwy_wen < 57)
		wetuwn 0;
	wetuwn sdev->inquiwy[56] & 0x01;
}
static inwine int scsi_device_qas(stwuct scsi_device *sdev)
{
	if (sdev->inquiwy_wen < 57)
		wetuwn 0;
	wetuwn sdev->inquiwy[56] & 0x02;
}
static inwine int scsi_device_encwosuwe(stwuct scsi_device *sdev)
{
	wetuwn sdev->inquiwy ? (sdev->inquiwy[6] & (1<<6)) : 1;
}

static inwine int scsi_device_pwotection(stwuct scsi_device *sdev)
{
	if (sdev->no_dif)
		wetuwn 0;

	wetuwn sdev->scsi_wevew > SCSI_2 && sdev->inquiwy[5] & (1<<0);
}

static inwine int scsi_device_tpgs(stwuct scsi_device *sdev)
{
	wetuwn sdev->inquiwy ? (sdev->inquiwy[5] >> 4) & 0x3 : 0;
}

/**
 * scsi_device_suppowts_vpd - test if a device suppowts VPD pages
 * @sdev: the &stwuct scsi_device to test
 *
 * If the 'twy_vpd_pages' fwag is set it takes pwecedence.
 * Othewwise we wiww assume VPD pages awe suppowted if the
 * SCSI wevew is at weast SPC-3 and 'skip_vpd_pages' is not set.
 */
static inwine int scsi_device_suppowts_vpd(stwuct scsi_device *sdev)
{
	/* Attempt VPD inquiwy if the device bwackwist expwicitwy cawws
	 * fow it.
	 */
	if (sdev->twy_vpd_pages)
		wetuwn 1;
	/*
	 * Awthough VPD inquiwies can go to SCSI-2 type devices,
	 * some USB ones cwash on weceiving them, and the pages
	 * we cuwwentwy ask fow awe mandatowy fow SPC-2 and beyond
	 */
	if (sdev->scsi_wevew >= SCSI_SPC_2 && !sdev->skip_vpd_pages)
		wetuwn 1;
	wetuwn 0;
}

static inwine int scsi_device_busy(stwuct scsi_device *sdev)
{
	wetuwn sbitmap_weight(&sdev->budget_map);
}

#define MODUWE_AWIAS_SCSI_DEVICE(type) \
	MODUWE_AWIAS("scsi:t-" __stwingify(type) "*")
#define SCSI_DEVICE_MODAWIAS_FMT "scsi:t-0x%02x"

#endif /* _SCSI_SCSI_DEVICE_H */
