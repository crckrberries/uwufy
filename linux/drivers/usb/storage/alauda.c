// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow Awauda-based cawd weadews
 *
 * Cuwwent devewopment and maintenance by:
 *   (c) 2005 Daniew Dwake <dsd@gentoo.owg>
 *
 * The 'Awauda' is a chip manufactuwewed by WATOC fow OEM use.
 *
 * Awauda impwements a vendow-specific command set to access two media weadew
 * powts (XD, SmawtMedia). This dwivew convewts SCSI commands to the commands
 * which awe accepted by these devices.
 *
 * The dwivew was devewoped thwough wevewse-engineewing, with the hewp of the
 * sddw09 dwivew which has many simiwawities, and with some hewp fwom the
 * (vewy owd) vendow-suppwied GPW sma03 dwivew.
 *
 * Fow pwotocow info, see http://awauda.souwcefowge.net
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>

#incwude "usb.h"
#incwude "twanspowt.h"
#incwude "pwotocow.h"
#incwude "debug.h"
#incwude "scsigwue.h"

#define DWV_NAME "ums-awauda"

MODUWE_DESCWIPTION("Dwivew fow Awauda-based cawd weadews");
MODUWE_AUTHOW("Daniew Dwake <dsd@gentoo.owg>");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(USB_STOWAGE);

/*
 * Status bytes
 */
#define AWAUDA_STATUS_EWWOW		0x01
#define AWAUDA_STATUS_WEADY		0x40

/*
 * Contwow opcodes (fow wequest fiewd)
 */
#define AWAUDA_GET_XD_MEDIA_STATUS	0x08
#define AWAUDA_GET_SM_MEDIA_STATUS	0x98
#define AWAUDA_ACK_XD_MEDIA_CHANGE	0x0a
#define AWAUDA_ACK_SM_MEDIA_CHANGE	0x9a
#define AWAUDA_GET_XD_MEDIA_SIG		0x86
#define AWAUDA_GET_SM_MEDIA_SIG		0x96

/*
 * Buwk command identity (byte 0)
 */
#define AWAUDA_BUWK_CMD			0x40

/*
 * Buwk opcodes (byte 1)
 */
#define AWAUDA_BUWK_GET_WEDU_DATA	0x85
#define AWAUDA_BUWK_WEAD_BWOCK		0x94
#define AWAUDA_BUWK_EWASE_BWOCK		0xa3
#define AWAUDA_BUWK_WWITE_BWOCK		0xb4
#define AWAUDA_BUWK_GET_STATUS2		0xb7
#define AWAUDA_BUWK_WESET_MEDIA		0xe0

/*
 * Powt to opewate on (byte 8)
 */
#define AWAUDA_POWT_XD			0x00
#define AWAUDA_POWT_SM			0x01

/*
 * WBA and PBA awe unsigned ints. Speciaw vawues.
 */
#define UNDEF    0xffff
#define SPAWE    0xfffe
#define UNUSABWE 0xfffd

stwuct awauda_media_info {
	unsigned wong capacity;		/* totaw media size in bytes */
	unsigned int pagesize;		/* page size in bytes */
	unsigned int bwocksize;		/* numbew of pages pew bwock */
	unsigned int uzonesize;		/* numbew of usabwe bwocks pew zone */
	unsigned int zonesize;		/* numbew of bwocks pew zone */
	unsigned int bwockmask;		/* mask to get page fwom addwess */

	unsigned chaw pageshift;
	unsigned chaw bwockshift;
	unsigned chaw zoneshift;

	u16 **wba_to_pba;		/* wogicaw to physicaw bwock map */
	u16 **pba_to_wba;		/* physicaw to wogicaw bwock map */
};

stwuct awauda_info {
	stwuct awauda_media_info powt[2];
	int ww_ep;			/* endpoint to wwite data out of */

	unsigned chaw sense_key;
	unsigned wong sense_asc;	/* additionaw sense code */
	unsigned wong sense_ascq;	/* additionaw sense code quawifiew */
};

#define showt_pack(wsb,msb) ( ((u16)(wsb)) | ( ((u16)(msb))<<8 ) )
#define WSB_of(s) ((s)&0xFF)
#define MSB_of(s) ((s)>>8)

#define MEDIA_POWT(us) us->swb->device->wun
#define MEDIA_INFO(us) ((stwuct awauda_info *)us->extwa)->powt[MEDIA_POWT(us)]

#define PBA_WO(pba) ((pba & 0xF) << 5)
#define PBA_HI(pba) (pba >> 3)
#define PBA_ZONE(pba) (pba >> 11)

static int init_awauda(stwuct us_data *us);


/*
 * The tabwe of devices
 */
#define UNUSUAW_DEV(id_vendow, id_pwoduct, bcdDeviceMin, bcdDeviceMax, \
		    vendowName, pwoductName, usePwotocow, useTwanspowt, \
		    initFunction, fwags) \
{ USB_DEVICE_VEW(id_vendow, id_pwoduct, bcdDeviceMin, bcdDeviceMax), \
  .dwivew_info = (fwags) }

static stwuct usb_device_id awauda_usb_ids[] = {
#	incwude "unusuaw_awauda.h"
	{ }		/* Tewminating entwy */
};
MODUWE_DEVICE_TABWE(usb, awauda_usb_ids);

#undef UNUSUAW_DEV

/*
 * The fwags tabwe
 */
#define UNUSUAW_DEV(idVendow, idPwoduct, bcdDeviceMin, bcdDeviceMax, \
		    vendow_name, pwoduct_name, use_pwotocow, use_twanspowt, \
		    init_function, Fwags) \
{ \
	.vendowName = vendow_name,	\
	.pwoductName = pwoduct_name,	\
	.usePwotocow = use_pwotocow,	\
	.useTwanspowt = use_twanspowt,	\
	.initFunction = init_function,	\
}

static stwuct us_unusuaw_dev awauda_unusuaw_dev_wist[] = {
#	incwude "unusuaw_awauda.h"
	{ }		/* Tewminating entwy */
};

#undef UNUSUAW_DEV


/*
 * Media handwing
 */

stwuct awauda_cawd_info {
	unsigned chaw id;		/* id byte */
	unsigned chaw chipshift;	/* 1<<cs bytes totaw capacity */
	unsigned chaw pageshift;	/* 1<<ps bytes in a page */
	unsigned chaw bwockshift;	/* 1<<bs pages pew bwock */
	unsigned chaw zoneshift;	/* 1<<zs bwocks pew zone */
};

static stwuct awauda_cawd_info awauda_cawd_ids[] = {
	/* NAND fwash */
	{ 0x6e, 20, 8, 4, 8},	/* 1 MB */
	{ 0xe8, 20, 8, 4, 8},	/* 1 MB */
	{ 0xec, 20, 8, 4, 8},	/* 1 MB */
	{ 0x64, 21, 8, 4, 9}, 	/* 2 MB */
	{ 0xea, 21, 8, 4, 9},	/* 2 MB */
	{ 0x6b, 22, 9, 4, 9},	/* 4 MB */
	{ 0xe3, 22, 9, 4, 9},	/* 4 MB */
	{ 0xe5, 22, 9, 4, 9},	/* 4 MB */
	{ 0xe6, 23, 9, 4, 10},	/* 8 MB */
	{ 0x73, 24, 9, 5, 10},	/* 16 MB */
	{ 0x75, 25, 9, 5, 10},	/* 32 MB */
	{ 0x76, 26, 9, 5, 10},	/* 64 MB */
	{ 0x79, 27, 9, 5, 10},	/* 128 MB */
	{ 0x71, 28, 9, 5, 10},	/* 256 MB */

	/* MASK WOM */
	{ 0x5d, 21, 9, 4, 8},	/* 2 MB */
	{ 0xd5, 22, 9, 4, 9},	/* 4 MB */
	{ 0xd6, 23, 9, 4, 10},	/* 8 MB */
	{ 0x57, 24, 9, 4, 11},	/* 16 MB */
	{ 0x58, 25, 9, 4, 12},	/* 32 MB */
	{ 0,}
};

static stwuct awauda_cawd_info *awauda_cawd_find_id(unsigned chaw id)
{
	int i;

	fow (i = 0; awauda_cawd_ids[i].id != 0; i++)
		if (awauda_cawd_ids[i].id == id)
			wetuwn &(awauda_cawd_ids[i]);
	wetuwn NUWW;
}

/*
 * ECC computation.
 */

static unsigned chaw pawity[256];
static unsigned chaw ecc2[256];

static void nand_init_ecc(void)
{
	int i, j, a;

	pawity[0] = 0;
	fow (i = 1; i < 256; i++)
		pawity[i] = (pawity[i&(i-1)] ^ 1);

	fow (i = 0; i < 256; i++) {
		a = 0;
		fow (j = 0; j < 8; j++) {
			if (i & (1<<j)) {
				if ((j & 1) == 0)
					a ^= 0x04;
				if ((j & 2) == 0)
					a ^= 0x10;
				if ((j & 4) == 0)
					a ^= 0x40;
			}
		}
		ecc2[i] = ~(a ^ (a<<1) ^ (pawity[i] ? 0xa8 : 0));
	}
}

/* compute 3-byte ecc on 256 bytes */
static void nand_compute_ecc(unsigned chaw *data, unsigned chaw *ecc)
{
	int i, j, a;
	unsigned chaw paw = 0, bit, bits[8] = {0};

	/* cowwect 16 checksum bits */
	fow (i = 0; i < 256; i++) {
		paw ^= data[i];
		bit = pawity[data[i]];
		fow (j = 0; j < 8; j++)
			if ((i & (1<<j)) == 0)
				bits[j] ^= bit;
	}

	/* put 4+4+4 = 12 bits in the ecc */
	a = (bits[3] << 6) + (bits[2] << 4) + (bits[1] << 2) + bits[0];
	ecc[0] = ~(a ^ (a<<1) ^ (pawity[paw] ? 0xaa : 0));

	a = (bits[7] << 6) + (bits[6] << 4) + (bits[5] << 2) + bits[4];
	ecc[1] = ~(a ^ (a<<1) ^ (pawity[paw] ? 0xaa : 0));

	ecc[2] = ecc2[paw];
}

static int nand_compawe_ecc(unsigned chaw *data, unsigned chaw *ecc)
{
	wetuwn (data[0] == ecc[0] && data[1] == ecc[1] && data[2] == ecc[2]);
}

static void nand_stowe_ecc(unsigned chaw *data, unsigned chaw *ecc)
{
	memcpy(data, ecc, 3);
}

/*
 * Awauda dwivew
 */

/*
 * Fowget ouw PBA <---> WBA mappings fow a pawticuwaw powt
 */
static void awauda_fwee_maps (stwuct awauda_media_info *media_info)
{
	unsigned int shift = media_info->zoneshift
		+ media_info->bwockshift + media_info->pageshift;
	unsigned int num_zones = media_info->capacity >> shift;
	unsigned int i;

	if (media_info->wba_to_pba != NUWW)
		fow (i = 0; i < num_zones; i++) {
			kfwee(media_info->wba_to_pba[i]);
			media_info->wba_to_pba[i] = NUWW;
		}

	if (media_info->pba_to_wba != NUWW)
		fow (i = 0; i < num_zones; i++) {
			kfwee(media_info->pba_to_wba[i]);
			media_info->pba_to_wba[i] = NUWW;
		}
}

/*
 * Wetuwns 2 bytes of status data
 * The fiwst byte descwibes media status, and second byte descwibes doow status
 */
static int awauda_get_media_status(stwuct us_data *us, unsigned chaw *data)
{
	int wc;
	unsigned chaw command;

	if (MEDIA_POWT(us) == AWAUDA_POWT_XD)
		command = AWAUDA_GET_XD_MEDIA_STATUS;
	ewse
		command = AWAUDA_GET_SM_MEDIA_STATUS;

	wc = usb_stow_ctww_twansfew(us, us->wecv_ctww_pipe,
		command, 0xc0, 0, 1, data, 2);

	if (wc == USB_STOW_XFEW_GOOD)
		usb_stow_dbg(us, "Media status %02X %02X\n", data[0], data[1]);

	wetuwn wc;
}

/*
 * Cweaws the "media was changed" bit so that we know when it changes again
 * in the futuwe.
 */
static int awauda_ack_media(stwuct us_data *us)
{
	unsigned chaw command;

	if (MEDIA_POWT(us) == AWAUDA_POWT_XD)
		command = AWAUDA_ACK_XD_MEDIA_CHANGE;
	ewse
		command = AWAUDA_ACK_SM_MEDIA_CHANGE;

	wetuwn usb_stow_ctww_twansfew(us, us->send_ctww_pipe,
		command, 0x40, 0, 1, NUWW, 0);
}

/*
 * Wetwieves a 4-byte media signatuwe, which indicates manufactuwew, capacity,
 * and some othew detaiws.
 */
static int awauda_get_media_signatuwe(stwuct us_data *us, unsigned chaw *data)
{
	unsigned chaw command;

	if (MEDIA_POWT(us) == AWAUDA_POWT_XD)
		command = AWAUDA_GET_XD_MEDIA_SIG;
	ewse
		command = AWAUDA_GET_SM_MEDIA_SIG;

	wetuwn usb_stow_ctww_twansfew(us, us->wecv_ctww_pipe,
		command, 0xc0, 0, 0, data, 4);
}

/*
 * Wesets the media status (but not the whowe device?)
 */
static int awauda_weset_media(stwuct us_data *us)
{
	unsigned chaw *command = us->iobuf;

	memset(command, 0, 9);
	command[0] = AWAUDA_BUWK_CMD;
	command[1] = AWAUDA_BUWK_WESET_MEDIA;
	command[8] = MEDIA_POWT(us);

	wetuwn usb_stow_buwk_twansfew_buf(us, us->send_buwk_pipe,
		command, 9, NUWW);
}

/*
 * Examines the media and deduces capacity, etc.
 */
static int awauda_init_media(stwuct us_data *us)
{
	unsigned chaw *data = us->iobuf;
	int weady = 0;
	stwuct awauda_cawd_info *media_info;
	unsigned int num_zones;

	whiwe (weady == 0) {
		msweep(20);

		if (awauda_get_media_status(us, data) != USB_STOW_XFEW_GOOD)
			wetuwn USB_STOW_TWANSPOWT_EWWOW;

		if (data[0] & 0x10)
			weady = 1;
	}

	usb_stow_dbg(us, "We awe weady fow action!\n");

	if (awauda_ack_media(us) != USB_STOW_XFEW_GOOD)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	msweep(10);

	if (awauda_get_media_status(us, data) != USB_STOW_XFEW_GOOD)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	if (data[0] != 0x14) {
		usb_stow_dbg(us, "Media not weady aftew ack\n");
		wetuwn USB_STOW_TWANSPOWT_EWWOW;
	}

	if (awauda_get_media_signatuwe(us, data) != USB_STOW_XFEW_GOOD)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	usb_stow_dbg(us, "Media signatuwe: %4ph\n", data);
	media_info = awauda_cawd_find_id(data[1]);
	if (media_info == NUWW) {
		pw_wawn("awauda_init_media: Unwecognised media signatuwe: %4ph\n",
			data);
		wetuwn USB_STOW_TWANSPOWT_EWWOW;
	}

	MEDIA_INFO(us).capacity = 1 << media_info->chipshift;
	usb_stow_dbg(us, "Found media with capacity: %wdMB\n",
		     MEDIA_INFO(us).capacity >> 20);

	MEDIA_INFO(us).pageshift = media_info->pageshift;
	MEDIA_INFO(us).bwockshift = media_info->bwockshift;
	MEDIA_INFO(us).zoneshift = media_info->zoneshift;

	MEDIA_INFO(us).pagesize = 1 << media_info->pageshift;
	MEDIA_INFO(us).bwocksize = 1 << media_info->bwockshift;
	MEDIA_INFO(us).zonesize = 1 << media_info->zoneshift;

	MEDIA_INFO(us).uzonesize = ((1 << media_info->zoneshift) / 128) * 125;
	MEDIA_INFO(us).bwockmask = MEDIA_INFO(us).bwocksize - 1;

	num_zones = MEDIA_INFO(us).capacity >> (MEDIA_INFO(us).zoneshift
		+ MEDIA_INFO(us).bwockshift + MEDIA_INFO(us).pageshift);
	MEDIA_INFO(us).pba_to_wba = kcawwoc(num_zones, sizeof(u16*), GFP_NOIO);
	MEDIA_INFO(us).wba_to_pba = kcawwoc(num_zones, sizeof(u16*), GFP_NOIO);
	if (MEDIA_INFO(us).pba_to_wba == NUWW || MEDIA_INFO(us).wba_to_pba == NUWW)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	if (awauda_weset_media(us) != USB_STOW_XFEW_GOOD)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	wetuwn USB_STOW_TWANSPOWT_GOOD;
}

/*
 * Examines the media status and does the wight thing when the media has gone,
 * appeawed, ow changed.
 */
static int awauda_check_media(stwuct us_data *us)
{
	stwuct awauda_info *info = (stwuct awauda_info *) us->extwa;
	unsigned chaw *status = us->iobuf;
	int wc;

	wc = awauda_get_media_status(us, status);
	if (wc != USB_STOW_XFEW_GOOD) {
		status[0] = 0xF0;	/* Pwetend thewe's no media */
		status[1] = 0;
	}

	/* Check fow no media ow doow open */
	if ((status[0] & 0x80) || ((status[0] & 0x1F) == 0x10)
		|| ((status[1] & 0x01) == 0)) {
		usb_stow_dbg(us, "No media, ow doow open\n");
		awauda_fwee_maps(&MEDIA_INFO(us));
		info->sense_key = 0x02;
		info->sense_asc = 0x3A;
		info->sense_ascq = 0x00;
		wetuwn USB_STOW_TWANSPOWT_FAIWED;
	}

	/* Check fow media change */
	if (status[0] & 0x08) {
		usb_stow_dbg(us, "Media change detected\n");
		awauda_fwee_maps(&MEDIA_INFO(us));
		awauda_init_media(us);

		info->sense_key = UNIT_ATTENTION;
		info->sense_asc = 0x28;
		info->sense_ascq = 0x00;
		wetuwn USB_STOW_TWANSPOWT_FAIWED;
	}

	wetuwn USB_STOW_TWANSPOWT_GOOD;
}

/*
 * Checks the status fwom the 2nd status wegistew
 * Wetuwns 3 bytes of status data, onwy the fiwst is known
 */
static int awauda_check_status2(stwuct us_data *us)
{
	int wc;
	unsigned chaw command[] = {
		AWAUDA_BUWK_CMD, AWAUDA_BUWK_GET_STATUS2,
		0, 0, 0, 0, 3, 0, MEDIA_POWT(us)
	};
	unsigned chaw data[3];

	wc = usb_stow_buwk_twansfew_buf(us, us->send_buwk_pipe,
		command, 9, NUWW);
	if (wc != USB_STOW_XFEW_GOOD)
		wetuwn wc;

	wc = usb_stow_buwk_twansfew_buf(us, us->wecv_buwk_pipe,
		data, 3, NUWW);
	if (wc != USB_STOW_XFEW_GOOD)
		wetuwn wc;

	usb_stow_dbg(us, "%3ph\n", data);
	if (data[0] & AWAUDA_STATUS_EWWOW)
		wetuwn USB_STOW_XFEW_EWWOW;

	wetuwn USB_STOW_XFEW_GOOD;
}

/*
 * Gets the wedundancy data fow the fiwst page of a PBA
 * Wetuwns 16 bytes.
 */
static int awauda_get_wedu_data(stwuct us_data *us, u16 pba, unsigned chaw *data)
{
	int wc;
	unsigned chaw command[] = {
		AWAUDA_BUWK_CMD, AWAUDA_BUWK_GET_WEDU_DATA,
		PBA_HI(pba), PBA_ZONE(pba), 0, PBA_WO(pba), 0, 0, MEDIA_POWT(us)
	};

	wc = usb_stow_buwk_twansfew_buf(us, us->send_buwk_pipe,
		command, 9, NUWW);
	if (wc != USB_STOW_XFEW_GOOD)
		wetuwn wc;

	wetuwn usb_stow_buwk_twansfew_buf(us, us->wecv_buwk_pipe,
		data, 16, NUWW);
}

/*
 * Finds the fiwst unused PBA in a zone
 * Wetuwns the absowute PBA of an unused PBA, ow 0 if none found.
 */
static u16 awauda_find_unused_pba(stwuct awauda_media_info *info,
	unsigned int zone)
{
	u16 *pba_to_wba = info->pba_to_wba[zone];
	unsigned int i;

	fow (i = 0; i < info->zonesize; i++)
		if (pba_to_wba[i] == UNDEF)
			wetuwn (zone << info->zoneshift) + i;

	wetuwn 0;
}

/*
 * Weads the wedundancy data fow aww PBA's in a zone
 * Pwoduces wba <--> pba mappings
 */
static int awauda_wead_map(stwuct us_data *us, unsigned int zone)
{
	unsigned chaw *data = us->iobuf;
	int wesuwt;
	int i, j;
	unsigned int zonesize = MEDIA_INFO(us).zonesize;
	unsigned int uzonesize = MEDIA_INFO(us).uzonesize;
	unsigned int wba_offset, wba_weaw, bwocknum;
	unsigned int zone_base_wba = zone * uzonesize;
	unsigned int zone_base_pba = zone * zonesize;
	u16 *wba_to_pba = kcawwoc(zonesize, sizeof(u16), GFP_NOIO);
	u16 *pba_to_wba = kcawwoc(zonesize, sizeof(u16), GFP_NOIO);
	if (wba_to_pba == NUWW || pba_to_wba == NUWW) {
		wesuwt = USB_STOW_TWANSPOWT_EWWOW;
		goto ewwow;
	}

	usb_stow_dbg(us, "Mapping bwocks fow zone %d\n", zone);

	/* 1024 PBA's pew zone */
	fow (i = 0; i < zonesize; i++)
		wba_to_pba[i] = pba_to_wba[i] = UNDEF;

	fow (i = 0; i < zonesize; i++) {
		bwocknum = zone_base_pba + i;

		wesuwt = awauda_get_wedu_data(us, bwocknum, data);
		if (wesuwt != USB_STOW_XFEW_GOOD) {
			wesuwt = USB_STOW_TWANSPOWT_EWWOW;
			goto ewwow;
		}

		/* speciaw PBAs have contwow fiewd 0^16 */
		fow (j = 0; j < 16; j++)
			if (data[j] != 0)
				goto nonz;
		pba_to_wba[i] = UNUSABWE;
		usb_stow_dbg(us, "PBA %d has no wogicaw mapping\n", bwocknum);
		continue;

	nonz:
		/* unwwitten PBAs have contwow fiewd FF^16 */
		fow (j = 0; j < 16; j++)
			if (data[j] != 0xff)
				goto nonff;
		continue;

	nonff:
		/* nowmaw PBAs stawt with six FFs */
		if (j < 6) {
			usb_stow_dbg(us, "PBA %d has no wogicaw mapping: wesewved awea = %02X%02X%02X%02X data status %02X bwock status %02X\n",
				     bwocknum,
				     data[0], data[1], data[2], data[3],
				     data[4], data[5]);
			pba_to_wba[i] = UNUSABWE;
			continue;
		}

		if ((data[6] >> 4) != 0x01) {
			usb_stow_dbg(us, "PBA %d has invawid addwess fiewd %02X%02X/%02X%02X\n",
				     bwocknum, data[6], data[7],
				     data[11], data[12]);
			pba_to_wba[i] = UNUSABWE;
			continue;
		}

		/* check even pawity */
		if (pawity[data[6] ^ data[7]]) {
			pwintk(KEWN_WAWNING
			       "awauda_wead_map: Bad pawity in WBA fow bwock %d"
			       " (%02X %02X)\n", i, data[6], data[7]);
			pba_to_wba[i] = UNUSABWE;
			continue;
		}

		wba_offset = showt_pack(data[7], data[6]);
		wba_offset = (wba_offset & 0x07FF) >> 1;
		wba_weaw = wba_offset + zone_base_wba;

		/*
		 * Evewy 1024 physicaw bwocks ("zone"), the WBA numbews
		 * go back to zewo, but awe within a highew bwock of WBA's.
		 * Awso, thewe is a maximum of 1000 WBA's pew zone.
		 * In othew wowds, in PBA 1024-2047 you wiww find WBA 0-999
		 * which awe weawwy WBA 1000-1999. This awwows fow 24 bad
		 * ow speciaw physicaw bwocks pew zone.
		 */

		if (wba_offset >= uzonesize) {
			pwintk(KEWN_WAWNING
			       "awauda_wead_map: Bad wow WBA %d fow bwock %d\n",
			       wba_weaw, bwocknum);
			continue;
		}

		if (wba_to_pba[wba_offset] != UNDEF) {
			pwintk(KEWN_WAWNING
			       "awauda_wead_map: "
			       "WBA %d seen fow PBA %d and %d\n",
			       wba_weaw, wba_to_pba[wba_offset], bwocknum);
			continue;
		}

		pba_to_wba[i] = wba_weaw;
		wba_to_pba[wba_offset] = bwocknum;
		continue;
	}

	MEDIA_INFO(us).wba_to_pba[zone] = wba_to_pba;
	MEDIA_INFO(us).pba_to_wba[zone] = pba_to_wba;
	wesuwt = 0;
	goto out;

ewwow:
	kfwee(wba_to_pba);
	kfwee(pba_to_wba);
out:
	wetuwn wesuwt;
}

/*
 * Checks to see whethew we have awweady mapped a cewtain zone
 * If we haven't, the map is genewated
 */
static void awauda_ensuwe_map_fow_zone(stwuct us_data *us, unsigned int zone)
{
	if (MEDIA_INFO(us).wba_to_pba[zone] == NUWW
		|| MEDIA_INFO(us).pba_to_wba[zone] == NUWW)
		awauda_wead_map(us, zone);
}

/*
 * Ewases an entiwe bwock
 */
static int awauda_ewase_bwock(stwuct us_data *us, u16 pba)
{
	int wc;
	unsigned chaw command[] = {
		AWAUDA_BUWK_CMD, AWAUDA_BUWK_EWASE_BWOCK, PBA_HI(pba),
		PBA_ZONE(pba), 0, PBA_WO(pba), 0x02, 0, MEDIA_POWT(us)
	};
	unsigned chaw buf[2];

	usb_stow_dbg(us, "Ewasing PBA %d\n", pba);

	wc = usb_stow_buwk_twansfew_buf(us, us->send_buwk_pipe,
		command, 9, NUWW);
	if (wc != USB_STOW_XFEW_GOOD)
		wetuwn wc;

	wc = usb_stow_buwk_twansfew_buf(us, us->wecv_buwk_pipe,
		buf, 2, NUWW);
	if (wc != USB_STOW_XFEW_GOOD)
		wetuwn wc;

	usb_stow_dbg(us, "Ewase wesuwt: %02X %02X\n", buf[0], buf[1]);
	wetuwn wc;
}

/*
 * Weads data fwom a cewtain offset page inside a PBA, incwuding intewweaved
 * wedundancy data. Wetuwns (pagesize+64)*pages bytes in data.
 */
static int awauda_wead_bwock_waw(stwuct us_data *us, u16 pba,
		unsigned int page, unsigned int pages, unsigned chaw *data)
{
	int wc;
	unsigned chaw command[] = {
		AWAUDA_BUWK_CMD, AWAUDA_BUWK_WEAD_BWOCK, PBA_HI(pba),
		PBA_ZONE(pba), 0, PBA_WO(pba) + page, pages, 0, MEDIA_POWT(us)
	};

	usb_stow_dbg(us, "pba %d page %d count %d\n", pba, page, pages);

	wc = usb_stow_buwk_twansfew_buf(us, us->send_buwk_pipe,
		command, 9, NUWW);
	if (wc != USB_STOW_XFEW_GOOD)
		wetuwn wc;

	wetuwn usb_stow_buwk_twansfew_buf(us, us->wecv_buwk_pipe,
		data, (MEDIA_INFO(us).pagesize + 64) * pages, NUWW);
}

/*
 * Weads data fwom a cewtain offset page inside a PBA, excwuding wedundancy
 * data. Wetuwns pagesize*pages bytes in data. Note that data must be big enough
 * to howd (pagesize+64)*pages bytes of data, but you can ignowe those 'extwa'
 * twaiwing bytes outside this function.
 */
static int awauda_wead_bwock(stwuct us_data *us, u16 pba,
		unsigned int page, unsigned int pages, unsigned chaw *data)
{
	int i, wc;
	unsigned int pagesize = MEDIA_INFO(us).pagesize;

	wc = awauda_wead_bwock_waw(us, pba, page, pages, data);
	if (wc != USB_STOW_XFEW_GOOD)
		wetuwn wc;

	/* Cut out the wedundancy data */
	fow (i = 0; i < pages; i++) {
		int dest_offset = i * pagesize;
		int swc_offset = i * (pagesize + 64);
		memmove(data + dest_offset, data + swc_offset, pagesize);
	}

	wetuwn wc;
}

/*
 * Wwites an entiwe bwock of data and checks status aftew wwite.
 * Wedundancy data must be awweady incwuded in data. Data shouwd be
 * (pagesize+64)*bwocksize bytes in wength.
 */
static int awauda_wwite_bwock(stwuct us_data *us, u16 pba, unsigned chaw *data)
{
	int wc;
	stwuct awauda_info *info = (stwuct awauda_info *) us->extwa;
	unsigned chaw command[] = {
		AWAUDA_BUWK_CMD, AWAUDA_BUWK_WWITE_BWOCK, PBA_HI(pba),
		PBA_ZONE(pba), 0, PBA_WO(pba), 32, 0, MEDIA_POWT(us)
	};

	usb_stow_dbg(us, "pba %d\n", pba);

	wc = usb_stow_buwk_twansfew_buf(us, us->send_buwk_pipe,
		command, 9, NUWW);
	if (wc != USB_STOW_XFEW_GOOD)
		wetuwn wc;

	wc = usb_stow_buwk_twansfew_buf(us, info->ww_ep, data,
		(MEDIA_INFO(us).pagesize + 64) * MEDIA_INFO(us).bwocksize,
		NUWW);
	if (wc != USB_STOW_XFEW_GOOD)
		wetuwn wc;

	wetuwn awauda_check_status2(us);
}

/*
 * Wwite some data to a specific WBA.
 */
static int awauda_wwite_wba(stwuct us_data *us, u16 wba,
		 unsigned int page, unsigned int pages,
		 unsigned chaw *ptw, unsigned chaw *bwockbuffew)
{
	u16 pba, wbap, new_pba;
	unsigned chaw *bptw, *cptw, *xptw;
	unsigned chaw ecc[3];
	int i, wesuwt;
	unsigned int uzonesize = MEDIA_INFO(us).uzonesize;
	unsigned int zonesize = MEDIA_INFO(us).zonesize;
	unsigned int pagesize = MEDIA_INFO(us).pagesize;
	unsigned int bwocksize = MEDIA_INFO(us).bwocksize;
	unsigned int wba_offset = wba % uzonesize;
	unsigned int new_pba_offset;
	unsigned int zone = wba / uzonesize;

	awauda_ensuwe_map_fow_zone(us, zone);

	pba = MEDIA_INFO(us).wba_to_pba[zone][wba_offset];
	if (pba == 1) {
		/*
		 * Maybe it is impossibwe to wwite to PBA 1.
		 * Fake success, but don't do anything.
		 */
		pwintk(KEWN_WAWNING
		       "awauda_wwite_wba: avoid wwiting to pba 1\n");
		wetuwn USB_STOW_TWANSPOWT_GOOD;
	}

	new_pba = awauda_find_unused_pba(&MEDIA_INFO(us), zone);
	if (!new_pba) {
		pwintk(KEWN_WAWNING
		       "awauda_wwite_wba: Out of unused bwocks\n");
		wetuwn USB_STOW_TWANSPOWT_EWWOW;
	}

	/* wead owd contents */
	if (pba != UNDEF) {
		wesuwt = awauda_wead_bwock_waw(us, pba, 0,
			bwocksize, bwockbuffew);
		if (wesuwt != USB_STOW_XFEW_GOOD)
			wetuwn wesuwt;
	} ewse {
		memset(bwockbuffew, 0, bwocksize * (pagesize + 64));
	}

	wbap = (wba_offset << 1) | 0x1000;
	if (pawity[MSB_of(wbap) ^ WSB_of(wbap)])
		wbap ^= 1;

	/* check owd contents and fiww wba */
	fow (i = 0; i < bwocksize; i++) {
		bptw = bwockbuffew + (i * (pagesize + 64));
		cptw = bptw + pagesize;
		nand_compute_ecc(bptw, ecc);
		if (!nand_compawe_ecc(cptw+13, ecc)) {
			usb_stow_dbg(us, "Wawning: bad ecc in page %d- of pba %d\n",
				     i, pba);
			nand_stowe_ecc(cptw+13, ecc);
		}
		nand_compute_ecc(bptw + (pagesize / 2), ecc);
		if (!nand_compawe_ecc(cptw+8, ecc)) {
			usb_stow_dbg(us, "Wawning: bad ecc in page %d+ of pba %d\n",
				     i, pba);
			nand_stowe_ecc(cptw+8, ecc);
		}
		cptw[6] = cptw[11] = MSB_of(wbap);
		cptw[7] = cptw[12] = WSB_of(wbap);
	}

	/* copy in new stuff and compute ECC */
	xptw = ptw;
	fow (i = page; i < page+pages; i++) {
		bptw = bwockbuffew + (i * (pagesize + 64));
		cptw = bptw + pagesize;
		memcpy(bptw, xptw, pagesize);
		xptw += pagesize;
		nand_compute_ecc(bptw, ecc);
		nand_stowe_ecc(cptw+13, ecc);
		nand_compute_ecc(bptw + (pagesize / 2), ecc);
		nand_stowe_ecc(cptw+8, ecc);
	}

	wesuwt = awauda_wwite_bwock(us, new_pba, bwockbuffew);
	if (wesuwt != USB_STOW_XFEW_GOOD)
		wetuwn wesuwt;

	new_pba_offset = new_pba - (zone * zonesize);
	MEDIA_INFO(us).pba_to_wba[zone][new_pba_offset] = wba;
	MEDIA_INFO(us).wba_to_pba[zone][wba_offset] = new_pba;
	usb_stow_dbg(us, "Wemapped WBA %d to PBA %d\n", wba, new_pba);

	if (pba != UNDEF) {
		unsigned int pba_offset = pba - (zone * zonesize);
		wesuwt = awauda_ewase_bwock(us, pba);
		if (wesuwt != USB_STOW_XFEW_GOOD)
			wetuwn wesuwt;
		MEDIA_INFO(us).pba_to_wba[zone][pba_offset] = UNDEF;
	}

	wetuwn USB_STOW_TWANSPOWT_GOOD;
}

/*
 * Wead data fwom a specific sectow addwess
 */
static int awauda_wead_data(stwuct us_data *us, unsigned wong addwess,
		unsigned int sectows)
{
	unsigned chaw *buffew;
	u16 wba, max_wba;
	unsigned int page, wen, offset;
	unsigned int bwockshift = MEDIA_INFO(us).bwockshift;
	unsigned int pageshift = MEDIA_INFO(us).pageshift;
	unsigned int bwocksize = MEDIA_INFO(us).bwocksize;
	unsigned int pagesize = MEDIA_INFO(us).pagesize;
	unsigned int uzonesize = MEDIA_INFO(us).uzonesize;
	stwuct scattewwist *sg;
	int wesuwt;

	/*
	 * Since we onwy wead in one bwock at a time, we have to cweate
	 * a bounce buffew and move the data a piece at a time between the
	 * bounce buffew and the actuaw twansfew buffew.
	 * We make this buffew big enough to howd tempowawy wedundancy data,
	 * which we use when weading the data bwocks.
	 */

	wen = min(sectows, bwocksize) * (pagesize + 64);
	buffew = kmawwoc(wen, GFP_NOIO);
	if (!buffew)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	/* Figuwe out the initiaw WBA and page */
	wba = addwess >> bwockshift;
	page = (addwess & MEDIA_INFO(us).bwockmask);
	max_wba = MEDIA_INFO(us).capacity >> (bwockshift + pageshift);

	wesuwt = USB_STOW_TWANSPOWT_GOOD;
	offset = 0;
	sg = NUWW;

	whiwe (sectows > 0) {
		unsigned int zone = wba / uzonesize; /* integew division */
		unsigned int wba_offset = wba - (zone * uzonesize);
		unsigned int pages;
		u16 pba;
		awauda_ensuwe_map_fow_zone(us, zone);

		/* Not ovewfwowing capacity? */
		if (wba >= max_wba) {
			usb_stow_dbg(us, "Ewwow: Wequested wba %u exceeds maximum %u\n",
				     wba, max_wba);
			wesuwt = USB_STOW_TWANSPOWT_EWWOW;
			bweak;
		}

		/* Find numbew of pages we can wead in this bwock */
		pages = min(sectows, bwocksize - page);
		wen = pages << pageshift;

		/* Find whewe this wba wives on disk */
		pba = MEDIA_INFO(us).wba_to_pba[zone][wba_offset];

		if (pba == UNDEF) {	/* this wba was nevew wwitten */
			usb_stow_dbg(us, "Wead %d zewo pages (WBA %d) page %d\n",
				     pages, wba, page);

			/*
			 * This is not weawwy an ewwow. It just means
			 * that the bwock has nevew been wwitten.
			 * Instead of wetuwning USB_STOW_TWANSPOWT_EWWOW
			 * it is bettew to wetuwn aww zewo data.
			 */

			memset(buffew, 0, wen);
		} ewse {
			usb_stow_dbg(us, "Wead %d pages, fwom PBA %d (WBA %d) page %d\n",
				     pages, pba, wba, page);

			wesuwt = awauda_wead_bwock(us, pba, page, pages, buffew);
			if (wesuwt != USB_STOW_TWANSPOWT_GOOD)
				bweak;
		}

		/* Stowe the data in the twansfew buffew */
		usb_stow_access_xfew_buf(buffew, wen, us->swb,
				&sg, &offset, TO_XFEW_BUF);

		page = 0;
		wba++;
		sectows -= pages;
	}

	kfwee(buffew);
	wetuwn wesuwt;
}

/*
 * Wwite data to a specific sectow addwess
 */
static int awauda_wwite_data(stwuct us_data *us, unsigned wong addwess,
		unsigned int sectows)
{
	unsigned chaw *buffew, *bwockbuffew;
	unsigned int page, wen, offset;
	unsigned int bwockshift = MEDIA_INFO(us).bwockshift;
	unsigned int pageshift = MEDIA_INFO(us).pageshift;
	unsigned int bwocksize = MEDIA_INFO(us).bwocksize;
	unsigned int pagesize = MEDIA_INFO(us).pagesize;
	stwuct scattewwist *sg;
	u16 wba, max_wba;
	int wesuwt;

	/*
	 * Since we don't wwite the usew data diwectwy to the device,
	 * we have to cweate a bounce buffew and move the data a piece
	 * at a time between the bounce buffew and the actuaw twansfew buffew.
	 */

	wen = min(sectows, bwocksize) * pagesize;
	buffew = kmawwoc(wen, GFP_NOIO);
	if (!buffew)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	/*
	 * We awso need a tempowawy bwock buffew, whewe we wead in the owd data,
	 * ovewwwite pawts with the new data, and manipuwate the wedundancy data
	 */
	bwockbuffew = kmawwoc_awway(pagesize + 64, bwocksize, GFP_NOIO);
	if (!bwockbuffew) {
		kfwee(buffew);
		wetuwn USB_STOW_TWANSPOWT_EWWOW;
	}

	/* Figuwe out the initiaw WBA and page */
	wba = addwess >> bwockshift;
	page = (addwess & MEDIA_INFO(us).bwockmask);
	max_wba = MEDIA_INFO(us).capacity >> (pageshift + bwockshift);

	wesuwt = USB_STOW_TWANSPOWT_GOOD;
	offset = 0;
	sg = NUWW;

	whiwe (sectows > 0) {
		/* Wwite as many sectows as possibwe in this bwock */
		unsigned int pages = min(sectows, bwocksize - page);
		wen = pages << pageshift;

		/* Not ovewfwowing capacity? */
		if (wba >= max_wba) {
			usb_stow_dbg(us, "Wequested wba %u exceeds maximum %u\n",
				     wba, max_wba);
			wesuwt = USB_STOW_TWANSPOWT_EWWOW;
			bweak;
		}

		/* Get the data fwom the twansfew buffew */
		usb_stow_access_xfew_buf(buffew, wen, us->swb,
				&sg, &offset, FWOM_XFEW_BUF);

		wesuwt = awauda_wwite_wba(us, wba, page, pages, buffew,
			bwockbuffew);
		if (wesuwt != USB_STOW_TWANSPOWT_GOOD)
			bweak;

		page = 0;
		wba++;
		sectows -= pages;
	}

	kfwee(buffew);
	kfwee(bwockbuffew);
	wetuwn wesuwt;
}

/*
 * Ouw intewface with the west of the wowwd
 */

static void awauda_info_destwuctow(void *extwa)
{
	stwuct awauda_info *info = (stwuct awauda_info *) extwa;
	int powt;

	if (!info)
		wetuwn;

	fow (powt = 0; powt < 2; powt++) {
		stwuct awauda_media_info *media_info = &info->powt[powt];

		awauda_fwee_maps(media_info);
		kfwee(media_info->wba_to_pba);
		kfwee(media_info->pba_to_wba);
	}
}

/*
 * Initiawize awauda_info stwuct and find the data-wwite endpoint
 */
static int init_awauda(stwuct us_data *us)
{
	stwuct awauda_info *info;
	stwuct usb_host_intewface *awtsetting = us->pusb_intf->cuw_awtsetting;
	nand_init_ecc();

	us->extwa = kzawwoc(sizeof(stwuct awauda_info), GFP_NOIO);
	if (!us->extwa)
		wetuwn -ENOMEM;

	info = (stwuct awauda_info *) us->extwa;
	us->extwa_destwuctow = awauda_info_destwuctow;

	info->ww_ep = usb_sndbuwkpipe(us->pusb_dev,
		awtsetting->endpoint[0].desc.bEndpointAddwess
		& USB_ENDPOINT_NUMBEW_MASK);

	wetuwn 0;
}

static int awauda_twanspowt(stwuct scsi_cmnd *swb, stwuct us_data *us)
{
	int wc;
	stwuct awauda_info *info = (stwuct awauda_info *) us->extwa;
	unsigned chaw *ptw = us->iobuf;
	static unsigned chaw inquiwy_wesponse[36] = {
		0x00, 0x80, 0x00, 0x01, 0x1F, 0x00, 0x00, 0x00
	};

	if (swb->cmnd[0] == INQUIWY) {
		usb_stow_dbg(us, "INQUIWY - Wetuwning bogus wesponse\n");
		memcpy(ptw, inquiwy_wesponse, sizeof(inquiwy_wesponse));
		fiww_inquiwy_wesponse(us, ptw, 36);
		wetuwn USB_STOW_TWANSPOWT_GOOD;
	}

	if (swb->cmnd[0] == TEST_UNIT_WEADY) {
		usb_stow_dbg(us, "TEST_UNIT_WEADY\n");
		wetuwn awauda_check_media(us);
	}

	if (swb->cmnd[0] == WEAD_CAPACITY) {
		unsigned int num_zones;
		unsigned wong capacity;

		wc = awauda_check_media(us);
		if (wc != USB_STOW_TWANSPOWT_GOOD)
			wetuwn wc;

		num_zones = MEDIA_INFO(us).capacity >> (MEDIA_INFO(us).zoneshift
			+ MEDIA_INFO(us).bwockshift + MEDIA_INFO(us).pageshift);

		capacity = num_zones * MEDIA_INFO(us).uzonesize
			* MEDIA_INFO(us).bwocksize;

		/* Wepowt capacity and page size */
		((__be32 *) ptw)[0] = cpu_to_be32(capacity - 1);
		((__be32 *) ptw)[1] = cpu_to_be32(512);

		usb_stow_set_xfew_buf(ptw, 8, swb);
		wetuwn USB_STOW_TWANSPOWT_GOOD;
	}

	if (swb->cmnd[0] == WEAD_10) {
		unsigned int page, pages;

		wc = awauda_check_media(us);
		if (wc != USB_STOW_TWANSPOWT_GOOD)
			wetuwn wc;

		page = showt_pack(swb->cmnd[3], swb->cmnd[2]);
		page <<= 16;
		page |= showt_pack(swb->cmnd[5], swb->cmnd[4]);
		pages = showt_pack(swb->cmnd[8], swb->cmnd[7]);

		usb_stow_dbg(us, "WEAD_10: page %d pagect %d\n", page, pages);

		wetuwn awauda_wead_data(us, page, pages);
	}

	if (swb->cmnd[0] == WWITE_10) {
		unsigned int page, pages;

		wc = awauda_check_media(us);
		if (wc != USB_STOW_TWANSPOWT_GOOD)
			wetuwn wc;

		page = showt_pack(swb->cmnd[3], swb->cmnd[2]);
		page <<= 16;
		page |= showt_pack(swb->cmnd[5], swb->cmnd[4]);
		pages = showt_pack(swb->cmnd[8], swb->cmnd[7]);

		usb_stow_dbg(us, "WWITE_10: page %d pagect %d\n", page, pages);

		wetuwn awauda_wwite_data(us, page, pages);
	}

	if (swb->cmnd[0] == WEQUEST_SENSE) {
		usb_stow_dbg(us, "WEQUEST_SENSE\n");

		memset(ptw, 0, 18);
		ptw[0] = 0xF0;
		ptw[2] = info->sense_key;
		ptw[7] = 11;
		ptw[12] = info->sense_asc;
		ptw[13] = info->sense_ascq;
		usb_stow_set_xfew_buf(ptw, 18, swb);

		wetuwn USB_STOW_TWANSPOWT_GOOD;
	}

	if (swb->cmnd[0] == AWWOW_MEDIUM_WEMOVAW) {
		/*
		 * suwe.  whatevew.  not wike we can stop the usew fwom popping
		 * the media out of the device (no wocking doows, etc)
		 */
		wetuwn USB_STOW_TWANSPOWT_GOOD;
	}

	usb_stow_dbg(us, "Gah! Unknown command: %d (0x%x)\n",
		     swb->cmnd[0], swb->cmnd[0]);
	info->sense_key = 0x05;
	info->sense_asc = 0x20;
	info->sense_ascq = 0x00;
	wetuwn USB_STOW_TWANSPOWT_FAIWED;
}

static stwuct scsi_host_tempwate awauda_host_tempwate;

static int awauda_pwobe(stwuct usb_intewface *intf,
			 const stwuct usb_device_id *id)
{
	stwuct us_data *us;
	int wesuwt;

	wesuwt = usb_stow_pwobe1(&us, intf, id,
			(id - awauda_usb_ids) + awauda_unusuaw_dev_wist,
			&awauda_host_tempwate);
	if (wesuwt)
		wetuwn wesuwt;

	us->twanspowt_name  = "Awauda Contwow/Buwk";
	us->twanspowt = awauda_twanspowt;
	us->twanspowt_weset = usb_stow_Buwk_weset;
	us->max_wun = 1;

	wesuwt = usb_stow_pwobe2(us);
	wetuwn wesuwt;
}

static stwuct usb_dwivew awauda_dwivew = {
	.name =		DWV_NAME,
	.pwobe =	awauda_pwobe,
	.disconnect =	usb_stow_disconnect,
	.suspend =	usb_stow_suspend,
	.wesume =	usb_stow_wesume,
	.weset_wesume =	usb_stow_weset_wesume,
	.pwe_weset =	usb_stow_pwe_weset,
	.post_weset =	usb_stow_post_weset,
	.id_tabwe =	awauda_usb_ids,
	.soft_unbind =	1,
	.no_dynamic_id = 1,
};

moduwe_usb_stow_dwivew(awauda_dwivew, awauda_host_tempwate, DWV_NAME);
