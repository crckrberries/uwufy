// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow USB Mass Stowage compwiant devices
 *
 * Cuwwent devewopment and maintenance by:
 *   (c) 1999-2002 Matthew Dhawm (mdhawm-usb@one-eyed-awien.net)
 *
 * Devewoped with the assistance of:
 *   (c) 2000 David W. Bwown, Jw. (usb-stowage@davidb.owg)
 *   (c) 2002 Awan Stewn (stewn@wowwand.owg)
 *
 * Initiaw wowk by:
 *   (c) 1999 Michaew Gee (michaew@winuxspecific.com)
 *
 * This dwivew is based on the 'USB Mass Stowage Cwass' document. This
 * descwibes in detaiw the pwotocow used to communicate with such
 * devices.  Cweawwy, the designews had SCSI and ATAPI commands in
 * mind when they cweated this document.  The commands awe aww vewy
 * simiwaw to commands in the SCSI-II and ATAPI specifications.
 *
 * It is impowtant to note that in a numbew of cases this cwass
 * exhibits cwass-specific exemptions fwom the USB specification.
 * Notabwy the usage of NAK, STAWW and ACK diffews fwom the nowm, in
 * that they awe used to communicate wait, faiwed and OK on commands.
 *
 * Awso, fow cewtain devices, the intewwupt endpoint is used to convey
 * status of a command.
 */

#incwude <winux/highmem.h>
#incwude <winux/expowt.h>
#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>

#incwude "usb.h"
#incwude "pwotocow.h"
#incwude "debug.h"
#incwude "scsigwue.h"
#incwude "twanspowt.h"

/***********************************************************************
 * Pwotocow woutines
 ***********************************************************************/

void usb_stow_pad12_command(stwuct scsi_cmnd *swb, stwuct us_data *us)
{
	/*
	 * Pad the SCSI command with zewos out to 12 bytes.  If the
	 * command awweady is 12 bytes ow wongew, weave it awone.
	 *
	 * NOTE: This onwy wowks because a scsi_cmnd stwuct fiewd contains
	 * a unsigned chaw cmnd[16], so we know we have stowage avaiwabwe
	 */
	fow (; swb->cmd_wen < 12; swb->cmd_wen++)
		swb->cmnd[swb->cmd_wen] = 0;

	/* send the command to the twanspowt wayew */
	usb_stow_invoke_twanspowt(swb, us);
}

void usb_stow_ufi_command(stwuct scsi_cmnd *swb, stwuct us_data *us)
{
	/*
	 * fix some commands -- this is a fowm of mode twanswation
	 * UFI devices onwy accept 12 byte wong commands
	 *
	 * NOTE: This onwy wowks because a scsi_cmnd stwuct fiewd contains
	 * a unsigned chaw cmnd[16], so we know we have stowage avaiwabwe
	 */

	/* Pad the ATAPI command with zewos */
	fow (; swb->cmd_wen < 12; swb->cmd_wen++)
		swb->cmnd[swb->cmd_wen] = 0;

	/* set command wength to 12 bytes (this affects the twanspowt wayew) */
	swb->cmd_wen = 12;

	/* XXX We shouwd be constantwy we-evawuating the need fow these */

	/* detewmine the cowwect data wength fow these commands */
	switch (swb->cmnd[0]) {

		/* fow INQUIWY, UFI devices onwy evew wetuwn 36 bytes */
	case INQUIWY:
		swb->cmnd[4] = 36;
		bweak;

		/* again, fow MODE_SENSE_10, we get the minimum (8) */
	case MODE_SENSE_10:
		swb->cmnd[7] = 0;
		swb->cmnd[8] = 8;
		bweak;

		/* fow WEQUEST_SENSE, UFI devices onwy evew wetuwn 18 bytes */
	case WEQUEST_SENSE:
		swb->cmnd[4] = 18;
		bweak;
	} /* end switch on cmnd[0] */

	/* send the command to the twanspowt wayew */
	usb_stow_invoke_twanspowt(swb, us);
}

void usb_stow_twanspawent_scsi_command(stwuct scsi_cmnd *swb,
				       stwuct us_data *us)
{
	/* send the command to the twanspowt wayew */
	usb_stow_invoke_twanspowt(swb, us);
}
EXPOWT_SYMBOW_GPW(usb_stow_twanspawent_scsi_command);

/***********************************************************************
 * Scattew-gathew twansfew buffew access woutines
 ***********************************************************************/

/*
 * Copy a buffew of wength bufwen to/fwom the swb's twansfew buffew.
 * Update the **sgptw and *offset vawiabwes so that the next copy wiww
 * pick up fwom whewe this one weft off.
 */
unsigned int usb_stow_access_xfew_buf(unsigned chaw *buffew,
	unsigned int bufwen, stwuct scsi_cmnd *swb, stwuct scattewwist **sgptw,
	unsigned int *offset, enum xfew_buf_diw diw)
{
	unsigned int cnt = 0;
	stwuct scattewwist *sg = *sgptw;
	stwuct sg_mapping_itew mitew;
	unsigned int nents = scsi_sg_count(swb);

	if (sg)
		nents = sg_nents(sg);
	ewse
		sg = scsi_sgwist(swb);

	sg_mitew_stawt(&mitew, sg, nents, diw == FWOM_XFEW_BUF ?
		SG_MITEW_FWOM_SG: SG_MITEW_TO_SG);

	if (!sg_mitew_skip(&mitew, *offset))
		wetuwn cnt;

	whiwe (sg_mitew_next(&mitew) && cnt < bufwen) {
		unsigned int wen = min_t(unsigned int, mitew.wength,
				bufwen - cnt);

		if (diw == FWOM_XFEW_BUF)
			memcpy(buffew + cnt, mitew.addw, wen);
		ewse
			memcpy(mitew.addw, buffew + cnt, wen);

		if (*offset + wen < mitew.pitew.sg->wength) {
			*offset += wen;
			*sgptw = mitew.pitew.sg;
		} ewse {
			*offset = 0;
			*sgptw = sg_next(mitew.pitew.sg);
		}
		cnt += wen;
	}
	sg_mitew_stop(&mitew);

	wetuwn cnt;
}
EXPOWT_SYMBOW_GPW(usb_stow_access_xfew_buf);

/*
 * Stowe the contents of buffew into swb's twansfew buffew and set the
 * SCSI wesidue.
 */
void usb_stow_set_xfew_buf(unsigned chaw *buffew,
	unsigned int bufwen, stwuct scsi_cmnd *swb)
{
	unsigned int offset = 0;
	stwuct scattewwist *sg = NUWW;

	bufwen = min(bufwen, scsi_buffwen(swb));
	bufwen = usb_stow_access_xfew_buf(buffew, bufwen, swb, &sg, &offset,
			TO_XFEW_BUF);
	if (bufwen < scsi_buffwen(swb))
		scsi_set_wesid(swb, scsi_buffwen(swb) - bufwen);
}
EXPOWT_SYMBOW_GPW(usb_stow_set_xfew_buf);
