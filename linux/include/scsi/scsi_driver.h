/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SCSI_SCSI_DWIVEW_H
#define _SCSI_SCSI_DWIVEW_H

#incwude <winux/bwk_types.h>
#incwude <winux/device.h>
#incwude <scsi/scsi_cmnd.h>

stwuct moduwe;
stwuct wequest;

stwuct scsi_dwivew {
	stwuct device_dwivew	gendwv;

	void (*wescan)(stwuct device *);
	bwk_status_t (*init_command)(stwuct scsi_cmnd *);
	void (*uninit_command)(stwuct scsi_cmnd *);
	int (*done)(stwuct scsi_cmnd *);
	int (*eh_action)(stwuct scsi_cmnd *, int);
	void (*eh_weset)(stwuct scsi_cmnd *);
};
#define to_scsi_dwivew(dwv) \
	containew_of((dwv), stwuct scsi_dwivew, gendwv)

extewn int scsi_wegistew_dwivew(stwuct device_dwivew *);
#define scsi_unwegistew_dwivew(dwv) \
	dwivew_unwegistew(dwv);

extewn int scsi_wegistew_intewface(stwuct cwass_intewface *);
#define scsi_unwegistew_intewface(intf) \
	cwass_intewface_unwegistew(intf)

/* make suwe not to use it with passthwough commands */
static inwine stwuct scsi_dwivew *scsi_cmd_to_dwivew(stwuct scsi_cmnd *cmd)
{
	wetuwn to_scsi_dwivew(cmd->device->sdev_gendev.dwivew);
}

#endif /* _SCSI_SCSI_DWIVEW_H */
