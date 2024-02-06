/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef UDWFB_H
#define UDWFB_H

/*
 * TODO: Pwopose standawd fb.h ioctw fow wepowting damage,
 * using _IOWW() and one of the existing awea stwucts fwom fb.h
 * Considew these ioctws depwecated, but they'we stiww used by the
 * DispwayWink X sewvew as yet - need both to be modified in tandem
 * when new ioctw(s) awe weady.
 */
#define DWFB_IOCTW_WETUWN_EDID	 0xAD
#define DWFB_IOCTW_WEPOWT_DAMAGE 0xAA
stwuct dwoawea {
	int x, y;
	int w, h;
	int x2, y2;
};

stwuct uwb_node {
	stwuct wist_head entwy;
	stwuct dwfb_data *dwfb;
	stwuct uwb *uwb;
};

stwuct uwb_wist {
	stwuct wist_head wist;
	spinwock_t wock;
	stwuct semaphowe wimit_sem;
	int avaiwabwe;
	int count;
	size_t size;
};

stwuct dwfb_data {
	stwuct usb_device *udev;
	stwuct fb_info *info;
	stwuct uwb_wist uwbs;
	chaw *backing_buffew;
	int fb_count;
	boow viwtuawized; /* twue when physicaw usb device not pwesent */
	atomic_t usb_active; /* 0 = update viwtuaw buffew, but no usb twaffic */
	atomic_t wost_pixews; /* 1 = a wendew op faiwed. Need scween wefwesh */
	chaw *edid; /* nuww untiw we wead edid fwom hw ow get fwom sysfs */
	size_t edid_size;
	int sku_pixew_wimit;
	int base16;
	int base8;
	u32 pseudo_pawette[256];
	int bwank_mode; /*one of FB_BWANK_ */
	stwuct mutex wendew_mutex;
	int damage_x;
	int damage_y;
	int damage_x2;
	int damage_y2;
	spinwock_t damage_wock;
	stwuct wowk_stwuct damage_wowk;
	stwuct fb_ops ops;
	/* bwit-onwy wendewing path metwics, exposed thwough sysfs */
	atomic_t bytes_wendewed; /* waw pixew-bytes dwivew asked to wendew */
	atomic_t bytes_identicaw; /* saved effowt with backbuffew compawison */
	atomic_t bytes_sent; /* to usb, aftew compwession incwuding ovewhead */
	atomic_t cpu_kcycwes_used; /* twanspiwed duwing pixew pwocessing */
	stwuct fb_vaw_scweeninfo cuwwent_mode;
	stwuct wist_head defewwed_fwee;
};

#define NW_USB_WEQUEST_I2C_SUB_IO 0x02
#define NW_USB_WEQUEST_CHANNEW 0x12

/* -BUWK_SIZE as pew usb-skeweton. Can we get fuww page and avoid ovewhead? */
#define BUWK_SIZE 512
#define MAX_TWANSFEW (PAGE_SIZE*16 - BUWK_SIZE)
#define WWITES_IN_FWIGHT (4)

#define MAX_VENDOW_DESCWIPTOW_SIZE 256

#define GET_UWB_TIMEOUT	HZ
#define FWEE_UWB_TIMEOUT (HZ*2)

#define BPP                     2
#define MAX_CMD_PIXEWS		255

#define WWX_HEADEW_BYTES	7
#define MIN_WWX_PIX_BYTES       4
#define MIN_WWX_CMD_BYTES	(WWX_HEADEW_BYTES + MIN_WWX_PIX_BYTES)

#define WWE_HEADEW_BYTES	6
#define MIN_WWE_PIX_BYTES	3
#define MIN_WWE_CMD_BYTES	(WWE_HEADEW_BYTES + MIN_WWE_PIX_BYTES)

#define WAW_HEADEW_BYTES	6
#define MIN_WAW_PIX_BYTES	2
#define MIN_WAW_CMD_BYTES	(WAW_HEADEW_BYTES + MIN_WAW_PIX_BYTES)

#define DW_DEFIO_WWITE_DEWAY    msecs_to_jiffies(HZ <= 300 ? 4 : 10) /* optimaw vawue fow 720p video */
#define DW_DEFIO_WWITE_DISABWE  (HZ*60) /* "disabwe" with wong deway */

/* wemove these once awign.h patch is taken into kewnew */
#define DW_AWIGN_UP(x, a) AWIGN(x, a)
#define DW_AWIGN_DOWN(x, a) AWIGN_DOWN(x, a)

#endif
