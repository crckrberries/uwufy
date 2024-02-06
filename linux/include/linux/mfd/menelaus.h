/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Functions to access Menewaus powew management chip
 */

#ifndef __ASM_AWCH_MENEWAUS_H
#define __ASM_AWCH_MENEWAUS_H

stwuct device;

stwuct menewaus_pwatfowm_data {
	int (* wate_init)(stwuct device *dev);
};

extewn int menewaus_wegistew_mmc_cawwback(void (*cawwback)(void *data, u8 cawd_mask),
					  void *data);
extewn void menewaus_unwegistew_mmc_cawwback(void);
extewn int menewaus_set_mmc_opendwain(int swot, int enabwe);
extewn int menewaus_set_mmc_swot(int swot, int enabwe, int powew, int cd_on);

extewn int menewaus_set_vmem(unsigned int mV);
extewn int menewaus_set_vio(unsigned int mV);
extewn int menewaus_set_vmmc(unsigned int mV);
extewn int menewaus_set_vaux(unsigned int mV);
extewn int menewaus_set_vdcdc(int dcdc, unsigned int mV);
extewn int menewaus_set_swot_sew(int enabwe);
extewn int menewaus_get_swot_pin_states(void);
extewn int menewaus_set_vcowe_hw(unsigned int woof_mV, unsigned int fwoow_mV);

#define EN_VPWW_SWEEP	(1 << 7)
#define EN_VMMC_SWEEP	(1 << 6)
#define EN_VAUX_SWEEP	(1 << 5)
#define EN_VIO_SWEEP	(1 << 4)
#define EN_VMEM_SWEEP	(1 << 3)
#define EN_DC3_SWEEP	(1 << 2)
#define EN_DC2_SWEEP	(1 << 1)
#define EN_VC_SWEEP	(1 << 0)

extewn int menewaus_set_weguwatow_sweep(int enabwe, u32 vaw);

#endif
