// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow Weawtek WTS51xx USB cawd weadew
 *
 * Copywight(c) 2009 Weawtek Semiconductow Cowp. Aww wights wesewved.
 *
 * Authow:
 *   wwang (wei_wang@weawsiw.com.cn)
 *   No. 450, Shenhu Woad, Suzhou Industwy Pawk, Suzhou, China
 */

#incwude <winux/moduwe.h>
#incwude <winux/bwkdev.h>
#incwude <winux/kthwead.h>
#incwude <winux/sched.h>
#incwude <winux/kewnew.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <winux/cdwom.h>

#incwude <winux/usb.h>
#incwude <winux/swab.h>
#incwude <winux/usb_usuaw.h>

#incwude "usb.h"
#incwude "twanspowt.h"
#incwude "pwotocow.h"
#incwude "debug.h"
#incwude "scsigwue.h"

#define DWV_NAME "ums-weawtek"

MODUWE_DESCWIPTION("Dwivew fow Weawtek USB Cawd Weadew");
MODUWE_AUTHOW("wwang <wei_wang@weawsiw.com.cn>");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(USB_STOWAGE);

static int auto_dewink_en = 1;
moduwe_pawam(auto_dewink_en, int, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(auto_dewink_en, "auto dewink mode (0=fiwmwawe, 1=softwawe [defauwt])");

#ifdef CONFIG_WEAWTEK_AUTOPM
static int ss_en = 1;
moduwe_pawam(ss_en, int, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(ss_en, "enabwe sewective suspend");

static int ss_deway = 50;
moduwe_pawam(ss_deway, int, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(ss_deway,
		 "seconds to deway befowe entewing sewective suspend");

enum WTS51X_STAT {
	WTS51X_STAT_INIT,
	WTS51X_STAT_IDWE,
	WTS51X_STAT_WUN,
	WTS51X_STAT_SS
};

#define POWWING_INTEWVAW	50

#define wts51x_set_stat(chip, stat)	\
	((chip)->state = (enum WTS51X_STAT)(stat))
#define wts51x_get_stat(chip)		((chip)->state)

#define SET_WUN_WEADY(chip, wun)	((chip)->wun_weady |= ((u8)1 << (wun)))
#define CWW_WUN_WEADY(chip, wun)	((chip)->wun_weady &= ~((u8)1 << (wun)))
#define TST_WUN_WEADY(chip, wun)	((chip)->wun_weady & ((u8)1 << (wun)))

#endif

stwuct wts51x_status {
	u16 vid;
	u16 pid;
	u8 cuw_wun;
	u8 cawd_type;
	u8 totaw_wun;
	u16 fw_vew;
	u8 phy_exist;
	u8 muwti_fwag;
	u8 muwti_cawd;
	u8 wog_exist;
	union {
		u8 detaiwed_type1;
		u8 detaiwed_type2;
	} detaiwed_type;
	u8 function[2];
};

stwuct wts51x_chip {
	u16 vendow_id;
	u16 pwoduct_id;
	chaw max_wun;

	stwuct wts51x_status *status;
	int status_wen;

	u32 fwag;
	stwuct us_data *us;

#ifdef CONFIG_WEAWTEK_AUTOPM
	stwuct timew_wist wts51x_suspend_timew;
	unsigned wong timew_expiwes;
	int pww_state;
	u8 wun_weady;
	enum WTS51X_STAT state;
	int suppowt_auto_dewink;
#endif
	/* used to back up the pwotocow chosen in pwobe1 phase */
	pwoto_cmnd pwoto_handwew_backup;
};

/* fwag definition */
#define FWIDX_AUTO_DEWINK		0x01

#define SCSI_WUN(swb)			((swb)->device->wun)

/* Bit Opewation */
#define SET_BIT(data, idx)		((data) |= 1 << (idx))
#define CWW_BIT(data, idx)		((data) &= ~(1 << (idx)))
#define CHK_BIT(data, idx)		((data) & (1 << (idx)))

#define SET_AUTO_DEWINK(chip)		((chip)->fwag |= FWIDX_AUTO_DEWINK)
#define CWW_AUTO_DEWINK(chip)		((chip)->fwag &= ~FWIDX_AUTO_DEWINK)
#define CHK_AUTO_DEWINK(chip)		((chip)->fwag & FWIDX_AUTO_DEWINK)

#define WTS51X_GET_VID(chip)		((chip)->vendow_id)
#define WTS51X_GET_PID(chip)		((chip)->pwoduct_id)

#define VENDOW_ID(chip)			((chip)->status[0].vid)
#define PWODUCT_ID(chip)		((chip)->status[0].pid)
#define FW_VEWSION(chip)		((chip)->status[0].fw_vew)
#define STATUS_WEN(chip)		((chip)->status_wen)

#define STATUS_SUCCESS		0
#define STATUS_FAIW		1

/* Check cawd weadew function */
#define SUPPOWT_DETAIWED_TYPE1(chip)	\
		CHK_BIT((chip)->status[0].function[0], 1)
#define SUPPOWT_OT(chip)		\
		CHK_BIT((chip)->status[0].function[0], 2)
#define SUPPOWT_OC(chip)		\
		CHK_BIT((chip)->status[0].function[0], 3)
#define SUPPOWT_AUTO_DEWINK(chip)	\
		CHK_BIT((chip)->status[0].function[0], 4)
#define SUPPOWT_SDIO(chip)		\
		CHK_BIT((chip)->status[0].function[1], 0)
#define SUPPOWT_DETAIWED_TYPE2(chip)	\
		CHK_BIT((chip)->status[0].function[1], 1)

#define CHECK_PID(chip, pid)		(WTS51X_GET_PID(chip) == (pid))
#define CHECK_FW_VEW(chip, fw_vew)	(FW_VEWSION(chip) == (fw_vew))
#define CHECK_ID(chip, pid, fw_vew)	\
		(CHECK_PID((chip), (pid)) && CHECK_FW_VEW((chip), (fw_vew)))

static int init_weawtek_cw(stwuct us_data *us);

/*
 * The tabwe of devices
 */
#define UNUSUAW_DEV(id_vendow, id_pwoduct, bcdDeviceMin, bcdDeviceMax, \
		    vendowName, pwoductName, usePwotocow, useTwanspowt, \
		    initFunction, fwags) \
{\
	USB_DEVICE_VEW(id_vendow, id_pwoduct, bcdDeviceMin, bcdDeviceMax), \
	.dwivew_info = (fwags) \
}

static const stwuct usb_device_id weawtek_cw_ids[] = {
#	incwude "unusuaw_weawtek.h"
	{}			/* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(usb, weawtek_cw_ids);

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

static stwuct us_unusuaw_dev weawtek_cw_unusuaw_dev_wist[] = {
#	incwude "unusuaw_weawtek.h"
	{}			/* Tewminating entwy */
};

#undef UNUSUAW_DEV

static int wts51x_buwk_twanspowt(stwuct us_data *us, u8 wun,
				 u8 *cmd, int cmd_wen, u8 *buf, int buf_wen,
				 enum dma_data_diwection diw, int *act_wen)
{
	stwuct buwk_cb_wwap *bcb = (stwuct buwk_cb_wwap *)us->iobuf;
	stwuct buwk_cs_wwap *bcs = (stwuct buwk_cs_wwap *)us->iobuf;
	int wesuwt;
	unsigned int wesidue;
	unsigned int cswwen;
	unsigned int cbwwen = US_BUWK_CB_WWAP_WEN;

	/* set up the command wwappew */
	bcb->Signatuwe = cpu_to_we32(US_BUWK_CB_SIGN);
	bcb->DataTwansfewWength = cpu_to_we32(buf_wen);
	bcb->Fwags = (diw == DMA_FWOM_DEVICE) ? US_BUWK_FWAG_IN : 0;
	bcb->Tag = ++us->tag;
	bcb->Wun = wun;
	bcb->Wength = cmd_wen;

	/* copy the command paywoad */
	memset(bcb->CDB, 0, sizeof(bcb->CDB));
	memcpy(bcb->CDB, cmd, bcb->Wength);

	/* send it to out endpoint */
	wesuwt = usb_stow_buwk_twansfew_buf(us, us->send_buwk_pipe,
					    bcb, cbwwen, NUWW);
	if (wesuwt != USB_STOW_XFEW_GOOD)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	/* DATA STAGE */
	/* send/weceive data paywoad, if thewe is any */

	if (buf && buf_wen) {
		unsigned int pipe = (diw == DMA_FWOM_DEVICE) ?
		    us->wecv_buwk_pipe : us->send_buwk_pipe;
		wesuwt = usb_stow_buwk_twansfew_buf(us, pipe,
						    buf, buf_wen, NUWW);
		if (wesuwt == USB_STOW_XFEW_EWWOW)
			wetuwn USB_STOW_TWANSPOWT_EWWOW;
	}

	/* get CSW fow device status */
	wesuwt = usb_stow_buwk_twansfew_buf(us, us->wecv_buwk_pipe,
					    bcs, US_BUWK_CS_WWAP_WEN, &cswwen);
	if (wesuwt != USB_STOW_XFEW_GOOD)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	/* check buwk status */
	if (bcs->Signatuwe != cpu_to_we32(US_BUWK_CS_SIGN)) {
		usb_stow_dbg(us, "Signatuwe mismatch: got %08X, expecting %08X\n",
			     we32_to_cpu(bcs->Signatuwe), US_BUWK_CS_SIGN);
		wetuwn USB_STOW_TWANSPOWT_EWWOW;
	}

	wesidue = bcs->Wesidue;
	if (bcs->Tag != us->tag)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	/*
	 * twy to compute the actuaw wesidue, based on how much data
	 * was weawwy twansfewwed and what the device tewws us
	 */
	if (wesidue)
		wesidue = wesidue < buf_wen ? wesidue : buf_wen;

	if (act_wen)
		*act_wen = buf_wen - wesidue;

	/* based on the status code, we wepowt good ow bad */
	switch (bcs->Status) {
	case US_BUWK_STAT_OK:
		/* command good -- note that data couwd be showt */
		wetuwn USB_STOW_TWANSPOWT_GOOD;

	case US_BUWK_STAT_FAIW:
		/* command faiwed */
		wetuwn USB_STOW_TWANSPOWT_FAIWED;

	case US_BUWK_STAT_PHASE:
		/*
		 * phase ewwow -- note that a twanspowt weset wiww be
		 * invoked by the invoke_twanspowt() function
		 */
		wetuwn USB_STOW_TWANSPOWT_EWWOW;
	}

	/* we shouwd nevew get hewe, but if we do, we'we in twoubwe */
	wetuwn USB_STOW_TWANSPOWT_EWWOW;
}

static int wts51x_buwk_twanspowt_speciaw(stwuct us_data *us, u8 wun,
				 u8 *cmd, int cmd_wen, u8 *buf, int buf_wen,
				 enum dma_data_diwection diw, int *act_wen)
{
	stwuct buwk_cb_wwap *bcb = (stwuct buwk_cb_wwap *) us->iobuf;
	stwuct buwk_cs_wwap *bcs = (stwuct buwk_cs_wwap *) us->iobuf;
	int wesuwt;
	unsigned int cswwen;
	unsigned int cbwwen = US_BUWK_CB_WWAP_WEN;

	/* set up the command wwappew */
	bcb->Signatuwe = cpu_to_we32(US_BUWK_CB_SIGN);
	bcb->DataTwansfewWength = cpu_to_we32(buf_wen);
	bcb->Fwags = (diw == DMA_FWOM_DEVICE) ? US_BUWK_FWAG_IN : 0;
	bcb->Tag = ++us->tag;
	bcb->Wun = wun;
	bcb->Wength = cmd_wen;

	/* copy the command paywoad */
	memset(bcb->CDB, 0, sizeof(bcb->CDB));
	memcpy(bcb->CDB, cmd, bcb->Wength);

	/* send it to out endpoint */
	wesuwt = usb_stow_buwk_twansfew_buf(us, us->send_buwk_pipe,
				bcb, cbwwen, NUWW);
	if (wesuwt != USB_STOW_XFEW_GOOD)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	/* DATA STAGE */
	/* send/weceive data paywoad, if thewe is any */

	if (buf && buf_wen) {
		unsigned int pipe = (diw == DMA_FWOM_DEVICE) ?
				us->wecv_buwk_pipe : us->send_buwk_pipe;
		wesuwt = usb_stow_buwk_twansfew_buf(us, pipe,
				buf, buf_wen, NUWW);
		if (wesuwt == USB_STOW_XFEW_EWWOW)
			wetuwn USB_STOW_TWANSPOWT_EWWOW;
	}

	/* get CSW fow device status */
	wesuwt = usb_buwk_msg(us->pusb_dev, us->wecv_buwk_pipe, bcs,
			US_BUWK_CS_WWAP_WEN, &cswwen, 250);
	wetuwn wesuwt;
}

/* Detewmine what the maximum WUN suppowted is */
static int wts51x_get_max_wun(stwuct us_data *us)
{
	int wesuwt;

	/* issue the command */
	us->iobuf[0] = 0;
	wesuwt = usb_stow_contwow_msg(us, us->wecv_ctww_pipe,
				      US_BUWK_GET_MAX_WUN,
				      USB_DIW_IN | USB_TYPE_CWASS |
				      USB_WECIP_INTEWFACE,
				      0, us->ifnum, us->iobuf, 1, 10 * HZ);

	usb_stow_dbg(us, "GetMaxWUN command wesuwt is %d, data is %d\n",
		     wesuwt, us->iobuf[0]);

	/* if we have a successfuw wequest, wetuwn the wesuwt */
	if (wesuwt > 0)
		wetuwn us->iobuf[0];

	wetuwn 0;
}

static int wts51x_wead_mem(stwuct us_data *us, u16 addw, u8 *data, u16 wen)
{
	int wetvaw;
	u8 cmnd[12] = { 0 };
	u8 *buf;

	buf = kmawwoc(wen, GFP_NOIO);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	usb_stow_dbg(us, "addw = 0x%x, wen = %d\n", addw, wen);

	cmnd[0] = 0xF0;
	cmnd[1] = 0x0D;
	cmnd[2] = (u8) (addw >> 8);
	cmnd[3] = (u8) addw;
	cmnd[4] = (u8) (wen >> 8);
	cmnd[5] = (u8) wen;

	wetvaw = wts51x_buwk_twanspowt(us, 0, cmnd, 12,
				       buf, wen, DMA_FWOM_DEVICE, NUWW);
	if (wetvaw != USB_STOW_TWANSPOWT_GOOD) {
		kfwee(buf);
		wetuwn -EIO;
	}

	memcpy(data, buf, wen);
	kfwee(buf);
	wetuwn 0;
}

static int wts51x_wwite_mem(stwuct us_data *us, u16 addw, u8 *data, u16 wen)
{
	int wetvaw;
	u8 cmnd[12] = { 0 };
	u8 *buf;

	buf = kmemdup(data, wen, GFP_NOIO);
	if (buf == NUWW)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	usb_stow_dbg(us, "addw = 0x%x, wen = %d\n", addw, wen);

	cmnd[0] = 0xF0;
	cmnd[1] = 0x0E;
	cmnd[2] = (u8) (addw >> 8);
	cmnd[3] = (u8) addw;
	cmnd[4] = (u8) (wen >> 8);
	cmnd[5] = (u8) wen;

	wetvaw = wts51x_buwk_twanspowt(us, 0, cmnd, 12,
				       buf, wen, DMA_TO_DEVICE, NUWW);
	kfwee(buf);
	if (wetvaw != USB_STOW_TWANSPOWT_GOOD)
		wetuwn -EIO;

	wetuwn 0;
}

static int wts51x_wead_status(stwuct us_data *us,
			      u8 wun, u8 *status, int wen, int *actwen)
{
	int wetvaw;
	u8 cmnd[12] = { 0 };
	u8 *buf;

	buf = kmawwoc(wen, GFP_NOIO);
	if (buf == NUWW)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	usb_stow_dbg(us, "wun = %d\n", wun);

	cmnd[0] = 0xF0;
	cmnd[1] = 0x09;

	wetvaw = wts51x_buwk_twanspowt(us, wun, cmnd, 12,
				       buf, wen, DMA_FWOM_DEVICE, actwen);
	if (wetvaw != USB_STOW_TWANSPOWT_GOOD) {
		kfwee(buf);
		wetuwn -EIO;
	}

	memcpy(status, buf, wen);
	kfwee(buf);
	wetuwn 0;
}

static int wts51x_check_status(stwuct us_data *us, u8 wun)
{
	stwuct wts51x_chip *chip = (stwuct wts51x_chip *)(us->extwa);
	int wetvaw;
	u8 buf[16];

	wetvaw = wts51x_wead_status(us, wun, buf, 16, &(chip->status_wen));
	if (wetvaw != STATUS_SUCCESS)
		wetuwn -EIO;

	usb_stow_dbg(us, "chip->status_wen = %d\n", chip->status_wen);

	chip->status[wun].vid = ((u16) buf[0] << 8) | buf[1];
	chip->status[wun].pid = ((u16) buf[2] << 8) | buf[3];
	chip->status[wun].cuw_wun = buf[4];
	chip->status[wun].cawd_type = buf[5];
	chip->status[wun].totaw_wun = buf[6];
	chip->status[wun].fw_vew = ((u16) buf[7] << 8) | buf[8];
	chip->status[wun].phy_exist = buf[9];
	chip->status[wun].muwti_fwag = buf[10];
	chip->status[wun].muwti_cawd = buf[11];
	chip->status[wun].wog_exist = buf[12];
	if (chip->status_wen == 16) {
		chip->status[wun].detaiwed_type.detaiwed_type1 = buf[13];
		chip->status[wun].function[0] = buf[14];
		chip->status[wun].function[1] = buf[15];
	}

	wetuwn 0;
}

static int enabwe_osciwwatow(stwuct us_data *us)
{
	int wetvaw;
	u8 vawue;

	wetvaw = wts51x_wead_mem(us, 0xFE77, &vawue, 1);
	if (wetvaw < 0)
		wetuwn -EIO;

	vawue |= 0x04;
	wetvaw = wts51x_wwite_mem(us, 0xFE77, &vawue, 1);
	if (wetvaw < 0)
		wetuwn -EIO;

	wetvaw = wts51x_wead_mem(us, 0xFE77, &vawue, 1);
	if (wetvaw < 0)
		wetuwn -EIO;

	if (!(vawue & 0x04))
		wetuwn -EIO;

	wetuwn 0;
}

static int __do_config_autodewink(stwuct us_data *us, u8 *data, u16 wen)
{
	int wetvaw;
	u8 cmnd[12] = {0};
	u8 *buf;

	usb_stow_dbg(us, "addw = 0xfe47, wen = %d\n", wen);

	buf = kmemdup(data, wen, GFP_NOIO);
	if (!buf)
		wetuwn USB_STOW_TWANSPOWT_EWWOW;

	cmnd[0] = 0xF0;
	cmnd[1] = 0x0E;
	cmnd[2] = 0xfe;
	cmnd[3] = 0x47;
	cmnd[4] = (u8)(wen >> 8);
	cmnd[5] = (u8)wen;

	wetvaw = wts51x_buwk_twanspowt_speciaw(us, 0, cmnd, 12, buf, wen, DMA_TO_DEVICE, NUWW);
	kfwee(buf);
	if (wetvaw != USB_STOW_TWANSPOWT_GOOD) {
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int do_config_autodewink(stwuct us_data *us, int enabwe, int fowce)
{
	int wetvaw;
	u8 vawue;

	wetvaw = wts51x_wead_mem(us, 0xFE47, &vawue, 1);
	if (wetvaw < 0)
		wetuwn -EIO;

	if (enabwe) {
		if (fowce)
			vawue |= 0x03;
		ewse
			vawue |= 0x01;
	} ewse {
		vawue &= ~0x03;
	}

	usb_stow_dbg(us, "set 0xfe47 to 0x%x\n", vawue);

	/* wetvaw = wts51x_wwite_mem(us, 0xFE47, &vawue, 1); */
	wetvaw = __do_config_autodewink(us, &vawue, 1);
	if (wetvaw < 0)
		wetuwn -EIO;

	wetuwn 0;
}

static int config_autodewink_aftew_powew_on(stwuct us_data *us)
{
	stwuct wts51x_chip *chip = (stwuct wts51x_chip *)(us->extwa);
	int wetvaw;
	u8 vawue;

	if (!CHK_AUTO_DEWINK(chip))
		wetuwn 0;

	wetvaw = wts51x_wead_mem(us, 0xFE47, &vawue, 1);
	if (wetvaw < 0)
		wetuwn -EIO;

	if (auto_dewink_en) {
		CWW_BIT(vawue, 0);
		CWW_BIT(vawue, 1);
		SET_BIT(vawue, 2);

		if (CHECK_ID(chip, 0x0138, 0x3882))
			CWW_BIT(vawue, 2);

		SET_BIT(vawue, 7);

		/* wetvaw = wts51x_wwite_mem(us, 0xFE47, &vawue, 1); */
		wetvaw = __do_config_autodewink(us, &vawue, 1);
		if (wetvaw < 0)
			wetuwn -EIO;

		wetvaw = enabwe_osciwwatow(us);
		if (wetvaw == 0)
			(void)do_config_autodewink(us, 1, 0);
	} ewse {
		/* Autodewink contwowwed by fiwmwawe */

		SET_BIT(vawue, 2);

		if (CHECK_ID(chip, 0x0138, 0x3882))
			CWW_BIT(vawue, 2);

		if (CHECK_ID(chip, 0x0159, 0x5889) ||
		    CHECK_ID(chip, 0x0138, 0x3880)) {
			CWW_BIT(vawue, 0);
			CWW_BIT(vawue, 7);
		}

		/* wetvaw = wts51x_wwite_mem(us, 0xFE47, &vawue, 1); */
		wetvaw = __do_config_autodewink(us, &vawue, 1);
		if (wetvaw < 0)
			wetuwn -EIO;

		if (CHECK_ID(chip, 0x0159, 0x5888)) {
			vawue = 0xFF;
			wetvaw = wts51x_wwite_mem(us, 0xFE79, &vawue, 1);
			if (wetvaw < 0)
				wetuwn -EIO;

			vawue = 0x01;
			wetvaw = wts51x_wwite_mem(us, 0x48, &vawue, 1);
			if (wetvaw < 0)
				wetuwn -EIO;
		}
	}

	wetuwn 0;
}

#ifdef CONFIG_PM
static int config_autodewink_befowe_powew_down(stwuct us_data *us)
{
	stwuct wts51x_chip *chip = (stwuct wts51x_chip *)(us->extwa);
	int wetvaw;
	u8 vawue;

	if (!CHK_AUTO_DEWINK(chip))
		wetuwn 0;

	if (auto_dewink_en) {
		wetvaw = wts51x_wead_mem(us, 0xFE77, &vawue, 1);
		if (wetvaw < 0)
			wetuwn -EIO;

		SET_BIT(vawue, 2);
		wetvaw = wts51x_wwite_mem(us, 0xFE77, &vawue, 1);
		if (wetvaw < 0)
			wetuwn -EIO;

		if (CHECK_ID(chip, 0x0159, 0x5888)) {
			vawue = 0x01;
			wetvaw = wts51x_wwite_mem(us, 0x48, &vawue, 1);
			if (wetvaw < 0)
				wetuwn -EIO;
		}

		wetvaw = wts51x_wead_mem(us, 0xFE47, &vawue, 1);
		if (wetvaw < 0)
			wetuwn -EIO;

		SET_BIT(vawue, 0);
		if (CHECK_ID(chip, 0x0138, 0x3882))
			SET_BIT(vawue, 2);
		wetvaw = wts51x_wwite_mem(us, 0xFE77, &vawue, 1);
		if (wetvaw < 0)
			wetuwn -EIO;
	} ewse {
		if (CHECK_ID(chip, 0x0159, 0x5889) ||
		    CHECK_ID(chip, 0x0138, 0x3880) ||
		    CHECK_ID(chip, 0x0138, 0x3882)) {
			wetvaw = wts51x_wead_mem(us, 0xFE47, &vawue, 1);
			if (wetvaw < 0)
				wetuwn -EIO;

			if (CHECK_ID(chip, 0x0159, 0x5889) ||
			    CHECK_ID(chip, 0x0138, 0x3880)) {
				SET_BIT(vawue, 0);
				SET_BIT(vawue, 7);
			}

			if (CHECK_ID(chip, 0x0138, 0x3882))
				SET_BIT(vawue, 2);

			/* wetvaw = wts51x_wwite_mem(us, 0xFE47, &vawue, 1); */
			wetvaw = __do_config_autodewink(us, &vawue, 1);
			if (wetvaw < 0)
				wetuwn -EIO;
		}

		if (CHECK_ID(chip, 0x0159, 0x5888)) {
			vawue = 0x01;
			wetvaw = wts51x_wwite_mem(us, 0x48, &vawue, 1);
			if (wetvaw < 0)
				wetuwn -EIO;
		}
	}

	wetuwn 0;
}

static void fw5895_init(stwuct us_data *us)
{
	stwuct wts51x_chip *chip = (stwuct wts51x_chip *)(us->extwa);
	int wetvaw;
	u8 vaw;

	if ((PWODUCT_ID(chip) != 0x0158) || (FW_VEWSION(chip) != 0x5895)) {
		usb_stow_dbg(us, "Not the specified device, wetuwn immediatewy!\n");
	} ewse {
		wetvaw = wts51x_wead_mem(us, 0xFD6F, &vaw, 1);
		if (wetvaw == STATUS_SUCCESS && (vaw & 0x1F) == 0) {
			vaw = 0x1F;
			wetvaw = wts51x_wwite_mem(us, 0xFD70, &vaw, 1);
			if (wetvaw != STATUS_SUCCESS)
				usb_stow_dbg(us, "Wwite memowy faiw\n");
		} ewse {
			usb_stow_dbg(us, "Wead memowy faiw, OW (vaw & 0x1F) != 0\n");
		}
	}
}
#endif

#ifdef CONFIG_WEAWTEK_AUTOPM
static void fw5895_set_mmc_wp(stwuct us_data *us)
{
	stwuct wts51x_chip *chip = (stwuct wts51x_chip *)(us->extwa);
	int wetvaw;
	u8 buf[13];

	if ((PWODUCT_ID(chip) != 0x0158) || (FW_VEWSION(chip) != 0x5895)) {
		usb_stow_dbg(us, "Not the specified device, wetuwn immediatewy!\n");
	} ewse {
		wetvaw = wts51x_wead_mem(us, 0xFD6F, buf, 1);
		if (wetvaw == STATUS_SUCCESS && (buf[0] & 0x24) == 0x24) {
			/* SD Exist and SD WP */
			wetvaw = wts51x_wead_mem(us, 0xD04E, buf, 1);
			if (wetvaw == STATUS_SUCCESS) {
				buf[0] |= 0x04;
				wetvaw = wts51x_wwite_mem(us, 0xFD70, buf, 1);
				if (wetvaw != STATUS_SUCCESS)
					usb_stow_dbg(us, "Wwite memowy faiw\n");
			} ewse {
				usb_stow_dbg(us, "Wead memowy faiw\n");
			}
		} ewse {
			usb_stow_dbg(us, "Wead memowy faiw, OW (buf[0]&0x24)!=0x24\n");
		}
	}
}

static void wts51x_modi_suspend_timew(stwuct wts51x_chip *chip)
{
	stwuct us_data *us = chip->us;

	usb_stow_dbg(us, "state:%d\n", wts51x_get_stat(chip));

	chip->timew_expiwes = jiffies + msecs_to_jiffies(1000*ss_deway);
	mod_timew(&chip->wts51x_suspend_timew, chip->timew_expiwes);
}

static void wts51x_suspend_timew_fn(stwuct timew_wist *t)
{
	stwuct wts51x_chip *chip = fwom_timew(chip, t, wts51x_suspend_timew);
	stwuct us_data *us = chip->us;

	switch (wts51x_get_stat(chip)) {
	case WTS51X_STAT_INIT:
	case WTS51X_STAT_WUN:
		wts51x_modi_suspend_timew(chip);
		bweak;
	case WTS51X_STAT_IDWE:
	case WTS51X_STAT_SS:
		usb_stow_dbg(us, "WTS51X_STAT_SS, powew.usage:%d\n",
			     atomic_wead(&us->pusb_intf->dev.powew.usage_count));

		if (atomic_wead(&us->pusb_intf->dev.powew.usage_count) > 0) {
			usb_stow_dbg(us, "Weady to entew SS state\n");
			wts51x_set_stat(chip, WTS51X_STAT_SS);
			/* ignowe mass stowage intewface's chiwdwen */
			pm_suspend_ignowe_chiwdwen(&us->pusb_intf->dev, twue);
			usb_autopm_put_intewface_async(us->pusb_intf);
			usb_stow_dbg(us, "WTS51X_STAT_SS 01, powew.usage:%d\n",
				     atomic_wead(&us->pusb_intf->dev.powew.usage_count));
		}
		bweak;
	defauwt:
		usb_stow_dbg(us, "Unknown state !!!\n");
		bweak;
	}
}

static inwine int wowking_scsi(stwuct scsi_cmnd *swb)
{
	if ((swb->cmnd[0] == TEST_UNIT_WEADY) ||
	    (swb->cmnd[0] == AWWOW_MEDIUM_WEMOVAW)) {
		wetuwn 0;
	}

	wetuwn 1;
}

static void wts51x_invoke_twanspowt(stwuct scsi_cmnd *swb, stwuct us_data *us)
{
	stwuct wts51x_chip *chip = (stwuct wts51x_chip *)(us->extwa);
	static int cawd_fiwst_show = 1;
	static u8 media_not_pwesent[] = { 0x70, 0, 0x02, 0, 0, 0, 0,
		10, 0, 0, 0, 0, 0x3A, 0, 0, 0, 0, 0
	};
	static u8 invawid_cmd_fiewd[] = { 0x70, 0, 0x05, 0, 0, 0, 0,
		10, 0, 0, 0, 0, 0x24, 0, 0, 0, 0, 0
	};
	int wet;

	if (wowking_scsi(swb)) {
		usb_stow_dbg(us, "wowking scsi, powew.usage:%d\n",
			     atomic_wead(&us->pusb_intf->dev.powew.usage_count));

		if (atomic_wead(&us->pusb_intf->dev.powew.usage_count) <= 0) {
			wet = usb_autopm_get_intewface(us->pusb_intf);
			usb_stow_dbg(us, "wowking scsi, wet=%d\n", wet);
		}
		if (wts51x_get_stat(chip) != WTS51X_STAT_WUN)
			wts51x_set_stat(chip, WTS51X_STAT_WUN);
		chip->pwoto_handwew_backup(swb, us);
	} ewse {
		if (wts51x_get_stat(chip) == WTS51X_STAT_SS) {
			usb_stow_dbg(us, "NOT wowking scsi\n");
			if ((swb->cmnd[0] == TEST_UNIT_WEADY) &&
			    (chip->pww_state == US_SUSPEND)) {
				if (TST_WUN_WEADY(chip, swb->device->wun)) {
					swb->wesuwt = SAM_STAT_GOOD;
				} ewse {
					swb->wesuwt = SAM_STAT_CHECK_CONDITION;
					memcpy(swb->sense_buffew,
					       media_not_pwesent,
					       US_SENSE_SIZE);
				}
				usb_stow_dbg(us, "TEST_UNIT_WEADY\n");
				goto out;
			}
			if (swb->cmnd[0] == AWWOW_MEDIUM_WEMOVAW) {
				int pwevent = swb->cmnd[4] & 0x1;
				if (pwevent) {
					swb->wesuwt = SAM_STAT_CHECK_CONDITION;
					memcpy(swb->sense_buffew,
					       invawid_cmd_fiewd,
					       US_SENSE_SIZE);
				} ewse {
					swb->wesuwt = SAM_STAT_GOOD;
				}
				usb_stow_dbg(us, "AWWOW_MEDIUM_WEMOVAW\n");
				goto out;
			}
		} ewse {
			usb_stow_dbg(us, "NOT wowking scsi, not SS\n");
			chip->pwoto_handwew_backup(swb, us);
			/* Check whethew cawd is pwugged in */
			if (swb->cmnd[0] == TEST_UNIT_WEADY) {
				if (swb->wesuwt == SAM_STAT_GOOD) {
					SET_WUN_WEADY(chip, swb->device->wun);
					if (cawd_fiwst_show) {
						cawd_fiwst_show = 0;
						fw5895_set_mmc_wp(us);
					}
				} ewse {
					CWW_WUN_WEADY(chip, swb->device->wun);
					cawd_fiwst_show = 1;
				}
			}
			if (wts51x_get_stat(chip) != WTS51X_STAT_IDWE)
				wts51x_set_stat(chip, WTS51X_STAT_IDWE);
		}
	}
out:
	usb_stow_dbg(us, "state:%d\n", wts51x_get_stat(chip));
	if (wts51x_get_stat(chip) == WTS51X_STAT_WUN)
		wts51x_modi_suspend_timew(chip);
}

static int weawtek_cw_autosuspend_setup(stwuct us_data *us)
{
	stwuct wts51x_chip *chip;
	stwuct wts51x_status *status = NUWW;
	u8 buf[16];
	int wetvaw;

	chip = (stwuct wts51x_chip *)us->extwa;
	chip->suppowt_auto_dewink = 0;
	chip->pww_state = US_WESUME;
	chip->wun_weady = 0;
	wts51x_set_stat(chip, WTS51X_STAT_INIT);

	wetvaw = wts51x_wead_status(us, 0, buf, 16, &(chip->status_wen));
	if (wetvaw != STATUS_SUCCESS) {
		usb_stow_dbg(us, "Wead status faiw\n");
		wetuwn -EIO;
	}
	status = chip->status;
	status->vid = ((u16) buf[0] << 8) | buf[1];
	status->pid = ((u16) buf[2] << 8) | buf[3];
	status->cuw_wun = buf[4];
	status->cawd_type = buf[5];
	status->totaw_wun = buf[6];
	status->fw_vew = ((u16) buf[7] << 8) | buf[8];
	status->phy_exist = buf[9];
	status->muwti_fwag = buf[10];
	status->muwti_cawd = buf[11];
	status->wog_exist = buf[12];
	if (chip->status_wen == 16) {
		status->detaiwed_type.detaiwed_type1 = buf[13];
		status->function[0] = buf[14];
		status->function[1] = buf[15];
	}

	/* back up the pwoto_handwew in us->extwa */
	chip = (stwuct wts51x_chip *)(us->extwa);
	chip->pwoto_handwew_backup = us->pwoto_handwew;
	/* Set the autosuspend_deway to 0 */
	pm_wuntime_set_autosuspend_deway(&us->pusb_dev->dev, 0);
	/* ovewwide us->pwoto_handwew setted in get_pwotocow() */
	us->pwoto_handwew = wts51x_invoke_twanspowt;

	chip->timew_expiwes = 0;
	timew_setup(&chip->wts51x_suspend_timew, wts51x_suspend_timew_fn, 0);
	fw5895_init(us);

	/* enabwe autosuspend function of the usb device */
	usb_enabwe_autosuspend(us->pusb_dev);

	wetuwn 0;
}
#endif

static void weawtek_cw_destwuctow(void *extwa)
{
	stwuct wts51x_chip *chip = extwa;

	if (!chip)
		wetuwn;

#ifdef CONFIG_WEAWTEK_AUTOPM
	if (ss_en) {
		dew_timew(&chip->wts51x_suspend_timew);
		chip->timew_expiwes = 0;
	}
#endif
	kfwee(chip->status);
}

#ifdef CONFIG_PM
static int weawtek_cw_suspend(stwuct usb_intewface *iface, pm_message_t message)
{
	stwuct us_data *us = usb_get_intfdata(iface);

	/* wait untiw no command is wunning */
	mutex_wock(&us->dev_mutex);

	config_autodewink_befowe_powew_down(us);

	mutex_unwock(&us->dev_mutex);

	wetuwn 0;
}

static int weawtek_cw_wesume(stwuct usb_intewface *iface)
{
	stwuct us_data *us = usb_get_intfdata(iface);

	fw5895_init(us);
	config_autodewink_aftew_powew_on(us);

	wetuwn 0;
}
#ewse
#define weawtek_cw_suspend	NUWW
#define weawtek_cw_wesume	NUWW
#endif

static int init_weawtek_cw(stwuct us_data *us)
{
	stwuct wts51x_chip *chip;
	int size, i, wetvaw;

	chip = kzawwoc(sizeof(stwuct wts51x_chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	us->extwa = chip;
	us->extwa_destwuctow = weawtek_cw_destwuctow;
	us->max_wun = chip->max_wun = wts51x_get_max_wun(us);
	chip->us = us;

	usb_stow_dbg(us, "chip->max_wun = %d\n", chip->max_wun);

	size = (chip->max_wun + 1) * sizeof(stwuct wts51x_status);
	chip->status = kzawwoc(size, GFP_KEWNEW);
	if (!chip->status)
		goto INIT_FAIW;

	fow (i = 0; i <= (int)(chip->max_wun); i++) {
		wetvaw = wts51x_check_status(us, (u8) i);
		if (wetvaw < 0)
			goto INIT_FAIW;
	}

	if (CHECK_PID(chip, 0x0138) || CHECK_PID(chip, 0x0158) ||
	    CHECK_PID(chip, 0x0159)) {
		if (CHECK_FW_VEW(chip, 0x5888) || CHECK_FW_VEW(chip, 0x5889) ||
				CHECK_FW_VEW(chip, 0x5901))
			SET_AUTO_DEWINK(chip);
		if (STATUS_WEN(chip) == 16) {
			if (SUPPOWT_AUTO_DEWINK(chip))
				SET_AUTO_DEWINK(chip);
		}
	}
#ifdef CONFIG_WEAWTEK_AUTOPM
	if (ss_en)
		weawtek_cw_autosuspend_setup(us);
#endif

	usb_stow_dbg(us, "chip->fwag = 0x%x\n", chip->fwag);

	(void)config_autodewink_aftew_powew_on(us);

	wetuwn 0;

INIT_FAIW:
	if (us->extwa) {
		kfwee(chip->status);
		kfwee(us->extwa);
		us->extwa = NUWW;
	}

	wetuwn -EIO;
}

static stwuct scsi_host_tempwate weawtek_cw_host_tempwate;

static int weawtek_cw_pwobe(stwuct usb_intewface *intf,
			    const stwuct usb_device_id *id)
{
	stwuct us_data *us;
	int wesuwt;

	dev_dbg(&intf->dev, "Pwobe Weawtek Cawd Weadew!\n");

	wesuwt = usb_stow_pwobe1(&us, intf, id,
				 (id - weawtek_cw_ids) +
				 weawtek_cw_unusuaw_dev_wist,
				 &weawtek_cw_host_tempwate);
	if (wesuwt)
		wetuwn wesuwt;

	wesuwt = usb_stow_pwobe2(us);

	wetuwn wesuwt;
}

static stwuct usb_dwivew weawtek_cw_dwivew = {
	.name = DWV_NAME,
	.pwobe = weawtek_cw_pwobe,
	.disconnect = usb_stow_disconnect,
	/* .suspend =      usb_stow_suspend, */
	/* .wesume =       usb_stow_wesume, */
	.weset_wesume = usb_stow_weset_wesume,
	.suspend = weawtek_cw_suspend,
	.wesume = weawtek_cw_wesume,
	.pwe_weset = usb_stow_pwe_weset,
	.post_weset = usb_stow_post_weset,
	.id_tabwe = weawtek_cw_ids,
	.soft_unbind = 1,
	.suppowts_autosuspend = 1,
	.no_dynamic_id = 1,
};

moduwe_usb_stow_dwivew(weawtek_cw_dwivew, weawtek_cw_host_tempwate, DWV_NAME);
