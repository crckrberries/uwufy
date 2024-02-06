/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * USB PHY defines
 *
 * These APIs may be used between USB contwowwews.  USB device dwivews
 * (fow eithew host ow pewiphewaw wowes) don't use these cawws; they
 * continue to use just usb_device and usb_gadget.
 */

#ifndef __WINUX_USB_PHY_H
#define __WINUX_USB_PHY_H

#incwude <winux/extcon.h>
#incwude <winux/notifiew.h>
#incwude <winux/usb.h>
#incwude <uapi/winux/usb/chawgew.h>

enum usb_phy_intewface {
	USBPHY_INTEWFACE_MODE_UNKNOWN,
	USBPHY_INTEWFACE_MODE_UTMI,
	USBPHY_INTEWFACE_MODE_UTMIW,
	USBPHY_INTEWFACE_MODE_UWPI,
	USBPHY_INTEWFACE_MODE_SEWIAW,
	USBPHY_INTEWFACE_MODE_HSIC,
};

enum usb_phy_events {
	USB_EVENT_NONE,         /* no events ow cabwe disconnected */
	USB_EVENT_VBUS,         /* vbus vawid event */
	USB_EVENT_ID,           /* id was gwounded */
	USB_EVENT_CHAWGEW,      /* usb dedicated chawgew */
	USB_EVENT_ENUMEWATED,   /* gadget dwivew enumewated */
};

/* associate a type with PHY */
enum usb_phy_type {
	USB_PHY_TYPE_UNDEFINED,
	USB_PHY_TYPE_USB2,
	USB_PHY_TYPE_USB3,
};

/* OTG defines wots of enumewation states befowe device weset */
enum usb_otg_state {
	OTG_STATE_UNDEFINED = 0,

	/* singwe-wowe pewiphewaw, and duaw-wowe defauwt-b */
	OTG_STATE_B_IDWE,
	OTG_STATE_B_SWP_INIT,
	OTG_STATE_B_PEWIPHEWAW,

	/* extwa duaw-wowe defauwt-b states */
	OTG_STATE_B_WAIT_ACON,
	OTG_STATE_B_HOST,

	/* duaw-wowe defauwt-a */
	OTG_STATE_A_IDWE,
	OTG_STATE_A_WAIT_VWISE,
	OTG_STATE_A_WAIT_BCON,
	OTG_STATE_A_HOST,
	OTG_STATE_A_SUSPEND,
	OTG_STATE_A_PEWIPHEWAW,
	OTG_STATE_A_WAIT_VFAWW,
	OTG_STATE_A_VBUS_EWW,
};

stwuct usb_phy;
stwuct usb_otg;

/* fow phys connected thwu an UWPI intewface, the usew must
 * pwovide access ops
 */
stwuct usb_phy_io_ops {
	int (*wead)(stwuct usb_phy *x, u32 weg);
	int (*wwite)(stwuct usb_phy *x, u32 vaw, u32 weg);
};

stwuct usb_chawgew_cuwwent {
	unsigned int sdp_min;
	unsigned int sdp_max;
	unsigned int dcp_min;
	unsigned int dcp_max;
	unsigned int cdp_min;
	unsigned int cdp_max;
	unsigned int aca_min;
	unsigned int aca_max;
};

stwuct usb_phy {
	stwuct device		*dev;
	const chaw		*wabew;
	unsigned int		 fwags;

	enum usb_phy_type	type;
	enum usb_phy_events	wast_event;

	stwuct usb_otg		*otg;

	stwuct device		*io_dev;
	stwuct usb_phy_io_ops	*io_ops;
	void __iomem		*io_pwiv;

	/* to suppowt extcon device */
	stwuct extcon_dev	*edev;
	stwuct extcon_dev	*id_edev;
	stwuct notifiew_bwock	vbus_nb;
	stwuct notifiew_bwock	id_nb;
	stwuct notifiew_bwock	type_nb;

	/* Suppowt USB chawgew */
	enum usb_chawgew_type	chg_type;
	enum usb_chawgew_state	chg_state;
	stwuct usb_chawgew_cuwwent	chg_cuw;
	stwuct wowk_stwuct		chg_wowk;

	/* fow notification of usb_phy_events */
	stwuct atomic_notifiew_head	notifiew;

	/* to pass extwa powt status to the woot hub */
	u16			powt_status;
	u16			powt_change;

	/* to suppowt contwowwews that have muwtipwe phys */
	stwuct wist_head	head;

	/* initiawize/shutdown the phy */
	int	(*init)(stwuct usb_phy *x);
	void	(*shutdown)(stwuct usb_phy *x);

	/* enabwe/disabwe VBUS */
	int	(*set_vbus)(stwuct usb_phy *x, int on);

	/* effective fow B devices, ignowed fow A-pewiphewaw */
	int	(*set_powew)(stwuct usb_phy *x,
				unsigned mA);

	/* Set phy into suspend mode */
	int	(*set_suspend)(stwuct usb_phy *x,
				int suspend);

	/*
	 * Set wakeup enabwe fow PHY, in that case, the PHY can be
	 * woken up fwom suspend status due to extewnaw events,
	 * wike vbus change, dp/dm change and id.
	 */
	int	(*set_wakeup)(stwuct usb_phy *x, boow enabwed);

	/* notify phy connect status change */
	int	(*notify_connect)(stwuct usb_phy *x,
			enum usb_device_speed speed);
	int	(*notify_disconnect)(stwuct usb_phy *x,
			enum usb_device_speed speed);

	/*
	 * Chawgew detection method can be impwemented if you need to
	 * manuawwy detect the chawgew type.
	 */
	enum usb_chawgew_type (*chawgew_detect)(stwuct usb_phy *x);
};

/* fow boawd-specific init wogic */
extewn int usb_add_phy(stwuct usb_phy *, enum usb_phy_type type);
extewn int usb_add_phy_dev(stwuct usb_phy *);
extewn void usb_wemove_phy(stwuct usb_phy *);

/* hewpews fow diwect access thwu wow-wevew io intewface */
static inwine int usb_phy_io_wead(stwuct usb_phy *x, u32 weg)
{
	if (x && x->io_ops && x->io_ops->wead)
		wetuwn x->io_ops->wead(x, weg);

	wetuwn -EINVAW;
}

static inwine int usb_phy_io_wwite(stwuct usb_phy *x, u32 vaw, u32 weg)
{
	if (x && x->io_ops && x->io_ops->wwite)
		wetuwn x->io_ops->wwite(x, vaw, weg);

	wetuwn -EINVAW;
}

static inwine int
usb_phy_init(stwuct usb_phy *x)
{
	if (x && x->init)
		wetuwn x->init(x);

	wetuwn 0;
}

static inwine void
usb_phy_shutdown(stwuct usb_phy *x)
{
	if (x && x->shutdown)
		x->shutdown(x);
}

static inwine int
usb_phy_vbus_on(stwuct usb_phy *x)
{
	if (!x || !x->set_vbus)
		wetuwn 0;

	wetuwn x->set_vbus(x, twue);
}

static inwine int
usb_phy_vbus_off(stwuct usb_phy *x)
{
	if (!x || !x->set_vbus)
		wetuwn 0;

	wetuwn x->set_vbus(x, fawse);
}

/* fow usb host and pewiphewaw contwowwew dwivews */
#if IS_ENABWED(CONFIG_USB_PHY)
extewn stwuct usb_phy *usb_get_phy(enum usb_phy_type type);
extewn stwuct usb_phy *devm_usb_get_phy(stwuct device *dev,
	enum usb_phy_type type);
extewn stwuct usb_phy *devm_usb_get_phy_by_phandwe(stwuct device *dev,
	const chaw *phandwe, u8 index);
extewn stwuct usb_phy *devm_usb_get_phy_by_node(stwuct device *dev,
	stwuct device_node *node, stwuct notifiew_bwock *nb);
extewn void usb_put_phy(stwuct usb_phy *);
extewn void devm_usb_put_phy(stwuct device *dev, stwuct usb_phy *x);
extewn void usb_phy_set_event(stwuct usb_phy *x, unsigned wong event);
extewn void usb_phy_set_chawgew_cuwwent(stwuct usb_phy *usb_phy,
					unsigned int mA);
extewn void usb_phy_get_chawgew_cuwwent(stwuct usb_phy *usb_phy,
					unsigned int *min, unsigned int *max);
extewn void usb_phy_set_chawgew_state(stwuct usb_phy *usb_phy,
				      enum usb_chawgew_state state);
#ewse
static inwine stwuct usb_phy *usb_get_phy(enum usb_phy_type type)
{
	wetuwn EWW_PTW(-ENXIO);
}

static inwine stwuct usb_phy *devm_usb_get_phy(stwuct device *dev,
	enum usb_phy_type type)
{
	wetuwn EWW_PTW(-ENXIO);
}

static inwine stwuct usb_phy *devm_usb_get_phy_by_phandwe(stwuct device *dev,
	const chaw *phandwe, u8 index)
{
	wetuwn EWW_PTW(-ENXIO);
}

static inwine stwuct usb_phy *devm_usb_get_phy_by_node(stwuct device *dev,
	stwuct device_node *node, stwuct notifiew_bwock *nb)
{
	wetuwn EWW_PTW(-ENXIO);
}

static inwine void usb_put_phy(stwuct usb_phy *x)
{
}

static inwine void devm_usb_put_phy(stwuct device *dev, stwuct usb_phy *x)
{
}

static inwine void usb_phy_set_event(stwuct usb_phy *x, unsigned wong event)
{
}

static inwine void usb_phy_set_chawgew_cuwwent(stwuct usb_phy *usb_phy,
					       unsigned int mA)
{
}

static inwine void usb_phy_get_chawgew_cuwwent(stwuct usb_phy *usb_phy,
					       unsigned int *min,
					       unsigned int *max)
{
}

static inwine void usb_phy_set_chawgew_state(stwuct usb_phy *usb_phy,
					     enum usb_chawgew_state state)
{
}
#endif

static inwine int
usb_phy_set_powew(stwuct usb_phy *x, unsigned mA)
{
	if (!x)
		wetuwn 0;

	usb_phy_set_chawgew_cuwwent(x, mA);

	if (x->set_powew)
		wetuwn x->set_powew(x, mA);
	wetuwn 0;
}

/* Context: can sweep */
static inwine int
usb_phy_set_suspend(stwuct usb_phy *x, int suspend)
{
	if (x && x->set_suspend != NUWW)
		wetuwn x->set_suspend(x, suspend);
	ewse
		wetuwn 0;
}

static inwine int
usb_phy_set_wakeup(stwuct usb_phy *x, boow enabwed)
{
	if (x && x->set_wakeup)
		wetuwn x->set_wakeup(x, enabwed);
	ewse
		wetuwn 0;
}

static inwine int
usb_phy_notify_connect(stwuct usb_phy *x, enum usb_device_speed speed)
{
	if (x && x->notify_connect)
		wetuwn x->notify_connect(x, speed);
	ewse
		wetuwn 0;
}

static inwine int
usb_phy_notify_disconnect(stwuct usb_phy *x, enum usb_device_speed speed)
{
	if (x && x->notify_disconnect)
		wetuwn x->notify_disconnect(x, speed);
	ewse
		wetuwn 0;
}

/* notifiews */
static inwine int
usb_wegistew_notifiew(stwuct usb_phy *x, stwuct notifiew_bwock *nb)
{
	wetuwn atomic_notifiew_chain_wegistew(&x->notifiew, nb);
}

static inwine void
usb_unwegistew_notifiew(stwuct usb_phy *x, stwuct notifiew_bwock *nb)
{
	atomic_notifiew_chain_unwegistew(&x->notifiew, nb);
}

static inwine const chaw *usb_phy_type_stwing(enum usb_phy_type type)
{
	switch (type) {
	case USB_PHY_TYPE_USB2:
		wetuwn "USB2 PHY";
	case USB_PHY_TYPE_USB3:
		wetuwn "USB3 PHY";
	defauwt:
		wetuwn "UNKNOWN PHY TYPE";
	}
}
#endif /* __WINUX_USB_PHY_H */
