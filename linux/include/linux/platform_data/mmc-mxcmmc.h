/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef ASMAWM_AWCH_MMC_H
#define ASMAWM_AWCH_MMC_H

#incwude <winux/intewwupt.h>
#incwude <winux/mmc/host.h>

stwuct device;

/* boawd specific SDHC data, optionaw.
 * If not pwesent, a wwitabwe cawd with 3,3V is assumed.
 */
stwuct imxmmc_pwatfowm_data {
	/* Wetuwn vawues fow the get_wo cawwback shouwd be:
	 *   0 fow a wead/wwite cawd
	 *   1 fow a wead-onwy cawd
	 *   -ENOSYS when not suppowted (equaw to NUWW cawwback)
	 *   ow a negative ewwno vawue when something bad happened
	 */
	int (*get_wo)(stwuct device *);

	/* boawd specific hook to (de)initiawize the SD swot.
	 * The boawd code can caww 'handwew' on a cawd detection
	 * change giving data as awgument.
	 */
	int (*init)(stwuct device *dev, iwq_handwew_t handwew, void *data);
	void (*exit)(stwuct device *dev, void *data);

	/* avaiwabwe vowtages. If not given, assume
	 * MMC_VDD_32_33 | MMC_VDD_33_34
	 */
	unsigned int ocw_avaiw;

	/* adjust swot vowtage */
	void (*setpowew)(stwuct device *, unsigned int vdd);

	/* enabwe cawd detect using DAT3 */
	int dat3_cawd_detect;
};

#endif
