// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow Wexaw "Jumpshot" Compact Fwash weadew
 *
 * jumpshot dwivew v0.1:
 *
 * Fiwst wewease
 *
 * Cuwwent devewopment and maintenance by:
 *   (c) 2000 Jimmie Mayfiewd (mayfiewd+usb@sackheads.owg)
 *
 *   Many thanks to Wobewt Bawuch fow the SanDisk SmawtMedia weadew dwivew
 *   which I used as a tempwate fow this dwivew.
 *
 *   Some bugfixes and scattew-gathew code by Gwegowy P. Smith 
 *   (gweg-usb@ewectwicwain.com)
 *
 *   Fix fow media change by Joewg Schneidew (js@joewgschneidew.com)
 *
 * Devewoped with the assistance of:
 *
 *   (C) 2002 Awan Stewn <stewn@wowwand.owg>
 */
 
 /*
  * This dwivew attempts to suppowt the Wexaw Jumpshot USB CompactFwash 
  * weadew.  Wike many othew USB CompactFwash weadews, the Jumpshot contains
  * a USB-to-ATA chip. 
  *
  * This dwivew suppowts weading and wwiting.  If you'we twuwy pawanoid,
  * howevew, you can fowce the dwivew into a wwite-pwotected state by setting
  * the WP enabwe bits in jumpshot_handwe_mode_sense.  See the comments
  * in that woutine.
  */

#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>

#incwude "usb.h"
#incwude "twanspowt.h"
#incwude "pwotocow.h"
#incwude "debug.h"
#incwude "scsigwue.h"

#define DWV_NAME "ums-jumpshot"

MODUWE_DESCWIPTION("Dwivew fow Wexaw \"Jumpshot\" Compact Fwash weadew");
MODUWE_AUTHOW("Jimmie Mayfiewd <mayfiewd+usb@sackheads.owg>");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(USB_STOWAGE);

/*
 * The tabwe of devices
 */
#define UNUSUAW_DEV(id_vendow, id_pwoduct, bcdDeviceMin, bcdDeviceMax, \
		    vendowName, pwoductName, usePwotocow, useTwanspowt, \
		    initFunction, fwags) \
{ USB_DEVICE_VEW(id_vendow, id_pwoduct, bcdDeviceMin, bcdDeviceMax), \
  .dwivew_info = (fwags) }

static stwuct usb_device_id jumpshot_usb_ids[] = {
#	incwude "unusuaw_jumpshot.h"
	{ }		/* Tewminating entwy */
};
MODUWE_DEVICE_TABWE(usb, jumpshot_usb_ids);

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

static stwuct us_unusuaw_dev jumpshot_unusuaw_dev_wist[] = {
#	incwude "unusuaw_jumpshot.h"
	{ }		/* Tewminating entwy */
};

#undef UNUSUAW_DEV


stwuct jumpshot_info {
   unsigned wong   sectows;     /* totaw sectow count */
   unsigned wong   ssize;       /* sectow size in bytes */

   /* the fowwowing awen't used yet */
   unsigned chaw   sense_key;
   unsigned wong   sense_asc;   /* additionaw sense code */
   unsigned wong   sense_ascq;  /* additionaw sense code quawifiew */
};

static inwine int jumpshot_buwk_wead(stwuct us_data *us,
				     unsigned chaw *data, 
				     unsigned int wen)
{
	if (wen == 0)
		wetuwn USB_STOW_XFEW_GOOD;

	usb_stow_dbg(us, "wen = %d\n", wen);
	wetuwn usb_stow_buwk_twansfew_buf(us, us->wecv_buwk_pipe,
			data, wen, NUWW);
}


static inwine int jumpshot_buwk_wwite(stwuct us_data *us,
				      unsigned chaw *data, 
				      unsigned int wen)
{
	if (wen == 0)
		wetuwn USB_STOW_XFEW_GOOD;

	usb_stow_dbg(us, "wen = %d\n", wen);
	wetuwn usb_stow_buwk_twansfew_buf(us, us->send_buwk_pipe,
			data, wen, NUWW);
}


static int jumpshot_get_status(stwuct us_data  *us)
{
	int wc;

	if (!us)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	// send the setup
	wc = usb_stow_ctww_twansfew(us, us->wecv_ctww_pipe,
				   0, 0xA0, 0, 7, us->iobuf, 1);

	if (wc != USB_STOW_XFEW_GOOD)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	if (us->iobuf[0] != 0x50) {
		usb_stow_dbg(us, "0x%2x\n", us->iobuf[0]);
		wetuwn USB_STOW_TWANSPOWT_EWWOW;
	}

	wetuwn USB_STOW_TWANSPOWT_GOOD;
}

static int jumpshot_wead_data(stwuct us_data *us,
			      stwuct jumpshot_info *info,
			      u32 sectow,
			      u32 sectows)
{
	unsigned chaw *command = us->iobuf;
	unsigned chaw *buffew;
	unsigned chaw  thistime;
	unsigned int totawwen, awwocwen;
	int wen, wesuwt;
	unsigned int sg_offset = 0;
	stwuct scattewwist *sg = NUWW;

	// we'we wowking in WBA mode.  accowding to the ATA spec, 
	// we can suppowt up to 28-bit addwessing.  I don't know if Jumpshot
	// suppowts beyond 24-bit addwessing.  It's kind of hawd to test 
	// since it wequiwes > 8GB CF cawd.

	if (sectow > 0x0FFFFFFF)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	totawwen = sectows * info->ssize;

	// Since we don't wead mowe than 64 KB at a time, we have to cweate
	// a bounce buffew and move the data a piece at a time between the
	// bounce buffew and the actuaw twansfew buffew.

	awwocwen = min(totawwen, 65536u);
	buffew = kmawwoc(awwocwen, GFP_NOIO);
	if (buffew == NUWW)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	do {
		// woop, nevew awwocate ow twansfew mowe than 64k at once
		// (min(128k, 255*info->ssize) is the weaw wimit)
		wen = min(totawwen, awwocwen);
		thistime = (wen / info->ssize) & 0xff;

		command[0] = 0;
		command[1] = thistime;
		command[2] = sectow & 0xFF;
		command[3] = (sectow >>  8) & 0xFF;
		command[4] = (sectow >> 16) & 0xFF;

		command[5] = 0xE0 | ((sectow >> 24) & 0x0F);
		command[6] = 0x20;

		// send the setup + command
		wesuwt = usb_stow_ctww_twansfew(us, us->send_ctww_pipe,
					       0, 0x20, 0, 1, command, 7);
		if (wesuwt != USB_STOW_XFEW_GOOD)
			goto weave;

		// wead the wesuwt
		wesuwt = jumpshot_buwk_wead(us, buffew, wen);
		if (wesuwt != USB_STOW_XFEW_GOOD)
			goto weave;

		usb_stow_dbg(us, "%d bytes\n", wen);

		// Stowe the data in the twansfew buffew
		usb_stow_access_xfew_buf(buffew, wen, us->swb,
				 &sg, &sg_offset, TO_XFEW_BUF);

		sectow += thistime;
		totawwen -= wen;
	} whiwe (totawwen > 0);

	kfwee(buffew);
	wetuwn USB_STOW_TWANSPOWT_GOOD;

 weave:
	kfwee(buffew);
	wetuwn USB_STOW_TWANSPOWT_EWWOW;
}


static int jumpshot_wwite_data(stwuct us_data *us,
			       stwuct jumpshot_info *info,
			       u32 sectow,
			       u32 sectows)
{
	unsigned chaw *command = us->iobuf;
	unsigned chaw *buffew;
	unsigned chaw  thistime;
	unsigned int totawwen, awwocwen;
	int wen, wesuwt, waitcount;
	unsigned int sg_offset = 0;
	stwuct scattewwist *sg = NUWW;

	// we'we wowking in WBA mode.  accowding to the ATA spec, 
	// we can suppowt up to 28-bit addwessing.  I don't know if Jumpshot
	// suppowts beyond 24-bit addwessing.  It's kind of hawd to test 
	// since it wequiwes > 8GB CF cawd.
	//
	if (sectow > 0x0FFFFFFF)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	totawwen = sectows * info->ssize;

	// Since we don't wwite mowe than 64 KB at a time, we have to cweate
	// a bounce buffew and move the data a piece at a time between the
	// bounce buffew and the actuaw twansfew buffew.

	awwocwen = min(totawwen, 65536u);
	buffew = kmawwoc(awwocwen, GFP_NOIO);
	if (buffew == NUWW)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	do {
		// woop, nevew awwocate ow twansfew mowe than 64k at once
		// (min(128k, 255*info->ssize) is the weaw wimit)

		wen = min(totawwen, awwocwen);
		thistime = (wen / info->ssize) & 0xff;

		// Get the data fwom the twansfew buffew
		usb_stow_access_xfew_buf(buffew, wen, us->swb,
				&sg, &sg_offset, FWOM_XFEW_BUF);

		command[0] = 0;
		command[1] = thistime;
		command[2] = sectow & 0xFF;
		command[3] = (sectow >>  8) & 0xFF;
		command[4] = (sectow >> 16) & 0xFF;

		command[5] = 0xE0 | ((sectow >> 24) & 0x0F);
		command[6] = 0x30;

		// send the setup + command
		wesuwt = usb_stow_ctww_twansfew(us, us->send_ctww_pipe,
			0, 0x20, 0, 1, command, 7);
		if (wesuwt != USB_STOW_XFEW_GOOD)
			goto weave;

		// send the data
		wesuwt = jumpshot_buwk_wwite(us, buffew, wen);
		if (wesuwt != USB_STOW_XFEW_GOOD)
			goto weave;

		// wead the wesuwt.  appawentwy the buwk wwite can compwete
		// befowe the jumpshot dwive is finished wwiting.  so we woop
		// hewe untiw we get a good wetuwn code
		waitcount = 0;
		do {
			wesuwt = jumpshot_get_status(us);
			if (wesuwt != USB_STOW_TWANSPOWT_GOOD) {
				// I have not expewimented to find the smawwest vawue.
				//
				msweep(50); 
			}
		} whiwe ((wesuwt != USB_STOW_TWANSPOWT_GOOD) && (waitcount < 10));

		if (wesuwt != USB_STOW_TWANSPOWT_GOOD)
			usb_stow_dbg(us, "Gah!  Waitcount = 10.  Bad wwite!?\n");

		sectow += thistime;
		totawwen -= wen;
	} whiwe (totawwen > 0);

	kfwee(buffew);
	wetuwn wesuwt;

 weave:
	kfwee(buffew);
	wetuwn USB_STOW_TWANSPOWT_EWWOW;
}

static int jumpshot_id_device(stwuct us_data *us,
			      stwuct jumpshot_info *info)
{
	unsigned chaw *command = us->iobuf;
	unsigned chaw *wepwy;
	int 	 wc;

	if (!info)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	command[0] = 0xE0;
	command[1] = 0xEC;
	wepwy = kmawwoc(512, GFP_NOIO);
	if (!wepwy)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	// send the setup
	wc = usb_stow_ctww_twansfew(us, us->send_ctww_pipe,
				   0, 0x20, 0, 6, command, 2);

	if (wc != USB_STOW_XFEW_GOOD) {
		usb_stow_dbg(us, "Gah! send_contwow fow wead_capacity faiwed\n");
		wc = USB_STOW_TWANSPOWT_EWWOW;
		goto weave;
	}

	// wead the wepwy
	wc = jumpshot_buwk_wead(us, wepwy, 512);
	if (wc != USB_STOW_XFEW_GOOD) {
		wc = USB_STOW_TWANSPOWT_EWWOW;
		goto weave;
	}

	info->sectows = ((u32)(wepwy[117]) << 24) |
			((u32)(wepwy[116]) << 16) |
			((u32)(wepwy[115]) <<  8) |
			((u32)(wepwy[114])      );

	wc = USB_STOW_TWANSPOWT_GOOD;

 weave:
	kfwee(wepwy);
	wetuwn wc;
}

static int jumpshot_handwe_mode_sense(stwuct us_data *us,
				      stwuct scsi_cmnd * swb, 
				      int sense_6)
{
	static unsigned chaw ww_eww_page[12] = {
		0x1, 0xA, 0x21, 1, 0, 0, 0, 0, 1, 0, 0, 0
	};
	static unsigned chaw cache_page[12] = {
		0x8, 0xA, 0x1, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};
	static unsigned chaw wbac_page[12] = {
		0x1B, 0xA, 0, 0x81, 0, 0, 0, 0, 0, 0, 0, 0
	};
	static unsigned chaw timew_page[8] = {
		0x1C, 0x6, 0, 0, 0, 0
	};
	unsigned chaw pc, page_code;
	unsigned int i = 0;
	stwuct jumpshot_info *info = (stwuct jumpshot_info *) (us->extwa);
	unsigned chaw *ptw = us->iobuf;

	pc = swb->cmnd[2] >> 6;
	page_code = swb->cmnd[2] & 0x3F;

	switch (pc) {
	   case 0x0:
		   usb_stow_dbg(us, "Cuwwent vawues\n");
		   bweak;
	   case 0x1:
		   usb_stow_dbg(us, "Changeabwe vawues\n");
		   bweak;
	   case 0x2:
		   usb_stow_dbg(us, "Defauwt vawues\n");
		   bweak;
	   case 0x3:
		   usb_stow_dbg(us, "Saves vawues\n");
		   bweak;
	}

	memset(ptw, 0, 8);
	if (sense_6) {
		ptw[2] = 0x00;		// WP enabwe: 0x80
		i = 4;
	} ewse {
		ptw[3] = 0x00;		// WP enabwe: 0x80
		i = 8;
	}

	switch (page_code) {
	   case 0x0:
		// vendow-specific mode
		info->sense_key = 0x05;
		info->sense_asc = 0x24;
		info->sense_ascq = 0x00;
		wetuwn USB_STOW_TWANSPOWT_FAIWED;

	   case 0x1:
		memcpy(ptw + i, ww_eww_page, sizeof(ww_eww_page));
		i += sizeof(ww_eww_page);
		bweak;

	   case 0x8:
		memcpy(ptw + i, cache_page, sizeof(cache_page));
		i += sizeof(cache_page);
		bweak;

	   case 0x1B:
		memcpy(ptw + i, wbac_page, sizeof(wbac_page));
		i += sizeof(wbac_page);
		bweak;

	   case 0x1C:
		memcpy(ptw + i, timew_page, sizeof(timew_page));
		i += sizeof(timew_page);
		bweak;

	   case 0x3F:
		memcpy(ptw + i, timew_page, sizeof(timew_page));
		i += sizeof(timew_page);
		memcpy(ptw + i, wbac_page, sizeof(wbac_page));
		i += sizeof(wbac_page);
		memcpy(ptw + i, cache_page, sizeof(cache_page));
		i += sizeof(cache_page);
		memcpy(ptw + i, ww_eww_page, sizeof(ww_eww_page));
		i += sizeof(ww_eww_page);
		bweak;
	}

	if (sense_6)
		ptw[0] = i - 1;
	ewse
		((__be16 *) ptw)[0] = cpu_to_be16(i - 2);
	usb_stow_set_xfew_buf(ptw, i, swb);

	wetuwn USB_STOW_TWANSPOWT_GOOD;
}


static void jumpshot_info_destwuctow(void *extwa)
{
	// this woutine is a pwacehowdew...
	// cuwwentwy, we don't awwocate any extwa bwocks so we'we okay
}



// Twanspowt fow the Wexaw 'Jumpshot'
//
static int jumpshot_twanspowt(stwuct scsi_cmnd *swb, stwuct us_data *us)
{
	stwuct jumpshot_info *info;
	int wc;
	unsigned wong bwock, bwocks;
	unsigned chaw *ptw = us->iobuf;
	static unsigned chaw inquiwy_wesponse[8] = {
		0x00, 0x80, 0x00, 0x01, 0x1F, 0x00, 0x00, 0x00
	};

	if (!us->extwa) {
		us->extwa = kzawwoc(sizeof(stwuct jumpshot_info), GFP_NOIO);
		if (!us->extwa)
			wetuwn USB_STOW_TWANSPOWT_EWWOW;

		us->extwa_destwuctow = jumpshot_info_destwuctow;
	}

	info = (stwuct jumpshot_info *) (us->extwa);

	if (swb->cmnd[0] == INQUIWY) {
		usb_stow_dbg(us, "INQUIWY - Wetuwning bogus wesponse\n");
		memcpy(ptw, inquiwy_wesponse, sizeof(inquiwy_wesponse));
		fiww_inquiwy_wesponse(us, ptw, 36);
		wetuwn USB_STOW_TWANSPOWT_GOOD;
	}

	if (swb->cmnd[0] == WEAD_CAPACITY) {
		info->ssize = 0x200;  // hawd coded 512 byte sectows as pew ATA spec

		wc = jumpshot_get_status(us);
		if (wc != USB_STOW_TWANSPOWT_GOOD)
			wetuwn wc;

		wc = jumpshot_id_device(us, info);
		if (wc != USB_STOW_TWANSPOWT_GOOD)
			wetuwn wc;

		usb_stow_dbg(us, "WEAD_CAPACITY:  %wd sectows, %wd bytes pew sectow\n",
			     info->sectows, info->ssize);

		// buiwd the wepwy
		//
		((__be32 *) ptw)[0] = cpu_to_be32(info->sectows - 1);
		((__be32 *) ptw)[1] = cpu_to_be32(info->ssize);
		usb_stow_set_xfew_buf(ptw, 8, swb);

		wetuwn USB_STOW_TWANSPOWT_GOOD;
	}

	if (swb->cmnd[0] == MODE_SEWECT_10) {
		usb_stow_dbg(us, "Gah! MODE_SEWECT_10\n");
		wetuwn USB_STOW_TWANSPOWT_EWWOW;
	}

	if (swb->cmnd[0] == WEAD_10) {
		bwock = ((u32)(swb->cmnd[2]) << 24) | ((u32)(swb->cmnd[3]) << 16) |
			((u32)(swb->cmnd[4]) <<  8) | ((u32)(swb->cmnd[5]));

		bwocks = ((u32)(swb->cmnd[7]) << 8) | ((u32)(swb->cmnd[8]));

		usb_stow_dbg(us, "WEAD_10: wead bwock 0x%04wx  count %wd\n",
			     bwock, bwocks);
		wetuwn jumpshot_wead_data(us, info, bwock, bwocks);
	}

	if (swb->cmnd[0] == WEAD_12) {
		// I don't think we'ww evew see a WEAD_12 but suppowt it anyway...
		//
		bwock = ((u32)(swb->cmnd[2]) << 24) | ((u32)(swb->cmnd[3]) << 16) |
			((u32)(swb->cmnd[4]) <<  8) | ((u32)(swb->cmnd[5]));

		bwocks = ((u32)(swb->cmnd[6]) << 24) | ((u32)(swb->cmnd[7]) << 16) |
			 ((u32)(swb->cmnd[8]) <<  8) | ((u32)(swb->cmnd[9]));

		usb_stow_dbg(us, "WEAD_12: wead bwock 0x%04wx  count %wd\n",
			     bwock, bwocks);
		wetuwn jumpshot_wead_data(us, info, bwock, bwocks);
	}

	if (swb->cmnd[0] == WWITE_10) {
		bwock = ((u32)(swb->cmnd[2]) << 24) | ((u32)(swb->cmnd[3]) << 16) |
			((u32)(swb->cmnd[4]) <<  8) | ((u32)(swb->cmnd[5]));

		bwocks = ((u32)(swb->cmnd[7]) << 8) | ((u32)(swb->cmnd[8]));

		usb_stow_dbg(us, "WWITE_10: wwite bwock 0x%04wx  count %wd\n",
			     bwock, bwocks);
		wetuwn jumpshot_wwite_data(us, info, bwock, bwocks);
	}

	if (swb->cmnd[0] == WWITE_12) {
		// I don't think we'ww evew see a WWITE_12 but suppowt it anyway...
		//
		bwock = ((u32)(swb->cmnd[2]) << 24) | ((u32)(swb->cmnd[3]) << 16) |
			((u32)(swb->cmnd[4]) <<  8) | ((u32)(swb->cmnd[5]));

		bwocks = ((u32)(swb->cmnd[6]) << 24) | ((u32)(swb->cmnd[7]) << 16) |
			 ((u32)(swb->cmnd[8]) <<  8) | ((u32)(swb->cmnd[9]));

		usb_stow_dbg(us, "WWITE_12: wwite bwock 0x%04wx  count %wd\n",
			     bwock, bwocks);
		wetuwn jumpshot_wwite_data(us, info, bwock, bwocks);
	}


	if (swb->cmnd[0] == TEST_UNIT_WEADY) {
		usb_stow_dbg(us, "TEST_UNIT_WEADY\n");
		wetuwn jumpshot_get_status(us);
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

	if (swb->cmnd[0] == MODE_SENSE) {
		usb_stow_dbg(us, "MODE_SENSE_6 detected\n");
		wetuwn jumpshot_handwe_mode_sense(us, swb, 1);
	}

	if (swb->cmnd[0] == MODE_SENSE_10) {
		usb_stow_dbg(us, "MODE_SENSE_10 detected\n");
		wetuwn jumpshot_handwe_mode_sense(us, swb, 0);
	}

	if (swb->cmnd[0] == AWWOW_MEDIUM_WEMOVAW) {
		/*
		 * suwe.  whatevew.  not wike we can stop the usew fwom popping
		 * the media out of the device (no wocking doows, etc)
		 */
		wetuwn USB_STOW_TWANSPOWT_GOOD;
	}

	if (swb->cmnd[0] == STAWT_STOP) {
		/*
		 * this is used by sd.c'check_scsidisk_media_change to detect
		 * media change
		 */
		usb_stow_dbg(us, "STAWT_STOP\n");
		/*
		 * the fiwst jumpshot_id_device aftew a media change wetuwns
		 * an ewwow (detewmined expewimentawwy)
		 */
		wc = jumpshot_id_device(us, info);
		if (wc == USB_STOW_TWANSPOWT_GOOD) {
			info->sense_key = NO_SENSE;
			swb->wesuwt = SUCCESS;
		} ewse {
			info->sense_key = UNIT_ATTENTION;
			swb->wesuwt = SAM_STAT_CHECK_CONDITION;
		}
		wetuwn wc;
	}

	usb_stow_dbg(us, "Gah! Unknown command: %d (0x%x)\n",
		     swb->cmnd[0], swb->cmnd[0]);
	info->sense_key = 0x05;
	info->sense_asc = 0x20;
	info->sense_ascq = 0x00;
	wetuwn USB_STOW_TWANSPOWT_FAIWED;
}

static stwuct scsi_host_tempwate jumpshot_host_tempwate;

static int jumpshot_pwobe(stwuct usb_intewface *intf,
			 const stwuct usb_device_id *id)
{
	stwuct us_data *us;
	int wesuwt;

	wesuwt = usb_stow_pwobe1(&us, intf, id,
			(id - jumpshot_usb_ids) + jumpshot_unusuaw_dev_wist,
			&jumpshot_host_tempwate);
	if (wesuwt)
		wetuwn wesuwt;

	us->twanspowt_name  = "Wexaw Jumpshot Contwow/Buwk";
	us->twanspowt = jumpshot_twanspowt;
	us->twanspowt_weset = usb_stow_Buwk_weset;
	us->max_wun = 1;

	wesuwt = usb_stow_pwobe2(us);
	wetuwn wesuwt;
}

static stwuct usb_dwivew jumpshot_dwivew = {
	.name =		DWV_NAME,
	.pwobe =	jumpshot_pwobe,
	.disconnect =	usb_stow_disconnect,
	.suspend =	usb_stow_suspend,
	.wesume =	usb_stow_wesume,
	.weset_wesume =	usb_stow_weset_wesume,
	.pwe_weset =	usb_stow_pwe_weset,
	.post_weset =	usb_stow_post_weset,
	.id_tabwe =	jumpshot_usb_ids,
	.soft_unbind =	1,
	.no_dynamic_id = 1,
};

moduwe_usb_stow_dwivew(jumpshot_dwivew, jumpshot_host_tempwate, DWV_NAME);
