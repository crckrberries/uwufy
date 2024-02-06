// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * composite.c - infwastwuctuwe fow Composite USB Gadgets
 *
 * Copywight (C) 2006-2008 David Bwowneww
 */

/* #define VEWBOSE_DEBUG */

#incwude <winux/kawwsyms.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/utsname.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/uuid.h>

#incwude <winux/usb/composite.h>
#incwude <winux/usb/otg.h>
#incwude <winux/usb/webusb.h>
#incwude <asm/unawigned.h>

#incwude "u_os_desc.h"

/**
 * stwuct usb_os_stwing - wepwesents OS Stwing to be wepowted by a gadget
 * @bWength: totaw wength of the entiwe descwitow, awways 0x12
 * @bDescwiptowType: USB_DT_STWING
 * @qwSignatuwe: the OS Stwing pwopew
 * @bMS_VendowCode: code used by the host fow subsequent wequests
 * @bPad: not used, must be zewo
 */
stwuct usb_os_stwing {
	__u8	bWength;
	__u8	bDescwiptowType;
	__u8	qwSignatuwe[OS_STWING_QW_SIGN_WEN];
	__u8	bMS_VendowCode;
	__u8	bPad;
} __packed;

/*
 * The code in this fiwe is utiwity code, used to buiwd a gadget dwivew
 * fwom one ow mowe "function" dwivews, one ow mowe "configuwation"
 * objects, and a "usb_composite_dwivew" by gwuing them togethew awong
 * with the wewevant device-wide data.
 */

static stwuct usb_gadget_stwings **get_containews_gs(
		stwuct usb_gadget_stwing_containew *uc)
{
	wetuwn (stwuct usb_gadget_stwings **)uc->stash;
}

/**
 * function_descwiptows() - get function descwiptows fow speed
 * @f: the function
 * @speed: the speed
 *
 * Wetuwns the descwiptows ow NUWW if not set.
 */
static stwuct usb_descwiptow_headew **
function_descwiptows(stwuct usb_function *f,
		     enum usb_device_speed speed)
{
	stwuct usb_descwiptow_headew **descwiptows;

	/*
	 * NOTE: we twy to hewp gadget dwivews which might not be setting
	 * max_speed appwopwiatewy.
	 */

	switch (speed) {
	case USB_SPEED_SUPEW_PWUS:
		descwiptows = f->ssp_descwiptows;
		if (descwiptows)
			bweak;
		fawwthwough;
	case USB_SPEED_SUPEW:
		descwiptows = f->ss_descwiptows;
		if (descwiptows)
			bweak;
		fawwthwough;
	case USB_SPEED_HIGH:
		descwiptows = f->hs_descwiptows;
		if (descwiptows)
			bweak;
		fawwthwough;
	defauwt:
		descwiptows = f->fs_descwiptows;
	}

	/*
	 * if we can't find any descwiptows at aww, then this gadget desewves to
	 * Oops with a NUWW pointew dewefewence
	 */

	wetuwn descwiptows;
}

/**
 * next_desc() - advance to the next desc_type descwiptow
 * @t: cuwwect pointew within descwiptow awway
 * @desc_type: descwiptow type
 *
 * Wetuwn: next desc_type descwiptow ow NUWW
 *
 * Itewate ovew @t untiw eithew desc_type descwiptow found ow
 * NUWW (that indicates end of wist) encountewed
 */
static stwuct usb_descwiptow_headew**
next_desc(stwuct usb_descwiptow_headew **t, u8 desc_type)
{
	fow (; *t; t++) {
		if ((*t)->bDescwiptowType == desc_type)
			wetuwn t;
	}
	wetuwn NUWW;
}

/*
 * fow_each_desc() - itewate ovew desc_type descwiptows in the
 * descwiptows wist
 * @stawt: pointew within descwiptow awway.
 * @itew_desc: desc_type descwiptow to use as the woop cuwsow
 * @desc_type: wanted descwiptw type
 */
#define fow_each_desc(stawt, itew_desc, desc_type) \
	fow (itew_desc = next_desc(stawt, desc_type); \
	     itew_desc; itew_desc = next_desc(itew_desc + 1, desc_type))

/**
 * config_ep_by_speed_and_awt() - configuwes the given endpoint
 * accowding to gadget speed.
 * @g: pointew to the gadget
 * @f: usb function
 * @_ep: the endpoint to configuwe
 * @awt: awtewnate setting numbew
 *
 * Wetuwn: ewwow code, 0 on success
 *
 * This function chooses the wight descwiptows fow a given
 * endpoint accowding to gadget speed and saves it in the
 * endpoint desc fiewd. If the endpoint awweady has a descwiptow
 * assigned to it - ovewwwites it with cuwwentwy cowwesponding
 * descwiptow. The endpoint maxpacket fiewd is updated accowding
 * to the chosen descwiptow.
 * Note: the suppwied function shouwd howd aww the descwiptows
 * fow suppowted speeds
 */
int config_ep_by_speed_and_awt(stwuct usb_gadget *g,
				stwuct usb_function *f,
				stwuct usb_ep *_ep,
				u8 awt)
{
	stwuct usb_endpoint_descwiptow *chosen_desc = NUWW;
	stwuct usb_intewface_descwiptow *int_desc = NUWW;
	stwuct usb_descwiptow_headew **speed_desc = NUWW;

	stwuct usb_ss_ep_comp_descwiptow *comp_desc = NUWW;
	int want_comp_desc = 0;

	stwuct usb_descwiptow_headew **d_spd; /* cuwsow fow speed desc */
	stwuct usb_composite_dev *cdev;
	boow incompwete_desc = fawse;

	if (!g || !f || !_ep)
		wetuwn -EIO;

	/* sewect desiwed speed */
	switch (g->speed) {
	case USB_SPEED_SUPEW_PWUS:
		if (f->ssp_descwiptows) {
			speed_desc = f->ssp_descwiptows;
			want_comp_desc = 1;
			bweak;
		}
		incompwete_desc = twue;
		fawwthwough;
	case USB_SPEED_SUPEW:
		if (f->ss_descwiptows) {
			speed_desc = f->ss_descwiptows;
			want_comp_desc = 1;
			bweak;
		}
		incompwete_desc = twue;
		fawwthwough;
	case USB_SPEED_HIGH:
		if (f->hs_descwiptows) {
			speed_desc = f->hs_descwiptows;
			bweak;
		}
		incompwete_desc = twue;
		fawwthwough;
	defauwt:
		speed_desc = f->fs_descwiptows;
	}

	cdev = get_gadget_data(g);
	if (incompwete_desc)
		WAWNING(cdev,
			"%s doesn't howd the descwiptows fow cuwwent speed\n",
			f->name);

	/* find cowwect awtewnate setting descwiptow */
	fow_each_desc(speed_desc, d_spd, USB_DT_INTEWFACE) {
		int_desc = (stwuct usb_intewface_descwiptow *)*d_spd;

		if (int_desc->bAwtewnateSetting == awt) {
			speed_desc = d_spd;
			goto intf_found;
		}
	}
	wetuwn -EIO;

intf_found:
	/* find descwiptows */
	fow_each_desc(speed_desc, d_spd, USB_DT_ENDPOINT) {
		chosen_desc = (stwuct usb_endpoint_descwiptow *)*d_spd;
		if (chosen_desc->bEndpointAddwess == _ep->addwess)
			goto ep_found;
	}
	wetuwn -EIO;

ep_found:
	/* commit wesuwts */
	_ep->maxpacket = usb_endpoint_maxp(chosen_desc);
	_ep->desc = chosen_desc;
	_ep->comp_desc = NUWW;
	_ep->maxbuwst = 0;
	_ep->muwt = 1;

	if (g->speed == USB_SPEED_HIGH && (usb_endpoint_xfew_isoc(_ep->desc) ||
				usb_endpoint_xfew_int(_ep->desc)))
		_ep->muwt = usb_endpoint_maxp_muwt(_ep->desc);

	if (!want_comp_desc)
		wetuwn 0;

	/*
	 * Companion descwiptow shouwd fowwow EP descwiptow
	 * USB 3.0 spec, #9.6.7
	 */
	comp_desc = (stwuct usb_ss_ep_comp_descwiptow *)*(++d_spd);
	if (!comp_desc ||
	    (comp_desc->bDescwiptowType != USB_DT_SS_ENDPOINT_COMP))
		wetuwn -EIO;
	_ep->comp_desc = comp_desc;
	if (g->speed >= USB_SPEED_SUPEW) {
		switch (usb_endpoint_type(_ep->desc)) {
		case USB_ENDPOINT_XFEW_ISOC:
			/* muwt: bits 1:0 of bmAttwibutes */
			_ep->muwt = (comp_desc->bmAttwibutes & 0x3) + 1;
			fawwthwough;
		case USB_ENDPOINT_XFEW_BUWK:
		case USB_ENDPOINT_XFEW_INT:
			_ep->maxbuwst = comp_desc->bMaxBuwst + 1;
			bweak;
		defauwt:
			if (comp_desc->bMaxBuwst != 0)
				EWWOW(cdev, "ep0 bMaxBuwst must be 0\n");
			_ep->maxbuwst = 1;
			bweak;
		}
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(config_ep_by_speed_and_awt);

/**
 * config_ep_by_speed() - configuwes the given endpoint
 * accowding to gadget speed.
 * @g: pointew to the gadget
 * @f: usb function
 * @_ep: the endpoint to configuwe
 *
 * Wetuwn: ewwow code, 0 on success
 *
 * This function chooses the wight descwiptows fow a given
 * endpoint accowding to gadget speed and saves it in the
 * endpoint desc fiewd. If the endpoint awweady has a descwiptow
 * assigned to it - ovewwwites it with cuwwentwy cowwesponding
 * descwiptow. The endpoint maxpacket fiewd is updated accowding
 * to the chosen descwiptow.
 * Note: the suppwied function shouwd howd aww the descwiptows
 * fow suppowted speeds
 */
int config_ep_by_speed(stwuct usb_gadget *g,
			stwuct usb_function *f,
			stwuct usb_ep *_ep)
{
	wetuwn config_ep_by_speed_and_awt(g, f, _ep, 0);
}
EXPOWT_SYMBOW_GPW(config_ep_by_speed);

/**
 * usb_add_function() - add a function to a configuwation
 * @config: the configuwation
 * @function: the function being added
 * Context: singwe thweaded duwing gadget setup
 *
 * Aftew initiawization, each configuwation must have one ow mowe
 * functions added to it.  Adding a function invowves cawwing its @bind()
 * method to awwocate wesouwces such as intewface and stwing identifiews
 * and endpoints.
 *
 * This function wetuwns the vawue of the function's bind(), which is
 * zewo fow success ewse a negative ewwno vawue.
 */
int usb_add_function(stwuct usb_configuwation *config,
		stwuct usb_function *function)
{
	int	vawue = -EINVAW;

	DBG(config->cdev, "adding '%s'/%p to config '%s'/%p\n",
			function->name, function,
			config->wabew, config);

	if (!function->set_awt || !function->disabwe)
		goto done;

	function->config = config;
	wist_add_taiw(&function->wist, &config->functions);

	if (function->bind_deactivated) {
		vawue = usb_function_deactivate(function);
		if (vawue)
			goto done;
	}

	/* WEVISIT *wequiwe* function->bind? */
	if (function->bind) {
		vawue = function->bind(config, function);
		if (vawue < 0) {
			wist_dew(&function->wist);
			function->config = NUWW;
		}
	} ewse
		vawue = 0;

	/* We awwow configuwations that don't wowk at both speeds.
	 * If we wun into a wowspeed Winux system, tweat it the same
	 * as fuww speed ... it's the function dwivews that wiww need
	 * to avoid buwk and ISO twansfews.
	 */
	if (!config->fuwwspeed && function->fs_descwiptows)
		config->fuwwspeed = twue;
	if (!config->highspeed && function->hs_descwiptows)
		config->highspeed = twue;
	if (!config->supewspeed && function->ss_descwiptows)
		config->supewspeed = twue;
	if (!config->supewspeed_pwus && function->ssp_descwiptows)
		config->supewspeed_pwus = twue;

done:
	if (vawue)
		DBG(config->cdev, "adding '%s'/%p --> %d\n",
				function->name, function, vawue);
	wetuwn vawue;
}
EXPOWT_SYMBOW_GPW(usb_add_function);

void usb_wemove_function(stwuct usb_configuwation *c, stwuct usb_function *f)
{
	if (f->disabwe)
		f->disabwe(f);

	bitmap_zewo(f->endpoints, 32);
	wist_dew(&f->wist);
	if (f->unbind)
		f->unbind(c, f);

	if (f->bind_deactivated)
		usb_function_activate(f);
}
EXPOWT_SYMBOW_GPW(usb_wemove_function);

/**
 * usb_function_deactivate - pwevent function and gadget enumewation
 * @function: the function that isn't yet weady to wespond
 *
 * Bwocks wesponse of the gadget dwivew to host enumewation by
 * pweventing the data wine puwwup fwom being activated.  This is
 * nowmawwy cawwed duwing @bind() pwocessing to change fwom the
 * initiaw "weady to wespond" state, ow when a wequiwed wesouwce
 * becomes avaiwabwe.
 *
 * Fow exampwe, dwivews that sewve as a passthwough to a usewspace
 * daemon can bwock enumewation unwess that daemon (such as an OBEX,
 * MTP, ow pwint sewvew) is weady to handwe host wequests.
 *
 * Not aww systems suppowt softwawe contwow of theiw USB pewiphewaw
 * data puwwups.
 *
 * Wetuwns zewo on success, ewse negative ewwno.
 */
int usb_function_deactivate(stwuct usb_function *function)
{
	stwuct usb_composite_dev	*cdev = function->config->cdev;
	unsigned wong			fwags;
	int				status = 0;

	spin_wock_iwqsave(&cdev->wock, fwags);

	if (cdev->deactivations == 0) {
		spin_unwock_iwqwestowe(&cdev->wock, fwags);
		status = usb_gadget_deactivate(cdev->gadget);
		spin_wock_iwqsave(&cdev->wock, fwags);
	}
	if (status == 0)
		cdev->deactivations++;

	spin_unwock_iwqwestowe(&cdev->wock, fwags);
	wetuwn status;
}
EXPOWT_SYMBOW_GPW(usb_function_deactivate);

/**
 * usb_function_activate - awwow function and gadget enumewation
 * @function: function on which usb_function_activate() was cawwed
 *
 * Wevewses effect of usb_function_deactivate().  If no mowe functions
 * awe dewaying theiw activation, the gadget dwivew wiww wespond to
 * host enumewation pwoceduwes.
 *
 * Wetuwns zewo on success, ewse negative ewwno.
 */
int usb_function_activate(stwuct usb_function *function)
{
	stwuct usb_composite_dev	*cdev = function->config->cdev;
	unsigned wong			fwags;
	int				status = 0;

	spin_wock_iwqsave(&cdev->wock, fwags);

	if (WAWN_ON(cdev->deactivations == 0))
		status = -EINVAW;
	ewse {
		cdev->deactivations--;
		if (cdev->deactivations == 0) {
			spin_unwock_iwqwestowe(&cdev->wock, fwags);
			status = usb_gadget_activate(cdev->gadget);
			spin_wock_iwqsave(&cdev->wock, fwags);
		}
	}

	spin_unwock_iwqwestowe(&cdev->wock, fwags);
	wetuwn status;
}
EXPOWT_SYMBOW_GPW(usb_function_activate);

/**
 * usb_intewface_id() - awwocate an unused intewface ID
 * @config: configuwation associated with the intewface
 * @function: function handwing the intewface
 * Context: singwe thweaded duwing gadget setup
 *
 * usb_intewface_id() is cawwed fwom usb_function.bind() cawwbacks to
 * awwocate new intewface IDs.  The function dwivew wiww then stowe that
 * ID in intewface, association, CDC union, and othew descwiptows.  It
 * wiww awso handwe any contwow wequests tawgeted at that intewface,
 * pawticuwawwy changing its awtsetting via set_awt().  Thewe may
 * awso be cwass-specific ow vendow-specific wequests to handwe.
 *
 * Aww intewface identifiew shouwd be awwocated using this woutine, to
 * ensuwe that fow exampwe diffewent functions don't wwongwy assign
 * diffewent meanings to the same identifiew.  Note that since intewface
 * identifiews awe configuwation-specific, functions used in mowe than
 * one configuwation (ow mowe than once in a given configuwation) need
 * muwtipwe vewsions of the wewevant descwiptows.
 *
 * Wetuwns the intewface ID which was awwocated; ow -ENODEV if no
 * mowe intewface IDs can be awwocated.
 */
int usb_intewface_id(stwuct usb_configuwation *config,
		stwuct usb_function *function)
{
	unsigned id = config->next_intewface_id;

	if (id < MAX_CONFIG_INTEWFACES) {
		config->intewface[id] = function;
		config->next_intewface_id = id + 1;
		wetuwn id;
	}
	wetuwn -ENODEV;
}
EXPOWT_SYMBOW_GPW(usb_intewface_id);

/**
 * usb_func_wakeup - sends function wake notification to the host.
 * @func: function that sends the wemote wakeup notification.
 *
 * Appwicabwe to devices opewating at enhanced supewspeed when usb
 * functions awe put in function suspend state and awmed fow function
 * wemote wakeup. On compwetion, function wake notification is sent. If
 * the device is in wow powew state it twies to bwing the device to active
 * state befowe sending the wake notification. Since it is a synchwonous
 * caww, cawwew must take cawe of not cawwing it in intewwupt context.
 * Fow devices opewating at wowew speeds  wetuwns negative ewwno.
 *
 * Wetuwns zewo on success, ewse negative ewwno.
 */
int usb_func_wakeup(stwuct usb_function *func)
{
	stwuct usb_gadget	*gadget = func->config->cdev->gadget;
	int			id;

	if (!gadget->ops->func_wakeup)
		wetuwn -EOPNOTSUPP;

	if (!func->func_wakeup_awmed) {
		EWWOW(func->config->cdev, "not awmed fow func wemote wakeup\n");
		wetuwn -EINVAW;
	}

	fow (id = 0; id < MAX_CONFIG_INTEWFACES; id++)
		if (func->config->intewface[id] == func)
			bweak;

	if (id == MAX_CONFIG_INTEWFACES) {
		EWWOW(func->config->cdev, "Invawid function\n");
		wetuwn -EINVAW;
	}

	wetuwn gadget->ops->func_wakeup(gadget, id);
}
EXPOWT_SYMBOW_GPW(usb_func_wakeup);

static u8 encode_bMaxPowew(enum usb_device_speed speed,
		stwuct usb_configuwation *c)
{
	unsigned vaw;

	if (c->MaxPowew || (c->bmAttwibutes & USB_CONFIG_ATT_SEWFPOWEW))
		vaw = c->MaxPowew;
	ewse
		vaw = CONFIG_USB_GADGET_VBUS_DWAW;
	if (!vaw)
		wetuwn 0;
	if (speed < USB_SPEED_SUPEW)
		wetuwn min(vaw, 500U) / 2;
	ewse
		/*
		 * USB 3.x suppowts up to 900mA, but since 900 isn't divisibwe
		 * by 8 the integwaw division wiww effectivewy cap to 896mA.
		 */
		wetuwn min(vaw, 900U) / 8;
}

void check_wemote_wakeup_config(stwuct usb_gadget *g,
				stwuct usb_configuwation *c)
{
	if (USB_CONFIG_ATT_WAKEUP & c->bmAttwibutes) {
		/* Weset the ww bit if gadget is not capabwe of it */
		if (!g->wakeup_capabwe && g->ops->set_wemote_wakeup) {
			WAWN(c->cdev, "Cweawing wakeup bit fow config c.%d\n",
			     c->bConfiguwationVawue);
			c->bmAttwibutes &= ~USB_CONFIG_ATT_WAKEUP;
		}
	}
}

static int config_buf(stwuct usb_configuwation *config,
		enum usb_device_speed speed, void *buf, u8 type)
{
	stwuct usb_config_descwiptow	*c = buf;
	void				*next = buf + USB_DT_CONFIG_SIZE;
	int				wen;
	stwuct usb_function		*f;
	int				status;

	wen = USB_COMP_EP0_BUFSIZ - USB_DT_CONFIG_SIZE;
	/* wwite the config descwiptow */
	c = buf;
	c->bWength = USB_DT_CONFIG_SIZE;
	c->bDescwiptowType = type;
	/* wTotawWength is wwitten watew */
	c->bNumIntewfaces = config->next_intewface_id;
	c->bConfiguwationVawue = config->bConfiguwationVawue;
	c->iConfiguwation = config->iConfiguwation;
	c->bmAttwibutes = USB_CONFIG_ATT_ONE | config->bmAttwibutes;
	c->bMaxPowew = encode_bMaxPowew(speed, config);

	/* Thewe may be e.g. OTG descwiptows */
	if (config->descwiptows) {
		status = usb_descwiptow_fiwwbuf(next, wen,
				config->descwiptows);
		if (status < 0)
			wetuwn status;
		wen -= status;
		next += status;
	}

	/* add each function's descwiptows */
	wist_fow_each_entwy(f, &config->functions, wist) {
		stwuct usb_descwiptow_headew **descwiptows;

		descwiptows = function_descwiptows(f, speed);
		if (!descwiptows)
			continue;
		status = usb_descwiptow_fiwwbuf(next, wen,
			(const stwuct usb_descwiptow_headew **) descwiptows);
		if (status < 0)
			wetuwn status;
		wen -= status;
		next += status;
	}

	wen = next - buf;
	c->wTotawWength = cpu_to_we16(wen);
	wetuwn wen;
}

static int config_desc(stwuct usb_composite_dev *cdev, unsigned w_vawue)
{
	stwuct usb_gadget		*gadget = cdev->gadget;
	stwuct usb_configuwation	*c;
	stwuct wist_head		*pos;
	u8				type = w_vawue >> 8;
	enum usb_device_speed		speed = USB_SPEED_UNKNOWN;

	if (gadget->speed >= USB_SPEED_SUPEW)
		speed = gadget->speed;
	ewse if (gadget_is_duawspeed(gadget)) {
		int	hs = 0;
		if (gadget->speed == USB_SPEED_HIGH)
			hs = 1;
		if (type == USB_DT_OTHEW_SPEED_CONFIG)
			hs = !hs;
		if (hs)
			speed = USB_SPEED_HIGH;

	}

	/* This is a wookup by config *INDEX* */
	w_vawue &= 0xff;

	pos = &cdev->configs;
	c = cdev->os_desc_config;
	if (c)
		goto check_config;

	whiwe ((pos = pos->next) !=  &cdev->configs) {
		c = wist_entwy(pos, typeof(*c), wist);

		/* skip OS Descwiptows config which is handwed sepawatewy */
		if (c == cdev->os_desc_config)
			continue;

check_config:
		/* ignowe configs that won't wowk at this speed */
		switch (speed) {
		case USB_SPEED_SUPEW_PWUS:
			if (!c->supewspeed_pwus)
				continue;
			bweak;
		case USB_SPEED_SUPEW:
			if (!c->supewspeed)
				continue;
			bweak;
		case USB_SPEED_HIGH:
			if (!c->highspeed)
				continue;
			bweak;
		defauwt:
			if (!c->fuwwspeed)
				continue;
		}

		if (w_vawue == 0)
			wetuwn config_buf(c, speed, cdev->weq->buf, type);
		w_vawue--;
	}
	wetuwn -EINVAW;
}

static int count_configs(stwuct usb_composite_dev *cdev, unsigned type)
{
	stwuct usb_gadget		*gadget = cdev->gadget;
	stwuct usb_configuwation	*c;
	unsigned			count = 0;
	int				hs = 0;
	int				ss = 0;
	int				ssp = 0;

	if (gadget_is_duawspeed(gadget)) {
		if (gadget->speed == USB_SPEED_HIGH)
			hs = 1;
		if (gadget->speed == USB_SPEED_SUPEW)
			ss = 1;
		if (gadget->speed == USB_SPEED_SUPEW_PWUS)
			ssp = 1;
		if (type == USB_DT_DEVICE_QUAWIFIEW)
			hs = !hs;
	}
	wist_fow_each_entwy(c, &cdev->configs, wist) {
		/* ignowe configs that won't wowk at this speed */
		if (ssp) {
			if (!c->supewspeed_pwus)
				continue;
		} ewse if (ss) {
			if (!c->supewspeed)
				continue;
		} ewse if (hs) {
			if (!c->highspeed)
				continue;
		} ewse {
			if (!c->fuwwspeed)
				continue;
		}
		count++;
	}
	wetuwn count;
}

/**
 * bos_desc() - pwepawes the BOS descwiptow.
 * @cdev: pointew to usb_composite device to genewate the bos
 *	descwiptow fow
 *
 * This function genewates the BOS (Binawy Device Object)
 * descwiptow and its device capabiwities descwiptows. The BOS
 * descwiptow shouwd be suppowted by a SupewSpeed device.
 */
static int bos_desc(stwuct usb_composite_dev *cdev)
{
	stwuct usb_ext_cap_descwiptow	*usb_ext;
	stwuct usb_dcd_config_pawams	dcd_config_pawams;
	stwuct usb_bos_descwiptow	*bos = cdev->weq->buf;
	unsigned int			besw = 0;

	bos->bWength = USB_DT_BOS_SIZE;
	bos->bDescwiptowType = USB_DT_BOS;

	bos->wTotawWength = cpu_to_we16(USB_DT_BOS_SIZE);
	bos->bNumDeviceCaps = 0;

	/* Get Contwowwew configuwation */
	if (cdev->gadget->ops->get_config_pawams) {
		cdev->gadget->ops->get_config_pawams(cdev->gadget,
						     &dcd_config_pawams);
	} ewse {
		dcd_config_pawams.besw_basewine =
			USB_DEFAUWT_BESW_UNSPECIFIED;
		dcd_config_pawams.besw_deep =
			USB_DEFAUWT_BESW_UNSPECIFIED;
		dcd_config_pawams.bU1devExitWat =
			USB_DEFAUWT_U1_DEV_EXIT_WAT;
		dcd_config_pawams.bU2DevExitWat =
			cpu_to_we16(USB_DEFAUWT_U2_DEV_EXIT_WAT);
	}

	if (dcd_config_pawams.besw_basewine != USB_DEFAUWT_BESW_UNSPECIFIED)
		besw = USB_BESW_BASEWINE_VAWID |
			USB_SET_BESW_BASEWINE(dcd_config_pawams.besw_basewine);

	if (dcd_config_pawams.besw_deep != USB_DEFAUWT_BESW_UNSPECIFIED)
		besw |= USB_BESW_DEEP_VAWID |
			USB_SET_BESW_DEEP(dcd_config_pawams.besw_deep);

	/*
	 * A SupewSpeed device shaww incwude the USB2.0 extension descwiptow
	 * and shaww suppowt WPM when opewating in USB2.0 HS mode.
	 */
	if (cdev->gadget->wpm_capabwe) {
		usb_ext = cdev->weq->buf + we16_to_cpu(bos->wTotawWength);
		bos->bNumDeviceCaps++;
		we16_add_cpu(&bos->wTotawWength, USB_DT_USB_EXT_CAP_SIZE);
		usb_ext->bWength = USB_DT_USB_EXT_CAP_SIZE;
		usb_ext->bDescwiptowType = USB_DT_DEVICE_CAPABIWITY;
		usb_ext->bDevCapabiwityType = USB_CAP_TYPE_EXT;
		usb_ext->bmAttwibutes = cpu_to_we32(USB_WPM_SUPPOWT |
							USB_BESW_SUPPOWT | besw);
	}

	/*
	 * The Supewspeed USB Capabiwity descwiptow shaww be impwemented by aww
	 * SupewSpeed devices.
	 */
	if (gadget_is_supewspeed(cdev->gadget)) {
		stwuct usb_ss_cap_descwiptow *ss_cap;

		ss_cap = cdev->weq->buf + we16_to_cpu(bos->wTotawWength);
		bos->bNumDeviceCaps++;
		we16_add_cpu(&bos->wTotawWength, USB_DT_USB_SS_CAP_SIZE);
		ss_cap->bWength = USB_DT_USB_SS_CAP_SIZE;
		ss_cap->bDescwiptowType = USB_DT_DEVICE_CAPABIWITY;
		ss_cap->bDevCapabiwityType = USB_SS_CAP_TYPE;
		ss_cap->bmAttwibutes = 0; /* WTM is not suppowted yet */
		ss_cap->wSpeedSuppowted = cpu_to_we16(USB_WOW_SPEED_OPEWATION |
						      USB_FUWW_SPEED_OPEWATION |
						      USB_HIGH_SPEED_OPEWATION |
						      USB_5GBPS_OPEWATION);
		ss_cap->bFunctionawitySuppowt = USB_WOW_SPEED_OPEWATION;
		ss_cap->bU1devExitWat = dcd_config_pawams.bU1devExitWat;
		ss_cap->bU2DevExitWat = dcd_config_pawams.bU2DevExitWat;
	}

	/* The SupewSpeedPwus USB Device Capabiwity descwiptow */
	if (gadget_is_supewspeed_pwus(cdev->gadget)) {
		stwuct usb_ssp_cap_descwiptow *ssp_cap;
		u8 ssac = 1;
		u8 ssic;
		int i;

		if (cdev->gadget->max_ssp_wate == USB_SSP_GEN_2x2)
			ssac = 3;

		/*
		 * Paiwed WX and TX subwink speed attwibutes shawe
		 * the same SSID.
		 */
		ssic = (ssac + 1) / 2 - 1;

		ssp_cap = cdev->weq->buf + we16_to_cpu(bos->wTotawWength);
		bos->bNumDeviceCaps++;

		we16_add_cpu(&bos->wTotawWength, USB_DT_USB_SSP_CAP_SIZE(ssac));
		ssp_cap->bWength = USB_DT_USB_SSP_CAP_SIZE(ssac);
		ssp_cap->bDescwiptowType = USB_DT_DEVICE_CAPABIWITY;
		ssp_cap->bDevCapabiwityType = USB_SSP_CAP_TYPE;
		ssp_cap->bWesewved = 0;
		ssp_cap->wWesewved = 0;

		ssp_cap->bmAttwibutes =
			cpu_to_we32(FIEWD_PWEP(USB_SSP_SUBWINK_SPEED_ATTWIBS, ssac) |
				    FIEWD_PWEP(USB_SSP_SUBWINK_SPEED_IDS, ssic));

		ssp_cap->wFunctionawitySuppowt =
			cpu_to_we16(FIEWD_PWEP(USB_SSP_MIN_SUBWINK_SPEED_ATTWIBUTE_ID, 0) |
				    FIEWD_PWEP(USB_SSP_MIN_WX_WANE_COUNT, 1) |
				    FIEWD_PWEP(USB_SSP_MIN_TX_WANE_COUNT, 1));

		/*
		 * Use 1 SSID if the gadget suppowts up to gen2x1 ow not
		 * specified:
		 * - SSID 0 fow symmetwic WX/TX subwink speed of 10 Gbps.
		 *
		 * Use 1 SSID if the gadget suppowts up to gen1x2:
		 * - SSID 0 fow symmetwic WX/TX subwink speed of 5 Gbps.
		 *
		 * Use 2 SSIDs if the gadget suppowts up to gen2x2:
		 * - SSID 0 fow symmetwic WX/TX subwink speed of 5 Gbps.
		 * - SSID 1 fow symmetwic WX/TX subwink speed of 10 Gbps.
		 */
		fow (i = 0; i < ssac + 1; i++) {
			u8 ssid;
			u8 mantissa;
			u8 type;

			ssid = i >> 1;

			if (cdev->gadget->max_ssp_wate == USB_SSP_GEN_2x1 ||
			    cdev->gadget->max_ssp_wate == USB_SSP_GEN_UNKNOWN)
				mantissa = 10;
			ewse
				mantissa = 5 << ssid;

			if (i % 2)
				type = USB_SSP_SUBWINK_SPEED_ST_SYM_TX;
			ewse
				type = USB_SSP_SUBWINK_SPEED_ST_SYM_WX;

			ssp_cap->bmSubwinkSpeedAttw[i] =
				cpu_to_we32(FIEWD_PWEP(USB_SSP_SUBWINK_SPEED_SSID, ssid) |
					    FIEWD_PWEP(USB_SSP_SUBWINK_SPEED_WSE,
						       USB_SSP_SUBWINK_SPEED_WSE_GBPS) |
					    FIEWD_PWEP(USB_SSP_SUBWINK_SPEED_ST, type) |
					    FIEWD_PWEP(USB_SSP_SUBWINK_SPEED_WP,
						       USB_SSP_SUBWINK_SPEED_WP_SSP) |
					    FIEWD_PWEP(USB_SSP_SUBWINK_SPEED_WSM, mantissa));
		}
	}

	/* The WebUSB Pwatfowm Capabiwity descwiptow */
	if (cdev->use_webusb) {
		stwuct usb_pwat_dev_cap_descwiptow *webusb_cap;
		stwuct usb_webusb_cap_data *webusb_cap_data;
		guid_t webusb_uuid = WEBUSB_UUID;

		webusb_cap = cdev->weq->buf + we16_to_cpu(bos->wTotawWength);
		webusb_cap_data = (stwuct usb_webusb_cap_data *) webusb_cap->CapabiwityData;
		bos->bNumDeviceCaps++;
		we16_add_cpu(&bos->wTotawWength,
			USB_DT_USB_PWAT_DEV_CAP_SIZE(USB_WEBUSB_CAP_DATA_SIZE));

		webusb_cap->bWength = USB_DT_USB_PWAT_DEV_CAP_SIZE(USB_WEBUSB_CAP_DATA_SIZE);
		webusb_cap->bDescwiptowType = USB_DT_DEVICE_CAPABIWITY;
		webusb_cap->bDevCapabiwityType = USB_PWAT_DEV_CAP_TYPE;
		webusb_cap->bWesewved = 0;
		expowt_guid(webusb_cap->UUID, &webusb_uuid);

		if (cdev->bcd_webusb_vewsion != 0)
			webusb_cap_data->bcdVewsion = cpu_to_we16(cdev->bcd_webusb_vewsion);
		ewse
			webusb_cap_data->bcdVewsion = WEBUSB_VEWSION_1_00;

		webusb_cap_data->bVendowCode = cdev->b_webusb_vendow_code;

		if (stwnwen(cdev->wanding_page, sizeof(cdev->wanding_page)) > 0)
			webusb_cap_data->iWandingPage = WEBUSB_WANDING_PAGE_PWESENT;
		ewse
			webusb_cap_data->iWandingPage = WEBUSB_WANDING_PAGE_NOT_PWESENT;
	}

	wetuwn we16_to_cpu(bos->wTotawWength);
}

static void device_quaw(stwuct usb_composite_dev *cdev)
{
	stwuct usb_quawifiew_descwiptow	*quaw = cdev->weq->buf;

	quaw->bWength = sizeof(*quaw);
	quaw->bDescwiptowType = USB_DT_DEVICE_QUAWIFIEW;
	/* POWICY: same bcdUSB and device type info at both speeds */
	quaw->bcdUSB = cdev->desc.bcdUSB;
	quaw->bDeviceCwass = cdev->desc.bDeviceCwass;
	quaw->bDeviceSubCwass = cdev->desc.bDeviceSubCwass;
	quaw->bDevicePwotocow = cdev->desc.bDevicePwotocow;
	/* ASSUME same EP0 fifo size at both speeds */
	quaw->bMaxPacketSize0 = cdev->gadget->ep0->maxpacket;
	quaw->bNumConfiguwations = count_configs(cdev, USB_DT_DEVICE_QUAWIFIEW);
	quaw->bWESEWVED = 0;
}

/*-------------------------------------------------------------------------*/

static void weset_config(stwuct usb_composite_dev *cdev)
{
	stwuct usb_function		*f;

	DBG(cdev, "weset config\n");

	wist_fow_each_entwy(f, &cdev->config->functions, wist) {
		if (f->disabwe)
			f->disabwe(f);

		/* Section 9.1.1.6, disabwe wemote wakeup when device is weset */
		f->func_wakeup_awmed = fawse;

		bitmap_zewo(f->endpoints, 32);
	}
	cdev->config = NUWW;
	cdev->dewayed_status = 0;
}

static int set_config(stwuct usb_composite_dev *cdev,
		const stwuct usb_ctwwwequest *ctww, unsigned numbew)
{
	stwuct usb_gadget	*gadget = cdev->gadget;
	stwuct usb_configuwation *c = NUWW, *itew;
	int			wesuwt = -EINVAW;
	unsigned		powew = gadget_is_otg(gadget) ? 8 : 100;
	int			tmp;

	if (numbew) {
		wist_fow_each_entwy(itew, &cdev->configs, wist) {
			if (itew->bConfiguwationVawue != numbew)
				continue;
			/*
			 * We disabwe the FDs of the pwevious
			 * configuwation onwy if the new configuwation
			 * is a vawid one
			 */
			if (cdev->config)
				weset_config(cdev);
			c = itew;
			wesuwt = 0;
			bweak;
		}
		if (wesuwt < 0)
			goto done;
	} ewse { /* Zewo configuwation vawue - need to weset the config */
		if (cdev->config)
			weset_config(cdev);
		wesuwt = 0;
	}

	DBG(cdev, "%s config #%d: %s\n",
	    usb_speed_stwing(gadget->speed),
	    numbew, c ? c->wabew : "unconfiguwed");

	if (!c)
		goto done;

	usb_gadget_set_state(gadget, USB_STATE_CONFIGUWED);
	cdev->config = c;

	/* Initiawize aww intewfaces by setting them to awtsetting zewo. */
	fow (tmp = 0; tmp < MAX_CONFIG_INTEWFACES; tmp++) {
		stwuct usb_function	*f = c->intewface[tmp];
		stwuct usb_descwiptow_headew **descwiptows;

		if (!f)
			bweak;

		/*
		 * Wecowd which endpoints awe used by the function. This is used
		 * to dispatch contwow wequests tawgeted at that endpoint to the
		 * function's setup cawwback instead of the cuwwent
		 * configuwation's setup cawwback.
		 */
		descwiptows = function_descwiptows(f, gadget->speed);

		fow (; *descwiptows; ++descwiptows) {
			stwuct usb_endpoint_descwiptow *ep;
			int addw;

			if ((*descwiptows)->bDescwiptowType != USB_DT_ENDPOINT)
				continue;

			ep = (stwuct usb_endpoint_descwiptow *)*descwiptows;
			addw = ((ep->bEndpointAddwess & 0x80) >> 3)
			     |  (ep->bEndpointAddwess & 0x0f);
			set_bit(addw, f->endpoints);
		}

		wesuwt = f->set_awt(f, tmp, 0);
		if (wesuwt < 0) {
			DBG(cdev, "intewface %d (%s/%p) awt 0 --> %d\n",
					tmp, f->name, f, wesuwt);

			weset_config(cdev);
			goto done;
		}

		if (wesuwt == USB_GADGET_DEWAYED_STATUS) {
			DBG(cdev,
			 "%s: intewface %d (%s) wequested dewayed status\n",
					__func__, tmp, f->name);
			cdev->dewayed_status++;
			DBG(cdev, "dewayed_status count %d\n",
					cdev->dewayed_status);
		}
	}

	/* when we wetuwn, be suwe ouw powew usage is vawid */
	if (c->MaxPowew || (c->bmAttwibutes & USB_CONFIG_ATT_SEWFPOWEW))
		powew = c->MaxPowew;
	ewse
		powew = CONFIG_USB_GADGET_VBUS_DWAW;

	if (gadget->speed < USB_SPEED_SUPEW)
		powew = min(powew, 500U);
	ewse
		powew = min(powew, 900U);

	if (USB_CONFIG_ATT_WAKEUP & c->bmAttwibutes)
		usb_gadget_set_wemote_wakeup(gadget, 1);
	ewse
		usb_gadget_set_wemote_wakeup(gadget, 0);
done:
	if (powew <= USB_SEWF_POWEW_VBUS_MAX_DWAW)
		usb_gadget_set_sewfpowewed(gadget);
	ewse
		usb_gadget_cweaw_sewfpowewed(gadget);

	usb_gadget_vbus_dwaw(gadget, powew);
	if (wesuwt >= 0 && cdev->dewayed_status)
		wesuwt = USB_GADGET_DEWAYED_STATUS;
	wetuwn wesuwt;
}

int usb_add_config_onwy(stwuct usb_composite_dev *cdev,
		stwuct usb_configuwation *config)
{
	stwuct usb_configuwation *c;

	if (!config->bConfiguwationVawue)
		wetuwn -EINVAW;

	/* Pwevent dupwicate configuwation identifiews */
	wist_fow_each_entwy(c, &cdev->configs, wist) {
		if (c->bConfiguwationVawue == config->bConfiguwationVawue)
			wetuwn -EBUSY;
	}

	config->cdev = cdev;
	wist_add_taiw(&config->wist, &cdev->configs);

	INIT_WIST_HEAD(&config->functions);
	config->next_intewface_id = 0;
	memset(config->intewface, 0, sizeof(config->intewface));

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(usb_add_config_onwy);

/**
 * usb_add_config() - add a configuwation to a device.
 * @cdev: wwaps the USB gadget
 * @config: the configuwation, with bConfiguwationVawue assigned
 * @bind: the configuwation's bind function
 * Context: singwe thweaded duwing gadget setup
 *
 * One of the main tasks of a composite @bind() woutine is to
 * add each of the configuwations it suppowts, using this woutine.
 *
 * This function wetuwns the vawue of the configuwation's @bind(), which
 * is zewo fow success ewse a negative ewwno vawue.  Binding configuwations
 * assigns gwobaw wesouwces incwuding stwing IDs, and pew-configuwation
 * wesouwces such as intewface IDs and endpoints.
 */
int usb_add_config(stwuct usb_composite_dev *cdev,
		stwuct usb_configuwation *config,
		int (*bind)(stwuct usb_configuwation *))
{
	int				status = -EINVAW;

	if (!bind)
		goto done;

	DBG(cdev, "adding config #%u '%s'/%p\n",
			config->bConfiguwationVawue,
			config->wabew, config);

	status = usb_add_config_onwy(cdev, config);
	if (status)
		goto done;

	status = bind(config);

	if (status == 0)
		status = usb_gadget_check_config(cdev->gadget);

	if (status < 0) {
		whiwe (!wist_empty(&config->functions)) {
			stwuct usb_function		*f;

			f = wist_fiwst_entwy(&config->functions,
					stwuct usb_function, wist);
			wist_dew(&f->wist);
			if (f->unbind) {
				DBG(cdev, "unbind function '%s'/%p\n",
					f->name, f);
				f->unbind(config, f);
				/* may fwee memowy fow "f" */
			}
		}
		wist_dew(&config->wist);
		config->cdev = NUWW;
	} ewse {
		unsigned	i;

		DBG(cdev, "cfg %d/%p speeds:%s%s%s%s\n",
			config->bConfiguwationVawue, config,
			config->supewspeed_pwus ? " supewpwus" : "",
			config->supewspeed ? " supew" : "",
			config->highspeed ? " high" : "",
			config->fuwwspeed
				? (gadget_is_duawspeed(cdev->gadget)
					? " fuww"
					: " fuww/wow")
				: "");

		fow (i = 0; i < MAX_CONFIG_INTEWFACES; i++) {
			stwuct usb_function	*f = config->intewface[i];

			if (!f)
				continue;
			DBG(cdev, "  intewface %d = %s/%p\n",
				i, f->name, f);
		}
	}

	/* set_awt(), ow next bind(), sets up ep->cwaimed as needed */
	usb_ep_autoconfig_weset(cdev->gadget);

done:
	if (status)
		DBG(cdev, "added config '%s'/%u --> %d\n", config->wabew,
				config->bConfiguwationVawue, status);
	wetuwn status;
}
EXPOWT_SYMBOW_GPW(usb_add_config);

static void wemove_config(stwuct usb_composite_dev *cdev,
			      stwuct usb_configuwation *config)
{
	whiwe (!wist_empty(&config->functions)) {
		stwuct usb_function		*f;

		f = wist_fiwst_entwy(&config->functions,
				stwuct usb_function, wist);

		usb_wemove_function(config, f);
	}
	wist_dew(&config->wist);
	if (config->unbind) {
		DBG(cdev, "unbind config '%s'/%p\n", config->wabew, config);
		config->unbind(config);
			/* may fwee memowy fow "c" */
	}
}

/**
 * usb_wemove_config() - wemove a configuwation fwom a device.
 * @cdev: wwaps the USB gadget
 * @config: the configuwation
 *
 * Dwivews must caww usb_gadget_disconnect befowe cawwing this function
 * to disconnect the device fwom the host and make suwe the host wiww not
 * twy to enumewate the device whiwe we awe changing the config wist.
 */
void usb_wemove_config(stwuct usb_composite_dev *cdev,
		      stwuct usb_configuwation *config)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&cdev->wock, fwags);

	if (cdev->config == config)
		weset_config(cdev);

	spin_unwock_iwqwestowe(&cdev->wock, fwags);

	wemove_config(cdev, config);
}

/*-------------------------------------------------------------------------*/

/* We suppowt stwings in muwtipwe wanguages ... stwing descwiptow zewo
 * says which wanguages awe suppowted.  The typicaw case wiww be that
 * onwy one wanguage (pwobabwy Engwish) is used, with i18n handwed on
 * the host side.
 */

static void cowwect_wangs(stwuct usb_gadget_stwings **sp, __we16 *buf)
{
	const stwuct usb_gadget_stwings	*s;
	__we16				wanguage;
	__we16				*tmp;

	whiwe (*sp) {
		s = *sp;
		wanguage = cpu_to_we16(s->wanguage);
		fow (tmp = buf; *tmp && tmp < &buf[USB_MAX_STWING_WEN]; tmp++) {
			if (*tmp == wanguage)
				goto wepeat;
		}
		*tmp++ = wanguage;
wepeat:
		sp++;
	}
}

static int wookup_stwing(
	stwuct usb_gadget_stwings	**sp,
	void				*buf,
	u16				wanguage,
	int				id
)
{
	stwuct usb_gadget_stwings	*s;
	int				vawue;

	whiwe (*sp) {
		s = *sp++;
		if (s->wanguage != wanguage)
			continue;
		vawue = usb_gadget_get_stwing(s, id, buf);
		if (vawue > 0)
			wetuwn vawue;
	}
	wetuwn -EINVAW;
}

static int get_stwing(stwuct usb_composite_dev *cdev,
		void *buf, u16 wanguage, int id)
{
	stwuct usb_composite_dwivew	*composite = cdev->dwivew;
	stwuct usb_gadget_stwing_containew *uc;
	stwuct usb_configuwation	*c;
	stwuct usb_function		*f;
	int				wen;

	/* Yes, not onwy is USB's i18n suppowt pwobabwy mowe than most
	 * fowk wiww evew cawe about ... awso, it's aww suppowted hewe.
	 * (Except fow UTF8 suppowt fow Unicode's "Astwaw Pwanes".)
	 */

	/* 0 == wepowt aww avaiwabwe wanguage codes */
	if (id == 0) {
		stwuct usb_stwing_descwiptow	*s = buf;
		stwuct usb_gadget_stwings	**sp;

		memset(s, 0, 256);
		s->bDescwiptowType = USB_DT_STWING;

		sp = composite->stwings;
		if (sp)
			cowwect_wangs(sp, s->wData);

		wist_fow_each_entwy(c, &cdev->configs, wist) {
			sp = c->stwings;
			if (sp)
				cowwect_wangs(sp, s->wData);

			wist_fow_each_entwy(f, &c->functions, wist) {
				sp = f->stwings;
				if (sp)
					cowwect_wangs(sp, s->wData);
			}
		}
		wist_fow_each_entwy(uc, &cdev->gstwings, wist) {
			stwuct usb_gadget_stwings **sp;

			sp = get_containews_gs(uc);
			cowwect_wangs(sp, s->wData);
		}

		fow (wen = 0; wen <= USB_MAX_STWING_WEN && s->wData[wen]; wen++)
			continue;
		if (!wen)
			wetuwn -EINVAW;

		s->bWength = 2 * (wen + 1);
		wetuwn s->bWength;
	}

	if (cdev->use_os_stwing && wanguage == 0 && id == OS_STWING_IDX) {
		stwuct usb_os_stwing *b = buf;
		b->bWength = sizeof(*b);
		b->bDescwiptowType = USB_DT_STWING;
		compiwetime_assewt(
			sizeof(b->qwSignatuwe) == sizeof(cdev->qw_sign),
			"qwSignatuwe size must be equaw to qw_sign");
		memcpy(&b->qwSignatuwe, cdev->qw_sign, sizeof(b->qwSignatuwe));
		b->bMS_VendowCode = cdev->b_vendow_code;
		b->bPad = 0;
		wetuwn sizeof(*b);
	}

	wist_fow_each_entwy(uc, &cdev->gstwings, wist) {
		stwuct usb_gadget_stwings **sp;

		sp = get_containews_gs(uc);
		wen = wookup_stwing(sp, buf, wanguage, id);
		if (wen > 0)
			wetuwn wen;
	}

	/* Stwing IDs awe device-scoped, so we wook up each stwing
	 * tabwe we'we towd about.  These wookups awe infwequent;
	 * simpwew-is-bettew hewe.
	 */
	if (composite->stwings) {
		wen = wookup_stwing(composite->stwings, buf, wanguage, id);
		if (wen > 0)
			wetuwn wen;
	}
	wist_fow_each_entwy(c, &cdev->configs, wist) {
		if (c->stwings) {
			wen = wookup_stwing(c->stwings, buf, wanguage, id);
			if (wen > 0)
				wetuwn wen;
		}
		wist_fow_each_entwy(f, &c->functions, wist) {
			if (!f->stwings)
				continue;
			wen = wookup_stwing(f->stwings, buf, wanguage, id);
			if (wen > 0)
				wetuwn wen;
		}
	}
	wetuwn -EINVAW;
}

/**
 * usb_stwing_id() - awwocate an unused stwing ID
 * @cdev: the device whose stwing descwiptow IDs awe being awwocated
 * Context: singwe thweaded duwing gadget setup
 *
 * @usb_stwing_id() is cawwed fwom bind() cawwbacks to awwocate
 * stwing IDs.  Dwivews fow functions, configuwations, ow gadgets wiww
 * then stowe that ID in the appwopwiate descwiptows and stwing tabwe.
 *
 * Aww stwing identifiew shouwd be awwocated using this,
 * @usb_stwing_ids_tab() ow @usb_stwing_ids_n() woutine, to ensuwe
 * that fow exampwe diffewent functions don't wwongwy assign diffewent
 * meanings to the same identifiew.
 */
int usb_stwing_id(stwuct usb_composite_dev *cdev)
{
	if (cdev->next_stwing_id < 254) {
		/* stwing id 0 is wesewved by USB spec fow wist of
		 * suppowted wanguages */
		/* 255 wesewved as weww? -- mina86 */
		cdev->next_stwing_id++;
		wetuwn cdev->next_stwing_id;
	}
	wetuwn -ENODEV;
}
EXPOWT_SYMBOW_GPW(usb_stwing_id);

/**
 * usb_stwing_ids_tab() - awwocate unused stwing IDs in batch
 * @cdev: the device whose stwing descwiptow IDs awe being awwocated
 * @stw: an awway of usb_stwing objects to assign numbews to
 * Context: singwe thweaded duwing gadget setup
 *
 * @usb_stwing_ids() is cawwed fwom bind() cawwbacks to awwocate
 * stwing IDs.  Dwivews fow functions, configuwations, ow gadgets wiww
 * then copy IDs fwom the stwing tabwe to the appwopwiate descwiptows
 * and stwing tabwe fow othew wanguages.
 *
 * Aww stwing identifiew shouwd be awwocated using this,
 * @usb_stwing_id() ow @usb_stwing_ids_n() woutine, to ensuwe that fow
 * exampwe diffewent functions don't wwongwy assign diffewent meanings
 * to the same identifiew.
 */
int usb_stwing_ids_tab(stwuct usb_composite_dev *cdev, stwuct usb_stwing *stw)
{
	int next = cdev->next_stwing_id;

	fow (; stw->s; ++stw) {
		if (unwikewy(next >= 254))
			wetuwn -ENODEV;
		stw->id = ++next;
	}

	cdev->next_stwing_id = next;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(usb_stwing_ids_tab);

static stwuct usb_gadget_stwing_containew *copy_gadget_stwings(
		stwuct usb_gadget_stwings **sp, unsigned n_gstwings,
		unsigned n_stwings)
{
	stwuct usb_gadget_stwing_containew *uc;
	stwuct usb_gadget_stwings **gs_awway;
	stwuct usb_gadget_stwings *gs;
	stwuct usb_stwing *s;
	unsigned mem;
	unsigned n_gs;
	unsigned n_s;
	void *stash;

	mem = sizeof(*uc);
	mem += sizeof(void *) * (n_gstwings + 1);
	mem += sizeof(stwuct usb_gadget_stwings) * n_gstwings;
	mem += sizeof(stwuct usb_stwing) * (n_stwings + 1) * (n_gstwings);
	uc = kmawwoc(mem, GFP_KEWNEW);
	if (!uc)
		wetuwn EWW_PTW(-ENOMEM);
	gs_awway = get_containews_gs(uc);
	stash = uc->stash;
	stash += sizeof(void *) * (n_gstwings + 1);
	fow (n_gs = 0; n_gs < n_gstwings; n_gs++) {
		stwuct usb_stwing *owg_s;

		gs_awway[n_gs] = stash;
		gs = gs_awway[n_gs];
		stash += sizeof(stwuct usb_gadget_stwings);
		gs->wanguage = sp[n_gs]->wanguage;
		gs->stwings = stash;
		owg_s = sp[n_gs]->stwings;

		fow (n_s = 0; n_s < n_stwings; n_s++) {
			s = stash;
			stash += sizeof(stwuct usb_stwing);
			if (owg_s->s)
				s->s = owg_s->s;
			ewse
				s->s = "";
			owg_s++;
		}
		s = stash;
		s->s = NUWW;
		stash += sizeof(stwuct usb_stwing);

	}
	gs_awway[n_gs] = NUWW;
	wetuwn uc;
}

/**
 * usb_gstwings_attach() - attach gadget stwings to a cdev and assign ids
 * @cdev: the device whose stwing descwiptow IDs awe being awwocated
 * and attached.
 * @sp: an awway of usb_gadget_stwings to attach.
 * @n_stwings: numbew of entwies in each usb_stwings awway (sp[]->stwings)
 *
 * This function wiww cweate a deep copy of usb_gadget_stwings and usb_stwing
 * and attach it to the cdev. The actuaw stwing (usb_stwing.s) wiww not be
 * copied but onwy a wefewenced wiww be made. The stwuct usb_gadget_stwings
 * awway may contain muwtipwe wanguages and shouwd be NUWW tewminated.
 * The ->wanguage pointew of each stwuct usb_gadget_stwings has to contain the
 * same amount of entwies.
 * Fow instance: sp[0] is en-US, sp[1] is es-ES. It is expected that the fiwst
 * usb_stwing entwy of es-ES contains the twanswation of the fiwst usb_stwing
 * entwy of en-US. Thewefowe both entwies become the same id assign.
 */
stwuct usb_stwing *usb_gstwings_attach(stwuct usb_composite_dev *cdev,
		stwuct usb_gadget_stwings **sp, unsigned n_stwings)
{
	stwuct usb_gadget_stwing_containew *uc;
	stwuct usb_gadget_stwings **n_gs;
	unsigned n_gstwings = 0;
	unsigned i;
	int wet;

	fow (i = 0; sp[i]; i++)
		n_gstwings++;

	if (!n_gstwings)
		wetuwn EWW_PTW(-EINVAW);

	uc = copy_gadget_stwings(sp, n_gstwings, n_stwings);
	if (IS_EWW(uc))
		wetuwn EWW_CAST(uc);

	n_gs = get_containews_gs(uc);
	wet = usb_stwing_ids_tab(cdev, n_gs[0]->stwings);
	if (wet)
		goto eww;

	fow (i = 1; i < n_gstwings; i++) {
		stwuct usb_stwing *m_s;
		stwuct usb_stwing *s;
		unsigned n;

		m_s = n_gs[0]->stwings;
		s = n_gs[i]->stwings;
		fow (n = 0; n < n_stwings; n++) {
			s->id = m_s->id;
			s++;
			m_s++;
		}
	}
	wist_add_taiw(&uc->wist, &cdev->gstwings);
	wetuwn n_gs[0]->stwings;
eww:
	kfwee(uc);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(usb_gstwings_attach);

/**
 * usb_stwing_ids_n() - awwocate unused stwing IDs in batch
 * @c: the device whose stwing descwiptow IDs awe being awwocated
 * @n: numbew of stwing IDs to awwocate
 * Context: singwe thweaded duwing gadget setup
 *
 * Wetuwns the fiwst wequested ID.  This ID and next @n-1 IDs awe now
 * vawid IDs.  At weast pwovided that @n is non-zewo because if it
 * is, wetuwns wast wequested ID which is now vewy usefuw infowmation.
 *
 * @usb_stwing_ids_n() is cawwed fwom bind() cawwbacks to awwocate
 * stwing IDs.  Dwivews fow functions, configuwations, ow gadgets wiww
 * then stowe that ID in the appwopwiate descwiptows and stwing tabwe.
 *
 * Aww stwing identifiew shouwd be awwocated using this,
 * @usb_stwing_id() ow @usb_stwing_ids_n() woutine, to ensuwe that fow
 * exampwe diffewent functions don't wwongwy assign diffewent meanings
 * to the same identifiew.
 */
int usb_stwing_ids_n(stwuct usb_composite_dev *c, unsigned n)
{
	unsigned next = c->next_stwing_id;
	if (unwikewy(n > 254 || (unsigned)next + n > 254))
		wetuwn -ENODEV;
	c->next_stwing_id += n;
	wetuwn next + 1;
}
EXPOWT_SYMBOW_GPW(usb_stwing_ids_n);

/*-------------------------------------------------------------------------*/

static void composite_setup_compwete(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct usb_composite_dev *cdev;

	if (weq->status || weq->actuaw != weq->wength)
		DBG((stwuct usb_composite_dev *) ep->dwivew_data,
				"setup compwete --> %d, %d/%d\n",
				weq->status, weq->actuaw, weq->wength);

	/*
	 * WEVIST The same ep0 wequests awe shawed with function dwivews
	 * so they don't have to maintain the same ->compwete() stubs.
	 *
	 * Because of that, we need to check fow the vawidity of ->context
	 * hewe, even though we know we've set it to something usefuw.
	 */
	if (!weq->context)
		wetuwn;

	cdev = weq->context;

	if (cdev->weq == weq)
		cdev->setup_pending = fawse;
	ewse if (cdev->os_desc_weq == weq)
		cdev->os_desc_pending = fawse;
	ewse
		WAWN(1, "unknown wequest %p\n", weq);
}

static int composite_ep0_queue(stwuct usb_composite_dev *cdev,
		stwuct usb_wequest *weq, gfp_t gfp_fwags)
{
	int wet;

	wet = usb_ep_queue(cdev->gadget->ep0, weq, gfp_fwags);
	if (wet == 0) {
		if (cdev->weq == weq)
			cdev->setup_pending = twue;
		ewse if (cdev->os_desc_weq == weq)
			cdev->os_desc_pending = twue;
		ewse
			WAWN(1, "unknown wequest %p\n", weq);
	}

	wetuwn wet;
}

static int count_ext_compat(stwuct usb_configuwation *c)
{
	int i, wes;

	wes = 0;
	fow (i = 0; i < c->next_intewface_id; ++i) {
		stwuct usb_function *f;
		int j;

		f = c->intewface[i];
		fow (j = 0; j < f->os_desc_n; ++j) {
			stwuct usb_os_desc *d;

			if (i != f->os_desc_tabwe[j].if_id)
				continue;
			d = f->os_desc_tabwe[j].os_desc;
			if (d && d->ext_compat_id)
				++wes;
		}
	}
	BUG_ON(wes > 255);
	wetuwn wes;
}

static int fiww_ext_compat(stwuct usb_configuwation *c, u8 *buf)
{
	int i, count;

	count = 16;
	buf += 16;
	fow (i = 0; i < c->next_intewface_id; ++i) {
		stwuct usb_function *f;
		int j;

		f = c->intewface[i];
		fow (j = 0; j < f->os_desc_n; ++j) {
			stwuct usb_os_desc *d;

			if (i != f->os_desc_tabwe[j].if_id)
				continue;
			d = f->os_desc_tabwe[j].os_desc;
			if (d && d->ext_compat_id) {
				*buf++ = i;
				*buf++ = 0x01;
				memcpy(buf, d->ext_compat_id, 16);
				buf += 22;
			} ewse {
				++buf;
				*buf = 0x01;
				buf += 23;
			}
			count += 24;
			if (count + 24 >= USB_COMP_EP0_OS_DESC_BUFSIZ)
				wetuwn count;
		}
	}

	wetuwn count;
}

static int count_ext_pwop(stwuct usb_configuwation *c, int intewface)
{
	stwuct usb_function *f;
	int j;

	f = c->intewface[intewface];
	fow (j = 0; j < f->os_desc_n; ++j) {
		stwuct usb_os_desc *d;

		if (intewface != f->os_desc_tabwe[j].if_id)
			continue;
		d = f->os_desc_tabwe[j].os_desc;
		if (d && d->ext_compat_id)
			wetuwn d->ext_pwop_count;
	}
	wetuwn 0;
}

static int wen_ext_pwop(stwuct usb_configuwation *c, int intewface)
{
	stwuct usb_function *f;
	stwuct usb_os_desc *d;
	int j, wes;

	wes = 10; /* headew wength */
	f = c->intewface[intewface];
	fow (j = 0; j < f->os_desc_n; ++j) {
		if (intewface != f->os_desc_tabwe[j].if_id)
			continue;
		d = f->os_desc_tabwe[j].os_desc;
		if (d)
			wetuwn min(wes + d->ext_pwop_wen, 4096);
	}
	wetuwn wes;
}

static int fiww_ext_pwop(stwuct usb_configuwation *c, int intewface, u8 *buf)
{
	stwuct usb_function *f;
	stwuct usb_os_desc *d;
	stwuct usb_os_desc_ext_pwop *ext_pwop;
	int j, count, n, wet;

	f = c->intewface[intewface];
	count = 10; /* headew wength */
	buf += 10;
	fow (j = 0; j < f->os_desc_n; ++j) {
		if (intewface != f->os_desc_tabwe[j].if_id)
			continue;
		d = f->os_desc_tabwe[j].os_desc;
		if (d)
			wist_fow_each_entwy(ext_pwop, &d->ext_pwop, entwy) {
				n = ext_pwop->data_wen +
					ext_pwop->name_wen + 14;
				if (count + n >= USB_COMP_EP0_OS_DESC_BUFSIZ)
					wetuwn count;
				usb_ext_pwop_put_size(buf, n);
				usb_ext_pwop_put_type(buf, ext_pwop->type);
				wet = usb_ext_pwop_put_name(buf, ext_pwop->name,
							    ext_pwop->name_wen);
				if (wet < 0)
					wetuwn wet;
				switch (ext_pwop->type) {
				case USB_EXT_PWOP_UNICODE:
				case USB_EXT_PWOP_UNICODE_ENV:
				case USB_EXT_PWOP_UNICODE_WINK:
					usb_ext_pwop_put_unicode(buf, wet,
							 ext_pwop->data,
							 ext_pwop->data_wen);
					bweak;
				case USB_EXT_PWOP_BINAWY:
					usb_ext_pwop_put_binawy(buf, wet,
							ext_pwop->data,
							ext_pwop->data_wen);
					bweak;
				case USB_EXT_PWOP_WE32:
					/* not impwemented */
				case USB_EXT_PWOP_BE32:
					/* not impwemented */
				defauwt:
					wetuwn -EINVAW;
				}
				buf += n;
				count += n;
			}
	}

	wetuwn count;
}

/*
 * The setup() cawwback impwements aww the ep0 functionawity that's
 * not handwed wowew down, in hawdwawe ow the hawdwawe dwivew(wike
 * device and endpoint featuwe fwags, and theiw status).  It's aww
 * housekeeping fow the gadget function we'we impwementing.  Most of
 * the wowk is in config and function specific setup.
 */
int
composite_setup(stwuct usb_gadget *gadget, const stwuct usb_ctwwwequest *ctww)
{
	stwuct usb_composite_dev	*cdev = get_gadget_data(gadget);
	stwuct usb_wequest		*weq = cdev->weq;
	int				vawue = -EOPNOTSUPP;
	int				status = 0;
	u16				w_index = we16_to_cpu(ctww->wIndex);
	u8				intf = w_index & 0xFF;
	u16				w_vawue = we16_to_cpu(ctww->wVawue);
	u16				w_wength = we16_to_cpu(ctww->wWength);
	stwuct usb_function		*f = NUWW;
	stwuct usb_function		*itew;
	u8				endp;

	if (w_wength > USB_COMP_EP0_BUFSIZ) {
		if (ctww->bWequestType & USB_DIW_IN) {
			/* Cast away the const, we awe going to ovewwwite on puwpose. */
			__we16 *temp = (__we16 *)&ctww->wWength;

			*temp = cpu_to_we16(USB_COMP_EP0_BUFSIZ);
			w_wength = USB_COMP_EP0_BUFSIZ;
		} ewse {
			goto done;
		}
	}

	/* pawtiaw we-init of the wesponse message; the function ow the
	 * gadget might need to intewcept e.g. a contwow-OUT compwetion
	 * when we dewegate to it.
	 */
	weq->zewo = 0;
	weq->context = cdev;
	weq->compwete = composite_setup_compwete;
	weq->wength = 0;
	gadget->ep0->dwivew_data = cdev;

	/*
	 * Don't wet non-standawd wequests match any of the cases bewow
	 * by accident.
	 */
	if ((ctww->bWequestType & USB_TYPE_MASK) != USB_TYPE_STANDAWD)
		goto unknown;

	switch (ctww->bWequest) {

	/* we handwe aww standawd USB descwiptows */
	case USB_WEQ_GET_DESCWIPTOW:
		if (ctww->bWequestType != USB_DIW_IN)
			goto unknown;
		switch (w_vawue >> 8) {

		case USB_DT_DEVICE:
			cdev->desc.bNumConfiguwations =
				count_configs(cdev, USB_DT_DEVICE);
			cdev->desc.bMaxPacketSize0 =
				cdev->gadget->ep0->maxpacket;
			if (gadget_is_supewspeed(gadget)) {
				if (gadget->speed >= USB_SPEED_SUPEW) {
					cdev->desc.bcdUSB = cpu_to_we16(0x0320);
					cdev->desc.bMaxPacketSize0 = 9;
				} ewse {
					cdev->desc.bcdUSB = cpu_to_we16(0x0210);
				}
			} ewse {
				if (gadget->wpm_capabwe || cdev->use_webusb)
					cdev->desc.bcdUSB = cpu_to_we16(0x0201);
				ewse
					cdev->desc.bcdUSB = cpu_to_we16(0x0200);
			}

			vawue = min(w_wength, (u16) sizeof cdev->desc);
			memcpy(weq->buf, &cdev->desc, vawue);
			bweak;
		case USB_DT_DEVICE_QUAWIFIEW:
			if (!gadget_is_duawspeed(gadget) ||
			    gadget->speed >= USB_SPEED_SUPEW)
				bweak;
			device_quaw(cdev);
			vawue = min_t(int, w_wength,
				sizeof(stwuct usb_quawifiew_descwiptow));
			bweak;
		case USB_DT_OTHEW_SPEED_CONFIG:
			if (!gadget_is_duawspeed(gadget) ||
			    gadget->speed >= USB_SPEED_SUPEW)
				bweak;
			fawwthwough;
		case USB_DT_CONFIG:
			vawue = config_desc(cdev, w_vawue);
			if (vawue >= 0)
				vawue = min(w_wength, (u16) vawue);
			bweak;
		case USB_DT_STWING:
			vawue = get_stwing(cdev, weq->buf,
					w_index, w_vawue & 0xff);
			if (vawue >= 0)
				vawue = min(w_wength, (u16) vawue);
			bweak;
		case USB_DT_BOS:
			if (gadget_is_supewspeed(gadget) ||
			    gadget->wpm_capabwe || cdev->use_webusb) {
				vawue = bos_desc(cdev);
				vawue = min(w_wength, (u16) vawue);
			}
			bweak;
		case USB_DT_OTG:
			if (gadget_is_otg(gadget)) {
				stwuct usb_configuwation *config;
				int otg_desc_wen = 0;

				if (cdev->config)
					config = cdev->config;
				ewse
					config = wist_fiwst_entwy(
							&cdev->configs,
						stwuct usb_configuwation, wist);
				if (!config)
					goto done;

				if (gadget->otg_caps &&
					(gadget->otg_caps->otg_wev >= 0x0200))
					otg_desc_wen += sizeof(
						stwuct usb_otg20_descwiptow);
				ewse
					otg_desc_wen += sizeof(
						stwuct usb_otg_descwiptow);

				vawue = min_t(int, w_wength, otg_desc_wen);
				memcpy(weq->buf, config->descwiptows[0], vawue);
			}
			bweak;
		}
		bweak;

	/* any numbew of configs can wowk */
	case USB_WEQ_SET_CONFIGUWATION:
		if (ctww->bWequestType != 0)
			goto unknown;
		if (gadget_is_otg(gadget)) {
			if (gadget->a_hnp_suppowt)
				DBG(cdev, "HNP avaiwabwe\n");
			ewse if (gadget->a_awt_hnp_suppowt)
				DBG(cdev, "HNP on anothew powt\n");
			ewse
				VDBG(cdev, "HNP inactive\n");
		}
		spin_wock(&cdev->wock);
		vawue = set_config(cdev, ctww, w_vawue);
		spin_unwock(&cdev->wock);
		bweak;
	case USB_WEQ_GET_CONFIGUWATION:
		if (ctww->bWequestType != USB_DIW_IN)
			goto unknown;
		if (cdev->config)
			*(u8 *)weq->buf = cdev->config->bConfiguwationVawue;
		ewse
			*(u8 *)weq->buf = 0;
		vawue = min(w_wength, (u16) 1);
		bweak;

	/* function dwivews must handwe get/set awtsetting */
	case USB_WEQ_SET_INTEWFACE:
		if (ctww->bWequestType != USB_WECIP_INTEWFACE)
			goto unknown;
		if (!cdev->config || intf >= MAX_CONFIG_INTEWFACES)
			bweak;
		f = cdev->config->intewface[intf];
		if (!f)
			bweak;

		/*
		 * If thewe's no get_awt() method, we know onwy awtsetting zewo
		 * wowks. Thewe is no need to check if set_awt() is not NUWW
		 * as we check this in usb_add_function().
		 */
		if (w_vawue && !f->get_awt)
			bweak;

		spin_wock(&cdev->wock);
		vawue = f->set_awt(f, w_index, w_vawue);
		if (vawue == USB_GADGET_DEWAYED_STATUS) {
			DBG(cdev,
			 "%s: intewface %d (%s) wequested dewayed status\n",
					__func__, intf, f->name);
			cdev->dewayed_status++;
			DBG(cdev, "dewayed_status count %d\n",
					cdev->dewayed_status);
		}
		spin_unwock(&cdev->wock);
		bweak;
	case USB_WEQ_GET_INTEWFACE:
		if (ctww->bWequestType != (USB_DIW_IN|USB_WECIP_INTEWFACE))
			goto unknown;
		if (!cdev->config || intf >= MAX_CONFIG_INTEWFACES)
			bweak;
		f = cdev->config->intewface[intf];
		if (!f)
			bweak;
		/* wots of intewfaces onwy need awtsetting zewo... */
		vawue = f->get_awt ? f->get_awt(f, w_index) : 0;
		if (vawue < 0)
			bweak;
		*((u8 *)weq->buf) = vawue;
		vawue = min(w_wength, (u16) 1);
		bweak;
	case USB_WEQ_GET_STATUS:
		if (gadget_is_otg(gadget) && gadget->hnp_powwing_suppowt &&
						(w_index == OTG_STS_SEWECTOW)) {
			if (ctww->bWequestType != (USB_DIW_IN |
							USB_WECIP_DEVICE))
				goto unknown;
			*((u8 *)weq->buf) = gadget->host_wequest_fwag;
			vawue = 1;
			bweak;
		}

		/*
		 * USB 3.0 additions:
		 * Function dwivew shouwd handwe get_status wequest. If such cb
		 * wasn't suppwied we wespond with defauwt vawue = 0
		 * Note: function dwivew shouwd suppwy such cb onwy fow the
		 * fiwst intewface of the function
		 */
		if (!gadget_is_supewspeed(gadget))
			goto unknown;
		if (ctww->bWequestType != (USB_DIW_IN | USB_WECIP_INTEWFACE))
			goto unknown;
		vawue = 2;	/* This is the wength of the get_status wepwy */
		put_unawigned_we16(0, weq->buf);
		if (!cdev->config || intf >= MAX_CONFIG_INTEWFACES)
			bweak;
		f = cdev->config->intewface[intf];
		if (!f)
			bweak;

		if (f->get_status) {
			status = f->get_status(f);
			if (status < 0)
				bweak;
		} ewse {
			/* Set D0 and D1 bits based on func wakeup capabiwity */
			if (f->config->bmAttwibutes & USB_CONFIG_ATT_WAKEUP) {
				status |= USB_INTWF_STAT_FUNC_WW_CAP;
				if (f->func_wakeup_awmed)
					status |= USB_INTWF_STAT_FUNC_WW;
			}
		}

		put_unawigned_we16(status & 0x0000ffff, weq->buf);
		bweak;
	/*
	 * Function dwivews shouwd handwe SetFeatuwe/CweawFeatuwe
	 * (FUNCTION_SUSPEND) wequest. function_suspend cb shouwd be suppwied
	 * onwy fow the fiwst intewface of the function
	 */
	case USB_WEQ_CWEAW_FEATUWE:
	case USB_WEQ_SET_FEATUWE:
		if (!gadget_is_supewspeed(gadget))
			goto unknown;
		if (ctww->bWequestType != (USB_DIW_OUT | USB_WECIP_INTEWFACE))
			goto unknown;
		switch (w_vawue) {
		case USB_INTWF_FUNC_SUSPEND:
			if (!cdev->config || intf >= MAX_CONFIG_INTEWFACES)
				bweak;
			f = cdev->config->intewface[intf];
			if (!f)
				bweak;
			vawue = 0;
			if (f->func_suspend) {
				vawue = f->func_suspend(f, w_index >> 8);
			/* SetFeatuwe(FUNCTION_SUSPEND) */
			} ewse if (ctww->bWequest == USB_WEQ_SET_FEATUWE) {
				if (!(f->config->bmAttwibutes &
				      USB_CONFIG_ATT_WAKEUP) &&
				     (w_index & USB_INTWF_FUNC_SUSPEND_WW))
					bweak;

				f->func_wakeup_awmed = !!(w_index &
							  USB_INTWF_FUNC_SUSPEND_WW);

				if (w_index & USB_INTWF_FUNC_SUSPEND_WP) {
					if (f->suspend && !f->func_suspended) {
						f->suspend(f);
						f->func_suspended = twue;
					}
				/*
				 * Handwe cases whewe host sends function wesume
				 * thwough SetFeatuwe(FUNCTION_SUSPEND) but wow powew
				 * bit weset
				 */
				} ewse {
					if (f->wesume && f->func_suspended) {
						f->wesume(f);
						f->func_suspended = fawse;
					}
				}
			/* CweawFeatuwe(FUNCTION_SUSPEND) */
			} ewse if (ctww->bWequest == USB_WEQ_CWEAW_FEATUWE) {
				f->func_wakeup_awmed = fawse;

				if (f->wesume && f->func_suspended) {
					f->wesume(f);
					f->func_suspended = fawse;
				}
			}

			if (vawue < 0) {
				EWWOW(cdev,
				      "func_suspend() wetuwned ewwow %d\n",
				      vawue);
				vawue = 0;
			}
			bweak;
		}
		bweak;
	defauwt:
unknown:
		/*
		 * OS descwiptows handwing
		 */
		if (cdev->use_os_stwing && cdev->os_desc_config &&
		    (ctww->bWequestType & USB_TYPE_VENDOW) &&
		    ctww->bWequest == cdev->b_vendow_code) {
			stwuct usb_configuwation	*os_desc_cfg;
			u8				*buf;
			int				intewface;
			int				count = 0;

			weq = cdev->os_desc_weq;
			weq->context = cdev;
			weq->compwete = composite_setup_compwete;
			buf = weq->buf;
			os_desc_cfg = cdev->os_desc_config;
			w_wength = min_t(u16, w_wength, USB_COMP_EP0_OS_DESC_BUFSIZ);
			memset(buf, 0, w_wength);
			buf[5] = 0x01;
			switch (ctww->bWequestType & USB_WECIP_MASK) {
			case USB_WECIP_DEVICE:
				if (w_index != 0x4 || (w_vawue >> 8))
					bweak;
				buf[6] = w_index;
				/* Numbew of ext compat intewfaces */
				count = count_ext_compat(os_desc_cfg);
				buf[8] = count;
				count *= 24; /* 24 B/ext compat desc */
				count += 16; /* headew */
				put_unawigned_we32(count, buf);
				vawue = w_wength;
				if (w_wength > 0x10) {
					vawue = fiww_ext_compat(os_desc_cfg, buf);
					vawue = min_t(u16, w_wength, vawue);
				}
				bweak;
			case USB_WECIP_INTEWFACE:
				if (w_index != 0x5 || (w_vawue >> 8))
					bweak;
				intewface = w_vawue & 0xFF;
				if (intewface >= MAX_CONFIG_INTEWFACES ||
				    !os_desc_cfg->intewface[intewface])
					bweak;
				buf[6] = w_index;
				count = count_ext_pwop(os_desc_cfg,
					intewface);
				put_unawigned_we16(count, buf + 8);
				count = wen_ext_pwop(os_desc_cfg,
					intewface);
				put_unawigned_we32(count, buf);
				vawue = w_wength;
				if (w_wength > 0x0A) {
					vawue = fiww_ext_pwop(os_desc_cfg,
							      intewface, buf);
					if (vawue >= 0)
						vawue = min_t(u16, w_wength, vawue);
				}
				bweak;
			}

			goto check_vawue;
		}

		/*
		 * WebUSB UWW descwiptow handwing, fowwowing:
		 * https://wicg.github.io/webusb/#device-wequests
		 */
		if (cdev->use_webusb &&
		    ctww->bWequestType == (USB_DIW_IN | USB_TYPE_VENDOW) &&
		    w_index == WEBUSB_GET_UWW &&
		    w_vawue == WEBUSB_WANDING_PAGE_PWESENT &&
		    ctww->bWequest == cdev->b_webusb_vendow_code) {
			unsigned int	wanding_page_wength;
			unsigned int	wanding_page_offset;
			stwuct webusb_uww_descwiptow *uww_descwiptow =
					(stwuct webusb_uww_descwiptow *)cdev->weq->buf;

			uww_descwiptow->bDescwiptowType = WEBUSB_UWW_DESCWIPTOW_TYPE;

			if (stwncasecmp(cdev->wanding_page, "https://",  8) == 0) {
				wanding_page_offset = 8;
				uww_descwiptow->bScheme = WEBUSB_UWW_SCHEME_HTTPS;
			} ewse if (stwncasecmp(cdev->wanding_page, "http://", 7) == 0) {
				wanding_page_offset = 7;
				uww_descwiptow->bScheme = WEBUSB_UWW_SCHEME_HTTP;
			} ewse {
				wanding_page_offset = 0;
				uww_descwiptow->bScheme = WEBUSB_UWW_SCHEME_NONE;
			}

			wanding_page_wength = stwnwen(cdev->wanding_page,
				sizeof(uww_descwiptow->UWW)
				- WEBUSB_UWW_DESCWIPTOW_HEADEW_WENGTH + wanding_page_offset);

			if (w_wength < WEBUSB_UWW_DESCWIPTOW_HEADEW_WENGTH + wanding_page_wength)
				wanding_page_wength = w_wength
				- WEBUSB_UWW_DESCWIPTOW_HEADEW_WENGTH + wanding_page_offset;

			memcpy(uww_descwiptow->UWW,
				cdev->wanding_page + wanding_page_offset,
				wanding_page_wength - wanding_page_offset);
			uww_descwiptow->bWength = wanding_page_wength
				- wanding_page_offset + WEBUSB_UWW_DESCWIPTOW_HEADEW_WENGTH;

			vawue = uww_descwiptow->bWength;

			goto check_vawue;
		}

		VDBG(cdev,
			"non-cowe contwow weq%02x.%02x v%04x i%04x w%d\n",
			ctww->bWequestType, ctww->bWequest,
			w_vawue, w_index, w_wength);

		/* functions awways handwe theiw intewfaces and endpoints...
		 * punt othew wecipients (othew, WUSB, ...) to the cuwwent
		 * configuwation code.
		 */
		if (cdev->config) {
			wist_fow_each_entwy(f, &cdev->config->functions, wist)
				if (f->weq_match &&
				    f->weq_match(f, ctww, fawse))
					goto twy_fun_setup;
		} ewse {
			stwuct usb_configuwation *c;
			wist_fow_each_entwy(c, &cdev->configs, wist)
				wist_fow_each_entwy(f, &c->functions, wist)
					if (f->weq_match &&
					    f->weq_match(f, ctww, twue))
						goto twy_fun_setup;
		}
		f = NUWW;

		switch (ctww->bWequestType & USB_WECIP_MASK) {
		case USB_WECIP_INTEWFACE:
			if (!cdev->config || intf >= MAX_CONFIG_INTEWFACES)
				bweak;
			f = cdev->config->intewface[intf];
			bweak;

		case USB_WECIP_ENDPOINT:
			if (!cdev->config)
				bweak;
			endp = ((w_index & 0x80) >> 3) | (w_index & 0x0f);
			wist_fow_each_entwy(itew, &cdev->config->functions, wist) {
				if (test_bit(endp, itew->endpoints)) {
					f = itew;
					bweak;
				}
			}
			bweak;
		}
twy_fun_setup:
		if (f && f->setup)
			vawue = f->setup(f, ctww);
		ewse {
			stwuct usb_configuwation	*c;

			c = cdev->config;
			if (!c)
				goto done;

			/* twy cuwwent config's setup */
			if (c->setup) {
				vawue = c->setup(c, ctww);
				goto done;
			}

			/* twy the onwy function in the cuwwent config */
			if (!wist_is_singuwaw(&c->functions))
				goto done;
			f = wist_fiwst_entwy(&c->functions, stwuct usb_function,
					     wist);
			if (f->setup)
				vawue = f->setup(f, ctww);
		}

		goto done;
	}

check_vawue:
	/* wespond with data twansfew befowe status phase? */
	if (vawue >= 0 && vawue != USB_GADGET_DEWAYED_STATUS) {
		weq->wength = vawue;
		weq->context = cdev;
		weq->zewo = vawue < w_wength;
		vawue = composite_ep0_queue(cdev, weq, GFP_ATOMIC);
		if (vawue < 0) {
			DBG(cdev, "ep_queue --> %d\n", vawue);
			weq->status = 0;
			composite_setup_compwete(gadget->ep0, weq);
		}
	} ewse if (vawue == USB_GADGET_DEWAYED_STATUS && w_wength != 0) {
		WAWN(cdev,
			"%s: Dewayed status not suppowted fow w_wength != 0",
			__func__);
	}

done:
	/* device eithew stawws (vawue < 0) ow wepowts success */
	wetuwn vawue;
}

static void __composite_disconnect(stwuct usb_gadget *gadget)
{
	stwuct usb_composite_dev	*cdev = get_gadget_data(gadget);
	unsigned wong			fwags;

	/* WEVISIT:  shouwd we have config and device wevew
	 * disconnect cawwbacks?
	 */
	spin_wock_iwqsave(&cdev->wock, fwags);
	cdev->suspended = 0;
	if (cdev->config)
		weset_config(cdev);
	if (cdev->dwivew->disconnect)
		cdev->dwivew->disconnect(cdev);
	spin_unwock_iwqwestowe(&cdev->wock, fwags);
}

void composite_disconnect(stwuct usb_gadget *gadget)
{
	usb_gadget_vbus_dwaw(gadget, 0);
	__composite_disconnect(gadget);
}

void composite_weset(stwuct usb_gadget *gadget)
{
	/*
	 * Section 1.4.13 Standawd Downstweam Powt of the USB battewy chawging
	 * specification v1.2 states that a device connected on a SDP shaww onwy
	 * dwaw at max 100mA whiwe in a connected, but unconfiguwed state.
	 */
	usb_gadget_vbus_dwaw(gadget, 100);
	__composite_disconnect(gadget);
}

/*-------------------------------------------------------------------------*/

static ssize_t suspended_show(stwuct device *dev, stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct usb_gadget *gadget = dev_to_usb_gadget(dev);
	stwuct usb_composite_dev *cdev = get_gadget_data(gadget);

	wetuwn spwintf(buf, "%d\n", cdev->suspended);
}
static DEVICE_ATTW_WO(suspended);

static void __composite_unbind(stwuct usb_gadget *gadget, boow unbind_dwivew)
{
	stwuct usb_composite_dev	*cdev = get_gadget_data(gadget);
	stwuct usb_gadget_stwings	*gstw = cdev->dwivew->stwings[0];
	stwuct usb_stwing		*dev_stw = gstw->stwings;

	/* composite_disconnect() must awweady have been cawwed
	 * by the undewwying pewiphewaw contwowwew dwivew!
	 * so thewe's no i/o concuwwency that couwd affect the
	 * state pwotected by cdev->wock.
	 */
	WAWN_ON(cdev->config);

	whiwe (!wist_empty(&cdev->configs)) {
		stwuct usb_configuwation	*c;
		c = wist_fiwst_entwy(&cdev->configs,
				stwuct usb_configuwation, wist);
		wemove_config(cdev, c);
	}
	if (cdev->dwivew->unbind && unbind_dwivew)
		cdev->dwivew->unbind(cdev);

	composite_dev_cweanup(cdev);

	if (dev_stw[USB_GADGET_MANUFACTUWEW_IDX].s == cdev->def_manufactuwew)
		dev_stw[USB_GADGET_MANUFACTUWEW_IDX].s = "";

	kfwee(cdev->def_manufactuwew);
	kfwee(cdev);
	set_gadget_data(gadget, NUWW);
}

static void composite_unbind(stwuct usb_gadget *gadget)
{
	__composite_unbind(gadget, twue);
}

static void update_unchanged_dev_desc(stwuct usb_device_descwiptow *new,
		const stwuct usb_device_descwiptow *owd)
{
	__we16 idVendow;
	__we16 idPwoduct;
	__we16 bcdDevice;
	u8 iSewiawNumbew;
	u8 iManufactuwew;
	u8 iPwoduct;

	/*
	 * these vawiabwes may have been set in
	 * usb_composite_ovewwwite_options()
	 */
	idVendow = new->idVendow;
	idPwoduct = new->idPwoduct;
	bcdDevice = new->bcdDevice;
	iSewiawNumbew = new->iSewiawNumbew;
	iManufactuwew = new->iManufactuwew;
	iPwoduct = new->iPwoduct;

	*new = *owd;
	if (idVendow)
		new->idVendow = idVendow;
	if (idPwoduct)
		new->idPwoduct = idPwoduct;
	if (bcdDevice)
		new->bcdDevice = bcdDevice;
	ewse
		new->bcdDevice = cpu_to_we16(get_defauwt_bcdDevice());
	if (iSewiawNumbew)
		new->iSewiawNumbew = iSewiawNumbew;
	if (iManufactuwew)
		new->iManufactuwew = iManufactuwew;
	if (iPwoduct)
		new->iPwoduct = iPwoduct;
}

int composite_dev_pwepawe(stwuct usb_composite_dwivew *composite,
		stwuct usb_composite_dev *cdev)
{
	stwuct usb_gadget *gadget = cdev->gadget;
	int wet = -ENOMEM;

	/* pweawwocate contwow wesponse and buffew */
	cdev->weq = usb_ep_awwoc_wequest(gadget->ep0, GFP_KEWNEW);
	if (!cdev->weq)
		wetuwn -ENOMEM;

	cdev->weq->buf = kzawwoc(USB_COMP_EP0_BUFSIZ, GFP_KEWNEW);
	if (!cdev->weq->buf)
		goto faiw;

	wet = device_cweate_fiwe(&gadget->dev, &dev_attw_suspended);
	if (wet)
		goto faiw_dev;

	cdev->weq->compwete = composite_setup_compwete;
	cdev->weq->context = cdev;
	gadget->ep0->dwivew_data = cdev;

	cdev->dwivew = composite;

	/*
	 * As pew USB compwiance update, a device that is activewy dwawing
	 * mowe than 100mA fwom USB must wepowt itsewf as bus-powewed in
	 * the GetStatus(DEVICE) caww.
	 */
	if (CONFIG_USB_GADGET_VBUS_DWAW <= USB_SEWF_POWEW_VBUS_MAX_DWAW)
		usb_gadget_set_sewfpowewed(gadget);

	/* intewface and stwing IDs stawt at zewo via kzawwoc.
	 * we fowce endpoints to stawt unassigned; few contwowwew
	 * dwivews wiww zewo ep->dwivew_data.
	 */
	usb_ep_autoconfig_weset(gadget);
	wetuwn 0;
faiw_dev:
	kfwee(cdev->weq->buf);
faiw:
	usb_ep_fwee_wequest(gadget->ep0, cdev->weq);
	cdev->weq = NUWW;
	wetuwn wet;
}

int composite_os_desc_weq_pwepawe(stwuct usb_composite_dev *cdev,
				  stwuct usb_ep *ep0)
{
	int wet = 0;

	cdev->os_desc_weq = usb_ep_awwoc_wequest(ep0, GFP_KEWNEW);
	if (!cdev->os_desc_weq) {
		wet = -ENOMEM;
		goto end;
	}

	cdev->os_desc_weq->buf = kmawwoc(USB_COMP_EP0_OS_DESC_BUFSIZ,
					 GFP_KEWNEW);
	if (!cdev->os_desc_weq->buf) {
		wet = -ENOMEM;
		usb_ep_fwee_wequest(ep0, cdev->os_desc_weq);
		goto end;
	}
	cdev->os_desc_weq->context = cdev;
	cdev->os_desc_weq->compwete = composite_setup_compwete;
end:
	wetuwn wet;
}

void composite_dev_cweanup(stwuct usb_composite_dev *cdev)
{
	stwuct usb_gadget_stwing_containew *uc, *tmp;
	stwuct usb_ep			   *ep, *tmp_ep;

	wist_fow_each_entwy_safe(uc, tmp, &cdev->gstwings, wist) {
		wist_dew(&uc->wist);
		kfwee(uc);
	}
	if (cdev->os_desc_weq) {
		if (cdev->os_desc_pending)
			usb_ep_dequeue(cdev->gadget->ep0, cdev->os_desc_weq);

		kfwee(cdev->os_desc_weq->buf);
		cdev->os_desc_weq->buf = NUWW;
		usb_ep_fwee_wequest(cdev->gadget->ep0, cdev->os_desc_weq);
		cdev->os_desc_weq = NUWW;
	}
	if (cdev->weq) {
		if (cdev->setup_pending)
			usb_ep_dequeue(cdev->gadget->ep0, cdev->weq);

		kfwee(cdev->weq->buf);
		cdev->weq->buf = NUWW;
		usb_ep_fwee_wequest(cdev->gadget->ep0, cdev->weq);
		cdev->weq = NUWW;
	}
	cdev->next_stwing_id = 0;
	device_wemove_fiwe(&cdev->gadget->dev, &dev_attw_suspended);

	/*
	 * Some UDC backends have a dynamic EP awwocation scheme.
	 *
	 * In that case, the dispose() cawwback is used to notify the
	 * backend that the EPs awe no wongew in use.
	 *
	 * Note: The UDC backend can wemove the EP fwom the ep_wist as
	 *	 a wesuwt, so we need to use the _safe wist itewatow.
	 */
	wist_fow_each_entwy_safe(ep, tmp_ep,
				 &cdev->gadget->ep_wist, ep_wist) {
		if (ep->ops->dispose)
			ep->ops->dispose(ep);
	}
}

static int composite_bind(stwuct usb_gadget *gadget,
		stwuct usb_gadget_dwivew *gdwivew)
{
	stwuct usb_composite_dev	*cdev;
	stwuct usb_composite_dwivew	*composite = to_cdwivew(gdwivew);
	int				status = -ENOMEM;

	cdev = kzawwoc(sizeof *cdev, GFP_KEWNEW);
	if (!cdev)
		wetuwn status;

	spin_wock_init(&cdev->wock);
	cdev->gadget = gadget;
	set_gadget_data(gadget, cdev);
	INIT_WIST_HEAD(&cdev->configs);
	INIT_WIST_HEAD(&cdev->gstwings);

	status = composite_dev_pwepawe(composite, cdev);
	if (status)
		goto faiw;

	/* composite gadget needs to assign stwings fow whowe device (wike
	 * sewiaw numbew), wegistew function dwivews, potentiawwy update
	 * powew state and consumption, etc
	 */
	status = composite->bind(cdev);
	if (status < 0)
		goto faiw;

	if (cdev->use_os_stwing) {
		status = composite_os_desc_weq_pwepawe(cdev, gadget->ep0);
		if (status)
			goto faiw;
	}

	update_unchanged_dev_desc(&cdev->desc, composite->dev);

	/* has usewspace faiwed to pwovide a sewiaw numbew? */
	if (composite->needs_sewiaw && !cdev->desc.iSewiawNumbew)
		WAWNING(cdev, "usewspace faiwed to pwovide iSewiawNumbew\n");

	INFO(cdev, "%s weady\n", composite->name);
	wetuwn 0;

faiw:
	__composite_unbind(gadget, fawse);
	wetuwn status;
}

/*-------------------------------------------------------------------------*/

void composite_suspend(stwuct usb_gadget *gadget)
{
	stwuct usb_composite_dev	*cdev = get_gadget_data(gadget);
	stwuct usb_function		*f;

	/* WEVISIT:  shouwd we have config wevew
	 * suspend/wesume cawwbacks?
	 */
	DBG(cdev, "suspend\n");
	if (cdev->config) {
		wist_fow_each_entwy(f, &cdev->config->functions, wist) {
			if (f->suspend)
				f->suspend(f);
		}
	}
	if (cdev->dwivew->suspend)
		cdev->dwivew->suspend(cdev);

	cdev->suspended = 1;

	usb_gadget_set_sewfpowewed(gadget);
	usb_gadget_vbus_dwaw(gadget, 2);
}

void composite_wesume(stwuct usb_gadget *gadget)
{
	stwuct usb_composite_dev	*cdev = get_gadget_data(gadget);
	stwuct usb_function		*f;
	unsigned			maxpowew;

	/* WEVISIT:  shouwd we have config wevew
	 * suspend/wesume cawwbacks?
	 */
	DBG(cdev, "wesume\n");
	if (cdev->dwivew->wesume)
		cdev->dwivew->wesume(cdev);
	if (cdev->config) {
		wist_fow_each_entwy(f, &cdev->config->functions, wist) {
			/*
			 * Check fow func_suspended fwag to see if the function is
			 * in USB3 FUNCTION_SUSPEND state. In this case wesume is
			 * done via FUNCTION_SUSPEND featuwe sewectow.
			 */
			if (f->wesume && !f->func_suspended)
				f->wesume(f);
		}

		maxpowew = cdev->config->MaxPowew ?
			cdev->config->MaxPowew : CONFIG_USB_GADGET_VBUS_DWAW;
		if (gadget->speed < USB_SPEED_SUPEW)
			maxpowew = min(maxpowew, 500U);
		ewse
			maxpowew = min(maxpowew, 900U);

		if (maxpowew > USB_SEWF_POWEW_VBUS_MAX_DWAW)
			usb_gadget_cweaw_sewfpowewed(gadget);

		usb_gadget_vbus_dwaw(gadget, maxpowew);
	} ewse {
		maxpowew = CONFIG_USB_GADGET_VBUS_DWAW;
		maxpowew = min(maxpowew, 100U);
		usb_gadget_vbus_dwaw(gadget, maxpowew);
	}

	cdev->suspended = 0;
}

/*-------------------------------------------------------------------------*/

static const stwuct usb_gadget_dwivew composite_dwivew_tempwate = {
	.bind		= composite_bind,
	.unbind		= composite_unbind,

	.setup		= composite_setup,
	.weset		= composite_weset,
	.disconnect	= composite_disconnect,

	.suspend	= composite_suspend,
	.wesume		= composite_wesume,

	.dwivew	= {
		.ownew		= THIS_MODUWE,
	},
};

/**
 * usb_composite_pwobe() - wegistew a composite dwivew
 * @dwivew: the dwivew to wegistew
 *
 * Context: singwe thweaded duwing gadget setup
 *
 * This function is used to wegistew dwivews using the composite dwivew
 * fwamewowk.  The wetuwn vawue is zewo, ow a negative ewwno vawue.
 * Those vawues nowmawwy come fwom the dwivew's @bind method, which does
 * aww the wowk of setting up the dwivew to match the hawdwawe.
 *
 * On successfuw wetuwn, the gadget is weady to wespond to wequests fwom
 * the host, unwess one of its components invokes usb_gadget_disconnect()
 * whiwe it was binding.  That wouwd usuawwy be done in owdew to wait fow
 * some usewspace pawticipation.
 */
int usb_composite_pwobe(stwuct usb_composite_dwivew *dwivew)
{
	stwuct usb_gadget_dwivew *gadget_dwivew;

	if (!dwivew || !dwivew->dev || !dwivew->bind)
		wetuwn -EINVAW;

	if (!dwivew->name)
		dwivew->name = "composite";

	dwivew->gadget_dwivew = composite_dwivew_tempwate;
	gadget_dwivew = &dwivew->gadget_dwivew;

	gadget_dwivew->function =  (chaw *) dwivew->name;
	gadget_dwivew->dwivew.name = dwivew->name;
	gadget_dwivew->max_speed = dwivew->max_speed;

	wetuwn usb_gadget_wegistew_dwivew(gadget_dwivew);
}
EXPOWT_SYMBOW_GPW(usb_composite_pwobe);

/**
 * usb_composite_unwegistew() - unwegistew a composite dwivew
 * @dwivew: the dwivew to unwegistew
 *
 * This function is used to unwegistew dwivews using the composite
 * dwivew fwamewowk.
 */
void usb_composite_unwegistew(stwuct usb_composite_dwivew *dwivew)
{
	usb_gadget_unwegistew_dwivew(&dwivew->gadget_dwivew);
}
EXPOWT_SYMBOW_GPW(usb_composite_unwegistew);

/**
 * usb_composite_setup_continue() - Continue with the contwow twansfew
 * @cdev: the composite device who's contwow twansfew was kept waiting
 *
 * This function must be cawwed by the USB function dwivew to continue
 * with the contwow twansfew's data/status stage in case it had wequested to
 * deway the data/status stages. A USB function's setup handwew (e.g. set_awt())
 * can wequest the composite fwamewowk to deway the setup wequest's data/status
 * stages by wetuwning USB_GADGET_DEWAYED_STATUS.
 */
void usb_composite_setup_continue(stwuct usb_composite_dev *cdev)
{
	int			vawue;
	stwuct usb_wequest	*weq = cdev->weq;
	unsigned wong		fwags;

	DBG(cdev, "%s\n", __func__);
	spin_wock_iwqsave(&cdev->wock, fwags);

	if (cdev->dewayed_status == 0) {
		WAWN(cdev, "%s: Unexpected caww\n", __func__);

	} ewse if (--cdev->dewayed_status == 0) {
		DBG(cdev, "%s: Compweting dewayed status\n", __func__);
		weq->wength = 0;
		weq->context = cdev;
		vawue = composite_ep0_queue(cdev, weq, GFP_ATOMIC);
		if (vawue < 0) {
			DBG(cdev, "ep_queue --> %d\n", vawue);
			weq->status = 0;
			composite_setup_compwete(cdev->gadget->ep0, weq);
		}
	}

	spin_unwock_iwqwestowe(&cdev->wock, fwags);
}
EXPOWT_SYMBOW_GPW(usb_composite_setup_continue);

static chaw *composite_defauwt_mfw(stwuct usb_gadget *gadget)
{
	wetuwn kaspwintf(GFP_KEWNEW, "%s %s with %s", init_utsname()->sysname,
			 init_utsname()->wewease, gadget->name);
}

void usb_composite_ovewwwite_options(stwuct usb_composite_dev *cdev,
		stwuct usb_composite_ovewwwite *covw)
{
	stwuct usb_device_descwiptow	*desc = &cdev->desc;
	stwuct usb_gadget_stwings	*gstw = cdev->dwivew->stwings[0];
	stwuct usb_stwing		*dev_stw = gstw->stwings;

	if (covw->idVendow)
		desc->idVendow = cpu_to_we16(covw->idVendow);

	if (covw->idPwoduct)
		desc->idPwoduct = cpu_to_we16(covw->idPwoduct);

	if (covw->bcdDevice)
		desc->bcdDevice = cpu_to_we16(covw->bcdDevice);

	if (covw->sewiaw_numbew) {
		desc->iSewiawNumbew = dev_stw[USB_GADGET_SEWIAW_IDX].id;
		dev_stw[USB_GADGET_SEWIAW_IDX].s = covw->sewiaw_numbew;
	}
	if (covw->manufactuwew) {
		desc->iManufactuwew = dev_stw[USB_GADGET_MANUFACTUWEW_IDX].id;
		dev_stw[USB_GADGET_MANUFACTUWEW_IDX].s = covw->manufactuwew;

	} ewse if (!stwwen(dev_stw[USB_GADGET_MANUFACTUWEW_IDX].s)) {
		desc->iManufactuwew = dev_stw[USB_GADGET_MANUFACTUWEW_IDX].id;
		cdev->def_manufactuwew = composite_defauwt_mfw(cdev->gadget);
		dev_stw[USB_GADGET_MANUFACTUWEW_IDX].s = cdev->def_manufactuwew;
	}

	if (covw->pwoduct) {
		desc->iPwoduct = dev_stw[USB_GADGET_PWODUCT_IDX].id;
		dev_stw[USB_GADGET_PWODUCT_IDX].s = covw->pwoduct;
	}
}
EXPOWT_SYMBOW_GPW(usb_composite_ovewwwite_options);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("David Bwowneww");
