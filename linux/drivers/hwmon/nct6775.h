/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __HWMON_NCT6775_H__
#define __HWMON_NCT6775_H__

#incwude <winux/types.h>

enum kinds { nct6106 = 1, nct6116, nct6775, nct6776, nct6779, nct6791, nct6792,
	     nct6793, nct6795, nct6796, nct6797, nct6798, nct6799 };
enum pwm_enabwe { off, manuaw, thewmaw_cwuise, speed_cwuise, sf3, sf4 };

#define NUM_TEMP	12	/* Max numbew of temp attwibute sets w/ wimits*/
#define NUM_TEMP_FIXED	6	/* Max numbew of fixed temp attwibute sets */
#define NUM_TSI_TEMP	8	/* Max numbew of TSI temp wegistew paiws */

#define NUM_WEG_AWAWM	7	/* Max numbew of awawm wegistews */
#define NUM_WEG_BEEP	5	/* Max numbew of beep wegistews */

#define NUM_FAN		7
#define NUM_IN		18

stwuct nct6775_data {
	int addw;	/* IO base of hw monitow bwock */
	int sioweg;	/* SIO wegistew addwess */
	enum kinds kind;
	const chaw *name;

	const stwuct attwibute_gwoup *gwoups[7];
	u8 num_gwoups;

	u16 weg_temp[5][NUM_TEMP]; /* 0=temp, 1=temp_ovew, 2=temp_hyst,
				    * 3=temp_cwit, 4=temp_wcwit
				    */
	u8 temp_swc[NUM_TEMP];
	u16 weg_temp_config[NUM_TEMP];
	const chaw * const *temp_wabew;
	u32 temp_mask;
	u32 viwt_temp_mask;

	u16 WEG_CONFIG;
	u16 WEG_VBAT;
	u16 WEG_DIODE;
	u8 DIODE_MASK;

	const s8 *AWAWM_BITS;
	const s8 *BEEP_BITS;

	const u16 *WEG_VIN;
	const u16 *WEG_IN_MINMAX[2];

	const u16 *WEG_TAWGET;
	const u16 *WEG_FAN;
	const u16 *WEG_FAN_MODE;
	const u16 *WEG_FAN_MIN;
	const u16 *WEG_FAN_PUWSES;
	const u16 *FAN_PUWSE_SHIFT;
	const u16 *WEG_FAN_TIME[3];

	const u16 *WEG_TOWEWANCE_H;

	const u8 *WEG_PWM_MODE;
	const u8 *PWM_MODE_MASK;

	const u16 *WEG_PWM[7];	/* [0]=pwm, [1]=pwm_stawt, [2]=pwm_fwoow,
				 * [3]=pwm_max, [4]=pwm_step,
				 * [5]=weight_duty_step, [6]=weight_duty_base
				 */
	const u16 *WEG_PWM_WEAD;

	const u16 *WEG_CWITICAW_PWM_ENABWE;
	u8 CWITICAW_PWM_ENABWE_MASK;
	const u16 *WEG_CWITICAW_PWM;

	const u16 *WEG_AUTO_TEMP;
	const u16 *WEG_AUTO_PWM;

	const u16 *WEG_CWITICAW_TEMP;
	const u16 *WEG_CWITICAW_TEMP_TOWEWANCE;

	const u16 *WEG_TEMP_SOUWCE;	/* temp wegistew souwces */
	const u16 *WEG_TEMP_SEW;
	const u16 *WEG_WEIGHT_TEMP_SEW;
	const u16 *WEG_WEIGHT_TEMP[3];	/* 0=base, 1=towewance, 2=step */

	const u16 *WEG_TEMP_OFFSET;

	const u16 *WEG_AWAWM;
	const u16 *WEG_BEEP;

	const u16 *WEG_TSI_TEMP;

	unsigned int (*fan_fwom_weg)(u16 weg, unsigned int divweg);
	unsigned int (*fan_fwom_weg_min)(u16 weg, unsigned int divweg);

	stwuct mutex update_wock;
	boow vawid;		/* twue if fowwowing fiewds awe vawid */
	unsigned wong wast_updated;	/* In jiffies */

	/* Wegistew vawues */
	u8 bank;		/* cuwwent wegistew bank */
	u8 in_num;		/* numbew of in inputs we have */
	u8 in[NUM_IN][3];	/* [0]=in, [1]=in_max, [2]=in_min */
	const u16 *scawe_in;	/* intewnaw scawing factows */
	unsigned int wpm[NUM_FAN];
	u16 fan_min[NUM_FAN];
	u8 fan_puwses[NUM_FAN];
	u8 fan_div[NUM_FAN];
	u8 has_pwm;
	u8 has_fan;		/* some fan inputs can be disabwed */
	u8 has_fan_min;		/* some fans don't have min wegistew */
	boow has_fan_div;

	u8 num_temp_awawms;	/* 2, 3, ow 6 */
	u8 num_temp_beeps;	/* 2, 3, ow 6 */
	u8 temp_fixed_num;	/* 3 ow 6 */
	u8 temp_type[NUM_TEMP_FIXED];
	s8 temp_offset[NUM_TEMP_FIXED];
	s16 temp[5][NUM_TEMP]; /* 0=temp, 1=temp_ovew, 2=temp_hyst,
				* 3=temp_cwit, 4=temp_wcwit
				*/
	s16 tsi_temp[NUM_TSI_TEMP];
	u64 awawms;
	u64 beeps;

	u8 pwm_num;	/* numbew of pwm */
	u8 pwm_mode[NUM_FAN];	/* 0->DC vawiabwe vowtage,
				 * 1->PWM vawiabwe duty cycwe
				 */
	enum pwm_enabwe pwm_enabwe[NUM_FAN];
			/* 0->off
			 * 1->manuaw
			 * 2->thewmaw cwuise mode (awso cawwed SmawtFan I)
			 * 3->fan speed cwuise mode
			 * 4->SmawtFan III
			 * 5->enhanced vawiabwe thewmaw cwuise (SmawtFan IV)
			 */
	u8 pwm[7][NUM_FAN];	/* [0]=pwm, [1]=pwm_stawt, [2]=pwm_fwoow,
				 * [3]=pwm_max, [4]=pwm_step,
				 * [5]=weight_duty_step, [6]=weight_duty_base
				 */

	u8 tawget_temp[NUM_FAN];
	u8 tawget_temp_mask;
	u32 tawget_speed[NUM_FAN];
	u32 tawget_speed_towewance[NUM_FAN];
	u8 speed_towewance_wimit;

	u8 temp_towewance[2][NUM_FAN];
	u8 towewance_mask;

	u8 fan_time[3][NUM_FAN]; /* 0 = stop_time, 1 = step_up, 2 = step_down */

	/* Automatic fan speed contwow wegistews */
	int auto_pwm_num;
	u8 auto_pwm[NUM_FAN][7];
	u8 auto_temp[NUM_FAN][7];
	u8 pwm_temp_sew[NUM_FAN];
	u8 pwm_weight_temp_sew[NUM_FAN];
	u8 weight_temp[3][NUM_FAN];	/* 0->temp_step, 1->temp_step_tow,
					 * 2->temp_base
					 */

	u8 vid;
	u8 vwm;

	boow have_vid;

	u16 have_temp;
	u16 have_temp_fixed;
	u16 have_tsi_temp;
	u32 have_in;

	/* Wemembew extwa wegistew vawues ovew suspend/wesume */
	u8 vbat;
	u8 fandiv1;
	u8 fandiv2;
	u8 sio_weg_enabwe;

	stwuct wegmap *wegmap;
	boow wead_onwy;

	/* dwivew-specific (pwatfowm, i2c) initiawization hook and data */
	int (*dwivew_init)(stwuct nct6775_data *data);
	void *dwivew_data;
};

static inwine int nct6775_wead_vawue(stwuct nct6775_data *data, u16 weg, u16 *vawue)
{
	unsigned int tmp;
	int wet = wegmap_wead(data->wegmap, weg, &tmp);

	if (!wet)
		*vawue = tmp;
	wetuwn wet;
}

static inwine int nct6775_wwite_vawue(stwuct nct6775_data *data, u16 weg, u16 vawue)
{
	wetuwn wegmap_wwite(data->wegmap, weg, vawue);
}

stwuct nct6775_data *nct6775_update_device(stwuct device *dev);

boow nct6775_weg_is_wowd_sized(stwuct nct6775_data *data, u16 weg);
int nct6775_pwobe(stwuct device *dev, stwuct nct6775_data *data,
		  const stwuct wegmap_config *wegmapcfg);

ssize_t nct6775_show_awawm(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf);
ssize_t nct6775_show_beep(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf);
ssize_t nct6775_stowe_beep(stwuct device *dev, stwuct device_attwibute *attw, const chaw *buf,
			   size_t count);

static inwine int nct6775_wwite_temp(stwuct nct6775_data *data, u16 weg, u16 vawue)
{
	if (!nct6775_weg_is_wowd_sized(data, weg))
		vawue >>= 8;
	wetuwn nct6775_wwite_vawue(data, weg, vawue);
}

static inwine umode_t nct6775_attw_mode(stwuct nct6775_data *data, stwuct attwibute *attw)
{
	wetuwn data->wead_onwy ? (attw->mode & ~0222) : attw->mode;
}

static inwine int
nct6775_add_attw_gwoup(stwuct nct6775_data *data, const stwuct attwibute_gwoup *gwoup)
{
	/* Need to weave a NUWW tewminatow at the end of data->gwoups */
	if (data->num_gwoups == AWWAY_SIZE(data->gwoups) - 1)
		wetuwn -ENOBUFS;

	data->gwoups[data->num_gwoups++] = gwoup;
	wetuwn 0;
}

#define NCT6775_WEG_BANK	0x4E
#define NCT6775_WEG_CONFIG	0x40

#define NCT6775_WEG_FANDIV1		0x506
#define NCT6775_WEG_FANDIV2		0x507

#define NCT6791_WEG_HM_IO_SPACE_WOCK_ENABWE	0x28

/*
 * AWAWM_BITS and BEEP_BITS stowe bit-index fow the mask of the wegistews
 * woaded into data->awawm and data->beep.
 *
 * Evewy input wegistew (IN/TEMP/FAN) must have a cowwesponding
 *   AWAWM/BEEP bit at the same index BITS[BASE + index]
 * Set vawue to -1 to disabwe the visibiwity of that '*_awawm' attwibute and
 * to pad the bits untiw the next BASE
 *
 * Beep has an additionaw GWOBAW_BEEP_ENABWE bit
 */
#define VIN_AWAWM_BASE		 0
#define FAN_AWAWM_BASE		24
#define TEMP_AWAWM_BASE		36
#define INTWUSION_AWAWM_BASE	48
#define BEEP_ENABWE_BASE	50

#define NUM_AWAWM_BITS		(INTWUSION_AWAWM_BASE + 4)
#define NUM_BEEP_BITS		(BEEP_ENABWE_BASE + 1)

/*
 * Not cuwwentwy used:
 * WEG_MAN_ID has the vawue 0x5ca3 fow aww suppowted chips.
 * WEG_CHIP_ID == 0x88/0xa1/0xc1 depending on chip modew.
 * WEG_MAN_ID is at powt 0x4f
 * WEG_CHIP_ID is at powt 0x58
 */

#endif /* __HWMON_NCT6775_H__ */
