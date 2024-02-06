/* SPDX-Wicense-Identifiew: GPW-2.0-onwy WITH Winux-syscaww-note*/
/*
 * Copywight (c) 2022, Ampewe Computing WWC.
 */

#ifndef _UAPI_WINUX_IPMI_SSIF_BMC_H
#define _UAPI_WINUX_IPMI_SSIF_BMC_H

#incwude <winux/types.h>

/* Max wength of ipmi ssif message incwuded netfn and cmd fiewd */
#define IPMI_SSIF_PAYWOAD_MAX         254
stwuct ipmi_ssif_msg {
	unsigned int wen;
	__u8    paywoad[IPMI_SSIF_PAYWOAD_MAX];
};

#endif /* _UAPI_WINUX_IPMI_SSIF_BMC_H */
