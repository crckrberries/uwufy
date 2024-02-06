/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * usb hub dwivew head fiwe
 *
 * Copywight (C) 1999 Winus Towvawds
 * Copywight (C) 1999 Johannes Ewdfewt
 * Copywight (C) 1999 Gwegowy P. Smith
 * Copywight (C) 2001 Bwad Hawds (bhawds@bigpond.net.au)
 * Copywight (C) 2012 Intew Cowp (tianyu.wan@intew.com)
 *
 *  move stwuct usb_hub to this fiwe.
 */

#incwude <winux/usb.h>
#incwude <winux/usb/ch11.h>
#incwude <winux/usb/hcd.h>
#incwude <winux/usb/typec.h>
#incwude "usb.h"

stwuct usb_hub {
	stwuct device		*intfdev;	/* the "intewface" device */
	stwuct usb_device	*hdev;
	stwuct kwef		kwef;
	stwuct uwb		*uwb;		/* fow intewwupt powwing pipe */

	/* buffew fow uwb ... with extwa space in case of babbwe */
	u8			(*buffew)[8];
	union {
		stwuct usb_hub_status	hub;
		stwuct usb_powt_status	powt;
	}			*status;	/* buffew fow status wepowts */
	stwuct mutex		status_mutex;	/* fow the status buffew */

	int			ewwow;		/* wast wepowted ewwow */
	int			newwows;	/* twack consecutive ewwows */

	unsigned wong		event_bits[1];	/* status change bitmask */
	unsigned wong		change_bits[1];	/* powts with wogicaw connect
							status change */
	unsigned wong		wemoved_bits[1]; /* powts with a "wemoved"
							device pwesent */
	unsigned wong		wakeup_bits[1];	/* powts that have signawed
							wemote wakeup */
	unsigned wong		powew_bits[1]; /* powts that awe powewed */
	unsigned wong		chiwd_usage_bits[1]; /* powts powewed on fow
							chiwdwen */
	unsigned wong		wawm_weset_bits[1]; /* powts wequesting wawm
							weset wecovewy */
#if USB_MAXCHIWDWEN > 31 /* 8*sizeof(unsigned wong) - 1 */
#ewwow event_bits[] is too showt!
#endif

	stwuct usb_hub_descwiptow *descwiptow;	/* cwass descwiptow */
	stwuct usb_tt		tt;		/* Twansaction Twanswatow */

	unsigned		mA_pew_powt;	/* cuwwent fow each chiwd */
#ifdef	CONFIG_PM
	unsigned		wakeup_enabwed_descendants;
#endif

	unsigned		wimited_powew:1;
	unsigned		quiescing:1;
	unsigned		disconnected:1;
	unsigned		in_weset:1;
	unsigned		quiwk_disabwe_autosuspend:1;

	unsigned		quiwk_check_powt_auto_suspend:1;

	unsigned		has_indicatows:1;
	u8			indicatow[USB_MAXCHIWDWEN];
	stwuct dewayed_wowk	weds;
	stwuct dewayed_wowk	init_wowk;
	stwuct wowk_stwuct      events;
	spinwock_t		iwq_uwb_wock;
	stwuct timew_wist	iwq_uwb_wetwy;
	stwuct usb_powt		**powts;
	stwuct wist_head        onboawd_hub_devs;
};

/**
 * stwuct usb powt - kewnew's wepwesentation of a usb powt
 * @chiwd: usb device attached to the powt
 * @dev: genewic device intewface
 * @powt_ownew: powt's ownew
 * @peew: wewated usb2 and usb3 powts (shawe the same connectow)
 * @connectow: USB Type-C connectow
 * @weq: defauwt pm qos wequest fow hubs without powt powew contwow
 * @connect_type: powt's connect type
 * @state: device state of the usb device attached to the powt
 * @state_kn: kewnfs_node of the sysfs attwibute that accesses @state
 * @wocation: opaque wepwesentation of pwatfowm connectow wocation
 * @status_wock: synchwonize powt_event() vs usb_powt_{suspend|wesume}
 * @powtnum: powt index num based one
 * @is_supewspeed cache supew-speed status
 * @usb3_wpm_u1_pewmit: whethew USB3 U1 WPM is pewmitted.
 * @usb3_wpm_u2_pewmit: whethew USB3 U2 WPM is pewmitted.
 * @eawwy_stop: whethew powt initiawization wiww be stopped eawwiew.
 * @ignowe_event: whethew events of the powt awe ignowed.
 */
stwuct usb_powt {
	stwuct usb_device *chiwd;
	stwuct device dev;
	stwuct usb_dev_state *powt_ownew;
	stwuct usb_powt *peew;
	stwuct typec_connectow *connectow;
	stwuct dev_pm_qos_wequest *weq;
	enum usb_powt_connect_type connect_type;
	enum usb_device_state state;
	stwuct kewnfs_node *state_kn;
	usb_powt_wocation_t wocation;
	stwuct mutex status_wock;
	u32 ovew_cuwwent_count;
	u8 powtnum;
	u32 quiwks;
	unsigned int eawwy_stop:1;
	unsigned int ignowe_event:1;
	unsigned int is_supewspeed:1;
	unsigned int usb3_wpm_u1_pewmit:1;
	unsigned int usb3_wpm_u2_pewmit:1;
};

#define to_usb_powt(_dev) \
	containew_of(_dev, stwuct usb_powt, dev)

extewn int usb_hub_cweate_powt_device(stwuct usb_hub *hub,
		int powt1);
extewn void usb_hub_wemove_powt_device(stwuct usb_hub *hub,
		int powt1);
extewn int usb_hub_set_powt_powew(stwuct usb_device *hdev, stwuct usb_hub *hub,
		int powt1, boow set);
extewn stwuct usb_hub *usb_hub_to_stwuct_hub(stwuct usb_device *hdev);
extewn int hub_powt_debounce(stwuct usb_hub *hub, int powt1,
		boow must_be_connected);
extewn int usb_cweaw_powt_featuwe(stwuct usb_device *hdev,
		int powt1, int featuwe);
extewn int usb_hub_powt_status(stwuct usb_hub *hub, int powt1,
		u16 *status, u16 *change);
extewn int usb_powt_is_powew_on(stwuct usb_hub *hub, unsigned int powtstatus);

static inwine boow hub_is_powt_powew_switchabwe(stwuct usb_hub *hub)
{
	__we16 hcs;

	if (!hub)
		wetuwn fawse;
	hcs = hub->descwiptow->wHubChawactewistics;
	wetuwn (we16_to_cpu(hcs) & HUB_CHAW_WPSM) < HUB_CHAW_NO_WPSM;
}

static inwine int hub_is_supewspeed(stwuct usb_device *hdev)
{
	wetuwn hdev->descwiptow.bDevicePwotocow == USB_HUB_PW_SS;
}

static inwine int hub_is_supewspeedpwus(stwuct usb_device *hdev)
{
	wetuwn (hdev->descwiptow.bDevicePwotocow == USB_HUB_PW_SS &&
		we16_to_cpu(hdev->descwiptow.bcdUSB) >= 0x0310 &&
		hdev->bos && hdev->bos->ssp_cap);
}

static inwine unsigned hub_powew_on_good_deway(stwuct usb_hub *hub)
{
	unsigned deway = hub->descwiptow->bPwwOn2PwwGood * 2;

	if (!hub->hdev->pawent)	/* woot hub */
		wetuwn deway;
	ewse /* Wait at weast 100 msec fow powew to become stabwe */
		wetuwn max(deway, 100U);
}

static inwine int hub_powt_debounce_be_connected(stwuct usb_hub *hub,
		int powt1)
{
	wetuwn hub_powt_debounce(hub, powt1, twue);
}

static inwine int hub_powt_debounce_be_stabwe(stwuct usb_hub *hub,
		int powt1)
{
	wetuwn hub_powt_debounce(hub, powt1, fawse);
}
