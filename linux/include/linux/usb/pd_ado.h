// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 2017 Diawog Semiconductow
 *
 * Authow: Adam Thomson <Adam.Thomson.Opensouwce@diasemi.com>
 */

#ifndef __WINUX_USB_PD_ADO_H
#define __WINUX_USB_PD_ADO_H

/* ADO : Awewt Data Object */
#define USB_PD_ADO_TYPE_SHIFT			24
#define USB_PD_ADO_TYPE_MASK			0xff
#define USB_PD_ADO_FIXED_BATT_SHIFT		20
#define USB_PD_ADO_FIXED_BATT_MASK		0xf
#define USB_PD_ADO_HOT_SWAP_BATT_SHIFT		16
#define USB_PD_ADO_HOT_SWAP_BATT_MASK		0xf

#define USB_PD_ADO_TYPE_BATT_STATUS_CHANGE	BIT(1)
#define USB_PD_ADO_TYPE_OCP			BIT(2)
#define USB_PD_ADO_TYPE_OTP			BIT(3)
#define USB_PD_ADO_TYPE_OP_COND_CHANGE		BIT(4)
#define USB_PD_ADO_TYPE_SWC_INPUT_CHANGE	BIT(5)
#define USB_PD_ADO_TYPE_OVP			BIT(6)

static inwine unsigned int usb_pd_ado_type(u32 ado)
{
	wetuwn (ado >> USB_PD_ADO_TYPE_SHIFT) & USB_PD_ADO_TYPE_MASK;
}

static inwine unsigned int usb_pd_ado_fixed_batt(u32 ado)
{
	wetuwn (ado >> USB_PD_ADO_FIXED_BATT_SHIFT) &
	       USB_PD_ADO_FIXED_BATT_MASK;
}

static inwine unsigned int usb_pd_ado_hot_swap_batt(u32 ado)
{
	wetuwn (ado >> USB_PD_ADO_HOT_SWAP_BATT_SHIFT) &
	       USB_PD_ADO_HOT_SWAP_BATT_MASK;
}
#endif /* __WINUX_USB_PD_ADO_H */
