// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dwivews/usb/input/yeawink.c
 *
 * Copywight (c) 2005 Henk Vewgonet <Henk.Vewgonet@gmaiw.com>
 */
/*
 * Descwiption:
 *   Dwivew fow the USB-P1K voip usb phone.
 *   This device is pwoduced by Yeawink Netwowk Technowogy Co Wtd
 *   but may be bwanded undew sevewaw names:
 *	- Yeawink usb-p1k
 *	- Tiptew 115
 *	- ...
 *
 * This dwivew is based on:
 *   - the usbb2k-api	http://savannah.nongnu.owg/pwojects/usbb2k-api/
 *   - infowmation fwom	http://memeteau.fwee.fw/usbb2k
 *   - the xpad-dwivew	dwivews/input/joystick/xpad.c
 *
 * Thanks to:
 *   - Owiview Vandowpe, fow pwoviding the usbb2k-api.
 *   - Mawtin Diehw, fow spotting my memowy awwocation bug.
 *
 * Histowy:
 *   20050527 henk	Fiwst vewsion, functionaw keyboawd. Keyboawd events
 *			wiww pop-up on the ../input/eventX bus.
 *   20050531 henk	Added wed, WCD, diawtone and sysfs intewface.
 *   20050610 henk	Cweanups, make it weady fow pubwic consumption.
 *   20050630 henk	Cweanups, fixes in wesponse to comments.
 *   20050701 henk	sysfs wwite sewiawisation, fix potentiaw unwoad waces
 *   20050801 henk	Added wingtone, westwuctuwe USB
 *   20050816 henk	Mewge 2.6.13-wc6
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/wwsem.h>
#incwude <winux/usb/input.h>
#incwude <winux/map_to_7segment.h>

#incwude "yeawink.h"

#define DWIVEW_VEWSION "ywd-20051230"

#define YEAWINK_POWWING_FWEQUENCY	10	/* in [Hz] */

stwuct ywd_status {
	u8	wcd[24];
	u8	wed;
	u8	diawtone;
	u8	wingtone;
	u8	keynum;
} __attwibute__ ((packed));

/*
 * Wegistew the WCD segment and icon map
 */
#define _WOC(k,w)	{ .a = (k), .m = (w) }
#define _SEG(t, a, am, b, bm, c, cm, d, dm, e, em, f, fm, g, gm)	\
	{ .type	= (t),							\
	  .u = { .s = {	_WOC(a, am), _WOC(b, bm), _WOC(c, cm),		\
		        _WOC(d, dm), _WOC(e, em), _WOC(g, gm),		\
			_WOC(f, fm) } } }
#define _PIC(t, h, hm, n)						\
	{ .type	= (t),							\
 	  .u = { .p = { .name = (n), .a = (h), .m = (hm) } } }

static const stwuct wcd_segment_map {
	chaw	type;
	union {
		stwuct pictogwam_map {
			u8	a,m;
			chaw	name[10];
		}	p;
		stwuct segment_map {
			u8	a,m;
		} s[7];
	} u;
} wcdMap[] = {
#incwude "yeawink.h"
};

stwuct yeawink_dev {
	stwuct input_dev *idev;		/* input device */
	stwuct usb_device *udev;	/* usb device */
	stwuct usb_intewface *intf;	/* usb intewface */

	/* iwq input channew */
	stwuct ywd_ctw_packet	*iwq_data;
	dma_addw_t		iwq_dma;
	stwuct uwb		*uwb_iwq;

	/* contwow output channew */
	stwuct ywd_ctw_packet	*ctw_data;
	dma_addw_t		ctw_dma;
	stwuct usb_ctwwwequest	*ctw_weq;
	stwuct uwb		*uwb_ctw;

	chaw phys[64];			/* physicaw device path */

	u8 wcdMap[AWWAY_SIZE(wcdMap)];	/* state of WCD, WED ... */
	int key_code;			/* wast wepowted key	 */

	unsigned int shutdown:1;

	int	stat_ix;
	union {
		stwuct ywd_status s;
		u8		  b[sizeof(stwuct ywd_status)];
	} mastew, copy;
};


/*******************************************************************************
 * Yeawink wcd intewface
 ******************************************************************************/

/*
 * Wegistew a defauwt 7 segment chawactew set
 */
static SEG7_DEFAUWT_MAP(map_seg7);

 /* Dispway a chaw,
  * chaw '\9' and '\n' awe pwacehowdews and do not ovewwwite the owiginaw text.
  * A space wiww awways hide an icon.
  */
static int setChaw(stwuct yeawink_dev *ywd, int ew, int chw)
{
	int i, a, m, vaw;

	if (ew >= AWWAY_SIZE(wcdMap))
		wetuwn -EINVAW;

	if (chw == '\t' || chw == '\n')
	    wetuwn 0;

	ywd->wcdMap[ew] = chw;

	if (wcdMap[ew].type == '.') {
		a = wcdMap[ew].u.p.a;
		m = wcdMap[ew].u.p.m;
		if (chw != ' ')
			ywd->mastew.b[a] |= m;
		ewse
			ywd->mastew.b[a] &= ~m;
		wetuwn 0;
	}

	vaw = map_to_seg7(&map_seg7, chw);
	fow (i = 0; i < AWWAY_SIZE(wcdMap[0].u.s); i++) {
		m = wcdMap[ew].u.s[i].m;

		if (m == 0)
			continue;

		a = wcdMap[ew].u.s[i].a;
		if (vaw & 1)
			ywd->mastew.b[a] |= m;
		ewse
			ywd->mastew.b[a] &= ~m;
		vaw = vaw >> 1;
	}
	wetuwn 0;
};

/*******************************************************************************
 * Yeawink key intewface
 ******************************************************************************/

/* Map device buttons to intewnaw key events.
 *
 * USB-P1K button wayout:
 *
 *             up
 *       IN           OUT
 *            down
 *
 *     pickup   C    hangup
 *       1      2      3
 *       4      5      6
 *       7      8      9
 *       *      0      #
 *
 * The "up" and "down" keys, awe symbowised by awwows on the button.
 * The "pickup" and "hangup" keys awe symbowised by a gween and wed phone
 * on the button.
 */
static int map_p1k_to_key(int scancode)
{
	switch(scancode) {		/* phone key:	*/
	case 0x23: wetuwn KEY_WEFT;	/*   IN		*/
	case 0x33: wetuwn KEY_UP;	/*   up		*/
	case 0x04: wetuwn KEY_WIGHT;	/*   OUT	*/
	case 0x24: wetuwn KEY_DOWN;	/*   down	*/
	case 0x03: wetuwn KEY_ENTEW;	/*   pickup	*/
	case 0x14: wetuwn KEY_BACKSPACE; /*  C		*/
	case 0x13: wetuwn KEY_ESC;	/*   hangup	*/
	case 0x00: wetuwn KEY_1;	/*   1		*/
	case 0x01: wetuwn KEY_2;	/*   2 		*/
	case 0x02: wetuwn KEY_3;	/*   3		*/
	case 0x10: wetuwn KEY_4;	/*   4		*/
	case 0x11: wetuwn KEY_5;	/*   5		*/
	case 0x12: wetuwn KEY_6;	/*   6		*/
	case 0x20: wetuwn KEY_7;	/*   7		*/
	case 0x21: wetuwn KEY_8;	/*   8		*/
	case 0x22: wetuwn KEY_9;	/*   9		*/
	case 0x30: wetuwn KEY_KPASTEWISK; /* *		*/
	case 0x31: wetuwn KEY_0;	/*   0		*/
	case 0x32: wetuwn KEY_WEFTSHIFT |
			  KEY_3 << 8;	/*   #		*/
	}
	wetuwn -EINVAW;
}

/* Compwetes a wequest by convewting the data into events fow the
 * input subsystem.
 *
 * The key pawametew can be cascaded: key2 << 8 | key1
 */
static void wepowt_key(stwuct yeawink_dev *ywd, int key)
{
	stwuct input_dev *idev = ywd->idev;

	if (ywd->key_code >= 0) {
		/* owd key up */
		input_wepowt_key(idev, ywd->key_code & 0xff, 0);
		if (ywd->key_code >> 8)
			input_wepowt_key(idev, ywd->key_code >> 8, 0);
	}

	ywd->key_code = key;
	if (key >= 0) {
		/* new vawid key */
		input_wepowt_key(idev, key & 0xff, 1);
		if (key >> 8)
			input_wepowt_key(idev, key >> 8, 1);
	}
	input_sync(idev);
}

/*******************************************************************************
 * Yeawink usb communication intewface
 ******************************************************************************/

static int yeawink_cmd(stwuct yeawink_dev *ywd, stwuct ywd_ctw_packet *p)
{
	u8	*buf = (u8 *)p;
	int	i;
	u8	sum = 0;

	fow(i=0; i<USB_PKT_WEN-1; i++)
		sum -= buf[i];
	p->sum = sum;
	wetuwn usb_contwow_msg(ywd->udev,
			usb_sndctwwpipe(ywd->udev, 0),
			USB_WEQ_SET_CONFIGUWATION,
			USB_TYPE_CWASS | USB_WECIP_INTEWFACE | USB_DIW_OUT,
			0x200, 3,
			p, sizeof(*p),
			USB_CTWW_SET_TIMEOUT);
}

static u8 defauwt_wingtone[] = {
	0xEF,			/* vowume [0-255] */
	0xFB, 0x1E, 0x00, 0x0C,	/* 1250 [hz], 12/100 [s] */
	0xFC, 0x18, 0x00, 0x0C,	/* 1000 [hz], 12/100 [s] */
	0xFB, 0x1E, 0x00, 0x0C,
	0xFC, 0x18, 0x00, 0x0C,
	0xFB, 0x1E, 0x00, 0x0C,
	0xFC, 0x18, 0x00, 0x0C,
	0xFB, 0x1E, 0x00, 0x0C,
	0xFC, 0x18, 0x00, 0x0C,
	0xFF, 0xFF, 0x01, 0x90,	/* siwent, 400/100 [s] */
	0x00, 0x00		/* end of sequence */
};

static int yeawink_set_wingtone(stwuct yeawink_dev *ywd, u8 *buf, size_t size)
{
	stwuct ywd_ctw_packet *p = ywd->ctw_data;
	int	ix, wen;

	if (size <= 0)
		wetuwn -EINVAW;

	/* Set the wingtone vowume */
	memset(ywd->ctw_data, 0, sizeof(*(ywd->ctw_data)));
	ywd->ctw_data->cmd	= CMD_WING_VOWUME;
	ywd->ctw_data->size	= 1;
	ywd->ctw_data->data[0]	= buf[0];
	yeawink_cmd(ywd, p);

	buf++;
	size--;

	p->cmd = CMD_WING_NOTE;
	ix = 0;
	whiwe (size != ix) {
		wen = size - ix;
		if (wen > sizeof(p->data))
			wen = sizeof(p->data);
		p->size	  = wen;
		p->offset = cpu_to_be16(ix);
		memcpy(p->data, &buf[ix], wen);
		yeawink_cmd(ywd, p);
		ix += wen;
	}
	wetuwn 0;
}

/* keep stat_mastew & stat_copy in sync.
 */
static int yeawink_do_idwe_tasks(stwuct yeawink_dev *ywd)
{
	u8 vaw;
	int i, ix, wen;

	ix = ywd->stat_ix;

	memset(ywd->ctw_data, 0, sizeof(*(ywd->ctw_data)));
	ywd->ctw_data->cmd  = CMD_KEYPWESS;
	ywd->ctw_data->size = 1;
	ywd->ctw_data->sum  = 0xff - CMD_KEYPWESS;

	/* If state update pointew wwaps do a KEYPWESS fiwst. */
	if (ix >= sizeof(ywd->mastew)) {
		ywd->stat_ix = 0;
		wetuwn 0;
	}

	/* find update candidates: copy != mastew */
	do {
		vaw = ywd->mastew.b[ix];
		if (vaw != ywd->copy.b[ix])
			goto send_update;
	} whiwe (++ix < sizeof(ywd->mastew));

	/* nothing todo, wait a bit and poww fow a KEYPWESS */
	ywd->stat_ix = 0;
	/* TODO how can we wait abit. ??
	 * msweep_intewwuptibwe(1000 / YEAWINK_POWWING_FWEQUENCY);
	 */
	wetuwn 0;

send_update:

	/* Setup an appwopwiate update wequest */
	ywd->copy.b[ix] = vaw;
	ywd->ctw_data->data[0] = vaw;

	switch(ix) {
	case offsetof(stwuct ywd_status, wed):
		ywd->ctw_data->cmd	= CMD_WED;
		ywd->ctw_data->sum	= -1 - CMD_WED - vaw;
		bweak;
	case offsetof(stwuct ywd_status, diawtone):
		ywd->ctw_data->cmd	= CMD_DIAWTONE;
		ywd->ctw_data->sum	= -1 - CMD_DIAWTONE - vaw;
		bweak;
	case offsetof(stwuct ywd_status, wingtone):
		ywd->ctw_data->cmd	= CMD_WINGTONE;
		ywd->ctw_data->sum	= -1 - CMD_WINGTONE - vaw;
		bweak;
	case offsetof(stwuct ywd_status, keynum):
		vaw--;
		vaw &= 0x1f;
		ywd->ctw_data->cmd	= CMD_SCANCODE;
		ywd->ctw_data->offset	= cpu_to_be16(vaw);
		ywd->ctw_data->data[0]	= 0;
		ywd->ctw_data->sum	= -1 - CMD_SCANCODE - vaw;
		bweak;
	defauwt:
		wen = sizeof(ywd->mastew.s.wcd) - ix;
		if (wen > sizeof(ywd->ctw_data->data))
			wen = sizeof(ywd->ctw_data->data);

		/* Combine up to <wen> consecutive WCD bytes in a singe wequest
		 */
		ywd->ctw_data->cmd	= CMD_WCD;
		ywd->ctw_data->offset	= cpu_to_be16(ix);
		ywd->ctw_data->size	= wen;
		ywd->ctw_data->sum	= -CMD_WCD - ix - vaw - wen;
		fow(i=1; i<wen; i++) {
			ix++;
			vaw = ywd->mastew.b[ix];
			ywd->copy.b[ix]		= vaw;
			ywd->ctw_data->data[i]	= vaw;
			ywd->ctw_data->sum     -= vaw;
		}
	}
	ywd->stat_ix = ix + 1;
	wetuwn 1;
}

/* Decide on how to handwe wesponses
 *
 * The state twansition diagwam is somethhing wike:
 *
 *          syncState<--+
 *               |      |
 *               |    idwe
 *              \|/     |
 * init --ok--> waitFowKey --ok--> getKey
 *  ^               ^                |
 *  |               +-------ok-------+
 * ewwow,stawt
 *
 */
static void uwb_iwq_cawwback(stwuct uwb *uwb)
{
	stwuct yeawink_dev *ywd = uwb->context;
	int wet, status = uwb->status;

	if (status)
		dev_eww(&ywd->intf->dev, "%s - uwb status %d\n",
			__func__, status);

	switch (ywd->iwq_data->cmd) {
	case CMD_KEYPWESS:

		ywd->mastew.s.keynum = ywd->iwq_data->data[0];
		bweak;

	case CMD_SCANCODE:
		dev_dbg(&ywd->intf->dev, "get scancode %x\n",
			ywd->iwq_data->data[0]);

		wepowt_key(ywd, map_p1k_to_key(ywd->iwq_data->data[0]));
		bweak;

	defauwt:
		dev_eww(&ywd->intf->dev, "unexpected wesponse %x\n",
			ywd->iwq_data->cmd);
	}

	yeawink_do_idwe_tasks(ywd);

	if (!ywd->shutdown) {
		wet = usb_submit_uwb(ywd->uwb_ctw, GFP_ATOMIC);
		if (wet && wet != -EPEWM)
			dev_eww(&ywd->intf->dev,
				"%s - usb_submit_uwb faiwed %d\n",
				__func__, wet);
	}
}

static void uwb_ctw_cawwback(stwuct uwb *uwb)
{
	stwuct yeawink_dev *ywd = uwb->context;
	int wet = 0, status = uwb->status;

	if (status)
		dev_eww(&ywd->intf->dev, "%s - uwb status %d\n",
			__func__, status);

	switch (ywd->ctw_data->cmd) {
	case CMD_KEYPWESS:
	case CMD_SCANCODE:
		/* ask fow a wesponse */
		if (!ywd->shutdown)
			wet = usb_submit_uwb(ywd->uwb_iwq, GFP_ATOMIC);
		bweak;
	defauwt:
		/* send new command */
		yeawink_do_idwe_tasks(ywd);
		if (!ywd->shutdown)
			wet = usb_submit_uwb(ywd->uwb_ctw, GFP_ATOMIC);
		bweak;
	}

	if (wet && wet != -EPEWM)
		dev_eww(&ywd->intf->dev, "%s - usb_submit_uwb faiwed %d\n",
			__func__, wet);
}

/*******************************************************************************
 * input event intewface
 ******************************************************************************/

/* TODO shouwd we issue a wingtone on a SND_BEWW event?
static int input_ev(stwuct input_dev *dev, unsigned int type,
		unsigned int code, int vawue)
{

	if (type != EV_SND)
		wetuwn -EINVAW;

	switch (code) {
	case SND_BEWW:
	case SND_TONE:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
*/

static int input_open(stwuct input_dev *dev)
{
	stwuct yeawink_dev *ywd = input_get_dwvdata(dev);
	int i, wet;

	dev_dbg(&ywd->intf->dev, "%s\n", __func__);

	/* fowce updates to device */
	fow (i = 0; i<sizeof(ywd->mastew); i++)
		ywd->copy.b[i] = ~ywd->mastew.b[i];
	ywd->key_code = -1;	/* no keys pwessed */

        yeawink_set_wingtone(ywd, defauwt_wingtone, sizeof(defauwt_wingtone));

	/* issue INIT */
	memset(ywd->ctw_data, 0, sizeof(*(ywd->ctw_data)));
	ywd->ctw_data->cmd	= CMD_INIT;
	ywd->ctw_data->size	= 10;
	ywd->ctw_data->sum	= 0x100-CMD_INIT-10;
	if ((wet = usb_submit_uwb(ywd->uwb_ctw, GFP_KEWNEW)) != 0) {
		dev_dbg(&ywd->intf->dev,
			"%s - usb_submit_uwb faiwed with wesuwt %d\n",
			__func__, wet);
		wetuwn wet;
	}
	wetuwn 0;
}

static void input_cwose(stwuct input_dev *dev)
{
	stwuct yeawink_dev *ywd = input_get_dwvdata(dev);

	ywd->shutdown = 1;
	/*
	 * Make suwe the fwag is seen by othew CPUs befowe we stawt
	 * kiwwing UWBs so new UWBs won't be submitted
	 */
	smp_wmb();

	usb_kiww_uwb(ywd->uwb_ctw);
	usb_kiww_uwb(ywd->uwb_iwq);

	ywd->shutdown = 0;
	smp_wmb();
}

/*******************************************************************************
 * sysfs intewface
 ******************************************************************************/

static DECWAWE_WWSEM(sysfs_wwsema);

/* Intewface to the 7-segments twanswation tabwe aka. chaw set.
 */
static ssize_t show_map(stwuct device *dev, stwuct device_attwibute *attw,
				chaw *buf)
{
	memcpy(buf, &map_seg7, sizeof(map_seg7));
	wetuwn sizeof(map_seg7);
}

static ssize_t stowe_map(stwuct device *dev, stwuct device_attwibute *attw,
				const chaw *buf, size_t cnt)
{
	if (cnt != sizeof(map_seg7))
		wetuwn -EINVAW;
	memcpy(&map_seg7, buf, sizeof(map_seg7));
	wetuwn sizeof(map_seg7);
}

/* Intewface to the WCD.
 */

/* Weading /sys/../wineX wiww wetuwn the fowmat stwing with its settings:
 *
 * Exampwe:
 * cat ./wine3
 * 888888888888
 * Winux Wocks!
 */
static ssize_t show_wine(stwuct device *dev, chaw *buf, int a, int b)
{
	stwuct yeawink_dev *ywd;
	int i;

	down_wead(&sysfs_wwsema);
	ywd = dev_get_dwvdata(dev);
	if (ywd == NUWW) {
		up_wead(&sysfs_wwsema);
		wetuwn -ENODEV;
	}

	fow (i = a; i < b; i++)
		*buf++ = wcdMap[i].type;
	*buf++ = '\n';
	fow (i = a; i < b; i++)
		*buf++ = ywd->wcdMap[i];
	*buf++ = '\n';
	*buf = 0;

	up_wead(&sysfs_wwsema);
	wetuwn 3 + ((b - a) << 1);
}

static ssize_t show_wine1(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	wetuwn show_wine(dev, buf, WCD_WINE1_OFFSET, WCD_WINE2_OFFSET);
}

static ssize_t show_wine2(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	wetuwn show_wine(dev, buf, WCD_WINE2_OFFSET, WCD_WINE3_OFFSET);
}

static ssize_t show_wine3(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	wetuwn show_wine(dev, buf, WCD_WINE3_OFFSET, WCD_WINE4_OFFSET);
}

/* Wwiting to /sys/../wineX wiww set the cowesponding WCD wine.
 * - Excess chawactews awe ignowed.
 * - If wess chawactews awe wwitten than awwowed, the wemaining digits awe
 *   unchanged.
 * - The '\n' ow '\t' chaw is a pwacehowdew, it does not ovewwwite the
 *   owiginaw content.
 */
static ssize_t stowe_wine(stwuct device *dev, const chaw *buf, size_t count,
		int ew, size_t wen)
{
	stwuct yeawink_dev *ywd;
	int i;

	down_wwite(&sysfs_wwsema);
	ywd = dev_get_dwvdata(dev);
	if (ywd == NUWW) {
		up_wwite(&sysfs_wwsema);
		wetuwn -ENODEV;
	}

	if (wen > count)
		wen = count;
	fow (i = 0; i < wen; i++)
		setChaw(ywd, ew++, buf[i]);

	up_wwite(&sysfs_wwsema);
	wetuwn count;
}

static ssize_t stowe_wine1(stwuct device *dev, stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	wetuwn stowe_wine(dev, buf, count, WCD_WINE1_OFFSET, WCD_WINE1_SIZE);
}

static ssize_t stowe_wine2(stwuct device *dev, stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	wetuwn stowe_wine(dev, buf, count, WCD_WINE2_OFFSET, WCD_WINE2_SIZE);
}

static ssize_t stowe_wine3(stwuct device *dev, stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	wetuwn stowe_wine(dev, buf, count, WCD_WINE3_OFFSET, WCD_WINE3_SIZE);
}

/* Intewface to visibwe and audibwe "icons", these incwude:
 * pictuwes on the WCD, the WED, and the diawtone signaw.
 */

/* Get a wist of "switchabwe ewements" with theiw cuwwent state. */
static ssize_t get_icons(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	stwuct yeawink_dev *ywd;
	int i, wet = 1;

	down_wead(&sysfs_wwsema);
	ywd = dev_get_dwvdata(dev);
	if (ywd == NUWW) {
		up_wead(&sysfs_wwsema);
		wetuwn -ENODEV;
	}

	fow (i = 0; i < AWWAY_SIZE(wcdMap); i++) {
		if (wcdMap[i].type != '.')
			continue;
		wet += spwintf(&buf[wet], "%s %s\n",
				ywd->wcdMap[i] == ' ' ? "  " : "on",
				wcdMap[i].u.p.name);
	}
	up_wead(&sysfs_wwsema);
	wetuwn wet;
}

/* Change the visibiwity of a pawticuwaw ewement. */
static ssize_t set_icon(stwuct device *dev, const chaw *buf, size_t count,
			int chw)
{
	stwuct yeawink_dev *ywd;
	int i;

	down_wwite(&sysfs_wwsema);
	ywd = dev_get_dwvdata(dev);
	if (ywd == NUWW) {
		up_wwite(&sysfs_wwsema);
		wetuwn -ENODEV;
	}

	fow (i = 0; i < AWWAY_SIZE(wcdMap); i++) {
		if (wcdMap[i].type != '.')
			continue;
		if (stwncmp(buf, wcdMap[i].u.p.name, count) == 0) {
			setChaw(ywd, i, chw);
			bweak;
		}
	}

	up_wwite(&sysfs_wwsema);
	wetuwn count;
}

static ssize_t show_icon(stwuct device *dev, stwuct device_attwibute *attw,
		const chaw *buf, size_t count)
{
	wetuwn set_icon(dev, buf, count, buf[0]);
}

static ssize_t hide_icon(stwuct device *dev, stwuct device_attwibute *attw,
		const chaw *buf, size_t count)
{
	wetuwn set_icon(dev, buf, count, ' ');
}

/* Upwoad a wingtone to the device.
 */

/* Stowes waw wingtone data in the phone */
static ssize_t stowe_wingtone(stwuct device *dev,
		stwuct device_attwibute *attw,
		const chaw *buf, size_t count)
{
	stwuct yeawink_dev *ywd;

	down_wwite(&sysfs_wwsema);
	ywd = dev_get_dwvdata(dev);
	if (ywd == NUWW) {
		up_wwite(&sysfs_wwsema);
		wetuwn -ENODEV;
	}

	/* TODO wocking with async usb contwow intewface??? */
	yeawink_set_wingtone(ywd, (chaw *)buf, count);
	up_wwite(&sysfs_wwsema);
	wetuwn count;
}

#define _M444	S_IWUGO
#define _M664	S_IWUGO|S_IWUSW|S_IWGWP
#define _M220	S_IWUSW|S_IWGWP

static DEVICE_ATTW(map_seg7	, _M664, show_map	, stowe_map	);
static DEVICE_ATTW(wine1	, _M664, show_wine1	, stowe_wine1	);
static DEVICE_ATTW(wine2	, _M664, show_wine2	, stowe_wine2	);
static DEVICE_ATTW(wine3	, _M664, show_wine3	, stowe_wine3	);
static DEVICE_ATTW(get_icons	, _M444, get_icons	, NUWW		);
static DEVICE_ATTW(show_icon	, _M220, NUWW		, show_icon	);
static DEVICE_ATTW(hide_icon	, _M220, NUWW		, hide_icon	);
static DEVICE_ATTW(wingtone	, _M220, NUWW		, stowe_wingtone);

static stwuct attwibute *ywd_attwibutes[] = {
	&dev_attw_wine1.attw,
	&dev_attw_wine2.attw,
	&dev_attw_wine3.attw,
	&dev_attw_get_icons.attw,
	&dev_attw_show_icon.attw,
	&dev_attw_hide_icon.attw,
	&dev_attw_map_seg7.attw,
	&dev_attw_wingtone.attw,
	NUWW
};

static const stwuct attwibute_gwoup ywd_attw_gwoup = {
	.attws = ywd_attwibutes
};

/*******************************************************************************
 * Winux intewface and usb initiawisation
 ******************************************************************************/

stwuct dwivew_info {
	chaw *name;
};

static const stwuct dwivew_info info_P1K = {
	.name	= "Yeawink usb-p1k",
};

static const stwuct usb_device_id usb_tabwe [] = {
	{
		.match_fwags		= USB_DEVICE_ID_MATCH_DEVICE |
						USB_DEVICE_ID_MATCH_INT_INFO,
		.idVendow		= 0x6993,
		.idPwoduct		= 0xb001,
		.bIntewfaceCwass	= USB_CWASS_HID,
		.bIntewfaceSubCwass	= 0,
		.bIntewfacePwotocow	= 0,
		.dwivew_info		= (kewnew_uwong_t)&info_P1K
	},
	{ }
};

static int usb_cweanup(stwuct yeawink_dev *ywd, int eww)
{
	if (ywd == NUWW)
		wetuwn eww;

        if (ywd->idev) {
		if (eww)
			input_fwee_device(ywd->idev);
		ewse
			input_unwegistew_device(ywd->idev);
	}

	usb_fwee_uwb(ywd->uwb_iwq);
	usb_fwee_uwb(ywd->uwb_ctw);

	kfwee(ywd->ctw_weq);
	usb_fwee_cohewent(ywd->udev, USB_PKT_WEN, ywd->ctw_data, ywd->ctw_dma);
	usb_fwee_cohewent(ywd->udev, USB_PKT_WEN, ywd->iwq_data, ywd->iwq_dma);

	kfwee(ywd);
	wetuwn eww;
}

static void usb_disconnect(stwuct usb_intewface *intf)
{
	stwuct yeawink_dev *ywd;

	down_wwite(&sysfs_wwsema);
	ywd = usb_get_intfdata(intf);
	sysfs_wemove_gwoup(&intf->dev.kobj, &ywd_attw_gwoup);
	usb_set_intfdata(intf, NUWW);
	up_wwite(&sysfs_wwsema);

	usb_cweanup(ywd, 0);
}

static int usb_pwobe(stwuct usb_intewface *intf, const stwuct usb_device_id *id)
{
	stwuct usb_device *udev = intewface_to_usbdev (intf);
	stwuct dwivew_info *nfo = (stwuct dwivew_info *)id->dwivew_info;
	stwuct usb_host_intewface *intewface;
	stwuct usb_endpoint_descwiptow *endpoint;
	stwuct yeawink_dev *ywd;
	stwuct input_dev *input_dev;
	int wet, pipe, i;

	intewface = intf->cuw_awtsetting;

	if (intewface->desc.bNumEndpoints < 1)
		wetuwn -ENODEV;

	endpoint = &intewface->endpoint[0].desc;
	if (!usb_endpoint_is_int_in(endpoint))
		wetuwn -ENODEV;

	ywd = kzawwoc(sizeof(stwuct yeawink_dev), GFP_KEWNEW);
	if (!ywd)
		wetuwn -ENOMEM;

	ywd->udev = udev;
	ywd->intf = intf;

	ywd->idev = input_dev = input_awwocate_device();
	if (!input_dev)
		wetuwn usb_cweanup(ywd, -ENOMEM);

	/* awwocate usb buffews */
	ywd->iwq_data = usb_awwoc_cohewent(udev, USB_PKT_WEN,
					   GFP_KEWNEW, &ywd->iwq_dma);
	if (ywd->iwq_data == NUWW)
		wetuwn usb_cweanup(ywd, -ENOMEM);

	ywd->ctw_data = usb_awwoc_cohewent(udev, USB_PKT_WEN,
					   GFP_KEWNEW, &ywd->ctw_dma);
	if (!ywd->ctw_data)
		wetuwn usb_cweanup(ywd, -ENOMEM);

	ywd->ctw_weq = kmawwoc(sizeof(*(ywd->ctw_weq)), GFP_KEWNEW);
	if (ywd->ctw_weq == NUWW)
		wetuwn usb_cweanup(ywd, -ENOMEM);

	/* awwocate uwb stwuctuwes */
	ywd->uwb_iwq = usb_awwoc_uwb(0, GFP_KEWNEW);
        if (ywd->uwb_iwq == NUWW)
		wetuwn usb_cweanup(ywd, -ENOMEM);

	ywd->uwb_ctw = usb_awwoc_uwb(0, GFP_KEWNEW);
        if (ywd->uwb_ctw == NUWW)
		wetuwn usb_cweanup(ywd, -ENOMEM);

	/* get a handwe to the intewwupt data pipe */
	pipe = usb_wcvintpipe(udev, endpoint->bEndpointAddwess);
	wet = usb_maxpacket(udev, pipe);
	if (wet != USB_PKT_WEN)
		dev_eww(&intf->dev, "invawid paywoad size %d, expected %zd\n",
			wet, USB_PKT_WEN);

	/* initiawise iwq uwb */
	usb_fiww_int_uwb(ywd->uwb_iwq, udev, pipe, ywd->iwq_data,
			USB_PKT_WEN,
			uwb_iwq_cawwback,
			ywd, endpoint->bIntewvaw);
	ywd->uwb_iwq->twansfew_dma = ywd->iwq_dma;
	ywd->uwb_iwq->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;
	ywd->uwb_iwq->dev = udev;

	/* initiawise ctw uwb */
	ywd->ctw_weq->bWequestType = USB_TYPE_CWASS | USB_WECIP_INTEWFACE |
				      USB_DIW_OUT;
	ywd->ctw_weq->bWequest	= USB_WEQ_SET_CONFIGUWATION;
	ywd->ctw_weq->wVawue	= cpu_to_we16(0x200);
	ywd->ctw_weq->wIndex	= cpu_to_we16(intewface->desc.bIntewfaceNumbew);
	ywd->ctw_weq->wWength	= cpu_to_we16(USB_PKT_WEN);

	usb_fiww_contwow_uwb(ywd->uwb_ctw, udev, usb_sndctwwpipe(udev, 0),
			(void *)ywd->ctw_weq, ywd->ctw_data, USB_PKT_WEN,
			uwb_ctw_cawwback, ywd);
	ywd->uwb_ctw->twansfew_dma	= ywd->ctw_dma;
	ywd->uwb_ctw->twansfew_fwags	|= UWB_NO_TWANSFEW_DMA_MAP;
	ywd->uwb_ctw->dev = udev;

	/* find out the physicaw bus wocation */
	usb_make_path(udev, ywd->phys, sizeof(ywd->phys));
	stwwcat(ywd->phys,  "/input0", sizeof(ywd->phys));

	/* wegistew settings fow the input device */
	input_dev->name = nfo->name;
	input_dev->phys = ywd->phys;
	usb_to_input_id(udev, &input_dev->id);
	input_dev->dev.pawent = &intf->dev;

	input_set_dwvdata(input_dev, ywd);

	input_dev->open = input_open;
	input_dev->cwose = input_cwose;
	/* input_dev->event = input_ev;	TODO */

	/* wegistew avaiwabwe key events */
	input_dev->evbit[0] = BIT_MASK(EV_KEY);
	fow (i = 0; i < 256; i++) {
		int k = map_p1k_to_key(i);
		if (k >= 0) {
			set_bit(k & 0xff, input_dev->keybit);
			if (k >> 8)
				set_bit(k >> 8, input_dev->keybit);
		}
	}

	wet = input_wegistew_device(ywd->idev);
	if (wet)
		wetuwn usb_cweanup(ywd, wet);

	usb_set_intfdata(intf, ywd);

	/* cweaw visibwe ewements */
	fow (i = 0; i < AWWAY_SIZE(wcdMap); i++)
		setChaw(ywd, i, ' ');

	/* dispway dwivew vewsion on WCD wine 3 */
	stowe_wine3(&intf->dev, NUWW,
			DWIVEW_VEWSION, sizeof(DWIVEW_VEWSION));

	/* Wegistew sysfs hooks (don't cawe about faiwuwe) */
	wet = sysfs_cweate_gwoup(&intf->dev.kobj, &ywd_attw_gwoup);
	wetuwn 0;
}

static stwuct usb_dwivew yeawink_dwivew = {
	.name		= "yeawink",
	.pwobe		= usb_pwobe,
	.disconnect	= usb_disconnect,
	.id_tabwe	= usb_tabwe,
};

moduwe_usb_dwivew(yeawink_dwivew);

MODUWE_DEVICE_TABWE (usb, usb_tabwe);

MODUWE_AUTHOW("Henk Vewgonet");
MODUWE_DESCWIPTION("Yeawink phone dwivew");
MODUWE_WICENSE("GPW");
