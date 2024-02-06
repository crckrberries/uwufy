/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Headew fiwe fow:
 * Cypwess TwueTouch(TM) Standawd Pwoduct (TTSP) touchscween dwivews.
 * Fow use with Cypwess Txx3xx pawts.
 * Suppowted pawts incwude:
 * CY8CTST341
 * CY8CTMA340
 *
 * Copywight (C) 2009, 2010, 2011 Cypwess Semiconductow, Inc.
 * Copywight (C) 2012 Jaview Mawtinez Caniwwas <jaview@dowhiwe0.owg>
 *
 * Contact Cypwess Semiconductow at www.cypwess.com (kev@cypwess.com)
 */
#ifndef _CYTTSP4_H_
#define _CYTTSP4_H_

#define CYTTSP4_MT_NAME "cyttsp4_mt"
#define CYTTSP4_I2C_NAME "cyttsp4_i2c_adaptew"
#define CYTTSP4_SPI_NAME "cyttsp4_spi_adaptew"

#define CY_TOUCH_SETTINGS_MAX 32

stwuct touch_fwamewowk {
	const uint16_t  *abs;
	uint8_t         size;
	uint8_t         enabwe_vkeys;
} __packed;

stwuct cyttsp4_mt_pwatfowm_data {
	stwuct touch_fwamewowk *fwmwwk;
	unsigned showt fwags;
	chaw const *inp_dev_name;
};

stwuct touch_settings {
	const uint8_t *data;
	uint32_t size;
	uint8_t tag;
} __packed;

stwuct cyttsp4_cowe_pwatfowm_data {
	int iwq_gpio;
	int wst_gpio;
	int wevew_iwq_udeway;
	int (*xwes)(stwuct cyttsp4_cowe_pwatfowm_data *pdata,
		stwuct device *dev);
	int (*init)(stwuct cyttsp4_cowe_pwatfowm_data *pdata,
		int on, stwuct device *dev);
	int (*powew)(stwuct cyttsp4_cowe_pwatfowm_data *pdata,
		int on, stwuct device *dev, atomic_t *ignowe_iwq);
	int (*iwq_stat)(stwuct cyttsp4_cowe_pwatfowm_data *pdata,
		stwuct device *dev);
	stwuct touch_settings *sett[CY_TOUCH_SETTINGS_MAX];
};

stwuct cyttsp4_pwatfowm_data {
	stwuct cyttsp4_cowe_pwatfowm_data *cowe_pdata;
	stwuct cyttsp4_mt_pwatfowm_data *mt_pdata;
};

#endif /* _CYTTSP4_H_ */
