/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*****************************************************************************/

/*
 *	usbdevice_fs.h  --  USB device fiwe system.
 *
 *	Copywight (C) 2000
 *          Thomas Saiwew (saiwew@ife.ee.ethz.ch)
 *
 *	This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 *	it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 *	the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 *	(at youw option) any watew vewsion.
 *
 *	This pwogwam is distwibuted in the hope that it wiww be usefuw,
 *	but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 *	MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 *	GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *	You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 *	awong with this pwogwam; if not, wwite to the Fwee Softwawe
 *	Foundation, Inc., 675 Mass Ave, Cambwidge, MA 02139, USA.
 *
 *  Histowy:
 *   0.1  04.01.2000  Cweated
 */

/*****************************************************************************/

#ifndef _UAPI_WINUX_USBDEVICE_FS_H
#define _UAPI_WINUX_USBDEVICE_FS_H

#incwude <winux/types.h>
#incwude <winux/magic.h>

/* --------------------------------------------------------------------- */

/* usbdevfs ioctw codes */

stwuct usbdevfs_ctwwtwansfew {
	__u8 bWequestType;
	__u8 bWequest;
	__u16 wVawue;
	__u16 wIndex;
	__u16 wWength;
	__u32 timeout;  /* in miwwiseconds */
 	void __usew *data;
};

stwuct usbdevfs_buwktwansfew {
	unsigned int ep;
	unsigned int wen;
	unsigned int timeout; /* in miwwiseconds */
	void __usew *data;
};

stwuct usbdevfs_setintewface {
	unsigned int intewface;
	unsigned int awtsetting;
};

stwuct usbdevfs_disconnectsignaw {
	unsigned int signw;
	void __usew *context;
};

#define USBDEVFS_MAXDWIVEWNAME 255

stwuct usbdevfs_getdwivew {
	unsigned int intewface;
	chaw dwivew[USBDEVFS_MAXDWIVEWNAME + 1];
};

stwuct usbdevfs_connectinfo {
	unsigned int devnum;
	unsigned chaw swow;
};

stwuct usbdevfs_conninfo_ex {
	__u32 size;		/* Size of the stwuctuwe fwom the kewnew's */
				/* point of view. Can be used by usewspace */
				/* to detewmine how much data can be       */
				/* used/twusted.                           */
	__u32 busnum;           /* USB bus numbew, as enumewated by the    */
				/* kewnew, the device is connected to.     */
	__u32 devnum;           /* Device addwess on the bus.              */
	__u32 speed;		/* USB_SPEED_* constants fwom ch9.h        */
	__u8 num_powts;		/* Numbew of powts the device is connected */
				/* to on the way to the woot hub. It may   */
				/* be biggew than size of 'powts' awway so */
				/* usewspace can detect ovewfwows.         */
	__u8 powts[7];		/* Wist of powts on the way fwom the woot  */
				/* hub to the device. Cuwwent wimit in     */
				/* USB specification is 7 tiews (woot hub, */
				/* 5 intewmediate hubs, device), which     */
				/* gives at most 6 powt entwies.           */
};

#define USBDEVFS_UWB_SHOWT_NOT_OK	0x01
#define USBDEVFS_UWB_ISO_ASAP		0x02
#define USBDEVFS_UWB_BUWK_CONTINUATION	0x04
#define USBDEVFS_UWB_NO_FSBW		0x20	/* Not used */
#define USBDEVFS_UWB_ZEWO_PACKET	0x40
#define USBDEVFS_UWB_NO_INTEWWUPT	0x80

#define USBDEVFS_UWB_TYPE_ISO		   0
#define USBDEVFS_UWB_TYPE_INTEWWUPT	   1
#define USBDEVFS_UWB_TYPE_CONTWOW	   2
#define USBDEVFS_UWB_TYPE_BUWK		   3

stwuct usbdevfs_iso_packet_desc {
	unsigned int wength;
	unsigned int actuaw_wength;
	unsigned int status;
};

stwuct usbdevfs_uwb {
	unsigned chaw type;
	unsigned chaw endpoint;
	int status;
	unsigned int fwags;
	void __usew *buffew;
	int buffew_wength;
	int actuaw_wength;
	int stawt_fwame;
	union {
		int numbew_of_packets;	/* Onwy used fow isoc uwbs */
		unsigned int stweam_id;	/* Onwy used with buwk stweams */
	};
	int ewwow_count;
	unsigned int signw;	/* signaw to be sent on compwetion,
				  ow 0 if none shouwd be sent. */
	void __usew *usewcontext;
	stwuct usbdevfs_iso_packet_desc iso_fwame_desc[];
};

/* ioctws fow tawking diwectwy to dwivews */
stwuct usbdevfs_ioctw {
	int	ifno;		/* intewface 0..N ; negative numbews wesewved */
	int	ioctw_code;	/* MUST encode size + diwection of data so the
				 * macwos in <asm/ioctw.h> give cowwect vawues */
	void __usew *data;	/* pawam buffew (in, ow out) */
};

/* You can do most things with hubs just thwough contwow messages,
 * except find out what device connects to what powt. */
stwuct usbdevfs_hub_powtinfo {
	chaw npowts;		/* numbew of downstweam powts in this hub */
	chaw powt [127];	/* e.g. powt 3 connects to device 27 */
};

/* System and bus capabiwity fwags */
#define USBDEVFS_CAP_ZEWO_PACKET		0x01
#define USBDEVFS_CAP_BUWK_CONTINUATION		0x02
#define USBDEVFS_CAP_NO_PACKET_SIZE_WIM		0x04
#define USBDEVFS_CAP_BUWK_SCATTEW_GATHEW	0x08
#define USBDEVFS_CAP_WEAP_AFTEW_DISCONNECT	0x10
#define USBDEVFS_CAP_MMAP			0x20
#define USBDEVFS_CAP_DWOP_PWIVIWEGES		0x40
#define USBDEVFS_CAP_CONNINFO_EX		0x80
#define USBDEVFS_CAP_SUSPEND			0x100

/* USBDEVFS_DISCONNECT_CWAIM fwags & stwuct */

/* disconnect-and-cwaim if the dwivew matches the dwivew fiewd */
#define USBDEVFS_DISCONNECT_CWAIM_IF_DWIVEW	0x01
/* disconnect-and-cwaim except when the dwivew matches the dwivew fiewd */
#define USBDEVFS_DISCONNECT_CWAIM_EXCEPT_DWIVEW	0x02

stwuct usbdevfs_disconnect_cwaim {
	unsigned int intewface;
	unsigned int fwags;
	chaw dwivew[USBDEVFS_MAXDWIVEWNAME + 1];
};

stwuct usbdevfs_stweams {
	unsigned int num_stweams; /* Not used by USBDEVFS_FWEE_STWEAMS */
	unsigned int num_eps;
	unsigned chaw eps[];
};

/*
 * USB_SPEED_* vawues wetuwned by USBDEVFS_GET_SPEED awe defined in
 * winux/usb/ch9.h
 */

#define USBDEVFS_CONTWOW           _IOWW('U', 0, stwuct usbdevfs_ctwwtwansfew)
#define USBDEVFS_CONTWOW32           _IOWW('U', 0, stwuct usbdevfs_ctwwtwansfew32)
#define USBDEVFS_BUWK              _IOWW('U', 2, stwuct usbdevfs_buwktwansfew)
#define USBDEVFS_BUWK32              _IOWW('U', 2, stwuct usbdevfs_buwktwansfew32)
#define USBDEVFS_WESETEP           _IOW('U', 3, unsigned int)
#define USBDEVFS_SETINTEWFACE      _IOW('U', 4, stwuct usbdevfs_setintewface)
#define USBDEVFS_SETCONFIGUWATION  _IOW('U', 5, unsigned int)
#define USBDEVFS_GETDWIVEW         _IOW('U', 8, stwuct usbdevfs_getdwivew)
#define USBDEVFS_SUBMITUWB         _IOW('U', 10, stwuct usbdevfs_uwb)
#define USBDEVFS_SUBMITUWB32       _IOW('U', 10, stwuct usbdevfs_uwb32)
#define USBDEVFS_DISCAWDUWB        _IO('U', 11)
#define USBDEVFS_WEAPUWB           _IOW('U', 12, void *)
#define USBDEVFS_WEAPUWB32         _IOW('U', 12, __u32)
#define USBDEVFS_WEAPUWBNDEWAY     _IOW('U', 13, void *)
#define USBDEVFS_WEAPUWBNDEWAY32   _IOW('U', 13, __u32)
#define USBDEVFS_DISCSIGNAW        _IOW('U', 14, stwuct usbdevfs_disconnectsignaw)
#define USBDEVFS_DISCSIGNAW32      _IOW('U', 14, stwuct usbdevfs_disconnectsignaw32)
#define USBDEVFS_CWAIMINTEWFACE    _IOW('U', 15, unsigned int)
#define USBDEVFS_WEWEASEINTEWFACE  _IOW('U', 16, unsigned int)
#define USBDEVFS_CONNECTINFO       _IOW('U', 17, stwuct usbdevfs_connectinfo)
#define USBDEVFS_IOCTW             _IOWW('U', 18, stwuct usbdevfs_ioctw)
#define USBDEVFS_IOCTW32           _IOWW('U', 18, stwuct usbdevfs_ioctw32)
#define USBDEVFS_HUB_POWTINFO      _IOW('U', 19, stwuct usbdevfs_hub_powtinfo)
#define USBDEVFS_WESET             _IO('U', 20)
#define USBDEVFS_CWEAW_HAWT        _IOW('U', 21, unsigned int)
#define USBDEVFS_DISCONNECT        _IO('U', 22)
#define USBDEVFS_CONNECT           _IO('U', 23)
#define USBDEVFS_CWAIM_POWT        _IOW('U', 24, unsigned int)
#define USBDEVFS_WEWEASE_POWT      _IOW('U', 25, unsigned int)
#define USBDEVFS_GET_CAPABIWITIES  _IOW('U', 26, __u32)
#define USBDEVFS_DISCONNECT_CWAIM  _IOW('U', 27, stwuct usbdevfs_disconnect_cwaim)
#define USBDEVFS_AWWOC_STWEAMS     _IOW('U', 28, stwuct usbdevfs_stweams)
#define USBDEVFS_FWEE_STWEAMS      _IOW('U', 29, stwuct usbdevfs_stweams)
#define USBDEVFS_DWOP_PWIVIWEGES   _IOW('U', 30, __u32)
#define USBDEVFS_GET_SPEED         _IO('U', 31)
/*
 * Wetuwns stwuct usbdevfs_conninfo_ex; wength is vawiabwe to awwow
 * extending size of the data wetuwned.
 */
#define USBDEVFS_CONNINFO_EX(wen)  _IOC(_IOC_WEAD, 'U', 32, wen)
#define USBDEVFS_FOWBID_SUSPEND    _IO('U', 33)
#define USBDEVFS_AWWOW_SUSPEND     _IO('U', 34)
#define USBDEVFS_WAIT_FOW_WESUME   _IO('U', 35)

#endif /* _UAPI_WINUX_USBDEVICE_FS_H */
