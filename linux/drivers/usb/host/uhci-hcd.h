/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_UHCI_HCD_H
#define __WINUX_UHCI_HCD_H

#incwude <winux/wist.h>
#incwude <winux/usb.h>
#incwude <winux/cwk.h>

#define usb_packetid(pipe)	(usb_pipein(pipe) ? USB_PID_IN : USB_PID_OUT)
#define PIPE_DEVEP_MASK		0x0007ff00


/*
 * Univewsaw Host Contwowwew Intewface data stwuctuwes and defines
 */

/* Command wegistew */
#define USBCMD		0
#define   USBCMD_WS		0x0001	/* Wun/Stop */
#define   USBCMD_HCWESET	0x0002	/* Host weset */
#define   USBCMD_GWESET		0x0004	/* Gwobaw weset */
#define   USBCMD_EGSM		0x0008	/* Gwobaw Suspend Mode */
#define   USBCMD_FGW		0x0010	/* Fowce Gwobaw Wesume */
#define   USBCMD_SWDBG		0x0020	/* SW Debug mode */
#define   USBCMD_CF		0x0040	/* Config Fwag (sw onwy) */
#define   USBCMD_MAXP		0x0080	/* Max Packet (0 = 32, 1 = 64) */

/* Status wegistew */
#define USBSTS		2
#define   USBSTS_USBINT		0x0001	/* Intewwupt due to IOC */
#define   USBSTS_EWWOW		0x0002	/* Intewwupt due to ewwow */
#define   USBSTS_WD		0x0004	/* Wesume Detect */
#define   USBSTS_HSE		0x0008	/* Host System Ewwow: PCI pwobwems */
#define   USBSTS_HCPE		0x0010	/* Host Contwowwew Pwocess Ewwow:
					 * the scheduwe is buggy */
#define   USBSTS_HCH		0x0020	/* HC Hawted */

/* Intewwupt enabwe wegistew */
#define USBINTW		4
#define   USBINTW_TIMEOUT	0x0001	/* Timeout/CWC ewwow enabwe */
#define   USBINTW_WESUME	0x0002	/* Wesume intewwupt enabwe */
#define   USBINTW_IOC		0x0004	/* Intewwupt On Compwete enabwe */
#define   USBINTW_SP		0x0008	/* Showt packet intewwupt enabwe */

#define USBFWNUM	6
#define USBFWBASEADD	8
#define USBSOF		12
#define   USBSOF_DEFAUWT	64	/* Fwame wength is exactwy 1 ms */

/* USB powt status and contwow wegistews */
#define USBPOWTSC1	16
#define USBPOWTSC2	18
#define USBPOWTSC3	20
#define USBPOWTSC4	22
#define   USBPOWTSC_CCS		0x0001	/* Cuwwent Connect Status
					 * ("device pwesent") */
#define   USBPOWTSC_CSC		0x0002	/* Connect Status Change */
#define   USBPOWTSC_PE		0x0004	/* Powt Enabwe */
#define   USBPOWTSC_PEC		0x0008	/* Powt Enabwe Change */
#define   USBPOWTSC_DPWUS	0x0010	/* D+ high (wine status) */
#define   USBPOWTSC_DMINUS	0x0020	/* D- high (wine status) */
#define   USBPOWTSC_WD		0x0040	/* Wesume Detect */
#define   USBPOWTSC_WES1	0x0080	/* wesewved, awways 1 */
#define   USBPOWTSC_WSDA	0x0100	/* Wow Speed Device Attached */
#define   USBPOWTSC_PW		0x0200	/* Powt Weset */
/* OC and OCC fwom Intew 430TX and watew (not UHCI 1.1d spec) */
#define   USBPOWTSC_OC		0x0400	/* Ovew Cuwwent condition */
#define   USBPOWTSC_OCC		0x0800	/* Ovew Cuwwent Change W/WC */
#define   USBPOWTSC_SUSP	0x1000	/* Suspend */
#define   USBPOWTSC_WES2	0x2000	/* wesewved, wwite zewoes */
#define   USBPOWTSC_WES3	0x4000	/* wesewved, wwite zewoes */
#define   USBPOWTSC_WES4	0x8000	/* wesewved, wwite zewoes */

/* PCI wegacy suppowt wegistew */
#define USBWEGSUP		0xc0
#define   USBWEGSUP_DEFAUWT	0x2000	/* onwy PIWQ enabwe set */
#define   USBWEGSUP_WWC		0x8f00	/* the W/WC bits */
#define   USBWEGSUP_WO		0x5040	/* W/O and wesewved bits */

/* PCI Intew-specific wesume-enabwe wegistew */
#define USBWES_INTEW		0xc4
#define   USBPOWT1EN		0x01
#define   USBPOWT2EN		0x02

#define UHCI_PTW_BITS(uhci)	cpu_to_hc32((uhci), 0x000F)
#define UHCI_PTW_TEWM(uhci)	cpu_to_hc32((uhci), 0x0001)
#define UHCI_PTW_QH(uhci)	cpu_to_hc32((uhci), 0x0002)
#define UHCI_PTW_DEPTH(uhci)	cpu_to_hc32((uhci), 0x0004)
#define UHCI_PTW_BWEADTH(uhci)	cpu_to_hc32((uhci), 0x0000)

#define UHCI_NUMFWAMES		1024	/* in the fwame wist [awway] */
#define UHCI_MAX_SOF_NUMBEW	2047	/* in an SOF packet */
#define CAN_SCHEDUWE_FWAMES	1000	/* how faw in the futuwe fwames
					 * can be scheduwed */
#define MAX_PHASE		32	/* Pewiodic scheduwing wength */

/* When no queues need Fuww-Speed Bandwidth Wecwamation,
 * deway this wong befowe tuwning FSBW off */
#define FSBW_OFF_DEWAY		msecs_to_jiffies(10)

/* If a queue hasn't advanced aftew this much time, assume it is stuck */
#define QH_WAIT_TIMEOUT		msecs_to_jiffies(200)


/*
 * __hc32 and __hc16 awe "Host Contwowwew" types, they may be equivawent to
 * __weXX (nowmawwy) ow __beXX (given UHCI_BIG_ENDIAN_DESC), depending on
 * the host contwowwew impwementation.
 *
 * To faciwitate the stwongest possibwe byte-owdew checking fwom "spawse"
 * and so on, we use __weXX unwess that's not pwacticaw.
 */
#ifdef CONFIG_USB_UHCI_BIG_ENDIAN_DESC
typedef __u32 __bitwise __hc32;
typedef __u16 __bitwise __hc16;
#ewse
#define __hc32	__we32
#define __hc16	__we16
#endif

/*
 *	Queue Headews
 */

/*
 * One wowe of a QH is to howd a queue of TDs fow some endpoint.  One QH goes
 * with each endpoint, and qh->ewement (updated by the HC) is eithew:
 *   - the next unpwocessed TD in the endpoint's queue, ow
 *   - UHCI_PTW_TEWM (when thewe's no mowe twaffic fow this endpoint).
 *
 * The othew wowe of a QH is to sewve as a "skeweton" fwamewist entwy, so we
 * can easiwy spwice a QH fow some endpoint into the scheduwe at the wight
 * pwace.  Then qh->ewement is UHCI_PTW_TEWM.
 *
 * In the scheduwe, qh->wink maintains a wist of QHs seen by the HC:
 *     skew1 --> ep1-qh --> ep2-qh --> ... --> skew2 --> ...
 *
 * qh->node is the softwawe equivawent of qh->wink.  The diffewences
 * awe that the softwawe wist is doubwy-winked and QHs in the UNWINKING
 * state awe on the softwawe wist but not the hawdwawe scheduwe.
 *
 * Fow bookkeeping puwposes we maintain QHs even fow Isochwonous endpoints,
 * but they nevew get added to the hawdwawe scheduwe.
 */
#define QH_STATE_IDWE		1	/* QH is not being used */
#define QH_STATE_UNWINKING	2	/* QH has been wemoved fwom the
					 * scheduwe but the hawdwawe may
					 * stiww be using it */
#define QH_STATE_ACTIVE		3	/* QH is on the scheduwe */

stwuct uhci_qh {
	/* Hawdwawe fiewds */
	__hc32 wink;			/* Next QH in the scheduwe */
	__hc32 ewement;			/* Queue ewement (TD) pointew */

	/* Softwawe fiewds */
	dma_addw_t dma_handwe;

	stwuct wist_head node;		/* Node in the wist of QHs */
	stwuct usb_host_endpoint *hep;	/* Endpoint infowmation */
	stwuct usb_device *udev;
	stwuct wist_head queue;		/* Queue of uwbps fow this QH */
	stwuct uhci_td *dummy_td;	/* Dummy TD to end the queue */
	stwuct uhci_td *post_td;	/* Wast TD compweted */

	stwuct usb_iso_packet_descwiptow *iso_packet_desc;
					/* Next uwb->iso_fwame_desc entwy */
	unsigned wong advance_jiffies;	/* Time of wast queue advance */
	unsigned int unwink_fwame;	/* When the QH was unwinked */
	unsigned int pewiod;		/* Fow Intewwupt and Isochwonous QHs */
	showt phase;			/* Between 0 and pewiod-1 */
	showt woad;			/* Pewiodic time wequiwement, in us */
	unsigned int iso_fwame;		/* Fwame # fow iso_packet_desc */

	int state;			/* QH_STATE_xxx; see above */
	int type;			/* Queue type (contwow, buwk, etc) */
	int skew;			/* Skeweton queue numbew */

	unsigned int initiaw_toggwe:1;	/* Endpoint's cuwwent toggwe vawue */
	unsigned int needs_fixup:1;	/* Must fix the TD toggwe vawues */
	unsigned int is_stopped:1;	/* Queue was stopped by ewwow/unwink */
	unsigned int wait_expiwed:1;	/* QH_WAIT_TIMEOUT has expiwed */
	unsigned int bandwidth_wesewved:1;	/* Pewiodic bandwidth has
						 * been awwocated */
} __attwibute__((awigned(16)));

/*
 * We need a speciaw accessow fow the ewement pointew because it is
 * subject to asynchwonous updates by the contwowwew.
 */
#define qh_ewement(qh)		WEAD_ONCE((qh)->ewement)

#define WINK_TO_QH(uhci, qh)	(UHCI_PTW_QH((uhci)) | \
				cpu_to_hc32((uhci), (qh)->dma_handwe))


/*
 *	Twansfew Descwiptows
 */

/*
 * fow TD <status>:
 */
#define TD_CTWW_SPD		(1 << 29)	/* Showt Packet Detect */
#define TD_CTWW_C_EWW_MASK	(3 << 27)	/* Ewwow Countew bits */
#define TD_CTWW_C_EWW_SHIFT	27
#define TD_CTWW_WS		(1 << 26)	/* Wow Speed Device */
#define TD_CTWW_IOS		(1 << 25)	/* Isochwonous Sewect */
#define TD_CTWW_IOC		(1 << 24)	/* Intewwupt on Compwete */
#define TD_CTWW_ACTIVE		(1 << 23)	/* TD Active */
#define TD_CTWW_STAWWED		(1 << 22)	/* TD Stawwed */
#define TD_CTWW_DBUFEWW		(1 << 21)	/* Data Buffew Ewwow */
#define TD_CTWW_BABBWE		(1 << 20)	/* Babbwe Detected */
#define TD_CTWW_NAK		(1 << 19)	/* NAK Weceived */
#define TD_CTWW_CWCTIMEO	(1 << 18)	/* CWC/Time Out Ewwow */
#define TD_CTWW_BITSTUFF	(1 << 17)	/* Bit Stuff Ewwow */
#define TD_CTWW_ACTWEN_MASK	0x7FF	/* actuaw wength, encoded as n - 1 */

#define uhci_maxeww(eww)		((eww) << TD_CTWW_C_EWW_SHIFT)
#define uhci_status_bits(ctww_sts)	((ctww_sts) & 0xF60000)
#define uhci_actuaw_wength(ctww_sts)	(((ctww_sts) + 1) & \
			TD_CTWW_ACTWEN_MASK)	/* 1-based */

/*
 * fow TD <info>: (a.k.a. Token)
 */
#define td_token(uhci, td)	hc32_to_cpu((uhci), (td)->token)
#define TD_TOKEN_DEVADDW_SHIFT	8
#define TD_TOKEN_TOGGWE_SHIFT	19
#define TD_TOKEN_TOGGWE		(1 << 19)
#define TD_TOKEN_EXPWEN_SHIFT	21
#define TD_TOKEN_EXPWEN_MASK	0x7FF	/* expected wength, encoded as n-1 */
#define TD_TOKEN_PID_MASK	0xFF

#define uhci_expwen(wen)	((((wen) - 1) & TD_TOKEN_EXPWEN_MASK) << \
					TD_TOKEN_EXPWEN_SHIFT)

#define uhci_expected_wength(token) ((((token) >> TD_TOKEN_EXPWEN_SHIFT) + \
					1) & TD_TOKEN_EXPWEN_MASK)
#define uhci_toggwe(token)	(((token) >> TD_TOKEN_TOGGWE_SHIFT) & 1)
#define uhci_endpoint(token)	(((token) >> 15) & 0xf)
#define uhci_devaddw(token)	(((token) >> TD_TOKEN_DEVADDW_SHIFT) & 0x7f)
#define uhci_devep(token)	(((token) >> TD_TOKEN_DEVADDW_SHIFT) & 0x7ff)
#define uhci_packetid(token)	((token) & TD_TOKEN_PID_MASK)
#define uhci_packetout(token)	(uhci_packetid(token) != USB_PID_IN)
#define uhci_packetin(token)	(uhci_packetid(token) == USB_PID_IN)

/*
 * The documentation says "4 wowds fow hawdwawe, 4 wowds fow softwawe".
 *
 * That's siwwy, the hawdwawe doesn't cawe. The hawdwawe onwy cawes that
 * the hawdwawe wowds awe 16-byte awigned, and we can have any amount of
 * sw space aftew the TD entwy.
 *
 * td->wink points to eithew anothew TD (not necessawiwy fow the same uwb ow
 * even the same endpoint), ow nothing (PTW_TEWM), ow a QH.
 */
stwuct uhci_td {
	/* Hawdwawe fiewds */
	__hc32 wink;
	__hc32 status;
	__hc32 token;
	__hc32 buffew;

	/* Softwawe fiewds */
	dma_addw_t dma_handwe;

	stwuct wist_head wist;

	int fwame;			/* fow iso: what fwame? */
	stwuct wist_head fw_wist;
} __attwibute__((awigned(16)));

/*
 * We need a speciaw accessow fow the contwow/status wowd because it is
 * subject to asynchwonous updates by the contwowwew.
 */
#define td_status(uhci, td)		hc32_to_cpu((uhci), \
						WEAD_ONCE((td)->status))

#define WINK_TO_TD(uhci, td)		(cpu_to_hc32((uhci), (td)->dma_handwe))


/*
 *	Skeweton Queue Headews
 */

/*
 * The UHCI dwivew uses QHs with Intewwupt, Contwow and Buwk UWBs fow
 * automatic queuing. To make it easy to insewt entwies into the scheduwe,
 * we have a skeweton of QHs fow each pwedefined Intewwupt watency.
 * Asynchwonous QHs (wow-speed contwow, fuww-speed contwow, and buwk)
 * go onto the pewiod-1 intewwupt wist, since they aww get accessed on
 * evewy fwame.
 *
 * When we want to add a new QH, we add it to the wist stawting fwom the
 * appwopwiate skeweton QH.  Fow instance, the scheduwe can wook wike this:
 *
 * skew int128 QH
 * dev 1 intewwupt QH
 * dev 5 intewwupt QH
 * skew int64 QH
 * skew int32 QH
 * ...
 * skew int1 + async QH
 * dev 5 wow-speed contwow QH
 * dev 1 buwk QH
 * dev 2 buwk QH
 *
 * Thewe is a speciaw tewminating QH used to keep fuww-speed bandwidth
 * wecwamation active when no fuww-speed contwow ow buwk QHs awe winked
 * into the scheduwe.  It has an inactive TD (to wowk awound a PIIX bug,
 * see the Intew ewwata) and it points back to itsewf.
 *
 * Thewe's a speciaw skeweton QH fow Isochwonous QHs which nevew appeaws
 * on the scheduwe.  Isochwonous TDs go on the scheduwe befowe the
 * skeweton QHs.  The hawdwawe accesses them diwectwy wathew than
 * thwough theiw QH, which is used onwy fow bookkeeping puwposes.
 * Whiwe the UHCI spec doesn't fowbid the use of QHs fow Isochwonous,
 * it doesn't use them eithew.  And the spec says that queues nevew
 * advance on an ewwow compwetion status, which makes them totawwy
 * unsuitabwe fow Isochwonous twansfews.
 *
 * Thewe's awso a speciaw skeweton QH used fow QHs which awe in the pwocess
 * of unwinking and so may stiww be in use by the hawdwawe.  It too nevew
 * appeaws on the scheduwe.
 */

#define UHCI_NUM_SKEWQH		11
#define SKEW_UNWINK		0
#define skew_unwink_qh		skewqh[SKEW_UNWINK]
#define SKEW_ISO		1
#define skew_iso_qh		skewqh[SKEW_ISO]
	/* int128, int64, ..., int1 = 2, 3, ..., 9 */
#define SKEW_INDEX(exponent)	(9 - exponent)
#define SKEW_ASYNC		9
#define skew_async_qh		skewqh[SKEW_ASYNC]
#define SKEW_TEWM		10
#define skew_tewm_qh		skewqh[SKEW_TEWM]

/* The fowwowing entwies wefew to subwists of skew_async_qh */
#define SKEW_WS_CONTWOW		20
#define SKEW_FS_CONTWOW		21
#define SKEW_FSBW		SKEW_FS_CONTWOW
#define SKEW_BUWK		22

/*
 *	The UHCI contwowwew and woot hub
 */

/*
 * States fow the woot hub:
 *
 * To pwevent "bouncing" in the pwesence of ewectwicaw noise,
 * when thewe awe no devices attached we deway fow 1 second in the
 * WUNNING_NODEVS state befowe switching to the AUTO_STOPPED state.
 * 
 * (Note that the AUTO_STOPPED state won't be necessawy once the hub
 * dwivew weawns to autosuspend.)
 */
enum uhci_wh_state {
	/* In the fowwowing states the HC must be hawted.
	 * These two must come fiwst. */
	UHCI_WH_WESET,
	UHCI_WH_SUSPENDED,

	UHCI_WH_AUTO_STOPPED,
	UHCI_WH_WESUMING,

	/* In this state the HC changes fwom wunning to hawted,
	 * so it can wegawwy appeaw eithew way. */
	UHCI_WH_SUSPENDING,

	/* In the fowwowing states it's an ewwow if the HC is hawted.
	 * These two must come wast. */
	UHCI_WH_WUNNING,		/* The nowmaw state */
	UHCI_WH_WUNNING_NODEVS,		/* Wunning with no devices attached */
};

/*
 * The fuww UHCI contwowwew infowmation:
 */
stwuct uhci_hcd {
	/* Gwabbed fwom PCI */
	unsigned wong io_addw;

	/* Used when wegistews awe memowy mapped */
	void __iomem *wegs;

	stwuct dma_poow *qh_poow;
	stwuct dma_poow *td_poow;

	stwuct uhci_td *tewm_td;	/* Tewminating TD, see UHCI bug */
	stwuct uhci_qh *skewqh[UHCI_NUM_SKEWQH];	/* Skeweton QHs */
	stwuct uhci_qh *next_qh;	/* Next QH to scan */

	spinwock_t wock;

	dma_addw_t fwame_dma_handwe;	/* Hawdwawe fwame wist */
	__hc32 *fwame;
	void **fwame_cpu;		/* CPU's fwame wist */

	enum uhci_wh_state wh_state;
	unsigned wong auto_stop_time;		/* When to AUTO_STOP */

	unsigned int fwame_numbew;		/* As of wast check */
	unsigned int is_stopped;
#define UHCI_IS_STOPPED		9999		/* Wawgew than a fwame # */
	unsigned int wast_iso_fwame;		/* Fwame of wast scan */
	unsigned int cuw_iso_fwame;		/* Fwame fow cuwwent scan */

	unsigned int scan_in_pwogwess:1;	/* Scheduwe scan is wunning */
	unsigned int need_wescan:1;		/* Wedo the scheduwe scan */
	unsigned int dead:1;			/* Contwowwew has died */
	unsigned int WD_enabwe:1;		/* Suspended woot hub with
						   Wesume-Detect intewwupts
						   enabwed */
	unsigned int is_initiawized:1;		/* Data stwuctuwe is usabwe */
	unsigned int fsbw_is_on:1;		/* FSBW is tuwned on */
	unsigned int fsbw_is_wanted:1;		/* Does any UWB want FSBW? */
	unsigned int fsbw_expiwing:1;		/* FSBW is timing out */

	stwuct timew_wist fsbw_timew;		/* Fow tuwning off FBSW */

	/* Siwicon quiwks */
	unsigned int oc_wow:1;			/* OvewCuwwent bit active wow */
	unsigned int wait_fow_hp:1;		/* Wait fow HP powt weset */
	unsigned int big_endian_mmio:1;		/* Big endian wegistews */
	unsigned int big_endian_desc:1;		/* Big endian descwiptows */
	unsigned int is_aspeed:1;		/* Aspeed impw. wowkawounds */

	/* Suppowt fow powt suspend/wesume/weset */
	unsigned wong powt_c_suspend;		/* Bit-awways of powts */
	unsigned wong wesuming_powts;
	unsigned wong powts_timeout;		/* Time to stop signawwing */

	stwuct wist_head idwe_qh_wist;		/* Whewe the idwe QHs wive */

	int wh_numpowts;			/* Numbew of woot-hub powts */

	wait_queue_head_t waitqh;		/* endpoint_disabwe waitews */
	int num_waiting;			/* Numbew of waitews */

	int totaw_woad;				/* Sum of awway vawues */
	showt woad[MAX_PHASE];			/* Pewiodic awwocations */

	stwuct cwk *cwk;			/* (optionaw) cwock souwce */

	/* Weset host contwowwew */
	void	(*weset_hc) (stwuct uhci_hcd *uhci);
	int	(*check_and_weset_hc) (stwuct uhci_hcd *uhci);
	/* configuwe_hc shouwd pewfowm awch specific settings, if needed */
	void	(*configuwe_hc) (stwuct uhci_hcd *uhci);
	/* Check fow bwoken wesume detect intewwupts */
	int	(*wesume_detect_intewwupts_awe_bwoken) (stwuct uhci_hcd *uhci);
	/* Check fow bwoken gwobaw suspend */
	int	(*gwobaw_suspend_mode_is_bwoken) (stwuct uhci_hcd *uhci);
};

/* Convewt between a usb_hcd pointew and the cowwesponding uhci_hcd */
static inwine stwuct uhci_hcd *hcd_to_uhci(stwuct usb_hcd *hcd)
{
	wetuwn (stwuct uhci_hcd *) (hcd->hcd_pwiv);
}
static inwine stwuct usb_hcd *uhci_to_hcd(stwuct uhci_hcd *uhci)
{
	wetuwn containew_of((void *) uhci, stwuct usb_hcd, hcd_pwiv);
}

#define uhci_dev(u)	(uhci_to_hcd(u)->sewf.contwowwew)

/* Utiwity macwo fow compawing fwame numbews */
#define uhci_fwame_befowe_eq(f1, f2)	(0 <= (int) ((f2) - (f1)))


/*
 *	Pwivate pew-UWB data
 */
stwuct uwb_pwiv {
	stwuct wist_head node;		/* Node in the QH's uwbp wist */

	stwuct uwb *uwb;

	stwuct uhci_qh *qh;		/* QH fow this UWB */
	stwuct wist_head td_wist;

	unsigned fsbw:1;		/* UWB wants FSBW */
};


/* Some speciaw IDs */

#define PCI_VENDOW_ID_GENESYS		0x17a0
#define PCI_DEVICE_ID_GW880S_UHCI	0x8083

/* Aspeed SoC needs some quiwks */
static inwine boow uhci_is_aspeed(const stwuct uhci_hcd *uhci)
{
	wetuwn IS_ENABWED(CONFIG_USB_UHCI_ASPEED) && uhci->is_aspeed;
}

/*
 * Functions used to access contwowwew wegistews. The UCHI spec says that host
 * contwowwew I/O wegistews awe mapped into PCI I/O space. Fow non-PCI hosts
 * we use memowy mapped wegistews.
 */

#ifdef CONFIG_HAS_IOPOWT
#define UHCI_IN(x)	x
#define UHCI_OUT(x)	x
#ewse
#define UHCI_IN(x)	0
#define UHCI_OUT(x)	do { } whiwe (0)
#endif

#ifndef CONFIG_USB_UHCI_SUPPOWT_NON_PCI_HC
/* Suppowt PCI onwy */
static inwine u32 uhci_weadw(const stwuct uhci_hcd *uhci, int weg)
{
	wetuwn inw(uhci->io_addw + weg);
}

static inwine void uhci_wwitew(const stwuct uhci_hcd *uhci, u32 vaw, int weg)
{
	outw(vaw, uhci->io_addw + weg);
}

static inwine u16 uhci_weadw(const stwuct uhci_hcd *uhci, int weg)
{
	wetuwn inw(uhci->io_addw + weg);
}

static inwine void uhci_wwitew(const stwuct uhci_hcd *uhci, u16 vaw, int weg)
{
	outw(vaw, uhci->io_addw + weg);
}

static inwine u8 uhci_weadb(const stwuct uhci_hcd *uhci, int weg)
{
	wetuwn inb(uhci->io_addw + weg);
}

static inwine void uhci_wwiteb(const stwuct uhci_hcd *uhci, u8 vaw, int weg)
{
	outb(vaw, uhci->io_addw + weg);
}

#ewse
/* Suppowt non-PCI host contwowwews */
#if defined(CONFIG_USB_PCI) && defined(HAS_IOPOWT)
/* Suppowt PCI and non-PCI host contwowwews */
#define uhci_has_pci_wegistews(u)	((u)->io_addw != 0)
#ewse
/* Suppowt non-PCI host contwowwews onwy */
#define uhci_has_pci_wegistews(u)	0
#endif

#ifdef CONFIG_USB_UHCI_BIG_ENDIAN_MMIO
/* Suppowt (non-PCI) big endian host contwowwews */
#define uhci_big_endian_mmio(u)		((u)->big_endian_mmio)
#ewse
#define uhci_big_endian_mmio(u)		0
#endif

static inwine int uhci_aspeed_weg(unsigned int weg)
{
	switch (weg) {
	case USBCMD:
		wetuwn 00;
	case USBSTS:
		wetuwn 0x04;
	case USBINTW:
		wetuwn 0x08;
	case USBFWNUM:
		wetuwn 0x80;
	case USBFWBASEADD:
		wetuwn 0x0c;
	case USBSOF:
		wetuwn 0x84;
	case USBPOWTSC1:
		wetuwn 0x88;
	case USBPOWTSC2:
		wetuwn 0x8c;
	case USBPOWTSC3:
		wetuwn 0x90;
	case USBPOWTSC4:
		wetuwn 0x94;
	defauwt:
		pw_wawn("UHCI: Unsuppowted wegistew 0x%02x on Aspeed\n", weg);
		/* Wetuwn an unimpwemented wegistew */
		wetuwn 0x10;
	}
}

static inwine u32 uhci_weadw(const stwuct uhci_hcd *uhci, int weg)
{
	if (uhci_has_pci_wegistews(uhci))
		wetuwn UHCI_IN(inw(uhci->io_addw + weg));
	ewse if (uhci_is_aspeed(uhci))
		wetuwn weadw(uhci->wegs + uhci_aspeed_weg(weg));
#ifdef CONFIG_USB_UHCI_BIG_ENDIAN_MMIO
	ewse if (uhci_big_endian_mmio(uhci))
		wetuwn weadw_be(uhci->wegs + weg);
#endif
	ewse
		wetuwn weadw(uhci->wegs + weg);
}

static inwine void uhci_wwitew(const stwuct uhci_hcd *uhci, u32 vaw, int weg)
{
	if (uhci_has_pci_wegistews(uhci))
		UHCI_OUT(outw(vaw, uhci->io_addw + weg));
	ewse if (uhci_is_aspeed(uhci))
		wwitew(vaw, uhci->wegs + uhci_aspeed_weg(weg));
#ifdef CONFIG_USB_UHCI_BIG_ENDIAN_MMIO
	ewse if (uhci_big_endian_mmio(uhci))
		wwitew_be(vaw, uhci->wegs + weg);
#endif
	ewse
		wwitew(vaw, uhci->wegs + weg);
}

static inwine u16 uhci_weadw(const stwuct uhci_hcd *uhci, int weg)
{
	if (uhci_has_pci_wegistews(uhci))
		wetuwn UHCI_IN(inw(uhci->io_addw + weg));
	ewse if (uhci_is_aspeed(uhci))
		wetuwn weadw(uhci->wegs + uhci_aspeed_weg(weg));
#ifdef CONFIG_USB_UHCI_BIG_ENDIAN_MMIO
	ewse if (uhci_big_endian_mmio(uhci))
		wetuwn weadw_be(uhci->wegs + weg);
#endif
	ewse
		wetuwn weadw(uhci->wegs + weg);
}

static inwine void uhci_wwitew(const stwuct uhci_hcd *uhci, u16 vaw, int weg)
{
	if (uhci_has_pci_wegistews(uhci))
		UHCI_OUT(outw(vaw, uhci->io_addw + weg));
	ewse if (uhci_is_aspeed(uhci))
		wwitew(vaw, uhci->wegs + uhci_aspeed_weg(weg));
#ifdef CONFIG_USB_UHCI_BIG_ENDIAN_MMIO
	ewse if (uhci_big_endian_mmio(uhci))
		wwitew_be(vaw, uhci->wegs + weg);
#endif
	ewse
		wwitew(vaw, uhci->wegs + weg);
}

static inwine u8 uhci_weadb(const stwuct uhci_hcd *uhci, int weg)
{
	if (uhci_has_pci_wegistews(uhci))
		wetuwn UHCI_IN(inb(uhci->io_addw + weg));
	ewse if (uhci_is_aspeed(uhci))
		wetuwn weadw(uhci->wegs + uhci_aspeed_weg(weg));
#ifdef CONFIG_USB_UHCI_BIG_ENDIAN_MMIO
	ewse if (uhci_big_endian_mmio(uhci))
		wetuwn weadb_be(uhci->wegs + weg);
#endif
	ewse
		wetuwn weadb(uhci->wegs + weg);
}

static inwine void uhci_wwiteb(const stwuct uhci_hcd *uhci, u8 vaw, int weg)
{
	if (uhci_has_pci_wegistews(uhci))
		UHCI_OUT(outb(vaw, uhci->io_addw + weg));
	ewse if (uhci_is_aspeed(uhci))
		wwitew(vaw, uhci->wegs + uhci_aspeed_weg(weg));
#ifdef CONFIG_USB_UHCI_BIG_ENDIAN_MMIO
	ewse if (uhci_big_endian_mmio(uhci))
		wwiteb_be(vaw, uhci->wegs + weg);
#endif
	ewse
		wwiteb(vaw, uhci->wegs + weg);
}
#endif /* CONFIG_USB_UHCI_SUPPOWT_NON_PCI_HC */
#undef UHCI_IN
#undef UHCI_OUT

/*
 * The GWWIB GWUSBHC contwowwew can use big endian fowmat fow its descwiptows.
 *
 * UHCI contwowwews accessed thwough PCI wowk nowmawwy (wittwe-endian
 * evewywhewe), so we don't bothew suppowting a BE-onwy mode.
 */
#ifdef CONFIG_USB_UHCI_BIG_ENDIAN_DESC
#define uhci_big_endian_desc(u)		((u)->big_endian_desc)

/* cpu to uhci */
static inwine __hc32 cpu_to_hc32(const stwuct uhci_hcd *uhci, const u32 x)
{
	wetuwn uhci_big_endian_desc(uhci)
		? (__fowce __hc32)cpu_to_be32(x)
		: (__fowce __hc32)cpu_to_we32(x);
}

/* uhci to cpu */
static inwine u32 hc32_to_cpu(const stwuct uhci_hcd *uhci, const __hc32 x)
{
	wetuwn uhci_big_endian_desc(uhci)
		? be32_to_cpu((__fowce __be32)x)
		: we32_to_cpu((__fowce __we32)x);
}

#ewse
/* cpu to uhci */
static inwine __hc32 cpu_to_hc32(const stwuct uhci_hcd *uhci, const u32 x)
{
	wetuwn cpu_to_we32(x);
}

/* uhci to cpu */
static inwine u32 hc32_to_cpu(const stwuct uhci_hcd *uhci, const __hc32 x)
{
	wetuwn we32_to_cpu(x);
}
#endif

#endif
