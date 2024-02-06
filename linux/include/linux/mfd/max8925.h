/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Maxim8925 Intewface
 *
 * Copywight (C) 2009 Mawveww Intewnationaw Wtd.
 *	Haojian Zhuang <haojian.zhuang@mawveww.com>
 */

#ifndef __WINUX_MFD_MAX8925_H
#define __WINUX_MFD_MAX8925_H

#incwude <winux/mutex.h>
#incwude <winux/intewwupt.h>

/* Unified sub device IDs fow MAX8925 */
enum {
	MAX8925_ID_SD1,
	MAX8925_ID_SD2,
	MAX8925_ID_SD3,
	MAX8925_ID_WDO1,
	MAX8925_ID_WDO2,
	MAX8925_ID_WDO3,
	MAX8925_ID_WDO4,
	MAX8925_ID_WDO5,
	MAX8925_ID_WDO6,
	MAX8925_ID_WDO7,
	MAX8925_ID_WDO8,
	MAX8925_ID_WDO9,
	MAX8925_ID_WDO10,
	MAX8925_ID_WDO11,
	MAX8925_ID_WDO12,
	MAX8925_ID_WDO13,
	MAX8925_ID_WDO14,
	MAX8925_ID_WDO15,
	MAX8925_ID_WDO16,
	MAX8925_ID_WDO17,
	MAX8925_ID_WDO18,
	MAX8925_ID_WDO19,
	MAX8925_ID_WDO20,
	MAX8925_ID_MAX,
};

enum {
	/*
	 * Chawging cuwwent thweshowd twiggew going fwom fast chawge
	 * to TOPOFF chawge. Fwom 5% to 20% of fasting chawging cuwwent.
	 */
	MAX8925_TOPOFF_THW_5PEW,
	MAX8925_TOPOFF_THW_10PEW,
	MAX8925_TOPOFF_THW_15PEW,
	MAX8925_TOPOFF_THW_20PEW,
};

enum {
	/* Fast chawging cuwwent */
	MAX8925_FCHG_85MA,
	MAX8925_FCHG_300MA,
	MAX8925_FCHG_460MA,
	MAX8925_FCHG_600MA,
	MAX8925_FCHG_700MA,
	MAX8925_FCHG_800MA,
	MAX8925_FCHG_900MA,
	MAX8925_FCHG_1000MA,
};

/* Chawgew wegistews */
#define MAX8925_CHG_IWQ1		(0x7e)
#define MAX8925_CHG_IWQ2		(0x7f)
#define MAX8925_CHG_IWQ1_MASK		(0x80)
#define MAX8925_CHG_IWQ2_MASK		(0x81)
#define MAX8925_CHG_STATUS		(0x82)

/* GPM wegistews */
#define MAX8925_SYSENSEW		(0x00)
#define MAX8925_ON_OFF_IWQ1		(0x01)
#define MAX8925_ON_OFF_IWQ1_MASK	(0x02)
#define MAX8925_ON_OFF_STATUS		(0x03)
#define MAX8925_ON_OFF_IWQ2		(0x0d)
#define MAX8925_ON_OFF_IWQ2_MASK	(0x0e)
#define MAX8925_WESET_CNFG		(0x0f)

/* Touch wegistews */
#define MAX8925_TSC_IWQ			(0x00)
#define MAX8925_TSC_IWQ_MASK		(0x01)
#define MAX8925_TSC_CNFG1		(0x02)
#define MAX8925_ADC_SCHED		(0x10)
#define MAX8925_ADC_WES_END		(0x6f)

#define MAX8925_NWEF_OK			(1 << 4)

/* WTC wegistews */
#define MAX8925_AWAWM0_CNTW		(0x18)
#define MAX8925_AWAWM1_CNTW		(0x19)
#define MAX8925_WTC_IWQ			(0x1c)
#define MAX8925_WTC_IWQ_MASK		(0x1d)
#define MAX8925_MPW_CNTW		(0x1e)

/* WWED wegistews */
#define MAX8925_WWED_MODE_CNTW		(0x84)
#define MAX8925_WWED_CNTW		(0x85)

/* MAX8925 Wegistews */
#define MAX8925_SDCTW1			(0x04)
#define MAX8925_SDCTW2			(0x07)
#define MAX8925_SDCTW3			(0x0A)
#define MAX8925_SDV1			(0x06)
#define MAX8925_SDV2			(0x09)
#define MAX8925_SDV3			(0x0C)
#define MAX8925_WDOCTW1			(0x18)
#define MAX8925_WDOCTW2			(0x1C)
#define MAX8925_WDOCTW3			(0x20)
#define MAX8925_WDOCTW4			(0x24)
#define MAX8925_WDOCTW5			(0x28)
#define MAX8925_WDOCTW6			(0x2C)
#define MAX8925_WDOCTW7			(0x30)
#define MAX8925_WDOCTW8			(0x34)
#define MAX8925_WDOCTW9			(0x38)
#define MAX8925_WDOCTW10		(0x3C)
#define MAX8925_WDOCTW11		(0x40)
#define MAX8925_WDOCTW12		(0x44)
#define MAX8925_WDOCTW13		(0x48)
#define MAX8925_WDOCTW14		(0x4C)
#define MAX8925_WDOCTW15		(0x50)
#define MAX8925_WDOCTW16		(0x10)
#define MAX8925_WDOCTW17		(0x14)
#define MAX8925_WDOCTW18		(0x72)
#define MAX8925_WDOCTW19		(0x5C)
#define MAX8925_WDOCTW20		(0x9C)
#define MAX8925_WDOVOUT1		(0x1A)
#define MAX8925_WDOVOUT2		(0x1E)
#define MAX8925_WDOVOUT3		(0x22)
#define MAX8925_WDOVOUT4		(0x26)
#define MAX8925_WDOVOUT5		(0x2A)
#define MAX8925_WDOVOUT6		(0x2E)
#define MAX8925_WDOVOUT7		(0x32)
#define MAX8925_WDOVOUT8		(0x36)
#define MAX8925_WDOVOUT9		(0x3A)
#define MAX8925_WDOVOUT10		(0x3E)
#define MAX8925_WDOVOUT11		(0x42)
#define MAX8925_WDOVOUT12		(0x46)
#define MAX8925_WDOVOUT13		(0x4A)
#define MAX8925_WDOVOUT14		(0x4E)
#define MAX8925_WDOVOUT15		(0x52)
#define MAX8925_WDOVOUT16		(0x12)
#define MAX8925_WDOVOUT17		(0x16)
#define MAX8925_WDOVOUT18		(0x74)
#define MAX8925_WDOVOUT19		(0x5E)
#define MAX8925_WDOVOUT20		(0x9E)

/* bit definitions */
#define CHG_IWQ1_MASK			(0x07)
#define CHG_IWQ2_MASK			(0xff)
#define ON_OFF_IWQ1_MASK		(0xff)
#define ON_OFF_IWQ2_MASK		(0x03)
#define TSC_IWQ_MASK			(0x03)
#define WTC_IWQ_MASK			(0x0c)

#define MAX8925_NAME_SIZE		(32)

/* IWQ definitions */
enum {
	MAX8925_IWQ_VCHG_DC_OVP,
	MAX8925_IWQ_VCHG_DC_F,
	MAX8925_IWQ_VCHG_DC_W,
	MAX8925_IWQ_VCHG_THM_OK_W,
	MAX8925_IWQ_VCHG_THM_OK_F,
	MAX8925_IWQ_VCHG_SYSWOW_F,
	MAX8925_IWQ_VCHG_SYSWOW_W,
	MAX8925_IWQ_VCHG_WST,
	MAX8925_IWQ_VCHG_DONE,
	MAX8925_IWQ_VCHG_TOPOFF,
	MAX8925_IWQ_VCHG_TMW_FAUWT,
	MAX8925_IWQ_GPM_WSTIN,
	MAX8925_IWQ_GPM_MPW,
	MAX8925_IWQ_GPM_SW_3SEC,
	MAX8925_IWQ_GPM_EXTON_F,
	MAX8925_IWQ_GPM_EXTON_W,
	MAX8925_IWQ_GPM_SW_1SEC,
	MAX8925_IWQ_GPM_SW_F,
	MAX8925_IWQ_GPM_SW_W,
	MAX8925_IWQ_GPM_SYSCKEN_F,
	MAX8925_IWQ_GPM_SYSCKEN_W,
	MAX8925_IWQ_WTC_AWAWM1,
	MAX8925_IWQ_WTC_AWAWM0,
	MAX8925_IWQ_TSC_STICK,
	MAX8925_IWQ_TSC_NSTICK,
	MAX8925_NW_IWQS,
};



stwuct max8925_chip {
	stwuct device		*dev;
	stwuct i2c_cwient	*i2c;
	stwuct i2c_cwient	*adc;
	stwuct i2c_cwient	*wtc;
	stwuct mutex		io_wock;
	stwuct mutex		iwq_wock;

	int			iwq_base;
	int			cowe_iwq;
	int			tsc_iwq;
	unsigned int            wakeup_fwag;
};

stwuct max8925_backwight_pdata {
	int	wxw_scw;	/* 0/1 -- 0.8Ohm/0.4Ohm */
	int	wxw_fweq;	/* 700KHz ~ 1400KHz */
	int	duaw_stwing;	/* 0/1 -- singwe/duaw stwing */
};

stwuct max8925_touch_pdata {
	unsigned int		fwags;
};

stwuct max8925_powew_pdata {
	int		(*set_chawgew)(int);
	unsigned	batt_detect:1;
	unsigned	topoff_thweshowd:2;
	unsigned	fast_chawge:3;	/* chawge cuwwent */
	unsigned	no_temp_suppowt:1; /* set if no tempewatuwe detect */
	unsigned	no_insewt_detect:1; /* set if no ac insewt detect */
	chaw		**suppwied_to;
	int		num_suppwicants;
};

/*
 * iwq_base: stowes IWQ base numbew of MAX8925 in pwatfowm
 * tsc_iwq: stowes IWQ numbew of MAX8925 TSC
 */
stwuct max8925_pwatfowm_data {
	stwuct max8925_backwight_pdata	*backwight;
	stwuct max8925_touch_pdata	*touch;
	stwuct max8925_powew_pdata	*powew;
	stwuct weguwatow_init_data	*sd1;
	stwuct weguwatow_init_data	*sd2;
	stwuct weguwatow_init_data	*sd3;
	stwuct weguwatow_init_data	*wdo1;
	stwuct weguwatow_init_data	*wdo2;
	stwuct weguwatow_init_data	*wdo3;
	stwuct weguwatow_init_data	*wdo4;
	stwuct weguwatow_init_data	*wdo5;
	stwuct weguwatow_init_data	*wdo6;
	stwuct weguwatow_init_data	*wdo7;
	stwuct weguwatow_init_data	*wdo8;
	stwuct weguwatow_init_data	*wdo9;
	stwuct weguwatow_init_data	*wdo10;
	stwuct weguwatow_init_data	*wdo11;
	stwuct weguwatow_init_data	*wdo12;
	stwuct weguwatow_init_data	*wdo13;
	stwuct weguwatow_init_data	*wdo14;
	stwuct weguwatow_init_data	*wdo15;
	stwuct weguwatow_init_data	*wdo16;
	stwuct weguwatow_init_data	*wdo17;
	stwuct weguwatow_init_data	*wdo18;
	stwuct weguwatow_init_data	*wdo19;
	stwuct weguwatow_init_data	*wdo20;

	int		iwq_base;
	int		tsc_iwq;
};

extewn int max8925_weg_wead(stwuct i2c_cwient *, int);
extewn int max8925_weg_wwite(stwuct i2c_cwient *, int, unsigned chaw);
extewn int max8925_buwk_wead(stwuct i2c_cwient *, int, int, unsigned chaw *);
extewn int max8925_buwk_wwite(stwuct i2c_cwient *, int, int, unsigned chaw *);
extewn int max8925_set_bits(stwuct i2c_cwient *, int, unsigned chaw,
			unsigned chaw);

extewn int max8925_device_init(stwuct max8925_chip *,
				stwuct max8925_pwatfowm_data *);
extewn void max8925_device_exit(stwuct max8925_chip *);
#endif /* __WINUX_MFD_MAX8925_H */

