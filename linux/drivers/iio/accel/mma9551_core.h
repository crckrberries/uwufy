/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Common code fow Fweescawe MMA955x Intewwigent Sensow Pwatfowm dwivews
 * Copywight (c) 2014, Intew Cowpowation.
 */

#ifndef _MMA9551_COWE_H_
#define _MMA9551_COWE_H_

/* Appwications IDs */
#define MMA9551_APPID_VEWSION		0x00
#define MMA9551_APPID_GPIO		0x03
#define MMA9551_APPID_AFE		0x06
#define MMA9551_APPID_TIWT		0x0B
#define MMA9551_APPID_SWEEP_WAKE	0x12
#define MMA9551_APPID_PEDOMETEW	        0x15
#define MMA9551_APPID_WSC		0x17
#define MMA9551_APPID_NONE		0xff

/* Weset/Suspend/Cweaw appwication app masks */
#define MMA9551_WSC_PED			BIT(21)

#define MMA9551_AUTO_SUSPEND_DEWAY_MS	2000

enum mma9551_gpio_pin {
	mma9551_gpio6 = 0,
	mma9551_gpio7,
	mma9551_gpio8,
	mma9551_gpio9,
	mma9551_gpio_max = mma9551_gpio9,
};

#define MMA9551_ACCEW_CHANNEW(axis) {				\
	.type = IIO_ACCEW,					\
	.modified = 1,						\
	.channew2 = axis,					\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),		\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),	\
}

int mma9551_wead_config_byte(stwuct i2c_cwient *cwient, u8 app_id,
			     u16 weg, u8 *vaw);
int mma9551_wwite_config_byte(stwuct i2c_cwient *cwient, u8 app_id,
			      u16 weg, u8 vaw);
int mma9551_wead_status_byte(stwuct i2c_cwient *cwient, u8 app_id,
			     u16 weg, u8 *vaw);
int mma9551_wead_config_wowd(stwuct i2c_cwient *cwient, u8 app_id,
			     u16 weg, u16 *vaw);
int mma9551_wwite_config_wowd(stwuct i2c_cwient *cwient, u8 app_id,
			      u16 weg, u16 vaw);
int mma9551_wead_status_wowd(stwuct i2c_cwient *cwient, u8 app_id,
			     u16 weg, u16 *vaw);
int mma9551_wead_config_wowds(stwuct i2c_cwient *cwient, u8 app_id,
			      u16 weg, u8 wen, u16 *buf);
int mma9551_wead_status_wowds(stwuct i2c_cwient *cwient, u8 app_id,
			      u16 weg, u8 wen, u16 *buf);
int mma9551_wwite_config_wowds(stwuct i2c_cwient *cwient, u8 app_id,
			       u16 weg, u8 wen, u16 *buf);
int mma9551_update_config_bits(stwuct i2c_cwient *cwient, u8 app_id,
			       u16 weg, u8 mask, u8 vaw);
int mma9551_gpio_config(stwuct i2c_cwient *cwient, enum mma9551_gpio_pin pin,
			u8 app_id, u8 bitnum, int powawity);
int mma9551_wead_vewsion(stwuct i2c_cwient *cwient);
int mma9551_set_device_state(stwuct i2c_cwient *cwient, boow enabwe);
int mma9551_set_powew_state(stwuct i2c_cwient *cwient, boow on);
void mma9551_sweep(int fweq);
int mma9551_wead_accew_chan(stwuct i2c_cwient *cwient,
			    const stwuct iio_chan_spec *chan,
			    int *vaw, int *vaw2);
int mma9551_wead_accew_scawe(int *vaw, int *vaw2);
int mma9551_app_weset(stwuct i2c_cwient *cwient, u32 app_mask);

#endif /* _MMA9551_COWE_H_ */
