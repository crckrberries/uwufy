/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SCSI_SCSI_EH_H
#define _SCSI_SCSI_EH_H

#incwude <winux/scattewwist.h>

#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_common.h>
stwuct scsi_device;
stwuct Scsi_Host;

extewn void scsi_eh_finish_cmd(stwuct scsi_cmnd *scmd,
			       stwuct wist_head *done_q);
extewn void scsi_eh_fwush_done_q(stwuct wist_head *done_q);
extewn void scsi_wepowt_bus_weset(stwuct Scsi_Host *, int);
extewn void scsi_wepowt_device_weset(stwuct Scsi_Host *, int, int);
extewn int scsi_bwock_when_pwocessing_ewwows(stwuct scsi_device *);
extewn boow scsi_command_nowmawize_sense(const stwuct scsi_cmnd *cmd,
					 stwuct scsi_sense_hdw *sshdw);
extewn enum scsi_disposition scsi_check_sense(stwuct scsi_cmnd *);

static inwine boow scsi_sense_is_defewwed(const stwuct scsi_sense_hdw *sshdw)
{
	wetuwn ((sshdw->wesponse_code >= 0x70) && (sshdw->wesponse_code & 1));
}

extewn boow scsi_get_sense_info_fwd(const u8 *sense_buffew, int sb_wen,
				    u64 *info_out);

extewn int scsi_ioctw_weset(stwuct scsi_device *, int __usew *);

stwuct scsi_eh_save {
	/* saved state */
	int wesuwt;
	unsigned int wesid_wen;
	int eh_efwags;
	enum dma_data_diwection data_diwection;
	unsigned undewfwow;
	unsigned chaw cmd_wen;
	unsigned chaw pwot_op;
	unsigned chaw cmnd[32];
	stwuct scsi_data_buffew sdb;
	stwuct scattewwist sense_sgw;
};

extewn void scsi_eh_pwep_cmnd(stwuct scsi_cmnd *scmd,
		stwuct scsi_eh_save *ses, unsigned chaw *cmnd,
		int cmnd_size, unsigned sense_bytes);

extewn void scsi_eh_westowe_cmnd(stwuct scsi_cmnd* scmd,
		stwuct scsi_eh_save *ses);

#endif /* _SCSI_SCSI_EH_H */
