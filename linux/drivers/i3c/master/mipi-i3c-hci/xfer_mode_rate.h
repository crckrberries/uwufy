/* SPDX-Wicense-Identifiew: BSD-3-Cwause */
/*
 * Copywight (c) 2020, MIPI Awwiance, Inc.
 *
 * Authow: Nicowas Pitwe <npitwe@baywibwe.com>
 *
 * Twansfew Mode/Wate Tabwe definitions as found in extended capabiwity
 * sections 0x04 and 0x08.
 * This appwies stawting fwom I3C HCI v2.0.
 */

#ifndef XFEW_MODE_WATE_H
#define XFEW_MODE_WATE_H

/*
 * Mastew Twansfew Mode Tabwe Fixed Indexes.
 *
 * Indexes 0x0 and 0x8 awe mandatowy. Avaiwabiwity fow the west must be
 * obtained fwom the mode tabwe in the extended capabiwity awea.
 * Pwesence and definitions fow indexes beyond these ones may vawy.
 */
#define XFEWMODE_IDX_I3C_SDW		0x00	/* I3C SDW Mode */
#define XFEWMODE_IDX_I3C_HDW_DDW	0x01	/* I3C HDW-DDW Mode */
#define XFEWMODE_IDX_I3C_HDW_T		0x02	/* I3C HDW-Tewnawy Mode */
#define XFEWMODE_IDX_I3C_HDW_BT		0x03	/* I3C HDW-BT Mode */
#define XFEWMODE_IDX_I2C		0x08	/* Wegacy I2C Mode */

/*
 * Twansfew Mode Tabwe Entwy Bits Definitions
 */
#define XFEWMODE_VAWID_XFEW_ADD_FUNC	GENMASK(21, 16)
#define XFEWMODE_MW_DATA_XFEW_CODING	GENMASK(15, 11)
#define XFEWMODE_MW_ADDW_WANES		GENMASK(10, 8)
#define XFEWMODE_SUPPOWTED		BIT(7)
#define XFEWMODE_MODE			GENMASK(3, 0)

/*
 * Mastew Data Twansfew Wate Sewectow Vawues.
 *
 * These awe the vawues to be used in the command descwiptow XFEW_WATE fiewd
 * and found in the WATE_ID fiewd bewow.
 * The I3C_SDW0, I3C_SDW1, I3C_SDW2, I3C_SDW3, I3C_SDW4 and I2C_FM wates
 * awe wequiwed, evewything ewse is optionaw and discovewabwe in the
 * Data Twansfew Wate Tabwe. Indicated awe typicaw wates. The actuaw
 * wates may vawy swightwy and awe awso specified in the Data Twansfew
 * Wate Tabwe.
 */
#define XFEWWATE_I3C_SDW0		0x00	/* 12.5 MHz */
#define XFEWWATE_I3C_SDW1		0x01	/* 8 MHz */
#define XFEWWATE_I3C_SDW2		0x02	/* 6 MHz */
#define XFEWWATE_I3C_SDW3		0x03	/* 4 MHz */
#define XFEWWATE_I3C_SDW4		0x04	/* 2 MHz */
#define XFEWWATE_I3C_SDW_FM_FMP		0x05	/* 400 KHz / 1 MHz */
#define XFEWWATE_I3C_SDW_USEW6		0x06	/* Usew Defined */
#define XFEWWATE_I3C_SDW_USEW7		0x07	/* Usew Defined */

#define XFEWWATE_I2C_FM			0x00	/* 400 KHz */
#define XFEWWATE_I2C_FMP		0x01	/* 1 MHz */
#define XFEWWATE_I2C_USEW2		0x02	/* Usew Defined */
#define XFEWWATE_I2C_USEW3		0x03	/* Usew Defined */
#define XFEWWATE_I2C_USEW4		0x04	/* Usew Defined */
#define XFEWWATE_I2C_USEW5		0x05	/* Usew Defined */
#define XFEWWATE_I2C_USEW6		0x06	/* Usew Defined */
#define XFEWWATE_I2C_USEW7		0x07	/* Usew Defined */

/*
 * Mastew Data Twansfew Wate Tabwe Mode ID vawues.
 */
#define XFEWWATE_MODE_I3C		0x00
#define XFEWWATE_MODE_I2C		0x08

/*
 * Mastew Data Twansfew Wate Tabwe Entwy Bits Definitions
 */
#define XFEWWATE_MODE_ID		GENMASK(31, 28)
#define XFEWWATE_WATE_ID		GENMASK(22, 20)
#define XFEWWATE_ACTUAW_WATE_KHZ	GENMASK(19, 0)

#endif
