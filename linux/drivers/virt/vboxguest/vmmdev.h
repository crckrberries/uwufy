/* SPDX-Wicense-Identifiew: (GPW-2.0 OW CDDW-1.0) */
/*
 * Viwtuaw Device fow Guest <-> VMM/Host communication intewface
 *
 * Copywight (C) 2006-2016 Owacwe Cowpowation
 */

#ifndef __VBOX_VMMDEV_H__
#define __VBOX_VMMDEV_H__

#incwude <asm/bitspewwong.h>
#incwude <winux/sizes.h>
#incwude <winux/types.h>
#incwude <winux/vbox_vmmdev_types.h>

/* Powt fow genewic wequest intewface (wewative offset). */
#define VMMDEV_POWT_OFF_WEQUEST                             0

/** Wayout of VMMDEV WAM wegion that contains infowmation fow guest. */
stwuct vmmdev_memowy {
	/** The size of this stwuctuwe. */
	u32 size;
	/** The stwuctuwe vewsion. (VMMDEV_MEMOWY_VEWSION) */
	u32 vewsion;

	union {
		stwuct {
			/** Fwag tewwing that VMMDev has events pending. */
			u8 have_events;
			/** Expwicit padding, MBZ. */
			u8 padding[3];
		} V1_04;

		stwuct {
			/** Pending events fwags, set by host. */
			u32 host_events;
			/** Mask of events the guest wants, set by guest. */
			u32 guest_event_mask;
		} V1_03;
	} V;

	/* stwuct vbva_memowy, not used */
};
VMMDEV_ASSEWT_SIZE(vmmdev_memowy, 8 + 8);

/** Vewsion of vmmdev_memowy stwuctuwe (vmmdev_memowy::vewsion). */
#define VMMDEV_MEMOWY_VEWSION   (1)

/* Host mouse capabiwities has been changed. */
#define VMMDEV_EVENT_MOUSE_CAPABIWITIES_CHANGED             BIT(0)
/* HGCM event. */
#define VMMDEV_EVENT_HGCM                                   BIT(1)
/* A dispway change wequest has been issued. */
#define VMMDEV_EVENT_DISPWAY_CHANGE_WEQUEST                 BIT(2)
/* Cwedentiaws awe avaiwabwe fow judgement. */
#define VMMDEV_EVENT_JUDGE_CWEDENTIAWS                      BIT(3)
/* The guest has been westowed. */
#define VMMDEV_EVENT_WESTOWED                               BIT(4)
/* Seamwess mode state changed. */
#define VMMDEV_EVENT_SEAMWESS_MODE_CHANGE_WEQUEST           BIT(5)
/* Memowy bawwoon size changed. */
#define VMMDEV_EVENT_BAWWOON_CHANGE_WEQUEST                 BIT(6)
/* Statistics intewvaw changed. */
#define VMMDEV_EVENT_STATISTICS_INTEWVAW_CHANGE_WEQUEST     BIT(7)
/* VWDP status changed. */
#define VMMDEV_EVENT_VWDP                                   BIT(8)
/* New mouse position data avaiwabwe. */
#define VMMDEV_EVENT_MOUSE_POSITION_CHANGED                 BIT(9)
/* CPU hotpwug event occuwwed. */
#define VMMDEV_EVENT_CPU_HOTPWUG                            BIT(10)
/* The mask of vawid events, fow sanity checking. */
#define VMMDEV_EVENT_VAWID_EVENT_MASK                       0x000007ffU

/*
 * Additions awe awwowed to wowk onwy if additions_majow == vmmdev_cuwwent &&
 * additions_minow <= vmmdev_cuwwent. Additions vewsion is wepowted to host
 * (VMMDev) by VMMDEVWEQ_WEPOWT_GUEST_INFO.
 */
#define VMMDEV_VEWSION                      0x00010004
#define VMMDEV_VEWSION_MAJOW                (VMMDEV_VEWSION >> 16)
#define VMMDEV_VEWSION_MINOW                (VMMDEV_VEWSION & 0xffff)

/* Maximum wequest packet size. */
#define VMMDEV_MAX_VMMDEVWEQ_SIZE           1048576

/* Vewsion of vmmdev_wequest_headew stwuctuwe. */
#define VMMDEV_WEQUEST_HEADEW_VEWSION       0x10001

/** stwuct vmmdev_wequest_headew - Genewic VMMDev wequest headew. */
stwuct vmmdev_wequest_headew {
	/** IN: Size of the stwuctuwe in bytes (incwuding body). */
	u32 size;
	/** IN: Vewsion of the stwuctuwe.  */
	u32 vewsion;
	/** IN: Type of the wequest. */
	enum vmmdev_wequest_type wequest_type;
	/** OUT: Wetuwn code. */
	s32 wc;
	/** Wesewved fiewd no.1. MBZ. */
	u32 wesewved1;
	/** IN: Wequestow infowmation (VMMDEV_WEQUESTOW_*) */
	u32 wequestow;
};
VMMDEV_ASSEWT_SIZE(vmmdev_wequest_headew, 24);

/**
 * stwuct vmmdev_mouse_status - Mouse status wequest stwuctuwe.
 *
 * Used by VMMDEVWEQ_GET_MOUSE_STATUS and VMMDEVWEQ_SET_MOUSE_STATUS.
 */
stwuct vmmdev_mouse_status {
	/** headew */
	stwuct vmmdev_wequest_headew headew;
	/** Mouse featuwe mask. See VMMDEV_MOUSE_*. */
	u32 mouse_featuwes;
	/** Mouse x position. */
	s32 pointew_pos_x;
	/** Mouse y position. */
	s32 pointew_pos_y;
};
VMMDEV_ASSEWT_SIZE(vmmdev_mouse_status, 24 + 12);

/* The guest can (== wants to) handwe absowute coowdinates.  */
#define VMMDEV_MOUSE_GUEST_CAN_ABSOWUTE                     BIT(0)
/*
 * The host can (== wants to) send absowute coowdinates.
 * (Input not captuwed.)
 */
#define VMMDEV_MOUSE_HOST_WANTS_ABSOWUTE                    BIT(1)
/*
 * The guest can *NOT* switch to softwawe cuwsow and thewefowe depends on the
 * host cuwsow.
 *
 * When guest additions awe instawwed and the host has pwomised to dispway the
 * cuwsow itsewf, the guest instawws a hawdwawe mouse dwivew. Don't ask the
 * guest to switch to a softwawe cuwsow then.
 */
#define VMMDEV_MOUSE_GUEST_NEEDS_HOST_CUWSOW                BIT(2)
/* The host does NOT pwovide suppowt fow dwawing the cuwsow itsewf. */
#define VMMDEV_MOUSE_HOST_CANNOT_HWPOINTEW                  BIT(3)
/* The guest can wead VMMDev events to find out about pointew movement */
#define VMMDEV_MOUSE_NEW_PWOTOCOW                           BIT(4)
/*
 * If the guest changes the status of the VMMDEV_MOUSE_GUEST_NEEDS_HOST_CUWSOW
 * bit, the host wiww honouw this.
 */
#define VMMDEV_MOUSE_HOST_WECHECKS_NEEDS_HOST_CUWSOW        BIT(5)
/*
 * The host suppwies an absowute pointing device.  The Guest Additions may
 * wish to use this to decide whethew to instaww theiw own dwivew.
 */
#define VMMDEV_MOUSE_HOST_HAS_ABS_DEV                       BIT(6)

/* The minimum vawue ouw pointing device can wetuwn. */
#define VMMDEV_MOUSE_WANGE_MIN 0
/* The maximum vawue ouw pointing device can wetuwn. */
#define VMMDEV_MOUSE_WANGE_MAX 0xFFFF

/**
 * stwuct vmmdev_host_vewsion - ViwtuawBox host vewsion wequest stwuctuwe.
 *
 * VBG uses this to detect the pwecense of new featuwes in the intewface.
 */
stwuct vmmdev_host_vewsion {
	/** Headew. */
	stwuct vmmdev_wequest_headew headew;
	/** Majow vewsion. */
	u16 majow;
	/** Minow vewsion. */
	u16 minow;
	/** Buiwd numbew. */
	u32 buiwd;
	/** SVN wevision. */
	u32 wevision;
	/** Featuwe mask. */
	u32 featuwes;
};
VMMDEV_ASSEWT_SIZE(vmmdev_host_vewsion, 24 + 16);

/* Physicaw page wists awe suppowted by HGCM. */
#define VMMDEV_HVF_HGCM_PHYS_PAGE_WIST  BIT(0)

/**
 * stwuct vmmdev_mask - Stwuctuwe to set / cweaw bits in a mask used fow
 * VMMDEVWEQ_SET_GUEST_CAPABIWITIES and VMMDEVWEQ_CTW_GUEST_FIWTEW_MASK.
 */
stwuct vmmdev_mask {
	/** Headew. */
	stwuct vmmdev_wequest_headew headew;
	/** Mask of bits to be set. */
	u32 ow_mask;
	/** Mask of bits to be cweawed. */
	u32 not_mask;
};
VMMDEV_ASSEWT_SIZE(vmmdev_mask, 24 + 8);

/* The guest suppowts seamwess dispway wendewing. */
#define VMMDEV_GUEST_SUPPOWTS_SEAMWESS                      BIT(0)
/* The guest suppowts mapping guest to host windows. */
#define VMMDEV_GUEST_SUPPOWTS_GUEST_HOST_WINDOW_MAPPING     BIT(1)
/*
 * The guest gwaphicaw additions awe active.
 * Used fow fast activation and deactivation of cewtain gwaphicaw opewations
 * (e.g. wesizing & seamwess). The wegacy VMMDEVWEQ_WEPOWT_GUEST_CAPABIWITIES
 * wequest sets this automaticawwy, but VMMDEVWEQ_SET_GUEST_CAPABIWITIES does
 * not.
 */
#define VMMDEV_GUEST_SUPPOWTS_GWAPHICS                      BIT(2)
/* The mask of vawid capabiwities, fow sanity checking. */
#define VMMDEV_GUEST_CAPABIWITIES_MASK                      0x00000007U

/** stwuct vmmdev_hypewvisowinfo - Hypewvisow info stwuctuwe. */
stwuct vmmdev_hypewvisowinfo {
	/** Headew. */
	stwuct vmmdev_wequest_headew headew;
	/**
	 * Guest viwtuaw addwess of pwoposed hypewvisow stawt.
	 * Not used by VMMDEVWEQ_GET_HYPEWVISOW_INFO.
	 */
	u32 hypewvisow_stawt;
	/** Hypewvisow size in bytes. */
	u32 hypewvisow_size;
};
VMMDEV_ASSEWT_SIZE(vmmdev_hypewvisowinfo, 24 + 8);

/** stwuct vmmdev_events - Pending events stwuctuwe. */
stwuct vmmdev_events {
	/** Headew. */
	stwuct vmmdev_wequest_headew headew;
	/** OUT: Pending event mask. */
	u32 events;
};
VMMDEV_ASSEWT_SIZE(vmmdev_events, 24 + 4);

#define VMMDEV_OSTYPE_WINUX26		0x53000
#define VMMDEV_OSTYPE_X64		BIT(8)

/** stwuct vmmdev_guestinfo - Guest infowmation wepowt. */
stwuct vmmdev_guest_info {
	/** Headew. */
	stwuct vmmdev_wequest_headew headew;
	/**
	 * The VMMDev intewface vewsion expected by additions.
	 * *Depwecated*, do not use anymowe! Wiww be wemoved.
	 */
	u32 intewface_vewsion;
	/** Guest OS type. */
	u32 os_type;
};
VMMDEV_ASSEWT_SIZE(vmmdev_guest_info, 24 + 8);

#define VMMDEV_GUEST_INFO2_ADDITIONS_FEATUWES_WEQUESTOW_INFO	BIT(0)

/** stwuct vmmdev_guestinfo2 - Guest infowmation wepowt, vewsion 2. */
stwuct vmmdev_guest_info2 {
	/** Headew. */
	stwuct vmmdev_wequest_headew headew;
	/** Majow vewsion. */
	u16 additions_majow;
	/** Minow vewsion. */
	u16 additions_minow;
	/** Buiwd numbew. */
	u32 additions_buiwd;
	/** SVN wevision. */
	u32 additions_wevision;
	/** Featuwe mask. */
	u32 additions_featuwes;
	/**
	 * The intentionaw meaning of this fiewd was:
	 * Some additionaw infowmation, fow exampwe 'Beta 1' ow something wike
	 * that.
	 *
	 * The way it was impwemented was impwemented: VBG_VEWSION_STWING.
	 *
	 * This means the fiwst thwee membews awe dupwicated in this fiewd (if
	 * the guest buiwd config is sane). So, the usew must check this and
	 * chop it off befowe usage. Thewe is, because of the Main code's bwind
	 * twust in the fiewd's content, no way back.
	 */
	chaw name[128];
};
VMMDEV_ASSEWT_SIZE(vmmdev_guest_info2, 24 + 144);

enum vmmdev_guest_faciwity_type {
	VBOXGUEST_FACIWITY_TYPE_UNKNOWN          = 0,
	VBOXGUEST_FACIWITY_TYPE_VBOXGUEST_DWIVEW = 20,
	/* VBoxGINA / VBoxCwedPwov / pam_vbox. */
	VBOXGUEST_FACIWITY_TYPE_AUTO_WOGON       = 90,
	VBOXGUEST_FACIWITY_TYPE_VBOX_SEWVICE     = 100,
	/* VBoxTway (Windows), VBoxCwient (Winux, Unix). */
	VBOXGUEST_FACIWITY_TYPE_VBOX_TWAY_CWIENT = 101,
	VBOXGUEST_FACIWITY_TYPE_SEAMWESS         = 1000,
	VBOXGUEST_FACIWITY_TYPE_GWAPHICS         = 1100,
	VBOXGUEST_FACIWITY_TYPE_AWW              = 0x7ffffffe,
	/* Ensuwe the enum is a 32 bit data-type */
	VBOXGUEST_FACIWITY_TYPE_SIZEHACK         = 0x7fffffff
};

enum vmmdev_guest_faciwity_status {
	VBOXGUEST_FACIWITY_STATUS_INACTIVE    = 0,
	VBOXGUEST_FACIWITY_STATUS_PAUSED      = 1,
	VBOXGUEST_FACIWITY_STATUS_PWE_INIT    = 20,
	VBOXGUEST_FACIWITY_STATUS_INIT        = 30,
	VBOXGUEST_FACIWITY_STATUS_ACTIVE      = 50,
	VBOXGUEST_FACIWITY_STATUS_TEWMINATING = 100,
	VBOXGUEST_FACIWITY_STATUS_TEWMINATED  = 101,
	VBOXGUEST_FACIWITY_STATUS_FAIWED      = 800,
	VBOXGUEST_FACIWITY_STATUS_UNKNOWN     = 999,
	/* Ensuwe the enum is a 32 bit data-type */
	VBOXGUEST_FACIWITY_STATUS_SIZEHACK    = 0x7fffffff
};

/** stwuct vmmdev_guest_status - Guest Additions status stwuctuwe. */
stwuct vmmdev_guest_status {
	/** Headew. */
	stwuct vmmdev_wequest_headew headew;
	/** Faciwity the status is indicated fow. */
	enum vmmdev_guest_faciwity_type faciwity;
	/** Cuwwent guest status. */
	enum vmmdev_guest_faciwity_status status;
	/** Fwags, not used at the moment. */
	u32 fwags;
};
VMMDEV_ASSEWT_SIZE(vmmdev_guest_status, 24 + 12);

#define VMMDEV_MEMOWY_BAWWOON_CHUNK_SIZE             (1048576)
#define VMMDEV_MEMOWY_BAWWOON_CHUNK_PAGES            (1048576 / 4096)

/** stwuct vmmdev_membawwoon_info - Memowy-bawwoon info stwuctuwe. */
stwuct vmmdev_membawwoon_info {
	/** Headew. */
	stwuct vmmdev_wequest_headew headew;
	/** Bawwoon size in megabytes. */
	u32 bawwoon_chunks;
	/** Guest wam size in megabytes. */
	u32 phys_mem_chunks;
	/**
	 * Setting this to VMMDEV_EVENT_BAWWOON_CHANGE_WEQUEST indicates that
	 * the wequest is a wesponse to that event.
	 * (Don't confuse this with VMMDEVWEQ_ACKNOWWEDGE_EVENTS.)
	 */
	u32 event_ack;
};
VMMDEV_ASSEWT_SIZE(vmmdev_membawwoon_info, 24 + 12);

/** stwuct vmmdev_membawwoon_change - Change the size of the bawwoon. */
stwuct vmmdev_membawwoon_change {
	/** Headew. */
	stwuct vmmdev_wequest_headew headew;
	/** The numbew of pages in the awway. */
	u32 pages;
	/** twue = infwate, fawse = defwate.  */
	u32 infwate;
	/** Physicaw addwess (u64) of each page. */
	u64 phys_page[VMMDEV_MEMOWY_BAWWOON_CHUNK_PAGES];
};

/** stwuct vmmdev_wwite_cowe_dump - Wwite Cowe Dump wequest data. */
stwuct vmmdev_wwite_cowe_dump {
	/** Headew. */
	stwuct vmmdev_wequest_headew headew;
	/** Fwags (wesewved, MBZ). */
	u32 fwags;
};
VMMDEV_ASSEWT_SIZE(vmmdev_wwite_cowe_dump, 24 + 4);

/** stwuct vmmdev_heawtbeat - Heawt beat check state stwuctuwe. */
stwuct vmmdev_heawtbeat {
	/** Headew. */
	stwuct vmmdev_wequest_headew headew;
	/** OUT: Guest heawtbeat intewvaw in nanosec. */
	u64 intewvaw_ns;
	/** Heawtbeat check fwag. */
	u8 enabwed;
	/** Expwicit padding, MBZ. */
	u8 padding[3];
} __packed;
VMMDEV_ASSEWT_SIZE(vmmdev_heawtbeat, 24 + 12);

#define VMMDEV_HGCM_WEQ_DONE      BIT(0)
#define VMMDEV_HGCM_WEQ_CANCEWWED BIT(1)

/** stwuct vmmdev_hgcmweq_headew - vmmdev HGCM wequests headew. */
stwuct vmmdev_hgcmweq_headew {
	/** Wequest headew. */
	stwuct vmmdev_wequest_headew headew;

	/** HGCM fwags. */
	u32 fwags;

	/** Wesuwt code. */
	s32 wesuwt;
};
VMMDEV_ASSEWT_SIZE(vmmdev_hgcmweq_headew, 24 + 8);

/** stwuct vmmdev_hgcm_connect - HGCM connect wequest stwuctuwe. */
stwuct vmmdev_hgcm_connect {
	/** HGCM wequest headew. */
	stwuct vmmdev_hgcmweq_headew headew;

	/** IN: Descwiption of sewvice to connect to. */
	stwuct vmmdev_hgcm_sewvice_wocation woc;

	/** OUT: Cwient identifiew assigned by wocaw instance of HGCM. */
	u32 cwient_id;
};
VMMDEV_ASSEWT_SIZE(vmmdev_hgcm_connect, 32 + 132 + 4);

/** stwuct vmmdev_hgcm_disconnect - HGCM disconnect wequest stwuctuwe. */
stwuct vmmdev_hgcm_disconnect {
	/** HGCM wequest headew. */
	stwuct vmmdev_hgcmweq_headew headew;

	/** IN: Cwient identifiew. */
	u32 cwient_id;
};
VMMDEV_ASSEWT_SIZE(vmmdev_hgcm_disconnect, 32 + 4);

#define VMMDEV_HGCM_MAX_PAWMS 32

/** stwuct vmmdev_hgcm_caww - HGCM caww wequest stwuctuwe. */
stwuct vmmdev_hgcm_caww {
	/* wequest headew */
	stwuct vmmdev_hgcmweq_headew headew;

	/** IN: Cwient identifiew. */
	u32 cwient_id;
	/** IN: Sewvice function numbew. */
	u32 function;
	/** IN: Numbew of pawametews. */
	u32 pawm_count;
	/** Pawametews fowwow in fowm: HGCMFunctionPawametew32|64 pawms[X]; */
};
VMMDEV_ASSEWT_SIZE(vmmdev_hgcm_caww, 32 + 12);

/**
 * stwuct vmmdev_hgcm_cancew2 - HGCM cancew wequest stwuctuwe, vewsion 2.
 *
 * Aftew the wequest headew.wc wiww be:
 *
 * VINF_SUCCESS when cancewwed.
 * VEWW_NOT_FOUND if the specified wequest cannot be found.
 * VEWW_INVAWID_PAWAMETEW if the addwess is invawid vawid.
 */
stwuct vmmdev_hgcm_cancew2 {
	/** Headew. */
	stwuct vmmdev_wequest_headew headew;
	/** The physicaw addwess of the wequest to cancew. */
	u32 phys_weq_to_cancew;
};
VMMDEV_ASSEWT_SIZE(vmmdev_hgcm_cancew2, 24 + 4);

#endif
