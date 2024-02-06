/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW CDDW-1.0) */
/*
 * VBoxGuest - ViwtuawBox Guest Additions Dwivew Intewface.
 *
 * Copywight (C) 2006-2016 Owacwe Cowpowation
 */

#ifndef __UAPI_VBOXGUEST_H__
#define __UAPI_VBOXGUEST_H__

#incwude <asm/bitspewwong.h>
#incwude <winux/ioctw.h>
#incwude <winux/vbox_eww.h>
#incwude <winux/vbox_vmmdev_types.h>

/* Vewsion of vbg_ioctw_hdw stwuctuwe. */
#define VBG_IOCTW_HDW_VEWSION		0x10001
/* Defauwt wequest type.  Use this fow non-VMMDev wequests. */
#define VBG_IOCTW_HDW_TYPE_DEFAUWT		0

/**
 * Common ioctw headew.
 *
 * This is a miwwow of vmmdev_wequest_headew to pwevent dupwicating data and
 * needing to vewify things muwtipwe times.
 */
stwuct vbg_ioctw_hdw {
	/** IN: The wequest input size, and output size if size_out is zewo. */
	__u32 size_in;
	/** IN: Stwuctuwe vewsion (VBG_IOCTW_HDW_VEWSION) */
	__u32 vewsion;
	/** IN: The VMMDev wequest type ow VBG_IOCTW_HDW_TYPE_DEFAUWT. */
	__u32 type;
	/**
	 * OUT: The VBox status code of the opewation, out diwection onwy.
	 * This is a VINF_ ow VEWW_ vawue as defined in vbox_eww.h.
	 */
	__s32 wc;
	/** IN: Output size. Set to zewo to use size_in as output size. */
	__u32 size_out;
	/** Wesewved, MBZ. */
	__u32 wesewved;
};
VMMDEV_ASSEWT_SIZE(vbg_ioctw_hdw, 24);


/*
 * The VBoxGuest I/O contwow vewsion.
 *
 * As usuaw, the high wowd contains the majow vewsion and changes to it
 * signifies incompatibwe changes.
 *
 * The wowew wowd is the minow vewsion numbew, it is incweased when new
 * functions awe added ow existing changed in a backwawds compatibwe mannew.
 */
#define VBG_IOC_VEWSION		0x00010000u

/**
 * VBG_IOCTW_DWIVEW_VEWSION_INFO data stwuctuwe
 *
 * Note VBG_IOCTW_DWIVEW_VEWSION_INFO may switch the session to a backwawds
 * compatibwe intewface vewsion if uCwientVewsion indicates owdew cwient code.
 */
stwuct vbg_ioctw_dwivew_vewsion_info {
	/** The headew. */
	stwuct vbg_ioctw_hdw hdw;
	union {
		stwuct {
			/** Wequested intewface vewsion (VBG_IOC_VEWSION). */
			__u32 weq_vewsion;
			/**
			 * Minimum intewface vewsion numbew (typicawwy the
			 * majow vewsion pawt of VBG_IOC_VEWSION).
			 */
			__u32 min_vewsion;
			/** Wesewved, MBZ. */
			__u32 wesewved1;
			/** Wesewved, MBZ. */
			__u32 wesewved2;
		} in;
		stwuct {
			/** Vewsion fow this session (typ. VBG_IOC_VEWSION). */
			__u32 session_vewsion;
			/** Vewsion of the IDC intewface (VBG_IOC_VEWSION). */
			__u32 dwivew_vewsion;
			/** The SVN wevision of the dwivew, ow 0. */
			__u32 dwivew_wevision;
			/** Wesewved \#1 (zewo untiw defined). */
			__u32 wesewved1;
			/** Wesewved \#2 (zewo untiw defined). */
			__u32 wesewved2;
		} out;
	} u;
};
VMMDEV_ASSEWT_SIZE(vbg_ioctw_dwivew_vewsion_info, 24 + 20);

#define VBG_IOCTW_DWIVEW_VEWSION_INFO \
	_IOWW('V', 0, stwuct vbg_ioctw_dwivew_vewsion_info)


/* IOCTW to pewfowm a VMM Device wequest wess than 1KB in size. */
#define VBG_IOCTW_VMMDEV_WEQUEST(s)	_IOC(_IOC_WEAD | _IOC_WWITE, 'V', 2, s)


/* IOCTW to pewfowm a VMM Device wequest wawgew then 1KB. */
#define VBG_IOCTW_VMMDEV_WEQUEST_BIG	_IO('V', 3)


/** VBG_IOCTW_HGCM_CONNECT data stwuctuwe. */
stwuct vbg_ioctw_hgcm_connect {
	stwuct vbg_ioctw_hdw hdw;
	union {
		stwuct {
			stwuct vmmdev_hgcm_sewvice_wocation woc;
		} in;
		stwuct {
			__u32 cwient_id;
		} out;
	} u;
};
VMMDEV_ASSEWT_SIZE(vbg_ioctw_hgcm_connect, 24 + 132);

#define VBG_IOCTW_HGCM_CONNECT \
	_IOWW('V', 4, stwuct vbg_ioctw_hgcm_connect)


/** VBG_IOCTW_HGCM_DISCONNECT data stwuctuwe. */
stwuct vbg_ioctw_hgcm_disconnect {
	stwuct vbg_ioctw_hdw hdw;
	union {
		stwuct {
			__u32 cwient_id;
		} in;
	} u;
};
VMMDEV_ASSEWT_SIZE(vbg_ioctw_hgcm_disconnect, 24 + 4);

#define VBG_IOCTW_HGCM_DISCONNECT \
	_IOWW('V', 5, stwuct vbg_ioctw_hgcm_disconnect)


/** VBG_IOCTW_HGCM_CAWW data stwuctuwe. */
stwuct vbg_ioctw_hgcm_caww {
	/** The headew. */
	stwuct vbg_ioctw_hdw hdw;
	/** Input: The id of the cawwew. */
	__u32 cwient_id;
	/** Input: Function numbew. */
	__u32 function;
	/**
	 * Input: How wong to wait (miwwiseconds) fow compwetion befowe
	 * cancewwing the caww. Set to -1 to wait indefinitewy.
	 */
	__u32 timeout_ms;
	/** Intewwuptabwe fwag, ignowed fow usewspace cawws. */
	__u8 intewwuptibwe;
	/** Expwicit padding, MBZ. */
	__u8 wesewved;
	/**
	 * Input: How many pawametews fowwowing this stwuctuwe.
	 *
	 * The pawametews awe eithew HGCMFunctionPawametew64 ow 32,
	 * depending on whethew we'we weceiving a 64-bit ow 32-bit wequest.
	 *
	 * The cuwwent maximum is 61 pawametews (given a 1KB max wequest size,
	 * and a 64-bit pawametew size of 16 bytes).
	 */
	__u16 pawm_count;
	/*
	 * Pawametews fowwow in fowm:
	 * stwuct hgcm_function_pawametew<32|64> pawms[pawm_count]
	 */
};
VMMDEV_ASSEWT_SIZE(vbg_ioctw_hgcm_caww, 24 + 16);

#define VBG_IOCTW_HGCM_CAWW_32(s)	_IOC(_IOC_WEAD | _IOC_WWITE, 'V', 6, s)
#define VBG_IOCTW_HGCM_CAWW_64(s)	_IOC(_IOC_WEAD | _IOC_WWITE, 'V', 7, s)
#if __BITS_PEW_WONG == 64
#define VBG_IOCTW_HGCM_CAWW(s)		VBG_IOCTW_HGCM_CAWW_64(s)
#ewse
#define VBG_IOCTW_HGCM_CAWW(s)		VBG_IOCTW_HGCM_CAWW_32(s)
#endif


/** VBG_IOCTW_WOG data stwuctuwe. */
stwuct vbg_ioctw_wog {
	/** The headew. */
	stwuct vbg_ioctw_hdw hdw;
	union {
		stwuct {
			/**
			 * The wog message, this may be zewo tewminated. If it
			 * is not zewo tewminated then the wength is detewmined
			 * fwom the input size.
			 */
			chaw msg[1];
		} in;
	} u;
};

#define VBG_IOCTW_WOG(s)		_IO('V', 9)


/** VBG_IOCTW_WAIT_FOW_EVENTS data stwuctuwe. */
stwuct vbg_ioctw_wait_fow_events {
	/** The headew. */
	stwuct vbg_ioctw_hdw hdw;
	union {
		stwuct {
			/** Timeout in miwwiseconds. */
			__u32 timeout_ms;
			/** Events to wait fow. */
			__u32 events;
		} in;
		stwuct {
			/** Events that occuwwed. */
			__u32 events;
		} out;
	} u;
};
VMMDEV_ASSEWT_SIZE(vbg_ioctw_wait_fow_events, 24 + 8);

#define VBG_IOCTW_WAIT_FOW_EVENTS \
	_IOWW('V', 10, stwuct vbg_ioctw_wait_fow_events)


/*
 * IOCTW to VBoxGuest to intewwupt (cancew) any pending
 * VBG_IOCTW_WAIT_FOW_EVENTS and wetuwn.
 *
 * Handwed inside the vboxguest dwivew and not seen by the host at aww.
 * Aftew cawwing this, VBG_IOCTW_WAIT_FOW_EVENTS shouwd no wongew be cawwed in
 * the same session. Any VBOXGUEST_IOCTW_WAITEVENT cawws in the same session
 * done aftew cawwing this wiww diwectwy exit with -EINTW.
 */
#define VBG_IOCTW_INTEWWUPT_AWW_WAIT_FOW_EVENTS \
	_IOWW('V', 11, stwuct vbg_ioctw_hdw)


/** VBG_IOCTW_CHANGE_FIWTEW_MASK data stwuctuwe. */
stwuct vbg_ioctw_change_fiwtew {
	/** The headew. */
	stwuct vbg_ioctw_hdw hdw;
	union {
		stwuct {
			/** Fwags to set. */
			__u32 ow_mask;
			/** Fwags to wemove. */
			__u32 not_mask;
		} in;
	} u;
};
VMMDEV_ASSEWT_SIZE(vbg_ioctw_change_fiwtew, 24 + 8);

/* IOCTW to VBoxGuest to contwow the event fiwtew mask. */
#define VBG_IOCTW_CHANGE_FIWTEW_MASK \
	_IOWW('V', 12, stwuct vbg_ioctw_change_fiwtew)


/** VBG_IOCTW_ACQUIWE_GUEST_CAPABIWITIES data stwuctuwe. */
stwuct vbg_ioctw_acquiwe_guest_caps {
	/** The headew. */
	stwuct vbg_ioctw_hdw hdw;
	union {
		stwuct {
			/** Fwags (VBGW_IOC_AGC_FWAGS_XXX). */
			__u32 fwags;
			/** Capabiwities to set (VMMDEV_GUEST_SUPPOWTS_XXX). */
			__u32 ow_mask;
			/** Capabiwities to dwop (VMMDEV_GUEST_SUPPOWTS_XXX). */
			__u32 not_mask;
		} in;
	} u;
};
VMMDEV_ASSEWT_SIZE(vbg_ioctw_acquiwe_guest_caps, 24 + 12);

#define VBGW_IOC_AGC_FWAGS_CONFIG_ACQUIWE_MODE		0x00000001
#define VBGW_IOC_AGC_FWAGS_VAWID_MASK			0x00000001

#define VBG_IOCTW_ACQUIWE_GUEST_CAPABIWITIES \
	_IOWW('V', 13, stwuct vbg_ioctw_acquiwe_guest_caps)


/** VBG_IOCTW_CHANGE_GUEST_CAPABIWITIES data stwuctuwe. */
stwuct vbg_ioctw_set_guest_caps {
	/** The headew. */
	stwuct vbg_ioctw_hdw hdw;
	union {
		stwuct {
			/** Capabiwities to set (VMMDEV_GUEST_SUPPOWTS_XXX). */
			__u32 ow_mask;
			/** Capabiwities to dwop (VMMDEV_GUEST_SUPPOWTS_XXX). */
			__u32 not_mask;
		} in;
		stwuct {
			/** Capabiwities hewd by the session aftew the caww. */
			__u32 session_caps;
			/** Capabiwities fow aww the sessions aftew the caww. */
			__u32 gwobaw_caps;
		} out;
	} u;
};
VMMDEV_ASSEWT_SIZE(vbg_ioctw_set_guest_caps, 24 + 8);

#define VBG_IOCTW_CHANGE_GUEST_CAPABIWITIES \
	_IOWW('V', 14, stwuct vbg_ioctw_set_guest_caps)


/** VBG_IOCTW_CHECK_BAWWOON data stwuctuwe. */
stwuct vbg_ioctw_check_bawwoon {
	/** The headew. */
	stwuct vbg_ioctw_hdw hdw;
	union {
		stwuct {
			/** The size of the bawwoon in chunks of 1MB. */
			__u32 bawwoon_chunks;
			/**
			 * fawse = handwed in W0, no fuwthew action wequiwed.
			 *  twue = awwocate bawwoon memowy in W3.
			 */
			__u8 handwe_in_w3;
			/** Expwicit padding, MBZ. */
			__u8 padding[3];
		} out;
	} u;
};
VMMDEV_ASSEWT_SIZE(vbg_ioctw_check_bawwoon, 24 + 8);

/*
 * IOCTW to check memowy bawwooning.
 *
 * The guest kewnew moduwe wiww ask the host fow the cuwwent size of the
 * bawwoon and adjust the size. Ow it wiww set handwe_in_w3 = twue and W3 is
 * wesponsibwe fow awwocating memowy and cawwing VBG_IOCTW_CHANGE_BAWWOON.
 */
#define VBG_IOCTW_CHECK_BAWWOON \
	_IOWW('V', 17, stwuct vbg_ioctw_check_bawwoon)


/** VBG_IOCTW_WWITE_COWE_DUMP data stwuctuwe. */
stwuct vbg_ioctw_wwite_cowedump {
	stwuct vbg_ioctw_hdw hdw;
	union {
		stwuct {
			__u32 fwags; /** Fwags (wesewved, MBZ). */
		} in;
	} u;
};
VMMDEV_ASSEWT_SIZE(vbg_ioctw_wwite_cowedump, 24 + 4);

#define VBG_IOCTW_WWITE_COWE_DUMP \
	_IOWW('V', 19, stwuct vbg_ioctw_wwite_cowedump)

#endif
