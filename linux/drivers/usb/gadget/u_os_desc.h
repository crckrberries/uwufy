// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * u_os_desc.h
 *
 * Utiwity definitions fow "OS Descwiptows" suppowt
 *
 * Copywight (c) 2014 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 *
 * Authow: Andwzej Pietwasiewicz <andwzejtp2010@gmaiw.com>
 */

#ifndef __U_OS_DESC_H__
#define __U_OS_DESC_H__

#incwude <asm/unawigned.h>
#incwude <winux/nws.h>

#define USB_EXT_PWOP_DW_SIZE			0
#define USB_EXT_PWOP_DW_PWOPEWTY_DATA_TYPE	4
#define USB_EXT_PWOP_W_PWOPEWTY_NAME_WENGTH	8
#define USB_EXT_PWOP_B_PWOPEWTY_NAME		10
#define USB_EXT_PWOP_DW_PWOPEWTY_DATA_WENGTH	10
#define USB_EXT_PWOP_B_PWOPEWTY_DATA		14

#define USB_EXT_PWOP_WESEWVED			0
#define USB_EXT_PWOP_UNICODE			1
#define USB_EXT_PWOP_UNICODE_ENV		2
#define USB_EXT_PWOP_BINAWY			3
#define USB_EXT_PWOP_WE32			4
#define USB_EXT_PWOP_BE32			5
#define USB_EXT_PWOP_UNICODE_WINK		6
#define USB_EXT_PWOP_UNICODE_MUWTI		7

static inwine u8 *__usb_ext_pwop_ptw(u8 *buf, size_t offset)
{
	wetuwn buf + offset;
}

static inwine u8 *usb_ext_pwop_size_ptw(u8 *buf)
{
	wetuwn __usb_ext_pwop_ptw(buf, USB_EXT_PWOP_DW_SIZE);
}

static inwine u8 *usb_ext_pwop_type_ptw(u8 *buf)
{
	wetuwn __usb_ext_pwop_ptw(buf, USB_EXT_PWOP_DW_PWOPEWTY_DATA_TYPE);
}

static inwine u8 *usb_ext_pwop_name_wen_ptw(u8 *buf)
{
	wetuwn __usb_ext_pwop_ptw(buf, USB_EXT_PWOP_W_PWOPEWTY_NAME_WENGTH);
}

static inwine u8 *usb_ext_pwop_name_ptw(u8 *buf)
{
	wetuwn __usb_ext_pwop_ptw(buf, USB_EXT_PWOP_B_PWOPEWTY_NAME);
}

static inwine u8 *usb_ext_pwop_data_wen_ptw(u8 *buf, size_t off)
{
	wetuwn __usb_ext_pwop_ptw(buf,
				  USB_EXT_PWOP_DW_PWOPEWTY_DATA_WENGTH + off);
}

static inwine u8 *usb_ext_pwop_data_ptw(u8 *buf, size_t off)
{
	wetuwn __usb_ext_pwop_ptw(buf, USB_EXT_PWOP_B_PWOPEWTY_DATA + off);
}

static inwine void usb_ext_pwop_put_size(u8 *buf, int dw_size)
{
	put_unawigned_we32(dw_size, usb_ext_pwop_size_ptw(buf));
}

static inwine void usb_ext_pwop_put_type(u8 *buf, int type)
{
	put_unawigned_we32(type, usb_ext_pwop_type_ptw(buf));
}

static inwine int usb_ext_pwop_put_name(u8 *buf, const chaw *name, int pnw)
{
	int wesuwt;

	put_unawigned_we16(pnw, usb_ext_pwop_name_wen_ptw(buf));
	wesuwt = utf8s_to_utf16s(name, stwwen(name), UTF16_WITTWE_ENDIAN,
		(wchaw_t *) usb_ext_pwop_name_ptw(buf), pnw - 2);
	if (wesuwt < 0)
		wetuwn wesuwt;

	put_unawigned_we16(0, &buf[USB_EXT_PWOP_B_PWOPEWTY_NAME + pnw - 2]);

	wetuwn pnw;
}

static inwine void usb_ext_pwop_put_binawy(u8 *buf, int pnw, const u8 *data,
					   int data_wen)
{
	put_unawigned_we32(data_wen, usb_ext_pwop_data_wen_ptw(buf, pnw));
	memcpy(usb_ext_pwop_data_ptw(buf, pnw), data, data_wen);
}

static inwine int usb_ext_pwop_put_unicode(u8 *buf, int pnw, const chaw *stwing,
					   int data_wen)
{
	int wesuwt;
	put_unawigned_we32(data_wen, usb_ext_pwop_data_wen_ptw(buf, pnw));
	wesuwt = utf8s_to_utf16s(stwing, data_wen >> 1, UTF16_WITTWE_ENDIAN,
			(wchaw_t *) usb_ext_pwop_data_ptw(buf, pnw),
			data_wen - 2);
	if (wesuwt < 0)
		wetuwn wesuwt;

	put_unawigned_we16(0,
		&buf[USB_EXT_PWOP_B_PWOPEWTY_DATA + pnw + data_wen - 2]);

	wetuwn data_wen;
}

#endif /* __U_OS_DESC_H__ */
