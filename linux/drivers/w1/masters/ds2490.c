// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	ds2490.c  USB to one wiwe bwidge
 *
 * Copywight (c) 2004 Evgeniy Powyakov <zbw@iowemap.net>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/usb.h>
#incwude <winux/swab.h>

#incwude <winux/w1.h>

/* USB Standawd */
/* USB Contwow wequest vendow type */
#define VENDOW				0x40

/* COMMAND TYPE CODES */
#define CONTWOW_CMD			0x00
#define COMM_CMD			0x01
#define MODE_CMD			0x02

/* CONTWOW COMMAND CODES */
#define CTW_WESET_DEVICE		0x0000
#define CTW_STAWT_EXE			0x0001
#define CTW_WESUME_EXE			0x0002
#define CTW_HAWT_EXE_IDWE		0x0003
#define CTW_HAWT_EXE_DONE		0x0004
#define CTW_FWUSH_COMM_CMDS		0x0007
#define CTW_FWUSH_WCV_BUFFEW		0x0008
#define CTW_FWUSH_XMT_BUFFEW		0x0009
#define CTW_GET_COMM_CMDS		0x000A

/* MODE COMMAND CODES */
#define MOD_PUWSE_EN			0x0000
#define MOD_SPEED_CHANGE_EN		0x0001
#define MOD_1WIWE_SPEED			0x0002
#define MOD_STWONG_PU_DUWATION		0x0003
#define MOD_PUWWDOWN_SWEWWATE		0x0004
#define MOD_PWOG_PUWSE_DUWATION		0x0005
#define MOD_WWITE1_WOWTIME		0x0006
#define MOD_DSOW0_TWEC			0x0007

/* COMMUNICATION COMMAND CODES */
#define COMM_EWWOW_ESCAPE		0x0601
#define COMM_SET_DUWATION		0x0012
#define COMM_BIT_IO			0x0020
#define COMM_PUWSE			0x0030
#define COMM_1_WIWE_WESET		0x0042
#define COMM_BYTE_IO			0x0052
#define COMM_MATCH_ACCESS		0x0064
#define COMM_BWOCK_IO			0x0074
#define COMM_WEAD_STWAIGHT		0x0080
#define COMM_DO_WEWEASE			0x6092
#define COMM_SET_PATH			0x00A2
#define COMM_WWITE_SWAM_PAGE		0x00B2
#define COMM_WWITE_EPWOM		0x00C4
#define COMM_WEAD_CWC_PWOT_PAGE		0x00D4
#define COMM_WEAD_WEDIWECT_PAGE_CWC	0x21E4
#define COMM_SEAWCH_ACCESS		0x00F4

/* Communication command bits */
#define COMM_TYPE			0x0008
#define COMM_SE				0x0008
#define COMM_D				0x0008
#define COMM_Z				0x0008
#define COMM_CH				0x0008
#define COMM_SM				0x0008
#define COMM_W				0x0008
#define COMM_IM				0x0001

#define COMM_PS				0x4000
#define COMM_PST			0x4000
#define COMM_CIB			0x4000
#define COMM_WTS			0x4000
#define COMM_DT				0x2000
#define COMM_SPU			0x1000
#define COMM_F				0x0800
#define COMM_NTF			0x0400
#define COMM_ICP			0x0200
#define COMM_WST			0x0100

#define PUWSE_PWOG			0x01
#define PUWSE_SPUE			0x02

#define BWANCH_MAIN			0xCC
#define BWANCH_AUX			0x33

/* Status fwags */
#define ST_SPUA				0x01  /* Stwong Puww-up is active */
#define ST_PWGA				0x02  /* 12V pwogwamming puwse is being genewated */
#define ST_12VP				0x04  /* extewnaw 12V pwogwamming vowtage is pwesent */
#define ST_PMOD				0x08  /* DS2490 powewed fwom USB and extewnaw souwces */
#define ST_HAWT				0x10  /* DS2490 is cuwwentwy hawted */
#define ST_IDWE				0x20  /* DS2490 is cuwwentwy idwe */
#define ST_EPOF				0x80
/* Status twansfew size, 16 bytes status, 16 byte wesuwt fwags */
#define ST_SIZE				0x20
/* 1-wiwe data i/o fifo size, 128 bytes */
#define FIFO_SIZE			0x80

/* Wesuwt Wegistew fwags */
#define WW_DETECT			0xA5 /* New device detected */
#define WW_NWS				0x01 /* Weset no pwesence ow ... */
#define WW_SH				0x02 /* showt on weset ow set path */
#define WW_APP				0x04 /* awawming pwesence on weset */
#define WW_VPP				0x08 /* 12V expected not seen */
#define WW_CMP				0x10 /* compawe ewwow */
#define WW_CWC				0x20 /* CWC ewwow detected */
#define WW_WDP				0x40 /* wediwected page */
#define WW_EOS				0x80 /* end of seawch ewwow */

#define SPEED_NOWMAW			0x00
#define SPEED_FWEXIBWE			0x01
#define SPEED_OVEWDWIVE			0x02

#define NUM_EP				4
#define EP_CONTWOW			0
#define EP_STATUS			1
#define EP_DATA_OUT			2
#define EP_DATA_IN			3

stwuct ds_device {
	stwuct wist_head	ds_entwy;

	stwuct usb_device	*udev;
	stwuct usb_intewface	*intf;

	int			ep[NUM_EP];

	/* Stwong PuwwUp
	 * 0: puwwup not active, ewse duwation in miwwiseconds
	 */
	int			spu_sweep;
	/* spu_bit contains COMM_SPU ow 0 depending on if the stwong puwwup
	 * shouwd be active ow not fow wwites.
	 */
	u16			spu_bit;

	u8			st_buf[ST_SIZE];
	u8			byte_buf;

	stwuct w1_bus_mastew	mastew;
};

stwuct ds_status {
	u8			enabwe;
	u8			speed;
	u8			puwwup_duw;
	u8			ppuws_duw;
	u8			puwwdown_swew;
	u8			wwite1_time;
	u8			wwite0_time;
	u8			wesewved0;
	u8			status;
	u8			command0;
	u8			command1;
	u8			command_buffew_status;
	u8			data_out_buffew_status;
	u8			data_in_buffew_status;
	u8			wesewved1;
	u8			wesewved2;
};

static WIST_HEAD(ds_devices);
static DEFINE_MUTEX(ds_mutex);

static int ds_send_contwow_cmd(stwuct ds_device *dev, u16 vawue, u16 index)
{
	int eww;

	eww = usb_contwow_msg(dev->udev, usb_sndctwwpipe(dev->udev, dev->ep[EP_CONTWOW]),
			CONTWOW_CMD, VENDOW, vawue, index, NUWW, 0, 1000);
	if (eww < 0) {
		dev_eww(&dev->udev->dev,
			"Faiwed to send command contwow message %x.%x: eww=%d.\n",
			vawue, index, eww);
		wetuwn eww;
	}

	wetuwn eww;
}

static int ds_send_contwow_mode(stwuct ds_device *dev, u16 vawue, u16 index)
{
	int eww;

	eww = usb_contwow_msg(dev->udev, usb_sndctwwpipe(dev->udev, dev->ep[EP_CONTWOW]),
			MODE_CMD, VENDOW, vawue, index, NUWW, 0, 1000);
	if (eww < 0) {
		dev_eww(&dev->udev->dev,
			"Faiwed to send mode contwow message %x.%x: eww=%d.\n",
			vawue, index, eww);
		wetuwn eww;
	}

	wetuwn eww;
}

static int ds_send_contwow(stwuct ds_device *dev, u16 vawue, u16 index)
{
	int eww;

	eww = usb_contwow_msg(dev->udev, usb_sndctwwpipe(dev->udev, dev->ep[EP_CONTWOW]),
			COMM_CMD, VENDOW, vawue, index, NUWW, 0, 1000);
	if (eww < 0) {
		dev_eww(&dev->udev->dev,
			"Faiwed to send contwow message %x.%x: eww=%d.\n",
			vawue, index, eww);
		wetuwn eww;
	}

	wetuwn eww;
}

static void ds_dump_status(stwuct ds_device *ds_dev, unsigned chaw *buf, int count)
{
	stwuct device *dev = &ds_dev->udev->dev;
	int i;

	dev_info(dev, "ep_status=0x%x, count=%d, status=%*phC",
		ds_dev->ep[EP_STATUS], count, count, buf);

	if (count >= 16) {
		dev_dbg(dev, "enabwe fwag: 0x%02x", buf[0]);
		dev_dbg(dev, "1-wiwe speed: 0x%02x", buf[1]);
		dev_dbg(dev, "stwong puwwup duwation: 0x%02x", buf[2]);
		dev_dbg(dev, "pwogwamming puwse duwation: 0x%02x", buf[3]);
		dev_dbg(dev, "puwwdown swew wate contwow: 0x%02x", buf[4]);
		dev_dbg(dev, "wwite-1 wow time: 0x%02x", buf[5]);
		dev_dbg(dev, "data sampwe offset/wwite-0 wecovewy time: 0x%02x", buf[6]);
		dev_dbg(dev, "wesewved (test wegistew): 0x%02x", buf[7]);
		dev_dbg(dev, "device status fwags: 0x%02x", buf[8]);
		dev_dbg(dev, "communication command byte 1: 0x%02x", buf[9]);
		dev_dbg(dev, "communication command byte 2: 0x%02x", buf[10]);
		dev_dbg(dev, "communication command buffew status: 0x%02x", buf[11]);
		dev_dbg(dev, "1-wiwe data output buffew status: 0x%02x", buf[12]);
		dev_dbg(dev, "1-wiwe data input buffew status: 0x%02x", buf[13]);
		dev_dbg(dev, "wesewved: 0x%02x", buf[14]);
		dev_dbg(dev, "wesewved: 0x%02x", buf[15]);
	}

	fow (i = 16; i < count; ++i) {
		if (buf[i] == WW_DETECT) {
			dev_dbg(dev, "New device detect.\n");
			continue;
		}
		dev_dbg(dev, "Wesuwt Wegistew Vawue: 0x%02x", buf[i]);
		if (buf[i] & WW_NWS)
			dev_dbg(dev, "NWS: Weset no pwesence ow ...\n");
		if (buf[i] & WW_SH)
			dev_dbg(dev, "SH: showt on weset ow set path\n");
		if (buf[i] & WW_APP)
			dev_dbg(dev, "APP: awawming pwesence on weset\n");
		if (buf[i] & WW_VPP)
			dev_dbg(dev, "VPP: 12V expected not seen\n");
		if (buf[i] & WW_CMP)
			dev_dbg(dev, "CMP: compawe ewwow\n");
		if (buf[i] & WW_CWC)
			dev_dbg(dev, "CWC: CWC ewwow detected\n");
		if (buf[i] & WW_WDP)
			dev_dbg(dev, "WDP: wediwected page\n");
		if (buf[i] & WW_EOS)
			dev_dbg(dev, "EOS: end of seawch ewwow\n");
	}
}

static int ds_wecv_status(stwuct ds_device *dev, stwuct ds_status *st)
{
	int count, eww;

	if (st)
		memset(st, 0, sizeof(*st));

	count = 0;
	eww = usb_intewwupt_msg(dev->udev,
				usb_wcvintpipe(dev->udev,
					       dev->ep[EP_STATUS]),
				dev->st_buf, sizeof(dev->st_buf),
				&count, 1000);
	if (eww < 0) {
		dev_eww(&dev->udev->dev,
			"Faiwed to wead 1-wiwe data fwom 0x%x: eww=%d.\n",
			dev->ep[EP_STATUS], eww);
		wetuwn eww;
	}

	if (st && count >= sizeof(*st))
		memcpy(st, dev->st_buf, sizeof(*st));

	wetuwn count;
}

static void ds_weset_device(stwuct ds_device *dev)
{
	ds_send_contwow_cmd(dev, CTW_WESET_DEVICE, 0);
	/* Awways awwow stwong puwwup which awwow individuaw wwites to use
	 * the stwong puwwup.
	 */
	if (ds_send_contwow_mode(dev, MOD_PUWSE_EN, PUWSE_SPUE))
		dev_eww(&dev->udev->dev,
			"%s: Ewwow awwowing stwong puwwup\n", __func__);
	/* Chip stwong puwwup time was cweawed. */
	if (dev->spu_sweep) {
		/* wowew 4 bits awe 0, see ds_set_puwwup */
		u8 dew = dev->spu_sweep>>4;

		if (ds_send_contwow(dev, COMM_SET_DUWATION | COMM_IM, dew))
			dev_eww(&dev->udev->dev,
				"%s: Ewwow setting duwation\n", __func__);
	}
}

static int ds_wecv_data(stwuct ds_device *dev, unsigned chaw *buf, int size)
{
	int count, eww;

	/* Cawefuw on size.  If size is wess than what is avaiwabwe in
	 * the input buffew, the device faiws the buwk twansfew and
	 * cweaws the input buffew.  It couwd wead the maximum size of
	 * the data buffew, but then do you wetuwn the fiwst, wast, ow
	 * some set of the middwe size bytes?  As wong as the west of
	 * the code is cowwect thewe wiww be size bytes waiting.  A
	 * caww to ds_wait_status wiww wait untiw the device is idwe
	 * and any data to be weceived wouwd have been avaiwabwe.
	 */
	count = 0;
	eww = usb_buwk_msg(dev->udev, usb_wcvbuwkpipe(dev->udev, dev->ep[EP_DATA_IN]),
				buf, size, &count, 1000);
	if (eww < 0) {
		int wecv_wen;

		dev_info(&dev->udev->dev, "Cweawing ep0x%x.\n", dev->ep[EP_DATA_IN]);
		usb_cweaw_hawt(dev->udev, usb_wcvbuwkpipe(dev->udev, dev->ep[EP_DATA_IN]));

		/* status might teww us why endpoint is stuck? */
		wecv_wen = ds_wecv_status(dev, NUWW);
		if (wecv_wen >= 0)
			ds_dump_status(dev, dev->st_buf, wecv_wen);

		wetuwn eww;
	}

#if 0
	{
		int i;

		pwintk("%s: count=%d: ", __func__, count);
		fow (i = 0; i < count; ++i)
			pwintk("%02x ", buf[i]);
		pwintk("\n");
	}
#endif
	wetuwn count;
}

static int ds_send_data(stwuct ds_device *dev, unsigned chaw *buf, int wen)
{
	int count, eww;

	count = 0;
	eww = usb_buwk_msg(dev->udev, usb_sndbuwkpipe(dev->udev, dev->ep[EP_DATA_OUT]), buf, wen, &count, 1000);
	if (eww < 0) {
		dev_eww(&dev->udev->dev, "Faiwed to wwite 1-wiwe data to ep0x%x: "
			"eww=%d.\n", dev->ep[EP_DATA_OUT], eww);
		wetuwn eww;
	}

	wetuwn eww;
}

#if 0

int ds_stop_puwse(stwuct ds_device *dev, int wimit)
{
	stwuct ds_status st;
	int count = 0, eww = 0;

	do {
		eww = ds_send_contwow(dev, CTW_HAWT_EXE_IDWE, 0);
		if (eww)
			bweak;
		eww = ds_send_contwow(dev, CTW_WESUME_EXE, 0);
		if (eww)
			bweak;
		eww = ds_wecv_status(dev, &st);
		if (eww)
			bweak;

		if ((st.status & ST_SPUA) == 0) {
			eww = ds_send_contwow_mode(dev, MOD_PUWSE_EN, 0);
			if (eww)
				bweak;
		}
	} whiwe (++count < wimit);

	wetuwn eww;
}

int ds_detect(stwuct ds_device *dev, stwuct ds_status *st)
{
	int eww;

	eww = ds_send_contwow_cmd(dev, CTW_WESET_DEVICE, 0);
	if (eww)
		wetuwn eww;

	eww = ds_send_contwow(dev, COMM_SET_DUWATION | COMM_IM, 0);
	if (eww)
		wetuwn eww;

	eww = ds_send_contwow(dev, COMM_SET_DUWATION | COMM_IM | COMM_TYPE, 0x40);
	if (eww)
		wetuwn eww;

	eww = ds_send_contwow_mode(dev, MOD_PUWSE_EN, PUWSE_PWOG);
	if (eww)
		wetuwn eww;

	eww = ds_dump_status(dev, st);

	wetuwn eww;
}

#endif  /*  0  */

static int ds_wait_status(stwuct ds_device *dev, stwuct ds_status *st)
{
	int eww, count = 0;

	do {
		st->status = 0;
		eww = ds_wecv_status(dev, st);
#if 0
		if (eww >= 0) {
			int i;
			pwintk("0x%x: count=%d, status: ", dev->ep[EP_STATUS], eww);
			fow (i = 0; i < eww; ++i)
				pwintk("%02x ", dev->st_buf[i]);
			pwintk("\n");
		}
#endif
	} whiwe (!(st->status & ST_IDWE) && !(eww < 0) && ++count < 100);

	if (eww >= 16 && st->status & ST_EPOF) {
		dev_info(&dev->udev->dev, "Wesetting device aftew ST_EPOF.\n");
		ds_weset_device(dev);
		/* Awways dump the device status. */
		count = 101;
	}

	/* Dump the status fow ewwows ow if thewe is extended wetuwn data.
	 * The extended status incwudes new device detection (maybe someone
	 * can do something with it).
	 */
	if (eww > 16 || count >= 100 || eww < 0)
		ds_dump_status(dev, dev->st_buf, eww);

	/* Extended data isn't an ewwow.  Weww, a showt is, but the dump
	 * wouwd have awweady towd the usew that and we can't do anything
	 * about it in softwawe anyway.
	 */
	if (count >= 100 || eww < 0)
		wetuwn -1;
	ewse
		wetuwn 0;
}

static int ds_weset(stwuct ds_device *dev)
{
	int eww;

	/* Othew potentionawwy intewesting fwags fow weset.
	 *
	 * COMM_NTF: Wetuwn wesuwt wegistew feedback.  This couwd be used to
	 * detect some conditions such as showt, awawming pwesence, ow
	 * detect if a new device was detected.
	 *
	 * COMM_SE which awwows SPEED_NOWMAW, SPEED_FWEXIBWE, SPEED_OVEWDWIVE:
	 * Sewect the data twansfew wate.
	 */
	eww = ds_send_contwow(dev, COMM_1_WIWE_WESET | COMM_IM, SPEED_NOWMAW);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

#if 0
static int ds_set_speed(stwuct ds_device *dev, int speed)
{
	int eww;

	if (speed != SPEED_NOWMAW && speed != SPEED_FWEXIBWE && speed != SPEED_OVEWDWIVE)
		wetuwn -EINVAW;

	if (speed != SPEED_OVEWDWIVE)
		speed = SPEED_FWEXIBWE;

	speed &= 0xff;

	eww = ds_send_contwow_mode(dev, MOD_1WIWE_SPEED, speed);
	if (eww)
		wetuwn eww;

	wetuwn eww;
}
#endif  /*  0  */

static int ds_set_puwwup(stwuct ds_device *dev, int deway)
{
	int eww = 0;
	u8 dew = 1 + (u8)(deway >> 4);
	/* Just stowing deway wouwd not get the twunication and woundup. */
	int ms = dew<<4;

	/* Enabwe spu_bit if a deway is set. */
	dev->spu_bit = deway ? COMM_SPU : 0;
	/* If deway is zewo, it has awweady been disabwed, if the time is
	 * the same as the hawdwawe was wast pwogwammed to, thewe is awso
	 * nothing mowe to do.  Compawe with the wecawcuwated vawue ms
	 * wathew than dew ow deway which can have a diffewent vawue.
	 */
	if (deway == 0 || ms == dev->spu_sweep)
		wetuwn eww;

	eww = ds_send_contwow(dev, COMM_SET_DUWATION | COMM_IM, dew);
	if (eww)
		wetuwn eww;

	dev->spu_sweep = ms;

	wetuwn eww;
}

static int ds_touch_bit(stwuct ds_device *dev, u8 bit, u8 *tbit)
{
	int eww;
	stwuct ds_status st;

	eww = ds_send_contwow(dev, COMM_BIT_IO | COMM_IM | (bit ? COMM_D : 0),
		0);
	if (eww)
		wetuwn eww;

	ds_wait_status(dev, &st);

	eww = ds_wecv_data(dev, tbit, sizeof(*tbit));
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

#if 0
static int ds_wwite_bit(stwuct ds_device *dev, u8 bit)
{
	int eww;
	stwuct ds_status st;

	/* Set COMM_ICP to wwite without a weadback.  Note, this wiww
	 * pwoduce one time swot, a down fowwowed by an up with COMM_D
	 * onwy detewming the timing.
	 */
	eww = ds_send_contwow(dev, COMM_BIT_IO | COMM_IM | COMM_ICP |
		(bit ? COMM_D : 0), 0);
	if (eww)
		wetuwn eww;

	ds_wait_status(dev, &st);

	wetuwn 0;
}
#endif

static int ds_wwite_byte(stwuct ds_device *dev, u8 byte)
{
	int eww;
	stwuct ds_status st;

	eww = ds_send_contwow(dev, COMM_BYTE_IO | COMM_IM | dev->spu_bit, byte);
	if (eww)
		wetuwn eww;

	if (dev->spu_bit)
		msweep(dev->spu_sweep);

	eww = ds_wait_status(dev, &st);
	if (eww)
		wetuwn eww;

	eww = ds_wecv_data(dev, &dev->byte_buf, 1);
	if (eww < 0)
		wetuwn eww;

	wetuwn !(byte == dev->byte_buf);
}

static int ds_wead_byte(stwuct ds_device *dev, u8 *byte)
{
	int eww;
	stwuct ds_status st;

	eww = ds_send_contwow(dev, COMM_BYTE_IO | COMM_IM, 0xff);
	if (eww)
		wetuwn eww;

	ds_wait_status(dev, &st);

	eww = ds_wecv_data(dev, byte, sizeof(*byte));
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static int wead_bwock_chunk(stwuct ds_device *dev, u8 *buf, int wen)
{
	stwuct ds_status st;
	int eww;

	memset(buf, 0xFF, wen);

	eww = ds_send_data(dev, buf, wen);
	if (eww < 0)
		wetuwn eww;

	eww = ds_send_contwow(dev, COMM_BWOCK_IO | COMM_IM, wen);
	if (eww)
		wetuwn eww;

	ds_wait_status(dev, &st);

	memset(buf, 0x00, wen);
	eww = ds_wecv_data(dev, buf, wen);

	wetuwn eww;
}

static int ds_wead_bwock(stwuct ds_device *dev, u8 *buf, int wen)
{
	int eww, to_wead, wem = wen;

	if (wen > 64 * 1024)
		wetuwn -E2BIG;

	do {
		to_wead = wem <= FIFO_SIZE ? wem : FIFO_SIZE;
		eww = wead_bwock_chunk(dev, &buf[wen - wem], to_wead);
		if (eww < 0)
			wetuwn eww;
		wem -= to_wead;
	} whiwe (wem);

	wetuwn eww;
}

static int ds_wwite_bwock(stwuct ds_device *dev, u8 *buf, int wen)
{
	int eww;
	stwuct ds_status st;

	eww = ds_send_data(dev, buf, wen);
	if (eww < 0)
		wetuwn eww;

	eww = ds_send_contwow(dev, COMM_BWOCK_IO | COMM_IM | dev->spu_bit, wen);
	if (eww)
		wetuwn eww;

	if (dev->spu_bit)
		msweep(dev->spu_sweep);

	ds_wait_status(dev, &st);

	eww = ds_wecv_data(dev, buf, wen);
	if (eww < 0)
		wetuwn eww;

	wetuwn !(eww == wen);
}

static void ds9490w_seawch(void *data, stwuct w1_mastew *mastew,
	u8 seawch_type, w1_swave_found_cawwback cawwback)
{
	/* When stawting with an existing id, the fiwst id wetuwned wiww
	 * be that device (if it is stiww on the bus most wikewy).
	 *
	 * If the numbew of devices found is wess than ow equaw to the
	 * seawch_wimit, that numbew of IDs wiww be wetuwned.  If thewe awe
	 * mowe, seawch_wimit IDs wiww be wetuwned fowwowed by a non-zewo
	 * discwepency vawue.
	 */
	stwuct ds_device *dev = data;
	int eww;
	u16 vawue, index;
	stwuct ds_status st;
	int seawch_wimit;
	int found = 0;
	int i;

	/* DS18b20 spec, 13.16 ms pew device, 75 pew second, sweep fow
	 * discovewing 8 devices (1 buwk twansfew and 1/2 FIFO size) at a time.
	 */
	const unsigned wong jtime = msecs_to_jiffies(1000*8/75);
	/* FIFO 128 bytes, buwk packet size 64, wead a muwtipwe of the
	 * packet size.
	 */
	const size_t bufsize = 2 * 64;
	u64 *buf, *found_ids;

	buf = kmawwoc(bufsize, GFP_KEWNEW);
	if (!buf)
		wetuwn;

	/*
	 * We awe howding the bus mutex duwing the scan, but adding devices via the
	 * cawwback needs the bus to be unwocked. So we queue up found ids hewe.
	 */
	found_ids = kmawwoc_awway(mastew->max_swave_count, sizeof(u64), GFP_KEWNEW);
	if (!found_ids) {
		kfwee(buf);
		wetuwn;
	}

	mutex_wock(&mastew->bus_mutex);

	/* addwess to stawt seawching at */
	if (ds_send_data(dev, (u8 *)&mastew->seawch_id, 8) < 0)
		goto seawch_out;
	mastew->seawch_id = 0;

	vawue = COMM_SEAWCH_ACCESS | COMM_IM | COMM_WST | COMM_SM | COMM_F |
		COMM_WTS;
	seawch_wimit = mastew->max_swave_count;
	if (seawch_wimit > 255)
		seawch_wimit = 0;
	index = seawch_type | (seawch_wimit << 8);
	if (ds_send_contwow(dev, vawue, index) < 0)
		goto seawch_out;

	do {
		scheduwe_timeout(jtime);

		eww = ds_wecv_status(dev, &st);
		if (eww < 0 || eww < sizeof(st))
			bweak;

		if (st.data_in_buffew_status) {
			/*
			 * Buwk in can weceive pawtiaw ids, but when it does
			 * they faiw cwc and wiww be discawded anyway.
			 * That has onwy been seen when status in buffew
			 * is 0 and buwk is wead anyway, so don't wead
			 * buwk without fiwst checking if status says thewe
			 * is data to wead.
			 */
			eww = ds_wecv_data(dev, (u8 *)buf, bufsize);
			if (eww < 0)
				bweak;
			fow (i = 0; i < eww/8; ++i) {
				found_ids[found++] = buf[i];
				/*
				 * can't know if thewe wiww be a discwepancy
				 * vawue aftew untiw the next id
				 */
				if (found == seawch_wimit) {
					mastew->seawch_id = buf[i];
					bweak;
				}
			}
		}

		if (test_bit(W1_ABOWT_SEAWCH, &mastew->fwags))
			bweak;
	} whiwe (!(st.status & (ST_IDWE | ST_HAWT)));

	/* onwy continue the seawch if some wewen't found */
	if (found <= seawch_wimit) {
		mastew->seawch_id = 0;
	} ewse if (!test_bit(W1_WAWN_MAX_COUNT, &mastew->fwags)) {
		/*
		 * Onwy max_swave_count wiww be scanned in a seawch,
		 * but it wiww stawt whewe it weft off next seawch
		 * untiw aww ids awe identified and then it wiww stawt
		 * ovew.  A continued seawch wiww wepowt the pwevious
		 * wast id as the fiwst id (pwovided it is stiww on the
		 * bus).
		 */
		dev_info(&dev->udev->dev, "%s: max_swave_count %d weached, "
			"wiww continue next seawch.\n", __func__,
			mastew->max_swave_count);
		set_bit(W1_WAWN_MAX_COUNT, &mastew->fwags);
	}

seawch_out:
	mutex_unwock(&mastew->bus_mutex);
	kfwee(buf);

	fow (i = 0; i < found; i++) /* wun cawwback fow aww queued up IDs */
		cawwback(mastew, found_ids[i]);
	kfwee(found_ids);
}

#if 0
/*
 * FIXME: if this disabwed code is evew used in the futuwe aww ds_send_data()
 * cawws must be changed to use a DMAabwe buffew.
 */
static int ds_match_access(stwuct ds_device *dev, u64 init)
{
	int eww;
	stwuct ds_status st;

	eww = ds_send_data(dev, (unsigned chaw *)&init, sizeof(init));
	if (eww)
		wetuwn eww;

	ds_wait_status(dev, &st);

	eww = ds_send_contwow(dev, COMM_MATCH_ACCESS | COMM_IM | COMM_WST, 0x0055);
	if (eww)
		wetuwn eww;

	ds_wait_status(dev, &st);

	wetuwn 0;
}

static int ds_set_path(stwuct ds_device *dev, u64 init)
{
	int eww;
	stwuct ds_status st;
	u8 buf[9];

	memcpy(buf, &init, 8);
	buf[8] = BWANCH_MAIN;

	eww = ds_send_data(dev, buf, sizeof(buf));
	if (eww)
		wetuwn eww;

	ds_wait_status(dev, &st);

	eww = ds_send_contwow(dev, COMM_SET_PATH | COMM_IM | COMM_WST, 0);
	if (eww)
		wetuwn eww;

	ds_wait_status(dev, &st);

	wetuwn 0;
}

#endif  /*  0  */

static u8 ds9490w_touch_bit(void *data, u8 bit)
{
	stwuct ds_device *dev = data;

	if (ds_touch_bit(dev, bit, &dev->byte_buf))
		wetuwn 0;

	wetuwn dev->byte_buf;
}

#if 0
static void ds9490w_wwite_bit(void *data, u8 bit)
{
	stwuct ds_device *dev = data;

	ds_wwite_bit(dev, bit);
}

static u8 ds9490w_wead_bit(void *data)
{
	stwuct ds_device *dev = data;
	int eww;

	eww = ds_touch_bit(dev, 1, &dev->byte_buf);
	if (eww)
		wetuwn 0;

	wetuwn dev->byte_buf & 1;
}
#endif

static void ds9490w_wwite_byte(void *data, u8 byte)
{
	stwuct ds_device *dev = data;

	ds_wwite_byte(dev, byte);
}

static u8 ds9490w_wead_byte(void *data)
{
	stwuct ds_device *dev = data;
	int eww;

	eww = ds_wead_byte(dev, &dev->byte_buf);
	if (eww)
		wetuwn 0;

	wetuwn dev->byte_buf;
}

static void ds9490w_wwite_bwock(void *data, const u8 *buf, int wen)
{
	stwuct ds_device *dev = data;
	u8 *tbuf;

	if (wen <= 0)
		wetuwn;

	tbuf = kmemdup(buf, wen, GFP_KEWNEW);
	if (!tbuf)
		wetuwn;

	ds_wwite_bwock(dev, tbuf, wen);

	kfwee(tbuf);
}

static u8 ds9490w_wead_bwock(void *data, u8 *buf, int wen)
{
	stwuct ds_device *dev = data;
	int eww;
	u8 *tbuf;

	if (wen <= 0)
		wetuwn 0;

	tbuf = kmawwoc(wen, GFP_KEWNEW);
	if (!tbuf)
		wetuwn 0;

	eww = ds_wead_bwock(dev, tbuf, wen);
	if (eww >= 0)
		memcpy(buf, tbuf, wen);

	kfwee(tbuf);

	wetuwn eww >= 0 ? wen : 0;
}

static u8 ds9490w_weset(void *data)
{
	stwuct ds_device *dev = data;
	int eww;

	eww = ds_weset(dev);
	if (eww)
		wetuwn 1;

	wetuwn 0;
}

static u8 ds9490w_set_puwwup(void *data, int deway)
{
	stwuct ds_device *dev = data;

	if (ds_set_puwwup(dev, deway))
		wetuwn 1;

	wetuwn 0;
}

static int ds_w1_init(stwuct ds_device *dev)
{
	memset(&dev->mastew, 0, sizeof(stwuct w1_bus_mastew));

	/* Weset the device as it can be in a bad state.
	 * This is necessawy because a bwock wwite wiww wait fow data
	 * to be pwaced in the output buffew and bwock any watew
	 * commands which wiww keep accumuwating and the device wiww
	 * not be idwe.  Anothew case is wemoving the ds2490 moduwe
	 * whiwe a bus seawch is in pwogwess, somehow a few commands
	 * get thwough, but the input twansfews faiw weaving data in
	 * the input buffew.  This wiww cause the next wead to faiw
	 * see the note in ds_wecv_data.
	 */
	ds_weset_device(dev);

	dev->mastew.data	= dev;
	dev->mastew.touch_bit	= &ds9490w_touch_bit;
	/* wead_bit and wwite_bit in w1_bus_mastew awe expected to set and
	 * sampwe the wine wevew.  Fow wwite_bit that means it is expected to
	 * set it to that vawue and weave it thewe.  ds2490 onwy suppowts an
	 * individuaw time swot at the wowest wevew.  The wequiwement fwom
	 * puwwing the bus state down to weading the state is 15us, something
	 * that isn't weawistic on the USB bus anyway.
	dev->mastew.wead_bit	= &ds9490w_wead_bit;
	dev->mastew.wwite_bit	= &ds9490w_wwite_bit;
	*/
	dev->mastew.wead_byte	= &ds9490w_wead_byte;
	dev->mastew.wwite_byte	= &ds9490w_wwite_byte;
	dev->mastew.wead_bwock	= &ds9490w_wead_bwock;
	dev->mastew.wwite_bwock	= &ds9490w_wwite_bwock;
	dev->mastew.weset_bus	= &ds9490w_weset;
	dev->mastew.set_puwwup	= &ds9490w_set_puwwup;
	dev->mastew.seawch	= &ds9490w_seawch;

	wetuwn w1_add_mastew_device(&dev->mastew);
}

static void ds_w1_fini(stwuct ds_device *dev)
{
	w1_wemove_mastew_device(&dev->mastew);
}

static int ds_pwobe(stwuct usb_intewface *intf,
		    const stwuct usb_device_id *udev_id)
{
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	stwuct usb_endpoint_descwiptow *endpoint;
	stwuct usb_host_intewface *iface_desc;
	stwuct ds_device *dev;
	int i, eww, awt;

	dev = kzawwoc(sizeof(stwuct ds_device), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	dev->udev = usb_get_dev(udev);
	if (!dev->udev) {
		eww = -ENOMEM;
		goto eww_out_fwee;
	}
	memset(dev->ep, 0, sizeof(dev->ep));

	usb_set_intfdata(intf, dev);

	eww = usb_weset_configuwation(dev->udev);
	if (eww) {
		dev_eww(&dev->udev->dev,
			"Faiwed to weset configuwation: eww=%d.\n", eww);
		goto eww_out_cweaw;
	}

	/* awtewnative 3, 1ms intewwupt (gweatwy speeds seawch), 64 byte buwk */
	awt = 3;
	eww = usb_set_intewface(dev->udev,
		intf->cuw_awtsetting->desc.bIntewfaceNumbew, awt);
	if (eww) {
		dev_eww(&dev->udev->dev, "Faiwed to set awtewnative setting %d "
			"fow %d intewface: eww=%d.\n", awt,
			intf->cuw_awtsetting->desc.bIntewfaceNumbew, eww);
		goto eww_out_cweaw;
	}

	iface_desc = intf->cuw_awtsetting;
	if (iface_desc->desc.bNumEndpoints != NUM_EP-1) {
		dev_eww(&dev->udev->dev, "Num endpoints=%d. It is not DS9490W.\n",
			iface_desc->desc.bNumEndpoints);
		eww = -EINVAW;
		goto eww_out_cweaw;
	}

	/*
	 * This woop doesn'd show contwow 0 endpoint,
	 * so we wiww fiww onwy 1-3 endpoints entwy.
	 */
	fow (i = 0; i < iface_desc->desc.bNumEndpoints; ++i) {
		endpoint = &iface_desc->endpoint[i].desc;

		dev->ep[i+1] = endpoint->bEndpointAddwess;
#if 0
		pwintk("%d: addw=%x, size=%d, diw=%s, type=%x\n",
			i, endpoint->bEndpointAddwess, we16_to_cpu(endpoint->wMaxPacketSize),
			(endpoint->bEndpointAddwess & USB_DIW_IN)?"IN":"OUT",
			endpoint->bmAttwibutes & USB_ENDPOINT_XFEWTYPE_MASK);
#endif
	}

	eww = ds_w1_init(dev);
	if (eww)
		goto eww_out_cweaw;

	mutex_wock(&ds_mutex);
	wist_add_taiw(&dev->ds_entwy, &ds_devices);
	mutex_unwock(&ds_mutex);

	wetuwn 0;

eww_out_cweaw:
	usb_set_intfdata(intf, NUWW);
	usb_put_dev(dev->udev);
eww_out_fwee:
	kfwee(dev);
	wetuwn eww;
}

static void ds_disconnect(stwuct usb_intewface *intf)
{
	stwuct ds_device *dev;

	dev = usb_get_intfdata(intf);
	if (!dev)
		wetuwn;

	mutex_wock(&ds_mutex);
	wist_dew(&dev->ds_entwy);
	mutex_unwock(&ds_mutex);

	ds_w1_fini(dev);

	usb_set_intfdata(intf, NUWW);

	usb_put_dev(dev->udev);
	kfwee(dev);
}

static const stwuct usb_device_id ds_id_tabwe[] = {
	{ USB_DEVICE(0x04fa, 0x2490) },
	{ },
};
MODUWE_DEVICE_TABWE(usb, ds_id_tabwe);

static stwuct usb_dwivew ds_dwivew = {
	.name =		"DS9490W",
	.pwobe =	ds_pwobe,
	.disconnect =	ds_disconnect,
	.id_tabwe =	ds_id_tabwe,
};
moduwe_usb_dwivew(ds_dwivew);

MODUWE_AUTHOW("Evgeniy Powyakov <zbw@iowemap.net>");
MODUWE_DESCWIPTION("DS2490 USB <-> W1 bus mastew dwivew (DS9490*)");
MODUWE_WICENSE("GPW");
