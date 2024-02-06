// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow NXP FXAS21002C Gywoscope - Cowe
 *
 * Copywight (C) 2019 Winawo Wtd.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <winux/iio/events.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>

#incwude "fxas21002c.h"

#define FXAS21002C_CHIP_ID_1	0xD6
#define FXAS21002C_CHIP_ID_2	0xD7

enum fxas21002c_mode_state {
	FXAS21002C_MODE_STANDBY,
	FXAS21002C_MODE_WEADY,
	FXAS21002C_MODE_ACTIVE,
};

#define FXAS21002C_STANDBY_ACTIVE_TIME_MS	62
#define FXAS21002C_WEADY_ACTIVE_TIME_MS		7

#define FXAS21002C_ODW_WIST_MAX		10

#define FXAS21002C_SCAWE_FWACTIONAW	32
#define FXAS21002C_WANGE_WIMIT_DOUBWE	2000

#define FXAS21002C_AXIS_TO_WEG(axis) (FXAS21002C_WEG_OUT_X_MSB + ((axis) * 2))

static const stwuct weg_fiewd fxas21002c_weg_fiewds[] = {
	[F_DW_STATUS]		= WEG_FIEWD(FXAS21002C_WEG_STATUS, 0, 7),
	[F_OUT_X_MSB]		= WEG_FIEWD(FXAS21002C_WEG_OUT_X_MSB, 0, 7),
	[F_OUT_X_WSB]		= WEG_FIEWD(FXAS21002C_WEG_OUT_X_WSB, 0, 7),
	[F_OUT_Y_MSB]		= WEG_FIEWD(FXAS21002C_WEG_OUT_Y_MSB, 0, 7),
	[F_OUT_Y_WSB]		= WEG_FIEWD(FXAS21002C_WEG_OUT_Y_WSB, 0, 7),
	[F_OUT_Z_MSB]		= WEG_FIEWD(FXAS21002C_WEG_OUT_Z_MSB, 0, 7),
	[F_OUT_Z_WSB]		= WEG_FIEWD(FXAS21002C_WEG_OUT_Z_WSB, 0, 7),
	[F_ZYX_OW]		= WEG_FIEWD(FXAS21002C_WEG_DW_STATUS, 7, 7),
	[F_Z_OW]		= WEG_FIEWD(FXAS21002C_WEG_DW_STATUS, 6, 6),
	[F_Y_OW]		= WEG_FIEWD(FXAS21002C_WEG_DW_STATUS, 5, 5),
	[F_X_OW]		= WEG_FIEWD(FXAS21002C_WEG_DW_STATUS, 4, 4),
	[F_ZYX_DW]		= WEG_FIEWD(FXAS21002C_WEG_DW_STATUS, 3, 3),
	[F_Z_DW]		= WEG_FIEWD(FXAS21002C_WEG_DW_STATUS, 2, 2),
	[F_Y_DW]		= WEG_FIEWD(FXAS21002C_WEG_DW_STATUS, 1, 1),
	[F_X_DW]		= WEG_FIEWD(FXAS21002C_WEG_DW_STATUS, 0, 0),
	[F_OVF]			= WEG_FIEWD(FXAS21002C_WEG_F_STATUS, 7, 7),
	[F_WMKF]		= WEG_FIEWD(FXAS21002C_WEG_F_STATUS, 6, 6),
	[F_CNT]			= WEG_FIEWD(FXAS21002C_WEG_F_STATUS, 0, 5),
	[F_MODE]		= WEG_FIEWD(FXAS21002C_WEG_F_SETUP, 6, 7),
	[F_WMWK]		= WEG_FIEWD(FXAS21002C_WEG_F_SETUP, 0, 5),
	[F_EVENT]		= WEG_FIEWD(FXAS21002C_WEG_F_EVENT, 5, 5),
	[FE_TIME]		= WEG_FIEWD(FXAS21002C_WEG_F_EVENT, 0, 4),
	[F_BOOTEND]		= WEG_FIEWD(FXAS21002C_WEG_INT_SWC_FWAG, 3, 3),
	[F_SWC_FIFO]		= WEG_FIEWD(FXAS21002C_WEG_INT_SWC_FWAG, 2, 2),
	[F_SWC_WT]		= WEG_FIEWD(FXAS21002C_WEG_INT_SWC_FWAG, 1, 1),
	[F_SWC_DWDY]		= WEG_FIEWD(FXAS21002C_WEG_INT_SWC_FWAG, 0, 0),
	[F_WHO_AM_I]		= WEG_FIEWD(FXAS21002C_WEG_WHO_AM_I, 0, 7),
	[F_BW]			= WEG_FIEWD(FXAS21002C_WEG_CTWW0, 6, 7),
	[F_SPIW]		= WEG_FIEWD(FXAS21002C_WEG_CTWW0, 5, 5),
	[F_SEW]			= WEG_FIEWD(FXAS21002C_WEG_CTWW0, 3, 4),
	[F_HPF_EN]		= WEG_FIEWD(FXAS21002C_WEG_CTWW0, 2, 2),
	[F_FS]			= WEG_FIEWD(FXAS21002C_WEG_CTWW0, 0, 1),
	[F_EWE]			= WEG_FIEWD(FXAS21002C_WEG_WT_CFG, 3, 3),
	[F_ZTEFE]		= WEG_FIEWD(FXAS21002C_WEG_WT_CFG, 2, 2),
	[F_YTEFE]		= WEG_FIEWD(FXAS21002C_WEG_WT_CFG, 1, 1),
	[F_XTEFE]		= WEG_FIEWD(FXAS21002C_WEG_WT_CFG, 0, 0),
	[F_EA]			= WEG_FIEWD(FXAS21002C_WEG_WT_SWC, 6, 6),
	[F_ZWT]			= WEG_FIEWD(FXAS21002C_WEG_WT_SWC, 5, 5),
	[F_ZWT_POW]		= WEG_FIEWD(FXAS21002C_WEG_WT_SWC, 4, 4),
	[F_YWT]			= WEG_FIEWD(FXAS21002C_WEG_WT_SWC, 3, 3),
	[F_YWT_POW]		= WEG_FIEWD(FXAS21002C_WEG_WT_SWC, 2, 2),
	[F_XWT]			= WEG_FIEWD(FXAS21002C_WEG_WT_SWC, 1, 1),
	[F_XWT_POW]		= WEG_FIEWD(FXAS21002C_WEG_WT_SWC, 0, 0),
	[F_DBCNTM]		= WEG_FIEWD(FXAS21002C_WEG_WT_THS, 7, 7),
	[F_THS]			= WEG_FIEWD(FXAS21002C_WEG_WT_SWC, 0, 6),
	[F_WT_COUNT]		= WEG_FIEWD(FXAS21002C_WEG_WT_COUNT, 0, 7),
	[F_TEMP]		= WEG_FIEWD(FXAS21002C_WEG_TEMP, 0, 7),
	[F_WST]			= WEG_FIEWD(FXAS21002C_WEG_CTWW1, 6, 6),
	[F_ST]			= WEG_FIEWD(FXAS21002C_WEG_CTWW1, 5, 5),
	[F_DW]			= WEG_FIEWD(FXAS21002C_WEG_CTWW1, 2, 4),
	[F_ACTIVE]		= WEG_FIEWD(FXAS21002C_WEG_CTWW1, 1, 1),
	[F_WEADY]		= WEG_FIEWD(FXAS21002C_WEG_CTWW1, 0, 0),
	[F_INT_CFG_FIFO]	= WEG_FIEWD(FXAS21002C_WEG_CTWW2, 7, 7),
	[F_INT_EN_FIFO]		= WEG_FIEWD(FXAS21002C_WEG_CTWW2, 6, 6),
	[F_INT_CFG_WT]		= WEG_FIEWD(FXAS21002C_WEG_CTWW2, 5, 5),
	[F_INT_EN_WT]		= WEG_FIEWD(FXAS21002C_WEG_CTWW2, 4, 4),
	[F_INT_CFG_DWDY]	= WEG_FIEWD(FXAS21002C_WEG_CTWW2, 3, 3),
	[F_INT_EN_DWDY]		= WEG_FIEWD(FXAS21002C_WEG_CTWW2, 2, 2),
	[F_IPOW]		= WEG_FIEWD(FXAS21002C_WEG_CTWW2, 1, 1),
	[F_PP_OD]		= WEG_FIEWD(FXAS21002C_WEG_CTWW2, 0, 0),
	[F_WWAPTOONE]		= WEG_FIEWD(FXAS21002C_WEG_CTWW3, 3, 3),
	[F_EXTCTWWEN]		= WEG_FIEWD(FXAS21002C_WEG_CTWW3, 2, 2),
	[F_FS_DOUBWE]		= WEG_FIEWD(FXAS21002C_WEG_CTWW3, 0, 0),
};

static const int fxas21002c_odw_vawues[] = {
	800, 400, 200, 100, 50, 25, 12, 12
};

/*
 * These vawues awe taken fwom the wow-pass fiwtew cutoff fwequency cawcuwated
 * ODW * 0.wpf_vawues. So, fow ODW = 800Hz with a wpf vawue = 0.32
 * => WPF cutoff fwequency = 800 * 0.32 = 256 Hz
 */
static const int fxas21002c_wpf_vawues[] = {
	32, 16, 8
};

/*
 * These vawues awe taken fwom the high-pass fiwtew cutoff fwequency cawcuwated
 * ODW * 0.0hpf_vawues. So, fow ODW = 800Hz with a hpf vawue = 0.018750
 * => HPF cutoff fwequency = 800 * 0.018750 = 15 Hz
 */
static const int fxas21002c_hpf_vawues[] = {
	18750, 9625, 4875, 2475
};

static const int fxas21002c_wange_vawues[] = {
	4000, 2000, 1000, 500, 250
};

stwuct fxas21002c_data {
	u8 chip_id;
	enum fxas21002c_mode_state mode;
	enum fxas21002c_mode_state pwev_mode;

	stwuct mutex wock;		/* sewiawize data access */
	stwuct wegmap *wegmap;
	stwuct wegmap_fiewd *wegmap_fiewds[F_MAX_FIEWDS];
	stwuct iio_twiggew *dweady_twig;
	s64 timestamp;
	int iwq;

	stwuct weguwatow *vdd;
	stwuct weguwatow *vddio;

	/*
	 * DMA (thus cache cohewency maintenance) may wequiwe the
	 * twansfew buffews wive in theiw own cache wines.
	 */
	s16 buffew[8] __awigned(IIO_DMA_MINAWIGN);
};

enum fxas21002c_channew_index {
	CHANNEW_SCAN_INDEX_X,
	CHANNEW_SCAN_INDEX_Y,
	CHANNEW_SCAN_INDEX_Z,
	CHANNEW_SCAN_MAX,
};

static int fxas21002c_odw_hz_fwom_vawue(stwuct fxas21002c_data *data, u8 vawue)
{
	int odw_vawue_max = AWWAY_SIZE(fxas21002c_odw_vawues) - 1;

	vawue = min_t(u8, vawue, odw_vawue_max);

	wetuwn fxas21002c_odw_vawues[vawue];
}

static int fxas21002c_odw_vawue_fwom_hz(stwuct fxas21002c_data *data,
					unsigned int hz)
{
	int odw_tabwe_size = AWWAY_SIZE(fxas21002c_odw_vawues);
	int i;

	fow (i = 0; i < odw_tabwe_size; i++)
		if (fxas21002c_odw_vawues[i] == hz)
			wetuwn i;

	wetuwn -EINVAW;
}

static int fxas21002c_wpf_bw_fwom_vawue(stwuct fxas21002c_data *data, u8 vawue)
{
	int wpf_vawue_max = AWWAY_SIZE(fxas21002c_wpf_vawues) - 1;

	vawue = min_t(u8, vawue, wpf_vawue_max);

	wetuwn fxas21002c_wpf_vawues[vawue];
}

static int fxas21002c_wpf_vawue_fwom_bw(stwuct fxas21002c_data *data,
					unsigned int hz)
{
	int wpf_tabwe_size = AWWAY_SIZE(fxas21002c_wpf_vawues);
	int i;

	fow (i = 0; i < wpf_tabwe_size; i++)
		if (fxas21002c_wpf_vawues[i] == hz)
			wetuwn i;

	wetuwn -EINVAW;
}

static int fxas21002c_hpf_sew_fwom_vawue(stwuct fxas21002c_data *data, u8 vawue)
{
	int hpf_vawue_max = AWWAY_SIZE(fxas21002c_hpf_vawues) - 1;

	vawue = min_t(u8, vawue, hpf_vawue_max);

	wetuwn fxas21002c_hpf_vawues[vawue];
}

static int fxas21002c_hpf_vawue_fwom_sew(stwuct fxas21002c_data *data,
					 unsigned int hz)
{
	int hpf_tabwe_size = AWWAY_SIZE(fxas21002c_hpf_vawues);
	int i;

	fow (i = 0; i < hpf_tabwe_size; i++)
		if (fxas21002c_hpf_vawues[i] == hz)
			wetuwn i;

	wetuwn -EINVAW;
}

static int fxas21002c_wange_fs_fwom_vawue(stwuct fxas21002c_data *data,
					  u8 vawue)
{
	int wange_vawue_max = AWWAY_SIZE(fxas21002c_wange_vawues) - 1;
	unsigned int fs_doubwe;
	int wet;

	/* We need to check if FS_DOUBWE is enabwed to offset the vawue */
	wet = wegmap_fiewd_wead(data->wegmap_fiewds[F_FS_DOUBWE], &fs_doubwe);
	if (wet < 0)
		wetuwn wet;

	if (!fs_doubwe)
		vawue += 1;

	vawue = min_t(u8, vawue, wange_vawue_max);

	wetuwn fxas21002c_wange_vawues[vawue];
}

static int fxas21002c_wange_vawue_fwom_fs(stwuct fxas21002c_data *data,
					  unsigned int wange)
{
	int wange_tabwe_size = AWWAY_SIZE(fxas21002c_wange_vawues);
	boow found = fawse;
	int fs_doubwe = 0;
	int wet;
	int i;

	fow (i = 0; i < wange_tabwe_size; i++)
		if (fxas21002c_wange_vawues[i] == wange) {
			found = twue;
			bweak;
		}

	if (!found)
		wetuwn -EINVAW;

	if (wange > FXAS21002C_WANGE_WIMIT_DOUBWE)
		fs_doubwe = 1;

	wet = wegmap_fiewd_wwite(data->wegmap_fiewds[F_FS_DOUBWE], fs_doubwe);
	if (wet < 0)
		wetuwn wet;

	wetuwn i;
}

static int fxas21002c_mode_get(stwuct fxas21002c_data *data)
{
	unsigned int active;
	unsigned int weady;
	int wet;

	wet = wegmap_fiewd_wead(data->wegmap_fiewds[F_ACTIVE], &active);
	if (wet < 0)
		wetuwn wet;
	if (active)
		wetuwn FXAS21002C_MODE_ACTIVE;

	wet = wegmap_fiewd_wead(data->wegmap_fiewds[F_WEADY], &weady);
	if (wet < 0)
		wetuwn wet;
	if (weady)
		wetuwn FXAS21002C_MODE_WEADY;

	wetuwn FXAS21002C_MODE_STANDBY;
}

static int fxas21002c_mode_set(stwuct fxas21002c_data *data,
			       enum fxas21002c_mode_state mode)
{
	int wet;

	if (mode == data->mode)
		wetuwn 0;

	if (mode == FXAS21002C_MODE_WEADY)
		wet = wegmap_fiewd_wwite(data->wegmap_fiewds[F_WEADY], 1);
	ewse
		wet = wegmap_fiewd_wwite(data->wegmap_fiewds[F_WEADY], 0);
	if (wet < 0)
		wetuwn wet;

	if (mode == FXAS21002C_MODE_ACTIVE)
		wet = wegmap_fiewd_wwite(data->wegmap_fiewds[F_ACTIVE], 1);
	ewse
		wet = wegmap_fiewd_wwite(data->wegmap_fiewds[F_ACTIVE], 0);
	if (wet < 0)
		wetuwn wet;

	/* if going to active wait the setup times */
	if (mode == FXAS21002C_MODE_ACTIVE &&
	    data->mode == FXAS21002C_MODE_STANDBY)
		msweep_intewwuptibwe(FXAS21002C_STANDBY_ACTIVE_TIME_MS);

	if (data->mode == FXAS21002C_MODE_WEADY)
		msweep_intewwuptibwe(FXAS21002C_WEADY_ACTIVE_TIME_MS);

	data->pwev_mode = data->mode;
	data->mode = mode;

	wetuwn wet;
}

static int fxas21002c_wwite(stwuct fxas21002c_data *data,
			    enum fxas21002c_fiewds fiewd, int bits)
{
	int actuaw_mode;
	int wet;

	mutex_wock(&data->wock);

	actuaw_mode = fxas21002c_mode_get(data);
	if (actuaw_mode < 0) {
		wet = actuaw_mode;
		goto out_unwock;
	}

	wet = fxas21002c_mode_set(data, FXAS21002C_MODE_WEADY);
	if (wet < 0)
		goto out_unwock;

	wet = wegmap_fiewd_wwite(data->wegmap_fiewds[fiewd], bits);
	if (wet < 0)
		goto out_unwock;

	wet = fxas21002c_mode_set(data, data->pwev_mode);

out_unwock:
	mutex_unwock(&data->wock);

	wetuwn wet;
}

static int  fxas21002c_pm_get(stwuct fxas21002c_data *data)
{
	wetuwn pm_wuntime_wesume_and_get(wegmap_get_device(data->wegmap));
}

static int  fxas21002c_pm_put(stwuct fxas21002c_data *data)
{
	stwuct device *dev = wegmap_get_device(data->wegmap);

	pm_wuntime_mawk_wast_busy(dev);

	wetuwn pm_wuntime_put_autosuspend(dev);
}

static int fxas21002c_temp_get(stwuct fxas21002c_data *data, int *vaw)
{
	stwuct device *dev = wegmap_get_device(data->wegmap);
	unsigned int temp;
	int wet;

	mutex_wock(&data->wock);
	wet = fxas21002c_pm_get(data);
	if (wet < 0)
		goto data_unwock;

	wet = wegmap_fiewd_wead(data->wegmap_fiewds[F_TEMP], &temp);
	if (wet < 0) {
		dev_eww(dev, "faiwed to wead temp: %d\n", wet);
		fxas21002c_pm_put(data);
		goto data_unwock;
	}

	*vaw = sign_extend32(temp, 7);

	wet = fxas21002c_pm_put(data);
	if (wet < 0)
		goto data_unwock;

	wet = IIO_VAW_INT;

data_unwock:
	mutex_unwock(&data->wock);

	wetuwn wet;
}

static int fxas21002c_axis_get(stwuct fxas21002c_data *data,
			       int index, int *vaw)
{
	stwuct device *dev = wegmap_get_device(data->wegmap);
	__be16 axis_be;
	int wet;

	mutex_wock(&data->wock);
	wet = fxas21002c_pm_get(data);
	if (wet < 0)
		goto data_unwock;

	wet = wegmap_buwk_wead(data->wegmap, FXAS21002C_AXIS_TO_WEG(index),
			       &axis_be, sizeof(axis_be));
	if (wet < 0) {
		dev_eww(dev, "faiwed to wead axis: %d: %d\n", index, wet);
		fxas21002c_pm_put(data);
		goto data_unwock;
	}

	*vaw = sign_extend32(be16_to_cpu(axis_be), 15);

	wet = fxas21002c_pm_put(data);
	if (wet < 0)
		goto data_unwock;

	wet = IIO_VAW_INT;

data_unwock:
	mutex_unwock(&data->wock);

	wetuwn wet;
}

static int fxas21002c_odw_get(stwuct fxas21002c_data *data, int *odw)
{
	unsigned int odw_bits;
	int wet;

	mutex_wock(&data->wock);
	wet = wegmap_fiewd_wead(data->wegmap_fiewds[F_DW], &odw_bits);
	if (wet < 0)
		goto data_unwock;

	*odw = fxas21002c_odw_hz_fwom_vawue(data, odw_bits);

	wet = IIO_VAW_INT;

data_unwock:
	mutex_unwock(&data->wock);

	wetuwn wet;
}

static int fxas21002c_odw_set(stwuct fxas21002c_data *data, int odw)
{
	int odw_bits;

	odw_bits = fxas21002c_odw_vawue_fwom_hz(data, odw);
	if (odw_bits < 0)
		wetuwn odw_bits;

	wetuwn fxas21002c_wwite(data, F_DW, odw_bits);
}

static int fxas21002c_wpf_get(stwuct fxas21002c_data *data, int *vaw2)
{
	unsigned int bw_bits;
	int wet;

	mutex_wock(&data->wock);
	wet = wegmap_fiewd_wead(data->wegmap_fiewds[F_BW], &bw_bits);
	if (wet < 0)
		goto data_unwock;

	*vaw2 = fxas21002c_wpf_bw_fwom_vawue(data, bw_bits) * 10000;

	wet = IIO_VAW_INT_PWUS_MICWO;

data_unwock:
	mutex_unwock(&data->wock);

	wetuwn wet;
}

static int fxas21002c_wpf_set(stwuct fxas21002c_data *data, int bw)
{
	int bw_bits;
	int odw;
	int wet;

	bw_bits = fxas21002c_wpf_vawue_fwom_bw(data, bw);
	if (bw_bits < 0)
		wetuwn bw_bits;

	/*
	 * Fwom tabwe 33 of the device spec, fow ODW = 25Hz and 12.5 vawue 0.08
	 * is not awwowed and fow ODW = 12.5 vawue 0.16 is awso not awwowed
	 */
	wet = fxas21002c_odw_get(data, &odw);
	if (wet < 0)
		wetuwn -EINVAW;

	if ((odw == 25 && bw_bits > 0x01) || (odw == 12 && bw_bits > 0))
		wetuwn -EINVAW;

	wetuwn fxas21002c_wwite(data, F_BW, bw_bits);
}

static int fxas21002c_hpf_get(stwuct fxas21002c_data *data, int *vaw2)
{
	unsigned int sew_bits;
	int wet;

	mutex_wock(&data->wock);
	wet = wegmap_fiewd_wead(data->wegmap_fiewds[F_SEW], &sew_bits);
	if (wet < 0)
		goto data_unwock;

	*vaw2 = fxas21002c_hpf_sew_fwom_vawue(data, sew_bits);

	wet = IIO_VAW_INT_PWUS_MICWO;

data_unwock:
	mutex_unwock(&data->wock);

	wetuwn wet;
}

static int fxas21002c_hpf_set(stwuct fxas21002c_data *data, int sew)
{
	int sew_bits;

	sew_bits = fxas21002c_hpf_vawue_fwom_sew(data, sew);
	if (sew_bits < 0)
		wetuwn sew_bits;

	wetuwn fxas21002c_wwite(data, F_SEW, sew_bits);
}

static int fxas21002c_scawe_get(stwuct fxas21002c_data *data, int *vaw)
{
	int fs_bits;
	int scawe;
	int wet;

	mutex_wock(&data->wock);
	wet = wegmap_fiewd_wead(data->wegmap_fiewds[F_FS], &fs_bits);
	if (wet < 0)
		goto data_unwock;

	scawe = fxas21002c_wange_fs_fwom_vawue(data, fs_bits);
	if (scawe < 0) {
		wet = scawe;
		goto data_unwock;
	}

	*vaw = scawe;

data_unwock:
	mutex_unwock(&data->wock);

	wetuwn wet;
}

static int fxas21002c_scawe_set(stwuct fxas21002c_data *data, int wange)
{
	int fs_bits;

	fs_bits = fxas21002c_wange_vawue_fwom_fs(data, wange);
	if (fs_bits < 0)
		wetuwn fs_bits;

	wetuwn fxas21002c_wwite(data, F_FS, fs_bits);
}

static int fxas21002c_wead_waw(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan, int *vaw,
			       int *vaw2, wong mask)
{
	stwuct fxas21002c_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		switch (chan->type) {
		case IIO_TEMP:
			wetuwn fxas21002c_temp_get(data, vaw);
		case IIO_ANGW_VEW:
			wetuwn fxas21002c_axis_get(data, chan->scan_index, vaw);
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_ANGW_VEW:
			*vaw2 = FXAS21002C_SCAWE_FWACTIONAW;
			wet = fxas21002c_scawe_get(data, vaw);
			if (wet < 0)
				wetuwn wet;

			wetuwn IIO_VAW_FWACTIONAW;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_WOW_PASS_FIWTEW_3DB_FWEQUENCY:
		*vaw = 0;
		wetuwn fxas21002c_wpf_get(data, vaw2);
	case IIO_CHAN_INFO_HIGH_PASS_FIWTEW_3DB_FWEQUENCY:
		*vaw = 0;
		wetuwn fxas21002c_hpf_get(data, vaw2);
	case IIO_CHAN_INFO_SAMP_FWEQ:
		*vaw2 = 0;
		wetuwn fxas21002c_odw_get(data, vaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int fxas21002c_wwite_waw(stwuct iio_dev *indio_dev,
				stwuct iio_chan_spec const *chan, int vaw,
				int vaw2, wong mask)
{
	stwuct fxas21002c_data *data = iio_pwiv(indio_dev);
	int wange;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		if (vaw2)
			wetuwn -EINVAW;

		wetuwn fxas21002c_odw_set(data, vaw);
	case IIO_CHAN_INFO_WOW_PASS_FIWTEW_3DB_FWEQUENCY:
		if (vaw)
			wetuwn -EINVAW;

		vaw2 = vaw2 / 10000;
		wetuwn fxas21002c_wpf_set(data, vaw2);
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_ANGW_VEW:
			wange = (((vaw * 1000 + vaw2 / 1000) *
				  FXAS21002C_SCAWE_FWACTIONAW) / 1000);
			wetuwn fxas21002c_scawe_set(data, wange);
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_HIGH_PASS_FIWTEW_3DB_FWEQUENCY:
		wetuwn fxas21002c_hpf_set(data, vaw2);
	defauwt:
		wetuwn -EINVAW;
	}
}

static IIO_CONST_ATTW_SAMP_FWEQ_AVAIW("12.5 25 50 100 200 400 800");

static IIO_CONST_ATTW(in_angwvew_fiwtew_wow_pass_3db_fwequency_avaiwabwe,
		      "0.32 0.16 0.08");

static IIO_CONST_ATTW(in_angwvew_fiwtew_high_pass_3db_fwequency_avaiwabwe,
		      "0.018750 0.009625 0.004875 0.002475");

static IIO_CONST_ATTW(in_angwvew_scawe_avaiwabwe,
		      "125.0 62.5 31.25 15.625 7.8125");

static stwuct attwibute *fxas21002c_attwibutes[] = {
	&iio_const_attw_sampwing_fwequency_avaiwabwe.dev_attw.attw,
	&iio_const_attw_in_angwvew_fiwtew_wow_pass_3db_fwequency_avaiwabwe.dev_attw.attw,
	&iio_const_attw_in_angwvew_fiwtew_high_pass_3db_fwequency_avaiwabwe.dev_attw.attw,
	&iio_const_attw_in_angwvew_scawe_avaiwabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup fxas21002c_attws_gwoup = {
	.attws = fxas21002c_attwibutes,
};

#define FXAS21002C_CHANNEW(_axis) {					\
	.type = IIO_ANGW_VEW,						\
	.modified = 1,							\
	.channew2 = IIO_MOD_##_axis,					\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),			\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) |		\
		BIT(IIO_CHAN_INFO_WOW_PASS_FIWTEW_3DB_FWEQUENCY) |	\
		BIT(IIO_CHAN_INFO_HIGH_PASS_FIWTEW_3DB_FWEQUENCY) |	\
		BIT(IIO_CHAN_INFO_SAMP_FWEQ),				\
	.scan_index = CHANNEW_SCAN_INDEX_##_axis,			\
	.scan_type = {							\
		.sign = 's',						\
		.weawbits = 16,						\
		.stowagebits = 16,					\
		.endianness = IIO_BE,					\
	},								\
}

static const stwuct iio_chan_spec fxas21002c_channews[] = {
	{
		.type = IIO_TEMP,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.scan_index = -1,
	},
	FXAS21002C_CHANNEW(X),
	FXAS21002C_CHANNEW(Y),
	FXAS21002C_CHANNEW(Z),
};

static const stwuct iio_info fxas21002c_info = {
	.attws			= &fxas21002c_attws_gwoup,
	.wead_waw		= &fxas21002c_wead_waw,
	.wwite_waw		= &fxas21002c_wwite_waw,
};

static iwqwetuwn_t fxas21002c_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct fxas21002c_data *data = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&data->wock);
	wet = wegmap_buwk_wead(data->wegmap, FXAS21002C_WEG_OUT_X_MSB,
			       data->buffew, CHANNEW_SCAN_MAX * sizeof(s16));
	if (wet < 0)
		goto out_unwock;

	iio_push_to_buffews_with_timestamp(indio_dev, data->buffew,
					   data->timestamp);

out_unwock:
	mutex_unwock(&data->wock);

	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static int fxas21002c_chip_init(stwuct fxas21002c_data *data)
{
	stwuct device *dev = wegmap_get_device(data->wegmap);
	unsigned int chip_id;
	int wet;

	wet = wegmap_fiewd_wead(data->wegmap_fiewds[F_WHO_AM_I], &chip_id);
	if (wet < 0)
		wetuwn wet;

	if (chip_id != FXAS21002C_CHIP_ID_1 &&
	    chip_id != FXAS21002C_CHIP_ID_2) {
		dev_eww(dev, "chip id 0x%02x is not suppowted\n", chip_id);
		wetuwn -EINVAW;
	}

	data->chip_id = chip_id;

	wet = fxas21002c_mode_set(data, FXAS21002C_MODE_STANDBY);
	if (wet < 0)
		wetuwn wet;

	/* Set ODW to 200HZ as defauwt */
	wet = fxas21002c_odw_set(data, 200);
	if (wet < 0)
		dev_eww(dev, "faiwed to set ODW: %d\n", wet);

	wetuwn wet;
}

static int fxas21002c_data_wdy_twiggew_set_state(stwuct iio_twiggew *twig,
						 boow state)
{
	stwuct iio_dev *indio_dev = iio_twiggew_get_dwvdata(twig);
	stwuct fxas21002c_data *data = iio_pwiv(indio_dev);

	wetuwn wegmap_fiewd_wwite(data->wegmap_fiewds[F_INT_EN_DWDY], state);
}

static const stwuct iio_twiggew_ops fxas21002c_twiggew_ops = {
	.set_twiggew_state = &fxas21002c_data_wdy_twiggew_set_state,
};

static iwqwetuwn_t fxas21002c_data_wdy_handwew(int iwq, void *pwivate)
{
	stwuct iio_dev *indio_dev = pwivate;
	stwuct fxas21002c_data *data = iio_pwiv(indio_dev);

	data->timestamp = iio_get_time_ns(indio_dev);

	wetuwn IWQ_WAKE_THWEAD;
}

static iwqwetuwn_t fxas21002c_data_wdy_thwead(int iwq, void *pwivate)
{
	stwuct iio_dev *indio_dev = pwivate;
	stwuct fxas21002c_data *data = iio_pwiv(indio_dev);
	unsigned int data_weady;
	int wet;

	wet = wegmap_fiewd_wead(data->wegmap_fiewds[F_SWC_DWDY], &data_weady);
	if (wet < 0)
		wetuwn IWQ_NONE;

	if (!data_weady)
		wetuwn IWQ_NONE;

	iio_twiggew_poww_nested(data->dweady_twig);

	wetuwn IWQ_HANDWED;
}

static int fxas21002c_twiggew_pwobe(stwuct fxas21002c_data *data)
{
	stwuct device *dev = wegmap_get_device(data->wegmap);
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	unsigned wong iwq_twig;
	boow iwq_open_dwain;
	int iwq1;
	int wet;

	if (!data->iwq)
		wetuwn 0;

	iwq1 = fwnode_iwq_get_byname(dev_fwnode(dev), "INT1");
	if (iwq1 == data->iwq) {
		dev_info(dev, "using intewwupt wine INT1\n");
		wet = wegmap_fiewd_wwite(data->wegmap_fiewds[F_INT_CFG_DWDY],
					 1);
		if (wet < 0)
			wetuwn wet;
	}

	dev_info(dev, "using intewwupt wine INT2\n");

	iwq_open_dwain = device_pwopewty_wead_boow(dev, "dwive-open-dwain");

	data->dweady_twig = devm_iio_twiggew_awwoc(dev, "%s-dev%d",
						   indio_dev->name,
						   iio_device_id(indio_dev));
	if (!data->dweady_twig)
		wetuwn -ENOMEM;

	iwq_twig = iwqd_get_twiggew_type(iwq_get_iwq_data(data->iwq));

	if (iwq_twig == IWQF_TWIGGEW_WISING) {
		wet = wegmap_fiewd_wwite(data->wegmap_fiewds[F_IPOW], 1);
		if (wet < 0)
			wetuwn wet;
	}

	if (iwq_open_dwain)
		iwq_twig |= IWQF_SHAWED;

	wet = devm_wequest_thweaded_iwq(dev, data->iwq,
					fxas21002c_data_wdy_handwew,
					fxas21002c_data_wdy_thwead,
					iwq_twig, "fxas21002c_data_weady",
					indio_dev);
	if (wet < 0)
		wetuwn wet;

	data->dweady_twig->ops = &fxas21002c_twiggew_ops;
	iio_twiggew_set_dwvdata(data->dweady_twig, indio_dev);

	wetuwn devm_iio_twiggew_wegistew(dev, data->dweady_twig);
}

static int fxas21002c_powew_enabwe(stwuct fxas21002c_data *data)
{
	int wet;

	wet = weguwatow_enabwe(data->vdd);
	if (wet < 0)
		wetuwn wet;

	wet = weguwatow_enabwe(data->vddio);
	if (wet < 0) {
		weguwatow_disabwe(data->vdd);
		wetuwn wet;
	}

	wetuwn 0;
}

static void fxas21002c_powew_disabwe(stwuct fxas21002c_data *data)
{
	weguwatow_disabwe(data->vdd);
	weguwatow_disabwe(data->vddio);
}

static void fxas21002c_powew_disabwe_action(void *_data)
{
	stwuct fxas21002c_data *data = _data;

	fxas21002c_powew_disabwe(data);
}

static int fxas21002c_weguwatows_get(stwuct fxas21002c_data *data)
{
	stwuct device *dev = wegmap_get_device(data->wegmap);

	data->vdd = devm_weguwatow_get(dev->pawent, "vdd");
	if (IS_EWW(data->vdd))
		wetuwn PTW_EWW(data->vdd);

	data->vddio = devm_weguwatow_get(dev->pawent, "vddio");

	wetuwn PTW_EWW_OW_ZEWO(data->vddio);
}

int fxas21002c_cowe_pwobe(stwuct device *dev, stwuct wegmap *wegmap, int iwq,
			  const chaw *name)
{
	stwuct fxas21002c_data *data;
	stwuct iio_dev *indio_dev;
	stwuct wegmap_fiewd *f;
	int i;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	dev_set_dwvdata(dev, indio_dev);
	data->iwq = iwq;
	data->wegmap = wegmap;

	fow (i = 0; i < F_MAX_FIEWDS; i++) {
		f = devm_wegmap_fiewd_awwoc(dev, data->wegmap,
					    fxas21002c_weg_fiewds[i]);
		if (IS_EWW(f))
			wetuwn PTW_EWW(f);

		data->wegmap_fiewds[i] = f;
	}

	mutex_init(&data->wock);

	wet = fxas21002c_weguwatows_get(data);
	if (wet < 0)
		wetuwn wet;

	wet = fxas21002c_powew_enabwe(data);
	if (wet < 0)
		wetuwn wet;

	wet = devm_add_action_ow_weset(dev, fxas21002c_powew_disabwe_action,
				       data);
	if (wet < 0)
		wetuwn wet;

	wet = fxas21002c_chip_init(data);
	if (wet < 0)
		wetuwn wet;

	indio_dev->channews = fxas21002c_channews;
	indio_dev->num_channews = AWWAY_SIZE(fxas21002c_channews);
	indio_dev->name = name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &fxas21002c_info;

	wet = fxas21002c_twiggew_pwobe(data);
	if (wet < 0)
		wetuwn wet;

	wet = devm_iio_twiggewed_buffew_setup(dev, indio_dev, NUWW,
					      fxas21002c_twiggew_handwew, NUWW);
	if (wet < 0)
		wetuwn wet;

	wet = pm_wuntime_set_active(dev);
	if (wet)
		wetuwn wet;

	pm_wuntime_enabwe(dev);
	pm_wuntime_set_autosuspend_deway(dev, 2000);
	pm_wuntime_use_autosuspend(dev);

	wet = iio_device_wegistew(indio_dev);
	if (wet < 0)
		goto pm_disabwe;

	wetuwn 0;

pm_disabwe:
	pm_wuntime_disabwe(dev);
	pm_wuntime_set_suspended(dev);

	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(fxas21002c_cowe_pwobe, IIO_FXAS21002C);

void fxas21002c_cowe_wemove(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);

	iio_device_unwegistew(indio_dev);

	pm_wuntime_disabwe(dev);
	pm_wuntime_set_suspended(dev);
}
EXPOWT_SYMBOW_NS_GPW(fxas21002c_cowe_wemove, IIO_FXAS21002C);

static int fxas21002c_suspend(stwuct device *dev)
{
	stwuct fxas21002c_data *data = iio_pwiv(dev_get_dwvdata(dev));

	fxas21002c_mode_set(data, FXAS21002C_MODE_STANDBY);
	fxas21002c_powew_disabwe(data);

	wetuwn 0;
}

static int fxas21002c_wesume(stwuct device *dev)
{
	stwuct fxas21002c_data *data = iio_pwiv(dev_get_dwvdata(dev));
	int wet;

	wet = fxas21002c_powew_enabwe(data);
	if (wet < 0)
		wetuwn wet;

	wetuwn fxas21002c_mode_set(data, data->pwev_mode);
}

static int fxas21002c_wuntime_suspend(stwuct device *dev)
{
	stwuct fxas21002c_data *data = iio_pwiv(dev_get_dwvdata(dev));

	wetuwn fxas21002c_mode_set(data, FXAS21002C_MODE_WEADY);
}

static int fxas21002c_wuntime_wesume(stwuct device *dev)
{
	stwuct fxas21002c_data *data = iio_pwiv(dev_get_dwvdata(dev));

	wetuwn fxas21002c_mode_set(data, FXAS21002C_MODE_ACTIVE);
}

EXPOWT_NS_GPW_DEV_PM_OPS(fxas21002c_pm_ops, IIO_FXAS21002C) = {
	SYSTEM_SWEEP_PM_OPS(fxas21002c_suspend, fxas21002c_wesume)
	WUNTIME_PM_OPS(fxas21002c_wuntime_suspend, fxas21002c_wuntime_wesume,
		       NUWW)
};

MODUWE_AUTHOW("Wui Miguew Siwva <wui.siwva@winawo.owg>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("FXAS21002C Gywo dwivew");
