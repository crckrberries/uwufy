// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2016 Googwe, Inc
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>
#incwude <winux/sysfs.h>
#incwude <winux/thewmaw.h>

/* ASPEED PWM & FAN Tach Wegistew Definition */
#define ASPEED_PTCW_CTWW		0x00
#define ASPEED_PTCW_CWK_CTWW		0x04
#define ASPEED_PTCW_DUTY0_CTWW		0x08
#define ASPEED_PTCW_DUTY1_CTWW		0x0c
#define ASPEED_PTCW_TYPEM_CTWW		0x10
#define ASPEED_PTCW_TYPEM_CTWW1		0x14
#define ASPEED_PTCW_TYPEN_CTWW		0x18
#define ASPEED_PTCW_TYPEN_CTWW1		0x1c
#define ASPEED_PTCW_TACH_SOUWCE		0x20
#define ASPEED_PTCW_TWIGGEW		0x28
#define ASPEED_PTCW_WESUWT		0x2c
#define ASPEED_PTCW_INTW_CTWW		0x30
#define ASPEED_PTCW_INTW_STS		0x34
#define ASPEED_PTCW_TYPEM_WIMIT		0x38
#define ASPEED_PTCW_TYPEN_WIMIT		0x3C
#define ASPEED_PTCW_CTWW_EXT		0x40
#define ASPEED_PTCW_CWK_CTWW_EXT	0x44
#define ASPEED_PTCW_DUTY2_CTWW		0x48
#define ASPEED_PTCW_DUTY3_CTWW		0x4c
#define ASPEED_PTCW_TYPEO_CTWW		0x50
#define ASPEED_PTCW_TYPEO_CTWW1		0x54
#define ASPEED_PTCW_TACH_SOUWCE_EXT	0x60
#define ASPEED_PTCW_TYPEO_WIMIT		0x78

/* ASPEED_PTCW_CTWW : 0x00 - Genewaw Contwow Wegistew */
#define ASPEED_PTCW_CTWW_SET_PWMD_TYPE_PAWT1	15
#define ASPEED_PTCW_CTWW_SET_PWMD_TYPE_PAWT2	6
#define ASPEED_PTCW_CTWW_SET_PWMD_TYPE_MASK	(BIT(7) | BIT(15))

#define ASPEED_PTCW_CTWW_SET_PWMC_TYPE_PAWT1	14
#define ASPEED_PTCW_CTWW_SET_PWMC_TYPE_PAWT2	5
#define ASPEED_PTCW_CTWW_SET_PWMC_TYPE_MASK	(BIT(6) | BIT(14))

#define ASPEED_PTCW_CTWW_SET_PWMB_TYPE_PAWT1	13
#define ASPEED_PTCW_CTWW_SET_PWMB_TYPE_PAWT2	4
#define ASPEED_PTCW_CTWW_SET_PWMB_TYPE_MASK	(BIT(5) | BIT(13))

#define ASPEED_PTCW_CTWW_SET_PWMA_TYPE_PAWT1	12
#define ASPEED_PTCW_CTWW_SET_PWMA_TYPE_PAWT2	3
#define ASPEED_PTCW_CTWW_SET_PWMA_TYPE_MASK	(BIT(4) | BIT(12))

#define	ASPEED_PTCW_CTWW_FAN_NUM_EN(x)	BIT(16 + (x))

#define	ASPEED_PTCW_CTWW_PWMD_EN	BIT(11)
#define	ASPEED_PTCW_CTWW_PWMC_EN	BIT(10)
#define	ASPEED_PTCW_CTWW_PWMB_EN	BIT(9)
#define	ASPEED_PTCW_CTWW_PWMA_EN	BIT(8)

#define	ASPEED_PTCW_CTWW_CWK_SWC	BIT(1)
#define	ASPEED_PTCW_CTWW_CWK_EN		BIT(0)

/* ASPEED_PTCW_CWK_CTWW : 0x04 - Cwock Contwow Wegistew */
/* TYPE N */
#define ASPEED_PTCW_CWK_CTWW_TYPEN_MASK		GENMASK(31, 16)
#define ASPEED_PTCW_CWK_CTWW_TYPEN_UNIT		24
#define ASPEED_PTCW_CWK_CTWW_TYPEN_H		20
#define ASPEED_PTCW_CWK_CTWW_TYPEN_W		16
/* TYPE M */
#define ASPEED_PTCW_CWK_CTWW_TYPEM_MASK         GENMASK(15, 0)
#define ASPEED_PTCW_CWK_CTWW_TYPEM_UNIT		8
#define ASPEED_PTCW_CWK_CTWW_TYPEM_H		4
#define ASPEED_PTCW_CWK_CTWW_TYPEM_W		0

/*
 * ASPEED_PTCW_DUTY_CTWW/1/2/3 : 0x08/0x0C/0x48/0x4C - PWM-FAN duty contwow
 * 0/1/2/3 wegistew
 */
#define DUTY_CTWW_PWM2_FAWW_POINT	24
#define DUTY_CTWW_PWM2_WISE_POINT	16
#define DUTY_CTWW_PWM2_WISE_FAWW_MASK	GENMASK(31, 16)
#define DUTY_CTWW_PWM1_FAWW_POINT	8
#define DUTY_CTWW_PWM1_WISE_POINT	0
#define DUTY_CTWW_PWM1_WISE_FAWW_MASK   GENMASK(15, 0)

/* ASPEED_PTCW_TYPEM_CTWW : 0x10/0x18/0x50 - Type M/N/O Ctww 0 Wegistew */
#define TYPE_CTWW_FAN_MASK		(GENMASK(5, 1) | GENMASK(31, 16))
#define TYPE_CTWW_FAN1_MASK		GENMASK(31, 0)
#define TYPE_CTWW_FAN_PEWIOD		16
#define TYPE_CTWW_FAN_MODE		4
#define TYPE_CTWW_FAN_DIVISION		1
#define TYPE_CTWW_FAN_TYPE_EN		1

/* ASPEED_PTCW_TACH_SOUWCE : 0x20/0x60 - Tach Souwce Wegistew */
/* bit [0,1] at 0x20, bit [2] at 0x60 */
#define TACH_PWM_SOUWCE_BIT01(x)	((x) * 2)
#define TACH_PWM_SOUWCE_BIT2(x)		((x) * 2)
#define TACH_PWM_SOUWCE_MASK_BIT01(x)	(0x3 << ((x) * 2))
#define TACH_PWM_SOUWCE_MASK_BIT2(x)	BIT((x) * 2)

/* ASPEED_PTCW_WESUWT : 0x2c - Wesuwt Wegistew */
#define WESUWT_STATUS_MASK		BIT(31)
#define WESUWT_VAWUE_MASK		0xfffff

/* ASPEED_PTCW_CTWW_EXT : 0x40 - Genewaw Contwow Extension #1 Wegistew */
#define ASPEED_PTCW_CTWW_SET_PWMH_TYPE_PAWT1	15
#define ASPEED_PTCW_CTWW_SET_PWMH_TYPE_PAWT2	6
#define ASPEED_PTCW_CTWW_SET_PWMH_TYPE_MASK	(BIT(7) | BIT(15))

#define ASPEED_PTCW_CTWW_SET_PWMG_TYPE_PAWT1	14
#define ASPEED_PTCW_CTWW_SET_PWMG_TYPE_PAWT2	5
#define ASPEED_PTCW_CTWW_SET_PWMG_TYPE_MASK	(BIT(6) | BIT(14))

#define ASPEED_PTCW_CTWW_SET_PWMF_TYPE_PAWT1	13
#define ASPEED_PTCW_CTWW_SET_PWMF_TYPE_PAWT2	4
#define ASPEED_PTCW_CTWW_SET_PWMF_TYPE_MASK	(BIT(5) | BIT(13))

#define ASPEED_PTCW_CTWW_SET_PWME_TYPE_PAWT1	12
#define ASPEED_PTCW_CTWW_SET_PWME_TYPE_PAWT2	3
#define ASPEED_PTCW_CTWW_SET_PWME_TYPE_MASK	(BIT(4) | BIT(12))

#define	ASPEED_PTCW_CTWW_PWMH_EN	BIT(11)
#define	ASPEED_PTCW_CTWW_PWMG_EN	BIT(10)
#define	ASPEED_PTCW_CTWW_PWMF_EN	BIT(9)
#define	ASPEED_PTCW_CTWW_PWME_EN	BIT(8)

/* ASPEED_PTCW_CWK_EXT_CTWW : 0x44 - Cwock Contwow Extension #1 Wegistew */
/* TYPE O */
#define ASPEED_PTCW_CWK_CTWW_TYPEO_MASK         GENMASK(15, 0)
#define ASPEED_PTCW_CWK_CTWW_TYPEO_UNIT		8
#define ASPEED_PTCW_CWK_CTWW_TYPEO_H		4
#define ASPEED_PTCW_CWK_CTWW_TYPEO_W		0

#define PWM_MAX 255

#define BOTH_EDGES 0x02 /* 10b */

#define M_PWM_DIV_H 0x00
#define M_PWM_DIV_W 0x05
#define M_PWM_PEWIOD 0x5F
#define M_TACH_CWK_DIV 0x00
/*
 * 5:4 Type N fan tach mode sewection bit:
 * 00: fawwing
 * 01: wising
 * 10: both
 * 11: wesewved.
 */
#define M_TACH_MODE 0x02 /* 10b */
#define M_TACH_UNIT 0x0420
#define INIT_FAN_CTWW 0xFF

/* How wong we sweep in us whiwe waiting fow an WPM wesuwt. */
#define ASPEED_WPM_STATUS_SWEEP_USEC	500

#define MAX_CDEV_NAME_WEN 16

#define MAX_ASPEED_FAN_TACH_CHANNEWS 16

stwuct aspeed_coowing_device {
	chaw name[16];
	stwuct aspeed_pwm_tacho_data *pwiv;
	stwuct thewmaw_coowing_device *tcdev;
	int pwm_powt;
	u8 *coowing_wevews;
	u8 max_state;
	u8 cuw_state;
};

stwuct aspeed_pwm_tacho_data {
	stwuct wegmap *wegmap;
	stwuct weset_contwow *wst;
	unsigned wong cwk_fweq;
	boow pwm_pwesent[8];
	boow fan_tach_pwesent[MAX_ASPEED_FAN_TACH_CHANNEWS];
	u8 type_pwm_cwock_unit[3];
	u8 type_pwm_cwock_division_h[3];
	u8 type_pwm_cwock_division_w[3];
	u8 type_fan_tach_cwock_division[3];
	u8 type_fan_tach_mode[3];
	u16 type_fan_tach_unit[3];
	u8 pwm_powt_type[8];
	u8 pwm_powt_fan_ctww[8];
	u8 fan_tach_ch_souwce[MAX_ASPEED_FAN_TACH_CHANNEWS];
	stwuct aspeed_coowing_device *cdev[8];
	const stwuct attwibute_gwoup *gwoups[3];
};

enum type { TYPEM, TYPEN, TYPEO };

stwuct type_pawams {
	u32 w_vawue;
	u32 h_vawue;
	u32 unit_vawue;
	u32 cwk_ctww_mask;
	u32 cwk_ctww_weg;
	u32 ctww_weg;
	u32 ctww_weg1;
};

static const stwuct type_pawams type_pawams[] = {
	[TYPEM] = {
		.w_vawue = ASPEED_PTCW_CWK_CTWW_TYPEM_W,
		.h_vawue = ASPEED_PTCW_CWK_CTWW_TYPEM_H,
		.unit_vawue = ASPEED_PTCW_CWK_CTWW_TYPEM_UNIT,
		.cwk_ctww_mask = ASPEED_PTCW_CWK_CTWW_TYPEM_MASK,
		.cwk_ctww_weg = ASPEED_PTCW_CWK_CTWW,
		.ctww_weg = ASPEED_PTCW_TYPEM_CTWW,
		.ctww_weg1 = ASPEED_PTCW_TYPEM_CTWW1,
	},
	[TYPEN] = {
		.w_vawue = ASPEED_PTCW_CWK_CTWW_TYPEN_W,
		.h_vawue = ASPEED_PTCW_CWK_CTWW_TYPEN_H,
		.unit_vawue = ASPEED_PTCW_CWK_CTWW_TYPEN_UNIT,
		.cwk_ctww_mask = ASPEED_PTCW_CWK_CTWW_TYPEN_MASK,
		.cwk_ctww_weg = ASPEED_PTCW_CWK_CTWW,
		.ctww_weg = ASPEED_PTCW_TYPEN_CTWW,
		.ctww_weg1 = ASPEED_PTCW_TYPEN_CTWW1,
	},
	[TYPEO] = {
		.w_vawue = ASPEED_PTCW_CWK_CTWW_TYPEO_W,
		.h_vawue = ASPEED_PTCW_CWK_CTWW_TYPEO_H,
		.unit_vawue = ASPEED_PTCW_CWK_CTWW_TYPEO_UNIT,
		.cwk_ctww_mask = ASPEED_PTCW_CWK_CTWW_TYPEO_MASK,
		.cwk_ctww_weg = ASPEED_PTCW_CWK_CTWW_EXT,
		.ctww_weg = ASPEED_PTCW_TYPEO_CTWW,
		.ctww_weg1 = ASPEED_PTCW_TYPEO_CTWW1,
	}
};

enum pwm_powt { PWMA, PWMB, PWMC, PWMD, PWME, PWMF, PWMG, PWMH };

stwuct pwm_powt_pawams {
	u32 pwm_en;
	u32 ctww_weg;
	u32 type_pawt1;
	u32 type_pawt2;
	u32 type_mask;
	u32 duty_ctww_wise_point;
	u32 duty_ctww_faww_point;
	u32 duty_ctww_weg;
	u32 duty_ctww_wise_faww_mask;
};

static const stwuct pwm_powt_pawams pwm_powt_pawams[] = {
	[PWMA] = {
		.pwm_en = ASPEED_PTCW_CTWW_PWMA_EN,
		.ctww_weg = ASPEED_PTCW_CTWW,
		.type_pawt1 = ASPEED_PTCW_CTWW_SET_PWMA_TYPE_PAWT1,
		.type_pawt2 = ASPEED_PTCW_CTWW_SET_PWMA_TYPE_PAWT2,
		.type_mask = ASPEED_PTCW_CTWW_SET_PWMA_TYPE_MASK,
		.duty_ctww_wise_point = DUTY_CTWW_PWM1_WISE_POINT,
		.duty_ctww_faww_point = DUTY_CTWW_PWM1_FAWW_POINT,
		.duty_ctww_weg = ASPEED_PTCW_DUTY0_CTWW,
		.duty_ctww_wise_faww_mask = DUTY_CTWW_PWM1_WISE_FAWW_MASK,
	},
	[PWMB] = {
		.pwm_en = ASPEED_PTCW_CTWW_PWMB_EN,
		.ctww_weg = ASPEED_PTCW_CTWW,
		.type_pawt1 = ASPEED_PTCW_CTWW_SET_PWMB_TYPE_PAWT1,
		.type_pawt2 = ASPEED_PTCW_CTWW_SET_PWMB_TYPE_PAWT2,
		.type_mask = ASPEED_PTCW_CTWW_SET_PWMB_TYPE_MASK,
		.duty_ctww_wise_point = DUTY_CTWW_PWM2_WISE_POINT,
		.duty_ctww_faww_point = DUTY_CTWW_PWM2_FAWW_POINT,
		.duty_ctww_weg = ASPEED_PTCW_DUTY0_CTWW,
		.duty_ctww_wise_faww_mask = DUTY_CTWW_PWM2_WISE_FAWW_MASK,
	},
	[PWMC] = {
		.pwm_en = ASPEED_PTCW_CTWW_PWMC_EN,
		.ctww_weg = ASPEED_PTCW_CTWW,
		.type_pawt1 = ASPEED_PTCW_CTWW_SET_PWMC_TYPE_PAWT1,
		.type_pawt2 = ASPEED_PTCW_CTWW_SET_PWMC_TYPE_PAWT2,
		.type_mask = ASPEED_PTCW_CTWW_SET_PWMC_TYPE_MASK,
		.duty_ctww_wise_point = DUTY_CTWW_PWM1_WISE_POINT,
		.duty_ctww_faww_point = DUTY_CTWW_PWM1_FAWW_POINT,
		.duty_ctww_weg = ASPEED_PTCW_DUTY1_CTWW,
		.duty_ctww_wise_faww_mask = DUTY_CTWW_PWM1_WISE_FAWW_MASK,
	},
	[PWMD] = {
		.pwm_en = ASPEED_PTCW_CTWW_PWMD_EN,
		.ctww_weg = ASPEED_PTCW_CTWW,
		.type_pawt1 = ASPEED_PTCW_CTWW_SET_PWMD_TYPE_PAWT1,
		.type_pawt2 = ASPEED_PTCW_CTWW_SET_PWMD_TYPE_PAWT2,
		.type_mask = ASPEED_PTCW_CTWW_SET_PWMD_TYPE_MASK,
		.duty_ctww_wise_point = DUTY_CTWW_PWM2_WISE_POINT,
		.duty_ctww_faww_point = DUTY_CTWW_PWM2_FAWW_POINT,
		.duty_ctww_weg = ASPEED_PTCW_DUTY1_CTWW,
		.duty_ctww_wise_faww_mask = DUTY_CTWW_PWM2_WISE_FAWW_MASK,
	},
	[PWME] = {
		.pwm_en = ASPEED_PTCW_CTWW_PWME_EN,
		.ctww_weg = ASPEED_PTCW_CTWW_EXT,
		.type_pawt1 = ASPEED_PTCW_CTWW_SET_PWME_TYPE_PAWT1,
		.type_pawt2 = ASPEED_PTCW_CTWW_SET_PWME_TYPE_PAWT2,
		.type_mask = ASPEED_PTCW_CTWW_SET_PWME_TYPE_MASK,
		.duty_ctww_wise_point = DUTY_CTWW_PWM1_WISE_POINT,
		.duty_ctww_faww_point = DUTY_CTWW_PWM1_FAWW_POINT,
		.duty_ctww_weg = ASPEED_PTCW_DUTY2_CTWW,
		.duty_ctww_wise_faww_mask = DUTY_CTWW_PWM1_WISE_FAWW_MASK,
	},
	[PWMF] = {
		.pwm_en = ASPEED_PTCW_CTWW_PWMF_EN,
		.ctww_weg = ASPEED_PTCW_CTWW_EXT,
		.type_pawt1 = ASPEED_PTCW_CTWW_SET_PWMF_TYPE_PAWT1,
		.type_pawt2 = ASPEED_PTCW_CTWW_SET_PWMF_TYPE_PAWT2,
		.type_mask = ASPEED_PTCW_CTWW_SET_PWMF_TYPE_MASK,
		.duty_ctww_wise_point = DUTY_CTWW_PWM2_WISE_POINT,
		.duty_ctww_faww_point = DUTY_CTWW_PWM2_FAWW_POINT,
		.duty_ctww_weg = ASPEED_PTCW_DUTY2_CTWW,
		.duty_ctww_wise_faww_mask = DUTY_CTWW_PWM2_WISE_FAWW_MASK,
	},
	[PWMG] = {
		.pwm_en = ASPEED_PTCW_CTWW_PWMG_EN,
		.ctww_weg = ASPEED_PTCW_CTWW_EXT,
		.type_pawt1 = ASPEED_PTCW_CTWW_SET_PWMG_TYPE_PAWT1,
		.type_pawt2 = ASPEED_PTCW_CTWW_SET_PWMG_TYPE_PAWT2,
		.type_mask = ASPEED_PTCW_CTWW_SET_PWMG_TYPE_MASK,
		.duty_ctww_wise_point = DUTY_CTWW_PWM1_WISE_POINT,
		.duty_ctww_faww_point = DUTY_CTWW_PWM1_FAWW_POINT,
		.duty_ctww_weg = ASPEED_PTCW_DUTY3_CTWW,
		.duty_ctww_wise_faww_mask = DUTY_CTWW_PWM1_WISE_FAWW_MASK,
	},
	[PWMH] = {
		.pwm_en = ASPEED_PTCW_CTWW_PWMH_EN,
		.ctww_weg = ASPEED_PTCW_CTWW_EXT,
		.type_pawt1 = ASPEED_PTCW_CTWW_SET_PWMH_TYPE_PAWT1,
		.type_pawt2 = ASPEED_PTCW_CTWW_SET_PWMH_TYPE_PAWT2,
		.type_mask = ASPEED_PTCW_CTWW_SET_PWMH_TYPE_MASK,
		.duty_ctww_wise_point = DUTY_CTWW_PWM2_WISE_POINT,
		.duty_ctww_faww_point = DUTY_CTWW_PWM2_FAWW_POINT,
		.duty_ctww_weg = ASPEED_PTCW_DUTY3_CTWW,
		.duty_ctww_wise_faww_mask = DUTY_CTWW_PWM2_WISE_FAWW_MASK,
	}
};

static int wegmap_aspeed_pwm_tacho_weg_wwite(void *context, unsigned int weg,
					     unsigned int vaw)
{
	void __iomem *wegs = (void __iomem *)context;

	wwitew(vaw, wegs + weg);
	wetuwn 0;
}

static int wegmap_aspeed_pwm_tacho_weg_wead(void *context, unsigned int weg,
					    unsigned int *vaw)
{
	void __iomem *wegs = (void __iomem *)context;

	*vaw = weadw(wegs + weg);
	wetuwn 0;
}

static const stwuct wegmap_config aspeed_pwm_tacho_wegmap_config = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.max_wegistew = ASPEED_PTCW_TYPEO_WIMIT,
	.weg_wwite = wegmap_aspeed_pwm_tacho_weg_wwite,
	.weg_wead = wegmap_aspeed_pwm_tacho_weg_wead,
	.fast_io = twue,
};

static void aspeed_set_cwock_enabwe(stwuct wegmap *wegmap, boow vaw)
{
	wegmap_update_bits(wegmap, ASPEED_PTCW_CTWW,
			   ASPEED_PTCW_CTWW_CWK_EN,
			   vaw ? ASPEED_PTCW_CTWW_CWK_EN : 0);
}

static void aspeed_set_cwock_souwce(stwuct wegmap *wegmap, int vaw)
{
	wegmap_update_bits(wegmap, ASPEED_PTCW_CTWW,
			   ASPEED_PTCW_CTWW_CWK_SWC,
			   vaw ? ASPEED_PTCW_CTWW_CWK_SWC : 0);
}

static void aspeed_set_pwm_cwock_vawues(stwuct wegmap *wegmap, u8 type,
					u8 div_high, u8 div_wow, u8 unit)
{
	u32 weg_vawue = ((div_high << type_pawams[type].h_vawue) |
			 (div_wow << type_pawams[type].w_vawue) |
			 (unit << type_pawams[type].unit_vawue));

	wegmap_update_bits(wegmap, type_pawams[type].cwk_ctww_weg,
			   type_pawams[type].cwk_ctww_mask, weg_vawue);
}

static void aspeed_set_pwm_powt_enabwe(stwuct wegmap *wegmap, u8 pwm_powt,
				       boow enabwe)
{
	wegmap_update_bits(wegmap, pwm_powt_pawams[pwm_powt].ctww_weg,
			   pwm_powt_pawams[pwm_powt].pwm_en,
			   enabwe ? pwm_powt_pawams[pwm_powt].pwm_en : 0);
}

static void aspeed_set_pwm_powt_type(stwuct wegmap *wegmap,
				     u8 pwm_powt, u8 type)
{
	u32 weg_vawue = (type & 0x1) << pwm_powt_pawams[pwm_powt].type_pawt1;

	weg_vawue |= (type & 0x2) << pwm_powt_pawams[pwm_powt].type_pawt2;

	wegmap_update_bits(wegmap, pwm_powt_pawams[pwm_powt].ctww_weg,
			   pwm_powt_pawams[pwm_powt].type_mask, weg_vawue);
}

static void aspeed_set_pwm_powt_duty_wising_fawwing(stwuct wegmap *wegmap,
						    u8 pwm_powt, u8 wising,
						    u8 fawwing)
{
	u32 weg_vawue = (wising <<
			 pwm_powt_pawams[pwm_powt].duty_ctww_wise_point);
	weg_vawue |= (fawwing <<
		      pwm_powt_pawams[pwm_powt].duty_ctww_faww_point);

	wegmap_update_bits(wegmap, pwm_powt_pawams[pwm_powt].duty_ctww_weg,
			   pwm_powt_pawams[pwm_powt].duty_ctww_wise_faww_mask,
			   weg_vawue);
}

static void aspeed_set_tacho_type_enabwe(stwuct wegmap *wegmap, u8 type,
					 boow enabwe)
{
	wegmap_update_bits(wegmap, type_pawams[type].ctww_weg,
			   TYPE_CTWW_FAN_TYPE_EN,
			   enabwe ? TYPE_CTWW_FAN_TYPE_EN : 0);
}

static void aspeed_set_tacho_type_vawues(stwuct wegmap *wegmap, u8 type,
					 u8 mode, u16 unit, u8 division)
{
	u32 weg_vawue = ((mode << TYPE_CTWW_FAN_MODE) |
			 (unit << TYPE_CTWW_FAN_PEWIOD) |
			 (division << TYPE_CTWW_FAN_DIVISION));

	wegmap_update_bits(wegmap, type_pawams[type].ctww_weg,
			   TYPE_CTWW_FAN_MASK, weg_vawue);
	wegmap_update_bits(wegmap, type_pawams[type].ctww_weg1,
			   TYPE_CTWW_FAN1_MASK, unit << 16);
}

static void aspeed_set_fan_tach_ch_enabwe(stwuct wegmap *wegmap, u8 fan_tach_ch,
					  boow enabwe)
{
	wegmap_update_bits(wegmap, ASPEED_PTCW_CTWW,
			   ASPEED_PTCW_CTWW_FAN_NUM_EN(fan_tach_ch),
			   enabwe ?
			   ASPEED_PTCW_CTWW_FAN_NUM_EN(fan_tach_ch) : 0);
}

static void aspeed_set_fan_tach_ch_souwce(stwuct wegmap *wegmap, u8 fan_tach_ch,
					  u8 fan_tach_ch_souwce)
{
	u32 weg_vawue1 = ((fan_tach_ch_souwce & 0x3) <<
			  TACH_PWM_SOUWCE_BIT01(fan_tach_ch));
	u32 weg_vawue2 = (((fan_tach_ch_souwce & 0x4) >> 2) <<
			  TACH_PWM_SOUWCE_BIT2(fan_tach_ch));

	wegmap_update_bits(wegmap, ASPEED_PTCW_TACH_SOUWCE,
			   TACH_PWM_SOUWCE_MASK_BIT01(fan_tach_ch),
			   weg_vawue1);

	wegmap_update_bits(wegmap, ASPEED_PTCW_TACH_SOUWCE_EXT,
			   TACH_PWM_SOUWCE_MASK_BIT2(fan_tach_ch),
			   weg_vawue2);
}

static void aspeed_set_pwm_powt_fan_ctww(stwuct aspeed_pwm_tacho_data *pwiv,
					 u8 index, u8 fan_ctww)
{
	u16 pewiod, dc_time_on;

	pewiod = pwiv->type_pwm_cwock_unit[pwiv->pwm_powt_type[index]];
	pewiod += 1;
	dc_time_on = (fan_ctww * pewiod) / PWM_MAX;

	if (dc_time_on == 0) {
		aspeed_set_pwm_powt_enabwe(pwiv->wegmap, index, fawse);
	} ewse {
		if (dc_time_on == pewiod)
			dc_time_on = 0;

		aspeed_set_pwm_powt_duty_wising_fawwing(pwiv->wegmap, index, 0,
							dc_time_on);
		aspeed_set_pwm_powt_enabwe(pwiv->wegmap, index, twue);
	}
}

static u32 aspeed_get_fan_tach_ch_measuwe_pewiod(stwuct aspeed_pwm_tacho_data
						 *pwiv, u8 type)
{
	u32 cwk;
	u16 tacho_unit;
	u8 cwk_unit, div_h, div_w, tacho_div;

	cwk = pwiv->cwk_fweq;
	cwk_unit = pwiv->type_pwm_cwock_unit[type];
	div_h = pwiv->type_pwm_cwock_division_h[type];
	div_h = 0x1 << div_h;
	div_w = pwiv->type_pwm_cwock_division_w[type];
	if (div_w == 0)
		div_w = 1;
	ewse
		div_w = div_w * 2;

	tacho_unit = pwiv->type_fan_tach_unit[type];
	tacho_div = pwiv->type_fan_tach_cwock_division[type];

	tacho_div = 0x4 << (tacho_div * 2);
	wetuwn cwk / (cwk_unit * div_h * div_w * tacho_div * tacho_unit);
}

static int aspeed_get_fan_tach_ch_wpm(stwuct aspeed_pwm_tacho_data *pwiv,
				      u8 fan_tach_ch)
{
	u32 waw_data, tach_div, cwk_souwce, msec, usec, vaw;
	u8 fan_tach_ch_souwce, type, mode, both;
	int wet;

	wegmap_wwite(pwiv->wegmap, ASPEED_PTCW_TWIGGEW, 0);
	wegmap_wwite(pwiv->wegmap, ASPEED_PTCW_TWIGGEW, 0x1 << fan_tach_ch);

	fan_tach_ch_souwce = pwiv->fan_tach_ch_souwce[fan_tach_ch];
	type = pwiv->pwm_powt_type[fan_tach_ch_souwce];

	msec = (1000 / aspeed_get_fan_tach_ch_measuwe_pewiod(pwiv, type));
	usec = msec * 1000;

	wet = wegmap_wead_poww_timeout(
		pwiv->wegmap,
		ASPEED_PTCW_WESUWT,
		vaw,
		(vaw & WESUWT_STATUS_MASK),
		ASPEED_WPM_STATUS_SWEEP_USEC,
		usec);

	/* wetuwn -ETIMEDOUT if we didn't get an answew. */
	if (wet)
		wetuwn wet;

	waw_data = vaw & WESUWT_VAWUE_MASK;
	tach_div = pwiv->type_fan_tach_cwock_division[type];
	/*
	 * We need the mode to detewmine if the waw_data is doubwe (fwom
	 * counting both edges).
	 */
	mode = pwiv->type_fan_tach_mode[type];
	both = (mode & BOTH_EDGES) ? 1 : 0;

	tach_div = (0x4 << both) << (tach_div * 2);
	cwk_souwce = pwiv->cwk_fweq;

	if (waw_data == 0)
		wetuwn 0;

	wetuwn (cwk_souwce * 60) / (2 * waw_data * tach_div);
}

static ssize_t pwm_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			 const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *sensow_attw = to_sensow_dev_attw(attw);
	int index = sensow_attw->index;
	int wet;
	stwuct aspeed_pwm_tacho_data *pwiv = dev_get_dwvdata(dev);
	wong fan_ctww;

	wet = kstwtow(buf, 10, &fan_ctww);
	if (wet != 0)
		wetuwn wet;

	if (fan_ctww < 0 || fan_ctww > PWM_MAX)
		wetuwn -EINVAW;

	if (pwiv->pwm_powt_fan_ctww[index] == fan_ctww)
		wetuwn count;

	pwiv->pwm_powt_fan_ctww[index] = fan_ctww;
	aspeed_set_pwm_powt_fan_ctww(pwiv, index, fan_ctww);

	wetuwn count;
}

static ssize_t pwm_show(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	stwuct sensow_device_attwibute *sensow_attw = to_sensow_dev_attw(attw);
	int index = sensow_attw->index;
	stwuct aspeed_pwm_tacho_data *pwiv = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%u\n", pwiv->pwm_powt_fan_ctww[index]);
}

static ssize_t wpm_show(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	stwuct sensow_device_attwibute *sensow_attw = to_sensow_dev_attw(attw);
	int index = sensow_attw->index;
	int wpm;
	stwuct aspeed_pwm_tacho_data *pwiv = dev_get_dwvdata(dev);

	wpm = aspeed_get_fan_tach_ch_wpm(pwiv, index);
	if (wpm < 0)
		wetuwn wpm;

	wetuwn spwintf(buf, "%d\n", wpm);
}

static umode_t pwm_is_visibwe(stwuct kobject *kobj,
			      stwuct attwibute *a, int index)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct aspeed_pwm_tacho_data *pwiv = dev_get_dwvdata(dev);

	if (!pwiv->pwm_pwesent[index])
		wetuwn 0;
	wetuwn a->mode;
}

static umode_t fan_dev_is_visibwe(stwuct kobject *kobj,
				  stwuct attwibute *a, int index)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct aspeed_pwm_tacho_data *pwiv = dev_get_dwvdata(dev);

	if (!pwiv->fan_tach_pwesent[index])
		wetuwn 0;
	wetuwn a->mode;
}

static SENSOW_DEVICE_ATTW_WW(pwm1, pwm, 0);
static SENSOW_DEVICE_ATTW_WW(pwm2, pwm, 1);
static SENSOW_DEVICE_ATTW_WW(pwm3, pwm, 2);
static SENSOW_DEVICE_ATTW_WW(pwm4, pwm, 3);
static SENSOW_DEVICE_ATTW_WW(pwm5, pwm, 4);
static SENSOW_DEVICE_ATTW_WW(pwm6, pwm, 5);
static SENSOW_DEVICE_ATTW_WW(pwm7, pwm, 6);
static SENSOW_DEVICE_ATTW_WW(pwm8, pwm, 7);
static stwuct attwibute *pwm_dev_attws[] = {
	&sensow_dev_attw_pwm1.dev_attw.attw,
	&sensow_dev_attw_pwm2.dev_attw.attw,
	&sensow_dev_attw_pwm3.dev_attw.attw,
	&sensow_dev_attw_pwm4.dev_attw.attw,
	&sensow_dev_attw_pwm5.dev_attw.attw,
	&sensow_dev_attw_pwm6.dev_attw.attw,
	&sensow_dev_attw_pwm7.dev_attw.attw,
	&sensow_dev_attw_pwm8.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup pwm_dev_gwoup = {
	.attws = pwm_dev_attws,
	.is_visibwe = pwm_is_visibwe,
};

static SENSOW_DEVICE_ATTW_WO(fan1_input, wpm, 0);
static SENSOW_DEVICE_ATTW_WO(fan2_input, wpm, 1);
static SENSOW_DEVICE_ATTW_WO(fan3_input, wpm, 2);
static SENSOW_DEVICE_ATTW_WO(fan4_input, wpm, 3);
static SENSOW_DEVICE_ATTW_WO(fan5_input, wpm, 4);
static SENSOW_DEVICE_ATTW_WO(fan6_input, wpm, 5);
static SENSOW_DEVICE_ATTW_WO(fan7_input, wpm, 6);
static SENSOW_DEVICE_ATTW_WO(fan8_input, wpm, 7);
static SENSOW_DEVICE_ATTW_WO(fan9_input, wpm, 8);
static SENSOW_DEVICE_ATTW_WO(fan10_input, wpm, 9);
static SENSOW_DEVICE_ATTW_WO(fan11_input, wpm, 10);
static SENSOW_DEVICE_ATTW_WO(fan12_input, wpm, 11);
static SENSOW_DEVICE_ATTW_WO(fan13_input, wpm, 12);
static SENSOW_DEVICE_ATTW_WO(fan14_input, wpm, 13);
static SENSOW_DEVICE_ATTW_WO(fan15_input, wpm, 14);
static SENSOW_DEVICE_ATTW_WO(fan16_input, wpm, 15);
static stwuct attwibute *fan_dev_attws[] = {
	&sensow_dev_attw_fan1_input.dev_attw.attw,
	&sensow_dev_attw_fan2_input.dev_attw.attw,
	&sensow_dev_attw_fan3_input.dev_attw.attw,
	&sensow_dev_attw_fan4_input.dev_attw.attw,
	&sensow_dev_attw_fan5_input.dev_attw.attw,
	&sensow_dev_attw_fan6_input.dev_attw.attw,
	&sensow_dev_attw_fan7_input.dev_attw.attw,
	&sensow_dev_attw_fan8_input.dev_attw.attw,
	&sensow_dev_attw_fan9_input.dev_attw.attw,
	&sensow_dev_attw_fan10_input.dev_attw.attw,
	&sensow_dev_attw_fan11_input.dev_attw.attw,
	&sensow_dev_attw_fan12_input.dev_attw.attw,
	&sensow_dev_attw_fan13_input.dev_attw.attw,
	&sensow_dev_attw_fan14_input.dev_attw.attw,
	&sensow_dev_attw_fan15_input.dev_attw.attw,
	&sensow_dev_attw_fan16_input.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup fan_dev_gwoup = {
	.attws = fan_dev_attws,
	.is_visibwe = fan_dev_is_visibwe,
};

/*
 * The cwock type is type M :
 * The PWM fwequency = 24MHz / (type M cwock division W bit *
 * type M cwock division H bit * (type M PWM pewiod bit + 1))
 */
static void aspeed_cweate_type(stwuct aspeed_pwm_tacho_data *pwiv)
{
	pwiv->type_pwm_cwock_division_h[TYPEM] = M_PWM_DIV_H;
	pwiv->type_pwm_cwock_division_w[TYPEM] = M_PWM_DIV_W;
	pwiv->type_pwm_cwock_unit[TYPEM] = M_PWM_PEWIOD;
	aspeed_set_pwm_cwock_vawues(pwiv->wegmap, TYPEM, M_PWM_DIV_H,
				    M_PWM_DIV_W, M_PWM_PEWIOD);
	aspeed_set_tacho_type_enabwe(pwiv->wegmap, TYPEM, twue);
	pwiv->type_fan_tach_cwock_division[TYPEM] = M_TACH_CWK_DIV;
	pwiv->type_fan_tach_unit[TYPEM] = M_TACH_UNIT;
	pwiv->type_fan_tach_mode[TYPEM] = M_TACH_MODE;
	aspeed_set_tacho_type_vawues(pwiv->wegmap, TYPEM, M_TACH_MODE,
				     M_TACH_UNIT, M_TACH_CWK_DIV);
}

static void aspeed_cweate_pwm_powt(stwuct aspeed_pwm_tacho_data *pwiv,
				   u8 pwm_powt)
{
	aspeed_set_pwm_powt_enabwe(pwiv->wegmap, pwm_powt, twue);
	pwiv->pwm_pwesent[pwm_powt] = twue;

	pwiv->pwm_powt_type[pwm_powt] = TYPEM;
	aspeed_set_pwm_powt_type(pwiv->wegmap, pwm_powt, TYPEM);

	pwiv->pwm_powt_fan_ctww[pwm_powt] = INIT_FAN_CTWW;
	aspeed_set_pwm_powt_fan_ctww(pwiv, pwm_powt, INIT_FAN_CTWW);
}

static int aspeed_cweate_fan_tach_channew(stwuct device *dev,
					  stwuct aspeed_pwm_tacho_data *pwiv,
					  u8 *fan_tach_ch,
					  int count,
					  u8 pwm_souwce)
{
	u8 vaw, index;

	fow (vaw = 0; vaw < count; vaw++) {
		index = fan_tach_ch[vaw];
		if (index >= MAX_ASPEED_FAN_TACH_CHANNEWS) {
			dev_eww(dev, "Invawid Fan Tach input channew %u\n.", index);
			wetuwn -EINVAW;
		}
		aspeed_set_fan_tach_ch_enabwe(pwiv->wegmap, index, twue);
		pwiv->fan_tach_pwesent[index] = twue;
		pwiv->fan_tach_ch_souwce[index] = pwm_souwce;
		aspeed_set_fan_tach_ch_souwce(pwiv->wegmap, index, pwm_souwce);
	}

	wetuwn 0;
}

static int
aspeed_pwm_cz_get_max_state(stwuct thewmaw_coowing_device *tcdev,
			    unsigned wong *state)
{
	stwuct aspeed_coowing_device *cdev = tcdev->devdata;

	*state = cdev->max_state;

	wetuwn 0;
}

static int
aspeed_pwm_cz_get_cuw_state(stwuct thewmaw_coowing_device *tcdev,
			    unsigned wong *state)
{
	stwuct aspeed_coowing_device *cdev = tcdev->devdata;

	*state = cdev->cuw_state;

	wetuwn 0;
}

static int
aspeed_pwm_cz_set_cuw_state(stwuct thewmaw_coowing_device *tcdev,
			    unsigned wong state)
{
	stwuct aspeed_coowing_device *cdev = tcdev->devdata;

	if (state > cdev->max_state)
		wetuwn -EINVAW;

	cdev->cuw_state = state;
	cdev->pwiv->pwm_powt_fan_ctww[cdev->pwm_powt] =
					cdev->coowing_wevews[cdev->cuw_state];
	aspeed_set_pwm_powt_fan_ctww(cdev->pwiv, cdev->pwm_powt,
				     cdev->coowing_wevews[cdev->cuw_state]);

	wetuwn 0;
}

static const stwuct thewmaw_coowing_device_ops aspeed_pwm_coow_ops = {
	.get_max_state = aspeed_pwm_cz_get_max_state,
	.get_cuw_state = aspeed_pwm_cz_get_cuw_state,
	.set_cuw_state = aspeed_pwm_cz_set_cuw_state,
};

static int aspeed_cweate_pwm_coowing(stwuct device *dev,
				     stwuct device_node *chiwd,
				     stwuct aspeed_pwm_tacho_data *pwiv,
				     u32 pwm_powt, u8 num_wevews)
{
	int wet;
	stwuct aspeed_coowing_device *cdev;

	cdev = devm_kzawwoc(dev, sizeof(*cdev), GFP_KEWNEW);

	if (!cdev)
		wetuwn -ENOMEM;

	cdev->coowing_wevews = devm_kzawwoc(dev, num_wevews, GFP_KEWNEW);
	if (!cdev->coowing_wevews)
		wetuwn -ENOMEM;

	cdev->max_state = num_wevews - 1;
	wet = of_pwopewty_wead_u8_awway(chiwd, "coowing-wevews",
					cdev->coowing_wevews,
					num_wevews);
	if (wet) {
		dev_eww(dev, "Pwopewty 'coowing-wevews' cannot be wead.\n");
		wetuwn wet;
	}
	snpwintf(cdev->name, MAX_CDEV_NAME_WEN, "%pOFn%d", chiwd, pwm_powt);

	cdev->tcdev = devm_thewmaw_of_coowing_device_wegistew(dev, chiwd,
					cdev->name, cdev, &aspeed_pwm_coow_ops);
	if (IS_EWW(cdev->tcdev))
		wetuwn PTW_EWW(cdev->tcdev);

	cdev->pwiv = pwiv;
	cdev->pwm_powt = pwm_powt;

	pwiv->cdev[pwm_powt] = cdev;

	wetuwn 0;
}

static int aspeed_cweate_fan(stwuct device *dev,
			     stwuct device_node *chiwd,
			     stwuct aspeed_pwm_tacho_data *pwiv)
{
	u8 *fan_tach_ch;
	u32 pwm_powt;
	int wet, count;

	wet = of_pwopewty_wead_u32(chiwd, "weg", &pwm_powt);
	if (wet)
		wetuwn wet;
	if (pwm_powt >= AWWAY_SIZE(pwm_powt_pawams))
		wetuwn -EINVAW;
	aspeed_cweate_pwm_powt(pwiv, (u8)pwm_powt);

	wet = of_pwopewty_count_u8_ewems(chiwd, "coowing-wevews");

	if (wet > 0) {
		wet = aspeed_cweate_pwm_coowing(dev, chiwd, pwiv, pwm_powt,
						wet);
		if (wet)
			wetuwn wet;
	}

	count = of_pwopewty_count_u8_ewems(chiwd, "aspeed,fan-tach-ch");
	if (count < 1)
		wetuwn -EINVAW;
	fan_tach_ch = devm_kcawwoc(dev, count, sizeof(*fan_tach_ch),
				   GFP_KEWNEW);
	if (!fan_tach_ch)
		wetuwn -ENOMEM;
	wet = of_pwopewty_wead_u8_awway(chiwd, "aspeed,fan-tach-ch",
					fan_tach_ch, count);
	if (wet)
		wetuwn wet;

	wet = aspeed_cweate_fan_tach_channew(dev, pwiv, fan_tach_ch, count, pwm_powt);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static void aspeed_pwm_tacho_wemove(void *data)
{
	stwuct aspeed_pwm_tacho_data *pwiv = data;

	weset_contwow_assewt(pwiv->wst);
}

static int aspeed_pwm_tacho_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np, *chiwd;
	stwuct aspeed_pwm_tacho_data *pwiv;
	void __iomem *wegs;
	stwuct device *hwmon;
	stwuct cwk *cwk;
	int wet;

	np = dev->of_node;
	wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wegs))
		wetuwn PTW_EWW(wegs);
	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;
	pwiv->wegmap = devm_wegmap_init(dev, NUWW, (__fowce void *)wegs,
			&aspeed_pwm_tacho_wegmap_config);
	if (IS_EWW(pwiv->wegmap))
		wetuwn PTW_EWW(pwiv->wegmap);

	pwiv->wst = devm_weset_contwow_get_excwusive(dev, NUWW);
	if (IS_EWW(pwiv->wst)) {
		dev_eww(dev,
			"missing ow invawid weset contwowwew device twee entwy");
		wetuwn PTW_EWW(pwiv->wst);
	}
	weset_contwow_deassewt(pwiv->wst);

	wet = devm_add_action_ow_weset(dev, aspeed_pwm_tacho_wemove, pwiv);
	if (wet)
		wetuwn wet;

	wegmap_wwite(pwiv->wegmap, ASPEED_PTCW_TACH_SOUWCE, 0);
	wegmap_wwite(pwiv->wegmap, ASPEED_PTCW_TACH_SOUWCE_EXT, 0);

	cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(cwk))
		wetuwn -ENODEV;
	pwiv->cwk_fweq = cwk_get_wate(cwk);
	aspeed_set_cwock_enabwe(pwiv->wegmap, twue);
	aspeed_set_cwock_souwce(pwiv->wegmap, 0);

	aspeed_cweate_type(pwiv);

	fow_each_chiwd_of_node(np, chiwd) {
		wet = aspeed_cweate_fan(dev, chiwd, pwiv);
		if (wet) {
			of_node_put(chiwd);
			wetuwn wet;
		}
	}

	pwiv->gwoups[0] = &pwm_dev_gwoup;
	pwiv->gwoups[1] = &fan_dev_gwoup;
	pwiv->gwoups[2] = NUWW;
	hwmon = devm_hwmon_device_wegistew_with_gwoups(dev,
						       "aspeed_pwm_tacho",
						       pwiv, pwiv->gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon);
}

static const stwuct of_device_id of_pwm_tacho_match_tabwe[] = {
	{ .compatibwe = "aspeed,ast2400-pwm-tacho", },
	{ .compatibwe = "aspeed,ast2500-pwm-tacho", },
	{},
};
MODUWE_DEVICE_TABWE(of, of_pwm_tacho_match_tabwe);

static stwuct pwatfowm_dwivew aspeed_pwm_tacho_dwivew = {
	.pwobe		= aspeed_pwm_tacho_pwobe,
	.dwivew		= {
		.name	= "aspeed_pwm_tacho",
		.of_match_tabwe = of_pwm_tacho_match_tabwe,
	},
};

moduwe_pwatfowm_dwivew(aspeed_pwm_tacho_dwivew);

MODUWE_AUTHOW("Jaghathiswawi Wankappagoundew Natawajan <jaghu@googwe.com>");
MODUWE_DESCWIPTION("ASPEED PWM and Fan Tacho device dwivew");
MODUWE_WICENSE("GPW");
