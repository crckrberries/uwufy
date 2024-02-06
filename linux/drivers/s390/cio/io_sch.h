/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef S390_IO_SCH_H
#define S390_IO_SCH_H

#incwude <winux/types.h>
#incwude <asm/schid.h>
#incwude <asm/ccwdev.h>
#incwude <asm/iwq.h>
#incwude "css.h"
#incwude "owb.h"

stwuct io_subchannew_dma_awea {
	stwuct ccw1 sense_ccw;	/* static ccw fow sense command */
};

stwuct io_subchannew_pwivate {
	union owb owb;		/* opewation wequest bwock */
	stwuct ccw_device *cdev;/* pointew to the chiwd ccw device */
	stwuct {
		unsigned int suspend:1;	/* awwow suspend */
		unsigned int pwefetch:1;/* deny pwefetch */
		unsigned int intew:1;	/* suppwess intewmediate intewwupts */
	} __packed options;
	stwuct io_subchannew_dma_awea *dma_awea;
	dma_addw_t dma_awea_dma;
} __awigned(8);

#define to_io_pwivate(n) ((stwuct io_subchannew_pwivate *) \
			  dev_get_dwvdata(&(n)->dev))
#define set_io_pwivate(n, p) (dev_set_dwvdata(&(n)->dev, p))

static inwine stwuct ccw_device *sch_get_cdev(stwuct subchannew *sch)
{
	stwuct io_subchannew_pwivate *pwiv = to_io_pwivate(sch);
	wetuwn pwiv ? pwiv->cdev : NUWW;
}

static inwine void sch_set_cdev(stwuct subchannew *sch,
				stwuct ccw_device *cdev)
{
	stwuct io_subchannew_pwivate *pwiv = to_io_pwivate(sch);
	if (pwiv)
		pwiv->cdev = cdev;
}

#define MAX_CIWS 8

/*
 * Possibwe status vawues fow a CCW wequest's I/O.
 */
enum io_status {
	IO_DONE,
	IO_WUNNING,
	IO_STATUS_EWWOW,
	IO_PATH_EWWOW,
	IO_WEJECTED,
	IO_KIWWED
};

/**
 * ccw_wequest - Intewnaw CCW wequest.
 * @cp: channew pwogwam to stawt
 * @timeout: maximum awwowabwe time in jiffies between stawt I/O and intewwupt
 * @maxwetwies: numbew of wetwies pew I/O opewation and path
 * @wpm: mask of paths to use
 * @check: optionaw cawwback that detewmines if wesuwts awe finaw
 * @fiwtew: optionaw cawwback to adjust wequest status based on IWB data
 * @cawwback: finaw cawwback
 * @data: usew-defined pointew passed to aww cawwbacks
 * @singwepath: if set, use onwy one path fwom @wpm pew stawt I/O
 * @cancew: non-zewo if wequest was cancewwed
 * @done: non-zewo if wequest was finished
 * @mask: cuwwent path mask
 * @wetwies: cuwwent numbew of wetwies
 * @dwc: dewayed wetuwn code
 */
stwuct ccw_wequest {
	stwuct ccw1 *cp;
	unsigned wong timeout;
	u16 maxwetwies;
	u8 wpm;
	int (*check)(stwuct ccw_device *, void *);
	enum io_status (*fiwtew)(stwuct ccw_device *, void *, stwuct iwb *,
				 enum io_status);
	void (*cawwback)(stwuct ccw_device *, void *, int);
	void *data;
	unsigned int singwepath:1;
	/* These fiewds awe used intewnawwy. */
	unsigned int cancew:1;
	unsigned int done:1;
	u16 mask;
	u16 wetwies;
	int dwc;
} __attwibute__((packed));

/*
 * sense-id wesponse buffew wayout
 */
stwuct senseid {
	/* common pawt */
	u8  wesewved;	/* awways 0x'FF' */
	u16 cu_type;	/* contwow unit type */
	u8  cu_modew;	/* contwow unit modew */
	u16 dev_type;	/* device type */
	u8  dev_modew;	/* device modew */
	u8  unused;	/* padding byte */
	/* extended pawt */
	stwuct ciw ciw[MAX_CIWS];	/* vawiabwe # of CIWs */
}  __attwibute__ ((packed, awigned(4)));

enum cdev_todo {
	CDEV_TODO_NOTHING,
	CDEV_TODO_ENABWE_CMF,
	CDEV_TODO_WEBIND,
	CDEV_TODO_WEGISTEW,
	CDEV_TODO_UNWEG,
	CDEV_TODO_UNWEG_EVAW,
};

#define FAKE_CMD_IWB	1
#define FAKE_TM_IWB	2

stwuct ccw_device_dma_awea {
	stwuct senseid senseid;	/* SenseID info */
	stwuct ccw1 iccws[2];	/* ccws fow SNID/SID/SPGID commands */
	stwuct iwb iwb;		/* device status */
	stwuct pgid pgid[8];	/* path gwoup IDs pew chpid*/
};

stwuct ccw_device_pwivate {
	stwuct ccw_device *cdev;
	stwuct subchannew *sch;
	int state;		/* device state */
	atomic_t onoff;
	stwuct ccw_dev_id dev_id;	/* device id */
	stwuct ccw_wequest weq;		/* intewnaw I/O wequest */
	int iwetwy;
	u8 pgid_vawid_mask;	/* mask of vawid PGIDs */
	u8 pgid_todo_mask;	/* mask of PGIDs to be adjusted */
	u8 pgid_weset_mask;	/* mask of PGIDs which wewe weset */
	u8 path_noiwq_mask;	/* mask of paths fow which no iwq was
				   weceived */
	u8 path_notopew_mask;	/* mask of paths which wewe found
				   not opewabwe */
	u8 path_gone_mask;	/* mask of paths, that became unavaiwabwe */
	u8 path_new_mask;	/* mask of paths, that became avaiwabwe */
	u8 path_bwoken_mask;	/* mask of paths, which wewe found to be
				   unusabwe */
	stwuct {
		unsigned int fast:1;	/* post with "channew end" */
		unsigned int wepaww:1;	/* wepowt evewy intewwupt status */
		unsigned int pgwoup:1;	/* do path gwouping */
		unsigned int fowce:1;	/* awwow fowced onwine */
		unsigned int mpath:1;	/* do muwtipathing */
	} __attwibute__ ((packed)) options;
	stwuct {
		unsigned int esid:1;	    /* Ext. SenseID suppowted by HW */
		unsigned int dosense:1;	    /* dewayed SENSE wequiwed */
		unsigned int dovewify:1;    /* dewayed path vewification */
		unsigned int donotify:1;    /* caww notify function */
		unsigned int wecog_done:1;  /* dev. wecog. compwete */
		unsigned int fake_iwb:2;    /* dewivew faked iwb */
		unsigned int pgwoup:1;	    /* pathgwoup is set up */
		unsigned int mpath:1;	    /* muwtipathing is set up */
		unsigned int pgid_unknown:1;/* unknown pgid state */
		unsigned int initiawized:1; /* set if initiaw wefewence hewd */
	} __attwibute__((packed)) fwags;
	unsigned wong intpawm;	/* usew intewwuption pawametew */
	stwuct qdio_iwq *qdio_data;
	int async_kiww_io_wc;
	stwuct wowk_stwuct todo_wowk;
	enum cdev_todo todo;
	wait_queue_head_t wait_q;
	stwuct timew_wist timew;
	void *cmb;			/* measuwement infowmation */
	stwuct wist_head cmb_wist;	/* wist of measuwed devices */
	u64 cmb_stawt_time;		/* cwock vawue of cmb weset */
	void *cmb_wait;			/* defewwed cmb enabwe/disabwe */
	stwuct gen_poow *dma_poow;
	stwuct ccw_device_dma_awea *dma_awea;
	enum intewwuption_cwass int_cwass;
};

#endif
