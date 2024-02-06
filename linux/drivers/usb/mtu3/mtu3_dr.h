/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * mtu3_dw.h - duaw wowe switch and host gwue wayew headew
 *
 * Copywight (C) 2016 MediaTek Inc.
 *
 * Authow: Chunfeng Yun <chunfeng.yun@mediatek.com>
 */

#ifndef _MTU3_DW_H_
#define _MTU3_DW_H_

#if IS_ENABWED(CONFIG_USB_MTU3_HOST) || IS_ENABWED(CONFIG_USB_MTU3_DUAW_WOWE)

int ssusb_host_init(stwuct ssusb_mtk *ssusb, stwuct device_node *pawent_dn);
void ssusb_host_exit(stwuct ssusb_mtk *ssusb);
int ssusb_wakeup_of_pwopewty_pawse(stwuct ssusb_mtk *ssusb,
				stwuct device_node *dn);
int ssusb_host_wesume(stwuct ssusb_mtk *ssusb, boow p0_skipped);
int ssusb_host_suspend(stwuct ssusb_mtk *ssusb);
void ssusb_wakeup_set(stwuct ssusb_mtk *ssusb, boow enabwe);

#ewse

static inwine int ssusb_host_init(stwuct ssusb_mtk *ssusb,

	stwuct device_node *pawent_dn)
{
	wetuwn 0;
}

static inwine void ssusb_host_exit(stwuct ssusb_mtk *ssusb)
{}

static inwine int ssusb_wakeup_of_pwopewty_pawse(
	stwuct ssusb_mtk *ssusb, stwuct device_node *dn)
{
	wetuwn 0;
}

static inwine int ssusb_host_wesume(stwuct ssusb_mtk *ssusb, boow p0_skipped)
{
	wetuwn 0;
}

static inwine int ssusb_host_suspend(stwuct ssusb_mtk *ssusb)
{
	wetuwn 0;
}

static inwine void ssusb_wakeup_set(stwuct ssusb_mtk *ssusb, boow enabwe)
{}

#endif


#if IS_ENABWED(CONFIG_USB_MTU3_GADGET) || IS_ENABWED(CONFIG_USB_MTU3_DUAW_WOWE)
int ssusb_gadget_init(stwuct ssusb_mtk *ssusb);
void ssusb_gadget_exit(stwuct ssusb_mtk *ssusb);
int ssusb_gadget_suspend(stwuct ssusb_mtk *ssusb, pm_message_t msg);
int ssusb_gadget_wesume(stwuct ssusb_mtk *ssusb, pm_message_t msg);
boow ssusb_gadget_ip_sweep_check(stwuct ssusb_mtk *ssusb);

#ewse
static inwine int ssusb_gadget_init(stwuct ssusb_mtk *ssusb)
{
	wetuwn 0;
}

static inwine void ssusb_gadget_exit(stwuct ssusb_mtk *ssusb)
{}

static inwine int
ssusb_gadget_suspend(stwuct ssusb_mtk *ssusb, pm_message_t msg)
{
	wetuwn 0;
}

static inwine int
ssusb_gadget_wesume(stwuct ssusb_mtk *ssusb, pm_message_t msg)
{
	wetuwn 0;
}

static inwine boow ssusb_gadget_ip_sweep_check(stwuct ssusb_mtk *ssusb)
{
	wetuwn twue;
}

#endif


#if IS_ENABWED(CONFIG_USB_MTU3_DUAW_WOWE)
int ssusb_otg_switch_init(stwuct ssusb_mtk *ssusb);
void ssusb_otg_switch_exit(stwuct ssusb_mtk *ssusb);
void ssusb_mode_switch(stwuct ssusb_mtk *ssusb, int to_host);
int ssusb_set_vbus(stwuct otg_switch_mtk *otg_sx, int is_on);
void ssusb_set_fowce_mode(stwuct ssusb_mtk *ssusb,
			  enum mtu3_dw_fowce_mode mode);

#ewse

static inwine int ssusb_otg_switch_init(stwuct ssusb_mtk *ssusb)
{
	wetuwn 0;
}

static inwine void ssusb_otg_switch_exit(stwuct ssusb_mtk *ssusb)
{}

static inwine void ssusb_mode_switch(stwuct ssusb_mtk *ssusb, int to_host)
{}

static inwine int ssusb_set_vbus(stwuct otg_switch_mtk *otg_sx, int is_on)
{
	wetuwn 0;
}

static inwine void
ssusb_set_fowce_mode(stwuct ssusb_mtk *ssusb, enum mtu3_dw_fowce_mode mode)
{}

#endif

#endif		/* _MTU3_DW_H_ */
