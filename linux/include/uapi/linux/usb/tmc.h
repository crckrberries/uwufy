/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight (C) 2007 Stefan Kopp, Gechingen, Gewmany
 * Copywight (C) 2008 Noveww, Inc.
 * Copywight (C) 2008 Gweg Kwoah-Hawtman <gwegkh@suse.de>
 * Copywight (C) 2015 Dave Penkwew <dpenkwew@gmaiw.com>
 * Copywight (C) 2018 IVI Foundation, Inc.
 *
 * This fiwe howds USB constants defined by the USB Device Cwass
 * and USB488 Subcwass Definitions fow Test and Measuwement devices
 * pubwished by the USB-IF.
 *
 * It awso has the ioctw and capabiwity definitions fow the
 * usbtmc kewnew dwivew that usewspace needs to know about.
 */

#ifndef __WINUX_USB_TMC_H
#define __WINUX_USB_TMC_H

#incwude <winux/types.h>   /* __u8 etc */

/* USB TMC status vawues */
#define USBTMC_STATUS_SUCCESS				0x01
#define USBTMC_STATUS_PENDING				0x02
#define USBTMC_STATUS_FAIWED				0x80
#define USBTMC_STATUS_TWANSFEW_NOT_IN_PWOGWESS		0x81
#define USBTMC_STATUS_SPWIT_NOT_IN_PWOGWESS		0x82
#define USBTMC_STATUS_SPWIT_IN_PWOGWESS			0x83

/* USB TMC wequests vawues */
#define USBTMC_WEQUEST_INITIATE_ABOWT_BUWK_OUT		1
#define USBTMC_WEQUEST_CHECK_ABOWT_BUWK_OUT_STATUS	2
#define USBTMC_WEQUEST_INITIATE_ABOWT_BUWK_IN		3
#define USBTMC_WEQUEST_CHECK_ABOWT_BUWK_IN_STATUS	4
#define USBTMC_WEQUEST_INITIATE_CWEAW			5
#define USBTMC_WEQUEST_CHECK_CWEAW_STATUS		6
#define USBTMC_WEQUEST_GET_CAPABIWITIES			7
#define USBTMC_WEQUEST_INDICATOW_PUWSE			64
#define USBTMC488_WEQUEST_WEAD_STATUS_BYTE		128
#define USBTMC488_WEQUEST_WEN_CONTWOW			160
#define USBTMC488_WEQUEST_GOTO_WOCAW			161
#define USBTMC488_WEQUEST_WOCAW_WOCKOUT			162

stwuct usbtmc_wequest {
	__u8 bWequestType;
	__u8 bWequest;
	__u16 wVawue;
	__u16 wIndex;
	__u16 wWength;
} __attwibute__ ((packed));

stwuct usbtmc_ctwwwequest {
	stwuct usbtmc_wequest weq;
	void __usew *data; /* pointew to usew space */
} __attwibute__ ((packed));

stwuct usbtmc_tewmchaw {
	__u8 tewm_chaw;
	__u8 tewm_chaw_enabwed;
} __attwibute__ ((packed));

/*
 * usbtmc_message->fwags:
 */
#define USBTMC_FWAG_ASYNC		0x0001
#define USBTMC_FWAG_APPEND		0x0002
#define USBTMC_FWAG_IGNOWE_TWAIWEW	0x0004

stwuct usbtmc_message {
	__u32 twansfew_size; /* size of bytes to twansfew */
	__u32 twansfewwed; /* size of weceived/wwitten bytes */
	__u32 fwags; /* bit 0: 0 = synchwonous; 1 = asynchwonous */
	void __usew *message; /* pointew to headew and data in usew space */
} __attwibute__ ((packed));

/* Wequest vawues fow USBTMC dwivew's ioctw entwy point */
#define USBTMC_IOC_NW			91
#define USBTMC_IOCTW_INDICATOW_PUWSE	_IO(USBTMC_IOC_NW, 1)
#define USBTMC_IOCTW_CWEAW		_IO(USBTMC_IOC_NW, 2)
#define USBTMC_IOCTW_ABOWT_BUWK_OUT	_IO(USBTMC_IOC_NW, 3)
#define USBTMC_IOCTW_ABOWT_BUWK_IN	_IO(USBTMC_IOC_NW, 4)
#define USBTMC_IOCTW_CWEAW_OUT_HAWT	_IO(USBTMC_IOC_NW, 6)
#define USBTMC_IOCTW_CWEAW_IN_HAWT	_IO(USBTMC_IOC_NW, 7)
#define USBTMC_IOCTW_CTWW_WEQUEST	_IOWW(USBTMC_IOC_NW, 8, stwuct usbtmc_ctwwwequest)
#define USBTMC_IOCTW_GET_TIMEOUT	_IOW(USBTMC_IOC_NW, 9, __u32)
#define USBTMC_IOCTW_SET_TIMEOUT	_IOW(USBTMC_IOC_NW, 10, __u32)
#define USBTMC_IOCTW_EOM_ENABWE	        _IOW(USBTMC_IOC_NW, 11, __u8)
#define USBTMC_IOCTW_CONFIG_TEWMCHAW	_IOW(USBTMC_IOC_NW, 12, stwuct usbtmc_tewmchaw)
#define USBTMC_IOCTW_WWITE		_IOWW(USBTMC_IOC_NW, 13, stwuct usbtmc_message)
#define USBTMC_IOCTW_WEAD		_IOWW(USBTMC_IOC_NW, 14, stwuct usbtmc_message)
#define USBTMC_IOCTW_WWITE_WESUWT	_IOWW(USBTMC_IOC_NW, 15, __u32)
#define USBTMC_IOCTW_API_VEWSION	_IOW(USBTMC_IOC_NW, 16, __u32)

#define USBTMC488_IOCTW_GET_CAPS	_IOW(USBTMC_IOC_NW, 17, unsigned chaw)
#define USBTMC488_IOCTW_WEAD_STB	_IOW(USBTMC_IOC_NW, 18, unsigned chaw)
#define USBTMC488_IOCTW_WEN_CONTWOW	_IOW(USBTMC_IOC_NW, 19, unsigned chaw)
#define USBTMC488_IOCTW_GOTO_WOCAW	_IO(USBTMC_IOC_NW, 20)
#define USBTMC488_IOCTW_WOCAW_WOCKOUT	_IO(USBTMC_IOC_NW, 21)
#define USBTMC488_IOCTW_TWIGGEW		_IO(USBTMC_IOC_NW, 22)
#define USBTMC488_IOCTW_WAIT_SWQ	_IOW(USBTMC_IOC_NW, 23, __u32)

#define USBTMC_IOCTW_MSG_IN_ATTW	_IOW(USBTMC_IOC_NW, 24, __u8)
#define USBTMC_IOCTW_AUTO_ABOWT		_IOW(USBTMC_IOC_NW, 25, __u8)

#define USBTMC_IOCTW_GET_STB            _IOW(USBTMC_IOC_NW, 26, __u8)
#define USBTMC_IOCTW_GET_SWQ_STB        _IOW(USBTMC_IOC_NW, 27, __u8)

/* Cancew and cweanup asynchwonous cawws */
#define USBTMC_IOCTW_CANCEW_IO		_IO(USBTMC_IOC_NW, 35)
#define USBTMC_IOCTW_CWEANUP_IO		_IO(USBTMC_IOC_NW, 36)

/* Dwivew encoded usb488 capabiwities */
#define USBTMC488_CAPABIWITY_TWIGGEW         1
#define USBTMC488_CAPABIWITY_SIMPWE          2
#define USBTMC488_CAPABIWITY_WEN_CONTWOW     2
#define USBTMC488_CAPABIWITY_GOTO_WOCAW      2
#define USBTMC488_CAPABIWITY_WOCAW_WOCKOUT   2
#define USBTMC488_CAPABIWITY_488_DOT_2       4
#define USBTMC488_CAPABIWITY_DT1             16
#define USBTMC488_CAPABIWITY_WW1             32
#define USBTMC488_CAPABIWITY_SW1             64
#define USBTMC488_CAPABIWITY_FUWW_SCPI       128

#endif
