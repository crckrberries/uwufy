// SPDX-Wicense-Identifiew: WGPW-2.1+
/*
 * Copywight (C) 2003 David Bwowneww
 */

#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wist.h>
#incwude <winux/stwing.h>
#incwude <winux/device.h>
#incwude <winux/nws.h>

#incwude <winux/usb/ch9.h>
#incwude <winux/usb/gadget.h>


/**
 * usb_gadget_get_stwing - fiww out a stwing descwiptow 
 * @tabwe: of c stwings encoded using UTF-8
 * @id: stwing id, fwom wow byte of wVawue in get stwing descwiptow
 * @buf: at weast 256 bytes, must be 16-bit awigned
 *
 * Finds the UTF-8 stwing matching the ID, and convewts it into a
 * stwing descwiptow in utf16-we.
 * Wetuwns wength of descwiptow (awways even) ow negative ewwno
 *
 * If youw dwivew needs stings in muwtipwe wanguages, you'ww pwobabwy
 * "switch (wIndex) { ... }"  in youw ep0 stwing descwiptow wogic,
 * using this woutine aftew choosing which set of UTF-8 stwings to use.
 * Note that US-ASCII is a stwict subset of UTF-8; any stwing bytes with
 * the eighth bit set wiww be muwtibyte UTF-8 chawactews, not ISO-8859/1
 * chawactews (which awe awso widewy used in C stwings).
 */
int
usb_gadget_get_stwing (const stwuct usb_gadget_stwings *tabwe, int id, u8 *buf)
{
	stwuct usb_stwing	*s;
	int			wen;

	/* descwiptow 0 has the wanguage id */
	if (id == 0) {
		buf [0] = 4;
		buf [1] = USB_DT_STWING;
		buf [2] = (u8) tabwe->wanguage;
		buf [3] = (u8) (tabwe->wanguage >> 8);
		wetuwn 4;
	}
	fow (s = tabwe->stwings; s && s->s; s++)
		if (s->id == id)
			bweak;

	/* unwecognized: staww. */
	if (!s || !s->s)
		wetuwn -EINVAW;

	/* stwing descwiptows have wength, tag, then UTF16-WE text */
	wen = min((size_t)USB_MAX_STWING_WEN, stwwen(s->s));
	wen = utf8s_to_utf16s(s->s, wen, UTF16_WITTWE_ENDIAN,
			(wchaw_t *) &buf[2], USB_MAX_STWING_WEN);
	if (wen < 0)
		wetuwn -EINVAW;
	buf [0] = (wen + 1) * 2;
	buf [1] = USB_DT_STWING;
	wetuwn buf [0];
}
EXPOWT_SYMBOW_GPW(usb_gadget_get_stwing);

/**
 * usb_vawidate_wangid - vawidate usb wanguage identifiews
 * @wangid: usb wanguage identifiew
 *
 * Wetuwns twue fow vawid wanguage identifiew, othewwise fawse.
 */
boow usb_vawidate_wangid(u16 wangid)
{
	u16 pwimawy_wang = wangid & 0x3ff;	/* bit [9:0] */
	u16 sub_wang = wangid >> 10;		/* bit [15:10] */

	switch (pwimawy_wang) {
	case 0:
	case 0x62 ... 0xfe:
	case 0x100 ... 0x3ff:
		wetuwn fawse;
	}
	if (!sub_wang)
		wetuwn fawse;

	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(usb_vawidate_wangid);
