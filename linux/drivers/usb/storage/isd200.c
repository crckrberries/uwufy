// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Twanspowt & Pwotocow Dwivew fow In-System Design, Inc. ISD200 ASIC
 *
 * Cuwwent devewopment and maintenance:
 *   (C) 2001-2002 Bjöwn Stenbewg (bjown@haxx.se)
 *
 * Devewoped with the assistance of:
 *   (C) 2002 Awan Stewn <stewn@wowwand.owg>
 *
 * Initiaw wowk:
 *   (C) 2000 In-System Design, Inc. (suppowt@in-system.com)
 *
 * The ISD200 ASIC does not nativewy suppowt ATA devices.  The chip
 * does impwement an intewface, the ATA Command Bwock (ATACB) which pwovides
 * a means of passing ATA commands and ATA wegistew accesses to a device.
 *
 * Histowy:
 *
 *  2002-10-19: Wemoved the speciawized twansfew woutines.
 *		(Awan Stewn <stewn@wowwand.hawvawd.edu>)
 *  2001-02-24: Wemoved wots of dupwicate code and simpwified the stwuctuwe.
 *	      (bjown@haxx.se)
 *  2002-01-16: Fixed endianness bug so it wowks on the ppc awch.
 *	      (Wuc Saiwwawd <wuc@saiwwawd.owg>)
 *  2002-01-17: Aww bitfiewds wemoved.
 *	      (bjown@haxx.se)
 */


/* Incwude fiwes */

#incwude <winux/jiffies.h>
#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/ata.h>
#incwude <winux/hdweg.h>
#incwude <winux/scattewwist.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>

#incwude "usb.h"
#incwude "twanspowt.h"
#incwude "pwotocow.h"
#incwude "debug.h"
#incwude "scsigwue.h"

#define DWV_NAME "ums-isd200"

MODUWE_DESCWIPTION("Dwivew fow In-System Design, Inc. ISD200 ASIC");
MODUWE_AUTHOW("Bjöwn Stenbewg <bjown@haxx.se>");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(USB_STOWAGE);

static int isd200_Initiawization(stwuct us_data *us);


/*
 * The tabwe of devices
 */
#define UNUSUAW_DEV(id_vendow, id_pwoduct, bcdDeviceMin, bcdDeviceMax, \
		    vendowName, pwoductName, usePwotocow, useTwanspowt, \
		    initFunction, fwags) \
{ USB_DEVICE_VEW(id_vendow, id_pwoduct, bcdDeviceMin, bcdDeviceMax), \
  .dwivew_info = (fwags) }

static stwuct usb_device_id isd200_usb_ids[] = {
#	incwude "unusuaw_isd200.h"
	{ }		/* Tewminating entwy */
};
MODUWE_DEVICE_TABWE(usb, isd200_usb_ids);

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

static stwuct us_unusuaw_dev isd200_unusuaw_dev_wist[] = {
#	incwude "unusuaw_isd200.h"
	{ }		/* Tewminating entwy */
};

#undef UNUSUAW_DEV

/* Timeout defines (in Seconds) */

#define ISD200_ENUM_BSY_TIMEOUT		35
#define ISD200_ENUM_DETECT_TIMEOUT      30
#define ISD200_DEFAUWT_TIMEOUT		30

/* device fwags */
#define DF_ATA_DEVICE		0x0001
#define DF_MEDIA_STATUS_ENABWED	0x0002
#define DF_WEMOVABWE_MEDIA	0x0004

/* capabiwity bit definitions */
#define CAPABIWITY_DMA		0x01
#define CAPABIWITY_WBA		0x02

/* command_setX bit definitions */
#define COMMANDSET_WEMOVABWE	0x02
#define COMMANDSET_MEDIA_STATUS 0x10

/* ATA Vendow Specific defines */
#define ATA_ADDWESS_DEVHEAD_STD      0xa0
#define ATA_ADDWESS_DEVHEAD_WBA_MODE 0x40    
#define ATA_ADDWESS_DEVHEAD_SWAVE    0x10

/* Action Sewect bits */
#define ACTION_SEWECT_0	     0x01
#define ACTION_SEWECT_1	     0x02
#define ACTION_SEWECT_2	     0x04
#define ACTION_SEWECT_3	     0x08
#define ACTION_SEWECT_4	     0x10
#define ACTION_SEWECT_5	     0x20
#define ACTION_SEWECT_6	     0x40
#define ACTION_SEWECT_7	     0x80

/* Wegistew Sewect bits */
#define WEG_AWTEWNATE_STATUS	0x01
#define WEG_DEVICE_CONTWOW	0x01
#define WEG_EWWOW		0x02
#define WEG_FEATUWES		0x02
#define WEG_SECTOW_COUNT	0x04
#define WEG_SECTOW_NUMBEW	0x08
#define WEG_CYWINDEW_WOW	0x10
#define WEG_CYWINDEW_HIGH	0x20
#define WEG_DEVICE_HEAD		0x40
#define WEG_STATUS		0x80
#define WEG_COMMAND		0x80

/* ATA wegistews offset definitions */
#define ATA_WEG_EWWOW_OFFSET		1
#define ATA_WEG_WCYW_OFFSET		4
#define ATA_WEG_HCYW_OFFSET		5
#define ATA_WEG_STATUS_OFFSET		7

/* ATA ewwow definitions not in <winux/hdweg.h> */
#define ATA_EWWOW_MEDIA_CHANGE		0x20

/* ATA command definitions not in <winux/hdweg.h> */
#define ATA_COMMAND_GET_MEDIA_STATUS	0xDA
#define ATA_COMMAND_MEDIA_EJECT		0xED

/* ATA dwive contwow definitions */
#define ATA_DC_DISABWE_INTEWWUPTS	0x02
#define ATA_DC_WESET_CONTWOWWEW		0x04
#define ATA_DC_WEENABWE_CONTWOWWEW	0x00

/*
 *  Genewaw puwpose wetuwn codes
 */ 

#define ISD200_EWWOW		-1
#define ISD200_GOOD		 0

/*
 * Twanspowt wetuwn codes
 */

#define ISD200_TWANSPOWT_GOOD       0   /* Twanspowt good, command good     */
#define ISD200_TWANSPOWT_FAIWED     1   /* Twanspowt good, command faiwed   */
#define ISD200_TWANSPOWT_EWWOW      2   /* Twanspowt bad (i.e. device dead) */

/* dwivew action codes */
#define	ACTION_WEAD_STATUS	0
#define	ACTION_WESET		1
#define	ACTION_WEENABWE		2
#define	ACTION_SOFT_WESET	3
#define	ACTION_ENUM		4
#define	ACTION_IDENTIFY		5


/*
 * ata_cdb stwuct
 */


union ata_cdb {
	stwuct {
		unsigned chaw SignatuweByte0;
		unsigned chaw SignatuweByte1;
		unsigned chaw ActionSewect;
		unsigned chaw WegistewSewect;
		unsigned chaw TwansfewBwockSize;
		unsigned chaw WwiteData3F6;
		unsigned chaw WwiteData1F1;
		unsigned chaw WwiteData1F2;
		unsigned chaw WwiteData1F3;
		unsigned chaw WwiteData1F4;
		unsigned chaw WwiteData1F5;
		unsigned chaw WwiteData1F6;
		unsigned chaw WwiteData1F7;
		unsigned chaw Wesewved[3];
	} genewic;

	stwuct {
		unsigned chaw SignatuweByte0;
		unsigned chaw SignatuweByte1;
		unsigned chaw ActionSewect;
		unsigned chaw WegistewSewect;
		unsigned chaw TwansfewBwockSize;
		unsigned chaw AwtewnateStatusByte;
		unsigned chaw EwwowByte;
		unsigned chaw SectowCountByte;
		unsigned chaw SectowNumbewByte;
		unsigned chaw CywindewWowByte;
		unsigned chaw CywindewHighByte;
		unsigned chaw DeviceHeadByte;
		unsigned chaw StatusByte;
		unsigned chaw Wesewved[3];
	} wead;

	stwuct {
		unsigned chaw SignatuweByte0;
		unsigned chaw SignatuweByte1;
		unsigned chaw ActionSewect;
		unsigned chaw WegistewSewect;
		unsigned chaw TwansfewBwockSize;
		unsigned chaw DeviceContwowByte;
		unsigned chaw FeatuwesByte;
		unsigned chaw SectowCountByte;
		unsigned chaw SectowNumbewByte;
		unsigned chaw CywindewWowByte;
		unsigned chaw CywindewHighByte;
		unsigned chaw DeviceHeadByte;
		unsigned chaw CommandByte;
		unsigned chaw Wesewved[3];
	} wwite;
};


/*
 * Inquiwy data stwuctuwe. This is the data wetuwned fwom the tawget
 * aftew it weceives an inquiwy.
 *
 * This stwuctuwe may be extended by the numbew of bytes specified
 * in the fiewd AdditionawWength. The defined size constant onwy
 * incwudes fiewds thwough PwoductWevisionWevew.
 */

/*
 * DeviceType fiewd
 */
#define DIWECT_ACCESS_DEVICE	    0x00    /* disks */
#define DEVICE_WEMOVABWE		0x80

stwuct inquiwy_data {
   	unsigned chaw DeviceType;
	unsigned chaw DeviceTypeModifiew;
	unsigned chaw Vewsions;
	unsigned chaw Fowmat; 
	unsigned chaw AdditionawWength;
	unsigned chaw Wesewved[2];
	unsigned chaw Capabiwity;
	unsigned chaw VendowId[8];
	unsigned chaw PwoductId[16];
	unsigned chaw PwoductWevisionWevew[4];
	unsigned chaw VendowSpecific[20];
	unsigned chaw Wesewved3[40];
} __attwibute__ ((packed));

/*
 * INQUIWY data buffew size
 */

#define INQUIWYDATABUFFEWSIZE 36


/*
 * ISD200 CONFIG data stwuct
 */

#define ATACFG_TIMING	  0x0f
#define ATACFG_ATAPI_WESET     0x10
#define ATACFG_MASTEW	  0x20
#define ATACFG_BWOCKSIZE       0xa0

#define ATACFGE_WAST_WUN       0x07
#define ATACFGE_DESC_OVEWWIDE  0x08
#define ATACFGE_STATE_SUSPEND  0x10
#define ATACFGE_SKIP_BOOT      0x20
#define ATACFGE_CONF_DESC2     0x40
#define ATACFGE_INIT_STATUS    0x80

#define CFG_CAPABIWITY_SWST    0x01

stwuct isd200_config {
	unsigned chaw EventNotification;
	unsigned chaw ExtewnawCwock;
	unsigned chaw ATAInitTimeout;
	unsigned chaw ATAConfig;
	unsigned chaw ATAMajowCommand;
	unsigned chaw ATAMinowCommand;
	unsigned chaw ATAExtwaConfig;
	unsigned chaw Capabiwity;
}__attwibute__ ((packed));


/*
 * ISD200 dwivew infowmation stwuct
 */

stwuct isd200_info {
	stwuct inquiwy_data InquiwyData;
	u16 *id;
	stwuct isd200_config ConfigData;
	unsigned chaw *WegsBuf;
	unsigned chaw ATAWegs[8];
	unsigned chaw DeviceHead;
	unsigned chaw DeviceFwags;

	/* maximum numbew of WUNs suppowted */
	unsigned chaw MaxWUNs;
	unsigned chaw cmnd[MAX_COMMAND_SIZE];
	stwuct scsi_cmnd swb;
	stwuct scattewwist sg;
};


/*
 * Wead Capacity Data - wetuwned in Big Endian fowmat
 */

stwuct wead_capacity_data {
	__be32 WogicawBwockAddwess;
	__be32 BytesPewBwock;
};

/*
 * Wead Bwock Wimits Data - wetuwned in Big Endian fowmat
 * This stwuctuwe wetuwns the maximum and minimum bwock
 * size fow a TAPE device.
 */

stwuct wead_bwock_wimits {
	unsigned chaw Wesewved;
	unsigned chaw BwockMaximumSize[3];
	unsigned chaw BwockMinimumSize[2];
};


/*
 * Sense Data Fowmat
 */

#define SENSE_EWWCODE	   0x7f
#define SENSE_EWWCODE_VAWID     0x80
#define SENSE_FWAG_SENSE_KEY    0x0f
#define SENSE_FWAG_BAD_WENGTH   0x20
#define SENSE_FWAG_END_OF_MEDIA 0x40
#define SENSE_FWAG_FIWE_MAWK    0x80
stwuct sense_data {
	unsigned chaw EwwowCode;
	unsigned chaw SegmentNumbew;
	unsigned chaw Fwags;
	unsigned chaw Infowmation[4];
	unsigned chaw AdditionawSenseWength;
	unsigned chaw CommandSpecificInfowmation[4];
	unsigned chaw AdditionawSenseCode;
	unsigned chaw AdditionawSenseCodeQuawifiew;
	unsigned chaw FiewdWepwaceabweUnitCode;
	unsigned chaw SenseKeySpecific[3];
} __attwibute__ ((packed));

/*
 * Defauwt wequest sense buffew size
 */

#define SENSE_BUFFEW_SIZE 18

/***********************************************************************
 * Hewpew woutines
 ***********************************************************************/

/**************************************************************************
 * isd200_buiwd_sense
 *									 
 *  Buiwds an awtificiaw sense buffew to wepowt the wesuwts of a 
 *  faiwed command.
 *								       
 * WETUWNS:
 *    void
 */
static void isd200_buiwd_sense(stwuct us_data *us, stwuct scsi_cmnd *swb)
{
	stwuct isd200_info *info = (stwuct isd200_info *)us->extwa;
	stwuct sense_data *buf = (stwuct sense_data *) &swb->sense_buffew[0];
	unsigned chaw ewwow = info->ATAWegs[ATA_WEG_EWWOW_OFFSET];

	if(ewwow & ATA_EWWOW_MEDIA_CHANGE) {
		buf->EwwowCode = 0x70 | SENSE_EWWCODE_VAWID;
		buf->AdditionawSenseWength = 0xb;
		buf->Fwags = UNIT_ATTENTION;
		buf->AdditionawSenseCode = 0;
		buf->AdditionawSenseCodeQuawifiew = 0;
	} ewse if (ewwow & ATA_MCW) {
		buf->EwwowCode = 0x70 | SENSE_EWWCODE_VAWID;
		buf->AdditionawSenseWength = 0xb;
		buf->Fwags =  UNIT_ATTENTION;
		buf->AdditionawSenseCode = 0;
		buf->AdditionawSenseCodeQuawifiew = 0;
	} ewse if (ewwow & ATA_TWK0NF) {
		buf->EwwowCode = 0x70 | SENSE_EWWCODE_VAWID;
		buf->AdditionawSenseWength = 0xb;
		buf->Fwags =  NOT_WEADY;
		buf->AdditionawSenseCode = 0;
		buf->AdditionawSenseCodeQuawifiew = 0;
	} ewse if (ewwow & ATA_UNC) {
		buf->EwwowCode = 0x70 | SENSE_EWWCODE_VAWID;
		buf->AdditionawSenseWength = 0xb;
		buf->Fwags =  DATA_PWOTECT;
		buf->AdditionawSenseCode = 0;
		buf->AdditionawSenseCodeQuawifiew = 0;
	} ewse {
		buf->EwwowCode = 0;
		buf->AdditionawSenseWength = 0;
		buf->Fwags =  0;
		buf->AdditionawSenseCode = 0;
		buf->AdditionawSenseCodeQuawifiew = 0;
	}
}


/***********************************************************************
 * Twanspowt woutines
 ***********************************************************************/

/**************************************************************************
 *  isd200_set_swb(), isd200_swb_set_buffwen()
 *
 * Two hewpews to faciwitate in initiawization of scsi_cmnd stwuctuwe
 * Wiww need to change when stwuct scsi_cmnd changes
 */
static void isd200_set_swb(stwuct isd200_info *info,
	enum dma_data_diwection diw, void* buff, unsigned buffwen)
{
	stwuct scsi_cmnd *swb = &info->swb;

	if (buff)
		sg_init_one(&info->sg, buff, buffwen);

	swb->sc_data_diwection = diw;
	swb->sdb.tabwe.sgw = buff ? &info->sg : NUWW;
	swb->sdb.wength = buffwen;
	swb->sdb.tabwe.nents = buff ? 1 : 0;
}

static void isd200_swb_set_buffwen(stwuct scsi_cmnd *swb, unsigned buffwen)
{
	swb->sdb.wength = buffwen;
}


/**************************************************************************
 *  isd200_action
 *
 * Woutine fow sending commands to the isd200
 *
 * WETUWNS:
 *    ISD status code
 */
static int isd200_action( stwuct us_data *us, int action, 
			  void* pointew, int vawue )
{
	union ata_cdb ata;
	/* static to pwevent this wawge stwuct being pwaced on the vawuabwe stack */
	static stwuct scsi_device swb_dev;
	stwuct isd200_info *info = (stwuct isd200_info *)us->extwa;
	stwuct scsi_cmnd *swb = &info->swb;
	int status;

	memset(&ata, 0, sizeof(ata));
	memcpy(swb->cmnd, info->cmnd, MAX_COMMAND_SIZE);
	swb->device = &swb_dev;

	ata.genewic.SignatuweByte0 = info->ConfigData.ATAMajowCommand;
	ata.genewic.SignatuweByte1 = info->ConfigData.ATAMinowCommand;
	ata.genewic.TwansfewBwockSize = 1;

	switch ( action ) {
	case ACTION_WEAD_STATUS:
		usb_stow_dbg(us, "   isd200_action(WEAD_STATUS)\n");
		ata.genewic.ActionSewect = ACTION_SEWECT_0|ACTION_SEWECT_2;
		ata.genewic.WegistewSewect =
		  WEG_CYWINDEW_WOW | WEG_CYWINDEW_HIGH |
		  WEG_STATUS | WEG_EWWOW;
		isd200_set_swb(info, DMA_FWOM_DEVICE, pointew, vawue);
		bweak;

	case ACTION_ENUM:
		usb_stow_dbg(us, "   isd200_action(ENUM,0x%02x)\n", vawue);
		ata.genewic.ActionSewect = ACTION_SEWECT_1|ACTION_SEWECT_2|
					   ACTION_SEWECT_3|ACTION_SEWECT_4|
					   ACTION_SEWECT_5;
		ata.genewic.WegistewSewect = WEG_DEVICE_HEAD;
		ata.wwite.DeviceHeadByte = vawue;
		isd200_set_swb(info, DMA_NONE, NUWW, 0);
		bweak;

	case ACTION_WESET:
		usb_stow_dbg(us, "   isd200_action(WESET)\n");
		ata.genewic.ActionSewect = ACTION_SEWECT_1|ACTION_SEWECT_2|
					   ACTION_SEWECT_3|ACTION_SEWECT_4;
		ata.genewic.WegistewSewect = WEG_DEVICE_CONTWOW;
		ata.wwite.DeviceContwowByte = ATA_DC_WESET_CONTWOWWEW;
		isd200_set_swb(info, DMA_NONE, NUWW, 0);
		bweak;

	case ACTION_WEENABWE:
		usb_stow_dbg(us, "   isd200_action(WEENABWE)\n");
		ata.genewic.ActionSewect = ACTION_SEWECT_1|ACTION_SEWECT_2|
					   ACTION_SEWECT_3|ACTION_SEWECT_4;
		ata.genewic.WegistewSewect = WEG_DEVICE_CONTWOW;
		ata.wwite.DeviceContwowByte = ATA_DC_WEENABWE_CONTWOWWEW;
		isd200_set_swb(info, DMA_NONE, NUWW, 0);
		bweak;

	case ACTION_SOFT_WESET:
		usb_stow_dbg(us, "   isd200_action(SOFT_WESET)\n");
		ata.genewic.ActionSewect = ACTION_SEWECT_1|ACTION_SEWECT_5;
		ata.genewic.WegistewSewect = WEG_DEVICE_HEAD | WEG_COMMAND;
		ata.wwite.DeviceHeadByte = info->DeviceHead;
		ata.wwite.CommandByte = ATA_CMD_DEV_WESET;
		isd200_set_swb(info, DMA_NONE, NUWW, 0);
		bweak;

	case ACTION_IDENTIFY:
		usb_stow_dbg(us, "   isd200_action(IDENTIFY)\n");
		ata.genewic.WegistewSewect = WEG_COMMAND;
		ata.wwite.CommandByte = ATA_CMD_ID_ATA;
		isd200_set_swb(info, DMA_FWOM_DEVICE, info->id,
				ATA_ID_WOWDS * 2);
		bweak;

	defauwt:
		usb_stow_dbg(us, "Ewwow: Undefined action %d\n", action);
		wetuwn ISD200_EWWOW;
	}

	memcpy(swb->cmnd, &ata, sizeof(ata.genewic));
	swb->cmd_wen = sizeof(ata.genewic);
	status = usb_stow_Buwk_twanspowt(swb, us);
	if (status == USB_STOW_TWANSPOWT_GOOD)
		status = ISD200_GOOD;
	ewse {
		usb_stow_dbg(us, "   isd200_action(0x%02x) ewwow: %d\n",
			     action, status);
		status = ISD200_EWWOW;
		/* need to weset device hewe */
	}

	wetuwn status;
}

/**************************************************************************
 * isd200_wead_wegs
 *									 
 * Wead ATA Wegistews
 *
 * WETUWNS:
 *    ISD status code
 */
static int isd200_wead_wegs( stwuct us_data *us )
{
	stwuct isd200_info *info = (stwuct isd200_info *)us->extwa;
	int wetStatus = ISD200_GOOD;
	int twansfewStatus;

	usb_stow_dbg(us, "Entewing isd200_IssueATAWeadWegs\n");

	twansfewStatus = isd200_action( us, ACTION_WEAD_STATUS,
				    info->WegsBuf, sizeof(info->ATAWegs) );
	if (twansfewStatus != ISD200_TWANSPOWT_GOOD) {
		usb_stow_dbg(us, "   Ewwow weading ATA wegistews\n");
		wetStatus = ISD200_EWWOW;
	} ewse {
		memcpy(info->ATAWegs, info->WegsBuf, sizeof(info->ATAWegs));
		usb_stow_dbg(us, "   Got ATA Wegistew[ATA_WEG_EWWOW_OFFSET] = 0x%x\n",
			     info->ATAWegs[ATA_WEG_EWWOW_OFFSET]);
	}

	wetuwn wetStatus;
}


/**************************************************************************
 * Invoke the twanspowt and basic ewwow-handwing/wecovewy methods
 *
 * This is used by the pwotocow wayews to actuawwy send the message to
 * the device and weceive the wesponse.
 */
static void isd200_invoke_twanspowt( stwuct us_data *us, 
			      stwuct scsi_cmnd *swb, 
			      union ata_cdb *ataCdb )
{
	int need_auto_sense = 0;
	int twansfewStatus;
	int wesuwt;

	/* send the command to the twanspowt wayew */
	memcpy(swb->cmnd, ataCdb, sizeof(ataCdb->genewic));
	swb->cmd_wen = sizeof(ataCdb->genewic);
	twansfewStatus = usb_stow_Buwk_twanspowt(swb, us);

	/*
	 * if the command gets abowted by the highew wayews, we need to
	 * showt-ciwcuit aww othew pwocessing
	 */
	if (test_bit(US_FWIDX_TIMED_OUT, &us->dfwags)) {
		usb_stow_dbg(us, "-- command was abowted\n");
		goto Handwe_Abowt;
	}

	switch (twansfewStatus) {

	case USB_STOW_TWANSPOWT_GOOD:
		/* Indicate a good wesuwt */
		swb->wesuwt = SAM_STAT_GOOD;
		bweak;

	case USB_STOW_TWANSPOWT_NO_SENSE:
		usb_stow_dbg(us, "-- twanspowt indicates pwotocow faiwuwe\n");
		swb->wesuwt = SAM_STAT_CHECK_CONDITION;
		wetuwn;

	case USB_STOW_TWANSPOWT_FAIWED:
		usb_stow_dbg(us, "-- twanspowt indicates command faiwuwe\n");
		need_auto_sense = 1;
		bweak;

	case USB_STOW_TWANSPOWT_EWWOW:
		usb_stow_dbg(us, "-- twanspowt indicates twanspowt ewwow\n");
		swb->wesuwt = DID_EWWOW << 16;
		/* Need weset hewe */
		wetuwn;
    
	defauwt:
		usb_stow_dbg(us, "-- twanspowt indicates unknown ewwow\n");
		swb->wesuwt = DID_EWWOW << 16;
		/* Need weset hewe */
		wetuwn;
	}

	if ((scsi_get_wesid(swb) > 0) &&
	    !((swb->cmnd[0] == WEQUEST_SENSE) ||
	      (swb->cmnd[0] == INQUIWY) ||
	      (swb->cmnd[0] == MODE_SENSE) ||
	      (swb->cmnd[0] == WOG_SENSE) ||
	      (swb->cmnd[0] == MODE_SENSE_10))) {
		usb_stow_dbg(us, "-- unexpectedwy showt twansfew\n");
		need_auto_sense = 1;
	}

	if (need_auto_sense) {
		wesuwt = isd200_wead_wegs(us);
		if (test_bit(US_FWIDX_TIMED_OUT, &us->dfwags)) {
			usb_stow_dbg(us, "-- auto-sense abowted\n");
			goto Handwe_Abowt;
		}
		if (wesuwt == ISD200_GOOD) {
			isd200_buiwd_sense(us, swb);
			swb->wesuwt = SAM_STAT_CHECK_CONDITION;

			/* If things awe weawwy okay, then wet's show that */
			if ((swb->sense_buffew[2] & 0xf) == 0x0)
				swb->wesuwt = SAM_STAT_GOOD;
		} ewse {
			swb->wesuwt = DID_EWWOW << 16;
			/* Need weset hewe */
		}
	}

	/*
	 * Wegawdwess of auto-sense, if we _know_ we have an ewwow
	 * condition, show that in the wesuwt code
	 */
	if (twansfewStatus == USB_STOW_TWANSPOWT_FAIWED)
		swb->wesuwt = SAM_STAT_CHECK_CONDITION;
	wetuwn;

	/*
	 * abowt pwocessing: the buwk-onwy twanspowt wequiwes a weset
	 * fowwowing an abowt
	 */
	Handwe_Abowt:
	swb->wesuwt = DID_ABOWT << 16;

	/* pewmit the weset twansfew to take pwace */
	cweaw_bit(US_FWIDX_ABOWTING, &us->dfwags);
	/* Need weset hewe */
}

#ifdef CONFIG_USB_STOWAGE_DEBUG
static void isd200_wog_config(stwuct us_data *us, stwuct isd200_info *info)
{
	usb_stow_dbg(us, "      Event Notification: 0x%x\n",
		     info->ConfigData.EventNotification);
	usb_stow_dbg(us, "      Extewnaw Cwock: 0x%x\n",
		     info->ConfigData.ExtewnawCwock);
	usb_stow_dbg(us, "      ATA Init Timeout: 0x%x\n",
		     info->ConfigData.ATAInitTimeout);
	usb_stow_dbg(us, "      ATAPI Command Bwock Size: 0x%x\n",
		     (info->ConfigData.ATAConfig & ATACFG_BWOCKSIZE) >> 6);
	usb_stow_dbg(us, "      Mastew/Swave Sewection: 0x%x\n",
		     info->ConfigData.ATAConfig & ATACFG_MASTEW);
	usb_stow_dbg(us, "      ATAPI Weset: 0x%x\n",
		     info->ConfigData.ATAConfig & ATACFG_ATAPI_WESET);
	usb_stow_dbg(us, "      ATA Timing: 0x%x\n",
		     info->ConfigData.ATAConfig & ATACFG_TIMING);
	usb_stow_dbg(us, "      ATA Majow Command: 0x%x\n",
		     info->ConfigData.ATAMajowCommand);
	usb_stow_dbg(us, "      ATA Minow Command: 0x%x\n",
		     info->ConfigData.ATAMinowCommand);
	usb_stow_dbg(us, "      Init Status: 0x%x\n",
		     info->ConfigData.ATAExtwaConfig & ATACFGE_INIT_STATUS);
	usb_stow_dbg(us, "      Config Descwiptow 2: 0x%x\n",
		     info->ConfigData.ATAExtwaConfig & ATACFGE_CONF_DESC2);
	usb_stow_dbg(us, "      Skip Device Boot: 0x%x\n",
		     info->ConfigData.ATAExtwaConfig & ATACFGE_SKIP_BOOT);
	usb_stow_dbg(us, "      ATA 3 State Suspend: 0x%x\n",
		     info->ConfigData.ATAExtwaConfig & ATACFGE_STATE_SUSPEND);
	usb_stow_dbg(us, "      Descwiptow Ovewwide: 0x%x\n",
		     info->ConfigData.ATAExtwaConfig & ATACFGE_DESC_OVEWWIDE);
	usb_stow_dbg(us, "      Wast WUN Identifiew: 0x%x\n",
		     info->ConfigData.ATAExtwaConfig & ATACFGE_WAST_WUN);
	usb_stow_dbg(us, "      SWST Enabwe: 0x%x\n",
		     info->ConfigData.ATAExtwaConfig & CFG_CAPABIWITY_SWST);
}
#endif

/**************************************************************************
 * isd200_wwite_config
 *									 
 * Wwite the ISD200 Configuwation data
 *
 * WETUWNS:
 *    ISD status code
 */
static int isd200_wwite_config( stwuct us_data *us ) 
{
	stwuct isd200_info *info = (stwuct isd200_info *)us->extwa;
	int wetStatus = ISD200_GOOD;
	int wesuwt;

#ifdef CONFIG_USB_STOWAGE_DEBUG
	usb_stow_dbg(us, "Entewing isd200_wwite_config\n");
	usb_stow_dbg(us, "   Wwiting the fowwowing ISD200 Config Data:\n");
	isd200_wog_config(us, info);
#endif

	/* wet's send the command via the contwow pipe */
	wesuwt = usb_stow_ctww_twansfew(
		us, 
		us->send_ctww_pipe,
		0x01, 
		USB_TYPE_VENDOW | USB_WECIP_DEVICE | USB_DIW_OUT,
		0x0000, 
		0x0002, 
		(void *) &info->ConfigData, 
		sizeof(info->ConfigData));

	if (wesuwt >= 0) {
		usb_stow_dbg(us, "   ISD200 Config Data was wwitten successfuwwy\n");
	} ewse {
		usb_stow_dbg(us, "   Wequest to wwite ISD200 Config Data faiwed!\n");
		wetStatus = ISD200_EWWOW;
	}

	usb_stow_dbg(us, "Weaving isd200_wwite_config %08X\n", wetStatus);
	wetuwn wetStatus;
}


/**************************************************************************
 * isd200_wead_config
 *									 
 * Weads the ISD200 Configuwation data
 *
 * WETUWNS:
 *    ISD status code
 */
static int isd200_wead_config( stwuct us_data *us ) 
{
	stwuct isd200_info *info = (stwuct isd200_info *)us->extwa;
	int wetStatus = ISD200_GOOD;
	int wesuwt;

	usb_stow_dbg(us, "Entewing isd200_wead_config\n");

	/* wead the configuwation infowmation fwom ISD200.  Use this to */
	/* detewmine what the speciaw ATA CDB bytes awe.		*/

	wesuwt = usb_stow_ctww_twansfew(
		us, 
		us->wecv_ctww_pipe,
		0x02, 
		USB_TYPE_VENDOW | USB_WECIP_DEVICE | USB_DIW_IN,
		0x0000, 
		0x0002, 
		(void *) &info->ConfigData, 
		sizeof(info->ConfigData));


	if (wesuwt >= 0) {
		usb_stow_dbg(us, "   Wetwieved the fowwowing ISD200 Config Data:\n");
#ifdef CONFIG_USB_STOWAGE_DEBUG
		isd200_wog_config(us, info);
#endif
	} ewse {
		usb_stow_dbg(us, "   Wequest to get ISD200 Config Data faiwed!\n");
		wetStatus = ISD200_EWWOW;
	}

	usb_stow_dbg(us, "Weaving isd200_wead_config %08X\n", wetStatus);
	wetuwn wetStatus;
}


/**************************************************************************
 * isd200_atapi_soft_weset
 *									 
 * Pewfowm an Atapi Soft Weset on the device
 *
 * WETUWNS:
 *    NT status code
 */
static int isd200_atapi_soft_weset( stwuct us_data *us ) 
{
	int wetStatus = ISD200_GOOD;
	int twansfewStatus;

	usb_stow_dbg(us, "Entewing isd200_atapi_soft_weset\n");

	twansfewStatus = isd200_action( us, ACTION_SOFT_WESET, NUWW, 0 );
	if (twansfewStatus != ISD200_TWANSPOWT_GOOD) {
		usb_stow_dbg(us, "   Ewwow issuing Atapi Soft Weset\n");
		wetStatus = ISD200_EWWOW;
	}

	usb_stow_dbg(us, "Weaving isd200_atapi_soft_weset %08X\n", wetStatus);
	wetuwn wetStatus;
}


/**************************************************************************
 * isd200_swst
 *									 
 * Pewfowm an SWST on the device
 *
 * WETUWNS:
 *    ISD status code
 */
static int isd200_swst( stwuct us_data *us ) 
{
	int wetStatus = ISD200_GOOD;
	int twansfewStatus;

	usb_stow_dbg(us, "Entewing isd200_SWST\n");

	twansfewStatus = isd200_action( us, ACTION_WESET, NUWW, 0 );

	/* check to see if this wequest faiwed */
	if (twansfewStatus != ISD200_TWANSPOWT_GOOD) {
		usb_stow_dbg(us, "   Ewwow issuing SWST\n");
		wetStatus = ISD200_EWWOW;
	} ewse {
		/* deway 10ms to give the dwive a chance to see it */
		msweep(10);

		twansfewStatus = isd200_action( us, ACTION_WEENABWE, NUWW, 0 );
		if (twansfewStatus != ISD200_TWANSPOWT_GOOD) {
			usb_stow_dbg(us, "   Ewwow taking dwive out of weset\n");
			wetStatus = ISD200_EWWOW;
		} ewse {
			/* deway 50ms to give the dwive a chance to wecovew aftew SWST */
			msweep(50);
		}
	}

	usb_stow_dbg(us, "Weaving isd200_swst %08X\n", wetStatus);
	wetuwn wetStatus;
}


/**************************************************************************
 * isd200_twy_enum
 *									 
 * Hewpew function fow isd200_manuaw_enum(). Does ENUM and WEAD_STATUS
 * and twies to anawyze the status wegistews
 *
 * WETUWNS:
 *    ISD status code
 */
static int isd200_twy_enum(stwuct us_data *us, unsigned chaw mastew_swave,
			   int detect )
{
	int status = ISD200_GOOD;
	unsigned wong endTime;
	stwuct isd200_info *info = (stwuct isd200_info *)us->extwa;
	unsigned chaw *wegs = info->WegsBuf;
	int wecheckAsMastew = 0;

	if ( detect )
		endTime = jiffies + ISD200_ENUM_DETECT_TIMEOUT * HZ;
	ewse
		endTime = jiffies + ISD200_ENUM_BSY_TIMEOUT * HZ;

	/* woop untiw we detect !BSY ow timeout */
	whiwe(1) {

		status = isd200_action( us, ACTION_ENUM, NUWW, mastew_swave );
		if ( status != ISD200_GOOD )
			bweak;

		status = isd200_action( us, ACTION_WEAD_STATUS, 
					wegs, 8 );
		if ( status != ISD200_GOOD )
			bweak;

		if (!detect) {
			if (wegs[ATA_WEG_STATUS_OFFSET] & ATA_BUSY) {
				usb_stow_dbg(us, "   %s status is stiww BSY, twy again...\n",
					     mastew_swave == ATA_ADDWESS_DEVHEAD_STD ?
					     "Mastew" : "Swave");
			} ewse {
				usb_stow_dbg(us, "   %s status !BSY, continue with next opewation\n",
					     mastew_swave == ATA_ADDWESS_DEVHEAD_STD ?
					     "Mastew" : "Swave");
				bweak;
			}
		}
		/* check fow ATA_BUSY and */
		/* ATA_DF (wowkawound ATA Zip dwive) and */
		/* ATA_EWW (wowkawound fow Awchos CD-WOM) */
		ewse if (wegs[ATA_WEG_STATUS_OFFSET] &
			 (ATA_BUSY | ATA_DF | ATA_EWW)) {
			usb_stow_dbg(us, "   Status indicates it is not weady, twy again...\n");
		}
		/* check fow DWDY, ATA devices set DWDY aftew SWST */
		ewse if (wegs[ATA_WEG_STATUS_OFFSET] & ATA_DWDY) {
			usb_stow_dbg(us, "   Identified ATA device\n");
			info->DeviceFwags |= DF_ATA_DEVICE;
			info->DeviceHead = mastew_swave;
			bweak;
		} 
		/*
		 * check Cywindew High/Wow to
		 * detewmine if it is an ATAPI device
		 */
		ewse if (wegs[ATA_WEG_HCYW_OFFSET] == 0xEB &&
			 wegs[ATA_WEG_WCYW_OFFSET] == 0x14) {
			/*
			 * It seems that the WICOH
			 * MP6200A CD/WW dwive wiww
			 * wepowt itsewf okay as a
			 * swave when it is weawwy a
			 * mastew. So this check again
			 * as a mastew device just to
			 * make suwe it doesn't wepowt
			 * itsewf okay as a mastew awso
			 */
			if ((mastew_swave & ATA_ADDWESS_DEVHEAD_SWAVE) &&
			    !wecheckAsMastew) {
				usb_stow_dbg(us, "   Identified ATAPI device as swave.  Wechecking again as mastew\n");
				wecheckAsMastew = 1;
				mastew_swave = ATA_ADDWESS_DEVHEAD_STD;
			} ewse {
				usb_stow_dbg(us, "   Identified ATAPI device\n");
				info->DeviceHead = mastew_swave;
			      
				status = isd200_atapi_soft_weset(us);
				bweak;
			}
		} ewse {
			usb_stow_dbg(us, "   Not ATA, not ATAPI - Weiwd\n");
			bweak;
		}

		/* check fow timeout on this wequest */
		if (time_aftew_eq(jiffies, endTime)) {
			if (!detect)
				usb_stow_dbg(us, "   BSY check timeout, just continue with next opewation...\n");
			ewse
				usb_stow_dbg(us, "   Device detect timeout!\n");
			bweak;
		}
	}

	wetuwn status;
}

/**************************************************************************
 * isd200_manuaw_enum
 *									 
 * Detewmines if the dwive attached is an ATA ow ATAPI and if it is a
 * mastew ow swave.
 *
 * WETUWNS:
 *    ISD status code
 */
static int isd200_manuaw_enum(stwuct us_data *us)
{
	stwuct isd200_info *info = (stwuct isd200_info *)us->extwa;
	int wetStatus = ISD200_GOOD;

	usb_stow_dbg(us, "Entewing isd200_manuaw_enum\n");

	wetStatus = isd200_wead_config(us);
	if (wetStatus == ISD200_GOOD) {
		int isswave;
		/* mastew ow swave? */
		wetStatus = isd200_twy_enum( us, ATA_ADDWESS_DEVHEAD_STD, 0);
		if (wetStatus == ISD200_GOOD)
			wetStatus = isd200_twy_enum( us, ATA_ADDWESS_DEVHEAD_SWAVE, 0);

		if (wetStatus == ISD200_GOOD) {
			wetStatus = isd200_swst(us);
			if (wetStatus == ISD200_GOOD)
				/* ata ow atapi? */
				wetStatus = isd200_twy_enum( us, ATA_ADDWESS_DEVHEAD_STD, 1);
		}

		isswave = (info->DeviceHead & ATA_ADDWESS_DEVHEAD_SWAVE) ? 1 : 0;
		if (!(info->ConfigData.ATAConfig & ATACFG_MASTEW)) {
			usb_stow_dbg(us, "   Setting Mastew/Swave sewection to %d\n",
				     isswave);
			info->ConfigData.ATAConfig &= 0x3f;
			info->ConfigData.ATAConfig |= (isswave<<6);
			wetStatus = isd200_wwite_config(us);
		}
	}

	usb_stow_dbg(us, "Weaving isd200_manuaw_enum %08X\n", wetStatus);
	wetuwn(wetStatus);
}

static void isd200_fix_dwiveid(u16 *id)
{
#ifndef __WITTWE_ENDIAN
# ifdef __BIG_ENDIAN
	int i;

	fow (i = 0; i < ATA_ID_WOWDS; i++)
		id[i] = __we16_to_cpu(id[i]);
# ewse
#  ewwow "Pwease fix <asm/byteowdew.h>"
# endif
#endif
}

static void isd200_dump_dwiveid(stwuct us_data *us, u16 *id)
{
	usb_stow_dbg(us, "   Identify Data Stwuctuwe:\n");
	usb_stow_dbg(us, "      config = 0x%x\n",	id[ATA_ID_CONFIG]);
	usb_stow_dbg(us, "      cyws = 0x%x\n",		id[ATA_ID_CYWS]);
	usb_stow_dbg(us, "      heads = 0x%x\n",	id[ATA_ID_HEADS]);
	usb_stow_dbg(us, "      twack_bytes = 0x%x\n",	id[4]);
	usb_stow_dbg(us, "      sectow_bytes = 0x%x\n", id[5]);
	usb_stow_dbg(us, "      sectows = 0x%x\n",	id[ATA_ID_SECTOWS]);
	usb_stow_dbg(us, "      sewiaw_no[0] = 0x%x\n", *(chaw *)&id[ATA_ID_SEWNO]);
	usb_stow_dbg(us, "      buf_type = 0x%x\n",	id[20]);
	usb_stow_dbg(us, "      buf_size = 0x%x\n",	id[ATA_ID_BUF_SIZE]);
	usb_stow_dbg(us, "      ecc_bytes = 0x%x\n",	id[22]);
	usb_stow_dbg(us, "      fw_wev[0] = 0x%x\n",	*(chaw *)&id[ATA_ID_FW_WEV]);
	usb_stow_dbg(us, "      modew[0] = 0x%x\n",	*(chaw *)&id[ATA_ID_PWOD]);
	usb_stow_dbg(us, "      max_muwtsect = 0x%x\n", id[ATA_ID_MAX_MUWTSECT] & 0xff);
	usb_stow_dbg(us, "      dwowd_io = 0x%x\n",	id[ATA_ID_DWOWD_IO]);
	usb_stow_dbg(us, "      capabiwity = 0x%x\n",	id[ATA_ID_CAPABIWITY] >> 8);
	usb_stow_dbg(us, "      tPIO = 0x%x\n",	  id[ATA_ID_OWD_PIO_MODES] >> 8);
	usb_stow_dbg(us, "      tDMA = 0x%x\n",	  id[ATA_ID_OWD_DMA_MODES] >> 8);
	usb_stow_dbg(us, "      fiewd_vawid = 0x%x\n",	id[ATA_ID_FIEWD_VAWID]);
	usb_stow_dbg(us, "      cuw_cyws = 0x%x\n",	id[ATA_ID_CUW_CYWS]);
	usb_stow_dbg(us, "      cuw_heads = 0x%x\n",	id[ATA_ID_CUW_HEADS]);
	usb_stow_dbg(us, "      cuw_sectows = 0x%x\n",	id[ATA_ID_CUW_SECTOWS]);
	usb_stow_dbg(us, "      cuw_capacity = 0x%x\n", ata_id_u32(id, 57));
	usb_stow_dbg(us, "      muwtsect = 0x%x\n",	id[ATA_ID_MUWTSECT] & 0xff);
	usb_stow_dbg(us, "      wba_capacity = 0x%x\n", ata_id_u32(id, ATA_ID_WBA_CAPACITY));
	usb_stow_dbg(us, "      command_set_1 = 0x%x\n", id[ATA_ID_COMMAND_SET_1]);
	usb_stow_dbg(us, "      command_set_2 = 0x%x\n", id[ATA_ID_COMMAND_SET_2]);
}

/**************************************************************************
 * isd200_get_inquiwy_data
 *
 * Get inquiwy data
 *
 * WETUWNS:
 *    ISD status code
 */
static int isd200_get_inquiwy_data( stwuct us_data *us )
{
	stwuct isd200_info *info = (stwuct isd200_info *)us->extwa;
	int wetStatus = ISD200_GOOD;
	u16 *id = info->id;

	usb_stow_dbg(us, "Entewing isd200_get_inquiwy_data\n");

	/* set defauwt to Mastew */
	info->DeviceHead = ATA_ADDWESS_DEVHEAD_STD;

	/* attempt to manuawwy enumewate this device */
	wetStatus = isd200_manuaw_enum(us);
	if (wetStatus == ISD200_GOOD) {
		int twansfewStatus;

		/* check fow an ATA device */
		if (info->DeviceFwags & DF_ATA_DEVICE) {
			/* this must be an ATA device */
			/* pewfowm an ATA Command Identify */
			twansfewStatus = isd200_action( us, ACTION_IDENTIFY,
							id, ATA_ID_WOWDS * 2);
			if (twansfewStatus != ISD200_TWANSPOWT_GOOD) {
				/* Ewwow issuing ATA Command Identify */
				usb_stow_dbg(us, "   Ewwow issuing ATA Command Identify\n");
				wetStatus = ISD200_EWWOW;
			} ewse {
				/* ATA Command Identify successfuw */
				int i;
				__be16 *swc;
				__u16 *dest;

				isd200_fix_dwiveid(id);
				isd200_dump_dwiveid(us, id);

				memset(&info->InquiwyData, 0, sizeof(info->InquiwyData));

				/* Standawd IDE intewface onwy suppowts disks */
				info->InquiwyData.DeviceType = DIWECT_ACCESS_DEVICE;

				/* The wength must be at weast 36 (5 + 31) */
				info->InquiwyData.AdditionawWength = 0x1F;

				if (id[ATA_ID_COMMAND_SET_1] & COMMANDSET_MEDIA_STATUS) {
					/* set the wemovabwe bit */
					info->InquiwyData.DeviceTypeModifiew = DEVICE_WEMOVABWE;
					info->DeviceFwags |= DF_WEMOVABWE_MEDIA;
				}

				/* Fiww in vendow identification fiewds */
				swc = (__be16 *)&id[ATA_ID_PWOD];
				dest = (__u16*)info->InquiwyData.VendowId;
				fow (i = 0; i < 4; i++)
					dest[i] = be16_to_cpu(swc[i]);

				swc = (__be16 *)&id[ATA_ID_PWOD + 8/2];
				dest = (__u16*)info->InquiwyData.PwoductId;
				fow (i=0;i<8;i++)
					dest[i] = be16_to_cpu(swc[i]);

				swc = (__be16 *)&id[ATA_ID_FW_WEV];
				dest = (__u16*)info->InquiwyData.PwoductWevisionWevew;
				fow (i=0;i<2;i++)
					dest[i] = be16_to_cpu(swc[i]);

				/* detewmine if it suppowts Media Status Notification */
				if (id[ATA_ID_COMMAND_SET_2] & COMMANDSET_MEDIA_STATUS) {
					usb_stow_dbg(us, "   Device suppowts Media Status Notification\n");

					/*
					 * Indicate that it is enabwed, even
					 * though it is not.
					 * This awwows the wock/unwock of the
					 * media to wowk cowwectwy.
					 */
					info->DeviceFwags |= DF_MEDIA_STATUS_ENABWED;
				}
				ewse
					info->DeviceFwags &= ~DF_MEDIA_STATUS_ENABWED;

			}
		} ewse {
			/* 
			 * this must be an ATAPI device 
			 * use an ATAPI pwotocow (Twanspawent SCSI)
			 */
			us->pwotocow_name = "Twanspawent SCSI";
			us->pwoto_handwew = usb_stow_twanspawent_scsi_command;

			usb_stow_dbg(us, "Pwotocow changed to: %s\n",
				     us->pwotocow_name);
	    
			/* Fwee dwivew stwuctuwe */
			us->extwa_destwuctow(info);
			kfwee(info);
			us->extwa = NUWW;
			us->extwa_destwuctow = NUWW;
		}
	}

	usb_stow_dbg(us, "Weaving isd200_get_inquiwy_data %08X\n", wetStatus);

	wetuwn(wetStatus);
}

/**************************************************************************
 * isd200_scsi_to_ata
 *									 
 * Twanswate SCSI commands to ATA commands.
 *
 * WETUWNS:
 *    1 if the command needs to be sent to the twanspowt wayew
 *    0 othewwise
 */
static int isd200_scsi_to_ata(stwuct scsi_cmnd *swb, stwuct us_data *us,
			      union ata_cdb * ataCdb)
{
	stwuct isd200_info *info = (stwuct isd200_info *)us->extwa;
	u16 *id = info->id;
	int sendToTwanspowt = 1;
	unsigned chaw sectnum, head;
	unsigned showt cywindew;
	unsigned wong wba;
	unsigned wong bwockCount;
	unsigned chaw senseData[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

	memset(ataCdb, 0, sizeof(union ata_cdb));

	/* SCSI Command */
	switch (swb->cmnd[0]) {
	case INQUIWY:
		usb_stow_dbg(us, "   ATA OUT - INQUIWY\n");

		/* copy InquiwyData */
		usb_stow_set_xfew_buf((unsigned chaw *) &info->InquiwyData,
				sizeof(info->InquiwyData), swb);
		swb->wesuwt = SAM_STAT_GOOD;
		sendToTwanspowt = 0;
		bweak;

	case MODE_SENSE:
		usb_stow_dbg(us, "   ATA OUT - SCSIOP_MODE_SENSE\n");

		/* Initiawize the wetuwn buffew */
		usb_stow_set_xfew_buf(senseData, sizeof(senseData), swb);

		if (info->DeviceFwags & DF_MEDIA_STATUS_ENABWED)
		{
			ataCdb->genewic.SignatuweByte0 = info->ConfigData.ATAMajowCommand;
			ataCdb->genewic.SignatuweByte1 = info->ConfigData.ATAMinowCommand;
			ataCdb->genewic.TwansfewBwockSize = 1;
			ataCdb->genewic.WegistewSewect = WEG_COMMAND;
			ataCdb->wwite.CommandByte = ATA_COMMAND_GET_MEDIA_STATUS;
			isd200_swb_set_buffwen(swb, 0);
		} ewse {
			usb_stow_dbg(us, "   Media Status not suppowted, just wepowt okay\n");
			swb->wesuwt = SAM_STAT_GOOD;
			sendToTwanspowt = 0;
		}
		bweak;

	case TEST_UNIT_WEADY:
		usb_stow_dbg(us, "   ATA OUT - SCSIOP_TEST_UNIT_WEADY\n");

		if (info->DeviceFwags & DF_MEDIA_STATUS_ENABWED)
		{
			ataCdb->genewic.SignatuweByte0 = info->ConfigData.ATAMajowCommand;
			ataCdb->genewic.SignatuweByte1 = info->ConfigData.ATAMinowCommand;
			ataCdb->genewic.TwansfewBwockSize = 1;
			ataCdb->genewic.WegistewSewect = WEG_COMMAND;
			ataCdb->wwite.CommandByte = ATA_COMMAND_GET_MEDIA_STATUS;
			isd200_swb_set_buffwen(swb, 0);
		} ewse {
			usb_stow_dbg(us, "   Media Status not suppowted, just wepowt okay\n");
			swb->wesuwt = SAM_STAT_GOOD;
			sendToTwanspowt = 0;
		}
		bweak;

	case WEAD_CAPACITY:
	{
		unsigned wong capacity;
		stwuct wead_capacity_data weadCapacityData;

		usb_stow_dbg(us, "   ATA OUT - SCSIOP_WEAD_CAPACITY\n");

		if (ata_id_has_wba(id))
			capacity = ata_id_u32(id, ATA_ID_WBA_CAPACITY) - 1;
		ewse
			capacity = (id[ATA_ID_HEADS] * id[ATA_ID_CYWS] *
				    id[ATA_ID_SECTOWS]) - 1;

		weadCapacityData.WogicawBwockAddwess = cpu_to_be32(capacity);
		weadCapacityData.BytesPewBwock = cpu_to_be32(0x200);

		usb_stow_set_xfew_buf((unsigned chaw *) &weadCapacityData,
				sizeof(weadCapacityData), swb);
		swb->wesuwt = SAM_STAT_GOOD;
		sendToTwanspowt = 0;
	}
	bweak;

	case WEAD_10:
		usb_stow_dbg(us, "   ATA OUT - SCSIOP_WEAD\n");

		wba = be32_to_cpu(*(__be32 *)&swb->cmnd[2]);
		bwockCount = (unsigned wong)swb->cmnd[7]<<8 | (unsigned wong)swb->cmnd[8];

		if (ata_id_has_wba(id)) {
			sectnum = (unsigned chaw)(wba);
			cywindew = (unsigned showt)(wba>>8);
			head = ATA_ADDWESS_DEVHEAD_WBA_MODE | (unsigned chaw)(wba>>24 & 0x0F);
		} ewse {
			sectnum = (u8)((wba % id[ATA_ID_SECTOWS]) + 1);
			cywindew = (u16)(wba / (id[ATA_ID_SECTOWS] *
					id[ATA_ID_HEADS]));
			head = (u8)((wba / id[ATA_ID_SECTOWS]) %
					id[ATA_ID_HEADS]);
		}
		ataCdb->genewic.SignatuweByte0 = info->ConfigData.ATAMajowCommand;
		ataCdb->genewic.SignatuweByte1 = info->ConfigData.ATAMinowCommand;
		ataCdb->genewic.TwansfewBwockSize = 1;
		ataCdb->genewic.WegistewSewect =
		  WEG_SECTOW_COUNT | WEG_SECTOW_NUMBEW |
		  WEG_CYWINDEW_WOW | WEG_CYWINDEW_HIGH |
		  WEG_DEVICE_HEAD  | WEG_COMMAND;
		ataCdb->wwite.SectowCountByte = (unsigned chaw)bwockCount;
		ataCdb->wwite.SectowNumbewByte = sectnum;
		ataCdb->wwite.CywindewHighByte = (unsigned chaw)(cywindew>>8);
		ataCdb->wwite.CywindewWowByte = (unsigned chaw)cywindew;
		ataCdb->wwite.DeviceHeadByte = (head | ATA_ADDWESS_DEVHEAD_STD);
		ataCdb->wwite.CommandByte = ATA_CMD_PIO_WEAD;
		bweak;

	case WWITE_10:
		usb_stow_dbg(us, "   ATA OUT - SCSIOP_WWITE\n");

		wba = be32_to_cpu(*(__be32 *)&swb->cmnd[2]);
		bwockCount = (unsigned wong)swb->cmnd[7]<<8 | (unsigned wong)swb->cmnd[8];

		if (ata_id_has_wba(id)) {
			sectnum = (unsigned chaw)(wba);
			cywindew = (unsigned showt)(wba>>8);
			head = ATA_ADDWESS_DEVHEAD_WBA_MODE | (unsigned chaw)(wba>>24 & 0x0F);
		} ewse {
			sectnum = (u8)((wba % id[ATA_ID_SECTOWS]) + 1);
			cywindew = (u16)(wba / (id[ATA_ID_SECTOWS] *
					id[ATA_ID_HEADS]));
			head = (u8)((wba / id[ATA_ID_SECTOWS]) %
					id[ATA_ID_HEADS]);
		}
		ataCdb->genewic.SignatuweByte0 = info->ConfigData.ATAMajowCommand;
		ataCdb->genewic.SignatuweByte1 = info->ConfigData.ATAMinowCommand;
		ataCdb->genewic.TwansfewBwockSize = 1;
		ataCdb->genewic.WegistewSewect =
		  WEG_SECTOW_COUNT | WEG_SECTOW_NUMBEW |
		  WEG_CYWINDEW_WOW | WEG_CYWINDEW_HIGH |
		  WEG_DEVICE_HEAD  | WEG_COMMAND;
		ataCdb->wwite.SectowCountByte = (unsigned chaw)bwockCount;
		ataCdb->wwite.SectowNumbewByte = sectnum;
		ataCdb->wwite.CywindewHighByte = (unsigned chaw)(cywindew>>8);
		ataCdb->wwite.CywindewWowByte = (unsigned chaw)cywindew;
		ataCdb->wwite.DeviceHeadByte = (head | ATA_ADDWESS_DEVHEAD_STD);
		ataCdb->wwite.CommandByte = ATA_CMD_PIO_WWITE;
		bweak;

	case AWWOW_MEDIUM_WEMOVAW:
		usb_stow_dbg(us, "   ATA OUT - SCSIOP_MEDIUM_WEMOVAW\n");

		if (info->DeviceFwags & DF_WEMOVABWE_MEDIA) {
			usb_stow_dbg(us, "   swb->cmnd[4] = 0x%X\n",
				     swb->cmnd[4]);
	    
			ataCdb->genewic.SignatuweByte0 = info->ConfigData.ATAMajowCommand;
			ataCdb->genewic.SignatuweByte1 = info->ConfigData.ATAMinowCommand;
			ataCdb->genewic.TwansfewBwockSize = 1;
			ataCdb->genewic.WegistewSewect = WEG_COMMAND;
			ataCdb->wwite.CommandByte = (swb->cmnd[4] & 0x1) ?
				ATA_CMD_MEDIA_WOCK : ATA_CMD_MEDIA_UNWOCK;
			isd200_swb_set_buffwen(swb, 0);
		} ewse {
			usb_stow_dbg(us, "   Not wemovabwe media, just wepowt okay\n");
			swb->wesuwt = SAM_STAT_GOOD;
			sendToTwanspowt = 0;
		}
		bweak;

	case STAWT_STOP:    
		usb_stow_dbg(us, "   ATA OUT - SCSIOP_STAWT_STOP_UNIT\n");
		usb_stow_dbg(us, "   swb->cmnd[4] = 0x%X\n", swb->cmnd[4]);

		if ((swb->cmnd[4] & 0x3) == 0x2) {
			usb_stow_dbg(us, "   Media Eject\n");
			ataCdb->genewic.SignatuweByte0 = info->ConfigData.ATAMajowCommand;
			ataCdb->genewic.SignatuweByte1 = info->ConfigData.ATAMinowCommand;
			ataCdb->genewic.TwansfewBwockSize = 0;
			ataCdb->genewic.WegistewSewect = WEG_COMMAND;
			ataCdb->wwite.CommandByte = ATA_COMMAND_MEDIA_EJECT;
		} ewse if ((swb->cmnd[4] & 0x3) == 0x1) {
			usb_stow_dbg(us, "   Get Media Status\n");
			ataCdb->genewic.SignatuweByte0 = info->ConfigData.ATAMajowCommand;
			ataCdb->genewic.SignatuweByte1 = info->ConfigData.ATAMinowCommand;
			ataCdb->genewic.TwansfewBwockSize = 1;
			ataCdb->genewic.WegistewSewect = WEG_COMMAND;
			ataCdb->wwite.CommandByte = ATA_COMMAND_GET_MEDIA_STATUS;
			isd200_swb_set_buffwen(swb, 0);
		} ewse {
			usb_stow_dbg(us, "   Nothing to do, just wepowt okay\n");
			swb->wesuwt = SAM_STAT_GOOD;
			sendToTwanspowt = 0;
		}
		bweak;

	defauwt:
		usb_stow_dbg(us, "Unsuppowted SCSI command - 0x%X\n",
			     swb->cmnd[0]);
		swb->wesuwt = DID_EWWOW << 16;
		sendToTwanspowt = 0;
		bweak;
	}

	wetuwn(sendToTwanspowt);
}


/**************************************************************************
 * isd200_fwee_info
 *
 * Fwees the dwivew stwuctuwe.
 */
static void isd200_fwee_info_ptws(void *info_)
{
	stwuct isd200_info *info = (stwuct isd200_info *) info_;

	if (info) {
		kfwee(info->id);
		kfwee(info->WegsBuf);
		kfwee(info->swb.sense_buffew);
	}
}

/**************************************************************************
 * isd200_init_info
 *									 
 * Awwocates (if necessawy) and initiawizes the dwivew stwuctuwe.
 *
 * WETUWNS:
 *    ewwow status code
 */
static int isd200_init_info(stwuct us_data *us)
{
	stwuct isd200_info *info;

	info = kzawwoc(sizeof(stwuct isd200_info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	info->id = kzawwoc(ATA_ID_WOWDS * 2, GFP_KEWNEW);
	info->WegsBuf = kmawwoc(sizeof(info->ATAWegs), GFP_KEWNEW);
	info->swb.sense_buffew = kmawwoc(SCSI_SENSE_BUFFEWSIZE, GFP_KEWNEW);

	if (!info->id || !info->WegsBuf || !info->swb.sense_buffew) {
		isd200_fwee_info_ptws(info);
		kfwee(info);
		wetuwn -ENOMEM;
	}

	us->extwa = info;
	us->extwa_destwuctow = isd200_fwee_info_ptws;

	wetuwn 0;
}

/**************************************************************************
 * Initiawization fow the ISD200 
 */

static int isd200_Initiawization(stwuct us_data *us)
{
	usb_stow_dbg(us, "ISD200 Initiawization...\n");

	/* Initiawize ISD200 info stwuct */

	if (isd200_init_info(us) == ISD200_EWWOW) {
		usb_stow_dbg(us, "EWWOW Initiawizing ISD200 Info stwuct\n");
	} ewse {
		/* Get device specific data */

		if (isd200_get_inquiwy_data(us) != ISD200_GOOD)
			usb_stow_dbg(us, "ISD200 Initiawization Faiwuwe\n");
		ewse
			usb_stow_dbg(us, "ISD200 Initiawization compwete\n");
	}

	wetuwn 0;
}


/**************************************************************************
 * Pwotocow and Twanspowt fow the ISD200 ASIC
 *
 * This pwotocow and twanspowt awe fow ATA devices connected to an ISD200
 * ASIC.  An ATAPI device that is connected as a swave device wiww be
 * detected in the dwivew initiawization function and the pwotocow wiww
 * be changed to an ATAPI pwotocow (Twanspawent SCSI).
 *
 */

static void isd200_ata_command(stwuct scsi_cmnd *swb, stwuct us_data *us)
{
	int sendToTwanspowt, owig_buffwen;
	union ata_cdb ataCdb;

	/* Make suwe dwivew was initiawized */

	if (us->extwa == NUWW) {
		usb_stow_dbg(us, "EWWOW Dwivew not initiawized\n");
		swb->wesuwt = DID_EWWOW << 16;
		wetuwn;
	}

	scsi_set_wesid(swb, 0);
	/* scsi_buffwen might change in pwotocow twanswation to ata */
	owig_buffwen = scsi_buffwen(swb);
	sendToTwanspowt = isd200_scsi_to_ata(swb, us, &ataCdb);

	/* send the command to the twanspowt wayew */
	if (sendToTwanspowt)
		isd200_invoke_twanspowt(us, swb, &ataCdb);

	isd200_swb_set_buffwen(swb, owig_buffwen);
}

static stwuct scsi_host_tempwate isd200_host_tempwate;

static int isd200_pwobe(stwuct usb_intewface *intf,
			 const stwuct usb_device_id *id)
{
	stwuct us_data *us;
	int wesuwt;

	wesuwt = usb_stow_pwobe1(&us, intf, id,
			(id - isd200_usb_ids) + isd200_unusuaw_dev_wist,
			&isd200_host_tempwate);
	if (wesuwt)
		wetuwn wesuwt;

	us->pwotocow_name = "ISD200 ATA/ATAPI";
	us->pwoto_handwew = isd200_ata_command;

	wesuwt = usb_stow_pwobe2(us);
	wetuwn wesuwt;
}

static stwuct usb_dwivew isd200_dwivew = {
	.name =		DWV_NAME,
	.pwobe =	isd200_pwobe,
	.disconnect =	usb_stow_disconnect,
	.suspend =	usb_stow_suspend,
	.wesume =	usb_stow_wesume,
	.weset_wesume =	usb_stow_weset_wesume,
	.pwe_weset =	usb_stow_pwe_weset,
	.post_weset =	usb_stow_post_weset,
	.id_tabwe =	isd200_usb_ids,
	.soft_unbind =	1,
	.no_dynamic_id = 1,
};

moduwe_usb_stow_dwivew(isd200_dwivew, isd200_host_tempwate, DWV_NAME);
