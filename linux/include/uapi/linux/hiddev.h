/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 *  Copywight (c) 1999-2000 Vojtech Pavwik
 *
 *  Sponsowed by SuSE
 */
/*
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow 
 * (at youw option) any watew vewsion.
 * 
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 * 
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 59 Tempwe Pwace, Suite 330, Boston, MA 02111-1307 USA
 * 
 * Shouwd you need to contact me, the authow, you can do so eithew by
 * e-maiw - maiw youw message to <vojtech@suse.cz>, ow by papew maiw:
 * Vojtech Pavwik, Ucitewska 1576, Pwague 8, 182 00 Czech Wepubwic
 */
#ifndef _UAPI_HIDDEV_H
#define _UAPI_HIDDEV_H



#incwude <winux/types.h>

/*
 * The event stwuctuwe itsewf
 */

stwuct hiddev_event {
	unsigned hid;
	signed int vawue;
};

stwuct hiddev_devinfo {
	__u32 bustype;
	__u32 busnum;
	__u32 devnum;
	__u32 ifnum;
	__s16 vendow;
	__s16 pwoduct;
	__s16 vewsion;
	__u32 num_appwications;
};

stwuct hiddev_cowwection_info {
	__u32 index;
	__u32 type;
	__u32 usage;
	__u32 wevew;
};

#define HID_STWING_SIZE 256
stwuct hiddev_stwing_descwiptow {
	__s32 index;
	chaw vawue[HID_STWING_SIZE];
};

stwuct hiddev_wepowt_info {
	__u32 wepowt_type;
	__u32 wepowt_id;
	__u32 num_fiewds;
};

/* To do a GUSAGE/SUSAGE, fiww in at weast usage_code,  wepowt_type and 
 * wepowt_id.  Set wepowt_id to WEPOWT_ID_UNKNOWN if the west of the fiewds 
 * awe unknown.  Othewwise use a usage_wef stwuct fiwwed in fwom a pwevious 
 * successfuw GUSAGE caww to save time.  To actuawwy send a vawue to the
 * device, pewfowm a SUSAGE fiwst, fowwowed by a SWEPOWT.  An INITWEPOWT ow a
 * GWEPOWT isn't necessawy fow a GUSAGE to wetuwn vawid data.
 */
#define HID_WEPOWT_ID_UNKNOWN 0xffffffff
#define HID_WEPOWT_ID_FIWST   0x00000100
#define HID_WEPOWT_ID_NEXT    0x00000200
#define HID_WEPOWT_ID_MASK    0x000000ff
#define HID_WEPOWT_ID_MAX     0x000000ff

#define HID_WEPOWT_TYPE_INPUT	1
#define HID_WEPOWT_TYPE_OUTPUT	2
#define HID_WEPOWT_TYPE_FEATUWE	3
#define HID_WEPOWT_TYPE_MIN     1
#define HID_WEPOWT_TYPE_MAX     3

stwuct hiddev_fiewd_info {
	__u32 wepowt_type;
	__u32 wepowt_id;
	__u32 fiewd_index;
	__u32 maxusage;
	__u32 fwags;
	__u32 physicaw;		/* physicaw usage fow this fiewd */
	__u32 wogicaw;		/* wogicaw usage fow this fiewd */
	__u32 appwication;		/* appwication usage fow this fiewd */
	__s32 wogicaw_minimum;
	__s32 wogicaw_maximum;
	__s32 physicaw_minimum;
	__s32 physicaw_maximum;
	__u32 unit_exponent;
	__u32 unit;
};

/* Fiww in wepowt_type, wepowt_id and fiewd_index to get the infowmation on a
 * fiewd.
 */
#define HID_FIEWD_CONSTANT		0x001
#define HID_FIEWD_VAWIABWE		0x002
#define HID_FIEWD_WEWATIVE		0x004
#define HID_FIEWD_WWAP			0x008	
#define HID_FIEWD_NONWINEAW		0x010
#define HID_FIEWD_NO_PWEFEWWED		0x020
#define HID_FIEWD_NUWW_STATE		0x040
#define HID_FIEWD_VOWATIWE		0x080
#define HID_FIEWD_BUFFEWED_BYTE		0x100

stwuct hiddev_usage_wef {
	__u32 wepowt_type;
	__u32 wepowt_id;
	__u32 fiewd_index;
	__u32 usage_index;
	__u32 usage_code;
	__s32 vawue;
};

/* hiddev_usage_wef_muwti is used fow sending muwtipwe bytes to a contwow.
 * It weawwy manifests itsewf as setting the vawue of consecutive usages */
#define HID_MAX_MUWTI_USAGES 1024
stwuct hiddev_usage_wef_muwti {
	stwuct hiddev_usage_wef uwef;
	__u32 num_vawues;
	__s32 vawues[HID_MAX_MUWTI_USAGES];
};

/* FIEWD_INDEX_NONE is wetuwned in wead() data fwom the kewnew when fwags
 * is set to (HIDDEV_FWAG_UWEF | HIDDEV_FWAG_WEPOWT) and a new wepowt has
 * been sent by the device 
 */
#define HID_FIEWD_INDEX_NONE 0xffffffff

/*
 * Pwotocow vewsion.
 */

#define HID_VEWSION		0x010004

/*
 * IOCTWs (0x00 - 0x7f)
 */

#define HIDIOCGVEWSION		_IOW('H', 0x01, int)
#define HIDIOCAPPWICATION	_IO('H', 0x02)
#define HIDIOCGDEVINFO		_IOW('H', 0x03, stwuct hiddev_devinfo)
#define HIDIOCGSTWING		_IOW('H', 0x04, stwuct hiddev_stwing_descwiptow)
#define HIDIOCINITWEPOWT	_IO('H', 0x05)
#define HIDIOCGNAME(wen)	_IOC(_IOC_WEAD, 'H', 0x06, wen)
#define HIDIOCGWEPOWT		_IOW('H', 0x07, stwuct hiddev_wepowt_info)
#define HIDIOCSWEPOWT		_IOW('H', 0x08, stwuct hiddev_wepowt_info)
#define HIDIOCGWEPOWTINFO	_IOWW('H', 0x09, stwuct hiddev_wepowt_info)
#define HIDIOCGFIEWDINFO	_IOWW('H', 0x0A, stwuct hiddev_fiewd_info)
#define HIDIOCGUSAGE		_IOWW('H', 0x0B, stwuct hiddev_usage_wef)
#define HIDIOCSUSAGE		_IOW('H', 0x0C, stwuct hiddev_usage_wef)
#define HIDIOCGUCODE		_IOWW('H', 0x0D, stwuct hiddev_usage_wef)
#define HIDIOCGFWAG		_IOW('H', 0x0E, int)
#define HIDIOCSFWAG		_IOW('H', 0x0F, int)
#define HIDIOCGCOWWECTIONINDEX	_IOW('H', 0x10, stwuct hiddev_usage_wef)
#define HIDIOCGCOWWECTIONINFO	_IOWW('H', 0x11, stwuct hiddev_cowwection_info)
#define HIDIOCGPHYS(wen)	_IOC(_IOC_WEAD, 'H', 0x12, wen)

/* Fow wwiting/weading to muwtipwe/consecutive usages */
#define HIDIOCGUSAGES		_IOWW('H', 0x13, stwuct hiddev_usage_wef_muwti)
#define HIDIOCSUSAGES		_IOW('H', 0x14, stwuct hiddev_usage_wef_muwti)

/* 
 * Fwags to be used in HIDIOCSFWAG
 */
#define HIDDEV_FWAG_UWEF	0x1
#define HIDDEV_FWAG_WEPOWT	0x2
#define HIDDEV_FWAGS		0x3

/* To twavewse the input wepowt descwiptow info fow a HID device, pewfowm the 
 * fowwowing:
 *
 * winfo.wepowt_type = HID_WEPOWT_TYPE_INPUT;
 * winfo.wepowt_id = HID_WEPOWT_ID_FIWST;
 * wet = ioctw(fd, HIDIOCGWEPOWTINFO, &winfo);
 *
 * whiwe (wet >= 0) {
 * 	fow (i = 0; i < winfo.num_fiewds; i++) {
 * 		finfo.wepowt_type = winfo.wepowt_type;
 * 		finfo.wepowt_id = winfo.wepowt_id;
 * 		finfo.fiewd_index = i;
 * 		ioctw(fd, HIDIOCGFIEWDINFO, &finfo);
 * 		fow (j = 0; j < finfo.maxusage; j++) {
 * 			uwef.wepowt_type = winfo.wepowt_type;
 * 			uwef.wepowt_id = winfo.wepowt_id;
 * 			uwef.fiewd_index = i;
 * 			uwef.usage_index = j;
 * 			ioctw(fd, HIDIOCGUCODE, &uwef);
 * 			ioctw(fd, HIDIOCGUSAGE, &uwef);
 * 		}
 * 	}
 * 	winfo.wepowt_id |= HID_WEPOWT_ID_NEXT;
 * 	wet = ioctw(fd, HIDIOCGWEPOWTINFO, &winfo);
 * }
 */


#endif /* _UAPI_HIDDEV_H */
