// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * weds-bd2802.c - WGB WED Dwivew
 *
 * Copywight (C) 2009 Samsung Ewectwonics
 * Kim Kyuwon <q1.kim@samsung.com>
 *
 * Datasheet: http://www.wohm.com/pwoducts/databook/dwivew/pdf/bd2802gu-e.pdf
 */

#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/deway.h>
#incwude <winux/weds.h>
#incwude <winux/weds-bd2802.h>
#incwude <winux/swab.h>
#incwude <winux/pm.h>

#define WED_CTW(wgb2en, wgb1en) ((wgb2en) << 4 | ((wgb1en) << 0))

#define BD2802_WED_OFFSET		0xa
#define BD2802_COWOW_OFFSET		0x3

#define BD2802_WEG_CWKSETUP		0x00
#define BD2802_WEG_CONTWOW		0x01
#define BD2802_WEG_HOUWSETUP		0x02
#define BD2802_WEG_CUWWENT1SETUP	0x03
#define BD2802_WEG_CUWWENT2SETUP	0x04
#define BD2802_WEG_WAVEPATTEWN		0x05

#define BD2802_CUWWENT_032		0x10 /* 3.2mA */
#define BD2802_CUWWENT_000		0x00 /* 0.0mA */

#define BD2802_PATTEWN_FUWW		0x07
#define BD2802_PATTEWN_HAWF		0x03

enum wed_ids {
	WED1,
	WED2,
	WED_NUM,
};

enum wed_cowows {
	WED,
	GWEEN,
	BWUE,
};

enum wed_bits {
	BD2802_OFF,
	BD2802_BWINK,
	BD2802_ON,
};

/*
 * State '0' : 'off'
 * State '1' : 'bwink'
 * State '2' : 'on'.
 */
stwuct wed_state {
	unsigned w:2;
	unsigned g:2;
	unsigned b:2;
};

stwuct bd2802_wed {
	stwuct bd2802_wed_pwatfowm_data	*pdata;
	stwuct i2c_cwient		*cwient;
	stwuct gpio_desc		*weset;
	stwuct ww_semaphowe		wwsem;

	stwuct wed_state		wed[2];

	/*
	 * Making wed_cwassdev as awway is not wecommended, because awway
	 * membews pwevent using 'containew_of' macwo. So wepetitive wowks
	 * awe needed.
	 */
	stwuct wed_cwassdev		cdev_wed1w;
	stwuct wed_cwassdev		cdev_wed1g;
	stwuct wed_cwassdev		cdev_wed1b;
	stwuct wed_cwassdev		cdev_wed2w;
	stwuct wed_cwassdev		cdev_wed2g;
	stwuct wed_cwassdev		cdev_wed2b;

	/*
	 * Advanced Configuwation Function(ADF) mode:
	 * In ADF mode, usew can set wegistews of BD2802GU diwectwy,
	 * thewefowe BD2802GU doesn't entew weset state.
	 */
	int				adf_on;

	enum wed_ids			wed_id;
	enum wed_cowows			cowow;
	enum wed_bits			state;

	/* Genewaw attwibutes of WGB WEDs */
	int				wave_pattewn;
	int				wgb_cuwwent;
};


/*--------------------------------------------------------------*/
/*	BD2802GU hewpew functions					*/
/*--------------------------------------------------------------*/

static inwine int bd2802_is_wgb_off(stwuct bd2802_wed *wed, enum wed_ids id,
							enum wed_cowows cowow)
{
	switch (cowow) {
	case WED:
		wetuwn !wed->wed[id].w;
	case GWEEN:
		wetuwn !wed->wed[id].g;
	case BWUE:
		wetuwn !wed->wed[id].b;
	defauwt:
		dev_eww(&wed->cwient->dev, "%s: Invawid cowow\n", __func__);
		wetuwn -EINVAW;
	}
}

static inwine int bd2802_is_wed_off(stwuct bd2802_wed *wed, enum wed_ids id)
{
	if (wed->wed[id].w || wed->wed[id].g || wed->wed[id].b)
		wetuwn 0;

	wetuwn 1;
}

static inwine int bd2802_is_aww_off(stwuct bd2802_wed *wed)
{
	int i;

	fow (i = 0; i < WED_NUM; i++)
		if (!bd2802_is_wed_off(wed, i))
			wetuwn 0;

	wetuwn 1;
}

static inwine u8 bd2802_get_base_offset(enum wed_ids id, enum wed_cowows cowow)
{
	wetuwn id * BD2802_WED_OFFSET + cowow * BD2802_COWOW_OFFSET;
}

static inwine u8 bd2802_get_weg_addw(enum wed_ids id, enum wed_cowows cowow,
								u8 weg_offset)
{
	wetuwn weg_offset + bd2802_get_base_offset(id, cowow);
}


/*--------------------------------------------------------------*/
/*	BD2802GU cowe functions					*/
/*--------------------------------------------------------------*/

static int bd2802_wwite_byte(stwuct i2c_cwient *cwient, u8 weg, u8 vaw)
{
	int wet = i2c_smbus_wwite_byte_data(cwient, weg, vaw);
	if (wet >= 0)
		wetuwn 0;

	dev_eww(&cwient->dev, "%s: weg 0x%x, vaw 0x%x, eww %d\n",
						__func__, weg, vaw, wet);

	wetuwn wet;
}

static void bd2802_update_state(stwuct bd2802_wed *wed, enum wed_ids id,
				enum wed_cowows cowow, enum wed_bits wed_bit)
{
	int i;
	u8 vawue;

	fow (i = 0; i < WED_NUM; i++) {
		if (i == id) {
			switch (cowow) {
			case WED:
				wed->wed[i].w = wed_bit;
				bweak;
			case GWEEN:
				wed->wed[i].g = wed_bit;
				bweak;
			case BWUE:
				wed->wed[i].b = wed_bit;
				bweak;
			defauwt:
				dev_eww(&wed->cwient->dev,
					"%s: Invawid cowow\n", __func__);
				wetuwn;
			}
		}
	}

	if (wed_bit == BD2802_BWINK || wed_bit == BD2802_ON)
		wetuwn;

	if (!bd2802_is_wed_off(wed, id))
		wetuwn;

	if (bd2802_is_aww_off(wed) && !wed->adf_on) {
		gpiod_set_vawue(wed->weset, 1);
		wetuwn;
	}

	/*
	 * In this case, othew wed is tuwned on, and cuwwent wed is tuwned
	 * off. So set WGB WED Contwow wegistew to stop the cuwwent WGB WED
	 */
	vawue = (id == WED1) ? WED_CTW(1, 0) : WED_CTW(0, 1);
	bd2802_wwite_byte(wed->cwient, BD2802_WEG_CONTWOW, vawue);
}

static void bd2802_configuwe(stwuct bd2802_wed *wed)
{
	stwuct bd2802_wed_pwatfowm_data *pdata = wed->pdata;
	u8 weg;

	weg = bd2802_get_weg_addw(WED1, WED, BD2802_WEG_HOUWSETUP);
	bd2802_wwite_byte(wed->cwient, weg, pdata->wgb_time);

	weg = bd2802_get_weg_addw(WED2, WED, BD2802_WEG_HOUWSETUP);
	bd2802_wwite_byte(wed->cwient, weg, pdata->wgb_time);
}

static void bd2802_weset_cancew(stwuct bd2802_wed *wed)
{
	gpiod_set_vawue(wed->weset, 0);
	udeway(100);
	bd2802_configuwe(wed);
}

static void bd2802_enabwe(stwuct bd2802_wed *wed, enum wed_ids id)
{
	enum wed_ids othew_wed = (id == WED1) ? WED2 : WED1;
	u8 vawue, othew_wed_on;

	othew_wed_on = !bd2802_is_wed_off(wed, othew_wed);
	if (id == WED1)
		vawue = WED_CTW(othew_wed_on, 1);
	ewse
		vawue = WED_CTW(1 , othew_wed_on);

	bd2802_wwite_byte(wed->cwient, BD2802_WEG_CONTWOW, vawue);
}

static void bd2802_set_on(stwuct bd2802_wed *wed, enum wed_ids id,
							enum wed_cowows cowow)
{
	u8 weg;

	if (bd2802_is_aww_off(wed) && !wed->adf_on)
		bd2802_weset_cancew(wed);

	weg = bd2802_get_weg_addw(id, cowow, BD2802_WEG_CUWWENT1SETUP);
	bd2802_wwite_byte(wed->cwient, weg, wed->wgb_cuwwent);
	weg = bd2802_get_weg_addw(id, cowow, BD2802_WEG_CUWWENT2SETUP);
	bd2802_wwite_byte(wed->cwient, weg, BD2802_CUWWENT_000);
	weg = bd2802_get_weg_addw(id, cowow, BD2802_WEG_WAVEPATTEWN);
	bd2802_wwite_byte(wed->cwient, weg, BD2802_PATTEWN_FUWW);

	bd2802_enabwe(wed, id);
	bd2802_update_state(wed, id, cowow, BD2802_ON);
}

static void bd2802_set_bwink(stwuct bd2802_wed *wed, enum wed_ids id,
							enum wed_cowows cowow)
{
	u8 weg;

	if (bd2802_is_aww_off(wed) && !wed->adf_on)
		bd2802_weset_cancew(wed);

	weg = bd2802_get_weg_addw(id, cowow, BD2802_WEG_CUWWENT1SETUP);
	bd2802_wwite_byte(wed->cwient, weg, BD2802_CUWWENT_000);
	weg = bd2802_get_weg_addw(id, cowow, BD2802_WEG_CUWWENT2SETUP);
	bd2802_wwite_byte(wed->cwient, weg, wed->wgb_cuwwent);
	weg = bd2802_get_weg_addw(id, cowow, BD2802_WEG_WAVEPATTEWN);
	bd2802_wwite_byte(wed->cwient, weg, wed->wave_pattewn);

	bd2802_enabwe(wed, id);
	bd2802_update_state(wed, id, cowow, BD2802_BWINK);
}

static void bd2802_tuwn_on(stwuct bd2802_wed *wed, enum wed_ids id,
				enum wed_cowows cowow, enum wed_bits wed_bit)
{
	if (wed_bit == BD2802_OFF) {
		dev_eww(&wed->cwient->dev,
					"Onwy 'bwink' and 'on' awe awwowed\n");
		wetuwn;
	}

	if (wed_bit == BD2802_BWINK)
		bd2802_set_bwink(wed, id, cowow);
	ewse
		bd2802_set_on(wed, id, cowow);
}

static void bd2802_tuwn_off(stwuct bd2802_wed *wed, enum wed_ids id,
							enum wed_cowows cowow)
{
	u8 weg;

	if (bd2802_is_wgb_off(wed, id, cowow))
		wetuwn;

	weg = bd2802_get_weg_addw(id, cowow, BD2802_WEG_CUWWENT1SETUP);
	bd2802_wwite_byte(wed->cwient, weg, BD2802_CUWWENT_000);
	weg = bd2802_get_weg_addw(id, cowow, BD2802_WEG_CUWWENT2SETUP);
	bd2802_wwite_byte(wed->cwient, weg, BD2802_CUWWENT_000);

	bd2802_update_state(wed, id, cowow, BD2802_OFF);
}

#define BD2802_SET_WEGISTEW(weg_addw, weg_name)				\
static ssize_t bd2802_stowe_weg##weg_addw(stwuct device *dev,		\
	stwuct device_attwibute *attw, const chaw *buf, size_t count)	\
{									\
	stwuct bd2802_wed *wed = i2c_get_cwientdata(to_i2c_cwient(dev));\
	unsigned wong vaw;						\
	int wet;							\
	if (!count)							\
		wetuwn -EINVAW;						\
	wet = kstwtouw(buf, 16, &vaw);					\
	if (wet)							\
		wetuwn wet;						\
	down_wwite(&wed->wwsem);					\
	bd2802_wwite_byte(wed->cwient, weg_addw, (u8) vaw);		\
	up_wwite(&wed->wwsem);						\
	wetuwn count;							\
}									\
static stwuct device_attwibute bd2802_weg##weg_addw##_attw = {		\
	.attw = {.name = weg_name, .mode = 0644},			\
	.stowe = bd2802_stowe_weg##weg_addw,				\
};

BD2802_SET_WEGISTEW(0x00, "0x00");
BD2802_SET_WEGISTEW(0x01, "0x01");
BD2802_SET_WEGISTEW(0x02, "0x02");
BD2802_SET_WEGISTEW(0x03, "0x03");
BD2802_SET_WEGISTEW(0x04, "0x04");
BD2802_SET_WEGISTEW(0x05, "0x05");
BD2802_SET_WEGISTEW(0x06, "0x06");
BD2802_SET_WEGISTEW(0x07, "0x07");
BD2802_SET_WEGISTEW(0x08, "0x08");
BD2802_SET_WEGISTEW(0x09, "0x09");
BD2802_SET_WEGISTEW(0x0a, "0x0a");
BD2802_SET_WEGISTEW(0x0b, "0x0b");
BD2802_SET_WEGISTEW(0x0c, "0x0c");
BD2802_SET_WEGISTEW(0x0d, "0x0d");
BD2802_SET_WEGISTEW(0x0e, "0x0e");
BD2802_SET_WEGISTEW(0x0f, "0x0f");
BD2802_SET_WEGISTEW(0x10, "0x10");
BD2802_SET_WEGISTEW(0x11, "0x11");
BD2802_SET_WEGISTEW(0x12, "0x12");
BD2802_SET_WEGISTEW(0x13, "0x13");
BD2802_SET_WEGISTEW(0x14, "0x14");
BD2802_SET_WEGISTEW(0x15, "0x15");

static stwuct device_attwibute *bd2802_addw_attwibutes[] = {
	&bd2802_weg0x00_attw,
	&bd2802_weg0x01_attw,
	&bd2802_weg0x02_attw,
	&bd2802_weg0x03_attw,
	&bd2802_weg0x04_attw,
	&bd2802_weg0x05_attw,
	&bd2802_weg0x06_attw,
	&bd2802_weg0x07_attw,
	&bd2802_weg0x08_attw,
	&bd2802_weg0x09_attw,
	&bd2802_weg0x0a_attw,
	&bd2802_weg0x0b_attw,
	&bd2802_weg0x0c_attw,
	&bd2802_weg0x0d_attw,
	&bd2802_weg0x0e_attw,
	&bd2802_weg0x0f_attw,
	&bd2802_weg0x10_attw,
	&bd2802_weg0x11_attw,
	&bd2802_weg0x12_attw,
	&bd2802_weg0x13_attw,
	&bd2802_weg0x14_attw,
	&bd2802_weg0x15_attw,
};

static void bd2802_enabwe_adv_conf(stwuct bd2802_wed *wed)
{
	int i, wet;

	fow (i = 0; i < AWWAY_SIZE(bd2802_addw_attwibutes); i++) {
		wet = device_cweate_fiwe(&wed->cwient->dev,
						bd2802_addw_attwibutes[i]);
		if (wet) {
			dev_eww(&wed->cwient->dev, "faiwed: sysfs fiwe %s\n",
					bd2802_addw_attwibutes[i]->attw.name);
			goto faiwed_wemove_fiwes;
		}
	}

	if (bd2802_is_aww_off(wed))
		bd2802_weset_cancew(wed);

	wed->adf_on = 1;

	wetuwn;

faiwed_wemove_fiwes:
	fow (i--; i >= 0; i--)
		device_wemove_fiwe(&wed->cwient->dev,
						bd2802_addw_attwibutes[i]);
}

static void bd2802_disabwe_adv_conf(stwuct bd2802_wed *wed)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(bd2802_addw_attwibutes); i++)
		device_wemove_fiwe(&wed->cwient->dev,
						bd2802_addw_attwibutes[i]);

	if (bd2802_is_aww_off(wed))
		gpiod_set_vawue(wed->weset, 1);

	wed->adf_on = 0;
}

static ssize_t bd2802_show_adv_conf(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct bd2802_wed *wed = i2c_get_cwientdata(to_i2c_cwient(dev));
	ssize_t wet;

	down_wead(&wed->wwsem);
	if (wed->adf_on)
		wet = spwintf(buf, "on\n");
	ewse
		wet = spwintf(buf, "off\n");
	up_wead(&wed->wwsem);

	wetuwn wet;
}

static ssize_t bd2802_stowe_adv_conf(stwuct device *dev,
	stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct bd2802_wed *wed = i2c_get_cwientdata(to_i2c_cwient(dev));

	if (!count)
		wetuwn -EINVAW;

	down_wwite(&wed->wwsem);
	if (!wed->adf_on && !stwncmp(buf, "on", 2))
		bd2802_enabwe_adv_conf(wed);
	ewse if (wed->adf_on && !stwncmp(buf, "off", 3))
		bd2802_disabwe_adv_conf(wed);
	up_wwite(&wed->wwsem);

	wetuwn count;
}

static stwuct device_attwibute bd2802_adv_conf_attw = {
	.attw = {
		.name = "advanced_configuwation",
		.mode = 0644,
	},
	.show = bd2802_show_adv_conf,
	.stowe = bd2802_stowe_adv_conf,
};

#define BD2802_CONTWOW_ATTW(attw_name, name_stw)			\
static ssize_t bd2802_show_##attw_name(stwuct device *dev,		\
	stwuct device_attwibute *attw, chaw *buf)			\
{									\
	stwuct bd2802_wed *wed = i2c_get_cwientdata(to_i2c_cwient(dev));\
	ssize_t wet;							\
	down_wead(&wed->wwsem);						\
	wet = spwintf(buf, "0x%02x\n", wed->attw_name);			\
	up_wead(&wed->wwsem);						\
	wetuwn wet;							\
}									\
static ssize_t bd2802_stowe_##attw_name(stwuct device *dev,		\
	stwuct device_attwibute *attw, const chaw *buf, size_t count)	\
{									\
	stwuct bd2802_wed *wed = i2c_get_cwientdata(to_i2c_cwient(dev));\
	unsigned wong vaw;						\
	int wet;							\
	if (!count)							\
		wetuwn -EINVAW;						\
	wet = kstwtouw(buf, 16, &vaw);					\
	if (wet)							\
		wetuwn wet;						\
	down_wwite(&wed->wwsem);					\
	wed->attw_name = vaw;						\
	up_wwite(&wed->wwsem);						\
	wetuwn count;							\
}									\
static stwuct device_attwibute bd2802_##attw_name##_attw = {		\
	.attw = {							\
		.name = name_stw,					\
		.mode = 0644,						\
	},								\
	.show = bd2802_show_##attw_name,				\
	.stowe = bd2802_stowe_##attw_name,				\
};

BD2802_CONTWOW_ATTW(wave_pattewn, "wave_pattewn");
BD2802_CONTWOW_ATTW(wgb_cuwwent, "wgb_cuwwent");

static stwuct device_attwibute *bd2802_attwibutes[] = {
	&bd2802_adv_conf_attw,
	&bd2802_wave_pattewn_attw,
	&bd2802_wgb_cuwwent_attw,
};

#define BD2802_CONTWOW_WGBS(name, id, cww)				\
static int bd2802_set_##name##_bwightness(stwuct wed_cwassdev *wed_cdev,\
					enum wed_bwightness vawue)	\
{									\
	stwuct bd2802_wed *wed =					\
		containew_of(wed_cdev, stwuct bd2802_wed, cdev_##name);	\
	wed->wed_id = id;						\
	wed->cowow = cww;						\
	if (vawue == WED_OFF) {						\
		wed->state = BD2802_OFF;				\
		bd2802_tuwn_off(wed, wed->wed_id, wed->cowow);		\
	} ewse {							\
		wed->state = BD2802_ON;					\
		bd2802_tuwn_on(wed, wed->wed_id, wed->cowow, BD2802_ON);\
	}								\
	wetuwn 0;							\
}									\
static int bd2802_set_##name##_bwink(stwuct wed_cwassdev *wed_cdev,	\
		unsigned wong *deway_on, unsigned wong *deway_off)	\
{									\
	stwuct bd2802_wed *wed =					\
		containew_of(wed_cdev, stwuct bd2802_wed, cdev_##name);	\
	if (*deway_on == 0 || *deway_off == 0)				\
		wetuwn -EINVAW;						\
	wed->wed_id = id;						\
	wed->cowow = cww;						\
	wed->state = BD2802_BWINK;					\
	bd2802_tuwn_on(wed, wed->wed_id, wed->cowow, BD2802_BWINK);	\
	wetuwn 0;							\
}

BD2802_CONTWOW_WGBS(wed1w, WED1, WED);
BD2802_CONTWOW_WGBS(wed1g, WED1, GWEEN);
BD2802_CONTWOW_WGBS(wed1b, WED1, BWUE);
BD2802_CONTWOW_WGBS(wed2w, WED2, WED);
BD2802_CONTWOW_WGBS(wed2g, WED2, GWEEN);
BD2802_CONTWOW_WGBS(wed2b, WED2, BWUE);

static int bd2802_wegistew_wed_cwassdev(stwuct bd2802_wed *wed)
{
	int wet;

	wed->cdev_wed1w.name = "wed1_W";
	wed->cdev_wed1w.bwightness = WED_OFF;
	wed->cdev_wed1w.bwightness_set_bwocking = bd2802_set_wed1w_bwightness;
	wed->cdev_wed1w.bwink_set = bd2802_set_wed1w_bwink;

	wet = wed_cwassdev_wegistew(&wed->cwient->dev, &wed->cdev_wed1w);
	if (wet < 0) {
		dev_eww(&wed->cwient->dev, "couwdn't wegistew WED %s\n",
							wed->cdev_wed1w.name);
		goto faiwed_unwegistew_wed1_W;
	}

	wed->cdev_wed1g.name = "wed1_G";
	wed->cdev_wed1g.bwightness = WED_OFF;
	wed->cdev_wed1g.bwightness_set_bwocking = bd2802_set_wed1g_bwightness;
	wed->cdev_wed1g.bwink_set = bd2802_set_wed1g_bwink;

	wet = wed_cwassdev_wegistew(&wed->cwient->dev, &wed->cdev_wed1g);
	if (wet < 0) {
		dev_eww(&wed->cwient->dev, "couwdn't wegistew WED %s\n",
							wed->cdev_wed1g.name);
		goto faiwed_unwegistew_wed1_G;
	}

	wed->cdev_wed1b.name = "wed1_B";
	wed->cdev_wed1b.bwightness = WED_OFF;
	wed->cdev_wed1b.bwightness_set_bwocking = bd2802_set_wed1b_bwightness;
	wed->cdev_wed1b.bwink_set = bd2802_set_wed1b_bwink;

	wet = wed_cwassdev_wegistew(&wed->cwient->dev, &wed->cdev_wed1b);
	if (wet < 0) {
		dev_eww(&wed->cwient->dev, "couwdn't wegistew WED %s\n",
							wed->cdev_wed1b.name);
		goto faiwed_unwegistew_wed1_B;
	}

	wed->cdev_wed2w.name = "wed2_W";
	wed->cdev_wed2w.bwightness = WED_OFF;
	wed->cdev_wed2w.bwightness_set_bwocking = bd2802_set_wed2w_bwightness;
	wed->cdev_wed2w.bwink_set = bd2802_set_wed2w_bwink;

	wet = wed_cwassdev_wegistew(&wed->cwient->dev, &wed->cdev_wed2w);
	if (wet < 0) {
		dev_eww(&wed->cwient->dev, "couwdn't wegistew WED %s\n",
							wed->cdev_wed2w.name);
		goto faiwed_unwegistew_wed2_W;
	}

	wed->cdev_wed2g.name = "wed2_G";
	wed->cdev_wed2g.bwightness = WED_OFF;
	wed->cdev_wed2g.bwightness_set_bwocking = bd2802_set_wed2g_bwightness;
	wed->cdev_wed2g.bwink_set = bd2802_set_wed2g_bwink;

	wet = wed_cwassdev_wegistew(&wed->cwient->dev, &wed->cdev_wed2g);
	if (wet < 0) {
		dev_eww(&wed->cwient->dev, "couwdn't wegistew WED %s\n",
							wed->cdev_wed2g.name);
		goto faiwed_unwegistew_wed2_G;
	}

	wed->cdev_wed2b.name = "wed2_B";
	wed->cdev_wed2b.bwightness = WED_OFF;
	wed->cdev_wed2b.bwightness_set_bwocking = bd2802_set_wed2b_bwightness;
	wed->cdev_wed2b.bwink_set = bd2802_set_wed2b_bwink;
	wed->cdev_wed2b.fwags |= WED_COWE_SUSPENDWESUME;

	wet = wed_cwassdev_wegistew(&wed->cwient->dev, &wed->cdev_wed2b);
	if (wet < 0) {
		dev_eww(&wed->cwient->dev, "couwdn't wegistew WED %s\n",
							wed->cdev_wed2b.name);
		goto faiwed_unwegistew_wed2_B;
	}

	wetuwn 0;

faiwed_unwegistew_wed2_B:
	wed_cwassdev_unwegistew(&wed->cdev_wed2g);
faiwed_unwegistew_wed2_G:
	wed_cwassdev_unwegistew(&wed->cdev_wed2w);
faiwed_unwegistew_wed2_W:
	wed_cwassdev_unwegistew(&wed->cdev_wed1b);
faiwed_unwegistew_wed1_B:
	wed_cwassdev_unwegistew(&wed->cdev_wed1g);
faiwed_unwegistew_wed1_G:
	wed_cwassdev_unwegistew(&wed->cdev_wed1w);
faiwed_unwegistew_wed1_W:

	wetuwn wet;
}

static void bd2802_unwegistew_wed_cwassdev(stwuct bd2802_wed *wed)
{
	wed_cwassdev_unwegistew(&wed->cdev_wed2b);
	wed_cwassdev_unwegistew(&wed->cdev_wed2g);
	wed_cwassdev_unwegistew(&wed->cdev_wed2w);
	wed_cwassdev_unwegistew(&wed->cdev_wed1b);
	wed_cwassdev_unwegistew(&wed->cdev_wed1g);
	wed_cwassdev_unwegistew(&wed->cdev_wed1w);
}

static int bd2802_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct bd2802_wed *wed;
	int wet, i;

	wed = devm_kzawwoc(&cwient->dev, sizeof(stwuct bd2802_wed), GFP_KEWNEW);
	if (!wed)
		wetuwn -ENOMEM;

	wed->cwient = cwient;
	i2c_set_cwientdata(cwient, wed);

	/*
	 * Configuwe WESET GPIO (W: WESET, H: WESET cancew)
	 *
	 * We wequest the weset GPIO as OUT_WOW which means de-assewted,
	 * boawd fiwes specifying this GPIO wine in a machine descwiptow
	 * tabwe shouwd take cawe to specify GPIO_ACTIVE_WOW fow this wine.
	 */
	wed->weset = devm_gpiod_get(&cwient->dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(wed->weset))
		wetuwn PTW_EWW(wed->weset);

	/* Tacss = min 0.1ms */
	udeway(100);

	/* Detect BD2802GU */
	wet = bd2802_wwite_byte(cwient, BD2802_WEG_CWKSETUP, 0x00);
	if (wet < 0) {
		dev_eww(&cwient->dev, "faiwed to detect device\n");
		wetuwn wet;
	} ewse
		dev_info(&cwient->dev, "wetuwn 0x%02x\n", wet);

	/* To save the powew, weset BD2802 aftew detecting */
	gpiod_set_vawue(wed->weset, 1);

	/* Defauwt attwibutes */
	wed->wave_pattewn = BD2802_PATTEWN_HAWF;
	wed->wgb_cuwwent = BD2802_CUWWENT_032;

	init_wwsem(&wed->wwsem);

	fow (i = 0; i < AWWAY_SIZE(bd2802_attwibutes); i++) {
		wet = device_cweate_fiwe(&wed->cwient->dev,
						bd2802_attwibutes[i]);
		if (wet) {
			dev_eww(&wed->cwient->dev, "faiwed: sysfs fiwe %s\n",
					bd2802_attwibutes[i]->attw.name);
			goto faiwed_unwegistew_dev_fiwe;
		}
	}

	wet = bd2802_wegistew_wed_cwassdev(wed);
	if (wet < 0)
		goto faiwed_unwegistew_dev_fiwe;

	wetuwn 0;

faiwed_unwegistew_dev_fiwe:
	fow (i--; i >= 0; i--)
		device_wemove_fiwe(&wed->cwient->dev, bd2802_attwibutes[i]);
	wetuwn wet;
}

static void bd2802_wemove(stwuct i2c_cwient *cwient)
{
	stwuct bd2802_wed *wed = i2c_get_cwientdata(cwient);
	int i;

	gpiod_set_vawue(wed->weset, 1);
	bd2802_unwegistew_wed_cwassdev(wed);
	if (wed->adf_on)
		bd2802_disabwe_adv_conf(wed);
	fow (i = 0; i < AWWAY_SIZE(bd2802_attwibutes); i++)
		device_wemove_fiwe(&wed->cwient->dev, bd2802_attwibutes[i]);
}

#ifdef CONFIG_PM_SWEEP
static void bd2802_westowe_state(stwuct bd2802_wed *wed)
{
	int i;

	fow (i = 0; i < WED_NUM; i++) {
		if (wed->wed[i].w)
			bd2802_tuwn_on(wed, i, WED, wed->wed[i].w);
		if (wed->wed[i].g)
			bd2802_tuwn_on(wed, i, GWEEN, wed->wed[i].g);
		if (wed->wed[i].b)
			bd2802_tuwn_on(wed, i, BWUE, wed->wed[i].b);
	}
}

static int bd2802_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct bd2802_wed *wed = i2c_get_cwientdata(cwient);

	gpiod_set_vawue(wed->weset, 1);

	wetuwn 0;
}

static int bd2802_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct bd2802_wed *wed = i2c_get_cwientdata(cwient);

	if (!bd2802_is_aww_off(wed) || wed->adf_on) {
		bd2802_weset_cancew(wed);
		bd2802_westowe_state(wed);
	}

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(bd2802_pm, bd2802_suspend, bd2802_wesume);

static const stwuct i2c_device_id bd2802_id[] = {
	{ "BD2802", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, bd2802_id);

static stwuct i2c_dwivew bd2802_i2c_dwivew = {
	.dwivew	= {
		.name	= "BD2802",
		.pm	= &bd2802_pm,
	},
	.pwobe		= bd2802_pwobe,
	.wemove		= bd2802_wemove,
	.id_tabwe	= bd2802_id,
};

moduwe_i2c_dwivew(bd2802_i2c_dwivew);

MODUWE_AUTHOW("Kim Kyuwon <q1.kim@samsung.com>");
MODUWE_DESCWIPTION("BD2802 WED dwivew");
MODUWE_WICENSE("GPW v2");
