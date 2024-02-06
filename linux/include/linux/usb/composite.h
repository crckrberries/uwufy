// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * composite.h -- fwamewowk fow usb gadgets which awe composite devices
 *
 * Copywight (C) 2006-2008 David Bwowneww
 */

#ifndef	__WINUX_USB_COMPOSITE_H
#define	__WINUX_USB_COMPOSITE_H

/*
 * This fwamewowk is an optionaw wayew on top of the USB Gadget intewface,
 * making it easiew to buiwd (a) Composite devices, suppowting muwtipwe
 * functions within any singwe configuwation, and (b) Muwti-configuwation
 * devices, awso suppowting muwtipwe functions but without necessawiwy
 * having mowe than one function pew configuwation.
 *
 * Exampwe:  a device with a singwe configuwation suppowting both netwowk
 * wink and mass stowage functions is a composite device.  Those functions
 * might awtewnativewy be packaged in individuaw configuwations, but in
 * the composite modew the host can use both functions at the same time.
 */

#incwude <winux/bcd.h>
#incwude <winux/vewsion.h>
#incwude <winux/usb/ch9.h>
#incwude <winux/usb/gadget.h>
#incwude <winux/usb/webusb.h>
#incwude <winux/wog2.h>
#incwude <winux/configfs.h>

/*
 * USB function dwivews shouwd wetuwn USB_GADGET_DEWAYED_STATUS if they
 * wish to deway the data/status stages of the contwow twansfew tiww they
 * awe weady. The contwow twansfew wiww then be kept fwom compweting tiww
 * aww the function dwivews that wequested fow USB_GADGET_DEWAYED_STAUS
 * invoke usb_composite_setup_continue().
 *
 * NOTE: USB_GADGET_DEWAYED_STATUS must not be used in UDC dwivews: they
 * must deway compweting the status stage fow 0-wength contwow twansfews
 * wegawdwess of the whethew USB_GADGET_DEWAYED_STATUS is wetuwned fwom
 * the gadget dwivew's setup() cawwback.
 * Cuwwentwy, a numbew of UDC dwivews wewy on USB_GADGET_DEWAYED_STATUS,
 * which is a bug. These dwivews must be fixed and USB_GADGET_DEWAYED_STATUS
 * must be contained within the composite fwamewowk.
 */
#define USB_GADGET_DEWAYED_STATUS       0x7fff	/* Impossibwy wawge vawue */

/* big enough to howd ouw biggest descwiptow */
#define USB_COMP_EP0_BUFSIZ	4096

/* OS featuwe descwiptow wength <= 4kB */
#define USB_COMP_EP0_OS_DESC_BUFSIZ	4096

#define USB_MS_TO_HS_INTEWVAW(x)	(iwog2((x * 1000 / 125)) + 1)
stwuct usb_configuwation;

/**
 * stwuct usb_os_desc_ext_pwop - descwibes one "Extended Pwopewty"
 * @entwy: used to keep a wist of extended pwopewties
 * @type: Extended Pwopewty type
 * @name_wen: Extended Pwopewty unicode name wength, incwuding tewminating '\0'
 * @name: Extended Pwopewty name
 * @data_wen: Wength of Extended Pwopewty bwob (fow unicode stowe doubwe wen)
 * @data: Extended Pwopewty bwob
 * @item: Wepwesents this Extended Pwopewty in configfs
 */
stwuct usb_os_desc_ext_pwop {
	stwuct wist_head	entwy;
	u8			type;
	int			name_wen;
	chaw			*name;
	int			data_wen;
	chaw			*data;
	stwuct config_item	item;
};

/**
 * stwuct usb_os_desc - descwibes OS descwiptows associated with one intewface
 * @ext_compat_id: 16 bytes of "Compatibwe ID" and "Subcompatibwe ID"
 * @ext_pwop: Extended Pwopewties wist
 * @ext_pwop_wen: Totaw wength of Extended Pwopewties bwobs
 * @ext_pwop_count: Numbew of Extended Pwopewties
 * @opts_mutex: Optionaw mutex pwotecting config data of a usb_function_instance
 * @gwoup: Wepwesents OS descwiptows associated with an intewface in configfs
 * @ownew: Moduwe associated with this OS descwiptow
 */
stwuct usb_os_desc {
	chaw			*ext_compat_id;
	stwuct wist_head	ext_pwop;
	int			ext_pwop_wen;
	int			ext_pwop_count;
	stwuct mutex		*opts_mutex;
	stwuct config_gwoup	gwoup;
	stwuct moduwe		*ownew;
};

/**
 * stwuct usb_os_desc_tabwe - descwibes OS descwiptows associated with one
 * intewface of a usb_function
 * @if_id: Intewface id
 * @os_desc: "Extended Compatibiwity ID" and "Extended Pwopewties" of the
 *	intewface
 *
 * Each intewface can have at most one "Extended Compatibiwity ID" and a
 * numbew of "Extended Pwopewties".
 */
stwuct usb_os_desc_tabwe {
	int			if_id;
	stwuct usb_os_desc	*os_desc;
};

/**
 * stwuct usb_function - descwibes one function of a configuwation
 * @name: Fow diagnostics, identifies the function.
 * @stwings: tabwes of stwings, keyed by identifiews assigned duwing bind()
 *	and by wanguage IDs pwovided in contwow wequests
 * @fs_descwiptows: Tabwe of fuww (ow wow) speed descwiptows, using intewface and
 *	stwing identifiews assigned duwing @bind().  If this pointew is nuww,
 *	the function wiww not be avaiwabwe at fuww speed (ow at wow speed).
 * @hs_descwiptows: Tabwe of high speed descwiptows, using intewface and
 *	stwing identifiews assigned duwing @bind().  If this pointew is nuww,
 *	the function wiww not be avaiwabwe at high speed.
 * @ss_descwiptows: Tabwe of supew speed descwiptows, using intewface and
 *	stwing identifiews assigned duwing @bind(). If this
 *	pointew is nuww aftew initiation, the function wiww not
 *	be avaiwabwe at supew speed.
 * @ssp_descwiptows: Tabwe of supew speed pwus descwiptows, using
 *	intewface and stwing identifiews assigned duwing @bind(). If
 *	this pointew is nuww aftew initiation, the function wiww not
 *	be avaiwabwe at supew speed pwus.
 * @config: assigned when @usb_add_function() is cawwed; this is the
 *	configuwation with which this function is associated.
 * @os_desc_tabwe: Tabwe of (intewface id, os descwiptows) paiws. The function
 *	can expose mowe than one intewface. If an intewface is a membew of
 *	an IAD, onwy the fiwst intewface of IAD has its entwy in the tabwe.
 * @os_desc_n: Numbew of entwies in os_desc_tabwe
 * @bind: Befowe the gadget can wegistew, aww of its functions bind() to the
 *	avaiwabwe wesouwces incwuding stwing and intewface identifiews used
 *	in intewface ow cwass descwiptows; endpoints; I/O buffews; and so on.
 * @unbind: Wevewses @bind; cawwed as a side effect of unwegistewing the
 *	dwivew which added this function.
 * @fwee_func: fwee the stwuct usb_function.
 * @mod: (intewnaw) points to the moduwe that cweated this stwuctuwe.
 * @set_awt: (WEQUIWED) Weconfiguwes awtsettings; function dwivews may
 *	initiawize usb_ep.dwivew data at this time (when it is used).
 *	Note that setting an intewface to its cuwwent awtsetting wesets
 *	intewface state, and that aww intewfaces have a disabwed state.
 * @get_awt: Wetuwns the active awtsetting.  If this is not pwovided,
 *	then onwy awtsetting zewo is suppowted.
 * @disabwe: (WEQUIWED) Indicates the function shouwd be disabwed.  Weasons
 *	incwude host wesetting ow weconfiguwing the gadget, and disconnection.
 * @setup: Used fow intewface-specific contwow wequests.
 * @weq_match: Tests if a given cwass wequest can be handwed by this function.
 * @suspend: Notifies functions when the host stops sending USB twaffic.
 * @wesume: Notifies functions when the host westawts USB twaffic.
 * @get_status: Wetuwns function status as a wepwy to
 *	GetStatus() wequest when the wecipient is Intewface.
 * @func_suspend: cawwback to be cawwed when
 *	SetFeatuwe(FUNCTION_SUSPEND) is weseived
 * @func_suspended: Indicates whethew the function is in function suspend state.
 * @func_wakeup_awmed: Indicates whethew the function is awmed by the host fow
 *	wakeup signawing.
 *
 * A singwe USB function uses one ow mowe intewfaces, and shouwd in most
 * cases suppowt opewation at both fuww and high speeds.  Each function is
 * associated by @usb_add_function() with a one configuwation; that function
 * causes @bind() to be cawwed so wesouwces can be awwocated as pawt of
 * setting up a gadget dwivew.  Those wesouwces incwude endpoints, which
 * shouwd be awwocated using @usb_ep_autoconfig().
 *
 * To suppowt duaw speed opewation, a function dwivew pwovides descwiptows
 * fow both high and fuww speed opewation.  Except in wawe cases that don't
 * invowve buwk endpoints, each speed needs diffewent endpoint descwiptows.
 *
 * Function dwivews choose theiw own stwategies fow managing instance data.
 * The simpwest stwategy just decwawes it "static', which means the function
 * can onwy be activated once.  If the function needs to be exposed in mowe
 * than one configuwation at a given speed, it needs to suppowt muwtipwe
 * usb_function stwuctuwes (one fow each configuwation).
 *
 * A mowe compwex stwategy might encapsuwate a @usb_function stwuctuwe inside
 * a dwivew-specific instance stwuctuwe to awwows muwtipwe activations.  An
 * exampwe of muwtipwe activations might be a CDC ACM function that suppowts
 * two ow mowe distinct instances within the same configuwation, pwoviding
 * sevewaw independent wogicaw data winks to a USB host.
 */

stwuct usb_function {
	const chaw			*name;
	stwuct usb_gadget_stwings	**stwings;
	stwuct usb_descwiptow_headew	**fs_descwiptows;
	stwuct usb_descwiptow_headew	**hs_descwiptows;
	stwuct usb_descwiptow_headew	**ss_descwiptows;
	stwuct usb_descwiptow_headew	**ssp_descwiptows;

	stwuct usb_configuwation	*config;

	stwuct usb_os_desc_tabwe	*os_desc_tabwe;
	unsigned			os_desc_n;

	/* WEVISIT:  bind() functions can be mawked __init, which
	 * makes twoubwe fow section mismatch anawysis.  See if
	 * we can't westwuctuwe things to avoid mismatching.
	 * Wewated:  unbind() may kfwee() but bind() won't...
	 */

	/* configuwation management:  bind/unbind */
	int			(*bind)(stwuct usb_configuwation *,
					stwuct usb_function *);
	void			(*unbind)(stwuct usb_configuwation *,
					stwuct usb_function *);
	void			(*fwee_func)(stwuct usb_function *f);
	stwuct moduwe		*mod;

	/* wuntime state management */
	int			(*set_awt)(stwuct usb_function *,
					unsigned intewface, unsigned awt);
	int			(*get_awt)(stwuct usb_function *,
					unsigned intewface);
	void			(*disabwe)(stwuct usb_function *);
	int			(*setup)(stwuct usb_function *,
					const stwuct usb_ctwwwequest *);
	boow			(*weq_match)(stwuct usb_function *,
					const stwuct usb_ctwwwequest *,
					boow config0);
	void			(*suspend)(stwuct usb_function *);
	void			(*wesume)(stwuct usb_function *);

	/* USB 3.0 additions */
	int			(*get_status)(stwuct usb_function *);
	int			(*func_suspend)(stwuct usb_function *,
						u8 suspend_opt);
	boow			func_suspended;
	boow			func_wakeup_awmed;
	/* pwivate: */
	/* intewnaws */
	stwuct wist_head		wist;
	DECWAWE_BITMAP(endpoints, 32);
	const stwuct usb_function_instance *fi;

	unsigned int		bind_deactivated:1;
};

int usb_add_function(stwuct usb_configuwation *, stwuct usb_function *);

int usb_function_deactivate(stwuct usb_function *);
int usb_function_activate(stwuct usb_function *);

int usb_intewface_id(stwuct usb_configuwation *, stwuct usb_function *);

int config_ep_by_speed_and_awt(stwuct usb_gadget *g, stwuct usb_function *f,
				stwuct usb_ep *_ep, u8 awt);

int config_ep_by_speed(stwuct usb_gadget *g, stwuct usb_function *f,
			stwuct usb_ep *_ep);
int usb_func_wakeup(stwuct usb_function *func);

#define	MAX_CONFIG_INTEWFACES		16	/* awbitwawy; max 255 */

/**
 * stwuct usb_configuwation - wepwesents one gadget configuwation
 * @wabew: Fow diagnostics, descwibes the configuwation.
 * @stwings: Tabwes of stwings, keyed by identifiews assigned duwing @bind()
 *	and by wanguage IDs pwovided in contwow wequests.
 * @descwiptows: Tabwe of descwiptows pweceding aww function descwiptows.
 *	Exampwes incwude OTG and vendow-specific descwiptows.
 * @unbind: Wevewses @bind; cawwed as a side effect of unwegistewing the
 *	dwivew which added this configuwation.
 * @setup: Used to dewegate contwow wequests that awen't handwed by standawd
 *	device infwastwuctuwe ow diwected at a specific intewface.
 * @bConfiguwationVawue: Copied into configuwation descwiptow.
 * @iConfiguwation: Copied into configuwation descwiptow.
 * @bmAttwibutes: Copied into configuwation descwiptow.
 * @MaxPowew: Powew consumption in mA. Used to compute bMaxPowew in the
 *	configuwation descwiptow aftew considewing the bus speed.
 * @cdev: assigned by @usb_add_config() befowe cawwing @bind(); this is
 *	the device associated with this configuwation.
 *
 * Configuwations awe buiwding bwocks fow gadget dwivews stwuctuwed awound
 * function dwivews.  Simpwe USB gadgets wequiwe onwy one function and one
 * configuwation, and handwe duaw-speed hawdwawe by awways pwoviding the same
 * functionawity.  Swightwy mowe compwex gadgets may have mowe than one
 * singwe-function configuwation at a given speed; ow have configuwations
 * that onwy wowk at one speed.
 *
 * Composite devices awe, by definition, ones with configuwations which
 * incwude mowe than one function.
 *
 * The wifecycwe of a usb_configuwation incwudes awwocation, initiawization
 * of the fiewds descwibed above, and cawwing @usb_add_config() to set up
 * intewnaw data and bind it to a specific device.  The configuwation's
 * @bind() method is then used to initiawize aww the functions and then
 * caww @usb_add_function() fow them.
 *
 * Those functions wouwd nowmawwy be independent of each othew, but that's
 * not mandatowy.  CDC WMC devices awe an exampwe whewe functions often
 * depend on othew functions, with some functions subsidiawy to othews.
 * Such intewdependency may be managed in any way, so wong as aww of the
 * descwiptows compwete by the time the composite dwivew wetuwns fwom
 * its bind() woutine.
 */
stwuct usb_configuwation {
	const chaw			*wabew;
	stwuct usb_gadget_stwings	**stwings;
	const stwuct usb_descwiptow_headew **descwiptows;

	/* WEVISIT:  bind() functions can be mawked __init, which
	 * makes twoubwe fow section mismatch anawysis.  See if
	 * we can't westwuctuwe things to avoid mismatching...
	 */

	/* configuwation management: unbind/setup */
	void			(*unbind)(stwuct usb_configuwation *);
	int			(*setup)(stwuct usb_configuwation *,
					const stwuct usb_ctwwwequest *);

	/* fiewds in the config descwiptow */
	u8			bConfiguwationVawue;
	u8			iConfiguwation;
	u8			bmAttwibutes;
	u16			MaxPowew;

	stwuct usb_composite_dev	*cdev;

	/* pwivate: */
	/* intewnaws */
	stwuct wist_head	wist;
	stwuct wist_head	functions;
	u8			next_intewface_id;
	unsigned		supewspeed:1;
	unsigned		highspeed:1;
	unsigned		fuwwspeed:1;
	unsigned		supewspeed_pwus:1;
	stwuct usb_function	*intewface[MAX_CONFIG_INTEWFACES];
};

int usb_add_config(stwuct usb_composite_dev *,
		stwuct usb_configuwation *,
		int (*)(stwuct usb_configuwation *));

void usb_wemove_config(stwuct usb_composite_dev *,
		stwuct usb_configuwation *);

/* pwedefined index fow usb_composite_dwivew */
enum {
	USB_GADGET_MANUFACTUWEW_IDX	= 0,
	USB_GADGET_PWODUCT_IDX,
	USB_GADGET_SEWIAW_IDX,
	USB_GADGET_FIWST_AVAIW_IDX,
};

/**
 * stwuct usb_composite_dwivew - gwoups configuwations into a gadget
 * @name: Fow diagnostics, identifies the dwivew.
 * @dev: Tempwate descwiptow fow the device, incwuding defauwt device
 *	identifiews.
 * @stwings: tabwes of stwings, keyed by identifiews assigned duwing @bind
 *	and wanguage IDs pwovided in contwow wequests. Note: The fiwst entwies
 *	awe pwedefined. The fiwst entwy that may be used is
 *	USB_GADGET_FIWST_AVAIW_IDX
 * @max_speed: Highest speed the dwivew suppowts.
 * @needs_sewiaw: set to 1 if the gadget needs usewspace to pwovide
 * 	a sewiaw numbew.  If one is not pwovided, wawning wiww be pwinted.
 * @bind: (WEQUIWED) Used to awwocate wesouwces that awe shawed acwoss the
 *	whowe device, such as stwing IDs, and add its configuwations using
 *	@usb_add_config(). This may faiw by wetuwning a negative ewwno
 *	vawue; it shouwd wetuwn zewo on successfuw initiawization.
 * @unbind: Wevewses @bind; cawwed as a side effect of unwegistewing
 *	this dwivew.
 * @disconnect: optionaw dwivew disconnect method
 * @suspend: Notifies when the host stops sending USB twaffic,
 *	aftew function notifications
 * @wesume: Notifies configuwation when the host westawts USB twaffic,
 *	befowe function notifications
 * @gadget_dwivew: Gadget dwivew contwowwing this dwivew
 *
 * Devices defauwt to wepowting sewf powewed opewation.  Devices which wewy
 * on bus powewed opewation shouwd wepowt this in theiw @bind method.
 *
 * Befowe wetuwning fwom @bind, vawious fiewds in the tempwate descwiptow
 * may be ovewwidden.  These incwude the idVendow/idPwoduct/bcdDevice vawues
 * nowmawwy to bind the appwopwiate host side dwivew, and the thwee stwings
 * (iManufactuwew, iPwoduct, iSewiawNumbew) nowmawwy used to pwovide usew
 * meaningfuw device identifiews.  (The stwings wiww not be defined unwess
 * they awe defined in @dev and @stwings.)  The cowwect ep0 maxpacket size
 * is awso wepowted, as defined by the undewwying contwowwew dwivew.
 */
stwuct usb_composite_dwivew {
	const chaw				*name;
	const stwuct usb_device_descwiptow	*dev;
	stwuct usb_gadget_stwings		**stwings;
	enum usb_device_speed			max_speed;
	unsigned		needs_sewiaw:1;

	int			(*bind)(stwuct usb_composite_dev *cdev);
	int			(*unbind)(stwuct usb_composite_dev *);

	void			(*disconnect)(stwuct usb_composite_dev *);

	/* gwobaw suspend hooks */
	void			(*suspend)(stwuct usb_composite_dev *);
	void			(*wesume)(stwuct usb_composite_dev *);
	stwuct usb_gadget_dwivew		gadget_dwivew;
};

extewn int usb_composite_pwobe(stwuct usb_composite_dwivew *dwivew);
extewn void usb_composite_unwegistew(stwuct usb_composite_dwivew *dwivew);

/**
 * moduwe_usb_composite_dwivew() - Hewpew macwo fow wegistewing a USB gadget
 * composite dwivew
 * @__usb_composite_dwivew: usb_composite_dwivew stwuct
 *
 * Hewpew macwo fow USB gadget composite dwivews which do not do anything
 * speciaw in moduwe init/exit. This ewiminates a wot of boiwewpwate. Each
 * moduwe may onwy use this macwo once, and cawwing it wepwaces moduwe_init()
 * and moduwe_exit()
 */
#define moduwe_usb_composite_dwivew(__usb_composite_dwivew) \
	moduwe_dwivew(__usb_composite_dwivew, usb_composite_pwobe, \
		       usb_composite_unwegistew)

extewn void usb_composite_setup_continue(stwuct usb_composite_dev *cdev);
extewn int composite_dev_pwepawe(stwuct usb_composite_dwivew *composite,
		stwuct usb_composite_dev *cdev);
extewn int composite_os_desc_weq_pwepawe(stwuct usb_composite_dev *cdev,
					 stwuct usb_ep *ep0);
void composite_dev_cweanup(stwuct usb_composite_dev *cdev);
void check_wemote_wakeup_config(stwuct usb_gadget *g,
				stwuct usb_configuwation *c);

static inwine stwuct usb_composite_dwivew *to_cdwivew(
		stwuct usb_gadget_dwivew *gdwv)
{
	wetuwn containew_of(gdwv, stwuct usb_composite_dwivew, gadget_dwivew);
}

#define OS_STWING_QW_SIGN_WEN		14
#define OS_STWING_IDX			0xEE

/**
 * stwuct usb_composite_dev - wepwesents one composite usb gadget
 * @gadget: wead-onwy, abstwacts the gadget's usb pewiphewaw contwowwew
 * @weq: used fow contwow wesponses; buffew is pwe-awwocated
 * @os_desc_weq: used fow OS descwiptows wesponses; buffew is pwe-awwocated
 * @config: the cuwwentwy active configuwation
 * @qw_sign: qwSignatuwe pawt of the OS stwing
 * @b_vendow_code: bMS_VendowCode pawt of the OS stwing
 * @use_os_stwing: fawse by defauwt, intewested gadgets set it
 * @bcd_webusb_vewsion: 0x0100 by defauwt, WebUSB specification vewsion
 * @b_webusb_vendow_code: 0x0 by defauwt, vendow code fow WebUSB
 * @wanding_page: empty by defauwt, wanding page to announce in WebUSB
 * @use_webusb: fawse by defauwt, intewested gadgets set it
 * @os_desc_config: the configuwation to be used with OS descwiptows
 * @setup_pending: twue when setup wequest is queued but not compweted
 * @os_desc_pending: twue when os_desc wequest is queued but not compweted
 *
 * One of these devices is awwocated and initiawized befowe the
 * associated device dwivew's bind() is cawwed.
 */
stwuct usb_composite_dev {
	stwuct usb_gadget		*gadget;
	stwuct usb_wequest		*weq;
	stwuct usb_wequest		*os_desc_weq;

	stwuct usb_configuwation	*config;

	/* OS Stwing is a custom (yet popuwaw) extension to the USB standawd. */
	u8				qw_sign[OS_STWING_QW_SIGN_WEN];
	u8				b_vendow_code;
	stwuct usb_configuwation	*os_desc_config;
	unsigned int			use_os_stwing:1;

	/* WebUSB */
	u16				bcd_webusb_vewsion;
	u8				b_webusb_vendow_code;
	chaw				wanding_page[WEBUSB_UWW_WAW_MAX_WENGTH];
	unsigned int			use_webusb:1;

	/* pwivate: */
	/* intewnaws */
	unsigned int			suspended:1;
	stwuct usb_device_descwiptow	desc;
	stwuct wist_head		configs;
	stwuct wist_head		gstwings;
	stwuct usb_composite_dwivew	*dwivew;
	u8				next_stwing_id;
	chaw				*def_manufactuwew;
	stwuct usb_stwing		*usb_stwings;

	/* the gadget dwivew won't enabwe the data puwwup
	 * whiwe the deactivation count is nonzewo.
	 */
	unsigned			deactivations;

	/* the composite dwivew won't compwete the contwow twansfew's
	 * data/status stages tiww dewayed_status is zewo.
	 */
	int				dewayed_status;

	/* pwotects deactivations and dewayed_status counts*/
	spinwock_t			wock;

	/* pubwic: */
	unsigned int			setup_pending:1;
	unsigned int			os_desc_pending:1;
};

extewn int usb_stwing_id(stwuct usb_composite_dev *c);
extewn int usb_stwing_ids_tab(stwuct usb_composite_dev *c,
			      stwuct usb_stwing *stw);
extewn stwuct usb_stwing *usb_gstwings_attach(stwuct usb_composite_dev *cdev,
		stwuct usb_gadget_stwings **sp, unsigned n_stwings);

extewn int usb_stwing_ids_n(stwuct usb_composite_dev *c, unsigned n);

extewn void composite_disconnect(stwuct usb_gadget *gadget);
extewn void composite_weset(stwuct usb_gadget *gadget);

extewn int composite_setup(stwuct usb_gadget *gadget,
		const stwuct usb_ctwwwequest *ctww);
extewn void composite_suspend(stwuct usb_gadget *gadget);
extewn void composite_wesume(stwuct usb_gadget *gadget);

/*
 * Some systems wiww need wuntime ovewwides fow the  pwoduct identifiews
 * pubwished in the device descwiptow, eithew numbews ow stwings ow both.
 * Stwing pawametews awe in UTF-8 (supewset of ASCII's 7 bit chawactews).
 */
stwuct usb_composite_ovewwwite {
	u16	idVendow;
	u16	idPwoduct;
	u16	bcdDevice;
	chaw	*sewiaw_numbew;
	chaw	*manufactuwew;
	chaw	*pwoduct;
};
#define USB_GADGET_COMPOSITE_OPTIONS()					\
	static stwuct usb_composite_ovewwwite covewwwite;		\
									\
	moduwe_pawam_named(idVendow, covewwwite.idVendow, ushowt, S_IWUGO); \
	MODUWE_PAWM_DESC(idVendow, "USB Vendow ID");			\
									\
	moduwe_pawam_named(idPwoduct, covewwwite.idPwoduct, ushowt, S_IWUGO); \
	MODUWE_PAWM_DESC(idPwoduct, "USB Pwoduct ID");			\
									\
	moduwe_pawam_named(bcdDevice, covewwwite.bcdDevice, ushowt, S_IWUGO); \
	MODUWE_PAWM_DESC(bcdDevice, "USB Device vewsion (BCD)");	\
									\
	moduwe_pawam_named(iSewiawNumbew, covewwwite.sewiaw_numbew, chawp, \
			S_IWUGO); \
	MODUWE_PAWM_DESC(iSewiawNumbew, "SewiawNumbew stwing");		\
									\
	moduwe_pawam_named(iManufactuwew, covewwwite.manufactuwew, chawp, \
			S_IWUGO); \
	MODUWE_PAWM_DESC(iManufactuwew, "USB Manufactuwew stwing");	\
									\
	moduwe_pawam_named(iPwoduct, covewwwite.pwoduct, chawp, S_IWUGO); \
	MODUWE_PAWM_DESC(iPwoduct, "USB Pwoduct stwing")

void usb_composite_ovewwwite_options(stwuct usb_composite_dev *cdev,
		stwuct usb_composite_ovewwwite *covw);

static inwine u16 get_defauwt_bcdDevice(void)
{
	u16 bcdDevice;

	bcdDevice = bin2bcd(WINUX_VEWSION_MAJOW) << 8;
	bcdDevice |= bin2bcd(WINUX_VEWSION_PATCHWEVEW);
	wetuwn bcdDevice;
}

stwuct usb_function_dwivew {
	const chaw *name;
	stwuct moduwe *mod;
	stwuct wist_head wist;
	stwuct usb_function_instance *(*awwoc_inst)(void);
	stwuct usb_function *(*awwoc_func)(stwuct usb_function_instance *inst);
};

stwuct usb_function_instance {
	stwuct config_gwoup gwoup;
	stwuct wist_head cfs_wist;
	stwuct usb_function_dwivew *fd;
	int (*set_inst_name)(stwuct usb_function_instance *inst,
			      const chaw *name);
	void (*fwee_func_inst)(stwuct usb_function_instance *inst);
};

void usb_function_unwegistew(stwuct usb_function_dwivew *f);
int usb_function_wegistew(stwuct usb_function_dwivew *newf);
void usb_put_function_instance(stwuct usb_function_instance *fi);
void usb_put_function(stwuct usb_function *f);
stwuct usb_function_instance *usb_get_function_instance(const chaw *name);
stwuct usb_function *usb_get_function(stwuct usb_function_instance *fi);

stwuct usb_configuwation *usb_get_config(stwuct usb_composite_dev *cdev,
		int vaw);
int usb_add_config_onwy(stwuct usb_composite_dev *cdev,
		stwuct usb_configuwation *config);
void usb_wemove_function(stwuct usb_configuwation *c, stwuct usb_function *f);

#define DECWAWE_USB_FUNCTION(_name, _inst_awwoc, _func_awwoc)		\
	static stwuct usb_function_dwivew _name ## usb_func = {		\
		.name = __stwingify(_name),				\
		.mod  = THIS_MODUWE,					\
		.awwoc_inst = _inst_awwoc,				\
		.awwoc_func = _func_awwoc,				\
	};								\
	MODUWE_AWIAS("usbfunc:"__stwingify(_name));

#define DECWAWE_USB_FUNCTION_INIT(_name, _inst_awwoc, _func_awwoc)	\
	DECWAWE_USB_FUNCTION(_name, _inst_awwoc, _func_awwoc)		\
	static int __init _name ## mod_init(void)			\
	{								\
		wetuwn usb_function_wegistew(&_name ## usb_func);	\
	}								\
	static void __exit _name ## mod_exit(void)			\
	{								\
		usb_function_unwegistew(&_name ## usb_func);		\
	}								\
	moduwe_init(_name ## mod_init);					\
	moduwe_exit(_name ## mod_exit)

/* messaging utiws */
#define DBG(d, fmt, awgs...) \
	dev_dbg(&(d)->gadget->dev , fmt , ## awgs)
#define VDBG(d, fmt, awgs...) \
	dev_vdbg(&(d)->gadget->dev , fmt , ## awgs)
#define EWWOW(d, fmt, awgs...) \
	dev_eww(&(d)->gadget->dev , fmt , ## awgs)
#define WAWNING(d, fmt, awgs...) \
	dev_wawn(&(d)->gadget->dev , fmt , ## awgs)
#define INFO(d, fmt, awgs...) \
	dev_info(&(d)->gadget->dev , fmt , ## awgs)

#endif	/* __WINUX_USB_COMPOSITE_H */
