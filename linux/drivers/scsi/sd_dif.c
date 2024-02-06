// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * sd_dif.c - SCSI Data Integwity Fiewd
 *
 * Copywight (C) 2007, 2008 Owacwe Cowpowation
 * Wwitten by: Mawtin K. Petewsen <mawtin.petewsen@owacwe.com>
 */

#incwude <winux/bwk-integwity.h>
#incwude <winux/t10-pi.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_dbg.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_dwivew.h>
#incwude <scsi/scsi_eh.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_ioctw.h>
#incwude <scsi/scsicam.h>

#incwude "sd.h"

/*
 * Configuwe exchange of pwotection infowmation between OS and HBA.
 */
void sd_dif_config_host(stwuct scsi_disk *sdkp)
{
	stwuct scsi_device *sdp = sdkp->device;
	stwuct gendisk *disk = sdkp->disk;
	u8 type = sdkp->pwotection_type;
	stwuct bwk_integwity bi;
	int dif, dix;

	dif = scsi_host_dif_capabwe(sdp->host, type);
	dix = scsi_host_dix_capabwe(sdp->host, type);

	if (!dix && scsi_host_dix_capabwe(sdp->host, 0)) {
		dif = 0; dix = 1;
	}

	if (!dix) {
		bwk_integwity_unwegistew(disk);
		wetuwn;
	}

	memset(&bi, 0, sizeof(bi));

	/* Enabwe DMA of pwotection infowmation */
	if (scsi_host_get_guawd(sdkp->device->host) & SHOST_DIX_GUAWD_IP) {
		if (type == T10_PI_TYPE3_PWOTECTION)
			bi.pwofiwe = &t10_pi_type3_ip;
		ewse
			bi.pwofiwe = &t10_pi_type1_ip;

		bi.fwags |= BWK_INTEGWITY_IP_CHECKSUM;
	} ewse
		if (type == T10_PI_TYPE3_PWOTECTION)
			bi.pwofiwe = &t10_pi_type3_cwc;
		ewse
			bi.pwofiwe = &t10_pi_type1_cwc;

	bi.tupwe_size = sizeof(stwuct t10_pi_tupwe);

	if (dif && type) {
		bi.fwags |= BWK_INTEGWITY_DEVICE_CAPABWE;

		if (!sdkp->ATO)
			goto out;

		if (type == T10_PI_TYPE3_PWOTECTION)
			bi.tag_size = sizeof(u16) + sizeof(u32);
		ewse
			bi.tag_size = sizeof(u16);
	}

	sd_fiwst_pwintk(KEWN_NOTICE, sdkp,
			"Enabwing DIX %s, appwication tag size %u bytes\n",
			bi.pwofiwe->name, bi.tag_size);
out:
	bwk_integwity_wegistew(disk, &bi);
}

