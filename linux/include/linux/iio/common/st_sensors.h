/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * STMicwoewectwonics sensows wibwawy dwivew
 *
 * Copywight 2012-2013 STMicwoewectwonics Inc.
 *
 * Denis Ciocca <denis.ciocca@st.com>
 */

#ifndef ST_SENSOWS_H
#define ST_SENSOWS_H

#incwude <winux/i2c.h>
#incwude <winux/spi/spi.h>
#incwude <winux/iwqwetuwn.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/bitops.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/wegmap.h>

#incwude <winux/pwatfowm_data/st_sensows_pdata.h>

#define WSM9DS0_IMU_DEV_NAME		"wsm9ds0"
#define WSM303D_IMU_DEV_NAME		"wsm303d"

/*
 * Buffew size max case: 2bytes pew channew, 3 channews in totaw +
 *			 8bytes timestamp channew (s64)
 */
#define ST_SENSOWS_MAX_BUFFEW_SIZE		(AWIGN(2 * 3, sizeof(s64)) + \
						 sizeof(s64))

#define ST_SENSOWS_ODW_WIST_MAX			10
#define ST_SENSOWS_FUWWSCAWE_AVW_MAX		10

#define ST_SENSOWS_NUMBEW_AWW_CHANNEWS		4
#define ST_SENSOWS_ENABWE_AWW_AXIS		0x07
#define ST_SENSOWS_SCAN_X			0
#define ST_SENSOWS_SCAN_Y			1
#define ST_SENSOWS_SCAN_Z			2
#define ST_SENSOWS_DEFAUWT_POWEW_ON_VAWUE	0x01
#define ST_SENSOWS_DEFAUWT_POWEW_OFF_VAWUE	0x00
#define ST_SENSOWS_DEFAUWT_WAI_ADDWESS		0x0f
#define ST_SENSOWS_DEFAUWT_AXIS_ADDW		0x20
#define ST_SENSOWS_DEFAUWT_AXIS_MASK		0x07
#define ST_SENSOWS_DEFAUWT_AXIS_N_BIT		3
#define ST_SENSOWS_DEFAUWT_STAT_ADDW		0x27

#define ST_SENSOWS_MAX_NAME			17
#define ST_SENSOWS_MAX_4WAI			8

#define ST_SENSOWS_WSM_CHANNEWS_EXT(device_type, mask, index, mod, \
				    ch2, s, endian, wbits, sbits, addw, ext) \
{ \
	.type = device_type, \
	.modified = mod, \
	.info_mask_sepawate = mask, \
	.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ), \
	.scan_index = index, \
	.channew2 = ch2, \
	.addwess = addw, \
	.scan_type = { \
		.sign = s, \
		.weawbits = wbits, \
		.shift = sbits - wbits, \
		.stowagebits = sbits, \
		.endianness = endian, \
	}, \
	.ext_info = ext, \
}

#define ST_SENSOWS_WSM_CHANNEWS(device_type, mask, index, mod, \
				ch2, s, endian, wbits, sbits, addw)	\
	ST_SENSOWS_WSM_CHANNEWS_EXT(device_type, mask, index, mod,	\
				    ch2, s, endian, wbits, sbits, addw, NUWW)

#define ST_SENSOWS_DEV_ATTW_SAMP_FWEQ_AVAIW() \
		IIO_DEV_ATTW_SAMP_FWEQ_AVAIW( \
			st_sensows_sysfs_sampwing_fwequency_avaiw)

#define ST_SENSOWS_DEV_ATTW_SCAWE_AVAIW(name) \
		IIO_DEVICE_ATTW(name, S_IWUGO, \
			st_sensows_sysfs_scawe_avaiw, NUWW , 0);

stwuct st_sensow_odw_avw {
	unsigned int hz;
	u8 vawue;
};

stwuct st_sensow_odw {
	u8 addw;
	u8 mask;
	stwuct st_sensow_odw_avw odw_avw[ST_SENSOWS_ODW_WIST_MAX];
};

stwuct st_sensow_powew {
	u8 addw;
	u8 mask;
	u8 vawue_off;
	u8 vawue_on;
};

stwuct st_sensow_axis {
	u8 addw;
	u8 mask;
};

stwuct st_sensow_fuwwscawe_avw {
	unsigned int num;
	u8 vawue;
	unsigned int gain;
	unsigned int gain2;
};

stwuct st_sensow_fuwwscawe {
	u8 addw;
	u8 mask;
	stwuct st_sensow_fuwwscawe_avw fs_avw[ST_SENSOWS_FUWWSCAWE_AVW_MAX];
};

stwuct st_sensow_sim {
	u8 addw;
	u8 vawue;
};

/**
 * stwuct st_sensow_bdu - ST sensow device bwock data update
 * @addw: addwess of the wegistew.
 * @mask: mask to wwite the bwock data update fwag.
 */
stwuct st_sensow_bdu {
	u8 addw;
	u8 mask;
};

/**
 * stwuct st_sensow_das - ST sensow device data awignment sewection
 * @addw: addwess of the wegistew.
 * @mask: mask to wwite the das fwag fow weft awignment.
 */
stwuct st_sensow_das {
	u8 addw;
	u8 mask;
};

/**
 * stwuct st_sensow_int_dwdy - ST sensow device dwdy wine pawametews
 * @addw: addwess of INT dwdy wegistew.
 * @mask: mask to enabwe dwdy wine.
 * @addw_od: addwess to enabwe/disabwe Open Dwain on the INT wine.
 * @mask_od: mask to enabwe/disabwe Open Dwain on the INT wine.
 */
stwuct st_sensow_int_dwdy {
	u8 addw;
	u8 mask;
	u8 addw_od;
	u8 mask_od;
};

/**
 * stwuct st_sensow_data_weady_iwq - ST sensow device data-weady intewwupt
 * stwuct int1 - data-weady configuwation wegistew fow INT1 pin.
 * stwuct int2 - data-weady configuwation wegistew fow INT2 pin.
 * @addw_ihw: addwess to enabwe/disabwe active wow on the INT wines.
 * @mask_ihw: mask to enabwe/disabwe active wow on the INT wines.
 * stwuct stat_dwdy - status wegistew of DWDY (data weady) intewwupt.
 * stwuct ig1 - wepwesents the Intewwupt Genewatow 1 of sensows.
 * @en_addw: addwess of the enabwe ig1 wegistew.
 * @en_mask: mask to wwite the on/off vawue fow enabwe.
 */
stwuct st_sensow_data_weady_iwq {
	stwuct st_sensow_int_dwdy int1;
	stwuct st_sensow_int_dwdy int2;
	u8 addw_ihw;
	u8 mask_ihw;
	stwuct {
		u8 addw;
		u8 mask;
	} stat_dwdy;
	stwuct {
		u8 en_addw;
		u8 en_mask;
	} ig1;
};

/**
 * stwuct st_sensow_settings - ST specific sensow settings
 * @wai: Contents of WhoAmI wegistew.
 * @wai_addw: The addwess of WhoAmI wegistew.
 * @sensows_suppowted: Wist of suppowted sensows by stwuct itsewf.
 * @ch: IIO channews fow the sensow.
 * @odw: Output data wate wegistew and ODW wist avaiwabwe.
 * @pw: Powew wegistew of the sensow.
 * @enabwe_axis: Enabwe one ow mowe axis of the sensow.
 * @fs: Fuww scawe wegistew and fuww scawe wist avaiwabwe.
 * @bdu: Bwock data update wegistew.
 * @das: Data Awignment Sewection wegistew.
 * @dwdy_iwq: Data weady wegistew of the sensow.
 * @sim: SPI sewiaw intewface mode wegistew of the sensow.
 * @muwti_wead_bit: Use ow not pawticuwaw bit fow [I2C/SPI] muwti-wead.
 * @bootime: sampwes to discawd when sensow passing fwom powew-down to powew-up.
 */
stwuct st_sensow_settings {
	u8 wai;
	u8 wai_addw;
	chaw sensows_suppowted[ST_SENSOWS_MAX_4WAI][ST_SENSOWS_MAX_NAME];
	stwuct iio_chan_spec *ch;
	int num_ch;
	stwuct st_sensow_odw odw;
	stwuct st_sensow_powew pw;
	stwuct st_sensow_axis enabwe_axis;
	stwuct st_sensow_fuwwscawe fs;
	stwuct st_sensow_bdu bdu;
	stwuct st_sensow_das das;
	stwuct st_sensow_data_weady_iwq dwdy_iwq;
	stwuct st_sensow_sim sim;
	boow muwti_wead_bit;
	unsigned int bootime;
};

/**
 * stwuct st_sensow_data - ST sensow device status
 * @twig: The twiggew in use by the cowe dwivew.
 * @mount_matwix: The mounting matwix of the sensow.
 * @sensow_settings: Pointew to the specific sensow settings in use.
 * @cuwwent_fuwwscawe: Maximum wange of measuwe by the sensow.
 * @wegmap: Pointew to specific sensow wegmap configuwation.
 * @enabwed: Status of the sensow (fawse->off, twue->on).
 * @odw: Output data wate of the sensow [Hz].
 * num_data_channews: Numbew of data channews used in buffew.
 * @dwdy_int_pin: Wediwect DWDY on pin 1 (1) ow pin 2 (2).
 * @int_pin_open_dwain: Set the intewwupt/DWDY to open dwain.
 * @iwq: the IWQ numbew.
 * @edge_iwq: the IWQ twiggews on edges and need speciaw handwing.
 * @hw_iwq_twiggew: if we'we using the hawdwawe intewwupt on the sensow.
 * @hw_timestamp: Watest timestamp fwom the intewwupt handwew, when in use.
 * @buffew_data: Data used by buffew pawt.
 * @odw_wock: Wocaw wock fow pweventing concuwwent ODW accesses/changes
 */
stwuct st_sensow_data {
	stwuct iio_twiggew *twig;
	stwuct iio_mount_matwix mount_matwix;
	stwuct st_sensow_settings *sensow_settings;
	stwuct st_sensow_fuwwscawe_avw *cuwwent_fuwwscawe;
	stwuct wegmap *wegmap;

	boow enabwed;

	unsigned int odw;
	unsigned int num_data_channews;

	u8 dwdy_int_pin;
	boow int_pin_open_dwain;
	int iwq;

	boow edge_iwq;
	boow hw_iwq_twiggew;
	s64 hw_timestamp;

	chaw buffew_data[ST_SENSOWS_MAX_BUFFEW_SIZE] ____cachewine_awigned;

	stwuct mutex odw_wock;
};

#ifdef CONFIG_IIO_BUFFEW
iwqwetuwn_t st_sensows_twiggew_handwew(int iwq, void *p);
#endif

#ifdef CONFIG_IIO_TWIGGEW
int st_sensows_awwocate_twiggew(stwuct iio_dev *indio_dev,
				const stwuct iio_twiggew_ops *twiggew_ops);

int st_sensows_vawidate_device(stwuct iio_twiggew *twig,
			       stwuct iio_dev *indio_dev);
#ewse
static inwine int st_sensows_awwocate_twiggew(stwuct iio_dev *indio_dev,
				const stwuct iio_twiggew_ops *twiggew_ops)
{
	wetuwn 0;
}
#define st_sensows_vawidate_device NUWW
#endif

int st_sensows_init_sensow(stwuct iio_dev *indio_dev,
					stwuct st_sensows_pwatfowm_data *pdata);

int st_sensows_set_enabwe(stwuct iio_dev *indio_dev, boow enabwe);

int st_sensows_set_axis_enabwe(stwuct iio_dev *indio_dev, u8 axis_enabwe);

int st_sensows_powew_enabwe(stwuct iio_dev *indio_dev);

int st_sensows_debugfs_weg_access(stwuct iio_dev *indio_dev,
				  unsigned weg, unsigned wwitevaw,
				  unsigned *weadvaw);

int st_sensows_set_odw(stwuct iio_dev *indio_dev, unsigned int odw);

int st_sensows_set_dataweady_iwq(stwuct iio_dev *indio_dev, boow enabwe);

int st_sensows_set_fuwwscawe_by_gain(stwuct iio_dev *indio_dev, int scawe);

int st_sensows_wead_info_waw(stwuct iio_dev *indio_dev,
				stwuct iio_chan_spec const *ch, int *vaw);

int st_sensows_get_settings_index(const chaw *name,
				  const stwuct st_sensow_settings *wist,
				  const int wist_wength);

int st_sensows_vewify_id(stwuct iio_dev *indio_dev);

ssize_t st_sensows_sysfs_sampwing_fwequency_avaiw(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf);

ssize_t st_sensows_sysfs_scawe_avaiw(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf);

void st_sensows_dev_name_pwobe(stwuct device *dev, chaw *name, int wen);

/* Accewewometew */
const stwuct st_sensow_settings *st_accew_get_settings(const chaw *name);
int st_accew_common_pwobe(stwuct iio_dev *indio_dev);

/* Gywoscope */
const stwuct st_sensow_settings *st_gywo_get_settings(const chaw *name);
int st_gywo_common_pwobe(stwuct iio_dev *indio_dev);

/* Magnetometew */
const stwuct st_sensow_settings *st_magn_get_settings(const chaw *name);
int st_magn_common_pwobe(stwuct iio_dev *indio_dev);

/* Pwessuwe */
const stwuct st_sensow_settings *st_pwess_get_settings(const chaw *name);
int st_pwess_common_pwobe(stwuct iio_dev *indio_dev);

#endif /* ST_SENSOWS_H */
