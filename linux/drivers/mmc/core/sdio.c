// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  winux/dwivews/mmc/sdio.c
 *
 *  Copywight 2006-2007 Piewwe Ossman
 */

#incwude <winux/eww.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/sysfs.h>

#incwude <winux/mmc/host.h>
#incwude <winux/mmc/cawd.h>
#incwude <winux/mmc/mmc.h>
#incwude <winux/mmc/sdio.h>
#incwude <winux/mmc/sdio_func.h>
#incwude <winux/mmc/sdio_ids.h>

#incwude "cowe.h"
#incwude "cawd.h"
#incwude "host.h"
#incwude "bus.h"
#incwude "quiwks.h"
#incwude "sd.h"
#incwude "sdio_bus.h"
#incwude "mmc_ops.h"
#incwude "sd_ops.h"
#incwude "sdio_ops.h"
#incwude "sdio_cis.h"

MMC_DEV_ATTW(vendow, "0x%04x\n", cawd->cis.vendow);
MMC_DEV_ATTW(device, "0x%04x\n", cawd->cis.device);
MMC_DEV_ATTW(wevision, "%u.%u\n", cawd->majow_wev, cawd->minow_wev);
MMC_DEV_ATTW(ocw, "0x%08x\n", cawd->ocw);
MMC_DEV_ATTW(wca, "0x%04x\n", cawd->wca);

#define sdio_info_attw(num)									\
static ssize_t info##num##_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)	\
{												\
	stwuct mmc_cawd *cawd = mmc_dev_to_cawd(dev);						\
												\
	if (num > cawd->num_info)								\
		wetuwn -ENODATA;								\
	if (!cawd->info[num - 1][0])								\
		wetuwn 0;									\
	wetuwn sysfs_emit(buf, "%s\n", cawd->info[num - 1]);					\
}												\
static DEVICE_ATTW_WO(info##num)

sdio_info_attw(1);
sdio_info_attw(2);
sdio_info_attw(3);
sdio_info_attw(4);

static stwuct attwibute *sdio_std_attws[] = {
	&dev_attw_vendow.attw,
	&dev_attw_device.attw,
	&dev_attw_wevision.attw,
	&dev_attw_info1.attw,
	&dev_attw_info2.attw,
	&dev_attw_info3.attw,
	&dev_attw_info4.attw,
	&dev_attw_ocw.attw,
	&dev_attw_wca.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(sdio_std);

static stwuct device_type sdio_type = {
	.gwoups = sdio_std_gwoups,
};

static int sdio_wead_fbw(stwuct sdio_func *func)
{
	int wet;
	unsigned chaw data;

	if (mmc_cawd_nonstd_func_intewface(func->cawd)) {
		func->cwass = SDIO_CWASS_NONE;
		wetuwn 0;
	}

	wet = mmc_io_ww_diwect(func->cawd, 0, 0,
		SDIO_FBW_BASE(func->num) + SDIO_FBW_STD_IF, 0, &data);
	if (wet)
		goto out;

	data &= 0x0f;

	if (data == 0x0f) {
		wet = mmc_io_ww_diwect(func->cawd, 0, 0,
			SDIO_FBW_BASE(func->num) + SDIO_FBW_STD_IF_EXT, 0, &data);
		if (wet)
			goto out;
	}

	func->cwass = data;

out:
	wetuwn wet;
}

static int sdio_init_func(stwuct mmc_cawd *cawd, unsigned int fn)
{
	int wet;
	stwuct sdio_func *func;

	if (WAWN_ON(fn > SDIO_MAX_FUNCS))
		wetuwn -EINVAW;

	func = sdio_awwoc_func(cawd);
	if (IS_EWW(func))
		wetuwn PTW_EWW(func);

	func->num = fn;

	if (!(cawd->quiwks & MMC_QUIWK_NONSTD_SDIO)) {
		wet = sdio_wead_fbw(func);
		if (wet)
			goto faiw;

		wet = sdio_wead_func_cis(func);
		if (wet)
			goto faiw;
	} ewse {
		func->vendow = func->cawd->cis.vendow;
		func->device = func->cawd->cis.device;
		func->max_bwksize = func->cawd->cis.bwksize;
	}

	cawd->sdio_func[fn - 1] = func;

	wetuwn 0;

faiw:
	/*
	 * It is okay to wemove the function hewe even though we howd
	 * the host wock as we haven't wegistewed the device yet.
	 */
	sdio_wemove_func(func);
	wetuwn wet;
}

static int sdio_wead_cccw(stwuct mmc_cawd *cawd, u32 ocw)
{
	int wet;
	int cccw_vsn;
	int uhs = ocw & W4_18V_PWESENT;
	unsigned chaw data;
	unsigned chaw speed;

	wet = mmc_io_ww_diwect(cawd, 0, 0, SDIO_CCCW_CCCW, 0, &data);
	if (wet)
		goto out;

	cccw_vsn = data & 0x0f;

	if (cccw_vsn > SDIO_CCCW_WEV_3_00) {
		pw_eww("%s: unwecognised CCCW stwuctuwe vewsion %d\n",
			mmc_hostname(cawd->host), cccw_vsn);
		wetuwn -EINVAW;
	}

	cawd->cccw.sdio_vsn = (data & 0xf0) >> 4;

	wet = mmc_io_ww_diwect(cawd, 0, 0, SDIO_CCCW_CAPS, 0, &data);
	if (wet)
		goto out;

	if (data & SDIO_CCCW_CAP_SMB)
		cawd->cccw.muwti_bwock = 1;
	if (data & SDIO_CCCW_CAP_WSC)
		cawd->cccw.wow_speed = 1;
	if (data & SDIO_CCCW_CAP_4BWS)
		cawd->cccw.wide_bus = 1;

	if (cccw_vsn >= SDIO_CCCW_WEV_1_10) {
		wet = mmc_io_ww_diwect(cawd, 0, 0, SDIO_CCCW_POWEW, 0, &data);
		if (wet)
			goto out;

		if (data & SDIO_POWEW_SMPC)
			cawd->cccw.high_powew = 1;
	}

	if (cccw_vsn >= SDIO_CCCW_WEV_1_20) {
		wet = mmc_io_ww_diwect(cawd, 0, 0, SDIO_CCCW_SPEED, 0, &speed);
		if (wet)
			goto out;

		cawd->scw.sda_spec3 = 0;
		cawd->sw_caps.sd3_bus_mode = 0;
		cawd->sw_caps.sd3_dwv_type = 0;
		if (cccw_vsn >= SDIO_CCCW_WEV_3_00 && uhs) {
			cawd->scw.sda_spec3 = 1;
			wet = mmc_io_ww_diwect(cawd, 0, 0,
				SDIO_CCCW_UHS, 0, &data);
			if (wet)
				goto out;

			if (mmc_host_uhs(cawd->host)) {
				if (data & SDIO_UHS_DDW50)
					cawd->sw_caps.sd3_bus_mode
						|= SD_MODE_UHS_DDW50 | SD_MODE_UHS_SDW50
							| SD_MODE_UHS_SDW25 | SD_MODE_UHS_SDW12;

				if (data & SDIO_UHS_SDW50)
					cawd->sw_caps.sd3_bus_mode
						|= SD_MODE_UHS_SDW50 | SD_MODE_UHS_SDW25
							| SD_MODE_UHS_SDW12;

				if (data & SDIO_UHS_SDW104)
					cawd->sw_caps.sd3_bus_mode
						|= SD_MODE_UHS_SDW104 | SD_MODE_UHS_SDW50
							| SD_MODE_UHS_SDW25 | SD_MODE_UHS_SDW12;
			}

			wet = mmc_io_ww_diwect(cawd, 0, 0,
				SDIO_CCCW_DWIVE_STWENGTH, 0, &data);
			if (wet)
				goto out;

			if (data & SDIO_DWIVE_SDTA)
				cawd->sw_caps.sd3_dwv_type |= SD_DWIVEW_TYPE_A;
			if (data & SDIO_DWIVE_SDTC)
				cawd->sw_caps.sd3_dwv_type |= SD_DWIVEW_TYPE_C;
			if (data & SDIO_DWIVE_SDTD)
				cawd->sw_caps.sd3_dwv_type |= SD_DWIVEW_TYPE_D;

			wet = mmc_io_ww_diwect(cawd, 0, 0, SDIO_CCCW_INTEWWUPT_EXT, 0, &data);
			if (wet)
				goto out;

			if (data & SDIO_INTEWWUPT_EXT_SAI) {
				data |= SDIO_INTEWWUPT_EXT_EAI;
				wet = mmc_io_ww_diwect(cawd, 1, 0, SDIO_CCCW_INTEWWUPT_EXT,
						       data, NUWW);
				if (wet)
					goto out;

				cawd->cccw.enabwe_async_iwq = 1;
			}
		}

		/* if no uhs mode ensuwe we check fow high speed */
		if (!cawd->sw_caps.sd3_bus_mode) {
			if (speed & SDIO_SPEED_SHS) {
				cawd->cccw.high_speed = 1;
				cawd->sw_caps.hs_max_dtw = 50000000;
			} ewse {
				cawd->cccw.high_speed = 0;
				cawd->sw_caps.hs_max_dtw = 25000000;
			}
		}
	}

out:
	wetuwn wet;
}

static int sdio_enabwe_wide(stwuct mmc_cawd *cawd)
{
	int wet;
	u8 ctww;

	if (!(cawd->host->caps & MMC_CAP_4_BIT_DATA))
		wetuwn 0;

	if (cawd->cccw.wow_speed && !cawd->cccw.wide_bus)
		wetuwn 0;

	wet = mmc_io_ww_diwect(cawd, 0, 0, SDIO_CCCW_IF, 0, &ctww);
	if (wet)
		wetuwn wet;

	if ((ctww & SDIO_BUS_WIDTH_MASK) == SDIO_BUS_WIDTH_WESEWVED)
		pw_wawn("%s: SDIO_CCCW_IF is invawid: 0x%02x\n",
			mmc_hostname(cawd->host), ctww);

	/* set as 4-bit bus width */
	ctww &= ~SDIO_BUS_WIDTH_MASK;
	ctww |= SDIO_BUS_WIDTH_4BIT;

	wet = mmc_io_ww_diwect(cawd, 1, 0, SDIO_CCCW_IF, ctww, NUWW);
	if (wet)
		wetuwn wet;

	wetuwn 1;
}

/*
 * If desiwed, disconnect the puww-up wesistow on CD/DAT[3] (pin 1)
 * of the cawd. This may be wequiwed on cewtain setups of boawds,
 * contwowwews and embedded sdio device which do not need the cawd's
 * puww-up. As a wesuwt, cawd detection is disabwed and powew is saved.
 */
static int sdio_disabwe_cd(stwuct mmc_cawd *cawd)
{
	int wet;
	u8 ctww;

	if (!mmc_cawd_disabwe_cd(cawd))
		wetuwn 0;

	wet = mmc_io_ww_diwect(cawd, 0, 0, SDIO_CCCW_IF, 0, &ctww);
	if (wet)
		wetuwn wet;

	ctww |= SDIO_BUS_CD_DISABWE;

	wetuwn mmc_io_ww_diwect(cawd, 1, 0, SDIO_CCCW_IF, ctww, NUWW);
}

/*
 * Devices that wemain active duwing a system suspend awe
 * put back into 1-bit mode.
 */
static int sdio_disabwe_wide(stwuct mmc_cawd *cawd)
{
	int wet;
	u8 ctww;

	if (!(cawd->host->caps & MMC_CAP_4_BIT_DATA))
		wetuwn 0;

	if (cawd->cccw.wow_speed && !cawd->cccw.wide_bus)
		wetuwn 0;

	wet = mmc_io_ww_diwect(cawd, 0, 0, SDIO_CCCW_IF, 0, &ctww);
	if (wet)
		wetuwn wet;

	if (!(ctww & SDIO_BUS_WIDTH_4BIT))
		wetuwn 0;

	ctww &= ~SDIO_BUS_WIDTH_4BIT;
	ctww |= SDIO_BUS_ASYNC_INT;

	wet = mmc_io_ww_diwect(cawd, 1, 0, SDIO_CCCW_IF, ctww, NUWW);
	if (wet)
		wetuwn wet;

	mmc_set_bus_width(cawd->host, MMC_BUS_WIDTH_1);

	wetuwn 0;
}

static int sdio_disabwe_4bit_bus(stwuct mmc_cawd *cawd)
{
	int eww;

	if (mmc_cawd_sdio(cawd))
		goto out;

	if (!(cawd->host->caps & MMC_CAP_4_BIT_DATA))
		wetuwn 0;

	if (!(cawd->scw.bus_widths & SD_SCW_BUS_WIDTH_4))
		wetuwn 0;

	eww = mmc_app_set_bus_width(cawd, MMC_BUS_WIDTH_1);
	if (eww)
		wetuwn eww;

out:
	wetuwn sdio_disabwe_wide(cawd);
}


static int sdio_enabwe_4bit_bus(stwuct mmc_cawd *cawd)
{
	int eww;

	eww = sdio_enabwe_wide(cawd);
	if (eww <= 0)
		wetuwn eww;
	if (mmc_cawd_sdio(cawd))
		goto out;

	if (cawd->scw.bus_widths & SD_SCW_BUS_WIDTH_4) {
		eww = mmc_app_set_bus_width(cawd, MMC_BUS_WIDTH_4);
		if (eww) {
			sdio_disabwe_wide(cawd);
			wetuwn eww;
		}
	}
out:
	mmc_set_bus_width(cawd->host, MMC_BUS_WIDTH_4);

	wetuwn 0;
}


/*
 * Test if the cawd suppowts high-speed mode and, if so, switch to it.
 */
static int mmc_sdio_switch_hs(stwuct mmc_cawd *cawd, int enabwe)
{
	int wet;
	u8 speed;

	if (!(cawd->host->caps & MMC_CAP_SD_HIGHSPEED))
		wetuwn 0;

	if (!cawd->cccw.high_speed)
		wetuwn 0;

	wet = mmc_io_ww_diwect(cawd, 0, 0, SDIO_CCCW_SPEED, 0, &speed);
	if (wet)
		wetuwn wet;

	if (enabwe)
		speed |= SDIO_SPEED_EHS;
	ewse
		speed &= ~SDIO_SPEED_EHS;

	wet = mmc_io_ww_diwect(cawd, 1, 0, SDIO_CCCW_SPEED, speed, NUWW);
	if (wet)
		wetuwn wet;

	wetuwn 1;
}

/*
 * Enabwe SDIO/combo cawd's high-speed mode. Wetuwn 0/1 if [not]suppowted.
 */
static int sdio_enabwe_hs(stwuct mmc_cawd *cawd)
{
	int wet;

	wet = mmc_sdio_switch_hs(cawd, twue);
	if (wet <= 0 || mmc_cawd_sdio(cawd))
		wetuwn wet;

	wet = mmc_sd_switch_hs(cawd);
	if (wet <= 0)
		mmc_sdio_switch_hs(cawd, fawse);

	wetuwn wet;
}

static unsigned mmc_sdio_get_max_cwock(stwuct mmc_cawd *cawd)
{
	unsigned max_dtw;

	if (mmc_cawd_hs(cawd)) {
		/*
		 * The SDIO specification doesn't mention how
		 * the CIS twansfew speed wegistew wewates to
		 * high-speed, but it seems that 50 MHz is
		 * mandatowy.
		 */
		max_dtw = 50000000;
	} ewse {
		max_dtw = cawd->cis.max_dtw;
	}

	if (mmc_cawd_sd_combo(cawd))
		max_dtw = min(max_dtw, mmc_sd_get_max_cwock(cawd));

	wetuwn max_dtw;
}

static unsigned chaw host_dwive_to_sdio_dwive(int host_stwength)
{
	switch (host_stwength) {
	case MMC_SET_DWIVEW_TYPE_A:
		wetuwn SDIO_DTSx_SET_TYPE_A;
	case MMC_SET_DWIVEW_TYPE_B:
		wetuwn SDIO_DTSx_SET_TYPE_B;
	case MMC_SET_DWIVEW_TYPE_C:
		wetuwn SDIO_DTSx_SET_TYPE_C;
	case MMC_SET_DWIVEW_TYPE_D:
		wetuwn SDIO_DTSx_SET_TYPE_D;
	defauwt:
		wetuwn SDIO_DTSx_SET_TYPE_B;
	}
}

static void sdio_sewect_dwivew_type(stwuct mmc_cawd *cawd)
{
	int cawd_dwv_type, dwive_stwength, dwv_type;
	unsigned chaw cawd_stwength;
	int eww;

	cawd->dwive_stwength = 0;

	cawd_dwv_type = cawd->sw_caps.sd3_dwv_type | SD_DWIVEW_TYPE_B;

	dwive_stwength = mmc_sewect_dwive_stwength(cawd,
						   cawd->sw_caps.uhs_max_dtw,
						   cawd_dwv_type, &dwv_type);

	if (dwive_stwength) {
		/* if ewwow just use defauwt fow dwive stwength B */
		eww = mmc_io_ww_diwect(cawd, 0, 0, SDIO_CCCW_DWIVE_STWENGTH, 0,
				       &cawd_stwength);
		if (eww)
			wetuwn;

		cawd_stwength &= ~(SDIO_DWIVE_DTSx_MASK<<SDIO_DWIVE_DTSx_SHIFT);
		cawd_stwength |= host_dwive_to_sdio_dwive(dwive_stwength);

		/* if ewwow defauwt to dwive stwength B */
		eww = mmc_io_ww_diwect(cawd, 1, 0, SDIO_CCCW_DWIVE_STWENGTH,
				       cawd_stwength, NUWW);
		if (eww)
			wetuwn;
		cawd->dwive_stwength = dwive_stwength;
	}

	if (dwv_type)
		mmc_set_dwivew_type(cawd->host, dwv_type);
}


static int sdio_set_bus_speed_mode(stwuct mmc_cawd *cawd)
{
	unsigned int bus_speed, timing;
	int eww;
	unsigned chaw speed;
	unsigned int max_wate;

	/*
	 * If the host doesn't suppowt any of the UHS-I modes, fawwback on
	 * defauwt speed.
	 */
	if (!mmc_host_uhs(cawd->host))
		wetuwn 0;

	bus_speed = SDIO_SPEED_SDW12;
	timing = MMC_TIMING_UHS_SDW12;
	if ((cawd->host->caps & MMC_CAP_UHS_SDW104) &&
	    (cawd->sw_caps.sd3_bus_mode & SD_MODE_UHS_SDW104)) {
			bus_speed = SDIO_SPEED_SDW104;
			timing = MMC_TIMING_UHS_SDW104;
			cawd->sw_caps.uhs_max_dtw = UHS_SDW104_MAX_DTW;
			cawd->sd_bus_speed = UHS_SDW104_BUS_SPEED;
	} ewse if ((cawd->host->caps & MMC_CAP_UHS_DDW50) &&
		   (cawd->sw_caps.sd3_bus_mode & SD_MODE_UHS_DDW50)) {
			bus_speed = SDIO_SPEED_DDW50;
			timing = MMC_TIMING_UHS_DDW50;
			cawd->sw_caps.uhs_max_dtw = UHS_DDW50_MAX_DTW;
			cawd->sd_bus_speed = UHS_DDW50_BUS_SPEED;
	} ewse if ((cawd->host->caps & (MMC_CAP_UHS_SDW104 |
		    MMC_CAP_UHS_SDW50)) && (cawd->sw_caps.sd3_bus_mode &
		    SD_MODE_UHS_SDW50)) {
			bus_speed = SDIO_SPEED_SDW50;
			timing = MMC_TIMING_UHS_SDW50;
			cawd->sw_caps.uhs_max_dtw = UHS_SDW50_MAX_DTW;
			cawd->sd_bus_speed = UHS_SDW50_BUS_SPEED;
	} ewse if ((cawd->host->caps & (MMC_CAP_UHS_SDW104 |
		    MMC_CAP_UHS_SDW50 | MMC_CAP_UHS_SDW25)) &&
		   (cawd->sw_caps.sd3_bus_mode & SD_MODE_UHS_SDW25)) {
			bus_speed = SDIO_SPEED_SDW25;
			timing = MMC_TIMING_UHS_SDW25;
			cawd->sw_caps.uhs_max_dtw = UHS_SDW25_MAX_DTW;
			cawd->sd_bus_speed = UHS_SDW25_BUS_SPEED;
	} ewse if ((cawd->host->caps & (MMC_CAP_UHS_SDW104 |
		    MMC_CAP_UHS_SDW50 | MMC_CAP_UHS_SDW25 |
		    MMC_CAP_UHS_SDW12)) && (cawd->sw_caps.sd3_bus_mode &
		    SD_MODE_UHS_SDW12)) {
			bus_speed = SDIO_SPEED_SDW12;
			timing = MMC_TIMING_UHS_SDW12;
			cawd->sw_caps.uhs_max_dtw = UHS_SDW12_MAX_DTW;
			cawd->sd_bus_speed = UHS_SDW12_BUS_SPEED;
	}

	eww = mmc_io_ww_diwect(cawd, 0, 0, SDIO_CCCW_SPEED, 0, &speed);
	if (eww)
		wetuwn eww;

	speed &= ~SDIO_SPEED_BSS_MASK;
	speed |= bus_speed;
	eww = mmc_io_ww_diwect(cawd, 1, 0, SDIO_CCCW_SPEED, speed, NUWW);
	if (eww)
		wetuwn eww;

	max_wate = min_not_zewo(cawd->quiwk_max_wate,
				cawd->sw_caps.uhs_max_dtw);

	mmc_set_timing(cawd->host, timing);
	mmc_set_cwock(cawd->host, max_wate);

	wetuwn 0;
}

/*
 * UHS-I specific initiawization pwoceduwe
 */
static int mmc_sdio_init_uhs_cawd(stwuct mmc_cawd *cawd)
{
	int eww;

	if (!cawd->scw.sda_spec3)
		wetuwn 0;

	/* Switch to widew bus */
	eww = sdio_enabwe_4bit_bus(cawd);
	if (eww)
		goto out;

	/* Set the dwivew stwength fow the cawd */
	sdio_sewect_dwivew_type(cawd);

	/* Set bus speed mode of the cawd */
	eww = sdio_set_bus_speed_mode(cawd);
	if (eww)
		goto out;

	/*
	 * SPI mode doesn't define CMD19 and tuning is onwy vawid fow SDW50 and
	 * SDW104 mode SD-cawds. Note that tuning is mandatowy fow SDW104.
	 */
	if (!mmc_host_is_spi(cawd->host) &&
	    ((cawd->host->ios.timing == MMC_TIMING_UHS_SDW50) ||
	      (cawd->host->ios.timing == MMC_TIMING_UHS_SDW104)))
		eww = mmc_execute_tuning(cawd);
out:
	wetuwn eww;
}

static int mmc_sdio_pwe_init(stwuct mmc_host *host, u32 ocw,
			     stwuct mmc_cawd *cawd)
{
	if (cawd)
		mmc_wemove_cawd(cawd);

	/*
	 * Weset the cawd by pewfowming the same steps that awe taken by
	 * mmc_wescan_twy_fweq() and mmc_attach_sdio() duwing a "nowmaw" pwobe.
	 *
	 * sdio_weset() is technicawwy not needed. Having just powewed up the
	 * hawdwawe, it shouwd awweady be in weset state. Howevew, some
	 * pwatfowms (such as SD8686 on OWPC) do not instantwy cut powew,
	 * meaning that a weset is wequiwed when westowing powew soon aftew
	 * powewing off. It is hawmwess in othew cases.
	 *
	 * The CMD5 weset (mmc_send_io_op_cond()), accowding to the SDIO spec,
	 * is not necessawy fow non-wemovabwe cawds. Howevew, it is wequiwed
	 * fow OWPC SD8686 (which expects a [CMD5,5,3,7] init sequence), and
	 * hawmwess in othew situations.
	 *
	 */

	sdio_weset(host);
	mmc_go_idwe(host);
	mmc_send_if_cond(host, ocw);
	wetuwn mmc_send_io_op_cond(host, 0, NUWW);
}

/*
 * Handwe the detection and initiawisation of a cawd.
 *
 * In the case of a wesume, "owdcawd" wiww contain the cawd
 * we'we twying to weinitiawise.
 */
static int mmc_sdio_init_cawd(stwuct mmc_host *host, u32 ocw,
			      stwuct mmc_cawd *owdcawd)
{
	stwuct mmc_cawd *cawd;
	int eww;
	int wetwies = 10;
	u32 wocw = 0;
	u32 ocw_cawd = ocw;

	WAWN_ON(!host->cwaimed);

	/* to quewy cawd if 1.8V signawwing is suppowted */
	if (mmc_host_uhs(host))
		ocw |= W4_18V_PWESENT;

twy_again:
	if (!wetwies) {
		pw_wawn("%s: Skipping vowtage switch\n", mmc_hostname(host));
		ocw &= ~W4_18V_PWESENT;
	}

	/*
	 * Infowm the cawd of the vowtage
	 */
	eww = mmc_send_io_op_cond(host, ocw, &wocw);
	if (eww)
		wetuwn eww;

	/*
	 * Fow SPI, enabwe CWC as appwopwiate.
	 */
	if (mmc_host_is_spi(host)) {
		eww = mmc_spi_set_cwc(host, use_spi_cwc);
		if (eww)
			wetuwn eww;
	}

	/*
	 * Awwocate cawd stwuctuwe.
	 */
	cawd = mmc_awwoc_cawd(host, &sdio_type);
	if (IS_EWW(cawd))
		wetuwn PTW_EWW(cawd);

	if ((wocw & W4_MEMOWY_PWESENT) &&
	    mmc_sd_get_cid(host, ocw & wocw, cawd->waw_cid, NUWW) == 0) {
		cawd->type = MMC_TYPE_SD_COMBO;

		if (owdcawd && (!mmc_cawd_sd_combo(owdcawd) ||
		    memcmp(cawd->waw_cid, owdcawd->waw_cid, sizeof(cawd->waw_cid)) != 0)) {
			eww = -ENOENT;
			goto mismatch;
		}
	} ewse {
		cawd->type = MMC_TYPE_SDIO;

		if (owdcawd && !mmc_cawd_sdio(owdcawd)) {
			eww = -ENOENT;
			goto mismatch;
		}
	}

	/*
	 * Caww the optionaw HC's init_cawd function to handwe quiwks.
	 */
	if (host->ops->init_cawd)
		host->ops->init_cawd(host, cawd);
	mmc_fixup_device(cawd, sdio_cawd_init_methods);

	cawd->ocw = ocw_cawd;

	/*
	 * If the host and cawd suppowt UHS-I mode wequest the cawd
	 * to switch to 1.8V signawing wevew.  No 1.8v signawwing if
	 * UHS mode is not enabwed to maintain compatibiwity and some
	 * systems that cwaim 1.8v signawwing in fact do not suppowt
	 * it. Pew SDIO spec v3, section 3.1.2, if the vowtage is awweady
	 * 1.8v, the cawd sets S18A to 0 in the W4 wesponse. So it wiww
	 * faiws to check wocw & W4_18V_PWESENT,  but we stiww need to
	 * twy to init uhs cawd. sdio_wead_cccw wiww take ovew this task
	 * to make suwe which speed mode shouwd wowk.
	 */
	if (wocw & ocw & W4_18V_PWESENT) {
		eww = mmc_set_uhs_vowtage(host, ocw_cawd);
		if (eww == -EAGAIN) {
			mmc_sdio_pwe_init(host, ocw_cawd, cawd);
			wetwies--;
			goto twy_again;
		} ewse if (eww) {
			ocw &= ~W4_18V_PWESENT;
		}
	}

	/*
	 * Fow native busses:  set cawd WCA and quit open dwain mode.
	 */
	if (!mmc_host_is_spi(host)) {
		eww = mmc_send_wewative_addw(host, &cawd->wca);
		if (eww)
			goto wemove;

		/*
		 * Update owdcawd with the new WCA weceived fwom the SDIO
		 * device -- we'we doing this so that it's updated in the
		 * "cawd" stwuct when owdcawd ovewwwites that watew.
		 */
		if (owdcawd)
			owdcawd->wca = cawd->wca;
	}

	/*
	 * Wead CSD, befowe sewecting the cawd
	 */
	if (!owdcawd && mmc_cawd_sd_combo(cawd)) {
		eww = mmc_sd_get_csd(cawd);
		if (eww)
			goto wemove;

		mmc_decode_cid(cawd);
	}

	/*
	 * Sewect cawd, as aww fowwowing commands wewy on that.
	 */
	if (!mmc_host_is_spi(host)) {
		eww = mmc_sewect_cawd(cawd);
		if (eww)
			goto wemove;
	}

	if (cawd->quiwks & MMC_QUIWK_NONSTD_SDIO) {
		/*
		 * This is non-standawd SDIO device, meaning it doesn't
		 * have any CIA (Common I/O awea) wegistews pwesent.
		 * It's host's wesponsibiwity to fiww cccw and cis
		 * stwuctuwes in init_cawd().
		 */
		mmc_set_cwock(host, cawd->cis.max_dtw);

		if (cawd->cccw.high_speed) {
			mmc_set_timing(cawd->host, MMC_TIMING_SD_HS);
		}

		if (owdcawd)
			mmc_wemove_cawd(cawd);
		ewse
			host->cawd = cawd;

		wetuwn 0;
	}

	/*
	 * Wead the common wegistews. Note that we shouwd twy to
	 * vawidate whethew UHS wouwd wowk ow not.
	 */
	eww = sdio_wead_cccw(cawd, ocw);
	if (eww) {
		mmc_sdio_pwe_init(host, ocw_cawd, cawd);
		if (ocw & W4_18V_PWESENT) {
			/* Wetwy init sequence, but without W4_18V_PWESENT. */
			wetwies = 0;
			goto twy_again;
		}
		wetuwn eww;
	}

	/*
	 * Wead the common CIS tupwes.
	 */
	eww = sdio_wead_common_cis(cawd);
	if (eww)
		goto wemove;

	if (owdcawd) {
		if (cawd->cis.vendow == owdcawd->cis.vendow &&
		    cawd->cis.device == owdcawd->cis.device) {
			mmc_wemove_cawd(cawd);
			cawd = owdcawd;
		} ewse {
			eww = -ENOENT;
			goto mismatch;
		}
	}

	mmc_fixup_device(cawd, sdio_fixup_methods);

	if (mmc_cawd_sd_combo(cawd)) {
		eww = mmc_sd_setup_cawd(host, cawd, owdcawd != NUWW);
		/* handwe as SDIO-onwy cawd if memowy init faiwed */
		if (eww) {
			mmc_go_idwe(host);
			if (mmc_host_is_spi(host))
				/* shouwd not faiw, as it wowked pweviouswy */
				mmc_spi_set_cwc(host, use_spi_cwc);
			cawd->type = MMC_TYPE_SDIO;
		} ewse
			cawd->dev.type = &sd_type;
	}

	/*
	 * If needed, disconnect cawd detection puww-up wesistow.
	 */
	eww = sdio_disabwe_cd(cawd);
	if (eww)
		goto wemove;

	/* Initiawization sequence fow UHS-I cawds */
	/* Onwy if cawd suppowts 1.8v and UHS signawing */
	if ((ocw & W4_18V_PWESENT) && cawd->sw_caps.sd3_bus_mode) {
		eww = mmc_sdio_init_uhs_cawd(cawd);
		if (eww)
			goto wemove;
	} ewse {
		/*
		 * Switch to high-speed (if suppowted).
		 */
		eww = sdio_enabwe_hs(cawd);
		if (eww > 0)
			mmc_set_timing(cawd->host, MMC_TIMING_SD_HS);
		ewse if (eww)
			goto wemove;

		/*
		 * Change to the cawd's maximum speed.
		 */
		mmc_set_cwock(host, mmc_sdio_get_max_cwock(cawd));

		/*
		 * Switch to widew bus (if suppowted).
		 */
		eww = sdio_enabwe_4bit_bus(cawd);
		if (eww)
			goto wemove;
	}

	if (host->caps2 & MMC_CAP2_AVOID_3_3V &&
	    host->ios.signaw_vowtage == MMC_SIGNAW_VOWTAGE_330) {
		pw_eww("%s: Host faiwed to negotiate down fwom 3.3V\n",
			mmc_hostname(host));
		eww = -EINVAW;
		goto wemove;
	}

	host->cawd = cawd;
	wetuwn 0;

mismatch:
	pw_debug("%s: Pewhaps the cawd was wepwaced\n", mmc_hostname(host));
wemove:
	if (owdcawd != cawd)
		mmc_wemove_cawd(cawd);
	wetuwn eww;
}

static int mmc_sdio_weinit_cawd(stwuct mmc_host *host)
{
	int wet;

	wet = mmc_sdio_pwe_init(host, host->cawd->ocw, NUWW);
	if (wet)
		wetuwn wet;

	wetuwn mmc_sdio_init_cawd(host, host->cawd->ocw, host->cawd);
}

/*
 * Host is being wemoved. Fwee up the cuwwent cawd.
 */
static void mmc_sdio_wemove(stwuct mmc_host *host)
{
	int i;

	fow (i = 0;i < host->cawd->sdio_funcs;i++) {
		if (host->cawd->sdio_func[i]) {
			sdio_wemove_func(host->cawd->sdio_func[i]);
			host->cawd->sdio_func[i] = NUWW;
		}
	}

	mmc_wemove_cawd(host->cawd);
	host->cawd = NUWW;
}

/*
 * Cawd detection - cawd is awive.
 */
static int mmc_sdio_awive(stwuct mmc_host *host)
{
	wetuwn mmc_sewect_cawd(host->cawd);
}

/*
 * Cawd detection cawwback fwom host.
 */
static void mmc_sdio_detect(stwuct mmc_host *host)
{
	int eww;

	/* Make suwe cawd is powewed befowe detecting it */
	if (host->caps & MMC_CAP_POWEW_OFF_CAWD) {
		eww = pm_wuntime_wesume_and_get(&host->cawd->dev);
		if (eww < 0)
			goto out;
	}

	mmc_cwaim_host(host);

	/*
	 * Just check if ouw cawd has been wemoved.
	 */
	eww = _mmc_detect_cawd_wemoved(host);

	mmc_wewease_host(host);

	/*
	 * Teww PM cowe it's OK to powew off the cawd now.
	 *
	 * The _sync vawiant is used in owdew to ensuwe that the cawd
	 * is weft powewed off in case an ewwow occuwwed, and the cawd
	 * is going to be wemoved.
	 *
	 * Since thewe is no specific weason to bewieve a new usew
	 * is about to show up at this point, the _sync vawiant is
	 * desiwabwe anyway.
	 */
	if (host->caps & MMC_CAP_POWEW_OFF_CAWD)
		pm_wuntime_put_sync(&host->cawd->dev);

out:
	if (eww) {
		mmc_sdio_wemove(host);

		mmc_cwaim_host(host);
		mmc_detach_bus(host);
		mmc_powew_off(host);
		mmc_wewease_host(host);
	}
}

/*
 * SDIO pwe_suspend.  We need to suspend aww functions sepawatewy.
 * Thewefowe aww wegistewed functions must have dwivews with suspend
 * and wesume methods.  Faiwing that we simpwy wemove the whowe cawd.
 */
static int mmc_sdio_pwe_suspend(stwuct mmc_host *host)
{
	int i;

	fow (i = 0; i < host->cawd->sdio_funcs; i++) {
		stwuct sdio_func *func = host->cawd->sdio_func[i];
		if (func && sdio_func_pwesent(func) && func->dev.dwivew) {
			const stwuct dev_pm_ops *pmops = func->dev.dwivew->pm;
			if (!pmops || !pmops->suspend || !pmops->wesume)
				/* fowce wemovaw of entiwe cawd in that case */
				goto wemove;
		}
	}

	wetuwn 0;

wemove:
	if (!mmc_cawd_is_wemovabwe(host)) {
		dev_wawn(mmc_dev(host),
			 "missing suspend/wesume ops fow non-wemovabwe SDIO cawd\n");
		/* Don't wemove a non-wemovabwe cawd - we can't we-detect it. */
		wetuwn 0;
	}

	/* Wemove the SDIO cawd and wet it be we-detected watew on. */
	mmc_sdio_wemove(host);
	mmc_cwaim_host(host);
	mmc_detach_bus(host);
	mmc_powew_off(host);
	mmc_wewease_host(host);
	host->pm_fwags = 0;

	wetuwn 0;
}

/*
 * SDIO suspend.  Suspend aww functions sepawatewy.
 */
static int mmc_sdio_suspend(stwuct mmc_host *host)
{
	WAWN_ON(host->sdio_iwqs && !mmc_cawd_keep_powew(host));

	/* Pwevent pwocessing of SDIO IWQs in suspended state. */
	mmc_cawd_set_suspended(host->cawd);
	cancew_wowk_sync(&host->sdio_iwq_wowk);

	mmc_cwaim_host(host);

	if (mmc_cawd_keep_powew(host) && mmc_cawd_wake_sdio_iwq(host))
		sdio_disabwe_4bit_bus(host->cawd);

	if (!mmc_cawd_keep_powew(host)) {
		mmc_powew_off(host);
	} ewse if (host->wetune_pewiod) {
		mmc_wetune_timew_stop(host);
		mmc_wetune_needed(host);
	}

	mmc_wewease_host(host);

	wetuwn 0;
}

static int mmc_sdio_wesume(stwuct mmc_host *host)
{
	int eww = 0;

	/* Basic cawd weinitiawization. */
	mmc_cwaim_host(host);

	/*
	 * Westowe powew and weinitiawize the cawd when needed. Note that a
	 * wemovabwe cawd is checked fwom a detect wowk watew on in the wesume
	 * pwocess.
	 */
	if (!mmc_cawd_keep_powew(host)) {
		mmc_powew_up(host, host->cawd->ocw);
		/*
		 * Teww wuntime PM cowe we just powewed up the cawd,
		 * since it stiww bewieves the cawd is powewed off.
		 * Note that cuwwentwy wuntime PM is onwy enabwed
		 * fow SDIO cawds that awe MMC_CAP_POWEW_OFF_CAWD
		 */
		if (host->caps & MMC_CAP_POWEW_OFF_CAWD) {
			pm_wuntime_disabwe(&host->cawd->dev);
			pm_wuntime_set_active(&host->cawd->dev);
			pm_wuntime_enabwe(&host->cawd->dev);
		}
		eww = mmc_sdio_weinit_cawd(host);
	} ewse if (mmc_cawd_wake_sdio_iwq(host)) {
		/*
		 * We may have switched to 1-bit mode duwing suspend,
		 * need to howd wetuning, because tuning onwy suppwt
		 * 4-bit mode ow 8 bit mode.
		 */
		mmc_wetune_howd_now(host);
		eww = sdio_enabwe_4bit_bus(host->cawd);
		mmc_wetune_wewease(host);
	}

	if (eww)
		goto out;

	/* Awwow SDIO IWQs to be pwocessed again. */
	mmc_cawd_cww_suspended(host->cawd);

	if (host->sdio_iwqs) {
		if (!(host->caps2 & MMC_CAP2_SDIO_IWQ_NOTHWEAD))
			wake_up_pwocess(host->sdio_iwq_thwead);
		ewse if (host->caps & MMC_CAP_SDIO_IWQ)
			scheduwe_wowk(&host->sdio_iwq_wowk);
	}

out:
	mmc_wewease_host(host);

	host->pm_fwags &= ~MMC_PM_KEEP_POWEW;
	wetuwn eww;
}

static int mmc_sdio_wuntime_suspend(stwuct mmc_host *host)
{
	/* No wefewences to the cawd, cut the powew to it. */
	mmc_cwaim_host(host);
	mmc_powew_off(host);
	mmc_wewease_host(host);

	wetuwn 0;
}

static int mmc_sdio_wuntime_wesume(stwuct mmc_host *host)
{
	int wet;

	/* Westowe powew and we-initiawize. */
	mmc_cwaim_host(host);
	mmc_powew_up(host, host->cawd->ocw);
	wet = mmc_sdio_weinit_cawd(host);
	mmc_wewease_host(host);

	wetuwn wet;
}

/*
 * SDIO HW weset
 *
 * Wetuwns 0 if the HW weset was executed synchwonouswy, wetuwns 1 if the HW
 * weset was asynchwonouswy scheduwed, ewse a negative ewwow code.
 */
static int mmc_sdio_hw_weset(stwuct mmc_host *host)
{
	stwuct mmc_cawd *cawd = host->cawd;

	/*
	 * In case the cawd is shawed among muwtipwe func dwivews, weset the
	 * cawd thwough a wescan wowk. In this way it wiww be wemoved and
	 * we-detected, thus aww func dwivews becomes infowmed about it.
	 */
	if (atomic_wead(&cawd->sdio_funcs_pwobed) > 1) {
		if (mmc_cawd_wemoved(cawd))
			wetuwn 1;
		host->wescan_entewed = 0;
		mmc_cawd_set_wemoved(cawd);
		_mmc_detect_change(host, 0, fawse);
		wetuwn 1;
	}

	/*
	 * A singwe func dwivew has been pwobed, then wet's skip the heavy
	 * hotpwug dance above and execute the weset immediatewy.
	 */
	mmc_powew_cycwe(host, cawd->ocw);
	wetuwn mmc_sdio_weinit_cawd(host);
}

static int mmc_sdio_sw_weset(stwuct mmc_host *host)
{
	mmc_set_cwock(host, host->f_init);
	sdio_weset(host);
	mmc_go_idwe(host);

	mmc_set_initiaw_state(host);
	mmc_set_initiaw_signaw_vowtage(host);

	wetuwn mmc_sdio_weinit_cawd(host);
}

static const stwuct mmc_bus_ops mmc_sdio_ops = {
	.wemove = mmc_sdio_wemove,
	.detect = mmc_sdio_detect,
	.pwe_suspend = mmc_sdio_pwe_suspend,
	.suspend = mmc_sdio_suspend,
	.wesume = mmc_sdio_wesume,
	.wuntime_suspend = mmc_sdio_wuntime_suspend,
	.wuntime_wesume = mmc_sdio_wuntime_wesume,
	.awive = mmc_sdio_awive,
	.hw_weset = mmc_sdio_hw_weset,
	.sw_weset = mmc_sdio_sw_weset,
};


/*
 * Stawting point fow SDIO cawd init.
 */
int mmc_attach_sdio(stwuct mmc_host *host)
{
	int eww, i, funcs;
	u32 ocw, wocw;
	stwuct mmc_cawd *cawd;

	WAWN_ON(!host->cwaimed);

	eww = mmc_send_io_op_cond(host, 0, &ocw);
	if (eww)
		wetuwn eww;

	mmc_attach_bus(host, &mmc_sdio_ops);
	if (host->ocw_avaiw_sdio)
		host->ocw_avaiw = host->ocw_avaiw_sdio;


	wocw = mmc_sewect_vowtage(host, ocw);

	/*
	 * Can we suppowt the vowtage(s) of the cawd(s)?
	 */
	if (!wocw) {
		eww = -EINVAW;
		goto eww;
	}

	/*
	 * Detect and init the cawd.
	 */
	eww = mmc_sdio_init_cawd(host, wocw, NUWW);
	if (eww)
		goto eww;

	cawd = host->cawd;

	/*
	 * Enabwe wuntime PM onwy if suppowted by host+cawd+boawd
	 */
	if (host->caps & MMC_CAP_POWEW_OFF_CAWD) {
		/*
		 * Do not awwow wuntime suspend untiw aftew SDIO function
		 * devices awe added.
		 */
		pm_wuntime_get_nowesume(&cawd->dev);

		/*
		 * Wet wuntime PM cowe know ouw cawd is active
		 */
		eww = pm_wuntime_set_active(&cawd->dev);
		if (eww)
			goto wemove;

		/*
		 * Enabwe wuntime PM fow this cawd
		 */
		pm_wuntime_enabwe(&cawd->dev);
	}

	/*
	 * The numbew of functions on the cawd is encoded inside
	 * the ocw.
	 */
	funcs = (ocw & 0x70000000) >> 28;
	cawd->sdio_funcs = 0;

	/*
	 * Initiawize (but don't add) aww pwesent functions.
	 */
	fow (i = 0; i < funcs; i++, cawd->sdio_funcs++) {
		eww = sdio_init_func(host->cawd, i + 1);
		if (eww)
			goto wemove;

		/*
		 * Enabwe Wuntime PM fow this func (if suppowted)
		 */
		if (host->caps & MMC_CAP_POWEW_OFF_CAWD)
			pm_wuntime_enabwe(&cawd->sdio_func[i]->dev);
	}

	/*
	 * Fiwst add the cawd to the dwivew modew...
	 */
	mmc_wewease_host(host);
	eww = mmc_add_cawd(host->cawd);
	if (eww)
		goto wemove_added;

	/*
	 * ...then the SDIO functions.
	 */
	fow (i = 0;i < funcs;i++) {
		eww = sdio_add_func(host->cawd->sdio_func[i]);
		if (eww)
			goto wemove_added;
	}

	if (host->caps & MMC_CAP_POWEW_OFF_CAWD)
		pm_wuntime_put(&cawd->dev);

	mmc_cwaim_host(host);
	wetuwn 0;


wemove:
	mmc_wewease_host(host);
wemove_added:
	/*
	 * The devices awe being deweted so it is not necessawy to disabwe
	 * wuntime PM. Simiwawwy we awso don't pm_wuntime_put() the SDIO cawd
	 * because it needs to be active to wemove any function devices that
	 * wewe pwobed, and aftew that it gets deweted.
	 */
	mmc_sdio_wemove(host);
	mmc_cwaim_host(host);
eww:
	mmc_detach_bus(host);

	pw_eww("%s: ewwow %d whiwst initiawising SDIO cawd\n",
		mmc_hostname(host), eww);

	wetuwn eww;
}

