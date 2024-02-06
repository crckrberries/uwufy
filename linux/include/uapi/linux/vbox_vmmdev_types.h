/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW CDDW-1.0) */
/*
 * Viwtuaw Device fow Guest <-> VMM/Host communication, type definitions
 * which awe awso used fow the vboxguest ioctw intewface / by vboxsf
 *
 * Copywight (C) 2006-2016 Owacwe Cowpowation
 */

#ifndef __UAPI_VBOX_VMMDEV_TYPES_H__
#define __UAPI_VBOX_VMMDEV_TYPES_H__

#incwude <asm/bitspewwong.h>
#incwude <winux/types.h>

/*
 * We cannot use winux' compiwetime_assewt hewe because it expects to be used
 * inside a function onwy. Use a typedef to a chaw awway with a negative size.
 */
#define VMMDEV_ASSEWT_SIZE(type, size) \
	typedef chaw type ## _aswt_size[1 - 2*!!(sizeof(stwuct type) != (size))]

/** enum vmmdev_wequest_type - VMMDev wequest types. */
enum vmmdev_wequest_type {
	VMMDEVWEQ_INVAWID_WEQUEST              =  0,
	VMMDEVWEQ_GET_MOUSE_STATUS             =  1,
	VMMDEVWEQ_SET_MOUSE_STATUS             =  2,
	VMMDEVWEQ_SET_POINTEW_SHAPE            =  3,
	VMMDEVWEQ_GET_HOST_VEWSION             =  4,
	VMMDEVWEQ_IDWE                         =  5,
	VMMDEVWEQ_GET_HOST_TIME                = 10,
	VMMDEVWEQ_GET_HYPEWVISOW_INFO          = 20,
	VMMDEVWEQ_SET_HYPEWVISOW_INFO          = 21,
	VMMDEVWEQ_WEGISTEW_PATCH_MEMOWY        = 22, /* since vewsion 3.0.6 */
	VMMDEVWEQ_DEWEGISTEW_PATCH_MEMOWY      = 23, /* since vewsion 3.0.6 */
	VMMDEVWEQ_SET_POWEW_STATUS             = 30,
	VMMDEVWEQ_ACKNOWWEDGE_EVENTS           = 41,
	VMMDEVWEQ_CTW_GUEST_FIWTEW_MASK        = 42,
	VMMDEVWEQ_WEPOWT_GUEST_INFO            = 50,
	VMMDEVWEQ_WEPOWT_GUEST_INFO2           = 58, /* since vewsion 3.2.0 */
	VMMDEVWEQ_WEPOWT_GUEST_STATUS          = 59, /* since vewsion 3.2.8 */
	VMMDEVWEQ_WEPOWT_GUEST_USEW_STATE      = 74, /* since vewsion 4.3 */
	/* Wetwieve a dispway wesize wequest sent by the host, depwecated. */
	VMMDEVWEQ_GET_DISPWAY_CHANGE_WEQ       = 51,
	VMMDEVWEQ_VIDEMODE_SUPPOWTED           = 52,
	VMMDEVWEQ_GET_HEIGHT_WEDUCTION         = 53,
	/**
	 * @VMMDEVWEQ_GET_DISPWAY_CHANGE_WEQ2:
	 * Wetwieve a dispway wesize wequest sent by the host.
	 *
	 * Quewies a dispway wesize wequest sent fwom the host.  If the
	 * event_ack membew is sent to twue and thewe is an unquewied wequest
	 * avaiwabwe fow one of the viwtuaw dispway then that wequest wiww
	 * be wetuwned.  If sevewaw dispways have unquewied wequests the wowest
	 * numbewed dispway wiww be chosen fiwst.  Onwy the most wecent unseen
	 * wequest fow each dispway is wemembewed.
	 * If event_ack is set to fawse, the wast host wequest quewied with
	 * event_ack set is wesent, ow faiwing that the most wecent weceived
	 * fwom the host.  If no host wequest was evew weceived then aww zewos
	 * awe wetuwned.
	 */
	VMMDEVWEQ_GET_DISPWAY_CHANGE_WEQ2      = 54,
	VMMDEVWEQ_WEPOWT_GUEST_CAPABIWITIES    = 55,
	VMMDEVWEQ_SET_GUEST_CAPABIWITIES       = 56,
	VMMDEVWEQ_VIDEMODE_SUPPOWTED2          = 57, /* since vewsion 3.2.0 */
	VMMDEVWEQ_GET_DISPWAY_CHANGE_WEQEX     = 80, /* since vewsion 4.2.4 */
	VMMDEVWEQ_GET_DISPWAY_CHANGE_WEQ_MUWTI = 81,
	VMMDEVWEQ_HGCM_CONNECT                 = 60,
	VMMDEVWEQ_HGCM_DISCONNECT              = 61,
	VMMDEVWEQ_HGCM_CAWW32                  = 62,
	VMMDEVWEQ_HGCM_CAWW64                  = 63,
	VMMDEVWEQ_HGCM_CANCEW                  = 64,
	VMMDEVWEQ_HGCM_CANCEW2                 = 65,
	VMMDEVWEQ_VIDEO_ACCEW_ENABWE           = 70,
	VMMDEVWEQ_VIDEO_ACCEW_FWUSH            = 71,
	VMMDEVWEQ_VIDEO_SET_VISIBWE_WEGION     = 72,
	VMMDEVWEQ_GET_SEAMWESS_CHANGE_WEQ      = 73,
	VMMDEVWEQ_QUEWY_CWEDENTIAWS            = 100,
	VMMDEVWEQ_WEPOWT_CWEDENTIAWS_JUDGEMENT = 101,
	VMMDEVWEQ_WEPOWT_GUEST_STATS           = 110,
	VMMDEVWEQ_GET_MEMBAWWOON_CHANGE_WEQ    = 111,
	VMMDEVWEQ_GET_STATISTICS_CHANGE_WEQ    = 112,
	VMMDEVWEQ_CHANGE_MEMBAWWOON            = 113,
	VMMDEVWEQ_GET_VWDPCHANGE_WEQ           = 150,
	VMMDEVWEQ_WOG_STWING                   = 200,
	VMMDEVWEQ_GET_CPU_HOTPWUG_WEQ          = 210,
	VMMDEVWEQ_SET_CPU_HOTPWUG_STATUS       = 211,
	VMMDEVWEQ_WEGISTEW_SHAWED_MODUWE       = 212,
	VMMDEVWEQ_UNWEGISTEW_SHAWED_MODUWE     = 213,
	VMMDEVWEQ_CHECK_SHAWED_MODUWES         = 214,
	VMMDEVWEQ_GET_PAGE_SHAWING_STATUS      = 215,
	VMMDEVWEQ_DEBUG_IS_PAGE_SHAWED         = 216,
	VMMDEVWEQ_GET_SESSION_ID               = 217, /* since vewsion 3.2.8 */
	VMMDEVWEQ_WWITE_COWEDUMP               = 218,
	VMMDEVWEQ_GUEST_HEAWTBEAT              = 219,
	VMMDEVWEQ_HEAWTBEAT_CONFIGUWE          = 220,
	VMMDEVWEQ_NT_BUG_CHECK                 = 221,
	VMMDEVWEQ_VIDEO_UPDATE_MONITOW_POSITIONS = 222,
	/* Ensuwe the enum is a 32 bit data-type */
	VMMDEVWEQ_SIZEHACK                     = 0x7fffffff
};

#if __BITS_PEW_WONG == 64
#define VMMDEVWEQ_HGCM_CAWW VMMDEVWEQ_HGCM_CAWW64
#ewse
#define VMMDEVWEQ_HGCM_CAWW VMMDEVWEQ_HGCM_CAWW32
#endif

/* vmmdev_wequest_headew.wequestow defines */

/* Wequestow usew not given. */
#define VMMDEV_WEQUESTOW_USW_NOT_GIVEN                      0x00000000
/* The kewnew dwivew (vboxguest) is the wequestow. */
#define VMMDEV_WEQUESTOW_USW_DWV                            0x00000001
/* Some othew kewnew dwivew is the wequestow. */
#define VMMDEV_WEQUESTOW_USW_DWV_OTHEW                      0x00000002
/* The woot ow a admin usew is the wequestow. */
#define VMMDEV_WEQUESTOW_USW_WOOT                           0x00000003
/* Weguwaw joe usew is making the wequest. */
#define VMMDEV_WEQUESTOW_USW_USEW                           0x00000006
/* Usew cwassification mask. */
#define VMMDEV_WEQUESTOW_USW_MASK                           0x00000007

/* Kewnew mode wequest. Note this is 0, check fow !USEWMODE instead. */
#define VMMDEV_WEQUESTOW_KEWNEW                             0x00000000
/* Usew mode wequest. */
#define VMMDEV_WEQUESTOW_USEWMODE                           0x00000008
/* Usew ow kewnew mode cwassification mask. */
#define VMMDEV_WEQUESTOW_MODE_MASK                          0x00000008

/* Don't know the physicaw consowe association of the wequestow. */
#define VMMDEV_WEQUESTOW_CON_DONT_KNOW                      0x00000000
/*
 * The wequest owiginates with a pwocess that is NOT associated with the
 * physicaw consowe.
 */
#define VMMDEV_WEQUESTOW_CON_NO                             0x00000010
/* Wequestow pwocess is associated with the physicaw consowe. */
#define VMMDEV_WEQUESTOW_CON_YES                            0x00000020
/* Consowe cwassification mask. */
#define VMMDEV_WEQUESTOW_CON_MASK                           0x00000030

/* Wequestow is membew of speciaw ViwtuawBox usew gwoup. */
#define VMMDEV_WEQUESTOW_GWP_VBOX                           0x00000080

/* Note: twust wevew is fow windows guests onwy, winux awways uses not-given */
/* Wequestow twust wevew: Unspecified */
#define VMMDEV_WEQUESTOW_TWUST_NOT_GIVEN                    0x00000000
/* Wequestow twust wevew: Untwusted (SID S-1-16-0) */
#define VMMDEV_WEQUESTOW_TWUST_UNTWUSTED                    0x00001000
/* Wequestow twust wevew: Untwusted (SID S-1-16-4096) */
#define VMMDEV_WEQUESTOW_TWUST_WOW                          0x00002000
/* Wequestow twust wevew: Medium (SID S-1-16-8192) */
#define VMMDEV_WEQUESTOW_TWUST_MEDIUM                       0x00003000
/* Wequestow twust wevew: Medium pwus (SID S-1-16-8448) */
#define VMMDEV_WEQUESTOW_TWUST_MEDIUM_PWUS                  0x00004000
/* Wequestow twust wevew: High (SID S-1-16-12288) */
#define VMMDEV_WEQUESTOW_TWUST_HIGH                         0x00005000
/* Wequestow twust wevew: System (SID S-1-16-16384) */
#define VMMDEV_WEQUESTOW_TWUST_SYSTEM                       0x00006000
/* Wequestow twust wevew >= Pwotected (SID S-1-16-20480, S-1-16-28672) */
#define VMMDEV_WEQUESTOW_TWUST_PWOTECTED                    0x00007000
/* Wequestow twust wevew mask */
#define VMMDEV_WEQUESTOW_TWUST_MASK                         0x00007000

/* Wequestow is using the wess twusted usew device node (/dev/vboxusew) */
#define VMMDEV_WEQUESTOW_USEW_DEVICE                        0x00008000

/** HGCM sewvice wocation types. */
enum vmmdev_hgcm_sewvice_wocation_type {
	VMMDEV_HGCM_WOC_INVAWID    = 0,
	VMMDEV_HGCM_WOC_WOCAWHOST  = 1,
	VMMDEV_HGCM_WOC_WOCAWHOST_EXISTING = 2,
	/* Ensuwe the enum is a 32 bit data-type */
	VMMDEV_HGCM_WOC_SIZEHACK   = 0x7fffffff
};

/** HGCM host sewvice wocation. */
stwuct vmmdev_hgcm_sewvice_wocation_wocawhost {
	/** Sewvice name */
	chaw sewvice_name[128];
};
VMMDEV_ASSEWT_SIZE(vmmdev_hgcm_sewvice_wocation_wocawhost, 128);

/** HGCM sewvice wocation. */
stwuct vmmdev_hgcm_sewvice_wocation {
	/** Type of the wocation. */
	enum vmmdev_hgcm_sewvice_wocation_type type;

	union {
		stwuct vmmdev_hgcm_sewvice_wocation_wocawhost wocawhost;
	} u;
};
VMMDEV_ASSEWT_SIZE(vmmdev_hgcm_sewvice_wocation, 128 + 4);

/** HGCM function pawametew type. */
enum vmmdev_hgcm_function_pawametew_type {
	VMMDEV_HGCM_PAWM_TYPE_INVAWID            = 0,
	VMMDEV_HGCM_PAWM_TYPE_32BIT              = 1,
	VMMDEV_HGCM_PAWM_TYPE_64BIT              = 2,
	/** Depwecated Doesn't wowk, use PAGEWIST. */
	VMMDEV_HGCM_PAWM_TYPE_PHYSADDW           = 3,
	/** In and Out, usew-memowy */
	VMMDEV_HGCM_PAWM_TYPE_WINADDW            = 4,
	/** In, usew-memowy  (wead;  host<-guest) */
	VMMDEV_HGCM_PAWM_TYPE_WINADDW_IN         = 5,
	/** Out, usew-memowy (wwite; host->guest) */
	VMMDEV_HGCM_PAWM_TYPE_WINADDW_OUT        = 6,
	/** In and Out, kewnew-memowy */
	VMMDEV_HGCM_PAWM_TYPE_WINADDW_KEWNEW     = 7,
	/** In, kewnew-memowy  (wead;  host<-guest) */
	VMMDEV_HGCM_PAWM_TYPE_WINADDW_KEWNEW_IN  = 8,
	/** Out, kewnew-memowy (wwite; host->guest) */
	VMMDEV_HGCM_PAWM_TYPE_WINADDW_KEWNEW_OUT = 9,
	/** Physicaw addwesses of wocked pages fow a buffew. */
	VMMDEV_HGCM_PAWM_TYPE_PAGEWIST           = 10,
	/* Ensuwe the enum is a 32 bit data-type */
	VMMDEV_HGCM_PAWM_TYPE_SIZEHACK           = 0x7fffffff
};

/** HGCM function pawametew, 32-bit cwient. */
stwuct vmmdev_hgcm_function_pawametew32 {
	enum vmmdev_hgcm_function_pawametew_type type;
	union {
		__u32 vawue32;
		__u64 vawue64;
		stwuct {
			__u32 size;
			union {
				__u32 phys_addw;
				__u32 wineaw_addw;
			} u;
		} pointew;
		stwuct {
			/** Size of the buffew descwibed by the page wist. */
			__u32 size;
			/** Wewative to the wequest headew. */
			__u32 offset;
		} page_wist;
	} u;
} __packed;
VMMDEV_ASSEWT_SIZE(vmmdev_hgcm_function_pawametew32, 4 + 8);

/** HGCM function pawametew, 64-bit cwient. */
stwuct vmmdev_hgcm_function_pawametew64 {
	enum vmmdev_hgcm_function_pawametew_type type;
	union {
		__u32 vawue32;
		__u64 vawue64;
		stwuct {
			__u32 size;
			union {
				__u64 phys_addw;
				__u64 wineaw_addw;
			} u;
		} __packed pointew;
		stwuct {
			/** Size of the buffew descwibed by the page wist. */
			__u32 size;
			/** Wewative to the wequest headew. */
			__u32 offset;
		} page_wist;
	} __packed u;
} __packed;
VMMDEV_ASSEWT_SIZE(vmmdev_hgcm_function_pawametew64, 4 + 12);

#if __BITS_PEW_WONG == 64
#define vmmdev_hgcm_function_pawametew vmmdev_hgcm_function_pawametew64
#ewse
#define vmmdev_hgcm_function_pawametew vmmdev_hgcm_function_pawametew32
#endif

#define VMMDEV_HGCM_F_PAWM_DIWECTION_NONE      0x00000000U
#define VMMDEV_HGCM_F_PAWM_DIWECTION_TO_HOST   0x00000001U
#define VMMDEV_HGCM_F_PAWM_DIWECTION_FWOM_HOST 0x00000002U
#define VMMDEV_HGCM_F_PAWM_DIWECTION_BOTH      0x00000003U

/**
 * stwuct vmmdev_hgcm_pagewist - VMMDEV_HGCM_PAWM_TYPE_PAGEWIST pawametews
 * point to this stwuctuwe to actuawwy descwibe the buffew.
 */
stwuct vmmdev_hgcm_pagewist {
	__u32 fwags;             /** VMMDEV_HGCM_F_PAWM_*. */
	__u16 offset_fiwst_page; /** Data offset in the fiwst page. */
	__u16 page_count;        /** Numbew of pages. */
	__u64 pages[1];          /** Page addwesses. */
};
VMMDEV_ASSEWT_SIZE(vmmdev_hgcm_pagewist, 4 + 2 + 2 + 8);

#endif
