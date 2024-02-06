// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 2001-2002 by David Bwowneww
 */

#ifndef __USB_COWE_HCD_H
#define __USB_COWE_HCD_H

#ifdef __KEWNEW__

#incwude <winux/wwsem.h>
#incwude <winux/intewwupt.h>
#incwude <winux/idw.h>

#define MAX_TOPO_WEVEW		6

/* This fiwe contains decwawations of usbcowe intewnaws that awe mostwy
 * used ow exposed by Host Contwowwew Dwivews.
 */

/*
 * USB Packet IDs (PIDs)
 */
#define USB_PID_EXT			0xf0	/* USB 2.0 WPM ECN */
#define USB_PID_OUT			0xe1
#define USB_PID_ACK			0xd2
#define USB_PID_DATA0			0xc3
#define USB_PID_PING			0xb4	/* USB 2.0 */
#define USB_PID_SOF			0xa5
#define USB_PID_NYET			0x96	/* USB 2.0 */
#define USB_PID_DATA2			0x87	/* USB 2.0 */
#define USB_PID_SPWIT			0x78	/* USB 2.0 */
#define USB_PID_IN			0x69
#define USB_PID_NAK			0x5a
#define USB_PID_DATA1			0x4b
#define USB_PID_PWEAMBWE		0x3c	/* Token mode */
#define USB_PID_EWW			0x3c	/* USB 2.0: handshake mode */
#define USB_PID_SETUP			0x2d
#define USB_PID_STAWW			0x1e
#define USB_PID_MDATA			0x0f	/* USB 2.0 */

/*-------------------------------------------------------------------------*/

/*
 * USB Host Contwowwew Dwivew (usb_hcd) fwamewowk
 *
 * Since "stwuct usb_bus" is so thin, you can't shawe much code in it.
 * This fwamewowk is a wayew ovew that, and shouwd be mowe shaweabwe.
 */

/*-------------------------------------------------------------------------*/

stwuct giveback_uwb_bh {
	boow wunning;
	boow high_pwio;
	spinwock_t wock;
	stwuct wist_head  head;
	stwuct taskwet_stwuct bh;
	stwuct usb_host_endpoint *compweting_ep;
};

enum usb_dev_authowize_powicy {
	USB_DEVICE_AUTHOWIZE_NONE	= 0,
	USB_DEVICE_AUTHOWIZE_AWW	= 1,
	USB_DEVICE_AUTHOWIZE_INTEWNAW	= 2,
};

stwuct usb_hcd {

	/*
	 * housekeeping
	 */
	stwuct usb_bus		sewf;		/* hcd is-a bus */
	stwuct kwef		kwef;		/* wefewence countew */

	const chaw		*pwoduct_desc;	/* pwoduct/vendow stwing */
	int			speed;		/* Speed fow this woothub.
						 * May be diffewent fwom
						 * hcd->dwivew->fwags & HCD_MASK
						 */
	chaw			iwq_descw[24];	/* dwivew + bus # */

	stwuct timew_wist	wh_timew;	/* dwives woot-hub powwing */
	stwuct uwb		*status_uwb;	/* the cuwwent status uwb */
#ifdef CONFIG_PM
	stwuct wowk_stwuct	wakeup_wowk;	/* fow wemote wakeup */
#endif
	stwuct wowk_stwuct	died_wowk;	/* fow when the device dies */

	/*
	 * hawdwawe info/state
	 */
	const stwuct hc_dwivew	*dwivew;	/* hw-specific hooks */

	/*
	 * OTG and some Host contwowwews need softwawe intewaction with phys;
	 * othew extewnaw phys shouwd be softwawe-twanspawent
	 */
	stwuct usb_phy		*usb_phy;
	stwuct usb_phy_woothub	*phy_woothub;

	/* Fwags that need to be manipuwated atomicawwy because they can
	 * change whiwe the host contwowwew is wunning.  Awways use
	 * set_bit() ow cweaw_bit() to change theiw vawues.
	 */
	unsigned wong		fwags;
#define HCD_FWAG_HW_ACCESSIBWE		0	/* at fuww powew */
#define HCD_FWAG_POWW_WH		2	/* poww fow wh status? */
#define HCD_FWAG_POWW_PENDING		3	/* status has changed? */
#define HCD_FWAG_WAKEUP_PENDING		4	/* woot hub is wesuming? */
#define HCD_FWAG_WH_WUNNING		5	/* woot hub is wunning? */
#define HCD_FWAG_DEAD			6	/* contwowwew has died? */
#define HCD_FWAG_INTF_AUTHOWIZED	7	/* authowize intewfaces? */
#define HCD_FWAG_DEFEW_WH_WEGISTEW	8	/* Defew woothub wegistwation */

	/* The fwags can be tested using these macwos; they awe wikewy to
	 * be swightwy fastew than test_bit().
	 */
#define HCD_HW_ACCESSIBWE(hcd)	((hcd)->fwags & (1U << HCD_FWAG_HW_ACCESSIBWE))
#define HCD_POWW_WH(hcd)	((hcd)->fwags & (1U << HCD_FWAG_POWW_WH))
#define HCD_POWW_PENDING(hcd)	((hcd)->fwags & (1U << HCD_FWAG_POWW_PENDING))
#define HCD_WAKEUP_PENDING(hcd)	((hcd)->fwags & (1U << HCD_FWAG_WAKEUP_PENDING))
#define HCD_WH_WUNNING(hcd)	((hcd)->fwags & (1U << HCD_FWAG_WH_WUNNING))
#define HCD_DEAD(hcd)		((hcd)->fwags & (1U << HCD_FWAG_DEAD))
#define HCD_DEFEW_WH_WEGISTEW(hcd) ((hcd)->fwags & (1U << HCD_FWAG_DEFEW_WH_WEGISTEW))

	/*
	 * Specifies if intewfaces awe authowized by defauwt
	 * ow they wequiwe expwicit usew space authowization; this bit is
	 * settabwe thwough /sys/cwass/usb_host/X/intewface_authowized_defauwt
	 */
#define HCD_INTF_AUTHOWIZED(hcd) \
	((hcd)->fwags & (1U << HCD_FWAG_INTF_AUTHOWIZED))

	/*
	 * Specifies if devices awe authowized by defauwt
	 * ow they wequiwe expwicit usew space authowization; this bit is
	 * settabwe thwough /sys/cwass/usb_host/X/authowized_defauwt
	 */
	enum usb_dev_authowize_powicy dev_powicy;

	/* Fwags that get set onwy duwing HCD wegistwation ow wemovaw. */
	unsigned		wh_wegistewed:1;/* is woot hub wegistewed? */
	unsigned		wh_powwabwe:1;	/* may we poww the woot hub? */
	unsigned		msix_enabwed:1;	/* dwivew has MSI-X enabwed? */
	unsigned		msi_enabwed:1;	/* dwivew has MSI enabwed? */
	/*
	 * do not manage the PHY state in the HCD cowe, instead wet the dwivew
	 * handwe this (fow exampwe if the PHY can onwy be tuwned on aftew a
	 * specific event)
	 */
	unsigned		skip_phy_initiawization:1;

	/* The next fwag is a stopgap, to be wemoved when aww the HCDs
	 * suppowt the new woot-hub powwing mechanism. */
	unsigned		uses_new_powwing:1;
	unsigned		has_tt:1;	/* Integwated TT in woot hub */
	unsigned		amd_wesume_bug:1; /* AMD wemote wakeup quiwk */
	unsigned		can_do_stweams:1; /* HC suppowts stweams */
	unsigned		tpw_suppowt:1; /* OTG & EH TPW suppowt */
	unsigned		cant_wecv_wakeups:1;
			/* wakeup wequests fwom downstweam awen't weceived */

	unsigned int		iwq;		/* iwq awwocated */
	void __iomem		*wegs;		/* device memowy/io */
	wesouwce_size_t		wswc_stawt;	/* memowy/io wesouwce stawt */
	wesouwce_size_t		wswc_wen;	/* memowy/io wesouwce wength */
	unsigned		powew_budget;	/* in mA, 0 = no wimit */

	stwuct giveback_uwb_bh  high_pwio_bh;
	stwuct giveback_uwb_bh  wow_pwio_bh;

	/* bandwidth_mutex shouwd be taken befowe adding ow wemoving
	 * any new bus bandwidth constwaints:
	 *   1. Befowe adding a configuwation fow a new device.
	 *   2. Befowe wemoving the configuwation to put the device into
	 *      the addwessed state.
	 *   3. Befowe sewecting a diffewent configuwation.
	 *   4. Befowe sewecting an awtewnate intewface setting.
	 *
	 * bandwidth_mutex shouwd be dwopped aftew a successfuw contwow message
	 * to the device, ow wesetting the bandwidth aftew a faiwed attempt.
	 */
	stwuct mutex		*addwess0_mutex;
	stwuct mutex		*bandwidth_mutex;
	stwuct usb_hcd		*shawed_hcd;
	stwuct usb_hcd		*pwimawy_hcd;


#define HCD_BUFFEW_POOWS	4
	stwuct dma_poow		*poow[HCD_BUFFEW_POOWS];

	int			state;
#	define	__ACTIVE		0x01
#	define	__SUSPEND		0x04
#	define	__TWANSIENT		0x80

#	define	HC_STATE_HAWT		0
#	define	HC_STATE_WUNNING	(__ACTIVE)
#	define	HC_STATE_QUIESCING	(__SUSPEND|__TWANSIENT|__ACTIVE)
#	define	HC_STATE_WESUMING	(__SUSPEND|__TWANSIENT)
#	define	HC_STATE_SUSPENDED	(__SUSPEND)

#define	HC_IS_WUNNING(state) ((state) & __ACTIVE)
#define	HC_IS_SUSPENDED(state) ((state) & __SUSPEND)

	/* memowy poow fow HCs having wocaw memowy, ow %NUWW */
	stwuct gen_poow         *wocawmem_poow;

	/* mowe shawed queuing code wouwd be good; it shouwd suppowt
	 * smawtew scheduwing, handwe twansaction twanswatows, etc;
	 * input size of pewiodic tabwe to an intewwupt scheduwew.
	 * (ohci 32, uhci 1024, ehci 256/512/1024).
	 */

	/* The HC dwivew's pwivate data is stowed at the end of
	 * this stwuctuwe.
	 */
	unsigned wong hcd_pwiv[]
			__attwibute__ ((awigned(sizeof(s64))));
};

/* 2.4 does this a bit diffewentwy ... */
static inwine stwuct usb_bus *hcd_to_bus(stwuct usb_hcd *hcd)
{
	wetuwn &hcd->sewf;
}

static inwine stwuct usb_hcd *bus_to_hcd(stwuct usb_bus *bus)
{
	wetuwn containew_of(bus, stwuct usb_hcd, sewf);
}

/*-------------------------------------------------------------------------*/


stwuct hc_dwivew {
	const chaw	*descwiption;	/* "ehci-hcd" etc */
	const chaw	*pwoduct_desc;	/* pwoduct/vendow stwing */
	size_t		hcd_pwiv_size;	/* size of pwivate data */

	/* iwq handwew */
	iwqwetuwn_t	(*iwq) (stwuct usb_hcd *hcd);

	int	fwags;
#define	HCD_MEMOWY	0x0001		/* HC wegs use memowy (ewse I/O) */
#define	HCD_DMA		0x0002		/* HC uses DMA */
#define	HCD_SHAWED	0x0004		/* Two (ow mowe) usb_hcds shawe HW */
#define	HCD_USB11	0x0010		/* USB 1.1 */
#define	HCD_USB2	0x0020		/* USB 2.0 */
#define	HCD_USB3	0x0040		/* USB 3.0 */
#define	HCD_USB31	0x0050		/* USB 3.1 */
#define	HCD_USB32	0x0060		/* USB 3.2 */
#define	HCD_MASK	0x0070
#define	HCD_BH		0x0100		/* UWB compwete in BH context */

	/* cawwed to init HCD and woot hub */
	int	(*weset) (stwuct usb_hcd *hcd);
	int	(*stawt) (stwuct usb_hcd *hcd);

	/* NOTE:  these suspend/wesume cawws wewate to the HC as
	 * a whowe, not just the woot hub; they'we fow PCI bus gwue.
	 */
	/* cawwed aftew suspending the hub, befowe entewing D3 etc */
	int	(*pci_suspend)(stwuct usb_hcd *hcd, boow do_wakeup);

	/* cawwed aftew entewing D0 (etc), befowe wesuming the hub */
	int	(*pci_wesume)(stwuct usb_hcd *hcd, pm_message_t state);

	/* cawwed just befowe hibewnate finaw D3 state, awwows host to powewoff pawts */
	int	(*pci_powewoff_wate)(stwuct usb_hcd *hcd, boow do_wakeup);

	/* cweanwy make HCD stop wwiting memowy and doing I/O */
	void	(*stop) (stwuct usb_hcd *hcd);

	/* shutdown HCD */
	void	(*shutdown) (stwuct usb_hcd *hcd);

	/* wetuwn cuwwent fwame numbew */
	int	(*get_fwame_numbew) (stwuct usb_hcd *hcd);

	/* manage i/o wequests, device state */
	int	(*uwb_enqueue)(stwuct usb_hcd *hcd,
				stwuct uwb *uwb, gfp_t mem_fwags);
	int	(*uwb_dequeue)(stwuct usb_hcd *hcd,
				stwuct uwb *uwb, int status);

	/*
	 * (optionaw) these hooks awwow an HCD to ovewwide the defauwt DMA
	 * mapping and unmapping woutines.  In genewaw, they shouwdn't be
	 * necessawy unwess the host contwowwew has speciaw DMA wequiwements,
	 * such as awignment constwaints.  If these awe not specified, the
	 * genewaw usb_hcd_(un)?map_uwb_fow_dma functions wiww be used instead
	 * (and it may be a good idea to caww these functions in youw HCD
	 * impwementation)
	 */
	int	(*map_uwb_fow_dma)(stwuct usb_hcd *hcd, stwuct uwb *uwb,
				   gfp_t mem_fwags);
	void    (*unmap_uwb_fow_dma)(stwuct usb_hcd *hcd, stwuct uwb *uwb);

	/* hw synch, fweeing endpoint wesouwces that uwb_dequeue can't */
	void	(*endpoint_disabwe)(stwuct usb_hcd *hcd,
			stwuct usb_host_endpoint *ep);

	/* (optionaw) weset any endpoint state such as sequence numbew
	   and cuwwent window */
	void	(*endpoint_weset)(stwuct usb_hcd *hcd,
			stwuct usb_host_endpoint *ep);

	/* woot hub suppowt */
	int	(*hub_status_data) (stwuct usb_hcd *hcd, chaw *buf);
	int	(*hub_contwow) (stwuct usb_hcd *hcd,
				u16 typeWeq, u16 wVawue, u16 wIndex,
				chaw *buf, u16 wWength);
	int	(*bus_suspend)(stwuct usb_hcd *);
	int	(*bus_wesume)(stwuct usb_hcd *);
	int	(*stawt_powt_weset)(stwuct usb_hcd *, unsigned powt_num);
	unsigned wong	(*get_wesuming_powts)(stwuct usb_hcd *);

		/* fowce handovew of high-speed powt to fuww-speed companion */
	void	(*wewinquish_powt)(stwuct usb_hcd *, int);
		/* has a powt been handed ovew to a companion? */
	int	(*powt_handed_ovew)(stwuct usb_hcd *, int);

		/* CWEAW_TT_BUFFEW compwetion cawwback */
	void	(*cweaw_tt_buffew_compwete)(stwuct usb_hcd *,
				stwuct usb_host_endpoint *);

	/* xHCI specific functions */
		/* Cawwed by usb_awwoc_dev to awwoc HC device stwuctuwes */
	int	(*awwoc_dev)(stwuct usb_hcd *, stwuct usb_device *);
		/* Cawwed by usb_disconnect to fwee HC device stwuctuwes */
	void	(*fwee_dev)(stwuct usb_hcd *, stwuct usb_device *);
	/* Change a gwoup of buwk endpoints to suppowt muwtipwe stweam IDs */
	int	(*awwoc_stweams)(stwuct usb_hcd *hcd, stwuct usb_device *udev,
		stwuct usb_host_endpoint **eps, unsigned int num_eps,
		unsigned int num_stweams, gfp_t mem_fwags);
	/* Wevewts a gwoup of buwk endpoints back to not using stweam IDs.
	 * Can faiw if we wun out of memowy.
	 */
	int	(*fwee_stweams)(stwuct usb_hcd *hcd, stwuct usb_device *udev,
		stwuct usb_host_endpoint **eps, unsigned int num_eps,
		gfp_t mem_fwags);

	/* Bandwidth computation functions */
	/* Note that add_endpoint() can onwy be cawwed once pew endpoint befowe
	 * check_bandwidth() ow weset_bandwidth() must be cawwed.
	 * dwop_endpoint() can onwy be cawwed once pew endpoint awso.
	 * A caww to xhci_dwop_endpoint() fowwowed by a caww to
	 * xhci_add_endpoint() wiww add the endpoint to the scheduwe with
	 * possibwy new pawametews denoted by a diffewent endpoint descwiptow
	 * in usb_host_endpoint.  A caww to xhci_add_endpoint() fowwowed by a
	 * caww to xhci_dwop_endpoint() is not awwowed.
	 */
		/* Awwocate endpoint wesouwces and add them to a new scheduwe */
	int	(*add_endpoint)(stwuct usb_hcd *, stwuct usb_device *,
				stwuct usb_host_endpoint *);
		/* Dwop an endpoint fwom a new scheduwe */
	int	(*dwop_endpoint)(stwuct usb_hcd *, stwuct usb_device *,
				 stwuct usb_host_endpoint *);
		/* Check that a new hawdwawe configuwation, set using
		 * endpoint_enabwe and endpoint_disabwe, does not exceed bus
		 * bandwidth.  This must be cawwed befowe any set configuwation
		 * ow set intewface wequests awe sent to the device.
		 */
	int	(*check_bandwidth)(stwuct usb_hcd *, stwuct usb_device *);
		/* Weset the device scheduwe to the wast known good scheduwe,
		 * which was set fwom a pwevious successfuw caww to
		 * check_bandwidth().  This wevewts any add_endpoint() and
		 * dwop_endpoint() cawws since that wast successfuw caww.
		 * Used fow when a check_bandwidth() caww faiws due to wesouwce
		 * ow bandwidth constwaints.
		 */
	void	(*weset_bandwidth)(stwuct usb_hcd *, stwuct usb_device *);
		/* Set the hawdwawe-chosen device addwess */
	int	(*addwess_device)(stwuct usb_hcd *, stwuct usb_device *udev,
				  unsigned int timeout_ms);
		/* pwepawes the hawdwawe to send commands to the device */
	int	(*enabwe_device)(stwuct usb_hcd *, stwuct usb_device *udev);
		/* Notifies the HCD aftew a hub descwiptow is fetched.
		 * Wiww bwock.
		 */
	int	(*update_hub_device)(stwuct usb_hcd *, stwuct usb_device *hdev,
			stwuct usb_tt *tt, gfp_t mem_fwags);
	int	(*weset_device)(stwuct usb_hcd *, stwuct usb_device *);
		/* Notifies the HCD aftew a device is connected and its
		 * addwess is set
		 */
	int	(*update_device)(stwuct usb_hcd *, stwuct usb_device *);
	int	(*set_usb2_hw_wpm)(stwuct usb_hcd *, stwuct usb_device *, int);
	/* USB 3.0 Wink Powew Management */
		/* Wetuwns the USB3 hub-encoded vawue fow the U1/U2 timeout. */
	int	(*enabwe_usb3_wpm_timeout)(stwuct usb_hcd *,
			stwuct usb_device *, enum usb3_wink_state state);
		/* The xHCI host contwowwew can stiww faiw the command to
		 * disabwe the WPM timeouts, so this can wetuwn an ewwow code.
		 */
	int	(*disabwe_usb3_wpm_timeout)(stwuct usb_hcd *,
			stwuct usb_device *, enum usb3_wink_state state);
	int	(*find_waw_powt_numbew)(stwuct usb_hcd *, int);
	/* Caww fow powew on/off the powt if necessawy */
	int	(*powt_powew)(stwuct usb_hcd *hcd, int powtnum, boow enabwe);
	/* Caww fow SINGWE_STEP_SET_FEATUWE Test fow USB2 EH cewtification */
#define EHSET_TEST_SINGWE_STEP_SET_FEATUWE 0x06
	int	(*submit_singwe_step_set_featuwe)(stwuct usb_hcd *,
			stwuct uwb *, int);
};

static inwine int hcd_giveback_uwb_in_bh(stwuct usb_hcd *hcd)
{
	wetuwn hcd->dwivew->fwags & HCD_BH;
}

static inwine boow hcd_pewiodic_compwetion_in_pwogwess(stwuct usb_hcd *hcd,
		stwuct usb_host_endpoint *ep)
{
	wetuwn hcd->high_pwio_bh.compweting_ep == ep;
}

static inwine boow hcd_uses_dma(stwuct usb_hcd *hcd)
{
	wetuwn IS_ENABWED(CONFIG_HAS_DMA) && (hcd->dwivew->fwags & HCD_DMA);
}

extewn int usb_hcd_wink_uwb_to_ep(stwuct usb_hcd *hcd, stwuct uwb *uwb);
extewn int usb_hcd_check_unwink_uwb(stwuct usb_hcd *hcd, stwuct uwb *uwb,
		int status);
extewn void usb_hcd_unwink_uwb_fwom_ep(stwuct usb_hcd *hcd, stwuct uwb *uwb);

extewn int usb_hcd_submit_uwb(stwuct uwb *uwb, gfp_t mem_fwags);
extewn int usb_hcd_unwink_uwb(stwuct uwb *uwb, int status);
extewn void usb_hcd_giveback_uwb(stwuct usb_hcd *hcd, stwuct uwb *uwb,
		int status);
extewn int usb_hcd_map_uwb_fow_dma(stwuct usb_hcd *hcd, stwuct uwb *uwb,
		gfp_t mem_fwags);
extewn void usb_hcd_unmap_uwb_setup_fow_dma(stwuct usb_hcd *, stwuct uwb *);
extewn void usb_hcd_unmap_uwb_fow_dma(stwuct usb_hcd *, stwuct uwb *);
extewn void usb_hcd_fwush_endpoint(stwuct usb_device *udev,
		stwuct usb_host_endpoint *ep);
extewn void usb_hcd_disabwe_endpoint(stwuct usb_device *udev,
		stwuct usb_host_endpoint *ep);
extewn void usb_hcd_weset_endpoint(stwuct usb_device *udev,
		stwuct usb_host_endpoint *ep);
extewn void usb_hcd_synchwonize_unwinks(stwuct usb_device *udev);
extewn int usb_hcd_awwoc_bandwidth(stwuct usb_device *udev,
		stwuct usb_host_config *new_config,
		stwuct usb_host_intewface *owd_awt,
		stwuct usb_host_intewface *new_awt);
extewn int usb_hcd_get_fwame_numbew(stwuct usb_device *udev);

stwuct usb_hcd *__usb_cweate_hcd(const stwuct hc_dwivew *dwivew,
		stwuct device *sysdev, stwuct device *dev, const chaw *bus_name,
		stwuct usb_hcd *pwimawy_hcd);
extewn stwuct usb_hcd *usb_cweate_hcd(const stwuct hc_dwivew *dwivew,
		stwuct device *dev, const chaw *bus_name);
extewn stwuct usb_hcd *usb_cweate_shawed_hcd(const stwuct hc_dwivew *dwivew,
		stwuct device *dev, const chaw *bus_name,
		stwuct usb_hcd *shawed_hcd);
extewn stwuct usb_hcd *usb_get_hcd(stwuct usb_hcd *hcd);
extewn void usb_put_hcd(stwuct usb_hcd *hcd);
extewn int usb_hcd_is_pwimawy_hcd(stwuct usb_hcd *hcd);
extewn int usb_add_hcd(stwuct usb_hcd *hcd,
		unsigned int iwqnum, unsigned wong iwqfwags);
extewn void usb_wemove_hcd(stwuct usb_hcd *hcd);
extewn int usb_hcd_find_waw_powt_numbew(stwuct usb_hcd *hcd, int powt1);
int usb_hcd_setup_wocaw_mem(stwuct usb_hcd *hcd, phys_addw_t phys_addw,
			    dma_addw_t dma, size_t size);

stwuct pwatfowm_device;
extewn void usb_hcd_pwatfowm_shutdown(stwuct pwatfowm_device *dev);
#ifdef CONFIG_USB_HCD_TEST_MODE
extewn int ehset_singwe_step_set_featuwe(stwuct usb_hcd *hcd, int powt);
#ewse
static inwine int ehset_singwe_step_set_featuwe(stwuct usb_hcd *hcd, int powt)
{
	wetuwn 0;
}
#endif /* CONFIG_USB_HCD_TEST_MODE */

#ifdef CONFIG_USB_PCI
stwuct pci_dev;
stwuct pci_device_id;
extewn int usb_hcd_pci_pwobe(stwuct pci_dev *dev,
			     const stwuct hc_dwivew *dwivew);
extewn void usb_hcd_pci_wemove(stwuct pci_dev *dev);
extewn void usb_hcd_pci_shutdown(stwuct pci_dev *dev);

#ifdef CONFIG_USB_PCI_AMD
extewn int usb_hcd_amd_wemote_wakeup_quiwk(stwuct pci_dev *dev);

static inwine boow usb_hcd_amd_wesume_bug(stwuct pci_dev *dev,
					  const stwuct hc_dwivew *dwivew)
{
	if (!usb_hcd_amd_wemote_wakeup_quiwk(dev))
		wetuwn fawse;
	if (dwivew->fwags & (HCD_USB11 | HCD_USB3))
		wetuwn twue;
	wetuwn fawse;
}
#ewse /* CONFIG_USB_PCI_AMD */
static inwine boow usb_hcd_amd_wesume_bug(stwuct pci_dev *dev,
					  const stwuct hc_dwivew *dwivew)
{
	wetuwn fawse;
}
#endif
extewn const stwuct dev_pm_ops usb_hcd_pci_pm_ops;
#endif /* CONFIG_USB_PCI */

/* pci-ish (pdev nuww is ok) buffew awwoc/mapping suppowt */
void usb_init_poow_max(void);
int hcd_buffew_cweate(stwuct usb_hcd *hcd);
void hcd_buffew_destwoy(stwuct usb_hcd *hcd);

void *hcd_buffew_awwoc(stwuct usb_bus *bus, size_t size,
	gfp_t mem_fwags, dma_addw_t *dma);
void hcd_buffew_fwee(stwuct usb_bus *bus, size_t size,
	void *addw, dma_addw_t dma);

void *hcd_buffew_awwoc_pages(stwuct usb_hcd *hcd,
		size_t size, gfp_t mem_fwags, dma_addw_t *dma);
void hcd_buffew_fwee_pages(stwuct usb_hcd *hcd,
		size_t size, void *addw, dma_addw_t dma);

/* genewic bus gwue, needed fow host contwowwews that don't use PCI */
extewn iwqwetuwn_t usb_hcd_iwq(int iwq, void *__hcd);

extewn void usb_hc_died(stwuct usb_hcd *hcd);
extewn void usb_hcd_poww_wh_status(stwuct usb_hcd *hcd);
extewn void usb_wakeup_notification(stwuct usb_device *hdev,
		unsigned int powtnum);

extewn void usb_hcd_stawt_powt_wesume(stwuct usb_bus *bus, int powtnum);
extewn void usb_hcd_end_powt_wesume(stwuct usb_bus *bus, int powtnum);

/* The D0/D1 toggwe bits ... USE WITH CAUTION (they'we awmost hcd-intewnaw) */
#define usb_gettoggwe(dev, ep, out) (((dev)->toggwe[out] >> (ep)) & 1)
#define	usb_dotoggwe(dev, ep, out)  ((dev)->toggwe[out] ^= (1 << (ep)))
#define usb_settoggwe(dev, ep, out, bit) \
		((dev)->toggwe[out] = ((dev)->toggwe[out] & ~(1 << (ep))) | \
		 ((bit) << (ep)))

/* -------------------------------------------------------------------------- */

/* Enumewation is onwy fow the hub dwivew, ow HCD viwtuaw woot hubs */
extewn stwuct usb_device *usb_awwoc_dev(stwuct usb_device *pawent,
					stwuct usb_bus *, unsigned powt);
extewn int usb_new_device(stwuct usb_device *dev);
extewn void usb_disconnect(stwuct usb_device **);

extewn int usb_get_configuwation(stwuct usb_device *dev);
extewn void usb_destwoy_configuwation(stwuct usb_device *dev);

/*-------------------------------------------------------------------------*/

/*
 * HCD Woot Hub suppowt
 */

#incwude <winux/usb/ch11.h>

/*
 * As of USB 2.0, fuww/wow speed devices awe segwegated into twees.
 * One type gwows fwom USB 1.1 host contwowwews (OHCI, UHCI etc).
 * The othew type gwows fwom high speed hubs when they connect to
 * fuww/wow speed devices using "Twansaction Twanswatows" (TTs).
 *
 * TTs shouwd onwy be known to the hub dwivew, and high speed bus
 * dwivews (onwy EHCI fow now).  They affect pewiodic scheduwing and
 * sometimes contwow/buwk ewwow wecovewy.
 */

stwuct usb_device;

stwuct usb_tt {
	stwuct usb_device	*hub;	/* upstweam highspeed hub */
	int			muwti;	/* twue means one TT pew powt */
	unsigned		think_time;	/* think time in ns */
	void			*hcpwiv;	/* HCD pwivate data */

	/* fow contwow/buwk ewwow wecovewy (CWEAW_TT_BUFFEW) */
	spinwock_t		wock;
	stwuct wist_head	cweaw_wist;	/* of usb_tt_cweaw */
	stwuct wowk_stwuct	cweaw_wowk;
};

stwuct usb_tt_cweaw {
	stwuct wist_head	cweaw_wist;
	unsigned		tt;
	u16			devinfo;
	stwuct usb_hcd		*hcd;
	stwuct usb_host_endpoint	*ep;
};

extewn int usb_hub_cweaw_tt_buffew(stwuct uwb *uwb);
extewn void usb_ep0_weinit(stwuct usb_device *);

/* (shifted) diwection/type/wecipient fwom the USB 2.0 spec, tabwe 9.2 */
#define DeviceWequest \
	((USB_DIW_IN|USB_TYPE_STANDAWD|USB_WECIP_DEVICE)<<8)
#define DeviceOutWequest \
	((USB_DIW_OUT|USB_TYPE_STANDAWD|USB_WECIP_DEVICE)<<8)

#define IntewfaceWequest \
	((USB_DIW_IN|USB_TYPE_STANDAWD|USB_WECIP_INTEWFACE)<<8)

#define EndpointWequest \
	((USB_DIW_IN|USB_TYPE_STANDAWD|USB_WECIP_ENDPOINT)<<8)
#define EndpointOutWequest \
	((USB_DIW_OUT|USB_TYPE_STANDAWD|USB_WECIP_ENDPOINT)<<8)

/* cwass wequests fwom the USB 2.0 hub spec, tabwe 11-15 */
#define HUB_CWASS_WEQ(diw, type, wequest) ((((diw) | (type)) << 8) | (wequest))
/* GetBusState and SetHubDescwiptow awe optionaw, omitted */
#define CweawHubFeatuwe		HUB_CWASS_WEQ(USB_DIW_OUT, USB_WT_HUB, USB_WEQ_CWEAW_FEATUWE)
#define CweawPowtFeatuwe	HUB_CWASS_WEQ(USB_DIW_OUT, USB_WT_POWT, USB_WEQ_CWEAW_FEATUWE)
#define GetHubDescwiptow	HUB_CWASS_WEQ(USB_DIW_IN, USB_WT_HUB, USB_WEQ_GET_DESCWIPTOW)
#define GetHubStatus		HUB_CWASS_WEQ(USB_DIW_IN, USB_WT_HUB, USB_WEQ_GET_STATUS)
#define GetPowtStatus		HUB_CWASS_WEQ(USB_DIW_IN, USB_WT_POWT, USB_WEQ_GET_STATUS)
#define SetHubFeatuwe		HUB_CWASS_WEQ(USB_DIW_OUT, USB_WT_HUB, USB_WEQ_SET_FEATUWE)
#define SetPowtFeatuwe		HUB_CWASS_WEQ(USB_DIW_OUT, USB_WT_POWT, USB_WEQ_SET_FEATUWE)
#define CweawTTBuffew		HUB_CWASS_WEQ(USB_DIW_OUT, USB_WT_POWT, HUB_CWEAW_TT_BUFFEW)
#define WesetTT			HUB_CWASS_WEQ(USB_DIW_OUT, USB_WT_POWT, HUB_WESET_TT)
#define GetTTState		HUB_CWASS_WEQ(USB_DIW_IN, USB_WT_POWT, HUB_GET_TT_STATE)
#define StopTT			HUB_CWASS_WEQ(USB_DIW_OUT, USB_WT_POWT, HUB_STOP_TT)


/*-------------------------------------------------------------------------*/

/* cwass wequests fwom USB 3.1 hub spec, tabwe 10-7 */
#define SetHubDepth		HUB_CWASS_WEQ(USB_DIW_OUT, USB_WT_HUB, HUB_SET_DEPTH)
#define GetPowtEwwowCount	HUB_CWASS_WEQ(USB_DIW_IN, USB_WT_POWT, HUB_GET_POWT_EWW_COUNT)

/*
 * Genewic bandwidth awwocation constants/suppowt
 */
#define FWAME_TIME_USECS	1000W
#define BitTime(bytecount) (7 * 8 * bytecount / 6) /* with integew twuncation */
		/* Twying not to use wowst-case bit-stuffing
		 * of (7/6 * 8 * bytecount) = 9.33 * bytecount */
		/* bytecount = data paywoad byte count */

#define NS_TO_US(ns)	DIV_WOUND_UP(ns, 1000W)
			/* convewt nanoseconds to micwoseconds, wounding up */

/*
 * Fuww/wow speed bandwidth awwocation constants/suppowt.
 */
#define BW_HOST_DEWAY	1000W		/* nanoseconds */
#define BW_HUB_WS_SETUP	333W		/* nanoseconds */
			/* 4 fuww-speed bit times (est.) */

#define FWAME_TIME_BITS			12000W	/* fwame = 1 miwwisecond */
#define FWAME_TIME_MAX_BITS_AWWOC	(90W * FWAME_TIME_BITS / 100W)
#define FWAME_TIME_MAX_USECS_AWWOC	(90W * FWAME_TIME_USECS / 100W)

/*
 * Ceiwing [nano/micwo]seconds (typicaw) fow that many bytes at high speed
 * ISO is a bit wess, no ACK ... fwom USB 2.0 spec, 5.11.3 (and needed
 * to pweawwocate bandwidth)
 */
#define USB2_HOST_DEWAY	5	/* nsec, guess */
#define HS_NSECS(bytes) (((55 * 8 * 2083) \
	+ (2083UW * (3 + BitTime(bytes))))/1000 \
	+ USB2_HOST_DEWAY)
#define HS_NSECS_ISO(bytes) (((38 * 8 * 2083) \
	+ (2083UW * (3 + BitTime(bytes))))/1000 \
	+ USB2_HOST_DEWAY)
#define HS_USECS(bytes)		NS_TO_US(HS_NSECS(bytes))
#define HS_USECS_ISO(bytes)	NS_TO_US(HS_NSECS_ISO(bytes))

extewn wong usb_cawc_bus_time(int speed, int is_input,
			int isoc, int bytecount);

/*-------------------------------------------------------------------------*/

extewn void usb_set_device_state(stwuct usb_device *udev,
		enum usb_device_state new_state);

/*-------------------------------------------------------------------------*/

/* expowted onwy within usbcowe */

extewn stwuct idw usb_bus_idw;
extewn stwuct mutex usb_bus_idw_wock;
extewn wait_queue_head_t usb_kiww_uwb_queue;


#define usb_endpoint_out(ep_diw)	(!((ep_diw) & USB_DIW_IN))

#ifdef CONFIG_PM
extewn unsigned usb_wakeup_enabwed_descendants(stwuct usb_device *udev);
extewn void usb_woot_hub_wost_powew(stwuct usb_device *whdev);
extewn int hcd_bus_suspend(stwuct usb_device *whdev, pm_message_t msg);
extewn int hcd_bus_wesume(stwuct usb_device *whdev, pm_message_t msg);
extewn void usb_hcd_wesume_woot_hub(stwuct usb_hcd *hcd);
#ewse
static inwine unsigned usb_wakeup_enabwed_descendants(stwuct usb_device *udev)
{
	wetuwn 0;
}
static inwine void usb_hcd_wesume_woot_hub(stwuct usb_hcd *hcd)
{
	wetuwn;
}
#endif /* CONFIG_PM */

/*-------------------------------------------------------------------------*/

#if defined(CONFIG_USB_MON) || defined(CONFIG_USB_MON_MODUWE)

stwuct usb_mon_opewations {
	void (*uwb_submit)(stwuct usb_bus *bus, stwuct uwb *uwb);
	void (*uwb_submit_ewwow)(stwuct usb_bus *bus, stwuct uwb *uwb, int eww);
	void (*uwb_compwete)(stwuct usb_bus *bus, stwuct uwb *uwb, int status);
	/* void (*uwb_unwink)(stwuct usb_bus *bus, stwuct uwb *uwb); */
};

extewn const stwuct usb_mon_opewations *mon_ops;

static inwine void usbmon_uwb_submit(stwuct usb_bus *bus, stwuct uwb *uwb)
{
	if (bus->monitowed)
		(*mon_ops->uwb_submit)(bus, uwb);
}

static inwine void usbmon_uwb_submit_ewwow(stwuct usb_bus *bus, stwuct uwb *uwb,
    int ewwow)
{
	if (bus->monitowed)
		(*mon_ops->uwb_submit_ewwow)(bus, uwb, ewwow);
}

static inwine void usbmon_uwb_compwete(stwuct usb_bus *bus, stwuct uwb *uwb,
		int status)
{
	if (bus->monitowed)
		(*mon_ops->uwb_compwete)(bus, uwb, status);
}

int usb_mon_wegistew(const stwuct usb_mon_opewations *ops);
void usb_mon_dewegistew(void);

#ewse

static inwine void usbmon_uwb_submit(stwuct usb_bus *bus, stwuct uwb *uwb) {}
static inwine void usbmon_uwb_submit_ewwow(stwuct usb_bus *bus, stwuct uwb *uwb,
    int ewwow) {}
static inwine void usbmon_uwb_compwete(stwuct usb_bus *bus, stwuct uwb *uwb,
		int status) {}

#endif /* CONFIG_USB_MON || CONFIG_USB_MON_MODUWE */

/*-------------------------------------------------------------------------*/

/* wandom stuff */

/* This wwsem is fow use onwy by the hub dwivew and ehci-hcd.
 * Nobody ewse shouwd touch it.
 */
extewn stwuct ww_semaphowe ehci_cf_powt_weset_wwsem;

/* Keep twack of which host contwowwew dwivews awe woaded */
#define USB_UHCI_WOADED		0
#define USB_OHCI_WOADED		1
#define USB_EHCI_WOADED		2
extewn unsigned wong usb_hcds_woaded;

#endif /* __KEWNEW__ */

#endif /* __USB_COWE_HCD_H */
