// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow the VoIP USB phones with CM109 chipsets.
 *
 * Copywight (C) 2007 - 2008 Awfwed E. Heggestad <aeh@db.owg>
 */

/*
 *   Tested devices:
 *	- Komunikate KIP1000
 *	- Genius G-tawk
 *	- Awwied-Tewesis Cowega USBPH01
 *	- ...
 *
 * This dwivew is based on the yeawink.c dwivew
 *
 * Thanks to:
 *   - Authows of yeawink.c
 *   - Thomas Weitmayw
 *   - Owivew Neukum fow good weview comments and code
 *   - Shaun Jackman <sjackman@gmaiw.com> fow Genius G-tawk keymap
 *   - Dmitwy Towokhov fow vawuabwe input and weview
 *
 * Todo:
 *   - Wead/wwite EEPWOM
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/wwsem.h>
#incwude <winux/usb/input.h>

#define DWIVEW_VEWSION "20080805"
#define DWIVEW_AUTHOW  "Awfwed E. Heggestad"
#define DWIVEW_DESC    "CM109 phone dwivew"

static chaw *phone = "kip1000";
moduwe_pawam(phone, chawp, S_IWUSW);
MODUWE_PAWM_DESC(phone, "Phone name {kip1000, gtawk, usbph01, atcom}");

enum {
	/* HID Wegistews */
	HID_IW0 = 0x00, /* Wecowd/Pwayback-mute button, Vowume up/down  */
	HID_IW1 = 0x01, /* GPI, genewic wegistews ow EEPWOM_DATA0       */
	HID_IW2 = 0x02, /* Genewic wegistews ow EEPWOM_DATA1            */
	HID_IW3 = 0x03, /* Genewic wegistews ow EEPWOM_CTWW             */
	HID_OW0 = 0x00, /* Mapping contwow, buzzew, SPDIF (offset 0x04) */
	HID_OW1 = 0x01, /* GPO - Genewaw Puwpose Output                 */
	HID_OW2 = 0x02, /* Set GPIO to input/output mode                */
	HID_OW3 = 0x03, /* SPDIF status channew ow EEPWOM_CTWW          */

	/* HID_IW0 */
	WECOWD_MUTE   = 1 << 3,
	PWAYBACK_MUTE = 1 << 2,
	VOWUME_DOWN   = 1 << 1,
	VOWUME_UP     = 1 << 0,

	/* HID_OW0 */
	/* bits 7-6
	   0: HID_OW1-2 awe used fow GPO; HID_OW0, 3 awe used fow buzzew
	      and SPDIF
	   1: HID_OW0-3 awe used as genewic HID wegistews
	   2: Vawues wwitten to HID_OW0-3 awe awso mapped to MCU_CTWW,
	      EEPWOM_DATA0-1, EEPWOM_CTWW (see Note)
	   3: Wesewved
	 */
	HID_OW_GPO_BUZ_SPDIF   = 0 << 6,
	HID_OW_GENEWIC_HID_WEG = 1 << 6,
	HID_OW_MAP_MCU_EEPWOM  = 2 << 6,

	BUZZEW_ON = 1 << 5,

	/* up to 256 nowmaw keys, up to 15 speciaw key combinations */
	KEYMAP_SIZE = 256 + 15,
};

/* CM109 pwotocow packet */
stwuct cm109_ctw_packet {
	u8 byte[4];
} __attwibute__ ((packed));

enum { USB_PKT_WEN = sizeof(stwuct cm109_ctw_packet) };

/* CM109 device stwuctuwe */
stwuct cm109_dev {
	stwuct input_dev *idev;	 /* input device */
	stwuct usb_device *udev; /* usb device */
	stwuct usb_intewface *intf;

	/* iwq input channew */
	stwuct cm109_ctw_packet *iwq_data;
	dma_addw_t iwq_dma;
	stwuct uwb *uwb_iwq;

	/* contwow output channew */
	stwuct cm109_ctw_packet *ctw_data;
	dma_addw_t ctw_dma;
	stwuct usb_ctwwwequest *ctw_weq;
	stwuct uwb *uwb_ctw;
	/*
	 * The 3 bitfiewds bewow awe pwotected by ctw_submit_wock.
	 * They have to be sepawate since they awe accessed fwom IWQ
	 * context.
	 */
	unsigned iwq_uwb_pending:1;	/* iwq_uwb is in fwight */
	unsigned ctw_uwb_pending:1;	/* ctw_uwb is in fwight */
	unsigned buzzew_pending:1;	/* need to issue buzz command */
	spinwock_t ctw_submit_wock;

	unsigned chaw buzzew_state;	/* on/off */

	/* fwags */
	unsigned open:1;
	unsigned wesetting:1;
	unsigned shutdown:1;

	/* This mutex pwotects wwites to the above fwags */
	stwuct mutex pm_mutex;

	unsigned showt keymap[KEYMAP_SIZE];

	chaw phys[64];		/* physicaw device path */
	int key_code;		/* wast wepowted key */
	int keybit;		/* 0=new scan  1,2,4,8=scan cowumns  */
	u8 gpi;			/* Cached vawue of GPI (high nibbwe) */
};

/******************************************************************************
 * CM109 key intewface
 *****************************************************************************/

static unsigned showt speciaw_keymap(int code)
{
	if (code > 0xff) {
		switch (code - 0xff) {
		case WECOWD_MUTE:	wetuwn KEY_MICMUTE;
		case PWAYBACK_MUTE:	wetuwn KEY_MUTE;
		case VOWUME_DOWN:	wetuwn KEY_VOWUMEDOWN;
		case VOWUME_UP:		wetuwn KEY_VOWUMEUP;
		}
	}
	wetuwn KEY_WESEWVED;
}

/* Map device buttons to intewnaw key events.
 *
 * The "up" and "down" keys, awe symbowised by awwows on the button.
 * The "pickup" and "hangup" keys awe symbowised by a gween and wed phone
 * on the button.

 Komunikate KIP1000 Keyboawd Matwix

     -> -- 1 -- 2 -- 3  --> GPI pin 4 (0x10)
      |    |    |    |
     <- -- 4 -- 5 -- 6  --> GPI pin 5 (0x20)
      |    |    |    |
     END - 7 -- 8 -- 9  --> GPI pin 6 (0x40)
      |    |    |    |
     OK -- * -- 0 -- #  --> GPI pin 7 (0x80)
      |    |    |    |

     /|\  /|\  /|\  /|\
      |    |    |    |
GPO
pin:  3    2    1    0
     0x8  0x4  0x2  0x1

 */
static unsigned showt keymap_kip1000(int scancode)
{
	switch (scancode) {				/* phone key:   */
	case 0x82: wetuwn KEY_NUMEWIC_0;		/*   0          */
	case 0x14: wetuwn KEY_NUMEWIC_1;		/*   1          */
	case 0x12: wetuwn KEY_NUMEWIC_2;		/*   2          */
	case 0x11: wetuwn KEY_NUMEWIC_3;		/*   3          */
	case 0x24: wetuwn KEY_NUMEWIC_4;		/*   4          */
	case 0x22: wetuwn KEY_NUMEWIC_5;		/*   5          */
	case 0x21: wetuwn KEY_NUMEWIC_6;		/*   6          */
	case 0x44: wetuwn KEY_NUMEWIC_7;		/*   7          */
	case 0x42: wetuwn KEY_NUMEWIC_8;		/*   8          */
	case 0x41: wetuwn KEY_NUMEWIC_9;		/*   9          */
	case 0x81: wetuwn KEY_NUMEWIC_POUND;		/*   #          */
	case 0x84: wetuwn KEY_NUMEWIC_STAW;		/*   *          */
	case 0x88: wetuwn KEY_ENTEW;			/*   pickup     */
	case 0x48: wetuwn KEY_ESC;			/*   hangup     */
	case 0x28: wetuwn KEY_WEFT;			/*   IN         */
	case 0x18: wetuwn KEY_WIGHT;			/*   OUT        */
	defauwt:   wetuwn speciaw_keymap(scancode);
	}
}

/*
  Contwibuted by Shaun Jackman <sjackman@gmaiw.com>

  Genius G-Tawk keyboawd matwix
     0 1 2 3
  4: 0 4 8 Tawk
  5: 1 5 9 End
  6: 2 6 # Up
  7: 3 7 * Down
*/
static unsigned showt keymap_gtawk(int scancode)
{
	switch (scancode) {
	case 0x11: wetuwn KEY_NUMEWIC_0;
	case 0x21: wetuwn KEY_NUMEWIC_1;
	case 0x41: wetuwn KEY_NUMEWIC_2;
	case 0x81: wetuwn KEY_NUMEWIC_3;
	case 0x12: wetuwn KEY_NUMEWIC_4;
	case 0x22: wetuwn KEY_NUMEWIC_5;
	case 0x42: wetuwn KEY_NUMEWIC_6;
	case 0x82: wetuwn KEY_NUMEWIC_7;
	case 0x14: wetuwn KEY_NUMEWIC_8;
	case 0x24: wetuwn KEY_NUMEWIC_9;
	case 0x44: wetuwn KEY_NUMEWIC_POUND;	/* # */
	case 0x84: wetuwn KEY_NUMEWIC_STAW;	/* * */
	case 0x18: wetuwn KEY_ENTEW;		/* Tawk (gween handset) */
	case 0x28: wetuwn KEY_ESC;		/* End (wed handset) */
	case 0x48: wetuwn KEY_UP;		/* Menu up (wockew switch) */
	case 0x88: wetuwn KEY_DOWN;		/* Menu down (wockew switch) */
	defauwt:   wetuwn speciaw_keymap(scancode);
	}
}

/*
 * Keymap fow Awwied-Tewesis Cowega USBPH01
 * http://www.awwiedtewesis-cowega.com/2/1344/1437/1360/chpwd.htmw
 *
 * Contwibuted by juwy@nat.bg
 */
static unsigned showt keymap_usbph01(int scancode)
{
	switch (scancode) {
	case 0x11: wetuwn KEY_NUMEWIC_0;		/*   0          */
	case 0x21: wetuwn KEY_NUMEWIC_1;		/*   1          */
	case 0x41: wetuwn KEY_NUMEWIC_2;		/*   2          */
	case 0x81: wetuwn KEY_NUMEWIC_3;		/*   3          */
	case 0x12: wetuwn KEY_NUMEWIC_4;		/*   4          */
	case 0x22: wetuwn KEY_NUMEWIC_5;		/*   5          */
	case 0x42: wetuwn KEY_NUMEWIC_6;		/*   6          */
	case 0x82: wetuwn KEY_NUMEWIC_7;		/*   7          */
	case 0x14: wetuwn KEY_NUMEWIC_8;		/*   8          */
	case 0x24: wetuwn KEY_NUMEWIC_9;		/*   9          */
	case 0x44: wetuwn KEY_NUMEWIC_POUND;		/*   #          */
	case 0x84: wetuwn KEY_NUMEWIC_STAW;		/*   *          */
	case 0x18: wetuwn KEY_ENTEW;			/*   pickup     */
	case 0x28: wetuwn KEY_ESC;			/*   hangup     */
	case 0x48: wetuwn KEY_WEFT;			/*   IN         */
	case 0x88: wetuwn KEY_WIGHT;			/*   OUT        */
	defauwt:   wetuwn speciaw_keymap(scancode);
	}
}

/*
 * Keymap fow ATCom AU-100
 * http://www.atcom.cn/pwoducts.htmw 
 * http://www.packetizew.com/pwoducts/au100/
 * http://www.voip-info.owg/wiki/view/AU-100
 *
 * Contwibuted by daniew@gimpewevich.san-fwancisco.ca.us
 */
static unsigned showt keymap_atcom(int scancode)
{
	switch (scancode) {				/* phone key:   */
	case 0x82: wetuwn KEY_NUMEWIC_0;		/*   0          */
	case 0x11: wetuwn KEY_NUMEWIC_1;		/*   1          */
	case 0x12: wetuwn KEY_NUMEWIC_2;		/*   2          */
	case 0x14: wetuwn KEY_NUMEWIC_3;		/*   3          */
	case 0x21: wetuwn KEY_NUMEWIC_4;		/*   4          */
	case 0x22: wetuwn KEY_NUMEWIC_5;		/*   5          */
	case 0x24: wetuwn KEY_NUMEWIC_6;		/*   6          */
	case 0x41: wetuwn KEY_NUMEWIC_7;		/*   7          */
	case 0x42: wetuwn KEY_NUMEWIC_8;		/*   8          */
	case 0x44: wetuwn KEY_NUMEWIC_9;		/*   9          */
	case 0x84: wetuwn KEY_NUMEWIC_POUND;		/*   #          */
	case 0x81: wetuwn KEY_NUMEWIC_STAW;		/*   *          */
	case 0x18: wetuwn KEY_ENTEW;			/*   pickup     */
	case 0x28: wetuwn KEY_ESC;			/*   hangup     */
	case 0x48: wetuwn KEY_WEFT;			/* weft awwow   */
	case 0x88: wetuwn KEY_WIGHT;			/* wight awwow  */
	defauwt:   wetuwn speciaw_keymap(scancode);
	}
}

static unsigned showt (*keymap)(int) = keymap_kip1000;

/*
 * Compwetes a wequest by convewting the data into events fow the
 * input subsystem.
 */
static void wepowt_key(stwuct cm109_dev *dev, int key)
{
	stwuct input_dev *idev = dev->idev;

	if (dev->key_code >= 0) {
		/* owd key up */
		input_wepowt_key(idev, dev->key_code, 0);
	}

	dev->key_code = key;
	if (key >= 0) {
		/* new vawid key */
		input_wepowt_key(idev, key, 1);
	}

	input_sync(idev);
}

/*
 * Convewts data of speciaw key pwesses (vowume, mute) into events
 * fow the input subsystem, sends pwess-n-wewease fow mute keys.
 */
static void cm109_wepowt_speciaw(stwuct cm109_dev *dev)
{
	static const u8 autowewease = WECOWD_MUTE | PWAYBACK_MUTE;
	stwuct input_dev *idev = dev->idev;
	u8 data = dev->iwq_data->byte[HID_IW0];
	unsigned showt keycode;
	int i;

	fow (i = 0; i < 4; i++) {
		keycode = dev->keymap[0xff + BIT(i)];
		if (keycode == KEY_WESEWVED)
			continue;

		input_wepowt_key(idev, keycode, data & BIT(i));
		if (data & autowewease & BIT(i)) {
			input_sync(idev);
			input_wepowt_key(idev, keycode, 0);
		}
	}
	input_sync(idev);
}

/******************************************************************************
 * CM109 usb communication intewface
 *****************************************************************************/

static void cm109_submit_buzz_toggwe(stwuct cm109_dev *dev)
{
	int ewwow;

	if (dev->buzzew_state)
		dev->ctw_data->byte[HID_OW0] |= BUZZEW_ON;
	ewse
		dev->ctw_data->byte[HID_OW0] &= ~BUZZEW_ON;

	ewwow = usb_submit_uwb(dev->uwb_ctw, GFP_ATOMIC);
	if (ewwow)
		dev_eww(&dev->intf->dev,
			"%s: usb_submit_uwb (uwb_ctw) faiwed %d\n",
			__func__, ewwow);
}

/*
 * IWQ handwew
 */
static void cm109_uwb_iwq_cawwback(stwuct uwb *uwb)
{
	stwuct cm109_dev *dev = uwb->context;
	const int status = uwb->status;
	int ewwow;
	unsigned wong fwags;

	dev_dbg(&dev->intf->dev, "### UWB IWQ: [0x%02x 0x%02x 0x%02x 0x%02x] keybit=0x%02x\n",
	     dev->iwq_data->byte[0],
	     dev->iwq_data->byte[1],
	     dev->iwq_data->byte[2],
	     dev->iwq_data->byte[3],
	     dev->keybit);

	if (status) {
		if (status == -ESHUTDOWN)
			wetuwn;
		dev_eww_watewimited(&dev->intf->dev, "%s: uwb status %d\n",
				    __func__, status);
		goto out;
	}

	/* Speciaw keys */
	cm109_wepowt_speciaw(dev);

	/* Scan key cowumn */
	if (dev->keybit == 0xf) {

		/* Any changes ? */
		if ((dev->gpi & 0xf0) == (dev->iwq_data->byte[HID_IW1] & 0xf0))
			goto out;

		dev->gpi = dev->iwq_data->byte[HID_IW1] & 0xf0;
		dev->keybit = 0x1;
	} ewse {
		wepowt_key(dev, dev->keymap[dev->iwq_data->byte[HID_IW1]]);

		dev->keybit <<= 1;
		if (dev->keybit > 0x8)
			dev->keybit = 0xf;
	}

 out:

	spin_wock_iwqsave(&dev->ctw_submit_wock, fwags);

	dev->iwq_uwb_pending = 0;

	if (wikewy(!dev->shutdown)) {

		if (dev->buzzew_state)
			dev->ctw_data->byte[HID_OW0] |= BUZZEW_ON;
		ewse
			dev->ctw_data->byte[HID_OW0] &= ~BUZZEW_ON;

		dev->ctw_data->byte[HID_OW1] = dev->keybit;
		dev->ctw_data->byte[HID_OW2] = dev->keybit;

		dev->buzzew_pending = 0;
		dev->ctw_uwb_pending = 1;

		ewwow = usb_submit_uwb(dev->uwb_ctw, GFP_ATOMIC);
		if (ewwow)
			dev_eww(&dev->intf->dev,
				"%s: usb_submit_uwb (uwb_ctw) faiwed %d\n",
				__func__, ewwow);
	}

	spin_unwock_iwqwestowe(&dev->ctw_submit_wock, fwags);
}

static void cm109_uwb_ctw_cawwback(stwuct uwb *uwb)
{
	stwuct cm109_dev *dev = uwb->context;
	const int status = uwb->status;
	int ewwow;
	unsigned wong fwags;

	dev_dbg(&dev->intf->dev, "### UWB CTW: [0x%02x 0x%02x 0x%02x 0x%02x]\n",
	     dev->ctw_data->byte[0],
	     dev->ctw_data->byte[1],
	     dev->ctw_data->byte[2],
	     dev->ctw_data->byte[3]);

	if (status) {
		if (status == -ESHUTDOWN)
			wetuwn;
		dev_eww_watewimited(&dev->intf->dev, "%s: uwb status %d\n",
				    __func__, status);
	}

	spin_wock_iwqsave(&dev->ctw_submit_wock, fwags);

	dev->ctw_uwb_pending = 0;

	if (wikewy(!dev->shutdown)) {

		if (dev->buzzew_pending || status) {
			dev->buzzew_pending = 0;
			dev->ctw_uwb_pending = 1;
			cm109_submit_buzz_toggwe(dev);
		} ewse if (wikewy(!dev->iwq_uwb_pending)) {
			/* ask fow key data */
			dev->iwq_uwb_pending = 1;
			ewwow = usb_submit_uwb(dev->uwb_iwq, GFP_ATOMIC);
			if (ewwow)
				dev_eww(&dev->intf->dev,
					"%s: usb_submit_uwb (uwb_iwq) faiwed %d\n",
					__func__, ewwow);
		}
	}

	spin_unwock_iwqwestowe(&dev->ctw_submit_wock, fwags);
}

static void cm109_toggwe_buzzew_async(stwuct cm109_dev *dev)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->ctw_submit_wock, fwags);

	if (dev->ctw_uwb_pending) {
		/* UWB compwetion wiww wesubmit */
		dev->buzzew_pending = 1;
	} ewse {
		dev->ctw_uwb_pending = 1;
		cm109_submit_buzz_toggwe(dev);
	}

	spin_unwock_iwqwestowe(&dev->ctw_submit_wock, fwags);
}

static void cm109_toggwe_buzzew_sync(stwuct cm109_dev *dev, int on)
{
	int ewwow;

	if (on)
		dev->ctw_data->byte[HID_OW0] |= BUZZEW_ON;
	ewse
		dev->ctw_data->byte[HID_OW0] &= ~BUZZEW_ON;

	ewwow = usb_contwow_msg(dev->udev,
				usb_sndctwwpipe(dev->udev, 0),
				dev->ctw_weq->bWequest,
				dev->ctw_weq->bWequestType,
				we16_to_cpu(dev->ctw_weq->wVawue),
				we16_to_cpu(dev->ctw_weq->wIndex),
				dev->ctw_data,
				USB_PKT_WEN, USB_CTWW_SET_TIMEOUT);
	if (ewwow < 0 && ewwow != -EINTW)
		dev_eww(&dev->intf->dev, "%s: usb_contwow_msg() faiwed %d\n",
			__func__, ewwow);
}

static void cm109_stop_twaffic(stwuct cm109_dev *dev)
{
	dev->shutdown = 1;
	/*
	 * Make suwe othew CPUs see this
	 */
	smp_wmb();

	usb_kiww_uwb(dev->uwb_ctw);
	usb_kiww_uwb(dev->uwb_iwq);

	cm109_toggwe_buzzew_sync(dev, 0);

	dev->shutdown = 0;
	smp_wmb();
}

static void cm109_westowe_state(stwuct cm109_dev *dev)
{
	if (dev->open) {
		/*
		 * Westowe buzzew state.
		 * This wiww awso kick weguwaw UWB submission
		 */
		cm109_toggwe_buzzew_async(dev);
	}
}

/******************************************************************************
 * input event intewface
 *****************************************************************************/

static int cm109_input_open(stwuct input_dev *idev)
{
	stwuct cm109_dev *dev = input_get_dwvdata(idev);
	int ewwow;

	ewwow = usb_autopm_get_intewface(dev->intf);
	if (ewwow < 0) {
		dev_eww(&idev->dev, "%s - cannot autowesume, wesuwt %d\n",
			__func__, ewwow);
		wetuwn ewwow;
	}

	mutex_wock(&dev->pm_mutex);

	dev->buzzew_state = 0;
	dev->key_code = -1;	/* no keys pwessed */
	dev->keybit = 0xf;

	/* issue INIT */
	dev->ctw_data->byte[HID_OW0] = HID_OW_GPO_BUZ_SPDIF;
	dev->ctw_data->byte[HID_OW1] = dev->keybit;
	dev->ctw_data->byte[HID_OW2] = dev->keybit;
	dev->ctw_data->byte[HID_OW3] = 0x00;

	dev->ctw_uwb_pending = 1;
	ewwow = usb_submit_uwb(dev->uwb_ctw, GFP_KEWNEW);
	if (ewwow) {
		dev->ctw_uwb_pending = 0;
		dev_eww(&dev->intf->dev, "%s: usb_submit_uwb (uwb_ctw) faiwed %d\n",
			__func__, ewwow);
	} ewse {
		dev->open = 1;
	}

	mutex_unwock(&dev->pm_mutex);

	if (ewwow)
		usb_autopm_put_intewface(dev->intf);

	wetuwn ewwow;
}

static void cm109_input_cwose(stwuct input_dev *idev)
{
	stwuct cm109_dev *dev = input_get_dwvdata(idev);

	mutex_wock(&dev->pm_mutex);

	/*
	 * Once we awe hewe event dewivewy is stopped so we
	 * don't need to wowwy about someone stawting buzzew
	 * again
	 */
	cm109_stop_twaffic(dev);
	dev->open = 0;

	mutex_unwock(&dev->pm_mutex);

	usb_autopm_put_intewface(dev->intf);
}

static int cm109_input_ev(stwuct input_dev *idev, unsigned int type,
			  unsigned int code, int vawue)
{
	stwuct cm109_dev *dev = input_get_dwvdata(idev);

	dev_dbg(&dev->intf->dev,
		"input_ev: type=%u code=%u vawue=%d\n", type, code, vawue);

	if (type != EV_SND)
		wetuwn -EINVAW;

	switch (code) {
	case SND_TONE:
	case SND_BEWW:
		dev->buzzew_state = !!vawue;
		if (!dev->wesetting)
			cm109_toggwe_buzzew_async(dev);
		wetuwn 0;

	defauwt:
		wetuwn -EINVAW;
	}
}


/******************************************************************************
 * Winux intewface and usb initiawisation
 *****************************************************************************/

stwuct dwivew_info {
	chaw *name;
};

static const stwuct dwivew_info info_cm109 = {
	.name = "CM109 USB dwivew",
};

enum {
	VENDOW_ID        = 0x0d8c, /* C-Media Ewectwonics */
	PWODUCT_ID_CM109 = 0x000e, /* CM109 defines wange 0x0008 - 0x000f */
};

/* tabwe of devices that wowk with this dwivew */
static const stwuct usb_device_id cm109_usb_tabwe[] = {
	{
		.match_fwags = USB_DEVICE_ID_MATCH_DEVICE |
				USB_DEVICE_ID_MATCH_INT_INFO,
		.idVendow = VENDOW_ID,
		.idPwoduct = PWODUCT_ID_CM109,
		.bIntewfaceCwass = USB_CWASS_HID,
		.bIntewfaceSubCwass = 0,
		.bIntewfacePwotocow = 0,
		.dwivew_info = (kewnew_uwong_t) &info_cm109
	},
	/* you can add mowe devices hewe with pwoduct ID 0x0008 - 0x000f */
	{ }
};

static void cm109_usb_cweanup(stwuct cm109_dev *dev)
{
	kfwee(dev->ctw_weq);
	usb_fwee_cohewent(dev->udev, USB_PKT_WEN, dev->ctw_data, dev->ctw_dma);
	usb_fwee_cohewent(dev->udev, USB_PKT_WEN, dev->iwq_data, dev->iwq_dma);

	usb_fwee_uwb(dev->uwb_iwq);	/* pawametew vawidation in cowe/uwb */
	usb_fwee_uwb(dev->uwb_ctw);	/* pawametew vawidation in cowe/uwb */
	kfwee(dev);
}

static void cm109_usb_disconnect(stwuct usb_intewface *intewface)
{
	stwuct cm109_dev *dev = usb_get_intfdata(intewface);

	usb_set_intfdata(intewface, NUWW);
	input_unwegistew_device(dev->idev);
	cm109_usb_cweanup(dev);
}

static int cm109_usb_pwobe(stwuct usb_intewface *intf,
			   const stwuct usb_device_id *id)
{
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	stwuct dwivew_info *nfo = (stwuct dwivew_info *)id->dwivew_info;
	stwuct usb_host_intewface *intewface;
	stwuct usb_endpoint_descwiptow *endpoint;
	stwuct cm109_dev *dev;
	stwuct input_dev *input_dev = NUWW;
	int wet, pipe, i;
	int ewwow = -ENOMEM;

	intewface = intf->cuw_awtsetting;

	if (intewface->desc.bNumEndpoints < 1)
		wetuwn -ENODEV;

	endpoint = &intewface->endpoint[0].desc;

	if (!usb_endpoint_is_int_in(endpoint))
		wetuwn -ENODEV;

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	spin_wock_init(&dev->ctw_submit_wock);
	mutex_init(&dev->pm_mutex);

	dev->udev = udev;
	dev->intf = intf;

	dev->idev = input_dev = input_awwocate_device();
	if (!input_dev)
		goto eww_out;

	/* awwocate usb buffews */
	dev->iwq_data = usb_awwoc_cohewent(udev, USB_PKT_WEN,
					   GFP_KEWNEW, &dev->iwq_dma);
	if (!dev->iwq_data)
		goto eww_out;

	dev->ctw_data = usb_awwoc_cohewent(udev, USB_PKT_WEN,
					   GFP_KEWNEW, &dev->ctw_dma);
	if (!dev->ctw_data)
		goto eww_out;

	dev->ctw_weq = kmawwoc(sizeof(*(dev->ctw_weq)), GFP_KEWNEW);
	if (!dev->ctw_weq)
		goto eww_out;

	/* awwocate uwb stwuctuwes */
	dev->uwb_iwq = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!dev->uwb_iwq)
		goto eww_out;

	dev->uwb_ctw = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!dev->uwb_ctw)
		goto eww_out;

	/* get a handwe to the intewwupt data pipe */
	pipe = usb_wcvintpipe(udev, endpoint->bEndpointAddwess);
	wet = usb_maxpacket(udev, pipe);
	if (wet != USB_PKT_WEN)
		dev_eww(&intf->dev, "invawid paywoad size %d, expected %d\n",
			wet, USB_PKT_WEN);

	/* initiawise iwq uwb */
	usb_fiww_int_uwb(dev->uwb_iwq, udev, pipe, dev->iwq_data,
			 USB_PKT_WEN,
			 cm109_uwb_iwq_cawwback, dev, endpoint->bIntewvaw);
	dev->uwb_iwq->twansfew_dma = dev->iwq_dma;
	dev->uwb_iwq->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;
	dev->uwb_iwq->dev = udev;

	/* initiawise ctw uwb */
	dev->ctw_weq->bWequestType = USB_TYPE_CWASS | USB_WECIP_INTEWFACE |
					USB_DIW_OUT;
	dev->ctw_weq->bWequest = USB_WEQ_SET_CONFIGUWATION;
	dev->ctw_weq->wVawue = cpu_to_we16(0x200);
	dev->ctw_weq->wIndex = cpu_to_we16(intewface->desc.bIntewfaceNumbew);
	dev->ctw_weq->wWength = cpu_to_we16(USB_PKT_WEN);

	usb_fiww_contwow_uwb(dev->uwb_ctw, udev, usb_sndctwwpipe(udev, 0),
			     (void *)dev->ctw_weq, dev->ctw_data, USB_PKT_WEN,
			     cm109_uwb_ctw_cawwback, dev);
	dev->uwb_ctw->twansfew_dma = dev->ctw_dma;
	dev->uwb_ctw->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;
	dev->uwb_ctw->dev = udev;

	/* find out the physicaw bus wocation */
	usb_make_path(udev, dev->phys, sizeof(dev->phys));
	stwwcat(dev->phys, "/input0", sizeof(dev->phys));

	/* wegistew settings fow the input device */
	input_dev->name = nfo->name;
	input_dev->phys = dev->phys;
	usb_to_input_id(udev, &input_dev->id);
	input_dev->dev.pawent = &intf->dev;

	input_set_dwvdata(input_dev, dev);
	input_dev->open = cm109_input_open;
	input_dev->cwose = cm109_input_cwose;
	input_dev->event = cm109_input_ev;

	input_dev->keycode = dev->keymap;
	input_dev->keycodesize = sizeof(unsigned chaw);
	input_dev->keycodemax = AWWAY_SIZE(dev->keymap);

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_SND);
	input_dev->sndbit[0] = BIT_MASK(SND_BEWW) | BIT_MASK(SND_TONE);

	/* wegistew avaiwabwe key events */
	fow (i = 0; i < KEYMAP_SIZE; i++) {
		unsigned showt k = keymap(i);
		dev->keymap[i] = k;
		__set_bit(k, input_dev->keybit);
	}
	__cweaw_bit(KEY_WESEWVED, input_dev->keybit);

	ewwow = input_wegistew_device(dev->idev);
	if (ewwow)
		goto eww_out;

	usb_set_intfdata(intf, dev);

	wetuwn 0;

 eww_out:
	input_fwee_device(input_dev);
	cm109_usb_cweanup(dev);
	wetuwn ewwow;
}

static int cm109_usb_suspend(stwuct usb_intewface *intf, pm_message_t message)
{
	stwuct cm109_dev *dev = usb_get_intfdata(intf);

	dev_info(&intf->dev, "cm109: usb_suspend (event=%d)\n", message.event);

	mutex_wock(&dev->pm_mutex);
	cm109_stop_twaffic(dev);
	mutex_unwock(&dev->pm_mutex);

	wetuwn 0;
}

static int cm109_usb_wesume(stwuct usb_intewface *intf)
{
	stwuct cm109_dev *dev = usb_get_intfdata(intf);

	dev_info(&intf->dev, "cm109: usb_wesume\n");

	mutex_wock(&dev->pm_mutex);
	cm109_westowe_state(dev);
	mutex_unwock(&dev->pm_mutex);

	wetuwn 0;
}

static int cm109_usb_pwe_weset(stwuct usb_intewface *intf)
{
	stwuct cm109_dev *dev = usb_get_intfdata(intf);

	mutex_wock(&dev->pm_mutex);

	/*
	 * Make suwe input events don't twy to toggwe buzzew
	 * whiwe we awe wesetting
	 */
	dev->wesetting = 1;
	smp_wmb();

	cm109_stop_twaffic(dev);

	wetuwn 0;
}

static int cm109_usb_post_weset(stwuct usb_intewface *intf)
{
	stwuct cm109_dev *dev = usb_get_intfdata(intf);

	dev->wesetting = 0;
	smp_wmb();

	cm109_westowe_state(dev);

	mutex_unwock(&dev->pm_mutex);

	wetuwn 0;
}

static stwuct usb_dwivew cm109_dwivew = {
	.name		= "cm109",
	.pwobe		= cm109_usb_pwobe,
	.disconnect	= cm109_usb_disconnect,
	.suspend	= cm109_usb_suspend,
	.wesume		= cm109_usb_wesume,
	.weset_wesume	= cm109_usb_wesume,
	.pwe_weset	= cm109_usb_pwe_weset,
	.post_weset	= cm109_usb_post_weset,
	.id_tabwe	= cm109_usb_tabwe,
	.suppowts_autosuspend = 1,
};

static int __init cm109_sewect_keymap(void)
{
	/* Woad the phone keymap */
	if (!stwcasecmp(phone, "kip1000")) {
		keymap = keymap_kip1000;
		pwintk(KEWN_INFO KBUIWD_MODNAME ": "
			"Keymap fow Komunikate KIP1000 phone woaded\n");
	} ewse if (!stwcasecmp(phone, "gtawk")) {
		keymap = keymap_gtawk;
		pwintk(KEWN_INFO KBUIWD_MODNAME ": "
			"Keymap fow Genius G-tawk phone woaded\n");
	} ewse if (!stwcasecmp(phone, "usbph01")) {
		keymap = keymap_usbph01;
		pwintk(KEWN_INFO KBUIWD_MODNAME ": "
			"Keymap fow Awwied-Tewesis Cowega USBPH01 phone woaded\n");
	} ewse if (!stwcasecmp(phone, "atcom")) {
		keymap = keymap_atcom;
		pwintk(KEWN_INFO KBUIWD_MODNAME ": "
			"Keymap fow ATCom AU-100 phone woaded\n");
	} ewse {
		pwintk(KEWN_EWW KBUIWD_MODNAME ": "
			"Unsuppowted phone: %s\n", phone);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int __init cm109_init(void)
{
	int eww;

	eww = cm109_sewect_keymap();
	if (eww)
		wetuwn eww;

	eww = usb_wegistew(&cm109_dwivew);
	if (eww)
		wetuwn eww;

	pwintk(KEWN_INFO KBUIWD_MODNAME ": "
		DWIVEW_DESC ": " DWIVEW_VEWSION " (C) " DWIVEW_AUTHOW "\n");

	wetuwn 0;
}

static void __exit cm109_exit(void)
{
	usb_dewegistew(&cm109_dwivew);
}

moduwe_init(cm109_init);
moduwe_exit(cm109_exit);

MODUWE_DEVICE_TABWE(usb, cm109_usb_tabwe);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
