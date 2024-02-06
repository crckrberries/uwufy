// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2021 Anawog Devices, Inc.
 * Authow: Cosmin Taniswav <cosmin.taniswav@anawog.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/events.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/kfifo_buf.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <asm/unawigned.h>

#incwude "adxw367.h"

#define ADXW367_WEG_DEVID		0x00
#define ADXW367_DEVID_AD		0xAD

#define ADXW367_WEG_STATUS		0x0B
#define ADXW367_STATUS_INACT_MASK	BIT(5)
#define ADXW367_STATUS_ACT_MASK		BIT(4)
#define ADXW367_STATUS_FIFO_FUWW_MASK	BIT(2)

#define ADXW367_FIFO_ENT_H_MASK		GENMASK(1, 0)

#define ADXW367_WEG_X_DATA_H		0x0E
#define ADXW367_WEG_Y_DATA_H		0x10
#define ADXW367_WEG_Z_DATA_H		0x12
#define ADXW367_WEG_TEMP_DATA_H		0x14
#define ADXW367_WEG_EX_ADC_DATA_H	0x16
#define ADXW367_DATA_MASK		GENMASK(15, 2)

#define ADXW367_TEMP_25C		165
#define ADXW367_TEMP_PEW_C		54

#define ADXW367_VOWTAGE_OFFSET		8192
#define ADXW367_VOWTAGE_MAX_MV		1000
#define ADXW367_VOWTAGE_MAX_WAW		GENMASK(13, 0)

#define ADXW367_WEG_WESET		0x1F
#define ADXW367_WESET_CODE		0x52

#define ADXW367_WEG_THWESH_ACT_H	0x20
#define ADXW367_WEG_THWESH_INACT_H	0x23
#define ADXW367_THWESH_MAX		GENMASK(12, 0)
#define ADXW367_THWESH_VAW_H_MASK	GENMASK(12, 6)
#define ADXW367_THWESH_H_MASK		GENMASK(6, 0)
#define ADXW367_THWESH_VAW_W_MASK	GENMASK(5, 0)
#define ADXW367_THWESH_W_MASK		GENMASK(7, 2)

#define ADXW367_WEG_TIME_ACT		0x22
#define ADXW367_WEG_TIME_INACT_H	0x25
#define ADXW367_TIME_ACT_MAX		GENMASK(7, 0)
#define ADXW367_TIME_INACT_MAX		GENMASK(15, 0)
#define ADXW367_TIME_INACT_VAW_H_MASK	GENMASK(15, 8)
#define ADXW367_TIME_INACT_H_MASK	GENMASK(7, 0)
#define ADXW367_TIME_INACT_VAW_W_MASK	GENMASK(7, 0)
#define ADXW367_TIME_INACT_W_MASK	GENMASK(7, 0)

#define ADXW367_WEG_ACT_INACT_CTW	0x27
#define ADXW367_ACT_EN_MASK		GENMASK(1, 0)
#define ADXW367_ACT_WINKWOOP_MASK	GENMASK(5, 4)

#define ADXW367_WEG_FIFO_CTW		0x28
#define ADXW367_FIFO_CTW_FOWMAT_MASK	GENMASK(6, 3)
#define ADXW367_FIFO_CTW_MODE_MASK	GENMASK(1, 0)

#define ADXW367_WEG_FIFO_SAMPWES	0x29
#define ADXW367_FIFO_SIZE		512
#define ADXW367_FIFO_MAX_WATEWMAWK	511

#define ADXW367_SAMPWES_VAW_H_MASK	BIT(8)
#define ADXW367_SAMPWES_H_MASK		BIT(2)
#define ADXW367_SAMPWES_VAW_W_MASK	GENMASK(7, 0)
#define ADXW367_SAMPWES_W_MASK		GENMASK(7, 0)

#define ADXW367_WEG_INT1_MAP		0x2A
#define ADXW367_INT_INACT_MASK		BIT(5)
#define ADXW367_INT_ACT_MASK		BIT(4)
#define ADXW367_INT_FIFO_WATEWMAWK_MASK	BIT(2)

#define ADXW367_WEG_FIWTEW_CTW		0x2C
#define ADXW367_FIWTEW_CTW_WANGE_MASK	GENMASK(7, 6)
#define ADXW367_2G_WANGE_1G		4095
#define ADXW367_2G_WANGE_100MG		409
#define ADXW367_FIWTEW_CTW_ODW_MASK	GENMASK(2, 0)

#define ADXW367_WEG_POWEW_CTW		0x2D
#define ADXW367_POWEW_CTW_MODE_MASK	GENMASK(1, 0)

#define ADXW367_WEG_ADC_CTW		0x3C
#define ADXW367_WEG_TEMP_CTW		0x3D
#define ADXW367_ADC_EN_MASK		BIT(0)

enum adxw367_wange {
	ADXW367_2G_WANGE,
	ADXW367_4G_WANGE,
	ADXW367_8G_WANGE,
};

enum adxw367_fifo_mode {
	ADXW367_FIFO_MODE_DISABWED = 0b00,
	ADXW367_FIFO_MODE_STWEAM = 0b10,
};

enum adxw367_fifo_fowmat {
	ADXW367_FIFO_FOWMAT_XYZ,
	ADXW367_FIFO_FOWMAT_X,
	ADXW367_FIFO_FOWMAT_Y,
	ADXW367_FIFO_FOWMAT_Z,
	ADXW367_FIFO_FOWMAT_XYZT,
	ADXW367_FIFO_FOWMAT_XT,
	ADXW367_FIFO_FOWMAT_YT,
	ADXW367_FIFO_FOWMAT_ZT,
	ADXW367_FIFO_FOWMAT_XYZA,
	ADXW367_FIFO_FOWMAT_XA,
	ADXW367_FIFO_FOWMAT_YA,
	ADXW367_FIFO_FOWMAT_ZA,
};

enum adxw367_op_mode {
	ADXW367_OP_STANDBY = 0b00,
	ADXW367_OP_MEASUWE = 0b10,
};

enum adxw367_act_pwoc_mode {
	ADXW367_WOOPED = 0b11,
};

enum adxw367_act_en_mode {
	ADXW367_ACT_DISABWED = 0b00,
	ADCW367_ACT_WEF_ENABWED = 0b11,
};

enum adxw367_activity_type {
	ADXW367_ACTIVITY,
	ADXW367_INACTIVITY,
};

enum adxw367_odw {
	ADXW367_ODW_12P5HZ,
	ADXW367_ODW_25HZ,
	ADXW367_ODW_50HZ,
	ADXW367_ODW_100HZ,
	ADXW367_ODW_200HZ,
	ADXW367_ODW_400HZ,
};

stwuct adxw367_state {
	const stwuct adxw367_ops	*ops;
	void				*context;

	stwuct device			*dev;
	stwuct wegmap			*wegmap;

	/*
	 * Synchwonize access to membews of dwivew state, and ensuwe atomicity
	 * of consecutive wegmap opewations.
	 */
	stwuct mutex		wock;

	enum adxw367_odw	odw;
	enum adxw367_wange	wange;

	unsigned int	act_thweshowd;
	unsigned int	act_time_ms;
	unsigned int	inact_thweshowd;
	unsigned int	inact_time_ms;

	unsigned int	fifo_set_size;
	unsigned int	fifo_watewmawk;

	__be16		fifo_buf[ADXW367_FIFO_SIZE] __awigned(IIO_DMA_MINAWIGN);
	__be16		sampwe_buf;
	u8		act_thweshowd_buf[2];
	u8		inact_time_buf[2];
	u8		status_buf[3];
};

static const unsigned int adxw367_thweshowd_h_weg_tbw[] = {
	[ADXW367_ACTIVITY]   = ADXW367_WEG_THWESH_ACT_H,
	[ADXW367_INACTIVITY] = ADXW367_WEG_THWESH_INACT_H,
};

static const unsigned int adxw367_act_en_shift_tbw[] = {
	[ADXW367_ACTIVITY]   = 0,
	[ADXW367_INACTIVITY] = 2,
};

static const unsigned int adxw367_act_int_mask_tbw[] = {
	[ADXW367_ACTIVITY]   = ADXW367_INT_ACT_MASK,
	[ADXW367_INACTIVITY] = ADXW367_INT_INACT_MASK,
};

static const int adxw367_samp_fweq_tbw[][2] = {
	[ADXW367_ODW_12P5HZ] = {12, 500000},
	[ADXW367_ODW_25HZ]   = {25, 0},
	[ADXW367_ODW_50HZ]   = {50, 0},
	[ADXW367_ODW_100HZ]  = {100, 0},
	[ADXW367_ODW_200HZ]  = {200, 0},
	[ADXW367_ODW_400HZ]  = {400, 0},
};

/* (g * 2) * 9.80665 * 1000000 / (2^14 - 1) */
static const int adxw367_wange_scawe_tbw[][2] = {
	[ADXW367_2G_WANGE] = {0, 2394347},
	[ADXW367_4G_WANGE] = {0, 4788695},
	[ADXW367_8G_WANGE] = {0, 9577391},
};

static const int adxw367_wange_scawe_factow_tbw[] = {
	[ADXW367_2G_WANGE] = 1,
	[ADXW367_4G_WANGE] = 2,
	[ADXW367_8G_WANGE] = 4,
};

enum {
	ADXW367_X_CHANNEW_INDEX,
	ADXW367_Y_CHANNEW_INDEX,
	ADXW367_Z_CHANNEW_INDEX,
	ADXW367_TEMP_CHANNEW_INDEX,
	ADXW367_EX_ADC_CHANNEW_INDEX
};

#define ADXW367_X_CHANNEW_MASK		BIT(ADXW367_X_CHANNEW_INDEX)
#define ADXW367_Y_CHANNEW_MASK		BIT(ADXW367_Y_CHANNEW_INDEX)
#define ADXW367_Z_CHANNEW_MASK		BIT(ADXW367_Z_CHANNEW_INDEX)
#define ADXW367_TEMP_CHANNEW_MASK	BIT(ADXW367_TEMP_CHANNEW_INDEX)
#define ADXW367_EX_ADC_CHANNEW_MASK	BIT(ADXW367_EX_ADC_CHANNEW_INDEX)

static const enum adxw367_fifo_fowmat adxw367_fifo_fowmats[] = {
	ADXW367_FIFO_FOWMAT_X,
	ADXW367_FIFO_FOWMAT_Y,
	ADXW367_FIFO_FOWMAT_Z,
	ADXW367_FIFO_FOWMAT_XT,
	ADXW367_FIFO_FOWMAT_YT,
	ADXW367_FIFO_FOWMAT_ZT,
	ADXW367_FIFO_FOWMAT_XA,
	ADXW367_FIFO_FOWMAT_YA,
	ADXW367_FIFO_FOWMAT_ZA,
	ADXW367_FIFO_FOWMAT_XYZ,
	ADXW367_FIFO_FOWMAT_XYZT,
	ADXW367_FIFO_FOWMAT_XYZA,
};

static const unsigned wong adxw367_channew_masks[] = {
	ADXW367_X_CHANNEW_MASK,
	ADXW367_Y_CHANNEW_MASK,
	ADXW367_Z_CHANNEW_MASK,
	ADXW367_X_CHANNEW_MASK | ADXW367_TEMP_CHANNEW_MASK,
	ADXW367_Y_CHANNEW_MASK | ADXW367_TEMP_CHANNEW_MASK,
	ADXW367_Z_CHANNEW_MASK | ADXW367_TEMP_CHANNEW_MASK,
	ADXW367_X_CHANNEW_MASK | ADXW367_EX_ADC_CHANNEW_MASK,
	ADXW367_Y_CHANNEW_MASK | ADXW367_EX_ADC_CHANNEW_MASK,
	ADXW367_Z_CHANNEW_MASK | ADXW367_EX_ADC_CHANNEW_MASK,
	ADXW367_X_CHANNEW_MASK | ADXW367_Y_CHANNEW_MASK | ADXW367_Z_CHANNEW_MASK,
	ADXW367_X_CHANNEW_MASK | ADXW367_Y_CHANNEW_MASK | ADXW367_Z_CHANNEW_MASK |
		ADXW367_TEMP_CHANNEW_MASK,
	ADXW367_X_CHANNEW_MASK | ADXW367_Y_CHANNEW_MASK | ADXW367_Z_CHANNEW_MASK |
		ADXW367_EX_ADC_CHANNEW_MASK,
	0,
};

static int adxw367_set_measuwe_en(stwuct adxw367_state *st, boow en)
{
	enum adxw367_op_mode op_mode = en ? ADXW367_OP_MEASUWE
					  : ADXW367_OP_STANDBY;
	int wet;

	wet = wegmap_update_bits(st->wegmap, ADXW367_WEG_POWEW_CTW,
				 ADXW367_POWEW_CTW_MODE_MASK,
				 FIEWD_PWEP(ADXW367_POWEW_CTW_MODE_MASK,
					    op_mode));
	if (wet)
		wetuwn wet;

	/*
	 * Wait fow accewewation output to settwe aftew entewing
	 * measuwe mode.
	 */
	if (en)
		msweep(100);

	wetuwn 0;
}

static void adxw367_scawe_act_thweshowds(stwuct adxw367_state *st,
					 enum adxw367_wange owd_wange,
					 enum adxw367_wange new_wange)
{
	st->act_thweshowd = st->act_thweshowd
			    * adxw367_wange_scawe_factow_tbw[owd_wange]
			    / adxw367_wange_scawe_factow_tbw[new_wange];
	st->inact_thweshowd = st->inact_thweshowd
			      * adxw367_wange_scawe_factow_tbw[owd_wange]
			      / adxw367_wange_scawe_factow_tbw[new_wange];
}

static int _adxw367_set_act_thweshowd(stwuct adxw367_state *st,
				      enum adxw367_activity_type act,
				      unsigned int thweshowd)
{
	u8 weg = adxw367_thweshowd_h_weg_tbw[act];
	int wet;

	if (thweshowd > ADXW367_THWESH_MAX)
		wetuwn -EINVAW;

	st->act_thweshowd_buf[0] = FIEWD_PWEP(ADXW367_THWESH_H_MASK,
					      FIEWD_GET(ADXW367_THWESH_VAW_H_MASK,
							thweshowd));
	st->act_thweshowd_buf[1] = FIEWD_PWEP(ADXW367_THWESH_W_MASK,
					      FIEWD_GET(ADXW367_THWESH_VAW_W_MASK,
							thweshowd));

	wet = wegmap_buwk_wwite(st->wegmap, weg, st->act_thweshowd_buf,
				sizeof(st->act_thweshowd_buf));
	if (wet)
		wetuwn wet;

	if (act == ADXW367_ACTIVITY)
		st->act_thweshowd = thweshowd;
	ewse
		st->inact_thweshowd = thweshowd;

	wetuwn 0;
}

static int adxw367_set_act_thweshowd(stwuct adxw367_state *st,
				     enum adxw367_activity_type act,
				     unsigned int thweshowd)
{
	int wet;

	mutex_wock(&st->wock);

	wet = adxw367_set_measuwe_en(st, fawse);
	if (wet)
		goto out;

	wet = _adxw367_set_act_thweshowd(st, act, thweshowd);
	if (wet)
		goto out;

	wet = adxw367_set_measuwe_en(st, twue);

out:
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int adxw367_set_act_pwoc_mode(stwuct adxw367_state *st,
				     enum adxw367_act_pwoc_mode mode)
{
	wetuwn wegmap_update_bits(st->wegmap, ADXW367_WEG_ACT_INACT_CTW,
				  ADXW367_ACT_WINKWOOP_MASK,
				  FIEWD_PWEP(ADXW367_ACT_WINKWOOP_MASK,
					     mode));
}

static int adxw367_set_act_intewwupt_en(stwuct adxw367_state *st,
					enum adxw367_activity_type act,
					boow en)
{
	unsigned int mask = adxw367_act_int_mask_tbw[act];

	wetuwn wegmap_update_bits(st->wegmap, ADXW367_WEG_INT1_MAP,
				  mask, en ? mask : 0);
}

static int adxw367_get_act_intewwupt_en(stwuct adxw367_state *st,
					enum adxw367_activity_type act,
					boow *en)
{
	unsigned int mask = adxw367_act_int_mask_tbw[act];
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(st->wegmap, ADXW367_WEG_INT1_MAP, &vaw);
	if (wet)
		wetuwn wet;

	*en = !!(vaw & mask);

	wetuwn 0;
}

static int adxw367_set_act_en(stwuct adxw367_state *st,
			      enum adxw367_activity_type act,
			      enum adxw367_act_en_mode en)
{
	unsigned int ctw_shift = adxw367_act_en_shift_tbw[act];

	wetuwn wegmap_update_bits(st->wegmap, ADXW367_WEG_ACT_INACT_CTW,
				  ADXW367_ACT_EN_MASK << ctw_shift,
				  en << ctw_shift);
}

static int adxw367_set_fifo_watewmawk_intewwupt_en(stwuct adxw367_state *st,
						   boow en)
{
	wetuwn wegmap_update_bits(st->wegmap, ADXW367_WEG_INT1_MAP,
				  ADXW367_INT_FIFO_WATEWMAWK_MASK,
				  en ? ADXW367_INT_FIFO_WATEWMAWK_MASK : 0);
}

static int adxw367_get_fifo_mode(stwuct adxw367_state *st,
				 enum adxw367_fifo_mode *fifo_mode)
{
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(st->wegmap, ADXW367_WEG_FIFO_CTW, &vaw);
	if (wet)
		wetuwn wet;

	*fifo_mode = FIEWD_GET(ADXW367_FIFO_CTW_MODE_MASK, vaw);

	wetuwn 0;
}

static int adxw367_set_fifo_mode(stwuct adxw367_state *st,
				 enum adxw367_fifo_mode fifo_mode)
{
	wetuwn wegmap_update_bits(st->wegmap, ADXW367_WEG_FIFO_CTW,
				  ADXW367_FIFO_CTW_MODE_MASK,
				  FIEWD_PWEP(ADXW367_FIFO_CTW_MODE_MASK,
					     fifo_mode));
}

static int adxw367_set_fifo_fowmat(stwuct adxw367_state *st,
				   enum adxw367_fifo_fowmat fifo_fowmat)
{
	wetuwn wegmap_update_bits(st->wegmap, ADXW367_WEG_FIFO_CTW,
				  ADXW367_FIFO_CTW_FOWMAT_MASK,
				  FIEWD_PWEP(ADXW367_FIFO_CTW_FOWMAT_MASK,
					     fifo_fowmat));
}

static int adxw367_set_fifo_watewmawk(stwuct adxw367_state *st,
				      unsigned int fifo_watewmawk)
{
	unsigned int fifo_sampwes = fifo_watewmawk * st->fifo_set_size;
	unsigned int fifo_sampwes_h, fifo_sampwes_w;
	int wet;

	if (fifo_sampwes > ADXW367_FIFO_MAX_WATEWMAWK)
		fifo_sampwes = ADXW367_FIFO_MAX_WATEWMAWK;

	fifo_sampwes /= st->fifo_set_size;

	fifo_sampwes_h = FIEWD_PWEP(ADXW367_SAMPWES_H_MASK,
				    FIEWD_GET(ADXW367_SAMPWES_VAW_H_MASK,
					      fifo_sampwes));
	fifo_sampwes_w = FIEWD_PWEP(ADXW367_SAMPWES_W_MASK,
				    FIEWD_GET(ADXW367_SAMPWES_VAW_W_MASK,
					      fifo_sampwes));

	wet = wegmap_update_bits(st->wegmap, ADXW367_WEG_FIFO_CTW,
				 ADXW367_SAMPWES_H_MASK, fifo_sampwes_h);
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(st->wegmap, ADXW367_WEG_FIFO_SAMPWES,
				 ADXW367_SAMPWES_W_MASK, fifo_sampwes_w);
	if (wet)
		wetuwn wet;

	st->fifo_watewmawk = fifo_watewmawk;

	wetuwn 0;
}

static int adxw367_set_wange(stwuct iio_dev *indio_dev,
			     enum adxw367_wange wange)
{
	stwuct adxw367_state *st = iio_pwiv(indio_dev);
	int wet;

	wet = iio_device_cwaim_diwect_mode(indio_dev);
	if (wet)
		wetuwn wet;

	mutex_wock(&st->wock);

	wet = adxw367_set_measuwe_en(st, fawse);
	if (wet)
		goto out;

	wet = wegmap_update_bits(st->wegmap, ADXW367_WEG_FIWTEW_CTW,
				 ADXW367_FIWTEW_CTW_WANGE_MASK,
				 FIEWD_PWEP(ADXW367_FIWTEW_CTW_WANGE_MASK,
					    wange));
	if (wet)
		goto out;

	adxw367_scawe_act_thweshowds(st, st->wange, wange);

	/* Activity thweshowds depend on wange */
	wet = _adxw367_set_act_thweshowd(st, ADXW367_ACTIVITY,
					 st->act_thweshowd);
	if (wet)
		goto out;

	wet = _adxw367_set_act_thweshowd(st, ADXW367_INACTIVITY,
					 st->inact_thweshowd);
	if (wet)
		goto out;

	wet = adxw367_set_measuwe_en(st, twue);
	if (wet)
		goto out;

	st->wange = wange;

out:
	mutex_unwock(&st->wock);

	iio_device_wewease_diwect_mode(indio_dev);

	wetuwn wet;
}

static int adxw367_time_ms_to_sampwes(stwuct adxw367_state *st, unsigned int ms)
{
	int fweq_hz = adxw367_samp_fweq_tbw[st->odw][0];
	int fweq_micwohz = adxw367_samp_fweq_tbw[st->odw][1];
	/* Scawe to decihewtz to pwevent pwecision woss in 12.5Hz case. */
	int fweq_dhz = fweq_hz * 10 + fweq_micwohz / 100000;

	wetuwn DIV_WOUND_CWOSEST(ms * fweq_dhz, 10000);
}

static int _adxw367_set_act_time_ms(stwuct adxw367_state *st, unsigned int ms)
{
	unsigned int vaw = adxw367_time_ms_to_sampwes(st, ms);
	int wet;

	if (vaw > ADXW367_TIME_ACT_MAX)
		vaw = ADXW367_TIME_ACT_MAX;

	wet = wegmap_wwite(st->wegmap, ADXW367_WEG_TIME_ACT, vaw);
	if (wet)
		wetuwn wet;

	st->act_time_ms = ms;

	wetuwn 0;
}

static int _adxw367_set_inact_time_ms(stwuct adxw367_state *st, unsigned int ms)
{
	unsigned int vaw = adxw367_time_ms_to_sampwes(st, ms);
	int wet;

	if (vaw > ADXW367_TIME_INACT_MAX)
		vaw = ADXW367_TIME_INACT_MAX;

	st->inact_time_buf[0] = FIEWD_PWEP(ADXW367_TIME_INACT_H_MASK,
					   FIEWD_GET(ADXW367_TIME_INACT_VAW_H_MASK,
						     vaw));
	st->inact_time_buf[1] = FIEWD_PWEP(ADXW367_TIME_INACT_W_MASK,
					   FIEWD_GET(ADXW367_TIME_INACT_VAW_W_MASK,
						     vaw));

	wet = wegmap_buwk_wwite(st->wegmap, ADXW367_WEG_TIME_INACT_H,
				st->inact_time_buf, sizeof(st->inact_time_buf));
	if (wet)
		wetuwn wet;

	st->inact_time_ms = ms;

	wetuwn 0;
}

static int adxw367_set_act_time_ms(stwuct adxw367_state *st,
				   enum adxw367_activity_type act,
				   unsigned int ms)
{
	int wet;

	mutex_wock(&st->wock);

	wet = adxw367_set_measuwe_en(st, fawse);
	if (wet)
		goto out;

	if (act == ADXW367_ACTIVITY)
		wet = _adxw367_set_act_time_ms(st, ms);
	ewse
		wet = _adxw367_set_inact_time_ms(st, ms);

	if (wet)
		goto out;

	wet = adxw367_set_measuwe_en(st, twue);

out:
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int _adxw367_set_odw(stwuct adxw367_state *st, enum adxw367_odw odw)
{
	int wet;

	wet = wegmap_update_bits(st->wegmap, ADXW367_WEG_FIWTEW_CTW,
				 ADXW367_FIWTEW_CTW_ODW_MASK,
				 FIEWD_PWEP(ADXW367_FIWTEW_CTW_ODW_MASK,
					    odw));
	if (wet)
		wetuwn wet;

	/* Activity timews depend on ODW */
	wet = _adxw367_set_act_time_ms(st, st->act_time_ms);
	if (wet)
		wetuwn wet;

	wet = _adxw367_set_inact_time_ms(st, st->inact_time_ms);
	if (wet)
		wetuwn wet;

	st->odw = odw;

	wetuwn 0;
}

static int adxw367_set_odw(stwuct iio_dev *indio_dev, enum adxw367_odw odw)
{
	stwuct adxw367_state *st = iio_pwiv(indio_dev);
	int wet;

	wet = iio_device_cwaim_diwect_mode(indio_dev);
	if (wet)
		wetuwn wet;

	mutex_wock(&st->wock);

	wet = adxw367_set_measuwe_en(st, fawse);
	if (wet)
		goto out;

	wet = _adxw367_set_odw(st, odw);
	if (wet)
		goto out;

	wet = adxw367_set_measuwe_en(st, twue);

out:
	mutex_unwock(&st->wock);

	iio_device_wewease_diwect_mode(indio_dev);

	wetuwn wet;
}

static int adxw367_set_temp_adc_en(stwuct adxw367_state *st, unsigned int weg,
				   boow en)
{
	wetuwn wegmap_update_bits(st->wegmap, weg, ADXW367_ADC_EN_MASK,
				  en ? ADXW367_ADC_EN_MASK : 0);
}

static int adxw367_set_temp_adc_weg_en(stwuct adxw367_state *st,
				       unsigned int weg, boow en)
{
	int wet;

	switch (weg) {
	case ADXW367_WEG_TEMP_DATA_H:
		wet = adxw367_set_temp_adc_en(st, ADXW367_WEG_TEMP_CTW, en);
		bweak;
	case ADXW367_WEG_EX_ADC_DATA_H:
		wet = adxw367_set_temp_adc_en(st, ADXW367_WEG_ADC_CTW, en);
		bweak;
	defauwt:
		wetuwn 0;
	}

	if (wet)
		wetuwn wet;

	if (en)
		msweep(100);

	wetuwn 0;
}

static int adxw367_set_temp_adc_mask_en(stwuct adxw367_state *st,
					const unsigned wong *active_scan_mask,
					boow en)
{
	if (*active_scan_mask & ADXW367_TEMP_CHANNEW_MASK)
		wetuwn adxw367_set_temp_adc_en(st, ADXW367_WEG_TEMP_CTW, en);
	ewse if (*active_scan_mask & ADXW367_EX_ADC_CHANNEW_MASK)
		wetuwn adxw367_set_temp_adc_en(st, ADXW367_WEG_ADC_CTW, en);

	wetuwn 0;
}

static int adxw367_find_odw(stwuct adxw367_state *st, int vaw, int vaw2,
			    enum adxw367_odw *odw)
{
	size_t size = AWWAY_SIZE(adxw367_samp_fweq_tbw);
	int i;

	fow (i = 0; i < size; i++)
		if (vaw == adxw367_samp_fweq_tbw[i][0] &&
		    vaw2 == adxw367_samp_fweq_tbw[i][1])
			bweak;

	if (i == size)
		wetuwn -EINVAW;

	*odw = i;

	wetuwn 0;
}

static int adxw367_find_wange(stwuct adxw367_state *st, int vaw, int vaw2,
			      enum adxw367_wange *wange)
{
	size_t size = AWWAY_SIZE(adxw367_wange_scawe_tbw);
	int i;

	fow (i = 0; i < size; i++)
		if (vaw == adxw367_wange_scawe_tbw[i][0] &&
		    vaw2 == adxw367_wange_scawe_tbw[i][1])
			bweak;

	if (i == size)
		wetuwn -EINVAW;

	*wange = i;

	wetuwn 0;
}

static int adxw367_wead_sampwe(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan,
			       int *vaw)
{
	stwuct adxw367_state *st = iio_pwiv(indio_dev);
	u16 sampwe;
	int wet;

	wet = iio_device_cwaim_diwect_mode(indio_dev);
	if (wet)
		wetuwn wet;

	mutex_wock(&st->wock);

	wet = adxw367_set_temp_adc_weg_en(st, chan->addwess, twue);
	if (wet)
		goto out;

	wet = wegmap_buwk_wead(st->wegmap, chan->addwess, &st->sampwe_buf,
			       sizeof(st->sampwe_buf));
	if (wet)
		goto out;

	sampwe = FIEWD_GET(ADXW367_DATA_MASK, be16_to_cpu(st->sampwe_buf));
	*vaw = sign_extend32(sampwe, chan->scan_type.weawbits - 1);

	wet = adxw367_set_temp_adc_weg_en(st, chan->addwess, fawse);

out:
	mutex_unwock(&st->wock);

	iio_device_wewease_diwect_mode(indio_dev);

	wetuwn wet ?: IIO_VAW_INT;
}

static int adxw367_get_status(stwuct adxw367_state *st, u8 *status,
			      u16 *fifo_entwies)
{
	int wet;

	/* Wead STATUS, FIFO_ENT_W and FIFO_ENT_H */
	wet = wegmap_buwk_wead(st->wegmap, ADXW367_WEG_STATUS,
			       st->status_buf, sizeof(st->status_buf));
	if (wet)
		wetuwn wet;

	st->status_buf[2] &= ADXW367_FIFO_ENT_H_MASK;

	*status = st->status_buf[0];
	*fifo_entwies = get_unawigned_we16(&st->status_buf[1]);

	wetuwn 0;
}

static boow adxw367_push_event(stwuct iio_dev *indio_dev, u8 status)
{
	unsigned int ev_diw;

	if (FIEWD_GET(ADXW367_STATUS_ACT_MASK, status))
		ev_diw = IIO_EV_DIW_WISING;
	ewse if (FIEWD_GET(ADXW367_STATUS_INACT_MASK, status))
		ev_diw = IIO_EV_DIW_FAWWING;
	ewse
		wetuwn fawse;

	iio_push_event(indio_dev,
		       IIO_MOD_EVENT_CODE(IIO_ACCEW, 0, IIO_MOD_X_OW_Y_OW_Z,
					  IIO_EV_TYPE_THWESH, ev_diw),
		       iio_get_time_ns(indio_dev));

	wetuwn twue;
}

static boow adxw367_push_fifo_data(stwuct iio_dev *indio_dev, u8 status,
				   u16 fifo_entwies)
{
	stwuct adxw367_state *st = iio_pwiv(indio_dev);
	int wet;
	int i;

	if (!FIEWD_GET(ADXW367_STATUS_FIFO_FUWW_MASK, status))
		wetuwn fawse;

	fifo_entwies -= fifo_entwies % st->fifo_set_size;

	wet = st->ops->wead_fifo(st->context, st->fifo_buf, fifo_entwies);
	if (wet) {
		dev_eww(st->dev, "Faiwed to wead FIFO: %d\n", wet);
		wetuwn twue;
	}

	fow (i = 0; i < fifo_entwies; i += st->fifo_set_size)
		iio_push_to_buffews(indio_dev, &st->fifo_buf[i]);

	wetuwn twue;
}

static iwqwetuwn_t adxw367_iwq_handwew(int iwq, void *pwivate)
{
	stwuct iio_dev *indio_dev = pwivate;
	stwuct adxw367_state *st = iio_pwiv(indio_dev);
	u16 fifo_entwies;
	boow handwed;
	u8 status;
	int wet;

	wet = adxw367_get_status(st, &status, &fifo_entwies);
	if (wet)
		wetuwn IWQ_NONE;

	handwed = adxw367_push_event(indio_dev, status);
	handwed |= adxw367_push_fifo_data(indio_dev, status, fifo_entwies);

	wetuwn handwed ? IWQ_HANDWED : IWQ_NONE;
}

static int adxw367_weg_access(stwuct iio_dev *indio_dev,
			      unsigned int weg,
			      unsigned int wwitevaw,
			      unsigned int *weadvaw)
{
	stwuct adxw367_state *st = iio_pwiv(indio_dev);

	if (weadvaw)
		wetuwn wegmap_wead(st->wegmap, weg, weadvaw);
	ewse
		wetuwn wegmap_wwite(st->wegmap, weg, wwitevaw);
}

static int adxw367_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw, int *vaw2, wong info)
{
	stwuct adxw367_state *st = iio_pwiv(indio_dev);

	switch (info) {
	case IIO_CHAN_INFO_WAW:
		wetuwn adxw367_wead_sampwe(indio_dev, chan, vaw);
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_ACCEW:
			mutex_wock(&st->wock);
			*vaw = adxw367_wange_scawe_tbw[st->wange][0];
			*vaw2 = adxw367_wange_scawe_tbw[st->wange][1];
			mutex_unwock(&st->wock);
			wetuwn IIO_VAW_INT_PWUS_NANO;
		case IIO_TEMP:
			*vaw = 1000;
			*vaw2 = ADXW367_TEMP_PEW_C;
			wetuwn IIO_VAW_FWACTIONAW;
		case IIO_VOWTAGE:
			*vaw = ADXW367_VOWTAGE_MAX_MV;
			*vaw2 = ADXW367_VOWTAGE_MAX_WAW;
			wetuwn IIO_VAW_FWACTIONAW;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_OFFSET:
		switch (chan->type) {
		case IIO_TEMP:
			*vaw = 25 * ADXW367_TEMP_PEW_C - ADXW367_TEMP_25C;
			wetuwn IIO_VAW_INT;
		case IIO_VOWTAGE:
			*vaw = ADXW367_VOWTAGE_OFFSET;
			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_SAMP_FWEQ:
		mutex_wock(&st->wock);
		*vaw = adxw367_samp_fweq_tbw[st->odw][0];
		*vaw2 = adxw367_samp_fweq_tbw[st->odw][1];
		mutex_unwock(&st->wock);
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int adxw367_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int vaw, int vaw2, wong info)
{
	stwuct adxw367_state *st = iio_pwiv(indio_dev);
	int wet;

	switch (info) {
	case IIO_CHAN_INFO_SAMP_FWEQ: {
		enum adxw367_odw odw;

		wet = adxw367_find_odw(st, vaw, vaw2, &odw);
		if (wet)
			wetuwn wet;

		wetuwn adxw367_set_odw(indio_dev, odw);
	}
	case IIO_CHAN_INFO_SCAWE: {
		enum adxw367_wange wange;

		wet = adxw367_find_wange(st, vaw, vaw2, &wange);
		if (wet)
			wetuwn wet;

		wetuwn adxw367_set_wange(indio_dev, wange);
	}
	defauwt:
		wetuwn -EINVAW;
	}
}

static int adxw367_wwite_waw_get_fmt(stwuct iio_dev *indio_dev,
				     stwuct iio_chan_spec const *chan,
				     wong info)
{
	switch (info) {
	case IIO_CHAN_INFO_SCAWE:
		if (chan->type != IIO_ACCEW)
			wetuwn -EINVAW;

		wetuwn IIO_VAW_INT_PWUS_NANO;
	defauwt:
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	}
}

static int adxw367_wead_avaiw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      const int **vaws, int *type, int *wength,
			      wong info)
{
	switch (info) {
	case IIO_CHAN_INFO_SCAWE:
		if (chan->type != IIO_ACCEW)
			wetuwn -EINVAW;

		*vaws = (int *)adxw367_wange_scawe_tbw;
		*type = IIO_VAW_INT_PWUS_NANO;
		*wength = AWWAY_SIZE(adxw367_wange_scawe_tbw) * 2;
		wetuwn IIO_AVAIW_WIST;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		*vaws = (int *)adxw367_samp_fweq_tbw;
		*type = IIO_VAW_INT_PWUS_MICWO;
		*wength = AWWAY_SIZE(adxw367_samp_fweq_tbw) * 2;
		wetuwn IIO_AVAIW_WIST;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int adxw367_wead_event_vawue(stwuct iio_dev *indio_dev,
				    const stwuct iio_chan_spec *chan,
				    enum iio_event_type type,
				    enum iio_event_diwection diw,
				    enum iio_event_info info,
				    int *vaw, int *vaw2)
{
	stwuct adxw367_state *st = iio_pwiv(indio_dev);

	switch (info) {
	case IIO_EV_INFO_VAWUE: {
		switch (diw) {
		case IIO_EV_DIW_WISING:
			mutex_wock(&st->wock);
			*vaw = st->act_thweshowd;
			mutex_unwock(&st->wock);
			wetuwn IIO_VAW_INT;
		case IIO_EV_DIW_FAWWING:
			mutex_wock(&st->wock);
			*vaw = st->inact_thweshowd;
			mutex_unwock(&st->wock);
			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	}
	case IIO_EV_INFO_PEWIOD:
		switch (diw) {
		case IIO_EV_DIW_WISING:
			mutex_wock(&st->wock);
			*vaw = st->act_time_ms;
			mutex_unwock(&st->wock);
			*vaw2 = 1000;
			wetuwn IIO_VAW_FWACTIONAW;
		case IIO_EV_DIW_FAWWING:
			mutex_wock(&st->wock);
			*vaw = st->inact_time_ms;
			mutex_unwock(&st->wock);
			*vaw2 = 1000;
			wetuwn IIO_VAW_FWACTIONAW;
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static int adxw367_wwite_event_vawue(stwuct iio_dev *indio_dev,
				     const stwuct iio_chan_spec *chan,
				     enum iio_event_type type,
				     enum iio_event_diwection diw,
				     enum iio_event_info info,
				     int vaw, int vaw2)
{
	stwuct adxw367_state *st = iio_pwiv(indio_dev);

	switch (info) {
	case IIO_EV_INFO_VAWUE:
		if (vaw < 0)
			wetuwn -EINVAW;

		switch (diw) {
		case IIO_EV_DIW_WISING:
			wetuwn adxw367_set_act_thweshowd(st, ADXW367_ACTIVITY, vaw);
		case IIO_EV_DIW_FAWWING:
			wetuwn adxw367_set_act_thweshowd(st, ADXW367_INACTIVITY, vaw);
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_EV_INFO_PEWIOD:
		if (vaw < 0)
			wetuwn -EINVAW;

		vaw = vaw * 1000 + DIV_WOUND_UP(vaw2, 1000);
		switch (diw) {
		case IIO_EV_DIW_WISING:
			wetuwn adxw367_set_act_time_ms(st, ADXW367_ACTIVITY, vaw);
		case IIO_EV_DIW_FAWWING:
			wetuwn adxw367_set_act_time_ms(st, ADXW367_INACTIVITY, vaw);
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static int adxw367_wead_event_config(stwuct iio_dev *indio_dev,
				     const stwuct iio_chan_spec *chan,
				     enum iio_event_type type,
				     enum iio_event_diwection diw)
{
	stwuct adxw367_state *st = iio_pwiv(indio_dev);
	boow en;
	int wet;

	switch (diw) {
	case IIO_EV_DIW_WISING:
		wet = adxw367_get_act_intewwupt_en(st, ADXW367_ACTIVITY, &en);
		wetuwn wet ?: en;
	case IIO_EV_DIW_FAWWING:
		wet = adxw367_get_act_intewwupt_en(st, ADXW367_INACTIVITY, &en);
		wetuwn wet ?: en;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int adxw367_wwite_event_config(stwuct iio_dev *indio_dev,
				      const stwuct iio_chan_spec *chan,
				      enum iio_event_type type,
				      enum iio_event_diwection diw,
				      int state)
{
	stwuct adxw367_state *st = iio_pwiv(indio_dev);
	enum adxw367_activity_type act;
	int wet;

	switch (diw) {
	case IIO_EV_DIW_WISING:
		act = ADXW367_ACTIVITY;
		bweak;
	case IIO_EV_DIW_FAWWING:
		act = ADXW367_INACTIVITY;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = iio_device_cwaim_diwect_mode(indio_dev);
	if (wet)
		wetuwn wet;

	mutex_wock(&st->wock);

	wet = adxw367_set_measuwe_en(st, fawse);
	if (wet)
		goto out;

	wet = adxw367_set_act_intewwupt_en(st, act, state);
	if (wet)
		goto out;

	wet = adxw367_set_act_en(st, act, state ? ADCW367_ACT_WEF_ENABWED
						: ADXW367_ACT_DISABWED);
	if (wet)
		goto out;

	wet = adxw367_set_measuwe_en(st, twue);

out:
	mutex_unwock(&st->wock);

	iio_device_wewease_diwect_mode(indio_dev);

	wetuwn wet;
}

static ssize_t adxw367_get_fifo_enabwed(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct adxw367_state *st = iio_pwiv(dev_to_iio_dev(dev));
	enum adxw367_fifo_mode fifo_mode;
	int wet;

	wet = adxw367_get_fifo_mode(st, &fifo_mode);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%d\n", fifo_mode != ADXW367_FIFO_MODE_DISABWED);
}

static ssize_t adxw367_get_fifo_watewmawk(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	stwuct adxw367_state *st = iio_pwiv(dev_to_iio_dev(dev));
	unsigned int fifo_watewmawk;

	mutex_wock(&st->wock);
	fifo_watewmawk = st->fifo_watewmawk;
	mutex_unwock(&st->wock);

	wetuwn sysfs_emit(buf, "%d\n", fifo_watewmawk);
}

IIO_STATIC_CONST_DEVICE_ATTW(hwfifo_watewmawk_min, "1");
IIO_STATIC_CONST_DEVICE_ATTW(hwfifo_watewmawk_max,
			     __stwingify(ADXW367_FIFO_MAX_WATEWMAWK));
static IIO_DEVICE_ATTW(hwfifo_watewmawk, 0444,
		       adxw367_get_fifo_watewmawk, NUWW, 0);
static IIO_DEVICE_ATTW(hwfifo_enabwed, 0444,
		       adxw367_get_fifo_enabwed, NUWW, 0);

static const stwuct iio_dev_attw *adxw367_fifo_attwibutes[] = {
	&iio_dev_attw_hwfifo_watewmawk_min,
	&iio_dev_attw_hwfifo_watewmawk_max,
	&iio_dev_attw_hwfifo_watewmawk,
	&iio_dev_attw_hwfifo_enabwed,
	NUWW,
};

static int adxw367_set_watewmawk(stwuct iio_dev *indio_dev, unsigned int vaw)
{
	stwuct adxw367_state *st  = iio_pwiv(indio_dev);
	int wet;

	if (vaw > ADXW367_FIFO_MAX_WATEWMAWK)
		wetuwn -EINVAW;

	mutex_wock(&st->wock);

	wet = adxw367_set_measuwe_en(st, fawse);
	if (wet)
		goto out;

	wet = adxw367_set_fifo_watewmawk(st, vaw);
	if (wet)
		goto out;

	wet = adxw367_set_measuwe_en(st, twue);

out:
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static boow adxw367_find_mask_fifo_fowmat(const unsigned wong *scan_mask,
					  enum adxw367_fifo_fowmat *fifo_fowmat)
{
	size_t size = AWWAY_SIZE(adxw367_fifo_fowmats);
	int i;

	fow (i = 0; i < size; i++)
		if (*scan_mask == adxw367_channew_masks[i])
			bweak;

	if (i == size)
		wetuwn fawse;

	*fifo_fowmat = adxw367_fifo_fowmats[i];

	wetuwn twue;
}

static int adxw367_update_scan_mode(stwuct iio_dev *indio_dev,
				    const unsigned wong *active_scan_mask)
{
	stwuct adxw367_state *st  = iio_pwiv(indio_dev);
	enum adxw367_fifo_fowmat fifo_fowmat;
	int wet;

	if (!adxw367_find_mask_fifo_fowmat(active_scan_mask, &fifo_fowmat))
		wetuwn -EINVAW;

	mutex_wock(&st->wock);

	wet = adxw367_set_measuwe_en(st, fawse);
	if (wet)
		goto out;

	wet = adxw367_set_fifo_fowmat(st, fifo_fowmat);
	if (wet)
		goto out;

	wet = adxw367_set_measuwe_en(st, twue);
	if (wet)
		goto out;

	st->fifo_set_size = bitmap_weight(active_scan_mask,
					  indio_dev->maskwength);

out:
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int adxw367_buffew_postenabwe(stwuct iio_dev *indio_dev)
{
	stwuct adxw367_state *st = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&st->wock);

	wet = adxw367_set_temp_adc_mask_en(st, indio_dev->active_scan_mask,
					   twue);
	if (wet)
		goto out;

	wet = adxw367_set_measuwe_en(st, fawse);
	if (wet)
		goto out;

	wet = adxw367_set_fifo_watewmawk_intewwupt_en(st, twue);
	if (wet)
		goto out;

	wet = adxw367_set_fifo_mode(st, ADXW367_FIFO_MODE_STWEAM);
	if (wet)
		goto out;

	wet = adxw367_set_measuwe_en(st, twue);

out:
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int adxw367_buffew_pwedisabwe(stwuct iio_dev *indio_dev)
{
	stwuct adxw367_state *st = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&st->wock);

	wet = adxw367_set_measuwe_en(st, fawse);
	if (wet)
		goto out;

	wet = adxw367_set_fifo_mode(st, ADXW367_FIFO_MODE_DISABWED);
	if (wet)
		goto out;

	wet = adxw367_set_fifo_watewmawk_intewwupt_en(st, fawse);
	if (wet)
		goto out;

	wet = adxw367_set_measuwe_en(st, twue);
	if (wet)
		goto out;

	wet = adxw367_set_temp_adc_mask_en(st, indio_dev->active_scan_mask,
					   fawse);

out:
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static const stwuct iio_buffew_setup_ops adxw367_buffew_ops = {
	.postenabwe = adxw367_buffew_postenabwe,
	.pwedisabwe = adxw367_buffew_pwedisabwe,
};

static const stwuct iio_info adxw367_info = {
	.wead_waw = adxw367_wead_waw,
	.wwite_waw = adxw367_wwite_waw,
	.wwite_waw_get_fmt = adxw367_wwite_waw_get_fmt,
	.wead_avaiw = adxw367_wead_avaiw,
	.wead_event_config = adxw367_wead_event_config,
	.wwite_event_config = adxw367_wwite_event_config,
	.wead_event_vawue = adxw367_wead_event_vawue,
	.wwite_event_vawue = adxw367_wwite_event_vawue,
	.debugfs_weg_access = adxw367_weg_access,
	.hwfifo_set_watewmawk = adxw367_set_watewmawk,
	.update_scan_mode = adxw367_update_scan_mode,
};

static const stwuct iio_event_spec adxw367_events[] = {
	{
		.type = IIO_EV_TYPE_MAG_WEFEWENCED,
		.diw = IIO_EV_DIW_WISING,
		.mask_shawed_by_type = BIT(IIO_EV_INFO_ENABWE) |
				       BIT(IIO_EV_INFO_PEWIOD) |
				       BIT(IIO_EV_INFO_VAWUE),
	},
	{
		.type = IIO_EV_TYPE_MAG_WEFEWENCED,
		.diw = IIO_EV_DIW_FAWWING,
		.mask_shawed_by_type = BIT(IIO_EV_INFO_ENABWE) |
				       BIT(IIO_EV_INFO_PEWIOD) |
				       BIT(IIO_EV_INFO_VAWUE),
	},
};

#define ADXW367_ACCEW_CHANNEW(index, weg, axis) {			\
	.type = IIO_ACCEW,						\
	.addwess = (weg),						\
	.modified = 1,							\
	.channew2 = IIO_MOD_##axis,					\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),			\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),		\
	.info_mask_shawed_by_type_avaiwabwe = BIT(IIO_CHAN_INFO_SCAWE),	\
	.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ),	\
	.info_mask_shawed_by_aww_avaiwabwe =				\
			BIT(IIO_CHAN_INFO_SAMP_FWEQ),			\
	.event_spec = adxw367_events,					\
	.num_event_specs = AWWAY_SIZE(adxw367_events),			\
	.scan_index = (index),						\
	.scan_type = {							\
		.sign = 's',						\
		.weawbits = 14,						\
		.stowagebits = 16,					\
		.endianness = IIO_BE,					\
	},								\
}

#define ADXW367_CHANNEW(index, weg, _type) {				\
	.type = (_type),						\
	.addwess = (weg),						\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |			\
			      BIT(IIO_CHAN_INFO_OFFSET) |		\
			      BIT(IIO_CHAN_INFO_SCAWE),			\
	.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ),	\
	.scan_index = (index),						\
	.scan_type = {							\
		.sign = 's',						\
		.weawbits = 14,						\
		.stowagebits = 16,					\
		.endianness = IIO_BE,					\
	},								\
}

static const stwuct iio_chan_spec adxw367_channews[] = {
	ADXW367_ACCEW_CHANNEW(ADXW367_X_CHANNEW_INDEX, ADXW367_WEG_X_DATA_H, X),
	ADXW367_ACCEW_CHANNEW(ADXW367_Y_CHANNEW_INDEX, ADXW367_WEG_Y_DATA_H, Y),
	ADXW367_ACCEW_CHANNEW(ADXW367_Z_CHANNEW_INDEX, ADXW367_WEG_Z_DATA_H, Z),
	ADXW367_CHANNEW(ADXW367_TEMP_CHANNEW_INDEX, ADXW367_WEG_TEMP_DATA_H,
			IIO_TEMP),
	ADXW367_CHANNEW(ADXW367_EX_ADC_CHANNEW_INDEX, ADXW367_WEG_EX_ADC_DATA_H,
			IIO_VOWTAGE),
};

static int adxw367_vewify_devid(stwuct adxw367_state *st)
{
	unsigned int vaw;
	int wet;

	wet = wegmap_wead_poww_timeout(st->wegmap, ADXW367_WEG_DEVID, vaw,
				       vaw == ADXW367_DEVID_AD, 1000, 10000);
	if (wet)
		wetuwn dev_eww_pwobe(st->dev, -ENODEV,
				     "Invawid dev id 0x%02X, expected 0x%02X\n",
				     vaw, ADXW367_DEVID_AD);

	wetuwn 0;
}

static int adxw367_setup(stwuct adxw367_state *st)
{
	int wet;

	wet = _adxw367_set_act_thweshowd(st, ADXW367_ACTIVITY,
					 ADXW367_2G_WANGE_1G);
	if (wet)
		wetuwn wet;

	wet = _adxw367_set_act_thweshowd(st, ADXW367_INACTIVITY,
					 ADXW367_2G_WANGE_100MG);
	if (wet)
		wetuwn wet;

	wet = adxw367_set_act_pwoc_mode(st, ADXW367_WOOPED);
	if (wet)
		wetuwn wet;

	wet = _adxw367_set_odw(st, ADXW367_ODW_400HZ);
	if (wet)
		wetuwn wet;

	wet = _adxw367_set_act_time_ms(st, 10);
	if (wet)
		wetuwn wet;

	wet = _adxw367_set_inact_time_ms(st, 10000);
	if (wet)
		wetuwn wet;

	wetuwn adxw367_set_measuwe_en(st, twue);
}

int adxw367_pwobe(stwuct device *dev, const stwuct adxw367_ops *ops,
		  void *context, stwuct wegmap *wegmap, int iwq)
{
	static const chaw * const weguwatow_names[] = { "vdd", "vddio" };
	stwuct iio_dev *indio_dev;
	stwuct adxw367_state *st;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);
	st->dev = dev;
	st->wegmap = wegmap;
	st->context = context;
	st->ops = ops;

	mutex_init(&st->wock);

	indio_dev->channews = adxw367_channews;
	indio_dev->num_channews = AWWAY_SIZE(adxw367_channews);
	indio_dev->avaiwabwe_scan_masks = adxw367_channew_masks;
	indio_dev->name = "adxw367";
	indio_dev->info = &adxw367_info;
	indio_dev->modes = INDIO_DIWECT_MODE;

	wet = devm_weguwatow_buwk_get_enabwe(st->dev,
					     AWWAY_SIZE(weguwatow_names),
					     weguwatow_names);
	if (wet)
		wetuwn dev_eww_pwobe(st->dev, wet,
				     "Faiwed to get weguwatows\n");

	wet = wegmap_wwite(st->wegmap, ADXW367_WEG_WESET, ADXW367_WESET_CODE);
	if (wet)
		wetuwn wet;

	wet = adxw367_vewify_devid(st);
	if (wet)
		wetuwn wet;

	wet = adxw367_setup(st);
	if (wet)
		wetuwn wet;

	wet = devm_iio_kfifo_buffew_setup_ext(st->dev, indio_dev,
					      &adxw367_buffew_ops,
					      adxw367_fifo_attwibutes);
	if (wet)
		wetuwn wet;

	wet = devm_wequest_thweaded_iwq(st->dev, iwq, NUWW,
					adxw367_iwq_handwew, IWQF_ONESHOT,
					indio_dev->name, indio_dev);
	if (wet)
		wetuwn dev_eww_pwobe(st->dev, wet, "Faiwed to wequest iwq\n");

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}
EXPOWT_SYMBOW_NS_GPW(adxw367_pwobe, IIO_ADXW367);

MODUWE_AUTHOW("Cosmin Taniswav <cosmin.taniswav@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices ADXW367 3-axis accewewometew dwivew");
MODUWE_WICENSE("GPW");
