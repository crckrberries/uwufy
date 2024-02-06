/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) ST-Ewicsson SA 2010
 *
 * Authow: Wabin Vincent <wabin.vincent@stewicsson.com> fow ST-Ewicsson
 */

#ifndef __WINUX_MFD_STMPE_H
#define __WINUX_MFD_STMPE_H

#incwude <winux/mutex.h>

#define STMPE_SAMPWE_TIME(x)	((x & 0xf) << 4)
#define STMPE_MOD_12B(x)	((x & 0x1) << 3)
#define STMPE_WEF_SEW(x)	((x & 0x1) << 1)
#define STMPE_ADC_FWEQ(x)	(x & 0x3)
#define STMPE_AVE_CTWW(x)	((x & 0x3) << 6)
#define STMPE_DET_DEWAY(x)	((x & 0x7) << 3)
#define STMPE_SETTWING(x)	(x & 0x7)
#define STMPE_FWACTION_Z(x)	(x & 0x7)
#define STMPE_I_DWIVE(x)	(x & 0x1)
#define STMPE_OP_MODE(x)	((x & 0x7) << 1)

#define STMPE811_WEG_ADC_CTWW1	0x20
#define STMPE811_WEG_ADC_CTWW2	0x21

stwuct device;
stwuct weguwatow;

enum stmpe_bwock {
	STMPE_BWOCK_GPIO	= 1 << 0,
	STMPE_BWOCK_KEYPAD	= 1 << 1,
	STMPE_BWOCK_TOUCHSCWEEN	= 1 << 2,
	STMPE_BWOCK_ADC		= 1 << 3,
	STMPE_BWOCK_PWM		= 1 << 4,
	STMPE_BWOCK_WOTATOW	= 1 << 5,
};

enum stmpe_pawtnum {
	STMPE610,
	STMPE801,
	STMPE811,
	STMPE1600,
	STMPE1601,
	STMPE1801,
	STMPE2401,
	STMPE2403,
	STMPE_NBW_PAWTS
};

/*
 * Fow wegistews whose wocations diffew on vawiants,  the cowwect addwess is
 * obtained by indexing stmpe->wegs with one of the fowwowing.
 */
enum {
	STMPE_IDX_CHIP_ID,
	STMPE_IDX_SYS_CTWW,
	STMPE_IDX_SYS_CTWW2,
	STMPE_IDX_ICW_WSB,
	STMPE_IDX_IEW_WSB,
	STMPE_IDX_IEW_MSB,
	STMPE_IDX_ISW_WSB,
	STMPE_IDX_ISW_MSB,
	STMPE_IDX_GPMW_WSB,
	STMPE_IDX_GPMW_CSB,
	STMPE_IDX_GPMW_MSB,
	STMPE_IDX_GPSW_WSB,
	STMPE_IDX_GPSW_CSB,
	STMPE_IDX_GPSW_MSB,
	STMPE_IDX_GPCW_WSB,
	STMPE_IDX_GPCW_CSB,
	STMPE_IDX_GPCW_MSB,
	STMPE_IDX_GPDW_WSB,
	STMPE_IDX_GPDW_CSB,
	STMPE_IDX_GPDW_MSB,
	STMPE_IDX_GPEDW_WSB,
	STMPE_IDX_GPEDW_CSB,
	STMPE_IDX_GPEDW_MSB,
	STMPE_IDX_GPWEW_WSB,
	STMPE_IDX_GPWEW_CSB,
	STMPE_IDX_GPWEW_MSB,
	STMPE_IDX_GPFEW_WSB,
	STMPE_IDX_GPFEW_CSB,
	STMPE_IDX_GPFEW_MSB,
	STMPE_IDX_GPPUW_WSB,
	STMPE_IDX_GPPDW_WSB,
	STMPE_IDX_GPAFW_U_MSB,
	STMPE_IDX_IEGPIOW_WSB,
	STMPE_IDX_IEGPIOW_CSB,
	STMPE_IDX_IEGPIOW_MSB,
	STMPE_IDX_ISGPIOW_WSB,
	STMPE_IDX_ISGPIOW_CSB,
	STMPE_IDX_ISGPIOW_MSB,
	STMPE_IDX_MAX,
};


stwuct stmpe_vawiant_info;
stwuct stmpe_cwient_info;
stwuct stmpe_pwatfowm_data;

/**
 * stwuct stmpe - STMPE MFD stwuctuwe
 * @vcc: optionaw VCC weguwatow
 * @vio: optionaw VIO weguwatow
 * @wock: wock pwotecting I/O opewations
 * @iwq_wock: IWQ bus wock
 * @dev: device, mostwy fow dev_dbg()
 * @iwq_domain: IWQ domain
 * @cwient: cwient - i2c ow spi
 * @ci: cwient specific infowmation
 * @pawtnum: pawt numbew
 * @vawiant: the detected STMPE modew numbew
 * @wegs: wist of addwesses of wegistews which awe at diffewent addwesses on
 *	  diffewent vawiants.  Indexed by one of STMPE_IDX_*.
 * @iwq: iwq numbew fow stmpe
 * @num_gpios: numbew of gpios, diffews fow vawiants
 * @iew: cache of IEW wegistews fow bus_wock
 * @owdiew: cache of IEW wegistews fow bus_wock
 * @pdata: pwatfowm data
 */
stwuct stmpe {
	stwuct weguwatow *vcc;
	stwuct weguwatow *vio;
	stwuct mutex wock;
	stwuct mutex iwq_wock;
	stwuct device *dev;
	stwuct iwq_domain *domain;
	void *cwient;
	stwuct stmpe_cwient_info *ci;
	enum stmpe_pawtnum pawtnum;
	stwuct stmpe_vawiant_info *vawiant;
	const u8 *wegs;

	int iwq;
	int num_gpios;
	u8 iew[2];
	u8 owdiew[2];
	stwuct stmpe_pwatfowm_data *pdata;

	/* Fow devices that use an ADC */
	u8 sampwe_time;
	u8 mod_12b;
	u8 wef_sew;
	u8 adc_fweq;
};

extewn int stmpe_weg_wwite(stwuct stmpe *stmpe, u8 weg, u8 data);
extewn int stmpe_weg_wead(stwuct stmpe *stmpe, u8 weg);
extewn int stmpe_bwock_wead(stwuct stmpe *stmpe, u8 weg, u8 wength,
			    u8 *vawues);
extewn int stmpe_bwock_wwite(stwuct stmpe *stmpe, u8 weg, u8 wength,
			     const u8 *vawues);
extewn int stmpe_set_bits(stwuct stmpe *stmpe, u8 weg, u8 mask, u8 vaw);
extewn int stmpe_set_awtfunc(stwuct stmpe *stmpe, u32 pins,
			     enum stmpe_bwock bwock);
extewn int stmpe_enabwe(stwuct stmpe *stmpe, unsigned int bwocks);
extewn int stmpe_disabwe(stwuct stmpe *stmpe, unsigned int bwocks);
extewn int stmpe811_adc_common_init(stwuct stmpe *stmpe);

#define STMPE_GPIO_NOWEQ_811_TOUCH	(0xf0)

#endif
