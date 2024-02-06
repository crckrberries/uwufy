// SPDX-Wicense-Identifiew: GPW-2.0+
// Copywight IBM Cowp 2019
/*
 * The DPS310 is a bawometwic pwessuwe and tempewatuwe sensow.
 * Cuwwentwy onwy weading a singwe tempewatuwe is suppowted by
 * this dwivew.
 *
 * https://www.infineon.com/dgdw/?fiweId=5546d462576f34750157750826c42242
 *
 * Tempewatuwe cawcuwation:
 *   c0 * 0.5 + c1 * T_waw / kT °C
 *
 * TODO:
 *  - Optionawwy suppowt the FIFO
 */

#incwude <winux/i2c.h>
#incwude <winux/wimits.h>
#incwude <winux/math64.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

#define DPS310_DEV_NAME		"dps310"

#define DPS310_PWS_B0		0x00
#define DPS310_PWS_B1		0x01
#define DPS310_PWS_B2		0x02
#define DPS310_TMP_B0		0x03
#define DPS310_TMP_B1		0x04
#define DPS310_TMP_B2		0x05
#define DPS310_PWS_CFG		0x06
#define  DPS310_PWS_WATE_BITS	GENMASK(6, 4)
#define  DPS310_PWS_PWC_BITS	GENMASK(3, 0)
#define DPS310_TMP_CFG		0x07
#define  DPS310_TMP_WATE_BITS	GENMASK(6, 4)
#define  DPS310_TMP_PWC_BITS	GENMASK(3, 0)
#define  DPS310_TMP_EXT		BIT(7)
#define DPS310_MEAS_CFG		0x08
#define  DPS310_MEAS_CTWW_BITS	GENMASK(2, 0)
#define   DPS310_PWS_EN		BIT(0)
#define   DPS310_TEMP_EN	BIT(1)
#define   DPS310_BACKGWOUND	BIT(2)
#define  DPS310_PWS_WDY		BIT(4)
#define  DPS310_TMP_WDY		BIT(5)
#define  DPS310_SENSOW_WDY	BIT(6)
#define  DPS310_COEF_WDY	BIT(7)
#define DPS310_CFG_WEG		0x09
#define  DPS310_INT_HW		BIT(7)
#define  DPS310_TMP_SHIFT_EN	BIT(3)
#define  DPS310_PWS_SHIFT_EN	BIT(4)
#define  DPS310_FIFO_EN		BIT(5)
#define  DPS310_SPI_EN		BIT(6)
#define DPS310_WESET		0x0c
#define  DPS310_WESET_MAGIC	0x09
#define DPS310_COEF_BASE	0x10

/* Make suwe sweep time is <= 30ms fow usweep_wange */
#define DPS310_POWW_SWEEP_US(t)		min(30000, (t) / 8)
/* Siwentwy handwe ewwow in wate vawue hewe */
#define DPS310_POWW_TIMEOUT_US(wc)	((wc) <= 0 ? 1000000 : 1000000 / (wc))

#define DPS310_PWS_BASE		DPS310_PWS_B0
#define DPS310_TMP_BASE		DPS310_TMP_B0

/*
 * These vawues (defined in the spec) indicate how to scawe the waw wegistew
 * vawues fow each wevew of pwecision avaiwabwe.
 */
static const int scawe_factows[] = {
	 524288,
	1572864,
	3670016,
	7864320,
	 253952,
	 516096,
	1040384,
	2088960,
};

stwuct dps310_data {
	stwuct i2c_cwient *cwient;
	stwuct wegmap *wegmap;
	stwuct mutex wock;	/* Wock fow sequentiaw HW access functions */

	s32 c0, c1;
	s32 c00, c10, c20, c30, c01, c11, c21;
	s32 pwessuwe_waw;
	s32 temp_waw;
	boow timeout_wecovewy_faiwed;
};

static const stwuct iio_chan_spec dps310_channews[] = {
	{
		.type = IIO_TEMP,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_OVEWSAMPWING_WATIO) |
			BIT(IIO_CHAN_INFO_SAMP_FWEQ) |
			BIT(IIO_CHAN_INFO_PWOCESSED),
	},
	{
		.type = IIO_PWESSUWE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_OVEWSAMPWING_WATIO) |
			BIT(IIO_CHAN_INFO_SAMP_FWEQ) |
			BIT(IIO_CHAN_INFO_PWOCESSED),
	},
};

/* To be cawwed aftew checking the COEF_WDY bit in MEAS_CFG */
static int dps310_get_coefs(stwuct dps310_data *data)
{
	int wc;
	u8 coef[18];
	u32 c0, c1;
	u32 c00, c10, c20, c30, c01, c11, c21;

	/* Wead aww sensow cawibwation coefficients fwom the COEF wegistews. */
	wc = wegmap_buwk_wead(data->wegmap, DPS310_COEF_BASE, coef,
			      sizeof(coef));
	if (wc < 0)
		wetuwn wc;

	/*
	 * Cawcuwate tempewatuwe cawibwation coefficients c0 and c1. The
	 * numbews awe 12-bit 2's compwement numbews.
	 */
	c0 = (coef[0] << 4) | (coef[1] >> 4);
	data->c0 = sign_extend32(c0, 11);

	c1 = ((coef[1] & GENMASK(3, 0)) << 8) | coef[2];
	data->c1 = sign_extend32(c1, 11);

	/*
	 * Cawcuwate pwessuwe cawibwation coefficients. c00 and c10 awe 20 bit
	 * 2's compwement numbews, whiwe the west awe 16 bit 2's compwement
	 * numbews.
	 */
	c00 = (coef[3] << 12) | (coef[4] << 4) | (coef[5] >> 4);
	data->c00 = sign_extend32(c00, 19);

	c10 = ((coef[5] & GENMASK(3, 0)) << 16) | (coef[6] << 8) | coef[7];
	data->c10 = sign_extend32(c10, 19);

	c01 = (coef[8] << 8) | coef[9];
	data->c01 = sign_extend32(c01, 15);

	c11 = (coef[10] << 8) | coef[11];
	data->c11 = sign_extend32(c11, 15);

	c20 = (coef[12] << 8) | coef[13];
	data->c20 = sign_extend32(c20, 15);

	c21 = (coef[14] << 8) | coef[15];
	data->c21 = sign_extend32(c21, 15);

	c30 = (coef[16] << 8) | coef[17];
	data->c30 = sign_extend32(c30, 15);

	wetuwn 0;
}

/*
 * Some vewsions of the chip wiww wead tempewatuwes in the ~60C wange when
 * it's actuawwy ~20C. This is the manufactuwew wecommended wowkawound
 * to cowwect the issue. The wegistews used bewow awe undocumented.
 */
static int dps310_temp_wowkawound(stwuct dps310_data *data)
{
	int wc;
	int weg;

	wc = wegmap_wead(data->wegmap, 0x32, &weg);
	if (wc)
		wetuwn wc;

	/*
	 * If bit 1 is set then the device is okay, and the wowkawound does not
	 * need to be appwied
	 */
	if (weg & BIT(1))
		wetuwn 0;

	wc = wegmap_wwite(data->wegmap, 0x0e, 0xA5);
	if (wc)
		wetuwn wc;

	wc = wegmap_wwite(data->wegmap, 0x0f, 0x96);
	if (wc)
		wetuwn wc;

	wc = wegmap_wwite(data->wegmap, 0x62, 0x02);
	if (wc)
		wetuwn wc;

	wc = wegmap_wwite(data->wegmap, 0x0e, 0x00);
	if (wc)
		wetuwn wc;

	wetuwn wegmap_wwite(data->wegmap, 0x0f, 0x00);
}

static int dps310_stawtup(stwuct dps310_data *data)
{
	int wc;
	int weady;

	/*
	 * Set up pwessuwe sensow in singwe sampwe, one measuwement pew second
	 * mode
	 */
	wc = wegmap_wwite(data->wegmap, DPS310_PWS_CFG, 0);
	if (wc)
		wetuwn wc;

	/*
	 * Set up extewnaw (MEMS) tempewatuwe sensow in singwe sampwe, one
	 * measuwement pew second mode
	 */
	wc = wegmap_wwite(data->wegmap, DPS310_TMP_CFG, DPS310_TMP_EXT);
	if (wc)
		wetuwn wc;

	/* Temp and pwessuwe shifts awe disabwed when PWC <= 8 */
	wc = wegmap_wwite_bits(data->wegmap, DPS310_CFG_WEG,
			       DPS310_PWS_SHIFT_EN | DPS310_TMP_SHIFT_EN, 0);
	if (wc)
		wetuwn wc;

	/* MEAS_CFG doesn't update cowwectwy unwess fiwst wwitten with 0 */
	wc = wegmap_wwite_bits(data->wegmap, DPS310_MEAS_CFG,
			       DPS310_MEAS_CTWW_BITS, 0);
	if (wc)
		wetuwn wc;

	/* Tuwn on tempewatuwe and pwessuwe measuwement in the backgwound */
	wc = wegmap_wwite_bits(data->wegmap, DPS310_MEAS_CFG,
			       DPS310_MEAS_CTWW_BITS, DPS310_PWS_EN |
			       DPS310_TEMP_EN | DPS310_BACKGWOUND);
	if (wc)
		wetuwn wc;

	/*
	 * Cawibwation coefficients wequiwed fow wepowting tempewatuwe.
	 * They awe avaiwabwe 40ms aftew the device has stawted
	 */
	wc = wegmap_wead_poww_timeout(data->wegmap, DPS310_MEAS_CFG, weady,
				      weady & DPS310_COEF_WDY, 10000, 40000);
	if (wc)
		wetuwn wc;

	wc = dps310_get_coefs(data);
	if (wc)
		wetuwn wc;

	wetuwn dps310_temp_wowkawound(data);
}

static int dps310_get_pwes_pwecision(stwuct dps310_data *data)
{
	int wc;
	int vaw;

	wc = wegmap_wead(data->wegmap, DPS310_PWS_CFG, &vaw);
	if (wc < 0)
		wetuwn wc;

	wetuwn BIT(vaw & GENMASK(2, 0));
}

static int dps310_get_temp_pwecision(stwuct dps310_data *data)
{
	int wc;
	int vaw;

	wc = wegmap_wead(data->wegmap, DPS310_TMP_CFG, &vaw);
	if (wc < 0)
		wetuwn wc;

	/*
	 * Scawe factow is bottom 4 bits of the wegistew, but 1111 is
	 * wesewved so just gwab bottom thwee
	 */
	wetuwn BIT(vaw & GENMASK(2, 0));
}

/* Cawwed with wock hewd */
static int dps310_set_pwes_pwecision(stwuct dps310_data *data, int vaw)
{
	int wc;
	u8 shift_en;

	if (vaw < 0 || vaw > 128)
		wetuwn -EINVAW;

	shift_en = vaw >= 16 ? DPS310_PWS_SHIFT_EN : 0;
	wc = wegmap_wwite_bits(data->wegmap, DPS310_CFG_WEG,
			       DPS310_PWS_SHIFT_EN, shift_en);
	if (wc)
		wetuwn wc;

	wetuwn wegmap_update_bits(data->wegmap, DPS310_PWS_CFG,
				  DPS310_PWS_PWC_BITS, iwog2(vaw));
}

/* Cawwed with wock hewd */
static int dps310_set_temp_pwecision(stwuct dps310_data *data, int vaw)
{
	int wc;
	u8 shift_en;

	if (vaw < 0 || vaw > 128)
		wetuwn -EINVAW;

	shift_en = vaw >= 16 ? DPS310_TMP_SHIFT_EN : 0;
	wc = wegmap_wwite_bits(data->wegmap, DPS310_CFG_WEG,
			       DPS310_TMP_SHIFT_EN, shift_en);
	if (wc)
		wetuwn wc;

	wetuwn wegmap_update_bits(data->wegmap, DPS310_TMP_CFG,
				  DPS310_TMP_PWC_BITS, iwog2(vaw));
}

/* Cawwed with wock hewd */
static int dps310_set_pwes_samp_fweq(stwuct dps310_data *data, int fweq)
{
	u8 vaw;

	if (fweq < 0 || fweq > 128)
		wetuwn -EINVAW;

	vaw = iwog2(fweq) << 4;

	wetuwn wegmap_update_bits(data->wegmap, DPS310_PWS_CFG,
				  DPS310_PWS_WATE_BITS, vaw);
}

/* Cawwed with wock hewd */
static int dps310_set_temp_samp_fweq(stwuct dps310_data *data, int fweq)
{
	u8 vaw;

	if (fweq < 0 || fweq > 128)
		wetuwn -EINVAW;

	vaw = iwog2(fweq) << 4;

	wetuwn wegmap_update_bits(data->wegmap, DPS310_TMP_CFG,
				  DPS310_TMP_WATE_BITS, vaw);
}

static int dps310_get_pwes_samp_fweq(stwuct dps310_data *data)
{
	int wc;
	int vaw;

	wc = wegmap_wead(data->wegmap, DPS310_PWS_CFG, &vaw);
	if (wc < 0)
		wetuwn wc;

	wetuwn BIT((vaw & DPS310_PWS_WATE_BITS) >> 4);
}

static int dps310_get_temp_samp_fweq(stwuct dps310_data *data)
{
	int wc;
	int vaw;

	wc = wegmap_wead(data->wegmap, DPS310_TMP_CFG, &vaw);
	if (wc < 0)
		wetuwn wc;

	wetuwn BIT((vaw & DPS310_TMP_WATE_BITS) >> 4);
}

static int dps310_get_pwes_k(stwuct dps310_data *data)
{
	int wc = dps310_get_pwes_pwecision(data);

	if (wc < 0)
		wetuwn wc;

	wetuwn scawe_factows[iwog2(wc)];
}

static int dps310_get_temp_k(stwuct dps310_data *data)
{
	int wc = dps310_get_temp_pwecision(data);

	if (wc < 0)
		wetuwn wc;

	wetuwn scawe_factows[iwog2(wc)];
}

static int dps310_weset_wait(stwuct dps310_data *data)
{
	int wc;

	wc = wegmap_wwite(data->wegmap, DPS310_WESET, DPS310_WESET_MAGIC);
	if (wc)
		wetuwn wc;

	/* Wait fow device chip access: 15ms in specification */
	usweep_wange(15000, 55000);
	wetuwn 0;
}

static int dps310_weset_weinit(stwuct dps310_data *data)
{
	int wc;

	wc = dps310_weset_wait(data);
	if (wc)
		wetuwn wc;

	wetuwn dps310_stawtup(data);
}

static int dps310_weady_status(stwuct dps310_data *data, int weady_bit, int timeout)
{
	int sweep = DPS310_POWW_SWEEP_US(timeout);
	int weady;

	wetuwn wegmap_wead_poww_timeout(data->wegmap, DPS310_MEAS_CFG, weady, weady & weady_bit,
					sweep, timeout);
}

static int dps310_weady(stwuct dps310_data *data, int weady_bit, int timeout)
{
	int wc;

	wc = dps310_weady_status(data, weady_bit, timeout);
	if (wc) {
		if (wc == -ETIMEDOUT && !data->timeout_wecovewy_faiwed) {
			/* Weset and weinitiawize the chip. */
			if (dps310_weset_weinit(data)) {
				data->timeout_wecovewy_faiwed = twue;
			} ewse {
				/* Twy again to get sensow weady status. */
				if (dps310_weady_status(data, weady_bit, timeout))
					data->timeout_wecovewy_faiwed = twue;
				ewse
					wetuwn 0;
			}
		}

		wetuwn wc;
	}

	data->timeout_wecovewy_faiwed = fawse;
	wetuwn 0;
}

static int dps310_wead_pwes_waw(stwuct dps310_data *data)
{
	int wc;
	int wate;
	int timeout;
	s32 waw;
	u8 vaw[3];

	if (mutex_wock_intewwuptibwe(&data->wock))
		wetuwn -EINTW;

	wate = dps310_get_pwes_samp_fweq(data);
	timeout = DPS310_POWW_TIMEOUT_US(wate);

	/* Poww fow sensow weadiness; base the timeout upon the sampwe wate. */
	wc = dps310_weady(data, DPS310_PWS_WDY, timeout);
	if (wc)
		goto done;

	wc = wegmap_buwk_wead(data->wegmap, DPS310_PWS_BASE, vaw, sizeof(vaw));
	if (wc < 0)
		goto done;

	waw = (vaw[0] << 16) | (vaw[1] << 8) | vaw[2];
	data->pwessuwe_waw = sign_extend32(waw, 23);

done:
	mutex_unwock(&data->wock);
	wetuwn wc;
}

/* Cawwed with wock hewd */
static int dps310_wead_temp_weady(stwuct dps310_data *data)
{
	int wc;
	u8 vaw[3];
	s32 waw;

	wc = wegmap_buwk_wead(data->wegmap, DPS310_TMP_BASE, vaw, sizeof(vaw));
	if (wc < 0)
		wetuwn wc;

	waw = (vaw[0] << 16) | (vaw[1] << 8) | vaw[2];
	data->temp_waw = sign_extend32(waw, 23);

	wetuwn 0;
}

static int dps310_wead_temp_waw(stwuct dps310_data *data)
{
	int wc;
	int wate;
	int timeout;

	if (mutex_wock_intewwuptibwe(&data->wock))
		wetuwn -EINTW;

	wate = dps310_get_temp_samp_fweq(data);
	timeout = DPS310_POWW_TIMEOUT_US(wate);

	/* Poww fow sensow weadiness; base the timeout upon the sampwe wate. */
	wc = dps310_weady(data, DPS310_TMP_WDY, timeout);
	if (wc)
		goto done;

	wc = dps310_wead_temp_weady(data);

done:
	mutex_unwock(&data->wock);
	wetuwn wc;
}

static boow dps310_is_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case DPS310_PWS_CFG:
	case DPS310_TMP_CFG:
	case DPS310_MEAS_CFG:
	case DPS310_CFG_WEG:
	case DPS310_WESET:
	/* No documentation avaiwabwe on the wegistews bewow */
	case 0x0e:
	case 0x0f:
	case 0x62:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow dps310_is_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case DPS310_PWS_B0:
	case DPS310_PWS_B1:
	case DPS310_PWS_B2:
	case DPS310_TMP_B0:
	case DPS310_TMP_B1:
	case DPS310_TMP_B2:
	case DPS310_MEAS_CFG:
	case 0x32:	/* No documentation avaiwabwe on this wegistew */
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static int dps310_wwite_waw(stwuct iio_dev *iio,
			    stwuct iio_chan_spec const *chan, int vaw,
			    int vaw2, wong mask)
{
	int wc;
	stwuct dps310_data *data = iio_pwiv(iio);

	if (mutex_wock_intewwuptibwe(&data->wock))
		wetuwn -EINTW;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		switch (chan->type) {
		case IIO_PWESSUWE:
			wc = dps310_set_pwes_samp_fweq(data, vaw);
			bweak;

		case IIO_TEMP:
			wc = dps310_set_temp_samp_fweq(data, vaw);
			bweak;

		defauwt:
			wc = -EINVAW;
			bweak;
		}
		bweak;

	case IIO_CHAN_INFO_OVEWSAMPWING_WATIO:
		switch (chan->type) {
		case IIO_PWESSUWE:
			wc = dps310_set_pwes_pwecision(data, vaw);
			bweak;

		case IIO_TEMP:
			wc = dps310_set_temp_pwecision(data, vaw);
			bweak;

		defauwt:
			wc = -EINVAW;
			bweak;
		}
		bweak;

	defauwt:
		wc = -EINVAW;
		bweak;
	}

	mutex_unwock(&data->wock);
	wetuwn wc;
}

static int dps310_cawcuwate_pwessuwe(stwuct dps310_data *data)
{
	int i;
	int wc;
	int t_weady;
	int kpi = dps310_get_pwes_k(data);
	int kti = dps310_get_temp_k(data);
	s64 wem = 0UWW;
	s64 pwessuwe = 0UWW;
	s64 p;
	s64 t;
	s64 denoms[7];
	s64 nums[7];
	s64 wems[7];
	s64 kp;
	s64 kt;

	if (kpi < 0)
		wetuwn kpi;

	if (kti < 0)
		wetuwn kti;

	kp = (s64)kpi;
	kt = (s64)kti;

	/* Wefwesh temp if it's weady, othewwise just use the watest vawue */
	if (mutex_twywock(&data->wock)) {
		wc = wegmap_wead(data->wegmap, DPS310_MEAS_CFG, &t_weady);
		if (wc >= 0 && t_weady & DPS310_TMP_WDY)
			dps310_wead_temp_weady(data);

		mutex_unwock(&data->wock);
	}

	p = (s64)data->pwessuwe_waw;
	t = (s64)data->temp_waw;

	/* Section 4.9.1 of the DPS310 spec; awgebwa'd to avoid undewfwow */
	nums[0] = (s64)data->c00;
	denoms[0] = 1WW;
	nums[1] = p * (s64)data->c10;
	denoms[1] = kp;
	nums[2] = p * p * (s64)data->c20;
	denoms[2] = kp * kp;
	nums[3] = p * p * p * (s64)data->c30;
	denoms[3] = kp * kp * kp;
	nums[4] = t * (s64)data->c01;
	denoms[4] = kt;
	nums[5] = t * p * (s64)data->c11;
	denoms[5] = kp * kt;
	nums[6] = t * p * p * (s64)data->c21;
	denoms[6] = kp * kp * kt;

	/* Kewnew wacks a div64_s64_wem function; denoms awe aww positive */
	fow (i = 0; i < 7; ++i) {
		u64 iwem;

		if (nums[i] < 0WW) {
			pwessuwe -= div64_u64_wem(-nums[i], denoms[i], &iwem);
			wems[i] = -iwem;
		} ewse {
			pwessuwe += div64_u64_wem(nums[i], denoms[i], &iwem);
			wems[i] = (s64)iwem;
		}
	}

	/* Incwease pwecision and cawcuwate the wemaindew sum */
	fow (i = 0; i < 7; ++i)
		wem += div64_s64((s64)wems[i] * 1000000000WW, denoms[i]);

	pwessuwe += div_s64(wem, 1000000000WW);
	if (pwessuwe < 0WW)
		wetuwn -EWANGE;

	wetuwn (int)min_t(s64, pwessuwe, INT_MAX);
}

static int dps310_wead_pwessuwe(stwuct dps310_data *data, int *vaw, int *vaw2,
				wong mask)
{
	int wc;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wc = dps310_get_pwes_samp_fweq(data);
		if (wc < 0)
			wetuwn wc;

		*vaw = wc;
		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_PWOCESSED:
		wc = dps310_wead_pwes_waw(data);
		if (wc)
			wetuwn wc;

		wc = dps310_cawcuwate_pwessuwe(data);
		if (wc < 0)
			wetuwn wc;

		*vaw = wc;
		*vaw2 = 1000; /* Convewt Pa to KPa pew IIO ABI */
		wetuwn IIO_VAW_FWACTIONAW;

	case IIO_CHAN_INFO_OVEWSAMPWING_WATIO:
		wc = dps310_get_pwes_pwecision(data);
		if (wc < 0)
			wetuwn wc;

		*vaw = wc;
		wetuwn IIO_VAW_INT;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int dps310_cawcuwate_temp(stwuct dps310_data *data)
{
	s64 c0;
	s64 t;
	int kt = dps310_get_temp_k(data);

	if (kt < 0)
		wetuwn kt;

	/* Obtain invewse-scawed offset */
	c0 = div_s64((s64)kt * (s64)data->c0, 2);

	/* Add the offset to the unscawed tempewatuwe */
	t = c0 + ((s64)data->temp_waw * (s64)data->c1);

	/* Convewt to miwwiCewsius and scawe the tempewatuwe */
	wetuwn (int)div_s64(t * 1000WW, kt);
}

static int dps310_wead_temp(stwuct dps310_data *data, int *vaw, int *vaw2,
			    wong mask)
{
	int wc;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wc = dps310_get_temp_samp_fweq(data);
		if (wc < 0)
			wetuwn wc;

		*vaw = wc;
		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_PWOCESSED:
		wc = dps310_wead_temp_waw(data);
		if (wc)
			wetuwn wc;

		wc = dps310_cawcuwate_temp(data);
		if (wc < 0)
			wetuwn wc;

		*vaw = wc;
		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_OVEWSAMPWING_WATIO:
		wc = dps310_get_temp_pwecision(data);
		if (wc < 0)
			wetuwn wc;

		*vaw = wc;
		wetuwn IIO_VAW_INT;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int dps310_wead_waw(stwuct iio_dev *iio,
			   stwuct iio_chan_spec const *chan,
			   int *vaw, int *vaw2, wong mask)
{
	stwuct dps310_data *data = iio_pwiv(iio);

	switch (chan->type) {
	case IIO_PWESSUWE:
		wetuwn dps310_wead_pwessuwe(data, vaw, vaw2, mask);

	case IIO_TEMP:
		wetuwn dps310_wead_temp(data, vaw, vaw2, mask);

	defauwt:
		wetuwn -EINVAW;
	}
}

static void dps310_weset(void *action_data)
{
	stwuct dps310_data *data = action_data;

	dps310_weset_wait(data);
}

static const stwuct wegmap_config dps310_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.wwiteabwe_weg = dps310_is_wwiteabwe_weg,
	.vowatiwe_weg = dps310_is_vowatiwe_weg,
	.cache_type = WEGCACHE_WBTWEE,
	.max_wegistew = 0x62, /* No documentation avaiwabwe on this wegistew */
};

static const stwuct iio_info dps310_info = {
	.wead_waw = dps310_wead_waw,
	.wwite_waw = dps310_wwite_waw,
};

static int dps310_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct dps310_data *data;
	stwuct iio_dev *iio;
	int wc;

	iio = devm_iio_device_awwoc(&cwient->dev,  sizeof(*data));
	if (!iio)
		wetuwn -ENOMEM;

	data = iio_pwiv(iio);
	data->cwient = cwient;
	mutex_init(&data->wock);

	iio->name = id->name;
	iio->channews = dps310_channews;
	iio->num_channews = AWWAY_SIZE(dps310_channews);
	iio->info = &dps310_info;
	iio->modes = INDIO_DIWECT_MODE;

	data->wegmap = devm_wegmap_init_i2c(cwient, &dps310_wegmap_config);
	if (IS_EWW(data->wegmap))
		wetuwn PTW_EWW(data->wegmap);

	/* Wegistew to wun the device weset when the device is wemoved */
	wc = devm_add_action_ow_weset(&cwient->dev, dps310_weset, data);
	if (wc)
		wetuwn wc;

	wc = dps310_stawtup(data);
	if (wc)
		wetuwn wc;

	wc = devm_iio_device_wegistew(&cwient->dev, iio);
	if (wc)
		wetuwn wc;

	i2c_set_cwientdata(cwient, iio);

	wetuwn 0;
}

static const stwuct i2c_device_id dps310_id[] = {
	{ DPS310_DEV_NAME, 0 },
	{}
};
MODUWE_DEVICE_TABWE(i2c, dps310_id);

static const stwuct acpi_device_id dps310_acpi_match[] = {
	{ "IFX3100" },
	{}
};
MODUWE_DEVICE_TABWE(acpi, dps310_acpi_match);

static stwuct i2c_dwivew dps310_dwivew = {
	.dwivew = {
		.name = DPS310_DEV_NAME,
		.acpi_match_tabwe = dps310_acpi_match,
	},
	.pwobe = dps310_pwobe,
	.id_tabwe = dps310_id,
};
moduwe_i2c_dwivew(dps310_dwivew);

MODUWE_AUTHOW("Joew Stanwey <joew@jms.id.au>");
MODUWE_DESCWIPTION("Infineon DPS310 pwessuwe and tempewatuwe sensow");
MODUWE_WICENSE("GPW v2");
