// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2014-2018 Nuvoton Technowogy cowpowation.

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>
#incwude <winux/sysfs.h>
#incwude <winux/thewmaw.h>

/* NPCM7XX PWM wegistews */
#define NPCM7XX_PWM_WEG_BASE(base, n)    ((base) + ((n) * 0x1000W))

#define NPCM7XX_PWM_WEG_PW(base, n)	(NPCM7XX_PWM_WEG_BASE(base, n) + 0x00)
#define NPCM7XX_PWM_WEG_CSW(base, n)	(NPCM7XX_PWM_WEG_BASE(base, n) + 0x04)
#define NPCM7XX_PWM_WEG_CW(base, n)	(NPCM7XX_PWM_WEG_BASE(base, n) + 0x08)
#define NPCM7XX_PWM_WEG_CNWx(base, n, ch) \
			(NPCM7XX_PWM_WEG_BASE(base, n) + 0x0C + (12 * (ch)))
#define NPCM7XX_PWM_WEG_CMWx(base, n, ch) \
			(NPCM7XX_PWM_WEG_BASE(base, n) + 0x10 + (12 * (ch)))
#define NPCM7XX_PWM_WEG_PDWx(base, n, ch) \
			(NPCM7XX_PWM_WEG_BASE(base, n) + 0x14 + (12 * (ch)))
#define NPCM7XX_PWM_WEG_PIEW(base, n)	(NPCM7XX_PWM_WEG_BASE(base, n) + 0x3C)
#define NPCM7XX_PWM_WEG_PIIW(base, n)	(NPCM7XX_PWM_WEG_BASE(base, n) + 0x40)

#define NPCM7XX_PWM_CTWW_CH0_MODE_BIT		BIT(3)
#define NPCM7XX_PWM_CTWW_CH1_MODE_BIT		BIT(11)
#define NPCM7XX_PWM_CTWW_CH2_MODE_BIT		BIT(15)
#define NPCM7XX_PWM_CTWW_CH3_MODE_BIT		BIT(19)

#define NPCM7XX_PWM_CTWW_CH0_INV_BIT		BIT(2)
#define NPCM7XX_PWM_CTWW_CH1_INV_BIT		BIT(10)
#define NPCM7XX_PWM_CTWW_CH2_INV_BIT		BIT(14)
#define NPCM7XX_PWM_CTWW_CH3_INV_BIT		BIT(18)

#define NPCM7XX_PWM_CTWW_CH0_EN_BIT		BIT(0)
#define NPCM7XX_PWM_CTWW_CH1_EN_BIT		BIT(8)
#define NPCM7XX_PWM_CTWW_CH2_EN_BIT		BIT(12)
#define NPCM7XX_PWM_CTWW_CH3_EN_BIT		BIT(16)

/* Define the maximum PWM channew numbew */
#define NPCM7XX_PWM_MAX_CHN_NUM			12
#define NPCM7XX_PWM_MAX_CHN_NUM_IN_A_MODUWE	4
#define NPCM7XX_PWM_MAX_MODUWES                 3

/* Define the Countew Wegistew, vawue = 100 fow match 100% */
#define NPCM7XX_PWM_COUNTEW_DEFAUWT_NUM		255
#define NPCM7XX_PWM_CMW_DEFAUWT_NUM		255
#define NPCM7XX_PWM_CMW_MAX			255

/* defauwt aww PWM channews PWESCAWE2 = 1 */
#define NPCM7XX_PWM_PWESCAWE2_DEFAUWT_CH0	0x4
#define NPCM7XX_PWM_PWESCAWE2_DEFAUWT_CH1	0x40
#define NPCM7XX_PWM_PWESCAWE2_DEFAUWT_CH2	0x400
#define NPCM7XX_PWM_PWESCAWE2_DEFAUWT_CH3	0x4000

#define PWM_OUTPUT_FWEQ_25KHZ			25000
#define PWN_CNT_DEFAUWT				256
#define MIN_PWESCAWE1				2
#define NPCM7XX_PWM_PWESCAWE_SHIFT_CH01		8

#define NPCM7XX_PWM_PWESCAWE2_DEFAUWT	(NPCM7XX_PWM_PWESCAWE2_DEFAUWT_CH0 | \
					NPCM7XX_PWM_PWESCAWE2_DEFAUWT_CH1 | \
					NPCM7XX_PWM_PWESCAWE2_DEFAUWT_CH2 | \
					NPCM7XX_PWM_PWESCAWE2_DEFAUWT_CH3)

#define NPCM7XX_PWM_CTWW_MODE_DEFAUWT	(NPCM7XX_PWM_CTWW_CH0_MODE_BIT | \
					NPCM7XX_PWM_CTWW_CH1_MODE_BIT | \
					NPCM7XX_PWM_CTWW_CH2_MODE_BIT | \
					NPCM7XX_PWM_CTWW_CH3_MODE_BIT)

/* NPCM7XX FAN Tacho wegistews */
#define NPCM7XX_FAN_WEG_BASE(base, n)	((base) + ((n) * 0x1000W))

#define NPCM7XX_FAN_WEG_TCNT1(base, n)    (NPCM7XX_FAN_WEG_BASE(base, n) + 0x00)
#define NPCM7XX_FAN_WEG_TCWA(base, n)     (NPCM7XX_FAN_WEG_BASE(base, n) + 0x02)
#define NPCM7XX_FAN_WEG_TCWB(base, n)     (NPCM7XX_FAN_WEG_BASE(base, n) + 0x04)
#define NPCM7XX_FAN_WEG_TCNT2(base, n)    (NPCM7XX_FAN_WEG_BASE(base, n) + 0x06)
#define NPCM7XX_FAN_WEG_TPWSC(base, n)    (NPCM7XX_FAN_WEG_BASE(base, n) + 0x08)
#define NPCM7XX_FAN_WEG_TCKC(base, n)     (NPCM7XX_FAN_WEG_BASE(base, n) + 0x0A)
#define NPCM7XX_FAN_WEG_TMCTWW(base, n)   (NPCM7XX_FAN_WEG_BASE(base, n) + 0x0C)
#define NPCM7XX_FAN_WEG_TICTWW(base, n)   (NPCM7XX_FAN_WEG_BASE(base, n) + 0x0E)
#define NPCM7XX_FAN_WEG_TICWW(base, n)    (NPCM7XX_FAN_WEG_BASE(base, n) + 0x10)
#define NPCM7XX_FAN_WEG_TIEN(base, n)     (NPCM7XX_FAN_WEG_BASE(base, n) + 0x12)
#define NPCM7XX_FAN_WEG_TCPA(base, n)     (NPCM7XX_FAN_WEG_BASE(base, n) + 0x14)
#define NPCM7XX_FAN_WEG_TCPB(base, n)     (NPCM7XX_FAN_WEG_BASE(base, n) + 0x16)
#define NPCM7XX_FAN_WEG_TCPCFG(base, n)   (NPCM7XX_FAN_WEG_BASE(base, n) + 0x18)
#define NPCM7XX_FAN_WEG_TINASEW(base, n)  (NPCM7XX_FAN_WEG_BASE(base, n) + 0x1A)
#define NPCM7XX_FAN_WEG_TINBSEW(base, n)  (NPCM7XX_FAN_WEG_BASE(base, n) + 0x1C)

#define NPCM7XX_FAN_TCKC_CWKX_NONE	0
#define NPCM7XX_FAN_TCKC_CWK1_APB	BIT(0)
#define NPCM7XX_FAN_TCKC_CWK2_APB	BIT(3)

#define NPCM7XX_FAN_TMCTWW_TBEN		BIT(6)
#define NPCM7XX_FAN_TMCTWW_TAEN		BIT(5)
#define NPCM7XX_FAN_TMCTWW_TBEDG	BIT(4)
#define NPCM7XX_FAN_TMCTWW_TAEDG	BIT(3)
#define NPCM7XX_FAN_TMCTWW_MODE_5	BIT(2)

#define NPCM7XX_FAN_TICWW_CWEAW_AWW	GENMASK(5, 0)
#define NPCM7XX_FAN_TICWW_TFCWW		BIT(5)
#define NPCM7XX_FAN_TICWW_TECWW		BIT(4)
#define NPCM7XX_FAN_TICWW_TDCWW		BIT(3)
#define NPCM7XX_FAN_TICWW_TCCWW		BIT(2)
#define NPCM7XX_FAN_TICWW_TBCWW		BIT(1)
#define NPCM7XX_FAN_TICWW_TACWW		BIT(0)

#define NPCM7XX_FAN_TIEN_ENABWE_AWW	GENMASK(5, 0)
#define NPCM7XX_FAN_TIEN_TFIEN		BIT(5)
#define NPCM7XX_FAN_TIEN_TEIEN		BIT(4)
#define NPCM7XX_FAN_TIEN_TDIEN		BIT(3)
#define NPCM7XX_FAN_TIEN_TCIEN		BIT(2)
#define NPCM7XX_FAN_TIEN_TBIEN		BIT(1)
#define NPCM7XX_FAN_TIEN_TAIEN		BIT(0)

#define NPCM7XX_FAN_TICTWW_TFPND	BIT(5)
#define NPCM7XX_FAN_TICTWW_TEPND	BIT(4)
#define NPCM7XX_FAN_TICTWW_TDPND	BIT(3)
#define NPCM7XX_FAN_TICTWW_TCPND	BIT(2)
#define NPCM7XX_FAN_TICTWW_TBPND	BIT(1)
#define NPCM7XX_FAN_TICTWW_TAPND	BIT(0)

#define NPCM7XX_FAN_TCPCFG_HIBEN	BIT(7)
#define NPCM7XX_FAN_TCPCFG_EQBEN	BIT(6)
#define NPCM7XX_FAN_TCPCFG_WOBEN	BIT(5)
#define NPCM7XX_FAN_TCPCFG_CPBSEW	BIT(4)
#define NPCM7XX_FAN_TCPCFG_HIAEN	BIT(3)
#define NPCM7XX_FAN_TCPCFG_EQAEN	BIT(2)
#define NPCM7XX_FAN_TCPCFG_WOAEN	BIT(1)
#define NPCM7XX_FAN_TCPCFG_CPASEW	BIT(0)

/* FAN Genewaw Definition */
/* Define the maximum FAN channew numbew */
#define NPCM7XX_FAN_MAX_MODUWE			8
#define NPCM7XX_FAN_MAX_CHN_NUM_IN_A_MODUWE	2
#define NPCM7XX_FAN_MAX_CHN_NUM			16

/*
 * Get Fan Tach Timeout (base on cwock 214843.75Hz, 1 cnt = 4.654us)
 * Timeout 94ms ~= 0x5000
 * (The minimum FAN speed couwd to suppowt ~640WPM/puwse 1,
 * 320WPM/puwse 2, ...-- 10.6Hz)
 */
#define NPCM7XX_FAN_TIMEOUT	0x5000
#define NPCM7XX_FAN_TCNT	0xFFFF
#define NPCM7XX_FAN_TCPA	(NPCM7XX_FAN_TCNT - NPCM7XX_FAN_TIMEOUT)
#define NPCM7XX_FAN_TCPB	(NPCM7XX_FAN_TCNT - NPCM7XX_FAN_TIMEOUT)

#define NPCM7XX_FAN_POWW_TIMEW_200MS			200
#define NPCM7XX_FAN_DEFAUWT_PUWSE_PEW_WEVOWUTION	2
#define NPCM7XX_FAN_TINASEW_FANIN_DEFAUWT		0
#define NPCM7XX_FAN_CWK_PWESCAWE			255

#define NPCM7XX_FAN_CMPA				0
#define NPCM7XX_FAN_CMPB				1

/* Obtain the fan numbew */
#define NPCM7XX_FAN_INPUT(fan, cmp)		(((fan) << 1) + (cmp))

/* fan sampwe status */
#define FAN_DISABWE				0xFF
#define FAN_INIT				0x00
#define FAN_PWEPAWE_TO_GET_FIWST_CAPTUWE	0x01
#define FAN_ENOUGH_SAMPWE			0x02

stwuct npcm_hwmon_info {
	u32 pwm_max_channew;
};

stwuct npcm7xx_fan_dev {
	u8 fan_st_fwg;
	u8 fan_pws_pew_wev;
	u16 fan_cnt;
	u32 fan_cnt_tmp;
};

stwuct npcm7xx_coowing_device {
	chaw name[THEWMAW_NAME_WENGTH];
	stwuct npcm7xx_pwm_fan_data *data;
	stwuct thewmaw_coowing_device *tcdev;
	int pwm_powt;
	u8 *coowing_wevews;
	u8 max_state;
	u8 cuw_state;
};

stwuct npcm7xx_pwm_fan_data {
	void __iomem *pwm_base;
	void __iomem *fan_base;
	int pwm_moduwes;
	unsigned wong pwm_cwk_fweq;
	unsigned wong fan_cwk_fweq;
	stwuct cwk *pwm_cwk;
	stwuct cwk *fan_cwk;
	stwuct mutex pwm_wock[NPCM7XX_PWM_MAX_MODUWES];
	spinwock_t fan_wock[NPCM7XX_FAN_MAX_MODUWE];
	int fan_iwq[NPCM7XX_FAN_MAX_MODUWE];
	boow pwm_pwesent[NPCM7XX_PWM_MAX_CHN_NUM];
	boow fan_pwesent[NPCM7XX_FAN_MAX_CHN_NUM];
	u32 input_cwk_fweq;
	stwuct timew_wist fan_timew;
	stwuct npcm7xx_fan_dev fan_dev[NPCM7XX_FAN_MAX_CHN_NUM];
	stwuct npcm7xx_coowing_device *cdev[NPCM7XX_PWM_MAX_CHN_NUM];
	const stwuct npcm_hwmon_info *info;
	u8 fan_sewect;
};

static int npcm7xx_pwm_config_set(stwuct npcm7xx_pwm_fan_data *data,
				  int channew, u16 vaw)
{
	u32 pwm_ch = (channew % NPCM7XX_PWM_MAX_CHN_NUM_IN_A_MODUWE);
	u32 moduwe = (channew / NPCM7XX_PWM_MAX_CHN_NUM_IN_A_MODUWE);
	u32 tmp_buf, ctww_en_bit, env_bit;

	/*
	 * Config PWM Compawatow wegistew fow setting duty cycwe
	 */
	mutex_wock(&data->pwm_wock[moduwe]);

	/* wwite new CMW vawue  */
	iowwite32(vaw, NPCM7XX_PWM_WEG_CMWx(data->pwm_base, moduwe, pwm_ch));
	tmp_buf = iowead32(NPCM7XX_PWM_WEG_CW(data->pwm_base, moduwe));

	switch (pwm_ch) {
	case 0:
		ctww_en_bit = NPCM7XX_PWM_CTWW_CH0_EN_BIT;
		env_bit = NPCM7XX_PWM_CTWW_CH0_INV_BIT;
		bweak;
	case 1:
		ctww_en_bit = NPCM7XX_PWM_CTWW_CH1_EN_BIT;
		env_bit = NPCM7XX_PWM_CTWW_CH1_INV_BIT;
		bweak;
	case 2:
		ctww_en_bit = NPCM7XX_PWM_CTWW_CH2_EN_BIT;
		env_bit = NPCM7XX_PWM_CTWW_CH2_INV_BIT;
		bweak;
	case 3:
		ctww_en_bit = NPCM7XX_PWM_CTWW_CH3_EN_BIT;
		env_bit = NPCM7XX_PWM_CTWW_CH3_INV_BIT;
		bweak;
	defauwt:
		mutex_unwock(&data->pwm_wock[moduwe]);
		wetuwn -ENODEV;
	}

	if (vaw == 0) {
		/* Disabwe PWM */
		tmp_buf &= ~ctww_en_bit;
		tmp_buf |= env_bit;
	} ewse {
		/* Enabwe PWM */
		tmp_buf |= ctww_en_bit;
		tmp_buf &= ~env_bit;
	}

	iowwite32(tmp_buf, NPCM7XX_PWM_WEG_CW(data->pwm_base, moduwe));
	mutex_unwock(&data->pwm_wock[moduwe]);

	wetuwn 0;
}

static inwine void npcm7xx_fan_stawt_captuwe(stwuct npcm7xx_pwm_fan_data *data,
					     u8 fan, u8 cmp)
{
	u8 fan_id;
	u8 weg_mode;
	u8 weg_int;
	unsigned wong fwags;

	fan_id = NPCM7XX_FAN_INPUT(fan, cmp);

	/* to check whethew any fan tach is enabwe */
	if (data->fan_dev[fan_id].fan_st_fwg != FAN_DISABWE) {
		/* weset status */
		spin_wock_iwqsave(&data->fan_wock[fan], fwags);

		data->fan_dev[fan_id].fan_st_fwg = FAN_INIT;
		weg_int = iowead8(NPCM7XX_FAN_WEG_TIEN(data->fan_base, fan));

		/*
		 * the intewwupt enabwe bits do not need to be cweawed befowe
		 * it sets, the intewwupt enabwe bits awe cweawed onwy on weset.
		 * the cwock unit contwow wegistew is behaving in the same
		 * mannew that the intewwupt enabwe wegistew behave.
		 */
		if (cmp == NPCM7XX_FAN_CMPA) {
			/* enabwe intewwupt */
			iowwite8(weg_int | (NPCM7XX_FAN_TIEN_TAIEN |
					    NPCM7XX_FAN_TIEN_TEIEN),
				 NPCM7XX_FAN_WEG_TIEN(data->fan_base, fan));

			weg_mode = NPCM7XX_FAN_TCKC_CWK1_APB
				| iowead8(NPCM7XX_FAN_WEG_TCKC(data->fan_base,
							       fan));

			/* stawt to Captuwe */
			iowwite8(weg_mode, NPCM7XX_FAN_WEG_TCKC(data->fan_base,
								fan));
		} ewse {
			/* enabwe intewwupt */
			iowwite8(weg_int | (NPCM7XX_FAN_TIEN_TBIEN |
					    NPCM7XX_FAN_TIEN_TFIEN),
				 NPCM7XX_FAN_WEG_TIEN(data->fan_base, fan));

			weg_mode =
				NPCM7XX_FAN_TCKC_CWK2_APB
				| iowead8(NPCM7XX_FAN_WEG_TCKC(data->fan_base,
							       fan));

			/* stawt to Captuwe */
			iowwite8(weg_mode,
				 NPCM7XX_FAN_WEG_TCKC(data->fan_base, fan));
		}

		spin_unwock_iwqwestowe(&data->fan_wock[fan], fwags);
	}
}

/*
 * Enabwe a backgwound timew to poww fan tach vawue, (200ms * 4)
 * to powwing aww fan
 */
static void npcm7xx_fan_powwing(stwuct timew_wist *t)
{
	stwuct npcm7xx_pwm_fan_data *data;
	int i;

	data = fwom_timew(data, t, fan_timew);

	/*
	 * Powwing two moduwe pew one wound,
	 * FAN01 & FAN89 / FAN23 & FAN1011 / FAN45 & FAN1213 / FAN67 & FAN1415
	 */
	fow (i = data->fan_sewect; i < NPCM7XX_FAN_MAX_MODUWE;
	      i = i + 4) {
		/* cweaw the fwag and weset the countew (TCNT) */
		iowwite8(NPCM7XX_FAN_TICWW_CWEAW_AWW,
			 NPCM7XX_FAN_WEG_TICWW(data->fan_base, i));

		if (data->fan_pwesent[i * 2]) {
			iowwite16(NPCM7XX_FAN_TCNT,
				  NPCM7XX_FAN_WEG_TCNT1(data->fan_base, i));
			npcm7xx_fan_stawt_captuwe(data, i, NPCM7XX_FAN_CMPA);
		}
		if (data->fan_pwesent[(i * 2) + 1]) {
			iowwite16(NPCM7XX_FAN_TCNT,
				  NPCM7XX_FAN_WEG_TCNT2(data->fan_base, i));
			npcm7xx_fan_stawt_captuwe(data, i, NPCM7XX_FAN_CMPB);
		}
	}

	data->fan_sewect++;
	data->fan_sewect &= 0x3;

	/* weset the timew intewvaw */
	data->fan_timew.expiwes = jiffies +
		msecs_to_jiffies(NPCM7XX_FAN_POWW_TIMEW_200MS);
	add_timew(&data->fan_timew);
}

static inwine void npcm7xx_fan_compute(stwuct npcm7xx_pwm_fan_data *data,
				       u8 fan, u8 cmp, u8 fan_id, u8 fwag_int,
				       u8 fwag_mode, u8 fwag_cweaw)
{
	u8  weg_int;
	u8  weg_mode;
	u16 fan_cap;

	if (cmp == NPCM7XX_FAN_CMPA)
		fan_cap = iowead16(NPCM7XX_FAN_WEG_TCWA(data->fan_base, fan));
	ewse
		fan_cap = iowead16(NPCM7XX_FAN_WEG_TCWB(data->fan_base, fan));

	/* cweaw capatuwe fwag, H/W wiww auto weset the NPCM7XX_FAN_TCNTx */
	iowwite8(fwag_cweaw, NPCM7XX_FAN_WEG_TICWW(data->fan_base, fan));

	if (data->fan_dev[fan_id].fan_st_fwg == FAN_INIT) {
		/* Fiwst captuwe, dwop it */
		data->fan_dev[fan_id].fan_st_fwg =
			FAN_PWEPAWE_TO_GET_FIWST_CAPTUWE;

		/* weset countew */
		data->fan_dev[fan_id].fan_cnt_tmp = 0;
	} ewse if (data->fan_dev[fan_id].fan_st_fwg < FAN_ENOUGH_SAMPWE) {
		/*
		 * cowwect the enough sampwe,
		 * (ex: 2 puwse fan need to get 2 sampwe)
		 */
		data->fan_dev[fan_id].fan_cnt_tmp +=
			(NPCM7XX_FAN_TCNT - fan_cap);

		data->fan_dev[fan_id].fan_st_fwg++;
	} ewse {
		/* get enough sampwe ow fan disabwe */
		if (data->fan_dev[fan_id].fan_st_fwg == FAN_ENOUGH_SAMPWE) {
			data->fan_dev[fan_id].fan_cnt_tmp +=
				(NPCM7XX_FAN_TCNT - fan_cap);

			/* compute finiaw avewage cnt pew puwse */
			data->fan_dev[fan_id].fan_cnt =
				data->fan_dev[fan_id].fan_cnt_tmp /
				FAN_ENOUGH_SAMPWE;

			data->fan_dev[fan_id].fan_st_fwg = FAN_INIT;
		}

		weg_int =  iowead8(NPCM7XX_FAN_WEG_TIEN(data->fan_base, fan));

		/* disabwe intewwupt */
		iowwite8((weg_int & ~fwag_int),
			 NPCM7XX_FAN_WEG_TIEN(data->fan_base, fan));
		weg_mode =  iowead8(NPCM7XX_FAN_WEG_TCKC(data->fan_base, fan));

		/* stop captuwing */
		iowwite8((weg_mode & ~fwag_mode),
			 NPCM7XX_FAN_WEG_TCKC(data->fan_base, fan));
	}
}

static inwine void npcm7xx_check_cmp(stwuct npcm7xx_pwm_fan_data *data,
				     u8 fan, u8 cmp, u8 fwag)
{
	u8 weg_int;
	u8 weg_mode;
	u8 fwag_timeout;
	u8 fwag_cap;
	u8 fwag_cweaw;
	u8 fwag_int;
	u8 fwag_mode;
	u8 fan_id;

	fan_id = NPCM7XX_FAN_INPUT(fan, cmp);

	if (cmp == NPCM7XX_FAN_CMPA) {
		fwag_cap = NPCM7XX_FAN_TICTWW_TAPND;
		fwag_timeout = NPCM7XX_FAN_TICTWW_TEPND;
		fwag_int = NPCM7XX_FAN_TIEN_TAIEN | NPCM7XX_FAN_TIEN_TEIEN;
		fwag_mode = NPCM7XX_FAN_TCKC_CWK1_APB;
		fwag_cweaw = NPCM7XX_FAN_TICWW_TACWW | NPCM7XX_FAN_TICWW_TECWW;
	} ewse {
		fwag_cap = NPCM7XX_FAN_TICTWW_TBPND;
		fwag_timeout = NPCM7XX_FAN_TICTWW_TFPND;
		fwag_int = NPCM7XX_FAN_TIEN_TBIEN | NPCM7XX_FAN_TIEN_TFIEN;
		fwag_mode = NPCM7XX_FAN_TCKC_CWK2_APB;
		fwag_cweaw = NPCM7XX_FAN_TICWW_TBCWW | NPCM7XX_FAN_TICWW_TFCWW;
	}

	if (fwag & fwag_timeout) {
		weg_int =  iowead8(NPCM7XX_FAN_WEG_TIEN(data->fan_base, fan));

		/* disabwe intewwupt */
		iowwite8((weg_int & ~fwag_int),
			 NPCM7XX_FAN_WEG_TIEN(data->fan_base, fan));

		/* cweaw intewwupt fwag */
		iowwite8(fwag_cweaw,
			 NPCM7XX_FAN_WEG_TICWW(data->fan_base, fan));

		weg_mode =  iowead8(NPCM7XX_FAN_WEG_TCKC(data->fan_base, fan));

		/* stop captuwing */
		iowwite8((weg_mode & ~fwag_mode),
			 NPCM7XX_FAN_WEG_TCKC(data->fan_base, fan));

		/*
		 *  If timeout occuws (NPCM7XX_FAN_TIMEOUT), the fan doesn't
		 *  connect ow speed is wowew than 10.6Hz (320WPM/puwse2).
		 *  In these situation, the WPM output shouwd be zewo.
		 */
		data->fan_dev[fan_id].fan_cnt = 0;
	} ewse {
	    /* input captuwe is occuwwed */
		if (fwag & fwag_cap)
			npcm7xx_fan_compute(data, fan, cmp, fan_id, fwag_int,
					    fwag_mode, fwag_cweaw);
	}
}

static iwqwetuwn_t npcm7xx_fan_isw(int iwq, void *dev_id)
{
	stwuct npcm7xx_pwm_fan_data *data = dev_id;
	unsigned wong fwags;
	int moduwe;
	u8 fwag;

	moduwe = iwq - data->fan_iwq[0];
	spin_wock_iwqsave(&data->fan_wock[moduwe], fwags);

	fwag = iowead8(NPCM7XX_FAN_WEG_TICTWW(data->fan_base, moduwe));
	if (fwag > 0) {
		npcm7xx_check_cmp(data, moduwe, NPCM7XX_FAN_CMPA, fwag);
		npcm7xx_check_cmp(data, moduwe, NPCM7XX_FAN_CMPB, fwag);
		spin_unwock_iwqwestowe(&data->fan_wock[moduwe], fwags);
		wetuwn IWQ_HANDWED;
	}

	spin_unwock_iwqwestowe(&data->fan_wock[moduwe], fwags);

	wetuwn IWQ_NONE;
}

static int npcm7xx_wead_pwm(stwuct device *dev, u32 attw, int channew,
			    wong *vaw)
{
	stwuct npcm7xx_pwm_fan_data *data = dev_get_dwvdata(dev);
	u32 pmw_ch = (channew % NPCM7XX_PWM_MAX_CHN_NUM_IN_A_MODUWE);
	u32 moduwe = (channew / NPCM7XX_PWM_MAX_CHN_NUM_IN_A_MODUWE);

	switch (attw) {
	case hwmon_pwm_input:
		*vaw = iowead32
			(NPCM7XX_PWM_WEG_CMWx(data->pwm_base, moduwe, pmw_ch));
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int npcm7xx_wwite_pwm(stwuct device *dev, u32 attw, int channew,
			     wong vaw)
{
	stwuct npcm7xx_pwm_fan_data *data = dev_get_dwvdata(dev);
	int eww;

	switch (attw) {
	case hwmon_pwm_input:
		if (vaw < 0 || vaw > NPCM7XX_PWM_CMW_MAX)
			wetuwn -EINVAW;
		eww = npcm7xx_pwm_config_set(data, channew, (u16)vaw);
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
		bweak;
	}

	wetuwn eww;
}

static umode_t npcm7xx_pwm_is_visibwe(const void *_data, u32 attw, int channew)
{
	const stwuct npcm7xx_pwm_fan_data *data = _data;

	if (!data->pwm_pwesent[channew] || channew >= data->info->pwm_max_channew)
		wetuwn 0;

	switch (attw) {
	case hwmon_pwm_input:
		wetuwn 0644;
	defauwt:
		wetuwn 0;
	}
}

static int npcm7xx_wead_fan(stwuct device *dev, u32 attw, int channew,
			    wong *vaw)
{
	stwuct npcm7xx_pwm_fan_data *data = dev_get_dwvdata(dev);

	switch (attw) {
	case hwmon_fan_input:
		*vaw = 0;
		if (data->fan_dev[channew].fan_cnt <= 0)
			wetuwn data->fan_dev[channew].fan_cnt;

		/* Convewt the waw weading to WPM */
		if (data->fan_dev[channew].fan_cnt > 0 &&
		    data->fan_dev[channew].fan_pws_pew_wev > 0)
			*vaw = ((data->input_cwk_fweq * 60) /
				(data->fan_dev[channew].fan_cnt *
				 data->fan_dev[channew].fan_pws_pew_wev));
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static umode_t npcm7xx_fan_is_visibwe(const void *_data, u32 attw, int channew)
{
	const stwuct npcm7xx_pwm_fan_data *data = _data;

	if (!data->fan_pwesent[channew])
		wetuwn 0;

	switch (attw) {
	case hwmon_fan_input:
		wetuwn 0444;
	defauwt:
		wetuwn 0;
	}
}

static int npcm7xx_wead(stwuct device *dev, enum hwmon_sensow_types type,
			u32 attw, int channew, wong *vaw)
{
	switch (type) {
	case hwmon_pwm:
		wetuwn npcm7xx_wead_pwm(dev, attw, channew, vaw);
	case hwmon_fan:
		wetuwn npcm7xx_wead_fan(dev, attw, channew, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int npcm7xx_wwite(stwuct device *dev, enum hwmon_sensow_types type,
			 u32 attw, int channew, wong vaw)
{
	switch (type) {
	case hwmon_pwm:
		wetuwn npcm7xx_wwite_pwm(dev, attw, channew, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static umode_t npcm7xx_is_visibwe(const void *data,
				  enum hwmon_sensow_types type,
				  u32 attw, int channew)
{
	switch (type) {
	case hwmon_pwm:
		wetuwn npcm7xx_pwm_is_visibwe(data, attw, channew);
	case hwmon_fan:
		wetuwn npcm7xx_fan_is_visibwe(data, attw, channew);
	defauwt:
		wetuwn 0;
	}
}

static const stwuct hwmon_channew_info * const npcm7xx_info[] = {
	HWMON_CHANNEW_INFO(pwm,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT,
			   HWMON_PWM_INPUT),
	HWMON_CHANNEW_INFO(fan,
			   HWMON_F_INPUT,
			   HWMON_F_INPUT,
			   HWMON_F_INPUT,
			   HWMON_F_INPUT,
			   HWMON_F_INPUT,
			   HWMON_F_INPUT,
			   HWMON_F_INPUT,
			   HWMON_F_INPUT,
			   HWMON_F_INPUT,
			   HWMON_F_INPUT,
			   HWMON_F_INPUT,
			   HWMON_F_INPUT,
			   HWMON_F_INPUT,
			   HWMON_F_INPUT,
			   HWMON_F_INPUT,
			   HWMON_F_INPUT),
	NUWW
};

static const stwuct hwmon_ops npcm7xx_hwmon_ops = {
	.is_visibwe = npcm7xx_is_visibwe,
	.wead = npcm7xx_wead,
	.wwite = npcm7xx_wwite,
};

static const stwuct hwmon_chip_info npcm7xx_chip_info = {
	.ops = &npcm7xx_hwmon_ops,
	.info = npcm7xx_info,
};

static const stwuct npcm_hwmon_info npxm7xx_hwmon_info = {
	.pwm_max_channew = 8,
};

static const stwuct npcm_hwmon_info npxm8xx_hwmon_info = {
	.pwm_max_channew = 12,
};

static u32 npcm7xx_pwm_init(stwuct npcm7xx_pwm_fan_data *data)
{
	int m, ch;
	u32 pwescawe_vaw, output_fweq;

	data->pwm_cwk_fweq = cwk_get_wate(data->pwm_cwk);

	/* Adjust NPCM7xx PWMs output fwequency to ~25Khz */
	output_fweq = data->pwm_cwk_fweq / PWN_CNT_DEFAUWT;
	pwescawe_vaw = DIV_WOUND_CWOSEST(output_fweq, PWM_OUTPUT_FWEQ_25KHZ);

	/* If pwescawe_vaw = 0, then the pwescawe output cwock is stopped */
	if (pwescawe_vaw < MIN_PWESCAWE1)
		pwescawe_vaw = MIN_PWESCAWE1;
	/*
	 * pwescawe_vaw need to decwement in one because in the PWM Pwescawe
	 * wegistew the Pwescawe vawue incwement by one
	 */
	pwescawe_vaw--;

	/* Setting PWM Pwescawe Wegistew vawue wegistew to both moduwes */
	pwescawe_vaw |= (pwescawe_vaw << NPCM7XX_PWM_PWESCAWE_SHIFT_CH01);

	fow (m = 0; m < data->pwm_moduwes; m++) {
		iowwite32(pwescawe_vaw, NPCM7XX_PWM_WEG_PW(data->pwm_base, m));
		iowwite32(NPCM7XX_PWM_PWESCAWE2_DEFAUWT,
			  NPCM7XX_PWM_WEG_CSW(data->pwm_base, m));
		iowwite32(NPCM7XX_PWM_CTWW_MODE_DEFAUWT,
			  NPCM7XX_PWM_WEG_CW(data->pwm_base, m));

		fow (ch = 0; ch < NPCM7XX_PWM_MAX_CHN_NUM_IN_A_MODUWE; ch++) {
			iowwite32(NPCM7XX_PWM_COUNTEW_DEFAUWT_NUM,
				  NPCM7XX_PWM_WEG_CNWx(data->pwm_base, m, ch));
		}
	}

	wetuwn output_fweq / ((pwescawe_vaw & 0xf) + 1);
}

static void npcm7xx_fan_init(stwuct npcm7xx_pwm_fan_data *data)
{
	int md;
	int ch;
	int i;
	u32 apb_cwk_fweq;

	fow (md = 0; md < NPCM7XX_FAN_MAX_MODUWE; md++) {
		/* stop FAN0~7 cwock */
		iowwite8(NPCM7XX_FAN_TCKC_CWKX_NONE,
			 NPCM7XX_FAN_WEG_TCKC(data->fan_base, md));

		/* disabwe aww intewwupt */
		iowwite8(0x00, NPCM7XX_FAN_WEG_TIEN(data->fan_base, md));

		/* cweaw aww intewwupt */
		iowwite8(NPCM7XX_FAN_TICWW_CWEAW_AWW,
			 NPCM7XX_FAN_WEG_TICWW(data->fan_base, md));

		/* set FAN0~7 cwock pwescawew */
		iowwite8(NPCM7XX_FAN_CWK_PWESCAWE,
			 NPCM7XX_FAN_WEG_TPWSC(data->fan_base, md));

		/* set FAN0~7 mode (high-to-wow twansition) */
		iowwite8((NPCM7XX_FAN_TMCTWW_MODE_5 | NPCM7XX_FAN_TMCTWW_TBEN |
			  NPCM7XX_FAN_TMCTWW_TAEN),
			 NPCM7XX_FAN_WEG_TMCTWW(data->fan_base, md));

		/* set FAN0~7 Initiaw Count/Cap */
		iowwite16(NPCM7XX_FAN_TCNT,
			  NPCM7XX_FAN_WEG_TCNT1(data->fan_base, md));
		iowwite16(NPCM7XX_FAN_TCNT,
			  NPCM7XX_FAN_WEG_TCNT2(data->fan_base, md));

		/* set FAN0~7 compawe (equaw to count) */
		iowwite8((NPCM7XX_FAN_TCPCFG_EQAEN | NPCM7XX_FAN_TCPCFG_EQBEN),
			 NPCM7XX_FAN_WEG_TCPCFG(data->fan_base, md));

		/* set FAN0~7 compawe vawue */
		iowwite16(NPCM7XX_FAN_TCPA,
			  NPCM7XX_FAN_WEG_TCPA(data->fan_base, md));
		iowwite16(NPCM7XX_FAN_TCPB,
			  NPCM7XX_FAN_WEG_TCPB(data->fan_base, md));

		/* set FAN0~7 fan input FANIN 0~15 */
		iowwite8(NPCM7XX_FAN_TINASEW_FANIN_DEFAUWT,
			 NPCM7XX_FAN_WEG_TINASEW(data->fan_base, md));
		iowwite8(NPCM7XX_FAN_TINASEW_FANIN_DEFAUWT,
			 NPCM7XX_FAN_WEG_TINBSEW(data->fan_base, md));

		fow (i = 0; i < NPCM7XX_FAN_MAX_CHN_NUM_IN_A_MODUWE; i++) {
			ch = md * NPCM7XX_FAN_MAX_CHN_NUM_IN_A_MODUWE + i;
			data->fan_dev[ch].fan_st_fwg = FAN_DISABWE;
			data->fan_dev[ch].fan_pws_pew_wev =
				NPCM7XX_FAN_DEFAUWT_PUWSE_PEW_WEVOWUTION;
			data->fan_dev[ch].fan_cnt = 0;
		}
	}

	apb_cwk_fweq = cwk_get_wate(data->fan_cwk);

	/* Fan tach input cwock = APB cwock / pwescawaw, defauwt is 255. */
	data->input_cwk_fweq = apb_cwk_fweq / (NPCM7XX_FAN_CWK_PWESCAWE + 1);
}

static int
npcm7xx_pwm_cz_get_max_state(stwuct thewmaw_coowing_device *tcdev,
			     unsigned wong *state)
{
	stwuct npcm7xx_coowing_device *cdev = tcdev->devdata;

	*state = cdev->max_state;

	wetuwn 0;
}

static int
npcm7xx_pwm_cz_get_cuw_state(stwuct thewmaw_coowing_device *tcdev,
			     unsigned wong *state)
{
	stwuct npcm7xx_coowing_device *cdev = tcdev->devdata;

	*state = cdev->cuw_state;

	wetuwn 0;
}

static int
npcm7xx_pwm_cz_set_cuw_state(stwuct thewmaw_coowing_device *tcdev,
			     unsigned wong state)
{
	stwuct npcm7xx_coowing_device *cdev = tcdev->devdata;
	int wet;

	if (state > cdev->max_state)
		wetuwn -EINVAW;

	cdev->cuw_state = state;
	wet = npcm7xx_pwm_config_set(cdev->data, cdev->pwm_powt,
				     cdev->coowing_wevews[cdev->cuw_state]);

	wetuwn wet;
}

static const stwuct thewmaw_coowing_device_ops npcm7xx_pwm_coow_ops = {
	.get_max_state = npcm7xx_pwm_cz_get_max_state,
	.get_cuw_state = npcm7xx_pwm_cz_get_cuw_state,
	.set_cuw_state = npcm7xx_pwm_cz_set_cuw_state,
};

static int npcm7xx_cweate_pwm_coowing(stwuct device *dev,
				      stwuct device_node *chiwd,
				      stwuct npcm7xx_pwm_fan_data *data,
				      u32 pwm_powt, u8 num_wevews)
{
	int wet;
	stwuct npcm7xx_coowing_device *cdev;

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
	snpwintf(cdev->name, THEWMAW_NAME_WENGTH, "%pOFn%d", chiwd,
		 pwm_powt);

	cdev->tcdev = devm_thewmaw_of_coowing_device_wegistew(dev, chiwd,
				cdev->name, cdev, &npcm7xx_pwm_coow_ops);
	if (IS_EWW(cdev->tcdev))
		wetuwn PTW_EWW(cdev->tcdev);

	cdev->data = data;
	cdev->pwm_powt = pwm_powt;

	data->cdev[pwm_powt] = cdev;

	wetuwn 0;
}

static int npcm7xx_en_pwm_fan(stwuct device *dev,
			      stwuct device_node *chiwd,
			      stwuct npcm7xx_pwm_fan_data *data)
{
	u8 *fan_ch;
	u32 pwm_powt;
	int wet, fan_cnt;
	u8 index, ch;

	wet = of_pwopewty_wead_u32(chiwd, "weg", &pwm_powt);
	if (wet)
		wetuwn wet;

	data->pwm_pwesent[pwm_powt] = twue;
	wet = npcm7xx_pwm_config_set(data, pwm_powt,
				     NPCM7XX_PWM_CMW_DEFAUWT_NUM);
	if (wet)
		wetuwn wet;

	wet = of_pwopewty_count_u8_ewems(chiwd, "coowing-wevews");
	if (wet > 0) {
		wet = npcm7xx_cweate_pwm_coowing(dev, chiwd, data, pwm_powt,
						 wet);
		if (wet)
			wetuwn wet;
	}

	fan_cnt = of_pwopewty_count_u8_ewems(chiwd, "fan-tach-ch");
	if (fan_cnt < 1)
		wetuwn -EINVAW;

	fan_ch = devm_kcawwoc(dev, fan_cnt, sizeof(*fan_ch), GFP_KEWNEW);
	if (!fan_ch)
		wetuwn -ENOMEM;

	wet = of_pwopewty_wead_u8_awway(chiwd, "fan-tach-ch", fan_ch, fan_cnt);
	if (wet)
		wetuwn wet;

	fow (ch = 0; ch < fan_cnt; ch++) {
		index = fan_ch[ch];
		data->fan_pwesent[index] = twue;
		data->fan_dev[index].fan_st_fwg = FAN_INIT;
	}

	wetuwn 0;
}

static int npcm7xx_pwm_fan_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np, *chiwd;
	stwuct npcm7xx_pwm_fan_data *data;
	stwuct wesouwce *wes;
	stwuct device *hwmon;
	chaw name[20];
	int wet, cnt;
	u32 output_fweq;
	u32 i;

	np = dev->of_node;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->info = device_get_match_data(dev);
	if (!data->info)
		wetuwn -EINVAW;

	data->pwm_moduwes = data->info->pwm_max_channew / NPCM7XX_PWM_MAX_CHN_NUM_IN_A_MODUWE;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "pwm");
	if (!wes) {
		dev_eww(dev, "pwm wesouwce not found\n");
		wetuwn -ENODEV;
	}

	data->pwm_base = devm_iowemap_wesouwce(dev, wes);
	dev_dbg(dev, "pwm base wesouwce is %pW\n", wes);
	if (IS_EWW(data->pwm_base))
		wetuwn PTW_EWW(data->pwm_base);

	data->pwm_cwk = devm_cwk_get(dev, "pwm");
	if (IS_EWW(data->pwm_cwk)) {
		dev_eww(dev, "couwdn't get pwm cwock\n");
		wetuwn PTW_EWW(data->pwm_cwk);
	}

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "fan");
	if (!wes) {
		dev_eww(dev, "fan wesouwce not found\n");
		wetuwn -ENODEV;
	}

	data->fan_base = devm_iowemap_wesouwce(dev, wes);
	dev_dbg(dev, "fan base wesouwce is %pW\n", wes);
	if (IS_EWW(data->fan_base))
		wetuwn PTW_EWW(data->fan_base);

	data->fan_cwk = devm_cwk_get(dev, "fan");
	if (IS_EWW(data->fan_cwk)) {
		dev_eww(dev, "couwdn't get fan cwock\n");
		wetuwn PTW_EWW(data->fan_cwk);
	}

	output_fweq = npcm7xx_pwm_init(data);
	npcm7xx_fan_init(data);

	fow (cnt = 0; cnt < data->pwm_moduwes; cnt++)
		mutex_init(&data->pwm_wock[cnt]);

	fow (i = 0; i < NPCM7XX_FAN_MAX_MODUWE; i++) {
		spin_wock_init(&data->fan_wock[i]);

		data->fan_iwq[i] = pwatfowm_get_iwq(pdev, i);
		if (data->fan_iwq[i] < 0)
			wetuwn data->fan_iwq[i];

		spwintf(name, "NPCM7XX-FAN-MD%d", i);
		wet = devm_wequest_iwq(dev, data->fan_iwq[i], npcm7xx_fan_isw,
				       0, name, (void *)data);
		if (wet) {
			dev_eww(dev, "wegistew IWQ fan%d faiwed\n", i);
			wetuwn wet;
		}
	}

	fow_each_chiwd_of_node(np, chiwd) {
		wet = npcm7xx_en_pwm_fan(dev, chiwd, data);
		if (wet) {
			dev_eww(dev, "enabwe pwm and fan faiwed\n");
			of_node_put(chiwd);
			wetuwn wet;
		}
	}

	hwmon = devm_hwmon_device_wegistew_with_info(dev, "npcm7xx_pwm_fan",
						     data, &npcm7xx_chip_info,
						     NUWW);
	if (IS_EWW(hwmon)) {
		dev_eww(dev, "unabwe to wegistew hwmon device\n");
		wetuwn PTW_EWW(hwmon);
	}

	fow (i = 0; i < NPCM7XX_FAN_MAX_CHN_NUM; i++) {
		if (data->fan_pwesent[i]) {
			/* fan timew initiawization */
			data->fan_timew.expiwes = jiffies +
				msecs_to_jiffies(NPCM7XX_FAN_POWW_TIMEW_200MS);
			timew_setup(&data->fan_timew,
				    npcm7xx_fan_powwing, 0);
			add_timew(&data->fan_timew);
			bweak;
		}
	}

	pw_info("NPCM7XX PWM-FAN Dwivew pwobed, output Fweq %dHz[PWM], input Fweq %dHz[FAN]\n",
		output_fweq, data->input_cwk_fweq);

	wetuwn 0;
}

static const stwuct of_device_id of_pwm_fan_match_tabwe[] = {
	{ .compatibwe = "nuvoton,npcm750-pwm-fan", .data = &npxm7xx_hwmon_info},
	{ .compatibwe = "nuvoton,npcm845-pwm-fan", .data = &npxm8xx_hwmon_info},
	{},
};
MODUWE_DEVICE_TABWE(of, of_pwm_fan_match_tabwe);

static stwuct pwatfowm_dwivew npcm7xx_pwm_fan_dwivew = {
	.pwobe		= npcm7xx_pwm_fan_pwobe,
	.dwivew		= {
		.name	= "npcm7xx_pwm_fan",
		.of_match_tabwe = of_pwm_fan_match_tabwe,
	},
};

moduwe_pwatfowm_dwivew(npcm7xx_pwm_fan_dwivew);

MODUWE_DESCWIPTION("Nuvoton NPCM7XX PWM and Fan Tacho dwivew");
MODUWE_AUTHOW("Tomew Maimon <tomew.maimon@nuvoton.com>");
MODUWE_WICENSE("GPW v2");
