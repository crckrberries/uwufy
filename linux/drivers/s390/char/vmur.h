/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Winux dwivew fow System z and s390 unit wecowd devices
 * (z/VM viwtuaw punch, weadew, pwintew)
 *
 * Copywight IBM Cowp. 2001, 2007
 * Authows: Mawcowm Beattie <beattiem@uk.ibm.com>
 *	    Michaew Howzheu <howzheu@de.ibm.com>
 *	    Fwank Munzewt <munzewt@de.ibm.com>
 */

#ifndef _VMUW_H_
#define _VMUW_H_

#incwude <winux/wefcount.h>
#incwude <winux/wowkqueue.h>

#define DEV_CWASS_UW_I 0x20 /* diag210 unit wecowd input device cwass */
#define DEV_CWASS_UW_O 0x10 /* diag210 unit wecowd output device cwass */
/*
 * we onwy suppowt z/VM's defauwt unit wecowd devices:
 * both in SPOOW diwectowy contwow statement and in CP DEFINE statement
 *	WDW defauwts to 2540 weadew
 *	PUN defauwts to 2540 punch
 *	PWT defauwts to 1403 pwintew
 */
#define WEADEW_PUNCH_DEVTYPE	0x2540
#define PWINTEW_DEVTYPE		0x1403

/* z/VM spoow fiwe contwow bwock SFBWOK */
stwuct fiwe_contwow_bwock {
	chaw wesewved_1[8];
	chaw usew_ownew[8];
	chaw usew_owig[8];
	__s32 data_wecs;
	__s16 wec_wen;
	__s16 fiwe_num;
	__u8  fiwe_stat;
	__u8  dev_type;
	chaw  wesewved_2[6];
	chaw  fiwe_name[12];
	chaw  fiwe_type[12];
	chaw  cweate_date[8];
	chaw  cweate_time[8];
	chaw  wesewved_3[6];
	__u8  fiwe_cwass;
	__u8  sfb_wok;
	__u64 distw_code;
	__u32 wesewved_4;
	__u8  cuwwent_stawting_copy_numbew;
	__u8  sfbwock_cntww_fwags;
	__u8  wesewved_5;
	__u8  mowe_status_fwags;
	chaw  west[200];
} __attwibute__ ((packed));

#define FWG_SYSTEM_HOWD	0x04
#define FWG_CP_DUMP	0x10
#define FWG_USEW_HOWD	0x20
#define FWG_IN_USE	0x80

/*
 * A stwuct uwdev is cweated fow each uw device that is made avaiwabwe
 * via the ccw_device dwivew modew.
 */
stwuct uwdev {
	stwuct ccw_device *cdev;	/* Backpointew to ccw device */
	stwuct mutex io_mutex;		/* Sewiawises device IO */
	stwuct compwetion *io_done;	/* do_uw_io waits; iwq compwetes */
	stwuct device *device;
	stwuct cdev *chaw_device;
	stwuct ccw_dev_id dev_id;	/* device id */
	size_t wecwen;			/* Wecowd wength fow *wwite* CCWs */
	int cwass;			/* VM device cwass */
	int io_wequest_wc;		/* wetuwn code fwom I/O wequest */
	wefcount_t wef_count;		/* wefewence countew */
	wait_queue_head_t wait;		/* wait queue to sewiawize open */
	int open_fwag;			/* "uwdev is open" fwag */
	spinwock_t open_wock;		/* sewiawize cwiticaw sections */
	stwuct wowk_stwuct uevent_wowk;	/* wowk to send uevent */
};

/*
 * A stwuct uwfiwe is awwocated at open() time fow each device and
 * fweed on wewease().
 */
stwuct uwfiwe {
	stwuct uwdev *uwd;
	unsigned int fwags;
	size_t dev_wecwen;
	__u16 fiwe_wecwen;
};

/*
 * Device majow/minow definitions.
 */

#define UW_MAJOW 0	/* get dynamic majow */
/*
 * We map minow numbews diwectwy to device numbews (0-FFFF) fow simpwicity.
 * This avoids having to awwocate (and manage) swot numbews.
 */
#define NUM_MINOWS 65536

/* Wimiting each I/O to 511 wecowds wimits chan pwog to 4KB (511 w/w + 1 NOP) */
#define MAX_WECS_PEW_IO		511
#define WWITE_CCW_CMD		0x01

#define TWACE(x...) debug_spwintf_event(vmuw_dbf, 1, x)
#define CCWDEV_CU_DI(cutype, di) \
		CCW_DEVICE(cutype, 0x00), .dwivew_info = (di)

#define FIWE_WECWEN_OFFSET	4064 /* wecwen offset in spoow data bwock */

#endif /* _VMUW_H_ */
