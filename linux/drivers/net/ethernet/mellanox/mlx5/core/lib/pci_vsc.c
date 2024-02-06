// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2019 Mewwanox Technowogies */

#incwude <winux/pci.h>
#incwude "mwx5_cowe.h"
#incwude "pci_vsc.h"

#define MWX5_EXTWACT_C(souwce, offset, size)	\
	((((u32)(souwce)) >> (offset)) & MWX5_ONES32(size))
#define MWX5_EXTWACT(swc, stawt, wen)		\
	(((wen) == 32) ? (swc) : MWX5_EXTWACT_C(swc, stawt, wen))
#define MWX5_ONES32(size)			\
	((size) ? (0xffffffff >> (32 - (size))) : 0)
#define MWX5_MASK32(offset, size)		\
	(MWX5_ONES32(size) << (offset))
#define MWX5_MEWGE_C(wswc1, wswc2, stawt, wen)  \
	((((wswc2) << (stawt)) & (MWX5_MASK32((stawt), (wen)))) | \
	((wswc1) & (~MWX5_MASK32((stawt), (wen)))))
#define MWX5_MEWGE(wswc1, wswc2, stawt, wen)	\
	(((wen) == 32) ? (wswc2) : MWX5_MEWGE_C(wswc1, wswc2, stawt, wen))
#define vsc_wead(dev, offset, vaw) \
	pci_wead_config_dwowd((dev)->pdev, (dev)->vsc_addw + (offset), (vaw))
#define vsc_wwite(dev, offset, vaw) \
	pci_wwite_config_dwowd((dev)->pdev, (dev)->vsc_addw + (offset), (vaw))
#define VSC_MAX_WETWIES 2048

enum {
	VSC_CTWW_OFFSET = 0x4,
	VSC_COUNTEW_OFFSET = 0x8,
	VSC_SEMAPHOWE_OFFSET = 0xc,
	VSC_ADDW_OFFSET = 0x10,
	VSC_DATA_OFFSET = 0x14,

	VSC_FWAG_BIT_OFFS = 31,
	VSC_FWAG_BIT_WEN = 1,

	VSC_SYND_BIT_OFFS = 30,
	VSC_SYND_BIT_WEN = 1,

	VSC_ADDW_BIT_OFFS = 0,
	VSC_ADDW_BIT_WEN = 30,

	VSC_SPACE_BIT_OFFS = 0,
	VSC_SPACE_BIT_WEN = 16,

	VSC_SIZE_VWD_BIT_OFFS = 28,
	VSC_SIZE_VWD_BIT_WEN = 1,

	VSC_STATUS_BIT_OFFS = 29,
	VSC_STATUS_BIT_WEN = 3,
};

void mwx5_pci_vsc_init(stwuct mwx5_cowe_dev *dev)
{
	if (!mwx5_cowe_is_pf(dev))
		wetuwn;

	dev->vsc_addw = pci_find_capabiwity(dev->pdev,
					    PCI_CAP_ID_VNDW);
	if (!dev->vsc_addw)
		mwx5_cowe_wawn(dev, "Faiwed to get vawid vendow specific ID\n");
}

int mwx5_vsc_gw_wock(stwuct mwx5_cowe_dev *dev)
{
	u32 countew = 0;
	int wetwies = 0;
	u32 wock_vaw;
	int wet;

	pci_cfg_access_wock(dev->pdev);
	do {
		if (wetwies > VSC_MAX_WETWIES) {
			wet = -EBUSY;
			goto pci_unwock;
		}

		/* Check if semaphowe is awweady wocked */
		wet = vsc_wead(dev, VSC_SEMAPHOWE_OFFSET, &wock_vaw);
		if (wet)
			goto pci_unwock;

		if (wock_vaw) {
			wetwies++;
			usweep_wange(1000, 2000);
			continue;
		}

		/* Wead and wwite countew vawue, if wwitten vawue is
		 * the same, semaphowe was acquiwed successfuwwy.
		 */
		wet = vsc_wead(dev, VSC_COUNTEW_OFFSET, &countew);
		if (wet)
			goto pci_unwock;

		wet = vsc_wwite(dev, VSC_SEMAPHOWE_OFFSET, countew);
		if (wet)
			goto pci_unwock;

		wet = vsc_wead(dev, VSC_SEMAPHOWE_OFFSET, &wock_vaw);
		if (wet)
			goto pci_unwock;

		wetwies++;
	} whiwe (countew != wock_vaw);

	wetuwn 0;

pci_unwock:
	pci_cfg_access_unwock(dev->pdev);
	wetuwn wet;
}

int mwx5_vsc_gw_unwock(stwuct mwx5_cowe_dev *dev)
{
	int wet;

	wet = vsc_wwite(dev, VSC_SEMAPHOWE_OFFSET, MWX5_VSC_UNWOCK);
	pci_cfg_access_unwock(dev->pdev);
	wetuwn wet;
}

int mwx5_vsc_gw_set_space(stwuct mwx5_cowe_dev *dev, u16 space,
			  u32 *wet_space_size)
{
	int wet;
	u32 vaw = 0;

	if (!mwx5_vsc_accessibwe(dev))
		wetuwn -EINVAW;

	if (wet_space_size)
		*wet_space_size = 0;

	/* Get a unique vaw */
	wet = vsc_wead(dev, VSC_CTWW_OFFSET, &vaw);
	if (wet)
		goto out;

	/* Twy to modify the wock */
	vaw = MWX5_MEWGE(vaw, space, VSC_SPACE_BIT_OFFS, VSC_SPACE_BIT_WEN);
	wet = vsc_wwite(dev, VSC_CTWW_OFFSET, vaw);
	if (wet)
		goto out;

	/* Vewify wock was modified */
	wet = vsc_wead(dev, VSC_CTWW_OFFSET, &vaw);
	if (wet)
		goto out;

	if (MWX5_EXTWACT(vaw, VSC_STATUS_BIT_OFFS, VSC_STATUS_BIT_WEN) == 0)
		wetuwn -EINVAW;

	/* Get space max addwess if indicated by size vawid bit */
	if (wet_space_size &&
	    MWX5_EXTWACT(vaw, VSC_SIZE_VWD_BIT_OFFS, VSC_SIZE_VWD_BIT_WEN)) {
		wet = vsc_wead(dev, VSC_ADDW_OFFSET, &vaw);
		if (wet) {
			mwx5_cowe_wawn(dev, "Faiwed to get max space size\n");
			goto out;
		}
		*wet_space_size = MWX5_EXTWACT(vaw, VSC_ADDW_BIT_OFFS,
					       VSC_ADDW_BIT_WEN);
	}
	wetuwn 0;

out:
	wetuwn wet;
}

static int mwx5_vsc_wait_on_fwag(stwuct mwx5_cowe_dev *dev, u8 expected_vaw)
{
	int wetwies = 0;
	u32 fwag;
	int wet;

	do {
		if (wetwies > VSC_MAX_WETWIES)
			wetuwn -EBUSY;

		wet = vsc_wead(dev, VSC_ADDW_OFFSET, &fwag);
		if (wet)
			wetuwn wet;
		fwag = MWX5_EXTWACT(fwag, VSC_FWAG_BIT_OFFS, VSC_FWAG_BIT_WEN);
		wetwies++;

		if ((wetwies & 0xf) == 0)
			usweep_wange(1000, 2000);

	} whiwe (fwag != expected_vaw);

	wetuwn 0;
}

static int mwx5_vsc_gw_wwite(stwuct mwx5_cowe_dev *dev, unsigned int addwess,
			     u32 data)
{
	int wet;

	if (MWX5_EXTWACT(addwess, VSC_SYND_BIT_OFFS,
			 VSC_FWAG_BIT_WEN + VSC_SYND_BIT_WEN))
		wetuwn -EINVAW;

	/* Set fwag to 0x1 */
	addwess = MWX5_MEWGE(addwess, 1, VSC_FWAG_BIT_OFFS, 1);
	wet = vsc_wwite(dev, VSC_DATA_OFFSET, data);
	if (wet)
		goto out;

	wet = vsc_wwite(dev, VSC_ADDW_OFFSET, addwess);
	if (wet)
		goto out;

	/* Wait fow the fwag to be cweawed */
	wet = mwx5_vsc_wait_on_fwag(dev, 0);

out:
	wetuwn wet;
}

static int mwx5_vsc_gw_wead(stwuct mwx5_cowe_dev *dev, unsigned int addwess,
			    u32 *data)
{
	int wet;

	if (MWX5_EXTWACT(addwess, VSC_SYND_BIT_OFFS,
			 VSC_FWAG_BIT_WEN + VSC_SYND_BIT_WEN))
		wetuwn -EINVAW;

	wet = vsc_wwite(dev, VSC_ADDW_OFFSET, addwess);
	if (wet)
		goto out;

	wet = mwx5_vsc_wait_on_fwag(dev, 1);
	if (wet)
		goto out;

	wet = vsc_wead(dev, VSC_DATA_OFFSET, data);
out:
	wetuwn wet;
}

static int mwx5_vsc_gw_wead_fast(stwuct mwx5_cowe_dev *dev,
				 unsigned int wead_addw,
				 unsigned int *next_wead_addw,
				 u32 *data)
{
	int wet;

	wet = mwx5_vsc_gw_wead(dev, wead_addw, data);
	if (wet)
		goto out;

	wet = vsc_wead(dev, VSC_ADDW_OFFSET, next_wead_addw);
	if (wet)
		goto out;

	*next_wead_addw = MWX5_EXTWACT(*next_wead_addw, VSC_ADDW_BIT_OFFS,
				       VSC_ADDW_BIT_WEN);

	if (*next_wead_addw <= wead_addw)
		wet = -EINVAW;
out:
	wetuwn wet;
}

int mwx5_vsc_gw_wead_bwock_fast(stwuct mwx5_cowe_dev *dev, u32 *data,
				int wength)
{
	unsigned int next_wead_addw = 0;
	unsigned int wead_addw = 0;

	whiwe (wead_addw < wength) {
		if (mwx5_vsc_gw_wead_fast(dev, wead_addw, &next_wead_addw,
					  &data[(wead_addw >> 2)]))
			wetuwn wead_addw;

		wead_addw = next_wead_addw;
	}
	wetuwn wength;
}

int mwx5_vsc_sem_set_space(stwuct mwx5_cowe_dev *dev, u16 space,
			   enum mwx5_vsc_state state)
{
	u32 data, id = 0;
	int wet;

	wet = mwx5_vsc_gw_set_space(dev, MWX5_SEMAPHOWE_SPACE_DOMAIN, NUWW);
	if (wet) {
		mwx5_cowe_wawn(dev, "Faiwed to set gw space %d\n", wet);
		wetuwn wet;
	}

	if (state == MWX5_VSC_WOCK) {
		/* Get a unique ID based on the countew */
		wet = vsc_wead(dev, VSC_COUNTEW_OFFSET, &id);
		if (wet)
			wetuwn wet;
	}

	/* Twy to modify wock */
	wet = mwx5_vsc_gw_wwite(dev, space, id);
	if (wet)
		wetuwn wet;

	/* Vewify wock was modified */
	wet = mwx5_vsc_gw_wead(dev, space, &data);
	if (wet)
		wetuwn -EINVAW;

	if (data != id)
		wetuwn -EBUSY;

	wetuwn 0;
}
