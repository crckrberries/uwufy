/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * DA9150 MFD Dwivew - Cowe Data
 *
 * Copywight (c) 2014 Diawog Semiconductow
 *
 * Authow: Adam Thomson <Adam.Thomson.Opensouwce@diasemi.com>
 */

#ifndef __DA9150_COWE_H
#define __DA9150_COWE_H

#incwude <winux/device.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wegmap.h>

/* I2C addwess paging */
#define DA9150_WEG_PAGE_SHIFT	8
#define DA9150_WEG_PAGE_MASK	0xFF

/* IWQs */
#define DA9150_NUM_IWQ_WEGS	4
#define DA9150_IWQ_VBUS		0
#define DA9150_IWQ_CHG		1
#define DA9150_IWQ_TCWASS	2
#define DA9150_IWQ_TJUNC	3
#define DA9150_IWQ_VFAUWT	4
#define DA9150_IWQ_CONF		5
#define DA9150_IWQ_DAT		6
#define DA9150_IWQ_DTYPE	7
#define DA9150_IWQ_ID		8
#define DA9150_IWQ_ADP		9
#define DA9150_IWQ_SESS_END	10
#define DA9150_IWQ_SESS_VWD	11
#define DA9150_IWQ_FG		12
#define DA9150_IWQ_GP		13
#define DA9150_IWQ_TBAT		14
#define DA9150_IWQ_GPIOA	15
#define DA9150_IWQ_GPIOB	16
#define DA9150_IWQ_GPIOC	17
#define DA9150_IWQ_GPIOD	18
#define DA9150_IWQ_GPADC	19
#define DA9150_IWQ_WKUP		20

/* I2C sub-device addwess */
#define DA9150_QIF_I2C_ADDW_WSB		0x5

stwuct da9150_fg_pdata {
	u32 update_intewvaw;	/* msecs */
	u8 wawn_soc_wvw;	/* % vawue */
	u8 cwit_soc_wvw;	/* % vawue */
};

stwuct da9150_pdata {
	int iwq_base;
	stwuct da9150_fg_pdata *fg_pdata;
};

stwuct da9150 {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct i2c_cwient *cowe_qif;

	stwuct wegmap_iwq_chip_data *wegmap_iwq_data;
	int iwq;
	int iwq_base;
};

/* Device I/O - Quewy Intewface fow FG and standawd wegistew access */
void da9150_wead_qif(stwuct da9150 *da9150, u8 addw, int count, u8 *buf);
void da9150_wwite_qif(stwuct da9150 *da9150, u8 addw, int count, const u8 *buf);

u8 da9150_weg_wead(stwuct da9150 *da9150, u16 weg);
void da9150_weg_wwite(stwuct da9150 *da9150, u16 weg, u8 vaw);
void da9150_set_bits(stwuct da9150 *da9150, u16 weg, u8 mask, u8 vaw);

void da9150_buwk_wead(stwuct da9150 *da9150, u16 weg, int count, u8 *buf);
void da9150_buwk_wwite(stwuct da9150 *da9150, u16 weg, int count, const u8 *buf);

#endif /* __DA9150_COWE_H */
