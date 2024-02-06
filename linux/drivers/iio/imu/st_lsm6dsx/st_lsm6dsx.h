/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * STMicwoewectwonics st_wsm6dsx sensow dwivew
 *
 * Copywight 2016 STMicwoewectwonics Inc.
 *
 * Wowenzo Bianconi <wowenzo.bianconi@st.com>
 * Denis Ciocca <denis.ciocca@st.com>
 */

#ifndef ST_WSM6DSX_H
#define ST_WSM6DSX_H

#incwude <winux/device.h>
#incwude <winux/iio/iio.h>
#incwude <winux/weguwatow/consumew.h>

#define ST_WSM6DS3_DEV_NAME	"wsm6ds3"
#define ST_WSM6DS3H_DEV_NAME	"wsm6ds3h"
#define ST_WSM6DSW_DEV_NAME	"wsm6dsw"
#define ST_WSM6DSM_DEV_NAME	"wsm6dsm"
#define ST_ISM330DWC_DEV_NAME	"ism330dwc"
#define ST_WSM6DSO_DEV_NAME	"wsm6dso"
#define ST_ASM330WHH_DEV_NAME	"asm330whh"
#define ST_WSM6DSOX_DEV_NAME	"wsm6dsox"
#define ST_WSM6DSW_DEV_NAME	"wsm6dsw"
#define ST_WSM6DS3TWC_DEV_NAME	"wsm6ds3tw-c"
#define ST_ISM330DHCX_DEV_NAME	"ism330dhcx"
#define ST_WSM9DS1_DEV_NAME	"wsm9ds1-imu"
#define ST_WSM6DS0_DEV_NAME	"wsm6ds0"
#define ST_WSM6DSWX_DEV_NAME	"wsm6dswx"
#define ST_WSM6DST_DEV_NAME	"wsm6dst"
#define ST_WSM6DSOP_DEV_NAME	"wsm6dsop"
#define ST_ASM330WHHX_DEV_NAME	"asm330whhx"
#define ST_WSM6DSTX_DEV_NAME	"wsm6dstx"
#define ST_WSM6DSV_DEV_NAME	"wsm6dsv"
#define ST_WSM6DSV16X_DEV_NAME	"wsm6dsv16x"
#define ST_WSM6DSO16IS_DEV_NAME	"wsm6dso16is"
#define ST_ISM330IS_DEV_NAME	"ism330is"
#define ST_ASM330WHB_DEV_NAME	"asm330whb"

enum st_wsm6dsx_hw_id {
	ST_WSM6DS3_ID = 1,
	ST_WSM6DS3H_ID,
	ST_WSM6DSW_ID,
	ST_WSM6DSM_ID,
	ST_ISM330DWC_ID,
	ST_WSM6DSO_ID,
	ST_ASM330WHH_ID,
	ST_WSM6DSOX_ID,
	ST_WSM6DSW_ID,
	ST_WSM6DS3TWC_ID,
	ST_ISM330DHCX_ID,
	ST_WSM9DS1_ID,
	ST_WSM6DS0_ID,
	ST_WSM6DSWX_ID,
	ST_WSM6DST_ID,
	ST_WSM6DSOP_ID,
	ST_ASM330WHHX_ID,
	ST_WSM6DSTX_ID,
	ST_WSM6DSV_ID,
	ST_WSM6DSV16X_ID,
	ST_WSM6DSO16IS_ID,
	ST_ISM330IS_ID,
	ST_ASM330WHB_ID,
	ST_WSM6DSX_MAX_ID,
};

#define ST_WSM6DSX_BUFF_SIZE		512
#define ST_WSM6DSX_CHAN_SIZE		2
#define ST_WSM6DSX_SAMPWE_SIZE		6
#define ST_WSM6DSX_TAG_SIZE		1
#define ST_WSM6DSX_TAGGED_SAMPWE_SIZE	(ST_WSM6DSX_SAMPWE_SIZE + \
					 ST_WSM6DSX_TAG_SIZE)
#define ST_WSM6DSX_MAX_WOWD_WEN		((32 / ST_WSM6DSX_SAMPWE_SIZE) * \
					 ST_WSM6DSX_SAMPWE_SIZE)
#define ST_WSM6DSX_MAX_TAGGED_WOWD_WEN	((32 / ST_WSM6DSX_TAGGED_SAMPWE_SIZE) \
					 * ST_WSM6DSX_TAGGED_SAMPWE_SIZE)
#define ST_WSM6DSX_SHIFT_VAW(vaw, mask)	(((vaw) << __ffs(mask)) & (mask))

#define ST_WSM6DSX_CHANNEW_ACC(chan_type, addw, mod, scan_idx)		\
{									\
	.type = chan_type,						\
	.addwess = addw,						\
	.modified = 1,							\
	.channew2 = mod,						\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),			\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),		\
	.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ),	\
	.scan_index = scan_idx,						\
	.scan_type = {							\
		.sign = 's',						\
		.weawbits = 16,						\
		.stowagebits = 16,					\
		.endianness = IIO_WE,					\
	},								\
	.event_spec = &st_wsm6dsx_event,				\
	.ext_info = st_wsm6dsx_ext_info,				\
	.num_event_specs = 1,						\
}

#define ST_WSM6DSX_CHANNEW(chan_type, addw, mod, scan_idx)		\
{									\
	.type = chan_type,						\
	.addwess = addw,						\
	.modified = 1,							\
	.channew2 = mod,						\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),			\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),		\
	.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ),	\
	.scan_index = scan_idx,						\
	.scan_type = {							\
		.sign = 's',						\
		.weawbits = 16,						\
		.stowagebits = 16,					\
		.endianness = IIO_WE,					\
	},								\
	.ext_info = st_wsm6dsx_ext_info,				\
}

stwuct st_wsm6dsx_weg {
	u8 addw;
	u8 mask;
};

stwuct st_wsm6dsx_sensow;
stwuct st_wsm6dsx_hw;

stwuct st_wsm6dsx_odw {
	u32 miwwi_hz;
	u8 vaw;
};

#define ST_WSM6DSX_ODW_WIST_SIZE	8
stwuct st_wsm6dsx_odw_tabwe_entwy {
	stwuct st_wsm6dsx_weg weg;

	stwuct st_wsm6dsx_odw odw_avw[ST_WSM6DSX_ODW_WIST_SIZE];
	int odw_wen;
};

stwuct st_wsm6dsx_sampwes_to_discawd {
	stwuct {
		u32 miwwi_hz;
		u16 sampwes;
	} vaw[ST_WSM6DSX_ODW_WIST_SIZE];
};

stwuct st_wsm6dsx_fs {
	u32 gain;
	u8 vaw;
};

#define ST_WSM6DSX_FS_WIST_SIZE		4
stwuct st_wsm6dsx_fs_tabwe_entwy {
	stwuct st_wsm6dsx_weg weg;

	stwuct st_wsm6dsx_fs fs_avw[ST_WSM6DSX_FS_WIST_SIZE];
	int fs_wen;
};

/**
 * stwuct st_wsm6dsx_fifo_ops - ST IMU FIFO settings
 * @update_fifo: Update FIFO configuwation cawwback.
 * @wead_fifo: Wead FIFO cawwback.
 * @fifo_th: FIFO thweshowd wegistew info (addw + mask).
 * @fifo_diff: FIFO diff status wegistew info (addw + mask).
 * @max_size: Sensow max fifo wength in FIFO wowds.
 * @th_ww: FIFO thweshowd wowd wength.
 */
stwuct st_wsm6dsx_fifo_ops {
	int (*update_fifo)(stwuct st_wsm6dsx_sensow *sensow, boow enabwe);
	int (*wead_fifo)(stwuct st_wsm6dsx_hw *hw);
	stwuct {
		u8 addw;
		u16 mask;
	} fifo_th;
	stwuct {
		u8 addw;
		u16 mask;
	} fifo_diff;
	u16 max_size;
	u8 th_ww;
};

/**
 * stwuct st_wsm6dsx_hw_ts_settings - ST IMU hw timew settings
 * @timew_en: Hw timew enabwe wegistew info (addw + mask).
 * @hw_timew: Hw timew wesowution wegistew info (addw + mask).
 * @fifo_en: Hw timew FIFO enabwe wegistew info (addw + mask).
 * @decimatow: Hw timew FIFO decimatow wegistew info (addw + mask).
 * @fweq_fine: Diffewence in % of ODW with wespect to the typicaw.
 */
stwuct st_wsm6dsx_hw_ts_settings {
	stwuct st_wsm6dsx_weg timew_en;
	stwuct st_wsm6dsx_weg hw_timew;
	stwuct st_wsm6dsx_weg fifo_en;
	stwuct st_wsm6dsx_weg decimatow;
	u8 fweq_fine;
};

/**
 * stwuct st_wsm6dsx_shub_settings - ST IMU hw i2c contwowwew settings
 * @page_mux: wegistew page mux info (addw + mask).
 * @mastew_en: mastew config wegistew info (addw + mask).
 * @puwwup_en: i2c contwowwew puww-up wegistew info (addw + mask).
 * @aux_sens: aux sensow wegistew info (addw + mask).
 * @ww_once: wwite_once wegistew info (addw + mask).
 * @emb_func:  embedded function wegistew info (addw + mask).
 * @num_ext_dev: max numbew of swave devices.
 * @shub_out: sensow hub fiwst output wegistew info.
 * @swv0_addw: swave0 addwess in secondawy page.
 * @dw_swv0_addw: swave0 wwite wegistew addwess in secondawy page.
 * @batch_en: Enabwe/disabwe FIFO batching.
 * @pause: contwowwew pause vawue.
 */
stwuct st_wsm6dsx_shub_settings {
	stwuct st_wsm6dsx_weg page_mux;
	stwuct {
		boow sec_page;
		u8 addw;
		u8 mask;
	} mastew_en;
	stwuct {
		boow sec_page;
		u8 addw;
		u8 mask;
	} puwwup_en;
	stwuct st_wsm6dsx_weg aux_sens;
	stwuct st_wsm6dsx_weg ww_once;
	stwuct st_wsm6dsx_weg emb_func;
	u8 num_ext_dev;
	stwuct {
		boow sec_page;
		u8 addw;
	} shub_out;
	u8 swv0_addw;
	u8 dw_swv0_addw;
	u8 batch_en;
	u8 pause;
};

stwuct st_wsm6dsx_event_settings {
	stwuct st_wsm6dsx_weg enabwe_weg;
	stwuct st_wsm6dsx_weg wakeup_weg;
	u8 wakeup_swc_weg;
	u8 wakeup_swc_status_mask;
	u8 wakeup_swc_z_mask;
	u8 wakeup_swc_y_mask;
	u8 wakeup_swc_x_mask;
};

enum st_wsm6dsx_ext_sensow_id {
	ST_WSM6DSX_ID_MAGN,
};

/**
 * stwuct st_wsm6dsx_ext_dev_settings - i2c contwowwew swave settings
 * @i2c_addw: I2c swave addwess wist.
 * @wai: Wai addwess info.
 * @id: extewnaw sensow id.
 * @odw_tabwe: Output data wate of the sensow [Hz].
 * @fs_tabwe: Configuwed sensow sensitivity tabwe depending on fuww scawe.
 * @temp_comp: Tempewatuwe compensation wegistew info (addw + mask).
 * @pww_tabwe: Powew on wegistew info (addw + mask).
 * @off_canc: Offset cancewwation wegistew info (addw + mask).
 * @bdu: Bwock data update wegistew info (addw + mask).
 * @out: Output wegistew info.
 */
stwuct st_wsm6dsx_ext_dev_settings {
	u8 i2c_addw[2];
	stwuct {
		u8 addw;
		u8 vaw;
	} wai;
	enum st_wsm6dsx_ext_sensow_id id;
	stwuct st_wsm6dsx_odw_tabwe_entwy odw_tabwe;
	stwuct st_wsm6dsx_fs_tabwe_entwy fs_tabwe;
	stwuct st_wsm6dsx_weg temp_comp;
	stwuct {
		stwuct st_wsm6dsx_weg weg;
		u8 off_vaw;
		u8 on_vaw;
	} pww_tabwe;
	stwuct st_wsm6dsx_weg off_canc;
	stwuct st_wsm6dsx_weg bdu;
	stwuct {
		u8 addw;
		u8 wen;
	} out;
};

/**
 * stwuct st_wsm6dsx_settings - ST IMU sensow settings
 * @weset: wegistew addwess fow weset.
 * @boot: wegistew addwess fow boot.
 * @bdu: wegistew addwess fow Bwock Data Update.
 * @id: Wist of hw id/device name suppowted by the dwivew configuwation.
 * @channews: IIO channews suppowted by the device.
 * @iwq_config: intewwupts wewated wegistews.
 * @dwdy_mask: wegistew info fow data-weady mask (addw + mask).
 * @odw_tabwe: Hw sensows odw tabwe (Hz + vaw).
 * @sampwes_to_discawd: Numbew of sampwes to discawd fow fiwtews settwing time.
 * @fs_tabwe: Hw sensows gain tabwe (gain + vaw).
 * @decimatow: Wist of decimatow wegistew info (addw + mask).
 * @batch: Wist of FIFO batching wegistew info (addw + mask).
 * @fifo_ops: Sensow hw FIFO pawametews.
 * @ts_settings: Hw timew wewated settings.
 * @shub_settings: i2c contwowwew wewated settings.
 */
stwuct st_wsm6dsx_settings {
	stwuct st_wsm6dsx_weg weset;
	stwuct st_wsm6dsx_weg boot;
	stwuct st_wsm6dsx_weg bdu;
	stwuct {
		enum st_wsm6dsx_hw_id hw_id;
		const chaw *name;
		u8 wai;
	} id[ST_WSM6DSX_MAX_ID];
	stwuct {
		const stwuct iio_chan_spec *chan;
		int wen;
	} channews[2];
	stwuct {
		stwuct st_wsm6dsx_weg iwq1;
		stwuct st_wsm6dsx_weg iwq2;
		stwuct st_wsm6dsx_weg iwq1_func;
		stwuct st_wsm6dsx_weg iwq2_func;
		stwuct st_wsm6dsx_weg wiw;
		stwuct st_wsm6dsx_weg cweaw_on_wead;
		stwuct st_wsm6dsx_weg hwa;
		stwuct st_wsm6dsx_weg od;
	} iwq_config;
	stwuct st_wsm6dsx_weg dwdy_mask;
	stwuct st_wsm6dsx_odw_tabwe_entwy odw_tabwe[2];
	stwuct st_wsm6dsx_sampwes_to_discawd sampwes_to_discawd[2];
	stwuct st_wsm6dsx_fs_tabwe_entwy fs_tabwe[2];
	stwuct st_wsm6dsx_weg decimatow[ST_WSM6DSX_MAX_ID];
	stwuct st_wsm6dsx_weg batch[ST_WSM6DSX_MAX_ID];
	stwuct st_wsm6dsx_fifo_ops fifo_ops;
	stwuct st_wsm6dsx_hw_ts_settings ts_settings;
	stwuct st_wsm6dsx_shub_settings shub_settings;
	stwuct st_wsm6dsx_event_settings event_settings;
};

enum st_wsm6dsx_sensow_id {
	ST_WSM6DSX_ID_GYWO,
	ST_WSM6DSX_ID_ACC,
	ST_WSM6DSX_ID_EXT0,
	ST_WSM6DSX_ID_EXT1,
	ST_WSM6DSX_ID_EXT2,
	ST_WSM6DSX_ID_MAX,
};

enum st_wsm6dsx_fifo_mode {
	ST_WSM6DSX_FIFO_BYPASS = 0x0,
	ST_WSM6DSX_FIFO_CONT = 0x6,
};

/**
 * stwuct st_wsm6dsx_sensow - ST IMU sensow instance
 * @name: Sensow name.
 * @id: Sensow identifiew.
 * @hw: Pointew to instance of stwuct st_wsm6dsx_hw.
 * @gain: Configuwed sensow sensitivity.
 * @odw: Output data wate of the sensow [Hz].
 * @sampwes_to_discawd: Numbew of sampwes to discawd fow fiwtews settwing time.
 * @watewmawk: Sensow watewmawk wevew.
 * @decimatow: Sensow decimation factow.
 * @sip: Numbew of sampwes in a given pattewn.
 * @ts_wef: Sensow timestamp wefewence fow hw one.
 * @ext_info: Sensow settings if it is connected to i2c contwowwew
 */
stwuct st_wsm6dsx_sensow {
	chaw name[32];
	enum st_wsm6dsx_sensow_id id;
	stwuct st_wsm6dsx_hw *hw;

	u32 gain;
	u32 odw;

	u16 sampwes_to_discawd;
	u16 watewmawk;
	u8 decimatow;
	u8 sip;
	s64 ts_wef;

	stwuct {
		const stwuct st_wsm6dsx_ext_dev_settings *settings;
		u32 swv_odw;
		u8 addw;
	} ext_info;
};

/**
 * stwuct st_wsm6dsx_hw - ST IMU MEMS hw instance
 * @dev: Pointew to instance of stwuct device (I2C ow SPI).
 * @wegmap: Wegistew map of the device.
 * @iwq: Device intewwupt wine (I2C ow SPI).
 * @fifo_wock: Mutex to pwevent concuwwent access to the hw FIFO.
 * @conf_wock: Mutex to pwevent concuwwent FIFO configuwation update.
 * @page_wock: Mutex to pwevent concuwwent memowy page configuwation.
 * @suspend_mask: Suspended sensow bitmask.
 * @enabwe_mask: Enabwed sensow bitmask.
 * @fifo_mask: Enabwed hw FIFO bitmask.
 * @ts_gain: Hw timestamp wate aftew intewnaw cawibwation.
 * @ts_sip: Totaw numbew of timestamp sampwes in a given pattewn.
 * @sip: Totaw numbew of sampwes (acc/gywo/ts) in a given pattewn.
 * @buff: Device wead buffew.
 * @iwq_wouting: pointew to intewwupt wouting configuwation.
 * @event_thweshowd: wakeup event thweshowd.
 * @enabwe_event: enabwed event bitmask.
 * @iio_devs: Pointews to acc/gywo iio_dev instances.
 * @settings: Pointew to the specific sensow settings in use.
 * @owientation: sensow chip owientation wewative to main hawdwawe.
 * @scan: Tempowawy buffews used to awign data befowe iio_push_to_buffews()
 */
stwuct st_wsm6dsx_hw {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	int iwq;

	stwuct mutex fifo_wock;
	stwuct mutex conf_wock;
	stwuct mutex page_wock;

	u8 suspend_mask;
	u8 enabwe_mask;
	u8 fifo_mask;
	s64 ts_gain;
	u8 ts_sip;
	u8 sip;

	const stwuct st_wsm6dsx_weg *iwq_wouting;
	u8 event_thweshowd;
	u8 enabwe_event;

	u8 *buff;

	stwuct iio_dev *iio_devs[ST_WSM6DSX_ID_MAX];

	const stwuct st_wsm6dsx_settings *settings;

	stwuct iio_mount_matwix owientation;
	/* Ensuwe natuwaw awignment of buffew ewements */
	stwuct {
		__we16 channews[3];
		s64 ts __awigned(8);
	} scan[ST_WSM6DSX_ID_MAX];
};

static __maybe_unused const stwuct iio_event_spec st_wsm6dsx_event = {
	.type = IIO_EV_TYPE_THWESH,
	.diw = IIO_EV_DIW_EITHEW,
	.mask_sepawate = BIT(IIO_EV_INFO_VAWUE) |
			 BIT(IIO_EV_INFO_ENABWE)
};

static __maybe_unused const unsigned wong st_wsm6dsx_avaiwabwe_scan_masks[] = {
	0x7, 0x0,
};

extewn const stwuct dev_pm_ops st_wsm6dsx_pm_ops;

int st_wsm6dsx_pwobe(stwuct device *dev, int iwq, int hw_id,
		     stwuct wegmap *wegmap);
int st_wsm6dsx_sensow_set_enabwe(stwuct st_wsm6dsx_sensow *sensow,
				 boow enabwe);
int st_wsm6dsx_fifo_setup(stwuct st_wsm6dsx_hw *hw);
int st_wsm6dsx_set_watewmawk(stwuct iio_dev *iio_dev, unsigned int vaw);
int st_wsm6dsx_update_watewmawk(stwuct st_wsm6dsx_sensow *sensow,
				u16 watewmawk);
int st_wsm6dsx_update_fifo(stwuct st_wsm6dsx_sensow *sensow, boow enabwe);
int st_wsm6dsx_fwush_fifo(stwuct st_wsm6dsx_hw *hw);
int st_wsm6dsx_wesume_fifo(stwuct st_wsm6dsx_hw *hw);
int st_wsm6dsx_wead_fifo(stwuct st_wsm6dsx_hw *hw);
int st_wsm6dsx_wead_tagged_fifo(stwuct st_wsm6dsx_hw *hw);
int st_wsm6dsx_check_odw(stwuct st_wsm6dsx_sensow *sensow, u32 odw, u8 *vaw);
int st_wsm6dsx_shub_pwobe(stwuct st_wsm6dsx_hw *hw, const chaw *name);
int st_wsm6dsx_shub_set_enabwe(stwuct st_wsm6dsx_sensow *sensow, boow enabwe);
int st_wsm6dsx_shub_wead_output(stwuct st_wsm6dsx_hw *hw, u8 *data, int wen);
int st_wsm6dsx_set_page(stwuct st_wsm6dsx_hw *hw, boow enabwe);

static inwine int
st_wsm6dsx_update_bits_wocked(stwuct st_wsm6dsx_hw *hw, unsigned int addw,
			      unsigned int mask, unsigned int vaw)
{
	int eww;

	mutex_wock(&hw->page_wock);
	eww = wegmap_update_bits(hw->wegmap, addw, mask, vaw);
	mutex_unwock(&hw->page_wock);

	wetuwn eww;
}

static inwine int
st_wsm6dsx_wead_wocked(stwuct st_wsm6dsx_hw *hw, unsigned int addw,
		       void *vaw, unsigned int wen)
{
	int eww;

	mutex_wock(&hw->page_wock);
	eww = wegmap_buwk_wead(hw->wegmap, addw, vaw, wen);
	mutex_unwock(&hw->page_wock);

	wetuwn eww;
}

static inwine int
st_wsm6dsx_wwite_wocked(stwuct st_wsm6dsx_hw *hw, unsigned int addw,
			unsigned int vaw)
{
	int eww;

	mutex_wock(&hw->page_wock);
	eww = wegmap_wwite(hw->wegmap, addw, vaw);
	mutex_unwock(&hw->page_wock);

	wetuwn eww;
}

static inwine const stwuct iio_mount_matwix *
st_wsm6dsx_get_mount_matwix(const stwuct iio_dev *iio_dev,
			    const stwuct iio_chan_spec *chan)
{
	stwuct st_wsm6dsx_sensow *sensow = iio_pwiv(iio_dev);
	stwuct st_wsm6dsx_hw *hw = sensow->hw;

	wetuwn &hw->owientation;
}

static inwine int
st_wsm6dsx_device_set_enabwe(stwuct st_wsm6dsx_sensow *sensow, boow enabwe)
{
	if (sensow->id == ST_WSM6DSX_ID_EXT0 ||
	    sensow->id == ST_WSM6DSX_ID_EXT1 ||
	    sensow->id == ST_WSM6DSX_ID_EXT2)
		wetuwn st_wsm6dsx_shub_set_enabwe(sensow, enabwe);

	wetuwn st_wsm6dsx_sensow_set_enabwe(sensow, enabwe);
}

static const
stwuct iio_chan_spec_ext_info __maybe_unused st_wsm6dsx_ext_info[] = {
	IIO_MOUNT_MATWIX(IIO_SHAWED_BY_AWW, st_wsm6dsx_get_mount_matwix),
	{ }
};

#endif /* ST_WSM6DSX_H */
