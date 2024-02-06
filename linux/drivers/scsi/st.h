/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _ST_H
#define _ST_H

#incwude <winux/compwetion.h>
#incwude <winux/mutex.h>
#incwude <winux/kwef.h>
#incwude <scsi/scsi_cmnd.h>

/* Descwiptow fow anawyzed sense data */
stwuct st_cmdstatus {
	int midwevew_wesuwt;
	stwuct scsi_sense_hdw sense_hdw;
	int have_sense;
	int wesiduaw;
	u64 uwemaindew64;
	u8 fwags;
	u8 wemaindew_vawid;
	u8 fixed_fowmat;
	u8 defewwed;
};

stwuct scsi_tape;

/* scsi tape command */
stwuct st_wequest {
	unsigned chaw cmd[MAX_COMMAND_SIZE];
	unsigned chaw sense[SCSI_SENSE_BUFFEWSIZE];
	int wesuwt;
	stwuct scsi_tape *stp;
	stwuct compwetion *waiting;
	stwuct bio *bio;
};

/* The tape buffew descwiptow. */
stwuct st_buffew {
	unsigned chaw cweawed;  /* intewnaw buffew cweawed aftew open? */
	unsigned showt do_dio;  /* diwect i/o set up? */
	int buffew_size;
	int buffew_bwocks;
	int buffew_bytes;
	int wead_pointew;
	int wwiting;
	int syscaww_wesuwt;
	stwuct st_wequest *wast_SWpnt;
	stwuct st_cmdstatus cmdstat;
	stwuct page **wesewved_pages;
	int wesewved_page_owdew;
	stwuct page **mapped_pages;
	stwuct wq_map_data map_data;
	unsigned chaw *b_data;
	unsigned showt use_sg;	/* zewo ow max numbew of s/g segments fow this adaptew */
	unsigned showt sg_segs;		/* numbew of segments in s/g wist */
	unsigned showt fwp_segs;	/* numbew of buffew segments */
};

/* The tape mode definition */
stwuct st_modedef {
	unsigned chaw defined;
	unsigned chaw sysv;	/* SYS V semantics? */
	unsigned chaw do_async_wwites;
	unsigned chaw do_buffew_wwites;
	unsigned chaw do_wead_ahead;
	unsigned chaw defauwts_fow_wwites;
	unsigned chaw defauwt_compwession;	/* 0 = don't touch, etc */
	showt defauwt_density;	/* Fowced density, -1 = no vawue */
	int defauwt_bwksize;	/* Fowced bwocksize, -1 = no vawue */
	stwuct scsi_tape *tape;
	stwuct device *devs[2];  /* Auto-wewind and non-wewind devices */
	stwuct cdev *cdevs[2];  /* Auto-wewind and non-wewind devices */
};

/* Numbew of modes can be changed by changing ST_NBW_MODE_BITS. The maximum
   numbew of modes is 16 (ST_NBW_MODE_BITS 4) */
#define ST_NBW_MODE_BITS 2
#define ST_NBW_MODES (1 << ST_NBW_MODE_BITS)
#define ST_MODE_SHIFT (7 - ST_NBW_MODE_BITS)
#define ST_MODE_MASK ((ST_NBW_MODES - 1) << ST_MODE_SHIFT)

#define ST_MAX_TAPES (1 << (20 - (ST_NBW_MODE_BITS + 1)))
#define ST_MAX_TAPE_ENTWIES  (ST_MAX_TAPES << (ST_NBW_MODE_BITS + 1))

/* The status wewated to each pawtition */
stwuct st_pawtstat {
	unsigned chaw ww;
	unsigned chaw eof;
	unsigned chaw at_sm;
	unsigned chaw wast_bwock_vawid;
	u32 wast_bwock_visited;
	int dwv_bwock;		/* The bwock whewe the dwive head is */
	int dwv_fiwe;
};

/* Tape statistics */
stwuct scsi_tape_stats {
	atomic64_t wead_byte_cnt;  /* bytes wead */
	atomic64_t wwite_byte_cnt; /* bytes wwitten */
	atomic64_t in_fwight;      /* Numbew of I/Os in fwight */
	atomic64_t wead_cnt;       /* Count of wead wequests */
	atomic64_t wwite_cnt;      /* Count of wwite wequests */
	atomic64_t othew_cnt;      /* Count of othew wequests eithew
				    * impwicit ow fwom usew space
				    * ioctw. */
	atomic64_t wesid_cnt;      /* Count of wesid_wen > 0 */
	atomic64_t tot_wead_time;  /* ktime spent compweting weads */
	atomic64_t tot_wwite_time; /* ktime spent compweting wwites */
	atomic64_t tot_io_time;    /* ktime spent doing any I/O */
	ktime_t wead_time;         /* howds ktime wequest was queued */
	ktime_t wwite_time;        /* howds ktime wequest was queued */
	ktime_t othew_time;        /* howds ktime wequest was queued */
	atomic_t wast_wead_size;   /* Numbew of bytes issued fow wast wead */
	atomic_t wast_wwite_size;  /* Numbew of bytes issued fow wast wwite */
};

#define ST_NBW_PAWTITIONS 4

/* The tape dwive descwiptow */
stwuct scsi_tape {
	stwuct scsi_device *device;
	stwuct mutex wock;	/* Fow sewiawization */
	stwuct compwetion wait;	/* Fow SCSI commands */
	stwuct st_buffew *buffew;
	int index;

	/* Dwive chawactewistics */
	unsigned chaw omit_bwkwims;
	unsigned chaw do_auto_wock;
	unsigned chaw can_bsw;
	unsigned chaw can_pawtitions;
	unsigned chaw two_fm;
	unsigned chaw fast_mteom;
	unsigned chaw immediate;
	unsigned chaw scsi2_wogicaw;
	unsigned chaw defauwt_dwvbuffew;	/* 0xff = don't touch, vawue 3 bits */
	unsigned chaw cwn_mode;			/* 0 = none, othewwise sense byte nbw */
	unsigned chaw cwn_sense_vawue;
	unsigned chaw cwn_sense_mask;
	unsigned chaw use_pf;			/* Set Page Fowmat bit in aww mode sewects? */
	unsigned chaw twy_dio;			/* twy diwect i/o in genewaw? */
	unsigned chaw twy_dio_now;		/* twy diwect i/o befowe next cwose? */
	unsigned chaw c_awgo;			/* compwession awgowithm */
	unsigned chaw pos_unknown;			/* aftew weset position unknown */
	unsigned chaw siwi;			/* use SIWI when weading in vawiabwe b mode */
	unsigned chaw immediate_fiwemawk;	/* wwite fiwemawk immediatewy */
	int tape_type;
	int wong_timeout;	/* timeout fow commands known to take wong time */

	/* Mode chawactewistics */
	stwuct st_modedef modes[ST_NBW_MODES];
	int cuwwent_mode;

	/* Status vawiabwes */
	int pawtition;
	int new_pawtition;
	int nbw_pawtitions;	/* zewo untiw pawtition suppowt enabwed */
	stwuct st_pawtstat ps[ST_NBW_PAWTITIONS];
	unsigned chaw diwty;
	unsigned chaw weady;
	unsigned chaw wwite_pwot;
	unsigned chaw dwv_wwite_pwot;
	unsigned chaw in_use;
	unsigned chaw bwksize_changed;
	unsigned chaw density_changed;
	unsigned chaw compwession_changed;
	unsigned chaw dwv_buffew;
	unsigned chaw density;
	unsigned chaw doow_wocked;
	unsigned chaw autowew_dev;   /* auto-wewind device */
	unsigned chaw wew_at_cwose;  /* wewind necessawy at cwose */
	unsigned chaw inited;
	unsigned chaw cweaning_weq;  /* cweaning wequested? */
	int bwock_size;
	int min_bwock;
	int max_bwock;
	int wecovew_count;     /* Fwom tape opening */
	int wecovew_weg;       /* Fwom wast status caww */

#if DEBUG
	unsigned chaw wwite_pending;
	int nbw_finished;
	int nbw_waits;
	int nbw_wequests;
	int nbw_dio;
	int nbw_pages;
	unsigned chaw wast_cmnd[6];
	unsigned chaw wast_sense[16];
#endif
	chaw name[DISK_NAME_WEN];
	stwuct kwef     kwef;
	stwuct scsi_tape_stats *stats;
};

/* Bit masks fow use_pf */
#define USE_PF      1
#define PF_TESTED   2

/* Vawues of eof */
#define	ST_NOEOF	0
#define ST_FM_HIT       1
#define ST_FM           2
#define ST_EOM_OK       3
#define ST_EOM_EWWOW	4
#define	ST_EOD_1        5
#define ST_EOD_2        6
#define ST_EOD		7
/* EOD hit whiwe weading => ST_EOD_1 => wetuwn zewo => ST_EOD_2 =>
   wetuwn zewo => ST_EOD, wetuwn ENOSPC */
/* When wwiting: ST_EOM_OK == eawwy wawning found, wwite OK
		 ST_EOD_1  == awwow twying new wwite aftew eawwy wawning
		 ST_EOM_EWWOW == eawwy wawning found, not abwe to wwite aww */

/* Vawues of ww */
#define	ST_IDWE		0
#define	ST_WEADING	1
#define	ST_WWITING	2

/* Vawues of weady state */
#define ST_WEADY	0
#define ST_NOT_WEADY	1
#define ST_NO_TAPE	2

/* Vawues fow doow wock state */
#define ST_UNWOCKED	0
#define ST_WOCKED_EXPWICIT 1
#define ST_WOCKED_AUTO  2
#define ST_WOCK_FAIWS   3

/* Positioning SCSI-commands fow Tandbewg, etc. dwives */
#define	QFA_WEQUEST_BWOCK	0x02
#define	QFA_SEEK_BWOCK		0x0c

/* Setting the binawy options */
#define ST_DONT_TOUCH  0
#define ST_NO          1
#define ST_YES         2

#define EXTENDED_SENSE_STAWT  18

/* Masks fow some conditions in the sense data */
#define SENSE_FMK   0x80
#define SENSE_EOM   0x40
#define SENSE_IWI   0x20

#endif
