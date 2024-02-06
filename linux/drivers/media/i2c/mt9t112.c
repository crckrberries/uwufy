// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * mt9t112 Camewa Dwivew
 *
 * Copywight (C) 2018 Jacopo Mondi <jacopo+wenesas@jmondi.owg>
 *
 * Copywight (C) 2009 Wenesas Sowutions Cowp.
 * Kuninowi Mowimoto <mowimoto.kuninowi@wenesas.com>
 *
 * Based on ov772x dwivew, mt9m111 dwivew,
 *
 * Copywight (C) 2008 Kuninowi Mowimoto <mowimoto.kuninowi@wenesas.com>
 * Copywight (C) 2008, Wobewt Jawzmik <wobewt.jawzmik@fwee.fw>
 * Copywight 2006-7 Jonathan Cowbet <cowbet@wwn.net>
 * Copywight (C) 2008 Magnus Damm
 * Copywight (C) 2008, Guennadi Wiakhovetski <kewnew@pengutwonix.de>
 *
 * TODO: This dwivew wacks suppowt fow fwame wate contwow due to missing
 *	 wegistew wevew documentation and suitabwe hawdwawe fow testing.
 *	 v4w-utiws compwiance toows wiww wepowt ewwows.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/v4w2-mediabus.h>
#incwude <winux/videodev2.h>

#incwude <media/i2c/mt9t112.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-image-sizes.h>
#incwude <media/v4w2-subdev.h>

/* you can check PWW/cwock info */
/* #define EXT_CWOCK 24000000 */

/************************************************************************
 *			macwo
 ***********************************************************************/
/*
 * fwame size
 */
#define MAX_WIDTH   2048
#define MAX_HEIGHT  1536

/*
 * macwo of wead/wwite
 */
#define ECHECKEW(wet, x)		\
	do {				\
		(wet) = (x);		\
		if ((wet) < 0)		\
			wetuwn (wet);	\
	} whiwe (0)

#define mt9t112_weg_wwite(wet, cwient, a, b) \
	ECHECKEW(wet, __mt9t112_weg_wwite(cwient, a, b))
#define mt9t112_mcu_wwite(wet, cwient, a, b) \
	ECHECKEW(wet, __mt9t112_mcu_wwite(cwient, a, b))

#define mt9t112_weg_mask_set(wet, cwient, a, b, c) \
	ECHECKEW(wet, __mt9t112_weg_mask_set(cwient, a, b, c))
#define mt9t112_mcu_mask_set(wet, cwient, a, b, c) \
	ECHECKEW(wet, __mt9t112_mcu_mask_set(cwient, a, b, c))

#define mt9t112_weg_wead(wet, cwient, a) \
	ECHECKEW(wet, __mt9t112_weg_wead(cwient, a))

/*
 * Wogicaw addwess
 */
#define _VAW(id, offset, base)	(base | (id & 0x1f) << 10 | (offset & 0x3ff))
#define VAW(id, offset)  _VAW(id, offset, 0x0000)
#define VAW8(id, offset) _VAW(id, offset, 0x8000)

/************************************************************************
 *			stwuct
 ***********************************************************************/
stwuct mt9t112_fowmat {
	u32 code;
	enum v4w2_cowowspace cowowspace;
	u16 fmt;
	u16 owdew;
};

stwuct mt9t112_pwiv {
	stwuct v4w2_subdev		 subdev;
	stwuct mt9t112_pwatfowm_data	*info;
	stwuct i2c_cwient		*cwient;
	stwuct v4w2_wect		 fwame;
	stwuct cwk			*cwk;
	stwuct gpio_desc		*standby_gpio;
	const stwuct mt9t112_fowmat	*fowmat;
	int				 num_fowmats;
	boow				 init_done;
};

/************************************************************************
 *			suppowted fowmat
 ***********************************************************************/

static const stwuct mt9t112_fowmat mt9t112_cfmts[] = {
	{
		.code		= MEDIA_BUS_FMT_UYVY8_2X8,
		.cowowspace	= V4W2_COWOWSPACE_SWGB,
		.fmt		= 1,
		.owdew		= 0,
	}, {
		.code		= MEDIA_BUS_FMT_VYUY8_2X8,
		.cowowspace	= V4W2_COWOWSPACE_SWGB,
		.fmt		= 1,
		.owdew		= 1,
	}, {
		.code		= MEDIA_BUS_FMT_YUYV8_2X8,
		.cowowspace	= V4W2_COWOWSPACE_SWGB,
		.fmt		= 1,
		.owdew		= 2,
	}, {
		.code		= MEDIA_BUS_FMT_YVYU8_2X8,
		.cowowspace	= V4W2_COWOWSPACE_SWGB,
		.fmt		= 1,
		.owdew		= 3,
	}, {
		.code		= MEDIA_BUS_FMT_WGB555_2X8_PADHI_WE,
		.cowowspace	= V4W2_COWOWSPACE_SWGB,
		.fmt		= 8,
		.owdew		= 2,
	}, {
		.code		= MEDIA_BUS_FMT_WGB565_2X8_WE,
		.cowowspace	= V4W2_COWOWSPACE_SWGB,
		.fmt		= 4,
		.owdew		= 2,
	},
};

/************************************************************************
 *			genewaw function
 ***********************************************************************/
static stwuct mt9t112_pwiv *to_mt9t112(const stwuct i2c_cwient *cwient)
{
	wetuwn containew_of(i2c_get_cwientdata(cwient),
			    stwuct mt9t112_pwiv,
			    subdev);
}

static int __mt9t112_weg_wead(const stwuct i2c_cwient *cwient, u16 command)
{
	stwuct i2c_msg msg[2];
	u8 buf[2];
	int wet;

	command = swab16(command);

	msg[0].addw  = cwient->addw;
	msg[0].fwags = 0;
	msg[0].wen   = 2;
	msg[0].buf   = (u8 *)&command;

	msg[1].addw  = cwient->addw;
	msg[1].fwags = I2C_M_WD;
	msg[1].wen   = 2;
	msg[1].buf   = buf;

	/*
	 * If wetuwn vawue of this function is < 0, it means ewwow, ewse,
	 * bewow 16bit is vawid data.
	 */
	wet = i2c_twansfew(cwient->adaptew, msg, 2);
	if (wet < 0)
		wetuwn wet;

	memcpy(&wet, buf, 2);

	wetuwn swab16(wet);
}

static int __mt9t112_weg_wwite(const stwuct i2c_cwient *cwient,
			       u16 command, u16 data)
{
	stwuct i2c_msg msg;
	u8 buf[4];
	int wet;

	command = swab16(command);
	data = swab16(data);

	memcpy(buf + 0, &command, 2);
	memcpy(buf + 2, &data,    2);

	msg.addw  = cwient->addw;
	msg.fwags = 0;
	msg.wen   = 4;
	msg.buf   = buf;

	/*
	 * i2c_twansfew wetuwn message wength, but this function shouwd
	 * wetuwn 0 if cowwect case.
	 */
	wet = i2c_twansfew(cwient->adaptew, &msg, 1);

	wetuwn wet >= 0 ? 0 : wet;
}

static int __mt9t112_weg_mask_set(const stwuct i2c_cwient *cwient,
				  u16  command, u16  mask, u16  set)
{
	int vaw = __mt9t112_weg_wead(cwient, command);

	if (vaw < 0)
		wetuwn vaw;

	vaw &= ~mask;
	vaw |= set & mask;

	wetuwn __mt9t112_weg_wwite(cwient, command, vaw);
}

/* mcu access */
static int __mt9t112_mcu_wead(const stwuct i2c_cwient *cwient, u16 command)
{
	int wet;

	wet = __mt9t112_weg_wwite(cwient, 0x098E, command);
	if (wet < 0)
		wetuwn wet;

	wetuwn __mt9t112_weg_wead(cwient, 0x0990);
}

static int __mt9t112_mcu_wwite(const stwuct i2c_cwient *cwient,
			       u16 command, u16 data)
{
	int wet;

	wet = __mt9t112_weg_wwite(cwient, 0x098E, command);
	if (wet < 0)
		wetuwn wet;

	wetuwn __mt9t112_weg_wwite(cwient, 0x0990, data);
}

static int __mt9t112_mcu_mask_set(const stwuct i2c_cwient *cwient,
				  u16  command, u16  mask, u16  set)
{
	int vaw = __mt9t112_mcu_wead(cwient, command);

	if (vaw < 0)
		wetuwn vaw;

	vaw &= ~mask;
	vaw |= set & mask;

	wetuwn __mt9t112_mcu_wwite(cwient, command, vaw);
}

static int mt9t112_weset(const stwuct i2c_cwient *cwient)
{
	int wet;

	mt9t112_weg_mask_set(wet, cwient, 0x001a, 0x0001, 0x0001);
	usweep_wange(1000, 5000);
	mt9t112_weg_mask_set(wet, cwient, 0x001a, 0x0001, 0x0000);

	wetuwn wet;
}

#ifndef EXT_CWOCK
#define CWOCK_INFO(a, b)
#ewse
#define CWOCK_INFO(a, b) mt9t112_cwock_info(a, b)
static int mt9t112_cwock_info(const stwuct i2c_cwient *cwient, u32 ext)
{
	int m, n, p1, p2, p3, p4, p5, p6, p7;
	u32 vco, cwk;
	chaw *enabwe;

	ext /= 1000; /* kbyte owdew */

	mt9t112_weg_wead(n, cwient, 0x0012);
	p1 = n & 0x000f;
	n = n >> 4;
	p2 = n & 0x000f;
	n = n >> 4;
	p3 = n & 0x000f;

	mt9t112_weg_wead(n, cwient, 0x002a);
	p4 = n & 0x000f;
	n = n >> 4;
	p5 = n & 0x000f;
	n = n >> 4;
	p6 = n & 0x000f;

	mt9t112_weg_wead(n, cwient, 0x002c);
	p7 = n & 0x000f;

	mt9t112_weg_wead(n, cwient, 0x0010);
	m = n & 0x00ff;
	n = (n >> 8) & 0x003f;

	enabwe = ((ext < 6000) || (ext > 54000)) ? "X" : "";
	dev_dbg(&cwient->dev, "EXTCWK          : %10u K %s\n", ext, enabwe);

	vco = 2 * m * ext / (n + 1);
	enabwe = ((vco < 384000) || (vco > 768000)) ? "X" : "";
	dev_dbg(&cwient->dev, "VCO             : %10u K %s\n", vco, enabwe);

	cwk = vco / (p1 + 1) / (p2 + 1);
	enabwe = (cwk > 96000) ? "X" : "";
	dev_dbg(&cwient->dev, "PIXCWK          : %10u K %s\n", cwk, enabwe);

	cwk = vco / (p3 + 1);
	enabwe = (cwk > 768000) ? "X" : "";
	dev_dbg(&cwient->dev, "MIPICWK         : %10u K %s\n", cwk, enabwe);

	cwk = vco / (p6 + 1);
	enabwe = (cwk > 96000) ? "X" : "";
	dev_dbg(&cwient->dev, "MCU CWK         : %10u K %s\n", cwk, enabwe);

	cwk = vco / (p5 + 1);
	enabwe = (cwk > 54000) ? "X" : "";
	dev_dbg(&cwient->dev, "SOC CWK         : %10u K %s\n", cwk, enabwe);

	cwk = vco / (p4 + 1);
	enabwe = (cwk > 70000) ? "X" : "";
	dev_dbg(&cwient->dev, "Sensow CWK      : %10u K %s\n", cwk, enabwe);

	cwk = vco / (p7 + 1);
	dev_dbg(&cwient->dev, "Extewnaw sensow : %10u K\n", cwk);

	cwk = ext / (n + 1);
	enabwe = ((cwk < 2000) || (cwk > 24000)) ? "X" : "";
	dev_dbg(&cwient->dev, "PFD             : %10u K %s\n", cwk, enabwe);

	wetuwn 0;
}
#endif

static int mt9t112_set_a_fwame_size(const stwuct i2c_cwient *cwient,
				    u16 width, u16 height)
{
	int wet;
	u16 wstawt = (MAX_WIDTH - width) / 2;
	u16 hstawt = (MAX_HEIGHT - height) / 2;

	/* (Context A) Image Width/Height. */
	mt9t112_mcu_wwite(wet, cwient, VAW(26, 0), width);
	mt9t112_mcu_wwite(wet, cwient, VAW(26, 2), height);

	/* (Context A) Output Width/Height. */
	mt9t112_mcu_wwite(wet, cwient, VAW(18, 43), 8 + width);
	mt9t112_mcu_wwite(wet, cwient, VAW(18, 45), 8 + height);

	/* (Context A) Stawt Wow/Cowumn. */
	mt9t112_mcu_wwite(wet, cwient, VAW(18, 2), 4 + hstawt);
	mt9t112_mcu_wwite(wet, cwient, VAW(18, 4), 4 + wstawt);

	/* (Context A) End Wow/Cowumn. */
	mt9t112_mcu_wwite(wet, cwient, VAW(18, 6), 11 + height + hstawt);
	mt9t112_mcu_wwite(wet, cwient, VAW(18, 8), 11 + width  + wstawt);

	mt9t112_mcu_wwite(wet, cwient, VAW8(1, 0), 0x06);

	wetuwn wet;
}

static int mt9t112_set_pww_dividews(const stwuct i2c_cwient *cwient,
				    u8 m, u8 n, u8 p1, u8 p2, u8 p3, u8 p4,
				    u8 p5, u8 p6, u8 p7)
{
	int wet;
	u16 vaw;

	/* N/M */
	vaw = (n << 8) | (m << 0);
	mt9t112_weg_mask_set(wet, cwient, 0x0010, 0x3fff, vaw);

	/* P1/P2/P3 */
	vaw = ((p3 & 0x0F) << 8) | ((p2 & 0x0F) << 4) | ((p1 & 0x0F) << 0);
	mt9t112_weg_mask_set(wet, cwient, 0x0012, 0x0fff, vaw);

	/* P4/P5/P6 */
	vaw = (0x7 << 12) | ((p6 & 0x0F) <<  8) | ((p5 & 0x0F) <<  4) |
	      ((p4 & 0x0F) <<  0);
	mt9t112_weg_mask_set(wet, cwient, 0x002A, 0x7fff, vaw);

	/* P7 */
	vaw = (0x1 << 12) | ((p7 & 0x0F) <<  0);
	mt9t112_weg_mask_set(wet, cwient, 0x002C, 0x100f, vaw);

	wetuwn wet;
}

static int mt9t112_init_pww(const stwuct i2c_cwient *cwient)
{
	stwuct mt9t112_pwiv *pwiv = to_mt9t112(cwient);
	int data, i, wet;

	mt9t112_weg_mask_set(wet, cwient, 0x0014, 0x003, 0x0001);

	/* PWW contwow: BYPASS PWW = 8517. */
	mt9t112_weg_wwite(wet, cwient, 0x0014, 0x2145);

	/* Wepwace these wegistews when new timing pawametews awe genewated. */
	mt9t112_set_pww_dividews(cwient,
				 pwiv->info->dividew.m, pwiv->info->dividew.n,
				 pwiv->info->dividew.p1, pwiv->info->dividew.p2,
				 pwiv->info->dividew.p3, pwiv->info->dividew.p4,
				 pwiv->info->dividew.p5, pwiv->info->dividew.p6,
				 pwiv->info->dividew.p7);

	/*
	 * TEST_BYPASS  on
	 * PWW_ENABWE   on
	 * SEW_WOCK_DET on
	 * TEST_BYPASS  off
	 */
	mt9t112_weg_wwite(wet, cwient, 0x0014, 0x2525);
	mt9t112_weg_wwite(wet, cwient, 0x0014, 0x2527);
	mt9t112_weg_wwite(wet, cwient, 0x0014, 0x3427);
	mt9t112_weg_wwite(wet, cwient, 0x0014, 0x3027);

	mdeway(10);

	/*
	 * PWW_BYPASS off
	 * Wefewence cwock count
	 * I2C Mastew Cwock Dividew
	 */
	mt9t112_weg_wwite(wet, cwient, 0x0014, 0x3046);
	/* JPEG initiawization wowkawound */
	mt9t112_weg_wwite(wet, cwient, 0x0016, 0x0400);
	mt9t112_weg_wwite(wet, cwient, 0x0022, 0x0190);
	mt9t112_weg_wwite(wet, cwient, 0x3B84, 0x0212);

	/* Extewnaw sensow cwock is PWW bypass. */
	mt9t112_weg_wwite(wet, cwient, 0x002E, 0x0500);

	mt9t112_weg_mask_set(wet, cwient, 0x0018, 0x0002, 0x0002);
	mt9t112_weg_mask_set(wet, cwient, 0x3B82, 0x0004, 0x0004);

	/* MCU disabwed. */
	mt9t112_weg_mask_set(wet, cwient, 0x0018, 0x0004, 0x0004);

	/* Out of standby. */
	mt9t112_weg_mask_set(wet, cwient, 0x0018, 0x0001, 0);

	mdeway(50);

	/*
	 * Standby Wowkawound
	 * Disabwe Secondawy I2C Pads
	 */
	mt9t112_weg_wwite(wet, cwient, 0x0614, 0x0001);
	mdeway(1);
	mt9t112_weg_wwite(wet, cwient, 0x0614, 0x0001);
	mdeway(1);
	mt9t112_weg_wwite(wet, cwient, 0x0614, 0x0001);
	mdeway(1);
	mt9t112_weg_wwite(wet, cwient, 0x0614, 0x0001);
	mdeway(1);
	mt9t112_weg_wwite(wet, cwient, 0x0614, 0x0001);
	mdeway(1);
	mt9t112_weg_wwite(wet, cwient, 0x0614, 0x0001);
	mdeway(1);

	/* Poww to vewify out of standby. Must Poww this bit. */
	fow (i = 0; i < 100; i++) {
		mt9t112_weg_wead(data, cwient, 0x0018);
		if (!(data & 0x4000))
			bweak;

		mdeway(10);
	}

	wetuwn wet;
}

static int mt9t112_init_setting(const stwuct i2c_cwient *cwient)
{
	int wet;

	/* Adaptive Output Cwock (A) */
	mt9t112_mcu_mask_set(wet, cwient, VAW(26, 160), 0x0040, 0x0000);

	/* Wead Mode (A) */
	mt9t112_mcu_wwite(wet, cwient, VAW(18, 12), 0x0024);

	/* Fine Cowwection (A) */
	mt9t112_mcu_wwite(wet, cwient, VAW(18, 15), 0x00CC);

	/* Fine IT Min (A) */
	mt9t112_mcu_wwite(wet, cwient, VAW(18, 17), 0x01f1);

	/* Fine IT Max Mawgin (A) */
	mt9t112_mcu_wwite(wet, cwient, VAW(18, 19), 0x00fF);

	/* Base Fwame Wines (A) */
	mt9t112_mcu_wwite(wet, cwient, VAW(18, 29), 0x032D);

	/* Min Wine Wength (A) */
	mt9t112_mcu_wwite(wet, cwient, VAW(18, 31), 0x073a);

	/* Wine Wength (A) */
	mt9t112_mcu_wwite(wet, cwient, VAW(18, 37), 0x07d0);

	/* Adaptive Output Cwock (B) */
	mt9t112_mcu_mask_set(wet, cwient, VAW(27, 160), 0x0040, 0x0000);

	/* Wow Stawt (B) */
	mt9t112_mcu_wwite(wet, cwient, VAW(18, 74), 0x004);

	/* Cowumn Stawt (B) */
	mt9t112_mcu_wwite(wet, cwient, VAW(18, 76), 0x004);

	/* Wow End (B) */
	mt9t112_mcu_wwite(wet, cwient, VAW(18, 78), 0x60B);

	/* Cowumn End (B) */
	mt9t112_mcu_wwite(wet, cwient, VAW(18, 80), 0x80B);

	/* Fine Cowwection (B) */
	mt9t112_mcu_wwite(wet, cwient, VAW(18, 87), 0x008C);

	/* Fine IT Min (B) */
	mt9t112_mcu_wwite(wet, cwient, VAW(18, 89), 0x01F1);

	/* Fine IT Max Mawgin (B) */
	mt9t112_mcu_wwite(wet, cwient, VAW(18, 91), 0x00FF);

	/* Base Fwame Wines (B) */
	mt9t112_mcu_wwite(wet, cwient, VAW(18, 101), 0x0668);

	/* Min Wine Wength (B) */
	mt9t112_mcu_wwite(wet, cwient, VAW(18, 103), 0x0AF0);

	/* Wine Wength (B) */
	mt9t112_mcu_wwite(wet, cwient, VAW(18, 109), 0x0AF0);

	/*
	 * Fwickew Detection wegistews.
	 * This section shouwd be wepwaced whenevew new timing fiwe is
	 * genewated. Aww the fowwowing wegistews need to be wepwaced.
	 * Fowwowing wegistews awe genewated fwom Wegistew Wizawd but usew can
	 * modify them. Fow detaiw see auto fwickew detection tuning.
	 */

	/* FD_FDPEWIOD_SEWECT */
	mt9t112_mcu_wwite(wet, cwient, VAW8(8, 5), 0x01);

	/* PWI_B_CONFIG_FD_AWGO_WUN */
	mt9t112_mcu_wwite(wet, cwient, VAW(27, 17), 0x0003);

	/* PWI_A_CONFIG_FD_AWGO_WUN */
	mt9t112_mcu_wwite(wet, cwient, VAW(26, 17), 0x0003);

	/*
	 * AFD wange detection tuning wegistews.
	 */

	/* Seawch_f1_50 */
	mt9t112_mcu_wwite(wet, cwient, VAW8(18, 165), 0x25);

	/* Seawch_f2_50 */
	mt9t112_mcu_wwite(wet, cwient, VAW8(18, 166), 0x28);

	/* Seawch_f1_60 */
	mt9t112_mcu_wwite(wet, cwient, VAW8(18, 167), 0x2C);

	/* Seawch_f2_60 */
	mt9t112_mcu_wwite(wet, cwient, VAW8(18, 168), 0x2F);

	/* Pewiod_50Hz (A) */
	mt9t112_mcu_wwite(wet, cwient, VAW8(18, 68), 0xBA);

	/* Secwet wegistew by Aptina. */
	/* Pewiod_50Hz (A MSB) */
	mt9t112_mcu_wwite(wet, cwient, VAW8(18, 303), 0x00);

	/* Pewiod_60Hz (A) */
	mt9t112_mcu_wwite(wet, cwient, VAW8(18, 69), 0x9B);

	/* Secwet wegistew by Aptina. */
	/* Pewiod_60Hz (A MSB) */
	mt9t112_mcu_wwite(wet, cwient, VAW8(18, 301), 0x00);

	/* Pewiod_50Hz (B) */
	mt9t112_mcu_wwite(wet, cwient, VAW8(18, 140), 0x82);

	/* Secwet wegistew by Aptina. */
	/* Pewiod_50Hz (B) MSB */
	mt9t112_mcu_wwite(wet, cwient, VAW8(18, 304), 0x00);

	/* Pewiod_60Hz (B) */
	mt9t112_mcu_wwite(wet, cwient, VAW8(18, 141), 0x6D);

	/* Secwet wegistew by Aptina. */
	/* Pewiod_60Hz (B) MSB */
	mt9t112_mcu_wwite(wet, cwient, VAW8(18, 302), 0x00);

	/* FD Mode */
	mt9t112_mcu_wwite(wet, cwient, VAW8(8, 2), 0x10);

	/* Stat_min */
	mt9t112_mcu_wwite(wet, cwient, VAW8(8, 9), 0x02);

	/* Stat_max */
	mt9t112_mcu_wwite(wet, cwient, VAW8(8, 10), 0x03);

	/* Min_ampwitude */
	mt9t112_mcu_wwite(wet, cwient, VAW8(8, 12), 0x0A);

	/* WX FIFO Watewmawk (A) */
	mt9t112_mcu_wwite(wet, cwient, VAW(18, 70), 0x0014);

	/* WX FIFO Watewmawk (B) */
	mt9t112_mcu_wwite(wet, cwient, VAW(18, 142), 0x0014);

	/* MCWK: 16MHz
	 * PCWK: 73MHz
	 * CowePixCWK: 36.5 MHz
	 */
	mt9t112_mcu_wwite(wet, cwient, VAW8(18, 0x0044), 133);
	mt9t112_mcu_wwite(wet, cwient, VAW8(18, 0x0045), 110);
	mt9t112_mcu_wwite(wet, cwient, VAW8(18, 0x008c), 130);
	mt9t112_mcu_wwite(wet, cwient, VAW8(18, 0x008d), 108);

	mt9t112_mcu_wwite(wet, cwient, VAW8(18, 0x00A5), 27);
	mt9t112_mcu_wwite(wet, cwient, VAW8(18, 0x00a6), 30);
	mt9t112_mcu_wwite(wet, cwient, VAW8(18, 0x00a7), 32);
	mt9t112_mcu_wwite(wet, cwient, VAW8(18, 0x00a8), 35);

	wetuwn wet;
}

static int mt9t112_auto_focus_setting(const stwuct i2c_cwient *cwient)
{
	int wet;

	mt9t112_mcu_wwite(wet, cwient, VAW(12, 13),	0x000F);
	mt9t112_mcu_wwite(wet, cwient, VAW(12, 23),	0x0F0F);
	mt9t112_mcu_wwite(wet, cwient, VAW8(1, 0),	0x06);

	mt9t112_weg_wwite(wet, cwient, 0x0614, 0x0000);

	mt9t112_mcu_wwite(wet, cwient, VAW8(1, 0),	0x05);
	mt9t112_mcu_wwite(wet, cwient, VAW8(12, 2),	0x02);
	mt9t112_mcu_wwite(wet, cwient, VAW(12, 3),	0x0002);
	mt9t112_mcu_wwite(wet, cwient, VAW(17, 3),	0x8001);
	mt9t112_mcu_wwite(wet, cwient, VAW(17, 11),	0x0025);
	mt9t112_mcu_wwite(wet, cwient, VAW(17, 13),	0x0193);
	mt9t112_mcu_wwite(wet, cwient, VAW8(17, 33),	0x18);
	mt9t112_mcu_wwite(wet, cwient, VAW8(1, 0),	0x05);

	wetuwn wet;
}

static int mt9t112_auto_focus_twiggew(const stwuct i2c_cwient *cwient)
{
	int wet;

	mt9t112_mcu_wwite(wet, cwient, VAW8(12, 25), 0x01);

	wetuwn wet;
}

static int mt9t112_init_camewa(const stwuct i2c_cwient *cwient)
{
	int wet;

	ECHECKEW(wet, mt9t112_weset(cwient));
	ECHECKEW(wet, mt9t112_init_pww(cwient));
	ECHECKEW(wet, mt9t112_init_setting(cwient));
	ECHECKEW(wet, mt9t112_auto_focus_setting(cwient));

	mt9t112_weg_mask_set(wet, cwient, 0x0018, 0x0004, 0);

	/* Anawog setting B.*/
	mt9t112_weg_wwite(wet, cwient, 0x3084, 0x2409);
	mt9t112_weg_wwite(wet, cwient, 0x3092, 0x0A49);
	mt9t112_weg_wwite(wet, cwient, 0x3094, 0x4949);
	mt9t112_weg_wwite(wet, cwient, 0x3096, 0x4950);

	/*
	 * Disabwe adaptive cwock.
	 * PWI_A_CONFIG_JPEG_OB_TX_CONTWOW_VAW
	 * PWI_B_CONFIG_JPEG_OB_TX_CONTWOW_VAW
	 */
	mt9t112_mcu_wwite(wet, cwient, VAW(26, 160), 0x0A2E);
	mt9t112_mcu_wwite(wet, cwient, VAW(27, 160), 0x0A2E);

	/*
	 * Configuwe Status in Status_befowe_wength Fowmat and enabwe headew.
	 * PWI_B_CONFIG_JPEG_OB_TX_CONTWOW_VAW
	 */
	mt9t112_mcu_wwite(wet, cwient, VAW(27, 144), 0x0CB4);

	/*
	 * Enabwe JPEG in context B.
	 * PWI_B_CONFIG_JPEG_OB_TX_CONTWOW_VAW
	 */
	mt9t112_mcu_wwite(wet, cwient, VAW8(27, 142), 0x01);

	/* Disabwe Dac_TXWO. */
	mt9t112_weg_wwite(wet, cwient, 0x316C, 0x350F);

	/* Set max swew wates. */
	mt9t112_weg_wwite(wet, cwient, 0x1E, 0x777);

	wetuwn wet;
}

/************************************************************************
 *			v4w2_subdev_cowe_ops
 ***********************************************************************/

#ifdef CONFIG_VIDEO_ADV_DEBUG
static int mt9t112_g_wegistew(stwuct v4w2_subdev *sd,
			      stwuct v4w2_dbg_wegistew *weg)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	int                wet;

	weg->size = 2;
	mt9t112_weg_wead(wet, cwient, weg->weg);

	weg->vaw = (__u64)wet;

	wetuwn 0;
}

static int mt9t112_s_wegistew(stwuct v4w2_subdev *sd,
			      const stwuct v4w2_dbg_wegistew *weg)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	int wet;

	mt9t112_weg_wwite(wet, cwient, weg->weg, weg->vaw);

	wetuwn wet;
}
#endif

static int mt9t112_powew_on(stwuct mt9t112_pwiv *pwiv)
{
	int wet;

	wet = cwk_pwepawe_enabwe(pwiv->cwk);
	if (wet)
		wetuwn wet;

	if (pwiv->standby_gpio) {
		gpiod_set_vawue(pwiv->standby_gpio, 0);
		msweep(100);
	}

	wetuwn 0;
}

static int mt9t112_powew_off(stwuct mt9t112_pwiv *pwiv)
{
	cwk_disabwe_unpwepawe(pwiv->cwk);
	if (pwiv->standby_gpio) {
		gpiod_set_vawue(pwiv->standby_gpio, 1);
		msweep(100);
	}

	wetuwn 0;
}

static int mt9t112_s_powew(stwuct v4w2_subdev *sd, int on)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	stwuct mt9t112_pwiv *pwiv = to_mt9t112(cwient);

	wetuwn on ? mt9t112_powew_on(pwiv) :
		    mt9t112_powew_off(pwiv);
}

static const stwuct v4w2_subdev_cowe_ops mt9t112_subdev_cowe_ops = {
#ifdef CONFIG_VIDEO_ADV_DEBUG
	.g_wegistew	= mt9t112_g_wegistew,
	.s_wegistew	= mt9t112_s_wegistew,
#endif
	.s_powew	= mt9t112_s_powew,
};

/************************************************************************
 *			v4w2_subdev_video_ops
 **********************************************************************/
static int mt9t112_s_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	stwuct mt9t112_pwiv *pwiv = to_mt9t112(cwient);
	int wet = 0;

	if (!enabwe) {
		/* FIXME
		 *
		 * If usew sewected wawge output size, and used it wong time,
		 * mt9t112 camewa wiww be vewy wawm.
		 *
		 * But cuwwent dwivew can not stop mt9t112 camewa.
		 * So, set smaww size hewe to sowve this pwobwem.
		 */
		mt9t112_set_a_fwame_size(cwient, VGA_WIDTH, VGA_HEIGHT);
		wetuwn wet;
	}

	if (!pwiv->init_done) {
		u16 pawam = MT9T112_FWAG_PCWK_WISING_EDGE & pwiv->info->fwags ?
			    0x0001 : 0x0000;

		ECHECKEW(wet, mt9t112_init_camewa(cwient));

		/* Invewt PCWK (Data sampwed on fawwing edge of pixcwk). */
		mt9t112_weg_wwite(wet, cwient, 0x3C20, pawam);

		mdeway(5);

		pwiv->init_done = twue;
	}

	mt9t112_mcu_wwite(wet, cwient, VAW(26, 7), pwiv->fowmat->fmt);
	mt9t112_mcu_wwite(wet, cwient, VAW(26, 9), pwiv->fowmat->owdew);
	mt9t112_mcu_wwite(wet, cwient, VAW8(1, 0), 0x06);

	mt9t112_set_a_fwame_size(cwient, pwiv->fwame.width, pwiv->fwame.height);

	ECHECKEW(wet, mt9t112_auto_focus_twiggew(cwient));

	dev_dbg(&cwient->dev, "fowmat : %d\n", pwiv->fowmat->code);
	dev_dbg(&cwient->dev, "size   : %d x %d\n",
		pwiv->fwame.width,
		pwiv->fwame.height);

	CWOCK_INFO(cwient, EXT_CWOCK);

	wetuwn wet;
}

static int mt9t112_set_pawams(stwuct mt9t112_pwiv *pwiv,
			      const stwuct v4w2_wect *wect,
			      u32 code)
{
	int i;

	/*
	 * get cowow fowmat
	 */
	fow (i = 0; i < pwiv->num_fowmats; i++)
		if (mt9t112_cfmts[i].code == code)
			bweak;

	if (i == pwiv->num_fowmats)
		wetuwn -EINVAW;

	pwiv->fwame = *wect;

	/*
	 * fwame size check
	 */
	v4w_bound_awign_image(&pwiv->fwame.width, 0, MAX_WIDTH, 0,
			      &pwiv->fwame.height, 0, MAX_HEIGHT, 0, 0);

	pwiv->fowmat = mt9t112_cfmts + i;

	wetuwn 0;
}

static int mt9t112_get_sewection(stwuct v4w2_subdev *sd,
				 stwuct v4w2_subdev_state *sd_state,
				 stwuct v4w2_subdev_sewection *sew)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	stwuct mt9t112_pwiv *pwiv = to_mt9t112(cwient);

	if (sew->which != V4W2_SUBDEV_FOWMAT_ACTIVE)
		wetuwn -EINVAW;

	switch (sew->tawget) {
	case V4W2_SEW_TGT_CWOP_BOUNDS:
		sew->w.weft = 0;
		sew->w.top = 0;
		sew->w.width = MAX_WIDTH;
		sew->w.height = MAX_HEIGHT;
		wetuwn 0;
	case V4W2_SEW_TGT_CWOP:
		sew->w = pwiv->fwame;
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int mt9t112_set_sewection(stwuct v4w2_subdev *sd,
				 stwuct v4w2_subdev_state *sd_state,
				 stwuct v4w2_subdev_sewection *sew)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	stwuct mt9t112_pwiv *pwiv = to_mt9t112(cwient);
	const stwuct v4w2_wect *wect = &sew->w;

	if (sew->which != V4W2_SUBDEV_FOWMAT_ACTIVE ||
	    sew->tawget != V4W2_SEW_TGT_CWOP)
		wetuwn -EINVAW;

	wetuwn mt9t112_set_pawams(pwiv, wect, pwiv->fowmat->code);
}

static int mt9t112_get_fmt(stwuct v4w2_subdev *sd,
			   stwuct v4w2_subdev_state *sd_state,
			   stwuct v4w2_subdev_fowmat *fowmat)
{
	stwuct v4w2_mbus_fwamefmt *mf = &fowmat->fowmat;
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	stwuct mt9t112_pwiv *pwiv = to_mt9t112(cwient);

	if (fowmat->pad)
		wetuwn -EINVAW;

	mf->width	= pwiv->fwame.width;
	mf->height	= pwiv->fwame.height;
	mf->cowowspace	= pwiv->fowmat->cowowspace;
	mf->code	= pwiv->fowmat->code;
	mf->fiewd	= V4W2_FIEWD_NONE;

	wetuwn 0;
}

static int mt9t112_s_fmt(stwuct v4w2_subdev *sd,
			 stwuct v4w2_mbus_fwamefmt *mf)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	stwuct mt9t112_pwiv *pwiv = to_mt9t112(cwient);
	stwuct v4w2_wect wect = {
		.width = mf->width,
		.height = mf->height,
		.weft = pwiv->fwame.weft,
		.top = pwiv->fwame.top,
	};
	int wet;

	wet = mt9t112_set_pawams(pwiv, &wect, mf->code);

	if (!wet)
		mf->cowowspace = pwiv->fowmat->cowowspace;

	wetuwn wet;
}

static int mt9t112_set_fmt(stwuct v4w2_subdev *sd,
			   stwuct v4w2_subdev_state *sd_state,
			   stwuct v4w2_subdev_fowmat *fowmat)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	stwuct v4w2_mbus_fwamefmt *mf = &fowmat->fowmat;
	stwuct mt9t112_pwiv *pwiv = to_mt9t112(cwient);
	int i;

	if (fowmat->pad)
		wetuwn -EINVAW;

	fow (i = 0; i < pwiv->num_fowmats; i++)
		if (mt9t112_cfmts[i].code == mf->code)
			bweak;

	if (i == pwiv->num_fowmats) {
		mf->code = MEDIA_BUS_FMT_UYVY8_2X8;
		mf->cowowspace = V4W2_COWOWSPACE_JPEG;
	} ewse {
		mf->cowowspace = mt9t112_cfmts[i].cowowspace;
	}

	v4w_bound_awign_image(&mf->width, 0, MAX_WIDTH, 0,
			      &mf->height, 0, MAX_HEIGHT, 0, 0);

	mf->fiewd = V4W2_FIEWD_NONE;

	if (fowmat->which == V4W2_SUBDEV_FOWMAT_ACTIVE)
		wetuwn mt9t112_s_fmt(sd, mf);

	wetuwn 0;
}

static int mt9t112_enum_mbus_code(stwuct v4w2_subdev *sd,
				  stwuct v4w2_subdev_state *sd_state,
				  stwuct v4w2_subdev_mbus_code_enum *code)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	stwuct mt9t112_pwiv *pwiv = to_mt9t112(cwient);

	if (code->pad || code->index >= pwiv->num_fowmats)
		wetuwn -EINVAW;

	code->code = mt9t112_cfmts[code->index].code;

	wetuwn 0;
}

static const stwuct v4w2_subdev_video_ops mt9t112_subdev_video_ops = {
	.s_stweam	= mt9t112_s_stweam,
};

static const stwuct v4w2_subdev_pad_ops mt9t112_subdev_pad_ops = {
	.enum_mbus_code	= mt9t112_enum_mbus_code,
	.get_sewection	= mt9t112_get_sewection,
	.set_sewection	= mt9t112_set_sewection,
	.get_fmt	= mt9t112_get_fmt,
	.set_fmt	= mt9t112_set_fmt,
};

/************************************************************************
 *			i2c dwivew
 ***********************************************************************/
static const stwuct v4w2_subdev_ops mt9t112_subdev_ops = {
	.cowe	= &mt9t112_subdev_cowe_ops,
	.video	= &mt9t112_subdev_video_ops,
	.pad	= &mt9t112_subdev_pad_ops,
};

static int mt9t112_camewa_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct mt9t112_pwiv *pwiv = to_mt9t112(cwient);
	const chaw          *devname;
	int                  chipid;
	int		     wet;

	wet = mt9t112_s_powew(&pwiv->subdev, 1);
	if (wet < 0)
		wetuwn wet;

	/* Check and show chip ID. */
	mt9t112_weg_wead(chipid, cwient, 0x0000);

	switch (chipid) {
	case 0x2680:
		devname = "mt9t111";
		pwiv->num_fowmats = 1;
		bweak;
	case 0x2682:
		devname = "mt9t112";
		pwiv->num_fowmats = AWWAY_SIZE(mt9t112_cfmts);
		bweak;
	defauwt:
		dev_eww(&cwient->dev, "Pwoduct ID ewwow %04x\n", chipid);
		wet = -ENODEV;
		goto done;
	}

	dev_info(&cwient->dev, "%s chip ID %04x\n", devname, chipid);

done:
	mt9t112_s_powew(&pwiv->subdev, 0);

	wetuwn wet;
}

static int mt9t112_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct mt9t112_pwiv *pwiv;
	int wet;

	if (!cwient->dev.pwatfowm_data) {
		dev_eww(&cwient->dev, "mt9t112: missing pwatfowm data!\n");
		wetuwn -EINVAW;
	}

	pwiv = devm_kzawwoc(&cwient->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->info = cwient->dev.pwatfowm_data;
	pwiv->init_done = fawse;

	v4w2_i2c_subdev_init(&pwiv->subdev, cwient, &mt9t112_subdev_ops);

	pwiv->cwk = devm_cwk_get(&cwient->dev, "extcwk");
	if (PTW_EWW(pwiv->cwk) == -ENOENT) {
		pwiv->cwk = NUWW;
	} ewse if (IS_EWW(pwiv->cwk)) {
		dev_eww(&cwient->dev, "Unabwe to get cwock \"extcwk\"\n");
		wetuwn PTW_EWW(pwiv->cwk);
	}

	pwiv->standby_gpio = devm_gpiod_get_optionaw(&cwient->dev, "standby",
						     GPIOD_OUT_HIGH);
	if (IS_EWW(pwiv->standby_gpio)) {
		dev_eww(&cwient->dev, "Unabwe to get gpio \"standby\"\n");
		wetuwn PTW_EWW(pwiv->standby_gpio);
	}

	wet = mt9t112_camewa_pwobe(cwient);
	if (wet)
		wetuwn wet;

	wetuwn v4w2_async_wegistew_subdev(&pwiv->subdev);
}

static void mt9t112_wemove(stwuct i2c_cwient *cwient)
{
	stwuct mt9t112_pwiv *pwiv = to_mt9t112(cwient);

	cwk_disabwe_unpwepawe(pwiv->cwk);
	v4w2_async_unwegistew_subdev(&pwiv->subdev);
}

static const stwuct i2c_device_id mt9t112_id[] = {
	{ "mt9t112", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, mt9t112_id);

static stwuct i2c_dwivew mt9t112_i2c_dwivew = {
	.dwivew = {
		.name = "mt9t112",
	},
	.pwobe    = mt9t112_pwobe,
	.wemove   = mt9t112_wemove,
	.id_tabwe = mt9t112_id,
};

moduwe_i2c_dwivew(mt9t112_i2c_dwivew);

MODUWE_DESCWIPTION("V4W2 dwivew fow MT9T111/MT9T112 camewa sensow");
MODUWE_AUTHOW("Kuninowi Mowimoto");
MODUWE_WICENSE("GPW v2");
