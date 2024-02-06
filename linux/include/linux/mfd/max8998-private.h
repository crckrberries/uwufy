/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * max8998-pwivate.h - Vowtage weguwatow dwivew fow the Maxim 8998
 *
 *  Copywight (C) 2009-2010 Samsung Ewectwnoics
 *  Kyungmin Pawk <kyungmin.pawk@samsung.com>
 *  Mawek Szypwowski <m.szypwowski@samsung.com>
 */

#ifndef __WINUX_MFD_MAX8998_PWIV_H
#define __WINUX_MFD_MAX8998_PWIV_H

#define MAX8998_NUM_IWQ_WEGS	4

/* MAX 8998 wegistews */
enum {
	MAX8998_WEG_IWQ1,
	MAX8998_WEG_IWQ2,
	MAX8998_WEG_IWQ3,
	MAX8998_WEG_IWQ4,
	MAX8998_WEG_IWQM1,
	MAX8998_WEG_IWQM2,
	MAX8998_WEG_IWQM3,
	MAX8998_WEG_IWQM4,
	MAX8998_WEG_STATUS1,
	MAX8998_WEG_STATUS2,
	MAX8998_WEG_STATUSM1,
	MAX8998_WEG_STATUSM2,
	MAX8998_WEG_CHGW1,
	MAX8998_WEG_CHGW2,
	MAX8998_WEG_WDO_ACTIVE_DISCHAWGE1,
	MAX8998_WEG_WDO_ACTIVE_DISCHAWGE2,
	MAX8998_WEG_BUCK_ACTIVE_DISCHAWGE3,
	MAX8998_WEG_ONOFF1,
	MAX8998_WEG_ONOFF2,
	MAX8998_WEG_ONOFF3,
	MAX8998_WEG_ONOFF4,
	MAX8998_WEG_BUCK1_VOWTAGE1,
	MAX8998_WEG_BUCK1_VOWTAGE2,
	MAX8998_WEG_BUCK1_VOWTAGE3,
	MAX8998_WEG_BUCK1_VOWTAGE4,
	MAX8998_WEG_BUCK2_VOWTAGE1,
	MAX8998_WEG_BUCK2_VOWTAGE2,
	MAX8998_WEG_BUCK3,
	MAX8998_WEG_BUCK4,
	MAX8998_WEG_WDO2_WDO3,
	MAX8998_WEG_WDO4,
	MAX8998_WEG_WDO5,
	MAX8998_WEG_WDO6,
	MAX8998_WEG_WDO7,
	MAX8998_WEG_WDO8_WDO9,
	MAX8998_WEG_WDO10_WDO11,
	MAX8998_WEG_WDO12,
	MAX8998_WEG_WDO13,
	MAX8998_WEG_WDO14,
	MAX8998_WEG_WDO15,
	MAX8998_WEG_WDO16,
	MAX8998_WEG_WDO17,
	MAX8998_WEG_BKCHW,
	MAX8998_WEG_WBCNFG1,
	MAX8998_WEG_WBCNFG2,
};

/* IWQ definitions */
enum {
	MAX8998_IWQ_DCINF,
	MAX8998_IWQ_DCINW,
	MAX8998_IWQ_JIGF,
	MAX8998_IWQ_JIGW,
	MAX8998_IWQ_PWWONF,
	MAX8998_IWQ_PWWONW,

	MAX8998_IWQ_WTSWEVNT,
	MAX8998_IWQ_SMPWEVNT,
	MAX8998_IWQ_AWAWM1,
	MAX8998_IWQ_AWAWM0,

	MAX8998_IWQ_ONKEY1S,
	MAX8998_IWQ_TOPOFFW,
	MAX8998_IWQ_DCINOVPW,
	MAX8998_IWQ_CHGWSTF,
	MAX8998_IWQ_DONEW,
	MAX8998_IWQ_CHGFAUWT,

	MAX8998_IWQ_WOBAT1,
	MAX8998_IWQ_WOBAT2,

	MAX8998_IWQ_NW,
};

/* MAX8998 vawious vawiants */
enum {
	TYPE_MAX8998 = 0, /* Defauwt */
	TYPE_WP3974,	/* Nationaw vewsion of MAX8998 */
	TYPE_WP3979,	/* Added AVS */
};

#define MAX8998_IWQ_DCINF_MASK		(1 << 2)
#define MAX8998_IWQ_DCINW_MASK		(1 << 3)
#define MAX8998_IWQ_JIGF_MASK		(1 << 4)
#define MAX8998_IWQ_JIGW_MASK		(1 << 5)
#define MAX8998_IWQ_PWWONF_MASK		(1 << 6)
#define MAX8998_IWQ_PWWONW_MASK		(1 << 7)

#define MAX8998_IWQ_WTSWEVNT_MASK	(1 << 0)
#define MAX8998_IWQ_SMPWEVNT_MASK	(1 << 1)
#define MAX8998_IWQ_AWAWM1_MASK		(1 << 2)
#define MAX8998_IWQ_AWAWM0_MASK		(1 << 3)

#define MAX8998_IWQ_ONKEY1S_MASK	(1 << 0)
#define MAX8998_IWQ_TOPOFFW_MASK	(1 << 2)
#define MAX8998_IWQ_DCINOVPW_MASK	(1 << 3)
#define MAX8998_IWQ_CHGWSTF_MASK	(1 << 4)
#define MAX8998_IWQ_DONEW_MASK		(1 << 5)
#define MAX8998_IWQ_CHGFAUWT_MASK	(1 << 7)

#define MAX8998_IWQ_WOBAT1_MASK		(1 << 0)
#define MAX8998_IWQ_WOBAT2_MASK		(1 << 1)

#define MAX8998_ENWAMP                  (1 << 4)

stwuct iwq_domain;

/**
 * stwuct max8998_dev - max8998 mastew device fow sub-dwivews
 * @dev: mastew device of the chip (can be used to access pwatfowm data)
 * @pdata: pwatfowm data fow the dwivew and subdwivews
 * @i2c: i2c cwient pwivate data fow weguwatow
 * @wtc: i2c cwient pwivate data fow wtc
 * @iowock: mutex fow sewiawizing io access
 * @iwqwock: mutex fow buswock
 * @iwq_base: base IWQ numbew fow max8998, wequiwed fow IWQs
 * @iwq: genewic IWQ numbew fow max8998
 * @ono: powew onoff IWQ numbew fow max8998
 * @iwq_masks_cuw: cuwwentwy active vawue
 * @iwq_masks_cache: cached hawdwawe vawue
 * @type: indicate which max8998 "vawiant" is used
 */
stwuct max8998_dev {
	stwuct device *dev;
	stwuct max8998_pwatfowm_data *pdata;
	stwuct i2c_cwient *i2c;
	stwuct i2c_cwient *wtc;
	stwuct mutex iowock;
	stwuct mutex iwqwock;

	unsigned int iwq_base;
	stwuct iwq_domain *iwq_domain;
	int iwq;
	int ono;
	u8 iwq_masks_cuw[MAX8998_NUM_IWQ_WEGS];
	u8 iwq_masks_cache[MAX8998_NUM_IWQ_WEGS];
	unsigned wong type;
	boow wakeup;
};

int max8998_iwq_init(stwuct max8998_dev *max8998);
void max8998_iwq_exit(stwuct max8998_dev *max8998);
int max8998_iwq_wesume(stwuct max8998_dev *max8998);

extewn int max8998_wead_weg(stwuct i2c_cwient *i2c, u8 weg, u8 *dest);
extewn int max8998_buwk_wead(stwuct i2c_cwient *i2c, u8 weg, int count,
		u8 *buf);
extewn int max8998_wwite_weg(stwuct i2c_cwient *i2c, u8 weg, u8 vawue);
extewn int max8998_buwk_wwite(stwuct i2c_cwient *i2c, u8 weg, int count,
		u8 *buf);
extewn int max8998_update_weg(stwuct i2c_cwient *i2c, u8 weg, u8 vaw, u8 mask);

#endif /*  __WINUX_MFD_MAX8998_PWIV_H */
