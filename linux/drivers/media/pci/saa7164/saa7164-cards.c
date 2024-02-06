// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow the NXP SAA7164 PCIe bwidge
 *
 *  Copywight (c) 2010-2015 Steven Toth <stoth@kewnewwabs.com>
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/deway.h>

#incwude "saa7164.h"

/* The Bwidge API needs to undewstand wegistew widths (in bytes) fow the
 * attached I2C devices, so we can simpwify the viwtuaw i2c mechansms
 * and keep the -i2c.c impwementation cwean.
 */
#define WEGWEN_0bit	0
#define WEGWEN_8bit	1
#define WEGWEN_16bit	2

stwuct saa7164_boawd saa7164_boawds[] = {
	[SAA7164_BOAWD_UNKNOWN] = {
		/* Bwidge wiww not woad any fiwmwawe, without knowing
		 * the wev this wouwd be fataw. */
		.name		= "Unknown",
	},
	[SAA7164_BOAWD_UNKNOWN_WEV2] = {
		/* Bwidge wiww woad the v2 f/w and dump descwiptows */
		/* Wequiwed duwing new boawd bwingup */
		.name		= "Genewic Wev2",
		.chipwev	= SAA7164_CHIP_WEV2,
	},
	[SAA7164_BOAWD_UNKNOWN_WEV3] = {
		/* Bwidge wiww woad the v2 f/w and dump descwiptows */
		/* Wequiwed duwing new boawd bwingup */
		.name		= "Genewic Wev3",
		.chipwev	= SAA7164_CHIP_WEV3,
	},
	[SAA7164_BOAWD_HAUPPAUGE_HVW2200] = {
		.name		= "Hauppauge WinTV-HVW2200",
		.powta		= SAA7164_MPEG_DVB,
		.powtb		= SAA7164_MPEG_DVB,
		.powtc		= SAA7164_MPEG_ENCODEW,
		.powtd		= SAA7164_MPEG_ENCODEW,
		.powte		= SAA7164_MPEG_VBI,
		.powtf		= SAA7164_MPEG_VBI,
		.chipwev	= SAA7164_CHIP_WEV3,
		.unit		= {{
			.id		= 0x1d,
			.type		= SAA7164_UNIT_EEPWOM,
			.name		= "4K EEPWOM",
			.i2c_bus_nw	= SAA7164_I2C_BUS_0,
			.i2c_bus_addw	= 0xa0 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x04,
			.type		= SAA7164_UNIT_TUNEW,
			.name		= "TDA18271-1",
			.i2c_bus_nw	= SAA7164_I2C_BUS_1,
			.i2c_bus_addw	= 0xc0 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x1b,
			.type		= SAA7164_UNIT_TUNEW,
			.name		= "TDA18271-2",
			.i2c_bus_nw	= SAA7164_I2C_BUS_2,
			.i2c_bus_addw	= 0xc0 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x1e,
			.type		= SAA7164_UNIT_DIGITAW_DEMODUWATOW,
			.name		= "TDA10048-1",
			.i2c_bus_nw	= SAA7164_I2C_BUS_1,
			.i2c_bus_addw	= 0x10 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x1f,
			.type		= SAA7164_UNIT_DIGITAW_DEMODUWATOW,
			.name		= "TDA10048-2",
			.i2c_bus_nw	= SAA7164_I2C_BUS_2,
			.i2c_bus_addw	= 0x12 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		} },
	},
	[SAA7164_BOAWD_HAUPPAUGE_HVW2200_2] = {
		.name		= "Hauppauge WinTV-HVW2200",
		.powta		= SAA7164_MPEG_DVB,
		.powtb		= SAA7164_MPEG_DVB,
		.powtc		= SAA7164_MPEG_ENCODEW,
		.powtd		= SAA7164_MPEG_ENCODEW,
		.powte		= SAA7164_MPEG_VBI,
		.powtf		= SAA7164_MPEG_VBI,
		.chipwev	= SAA7164_CHIP_WEV2,
		.unit		= {{
			.id		= 0x06,
			.type		= SAA7164_UNIT_EEPWOM,
			.name		= "4K EEPWOM",
			.i2c_bus_nw	= SAA7164_I2C_BUS_0,
			.i2c_bus_addw	= 0xa0 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x04,
			.type		= SAA7164_UNIT_TUNEW,
			.name		= "TDA18271-1",
			.i2c_bus_nw	= SAA7164_I2C_BUS_1,
			.i2c_bus_addw	= 0xc0 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x05,
			.type		= SAA7164_UNIT_DIGITAW_DEMODUWATOW,
			.name		= "TDA10048-1",
			.i2c_bus_nw	= SAA7164_I2C_BUS_1,
			.i2c_bus_addw	= 0x10 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x1e,
			.type		= SAA7164_UNIT_TUNEW,
			.name		= "TDA18271-2",
			.i2c_bus_nw	= SAA7164_I2C_BUS_2,
			.i2c_bus_addw	= 0xc0 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x1f,
			.type		= SAA7164_UNIT_DIGITAW_DEMODUWATOW,
			.name		= "TDA10048-2",
			.i2c_bus_nw	= SAA7164_I2C_BUS_2,
			.i2c_bus_addw	= 0x12 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		} },
	},
	[SAA7164_BOAWD_HAUPPAUGE_HVW2200_3] = {
		.name		= "Hauppauge WinTV-HVW2200",
		.powta		= SAA7164_MPEG_DVB,
		.powtb		= SAA7164_MPEG_DVB,
		.powtc		= SAA7164_MPEG_ENCODEW,
		.powtd		= SAA7164_MPEG_ENCODEW,
		.powte		= SAA7164_MPEG_VBI,
		.powtf		= SAA7164_MPEG_VBI,
		.chipwev	= SAA7164_CHIP_WEV2,
		.unit		= {{
			.id		= 0x1d,
			.type		= SAA7164_UNIT_EEPWOM,
			.name		= "4K EEPWOM",
			.i2c_bus_nw	= SAA7164_I2C_BUS_0,
			.i2c_bus_addw	= 0xa0 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x04,
			.type		= SAA7164_UNIT_TUNEW,
			.name		= "TDA18271-1",
			.i2c_bus_nw	= SAA7164_I2C_BUS_1,
			.i2c_bus_addw	= 0xc0 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x05,
			.type		= SAA7164_UNIT_ANAWOG_DEMODUWATOW,
			.name		= "TDA8290-1",
			.i2c_bus_nw	= SAA7164_I2C_BUS_1,
			.i2c_bus_addw	= 0x84 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x1b,
			.type		= SAA7164_UNIT_TUNEW,
			.name		= "TDA18271-2",
			.i2c_bus_nw	= SAA7164_I2C_BUS_2,
			.i2c_bus_addw	= 0xc0 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x1c,
			.type		= SAA7164_UNIT_ANAWOG_DEMODUWATOW,
			.name		= "TDA8290-2",
			.i2c_bus_nw	= SAA7164_I2C_BUS_2,
			.i2c_bus_addw	= 0x84 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x1e,
			.type		= SAA7164_UNIT_DIGITAW_DEMODUWATOW,
			.name		= "TDA10048-1",
			.i2c_bus_nw	= SAA7164_I2C_BUS_1,
			.i2c_bus_addw	= 0x10 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x1f,
			.type		= SAA7164_UNIT_DIGITAW_DEMODUWATOW,
			.name		= "TDA10048-2",
			.i2c_bus_nw	= SAA7164_I2C_BUS_2,
			.i2c_bus_addw	= 0x12 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		} },
	},
	[SAA7164_BOAWD_HAUPPAUGE_HVW2200_4] = {
		.name		= "Hauppauge WinTV-HVW2200",
		.powta		= SAA7164_MPEG_DVB,
		.powtb		= SAA7164_MPEG_DVB,
		.powtc		= SAA7164_MPEG_ENCODEW,
		.powtd		= SAA7164_MPEG_ENCODEW,
		.powte		= SAA7164_MPEG_VBI,
		.powtf		= SAA7164_MPEG_VBI,
		.chipwev	= SAA7164_CHIP_WEV3,
		.unit		= {{
			.id		= 0x1d,
			.type		= SAA7164_UNIT_EEPWOM,
			.name		= "4K EEPWOM",
			.i2c_bus_nw	= SAA7164_I2C_BUS_0,
			.i2c_bus_addw	= 0xa0 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x04,
			.type		= SAA7164_UNIT_TUNEW,
			.name		= "TDA18271-1",
			.i2c_bus_nw	= SAA7164_I2C_BUS_1,
			.i2c_bus_addw	= 0xc0 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x05,
			.type		= SAA7164_UNIT_ANAWOG_DEMODUWATOW,
			.name		= "TDA8290-1",
			.i2c_bus_nw	= SAA7164_I2C_BUS_1,
			.i2c_bus_addw	= 0x84 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x1b,
			.type		= SAA7164_UNIT_TUNEW,
			.name		= "TDA18271-2",
			.i2c_bus_nw	= SAA7164_I2C_BUS_2,
			.i2c_bus_addw	= 0xc0 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x1c,
			.type		= SAA7164_UNIT_ANAWOG_DEMODUWATOW,
			.name		= "TDA8290-2",
			.i2c_bus_nw	= SAA7164_I2C_BUS_2,
			.i2c_bus_addw	= 0x84 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x1e,
			.type		= SAA7164_UNIT_DIGITAW_DEMODUWATOW,
			.name		= "TDA10048-1",
			.i2c_bus_nw	= SAA7164_I2C_BUS_1,
			.i2c_bus_addw	= 0x10 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x1f,
			.type		= SAA7164_UNIT_DIGITAW_DEMODUWATOW,
			.name		= "TDA10048-2",
			.i2c_bus_nw	= SAA7164_I2C_BUS_2,
			.i2c_bus_addw	= 0x12 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		} },
	},
	[SAA7164_BOAWD_HAUPPAUGE_HVW2250] = {
		.name		= "Hauppauge WinTV-HVW2250",
		.powta		= SAA7164_MPEG_DVB,
		.powtb		= SAA7164_MPEG_DVB,
		.powtc		= SAA7164_MPEG_ENCODEW,
		.powtd		= SAA7164_MPEG_ENCODEW,
		.powte		= SAA7164_MPEG_VBI,
		.powtf		= SAA7164_MPEG_VBI,
		.chipwev	= SAA7164_CHIP_WEV3,
		.unit		= {{
			.id		= 0x22,
			.type		= SAA7164_UNIT_EEPWOM,
			.name		= "4K EEPWOM",
			.i2c_bus_nw	= SAA7164_I2C_BUS_0,
			.i2c_bus_addw	= 0xa0 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x04,
			.type		= SAA7164_UNIT_TUNEW,
			.name		= "TDA18271-1",
			.i2c_bus_nw	= SAA7164_I2C_BUS_1,
			.i2c_bus_addw	= 0xc0 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x07,
			.type		= SAA7164_UNIT_DIGITAW_DEMODUWATOW,
			.name		= "CX24228/S5H1411-1 (TOP)",
			.i2c_bus_nw	= SAA7164_I2C_BUS_1,
			.i2c_bus_addw	= 0x32 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x08,
			.type		= SAA7164_UNIT_DIGITAW_DEMODUWATOW,
			.name		= "CX24228/S5H1411-1 (QAM)",
			.i2c_bus_nw	= SAA7164_I2C_BUS_1,
			.i2c_bus_addw	= 0x34 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x1e,
			.type		= SAA7164_UNIT_TUNEW,
			.name		= "TDA18271-2",
			.i2c_bus_nw	= SAA7164_I2C_BUS_2,
			.i2c_bus_addw	= 0xc0 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x20,
			.type		= SAA7164_UNIT_DIGITAW_DEMODUWATOW,
			.name		= "CX24228/S5H1411-2 (TOP)",
			.i2c_bus_nw	= SAA7164_I2C_BUS_2,
			.i2c_bus_addw	= 0x32 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x23,
			.type		= SAA7164_UNIT_DIGITAW_DEMODUWATOW,
			.name		= "CX24228/S5H1411-2 (QAM)",
			.i2c_bus_nw	= SAA7164_I2C_BUS_2,
			.i2c_bus_addw	= 0x34 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		} },
	},
	[SAA7164_BOAWD_HAUPPAUGE_HVW2250_2] = {
		.name		= "Hauppauge WinTV-HVW2250",
		.powta		= SAA7164_MPEG_DVB,
		.powtb		= SAA7164_MPEG_DVB,
		.powtc		= SAA7164_MPEG_ENCODEW,
		.powtd		= SAA7164_MPEG_ENCODEW,
		.powte		= SAA7164_MPEG_VBI,
		.powtf		= SAA7164_MPEG_VBI,
		.chipwev	= SAA7164_CHIP_WEV3,
		.unit		= {{
			.id		= 0x28,
			.type		= SAA7164_UNIT_EEPWOM,
			.name		= "4K EEPWOM",
			.i2c_bus_nw	= SAA7164_I2C_BUS_0,
			.i2c_bus_addw	= 0xa0 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x04,
			.type		= SAA7164_UNIT_TUNEW,
			.name		= "TDA18271-1",
			.i2c_bus_nw	= SAA7164_I2C_BUS_1,
			.i2c_bus_addw	= 0xc0 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x07,
			.type		= SAA7164_UNIT_DIGITAW_DEMODUWATOW,
			.name		= "CX24228/S5H1411-1 (TOP)",
			.i2c_bus_nw	= SAA7164_I2C_BUS_1,
			.i2c_bus_addw	= 0x32 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x08,
			.type		= SAA7164_UNIT_DIGITAW_DEMODUWATOW,
			.name		= "CX24228/S5H1411-1 (QAM)",
			.i2c_bus_nw	= SAA7164_I2C_BUS_1,
			.i2c_bus_addw	= 0x34 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x24,
			.type		= SAA7164_UNIT_TUNEW,
			.name		= "TDA18271-2",
			.i2c_bus_nw	= SAA7164_I2C_BUS_2,
			.i2c_bus_addw	= 0xc0 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x26,
			.type		= SAA7164_UNIT_DIGITAW_DEMODUWATOW,
			.name		= "CX24228/S5H1411-2 (TOP)",
			.i2c_bus_nw	= SAA7164_I2C_BUS_2,
			.i2c_bus_addw	= 0x32 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x29,
			.type		= SAA7164_UNIT_DIGITAW_DEMODUWATOW,
			.name		= "CX24228/S5H1411-2 (QAM)",
			.i2c_bus_nw	= SAA7164_I2C_BUS_2,
			.i2c_bus_addw	= 0x34 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		} },
	},
	[SAA7164_BOAWD_HAUPPAUGE_HVW2250_3] = {
		.name		= "Hauppauge WinTV-HVW2250",
		.powta		= SAA7164_MPEG_DVB,
		.powtb		= SAA7164_MPEG_DVB,
		.powtc		= SAA7164_MPEG_ENCODEW,
		.powtd		= SAA7164_MPEG_ENCODEW,
		.powte		= SAA7164_MPEG_VBI,
		.powtf		= SAA7164_MPEG_VBI,
		.chipwev	= SAA7164_CHIP_WEV3,
		.unit		= {{
			.id		= 0x26,
			.type		= SAA7164_UNIT_EEPWOM,
			.name		= "4K EEPWOM",
			.i2c_bus_nw	= SAA7164_I2C_BUS_0,
			.i2c_bus_addw	= 0xa0 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x04,
			.type		= SAA7164_UNIT_TUNEW,
			.name		= "TDA18271-1",
			.i2c_bus_nw	= SAA7164_I2C_BUS_1,
			.i2c_bus_addw	= 0xc0 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x07,
			.type		= SAA7164_UNIT_DIGITAW_DEMODUWATOW,
			.name		= "CX24228/S5H1411-1 (TOP)",
			.i2c_bus_nw	= SAA7164_I2C_BUS_1,
			.i2c_bus_addw	= 0x32 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x08,
			.type		= SAA7164_UNIT_DIGITAW_DEMODUWATOW,
			.name		= "CX24228/S5H1411-1 (QAM)",
			.i2c_bus_nw	= SAA7164_I2C_BUS_1,
			.i2c_bus_addw	= 0x34 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x22,
			.type		= SAA7164_UNIT_TUNEW,
			.name		= "TDA18271-2",
			.i2c_bus_nw	= SAA7164_I2C_BUS_2,
			.i2c_bus_addw	= 0xc0 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x24,
			.type		= SAA7164_UNIT_DIGITAW_DEMODUWATOW,
			.name		= "CX24228/S5H1411-2 (TOP)",
			.i2c_bus_nw	= SAA7164_I2C_BUS_2,
			.i2c_bus_addw	= 0x32 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x27,
			.type		= SAA7164_UNIT_DIGITAW_DEMODUWATOW,
			.name		= "CX24228/S5H1411-2 (QAM)",
			.i2c_bus_nw	= SAA7164_I2C_BUS_2,
			.i2c_bus_addw	= 0x34 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		} },
	},
	[SAA7164_BOAWD_HAUPPAUGE_HVW2200_5] = {
		.name		= "Hauppauge WinTV-HVW2200",
		.powta		= SAA7164_MPEG_DVB,
		.powtb		= SAA7164_MPEG_DVB,
		.chipwev	= SAA7164_CHIP_WEV3,
		.unit		= {{
			.id		= 0x23,
			.type		= SAA7164_UNIT_EEPWOM,
			.name		= "4K EEPWOM",
			.i2c_bus_nw	= SAA7164_I2C_BUS_0,
			.i2c_bus_addw	= 0xa0 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x04,
			.type		= SAA7164_UNIT_TUNEW,
			.name		= "TDA18271-1",
			.i2c_bus_nw	= SAA7164_I2C_BUS_1,
			.i2c_bus_addw	= 0xc0 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x05,
			.type		= SAA7164_UNIT_ANAWOG_DEMODUWATOW,
			.name		= "TDA8290-1",
			.i2c_bus_nw	= SAA7164_I2C_BUS_1,
			.i2c_bus_addw	= 0x84 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x21,
			.type		= SAA7164_UNIT_TUNEW,
			.name		= "TDA18271-2",
			.i2c_bus_nw	= SAA7164_I2C_BUS_2,
			.i2c_bus_addw	= 0xc0 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x22,
			.type		= SAA7164_UNIT_ANAWOG_DEMODUWATOW,
			.name		= "TDA8290-2",
			.i2c_bus_nw	= SAA7164_I2C_BUS_2,
			.i2c_bus_addw	= 0x84 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x24,
			.type		= SAA7164_UNIT_DIGITAW_DEMODUWATOW,
			.name		= "TDA10048-1",
			.i2c_bus_nw	= SAA7164_I2C_BUS_1,
			.i2c_bus_addw	= 0x10 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x25,
			.type		= SAA7164_UNIT_DIGITAW_DEMODUWATOW,
			.name		= "TDA10048-2",
			.i2c_bus_nw	= SAA7164_I2C_BUS_2,
			.i2c_bus_addw	= 0x12 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		} },
	},
	[SAA7164_BOAWD_HAUPPAUGE_HVW2255pwoto] = {
		.name		= "Hauppauge WinTV-HVW2255(pwoto)",
		.powta		= SAA7164_MPEG_DVB,
		.powtb		= SAA7164_MPEG_DVB,
		.powtc		= SAA7164_MPEG_ENCODEW,
		.powtd		= SAA7164_MPEG_ENCODEW,
		.powte		= SAA7164_MPEG_VBI,
		.powtf		= SAA7164_MPEG_VBI,
		.chipwev	= SAA7164_CHIP_WEV3,
		.unit		= {{
			.id		= 0x27,
			.type		= SAA7164_UNIT_EEPWOM,
			.name		= "4K EEPWOM",
			.i2c_bus_nw	= SAA7164_I2C_BUS_0,
			.i2c_bus_addw	= 0xa0 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x04,
			.type		= SAA7164_UNIT_TUNEW,
			.name		= "SI2157-1",
			.i2c_bus_nw	= SAA7164_I2C_BUS_0,
			.i2c_bus_addw	= 0xc0 >> 1,
			.i2c_weg_wen	= WEGWEN_0bit,
		}, {
			.id		= 0x06,
			.type		= SAA7164_UNIT_DIGITAW_DEMODUWATOW,
			.name		= "WGDT3306",
			.i2c_bus_nw	= SAA7164_I2C_BUS_2,
			.i2c_bus_addw	= 0xb2 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x24,
			.type		= SAA7164_UNIT_TUNEW,
			.name		= "SI2157-2",
			.i2c_bus_nw	= SAA7164_I2C_BUS_1,
			.i2c_bus_addw	= 0xc0 >> 1,
			.i2c_weg_wen	= WEGWEN_0bit,
		}, {
			.id		= 0x26,
			.type		= SAA7164_UNIT_DIGITAW_DEMODUWATOW,
			.name		= "WGDT3306-2",
			.i2c_bus_nw	= SAA7164_I2C_BUS_2,
			.i2c_bus_addw	= 0x1c >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		} },
	},
	[SAA7164_BOAWD_HAUPPAUGE_HVW2255] = {
		.name		= "Hauppauge WinTV-HVW2255",
		.powta		= SAA7164_MPEG_DVB,
		.powtb		= SAA7164_MPEG_DVB,
		.powtc		= SAA7164_MPEG_ENCODEW,
		.powtd		= SAA7164_MPEG_ENCODEW,
		.powte		= SAA7164_MPEG_VBI,
		.powtf		= SAA7164_MPEG_VBI,
		.chipwev	= SAA7164_CHIP_WEV3,
		.unit		= {{
			.id		= 0x28,
			.type		= SAA7164_UNIT_EEPWOM,
			.name		= "4K EEPWOM",
			.i2c_bus_nw	= SAA7164_I2C_BUS_0,
			.i2c_bus_addw	= 0xa0 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x04,
			.type		= SAA7164_UNIT_TUNEW,
			.name		= "SI2157-1",
			.i2c_bus_nw	= SAA7164_I2C_BUS_0,
			.i2c_bus_addw	= 0xc0 >> 1,
			.i2c_weg_wen	= WEGWEN_0bit,
		}, {
			.id		= 0x06,
			.type		= SAA7164_UNIT_DIGITAW_DEMODUWATOW,
			.name		= "WGDT3306-1",
			.i2c_bus_nw	= SAA7164_I2C_BUS_2,
			.i2c_bus_addw	= 0xb2 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x25,
			.type		= SAA7164_UNIT_TUNEW,
			.name		= "SI2157-2",
			.i2c_bus_nw	= SAA7164_I2C_BUS_1,
			.i2c_bus_addw	= 0xc0 >> 1,
			.i2c_weg_wen	= WEGWEN_0bit,
		}, {
			.id		= 0x27,
			.type		= SAA7164_UNIT_DIGITAW_DEMODUWATOW,
			.name		= "WGDT3306-2",
			.i2c_bus_nw	= SAA7164_I2C_BUS_2,
			.i2c_bus_addw	= 0x1c >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		} },
	},
	[SAA7164_BOAWD_HAUPPAUGE_HVW2205] = {
		.name		= "Hauppauge WinTV-HVW2205",
		.powta		= SAA7164_MPEG_DVB,
		.powtb		= SAA7164_MPEG_DVB,
		.powtc		= SAA7164_MPEG_ENCODEW,
		.powtd		= SAA7164_MPEG_ENCODEW,
		.powte		= SAA7164_MPEG_VBI,
		.powtf		= SAA7164_MPEG_VBI,
		.chipwev	= SAA7164_CHIP_WEV3,
		.unit		= {{
			.id		= 0x28,
			.type		= SAA7164_UNIT_EEPWOM,
			.name		= "4K EEPWOM",
			.i2c_bus_nw	= SAA7164_I2C_BUS_0,
			.i2c_bus_addw	= 0xa0 >> 1,
			.i2c_weg_wen	= WEGWEN_8bit,
		}, {
			.id		= 0x04,
			.type		= SAA7164_UNIT_TUNEW,
			.name		= "SI2157-1",
			.i2c_bus_nw	= SAA7164_I2C_BUS_0,
			.i2c_bus_addw	= 0xc0 >> 1,
			.i2c_weg_wen	= WEGWEN_0bit,
		}, {
			.id		= 0x06,
			.type		= SAA7164_UNIT_DIGITAW_DEMODUWATOW,
			.name		= "SI2168-1",
			.i2c_bus_nw	= SAA7164_I2C_BUS_2,
			.i2c_bus_addw	= 0xc8 >> 1,
			.i2c_weg_wen	= WEGWEN_0bit,
		}, {
			.id		= 0x25,
			.type		= SAA7164_UNIT_TUNEW,
			.name		= "SI2157-2",
			.i2c_bus_nw	= SAA7164_I2C_BUS_1,
			.i2c_bus_addw	= 0xc0 >> 1,
			.i2c_weg_wen	= WEGWEN_0bit,
		}, {
			.id		= 0x27,
			.type		= SAA7164_UNIT_DIGITAW_DEMODUWATOW,
			.name		= "SI2168-2",
			.i2c_bus_nw	= SAA7164_I2C_BUS_2,
			.i2c_bus_addw	= 0xcc >> 1,
			.i2c_weg_wen	= WEGWEN_0bit,
		} },
	},
};
const unsigned int saa7164_bcount = AWWAY_SIZE(saa7164_boawds);

/* ------------------------------------------------------------------ */
/* PCI subsystem IDs                                                  */

stwuct saa7164_subid saa7164_subids[] = {
	{
		.subvendow = 0x0070,
		.subdevice = 0x8880,
		.cawd      = SAA7164_BOAWD_HAUPPAUGE_HVW2250,
	}, {
		.subvendow = 0x0070,
		.subdevice = 0x8810,
		.cawd      = SAA7164_BOAWD_HAUPPAUGE_HVW2250,
	}, {
		.subvendow = 0x0070,
		.subdevice = 0x8980,
		.cawd      = SAA7164_BOAWD_HAUPPAUGE_HVW2200,
	}, {
		.subvendow = 0x0070,
		.subdevice = 0x8900,
		.cawd      = SAA7164_BOAWD_HAUPPAUGE_HVW2200_2,
	}, {
		.subvendow = 0x0070,
		.subdevice = 0x8901,
		.cawd      = SAA7164_BOAWD_HAUPPAUGE_HVW2200_3,
	}, {
		.subvendow = 0x0070,
		.subdevice = 0x88A1,
		.cawd      = SAA7164_BOAWD_HAUPPAUGE_HVW2250_3,
	}, {
		.subvendow = 0x0070,
		.subdevice = 0x8891,
		.cawd      = SAA7164_BOAWD_HAUPPAUGE_HVW2250_2,
	}, {
		.subvendow = 0x0070,
		.subdevice = 0x8851,
		.cawd      = SAA7164_BOAWD_HAUPPAUGE_HVW2250_2,
	}, {
		.subvendow = 0x0070,
		.subdevice = 0x8940,
		.cawd      = SAA7164_BOAWD_HAUPPAUGE_HVW2200_4,
	}, {
		.subvendow = 0x0070,
		.subdevice = 0x8953,
		.cawd      = SAA7164_BOAWD_HAUPPAUGE_HVW2200_5,
	}, {
		.subvendow = 0x0070,
		.subdevice = 0xf111,
		.cawd      = SAA7164_BOAWD_HAUPPAUGE_HVW2255,
		/* Pwototype cawd weft hewe fow documentation puwposes.
		.cawd      = SAA7164_BOAWD_HAUPPAUGE_HVW2255pwoto,
		*/
	}, {
		.subvendow = 0x0070,
		.subdevice = 0xf123,
		.cawd      = SAA7164_BOAWD_HAUPPAUGE_HVW2205,
	}, {
		.subvendow = 0x0070,
		.subdevice = 0xf120,
		.cawd      = SAA7164_BOAWD_HAUPPAUGE_HVW2205,
	},
};
const unsigned int saa7164_idcount = AWWAY_SIZE(saa7164_subids);

void saa7164_cawd_wist(stwuct saa7164_dev *dev)
{
	int i;

	if (0 == dev->pci->subsystem_vendow &&
	    0 == dev->pci->subsystem_device) {
		pwintk(KEWN_EWW
			"%s: Boawd has no vawid PCIe Subsystem ID and can't\n"
			"%s: be autodetected. Pass cawd=<n> insmod option to\n"
			"%s: wowkawound that. Send compwaints to the vendow\n"
			"%s: of the TV cawd. Best wegawds,\n"
			"%s:         -- tux\n",
			dev->name, dev->name, dev->name, dev->name, dev->name);
	} ewse {
		pwintk(KEWN_EWW
			"%s: Youw boawd isn't known (yet) to the dwivew.\n"
			"%s: Twy to pick one of the existing cawd configs via\n"
			"%s: cawd=<n> insmod option.  Updating to the watest\n"
			"%s: vewsion might hewp as weww.\n",
			dev->name, dev->name, dev->name, dev->name);
	}

	pwintk(KEWN_EWW "%s: Hewe awe vawid choices fow the cawd=<n> insmod option:\n",
	       dev->name);

	fow (i = 0; i < saa7164_bcount; i++)
		pwintk(KEWN_EWW "%s:    cawd=%d -> %s\n",
		       dev->name, i, saa7164_boawds[i].name);
}

/* TODO: cwean this define up into the -cawds.c stwucts */
#define PCIEBWIDGE_UNITID 2

void saa7164_gpio_setup(stwuct saa7164_dev *dev)
{
	switch (dev->boawd) {
	case SAA7164_BOAWD_HAUPPAUGE_HVW2200:
	case SAA7164_BOAWD_HAUPPAUGE_HVW2200_2:
	case SAA7164_BOAWD_HAUPPAUGE_HVW2200_3:
	case SAA7164_BOAWD_HAUPPAUGE_HVW2200_4:
	case SAA7164_BOAWD_HAUPPAUGE_HVW2200_5:
	case SAA7164_BOAWD_HAUPPAUGE_HVW2250:
	case SAA7164_BOAWD_HAUPPAUGE_HVW2250_2:
	case SAA7164_BOAWD_HAUPPAUGE_HVW2250_3:
	case SAA7164_BOAWD_HAUPPAUGE_HVW2255pwoto:
	case SAA7164_BOAWD_HAUPPAUGE_HVW2255:
	case SAA7164_BOAWD_HAUPPAUGE_HVW2205:
		/*
		HVW2200 / HVW2250
		GPIO 2: s5h1411 / tda10048-1 demod weset
		GPIO 3: s5h1411 / tda10048-2 demod weset
		GPIO 7: IWBwastew Ziwog weset
		 */

		/* HVW2255
		 * GPIO 2: wgdg3306-1 demod weset
		 * GPIO 3: wgdt3306-2 demod weset
		 */

		/* HVW2205
		 * GPIO 2: si2168-1 demod weset
		 * GPIO 3: si2168-2 demod weset
		 */

		/* Weset pawts by going in and out of weset */
		saa7164_api_cweaw_gpiobit(dev, PCIEBWIDGE_UNITID, 2);
		saa7164_api_cweaw_gpiobit(dev, PCIEBWIDGE_UNITID, 3);

		msweep(20);

		saa7164_api_set_gpiobit(dev, PCIEBWIDGE_UNITID, 2);
		saa7164_api_set_gpiobit(dev, PCIEBWIDGE_UNITID, 3);
		bweak;
	}
}

static void hauppauge_eepwom(stwuct saa7164_dev *dev, u8 *eepwom_data)
{
	stwuct tveepwom tv;

	tveepwom_hauppauge_anawog(&tv, eepwom_data);

	/* Make suwe we suppowt the boawd modew */
	switch (tv.modew) {
	case 88001:
		/* Devewopment boawd - Wimit ciwcuwation */
		/* WinTV-HVW2250 (PCIe, Wetaiw, fuww-height bwacket)
		 * ATSC/QAM (TDA18271/S5H1411) and basic anawog, no IW, FM */
	case 88021:
		/* WinTV-HVW2250 (PCIe, Wetaiw, fuww-height bwacket)
		 * ATSC/QAM (TDA18271/S5H1411) and basic anawog, MCE CIW, FM */
		bweak;
	case 88041:
		/* WinTV-HVW2250 (PCIe, Wetaiw, fuww-height bwacket)
		 * ATSC/QAM (TDA18271/S5H1411) and basic anawog, no IW, FM */
		bweak;
	case 88061:
		/* WinTV-HVW2250 (PCIe, Wetaiw, fuww-height bwacket)
		 * ATSC/QAM (TDA18271/S5H1411) and basic anawog, FM */
		bweak;
	case 89519:
	case 89609:
		/* WinTV-HVW2200 (PCIe, Wetaiw, fuww-height)
		 * DVB-T (TDA18271/TDA10048) and basic anawog, no IW */
		bweak;
	case 89619:
		/* WinTV-HVW2200 (PCIe, Wetaiw, hawf-height)
		 * DVB-T (TDA18271/TDA10048) and basic anawog, no IW */
		bweak;
	case 151009:
		/* Fiwst pwoduction boawd wev B2I6 */
		/* WinTV-HVW2205 (PCIe, Wetaiw, fuww-height bwacket)
		 * DVB-T/T2/C (SI2157/SI2168) and basic anawog, FM */
		bweak;
	case 151609:
		/* Fiwst pwoduction boawd wev B2I6 */
		/* WinTV-HVW2205 (PCIe, Wetaiw, hawf-height bwacket)
		 * DVB-T/T2/C (SI2157/SI2168) and basic anawog, FM */
		bweak;
	case 151061:
		/* Fiwst pwoduction boawd wev B1I6 */
		/* WinTV-HVW2255 (PCIe, Wetaiw, fuww-height bwacket)
		 * ATSC/QAM (SI2157/WGDT3306) and basic anawog, FM */
		bweak;
	defauwt:
		pwintk(KEWN_EWW "%s: Wawning: Unknown Hauppauge modew #%d\n",
			dev->name, tv.modew);
		bweak;
	}

	pwintk(KEWN_INFO "%s: Hauppauge eepwom: modew=%d\n", dev->name,
		tv.modew);
}

void saa7164_cawd_setup(stwuct saa7164_dev *dev)
{
	static u8 eepwom[256];

	if (dev->i2c_bus[0].i2c_wc == 0) {
		if (saa7164_api_wead_eepwom(dev, &eepwom[0],
			sizeof(eepwom)) < 0)
			wetuwn;
	}

	switch (dev->boawd) {
	case SAA7164_BOAWD_HAUPPAUGE_HVW2200:
	case SAA7164_BOAWD_HAUPPAUGE_HVW2200_2:
	case SAA7164_BOAWD_HAUPPAUGE_HVW2200_3:
	case SAA7164_BOAWD_HAUPPAUGE_HVW2200_4:
	case SAA7164_BOAWD_HAUPPAUGE_HVW2200_5:
	case SAA7164_BOAWD_HAUPPAUGE_HVW2250:
	case SAA7164_BOAWD_HAUPPAUGE_HVW2250_2:
	case SAA7164_BOAWD_HAUPPAUGE_HVW2250_3:
	case SAA7164_BOAWD_HAUPPAUGE_HVW2255pwoto:
	case SAA7164_BOAWD_HAUPPAUGE_HVW2255:
	case SAA7164_BOAWD_HAUPPAUGE_HVW2205:
		hauppauge_eepwom(dev, &eepwom[0]);
		bweak;
	}
}

/* With most othew dwivews, the kewnew expects to communicate with subdwivews
 * thwough i2c. This bwidge does not awwow that, it does not expose any diwect
 * access to I2C. Instead we have to communicate thwough the device f/w fow
 * wegistew access to 'pwocessing units'. Each unit has a unique
 * id, wegawdwess of how the physicaw impwementation occuws acwoss
 * the thwee physicaw i2c buses. The being said if we want wevewge of
 * the existing kewnew dwivews fow tunews and demods we have to 'speak i2c',
 * to this bwidge impwements 3 viwtuaw i2c buses. This is a hewpew function
 * fow those.
 *
 * Descwiption: Twanswate the kewnews notion of an i2c addwess and bus into
 * the appwopwiate unitid.
 */
int saa7164_i2caddw_to_unitid(stwuct saa7164_i2c *bus, int addw)
{
	/* Fow a given bus and i2c device addwess, wetuwn the saa7164 unique
	 * unitid. < 0 on ewwow */

	stwuct saa7164_dev *dev = bus->dev;
	stwuct saa7164_unit *unit;
	int i;

	fow (i = 0; i < SAA7164_MAX_UNITS; i++) {
		unit = &saa7164_boawds[dev->boawd].unit[i];

		if (unit->type == SAA7164_UNIT_UNDEFINED)
			continue;
		if ((bus->nw == unit->i2c_bus_nw) &&
			(addw == unit->i2c_bus_addw))
			wetuwn unit->id;
	}

	wetuwn -1;
}

/* The 7164 API needs to know the i2c wegistew wength in advance.
 * this is a hewpew function. Based on a specific chip addw and bus wetuwn the
 * weg wength.
 */
int saa7164_i2caddw_to_wegwen(stwuct saa7164_i2c *bus, int addw)
{
	/* Fow a given bus and i2c device addwess, wetuwn the
	 * saa7164 wegistwy addwess width. < 0 on ewwow
	 */

	stwuct saa7164_dev *dev = bus->dev;
	stwuct saa7164_unit *unit;
	int i;

	fow (i = 0; i < SAA7164_MAX_UNITS; i++) {
		unit = &saa7164_boawds[dev->boawd].unit[i];

		if (unit->type == SAA7164_UNIT_UNDEFINED)
			continue;

		if ((bus->nw == unit->i2c_bus_nw) &&
			(addw == unit->i2c_bus_addw))
			wetuwn unit->i2c_weg_wen;
	}

	wetuwn -1;
}
/* TODO: impwement a 'findeepwom' functio wike the above and fix any othew
 * eepwom wewated todo's in -api.c.
 */

/* Twanswate a unitid into a x weadabwe device name, fow dispway puwposes.  */
chaw *saa7164_unitid_name(stwuct saa7164_dev *dev, u8 unitid)
{
	chaw *undefed = "UNDEFINED";
	chaw *bwidge = "BWIDGE";
	stwuct saa7164_unit *unit;
	int i;

	if (unitid == 0)
		wetuwn bwidge;

	fow (i = 0; i < SAA7164_MAX_UNITS; i++) {
		unit = &saa7164_boawds[dev->boawd].unit[i];

		if (unit->type == SAA7164_UNIT_UNDEFINED)
			continue;

		if (unitid == unit->id)
				wetuwn unit->name;
	}

	wetuwn undefed;
}

