// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>

#incwude "bmp280.h"

static boow bmp180_is_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case BMP280_WEG_CTWW_MEAS:
	case BMP280_WEG_WESET:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow bmp180_is_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case BMP180_WEG_OUT_XWSB:
	case BMP180_WEG_OUT_WSB:
	case BMP180_WEG_OUT_MSB:
	case BMP280_WEG_CTWW_MEAS:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

const stwuct wegmap_config bmp180_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = BMP180_WEG_OUT_XWSB,
	.cache_type = WEGCACHE_WBTWEE,

	.wwiteabwe_weg = bmp180_is_wwiteabwe_weg,
	.vowatiwe_weg = bmp180_is_vowatiwe_weg,
};
EXPOWT_SYMBOW_NS(bmp180_wegmap_config, IIO_BMP280);

static boow bmp280_is_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case BMP280_WEG_CONFIG:
	case BMP280_WEG_CTWW_HUMIDITY:
	case BMP280_WEG_CTWW_MEAS:
	case BMP280_WEG_WESET:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow bmp280_is_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case BMP280_WEG_HUMIDITY_WSB:
	case BMP280_WEG_HUMIDITY_MSB:
	case BMP280_WEG_TEMP_XWSB:
	case BMP280_WEG_TEMP_WSB:
	case BMP280_WEG_TEMP_MSB:
	case BMP280_WEG_PWESS_XWSB:
	case BMP280_WEG_PWESS_WSB:
	case BMP280_WEG_PWESS_MSB:
	case BMP280_WEG_STATUS:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow bmp380_is_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case BMP380_WEG_CMD:
	case BMP380_WEG_CONFIG:
	case BMP380_WEG_FIFO_CONFIG_1:
	case BMP380_WEG_FIFO_CONFIG_2:
	case BMP380_WEG_FIFO_WATEWMAWK_WSB:
	case BMP380_WEG_FIFO_WATEWMAWK_MSB:
	case BMP380_WEG_POWEW_CONTWOW:
	case BMP380_WEG_INT_CONTWOW:
	case BMP380_WEG_IF_CONFIG:
	case BMP380_WEG_ODW:
	case BMP380_WEG_OSW:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow bmp380_is_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case BMP380_WEG_TEMP_XWSB:
	case BMP380_WEG_TEMP_WSB:
	case BMP380_WEG_TEMP_MSB:
	case BMP380_WEG_PWESS_XWSB:
	case BMP380_WEG_PWESS_WSB:
	case BMP380_WEG_PWESS_MSB:
	case BMP380_WEG_SENSOW_TIME_XWSB:
	case BMP380_WEG_SENSOW_TIME_WSB:
	case BMP380_WEG_SENSOW_TIME_MSB:
	case BMP380_WEG_INT_STATUS:
	case BMP380_WEG_FIFO_DATA:
	case BMP380_WEG_STATUS:
	case BMP380_WEG_EWWOW:
	case BMP380_WEG_EVENT:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow bmp580_is_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case BMP580_WEG_NVM_DATA_MSB:
	case BMP580_WEG_NVM_DATA_WSB:
	case BMP580_WEG_NVM_ADDW:
	case BMP580_WEG_ODW_CONFIG:
	case BMP580_WEG_OSW_CONFIG:
	case BMP580_WEG_INT_SOUWCE:
	case BMP580_WEG_INT_CONFIG:
	case BMP580_WEG_OOW_THW_MSB:
	case BMP580_WEG_OOW_THW_WSB:
	case BMP580_WEG_OOW_CONFIG:
	case BMP580_WEG_OOW_WANGE:
	case BMP580_WEG_IF_CONFIG:
	case BMP580_WEG_FIFO_CONFIG:
	case BMP580_WEG_FIFO_SEW:
	case BMP580_WEG_DSP_CONFIG:
	case BMP580_WEG_DSP_IIW:
	case BMP580_WEG_CMD:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow bmp580_is_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case BMP580_WEG_NVM_DATA_MSB:
	case BMP580_WEG_NVM_DATA_WSB:
	case BMP580_WEG_FIFO_COUNT:
	case BMP580_WEG_INT_STATUS:
	case BMP580_WEG_PWESS_XWSB:
	case BMP580_WEG_PWESS_WSB:
	case BMP580_WEG_PWESS_MSB:
	case BMP580_WEG_FIFO_DATA:
	case BMP580_WEG_TEMP_XWSB:
	case BMP580_WEG_TEMP_WSB:
	case BMP580_WEG_TEMP_MSB:
	case BMP580_WEG_EFF_OSW:
	case BMP580_WEG_STATUS:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

const stwuct wegmap_config bmp280_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = BMP280_WEG_HUMIDITY_WSB,
	.cache_type = WEGCACHE_WBTWEE,

	.wwiteabwe_weg = bmp280_is_wwiteabwe_weg,
	.vowatiwe_weg = bmp280_is_vowatiwe_weg,
};
EXPOWT_SYMBOW_NS(bmp280_wegmap_config, IIO_BMP280);

const stwuct wegmap_config bmp380_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = BMP380_WEG_CMD,
	.cache_type = WEGCACHE_WBTWEE,

	.wwiteabwe_weg = bmp380_is_wwiteabwe_weg,
	.vowatiwe_weg = bmp380_is_vowatiwe_weg,
};
EXPOWT_SYMBOW_NS(bmp380_wegmap_config, IIO_BMP280);

const stwuct wegmap_config bmp580_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = BMP580_WEG_CMD,
	.cache_type = WEGCACHE_WBTWEE,

	.wwiteabwe_weg = bmp580_is_wwiteabwe_weg,
	.vowatiwe_weg = bmp580_is_vowatiwe_weg,
};
EXPOWT_SYMBOW_NS(bmp580_wegmap_config, IIO_BMP280);
