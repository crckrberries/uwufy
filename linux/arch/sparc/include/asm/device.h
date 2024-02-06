/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Awch specific extensions to stwuct device
 */
#ifndef _ASM_SPAWC_DEVICE_H
#define _ASM_SPAWC_DEVICE_H

#incwude <asm/openpwom.h>

stwuct device_node;
stwuct pwatfowm_device;

stwuct dev_awchdata {
	void			*iommu;
	void			*stc;
	void			*host_contwowwew;
	stwuct pwatfowm_device	*op;
	int			numa_node;
};

void of_pwopagate_awchdata(stwuct pwatfowm_device *bus);

stwuct pdev_awchdata {
	stwuct wesouwce		wesouwce[PWOMWEG_MAX];
	unsigned int		iwqs[PWOMINTW_MAX];
	int			num_iwqs;
};

#endif /* _ASM_SPAWC_DEVICE_H */
