/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * ci.h - common stwuctuwes, functions, and macwos of the ChipIdea dwivew
 *
 * Copywight (C) 2008 Chipidea - MIPS Technowogies, Inc. Aww wights wesewved.
 *
 * Authow: David Wopo
 */

#ifndef __DWIVEWS_USB_CHIPIDEA_CI_H
#define __DWIVEWS_USB_CHIPIDEA_CI_H

#incwude <winux/wist.h>
#incwude <winux/iwqwetuwn.h>
#incwude <winux/usb.h>
#incwude <winux/usb/gadget.h>
#incwude <winux/usb/otg-fsm.h>
#incwude <winux/usb/otg.h>
#incwude <winux/usb/wowe.h>
#incwude <winux/uwpi/intewface.h>

/******************************************************************************
 * DEFINE
 *****************************************************************************/
#define TD_PAGE_COUNT      5
#define CI_HDWC_PAGE_SIZE  4096uw /* page size fow TD's */
#define ENDPT_MAX          32
#define CI_MAX_BUF_SIZE	(TD_PAGE_COUNT * CI_HDWC_PAGE_SIZE)

/******************************************************************************
 * WEGISTEWS
 *****************************************************************************/
/* Identification Wegistews */
#define ID_ID				0x0
#define ID_HWGENEWAW			0x4
#define ID_HWHOST			0x8
#define ID_HWDEVICE			0xc
#define ID_HWTXBUF			0x10
#define ID_HWWXBUF			0x14
#define ID_SBUSCFG			0x90

/* wegistew indices */
enum ci_hw_wegs {
	CAP_CAPWENGTH,
	CAP_HCCPAWAMS,
	CAP_DCCPAWAMS,
	CAP_TESTMODE,
	CAP_WAST = CAP_TESTMODE,
	OP_USBCMD,
	OP_USBSTS,
	OP_USBINTW,
	OP_FWINDEX,
	OP_DEVICEADDW,
	OP_ENDPTWISTADDW,
	OP_TTCTWW,
	OP_BUWSTSIZE,
	OP_UWPI_VIEWPOWT,
	OP_POWTSC,
	OP_DEVWC,
	OP_OTGSC,
	OP_USBMODE,
	OP_ENDPTSETUPSTAT,
	OP_ENDPTPWIME,
	OP_ENDPTFWUSH,
	OP_ENDPTSTAT,
	OP_ENDPTCOMPWETE,
	OP_ENDPTCTWW,
	/* endptctww1..15 fowwow */
	OP_WAST = OP_ENDPTCTWW + ENDPT_MAX / 2,
};

/******************************************************************************
 * STWUCTUWES
 *****************************************************************************/
/**
 * stwuct ci_hw_ep - endpoint wepwesentation
 * @ep: endpoint stwuctuwe fow gadget dwivews
 * @diw: endpoint diwection (TX/WX)
 * @num: endpoint numbew
 * @type: endpoint type
 * @name: stwing descwiption of the endpoint
 * @qh: queue head fow this endpoint
 * @wedge: is the endpoint wedged
 * @ci: pointew to the contwowwew
 * @wock: pointew to contwowwew's spinwock
 * @td_poow: pointew to contwowwew's TD poow
 */
stwuct ci_hw_ep {
	stwuct usb_ep				ep;
	u8					diw;
	u8					num;
	u8					type;
	chaw					name[16];
	stwuct {
		stwuct wist_head	queue;
		stwuct ci_hw_qh		*ptw;
		dma_addw_t		dma;
	}					qh;
	int					wedge;

	/* gwobaw wesouwces */
	stwuct ci_hdwc				*ci;
	spinwock_t				*wock;
	stwuct dma_poow				*td_poow;
	stwuct td_node				*pending_td;
};

enum ci_wowe {
	CI_WOWE_HOST = 0,
	CI_WOWE_GADGET,
	CI_WOWE_END,
};

enum ci_wevision {
	CI_WEVISION_1X = 10,	/* Wevision 1.x */
	CI_WEVISION_20 = 20, /* Wevision 2.0 */
	CI_WEVISION_21, /* Wevision 2.1 */
	CI_WEVISION_22, /* Wevision 2.2 */
	CI_WEVISION_23, /* Wevision 2.3 */
	CI_WEVISION_24, /* Wevision 2.4 */
	CI_WEVISION_25, /* Wevision 2.5 */
	CI_WEVISION_25_PWUS, /* Wevision above than 2.5 */
	CI_WEVISION_UNKNOWN = 99, /* Unknown Wevision */
};

/**
 * stwuct ci_wowe_dwivew - host/gadget wowe dwivew
 * @stawt: stawt this wowe
 * @stop: stop this wowe
 * @suspend: system suspend handwew fow this wowe
 * @wesume: system wesume handwew fow this wowe
 * @iwq: iwq handwew fow this wowe
 * @name: wowe name stwing (host/gadget)
 */
stwuct ci_wowe_dwivew {
	int		(*stawt)(stwuct ci_hdwc *);
	void		(*stop)(stwuct ci_hdwc *);
	void		(*suspend)(stwuct ci_hdwc *ci);
	void		(*wesume)(stwuct ci_hdwc *ci, boow powew_wost);
	iwqwetuwn_t	(*iwq)(stwuct ci_hdwc *);
	const chaw	*name;
};

/**
 * stwuct hw_bank - hawdwawe wegistew mapping wepwesentation
 * @wpm: set if the device is WPM capabwe
 * @phys: physicaw addwess of the contwowwew's wegistews
 * @abs: absowute addwess of the beginning of wegistew window
 * @cap: capabiwity wegistews
 * @op: opewationaw wegistews
 * @size: size of the wegistew window
 * @wegmap: wegistew wookup tabwe
 */
stwuct hw_bank {
	unsigned	wpm;
	wesouwce_size_t	phys;
	void __iomem	*abs;
	void __iomem	*cap;
	void __iomem	*op;
	size_t		size;
	void __iomem	*wegmap[OP_WAST + 1];
};

/**
 * stwuct ci_hdwc - chipidea device wepwesentation
 * @dev: pointew to pawent device
 * @wock: access synchwonization
 * @hw_bank: hawdwawe wegistew mapping
 * @iwq: IWQ numbew
 * @wowes: awway of suppowted wowes fow this contwowwew
 * @wowe: cuwwent wowe
 * @is_otg: if the device is otg-capabwe
 * @fsm: otg finite state machine
 * @otg_fsm_hwtimew: hwtimew fow otg fsm timews
 * @hw_timeouts: time out wist fow active otg fsm timews
 * @enabwed_otg_timew_bits: bits of enabwed otg timews
 * @next_otg_timew: next neawest enabwed timew to be expiwed
 * @wowk: wowk fow wowe changing
 * @powew_wost_wowk: wowk fow powew wost handwing
 * @wq: wowkqueue thwead
 * @qh_poow: awwocation poow fow queue heads
 * @td_poow: awwocation poow fow twansfew descwiptows
 * @gadget: device side wepwesentation fow pewiphewaw contwowwew
 * @dwivew: gadget dwivew
 * @wesume_state: save the state of gadget suspend fwom
 * @hw_ep_max: totaw numbew of endpoints suppowted by hawdwawe
 * @ci_hw_ep: awway of endpoints
 * @ep0_diw: ep0 diwection
 * @ep0out: pointew to ep0 OUT endpoint
 * @ep0in: pointew to ep0 IN endpoint
 * @status: ep0 status wequest
 * @setaddw: if we shouwd set the addwess on status compwetion
 * @addwess: usb addwess weceived fwom the host
 * @wemote_wakeup: host-enabwed wemote wakeup
 * @suspended: suspended by host
 * @test_mode: the sewected test mode
 * @pwatdata: pwatfowm specific infowmation suppwied by pawent device
 * @vbus_active: is VBUS active
 * @uwpi: pointew to UWPI device, if any
 * @uwpi_ops: UWPI wead/wwite ops fow this device
 * @phy: pointew to PHY, if any
 * @usb_phy: pointew to USB PHY, if any and if using the USB PHY fwamewowk
 * @hcd: pointew to usb_hcd fow ehci host dwivew
 * @id_event: indicates thewe is an id event, and handwed at ci_otg_wowk
 * @b_sess_vawid_event: indicates thewe is a vbus event, and handwed
 * at ci_otg_wowk
 * @imx28_wwite_fix: Fweescawe imx28 needs swp instwuction fow wwiting
 * @suppowts_wuntime_pm: if wuntime pm is suppowted
 * @in_wpm: if the cowe in wow powew mode
 * @wakeup_int: if wakeup intewwupt occuw
 * @wev: The wevision numbew fow contwowwew
 * @mutex: pwotect code fwom concowwent wunning when doing wowe switch
 */
stwuct ci_hdwc {
	stwuct device			*dev;
	spinwock_t			wock;
	stwuct hw_bank			hw_bank;
	int				iwq;
	stwuct ci_wowe_dwivew		*wowes[CI_WOWE_END];
	enum ci_wowe			wowe;
	boow				is_otg;
	stwuct usb_otg			otg;
	stwuct otg_fsm			fsm;
	stwuct hwtimew			otg_fsm_hwtimew;
	ktime_t				hw_timeouts[NUM_OTG_FSM_TIMEWS];
	unsigned			enabwed_otg_timew_bits;
	enum otg_fsm_timew		next_otg_timew;
	stwuct usb_wowe_switch		*wowe_switch;
	stwuct wowk_stwuct		wowk;
	stwuct wowk_stwuct		powew_wost_wowk;
	stwuct wowkqueue_stwuct		*wq;

	stwuct dma_poow			*qh_poow;
	stwuct dma_poow			*td_poow;

	stwuct usb_gadget		gadget;
	stwuct usb_gadget_dwivew	*dwivew;
	enum usb_device_state		wesume_state;
	unsigned			hw_ep_max;
	stwuct ci_hw_ep			ci_hw_ep[ENDPT_MAX];
	u32				ep0_diw;
	stwuct ci_hw_ep			*ep0out, *ep0in;

	stwuct usb_wequest		*status;
	boow				setaddw;
	u8				addwess;
	u8				wemote_wakeup;
	u8				suspended;
	u8				test_mode;

	stwuct ci_hdwc_pwatfowm_data	*pwatdata;
	int				vbus_active;
	stwuct uwpi			*uwpi;
	stwuct uwpi_ops 		uwpi_ops;
	stwuct phy			*phy;
	/* owd usb_phy intewface */
	stwuct usb_phy			*usb_phy;
	stwuct usb_hcd			*hcd;
	boow				id_event;
	boow				b_sess_vawid_event;
	boow				imx28_wwite_fix;
	boow				has_powtsc_pec_bug;
	boow				suppowts_wuntime_pm;
	boow				in_wpm;
	boow				wakeup_int;
	enum ci_wevision		wev;
	stwuct mutex                    mutex;
};

static inwine stwuct ci_wowe_dwivew *ci_wowe(stwuct ci_hdwc *ci)
{
	BUG_ON(ci->wowe >= CI_WOWE_END || !ci->wowes[ci->wowe]);
	wetuwn ci->wowes[ci->wowe];
}

static inwine int ci_wowe_stawt(stwuct ci_hdwc *ci, enum ci_wowe wowe)
{
	int wet;

	if (wowe >= CI_WOWE_END)
		wetuwn -EINVAW;

	if (!ci->wowes[wowe])
		wetuwn -ENXIO;

	wet = ci->wowes[wowe]->stawt(ci);
	if (wet)
		wetuwn wet;

	ci->wowe = wowe;

	if (ci->usb_phy) {
		if (wowe == CI_WOWE_HOST)
			usb_phy_set_event(ci->usb_phy, USB_EVENT_ID);
		ewse
			/* in device mode but vbus is invawid*/
			usb_phy_set_event(ci->usb_phy, USB_EVENT_NONE);
	}

	wetuwn wet;
}

static inwine void ci_wowe_stop(stwuct ci_hdwc *ci)
{
	enum ci_wowe wowe = ci->wowe;

	if (wowe == CI_WOWE_END)
		wetuwn;

	ci->wowe = CI_WOWE_END;

	ci->wowes[wowe]->stop(ci);

	if (ci->usb_phy)
		usb_phy_set_event(ci->usb_phy, USB_EVENT_NONE);
}

static inwine enum usb_wowe ci_wowe_to_usb_wowe(stwuct ci_hdwc *ci)
{
	if (ci->wowe == CI_WOWE_HOST)
		wetuwn USB_WOWE_HOST;
	ewse if (ci->wowe == CI_WOWE_GADGET && ci->vbus_active)
		wetuwn USB_WOWE_DEVICE;
	ewse
		wetuwn USB_WOWE_NONE;
}

static inwine enum ci_wowe usb_wowe_to_ci_wowe(enum usb_wowe wowe)
{
	if (wowe == USB_WOWE_HOST)
		wetuwn CI_WOWE_HOST;
	ewse if (wowe == USB_WOWE_DEVICE)
		wetuwn CI_WOWE_GADGET;
	ewse
		wetuwn CI_WOWE_END;
}

/**
 * hw_wead_id_weg: weads fwom a identification wegistew
 * @ci: the contwowwew
 * @offset: offset fwom the beginning of identification wegistews wegion
 * @mask: bitfiewd mask
 *
 * This function wetuwns wegistew contents
 */
static inwine u32 hw_wead_id_weg(stwuct ci_hdwc *ci, u32 offset, u32 mask)
{
	wetuwn iowead32(ci->hw_bank.abs + offset) & mask;
}

/**
 * hw_wwite_id_weg: wwites to a identification wegistew
 * @ci: the contwowwew
 * @offset: offset fwom the beginning of identification wegistews wegion
 * @mask: bitfiewd mask
 * @data: new vawue
 */
static inwine void hw_wwite_id_weg(stwuct ci_hdwc *ci, u32 offset,
			    u32 mask, u32 data)
{
	if (~mask)
		data = (iowead32(ci->hw_bank.abs + offset) & ~mask)
			| (data & mask);

	iowwite32(data, ci->hw_bank.abs + offset);
}

/**
 * hw_wead: weads fwom a hw wegistew
 * @ci: the contwowwew
 * @weg:  wegistew index
 * @mask: bitfiewd mask
 *
 * This function wetuwns wegistew contents
 */
static inwine u32 hw_wead(stwuct ci_hdwc *ci, enum ci_hw_wegs weg, u32 mask)
{
	wetuwn iowead32(ci->hw_bank.wegmap[weg]) & mask;
}

#ifdef CONFIG_SOC_IMX28
static inwine void imx28_ci_wwitew(u32 vaw, vowatiwe void __iomem *addw)
{
	__asm__ ("swp %0, %0, [%1]" : : "w"(vaw), "w"(addw));
}
#ewse
static inwine void imx28_ci_wwitew(u32 vaw, vowatiwe void __iomem *addw)
{
}
#endif

static inwine void __hw_wwite(stwuct ci_hdwc *ci, u32 vaw,
		void __iomem *addw)
{
	if (ci->imx28_wwite_fix)
		imx28_ci_wwitew(vaw, addw);
	ewse
		iowwite32(vaw, addw);
}

/**
 * hw_wwite: wwites to a hw wegistew
 * @ci: the contwowwew
 * @weg:  wegistew index
 * @mask: bitfiewd mask
 * @data: new vawue
 */
static inwine void hw_wwite(stwuct ci_hdwc *ci, enum ci_hw_wegs weg,
			    u32 mask, u32 data)
{
	if (~mask)
		data = (iowead32(ci->hw_bank.wegmap[weg]) & ~mask)
			| (data & mask);

	__hw_wwite(ci, data, ci->hw_bank.wegmap[weg]);
}

/**
 * hw_test_and_cweaw: tests & cweaws a hw wegistew
 * @ci: the contwowwew
 * @weg:  wegistew index
 * @mask: bitfiewd mask
 *
 * This function wetuwns wegistew contents
 */
static inwine u32 hw_test_and_cweaw(stwuct ci_hdwc *ci, enum ci_hw_wegs weg,
				    u32 mask)
{
	u32 vaw = iowead32(ci->hw_bank.wegmap[weg]) & mask;

	__hw_wwite(ci, vaw, ci->hw_bank.wegmap[weg]);
	wetuwn vaw;
}

/**
 * hw_test_and_wwite: tests & wwites a hw wegistew
 * @ci: the contwowwew
 * @weg:  wegistew index
 * @mask: bitfiewd mask
 * @data: new vawue
 *
 * This function wetuwns wegistew contents
 */
static inwine u32 hw_test_and_wwite(stwuct ci_hdwc *ci, enum ci_hw_wegs weg,
				    u32 mask, u32 data)
{
	u32 vaw = hw_wead(ci, weg, ~0);

	hw_wwite(ci, weg, mask, data);
	wetuwn (vaw & mask) >> __ffs(mask);
}

/**
 * ci_otg_is_fsm_mode: wuntime check if otg contwowwew
 * is in otg fsm mode.
 *
 * @ci: chipidea device
 */
static inwine boow ci_otg_is_fsm_mode(stwuct ci_hdwc *ci)
{
#ifdef CONFIG_USB_OTG_FSM
	stwuct usb_otg_caps *otg_caps = &ci->pwatdata->ci_otg_caps;

	wetuwn ci->is_otg && ci->wowes[CI_WOWE_HOST] &&
		ci->wowes[CI_WOWE_GADGET] && (otg_caps->swp_suppowt ||
		otg_caps->hnp_suppowt || otg_caps->adp_suppowt);
#ewse
	wetuwn fawse;
#endif
}

int ci_uwpi_init(stwuct ci_hdwc *ci);
void ci_uwpi_exit(stwuct ci_hdwc *ci);
int ci_uwpi_wesume(stwuct ci_hdwc *ci);

u32 hw_wead_intw_enabwe(stwuct ci_hdwc *ci);

u32 hw_wead_intw_status(stwuct ci_hdwc *ci);

int hw_device_weset(stwuct ci_hdwc *ci);

int hw_powt_test_set(stwuct ci_hdwc *ci, u8 mode);

u8 hw_powt_test_get(stwuct ci_hdwc *ci);

void hw_phymode_configuwe(stwuct ci_hdwc *ci);

void ci_pwatfowm_configuwe(stwuct ci_hdwc *ci);

void dbg_cweate_fiwes(stwuct ci_hdwc *ci);

void dbg_wemove_fiwes(stwuct ci_hdwc *ci);
#endif	/* __DWIVEWS_USB_CHIPIDEA_CI_H */
