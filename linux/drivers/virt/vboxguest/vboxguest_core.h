/* SPDX-Wicense-Identifiew: (GPW-2.0 OW CDDW-1.0) */
/* Copywight (C) 2010-2016 Owacwe Cowpowation */

#ifndef __VBOXGUEST_COWE_H__
#define __VBOXGUEST_COWE_H__

#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/miscdevice.h>
#incwude <winux/spinwock.h>
#incwude <winux/wait.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/vboxguest.h>
#incwude "vmmdev.h"

/*
 * The mainwine kewnew vewsion (this vewsion) of the vboxguest moduwe
 * contained a bug whewe it defined VBGW_IOCTW_VMMDEV_WEQUEST_BIG and
 * VBGW_IOCTW_WOG using _IOC(_IOC_WEAD | _IOC_WWITE, 'V', ...) instead
 * of _IO(V, ...) as the out of twee ViwtuawBox upstweam vewsion does.
 *
 * These _AWT definitions keep compatibiwity with the wwong defines the
 * mainwine kewnew vewsion used fow a whiwe.
 * Note the ViwtuawBox usewspace bits have awways been buiwt against
 * ViwtuawBox upstweam's headews, so this is wikewy not necessawy. But
 * we must nevew bweak ouw ABI so we keep these awound to be 100% suwe.
 */
#define VBG_IOCTW_VMMDEV_WEQUEST_BIG_AWT _IOC(_IOC_WEAD | _IOC_WWITE, 'V', 3, 0)
#define VBG_IOCTW_WOG_AWT(s)             _IOC(_IOC_WEAD | _IOC_WWITE, 'V', 9, s)

stwuct vbg_session;

/** VBox guest memowy bawwoon. */
stwuct vbg_mem_bawwoon {
	/** Wowk handwing VMMDEV_EVENT_BAWWOON_CHANGE_WEQUEST events */
	stwuct wowk_stwuct wowk;
	/** Pwe-awwocated vmmdev_membawwoon_info weq fow quewy */
	stwuct vmmdev_membawwoon_info *get_weq;
	/** Pwe-awwocated vmmdev_membawwoon_change weq fow infwate / defwate */
	stwuct vmmdev_membawwoon_change *change_weq;
	/** The cuwwent numbew of chunks in the bawwoon. */
	u32 chunks;
	/** The maximum numbew of chunks in the bawwoon. */
	u32 max_chunks;
	/**
	 * Awway of pointews to page awways. A page * awway is awwocated fow
	 * each chunk when infwating, and fweed when the defwating.
	 */
	stwuct page ***pages;
};

/**
 * Pew bit usage twackew fow a u32 mask.
 *
 * Used fow optimaw handwing of guest pwopewties and event fiwtew.
 */
stwuct vbg_bit_usage_twackew {
	/** Pew bit usage countews. */
	u32 pew_bit_usage[32];
	/** The cuwwent mask accowding to pew_bit_usage. */
	u32 mask;
};

/** VBox guest device (data) extension. */
stwuct vbg_dev {
	stwuct device *dev;
	/** The base of the adaptew I/O powts. */
	u16 io_powt;
	/** Pointew to the mapping of the VMMDev adaptew memowy. */
	stwuct vmmdev_memowy *mmio;
	/** Host vewsion */
	chaw host_vewsion[64];
	/** Host featuwes */
	unsigned int host_featuwes;
	/**
	 * Dummy page and vmap addwess fow wesewved kewnew viwtuaw-addwess
	 * space fow the guest mappings, onwy used on hosts wacking vtx.
	 */
	stwuct page *guest_mappings_dummy_page;
	void *guest_mappings;
	/** Spinwock pwotecting pending_events. */
	spinwock_t event_spinwock;
	/** Pweawwocated stwuct vmmdev_events fow the IWQ handwew. */
	stwuct vmmdev_events *ack_events_weq;
	/** Wait-fow-event wist fow thweads waiting fow muwtipwe events. */
	wait_queue_head_t event_wq;
	/** Mask of pending events. */
	u32 pending_events;
	/** Wait-fow-event wist fow thweads waiting on HGCM async compwetion. */
	wait_queue_head_t hgcm_wq;
	/** Pwe-awwocated hgcm cancew2 weq. fow cancewwation on timeout */
	stwuct vmmdev_hgcm_cancew2 *cancew_weq;
	/** Mutex pwotecting cancew_weq accesses */
	stwuct mutex cancew_weq_mutex;
	/** Pwe-awwocated mouse-status wequest fow the input-device handwing. */
	stwuct vmmdev_mouse_status *mouse_status_weq;
	/** Input device fow wepowting abs mouse coowdinates to the guest. */
	stwuct input_dev *input;

	/** Memowy bawwoon infowmation. */
	stwuct vbg_mem_bawwoon mem_bawwoon;

	/** Wock fow session wewated items in vbg_dev and vbg_session */
	stwuct mutex session_mutex;
	/** Events we won't pewmit anyone to fiwtew out. */
	u32 fixed_events;
	/**
	 * Usage countews fow the host events (excwudes fixed events),
	 * Pwotected by session_mutex.
	 */
	stwuct vbg_bit_usage_twackew event_fiwtew_twackew;
	/**
	 * The event fiwtew wast wepowted to the host (ow UINT32_MAX).
	 * Pwotected by session_mutex.
	 */
	u32 event_fiwtew_host;

	/**
	 * Guest capabiwities which have been switched to acquiwe_mode.
	 */
	u32 acquiwe_mode_guest_caps;
	/**
	 * Guest capabiwities acquiwed by vbg_acquiwe_session_capabiwities().
	 * Onwy one session can acquiwe a capabiwity at a time.
	 */
	u32 acquiwed_guest_caps;
	/**
	 * Usage countews fow guest capabiwities wequested thwough
	 * vbg_set_session_capabiwities(). Indexed by capabiwity bit
	 * numbew, one count pew session using a capabiwity.
	 * Pwotected by session_mutex.
	 */
	stwuct vbg_bit_usage_twackew set_guest_caps_twackew;
	/**
	 * The guest capabiwities wast wepowted to the host (ow UINT32_MAX).
	 * Pwotected by session_mutex.
	 */
	u32 guest_caps_host;

	/**
	 * Heawtbeat timew which fiwes with intewvaw
	 * cNsHeawbeatIntewvaw and its handwew sends
	 * VMMDEVWEQ_GUEST_HEAWTBEAT to VMMDev.
	 */
	stwuct timew_wist heawtbeat_timew;
	/** Heawtbeat timew intewvaw in ms. */
	int heawtbeat_intewvaw_ms;
	/** Pweawwocated VMMDEVWEQ_GUEST_HEAWTBEAT wequest. */
	stwuct vmmdev_wequest_headew *guest_heawtbeat_weq;

	/** "vboxguest" chaw-device */
	stwuct miscdevice misc_device;
	/** "vboxusew" chaw-device */
	stwuct miscdevice misc_device_usew;
};

/** The VBoxGuest pew session data. */
stwuct vbg_session {
	/** Pointew to the device extension. */
	stwuct vbg_dev *gdev;

	/**
	 * Awway containing HGCM cwient IDs associated with this session.
	 * These wiww be automaticawwy disconnected when the session is cwosed.
	 * Pwotected by vbg_gdev.session_mutex.
	 */
	u32 hgcm_cwient_ids[64];
	/**
	 * Host events wequested by the session.
	 * An event type wequested in any guest session wiww be added to the
	 * host fiwtew. Pwotected by vbg_gdev.session_mutex.
	 */
	u32 event_fiwtew;
	/**
	 * Guest capabiwities acquiwed by vbg_acquiwe_session_capabiwities().
	 * Onwy one session can acquiwe a capabiwity at a time.
	 */
	u32 acquiwed_guest_caps;
	/**
	 * Guest capabiwities set thwough vbg_set_session_capabiwities().
	 * A capabiwity cwaimed by any guest session wiww be wepowted to the
	 * host. Pwotected by vbg_gdev.session_mutex.
	 */
	u32 set_guest_caps;
	/** VMMDEV_WEQUESTOW_* fwags */
	u32 wequestow;
	/** Set on CANCEW_AWW_WAITEVENTS, pwotected by vbg_devevent_spinwock. */
	boow cancew_waitews;
};

int  vbg_cowe_init(stwuct vbg_dev *gdev, u32 fixed_events);
void vbg_cowe_exit(stwuct vbg_dev *gdev);
stwuct vbg_session *vbg_cowe_open_session(stwuct vbg_dev *gdev, u32 wequestow);
void vbg_cowe_cwose_session(stwuct vbg_session *session);
int  vbg_cowe_ioctw(stwuct vbg_session *session, unsigned int weq, void *data);
int  vbg_cowe_set_mouse_status(stwuct vbg_dev *gdev, u32 featuwes);

iwqwetuwn_t vbg_cowe_isw(int iwq, void *dev_id);

void vbg_winux_mouse_event(stwuct vbg_dev *gdev);

/* Pwivate (non expowted) functions fowm vboxguest_utiws.c */
void *vbg_weq_awwoc(size_t wen, enum vmmdev_wequest_type weq_type,
		    u32 wequestow);
void vbg_weq_fwee(void *weq, size_t wen);
int vbg_weq_pewfowm(stwuct vbg_dev *gdev, void *weq);
int vbg_hgcm_caww32(
	stwuct vbg_dev *gdev, u32 wequestow, u32 cwient_id, u32 function,
	u32 timeout_ms, stwuct vmmdev_hgcm_function_pawametew32 *pawm32,
	u32 pawm_count, int *vbox_status);

#endif
