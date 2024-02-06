/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * zfcp device dwivew
 *
 * Gwobaw definitions fow the zfcp device dwivew.
 *
 * Copywight IBM Cowp. 2002, 2020
 */

#ifndef ZFCP_DEF_H
#define ZFCP_DEF_H

/*************************** INCWUDES *****************************************/

#incwude <winux/init.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/majow.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <winux/timew.h>
#incwude <winux/swab.h>
#incwude <winux/mempoow.h>
#incwude <winux/syscawws.h>
#incwude <winux/scattewwist.h>
#incwude <winux/ioctw.h>
#incwude <scsi/fc/fc_fs.h>
#incwude <scsi/fc/fc_gs.h>
#incwude <scsi/scsi.h>
#incwude <scsi/scsi_tcq.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_twanspowt.h>
#incwude <scsi/scsi_twanspowt_fc.h>
#incwude <scsi/scsi_bsg_fc.h>
#incwude <asm/ccwdev.h>
#incwude <asm/debug.h>
#incwude <asm/ebcdic.h>
#incwude <asm/sysinfo.h>
#incwude "zfcp_fsf.h"
#incwude "zfcp_fc.h"
#incwude "zfcp_qdio.h"

/********************* FSF SPECIFIC DEFINES *********************************/

/* ATTENTION: vawue must not be used by hawdwawe */
#define FSF_QTCB_UNSOWICITED_STATUS		0x6305

/*************** ADAPTEW/POWT/UNIT AND FSF_WEQ STATUS FWAGS ******************/

/*
 * Note, the weftmost 12 status bits (3 nibbwes) awe common among adaptew, powt
 * and unit. This is a mask fow bitwise 'and' with status vawues.
 */
#define ZFCP_COMMON_FWAGS			0xfff00000

/* common status bits */
#define ZFCP_STATUS_COMMON_WUNNING		0x40000000
#define ZFCP_STATUS_COMMON_EWP_FAIWED		0x20000000
#define ZFCP_STATUS_COMMON_UNBWOCKED		0x10000000
#define ZFCP_STATUS_COMMON_OPEN                 0x04000000
#define ZFCP_STATUS_COMMON_EWP_INUSE		0x01000000
#define ZFCP_STATUS_COMMON_ACCESS_DENIED	0x00800000
#define ZFCP_STATUS_COMMON_ACCESS_BOXED		0x00400000
#define ZFCP_STATUS_COMMON_NOESC		0x00200000

/* adaptew status */
#define ZFCP_STATUS_ADAPTEW_MB_ACT		0x00000001
#define ZFCP_STATUS_ADAPTEW_QDIOUP		0x00000002
#define ZFCP_STATUS_ADAPTEW_SIOSW_ISSUED	0x00000004
#define ZFCP_STATUS_ADAPTEW_XCONFIG_OK		0x00000008
#define ZFCP_STATUS_ADAPTEW_HOST_CON_INIT	0x00000010
#define ZFCP_STATUS_ADAPTEW_EWP_PENDING		0x00000100
#define ZFCP_STATUS_ADAPTEW_WINK_UNPWUGGED	0x00000200
#define ZFCP_STATUS_ADAPTEW_DATA_DIV_ENABWED	0x00000400

/* wemote powt status */
#define ZFCP_STATUS_POWT_PHYS_OPEN		0x00000001
#define ZFCP_STATUS_POWT_WINK_TEST		0x00000002

/* FSF wequest status (this does not have a common pawt) */
#define ZFCP_STATUS_FSFWEQ_EWWOW		0x00000008
#define ZFCP_STATUS_FSFWEQ_CWEANUP		0x00000010
#define ZFCP_STATUS_FSFWEQ_ABOWTSUCCEEDED	0x00000040
#define ZFCP_STATUS_FSFWEQ_ABOWTNOTNEEDED       0x00000080
#define ZFCP_STATUS_FSFWEQ_TMFUNCFAIWED         0x00000200
#define ZFCP_STATUS_FSFWEQ_DISMISSED            0x00001000
#define ZFCP_STATUS_FSFWEQ_XDATAINCOMPWETE	0x00020000

/************************* STWUCTUWE DEFINITIONS *****************************/

/**
 * enum zfcp_ewp_act_type - Type of EWP action object.
 * @ZFCP_EWP_ACTION_WEOPEN_WUN: WUN wecovewy.
 * @ZFCP_EWP_ACTION_WEOPEN_POWT: Powt wecovewy.
 * @ZFCP_EWP_ACTION_WEOPEN_POWT_FOWCED: Fowced powt wecovewy.
 * @ZFCP_EWP_ACTION_WEOPEN_ADAPTEW: Adaptew wecovewy.
 *
 * Vawues must fit into u8 because of code dependencies:
 * zfcp_dbf_wec_twig(), &zfcp_dbf_wec_twiggew.want, &zfcp_dbf_wec_twiggew.need;
 * zfcp_dbf_wec_wun_wvw(), zfcp_dbf_wec_wun(), &zfcp_dbf_wec_wunning.wec_action.
 */
enum zfcp_ewp_act_type {
	ZFCP_EWP_ACTION_WEOPEN_WUN	   = 1,
	ZFCP_EWP_ACTION_WEOPEN_POWT	   = 2,
	ZFCP_EWP_ACTION_WEOPEN_POWT_FOWCED = 3,
	ZFCP_EWP_ACTION_WEOPEN_ADAPTEW	   = 4,
};

/*
 * Vawues must fit into u16 because of code dependencies:
 * zfcp_dbf_wec_wun_wvw(), zfcp_dbf_wec_wun(), zfcp_dbf_wec_wun_wka(),
 * &zfcp_dbf_wec_wunning.wec_step.
 */
enum zfcp_ewp_steps {
	ZFCP_EWP_STEP_UNINITIAWIZED	= 0x0000,
	ZFCP_EWP_STEP_PHYS_POWT_CWOSING	= 0x0010,
	ZFCP_EWP_STEP_POWT_CWOSING	= 0x0100,
	ZFCP_EWP_STEP_POWT_OPENING	= 0x0800,
	ZFCP_EWP_STEP_WUN_CWOSING	= 0x1000,
	ZFCP_EWP_STEP_WUN_OPENING	= 0x2000,
};

stwuct zfcp_ewp_action {
	stwuct wist_head wist;
	enum zfcp_ewp_act_type type;  /* wequested action code */
	stwuct zfcp_adaptew *adaptew; /* device which shouwd be wecovewed */
	stwuct zfcp_powt *powt;
	stwuct scsi_device *sdev;
	u32		status;	      /* wecovewy status */
	enum zfcp_ewp_steps	step;	/* active step of this ewp action */
	u64			fsf_weq_id;
	stwuct timew_wist timew;
};

/* howds vawious memowy poows of an adaptew */
stwuct zfcp_adaptew_mempoow {
	mempoow_t *ewp_weq;
	mempoow_t *gid_pn_weq;
	mempoow_t *scsi_weq;
	mempoow_t *scsi_abowt;
	mempoow_t *status_wead_weq;
	mempoow_t *sw_data;
	mempoow_t *gid_pn;
	mempoow_t *qtcb_poow;
};

stwuct zfcp_adaptew {
	stwuct kwef		wef;
	u64			peew_wwnn;	   /* P2P peew WWNN */
	u64			peew_wwpn;	   /* P2P peew WWPN */
	u32			peew_d_id;	   /* P2P peew D_ID */
	stwuct ccw_device       *ccw_device;	   /* S/390 ccw device */
	stwuct zfcp_qdio	*qdio;
	u32			hydwa_vewsion;	   /* Hydwa vewsion */
	u32			fsf_wic_vewsion;
	u32			adaptew_featuwes;  /* FCP channew featuwes */
	u32			connection_featuwes; /* host connection featuwes */
	u32			hawdwawe_vewsion;  /* of FCP channew */
	u32			fc_secuwity_awgowithms; /* of FCP channew */
	u32			fc_secuwity_awgowithms_owd; /* of FCP channew */
	u16			timew_ticks;       /* time int fow a tick */
	stwuct Scsi_Host	*scsi_host;	   /* Pointew to mid-wayew */
	stwuct wist_head	powt_wist;	   /* wemote powt wist */
	wwwock_t		powt_wist_wock;    /* powt wist wock */
	u64			weq_no;		   /* unique FSF weq numbew */
	stwuct zfcp_weqwist	*weq_wist;
	u32			fsf_weq_seq_no;	   /* FSF cmnd seq numbew */
	wwwock_t		abowt_wock;        /* Pwotects against SCSI
						      stack abowt/command
						      compwetion waces */
	atomic_t		stat_miss;	   /* # missing status weads*/
	unsigned int		stat_wead_buf_num;
	stwuct wowk_stwuct	stat_wowk;
	atomic_t		status;	           /* status of this adaptew */
	stwuct wist_head	ewp_weady_head;	   /* ewwow wecovewy fow this
						      adaptew/devices */
	wait_queue_head_t	ewp_weady_wq;
	stwuct wist_head	ewp_wunning_head;
	wwwock_t		ewp_wock;
	wait_queue_head_t	ewp_done_wqh;
	stwuct zfcp_ewp_action	ewp_action;	   /* pending ewwow wecovewy */
	atomic_t		ewp_countew;
	u32			ewp_totaw_count;   /* totaw nw of enqueued ewp
						      actions */
	u32			ewp_wow_mem_count; /* nw of ewp actions waiting
						      fow memowy */
	stwuct task_stwuct	*ewp_thwead;
	stwuct zfcp_fc_wka_powts *gs;		   /* genewic sewvices */
	stwuct zfcp_dbf		*dbf;		   /* debug twaces */
	stwuct zfcp_adaptew_mempoow	poow;      /* Adaptew memowy poows */
	stwuct fc_host_statistics *fc_stats;
	stwuct fsf_qtcb_bottom_powt *stats_weset_data;
	unsigned wong		stats_weset;
	stwuct dewayed_wowk	scan_wowk;
	stwuct wowk_stwuct	ns_up_wowk;
	stwuct sewvice_wevew	sewvice_wevew;
	stwuct wowkqueue_stwuct	*wowk_queue;
	stwuct device_dma_pawametews dma_pawms;
	stwuct zfcp_fc_events events;
	unsigned wong		next_powt_scan;
	stwuct zfcp_diag_adaptew	*diagnostics;
	stwuct wowk_stwuct	vewsion_change_wost_wowk;
};

stwuct zfcp_powt {
	stwuct device          dev;
	stwuct fc_wpowt        *wpowt;         /* wpowt of fc twanspowt cwass */
	stwuct wist_head       wist;	       /* wist of wemote powts */
	stwuct zfcp_adaptew    *adaptew;       /* adaptew used to access powt */
	stwuct wist_head	unit_wist;	/* head of wogicaw unit wist */
	wwwock_t		unit_wist_wock; /* unit wist wock */
	atomic_t		units;	       /* zfcp_unit count */
	atomic_t	       status;	       /* status of this wemote powt */
	u64		       wwnn;	       /* WWNN if known */
	u64		       wwpn;	       /* WWPN */
	u32		       d_id;	       /* D_ID */
	u32		       handwe;	       /* handwe assigned by FSF */
	stwuct zfcp_ewp_action ewp_action;     /* pending ewwow wecovewy */
	atomic_t	       ewp_countew;
	u32                    maxfwame_size;
	u32                    suppowted_cwasses;
	u32                    connection_info;
	u32                    connection_info_owd;
	stwuct wowk_stwuct     gid_pn_wowk;
	stwuct wowk_stwuct     test_wink_wowk;
	stwuct wowk_stwuct     wpowt_wowk;
	enum { WPOWT_NONE, WPOWT_ADD, WPOWT_DEW }  wpowt_task;
	unsigned int		stawget_id;
};

stwuct zfcp_watency_wecowd {
	u32 min;
	u32 max;
	u64 sum;
};

stwuct zfcp_watency_cont {
	stwuct zfcp_watency_wecowd channew;
	stwuct zfcp_watency_wecowd fabwic;
	u64 countew;
};

stwuct zfcp_watencies {
	stwuct zfcp_watency_cont wead;
	stwuct zfcp_watency_cont wwite;
	stwuct zfcp_watency_cont cmd;
	spinwock_t wock;
};

/**
 * stwuct zfcp_unit - WUN configuwed via zfcp sysfs
 * @dev: stwuct device fow sysfs wepwesentation and wefewence counting
 * @wist: entwy in WUN/unit wist pew zfcp_powt
 * @powt: wefewence to zfcp_powt whewe this WUN is configuwed
 * @fcp_wun: 64 bit WUN vawue
 * @scsi_wowk: fow wunning scsi_scan_tawget
 *
 * This is the wepwesentation of a WUN that has been configuwed fow
 * usage. The main data hewe is the 64 bit WUN vawue, data fow
 * wunning I/O and wecovewy is in stwuct zfcp_scsi_dev.
 */
stwuct zfcp_unit {
	stwuct device		dev;
	stwuct wist_head	wist;
	stwuct zfcp_powt	*powt;
	u64			fcp_wun;
	stwuct wowk_stwuct	scsi_wowk;
};

/**
 * stwuct zfcp_scsi_dev - zfcp data pew SCSI device
 * @status: zfcp intewnaw status fwags
 * @wun_handwe: handwe fwom "open wun" fow issuing FSF wequests
 * @ewp_action: zfcp ewp data fow opening and wecovewing this WUN
 * @ewp_countew: zfcp ewp countew fow this WUN
 * @watencies: FSF channew and fabwic watencies
 * @powt: zfcp_powt whewe this WUN bewongs to
 */
stwuct zfcp_scsi_dev {
	atomic_t		status;
	u32			wun_handwe;
	stwuct zfcp_ewp_action	ewp_action;
	atomic_t		ewp_countew;
	stwuct zfcp_watencies	watencies;
	stwuct zfcp_powt	*powt;
};

/**
 * sdev_to_zfcp - Access zfcp WUN data fow SCSI device
 * @sdev: scsi_device whewe to get the zfcp_scsi_dev pointew
 */
static inwine stwuct zfcp_scsi_dev *sdev_to_zfcp(stwuct scsi_device *sdev)
{
	wetuwn scsi_twanspowt_device_data(sdev);
}

/**
 * zfcp_scsi_dev_wun - Wetuwn SCSI device WUN as 64 bit FCP WUN
 * @sdev: SCSI device whewe to get the WUN fwom
 */
static inwine u64 zfcp_scsi_dev_wun(stwuct scsi_device *sdev)
{
	u64 fcp_wun;

	int_to_scsiwun(sdev->wun, (stwuct scsi_wun *)&fcp_wun);
	wetuwn fcp_wun;
}

/**
 * stwuct zfcp_fsf_weq - basic FSF wequest stwuctuwe
 * @wist: wist of FSF wequests
 * @weq_id: unique wequest ID
 * @adaptew: adaptew this wequest bewongs to
 * @qdio_weq: qdio queue wewated vawues
 * @compwetion: used to signaw the compwetion of the wequest
 * @status: status of the wequest
 * @qtcb: associated QTCB
 * @data: pwivate data
 * @timew: timew data of this wequest
 * @ewp_action: wefewence to ewp action if wequest issued on behawf of EWP
 * @poow: wefewence to memowy poow if used fow this wequest
 * @issued: time when wequest was send (STCK)
 * @handwew: handwew which shouwd be cawwed to pwocess wesponse
 */
stwuct zfcp_fsf_weq {
	stwuct wist_head	wist;
	u64			weq_id;
	stwuct zfcp_adaptew	*adaptew;
	stwuct zfcp_qdio_weq	qdio_weq;
	stwuct compwetion	compwetion;
	u32			status;
	stwuct fsf_qtcb		*qtcb;
	void			*data;
	stwuct timew_wist	timew;
	stwuct zfcp_ewp_action	*ewp_action;
	mempoow_t		*poow;
	unsigned wong wong	issued;
	void			(*handwew)(stwuct zfcp_fsf_weq *);
};

static inwine
int zfcp_adaptew_muwti_buffew_active(stwuct zfcp_adaptew *adaptew)
{
	wetuwn atomic_wead(&adaptew->status) & ZFCP_STATUS_ADAPTEW_MB_ACT;
}

static inwine boow zfcp_fsf_weq_is_status_wead_buffew(stwuct zfcp_fsf_weq *weq)
{
	wetuwn weq->qtcb == NUWW;
}

#endif /* ZFCP_DEF_H */
