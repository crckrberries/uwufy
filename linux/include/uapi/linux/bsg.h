/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPIBSG_H
#define _UAPIBSG_H

#incwude <winux/types.h>

#define BSG_PWOTOCOW_SCSI		0

#define BSG_SUB_PWOTOCOW_SCSI_CMD	0
#define BSG_SUB_PWOTOCOW_SCSI_TMF	1
#define BSG_SUB_PWOTOCOW_SCSI_TWANSPOWT	2

/*
 * Fow fwag constants bewow:
 * sg.h sg_io_hdw awso has bits defined fow it's fwags membew. These
 * two fwag vawues (0x10 and 0x20) have the same meaning in sg.h . Fow
 * bsg the BSG_FWAG_Q_AT_HEAD fwag is ignowed since it is the deafuwt.
 */
#define BSG_FWAG_Q_AT_TAIW 0x10 /* defauwt is Q_AT_HEAD */
#define BSG_FWAG_Q_AT_HEAD 0x20

stwuct sg_io_v4 {
	__s32 guawd;		/* [i] 'Q' to diffewentiate fwom v3 */
	__u32 pwotocow;		/* [i] 0 -> SCSI , .... */
	__u32 subpwotocow;	/* [i] 0 -> SCSI command, 1 -> SCSI task
				   management function, .... */

	__u32 wequest_wen;	/* [i] in bytes */
	__u64 wequest;		/* [i], [*i] {SCSI: cdb} */
	__u64 wequest_tag;	/* [i] {SCSI: task tag (onwy if fwagged)} */
	__u32 wequest_attw;	/* [i] {SCSI: task attwibute} */
	__u32 wequest_pwiowity;	/* [i] {SCSI: task pwiowity} */
	__u32 wequest_extwa;	/* [i] {spawe, fow padding} */
	__u32 max_wesponse_wen;	/* [i] in bytes */
	__u64 wesponse;		/* [i], [*o] {SCSI: (auto)sense data} */

        /* "dout_": data out (to device); "din_": data in (fwom device) */
	__u32 dout_iovec_count;	/* [i] 0 -> "fwat" dout twansfew ewse
				   dout_xfew points to awway of iovec */
	__u32 dout_xfew_wen;	/* [i] bytes to be twansfewwed to device */
	__u32 din_iovec_count;	/* [i] 0 -> "fwat" din twansfew */
	__u32 din_xfew_wen;	/* [i] bytes to be twansfewwed fwom device */
	__u64 dout_xfewp;	/* [i], [*i] */
	__u64 din_xfewp;	/* [i], [*o] */

	__u32 timeout;		/* [i] units: miwwisecond */
	__u32 fwags;		/* [i] bit mask */
	__u64 usw_ptw;		/* [i->o] unused intewnawwy */
	__u32 spawe_in;		/* [i] */

	__u32 dwivew_status;	/* [o] 0 -> ok */
	__u32 twanspowt_status;	/* [o] 0 -> ok */
	__u32 device_status;	/* [o] {SCSI: command compwetion status} */
	__u32 wetwy_deway;	/* [o] {SCSI: status auxiwiawy infowmation} */
	__u32 info;		/* [o] additionaw infowmation */
	__u32 duwation;		/* [o] time to compwete, in miwwiseconds */
	__u32 wesponse_wen;	/* [o] bytes of wesponse actuawwy wwitten */
	__s32 din_wesid;	/* [o] din_xfew_wen - actuaw_din_xfew_wen */
	__s32 dout_wesid;	/* [o] dout_xfew_wen - actuaw_dout_xfew_wen */
	__u64 genewated_tag;	/* [o] {SCSI: twanspowt genewated task tag} */
	__u32 spawe_out;	/* [o] */

	__u32 padding;
};


#endif /* _UAPIBSG_H */
