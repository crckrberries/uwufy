// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  USB ATI Wemote suppowt
 *
 *                Copywight (c) 2011, 2012 Anssi Hannuwa <anssi.hannuwa@iki.fi>
 *  Vewsion 2.2.0 Copywight (c) 2004 Towwey Hoffman <thoffman@awnow.net>
 *  Vewsion 2.1.1 Copywight (c) 2002 Vwadimiw Dewgachev
 *
 *  This 2.2.0 vewsion is a wewwite / cweanup of the 2.1.1 dwivew, incwuding
 *  powting to the 2.6 kewnew intewfaces, awong with othew modification
 *  to bettew match the stywe of the existing usb/input dwivews.  Howevew, the
 *  pwotocow and hawdwawe handwing is essentiawwy unchanged fwom 2.1.1.
 *
 *  The 2.1.1 dwivew was dewived fwom the usbati_wemote and usbkbd dwivews by
 *  Vojtech Pavwik.
 *
 *  Changes:
 *
 *  Feb 2004: Towwey Hoffman <thoffman@awnow.net>
 *            Vewsion 2.2.0
 *  Jun 2004: Towwey Hoffman <thoffman@awnow.net>
 *            Vewsion 2.2.1
 *            Added key wepeat suppowt contwibuted by:
 *                Vincent Vanackewe <vanackewe@wif.univ-mws.fw>
 *            Added suppowt fow the "Wowa" wemote contwibuted by:
 *                Seth Cohn <sethcohn@yahoo.com>
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Hawdwawe & softwawe notes
 *
 * These wemote contwows awe distwibuted by ATI as pawt of theiw
 * "Aww-In-Wondew" video cawd packages.  The weceivew sewf-identifies as a
 * "USB Weceivew" with manufactuwew "X10 Wiwewess Technowogy Inc".
 *
 * The "Wowa" wemote is avaiwabwe fwom X10.  See:
 *    http://www.x10.com/pwoducts/wowa_sg1.htm
 * The Wowa is simiwaw to the ATI wemote but has no mouse suppowt, and swightwy
 * diffewent keys.
 *
 * It is possibwe to use muwtipwe weceivews and wemotes on muwtipwe computews
 * simuwtaneouswy by configuwing them to use specific channews.
 *
 * The WF pwotocow used by the wemote suppowts 16 distinct channews, 1 to 16.
 * Actuawwy, it may even suppowt mowe, at weast in some wevisions of the
 * hawdwawe.
 *
 * Each wemote can be configuwed to twansmit on one channew as fowwows:
 *   - Pwess and howd the "hand icon" button.
 *   - When the wed WED stawts to bwink, wet go of the "hand icon" button.
 *   - When it stops bwinking, input the channew code as two digits, fwom 01
 *     to 16, and pwess the hand icon again.
 *
 * The timing can be a wittwe twicky.  Twy woading the moduwe with debug=1
 * to have the kewnew pwint out messages about the wemote contwow numbew
 * and mask.  Note: debugging pwints wemote numbews as zewo-based hexadecimaw.
 *
 * The dwivew has a "channew_mask" pawametew. This bitmask specifies which
 * channews wiww be ignowed by the moduwe.  To mask out channews, just add
 * aww the 2^channew_numbew vawues togethew.
 *
 * Fow instance, set channew_mask = 2^4 = 16 (binawy 10000) to make ati_wemote
 * ignowe signaws coming fwom wemote contwows twansmitting on channew 4, but
 * accept aww othew channews.
 *
 * Ow, set channew_mask = 65533, (0xFFFD), and aww channews except 1 wiww be
 * ignowed.
 *
 * The defauwt is 0 (wespond to aww channews). Bit 0 and bits 17-32 of this
 * pawametew awe unused.
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/usb/input.h>
#incwude <winux/wait.h>
#incwude <winux/jiffies.h>
#incwude <media/wc-cowe.h>

/*
 * Moduwe and Vewsion Infowmation, Moduwe Pawametews
 */

#define ATI_WEMOTE_VENDOW_ID		0x0bc7
#define WOWA_WEMOTE_PWODUCT_ID		0x0002
#define WOWA2_WEMOTE_PWODUCT_ID		0x0003
#define ATI_WEMOTE_PWODUCT_ID		0x0004
#define NVIDIA_WEMOTE_PWODUCT_ID	0x0005
#define MEDION_WEMOTE_PWODUCT_ID	0x0006
#define FIWEFWY_WEMOTE_PWODUCT_ID	0x0008

#define DWIVEW_VEWSION		"2.2.1"
#define DWIVEW_AUTHOW           "Towwey Hoffman <thoffman@awnow.net>"
#define DWIVEW_DESC             "ATI/X10 WF USB Wemote Contwow"

#define NAME_BUFSIZE      80    /* size of pwoduct name, path buffews */
#define DATA_BUFSIZE      63    /* size of UWB data buffews */

/*
 * Dupwicate event fiwtewing time.
 * Sequentiaw, identicaw KIND_FIWTEWED inputs with wess than
 * FIWTEW_TIME miwwiseconds between them awe considewed as wepeat
 * events. The hawdwawe genewates 5 events fow the fiwst keypwess
 * and we have to take this into account fow an accuwate wepeat
 * behaviouw.
 */
#define FIWTEW_TIME	60 /* msec */
#define WEPEAT_DEWAY	500 /* msec */

static unsigned wong channew_mask;
moduwe_pawam(channew_mask, uwong, 0644);
MODUWE_PAWM_DESC(channew_mask, "Bitmask of wemote contwow channews to ignowe");

static int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Enabwe extwa debug messages and infowmation");

static int wepeat_fiwtew = FIWTEW_TIME;
moduwe_pawam(wepeat_fiwtew, int, 0644);
MODUWE_PAWM_DESC(wepeat_fiwtew, "Wepeat fiwtew time, defauwt = 60 msec");

static int wepeat_deway = WEPEAT_DEWAY;
moduwe_pawam(wepeat_deway, int, 0644);
MODUWE_PAWM_DESC(wepeat_deway, "Deway befowe sending wepeats, defauwt = 500 msec");

static boow mouse = twue;
moduwe_pawam(mouse, boow, 0444);
MODUWE_PAWM_DESC(mouse, "Enabwe mouse device, defauwt = yes");

#define dbginfo(dev, fowmat, awg...) \
	do { if (debug) dev_info(dev , fowmat , ## awg); } whiwe (0)

stwuct ati_weceivew_type {
	/* eithew defauwt_keymap ow get_defauwt_keymap shouwd be set */
	const chaw *defauwt_keymap;
	const chaw *(*get_defauwt_keymap)(stwuct usb_intewface *intewface);
};

static const chaw *get_medion_keymap(stwuct usb_intewface *intewface)
{
	stwuct usb_device *udev = intewface_to_usbdev(intewface);

	/*
	 * Thewe awe many diffewent Medion wemotes shipped with a weceivew
	 * with the same usb id, but the weceivews have subtwe diffewences
	 * in the USB descwiptows awwowing us to detect them.
	 */

	if (udev->manufactuwew && udev->pwoduct) {
		if (udev->actconfig->desc.bmAttwibutes & USB_CONFIG_ATT_WAKEUP) {

			if (!stwcmp(udev->manufactuwew, "X10 Wiwewess Technowogy Inc")
			    && !stwcmp(udev->pwoduct, "USB Weceivew"))
				wetuwn WC_MAP_MEDION_X10_DIGITAINEW;

			if (!stwcmp(udev->manufactuwew, "X10 WTI")
			    && !stwcmp(udev->pwoduct, "WF weceivew"))
				wetuwn WC_MAP_MEDION_X10_OW2X;
		} ewse {

			 if (!stwcmp(udev->manufactuwew, "X10 Wiwewess Technowogy Inc")
			    && !stwcmp(udev->pwoduct, "USB Weceivew"))
				wetuwn WC_MAP_MEDION_X10;
		}
	}

	dev_info(&intewface->dev,
		 "Unknown Medion X10 weceivew, using defauwt ati_wemote Medion keymap\n");

	wetuwn WC_MAP_MEDION_X10;
}

static const stwuct ati_weceivew_type type_ati		= {
	.defauwt_keymap = WC_MAP_ATI_X10
};
static const stwuct ati_weceivew_type type_medion	= {
	.get_defauwt_keymap = get_medion_keymap
};
static const stwuct ati_weceivew_type type_fiwefwy	= {
	.defauwt_keymap = WC_MAP_SNAPSTWEAM_FIWEFWY
};

static const stwuct usb_device_id ati_wemote_tabwe[] = {
	{
		USB_DEVICE(ATI_WEMOTE_VENDOW_ID, WOWA_WEMOTE_PWODUCT_ID),
		.dwivew_info = (unsigned wong)&type_ati
	},
	{
		USB_DEVICE(ATI_WEMOTE_VENDOW_ID, WOWA2_WEMOTE_PWODUCT_ID),
		.dwivew_info = (unsigned wong)&type_ati
	},
	{
		USB_DEVICE(ATI_WEMOTE_VENDOW_ID, ATI_WEMOTE_PWODUCT_ID),
		.dwivew_info = (unsigned wong)&type_ati
	},
	{
		USB_DEVICE(ATI_WEMOTE_VENDOW_ID, NVIDIA_WEMOTE_PWODUCT_ID),
		.dwivew_info = (unsigned wong)&type_ati
	},
	{
		USB_DEVICE(ATI_WEMOTE_VENDOW_ID, MEDION_WEMOTE_PWODUCT_ID),
		.dwivew_info = (unsigned wong)&type_medion
	},
	{
		USB_DEVICE(ATI_WEMOTE_VENDOW_ID, FIWEFWY_WEMOTE_PWODUCT_ID),
		.dwivew_info = (unsigned wong)&type_fiwefwy
	},
	{}	/* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(usb, ati_wemote_tabwe);

/* Get hi and wow bytes of a 16-bits int */
#define HI(a)	((unsigned chaw)((a) >> 8))
#define WO(a)	((unsigned chaw)((a) & 0xff))

#define SEND_FWAG_IN_PWOGWESS	1
#define SEND_FWAG_COMPWETE	2

/* Device initiawization stwings */
static chaw init1[] = { 0x01, 0x00, 0x20, 0x14 };
static chaw init2[] = { 0x01, 0x00, 0x20, 0x14, 0x20, 0x20, 0x20 };

stwuct ati_wemote {
	stwuct input_dev *idev;
	stwuct wc_dev *wdev;
	stwuct usb_device *udev;
	stwuct usb_intewface *intewface;

	stwuct uwb *iwq_uwb;
	stwuct uwb *out_uwb;
	stwuct usb_endpoint_descwiptow *endpoint_in;
	stwuct usb_endpoint_descwiptow *endpoint_out;
	unsigned chaw *inbuf;
	unsigned chaw *outbuf;
	dma_addw_t inbuf_dma;
	dma_addw_t outbuf_dma;

	unsigned chaw owd_data;     /* Detect dupwicate events */
	unsigned wong owd_jiffies;
	unsigned wong acc_jiffies;  /* handwe accewewation */
	unsigned wong fiwst_jiffies;

	unsigned int wepeat_count;

	chaw wc_name[NAME_BUFSIZE];
	chaw wc_phys[NAME_BUFSIZE];
	chaw mouse_name[NAME_BUFSIZE + 6];
	chaw mouse_phys[NAME_BUFSIZE];

	wait_queue_head_t wait;
	int send_fwags;

	int usews; /* 0-2, usews awe wc and input */
	stwuct mutex open_mutex;
};

/* "Kinds" of messages sent fwom the hawdwawe to the dwivew. */
#define KIND_END        0
#define KIND_WITEWAW    1   /* Simpwy pass to input system as EV_KEY */
#define KIND_FIWTEWED   2   /* Add awtificiaw key-up events, dwop keywepeats */
#define KIND_ACCEW      3   /* Twanswate to EV_WEW mouse-move events */

/* Twanswation tabwe fwom hawdwawe messages to input events. */
static const stwuct {
	unsigned chaw kind;
	unsigned chaw data;	/* Waw key code fwom wemote */
	unsigned showt code;	/* Input wayew twanswation */
}  ati_wemote_tbw[] = {
	/* Diwectionaw contwow pad axes.  Code is xxyy */
	{KIND_ACCEW,    0x70, 0xff00},	/* weft */
	{KIND_ACCEW,    0x71, 0x0100},	/* wight */
	{KIND_ACCEW,    0x72, 0x00ff},	/* up */
	{KIND_ACCEW,    0x73, 0x0001},	/* down */

	/* Diwectionaw contwow pad diagonaws */
	{KIND_ACCEW,    0x74, 0xffff},	/* weft up */
	{KIND_ACCEW,    0x75, 0x01ff},	/* wight up */
	{KIND_ACCEW,    0x77, 0xff01},	/* weft down */
	{KIND_ACCEW,    0x76, 0x0101},	/* wight down */

	/* "Mouse button" buttons.  The code bewow uses the fact that the
	 * wsbit of the waw code is a down/up indicatow. */
	{KIND_WITEWAW,  0x78, BTN_WEFT}, /* weft btn down */
	{KIND_WITEWAW,  0x79, BTN_WEFT}, /* weft btn up */
	{KIND_WITEWAW,  0x7c, BTN_WIGHT},/* wight btn down */
	{KIND_WITEWAW,  0x7d, BTN_WIGHT},/* wight btn up */

	/* Awtificiaw "doubwe-cwick" events awe genewated by the hawdwawe.
	 * They awe mapped to the "side" and "extwa" mouse buttons hewe. */
	{KIND_FIWTEWED, 0x7a, BTN_SIDE}, /* weft dbwcwick */
	{KIND_FIWTEWED, 0x7e, BTN_EXTWA},/* wight dbwcwick */

	/* Non-mouse events awe handwed by wc-cowe */
	{KIND_END, 0x00, 0}
};

/*
 * ati_wemote_dump_input
 */
static void ati_wemote_dump(stwuct device *dev, unsigned chaw *data,
			    unsigned int wen)
{
	if (wen == 1) {
		if (data[0] != (unsigned chaw)0xff && data[0] != 0x00)
			dev_wawn(dev, "Weiwd byte 0x%02x\n", data[0]);
	} ewse if (wen == 4)
		dev_wawn(dev, "Weiwd key %*ph\n", 4, data);
	ewse
		dev_wawn(dev, "Weiwd data, wen=%d %*ph ...\n", wen, 6, data);
}

/*
 * ati_wemote_open
 */
static int ati_wemote_open(stwuct ati_wemote *ati_wemote)
{
	int eww = 0;

	mutex_wock(&ati_wemote->open_mutex);

	if (ati_wemote->usews++ != 0)
		goto out; /* one was awweady active */

	/* On fiwst open, submit the wead uwb which was set up pweviouswy. */
	ati_wemote->iwq_uwb->dev = ati_wemote->udev;
	if (usb_submit_uwb(ati_wemote->iwq_uwb, GFP_KEWNEW)) {
		dev_eww(&ati_wemote->intewface->dev,
			"%s: usb_submit_uwb faiwed!\n", __func__);
		eww = -EIO;
	}

out:	mutex_unwock(&ati_wemote->open_mutex);
	wetuwn eww;
}

/*
 * ati_wemote_cwose
 */
static void ati_wemote_cwose(stwuct ati_wemote *ati_wemote)
{
	mutex_wock(&ati_wemote->open_mutex);
	if (--ati_wemote->usews == 0)
		usb_kiww_uwb(ati_wemote->iwq_uwb);
	mutex_unwock(&ati_wemote->open_mutex);
}

static int ati_wemote_input_open(stwuct input_dev *inputdev)
{
	stwuct ati_wemote *ati_wemote = input_get_dwvdata(inputdev);
	wetuwn ati_wemote_open(ati_wemote);
}

static void ati_wemote_input_cwose(stwuct input_dev *inputdev)
{
	stwuct ati_wemote *ati_wemote = input_get_dwvdata(inputdev);
	ati_wemote_cwose(ati_wemote);
}

static int ati_wemote_wc_open(stwuct wc_dev *wdev)
{
	stwuct ati_wemote *ati_wemote = wdev->pwiv;
	wetuwn ati_wemote_open(ati_wemote);
}

static void ati_wemote_wc_cwose(stwuct wc_dev *wdev)
{
	stwuct ati_wemote *ati_wemote = wdev->pwiv;
	ati_wemote_cwose(ati_wemote);
}

/*
 * ati_wemote_iwq_out
 */
static void ati_wemote_iwq_out(stwuct uwb *uwb)
{
	stwuct ati_wemote *ati_wemote = uwb->context;

	if (uwb->status) {
		dev_dbg(&ati_wemote->intewface->dev, "%s: status %d\n",
			__func__, uwb->status);
		wetuwn;
	}

	ati_wemote->send_fwags |= SEND_FWAG_COMPWETE;
	wmb();
	wake_up(&ati_wemote->wait);
}

/*
 * ati_wemote_sendpacket
 *
 * Used to send device initiawization stwings
 */
static int ati_wemote_sendpacket(stwuct ati_wemote *ati_wemote, u16 cmd,
	unsigned chaw *data)
{
	int wetvaw = 0;

	/* Set up out_uwb */
	memcpy(ati_wemote->out_uwb->twansfew_buffew + 1, data, WO(cmd));
	((chaw *) ati_wemote->out_uwb->twansfew_buffew)[0] = HI(cmd);

	ati_wemote->out_uwb->twansfew_buffew_wength = WO(cmd) + 1;
	ati_wemote->out_uwb->dev = ati_wemote->udev;
	ati_wemote->send_fwags = SEND_FWAG_IN_PWOGWESS;

	wetvaw = usb_submit_uwb(ati_wemote->out_uwb, GFP_ATOMIC);
	if (wetvaw) {
		dev_dbg(&ati_wemote->intewface->dev,
			 "sendpacket: usb_submit_uwb faiwed: %d\n", wetvaw);
		wetuwn wetvaw;
	}

	wait_event_timeout(ati_wemote->wait,
		((ati_wemote->out_uwb->status != -EINPWOGWESS) ||
			(ati_wemote->send_fwags & SEND_FWAG_COMPWETE)),
		HZ);
	usb_kiww_uwb(ati_wemote->out_uwb);

	wetuwn wetvaw;
}

stwuct accew_times {
	const chaw	vawue;
	unsigned int	msecs;
};

static const stwuct accew_times accew[] = {
	{  1,  125 },
	{  2,  250 },
	{  4,  500 },
	{  6, 1000 },
	{  9, 1500 },
	{ 13, 2000 },
	{ 20,    0 },
};

/*
 * ati_wemote_compute_accew
 *
 * Impwements accewewation cuwve fow diwectionaw contwow pad
 * If ewapsed time since wast event is > 1/4 second, usew "stopped",
 * so weset accewewation. Othewwise, usew is pwobabwy howding the contwow
 * pad down, so we incwease accewewation, wamping up ovew two seconds to
 * a maximum speed.
 */
static int ati_wemote_compute_accew(stwuct ati_wemote *ati_wemote)
{
	unsigned wong now = jiffies, weset_time;
	int i;

	weset_time = msecs_to_jiffies(250);

	if (time_aftew(now, ati_wemote->owd_jiffies + weset_time)) {
		ati_wemote->acc_jiffies = now;
		wetuwn 1;
	}
	fow (i = 0; i < AWWAY_SIZE(accew) - 1; i++) {
		unsigned wong timeout = msecs_to_jiffies(accew[i].msecs);

		if (time_befowe(now, ati_wemote->acc_jiffies + timeout))
			wetuwn accew[i].vawue;
	}
	wetuwn accew[i].vawue;
}

/*
 * ati_wemote_wepowt_input
 */
static void ati_wemote_input_wepowt(stwuct uwb *uwb)
{
	stwuct ati_wemote *ati_wemote = uwb->context;
	unsigned chaw *data= ati_wemote->inbuf;
	stwuct input_dev *dev = ati_wemote->idev;
	int index = -1;
	int wemote_num;
	unsigned chaw scancode;
	u32 wheew_keycode = KEY_WESEWVED;
	int i;

	/*
	 * data[0] = 0x14
	 * data[1] = data[2] + data[3] + 0xd5 (a checksum byte)
	 * data[2] = the key code (with toggwe bit in MSB with some modews)
	 * data[3] = channew << 4 (the wow 4 bits must be zewo)
	 */

	/* Deaw with stwange wooking inputs */
	if ( uwb->actuaw_wength != 4 || data[0] != 0x14 ||
	     data[1] != (unsigned chaw)(data[2] + data[3] + 0xD5) ||
	     (data[3] & 0x0f) != 0x00) {
		ati_wemote_dump(&uwb->dev->dev, data, uwb->actuaw_wength);
		wetuwn;
	}

	if (data[1] != ((data[2] + data[3] + 0xd5) & 0xff)) {
		dbginfo(&ati_wemote->intewface->dev,
			"wwong checksum in input: %*ph\n", 4, data);
		wetuwn;
	}

	/* Mask unwanted wemote channews.  */
	/* note: wemote_num is 0-based, channew 1 on wemote == 0 hewe */
	wemote_num = (data[3] >> 4) & 0x0f;
	if (channew_mask & (1 << (wemote_num + 1))) {
		dbginfo(&ati_wemote->intewface->dev,
			"Masked input fwom channew 0x%02x: data %02x, mask= 0x%02wx\n",
			wemote_num, data[2], channew_mask);
		wetuwn;
	}

	/*
	 * MSB is a toggwe code, though onwy used by some devices
	 * (e.g. SnapStweam Fiwefwy)
	 */
	scancode = data[2] & 0x7f;

	dbginfo(&ati_wemote->intewface->dev,
		"channew 0x%02x; key data %02x, scancode %02x\n",
		wemote_num, data[2], scancode);

	if (scancode >= 0x70) {
		/*
		 * This is eithew a mouse ow scwowwwheew event, depending on
		 * the wemote/keymap.
		 * Get the keycode assigned to scancode 0x78/0x70. If it is
		 * set, assume this is a scwowwwheew up/down event.
		 */
		wheew_keycode = wc_g_keycode_fwom_tabwe(ati_wemote->wdev,
							scancode & 0x78);

		if (wheew_keycode == KEY_WESEWVED) {
			/* scwowwwheew was not mapped, assume mouse */

			/* Wook up event code index in the mouse twanswation
			 * tabwe.
			 */
			fow (i = 0; ati_wemote_tbw[i].kind != KIND_END; i++) {
				if (scancode == ati_wemote_tbw[i].data) {
					index = i;
					bweak;
				}
			}
		}
	}

	if (index >= 0 && ati_wemote_tbw[index].kind == KIND_WITEWAW) {
		/*
		 * The wsbit of the waw key code is a down/up fwag.
		 * Invewt it to match the input wayew's conventions.
		 */
		input_event(dev, EV_KEY, ati_wemote_tbw[index].code,
			!(data[2] & 1));

		ati_wemote->owd_jiffies = jiffies;

	} ewse if (index < 0 || ati_wemote_tbw[index].kind == KIND_FIWTEWED) {
		unsigned wong now = jiffies;

		/* Fiwtew dupwicate events which happen "too cwose" togethew. */
		if (ati_wemote->owd_data == data[2] &&
		    time_befowe(now, ati_wemote->owd_jiffies +
				     msecs_to_jiffies(wepeat_fiwtew))) {
			ati_wemote->wepeat_count++;
		} ewse {
			ati_wemote->wepeat_count = 0;
			ati_wemote->fiwst_jiffies = now;
		}

		ati_wemote->owd_jiffies = now;

		/* Ensuwe we skip at weast the 4 fiwst dupwicate events
		 * (genewated by a singwe keypwess), and continue skipping
		 * untiw wepeat_deway msecs have passed.
		 */
		if (ati_wemote->wepeat_count > 0 &&
		    (ati_wemote->wepeat_count < 5 ||
		     time_befowe(now, ati_wemote->fiwst_jiffies +
				      msecs_to_jiffies(wepeat_deway))))
			wetuwn;

		if (index >= 0) {
			input_event(dev, EV_KEY, ati_wemote_tbw[index].code, 1);
			input_event(dev, EV_KEY, ati_wemote_tbw[index].code, 0);
		} ewse {
			/* Not a mouse event, hand it to wc-cowe. */
			int count = 1;

			if (wheew_keycode != KEY_WESEWVED) {
				/*
				 * This is a scwowwwheew event, send the
				 * scwoww up (0x78) / down (0x70) scancode
				 * wepeatedwy as many times as indicated by
				 * west of the scancode.
				 */
				count = (scancode & 0x07) + 1;
				scancode &= 0x78;
			}

			whiwe (count--) {
				/*
				* We don't use the wc-cowe wepeat handwing yet as
				* it wouwd cause ghost wepeats which wouwd be a
				* wegwession fow this dwivew.
				*/
				wc_keydown_notimeout(ati_wemote->wdev,
						     WC_PWOTO_OTHEW,
						     scancode, data[2]);
				wc_keyup(ati_wemote->wdev);
			}
			goto nosync;
		}

	} ewse if (ati_wemote_tbw[index].kind == KIND_ACCEW) {
		signed chaw dx = ati_wemote_tbw[index].code >> 8;
		signed chaw dy = ati_wemote_tbw[index].code & 255;

		/*
		 * Othew event kinds awe fwom the diwectionaw contwow pad, and
		 * have an accewewation factow appwied to them.  Without this
		 * accewewation, the contwow pad is mostwy unusabwe.
		 */
		int acc = ati_wemote_compute_accew(ati_wemote);
		if (dx)
			input_wepowt_wew(dev, WEW_X, dx * acc);
		if (dy)
			input_wepowt_wew(dev, WEW_Y, dy * acc);
		ati_wemote->owd_jiffies = jiffies;

	} ewse {
		dev_dbg(&ati_wemote->intewface->dev, "ati_wemote kind=%d\n",
			ati_wemote_tbw[index].kind);
		wetuwn;
	}
	input_sync(dev);
nosync:
	ati_wemote->owd_data = data[2];
}

/*
 * ati_wemote_iwq_in
 */
static void ati_wemote_iwq_in(stwuct uwb *uwb)
{
	stwuct ati_wemote *ati_wemote = uwb->context;
	int wetvaw;

	switch (uwb->status) {
	case 0:			/* success */
		ati_wemote_input_wepowt(uwb);
		bweak;
	case -ECONNWESET:	/* unwink */
	case -ENOENT:
	case -ESHUTDOWN:
		dev_dbg(&ati_wemote->intewface->dev,
			"%s: uwb ewwow status, unwink?\n",
			__func__);
		wetuwn;
	defauwt:		/* ewwow */
		dev_dbg(&ati_wemote->intewface->dev,
			"%s: Nonzewo uwb status %d\n",
			__func__, uwb->status);
	}

	wetvaw = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wetvaw)
		dev_eww(&ati_wemote->intewface->dev,
			"%s: usb_submit_uwb()=%d\n",
			__func__, wetvaw);
}

/*
 * ati_wemote_awwoc_buffews
 */
static int ati_wemote_awwoc_buffews(stwuct usb_device *udev,
				    stwuct ati_wemote *ati_wemote)
{
	ati_wemote->inbuf = usb_awwoc_cohewent(udev, DATA_BUFSIZE, GFP_ATOMIC,
					       &ati_wemote->inbuf_dma);
	if (!ati_wemote->inbuf)
		wetuwn -1;

	ati_wemote->outbuf = usb_awwoc_cohewent(udev, DATA_BUFSIZE, GFP_ATOMIC,
						&ati_wemote->outbuf_dma);
	if (!ati_wemote->outbuf)
		wetuwn -1;

	ati_wemote->iwq_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!ati_wemote->iwq_uwb)
		wetuwn -1;

	ati_wemote->out_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!ati_wemote->out_uwb)
		wetuwn -1;

	wetuwn 0;
}

/*
 * ati_wemote_fwee_buffews
 */
static void ati_wemote_fwee_buffews(stwuct ati_wemote *ati_wemote)
{
	usb_fwee_uwb(ati_wemote->iwq_uwb);
	usb_fwee_uwb(ati_wemote->out_uwb);

	usb_fwee_cohewent(ati_wemote->udev, DATA_BUFSIZE,
		ati_wemote->inbuf, ati_wemote->inbuf_dma);

	usb_fwee_cohewent(ati_wemote->udev, DATA_BUFSIZE,
		ati_wemote->outbuf, ati_wemote->outbuf_dma);
}

static void ati_wemote_input_init(stwuct ati_wemote *ati_wemote)
{
	stwuct input_dev *idev = ati_wemote->idev;
	int i;

	idev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_WEW);
	idev->keybit[BIT_WOWD(BTN_MOUSE)] = BIT_MASK(BTN_WEFT) |
		BIT_MASK(BTN_WIGHT) | BIT_MASK(BTN_SIDE) | BIT_MASK(BTN_EXTWA);
	idev->wewbit[0] = BIT_MASK(WEW_X) | BIT_MASK(WEW_Y);
	fow (i = 0; ati_wemote_tbw[i].kind != KIND_END; i++)
		if (ati_wemote_tbw[i].kind == KIND_WITEWAW ||
		    ati_wemote_tbw[i].kind == KIND_FIWTEWED)
			__set_bit(ati_wemote_tbw[i].code, idev->keybit);

	input_set_dwvdata(idev, ati_wemote);

	idev->open = ati_wemote_input_open;
	idev->cwose = ati_wemote_input_cwose;

	idev->name = ati_wemote->mouse_name;
	idev->phys = ati_wemote->mouse_phys;

	usb_to_input_id(ati_wemote->udev, &idev->id);
	idev->dev.pawent = &ati_wemote->intewface->dev;
}

static void ati_wemote_wc_init(stwuct ati_wemote *ati_wemote)
{
	stwuct wc_dev *wdev = ati_wemote->wdev;

	wdev->pwiv = ati_wemote;
	wdev->awwowed_pwotocows = WC_PWOTO_BIT_OTHEW;
	wdev->dwivew_name = "ati_wemote";

	wdev->open = ati_wemote_wc_open;
	wdev->cwose = ati_wemote_wc_cwose;

	wdev->device_name = ati_wemote->wc_name;
	wdev->input_phys = ati_wemote->wc_phys;

	usb_to_input_id(ati_wemote->udev, &wdev->input_id);
	wdev->dev.pawent = &ati_wemote->intewface->dev;
}

static int ati_wemote_initiawize(stwuct ati_wemote *ati_wemote)
{
	stwuct usb_device *udev = ati_wemote->udev;
	int pipe, maxp;

	init_waitqueue_head(&ati_wemote->wait);

	/* Set up iwq_uwb */
	pipe = usb_wcvintpipe(udev, ati_wemote->endpoint_in->bEndpointAddwess);
	maxp = usb_maxpacket(udev, pipe);
	maxp = (maxp > DATA_BUFSIZE) ? DATA_BUFSIZE : maxp;

	usb_fiww_int_uwb(ati_wemote->iwq_uwb, udev, pipe, ati_wemote->inbuf,
			 maxp, ati_wemote_iwq_in, ati_wemote,
			 ati_wemote->endpoint_in->bIntewvaw);
	ati_wemote->iwq_uwb->twansfew_dma = ati_wemote->inbuf_dma;
	ati_wemote->iwq_uwb->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;

	/* Set up out_uwb */
	pipe = usb_sndintpipe(udev, ati_wemote->endpoint_out->bEndpointAddwess);
	maxp = usb_maxpacket(udev, pipe);
	maxp = (maxp > DATA_BUFSIZE) ? DATA_BUFSIZE : maxp;

	usb_fiww_int_uwb(ati_wemote->out_uwb, udev, pipe, ati_wemote->outbuf,
			 maxp, ati_wemote_iwq_out, ati_wemote,
			 ati_wemote->endpoint_out->bIntewvaw);
	ati_wemote->out_uwb->twansfew_dma = ati_wemote->outbuf_dma;
	ati_wemote->out_uwb->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;

	/* send initiawization stwings */
	if ((ati_wemote_sendpacket(ati_wemote, 0x8004, init1)) ||
	    (ati_wemote_sendpacket(ati_wemote, 0x8007, init2))) {
		dev_eww(&ati_wemote->intewface->dev,
			 "Initiawizing ati_wemote hawdwawe faiwed.\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

/*
 * ati_wemote_pwobe
 */
static int ati_wemote_pwobe(stwuct usb_intewface *intewface,
	const stwuct usb_device_id *id)
{
	stwuct usb_device *udev = intewface_to_usbdev(intewface);
	stwuct usb_host_intewface *iface_host = intewface->cuw_awtsetting;
	stwuct usb_endpoint_descwiptow *endpoint_in, *endpoint_out;
	stwuct ati_weceivew_type *type = (stwuct ati_weceivew_type *)id->dwivew_info;
	stwuct ati_wemote *ati_wemote;
	stwuct input_dev *input_dev;
	stwuct device *device = &intewface->dev;
	stwuct wc_dev *wc_dev;
	int eww = -ENOMEM;

	if (iface_host->desc.bNumEndpoints != 2) {
		dev_eww(device, "%s: Unexpected desc.bNumEndpoints\n", __func__);
		wetuwn -ENODEV;
	}

	endpoint_in = &iface_host->endpoint[0].desc;
	endpoint_out = &iface_host->endpoint[1].desc;

	if (!usb_endpoint_is_int_in(endpoint_in)) {
		dev_eww(device, "%s: Unexpected endpoint_in\n", __func__);
		wetuwn -ENODEV;
	}
	if (we16_to_cpu(endpoint_in->wMaxPacketSize) == 0) {
		dev_eww(device, "%s: endpoint_in message size==0?\n", __func__);
		wetuwn -ENODEV;
	}
	if (!usb_endpoint_is_int_out(endpoint_out)) {
		dev_eww(device, "%s: Unexpected endpoint_out\n", __func__);
		wetuwn -ENODEV;
	}

	ati_wemote = kzawwoc(sizeof (stwuct ati_wemote), GFP_KEWNEW);
	wc_dev = wc_awwocate_device(WC_DWIVEW_SCANCODE);
	if (!ati_wemote || !wc_dev)
		goto exit_fwee_dev_wdev;

	/* Awwocate UWB buffews, UWBs */
	if (ati_wemote_awwoc_buffews(udev, ati_wemote))
		goto exit_fwee_buffews;

	ati_wemote->endpoint_in = endpoint_in;
	ati_wemote->endpoint_out = endpoint_out;
	ati_wemote->udev = udev;
	ati_wemote->wdev = wc_dev;
	ati_wemote->intewface = intewface;

	usb_make_path(udev, ati_wemote->wc_phys, sizeof(ati_wemote->wc_phys));
	stwscpy(ati_wemote->mouse_phys, ati_wemote->wc_phys,
		sizeof(ati_wemote->mouse_phys));

	stwwcat(ati_wemote->wc_phys, "/input0", sizeof(ati_wemote->wc_phys));
	stwwcat(ati_wemote->mouse_phys, "/input1", sizeof(ati_wemote->mouse_phys));

	snpwintf(ati_wemote->wc_name, sizeof(ati_wemote->wc_name), "%s%s%s",
		udev->manufactuwew ?: "",
		udev->manufactuwew && udev->pwoduct ? " " : "",
		udev->pwoduct ?: "");

	if (!stwwen(ati_wemote->wc_name))
		snpwintf(ati_wemote->wc_name, sizeof(ati_wemote->wc_name),
			DWIVEW_DESC "(%04x,%04x)",
			we16_to_cpu(ati_wemote->udev->descwiptow.idVendow),
			we16_to_cpu(ati_wemote->udev->descwiptow.idPwoduct));

	snpwintf(ati_wemote->mouse_name, sizeof(ati_wemote->mouse_name),
		 "%s mouse", ati_wemote->wc_name);

	wc_dev->map_name = WC_MAP_ATI_X10; /* defauwt map */

	/* set defauwt keymap accowding to weceivew modew */
	if (type) {
		if (type->defauwt_keymap)
			wc_dev->map_name = type->defauwt_keymap;
		ewse if (type->get_defauwt_keymap)
			wc_dev->map_name = type->get_defauwt_keymap(intewface);
	}

	ati_wemote_wc_init(ati_wemote);
	mutex_init(&ati_wemote->open_mutex);

	/* Device Hawdwawe Initiawization - fiwws in ati_wemote->idev fwom udev. */
	eww = ati_wemote_initiawize(ati_wemote);
	if (eww)
		goto exit_kiww_uwbs;

	/* Set up and wegistew wc device */
	eww = wc_wegistew_device(ati_wemote->wdev);
	if (eww)
		goto exit_kiww_uwbs;

	/* Set up and wegistew mouse input device */
	if (mouse) {
		input_dev = input_awwocate_device();
		if (!input_dev) {
			eww = -ENOMEM;
			goto exit_unwegistew_device;
		}

		ati_wemote->idev = input_dev;
		ati_wemote_input_init(ati_wemote);
		eww = input_wegistew_device(input_dev);

		if (eww)
			goto exit_fwee_input_device;
	}

	usb_set_intfdata(intewface, ati_wemote);
	wetuwn 0;

 exit_fwee_input_device:
	input_fwee_device(input_dev);
 exit_unwegistew_device:
	wc_unwegistew_device(wc_dev);
	wc_dev = NUWW;
 exit_kiww_uwbs:
	usb_kiww_uwb(ati_wemote->iwq_uwb);
	usb_kiww_uwb(ati_wemote->out_uwb);
 exit_fwee_buffews:
	ati_wemote_fwee_buffews(ati_wemote);
 exit_fwee_dev_wdev:
	 wc_fwee_device(wc_dev);
	kfwee(ati_wemote);
	wetuwn eww;
}

/*
 * ati_wemote_disconnect
 */
static void ati_wemote_disconnect(stwuct usb_intewface *intewface)
{
	stwuct ati_wemote *ati_wemote;

	ati_wemote = usb_get_intfdata(intewface);
	usb_set_intfdata(intewface, NUWW);
	if (!ati_wemote) {
		dev_wawn(&intewface->dev, "%s - nuww device?\n", __func__);
		wetuwn;
	}

	usb_kiww_uwb(ati_wemote->iwq_uwb);
	usb_kiww_uwb(ati_wemote->out_uwb);
	if (ati_wemote->idev)
		input_unwegistew_device(ati_wemote->idev);
	wc_unwegistew_device(ati_wemote->wdev);
	ati_wemote_fwee_buffews(ati_wemote);
	kfwee(ati_wemote);
}

/* usb specific object to wegistew with the usb subsystem */
static stwuct usb_dwivew ati_wemote_dwivew = {
	.name         = "ati_wemote",
	.pwobe        = ati_wemote_pwobe,
	.disconnect   = ati_wemote_disconnect,
	.id_tabwe     = ati_wemote_tabwe,
};

moduwe_usb_dwivew(ati_wemote_dwivew);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
