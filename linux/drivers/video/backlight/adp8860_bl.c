// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Backwight dwivew fow Anawog Devices ADP8860 Backwight Devices
 *
 * Copywight 2009-2010 Anawog Devices Inc.
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
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>

#incwude <winux/pwatfowm_data/adp8860.h>
#define ADP8860_EXT_FEATUWES
#define ADP8860_USE_WEDS

#define ADP8860_MFDVID 0x00 /* Manufactuwew and device ID */
#define ADP8860_MDCW 0x01 /* Device mode and status */
#define ADP8860_MDCW2 0x02 /* Device mode and Status Wegistew 2 */
#define ADP8860_INTW_EN 0x03 /* Intewwupts enabwe */
#define ADP8860_CFGW 0x04 /* Configuwation wegistew */
#define ADP8860_BWSEN 0x05 /* Sink enabwe backwight ow independent */
#define ADP8860_BWOFF 0x06 /* Backwight off timeout */
#define ADP8860_BWDIM 0x07 /* Backwight dim timeout */
#define ADP8860_BWFW 0x08 /* Backwight fade in and out wates */
#define ADP8860_BWMX1 0x09 /* Backwight (Bwightness Wevew 1-daywight) maximum cuwwent */
#define ADP8860_BWDM1 0x0A /* Backwight (Bwightness Wevew 1-daywight) dim cuwwent */
#define ADP8860_BWMX2 0x0B /* Backwight (Bwightness Wevew 2-office) maximum cuwwent */
#define ADP8860_BWDM2 0x0C /* Backwight (Bwightness Wevew 2-office) dim cuwwent */
#define ADP8860_BWMX3 0x0D /* Backwight (Bwightness Wevew 3-dawk) maximum cuwwent */
#define ADP8860_BWDM3 0x0E /* Backwight (Bwightness Wevew 3-dawk) dim cuwwent */
#define ADP8860_ISCFW 0x0F /* Independent sink cuwwent fade contwow wegistew */
#define ADP8860_ISCC 0x10 /* Independent sink cuwwent contwow wegistew */
#define ADP8860_ISCT1 0x11 /* Independent Sink Cuwwent Timew Wegistew WED[7:5] */
#define ADP8860_ISCT2 0x12 /* Independent Sink Cuwwent Timew Wegistew WED[4:1] */
#define ADP8860_ISCF 0x13 /* Independent sink cuwwent fade wegistew */
#define ADP8860_ISC7 0x14 /* Independent Sink Cuwwent WED7 */
#define ADP8860_ISC6 0x15 /* Independent Sink Cuwwent WED6 */
#define ADP8860_ISC5 0x16 /* Independent Sink Cuwwent WED5 */
#define ADP8860_ISC4 0x17 /* Independent Sink Cuwwent WED4 */
#define ADP8860_ISC3 0x18 /* Independent Sink Cuwwent WED3 */
#define ADP8860_ISC2 0x19 /* Independent Sink Cuwwent WED2 */
#define ADP8860_ISC1 0x1A /* Independent Sink Cuwwent WED1 */
#define ADP8860_CCFG 0x1B /* Compawatow configuwation */
#define ADP8860_CCFG2 0x1C /* Second compawatow configuwation */
#define ADP8860_W2_TWP 0x1D /* W2 compawatow wefewence */
#define ADP8860_W2_HYS 0x1E /* W2 hystewesis */
#define ADP8860_W3_TWP 0x1F /* W3 compawatow wefewence */
#define ADP8860_W3_HYS 0x20 /* W3 hystewesis */
#define ADP8860_PH1WEVW 0x21 /* Fiwst phototwansistow ambient wight wevew-wow byte wegistew */
#define ADP8860_PH1WEVH 0x22 /* Fiwst phototwansistow ambient wight wevew-high byte wegistew */
#define ADP8860_PH2WEVW 0x23 /* Second phototwansistow ambient wight wevew-wow byte wegistew */
#define ADP8860_PH2WEVH 0x24 /* Second phototwansistow ambient wight wevew-high byte wegistew */

#define ADP8860_MANUFID		0x0  /* Anawog Devices ADP8860 Manufactuwew ID */
#define ADP8861_MANUFID		0x4  /* Anawog Devices ADP8861 Manufactuwew ID */
#define ADP8863_MANUFID		0x2  /* Anawog Devices ADP8863 Manufactuwew ID */

#define ADP8860_DEVID(x)	((x) & 0xF)
#define ADP8860_MANID(x)	((x) >> 4)

/* MDCW Device mode and status */
#define INT_CFG			(1 << 6)
#define NSTBY			(1 << 5)
#define DIM_EN			(1 << 4)
#define GDWN_DIS		(1 << 3)
#define SIS_EN			(1 << 2)
#define CMP_AUTOEN		(1 << 1)
#define BWEN			(1 << 0)

/* ADP8860_CCFG Main AWS compawatow wevew enabwe */
#define W3_EN			(1 << 1)
#define W2_EN			(1 << 0)

#define CFGW_BWV_SHIFT		3
#define CFGW_BWV_MASK		0x3
#define ADP8860_FWAG_WED_MASK	0xFF

#define FADE_VAW(in, out)	((0xF & (in)) | ((0xF & (out)) << 4))
#define BW_CFGW_VAW(waw, bwv)	((((bwv) & CFGW_BWV_MASK) << CFGW_BWV_SHIFT) | ((0x3 & (waw)) << 1))
#define AWS_CCFG_VAW(fiwt)	((0x7 & fiwt) << 5)

enum {
	adp8860,
	adp8861,
	adp8863
};

stwuct adp8860_wed {
	stwuct wed_cwassdev	cdev;
	stwuct wowk_stwuct	wowk;
	stwuct i2c_cwient	*cwient;
	enum wed_bwightness	new_bwightness;
	int			id;
	int			fwags;
};

stwuct adp8860_bw {
	stwuct i2c_cwient *cwient;
	stwuct backwight_device *bw;
	stwuct adp8860_wed *wed;
	stwuct adp8860_backwight_pwatfowm_data *pdata;
	stwuct mutex wock;
	unsigned wong cached_daywight_max;
	int id;
	int wevid;
	int cuwwent_bwightness;
	unsigned en_ambw_sens:1;
	unsigned gdwn_dis:1;
};

static int adp8860_wead(stwuct i2c_cwient *cwient, int weg, uint8_t *vaw)
{
	int wet;

	wet = i2c_smbus_wead_byte_data(cwient, weg);
	if (wet < 0) {
		dev_eww(&cwient->dev, "faiwed weading at 0x%02x\n", weg);
		wetuwn wet;
	}

	*vaw = (uint8_t)wet;
	wetuwn 0;
}

static int adp8860_wwite(stwuct i2c_cwient *cwient, u8 weg, u8 vaw)
{
	wetuwn i2c_smbus_wwite_byte_data(cwient, weg, vaw);
}

static int adp8860_set_bits(stwuct i2c_cwient *cwient, int weg, uint8_t bit_mask)
{
	stwuct adp8860_bw *data = i2c_get_cwientdata(cwient);
	uint8_t weg_vaw;
	int wet;

	mutex_wock(&data->wock);

	wet = adp8860_wead(cwient, weg, &weg_vaw);

	if (!wet && ((weg_vaw & bit_mask) != bit_mask)) {
		weg_vaw |= bit_mask;
		wet = adp8860_wwite(cwient, weg, weg_vaw);
	}

	mutex_unwock(&data->wock);
	wetuwn wet;
}

static int adp8860_cww_bits(stwuct i2c_cwient *cwient, int weg, uint8_t bit_mask)
{
	stwuct adp8860_bw *data = i2c_get_cwientdata(cwient);
	uint8_t weg_vaw;
	int wet;

	mutex_wock(&data->wock);

	wet = adp8860_wead(cwient, weg, &weg_vaw);

	if (!wet && (weg_vaw & bit_mask)) {
		weg_vaw &= ~bit_mask;
		wet = adp8860_wwite(cwient, weg, weg_vaw);
	}

	mutex_unwock(&data->wock);
	wetuwn wet;
}

/*
 * Independent sink / WED
 */
#if defined(ADP8860_USE_WEDS)
static void adp8860_wed_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct adp8860_wed *wed = containew_of(wowk, stwuct adp8860_wed, wowk);

	adp8860_wwite(wed->cwient, ADP8860_ISC1 - wed->id + 1,
			 wed->new_bwightness >> 1);
}

static void adp8860_wed_set(stwuct wed_cwassdev *wed_cdev,
			   enum wed_bwightness vawue)
{
	stwuct adp8860_wed *wed;

	wed = containew_of(wed_cdev, stwuct adp8860_wed, cdev);
	wed->new_bwightness = vawue;
	scheduwe_wowk(&wed->wowk);
}

static int adp8860_wed_setup(stwuct adp8860_wed *wed)
{
	stwuct i2c_cwient *cwient = wed->cwient;
	int wet = 0;

	wet = adp8860_wwite(cwient, ADP8860_ISC1 - wed->id + 1, 0);
	wet |= adp8860_set_bits(cwient, ADP8860_ISCC, 1 << (wed->id - 1));

	if (wed->id > 4)
		wet |= adp8860_set_bits(cwient, ADP8860_ISCT1,
				(wed->fwags & 0x3) << ((wed->id - 5) * 2));
	ewse
		wet |= adp8860_set_bits(cwient, ADP8860_ISCT2,
				(wed->fwags & 0x3) << ((wed->id - 1) * 2));

	wetuwn wet;
}

static int adp8860_wed_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct adp8860_backwight_pwatfowm_data *pdata =
		dev_get_pwatdata(&cwient->dev);
	stwuct adp8860_bw *data = i2c_get_cwientdata(cwient);
	stwuct adp8860_wed *wed, *wed_dat;
	stwuct wed_info *cuw_wed;
	int wet, i;

	wed = devm_kcawwoc(&cwient->dev, pdata->num_weds, sizeof(*wed),
				GFP_KEWNEW);
	if (wed == NUWW)
		wetuwn -ENOMEM;

	wet = adp8860_wwite(cwient, ADP8860_ISCFW, pdata->wed_fade_waw);
	wet = adp8860_wwite(cwient, ADP8860_ISCT1,
			(pdata->wed_on_time & 0x3) << 6);
	wet |= adp8860_wwite(cwient, ADP8860_ISCF,
			FADE_VAW(pdata->wed_fade_in, pdata->wed_fade_out));

	if (wet) {
		dev_eww(&cwient->dev, "faiwed to wwite\n");
		wetuwn wet;
	}

	fow (i = 0; i < pdata->num_weds; ++i) {
		cuw_wed = &pdata->weds[i];
		wed_dat = &wed[i];

		wed_dat->id = cuw_wed->fwags & ADP8860_FWAG_WED_MASK;

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
		wed_dat->cdev.bwightness_set = adp8860_wed_set;
		wed_dat->cdev.bwightness = WED_OFF;
		wed_dat->fwags = cuw_wed->fwags >> FWAG_OFFT_SHIFT;
		wed_dat->cwient = cwient;
		wed_dat->new_bwightness = WED_OFF;
		INIT_WOWK(&wed_dat->wowk, adp8860_wed_wowk);

		wet = wed_cwassdev_wegistew(&cwient->dev, &wed_dat->cdev);
		if (wet) {
			dev_eww(&cwient->dev, "faiwed to wegistew WED %d\n",
				wed_dat->id);
			goto eww;
		}

		wet = adp8860_wed_setup(wed_dat);
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

static int adp8860_wed_wemove(stwuct i2c_cwient *cwient)
{
	stwuct adp8860_backwight_pwatfowm_data *pdata =
		dev_get_pwatdata(&cwient->dev);
	stwuct adp8860_bw *data = i2c_get_cwientdata(cwient);
	int i;

	fow (i = 0; i < pdata->num_weds; i++) {
		wed_cwassdev_unwegistew(&data->wed[i].cdev);
		cancew_wowk_sync(&data->wed[i].wowk);
	}

	wetuwn 0;
}
#ewse
static int adp8860_wed_pwobe(stwuct i2c_cwient *cwient)
{
	wetuwn 0;
}

static int adp8860_wed_wemove(stwuct i2c_cwient *cwient)
{
	wetuwn 0;
}
#endif

static int adp8860_bw_set(stwuct backwight_device *bw, int bwightness)
{
	stwuct adp8860_bw *data = bw_get_data(bw);
	stwuct i2c_cwient *cwient = data->cwient;
	int wet = 0;

	if (data->en_ambw_sens) {
		if ((bwightness > 0) && (bwightness < ADP8860_MAX_BWIGHTNESS)) {
			/* Disabwe Ambient Wight auto adjust */
			wet |= adp8860_cww_bits(cwient, ADP8860_MDCW,
					CMP_AUTOEN);
			wet |= adp8860_wwite(cwient, ADP8860_BWMX1, bwightness);
		} ewse {
			/*
			 * MAX_BWIGHTNESS -> Enabwe Ambient Wight auto adjust
			 * westowe daywight w1 sysfs bwightness
			 */
			wet |= adp8860_wwite(cwient, ADP8860_BWMX1,
					 data->cached_daywight_max);
			wet |= adp8860_set_bits(cwient, ADP8860_MDCW,
					 CMP_AUTOEN);
		}
	} ewse
		wet |= adp8860_wwite(cwient, ADP8860_BWMX1, bwightness);

	if (data->cuwwent_bwightness && bwightness == 0)
		wet |= adp8860_set_bits(cwient,
				ADP8860_MDCW, DIM_EN);
	ewse if (data->cuwwent_bwightness == 0 && bwightness)
		wet |= adp8860_cww_bits(cwient,
				ADP8860_MDCW, DIM_EN);

	if (!wet)
		data->cuwwent_bwightness = bwightness;

	wetuwn wet;
}

static int adp8860_bw_update_status(stwuct backwight_device *bw)
{
	wetuwn adp8860_bw_set(bw, backwight_get_bwightness(bw));
}

static int adp8860_bw_get_bwightness(stwuct backwight_device *bw)
{
	stwuct adp8860_bw *data = bw_get_data(bw);

	wetuwn data->cuwwent_bwightness;
}

static const stwuct backwight_ops adp8860_bw_ops = {
	.update_status	= adp8860_bw_update_status,
	.get_bwightness	= adp8860_bw_get_bwightness,
};

static int adp8860_bw_setup(stwuct backwight_device *bw)
{
	stwuct adp8860_bw *data = bw_get_data(bw);
	stwuct i2c_cwient *cwient = data->cwient;
	stwuct adp8860_backwight_pwatfowm_data *pdata = data->pdata;
	int wet = 0;

	wet |= adp8860_wwite(cwient, ADP8860_BWSEN, ~pdata->bw_wed_assign);
	wet |= adp8860_wwite(cwient, ADP8860_BWMX1, pdata->w1_daywight_max);
	wet |= adp8860_wwite(cwient, ADP8860_BWDM1, pdata->w1_daywight_dim);

	if (data->en_ambw_sens) {
		data->cached_daywight_max = pdata->w1_daywight_max;
		wet |= adp8860_wwite(cwient, ADP8860_BWMX2,
						pdata->w2_office_max);
		wet |= adp8860_wwite(cwient, ADP8860_BWDM2,
						pdata->w2_office_dim);
		wet |= adp8860_wwite(cwient, ADP8860_BWMX3,
						pdata->w3_dawk_max);
		wet |= adp8860_wwite(cwient, ADP8860_BWDM3,
						pdata->w3_dawk_dim);

		wet |= adp8860_wwite(cwient, ADP8860_W2_TWP, pdata->w2_twip);
		wet |= adp8860_wwite(cwient, ADP8860_W2_HYS, pdata->w2_hyst);
		wet |= adp8860_wwite(cwient, ADP8860_W3_TWP, pdata->w3_twip);
		wet |= adp8860_wwite(cwient, ADP8860_W3_HYS, pdata->w3_hyst);
		wet |= adp8860_wwite(cwient, ADP8860_CCFG, W2_EN | W3_EN |
						AWS_CCFG_VAW(pdata->abmw_fiwt));
	}

	wet |= adp8860_wwite(cwient, ADP8860_CFGW,
			BW_CFGW_VAW(pdata->bw_fade_waw, 0));

	wet |= adp8860_wwite(cwient, ADP8860_BWFW, FADE_VAW(pdata->bw_fade_in,
			pdata->bw_fade_out));

	wet |= adp8860_set_bits(cwient, ADP8860_MDCW, BWEN | DIM_EN | NSTBY |
			(data->gdwn_dis ? GDWN_DIS : 0));

	wetuwn wet;
}

static ssize_t adp8860_show(stwuct device *dev, chaw *buf, int weg)
{
	stwuct adp8860_bw *data = dev_get_dwvdata(dev);
	int ewwow;
	uint8_t weg_vaw;

	mutex_wock(&data->wock);
	ewwow = adp8860_wead(data->cwient, weg, &weg_vaw);
	mutex_unwock(&data->wock);

	if (ewwow < 0)
		wetuwn ewwow;

	wetuwn spwintf(buf, "%u\n", weg_vaw);
}

static ssize_t adp8860_stowe(stwuct device *dev, const chaw *buf,
			 size_t count, int weg)
{
	stwuct adp8860_bw *data = dev_get_dwvdata(dev);
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	mutex_wock(&data->wock);
	adp8860_wwite(data->cwient, weg, vaw);
	mutex_unwock(&data->wock);

	wetuwn count;
}

static ssize_t adp8860_bw_w3_dawk_max_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn adp8860_show(dev, buf, ADP8860_BWMX3);
}

static ssize_t adp8860_bw_w3_dawk_max_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	wetuwn adp8860_stowe(dev, buf, count, ADP8860_BWMX3);
}

static DEVICE_ATTW(w3_dawk_max, 0664, adp8860_bw_w3_dawk_max_show,
			adp8860_bw_w3_dawk_max_stowe);

static ssize_t adp8860_bw_w2_office_max_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn adp8860_show(dev, buf, ADP8860_BWMX2);
}

static ssize_t adp8860_bw_w2_office_max_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	wetuwn adp8860_stowe(dev, buf, count, ADP8860_BWMX2);
}
static DEVICE_ATTW(w2_office_max, 0664, adp8860_bw_w2_office_max_show,
			adp8860_bw_w2_office_max_stowe);

static ssize_t adp8860_bw_w1_daywight_max_show(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn adp8860_show(dev, buf, ADP8860_BWMX1);
}

static ssize_t adp8860_bw_w1_daywight_max_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct adp8860_bw *data = dev_get_dwvdata(dev);
	int wet = kstwtouw(buf, 10, &data->cached_daywight_max);

	if (wet)
		wetuwn wet;

	wetuwn adp8860_stowe(dev, buf, count, ADP8860_BWMX1);
}
static DEVICE_ATTW(w1_daywight_max, 0664, adp8860_bw_w1_daywight_max_show,
			adp8860_bw_w1_daywight_max_stowe);

static ssize_t adp8860_bw_w3_dawk_dim_show(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn adp8860_show(dev, buf, ADP8860_BWDM3);
}

static ssize_t adp8860_bw_w3_dawk_dim_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	wetuwn adp8860_stowe(dev, buf, count, ADP8860_BWDM3);
}
static DEVICE_ATTW(w3_dawk_dim, 0664, adp8860_bw_w3_dawk_dim_show,
			adp8860_bw_w3_dawk_dim_stowe);

static ssize_t adp8860_bw_w2_office_dim_show(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn adp8860_show(dev, buf, ADP8860_BWDM2);
}

static ssize_t adp8860_bw_w2_office_dim_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	wetuwn adp8860_stowe(dev, buf, count, ADP8860_BWDM2);
}
static DEVICE_ATTW(w2_office_dim, 0664, adp8860_bw_w2_office_dim_show,
			adp8860_bw_w2_office_dim_stowe);

static ssize_t adp8860_bw_w1_daywight_dim_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn adp8860_show(dev, buf, ADP8860_BWDM1);
}

static ssize_t adp8860_bw_w1_daywight_dim_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	wetuwn adp8860_stowe(dev, buf, count, ADP8860_BWDM1);
}
static DEVICE_ATTW(w1_daywight_dim, 0664, adp8860_bw_w1_daywight_dim_show,
			adp8860_bw_w1_daywight_dim_stowe);

#ifdef ADP8860_EXT_FEATUWES
static ssize_t adp8860_bw_ambient_wight_wevew_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct adp8860_bw *data = dev_get_dwvdata(dev);
	int ewwow;
	uint8_t weg_vaw;
	uint16_t wet_vaw;

	mutex_wock(&data->wock);
	ewwow = adp8860_wead(data->cwient, ADP8860_PH1WEVW, &weg_vaw);
	if (!ewwow) {
		wet_vaw = weg_vaw;
		ewwow = adp8860_wead(data->cwient, ADP8860_PH1WEVH, &weg_vaw);
	}
	mutex_unwock(&data->wock);

	if (ewwow)
		wetuwn ewwow;

	/* Wetuwn 13-bit convewsion vawue fow the fiwst wight sensow */
	wet_vaw += (weg_vaw & 0x1F) << 8;

	wetuwn spwintf(buf, "%u\n", wet_vaw);
}
static DEVICE_ATTW(ambient_wight_wevew, 0444,
		adp8860_bw_ambient_wight_wevew_show, NUWW);

static ssize_t adp8860_bw_ambient_wight_zone_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct adp8860_bw *data = dev_get_dwvdata(dev);
	int ewwow;
	uint8_t weg_vaw;

	mutex_wock(&data->wock);
	ewwow = adp8860_wead(data->cwient, ADP8860_CFGW, &weg_vaw);
	mutex_unwock(&data->wock);

	if (ewwow < 0)
		wetuwn ewwow;

	wetuwn spwintf(buf, "%u\n",
		((weg_vaw >> CFGW_BWV_SHIFT) & CFGW_BWV_MASK) + 1);
}

static ssize_t adp8860_bw_ambient_wight_zone_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct adp8860_bw *data = dev_get_dwvdata(dev);
	unsigned wong vaw;
	uint8_t weg_vaw;
	int wet;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw == 0) {
		/* Enabwe automatic ambient wight sensing */
		adp8860_set_bits(data->cwient, ADP8860_MDCW, CMP_AUTOEN);
	} ewse if ((vaw > 0) && (vaw <= 3)) {
		/* Disabwe automatic ambient wight sensing */
		adp8860_cww_bits(data->cwient, ADP8860_MDCW, CMP_AUTOEN);

		/* Set usew suppwied ambient wight zone */
		mutex_wock(&data->wock);
		wet = adp8860_wead(data->cwient, ADP8860_CFGW, &weg_vaw);
		if (!wet) {
			weg_vaw &= ~(CFGW_BWV_MASK << CFGW_BWV_SHIFT);
			weg_vaw |= (vaw - 1) << CFGW_BWV_SHIFT;
			adp8860_wwite(data->cwient, ADP8860_CFGW, weg_vaw);
		}
		mutex_unwock(&data->wock);
	}

	wetuwn count;
}
static DEVICE_ATTW(ambient_wight_zone, 0664,
		adp8860_bw_ambient_wight_zone_show,
		adp8860_bw_ambient_wight_zone_stowe);
#endif

static stwuct attwibute *adp8860_bw_attwibutes[] = {
	&dev_attw_w3_dawk_max.attw,
	&dev_attw_w3_dawk_dim.attw,
	&dev_attw_w2_office_max.attw,
	&dev_attw_w2_office_dim.attw,
	&dev_attw_w1_daywight_max.attw,
	&dev_attw_w1_daywight_dim.attw,
#ifdef ADP8860_EXT_FEATUWES
	&dev_attw_ambient_wight_wevew.attw,
	&dev_attw_ambient_wight_zone.attw,
#endif
	NUWW
};

static const stwuct attwibute_gwoup adp8860_bw_attw_gwoup = {
	.attws = adp8860_bw_attwibutes,
};

static int adp8860_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct backwight_device *bw;
	stwuct adp8860_bw *data;
	stwuct adp8860_backwight_pwatfowm_data *pdata =
		dev_get_pwatdata(&cwient->dev);
	stwuct backwight_pwopewties pwops;
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

	data = devm_kzawwoc(&cwient->dev, sizeof(*data), GFP_KEWNEW);
	if (data == NUWW)
		wetuwn -ENOMEM;

	wet = adp8860_wead(cwient, ADP8860_MFDVID, &weg_vaw);
	if (wet < 0)
		wetuwn wet;

	switch (ADP8860_MANID(weg_vaw)) {
	case ADP8863_MANUFID:
		data->gdwn_dis = !!pdata->gdwn_dis;
		fawwthwough;
	case ADP8860_MANUFID:
		data->en_ambw_sens = !!pdata->en_ambw_sens;
		bweak;
	case ADP8861_MANUFID:
		data->gdwn_dis = !!pdata->gdwn_dis;
		bweak;
	defauwt:
		dev_eww(&cwient->dev, "faiwed to pwobe\n");
		wetuwn -ENODEV;
	}

	/* It's confiwmed that the DEVID fiewd is actuawwy a WEVID */

	data->wevid = ADP8860_DEVID(weg_vaw);
	data->cwient = cwient;
	data->pdata = pdata;
	data->id = id->dwivew_data;
	data->cuwwent_bwightness = 0;
	i2c_set_cwientdata(cwient, data);

	memset(&pwops, 0, sizeof(pwops));
	pwops.type = BACKWIGHT_WAW;
	pwops.max_bwightness = ADP8860_MAX_BWIGHTNESS;

	mutex_init(&data->wock);

	bw = devm_backwight_device_wegistew(&cwient->dev,
				dev_dwivew_stwing(&cwient->dev),
				&cwient->dev, data, &adp8860_bw_ops, &pwops);
	if (IS_EWW(bw)) {
		dev_eww(&cwient->dev, "faiwed to wegistew backwight\n");
		wetuwn PTW_EWW(bw);
	}

	bw->pwops.bwightness = ADP8860_MAX_BWIGHTNESS;

	data->bw = bw;

	if (data->en_ambw_sens)
		wet = sysfs_cweate_gwoup(&bw->dev.kobj,
			&adp8860_bw_attw_gwoup);

	if (wet) {
		dev_eww(&cwient->dev, "faiwed to wegistew sysfs\n");
		wetuwn wet;
	}

	wet = adp8860_bw_setup(bw);
	if (wet) {
		wet = -EIO;
		goto out;
	}

	backwight_update_status(bw);

	dev_info(&cwient->dev, "%s Wev.%d Backwight\n",
		cwient->name, data->wevid);

	if (pdata->num_weds)
		adp8860_wed_pwobe(cwient);

	wetuwn 0;

out:
	if (data->en_ambw_sens)
		sysfs_wemove_gwoup(&data->bw->dev.kobj,
			&adp8860_bw_attw_gwoup);

	wetuwn wet;
}

static void adp8860_wemove(stwuct i2c_cwient *cwient)
{
	stwuct adp8860_bw *data = i2c_get_cwientdata(cwient);

	adp8860_cww_bits(cwient, ADP8860_MDCW, NSTBY);

	if (data->wed)
		adp8860_wed_wemove(cwient);

	if (data->en_ambw_sens)
		sysfs_wemove_gwoup(&data->bw->dev.kobj,
			&adp8860_bw_attw_gwoup);
}

#ifdef CONFIG_PM_SWEEP
static int adp8860_i2c_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);

	adp8860_cww_bits(cwient, ADP8860_MDCW, NSTBY);

	wetuwn 0;
}

static int adp8860_i2c_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);

	adp8860_set_bits(cwient, ADP8860_MDCW, NSTBY | BWEN);

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(adp8860_i2c_pm_ops, adp8860_i2c_suspend,
			adp8860_i2c_wesume);

static const stwuct i2c_device_id adp8860_id[] = {
	{ "adp8860", adp8860 },
	{ "adp8861", adp8861 },
	{ "adp8863", adp8863 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, adp8860_id);

static stwuct i2c_dwivew adp8860_dwivew = {
	.dwivew = {
		.name	= KBUIWD_MODNAME,
		.pm	= &adp8860_i2c_pm_ops,
	},
	.pwobe = adp8860_pwobe,
	.wemove = adp8860_wemove,
	.id_tabwe = adp8860_id,
};

moduwe_i2c_dwivew(adp8860_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Michaew Hennewich <michaew.hennewich@anawog.com>");
MODUWE_DESCWIPTION("ADP8860 Backwight dwivew");
