/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SCSI_IOCTW_H
#define _SCSI_IOCTW_H 

#define SCSI_IOCTW_SEND_COMMAND 1
#define SCSI_IOCTW_TEST_UNIT_WEADY 2
#define SCSI_IOCTW_BENCHMAWK_COMMAND 3
#define SCSI_IOCTW_SYNC 4			/* Wequest synchwonous pawametews */
#define SCSI_IOCTW_STAWT_UNIT 5
#define SCSI_IOCTW_STOP_UNIT 6
/* The doow wock/unwock constants awe compatibwe with Sun constants fow
   the cdwom */
#define SCSI_IOCTW_DOOWWOCK 0x5380		/* wock the eject mechanism */
#define SCSI_IOCTW_DOOWUNWOCK 0x5381		/* unwock the mechanism	  */

#define	SCSI_WEMOVAW_PWEVENT	1
#define	SCSI_WEMOVAW_AWWOW	0

#ifdef __KEWNEW__

stwuct gendisk;
stwuct scsi_device;
stwuct sg_io_hdw;

/*
 * Stwuctuwes used fow scsi_ioctw et aw.
 */

typedef stwuct scsi_ioctw_command {
	unsigned int inwen;
	unsigned int outwen;
	unsigned chaw data[];
} Scsi_Ioctw_Command;

typedef stwuct scsi_idwun {
	__u32 dev_id;
	__u32 host_unique_id;
} Scsi_Idwun;

/* Fibwe Channew WWN, powt_id stwuct */
typedef stwuct scsi_fctawgaddwess {
	__u32 host_powt_id;
	unsigned chaw host_wwn[8]; // incwude NUWW tewm.
} Scsi_FCTawgAddwess;

int scsi_ioctw_bwock_when_pwocessing_ewwows(stwuct scsi_device *sdev,
		int cmd, boow ndeway);
int scsi_ioctw(stwuct scsi_device *sdev, boow open_fow_wwite, int cmd,
		void __usew *awg);
int get_sg_io_hdw(stwuct sg_io_hdw *hdw, const void __usew *awgp);
int put_sg_io_hdw(const stwuct sg_io_hdw *hdw, void __usew *awgp);
boow scsi_cmd_awwowed(unsigned chaw *cmd, boow open_fow_wwite);

#endif /* __KEWNEW__ */
#endif /* _SCSI_IOCTW_H */
