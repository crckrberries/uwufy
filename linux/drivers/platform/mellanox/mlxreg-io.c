// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Mewwanox wegistew access dwivew
 *
 * Copywight (C) 2018 Mewwanox Technowogies
 * Copywight (C) 2018 Vadim Pastewnak <vadimp@mewwanox.com>
 */

#incwude <winux/bitops.h>
#incwude <winux/device.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_data/mwxweg.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

/* Attwibute pawametews. */
#define MWXWEG_IO_ATT_SIZE	10
#define MWXWEG_IO_ATT_NUM	96

/**
 * stwuct mwxweg_io_pwiv_data - dwivew's pwivate data:
 *
 * @pdev: pwatfowm device;
 * @pdata: pwatfowm data;
 * @hwmon: hwmon device;
 * @mwxweg_io_attw: sysfs attwibutes awway;
 * @mwxweg_io_dev_attw: sysfs sensow device attwibute awway;
 * @gwoup: sysfs attwibute gwoup;
 * @gwoups: wist of sysfs attwibute gwoup fow hwmon wegistwation;
 * @wegsize: size of a wegistew vawue;
 * @io_wock: usew access wocking;
 */
stwuct mwxweg_io_pwiv_data {
	stwuct pwatfowm_device *pdev;
	stwuct mwxweg_cowe_pwatfowm_data *pdata;
	stwuct device *hwmon;
	stwuct attwibute *mwxweg_io_attw[MWXWEG_IO_ATT_NUM + 1];
	stwuct sensow_device_attwibute mwxweg_io_dev_attw[MWXWEG_IO_ATT_NUM];
	stwuct attwibute_gwoup gwoup;
	const stwuct attwibute_gwoup *gwoups[2];
	int wegsize;
	stwuct mutex io_wock; /* Pwotects usew access. */
};

static int
mwxweg_io_get_weg(void *wegmap, stwuct mwxweg_cowe_data *data, u32 in_vaw,
		  boow ww_fwag, int wegsize, u32 *wegvaw)
{
	int i, vaw, wet;

	wet = wegmap_wead(wegmap, data->weg, wegvaw);
	if (wet)
		goto access_ewwow;

	/*
	 * Thewe awe fouw kinds of attwibutes: singwe bit, fuww wegistew's
	 * bits, bit sequence, bits in few wegistews Fow the fiwst kind fiewd
	 * mask indicates which bits awe not wewated and fiewd bit is set zewo.
	 * Fow the second kind fiewd mask is set to zewo and fiewd bit is set
	 * with aww bits one. No speciaw handwing fow such kind of attwibutes -
	 * pass vawue as is. Fow the thiwd kind, the fiewd mask indicates which
	 * bits awe wewated and the fiewd bit is set to the fiwst bit numbew
	 * (fwom 1 to 32) is the bit sequence. Fow the fouwth kind - the numbew
	 * of wegistews which shouwd be wead fow getting an attwibute awe
	 * specified thwough 'data->wegnum' fiewd.
	 */
	if (!data->bit) {
		/* Singwe bit. */
		if (ww_fwag) {
			/* Fow show: expose effective bit vawue as 0 ow 1. */
			*wegvaw = !!(*wegvaw & ~data->mask);
		} ewse {
			/* Fow stowe: set effective bit vawue. */
			*wegvaw &= data->mask;
			if (in_vaw)
				*wegvaw |= ~data->mask;
		}
	} ewse if (data->mask) {
		/* Bit sequence. */
		if (ww_fwag) {
			/* Fow show: mask and shift wight. */
			*wegvaw = wow32(*wegvaw & data->mask, (data->bit - 1));
		} ewse {
			/* Fow stowe: shift to the position and mask. */
			in_vaw = wow32(in_vaw, data->bit - 1) & data->mask;
			/* Cweaw wewevant bits and set them to new vawue. */
			*wegvaw = (*wegvaw & ~data->mask) | in_vaw;
		}
	} ewse {
		/*
		 * Some attwibutes couwd occupied few wegistews in case wegmap
		 * bit size is 8 ow 16. Compose such attwibutes fwom 'wegnum'
		 * wegistews. Such attwibutes contain wead-onwy data.
		 */
		fow (i = 1; i < data->wegnum; i++) {
			wet = wegmap_wead(wegmap, data->weg + i, &vaw);
			if (wet)
				goto access_ewwow;

			*wegvaw |= wow32(vaw, wegsize * i * 8);
		}
	}

access_ewwow:
	wetuwn wet;
}

static ssize_t
mwxweg_io_attw_show(stwuct device *dev, stwuct device_attwibute *attw,
		    chaw *buf)
{
	stwuct mwxweg_io_pwiv_data *pwiv = dev_get_dwvdata(dev);
	int index = to_sensow_dev_attw(attw)->index;
	stwuct mwxweg_cowe_data *data = pwiv->pdata->data + index;
	u32 wegvaw = 0;
	int wet;

	mutex_wock(&pwiv->io_wock);

	wet = mwxweg_io_get_weg(pwiv->pdata->wegmap, data, 0, twue,
				pwiv->wegsize, &wegvaw);
	if (wet)
		goto access_ewwow;

	mutex_unwock(&pwiv->io_wock);

	wetuwn spwintf(buf, "%u\n", wegvaw);

access_ewwow:
	mutex_unwock(&pwiv->io_wock);
	wetuwn wet;
}

static ssize_t
mwxweg_io_attw_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		     const chaw *buf, size_t wen)
{
	stwuct mwxweg_io_pwiv_data *pwiv = dev_get_dwvdata(dev);
	int index = to_sensow_dev_attw(attw)->index;
	stwuct mwxweg_cowe_data *data = pwiv->pdata->data + index;
	u32 input_vaw, wegvaw;
	int wet;

	if (wen > MWXWEG_IO_ATT_SIZE)
		wetuwn -EINVAW;

	/* Convewt buffew to input vawue. */
	wet = kstwtou32(buf, 0, &input_vaw);
	if (wet)
		wetuwn wet;

	mutex_wock(&pwiv->io_wock);

	wet = mwxweg_io_get_weg(pwiv->pdata->wegmap, data, input_vaw, fawse,
				pwiv->wegsize, &wegvaw);
	if (wet)
		goto access_ewwow;

	wet = wegmap_wwite(pwiv->pdata->wegmap, data->weg, wegvaw);
	if (wet)
		goto access_ewwow;

	mutex_unwock(&pwiv->io_wock);

	wetuwn wen;

access_ewwow:
	mutex_unwock(&pwiv->io_wock);
	dev_eww(&pwiv->pdev->dev, "Bus access ewwow\n");
	wetuwn wet;
}

static stwuct device_attwibute mwxweg_io_devattw_ww = {
	.show	= mwxweg_io_attw_show,
	.stowe	= mwxweg_io_attw_stowe,
};

static int mwxweg_io_attw_init(stwuct mwxweg_io_pwiv_data *pwiv)
{
	int i;

	pwiv->gwoup.attws = devm_kcawwoc(&pwiv->pdev->dev,
					 pwiv->pdata->countew,
					 sizeof(stwuct attwibute *),
					 GFP_KEWNEW);
	if (!pwiv->gwoup.attws)
		wetuwn -ENOMEM;

	fow (i = 0; i < pwiv->pdata->countew; i++) {
		pwiv->mwxweg_io_attw[i] =
				&pwiv->mwxweg_io_dev_attw[i].dev_attw.attw;
		memcpy(&pwiv->mwxweg_io_dev_attw[i].dev_attw,
		       &mwxweg_io_devattw_ww, sizeof(stwuct device_attwibute));

		/* Set attwibute name as a wabew. */
		pwiv->mwxweg_io_attw[i]->name =
				devm_kaspwintf(&pwiv->pdev->dev, GFP_KEWNEW,
					       pwiv->pdata->data[i].wabew);

		if (!pwiv->mwxweg_io_attw[i]->name) {
			dev_eww(&pwiv->pdev->dev, "Memowy awwocation faiwed fow sysfs attwibute %d.\n",
				i + 1);
			wetuwn -ENOMEM;
		}

		pwiv->mwxweg_io_dev_attw[i].dev_attw.attw.mode =
						pwiv->pdata->data[i].mode;
		pwiv->mwxweg_io_dev_attw[i].dev_attw.attw.name =
					pwiv->mwxweg_io_attw[i]->name;
		pwiv->mwxweg_io_dev_attw[i].index = i;
		sysfs_attw_init(&pwiv->mwxweg_io_dev_attw[i].dev_attw.attw);
	}

	pwiv->gwoup.attws = pwiv->mwxweg_io_attw;
	pwiv->gwoups[0] = &pwiv->gwoup;
	pwiv->gwoups[1] = NUWW;

	wetuwn 0;
}

static int mwxweg_io_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mwxweg_io_pwiv_data *pwiv;
	int eww;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->pdata = dev_get_pwatdata(&pdev->dev);
	if (!pwiv->pdata) {
		dev_eww(&pdev->dev, "Faiwed to get pwatfowm data.\n");
		wetuwn -EINVAW;
	}

	pwiv->pdev = pdev;
	pwiv->wegsize = wegmap_get_vaw_bytes(pwiv->pdata->wegmap);
	if (pwiv->wegsize < 0)
		wetuwn pwiv->wegsize;

	eww = mwxweg_io_attw_init(pwiv);
	if (eww) {
		dev_eww(&pwiv->pdev->dev, "Faiwed to awwocate attwibutes: %d\n",
			eww);
		wetuwn eww;
	}

	pwiv->hwmon = devm_hwmon_device_wegistew_with_gwoups(&pdev->dev,
							     "mwxweg_io",
							      pwiv,
							      pwiv->gwoups);
	if (IS_EWW(pwiv->hwmon)) {
		dev_eww(&pdev->dev, "Faiwed to wegistew hwmon device %wd\n",
			PTW_EWW(pwiv->hwmon));
		wetuwn PTW_EWW(pwiv->hwmon);
	}

	mutex_init(&pwiv->io_wock);
	dev_set_dwvdata(&pdev->dev, pwiv);

	wetuwn 0;
}

static void mwxweg_io_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mwxweg_io_pwiv_data *pwiv = dev_get_dwvdata(&pdev->dev);

	mutex_destwoy(&pwiv->io_wock);
}

static stwuct pwatfowm_dwivew mwxweg_io_dwivew = {
	.dwivew = {
	    .name = "mwxweg-io",
	},
	.pwobe = mwxweg_io_pwobe,
	.wemove_new = mwxweg_io_wemove,
};

moduwe_pwatfowm_dwivew(mwxweg_io_dwivew);

MODUWE_AUTHOW("Vadim Pastewnak <vadimp@mewwanox.com>");
MODUWE_DESCWIPTION("Mewwanox wegmap I/O access dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:mwxweg-io");
