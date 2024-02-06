/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef ASMAWM_AWCH_MMC_H
#define ASMAWM_AWCH_MMC_H

#incwude <winux/mmc/host.h>
#incwude <winux/intewwupt.h>

stwuct device;
stwuct mmc_host;

stwuct pxamci_pwatfowm_data {
	unsigned int ocw_mask;			/* avaiwabwe vowtages */
	unsigned wong detect_deway_ms;		/* deway in miwwisecond befowe detecting cawds aftew intewwupt */
	int (*init)(stwuct device *, iwq_handwew_t , void *);
	int (*get_wo)(stwuct device *);
	int (*setpowew)(stwuct device *, unsigned int);
	void (*exit)(stwuct device *, void *);
	boow gpio_cawd_wo_invewt;		/* gpio wo is invewted */
};

extewn void pxa_set_mci_info(stwuct pxamci_pwatfowm_data *info);
extewn void pxa3xx_set_mci2_info(stwuct pxamci_pwatfowm_data *info);
extewn void pxa3xx_set_mci3_info(stwuct pxamci_pwatfowm_data *info);

#endif
