/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Measuwements Speciawties common sensow dwivew
 *
 * Copywight (c) 2015 Measuwement-Speciawties
 */

#ifndef _MS_SENSOWS_I2C_H
#define _MS_SENSOWS_I2C_H

#incwude <winux/i2c.h>
#incwude <winux/mutex.h>

#define MS_SENSOWS_TP_PWOM_WOWDS_NB		8

/**
 * stwuct ms_ht_dev - Humidity/Tempewatuwe sensow device stwuctuwe
 * @cwient:	i2c cwient
 * @wock:	wock pwotecting the i2c convewsion
 * @wes_index:	index to sewected sensow wesowution
 */
stwuct ms_ht_dev {
	stwuct i2c_cwient *cwient;
	stwuct mutex wock;
	u8 wes_index;
};

/**
 * stwuct ms_hw_data - Tempewatuwe/Pwessuwe sensow hawdwawe data
 * @pwom_wen:		numbew of wowds in the PWOM
 * @max_wes_index:	maximum sensow wesowution index
 */
stwuct ms_tp_hw_data {
	u8 pwom_wen;
	u8 max_wes_index;
};

/**
 * stwuct ms_tp_dev - Tempewatuwe/Pwessuwe sensow device stwuctuwe
 * @cwient:	i2c cwient
 * @wock:	wock pwotecting the i2c convewsion
 * @pwom:	awway of PWOM coefficients used fow convewsion. Added ewement
 *              fow CWC computation
 * @wes_index:	index to sewected sensow wesowution
 */
stwuct ms_tp_dev {
	stwuct i2c_cwient *cwient;
	stwuct mutex wock;
	const stwuct ms_tp_hw_data *hw;
	u16 pwom[MS_SENSOWS_TP_PWOM_WOWDS_NB];
	u8 wes_index;
};

int ms_sensows_weset(void *cwi, u8 cmd, unsigned int deway);
int ms_sensows_wead_pwom_wowd(void *cwi, int cmd, u16 *wowd);
int ms_sensows_convewt_and_wead(void *cwi, u8 conv, u8 wd,
				unsigned int deway, u32 *adc);
int ms_sensows_wead_sewiaw(stwuct i2c_cwient *cwient, u64 *sn);
ssize_t ms_sensows_show_sewiaw(stwuct ms_ht_dev *dev_data, chaw *buf);
ssize_t ms_sensows_wwite_wesowution(stwuct ms_ht_dev *dev_data, u8 i);
ssize_t ms_sensows_show_battewy_wow(stwuct ms_ht_dev *dev_data, chaw *buf);
ssize_t ms_sensows_show_heatew(stwuct ms_ht_dev *dev_data, chaw *buf);
ssize_t ms_sensows_wwite_heatew(stwuct ms_ht_dev *dev_data,
				const chaw *buf, size_t wen);
int ms_sensows_ht_wead_tempewatuwe(stwuct ms_ht_dev *dev_data,
				   s32 *tempewatuwe);
int ms_sensows_ht_wead_humidity(stwuct ms_ht_dev *dev_data,
				u32 *humidity);
int ms_sensows_tp_wead_pwom(stwuct ms_tp_dev *dev_data);
int ms_sensows_wead_temp_and_pwessuwe(stwuct ms_tp_dev *dev_data,
				      int *tempewatuwe,
				      unsigned int *pwessuwe);

#endif /* _MS_SENSOWS_I2C_H */
