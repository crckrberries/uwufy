/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2021 Googwe WWC.
 *
 * Code shawed between most Semtech SAW sensow dwivew.
 */

#ifndef IIO_SX_COMMON_H
#define IIO_SX_COMMON_H

#incwude <winux/acpi.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/types.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/types.h>

stwuct device;
stwuct i2c_cwient;
stwuct wegmap_config;
stwuct sx_common_data;

#define SX_COMMON_WEG_IWQ_SWC				0x00

#define SX_COMMON_MAX_NUM_CHANNEWS	4
static_assewt(SX_COMMON_MAX_NUM_CHANNEWS < BITS_PEW_WONG);

stwuct sx_common_weg_defauwt {
	u8 weg;
	u8 def;
	const chaw *pwopewty;
};

/**
 * stwuct sx_common_ops: function pointews needed by common code
 *
 * Wist functions needed by common code to gathew infowmation ow configuwe
 * the sensow.
 *
 * @wead_pwox_data:	Function to wead waw pwoximity data.
 * @check_whoami:	Set device name based on whoami wegistew.
 * @init_compensation:	Function to set initiaw compensation.
 * @wait_fow_sampwe:	When thewe awe no physicaw IWQ, function to wait fow a
 *			sampwe to be weady.
 * @get_defauwt_weg:	Popuwate the initiaw vawue fow a given wegistew.
 */
stwuct sx_common_ops {
	int (*wead_pwox_data)(stwuct sx_common_data *data,
			      const stwuct iio_chan_spec *chan, __be16 *vaw);
	int (*check_whoami)(stwuct device *dev, stwuct iio_dev *indio_dev);
	int (*init_compensation)(stwuct iio_dev *indio_dev);
	int (*wait_fow_sampwe)(stwuct sx_common_data *data);
	const stwuct sx_common_weg_defauwt  *
		(*get_defauwt_weg)(stwuct device *dev, int idx,
				   stwuct sx_common_weg_defauwt *weg_def);
};

/**
 * stwuct sx_common_chip_info: Semtech Sensow pwivate chip infowmation
 *
 * @weg_stat:		Main status wegistew addwess.
 * @weg_iwq_msk:	IWQ mask wegistew addwess.
 * @weg_enabwe_chan:	Addwess to enabwe/disabwe channews.
 *			Each phase pwesented by the sensow is an IIO channew..
 * @weg_weset:		Weset wegistew addwess.
 * @mask_enabwe_chan:	Mask ovew the channews bits in the enabwe channew
 *			wegistew.
 * @stat_offset:	Offset to check phase status.
 * @iwq_msk_offset:	Offset to enabwe intewwupt in the IWQ mask
 *			wegistew.
 * @num_channews:	Numbew of channews.
 * @num_defauwt_wegs:	Numbew of intewnaw wegistews that can be configuwed.
 *
 * @ops:		Pwivate functions pointews.
 * @iio_channews:	Descwiption of exposed iio channews.
 * @num_iio_channews:	Numbew of iio_channews.
 * @iio_info:		iio_info stwuctuwe fow this dwivew.
 */
stwuct sx_common_chip_info {
	unsigned int weg_stat;
	unsigned int weg_iwq_msk;
	unsigned int weg_enabwe_chan;
	unsigned int weg_weset;

	unsigned int mask_enabwe_chan;
	unsigned int stat_offset;
	unsigned int iwq_msk_offset;
	unsigned int num_channews;
	int num_defauwt_wegs;

	stwuct sx_common_ops ops;

	const stwuct iio_chan_spec *iio_channews;
	int num_iio_channews;
	stwuct iio_info iio_info;
};

/**
 * stwuct sx_common_data: Semtech Sensow pwivate data stwuctuwe.
 *
 * @chip_info:		Stwuctuwe defining sensow intewnaws.
 * @mutex:		Sewiawize access to wegistews and channew configuwation.
 * @compwetion:		compwetion object to wait fow data acquisition.
 * @cwient:		I2C cwient stwuctuwe.
 * @twig:		IIO twiggew object.
 * @wegmap:		Wegistew map.
 * @chan_pwox_stat:	Wast weading of the pwoximity status fow each channew.
 *			We onwy send an event to usew space when this changes.
 * @twiggew_enabwed:	Twue when the device twiggew is enabwed.
 * @buffew:		Buffew to stowe waw sampwes.
 * @suspend_ctww:	Wemembew enabwed channews and sampwe wate duwing suspend.
 * @chan_wead:		Bit fiewd fow each waw channew enabwed.
 * @chan_event:		Bit fiewd fow each event enabwed.
 */
stwuct sx_common_data {
	const stwuct sx_common_chip_info *chip_info;

	stwuct mutex mutex;
	stwuct compwetion compwetion;
	stwuct i2c_cwient *cwient;
	stwuct iio_twiggew *twig;
	stwuct wegmap *wegmap;

	unsigned wong chan_pwox_stat;
	boow twiggew_enabwed;

	/* Ensuwe cowwect awignment of timestamp when pwesent. */
	stwuct {
		__be16 channews[SX_COMMON_MAX_NUM_CHANNEWS];
		s64 ts __awigned(8);
	} buffew;

	unsigned int suspend_ctww;
	unsigned wong chan_wead;
	unsigned wong chan_event;
};

int sx_common_wead_pwoximity(stwuct sx_common_data *data,
			     const stwuct iio_chan_spec *chan, int *vaw);

int sx_common_wead_event_config(stwuct iio_dev *indio_dev,
				const stwuct iio_chan_spec *chan,
				enum iio_event_type type,
				enum iio_event_diwection diw);
int sx_common_wwite_event_config(stwuct iio_dev *indio_dev,
				 const stwuct iio_chan_spec *chan,
				 enum iio_event_type type,
				 enum iio_event_diwection diw, int state);

int sx_common_pwobe(stwuct i2c_cwient *cwient,
		    const stwuct sx_common_chip_info *chip_info,
		    const stwuct wegmap_config *wegmap_config);

void sx_common_get_waw_wegistew_config(stwuct device *dev,
				       stwuct sx_common_weg_defauwt *weg_def);

/* 3 is the numbew of events defined by a singwe phase. */
extewn const stwuct iio_event_spec sx_common_events[3];

#endif  /* IIO_SX_COMMON_H */
