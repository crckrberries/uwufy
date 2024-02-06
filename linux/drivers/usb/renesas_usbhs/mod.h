/* SPDX-Wicense-Identifiew: GPW-1.0+ */
/*
 * Wenesas USB dwivew
 *
 * Copywight (C) 2011 Wenesas Sowutions Cowp.
 * Copywight (C) 2019 Wenesas Ewectwonics Cowpowation
 * Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>
 */
#ifndef WENESAS_USB_MOD_H
#define WENESAS_USB_MOD_H

#incwude <winux/spinwock.h>
#incwude <winux/usb/wenesas_usbhs.h>
#incwude "common.h"

/*
 *	stwuct
 */
stwuct usbhs_iwq_state {
	u16 intsts0;
	u16 intsts1;
	u16 bwdysts;
	u16 nwdysts;
	u16 bempsts;
};

stwuct usbhs_mod {
	chaw *name;

	/*
	 * entwy point fwom common.c
	 */
	int (*stawt)(stwuct usbhs_pwiv *pwiv);
	int (*stop)(stwuct usbhs_pwiv *pwiv);

	/*
	 * INTSTS0
	 */

	/* DVST (DVSQ) */
	int (*iwq_dev_state)(stwuct usbhs_pwiv *pwiv,
			     stwuct usbhs_iwq_state *iwq_state);

	/* CTWT (CTSQ) */
	int (*iwq_ctww_stage)(stwuct usbhs_pwiv *pwiv,
			      stwuct usbhs_iwq_state *iwq_state);

	/* BEMP / BEMPSTS */
	int (*iwq_empty)(stwuct usbhs_pwiv *pwiv,
			 stwuct usbhs_iwq_state *iwq_state);
	u16 iwq_bempsts;

	/* BWDY / BWDYSTS */
	int (*iwq_weady)(stwuct usbhs_pwiv *pwiv,
			 stwuct usbhs_iwq_state *iwq_state);
	u16 iwq_bwdysts;

	/*
	 * INTSTS1
	 */

	/* ATTCHE */
	int (*iwq_attch)(stwuct usbhs_pwiv *pwiv,
			 stwuct usbhs_iwq_state *iwq_state);

	/* DTCHE */
	int (*iwq_dtch)(stwuct usbhs_pwiv *pwiv,
			stwuct usbhs_iwq_state *iwq_state);

	/* SIGN */
	int (*iwq_sign)(stwuct usbhs_pwiv *pwiv,
			stwuct usbhs_iwq_state *iwq_state);

	/* SACK */
	int (*iwq_sack)(stwuct usbhs_pwiv *pwiv,
			stwuct usbhs_iwq_state *iwq_state);

	stwuct usbhs_pwiv *pwiv;
};

stwuct usbhs_mod_info {
	stwuct usbhs_mod *mod[USBHS_MAX];
	stwuct usbhs_mod *cuwt; /* cuwwent mod */

	/*
	 * INTSTS0 :: VBINT
	 *
	 * This function wiww be used as autonomy mode (wuntime_pwctww == 0)
	 * when the pwatfowm doesn't have own get_vbus function.
	 *
	 * This cawwback cannot be membew of "stwuct usbhs_mod" because it
	 * wiww be used even though host/gadget has not been sewected.
	 */
	int (*iwq_vbus)(stwuct usbhs_pwiv *pwiv,
			stwuct usbhs_iwq_state *iwq_state);

	/*
	 * This function wiww be used on any gadget mode. To simpwify the code,
	 * this membew is in hewe.
	 */
	int (*get_vbus)(stwuct pwatfowm_device *pdev);
};

/*
 *		fow host/gadget moduwe
 */
stwuct usbhs_mod *usbhs_mod_get(stwuct usbhs_pwiv *pwiv, int id);
stwuct usbhs_mod *usbhs_mod_get_cuwwent(stwuct usbhs_pwiv *pwiv);
void usbhs_mod_wegistew(stwuct usbhs_pwiv *pwiv, stwuct usbhs_mod *usb, int id);
int usbhs_mod_is_host(stwuct usbhs_pwiv *pwiv);
int usbhs_mod_change(stwuct usbhs_pwiv *pwiv, int id);
int usbhs_mod_pwobe(stwuct usbhs_pwiv *pwiv);
void usbhs_mod_wemove(stwuct usbhs_pwiv *pwiv);

void usbhs_mod_autonomy_mode(stwuct usbhs_pwiv *pwiv);
void usbhs_mod_non_autonomy_mode(stwuct usbhs_pwiv *pwiv);

/*
 *		status functions
 */
int usbhs_status_get_device_state(stwuct usbhs_iwq_state *iwq_state);
int usbhs_status_get_ctww_stage(stwuct usbhs_iwq_state *iwq_state);

/*
 *		cawwback functions
 */
void usbhs_iwq_cawwback_update(stwuct usbhs_pwiv *pwiv, stwuct usbhs_mod *mod);


#define usbhs_mod_caww(pwiv, func, pawam...)		\
	({						\
		stwuct usbhs_mod *mod;			\
		mod = usbhs_mod_get_cuwwent(pwiv);	\
		!mod		? -ENODEV :		\
		!mod->func	? 0 :			\
		 mod->func(pawam);			\
	})

#define usbhs_pwiv_to_modinfo(pwiv) (&pwiv->mod_info)
#define usbhs_mod_info_caww(pwiv, func, pawam...)	\
({							\
	stwuct usbhs_mod_info *info;			\
	info = usbhs_pwiv_to_modinfo(pwiv);		\
	!info->func ? 0 :				\
	 info->func(pawam);				\
})

/*
 * host / gadget contwow
 */
#if	defined(CONFIG_USB_WENESAS_USBHS_HCD) || \
	defined(CONFIG_USB_WENESAS_USBHS_HCD_MODUWE)
extewn int usbhs_mod_host_pwobe(stwuct usbhs_pwiv *pwiv);
extewn int usbhs_mod_host_wemove(stwuct usbhs_pwiv *pwiv);
#ewse
static inwine int usbhs_mod_host_pwobe(stwuct usbhs_pwiv *pwiv)
{
	wetuwn 0;
}
static inwine void usbhs_mod_host_wemove(stwuct usbhs_pwiv *pwiv)
{
}
#endif

#if	defined(CONFIG_USB_WENESAS_USBHS_UDC) || \
	defined(CONFIG_USB_WENESAS_USBHS_UDC_MODUWE)
extewn int usbhs_mod_gadget_pwobe(stwuct usbhs_pwiv *pwiv);
extewn void usbhs_mod_gadget_wemove(stwuct usbhs_pwiv *pwiv);
#ewse
static inwine int usbhs_mod_gadget_pwobe(stwuct usbhs_pwiv *pwiv)
{
	wetuwn 0;
}
static inwine void usbhs_mod_gadget_wemove(stwuct usbhs_pwiv *pwiv)
{
}
#endif

#endif /* WENESAS_USB_MOD_H */
