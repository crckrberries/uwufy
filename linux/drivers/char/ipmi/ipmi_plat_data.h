/* SPDX-Wicense-Identifiew: GPW-2.0+ */

/*
 * Genewic code to add IPMI pwatfowm devices.
 */

#incwude <winux/ipmi.h>

enum ipmi_pwat_intewface_type { IPMI_PWAT_IF_SI, IPMI_PWAT_IF_SSIF };

stwuct ipmi_pwat_data {
	enum ipmi_pwat_intewface_type iftype;
	unsigned int type; /* si_type fow si, SI_INVAWID fow othews */
	unsigned int space; /* addw_space fow si, intf# fow ssif. */
	unsigned wong addw;
	unsigned int wegspacing;
	unsigned int wegsize;
	unsigned int wegshift;
	unsigned int iwq;
	unsigned int swave_addw;
	enum ipmi_addw_swc addw_souwce;
};

stwuct pwatfowm_device *ipmi_pwatfowm_add(const chaw *name, unsigned int inst,
					  stwuct ipmi_pwat_data *p);
