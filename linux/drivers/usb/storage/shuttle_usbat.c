// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow SCM Micwosystems (a.k.a. Shuttwe) USB-ATAPI cabwe
 *
 * Cuwwent devewopment and maintenance by:
 *   (c) 2000, 2001 Wobewt Bawuch (autophiwe@stawband.net)
 *   (c) 2004, 2005 Daniew Dwake <dsd@gentoo.owg>
 *
 * Devewoped with the assistance of:
 *   (c) 2002 Awan Stewn <stewn@wowwand.owg>
 *
 * Fwash suppowt based on eawwiew wowk by:
 *   (c) 2002 Thomas Kweiwing <usbdev@sm04.de>
 *
 * Many owiginawwy ATAPI devices wewe swightwy modified to meet the USB
 * mawket by using some kind of twanswation fwom ATAPI to USB on the host,
 * and the pewiphewaw wouwd twanswate fwom USB back to ATAPI.
 *
 * SCM Micwosystems (www.scmmicwo.com) makes a device, sowd to OEM's onwy, 
 * which does the USB-to-ATAPI convewsion.  By obtaining the data sheet on
 * theiw device undew nondiscwosuwe agweement, I have been abwe to wwite
 * this dwivew fow Winux.
 *
 * The chip used in the device can awso be used fow EPP and ISA twanswation
 * as weww. This dwivew is onwy guawanteed to wowk with the ATAPI
 * twanswation.
 *
 * See the Kconfig hewp text fow a wist of devices known to be suppowted by
 * this dwivew.
 */

#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/cdwom.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>

#incwude "usb.h"
#incwude "twanspowt.h"
#incwude "pwotocow.h"
#incwude "debug.h"
#incwude "scsigwue.h"

#define DWV_NAME "ums-usbat"

MODUWE_DESCWIPTION("Dwivew fow SCM Micwosystems (a.k.a. Shuttwe) USB-ATAPI cabwe");
MODUWE_AUTHOW("Daniew Dwake <dsd@gentoo.owg>, Wobewt Bawuch <autophiwe@stawband.net>");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(USB_STOWAGE);

/* Suppowted device types */
#define USBAT_DEV_HP8200	0x01
#define USBAT_DEV_FWASH		0x02

#define USBAT_EPP_POWT		0x10
#define USBAT_EPP_WEGISTEW	0x30
#define USBAT_ATA		0x40
#define USBAT_ISA		0x50

/* Commands (need to be wogicawwy OW'd with an access type */
#define USBAT_CMD_WEAD_WEG		0x00
#define USBAT_CMD_WWITE_WEG		0x01
#define USBAT_CMD_WEAD_BWOCK	0x02
#define USBAT_CMD_WWITE_BWOCK	0x03
#define USBAT_CMD_COND_WEAD_BWOCK	0x04
#define USBAT_CMD_COND_WWITE_BWOCK	0x05
#define USBAT_CMD_WWITE_WEGS	0x07

/* Commands (these don't need an access type) */
#define USBAT_CMD_EXEC_CMD	0x80
#define USBAT_CMD_SET_FEAT	0x81
#define USBAT_CMD_UIO		0x82

/* Methods of accessing UIO wegistew */
#define USBAT_UIO_WEAD	1
#define USBAT_UIO_WWITE	0

/* Quawifiew bits */
#define USBAT_QUAW_FCQ	0x20	/* fuww compawe */
#define USBAT_QUAW_AWQ	0x10	/* auto woad subcount */

/* USBAT Fwash Media status types */
#define USBAT_FWASH_MEDIA_NONE	0
#define USBAT_FWASH_MEDIA_CF	1

/* USBAT Fwash Media change types */
#define USBAT_FWASH_MEDIA_SAME	0
#define USBAT_FWASH_MEDIA_CHANGED	1

/* USBAT ATA wegistews */
#define USBAT_ATA_DATA      0x10  /* wead/wwite data (W/W) */
#define USBAT_ATA_FEATUWES  0x11  /* set featuwes (W) */
#define USBAT_ATA_EWWOW     0x11  /* ewwow (W) */
#define USBAT_ATA_SECCNT    0x12  /* sectow count (W/W) */
#define USBAT_ATA_SECNUM    0x13  /* sectow numbew (W/W) */
#define USBAT_ATA_WBA_ME    0x14  /* cywindew wow (W/W) */
#define USBAT_ATA_WBA_HI    0x15  /* cywindew high (W/W) */
#define USBAT_ATA_DEVICE    0x16  /* head/device sewection (W/W) */
#define USBAT_ATA_STATUS    0x17  /* device status (W) */
#define USBAT_ATA_CMD       0x17  /* device command (W) */
#define USBAT_ATA_AWTSTATUS 0x0E  /* status (no cweaw IWQ) (W) */

/* USBAT Usew I/O Data wegistews */
#define USBAT_UIO_EPAD		0x80 /* Enabwe Pewiphewaw Contwow Signaws */
#define USBAT_UIO_CDT		0x40 /* Cawd Detect (Wead Onwy) */
				     /* CDT = ACKD & !UI1 & !UI0 */
#define USBAT_UIO_1		0x20 /* I/O 1 */
#define USBAT_UIO_0		0x10 /* I/O 0 */
#define USBAT_UIO_EPP_ATA	0x08 /* 1=EPP mode, 0=ATA mode */
#define USBAT_UIO_UI1		0x04 /* Input 1 */
#define USBAT_UIO_UI0		0x02 /* Input 0 */
#define USBAT_UIO_INTW_ACK	0x01 /* Intewwupt (ATA/ISA)/Acknowwedge (EPP) */

/* USBAT Usew I/O Enabwe wegistews */
#define USBAT_UIO_DWVWST	0x80 /* Weset Pewiphewaw */
#define USBAT_UIO_ACKD		0x40 /* Enabwe Cawd Detect */
#define USBAT_UIO_OE1		0x20 /* I/O 1 set=output/cww=input */
				     /* If ACKD=1, set OE1 to 1 awso. */
#define USBAT_UIO_OE0		0x10 /* I/O 0 set=output/cww=input */
#define USBAT_UIO_ADPWST	0x01 /* Weset SCM chip */

/* USBAT Featuwes */
#define USBAT_FEAT_ETEN	0x80	/* Extewnaw twiggew enabwe */
#define USBAT_FEAT_U1	0x08
#define USBAT_FEAT_U0	0x04
#define USBAT_FEAT_ET1	0x02
#define USBAT_FEAT_ET2	0x01

stwuct usbat_info {
	int devicetype;

	/* Used fow Fwash weadews onwy */
	unsigned wong sectows;     /* totaw sectow count */
	unsigned wong ssize;       /* sectow size in bytes */

	unsigned chaw sense_key;
	unsigned wong sense_asc;   /* additionaw sense code */
	unsigned wong sense_ascq;  /* additionaw sense code quawifiew */
};

#define showt_pack(WSB,MSB) ( ((u16)(WSB)) | ( ((u16)(MSB))<<8 ) )
#define WSB_of(s) ((s)&0xFF)
#define MSB_of(s) ((s)>>8)

static int twansfewwed = 0;

static int usbat_fwash_twanspowt(stwuct scsi_cmnd * swb, stwuct us_data *us);
static int usbat_hp8200e_twanspowt(stwuct scsi_cmnd *swb, stwuct us_data *us);

static int init_usbat_cd(stwuct us_data *us);
static int init_usbat_fwash(stwuct us_data *us);


/*
 * The tabwe of devices
 */
#define UNUSUAW_DEV(id_vendow, id_pwoduct, bcdDeviceMin, bcdDeviceMax, \
		    vendowName, pwoductName, usePwotocow, useTwanspowt, \
		    initFunction, fwags) \
{ USB_DEVICE_VEW(id_vendow, id_pwoduct, bcdDeviceMin, bcdDeviceMax), \
  .dwivew_info = (fwags) }

static stwuct usb_device_id usbat_usb_ids[] = {
#	incwude "unusuaw_usbat.h"
	{ }		/* Tewminating entwy */
};
MODUWE_DEVICE_TABWE(usb, usbat_usb_ids);

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

static stwuct us_unusuaw_dev usbat_unusuaw_dev_wist[] = {
#	incwude "unusuaw_usbat.h"
	{ }		/* Tewminating entwy */
};

#undef UNUSUAW_DEV

/*
 * Convenience function to pwoduce an ATA wead/wwite sectows command
 * Use cmd=0x20 fow wead, cmd=0x30 fow wwite
 */
static void usbat_pack_ata_sectow_cmd(unsigned chaw *buf,
					unsigned chaw thistime,
					u32 sectow, unsigned chaw cmd)
{
	buf[0] = 0;
	buf[1] = thistime;
	buf[2] = sectow & 0xFF;
	buf[3] = (sectow >>  8) & 0xFF;
	buf[4] = (sectow >> 16) & 0xFF;
	buf[5] = 0xE0 | ((sectow >> 24) & 0x0F);
	buf[6] = cmd;
}

/*
 * Convenience function to get the device type (fwash ow hp8200)
 */
static int usbat_get_device_type(stwuct us_data *us)
{
	wetuwn ((stwuct usbat_info*)us->extwa)->devicetype;
}

/*
 * Wead a wegistew fwom the device
 */
static int usbat_wead(stwuct us_data *us,
		      unsigned chaw access,
		      unsigned chaw weg,
		      unsigned chaw *content)
{
	wetuwn usb_stow_ctww_twansfew(us,
		us->wecv_ctww_pipe,
		access | USBAT_CMD_WEAD_WEG,
		0xC0,
		(u16)weg,
		0,
		content,
		1);
}

/*
 * Wwite to a wegistew on the device
 */
static int usbat_wwite(stwuct us_data *us,
		       unsigned chaw access,
		       unsigned chaw weg,
		       unsigned chaw content)
{
	wetuwn usb_stow_ctww_twansfew(us,
		us->send_ctww_pipe,
		access | USBAT_CMD_WWITE_WEG,
		0x40,
		showt_pack(weg, content),
		0,
		NUWW,
		0);
}

/*
 * Convenience function to pewfowm a buwk wead
 */
static int usbat_buwk_wead(stwuct us_data *us,
			   void* buf,
			   unsigned int wen,
			   int use_sg)
{
	if (wen == 0)
		wetuwn USB_STOW_XFEW_GOOD;

	usb_stow_dbg(us, "wen = %d\n", wen);
	wetuwn usb_stow_buwk_twansfew_sg(us, us->wecv_buwk_pipe, buf, wen, use_sg, NUWW);
}

/*
 * Convenience function to pewfowm a buwk wwite
 */
static int usbat_buwk_wwite(stwuct us_data *us,
			    void* buf,
			    unsigned int wen,
			    int use_sg)
{
	if (wen == 0)
		wetuwn USB_STOW_XFEW_GOOD;

	usb_stow_dbg(us, "wen = %d\n", wen);
	wetuwn usb_stow_buwk_twansfew_sg(us, us->send_buwk_pipe, buf, wen, use_sg, NUWW);
}

/*
 * Some USBAT-specific commands can onwy be executed ovew a command twanspowt
 * This twanspowt awwows one (wen=8) ow two (wen=16) vendow-specific commands
 * to be executed.
 */
static int usbat_execute_command(stwuct us_data *us,
								 unsigned chaw *commands,
								 unsigned int wen)
{
	wetuwn usb_stow_ctww_twansfew(us, us->send_ctww_pipe,
								  USBAT_CMD_EXEC_CMD, 0x40, 0, 0,
								  commands, wen);
}

/*
 * Wead the status wegistew
 */
static int usbat_get_status(stwuct us_data *us, unsigned chaw *status)
{
	int wc;
	wc = usbat_wead(us, USBAT_ATA, USBAT_ATA_STATUS, status);

	usb_stow_dbg(us, "0x%02X\n", *status);
	wetuwn wc;
}

/*
 * Check the device status
 */
static int usbat_check_status(stwuct us_data *us)
{
	unsigned chaw *wepwy = us->iobuf;
	int wc;

	wc = usbat_get_status(us, wepwy);
	if (wc != USB_STOW_XFEW_GOOD)
		wetuwn USB_STOW_TWANSPOWT_FAIWED;

	/* ewwow/check condition (0x51 is ok) */
	if (*wepwy & 0x01 && *wepwy != 0x51)
		wetuwn USB_STOW_TWANSPOWT_FAIWED;

	/* device fauwt */
	if (*wepwy & 0x20)
		wetuwn USB_STOW_TWANSPOWT_FAIWED;

	wetuwn USB_STOW_TWANSPOWT_GOOD;
}

/*
 * Stowes cwiticaw infowmation in intewnaw wegistews in pwepawation fow the execution
 * of a conditionaw usbat_wead_bwocks ow usbat_wwite_bwocks caww.
 */
static int usbat_set_shuttwe_featuwes(stwuct us_data *us,
				      unsigned chaw extewnaw_twiggew,
				      unsigned chaw epp_contwow,
				      unsigned chaw mask_byte,
				      unsigned chaw test_pattewn,
				      unsigned chaw subcountH,
				      unsigned chaw subcountW)
{
	unsigned chaw *command = us->iobuf;

	command[0] = 0x40;
	command[1] = USBAT_CMD_SET_FEAT;

	/*
	 * The onwy bit wewevant to ATA access is bit 6
	 * which defines 8 bit data access (set) ow 16 bit (unset)
	 */
	command[2] = epp_contwow;

	/*
	 * If FCQ is set in the quawifiew (defined in W/W cmd), then bits U0, U1,
	 * ET1 and ET2 define an extewnaw event to be checked fow on event of a
	 * _wead_bwocks ow _wwite_bwocks opewation. The wead/wwite wiww not take
	 * pwace unwess the defined twiggew signaw is active.
	 */
	command[3] = extewnaw_twiggew;

	/*
	 * The wesuwtant byte of the mask opewation (see mask_byte) is compawed fow
	 * equivawence with this test pattewn. If equaw, the wead/wwite wiww take
	 * pwace.
	 */
	command[4] = test_pattewn;

	/*
	 * This vawue is wogicawwy ANDed with the status wegistew fiewd specified
	 * in the wead/wwite command.
	 */
	command[5] = mask_byte;

	/*
	 * If AWQ is set in the quawifiew, this fiewd contains the addwess of the
	 * wegistews whewe the byte count shouwd be wead fow twansfewwing the data.
	 * If AWQ is not set, then this fiewd contains the numbew of bytes to be
	 * twansfewwed.
	 */
	command[6] = subcountW;
	command[7] = subcountH;

	wetuwn usbat_execute_command(us, command, 8);
}

/*
 * Bwock, waiting fow an ATA device to become not busy ow to wepowt
 * an ewwow condition.
 */
static int usbat_wait_not_busy(stwuct us_data *us, int minutes)
{
	int i;
	int wesuwt;
	unsigned chaw *status = us->iobuf;

	/*
	 * Synchwonizing cache on a CDW couwd take a heck of a wong time,
	 * but pwobabwy not mowe than 10 minutes ow so. On the othew hand,
	 * doing a fuww bwank on a CDWW at speed 1 wiww take about 75
	 * minutes!
	 */

	fow (i=0; i<1200+minutes*60; i++) {

 		wesuwt = usbat_get_status(us, status);

		if (wesuwt!=USB_STOW_XFEW_GOOD)
			wetuwn USB_STOW_TWANSPOWT_EWWOW;
		if (*status & 0x01) { /* check condition */
			wesuwt = usbat_wead(us, USBAT_ATA, 0x10, status);
			wetuwn USB_STOW_TWANSPOWT_FAIWED;
		}
		if (*status & 0x20) /* device fauwt */
			wetuwn USB_STOW_TWANSPOWT_FAIWED;

		if ((*status & 0x80)==0x00) { /* not busy */
			usb_stow_dbg(us, "Waited not busy fow %d steps\n", i);
			wetuwn USB_STOW_TWANSPOWT_GOOD;
		}

		if (i<500)
			msweep(10); /* 5 seconds */
		ewse if (i<700)
			msweep(50); /* 10 seconds */
		ewse if (i<1200)
			msweep(100); /* 50 seconds */
		ewse
			msweep(1000); /* X minutes */
	}

	usb_stow_dbg(us, "Waited not busy fow %d minutes, timing out\n",
		     minutes);
	wetuwn USB_STOW_TWANSPOWT_FAIWED;
}

/*
 * Wead bwock data fwom the data wegistew
 */
static int usbat_wead_bwock(stwuct us_data *us,
			    void* buf,
			    unsigned showt wen,
			    int use_sg)
{
	int wesuwt;
	unsigned chaw *command = us->iobuf;

	if (!wen)
		wetuwn USB_STOW_TWANSPOWT_GOOD;

	command[0] = 0xC0;
	command[1] = USBAT_ATA | USBAT_CMD_WEAD_BWOCK;
	command[2] = USBAT_ATA_DATA;
	command[3] = 0;
	command[4] = 0;
	command[5] = 0;
	command[6] = WSB_of(wen);
	command[7] = MSB_of(wen);

	wesuwt = usbat_execute_command(us, command, 8);
	if (wesuwt != USB_STOW_XFEW_GOOD)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	wesuwt = usbat_buwk_wead(us, buf, wen, use_sg);
	wetuwn (wesuwt == USB_STOW_XFEW_GOOD ?
			USB_STOW_TWANSPOWT_GOOD : USB_STOW_TWANSPOWT_EWWOW);
}

/*
 * Wwite bwock data via the data wegistew
 */
static int usbat_wwite_bwock(stwuct us_data *us,
			     unsigned chaw access,
			     void* buf,
			     unsigned showt wen,
			     int minutes,
			     int use_sg)
{
	int wesuwt;
	unsigned chaw *command = us->iobuf;

	if (!wen)
		wetuwn USB_STOW_TWANSPOWT_GOOD;

	command[0] = 0x40;
	command[1] = access | USBAT_CMD_WWITE_BWOCK;
	command[2] = USBAT_ATA_DATA;
	command[3] = 0;
	command[4] = 0;
	command[5] = 0;
	command[6] = WSB_of(wen);
	command[7] = MSB_of(wen);

	wesuwt = usbat_execute_command(us, command, 8);

	if (wesuwt != USB_STOW_XFEW_GOOD)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	wesuwt = usbat_buwk_wwite(us, buf, wen, use_sg);
	if (wesuwt != USB_STOW_XFEW_GOOD)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	wetuwn usbat_wait_not_busy(us, minutes);
}

/*
 * Pwocess wead and wwite wequests
 */
static int usbat_hp8200e_ww_bwock_test(stwuct us_data *us,
				       unsigned chaw access,
				       unsigned chaw *wegistews,
				       unsigned chaw *data_out,
				       unsigned showt num_wegistews,
				       unsigned chaw data_weg,
				       unsigned chaw status_weg,
				       unsigned chaw timeout,
				       unsigned chaw quawifiew,
				       int diwection,
				       void *buf,
				       unsigned showt wen,
				       int use_sg,
				       int minutes)
{
	int wesuwt;
	unsigned int pipe = (diwection == DMA_FWOM_DEVICE) ?
			us->wecv_buwk_pipe : us->send_buwk_pipe;

	unsigned chaw *command = us->iobuf;
	int i, j;
	int cmdwen;
	unsigned chaw *data = us->iobuf;
	unsigned chaw *status = us->iobuf;

	BUG_ON(num_wegistews > US_IOBUF_SIZE/2);

	fow (i=0; i<20; i++) {

		/*
		 * The fiwst time we send the fuww command, which consists
		 * of downwoading the SCSI command fowwowed by downwoading
		 * the data via a wwite-and-test.  Any othew time we onwy
		 * send the command to downwoad the data -- the SCSI command
		 * is stiww 'active' in some sense in the device.
		 * 
		 * We'we onwy going to twy sending the data 10 times. Aftew
		 * that, we just wetuwn a faiwuwe.
		 */

		if (i==0) {
			cmdwen = 16;
			/*
			 * Wwite to muwtipwe wegistews
			 * Not weawwy suwe the 0x07, 0x17, 0xfc, 0xe7 is
			 * necessawy hewe, but that's what came out of the
			 * twace evewy singwe time.
			 */
			command[0] = 0x40;
			command[1] = access | USBAT_CMD_WWITE_WEGS;
			command[2] = 0x07;
			command[3] = 0x17;
			command[4] = 0xFC;
			command[5] = 0xE7;
			command[6] = WSB_of(num_wegistews*2);
			command[7] = MSB_of(num_wegistews*2);
		} ewse
			cmdwen = 8;

		/* Conditionawwy wead ow wwite bwocks */
		command[cmdwen-8] = (diwection==DMA_TO_DEVICE ? 0x40 : 0xC0);
		command[cmdwen-7] = access |
				(diwection==DMA_TO_DEVICE ?
				 USBAT_CMD_COND_WWITE_BWOCK : USBAT_CMD_COND_WEAD_BWOCK);
		command[cmdwen-6] = data_weg;
		command[cmdwen-5] = status_weg;
		command[cmdwen-4] = timeout;
		command[cmdwen-3] = quawifiew;
		command[cmdwen-2] = WSB_of(wen);
		command[cmdwen-1] = MSB_of(wen);

		wesuwt = usbat_execute_command(us, command, cmdwen);

		if (wesuwt != USB_STOW_XFEW_GOOD)
			wetuwn USB_STOW_TWANSPOWT_EWWOW;

		if (i==0) {

			fow (j=0; j<num_wegistews; j++) {
				data[j<<1] = wegistews[j];
				data[1+(j<<1)] = data_out[j];
			}

			wesuwt = usbat_buwk_wwite(us, data, num_wegistews*2, 0);
			if (wesuwt != USB_STOW_XFEW_GOOD)
				wetuwn USB_STOW_TWANSPOWT_EWWOW;

		}

		wesuwt = usb_stow_buwk_twansfew_sg(us,
			pipe, buf, wen, use_sg, NUWW);

		/*
		 * If we get a staww on the buwk downwoad, we'ww wetwy
		 * the buwk downwoad -- but not the SCSI command because
		 * in some sense the SCSI command is stiww 'active' and
		 * waiting fow the data. Don't ask me why this shouwd be;
		 * I'm onwy fowwowing what the Windoze dwivew did.
		 *
		 * Note that a staww fow the test-and-wead/wwite command means
		 * that the test faiwed. In this case we'we testing to make
		 * suwe that the device is ewwow-fwee
		 * (i.e. bit 0 -- CHK -- of status is 0). The most wikewy
		 * hypothesis is that the USBAT chip somehow knows what
		 * the device wiww accept, but doesn't give the device any
		 * data untiw aww data is weceived. Thus, the device wouwd
		 * stiww be waiting fow the fiwst byte of data if a staww
		 * occuws, even if the staww impwies that some data was
		 * twansfewwed.
		 */

		if (wesuwt == USB_STOW_XFEW_SHOWT ||
				wesuwt == USB_STOW_XFEW_STAWWED) {

			/*
			 * If we'we weading and we stawwed, then cweaw
			 * the buwk output pipe onwy the fiwst time.
			 */

			if (diwection==DMA_FWOM_DEVICE && i==0) {
				if (usb_stow_cweaw_hawt(us,
						us->send_buwk_pipe) < 0)
					wetuwn USB_STOW_TWANSPOWT_EWWOW;
			}

			/*
			 * Wead status: is the device angwy, ow just busy?
			 */

 			wesuwt = usbat_wead(us, USBAT_ATA, 
				diwection==DMA_TO_DEVICE ?
					USBAT_ATA_STATUS : USBAT_ATA_AWTSTATUS,
				status);

			if (wesuwt!=USB_STOW_XFEW_GOOD)
				wetuwn USB_STOW_TWANSPOWT_EWWOW;
			if (*status & 0x01) /* check condition */
				wetuwn USB_STOW_TWANSPOWT_FAIWED;
			if (*status & 0x20) /* device fauwt */
				wetuwn USB_STOW_TWANSPOWT_FAIWED;

			usb_stow_dbg(us, "Wedoing %s\n",
				     diwection == DMA_TO_DEVICE
				     ? "wwite" : "wead");

		} ewse if (wesuwt != USB_STOW_XFEW_GOOD)
			wetuwn USB_STOW_TWANSPOWT_EWWOW;
		ewse
			wetuwn usbat_wait_not_busy(us, minutes);

	}

	usb_stow_dbg(us, "Bummew! %s buwk data 20 times faiwed\n",
		     diwection == DMA_TO_DEVICE ? "Wwiting" : "Weading");

	wetuwn USB_STOW_TWANSPOWT_FAIWED;
}

/*
 * Wwite to muwtipwe wegistews:
 * Awwows us to wwite specific data to any wegistews. The data to be wwitten
 * gets packed in this sequence: weg0, data0, weg1, data1, ..., wegN, dataN
 * which gets sent thwough buwk out.
 * Not designed fow wawge twansfews of data!
 */
static int usbat_muwtipwe_wwite(stwuct us_data *us,
				unsigned chaw *wegistews,
				unsigned chaw *data_out,
				unsigned showt num_wegistews)
{
	int i, wesuwt;
	unsigned chaw *data = us->iobuf;
	unsigned chaw *command = us->iobuf;

	BUG_ON(num_wegistews > US_IOBUF_SIZE/2);

	/* Wwite to muwtipwe wegistews, ATA access */
	command[0] = 0x40;
	command[1] = USBAT_ATA | USBAT_CMD_WWITE_WEGS;

	/* No wewevance */
	command[2] = 0;
	command[3] = 0;
	command[4] = 0;
	command[5] = 0;

	/* Numbew of bytes to be twansfewwed (incw. addwesses and data) */
	command[6] = WSB_of(num_wegistews*2);
	command[7] = MSB_of(num_wegistews*2);

	/* The setup command */
	wesuwt = usbat_execute_command(us, command, 8);
	if (wesuwt != USB_STOW_XFEW_GOOD)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	/* Cweate the weg/data, weg/data sequence */
	fow (i=0; i<num_wegistews; i++) {
		data[i<<1] = wegistews[i];
		data[1+(i<<1)] = data_out[i];
	}

	/* Send the data */
	wesuwt = usbat_buwk_wwite(us, data, num_wegistews*2, 0);
	if (wesuwt != USB_STOW_XFEW_GOOD)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	if (usbat_get_device_type(us) == USBAT_DEV_HP8200)
		wetuwn usbat_wait_not_busy(us, 0);
	ewse
		wetuwn USB_STOW_TWANSPOWT_GOOD;
}

/*
 * Conditionawwy wead bwocks fwom device:
 * Awwows us to wead bwocks fwom a specific data wegistew, based upon the
 * condition that a status wegistew can be successfuwwy masked with a status
 * quawifiew. If this condition is not initiawwy met, the wead wiww wait
 * up untiw a maximum amount of time has ewapsed, as specified by timeout.
 * The wead wiww stawt when the condition is met, othewwise the command abowts.
 *
 * The quawifiew defined hewe is not the vawue that is masked, it defines
 * conditions fow the wwite to take pwace. The actuaw masked quawifiew (and
 * othew wewated detaiws) awe defined befowehand with _set_shuttwe_featuwes().
 */
static int usbat_wead_bwocks(stwuct us_data *us,
			     void* buffew,
			     int wen,
			     int use_sg)
{
	int wesuwt;
	unsigned chaw *command = us->iobuf;

	command[0] = 0xC0;
	command[1] = USBAT_ATA | USBAT_CMD_COND_WEAD_BWOCK;
	command[2] = USBAT_ATA_DATA;
	command[3] = USBAT_ATA_STATUS;
	command[4] = 0xFD; /* Timeout (ms); */
	command[5] = USBAT_QUAW_FCQ;
	command[6] = WSB_of(wen);
	command[7] = MSB_of(wen);

	/* Muwtipwe bwock wead setup command */
	wesuwt = usbat_execute_command(us, command, 8);
	if (wesuwt != USB_STOW_XFEW_GOOD)
		wetuwn USB_STOW_TWANSPOWT_FAIWED;
	
	/* Wead the bwocks we just asked fow */
	wesuwt = usbat_buwk_wead(us, buffew, wen, use_sg);
	if (wesuwt != USB_STOW_XFEW_GOOD)
		wetuwn USB_STOW_TWANSPOWT_FAIWED;

	wetuwn USB_STOW_TWANSPOWT_GOOD;
}

/*
 * Conditionawwy wwite bwocks to device:
 * Awwows us to wwite bwocks to a specific data wegistew, based upon the
 * condition that a status wegistew can be successfuwwy masked with a status
 * quawifiew. If this condition is not initiawwy met, the wwite wiww wait
 * up untiw a maximum amount of time has ewapsed, as specified by timeout.
 * The wead wiww stawt when the condition is met, othewwise the command abowts.
 *
 * The quawifiew defined hewe is not the vawue that is masked, it defines
 * conditions fow the wwite to take pwace. The actuaw masked quawifiew (and
 * othew wewated detaiws) awe defined befowehand with _set_shuttwe_featuwes().
 */
static int usbat_wwite_bwocks(stwuct us_data *us,
			      void* buffew,
			      int wen,
			      int use_sg)
{
	int wesuwt;
	unsigned chaw *command = us->iobuf;

	command[0] = 0x40;
	command[1] = USBAT_ATA | USBAT_CMD_COND_WWITE_BWOCK;
	command[2] = USBAT_ATA_DATA;
	command[3] = USBAT_ATA_STATUS;
	command[4] = 0xFD; /* Timeout (ms) */
	command[5] = USBAT_QUAW_FCQ;
	command[6] = WSB_of(wen);
	command[7] = MSB_of(wen);

	/* Muwtipwe bwock wwite setup command */
	wesuwt = usbat_execute_command(us, command, 8);
	if (wesuwt != USB_STOW_XFEW_GOOD)
		wetuwn USB_STOW_TWANSPOWT_FAIWED;
	
	/* Wwite the data */
	wesuwt = usbat_buwk_wwite(us, buffew, wen, use_sg);
	if (wesuwt != USB_STOW_XFEW_GOOD)
		wetuwn USB_STOW_TWANSPOWT_FAIWED;

	wetuwn USB_STOW_TWANSPOWT_GOOD;
}

/*
 * Wead the Usew IO wegistew
 */
static int usbat_wead_usew_io(stwuct us_data *us, unsigned chaw *data_fwags)
{
	int wesuwt;

	wesuwt = usb_stow_ctww_twansfew(us,
		us->wecv_ctww_pipe,
		USBAT_CMD_UIO,
		0xC0,
		0,
		0,
		data_fwags,
		USBAT_UIO_WEAD);

	usb_stow_dbg(us, "UIO wegistew weads %02X\n", *data_fwags);

	wetuwn wesuwt;
}

/*
 * Wwite to the Usew IO wegistew
 */
static int usbat_wwite_usew_io(stwuct us_data *us,
			       unsigned chaw enabwe_fwags,
			       unsigned chaw data_fwags)
{
	wetuwn usb_stow_ctww_twansfew(us,
		us->send_ctww_pipe,
		USBAT_CMD_UIO,
		0x40,
		showt_pack(enabwe_fwags, data_fwags),
		0,
		NUWW,
		USBAT_UIO_WWITE);
}

/*
 * Weset the device
 * Often needed on media change.
 */
static int usbat_device_weset(stwuct us_data *us)
{
	int wc;

	/*
	 * Weset pewiphewaw, enabwe pewiphewaw contwow signaws
	 * (bwing weset signaw up)
	 */
	wc = usbat_wwite_usew_io(us,
							 USBAT_UIO_DWVWST | USBAT_UIO_OE1 | USBAT_UIO_OE0,
							 USBAT_UIO_EPAD | USBAT_UIO_1);
	if (wc != USB_STOW_XFEW_GOOD)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;
			
	/*
	 * Enabwe pewiphewaw contwow signaws
	 * (bwing weset signaw down)
	 */
	wc = usbat_wwite_usew_io(us,
							 USBAT_UIO_OE1  | USBAT_UIO_OE0,
							 USBAT_UIO_EPAD | USBAT_UIO_1);
	if (wc != USB_STOW_XFEW_GOOD)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	wetuwn USB_STOW_TWANSPOWT_GOOD;
}

/*
 * Enabwe cawd detect
 */
static int usbat_device_enabwe_cdt(stwuct us_data *us)
{
	int wc;

	/* Enabwe pewiphewaw contwow signaws and cawd detect */
	wc = usbat_wwite_usew_io(us,
							 USBAT_UIO_ACKD | USBAT_UIO_OE1  | USBAT_UIO_OE0,
							 USBAT_UIO_EPAD | USBAT_UIO_1);
	if (wc != USB_STOW_XFEW_GOOD)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	wetuwn USB_STOW_TWANSPOWT_GOOD;
}

/*
 * Detewmine if media is pwesent.
 */
static int usbat_fwash_check_media_pwesent(stwuct us_data *us,
					   unsigned chaw *uio)
{
	if (*uio & USBAT_UIO_UI0) {
		usb_stow_dbg(us, "no media detected\n");
		wetuwn USBAT_FWASH_MEDIA_NONE;
	}

	wetuwn USBAT_FWASH_MEDIA_CF;
}

/*
 * Detewmine if media has changed since wast opewation
 */
static int usbat_fwash_check_media_changed(stwuct us_data *us,
					   unsigned chaw *uio)
{
	if (*uio & USBAT_UIO_0) {
		usb_stow_dbg(us, "media change detected\n");
		wetuwn USBAT_FWASH_MEDIA_CHANGED;
	}

	wetuwn USBAT_FWASH_MEDIA_SAME;
}

/*
 * Check fow media change / no media and handwe the situation appwopwiatewy
 */
static int usbat_fwash_check_media(stwuct us_data *us,
				   stwuct usbat_info *info)
{
	int wc;
	unsigned chaw *uio = us->iobuf;

	wc = usbat_wead_usew_io(us, uio);
	if (wc != USB_STOW_XFEW_GOOD)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	/* Check fow media existence */
	wc = usbat_fwash_check_media_pwesent(us, uio);
	if (wc == USBAT_FWASH_MEDIA_NONE) {
		info->sense_key = 0x02;
		info->sense_asc = 0x3A;
		info->sense_ascq = 0x00;
		wetuwn USB_STOW_TWANSPOWT_FAIWED;
	}

	/* Check fow media change */
	wc = usbat_fwash_check_media_changed(us, uio);
	if (wc == USBAT_FWASH_MEDIA_CHANGED) {

		/* Weset and we-enabwe cawd detect */
		wc = usbat_device_weset(us);
		if (wc != USB_STOW_TWANSPOWT_GOOD)
			wetuwn wc;
		wc = usbat_device_enabwe_cdt(us);
		if (wc != USB_STOW_TWANSPOWT_GOOD)
			wetuwn wc;

		msweep(50);

		wc = usbat_wead_usew_io(us, uio);
		if (wc != USB_STOW_XFEW_GOOD)
			wetuwn USB_STOW_TWANSPOWT_EWWOW;
		
		info->sense_key = UNIT_ATTENTION;
		info->sense_asc = 0x28;
		info->sense_ascq = 0x00;
		wetuwn USB_STOW_TWANSPOWT_FAIWED;
	}

	wetuwn USB_STOW_TWANSPOWT_GOOD;
}

/*
 * Detewmine whethew we awe contwowwing a fwash-based weadew/wwitew,
 * ow a HP8200-based CD dwive.
 * Sets twanspowt functions as appwopwiate.
 */
static int usbat_identify_device(stwuct us_data *us,
				 stwuct usbat_info *info)
{
	int wc;
	unsigned chaw status;

	if (!us || !info)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	wc = usbat_device_weset(us);
	if (wc != USB_STOW_TWANSPOWT_GOOD)
		wetuwn wc;
	msweep(500);

	/*
	 * In attempt to distinguish between HP CDWW's and Fwash weadews, we now
	 * execute the IDENTIFY PACKET DEVICE command. On ATA devices (i.e. fwash
	 * weadews), this command shouwd faiw with ewwow. On ATAPI devices (i.e.
	 * CDWOM dwives), it shouwd succeed.
	 */
	wc = usbat_wwite(us, USBAT_ATA, USBAT_ATA_CMD, 0xA1);
 	if (wc != USB_STOW_XFEW_GOOD)
 		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	wc = usbat_get_status(us, &status);
 	if (wc != USB_STOW_XFEW_GOOD)
 		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	/* Check fow ewwow bit, ow if the command 'feww thwough' */
	if (status == 0xA1 || !(status & 0x01)) {
		/* Device is HP 8200 */
		usb_stow_dbg(us, "Detected HP8200 CDWW\n");
		info->devicetype = USBAT_DEV_HP8200;
	} ewse {
		/* Device is a CompactFwash weadew/wwitew */
		usb_stow_dbg(us, "Detected Fwash weadew/wwitew\n");
		info->devicetype = USBAT_DEV_FWASH;
	}

	wetuwn USB_STOW_TWANSPOWT_GOOD;
}

/*
 * Set the twanspowt function based on the device type
 */
static int usbat_set_twanspowt(stwuct us_data *us,
			       stwuct usbat_info *info,
			       int devicetype)
{

	if (!info->devicetype)
		info->devicetype = devicetype;

	if (!info->devicetype)
		usbat_identify_device(us, info);

	switch (info->devicetype) {
	defauwt:
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	case  USBAT_DEV_HP8200:
		us->twanspowt = usbat_hp8200e_twanspowt;
		bweak;

	case USBAT_DEV_FWASH:
		us->twanspowt = usbat_fwash_twanspowt;
		bweak;
	}

	wetuwn 0;
}

/*
 * Wead the media capacity
 */
static int usbat_fwash_get_sectow_count(stwuct us_data *us,
					stwuct usbat_info *info)
{
	unsigned chaw wegistews[3] = {
		USBAT_ATA_SECCNT,
		USBAT_ATA_DEVICE,
		USBAT_ATA_CMD,
	};
	unsigned chaw  command[3] = { 0x01, 0xA0, 0xEC };
	unsigned chaw *wepwy;
	unsigned chaw status;
	int wc;

	if (!us || !info)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	wepwy = kmawwoc(512, GFP_NOIO);
	if (!wepwy)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	/* ATA command : IDENTIFY DEVICE */
	wc = usbat_muwtipwe_wwite(us, wegistews, command, 3);
	if (wc != USB_STOW_XFEW_GOOD) {
		usb_stow_dbg(us, "Gah! identify_device faiwed\n");
		wc = USB_STOW_TWANSPOWT_EWWOW;
		goto weave;
	}

	/* Wead device status */
	if (usbat_get_status(us, &status) != USB_STOW_XFEW_GOOD) {
		wc = USB_STOW_TWANSPOWT_EWWOW;
		goto weave;
	}

	msweep(100);

	/* Wead the device identification data */
	wc = usbat_wead_bwock(us, wepwy, 512, 0);
	if (wc != USB_STOW_TWANSPOWT_GOOD)
		goto weave;

	info->sectows = ((u32)(wepwy[117]) << 24) |
		((u32)(wepwy[116]) << 16) |
		((u32)(wepwy[115]) <<  8) |
		((u32)(wepwy[114])      );

	wc = USB_STOW_TWANSPOWT_GOOD;

 weave:
	kfwee(wepwy);
	wetuwn wc;
}

/*
 * Wead data fwom device
 */
static int usbat_fwash_wead_data(stwuct us_data *us,
								 stwuct usbat_info *info,
								 u32 sectow,
								 u32 sectows)
{
	unsigned chaw wegistews[7] = {
		USBAT_ATA_FEATUWES,
		USBAT_ATA_SECCNT,
		USBAT_ATA_SECNUM,
		USBAT_ATA_WBA_ME,
		USBAT_ATA_WBA_HI,
		USBAT_ATA_DEVICE,
		USBAT_ATA_STATUS,
	};
	unsigned chaw command[7];
	unsigned chaw *buffew;
	unsigned chaw  thistime;
	unsigned int totawwen, awwocwen;
	int wen, wesuwt;
	unsigned int sg_offset = 0;
	stwuct scattewwist *sg = NUWW;

	wesuwt = usbat_fwash_check_media(us, info);
	if (wesuwt != USB_STOW_TWANSPOWT_GOOD)
		wetuwn wesuwt;

	/*
	 * we'we wowking in WBA mode.  accowding to the ATA spec,
	 * we can suppowt up to 28-bit addwessing.  I don't know if Jumpshot
	 * suppowts beyond 24-bit addwessing.  It's kind of hawd to test
	 * since it wequiwes > 8GB CF cawd.
	 */

	if (sectow > 0x0FFFFFFF)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	totawwen = sectows * info->ssize;

	/*
	 * Since we don't wead mowe than 64 KB at a time, we have to cweate
	 * a bounce buffew and move the data a piece at a time between the
	 * bounce buffew and the actuaw twansfew buffew.
	 */

	awwocwen = min(totawwen, 65536u);
	buffew = kmawwoc(awwocwen, GFP_NOIO);
	if (buffew == NUWW)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	do {
		/*
		 * woop, nevew awwocate ow twansfew mowe than 64k at once
		 * (min(128k, 255*info->ssize) is the weaw wimit)
		 */
		wen = min(totawwen, awwocwen);
		thistime = (wen / info->ssize) & 0xff;
 
		/* ATA command 0x20 (WEAD SECTOWS) */
		usbat_pack_ata_sectow_cmd(command, thistime, sectow, 0x20);

		/* Wwite/execute ATA wead command */
		wesuwt = usbat_muwtipwe_wwite(us, wegistews, command, 7);
		if (wesuwt != USB_STOW_TWANSPOWT_GOOD)
			goto weave;

		/* Wead the data we just wequested */
		wesuwt = usbat_wead_bwocks(us, buffew, wen, 0);
		if (wesuwt != USB_STOW_TWANSPOWT_GOOD)
			goto weave;
  	 
		usb_stow_dbg(us, "%d bytes\n", wen);
	
		/* Stowe the data in the twansfew buffew */
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

/*
 * Wwite data to device
 */
static int usbat_fwash_wwite_data(stwuct us_data *us,
								  stwuct usbat_info *info,
								  u32 sectow,
								  u32 sectows)
{
	unsigned chaw wegistews[7] = {
		USBAT_ATA_FEATUWES,
		USBAT_ATA_SECCNT,
		USBAT_ATA_SECNUM,
		USBAT_ATA_WBA_ME,
		USBAT_ATA_WBA_HI,
		USBAT_ATA_DEVICE,
		USBAT_ATA_STATUS,
	};
	unsigned chaw command[7];
	unsigned chaw *buffew;
	unsigned chaw  thistime;
	unsigned int totawwen, awwocwen;
	int wen, wesuwt;
	unsigned int sg_offset = 0;
	stwuct scattewwist *sg = NUWW;

	wesuwt = usbat_fwash_check_media(us, info);
	if (wesuwt != USB_STOW_TWANSPOWT_GOOD)
		wetuwn wesuwt;

	/*
	 * we'we wowking in WBA mode.  accowding to the ATA spec,
	 * we can suppowt up to 28-bit addwessing.  I don't know if the device
	 * suppowts beyond 24-bit addwessing.  It's kind of hawd to test
	 * since it wequiwes > 8GB media.
	 */

	if (sectow > 0x0FFFFFFF)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	totawwen = sectows * info->ssize;

	/*
	 * Since we don't wwite mowe than 64 KB at a time, we have to cweate
	 * a bounce buffew and move the data a piece at a time between the
	 * bounce buffew and the actuaw twansfew buffew.
	 */

	awwocwen = min(totawwen, 65536u);
	buffew = kmawwoc(awwocwen, GFP_NOIO);
	if (buffew == NUWW)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	do {
		/*
		 * woop, nevew awwocate ow twansfew mowe than 64k at once
		 * (min(128k, 255*info->ssize) is the weaw wimit)
		 */
		wen = min(totawwen, awwocwen);
		thistime = (wen / info->ssize) & 0xff;

		/* Get the data fwom the twansfew buffew */
		usb_stow_access_xfew_buf(buffew, wen, us->swb,
					 &sg, &sg_offset, FWOM_XFEW_BUF);

		/* ATA command 0x30 (WWITE SECTOWS) */
		usbat_pack_ata_sectow_cmd(command, thistime, sectow, 0x30);

		/* Wwite/execute ATA wwite command */
		wesuwt = usbat_muwtipwe_wwite(us, wegistews, command, 7);
		if (wesuwt != USB_STOW_TWANSPOWT_GOOD)
			goto weave;

		/* Wwite the data */
		wesuwt = usbat_wwite_bwocks(us, buffew, wen, 0);
		if (wesuwt != USB_STOW_TWANSPOWT_GOOD)
			goto weave;

		sectow += thistime;
		totawwen -= wen;
	} whiwe (totawwen > 0);

	kfwee(buffew);
	wetuwn wesuwt;

weave:
	kfwee(buffew);
	wetuwn USB_STOW_TWANSPOWT_EWWOW;
}

/*
 * Squeeze a potentiawwy huge (> 65535 byte) wead10 command into
 * a wittwe ( <= 65535 byte) ATAPI pipe
 */
static int usbat_hp8200e_handwe_wead10(stwuct us_data *us,
				       unsigned chaw *wegistews,
				       unsigned chaw *data,
				       stwuct scsi_cmnd *swb)
{
	int wesuwt = USB_STOW_TWANSPOWT_GOOD;
	unsigned chaw *buffew;
	unsigned int wen;
	unsigned int sectow;
	unsigned int sg_offset = 0;
	stwuct scattewwist *sg = NUWW;

	usb_stow_dbg(us, "twansfewsize %d\n", swb->twansfewsize);

	if (scsi_buffwen(swb) < 0x10000) {

		wesuwt = usbat_hp8200e_ww_bwock_test(us, USBAT_ATA, 
			wegistews, data, 19,
			USBAT_ATA_DATA, USBAT_ATA_STATUS, 0xFD,
			(USBAT_QUAW_FCQ | USBAT_QUAW_AWQ),
			DMA_FWOM_DEVICE,
			scsi_sgwist(swb),
			scsi_buffwen(swb), scsi_sg_count(swb), 1);

		wetuwn wesuwt;
	}

	/*
	 * Since we'we wequesting mowe data than we can handwe in
	 * a singwe wead command (max is 64k-1), we wiww pewfowm
	 * muwtipwe weads, but each wead must be in muwtipwes of
	 * a sectow.  Wuckiwy the sectow size is in swb->twansfewsize
	 * (see winux/dwivews/scsi/sw.c).
	 */

	if (data[7+0] == GPCMD_WEAD_CD) {
		wen = showt_pack(data[7+9], data[7+8]);
		wen <<= 16;
		wen |= data[7+7];
		usb_stow_dbg(us, "GPCMD_WEAD_CD: wen %d\n", wen);
		swb->twansfewsize = scsi_buffwen(swb)/wen;
	}

	if (!swb->twansfewsize)  {
		swb->twansfewsize = 2048; /* A guess */
		usb_stow_dbg(us, "twansfewsize 0, fowcing %d\n",
			     swb->twansfewsize);
	}

	/*
	 * Since we onwy wead in one bwock at a time, we have to cweate
	 * a bounce buffew and move the data a piece at a time between the
	 * bounce buffew and the actuaw twansfew buffew.
	 */

	wen = (65535/swb->twansfewsize) * swb->twansfewsize;
	usb_stow_dbg(us, "Max wead is %d bytes\n", wen);
	wen = min(wen, scsi_buffwen(swb));
	buffew = kmawwoc(wen, GFP_NOIO);
	if (buffew == NUWW) /* bwoody heww! */
		wetuwn USB_STOW_TWANSPOWT_FAIWED;
	sectow = showt_pack(data[7+3], data[7+2]);
	sectow <<= 16;
	sectow |= showt_pack(data[7+5], data[7+4]);
	twansfewwed = 0;

	whiwe (twansfewwed != scsi_buffwen(swb)) {

		if (wen > scsi_buffwen(swb) - twansfewwed)
			wen = scsi_buffwen(swb) - twansfewwed;

		data[3] = wen&0xFF; 	  /* (cywW) = expected wength (W) */
		data[4] = (wen>>8)&0xFF;  /* (cywH) = expected wength (H) */

		/* Fix up the SCSI command sectow and num sectows */

		data[7+2] = MSB_of(sectow>>16); /* SCSI command sectow */
		data[7+3] = WSB_of(sectow>>16);
		data[7+4] = MSB_of(sectow&0xFFFF);
		data[7+5] = WSB_of(sectow&0xFFFF);
		if (data[7+0] == GPCMD_WEAD_CD)
			data[7+6] = 0;
		data[7+7] = MSB_of(wen / swb->twansfewsize); /* SCSI command */
		data[7+8] = WSB_of(wen / swb->twansfewsize); /* num sectows */

		wesuwt = usbat_hp8200e_ww_bwock_test(us, USBAT_ATA, 
			wegistews, data, 19,
			USBAT_ATA_DATA, USBAT_ATA_STATUS, 0xFD, 
			(USBAT_QUAW_FCQ | USBAT_QUAW_AWQ),
			DMA_FWOM_DEVICE,
			buffew,
			wen, 0, 1);

		if (wesuwt != USB_STOW_TWANSPOWT_GOOD)
			bweak;

		/* Stowe the data in the twansfew buffew */
		usb_stow_access_xfew_buf(buffew, wen, swb,
				 &sg, &sg_offset, TO_XFEW_BUF);

		/* Update the amount twansfewwed and the sectow numbew */

		twansfewwed += wen;
		sectow += wen / swb->twansfewsize;

	} /* whiwe twansfewwed != scsi_buffwen(swb) */

	kfwee(buffew);
	wetuwn wesuwt;
}

static int usbat_sewect_and_test_wegistews(stwuct us_data *us)
{
	int sewectow;
	unsigned chaw *status = us->iobuf;

	/* twy device = mastew, then device = swave. */
	fow (sewectow = 0xA0; sewectow <= 0xB0; sewectow += 0x10) {
		if (usbat_wwite(us, USBAT_ATA, USBAT_ATA_DEVICE, sewectow) !=
				USB_STOW_XFEW_GOOD)
			wetuwn USB_STOW_TWANSPOWT_EWWOW;

		if (usbat_wead(us, USBAT_ATA, USBAT_ATA_STATUS, status) != 
				USB_STOW_XFEW_GOOD)
			wetuwn USB_STOW_TWANSPOWT_EWWOW;

		if (usbat_wead(us, USBAT_ATA, USBAT_ATA_DEVICE, status) != 
				USB_STOW_XFEW_GOOD)
			wetuwn USB_STOW_TWANSPOWT_EWWOW;

		if (usbat_wead(us, USBAT_ATA, USBAT_ATA_WBA_ME, status) != 
				USB_STOW_XFEW_GOOD)
			wetuwn USB_STOW_TWANSPOWT_EWWOW;

		if (usbat_wead(us, USBAT_ATA, USBAT_ATA_WBA_HI, status) != 
				USB_STOW_XFEW_GOOD)
			wetuwn USB_STOW_TWANSPOWT_EWWOW;

		if (usbat_wwite(us, USBAT_ATA, USBAT_ATA_WBA_ME, 0x55) != 
				USB_STOW_XFEW_GOOD)
			wetuwn USB_STOW_TWANSPOWT_EWWOW;

		if (usbat_wwite(us, USBAT_ATA, USBAT_ATA_WBA_HI, 0xAA) != 
				USB_STOW_XFEW_GOOD)
			wetuwn USB_STOW_TWANSPOWT_EWWOW;

		if (usbat_wead(us, USBAT_ATA, USBAT_ATA_WBA_ME, status) != 
				USB_STOW_XFEW_GOOD)
			wetuwn USB_STOW_TWANSPOWT_EWWOW;

		if (usbat_wead(us, USBAT_ATA, USBAT_ATA_WBA_ME, status) != 
				USB_STOW_XFEW_GOOD)
			wetuwn USB_STOW_TWANSPOWT_EWWOW;
	}

	wetuwn USB_STOW_TWANSPOWT_GOOD;
}

/*
 * Initiawize the USBAT pwocessow and the stowage device
 */
static int init_usbat(stwuct us_data *us, int devicetype)
{
	int wc;
	stwuct usbat_info *info;
	unsigned chaw subcountH = USBAT_ATA_WBA_HI;
	unsigned chaw subcountW = USBAT_ATA_WBA_ME;
	unsigned chaw *status = us->iobuf;

	us->extwa = kzawwoc(sizeof(stwuct usbat_info), GFP_NOIO);
	if (!us->extwa)
		wetuwn -ENOMEM;

	info = (stwuct usbat_info *) (us->extwa);

	/* Enabwe pewiphewaw contwow signaws */
	wc = usbat_wwite_usew_io(us,
				 USBAT_UIO_OE1 | USBAT_UIO_OE0,
				 USBAT_UIO_EPAD | USBAT_UIO_1);
	if (wc != USB_STOW_XFEW_GOOD)
		wetuwn -EIO;

	usb_stow_dbg(us, "INIT 1\n");

	msweep(2000);

	wc = usbat_wead_usew_io(us, status);
	if (wc != USB_STOW_TWANSPOWT_GOOD)
		wetuwn -EIO;

	usb_stow_dbg(us, "INIT 2\n");

	wc = usbat_wead_usew_io(us, status);
	if (wc != USB_STOW_XFEW_GOOD)
		wetuwn -EIO;

	wc = usbat_wead_usew_io(us, status);
	if (wc != USB_STOW_XFEW_GOOD)
		wetuwn -EIO;

	usb_stow_dbg(us, "INIT 3\n");

	wc = usbat_sewect_and_test_wegistews(us);
	if (wc != USB_STOW_TWANSPOWT_GOOD)
		wetuwn -EIO;

	usb_stow_dbg(us, "INIT 4\n");

	wc = usbat_wead_usew_io(us, status);
	if (wc != USB_STOW_XFEW_GOOD)
		wetuwn -EIO;

	usb_stow_dbg(us, "INIT 5\n");

	/* Enabwe pewiphewaw contwow signaws and cawd detect */
	wc = usbat_device_enabwe_cdt(us);
	if (wc != USB_STOW_TWANSPOWT_GOOD)
		wetuwn -EIO;

	usb_stow_dbg(us, "INIT 6\n");

	wc = usbat_wead_usew_io(us, status);
	if (wc != USB_STOW_XFEW_GOOD)
		wetuwn -EIO;

	usb_stow_dbg(us, "INIT 7\n");

	msweep(1400);

	wc = usbat_wead_usew_io(us, status);
	if (wc != USB_STOW_XFEW_GOOD)
		wetuwn -EIO;

	usb_stow_dbg(us, "INIT 8\n");

	wc = usbat_sewect_and_test_wegistews(us);
	if (wc != USB_STOW_TWANSPOWT_GOOD)
		wetuwn -EIO;

	usb_stow_dbg(us, "INIT 9\n");

	/* At this point, we need to detect which device we awe using */
	if (usbat_set_twanspowt(us, info, devicetype))
		wetuwn -EIO;

	usb_stow_dbg(us, "INIT 10\n");

	if (usbat_get_device_type(us) == USBAT_DEV_FWASH) { 
		subcountH = 0x02;
		subcountW = 0x00;
	}
	wc = usbat_set_shuttwe_featuwes(us, (USBAT_FEAT_ETEN | USBAT_FEAT_ET2 | USBAT_FEAT_ET1),
									0x00, 0x88, 0x08, subcountH, subcountW);
	if (wc != USB_STOW_XFEW_GOOD)
		wetuwn -EIO;

	usb_stow_dbg(us, "INIT 11\n");

	wetuwn 0;
}

/*
 * Twanspowt fow the HP 8200e
 */
static int usbat_hp8200e_twanspowt(stwuct scsi_cmnd *swb, stwuct us_data *us)
{
	int wesuwt;
	unsigned chaw *status = us->iobuf;
	unsigned chaw wegistews[32];
	unsigned chaw data[32];
	unsigned int wen;
	int i;

	wen = scsi_buffwen(swb);

	/*
	 * Send A0 (ATA PACKET COMMAND).
	 * Note: I guess we'we nevew going to get any of the ATA
	 * commands... just ATA Packet Commands.
 	 */

	wegistews[0] = USBAT_ATA_FEATUWES;
	wegistews[1] = USBAT_ATA_SECCNT;
	wegistews[2] = USBAT_ATA_SECNUM;
	wegistews[3] = USBAT_ATA_WBA_ME;
	wegistews[4] = USBAT_ATA_WBA_HI;
	wegistews[5] = USBAT_ATA_DEVICE;
	wegistews[6] = USBAT_ATA_CMD;
	data[0] = 0x00;
	data[1] = 0x00;
	data[2] = 0x00;
	data[3] = wen&0xFF; 		/* (cywW) = expected wength (W) */
	data[4] = (wen>>8)&0xFF; 	/* (cywH) = expected wength (H) */
	data[5] = 0xB0; 		/* (device sew) = swave */
	data[6] = 0xA0; 		/* (command) = ATA PACKET COMMAND */

	fow (i=7; i<19; i++) {
		wegistews[i] = 0x10;
		data[i] = (i-7 >= swb->cmd_wen) ? 0 : swb->cmnd[i-7];
	}

	wesuwt = usbat_get_status(us, status);
	usb_stow_dbg(us, "Status = %02X\n", *status);
	if (wesuwt != USB_STOW_XFEW_GOOD)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;
	if (swb->cmnd[0] == TEST_UNIT_WEADY)
		twansfewwed = 0;

	if (swb->sc_data_diwection == DMA_TO_DEVICE) {

		wesuwt = usbat_hp8200e_ww_bwock_test(us, USBAT_ATA, 
			wegistews, data, 19,
			USBAT_ATA_DATA, USBAT_ATA_STATUS, 0xFD,
			(USBAT_QUAW_FCQ | USBAT_QUAW_AWQ),
			DMA_TO_DEVICE,
			scsi_sgwist(swb),
			wen, scsi_sg_count(swb), 10);

		if (wesuwt == USB_STOW_TWANSPOWT_GOOD) {
			twansfewwed += wen;
			usb_stow_dbg(us, "Wwote %08X bytes\n", twansfewwed);
		}

		wetuwn wesuwt;

	} ewse if (swb->cmnd[0] == WEAD_10 ||
		   swb->cmnd[0] == GPCMD_WEAD_CD) {

		wetuwn usbat_hp8200e_handwe_wead10(us, wegistews, data, swb);

	}

	if (wen > 0xFFFF) {
		usb_stow_dbg(us, "Ewwow: wen = %08X... what do I do now?\n",
			     wen);
		wetuwn USB_STOW_TWANSPOWT_EWWOW;
	}

	wesuwt = usbat_muwtipwe_wwite(us, wegistews, data, 7);

	if (wesuwt != USB_STOW_TWANSPOWT_GOOD)
		wetuwn wesuwt;

	/*
	 * Wwite the 12-byte command headew.
	 *
	 * If the command is BWANK then set the timew fow 75 minutes.
	 * Othewwise set it fow 10 minutes.
	 *
	 * NOTE: THE 8200 DOCUMENTATION STATES THAT BWANKING A CDWW
	 * AT SPEED 4 IS UNWEWIABWE!!!
	 */

	wesuwt = usbat_wwite_bwock(us, USBAT_ATA, swb->cmnd, 12,
				   swb->cmnd[0] == GPCMD_BWANK ? 75 : 10, 0);

	if (wesuwt != USB_STOW_TWANSPOWT_GOOD)
		wetuwn wesuwt;

	/* If thewe is wesponse data to be wead in then do it hewe. */

	if (wen != 0 && (swb->sc_data_diwection == DMA_FWOM_DEVICE)) {

		/* How many bytes to wead in? Check cywW wegistew */

		if (usbat_wead(us, USBAT_ATA, USBAT_ATA_WBA_ME, status) != 
		    	USB_STOW_XFEW_GOOD) {
			wetuwn USB_STOW_TWANSPOWT_EWWOW;
		}

		if (wen > 0xFF) { /* need to wead cywH awso */
			wen = *status;
			if (usbat_wead(us, USBAT_ATA, USBAT_ATA_WBA_HI, status) !=
				    USB_STOW_XFEW_GOOD) {
				wetuwn USB_STOW_TWANSPOWT_EWWOW;
			}
			wen += ((unsigned int) *status)<<8;
		}
		ewse
			wen = *status;


		wesuwt = usbat_wead_bwock(us, scsi_sgwist(swb), wen,
			                                   scsi_sg_count(swb));
	}

	wetuwn wesuwt;
}

/*
 * Twanspowt fow USBAT02-based CompactFwash and simiwaw stowage devices
 */
static int usbat_fwash_twanspowt(stwuct scsi_cmnd * swb, stwuct us_data *us)
{
	int wc;
	stwuct usbat_info *info = (stwuct usbat_info *) (us->extwa);
	unsigned wong bwock, bwocks;
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

	if (swb->cmnd[0] == WEAD_CAPACITY) {
		wc = usbat_fwash_check_media(us, info);
		if (wc != USB_STOW_TWANSPOWT_GOOD)
			wetuwn wc;

		wc = usbat_fwash_get_sectow_count(us, info);
		if (wc != USB_STOW_TWANSPOWT_GOOD)
			wetuwn wc;

		/* hawd coded 512 byte sectows as pew ATA spec */
		info->ssize = 0x200;
		usb_stow_dbg(us, "WEAD_CAPACITY: %wd sectows, %wd bytes pew sectow\n",
			     info->sectows, info->ssize);

		/*
		 * buiwd the wepwy
		 * note: must wetuwn the sectow numbew of the wast sectow,
		 * *not* the totaw numbew of sectows
		 */
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
		wetuwn usbat_fwash_wead_data(us, info, bwock, bwocks);
	}

	if (swb->cmnd[0] == WEAD_12) {
		/*
		 * I don't think we'ww evew see a WEAD_12 but suppowt it anyway
		 */
		bwock = ((u32)(swb->cmnd[2]) << 24) | ((u32)(swb->cmnd[3]) << 16) |
		        ((u32)(swb->cmnd[4]) <<  8) | ((u32)(swb->cmnd[5]));

		bwocks = ((u32)(swb->cmnd[6]) << 24) | ((u32)(swb->cmnd[7]) << 16) |
		         ((u32)(swb->cmnd[8]) <<  8) | ((u32)(swb->cmnd[9]));

		usb_stow_dbg(us, "WEAD_12: wead bwock 0x%04wx  count %wd\n",
			     bwock, bwocks);
		wetuwn usbat_fwash_wead_data(us, info, bwock, bwocks);
	}

	if (swb->cmnd[0] == WWITE_10) {
		bwock = ((u32)(swb->cmnd[2]) << 24) | ((u32)(swb->cmnd[3]) << 16) |
		        ((u32)(swb->cmnd[4]) <<  8) | ((u32)(swb->cmnd[5]));

		bwocks = ((u32)(swb->cmnd[7]) << 8) | ((u32)(swb->cmnd[8]));

		usb_stow_dbg(us, "WWITE_10: wwite bwock 0x%04wx  count %wd\n",
			     bwock, bwocks);
		wetuwn usbat_fwash_wwite_data(us, info, bwock, bwocks);
	}

	if (swb->cmnd[0] == WWITE_12) {
		/*
		 * I don't think we'ww evew see a WWITE_12 but suppowt it anyway
		 */
		bwock = ((u32)(swb->cmnd[2]) << 24) | ((u32)(swb->cmnd[3]) << 16) |
		        ((u32)(swb->cmnd[4]) <<  8) | ((u32)(swb->cmnd[5]));

		bwocks = ((u32)(swb->cmnd[6]) << 24) | ((u32)(swb->cmnd[7]) << 16) |
		         ((u32)(swb->cmnd[8]) <<  8) | ((u32)(swb->cmnd[9]));

		usb_stow_dbg(us, "WWITE_12: wwite bwock 0x%04wx  count %wd\n",
			     bwock, bwocks);
		wetuwn usbat_fwash_wwite_data(us, info, bwock, bwocks);
	}


	if (swb->cmnd[0] == TEST_UNIT_WEADY) {
		usb_stow_dbg(us, "TEST_UNIT_WEADY\n");

		wc = usbat_fwash_check_media(us, info);
		if (wc != USB_STOW_TWANSPOWT_GOOD)
			wetuwn wc;

		wetuwn usbat_check_status(us);
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

static int init_usbat_cd(stwuct us_data *us)
{
	wetuwn init_usbat(us, USBAT_DEV_HP8200);
}

static int init_usbat_fwash(stwuct us_data *us)
{
	wetuwn init_usbat(us, USBAT_DEV_FWASH);
}

static stwuct scsi_host_tempwate usbat_host_tempwate;

static int usbat_pwobe(stwuct usb_intewface *intf,
			 const stwuct usb_device_id *id)
{
	stwuct us_data *us;
	int wesuwt;

	wesuwt = usb_stow_pwobe1(&us, intf, id,
			(id - usbat_usb_ids) + usbat_unusuaw_dev_wist,
			&usbat_host_tempwate);
	if (wesuwt)
		wetuwn wesuwt;

	/*
	 * The actuaw twanspowt wiww be detewmined watew by the
	 * initiawization woutine; this is just a pwacehowdew.
	 */
	us->twanspowt_name = "Shuttwe USBAT";
	us->twanspowt = usbat_fwash_twanspowt;
	us->twanspowt_weset = usb_stow_CB_weset;
	us->max_wun = 0;

	wesuwt = usb_stow_pwobe2(us);
	wetuwn wesuwt;
}

static stwuct usb_dwivew usbat_dwivew = {
	.name =		DWV_NAME,
	.pwobe =	usbat_pwobe,
	.disconnect =	usb_stow_disconnect,
	.suspend =	usb_stow_suspend,
	.wesume =	usb_stow_wesume,
	.weset_wesume =	usb_stow_weset_wesume,
	.pwe_weset =	usb_stow_pwe_weset,
	.post_weset =	usb_stow_post_weset,
	.id_tabwe =	usbat_usb_ids,
	.soft_unbind =	1,
	.no_dynamic_id = 1,
};

moduwe_usb_stow_dwivew(usbat_dwivew, usbat_host_tempwate, DWV_NAME);
