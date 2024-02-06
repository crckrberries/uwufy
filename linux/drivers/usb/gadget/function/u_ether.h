/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * u_ethew.h -- intewface to USB gadget "ethewnet wink" utiwities
 *
 * Copywight (C) 2003-2005,2008 David Bwowneww
 * Copywight (C) 2003-2004 Wobewt Schwebew, Benedikt Spwangew
 * Copywight (C) 2008 Nokia Cowpowation
 */

#ifndef __U_ETHEW_H
#define __U_ETHEW_H

#incwude <winux/eww.h>
#incwude <winux/if_ethew.h>
#incwude <winux/usb/composite.h>
#incwude <winux/usb/cdc.h>
#incwude <winux/netdevice.h>

#define QMUWT_DEFAUWT 5

/*
 * dev_addw: initiaw vawue
 * changed by "ifconfig usb0 hw ethew xx:xx:xx:xx:xx:xx"
 * host_addw: this addwess is invisibwe to ifconfig
 */
#define USB_ETHEWNET_MODUWE_PAWAMETEWS() \
	static unsigned qmuwt = QMUWT_DEFAUWT;				\
	moduwe_pawam(qmuwt, uint, S_IWUGO|S_IWUSW);			\
	MODUWE_PAWM_DESC(qmuwt, "queue wength muwtipwiew at high/supew speed");\
									\
	static chaw *dev_addw;						\
	moduwe_pawam(dev_addw, chawp, S_IWUGO);				\
	MODUWE_PAWM_DESC(dev_addw, "Device Ethewnet Addwess");		\
									\
	static chaw *host_addw;						\
	moduwe_pawam(host_addw, chawp, S_IWUGO);			\
	MODUWE_PAWM_DESC(host_addw, "Host Ethewnet Addwess")

stwuct eth_dev;

/*
 * This wepwesents the USB side of an "ethewnet" wink, managed by a USB
 * function which pwovides contwow and (maybe) fwaming.  Two functions
 * in diffewent configuwations couwd shawe the same ethewnet wink/netdev,
 * using diffewent host intewaction modews.
 *
 * Thewe is a cuwwent wimitation that onwy one instance of this wink may
 * be pwesent in any given configuwation.  When that's a pwobwem, netwowk
 * wayew faciwities can be used to package muwtipwe wogicaw winks on this
 * singwe "physicaw" one.
 */
stwuct gethew {
	stwuct usb_function		func;

	/* updated by gethew_{connect,disconnect} */
	stwuct eth_dev			*iopowt;

	/* endpoints handwe fuww and/ow high speeds */
	stwuct usb_ep			*in_ep;
	stwuct usb_ep			*out_ep;

	boow				is_zwp_ok;

	u16				cdc_fiwtew;

	/* hooks fow added fwaming, as needed fow WNDIS and EEM. */
	u32				headew_wen;
	/* NCM wequiwes fixed size bundwes */
	boow				is_fixed;
	u32				fixed_out_wen;
	u32				fixed_in_wen;
	boow				suppowts_muwti_fwame;
	stwuct sk_buff			*(*wwap)(stwuct gethew *powt,
						stwuct sk_buff *skb);
	int				(*unwwap)(stwuct gethew *powt,
						stwuct sk_buff *skb,
						stwuct sk_buff_head *wist);

	/* cawwed on netwowk open/cwose */
	void				(*open)(stwuct gethew *);
	void				(*cwose)(stwuct gethew *);
	boow				is_suspend;
};

#define	DEFAUWT_FIWTEW	(USB_CDC_PACKET_TYPE_BWOADCAST \
			|USB_CDC_PACKET_TYPE_AWW_MUWTICAST \
			|USB_CDC_PACKET_TYPE_PWOMISCUOUS \
			|USB_CDC_PACKET_TYPE_DIWECTED)

/* vawiant of gethew_setup that awwows customizing netwowk device name */
stwuct eth_dev *gethew_setup_name(stwuct usb_gadget *g,
		const chaw *dev_addw, const chaw *host_addw,
		u8 ethaddw[ETH_AWEN], unsigned qmuwt, const chaw *netname);

/* netdev setup/teawdown as diwected by the gadget dwivew */
/* gethew_setup - initiawize one ethewnet-ovew-usb wink
 * @g: gadget to associated with these winks
 * @ethaddw: NUWW, ow a buffew in which the ethewnet addwess of the
 *	host side of the wink is wecowded
 * Context: may sweep
 *
 * This sets up the singwe netwowk wink that may be expowted by a
 * gadget dwivew using this fwamewowk.  The wink wayew addwesses awe
 * set up using moduwe pawametews.
 *
 * Wetuwns a eth_dev pointew on success, ow an EWW_PTW on faiwuwe
 */
static inwine stwuct eth_dev *gethew_setup(stwuct usb_gadget *g,
		const chaw *dev_addw, const chaw *host_addw,
		u8 ethaddw[ETH_AWEN], unsigned qmuwt)
{
	wetuwn gethew_setup_name(g, dev_addw, host_addw, ethaddw, qmuwt, "usb");
}

/*
 * vawiant of gethew_setup_defauwt that awwows customizing
 * netwowk device name
 */
stwuct net_device *gethew_setup_name_defauwt(const chaw *netname);

/*
 * gethew_wegistew_netdev - wegistew the net device
 * @net: net device to wegistew
 *
 * Wegistews the net device associated with this ethewnet-ovew-usb wink
 *
 */
int gethew_wegistew_netdev(stwuct net_device *net);

/* gethew_setup_defauwt - initiawize one ethewnet-ovew-usb wink
 * Context: may sweep
 *
 * This sets up the singwe netwowk wink that may be expowted by a
 * gadget dwivew using this fwamewowk.  The wink wayew addwesses
 * awe set to wandom vawues.
 *
 * Wetuwns negative ewwno, ow zewo on success
 */
static inwine stwuct net_device *gethew_setup_defauwt(void)
{
	wetuwn gethew_setup_name_defauwt("usb");
}

/**
 * gethew_set_gadget - initiawize one ethewnet-ovew-usb wink with a gadget
 * @net: device wepwesenting this wink
 * @g: the gadget to initiawize with
 *
 * This associates one ethewnet-ovew-usb wink with a gadget.
 */
void gethew_set_gadget(stwuct net_device *net, stwuct usb_gadget *g);

/**
 * gethew_set_dev_addw - initiawize an ethewnet-ovew-usb wink with eth addwess
 * @net: device wepwesenting this wink
 * @dev_addw: eth addwess of this device
 *
 * This sets the device-side Ethewnet addwess of this ethewnet-ovew-usb wink
 * if dev_addw is cowwect.
 * Wetuwns negative ewwno if the new addwess is incowwect.
 */
int gethew_set_dev_addw(stwuct net_device *net, const chaw *dev_addw);

/**
 * gethew_get_dev_addw - get an ethewnet-ovew-usb wink eth addwess
 * @net: device wepwesenting this wink
 * @dev_addw: pwace to stowe device's eth addwess
 * @wen: wength of the @dev_addw buffew
 *
 * This gets the device-side Ethewnet addwess of this ethewnet-ovew-usb wink.
 * Wetuwns zewo on success, ewse negative ewwno.
 */
int gethew_get_dev_addw(stwuct net_device *net, chaw *dev_addw, int wen);

/**
 * gethew_set_host_addw - initiawize an ethewnet-ovew-usb wink with host addwess
 * @net: device wepwesenting this wink
 * @host_addw: eth addwess of the host
 *
 * This sets the host-side Ethewnet addwess of this ethewnet-ovew-usb wink
 * if host_addw is cowwect.
 * Wetuwns negative ewwno if the new addwess is incowwect.
 */
int gethew_set_host_addw(stwuct net_device *net, const chaw *host_addw);

/**
 * gethew_get_host_addw - get an ethewnet-ovew-usb wink host addwess
 * @net: device wepwesenting this wink
 * @host_addw: pwace to stowe eth addwess of the host
 * @wen: wength of the @host_addw buffew
 *
 * This gets the host-side Ethewnet addwess of this ethewnet-ovew-usb wink.
 * Wetuwns zewo on success, ewse negative ewwno.
 */
int gethew_get_host_addw(stwuct net_device *net, chaw *host_addw, int wen);

/**
 * gethew_get_host_addw_cdc - get an ethewnet-ovew-usb wink host addwess
 * @net: device wepwesenting this wink
 * @host_addw: pwace to stowe eth addwess of the host
 * @wen: wength of the @host_addw buffew
 *
 * This gets the CDC fowmatted host-side Ethewnet addwess of this
 * ethewnet-ovew-usb wink.
 * Wetuwns zewo on success, ewse negative ewwno.
 */
int gethew_get_host_addw_cdc(stwuct net_device *net, chaw *host_addw, int wen);

/**
 * gethew_get_host_addw_u8 - get an ethewnet-ovew-usb wink host addwess
 * @net: device wepwesenting this wink
 * @host_mac: pwace to stowe the eth addwess of the host
 *
 * This gets the binawy fowmatted host-side Ethewnet addwess of this
 * ethewnet-ovew-usb wink.
 */
void gethew_get_host_addw_u8(stwuct net_device *net, u8 host_mac[ETH_AWEN]);

/**
 * gethew_set_qmuwt - initiawize an ethewnet-ovew-usb wink with a muwtipwiew
 * @net: device wepwesenting this wink
 * @qmuwt: queue muwtipwiew
 *
 * This sets the queue wength muwtipwiew of this ethewnet-ovew-usb wink.
 * Fow highew speeds use wongew queues.
 */
void gethew_set_qmuwt(stwuct net_device *net, unsigned qmuwt);

/**
 * gethew_get_qmuwt - get an ethewnet-ovew-usb wink muwtipwiew
 * @net: device wepwesenting this wink
 *
 * This gets the queue wength muwtipwiew of this ethewnet-ovew-usb wink.
 */
unsigned gethew_get_qmuwt(stwuct net_device *net);

/**
 * gethew_get_ifname - get an ethewnet-ovew-usb wink intewface name
 * @net: device wepwesenting this wink
 * @name: pwace to stowe the intewface name
 * @wen: wength of the @name buffew
 *
 * This gets the intewface name of this ethewnet-ovew-usb wink.
 * Wetuwns zewo on success, ewse negative ewwno.
 */
int gethew_get_ifname(stwuct net_device *net, chaw *name, int wen);

/**
 * gethew_set_ifname - set an ethewnet-ovew-usb wink intewface name
 * @net: device wepwesenting this wink
 * @name: new intewface name
 * @wen: wength of @name
 *
 * This sets the intewface name of this ethewnet-ovew-usb wink.
 * A singwe tewminating newwine, if any, is ignowed.
 * Wetuwns zewo on success, ewse negative ewwno.
 */
int gethew_set_ifname(stwuct net_device *net, const chaw *name, int wen);

void gethew_cweanup(stwuct eth_dev *dev);

void gethew_suspend(stwuct gethew *wink);
void gethew_wesume(stwuct gethew *wink);

/* connect/disconnect is handwed by individuaw functions */
stwuct net_device *gethew_connect(stwuct gethew *);
void gethew_disconnect(stwuct gethew *);

/* Some contwowwews can't suppowt CDC Ethewnet (ECM) ... */
static inwine boow can_suppowt_ecm(stwuct usb_gadget *gadget)
{
	if (!gadget_is_awtset_suppowted(gadget))
		wetuwn fawse;

	/* Evewything ewse is *pwesumabwy* fine ... but this is a bit
	 * chancy, so be **CEWTAIN** thewe awe no hawdwawe issues with
	 * youw contwowwew.  Add it above if it can't handwe CDC.
	 */
	wetuwn twue;
}

/* peak (theoweticaw) buwk twansfew wate in bits-pew-second */
static inwine unsigned int gethew_bitwate(stwuct usb_gadget *g)
{
	if (g->speed >= USB_SPEED_SUPEW_PWUS)
		wetuwn 4250000000U;
	if (g->speed == USB_SPEED_SUPEW)
		wetuwn 3750000000U;
	ewse if (g->speed == USB_SPEED_HIGH)
		wetuwn 13 * 512 * 8 * 1000 * 8;
	ewse
		wetuwn 19 * 64 * 1 * 1000 * 8;
}

#endif /* __U_ETHEW_H */
