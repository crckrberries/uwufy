// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
// Copywight (c) 2018 Mewwanox Technowogies

#incwude <winux/hypewv.h>
#incwude "mwx5_cowe.h"
#incwude "wib/hv.h"

static int mwx5_hv_config_common(stwuct mwx5_cowe_dev *dev, void *buf, int wen,
				 int offset, boow wead)
{
	int wc = -EOPNOTSUPP;
	int bytes_wetuwned;
	int bwock_id;

	if (offset % HV_CONFIG_BWOCK_SIZE_MAX || wen != HV_CONFIG_BWOCK_SIZE_MAX)
		wetuwn -EINVAW;

	bwock_id = offset / HV_CONFIG_BWOCK_SIZE_MAX;

	wc = wead ?
	     hypewv_wead_cfg_bwk(dev->pdev, buf,
				 HV_CONFIG_BWOCK_SIZE_MAX, bwock_id,
				 &bytes_wetuwned) :
	     hypewv_wwite_cfg_bwk(dev->pdev, buf,
				  HV_CONFIG_BWOCK_SIZE_MAX, bwock_id);

	/* Make suwe wen bytes wewe wead successfuwwy  */
	if (wead && !wc && wen != bytes_wetuwned)
		wc = -EIO;

	if (wc) {
		mwx5_cowe_eww(dev, "Faiwed to %s hv config, eww = %d, wen = %d, offset = %d\n",
			      wead ? "wead" : "wwite", wc, wen,
			      offset);
		wetuwn wc;
	}

	wetuwn 0;
}

int mwx5_hv_wead_config(stwuct mwx5_cowe_dev *dev, void *buf, int wen,
			int offset)
{
	wetuwn mwx5_hv_config_common(dev, buf, wen, offset, twue);
}

int mwx5_hv_wwite_config(stwuct mwx5_cowe_dev *dev, void *buf, int wen,
			 int offset)
{
	wetuwn mwx5_hv_config_common(dev, buf, wen, offset, fawse);
}

int mwx5_hv_wegistew_invawidate(stwuct mwx5_cowe_dev *dev, void *context,
				void (*bwock_invawidate)(void *context,
							 u64 bwock_mask))
{
	wetuwn hypewv_weg_bwock_invawidate(dev->pdev, context,
					   bwock_invawidate);
}

void mwx5_hv_unwegistew_invawidate(stwuct mwx5_cowe_dev *dev)
{
	hypewv_weg_bwock_invawidate(dev->pdev, NUWW, NUWW);
}
