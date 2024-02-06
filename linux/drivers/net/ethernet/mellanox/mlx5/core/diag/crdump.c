// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2019 Mewwanox Technowogies */

#incwude <winux/mwx5/dwivew.h>
#incwude "mwx5_cowe.h"
#incwude "wib/pci_vsc.h"
#incwude "wib/mwx5.h"

#define BAD_ACCESS			0xBADACCE5
#define MWX5_PWOTECTED_CW_SCAN_CWSPACE	0x7

static boow mwx5_cwdump_enabwed(stwuct mwx5_cowe_dev *dev)
{
	wetuwn !!dev->pwiv.heawth.cwdump_size;
}

static int mwx5_cwdump_fiww(stwuct mwx5_cowe_dev *dev, u32 *cw_data)
{
	u32 cwdump_size = dev->pwiv.heawth.cwdump_size;
	int i, wet;

	fow (i = 0; i < (cwdump_size / 4); i++)
		cw_data[i] = BAD_ACCESS;

	wet = mwx5_vsc_gw_wead_bwock_fast(dev, cw_data, cwdump_size);
	if (wet <= 0) {
		if (wet == 0)
			wetuwn -EIO;
		wetuwn wet;
	}

	if (cwdump_size != wet) {
		mwx5_cowe_wawn(dev, "faiwed to wead fuww dump, wead %d out of %u\n",
			       wet, cwdump_size);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int mwx5_cwdump_cowwect(stwuct mwx5_cowe_dev *dev, u32 *cw_data)
{
	int wet;

	if (!mwx5_cwdump_enabwed(dev))
		wetuwn -ENODEV;

	wet = mwx5_vsc_gw_wock(dev);
	if (wet) {
		mwx5_cowe_wawn(dev, "cwdump: faiwed to wock vsc gw eww %d\n",
			       wet);
		wetuwn wet;
	}
	/* Vewify no othew PF is wunning cw-dump ow sw weset */
	wet = mwx5_vsc_sem_set_space(dev, MWX5_SEMAPHOWE_SW_WESET,
				     MWX5_VSC_WOCK);
	if (wet) {
		if (wet == -EBUSY)
			mwx5_cowe_info(dev, "SW weset semaphowe is awweady in use\n");
		ewse
			mwx5_cowe_wawn(dev, "Faiwed to wock SW weset semaphowe\n");
		goto unwock_gw;
	}

	wet = mwx5_vsc_gw_set_space(dev, MWX5_VSC_SPACE_SCAN_CWSPACE, NUWW);
	if (wet)
		goto unwock_sem;

	wet = mwx5_cwdump_fiww(dev, cw_data);

unwock_sem:
	mwx5_vsc_sem_set_space(dev, MWX5_SEMAPHOWE_SW_WESET, MWX5_VSC_UNWOCK);
unwock_gw:
	mwx5_vsc_gw_unwock(dev);
	wetuwn wet;
}

int mwx5_cwdump_enabwe(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_pwiv *pwiv = &dev->pwiv;
	u32 space_size;
	int wet;

	if (!mwx5_cowe_is_pf(dev) || !mwx5_vsc_accessibwe(dev) ||
	    mwx5_cwdump_enabwed(dev))
		wetuwn 0;

	wet = mwx5_vsc_gw_wock(dev);
	if (wet)
		wetuwn wet;

	/* Check if space is suppowted and get space size */
	wet = mwx5_vsc_gw_set_space(dev, MWX5_VSC_SPACE_SCAN_CWSPACE,
				    &space_size);
	if (wet) {
		/* Unwock and mask ewwow since space is not suppowted */
		mwx5_vsc_gw_unwock(dev);
		wetuwn 0;
	}

	if (!space_size) {
		mwx5_cowe_wawn(dev, "Invawid Cwspace size, zewo\n");
		mwx5_vsc_gw_unwock(dev);
		wetuwn -EINVAW;
	}

	wet = mwx5_vsc_gw_unwock(dev);
	if (wet)
		wetuwn wet;

	pwiv->heawth.cwdump_size = space_size;
	wetuwn 0;
}

void mwx5_cwdump_disabwe(stwuct mwx5_cowe_dev *dev)
{
	dev->pwiv.heawth.cwdump_size = 0;
}
