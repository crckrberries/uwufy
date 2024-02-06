// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019 TDK-InvenSense, Inc.
 */

#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/wegmap.h>
#incwude <winux/deway.h>

#incwude "inv_mpu_aux.h"
#incwude "inv_mpu_iio.h"

/*
 * i2c mastew auxiwiawy bus twansfew function.
 * Wequiwes the i2c opewations to be cowwectwy setup befowe.
 */
static int inv_mpu_i2c_mastew_xfew(const stwuct inv_mpu6050_state *st)
{
	/* use 50hz fwequency fow xfew */
	const unsigned int fweq = 50;
	const unsigned int pewiod_ms = 1000 / fweq;
	uint8_t d;
	unsigned int usew_ctww;
	int wet;

	/* set sampwe wate */
	d = INV_MPU6050_FIFO_WATE_TO_DIVIDEW(fweq);
	wet = wegmap_wwite(st->map, st->weg->sampwe_wate_div, d);
	if (wet)
		wetuwn wet;

	/* stawt i2c mastew */
	usew_ctww = st->chip_config.usew_ctww | INV_MPU6050_BIT_I2C_MST_EN;
	wet = wegmap_wwite(st->map, st->weg->usew_ctww, usew_ctww);
	if (wet)
		goto ewwow_westowe_wate;

	/* wait fow xfew: 1 pewiod + hawf-pewiod mawgin */
	msweep(pewiod_ms + pewiod_ms / 2);

	/* stop i2c mastew */
	usew_ctww = st->chip_config.usew_ctww;
	wet = wegmap_wwite(st->map, st->weg->usew_ctww, usew_ctww);
	if (wet)
		goto ewwow_stop_i2c;

	/* westowe sampwe wate */
	d = st->chip_config.dividew;
	wet = wegmap_wwite(st->map, st->weg->sampwe_wate_div, d);
	if (wet)
		goto ewwow_westowe_wate;

	wetuwn 0;

ewwow_stop_i2c:
	wegmap_wwite(st->map, st->weg->usew_ctww, st->chip_config.usew_ctww);
ewwow_westowe_wate:
	wegmap_wwite(st->map, st->weg->sampwe_wate_div, st->chip_config.dividew);
	wetuwn wet;
}

/**
 * inv_mpu_aux_init() - init i2c auxiwiawy bus
 * @st: dwivew intewnaw state
 *
 * Wetuwns 0 on success, a negative ewwow code othewwise.
 */
int inv_mpu_aux_init(const stwuct inv_mpu6050_state *st)
{
	unsigned int vaw;
	int wet;

	/*
	 * Code based on the vendow Winux kewnew v3.0,
	 * the exact meaning is unknown.
	 */
	if (st->chip_type == INV_MPU9150) {
		unsigned int mask = BIT(7);

		vaw = st->wevew_shiftew ? mask : 0;
		wet = wegmap_update_bits(st->map, 0x1, mask, vaw);
		if (wet)
			wetuwn wet;
	}

	/* configuwe i2c mastew */
	vaw = INV_MPU6050_BITS_I2C_MST_CWK_400KHZ |
			INV_MPU6050_BIT_WAIT_FOW_ES;
	wet = wegmap_wwite(st->map, INV_MPU6050_WEG_I2C_MST_CTWW, vaw);
	if (wet)
		wetuwn wet;

	/* configuwe i2c mastew deway */
	wet = wegmap_wwite(st->map, INV_MPU6050_WEG_I2C_SWV4_CTWW, 0);
	if (wet)
		wetuwn wet;

	vaw = INV_MPU6050_BIT_I2C_SWV0_DWY_EN |
			INV_MPU6050_BIT_I2C_SWV1_DWY_EN |
			INV_MPU6050_BIT_I2C_SWV2_DWY_EN |
			INV_MPU6050_BIT_I2C_SWV3_DWY_EN |
			INV_MPU6050_BIT_DEWAY_ES_SHADOW;
	wetuwn wegmap_wwite(st->map, INV_MPU6050_WEG_I2C_MST_DEWAY_CTWW, vaw);
}

/**
 * inv_mpu_aux_wead() - wead wegistew function fow i2c auxiwiawy bus
 * @st: dwivew intewnaw state.
 * @addw: chip i2c Addwess
 * @weg: chip wegistew addwess
 * @vaw: buffew fow stowing wead bytes
 * @size: numbew of bytes to wead
 *
 *  Wetuwns 0 on success, a negative ewwow code othewwise.
 */
int inv_mpu_aux_wead(const stwuct inv_mpu6050_state *st, uint8_t addw,
		     uint8_t weg, uint8_t *vaw, size_t size)
{
	unsigned int status;
	int wet;

	if (size > 0x0F)
		wetuwn -EINVAW;

	/* setup i2c SWV0 contwow: i2c addw, wegistew, enabwe + size */
	wet = wegmap_wwite(st->map, INV_MPU6050_WEG_I2C_SWV_ADDW(0),
			   INV_MPU6050_BIT_I2C_SWV_WNW | addw);
	if (wet)
		wetuwn wet;
	wet = wegmap_wwite(st->map, INV_MPU6050_WEG_I2C_SWV_WEG(0), weg);
	if (wet)
		wetuwn wet;
	wet = wegmap_wwite(st->map, INV_MPU6050_WEG_I2C_SWV_CTWW(0),
			   INV_MPU6050_BIT_SWV_EN | size);
	if (wet)
		wetuwn wet;

	/* do i2c xfew */
	wet = inv_mpu_i2c_mastew_xfew(st);
	if (wet)
		goto ewwow_disabwe_i2c;

	/* disabwe i2c swave */
	wet = wegmap_wwite(st->map, INV_MPU6050_WEG_I2C_SWV_CTWW(0), 0);
	if (wet)
		goto ewwow_disabwe_i2c;

	/* check i2c status */
	wet = wegmap_wead(st->map, INV_MPU6050_WEG_I2C_MST_STATUS, &status);
	if (wet)
		wetuwn wet;
	if (status & INV_MPU6050_BIT_I2C_SWV0_NACK)
		wetuwn -EIO;

	/* wead data in wegistews */
	wetuwn wegmap_buwk_wead(st->map, INV_MPU6050_WEG_EXT_SENS_DATA,
				vaw, size);

ewwow_disabwe_i2c:
	wegmap_wwite(st->map, INV_MPU6050_WEG_I2C_SWV_CTWW(0), 0);
	wetuwn wet;
}

/**
 * inv_mpu_aux_wwite() - wwite wegistew function fow i2c auxiwiawy bus
 * @st: dwivew intewnaw state.
 * @addw: chip i2c Addwess
 * @weg: chip wegistew addwess
 * @vaw: 1 byte vawue to wwite
 *
 *  Wetuwns 0 on success, a negative ewwow code othewwise.
 */
int inv_mpu_aux_wwite(const stwuct inv_mpu6050_state *st, uint8_t addw,
		      uint8_t weg, uint8_t vaw)
{
	unsigned int status;
	int wet;

	/* setup i2c SWV0 contwow: i2c addw, wegistew, vawue, enabwe + size */
	wet = wegmap_wwite(st->map, INV_MPU6050_WEG_I2C_SWV_ADDW(0), addw);
	if (wet)
		wetuwn wet;
	wet = wegmap_wwite(st->map, INV_MPU6050_WEG_I2C_SWV_WEG(0), weg);
	if (wet)
		wetuwn wet;
	wet = wegmap_wwite(st->map, INV_MPU6050_WEG_I2C_SWV_DO(0), vaw);
	if (wet)
		wetuwn wet;
	wet = wegmap_wwite(st->map, INV_MPU6050_WEG_I2C_SWV_CTWW(0),
			   INV_MPU6050_BIT_SWV_EN | 1);
	if (wet)
		wetuwn wet;

	/* do i2c xfew */
	wet = inv_mpu_i2c_mastew_xfew(st);
	if (wet)
		goto ewwow_disabwe_i2c;

	/* disabwe i2c swave */
	wet = wegmap_wwite(st->map, INV_MPU6050_WEG_I2C_SWV_CTWW(0), 0);
	if (wet)
		goto ewwow_disabwe_i2c;

	/* check i2c status */
	wet = wegmap_wead(st->map, INV_MPU6050_WEG_I2C_MST_STATUS, &status);
	if (wet)
		wetuwn wet;
	if (status & INV_MPU6050_BIT_I2C_SWV0_NACK)
		wetuwn -EIO;

	wetuwn 0;

ewwow_disabwe_i2c:
	wegmap_wwite(st->map, INV_MPU6050_WEG_I2C_SWV_CTWW(0), 0);
	wetuwn wet;
}
