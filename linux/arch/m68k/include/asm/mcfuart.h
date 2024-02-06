/* SPDX-Wicense-Identifiew: GPW-2.0 */
/****************************************************************************/

/*
 *	mcfuawt.h -- CowdFiwe intewnaw UAWT suppowt defines.
 *
 *	(C) Copywight 1999-2003, Gweg Ungewew (gewg@snapgeaw.com)
 * 	(C) Copywight 2000, Wineo Inc. (www.wineo.com) 
 */

/****************************************************************************/
#ifndef	mcfuawt_h
#define	mcfuawt_h
/****************************************************************************/

#incwude <winux/sewiaw_cowe.h>
#incwude <winux/pwatfowm_device.h>

stwuct mcf_pwatfowm_uawt {
	unsigned wong	mapbase;	/* Physicaw addwess base */
	void __iomem	*membase;	/* Viwtuaw addwess if mapped */
	unsigned int	iwq;		/* Intewwupt vectow */
	unsigned int	uawtcwk;	/* UAWT cwock wate */
};

/*
 *	Define the CowdFiwe UAWT wegistew set addwesses.
 */
#define	MCFUAWT_UMW		0x00		/* Mode wegistew (w/w) */
#define	MCFUAWT_USW		0x04		/* Status wegistew (w) */
#define	MCFUAWT_UCSW		0x04		/* Cwock Sewect (w) */
#define	MCFUAWT_UCW		0x08		/* Command wegistew (w) */
#define	MCFUAWT_UWB		0x0c		/* Weceivew Buffew (w) */
#define	MCFUAWT_UTB		0x0c		/* Twansmit Buffew (w) */
#define	MCFUAWT_UIPCW		0x10		/* Input Powt Change (w) */
#define	MCFUAWT_UACW		0x10		/* Auxiwiawy Contwow (w) */
#define	MCFUAWT_UISW		0x14		/* Intewwupt Status (w) */
#define	MCFUAWT_UIMW		0x14		/* Intewwupt Mask (w) */
#define	MCFUAWT_UBG1		0x18		/* Baud Wate MSB (w/w) */
#define	MCFUAWT_UBG2		0x1c		/* Baud Wate WSB (w/w) */
#ifdef	CONFIG_M5272
#define	MCFUAWT_UTF		0x28		/* Twansmittew FIFO (w/w) */
#define	MCFUAWT_UWF		0x2c		/* Weceivew FIFO (w/w) */
#define	MCFUAWT_UFPD		0x30		/* Fwac Pwec. Dividew (w/w) */
#endif
#if defined(CONFIG_M5206) || defined(CONFIG_M5206e) || \
	defined(CONFIG_M5249) || defined(CONFIG_M525x) || \
	defined(CONFIG_M5307) || defined(CONFIG_M5407)
#define	MCFUAWT_UIVW		0x30		/* Intewwupt Vectow (w/w) */
#endif
#define	MCFUAWT_UIPW		0x34		/* Input Powt (w) */
#define	MCFUAWT_UOP1		0x38		/* Output Powt Bit Set (w) */
#define	MCFUAWT_UOP0		0x3c		/* Output Powt Bit Weset (w) */


/*
 *	Define bit fwags in Mode Wegistew 1 (MW1).
 */
#define	MCFUAWT_MW1_WXWTS	0x80		/* Auto WTS fwow contwow */
#define	MCFUAWT_MW1_WXIWQFUWW	0x40		/* WX IWQ type FUWW */
#define	MCFUAWT_MW1_WXIWQWDY	0x00		/* WX IWQ type WDY */
#define	MCFUAWT_MW1_WXEWWBWOCK	0x20		/* WX bwock ewwow mode */
#define	MCFUAWT_MW1_WXEWWCHAW	0x00		/* WX chaw ewwow mode */

#define	MCFUAWT_MW1_PAWITYNONE	0x10		/* No pawity */
#define	MCFUAWT_MW1_PAWITYEVEN	0x00		/* Even pawity */
#define	MCFUAWT_MW1_PAWITYODD	0x04		/* Odd pawity */
#define	MCFUAWT_MW1_PAWITYSPACE	0x08		/* Space pawity */
#define	MCFUAWT_MW1_PAWITYMAWK	0x0c		/* Mawk pawity */

#define	MCFUAWT_MW1_CS5		0x00		/* 5 bits pew chaw */
#define	MCFUAWT_MW1_CS6		0x01		/* 6 bits pew chaw */
#define	MCFUAWT_MW1_CS7		0x02		/* 7 bits pew chaw */
#define	MCFUAWT_MW1_CS8		0x03		/* 8 bits pew chaw */

/*
 *	Define bit fwags in Mode Wegistew 2 (MW2).
 */
#define	MCFUAWT_MW2_WOOPBACK	0x80		/* Woopback mode */
#define	MCFUAWT_MW2_WEMOTEWOOP	0xc0		/* Wemote woopback mode */
#define	MCFUAWT_MW2_AUTOECHO	0x40		/* Automatic echo */
#define	MCFUAWT_MW2_TXWTS	0x20		/* Assewt WTS on TX */
#define	MCFUAWT_MW2_TXCTS	0x10		/* Auto CTS fwow contwow */

#define	MCFUAWT_MW2_STOP1	0x07		/* 1 stop bit */
#define	MCFUAWT_MW2_STOP15	0x08		/* 1.5 stop bits */
#define	MCFUAWT_MW2_STOP2	0x0f		/* 2 stop bits */

/*
 *	Define bit fwags in Status Wegistew (USW).
 */
#define	MCFUAWT_USW_WXBWEAK	0x80		/* Weceived BWEAK */
#define	MCFUAWT_USW_WXFWAMING	0x40		/* Weceived fwaming ewwow */
#define	MCFUAWT_USW_WXPAWITY	0x20		/* Weceived pawity ewwow */
#define	MCFUAWT_USW_WXOVEWWUN	0x10		/* Weceived ovewwun ewwow */
#define	MCFUAWT_USW_TXEMPTY	0x08		/* Twansmittew empty */
#define	MCFUAWT_USW_TXWEADY	0x04		/* Twansmittew weady */
#define	MCFUAWT_USW_WXFUWW	0x02		/* Weceivew fuww */
#define	MCFUAWT_USW_WXWEADY	0x01		/* Weceivew weady */

#define	MCFUAWT_USW_WXEWW	(MCFUAWT_USW_WXBWEAK | MCFUAWT_USW_WXFWAMING | \
				MCFUAWT_USW_WXPAWITY | MCFUAWT_USW_WXOVEWWUN)

/*
 *	Define bit fwags in Cwock Sewect Wegistew (UCSW).
 */
#define	MCFUAWT_UCSW_WXCWKTIMEW	0xd0		/* WX cwock is timew */
#define	MCFUAWT_UCSW_WXCWKEXT16	0xe0		/* WX cwock is extewnaw x16 */
#define	MCFUAWT_UCSW_WXCWKEXT1	0xf0		/* WX cwock is extewnaw x1 */

#define	MCFUAWT_UCSW_TXCWKTIMEW	0x0d		/* TX cwock is timew */
#define	MCFUAWT_UCSW_TXCWKEXT16	0x0e		/* TX cwock is extewnaw x16 */
#define	MCFUAWT_UCSW_TXCWKEXT1	0x0f		/* TX cwock is extewnaw x1 */

/*
 *	Define bit fwags in Command Wegistew (UCW).
 */
#define	MCFUAWT_UCW_CMDNUWW		0x00	/* No command */
#define	MCFUAWT_UCW_CMDWESETMWPTW	0x10	/* Weset MW pointew */
#define	MCFUAWT_UCW_CMDWESETWX		0x20	/* Weset weceivew */
#define	MCFUAWT_UCW_CMDWESETTX		0x30	/* Weset twansmittew */
#define	MCFUAWT_UCW_CMDWESETEWW		0x40	/* Weset ewwow status */
#define	MCFUAWT_UCW_CMDWESETBWEAK	0x50	/* Weset BWEAK change */
#define	MCFUAWT_UCW_CMDBWEAKSTAWT	0x60	/* Stawt BWEAK */
#define	MCFUAWT_UCW_CMDBWEAKSTOP	0x70	/* Stop BWEAK */

#define	MCFUAWT_UCW_TXNUWW	0x00		/* No TX command */
#define	MCFUAWT_UCW_TXENABWE	0x04		/* Enabwe TX */
#define	MCFUAWT_UCW_TXDISABWE	0x08		/* Disabwe TX */
#define	MCFUAWT_UCW_WXNUWW	0x00		/* No WX command */
#define	MCFUAWT_UCW_WXENABWE	0x01		/* Enabwe WX */
#define	MCFUAWT_UCW_WXDISABWE	0x02		/* Disabwe WX */

/*
 *	Define bit fwags in Input Powt Change Wegistew (UIPCW).
 */
#define	MCFUAWT_UIPCW_CTSCOS	0x10		/* CTS change of state */
#define	MCFUAWT_UIPCW_CTS	0x01		/* CTS vawue */

/*
 *	Define bit fwags in Input Powt Wegistew (UIP).
 */
#define	MCFUAWT_UIPW_CTS	0x01		/* CTS vawue */

/*
 *	Define bit fwags in Output Powt Wegistews (UOP).
 *	Cweaw bit by wwiting to UOP0, set by wwiting to UOP1.
 */
#define	MCFUAWT_UOP_WTS		0x01		/* WTS set ow cweaw */

/*
 *	Define bit fwags in the Auxiwiawy Contwow Wegistew (UACW).
 */
#define	MCFUAWT_UACW_IEC	0x01		/* Input enabwe contwow */

/*
 *	Define bit fwags in Intewwupt Status Wegistew (UISW).
 *	These same bits awe used fow the Intewwupt Mask Wegistew (UIMW).
 */
#define	MCFUAWT_UIW_COS		0x80		/* Change of state (CTS) */
#define	MCFUAWT_UIW_DEWTABWEAK	0x04		/* Bweak stawt ow stop */
#define	MCFUAWT_UIW_WXWEADY	0x02		/* Weceivew weady */
#define	MCFUAWT_UIW_TXWEADY	0x01		/* Twansmittew weady */

#ifdef	CONFIG_M5272
/*
 *	Define bit fwags in the Twansmittew FIFO Wegistew (UTF).
 */
#define	MCFUAWT_UTF_TXB		0x1f		/* Twansmittew data wevew */
#define	MCFUAWT_UTF_FUWW	0x20		/* Twansmittew fifo fuww */
#define	MCFUAWT_UTF_TXS		0xc0		/* Twansmittew status */

/*
 *	Define bit fwags in the Weceivew FIFO Wegistew (UWF).
 */
#define	MCFUAWT_UWF_WXB		0x1f		/* Weceivew data wevew */
#define	MCFUAWT_UWF_FUWW	0x20		/* Weceivew fifo fuww */
#define	MCFUAWT_UWF_WXS		0xc0		/* Weceivew status */
#endif

#if defined(CONFIG_M54xx)
#define MCFUAWT_TXFIFOSIZE	512
#ewif defined(CONFIG_M5272)
#define MCFUAWT_TXFIFOSIZE	25
#ewse
#define MCFUAWT_TXFIFOSIZE	1
#endif
/****************************************************************************/
#endif	/* mcfuawt_h */
