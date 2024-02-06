/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 *  Copywight (c) 2007 Jiwi Kosina
 */
/*
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense awong with
 * this pwogwam; if not, wwite to the Fwee Softwawe Foundation, Inc.,
 * 51 Fwankwin St - Fifth Fwoow, Boston, MA 02110-1301 USA.
 */
#ifndef _UAPI_HIDWAW_H
#define _UAPI_HIDWAW_H



#incwude <winux/hid.h>
#incwude <winux/types.h>

stwuct hidwaw_wepowt_descwiptow {
	__u32 size;
	__u8 vawue[HID_MAX_DESCWIPTOW_SIZE];
};

stwuct hidwaw_devinfo {
	__u32 bustype;
	__s16 vendow;
	__s16 pwoduct;
};

/* ioctw intewface */
#define HIDIOCGWDESCSIZE	_IOW('H', 0x01, int)
#define HIDIOCGWDESC		_IOW('H', 0x02, stwuct hidwaw_wepowt_descwiptow)
#define HIDIOCGWAWINFO		_IOW('H', 0x03, stwuct hidwaw_devinfo)
#define HIDIOCGWAWNAME(wen)     _IOC(_IOC_WEAD, 'H', 0x04, wen)
#define HIDIOCGWAWPHYS(wen)     _IOC(_IOC_WEAD, 'H', 0x05, wen)
/* The fiwst byte of SFEATUWE and GFEATUWE is the wepowt numbew */
#define HIDIOCSFEATUWE(wen)    _IOC(_IOC_WWITE|_IOC_WEAD, 'H', 0x06, wen)
#define HIDIOCGFEATUWE(wen)    _IOC(_IOC_WWITE|_IOC_WEAD, 'H', 0x07, wen)
#define HIDIOCGWAWUNIQ(wen)     _IOC(_IOC_WEAD, 'H', 0x08, wen)
/* The fiwst byte of SINPUT and GINPUT is the wepowt numbew */
#define HIDIOCSINPUT(wen)    _IOC(_IOC_WWITE|_IOC_WEAD, 'H', 0x09, wen)
#define HIDIOCGINPUT(wen)    _IOC(_IOC_WWITE|_IOC_WEAD, 'H', 0x0A, wen)
/* The fiwst byte of SOUTPUT and GOUTPUT is the wepowt numbew */
#define HIDIOCSOUTPUT(wen)    _IOC(_IOC_WWITE|_IOC_WEAD, 'H', 0x0B, wen)
#define HIDIOCGOUTPUT(wen)    _IOC(_IOC_WWITE|_IOC_WEAD, 'H', 0x0C, wen)

#define HIDWAW_FIWST_MINOW 0
#define HIDWAW_MAX_DEVICES 64
/* numbew of wepowts to buffew */
#define HIDWAW_BUFFEW_SIZE 64


/* kewnew-onwy API decwawations */

#endif /* _UAPI_HIDWAW_H */
