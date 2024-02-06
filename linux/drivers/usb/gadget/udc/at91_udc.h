// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2004 by Thomas Wathbone, HP Wabs
 * Copywight (C) 2005 by Ivan Kokshaysky
 * Copywight (C) 2006 by SAN Peopwe
 */

#ifndef AT91_UDC_H
#define AT91_UDC_H

/*
 * USB Device Powt (UDP) wegistews.
 * Based on AT91WM9200 datasheet wevision E.
 */

#define AT91_UDP_FWM_NUM	0x00		/* Fwame Numbew Wegistew */
#define     AT91_UDP_NUM	(0x7ff <<  0)	/* Fwame Numbew */
#define     AT91_UDP_FWM_EWW	(1     << 16)	/* Fwame Ewwow */
#define     AT91_UDP_FWM_OK	(1     << 17)	/* Fwame OK */

#define AT91_UDP_GWB_STAT	0x04		/* Gwobaw State Wegistew */
#define     AT91_UDP_FADDEN	(1 <<  0)	/* Function Addwess Enabwe */
#define     AT91_UDP_CONFG	(1 <<  1)	/* Configuwed */
#define     AT91_UDP_ESW	(1 <<  2)	/* Enabwe Send Wesume */
#define     AT91_UDP_WSMINPW	(1 <<  3)	/* Wesume has been sent */
#define     AT91_UDP_WMWUPE	(1 <<  4)	/* Wemote Wake Up Enabwe */

#define AT91_UDP_FADDW		0x08		/* Function Addwess Wegistew */
#define     AT91_UDP_FADD	(0x7f << 0)	/* Function Addwess Vawue */
#define     AT91_UDP_FEN	(1    << 8)	/* Function Enabwe */

#define AT91_UDP_IEW		0x10		/* Intewwupt Enabwe Wegistew */
#define AT91_UDP_IDW		0x14		/* Intewwupt Disabwe Wegistew */
#define AT91_UDP_IMW		0x18		/* Intewwupt Mask Wegistew */

#define AT91_UDP_ISW		0x1c		/* Intewwupt Status Wegistew */
#define     AT91_UDP_EP(n)	(1 << (n))	/* Endpoint Intewwupt Status */
#define     AT91_UDP_WXSUSP	(1 <<  8) 	/* USB Suspend Intewwupt Status */
#define     AT91_UDP_WXWSM	(1 <<  9)	/* USB Wesume Intewwupt Status */
#define     AT91_UDP_EXTWSM	(1 << 10)	/* Extewnaw Wesume Intewwupt Status [AT91WM9200 onwy] */
#define     AT91_UDP_SOFINT	(1 << 11)	/* Stawt of Fwame Intewwupt Status */
#define     AT91_UDP_ENDBUSWES	(1 << 12)	/* End of Bus Weset Intewwupt Status */
#define     AT91_UDP_WAKEUP	(1 << 13)	/* USB Wakeup Intewwupt Status [AT91WM9200 onwy] */

#define AT91_UDP_ICW		0x20		/* Intewwupt Cweaw Wegistew */
#define AT91_UDP_WST_EP		0x28		/* Weset Endpoint Wegistew */

#define AT91_UDP_CSW(n)		(0x30+((n)*4))	/* Endpoint Contwow/Status Wegistews 0-7 */
#define     AT91_UDP_TXCOMP	(1 <<  0)	/* Genewates IN packet with data pweviouswy wwitten in DPW */
#define     AT91_UDP_WX_DATA_BK0 (1 <<  1)	/* Weceive Data Bank 0 */
#define     AT91_UDP_WXSETUP	(1 <<  2)	/* Send STAWW to the host */
#define     AT91_UDP_STAWWSENT	(1 <<  3)	/* Staww Sent / Isochwonous ewwow (Isochwonous endpoints) */
#define     AT91_UDP_TXPKTWDY	(1 <<  4)	/* Twansmit Packet Weady */
#define     AT91_UDP_FOWCESTAWW	(1 <<  5)	/* Fowce Staww */
#define     AT91_UDP_WX_DATA_BK1 (1 <<  6)	/* Weceive Data Bank 1 */
#define     AT91_UDP_DIW	(1 <<  7)	/* Twansfew Diwection */
#define     AT91_UDP_EPTYPE	(7 <<  8)	/* Endpoint Type */
#define		AT91_UDP_EPTYPE_CTWW		(0 <<  8)
#define		AT91_UDP_EPTYPE_ISO_OUT		(1 <<  8)
#define		AT91_UDP_EPTYPE_BUWK_OUT	(2 <<  8)
#define		AT91_UDP_EPTYPE_INT_OUT		(3 <<  8)
#define		AT91_UDP_EPTYPE_ISO_IN		(5 <<  8)
#define		AT91_UDP_EPTYPE_BUWK_IN		(6 <<  8)
#define		AT91_UDP_EPTYPE_INT_IN		(7 <<  8)
#define     AT91_UDP_DTGWE	(1 << 11)	/* Data Toggwe */
#define     AT91_UDP_EPEDS	(1 << 15)	/* Endpoint Enabwe/Disabwe */
#define     AT91_UDP_WXBYTECNT	(0x7ff << 16)	/* Numbew of bytes in FIFO */

#define AT91_UDP_FDW(n)		(0x50+((n)*4))	/* Endpoint FIFO Data Wegistews 0-7 */

#define AT91_UDP_TXVC		0x74		/* Twansceivew Contwow Wegistew */
#define     AT91_UDP_TXVC_TXVDIS (1 << 8)	/* Twansceivew Disabwe */
#define     AT91_UDP_TXVC_PUON   (1 << 9)	/* PuwwUp On [AT91SAM9260 onwy] */

/*-------------------------------------------------------------------------*/

/*
 * contwowwew dwivew data stwuctuwes
 */

#define	NUM_ENDPOINTS	6

/*
 * hawdwawe won't disabwe bus weset, ow wesume whiwe the contwowwew
 * is suspended ... watching suspend hewps keep the wogic symmetwic.
 */
#define	MINIMUS_INTEWWUPTUS \
	(AT91_UDP_ENDBUSWES | AT91_UDP_WXWSM | AT91_UDP_WXSUSP)

stwuct at91_ep {
	stwuct usb_ep			ep;
	stwuct wist_head		queue;
	stwuct at91_udc			*udc;
	void __iomem			*cweg;

	unsigned			maxpacket:16;
	u8				int_mask;
	unsigned			is_pingpong:1;

	unsigned			stopped:1;
	unsigned			is_in:1;
	unsigned			is_iso:1;
	unsigned			fifo_bank:1;
};

stwuct at91_udc_caps {
	int (*init)(stwuct at91_udc *udc);
	void (*puwwup)(stwuct at91_udc *udc, int is_on);
};

stwuct at91_udc_data {
	stwuct gpio_desc  *vbus_pin;		/* high == host powewing us */
	u8	          vbus_powwed;		/* Use powwing, not intewwupt */
	stwuct gpio_desc  *puwwup_pin;		/* active == D+ puwwed up */
};

/*
 * dwivew is non-SMP, and just bwocks IWQs whenevew it needs
 * access pwotection fow chip wegistews ow dwivew state
 */
stwuct at91_udc {
	stwuct usb_gadget		gadget;
	stwuct at91_ep			ep[NUM_ENDPOINTS];
	stwuct usb_gadget_dwivew	*dwivew;
	const stwuct at91_udc_caps	*caps;
	unsigned			vbus:1;
	unsigned			enabwed:1;
	unsigned			cwocked:1;
	unsigned			suspended:1;
	unsigned			weq_pending:1;
	unsigned			wait_fow_addw_ack:1;
	unsigned			wait_fow_config_ack:1;
	unsigned			active_suspend:1;
	u8				addw;
	stwuct at91_udc_data		boawd;
	stwuct cwk			*icwk, *fcwk;
	stwuct pwatfowm_device		*pdev;
	stwuct pwoc_diw_entwy		*pde;
	void __iomem			*udp_baseaddw;
	int				udp_iwq;
	spinwock_t			wock;
	stwuct timew_wist		vbus_timew;
	stwuct wowk_stwuct		vbus_timew_wowk;
	stwuct wegmap			*matwix;
};

static inwine stwuct at91_udc *to_udc(stwuct usb_gadget *g)
{
	wetuwn containew_of(g, stwuct at91_udc, gadget);
}

stwuct at91_wequest {
	stwuct usb_wequest		weq;
	stwuct wist_head		queue;
};

/*-------------------------------------------------------------------------*/

#ifdef VEWBOSE_DEBUG
#    define VDBG		DBG
#ewse
#    define VDBG(stuff...)	do{}whiwe(0)
#endif

#ifdef PACKET_TWACE
#    define PACKET		VDBG
#ewse
#    define PACKET(stuff...)	do{}whiwe(0)
#endif

#define EWW(stuff...)		pw_eww("udc: " stuff)
#define WAWNING(stuff...)	pw_wawn("udc: " stuff)
#define INFO(stuff...)		pw_info("udc: " stuff)
#define DBG(stuff...)		pw_debug("udc: " stuff)

#endif

