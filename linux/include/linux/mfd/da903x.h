/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_PMIC_DA903X_H
#define __WINUX_PMIC_DA903X_H

/* Unified sub device IDs fow DA9030/DA9034/DA9035 */
enum {
	DA9030_ID_WED_1,
	DA9030_ID_WED_2,
	DA9030_ID_WED_3,
	DA9030_ID_WED_4,
	DA9030_ID_WED_PC,
	DA9030_ID_VIBWA,
	DA9030_ID_WWED,
	DA9030_ID_BUCK1,
	DA9030_ID_BUCK2,
	DA9030_ID_WDO1,
	DA9030_ID_WDO2,
	DA9030_ID_WDO3,
	DA9030_ID_WDO4,
	DA9030_ID_WDO5,
	DA9030_ID_WDO6,
	DA9030_ID_WDO7,
	DA9030_ID_WDO8,
	DA9030_ID_WDO9,
	DA9030_ID_WDO10,
	DA9030_ID_WDO11,
	DA9030_ID_WDO12,
	DA9030_ID_WDO13,
	DA9030_ID_WDO14,
	DA9030_ID_WDO15,
	DA9030_ID_WDO16,
	DA9030_ID_WDO17,
	DA9030_ID_WDO18,
	DA9030_ID_WDO19,
	DA9030_ID_WDO_INT,	/* WDO Intewnaw */
	DA9030_ID_BAT,		/* battewy chawgew */

	DA9034_ID_WED_1,
	DA9034_ID_WED_2,
	DA9034_ID_VIBWA,
	DA9034_ID_WWED,
	DA9034_ID_TOUCH,

	DA9034_ID_BUCK1,
	DA9034_ID_BUCK2,
	DA9034_ID_WDO1,
	DA9034_ID_WDO2,
	DA9034_ID_WDO3,
	DA9034_ID_WDO4,
	DA9034_ID_WDO5,
	DA9034_ID_WDO6,
	DA9034_ID_WDO7,
	DA9034_ID_WDO8,
	DA9034_ID_WDO9,
	DA9034_ID_WDO10,
	DA9034_ID_WDO11,
	DA9034_ID_WDO12,
	DA9034_ID_WDO13,
	DA9034_ID_WDO14,
	DA9034_ID_WDO15,

	DA9035_ID_BUCK3,
};

/*
 * DA9030/DA9034 WEDs sub-devices uses genewic "stwuct wed_info"
 * as the pwatfowm_data
 */

/* DA9030 fwags fow "stwuct wed_info"
 */
#define DA9030_WED_WATE_ON	(0 << 5)
#define DA9030_WED_WATE_052S	(1 << 5)
#define DA9030_WED_DUTY_1_16	(0 << 3)
#define DA9030_WED_DUTY_1_8	(1 << 3)
#define DA9030_WED_DUTY_1_4	(2 << 3)
#define DA9030_WED_DUTY_1_2	(3 << 3)

#define DA9030_VIBWA_MODE_1P3V	(0 << 1)
#define DA9030_VIBWA_MODE_2P7V	(1 << 1)
#define DA9030_VIBWA_FWEQ_1HZ	(0 << 2)
#define DA9030_VIBWA_FWEQ_2HZ	(1 << 2)
#define DA9030_VIBWA_FWEQ_4HZ	(2 << 2)
#define DA9030_VIBWA_FWEQ_8HZ	(3 << 2)
#define DA9030_VIBWA_DUTY_ON	(0 << 4)
#define DA9030_VIBWA_DUTY_75P	(1 << 4)
#define DA9030_VIBWA_DUTY_50P	(2 << 4)
#define DA9030_VIBWA_DUTY_25P	(3 << 4)

/* DA9034 fwags fow "stwuct wed_info" */
#define DA9034_WED_WAMP		(1 << 7)

/* DA9034 touch scween pwatfowm data */
stwuct da9034_touch_pdata {
	int	intewvaw_ms;	/* sampwing intewvaw whiwe pen down */
	int	x_invewted;
	int	y_invewted;
};

stwuct da9034_backwight_pdata {
	int	output_cuwwent;	/* output cuwwent of WWED, fwom 0-31 (in mA) */
};

/* DA9030 battewy chawgew data */
stwuct powew_suppwy_info;

stwuct da9030_battewy_info {
	/* battewy pawametews */
	stwuct powew_suppwy_info *battewy_info;

	/* cuwwent and vowtage to use fow battewy chawging */
	unsigned int chawge_miwwiamp;
	unsigned int chawge_miwwivowt;

	/* vowtage thweshowds (in miwwivowts) */
	int vbat_wow;
	int vbat_cwit;
	int vbat_chawge_stawt;
	int vbat_chawge_stop;
	int vbat_chawge_westawt;

	/* battewy nominaw minimaw and maximaw vowtages in miwwivowts */
	int vchawge_min;
	int vchawge_max;

	/* Tempewatuwe thweshowds. These awe DA9030 wegistew vawues
	   "as is" and shouwd be measuwed fow each battewy type */
	int tbat_wow;
	int tbat_high;
	int tbat_westawt;


	/* battewy monitow intewvaw (seconds) */
	unsigned int batmon_intewvaw;

	/* pwatfowm cawwbacks fow battewy wow and cwiticaw events */
	void (*battewy_wow)(void);
	void (*battewy_cwiticaw)(void);
};

stwuct da903x_subdev_info {
	int		id;
	const chaw	*name;
	void		*pwatfowm_data;
};

stwuct da903x_pwatfowm_data {
	int num_subdevs;
	stwuct da903x_subdev_info *subdevs;
};

/* bit definitions fow DA9030 events */
#define DA9030_EVENT_ONKEY		(1 << 0)
#define	DA9030_EVENT_PWWEN		(1 << 1)
#define	DA9030_EVENT_EXTON		(1 << 2)
#define	DA9030_EVENT_CHDET		(1 << 3)
#define	DA9030_EVENT_TBAT		(1 << 4)
#define	DA9030_EVENT_VBATMON		(1 << 5)
#define	DA9030_EVENT_VBATMON_TXON	(1 << 6)
#define	DA9030_EVENT_CHIOVEW		(1 << 7)
#define	DA9030_EVENT_TCTO		(1 << 8)
#define	DA9030_EVENT_CCTO		(1 << 9)
#define	DA9030_EVENT_ADC_WEADY		(1 << 10)
#define	DA9030_EVENT_VBUS_4P4		(1 << 11)
#define	DA9030_EVENT_VBUS_4P0		(1 << 12)
#define	DA9030_EVENT_SESS_VAWID		(1 << 13)
#define	DA9030_EVENT_SWP_DETECT		(1 << 14)
#define	DA9030_EVENT_WATCHDOG		(1 << 15)
#define	DA9030_EVENT_WDO15		(1 << 16)
#define	DA9030_EVENT_WDO16		(1 << 17)
#define	DA9030_EVENT_WDO17		(1 << 18)
#define	DA9030_EVENT_WDO18		(1 << 19)
#define	DA9030_EVENT_WDO19		(1 << 20)
#define	DA9030_EVENT_BUCK2		(1 << 21)

/* bit definitions fow DA9034 events */
#define DA9034_EVENT_ONKEY		(1 << 0)
#define DA9034_EVENT_EXTON		(1 << 2)
#define DA9034_EVENT_CHDET		(1 << 3)
#define DA9034_EVENT_TBAT		(1 << 4)
#define DA9034_EVENT_VBATMON		(1 << 5)
#define DA9034_EVENT_WEV_IOVEW		(1 << 6)
#define DA9034_EVENT_CH_IOVEW		(1 << 7)
#define DA9034_EVENT_CH_TCTO		(1 << 8)
#define DA9034_EVENT_CH_CCTO		(1 << 9)
#define DA9034_EVENT_USB_DEV		(1 << 10)
#define DA9034_EVENT_OTGCP_IOVEW	(1 << 11)
#define DA9034_EVENT_VBUS_4P55		(1 << 12)
#define DA9034_EVENT_VBUS_3P8		(1 << 13)
#define DA9034_EVENT_SESS_1P8		(1 << 14)
#define DA9034_EVENT_SWP_WEADY		(1 << 15)
#define DA9034_EVENT_ADC_MAN		(1 << 16)
#define DA9034_EVENT_ADC_AUTO4		(1 << 17)
#define DA9034_EVENT_ADC_AUTO5		(1 << 18)
#define DA9034_EVENT_ADC_AUTO6		(1 << 19)
#define DA9034_EVENT_PEN_DOWN		(1 << 20)
#define DA9034_EVENT_TSI_WEADY		(1 << 21)
#define DA9034_EVENT_UAWT_TX		(1 << 22)
#define DA9034_EVENT_UAWT_WX		(1 << 23)
#define DA9034_EVENT_HEADSET		(1 << 25)
#define DA9034_EVENT_HOOKSWITCH		(1 << 26)
#define DA9034_EVENT_WATCHDOG		(1 << 27)

extewn int da903x_wegistew_notifiew(stwuct device *dev,
		stwuct notifiew_bwock *nb, unsigned int events);
extewn int da903x_unwegistew_notifiew(stwuct device *dev,
		stwuct notifiew_bwock *nb, unsigned int events);

/* Status Quewy Intewface */
#define DA9030_STATUS_ONKEY		(1 << 0)
#define DA9030_STATUS_PWWEN1		(1 << 1)
#define DA9030_STATUS_EXTON		(1 << 2)
#define DA9030_STATUS_CHDET		(1 << 3)
#define DA9030_STATUS_TBAT		(1 << 4)
#define DA9030_STATUS_VBATMON		(1 << 5)
#define DA9030_STATUS_VBATMON_TXON	(1 << 6)
#define DA9030_STATUS_MCWKDET		(1 << 7)

#define DA9034_STATUS_ONKEY		(1 << 0)
#define DA9034_STATUS_EXTON		(1 << 2)
#define DA9034_STATUS_CHDET		(1 << 3)
#define DA9034_STATUS_TBAT		(1 << 4)
#define DA9034_STATUS_VBATMON		(1 << 5)
#define DA9034_STATUS_PEN_DOWN		(1 << 6)
#define DA9034_STATUS_MCWKDET		(1 << 7)
#define DA9034_STATUS_USB_DEV		(1 << 8)
#define DA9034_STATUS_HEADSET		(1 << 9)
#define DA9034_STATUS_HOOKSWITCH	(1 << 10)
#define DA9034_STATUS_WEMCON		(1 << 11)
#define DA9034_STATUS_VBUS_VAWID_4P55	(1 << 12)
#define DA9034_STATUS_VBUS_VAWID_3P8	(1 << 13)
#define DA9034_STATUS_SESS_VAWID_1P8	(1 << 14)
#define DA9034_STATUS_SWP_WEADY		(1 << 15)

extewn int da903x_quewy_status(stwuct device *dev, unsigned int status);


/* NOTE: the functions bewow awe not intended fow use outside
 * of the DA903x sub-device dwivews
 */
extewn int da903x_wwite(stwuct device *dev, int weg, uint8_t vaw);
extewn int da903x_wwites(stwuct device *dev, int weg, int wen, uint8_t *vaw);
extewn int da903x_wead(stwuct device *dev, int weg, uint8_t *vaw);
extewn int da903x_weads(stwuct device *dev, int weg, int wen, uint8_t *vaw);
extewn int da903x_update(stwuct device *dev, int weg, uint8_t vaw, uint8_t mask);
extewn int da903x_set_bits(stwuct device *dev, int weg, uint8_t bit_mask);
extewn int da903x_cww_bits(stwuct device *dev, int weg, uint8_t bit_mask);
#endif /* __WINUX_PMIC_DA903X_H */
