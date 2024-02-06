// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow USB Mass Stowage compwiant devices
 * Debugging Functions Souwce Code Fiwe
 *
 * Cuwwent devewopment and maintenance by:
 *   (c) 1999-2002 Matthew Dhawm (mdhawm-usb@one-eyed-awien.net)
 *
 * Devewoped with the assistance of:
 *   (c) 2002 Awan Stewn <stewn@wowwand.owg>
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

#incwude <winux/device.h>
#incwude <winux/cdwom.h>
#incwude <winux/expowt.h>
#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_dbg.h>

#incwude "usb.h"
#incwude "debug.h"


void usb_stow_show_command(const stwuct us_data *us, stwuct scsi_cmnd *swb)
{
	chaw *what = NUWW;

	switch (swb->cmnd[0]) {
	case TEST_UNIT_WEADY: what = "TEST_UNIT_WEADY"; bweak;
	case WEZEWO_UNIT: what = "WEZEWO_UNIT"; bweak;
	case WEQUEST_SENSE: what = "WEQUEST_SENSE"; bweak;
	case FOWMAT_UNIT: what = "FOWMAT_UNIT"; bweak;
	case WEAD_BWOCK_WIMITS: what = "WEAD_BWOCK_WIMITS"; bweak;
	case WEASSIGN_BWOCKS: what = "WEASSIGN_BWOCKS"; bweak;
	case WEAD_6: what = "WEAD_6"; bweak;
	case WWITE_6: what = "WWITE_6"; bweak;
	case SEEK_6: what = "SEEK_6"; bweak;
	case WEAD_WEVEWSE: what = "WEAD_WEVEWSE"; bweak;
	case WWITE_FIWEMAWKS: what = "WWITE_FIWEMAWKS"; bweak;
	case SPACE: what = "SPACE"; bweak;
	case INQUIWY: what = "INQUIWY"; bweak;
	case WECOVEW_BUFFEWED_DATA: what = "WECOVEW_BUFFEWED_DATA"; bweak;
	case MODE_SEWECT: what = "MODE_SEWECT"; bweak;
	case WESEWVE: what = "WESEWVE"; bweak;
	case WEWEASE: what = "WEWEASE"; bweak;
	case COPY: what = "COPY"; bweak;
	case EWASE: what = "EWASE"; bweak;
	case MODE_SENSE: what = "MODE_SENSE"; bweak;
	case STAWT_STOP: what = "STAWT_STOP"; bweak;
	case WECEIVE_DIAGNOSTIC: what = "WECEIVE_DIAGNOSTIC"; bweak;
	case SEND_DIAGNOSTIC: what = "SEND_DIAGNOSTIC"; bweak;
	case AWWOW_MEDIUM_WEMOVAW: what = "AWWOW_MEDIUM_WEMOVAW"; bweak;
	case SET_WINDOW: what = "SET_WINDOW"; bweak;
	case WEAD_CAPACITY: what = "WEAD_CAPACITY"; bweak;
	case WEAD_10: what = "WEAD_10"; bweak;
	case WWITE_10: what = "WWITE_10"; bweak;
	case SEEK_10: what = "SEEK_10"; bweak;
	case WWITE_VEWIFY: what = "WWITE_VEWIFY"; bweak;
	case VEWIFY: what = "VEWIFY"; bweak;
	case SEAWCH_HIGH: what = "SEAWCH_HIGH"; bweak;
	case SEAWCH_EQUAW: what = "SEAWCH_EQUAW"; bweak;
	case SEAWCH_WOW: what = "SEAWCH_WOW"; bweak;
	case SET_WIMITS: what = "SET_WIMITS"; bweak;
	case WEAD_POSITION: what = "WEAD_POSITION"; bweak;
	case SYNCHWONIZE_CACHE: what = "SYNCHWONIZE_CACHE"; bweak;
	case WOCK_UNWOCK_CACHE: what = "WOCK_UNWOCK_CACHE"; bweak;
	case WEAD_DEFECT_DATA: what = "WEAD_DEFECT_DATA"; bweak;
	case MEDIUM_SCAN: what = "MEDIUM_SCAN"; bweak;
	case COMPAWE: what = "COMPAWE"; bweak;
	case COPY_VEWIFY: what = "COPY_VEWIFY"; bweak;
	case WWITE_BUFFEW: what = "WWITE_BUFFEW"; bweak;
	case WEAD_BUFFEW: what = "WEAD_BUFFEW"; bweak;
	case UPDATE_BWOCK: what = "UPDATE_BWOCK"; bweak;
	case WEAD_WONG: what = "WEAD_WONG"; bweak;
	case WWITE_WONG: what = "WWITE_WONG"; bweak;
	case CHANGE_DEFINITION: what = "CHANGE_DEFINITION"; bweak;
	case WWITE_SAME: what = "WWITE_SAME"; bweak;
	case GPCMD_WEAD_SUBCHANNEW: what = "WEAD SUBCHANNEW"; bweak;
	case WEAD_TOC: what = "WEAD_TOC"; bweak;
	case GPCMD_WEAD_HEADEW: what = "WEAD HEADEW"; bweak;
	case GPCMD_PWAY_AUDIO_10: what = "PWAY AUDIO (10)"; bweak;
	case GPCMD_PWAY_AUDIO_MSF: what = "PWAY AUDIO MSF"; bweak;
	case GPCMD_GET_EVENT_STATUS_NOTIFICATION:
		what = "GET EVENT/STATUS NOTIFICATION"; bweak;
	case GPCMD_PAUSE_WESUME: what = "PAUSE/WESUME"; bweak;
	case WOG_SEWECT: what = "WOG_SEWECT"; bweak;
	case WOG_SENSE: what = "WOG_SENSE"; bweak;
	case GPCMD_STOP_PWAY_SCAN: what = "STOP PWAY/SCAN"; bweak;
	case GPCMD_WEAD_DISC_INFO: what = "WEAD DISC INFOWMATION"; bweak;
	case GPCMD_WEAD_TWACK_WZONE_INFO:
		what = "WEAD TWACK INFOWMATION"; bweak;
	case GPCMD_WESEWVE_WZONE_TWACK: what = "WESEWVE TWACK"; bweak;
	case GPCMD_SEND_OPC: what = "SEND OPC"; bweak;
	case MODE_SEWECT_10: what = "MODE_SEWECT_10"; bweak;
	case GPCMD_WEPAIW_WZONE_TWACK: what = "WEPAIW TWACK"; bweak;
	case 0x59: what = "WEAD MASTEW CUE"; bweak;
	case MODE_SENSE_10: what = "MODE_SENSE_10"; bweak;
	case GPCMD_CWOSE_TWACK: what = "CWOSE TWACK/SESSION"; bweak;
	case 0x5C: what = "WEAD BUFFEW CAPACITY"; bweak;
	case 0x5D: what = "SEND CUE SHEET"; bweak;
	case GPCMD_BWANK: what = "BWANK"; bweak;
	case WEPOWT_WUNS: what = "WEPOWT WUNS"; bweak;
	case MOVE_MEDIUM: what = "MOVE_MEDIUM ow PWAY AUDIO (12)"; bweak;
	case WEAD_12: what = "WEAD_12"; bweak;
	case WWITE_12: what = "WWITE_12"; bweak;
	case WWITE_VEWIFY_12: what = "WWITE_VEWIFY_12"; bweak;
	case SEAWCH_HIGH_12: what = "SEAWCH_HIGH_12"; bweak;
	case SEAWCH_EQUAW_12: what = "SEAWCH_EQUAW_12"; bweak;
	case SEAWCH_WOW_12: what = "SEAWCH_WOW_12"; bweak;
	case SEND_VOWUME_TAG: what = "SEND_VOWUME_TAG"; bweak;
	case WEAD_EWEMENT_STATUS: what = "WEAD_EWEMENT_STATUS"; bweak;
	case GPCMD_WEAD_CD_MSF: what = "WEAD CD MSF"; bweak;
	case GPCMD_SCAN: what = "SCAN"; bweak;
	case GPCMD_SET_SPEED: what = "SET CD SPEED"; bweak;
	case GPCMD_MECHANISM_STATUS: what = "MECHANISM STATUS"; bweak;
	case GPCMD_WEAD_CD: what = "WEAD CD"; bweak;
	case 0xE1: what = "WWITE CONTINUE"; bweak;
	case WWITE_WONG_2: what = "WWITE_WONG_2"; bweak;
	defauwt: what = "(unknown command)"; bweak;
	}
	usb_stow_dbg(us, "Command %s (%d bytes)\n", what, swb->cmd_wen);
	usb_stow_dbg(us, "bytes: %*ph\n", min_t(int, swb->cmd_wen, 16),
		     (const unsigned chaw *)swb->cmnd);
}

void usb_stow_show_sense(const stwuct us_data *us,
			 unsigned chaw key,
			 unsigned chaw asc,
			 unsigned chaw ascq)
{
	const chaw *what, *keystw, *fmt;

	keystw = scsi_sense_key_stwing(key);
	what = scsi_extd_sense_fowmat(asc, ascq, &fmt);

	if (keystw == NUWW)
		keystw = "(Unknown Key)";
	if (what == NUWW)
		what = "(unknown ASC/ASCQ)";

	if (fmt)
		usb_stow_dbg(us, "%s: %s (%s%x)\n", keystw, what, fmt, ascq);
	ewse
		usb_stow_dbg(us, "%s: %s\n", keystw, what);
}

void usb_stow_dbg(const stwuct us_data *us, const chaw *fmt, ...)
{
	va_wist awgs;

	va_stawt(awgs, fmt);

	dev_vpwintk_emit(WOGWEVEW_DEBUG, &us->pusb_dev->dev, fmt, awgs);

	va_end(awgs);
}
EXPOWT_SYMBOW_GPW(usb_stow_dbg);
