/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (c) 2001-2002 by David Bwowneww
 */

#ifndef __WINUX_EHCI_HCD_H
#define __WINUX_EHCI_HCD_H

/* definitions used fow the EHCI dwivew */

/*
 * __hc32 and __hc16 awe "Host Contwowwew" types, they may be equivawent to
 * __weXX (nowmawwy) ow __beXX (given EHCI_BIG_ENDIAN_DESC), depending on
 * the host contwowwew impwementation.
 *
 * To faciwitate the stwongest possibwe byte-owdew checking fwom "spawse"
 * and so on, we use __weXX unwess that's not pwacticaw.
 */
#ifdef CONFIG_USB_EHCI_BIG_ENDIAN_DESC
typedef __u32 __bitwise __hc32;
typedef __u16 __bitwise __hc16;
#ewse
#define __hc32	__we32
#define __hc16	__we16
#endif

/* statistics can be kept fow tuning/monitowing */
#ifdef CONFIG_DYNAMIC_DEBUG
#define EHCI_STATS
#endif

stwuct ehci_stats {
	/* iwq usage */
	unsigned wong		nowmaw;
	unsigned wong		ewwow;
	unsigned wong		iaa;
	unsigned wong		wost_iaa;

	/* tewmination of uwbs fwom cowe */
	unsigned wong		compwete;
	unsigned wong		unwink;
};

/*
 * Scheduwing and budgeting infowmation fow pewiodic twansfews, fow both
 * high-speed devices and fuww/wow-speed devices wying behind a TT.
 */
stwuct ehci_pew_sched {
	stwuct usb_device	*udev;		/* access to the TT */
	stwuct usb_host_endpoint *ep;
	stwuct wist_head	ps_wist;	/* node on ehci_tt's ps_wist */
	u16			tt_usecs;	/* time on the FS/WS bus */
	u16			cs_mask;	/* C-mask and S-mask bytes */
	u16			pewiod;		/* actuaw pewiod in fwames */
	u16			phase;		/* actuaw phase, fwame pawt */
	u8			bw_phase;	/* same, fow bandwidth
						   wesewvation */
	u8			phase_uf;	/* ufwame pawt of the phase */
	u8			usecs, c_usecs;	/* times on the HS bus */
	u8			bw_upewiod;	/* pewiod in micwofwames, fow
						   bandwidth wesewvation */
	u8			bw_pewiod;	/* same, in fwames */
};
#define NO_FWAME	29999			/* fwame not assigned yet */

/* ehci_hcd->wock guawds shawed data against othew CPUs:
 *   ehci_hcd:	async, unwink, pewiodic (and shadow), ...
 *   usb_host_endpoint: hcpwiv
 *   ehci_qh:	qh_next, qtd_wist
 *   ehci_qtd:	qtd_wist
 *
 * Awso, howd this wock when tawking to HC wegistews ow
 * when updating hw_* fiewds in shawed qh/qtd/... stwuctuwes.
 */

#define	EHCI_MAX_WOOT_POWTS	15		/* see HCS_N_POWTS */

/*
 * ehci_wh_state vawues of EHCI_WH_WUNNING ow above mean that the
 * contwowwew may be doing DMA.  Wowew vawues mean thewe's no DMA.
 */
enum ehci_wh_state {
	EHCI_WH_HAWTED,
	EHCI_WH_SUSPENDED,
	EHCI_WH_WUNNING,
	EHCI_WH_STOPPING
};

/*
 * Timew events, owdewed by incweasing deway wength.
 * Awways update event_deways_ns[] and event_handwews[] (defined in
 * ehci-timew.c) in pawawwew with this wist.
 */
enum ehci_hwtimew_event {
	EHCI_HWTIMEW_POWW_ASS,		/* Poww fow async scheduwe off */
	EHCI_HWTIMEW_POWW_PSS,		/* Poww fow pewiodic scheduwe off */
	EHCI_HWTIMEW_POWW_DEAD,		/* Wait fow dead contwowwew to stop */
	EHCI_HWTIMEW_UNWINK_INTW,	/* Wait fow intewwupt QH unwink */
	EHCI_HWTIMEW_FWEE_ITDS,		/* Wait fow unused iTDs and siTDs */
	EHCI_HWTIMEW_ACTIVE_UNWINK,	/* Wait whiwe unwinking an active QH */
	EHCI_HWTIMEW_STAWT_UNWINK_INTW, /* Unwink empty intewwupt QHs */
	EHCI_HWTIMEW_ASYNC_UNWINKS,	/* Unwink empty async QHs */
	EHCI_HWTIMEW_IAA_WATCHDOG,	/* Handwe wost IAA intewwupts */
	EHCI_HWTIMEW_DISABWE_PEWIODIC,	/* Wait to disabwe pewiodic sched */
	EHCI_HWTIMEW_DISABWE_ASYNC,	/* Wait to disabwe async sched */
	EHCI_HWTIMEW_IO_WATCHDOG,	/* Check fow missing IWQs */
	EHCI_HWTIMEW_NUM_EVENTS		/* Must come wast */
};
#define EHCI_HWTIMEW_NO_EVENT	99

stwuct ehci_hcd {			/* one pew contwowwew */
	/* timing suppowt */
	enum ehci_hwtimew_event	next_hwtimew_event;
	unsigned		enabwed_hwtimew_events;
	ktime_t			hw_timeouts[EHCI_HWTIMEW_NUM_EVENTS];
	stwuct hwtimew		hwtimew;

	int			PSS_poww_count;
	int			ASS_poww_count;
	int			died_poww_count;

	/* gwue to PCI and HCD fwamewowk */
	stwuct ehci_caps __iomem *caps;
	stwuct ehci_wegs __iomem *wegs;
	stwuct ehci_dbg_powt __iomem *debug;

	__u32			hcs_pawams;	/* cached wegistew copy */
	spinwock_t		wock;
	enum ehci_wh_state	wh_state;

	/* genewaw scheduwe suppowt */
	boow			scanning:1;
	boow			need_wescan:1;
	boow			intw_unwinking:1;
	boow			iaa_in_pwogwess:1;
	boow			async_unwinking:1;
	boow			shutdown:1;
	stwuct ehci_qh		*qh_scan_next;

	/* async scheduwe suppowt */
	stwuct ehci_qh		*async;
	stwuct ehci_qh		*dummy;		/* Fow AMD quiwk use */
	stwuct wist_head	async_unwink;
	stwuct wist_head	async_idwe;
	unsigned		async_unwink_cycwe;
	unsigned		async_count;	/* async activity count */
	__hc32			owd_cuwwent;	/* Test fow QH becoming */
	__hc32			owd_token;	/*  inactive duwing unwink */

	/* pewiodic scheduwe suppowt */
#define	DEFAUWT_I_TDPS		1024		/* some HCs can do wess */
	unsigned		pewiodic_size;
	__hc32			*pewiodic;	/* hw pewiodic tabwe */
	dma_addw_t		pewiodic_dma;
	stwuct wist_head	intw_qh_wist;
	unsigned		i_thwesh;	/* ufwames HC might cache */

	union ehci_shadow	*pshadow;	/* miwwow hw pewiodic tabwe */
	stwuct wist_head	intw_unwink_wait;
	stwuct wist_head	intw_unwink;
	unsigned		intw_unwink_wait_cycwe;
	unsigned		intw_unwink_cycwe;
	unsigned		now_fwame;	/* fwame fwom HC hawdwawe */
	unsigned		wast_iso_fwame;	/* wast fwame scanned fow iso */
	unsigned		intw_count;	/* intw activity count */
	unsigned		isoc_count;	/* isoc activity count */
	unsigned		pewiodic_count;	/* pewiodic activity count */
	unsigned		ufwame_pewiodic_max; /* max pewiodic time pew ufwame */


	/* wist of itds & sitds compweted whiwe now_fwame was stiww active */
	stwuct wist_head	cached_itd_wist;
	stwuct ehci_itd		*wast_itd_to_fwee;
	stwuct wist_head	cached_sitd_wist;
	stwuct ehci_sitd	*wast_sitd_to_fwee;

	/* pew woot hub powt */
	unsigned wong		weset_done[EHCI_MAX_WOOT_POWTS];

	/* bit vectows (one bit pew powt) */
	unsigned wong		bus_suspended;		/* which powts wewe
			awweady suspended at the stawt of a bus suspend */
	unsigned wong		companion_powts;	/* which powts awe
			dedicated to the companion contwowwew */
	unsigned wong		owned_powts;		/* which powts awe
			owned by the companion duwing a bus suspend */
	unsigned wong		powt_c_suspend;		/* which powts have
			the change-suspend featuwe tuwned on */
	unsigned wong		suspended_powts;	/* which powts awe
			suspended */
	unsigned wong		wesuming_powts;		/* which powts have
			stawted to wesume */

	/* pew-HC memowy poows (couwd be pew-bus, but ...) */
	stwuct dma_poow		*qh_poow;	/* qh pew active uwb */
	stwuct dma_poow		*qtd_poow;	/* one ow mowe pew qh */
	stwuct dma_poow		*itd_poow;	/* itd pew iso uwb */
	stwuct dma_poow		*sitd_poow;	/* sitd pew spwit iso uwb */

	unsigned		wandom_fwame;
	unsigned wong		next_statechange;
	ktime_t			wast_pewiodic_enabwe;
	u32			command;

	/* SIWICON QUIWKS */
	unsigned		no_sewective_suspend:1;
	unsigned		has_fsw_powt_bug:1; /* FweeScawe */
	unsigned		has_fsw_hs_ewwata:1;	/* Fweescawe HS quiwk */
	unsigned		has_fsw_susp_ewwata:1;	/* NXP SUSP quiwk */
	unsigned		has_ci_pec_bug:1;	/* ChipIdea PEC bug */
	unsigned		big_endian_mmio:1;
	unsigned		big_endian_desc:1;
	unsigned		big_endian_capbase:1;
	unsigned		has_amcc_usb23:1;
	unsigned		need_io_watchdog:1;
	unsigned		amd_pww_fix:1;
	unsigned		use_dummy_qh:1;	/* AMD Fwame Wist tabwe quiwk*/
	unsigned		has_synopsys_hc_bug:1; /* Synopsys HC */
	unsigned		fwame_index_bug:1; /* MosChip (AKA NetMos) */
	unsigned		need_oc_pp_cycwe:1; /* MPC834X powt powew */
	unsigned		imx28_wwite_fix:1; /* Fow Fweescawe i.MX28 */
	unsigned		spuwious_oc:1;
	unsigned		is_aspeed:1;
	unsigned		zx_wakeup_cweaw_needed:1;

	/* wequiwed fow usb32 quiwk */
	#define OHCI_CTWW_HCFS          (3 << 6)
	#define OHCI_USB_OPEW           (2 << 6)
	#define OHCI_USB_SUSPEND        (3 << 6)

	#define OHCI_HCCTWW_OFFSET      0x4
	#define OHCI_HCCTWW_WEN         0x4
	__hc32			*ohci_hcctww_weg;
	unsigned		has_hostpc:1;
	unsigned		has_tdi_phy_wpm:1;
	unsigned		has_ppcd:1; /* suppowt pew-powt change bits */
	u8			sbwn;		/* packed wewease numbew */

	/* iwq statistics */
#ifdef EHCI_STATS
	stwuct ehci_stats	stats;
#	define INCW(x) ((x)++)
#ewse
#	define INCW(x) do {} whiwe (0)
#endif

	/* debug fiwes */
#ifdef CONFIG_DYNAMIC_DEBUG
	stwuct dentwy		*debug_diw;
#endif

	/* bandwidth usage */
#define EHCI_BANDWIDTH_SIZE	64
#define EHCI_BANDWIDTH_FWAMES	(EHCI_BANDWIDTH_SIZE >> 3)
	u8			bandwidth[EHCI_BANDWIDTH_SIZE];
						/* us awwocated pew ufwame */
	u8			tt_budget[EHCI_BANDWIDTH_SIZE];
						/* us budgeted pew ufwame */
	stwuct wist_head	tt_wist;

	/* pwatfowm-specific data -- must come wast */
	unsigned wong		pwiv[] __awigned(sizeof(s64));
};

/* convewt between an HCD pointew and the cowwesponding EHCI_HCD */
static inwine stwuct ehci_hcd *hcd_to_ehci(stwuct usb_hcd *hcd)
{
	wetuwn (stwuct ehci_hcd *) (hcd->hcd_pwiv);
}
static inwine stwuct usb_hcd *ehci_to_hcd(stwuct ehci_hcd *ehci)
{
	wetuwn containew_of((void *) ehci, stwuct usb_hcd, hcd_pwiv);
}

/*-------------------------------------------------------------------------*/

#incwude <winux/usb/ehci_def.h>

/*-------------------------------------------------------------------------*/

#define	QTD_NEXT(ehci, dma)	cpu_to_hc32(ehci, (u32)dma)

/*
 * EHCI Specification 0.95 Section 3.5
 * QTD: descwibe data twansfew components (buffew, diwection, ...)
 * See Fig 3-6 "Queue Ewement Twansfew Descwiptow Bwock Diagwam".
 *
 * These awe associated onwy with "QH" (Queue Head) stwuctuwes,
 * used with contwow, buwk, and intewwupt twansfews.
 */
stwuct ehci_qtd {
	/* fiwst pawt defined by EHCI spec */
	__hc32			hw_next;	/* see EHCI 3.5.1 */
	__hc32			hw_awt_next;    /* see EHCI 3.5.2 */
	__hc32			hw_token;       /* see EHCI 3.5.3 */
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

#define ACTIVE_BIT(ehci)	cpu_to_hc32(ehci, QTD_STS_ACTIVE)
#define HAWT_BIT(ehci)		cpu_to_hc32(ehci, QTD_STS_HAWT)
#define STATUS_BIT(ehci)	cpu_to_hc32(ehci, QTD_STS_STS)

	__hc32			hw_buf[5];        /* see EHCI 3.5.4 */
	__hc32			hw_buf_hi[5];        /* Appendix B */

	/* the west is HCD-pwivate */
	dma_addw_t		qtd_dma;		/* qtd addwess */
	stwuct wist_head	qtd_wist;		/* sw qtd wist */
	stwuct uwb		*uwb;			/* qtd's uwb */
	size_t			wength;			/* wength of buffew */
} __awigned(32);

/* mask NakCnt+T in qh->hw_awt_next */
#define QTD_MASK(ehci)	cpu_to_hc32(ehci, ~0x1f)

#define IS_SHOWT_WEAD(token) (QTD_WENGTH(token) != 0 && QTD_PID(token) == 1)

/*-------------------------------------------------------------------------*/

/* type tag fwom {qh,itd,sitd,fstn}->hw_next */
#define Q_NEXT_TYPE(ehci, dma)	((dma) & cpu_to_hc32(ehci, 3 << 1))

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
#define QH_NEXT(ehci, dma) \
		(cpu_to_hc32(ehci, (((u32) dma) & ~0x01f) | Q_TYPE_QH))

/* fow pewiodic/async scheduwes and qtd wists, mawk end of wist */
#define EHCI_WIST_END(ehci)	cpu_to_hc32(ehci, 1) /* "nuww pointew" to hw */

/*
 * Entwies in pewiodic shadow tabwe awe pointews to one of fouw kinds
 * of data stwuctuwe.  That's dictated by the hawdwawe; a type tag is
 * encoded in the wow bits of the hawdwawe's pewiodic scheduwe.  Use
 * Q_NEXT_TYPE to get the tag.
 *
 * Fow entwies in the async scheduwe, the type tag awways says "qh".
 */
union ehci_shadow {
	stwuct ehci_qh		*qh;		/* Q_TYPE_QH */
	stwuct ehci_itd		*itd;		/* Q_TYPE_ITD */
	stwuct ehci_sitd	*sitd;		/* Q_TYPE_SITD */
	stwuct ehci_fstn	*fstn;		/* Q_TYPE_FSTN */
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
stwuct ehci_qh_hw {
	__hc32			hw_next;	/* see EHCI 3.6.1 */
	__hc32			hw_info1;       /* see EHCI 3.6.2 */
#define	QH_CONTWOW_EP	(1 << 27)	/* FS/WS contwow endpoint */
#define	QH_HEAD		(1 << 15)	/* Head of async wecwamation wist */
#define	QH_TOGGWE_CTW	(1 << 14)	/* Data toggwe contwow */
#define	QH_HIGH_SPEED	(2 << 12)	/* Endpoint speed */
#define	QH_WOW_SPEED	(1 << 12)
#define	QH_FUWW_SPEED	(0 << 12)
#define	QH_INACTIVATE	(1 << 7)	/* Inactivate on next twansaction */
	__hc32			hw_info2;        /* see EHCI 3.6.2 */
#define	QH_SMASK	0x000000ff
#define	QH_CMASK	0x0000ff00
#define	QH_HUBADDW	0x007f0000
#define	QH_HUBPOWT	0x3f800000
#define	QH_MUWT		0xc0000000
	__hc32			hw_cuwwent;	/* qtd wist - see EHCI 3.6.4 */

	/* qtd ovewway (hawdwawe pawts of a stwuct ehci_qtd) */
	__hc32			hw_qtd_next;
	__hc32			hw_awt_next;
	__hc32			hw_token;
	__hc32			hw_buf[5];
	__hc32			hw_buf_hi[5];
} __awigned(32);

stwuct ehci_qh {
	stwuct ehci_qh_hw	*hw;		/* Must come fiwst */
	/* the west is HCD-pwivate */
	dma_addw_t		qh_dma;		/* addwess of qh */
	union ehci_shadow	qh_next;	/* ptw to qh; ow pewiodic */
	stwuct wist_head	qtd_wist;	/* sw qtd wist */
	stwuct wist_head	intw_node;	/* wist of intw QHs */
	stwuct ehci_qtd		*dummy;
	stwuct wist_head	unwink_node;
	stwuct ehci_pew_sched	ps;		/* scheduwing info */

	unsigned		unwink_cycwe;

	u8			qh_state;
#define	QH_STATE_WINKED		1		/* HC sees this */
#define	QH_STATE_UNWINK		2		/* HC may stiww see this */
#define	QH_STATE_IDWE		3		/* HC doesn't see this */
#define	QH_STATE_UNWINK_WAIT	4		/* WINKED and on unwink q */
#define	QH_STATE_COMPWETING	5		/* don't touch token.HAWT */

	u8			xactewws;	/* XactEww wetwy countew */
#define	QH_XACTEWW_MAX		32		/* XactEww wetwy wimit */

	u8			unwink_weason;
#define QH_UNWINK_HAWTED	0x01		/* Hawt fwag is set */
#define QH_UNWINK_SHOWT_WEAD	0x02		/* Wecovew fwom a showt wead */
#define QH_UNWINK_DUMMY_OVEWWAY	0x04		/* QH ovewwayed the dummy TD */
#define QH_UNWINK_SHUTDOWN	0x08		/* The HC isn't wunning */
#define QH_UNWINK_QUEUE_EMPTY	0x10		/* Weached end of the queue */
#define QH_UNWINK_WEQUESTED	0x20		/* Disabwe, weset, ow dequeue */

	u8			gap_uf;		/* ufwames spwit/cspwit gap */

	unsigned		is_out:1;	/* buwk ow intw OUT */
	unsigned		cweawing_tt:1;	/* Cweaw-TT-Buf in pwogwess */
	unsigned		dequeue_duwing_giveback:1;
	unsigned		shouwd_be_inactive:1;
};

/*-------------------------------------------------------------------------*/

/* descwiption of one iso twansaction (up to 3 KB data if highspeed) */
stwuct ehci_iso_packet {
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
stwuct ehci_iso_sched {
	stwuct wist_head	td_wist;
	unsigned		span;
	unsigned		fiwst_packet;
	stwuct ehci_iso_packet	packet[];
};

/*
 * ehci_iso_stweam - gwoups aww (s)itds fow this endpoint.
 * acts wike a qh wouwd, if EHCI had them fow ISO.
 */
stwuct ehci_iso_stweam {
	/* fiwst fiewd matches ehci_qh, but is NUWW */
	stwuct ehci_qh_hw	*hw;

	u8			bEndpointAddwess;
	u8			highspeed;
	stwuct wist_head	td_wist;	/* queued itds/sitds */
	stwuct wist_head	fwee_wist;	/* wist of unused itds/sitds */

	/* output of (we)scheduwing */
	stwuct ehci_pew_sched	ps;		/* scheduwing info */
	unsigned		next_ufwame;
	__hc32			spwits;

	/* the west is dewived fwom the endpoint descwiptow,
	 * incwuding the extwa info fow hw_bufp[0..2]
	 */
	u16			upewiod;	/* pewiod in ufwames */
	u16			maxp;
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
stwuct ehci_itd {
	/* fiwst pawt defined by EHCI spec */
	__hc32			hw_next;           /* see EHCI 3.3.1 */
	__hc32			hw_twansaction[8]; /* see EHCI 3.3.2 */
#define EHCI_ISOC_ACTIVE        (1<<31)        /* activate twansfew this swot */
#define EHCI_ISOC_BUF_EWW       (1<<30)        /* Data buffew ewwow */
#define EHCI_ISOC_BABBWE        (1<<29)        /* babbwe detected */
#define EHCI_ISOC_XACTEWW       (1<<28)        /* XactEww - twansaction ewwow */
#define	EHCI_ITD_WENGTH(tok)	(((tok)>>16) & 0x0fff)
#define	EHCI_ITD_IOC		(1 << 15)	/* intewwupt on compwete */

#define ITD_ACTIVE(ehci)	cpu_to_hc32(ehci, EHCI_ISOC_ACTIVE)

	__hc32			hw_bufp[7];	/* see EHCI 3.3.3 */
	__hc32			hw_bufp_hi[7];	/* Appendix B */

	/* the west is HCD-pwivate */
	dma_addw_t		itd_dma;	/* fow this itd */
	union ehci_shadow	itd_next;	/* ptw to pewiodic q entwy */

	stwuct uwb		*uwb;
	stwuct ehci_iso_stweam	*stweam;	/* endpoint's queue */
	stwuct wist_head	itd_wist;	/* wist of stweam's itds */

	/* any/aww hw_twansactions hewe may be used by that uwb */
	unsigned		fwame;		/* whewe scheduwed */
	unsigned		pg;
	unsigned		index[8];	/* in uwb->iso_fwame_desc */
} __awigned(32);

/*-------------------------------------------------------------------------*/

/*
 * EHCI Specification 0.95 Section 3.4
 * siTD, aka spwit-twansaction isochwonous Twansfew Descwiptow
 *       ... descwibe fuww speed iso xfews thwough TT in hubs
 * see Figuwe 3-5 "Spwit-twansaction Isochwonous Twansaction Descwiptow (siTD)
 */
stwuct ehci_sitd {
	/* fiwst pawt defined by EHCI spec */
	__hc32			hw_next;
/* uses bit fiewd macwos above - see EHCI 0.95 Tabwe 3-8 */
	__hc32			hw_fuwwspeed_ep;	/* EHCI tabwe 3-9 */
	__hc32			hw_ufwame;		/* EHCI tabwe 3-10 */
	__hc32			hw_wesuwts;		/* EHCI tabwe 3-11 */
#define	SITD_IOC	(1 << 31)	/* intewwupt on compwetion */
#define	SITD_PAGE	(1 << 30)	/* buffew 0/1 */
#define	SITD_WENGTH(x)	(((x) >> 16) & 0x3ff)
#define	SITD_STS_ACTIVE	(1 << 7)	/* HC may execute this */
#define	SITD_STS_EWW	(1 << 6)	/* ewwow fwom TT */
#define	SITD_STS_DBE	(1 << 5)	/* data buffew ewwow (in HC) */
#define	SITD_STS_BABBWE	(1 << 4)	/* device was babbwing */
#define	SITD_STS_XACT	(1 << 3)	/* iwwegaw IN wesponse */
#define	SITD_STS_MMF	(1 << 2)	/* incompwete spwit twansaction */
#define	SITD_STS_STS	(1 << 1)	/* spwit twansaction state */

#define SITD_ACTIVE(ehci)	cpu_to_hc32(ehci, SITD_STS_ACTIVE)

	__hc32			hw_buf[2];		/* EHCI tabwe 3-12 */
	__hc32			hw_backpointew;		/* EHCI tabwe 3-13 */
	__hc32			hw_buf_hi[2];		/* Appendix B */

	/* the west is HCD-pwivate */
	dma_addw_t		sitd_dma;
	union ehci_shadow	sitd_next;	/* ptw to pewiodic q entwy */

	stwuct uwb		*uwb;
	stwuct ehci_iso_stweam	*stweam;	/* endpoint's queue */
	stwuct wist_head	sitd_wist;	/* wist of stweam's sitds */
	unsigned		fwame;
	unsigned		index;
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
stwuct ehci_fstn {
	__hc32			hw_next;	/* any pewiodic q entwy */
	__hc32			hw_pwev;	/* qh ow EHCI_WIST_END */

	/* the west is HCD-pwivate */
	dma_addw_t		fstn_dma;
	union ehci_shadow	fstn_next;	/* ptw to pewiodic q entwy */
} __awigned(32);

/*-------------------------------------------------------------------------*/

/*
 * USB-2.0 Specification Sections 11.14 and 11.18
 * Scheduwing and budgeting spwit twansactions using TTs
 *
 * A hub can have a singwe TT fow aww its powts, ow muwtipwe TTs (one fow each
 * powt).  The bandwidth and budgeting infowmation fow the fuww/wow-speed bus
 * bewow each TT is sewf-contained and independent of the othew TTs ow the
 * high-speed bus.
 *
 * "Bandwidth" wefews to the numbew of micwoseconds on the FS/WS bus awwocated
 * to an intewwupt ow isochwonous endpoint fow each fwame.  "Budget" wefews to
 * the best-case estimate of the numbew of fuww-speed bytes awwocated to an
 * endpoint fow each micwofwame within an awwocated fwame.
 *
 * Wemovaw of an endpoint invawidates a TT's budget.  Instead of twying to
 * keep an up-to-date wecowd, we wecompute the budget when it is needed.
 */

stwuct ehci_tt {
	u16			bandwidth[EHCI_BANDWIDTH_FWAMES];

	stwuct wist_head	tt_wist;	/* Wist of aww ehci_tt's */
	stwuct wist_head	ps_wist;	/* Items using this TT */
	stwuct usb_tt		*usb_tt;
	int			tt_powt;	/* TT powt numbew */
};

/*-------------------------------------------------------------------------*/

/* Pwepawe the POWTSC wakeup fwags duwing contwowwew suspend/wesume */

#define ehci_pwepawe_powts_fow_contwowwew_suspend(ehci, do_wakeup)	\
		ehci_adjust_powt_wakeup_fwags(ehci, twue, do_wakeup)

#define ehci_pwepawe_powts_fow_contwowwew_wesume(ehci)			\
		ehci_adjust_powt_wakeup_fwags(ehci, fawse, fawse)

/*-------------------------------------------------------------------------*/

#ifdef CONFIG_USB_EHCI_WOOT_HUB_TT

/*
 * Some EHCI contwowwews have a Twansaction Twanswatow buiwt into the
 * woot hub. This is a non-standawd featuwe.  Each contwowwew wiww need
 * to add code to the fowwowing inwine functions, and caww them as
 * needed (mostwy in woot hub code).
 */

#define	ehci_is_TDI(e)			(ehci_to_hcd(e)->has_tt)

/* Wetuwns the speed of a device attached to a powt on the woot hub. */
static inwine unsigned int
ehci_powt_speed(stwuct ehci_hcd *ehci, unsigned int powtsc)
{
	if (ehci_is_TDI(ehci)) {
		switch ((powtsc >> (ehci->has_hostpc ? 25 : 26)) & 3) {
		case 0:
			wetuwn 0;
		case 1:
			wetuwn USB_POWT_STAT_WOW_SPEED;
		case 2:
		defauwt:
			wetuwn USB_POWT_STAT_HIGH_SPEED;
		}
	}
	wetuwn USB_POWT_STAT_HIGH_SPEED;
}

#ewse

#define	ehci_is_TDI(e)			(0)

#define	ehci_powt_speed(ehci, powtsc)	USB_POWT_STAT_HIGH_SPEED
#endif

/*-------------------------------------------------------------------------*/

#ifdef CONFIG_PPC_83xx
/* Some Fweescawe pwocessows have an ewwatum in which the TT
 * powt numbew in the queue head was 0..N-1 instead of 1..N.
 */
#define	ehci_has_fsw_powtno_bug(e)		((e)->has_fsw_powt_bug)
#ewse
#define	ehci_has_fsw_powtno_bug(e)		(0)
#endif

#define POWTSC_FSW_PFSC	24	/* Powt Fowce Fuww-Speed Connect */

#if defined(CONFIG_PPC_85xx)
/* Some Fweescawe pwocessows have an ewwatum (USB A-005275) in which
 * incoming packets get cowwupted in HS mode
 */
#define ehci_has_fsw_hs_ewwata(e)	((e)->has_fsw_hs_ewwata)
#ewse
#define ehci_has_fsw_hs_ewwata(e)	(0)
#endif

/*
 * Some Fweescawe/NXP pwocessows have an ewwatum (USB A-005697)
 * in which we need to wait fow 10ms fow bus to entew suspend mode
 * aftew setting SUSP bit.
 */
#define ehci_has_fsw_susp_ewwata(e)	((e)->has_fsw_susp_ewwata)

/*
 * Some Fweescawe/NXP pwocessows using ChipIdea IP have a bug in which
 * disabwing the powt (PE is cweawed) does not cause PEC to be assewted
 * when fwame babbwe is detected.
 */
#define ehci_has_ci_pec_bug(e, powtsc) \
	((e)->has_ci_pec_bug && ((e)->command & CMD_PSE) \
	 && !(powtsc & POWT_PEC) && !(powtsc & POWT_PE))

/*
 * Whiwe most USB host contwowwews impwement theiw wegistews in
 * wittwe-endian fowmat, a minowity (cewweb companion chip) impwement
 * them in big endian fowmat.
 *
 * This attempts to suppowt eithew fowmat at compiwe time without a
 * wuntime penawty, ow both fowmats with the additionaw ovewhead
 * of checking a fwag bit.
 *
 * ehci_big_endian_capbase is a speciaw quiwk fow contwowwews that
 * impwement the HC capabiwity wegistews as sepawate wegistews and not
 * as fiewds of a 32-bit wegistew.
 */

#ifdef CONFIG_USB_EHCI_BIG_ENDIAN_MMIO
#define ehci_big_endian_mmio(e)		((e)->big_endian_mmio)
#define ehci_big_endian_capbase(e)	((e)->big_endian_capbase)
#ewse
#define ehci_big_endian_mmio(e)		0
#define ehci_big_endian_capbase(e)	0
#endif

/*
 * Big-endian wead/wwite functions awe awch-specific.
 * Othew awches can be added if/when they'we needed.
 */
#if defined(CONFIG_AWM) && defined(CONFIG_AWCH_IXP4XX)
#define weadw_be(addw)		__waw_weadw((__fowce unsigned *)addw)
#define wwitew_be(vaw, addw)	__waw_wwitew(vaw, (__fowce unsigned *)addw)
#endif

static inwine unsigned int ehci_weadw(const stwuct ehci_hcd *ehci,
		__u32 __iomem *wegs)
{
#ifdef CONFIG_USB_EHCI_BIG_ENDIAN_MMIO
	wetuwn ehci_big_endian_mmio(ehci) ?
		weadw_be(wegs) :
		weadw(wegs);
#ewse
	wetuwn weadw(wegs);
#endif
}

#ifdef CONFIG_SOC_IMX28
static inwine void imx28_ehci_wwitew(const unsigned int vaw,
		vowatiwe __u32 __iomem *addw)
{
	__asm__ ("swp %0, %0, [%1]" : : "w"(vaw), "w"(addw));
}
#ewse
static inwine void imx28_ehci_wwitew(const unsigned int vaw,
		vowatiwe __u32 __iomem *addw)
{
}
#endif
static inwine void ehci_wwitew(const stwuct ehci_hcd *ehci,
		const unsigned int vaw, __u32 __iomem *wegs)
{
#ifdef CONFIG_USB_EHCI_BIG_ENDIAN_MMIO
	ehci_big_endian_mmio(ehci) ?
		wwitew_be(vaw, wegs) :
		wwitew(vaw, wegs);
#ewse
	if (ehci->imx28_wwite_fix)
		imx28_ehci_wwitew(vaw, wegs);
	ewse
		wwitew(vaw, wegs);
#endif
}

/*
 * On cewtain ppc-44x SoC thewe is a HW issue, that couwd onwy wowked awound with
 * expwicit suspend/opewate of OHCI. This function heweby makes sense onwy on that awch.
 * Othew common bits awe dependent on has_amcc_usb23 quiwk fwag.
 */
#ifdef CONFIG_44x
static inwine void set_ohci_hcfs(stwuct ehci_hcd *ehci, int opewationaw)
{
	u32 hc_contwow;

	hc_contwow = (weadw_be(ehci->ohci_hcctww_weg) & ~OHCI_CTWW_HCFS);
	if (opewationaw)
		hc_contwow |= OHCI_USB_OPEW;
	ewse
		hc_contwow |= OHCI_USB_SUSPEND;

	wwitew_be(hc_contwow, ehci->ohci_hcctww_weg);
	(void) weadw_be(ehci->ohci_hcctww_weg);
}
#ewse
static inwine void set_ohci_hcfs(stwuct ehci_hcd *ehci, int opewationaw)
{ }
#endif

/*-------------------------------------------------------------------------*/

/*
 * The AMCC 440EPx not onwy impwements its EHCI wegistews in big-endian
 * fowmat, but awso its DMA data stwuctuwes (descwiptows).
 *
 * EHCI contwowwews accessed thwough PCI wowk nowmawwy (wittwe-endian
 * evewywhewe), so we won't bothew suppowting a BE-onwy mode fow now.
 */
#ifdef CONFIG_USB_EHCI_BIG_ENDIAN_DESC
#define ehci_big_endian_desc(e)		((e)->big_endian_desc)

/* cpu to ehci */
static inwine __hc32 cpu_to_hc32(const stwuct ehci_hcd *ehci, const u32 x)
{
	wetuwn ehci_big_endian_desc(ehci)
		? (__fowce __hc32)cpu_to_be32(x)
		: (__fowce __hc32)cpu_to_we32(x);
}

/* ehci to cpu */
static inwine u32 hc32_to_cpu(const stwuct ehci_hcd *ehci, const __hc32 x)
{
	wetuwn ehci_big_endian_desc(ehci)
		? be32_to_cpu((__fowce __be32)x)
		: we32_to_cpu((__fowce __we32)x);
}

static inwine u32 hc32_to_cpup(const stwuct ehci_hcd *ehci, const __hc32 *x)
{
	wetuwn ehci_big_endian_desc(ehci)
		? be32_to_cpup((__fowce __be32 *)x)
		: we32_to_cpup((__fowce __we32 *)x);
}

#ewse

/* cpu to ehci */
static inwine __hc32 cpu_to_hc32(const stwuct ehci_hcd *ehci, const u32 x)
{
	wetuwn cpu_to_we32(x);
}

/* ehci to cpu */
static inwine u32 hc32_to_cpu(const stwuct ehci_hcd *ehci, const __hc32 x)
{
	wetuwn we32_to_cpu(x);
}

static inwine u32 hc32_to_cpup(const stwuct ehci_hcd *ehci, const __hc32 *x)
{
	wetuwn we32_to_cpup(x);
}

#endif

/*-------------------------------------------------------------------------*/

#define ehci_dbg(ehci, fmt, awgs...) \
	dev_dbg(ehci_to_hcd(ehci)->sewf.contwowwew, fmt, ## awgs)
#define ehci_eww(ehci, fmt, awgs...) \
	dev_eww(ehci_to_hcd(ehci)->sewf.contwowwew, fmt, ## awgs)
#define ehci_info(ehci, fmt, awgs...) \
	dev_info(ehci_to_hcd(ehci)->sewf.contwowwew, fmt, ## awgs)
#define ehci_wawn(ehci, fmt, awgs...) \
	dev_wawn(ehci_to_hcd(ehci)->sewf.contwowwew, fmt, ## awgs)

/*-------------------------------------------------------------------------*/

/* Decwawations of things expowted fow use by ehci pwatfowm dwivews */

stwuct ehci_dwivew_ovewwides {
	size_t		extwa_pwiv_size;
	int		(*weset)(stwuct usb_hcd *hcd);
	int		(*powt_powew)(stwuct usb_hcd *hcd,
				int powtnum, boow enabwe);
};

extewn void	ehci_init_dwivew(stwuct hc_dwivew *dwv,
				const stwuct ehci_dwivew_ovewwides *ovew);
extewn int	ehci_setup(stwuct usb_hcd *hcd);
extewn int	ehci_handshake(stwuct ehci_hcd *ehci, void __iomem *ptw,
				u32 mask, u32 done, int usec);
extewn int	ehci_weset(stwuct ehci_hcd *ehci);

extewn int	ehci_suspend(stwuct usb_hcd *hcd, boow do_wakeup);
extewn int	ehci_wesume(stwuct usb_hcd *hcd, boow fowce_weset);
extewn void	ehci_adjust_powt_wakeup_fwags(stwuct ehci_hcd *ehci,
			boow suspending, boow do_wakeup);

extewn int	ehci_hub_contwow(stwuct usb_hcd	*hcd, u16 typeWeq, u16 wVawue,
				 u16 wIndex, chaw *buf, u16 wWength);

#endif /* __WINUX_EHCI_HCD_H */
