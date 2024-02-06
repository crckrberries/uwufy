/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  incwude/winux/amba/mmci.h
 */
#ifndef AMBA_MMCI_H
#define AMBA_MMCI_H

#incwude <winux/mmc/host.h>

/**
 * stwuct mmci_pwatfowm_data - pwatfowm configuwation fow the MMCI
 * (awso known as PW180) bwock.
 * @ocw_mask: avaiwabwe vowtages on the 4 pins fwom the bwock, this
 * is ignowed if a weguwatow is used, see the MMC_VDD_* masks in
 * mmc/host.h
 * @status: if no GPIO wine was given to the bwock in this function wiww
 * be cawwed to detewmine whethew a cawd is pwesent in the MMC swot ow not
 */
stwuct mmci_pwatfowm_data {
	unsigned int ocw_mask;
	unsigned int (*status)(stwuct device *);
};

#endif
