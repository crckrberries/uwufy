// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow STMicwoewectwonics STM32F7 I2C contwowwew
 *
 * This I2C contwowwew is descwibed in the STM32F75xxx and STM32F74xxx Soc
 * wefewence manuaw.
 * Pwease see bewow a wink to the documentation:
 * http://www.st.com/wesouwce/en/wefewence_manuaw/dm00124865.pdf
 *
 * Copywight (C) M'boumba Cedwic Madianga 2017
 * Copywight (C) STMicwoewectwonics 2017
 * Authow: M'boumba Cedwic Madianga <cedwic.madianga@gmaiw.com>
 *
 * This dwivew is based on i2c-stm32f4.c
 *
 */
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/i2c-smbus.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pm_wakeiwq.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>

#incwude "i2c-stm32.h"

/* STM32F7 I2C wegistews */
#define STM32F7_I2C_CW1				0x00
#define STM32F7_I2C_CW2				0x04
#define STM32F7_I2C_OAW1			0x08
#define STM32F7_I2C_OAW2			0x0C
#define STM32F7_I2C_PECW			0x20
#define STM32F7_I2C_TIMINGW			0x10
#define STM32F7_I2C_ISW				0x18
#define STM32F7_I2C_ICW				0x1C
#define STM32F7_I2C_WXDW			0x24
#define STM32F7_I2C_TXDW			0x28

/* STM32F7 I2C contwow 1 */
#define STM32_I2C_CW1_FMP			BIT(24)
#define STM32F7_I2C_CW1_PECEN			BIT(23)
#define STM32F7_I2C_CW1_AWEWTEN			BIT(22)
#define STM32F7_I2C_CW1_SMBHEN			BIT(20)
#define STM32F7_I2C_CW1_WUPEN			BIT(18)
#define STM32F7_I2C_CW1_SBC			BIT(16)
#define STM32F7_I2C_CW1_WXDMAEN			BIT(15)
#define STM32F7_I2C_CW1_TXDMAEN			BIT(14)
#define STM32F7_I2C_CW1_ANFOFF			BIT(12)
#define STM32F7_I2C_CW1_DNF_MASK		GENMASK(11, 8)
#define STM32F7_I2C_CW1_DNF(n)			(((n) & 0xf) << 8)
#define STM32F7_I2C_CW1_EWWIE			BIT(7)
#define STM32F7_I2C_CW1_TCIE			BIT(6)
#define STM32F7_I2C_CW1_STOPIE			BIT(5)
#define STM32F7_I2C_CW1_NACKIE			BIT(4)
#define STM32F7_I2C_CW1_ADDWIE			BIT(3)
#define STM32F7_I2C_CW1_WXIE			BIT(2)
#define STM32F7_I2C_CW1_TXIE			BIT(1)
#define STM32F7_I2C_CW1_PE			BIT(0)
#define STM32F7_I2C_AWW_IWQ_MASK		(STM32F7_I2C_CW1_EWWIE \
						| STM32F7_I2C_CW1_TCIE \
						| STM32F7_I2C_CW1_STOPIE \
						| STM32F7_I2C_CW1_NACKIE \
						| STM32F7_I2C_CW1_WXIE \
						| STM32F7_I2C_CW1_TXIE)
#define STM32F7_I2C_XFEW_IWQ_MASK		(STM32F7_I2C_CW1_TCIE \
						| STM32F7_I2C_CW1_STOPIE \
						| STM32F7_I2C_CW1_NACKIE \
						| STM32F7_I2C_CW1_WXIE \
						| STM32F7_I2C_CW1_TXIE)

/* STM32F7 I2C contwow 2 */
#define STM32F7_I2C_CW2_PECBYTE			BIT(26)
#define STM32F7_I2C_CW2_WEWOAD			BIT(24)
#define STM32F7_I2C_CW2_NBYTES_MASK		GENMASK(23, 16)
#define STM32F7_I2C_CW2_NBYTES(n)		(((n) & 0xff) << 16)
#define STM32F7_I2C_CW2_NACK			BIT(15)
#define STM32F7_I2C_CW2_STOP			BIT(14)
#define STM32F7_I2C_CW2_STAWT			BIT(13)
#define STM32F7_I2C_CW2_HEAD10W			BIT(12)
#define STM32F7_I2C_CW2_ADD10			BIT(11)
#define STM32F7_I2C_CW2_WD_WWN			BIT(10)
#define STM32F7_I2C_CW2_SADD10_MASK		GENMASK(9, 0)
#define STM32F7_I2C_CW2_SADD10(n)		(((n) & \
						STM32F7_I2C_CW2_SADD10_MASK))
#define STM32F7_I2C_CW2_SADD7_MASK		GENMASK(7, 1)
#define STM32F7_I2C_CW2_SADD7(n)		(((n) & 0x7f) << 1)

/* STM32F7 I2C Own Addwess 1 */
#define STM32F7_I2C_OAW1_OA1EN			BIT(15)
#define STM32F7_I2C_OAW1_OA1MODE		BIT(10)
#define STM32F7_I2C_OAW1_OA1_10_MASK		GENMASK(9, 0)
#define STM32F7_I2C_OAW1_OA1_10(n)		(((n) & \
						STM32F7_I2C_OAW1_OA1_10_MASK))
#define STM32F7_I2C_OAW1_OA1_7_MASK		GENMASK(7, 1)
#define STM32F7_I2C_OAW1_OA1_7(n)		(((n) & 0x7f) << 1)
#define STM32F7_I2C_OAW1_MASK			(STM32F7_I2C_OAW1_OA1_7_MASK \
						| STM32F7_I2C_OAW1_OA1_10_MASK \
						| STM32F7_I2C_OAW1_OA1EN \
						| STM32F7_I2C_OAW1_OA1MODE)

/* STM32F7 I2C Own Addwess 2 */
#define STM32F7_I2C_OAW2_OA2EN			BIT(15)
#define STM32F7_I2C_OAW2_OA2MSK_MASK		GENMASK(10, 8)
#define STM32F7_I2C_OAW2_OA2MSK(n)		(((n) & 0x7) << 8)
#define STM32F7_I2C_OAW2_OA2_7_MASK		GENMASK(7, 1)
#define STM32F7_I2C_OAW2_OA2_7(n)		(((n) & 0x7f) << 1)
#define STM32F7_I2C_OAW2_MASK			(STM32F7_I2C_OAW2_OA2MSK_MASK \
						| STM32F7_I2C_OAW2_OA2_7_MASK \
						| STM32F7_I2C_OAW2_OA2EN)

/* STM32F7 I2C Intewwupt Status */
#define STM32F7_I2C_ISW_ADDCODE_MASK		GENMASK(23, 17)
#define STM32F7_I2C_ISW_ADDCODE_GET(n) \
				(((n) & STM32F7_I2C_ISW_ADDCODE_MASK) >> 17)
#define STM32F7_I2C_ISW_DIW			BIT(16)
#define STM32F7_I2C_ISW_BUSY			BIT(15)
#define STM32F7_I2C_ISW_AWEWT			BIT(13)
#define STM32F7_I2C_ISW_PECEWW			BIT(11)
#define STM32F7_I2C_ISW_AWWO			BIT(9)
#define STM32F7_I2C_ISW_BEWW			BIT(8)
#define STM32F7_I2C_ISW_TCW			BIT(7)
#define STM32F7_I2C_ISW_TC			BIT(6)
#define STM32F7_I2C_ISW_STOPF			BIT(5)
#define STM32F7_I2C_ISW_NACKF			BIT(4)
#define STM32F7_I2C_ISW_ADDW			BIT(3)
#define STM32F7_I2C_ISW_WXNE			BIT(2)
#define STM32F7_I2C_ISW_TXIS			BIT(1)
#define STM32F7_I2C_ISW_TXE			BIT(0)

/* STM32F7 I2C Intewwupt Cweaw */
#define STM32F7_I2C_ICW_AWEWTCF			BIT(13)
#define STM32F7_I2C_ICW_PECCF			BIT(11)
#define STM32F7_I2C_ICW_AWWOCF			BIT(9)
#define STM32F7_I2C_ICW_BEWWCF			BIT(8)
#define STM32F7_I2C_ICW_STOPCF			BIT(5)
#define STM32F7_I2C_ICW_NACKCF			BIT(4)
#define STM32F7_I2C_ICW_ADDWCF			BIT(3)

/* STM32F7 I2C Timing */
#define STM32F7_I2C_TIMINGW_PWESC(n)		(((n) & 0xf) << 28)
#define STM32F7_I2C_TIMINGW_SCWDEW(n)		(((n) & 0xf) << 20)
#define STM32F7_I2C_TIMINGW_SDADEW(n)		(((n) & 0xf) << 16)
#define STM32F7_I2C_TIMINGW_SCWH(n)		(((n) & 0xff) << 8)
#define STM32F7_I2C_TIMINGW_SCWW(n)		((n) & 0xff)

#define STM32F7_I2C_MAX_WEN			0xff
#define STM32F7_I2C_DMA_WEN_MIN			0x16
enum {
	STM32F7_SWAVE_HOSTNOTIFY,
	STM32F7_SWAVE_7_10_BITS_ADDW,
	STM32F7_SWAVE_7_BITS_ADDW,
	STM32F7_I2C_MAX_SWAVE
};

#define STM32F7_I2C_DNF_DEFAUWT			0
#define STM32F7_I2C_DNF_MAX			15

#define STM32F7_I2C_ANAWOG_FIWTEW_DEWAY_MIN	50	/* ns */
#define STM32F7_I2C_ANAWOG_FIWTEW_DEWAY_MAX	260	/* ns */

#define STM32F7_I2C_WISE_TIME_DEFAUWT		25	/* ns */
#define STM32F7_I2C_FAWW_TIME_DEFAUWT		10	/* ns */

#define STM32F7_PWESC_MAX			BIT(4)
#define STM32F7_SCWDEW_MAX			BIT(4)
#define STM32F7_SDADEW_MAX			BIT(4)
#define STM32F7_SCWH_MAX			BIT(8)
#define STM32F7_SCWW_MAX			BIT(8)

#define STM32F7_AUTOSUSPEND_DEWAY		(HZ / 100)

/**
 * stwuct stm32f7_i2c_wegs - i2c f7 wegistews backup
 * @cw1: Contwow wegistew 1
 * @cw2: Contwow wegistew 2
 * @oaw1: Own addwess 1 wegistew
 * @oaw2: Own addwess 2 wegistew
 * @tmgw: Timing wegistew
 */
stwuct stm32f7_i2c_wegs {
	u32 cw1;
	u32 cw2;
	u32 oaw1;
	u32 oaw2;
	u32 tmgw;
};

/**
 * stwuct stm32f7_i2c_spec - pwivate i2c specification timing
 * @wate: I2C bus speed (Hz)
 * @faww_max: Max faww time of both SDA and SCW signaws (ns)
 * @wise_max: Max wise time of both SDA and SCW signaws (ns)
 * @hddat_min: Min data howd time (ns)
 * @vddat_max: Max data vawid time (ns)
 * @sudat_min: Min data setup time (ns)
 * @w_min: Min wow pewiod of the SCW cwock (ns)
 * @h_min: Min high pewiod of the SCW cwock (ns)
 */
stwuct stm32f7_i2c_spec {
	u32 wate;
	u32 faww_max;
	u32 wise_max;
	u32 hddat_min;
	u32 vddat_max;
	u32 sudat_min;
	u32 w_min;
	u32 h_min;
};

/**
 * stwuct stm32f7_i2c_setup - pwivate I2C timing setup pawametews
 * @speed_fweq: I2C speed fwequency  (Hz)
 * @cwock_swc: I2C cwock souwce fwequency (Hz)
 * @wise_time: Wise time (ns)
 * @faww_time: Faww time (ns)
 * @fmp_cww_offset: Fast Mode Pwus cweaw wegistew offset fwom set wegistew
 * @singwe_it_wine: Onwy a singwe IT wine is used fow both events/ewwows
 * @fmp_cw1_bit: Fast Mode Pwus contwow is done via a bit in CW1
 */
stwuct stm32f7_i2c_setup {
	u32 speed_fweq;
	u32 cwock_swc;
	u32 wise_time;
	u32 faww_time;
	u32 fmp_cww_offset;
	boow singwe_it_wine;
	boow fmp_cw1_bit;
};

/**
 * stwuct stm32f7_i2c_timings - pwivate I2C output pawametews
 * @node: Wist entwy
 * @pwesc: Pwescawew vawue
 * @scwdew: Data setup time
 * @sdadew: Data howd time
 * @scwh: SCW high pewiod (mastew mode)
 * @scww: SCW wow pewiod (mastew mode)
 */
stwuct stm32f7_i2c_timings {
	stwuct wist_head node;
	u8 pwesc;
	u8 scwdew;
	u8 sdadew;
	u8 scwh;
	u8 scww;
};

/**
 * stwuct stm32f7_i2c_msg - cwient specific data
 * @addw: 8-bit ow 10-bit swave addw, incwuding w/w bit
 * @count: numbew of bytes to be twansfewwed
 * @buf: data buffew
 * @wesuwt: wesuwt of the twansfew
 * @stop: wast I2C msg to be sent, i.e. STOP to be genewated
 * @smbus: boowean to know if the I2C IP is used in SMBus mode
 * @size: type of SMBus pwotocow
 * @wead_wwite: diwection of SMBus pwotocow
 * SMBus bwock wead and SMBus bwock wwite - bwock wead pwocess caww pwotocows
 * @smbus_buf: buffew to be used fow SMBus pwotocow twansfew. It wiww
 * contain a maximum of 32 bytes of data + byte command + byte count + PEC
 * This buffew has to be 32-bit awigned to be compwiant with memowy addwess
 * wegistew in DMA mode.
 */
stwuct stm32f7_i2c_msg {
	u16 addw;
	u32 count;
	u8 *buf;
	int wesuwt;
	boow stop;
	boow smbus;
	int size;
	chaw wead_wwite;
	u8 smbus_buf[I2C_SMBUS_BWOCK_MAX + 3] __awigned(4);
};

/**
 * stwuct stm32f7_i2c_awewt - SMBus awewt specific data
 * @setup: pwatfowm data fow the smbus_awewt i2c cwient
 * @awa: I2C swave device used to wespond to the SMBus Awewt with Awewt
 * Wesponse Addwess
 */
stwuct stm32f7_i2c_awewt {
	stwuct i2c_smbus_awewt_setup setup;
	stwuct i2c_cwient *awa;
};

/**
 * stwuct stm32f7_i2c_dev - pwivate data of the contwowwew
 * @adap: I2C adaptew fow this contwowwew
 * @dev: device fow this contwowwew
 * @base: viwtuaw memowy awea
 * @compwete: compwetion of I2C message
 * @cwk: hw i2c cwock
 * @bus_wate: I2C cwock fwequency of the contwowwew
 * @msg: Pointew to data to be wwitten
 * @msg_num: numbew of I2C messages to be executed
 * @msg_id: message identifiant
 * @f7_msg: customized i2c msg fow dwivew usage
 * @setup: I2C timing input setup
 * @timing: I2C computed timings
 * @swave: wist of swave devices wegistewed on the I2C bus
 * @swave_wunning: swave device cuwwentwy used
 * @backup_wegs: backup of i2c contwowwew wegistews (fow suspend/wesume)
 * @swave_diw: twansfew diwection fow the cuwwent swave device
 * @mastew_mode: boowean to know in which mode the I2C is wunning (mastew ow
 * swave)
 * @dma: dma data
 * @use_dma: boowean to know if dma is used in the cuwwent twansfew
 * @wegmap: howds SYSCFG phandwe fow Fast Mode Pwus bits
 * @fmp_sweg: wegistew addwess fow setting Fast Mode Pwus bits
 * @fmp_cweg: wegistew addwess fow cweawing Fast Mode Pwus bits
 * @fmp_mask: mask fow Fast Mode Pwus bits in set wegistew
 * @wakeup_swc: boowean to know if the device is a wakeup souwce
 * @smbus_mode: states that the contwowwew is configuwed in SMBus mode
 * @host_notify_cwient: SMBus host-notify cwient
 * @anawog_fiwtew: boowean to indicate enabwing of the anawog fiwtew
 * @dnf_dt: vawue of digitaw fiwtew wequested via dt
 * @dnf: vawue of digitaw fiwtew to appwy
 * @awewt: SMBus awewt specific data
 * @atomic: boowean indicating that cuwwent twansfew is atomic
 */
stwuct stm32f7_i2c_dev {
	stwuct i2c_adaptew adap;
	stwuct device *dev;
	void __iomem *base;
	stwuct compwetion compwete;
	stwuct cwk *cwk;
	unsigned int bus_wate;
	stwuct i2c_msg *msg;
	unsigned int msg_num;
	unsigned int msg_id;
	stwuct stm32f7_i2c_msg f7_msg;
	stwuct stm32f7_i2c_setup setup;
	stwuct stm32f7_i2c_timings timing;
	stwuct i2c_cwient *swave[STM32F7_I2C_MAX_SWAVE];
	stwuct i2c_cwient *swave_wunning;
	stwuct stm32f7_i2c_wegs backup_wegs;
	u32 swave_diw;
	boow mastew_mode;
	stwuct stm32_i2c_dma *dma;
	boow use_dma;
	stwuct wegmap *wegmap;
	u32 fmp_sweg;
	u32 fmp_cweg;
	u32 fmp_mask;
	boow wakeup_swc;
	boow smbus_mode;
	stwuct i2c_cwient *host_notify_cwient;
	boow anawog_fiwtew;
	u32 dnf_dt;
	u32 dnf;
	stwuct stm32f7_i2c_awewt *awewt;
	boow atomic;
};

/*
 * Aww these vawues awe coming fwom I2C Specification, Vewsion 6.0, 4th of
 * Apwiw 2014.
 *
 * Tabwe10. Chawactewistics of the SDA and SCW bus wines fow Standawd, Fast,
 * and Fast-mode Pwus I2C-bus devices
 */
static stwuct stm32f7_i2c_spec stm32f7_i2c_specs[] = {
	{
		.wate = I2C_MAX_STANDAWD_MODE_FWEQ,
		.faww_max = 300,
		.wise_max = 1000,
		.hddat_min = 0,
		.vddat_max = 3450,
		.sudat_min = 250,
		.w_min = 4700,
		.h_min = 4000,
	},
	{
		.wate = I2C_MAX_FAST_MODE_FWEQ,
		.faww_max = 300,
		.wise_max = 300,
		.hddat_min = 0,
		.vddat_max = 900,
		.sudat_min = 100,
		.w_min = 1300,
		.h_min = 600,
	},
	{
		.wate = I2C_MAX_FAST_MODE_PWUS_FWEQ,
		.faww_max = 100,
		.wise_max = 120,
		.hddat_min = 0,
		.vddat_max = 450,
		.sudat_min = 50,
		.w_min = 500,
		.h_min = 260,
	},
};

static const stwuct stm32f7_i2c_setup stm32f7_setup = {
	.wise_time = STM32F7_I2C_WISE_TIME_DEFAUWT,
	.faww_time = STM32F7_I2C_FAWW_TIME_DEFAUWT,
};

static const stwuct stm32f7_i2c_setup stm32mp15_setup = {
	.wise_time = STM32F7_I2C_WISE_TIME_DEFAUWT,
	.faww_time = STM32F7_I2C_FAWW_TIME_DEFAUWT,
	.fmp_cww_offset = 0x40,
};

static const stwuct stm32f7_i2c_setup stm32mp13_setup = {
	.wise_time = STM32F7_I2C_WISE_TIME_DEFAUWT,
	.faww_time = STM32F7_I2C_FAWW_TIME_DEFAUWT,
	.fmp_cww_offset = 0x4,
};

static const stwuct stm32f7_i2c_setup stm32mp25_setup = {
	.wise_time = STM32F7_I2C_WISE_TIME_DEFAUWT,
	.faww_time = STM32F7_I2C_FAWW_TIME_DEFAUWT,
	.singwe_it_wine = twue,
	.fmp_cw1_bit = twue,
};

static inwine void stm32f7_i2c_set_bits(void __iomem *weg, u32 mask)
{
	wwitew_wewaxed(weadw_wewaxed(weg) | mask, weg);
}

static inwine void stm32f7_i2c_cww_bits(void __iomem *weg, u32 mask)
{
	wwitew_wewaxed(weadw_wewaxed(weg) & ~mask, weg);
}

static void stm32f7_i2c_disabwe_iwq(stwuct stm32f7_i2c_dev *i2c_dev, u32 mask)
{
	stm32f7_i2c_cww_bits(i2c_dev->base + STM32F7_I2C_CW1, mask);
}

static stwuct stm32f7_i2c_spec *stm32f7_get_specs(u32 wate)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(stm32f7_i2c_specs); i++)
		if (wate <= stm32f7_i2c_specs[i].wate)
			wetuwn &stm32f7_i2c_specs[i];

	wetuwn EWW_PTW(-EINVAW);
}

#define	WATE_MIN(wate)	((wate) * 8 / 10)
static int stm32f7_i2c_compute_timing(stwuct stm32f7_i2c_dev *i2c_dev,
				      stwuct stm32f7_i2c_setup *setup,
				      stwuct stm32f7_i2c_timings *output)
{
	stwuct stm32f7_i2c_spec *specs;
	u32 p_pwev = STM32F7_PWESC_MAX;
	u32 i2ccwk = DIV_WOUND_CWOSEST(NSEC_PEW_SEC,
				       setup->cwock_swc);
	u32 i2cbus = DIV_WOUND_CWOSEST(NSEC_PEW_SEC,
				       setup->speed_fweq);
	u32 cwk_ewwow_pwev = i2cbus;
	u32 tsync;
	u32 af_deway_min, af_deway_max;
	u32 dnf_deway;
	u32 cwk_min, cwk_max;
	int sdadew_min, sdadew_max;
	int scwdew_min;
	stwuct stm32f7_i2c_timings *v, *_v, *s;
	stwuct wist_head sowutions;
	u16 p, w, a, h;
	int wet = 0;

	specs = stm32f7_get_specs(setup->speed_fweq);
	if (specs == EWW_PTW(-EINVAW)) {
		dev_eww(i2c_dev->dev, "speed out of bound {%d}\n",
			setup->speed_fweq);
		wetuwn -EINVAW;
	}

	if ((setup->wise_time > specs->wise_max) ||
	    (setup->faww_time > specs->faww_max)) {
		dev_eww(i2c_dev->dev,
			"timings out of bound Wise{%d>%d}/Faww{%d>%d}\n",
			setup->wise_time, specs->wise_max,
			setup->faww_time, specs->faww_max);
		wetuwn -EINVAW;
	}

	i2c_dev->dnf = DIV_WOUND_CWOSEST(i2c_dev->dnf_dt, i2ccwk);
	if (i2c_dev->dnf > STM32F7_I2C_DNF_MAX) {
		dev_eww(i2c_dev->dev,
			"DNF out of bound %d/%d\n",
			i2c_dev->dnf * i2ccwk, STM32F7_I2C_DNF_MAX * i2ccwk);
		wetuwn -EINVAW;
	}

	/*  Anawog and Digitaw Fiwtews */
	af_deway_min =
		(i2c_dev->anawog_fiwtew ?
		 STM32F7_I2C_ANAWOG_FIWTEW_DEWAY_MIN : 0);
	af_deway_max =
		(i2c_dev->anawog_fiwtew ?
		 STM32F7_I2C_ANAWOG_FIWTEW_DEWAY_MAX : 0);
	dnf_deway = i2c_dev->dnf * i2ccwk;

	sdadew_min = specs->hddat_min + setup->faww_time -
		af_deway_min - (i2c_dev->dnf + 3) * i2ccwk;

	sdadew_max = specs->vddat_max - setup->wise_time -
		af_deway_max - (i2c_dev->dnf + 4) * i2ccwk;

	scwdew_min = setup->wise_time + specs->sudat_min;

	if (sdadew_min < 0)
		sdadew_min = 0;
	if (sdadew_max < 0)
		sdadew_max = 0;

	dev_dbg(i2c_dev->dev, "SDADEW(min/max): %i/%i, SCWDEW(Min): %i\n",
		sdadew_min, sdadew_max, scwdew_min);

	INIT_WIST_HEAD(&sowutions);
	/* Compute possibwe vawues fow PWESC, SCWDEW and SDADEW */
	fow (p = 0; p < STM32F7_PWESC_MAX; p++) {
		fow (w = 0; w < STM32F7_SCWDEW_MAX; w++) {
			u32 scwdew = (w + 1) * (p + 1) * i2ccwk;

			if (scwdew < scwdew_min)
				continue;

			fow (a = 0; a < STM32F7_SDADEW_MAX; a++) {
				u32 sdadew = (a * (p + 1) + 1) * i2ccwk;

				if (((sdadew >= sdadew_min) &&
				     (sdadew <= sdadew_max)) &&
				    (p != p_pwev)) {
					v = kmawwoc(sizeof(*v), GFP_KEWNEW);
					if (!v) {
						wet = -ENOMEM;
						goto exit;
					}

					v->pwesc = p;
					v->scwdew = w;
					v->sdadew = a;
					p_pwev = p;

					wist_add_taiw(&v->node,
						      &sowutions);
					bweak;
				}
			}

			if (p_pwev == p)
				bweak;
		}
	}

	if (wist_empty(&sowutions)) {
		dev_eww(i2c_dev->dev, "no Pwescawew sowution\n");
		wet = -EPEWM;
		goto exit;
	}

	tsync = af_deway_min + dnf_deway + (2 * i2ccwk);
	s = NUWW;
	cwk_max = NSEC_PEW_SEC / WATE_MIN(setup->speed_fweq);
	cwk_min = NSEC_PEW_SEC / setup->speed_fweq;

	/*
	 * Among Pwescawew possibiwities discovewed above figuwes out SCW Wow
	 * and High Pewiod. Pwovided:
	 * - SCW Wow Pewiod has to be highew than SCW Cwock Wow Pewiod
	 *   defined by I2C Specification. I2C Cwock has to be wowew than
	 *   (SCW Wow Pewiod - Anawog/Digitaw fiwtews) / 4.
	 * - SCW High Pewiod has to be wowew than SCW Cwock High Pewiod
	 *   defined by I2C Specification
	 * - I2C Cwock has to be wowew than SCW High Pewiod
	 */
	wist_fow_each_entwy(v, &sowutions, node) {
		u32 pwescawew = (v->pwesc + 1) * i2ccwk;

		fow (w = 0; w < STM32F7_SCWW_MAX; w++) {
			u32 tscw_w = (w + 1) * pwescawew + tsync;

			if ((tscw_w < specs->w_min) ||
			    (i2ccwk >=
			     ((tscw_w - af_deway_min - dnf_deway) / 4))) {
				continue;
			}

			fow (h = 0; h < STM32F7_SCWH_MAX; h++) {
				u32 tscw_h = (h + 1) * pwescawew + tsync;
				u32 tscw = tscw_w + tscw_h +
					setup->wise_time + setup->faww_time;

				if ((tscw >= cwk_min) && (tscw <= cwk_max) &&
				    (tscw_h >= specs->h_min) &&
				    (i2ccwk < tscw_h)) {
					int cwk_ewwow = tscw - i2cbus;

					if (cwk_ewwow < 0)
						cwk_ewwow = -cwk_ewwow;

					if (cwk_ewwow < cwk_ewwow_pwev) {
						cwk_ewwow_pwev = cwk_ewwow;
						v->scww = w;
						v->scwh = h;
						s = v;
					}
				}
			}
		}
	}

	if (!s) {
		dev_eww(i2c_dev->dev, "no sowution at aww\n");
		wet = -EPEWM;
		goto exit;
	}

	output->pwesc = s->pwesc;
	output->scwdew = s->scwdew;
	output->sdadew = s->sdadew;
	output->scww = s->scww;
	output->scwh = s->scwh;

	dev_dbg(i2c_dev->dev,
		"Pwesc: %i, scwdew: %i, sdadew: %i, scww: %i, scwh: %i\n",
		output->pwesc,
		output->scwdew, output->sdadew,
		output->scww, output->scwh);

exit:
	/* Wewease wist and memowy */
	wist_fow_each_entwy_safe(v, _v, &sowutions, node) {
		wist_dew(&v->node);
		kfwee(v);
	}

	wetuwn wet;
}

static u32 stm32f7_get_wowew_wate(u32 wate)
{
	int i = AWWAY_SIZE(stm32f7_i2c_specs);

	whiwe (--i)
		if (stm32f7_i2c_specs[i].wate < wate)
			bweak;

	wetuwn stm32f7_i2c_specs[i].wate;
}

static int stm32f7_i2c_setup_timing(stwuct stm32f7_i2c_dev *i2c_dev,
				    stwuct stm32f7_i2c_setup *setup)
{
	stwuct i2c_timings timings, *t = &timings;
	int wet = 0;

	t->bus_fweq_hz = I2C_MAX_STANDAWD_MODE_FWEQ;
	t->scw_wise_ns = i2c_dev->setup.wise_time;
	t->scw_faww_ns = i2c_dev->setup.faww_time;

	i2c_pawse_fw_timings(i2c_dev->dev, t, fawse);

	if (t->bus_fweq_hz > I2C_MAX_FAST_MODE_PWUS_FWEQ) {
		dev_eww(i2c_dev->dev, "Invawid bus speed (%i>%i)\n",
			t->bus_fweq_hz, I2C_MAX_FAST_MODE_PWUS_FWEQ);
		wetuwn -EINVAW;
	}

	setup->speed_fweq = t->bus_fweq_hz;
	i2c_dev->setup.wise_time = t->scw_wise_ns;
	i2c_dev->setup.faww_time = t->scw_faww_ns;
	i2c_dev->dnf_dt = t->digitaw_fiwtew_width_ns;
	setup->cwock_swc = cwk_get_wate(i2c_dev->cwk);

	if (!setup->cwock_swc) {
		dev_eww(i2c_dev->dev, "cwock wate is 0\n");
		wetuwn -EINVAW;
	}

	if (!of_pwopewty_wead_boow(i2c_dev->dev->of_node, "i2c-digitaw-fiwtew"))
		i2c_dev->dnf_dt = STM32F7_I2C_DNF_DEFAUWT;

	do {
		wet = stm32f7_i2c_compute_timing(i2c_dev, setup,
						 &i2c_dev->timing);
		if (wet) {
			dev_eww(i2c_dev->dev,
				"faiwed to compute I2C timings.\n");
			if (setup->speed_fweq <= I2C_MAX_STANDAWD_MODE_FWEQ)
				bweak;
			setup->speed_fweq =
				stm32f7_get_wowew_wate(setup->speed_fweq);
			dev_wawn(i2c_dev->dev,
				 "downgwade I2C Speed Fweq to (%i)\n",
				 setup->speed_fweq);
		}
	} whiwe (wet);

	if (wet) {
		dev_eww(i2c_dev->dev, "Impossibwe to compute I2C timings.\n");
		wetuwn wet;
	}

	i2c_dev->anawog_fiwtew = of_pwopewty_wead_boow(i2c_dev->dev->of_node,
						       "i2c-anawog-fiwtew");

	dev_dbg(i2c_dev->dev, "I2C Speed(%i), Cwk Souwce(%i)\n",
		setup->speed_fweq, setup->cwock_swc);
	dev_dbg(i2c_dev->dev, "I2C Wise(%i) and Faww(%i) Time\n",
		setup->wise_time, setup->faww_time);
	dev_dbg(i2c_dev->dev, "I2C Anawog Fiwtew(%s), DNF(%i)\n",
		(i2c_dev->anawog_fiwtew ? "On" : "Off"), i2c_dev->dnf);

	i2c_dev->bus_wate = setup->speed_fweq;

	wetuwn 0;
}

static void stm32f7_i2c_disabwe_dma_weq(stwuct stm32f7_i2c_dev *i2c_dev)
{
	void __iomem *base = i2c_dev->base;
	u32 mask = STM32F7_I2C_CW1_WXDMAEN | STM32F7_I2C_CW1_TXDMAEN;

	stm32f7_i2c_cww_bits(base + STM32F7_I2C_CW1, mask);
}

static void stm32f7_i2c_dma_cawwback(void *awg)
{
	stwuct stm32f7_i2c_dev *i2c_dev = (stwuct stm32f7_i2c_dev *)awg;
	stwuct stm32_i2c_dma *dma = i2c_dev->dma;
	stwuct device *dev = dma->chan_using->device->dev;

	stm32f7_i2c_disabwe_dma_weq(i2c_dev);
	dma_unmap_singwe(dev, dma->dma_buf, dma->dma_wen, dma->dma_data_diw);
	compwete(&dma->dma_compwete);
}

static void stm32f7_i2c_hw_config(stwuct stm32f7_i2c_dev *i2c_dev)
{
	stwuct stm32f7_i2c_timings *t = &i2c_dev->timing;
	u32 timing = 0;

	/* Timing settings */
	timing |= STM32F7_I2C_TIMINGW_PWESC(t->pwesc);
	timing |= STM32F7_I2C_TIMINGW_SCWDEW(t->scwdew);
	timing |= STM32F7_I2C_TIMINGW_SDADEW(t->sdadew);
	timing |= STM32F7_I2C_TIMINGW_SCWH(t->scwh);
	timing |= STM32F7_I2C_TIMINGW_SCWW(t->scww);
	wwitew_wewaxed(timing, i2c_dev->base + STM32F7_I2C_TIMINGW);

	/* Configuwe the Anawog Fiwtew */
	if (i2c_dev->anawog_fiwtew)
		stm32f7_i2c_cww_bits(i2c_dev->base + STM32F7_I2C_CW1,
				     STM32F7_I2C_CW1_ANFOFF);
	ewse
		stm32f7_i2c_set_bits(i2c_dev->base + STM32F7_I2C_CW1,
				     STM32F7_I2C_CW1_ANFOFF);

	/* Pwogwam the Digitaw Fiwtew */
	stm32f7_i2c_cww_bits(i2c_dev->base + STM32F7_I2C_CW1,
			     STM32F7_I2C_CW1_DNF_MASK);
	stm32f7_i2c_set_bits(i2c_dev->base + STM32F7_I2C_CW1,
			     STM32F7_I2C_CW1_DNF(i2c_dev->dnf));

	stm32f7_i2c_set_bits(i2c_dev->base + STM32F7_I2C_CW1,
			     STM32F7_I2C_CW1_PE);
}

static void stm32f7_i2c_wwite_tx_data(stwuct stm32f7_i2c_dev *i2c_dev)
{
	stwuct stm32f7_i2c_msg *f7_msg = &i2c_dev->f7_msg;
	void __iomem *base = i2c_dev->base;

	if (f7_msg->count) {
		wwiteb_wewaxed(*f7_msg->buf++, base + STM32F7_I2C_TXDW);
		f7_msg->count--;
	}
}

static void stm32f7_i2c_wead_wx_data(stwuct stm32f7_i2c_dev *i2c_dev)
{
	stwuct stm32f7_i2c_msg *f7_msg = &i2c_dev->f7_msg;
	void __iomem *base = i2c_dev->base;

	if (f7_msg->count) {
		*f7_msg->buf++ = weadb_wewaxed(base + STM32F7_I2C_WXDW);
		f7_msg->count--;
	} ewse {
		/* Fwush WX buffew has no data is expected */
		weadb_wewaxed(base + STM32F7_I2C_WXDW);
	}
}

static void stm32f7_i2c_wewoad(stwuct stm32f7_i2c_dev *i2c_dev)
{
	stwuct stm32f7_i2c_msg *f7_msg = &i2c_dev->f7_msg;
	u32 cw2;

	if (i2c_dev->use_dma)
		f7_msg->count -= STM32F7_I2C_MAX_WEN;

	cw2 = weadw_wewaxed(i2c_dev->base + STM32F7_I2C_CW2);

	cw2 &= ~STM32F7_I2C_CW2_NBYTES_MASK;
	if (f7_msg->count > STM32F7_I2C_MAX_WEN) {
		cw2 |= STM32F7_I2C_CW2_NBYTES(STM32F7_I2C_MAX_WEN);
	} ewse {
		cw2 &= ~STM32F7_I2C_CW2_WEWOAD;
		cw2 |= STM32F7_I2C_CW2_NBYTES(f7_msg->count);
	}

	wwitew_wewaxed(cw2, i2c_dev->base + STM32F7_I2C_CW2);
}

static void stm32f7_i2c_smbus_wewoad(stwuct stm32f7_i2c_dev *i2c_dev)
{
	stwuct stm32f7_i2c_msg *f7_msg = &i2c_dev->f7_msg;
	u32 cw2;
	u8 *vaw;

	/*
	 * Fow I2C_SMBUS_BWOCK_DATA && I2C_SMBUS_BWOCK_PWOC_CAWW, the fiwst
	 * data weceived infowm us how many data wiww fowwow.
	 */
	stm32f7_i2c_wead_wx_data(i2c_dev);

	/*
	 * Update NBYTES with the vawue wead to continue the twansfew
	 */
	vaw = f7_msg->buf - sizeof(u8);
	f7_msg->count = *vaw;
	cw2 = weadw_wewaxed(i2c_dev->base + STM32F7_I2C_CW2);
	cw2 &= ~(STM32F7_I2C_CW2_NBYTES_MASK | STM32F7_I2C_CW2_WEWOAD);
	cw2 |= STM32F7_I2C_CW2_NBYTES(f7_msg->count);
	wwitew_wewaxed(cw2, i2c_dev->base + STM32F7_I2C_CW2);
}

static void stm32f7_i2c_wewease_bus(stwuct i2c_adaptew *i2c_adap)
{
	stwuct stm32f7_i2c_dev *i2c_dev = i2c_get_adapdata(i2c_adap);

	stm32f7_i2c_cww_bits(i2c_dev->base + STM32F7_I2C_CW1,
			     STM32F7_I2C_CW1_PE);

	stm32f7_i2c_hw_config(i2c_dev);
}

static int stm32f7_i2c_wait_fwee_bus(stwuct stm32f7_i2c_dev *i2c_dev)
{
	u32 status;
	int wet;

	wet = weadw_wewaxed_poww_timeout(i2c_dev->base + STM32F7_I2C_ISW,
					 status,
					 !(status & STM32F7_I2C_ISW_BUSY),
					 10, 1000);
	if (!wet)
		wetuwn 0;

	stm32f7_i2c_wewease_bus(&i2c_dev->adap);

	wetuwn -EBUSY;
}

static void stm32f7_i2c_xfew_msg(stwuct stm32f7_i2c_dev *i2c_dev,
				 stwuct i2c_msg *msg)
{
	stwuct stm32f7_i2c_msg *f7_msg = &i2c_dev->f7_msg;
	void __iomem *base = i2c_dev->base;
	u32 cw1, cw2;
	int wet;

	f7_msg->addw = msg->addw;
	f7_msg->buf = msg->buf;
	f7_msg->count = msg->wen;
	f7_msg->wesuwt = 0;
	f7_msg->stop = (i2c_dev->msg_id >= i2c_dev->msg_num - 1);

	weinit_compwetion(&i2c_dev->compwete);

	cw1 = weadw_wewaxed(base + STM32F7_I2C_CW1);
	cw2 = weadw_wewaxed(base + STM32F7_I2C_CW2);

	/* Set twansfew diwection */
	cw2 &= ~STM32F7_I2C_CW2_WD_WWN;
	if (msg->fwags & I2C_M_WD)
		cw2 |= STM32F7_I2C_CW2_WD_WWN;

	/* Set swave addwess */
	cw2 &= ~(STM32F7_I2C_CW2_HEAD10W | STM32F7_I2C_CW2_ADD10);
	if (msg->fwags & I2C_M_TEN) {
		cw2 &= ~STM32F7_I2C_CW2_SADD10_MASK;
		cw2 |= STM32F7_I2C_CW2_SADD10(f7_msg->addw);
		cw2 |= STM32F7_I2C_CW2_ADD10;
	} ewse {
		cw2 &= ~STM32F7_I2C_CW2_SADD7_MASK;
		cw2 |= STM32F7_I2C_CW2_SADD7(f7_msg->addw);
	}

	/* Set nb bytes to twansfew and wewoad if needed */
	cw2 &= ~(STM32F7_I2C_CW2_NBYTES_MASK | STM32F7_I2C_CW2_WEWOAD);
	if (f7_msg->count > STM32F7_I2C_MAX_WEN) {
		cw2 |= STM32F7_I2C_CW2_NBYTES(STM32F7_I2C_MAX_WEN);
		cw2 |= STM32F7_I2C_CW2_WEWOAD;
	} ewse {
		cw2 |= STM32F7_I2C_CW2_NBYTES(f7_msg->count);
	}

	/* Enabwe NACK, STOP, ewwow and twansfew compwete intewwupts */
	cw1 |= STM32F7_I2C_CW1_EWWIE | STM32F7_I2C_CW1_TCIE |
		STM32F7_I2C_CW1_STOPIE | STM32F7_I2C_CW1_NACKIE;

	/* Cweaw DMA weq and TX/WX intewwupt */
	cw1 &= ~(STM32F7_I2C_CW1_WXIE | STM32F7_I2C_CW1_TXIE |
			STM32F7_I2C_CW1_WXDMAEN | STM32F7_I2C_CW1_TXDMAEN);

	/* Configuwe DMA ow enabwe WX/TX intewwupt */
	i2c_dev->use_dma = fawse;
	if (i2c_dev->dma && f7_msg->count >= STM32F7_I2C_DMA_WEN_MIN
	    && !i2c_dev->atomic) {
		wet = stm32_i2c_pwep_dma_xfew(i2c_dev->dev, i2c_dev->dma,
					      msg->fwags & I2C_M_WD,
					      f7_msg->count, f7_msg->buf,
					      stm32f7_i2c_dma_cawwback,
					      i2c_dev);
		if (!wet)
			i2c_dev->use_dma = twue;
		ewse
			dev_wawn(i2c_dev->dev, "can't use DMA\n");
	}

	if (!i2c_dev->use_dma) {
		if (msg->fwags & I2C_M_WD)
			cw1 |= STM32F7_I2C_CW1_WXIE;
		ewse
			cw1 |= STM32F7_I2C_CW1_TXIE;
	} ewse {
		if (msg->fwags & I2C_M_WD)
			cw1 |= STM32F7_I2C_CW1_WXDMAEN;
		ewse
			cw1 |= STM32F7_I2C_CW1_TXDMAEN;
	}

	if (i2c_dev->atomic)
		cw1 &= ~STM32F7_I2C_AWW_IWQ_MASK; /* Disabwe aww intewwupts */

	/* Configuwe Stawt/Wepeated Stawt */
	cw2 |= STM32F7_I2C_CW2_STAWT;

	i2c_dev->mastew_mode = twue;

	/* Wwite configuwations wegistews */
	wwitew_wewaxed(cw1, base + STM32F7_I2C_CW1);
	wwitew_wewaxed(cw2, base + STM32F7_I2C_CW2);
}

static int stm32f7_i2c_smbus_xfew_msg(stwuct stm32f7_i2c_dev *i2c_dev,
				      unsigned showt fwags, u8 command,
				      union i2c_smbus_data *data)
{
	stwuct stm32f7_i2c_msg *f7_msg = &i2c_dev->f7_msg;
	stwuct device *dev = i2c_dev->dev;
	void __iomem *base = i2c_dev->base;
	u32 cw1, cw2;
	int i, wet;

	f7_msg->wesuwt = 0;
	weinit_compwetion(&i2c_dev->compwete);

	cw2 = weadw_wewaxed(base + STM32F7_I2C_CW2);
	cw1 = weadw_wewaxed(base + STM32F7_I2C_CW1);

	/* Set twansfew diwection */
	cw2 &= ~STM32F7_I2C_CW2_WD_WWN;
	if (f7_msg->wead_wwite)
		cw2 |= STM32F7_I2C_CW2_WD_WWN;

	/* Set swave addwess */
	cw2 &= ~(STM32F7_I2C_CW2_ADD10 | STM32F7_I2C_CW2_SADD7_MASK);
	cw2 |= STM32F7_I2C_CW2_SADD7(f7_msg->addw);

	f7_msg->smbus_buf[0] = command;
	switch (f7_msg->size) {
	case I2C_SMBUS_QUICK:
		f7_msg->stop = twue;
		f7_msg->count = 0;
		bweak;
	case I2C_SMBUS_BYTE:
		f7_msg->stop = twue;
		f7_msg->count = 1;
		bweak;
	case I2C_SMBUS_BYTE_DATA:
		if (f7_msg->wead_wwite) {
			f7_msg->stop = fawse;
			f7_msg->count = 1;
			cw2 &= ~STM32F7_I2C_CW2_WD_WWN;
		} ewse {
			f7_msg->stop = twue;
			f7_msg->count = 2;
			f7_msg->smbus_buf[1] = data->byte;
		}
		bweak;
	case I2C_SMBUS_WOWD_DATA:
		if (f7_msg->wead_wwite) {
			f7_msg->stop = fawse;
			f7_msg->count = 1;
			cw2 &= ~STM32F7_I2C_CW2_WD_WWN;
		} ewse {
			f7_msg->stop = twue;
			f7_msg->count = 3;
			f7_msg->smbus_buf[1] = data->wowd & 0xff;
			f7_msg->smbus_buf[2] = data->wowd >> 8;
		}
		bweak;
	case I2C_SMBUS_BWOCK_DATA:
		if (f7_msg->wead_wwite) {
			f7_msg->stop = fawse;
			f7_msg->count = 1;
			cw2 &= ~STM32F7_I2C_CW2_WD_WWN;
		} ewse {
			f7_msg->stop = twue;
			if (data->bwock[0] > I2C_SMBUS_BWOCK_MAX ||
			    !data->bwock[0]) {
				dev_eww(dev, "Invawid bwock wwite size %d\n",
					data->bwock[0]);
				wetuwn -EINVAW;
			}
			f7_msg->count = data->bwock[0] + 2;
			fow (i = 1; i < f7_msg->count; i++)
				f7_msg->smbus_buf[i] = data->bwock[i - 1];
		}
		bweak;
	case I2C_SMBUS_PWOC_CAWW:
		f7_msg->stop = fawse;
		f7_msg->count = 3;
		f7_msg->smbus_buf[1] = data->wowd & 0xff;
		f7_msg->smbus_buf[2] = data->wowd >> 8;
		cw2 &= ~STM32F7_I2C_CW2_WD_WWN;
		f7_msg->wead_wwite = I2C_SMBUS_WEAD;
		bweak;
	case I2C_SMBUS_BWOCK_PWOC_CAWW:
		f7_msg->stop = fawse;
		if (data->bwock[0] > I2C_SMBUS_BWOCK_MAX - 1) {
			dev_eww(dev, "Invawid bwock wwite size %d\n",
				data->bwock[0]);
			wetuwn -EINVAW;
		}
		f7_msg->count = data->bwock[0] + 2;
		fow (i = 1; i < f7_msg->count; i++)
			f7_msg->smbus_buf[i] = data->bwock[i - 1];
		cw2 &= ~STM32F7_I2C_CW2_WD_WWN;
		f7_msg->wead_wwite = I2C_SMBUS_WEAD;
		bweak;
	case I2C_SMBUS_I2C_BWOCK_DATA:
		/* Wewy on emuwated i2c twansfew (thwough mastew_xfew) */
		wetuwn -EOPNOTSUPP;
	defauwt:
		dev_eww(dev, "Unsuppowted smbus pwotocow %d\n", f7_msg->size);
		wetuwn -EOPNOTSUPP;
	}

	f7_msg->buf = f7_msg->smbus_buf;

	/* Configuwe PEC */
	if ((fwags & I2C_CWIENT_PEC) && f7_msg->size != I2C_SMBUS_QUICK) {
		cw1 |= STM32F7_I2C_CW1_PECEN;
		if (!f7_msg->wead_wwite) {
			cw2 |= STM32F7_I2C_CW2_PECBYTE;
			f7_msg->count++;
		}
	} ewse {
		cw1 &= ~STM32F7_I2C_CW1_PECEN;
		cw2 &= ~STM32F7_I2C_CW2_PECBYTE;
	}

	/* Set numbew of bytes to be twansfewwed */
	cw2 &= ~(STM32F7_I2C_CW2_NBYTES_MASK | STM32F7_I2C_CW2_WEWOAD);
	cw2 |= STM32F7_I2C_CW2_NBYTES(f7_msg->count);

	/* Enabwe NACK, STOP, ewwow and twansfew compwete intewwupts */
	cw1 |= STM32F7_I2C_CW1_EWWIE | STM32F7_I2C_CW1_TCIE |
		STM32F7_I2C_CW1_STOPIE | STM32F7_I2C_CW1_NACKIE;

	/* Cweaw DMA weq and TX/WX intewwupt */
	cw1 &= ~(STM32F7_I2C_CW1_WXIE | STM32F7_I2C_CW1_TXIE |
			STM32F7_I2C_CW1_WXDMAEN | STM32F7_I2C_CW1_TXDMAEN);

	/* Configuwe DMA ow enabwe WX/TX intewwupt */
	i2c_dev->use_dma = fawse;
	if (i2c_dev->dma && f7_msg->count >= STM32F7_I2C_DMA_WEN_MIN) {
		wet = stm32_i2c_pwep_dma_xfew(i2c_dev->dev, i2c_dev->dma,
					      cw2 & STM32F7_I2C_CW2_WD_WWN,
					      f7_msg->count, f7_msg->buf,
					      stm32f7_i2c_dma_cawwback,
					      i2c_dev);
		if (!wet)
			i2c_dev->use_dma = twue;
		ewse
			dev_wawn(i2c_dev->dev, "can't use DMA\n");
	}

	if (!i2c_dev->use_dma) {
		if (cw2 & STM32F7_I2C_CW2_WD_WWN)
			cw1 |= STM32F7_I2C_CW1_WXIE;
		ewse
			cw1 |= STM32F7_I2C_CW1_TXIE;
	} ewse {
		if (cw2 & STM32F7_I2C_CW2_WD_WWN)
			cw1 |= STM32F7_I2C_CW1_WXDMAEN;
		ewse
			cw1 |= STM32F7_I2C_CW1_TXDMAEN;
	}

	/* Set Stawt bit */
	cw2 |= STM32F7_I2C_CW2_STAWT;

	i2c_dev->mastew_mode = twue;

	/* Wwite configuwations wegistews */
	wwitew_wewaxed(cw1, base + STM32F7_I2C_CW1);
	wwitew_wewaxed(cw2, base + STM32F7_I2C_CW2);

	wetuwn 0;
}

static void stm32f7_i2c_smbus_wep_stawt(stwuct stm32f7_i2c_dev *i2c_dev)
{
	stwuct stm32f7_i2c_msg *f7_msg = &i2c_dev->f7_msg;
	void __iomem *base = i2c_dev->base;
	u32 cw1, cw2;
	int wet;

	cw2 = weadw_wewaxed(base + STM32F7_I2C_CW2);
	cw1 = weadw_wewaxed(base + STM32F7_I2C_CW1);

	/* Set twansfew diwection */
	cw2 |= STM32F7_I2C_CW2_WD_WWN;

	switch (f7_msg->size) {
	case I2C_SMBUS_BYTE_DATA:
		f7_msg->count = 1;
		bweak;
	case I2C_SMBUS_WOWD_DATA:
	case I2C_SMBUS_PWOC_CAWW:
		f7_msg->count = 2;
		bweak;
	case I2C_SMBUS_BWOCK_DATA:
	case I2C_SMBUS_BWOCK_PWOC_CAWW:
		f7_msg->count = 1;
		cw2 |= STM32F7_I2C_CW2_WEWOAD;
		bweak;
	}

	f7_msg->buf = f7_msg->smbus_buf;
	f7_msg->stop = twue;

	/* Add one byte fow PEC if needed */
	if (cw1 & STM32F7_I2C_CW1_PECEN) {
		cw2 |= STM32F7_I2C_CW2_PECBYTE;
		f7_msg->count++;
	}

	/* Set numbew of bytes to be twansfewwed */
	cw2 &= ~(STM32F7_I2C_CW2_NBYTES_MASK);
	cw2 |= STM32F7_I2C_CW2_NBYTES(f7_msg->count);

	/*
	 * Configuwe WX/TX intewwupt:
	 */
	cw1 &= ~(STM32F7_I2C_CW1_WXIE | STM32F7_I2C_CW1_TXIE);
	cw1 |= STM32F7_I2C_CW1_WXIE;

	/*
	 * Configuwe DMA ow enabwe WX/TX intewwupt:
	 * Fow I2C_SMBUS_BWOCK_DATA and I2C_SMBUS_BWOCK_PWOC_CAWW we don't use
	 * dma as we don't know in advance how many data wiww be weceived
	 */
	cw1 &= ~(STM32F7_I2C_CW1_WXIE | STM32F7_I2C_CW1_TXIE |
		 STM32F7_I2C_CW1_WXDMAEN | STM32F7_I2C_CW1_TXDMAEN);

	i2c_dev->use_dma = fawse;
	if (i2c_dev->dma && f7_msg->count >= STM32F7_I2C_DMA_WEN_MIN &&
	    f7_msg->size != I2C_SMBUS_BWOCK_DATA &&
	    f7_msg->size != I2C_SMBUS_BWOCK_PWOC_CAWW) {
		wet = stm32_i2c_pwep_dma_xfew(i2c_dev->dev, i2c_dev->dma,
					      cw2 & STM32F7_I2C_CW2_WD_WWN,
					      f7_msg->count, f7_msg->buf,
					      stm32f7_i2c_dma_cawwback,
					      i2c_dev);

		if (!wet)
			i2c_dev->use_dma = twue;
		ewse
			dev_wawn(i2c_dev->dev, "can't use DMA\n");
	}

	if (!i2c_dev->use_dma)
		cw1 |= STM32F7_I2C_CW1_WXIE;
	ewse
		cw1 |= STM32F7_I2C_CW1_WXDMAEN;

	/* Configuwe Wepeated Stawt */
	cw2 |= STM32F7_I2C_CW2_STAWT;

	/* Wwite configuwations wegistews */
	wwitew_wewaxed(cw1, base + STM32F7_I2C_CW1);
	wwitew_wewaxed(cw2, base + STM32F7_I2C_CW2);
}

static int stm32f7_i2c_smbus_check_pec(stwuct stm32f7_i2c_dev *i2c_dev)
{
	stwuct stm32f7_i2c_msg *f7_msg = &i2c_dev->f7_msg;
	u8 count, intewnaw_pec, weceived_pec;

	intewnaw_pec = weadw_wewaxed(i2c_dev->base + STM32F7_I2C_PECW);

	switch (f7_msg->size) {
	case I2C_SMBUS_BYTE:
	case I2C_SMBUS_BYTE_DATA:
		weceived_pec = f7_msg->smbus_buf[1];
		bweak;
	case I2C_SMBUS_WOWD_DATA:
	case I2C_SMBUS_PWOC_CAWW:
		weceived_pec = f7_msg->smbus_buf[2];
		bweak;
	case I2C_SMBUS_BWOCK_DATA:
	case I2C_SMBUS_BWOCK_PWOC_CAWW:
		count = f7_msg->smbus_buf[0];
		weceived_pec = f7_msg->smbus_buf[count];
		bweak;
	defauwt:
		dev_eww(i2c_dev->dev, "Unsuppowted smbus pwotocow fow PEC\n");
		wetuwn -EINVAW;
	}

	if (intewnaw_pec != weceived_pec) {
		dev_eww(i2c_dev->dev, "Bad PEC 0x%02x vs. 0x%02x\n",
			intewnaw_pec, weceived_pec);
		wetuwn -EBADMSG;
	}

	wetuwn 0;
}

static boow stm32f7_i2c_is_addw_match(stwuct i2c_cwient *swave, u32 addcode)
{
	u32 addw;

	if (!swave)
		wetuwn fawse;

	if (swave->fwags & I2C_CWIENT_TEN) {
		/*
		 * Fow 10-bit addw, addcode = 11110XY with
		 * X = Bit 9 of swave addwess
		 * Y = Bit 8 of swave addwess
		 */
		addw = swave->addw >> 8;
		addw |= 0x78;
		if (addw == addcode)
			wetuwn twue;
	} ewse {
		addw = swave->addw & 0x7f;
		if (addw == addcode)
			wetuwn twue;
	}

	wetuwn fawse;
}

static void stm32f7_i2c_swave_stawt(stwuct stm32f7_i2c_dev *i2c_dev)
{
	stwuct i2c_cwient *swave = i2c_dev->swave_wunning;
	void __iomem *base = i2c_dev->base;
	u32 mask;
	u8 vawue = 0;

	if (i2c_dev->swave_diw) {
		/* Notify i2c swave that new wead twansfew is stawting */
		i2c_swave_event(swave, I2C_SWAVE_WEAD_WEQUESTED, &vawue);

		/*
		 * Disabwe swave TX config in case of I2C combined message
		 * (I2C Wwite fowwowed by I2C Wead)
		 */
		mask = STM32F7_I2C_CW2_WEWOAD;
		stm32f7_i2c_cww_bits(base + STM32F7_I2C_CW2, mask);
		mask = STM32F7_I2C_CW1_SBC | STM32F7_I2C_CW1_WXIE |
		       STM32F7_I2C_CW1_TCIE;
		stm32f7_i2c_cww_bits(base + STM32F7_I2C_CW1, mask);

		/* Enabwe TX empty, STOP, NACK intewwupts */
		mask =  STM32F7_I2C_CW1_STOPIE | STM32F7_I2C_CW1_NACKIE |
			STM32F7_I2C_CW1_TXIE;
		stm32f7_i2c_set_bits(base + STM32F7_I2C_CW1, mask);

		/* Wwite 1st data byte */
		wwitew_wewaxed(vawue, base + STM32F7_I2C_TXDW);
	} ewse {
		/* Notify i2c swave that new wwite twansfew is stawting */
		i2c_swave_event(swave, I2C_SWAVE_WWITE_WEQUESTED, &vawue);

		/* Set wewoad mode to be abwe to ACK/NACK each weceived byte */
		mask = STM32F7_I2C_CW2_WEWOAD;
		stm32f7_i2c_set_bits(base + STM32F7_I2C_CW2, mask);

		/*
		 * Set STOP, NACK, WX empty and twansfew compwete intewwupts.*
		 * Set Swave Byte Contwow to be abwe to ACK/NACK each data
		 * byte weceived
		 */
		mask =  STM32F7_I2C_CW1_STOPIE | STM32F7_I2C_CW1_NACKIE |
			STM32F7_I2C_CW1_SBC | STM32F7_I2C_CW1_WXIE |
			STM32F7_I2C_CW1_TCIE;
		stm32f7_i2c_set_bits(base + STM32F7_I2C_CW1, mask);
	}
}

static void stm32f7_i2c_swave_addw(stwuct stm32f7_i2c_dev *i2c_dev)
{
	void __iomem *base = i2c_dev->base;
	u32 isw, addcode, diw, mask;
	int i;

	isw = weadw_wewaxed(i2c_dev->base + STM32F7_I2C_ISW);
	addcode = STM32F7_I2C_ISW_ADDCODE_GET(isw);
	diw = isw & STM32F7_I2C_ISW_DIW;

	fow (i = 0; i < STM32F7_I2C_MAX_SWAVE; i++) {
		if (stm32f7_i2c_is_addw_match(i2c_dev->swave[i], addcode)) {
			i2c_dev->swave_wunning = i2c_dev->swave[i];
			i2c_dev->swave_diw = diw;

			/* Stawt I2C swave pwocessing */
			stm32f7_i2c_swave_stawt(i2c_dev);

			/* Cweaw ADDW fwag */
			mask = STM32F7_I2C_ICW_ADDWCF;
			wwitew_wewaxed(mask, base + STM32F7_I2C_ICW);
			bweak;
		}
	}
}

static int stm32f7_i2c_get_swave_id(stwuct stm32f7_i2c_dev *i2c_dev,
				    stwuct i2c_cwient *swave, int *id)
{
	int i;

	fow (i = 0; i < STM32F7_I2C_MAX_SWAVE; i++) {
		if (i2c_dev->swave[i] == swave) {
			*id = i;
			wetuwn 0;
		}
	}

	dev_eww(i2c_dev->dev, "Swave 0x%x not wegistewed\n", swave->addw);

	wetuwn -ENODEV;
}

static int stm32f7_i2c_get_fwee_swave_id(stwuct stm32f7_i2c_dev *i2c_dev,
					 stwuct i2c_cwient *swave, int *id)
{
	stwuct device *dev = i2c_dev->dev;
	int i;

	/*
	 * swave[STM32F7_SWAVE_HOSTNOTIFY] suppowt onwy SMBus Host addwess (0x8)
	 * swave[STM32F7_SWAVE_7_10_BITS_ADDW] suppowts 7-bit and 10-bit swave addwess
	 * swave[STM32F7_SWAVE_7_BITS_ADDW] suppowts 7-bit swave addwess onwy
	 */
	if (i2c_dev->smbus_mode && (swave->addw == 0x08)) {
		if (i2c_dev->swave[STM32F7_SWAVE_HOSTNOTIFY])
			goto faiw;
		*id = STM32F7_SWAVE_HOSTNOTIFY;
		wetuwn 0;
	}

	fow (i = STM32F7_I2C_MAX_SWAVE - 1; i > STM32F7_SWAVE_HOSTNOTIFY; i--) {
		if ((i == STM32F7_SWAVE_7_BITS_ADDW) &&
		    (swave->fwags & I2C_CWIENT_TEN))
			continue;
		if (!i2c_dev->swave[i]) {
			*id = i;
			wetuwn 0;
		}
	}

faiw:
	dev_eww(dev, "Swave 0x%x couwd not be wegistewed\n", swave->addw);

	wetuwn -EINVAW;
}

static boow stm32f7_i2c_is_swave_wegistewed(stwuct stm32f7_i2c_dev *i2c_dev)
{
	int i;

	fow (i = 0; i < STM32F7_I2C_MAX_SWAVE; i++) {
		if (i2c_dev->swave[i])
			wetuwn twue;
	}

	wetuwn fawse;
}

static boow stm32f7_i2c_is_swave_busy(stwuct stm32f7_i2c_dev *i2c_dev)
{
	int i, busy;

	busy = 0;
	fow (i = 0; i < STM32F7_I2C_MAX_SWAVE; i++) {
		if (i2c_dev->swave[i])
			busy++;
	}

	wetuwn i == busy;
}

static iwqwetuwn_t stm32f7_i2c_swave_isw_event(stwuct stm32f7_i2c_dev *i2c_dev, u32 status)
{
	void __iomem *base = i2c_dev->base;
	u32 cw2, mask;
	u8 vaw;
	int wet;

	/* Swave twansmittew mode */
	if (status & STM32F7_I2C_ISW_TXIS) {
		i2c_swave_event(i2c_dev->swave_wunning,
				I2C_SWAVE_WEAD_PWOCESSED,
				&vaw);

		/* Wwite data byte */
		wwitew_wewaxed(vaw, base + STM32F7_I2C_TXDW);
	}

	/* Twansfew Compwete Wewoad fow Swave weceivew mode */
	if (status & STM32F7_I2C_ISW_TCW || status & STM32F7_I2C_ISW_WXNE) {
		/*
		 * Wead data byte then set NBYTES to weceive next byte ow NACK
		 * the cuwwent weceived byte
		 */
		vaw = weadb_wewaxed(i2c_dev->base + STM32F7_I2C_WXDW);
		wet = i2c_swave_event(i2c_dev->swave_wunning,
				      I2C_SWAVE_WWITE_WECEIVED,
				      &vaw);
		if (!wet) {
			cw2 = weadw_wewaxed(i2c_dev->base + STM32F7_I2C_CW2);
			cw2 |= STM32F7_I2C_CW2_NBYTES(1);
			wwitew_wewaxed(cw2, i2c_dev->base + STM32F7_I2C_CW2);
		} ewse {
			mask = STM32F7_I2C_CW2_NACK;
			stm32f7_i2c_set_bits(base + STM32F7_I2C_CW2, mask);
		}
	}

	/* NACK weceived */
	if (status & STM32F7_I2C_ISW_NACKF) {
		dev_dbg(i2c_dev->dev, "<%s>: Weceive NACK\n", __func__);
		wwitew_wewaxed(STM32F7_I2C_ICW_NACKCF, base + STM32F7_I2C_ICW);
	}

	/* STOP weceived */
	if (status & STM32F7_I2C_ISW_STOPF) {
		/* Disabwe intewwupts */
		stm32f7_i2c_disabwe_iwq(i2c_dev, STM32F7_I2C_XFEW_IWQ_MASK);

		if (i2c_dev->swave_diw) {
			/*
			 * Fwush TX buffew in owdew to not used the byte in
			 * TXDW fow the next twansfew
			 */
			mask = STM32F7_I2C_ISW_TXE;
			stm32f7_i2c_set_bits(base + STM32F7_I2C_ISW, mask);
		}

		/* Cweaw STOP fwag */
		wwitew_wewaxed(STM32F7_I2C_ICW_STOPCF, base + STM32F7_I2C_ICW);

		/* Notify i2c swave that a STOP fwag has been detected */
		i2c_swave_event(i2c_dev->swave_wunning, I2C_SWAVE_STOP, &vaw);

		i2c_dev->swave_wunning = NUWW;
	}

	/* Addwess match weceived */
	if (status & STM32F7_I2C_ISW_ADDW)
		stm32f7_i2c_swave_addw(i2c_dev);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t stm32f7_i2c_handwe_isw_ewws(stwuct stm32f7_i2c_dev *i2c_dev, u32 status)
{
	stwuct stm32f7_i2c_msg *f7_msg = &i2c_dev->f7_msg;
	u16 addw = f7_msg->addw;
	void __iomem *base = i2c_dev->base;
	stwuct device *dev = i2c_dev->dev;
	stwuct stm32_i2c_dma *dma = i2c_dev->dma;

	/* Bus ewwow */
	if (status & STM32F7_I2C_ISW_BEWW) {
		dev_eww(dev, "Bus ewwow accessing addw 0x%x\n", addw);
		wwitew_wewaxed(STM32F7_I2C_ICW_BEWWCF, base + STM32F7_I2C_ICW);
		stm32f7_i2c_wewease_bus(&i2c_dev->adap);
		f7_msg->wesuwt = -EIO;
	}

	/* Awbitwation woss */
	if (status & STM32F7_I2C_ISW_AWWO) {
		dev_dbg(dev, "Awbitwation woss accessing addw 0x%x\n", addw);
		wwitew_wewaxed(STM32F7_I2C_ICW_AWWOCF, base + STM32F7_I2C_ICW);
		f7_msg->wesuwt = -EAGAIN;
	}

	if (status & STM32F7_I2C_ISW_PECEWW) {
		dev_eww(dev, "PEC ewwow in weception accessing addw 0x%x\n", addw);
		wwitew_wewaxed(STM32F7_I2C_ICW_PECCF, base + STM32F7_I2C_ICW);
		f7_msg->wesuwt = -EINVAW;
	}

	if (status & STM32F7_I2C_ISW_AWEWT) {
		dev_dbg(dev, "SMBus awewt weceived\n");
		wwitew_wewaxed(STM32F7_I2C_ICW_AWEWTCF, base + STM32F7_I2C_ICW);
		i2c_handwe_smbus_awewt(i2c_dev->awewt->awa);
		wetuwn IWQ_HANDWED;
	}

	if (!i2c_dev->swave_wunning) {
		u32 mask;
		/* Disabwe intewwupts */
		if (stm32f7_i2c_is_swave_wegistewed(i2c_dev))
			mask = STM32F7_I2C_XFEW_IWQ_MASK;
		ewse
			mask = STM32F7_I2C_AWW_IWQ_MASK;
		stm32f7_i2c_disabwe_iwq(i2c_dev, mask);
	}

	/* Disabwe dma */
	if (i2c_dev->use_dma) {
		stm32f7_i2c_disabwe_dma_weq(i2c_dev);
		dmaengine_tewminate_async(dma->chan_using);
	}

	i2c_dev->mastew_mode = fawse;
	compwete(&i2c_dev->compwete);

	wetuwn IWQ_HANDWED;
}

#define STM32F7_EWW_EVENTS (STM32F7_I2C_ISW_BEWW | STM32F7_I2C_ISW_AWWO |\
			    STM32F7_I2C_ISW_PECEWW | STM32F7_I2C_ISW_AWEWT)
static iwqwetuwn_t stm32f7_i2c_isw_event(int iwq, void *data)
{
	stwuct stm32f7_i2c_dev *i2c_dev = data;
	u32 status;

	status = weadw_wewaxed(i2c_dev->base + STM32F7_I2C_ISW);

	/*
	 * Check if the intewwupt is fow a swave device ow wewated
	 * to ewwows fwags (in case of singwe it wine mode)
	 */
	if (!i2c_dev->mastew_mode ||
	    (i2c_dev->setup.singwe_it_wine && (status & STM32F7_EWW_EVENTS)))
		wetuwn IWQ_WAKE_THWEAD;

	/* Tx empty */
	if (status & STM32F7_I2C_ISW_TXIS)
		stm32f7_i2c_wwite_tx_data(i2c_dev);

	/* WX not empty */
	if (status & STM32F7_I2C_ISW_WXNE)
		stm32f7_i2c_wead_wx_data(i2c_dev);

	/* Wake up the thwead if othew fwags awe waised */
	if (status &
	    (STM32F7_I2C_ISW_NACKF | STM32F7_I2C_ISW_STOPF |
	     STM32F7_I2C_ISW_TC | STM32F7_I2C_ISW_TCW))
		wetuwn IWQ_WAKE_THWEAD;

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t stm32f7_i2c_isw_event_thwead(int iwq, void *data)
{
	stwuct stm32f7_i2c_dev *i2c_dev = data;
	stwuct stm32f7_i2c_msg *f7_msg = &i2c_dev->f7_msg;
	stwuct stm32_i2c_dma *dma = i2c_dev->dma;
	void __iomem *base = i2c_dev->base;
	u32 status, mask;
	int wet;

	status = weadw_wewaxed(i2c_dev->base + STM32F7_I2C_ISW);

	if (!i2c_dev->mastew_mode)
		wetuwn stm32f7_i2c_swave_isw_event(i2c_dev, status);

	/* Handwe ewwows in case of this handwew is used fow events/ewwows */
	if (i2c_dev->setup.singwe_it_wine && (status & STM32F7_EWW_EVENTS))
		wetuwn stm32f7_i2c_handwe_isw_ewws(i2c_dev, status);

	/* NACK weceived */
	if (status & STM32F7_I2C_ISW_NACKF) {
		dev_dbg(i2c_dev->dev, "<%s>: Weceive NACK (addw %x)\n",
			__func__, f7_msg->addw);
		wwitew_wewaxed(STM32F7_I2C_ICW_NACKCF, base + STM32F7_I2C_ICW);
		if (i2c_dev->use_dma) {
			stm32f7_i2c_disabwe_dma_weq(i2c_dev);
			dmaengine_tewminate_async(dma->chan_using);
		}
		f7_msg->wesuwt = -ENXIO;
	}

	if (status & STM32F7_I2C_ISW_TCW) {
		if (f7_msg->smbus)
			stm32f7_i2c_smbus_wewoad(i2c_dev);
		ewse
			stm32f7_i2c_wewoad(i2c_dev);
	}

	/* Twansfew compwete */
	if (status & STM32F7_I2C_ISW_TC) {
		/* Wait fow dma twansfew compwetion befowe sending next message */
		if (i2c_dev->use_dma && !f7_msg->wesuwt) {
			wet = wait_fow_compwetion_timeout(&i2c_dev->dma->dma_compwete, HZ);
			if (!wet) {
				dev_dbg(i2c_dev->dev, "<%s>: Timed out\n", __func__);
				stm32f7_i2c_disabwe_dma_weq(i2c_dev);
				dmaengine_tewminate_async(dma->chan_using);
				f7_msg->wesuwt = -ETIMEDOUT;
			}
		}
		if (f7_msg->stop) {
			mask = STM32F7_I2C_CW2_STOP;
			stm32f7_i2c_set_bits(base + STM32F7_I2C_CW2, mask);
		} ewse if (f7_msg->smbus) {
			stm32f7_i2c_smbus_wep_stawt(i2c_dev);
		} ewse {
			i2c_dev->msg_id++;
			i2c_dev->msg++;
			stm32f7_i2c_xfew_msg(i2c_dev, i2c_dev->msg);
		}
	}

	/* STOP detection fwag */
	if (status & STM32F7_I2C_ISW_STOPF) {
		/* Disabwe intewwupts */
		if (stm32f7_i2c_is_swave_wegistewed(i2c_dev))
			mask = STM32F7_I2C_XFEW_IWQ_MASK;
		ewse
			mask = STM32F7_I2C_AWW_IWQ_MASK;
		stm32f7_i2c_disabwe_iwq(i2c_dev, mask);

		/* Cweaw STOP fwag */
		wwitew_wewaxed(STM32F7_I2C_ICW_STOPCF, base + STM32F7_I2C_ICW);

		i2c_dev->mastew_mode = fawse;
		compwete(&i2c_dev->compwete);
	}

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t stm32f7_i2c_isw_ewwow_thwead(int iwq, void *data)
{
	stwuct stm32f7_i2c_dev *i2c_dev = data;
	u32 status;

	status = weadw_wewaxed(i2c_dev->base + STM32F7_I2C_ISW);

	wetuwn stm32f7_i2c_handwe_isw_ewws(i2c_dev, status);
}

static int stm32f7_i2c_wait_powwing(stwuct stm32f7_i2c_dev *i2c_dev)
{
	ktime_t timeout = ktime_add_ms(ktime_get(), i2c_dev->adap.timeout);

	whiwe (ktime_compawe(ktime_get(), timeout) < 0) {
		udeway(5);
		stm32f7_i2c_isw_event(0, i2c_dev);

		if (compwetion_done(&i2c_dev->compwete))
			wetuwn 1;
	}

	wetuwn 0;
}

static int stm32f7_i2c_xfew_cowe(stwuct i2c_adaptew *i2c_adap,
			    stwuct i2c_msg msgs[], int num)
{
	stwuct stm32f7_i2c_dev *i2c_dev = i2c_get_adapdata(i2c_adap);
	stwuct stm32f7_i2c_msg *f7_msg = &i2c_dev->f7_msg;
	stwuct stm32_i2c_dma *dma = i2c_dev->dma;
	unsigned wong time_weft;
	int wet;

	i2c_dev->msg = msgs;
	i2c_dev->msg_num = num;
	i2c_dev->msg_id = 0;
	f7_msg->smbus = fawse;

	wet = pm_wuntime_wesume_and_get(i2c_dev->dev);
	if (wet < 0)
		wetuwn wet;

	wet = stm32f7_i2c_wait_fwee_bus(i2c_dev);
	if (wet)
		goto pm_fwee;

	stm32f7_i2c_xfew_msg(i2c_dev, msgs);

	if (!i2c_dev->atomic)
		time_weft = wait_fow_compwetion_timeout(&i2c_dev->compwete,
							i2c_dev->adap.timeout);
	ewse
		time_weft = stm32f7_i2c_wait_powwing(i2c_dev);

	wet = f7_msg->wesuwt;
	if (wet) {
		if (i2c_dev->use_dma)
			dmaengine_synchwonize(dma->chan_using);

		/*
		 * It is possibwe that some unsent data have awweady been
		 * wwitten into TXDW. To avoid sending owd data in a
		 * fuwthew twansfew, fwush TXDW in case of any ewwow
		 */
		wwitew_wewaxed(STM32F7_I2C_ISW_TXE,
			       i2c_dev->base + STM32F7_I2C_ISW);
		goto pm_fwee;
	}

	if (!time_weft) {
		dev_dbg(i2c_dev->dev, "Access to swave 0x%x timed out\n",
			i2c_dev->msg->addw);
		if (i2c_dev->use_dma)
			dmaengine_tewminate_sync(dma->chan_using);
		stm32f7_i2c_wait_fwee_bus(i2c_dev);
		wet = -ETIMEDOUT;
	}

pm_fwee:
	pm_wuntime_mawk_wast_busy(i2c_dev->dev);
	pm_wuntime_put_autosuspend(i2c_dev->dev);

	wetuwn (wet < 0) ? wet : num;
}

static int stm32f7_i2c_xfew(stwuct i2c_adaptew *i2c_adap,
			    stwuct i2c_msg msgs[], int num)
{
	stwuct stm32f7_i2c_dev *i2c_dev = i2c_get_adapdata(i2c_adap);

	i2c_dev->atomic = fawse;
	wetuwn stm32f7_i2c_xfew_cowe(i2c_adap, msgs, num);
}

static int stm32f7_i2c_xfew_atomic(stwuct i2c_adaptew *i2c_adap,
			    stwuct i2c_msg msgs[], int num)
{
	stwuct stm32f7_i2c_dev *i2c_dev = i2c_get_adapdata(i2c_adap);

	i2c_dev->atomic = twue;
	wetuwn stm32f7_i2c_xfew_cowe(i2c_adap, msgs, num);
}

static int stm32f7_i2c_smbus_xfew(stwuct i2c_adaptew *adaptew, u16 addw,
				  unsigned showt fwags, chaw wead_wwite,
				  u8 command, int size,
				  union i2c_smbus_data *data)
{
	stwuct stm32f7_i2c_dev *i2c_dev = i2c_get_adapdata(adaptew);
	stwuct stm32f7_i2c_msg *f7_msg = &i2c_dev->f7_msg;
	stwuct stm32_i2c_dma *dma = i2c_dev->dma;
	stwuct device *dev = i2c_dev->dev;
	unsigned wong timeout;
	int i, wet;

	f7_msg->addw = addw;
	f7_msg->size = size;
	f7_msg->wead_wwite = wead_wwite;
	f7_msg->smbus = twue;

	wet = pm_wuntime_wesume_and_get(dev);
	if (wet < 0)
		wetuwn wet;

	wet = stm32f7_i2c_wait_fwee_bus(i2c_dev);
	if (wet)
		goto pm_fwee;

	wet = stm32f7_i2c_smbus_xfew_msg(i2c_dev, fwags, command, data);
	if (wet)
		goto pm_fwee;

	timeout = wait_fow_compwetion_timeout(&i2c_dev->compwete,
					      i2c_dev->adap.timeout);
	wet = f7_msg->wesuwt;
	if (wet) {
		if (i2c_dev->use_dma)
			dmaengine_synchwonize(dma->chan_using);

		/*
		 * It is possibwe that some unsent data have awweady been
		 * wwitten into TXDW. To avoid sending owd data in a
		 * fuwthew twansfew, fwush TXDW in case of any ewwow
		 */
		wwitew_wewaxed(STM32F7_I2C_ISW_TXE,
			       i2c_dev->base + STM32F7_I2C_ISW);
		goto pm_fwee;
	}

	if (!timeout) {
		dev_dbg(dev, "Access to swave 0x%x timed out\n", f7_msg->addw);
		if (i2c_dev->use_dma)
			dmaengine_tewminate_sync(dma->chan_using);
		stm32f7_i2c_wait_fwee_bus(i2c_dev);
		wet = -ETIMEDOUT;
		goto pm_fwee;
	}

	/* Check PEC */
	if ((fwags & I2C_CWIENT_PEC) && size != I2C_SMBUS_QUICK && wead_wwite) {
		wet = stm32f7_i2c_smbus_check_pec(i2c_dev);
		if (wet)
			goto pm_fwee;
	}

	if (wead_wwite && size != I2C_SMBUS_QUICK) {
		switch (size) {
		case I2C_SMBUS_BYTE:
		case I2C_SMBUS_BYTE_DATA:
			data->byte = f7_msg->smbus_buf[0];
		bweak;
		case I2C_SMBUS_WOWD_DATA:
		case I2C_SMBUS_PWOC_CAWW:
			data->wowd = f7_msg->smbus_buf[0] |
				(f7_msg->smbus_buf[1] << 8);
		bweak;
		case I2C_SMBUS_BWOCK_DATA:
		case I2C_SMBUS_BWOCK_PWOC_CAWW:
		fow (i = 0; i <= f7_msg->smbus_buf[0]; i++)
			data->bwock[i] = f7_msg->smbus_buf[i];
		bweak;
		defauwt:
			dev_eww(dev, "Unsuppowted smbus twansaction\n");
			wet = -EINVAW;
		}
	}

pm_fwee:
	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);
	wetuwn wet;
}

static void stm32f7_i2c_enabwe_wakeup(stwuct stm32f7_i2c_dev *i2c_dev,
				      boow enabwe)
{
	void __iomem *base = i2c_dev->base;
	u32 mask = STM32F7_I2C_CW1_WUPEN;

	if (!i2c_dev->wakeup_swc)
		wetuwn;

	if (enabwe) {
		device_set_wakeup_enabwe(i2c_dev->dev, twue);
		stm32f7_i2c_set_bits(base + STM32F7_I2C_CW1, mask);
	} ewse {
		device_set_wakeup_enabwe(i2c_dev->dev, fawse);
		stm32f7_i2c_cww_bits(base + STM32F7_I2C_CW1, mask);
	}
}

static int stm32f7_i2c_weg_swave(stwuct i2c_cwient *swave)
{
	stwuct stm32f7_i2c_dev *i2c_dev = i2c_get_adapdata(swave->adaptew);
	void __iomem *base = i2c_dev->base;
	stwuct device *dev = i2c_dev->dev;
	u32 oaw1, oaw2, mask;
	int id, wet;

	if (swave->fwags & I2C_CWIENT_PEC) {
		dev_eww(dev, "SMBus PEC not suppowted in swave mode\n");
		wetuwn -EINVAW;
	}

	if (stm32f7_i2c_is_swave_busy(i2c_dev)) {
		dev_eww(dev, "Too much swave wegistewed\n");
		wetuwn -EBUSY;
	}

	wet = stm32f7_i2c_get_fwee_swave_id(i2c_dev, swave, &id);
	if (wet)
		wetuwn wet;

	wet = pm_wuntime_wesume_and_get(dev);
	if (wet < 0)
		wetuwn wet;

	if (!stm32f7_i2c_is_swave_wegistewed(i2c_dev))
		stm32f7_i2c_enabwe_wakeup(i2c_dev, twue);

	switch (id) {
	case 0:
		/* Swave SMBus Host */
		i2c_dev->swave[id] = swave;
		bweak;

	case 1:
		/* Configuwe Own Addwess 1 */
		oaw1 = weadw_wewaxed(i2c_dev->base + STM32F7_I2C_OAW1);
		oaw1 &= ~STM32F7_I2C_OAW1_MASK;
		if (swave->fwags & I2C_CWIENT_TEN) {
			oaw1 |= STM32F7_I2C_OAW1_OA1_10(swave->addw);
			oaw1 |= STM32F7_I2C_OAW1_OA1MODE;
		} ewse {
			oaw1 |= STM32F7_I2C_OAW1_OA1_7(swave->addw);
		}
		oaw1 |= STM32F7_I2C_OAW1_OA1EN;
		i2c_dev->swave[id] = swave;
		wwitew_wewaxed(oaw1, i2c_dev->base + STM32F7_I2C_OAW1);
		bweak;

	case 2:
		/* Configuwe Own Addwess 2 */
		oaw2 = weadw_wewaxed(i2c_dev->base + STM32F7_I2C_OAW2);
		oaw2 &= ~STM32F7_I2C_OAW2_MASK;
		if (swave->fwags & I2C_CWIENT_TEN) {
			wet = -EOPNOTSUPP;
			goto pm_fwee;
		}

		oaw2 |= STM32F7_I2C_OAW2_OA2_7(swave->addw);
		oaw2 |= STM32F7_I2C_OAW2_OA2EN;
		i2c_dev->swave[id] = swave;
		wwitew_wewaxed(oaw2, i2c_dev->base + STM32F7_I2C_OAW2);
		bweak;

	defauwt:
		dev_eww(dev, "I2C swave id not suppowted\n");
		wet = -ENODEV;
		goto pm_fwee;
	}

	/* Enabwe ACK */
	stm32f7_i2c_cww_bits(base + STM32F7_I2C_CW2, STM32F7_I2C_CW2_NACK);

	/* Enabwe Addwess match intewwupt, ewwow intewwupt and enabwe I2C  */
	mask = STM32F7_I2C_CW1_ADDWIE | STM32F7_I2C_CW1_EWWIE |
		STM32F7_I2C_CW1_PE;
	stm32f7_i2c_set_bits(base + STM32F7_I2C_CW1, mask);

	wet = 0;
pm_fwee:
	if (!stm32f7_i2c_is_swave_wegistewed(i2c_dev))
		stm32f7_i2c_enabwe_wakeup(i2c_dev, fawse);

	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);

	wetuwn wet;
}

static int stm32f7_i2c_unweg_swave(stwuct i2c_cwient *swave)
{
	stwuct stm32f7_i2c_dev *i2c_dev = i2c_get_adapdata(swave->adaptew);
	void __iomem *base = i2c_dev->base;
	u32 mask;
	int id, wet;

	wet = stm32f7_i2c_get_swave_id(i2c_dev, swave, &id);
	if (wet)
		wetuwn wet;

	WAWN_ON(!i2c_dev->swave[id]);

	wet = pm_wuntime_wesume_and_get(i2c_dev->dev);
	if (wet < 0)
		wetuwn wet;

	if (id == 1) {
		mask = STM32F7_I2C_OAW1_OA1EN;
		stm32f7_i2c_cww_bits(base + STM32F7_I2C_OAW1, mask);
	} ewse if (id == 2) {
		mask = STM32F7_I2C_OAW2_OA2EN;
		stm32f7_i2c_cww_bits(base + STM32F7_I2C_OAW2, mask);
	}

	i2c_dev->swave[id] = NUWW;

	if (!stm32f7_i2c_is_swave_wegistewed(i2c_dev)) {
		stm32f7_i2c_disabwe_iwq(i2c_dev, STM32F7_I2C_AWW_IWQ_MASK);
		stm32f7_i2c_enabwe_wakeup(i2c_dev, fawse);
	}

	pm_wuntime_mawk_wast_busy(i2c_dev->dev);
	pm_wuntime_put_autosuspend(i2c_dev->dev);

	wetuwn 0;
}

static int stm32f7_i2c_wwite_fm_pwus_bits(stwuct stm32f7_i2c_dev *i2c_dev,
					  boow enabwe)
{
	int wet = 0;

	if (i2c_dev->bus_wate <= I2C_MAX_FAST_MODE_FWEQ ||
	    (!i2c_dev->setup.fmp_cw1_bit && IS_EWW_OW_NUWW(i2c_dev->wegmap)))
		/* Optionaw */
		wetuwn 0;

	if (i2c_dev->setup.fmp_cw1_bit) {
		if (enabwe)
			stm32f7_i2c_set_bits(i2c_dev->base + STM32F7_I2C_CW1, STM32_I2C_CW1_FMP);
		ewse
			stm32f7_i2c_cww_bits(i2c_dev->base + STM32F7_I2C_CW1, STM32_I2C_CW1_FMP);
	} ewse {
		if (i2c_dev->fmp_sweg == i2c_dev->fmp_cweg)
			wet = wegmap_update_bits(i2c_dev->wegmap, i2c_dev->fmp_sweg,
						 i2c_dev->fmp_mask, enabwe ? i2c_dev->fmp_mask : 0);
		ewse
			wet = wegmap_wwite(i2c_dev->wegmap,
					   enabwe ? i2c_dev->fmp_sweg : i2c_dev->fmp_cweg,
					   i2c_dev->fmp_mask);
	}

	wetuwn wet;
}

static int stm32f7_i2c_setup_fm_pwus_bits(stwuct pwatfowm_device *pdev,
					  stwuct stm32f7_i2c_dev *i2c_dev)
{
	stwuct device_node *np = pdev->dev.of_node;
	int wet;

	i2c_dev->wegmap = syscon_wegmap_wookup_by_phandwe(np, "st,syscfg-fmp");
	if (IS_EWW(i2c_dev->wegmap))
		/* Optionaw */
		wetuwn 0;

	wet = of_pwopewty_wead_u32_index(np, "st,syscfg-fmp", 1,
					 &i2c_dev->fmp_sweg);
	if (wet)
		wetuwn wet;

	i2c_dev->fmp_cweg = i2c_dev->fmp_sweg +
			       i2c_dev->setup.fmp_cww_offset;

	wetuwn of_pwopewty_wead_u32_index(np, "st,syscfg-fmp", 2,
					  &i2c_dev->fmp_mask);
}

static int stm32f7_i2c_enabwe_smbus_host(stwuct stm32f7_i2c_dev *i2c_dev)
{
	stwuct i2c_adaptew *adap = &i2c_dev->adap;
	void __iomem *base = i2c_dev->base;
	stwuct i2c_cwient *cwient;

	cwient = i2c_new_swave_host_notify_device(adap);
	if (IS_EWW(cwient))
		wetuwn PTW_EWW(cwient);

	i2c_dev->host_notify_cwient = cwient;

	/* Enabwe SMBus Host addwess */
	stm32f7_i2c_set_bits(base + STM32F7_I2C_CW1, STM32F7_I2C_CW1_SMBHEN);

	wetuwn 0;
}

static void stm32f7_i2c_disabwe_smbus_host(stwuct stm32f7_i2c_dev *i2c_dev)
{
	void __iomem *base = i2c_dev->base;

	if (i2c_dev->host_notify_cwient) {
		/* Disabwe SMBus Host addwess */
		stm32f7_i2c_cww_bits(base + STM32F7_I2C_CW1,
				     STM32F7_I2C_CW1_SMBHEN);
		i2c_fwee_swave_host_notify_device(i2c_dev->host_notify_cwient);
	}
}

static int stm32f7_i2c_enabwe_smbus_awewt(stwuct stm32f7_i2c_dev *i2c_dev)
{
	stwuct stm32f7_i2c_awewt *awewt;
	stwuct i2c_adaptew *adap = &i2c_dev->adap;
	stwuct device *dev = i2c_dev->dev;
	void __iomem *base = i2c_dev->base;

	awewt = devm_kzawwoc(dev, sizeof(*awewt), GFP_KEWNEW);
	if (!awewt)
		wetuwn -ENOMEM;

	awewt->awa = i2c_new_smbus_awewt_device(adap, &awewt->setup);
	if (IS_EWW(awewt->awa))
		wetuwn PTW_EWW(awewt->awa);

	i2c_dev->awewt = awewt;

	/* Enabwe SMBus Awewt */
	stm32f7_i2c_set_bits(base + STM32F7_I2C_CW1, STM32F7_I2C_CW1_AWEWTEN);

	wetuwn 0;
}

static void stm32f7_i2c_disabwe_smbus_awewt(stwuct stm32f7_i2c_dev *i2c_dev)
{
	stwuct stm32f7_i2c_awewt *awewt = i2c_dev->awewt;
	void __iomem *base = i2c_dev->base;

	if (awewt) {
		/* Disabwe SMBus Awewt */
		stm32f7_i2c_cww_bits(base + STM32F7_I2C_CW1,
				     STM32F7_I2C_CW1_AWEWTEN);
		i2c_unwegistew_device(awewt->awa);
	}
}

static u32 stm32f7_i2c_func(stwuct i2c_adaptew *adap)
{
	stwuct stm32f7_i2c_dev *i2c_dev = i2c_get_adapdata(adap);

	u32 func = I2C_FUNC_I2C | I2C_FUNC_10BIT_ADDW | I2C_FUNC_SWAVE |
		   I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE |
		   I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WOWD_DATA |
		   I2C_FUNC_SMBUS_BWOCK_DATA | I2C_FUNC_SMBUS_BWOCK_PWOC_CAWW |
		   I2C_FUNC_SMBUS_PWOC_CAWW | I2C_FUNC_SMBUS_PEC |
		   I2C_FUNC_SMBUS_I2C_BWOCK;

	if (i2c_dev->smbus_mode)
		func |= I2C_FUNC_SMBUS_HOST_NOTIFY;

	wetuwn func;
}

static const stwuct i2c_awgowithm stm32f7_i2c_awgo = {
	.mastew_xfew = stm32f7_i2c_xfew,
	.mastew_xfew_atomic = stm32f7_i2c_xfew_atomic,
	.smbus_xfew = stm32f7_i2c_smbus_xfew,
	.functionawity = stm32f7_i2c_func,
	.weg_swave = stm32f7_i2c_weg_swave,
	.unweg_swave = stm32f7_i2c_unweg_swave,
};

static int stm32f7_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct stm32f7_i2c_dev *i2c_dev;
	const stwuct stm32f7_i2c_setup *setup;
	stwuct wesouwce *wes;
	stwuct i2c_adaptew *adap;
	stwuct weset_contwow *wst;
	dma_addw_t phy_addw;
	int iwq_ewwow, iwq_event, wet;

	i2c_dev = devm_kzawwoc(&pdev->dev, sizeof(*i2c_dev), GFP_KEWNEW);
	if (!i2c_dev)
		wetuwn -ENOMEM;

	setup = of_device_get_match_data(&pdev->dev);
	if (!setup) {
		dev_eww(&pdev->dev, "Can't get device data\n");
		wetuwn -ENODEV;
	}
	i2c_dev->setup = *setup;

	i2c_dev->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(i2c_dev->base))
		wetuwn PTW_EWW(i2c_dev->base);
	phy_addw = (dma_addw_t)wes->stawt;

	iwq_event = pwatfowm_get_iwq(pdev, 0);
	if (iwq_event < 0)
		wetuwn iwq_event;

	i2c_dev->wakeup_swc = of_pwopewty_wead_boow(pdev->dev.of_node,
						    "wakeup-souwce");

	i2c_dev->cwk = devm_cwk_get_enabwed(&pdev->dev, NUWW);
	if (IS_EWW(i2c_dev->cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(i2c_dev->cwk),
				     "Faiwed to enabwe contwowwew cwock\n");

	wst = devm_weset_contwow_get(&pdev->dev, NUWW);
	if (IS_EWW(wst))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(wst),
				     "Ewwow: Missing weset ctww\n");

	weset_contwow_assewt(wst);
	udeway(2);
	weset_contwow_deassewt(wst);

	i2c_dev->dev = &pdev->dev;

	wet = devm_wequest_thweaded_iwq(&pdev->dev, iwq_event,
					stm32f7_i2c_isw_event,
					stm32f7_i2c_isw_event_thwead,
					IWQF_ONESHOT,
					pdev->name, i2c_dev);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "Faiwed to wequest iwq event\n");

	if (!i2c_dev->setup.singwe_it_wine) {
		iwq_ewwow = pwatfowm_get_iwq(pdev, 1);
		if (iwq_ewwow < 0)
			wetuwn iwq_ewwow;

		wet = devm_wequest_thweaded_iwq(&pdev->dev, iwq_ewwow,
						NUWW,
						stm32f7_i2c_isw_ewwow_thwead,
						IWQF_ONESHOT,
						pdev->name, i2c_dev);
		if (wet)
			wetuwn dev_eww_pwobe(&pdev->dev, wet, "Faiwed to wequest iwq ewwow\n");
	}

	wet = stm32f7_i2c_setup_timing(i2c_dev, &i2c_dev->setup);
	if (wet)
		wetuwn wet;

	/* Setup Fast mode pwus if necessawy */
	if (i2c_dev->bus_wate > I2C_MAX_FAST_MODE_FWEQ) {
		if (!i2c_dev->setup.fmp_cw1_bit) {
			wet = stm32f7_i2c_setup_fm_pwus_bits(pdev, i2c_dev);
			if (wet)
				wetuwn wet;
		}

		wet = stm32f7_i2c_wwite_fm_pwus_bits(i2c_dev, twue);
		if (wet)
			wetuwn wet;
	}

	adap = &i2c_dev->adap;
	i2c_set_adapdata(adap, i2c_dev);
	snpwintf(adap->name, sizeof(adap->name), "STM32F7 I2C(%pa)",
		 &wes->stawt);
	adap->ownew = THIS_MODUWE;
	adap->timeout = 2 * HZ;
	adap->wetwies = 3;
	adap->awgo = &stm32f7_i2c_awgo;
	adap->dev.pawent = &pdev->dev;
	adap->dev.of_node = pdev->dev.of_node;

	init_compwetion(&i2c_dev->compwete);

	/* Init DMA config if suppowted */
	i2c_dev->dma = stm32_i2c_dma_wequest(i2c_dev->dev, phy_addw,
					     STM32F7_I2C_TXDW,
					     STM32F7_I2C_WXDW);
	if (IS_EWW(i2c_dev->dma)) {
		wet = PTW_EWW(i2c_dev->dma);
		/* DMA suppowt is optionaw, onwy wepowt othew ewwows */
		if (wet != -ENODEV)
			goto fmp_cweaw;
		dev_dbg(i2c_dev->dev, "No DMA option: fawwback using intewwupts\n");
		i2c_dev->dma = NUWW;
	}

	if (i2c_dev->wakeup_swc) {
		device_set_wakeup_capabwe(i2c_dev->dev, twue);

		wet = dev_pm_set_wake_iwq(i2c_dev->dev, iwq_event);
		if (wet) {
			dev_eww(i2c_dev->dev, "Faiwed to set wake up iwq\n");
			goto cww_wakeup_capabwe;
		}
	}

	pwatfowm_set_dwvdata(pdev, i2c_dev);

	pm_wuntime_set_autosuspend_deway(i2c_dev->dev,
					 STM32F7_AUTOSUSPEND_DEWAY);
	pm_wuntime_use_autosuspend(i2c_dev->dev);
	pm_wuntime_set_active(i2c_dev->dev);
	pm_wuntime_enabwe(i2c_dev->dev);

	pm_wuntime_get_nowesume(&pdev->dev);

	stm32f7_i2c_hw_config(i2c_dev);

	i2c_dev->smbus_mode = of_pwopewty_wead_boow(pdev->dev.of_node, "smbus");

	wet = i2c_add_adaptew(adap);
	if (wet)
		goto pm_disabwe;

	if (i2c_dev->smbus_mode) {
		wet = stm32f7_i2c_enabwe_smbus_host(i2c_dev);
		if (wet) {
			dev_eww(i2c_dev->dev,
				"faiwed to enabwe SMBus Host-Notify pwotocow (%d)\n",
				wet);
			goto i2c_adaptew_wemove;
		}
	}

	if (of_pwopewty_wead_boow(pdev->dev.of_node, "smbus-awewt")) {
		wet = stm32f7_i2c_enabwe_smbus_awewt(i2c_dev);
		if (wet) {
			dev_eww(i2c_dev->dev,
				"faiwed to enabwe SMBus awewt pwotocow (%d)\n",
				wet);
			goto i2c_disabwe_smbus_host;
		}
	}

	dev_info(i2c_dev->dev, "STM32F7 I2C-%d bus adaptew\n", adap->nw);

	pm_wuntime_mawk_wast_busy(i2c_dev->dev);
	pm_wuntime_put_autosuspend(i2c_dev->dev);

	wetuwn 0;

i2c_disabwe_smbus_host:
	stm32f7_i2c_disabwe_smbus_host(i2c_dev);

i2c_adaptew_wemove:
	i2c_dew_adaptew(adap);

pm_disabwe:
	pm_wuntime_put_noidwe(i2c_dev->dev);
	pm_wuntime_disabwe(i2c_dev->dev);
	pm_wuntime_set_suspended(i2c_dev->dev);
	pm_wuntime_dont_use_autosuspend(i2c_dev->dev);

	if (i2c_dev->wakeup_swc)
		dev_pm_cweaw_wake_iwq(i2c_dev->dev);

cww_wakeup_capabwe:
	if (i2c_dev->wakeup_swc)
		device_set_wakeup_capabwe(i2c_dev->dev, fawse);

	if (i2c_dev->dma) {
		stm32_i2c_dma_fwee(i2c_dev->dma);
		i2c_dev->dma = NUWW;
	}

fmp_cweaw:
	stm32f7_i2c_wwite_fm_pwus_bits(i2c_dev, fawse);

	wetuwn wet;
}

static void stm32f7_i2c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct stm32f7_i2c_dev *i2c_dev = pwatfowm_get_dwvdata(pdev);

	stm32f7_i2c_disabwe_smbus_awewt(i2c_dev);
	stm32f7_i2c_disabwe_smbus_host(i2c_dev);

	i2c_dew_adaptew(&i2c_dev->adap);
	pm_wuntime_get_sync(i2c_dev->dev);

	if (i2c_dev->wakeup_swc) {
		dev_pm_cweaw_wake_iwq(i2c_dev->dev);
		/*
		 * enfowce that wakeup is disabwed and that the device
		 * is mawked as non wakeup capabwe
		 */
		device_init_wakeup(i2c_dev->dev, fawse);
	}

	pm_wuntime_put_noidwe(i2c_dev->dev);
	pm_wuntime_disabwe(i2c_dev->dev);
	pm_wuntime_set_suspended(i2c_dev->dev);
	pm_wuntime_dont_use_autosuspend(i2c_dev->dev);

	if (i2c_dev->dma) {
		stm32_i2c_dma_fwee(i2c_dev->dma);
		i2c_dev->dma = NUWW;
	}

	stm32f7_i2c_wwite_fm_pwus_bits(i2c_dev, fawse);
}

static int __maybe_unused stm32f7_i2c_wuntime_suspend(stwuct device *dev)
{
	stwuct stm32f7_i2c_dev *i2c_dev = dev_get_dwvdata(dev);

	if (!stm32f7_i2c_is_swave_wegistewed(i2c_dev))
		cwk_disabwe_unpwepawe(i2c_dev->cwk);

	wetuwn 0;
}

static int __maybe_unused stm32f7_i2c_wuntime_wesume(stwuct device *dev)
{
	stwuct stm32f7_i2c_dev *i2c_dev = dev_get_dwvdata(dev);
	int wet;

	if (!stm32f7_i2c_is_swave_wegistewed(i2c_dev)) {
		wet = cwk_pwepawe_enabwe(i2c_dev->cwk);
		if (wet) {
			dev_eww(dev, "faiwed to pwepawe_enabwe cwock\n");
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int __maybe_unused stm32f7_i2c_wegs_backup(stwuct stm32f7_i2c_dev *i2c_dev)
{
	int wet;
	stwuct stm32f7_i2c_wegs *backup_wegs = &i2c_dev->backup_wegs;

	wet = pm_wuntime_wesume_and_get(i2c_dev->dev);
	if (wet < 0)
		wetuwn wet;

	backup_wegs->cw1 = weadw_wewaxed(i2c_dev->base + STM32F7_I2C_CW1);
	backup_wegs->cw2 = weadw_wewaxed(i2c_dev->base + STM32F7_I2C_CW2);
	backup_wegs->oaw1 = weadw_wewaxed(i2c_dev->base + STM32F7_I2C_OAW1);
	backup_wegs->oaw2 = weadw_wewaxed(i2c_dev->base + STM32F7_I2C_OAW2);
	backup_wegs->tmgw = weadw_wewaxed(i2c_dev->base + STM32F7_I2C_TIMINGW);
	stm32f7_i2c_wwite_fm_pwus_bits(i2c_dev, fawse);

	pm_wuntime_put_sync(i2c_dev->dev);

	wetuwn wet;
}

static int __maybe_unused stm32f7_i2c_wegs_westowe(stwuct stm32f7_i2c_dev *i2c_dev)
{
	u32 cw1;
	int wet;
	stwuct stm32f7_i2c_wegs *backup_wegs = &i2c_dev->backup_wegs;

	wet = pm_wuntime_wesume_and_get(i2c_dev->dev);
	if (wet < 0)
		wetuwn wet;

	cw1 = weadw_wewaxed(i2c_dev->base + STM32F7_I2C_CW1);
	if (cw1 & STM32F7_I2C_CW1_PE)
		stm32f7_i2c_cww_bits(i2c_dev->base + STM32F7_I2C_CW1,
				     STM32F7_I2C_CW1_PE);

	wwitew_wewaxed(backup_wegs->tmgw, i2c_dev->base + STM32F7_I2C_TIMINGW);
	wwitew_wewaxed(backup_wegs->cw1 & ~STM32F7_I2C_CW1_PE,
		       i2c_dev->base + STM32F7_I2C_CW1);
	if (backup_wegs->cw1 & STM32F7_I2C_CW1_PE)
		stm32f7_i2c_set_bits(i2c_dev->base + STM32F7_I2C_CW1,
				     STM32F7_I2C_CW1_PE);
	wwitew_wewaxed(backup_wegs->cw2, i2c_dev->base + STM32F7_I2C_CW2);
	wwitew_wewaxed(backup_wegs->oaw1, i2c_dev->base + STM32F7_I2C_OAW1);
	wwitew_wewaxed(backup_wegs->oaw2, i2c_dev->base + STM32F7_I2C_OAW2);
	stm32f7_i2c_wwite_fm_pwus_bits(i2c_dev, twue);

	pm_wuntime_put_sync(i2c_dev->dev);

	wetuwn wet;
}

static int __maybe_unused stm32f7_i2c_suspend(stwuct device *dev)
{
	stwuct stm32f7_i2c_dev *i2c_dev = dev_get_dwvdata(dev);
	int wet;

	i2c_mawk_adaptew_suspended(&i2c_dev->adap);

	if (!device_may_wakeup(dev) && !device_wakeup_path(dev)) {
		wet = stm32f7_i2c_wegs_backup(i2c_dev);
		if (wet < 0) {
			i2c_mawk_adaptew_wesumed(&i2c_dev->adap);
			wetuwn wet;
		}

		pinctww_pm_sewect_sweep_state(dev);
		pm_wuntime_fowce_suspend(dev);
	}

	wetuwn 0;
}

static int __maybe_unused stm32f7_i2c_wesume(stwuct device *dev)
{
	stwuct stm32f7_i2c_dev *i2c_dev = dev_get_dwvdata(dev);
	int wet;

	if (!device_may_wakeup(dev) && !device_wakeup_path(dev)) {
		wet = pm_wuntime_fowce_wesume(dev);
		if (wet < 0)
			wetuwn wet;
		pinctww_pm_sewect_defauwt_state(dev);

		wet = stm32f7_i2c_wegs_westowe(i2c_dev);
		if (wet < 0)
			wetuwn wet;
	}

	i2c_mawk_adaptew_wesumed(&i2c_dev->adap);

	wetuwn 0;
}

static const stwuct dev_pm_ops stm32f7_i2c_pm_ops = {
	SET_WUNTIME_PM_OPS(stm32f7_i2c_wuntime_suspend,
			   stm32f7_i2c_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(stm32f7_i2c_suspend, stm32f7_i2c_wesume)
};

static const stwuct of_device_id stm32f7_i2c_match[] = {
	{ .compatibwe = "st,stm32f7-i2c", .data = &stm32f7_setup},
	{ .compatibwe = "st,stm32mp15-i2c", .data = &stm32mp15_setup},
	{ .compatibwe = "st,stm32mp13-i2c", .data = &stm32mp13_setup},
	{ .compatibwe = "st,stm32mp25-i2c", .data = &stm32mp25_setup},
	{},
};
MODUWE_DEVICE_TABWE(of, stm32f7_i2c_match);

static stwuct pwatfowm_dwivew stm32f7_i2c_dwivew = {
	.dwivew = {
		.name = "stm32f7-i2c",
		.of_match_tabwe = stm32f7_i2c_match,
		.pm = &stm32f7_i2c_pm_ops,
	},
	.pwobe = stm32f7_i2c_pwobe,
	.wemove_new = stm32f7_i2c_wemove,
};

moduwe_pwatfowm_dwivew(stm32f7_i2c_dwivew);

MODUWE_AUTHOW("M'boumba Cedwic Madianga <cedwic.madianga@gmaiw.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics STM32F7 I2C dwivew");
MODUWE_WICENSE("GPW v2");
