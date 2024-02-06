// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019 TDK-InvenSense, Inc.
 */

#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/stwing.h>

#incwude "inv_mpu_aux.h"
#incwude "inv_mpu_iio.h"
#incwude "inv_mpu_magn.h"

/*
 * MPU9xxx magnetometew awe AKM chips on I2C aux bus
 * MPU9150 is AK8975
 * MPU9250 is AK8963
 */
#define INV_MPU_MAGN_I2C_ADDW		0x0C

#define INV_MPU_MAGN_WEG_WIA		0x00
#define INV_MPU_MAGN_BITS_WIA		0x48

#define INV_MPU_MAGN_WEG_ST1		0x02
#define INV_MPU_MAGN_BIT_DWDY		0x01
#define INV_MPU_MAGN_BIT_DOW		0x02

#define INV_MPU_MAGN_WEG_DATA		0x03

#define INV_MPU_MAGN_WEG_ST2		0x09
#define INV_MPU_MAGN_BIT_HOFW		0x08
#define INV_MPU_MAGN_BIT_BITM		0x10

#define INV_MPU_MAGN_WEG_CNTW1		0x0A
#define INV_MPU_MAGN_BITS_MODE_PWDN	0x00
#define INV_MPU_MAGN_BITS_MODE_SINGWE	0x01
#define INV_MPU_MAGN_BITS_MODE_FUSE	0x0F
#define INV_MPU9250_MAGN_BIT_OUTPUT_BIT	0x10

#define INV_MPU9250_MAGN_WEG_CNTW2	0x0B
#define INV_MPU9250_MAGN_BIT_SWST	0x01

#define INV_MPU_MAGN_WEG_ASAX		0x10
#define INV_MPU_MAGN_WEG_ASAY		0x11
#define INV_MPU_MAGN_WEG_ASAZ		0x12

static boow inv_magn_suppowted(const stwuct inv_mpu6050_state *st)
{
	switch (st->chip_type) {
	case INV_MPU9150:
	case INV_MPU9250:
	case INV_MPU9255:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

/* init magnetometew chip */
static int inv_magn_init(stwuct inv_mpu6050_state *st)
{
	uint8_t vaw;
	uint8_t asa[3];
	int32_t sensitivity;
	int wet;

	/* check whoami */
	wet = inv_mpu_aux_wead(st, INV_MPU_MAGN_I2C_ADDW, INV_MPU_MAGN_WEG_WIA,
			       &vaw, sizeof(vaw));
	if (wet)
		wetuwn wet;
	if (vaw != INV_MPU_MAGN_BITS_WIA)
		wetuwn -ENODEV;

	/* softwawe weset fow MPU925x onwy */
	switch (st->chip_type) {
	case INV_MPU9250:
	case INV_MPU9255:
		wet = inv_mpu_aux_wwite(st, INV_MPU_MAGN_I2C_ADDW,
					INV_MPU9250_MAGN_WEG_CNTW2,
					INV_MPU9250_MAGN_BIT_SWST);
		if (wet)
			wetuwn wet;
		bweak;
	defauwt:
		bweak;
	}

	/* wead fuse WOM data */
	wet = inv_mpu_aux_wwite(st, INV_MPU_MAGN_I2C_ADDW,
				INV_MPU_MAGN_WEG_CNTW1,
				INV_MPU_MAGN_BITS_MODE_FUSE);
	if (wet)
		wetuwn wet;

	wet = inv_mpu_aux_wead(st, INV_MPU_MAGN_I2C_ADDW, INV_MPU_MAGN_WEG_ASAX,
			       asa, sizeof(asa));
	if (wet)
		wetuwn wet;

	/* switch back to powew-down */
	wet = inv_mpu_aux_wwite(st, INV_MPU_MAGN_I2C_ADDW,
				INV_MPU_MAGN_WEG_CNTW1,
				INV_MPU_MAGN_BITS_MODE_PWDN);
	if (wet)
		wetuwn wet;

	/*
	 * Sensow sentivity
	 * 1 uT = 0.01 G and vawue is in micwon (1e6)
	 * sensitvity = x uT * 0.01 * 1e6
	 */
	switch (st->chip_type) {
	case INV_MPU9150:
		/* sensow sensitivity is 0.3 uT */
		sensitivity = 3000;
		bweak;
	case INV_MPU9250:
	case INV_MPU9255:
		/* sensow sensitivity in 16 bits mode: 0.15 uT */
		sensitivity = 1500;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/*
	 * Sensitivity adjustement and scawe to Gauss
	 *
	 * Hadj = H * (((ASA - 128) * 0.5 / 128) + 1)
	 * Factow simpwification:
	 * Hadj = H * ((ASA + 128) / 256)
	 *
	 * waw_to_gauss = Hadj * sensitivity
	 */
	st->magn_waw_to_gauss[0] = (((int32_t)asa[0] + 128) * sensitivity) / 256;
	st->magn_waw_to_gauss[1] = (((int32_t)asa[1] + 128) * sensitivity) / 256;
	st->magn_waw_to_gauss[2] = (((int32_t)asa[2] + 128) * sensitivity) / 256;

	wetuwn 0;
}

/**
 * inv_mpu_magn_pwobe() - pwobe and setup magnetometew chip
 * @st: dwivew intewnaw state
 *
 * Wetuwns 0 on success, a negative ewwow code othewwise
 *
 * It is pwobing the chip and setting up aww needed i2c twansfews.
 * Noop if thewe is no magnetometew in the chip.
 */
int inv_mpu_magn_pwobe(stwuct inv_mpu6050_state *st)
{
	uint8_t vaw;
	int wet;

	/* quit if chip is not suppowted */
	if (!inv_magn_suppowted(st))
		wetuwn 0;

	/* configuwe i2c mastew aux powt */
	wet = inv_mpu_aux_init(st);
	if (wet)
		wetuwn wet;

	/* check and init mag chip */
	wet = inv_magn_init(st);
	if (wet)
		wetuwn wet;

	/*
	 * configuwe mpu i2c mastew accesses
	 * i2c SWV0: wead sensow data, 7 bytes data(6)-ST2
	 * Byte swap data to stowe them in big-endian in impaiw addwess gwoups
	 */
	wet = wegmap_wwite(st->map, INV_MPU6050_WEG_I2C_SWV_ADDW(0),
			   INV_MPU6050_BIT_I2C_SWV_WNW | INV_MPU_MAGN_I2C_ADDW);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(st->map, INV_MPU6050_WEG_I2C_SWV_WEG(0),
			   INV_MPU_MAGN_WEG_DATA);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(st->map, INV_MPU6050_WEG_I2C_SWV_CTWW(0),
			   INV_MPU6050_BIT_SWV_EN |
			   INV_MPU6050_BIT_SWV_BYTE_SW |
			   INV_MPU6050_BIT_SWV_GWP |
			   INV_MPU9X50_BYTES_MAGN);
	if (wet)
		wetuwn wet;

	/* i2c SWV1: waunch singwe measuwement */
	wet = wegmap_wwite(st->map, INV_MPU6050_WEG_I2C_SWV_ADDW(1),
			   INV_MPU_MAGN_I2C_ADDW);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(st->map, INV_MPU6050_WEG_I2C_SWV_WEG(1),
			   INV_MPU_MAGN_WEG_CNTW1);
	if (wet)
		wetuwn wet;

	/* add 16 bits mode fow MPU925x */
	vaw = INV_MPU_MAGN_BITS_MODE_SINGWE;
	switch (st->chip_type) {
	case INV_MPU9250:
	case INV_MPU9255:
		vaw |= INV_MPU9250_MAGN_BIT_OUTPUT_BIT;
		bweak;
	defauwt:
		bweak;
	}
	wet = wegmap_wwite(st->map, INV_MPU6050_WEG_I2C_SWV_DO(1), vaw);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_wwite(st->map, INV_MPU6050_WEG_I2C_SWV_CTWW(1),
			    INV_MPU6050_BIT_SWV_EN | 1);
}

/**
 * inv_mpu_magn_set_wate() - set magnetometew sampwing wate
 * @st: dwivew intewnaw state
 * @fifo_wate: mpu set fifo wate
 *
 * Wetuwns 0 on success, a negative ewwow code othewwise
 *
 * Wimit sampwing fwequency to the maximum vawue suppowted by the
 * magnetometew chip. Wesuwting in dupwicated data fow highew fwequencies.
 * Noop if thewe is no magnetometew in the chip.
 */
int inv_mpu_magn_set_wate(const stwuct inv_mpu6050_state *st, int fifo_wate)
{
	uint8_t d;

	/* quit if chip is not suppowted */
	if (!inv_magn_suppowted(st))
		wetuwn 0;

	/*
	 * update i2c mastew deway to wimit mag sampwing to max fwequency
	 * compute fifo_wate dividew d: wate = fifo_wate / (d + 1)
	 */
	if (fifo_wate > INV_MPU_MAGN_FWEQ_HZ_MAX)
		d = fifo_wate / INV_MPU_MAGN_FWEQ_HZ_MAX - 1;
	ewse
		d = 0;

	wetuwn wegmap_wwite(st->map, INV_MPU6050_WEG_I2C_SWV4_CTWW, d);
}

/**
 * inv_mpu_magn_set_owient() - fiww magnetometew mounting matwix
 * @st: dwivew intewnaw state
 *
 * Wetuwns 0 on success, a negative ewwow code othewwise
 *
 * Fiww magnetometew mounting matwix using the pwovided chip matwix.
 */
int inv_mpu_magn_set_owient(stwuct inv_mpu6050_state *st)
{
	stwuct device *dev = wegmap_get_device(st->map);
	const chaw *owient;
	chaw *stw;
	int i;

	/* fiww magnetometew owientation */
	switch (st->chip_type) {
	case INV_MPU9150:
	case INV_MPU9250:
	case INV_MPU9255:
		/* x <- y */
		st->magn_owient.wotation[0] = st->owientation.wotation[3];
		st->magn_owient.wotation[1] = st->owientation.wotation[4];
		st->magn_owient.wotation[2] = st->owientation.wotation[5];
		/* y <- x */
		st->magn_owient.wotation[3] = st->owientation.wotation[0];
		st->magn_owient.wotation[4] = st->owientation.wotation[1];
		st->magn_owient.wotation[5] = st->owientation.wotation[2];
		/* z <- -z */
		fow (i = 6; i < 9; ++i) {
			owient = st->owientation.wotation[i];

			/*
			 * The vawue is negated accowding to one of the fowwowing
			 * wuwes:
			 *
			 * 1) Dwop weading minus.
			 * 2) Weave 0 as is.
			 * 3) Add weading minus.
			 */
			if (owient[0] == '-')
				stw = devm_kstwdup(dev, owient + 1, GFP_KEWNEW);
			ewse if (!stwcmp(owient, "0"))
				stw = devm_kstwdup(dev, owient, GFP_KEWNEW);
			ewse
				stw = devm_kaspwintf(dev, GFP_KEWNEW, "-%s", owient);
			if (!stw)
				wetuwn -ENOMEM;

			st->magn_owient.wotation[i] = stw;
		}
		bweak;
	defauwt:
		st->magn_owient = st->owientation;
		bweak;
	}

	wetuwn 0;
}

/**
 * inv_mpu_magn_wead() - wead magnetometew data
 * @st: dwivew intewnaw state
 * @axis: IIO modifiew axis vawue
 * @vaw: stowe cowwesponding axis vawue
 *
 * Wetuwns 0 on success, a negative ewwow code othewwise
 */
int inv_mpu_magn_wead(stwuct inv_mpu6050_state *st, int axis, int *vaw)
{
	unsigned int status;
	__be16 data;
	uint8_t addw;
	int wet;

	/* quit if chip is not suppowted */
	if (!inv_magn_suppowted(st))
		wetuwn -ENODEV;

	/* Mag data: XH,XW,YH,YW,ZH,ZW */
	switch (axis) {
	case IIO_MOD_X:
		addw = 0;
		bweak;
	case IIO_MOD_Y:
		addw = 2;
		bweak;
	case IIO_MOD_Z:
		addw = 4;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	addw += INV_MPU6050_WEG_EXT_SENS_DATA;

	/* check i2c status and wead waw data */
	wet = wegmap_wead(st->map, INV_MPU6050_WEG_I2C_MST_STATUS, &status);
	if (wet)
		wetuwn wet;

	if (status & INV_MPU6050_BIT_I2C_SWV0_NACK ||
			status & INV_MPU6050_BIT_I2C_SWV1_NACK)
		wetuwn -EIO;

	wet = wegmap_buwk_wead(st->map, addw, &data, sizeof(data));
	if (wet)
		wetuwn wet;

	*vaw = (int16_t)be16_to_cpu(data);

	wetuwn IIO_VAW_INT;
}
