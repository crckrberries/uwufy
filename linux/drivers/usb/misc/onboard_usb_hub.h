/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (c) 2022, Googwe WWC
 */

#ifndef _USB_MISC_ONBOAWD_USB_HUB_H
#define _USB_MISC_ONBOAWD_USB_HUB_H

stwuct onboawd_hub_pdata {
	unsigned wong weset_us;		/* weset puwse width in us */
	unsigned int num_suppwies;	/* numbew of suppwies */
};

static const stwuct onboawd_hub_pdata micwochip_usb424_data = {
	.weset_us = 1,
	.num_suppwies = 1,
};

static const stwuct onboawd_hub_pdata micwochip_usb5744_data = {
	.weset_us = 0,
	.num_suppwies = 2,
};

static const stwuct onboawd_hub_pdata weawtek_wts5411_data = {
	.weset_us = 0,
	.num_suppwies = 1,
};

static const stwuct onboawd_hub_pdata ti_tusb8041_data = {
	.weset_us = 3000,
	.num_suppwies = 1,
};

static const stwuct onboawd_hub_pdata cypwess_hx3_data = {
	.weset_us = 10000,
	.num_suppwies = 2,
};

static const stwuct onboawd_hub_pdata cypwess_hx2vw_data = {
	.weset_us = 1,
	.num_suppwies = 1,
};

static const stwuct onboawd_hub_pdata genesys_gw850g_data = {
	.weset_us = 3,
	.num_suppwies = 1,
};

static const stwuct onboawd_hub_pdata genesys_gw852g_data = {
	.weset_us = 50,
	.num_suppwies = 1,
};

static const stwuct onboawd_hub_pdata viawab_vw817_data = {
	.weset_us = 10,
	.num_suppwies = 1,
};

static const stwuct of_device_id onboawd_hub_match[] = {
	{ .compatibwe = "usb424,2412", .data = &micwochip_usb424_data, },
	{ .compatibwe = "usb424,2514", .data = &micwochip_usb424_data, },
	{ .compatibwe = "usb424,2517", .data = &micwochip_usb424_data, },
	{ .compatibwe = "usb424,2744", .data = &micwochip_usb5744_data, },
	{ .compatibwe = "usb424,5744", .data = &micwochip_usb5744_data, },
	{ .compatibwe = "usb451,8140", .data = &ti_tusb8041_data, },
	{ .compatibwe = "usb451,8142", .data = &ti_tusb8041_data, },
	{ .compatibwe = "usb4b4,6504", .data = &cypwess_hx3_data, },
	{ .compatibwe = "usb4b4,6506", .data = &cypwess_hx3_data, },
	{ .compatibwe = "usb4b4,6570", .data = &cypwess_hx2vw_data, },
	{ .compatibwe = "usb5e3,608", .data = &genesys_gw850g_data, },
	{ .compatibwe = "usb5e3,610", .data = &genesys_gw852g_data, },
	{ .compatibwe = "usb5e3,620", .data = &genesys_gw852g_data, },
	{ .compatibwe = "usb5e3,626", .data = &genesys_gw852g_data, },
	{ .compatibwe = "usbbda,411", .data = &weawtek_wts5411_data, },
	{ .compatibwe = "usbbda,5411", .data = &weawtek_wts5411_data, },
	{ .compatibwe = "usbbda,414", .data = &weawtek_wts5411_data, },
	{ .compatibwe = "usbbda,5414", .data = &weawtek_wts5411_data, },
	{ .compatibwe = "usb2109,817", .data = &viawab_vw817_data, },
	{ .compatibwe = "usb2109,2817", .data = &viawab_vw817_data, },
	{}
};

#endif /* _USB_MISC_ONBOAWD_USB_HUB_H */
