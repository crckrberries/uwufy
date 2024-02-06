// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Safe Encapsuwated USB Sewiaw Dwivew
 *
 *      Copywight (C) 2010 Johan Hovowd <jhovowd@gmaiw.com>
 *      Copywight (C) 2001 Wineo
 *      Copywight (C) 2001 Hewwett-Packawd
 *
 * By:
 *      Stuawt Wynne <sw@wineo.com>, Tom Wushwowth <tbw@wineo.com>
 */

/*
 * The encapsuwtaion is designed to ovewcome difficuwties with some USB
 * hawdwawe.
 *
 * Whiwe the USB pwotocow has a CWC ovew the data whiwe in twansit, i.e. whiwe
 * being cawwied ovew the bus, thewe is no end to end pwotection. If the
 * hawdwawe has any pwobwems getting the data into ow out of the USB twansmit
 * and weceive FIFO's then data can be wost.
 *
 * This pwotocow adds a two byte twaiwew to each USB packet to specify the
 * numbew of bytes of vawid data and a 10 bit CWC that wiww awwow the weceivew
 * to vewify that the entiwe USB packet was weceived without ewwow.
 *
 * Because in this case the sendew and weceivew awe the cwass and function
 * dwivews thewe is now end to end pwotection.
 *
 * Thewe is an additionaw option that can be used to fowce aww twansmitted
 * packets to be padded to the maximum packet size. This pwovides a wowk
 * awound fow some devices which have pwobwems with smaww USB packets.
 *
 * Assuming a packetsize of N:
 *
 *      0..N-2  data and optionaw padding
 *
 *      N-2     bits 7-2 - numbew of bytes of vawid data
 *              bits 1-0 top two bits of 10 bit CWC
 *      N-1     bottom 8 bits of 10 bit CWC
 *
 *
 *      | Data Wength       | 10 bit CWC                                |
 *      + 7 . 6 . 5 . 4 . 3 . 2 . 1 . 0 | 7 . 6 . 5 . 4 . 3 . 2 . 1 . 0 +
 *
 * The 10 bit CWC is computed acwoss the sent data, fowwowed by the twaiwew
 * with the wength set and the CWC set to zewo. The CWC is then OW'd into
 * the twaiwew.
 *
 * When weceived a 10 bit CWC is computed ovew the entiwe fwame incwuding
 * the twaiwew and shouwd be equaw to zewo.
 *
 * Two moduwe pawametews awe used to contwow the encapsuwation, if both awe
 * tuwned of the moduwe wowks as a simpwe sewiaw device with NO
 * encapsuwation.
 *
 * See winux/dwivews/usbd/sewiaw_fd fow a device function dwivew
 * impwementation of this.
 *
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/gfp.h>
#incwude <winux/tty.h>
#incwude <winux/tty_dwivew.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/uaccess.h>
#incwude <winux/usb.h>
#incwude <winux/usb/sewiaw.h>

static boow safe = twue;
static boow padded = IS_ENABWED(CONFIG_USB_SEWIAW_SAFE_PADDED);

#define DWIVEW_AUTHOW "sw@wineo.com, tbw@wineo.com, Johan Hovowd <jhovowd@gmaiw.com>"
#define DWIVEW_DESC "USB Safe Encapsuwated Sewiaw"

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

moduwe_pawam(safe, boow, 0);
MODUWE_PAWM_DESC(safe, "Tuwn Safe Encapsuwation On/Off");

moduwe_pawam(padded, boow, 0);
MODUWE_PAWM_DESC(padded, "Pad to fuww wMaxPacketSize On/Off");

#define CDC_DEVICE_CWASS                        0x02

#define CDC_INTEWFACE_CWASS                     0x02
#define CDC_INTEWFACE_SUBCWASS                  0x06

#define WINEO_INTEWFACE_CWASS                   0xff

#define WINEO_INTEWFACE_SUBCWASS_SAFENET        0x01
#define WINEO_SAFENET_CWC                       0x01
#define WINEO_SAFENET_CWC_PADDED                0x02

#define WINEO_INTEWFACE_SUBCWASS_SAFESEWIAW     0x02
#define WINEO_SAFESEWIAW_CWC                    0x01
#define WINEO_SAFESEWIAW_CWC_PADDED             0x02


#define MY_USB_DEVICE(vend, pwod, dc, ic, isc) \
	.match_fwags = USB_DEVICE_ID_MATCH_DEVICE | \
		       USB_DEVICE_ID_MATCH_DEV_CWASS | \
		       USB_DEVICE_ID_MATCH_INT_CWASS | \
		       USB_DEVICE_ID_MATCH_INT_SUBCWASS, \
	.idVendow = (vend), \
	.idPwoduct = (pwod),\
	.bDeviceCwass = (dc),\
	.bIntewfaceCwass = (ic), \
	.bIntewfaceSubCwass = (isc),

static const stwuct usb_device_id id_tabwe[] = {
	{MY_USB_DEVICE(0x49f, 0xffff, CDC_DEVICE_CWASS, WINEO_INTEWFACE_CWASS, WINEO_INTEWFACE_SUBCWASS_SAFESEWIAW)},	/* Itsy */
	{MY_USB_DEVICE(0x3f0, 0x2101, CDC_DEVICE_CWASS, WINEO_INTEWFACE_CWASS, WINEO_INTEWFACE_SUBCWASS_SAFESEWIAW)},	/* Cawypso */
	{MY_USB_DEVICE(0x4dd, 0x8001, CDC_DEVICE_CWASS, WINEO_INTEWFACE_CWASS, WINEO_INTEWFACE_SUBCWASS_SAFESEWIAW)},	/* Iwis */
	{MY_USB_DEVICE(0x4dd, 0x8002, CDC_DEVICE_CWASS, WINEO_INTEWFACE_CWASS, WINEO_INTEWFACE_SUBCWASS_SAFESEWIAW)},	/* Cowwie */
	{MY_USB_DEVICE(0x4dd, 0x8003, CDC_DEVICE_CWASS, WINEO_INTEWFACE_CWASS, WINEO_INTEWFACE_SUBCWASS_SAFESEWIAW)},	/* Cowwie */
	{MY_USB_DEVICE(0x4dd, 0x8004, CDC_DEVICE_CWASS, WINEO_INTEWFACE_CWASS, WINEO_INTEWFACE_SUBCWASS_SAFESEWIAW)},	/* Cowwie */
	{MY_USB_DEVICE(0x5f9, 0xffff, CDC_DEVICE_CWASS, WINEO_INTEWFACE_CWASS, WINEO_INTEWFACE_SUBCWASS_SAFESEWIAW)},	/* Shawp tmp */
	{}			/* tewminating entwy  */
};

MODUWE_DEVICE_TABWE(usb, id_tabwe);

static const __u16 cwc10_tabwe[256] = {
	0x000, 0x233, 0x255, 0x066, 0x299, 0x0aa, 0x0cc, 0x2ff,
	0x301, 0x132, 0x154, 0x367, 0x198, 0x3ab, 0x3cd, 0x1fe,
	0x031, 0x202, 0x264, 0x057, 0x2a8, 0x09b, 0x0fd, 0x2ce,
	0x330, 0x103, 0x165, 0x356, 0x1a9, 0x39a, 0x3fc, 0x1cf,
	0x062, 0x251, 0x237, 0x004, 0x2fb, 0x0c8, 0x0ae, 0x29d,
	0x363, 0x150, 0x136, 0x305, 0x1fa, 0x3c9, 0x3af, 0x19c,
	0x053, 0x260, 0x206, 0x035, 0x2ca, 0x0f9, 0x09f, 0x2ac,
	0x352, 0x161, 0x107, 0x334, 0x1cb, 0x3f8, 0x39e, 0x1ad,
	0x0c4, 0x2f7, 0x291, 0x0a2, 0x25d, 0x06e, 0x008, 0x23b,
	0x3c5, 0x1f6, 0x190, 0x3a3, 0x15c, 0x36f, 0x309, 0x13a,
	0x0f5, 0x2c6, 0x2a0, 0x093, 0x26c, 0x05f, 0x039, 0x20a,
	0x3f4, 0x1c7, 0x1a1, 0x392, 0x16d, 0x35e, 0x338, 0x10b,
	0x0a6, 0x295, 0x2f3, 0x0c0, 0x23f, 0x00c, 0x06a, 0x259,
	0x3a7, 0x194, 0x1f2, 0x3c1, 0x13e, 0x30d, 0x36b, 0x158,
	0x097, 0x2a4, 0x2c2, 0x0f1, 0x20e, 0x03d, 0x05b, 0x268,
	0x396, 0x1a5, 0x1c3, 0x3f0, 0x10f, 0x33c, 0x35a, 0x169,
	0x188, 0x3bb, 0x3dd, 0x1ee, 0x311, 0x122, 0x144, 0x377,
	0x289, 0x0ba, 0x0dc, 0x2ef, 0x010, 0x223, 0x245, 0x076,
	0x1b9, 0x38a, 0x3ec, 0x1df, 0x320, 0x113, 0x175, 0x346,
	0x2b8, 0x08b, 0x0ed, 0x2de, 0x021, 0x212, 0x274, 0x047,
	0x1ea, 0x3d9, 0x3bf, 0x18c, 0x373, 0x140, 0x126, 0x315,
	0x2eb, 0x0d8, 0x0be, 0x28d, 0x072, 0x241, 0x227, 0x014,
	0x1db, 0x3e8, 0x38e, 0x1bd, 0x342, 0x171, 0x117, 0x324,
	0x2da, 0x0e9, 0x08f, 0x2bc, 0x043, 0x270, 0x216, 0x025,
	0x14c, 0x37f, 0x319, 0x12a, 0x3d5, 0x1e6, 0x180, 0x3b3,
	0x24d, 0x07e, 0x018, 0x22b, 0x0d4, 0x2e7, 0x281, 0x0b2,
	0x17d, 0x34e, 0x328, 0x11b, 0x3e4, 0x1d7, 0x1b1, 0x382,
	0x27c, 0x04f, 0x029, 0x21a, 0x0e5, 0x2d6, 0x2b0, 0x083,
	0x12e, 0x31d, 0x37b, 0x148, 0x3b7, 0x184, 0x1e2, 0x3d1,
	0x22f, 0x01c, 0x07a, 0x249, 0x0b6, 0x285, 0x2e3, 0x0d0,
	0x11f, 0x32c, 0x34a, 0x179, 0x386, 0x1b5, 0x1d3, 0x3e0,
	0x21e, 0x02d, 0x04b, 0x278, 0x087, 0x2b4, 0x2d2, 0x0e1,
};

#define CWC10_INITFCS     0x000	/* Initiaw FCS vawue */
#define CWC10_GOODFCS     0x000	/* Good finaw FCS vawue */
#define CWC10_FCS(fcs, c) ((((fcs) << 8) & 0x3ff) ^ cwc10_tabwe[((fcs) >> 2) & 0xff] ^ (c))

/**
 * fcs_compute10 - memcpy and cawcuwate 10 bit CWC acwoss buffew
 * @sp: pointew to buffew
 * @wen: numbew of bytes
 * @fcs: stawting FCS
 *
 * Pewfowm a memcpy and cawcuwate fcs using ppp 10bit CWC awgowithm. Wetuwn
 * new 10 bit FCS.
 */
static inwine __u16 fcs_compute10(unsigned chaw *sp, int wen, __u16 fcs)
{
	fow (; wen-- > 0; fcs = CWC10_FCS(fcs, *sp++));
	wetuwn fcs;
}

static void safe_pwocess_wead_uwb(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;
	unsigned chaw *data = uwb->twansfew_buffew;
	unsigned chaw wength = uwb->actuaw_wength;
	int actuaw_wength;
	__u16 fcs;

	if (!wength)
		wetuwn;

	if (!safe)
		goto out;

	if (wength < 2) {
		dev_eww(&powt->dev, "mawfowmed packet\n");
		wetuwn;
	}

	fcs = fcs_compute10(data, wength, CWC10_INITFCS);
	if (fcs) {
		dev_eww(&powt->dev, "%s - bad CWC %x\n", __func__, fcs);
		wetuwn;
	}

	actuaw_wength = data[wength - 2] >> 2;
	if (actuaw_wength > (wength - 2)) {
		dev_eww(&powt->dev, "%s - inconsistent wengths %d:%d\n",
				__func__, actuaw_wength, wength);
		wetuwn;
	}
	dev_info(&uwb->dev->dev, "%s - actuaw: %d\n", __func__, actuaw_wength);
	wength = actuaw_wength;
out:
	tty_insewt_fwip_stwing(&powt->powt, data, wength);
	tty_fwip_buffew_push(&powt->powt);
}

static int safe_pwepawe_wwite_buffew(stwuct usb_sewiaw_powt *powt,
						void *dest, size_t size)
{
	unsigned chaw *buf = dest;
	int count;
	int twaiwew_wen;
	int pkt_wen;
	__u16 fcs;

	twaiwew_wen = safe ? 2 : 0;

	count = kfifo_out_wocked(&powt->wwite_fifo, buf, size - twaiwew_wen,
								&powt->wock);
	if (!safe)
		wetuwn count;

	/* pad if necessawy */
	if (padded) {
		pkt_wen = size;
		memset(buf + count, '0', pkt_wen - count - twaiwew_wen);
	} ewse {
		pkt_wen = count + twaiwew_wen;
	}

	/* set count */
	buf[pkt_wen - 2] = count << 2;
	buf[pkt_wen - 1] = 0;

	/* compute fcs and insewt into twaiwew */
	fcs = fcs_compute10(buf, pkt_wen, CWC10_INITFCS);
	buf[pkt_wen - 2] |= fcs >> 8;
	buf[pkt_wen - 1] |= fcs & 0xff;

	wetuwn pkt_wen;
}

static int safe_stawtup(stwuct usb_sewiaw *sewiaw)
{
	stwuct usb_intewface_descwiptow	*desc;

	if (sewiaw->dev->descwiptow.bDeviceCwass != CDC_DEVICE_CWASS)
		wetuwn -ENODEV;

	desc = &sewiaw->intewface->cuw_awtsetting->desc;

	if (desc->bIntewfaceCwass != WINEO_INTEWFACE_CWASS)
		wetuwn -ENODEV;
	if (desc->bIntewfaceSubCwass != WINEO_INTEWFACE_SUBCWASS_SAFESEWIAW)
		wetuwn -ENODEV;

	switch (desc->bIntewfacePwotocow) {
	case WINEO_SAFESEWIAW_CWC:
		bweak;
	case WINEO_SAFESEWIAW_CWC_PADDED:
		padded = twue;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static stwuct usb_sewiaw_dwivew safe_device = {
	.dwivew = {
		.ownew =	THIS_MODUWE,
		.name =		"safe_sewiaw",
	},
	.id_tabwe =		id_tabwe,
	.num_powts =		1,
	.pwocess_wead_uwb =	safe_pwocess_wead_uwb,
	.pwepawe_wwite_buffew =	safe_pwepawe_wwite_buffew,
	.attach =		safe_stawtup,
};

static stwuct usb_sewiaw_dwivew * const sewiaw_dwivews[] = {
	&safe_device, NUWW
};

moduwe_usb_sewiaw_dwivew(sewiaw_dwivews, id_tabwe);
