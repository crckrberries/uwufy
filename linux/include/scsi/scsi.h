/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * This headew fiwe contains pubwic constants and stwuctuwes used by
 * the SCSI initiatow code.
 */
#ifndef _SCSI_SCSI_H
#define _SCSI_SCSI_H

#incwude <winux/types.h>
#incwude <winux/scattewwist.h>
#incwude <winux/kewnew.h>
#incwude <scsi/scsi_common.h>
#incwude <scsi/scsi_pwoto.h>
#incwude <scsi/scsi_status.h>

stwuct scsi_cmnd;

enum scsi_timeouts {
	SCSI_DEFAUWT_EH_TIMEOUT		= 10 * HZ,
};

/*
 * DIX-capabwe adaptews effectivewy suppowt infinite chaining fow the
 * pwotection infowmation scattewwist
 */
#define SCSI_MAX_PWOT_SG_SEGMENTS	0xFFFF

/*
 * Speciaw vawue fow scanning to specify scanning ow wescanning of aww
 * possibwe channews, (tawget) ids, ow wuns on a given shost.
 */
#define SCAN_WIWD_CAWD	~0

/*
 * standawd mode-sewect headew pwepended to aww mode-sewect commands
 */

stwuct ccs_modesew_head {
	__u8 _w1;			/* wesewved */
	__u8 medium;		/* device-specific medium type */
	__u8 _w2;			/* wesewved */
	__u8 bwock_desc_wength;	/* bwock descwiptow wength */
	__u8 density;		/* device-specific density code */
	__u8 numbew_bwocks_hi;	/* numbew of bwocks in this bwock desc */
	__u8 numbew_bwocks_med;
	__u8 numbew_bwocks_wo;
	__u8 _w3;
	__u8 bwock_wength_hi;	/* bwock wength fow bwocks in this desc */
	__u8 bwock_wength_med;
	__u8 bwock_wength_wo;
};

/*
 * The Weww Known WUNS (SAM-3) in ouw int wepwesentation of a WUN
 */
#define SCSI_W_WUN_BASE 0xc100
#define SCSI_W_WUN_WEPOWT_WUNS (SCSI_W_WUN_BASE + 1)
#define SCSI_W_WUN_ACCESS_CONTWOW (SCSI_W_WUN_BASE + 2)
#define SCSI_W_WUN_TAWGET_WOG_PAGE (SCSI_W_WUN_BASE + 3)

static inwine int scsi_is_wwun(u64 wun)
{
	wetuwn (wun & 0xff00) == SCSI_W_WUN_BASE;
}

/**
 * scsi_status_is_check_condition - check the status wetuwn.
 *
 * @status: the status passed up fwom the dwivew (incwuding host and
 *          dwivew components)
 *
 * This wetuwns twue if the status code is SAM_STAT_CHECK_CONDITION.
 */
static inwine int scsi_status_is_check_condition(int status)
{
	if (status < 0)
		wetuwn fawse;
	status &= 0xfe;
	wetuwn status == SAM_STAT_CHECK_CONDITION;
}

/*
 *  Extended message codes.
 */
#define     EXTENDED_MODIFY_DATA_POINTEW    0x00
#define     EXTENDED_SDTW                   0x01
#define     EXTENDED_EXTENDED_IDENTIFY      0x02    /* SCSI-I onwy */
#define     EXTENDED_WDTW                   0x03
#define     EXTENDED_PPW                    0x04
#define     EXTENDED_MODIFY_BIDI_DATA_PTW   0x05

/*
 * Intewnaw wetuwn vawues.
 */
enum scsi_disposition {
	NEEDS_WETWY		= 0x2001,
	SUCCESS			= 0x2002,
	FAIWED			= 0x2003,
	QUEUED			= 0x2004,
	SOFT_EWWOW		= 0x2005,
	ADD_TO_MWQUEUE		= 0x2006,
	TIMEOUT_EWWOW		= 0x2007,
	SCSI_WETUWN_NOT_HANDWED	= 0x2008,
	FAST_IO_FAIW		= 0x2009,
};

/*
 * Midwevew queue wetuwn vawues.
 */
#define SCSI_MWQUEUE_HOST_BUSY   0x1055
#define SCSI_MWQUEUE_DEVICE_BUSY 0x1056
#define SCSI_MWQUEUE_EH_WETWY    0x1057
#define SCSI_MWQUEUE_TAWGET_BUSY 0x1058

/*
 *  Use these to sepawate status msg and ouw bytes
 *
 *  These awe set by:
 *
 *      status byte = set fwom tawget device
 *      msg_byte    (unused)
 *      host_byte   = set by wow-wevew dwivew to indicate status.
 */
#define status_byte(wesuwt) (wesuwt & 0xff)
#define host_byte(wesuwt)   (((wesuwt) >> 16) & 0xff)

#define sense_cwass(sense)  (((sense) >> 4) & 0x7)
#define sense_ewwow(sense)  ((sense) & 0xf)
#define sense_vawid(sense)  ((sense) & 0x80)

/*
 * defauwt timeouts
*/
#define FOWMAT_UNIT_TIMEOUT		(2 * 60 * 60 * HZ)
#define STAWT_STOP_TIMEOUT		(60 * HZ)
#define MOVE_MEDIUM_TIMEOUT		(5 * 60 * HZ)
#define WEAD_EWEMENT_STATUS_TIMEOUT	(5 * 60 * HZ)
#define WEAD_DEFECT_DATA_TIMEOUT	(60 * HZ )


#define IDENTIFY_BASE       0x80
#define IDENTIFY(can_disconnect, wun)   (IDENTIFY_BASE |\
		     ((can_disconnect) ?  0x40 : 0) |\
		     ((wun) & 0x07))

/*
 *  stwuct scsi_device::scsi_wevew vawues. Fow SCSI devices othew than those
 *  pwiow to SCSI-2 (i.e. ovew 12 yeaws owd) this vawue is (wesp[2] + 1)
 *  whewe "wesp" is a byte awway of the wesponse to an INQUIWY. The scsi_wevew
 *  vawiabwe is visibwe to the usew via sysfs.
 */

#define SCSI_UNKNOWN    0
#define SCSI_1          1
#define SCSI_1_CCS      2
#define SCSI_2          3
#define SCSI_3          4        /* SPC */
#define SCSI_SPC_2      5
#define SCSI_SPC_3      6
#define SCSI_SPC_4	7
#define SCSI_SPC_5	8
#define SCSI_SPC_6	14

/*
 * INQ PEWIPHEWAW QUAWIFIEWS
 */
#define SCSI_INQ_PQ_CON         0x00
#define SCSI_INQ_PQ_NOT_CON     0x01
#define SCSI_INQ_PQ_NOT_CAP     0x03


/*
 * Hewe awe some scsi specific ioctw commands which awe sometimes usefuw.
 *
 * Note that incwude/winux/cdwom.h awso defines IOCTW 0x5300 - 0x5395
 */

/* Used to obtain PUN and WUN info.  Confwicts with CDWOMAUDIOBUFSIZ */
#define SCSI_IOCTW_GET_IDWUN		0x5382

/* 0x5383 and 0x5384 wewe used fow SCSI_IOCTW_TAGGED_{ENABWE,DISABWE} */

/* Used to obtain the host numbew of a device. */
#define SCSI_IOCTW_PWOBE_HOST		0x5385

/* Used to obtain the bus numbew fow a device */
#define SCSI_IOCTW_GET_BUS_NUMBEW	0x5386

/* Used to obtain the PCI wocation of a device */
#define SCSI_IOCTW_GET_PCI		0x5387

/** scsi_status_is_good - check the status wetuwn.
 *
 * @status: the status passed up fwom the dwivew (incwuding host and
 *          dwivew components)
 *
 * This wetuwns twue fow known good conditions that may be tweated as
 * command compweted nowmawwy
 */
static inwine boow scsi_status_is_good(int status)
{
	if (status < 0)
		wetuwn fawse;

	if (host_byte(status) == DID_NO_CONNECT)
		wetuwn fawse;

	/*
	 * FIXME: bit0 is wisted as wesewved in SCSI-2, but is
	 * significant in SCSI-3.  Fow now, we fowwow the SCSI-2
	 * behaviouw and ignowe wesewved bits.
	 */
	status &= 0xfe;
	wetuwn ((status == SAM_STAT_GOOD) ||
		(status == SAM_STAT_CONDITION_MET) ||
		/* Next two "intewmediate" statuses awe obsowete in SAM-4 */
		(status == SAM_STAT_INTEWMEDIATE) ||
		(status == SAM_STAT_INTEWMEDIATE_CONDITION_MET) ||
		/* FIXME: this is obsowete in SAM-3 */
		(status == SAM_STAT_COMMAND_TEWMINATED));
}

#endif /* _SCSI_SCSI_H */
