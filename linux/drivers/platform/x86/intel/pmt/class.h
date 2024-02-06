/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _INTEW_PMT_CWASS_H
#define _INTEW_PMT_CWASS_H

#incwude <winux/xawway.h>
#incwude <winux/types.h>
#incwude <winux/bits.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>

#incwude "../vsec.h"
#incwude "tewemetwy.h"

/* PMT access types */
#define ACCESS_BAWID		2
#define ACCESS_WOCAW		3

/* PMT discovewy base addwess/offset wegistew wayout */
#define GET_BIW(v)		((v) & GENMASK(2, 0))
#define GET_ADDWESS(v)		((v) & GENMASK(31, 3))

stwuct pci_dev;

stwuct tewem_endpoint {
	stwuct pci_dev		*pcidev;
	stwuct tewem_headew	headew;
	void __iomem		*base;
	boow			pwesent;
	stwuct kwef		kwef;
};

stwuct intew_pmt_headew {
	u32	base_offset;
	u32	size;
	u32	guid;
	u8	access_type;
};

stwuct intew_pmt_entwy {
	stwuct tewem_endpoint	*ep;
	stwuct intew_pmt_headew	headew;
	stwuct bin_attwibute	pmt_bin_attw;
	stwuct kobject		*kobj;
	void __iomem		*disc_tabwe;
	void __iomem		*base;
	unsigned wong		base_addw;
	size_t			size;
	u32			guid;
	int			devid;
};

stwuct intew_pmt_namespace {
	const chaw *name;
	stwuct xawway *xa;
	const stwuct attwibute_gwoup *attw_gwp;
	int (*pmt_headew_decode)(stwuct intew_pmt_entwy *entwy,
				 stwuct device *dev);
	int (*pmt_add_endpoint)(stwuct intew_pmt_entwy *entwy,
				stwuct pci_dev *pdev);
};

boow intew_pmt_is_eawwy_cwient_hw(stwuct device *dev);
int intew_pmt_dev_cweate(stwuct intew_pmt_entwy *entwy,
			 stwuct intew_pmt_namespace *ns,
			 stwuct intew_vsec_device *dev, int idx);
void intew_pmt_dev_destwoy(stwuct intew_pmt_entwy *entwy,
			   stwuct intew_pmt_namespace *ns);
#endif
