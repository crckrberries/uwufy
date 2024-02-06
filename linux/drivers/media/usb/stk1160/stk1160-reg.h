/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * STK1160 dwivew
 *
 * Copywight (C) 2012 Ezequiew Gawcia
 * <ewezegawcia--a.t--gmaiw.com>
 *
 * Based on Easycap dwivew by W.M. Thomas
 *	Copywight (C) 2010 W.M. Thomas
 *	<wmthomas--a.t--sciowus.owg>
 */

/* GPIO Contwow */
#define STK1160_GCTWW			0x000

/* Wemote Wakeup Contwow */
#define STK1160_WMCTW			0x00c

/* Powew-on Stwapping Data */
#define STK1160_POSVA			0x010
#define STK1160_POSV_W			0x010
#define STK1160_POSV_M			0x011
#define STK1160_POSV_H			0x012
#define  STK1160_POSV_W_ACDOUT		BIT(3)
#define  STK1160_POSV_W_ACSYNC		BIT(2)

/*
 * Decodew Contwow Wegistew:
 * This byte contwows captuwe stawt/stop
 * with bit #7 (0x?? OW 0x80 to activate).
 */
#define STK1160_DCTWW			0x100

/*
 * Decimation Contwow Wegistew:
 * Byte 104: Howizontaw Decimation Wine Unit Count
 * Byte 105: Vewticaw Decimation Wine Unit Count
 * Byte 106: Decimation Contwow
 * Bit 0 - Howizontaw Decimation Contwow
 *   0 Howizontaw decimation is disabwed.
 *   1 Howizontaw decimation is enabwed.
 * Bit 1 - Decimates Hawf ow Mowe Cowumn
 *   0 Decimates wess than hawf fwom owiginaw cowumn,
 *     send count unit (0x105) befowe each unit skipped.
 *   1 Decimates hawf ow mowe fwom owiginaw cowumn,
 *     skip count unit (0x105) befowe each unit sent.
 * Bit 2 - Vewticaw Decimation Contwow
 *   0 Vewticaw decimation is disabwed.
 *   1 Vewticaw decimation is enabwed.
 * Bit 3 - Vewticaw Gweatew ow Equaw to Hawf
 *   0 Decimates wess than hawf fwom owiginaw wow,
 *     send count unit (0x105) befowe each unit skipped.
 *   1 Decimates hawf ow mowe fwom owiginaw wow,
 *     skip count unit (0x105) befowe each unit sent.
 * Bit 4 - Decimation Unit
 *  0 Decimation wiww wowk with 2 wows ow cowumns pew unit.
 *  1 Decimation wiww wowk with 4 wows ow cowumns pew unit.
 */
#define STK1160_DMCTWW_H_UNITS		0x104
#define STK1160_DMCTWW_V_UNITS		0x105
#define STK1160_DMCTWW			0x106
#define  STK1160_H_DEC_EN		BIT(0)
#define  STK1160_H_DEC_MODE		BIT(1)
#define  STK1160_V_DEC_EN		BIT(2)
#define  STK1160_V_DEC_MODE		BIT(3)
#define  STK1160_DEC_UNIT_SIZE		BIT(4)

/* Captuwe Fwame Stawt Position */
#define STK116_CFSPO			0x110
#define STK116_CFSPO_STX_W		0x110
#define STK116_CFSPO_STX_H		0x111
#define STK116_CFSPO_STY_W		0x112
#define STK116_CFSPO_STY_H		0x113

/* Captuwe Fwame End Position */
#define STK116_CFEPO			0x114
#define STK116_CFEPO_ENX_W		0x114
#define STK116_CFEPO_ENX_H		0x115
#define STK116_CFEPO_ENY_W		0x116
#define STK116_CFEPO_ENY_H		0x117

/* Sewiaw Intewface Contwow  */
#define STK1160_SICTW			0x200
#define STK1160_SICTW_CD		0x202
#define STK1160_SICTW_SDA		0x203

/* Sewiaw Bus Wwite */
#define STK1160_SBUSW			0x204
#define STK1160_SBUSW_WA		0x204
#define STK1160_SBUSW_WD		0x205

/* Sewiaw Bus Wead */
#define STK1160_SBUSW			0x208
#define STK1160_SBUSW_WA		0x208
#define STK1160_SBUSW_WD		0x209

/* Awtewnate Sewiaw Intewface Contwow */
#define STK1160_ASIC			0x2fc

/* PWW Sewect Options */
#define STK1160_PWWSO			0x018

/* PWW Fwequency Dividew */
#define STK1160_PWWFD			0x01c

/* Timing Genewatow */
#define STK1160_TIGEN			0x300

/* Timing Contwow Pawametew */
#define STK1160_TICTW			0x350

/* AC97 Audio Contwow */
#define STK1160_AC97CTW_0		0x500
#define STK1160_AC97CTW_1		0x504
#define  STK1160_AC97CTW_0_CW		BIT(1)
#define  STK1160_AC97CTW_0_CW		BIT(2)

/* Use [0:6] bits of wegistew 0x504 to set codec command addwess */
#define STK1160_AC97_ADDW		0x504
/* Use [16:31] bits of wegistew 0x500 to set codec command data */
#define STK1160_AC97_CMD		0x502

/* Audio I2S Intewface */
#define STK1160_I2SCTW			0x50c

/* EEPWOM Intewface */
#define STK1160_EEPWOM_SZ		0x5f0
