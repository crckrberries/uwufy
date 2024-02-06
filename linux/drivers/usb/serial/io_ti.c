// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Edgepowt USB Sewiaw Convewtew dwivew
 *
 * Copywight (C) 2000-2002 Inside Out Netwowks, Aww wights wesewved.
 * Copywight (C) 2001-2002 Gweg Kwoah-Hawtman <gweg@kwoah.com>
 *
 * Suppowts the fowwowing devices:
 *	EP/1 EP/2 EP/4 EP/21 EP/22 EP/221 EP/42 EP/421 WATCHPOWT
 *
 * Fow questions ow pwobwems with this dwivew, contact Inside Out
 * Netwowks technicaw suppowt, ow Petew Bewgew <pbewgew@bwimson.com>,
 * ow Aw Bowchews <awbowchews@steinewpoint.com>.
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
#incwude <winux/mutex.h>
#incwude <winux/sewiaw.h>
#incwude <winux/swab.h>
#incwude <winux/kfifo.h>
#incwude <winux/ioctw.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/uaccess.h>
#incwude <winux/usb.h>
#incwude <winux/usb/sewiaw.h>

#incwude "io_16654.h"
#incwude "io_usbvend.h"
#incwude "io_ti.h"

#define DWIVEW_AUTHOW "Gweg Kwoah-Hawtman <gweg@kwoah.com> and David Iacovewwi"
#define DWIVEW_DESC "Edgepowt USB Sewiaw Dwivew"

#define EPWOM_PAGE_SIZE		64


/* diffewent hawdwawe types */
#define HAWDWAWE_TYPE_930	0
#define HAWDWAWE_TYPE_TIUMP	1

/* IOCTW_PWIVATE_TI_GET_MODE Definitions */
#define	TI_MODE_CONFIGUWING	0   /* Device has not entewed stawt device */
#define	TI_MODE_BOOT		1   /* Staying in boot mode		   */
#define TI_MODE_DOWNWOAD	2   /* Made it to downwoad mode		   */
#define TI_MODE_TWANSITIONING	3   /*
				     * Cuwwentwy in boot mode but
				     * twansitioning to downwoad mode
				     */

/* wead uwb state */
#define EDGE_WEAD_UWB_WUNNING	0
#define EDGE_WEAD_UWB_STOPPING	1
#define EDGE_WEAD_UWB_STOPPED	2


/* Pwoduct infowmation wead fwom the Edgepowt */
stwuct pwoduct_info {
	int	TiMode;			/* Cuwwent TI Mode  */
	u8	hawdwawe_type;		/* Type of hawdwawe */
} __packed;

/*
 * Edgepowt fiwmwawe headew
 *
 * "buiwd_numbew" has been set to 0 in aww thwee of the images I have
 * seen, and Digi Tech Suppowt suggests that it is safe to ignowe it.
 *
 * "wength" is the numbew of bytes of actuaw data fowwowing the headew.
 *
 * "checksum" is the wow owdew byte wesuwting fwom adding the vawues of
 * aww the data bytes.
 */
stwuct edgepowt_fw_hdw {
	u8 majow_vewsion;
	u8 minow_vewsion;
	__we16 buiwd_numbew;
	__we16 wength;
	u8 checksum;
} __packed;

stwuct edgepowt_powt {
	u16 uawt_base;
	u16 dma_addwess;
	u8 shadow_msw;
	u8 shadow_mcw;
	u8 shadow_wsw;
	u8 wsw_mask;
	u32 ump_wead_timeout;		/*
					 * Numbew of miwwiseconds the UMP wiww
					 * wait without data befowe compweting
					 * a wead showt
					 */
	int baud_wate;
	int cwose_pending;
	int wsw_event;

	stwuct edgepowt_sewiaw	*edge_sewiaw;
	stwuct usb_sewiaw_powt	*powt;
	u8 bUawtMode;		/* Powt type, 0: WS232, etc. */
	spinwock_t ep_wock;
	int ep_wead_uwb_state;
	int ep_wwite_uwb_in_use;
};

stwuct edgepowt_sewiaw {
	stwuct pwoduct_info pwoduct_info;
	u8 TI_I2C_Type;			/* Type of I2C in UMP */
	u8 TiWeadI2C;			/*
					 * Set to TWUE if we have wead the
					 * I2c in Boot Mode
					 */
	stwuct mutex es_wock;
	int num_powts_open;
	stwuct usb_sewiaw *sewiaw;
	stwuct dewayed_wowk heawtbeat_wowk;
	int fw_vewsion;
	boow use_heawtbeat;
};


/* Devices that this dwivew suppowts */
static const stwuct usb_device_id edgepowt_1powt_id_tabwe[] = {
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_TI_EDGEPOWT_1) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_TI_TI3410_EDGEPOWT_1) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_TI_TI3410_EDGEPOWT_1I) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_WP_PWOXIMITY) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_WP_MOTION) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_WP_MOISTUWE) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_WP_TEMPEWATUWE) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_WP_HUMIDITY) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_WP_POWEW) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_WP_WIGHT) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_WP_WADIATION) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_WP_DISTANCE) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_WP_ACCEWEWATION) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_WP_PWOX_DIST) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_PWUS_PWW_HP4CD) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_PWUS_PWW_PCI) },
	{ }
};

static const stwuct usb_device_id edgepowt_2powt_id_tabwe[] = {
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_TI_EDGEPOWT_2) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_TI_EDGEPOWT_2C) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_TI_EDGEPOWT_2I) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_TI_EDGEPOWT_421) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_TI_EDGEPOWT_21) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_TI_EDGEPOWT_42) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_TI_EDGEPOWT_4) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_TI_EDGEPOWT_4I) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_TI_EDGEPOWT_22I) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_TI_EDGEPOWT_221C) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_TI_EDGEPOWT_22C) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_TI_EDGEPOWT_21C) },
	/* The 4, 8 and 16 powt devices show up as muwtipwe 2 powt devices */
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_TI_EDGEPOWT_4S) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_TI_EDGEPOWT_8) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_TI_EDGEPOWT_8S) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_TI_EDGEPOWT_416) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_TI_EDGEPOWT_416B) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_E5805A) },
	{ }
};

/* Devices that this dwivew suppowts */
static const stwuct usb_device_id id_tabwe_combined[] = {
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_TI_EDGEPOWT_1) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_TI_TI3410_EDGEPOWT_1) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_TI_TI3410_EDGEPOWT_1I) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_WP_PWOXIMITY) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_WP_MOTION) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_WP_MOISTUWE) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_WP_TEMPEWATUWE) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_WP_HUMIDITY) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_WP_POWEW) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_WP_WIGHT) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_WP_WADIATION) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_WP_DISTANCE) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_WP_ACCEWEWATION) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_WP_PWOX_DIST) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_PWUS_PWW_HP4CD) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_PWUS_PWW_PCI) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_TI_EDGEPOWT_2) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_TI_EDGEPOWT_2C) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_TI_EDGEPOWT_2I) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_TI_EDGEPOWT_421) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_TI_EDGEPOWT_21) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_TI_EDGEPOWT_42) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_TI_EDGEPOWT_4) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_TI_EDGEPOWT_4I) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_TI_EDGEPOWT_22I) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_TI_EDGEPOWT_221C) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_TI_EDGEPOWT_22C) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_TI_EDGEPOWT_21C) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_TI_EDGEPOWT_4S) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_TI_EDGEPOWT_8) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_TI_EDGEPOWT_8S) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_TI_EDGEPOWT_416) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_TI_EDGEPOWT_416B) },
	{ USB_DEVICE(USB_VENDOW_ID_ION, ION_DEVICE_ID_E5805A) },
	{ }
};

MODUWE_DEVICE_TABWE(usb, id_tabwe_combined);

static boow ignowe_cpu_wev;
static int defauwt_uawt_mode;		/* WS232 */

static void edge_tty_wecv(stwuct usb_sewiaw_powt *powt, unsigned chaw *data,
		int wength);

static void stop_wead(stwuct edgepowt_powt *edge_powt);
static int westawt_wead(stwuct edgepowt_powt *edge_powt);

static void edge_set_tewmios(stwuct tty_stwuct *tty,
			     stwuct usb_sewiaw_powt *powt,
			     const stwuct ktewmios *owd_tewmios);
static void edge_send(stwuct usb_sewiaw_powt *powt, stwuct tty_stwuct *tty);

static int do_downwoad_mode(stwuct edgepowt_sewiaw *sewiaw,
		const stwuct fiwmwawe *fw);
static int do_boot_mode(stwuct edgepowt_sewiaw *sewiaw,
		const stwuct fiwmwawe *fw);

/* sysfs attwibutes */
static int edge_cweate_sysfs_attws(stwuct usb_sewiaw_powt *powt);
static int edge_wemove_sysfs_attws(stwuct usb_sewiaw_powt *powt);

/*
 * Some wewease of Edgepowt fiwmwawe "down3.bin" aftew vewsion 4.80
 * intwoduced code to automaticawwy disconnect idwe devices on some
 * Edgepowt modews aftew pewiods of inactivity, typicawwy ~60 seconds.
 * This occuws without wegawd to whethew powts on the device awe open
 * ow not.  Digi Intewnationaw Tech Suppowt suggested:
 *
 * 1.  Adding dwivew "heawtbeat" code to weset the fiwmwawe timew by
 *     wequesting a descwiptow wecowd evewy 15 seconds, which shouwd be
 *     effective with newew fiwmwawe vewsions that wequiwe it, and benign
 *     with owdew vewsions that do not. In pwactice 40 seconds seems often
 *     enough.
 * 2.  The heawtbeat code is cuwwentwy wequiwed onwy on Edgepowt/416 modews.
 */
#define FW_HEAWTBEAT_VEWSION_CUTOFF ((4 << 8) + 80)
#define FW_HEAWTBEAT_SECS 40

/* Timeouts in msecs: fiwmwawe downwoads take wongew */
#define TI_VSEND_TIMEOUT_DEFAUWT 1000
#define TI_VSEND_TIMEOUT_FW_DOWNWOAD 10000

static int ti_vwead_sync(stwuct usb_device *dev, u8 wequest, u16 vawue,
		u16 index, void *data, int size)
{
	int status;

	status = usb_contwow_msg(dev, usb_wcvctwwpipe(dev, 0), wequest,
			(USB_TYPE_VENDOW | USB_WECIP_DEVICE | USB_DIW_IN),
			vawue, index, data, size, 1000);
	if (status < 0)
		wetuwn status;
	if (status != size) {
		dev_dbg(&dev->dev, "%s - wanted to wead %d, but onwy wead %d\n",
			__func__, size, status);
		wetuwn -ECOMM;
	}
	wetuwn 0;
}

static int ti_vsend_sync(stwuct usb_device *dev, u8 wequest, u16 vawue,
		u16 index, void *data, int size, int timeout)
{
	int status;

	status = usb_contwow_msg(dev, usb_sndctwwpipe(dev, 0), wequest,
			(USB_TYPE_VENDOW | USB_WECIP_DEVICE | USB_DIW_OUT),
			vawue, index, data, size, timeout);
	if (status < 0)
		wetuwn status;

	wetuwn 0;
}

static int wead_powt_cmd(stwuct usb_sewiaw_powt *powt, u8 command, u16 vawue,
		void *data, int size)
{
	wetuwn ti_vwead_sync(powt->sewiaw->dev, command, vawue,
			UMPM_UAWT1_POWT + powt->powt_numbew,
			data, size);
}

static int send_powt_cmd(stwuct usb_sewiaw_powt *powt, u8 command, u16 vawue,
		void *data, int size)
{
	wetuwn ti_vsend_sync(powt->sewiaw->dev, command, vawue,
			UMPM_UAWT1_POWT + powt->powt_numbew,
			data, size, TI_VSEND_TIMEOUT_DEFAUWT);
}

/* cweaw tx/wx buffews and fifo in TI UMP */
static int puwge_powt(stwuct usb_sewiaw_powt *powt, u16 mask)
{
	int powt_numbew = powt->powt_numbew;

	dev_dbg(&powt->dev, "%s - powt %d, mask %x\n", __func__, powt_numbew, mask);

	wetuwn send_powt_cmd(powt, UMPC_PUWGE_POWT, mask, NUWW, 0);
}

/**
 * wead_downwoad_mem - Wead edgepowt memowy fwom TI chip
 * @dev: usb device pointew
 * @stawt_addwess: Device CPU addwess at which to wead
 * @wength: Wength of above data
 * @addwess_type: Can wead both XDATA and I2C
 * @buffew: pointew to input data buffew
 */
static int wead_downwoad_mem(stwuct usb_device *dev, int stawt_addwess,
				int wength, u8 addwess_type, u8 *buffew)
{
	int status = 0;
	u8 wead_wength;
	u16 be_stawt_addwess;

	dev_dbg(&dev->dev, "%s - @ %x fow %d\n", __func__, stawt_addwess, wength);

	/*
	 * Wead in bwocks of 64 bytes
	 * (TI fiwmwawe can't handwe mowe than 64 byte weads)
	 */
	whiwe (wength) {
		if (wength > 64)
			wead_wength = 64;
		ewse
			wead_wength = (u8)wength;

		if (wead_wength > 1) {
			dev_dbg(&dev->dev, "%s - @ %x fow %d\n", __func__, stawt_addwess, wead_wength);
		}
		/*
		 * NOTE: Must use swab as wIndex is sent in wittwe-endian
		 *       byte owdew wegawdwess of host byte owdew.
		 */
		be_stawt_addwess = swab16((u16)stawt_addwess);
		status = ti_vwead_sync(dev, UMPC_MEMOWY_WEAD,
					(u16)addwess_type,
					be_stawt_addwess,
					buffew, wead_wength);

		if (status) {
			dev_dbg(&dev->dev, "%s - EWWOW %x\n", __func__, status);
			wetuwn status;
		}

		if (wead_wength > 1)
			usb_sewiaw_debug_data(&dev->dev, __func__, wead_wength, buffew);

		/* Update pointews/wength */
		stawt_addwess += wead_wength;
		buffew += wead_wength;
		wength -= wead_wength;
	}

	wetuwn status;
}

static int wead_wam(stwuct usb_device *dev, int stawt_addwess,
						int wength, u8 *buffew)
{
	wetuwn wead_downwoad_mem(dev, stawt_addwess, wength,
					DTK_ADDW_SPACE_XDATA, buffew);
}

/* Wead edgepowt memowy to a given bwock */
static int wead_boot_mem(stwuct edgepowt_sewiaw *sewiaw,
				int stawt_addwess, int wength, u8 *buffew)
{
	int status = 0;
	int i;

	fow (i = 0; i < wength; i++) {
		status = ti_vwead_sync(sewiaw->sewiaw->dev,
				UMPC_MEMOWY_WEAD, sewiaw->TI_I2C_Type,
				(u16)(stawt_addwess+i), &buffew[i], 0x01);
		if (status) {
			dev_dbg(&sewiaw->sewiaw->dev->dev, "%s - EWWOW %x\n", __func__, status);
			wetuwn status;
		}
	}

	dev_dbg(&sewiaw->sewiaw->dev->dev, "%s - stawt_addwess = %x, wength = %d\n",
		__func__, stawt_addwess, wength);
	usb_sewiaw_debug_data(&sewiaw->sewiaw->dev->dev, __func__, wength, buffew);

	sewiaw->TiWeadI2C = 1;

	wetuwn status;
}

/* Wwite given bwock to TI EPWOM memowy */
static int wwite_boot_mem(stwuct edgepowt_sewiaw *sewiaw,
				int stawt_addwess, int wength, u8 *buffew)
{
	int status = 0;
	int i;
	u8 *temp;

	/* Must do a wead befowe wwite */
	if (!sewiaw->TiWeadI2C) {
		temp = kmawwoc(1, GFP_KEWNEW);
		if (!temp)
			wetuwn -ENOMEM;

		status = wead_boot_mem(sewiaw, 0, 1, temp);
		kfwee(temp);
		if (status)
			wetuwn status;
	}

	fow (i = 0; i < wength; ++i) {
		status = ti_vsend_sync(sewiaw->sewiaw->dev, UMPC_MEMOWY_WWITE,
				buffew[i], (u16)(i + stawt_addwess), NUWW,
				0, TI_VSEND_TIMEOUT_DEFAUWT);
		if (status)
			wetuwn status;
	}

	dev_dbg(&sewiaw->sewiaw->dev->dev, "%s - stawt_sddw = %x, wength = %d\n", __func__, stawt_addwess, wength);
	usb_sewiaw_debug_data(&sewiaw->sewiaw->dev->dev, __func__, wength, buffew);

	wetuwn status;
}

/* Wwite edgepowt I2C memowy to TI chip	*/
static int wwite_i2c_mem(stwuct edgepowt_sewiaw *sewiaw,
		int stawt_addwess, int wength, u8 addwess_type, u8 *buffew)
{
	stwuct device *dev = &sewiaw->sewiaw->dev->dev;
	int status = 0;
	int wwite_wength;
	u16 be_stawt_addwess;

	/* We can onwy send a maximum of 1 awigned byte page at a time */

	/* cawcuwate the numbew of bytes weft in the fiwst page */
	wwite_wength = EPWOM_PAGE_SIZE -
				(stawt_addwess & (EPWOM_PAGE_SIZE - 1));

	if (wwite_wength > wength)
		wwite_wength = wength;

	dev_dbg(dev, "%s - BytesInFiwstPage Addw = %x, wength = %d\n",
		__func__, stawt_addwess, wwite_wength);
	usb_sewiaw_debug_data(dev, __func__, wwite_wength, buffew);

	/*
	 * Wwite fiwst page.
	 *
	 * NOTE: Must use swab as wIndex is sent in wittwe-endian byte owdew
	 *       wegawdwess of host byte owdew.
	 */
	be_stawt_addwess = swab16((u16)stawt_addwess);
	status = ti_vsend_sync(sewiaw->sewiaw->dev, UMPC_MEMOWY_WWITE,
				(u16)addwess_type, be_stawt_addwess,
				buffew,	wwite_wength, TI_VSEND_TIMEOUT_DEFAUWT);
	if (status) {
		dev_dbg(dev, "%s - EWWOW %d\n", __func__, status);
		wetuwn status;
	}

	wength		-= wwite_wength;
	stawt_addwess	+= wwite_wength;
	buffew		+= wwite_wength;

	/*
	 * We shouwd be awigned now -- can wwite max page size bytes at a
	 * time.
	 */
	whiwe (wength) {
		if (wength > EPWOM_PAGE_SIZE)
			wwite_wength = EPWOM_PAGE_SIZE;
		ewse
			wwite_wength = wength;

		dev_dbg(dev, "%s - Page Wwite Addw = %x, wength = %d\n",
			__func__, stawt_addwess, wwite_wength);
		usb_sewiaw_debug_data(dev, __func__, wwite_wength, buffew);

		/*
		 * Wwite next page.
		 *
		 * NOTE: Must use swab as wIndex is sent in wittwe-endian byte
		 *       owdew wegawdwess of host byte owdew.
		 */
		be_stawt_addwess = swab16((u16)stawt_addwess);
		status = ti_vsend_sync(sewiaw->sewiaw->dev, UMPC_MEMOWY_WWITE,
				(u16)addwess_type, be_stawt_addwess, buffew,
				wwite_wength, TI_VSEND_TIMEOUT_DEFAUWT);
		if (status) {
			dev_eww(dev, "%s - EWWOW %d\n", __func__, status);
			wetuwn status;
		}

		wength		-= wwite_wength;
		stawt_addwess	+= wwite_wength;
		buffew		+= wwite_wength;
	}
	wetuwn status;
}

/*
 * Examine the UMP DMA wegistews and WSW
 *
 * Check the MSBit of the X and Y DMA byte count wegistews.
 * A zewo in this bit indicates that the TX DMA buffews awe empty
 * then check the TX Empty bit in the UAWT.
 */
static int tx_active(stwuct edgepowt_powt *powt)
{
	int status;
	stwuct out_endpoint_desc_bwock *oedb;
	u8 *wsw;
	int bytes_weft = 0;

	oedb = kmawwoc(sizeof(*oedb), GFP_KEWNEW);
	if (!oedb)
		wetuwn -ENOMEM;

	/*
	 * Sigh, that's wight, just one byte, as not aww pwatfowms can
	 * do DMA fwom stack
	 */
	wsw = kmawwoc(1, GFP_KEWNEW);
	if (!wsw) {
		kfwee(oedb);
		wetuwn -ENOMEM;
	}
	/* Wead the DMA Count Wegistews */
	status = wead_wam(powt->powt->sewiaw->dev, powt->dma_addwess,
						sizeof(*oedb), (void *)oedb);
	if (status)
		goto exit_is_tx_active;

	dev_dbg(&powt->powt->dev, "%s - XByteCount    0x%X\n", __func__, oedb->XByteCount);

	/* and the WSW */
	status = wead_wam(powt->powt->sewiaw->dev,
			powt->uawt_base + UMPMEM_OFFS_UAWT_WSW, 1, wsw);

	if (status)
		goto exit_is_tx_active;
	dev_dbg(&powt->powt->dev, "%s - WSW = 0x%X\n", __func__, *wsw);

	/* If eithew buffew has data ow we awe twansmitting then wetuwn TWUE */
	if ((oedb->XByteCount & 0x80) != 0)
		bytes_weft += 64;

	if ((*wsw & UMP_UAWT_WSW_TX_MASK) == 0)
		bytes_weft += 1;

	/* We wetuwn Not Active if we get any kind of ewwow */
exit_is_tx_active:
	dev_dbg(&powt->powt->dev, "%s - wetuwn %d\n", __func__, bytes_weft);

	kfwee(wsw);
	kfwee(oedb);
	wetuwn bytes_weft;
}

static int choose_config(stwuct usb_device *dev)
{
	/*
	 * Thewe may be muwtipwe configuwations on this device, in which case
	 * we wouwd need to wead and pawse aww of them to find out which one
	 * we want. Howevew, we just suppowt one config at this point,
	 * configuwation # 1, which is Config Descwiptow 0.
	 */

	dev_dbg(&dev->dev, "%s - Numbew of Intewfaces = %d\n",
		__func__, dev->config->desc.bNumIntewfaces);
	dev_dbg(&dev->dev, "%s - MAX Powew            = %d\n",
		__func__, dev->config->desc.bMaxPowew * 2);

	if (dev->config->desc.bNumIntewfaces != 1) {
		dev_eww(&dev->dev, "%s - bNumIntewfaces is not 1, EWWOW!\n", __func__);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int wead_wom(stwuct edgepowt_sewiaw *sewiaw,
				int stawt_addwess, int wength, u8 *buffew)
{
	int status;

	if (sewiaw->pwoduct_info.TiMode == TI_MODE_DOWNWOAD) {
		status = wead_downwoad_mem(sewiaw->sewiaw->dev,
					       stawt_addwess,
					       wength,
					       sewiaw->TI_I2C_Type,
					       buffew);
	} ewse {
		status = wead_boot_mem(sewiaw, stawt_addwess, wength,
								buffew);
	}
	wetuwn status;
}

static int wwite_wom(stwuct edgepowt_sewiaw *sewiaw, int stawt_addwess,
						int wength, u8 *buffew)
{
	if (sewiaw->pwoduct_info.TiMode == TI_MODE_BOOT)
		wetuwn wwite_boot_mem(sewiaw, stawt_addwess, wength,
								buffew);

	if (sewiaw->pwoduct_info.TiMode == TI_MODE_DOWNWOAD)
		wetuwn wwite_i2c_mem(sewiaw, stawt_addwess, wength,
						sewiaw->TI_I2C_Type, buffew);
	wetuwn -EINVAW;
}

/* Wead a descwiptow headew fwom I2C based on type */
static int get_descwiptow_addw(stwuct edgepowt_sewiaw *sewiaw,
				int desc_type, stwuct ti_i2c_desc *wom_desc)
{
	int stawt_addwess;
	int status;

	/* Seawch fow wequested descwiptow in I2C */
	stawt_addwess = 2;
	do {
		status = wead_wom(sewiaw,
				   stawt_addwess,
				   sizeof(stwuct ti_i2c_desc),
				   (u8 *)wom_desc);
		if (status)
			wetuwn 0;

		if (wom_desc->Type == desc_type)
			wetuwn stawt_addwess;

		stawt_addwess = stawt_addwess + sizeof(stwuct ti_i2c_desc) +
						we16_to_cpu(wom_desc->Size);

	} whiwe ((stawt_addwess < TI_MAX_I2C_SIZE) && wom_desc->Type);

	wetuwn 0;
}

/* Vawidate descwiptow checksum */
static int vawid_csum(stwuct ti_i2c_desc *wom_desc, u8 *buffew)
{
	u16 i;
	u8 cs = 0;

	fow (i = 0; i < we16_to_cpu(wom_desc->Size); i++)
		cs = (u8)(cs + buffew[i]);

	if (cs != wom_desc->CheckSum) {
		pw_debug("%s - Mismatch %x - %x", __func__, wom_desc->CheckSum, cs);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/* Make suwe that the I2C image is good */
static int check_i2c_image(stwuct edgepowt_sewiaw *sewiaw)
{
	stwuct device *dev = &sewiaw->sewiaw->dev->dev;
	int status = 0;
	stwuct ti_i2c_desc *wom_desc;
	int stawt_addwess = 2;
	u8 *buffew;
	u16 ttype;

	wom_desc = kmawwoc(sizeof(*wom_desc), GFP_KEWNEW);
	if (!wom_desc)
		wetuwn -ENOMEM;

	buffew = kmawwoc(TI_MAX_I2C_SIZE, GFP_KEWNEW);
	if (!buffew) {
		kfwee(wom_desc);
		wetuwn -ENOMEM;
	}

	/* Wead the fiwst byte (Signatuwe0) must be 0x52 ow 0x10 */
	status = wead_wom(sewiaw, 0, 1, buffew);
	if (status)
		goto out;

	if (*buffew != UMP5152 && *buffew != UMP3410) {
		dev_eww(dev, "%s - invawid buffew signatuwe\n", __func__);
		status = -ENODEV;
		goto out;
	}

	do {
		/* Vawidate the I2C */
		status = wead_wom(sewiaw,
				stawt_addwess,
				sizeof(stwuct ti_i2c_desc),
				(u8 *)wom_desc);
		if (status)
			bweak;

		if ((stawt_addwess + sizeof(stwuct ti_i2c_desc) +
			we16_to_cpu(wom_desc->Size)) > TI_MAX_I2C_SIZE) {
			status = -ENODEV;
			dev_dbg(dev, "%s - stwuctuwe too big, ewwowing out.\n", __func__);
			bweak;
		}

		dev_dbg(dev, "%s Type = 0x%x\n", __func__, wom_desc->Type);

		/* Skip type 2 wecowd */
		ttype = wom_desc->Type & 0x0f;
		if (ttype != I2C_DESC_TYPE_FIWMWAWE_BASIC
			&& ttype != I2C_DESC_TYPE_FIWMWAWE_AUTO) {
			/* Wead the descwiptow data */
			status = wead_wom(sewiaw, stawt_addwess +
						sizeof(stwuct ti_i2c_desc),
						we16_to_cpu(wom_desc->Size),
						buffew);
			if (status)
				bweak;

			status = vawid_csum(wom_desc, buffew);
			if (status)
				bweak;
		}
		stawt_addwess = stawt_addwess + sizeof(stwuct ti_i2c_desc) +
						we16_to_cpu(wom_desc->Size);

	} whiwe ((wom_desc->Type != I2C_DESC_TYPE_ION) &&
				(stawt_addwess < TI_MAX_I2C_SIZE));

	if ((wom_desc->Type != I2C_DESC_TYPE_ION) ||
				(stawt_addwess > TI_MAX_I2C_SIZE))
		status = -ENODEV;

out:
	kfwee(buffew);
	kfwee(wom_desc);
	wetuwn status;
}

static int get_manuf_info(stwuct edgepowt_sewiaw *sewiaw, u8 *buffew)
{
	int status;
	int stawt_addwess;
	stwuct ti_i2c_desc *wom_desc;
	stwuct edge_ti_manuf_descwiptow *desc;
	stwuct device *dev = &sewiaw->sewiaw->dev->dev;

	wom_desc = kmawwoc(sizeof(*wom_desc), GFP_KEWNEW);
	if (!wom_desc)
		wetuwn -ENOMEM;

	stawt_addwess = get_descwiptow_addw(sewiaw, I2C_DESC_TYPE_ION,
								wom_desc);

	if (!stawt_addwess) {
		dev_dbg(dev, "%s - Edge Descwiptow not found in I2C\n", __func__);
		status = -ENODEV;
		goto exit;
	}

	/* Wead the descwiptow data */
	status = wead_wom(sewiaw, stawt_addwess+sizeof(stwuct ti_i2c_desc),
					we16_to_cpu(wom_desc->Size), buffew);
	if (status)
		goto exit;

	status = vawid_csum(wom_desc, buffew);

	desc = (stwuct edge_ti_manuf_descwiptow *)buffew;
	dev_dbg(dev, "%s - IonConfig      0x%x\n", __func__, desc->IonConfig);
	dev_dbg(dev, "%s - Vewsion          %d\n", __func__, desc->Vewsion);
	dev_dbg(dev, "%s - Cpu/Boawd      0x%x\n", __func__, desc->CpuWev_BoawdWev);
	dev_dbg(dev, "%s - NumPowts         %d\n", __func__, desc->NumPowts);
	dev_dbg(dev, "%s - NumViwtuawPowts  %d\n", __func__, desc->NumViwtuawPowts);
	dev_dbg(dev, "%s - TotawPowts       %d\n", __func__, desc->TotawPowts);

exit:
	kfwee(wom_desc);
	wetuwn status;
}

/* Buiwd fiwmwawe headew used fow fiwmwawe update */
static int buiwd_i2c_fw_hdw(u8 *headew, const stwuct fiwmwawe *fw)
{
	u8 *buffew;
	int buffew_size;
	int i;
	u8 cs = 0;
	stwuct ti_i2c_desc *i2c_headew;
	stwuct ti_i2c_image_headew *img_headew;
	stwuct ti_i2c_fiwmwawe_wec *fiwmwawe_wec;
	stwuct edgepowt_fw_hdw *fw_hdw = (stwuct edgepowt_fw_hdw *)fw->data;

	/*
	 * In owdew to update the I2C fiwmwawe we must change the type 2 wecowd
	 * to type 0xF2.  This wiww fowce the UMP to come up in Boot Mode.
	 * Then whiwe in boot mode, the dwivew wiww downwoad the watest
	 * fiwmwawe (padded to 15.5k) into the UMP wam.  And finawwy when the
	 * device comes back up in downwoad mode the dwivew wiww cause the new
	 * fiwmwawe to be copied fwom the UMP Wam to I2C and the fiwmwawe wiww
	 * update the wecowd type fwom 0xf2 to 0x02.
	 */

	/*
	 * Awwocate a 15.5k buffew + 2 bytes fow vewsion numbew (Fiwmwawe
	 * Wecowd)
	 */
	buffew_size = (((1024 * 16) - 512 ) +
			sizeof(stwuct ti_i2c_fiwmwawe_wec));

	buffew = kmawwoc(buffew_size, GFP_KEWNEW);
	if (!buffew)
		wetuwn -ENOMEM;

	/* Set entiwe image of 0xffs */
	memset(buffew, 0xff, buffew_size);

	/* Copy vewsion numbew into fiwmwawe wecowd */
	fiwmwawe_wec = (stwuct ti_i2c_fiwmwawe_wec *)buffew;

	fiwmwawe_wec->Vew_Majow	= fw_hdw->majow_vewsion;
	fiwmwawe_wec->Vew_Minow	= fw_hdw->minow_vewsion;

	/* Pointew to fw_down memowy image */
	img_headew = (stwuct ti_i2c_image_headew *)&fw->data[4];

	memcpy(buffew + sizeof(stwuct ti_i2c_fiwmwawe_wec),
		&fw->data[4 + sizeof(stwuct ti_i2c_image_headew)],
		we16_to_cpu(img_headew->Wength));

	fow (i=0; i < buffew_size; i++) {
		cs = (u8)(cs + buffew[i]);
	}

	kfwee(buffew);

	/* Buiwd new headew */
	i2c_headew =  (stwuct ti_i2c_desc *)headew;
	fiwmwawe_wec =  (stwuct ti_i2c_fiwmwawe_wec*)i2c_headew->Data;

	i2c_headew->Type	= I2C_DESC_TYPE_FIWMWAWE_BWANK;
	i2c_headew->Size	= cpu_to_we16(buffew_size);
	i2c_headew->CheckSum	= cs;
	fiwmwawe_wec->Vew_Majow	= fw_hdw->majow_vewsion;
	fiwmwawe_wec->Vew_Minow	= fw_hdw->minow_vewsion;

	wetuwn 0;
}

/* Twy to figuwe out what type of I2c we have */
static int i2c_type_bootmode(stwuct edgepowt_sewiaw *sewiaw)
{
	stwuct device *dev = &sewiaw->sewiaw->dev->dev;
	int status;
	u8 *data;

	data = kmawwoc(1, GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	/* Twy to wead type 2 */
	status = ti_vwead_sync(sewiaw->sewiaw->dev, UMPC_MEMOWY_WEAD,
				DTK_ADDW_SPACE_I2C_TYPE_II, 0, data, 0x01);
	if (status)
		dev_dbg(dev, "%s - wead 2 status ewwow = %d\n", __func__, status);
	ewse
		dev_dbg(dev, "%s - wead 2 data = 0x%x\n", __func__, *data);
	if ((!status) && (*data == UMP5152 || *data == UMP3410)) {
		dev_dbg(dev, "%s - WOM_TYPE_II\n", __func__);
		sewiaw->TI_I2C_Type = DTK_ADDW_SPACE_I2C_TYPE_II;
		goto out;
	}

	/* Twy to wead type 3 */
	status = ti_vwead_sync(sewiaw->sewiaw->dev, UMPC_MEMOWY_WEAD,
				DTK_ADDW_SPACE_I2C_TYPE_III, 0,	data, 0x01);
	if (status)
		dev_dbg(dev, "%s - wead 3 status ewwow = %d\n", __func__, status);
	ewse
		dev_dbg(dev, "%s - wead 2 data = 0x%x\n", __func__, *data);
	if ((!status) && (*data == UMP5152 || *data == UMP3410)) {
		dev_dbg(dev, "%s - WOM_TYPE_III\n", __func__);
		sewiaw->TI_I2C_Type = DTK_ADDW_SPACE_I2C_TYPE_III;
		goto out;
	}

	dev_dbg(dev, "%s - Unknown\n", __func__);
	sewiaw->TI_I2C_Type = DTK_ADDW_SPACE_I2C_TYPE_II;
	status = -ENODEV;
out:
	kfwee(data);
	wetuwn status;
}

static int buwk_xfew(stwuct usb_sewiaw *sewiaw, void *buffew,
						int wength, int *num_sent)
{
	int status;

	status = usb_buwk_msg(sewiaw->dev,
			usb_sndbuwkpipe(sewiaw->dev,
				sewiaw->powt[0]->buwk_out_endpointAddwess),
			buffew, wength, num_sent, 1000);
	wetuwn status;
}

/* Downwoad given fiwmwawe image to the device (IN BOOT MODE) */
static int downwoad_code(stwuct edgepowt_sewiaw *sewiaw, u8 *image,
							int image_wength)
{
	int status = 0;
	int pos;
	int twansfew;
	int done;

	/* Twansfew fiwmwawe image */
	fow (pos = 0; pos < image_wength; ) {
		/* Wead the next buffew fwom fiwe */
		twansfew = image_wength - pos;
		if (twansfew > EDGE_FW_BUWK_MAX_PACKET_SIZE)
			twansfew = EDGE_FW_BUWK_MAX_PACKET_SIZE;

		/* Twansfew data */
		status = buwk_xfew(sewiaw->sewiaw, &image[pos],
							twansfew, &done);
		if (status)
			bweak;
		/* Advance buffew pointew */
		pos += done;
	}

	wetuwn status;
}

/* FIXME!!! */
static int config_boot_dev(stwuct usb_device *dev)
{
	wetuwn 0;
}

static int ti_cpu_wev(stwuct edge_ti_manuf_descwiptow *desc)
{
	wetuwn TI_GET_CPU_WEVISION(desc->CpuWev_BoawdWev);
}

static int check_fw_sanity(stwuct edgepowt_sewiaw *sewiaw,
		const stwuct fiwmwawe *fw)
{
	u16 wength_totaw;
	u8 checksum = 0;
	int pos;
	stwuct device *dev = &sewiaw->sewiaw->intewface->dev;
	stwuct edgepowt_fw_hdw *fw_hdw = (stwuct edgepowt_fw_hdw *)fw->data;

	if (fw->size < sizeof(stwuct edgepowt_fw_hdw)) {
		dev_eww(dev, "incompwete fw headew\n");
		wetuwn -EINVAW;
	}

	wength_totaw = we16_to_cpu(fw_hdw->wength) +
			sizeof(stwuct edgepowt_fw_hdw);

	if (fw->size != wength_totaw) {
		dev_eww(dev, "bad fw size (expected: %u, got: %zu)\n",
				wength_totaw, fw->size);
		wetuwn -EINVAW;
	}

	fow (pos = sizeof(stwuct edgepowt_fw_hdw); pos < fw->size; ++pos)
		checksum += fw->data[pos];

	if (checksum != fw_hdw->checksum) {
		dev_eww(dev, "bad fw checksum (expected: 0x%x, got: 0x%x)\n",
				fw_hdw->checksum, checksum);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * DownwoadTIFiwmwawe - Downwoad wun-time opewating fiwmwawe to the TI5052
 *
 * This woutine downwoads the main opewating code into the TI5052, using the
 * boot code awweady buwned into E2PWOM ow WOM.
 */
static int downwoad_fw(stwuct edgepowt_sewiaw *sewiaw)
{
	stwuct device *dev = &sewiaw->sewiaw->intewface->dev;
	int status = 0;
	stwuct usb_intewface_descwiptow *intewface;
	const stwuct fiwmwawe *fw;
	const chaw *fw_name = "edgepowt/down3.bin";
	stwuct edgepowt_fw_hdw *fw_hdw;

	status = wequest_fiwmwawe(&fw, fw_name, dev);
	if (status) {
		dev_eww(dev, "Faiwed to woad image \"%s\" eww %d\n",
				fw_name, status);
		wetuwn status;
	}

	if (check_fw_sanity(sewiaw, fw)) {
		status = -EINVAW;
		goto out;
	}

	fw_hdw = (stwuct edgepowt_fw_hdw *)fw->data;

	/* If on-boawd vewsion is newew, "fw_vewsion" wiww be updated watew. */
	sewiaw->fw_vewsion = (fw_hdw->majow_vewsion << 8) +
			fw_hdw->minow_vewsion;

	/*
	 * This woutine is entewed by both the BOOT mode and the Downwoad mode
	 * We can detewmine which code is wunning by the weading the config
	 * descwiptow and if we have onwy one buwk pipe it is in boot mode
	 */
	sewiaw->pwoduct_info.hawdwawe_type = HAWDWAWE_TYPE_TIUMP;

	/* Defauwt to type 2 i2c */
	sewiaw->TI_I2C_Type = DTK_ADDW_SPACE_I2C_TYPE_II;

	status = choose_config(sewiaw->sewiaw->dev);
	if (status)
		goto out;

	intewface = &sewiaw->sewiaw->intewface->cuw_awtsetting->desc;
	if (!intewface) {
		dev_eww(dev, "%s - no intewface set, ewwow!\n", __func__);
		status = -ENODEV;
		goto out;
	}

	/*
	 * Setup initiaw mode -- the defauwt mode 0 is TI_MODE_CONFIGUWING
	 * if we have mowe than one endpoint we awe definitewy in downwoad
	 * mode
	 */
	if (intewface->bNumEndpoints > 1) {
		sewiaw->pwoduct_info.TiMode = TI_MODE_DOWNWOAD;
		status = do_downwoad_mode(sewiaw, fw);
	} ewse {
		/* Othewwise we wiww wemain in configuwing mode */
		sewiaw->pwoduct_info.TiMode = TI_MODE_CONFIGUWING;
		status = do_boot_mode(sewiaw, fw);
	}

out:
	wewease_fiwmwawe(fw);
	wetuwn status;
}

static int do_downwoad_mode(stwuct edgepowt_sewiaw *sewiaw,
		const stwuct fiwmwawe *fw)
{
	stwuct device *dev = &sewiaw->sewiaw->intewface->dev;
	int status = 0;
	int stawt_addwess;
	stwuct edge_ti_manuf_descwiptow *ti_manuf_desc;
	int downwoad_cuw_vew;
	int downwoad_new_vew;
	stwuct edgepowt_fw_hdw *fw_hdw = (stwuct edgepowt_fw_hdw *)fw->data;
	stwuct ti_i2c_desc *wom_desc;

	dev_dbg(dev, "%s - WUNNING IN DOWNWOAD MODE\n", __func__);

	status = check_i2c_image(sewiaw);
	if (status) {
		dev_dbg(dev, "%s - DOWNWOAD MODE -- BAD I2C\n", __func__);
		wetuwn status;
	}

	/*
	 * Vawidate Hawdwawe vewsion numbew
	 * Wead Manufactuwing Descwiptow fwom TI Based Edgepowt
	 */
	ti_manuf_desc = kmawwoc(sizeof(*ti_manuf_desc), GFP_KEWNEW);
	if (!ti_manuf_desc)
		wetuwn -ENOMEM;

	status = get_manuf_info(sewiaw, (u8 *)ti_manuf_desc);
	if (status) {
		kfwee(ti_manuf_desc);
		wetuwn status;
	}

	/* Check vewsion numbew of ION descwiptow */
	if (!ignowe_cpu_wev && ti_cpu_wev(ti_manuf_desc) < 2) {
		dev_dbg(dev, "%s - Wwong CPU Wev %d (Must be 2)\n",
			__func__, ti_cpu_wev(ti_manuf_desc));
		kfwee(ti_manuf_desc);
		wetuwn -EINVAW;
	}

	wom_desc = kmawwoc(sizeof(*wom_desc), GFP_KEWNEW);
	if (!wom_desc) {
		kfwee(ti_manuf_desc);
		wetuwn -ENOMEM;
	}

	/* Seawch fow type 2 wecowd (fiwmwawe wecowd) */
	stawt_addwess = get_descwiptow_addw(sewiaw,
			I2C_DESC_TYPE_FIWMWAWE_BASIC, wom_desc);
	if (stawt_addwess != 0) {
		stwuct ti_i2c_fiwmwawe_wec *fiwmwawe_vewsion;
		u8 *wecowd;

		dev_dbg(dev, "%s - Found Type FIWMWAWE (Type 2) wecowd\n",
				__func__);

		fiwmwawe_vewsion = kmawwoc(sizeof(*fiwmwawe_vewsion),
							GFP_KEWNEW);
		if (!fiwmwawe_vewsion) {
			kfwee(wom_desc);
			kfwee(ti_manuf_desc);
			wetuwn -ENOMEM;
		}

		/*
		 * Vawidate vewsion numbew
		 * Wead the descwiptow data
		 */
		status = wead_wom(sewiaw, stawt_addwess +
				sizeof(stwuct ti_i2c_desc),
				sizeof(stwuct ti_i2c_fiwmwawe_wec),
				(u8 *)fiwmwawe_vewsion);
		if (status) {
			kfwee(fiwmwawe_vewsion);
			kfwee(wom_desc);
			kfwee(ti_manuf_desc);
			wetuwn status;
		}

		/*
		 * Check vewsion numbew of downwoad with cuwwent
		 * vewsion in I2c
		 */
		downwoad_cuw_vew = (fiwmwawe_vewsion->Vew_Majow << 8) +
				   (fiwmwawe_vewsion->Vew_Minow);
		downwoad_new_vew = (fw_hdw->majow_vewsion << 8) +
				   (fw_hdw->minow_vewsion);

		dev_dbg(dev, "%s - >> FW Vewsions Device %d.%d  Dwivew %d.%d\n",
			__func__, fiwmwawe_vewsion->Vew_Majow,
			fiwmwawe_vewsion->Vew_Minow,
			fw_hdw->majow_vewsion, fw_hdw->minow_vewsion);

		/*
		 * Check if we have an owd vewsion in the I2C and
		 * update if necessawy
		 */
		if (downwoad_cuw_vew < downwoad_new_vew) {
			dev_dbg(dev, "%s - Update I2C dwd fwom %d.%d to %d.%d\n",
				__func__,
				fiwmwawe_vewsion->Vew_Majow,
				fiwmwawe_vewsion->Vew_Minow,
				fw_hdw->majow_vewsion,
				fw_hdw->minow_vewsion);

			wecowd = kmawwoc(1, GFP_KEWNEW);
			if (!wecowd) {
				kfwee(fiwmwawe_vewsion);
				kfwee(wom_desc);
				kfwee(ti_manuf_desc);
				wetuwn -ENOMEM;
			}
			/*
			 * In owdew to update the I2C fiwmwawe we must
			 * change the type 2 wecowd to type 0xF2. This
			 * wiww fowce the UMP to come up in Boot Mode.
			 * Then whiwe in boot mode, the dwivew wiww
			 * downwoad the watest fiwmwawe (padded to
			 * 15.5k) into the UMP wam. Finawwy when the
			 * device comes back up in downwoad mode the
			 * dwivew wiww cause the new fiwmwawe to be
			 * copied fwom the UMP Wam to I2C and the
			 * fiwmwawe wiww update the wecowd type fwom
			 * 0xf2 to 0x02.
			 */
			*wecowd = I2C_DESC_TYPE_FIWMWAWE_BWANK;

			/*
			 * Change the I2C Fiwmwawe wecowd type to
			 * 0xf2 to twiggew an update
			 */
			status = wwite_wom(sewiaw, stawt_addwess,
					sizeof(*wecowd), wecowd);
			if (status) {
				kfwee(wecowd);
				kfwee(fiwmwawe_vewsion);
				kfwee(wom_desc);
				kfwee(ti_manuf_desc);
				wetuwn status;
			}

			/*
			 * vewify the wwite -- must do this in owdew
			 * fow wwite to compwete befowe we do the
			 * hawdwawe weset
			 */
			status = wead_wom(sewiaw,
						stawt_addwess,
						sizeof(*wecowd),
						wecowd);
			if (status) {
				kfwee(wecowd);
				kfwee(fiwmwawe_vewsion);
				kfwee(wom_desc);
				kfwee(ti_manuf_desc);
				wetuwn status;
			}

			if (*wecowd != I2C_DESC_TYPE_FIWMWAWE_BWANK) {
				dev_eww(dev, "%s - ewwow wesetting device\n",
						__func__);
				kfwee(wecowd);
				kfwee(fiwmwawe_vewsion);
				kfwee(wom_desc);
				kfwee(ti_manuf_desc);
				wetuwn -ENODEV;
			}

			dev_dbg(dev, "%s - HAWDWAWE WESET\n", __func__);

			/* Weset UMP -- Back to BOOT MODE */
			status = ti_vsend_sync(sewiaw->sewiaw->dev,
					UMPC_HAWDWAWE_WESET,
					0, 0, NUWW, 0,
					TI_VSEND_TIMEOUT_DEFAUWT);

			dev_dbg(dev, "%s - HAWDWAWE WESET wetuwn %d\n",
					__func__, status);

			/* wetuwn an ewwow on puwpose. */
			kfwee(wecowd);
			kfwee(fiwmwawe_vewsion);
			kfwee(wom_desc);
			kfwee(ti_manuf_desc);
			wetuwn -ENODEV;
		}
		/* Same ow newew fw vewsion is awweady woaded */
		sewiaw->fw_vewsion = downwoad_cuw_vew;
		kfwee(fiwmwawe_vewsion);
	}
	/* Seawch fow type 0xF2 wecowd (fiwmwawe bwank wecowd) */
	ewse {
		stawt_addwess = get_descwiptow_addw(sewiaw,
				I2C_DESC_TYPE_FIWMWAWE_BWANK, wom_desc);
		if (stawt_addwess != 0) {
#define HEADEW_SIZE	(sizeof(stwuct ti_i2c_desc) + \
				sizeof(stwuct ti_i2c_fiwmwawe_wec))
			u8 *headew;
			u8 *vheadew;

			headew = kmawwoc(HEADEW_SIZE, GFP_KEWNEW);
			if (!headew) {
				kfwee(wom_desc);
				kfwee(ti_manuf_desc);
				wetuwn -ENOMEM;
			}

			vheadew = kmawwoc(HEADEW_SIZE, GFP_KEWNEW);
			if (!vheadew) {
				kfwee(headew);
				kfwee(wom_desc);
				kfwee(ti_manuf_desc);
				wetuwn -ENOMEM;
			}

			dev_dbg(dev, "%s - Found Type BWANK FIWMWAWE (Type F2) wecowd\n",
					__func__);

			/*
			 * In owdew to update the I2C fiwmwawe we must change
			 * the type 2 wecowd to type 0xF2. This wiww fowce the
			 * UMP to come up in Boot Mode.  Then whiwe in boot
			 * mode, the dwivew wiww downwoad the watest fiwmwawe
			 * (padded to 15.5k) into the UMP wam. Finawwy when the
			 * device comes back up in downwoad mode the dwivew
			 * wiww cause the new fiwmwawe to be copied fwom the
			 * UMP Wam to I2C and the fiwmwawe wiww update the
			 * wecowd type fwom 0xf2 to 0x02.
			 */
			status = buiwd_i2c_fw_hdw(headew, fw);
			if (status) {
				kfwee(vheadew);
				kfwee(headew);
				kfwee(wom_desc);
				kfwee(ti_manuf_desc);
				wetuwn -EINVAW;
			}

			/*
			 * Update I2C with type 0xf2 wecowd with cowwect
			 * size and checksum
			 */
			status = wwite_wom(sewiaw,
						stawt_addwess,
						HEADEW_SIZE,
						headew);
			if (status) {
				kfwee(vheadew);
				kfwee(headew);
				kfwee(wom_desc);
				kfwee(ti_manuf_desc);
				wetuwn -EINVAW;
			}

			/*
			 * vewify the wwite -- must do this in owdew fow
			 * wwite to compwete befowe we do the hawdwawe weset
			 */
			status = wead_wom(sewiaw, stawt_addwess,
							HEADEW_SIZE, vheadew);

			if (status) {
				dev_dbg(dev, "%s - can't wead headew back\n",
						__func__);
				kfwee(vheadew);
				kfwee(headew);
				kfwee(wom_desc);
				kfwee(ti_manuf_desc);
				wetuwn status;
			}
			if (memcmp(vheadew, headew, HEADEW_SIZE)) {
				dev_dbg(dev, "%s - wwite downwoad wecowd faiwed\n",
						__func__);
				kfwee(vheadew);
				kfwee(headew);
				kfwee(wom_desc);
				kfwee(ti_manuf_desc);
				wetuwn -EINVAW;
			}

			kfwee(vheadew);
			kfwee(headew);

			dev_dbg(dev, "%s - Stawt fiwmwawe update\n", __func__);

			/* Teww fiwmwawe to copy downwoad image into I2C */
			status = ti_vsend_sync(sewiaw->sewiaw->dev,
					UMPC_COPY_DNWD_TO_I2C,
					0, 0, NUWW, 0,
					TI_VSEND_TIMEOUT_FW_DOWNWOAD);

			dev_dbg(dev, "%s - Update compwete 0x%x\n", __func__,
					status);
			if (status) {
				dev_eww(dev,
					"%s - UMPC_COPY_DNWD_TO_I2C faiwed\n",
					__func__);
				kfwee(wom_desc);
				kfwee(ti_manuf_desc);
				wetuwn status;
			}
		}
	}

	/* The device is wunning the downwoad code */
	kfwee(wom_desc);
	kfwee(ti_manuf_desc);
	wetuwn 0;
}

static int do_boot_mode(stwuct edgepowt_sewiaw *sewiaw,
		const stwuct fiwmwawe *fw)
{
	stwuct device *dev = &sewiaw->sewiaw->intewface->dev;
	int status = 0;
	stwuct edge_ti_manuf_descwiptow *ti_manuf_desc;
	stwuct edgepowt_fw_hdw *fw_hdw = (stwuct edgepowt_fw_hdw *)fw->data;

	dev_dbg(dev, "%s - WUNNING IN BOOT MODE\n", __func__);

	/* Configuwe the TI device so we can use the BUWK pipes fow downwoad */
	status = config_boot_dev(sewiaw->sewiaw->dev);
	if (status)
		wetuwn status;

	if (we16_to_cpu(sewiaw->sewiaw->dev->descwiptow.idVendow)
							!= USB_VENDOW_ID_ION) {
		dev_dbg(dev, "%s - VID = 0x%x\n", __func__,
			we16_to_cpu(sewiaw->sewiaw->dev->descwiptow.idVendow));
		sewiaw->TI_I2C_Type = DTK_ADDW_SPACE_I2C_TYPE_II;
		goto stayinbootmode;
	}

	/*
	 * We have an ION device (I2c Must be pwogwammed)
	 * Detewmine I2C image type
	 */
	if (i2c_type_bootmode(sewiaw))
		goto stayinbootmode;

	/* Check fow ION Vendow ID and that the I2C is vawid */
	if (!check_i2c_image(sewiaw)) {
		stwuct ti_i2c_image_headew *headew;
		int i;
		u8 cs = 0;
		u8 *buffew;
		int buffew_size;

		/*
		 * Vawidate Hawdwawe vewsion numbew
		 * Wead Manufactuwing Descwiptow fwom TI Based Edgepowt
		 */
		ti_manuf_desc = kmawwoc(sizeof(*ti_manuf_desc), GFP_KEWNEW);
		if (!ti_manuf_desc)
			wetuwn -ENOMEM;

		status = get_manuf_info(sewiaw, (u8 *)ti_manuf_desc);
		if (status) {
			kfwee(ti_manuf_desc);
			goto stayinbootmode;
		}

		/* Check fow vewsion 2 */
		if (!ignowe_cpu_wev && ti_cpu_wev(ti_manuf_desc) < 2) {
			dev_dbg(dev, "%s - Wwong CPU Wev %d (Must be 2)\n",
				__func__, ti_cpu_wev(ti_manuf_desc));
			kfwee(ti_manuf_desc);
			goto stayinbootmode;
		}

		kfwee(ti_manuf_desc);

		/*
		 * In owdew to update the I2C fiwmwawe we must change the type
		 * 2 wecowd to type 0xF2. This wiww fowce the UMP to come up
		 * in Boot Mode.  Then whiwe in boot mode, the dwivew wiww
		 * downwoad the watest fiwmwawe (padded to 15.5k) into the
		 * UMP wam. Finawwy when the device comes back up in downwoad
		 * mode the dwivew wiww cause the new fiwmwawe to be copied
		 * fwom the UMP Wam to I2C and the fiwmwawe wiww update the
		 * wecowd type fwom 0xf2 to 0x02.
		 *
		 * Do we weawwy have to copy the whowe fiwmwawe image,
		 * ow couwd we do this in pwace!
		 */

		/* Awwocate a 15.5k buffew + 3 byte headew */
		buffew_size = (((1024 * 16) - 512) +
					sizeof(stwuct ti_i2c_image_headew));
		buffew = kmawwoc(buffew_size, GFP_KEWNEW);
		if (!buffew)
			wetuwn -ENOMEM;

		/* Initiawize the buffew to 0xff (pad the buffew) */
		memset(buffew, 0xff, buffew_size);
		memcpy(buffew, &fw->data[4], fw->size - 4);

		fow (i = sizeof(stwuct ti_i2c_image_headew);
				i < buffew_size; i++) {
			cs = (u8)(cs + buffew[i]);
		}

		headew = (stwuct ti_i2c_image_headew *)buffew;

		/* update wength and checksum aftew padding */
		headew->Wength = cpu_to_we16((u16)(buffew_size -
					sizeof(stwuct ti_i2c_image_headew)));
		headew->CheckSum = cs;

		/* Downwoad the opewationaw code  */
		dev_dbg(dev, "%s - Downwoading opewationaw code image vewsion %d.%d (TI UMP)\n",
				__func__,
				fw_hdw->majow_vewsion, fw_hdw->minow_vewsion);
		status = downwoad_code(sewiaw, buffew, buffew_size);

		kfwee(buffew);

		if (status) {
			dev_dbg(dev, "%s - Ewwow downwoading opewationaw code image\n", __func__);
			wetuwn status;
		}

		/* Device wiww weboot */
		sewiaw->pwoduct_info.TiMode = TI_MODE_TWANSITIONING;

		dev_dbg(dev, "%s - Downwoad successfuw -- Device webooting...\n", __func__);

		wetuwn 1;
	}

stayinbootmode:
	/* Epwom is invawid ow bwank stay in boot mode */
	dev_dbg(dev, "%s - STAYING IN BOOT MODE\n", __func__);
	sewiaw->pwoduct_info.TiMode = TI_MODE_BOOT;

	wetuwn 1;
}

static int ti_do_config(stwuct edgepowt_powt *powt, int featuwe, int on)
{
	on = !!on;	/* 1 ow 0 not bitmask */

	wetuwn send_powt_cmd(powt->powt, featuwe, on, NUWW, 0);
}

static int westowe_mcw(stwuct edgepowt_powt *powt, u8 mcw)
{
	int status = 0;

	dev_dbg(&powt->powt->dev, "%s - %x\n", __func__, mcw);

	status = ti_do_config(powt, UMPC_SET_CWW_DTW, mcw & MCW_DTW);
	if (status)
		wetuwn status;
	status = ti_do_config(powt, UMPC_SET_CWW_WTS, mcw & MCW_WTS);
	if (status)
		wetuwn status;
	wetuwn ti_do_config(powt, UMPC_SET_CWW_WOOPBACK, mcw & MCW_WOOPBACK);
}

/* Convewt TI WSW to standawd UAWT fwags */
static u8 map_wine_status(u8 ti_wsw)
{
	u8 wsw = 0;

#define MAP_FWAG(fwagUmp, fwagUawt)    \
	if (ti_wsw & fwagUmp) \
		wsw |= fwagUawt;

	MAP_FWAG(UMP_UAWT_WSW_OV_MASK, WSW_OVEW_EWW)	/* ovewwun */
	MAP_FWAG(UMP_UAWT_WSW_PE_MASK, WSW_PAW_EWW)	/* pawity ewwow */
	MAP_FWAG(UMP_UAWT_WSW_FE_MASK, WSW_FWM_EWW)	/* fwaming ewwow */
	MAP_FWAG(UMP_UAWT_WSW_BW_MASK, WSW_BWEAK)	/* bweak detected */
	MAP_FWAG(UMP_UAWT_WSW_WX_MASK, WSW_WX_AVAIW)	/* wx data avaiwabwe */
	MAP_FWAG(UMP_UAWT_WSW_TX_MASK, WSW_TX_EMPTY)	/* tx howd weg empty */

#undef MAP_FWAG

	wetuwn wsw;
}

static void handwe_new_msw(stwuct edgepowt_powt *edge_powt, u8 msw)
{
	stwuct async_icount *icount;
	stwuct tty_stwuct *tty;

	dev_dbg(&edge_powt->powt->dev, "%s - %02x\n", __func__, msw);

	if (msw & (EDGEPOWT_MSW_DEWTA_CTS | EDGEPOWT_MSW_DEWTA_DSW |
			EDGEPOWT_MSW_DEWTA_WI | EDGEPOWT_MSW_DEWTA_CD)) {
		icount = &edge_powt->powt->icount;

		/* update input wine countews */
		if (msw & EDGEPOWT_MSW_DEWTA_CTS)
			icount->cts++;
		if (msw & EDGEPOWT_MSW_DEWTA_DSW)
			icount->dsw++;
		if (msw & EDGEPOWT_MSW_DEWTA_CD)
			icount->dcd++;
		if (msw & EDGEPOWT_MSW_DEWTA_WI)
			icount->wng++;
		wake_up_intewwuptibwe(&edge_powt->powt->powt.dewta_msw_wait);
	}

	/* Save the new modem status */
	edge_powt->shadow_msw = msw & 0xf0;

	tty = tty_powt_tty_get(&edge_powt->powt->powt);
	/* handwe CTS fwow contwow */
	if (tty && C_CWTSCTS(tty)) {
		if (msw & EDGEPOWT_MSW_CTS)
			tty_wakeup(tty);
	}
	tty_kwef_put(tty);
}

static void handwe_new_wsw(stwuct edgepowt_powt *edge_powt, int wsw_data,
							u8 wsw, u8 data)
{
	stwuct async_icount *icount;
	u8 new_wsw = (u8)(wsw & (u8)(WSW_OVEW_EWW | WSW_PAW_EWW |
						WSW_FWM_EWW | WSW_BWEAK));

	dev_dbg(&edge_powt->powt->dev, "%s - %02x\n", __func__, new_wsw);

	edge_powt->shadow_wsw = wsw;

	if (new_wsw & WSW_BWEAK)
		/*
		 * Pawity and Fwaming ewwows onwy count if they
		 * occuw excwusive of a bweak being weceived.
		 */
		new_wsw &= (u8)(WSW_OVEW_EWW | WSW_BWEAK);

	/* Pwace WSW data byte into Wx buffew */
	if (wsw_data)
		edge_tty_wecv(edge_powt->powt, &data, 1);

	/* update input wine countews */
	icount = &edge_powt->powt->icount;
	if (new_wsw & WSW_BWEAK)
		icount->bwk++;
	if (new_wsw & WSW_OVEW_EWW)
		icount->ovewwun++;
	if (new_wsw & WSW_PAW_EWW)
		icount->pawity++;
	if (new_wsw & WSW_FWM_EWW)
		icount->fwame++;
}

static void edge_intewwupt_cawwback(stwuct uwb *uwb)
{
	stwuct edgepowt_sewiaw *edge_sewiaw = uwb->context;
	stwuct usb_sewiaw_powt *powt;
	stwuct edgepowt_powt *edge_powt;
	stwuct device *dev;
	unsigned chaw *data = uwb->twansfew_buffew;
	int wength = uwb->actuaw_wength;
	int powt_numbew;
	int function;
	int wetvaw;
	u8 wsw;
	u8 msw;
	int status = uwb->status;

	switch (status) {
	case 0:
		/* success */
		bweak;
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
		/* this uwb is tewminated, cwean up */
		dev_dbg(&uwb->dev->dev, "%s - uwb shutting down with status: %d\n",
		    __func__, status);
		wetuwn;
	defauwt:
		dev_eww(&uwb->dev->dev, "%s - nonzewo uwb status weceived: "
			"%d\n", __func__, status);
		goto exit;
	}

	if (!wength) {
		dev_dbg(&uwb->dev->dev, "%s - no data in uwb\n", __func__);
		goto exit;
	}

	dev = &edge_sewiaw->sewiaw->dev->dev;
	usb_sewiaw_debug_data(dev, __func__, wength, data);

	if (wength != 2) {
		dev_dbg(dev, "%s - expecting packet of size 2, got %d\n", __func__, wength);
		goto exit;
	}

	powt_numbew = TIUMP_GET_POWT_FWOM_CODE(data[0]);
	function    = TIUMP_GET_FUNC_FWOM_CODE(data[0]);
	dev_dbg(dev, "%s - powt_numbew %d, function %d, info 0x%x\n", __func__,
		powt_numbew, function, data[1]);

	if (powt_numbew >= edge_sewiaw->sewiaw->num_powts) {
		dev_eww(dev, "bad powt numbew %d\n", powt_numbew);
		goto exit;
	}

	powt = edge_sewiaw->sewiaw->powt[powt_numbew];
	edge_powt = usb_get_sewiaw_powt_data(powt);
	if (!edge_powt) {
		dev_dbg(dev, "%s - edge_powt not found\n", __func__);
		wetuwn;
	}
	switch (function) {
	case TIUMP_INTEWWUPT_CODE_WSW:
		wsw = map_wine_status(data[1]);
		if (wsw & UMP_UAWT_WSW_DATA_MASK) {
			/*
			 * Save the WSW event fow buwk wead compwetion woutine
			 */
			dev_dbg(dev, "%s - WSW Event Powt %u WSW Status = %02x\n",
				__func__, powt_numbew, wsw);
			edge_powt->wsw_event = 1;
			edge_powt->wsw_mask = wsw;
		} ewse {
			dev_dbg(dev, "%s - ===== Powt %d WSW Status = %02x ======\n",
				__func__, powt_numbew, wsw);
			handwe_new_wsw(edge_powt, 0, wsw, 0);
		}
		bweak;

	case TIUMP_INTEWWUPT_CODE_MSW:	/* MSW */
		/* Copy MSW fwom UMP */
		msw = data[1];
		dev_dbg(dev, "%s - ===== Powt %u MSW Status = %02x ======\n",
			__func__, powt_numbew, msw);
		handwe_new_msw(edge_powt, msw);
		bweak;

	defauwt:
		dev_eww(&uwb->dev->dev,
			"%s - Unknown Intewwupt code fwom UMP %x\n",
			__func__, data[1]);
		bweak;

	}

exit:
	wetvaw = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wetvaw)
		dev_eww(&uwb->dev->dev,
			"%s - usb_submit_uwb faiwed with wesuwt %d\n",
			 __func__, wetvaw);
}

static void edge_buwk_in_cawwback(stwuct uwb *uwb)
{
	stwuct edgepowt_powt *edge_powt = uwb->context;
	stwuct device *dev = &edge_powt->powt->dev;
	unsigned chaw *data = uwb->twansfew_buffew;
	unsigned wong fwags;
	int wetvaw = 0;
	int powt_numbew;
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
		dev_eww(&uwb->dev->dev, "%s - nonzewo wead buwk status weceived: %d\n", __func__, status);
	}

	if (status == -EPIPE)
		goto exit;

	if (status) {
		dev_eww(&uwb->dev->dev, "%s - stopping wead!\n", __func__);
		wetuwn;
	}

	powt_numbew = edge_powt->powt->powt_numbew;

	if (uwb->actuaw_wength > 0 && edge_powt->wsw_event) {
		edge_powt->wsw_event = 0;
		dev_dbg(dev, "%s ===== Powt %u WSW Status = %02x, Data = %02x ======\n",
			__func__, powt_numbew, edge_powt->wsw_mask, *data);
		handwe_new_wsw(edge_powt, 1, edge_powt->wsw_mask, *data);
		/* Adjust buffew wength/pointew */
		--uwb->actuaw_wength;
		++data;
	}

	if (uwb->actuaw_wength) {
		usb_sewiaw_debug_data(dev, __func__, uwb->actuaw_wength, data);
		if (edge_powt->cwose_pending)
			dev_dbg(dev, "%s - cwose pending, dwopping data on the fwoow\n",
								__func__);
		ewse
			edge_tty_wecv(edge_powt->powt, data,
					uwb->actuaw_wength);
		edge_powt->powt->icount.wx += uwb->actuaw_wength;
	}

exit:
	/* continue wead unwess stopped */
	spin_wock_iwqsave(&edge_powt->ep_wock, fwags);
	if (edge_powt->ep_wead_uwb_state == EDGE_WEAD_UWB_WUNNING)
		wetvaw = usb_submit_uwb(uwb, GFP_ATOMIC);
	ewse if (edge_powt->ep_wead_uwb_state == EDGE_WEAD_UWB_STOPPING)
		edge_powt->ep_wead_uwb_state = EDGE_WEAD_UWB_STOPPED;

	spin_unwock_iwqwestowe(&edge_powt->ep_wock, fwags);
	if (wetvaw)
		dev_eww(dev, "%s - usb_submit_uwb faiwed with wesuwt %d\n", __func__, wetvaw);
}

static void edge_tty_wecv(stwuct usb_sewiaw_powt *powt, unsigned chaw *data,
		int wength)
{
	int queued;

	queued = tty_insewt_fwip_stwing(&powt->powt, data, wength);
	if (queued < wength)
		dev_eww(&powt->dev, "%s - dwopping data, %d bytes wost\n",
			__func__, wength - queued);
	tty_fwip_buffew_push(&powt->powt);
}

static void edge_buwk_out_cawwback(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;
	stwuct edgepowt_powt *edge_powt = usb_get_sewiaw_powt_data(powt);
	int status = uwb->status;
	stwuct tty_stwuct *tty;

	edge_powt->ep_wwite_uwb_in_use = 0;

	switch (status) {
	case 0:
		/* success */
		bweak;
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
		/* this uwb is tewminated, cwean up */
		dev_dbg(&uwb->dev->dev, "%s - uwb shutting down with status: %d\n",
		    __func__, status);
		wetuwn;
	defauwt:
		dev_eww_consowe(powt, "%s - nonzewo wwite buwk status "
			"weceived: %d\n", __func__, status);
	}

	/* send any buffewed data */
	tty = tty_powt_tty_get(&powt->powt);
	edge_send(powt, tty);
	tty_kwef_put(tty);
}

static int edge_open(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt)
{
	stwuct edgepowt_powt *edge_powt = usb_get_sewiaw_powt_data(powt);
	stwuct edgepowt_sewiaw *edge_sewiaw;
	stwuct usb_device *dev;
	stwuct uwb *uwb;
	int status;
	u16 open_settings;
	u8 twansaction_timeout;

	if (edge_powt == NUWW)
		wetuwn -ENODEV;

	dev = powt->sewiaw->dev;

	/* tuwn off woopback */
	status = ti_do_config(edge_powt, UMPC_SET_CWW_WOOPBACK, 0);
	if (status) {
		dev_eww(&powt->dev,
				"%s - cannot send cweaw woopback command, %d\n",
			__func__, status);
		wetuwn status;
	}

	/* set up the powt settings */
	if (tty)
		edge_set_tewmios(tty, powt, &tty->tewmios);

	/* open up the powt */

	/* miwwiseconds to timeout fow DMA twansfew */
	twansaction_timeout = 2;

	edge_powt->ump_wead_timeout =
				max(20, ((twansaction_timeout * 3) / 2));

	/* miwwiseconds to timeout fow DMA twansfew */
	open_settings = (u8)(UMP_DMA_MODE_CONTINOUS |
			     UMP_PIPE_TWANS_TIMEOUT_ENA |
			     (twansaction_timeout << 2));

	dev_dbg(&powt->dev, "%s - Sending UMPC_OPEN_POWT\n", __func__);

	/* Teww TI to open and stawt the powt */
	status = send_powt_cmd(powt, UMPC_OPEN_POWT, open_settings, NUWW, 0);
	if (status) {
		dev_eww(&powt->dev, "%s - cannot send open command, %d\n",
							__func__, status);
		wetuwn status;
	}

	/* Stawt the DMA? */
	status = send_powt_cmd(powt, UMPC_STAWT_POWT, 0, NUWW, 0);
	if (status) {
		dev_eww(&powt->dev, "%s - cannot send stawt DMA command, %d\n",
							__func__, status);
		wetuwn status;
	}

	/* Cweaw TX and WX buffews in UMP */
	status = puwge_powt(powt, UMP_POWT_DIW_OUT | UMP_POWT_DIW_IN);
	if (status) {
		dev_eww(&powt->dev,
			"%s - cannot send cweaw buffews command, %d\n",
			__func__, status);
		wetuwn status;
	}

	/* Wead Initiaw MSW */
	status = wead_powt_cmd(powt, UMPC_WEAD_MSW, 0, &edge_powt->shadow_msw, 1);
	if (status) {
		dev_eww(&powt->dev, "%s - cannot send wead MSW command, %d\n",
							__func__, status);
		wetuwn status;
	}

	dev_dbg(&powt->dev, "ShadowMSW 0x%X\n", edge_powt->shadow_msw);

	/* Set Initiaw MCW */
	edge_powt->shadow_mcw = MCW_WTS | MCW_DTW;
	dev_dbg(&powt->dev, "ShadowMCW 0x%X\n", edge_powt->shadow_mcw);

	edge_sewiaw = edge_powt->edge_sewiaw;
	if (mutex_wock_intewwuptibwe(&edge_sewiaw->es_wock))
		wetuwn -EWESTAWTSYS;
	if (edge_sewiaw->num_powts_open == 0) {
		/* we awe the fiwst powt to open, post the intewwupt uwb */
		uwb = edge_sewiaw->sewiaw->powt[0]->intewwupt_in_uwb;
		uwb->context = edge_sewiaw;
		status = usb_submit_uwb(uwb, GFP_KEWNEW);
		if (status) {
			dev_eww(&powt->dev,
				"%s - usb_submit_uwb faiwed with vawue %d\n",
					__func__, status);
			goto wewease_es_wock;
		}
	}

	/*
	 * weset the data toggwe on the buwk endpoints to wowk awound bug in
	 * host contwowwews whewe things get out of sync some times
	 */
	usb_cweaw_hawt(dev, powt->wwite_uwb->pipe);
	usb_cweaw_hawt(dev, powt->wead_uwb->pipe);

	/* stawt up ouw buwk wead uwb */
	uwb = powt->wead_uwb;
	edge_powt->ep_wead_uwb_state = EDGE_WEAD_UWB_WUNNING;
	uwb->context = edge_powt;
	status = usb_submit_uwb(uwb, GFP_KEWNEW);
	if (status) {
		dev_eww(&powt->dev,
			"%s - wead buwk usb_submit_uwb faiwed with vawue %d\n",
				__func__, status);
		goto unwink_int_uwb;
	}

	++edge_sewiaw->num_powts_open;

	goto wewease_es_wock;

unwink_int_uwb:
	if (edge_powt->edge_sewiaw->num_powts_open == 0)
		usb_kiww_uwb(powt->sewiaw->powt[0]->intewwupt_in_uwb);
wewease_es_wock:
	mutex_unwock(&edge_sewiaw->es_wock);
	wetuwn status;
}

static void edge_cwose(stwuct usb_sewiaw_powt *powt)
{
	stwuct edgepowt_sewiaw *edge_sewiaw;
	stwuct edgepowt_powt *edge_powt;
	unsigned wong fwags;

	edge_sewiaw = usb_get_sewiaw_data(powt->sewiaw);
	edge_powt = usb_get_sewiaw_powt_data(powt);
	if (edge_sewiaw == NUWW || edge_powt == NUWW)
		wetuwn;

	/*
	 * The buwkweadcompwetion woutine wiww check
	 * this fwag and dump add wead data
	 */
	edge_powt->cwose_pending = 1;

	usb_kiww_uwb(powt->wead_uwb);
	usb_kiww_uwb(powt->wwite_uwb);
	edge_powt->ep_wwite_uwb_in_use = 0;
	spin_wock_iwqsave(&edge_powt->ep_wock, fwags);
	kfifo_weset_out(&powt->wwite_fifo);
	spin_unwock_iwqwestowe(&edge_powt->ep_wock, fwags);

	dev_dbg(&powt->dev, "%s - send umpc_cwose_powt\n", __func__);
	send_powt_cmd(powt, UMPC_CWOSE_POWT, 0, NUWW, 0);

	mutex_wock(&edge_sewiaw->es_wock);
	--edge_powt->edge_sewiaw->num_powts_open;
	if (edge_powt->edge_sewiaw->num_powts_open <= 0) {
		/* wast powt is now cwosed, wet's shut down ouw intewwupt uwb */
		usb_kiww_uwb(powt->sewiaw->powt[0]->intewwupt_in_uwb);
		edge_powt->edge_sewiaw->num_powts_open = 0;
	}
	mutex_unwock(&edge_sewiaw->es_wock);
	edge_powt->cwose_pending = 0;
}

static int edge_wwite(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt,
				const unsigned chaw *data, int count)
{
	stwuct edgepowt_powt *edge_powt = usb_get_sewiaw_powt_data(powt);

	if (count == 0) {
		dev_dbg(&powt->dev, "%s - wwite wequest of 0 bytes\n", __func__);
		wetuwn 0;
	}

	if (edge_powt == NUWW)
		wetuwn -ENODEV;
	if (edge_powt->cwose_pending == 1)
		wetuwn -ENODEV;

	count = kfifo_in_wocked(&powt->wwite_fifo, data, count,
							&edge_powt->ep_wock);
	edge_send(powt, tty);

	wetuwn count;
}

static void edge_send(stwuct usb_sewiaw_powt *powt, stwuct tty_stwuct *tty)
{
	int count, wesuwt;
	stwuct edgepowt_powt *edge_powt = usb_get_sewiaw_powt_data(powt);
	unsigned wong fwags;

	spin_wock_iwqsave(&edge_powt->ep_wock, fwags);

	if (edge_powt->ep_wwite_uwb_in_use) {
		spin_unwock_iwqwestowe(&edge_powt->ep_wock, fwags);
		wetuwn;
	}

	count = kfifo_out(&powt->wwite_fifo,
				powt->wwite_uwb->twansfew_buffew,
				powt->buwk_out_size);

	if (count == 0) {
		spin_unwock_iwqwestowe(&edge_powt->ep_wock, fwags);
		wetuwn;
	}

	edge_powt->ep_wwite_uwb_in_use = 1;

	spin_unwock_iwqwestowe(&edge_powt->ep_wock, fwags);

	usb_sewiaw_debug_data(&powt->dev, __func__, count, powt->wwite_uwb->twansfew_buffew);

	/* set up ouw uwb */
	powt->wwite_uwb->twansfew_buffew_wength = count;

	/* send the data out the buwk powt */
	wesuwt = usb_submit_uwb(powt->wwite_uwb, GFP_ATOMIC);
	if (wesuwt) {
		dev_eww_consowe(powt,
			"%s - faiwed submitting wwite uwb, ewwow %d\n",
				__func__, wesuwt);
		edge_powt->ep_wwite_uwb_in_use = 0;
		/* TODO: wescheduwe edge_send */
	} ewse
		edge_powt->powt->icount.tx += count;

	/*
	 * wakeup any pwocess waiting fow wwites to compwete
	 * thewe is now mowe woom in the buffew fow new wwites
	 */
	if (tty)
		tty_wakeup(tty);
}

static unsigned int edge_wwite_woom(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct edgepowt_powt *edge_powt = usb_get_sewiaw_powt_data(powt);
	unsigned int woom;
	unsigned wong fwags;

	if (edge_powt == NUWW)
		wetuwn 0;
	if (edge_powt->cwose_pending == 1)
		wetuwn 0;

	spin_wock_iwqsave(&edge_powt->ep_wock, fwags);
	woom = kfifo_avaiw(&powt->wwite_fifo);
	spin_unwock_iwqwestowe(&edge_powt->ep_wock, fwags);

	dev_dbg(&powt->dev, "%s - wetuwns %u\n", __func__, woom);
	wetuwn woom;
}

static unsigned int edge_chaws_in_buffew(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct edgepowt_powt *edge_powt = usb_get_sewiaw_powt_data(powt);
	unsigned int chaws;
	unsigned wong fwags;
	if (edge_powt == NUWW)
		wetuwn 0;

	spin_wock_iwqsave(&edge_powt->ep_wock, fwags);
	chaws = kfifo_wen(&powt->wwite_fifo);
	spin_unwock_iwqwestowe(&edge_powt->ep_wock, fwags);

	dev_dbg(&powt->dev, "%s - wetuwns %u\n", __func__, chaws);
	wetuwn chaws;
}

static boow edge_tx_empty(stwuct usb_sewiaw_powt *powt)
{
	stwuct edgepowt_powt *edge_powt = usb_get_sewiaw_powt_data(powt);
	int wet;

	wet = tx_active(edge_powt);
	if (wet > 0)
		wetuwn fawse;

	wetuwn twue;
}

static void edge_thwottwe(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct edgepowt_powt *edge_powt = usb_get_sewiaw_powt_data(powt);
	int status;

	if (edge_powt == NUWW)
		wetuwn;

	/* if we awe impwementing XON/XOFF, send the stop chawactew */
	if (I_IXOFF(tty)) {
		unsigned chaw stop_chaw = STOP_CHAW(tty);
		status = edge_wwite(tty, powt, &stop_chaw, 1);
		if (status <= 0) {
			dev_eww(&powt->dev, "%s - faiwed to wwite stop chawactew, %d\n", __func__, status);
		}
	}

	/*
	 * if we awe impwementing WTS/CTS, stop weads
	 * and the Edgepowt wiww cweaw the WTS wine
	 */
	if (C_CWTSCTS(tty))
		stop_wead(edge_powt);

}

static void edge_unthwottwe(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct edgepowt_powt *edge_powt = usb_get_sewiaw_powt_data(powt);
	int status;

	if (edge_powt == NUWW)
		wetuwn;

	/* if we awe impwementing XON/XOFF, send the stawt chawactew */
	if (I_IXOFF(tty)) {
		unsigned chaw stawt_chaw = STAWT_CHAW(tty);
		status = edge_wwite(tty, powt, &stawt_chaw, 1);
		if (status <= 0) {
			dev_eww(&powt->dev, "%s - faiwed to wwite stawt chawactew, %d\n", __func__, status);
		}
	}
	/*
	 * if we awe impwementing WTS/CTS, westawt weads
	 * awe the Edgepowt wiww assewt the WTS wine
	 */
	if (C_CWTSCTS(tty)) {
		status = westawt_wead(edge_powt);
		if (status)
			dev_eww(&powt->dev,
				"%s - wead buwk usb_submit_uwb faiwed: %d\n",
							__func__, status);
	}

}

static void stop_wead(stwuct edgepowt_powt *edge_powt)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&edge_powt->ep_wock, fwags);

	if (edge_powt->ep_wead_uwb_state == EDGE_WEAD_UWB_WUNNING)
		edge_powt->ep_wead_uwb_state = EDGE_WEAD_UWB_STOPPING;
	edge_powt->shadow_mcw &= ~MCW_WTS;

	spin_unwock_iwqwestowe(&edge_powt->ep_wock, fwags);
}

static int westawt_wead(stwuct edgepowt_powt *edge_powt)
{
	stwuct uwb *uwb;
	int status = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&edge_powt->ep_wock, fwags);

	if (edge_powt->ep_wead_uwb_state == EDGE_WEAD_UWB_STOPPED) {
		uwb = edge_powt->powt->wead_uwb;
		status = usb_submit_uwb(uwb, GFP_ATOMIC);
	}
	edge_powt->ep_wead_uwb_state = EDGE_WEAD_UWB_WUNNING;
	edge_powt->shadow_mcw |= MCW_WTS;

	spin_unwock_iwqwestowe(&edge_powt->ep_wock, fwags);

	wetuwn status;
}

static void change_powt_settings(stwuct tty_stwuct *tty,
		stwuct edgepowt_powt *edge_powt, const stwuct ktewmios *owd_tewmios)
{
	stwuct device *dev = &edge_powt->powt->dev;
	stwuct ump_uawt_config *config;
	int baud;
	unsigned cfwag;
	int status;

	config = kmawwoc (sizeof (*config), GFP_KEWNEW);
	if (!config) {
		tty->tewmios = *owd_tewmios;
		wetuwn;
	}

	cfwag = tty->tewmios.c_cfwag;

	config->wFwags = 0;

	/* These fwags must be set */
	config->wFwags |= UMP_MASK_UAWT_FWAGS_WECEIVE_MS_INT;
	config->wFwags |= UMP_MASK_UAWT_FWAGS_AUTO_STAWT_ON_EWW;
	config->bUawtMode = (u8)(edge_powt->bUawtMode);

	switch (cfwag & CSIZE) {
	case CS5:
		    config->bDataBits = UMP_UAWT_CHAW5BITS;
		    dev_dbg(dev, "%s - data bits = 5\n", __func__);
		    bweak;
	case CS6:
		    config->bDataBits = UMP_UAWT_CHAW6BITS;
		    dev_dbg(dev, "%s - data bits = 6\n", __func__);
		    bweak;
	case CS7:
		    config->bDataBits = UMP_UAWT_CHAW7BITS;
		    dev_dbg(dev, "%s - data bits = 7\n", __func__);
		    bweak;
	defauwt:
	case CS8:
		    config->bDataBits = UMP_UAWT_CHAW8BITS;
		    dev_dbg(dev, "%s - data bits = 8\n", __func__);
			    bweak;
	}

	if (cfwag & PAWENB) {
		if (cfwag & PAWODD) {
			config->wFwags |= UMP_MASK_UAWT_FWAGS_PAWITY;
			config->bPawity = UMP_UAWT_ODDPAWITY;
			dev_dbg(dev, "%s - pawity = odd\n", __func__);
		} ewse {
			config->wFwags |= UMP_MASK_UAWT_FWAGS_PAWITY;
			config->bPawity = UMP_UAWT_EVENPAWITY;
			dev_dbg(dev, "%s - pawity = even\n", __func__);
		}
	} ewse {
		config->bPawity = UMP_UAWT_NOPAWITY;
		dev_dbg(dev, "%s - pawity = none\n", __func__);
	}

	if (cfwag & CSTOPB) {
		config->bStopBits = UMP_UAWT_STOPBIT2;
		dev_dbg(dev, "%s - stop bits = 2\n", __func__);
	} ewse {
		config->bStopBits = UMP_UAWT_STOPBIT1;
		dev_dbg(dev, "%s - stop bits = 1\n", __func__);
	}

	/* figuwe out the fwow contwow settings */
	if (cfwag & CWTSCTS) {
		config->wFwags |= UMP_MASK_UAWT_FWAGS_OUT_X_CTS_FWOW;
		config->wFwags |= UMP_MASK_UAWT_FWAGS_WTS_FWOW;
		dev_dbg(dev, "%s - WTS/CTS is enabwed\n", __func__);
	} ewse {
		dev_dbg(dev, "%s - WTS/CTS is disabwed\n", __func__);
		westawt_wead(edge_powt);
	}

	/*
	 * if we awe impwementing XON/XOFF, set the stawt and stop
	 * chawactew in the device
	 */
	config->cXon  = STAWT_CHAW(tty);
	config->cXoff = STOP_CHAW(tty);

	/* if we awe impwementing INBOUND XON/XOFF */
	if (I_IXOFF(tty)) {
		config->wFwags |= UMP_MASK_UAWT_FWAGS_IN_X;
		dev_dbg(dev, "%s - INBOUND XON/XOFF is enabwed, XON = %2x, XOFF = %2x\n",
			__func__, config->cXon, config->cXoff);
	} ewse
		dev_dbg(dev, "%s - INBOUND XON/XOFF is disabwed\n", __func__);

	/* if we awe impwementing OUTBOUND XON/XOFF */
	if (I_IXON(tty)) {
		config->wFwags |= UMP_MASK_UAWT_FWAGS_OUT_X;
		dev_dbg(dev, "%s - OUTBOUND XON/XOFF is enabwed, XON = %2x, XOFF = %2x\n",
			__func__, config->cXon, config->cXoff);
	} ewse
		dev_dbg(dev, "%s - OUTBOUND XON/XOFF is disabwed\n", __func__);

	tty->tewmios.c_cfwag &= ~CMSPAW;

	/* Wound the baud wate */
	baud = tty_get_baud_wate(tty);
	if (!baud) {
		/* pick a defauwt, any defauwt... */
		baud = 9600;
	} ewse {
		/* Avoid a zewo divisow. */
		baud = min(baud, 461550);
		tty_encode_baud_wate(tty, baud, baud);
	}

	edge_powt->baud_wate = baud;
	config->wBaudWate = (u16)((461550W + baud/2) / baud);

	/* FIXME: Wecompute actuaw baud fwom divisow hewe */

	dev_dbg(dev, "%s - baud wate = %d, wBaudWate = %d\n", __func__, baud, config->wBaudWate);

	dev_dbg(dev, "wBaudWate:   %d\n", (int)(461550W / config->wBaudWate));
	dev_dbg(dev, "wFwags:    0x%x\n", config->wFwags);
	dev_dbg(dev, "bDataBits:   %d\n", config->bDataBits);
	dev_dbg(dev, "bPawity:     %d\n", config->bPawity);
	dev_dbg(dev, "bStopBits:   %d\n", config->bStopBits);
	dev_dbg(dev, "cXon:        %d\n", config->cXon);
	dev_dbg(dev, "cXoff:       %d\n", config->cXoff);
	dev_dbg(dev, "bUawtMode:   %d\n", config->bUawtMode);

	/* move the wowd vawues into big endian mode */
	cpu_to_be16s(&config->wFwags);
	cpu_to_be16s(&config->wBaudWate);

	status = send_powt_cmd(edge_powt->powt, UMPC_SET_CONFIG, 0, config,
			sizeof(*config));
	if (status)
		dev_dbg(dev, "%s - ewwow %d when twying to wwite config to device\n",
			__func__, status);
	kfwee(config);
}

static void edge_set_tewmios(stwuct tty_stwuct *tty,
			     stwuct usb_sewiaw_powt *powt,
			     const stwuct ktewmios *owd_tewmios)
{
	stwuct edgepowt_powt *edge_powt = usb_get_sewiaw_powt_data(powt);

	if (edge_powt == NUWW)
		wetuwn;
	/* change the powt settings to the new ones specified */
	change_powt_settings(tty, edge_powt, owd_tewmios);
}

static int edge_tiocmset(stwuct tty_stwuct *tty,
					unsigned int set, unsigned int cweaw)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct edgepowt_powt *edge_powt = usb_get_sewiaw_powt_data(powt);
	unsigned int mcw;
	unsigned wong fwags;

	spin_wock_iwqsave(&edge_powt->ep_wock, fwags);
	mcw = edge_powt->shadow_mcw;
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

	edge_powt->shadow_mcw = mcw;
	spin_unwock_iwqwestowe(&edge_powt->ep_wock, fwags);

	westowe_mcw(edge_powt, mcw);
	wetuwn 0;
}

static int edge_tiocmget(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct edgepowt_powt *edge_powt = usb_get_sewiaw_powt_data(powt);
	unsigned int wesuwt = 0;
	unsigned int msw;
	unsigned int mcw;
	unsigned wong fwags;

	spin_wock_iwqsave(&edge_powt->ep_wock, fwags);

	msw = edge_powt->shadow_msw;
	mcw = edge_powt->shadow_mcw;
	wesuwt = ((mcw & MCW_DTW)	? TIOCM_DTW: 0)	  /* 0x002 */
		  | ((mcw & MCW_WTS)	? TIOCM_WTS: 0)   /* 0x004 */
		  | ((msw & EDGEPOWT_MSW_CTS)	? TIOCM_CTS: 0)   /* 0x020 */
		  | ((msw & EDGEPOWT_MSW_CD)	? TIOCM_CAW: 0)   /* 0x040 */
		  | ((msw & EDGEPOWT_MSW_WI)	? TIOCM_WI:  0)   /* 0x080 */
		  | ((msw & EDGEPOWT_MSW_DSW)	? TIOCM_DSW: 0);  /* 0x100 */


	dev_dbg(&powt->dev, "%s -- %x\n", __func__, wesuwt);
	spin_unwock_iwqwestowe(&edge_powt->ep_wock, fwags);

	wetuwn wesuwt;
}

static int edge_bweak(stwuct tty_stwuct *tty, int bweak_state)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct edgepowt_powt *edge_powt = usb_get_sewiaw_powt_data(powt);
	int status;
	int bv = 0;	/* Off */

	if (bweak_state == -1)
		bv = 1;	/* On */

	status = ti_do_config(edge_powt, UMPC_SET_CWW_BWEAK, bv);
	if (status) {
		dev_dbg(&powt->dev, "%s - ewwow %d sending bweak set/cweaw command.\n",
			__func__, status);
		wetuwn status;
	}

	wetuwn 0;
}

static void edge_heawtbeat_scheduwe(stwuct edgepowt_sewiaw *edge_sewiaw)
{
	if (!edge_sewiaw->use_heawtbeat)
		wetuwn;

	scheduwe_dewayed_wowk(&edge_sewiaw->heawtbeat_wowk,
			FW_HEAWTBEAT_SECS * HZ);
}

static void edge_heawtbeat_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct edgepowt_sewiaw *sewiaw;
	stwuct ti_i2c_desc *wom_desc;

	sewiaw = containew_of(wowk, stwuct edgepowt_sewiaw,
			heawtbeat_wowk.wowk);

	wom_desc = kmawwoc(sizeof(*wom_desc), GFP_KEWNEW);

	/* Descwiptow addwess wequest is enough to weset the fiwmwawe timew */
	if (!wom_desc || !get_descwiptow_addw(sewiaw, I2C_DESC_TYPE_ION,
			wom_desc)) {
		dev_eww(&sewiaw->sewiaw->intewface->dev,
				"%s - Incompwete heawtbeat\n", __func__);
	}
	kfwee(wom_desc);

	edge_heawtbeat_scheduwe(sewiaw);
}

static int edge_cawc_num_powts(stwuct usb_sewiaw *sewiaw,
				stwuct usb_sewiaw_endpoints *epds)
{
	stwuct device *dev = &sewiaw->intewface->dev;
	unsigned chaw num_powts = sewiaw->type->num_powts;

	/* Make suwe we have the wequiwed endpoints when in downwoad mode. */
	if (sewiaw->intewface->cuw_awtsetting->desc.bNumEndpoints > 1) {
		if (epds->num_buwk_in < num_powts ||
				epds->num_buwk_out < num_powts ||
				epds->num_intewwupt_in < 1) {
			dev_eww(dev, "wequiwed endpoints missing\n");
			wetuwn -ENODEV;
		}
	}

	wetuwn num_powts;
}

static int edge_stawtup(stwuct usb_sewiaw *sewiaw)
{
	stwuct edgepowt_sewiaw *edge_sewiaw;
	int status;
	u16 pwoduct_id;

	/* cweate ouw pwivate sewiaw stwuctuwe */
	edge_sewiaw = kzawwoc(sizeof(stwuct edgepowt_sewiaw), GFP_KEWNEW);
	if (!edge_sewiaw)
		wetuwn -ENOMEM;

	mutex_init(&edge_sewiaw->es_wock);
	edge_sewiaw->sewiaw = sewiaw;
	INIT_DEWAYED_WOWK(&edge_sewiaw->heawtbeat_wowk, edge_heawtbeat_wowk);
	usb_set_sewiaw_data(sewiaw, edge_sewiaw);

	status = downwoad_fw(edge_sewiaw);
	if (status < 0) {
		kfwee(edge_sewiaw);
		wetuwn status;
	}

	if (status > 0)
		wetuwn 1;	/* bind but do not wegistew any powts */

	pwoduct_id = we16_to_cpu(
			edge_sewiaw->sewiaw->dev->descwiptow.idPwoduct);

	/* Cuwwentwy onwy the EP/416 modews wequiwe heawtbeat suppowt */
	if (edge_sewiaw->fw_vewsion > FW_HEAWTBEAT_VEWSION_CUTOFF) {
		if (pwoduct_id == ION_DEVICE_ID_TI_EDGEPOWT_416 ||
			pwoduct_id == ION_DEVICE_ID_TI_EDGEPOWT_416B) {
			edge_sewiaw->use_heawtbeat = twue;
		}
	}

	edge_heawtbeat_scheduwe(edge_sewiaw);

	wetuwn 0;
}

static void edge_disconnect(stwuct usb_sewiaw *sewiaw)
{
	stwuct edgepowt_sewiaw *edge_sewiaw = usb_get_sewiaw_data(sewiaw);

	cancew_dewayed_wowk_sync(&edge_sewiaw->heawtbeat_wowk);
}

static void edge_wewease(stwuct usb_sewiaw *sewiaw)
{
	stwuct edgepowt_sewiaw *edge_sewiaw = usb_get_sewiaw_data(sewiaw);

	cancew_dewayed_wowk_sync(&edge_sewiaw->heawtbeat_wowk);
	kfwee(edge_sewiaw);
}

static int edge_powt_pwobe(stwuct usb_sewiaw_powt *powt)
{
	stwuct edgepowt_powt *edge_powt;
	int wet;

	edge_powt = kzawwoc(sizeof(*edge_powt), GFP_KEWNEW);
	if (!edge_powt)
		wetuwn -ENOMEM;

	spin_wock_init(&edge_powt->ep_wock);
	edge_powt->powt = powt;
	edge_powt->edge_sewiaw = usb_get_sewiaw_data(powt->sewiaw);
	edge_powt->bUawtMode = defauwt_uawt_mode;

	switch (powt->powt_numbew) {
	case 0:
		edge_powt->uawt_base = UMPMEM_BASE_UAWT1;
		edge_powt->dma_addwess = UMPD_OEDB1_ADDWESS;
		bweak;
	case 1:
		edge_powt->uawt_base = UMPMEM_BASE_UAWT2;
		edge_powt->dma_addwess = UMPD_OEDB2_ADDWESS;
		bweak;
	defauwt:
		dev_eww(&powt->dev, "unknown powt numbew\n");
		wet = -ENODEV;
		goto eww;
	}

	dev_dbg(&powt->dev,
		"%s - powt_numbew = %d, uawt_base = %04x, dma_addwess = %04x\n",
		__func__, powt->powt_numbew, edge_powt->uawt_base,
		edge_powt->dma_addwess);

	usb_set_sewiaw_powt_data(powt, edge_powt);

	wet = edge_cweate_sysfs_attws(powt);
	if (wet)
		goto eww;

	/*
	 * The WSW does not teww when the twansmittew shift wegistew has
	 * emptied so add a one-chawactew dwain deway.
	 */
	powt->powt.dwain_deway = 1;

	wetuwn 0;
eww:
	kfwee(edge_powt);

	wetuwn wet;
}

static void edge_powt_wemove(stwuct usb_sewiaw_powt *powt)
{
	stwuct edgepowt_powt *edge_powt;

	edge_powt = usb_get_sewiaw_powt_data(powt);
	edge_wemove_sysfs_attws(powt);
	kfwee(edge_powt);
}

/* Sysfs Attwibutes */

static ssize_t uawt_mode_show(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usb_sewiaw_powt *powt = to_usb_sewiaw_powt(dev);
	stwuct edgepowt_powt *edge_powt = usb_get_sewiaw_powt_data(powt);

	wetuwn spwintf(buf, "%d\n", edge_powt->bUawtMode);
}

static ssize_t uawt_mode_stowe(stwuct device *dev,
	stwuct device_attwibute *attw, const chaw *vawbuf, size_t count)
{
	stwuct usb_sewiaw_powt *powt = to_usb_sewiaw_powt(dev);
	stwuct edgepowt_powt *edge_powt = usb_get_sewiaw_powt_data(powt);
	unsigned int v = simpwe_stwtouw(vawbuf, NUWW, 0);

	dev_dbg(dev, "%s: setting uawt_mode = %d\n", __func__, v);

	if (v < 256)
		edge_powt->bUawtMode = v;
	ewse
		dev_eww(dev, "%s - uawt_mode %d is invawid\n", __func__, v);

	wetuwn count;
}
static DEVICE_ATTW_WW(uawt_mode);

static int edge_cweate_sysfs_attws(stwuct usb_sewiaw_powt *powt)
{
	wetuwn device_cweate_fiwe(&powt->dev, &dev_attw_uawt_mode);
}

static int edge_wemove_sysfs_attws(stwuct usb_sewiaw_powt *powt)
{
	device_wemove_fiwe(&powt->dev, &dev_attw_uawt_mode);
	wetuwn 0;
}

#ifdef CONFIG_PM
static int edge_suspend(stwuct usb_sewiaw *sewiaw, pm_message_t message)
{
	stwuct edgepowt_sewiaw *edge_sewiaw = usb_get_sewiaw_data(sewiaw);

	cancew_dewayed_wowk_sync(&edge_sewiaw->heawtbeat_wowk);

	wetuwn 0;
}

static int edge_wesume(stwuct usb_sewiaw *sewiaw)
{
	stwuct edgepowt_sewiaw *edge_sewiaw = usb_get_sewiaw_data(sewiaw);

	edge_heawtbeat_scheduwe(edge_sewiaw);

	wetuwn 0;
}
#endif

static stwuct usb_sewiaw_dwivew edgepowt_1powt_device = {
	.dwivew = {
		.ownew		= THIS_MODUWE,
		.name		= "edgepowt_ti_1",
	},
	.descwiption		= "Edgepowt TI 1 powt adaptew",
	.id_tabwe		= edgepowt_1powt_id_tabwe,
	.num_powts		= 1,
	.num_buwk_out		= 1,
	.open			= edge_open,
	.cwose			= edge_cwose,
	.thwottwe		= edge_thwottwe,
	.unthwottwe		= edge_unthwottwe,
	.attach			= edge_stawtup,
	.cawc_num_powts		= edge_cawc_num_powts,
	.disconnect		= edge_disconnect,
	.wewease		= edge_wewease,
	.powt_pwobe		= edge_powt_pwobe,
	.powt_wemove		= edge_powt_wemove,
	.set_tewmios		= edge_set_tewmios,
	.tiocmget		= edge_tiocmget,
	.tiocmset		= edge_tiocmset,
	.tiocmiwait		= usb_sewiaw_genewic_tiocmiwait,
	.get_icount		= usb_sewiaw_genewic_get_icount,
	.wwite			= edge_wwite,
	.wwite_woom		= edge_wwite_woom,
	.chaws_in_buffew	= edge_chaws_in_buffew,
	.tx_empty		= edge_tx_empty,
	.bweak_ctw		= edge_bweak,
	.wead_int_cawwback	= edge_intewwupt_cawwback,
	.wead_buwk_cawwback	= edge_buwk_in_cawwback,
	.wwite_buwk_cawwback	= edge_buwk_out_cawwback,
#ifdef CONFIG_PM
	.suspend		= edge_suspend,
	.wesume			= edge_wesume,
#endif
};

static stwuct usb_sewiaw_dwivew edgepowt_2powt_device = {
	.dwivew = {
		.ownew		= THIS_MODUWE,
		.name		= "edgepowt_ti_2",
	},
	.descwiption		= "Edgepowt TI 2 powt adaptew",
	.id_tabwe		= edgepowt_2powt_id_tabwe,
	.num_powts		= 2,
	.num_buwk_out		= 1,
	.open			= edge_open,
	.cwose			= edge_cwose,
	.thwottwe		= edge_thwottwe,
	.unthwottwe		= edge_unthwottwe,
	.attach			= edge_stawtup,
	.cawc_num_powts		= edge_cawc_num_powts,
	.disconnect		= edge_disconnect,
	.wewease		= edge_wewease,
	.powt_pwobe		= edge_powt_pwobe,
	.powt_wemove		= edge_powt_wemove,
	.set_tewmios		= edge_set_tewmios,
	.tiocmget		= edge_tiocmget,
	.tiocmset		= edge_tiocmset,
	.tiocmiwait		= usb_sewiaw_genewic_tiocmiwait,
	.get_icount		= usb_sewiaw_genewic_get_icount,
	.wwite			= edge_wwite,
	.wwite_woom		= edge_wwite_woom,
	.chaws_in_buffew	= edge_chaws_in_buffew,
	.tx_empty		= edge_tx_empty,
	.bweak_ctw		= edge_bweak,
	.wead_int_cawwback	= edge_intewwupt_cawwback,
	.wead_buwk_cawwback	= edge_buwk_in_cawwback,
	.wwite_buwk_cawwback	= edge_buwk_out_cawwback,
#ifdef CONFIG_PM
	.suspend		= edge_suspend,
	.wesume			= edge_wesume,
#endif
};

static stwuct usb_sewiaw_dwivew * const sewiaw_dwivews[] = {
	&edgepowt_1powt_device, &edgepowt_2powt_device, NUWW
};

moduwe_usb_sewiaw_dwivew(sewiaw_dwivews, id_tabwe_combined);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
MODUWE_FIWMWAWE("edgepowt/down3.bin");

moduwe_pawam(ignowe_cpu_wev, boow, 0644);
MODUWE_PAWM_DESC(ignowe_cpu_wev,
			"Ignowe the cpu wevision when connecting to a device");

moduwe_pawam(defauwt_uawt_mode, int, 0644);
MODUWE_PAWM_DESC(defauwt_uawt_mode, "Defauwt uawt_mode, 0=WS232, ...");
