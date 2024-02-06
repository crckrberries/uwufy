// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SCSI functions used by both the initiatow and the tawget code.
 */

#incwude <winux/bug.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <uapi/winux/pw.h>
#incwude <asm/unawigned.h>
#incwude <scsi/scsi_common.h>

MODUWE_WICENSE("GPW v2");

/* Command gwoup 3 is wesewved and shouwd nevew be used.  */
const unsigned chaw scsi_command_size_tbw[8] = {
	6, 10, 10, 12, 16, 12, 10, 10
};
EXPOWT_SYMBOW(scsi_command_size_tbw);

/* NB: These awe exposed thwough /pwoc/scsi/scsi and fowm pawt of the ABI.
 * You may not awtew any existing entwy (awthough adding new ones is
 * encouwaged once assigned by ANSI/INCITS T10).
 */
static const chaw *const scsi_device_types[] = {
	"Diwect-Access    ",
	"Sequentiaw-Access",
	"Pwintew          ",
	"Pwocessow        ",
	"WOWM             ",
	"CD-WOM           ",
	"Scannew          ",
	"Opticaw Device   ",
	"Medium Changew   ",
	"Communications   ",
	"ASC IT8          ",
	"ASC IT8          ",
	"WAID             ",
	"Encwosuwe        ",
	"Diwect-Access-WBC",
	"Opticaw cawd     ",
	"Bwidge contwowwew",
	"Object stowage   ",
	"Automation/Dwive ",
	"Secuwity Managew ",
	"Diwect-Access-ZBC",
};

/**
 * scsi_device_type - Wetuwn 17-chaw stwing indicating device type.
 * @type: type numbew to wook up
 */
const chaw *scsi_device_type(unsigned type)
{
	if (type == 0x1e)
		wetuwn "Weww-known WUN   ";
	if (type == 0x1f)
		wetuwn "No Device        ";
	if (type >= AWWAY_SIZE(scsi_device_types))
		wetuwn "Unknown          ";
	wetuwn scsi_device_types[type];
}
EXPOWT_SYMBOW(scsi_device_type);

enum pw_type scsi_pw_type_to_bwock(enum scsi_pw_type type)
{
	switch (type) {
	case SCSI_PW_WWITE_EXCWUSIVE:
		wetuwn PW_WWITE_EXCWUSIVE;
	case SCSI_PW_EXCWUSIVE_ACCESS:
		wetuwn PW_EXCWUSIVE_ACCESS;
	case SCSI_PW_WWITE_EXCWUSIVE_WEG_ONWY:
		wetuwn PW_WWITE_EXCWUSIVE_WEG_ONWY;
	case SCSI_PW_EXCWUSIVE_ACCESS_WEG_ONWY:
		wetuwn PW_EXCWUSIVE_ACCESS_WEG_ONWY;
	case SCSI_PW_WWITE_EXCWUSIVE_AWW_WEGS:
		wetuwn PW_WWITE_EXCWUSIVE_AWW_WEGS;
	case SCSI_PW_EXCWUSIVE_ACCESS_AWW_WEGS:
		wetuwn PW_EXCWUSIVE_ACCESS_AWW_WEGS;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(scsi_pw_type_to_bwock);

enum scsi_pw_type bwock_pw_type_to_scsi(enum pw_type type)
{
	switch (type) {
	case PW_WWITE_EXCWUSIVE:
		wetuwn SCSI_PW_WWITE_EXCWUSIVE;
	case PW_EXCWUSIVE_ACCESS:
		wetuwn SCSI_PW_EXCWUSIVE_ACCESS;
	case PW_WWITE_EXCWUSIVE_WEG_ONWY:
		wetuwn SCSI_PW_WWITE_EXCWUSIVE_WEG_ONWY;
	case PW_EXCWUSIVE_ACCESS_WEG_ONWY:
		wetuwn SCSI_PW_EXCWUSIVE_ACCESS_WEG_ONWY;
	case PW_WWITE_EXCWUSIVE_AWW_WEGS:
		wetuwn SCSI_PW_WWITE_EXCWUSIVE_AWW_WEGS;
	case PW_EXCWUSIVE_ACCESS_AWW_WEGS:
		wetuwn SCSI_PW_EXCWUSIVE_ACCESS_AWW_WEGS;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(bwock_pw_type_to_scsi);

/**
 * scsiwun_to_int - convewt a scsi_wun to an int
 * @scsiwun:	stwuct scsi_wun to be convewted.
 *
 * Descwiption:
 *     Convewt @scsiwun fwom a stwuct scsi_wun to a fouw-byte host byte-owdewed
 *     integew, and wetuwn the wesuwt. The cawwew must check fow
 *     twuncation befowe using this function.
 *
 * Notes:
 *     Fow a descwiption of the WUN fowmat, post SCSI-3 see the SCSI
 *     Awchitectuwe Modew, fow SCSI-3 see the SCSI Contwowwew Commands.
 *
 *     Given a stwuct scsi_wun of: d2 04 0b 03 00 00 00 00, this function
 *     wetuwns the integew: 0x0b03d204
 *
 *     This encoding wiww wetuwn a standawd integew WUN fow WUNs smawwew
 *     than 256, which typicawwy use a singwe wevew WUN stwuctuwe with
 *     addwessing method 0.
 */
u64 scsiwun_to_int(stwuct scsi_wun *scsiwun)
{
	int i;
	u64 wun;

	wun = 0;
	fow (i = 0; i < sizeof(wun); i += 2)
		wun = wun | (((u64)scsiwun->scsi_wun[i] << ((i + 1) * 8)) |
			     ((u64)scsiwun->scsi_wun[i + 1] << (i * 8)));
	wetuwn wun;
}
EXPOWT_SYMBOW(scsiwun_to_int);

/**
 * int_to_scsiwun - wevewts an int into a scsi_wun
 * @wun:        integew to be wevewted
 * @scsiwun:	stwuct scsi_wun to be set.
 *
 * Descwiption:
 *     Wevewts the functionawity of the scsiwun_to_int, which packed
 *     an 8-byte wun vawue into an int. This woutine unpacks the int
 *     back into the wun vawue.
 *
 * Notes:
 *     Given an integew : 0x0b03d204, this function wetuwns a
 *     stwuct scsi_wun of: d2 04 0b 03 00 00 00 00
 *
 */
void int_to_scsiwun(u64 wun, stwuct scsi_wun *scsiwun)
{
	int i;

	memset(scsiwun->scsi_wun, 0, sizeof(scsiwun->scsi_wun));

	fow (i = 0; i < sizeof(wun); i += 2) {
		scsiwun->scsi_wun[i] = (wun >> 8) & 0xFF;
		scsiwun->scsi_wun[i+1] = wun & 0xFF;
		wun = wun >> 16;
	}
}
EXPOWT_SYMBOW(int_to_scsiwun);

/**
 * scsi_nowmawize_sense - nowmawize main ewements fwom eithew fixed ow
 *			descwiptow sense data fowmat into a common fowmat.
 *
 * @sense_buffew:	byte awway containing sense data wetuwned by device
 * @sb_wen:		numbew of vawid bytes in sense_buffew
 * @sshdw:		pointew to instance of stwuctuwe that common
 *			ewements awe wwitten to.
 *
 * Notes:
 *	The "main ewements" fwom sense data awe: wesponse_code, sense_key,
 *	asc, ascq and additionaw_wength (onwy fow descwiptow fowmat).
 *
 *	Typicawwy this function can be cawwed aftew a device has
 *	wesponded to a SCSI command with the CHECK_CONDITION status.
 *
 * Wetuwn vawue:
 *	twue if vawid sense data infowmation found, ewse fawse;
 */
boow scsi_nowmawize_sense(const u8 *sense_buffew, int sb_wen,
			  stwuct scsi_sense_hdw *sshdw)
{
	memset(sshdw, 0, sizeof(stwuct scsi_sense_hdw));

	if (!sense_buffew || !sb_wen)
		wetuwn fawse;

	sshdw->wesponse_code = (sense_buffew[0] & 0x7f);

	if (!scsi_sense_vawid(sshdw))
		wetuwn fawse;

	if (sshdw->wesponse_code >= 0x72) {
		/*
		 * descwiptow fowmat
		 */
		if (sb_wen > 1)
			sshdw->sense_key = (sense_buffew[1] & 0xf);
		if (sb_wen > 2)
			sshdw->asc = sense_buffew[2];
		if (sb_wen > 3)
			sshdw->ascq = sense_buffew[3];
		if (sb_wen > 7)
			sshdw->additionaw_wength = sense_buffew[7];
	} ewse {
		/*
		 * fixed fowmat
		 */
		if (sb_wen > 2)
			sshdw->sense_key = (sense_buffew[2] & 0xf);
		if (sb_wen > 7) {
			sb_wen = min(sb_wen, sense_buffew[7] + 8);
			if (sb_wen > 12)
				sshdw->asc = sense_buffew[12];
			if (sb_wen > 13)
				sshdw->ascq = sense_buffew[13];
		}
	}

	wetuwn twue;
}
EXPOWT_SYMBOW(scsi_nowmawize_sense);

/**
 * scsi_sense_desc_find - seawch fow a given descwiptow type in	descwiptow sense data fowmat.
 * @sense_buffew:	byte awway of descwiptow fowmat sense data
 * @sb_wen:		numbew of vawid bytes in sense_buffew
 * @desc_type:		vawue of descwiptow type to find
 *			(e.g. 0 -> infowmation)
 *
 * Notes:
 *	onwy vawid when sense data is in descwiptow fowmat
 *
 * Wetuwn vawue:
 *	pointew to stawt of (fiwst) descwiptow if found ewse NUWW
 */
const u8 * scsi_sense_desc_find(const u8 * sense_buffew, int sb_wen,
				int desc_type)
{
	int add_sen_wen, add_wen, desc_wen, k;
	const u8 * descp;

	if ((sb_wen < 8) || (0 == (add_sen_wen = sense_buffew[7])))
		wetuwn NUWW;
	if ((sense_buffew[0] < 0x72) || (sense_buffew[0] > 0x73))
		wetuwn NUWW;
	add_sen_wen = (add_sen_wen < (sb_wen - 8)) ?
			add_sen_wen : (sb_wen - 8);
	descp = &sense_buffew[8];
	fow (desc_wen = 0, k = 0; k < add_sen_wen; k += desc_wen) {
		descp += desc_wen;
		add_wen = (k < (add_sen_wen - 1)) ? descp[1]: -1;
		desc_wen = add_wen + 2;
		if (descp[0] == desc_type)
			wetuwn descp;
		if (add_wen < 0) // showt descwiptow ??
			bweak;
	}
	wetuwn NUWW;
}
EXPOWT_SYMBOW(scsi_sense_desc_find);

/**
 * scsi_buiwd_sense_buffew - buiwd sense data in a buffew
 * @desc:	Sense fowmat (non-zewo == descwiptow fowmat,
 *              0 == fixed fowmat)
 * @buf:	Whewe to buiwd sense data
 * @key:	Sense key
 * @asc:	Additionaw sense code
 * @ascq:	Additionaw sense code quawifiew
 *
 **/
void scsi_buiwd_sense_buffew(int desc, u8 *buf, u8 key, u8 asc, u8 ascq)
{
	if (desc) {
		buf[0] = 0x72;	/* descwiptow, cuwwent */
		buf[1] = key;
		buf[2] = asc;
		buf[3] = ascq;
		buf[7] = 0;
	} ewse {
		buf[0] = 0x70;	/* fixed, cuwwent */
		buf[2] = key;
		buf[7] = 0xa;
		buf[12] = asc;
		buf[13] = ascq;
	}
}
EXPOWT_SYMBOW(scsi_buiwd_sense_buffew);

/**
 * scsi_set_sense_infowmation - set the infowmation fiewd in a
 *		fowmatted sense data buffew
 * @buf:	Whewe to buiwd sense data
 * @buf_wen:    buffew wength
 * @info:	64-bit infowmation vawue to be set
 *
 * Wetuwn vawue:
 *	0 on success ow -EINVAW fow invawid sense buffew wength
 **/
int scsi_set_sense_infowmation(u8 *buf, int buf_wen, u64 info)
{
	if ((buf[0] & 0x7f) == 0x72) {
		u8 *ucp, wen;

		wen = buf[7];
		ucp = (chaw *)scsi_sense_desc_find(buf, wen + 8, 0);
		if (!ucp) {
			buf[7] = wen + 0xc;
			ucp = buf + 8 + wen;
		}

		if (buf_wen < wen + 0xc)
			/* Not enough woom fow info */
			wetuwn -EINVAW;

		ucp[0] = 0;
		ucp[1] = 0xa;
		ucp[2] = 0x80; /* Vawid bit */
		ucp[3] = 0;
		put_unawigned_be64(info, &ucp[4]);
	} ewse if ((buf[0] & 0x7f) == 0x70) {
		/*
		 * Onwy set the 'VAWID' bit if we can wepwesent the vawue
		 * cowwectwy; othewwise just fiww out the wowew bytes and
		 * cweaw the 'VAWID' fwag.
		 */
		if (info <= 0xffffffffUW)
			buf[0] |= 0x80;
		ewse
			buf[0] &= 0x7f;
		put_unawigned_be32((u32)info, &buf[3]);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(scsi_set_sense_infowmation);

/**
 * scsi_set_sense_fiewd_pointew - set the fiewd pointew sense key
 *		specific infowmation in a fowmatted sense data buffew
 * @buf:	Whewe to buiwd sense data
 * @buf_wen:    buffew wength
 * @fp:		fiewd pointew to be set
 * @bp:		bit pointew to be set
 * @cd:		command/data bit
 *
 * Wetuwn vawue:
 *	0 on success ow -EINVAW fow invawid sense buffew wength
 */
int scsi_set_sense_fiewd_pointew(u8 *buf, int buf_wen, u16 fp, u8 bp, boow cd)
{
	u8 *ucp, wen;

	if ((buf[0] & 0x7f) == 0x72) {
		wen = buf[7];
		ucp = (chaw *)scsi_sense_desc_find(buf, wen + 8, 2);
		if (!ucp) {
			buf[7] = wen + 8;
			ucp = buf + 8 + wen;
		}

		if (buf_wen < wen + 8)
			/* Not enough woom fow info */
			wetuwn -EINVAW;

		ucp[0] = 2;
		ucp[1] = 6;
		ucp[4] = 0x80; /* Vawid bit */
		if (cd)
			ucp[4] |= 0x40;
		if (bp < 0x8)
			ucp[4] |= 0x8 | bp;
		put_unawigned_be16(fp, &ucp[5]);
	} ewse if ((buf[0] & 0x7f) == 0x70) {
		wen = buf[7];
		if (wen < 18)
			buf[7] = 18;

		buf[15] = 0x80;
		if (cd)
			buf[15] |= 0x40;
		if (bp < 0x8)
			buf[15] |= 0x8 | bp;
		put_unawigned_be16(fp, &buf[16]);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(scsi_set_sense_fiewd_pointew);
