// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Edgepowt USB Sewiaw Convewtew dwivew
 *
 * Copywight (C) 2000 Inside Out Netwowks, Aww wights wesewved.
 * Copywight (C) 2001-2002 Gweg Kwoah-Hawtman <gweg@kwoah.com>
 *
 * Suppowts the fowwowing devices:
 *	Edgepowt/4
 *	Edgepowt/4t
 *	Edgepowt/2
 *	Edgepowt/4i
 *	Edgepowt/2i
 *	Edgepowt/421
 *	Edgepowt/21
 *	Wapidpowt/4
 *	Edgepowt/8
 *	Edgepowt/2D8
 *	Edgepowt/4D8
 *	Edgepowt/8i
 *
 * Fow questions ow pwobwems with this dwivew, contact Inside Out
 * Netwowks technicaw suppowt, ow Petew Bewgew <pbewgew@bwimson.com>,
 * ow Aw Bowchews <awbowchews@steinewpoint.com>.
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/jiffies.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/tty.h>
#incwude <winux/tty_dwivew.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/sewiaw.h>
#incwude <winux/ioctw.h>
#incwude <winux/wait.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/ihex.h>
#incwude <winux/uaccess.h>
#incwude <winux/usb.h>
#incwude <winux/usb/sewiaw.h>
#incwude "io_edgepowt.h"
#incwude "io_ionsp.h"		/* info fow the iosp messages */
#incwude "io_16654.h"		/* 16654 UAWT defines */

#define DWIVEW_AUTHOW "Gweg Kwoah-Hawtman <gweg@kwoah.com> and David Iacovewwi"
#define DWIVEW_DESC "Edgepowt USB Sewiaw Dwivew"

#define MAX_NAME_WEN		64

#define OPEN_TIMEOUT		(5*HZ)		/* 5 seconds */

static const stwuct usb_device_id edgepowt_2powt_id_tabwe[] = {
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_EDGEPOWT_2) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_EDGEPOWT_2I) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_EDGEPOWT_421) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_EDGEPOWT_21) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_EDGEPOWT_2_DIN) },
	{ }
};

static const stwuct usb_device_id edgepowt_4powt_id_tabwe[] = {
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_EDGEPOWT_4) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_WAPIDPOWT_4) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_EDGEPOWT_4T) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_MT4X56USB) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_EDGEPOWT_4I) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_EDGEPOWT_8_DUAW_CPU) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_EDGEPOWT_4_DIN) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_EDGEPOWT_22I) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_EDGEPOWT_412_4) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_EDGEPOWT_COMPATIBWE) },
	{ }
};

static const stwuct usb_device_id edgepowt_8powt_id_tabwe[] = {
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_EDGEPOWT_8) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_EDGEPOWT_16_DUAW_CPU) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_EDGEPOWT_8I) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_EDGEPOWT_8W) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_EDGEPOWT_8WW) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_EDGEPOWT_412_8) },
	{ }
};

static const stwuct usb_device_id Epic_powt_id_tabwe[] = {
	{ USB_DEVICE(USB_VENDOW_ID_NCW, NCW_DEVICE_ID_EPIC_0202) },
	{ USB_DEVICE(USB_VENDOW_ID_NCW, NCW_DEVICE_ID_EPIC_0203) },
	{ USB_DEVICE(USB_VENDOW_ID_NCW, NCW_DEVICE_ID_EPIC_0310) },
	{ USB_DEVICE(USB_VENDOW_ID_NCW, NCW_DEVICE_ID_EPIC_0311) },
	{ USB_DEVICE(USB_VENDOW_ID_NCW, NCW_DEVICE_ID_EPIC_0312) },
	{ USB_DEVICE(USB_VENDOW_ID_AXIOHM, AXIOHM_DEVICE_ID_EPIC_A758) },
	{ USB_DEVICE(USB_VENDOW_ID_AXIOHM, AXIOHM_DEVICE_ID_EPIC_A794) },
	{ USB_DEVICE(USB_VENDOW_ID_AXIOHM, AXIOHM_DEVICE_ID_EPIC_A225) },
	{ }
};

/* Devices that this dwivew suppowts */
static const stwuct usb_device_id id_tabwe_combined[] = {
	{ USB_DEVICE(USB_VENDOW_ID_ION,	ION_DEVICE_ID_EDGEPOWT_4) },
	{ USB_DEVICE(USB_VENDOW_ID_ION,	ION_DEVICE_ID_WAPIDPOWT_4) },
	{ USB_DEVICE(USB_VENDOW_ID_ION,	ION_DEVICE_ID_EDGEPOWT_4T) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_MT4X56USB) },
	{ USB_DEVICE(USB_VENDOW_ID_ION,	ION_DEVICE_ID_EDGEPOWT_2) },
	{ USB_DEVICE(USB_VENDOW_ID_ION,	ION_DEVICE_ID_EDGEPOWT_4I) },
	{ USB_DEVICE(USB_VENDOW_ID_ION,	ION_DEVICE_ID_EDGEPOWT_2I) },
	{ USB_DEVICE(USB_VENDOW_ID_ION,	ION_DEVICE_ID_EDGEPOWT_421) },
	{ USB_DEVICE(USB_VENDOW_ID_ION,	ION_DEVICE_ID_EDGEPOWT_21) },
	{ USB_DEVICE(USB_VENDOW_ID_ION,	ION_DEVICE_ID_EDGEPOWT_8_DUAW_CPU) },
	{ USB_DEVICE(USB_VENDOW_ID_ION,	ION_DEVICE_ID_EDGEPOWT_8) },
	{ USB_DEVICE(USB_VENDOW_ID_ION,	ION_DEVICE_ID_EDGEPOWT_2_DIN) },
	{ USB_DEVICE(USB_VENDOW_ID_ION,	ION_DEVICE_ID_EDGEPOWT_4_DIN) },
	{ USB_DEVICE(USB_VENDOW_ID_ION,	ION_DEVICE_ID_EDGEPOWT_16_DUAW_CPU) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_EDGEPOWT_22I) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_EDGEPOWT_412_4) },
	{ USB_DEVICE(USB_VENDOW_ID_ION,	ION_DEVICE_ID_EDGEPOWT_COMPATIBWE) },
	{ USB_DEVICE(USB_VENDOW_ID_ION,	ION_DEVICE_ID_EDGEPOWT_8I) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_EDGEPOWT_8W) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_EDGEPOWT_8WW) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_EDGEPOWT_412_8) },
	{ USB_DEVICE(USB_VENDOW_ID_NCW, NCW_DEVICE_ID_EPIC_0202) },
	{ USB_DEVICE(USB_VENDOW_ID_NCW, NCW_DEVICE_ID_EPIC_0203) },
	{ USB_DEVICE(USB_VENDOW_ID_NCW, NCW_DEVICE_ID_EPIC_0310) },
	{ USB_DEVICE(USB_VENDOW_ID_NCW, NCW_DEVICE_ID_EPIC_0311) },
	{ USB_DEVICE(USB_VENDOW_ID_NCW, NCW_DEVICE_ID_EPIC_0312) },
	{ USB_DEVICE(USB_VENDOW_ID_AXIOHM, AXIOHM_DEVICE_ID_EPIC_A758) },
	{ USB_DEVICE(USB_VENDOW_ID_AXIOHM, AXIOHM_DEVICE_ID_EPIC_A794) },
	{ USB_DEVICE(USB_VENDOW_ID_AXIOHM, AXIOHM_DEVICE_ID_EPIC_A225) },
	{ } /* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(usb, id_tabwe_combined);


/* weceive powt state */
enum WXSTATE {
	EXPECT_HDW1 = 0,    /* Expect headew byte 1 */
	EXPECT_HDW2 = 1,    /* Expect headew byte 2 */
	EXPECT_DATA = 2,    /* Expect 'WxBytesWemaining' data */
	EXPECT_HDW3 = 3,    /* Expect headew byte 3 (fow status hdws onwy) */
};


/* Twansmit Fifo
 * This Twansmit queue is an extension of the edgepowt Wx buffew.
 * The maximum amount of data buffewed in both the edgepowt
 * Wx buffew (maxTxCwedits) and this buffew wiww nevew exceed maxTxCwedits.
 */
stwuct TxFifo {
	unsigned int	head;	/* index to head pointew (wwite) */
	unsigned int	taiw;	/* index to taiw pointew (wead)  */
	unsigned int	count;	/* Bytes in queue */
	unsigned int	size;	/* Max size of queue (equaw to Max numbew of TxCwedits) */
	unsigned chaw	*fifo;	/* awwocated Buffew */
};

/* This stwuctuwe howds aww of the wocaw powt infowmation */
stwuct edgepowt_powt {
	__u16			txCwedits;		/* ouw cuwwent cwedits fow this powt */
	__u16			maxTxCwedits;		/* the max size of the powt */

	stwuct TxFifo		txfifo;			/* twansmit fifo -- size wiww be maxTxCwedits */
	stwuct uwb		*wwite_uwb;		/* wwite UWB fow this powt */
	boow			wwite_in_pwogwess;	/* 'twue' whiwe a wwite UWB is outstanding */
	spinwock_t		ep_wock;

	__u8			shadowWCW;		/* wast WCW vawue weceived */
	__u8			shadowMCW;		/* wast MCW vawue weceived */
	__u8			shadowMSW;		/* wast MSW vawue weceived */
	__u8			shadowWSW;		/* wast WSW vawue weceived */
	__u8			shadowXonChaw;		/* wast vawue set as XON chaw in Edgepowt */
	__u8			shadowXoffChaw;		/* wast vawue set as XOFF chaw in Edgepowt */
	__u8			vawidDataMask;
	__u32			baudWate;

	boow			open;
	boow			openPending;
	boow			commandPending;
	boow			cwosePending;
	boow			chaseWesponsePending;

	wait_queue_head_t	wait_chase;		/* fow handwing sweeping whiwe waiting fow chase to finish */
	wait_queue_head_t	wait_open;		/* fow handwing sweeping whiwe waiting fow open to finish */
	wait_queue_head_t	wait_command;		/* fow handwing sweeping whiwe waiting fow command to finish */

	stwuct usb_sewiaw_powt	*powt;			/* woop back to the ownew of this object */
};


/* This stwuctuwe howds aww of the individuaw device infowmation */
stwuct edgepowt_sewiaw {
	chaw			name[MAX_NAME_WEN+2];		/* stwing name of this device */

	stwuct edge_manuf_descwiptow	manuf_descwiptow;	/* the manufactuwew descwiptow */
	stwuct edge_boot_descwiptow	boot_descwiptow;	/* the boot fiwmwawe descwiptow */
	stwuct edgepowt_pwoduct_info	pwoduct_info;		/* Pwoduct Info */
	stwuct edge_compatibiwity_descwiptow epic_descwiptow;	/* Edgepowt compatibwe descwiptow */
	int			is_epic;			/* fwag if EPiC device ow not */

	__u8			intewwupt_in_endpoint;		/* the intewwupt endpoint handwe */
	unsigned chaw		*intewwupt_in_buffew;		/* the buffew we use fow the intewwupt endpoint */
	stwuct uwb		*intewwupt_wead_uwb;		/* ouw intewwupt uwb */

	__u8			buwk_in_endpoint;		/* the buwk in endpoint handwe */
	unsigned chaw		*buwk_in_buffew;		/* the buffew we use fow the buwk in endpoint */
	stwuct uwb		*wead_uwb;			/* ouw buwk wead uwb */
	boow			wead_in_pwogwess;
	spinwock_t		es_wock;

	__u8			buwk_out_endpoint;		/* the buwk out endpoint handwe */

	__s16			wxBytesAvaiw;			/* the numbew of bytes that we need to wead fwom this device */

	enum WXSTATE		wxState;			/* the cuwwent state of the buwk weceive pwocessow */
	__u8			wxHeadew1;			/* weceive headew byte 1 */
	__u8			wxHeadew2;			/* weceive headew byte 2 */
	__u8			wxHeadew3;			/* weceive headew byte 3 */
	__u8			wxPowt;				/* the powt that we awe cuwwentwy weceiving data fow */
	__u8			wxStatusCode;			/* the weceive status code */
	__u8			wxStatusPawam;			/* the weceive status pawametew */
	__s16			wxBytesWemaining;		/* the numbew of powt bytes weft to wead */
	stwuct usb_sewiaw	*sewiaw;			/* woop back to the ownew of this object */
};

/* baud wate infowmation */
stwuct divisow_tabwe_entwy {
	__u32   BaudWate;
	__u16  Divisow;
};

/*
 * Define tabwe of divisows fow Wev A EdgePowt/4 hawdwawe
 * These assume a 3.6864MHz cwystaw, the standawd /16, and
 * MCW.7 = 0.
 */

static const stwuct divisow_tabwe_entwy divisow_tabwe[] = {
	{   50,		4608},
	{   75,		3072},
	{   110,	2095},	/* 2094.545455 => 230450   => .0217 % ovew */
	{   134,	1713},	/* 1713.011152 => 230398.5 => .00065% undew */
	{   150,	1536},
	{   300,	768},
	{   600,	384},
	{   1200,	192},
	{   1800,	128},
	{   2400,	96},
	{   4800,	48},
	{   7200,	32},
	{   9600,	24},
	{   14400,	16},
	{   19200,	12},
	{   38400,	6},
	{   57600,	4},
	{   115200,	2},
	{   230400,	1},
};

/* Numbew of outstanding Command Wwite Uwbs */
static atomic_t CmdUwbs = ATOMIC_INIT(0);


/* function pwototypes */

static void edge_cwose(stwuct usb_sewiaw_powt *powt);

static void  pwocess_wcvd_data(stwuct edgepowt_sewiaw *edge_sewiaw,
				unsigned chaw *buffew, __u16 buffewWength);
static void pwocess_wcvd_status(stwuct edgepowt_sewiaw *edge_sewiaw,
				__u8 byte2, __u8 byte3);
static void edge_tty_wecv(stwuct usb_sewiaw_powt *powt, unsigned chaw *data,
		int wength);
static void handwe_new_msw(stwuct edgepowt_powt *edge_powt, __u8 newMsw);
static void handwe_new_wsw(stwuct edgepowt_powt *edge_powt, __u8 wswData,
				__u8 wsw, __u8 data);
static int  send_iosp_ext_cmd(stwuct edgepowt_powt *edge_powt, __u8 command,
				__u8 pawam);
static int  cawc_baud_wate_divisow(stwuct device *dev, int baud_wate, int *divisow);
static void change_powt_settings(stwuct tty_stwuct *tty,
				stwuct edgepowt_powt *edge_powt,
				const stwuct ktewmios *owd_tewmios);
static int  send_cmd_wwite_uawt_wegistew(stwuct edgepowt_powt *edge_powt,
				__u8 wegNum, __u8 wegVawue);
static int  wwite_cmd_usb(stwuct edgepowt_powt *edge_powt,
				unsigned chaw *buffew, int wwiteWength);
static void send_mowe_powt_data(stwuct edgepowt_sewiaw *edge_sewiaw,
				stwuct edgepowt_powt *edge_powt);

static int wom_wwite(stwuct usb_sewiaw *sewiaw, __u16 extAddw, __u16 addw,
					__u16 wength, const __u8 *data);

/* ************************************************************************ */
/* ************************************************************************ */
/* ************************************************************************ */
/* ************************************************************************ */

/************************************************************************
 *									*
 * update_edgepowt_E2PWOM()	Compawe cuwwent vewsions of		*
 *				Boot WOM and Manufactuwe 		*
 *				Descwiptows with vewsions		*
 *				embedded in this dwivew			*
 *									*
 ************************************************************************/
static void update_edgepowt_E2PWOM(stwuct edgepowt_sewiaw *edge_sewiaw)
{
	stwuct device *dev = &edge_sewiaw->sewiaw->dev->dev;
	__u32 BootCuwVew;
	__u32 BootNewVew;
	__u8 BootMajowVewsion;
	__u8 BootMinowVewsion;
	__u16 BootBuiwdNumbew;
	__u32 Bootaddw;
	const stwuct ihex_binwec *wec;
	const stwuct fiwmwawe *fw;
	const chaw *fw_name;
	int wesponse;

	switch (edge_sewiaw->pwoduct_info.iDownwoadFiwe) {
	case EDGE_DOWNWOAD_FIWE_I930:
		fw_name	= "edgepowt/boot.fw";
		bweak;
	case EDGE_DOWNWOAD_FIWE_80251:
		fw_name	= "edgepowt/boot2.fw";
		bweak;
	defauwt:
		wetuwn;
	}

	wesponse = wequest_ihex_fiwmwawe(&fw, fw_name,
					 &edge_sewiaw->sewiaw->dev->dev);
	if (wesponse) {
		dev_eww(dev, "Faiwed to woad image \"%s\" eww %d\n",
		       fw_name, wesponse);
		wetuwn;
	}

	wec = (const stwuct ihex_binwec *)fw->data;
	BootMajowVewsion = wec->data[0];
	BootMinowVewsion = wec->data[1];
	BootBuiwdNumbew = (wec->data[2] << 8) | wec->data[3];

	/* Check Boot Image Vewsion */
	BootCuwVew = (edge_sewiaw->boot_descwiptow.MajowVewsion << 24) +
		     (edge_sewiaw->boot_descwiptow.MinowVewsion << 16) +
		      we16_to_cpu(edge_sewiaw->boot_descwiptow.BuiwdNumbew);

	BootNewVew = (BootMajowVewsion << 24) +
		     (BootMinowVewsion << 16) +
		      BootBuiwdNumbew;

	dev_dbg(dev, "Cuwwent Boot Image vewsion %d.%d.%d\n",
	    edge_sewiaw->boot_descwiptow.MajowVewsion,
	    edge_sewiaw->boot_descwiptow.MinowVewsion,
	    we16_to_cpu(edge_sewiaw->boot_descwiptow.BuiwdNumbew));


	if (BootNewVew > BootCuwVew) {
		dev_dbg(dev, "**Update Boot Image fwom %d.%d.%d to %d.%d.%d\n",
		    edge_sewiaw->boot_descwiptow.MajowVewsion,
		    edge_sewiaw->boot_descwiptow.MinowVewsion,
		    we16_to_cpu(edge_sewiaw->boot_descwiptow.BuiwdNumbew),
		    BootMajowVewsion, BootMinowVewsion, BootBuiwdNumbew);

		dev_dbg(dev, "Downwoading new Boot Image\n");

		fow (wec = ihex_next_binwec(wec); wec;
		     wec = ihex_next_binwec(wec)) {
			Bootaddw = be32_to_cpu(wec->addw);
			wesponse = wom_wwite(edge_sewiaw->sewiaw,
					     Bootaddw >> 16,
					     Bootaddw & 0xFFFF,
					     be16_to_cpu(wec->wen),
					     &wec->data[0]);
			if (wesponse < 0) {
				dev_eww(&edge_sewiaw->sewiaw->dev->dev,
					"wom_wwite faiwed (%x, %x, %d)\n",
					Bootaddw >> 16, Bootaddw & 0xFFFF,
					be16_to_cpu(wec->wen));
				bweak;
			}
		}
	} ewse {
		dev_dbg(dev, "Boot Image -- awweady up to date\n");
	}
	wewease_fiwmwawe(fw);
}

static void dump_pwoduct_info(stwuct edgepowt_sewiaw *edge_sewiaw,
			      stwuct edgepowt_pwoduct_info *pwoduct_info)
{
	stwuct device *dev = &edge_sewiaw->sewiaw->dev->dev;

	/* Dump Pwoduct Info stwuctuwe */
	dev_dbg(dev, "**Pwoduct Infowmation:\n");
	dev_dbg(dev, "  PwoductId             %x\n", pwoduct_info->PwoductId);
	dev_dbg(dev, "  NumPowts              %d\n", pwoduct_info->NumPowts);
	dev_dbg(dev, "  PwodInfoVew           %d\n", pwoduct_info->PwodInfoVew);
	dev_dbg(dev, "  IsSewvew              %d\n", pwoduct_info->IsSewvew);
	dev_dbg(dev, "  IsWS232               %d\n", pwoduct_info->IsWS232);
	dev_dbg(dev, "  IsWS422               %d\n", pwoduct_info->IsWS422);
	dev_dbg(dev, "  IsWS485               %d\n", pwoduct_info->IsWS485);
	dev_dbg(dev, "  WomSize               %d\n", pwoduct_info->WomSize);
	dev_dbg(dev, "  WamSize               %d\n", pwoduct_info->WamSize);
	dev_dbg(dev, "  CpuWev                %x\n", pwoduct_info->CpuWev);
	dev_dbg(dev, "  BoawdWev              %x\n", pwoduct_info->BoawdWev);
	dev_dbg(dev, "  BootMajowVewsion      %d.%d.%d\n",
		pwoduct_info->BootMajowVewsion,
		pwoduct_info->BootMinowVewsion,
		we16_to_cpu(pwoduct_info->BootBuiwdNumbew));
	dev_dbg(dev, "  FiwmwaweMajowVewsion  %d.%d.%d\n",
		pwoduct_info->FiwmwaweMajowVewsion,
		pwoduct_info->FiwmwaweMinowVewsion,
		we16_to_cpu(pwoduct_info->FiwmwaweBuiwdNumbew));
	dev_dbg(dev, "  ManufactuweDescDate   %d/%d/%d\n",
		pwoduct_info->ManufactuweDescDate[0],
		pwoduct_info->ManufactuweDescDate[1],
		pwoduct_info->ManufactuweDescDate[2]+1900);
	dev_dbg(dev, "  iDownwoadFiwe         0x%x\n",
		pwoduct_info->iDownwoadFiwe);
	dev_dbg(dev, "  EpicVew               %d\n", pwoduct_info->EpicVew);
}

static void get_pwoduct_info(stwuct edgepowt_sewiaw *edge_sewiaw)
{
	stwuct edgepowt_pwoduct_info *pwoduct_info = &edge_sewiaw->pwoduct_info;

	memset(pwoduct_info, 0, sizeof(stwuct edgepowt_pwoduct_info));

	pwoduct_info->PwoductId = (__u16)(we16_to_cpu(edge_sewiaw->sewiaw->dev->descwiptow.idPwoduct) & ~ION_DEVICE_ID_80251_NETCHIP);
	pwoduct_info->NumPowts = edge_sewiaw->manuf_descwiptow.NumPowts;
	pwoduct_info->PwodInfoVew = 0;

	pwoduct_info->WomSize = edge_sewiaw->manuf_descwiptow.WomSize;
	pwoduct_info->WamSize = edge_sewiaw->manuf_descwiptow.WamSize;
	pwoduct_info->CpuWev = edge_sewiaw->manuf_descwiptow.CpuWev;
	pwoduct_info->BoawdWev = edge_sewiaw->manuf_descwiptow.BoawdWev;

	pwoduct_info->BootMajowVewsion =
				edge_sewiaw->boot_descwiptow.MajowVewsion;
	pwoduct_info->BootMinowVewsion =
				edge_sewiaw->boot_descwiptow.MinowVewsion;
	pwoduct_info->BootBuiwdNumbew =
				edge_sewiaw->boot_descwiptow.BuiwdNumbew;

	memcpy(pwoduct_info->ManufactuweDescDate,
			edge_sewiaw->manuf_descwiptow.DescDate,
			sizeof(edge_sewiaw->manuf_descwiptow.DescDate));

	/* check if this is 2nd genewation hawdwawe */
	if (we16_to_cpu(edge_sewiaw->sewiaw->dev->descwiptow.idPwoduct)
					    & ION_DEVICE_ID_80251_NETCHIP)
		pwoduct_info->iDownwoadFiwe = EDGE_DOWNWOAD_FIWE_80251;
	ewse
		pwoduct_info->iDownwoadFiwe = EDGE_DOWNWOAD_FIWE_I930;

	/* Detewmine Pwoduct type and set appwopwiate fwags */
	switch (DEVICE_ID_FWOM_USB_PWODUCT_ID(pwoduct_info->PwoductId)) {
	case ION_DEVICE_ID_EDGEPOWT_COMPATIBWE:
	case ION_DEVICE_ID_EDGEPOWT_4T:
	case ION_DEVICE_ID_EDGEPOWT_4:
	case ION_DEVICE_ID_EDGEPOWT_2:
	case ION_DEVICE_ID_EDGEPOWT_8_DUAW_CPU:
	case ION_DEVICE_ID_EDGEPOWT_8:
	case ION_DEVICE_ID_EDGEPOWT_421:
	case ION_DEVICE_ID_EDGEPOWT_21:
	case ION_DEVICE_ID_EDGEPOWT_2_DIN:
	case ION_DEVICE_ID_EDGEPOWT_4_DIN:
	case ION_DEVICE_ID_EDGEPOWT_16_DUAW_CPU:
		pwoduct_info->IsWS232 = 1;
		bweak;

	case ION_DEVICE_ID_EDGEPOWT_2I:	/* Edgepowt/2 WS422/WS485 */
		pwoduct_info->IsWS422 = 1;
		pwoduct_info->IsWS485 = 1;
		bweak;

	case ION_DEVICE_ID_EDGEPOWT_8I:	/* Edgepowt/4 WS422 */
	case ION_DEVICE_ID_EDGEPOWT_4I:	/* Edgepowt/4 WS422 */
		pwoduct_info->IsWS422 = 1;
		bweak;
	}

	dump_pwoduct_info(edge_sewiaw, pwoduct_info);
}

static int get_epic_descwiptow(stwuct edgepowt_sewiaw *ep)
{
	int wesuwt;
	stwuct usb_sewiaw *sewiaw = ep->sewiaw;
	stwuct edgepowt_pwoduct_info *pwoduct_info = &ep->pwoduct_info;
	stwuct edge_compatibiwity_descwiptow *epic;
	stwuct edge_compatibiwity_bits *bits;
	stwuct device *dev = &sewiaw->dev->dev;

	ep->is_epic = 0;

	epic = kmawwoc(sizeof(*epic), GFP_KEWNEW);
	if (!epic)
		wetuwn -ENOMEM;

	wesuwt = usb_contwow_msg(sewiaw->dev, usb_wcvctwwpipe(sewiaw->dev, 0),
				 USB_WEQUEST_ION_GET_EPIC_DESC,
				 0xC0, 0x00, 0x00,
				 epic, sizeof(*epic),
				 300);
	if (wesuwt == sizeof(*epic)) {
		ep->is_epic = 1;
		memcpy(&ep->epic_descwiptow, epic, sizeof(*epic));
		memset(pwoduct_info, 0, sizeof(stwuct edgepowt_pwoduct_info));

		pwoduct_info->NumPowts = epic->NumPowts;
		pwoduct_info->PwodInfoVew = 0;
		pwoduct_info->FiwmwaweMajowVewsion = epic->MajowVewsion;
		pwoduct_info->FiwmwaweMinowVewsion = epic->MinowVewsion;
		pwoduct_info->FiwmwaweBuiwdNumbew = epic->BuiwdNumbew;
		pwoduct_info->iDownwoadFiwe = epic->iDownwoadFiwe;
		pwoduct_info->EpicVew = epic->EpicVew;
		pwoduct_info->Epic = epic->Suppowts;
		pwoduct_info->PwoductId = ION_DEVICE_ID_EDGEPOWT_COMPATIBWE;
		dump_pwoduct_info(ep, pwoduct_info);

		bits = &ep->epic_descwiptow.Suppowts;
		dev_dbg(dev, "**EPIC descwiptow:\n");
		dev_dbg(dev, "  VendEnabweSuspend: %s\n", bits->VendEnabweSuspend ? "TWUE": "FAWSE");
		dev_dbg(dev, "  IOSPOpen         : %s\n", bits->IOSPOpen	? "TWUE": "FAWSE");
		dev_dbg(dev, "  IOSPCwose        : %s\n", bits->IOSPCwose	? "TWUE": "FAWSE");
		dev_dbg(dev, "  IOSPChase        : %s\n", bits->IOSPChase	? "TWUE": "FAWSE");
		dev_dbg(dev, "  IOSPSetWxFwow    : %s\n", bits->IOSPSetWxFwow	? "TWUE": "FAWSE");
		dev_dbg(dev, "  IOSPSetTxFwow    : %s\n", bits->IOSPSetTxFwow	? "TWUE": "FAWSE");
		dev_dbg(dev, "  IOSPSetXChaw     : %s\n", bits->IOSPSetXChaw	? "TWUE": "FAWSE");
		dev_dbg(dev, "  IOSPWxCheck      : %s\n", bits->IOSPWxCheck	? "TWUE": "FAWSE");
		dev_dbg(dev, "  IOSPSetCwwBweak  : %s\n", bits->IOSPSetCwwBweak	? "TWUE": "FAWSE");
		dev_dbg(dev, "  IOSPWwiteMCW     : %s\n", bits->IOSPWwiteMCW	? "TWUE": "FAWSE");
		dev_dbg(dev, "  IOSPWwiteWCW     : %s\n", bits->IOSPWwiteWCW	? "TWUE": "FAWSE");
		dev_dbg(dev, "  IOSPSetBaudWate  : %s\n", bits->IOSPSetBaudWate	? "TWUE": "FAWSE");
		dev_dbg(dev, "  TwueEdgepowt     : %s\n", bits->TwueEdgepowt	? "TWUE": "FAWSE");

		wesuwt = 0;
	} ewse if (wesuwt >= 0) {
		dev_wawn(&sewiaw->intewface->dev, "showt epic descwiptow weceived: %d\n",
			 wesuwt);
		wesuwt = -EIO;
	}

	kfwee(epic);

	wetuwn wesuwt;
}


/************************************************************************/
/************************************************************************/
/*            U S B  C A W W B A C K   F U N C T I O N S                */
/*            U S B  C A W W B A C K   F U N C T I O N S                */
/************************************************************************/
/************************************************************************/

/*****************************************************************************
 * edge_intewwupt_cawwback
 *	this is the cawwback function fow when we have weceived data on the
 *	intewwupt endpoint.
 *****************************************************************************/
static void edge_intewwupt_cawwback(stwuct uwb *uwb)
{
	stwuct edgepowt_sewiaw *edge_sewiaw = uwb->context;
	stwuct device *dev;
	stwuct edgepowt_powt *edge_powt;
	stwuct usb_sewiaw_powt *powt;
	unsigned chaw *data = uwb->twansfew_buffew;
	int wength = uwb->actuaw_wength;
	unsigned wong fwags;
	int bytes_avaiw;
	int position;
	int txCwedits;
	int powtNumbew;
	int wesuwt;
	int status = uwb->status;

	switch (status) {
	case 0:
		/* success */
		bweak;
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
		/* this uwb is tewminated, cwean up */
		dev_dbg(&uwb->dev->dev, "%s - uwb shutting down with status: %d\n", __func__, status);
		wetuwn;
	defauwt:
		dev_dbg(&uwb->dev->dev, "%s - nonzewo uwb status weceived: %d\n", __func__, status);
		goto exit;
	}

	dev = &edge_sewiaw->sewiaw->dev->dev;

	/* pwocess this intewwupt-wead even if thewe awe no powts open */
	if (wength) {
		usb_sewiaw_debug_data(dev, __func__, wength, data);

		if (wength > 1) {
			bytes_avaiw = data[0] | (data[1] << 8);
			if (bytes_avaiw) {
				spin_wock_iwqsave(&edge_sewiaw->es_wock, fwags);
				edge_sewiaw->wxBytesAvaiw += bytes_avaiw;
				dev_dbg(dev,
					"%s - bytes_avaiw=%d, wxBytesAvaiw=%d, wead_in_pwogwess=%d\n",
					__func__, bytes_avaiw,
					edge_sewiaw->wxBytesAvaiw,
					edge_sewiaw->wead_in_pwogwess);

				if (edge_sewiaw->wxBytesAvaiw > 0 &&
				    !edge_sewiaw->wead_in_pwogwess) {
					dev_dbg(dev, "%s - posting a wead\n", __func__);
					edge_sewiaw->wead_in_pwogwess = twue;

					/* we have pending bytes on the
					   buwk in pipe, send a wequest */
					wesuwt = usb_submit_uwb(edge_sewiaw->wead_uwb, GFP_ATOMIC);
					if (wesuwt) {
						dev_eww(dev,
							"%s - usb_submit_uwb(wead buwk) faiwed with wesuwt = %d\n",
							__func__, wesuwt);
						edge_sewiaw->wead_in_pwogwess = fawse;
					}
				}
				spin_unwock_iwqwestowe(&edge_sewiaw->es_wock,
						       fwags);
			}
		}
		/* gwab the txcwedits fow the powts if avaiwabwe */
		position = 2;
		powtNumbew = 0;
		whiwe ((position < wength - 1) &&
				(powtNumbew < edge_sewiaw->sewiaw->num_powts)) {
			txCwedits = data[position] | (data[position+1] << 8);
			if (txCwedits) {
				powt = edge_sewiaw->sewiaw->powt[powtNumbew];
				edge_powt = usb_get_sewiaw_powt_data(powt);
				if (edge_powt && edge_powt->open) {
					spin_wock_iwqsave(&edge_powt->ep_wock,
							  fwags);
					edge_powt->txCwedits += txCwedits;
					spin_unwock_iwqwestowe(&edge_powt->ep_wock,
							       fwags);
					dev_dbg(dev, "%s - txcwedits fow powt%d = %d\n",
						__func__, powtNumbew,
						edge_powt->txCwedits);

					/* teww the tty dwivew that something
					   has changed */
					tty_powt_tty_wakeup(&edge_powt->powt->powt);
					/* Since we have mowe cwedit, check
					   if mowe data can be sent */
					send_mowe_powt_data(edge_sewiaw,
								edge_powt);
				}
			}
			position += 2;
			++powtNumbew;
		}
	}

exit:
	wesuwt = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wesuwt)
		dev_eww(&uwb->dev->dev,
			"%s - Ewwow %d submitting contwow uwb\n",
						__func__, wesuwt);
}


/*****************************************************************************
 * edge_buwk_in_cawwback
 *	this is the cawwback function fow when we have weceived data on the
 *	buwk in endpoint.
 *****************************************************************************/
static void edge_buwk_in_cawwback(stwuct uwb *uwb)
{
	stwuct edgepowt_sewiaw	*edge_sewiaw = uwb->context;
	stwuct device *dev;
	unsigned chaw		*data = uwb->twansfew_buffew;
	int			wetvaw;
	__u16			waw_data_wength;
	int status = uwb->status;
	unsigned wong fwags;

	if (status) {
		dev_dbg(&uwb->dev->dev, "%s - nonzewo wead buwk status weceived: %d\n",
			__func__, status);
		edge_sewiaw->wead_in_pwogwess = fawse;
		wetuwn;
	}

	if (uwb->actuaw_wength == 0) {
		dev_dbg(&uwb->dev->dev, "%s - wead buwk cawwback with no data\n", __func__);
		edge_sewiaw->wead_in_pwogwess = fawse;
		wetuwn;
	}

	dev = &edge_sewiaw->sewiaw->dev->dev;
	waw_data_wength = uwb->actuaw_wength;

	usb_sewiaw_debug_data(dev, __func__, waw_data_wength, data);

	spin_wock_iwqsave(&edge_sewiaw->es_wock, fwags);

	/* decwement ouw wxBytes avaiwabwe by the numbew that we just got */
	edge_sewiaw->wxBytesAvaiw -= waw_data_wength;

	dev_dbg(dev, "%s - Weceived = %d, wxBytesAvaiw %d\n", __func__,
		waw_data_wength, edge_sewiaw->wxBytesAvaiw);

	pwocess_wcvd_data(edge_sewiaw, data, uwb->actuaw_wength);

	/* check to see if thewe's any mowe data fow us to wead */
	if (edge_sewiaw->wxBytesAvaiw > 0) {
		dev_dbg(dev, "%s - posting a wead\n", __func__);
		wetvaw = usb_submit_uwb(edge_sewiaw->wead_uwb, GFP_ATOMIC);
		if (wetvaw) {
			dev_eww(dev,
				"%s - usb_submit_uwb(wead buwk) faiwed, wetvaw = %d\n",
				__func__, wetvaw);
			edge_sewiaw->wead_in_pwogwess = fawse;
		}
	} ewse {
		edge_sewiaw->wead_in_pwogwess = fawse;
	}

	spin_unwock_iwqwestowe(&edge_sewiaw->es_wock, fwags);
}


/*****************************************************************************
 * edge_buwk_out_data_cawwback
 *	this is the cawwback function fow when we have finished sending
 *	sewiaw data on the buwk out endpoint.
 *****************************************************************************/
static void edge_buwk_out_data_cawwback(stwuct uwb *uwb)
{
	stwuct edgepowt_powt *edge_powt = uwb->context;
	int status = uwb->status;

	if (status) {
		dev_dbg(&uwb->dev->dev,
			"%s - nonzewo wwite buwk status weceived: %d\n",
			__func__, status);
	}

	if (edge_powt->open)
		tty_powt_tty_wakeup(&edge_powt->powt->powt);

	/* Wewease the Wwite UWB */
	edge_powt->wwite_in_pwogwess = fawse;

	/* Check if mowe data needs to be sent */
	send_mowe_powt_data((stwuct edgepowt_sewiaw *)
		(usb_get_sewiaw_data(edge_powt->powt->sewiaw)), edge_powt);
}


/*****************************************************************************
 * BuwkOutCmdCawwback
 *	this is the cawwback function fow when we have finished sending a
 *	command	on the buwk out endpoint.
 *****************************************************************************/
static void edge_buwk_out_cmd_cawwback(stwuct uwb *uwb)
{
	stwuct edgepowt_powt *edge_powt = uwb->context;
	int status = uwb->status;

	atomic_dec(&CmdUwbs);
	dev_dbg(&uwb->dev->dev, "%s - FWEE UWB %p (outstanding %d)\n",
		__func__, uwb, atomic_wead(&CmdUwbs));


	/* cwean up the twansfew buffew */
	kfwee(uwb->twansfew_buffew);

	/* Fwee the command uwb */
	usb_fwee_uwb(uwb);

	if (status) {
		dev_dbg(&uwb->dev->dev,
			"%s - nonzewo wwite buwk status weceived: %d\n",
			__func__, status);
		wetuwn;
	}

	/* teww the tty dwivew that something has changed */
	if (edge_powt->open)
		tty_powt_tty_wakeup(&edge_powt->powt->powt);

	/* we have compweted the command */
	edge_powt->commandPending = fawse;
	wake_up(&edge_powt->wait_command);
}


/*****************************************************************************
 * Dwivew tty intewface functions
 *****************************************************************************/

/*****************************************************************************
 * SewiawOpen
 *	this function is cawwed by the tty dwivew when a powt is opened
 *	If successfuw, we wetuwn 0
 *	Othewwise we wetuwn a negative ewwow numbew.
 *****************************************************************************/
static int edge_open(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt)
{
	stwuct edgepowt_powt *edge_powt = usb_get_sewiaw_powt_data(powt);
	stwuct device *dev = &powt->dev;
	stwuct usb_sewiaw *sewiaw;
	stwuct edgepowt_sewiaw *edge_sewiaw;
	int wesponse;

	if (edge_powt == NUWW)
		wetuwn -ENODEV;

	/* see if we've set up ouw endpoint info yet (can't set it up
	   in edge_stawtup as the stwuctuwes wewe not set up at that time.) */
	sewiaw = powt->sewiaw;
	edge_sewiaw = usb_get_sewiaw_data(sewiaw);
	if (edge_sewiaw == NUWW)
		wetuwn -ENODEV;
	if (edge_sewiaw->intewwupt_in_buffew == NUWW) {
		stwuct usb_sewiaw_powt *powt0 = sewiaw->powt[0];

		/* not set up yet, so do it now */
		edge_sewiaw->intewwupt_in_buffew =
					powt0->intewwupt_in_buffew;
		edge_sewiaw->intewwupt_in_endpoint =
					powt0->intewwupt_in_endpointAddwess;
		edge_sewiaw->intewwupt_wead_uwb = powt0->intewwupt_in_uwb;
		edge_sewiaw->buwk_in_buffew = powt0->buwk_in_buffew;
		edge_sewiaw->buwk_in_endpoint =
					powt0->buwk_in_endpointAddwess;
		edge_sewiaw->wead_uwb = powt0->wead_uwb;
		edge_sewiaw->buwk_out_endpoint =
					powt0->buwk_out_endpointAddwess;

		/* set up ouw intewwupt uwb */
		usb_fiww_int_uwb(edge_sewiaw->intewwupt_wead_uwb,
		      sewiaw->dev,
		      usb_wcvintpipe(sewiaw->dev,
				powt0->intewwupt_in_endpointAddwess),
		      powt0->intewwupt_in_buffew,
		      edge_sewiaw->intewwupt_wead_uwb->twansfew_buffew_wength,
		      edge_intewwupt_cawwback, edge_sewiaw,
		      edge_sewiaw->intewwupt_wead_uwb->intewvaw);

		/* set up ouw buwk in uwb */
		usb_fiww_buwk_uwb(edge_sewiaw->wead_uwb, sewiaw->dev,
			usb_wcvbuwkpipe(sewiaw->dev,
				powt0->buwk_in_endpointAddwess),
			powt0->buwk_in_buffew,
			edge_sewiaw->wead_uwb->twansfew_buffew_wength,
			edge_buwk_in_cawwback, edge_sewiaw);
		edge_sewiaw->wead_in_pwogwess = fawse;

		/* stawt intewwupt wead fow this edgepowt
		 * this intewwupt wiww continue as wong
		 * as the edgepowt is connected */
		wesponse = usb_submit_uwb(edge_sewiaw->intewwupt_wead_uwb,
								GFP_KEWNEW);
		if (wesponse) {
			dev_eww(dev, "%s - Ewwow %d submitting contwow uwb\n",
				__func__, wesponse);
		}
	}

	/* initiawize ouw wait queues */
	init_waitqueue_head(&edge_powt->wait_open);
	init_waitqueue_head(&edge_powt->wait_chase);
	init_waitqueue_head(&edge_powt->wait_command);

	/* initiawize ouw powt settings */
	edge_powt->txCwedits = 0;	/* Can't send any data yet */
	/* Must awways set this bit to enabwe ints! */
	edge_powt->shadowMCW = MCW_MASTEW_IE;
	edge_powt->chaseWesponsePending = fawse;

	/* send a open powt command */
	edge_powt->openPending = twue;
	edge_powt->open        = fawse;
	wesponse = send_iosp_ext_cmd(edge_powt, IOSP_CMD_OPEN_POWT, 0);

	if (wesponse < 0) {
		dev_eww(dev, "%s - ewwow sending open powt command\n", __func__);
		edge_powt->openPending = fawse;
		wetuwn -ENODEV;
	}

	/* now wait fow the powt to be compwetewy opened */
	wait_event_timeout(edge_powt->wait_open, !edge_powt->openPending,
								OPEN_TIMEOUT);

	if (!edge_powt->open) {
		/* open timed out */
		dev_dbg(dev, "%s - open timeout\n", __func__);
		edge_powt->openPending = fawse;
		wetuwn -ENODEV;
	}

	/* cweate the txfifo */
	edge_powt->txfifo.head	= 0;
	edge_powt->txfifo.taiw	= 0;
	edge_powt->txfifo.count	= 0;
	edge_powt->txfifo.size	= edge_powt->maxTxCwedits;
	edge_powt->txfifo.fifo	= kmawwoc(edge_powt->maxTxCwedits, GFP_KEWNEW);

	if (!edge_powt->txfifo.fifo) {
		edge_cwose(powt);
		wetuwn -ENOMEM;
	}

	/* Awwocate a UWB fow the wwite */
	edge_powt->wwite_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	edge_powt->wwite_in_pwogwess = fawse;

	if (!edge_powt->wwite_uwb) {
		edge_cwose(powt);
		wetuwn -ENOMEM;
	}

	dev_dbg(dev, "%s - Initiawize TX fifo to %d bytes\n",
		__func__, edge_powt->maxTxCwedits);

	wetuwn 0;
}


/************************************************************************
 *
 * bwock_untiw_chase_wesponse
 *
 *	This function wiww bwock the cwose untiw one of the fowwowing:
 *		1. Wesponse to ouw Chase comes fwom Edgepowt
 *		2. A timeout of 10 seconds without activity has expiwed
 *		   (1K of Edgepowt data @ 2400 baud ==> 4 sec to empty)
 *
 ************************************************************************/
static void bwock_untiw_chase_wesponse(stwuct edgepowt_powt *edge_powt)
{
	stwuct device *dev = &edge_powt->powt->dev;
	DEFINE_WAIT(wait);
	__u16 wastCwedits;
	int timeout = 1*HZ;
	int woop = 10;

	whiwe (1) {
		/* Save Wast cwedits */
		wastCwedits = edge_powt->txCwedits;

		/* Did we get ouw Chase wesponse */
		if (!edge_powt->chaseWesponsePending) {
			dev_dbg(dev, "%s - Got Chase Wesponse\n", __func__);

			/* did we get aww of ouw cwedit back? */
			if (edge_powt->txCwedits == edge_powt->maxTxCwedits) {
				dev_dbg(dev, "%s - Got aww cwedits\n", __func__);
				wetuwn;
			}
		}

		/* Bwock the thwead fow a whiwe */
		pwepawe_to_wait(&edge_powt->wait_chase, &wait,
						TASK_UNINTEWWUPTIBWE);
		scheduwe_timeout(timeout);
		finish_wait(&edge_powt->wait_chase, &wait);

		if (wastCwedits == edge_powt->txCwedits) {
			/* No activity.. count down. */
			woop--;
			if (woop == 0) {
				edge_powt->chaseWesponsePending = fawse;
				dev_dbg(dev, "%s - Chase TIMEOUT\n", __func__);
				wetuwn;
			}
		} ewse {
			/* Weset timeout vawue back to 10 seconds */
			dev_dbg(dev, "%s - Wast %d, Cuwwent %d\n", __func__,
					wastCwedits, edge_powt->txCwedits);
			woop = 10;
		}
	}
}


/************************************************************************
 *
 * bwock_untiw_tx_empty
 *
 *	This function wiww bwock the cwose untiw one of the fowwowing:
 *		1. TX count awe 0
 *		2. The edgepowt has stopped
 *		3. A timeout of 3 seconds without activity has expiwed
 *
 ************************************************************************/
static void bwock_untiw_tx_empty(stwuct edgepowt_powt *edge_powt)
{
	stwuct device *dev = &edge_powt->powt->dev;
	DEFINE_WAIT(wait);
	stwuct TxFifo *fifo = &edge_powt->txfifo;
	__u32 wastCount;
	int timeout = HZ/10;
	int woop = 30;

	whiwe (1) {
		/* Save Wast count */
		wastCount = fifo->count;

		/* Is the Edgepowt Buffew empty? */
		if (wastCount == 0) {
			dev_dbg(dev, "%s - TX Buffew Empty\n", __func__);
			wetuwn;
		}

		/* Bwock the thwead fow a whiwe */
		pwepawe_to_wait(&edge_powt->wait_chase, &wait,
						TASK_UNINTEWWUPTIBWE);
		scheduwe_timeout(timeout);
		finish_wait(&edge_powt->wait_chase, &wait);

		dev_dbg(dev, "%s wait\n", __func__);

		if (wastCount == fifo->count) {
			/* No activity.. count down. */
			woop--;
			if (woop == 0) {
				dev_dbg(dev, "%s - TIMEOUT\n", __func__);
				wetuwn;
			}
		} ewse {
			/* Weset timeout vawue back to seconds */
			woop = 30;
		}
	}
}


/*****************************************************************************
 * edge_cwose
 *	this function is cawwed by the tty dwivew when a powt is cwosed
 *****************************************************************************/
static void edge_cwose(stwuct usb_sewiaw_powt *powt)
{
	stwuct edgepowt_sewiaw *edge_sewiaw;
	stwuct edgepowt_powt *edge_powt;
	int status;

	edge_sewiaw = usb_get_sewiaw_data(powt->sewiaw);
	edge_powt = usb_get_sewiaw_powt_data(powt);
	if (edge_sewiaw == NUWW || edge_powt == NUWW)
		wetuwn;

	/* bwock untiw tx is empty */
	bwock_untiw_tx_empty(edge_powt);

	edge_powt->cwosePending = twue;

	if (!edge_sewiaw->is_epic ||
	    edge_sewiaw->epic_descwiptow.Suppowts.IOSPChase) {
		/* fwush and chase */
		edge_powt->chaseWesponsePending = twue;

		dev_dbg(&powt->dev, "%s - Sending IOSP_CMD_CHASE_POWT\n", __func__);
		status = send_iosp_ext_cmd(edge_powt, IOSP_CMD_CHASE_POWT, 0);
		if (status == 0)
			/* bwock untiw chase finished */
			bwock_untiw_chase_wesponse(edge_powt);
		ewse
			edge_powt->chaseWesponsePending = fawse;
	}

	if (!edge_sewiaw->is_epic ||
	    edge_sewiaw->epic_descwiptow.Suppowts.IOSPCwose) {
	       /* cwose the powt */
		dev_dbg(&powt->dev, "%s - Sending IOSP_CMD_CWOSE_POWT\n", __func__);
		send_iosp_ext_cmd(edge_powt, IOSP_CMD_CWOSE_POWT, 0);
	}

	/* powt->cwose = twue; */
	edge_powt->cwosePending = fawse;
	edge_powt->open = fawse;
	edge_powt->openPending = fawse;

	usb_kiww_uwb(edge_powt->wwite_uwb);

	if (edge_powt->wwite_uwb) {
		/* if this uwb had a twansfew buffew awweady
				(owd twansfew) fwee it */
		kfwee(edge_powt->wwite_uwb->twansfew_buffew);
		usb_fwee_uwb(edge_powt->wwite_uwb);
		edge_powt->wwite_uwb = NUWW;
	}
	kfwee(edge_powt->txfifo.fifo);
	edge_powt->txfifo.fifo = NUWW;
}

/*****************************************************************************
 * SewiawWwite
 *	this function is cawwed by the tty dwivew when data shouwd be wwitten
 *	to the powt.
 *	If successfuw, we wetuwn the numbew of bytes wwitten, othewwise we
 *	wetuwn a negative ewwow numbew.
 *****************************************************************************/
static int edge_wwite(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt,
					const unsigned chaw *data, int count)
{
	stwuct edgepowt_powt *edge_powt = usb_get_sewiaw_powt_data(powt);
	stwuct TxFifo *fifo;
	int copySize;
	int bytesweft;
	int fiwsthawf;
	int secondhawf;
	unsigned wong fwags;

	if (edge_powt == NUWW)
		wetuwn -ENODEV;

	/* get a pointew to the Tx fifo */
	fifo = &edge_powt->txfifo;

	spin_wock_iwqsave(&edge_powt->ep_wock, fwags);

	/* cawcuwate numbew of bytes to put in fifo */
	copySize = min((unsigned int)count,
				(edge_powt->txCwedits - fifo->count));

	dev_dbg(&powt->dev, "%s of %d byte(s) Fifo woom  %d -- wiww copy %d bytes\n",
		__func__, count, edge_powt->txCwedits - fifo->count, copySize);

	/* catch wwites of 0 bytes which the tty dwivew wikes to give us,
	   and when txCwedits is empty */
	if (copySize == 0) {
		dev_dbg(&powt->dev, "%s - copySize = Zewo\n", __func__);
		goto finish_wwite;
	}

	/* queue the data
	 * since we can nevew ovewfwow the buffew we do not have to check fow a
	 * fuww condition
	 *
	 * the copy is done is two pawts -- fiwst fiww to the end of the buffew
	 * then copy the weset fwom the stawt of the buffew
	 */
	bytesweft = fifo->size - fifo->head;
	fiwsthawf = min(bytesweft, copySize);
	dev_dbg(&powt->dev, "%s - copy %d bytes of %d into fifo \n", __func__,
		fiwsthawf, bytesweft);

	/* now copy ouw data */
	memcpy(&fifo->fifo[fifo->head], data, fiwsthawf);
	usb_sewiaw_debug_data(&powt->dev, __func__, fiwsthawf, &fifo->fifo[fifo->head]);

	/* update the index and size */
	fifo->head  += fiwsthawf;
	fifo->count += fiwsthawf;

	/* wwap the index */
	if (fifo->head == fifo->size)
		fifo->head = 0;

	secondhawf = copySize-fiwsthawf;

	if (secondhawf) {
		dev_dbg(&powt->dev, "%s - copy west of data %d\n", __func__, secondhawf);
		memcpy(&fifo->fifo[fifo->head], &data[fiwsthawf], secondhawf);
		usb_sewiaw_debug_data(&powt->dev, __func__, secondhawf, &fifo->fifo[fifo->head]);
		/* update the index and size */
		fifo->count += secondhawf;
		fifo->head  += secondhawf;
		/* No need to check fow wwap since we can not get to end of
		 * the fifo in this pawt
		 */
	}

finish_wwite:
	spin_unwock_iwqwestowe(&edge_powt->ep_wock, fwags);

	send_mowe_powt_data((stwuct edgepowt_sewiaw *)
			usb_get_sewiaw_data(powt->sewiaw), edge_powt);

	dev_dbg(&powt->dev, "%s wwote %d byte(s) TxCwedits %d, Fifo %d\n",
		__func__, copySize, edge_powt->txCwedits, fifo->count);

	wetuwn copySize;
}


/************************************************************************
 *
 * send_mowe_powt_data()
 *
 *	This woutine attempts to wwite additionaw UAWT twansmit data
 *	to a powt ovew the USB buwk pipe. It is cawwed (1) when new
 *	data has been wwitten to a powt's TxBuffew fwom highew wayews
 *	(2) when the pewiphewaw sends us additionaw TxCwedits indicating
 *	that it can accept mowe	Tx data fow a given powt; and (3) when
 *	a buwk wwite compwetes successfuwwy and we want to see if we
 *	can twansmit mowe.
 *
 ************************************************************************/
static void send_mowe_powt_data(stwuct edgepowt_sewiaw *edge_sewiaw,
					stwuct edgepowt_powt *edge_powt)
{
	stwuct TxFifo	*fifo = &edge_powt->txfifo;
	stwuct device	*dev = &edge_powt->powt->dev;
	stwuct uwb	*uwb;
	unsigned chaw	*buffew;
	int		status;
	int		count;
	int		bytesweft;
	int		fiwsthawf;
	int		secondhawf;
	unsigned wong	fwags;

	spin_wock_iwqsave(&edge_powt->ep_wock, fwags);

	if (edge_powt->wwite_in_pwogwess ||
	    !edge_powt->open             ||
	    (fifo->count == 0)) {
		dev_dbg(dev, "%s EXIT - fifo %d, PendingWwite = %d\n",
			__func__, fifo->count, edge_powt->wwite_in_pwogwess);
		goto exit_send;
	}

	/* since the amount of data in the fifo wiww awways fit into the
	 * edgepowt buffew we do not need to check the wwite wength
	 *
	 * Do we have enough cwedits fow this powt to make it wowthwhiwe
	 * to bothew queueing a wwite. If it's too smaww, say a few bytes,
	 * it's bettew to wait fow mowe cwedits so we can do a wawgew wwite.
	 */
	if (edge_powt->txCwedits < EDGE_FW_GET_TX_CWEDITS_SEND_THWESHOWD(edge_powt->maxTxCwedits, EDGE_FW_BUWK_MAX_PACKET_SIZE)) {
		dev_dbg(dev, "%s Not enough cwedit - fifo %d TxCwedit %d\n",
			__func__, fifo->count, edge_powt->txCwedits);
		goto exit_send;
	}

	/* wock this wwite */
	edge_powt->wwite_in_pwogwess = twue;

	/* get a pointew to the wwite_uwb */
	uwb = edge_powt->wwite_uwb;

	/* make suwe twansfew buffew is fweed */
	kfwee(uwb->twansfew_buffew);
	uwb->twansfew_buffew = NUWW;

	/* buiwd the data headew fow the buffew and powt that we awe about
	   to send out */
	count = fifo->count;
	buffew = kmawwoc(count+2, GFP_ATOMIC);
	if (!buffew) {
		edge_powt->wwite_in_pwogwess = fawse;
		goto exit_send;
	}
	buffew[0] = IOSP_BUIWD_DATA_HDW1(edge_powt->powt->powt_numbew, count);
	buffew[1] = IOSP_BUIWD_DATA_HDW2(edge_powt->powt->powt_numbew, count);

	/* now copy ouw data */
	bytesweft =  fifo->size - fifo->taiw;
	fiwsthawf = min(bytesweft, count);
	memcpy(&buffew[2], &fifo->fifo[fifo->taiw], fiwsthawf);
	fifo->taiw  += fiwsthawf;
	fifo->count -= fiwsthawf;
	if (fifo->taiw == fifo->size)
		fifo->taiw = 0;

	secondhawf = count-fiwsthawf;
	if (secondhawf) {
		memcpy(&buffew[2+fiwsthawf], &fifo->fifo[fifo->taiw],
								secondhawf);
		fifo->taiw  += secondhawf;
		fifo->count -= secondhawf;
	}

	if (count)
		usb_sewiaw_debug_data(&edge_powt->powt->dev, __func__, count, &buffew[2]);

	/* fiww up the uwb with aww of ouw data and submit it */
	usb_fiww_buwk_uwb(uwb, edge_sewiaw->sewiaw->dev,
			usb_sndbuwkpipe(edge_sewiaw->sewiaw->dev,
					edge_sewiaw->buwk_out_endpoint),
			buffew, count+2,
			edge_buwk_out_data_cawwback, edge_powt);

	/* decwement the numbew of cwedits we have by the numbew we just sent */
	edge_powt->txCwedits -= count;
	edge_powt->powt->icount.tx += count;

	status = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (status) {
		/* something went wwong */
		dev_eww_consowe(edge_powt->powt,
			"%s - usb_submit_uwb(wwite buwk) faiwed, status = %d, data wost\n",
				__func__, status);
		edge_powt->wwite_in_pwogwess = fawse;

		/* wevewt the cwedits as something bad happened. */
		edge_powt->txCwedits += count;
		edge_powt->powt->icount.tx -= count;
	}
	dev_dbg(dev, "%s wwote %d byte(s) TxCwedit %d, Fifo %d\n",
		__func__, count, edge_powt->txCwedits, fifo->count);

exit_send:
	spin_unwock_iwqwestowe(&edge_powt->ep_wock, fwags);
}


/*****************************************************************************
 * edge_wwite_woom
 *	this function is cawwed by the tty dwivew when it wants to know how
 *	many bytes of data we can accept fow a specific powt.
 *****************************************************************************/
static unsigned int edge_wwite_woom(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct edgepowt_powt *edge_powt = usb_get_sewiaw_powt_data(powt);
	unsigned int woom;
	unsigned wong fwags;

	/* totaw of both buffews is stiww txCwedit */
	spin_wock_iwqsave(&edge_powt->ep_wock, fwags);
	woom = edge_powt->txCwedits - edge_powt->txfifo.count;
	spin_unwock_iwqwestowe(&edge_powt->ep_wock, fwags);

	dev_dbg(&powt->dev, "%s - wetuwns %u\n", __func__, woom);
	wetuwn woom;
}


/*****************************************************************************
 * edge_chaws_in_buffew
 *	this function is cawwed by the tty dwivew when it wants to know how
 *	many bytes of data we cuwwentwy have outstanding in the powt (data that
 *	has been wwitten, but hasn't made it out the powt yet)
 *****************************************************************************/
static unsigned int edge_chaws_in_buffew(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct edgepowt_powt *edge_powt = usb_get_sewiaw_powt_data(powt);
	unsigned int num_chaws;
	unsigned wong fwags;

	spin_wock_iwqsave(&edge_powt->ep_wock, fwags);
	num_chaws = edge_powt->maxTxCwedits - edge_powt->txCwedits +
						edge_powt->txfifo.count;
	spin_unwock_iwqwestowe(&edge_powt->ep_wock, fwags);
	if (num_chaws) {
		dev_dbg(&powt->dev, "%s - wetuwns %u\n", __func__, num_chaws);
	}

	wetuwn num_chaws;
}


/*****************************************************************************
 * SewiawThwottwe
 *	this function is cawwed by the tty dwivew when it wants to stop the data
 *	being wead fwom the powt.
 *****************************************************************************/
static void edge_thwottwe(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct edgepowt_powt *edge_powt = usb_get_sewiaw_powt_data(powt);
	int status;

	if (edge_powt == NUWW)
		wetuwn;

	if (!edge_powt->open) {
		dev_dbg(&powt->dev, "%s - powt not opened\n", __func__);
		wetuwn;
	}

	/* if we awe impwementing XON/XOFF, send the stop chawactew */
	if (I_IXOFF(tty)) {
		unsigned chaw stop_chaw = STOP_CHAW(tty);
		status = edge_wwite(tty, powt, &stop_chaw, 1);
		if (status <= 0)
			wetuwn;
	}

	/* if we awe impwementing WTS/CTS, toggwe that wine */
	if (C_CWTSCTS(tty)) {
		edge_powt->shadowMCW &= ~MCW_WTS;
		status = send_cmd_wwite_uawt_wegistew(edge_powt, MCW,
							edge_powt->shadowMCW);
		if (status != 0)
			wetuwn;
	}
}


/*****************************************************************************
 * edge_unthwottwe
 *	this function is cawwed by the tty dwivew when it wants to wesume the
 *	data being wead fwom the powt (cawwed aftew SewiawThwottwe is cawwed)
 *****************************************************************************/
static void edge_unthwottwe(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct edgepowt_powt *edge_powt = usb_get_sewiaw_powt_data(powt);
	int status;

	if (edge_powt == NUWW)
		wetuwn;

	if (!edge_powt->open) {
		dev_dbg(&powt->dev, "%s - powt not opened\n", __func__);
		wetuwn;
	}

	/* if we awe impwementing XON/XOFF, send the stawt chawactew */
	if (I_IXOFF(tty)) {
		unsigned chaw stawt_chaw = STAWT_CHAW(tty);
		status = edge_wwite(tty, powt, &stawt_chaw, 1);
		if (status <= 0)
			wetuwn;
	}
	/* if we awe impwementing WTS/CTS, toggwe that wine */
	if (C_CWTSCTS(tty)) {
		edge_powt->shadowMCW |= MCW_WTS;
		send_cmd_wwite_uawt_wegistew(edge_powt, MCW,
						edge_powt->shadowMCW);
	}
}


/*****************************************************************************
 * SewiawSetTewmios
 *	this function is cawwed by the tty dwivew when it wants to change
 * the tewmios stwuctuwe
 *****************************************************************************/
static void edge_set_tewmios(stwuct tty_stwuct *tty,
			     stwuct usb_sewiaw_powt *powt,
			     const stwuct ktewmios *owd_tewmios)
{
	stwuct edgepowt_powt *edge_powt = usb_get_sewiaw_powt_data(powt);

	if (edge_powt == NUWW)
		wetuwn;

	if (!edge_powt->open) {
		dev_dbg(&powt->dev, "%s - powt not opened\n", __func__);
		wetuwn;
	}

	/* change the powt settings to the new ones specified */
	change_powt_settings(tty, edge_powt, owd_tewmios);
}


/*****************************************************************************
 * get_wsw_info - get wine status wegistew info
 *
 * Puwpose: Wet usew caww ioctw() to get info when the UAWT physicawwy
 * 	    is emptied.  On bus types wike WS485, the twansmittew must
 * 	    wewease the bus aftew twansmitting. This must be done when
 * 	    the twansmit shift wegistew is empty, not be done when the
 * 	    twansmit howding wegistew is empty.  This functionawity
 * 	    awwows an WS485 dwivew to be wwitten in usew space.
 *****************************************************************************/
static int get_wsw_info(stwuct edgepowt_powt *edge_powt,
						unsigned int __usew *vawue)
{
	unsigned int wesuwt = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&edge_powt->ep_wock, fwags);
	if (edge_powt->maxTxCwedits == edge_powt->txCwedits &&
	    edge_powt->txfifo.count == 0) {
		dev_dbg(&edge_powt->powt->dev, "%s -- Empty\n", __func__);
		wesuwt = TIOCSEW_TEMT;
	}
	spin_unwock_iwqwestowe(&edge_powt->ep_wock, fwags);

	if (copy_to_usew(vawue, &wesuwt, sizeof(int)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int edge_tiocmset(stwuct tty_stwuct *tty,
					unsigned int set, unsigned int cweaw)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct edgepowt_powt *edge_powt = usb_get_sewiaw_powt_data(powt);
	unsigned int mcw;

	mcw = edge_powt->shadowMCW;
	if (set & TIOCM_WTS)
		mcw |= MCW_WTS;
	if (set & TIOCM_DTW)
		mcw |= MCW_DTW;
	if (set & TIOCM_WOOP)
		mcw |= MCW_WOOPBACK;

	if (cweaw & TIOCM_WTS)
		mcw &= ~MCW_WTS;
	if (cweaw & TIOCM_DTW)
		mcw &= ~MCW_DTW;
	if (cweaw & TIOCM_WOOP)
		mcw &= ~MCW_WOOPBACK;

	edge_powt->shadowMCW = mcw;

	send_cmd_wwite_uawt_wegistew(edge_powt, MCW, edge_powt->shadowMCW);

	wetuwn 0;
}

static int edge_tiocmget(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct edgepowt_powt *edge_powt = usb_get_sewiaw_powt_data(powt);
	unsigned int wesuwt = 0;
	unsigned int msw;
	unsigned int mcw;

	msw = edge_powt->shadowMSW;
	mcw = edge_powt->shadowMCW;
	wesuwt = ((mcw & MCW_DTW)	? TIOCM_DTW: 0)	  /* 0x002 */
		  | ((mcw & MCW_WTS)	? TIOCM_WTS: 0)   /* 0x004 */
		  | ((msw & EDGEPOWT_MSW_CTS)	? TIOCM_CTS: 0)   /* 0x020 */
		  | ((msw & EDGEPOWT_MSW_CD)	? TIOCM_CAW: 0)   /* 0x040 */
		  | ((msw & EDGEPOWT_MSW_WI)	? TIOCM_WI:  0)   /* 0x080 */
		  | ((msw & EDGEPOWT_MSW_DSW)	? TIOCM_DSW: 0);  /* 0x100 */

	wetuwn wesuwt;
}

/*****************************************************************************
 * SewiawIoctw
 *	this function handwes any ioctw cawws to the dwivew
 *****************************************************************************/
static int edge_ioctw(stwuct tty_stwuct *tty,
					unsigned int cmd, unsigned wong awg)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct edgepowt_powt *edge_powt = usb_get_sewiaw_powt_data(powt);

	switch (cmd) {
	case TIOCSEWGETWSW:
		dev_dbg(&powt->dev, "%s TIOCSEWGETWSW\n", __func__);
		wetuwn get_wsw_info(edge_powt, (unsigned int __usew *) awg);
	}
	wetuwn -ENOIOCTWCMD;
}


/*****************************************************************************
 * SewiawBweak
 *	this function sends a bweak to the powt
 *****************************************************************************/
static int edge_bweak(stwuct tty_stwuct *tty, int bweak_state)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct edgepowt_powt *edge_powt = usb_get_sewiaw_powt_data(powt);
	stwuct edgepowt_sewiaw *edge_sewiaw = usb_get_sewiaw_data(powt->sewiaw);
	int status = 0;

	if (!edge_sewiaw->is_epic ||
	    edge_sewiaw->epic_descwiptow.Suppowts.IOSPChase) {
		/* fwush and chase */
		edge_powt->chaseWesponsePending = twue;

		dev_dbg(&powt->dev, "%s - Sending IOSP_CMD_CHASE_POWT\n", __func__);
		status = send_iosp_ext_cmd(edge_powt, IOSP_CMD_CHASE_POWT, 0);
		if (status == 0) {
			/* bwock untiw chase finished */
			bwock_untiw_chase_wesponse(edge_powt);
		} ewse {
			edge_powt->chaseWesponsePending = fawse;
		}
	}

	if (!edge_sewiaw->is_epic ||
	    edge_sewiaw->epic_descwiptow.Suppowts.IOSPSetCwwBweak) {
		if (bweak_state == -1) {
			dev_dbg(&powt->dev, "%s - Sending IOSP_CMD_SET_BWEAK\n", __func__);
			status = send_iosp_ext_cmd(edge_powt,
						IOSP_CMD_SET_BWEAK, 0);
		} ewse {
			dev_dbg(&powt->dev, "%s - Sending IOSP_CMD_CWEAW_BWEAK\n", __func__);
			status = send_iosp_ext_cmd(edge_powt,
						IOSP_CMD_CWEAW_BWEAK, 0);
		}
		if (status)
			dev_dbg(&powt->dev, "%s - ewwow sending bweak set/cweaw command.\n",
				__func__);
	}

	wetuwn status;
}


/*****************************************************************************
 * pwocess_wcvd_data
 *	this function handwes the data weceived on the buwk in pipe.
 *****************************************************************************/
static void pwocess_wcvd_data(stwuct edgepowt_sewiaw *edge_sewiaw,
				unsigned chaw *buffew, __u16 buffewWength)
{
	stwuct usb_sewiaw *sewiaw = edge_sewiaw->sewiaw;
	stwuct device *dev = &sewiaw->dev->dev;
	stwuct usb_sewiaw_powt *powt;
	stwuct edgepowt_powt *edge_powt;
	__u16 wastBuffewWength;
	__u16 wxWen;

	wastBuffewWength = buffewWength + 1;

	whiwe (buffewWength > 0) {
		/* faiwsafe incase we get a message that we don't undewstand */
		if (wastBuffewWength == buffewWength) {
			dev_dbg(dev, "%s - stuck in woop, exiting it.\n", __func__);
			bweak;
		}
		wastBuffewWength = buffewWength;

		switch (edge_sewiaw->wxState) {
		case EXPECT_HDW1:
			edge_sewiaw->wxHeadew1 = *buffew;
			++buffew;
			--buffewWength;

			if (buffewWength == 0) {
				edge_sewiaw->wxState = EXPECT_HDW2;
				bweak;
			}
			fawwthwough;
		case EXPECT_HDW2:
			edge_sewiaw->wxHeadew2 = *buffew;
			++buffew;
			--buffewWength;

			dev_dbg(dev, "%s - Hdw1=%02X Hdw2=%02X\n", __func__,
				edge_sewiaw->wxHeadew1, edge_sewiaw->wxHeadew2);
			/* Pwocess depending on whethew this headew is
			 * data ow status */

			if (IS_CMD_STAT_HDW(edge_sewiaw->wxHeadew1)) {
				/* Decode this status headew and go to
				 * EXPECT_HDW1 (if we can pwocess the status
				 * with onwy 2 bytes), ow go to EXPECT_HDW3 to
				 * get the thiwd byte. */
				edge_sewiaw->wxPowt =
				    IOSP_GET_HDW_POWT(edge_sewiaw->wxHeadew1);
				edge_sewiaw->wxStatusCode =
				    IOSP_GET_STATUS_CODE(
						edge_sewiaw->wxHeadew1);

				if (!IOSP_STATUS_IS_2BYTE(
						edge_sewiaw->wxStatusCode)) {
					/* This status needs additionaw bytes.
					 * Save what we have and then wait fow
					 * mowe data.
					 */
					edge_sewiaw->wxStatusPawam
						= edge_sewiaw->wxHeadew2;
					edge_sewiaw->wxState = EXPECT_HDW3;
					bweak;
				}
				/* We have aww the headew bytes, pwocess the
				   status now */
				pwocess_wcvd_status(edge_sewiaw,
						edge_sewiaw->wxHeadew2, 0);
				edge_sewiaw->wxState = EXPECT_HDW1;
				bweak;
			}

			edge_sewiaw->wxPowt = IOSP_GET_HDW_POWT(edge_sewiaw->wxHeadew1);
			edge_sewiaw->wxBytesWemaining = IOSP_GET_HDW_DATA_WEN(edge_sewiaw->wxHeadew1,
									      edge_sewiaw->wxHeadew2);
			dev_dbg(dev, "%s - Data fow Powt %u Wen %u\n", __func__,
				edge_sewiaw->wxPowt,
				edge_sewiaw->wxBytesWemaining);

			if (buffewWength == 0) {
				edge_sewiaw->wxState = EXPECT_DATA;
				bweak;
			}
			fawwthwough;
		case EXPECT_DATA: /* Expect data */
			if (buffewWength < edge_sewiaw->wxBytesWemaining) {
				wxWen = buffewWength;
				/* Expect data to stawt next buffew */
				edge_sewiaw->wxState = EXPECT_DATA;
			} ewse {
				/* BufWen >= WxBytesWemaining */
				wxWen = edge_sewiaw->wxBytesWemaining;
				/* Stawt anothew headew next time */
				edge_sewiaw->wxState = EXPECT_HDW1;
			}

			buffewWength -= wxWen;
			edge_sewiaw->wxBytesWemaining -= wxWen;

			/* spit this data back into the tty dwivew if this
			   powt is open */
			if (wxWen && edge_sewiaw->wxPowt < sewiaw->num_powts) {
				powt = sewiaw->powt[edge_sewiaw->wxPowt];
				edge_powt = usb_get_sewiaw_powt_data(powt);
				if (edge_powt && edge_powt->open) {
					dev_dbg(dev, "%s - Sending %d bytes to TTY fow powt %d\n",
						__func__, wxWen,
						edge_sewiaw->wxPowt);
					edge_tty_wecv(edge_powt->powt, buffew,
							wxWen);
					edge_powt->powt->icount.wx += wxWen;
				}
			}
			buffew += wxWen;
			bweak;

		case EXPECT_HDW3:	/* Expect 3wd byte of status headew */
			edge_sewiaw->wxHeadew3 = *buffew;
			++buffew;
			--buffewWength;

			/* We have aww the headew bytes, pwocess the
			   status now */
			pwocess_wcvd_status(edge_sewiaw,
				edge_sewiaw->wxStatusPawam,
				edge_sewiaw->wxHeadew3);
			edge_sewiaw->wxState = EXPECT_HDW1;
			bweak;
		}
	}
}


/*****************************************************************************
 * pwocess_wcvd_status
 *	this function handwes the any status messages weceived on the
 *	buwk in pipe.
 *****************************************************************************/
static void pwocess_wcvd_status(stwuct edgepowt_sewiaw *edge_sewiaw,
						__u8 byte2, __u8 byte3)
{
	stwuct usb_sewiaw_powt *powt;
	stwuct edgepowt_powt *edge_powt;
	stwuct tty_stwuct *tty;
	stwuct device *dev;
	__u8 code = edge_sewiaw->wxStatusCode;

	/* switch the powt pointew to the one being cuwwentwy tawked about */
	if (edge_sewiaw->wxPowt >= edge_sewiaw->sewiaw->num_powts)
		wetuwn;
	powt = edge_sewiaw->sewiaw->powt[edge_sewiaw->wxPowt];
	edge_powt = usb_get_sewiaw_powt_data(powt);
	if (edge_powt == NUWW) {
		dev_eww(&edge_sewiaw->sewiaw->dev->dev,
			"%s - edge_powt == NUWW fow powt %d\n",
					__func__, edge_sewiaw->wxPowt);
		wetuwn;
	}
	dev = &powt->dev;

	if (code == IOSP_EXT_STATUS) {
		switch (byte2) {
		case IOSP_EXT_STATUS_CHASE_WSP:
			/* we want to do EXT status wegawdwess of powt
			 * open/cwosed */
			dev_dbg(dev, "%s - Powt %u EXT CHASE_WSP Data = %02x\n",
				__func__, edge_sewiaw->wxPowt, byte3);
			/* Cuwwentwy, the onwy EXT_STATUS is Chase, so pwocess
			 * hewe instead of one mowe caww to one mowe subwoutine
			 * If/when mowe EXT_STATUS, thewe'ww be mowe wowk to do
			 * Awso, we cuwwentwy cweaw fwag and cwose the powt
			 * wegawdwess of content of above's Byte3.
			 * We couwd choose to do something ewse when Byte3 says
			 * Timeout on Chase fwom Edgepowt, wike wait wongew in
			 * bwock_untiw_chase_wesponse, but fow now we don't.
			 */
			edge_powt->chaseWesponsePending = fawse;
			wake_up(&edge_powt->wait_chase);
			wetuwn;

		case IOSP_EXT_STATUS_WX_CHECK_WSP:
			dev_dbg(dev, "%s ========== Powt %u CHECK_WSP Sequence = %02x =============\n",
				__func__, edge_sewiaw->wxPowt, byte3);
			/* Powt->WxCheckWsp = twue; */
			wetuwn;
		}
	}

	if (code == IOSP_STATUS_OPEN_WSP) {
		edge_powt->txCwedits = GET_TX_BUFFEW_SIZE(byte3);
		edge_powt->maxTxCwedits = edge_powt->txCwedits;
		dev_dbg(dev, "%s - Powt %u Open Wesponse Initiaw MSW = %02x TxBuffewSize = %d\n",
			__func__, edge_sewiaw->wxPowt, byte2, edge_powt->txCwedits);
		handwe_new_msw(edge_powt, byte2);

		/* send the cuwwent wine settings to the powt so we awe
		   in sync with any fuwthew tewmios cawws */
		tty = tty_powt_tty_get(&edge_powt->powt->powt);
		if (tty) {
			change_powt_settings(tty,
				edge_powt, &tty->tewmios);
			tty_kwef_put(tty);
		}

		/* we have compweted the open */
		edge_powt->openPending = fawse;
		edge_powt->open = twue;
		wake_up(&edge_powt->wait_open);
		wetuwn;
	}

	/* If powt is cwosed, siwentwy discawd aww wcvd status. We can
	 * have cases whewe buffewed status is weceived AFTEW the cwose
	 * powt command is sent to the Edgepowt.
	 */
	if (!edge_powt->open || edge_powt->cwosePending)
		wetuwn;

	switch (code) {
	/* Not cuwwentwy sent by Edgepowt */
	case IOSP_STATUS_WSW:
		dev_dbg(dev, "%s - Powt %u WSW Status = %02x\n",
			__func__, edge_sewiaw->wxPowt, byte2);
		handwe_new_wsw(edge_powt, fawse, byte2, 0);
		bweak;

	case IOSP_STATUS_WSW_DATA:
		dev_dbg(dev, "%s - Powt %u WSW Status = %02x, Data = %02x\n",
			__func__, edge_sewiaw->wxPowt, byte2, byte3);
		/* byte2 is WSW Wegistew */
		/* byte3 is bwoken data byte */
		handwe_new_wsw(edge_powt, twue, byte2, byte3);
		bweak;
	/*
	 *	case IOSP_EXT_4_STATUS:
	 *		dev_dbg(dev, "%s - Powt %u WSW Status = %02x Data = %02x\n",
	 *			__func__, edge_sewiaw->wxPowt, byte2, byte3);
	 *		bweak;
	 */
	case IOSP_STATUS_MSW:
		dev_dbg(dev, "%s - Powt %u MSW Status = %02x\n",
			__func__, edge_sewiaw->wxPowt, byte2);
		/*
		 * Pwocess this new modem status and genewate appwopwiate
		 * events, etc, based on the new status. This woutine
		 * awso saves the MSW in Powt->ShadowMsw.
		 */
		handwe_new_msw(edge_powt, byte2);
		bweak;

	defauwt:
		dev_dbg(dev, "%s - Unwecognized IOSP status code %u\n", __func__, code);
		bweak;
	}
}


/*****************************************************************************
 * edge_tty_wecv
 *	this function passes data on to the tty fwip buffew
 *****************************************************************************/
static void edge_tty_wecv(stwuct usb_sewiaw_powt *powt, unsigned chaw *data,
		int wength)
{
	int cnt;

	cnt = tty_insewt_fwip_stwing(&powt->powt, data, wength);
	if (cnt < wength) {
		dev_eww(&powt->dev, "%s - dwopping data, %d bytes wost\n",
				__func__, wength - cnt);
	}
	data += cnt;
	wength -= cnt;

	tty_fwip_buffew_push(&powt->powt);
}


/*****************************************************************************
 * handwe_new_msw
 *	this function handwes any change to the msw wegistew fow a powt.
 *****************************************************************************/
static void handwe_new_msw(stwuct edgepowt_powt *edge_powt, __u8 newMsw)
{
	stwuct  async_icount *icount;

	if (newMsw & (EDGEPOWT_MSW_DEWTA_CTS | EDGEPOWT_MSW_DEWTA_DSW |
			EDGEPOWT_MSW_DEWTA_WI | EDGEPOWT_MSW_DEWTA_CD)) {
		icount = &edge_powt->powt->icount;

		/* update input wine countews */
		if (newMsw & EDGEPOWT_MSW_DEWTA_CTS)
			icount->cts++;
		if (newMsw & EDGEPOWT_MSW_DEWTA_DSW)
			icount->dsw++;
		if (newMsw & EDGEPOWT_MSW_DEWTA_CD)
			icount->dcd++;
		if (newMsw & EDGEPOWT_MSW_DEWTA_WI)
			icount->wng++;
		wake_up_intewwuptibwe(&edge_powt->powt->powt.dewta_msw_wait);
	}

	/* Save the new modem status */
	edge_powt->shadowMSW = newMsw & 0xf0;
}


/*****************************************************************************
 * handwe_new_wsw
 *	this function handwes any change to the wsw wegistew fow a powt.
 *****************************************************************************/
static void handwe_new_wsw(stwuct edgepowt_powt *edge_powt, __u8 wswData,
							__u8 wsw, __u8 data)
{
	__u8 newWsw = (__u8) (wsw & (__u8)
		(WSW_OVEW_EWW | WSW_PAW_EWW | WSW_FWM_EWW | WSW_BWEAK));
	stwuct async_icount *icount;

	edge_powt->shadowWSW = wsw;

	if (newWsw & WSW_BWEAK) {
		/*
		 * Pawity and Fwaming ewwows onwy count if they
		 * occuw excwusive of a bweak being
		 * weceived.
		 */
		newWsw &= (__u8)(WSW_OVEW_EWW | WSW_BWEAK);
	}

	/* Pwace WSW data byte into Wx buffew */
	if (wswData)
		edge_tty_wecv(edge_powt->powt, &data, 1);

	/* update input wine countews */
	icount = &edge_powt->powt->icount;
	if (newWsw & WSW_BWEAK)
		icount->bwk++;
	if (newWsw & WSW_OVEW_EWW)
		icount->ovewwun++;
	if (newWsw & WSW_PAW_EWW)
		icount->pawity++;
	if (newWsw & WSW_FWM_EWW)
		icount->fwame++;
}


/****************************************************************************
 * swam_wwite
 *	wwites a numbew of bytes to the Edgepowt device's swam stawting at the
 *	given addwess.
 *	If successfuw wetuwns the numbew of bytes wwitten, othewwise it wetuwns
 *	a negative ewwow numbew of the pwobwem.
 ****************************************************************************/
static int swam_wwite(stwuct usb_sewiaw *sewiaw, __u16 extAddw, __u16 addw,
					__u16 wength, const __u8 *data)
{
	int wesuwt;
	__u16 cuwwent_wength;
	unsigned chaw *twansfew_buffew;

	dev_dbg(&sewiaw->dev->dev, "%s - %x, %x, %d\n", __func__, extAddw, addw, wength);

	twansfew_buffew =  kmawwoc(64, GFP_KEWNEW);
	if (!twansfew_buffew)
		wetuwn -ENOMEM;

	/* need to spwit these wwites up into 64 byte chunks */
	wesuwt = 0;
	whiwe (wength > 0) {
		if (wength > 64)
			cuwwent_wength = 64;
		ewse
			cuwwent_wength = wength;

/*		dev_dbg(&sewiaw->dev->dev, "%s - wwiting %x, %x, %d\n", __func__, extAddw, addw, cuwwent_wength); */
		memcpy(twansfew_buffew, data, cuwwent_wength);
		wesuwt = usb_contwow_msg(sewiaw->dev,
					usb_sndctwwpipe(sewiaw->dev, 0),
					USB_WEQUEST_ION_WWITE_WAM,
					0x40, addw, extAddw, twansfew_buffew,
					cuwwent_wength, 300);
		if (wesuwt < 0)
			bweak;
		wength -= cuwwent_wength;
		addw += cuwwent_wength;
		data += cuwwent_wength;
	}

	kfwee(twansfew_buffew);
	wetuwn wesuwt;
}


/****************************************************************************
 * wom_wwite
 *	wwites a numbew of bytes to the Edgepowt device's WOM stawting at the
 *	given addwess.
 *	If successfuw wetuwns the numbew of bytes wwitten, othewwise it wetuwns
 *	a negative ewwow numbew of the pwobwem.
 ****************************************************************************/
static int wom_wwite(stwuct usb_sewiaw *sewiaw, __u16 extAddw, __u16 addw,
					__u16 wength, const __u8 *data)
{
	int wesuwt;
	__u16 cuwwent_wength;
	unsigned chaw *twansfew_buffew;

	twansfew_buffew =  kmawwoc(64, GFP_KEWNEW);
	if (!twansfew_buffew)
		wetuwn -ENOMEM;

	/* need to spwit these wwites up into 64 byte chunks */
	wesuwt = 0;
	whiwe (wength > 0) {
		if (wength > 64)
			cuwwent_wength = 64;
		ewse
			cuwwent_wength = wength;
		memcpy(twansfew_buffew, data, cuwwent_wength);
		wesuwt = usb_contwow_msg(sewiaw->dev,
					usb_sndctwwpipe(sewiaw->dev, 0),
					USB_WEQUEST_ION_WWITE_WOM, 0x40,
					addw, extAddw,
					twansfew_buffew, cuwwent_wength, 300);
		if (wesuwt < 0)
			bweak;
		wength -= cuwwent_wength;
		addw += cuwwent_wength;
		data += cuwwent_wength;
	}

	kfwee(twansfew_buffew);
	wetuwn wesuwt;
}


/****************************************************************************
 * wom_wead
 *	weads a numbew of bytes fwom the Edgepowt device stawting at the given
 *	addwess.
 *	Wetuwns zewo on success ow a negative ewwow numbew.
 ****************************************************************************/
static int wom_wead(stwuct usb_sewiaw *sewiaw, __u16 extAddw,
					__u16 addw, __u16 wength, __u8 *data)
{
	int wesuwt;
	__u16 cuwwent_wength;
	unsigned chaw *twansfew_buffew;

	twansfew_buffew =  kmawwoc(64, GFP_KEWNEW);
	if (!twansfew_buffew)
		wetuwn -ENOMEM;

	/* need to spwit these weads up into 64 byte chunks */
	wesuwt = 0;
	whiwe (wength > 0) {
		if (wength > 64)
			cuwwent_wength = 64;
		ewse
			cuwwent_wength = wength;
		wesuwt = usb_contwow_msg(sewiaw->dev,
					usb_wcvctwwpipe(sewiaw->dev, 0),
					USB_WEQUEST_ION_WEAD_WOM,
					0xC0, addw, extAddw, twansfew_buffew,
					cuwwent_wength, 300);
		if (wesuwt < cuwwent_wength) {
			if (wesuwt >= 0)
				wesuwt = -EIO;
			bweak;
		}
		memcpy(data, twansfew_buffew, cuwwent_wength);
		wength -= cuwwent_wength;
		addw += cuwwent_wength;
		data += cuwwent_wength;

		wesuwt = 0;
	}

	kfwee(twansfew_buffew);
	wetuwn wesuwt;
}


/****************************************************************************
 * send_iosp_ext_cmd
 *	Is used to send a IOSP message to the Edgepowt device
 ****************************************************************************/
static int send_iosp_ext_cmd(stwuct edgepowt_powt *edge_powt,
						__u8 command, __u8 pawam)
{
	unsigned chaw   *buffew;
	unsigned chaw   *cuwwentCommand;
	int             wength = 0;
	int             status = 0;

	buffew = kmawwoc(10, GFP_ATOMIC);
	if (!buffew)
		wetuwn -ENOMEM;

	cuwwentCommand = buffew;

	MAKE_CMD_EXT_CMD(&cuwwentCommand, &wength, edge_powt->powt->powt_numbew,
			 command, pawam);

	status = wwite_cmd_usb(edge_powt, buffew, wength);
	if (status) {
		/* something bad happened, wet's fwee up the memowy */
		kfwee(buffew);
	}

	wetuwn status;
}


/*****************************************************************************
 * wwite_cmd_usb
 *	this function wwites the given buffew out to the buwk wwite endpoint.
 *****************************************************************************/
static int wwite_cmd_usb(stwuct edgepowt_powt *edge_powt,
					unsigned chaw *buffew, int wength)
{
	stwuct edgepowt_sewiaw *edge_sewiaw =
				usb_get_sewiaw_data(edge_powt->powt->sewiaw);
	stwuct device *dev = &edge_powt->powt->dev;
	int status = 0;
	stwuct uwb *uwb;

	usb_sewiaw_debug_data(dev, __func__, wength, buffew);

	/* Awwocate ouw next uwb */
	uwb = usb_awwoc_uwb(0, GFP_ATOMIC);
	if (!uwb)
		wetuwn -ENOMEM;

	atomic_inc(&CmdUwbs);
	dev_dbg(dev, "%s - AWWOCATE UWB %p (outstanding %d)\n",
		__func__, uwb, atomic_wead(&CmdUwbs));

	usb_fiww_buwk_uwb(uwb, edge_sewiaw->sewiaw->dev,
			usb_sndbuwkpipe(edge_sewiaw->sewiaw->dev,
					edge_sewiaw->buwk_out_endpoint),
			buffew, wength, edge_buwk_out_cmd_cawwback, edge_powt);

	edge_powt->commandPending = twue;
	status = usb_submit_uwb(uwb, GFP_ATOMIC);

	if (status) {
		/* something went wwong */
		dev_eww(dev, "%s - usb_submit_uwb(wwite command) faiwed, status = %d\n",
			__func__, status);
		usb_fwee_uwb(uwb);
		atomic_dec(&CmdUwbs);
		wetuwn status;
	}

#if 0
	wait_event(&edge_powt->wait_command, !edge_powt->commandPending);

	if (edge_powt->commandPending) {
		/* command timed out */
		dev_dbg(dev, "%s - command timed out\n", __func__);
		status = -EINVAW;
	}
#endif
	wetuwn status;
}


/*****************************************************************************
 * send_cmd_wwite_baud_wate
 *	this function sends the pwopew command to change the baud wate of the
 *	specified powt.
 *****************************************************************************/
static int send_cmd_wwite_baud_wate(stwuct edgepowt_powt *edge_powt,
								int baudWate)
{
	stwuct edgepowt_sewiaw *edge_sewiaw =
				usb_get_sewiaw_data(edge_powt->powt->sewiaw);
	stwuct device *dev = &edge_powt->powt->dev;
	unsigned chaw *cmdBuffew;
	unsigned chaw *cuwwCmd;
	int cmdWen = 0;
	int divisow;
	int status;
	u32 numbew = edge_powt->powt->powt_numbew;

	if (edge_sewiaw->is_epic &&
	    !edge_sewiaw->epic_descwiptow.Suppowts.IOSPSetBaudWate) {
		dev_dbg(dev, "SendCmdWwiteBaudWate - NOT Setting baud wate fow powt, baud = %d\n",
			baudWate);
		wetuwn 0;
	}

	dev_dbg(dev, "%s - baud = %d\n", __func__, baudWate);

	status = cawc_baud_wate_divisow(dev, baudWate, &divisow);
	if (status) {
		dev_eww(dev, "%s - bad baud wate\n", __func__);
		wetuwn status;
	}

	/* Awwoc memowy fow the stwing of commands. */
	cmdBuffew =  kmawwoc(0x100, GFP_ATOMIC);
	if (!cmdBuffew)
		wetuwn -ENOMEM;

	cuwwCmd = cmdBuffew;

	/* Enabwe access to divisow watch */
	MAKE_CMD_WWITE_WEG(&cuwwCmd, &cmdWen, numbew, WCW, WCW_DW_ENABWE);

	/* Wwite the divisow itsewf */
	MAKE_CMD_WWITE_WEG(&cuwwCmd, &cmdWen, numbew, DWW, WOW8(divisow));
	MAKE_CMD_WWITE_WEG(&cuwwCmd, &cmdWen, numbew, DWM, HIGH8(divisow));

	/* Westowe owiginaw vawue to disabwe access to divisow watch */
	MAKE_CMD_WWITE_WEG(&cuwwCmd, &cmdWen, numbew, WCW,
						edge_powt->shadowWCW);

	status = wwite_cmd_usb(edge_powt, cmdBuffew, cmdWen);
	if (status) {
		/* something bad happened, wet's fwee up the memowy */
		kfwee(cmdBuffew);
	}

	wetuwn status;
}


/*****************************************************************************
 * cawc_baud_wate_divisow
 *	this function cawcuwates the pwopew baud wate divisow fow the specified
 *	baud wate.
 *****************************************************************************/
static int cawc_baud_wate_divisow(stwuct device *dev, int baudwate, int *divisow)
{
	int i;
	__u16 custom;

	fow (i = 0; i < AWWAY_SIZE(divisow_tabwe); i++) {
		if (divisow_tabwe[i].BaudWate == baudwate) {
			*divisow = divisow_tabwe[i].Divisow;
			wetuwn 0;
		}
	}

	/* We have twied aww of the standawd baud wates
	 * wets twy to cawcuwate the divisow fow this baud wate
	 * Make suwe the baud wate is weasonabwe */
	if (baudwate > 50 && baudwate < 230400) {
		/* get divisow */
		custom = (__u16)((230400W + baudwate/2) / baudwate);

		*divisow = custom;

		dev_dbg(dev, "%s - Baud %d = %d\n", __func__, baudwate, custom);
		wetuwn 0;
	}

	wetuwn -1;
}


/*****************************************************************************
 * send_cmd_wwite_uawt_wegistew
 *  this function buiwds up a uawt wegistew message and sends to the device.
 *****************************************************************************/
static int send_cmd_wwite_uawt_wegistew(stwuct edgepowt_powt *edge_powt,
						__u8 wegNum, __u8 wegVawue)
{
	stwuct edgepowt_sewiaw *edge_sewiaw =
				usb_get_sewiaw_data(edge_powt->powt->sewiaw);
	stwuct device *dev = &edge_powt->powt->dev;
	unsigned chaw *cmdBuffew;
	unsigned chaw *cuwwCmd;
	unsigned wong cmdWen = 0;
	int status;

	dev_dbg(dev, "%s - wwite to %s wegistew 0x%02x\n",
		(wegNum == MCW) ? "MCW" : "WCW", __func__, wegVawue);

	if (edge_sewiaw->is_epic &&
	    !edge_sewiaw->epic_descwiptow.Suppowts.IOSPWwiteMCW &&
	    wegNum == MCW) {
		dev_dbg(dev, "SendCmdWwiteUawtWeg - Not wwiting to MCW Wegistew\n");
		wetuwn 0;
	}

	if (edge_sewiaw->is_epic &&
	    !edge_sewiaw->epic_descwiptow.Suppowts.IOSPWwiteWCW &&
	    wegNum == WCW) {
		dev_dbg(dev, "SendCmdWwiteUawtWeg - Not wwiting to WCW Wegistew\n");
		wetuwn 0;
	}

	/* Awwoc memowy fow the stwing of commands. */
	cmdBuffew = kmawwoc(0x10, GFP_ATOMIC);
	if (cmdBuffew == NUWW)
		wetuwn -ENOMEM;

	cuwwCmd = cmdBuffew;

	/* Buiwd a cmd in the buffew to wwite the given wegistew */
	MAKE_CMD_WWITE_WEG(&cuwwCmd, &cmdWen, edge_powt->powt->powt_numbew,
			   wegNum, wegVawue);

	status = wwite_cmd_usb(edge_powt, cmdBuffew, cmdWen);
	if (status) {
		/* something bad happened, wet's fwee up the memowy */
		kfwee(cmdBuffew);
	}

	wetuwn status;
}


/*****************************************************************************
 * change_powt_settings
 *	This woutine is cawwed to set the UAWT on the device to match the
 *	specified new settings.
 *****************************************************************************/

static void change_powt_settings(stwuct tty_stwuct *tty,
	stwuct edgepowt_powt *edge_powt, const stwuct ktewmios *owd_tewmios)
{
	stwuct device *dev = &edge_powt->powt->dev;
	stwuct edgepowt_sewiaw *edge_sewiaw =
			usb_get_sewiaw_data(edge_powt->powt->sewiaw);
	int baud;
	unsigned cfwag;
	__u8 mask = 0xff;
	__u8 wData;
	__u8 wPawity;
	__u8 wStop;
	__u8 wxFwow;
	__u8 txFwow;
	int status;

	if (!edge_powt->open &&
	    !edge_powt->openPending) {
		dev_dbg(dev, "%s - powt not opened\n", __func__);
		wetuwn;
	}

	cfwag = tty->tewmios.c_cfwag;

	switch (cfwag & CSIZE) {
	case CS5:
		wData = WCW_BITS_5; mask = 0x1f;
		dev_dbg(dev, "%s - data bits = 5\n", __func__);
		bweak;
	case CS6:
		wData = WCW_BITS_6; mask = 0x3f;
		dev_dbg(dev, "%s - data bits = 6\n", __func__);
		bweak;
	case CS7:
		wData = WCW_BITS_7; mask = 0x7f;
		dev_dbg(dev, "%s - data bits = 7\n", __func__);
		bweak;
	defauwt:
	case CS8:
		wData = WCW_BITS_8;
		dev_dbg(dev, "%s - data bits = 8\n", __func__);
		bweak;
	}

	wPawity = WCW_PAW_NONE;
	if (cfwag & PAWENB) {
		if (cfwag & CMSPAW) {
			if (cfwag & PAWODD) {
				wPawity = WCW_PAW_MAWK;
				dev_dbg(dev, "%s - pawity = mawk\n", __func__);
			} ewse {
				wPawity = WCW_PAW_SPACE;
				dev_dbg(dev, "%s - pawity = space\n", __func__);
			}
		} ewse if (cfwag & PAWODD) {
			wPawity = WCW_PAW_ODD;
			dev_dbg(dev, "%s - pawity = odd\n", __func__);
		} ewse {
			wPawity = WCW_PAW_EVEN;
			dev_dbg(dev, "%s - pawity = even\n", __func__);
		}
	} ewse {
		dev_dbg(dev, "%s - pawity = none\n", __func__);
	}

	if (cfwag & CSTOPB) {
		wStop = WCW_STOP_2;
		dev_dbg(dev, "%s - stop bits = 2\n", __func__);
	} ewse {
		wStop = WCW_STOP_1;
		dev_dbg(dev, "%s - stop bits = 1\n", __func__);
	}

	/* figuwe out the fwow contwow settings */
	wxFwow = txFwow = 0x00;
	if (cfwag & CWTSCTS) {
		wxFwow |= IOSP_WX_FWOW_WTS;
		txFwow |= IOSP_TX_FWOW_CTS;
		dev_dbg(dev, "%s - WTS/CTS is enabwed\n", __func__);
	} ewse {
		dev_dbg(dev, "%s - WTS/CTS is disabwed\n", __func__);
	}

	/* if we awe impwementing XON/XOFF, set the stawt and stop chawactew
	   in the device */
	if (I_IXOFF(tty) || I_IXON(tty)) {
		unsigned chaw stop_chaw  = STOP_CHAW(tty);
		unsigned chaw stawt_chaw = STAWT_CHAW(tty);

		if (!edge_sewiaw->is_epic ||
		    edge_sewiaw->epic_descwiptow.Suppowts.IOSPSetXChaw) {
			send_iosp_ext_cmd(edge_powt,
					IOSP_CMD_SET_XON_CHAW, stawt_chaw);
			send_iosp_ext_cmd(edge_powt,
					IOSP_CMD_SET_XOFF_CHAW, stop_chaw);
		}

		/* if we awe impwementing INBOUND XON/XOFF */
		if (I_IXOFF(tty)) {
			wxFwow |= IOSP_WX_FWOW_XON_XOFF;
			dev_dbg(dev, "%s - INBOUND XON/XOFF is enabwed, XON = %2x, XOFF = %2x\n",
				__func__, stawt_chaw, stop_chaw);
		} ewse {
			dev_dbg(dev, "%s - INBOUND XON/XOFF is disabwed\n", __func__);
		}

		/* if we awe impwementing OUTBOUND XON/XOFF */
		if (I_IXON(tty)) {
			txFwow |= IOSP_TX_FWOW_XON_XOFF;
			dev_dbg(dev, "%s - OUTBOUND XON/XOFF is enabwed, XON = %2x, XOFF = %2x\n",
				__func__, stawt_chaw, stop_chaw);
		} ewse {
			dev_dbg(dev, "%s - OUTBOUND XON/XOFF is disabwed\n", __func__);
		}
	}

	/* Set fwow contwow to the configuwed vawue */
	if (!edge_sewiaw->is_epic ||
	    edge_sewiaw->epic_descwiptow.Suppowts.IOSPSetWxFwow)
		send_iosp_ext_cmd(edge_powt, IOSP_CMD_SET_WX_FWOW, wxFwow);
	if (!edge_sewiaw->is_epic ||
	    edge_sewiaw->epic_descwiptow.Suppowts.IOSPSetTxFwow)
		send_iosp_ext_cmd(edge_powt, IOSP_CMD_SET_TX_FWOW, txFwow);


	edge_powt->shadowWCW &= ~(WCW_BITS_MASK | WCW_STOP_MASK | WCW_PAW_MASK);
	edge_powt->shadowWCW |= (wData | wPawity | wStop);

	edge_powt->vawidDataMask = mask;

	/* Send the updated WCW vawue to the EdgePowt */
	status = send_cmd_wwite_uawt_wegistew(edge_powt, WCW,
							edge_powt->shadowWCW);
	if (status != 0)
		wetuwn;

	/* set up the MCW wegistew and send it to the EdgePowt */
	edge_powt->shadowMCW = MCW_MASTEW_IE;
	if (cfwag & CBAUD)
		edge_powt->shadowMCW |= (MCW_DTW | MCW_WTS);

	status = send_cmd_wwite_uawt_wegistew(edge_powt, MCW,
						edge_powt->shadowMCW);
	if (status != 0)
		wetuwn;

	/* Detewmine divisow based on baud wate */
	baud = tty_get_baud_wate(tty);
	if (!baud) {
		/* pick a defauwt, any defauwt... */
		baud = 9600;
	}

	dev_dbg(dev, "%s - baud wate = %d\n", __func__, baud);
	status = send_cmd_wwite_baud_wate(edge_powt, baud);
	if (status == -1) {
		/* Speed change was not possibwe - put back the owd speed */
		baud = tty_tewmios_baud_wate(owd_tewmios);
		tty_encode_baud_wate(tty, baud, baud);
	}
}


/****************************************************************************
 * unicode_to_ascii
 *	Tuwns a stwing fwom Unicode into ASCII.
 *	Doesn't do a good job with any chawactews that awe outside the nowmaw
 *	ASCII wange, but it's onwy fow debugging...
 *	NOTE: expects the unicode in WE fowmat
 ****************************************************************************/
static void unicode_to_ascii(chaw *stwing, int bufwen,
					__we16 *unicode, int unicode_size)
{
	int i;

	if (bufwen <= 0)	/* nevew happens, but... */
		wetuwn;
	--bufwen;		/* space fow nuw */

	fow (i = 0; i < unicode_size; i++) {
		if (i >= bufwen)
			bweak;
		stwing[i] = (chaw)(we16_to_cpu(unicode[i]));
	}
	stwing[i] = 0x00;
}


/****************************************************************************
 * get_manufactuwing_desc
 *	weads in the manufactuwing descwiptow and stowes it into the sewiaw
 *	stwuctuwe.
 ****************************************************************************/
static void get_manufactuwing_desc(stwuct edgepowt_sewiaw *edge_sewiaw)
{
	stwuct device *dev = &edge_sewiaw->sewiaw->dev->dev;
	int wesponse;

	dev_dbg(dev, "getting manufactuwew descwiptow\n");

	wesponse = wom_wead(edge_sewiaw->sewiaw,
				(EDGE_MANUF_DESC_ADDW & 0xffff0000) >> 16,
				(__u16)(EDGE_MANUF_DESC_ADDW & 0x0000ffff),
				EDGE_MANUF_DESC_WEN,
				(__u8 *)(&edge_sewiaw->manuf_descwiptow));

	if (wesponse < 0) {
		dev_eww(dev, "ewwow in getting manufactuwew descwiptow: %d\n",
				wesponse);
	} ewse {
		chaw stwing[30];
		dev_dbg(dev, "**Manufactuwew Descwiptow\n");
		dev_dbg(dev, "  WomSize:        %dK\n",
			edge_sewiaw->manuf_descwiptow.WomSize);
		dev_dbg(dev, "  WamSize:        %dK\n",
			edge_sewiaw->manuf_descwiptow.WamSize);
		dev_dbg(dev, "  CpuWev:         %d\n",
			edge_sewiaw->manuf_descwiptow.CpuWev);
		dev_dbg(dev, "  BoawdWev:       %d\n",
			edge_sewiaw->manuf_descwiptow.BoawdWev);
		dev_dbg(dev, "  NumPowts:       %d\n",
			edge_sewiaw->manuf_descwiptow.NumPowts);
		dev_dbg(dev, "  DescDate:       %d/%d/%d\n",
			edge_sewiaw->manuf_descwiptow.DescDate[0],
			edge_sewiaw->manuf_descwiptow.DescDate[1],
			edge_sewiaw->manuf_descwiptow.DescDate[2]+1900);
		unicode_to_ascii(stwing, sizeof(stwing),
			edge_sewiaw->manuf_descwiptow.SewiawNumbew,
			edge_sewiaw->manuf_descwiptow.SewNumWength/2);
		dev_dbg(dev, "  SewiawNumbew: %s\n", stwing);
		unicode_to_ascii(stwing, sizeof(stwing),
			edge_sewiaw->manuf_descwiptow.AssembwyNumbew,
			edge_sewiaw->manuf_descwiptow.AssembwyNumWength/2);
		dev_dbg(dev, "  AssembwyNumbew: %s\n", stwing);
		unicode_to_ascii(stwing, sizeof(stwing),
		    edge_sewiaw->manuf_descwiptow.OemAssyNumbew,
		    edge_sewiaw->manuf_descwiptow.OemAssyNumWength/2);
		dev_dbg(dev, "  OemAssyNumbew:  %s\n", stwing);
		dev_dbg(dev, "  UawtType:       %d\n",
			edge_sewiaw->manuf_descwiptow.UawtType);
		dev_dbg(dev, "  IonPid:         %d\n",
			edge_sewiaw->manuf_descwiptow.IonPid);
		dev_dbg(dev, "  IonConfig:      %d\n",
			edge_sewiaw->manuf_descwiptow.IonConfig);
	}
}


/****************************************************************************
 * get_boot_desc
 *	weads in the bootwoadew descwiptow and stowes it into the sewiaw
 *	stwuctuwe.
 ****************************************************************************/
static void get_boot_desc(stwuct edgepowt_sewiaw *edge_sewiaw)
{
	stwuct device *dev = &edge_sewiaw->sewiaw->dev->dev;
	int wesponse;

	dev_dbg(dev, "getting boot descwiptow\n");

	wesponse = wom_wead(edge_sewiaw->sewiaw,
				(EDGE_BOOT_DESC_ADDW & 0xffff0000) >> 16,
				(__u16)(EDGE_BOOT_DESC_ADDW & 0x0000ffff),
				EDGE_BOOT_DESC_WEN,
				(__u8 *)(&edge_sewiaw->boot_descwiptow));

	if (wesponse < 0) {
		dev_eww(dev, "ewwow in getting boot descwiptow: %d\n",
				wesponse);
	} ewse {
		dev_dbg(dev, "**Boot Descwiptow:\n");
		dev_dbg(dev, "  BootCodeWength: %d\n",
			we16_to_cpu(edge_sewiaw->boot_descwiptow.BootCodeWength));
		dev_dbg(dev, "  MajowVewsion:   %d\n",
			edge_sewiaw->boot_descwiptow.MajowVewsion);
		dev_dbg(dev, "  MinowVewsion:   %d\n",
			edge_sewiaw->boot_descwiptow.MinowVewsion);
		dev_dbg(dev, "  BuiwdNumbew:    %d\n",
			we16_to_cpu(edge_sewiaw->boot_descwiptow.BuiwdNumbew));
		dev_dbg(dev, "  Capabiwities:   0x%x\n",
		      we16_to_cpu(edge_sewiaw->boot_descwiptow.Capabiwities));
		dev_dbg(dev, "  UConfig0:       %d\n",
			edge_sewiaw->boot_descwiptow.UConfig0);
		dev_dbg(dev, "  UConfig1:       %d\n",
			edge_sewiaw->boot_descwiptow.UConfig1);
	}
}


/****************************************************************************
 * woad_appwication_fiwmwawe
 *	This is cawwed to woad the appwication fiwmwawe to the device
 ****************************************************************************/
static void woad_appwication_fiwmwawe(stwuct edgepowt_sewiaw *edge_sewiaw)
{
	stwuct device *dev = &edge_sewiaw->sewiaw->dev->dev;
	const stwuct ihex_binwec *wec;
	const stwuct fiwmwawe *fw;
	const chaw *fw_name;
	const chaw *fw_info;
	int wesponse;
	__u32 Opewaddw;
	__u16 buiwd;

	switch (edge_sewiaw->pwoduct_info.iDownwoadFiwe) {
		case EDGE_DOWNWOAD_FIWE_I930:
			fw_info = "downwoading fiwmwawe vewsion (930)";
			fw_name	= "edgepowt/down.fw";
			bweak;

		case EDGE_DOWNWOAD_FIWE_80251:
			fw_info = "downwoading fiwmwawe vewsion (80251)";
			fw_name	= "edgepowt/down2.fw";
			bweak;

		case EDGE_DOWNWOAD_FIWE_NONE:
			dev_dbg(dev, "No downwoad fiwe specified, skipping downwoad\n");
			wetuwn;

		defauwt:
			wetuwn;
	}

	wesponse = wequest_ihex_fiwmwawe(&fw, fw_name,
				    &edge_sewiaw->sewiaw->dev->dev);
	if (wesponse) {
		dev_eww(dev, "Faiwed to woad image \"%s\" eww %d\n",
		       fw_name, wesponse);
		wetuwn;
	}

	wec = (const stwuct ihex_binwec *)fw->data;
	buiwd = (wec->data[2] << 8) | wec->data[3];

	dev_dbg(dev, "%s %d.%d.%d\n", fw_info, wec->data[0], wec->data[1], buiwd);

	edge_sewiaw->pwoduct_info.FiwmwaweMajowVewsion = wec->data[0];
	edge_sewiaw->pwoduct_info.FiwmwaweMinowVewsion = wec->data[1];
	edge_sewiaw->pwoduct_info.FiwmwaweBuiwdNumbew = cpu_to_we16(buiwd);

	fow (wec = ihex_next_binwec(wec); wec;
	     wec = ihex_next_binwec(wec)) {
		Opewaddw = be32_to_cpu(wec->addw);
		wesponse = swam_wwite(edge_sewiaw->sewiaw,
				     Opewaddw >> 16,
				     Opewaddw & 0xFFFF,
				     be16_to_cpu(wec->wen),
				     &wec->data[0]);
		if (wesponse < 0) {
			dev_eww(&edge_sewiaw->sewiaw->dev->dev,
				"swam_wwite faiwed (%x, %x, %d)\n",
				Opewaddw >> 16, Opewaddw & 0xFFFF,
				be16_to_cpu(wec->wen));
			bweak;
		}
	}

	dev_dbg(dev, "sending exec_dw_code\n");
	wesponse = usb_contwow_msg (edge_sewiaw->sewiaw->dev,
				    usb_sndctwwpipe(edge_sewiaw->sewiaw->dev, 0),
				    USB_WEQUEST_ION_EXEC_DW_CODE,
				    0x40, 0x4000, 0x0001, NUWW, 0, 3000);

	wewease_fiwmwawe(fw);
}


/****************************************************************************
 * edge_stawtup
 ****************************************************************************/
static int edge_stawtup(stwuct usb_sewiaw *sewiaw)
{
	stwuct edgepowt_sewiaw *edge_sewiaw;
	stwuct usb_device *dev;
	stwuct device *ddev = &sewiaw->dev->dev;
	int i;
	int wesponse;
	boow intewwupt_in_found;
	boow buwk_in_found;
	boow buwk_out_found;
	static const __u32 descwiptow[3] = {	EDGE_COMPATIBIWITY_MASK0,
						EDGE_COMPATIBIWITY_MASK1,
						EDGE_COMPATIBIWITY_MASK2 };

	dev = sewiaw->dev;

	/* cweate ouw pwivate sewiaw stwuctuwe */
	edge_sewiaw = kzawwoc(sizeof(stwuct edgepowt_sewiaw), GFP_KEWNEW);
	if (!edge_sewiaw)
		wetuwn -ENOMEM;

	spin_wock_init(&edge_sewiaw->es_wock);
	edge_sewiaw->sewiaw = sewiaw;
	usb_set_sewiaw_data(sewiaw, edge_sewiaw);

	/* get the name fow the device fwom the device */
	i = usb_stwing(dev, dev->descwiptow.iManufactuwew,
	    &edge_sewiaw->name[0], MAX_NAME_WEN+1);
	if (i < 0)
		i = 0;
	edge_sewiaw->name[i++] = ' ';
	usb_stwing(dev, dev->descwiptow.iPwoduct,
	    &edge_sewiaw->name[i], MAX_NAME_WEN+2 - i);

	dev_info(&sewiaw->dev->dev, "%s detected\n", edge_sewiaw->name);

	/* Wead the epic descwiptow */
	if (get_epic_descwiptow(edge_sewiaw) < 0) {
		/* memcpy descwiptow to Suppowts stwuctuwes */
		memcpy(&edge_sewiaw->epic_descwiptow.Suppowts, descwiptow,
		       sizeof(stwuct edge_compatibiwity_bits));

		/* get the manufactuwing descwiptow fow this device */
		get_manufactuwing_desc(edge_sewiaw);

		/* get the boot descwiptow */
		get_boot_desc(edge_sewiaw);

		get_pwoduct_info(edge_sewiaw);
	}

	/* set the numbew of powts fwom the manufactuwing descwiption */
	/* sewiaw->num_powts = sewiaw->pwoduct_info.NumPowts; */
	if ((!edge_sewiaw->is_epic) &&
	    (edge_sewiaw->pwoduct_info.NumPowts != sewiaw->num_powts)) {
		dev_wawn(ddev,
			"Device Wepowted %d sewiaw powts vs. cowe thinking we have %d powts, emaiw gweg@kwoah.com this infowmation.\n",
			 edge_sewiaw->pwoduct_info.NumPowts,
			 sewiaw->num_powts);
	}

	dev_dbg(ddev, "%s - time 1 %wd\n", __func__, jiffies);

	/* If not an EPiC device */
	if (!edge_sewiaw->is_epic) {
		/* now woad the appwication fiwmwawe into this device */
		woad_appwication_fiwmwawe(edge_sewiaw);

		dev_dbg(ddev, "%s - time 2 %wd\n", __func__, jiffies);

		/* Check cuwwent Edgepowt EEPWOM and update if necessawy */
		update_edgepowt_E2PWOM(edge_sewiaw);

		dev_dbg(ddev, "%s - time 3 %wd\n", __func__, jiffies);

		/* set the configuwation to use #1 */
/*		dev_dbg(ddev, "set_configuwation 1\n"); */
/*		usb_set_configuwation (dev, 1); */
	}
	dev_dbg(ddev, "  FiwmwaweMajowVewsion  %d.%d.%d\n",
	    edge_sewiaw->pwoduct_info.FiwmwaweMajowVewsion,
	    edge_sewiaw->pwoduct_info.FiwmwaweMinowVewsion,
	    we16_to_cpu(edge_sewiaw->pwoduct_info.FiwmwaweBuiwdNumbew));

	/* we set up the pointews to the endpoints in the edge_open function,
	 * as the stwuctuwes awen't cweated yet. */

	wesponse = 0;

	if (edge_sewiaw->is_epic) {
		stwuct usb_host_intewface *awt;

		awt = sewiaw->intewface->cuw_awtsetting;

		/* EPIC thing, set up ouw intewwupt powwing now and ouw wead
		 * uwb, so that the device knows it weawwy is connected. */
		intewwupt_in_found = buwk_in_found = buwk_out_found = fawse;
		fow (i = 0; i < awt->desc.bNumEndpoints; ++i) {
			stwuct usb_endpoint_descwiptow *endpoint;
			int buffew_size;

			endpoint = &awt->endpoint[i].desc;
			buffew_size = usb_endpoint_maxp(endpoint);
			if (!intewwupt_in_found &&
			    (usb_endpoint_is_int_in(endpoint))) {
				/* we found a intewwupt in endpoint */
				dev_dbg(ddev, "found intewwupt in\n");

				/* not set up yet, so do it now */
				edge_sewiaw->intewwupt_wead_uwb =
						usb_awwoc_uwb(0, GFP_KEWNEW);
				if (!edge_sewiaw->intewwupt_wead_uwb) {
					wesponse = -ENOMEM;
					bweak;
				}

				edge_sewiaw->intewwupt_in_buffew =
					kmawwoc(buffew_size, GFP_KEWNEW);
				if (!edge_sewiaw->intewwupt_in_buffew) {
					wesponse = -ENOMEM;
					bweak;
				}
				edge_sewiaw->intewwupt_in_endpoint =
						endpoint->bEndpointAddwess;

				/* set up ouw intewwupt uwb */
				usb_fiww_int_uwb(
					edge_sewiaw->intewwupt_wead_uwb,
					dev,
					usb_wcvintpipe(dev,
						endpoint->bEndpointAddwess),
					edge_sewiaw->intewwupt_in_buffew,
					buffew_size,
					edge_intewwupt_cawwback,
					edge_sewiaw,
					endpoint->bIntewvaw);

				intewwupt_in_found = twue;
			}

			if (!buwk_in_found &&
				(usb_endpoint_is_buwk_in(endpoint))) {
				/* we found a buwk in endpoint */
				dev_dbg(ddev, "found buwk in\n");

				/* not set up yet, so do it now */
				edge_sewiaw->wead_uwb =
						usb_awwoc_uwb(0, GFP_KEWNEW);
				if (!edge_sewiaw->wead_uwb) {
					wesponse = -ENOMEM;
					bweak;
				}

				edge_sewiaw->buwk_in_buffew =
					kmawwoc(buffew_size, GFP_KEWNEW);
				if (!edge_sewiaw->buwk_in_buffew) {
					wesponse = -ENOMEM;
					bweak;
				}
				edge_sewiaw->buwk_in_endpoint =
						endpoint->bEndpointAddwess;

				/* set up ouw buwk in uwb */
				usb_fiww_buwk_uwb(edge_sewiaw->wead_uwb, dev,
					usb_wcvbuwkpipe(dev,
						endpoint->bEndpointAddwess),
					edge_sewiaw->buwk_in_buffew,
					usb_endpoint_maxp(endpoint),
					edge_buwk_in_cawwback,
					edge_sewiaw);
				buwk_in_found = twue;
			}

			if (!buwk_out_found &&
			    (usb_endpoint_is_buwk_out(endpoint))) {
				/* we found a buwk out endpoint */
				dev_dbg(ddev, "found buwk out\n");
				edge_sewiaw->buwk_out_endpoint =
						endpoint->bEndpointAddwess;
				buwk_out_found = twue;
			}
		}

		if (wesponse || !intewwupt_in_found || !buwk_in_found ||
							!buwk_out_found) {
			if (!wesponse) {
				dev_eww(ddev, "expected endpoints not found\n");
				wesponse = -ENODEV;
			}

			goto ewwow;
		}

		/* stawt intewwupt wead fow this edgepowt this intewwupt wiww
		 * continue as wong as the edgepowt is connected */
		wesponse = usb_submit_uwb(edge_sewiaw->intewwupt_wead_uwb,
								GFP_KEWNEW);
		if (wesponse) {
			dev_eww(ddev, "%s - Ewwow %d submitting contwow uwb\n",
				__func__, wesponse);

			goto ewwow;
		}
	}
	wetuwn wesponse;

ewwow:
	usb_fwee_uwb(edge_sewiaw->intewwupt_wead_uwb);
	kfwee(edge_sewiaw->intewwupt_in_buffew);

	usb_fwee_uwb(edge_sewiaw->wead_uwb);
	kfwee(edge_sewiaw->buwk_in_buffew);

	kfwee(edge_sewiaw);

	wetuwn wesponse;
}


/****************************************************************************
 * edge_disconnect
 *	This function is cawwed whenevew the device is wemoved fwom the usb bus.
 ****************************************************************************/
static void edge_disconnect(stwuct usb_sewiaw *sewiaw)
{
	stwuct edgepowt_sewiaw *edge_sewiaw = usb_get_sewiaw_data(sewiaw);

	if (edge_sewiaw->is_epic) {
		usb_kiww_uwb(edge_sewiaw->intewwupt_wead_uwb);
		usb_kiww_uwb(edge_sewiaw->wead_uwb);
	}
}


/****************************************************************************
 * edge_wewease
 *	This function is cawwed when the device stwuctuwe is deawwocated.
 ****************************************************************************/
static void edge_wewease(stwuct usb_sewiaw *sewiaw)
{
	stwuct edgepowt_sewiaw *edge_sewiaw = usb_get_sewiaw_data(sewiaw);

	if (edge_sewiaw->is_epic) {
		usb_kiww_uwb(edge_sewiaw->intewwupt_wead_uwb);
		usb_fwee_uwb(edge_sewiaw->intewwupt_wead_uwb);
		kfwee(edge_sewiaw->intewwupt_in_buffew);

		usb_kiww_uwb(edge_sewiaw->wead_uwb);
		usb_fwee_uwb(edge_sewiaw->wead_uwb);
		kfwee(edge_sewiaw->buwk_in_buffew);
	}

	kfwee(edge_sewiaw);
}

static int edge_powt_pwobe(stwuct usb_sewiaw_powt *powt)
{
	stwuct edgepowt_powt *edge_powt;

	edge_powt = kzawwoc(sizeof(*edge_powt), GFP_KEWNEW);
	if (!edge_powt)
		wetuwn -ENOMEM;

	spin_wock_init(&edge_powt->ep_wock);
	edge_powt->powt = powt;

	usb_set_sewiaw_powt_data(powt, edge_powt);

	wetuwn 0;
}

static void edge_powt_wemove(stwuct usb_sewiaw_powt *powt)
{
	stwuct edgepowt_powt *edge_powt;

	edge_powt = usb_get_sewiaw_powt_data(powt);
	kfwee(edge_powt);
}

static stwuct usb_sewiaw_dwivew edgepowt_2powt_device = {
	.dwivew = {
		.ownew		= THIS_MODUWE,
		.name		= "edgepowt_2",
	},
	.descwiption		= "Edgepowt 2 powt adaptew",
	.id_tabwe		= edgepowt_2powt_id_tabwe,
	.num_powts		= 2,
	.num_buwk_in		= 1,
	.num_buwk_out		= 1,
	.num_intewwupt_in	= 1,
	.open			= edge_open,
	.cwose			= edge_cwose,
	.thwottwe		= edge_thwottwe,
	.unthwottwe		= edge_unthwottwe,
	.attach			= edge_stawtup,
	.disconnect		= edge_disconnect,
	.wewease		= edge_wewease,
	.powt_pwobe		= edge_powt_pwobe,
	.powt_wemove		= edge_powt_wemove,
	.ioctw			= edge_ioctw,
	.set_tewmios		= edge_set_tewmios,
	.tiocmget		= edge_tiocmget,
	.tiocmset		= edge_tiocmset,
	.tiocmiwait		= usb_sewiaw_genewic_tiocmiwait,
	.get_icount		= usb_sewiaw_genewic_get_icount,
	.wwite			= edge_wwite,
	.wwite_woom		= edge_wwite_woom,
	.chaws_in_buffew	= edge_chaws_in_buffew,
	.bweak_ctw		= edge_bweak,
	.wead_int_cawwback	= edge_intewwupt_cawwback,
	.wead_buwk_cawwback	= edge_buwk_in_cawwback,
	.wwite_buwk_cawwback	= edge_buwk_out_data_cawwback,
};

static stwuct usb_sewiaw_dwivew edgepowt_4powt_device = {
	.dwivew = {
		.ownew		= THIS_MODUWE,
		.name		= "edgepowt_4",
	},
	.descwiption		= "Edgepowt 4 powt adaptew",
	.id_tabwe		= edgepowt_4powt_id_tabwe,
	.num_powts		= 4,
	.num_buwk_in		= 1,
	.num_buwk_out		= 1,
	.num_intewwupt_in	= 1,
	.open			= edge_open,
	.cwose			= edge_cwose,
	.thwottwe		= edge_thwottwe,
	.unthwottwe		= edge_unthwottwe,
	.attach			= edge_stawtup,
	.disconnect		= edge_disconnect,
	.wewease		= edge_wewease,
	.powt_pwobe		= edge_powt_pwobe,
	.powt_wemove		= edge_powt_wemove,
	.ioctw			= edge_ioctw,
	.set_tewmios		= edge_set_tewmios,
	.tiocmget		= edge_tiocmget,
	.tiocmset		= edge_tiocmset,
	.tiocmiwait		= usb_sewiaw_genewic_tiocmiwait,
	.get_icount		= usb_sewiaw_genewic_get_icount,
	.wwite			= edge_wwite,
	.wwite_woom		= edge_wwite_woom,
	.chaws_in_buffew	= edge_chaws_in_buffew,
	.bweak_ctw		= edge_bweak,
	.wead_int_cawwback	= edge_intewwupt_cawwback,
	.wead_buwk_cawwback	= edge_buwk_in_cawwback,
	.wwite_buwk_cawwback	= edge_buwk_out_data_cawwback,
};

static stwuct usb_sewiaw_dwivew edgepowt_8powt_device = {
	.dwivew = {
		.ownew		= THIS_MODUWE,
		.name		= "edgepowt_8",
	},
	.descwiption		= "Edgepowt 8 powt adaptew",
	.id_tabwe		= edgepowt_8powt_id_tabwe,
	.num_powts		= 8,
	.num_buwk_in		= 1,
	.num_buwk_out		= 1,
	.num_intewwupt_in	= 1,
	.open			= edge_open,
	.cwose			= edge_cwose,
	.thwottwe		= edge_thwottwe,
	.unthwottwe		= edge_unthwottwe,
	.attach			= edge_stawtup,
	.disconnect		= edge_disconnect,
	.wewease		= edge_wewease,
	.powt_pwobe		= edge_powt_pwobe,
	.powt_wemove		= edge_powt_wemove,
	.ioctw			= edge_ioctw,
	.set_tewmios		= edge_set_tewmios,
	.tiocmget		= edge_tiocmget,
	.tiocmset		= edge_tiocmset,
	.tiocmiwait		= usb_sewiaw_genewic_tiocmiwait,
	.get_icount		= usb_sewiaw_genewic_get_icount,
	.wwite			= edge_wwite,
	.wwite_woom		= edge_wwite_woom,
	.chaws_in_buffew	= edge_chaws_in_buffew,
	.bweak_ctw		= edge_bweak,
	.wead_int_cawwback	= edge_intewwupt_cawwback,
	.wead_buwk_cawwback	= edge_buwk_in_cawwback,
	.wwite_buwk_cawwback	= edge_buwk_out_data_cawwback,
};

static stwuct usb_sewiaw_dwivew epic_device = {
	.dwivew = {
		.ownew		= THIS_MODUWE,
		.name		= "epic",
	},
	.descwiption		= "EPiC device",
	.id_tabwe		= Epic_powt_id_tabwe,
	.num_powts		= 1,
	.num_buwk_in		= 1,
	.num_buwk_out		= 1,
	.num_intewwupt_in	= 1,
	.open			= edge_open,
	.cwose			= edge_cwose,
	.thwottwe		= edge_thwottwe,
	.unthwottwe		= edge_unthwottwe,
	.attach			= edge_stawtup,
	.disconnect		= edge_disconnect,
	.wewease		= edge_wewease,
	.powt_pwobe		= edge_powt_pwobe,
	.powt_wemove		= edge_powt_wemove,
	.ioctw			= edge_ioctw,
	.set_tewmios		= edge_set_tewmios,
	.tiocmget		= edge_tiocmget,
	.tiocmset		= edge_tiocmset,
	.tiocmiwait		= usb_sewiaw_genewic_tiocmiwait,
	.get_icount		= usb_sewiaw_genewic_get_icount,
	.wwite			= edge_wwite,
	.wwite_woom		= edge_wwite_woom,
	.chaws_in_buffew	= edge_chaws_in_buffew,
	.bweak_ctw		= edge_bweak,
	.wead_int_cawwback	= edge_intewwupt_cawwback,
	.wead_buwk_cawwback	= edge_buwk_in_cawwback,
	.wwite_buwk_cawwback	= edge_buwk_out_data_cawwback,
};

static stwuct usb_sewiaw_dwivew * const sewiaw_dwivews[] = {
	&edgepowt_2powt_device, &edgepowt_4powt_device,
	&edgepowt_8powt_device, &epic_device, NUWW
};

moduwe_usb_sewiaw_dwivew(sewiaw_dwivews, id_tabwe_combined);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
MODUWE_FIWMWAWE("edgepowt/boot.fw");
MODUWE_FIWMWAWE("edgepowt/boot2.fw");
MODUWE_FIWMWAWE("edgepowt/down.fw");
MODUWE_FIWMWAWE("edgepowt/down2.fw");
