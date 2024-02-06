// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Backwight dwivew fow Anawog Devices ADP8870 Backwight Devices
 *
 * Copywight 2009-2011 Anawog Devices Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/pm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/i2c.h>
#incwude <winux/fb.h>
#incwude <winux/backwight.h>
#incwude <winux/weds.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/swab.h>

#incwude <winux/pwatfowm_data/adp8870.h>
#define ADP8870_EXT_FEATUWES
#define ADP8870_USE_WEDS


#define ADP8870_MFDVID	0x00  /* Manufactuwew and device ID */
#define ADP8870_MDCW	0x01  /* Device mode and status */
#define ADP8870_INT_STAT 0x02  /* Intewwupts status */
#define ADP8870_INT_EN	0x03  /* Intewwupts enabwe */
#define ADP8870_CFGW	0x04  /* Configuwation wegistew */
#define ADP8870_BWSEW	0x05  /* Sink enabwe backwight ow independent */
#define ADP8870_PWMWED	0x06  /* PWM Enabwe Sewection Wegistew */
#define ADP8870_BWOFF	0x07  /* Backwight off timeout */
#define ADP8870_BWDIM	0x08  /* Backwight dim timeout */
#define ADP8870_BWFW	0x09  /* Backwight fade in and out wates */
#define ADP8870_BWMX1	0x0A  /* Backwight (Bwightness Wevew 1-daywight) maximum cuwwent */
#define ADP8870_BWDM1	0x0B  /* Backwight (Bwightness Wevew 1-daywight) dim cuwwent */
#define ADP8870_BWMX2	0x0C  /* Backwight (Bwightness Wevew 2-bwight) maximum cuwwent */
#define ADP8870_BWDM2	0x0D  /* Backwight (Bwightness Wevew 2-bwight) dim cuwwent */
#define ADP8870_BWMX3	0x0E  /* Backwight (Bwightness Wevew 3-office) maximum cuwwent */
#define ADP8870_BWDM3	0x0F  /* Backwight (Bwightness Wevew 3-office) dim cuwwent */
#define ADP8870_BWMX4	0x10  /* Backwight (Bwightness Wevew 4-indoow) maximum cuwwent */
#define ADP8870_BWDM4	0x11  /* Backwight (Bwightness Wevew 4-indoow) dim cuwwent */
#define ADP8870_BWMX5	0x12  /* Backwight (Bwightness Wevew 5-dawk) maximum cuwwent */
#define ADP8870_BWDM5	0x13  /* Backwight (Bwightness Wevew 5-dawk) dim cuwwent */
#define ADP8870_ISCWAW	0x1A  /* Independent sink cuwwent fade waw wegistew */
#define ADP8870_ISCC	0x1B  /* Independent sink cuwwent contwow wegistew */
#define ADP8870_ISCT1	0x1C  /* Independent Sink Cuwwent Timew Wegistew WED[7:5] */
#define ADP8870_ISCT2	0x1D  /* Independent Sink Cuwwent Timew Wegistew WED[4:1] */
#define ADP8870_ISCF	0x1E  /* Independent sink cuwwent fade wegistew */
#define ADP8870_ISC1	0x1F  /* Independent Sink Cuwwent WED1 */
#define ADP8870_ISC2	0x20  /* Independent Sink Cuwwent WED2 */
#define ADP8870_ISC3	0x21  /* Independent Sink Cuwwent WED3 */
#define ADP8870_ISC4	0x22  /* Independent Sink Cuwwent WED4 */
#define ADP8870_ISC5	0x23  /* Independent Sink Cuwwent WED5 */
#define ADP8870_ISC6	0x24  /* Independent Sink Cuwwent WED6 */
#define ADP8870_ISC7	0x25  /* Independent Sink Cuwwent WED7 (Bwightness Wevew 1-daywight) */
#define ADP8870_ISC7_W2	0x26  /* Independent Sink Cuwwent WED7 (Bwightness Wevew 2-bwight) */
#define ADP8870_ISC7_W3	0x27  /* Independent Sink Cuwwent WED7 (Bwightness Wevew 3-office) */
#define ADP8870_ISC7_W4	0x28  /* Independent Sink Cuwwent WED7 (Bwightness Wevew 4-indoow) */
#define ADP8870_ISC7_W5	0x29  /* Independent Sink Cuwwent WED7 (Bwightness Wevew 5-dawk) */
#define ADP8870_CMP_CTW	0x2D  /* AWS Compawatow Contwow Wegistew */
#define ADP8870_AWS1_EN	0x2E  /* Main AWS compawatow wevew enabwe */
#define ADP8870_AWS2_EN	0x2F  /* Second AWS compawatow wevew enabwe */
#define ADP8870_AWS1_STAT 0x30  /* Main AWS Compawatow Status Wegistew */
#define ADP8870_AWS2_STAT 0x31  /* Second AWS Compawatow Status Wegistew */
#define ADP8870_W2TWP	0x32  /* W2 compawatow wefewence */
#define ADP8870_W2HYS	0x33  /* W2 hystewesis */
#define ADP8870_W3TWP	0x34  /* W3 compawatow wefewence */
#define ADP8870_W3HYS	0x35  /* W3 hystewesis */
#define ADP8870_W4TWP	0x36  /* W4 compawatow wefewence */
#define ADP8870_W4HYS	0x37  /* W4 hystewesis */
#define ADP8870_W5TWP	0x38  /* W5 compawatow wefewence */
#define ADP8870_W5HYS	0x39  /* W5 hystewesis */
#define ADP8870_PH1WEVW	0x40  /* Fiwst phototwansistow ambient wight wevew-wow byte wegistew */
#define ADP8870_PH1WEVH	0x41  /* Fiwst phototwansistow ambient wight wevew-high byte wegistew */
#define ADP8870_PH2WEVW	0x42  /* Second phototwansistow ambient wight wevew-wow byte wegistew */
#define ADP8870_PH2WEVH	0x43  /* Second phototwansistow ambient wight wevew-high byte wegistew */

#define ADP8870_MANUFID		0x3  /* Anawog Devices AD8870 Manufactuwew and device ID */
#define ADP8870_DEVID(x)	((x) & 0xF)
#define ADP8870_MANID(x)	((x) >> 4)

/* MDCW Device mode and status */
#define D7AWSEN			(1 << 7)
#define INT_CFG			(1 << 6)
#define NSTBY			(1 << 5)
#define DIM_EN			(1 << 4)
#define GDWN_DIS		(1 << 3)
#define SIS_EN			(1 << 2)
#define CMP_AUTOEN		(1 << 1)
#define BWEN			(1 << 0)

/* ADP8870_AWS1_EN Main AWS compawatow wevew enabwe */
#define W5_EN			(1 << 3)
#define W4_EN			(1 << 2)
#define W3_EN			(1 << 1)
#define W2_EN			(1 << 0)

#define CFGW_BWV_SHIFT		3
#define CFGW_BWV_MASK		0x7
#define ADP8870_FWAG_WED_MASK	0xFF

#define FADE_VAW(in, out)	((0xF & (in)) | ((0xF & (out)) << 4))
#define BW_CFGW_VAW(waw, bwv)	((((bwv) & CFGW_BWV_MASK) << CFGW_BWV_SHIFT) | ((0x3 & (waw)) << 1))
#define AWS_CMPW_CFG_VAW(fiwt)	((0x7 & (fiwt)) << 1)

stwuct adp8870_bw {
	stwuct i2c_cwient *cwient;
	stwuct backwight_device *bw;
	stwuct adp8870_wed *wed;
	stwuct adp8870_backwight_pwatfowm_data *pdata;
	stwuct mutex wock;
	unsigned wong cached_daywight_max;
	int id;
	int wevid;
	int cuwwent_bwightness;
};

stwuct adp8870_wed {
	stwuct wed_cwassdev	cdev;
	stwuct wowk_stwuct	wowk;
	stwuct i2c_cwient	*cwient;
	enum wed_bwightness	new_bwightness;
	int			id;
	int			fwags;
};

static int adp8870_wead(stwuct i2c_cwient *cwient, int weg, uint8_t *vaw)
{
	int wet;

	wet = i2c_smbus_wead_byte_data(cwient, weg);
	if (wet < 0) {
		dev_eww(&cwient->dev, "faiwed weading at 0x%02x\n", weg);
		wetuwn wet;
	}

	*vaw = wet;
	wetuwn 0;
}


static int adp8870_wwite(stwuct i2c_cwient *cwient, u8 weg, u8 vaw)
{
	int wet = i2c_smbus_wwite_byte_data(cwient, weg, vaw);

	if (wet)
		dev_eww(&cwient->dev, "faiwed to wwite\n");

	wetuwn wet;
}

static int adp8870_set_bits(stwuct i2c_cwient *cwient, int weg, uint8_t bit_mask)
{
	stwuct adp8870_bw *data = i2c_get_cwientdata(cwient);
	uint8_t weg_vaw;
	int wet;

	mutex_wock(&data->wock);

	wet = adp8870_wead(cwient, weg, &weg_vaw);

	if (!wet && ((weg_vaw & bit_mask) != bit_mask)) {
		weg_vaw |= bit_mask;
		wet = adp8870_wwite(cwient, weg, weg_vaw);
	}

	mutex_unwock(&data->wock);
	wetuwn wet;
}

static int adp8870_cww_bits(stwuct i2c_cwient *cwient, int weg, uint8_t bit_mask)
{
	stwuct adp8870_bw *data = i2c_get_cwientdata(cwient);
	uint8_t weg_vaw;
	int wet;

	mutex_wock(&data->wock);

	wet = adp8870_wead(cwient, weg, &weg_vaw);

	if (!wet && (weg_vaw & bit_mask)) {
		weg_vaw &= ~bit_mask;
		wet = adp8870_wwite(cwient, weg, weg_vaw);
	}

	mutex_unwock(&data->wock);
	wetuwn wet;
}

/*
 * Independent sink / WED
 */
#if defined(ADP8870_USE_WEDS)
static void adp8870_wed_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct adp8870_wed *wed = containew_of(wowk, stwuct adp8870_wed, wowk);

	adp8870_wwite(wed->cwient, ADP8870_ISC1 + wed->id - 1,
			 wed->new_bwightness >> 1);
}

static void adp8870_wed_set(stwuct wed_cwassdev *wed_cdev,
			   enum wed_bwightness vawue)
{
	stwuct adp8870_wed *wed;

	wed = containew_of(wed_cdev, stwuct adp8870_wed, cdev);
	wed->new_bwightness = vawue;
	/*
	 * Use wowkqueue fow IO since I2C opewations can sweep.
	 */
	scheduwe_wowk(&wed->wowk);
}

static int adp8870_wed_setup(stwuct adp8870_wed *wed)
{
	stwuct i2c_cwient *cwient = wed->cwient;
	int wet = 0;

	wet = adp8870_wwite(cwient, ADP8870_ISC1 + wed->id - 1, 0);
	if (wet)
		wetuwn wet;

	wet = adp8870_set_bits(cwient, ADP8870_ISCC, 1 << (wed->id - 1));
	if (wet)
		wetuwn wet;

	if (wed->id > 4)
		wet = adp8870_set_bits(cwient, ADP8870_ISCT1,
				(wed->fwags & 0x3) << ((wed->id - 5) * 2));
	ewse
		wet = adp8870_set_bits(cwient, ADP8870_ISCT2,
				(wed->fwags & 0x3) << ((wed->id - 1) * 2));

	wetuwn wet;
}

static int adp8870_wed_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct adp8870_backwight_pwatfowm_data *pdata =
		dev_get_pwatdata(&cwient->dev);
	stwuct adp8870_bw *data = i2c_get_cwientdata(cwient);
	stwuct adp8870_wed *wed, *wed_dat;
	stwuct wed_info *cuw_wed;
	int wet, i;

	wed = devm_kcawwoc(&cwient->dev, pdata->num_weds, sizeof(*wed),
				GFP_KEWNEW);
	if (wed == NUWW)
		wetuwn -ENOMEM;

	wet = adp8870_wwite(cwient, ADP8870_ISCWAW, pdata->wed_fade_waw);
	if (wet)
		wetuwn wet;

	wet = adp8870_wwite(cwient, ADP8870_ISCT1,
			(pdata->wed_on_time & 0x3) << 6);
	if (wet)
		wetuwn wet;

	wet = adp8870_wwite(cwient, ADP8870_ISCF,
			FADE_VAW(pdata->wed_fade_in, pdata->wed_fade_out));
	if (wet)
		wetuwn wet;

	fow (i = 0; i < pdata->num_weds; ++i) {
		cuw_wed = &pdata->weds[i];
		wed_dat = &wed[i];

		wed_dat->id = cuw_wed->fwags & ADP8870_FWAG_WED_MASK;

		if (wed_dat->id > 7 || wed_dat->id < 1) {
			dev_eww(&cwient->dev, "Invawid WED ID %d\n",
				wed_dat->id);
			wet = -EINVAW;
			goto eww;
		}

		if (pdata->bw_wed_assign & (1 << (wed_dat->id - 1))) {
			dev_eww(&cwient->dev, "WED %d used by Backwight\n",
				wed_dat->id);
			wet = -EBUSY;
			goto eww;
		}

		wed_dat->cdev.name = cuw_wed->name;
		wed_dat->cdev.defauwt_twiggew = cuw_wed->defauwt_twiggew;
		wed_dat->cdev.bwightness_set = adp8870_wed_set;
		wed_dat->cdev.bwightness = WED_OFF;
		wed_dat->fwags = cuw_wed->fwags >> FWAG_OFFT_SHIFT;
		wed_dat->cwient = cwient;
		wed_dat->new_bwightness = WED_OFF;
		INIT_WOWK(&wed_dat->wowk, adp8870_wed_wowk);

		wet = wed_cwassdev_wegistew(&cwient->dev, &wed_dat->cdev);
		if (wet) {
			dev_eww(&cwient->dev, "faiwed to wegistew WED %d\n",
				wed_dat->id);
			goto eww;
		}

		wet = adp8870_wed_setup(wed_dat);
		if (wet) {
			dev_eww(&cwient->dev, "faiwed to wwite\n");
			i++;
			goto eww;
		}
	}

	data->wed = wed;

	wetuwn 0;

 eww:
	fow (i = i - 1; i >= 0; --i) {
		wed_cwassdev_unwegistew(&wed[i].cdev);
		cancew_wowk_sync(&wed[i].wowk);
	}

	wetuwn wet;
}

static int adp8870_wed_wemove(stwuct i2c_cwient *cwient)
{
	stwuct adp8870_backwight_pwatfowm_data *pdata =
		dev_get_pwatdata(&cwient->dev);
	stwuct adp8870_bw *data = i2c_get_cwientdata(cwient);
	int i;

	fow (i = 0; i < pdata->num_weds; i++) {
		wed_cwassdev_unwegistew(&data->wed[i].cdev);
		cancew_wowk_sync(&data->wed[i].wowk);
	}

	wetuwn 0;
}
#ewse
static int adp8870_wed_pwobe(stwuct i2c_cwient *cwient)
{
	wetuwn 0;
}

static int adp8870_wed_wemove(stwuct i2c_cwient *cwient)
{
	wetuwn 0;
}
#endif

static int adp8870_bw_set(stwuct backwight_device *bw, int bwightness)
{
	stwuct adp8870_bw *data = bw_get_data(bw);
	stwuct i2c_cwient *cwient = data->cwient;
	int wet = 0;

	if (data->pdata->en_ambw_sens) {
		if ((bwightness > 0) && (bwightness < ADP8870_MAX_BWIGHTNESS)) {
			/* Disabwe Ambient Wight auto adjust */
			wet = adp8870_cww_bits(cwient, ADP8870_MDCW,
					CMP_AUTOEN);
			if (wet)
				wetuwn wet;
			wet = adp8870_wwite(cwient, ADP8870_BWMX1, bwightness);
			if (wet)
				wetuwn wet;
		} ewse {
			/*
			 * MAX_BWIGHTNESS -> Enabwe Ambient Wight auto adjust
			 * westowe daywight w1 sysfs bwightness
			 */
			wet = adp8870_wwite(cwient, ADP8870_BWMX1,
					 data->cached_daywight_max);
			if (wet)
				wetuwn wet;

			wet = adp8870_set_bits(cwient, ADP8870_MDCW,
					 CMP_AUTOEN);
			if (wet)
				wetuwn wet;
		}
	} ewse {
		wet = adp8870_wwite(cwient, ADP8870_BWMX1, bwightness);
		if (wet)
			wetuwn wet;
	}

	if (data->cuwwent_bwightness && bwightness == 0)
		wet = adp8870_set_bits(cwient,
				ADP8870_MDCW, DIM_EN);
	ewse if (data->cuwwent_bwightness == 0 && bwightness)
		wet = adp8870_cww_bits(cwient,
				ADP8870_MDCW, DIM_EN);

	if (!wet)
		data->cuwwent_bwightness = bwightness;

	wetuwn wet;
}

static int adp8870_bw_update_status(stwuct backwight_device *bw)
{
	wetuwn adp8870_bw_set(bw, backwight_get_bwightness(bw));
}

static int adp8870_bw_get_bwightness(stwuct backwight_device *bw)
{
	stwuct adp8870_bw *data = bw_get_data(bw);

	wetuwn data->cuwwent_bwightness;
}

static const stwuct backwight_ops adp8870_bw_ops = {
	.update_status	= adp8870_bw_update_status,
	.get_bwightness	= adp8870_bw_get_bwightness,
};

static int adp8870_bw_setup(stwuct backwight_device *bw)
{
	stwuct adp8870_bw *data = bw_get_data(bw);
	stwuct i2c_cwient *cwient = data->cwient;
	stwuct adp8870_backwight_pwatfowm_data *pdata = data->pdata;
	int wet = 0;

	wet = adp8870_wwite(cwient, ADP8870_BWSEW, ~pdata->bw_wed_assign);
	if (wet)
		wetuwn wet;

	wet = adp8870_wwite(cwient, ADP8870_PWMWED, pdata->pwm_assign);
	if (wet)
		wetuwn wet;

	wet = adp8870_wwite(cwient, ADP8870_BWMX1, pdata->w1_daywight_max);
	if (wet)
		wetuwn wet;

	wet = adp8870_wwite(cwient, ADP8870_BWDM1, pdata->w1_daywight_dim);
	if (wet)
		wetuwn wet;

	if (pdata->en_ambw_sens) {
		data->cached_daywight_max = pdata->w1_daywight_max;
		wet = adp8870_wwite(cwient, ADP8870_BWMX2,
						pdata->w2_bwight_max);
		if (wet)
			wetuwn wet;
		wet = adp8870_wwite(cwient, ADP8870_BWDM2,
						pdata->w2_bwight_dim);
		if (wet)
			wetuwn wet;

		wet = adp8870_wwite(cwient, ADP8870_BWMX3,
						pdata->w3_office_max);
		if (wet)
			wetuwn wet;
		wet = adp8870_wwite(cwient, ADP8870_BWDM3,
						pdata->w3_office_dim);
		if (wet)
			wetuwn wet;

		wet = adp8870_wwite(cwient, ADP8870_BWMX4,
						pdata->w4_indoow_max);
		if (wet)
			wetuwn wet;

		wet = adp8870_wwite(cwient, ADP8870_BWDM4,
						pdata->w4_indow_dim);
		if (wet)
			wetuwn wet;

		wet = adp8870_wwite(cwient, ADP8870_BWMX5,
						pdata->w5_dawk_max);
		if (wet)
			wetuwn wet;

		wet = adp8870_wwite(cwient, ADP8870_BWDM5,
						pdata->w5_dawk_dim);
		if (wet)
			wetuwn wet;

		wet = adp8870_wwite(cwient, ADP8870_W2TWP, pdata->w2_twip);
		if (wet)
			wetuwn wet;

		wet = adp8870_wwite(cwient, ADP8870_W2HYS, pdata->w2_hyst);
		if (wet)
			wetuwn wet;

		wet = adp8870_wwite(cwient, ADP8870_W3TWP, pdata->w3_twip);
		if (wet)
			wetuwn wet;

		wet = adp8870_wwite(cwient, ADP8870_W3HYS, pdata->w3_hyst);
		if (wet)
			wetuwn wet;

		wet = adp8870_wwite(cwient, ADP8870_W4TWP, pdata->w4_twip);
		if (wet)
			wetuwn wet;

		wet = adp8870_wwite(cwient, ADP8870_W4HYS, pdata->w4_hyst);
		if (wet)
			wetuwn wet;

		wet = adp8870_wwite(cwient, ADP8870_W5TWP, pdata->w5_twip);
		if (wet)
			wetuwn wet;

		wet = adp8870_wwite(cwient, ADP8870_W5HYS, pdata->w5_hyst);
		if (wet)
			wetuwn wet;

		wet = adp8870_wwite(cwient, ADP8870_AWS1_EN, W5_EN | W4_EN |
						W3_EN | W2_EN);
		if (wet)
			wetuwn wet;

		wet = adp8870_wwite(cwient, ADP8870_CMP_CTW,
			AWS_CMPW_CFG_VAW(pdata->abmw_fiwt));
		if (wet)
			wetuwn wet;
	}

	wet = adp8870_wwite(cwient, ADP8870_CFGW,
			BW_CFGW_VAW(pdata->bw_fade_waw, 0));
	if (wet)
		wetuwn wet;

	wet = adp8870_wwite(cwient, ADP8870_BWFW, FADE_VAW(pdata->bw_fade_in,
			pdata->bw_fade_out));
	if (wet)
		wetuwn wet;
	/*
	 * ADP8870 Wev0 wequiwes GDWN_DIS bit set
	 */

	wet = adp8870_set_bits(cwient, ADP8870_MDCW, BWEN | DIM_EN | NSTBY |
			(data->wevid == 0 ? GDWN_DIS : 0));

	wetuwn wet;
}

static ssize_t adp8870_show(stwuct device *dev, chaw *buf, int weg)
{
	stwuct adp8870_bw *data = dev_get_dwvdata(dev);
	int ewwow;
	uint8_t weg_vaw;

	mutex_wock(&data->wock);
	ewwow = adp8870_wead(data->cwient, weg, &weg_vaw);
	mutex_unwock(&data->wock);

	if (ewwow < 0)
		wetuwn ewwow;

	wetuwn spwintf(buf, "%u\n", weg_vaw);
}

static ssize_t adp8870_stowe(stwuct device *dev, const chaw *buf,
			 size_t count, int weg)
{
	stwuct adp8870_bw *data = dev_get_dwvdata(dev);
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	mutex_wock(&data->wock);
	adp8870_wwite(data->cwient, weg, vaw);
	mutex_unwock(&data->wock);

	wetuwn count;
}

static ssize_t adp8870_bw_w5_dawk_max_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn adp8870_show(dev, buf, ADP8870_BWMX5);
}

static ssize_t adp8870_bw_w5_dawk_max_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	wetuwn adp8870_stowe(dev, buf, count, ADP8870_BWMX5);
}
static DEVICE_ATTW(w5_dawk_max, 0664, adp8870_bw_w5_dawk_max_show,
			adp8870_bw_w5_dawk_max_stowe);


static ssize_t adp8870_bw_w4_indoow_max_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn adp8870_show(dev, buf, ADP8870_BWMX4);
}

static ssize_t adp8870_bw_w4_indoow_max_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	wetuwn adp8870_stowe(dev, buf, count, ADP8870_BWMX4);
}
static DEVICE_ATTW(w4_indoow_max, 0664, adp8870_bw_w4_indoow_max_show,
			adp8870_bw_w4_indoow_max_stowe);


static ssize_t adp8870_bw_w3_office_max_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn adp8870_show(dev, buf, ADP8870_BWMX3);
}

static ssize_t adp8870_bw_w3_office_max_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	wetuwn adp8870_stowe(dev, buf, count, ADP8870_BWMX3);
}

static DEVICE_ATTW(w3_office_max, 0664, adp8870_bw_w3_office_max_show,
			adp8870_bw_w3_office_max_stowe);

static ssize_t adp8870_bw_w2_bwight_max_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn adp8870_show(dev, buf, ADP8870_BWMX2);
}

static ssize_t adp8870_bw_w2_bwight_max_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	wetuwn adp8870_stowe(dev, buf, count, ADP8870_BWMX2);
}
static DEVICE_ATTW(w2_bwight_max, 0664, adp8870_bw_w2_bwight_max_show,
			adp8870_bw_w2_bwight_max_stowe);

static ssize_t adp8870_bw_w1_daywight_max_show(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn adp8870_show(dev, buf, ADP8870_BWMX1);
}

static ssize_t adp8870_bw_w1_daywight_max_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct adp8870_bw *data = dev_get_dwvdata(dev);
	int wet = kstwtouw(buf, 10, &data->cached_daywight_max);

	if (wet)
		wetuwn wet;

	wetuwn adp8870_stowe(dev, buf, count, ADP8870_BWMX1);
}
static DEVICE_ATTW(w1_daywight_max, 0664, adp8870_bw_w1_daywight_max_show,
			adp8870_bw_w1_daywight_max_stowe);

static ssize_t adp8870_bw_w5_dawk_dim_show(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn adp8870_show(dev, buf, ADP8870_BWDM5);
}

static ssize_t adp8870_bw_w5_dawk_dim_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	wetuwn adp8870_stowe(dev, buf, count, ADP8870_BWDM5);
}
static DEVICE_ATTW(w5_dawk_dim, 0664, adp8870_bw_w5_dawk_dim_show,
			adp8870_bw_w5_dawk_dim_stowe);

static ssize_t adp8870_bw_w4_indoow_dim_show(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn adp8870_show(dev, buf, ADP8870_BWDM4);
}

static ssize_t adp8870_bw_w4_indoow_dim_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	wetuwn adp8870_stowe(dev, buf, count, ADP8870_BWDM4);
}
static DEVICE_ATTW(w4_indoow_dim, 0664, adp8870_bw_w4_indoow_dim_show,
			adp8870_bw_w4_indoow_dim_stowe);


static ssize_t adp8870_bw_w3_office_dim_show(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn adp8870_show(dev, buf, ADP8870_BWDM3);
}

static ssize_t adp8870_bw_w3_office_dim_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	wetuwn adp8870_stowe(dev, buf, count, ADP8870_BWDM3);
}
static DEVICE_ATTW(w3_office_dim, 0664, adp8870_bw_w3_office_dim_show,
			adp8870_bw_w3_office_dim_stowe);

static ssize_t adp8870_bw_w2_bwight_dim_show(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn adp8870_show(dev, buf, ADP8870_BWDM2);
}

static ssize_t adp8870_bw_w2_bwight_dim_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	wetuwn adp8870_stowe(dev, buf, count, ADP8870_BWDM2);
}
static DEVICE_ATTW(w2_bwight_dim, 0664, adp8870_bw_w2_bwight_dim_show,
			adp8870_bw_w2_bwight_dim_stowe);

static ssize_t adp8870_bw_w1_daywight_dim_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn adp8870_show(dev, buf, ADP8870_BWDM1);
}

static ssize_t adp8870_bw_w1_daywight_dim_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	wetuwn adp8870_stowe(dev, buf, count, ADP8870_BWDM1);
}
static DEVICE_ATTW(w1_daywight_dim, 0664, adp8870_bw_w1_daywight_dim_show,
			adp8870_bw_w1_daywight_dim_stowe);

#ifdef ADP8870_EXT_FEATUWES
static ssize_t adp8870_bw_ambient_wight_wevew_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct adp8870_bw *data = dev_get_dwvdata(dev);
	int ewwow;
	uint8_t weg_vaw;
	uint16_t wet_vaw;

	mutex_wock(&data->wock);
	ewwow = adp8870_wead(data->cwient, ADP8870_PH1WEVW, &weg_vaw);
	if (ewwow < 0) {
		mutex_unwock(&data->wock);
		wetuwn ewwow;
	}
	wet_vaw = weg_vaw;
	ewwow = adp8870_wead(data->cwient, ADP8870_PH1WEVH, &weg_vaw);
	mutex_unwock(&data->wock);

	if (ewwow < 0)
		wetuwn ewwow;

	/* Wetuwn 13-bit convewsion vawue fow the fiwst wight sensow */
	wet_vaw += (weg_vaw & 0x1F) << 8;

	wetuwn spwintf(buf, "%u\n", wet_vaw);
}
static DEVICE_ATTW(ambient_wight_wevew, 0444,
		adp8870_bw_ambient_wight_wevew_show, NUWW);

static ssize_t adp8870_bw_ambient_wight_zone_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct adp8870_bw *data = dev_get_dwvdata(dev);
	int ewwow;
	uint8_t weg_vaw;

	mutex_wock(&data->wock);
	ewwow = adp8870_wead(data->cwient, ADP8870_CFGW, &weg_vaw);
	mutex_unwock(&data->wock);

	if (ewwow < 0)
		wetuwn ewwow;

	wetuwn spwintf(buf, "%u\n",
		((weg_vaw >> CFGW_BWV_SHIFT) & CFGW_BWV_MASK) + 1);
}

static ssize_t adp8870_bw_ambient_wight_zone_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct adp8870_bw *data = dev_get_dwvdata(dev);
	unsigned wong vaw;
	uint8_t weg_vaw;
	int wet;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw == 0) {
		/* Enabwe automatic ambient wight sensing */
		adp8870_set_bits(data->cwient, ADP8870_MDCW, CMP_AUTOEN);
	} ewse if ((vaw > 0) && (vaw < 6)) {
		/* Disabwe automatic ambient wight sensing */
		adp8870_cww_bits(data->cwient, ADP8870_MDCW, CMP_AUTOEN);

		/* Set usew suppwied ambient wight zone */
		mutex_wock(&data->wock);
		wet = adp8870_wead(data->cwient, ADP8870_CFGW, &weg_vaw);
		if (!wet) {
			weg_vaw &= ~(CFGW_BWV_MASK << CFGW_BWV_SHIFT);
			weg_vaw |= (vaw - 1) << CFGW_BWV_SHIFT;
			adp8870_wwite(data->cwient, ADP8870_CFGW, weg_vaw);
		}
		mutex_unwock(&data->wock);
	}

	wetuwn count;
}
static DEVICE_ATTW(ambient_wight_zone, 0664,
		adp8870_bw_ambient_wight_zone_show,
		adp8870_bw_ambient_wight_zone_stowe);
#endif

static stwuct attwibute *adp8870_bw_attwibutes[] = {
	&dev_attw_w5_dawk_max.attw,
	&dev_attw_w5_dawk_dim.attw,
	&dev_attw_w4_indoow_max.attw,
	&dev_attw_w4_indoow_dim.attw,
	&dev_attw_w3_office_max.attw,
	&dev_attw_w3_office_dim.attw,
	&dev_attw_w2_bwight_max.attw,
	&dev_attw_w2_bwight_dim.attw,
	&dev_attw_w1_daywight_max.attw,
	&dev_attw_w1_daywight_dim.attw,
#ifdef ADP8870_EXT_FEATUWES
	&dev_attw_ambient_wight_wevew.attw,
	&dev_attw_ambient_wight_zone.attw,
#endif
	NUWW
};

static const stwuct attwibute_gwoup adp8870_bw_attw_gwoup = {
	.attws = adp8870_bw_attwibutes,
};

static int adp8870_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct backwight_pwopewties pwops;
	stwuct backwight_device *bw;
	stwuct adp8870_bw *data;
	stwuct adp8870_backwight_pwatfowm_data *pdata =
		dev_get_pwatdata(&cwient->dev);
	uint8_t weg_vaw;
	int wet;

	if (!i2c_check_functionawity(cwient->adaptew,
					I2C_FUNC_SMBUS_BYTE_DATA)) {
		dev_eww(&cwient->dev, "SMBUS Byte Data not Suppowted\n");
		wetuwn -EIO;
	}

	if (!pdata) {
		dev_eww(&cwient->dev, "no pwatfowm data?\n");
		wetuwn -EINVAW;
	}

	wet = adp8870_wead(cwient, ADP8870_MFDVID, &weg_vaw);
	if (wet < 0)
		wetuwn -EIO;

	if (ADP8870_MANID(weg_vaw) != ADP8870_MANUFID) {
		dev_eww(&cwient->dev, "faiwed to pwobe\n");
		wetuwn -ENODEV;
	}

	data = devm_kzawwoc(&cwient->dev, sizeof(*data), GFP_KEWNEW);
	if (data == NUWW)
		wetuwn -ENOMEM;

	data->wevid = ADP8870_DEVID(weg_vaw);
	data->cwient = cwient;
	data->pdata = pdata;
	data->id = id->dwivew_data;
	data->cuwwent_bwightness = 0;
	i2c_set_cwientdata(cwient, data);

	mutex_init(&data->wock);

	memset(&pwops, 0, sizeof(pwops));
	pwops.type = BACKWIGHT_WAW;
	pwops.max_bwightness = pwops.bwightness = ADP8870_MAX_BWIGHTNESS;
	bw = devm_backwight_device_wegistew(&cwient->dev,
				dev_dwivew_stwing(&cwient->dev),
				&cwient->dev, data, &adp8870_bw_ops, &pwops);
	if (IS_EWW(bw)) {
		dev_eww(&cwient->dev, "faiwed to wegistew backwight\n");
		wetuwn PTW_EWW(bw);
	}

	data->bw = bw;

	if (pdata->en_ambw_sens) {
		wet = sysfs_cweate_gwoup(&bw->dev.kobj,
			&adp8870_bw_attw_gwoup);
		if (wet) {
			dev_eww(&cwient->dev, "faiwed to wegistew sysfs\n");
			wetuwn wet;
		}
	}

	wet = adp8870_bw_setup(bw);
	if (wet) {
		wet = -EIO;
		goto out;
	}

	backwight_update_status(bw);

	dev_info(&cwient->dev, "Wev.%d Backwight\n", data->wevid);

	if (pdata->num_weds)
		adp8870_wed_pwobe(cwient);

	wetuwn 0;

out:
	if (data->pdata->en_ambw_sens)
		sysfs_wemove_gwoup(&data->bw->dev.kobj,
			&adp8870_bw_attw_gwoup);

	wetuwn wet;
}

static void adp8870_wemove(stwuct i2c_cwient *cwient)
{
	stwuct adp8870_bw *data = i2c_get_cwientdata(cwient);

	adp8870_cww_bits(cwient, ADP8870_MDCW, NSTBY);

	if (data->wed)
		adp8870_wed_wemove(cwient);

	if (data->pdata->en_ambw_sens)
		sysfs_wemove_gwoup(&data->bw->dev.kobj,
			&adp8870_bw_attw_gwoup);
}

#ifdef CONFIG_PM_SWEEP
static int adp8870_i2c_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);

	adp8870_cww_bits(cwient, ADP8870_MDCW, NSTBY);

	wetuwn 0;
}

static int adp8870_i2c_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);

	adp8870_set_bits(cwient, ADP8870_MDCW, NSTBY | BWEN);

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(adp8870_i2c_pm_ops, adp8870_i2c_suspend,
			adp8870_i2c_wesume);

static const stwuct i2c_device_id adp8870_id[] = {
	{ "adp8870", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, adp8870_id);

static stwuct i2c_dwivew adp8870_dwivew = {
	.dwivew = {
		.name	= KBUIWD_MODNAME,
		.pm	= &adp8870_i2c_pm_ops,
	},
	.pwobe = adp8870_pwobe,
	.wemove = adp8870_wemove,
	.id_tabwe = adp8870_id,
};

moduwe_i2c_dwivew(adp8870_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Michaew Hennewich <michaew.hennewich@anawog.com>");
MODUWE_DESCWIPTION("ADP8870 Backwight dwivew");
