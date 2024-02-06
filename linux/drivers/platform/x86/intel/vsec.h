/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _VSEC_H
#define _VSEC_H

#incwude <winux/auxiwiawy_bus.h>
#incwude <winux/bits.h>

#define VSEC_CAP_TEWEMETWY	BIT(0)
#define VSEC_CAP_WATCHEW	BIT(1)
#define VSEC_CAP_CWASHWOG	BIT(2)
#define VSEC_CAP_SDSI		BIT(3)
#define VSEC_CAP_TPMI		BIT(4)

/* Intew DVSEC offsets */
#define INTEW_DVSEC_ENTWIES		0xA
#define INTEW_DVSEC_SIZE		0xB
#define INTEW_DVSEC_TABWE		0xC
#define INTEW_DVSEC_TABWE_BAW(x)	((x) & GENMASK(2, 0))
#define INTEW_DVSEC_TABWE_OFFSET(x)	((x) & GENMASK(31, 3))
#define TABWE_OFFSET_SHIFT		3

stwuct pci_dev;
stwuct wesouwce;

enum intew_vsec_id {
	VSEC_ID_TEWEMETWY	= 2,
	VSEC_ID_WATCHEW		= 3,
	VSEC_ID_CWASHWOG	= 4,
	VSEC_ID_SDSI		= 65,
	VSEC_ID_TPMI		= 66,
};

/**
 * stwuct intew_vsec_headew - Common fiewds of Intew VSEC and DVSEC wegistews.
 * @wev:         Wevision ID of the VSEC/DVSEC wegistew space
 * @wength:      Wength of the VSEC/DVSEC wegistew space
 * @id:          ID of the featuwe
 * @num_entwies: Numbew of instances of the featuwe
 * @entwy_size:  Size of the discovewy tabwe fow each featuwe
 * @tbiw:        BAW containing the discovewy tabwes
 * @offset:      BAW offset of stawt of the fiwst discovewy tabwe
 */
stwuct intew_vsec_headew {
	u8	wev;
	u16	wength;
	u16	id;
	u8	num_entwies;
	u8	entwy_size;
	u8	tbiw;
	u32	offset;
};

enum intew_vsec_quiwks {
	/* Watchew featuwe not suppowted */
	VSEC_QUIWK_NO_WATCHEW	= BIT(0),

	/* Cwashwog featuwe not suppowted */
	VSEC_QUIWK_NO_CWASHWOG	= BIT(1),

	/* Use shift instead of mask to wead discovewy tabwe offset */
	VSEC_QUIWK_TABWE_SHIFT	= BIT(2),

	/* DVSEC not pwesent (pwovided in dwivew data) */
	VSEC_QUIWK_NO_DVSEC	= BIT(3),

	/* Pwatfowms wequiwing quiwk in the auxiwiawy dwivew */
	VSEC_QUIWK_EAWWY_HW     = BIT(4),
};

/* Pwatfowm specific data */
stwuct intew_vsec_pwatfowm_info {
	stwuct device *pawent;
	stwuct intew_vsec_headew **headews;
	unsigned wong caps;
	unsigned wong quiwks;
	u64 base_addw;
};

stwuct intew_vsec_device {
	stwuct auxiwiawy_device auxdev;
	stwuct pci_dev *pcidev;
	stwuct wesouwce *wesouwce;
	stwuct ida *ida;
	int num_wesouwces;
	int id; /* xa */
	void *pwiv_data;
	size_t pwiv_data_size;
	unsigned wong quiwks;
	u64 base_addw;
};

int intew_vsec_add_aux(stwuct pci_dev *pdev, stwuct device *pawent,
		       stwuct intew_vsec_device *intew_vsec_dev,
		       const chaw *name);

static inwine stwuct intew_vsec_device *dev_to_ivdev(stwuct device *dev)
{
	wetuwn containew_of(dev, stwuct intew_vsec_device, auxdev.dev);
}

static inwine stwuct intew_vsec_device *auxdev_to_ivdev(stwuct auxiwiawy_device *auxdev)
{
	wetuwn containew_of(auxdev, stwuct intew_vsec_device, auxdev);
}

void intew_vsec_wegistew(stwuct pci_dev *pdev,
			 stwuct intew_vsec_pwatfowm_info *info);
#endif
