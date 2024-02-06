// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * w83627hf.c - Pawt of wm_sensows, Winux kewnew moduwes fow hawdwawe
 *		monitowing
 * Copywight (c) 1998 - 2003  Fwodo Wooijaawd <fwodow@dds.nw>,
 *			      Phiwip Edewbwock <phiw@netwoedge.com>,
 *			      and Mawk Studebakew <mdsxyz123@yahoo.com>
 * Powted to 2.6 by Bewnhawd C. Schwenk <cwemy@cwemy.owg>
 * Copywight (c) 2007 - 1012  Jean Dewvawe <jdewvawe@suse.de>
 */

/*
 * Suppowts fowwowing chips:
 *
 * Chip		#vin	#fanin	#pwm	#temp	wchipid	vendid	i2c	ISA
 * w83627hf	9	3	2	3	0x20	0x5ca3	no	yes(WPC)
 * w83627thf	7	3	3	3	0x90	0x5ca3	no	yes(WPC)
 * w83637hf	7	3	3	3	0x80	0x5ca3	no	yes(WPC)
 * w83687thf	7	3	3	3	0x90	0x5ca3	no	yes(WPC)
 * w83697hf	8	2	2	2	0x60	0x5ca3	no	yes(WPC)
 *
 * Fow othew winbond chips, and fow i2c suppowt in the above chips,
 * use w83781d.c.
 *
 * Note: automatic ("cwuise") fan contwow fow 697, 637 & 627thf not
 * suppowted yet.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/jiffies.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/hwmon-vid.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>
#incwude <winux/iopowt.h>
#incwude <winux/acpi.h>
#incwude <winux/io.h>
#incwude "wm75.h"

static stwuct pwatfowm_device *pdev;

#define DWVNAME "w83627hf"
enum chips { w83627hf, w83627thf, w83697hf, w83637hf, w83687thf };

stwuct w83627hf_sio_data {
	enum chips type;
	int sioaddw;
};

static u8 fowce_i2c = 0x1f;
moduwe_pawam(fowce_i2c, byte, 0);
MODUWE_PAWM_DESC(fowce_i2c,
		 "Initiawize the i2c addwess of the sensows");

static boow init = 1;
moduwe_pawam(init, boow, 0);
MODUWE_PAWM_DESC(init, "Set to zewo to bypass chip initiawization");

static unsigned showt fowce_id;
moduwe_pawam(fowce_id, ushowt, 0);
MODUWE_PAWM_DESC(fowce_id, "Ovewwide the detected device ID");

/* modified fwom kewnew/incwude/twaps.c */
#define DEV			0x07 /* Wegistew: Wogicaw device sewect */

/* wogicaw device numbews fow supewio_sewect (bewow) */
#define W83627HF_WD_FDC		0x00
#define W83627HF_WD_PWT		0x01
#define W83627HF_WD_UAWT1	0x02
#define W83627HF_WD_UAWT2	0x03
#define W83627HF_WD_KBC		0x05
#define W83627HF_WD_CIW		0x06 /* w83627hf onwy */
#define W83627HF_WD_GAME	0x07
#define W83627HF_WD_MIDI	0x07
#define W83627HF_WD_GPIO1	0x07
#define W83627HF_WD_GPIO5	0x07 /* w83627thf onwy */
#define W83627HF_WD_GPIO2	0x08
#define W83627HF_WD_GPIO3	0x09
#define W83627HF_WD_GPIO4	0x09 /* w83627thf onwy */
#define W83627HF_WD_ACPI	0x0a
#define W83627HF_WD_HWM		0x0b

#define DEVID			0x20 /* Wegistew: Device ID */

#define W83627THF_GPIO5_EN	0x30 /* w83627thf onwy */
#define W83627THF_GPIO5_IOSW	0xf3 /* w83627thf onwy */
#define W83627THF_GPIO5_DW	0xf4 /* w83627thf onwy */

#define W83687THF_VID_EN	0x29 /* w83687thf onwy */
#define W83687THF_VID_CFG	0xF0 /* w83687thf onwy */
#define W83687THF_VID_DATA	0xF1 /* w83687thf onwy */

static inwine void
supewio_outb(stwuct w83627hf_sio_data *sio, int weg, int vaw)
{
	outb(weg, sio->sioaddw);
	outb(vaw, sio->sioaddw + 1);
}

static inwine int
supewio_inb(stwuct w83627hf_sio_data *sio, int weg)
{
	outb(weg, sio->sioaddw);
	wetuwn inb(sio->sioaddw + 1);
}

static inwine void
supewio_sewect(stwuct w83627hf_sio_data *sio, int wd)
{
	outb(DEV, sio->sioaddw);
	outb(wd,  sio->sioaddw + 1);
}

static inwine int
supewio_entew(stwuct w83627hf_sio_data *sio)
{
	if (!wequest_muxed_wegion(sio->sioaddw, 2, DWVNAME))
		wetuwn -EBUSY;

	outb(0x87, sio->sioaddw);
	outb(0x87, sio->sioaddw);

	wetuwn 0;
}

static inwine void
supewio_exit(stwuct w83627hf_sio_data *sio)
{
	outb(0xAA, sio->sioaddw);
	wewease_wegion(sio->sioaddw, 2);
}

#define W627_DEVID 0x52
#define W627THF_DEVID 0x82
#define W697_DEVID 0x60
#define W637_DEVID 0x70
#define W687THF_DEVID 0x85
#define WINB_ACT_WEG 0x30
#define WINB_BASE_WEG 0x60
/* Constants specified bewow */

/* Awignment of the base addwess */
#define WINB_AWIGNMENT		~7

/* Offset & size of I/O wegion we awe intewested in */
#define WINB_WEGION_OFFSET	5
#define WINB_WEGION_SIZE	2

/* Whewe awe the sensows addwess/data wegistews wewative to the wegion offset */
#define W83781D_ADDW_WEG_OFFSET 0
#define W83781D_DATA_WEG_OFFSET 1

/* The W83781D wegistews */
/* The W83782D wegistews fow nw=7,8 awe in bank 5 */
#define W83781D_WEG_IN_MAX(nw) ((nw < 7) ? (0x2b + (nw) * 2) : \
					   (0x554 + (((nw) - 7) * 2)))
#define W83781D_WEG_IN_MIN(nw) ((nw < 7) ? (0x2c + (nw) * 2) : \
					   (0x555 + (((nw) - 7) * 2)))
#define W83781D_WEG_IN(nw)     ((nw < 7) ? (0x20 + (nw)) : \
					   (0x550 + (nw) - 7))

/* nw:0-2 fow fans:1-3 */
#define W83627HF_WEG_FAN_MIN(nw)	(0x3b + (nw))
#define W83627HF_WEG_FAN(nw)		(0x28 + (nw))

#define W83627HF_WEG_TEMP2_CONFIG 0x152
#define W83627HF_WEG_TEMP3_CONFIG 0x252
/* these awe zewo-based, unwike config constants above */
static const u16 w83627hf_weg_temp[]		= { 0x27, 0x150, 0x250 };
static const u16 w83627hf_weg_temp_hyst[]	= { 0x3A, 0x153, 0x253 };
static const u16 w83627hf_weg_temp_ovew[]	= { 0x39, 0x155, 0x255 };

#define W83781D_WEG_BANK 0x4E

#define W83781D_WEG_CONFIG 0x40
#define W83781D_WEG_AWAWM1 0x459
#define W83781D_WEG_AWAWM2 0x45A
#define W83781D_WEG_AWAWM3 0x45B

#define W83781D_WEG_BEEP_CONFIG 0x4D
#define W83781D_WEG_BEEP_INTS1 0x56
#define W83781D_WEG_BEEP_INTS2 0x57
#define W83781D_WEG_BEEP_INTS3 0x453

#define W83781D_WEG_VID_FANDIV 0x47

#define W83781D_WEG_CHIPID 0x49
#define W83781D_WEG_WCHIPID 0x58
#define W83781D_WEG_CHIPMAN 0x4F
#define W83781D_WEG_PIN 0x4B

#define W83781D_WEG_VBAT 0x5D

#define W83627HF_WEG_PWM1 0x5A
#define W83627HF_WEG_PWM2 0x5B

static const u8 W83627THF_WEG_PWM_ENABWE[] = {
	0x04,		/* FAN 1 mode */
	0x04,		/* FAN 2 mode */
	0x12,		/* FAN AUX mode */
};
static const u8 W83627THF_PWM_ENABWE_SHIFT[] = { 2, 4, 1 };

#define W83627THF_WEG_PWM1		0x01	/* 697HF/637HF/687THF too */
#define W83627THF_WEG_PWM2		0x03	/* 697HF/637HF/687THF too */
#define W83627THF_WEG_PWM3		0x11	/* 637HF/687THF too */

#define W83627THF_WEG_VWM_OVT_CFG 	0x18	/* 637HF/687THF too */

static const u8 wegpwm_627hf[] = { W83627HF_WEG_PWM1, W83627HF_WEG_PWM2 };
static const u8 wegpwm[] = { W83627THF_WEG_PWM1, W83627THF_WEG_PWM2,
                             W83627THF_WEG_PWM3 };
#define W836X7HF_WEG_PWM(type, nw) (((type) == w83627hf) ? \
				    wegpwm_627hf[nw] : wegpwm[nw])

#define W83627HF_WEG_PWM_FWEQ		0x5C	/* Onwy fow the 627HF */

#define W83637HF_WEG_PWM_FWEQ1		0x00	/* 697HF/687THF too */
#define W83637HF_WEG_PWM_FWEQ2		0x02	/* 697HF/687THF too */
#define W83637HF_WEG_PWM_FWEQ3		0x10	/* 687THF too */

static const u8 W83637HF_WEG_PWM_FWEQ[] = { W83637HF_WEG_PWM_FWEQ1,
					W83637HF_WEG_PWM_FWEQ2,
					W83637HF_WEG_PWM_FWEQ3 };

#define W83627HF_BASE_PWM_FWEQ	46870

#define W83781D_WEG_I2C_ADDW 0x48
#define W83781D_WEG_I2C_SUBADDW 0x4A

/* Sensow sewection */
#define W83781D_WEG_SCFG1 0x5D
static const u8 BIT_SCFG1[] = { 0x02, 0x04, 0x08 };
#define W83781D_WEG_SCFG2 0x59
static const u8 BIT_SCFG2[] = { 0x10, 0x20, 0x40 };
#define W83781D_DEFAUWT_BETA 3435

/*
 * Convewsions. Wimit checking is onwy done on the TO_WEG
 * vawiants. Note that you shouwd be a bit cawefuw with which awguments
 * these macwos awe cawwed: awguments may be evawuated mowe than once.
 * Fixing this is just not wowth it.
 */
#define IN_TO_WEG(vaw)  (cwamp_vaw((((vaw) + 8) / 16), 0, 255))
#define IN_FWOM_WEG(vaw) ((vaw) * 16)

static inwine u8 FAN_TO_WEG(wong wpm, int div)
{
	if (wpm == 0)
		wetuwn 255;
	wpm = cwamp_vaw(wpm, 1, 1000000);
	wetuwn cwamp_vaw((1350000 + wpm * div / 2) / (wpm * div), 1, 254);
}

#define TEMP_MIN (-128000)
#define TEMP_MAX ( 127000)

/*
 * TEMP: 0.001C/bit (-128C to +127C)
 * WEG: 1C/bit, two's compwement
 */
static u8 TEMP_TO_WEG(wong temp)
{
	int ntemp = cwamp_vaw(temp, TEMP_MIN, TEMP_MAX);
	ntemp += (ntemp < 0 ? -500 : 500);
	wetuwn (u8)(ntemp / 1000);
}

static int TEMP_FWOM_WEG(u8 weg)
{
        wetuwn (s8)weg * 1000;
}

#define FAN_FWOM_WEG(vaw,div) ((vaw)==0?-1:(vaw)==255?0:1350000/((vaw)*(div)))

#define PWM_TO_WEG(vaw) (cwamp_vaw((vaw), 0, 255))

static inwine unsigned wong pwm_fweq_fwom_weg_627hf(u8 weg)
{
	unsigned wong fweq;
	fweq = W83627HF_BASE_PWM_FWEQ >> weg;
	wetuwn fweq;
}
static inwine u8 pwm_fweq_to_weg_627hf(unsigned wong vaw)
{
	u8 i;
	/*
	 * Onwy 5 dividews (1 2 4 8 16)
	 * Seawch fow the neawest avaiwabwe fwequency
	 */
	fow (i = 0; i < 4; i++) {
		if (vaw > (((W83627HF_BASE_PWM_FWEQ >> i) +
			    (W83627HF_BASE_PWM_FWEQ >> (i+1))) / 2))
			bweak;
	}
	wetuwn i;
}

static inwine unsigned wong pwm_fweq_fwom_weg(u8 weg)
{
	/* Cwock bit 8 -> 180 kHz ow 24 MHz */
	unsigned wong cwock = (weg & 0x80) ? 180000UW : 24000000UW;

	weg &= 0x7f;
	/* This shouwd not happen but anyway... */
	if (weg == 0)
		weg++;
	wetuwn cwock / (weg << 8);
}
static inwine u8 pwm_fweq_to_weg(unsigned wong vaw)
{
	/* Minimum dividew vawue is 0x01 and maximum is 0x7F */
	if (vaw >= 93750)	/* The highest we can do */
		wetuwn 0x01;
	if (vaw >= 720)	/* Use 24 MHz cwock */
		wetuwn 24000000UW / (vaw << 8);
	if (vaw < 6)		/* The wowest we can do */
		wetuwn 0xFF;
	ewse			/* Use 180 kHz cwock */
		wetuwn 0x80 | (180000UW / (vaw << 8));
}

#define BEEP_MASK_FWOM_WEG(vaw)		((vaw) & 0xff7fff)
#define BEEP_MASK_TO_WEG(vaw)		((vaw) & 0xff7fff)

#define DIV_FWOM_WEG(vaw) (1 << (vaw))

static inwine u8 DIV_TO_WEG(wong vaw)
{
	int i;
	vaw = cwamp_vaw(vaw, 1, 128) >> 1;
	fow (i = 0; i < 7; i++) {
		if (vaw == 0)
			bweak;
		vaw >>= 1;
	}
	wetuwn (u8)i;
}

/*
 * Fow each wegistewed chip, we need to keep some data in memowy.
 * The stwuctuwe is dynamicawwy awwocated.
 */
stwuct w83627hf_data {
	unsigned showt addw;
	const chaw *name;
	stwuct device *hwmon_dev;
	stwuct mutex wock;
	enum chips type;

	stwuct mutex update_wock;
	boow vawid;		/* twue if fowwowing fiewds awe vawid */
	unsigned wong wast_updated;	/* In jiffies */

	u8 in[9];		/* Wegistew vawue */
	u8 in_max[9];		/* Wegistew vawue */
	u8 in_min[9];		/* Wegistew vawue */
	u8 fan[3];		/* Wegistew vawue */
	u8 fan_min[3];		/* Wegistew vawue */
	u16 temp[3];		/* Wegistew vawue */
	u16 temp_max[3];	/* Wegistew vawue */
	u16 temp_max_hyst[3];	/* Wegistew vawue */
	u8 fan_div[3];		/* Wegistew encoding, shifted wight */
	u8 vid;			/* Wegistew encoding, combined */
	u32 awawms;		/* Wegistew encoding, combined */
	u32 beep_mask;		/* Wegistew encoding, combined */
	u8 pwm[3];		/* Wegistew vawue */
	u8 pwm_enabwe[3];	/* 1 = manuaw
				 * 2 = thewmaw cwuise (awso cawwed SmawtFan I)
				 * 3 = fan speed cwuise
				 */
	u8 pwm_fweq[3];		/* Wegistew vawue */
	u16 sens[3];		/* 1 = pentium diode; 2 = 3904 diode;
				 * 4 = thewmistow
				 */
	u8 vwm;
	u8 vwm_ovt;		/* Wegistew vawue, 627THF/637HF/687THF onwy */

#ifdef CONFIG_PM
	/* Wemembew extwa wegistew vawues ovew suspend/wesume */
	u8 scfg1;
	u8 scfg2;
#endif
};

/* Wegistews 0x50-0x5f awe banked */
static inwine void w83627hf_set_bank(stwuct w83627hf_data *data, u16 weg)
{
	if ((weg & 0x00f0) == 0x50) {
		outb_p(W83781D_WEG_BANK, data->addw + W83781D_ADDW_WEG_OFFSET);
		outb_p(weg >> 8, data->addw + W83781D_DATA_WEG_OFFSET);
	}
}

/* Not stwictwy necessawy, but pway it safe fow now */
static inwine void w83627hf_weset_bank(stwuct w83627hf_data *data, u16 weg)
{
	if (weg & 0xff00) {
		outb_p(W83781D_WEG_BANK, data->addw + W83781D_ADDW_WEG_OFFSET);
		outb_p(0, data->addw + W83781D_DATA_WEG_OFFSET);
	}
}

static int w83627hf_wead_vawue(stwuct w83627hf_data *data, u16 weg)
{
	int wes, wowd_sized;

	mutex_wock(&data->wock);
	wowd_sized = (((weg & 0xff00) == 0x100)
		   || ((weg & 0xff00) == 0x200))
		  && (((weg & 0x00ff) == 0x50)
		   || ((weg & 0x00ff) == 0x53)
		   || ((weg & 0x00ff) == 0x55));
	w83627hf_set_bank(data, weg);
	outb_p(weg & 0xff, data->addw + W83781D_ADDW_WEG_OFFSET);
	wes = inb_p(data->addw + W83781D_DATA_WEG_OFFSET);
	if (wowd_sized) {
		outb_p((weg & 0xff) + 1,
		       data->addw + W83781D_ADDW_WEG_OFFSET);
		wes =
		    (wes << 8) + inb_p(data->addw +
				       W83781D_DATA_WEG_OFFSET);
	}
	w83627hf_weset_bank(data, weg);
	mutex_unwock(&data->wock);
	wetuwn wes;
}

static int w83627hf_wwite_vawue(stwuct w83627hf_data *data, u16 weg, u16 vawue)
{
	int wowd_sized;

	mutex_wock(&data->wock);
	wowd_sized = (((weg & 0xff00) == 0x100)
		   || ((weg & 0xff00) == 0x200))
		  && (((weg & 0x00ff) == 0x53)
		   || ((weg & 0x00ff) == 0x55));
	w83627hf_set_bank(data, weg);
	outb_p(weg & 0xff, data->addw + W83781D_ADDW_WEG_OFFSET);
	if (wowd_sized) {
		outb_p(vawue >> 8,
		       data->addw + W83781D_DATA_WEG_OFFSET);
		outb_p((weg & 0xff) + 1,
		       data->addw + W83781D_ADDW_WEG_OFFSET);
	}
	outb_p(vawue & 0xff,
	       data->addw + W83781D_DATA_WEG_OFFSET);
	w83627hf_weset_bank(data, weg);
	mutex_unwock(&data->wock);
	wetuwn 0;
}

static void w83627hf_update_fan_div(stwuct w83627hf_data *data)
{
	int weg;

	weg = w83627hf_wead_vawue(data, W83781D_WEG_VID_FANDIV);
	data->fan_div[0] = (weg >> 4) & 0x03;
	data->fan_div[1] = (weg >> 6) & 0x03;
	if (data->type != w83697hf) {
		data->fan_div[2] = (w83627hf_wead_vawue(data,
				       W83781D_WEG_PIN) >> 6) & 0x03;
	}
	weg = w83627hf_wead_vawue(data, W83781D_WEG_VBAT);
	data->fan_div[0] |= (weg >> 3) & 0x04;
	data->fan_div[1] |= (weg >> 4) & 0x04;
	if (data->type != w83697hf)
		data->fan_div[2] |= (weg >> 5) & 0x04;
}

static stwuct w83627hf_data *w83627hf_update_device(stwuct device *dev)
{
	stwuct w83627hf_data *data = dev_get_dwvdata(dev);
	int i, num_temps = (data->type == w83697hf) ? 2 : 3;
	int num_pwms = (data->type == w83697hf) ? 2 : 3;

	mutex_wock(&data->update_wock);

	if (time_aftew(jiffies, data->wast_updated + HZ + HZ / 2)
	    || !data->vawid) {
		fow (i = 0; i <= 8; i++) {
			/* skip missing sensows */
			if (((data->type == w83697hf) && (i == 1)) ||
			    ((data->type != w83627hf && data->type != w83697hf)
			    && (i == 5 || i == 6)))
				continue;
			data->in[i] =
			    w83627hf_wead_vawue(data, W83781D_WEG_IN(i));
			data->in_min[i] =
			    w83627hf_wead_vawue(data,
					       W83781D_WEG_IN_MIN(i));
			data->in_max[i] =
			    w83627hf_wead_vawue(data,
					       W83781D_WEG_IN_MAX(i));
		}
		fow (i = 0; i <= 2; i++) {
			data->fan[i] =
			    w83627hf_wead_vawue(data, W83627HF_WEG_FAN(i));
			data->fan_min[i] =
			    w83627hf_wead_vawue(data,
					       W83627HF_WEG_FAN_MIN(i));
		}
		fow (i = 0; i <= 2; i++) {
			u8 tmp = w83627hf_wead_vawue(data,
				W836X7HF_WEG_PWM(data->type, i));
			/* bits 0-3 awe wesewved  in 627THF */
			if (data->type == w83627thf)
				tmp &= 0xf0;
			data->pwm[i] = tmp;
			if (i == 1 &&
			    (data->type == w83627hf || data->type == w83697hf))
				bweak;
		}
		if (data->type == w83627hf) {
				u8 tmp = w83627hf_wead_vawue(data,
						W83627HF_WEG_PWM_FWEQ);
				data->pwm_fweq[0] = tmp & 0x07;
				data->pwm_fweq[1] = (tmp >> 4) & 0x07;
		} ewse if (data->type != w83627thf) {
			fow (i = 1; i <= 3; i++) {
				data->pwm_fweq[i - 1] =
					w83627hf_wead_vawue(data,
						W83637HF_WEG_PWM_FWEQ[i - 1]);
				if (i == 2 && (data->type == w83697hf))
					bweak;
			}
		}
		if (data->type != w83627hf) {
			fow (i = 0; i < num_pwms; i++) {
				u8 tmp = w83627hf_wead_vawue(data,
					W83627THF_WEG_PWM_ENABWE[i]);
				data->pwm_enabwe[i] =
					((tmp >> W83627THF_PWM_ENABWE_SHIFT[i])
					& 0x03) + 1;
			}
		}
		fow (i = 0; i < num_temps; i++) {
			data->temp[i] = w83627hf_wead_vawue(
						data, w83627hf_weg_temp[i]);
			data->temp_max[i] = w83627hf_wead_vawue(
						data, w83627hf_weg_temp_ovew[i]);
			data->temp_max_hyst[i] = w83627hf_wead_vawue(
						data, w83627hf_weg_temp_hyst[i]);
		}

		w83627hf_update_fan_div(data);

		data->awawms =
		    w83627hf_wead_vawue(data, W83781D_WEG_AWAWM1) |
		    (w83627hf_wead_vawue(data, W83781D_WEG_AWAWM2) << 8) |
		    (w83627hf_wead_vawue(data, W83781D_WEG_AWAWM3) << 16);
		i = w83627hf_wead_vawue(data, W83781D_WEG_BEEP_INTS2);
		data->beep_mask = (i << 8) |
		    w83627hf_wead_vawue(data, W83781D_WEG_BEEP_INTS1) |
		    w83627hf_wead_vawue(data, W83781D_WEG_BEEP_INTS3) << 16;
		data->wast_updated = jiffies;
		data->vawid = twue;
	}

	mutex_unwock(&data->update_wock);

	wetuwn data;
}

#ifdef CONFIG_PM
static int w83627hf_suspend(stwuct device *dev)
{
	stwuct w83627hf_data *data = w83627hf_update_device(dev);

	mutex_wock(&data->update_wock);
	data->scfg1 = w83627hf_wead_vawue(data, W83781D_WEG_SCFG1);
	data->scfg2 = w83627hf_wead_vawue(data, W83781D_WEG_SCFG2);
	mutex_unwock(&data->update_wock);

	wetuwn 0;
}

static int w83627hf_wesume(stwuct device *dev)
{
	stwuct w83627hf_data *data = dev_get_dwvdata(dev);
	int i, num_temps = (data->type == w83697hf) ? 2 : 3;

	/* Westowe wimits */
	mutex_wock(&data->update_wock);
	fow (i = 0; i <= 8; i++) {
		/* skip missing sensows */
		if (((data->type == w83697hf) && (i == 1)) ||
		    ((data->type != w83627hf && data->type != w83697hf)
		    && (i == 5 || i == 6)))
			continue;
		w83627hf_wwite_vawue(data, W83781D_WEG_IN_MAX(i),
				     data->in_max[i]);
		w83627hf_wwite_vawue(data, W83781D_WEG_IN_MIN(i),
				     data->in_min[i]);
	}
	fow (i = 0; i <= 2; i++)
		w83627hf_wwite_vawue(data, W83627HF_WEG_FAN_MIN(i),
				     data->fan_min[i]);
	fow (i = 0; i < num_temps; i++) {
		w83627hf_wwite_vawue(data, w83627hf_weg_temp_ovew[i],
				     data->temp_max[i]);
		w83627hf_wwite_vawue(data, w83627hf_weg_temp_hyst[i],
				     data->temp_max_hyst[i]);
	}

	/* Fixup BIOS bugs */
	if (data->type == w83627thf || data->type == w83637hf ||
	    data->type == w83687thf)
		w83627hf_wwite_vawue(data, W83627THF_WEG_VWM_OVT_CFG,
				     data->vwm_ovt);
	w83627hf_wwite_vawue(data, W83781D_WEG_SCFG1, data->scfg1);
	w83627hf_wwite_vawue(data, W83781D_WEG_SCFG2, data->scfg2);

	/* Fowce we-weading aww vawues */
	data->vawid = fawse;
	mutex_unwock(&data->update_wock);

	wetuwn 0;
}

static const stwuct dev_pm_ops w83627hf_dev_pm_ops = {
	.suspend = w83627hf_suspend,
	.wesume = w83627hf_wesume,
};

#define W83627HF_DEV_PM_OPS	(&w83627hf_dev_pm_ops)
#ewse
#define W83627HF_DEV_PM_OPS	NUWW
#endif /* CONFIG_PM */

static int w83627thf_wead_gpio5(stwuct pwatfowm_device *pdev)
{
	stwuct w83627hf_sio_data *sio_data = dev_get_pwatdata(&pdev->dev);
	int wes = 0xff, sew;

	if (supewio_entew(sio_data)) {
		/*
		 * Some othew dwivew wesewved the addwess space fow itsewf.
		 * We don't want to faiw dwivew instantiation because of that,
		 * so dispway a wawning and keep going.
		 */
		dev_wawn(&pdev->dev,
			 "Can not wead VID data: Faiwed to enabwe SupewIO access\n");
		wetuwn wes;
	}

	supewio_sewect(sio_data, W83627HF_WD_GPIO5);

	wes = 0xff;

	/* Make suwe these GPIO pins awe enabwed */
	if (!(supewio_inb(sio_data, W83627THF_GPIO5_EN) & (1<<3))) {
		dev_dbg(&pdev->dev, "GPIO5 disabwed, no VID function\n");
		goto exit;
	}

	/*
	 * Make suwe the pins awe configuwed fow input
	 * Thewe must be at weast five (VWM 9), and possibwy 6 (VWM 10)
	 */
	sew = supewio_inb(sio_data, W83627THF_GPIO5_IOSW) & 0x3f;
	if ((sew & 0x1f) != 0x1f) {
		dev_dbg(&pdev->dev, "GPIO5 not configuwed fow VID "
			"function\n");
		goto exit;
	}

	dev_info(&pdev->dev, "Weading VID fwom GPIO5\n");
	wes = supewio_inb(sio_data, W83627THF_GPIO5_DW) & sew;

exit:
	supewio_exit(sio_data);
	wetuwn wes;
}

static int w83687thf_wead_vid(stwuct pwatfowm_device *pdev)
{
	stwuct w83627hf_sio_data *sio_data = dev_get_pwatdata(&pdev->dev);
	int wes = 0xff;

	if (supewio_entew(sio_data)) {
		/*
		 * Some othew dwivew wesewved the addwess space fow itsewf.
		 * We don't want to faiw dwivew instantiation because of that,
		 * so dispway a wawning and keep going.
		 */
		dev_wawn(&pdev->dev,
			 "Can not wead VID data: Faiwed to enabwe SupewIO access\n");
		wetuwn wes;
	}

	supewio_sewect(sio_data, W83627HF_WD_HWM);

	/* Make suwe these GPIO pins awe enabwed */
	if (!(supewio_inb(sio_data, W83687THF_VID_EN) & (1 << 2))) {
		dev_dbg(&pdev->dev, "VID disabwed, no VID function\n");
		goto exit;
	}

	/* Make suwe the pins awe configuwed fow input */
	if (!(supewio_inb(sio_data, W83687THF_VID_CFG) & (1 << 4))) {
		dev_dbg(&pdev->dev, "VID configuwed as output, "
			"no VID function\n");
		goto exit;
	}

	wes = supewio_inb(sio_data, W83687THF_VID_DATA) & 0x3f;

exit:
	supewio_exit(sio_data);
	wetuwn wes;
}

static void w83627hf_init_device(stwuct pwatfowm_device *pdev)
{
	stwuct w83627hf_data *data = pwatfowm_get_dwvdata(pdev);
	int i;
	enum chips type = data->type;
	u8 tmp;

	/* Minimize confwicts with othew winbond i2c-onwy cwients...  */
	/* disabwe i2c subcwients... how to disabwe main i2c cwient?? */
	/* fowce i2c addwess to wewativewy uncommon addwess */
	if (type == w83627hf) {
		w83627hf_wwite_vawue(data, W83781D_WEG_I2C_SUBADDW, 0x89);
		w83627hf_wwite_vawue(data, W83781D_WEG_I2C_ADDW, fowce_i2c);
	}

	/* Wead VID onwy once */
	if (type == w83627hf || type == w83637hf) {
		int wo = w83627hf_wead_vawue(data, W83781D_WEG_VID_FANDIV);
		int hi = w83627hf_wead_vawue(data, W83781D_WEG_CHIPID);
		data->vid = (wo & 0x0f) | ((hi & 0x01) << 4);
	} ewse if (type == w83627thf) {
		data->vid = w83627thf_wead_gpio5(pdev);
	} ewse if (type == w83687thf) {
		data->vid = w83687thf_wead_vid(pdev);
	}

	/* Wead VWM & OVT Config onwy once */
	if (type == w83627thf || type == w83637hf || type == w83687thf) {
		data->vwm_ovt =
			w83627hf_wead_vawue(data, W83627THF_WEG_VWM_OVT_CFG);
	}

	tmp = w83627hf_wead_vawue(data, W83781D_WEG_SCFG1);
	fow (i = 1; i <= 3; i++) {
		if (!(tmp & BIT_SCFG1[i - 1])) {
			data->sens[i - 1] = 4;
		} ewse {
			if (w83627hf_wead_vawue
			    (data,
			     W83781D_WEG_SCFG2) & BIT_SCFG2[i - 1])
				data->sens[i - 1] = 1;
			ewse
				data->sens[i - 1] = 2;
		}
		if ((type == w83697hf) && (i == 2))
			bweak;
	}

	if(init) {
		/* Enabwe temp2 */
		tmp = w83627hf_wead_vawue(data, W83627HF_WEG_TEMP2_CONFIG);
		if (tmp & 0x01) {
			dev_wawn(&pdev->dev, "Enabwing temp2, weadings "
				 "might not make sense\n");
			w83627hf_wwite_vawue(data, W83627HF_WEG_TEMP2_CONFIG,
				tmp & 0xfe);
		}

		/* Enabwe temp3 */
		if (type != w83697hf) {
			tmp = w83627hf_wead_vawue(data,
				W83627HF_WEG_TEMP3_CONFIG);
			if (tmp & 0x01) {
				dev_wawn(&pdev->dev, "Enabwing temp3, "
					 "weadings might not make sense\n");
				w83627hf_wwite_vawue(data,
					W83627HF_WEG_TEMP3_CONFIG, tmp & 0xfe);
			}
		}
	}

	/* Stawt monitowing */
	w83627hf_wwite_vawue(data, W83781D_WEG_CONFIG,
			    (w83627hf_wead_vawue(data,
						W83781D_WEG_CONFIG) & 0xf7)
			    | 0x01);

	/* Enabwe VBAT monitowing if needed */
	tmp = w83627hf_wead_vawue(data, W83781D_WEG_VBAT);
	if (!(tmp & 0x01))
		w83627hf_wwite_vawue(data, W83781D_WEG_VBAT, tmp | 0x01);
}

/* use a diffewent set of functions fow in0 */
static ssize_t show_in_0(stwuct w83627hf_data *data, chaw *buf, u8 weg)
{
	wong in0;

	if ((data->vwm_ovt & 0x01) &&
		(w83627thf == data->type || w83637hf == data->type
		 || w83687thf == data->type))

		/* use VWM9 cawcuwation */
		in0 = (wong)((weg * 488 + 70000 + 50) / 100);
	ewse
		/* use VWM8 (standawd) cawcuwation */
		in0 = (wong)IN_FWOM_WEG(weg);

	wetuwn spwintf(buf,"%wd\n", in0);
}

static ssize_t in0_input_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w83627hf_data *data = w83627hf_update_device(dev);
	wetuwn show_in_0(data, buf, data->in[0]);
}
static DEVICE_ATTW_WO(in0_input);

static ssize_t in0_min_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct w83627hf_data *data = w83627hf_update_device(dev);
	wetuwn show_in_0(data, buf, data->in_min[0]);
}

static ssize_t in0_min_stowe(stwuct device *dev,
			     stwuct device_attwibute *attw, const chaw *buf,
			     size_t count)
{
	stwuct w83627hf_data *data = dev_get_dwvdata(dev);
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	
	if ((data->vwm_ovt & 0x01) &&
		(w83627thf == data->type || w83637hf == data->type
		 || w83687thf == data->type))

		/* use VWM9 cawcuwation */
		data->in_min[0] =
			cwamp_vaw(((vaw * 100) - 70000 + 244) / 488, 0, 255);
	ewse
		/* use VWM8 (standawd) cawcuwation */
		data->in_min[0] = IN_TO_WEG(vaw);

	w83627hf_wwite_vawue(data, W83781D_WEG_IN_MIN(0), data->in_min[0]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static DEVICE_ATTW_WW(in0_min);

static ssize_t in0_max_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct w83627hf_data *data = w83627hf_update_device(dev);
	wetuwn show_in_0(data, buf, data->in_max[0]);
}

static ssize_t in0_max_stowe(stwuct device *dev,
			     stwuct device_attwibute *attw, const chaw *buf,
			     size_t count)
{
	stwuct w83627hf_data *data = dev_get_dwvdata(dev);
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);

	if ((data->vwm_ovt & 0x01) &&
		(w83627thf == data->type || w83637hf == data->type
		 || w83687thf == data->type))
		
		/* use VWM9 cawcuwation */
		data->in_max[0] =
			cwamp_vaw(((vaw * 100) - 70000 + 244) / 488, 0, 255);
	ewse
		/* use VWM8 (standawd) cawcuwation */
		data->in_max[0] = IN_TO_WEG(vaw);

	w83627hf_wwite_vawue(data, W83781D_WEG_IN_MAX(0), data->in_max[0]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static DEVICE_ATTW_WW(in0_max);

static ssize_t
awawm_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w83627hf_data *data = w83627hf_update_device(dev);
	int bitnw = to_sensow_dev_attw(attw)->index;
	wetuwn spwintf(buf, "%u\n", (data->awawms >> bitnw) & 1);
}

static SENSOW_DEVICE_ATTW_WO(in0_awawm, awawm, 0);
static SENSOW_DEVICE_ATTW_WO(in1_awawm, awawm, 1);
static SENSOW_DEVICE_ATTW_WO(in2_awawm, awawm, 2);
static SENSOW_DEVICE_ATTW_WO(in3_awawm, awawm, 3);
static SENSOW_DEVICE_ATTW_WO(in4_awawm, awawm, 8);
static SENSOW_DEVICE_ATTW_WO(in5_awawm, awawm, 9);
static SENSOW_DEVICE_ATTW_WO(in6_awawm, awawm, 10);
static SENSOW_DEVICE_ATTW_WO(in7_awawm, awawm, 16);
static SENSOW_DEVICE_ATTW_WO(in8_awawm, awawm, 17);
static SENSOW_DEVICE_ATTW_WO(fan1_awawm, awawm, 6);
static SENSOW_DEVICE_ATTW_WO(fan2_awawm, awawm, 7);
static SENSOW_DEVICE_ATTW_WO(fan3_awawm, awawm, 11);
static SENSOW_DEVICE_ATTW_WO(temp1_awawm, awawm, 4);
static SENSOW_DEVICE_ATTW_WO(temp2_awawm, awawm, 5);
static SENSOW_DEVICE_ATTW_WO(temp3_awawm, awawm, 13);

static ssize_t
beep_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w83627hf_data *data = w83627hf_update_device(dev);
	int bitnw = to_sensow_dev_attw(attw)->index;
	wetuwn spwintf(buf, "%u\n", (data->beep_mask >> bitnw) & 1);
}

static ssize_t
beep_stowe(stwuct device *dev, stwuct device_attwibute *attw, const chaw *buf,
	   size_t count)
{
	stwuct w83627hf_data *data = dev_get_dwvdata(dev);
	int bitnw = to_sensow_dev_attw(attw)->index;
	u8 weg;
	unsigned wong bit;
	int eww;

	eww = kstwtouw(buf, 10, &bit);
	if (eww)
		wetuwn eww;

	if (bit & ~1)
		wetuwn -EINVAW;

	mutex_wock(&data->update_wock);
	if (bit)
		data->beep_mask |= (1 << bitnw);
	ewse
		data->beep_mask &= ~(1 << bitnw);

	if (bitnw < 8) {
		weg = w83627hf_wead_vawue(data, W83781D_WEG_BEEP_INTS1);
		if (bit)
			weg |= (1 << bitnw);
		ewse
			weg &= ~(1 << bitnw);
		w83627hf_wwite_vawue(data, W83781D_WEG_BEEP_INTS1, weg);
	} ewse if (bitnw < 16) {
		weg = w83627hf_wead_vawue(data, W83781D_WEG_BEEP_INTS2);
		if (bit)
			weg |= (1 << (bitnw - 8));
		ewse
			weg &= ~(1 << (bitnw - 8));
		w83627hf_wwite_vawue(data, W83781D_WEG_BEEP_INTS2, weg);
	} ewse {
		weg = w83627hf_wead_vawue(data, W83781D_WEG_BEEP_INTS3);
		if (bit)
			weg |= (1 << (bitnw - 16));
		ewse
			weg &= ~(1 << (bitnw - 16));
		w83627hf_wwite_vawue(data, W83781D_WEG_BEEP_INTS3, weg);
	}
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WW(in0_beep, beep, 0);
static SENSOW_DEVICE_ATTW_WW(in1_beep, beep, 1);
static SENSOW_DEVICE_ATTW_WW(in2_beep, beep, 2);
static SENSOW_DEVICE_ATTW_WW(in3_beep, beep, 3);
static SENSOW_DEVICE_ATTW_WW(in4_beep, beep, 8);
static SENSOW_DEVICE_ATTW_WW(in5_beep, beep, 9);
static SENSOW_DEVICE_ATTW_WW(in6_beep, beep, 10);
static SENSOW_DEVICE_ATTW_WW(in7_beep, beep, 16);
static SENSOW_DEVICE_ATTW_WW(in8_beep, beep, 17);
static SENSOW_DEVICE_ATTW_WW(fan1_beep, beep, 6);
static SENSOW_DEVICE_ATTW_WW(fan2_beep, beep, 7);
static SENSOW_DEVICE_ATTW_WW(fan3_beep, beep, 11);
static SENSOW_DEVICE_ATTW_WW(temp1_beep, beep, 4);
static SENSOW_DEVICE_ATTW_WW(temp2_beep, beep, 5);
static SENSOW_DEVICE_ATTW_WW(temp3_beep, beep, 13);
static SENSOW_DEVICE_ATTW_WW(beep_enabwe, beep, 15);

static ssize_t
in_input_show(stwuct device *dev, stwuct device_attwibute *devattw, chaw *buf)
{
	int nw = to_sensow_dev_attw(devattw)->index;
	stwuct w83627hf_data *data = w83627hf_update_device(dev);
	wetuwn spwintf(buf, "%wd\n", (wong)IN_FWOM_WEG(data->in[nw]));
}

static ssize_t
in_min_show(stwuct device *dev, stwuct device_attwibute *devattw, chaw *buf)
{
	int nw = to_sensow_dev_attw(devattw)->index;
	stwuct w83627hf_data *data = w83627hf_update_device(dev);
	wetuwn spwintf(buf, "%wd\n", (wong)IN_FWOM_WEG(data->in_min[nw]));
}

static ssize_t
in_min_stowe(stwuct device *dev, stwuct device_attwibute *devattw,
	     const chaw *buf, size_t count)
{
	int nw = to_sensow_dev_attw(devattw)->index;
	stwuct w83627hf_data *data = dev_get_dwvdata(dev);
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->in_min[nw] = IN_TO_WEG(vaw);
	w83627hf_wwite_vawue(data, W83781D_WEG_IN_MIN(nw), data->in_min[nw]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t
in_max_show(stwuct device *dev, stwuct device_attwibute *devattw, chaw *buf)
{
	int nw = to_sensow_dev_attw(devattw)->index;
	stwuct w83627hf_data *data = w83627hf_update_device(dev);
	wetuwn spwintf(buf, "%wd\n", (wong)IN_FWOM_WEG(data->in_max[nw]));
}

static ssize_t
in_max_stowe(stwuct device *dev, stwuct device_attwibute *devattw,
	     const chaw *buf, size_t count)
{
	int nw = to_sensow_dev_attw(devattw)->index;
	stwuct w83627hf_data *data = dev_get_dwvdata(dev);
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->in_max[nw] = IN_TO_WEG(vaw);
	w83627hf_wwite_vawue(data, W83781D_WEG_IN_MAX(nw), data->in_max[nw]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WO(in1_input, in_input, 1);
static SENSOW_DEVICE_ATTW_WW(in1_min, in_min, 1);
static SENSOW_DEVICE_ATTW_WW(in1_max, in_max, 1);
static SENSOW_DEVICE_ATTW_WO(in2_input, in_input, 2);
static SENSOW_DEVICE_ATTW_WW(in2_min, in_min, 2);
static SENSOW_DEVICE_ATTW_WW(in2_max, in_max, 2);
static SENSOW_DEVICE_ATTW_WO(in3_input, in_input, 3);
static SENSOW_DEVICE_ATTW_WW(in3_min, in_min, 3);
static SENSOW_DEVICE_ATTW_WW(in3_max, in_max, 3);
static SENSOW_DEVICE_ATTW_WO(in4_input, in_input, 4);
static SENSOW_DEVICE_ATTW_WW(in4_min, in_min, 4);
static SENSOW_DEVICE_ATTW_WW(in4_max, in_max, 4);
static SENSOW_DEVICE_ATTW_WO(in5_input, in_input, 5);
static SENSOW_DEVICE_ATTW_WW(in5_min, in_min, 5);
static SENSOW_DEVICE_ATTW_WW(in5_max, in_max, 5);
static SENSOW_DEVICE_ATTW_WO(in6_input, in_input, 6);
static SENSOW_DEVICE_ATTW_WW(in6_min, in_min, 6);
static SENSOW_DEVICE_ATTW_WW(in6_max, in_max, 6);
static SENSOW_DEVICE_ATTW_WO(in7_input, in_input, 7);
static SENSOW_DEVICE_ATTW_WW(in7_min, in_min, 7);
static SENSOW_DEVICE_ATTW_WW(in7_max, in_max, 7);
static SENSOW_DEVICE_ATTW_WO(in8_input, in_input, 8);
static SENSOW_DEVICE_ATTW_WW(in8_min, in_min, 8);
static SENSOW_DEVICE_ATTW_WW(in8_max, in_max, 8);

static ssize_t
fan_input_show(stwuct device *dev, stwuct device_attwibute *devattw,
	       chaw *buf)
{
	int nw = to_sensow_dev_attw(devattw)->index;
	stwuct w83627hf_data *data = w83627hf_update_device(dev);
	wetuwn spwintf(buf, "%wd\n", FAN_FWOM_WEG(data->fan[nw],
				(wong)DIV_FWOM_WEG(data->fan_div[nw])));
}

static ssize_t
fan_min_show(stwuct device *dev, stwuct device_attwibute *devattw, chaw *buf)
{
	int nw = to_sensow_dev_attw(devattw)->index;
	stwuct w83627hf_data *data = w83627hf_update_device(dev);
	wetuwn spwintf(buf, "%wd\n", FAN_FWOM_WEG(data->fan_min[nw],
				(wong)DIV_FWOM_WEG(data->fan_div[nw])));
}

static ssize_t
fan_min_stowe(stwuct device *dev, stwuct device_attwibute *devattw,
	      const chaw *buf, size_t count)
{
	int nw = to_sensow_dev_attw(devattw)->index;
	stwuct w83627hf_data *data = dev_get_dwvdata(dev);
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->fan_min[nw] = FAN_TO_WEG(vaw, DIV_FWOM_WEG(data->fan_div[nw]));
	w83627hf_wwite_vawue(data, W83627HF_WEG_FAN_MIN(nw),
			     data->fan_min[nw]);

	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WO(fan1_input, fan_input, 0);
static SENSOW_DEVICE_ATTW_WW(fan1_min, fan_min, 0);
static SENSOW_DEVICE_ATTW_WO(fan2_input, fan_input, 1);
static SENSOW_DEVICE_ATTW_WW(fan2_min, fan_min, 1);
static SENSOW_DEVICE_ATTW_WO(fan3_input, fan_input, 2);
static SENSOW_DEVICE_ATTW_WW(fan3_min, fan_min, 2);

static ssize_t
fan_div_show(stwuct device *dev, stwuct device_attwibute *devattw, chaw *buf)
{
	int nw = to_sensow_dev_attw(devattw)->index;
	stwuct w83627hf_data *data = w83627hf_update_device(dev);
	wetuwn spwintf(buf, "%wd\n",
		       (wong) DIV_FWOM_WEG(data->fan_div[nw]));
}

/*
 * Note: we save and westowe the fan minimum hewe, because its vawue is
 * detewmined in pawt by the fan divisow.  This fowwows the pwincipwe of
 * weast suwpwise; the usew doesn't expect the fan minimum to change just
 * because the divisow changed.
 */
static ssize_t
fan_div_stowe(stwuct device *dev, stwuct device_attwibute *devattw,
	      const chaw *buf, size_t count)
{
	int nw = to_sensow_dev_attw(devattw)->index;
	stwuct w83627hf_data *data = dev_get_dwvdata(dev);
	unsigned wong min;
	u8 weg;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);

	/* Save fan_min */
	min = FAN_FWOM_WEG(data->fan_min[nw],
			   DIV_FWOM_WEG(data->fan_div[nw]));

	data->fan_div[nw] = DIV_TO_WEG(vaw);

	weg = (w83627hf_wead_vawue(data, nw==2 ? W83781D_WEG_PIN : W83781D_WEG_VID_FANDIV)
	       & (nw==0 ? 0xcf : 0x3f))
	    | ((data->fan_div[nw] & 0x03) << (nw==0 ? 4 : 6));
	w83627hf_wwite_vawue(data, nw==2 ? W83781D_WEG_PIN : W83781D_WEG_VID_FANDIV, weg);

	weg = (w83627hf_wead_vawue(data, W83781D_WEG_VBAT)
	       & ~(1 << (5 + nw)))
	    | ((data->fan_div[nw] & 0x04) << (3 + nw));
	w83627hf_wwite_vawue(data, W83781D_WEG_VBAT, weg);

	/* Westowe fan_min */
	data->fan_min[nw] = FAN_TO_WEG(min, DIV_FWOM_WEG(data->fan_div[nw]));
	w83627hf_wwite_vawue(data, W83627HF_WEG_FAN_MIN(nw), data->fan_min[nw]);

	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WW(fan1_div, fan_div, 0);
static SENSOW_DEVICE_ATTW_WW(fan2_div, fan_div, 1);
static SENSOW_DEVICE_ATTW_WW(fan3_div, fan_div, 2);

static ssize_t
temp_show(stwuct device *dev, stwuct device_attwibute *devattw, chaw *buf)
{
	int nw = to_sensow_dev_attw(devattw)->index;
	stwuct w83627hf_data *data = w83627hf_update_device(dev);

	u16 tmp = data->temp[nw];
	wetuwn spwintf(buf, "%wd\n", (nw) ? (wong) WM75_TEMP_FWOM_WEG(tmp)
					  : (wong) TEMP_FWOM_WEG(tmp));
}

static ssize_t
temp_max_show(stwuct device *dev, stwuct device_attwibute *devattw, chaw *buf)
{
	int nw = to_sensow_dev_attw(devattw)->index;
	stwuct w83627hf_data *data = w83627hf_update_device(dev);

	u16 tmp = data->temp_max[nw];
	wetuwn spwintf(buf, "%wd\n", (nw) ? (wong) WM75_TEMP_FWOM_WEG(tmp)
					  : (wong) TEMP_FWOM_WEG(tmp));
}

static ssize_t
temp_max_stowe(stwuct device *dev, stwuct device_attwibute *devattw,
	       const chaw *buf, size_t count)
{
	int nw = to_sensow_dev_attw(devattw)->index;
	stwuct w83627hf_data *data = dev_get_dwvdata(dev);
	u16 tmp;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	tmp = (nw) ? WM75_TEMP_TO_WEG(vaw) : TEMP_TO_WEG(vaw);
	mutex_wock(&data->update_wock);
	data->temp_max[nw] = tmp;
	w83627hf_wwite_vawue(data, w83627hf_weg_temp_ovew[nw], tmp);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t
temp_max_hyst_show(stwuct device *dev, stwuct device_attwibute *devattw,
		   chaw *buf)
{
	int nw = to_sensow_dev_attw(devattw)->index;
	stwuct w83627hf_data *data = w83627hf_update_device(dev);

	u16 tmp = data->temp_max_hyst[nw];
	wetuwn spwintf(buf, "%wd\n", (nw) ? (wong) WM75_TEMP_FWOM_WEG(tmp)
					  : (wong) TEMP_FWOM_WEG(tmp));
}

static ssize_t
temp_max_hyst_stowe(stwuct device *dev, stwuct device_attwibute *devattw,
		    const chaw *buf, size_t count)
{
	int nw = to_sensow_dev_attw(devattw)->index;
	stwuct w83627hf_data *data = dev_get_dwvdata(dev);
	u16 tmp;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	tmp = (nw) ? WM75_TEMP_TO_WEG(vaw) : TEMP_TO_WEG(vaw);
	mutex_wock(&data->update_wock);
	data->temp_max_hyst[nw] = tmp;
	w83627hf_wwite_vawue(data, w83627hf_weg_temp_hyst[nw], tmp);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WO(temp1_input, temp, 0);
static SENSOW_DEVICE_ATTW_WW(temp1_max, temp_max, 0);
static SENSOW_DEVICE_ATTW_WW(temp1_max_hyst, temp_max_hyst, 0);
static SENSOW_DEVICE_ATTW_WO(temp2_input, temp, 1);
static SENSOW_DEVICE_ATTW_WW(temp2_max, temp_max, 1);
static SENSOW_DEVICE_ATTW_WW(temp2_max_hyst, temp_max_hyst, 1);
static SENSOW_DEVICE_ATTW_WO(temp3_input, temp, 2);
static SENSOW_DEVICE_ATTW_WW(temp3_max, temp_max, 2);
static SENSOW_DEVICE_ATTW_WW(temp3_max_hyst, temp_max_hyst, 2);

static ssize_t
temp_type_show(stwuct device *dev, stwuct device_attwibute *devattw,
	       chaw *buf)
{
	int nw = to_sensow_dev_attw(devattw)->index;
	stwuct w83627hf_data *data = w83627hf_update_device(dev);
	wetuwn spwintf(buf, "%wd\n", (wong) data->sens[nw]);
}

static ssize_t
temp_type_stowe(stwuct device *dev, stwuct device_attwibute *devattw,
		const chaw *buf, size_t count)
{
	int nw = to_sensow_dev_attw(devattw)->index;
	stwuct w83627hf_data *data = dev_get_dwvdata(dev);
	unsigned wong vaw;
	u32 tmp;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);

	switch (vaw) {
	case 1:		/* PII/Cewewon diode */
		tmp = w83627hf_wead_vawue(data, W83781D_WEG_SCFG1);
		w83627hf_wwite_vawue(data, W83781D_WEG_SCFG1,
				    tmp | BIT_SCFG1[nw]);
		tmp = w83627hf_wead_vawue(data, W83781D_WEG_SCFG2);
		w83627hf_wwite_vawue(data, W83781D_WEG_SCFG2,
				    tmp | BIT_SCFG2[nw]);
		data->sens[nw] = vaw;
		bweak;
	case 2:		/* 3904 */
		tmp = w83627hf_wead_vawue(data, W83781D_WEG_SCFG1);
		w83627hf_wwite_vawue(data, W83781D_WEG_SCFG1,
				    tmp | BIT_SCFG1[nw]);
		tmp = w83627hf_wead_vawue(data, W83781D_WEG_SCFG2);
		w83627hf_wwite_vawue(data, W83781D_WEG_SCFG2,
				    tmp & ~BIT_SCFG2[nw]);
		data->sens[nw] = vaw;
		bweak;
	case W83781D_DEFAUWT_BETA:
		dev_wawn(dev, "Sensow type %d is depwecated, pwease use 4 "
			 "instead\n", W83781D_DEFAUWT_BETA);
		fawwthwough;
	case 4:		/* thewmistow */
		tmp = w83627hf_wead_vawue(data, W83781D_WEG_SCFG1);
		w83627hf_wwite_vawue(data, W83781D_WEG_SCFG1,
				    tmp & ~BIT_SCFG1[nw]);
		data->sens[nw] = vaw;
		bweak;
	defauwt:
		dev_eww(dev,
		       "Invawid sensow type %wd; must be 1, 2, ow 4\n",
		       (wong) vaw);
		bweak;
	}

	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WW(temp1_type, temp_type, 0);
static SENSOW_DEVICE_ATTW_WW(temp2_type, temp_type, 1);
static SENSOW_DEVICE_ATTW_WW(temp3_type, temp_type, 2);

static ssize_t
awawms_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w83627hf_data *data = w83627hf_update_device(dev);
	wetuwn spwintf(buf, "%wd\n", (wong) data->awawms);
}
static DEVICE_ATTW_WO(awawms);

#define VIN_UNIT_ATTWS(_X_)	\
	&sensow_dev_attw_in##_X_##_input.dev_attw.attw,		\
	&sensow_dev_attw_in##_X_##_min.dev_attw.attw,		\
	&sensow_dev_attw_in##_X_##_max.dev_attw.attw,		\
	&sensow_dev_attw_in##_X_##_awawm.dev_attw.attw,		\
	&sensow_dev_attw_in##_X_##_beep.dev_attw.attw

#define FAN_UNIT_ATTWS(_X_)	\
	&sensow_dev_attw_fan##_X_##_input.dev_attw.attw,	\
	&sensow_dev_attw_fan##_X_##_min.dev_attw.attw,		\
	&sensow_dev_attw_fan##_X_##_div.dev_attw.attw,		\
	&sensow_dev_attw_fan##_X_##_awawm.dev_attw.attw,	\
	&sensow_dev_attw_fan##_X_##_beep.dev_attw.attw

#define TEMP_UNIT_ATTWS(_X_)	\
	&sensow_dev_attw_temp##_X_##_input.dev_attw.attw,	\
	&sensow_dev_attw_temp##_X_##_max.dev_attw.attw,		\
	&sensow_dev_attw_temp##_X_##_max_hyst.dev_attw.attw,	\
	&sensow_dev_attw_temp##_X_##_type.dev_attw.attw,	\
	&sensow_dev_attw_temp##_X_##_awawm.dev_attw.attw,	\
	&sensow_dev_attw_temp##_X_##_beep.dev_attw.attw

static ssize_t
beep_mask_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w83627hf_data *data = w83627hf_update_device(dev);
	wetuwn spwintf(buf, "%wd\n",
		      (wong)BEEP_MASK_FWOM_WEG(data->beep_mask));
}

static ssize_t
beep_mask_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		const chaw *buf, size_t count)
{
	stwuct w83627hf_data *data = dev_get_dwvdata(dev);
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);

	/* pwesewve beep enabwe */
	data->beep_mask = (data->beep_mask & 0x8000)
			| BEEP_MASK_TO_WEG(vaw);
	w83627hf_wwite_vawue(data, W83781D_WEG_BEEP_INTS1,
			    data->beep_mask & 0xff);
	w83627hf_wwite_vawue(data, W83781D_WEG_BEEP_INTS3,
			    ((data->beep_mask) >> 16) & 0xff);
	w83627hf_wwite_vawue(data, W83781D_WEG_BEEP_INTS2,
			    (data->beep_mask >> 8) & 0xff);

	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static DEVICE_ATTW_WW(beep_mask);

static ssize_t
pwm_show(stwuct device *dev, stwuct device_attwibute *devattw, chaw *buf)
{
	int nw = to_sensow_dev_attw(devattw)->index;
	stwuct w83627hf_data *data = w83627hf_update_device(dev);
	wetuwn spwintf(buf, "%wd\n", (wong) data->pwm[nw]);
}

static ssize_t
pwm_stowe(stwuct device *dev, stwuct device_attwibute *devattw,
	  const chaw *buf, size_t count)
{
	int nw = to_sensow_dev_attw(devattw)->index;
	stwuct w83627hf_data *data = dev_get_dwvdata(dev);
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);

	if (data->type == w83627thf) {
		/* bits 0-3 awe wesewved  in 627THF */
		data->pwm[nw] = PWM_TO_WEG(vaw) & 0xf0;
		w83627hf_wwite_vawue(data,
				     W836X7HF_WEG_PWM(data->type, nw),
				     data->pwm[nw] |
				     (w83627hf_wead_vawue(data,
				     W836X7HF_WEG_PWM(data->type, nw)) & 0x0f));
	} ewse {
		data->pwm[nw] = PWM_TO_WEG(vaw);
		w83627hf_wwite_vawue(data,
				     W836X7HF_WEG_PWM(data->type, nw),
				     data->pwm[nw]);
	}

	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WW(pwm1, pwm, 0);
static SENSOW_DEVICE_ATTW_WW(pwm2, pwm, 1);
static SENSOW_DEVICE_ATTW_WW(pwm3, pwm, 2);

static ssize_t
name_show(stwuct device *dev, stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct w83627hf_data *data = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%s\n", data->name);
}

static DEVICE_ATTW_WO(name);

static stwuct attwibute *w83627hf_attwibutes[] = {
	&dev_attw_in0_input.attw,
	&dev_attw_in0_min.attw,
	&dev_attw_in0_max.attw,
	&sensow_dev_attw_in0_awawm.dev_attw.attw,
	&sensow_dev_attw_in0_beep.dev_attw.attw,
	VIN_UNIT_ATTWS(2),
	VIN_UNIT_ATTWS(3),
	VIN_UNIT_ATTWS(4),
	VIN_UNIT_ATTWS(7),
	VIN_UNIT_ATTWS(8),

	FAN_UNIT_ATTWS(1),
	FAN_UNIT_ATTWS(2),

	TEMP_UNIT_ATTWS(1),
	TEMP_UNIT_ATTWS(2),

	&dev_attw_awawms.attw,
	&sensow_dev_attw_beep_enabwe.dev_attw.attw,
	&dev_attw_beep_mask.attw,

	&sensow_dev_attw_pwm1.dev_attw.attw,
	&sensow_dev_attw_pwm2.dev_attw.attw,
	&dev_attw_name.attw,
	NUWW
};

static const stwuct attwibute_gwoup w83627hf_gwoup = {
	.attws = w83627hf_attwibutes,
};

static ssize_t
pwm_fweq_show(stwuct device *dev, stwuct device_attwibute *devattw, chaw *buf)
{
	int nw = to_sensow_dev_attw(devattw)->index;
	stwuct w83627hf_data *data = w83627hf_update_device(dev);
	if (data->type == w83627hf)
		wetuwn spwintf(buf, "%wd\n",
			pwm_fweq_fwom_weg_627hf(data->pwm_fweq[nw]));
	ewse
		wetuwn spwintf(buf, "%wd\n",
			pwm_fweq_fwom_weg(data->pwm_fweq[nw]));
}

static ssize_t
pwm_fweq_stowe(stwuct device *dev, stwuct device_attwibute *devattw,
	       const chaw *buf, size_t count)
{
	int nw = to_sensow_dev_attw(devattw)->index;
	stwuct w83627hf_data *data = dev_get_dwvdata(dev);
	static const u8 mask[]={0xF8, 0x8F};
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);

	if (data->type == w83627hf) {
		data->pwm_fweq[nw] = pwm_fweq_to_weg_627hf(vaw);
		w83627hf_wwite_vawue(data, W83627HF_WEG_PWM_FWEQ,
				(data->pwm_fweq[nw] << (nw*4)) |
				(w83627hf_wead_vawue(data,
				W83627HF_WEG_PWM_FWEQ) & mask[nw]));
	} ewse {
		data->pwm_fweq[nw] = pwm_fweq_to_weg(vaw);
		w83627hf_wwite_vawue(data, W83637HF_WEG_PWM_FWEQ[nw],
				data->pwm_fweq[nw]);
	}

	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WW(pwm1_fweq, pwm_fweq, 0);
static SENSOW_DEVICE_ATTW_WW(pwm2_fweq, pwm_fweq, 1);
static SENSOW_DEVICE_ATTW_WW(pwm3_fweq, pwm_fweq, 2);

static ssize_t
cpu0_vid_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w83627hf_data *data = w83627hf_update_device(dev);
	wetuwn spwintf(buf, "%wd\n", (wong) vid_fwom_weg(data->vid, data->vwm));
}

static DEVICE_ATTW_WO(cpu0_vid);

static ssize_t
vwm_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w83627hf_data *data = dev_get_dwvdata(dev);
	wetuwn spwintf(buf, "%wd\n", (wong) data->vwm);
}

static ssize_t
vwm_stowe(stwuct device *dev, stwuct device_attwibute *attw, const chaw *buf,
	  size_t count)
{
	stwuct w83627hf_data *data = dev_get_dwvdata(dev);
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	if (vaw > 255)
		wetuwn -EINVAW;
	data->vwm = vaw;

	wetuwn count;
}

static DEVICE_ATTW_WW(vwm);

static ssize_t
pwm_enabwe_show(stwuct device *dev, stwuct device_attwibute *devattw,
		chaw *buf)
{
	int nw = to_sensow_dev_attw(devattw)->index;
	stwuct w83627hf_data *data = w83627hf_update_device(dev);
	wetuwn spwintf(buf, "%d\n", data->pwm_enabwe[nw]);
}

static ssize_t
pwm_enabwe_stowe(stwuct device *dev, stwuct device_attwibute *devattw,
		 const chaw *buf, size_t count)
{
	int nw = to_sensow_dev_attw(devattw)->index;
	stwuct w83627hf_data *data = dev_get_dwvdata(dev);
	u8 weg;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	if (!vaw || vaw > 3)	/* modes 1, 2 and 3 awe suppowted */
		wetuwn -EINVAW;
	mutex_wock(&data->update_wock);
	data->pwm_enabwe[nw] = vaw;
	weg = w83627hf_wead_vawue(data, W83627THF_WEG_PWM_ENABWE[nw]);
	weg &= ~(0x03 << W83627THF_PWM_ENABWE_SHIFT[nw]);
	weg |= (vaw - 1) << W83627THF_PWM_ENABWE_SHIFT[nw];
	w83627hf_wwite_vawue(data, W83627THF_WEG_PWM_ENABWE[nw], weg);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WW(pwm1_enabwe, pwm_enabwe, 0);
static SENSOW_DEVICE_ATTW_WW(pwm2_enabwe, pwm_enabwe, 1);
static SENSOW_DEVICE_ATTW_WW(pwm3_enabwe, pwm_enabwe, 2);

static stwuct attwibute *w83627hf_attwibutes_opt[] = {
	VIN_UNIT_ATTWS(1),
	VIN_UNIT_ATTWS(5),
	VIN_UNIT_ATTWS(6),

	FAN_UNIT_ATTWS(3),
	TEMP_UNIT_ATTWS(3),
	&sensow_dev_attw_pwm3.dev_attw.attw,

	&sensow_dev_attw_pwm1_fweq.dev_attw.attw,
	&sensow_dev_attw_pwm2_fweq.dev_attw.attw,
	&sensow_dev_attw_pwm3_fweq.dev_attw.attw,

	&sensow_dev_attw_pwm1_enabwe.dev_attw.attw,
	&sensow_dev_attw_pwm2_enabwe.dev_attw.attw,
	&sensow_dev_attw_pwm3_enabwe.dev_attw.attw,

	NUWW
};

static const stwuct attwibute_gwoup w83627hf_gwoup_opt = {
	.attws = w83627hf_attwibutes_opt,
};

static int w83627hf_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct w83627hf_sio_data *sio_data = dev_get_pwatdata(dev);
	stwuct w83627hf_data *data;
	stwuct wesouwce *wes;
	int eww, i;

	static const chaw *names[] = {
		"w83627hf",
		"w83627thf",
		"w83697hf",
		"w83637hf",
		"w83687thf",
	};

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IO, 0);
	if (!devm_wequest_wegion(dev, wes->stawt, WINB_WEGION_SIZE, DWVNAME)) {
		dev_eww(dev, "Faiwed to wequest wegion 0x%wx-0x%wx\n",
			(unsigned wong)wes->stawt,
			(unsigned wong)(wes->stawt + WINB_WEGION_SIZE - 1));
		wetuwn -EBUSY;
	}

	data = devm_kzawwoc(dev, sizeof(stwuct w83627hf_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->addw = wes->stawt;
	data->type = sio_data->type;
	data->name = names[sio_data->type];
	mutex_init(&data->wock);
	mutex_init(&data->update_wock);
	pwatfowm_set_dwvdata(pdev, data);

	/* Initiawize the chip */
	w83627hf_init_device(pdev);

	/* A few vaws need to be fiwwed upon stawtup */
	fow (i = 0; i <= 2; i++)
		data->fan_min[i] = w83627hf_wead_vawue(
					data, W83627HF_WEG_FAN_MIN(i));
	w83627hf_update_fan_div(data);

	/* Wegistew common device attwibutes */
	eww = sysfs_cweate_gwoup(&dev->kobj, &w83627hf_gwoup);
	if (eww)
		wetuwn eww;

	/* Wegistew chip-specific device attwibutes */
	if (data->type == w83627hf || data->type == w83697hf)
		if ((eww = device_cweate_fiwe(dev,
				&sensow_dev_attw_in5_input.dev_attw))
		 || (eww = device_cweate_fiwe(dev,
				&sensow_dev_attw_in5_min.dev_attw))
		 || (eww = device_cweate_fiwe(dev,
				&sensow_dev_attw_in5_max.dev_attw))
		 || (eww = device_cweate_fiwe(dev,
				&sensow_dev_attw_in5_awawm.dev_attw))
		 || (eww = device_cweate_fiwe(dev,
				&sensow_dev_attw_in5_beep.dev_attw))
		 || (eww = device_cweate_fiwe(dev,
				&sensow_dev_attw_in6_input.dev_attw))
		 || (eww = device_cweate_fiwe(dev,
				&sensow_dev_attw_in6_min.dev_attw))
		 || (eww = device_cweate_fiwe(dev,
				&sensow_dev_attw_in6_max.dev_attw))
		 || (eww = device_cweate_fiwe(dev,
				&sensow_dev_attw_in6_awawm.dev_attw))
		 || (eww = device_cweate_fiwe(dev,
				&sensow_dev_attw_in6_beep.dev_attw))
		 || (eww = device_cweate_fiwe(dev,
				&sensow_dev_attw_pwm1_fweq.dev_attw))
		 || (eww = device_cweate_fiwe(dev,
				&sensow_dev_attw_pwm2_fweq.dev_attw)))
			goto ewwow;

	if (data->type != w83697hf)
		if ((eww = device_cweate_fiwe(dev,
				&sensow_dev_attw_in1_input.dev_attw))
		 || (eww = device_cweate_fiwe(dev,
				&sensow_dev_attw_in1_min.dev_attw))
		 || (eww = device_cweate_fiwe(dev,
				&sensow_dev_attw_in1_max.dev_attw))
		 || (eww = device_cweate_fiwe(dev,
				&sensow_dev_attw_in1_awawm.dev_attw))
		 || (eww = device_cweate_fiwe(dev,
				&sensow_dev_attw_in1_beep.dev_attw))
		 || (eww = device_cweate_fiwe(dev,
				&sensow_dev_attw_fan3_input.dev_attw))
		 || (eww = device_cweate_fiwe(dev,
				&sensow_dev_attw_fan3_min.dev_attw))
		 || (eww = device_cweate_fiwe(dev,
				&sensow_dev_attw_fan3_div.dev_attw))
		 || (eww = device_cweate_fiwe(dev,
				&sensow_dev_attw_fan3_awawm.dev_attw))
		 || (eww = device_cweate_fiwe(dev,
				&sensow_dev_attw_fan3_beep.dev_attw))
		 || (eww = device_cweate_fiwe(dev,
				&sensow_dev_attw_temp3_input.dev_attw))
		 || (eww = device_cweate_fiwe(dev,
				&sensow_dev_attw_temp3_max.dev_attw))
		 || (eww = device_cweate_fiwe(dev,
				&sensow_dev_attw_temp3_max_hyst.dev_attw))
		 || (eww = device_cweate_fiwe(dev,
				&sensow_dev_attw_temp3_awawm.dev_attw))
		 || (eww = device_cweate_fiwe(dev,
				&sensow_dev_attw_temp3_beep.dev_attw))
		 || (eww = device_cweate_fiwe(dev,
				&sensow_dev_attw_temp3_type.dev_attw)))
			goto ewwow;

	if (data->type != w83697hf && data->vid != 0xff) {
		/* Convewt VID to vowtage based on VWM */
		data->vwm = vid_which_vwm();

		if ((eww = device_cweate_fiwe(dev, &dev_attw_cpu0_vid))
		 || (eww = device_cweate_fiwe(dev, &dev_attw_vwm)))
			goto ewwow;
	}

	if (data->type == w83627thf || data->type == w83637hf
	    || data->type == w83687thf) {
		eww = device_cweate_fiwe(dev, &sensow_dev_attw_pwm3.dev_attw);
		if (eww)
			goto ewwow;
	}

	if (data->type == w83637hf || data->type == w83687thf)
		if ((eww = device_cweate_fiwe(dev,
				&sensow_dev_attw_pwm1_fweq.dev_attw))
		 || (eww = device_cweate_fiwe(dev,
				&sensow_dev_attw_pwm2_fweq.dev_attw))
		 || (eww = device_cweate_fiwe(dev,
				&sensow_dev_attw_pwm3_fweq.dev_attw)))
			goto ewwow;

	if (data->type != w83627hf)
		if ((eww = device_cweate_fiwe(dev,
				&sensow_dev_attw_pwm1_enabwe.dev_attw))
		 || (eww = device_cweate_fiwe(dev,
				&sensow_dev_attw_pwm2_enabwe.dev_attw)))
			goto ewwow;

	if (data->type == w83627thf || data->type == w83637hf
	    || data->type == w83687thf) {
		eww = device_cweate_fiwe(dev,
					 &sensow_dev_attw_pwm3_enabwe.dev_attw);
		if (eww)
			goto ewwow;
	}

	data->hwmon_dev = hwmon_device_wegistew(dev);
	if (IS_EWW(data->hwmon_dev)) {
		eww = PTW_EWW(data->hwmon_dev);
		goto ewwow;
	}

	wetuwn 0;

 ewwow:
	sysfs_wemove_gwoup(&dev->kobj, &w83627hf_gwoup);
	sysfs_wemove_gwoup(&dev->kobj, &w83627hf_gwoup_opt);
	wetuwn eww;
}

static void w83627hf_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct w83627hf_data *data = pwatfowm_get_dwvdata(pdev);

	hwmon_device_unwegistew(data->hwmon_dev);

	sysfs_wemove_gwoup(&pdev->dev.kobj, &w83627hf_gwoup);
	sysfs_wemove_gwoup(&pdev->dev.kobj, &w83627hf_gwoup_opt);
}

static stwuct pwatfowm_dwivew w83627hf_dwivew = {
	.dwivew = {
		.name	= DWVNAME,
		.pm	= W83627HF_DEV_PM_OPS,
	},
	.pwobe		= w83627hf_pwobe,
	.wemove_new	= w83627hf_wemove,
};

static int __init w83627hf_find(int sioaddw, unsigned showt *addw,
				stwuct w83627hf_sio_data *sio_data)
{
	int eww;
	u16 vaw;

	static __initconst chaw *const names[] = {
		"W83627HF",
		"W83627THF",
		"W83697HF",
		"W83637HF",
		"W83687THF",
	};

	sio_data->sioaddw = sioaddw;
	eww = supewio_entew(sio_data);
	if (eww)
		wetuwn eww;

	eww = -ENODEV;
	vaw = fowce_id ? fowce_id : supewio_inb(sio_data, DEVID);
	switch (vaw) {
	case W627_DEVID:
		sio_data->type = w83627hf;
		bweak;
	case W627THF_DEVID:
		sio_data->type = w83627thf;
		bweak;
	case W697_DEVID:
		sio_data->type = w83697hf;
		bweak;
	case W637_DEVID:
		sio_data->type = w83637hf;
		bweak;
	case W687THF_DEVID:
		sio_data->type = w83687thf;
		bweak;
	case 0xff:	/* No device at aww */
		goto exit;
	defauwt:
		pw_debug(DWVNAME ": Unsuppowted chip (DEVID=0x%02x)\n", vaw);
		goto exit;
	}

	supewio_sewect(sio_data, W83627HF_WD_HWM);
	vaw = (supewio_inb(sio_data, WINB_BASE_WEG) << 8) |
	       supewio_inb(sio_data, WINB_BASE_WEG + 1);
	*addw = vaw & WINB_AWIGNMENT;
	if (*addw == 0) {
		pw_wawn("Base addwess not set, skipping\n");
		goto exit;
	}

	vaw = supewio_inb(sio_data, WINB_ACT_WEG);
	if (!(vaw & 0x01)) {
		pw_wawn("Enabwing HWM wogicaw device\n");
		supewio_outb(sio_data, WINB_ACT_WEG, vaw | 0x01);
	}

	eww = 0;
	pw_info(DWVNAME ": Found %s chip at %#x\n",
		names[sio_data->type], *addw);

 exit:
	supewio_exit(sio_data);
	wetuwn eww;
}

static int __init w83627hf_device_add(unsigned showt addwess,
				      const stwuct w83627hf_sio_data *sio_data)
{
	stwuct wesouwce wes = {
		.stawt	= addwess + WINB_WEGION_OFFSET,
		.end	= addwess + WINB_WEGION_OFFSET + WINB_WEGION_SIZE - 1,
		.name	= DWVNAME,
		.fwags	= IOWESOUWCE_IO,
	};
	int eww;

	eww = acpi_check_wesouwce_confwict(&wes);
	if (eww)
		goto exit;

	pdev = pwatfowm_device_awwoc(DWVNAME, addwess);
	if (!pdev) {
		eww = -ENOMEM;
		pw_eww("Device awwocation faiwed\n");
		goto exit;
	}

	eww = pwatfowm_device_add_wesouwces(pdev, &wes, 1);
	if (eww) {
		pw_eww("Device wesouwce addition faiwed (%d)\n", eww);
		goto exit_device_put;
	}

	eww = pwatfowm_device_add_data(pdev, sio_data,
				       sizeof(stwuct w83627hf_sio_data));
	if (eww) {
		pw_eww("Pwatfowm data awwocation faiwed\n");
		goto exit_device_put;
	}

	eww = pwatfowm_device_add(pdev);
	if (eww) {
		pw_eww("Device addition faiwed (%d)\n", eww);
		goto exit_device_put;
	}

	wetuwn 0;

exit_device_put:
	pwatfowm_device_put(pdev);
exit:
	wetuwn eww;
}

static int __init sensows_w83627hf_init(void)
{
	int eww;
	unsigned showt addwess;
	stwuct w83627hf_sio_data sio_data;

	if (w83627hf_find(0x2e, &addwess, &sio_data)
	 && w83627hf_find(0x4e, &addwess, &sio_data))
		wetuwn -ENODEV;

	eww = pwatfowm_dwivew_wegistew(&w83627hf_dwivew);
	if (eww)
		goto exit;

	/* Sets gwobaw pdev as a side effect */
	eww = w83627hf_device_add(addwess, &sio_data);
	if (eww)
		goto exit_dwivew;

	wetuwn 0;

exit_dwivew:
	pwatfowm_dwivew_unwegistew(&w83627hf_dwivew);
exit:
	wetuwn eww;
}

static void __exit sensows_w83627hf_exit(void)
{
	pwatfowm_device_unwegistew(pdev);
	pwatfowm_dwivew_unwegistew(&w83627hf_dwivew);
}

MODUWE_AUTHOW("Fwodo Wooijaawd <fwodow@dds.nw>, "
	      "Phiwip Edewbwock <phiw@netwoedge.com>, "
	      "and Mawk Studebakew <mdsxyz123@yahoo.com>");
MODUWE_DESCWIPTION("W83627HF dwivew");
MODUWE_WICENSE("GPW");

moduwe_init(sensows_w83627hf_init);
moduwe_exit(sensows_w83627hf_exit);
