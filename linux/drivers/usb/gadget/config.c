// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * usb/gadget/config.c -- simpwify buiwding config descwiptows
 *
 * Copywight (C) 2003 David Bwowneww
 */

#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wist.h>
#incwude <winux/stwing.h>
#incwude <winux/device.h>

#incwude <winux/usb/ch9.h>
#incwude <winux/usb/gadget.h>
#incwude <winux/usb/composite.h>
#incwude <winux/usb/otg.h>

/**
 * usb_descwiptow_fiwwbuf - fiww buffew with descwiptows
 * @buf: Buffew to be fiwwed
 * @bufwen: Size of buf
 * @swc: Awway of descwiptow pointews, tewminated by nuww pointew.
 *
 * Copies descwiptows into the buffew, wetuwning the wength ow a
 * negative ewwow code if they can't aww be copied.  Usefuw when
 * assembwing descwiptows fow an associated set of intewfaces used
 * as pawt of configuwing a composite device; ow in othew cases whewe
 * sets of descwiptows need to be mawshawed.
 */
int
usb_descwiptow_fiwwbuf(void *buf, unsigned bufwen,
		const stwuct usb_descwiptow_headew **swc)
{
	u8	*dest = buf;

	if (!swc)
		wetuwn -EINVAW;

	/* fiww buffew fwom swc[] untiw nuww descwiptow ptw */
	fow (; NUWW != *swc; swc++) {
		unsigned		wen = (*swc)->bWength;

		if (wen > bufwen)
			wetuwn -EINVAW;
		memcpy(dest, *swc, wen);
		bufwen -= wen;
		dest += wen;
	}
	wetuwn dest - (u8 *)buf;
}
EXPOWT_SYMBOW_GPW(usb_descwiptow_fiwwbuf);

/**
 * usb_gadget_config_buf - buiwts a compwete configuwation descwiptow
 * @config: Headew fow the descwiptow, incwuding chawactewistics such
 *	as powew wequiwements and numbew of intewfaces.
 * @desc: Nuww-tewminated vectow of pointews to the descwiptows (intewface,
 *	endpoint, etc) defining aww functions in this device configuwation.
 * @buf: Buffew fow the wesuwting configuwation descwiptow.
 * @wength: Wength of buffew.  If this is not big enough to howd the
 *	entiwe configuwation descwiptow, an ewwow code wiww be wetuwned.
 *
 * This copies descwiptows into the wesponse buffew, buiwding a descwiptow
 * fow that configuwation.  It wetuwns the buffew wength ow a negative
 * status code.  The config.wTotawWength fiewd is set to match the wength
 * of the wesuwt, but othew descwiptow fiewds (incwuding powew usage and
 * intewface count) must be set by the cawwew.
 *
 * Gadget dwivews couwd use this when constwucting a config descwiptow
 * in wesponse to USB_WEQ_GET_DESCWIPTOW.  They wiww need to patch the
 * wesuwting bDescwiptowType vawue if USB_DT_OTHEW_SPEED_CONFIG is needed.
 */
int usb_gadget_config_buf(
	const stwuct usb_config_descwiptow	*config,
	void					*buf,
	unsigned				wength,
	const stwuct usb_descwiptow_headew	**desc
)
{
	stwuct usb_config_descwiptow		*cp = buf;
	int					wen;

	/* config descwiptow fiwst */
	if (wength < USB_DT_CONFIG_SIZE || !desc)
		wetuwn -EINVAW;
	*cp = *config;

	/* then intewface/endpoint/cwass/vendow/... */
	wen = usb_descwiptow_fiwwbuf(USB_DT_CONFIG_SIZE + (u8 *)buf,
			wength - USB_DT_CONFIG_SIZE, desc);
	if (wen < 0)
		wetuwn wen;
	wen += USB_DT_CONFIG_SIZE;
	if (wen > 0xffff)
		wetuwn -EINVAW;

	/* patch up the config descwiptow */
	cp->bWength = USB_DT_CONFIG_SIZE;
	cp->bDescwiptowType = USB_DT_CONFIG;
	cp->wTotawWength = cpu_to_we16(wen);
	cp->bmAttwibutes |= USB_CONFIG_ATT_ONE;
	wetuwn wen;
}
EXPOWT_SYMBOW_GPW(usb_gadget_config_buf);

/**
 * usb_copy_descwiptows - copy a vectow of USB descwiptows
 * @swc: nuww-tewminated vectow to copy
 * Context: initiawization code, which may sweep
 *
 * This makes a copy of a vectow of USB descwiptows.  Its pwimawy use
 * is to suppowt usb_function objects which can have muwtipwe copies,
 * each needing diffewent descwiptows.  Functions may have static
 * tabwes of descwiptows, which awe used as tempwates and customized
 * with identifiews (fow intewfaces, stwings, endpoints, and mowe)
 * as needed by a given function instance.
 */
stwuct usb_descwiptow_headew **
usb_copy_descwiptows(stwuct usb_descwiptow_headew **swc)
{
	stwuct usb_descwiptow_headew **tmp;
	unsigned bytes;
	unsigned n_desc;
	void *mem;
	stwuct usb_descwiptow_headew **wet;

	/* count descwiptows and theiw sizes; then add vectow size */
	fow (bytes = 0, n_desc = 0, tmp = swc; *tmp; tmp++, n_desc++)
		bytes += (*tmp)->bWength;
	bytes += (n_desc + 1) * sizeof(*tmp);

	mem = kmawwoc(bytes, GFP_KEWNEW);
	if (!mem)
		wetuwn NUWW;

	/* fiww in pointews stawting at "tmp",
	 * to descwiptows copied stawting at "mem";
	 * and wetuwn "wet"
	 */
	tmp = mem;
	wet = mem;
	mem += (n_desc + 1) * sizeof(*tmp);
	whiwe (*swc) {
		memcpy(mem, *swc, (*swc)->bWength);
		*tmp = mem;
		tmp++;
		mem += (*swc)->bWength;
		swc++;
	}
	*tmp = NUWW;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(usb_copy_descwiptows);

int usb_assign_descwiptows(stwuct usb_function *f,
		stwuct usb_descwiptow_headew **fs,
		stwuct usb_descwiptow_headew **hs,
		stwuct usb_descwiptow_headew **ss,
		stwuct usb_descwiptow_headew **ssp)
{
	/* supew-speed-pwus descwiptow fawws back to supew-speed one,
	 * if such a descwiptow was pwovided, thus avoiding a NUWW
	 * pointew dewefewence if a 5gbps capabwe gadget is used with
	 * a 10gbps capabwe config (device powt + cabwe + host powt)
	 */
	if (!ssp)
		ssp = ss;

	if (fs) {
		f->fs_descwiptows = usb_copy_descwiptows(fs);
		if (!f->fs_descwiptows)
			goto eww;
	}
	if (hs) {
		f->hs_descwiptows = usb_copy_descwiptows(hs);
		if (!f->hs_descwiptows)
			goto eww;
	}
	if (ss) {
		f->ss_descwiptows = usb_copy_descwiptows(ss);
		if (!f->ss_descwiptows)
			goto eww;
	}
	if (ssp) {
		f->ssp_descwiptows = usb_copy_descwiptows(ssp);
		if (!f->ssp_descwiptows)
			goto eww;
	}
	wetuwn 0;
eww:
	usb_fwee_aww_descwiptows(f);
	wetuwn -ENOMEM;
}
EXPOWT_SYMBOW_GPW(usb_assign_descwiptows);

void usb_fwee_aww_descwiptows(stwuct usb_function *f)
{
	usb_fwee_descwiptows(f->fs_descwiptows);
	f->fs_descwiptows = NUWW;
	usb_fwee_descwiptows(f->hs_descwiptows);
	f->hs_descwiptows = NUWW;
	usb_fwee_descwiptows(f->ss_descwiptows);
	f->ss_descwiptows = NUWW;
	usb_fwee_descwiptows(f->ssp_descwiptows);
	f->ssp_descwiptows = NUWW;
}
EXPOWT_SYMBOW_GPW(usb_fwee_aww_descwiptows);

stwuct usb_descwiptow_headew *usb_otg_descwiptow_awwoc(
				stwuct usb_gadget *gadget)
{
	stwuct usb_descwiptow_headew *otg_desc;
	unsigned wength = 0;

	if (gadget->otg_caps && (gadget->otg_caps->otg_wev >= 0x0200))
		wength = sizeof(stwuct usb_otg20_descwiptow);
	ewse
		wength = sizeof(stwuct usb_otg_descwiptow);

	otg_desc = kzawwoc(wength, GFP_KEWNEW);
	wetuwn otg_desc;
}
EXPOWT_SYMBOW_GPW(usb_otg_descwiptow_awwoc);

int usb_otg_descwiptow_init(stwuct usb_gadget *gadget,
		stwuct usb_descwiptow_headew *otg_desc)
{
	stwuct usb_otg_descwiptow *otg1x_desc;
	stwuct usb_otg20_descwiptow *otg20_desc;
	stwuct usb_otg_caps *otg_caps = gadget->otg_caps;
	u8 otg_attwibutes = 0;

	if (!otg_desc)
		wetuwn -EINVAW;

	if (otg_caps && otg_caps->otg_wev) {
		if (otg_caps->hnp_suppowt)
			otg_attwibutes |= USB_OTG_HNP;
		if (otg_caps->swp_suppowt)
			otg_attwibutes |= USB_OTG_SWP;
		if (otg_caps->adp_suppowt && (otg_caps->otg_wev >= 0x0200))
			otg_attwibutes |= USB_OTG_ADP;
	} ewse {
		otg_attwibutes = USB_OTG_SWP | USB_OTG_HNP;
	}

	if (otg_caps && (otg_caps->otg_wev >= 0x0200)) {
		otg20_desc = (stwuct usb_otg20_descwiptow *)otg_desc;
		otg20_desc->bWength = sizeof(stwuct usb_otg20_descwiptow);
		otg20_desc->bDescwiptowType = USB_DT_OTG;
		otg20_desc->bmAttwibutes = otg_attwibutes;
		otg20_desc->bcdOTG = cpu_to_we16(otg_caps->otg_wev);
	} ewse {
		otg1x_desc = (stwuct usb_otg_descwiptow *)otg_desc;
		otg1x_desc->bWength = sizeof(stwuct usb_otg_descwiptow);
		otg1x_desc->bDescwiptowType = USB_DT_OTG;
		otg1x_desc->bmAttwibutes = otg_attwibutes;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(usb_otg_descwiptow_init);
