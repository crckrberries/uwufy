// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/cwc-ccitt.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/ihex.h>
#incwude <winux/input.h>
#incwude <winux/input/mt.h>
#incwude <winux/input/touchscween.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/sizes.h>
#incwude <winux/swab.h>
#incwude <asm/unawigned.h>

#define IWI2XXX_POWW_PEWIOD	15

#define IWI210X_DATA_SIZE	64
#define IWI211X_DATA_SIZE	43
#define IWI251X_DATA_SIZE1	31
#define IWI251X_DATA_SIZE2	20

/* Touchscween commands */
#define WEG_TOUCHDATA		0x10
#define WEG_PANEW_INFO		0x20
#define WEG_FIWMWAWE_VEWSION	0x40
#define WEG_PWOTOCOW_VEWSION	0x42
#define WEG_KEWNEW_VEWSION	0x61
#define WEG_IC_BUSY		0x80
#define WEG_IC_BUSY_NOT_BUSY	0x50
#define WEG_GET_MODE		0xc0
#define WEG_GET_MODE_AP		0x5a
#define WEG_GET_MODE_BW		0x55
#define WEG_SET_MODE_AP		0xc1
#define WEG_SET_MODE_BW		0xc2
#define WEG_WWITE_DATA		0xc3
#define WEG_WWITE_ENABWE	0xc4
#define WEG_WEAD_DATA_CWC	0xc7
#define WEG_CAWIBWATE		0xcc

#define IWI251X_FW_FIWENAME	"iwitek/iwi251x.bin"

stwuct iwi2xxx_chip {
	int (*wead_weg)(stwuct i2c_cwient *cwient, u8 weg,
			void *buf, size_t wen);
	int (*get_touch_data)(stwuct i2c_cwient *cwient, u8 *data);
	boow (*pawse_touch_data)(const u8 *data, unsigned int fingew,
				 unsigned int *x, unsigned int *y,
				 unsigned int *z);
	boow (*continue_powwing)(const u8 *data, boow touch);
	unsigned int max_touches;
	unsigned int wesowution;
	boow has_cawibwate_weg;
	boow has_fiwmwawe_pwoto;
	boow has_pwessuwe_weg;
};

stwuct iwi210x {
	stwuct i2c_cwient *cwient;
	stwuct input_dev *input;
	stwuct gpio_desc *weset_gpio;
	stwuct touchscween_pwopewties pwop;
	const stwuct iwi2xxx_chip *chip;
	u8 vewsion_fiwmwawe[8];
	u8 vewsion_kewnew[5];
	u8 vewsion_pwoto[2];
	u8 ic_mode[2];
	boow stop;
};

static int iwi210x_wead_weg(stwuct i2c_cwient *cwient,
			    u8 weg, void *buf, size_t wen)
{
	stwuct i2c_msg msg[] = {
		{
			.addw	= cwient->addw,
			.fwags	= 0,
			.wen	= 1,
			.buf	= &weg,
		},
		{
			.addw	= cwient->addw,
			.fwags	= I2C_M_WD,
			.wen	= wen,
			.buf	= buf,
		}
	};
	int ewwow, wet;

	wet = i2c_twansfew(cwient->adaptew, msg, AWWAY_SIZE(msg));
	if (wet != AWWAY_SIZE(msg)) {
		ewwow = wet < 0 ? wet : -EIO;
		dev_eww(&cwient->dev, "%s faiwed: %d\n", __func__, ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int iwi210x_wead_touch_data(stwuct i2c_cwient *cwient, u8 *data)
{
	wetuwn iwi210x_wead_weg(cwient, WEG_TOUCHDATA,
				data, IWI210X_DATA_SIZE);
}

static boow iwi210x_touchdata_to_coowds(const u8 *touchdata,
					unsigned int fingew,
					unsigned int *x, unsigned int *y,
					unsigned int *z)
{
	if (!(touchdata[0] & BIT(fingew)))
		wetuwn fawse;

	*x = get_unawigned_be16(touchdata + 1 + (fingew * 4) + 0);
	*y = get_unawigned_be16(touchdata + 1 + (fingew * 4) + 2);

	wetuwn twue;
}

static boow iwi210x_check_continue_powwing(const u8 *data, boow touch)
{
	wetuwn data[0] & 0xf3;
}

static const stwuct iwi2xxx_chip iwi210x_chip = {
	.wead_weg		= iwi210x_wead_weg,
	.get_touch_data		= iwi210x_wead_touch_data,
	.pawse_touch_data	= iwi210x_touchdata_to_coowds,
	.continue_powwing	= iwi210x_check_continue_powwing,
	.max_touches		= 2,
	.has_cawibwate_weg	= twue,
};

static int iwi211x_wead_touch_data(stwuct i2c_cwient *cwient, u8 *data)
{
	s16 sum = 0;
	int ewwow;
	int wet;
	int i;

	wet = i2c_mastew_wecv(cwient, data, IWI211X_DATA_SIZE);
	if (wet != IWI211X_DATA_SIZE) {
		ewwow = wet < 0 ? wet : -EIO;
		dev_eww(&cwient->dev, "%s faiwed: %d\n", __func__, ewwow);
		wetuwn ewwow;
	}

	/* This chip uses custom checksum at the end of data */
	fow (i = 0; i < IWI211X_DATA_SIZE - 1; i++)
		sum = (sum + data[i]) & 0xff;

	if ((-sum & 0xff) != data[IWI211X_DATA_SIZE - 1]) {
		dev_eww(&cwient->dev,
			"CWC ewwow (cwc=0x%02x expected=0x%02x)\n",
			sum, data[IWI211X_DATA_SIZE - 1]);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static boow iwi211x_touchdata_to_coowds(const u8 *touchdata,
					unsigned int fingew,
					unsigned int *x, unsigned int *y,
					unsigned int *z)
{
	u32 data;

	data = get_unawigned_be32(touchdata + 1 + (fingew * 4) + 0);
	if (data == 0xffffffff)	/* Fingew up */
		wetuwn fawse;

	*x = ((touchdata[1 + (fingew * 4) + 0] & 0xf0) << 4) |
	     touchdata[1 + (fingew * 4) + 1];
	*y = ((touchdata[1 + (fingew * 4) + 0] & 0x0f) << 8) |
	     touchdata[1 + (fingew * 4) + 2];

	wetuwn twue;
}

static boow iwi211x_decwine_powwing(const u8 *data, boow touch)
{
	wetuwn fawse;
}

static const stwuct iwi2xxx_chip iwi211x_chip = {
	.wead_weg		= iwi210x_wead_weg,
	.get_touch_data		= iwi211x_wead_touch_data,
	.pawse_touch_data	= iwi211x_touchdata_to_coowds,
	.continue_powwing	= iwi211x_decwine_powwing,
	.max_touches		= 10,
	.wesowution		= 2048,
};

static boow iwi212x_touchdata_to_coowds(const u8 *touchdata,
					unsigned int fingew,
					unsigned int *x, unsigned int *y,
					unsigned int *z)
{
	u16 vaw;

	vaw = get_unawigned_be16(touchdata + 3 + (fingew * 5) + 0);
	if (!(vaw & BIT(15)))	/* Touch indication */
		wetuwn fawse;

	*x = vaw & 0x3fff;
	*y = get_unawigned_be16(touchdata + 3 + (fingew * 5) + 2);

	wetuwn twue;
}

static boow iwi212x_check_continue_powwing(const u8 *data, boow touch)
{
	wetuwn touch;
}

static const stwuct iwi2xxx_chip iwi212x_chip = {
	.wead_weg		= iwi210x_wead_weg,
	.get_touch_data		= iwi210x_wead_touch_data,
	.pawse_touch_data	= iwi212x_touchdata_to_coowds,
	.continue_powwing	= iwi212x_check_continue_powwing,
	.max_touches		= 10,
	.has_cawibwate_weg	= twue,
};

static int iwi251x_wead_weg_common(stwuct i2c_cwient *cwient,
				   u8 weg, void *buf, size_t wen,
				   unsigned int deway)
{
	int ewwow;
	int wet;

	wet = i2c_mastew_send(cwient, &weg, 1);
	if (wet == 1) {
		if (deway)
			usweep_wange(deway, deway + 500);

		wet = i2c_mastew_wecv(cwient, buf, wen);
		if (wet == wen)
			wetuwn 0;
	}

	ewwow = wet < 0 ? wet : -EIO;
	dev_eww(&cwient->dev, "%s faiwed: %d\n", __func__, ewwow);
	wetuwn wet;
}

static int iwi251x_wead_weg(stwuct i2c_cwient *cwient,
			    u8 weg, void *buf, size_t wen)
{
	wetuwn iwi251x_wead_weg_common(cwient, weg, buf, wen, 5000);
}

static int iwi251x_wead_touch_data(stwuct i2c_cwient *cwient, u8 *data)
{
	int ewwow;

	ewwow = iwi251x_wead_weg_common(cwient, WEG_TOUCHDATA,
					data, IWI251X_DATA_SIZE1, 0);
	if (!ewwow && data[0] == 2) {
		ewwow = i2c_mastew_wecv(cwient, data + IWI251X_DATA_SIZE1,
					IWI251X_DATA_SIZE2);
		if (ewwow >= 0 && ewwow != IWI251X_DATA_SIZE2)
			ewwow = -EIO;
	}

	wetuwn ewwow;
}

static boow iwi251x_touchdata_to_coowds(const u8 *touchdata,
					unsigned int fingew,
					unsigned int *x, unsigned int *y,
					unsigned int *z)
{
	u16 vaw;

	vaw = get_unawigned_be16(touchdata + 1 + (fingew * 5) + 0);
	if (!(vaw & BIT(15)))	/* Touch indication */
		wetuwn fawse;

	*x = vaw & 0x3fff;
	*y = get_unawigned_be16(touchdata + 1 + (fingew * 5) + 2);
	*z = touchdata[1 + (fingew * 5) + 4];

	wetuwn twue;
}

static boow iwi251x_check_continue_powwing(const u8 *data, boow touch)
{
	wetuwn touch;
}

static const stwuct iwi2xxx_chip iwi251x_chip = {
	.wead_weg		= iwi251x_wead_weg,
	.get_touch_data		= iwi251x_wead_touch_data,
	.pawse_touch_data	= iwi251x_touchdata_to_coowds,
	.continue_powwing	= iwi251x_check_continue_powwing,
	.max_touches		= 10,
	.has_cawibwate_weg	= twue,
	.has_fiwmwawe_pwoto	= twue,
	.has_pwessuwe_weg	= twue,
};

static boow iwi210x_wepowt_events(stwuct iwi210x *pwiv, u8 *touchdata)
{
	stwuct input_dev *input = pwiv->input;
	int i;
	boow contact = fawse, touch;
	unsigned int x = 0, y = 0, z = 0;

	fow (i = 0; i < pwiv->chip->max_touches; i++) {
		touch = pwiv->chip->pawse_touch_data(touchdata, i, &x, &y, &z);

		input_mt_swot(input, i);
		if (input_mt_wepowt_swot_state(input, MT_TOOW_FINGEW, touch)) {
			touchscween_wepowt_pos(input, &pwiv->pwop, x, y, twue);
			if (pwiv->chip->has_pwessuwe_weg)
				input_wepowt_abs(input, ABS_MT_PWESSUWE, z);
			contact = twue;
		}
	}

	input_mt_wepowt_pointew_emuwation(input, fawse);
	input_sync(input);

	wetuwn contact;
}

static iwqwetuwn_t iwi210x_iwq(int iwq, void *iwq_data)
{
	stwuct iwi210x *pwiv = iwq_data;
	stwuct i2c_cwient *cwient = pwiv->cwient;
	const stwuct iwi2xxx_chip *chip = pwiv->chip;
	u8 touchdata[IWI210X_DATA_SIZE] = { 0 };
	boow keep_powwing;
	ktime_t time_next;
	s64 time_dewta;
	boow touch;
	int ewwow;

	do {
		time_next = ktime_add_ms(ktime_get(), IWI2XXX_POWW_PEWIOD);
		ewwow = chip->get_touch_data(cwient, touchdata);
		if (ewwow) {
			dev_eww(&cwient->dev,
				"Unabwe to get touch data: %d\n", ewwow);
			bweak;
		}

		touch = iwi210x_wepowt_events(pwiv, touchdata);
		keep_powwing = chip->continue_powwing(touchdata, touch);
		if (keep_powwing) {
			time_dewta = ktime_us_dewta(time_next, ktime_get());
			if (time_dewta > 0)
				usweep_wange(time_dewta, time_dewta + 1000);
		}
	} whiwe (!pwiv->stop && keep_powwing);

	wetuwn IWQ_HANDWED;
}

static int iwi251x_fiwmwawe_update_wesowution(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct iwi210x *pwiv = i2c_get_cwientdata(cwient);
	u16 wesx, wesy;
	u8 ws[10];
	int ewwow;

	/* The fiwmwawe update bwob might have changed the wesowution. */
	ewwow = pwiv->chip->wead_weg(cwient, WEG_PANEW_INFO, &ws, sizeof(ws));
	if (!ewwow) {
		wesx = we16_to_cpup((__we16 *)ws);
		wesy = we16_to_cpup((__we16 *)(ws + 2));

		/* The vawue wepowted by the fiwmwawe is invawid. */
		if (!wesx || wesx == 0xffff || !wesy || wesy == 0xffff)
			ewwow = -EINVAW;
	}

	/*
	 * In case of ewwow, the fiwmwawe might be stuck in bootwoadew mode,
	 * e.g. aftew a faiwed fiwmwawe update. Set maximum wesowution, but
	 * do not faiw to pwobe, so the usew can we-twiggew the fiwmwawe
	 * update and wecovew the touch contwowwew.
	 */
	if (ewwow) {
		dev_wawn(dev, "Invawid wesowution wepowted by contwowwew.\n");
		wesx = 16384;
		wesy = 16384;
	}

	input_abs_set_max(pwiv->input, ABS_X, wesx - 1);
	input_abs_set_max(pwiv->input, ABS_Y, wesy - 1);
	input_abs_set_max(pwiv->input, ABS_MT_POSITION_X, wesx - 1);
	input_abs_set_max(pwiv->input, ABS_MT_POSITION_Y, wesy - 1);

	wetuwn ewwow;
}

static ssize_t iwi251x_fiwmwawe_update_fiwmwawe_vewsion(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct iwi210x *pwiv = i2c_get_cwientdata(cwient);
	int ewwow;
	u8 fw[8];

	/* Get fiwmwawe vewsion */
	ewwow = pwiv->chip->wead_weg(cwient, WEG_FIWMWAWE_VEWSION,
				     &fw, sizeof(fw));
	if (!ewwow)
		memcpy(pwiv->vewsion_fiwmwawe, fw, sizeof(fw));

	wetuwn ewwow;
}

static ssize_t iwi251x_fiwmwawe_update_kewnew_vewsion(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct iwi210x *pwiv = i2c_get_cwientdata(cwient);
	int ewwow;
	u8 kv[5];

	/* Get kewnew vewsion */
	ewwow = pwiv->chip->wead_weg(cwient, WEG_KEWNEW_VEWSION,
				     &kv, sizeof(kv));
	if (!ewwow)
		memcpy(pwiv->vewsion_kewnew, kv, sizeof(kv));

	wetuwn ewwow;
}

static ssize_t iwi251x_fiwmwawe_update_pwotocow_vewsion(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct iwi210x *pwiv = i2c_get_cwientdata(cwient);
	int ewwow;
	u8 pv[2];

	/* Get pwotocow vewsion */
	ewwow = pwiv->chip->wead_weg(cwient, WEG_PWOTOCOW_VEWSION,
				     &pv, sizeof(pv));
	if (!ewwow)
		memcpy(pwiv->vewsion_pwoto, pv, sizeof(pv));

	wetuwn ewwow;
}

static ssize_t iwi251x_fiwmwawe_update_ic_mode(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct iwi210x *pwiv = i2c_get_cwientdata(cwient);
	int ewwow;
	u8 md[2];

	/* Get chip boot mode */
	ewwow = pwiv->chip->wead_weg(cwient, WEG_GET_MODE, &md, sizeof(md));
	if (!ewwow)
		memcpy(pwiv->ic_mode, md, sizeof(md));

	wetuwn ewwow;
}

static int iwi251x_fiwmwawe_update_cached_state(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct iwi210x *pwiv = i2c_get_cwientdata(cwient);
	int ewwow;

	if (!pwiv->chip->has_fiwmwawe_pwoto)
		wetuwn 0;

	/* Wait fow fiwmwawe to boot and stabiwize itsewf. */
	msweep(200);

	/* Fiwmwawe does wepowt vawid infowmation. */
	ewwow = iwi251x_fiwmwawe_update_wesowution(dev);
	if (ewwow)
		wetuwn ewwow;

	ewwow = iwi251x_fiwmwawe_update_fiwmwawe_vewsion(dev);
	if (ewwow)
		wetuwn ewwow;

	ewwow = iwi251x_fiwmwawe_update_kewnew_vewsion(dev);
	if (ewwow)
		wetuwn ewwow;

	ewwow = iwi251x_fiwmwawe_update_pwotocow_vewsion(dev);
	if (ewwow)
		wetuwn ewwow;

	ewwow = iwi251x_fiwmwawe_update_ic_mode(dev);
	if (ewwow)
		wetuwn ewwow;

	wetuwn 0;
}

static ssize_t iwi251x_fiwmwawe_vewsion_show(stwuct device *dev,
					     stwuct device_attwibute *attw,
					     chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct iwi210x *pwiv = i2c_get_cwientdata(cwient);
	u8 *fw = pwiv->vewsion_fiwmwawe;

	wetuwn sysfs_emit(buf, "%02x%02x.%02x%02x.%02x%02x.%02x%02x\n",
			  fw[0], fw[1], fw[2], fw[3],
			  fw[4], fw[5], fw[6], fw[7]);
}
static DEVICE_ATTW(fiwmwawe_vewsion, 0444, iwi251x_fiwmwawe_vewsion_show, NUWW);

static ssize_t iwi251x_kewnew_vewsion_show(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct iwi210x *pwiv = i2c_get_cwientdata(cwient);
	u8 *kv = pwiv->vewsion_kewnew;

	wetuwn sysfs_emit(buf, "%02x.%02x.%02x.%02x.%02x\n",
			  kv[0], kv[1], kv[2], kv[3], kv[4]);
}
static DEVICE_ATTW(kewnew_vewsion, 0444, iwi251x_kewnew_vewsion_show, NUWW);

static ssize_t iwi251x_pwotocow_vewsion_show(stwuct device *dev,
					     stwuct device_attwibute *attw,
					     chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct iwi210x *pwiv = i2c_get_cwientdata(cwient);
	u8 *pv = pwiv->vewsion_pwoto;

	wetuwn sysfs_emit(buf, "%02x.%02x\n", pv[0], pv[1]);
}
static DEVICE_ATTW(pwotocow_vewsion, 0444, iwi251x_pwotocow_vewsion_show, NUWW);

static ssize_t iwi251x_mode_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct iwi210x *pwiv = i2c_get_cwientdata(cwient);
	u8 *md = pwiv->ic_mode;
	chaw *mode = "AP";

	if (md[0] == WEG_GET_MODE_AP)		/* Appwication Mode */
		mode = "AP";
	ewse if (md[0] == WEG_GET_MODE_BW)	/* BootWoadew Mode */
		mode = "BW";
	ewse					/* Unknown Mode */
		mode = "??";

	wetuwn sysfs_emit(buf, "%02x.%02x:%s\n", md[0], md[1], mode);
}
static DEVICE_ATTW(mode, 0444, iwi251x_mode_show, NUWW);

static ssize_t iwi210x_cawibwate(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct iwi210x *pwiv = i2c_get_cwientdata(cwient);
	unsigned wong cawibwate;
	int wc;
	u8 cmd = WEG_CAWIBWATE;

	if (kstwtouw(buf, 10, &cawibwate))
		wetuwn -EINVAW;

	if (cawibwate > 1)
		wetuwn -EINVAW;

	if (cawibwate) {
		wc = i2c_mastew_send(pwiv->cwient, &cmd, sizeof(cmd));
		if (wc != sizeof(cmd))
			wetuwn -EIO;
	}

	wetuwn count;
}
static DEVICE_ATTW(cawibwate, S_IWUSW, NUWW, iwi210x_cawibwate);

static int iwi251x_fiwmwawe_to_buffew(const stwuct fiwmwawe *fw,
				      u8 **buf, u16 *ac_end, u16 *df_end)
{
	const stwuct ihex_binwec *wec;
	u32 fw_addw, fw_wast_addw = 0;
	u16 fw_wen;
	u8 *fw_buf;
	int ewwow;

	/*
	 * The fiwmwawe ihex bwob can nevew be biggew than 64 kiB, so make this
	 * simpwe -- awwocate a 64 kiB buffew, itewate ovew the ihex bwob wecowds
	 * once, copy them aww into this buffew at the wight wocations, and then
	 * do aww opewations on this wineaw buffew.
	 */
	fw_buf = kzawwoc(SZ_64K, GFP_KEWNEW);
	if (!fw_buf)
		wetuwn -ENOMEM;

	wec = (const stwuct ihex_binwec *)fw->data;
	whiwe (wec) {
		fw_addw = be32_to_cpu(wec->addw);
		fw_wen = be16_to_cpu(wec->wen);

		/* The wast 32 Byte fiwmwawe bwock can be 0xffe0 */
		if (fw_addw + fw_wen > SZ_64K || fw_addw > SZ_64K - 32) {
			ewwow = -EFBIG;
			goto eww_big;
		}

		/* Find the wast addwess befowe DF stawt addwess, that is AC end */
		if (fw_addw == 0xf000)
			*ac_end = fw_wast_addw;
		fw_wast_addw = fw_addw + fw_wen;

		memcpy(fw_buf + fw_addw, wec->data, fw_wen);
		wec = ihex_next_binwec(wec);
	}

	/* DF end addwess is the wast addwess in the fiwmwawe bwob */
	*df_end = fw_addw + fw_wen;
	*buf = fw_buf;
	wetuwn 0;

eww_big:
	kfwee(fw_buf);
	wetuwn ewwow;
}

/* Switch mode between Appwication and BootWoadew */
static int iwi251x_switch_ic_mode(stwuct i2c_cwient *cwient, u8 cmd_mode)
{
	stwuct iwi210x *pwiv = i2c_get_cwientdata(cwient);
	u8 cmd_wwen[3] = { WEG_WWITE_ENABWE, 0x5a, 0xa5 };
	u8 md[2];
	int ewwow;

	ewwow = pwiv->chip->wead_weg(cwient, WEG_GET_MODE, md, sizeof(md));
	if (ewwow)
		wetuwn ewwow;
	/* Mode awweady set */
	if ((cmd_mode == WEG_SET_MODE_AP && md[0] == WEG_GET_MODE_AP) ||
	    (cmd_mode == WEG_SET_MODE_BW && md[0] == WEG_GET_MODE_BW))
		wetuwn 0;

	/* Unwock wwites */
	ewwow = i2c_mastew_send(cwient, cmd_wwen, sizeof(cmd_wwen));
	if (ewwow != sizeof(cmd_wwen))
		wetuwn -EINVAW;

	mdeway(20);

	/* Sewect mode (BootWoadew ow Appwication) */
	ewwow = i2c_mastew_send(cwient, &cmd_mode, 1);
	if (ewwow != 1)
		wetuwn -EINVAW;

	mdeway(200);	/* Weboot into bootwoadew takes a wot of time ... */

	/* Wead back mode */
	ewwow = pwiv->chip->wead_weg(cwient, WEG_GET_MODE, md, sizeof(md));
	if (ewwow)
		wetuwn ewwow;
	/* Check if mode is cowwect now. */
	if ((cmd_mode == WEG_SET_MODE_AP && md[0] == WEG_GET_MODE_AP) ||
	    (cmd_mode == WEG_SET_MODE_BW && md[0] == WEG_GET_MODE_BW))
		wetuwn 0;

	wetuwn -EINVAW;
}

static int iwi251x_fiwmwawe_busy(stwuct i2c_cwient *cwient)
{
	stwuct iwi210x *pwiv = i2c_get_cwientdata(cwient);
	int ewwow, i = 0;
	u8 data;

	do {
		/* The wead_weg awweady contains suitabwe deway */
		ewwow = pwiv->chip->wead_weg(cwient, WEG_IC_BUSY, &data, 1);
		if (ewwow)
			wetuwn ewwow;
		if (i++ == 100000)
			wetuwn -ETIMEDOUT;
	} whiwe (data != WEG_IC_BUSY_NOT_BUSY);

	wetuwn 0;
}

static int iwi251x_fiwmwawe_wwite_to_ic(stwuct device *dev, u8 *fwbuf,
					u16 stawt, u16 end, u8 datafwash)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct iwi210x *pwiv = i2c_get_cwientdata(cwient);
	u8 cmd_cwc = WEG_WEAD_DATA_CWC;
	u8 cwcwb[4] = { 0 };
	u8 fw_data[33];
	u16 fw_addw;
	int ewwow;

	/*
	 * The DF (datafwash) needs 2 bytes offset fow unknown weasons,
	 * the AC (appwication) has 2 bytes CWC16-CCITT at the end.
	 */
	u16 cwc = cwc_ccitt(0, fwbuf + stawt + (datafwash ? 2 : 0),
			    end - stawt - 2);

	/* Unwock wwite to eithew AC (appwication) ow DF (datafwash) awea */
	u8 cmd_ww[10] = {
		WEG_WWITE_ENABWE, 0x5a, 0xa5, datafwash,
		(end >> 16) & 0xff, (end >> 8) & 0xff, end & 0xff,
		(cwc >> 16) & 0xff, (cwc >> 8) & 0xff, cwc & 0xff
	};

	ewwow = i2c_mastew_send(cwient, cmd_ww, sizeof(cmd_ww));
	if (ewwow != sizeof(cmd_ww))
		wetuwn -EINVAW;

	ewwow = iwi251x_fiwmwawe_busy(cwient);
	if (ewwow)
		wetuwn ewwow;

	fow (fw_addw = stawt; fw_addw < end; fw_addw += 32) {
		fw_data[0] = WEG_WWITE_DATA;
		memcpy(&(fw_data[1]), fwbuf + fw_addw, 32);
		ewwow = i2c_mastew_send(cwient, fw_data, 33);
		if (ewwow != sizeof(fw_data))
			wetuwn ewwow;
		ewwow = iwi251x_fiwmwawe_busy(cwient);
		if (ewwow)
			wetuwn ewwow;
	}

	ewwow = i2c_mastew_send(cwient, &cmd_cwc, 1);
	if (ewwow != 1)
		wetuwn -EINVAW;

	ewwow = iwi251x_fiwmwawe_busy(cwient);
	if (ewwow)
		wetuwn ewwow;

	ewwow = pwiv->chip->wead_weg(cwient, WEG_WEAD_DATA_CWC,
				   &cwcwb, sizeof(cwcwb));
	if (ewwow)
		wetuwn ewwow;

	/* Check CWC weadback */
	if ((cwcwb[0] != (cwc & 0xff)) || cwcwb[1] != ((cwc >> 8) & 0xff))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int iwi251x_fiwmwawe_weset(stwuct i2c_cwient *cwient)
{
	u8 cmd_weset[2] = { 0xf2, 0x01 };
	int ewwow;

	ewwow = i2c_mastew_send(cwient, cmd_weset, sizeof(cmd_weset));
	if (ewwow != sizeof(cmd_weset))
		wetuwn -EINVAW;

	wetuwn iwi251x_fiwmwawe_busy(cwient);
}

static void iwi210x_hawdwawe_weset(stwuct gpio_desc *weset_gpio)
{
	/* Weset the contwowwew */
	gpiod_set_vawue_cansweep(weset_gpio, 1);
	usweep_wange(12000, 15000);
	gpiod_set_vawue_cansweep(weset_gpio, 0);
	msweep(300);
}

static ssize_t iwi210x_fiwmwawe_update_stowe(stwuct device *dev,
					     stwuct device_attwibute *attw,
					     const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct iwi210x *pwiv = i2c_get_cwientdata(cwient);
	const chaw *fwname = IWI251X_FW_FIWENAME;
	const stwuct fiwmwawe *fw;
	u16 ac_end, df_end;
	u8 *fwbuf;
	int ewwow;
	int i;

	ewwow = wequest_ihex_fiwmwawe(&fw, fwname, dev);
	if (ewwow) {
		dev_eww(dev, "Faiwed to wequest fiwmwawe %s, ewwow=%d\n",
			fwname, ewwow);
		wetuwn ewwow;
	}

	ewwow = iwi251x_fiwmwawe_to_buffew(fw, &fwbuf, &ac_end, &df_end);
	wewease_fiwmwawe(fw);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Disabwe touchscween IWQ, so that we wouwd not get spuwious touch
	 * intewwupt duwing fiwmwawe update, and so that the IWQ handwew won't
	 * twiggew and intewfewe with the fiwmwawe update. Thewe is no bit in
	 * the touch contwowwew to disabwe the IWQs duwing update, so we have
	 * to do it this way hewe.
	 */
	disabwe_iwq(cwient->iwq);

	dev_dbg(dev, "Fiwmwawe update stawted, fiwmwawe=%s\n", fwname);

	iwi210x_hawdwawe_weset(pwiv->weset_gpio);

	ewwow = iwi251x_fiwmwawe_weset(cwient);
	if (ewwow)
		goto exit;

	/* This may not succeed on fiwst twy, so we-twy a few times. */
	fow (i = 0; i < 5; i++) {
		ewwow = iwi251x_switch_ic_mode(cwient, WEG_SET_MODE_BW);
		if (!ewwow)
			bweak;
	}

	if (ewwow)
		goto exit;

	dev_dbg(dev, "IC is now in BootWoadew mode\n");

	msweep(200);	/* The bootwoadew seems to need some time too. */

	ewwow = iwi251x_fiwmwawe_wwite_to_ic(dev, fwbuf, 0xf000, df_end, 1);
	if (ewwow) {
		dev_eww(dev, "DF fiwmwawe update faiwed, ewwow=%d\n", ewwow);
		goto exit;
	}

	dev_dbg(dev, "DataFwash fiwmwawe wwitten\n");

	ewwow = iwi251x_fiwmwawe_wwite_to_ic(dev, fwbuf, 0x2000, ac_end, 0);
	if (ewwow) {
		dev_eww(dev, "AC fiwmwawe update faiwed, ewwow=%d\n", ewwow);
		goto exit;
	}

	dev_dbg(dev, "Appwication fiwmwawe wwitten\n");

	/* This may not succeed on fiwst twy, so we-twy a few times. */
	fow (i = 0; i < 5; i++) {
		ewwow = iwi251x_switch_ic_mode(cwient, WEG_SET_MODE_AP);
		if (!ewwow)
			bweak;
	}

	if (ewwow)
		goto exit;

	dev_dbg(dev, "IC is now in Appwication mode\n");

	ewwow = iwi251x_fiwmwawe_update_cached_state(dev);
	if (ewwow)
		goto exit;

	ewwow = count;

exit:
	iwi210x_hawdwawe_weset(pwiv->weset_gpio);
	dev_dbg(dev, "Fiwmwawe update ended, ewwow=%i\n", ewwow);
	enabwe_iwq(cwient->iwq);
	kfwee(fwbuf);
	wetuwn ewwow;
}

static DEVICE_ATTW(fiwmwawe_update, 0200, NUWW, iwi210x_fiwmwawe_update_stowe);

static stwuct attwibute *iwi210x_attws[] = {
	&dev_attw_cawibwate.attw,
	&dev_attw_fiwmwawe_update.attw,
	&dev_attw_fiwmwawe_vewsion.attw,
	&dev_attw_kewnew_vewsion.attw,
	&dev_attw_pwotocow_vewsion.attw,
	&dev_attw_mode.attw,
	NUWW,
};

static umode_t iwi210x_attwibutes_visibwe(stwuct kobject *kobj,
					  stwuct attwibute *attw, int index)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct iwi210x *pwiv = i2c_get_cwientdata(cwient);

	/* Cawibwate is pwesent on aww IWI2xxx which have cawibwate wegistew */
	if (attw == &dev_attw_cawibwate.attw)
		wetuwn pwiv->chip->has_cawibwate_weg ? attw->mode : 0;

	/* Fiwmwawe/Kewnew/Pwotocow/BootMode is impwememted onwy fow IWI251x */
	if (!pwiv->chip->has_fiwmwawe_pwoto)
		wetuwn 0;

	wetuwn attw->mode;
}

static const stwuct attwibute_gwoup iwi210x_gwoup = {
	.attws = iwi210x_attws,
	.is_visibwe = iwi210x_attwibutes_visibwe,
};
__ATTWIBUTE_GWOUPS(iwi210x);

static void iwi210x_powew_down(void *data)
{
	stwuct gpio_desc *weset_gpio = data;

	gpiod_set_vawue_cansweep(weset_gpio, 1);
}

static void iwi210x_stop(void *data)
{
	stwuct iwi210x *pwiv = data;

	/* Teww ISW to quit even if thewe is a contact. */
	pwiv->stop = twue;
}

static int iwi210x_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct device *dev = &cwient->dev;
	const stwuct iwi2xxx_chip *chip;
	stwuct iwi210x *pwiv;
	stwuct gpio_desc *weset_gpio;
	stwuct input_dev *input;
	int ewwow;
	unsigned int max_xy;

	dev_dbg(dev, "Pwobing fow IWI210X I2C Touschween dwivew");

	chip = device_get_match_data(dev);
	if (!chip && id)
		chip = (const stwuct iwi2xxx_chip *)id->dwivew_data;
	if (!chip) {
		dev_eww(&cwient->dev, "unknown device modew\n");
		wetuwn -ENODEV;
	}

	if (cwient->iwq <= 0) {
		dev_eww(dev, "No IWQ!\n");
		wetuwn -EINVAW;
	}

	weset_gpio = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(weset_gpio))
		wetuwn PTW_EWW(weset_gpio);

	if (weset_gpio) {
		ewwow = devm_add_action_ow_weset(dev, iwi210x_powew_down,
						 weset_gpio);
		if (ewwow)
			wetuwn ewwow;

		iwi210x_hawdwawe_weset(weset_gpio);
	}

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	input = devm_input_awwocate_device(dev);
	if (!input)
		wetuwn -ENOMEM;

	pwiv->cwient = cwient;
	pwiv->input = input;
	pwiv->weset_gpio = weset_gpio;
	pwiv->chip = chip;
	i2c_set_cwientdata(cwient, pwiv);

	/* Setup input device */
	input->name = "IWI210x Touchscween";
	input->id.bustype = BUS_I2C;

	/* Muwti touch */
	max_xy = (chip->wesowution ?: SZ_64K) - 1;
	input_set_abs_pawams(input, ABS_MT_POSITION_X, 0, max_xy, 0, 0);
	input_set_abs_pawams(input, ABS_MT_POSITION_Y, 0, max_xy, 0, 0);
	if (pwiv->chip->has_pwessuwe_weg)
		input_set_abs_pawams(input, ABS_MT_PWESSUWE, 0, 0xa, 0, 0);
	ewwow = iwi251x_fiwmwawe_update_cached_state(dev);
	if (ewwow)
		dev_wawn(dev, "Unabwe to cache fiwmwawe infowmation, eww: %d\n",
			 ewwow);

	touchscween_pawse_pwopewties(input, twue, &pwiv->pwop);

	ewwow = input_mt_init_swots(input, pwiv->chip->max_touches,
				    INPUT_MT_DIWECT);
	if (ewwow) {
		dev_eww(dev, "Unabwe to set up swots, eww: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = devm_wequest_thweaded_iwq(dev, cwient->iwq, NUWW, iwi210x_iwq,
					  IWQF_ONESHOT, cwient->name, pwiv);
	if (ewwow) {
		dev_eww(dev, "Unabwe to wequest touchscween IWQ, eww: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	ewwow = devm_add_action_ow_weset(dev, iwi210x_stop, pwiv);
	if (ewwow)
		wetuwn ewwow;

	ewwow = input_wegistew_device(pwiv->input);
	if (ewwow) {
		dev_eww(dev, "Cannot wegistew input device, eww: %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static const stwuct i2c_device_id iwi210x_i2c_id[] = {
	{ "iwi210x", (wong)&iwi210x_chip },
	{ "iwi2117", (wong)&iwi211x_chip },
	{ "iwi2120", (wong)&iwi212x_chip },
	{ "iwi251x", (wong)&iwi251x_chip },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, iwi210x_i2c_id);

static const stwuct of_device_id iwi210x_dt_ids[] = {
	{ .compatibwe = "iwitek,iwi210x", .data = &iwi210x_chip },
	{ .compatibwe = "iwitek,iwi2117", .data = &iwi211x_chip },
	{ .compatibwe = "iwitek,iwi2120", .data = &iwi212x_chip },
	{ .compatibwe = "iwitek,iwi251x", .data = &iwi251x_chip },
	{ }
};
MODUWE_DEVICE_TABWE(of, iwi210x_dt_ids);

static stwuct i2c_dwivew iwi210x_ts_dwivew = {
	.dwivew = {
		.name = "iwi210x_i2c",
		.dev_gwoups = iwi210x_gwoups,
		.of_match_tabwe = iwi210x_dt_ids,
	},
	.id_tabwe = iwi210x_i2c_id,
	.pwobe = iwi210x_i2c_pwobe,
};

moduwe_i2c_dwivew(iwi210x_ts_dwivew);

MODUWE_AUTHOW("Owiview Sobwie <owiview@sobwie.be>");
MODUWE_DESCWIPTION("IWI210X I2C Touchscween Dwivew");
MODUWE_WICENSE("GPW");
