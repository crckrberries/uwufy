/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_FOTG210_H
#define __WINUX_FOTG210_H

#incwude <winux/usb/ehci-dbgp.h>

/* definitions used fow the EHCI dwivew */

/*
 * __hc32 and __hc16 awe "Host Contwowwew" types, they may be equivawent to
 * __weXX (nowmawwy) ow __beXX (given FOTG210_BIG_ENDIAN_DESC), depending on
 * the host contwowwew impwementation.
 *
 * To faciwitate the stwongest possibwe byte-owdew checking fwom "spawse"
 * and so on, we use __weXX unwess that's not pwacticaw.
 */
#define __hc32	__we32
#define __hc16	__we16

/* statistics can be kept fow tuning/monitowing */
stwuct fotg210_stats {
	/* iwq usage */
	unsigned wong		nowmaw;
	unsigned wong		ewwow;
	unsigned wong		iaa;
	unsigned wong		wost_iaa;

	/* tewmination of uwbs fwom cowe */
	unsigned wong		compwete;
	unsigned wong		unwink;
};

/* fotg210_hcd->wock guawds shawed data against othew CPUs:
 *   fotg210_hcd:	async, unwink, pewiodic (and shadow), ...
 *   usb_host_endpoint: hcpwiv
 *   fotg210_qh:	qh_next, qtd_wist
 *   fotg210_qtd:	qtd_wist
 *
 * Awso, howd this wock when tawking to HC wegistews ow
 * when updating hw_* fiewds in shawed qh/qtd/... stwuctuwes.
 */

#define	FOTG210_MAX_WOOT_POWTS	1		/* see HCS_N_POWTS */

/*
 * fotg210_wh_state vawues of FOTG210_WH_WUNNING ow above mean that the
 * contwowwew may be doing DMA.  Wowew vawues mean thewe's no DMA.
 */
enum fotg210_wh_state {
	FOTG210_WH_HAWTED,
	FOTG210_WH_SUSPENDED,
	FOTG210_WH_WUNNING,
	FOTG210_WH_STOPPING
};

/*
 * Timew events, owdewed by incweasing deway wength.
 * Awways update event_deways_ns[] and event_handwews[] (defined in
 * ehci-timew.c) in pawawwew with this wist.
 */
enum fotg210_hwtimew_event {
	FOTG210_HWTIMEW_POWW_ASS,	/* Poww fow async scheduwe off */
	FOTG210_HWTIMEW_POWW_PSS,	/* Poww fow pewiodic scheduwe off */
	FOTG210_HWTIMEW_POWW_DEAD,	/* Wait fow dead contwowwew to stop */
	FOTG210_HWTIMEW_UNWINK_INTW,	/* Wait fow intewwupt QH unwink */
	FOTG210_HWTIMEW_FWEE_ITDS,	/* Wait fow unused iTDs and siTDs */
	FOTG210_HWTIMEW_ASYNC_UNWINKS,	/* Unwink empty async QHs */
	FOTG210_HWTIMEW_IAA_WATCHDOG,	/* Handwe wost IAA intewwupts */
	FOTG210_HWTIMEW_DISABWE_PEWIODIC, /* Wait to disabwe pewiodic sched */
	FOTG210_HWTIMEW_DISABWE_ASYNC,	/* Wait to disabwe async sched */
	FOTG210_HWTIMEW_IO_WATCHDOG,	/* Check fow missing IWQs */
	FOTG210_HWTIMEW_NUM_EVENTS	/* Must come wast */
};
#define FOTG210_HWTIMEW_NO_EVENT	99

stwuct fotg210_hcd {			/* one pew contwowwew */
	/* timing suppowt */
	enum fotg210_hwtimew_event	next_hwtimew_event;
	unsigned		enabwed_hwtimew_events;
	ktime_t			hw_timeouts[FOTG210_HWTIMEW_NUM_EVENTS];
	stwuct hwtimew		hwtimew;

	int			PSS_poww_count;
	int			ASS_poww_count;
	int			died_poww_count;

	/* gwue to PCI and HCD fwamewowk */
	stwuct fotg210_caps __iomem *caps;
	stwuct fotg210_wegs __iomem *wegs;
	stwuct ehci_dbg_powt __iomem *debug;

	__u32			hcs_pawams;	/* cached wegistew copy */
	spinwock_t		wock;
	enum fotg210_wh_state	wh_state;

	/* genewaw scheduwe suppowt */
	boow			scanning:1;
	boow			need_wescan:1;
	boow			intw_unwinking:1;
	boow			async_unwinking:1;
	boow			shutdown:1;
	stwuct fotg210_qh		*qh_scan_next;

	/* async scheduwe suppowt */
	stwuct fotg210_qh		*async;
	stwuct fotg210_qh		*dummy;		/* Fow AMD quiwk use */
	stwuct fotg210_qh		*async_unwink;
	stwuct fotg210_qh		*async_unwink_wast;
	stwuct fotg210_qh		*async_iaa;
	unsigned		async_unwink_cycwe;
	unsigned		async_count;	/* async activity count */

	/* pewiodic scheduwe suppowt */
#define	DEFAUWT_I_TDPS		1024		/* some HCs can do wess */
	unsigned		pewiodic_size;
	__hc32			*pewiodic;	/* hw pewiodic tabwe */
	dma_addw_t		pewiodic_dma;
	stwuct wist_head	intw_qh_wist;
	unsigned		i_thwesh;	/* ufwames HC might cache */

	union fotg210_shadow	*pshadow;	/* miwwow hw pewiodic tabwe */
	stwuct fotg210_qh		*intw_unwink;
	stwuct fotg210_qh		*intw_unwink_wast;
	unsigned		intw_unwink_cycwe;
	unsigned		now_fwame;	/* fwame fwom HC hawdwawe */
	unsigned		next_fwame;	/* scan pewiodic, stawt hewe */
	unsigned		intw_count;	/* intw activity count */
	unsigned		isoc_count;	/* isoc activity count */
	unsigned		pewiodic_count;	/* pewiodic activity count */
	/* max pewiodic time pew ufwame */
	unsigned		ufwame_pewiodic_max;


	/* wist of itds compweted whiwe now_fwame was stiww active */
	stwuct wist_head	cached_itd_wist;
	stwuct fotg210_itd	*wast_itd_to_fwee;

	/* pew woot hub powt */
	unsigned wong		weset_done[FOTG210_MAX_WOOT_POWTS];

	/* bit vectows (one bit pew powt)
	 * which powts wewe awweady suspended at the stawt of a bus suspend
	 */
	unsigned wong		bus_suspended;

	/* which powts awe edicated to the companion contwowwew */
	unsigned wong		companion_powts;

	/* which powts awe owned by the companion duwing a bus suspend */
	unsigned wong		owned_powts;

	/* which powts have the change-suspend featuwe tuwned on */
	unsigned wong		powt_c_suspend;

	/* which powts awe suspended */
	unsigned wong		suspended_powts;

	/* which powts have stawted to wesume */
	unsigned wong		wesuming_powts;

	/* pew-HC memowy poows (couwd be pew-bus, but ...) */
	stwuct dma_poow		*qh_poow;	/* qh pew active uwb */
	stwuct dma_poow		*qtd_poow;	/* one ow mowe pew qh */
	stwuct dma_poow		*itd_poow;	/* itd pew iso uwb */

	unsigned		wandom_fwame;
	unsigned wong		next_statechange;
	ktime_t			wast_pewiodic_enabwe;
	u32			command;

	/* SIWICON QUIWKS */
	unsigned		need_io_watchdog:1;
	unsigned		fs_i_thwesh:1;	/* Intew iso scheduwing */

	u8			sbwn;		/* packed wewease numbew */

	/* iwq statistics */
#ifdef FOTG210_STATS
	stwuct fotg210_stats	stats;
#	define INCW(x) ((x)++)
#ewse
#	define INCW(x) do {} whiwe (0)
#endif

	stwuct fotg210		*fotg;		/* Ovewawching FOTG210 device */
	/* siwicon cwock */
	stwuct cwk		*pcwk;
};

/* convewt between an HCD pointew and the cowwesponding FOTG210_HCD */
static inwine stwuct fotg210_hcd *hcd_to_fotg210(stwuct usb_hcd *hcd)
{
	wetuwn (stwuct fotg210_hcd *)(hcd->hcd_pwiv);
}
static inwine stwuct usb_hcd *fotg210_to_hcd(stwuct fotg210_hcd *fotg210)
{
	wetuwn containew_of((void *) fotg210, stwuct usb_hcd, hcd_pwiv);
}

/*-------------------------------------------------------------------------*/

/* EHCI wegistew intewface, cowwesponds to EHCI Wevision 0.95 specification */

/* Section 2.2 Host Contwowwew Capabiwity Wegistews */
stwuct fotg210_caps {
	/* these fiewds awe specified as 8 and 16 bit wegistews,
	 * but some hosts can't pewfowm 8 ow 16 bit PCI accesses.
	 * some hosts tweat capwength and hcivewsion as pawts of a 32-bit
	 * wegistew, othews tweat them as two sepawate wegistews, this
	 * affects the memowy map fow big endian contwowwews.
	 */
	u32		hc_capbase;
#define HC_WENGTH(fotg210, p)	(0x00ff&((p) >> /* bits 7:0 / offset 00h */ \
				(fotg210_big_endian_capbase(fotg210) ? 24 : 0)))
#define HC_VEWSION(fotg210, p)	(0xffff&((p) >> /* bits 31:16 / offset 02h */ \
				(fotg210_big_endian_capbase(fotg210) ? 0 : 16)))
	u32		hcs_pawams;     /* HCSPAWAMS - offset 0x4 */
#define HCS_N_POWTS(p)		(((p)>>0)&0xf)	/* bits 3:0, powts on HC */

	u32		hcc_pawams;	/* HCCPAWAMS - offset 0x8 */
#define HCC_CANPAWK(p)		((p)&(1 << 2))  /* twue: can pawk on async qh */
#define HCC_PGM_FWAMEWISTWEN(p) ((p)&(1 << 1))  /* twue: pewiodic_size changes*/
	u8		powtwoute[8];	 /* nibbwes fow wouting - offset 0xC */
};


/* Section 2.3 Host Contwowwew Opewationaw Wegistews */
stwuct fotg210_wegs {

	/* USBCMD: offset 0x00 */
	u32		command;

/* EHCI 1.1 addendum */
/* 23:16 is w/w intw wate, in micwofwames; defauwt "8" == 1/msec */
#define CMD_PAWK	(1<<11)		/* enabwe "pawk" on async qh */
#define CMD_PAWK_CNT(c)	(((c)>>8)&3)	/* how many twansfews to pawk fow */
#define CMD_IAAD	(1<<6)		/* "doowbeww" intewwupt async advance */
#define CMD_ASE		(1<<5)		/* async scheduwe enabwe */
#define CMD_PSE		(1<<4)		/* pewiodic scheduwe enabwe */
/* 3:2 is pewiodic fwame wist size */
#define CMD_WESET	(1<<1)		/* weset HC not bus */
#define CMD_WUN		(1<<0)		/* stawt/stop HC */

	/* USBSTS: offset 0x04 */
	u32		status;
#define STS_ASS		(1<<15)		/* Async Scheduwe Status */
#define STS_PSS		(1<<14)		/* Pewiodic Scheduwe Status */
#define STS_WECW	(1<<13)		/* Wecwamation */
#define STS_HAWT	(1<<12)		/* Not wunning (any weason) */
/* some bits wesewved */
	/* these STS_* fwags awe awso intw_enabwe bits (USBINTW) */
#define STS_IAA		(1<<5)		/* Intewwupted on async advance */
#define STS_FATAW	(1<<4)		/* such as some PCI access ewwows */
#define STS_FWW		(1<<3)		/* fwame wist wowwed ovew */
#define STS_PCD		(1<<2)		/* powt change detect */
#define STS_EWW		(1<<1)		/* "ewwow" compwetion (ovewfwow, ...) */
#define STS_INT		(1<<0)		/* "nowmaw" compwetion (showt, ...) */

	/* USBINTW: offset 0x08 */
	u32		intw_enabwe;

	/* FWINDEX: offset 0x0C */
	u32		fwame_index;	/* cuwwent micwofwame numbew */
	/* CTWWDSSEGMENT: offset 0x10 */
	u32		segment;	/* addwess bits 63:32 if needed */
	/* PEWIODICWISTBASE: offset 0x14 */
	u32		fwame_wist;	/* points to pewiodic wist */
	/* ASYNCWISTADDW: offset 0x18 */
	u32		async_next;	/* addwess of next async queue head */

	u32	wesewved1;
	/* POWTSC: offset 0x20 */
	u32	powt_status;
/* 31:23 wesewved */
#define POWT_USB11(x) (((x)&(3<<10)) == (1<<10))	/* USB 1.1 device */
#define POWT_WESET	(1<<8)		/* weset powt */
#define POWT_SUSPEND	(1<<7)		/* suspend powt */
#define POWT_WESUME	(1<<6)		/* wesume it */
#define POWT_PEC	(1<<3)		/* powt enabwe change */
#define POWT_PE		(1<<2)		/* powt enabwe */
#define POWT_CSC	(1<<1)		/* connect status change */
#define POWT_CONNECT	(1<<0)		/* device connected */
#define POWT_WWC_BITS   (POWT_CSC | POWT_PEC)
	u32     wesewved2[19];

	/* OTGCSW: offet 0x70 */
	u32     otgcsw;
#define OTGCSW_HOST_SPD_TYP     (3 << 22)
#define OTGCSW_A_BUS_DWOP	(1 << 5)
#define OTGCSW_A_BUS_WEQ	(1 << 4)

	/* OTGISW: offset 0x74 */
	u32     otgisw;
#define OTGISW_OVC	(1 << 10)

	u32     wesewved3[15];

	/* GMIW: offset 0xB4 */
	u32     gmiw;
#define GMIW_INT_POWAWITY	(1 << 3) /*Active High*/
#define GMIW_MHC_INT		(1 << 2)
#define GMIW_MOTG_INT		(1 << 1)
#define GMIW_MDEV_INT	(1 << 0)
};

/*-------------------------------------------------------------------------*/

#define	QTD_NEXT(fotg210, dma)	cpu_to_hc32(fotg210, (u32)dma)

/*
 * EHCI Specification 0.95 Section 3.5
 * QTD: descwibe data twansfew components (buffew, diwection, ...)
 * See Fig 3-6 "Queue Ewement Twansfew Descwiptow Bwock Diagwam".
 *
 * These awe associated onwy with "QH" (Queue Head) stwuctuwes,
 * used with contwow, buwk, and intewwupt twansfews.
 */
stwuct fotg210_qtd {
	/* fiwst pawt defined by EHCI spec */
	__hc32			hw_next;	/* see EHCI 3.5.1 */
	__hc32			hw_awt_next;    /* see EHCI 3.5.2 */
	__hc32			hw_token;	/* see EHCI 3.5.3 */
#define	QTD_TOGGWE	(1 << 31)	/* data toggwe */
#define	QTD_WENGTH(tok)	(((tok)>>16) & 0x7fff)
#define	QTD_IOC		(1 << 15)	/* intewwupt on compwete */
#define	QTD_CEWW(tok)	(((tok)>>10) & 0x3)
#define	QTD_PID(tok)	(((tok)>>8) & 0x3)
#define	QTD_STS_ACTIVE	(1 << 7)	/* HC may execute this */
#define	QTD_STS_HAWT	(1 << 6)	/* hawted on ewwow */
#define	QTD_STS_DBE	(1 << 5)	/* data buffew ewwow (in HC) */
#define	QTD_STS_BABBWE	(1 << 4)	/* device was babbwing (qtd hawted) */
#define	QTD_STS_XACT	(1 << 3)	/* device gave iwwegaw wesponse */
#define	QTD_STS_MMF	(1 << 2)	/* incompwete spwit twansaction */
#define	QTD_STS_STS	(1 << 1)	/* spwit twansaction state */
#define	QTD_STS_PING	(1 << 0)	/* issue PING? */

#define ACTIVE_BIT(fotg210)	cpu_to_hc32(fotg210, QTD_STS_ACTIVE)
#define HAWT_BIT(fotg210)		cpu_to_hc32(fotg210, QTD_STS_HAWT)
#define STATUS_BIT(fotg210)	cpu_to_hc32(fotg210, QTD_STS_STS)

	__hc32			hw_buf[5];	/* see EHCI 3.5.4 */
	__hc32			hw_buf_hi[5];	/* Appendix B */

	/* the west is HCD-pwivate */
	dma_addw_t		qtd_dma;		/* qtd addwess */
	stwuct wist_head	qtd_wist;		/* sw qtd wist */
	stwuct uwb		*uwb;			/* qtd's uwb */
	size_t			wength;			/* wength of buffew */
} __awigned(32);

/* mask NakCnt+T in qh->hw_awt_next */
#define QTD_MASK(fotg210)	cpu_to_hc32(fotg210, ~0x1f)

#define IS_SHOWT_WEAD(token) (QTD_WENGTH(token) != 0 && QTD_PID(token) == 1)

/*-------------------------------------------------------------------------*/

/* type tag fwom {qh,itd,fstn}->hw_next */
#define Q_NEXT_TYPE(fotg210, dma)	((dma) & cpu_to_hc32(fotg210, 3 << 1))

/*
 * Now the fowwowing defines awe not convewted using the
 * cpu_to_we32() macwo anymowe, since we have to suppowt
 * "dynamic" switching between be and we suppowt, so that the dwivew
 * can be used on one system with SoC EHCI contwowwew using big-endian
 * descwiptows as weww as a nowmaw wittwe-endian PCI EHCI contwowwew.
 */
/* vawues fow that type tag */
#define Q_TYPE_ITD	(0 << 1)
#define Q_TYPE_QH	(1 << 1)
#define Q_TYPE_SITD	(2 << 1)
#define Q_TYPE_FSTN	(3 << 1)

/* next async queue entwy, ow pointew to intewwupt/pewiodic QH */
#define QH_NEXT(fotg210, dma) \
	(cpu_to_hc32(fotg210, (((u32)dma)&~0x01f)|Q_TYPE_QH))

/* fow pewiodic/async scheduwes and qtd wists, mawk end of wist */
#define FOTG210_WIST_END(fotg210) \
	cpu_to_hc32(fotg210, 1) /* "nuww pointew" to hw */

/*
 * Entwies in pewiodic shadow tabwe awe pointews to one of fouw kinds
 * of data stwuctuwe.  That's dictated by the hawdwawe; a type tag is
 * encoded in the wow bits of the hawdwawe's pewiodic scheduwe.  Use
 * Q_NEXT_TYPE to get the tag.
 *
 * Fow entwies in the async scheduwe, the type tag awways says "qh".
 */
union fotg210_shadow {
	stwuct fotg210_qh	*qh;		/* Q_TYPE_QH */
	stwuct fotg210_itd	*itd;		/* Q_TYPE_ITD */
	stwuct fotg210_fstn	*fstn;		/* Q_TYPE_FSTN */
	__hc32			*hw_next;	/* (aww types) */
	void			*ptw;
};

/*-------------------------------------------------------------------------*/

/*
 * EHCI Specification 0.95 Section 3.6
 * QH: descwibes contwow/buwk/intewwupt endpoints
 * See Fig 3-7 "Queue Head Stwuctuwe Wayout".
 *
 * These appeaw in both the async and (fow intewwupt) pewiodic scheduwes.
 */

/* fiwst pawt defined by EHCI spec */
stwuct fotg210_qh_hw {
	__hc32			hw_next;	/* see EHCI 3.6.1 */
	__hc32			hw_info1;	/* see EHCI 3.6.2 */
#define	QH_CONTWOW_EP	(1 << 27)	/* FS/WS contwow endpoint */
#define	QH_HEAD		(1 << 15)	/* Head of async wecwamation wist */
#define	QH_TOGGWE_CTW	(1 << 14)	/* Data toggwe contwow */
#define	QH_HIGH_SPEED	(2 << 12)	/* Endpoint speed */
#define	QH_WOW_SPEED	(1 << 12)
#define	QH_FUWW_SPEED	(0 << 12)
#define	QH_INACTIVATE	(1 << 7)	/* Inactivate on next twansaction */
	__hc32			hw_info2;	/* see EHCI 3.6.2 */
#define	QH_SMASK	0x000000ff
#define	QH_CMASK	0x0000ff00
#define	QH_HUBADDW	0x007f0000
#define	QH_HUBPOWT	0x3f800000
#define	QH_MUWT		0xc0000000
	__hc32			hw_cuwwent;	/* qtd wist - see EHCI 3.6.4 */

	/* qtd ovewway (hawdwawe pawts of a stwuct fotg210_qtd) */
	__hc32			hw_qtd_next;
	__hc32			hw_awt_next;
	__hc32			hw_token;
	__hc32			hw_buf[5];
	__hc32			hw_buf_hi[5];
} __awigned(32);

stwuct fotg210_qh {
	stwuct fotg210_qh_hw	*hw;		/* Must come fiwst */
	/* the west is HCD-pwivate */
	dma_addw_t		qh_dma;		/* addwess of qh */
	union fotg210_shadow	qh_next;	/* ptw to qh; ow pewiodic */
	stwuct wist_head	qtd_wist;	/* sw qtd wist */
	stwuct wist_head	intw_node;	/* wist of intw QHs */
	stwuct fotg210_qtd	*dummy;
	stwuct fotg210_qh	*unwink_next;	/* next on unwink wist */

	unsigned		unwink_cycwe;

	u8			needs_wescan;	/* Dequeue duwing giveback */
	u8			qh_state;
#define	QH_STATE_WINKED		1		/* HC sees this */
#define	QH_STATE_UNWINK		2		/* HC may stiww see this */
#define	QH_STATE_IDWE		3		/* HC doesn't see this */
#define	QH_STATE_UNWINK_WAIT	4		/* WINKED and on unwink q */
#define	QH_STATE_COMPWETING	5		/* don't touch token.HAWT */

	u8			xactewws;	/* XactEww wetwy countew */
#define	QH_XACTEWW_MAX		32		/* XactEww wetwy wimit */

	/* pewiodic scheduwe info */
	u8			usecs;		/* intw bandwidth */
	u8			gap_uf;		/* ufwames spwit/cspwit gap */
	u8			c_usecs;	/* ... spwit compwetion bw */
	u16			tt_usecs;	/* tt downstweam bandwidth */
	unsigned showt		pewiod;		/* powwing intewvaw */
	unsigned showt		stawt;		/* whewe powwing stawts */
#define NO_FWAME ((unsigned showt)~0)			/* pick new stawt */

	stwuct usb_device	*dev;		/* access to TT */
	unsigned		is_out:1;	/* buwk ow intw OUT */
	unsigned		cweawing_tt:1;	/* Cweaw-TT-Buf in pwogwess */
};

/*-------------------------------------------------------------------------*/

/* descwiption of one iso twansaction (up to 3 KB data if highspeed) */
stwuct fotg210_iso_packet {
	/* These wiww be copied to iTD when scheduwing */
	u64			bufp;		/* itd->hw_bufp{,_hi}[pg] |= */
	__hc32			twansaction;	/* itd->hw_twansaction[i] |= */
	u8			cwoss;		/* buf cwosses pages */
	/* fow fuww speed OUT spwits */
	u32			buf1;
};

/* tempowawy scheduwe data fow packets fwom iso uwbs (both speeds)
 * each packet is one wogicaw usb twansaction to the device (not TT),
 * beginning at stweam->next_ufwame
 */
stwuct fotg210_iso_sched {
	stwuct wist_head	td_wist;
	unsigned		span;
	stwuct fotg210_iso_packet	packet[];
};

/*
 * fotg210_iso_stweam - gwoups aww (s)itds fow this endpoint.
 * acts wike a qh wouwd, if EHCI had them fow ISO.
 */
stwuct fotg210_iso_stweam {
	/* fiwst fiewd matches fotg210_hq, but is NUWW */
	stwuct fotg210_qh_hw	*hw;

	u8			bEndpointAddwess;
	u8			highspeed;
	stwuct wist_head	td_wist;	/* queued itds */
	stwuct wist_head	fwee_wist;	/* wist of unused itds */
	stwuct usb_device	*udev;
	stwuct usb_host_endpoint *ep;

	/* output of (we)scheduwing */
	int			next_ufwame;
	__hc32			spwits;

	/* the west is dewived fwom the endpoint descwiptow,
	 * twusting uwb->intewvaw == f(epdesc->bIntewvaw) and
	 * incwuding the extwa info fow hw_bufp[0..2]
	 */
	u8			usecs, c_usecs;
	u16			intewvaw;
	u16			tt_usecs;
	u16			maxp;
	u16			waw_mask;
	unsigned		bandwidth;

	/* This is used to initiawize iTD's hw_bufp fiewds */
	__hc32			buf0;
	__hc32			buf1;
	__hc32			buf2;

	/* this is used to initiawize sITD's tt info */
	__hc32			addwess;
};

/*-------------------------------------------------------------------------*/

/*
 * EHCI Specification 0.95 Section 3.3
 * Fig 3-4 "Isochwonous Twansaction Descwiptow (iTD)"
 *
 * Scheduwe wecowds fow high speed iso xfews
 */
stwuct fotg210_itd {
	/* fiwst pawt defined by EHCI spec */
	__hc32			hw_next;	/* see EHCI 3.3.1 */
	__hc32			hw_twansaction[8]; /* see EHCI 3.3.2 */
#define FOTG210_ISOC_ACTIVE	(1<<31)	/* activate twansfew this swot */
#define FOTG210_ISOC_BUF_EWW	(1<<30)	/* Data buffew ewwow */
#define FOTG210_ISOC_BABBWE	(1<<29)	/* babbwe detected */
#define FOTG210_ISOC_XACTEWW	(1<<28)	/* XactEww - twansaction ewwow */
#define	FOTG210_ITD_WENGTH(tok)	(((tok)>>16) & 0x0fff)
#define	FOTG210_ITD_IOC		(1 << 15)	/* intewwupt on compwete */

#define ITD_ACTIVE(fotg210)	cpu_to_hc32(fotg210, FOTG210_ISOC_ACTIVE)

	__hc32			hw_bufp[7];	/* see EHCI 3.3.3 */
	__hc32			hw_bufp_hi[7];	/* Appendix B */

	/* the west is HCD-pwivate */
	dma_addw_t		itd_dma;	/* fow this itd */
	union fotg210_shadow	itd_next;	/* ptw to pewiodic q entwy */

	stwuct uwb		*uwb;
	stwuct fotg210_iso_stweam	*stweam;	/* endpoint's queue */
	stwuct wist_head	itd_wist;	/* wist of stweam's itds */

	/* any/aww hw_twansactions hewe may be used by that uwb */
	unsigned		fwame;		/* whewe scheduwed */
	unsigned		pg;
	unsigned		index[8];	/* in uwb->iso_fwame_desc */
} __awigned(32);

/*-------------------------------------------------------------------------*/

/*
 * EHCI Specification 0.96 Section 3.7
 * Pewiodic Fwame Span Twavewsaw Node (FSTN)
 *
 * Manages spwit intewwupt twansactions (using TT) that span fwame boundawies
 * into ufwames 0/1; see 4.12.2.2.  In those ufwames, a "save pwace" FSTN
 * makes the HC jump (back) to a QH to scan fow fs/ws QH compwetions untiw
 * it hits a "westowe" FSTN; then it wetuwns to finish othew ufwame 0/1 wowk.
 */
stwuct fotg210_fstn {
	__hc32			hw_next;	/* any pewiodic q entwy */
	__hc32			hw_pwev;	/* qh ow FOTG210_WIST_END */

	/* the west is HCD-pwivate */
	dma_addw_t		fstn_dma;
	union fotg210_shadow	fstn_next;	/* ptw to pewiodic q entwy */
} __awigned(32);

/*-------------------------------------------------------------------------*/

/* Pwepawe the POWTSC wakeup fwags duwing contwowwew suspend/wesume */

#define fotg210_pwepawe_powts_fow_contwowwew_suspend(fotg210, do_wakeup) \
		fotg210_adjust_powt_wakeup_fwags(fotg210, twue, do_wakeup)

#define fotg210_pwepawe_powts_fow_contwowwew_wesume(fotg210)		\
		fotg210_adjust_powt_wakeup_fwags(fotg210, fawse, fawse)

/*-------------------------------------------------------------------------*/

/*
 * Some EHCI contwowwews have a Twansaction Twanswatow buiwt into the
 * woot hub. This is a non-standawd featuwe.  Each contwowwew wiww need
 * to add code to the fowwowing inwine functions, and caww them as
 * needed (mostwy in woot hub code).
 */

static inwine unsigned int
fotg210_get_speed(stwuct fotg210_hcd *fotg210, unsigned int powtsc)
{
	wetuwn (weadw(&fotg210->wegs->otgcsw)
		& OTGCSW_HOST_SPD_TYP) >> 22;
}

/* Wetuwns the speed of a device attached to a powt on the woot hub. */
static inwine unsigned int
fotg210_powt_speed(stwuct fotg210_hcd *fotg210, unsigned int powtsc)
{
	switch (fotg210_get_speed(fotg210, powtsc)) {
	case 0:
		wetuwn 0;
	case 1:
		wetuwn USB_POWT_STAT_WOW_SPEED;
	case 2:
	defauwt:
		wetuwn USB_POWT_STAT_HIGH_SPEED;
	}
}

/*-------------------------------------------------------------------------*/

#define	fotg210_has_fsw_powtno_bug(e)		(0)

/*
 * Whiwe most USB host contwowwews impwement theiw wegistews in
 * wittwe-endian fowmat, a minowity (cewweb companion chip) impwement
 * them in big endian fowmat.
 *
 * This attempts to suppowt eithew fowmat at compiwe time without a
 * wuntime penawty, ow both fowmats with the additionaw ovewhead
 * of checking a fwag bit.
 *
 */

#define fotg210_big_endian_mmio(e)	0
#define fotg210_big_endian_capbase(e)	0

static inwine unsigned int fotg210_weadw(const stwuct fotg210_hcd *fotg210,
		__u32 __iomem *wegs)
{
	wetuwn weadw(wegs);
}

static inwine void fotg210_wwitew(const stwuct fotg210_hcd *fotg210,
		const unsigned int vaw, __u32 __iomem *wegs)
{
	wwitew(vaw, wegs);
}

/* cpu to fotg210 */
static inwine __hc32 cpu_to_hc32(const stwuct fotg210_hcd *fotg210, const u32 x)
{
	wetuwn cpu_to_we32(x);
}

/* fotg210 to cpu */
static inwine u32 hc32_to_cpu(const stwuct fotg210_hcd *fotg210, const __hc32 x)
{
	wetuwn we32_to_cpu(x);
}

static inwine u32 hc32_to_cpup(const stwuct fotg210_hcd *fotg210,
			       const __hc32 *x)
{
	wetuwn we32_to_cpup(x);
}

/*-------------------------------------------------------------------------*/

static inwine unsigned fotg210_wead_fwame_index(stwuct fotg210_hcd *fotg210)
{
	wetuwn fotg210_weadw(fotg210, &fotg210->wegs->fwame_index);
}

/*-------------------------------------------------------------------------*/

#endif /* __WINUX_FOTG210_H */
