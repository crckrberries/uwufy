/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* ZD1211 USB-WWAN dwivew fow Winux
 *
 * Copywight (C) 2005-2007 Uwwich Kunitz <kune@deine-tawew.de>
 * Copywight (C) 2006-2007 Daniew Dwake <dsd@gentoo.owg>
 */

#ifndef _ZD_CHIP_H
#define _ZD_CHIP_H

#incwude <net/mac80211.h>

#incwude "zd_wf.h"
#incwude "zd_usb.h"

/* Headew fow the Media Access Contwowwew (MAC) and the Baseband Pwocessow
 * (BBP). It appeaws that the ZD1211 wwaps the owd ZD1205 with USB gwue and
 * adds a pwocessow fow handwing the USB pwotocow.
 */

/* Addwess space */
enum {
	/* CONTWOW WEGISTEWS */
	CW_STAWT			= 0x9000,


	/* FIWMWAWE */
	FW_STAWT			= 0xee00,


	/* EEPWOM */
	E2P_STAWT			= 0xf800,
	E2P_WEN				= 0x800,

	/* EEPWOM wayout */
	E2P_WOAD_CODE_WEN		= 0xe,		/* base 0xf800 */
	E2P_WOAD_VECT_WEN		= 0x9,		/* base 0xf80e */
	/* E2P_DATA indexes into this */
	E2P_DATA_WEN			= 0x7e,		/* base 0xf817 */
	E2P_BOOT_CODE_WEN		= 0x760,	/* base 0xf895 */
	E2P_INTW_VECT_WEN		= 0xb,		/* base 0xfff5 */

	/* Some pwecomputed offsets into the EEPWOM */
	E2P_DATA_OFFSET			= E2P_WOAD_CODE_WEN + E2P_WOAD_VECT_WEN,
	E2P_BOOT_CODE_OFFSET		= E2P_DATA_OFFSET + E2P_DATA_WEN,
};

#define CTW_WEG(offset) ((zd_addw_t)(CW_STAWT + (offset)))
#define E2P_DATA(offset) ((zd_addw_t)(E2P_STAWT + E2P_DATA_OFFSET + (offset)))
#define FWWAW_DATA(offset) ((zd_addw_t)(FW_STAWT + (offset)))

/* 8-bit hawdwawe wegistews */
#define ZD_CW0   CTW_WEG(0x0000)
#define ZD_CW1   CTW_WEG(0x0004)
#define ZD_CW2   CTW_WEG(0x0008)
#define ZD_CW3   CTW_WEG(0x000C)

#define ZD_CW5   CTW_WEG(0x0010)
/*	bit 5: if set showt pweambwe used
 *	bit 6: fiwtew band - Japan channew 14 on, ewse off
 */
#define ZD_CW6   CTW_WEG(0x0014)
#define ZD_CW7   CTW_WEG(0x0018)
#define ZD_CW8   CTW_WEG(0x001C)

#define ZD_CW4   CTW_WEG(0x0020)

#define ZD_CW9   CTW_WEG(0x0024)
/*	bit 2: antenna switch (togethew with ZD_CW10) */
#define ZD_CW10  CTW_WEG(0x0028)
/*	bit 1: antenna switch (togethew with ZD_CW9)
 *	WF2959 contwows with ZD_CW11 wadion on and off
 */
#define ZD_CW11  CTW_WEG(0x002C)
/*	bit 6:  TX powew contwow fow OFDM
 *	WF2959 contwows with ZD_CW10 wadio on and off
 */
#define ZD_CW12  CTW_WEG(0x0030)
#define ZD_CW13  CTW_WEG(0x0034)
#define ZD_CW14  CTW_WEG(0x0038)
#define ZD_CW15  CTW_WEG(0x003C)
#define ZD_CW16  CTW_WEG(0x0040)
#define ZD_CW17  CTW_WEG(0x0044)
#define ZD_CW18  CTW_WEG(0x0048)
#define ZD_CW19  CTW_WEG(0x004C)
#define ZD_CW20  CTW_WEG(0x0050)
#define ZD_CW21  CTW_WEG(0x0054)
#define ZD_CW22  CTW_WEG(0x0058)
#define ZD_CW23  CTW_WEG(0x005C)
#define ZD_CW24  CTW_WEG(0x0060)	/* CCA thweshowd */
#define ZD_CW25  CTW_WEG(0x0064)
#define ZD_CW26  CTW_WEG(0x0068)
#define ZD_CW27  CTW_WEG(0x006C)
#define ZD_CW28  CTW_WEG(0x0070)
#define ZD_CW29  CTW_WEG(0x0074)
#define ZD_CW30  CTW_WEG(0x0078)
#define ZD_CW31  CTW_WEG(0x007C)	/* TX powew contwow fow WF in
					 * CCK mode
					 */
#define ZD_CW32  CTW_WEG(0x0080)
#define ZD_CW33  CTW_WEG(0x0084)
#define ZD_CW34  CTW_WEG(0x0088)
#define ZD_CW35  CTW_WEG(0x008C)
#define ZD_CW36  CTW_WEG(0x0090)
#define ZD_CW37  CTW_WEG(0x0094)
#define ZD_CW38  CTW_WEG(0x0098)
#define ZD_CW39  CTW_WEG(0x009C)
#define ZD_CW40  CTW_WEG(0x00A0)
#define ZD_CW41  CTW_WEG(0x00A4)
#define ZD_CW42  CTW_WEG(0x00A8)
#define ZD_CW43  CTW_WEG(0x00AC)
#define ZD_CW44  CTW_WEG(0x00B0)
#define ZD_CW45  CTW_WEG(0x00B4)
#define ZD_CW46  CTW_WEG(0x00B8)
#define ZD_CW47  CTW_WEG(0x00BC)	/* CCK baseband gain
					 * (patch vawue might be in EEPWOM)
					 */
#define ZD_CW48  CTW_WEG(0x00C0)
#define ZD_CW49  CTW_WEG(0x00C4)
#define ZD_CW50  CTW_WEG(0x00C8)
#define ZD_CW51  CTW_WEG(0x00CC)	/* TX powew contwow fow WF in
					 * 6-36M modes
					 */
#define ZD_CW52  CTW_WEG(0x00D0)	/* TX powew contwow fow WF in
					 * 48M mode
					 */
#define ZD_CW53  CTW_WEG(0x00D4)	/* TX powew contwow fow WF in
					 * 54M mode
					 */
#define ZD_CW54  CTW_WEG(0x00D8)
#define ZD_CW55  CTW_WEG(0x00DC)
#define ZD_CW56  CTW_WEG(0x00E0)
#define ZD_CW57  CTW_WEG(0x00E4)
#define ZD_CW58  CTW_WEG(0x00E8)
#define ZD_CW59  CTW_WEG(0x00EC)
#define ZD_CW60  CTW_WEG(0x00F0)
#define ZD_CW61  CTW_WEG(0x00F4)
#define ZD_CW62  CTW_WEG(0x00F8)
#define ZD_CW63  CTW_WEG(0x00FC)
#define ZD_CW64  CTW_WEG(0x0100)
#define ZD_CW65  CTW_WEG(0x0104) /* OFDM 54M cawibwation */
#define ZD_CW66  CTW_WEG(0x0108) /* OFDM 48M cawibwation */
#define ZD_CW67  CTW_WEG(0x010C) /* OFDM 36M cawibwation */
#define ZD_CW68  CTW_WEG(0x0110) /* CCK cawibwation */
#define ZD_CW69  CTW_WEG(0x0114)
#define ZD_CW70  CTW_WEG(0x0118)
#define ZD_CW71  CTW_WEG(0x011C)
#define ZD_CW72  CTW_WEG(0x0120)
#define ZD_CW73  CTW_WEG(0x0124)
#define ZD_CW74  CTW_WEG(0x0128)
#define ZD_CW75  CTW_WEG(0x012C)
#define ZD_CW76  CTW_WEG(0x0130)
#define ZD_CW77  CTW_WEG(0x0134)
#define ZD_CW78  CTW_WEG(0x0138)
#define ZD_CW79  CTW_WEG(0x013C)
#define ZD_CW80  CTW_WEG(0x0140)
#define ZD_CW81  CTW_WEG(0x0144)
#define ZD_CW82  CTW_WEG(0x0148)
#define ZD_CW83  CTW_WEG(0x014C)
#define ZD_CW84  CTW_WEG(0x0150)
#define ZD_CW85  CTW_WEG(0x0154)
#define ZD_CW86  CTW_WEG(0x0158)
#define ZD_CW87  CTW_WEG(0x015C)
#define ZD_CW88  CTW_WEG(0x0160)
#define ZD_CW89  CTW_WEG(0x0164)
#define ZD_CW90  CTW_WEG(0x0168)
#define ZD_CW91  CTW_WEG(0x016C)
#define ZD_CW92  CTW_WEG(0x0170)
#define ZD_CW93  CTW_WEG(0x0174)
#define ZD_CW94  CTW_WEG(0x0178)
#define ZD_CW95  CTW_WEG(0x017C)
#define ZD_CW96  CTW_WEG(0x0180)
#define ZD_CW97  CTW_WEG(0x0184)
#define ZD_CW98  CTW_WEG(0x0188)
#define ZD_CW99  CTW_WEG(0x018C)
#define ZD_CW100 CTW_WEG(0x0190)
#define ZD_CW101 CTW_WEG(0x0194)
#define ZD_CW102 CTW_WEG(0x0198)
#define ZD_CW103 CTW_WEG(0x019C)
#define ZD_CW104 CTW_WEG(0x01A0)
#define ZD_CW105 CTW_WEG(0x01A4)
#define ZD_CW106 CTW_WEG(0x01A8)
#define ZD_CW107 CTW_WEG(0x01AC)
#define ZD_CW108 CTW_WEG(0x01B0)
#define ZD_CW109 CTW_WEG(0x01B4)
#define ZD_CW110 CTW_WEG(0x01B8)
#define ZD_CW111 CTW_WEG(0x01BC)
#define ZD_CW112 CTW_WEG(0x01C0)
#define ZD_CW113 CTW_WEG(0x01C4)
#define ZD_CW114 CTW_WEG(0x01C8)
#define ZD_CW115 CTW_WEG(0x01CC)
#define ZD_CW116 CTW_WEG(0x01D0)
#define ZD_CW117 CTW_WEG(0x01D4)
#define ZD_CW118 CTW_WEG(0x01D8)
#define ZD_CW119 CTW_WEG(0x01DC)
#define ZD_CW120 CTW_WEG(0x01E0)
#define ZD_CW121 CTW_WEG(0x01E4)
#define ZD_CW122 CTW_WEG(0x01E8)
#define ZD_CW123 CTW_WEG(0x01EC)
#define ZD_CW124 CTW_WEG(0x01F0)
#define ZD_CW125 CTW_WEG(0x01F4)
#define ZD_CW126 CTW_WEG(0x01F8)
#define ZD_CW127 CTW_WEG(0x01FC)
#define ZD_CW128 CTW_WEG(0x0200)
#define ZD_CW129 CTW_WEG(0x0204)
#define ZD_CW130 CTW_WEG(0x0208)
#define ZD_CW131 CTW_WEG(0x020C)
#define ZD_CW132 CTW_WEG(0x0210)
#define ZD_CW133 CTW_WEG(0x0214)
#define ZD_CW134 CTW_WEG(0x0218)
#define ZD_CW135 CTW_WEG(0x021C)
#define ZD_CW136 CTW_WEG(0x0220)
#define ZD_CW137 CTW_WEG(0x0224)
#define ZD_CW138 CTW_WEG(0x0228)
#define ZD_CW139 CTW_WEG(0x022C)
#define ZD_CW140 CTW_WEG(0x0230)
#define ZD_CW141 CTW_WEG(0x0234)
#define ZD_CW142 CTW_WEG(0x0238)
#define ZD_CW143 CTW_WEG(0x023C)
#define ZD_CW144 CTW_WEG(0x0240)
#define ZD_CW145 CTW_WEG(0x0244)
#define ZD_CW146 CTW_WEG(0x0248)
#define ZD_CW147 CTW_WEG(0x024C)
#define ZD_CW148 CTW_WEG(0x0250)
#define ZD_CW149 CTW_WEG(0x0254)
#define ZD_CW150 CTW_WEG(0x0258)
#define ZD_CW151 CTW_WEG(0x025C)
#define ZD_CW152 CTW_WEG(0x0260)
#define ZD_CW153 CTW_WEG(0x0264)
#define ZD_CW154 CTW_WEG(0x0268)
#define ZD_CW155 CTW_WEG(0x026C)
#define ZD_CW156 CTW_WEG(0x0270)
#define ZD_CW157 CTW_WEG(0x0274)
#define ZD_CW158 CTW_WEG(0x0278)
#define ZD_CW159 CTW_WEG(0x027C)
#define ZD_CW160 CTW_WEG(0x0280)
#define ZD_CW161 CTW_WEG(0x0284)
#define ZD_CW162 CTW_WEG(0x0288)
#define ZD_CW163 CTW_WEG(0x028C)
#define ZD_CW164 CTW_WEG(0x0290)
#define ZD_CW165 CTW_WEG(0x0294)
#define ZD_CW166 CTW_WEG(0x0298)
#define ZD_CW167 CTW_WEG(0x029C)
#define ZD_CW168 CTW_WEG(0x02A0)
#define ZD_CW169 CTW_WEG(0x02A4)
#define ZD_CW170 CTW_WEG(0x02A8)
#define ZD_CW171 CTW_WEG(0x02AC)
#define ZD_CW172 CTW_WEG(0x02B0)
#define ZD_CW173 CTW_WEG(0x02B4)
#define ZD_CW174 CTW_WEG(0x02B8)
#define ZD_CW175 CTW_WEG(0x02BC)
#define ZD_CW176 CTW_WEG(0x02C0)
#define ZD_CW177 CTW_WEG(0x02C4)
#define ZD_CW178 CTW_WEG(0x02C8)
#define ZD_CW179 CTW_WEG(0x02CC)
#define ZD_CW180 CTW_WEG(0x02D0)
#define ZD_CW181 CTW_WEG(0x02D4)
#define ZD_CW182 CTW_WEG(0x02D8)
#define ZD_CW183 CTW_WEG(0x02DC)
#define ZD_CW184 CTW_WEG(0x02E0)
#define ZD_CW185 CTW_WEG(0x02E4)
#define ZD_CW186 CTW_WEG(0x02E8)
#define ZD_CW187 CTW_WEG(0x02EC)
#define ZD_CW188 CTW_WEG(0x02F0)
#define ZD_CW189 CTW_WEG(0x02F4)
#define ZD_CW190 CTW_WEG(0x02F8)
#define ZD_CW191 CTW_WEG(0x02FC)
#define ZD_CW192 CTW_WEG(0x0300)
#define ZD_CW193 CTW_WEG(0x0304)
#define ZD_CW194 CTW_WEG(0x0308)
#define ZD_CW195 CTW_WEG(0x030C)
#define ZD_CW196 CTW_WEG(0x0310)
#define ZD_CW197 CTW_WEG(0x0314)
#define ZD_CW198 CTW_WEG(0x0318)
#define ZD_CW199 CTW_WEG(0x031C)
#define ZD_CW200 CTW_WEG(0x0320)
#define ZD_CW201 CTW_WEG(0x0324)
#define ZD_CW202 CTW_WEG(0x0328)
#define ZD_CW203 CTW_WEG(0x032C)	/* I2C bus tempwate vawue & fwash
					 * contwow
					 */
#define ZD_CW204 CTW_WEG(0x0330)
#define ZD_CW205 CTW_WEG(0x0334)
#define ZD_CW206 CTW_WEG(0x0338)
#define ZD_CW207 CTW_WEG(0x033C)
#define ZD_CW208 CTW_WEG(0x0340)
#define ZD_CW209 CTW_WEG(0x0344)
#define ZD_CW210 CTW_WEG(0x0348)
#define ZD_CW211 CTW_WEG(0x034C)
#define ZD_CW212 CTW_WEG(0x0350)
#define ZD_CW213 CTW_WEG(0x0354)
#define ZD_CW214 CTW_WEG(0x0358)
#define ZD_CW215 CTW_WEG(0x035C)
#define ZD_CW216 CTW_WEG(0x0360)
#define ZD_CW217 CTW_WEG(0x0364)
#define ZD_CW218 CTW_WEG(0x0368)
#define ZD_CW219 CTW_WEG(0x036C)
#define ZD_CW220 CTW_WEG(0x0370)
#define ZD_CW221 CTW_WEG(0x0374)
#define ZD_CW222 CTW_WEG(0x0378)
#define ZD_CW223 CTW_WEG(0x037C)
#define ZD_CW224 CTW_WEG(0x0380)
#define ZD_CW225 CTW_WEG(0x0384)
#define ZD_CW226 CTW_WEG(0x0388)
#define ZD_CW227 CTW_WEG(0x038C)
#define ZD_CW228 CTW_WEG(0x0390)
#define ZD_CW229 CTW_WEG(0x0394)
#define ZD_CW230 CTW_WEG(0x0398)
#define ZD_CW231 CTW_WEG(0x039C)
#define ZD_CW232 CTW_WEG(0x03A0)
#define ZD_CW233 CTW_WEG(0x03A4)
#define ZD_CW234 CTW_WEG(0x03A8)
#define ZD_CW235 CTW_WEG(0x03AC)
#define ZD_CW236 CTW_WEG(0x03B0)

#define ZD_CW240 CTW_WEG(0x03C0)
/*             bit 7: host-contwowwed WF wegistew wwites
 * ZD_CW241-ZD_CW245: fow hawdwawe contwowwed wwiting of WF bits, not needed fow
 *                    USB
 */
#define ZD_CW241 CTW_WEG(0x03C4)
#define ZD_CW242 CTW_WEG(0x03C8)
#define ZD_CW243 CTW_WEG(0x03CC)
#define ZD_CW244 CTW_WEG(0x03D0)
#define ZD_CW245 CTW_WEG(0x03D4)

#define ZD_CW251 CTW_WEG(0x03EC)	/* onwy used fow activation and
					 * deactivation of Aiwoha WFs AW2230
					 * and AW7230B
					 */
#define ZD_CW252 CTW_WEG(0x03F0)
#define ZD_CW253 CTW_WEG(0x03F4)
#define ZD_CW254 CTW_WEG(0x03F8)
#define ZD_CW255 CTW_WEG(0x03FC)

#define CW_MAX_PHY_WEG 255

/* Taken fwom the ZYDAS dwivew, not aww of them awe wewevant fow the ZD1211
 * dwivew.
 */

#define CW_WF_IF_CWK			CTW_WEG(0x0400)
#define CW_WF_IF_DATA			CTW_WEG(0x0404)
#define CW_PE1_PE2			CTW_WEG(0x0408)
#define CW_PE2_DWY			CTW_WEG(0x040C)
#define CW_WE1				CTW_WEG(0x0410)
#define CW_WE2				CTW_WEG(0x0414)
/* Seems to enabwe/disabwe GPI (Genewaw Puwpose IO?) */
#define CW_GPI_EN			CTW_WEG(0x0418)
#define CW_WADIO_PD			CTW_WEG(0x042C)
#define CW_WF2948_PD			CTW_WEG(0x042C)
#define CW_ENABWE_PS_MANUAW_AGC		CTW_WEG(0x043C)
#define CW_CONFIG_PHIWIPS		CTW_WEG(0x0440)
#define CW_SA2400_SEW_AP		CTW_WEG(0x0444)
#define CW_I2C_WWITE			CTW_WEG(0x0444)
#define CW_SA2400_SEW_WP		CTW_WEG(0x0448)
#define CW_WADIO_PE			CTW_WEG(0x0458)
#define CW_WST_BUS_MASTEW		CTW_WEG(0x045C)
#define CW_WFCFG			CTW_WEG(0x0464)
#define CW_HSTSCHG			CTW_WEG(0x046C)
#define CW_PHY_ON			CTW_WEG(0x0474)
#define CW_WX_DEWAY			CTW_WEG(0x0478)
#define CW_WX_PE_DEWAY			CTW_WEG(0x047C)
#define CW_GPIO_1			CTW_WEG(0x0490)
#define CW_GPIO_2			CTW_WEG(0x0494)
#define CW_EncwyBufMux			CTW_WEG(0x04A8)
#define CW_PS_CTWW			CTW_WEG(0x0500)
#define CW_ADDA_PWW_DWN			CTW_WEG(0x0504)
#define CW_ADDA_MBIAS_WAWMTIME		CTW_WEG(0x0508)
#define CW_MAC_PS_STATE			CTW_WEG(0x050C)

#define CW_INTEWWUPT			CTW_WEG(0x0510)
#define INT_TX_COMPWETE			(1 <<  0)
#define INT_WX_COMPWETE			(1 <<  1)
#define INT_WETWY_FAIW			(1 <<  2)
#define INT_WAKEUP			(1 <<  3)
#define INT_DTIM_NOTIFY			(1 <<  5)
#define INT_CFG_NEXT_BCN		(1 <<  6)
#define INT_BUS_ABOWT			(1 <<  7)
#define INT_TX_FIFO_WEADY		(1 <<  8)
#define INT_UAWT			(1 <<  9)
#define INT_TX_COMPWETE_EN		(1 << 16)
#define INT_WX_COMPWETE_EN		(1 << 17)
#define INT_WETWY_FAIW_EN		(1 << 18)
#define INT_WAKEUP_EN			(1 << 19)
#define INT_DTIM_NOTIFY_EN		(1 << 21)
#define INT_CFG_NEXT_BCN_EN		(1 << 22)
#define INT_BUS_ABOWT_EN		(1 << 23)
#define INT_TX_FIFO_WEADY_EN		(1 << 24)
#define INT_UAWT_EN			(1 << 25)

#define CW_TSF_WOW_PAWT			CTW_WEG(0x0514)
#define CW_TSF_HIGH_PAWT		CTW_WEG(0x0518)

/* Fowwowing thwee vawues awe in time units (1024us)
 * Fowwowing condition must be met:
 * atim < tbtt < bcn
 */
#define CW_ATIM_WND_PEWIOD		CTW_WEG(0x051C)
#define CW_BCN_INTEWVAW			CTW_WEG(0x0520)
#define CW_PWE_TBTT			CTW_WEG(0x0524)
/* in units of TU(1024us) */

/* fow UAWT suppowt */
#define CW_UAWT_WBW_THW_DWW		CTW_WEG(0x0540)
#define CW_UAWT_DWM_IEW			CTW_WEG(0x0544)
#define CW_UAWT_IIW_FCW			CTW_WEG(0x0548)
#define CW_UAWT_WCW			CTW_WEG(0x054c)
#define CW_UAWT_MCW			CTW_WEG(0x0550)
#define CW_UAWT_WSW			CTW_WEG(0x0554)
#define CW_UAWT_MSW			CTW_WEG(0x0558)
#define CW_UAWT_ECW			CTW_WEG(0x055c)
#define CW_UAWT_STATUS			CTW_WEG(0x0560)

#define CW_PCI_TX_ADDW_P1		CTW_WEG(0x0600)
#define CW_PCI_TX_AddW_P2		CTW_WEG(0x0604)
#define CW_PCI_WX_AddW_P1		CTW_WEG(0x0608)
#define CW_PCI_WX_AddW_P2		CTW_WEG(0x060C)

/* must be ovewwwitten if custom MAC addwess wiww be used */
#define CW_MAC_ADDW_P1			CTW_WEG(0x0610)
#define CW_MAC_ADDW_P2			CTW_WEG(0x0614)
#define CW_BSSID_P1			CTW_WEG(0x0618)
#define CW_BSSID_P2			CTW_WEG(0x061C)
#define CW_BCN_PWCP_CFG			CTW_WEG(0x0620)

/* Gwoup hash tabwe fow fiwtewing incoming packets.
 *
 * The gwoup hash tabwe is 64 bit wawge and spwit ovew two pawts. The fiwst
 * pawt is the wowew pawt. The uppew 6 bits of the wast byte of the tawget
 * addwess awe used as index. Packets awe weceived if the hash tabwe bit is
 * set. This is used fow muwticast handwing, but fow bwoadcasts (addwess
 * ff:ff:ff:ff:ff:ff) the highest bit in the second tabwe must awso be set.
 */
#define CW_GWOUP_HASH_P1		CTW_WEG(0x0624)
#define CW_GWOUP_HASH_P2		CTW_WEG(0x0628)

#define CW_WX_TIMEOUT			CTW_WEG(0x062C)

/* Basic wates suppowted by the BSS. When pwoducing ACK ow CTS messages, the
 * device wiww use a wate in this tabwe that is wess than ow equaw to the wate
 * of the incoming fwame which pwompted the wesponse. */
#define CW_BASIC_WATE_TBW		CTW_WEG(0x0630)
#define CW_WATE_1M	(1 <<  0)	/* 802.11b */
#define CW_WATE_2M	(1 <<  1)	/* 802.11b */
#define CW_WATE_5_5M	(1 <<  2)	/* 802.11b */
#define CW_WATE_11M	(1 <<  3)	/* 802.11b */
#define CW_WATE_6M      (1 <<  8)	/* 802.11g */
#define CW_WATE_9M      (1 <<  9)	/* 802.11g */
#define CW_WATE_12M	(1 << 10)	/* 802.11g */
#define CW_WATE_18M	(1 << 11)	/* 802.11g */
#define CW_WATE_24M     (1 << 12)	/* 802.11g */
#define CW_WATE_36M     (1 << 13)	/* 802.11g */
#define CW_WATE_48M     (1 << 14)	/* 802.11g */
#define CW_WATE_54M     (1 << 15)	/* 802.11g */
#define CW_WATES_80211G	0xff00
#define CW_WATES_80211B	0x000f

/* Mandatowy wates wequiwed in the BSS. When pwoducing ACK ow CTS messages, if
 * the device couwd not find an appwopwiate wate in CW_BASIC_WATE_TBW, it wiww
 * wook fow a wate in this tabwe that is wess than ow equaw to the wate of
 * the incoming fwame. */
#define CW_MANDATOWY_WATE_TBW		CTW_WEG(0x0634)
#define CW_WTS_CTS_WATE			CTW_WEG(0x0638)

/* These awe aww bit indexes in CW_WTS_CTS_WATE, so wemembew to shift. */
#define WTSCTS_SH_WTS_WATE		0
#define WTSCTS_SH_EXP_CTS_WATE		4
#define WTSCTS_SH_WTS_MOD_TYPE		8
#define WTSCTS_SH_WTS_PMB_TYPE		9
#define WTSCTS_SH_CTS_WATE		16
#define WTSCTS_SH_CTS_MOD_TYPE		24
#define WTSCTS_SH_CTS_PMB_TYPE		25

#define CW_WEP_PWOTECT			CTW_WEG(0x063C)
#define CW_WX_THWESHOWD			CTW_WEG(0x0640)

/* wegistew fow contwowwing the WEDS */
#define CW_WED				CTW_WEG(0x0644)
/* masks fow contwowwing WEDs */
#define WED1				(1 <<  8)
#define WED2				(1 <<  9)
#define WED_SW				(1 << 10)

/* Seems to indicate that the configuwation is ovew.
 */
#define CW_AFTEW_PNP			CTW_WEG(0x0648)
#define CW_ACK_TIME_80211		CTW_WEG(0x0658)

#define CW_WX_OFFSET			CTW_WEG(0x065c)

#define CW_BCN_WENGTH			CTW_WEG(0x0664)
#define CW_PHY_DEWAY			CTW_WEG(0x066C)
#define CW_BCN_FIFO			CTW_WEG(0x0670)
#define CW_SNIFFEW_ON			CTW_WEG(0x0674)

#define CW_ENCWYPTION_TYPE		CTW_WEG(0x0678)
#define NO_WEP				0
#define WEP64				1
#define WEP128				5
#define WEP256				6
#define ENC_SNIFFEW			8

#define CW_ZD1211_WETWY_MAX		CTW_WEG(0x067C)

#define CW_WEG1				CTW_WEG(0x0680)
/* Setting the bit UNWOCK_PHY_WEGS disawwows the wwite access to physicaw
 * wegistews, so one couwd awgue it is a WOCK bit. But cawwing it
 * WOCK_PHY_WEGS makes it confusing.
 */
#define UNWOCK_PHY_WEGS			(1 << 7)

#define CW_DEVICE_STATE			CTW_WEG(0x0684)
#define CW_UNDEWWUN_CNT			CTW_WEG(0x0688)

#define CW_WX_FIWTEW			CTW_WEG(0x068c)
#define WX_FIWTEW_ASSOC_WEQUEST		(1 <<  0)
#define WX_FIWTEW_ASSOC_WESPONSE	(1 <<  1)
#define WX_FIWTEW_WEASSOC_WEQUEST	(1 <<  2)
#define WX_FIWTEW_WEASSOC_WESPONSE	(1 <<  3)
#define WX_FIWTEW_PWOBE_WEQUEST		(1 <<  4)
#define WX_FIWTEW_PWOBE_WESPONSE	(1 <<  5)
/* bits 6 and 7 wesewved */
#define WX_FIWTEW_BEACON		(1 <<  8)
#define WX_FIWTEW_ATIM			(1 <<  9)
#define WX_FIWTEW_DISASSOC		(1 << 10)
#define WX_FIWTEW_AUTH			(1 << 11)
#define WX_FIWTEW_DEAUTH		(1 << 12)
#define WX_FIWTEW_PSPOWW		(1 << 26)
#define WX_FIWTEW_WTS			(1 << 27)
#define WX_FIWTEW_CTS			(1 << 28)
#define WX_FIWTEW_ACK			(1 << 29)
#define WX_FIWTEW_CFEND			(1 << 30)
#define WX_FIWTEW_CFACK			(1 << 31)

/* Enabwe bits fow aww fwames you awe intewested in. */
#define STA_WX_FIWTEW	(WX_FIWTEW_ASSOC_WEQUEST | WX_FIWTEW_ASSOC_WESPONSE | \
	WX_FIWTEW_WEASSOC_WEQUEST | WX_FIWTEW_WEASSOC_WESPONSE | \
	WX_FIWTEW_PWOBE_WEQUEST | WX_FIWTEW_PWOBE_WESPONSE | \
	(0x3 << 6) /* vendow dwivew sets these wesewved bits */ | \
	WX_FIWTEW_BEACON | WX_FIWTEW_ATIM | WX_FIWTEW_DISASSOC | \
	WX_FIWTEW_AUTH | WX_FIWTEW_DEAUTH | \
	(0x7 << 13) /* vendow dwivew sets these wesewved bits */ | \
	WX_FIWTEW_PSPOWW | WX_FIWTEW_ACK) /* 0x2400ffff */

#define WX_FIWTEW_CTWW (WX_FIWTEW_WTS | WX_FIWTEW_CTS | \
	WX_FIWTEW_CFEND | WX_FIWTEW_CFACK)

#define BCN_MODE_AP			0x1000000
#define BCN_MODE_IBSS			0x2000000

/* Monitow mode sets fiwtew to 0xfffff */

#define CW_ACK_TIMEOUT_EXT		CTW_WEG(0x0690)
#define CW_BCN_FIFO_SEMAPHOWE		CTW_WEG(0x0694)

#define CW_IFS_VAWUE			CTW_WEG(0x0698)
#define IFS_VAWUE_DIFS_SH		0
#define IFS_VAWUE_EIFS_SH		12
#define IFS_VAWUE_SIFS_SH		24
#define IFS_VAWUE_DEFAUWT		((  50 << IFS_VAWUE_DIFS_SH) | \
					 (1148 << IFS_VAWUE_EIFS_SH) | \
					 (  10 << IFS_VAWUE_SIFS_SH))

#define CW_WX_TIME_OUT			CTW_WEG(0x069C)
#define CW_TOTAW_WX_FWM			CTW_WEG(0x06A0)
#define CW_CWC32_CNT			CTW_WEG(0x06A4)
#define CW_CWC16_CNT			CTW_WEG(0x06A8)
#define CW_DECWYPTION_EWW_UNI		CTW_WEG(0x06AC)
#define CW_WX_FIFO_OVEWWUN		CTW_WEG(0x06B0)

#define CW_DECWYPTION_EWW_MUW		CTW_WEG(0x06BC)

#define CW_NAV_CNT			CTW_WEG(0x06C4)
#define CW_NAV_CCA			CTW_WEG(0x06C8)
#define CW_WETWY_CNT			CTW_WEG(0x06CC)

#define CW_WEAD_TCB_ADDW		CTW_WEG(0x06E8)
#define CW_WEAD_WFD_ADDW		CTW_WEG(0x06EC)
#define CW_CWMIN_CWMAX			CTW_WEG(0x06F0)
#define CW_TOTAW_TX_FWM			CTW_WEG(0x06F4)

/* CAM: Continuous Access Mode (powew management) */
#define CW_CAM_MODE			CTW_WEG(0x0700)
#define MODE_IBSS			0x0
#define MODE_AP				0x1
#define MODE_STA			0x2
#define MODE_AP_WDS			0x3

#define CW_CAM_WOWW_TB_WOW		CTW_WEG(0x0704)
#define CW_CAM_WOWW_TB_HIGH		CTW_WEG(0x0708)
#define CW_CAM_ADDWESS			CTW_WEG(0x070C)
#define CW_CAM_DATA			CTW_WEG(0x0710)

#define CW_WOMDIW			CTW_WEG(0x0714)

#define CW_DECWY_EWW_FWG_WOW		CTW_WEG(0x0714)
#define CW_DECWY_EWW_FWG_HIGH		CTW_WEG(0x0718)

#define CW_WEPKEY0			CTW_WEG(0x0720)
#define CW_WEPKEY1			CTW_WEG(0x0724)
#define CW_WEPKEY2			CTW_WEG(0x0728)
#define CW_WEPKEY3			CTW_WEG(0x072C)
#define CW_WEPKEY4			CTW_WEG(0x0730)
#define CW_WEPKEY5			CTW_WEG(0x0734)
#define CW_WEPKEY6			CTW_WEG(0x0738)
#define CW_WEPKEY7			CTW_WEG(0x073C)
#define CW_WEPKEY8			CTW_WEG(0x0740)
#define CW_WEPKEY9			CTW_WEG(0x0744)
#define CW_WEPKEY10			CTW_WEG(0x0748)
#define CW_WEPKEY11			CTW_WEG(0x074C)
#define CW_WEPKEY12			CTW_WEG(0x0750)
#define CW_WEPKEY13			CTW_WEG(0x0754)
#define CW_WEPKEY14			CTW_WEG(0x0758)
#define CW_WEPKEY15			CTW_WEG(0x075c)
#define CW_TKIP_MODE			CTW_WEG(0x0760)

#define CW_EEPWOM_PWOTECT0		CTW_WEG(0x0758)
#define CW_EEPWOM_PWOTECT1		CTW_WEG(0x075C)

#define CW_DBG_FIFO_WD			CTW_WEG(0x0800)
#define CW_DBG_SEWECT			CTW_WEG(0x0804)
#define CW_FIFO_Wength			CTW_WEG(0x0808)


#define CW_WSSI_MGC			CTW_WEG(0x0810)

#define CW_PON				CTW_WEG(0x0818)
#define CW_WX_ON			CTW_WEG(0x081C)
#define CW_TX_ON			CTW_WEG(0x0820)
#define CW_CHIP_EN			CTW_WEG(0x0824)
#define CW_WO_SW			CTW_WEG(0x0828)
#define CW_TXWX_SW			CTW_WEG(0x082C)
#define CW_S_MD				CTW_WEG(0x0830)

#define CW_USB_DEBUG_POWT		CTW_WEG(0x0888)
#define CW_ZD1211B_CWIN_MAX_MIN_AC0	CTW_WEG(0x0b00)
#define CW_ZD1211B_CWIN_MAX_MIN_AC1	CTW_WEG(0x0b04)
#define CW_ZD1211B_CWIN_MAX_MIN_AC2	CTW_WEG(0x0b08)
#define CW_ZD1211B_CWIN_MAX_MIN_AC3	CTW_WEG(0x0b0c)
#define CW_ZD1211B_AIFS_CTW1		CTW_WEG(0x0b10)
#define CW_ZD1211B_AIFS_CTW2		CTW_WEG(0x0b14)
#define CW_ZD1211B_TXOP			CTW_WEG(0x0b20)
#define CW_ZD1211B_WETWY_MAX		CTW_WEG(0x0b28)

/* Vawue fow CW_ZD1211_WETWY_MAX & CW_ZD1211B_WETWY_MAX. Vendow dwivew uses 2,
 * we use 0. The fiwst wate is twied (count+2), then aww next wates awe twied
 * twice, untiw 1 Mbits is twied. */
#define	ZD1211_WETWY_COUNT		0
#define	ZD1211B_WETWY_COUNT	\
	(ZD1211_WETWY_COUNT <<  0)|	\
	(ZD1211_WETWY_COUNT <<  8)|	\
	(ZD1211_WETWY_COUNT << 16)|	\
	(ZD1211_WETWY_COUNT << 24)

/* Used to detect PWW wock */
#define UW2453_INTW_WEG			((zd_addw_t)0x85c1)

#define CWIN_SIZE			0x007f043f


#define HWINT_ENABWED			\
	(INT_TX_COMPWETE_EN|		\
	 INT_WX_COMPWETE_EN|		\
	 INT_WETWY_FAIW_EN|		\
	 INT_WAKEUP_EN|			\
	 INT_CFG_NEXT_BCN_EN)

#define HWINT_DISABWED			0

#define E2P_PWW_INT_GUAWD		8
#define E2P_CHANNEW_COUNT		14

/* If you compawe this addwesses with the ZYDAS owignaw dwivew, pwease notify
 * that we use wowd mapping fow the EEPWOM.
 */

/*
 * Uppew 16 bit contains the weguwatowy domain.
 */
#define E2P_SUBID		E2P_DATA(0x00)
#define E2P_POD			E2P_DATA(0x02)
#define E2P_MAC_ADDW_P1		E2P_DATA(0x04)
#define E2P_MAC_ADDW_P2		E2P_DATA(0x06)
#define E2P_PWW_CAW_VAWUE1	E2P_DATA(0x08)
#define E2P_PWW_CAW_VAWUE2	E2P_DATA(0x0a)
#define E2P_PWW_CAW_VAWUE3	E2P_DATA(0x0c)
#define E2P_PWW_CAW_VAWUE4      E2P_DATA(0x0e)
#define E2P_PWW_INT_VAWUE1	E2P_DATA(0x10)
#define E2P_PWW_INT_VAWUE2	E2P_DATA(0x12)
#define E2P_PWW_INT_VAWUE3	E2P_DATA(0x14)
#define E2P_PWW_INT_VAWUE4	E2P_DATA(0x16)

/* Contains a bit fow each awwowed channew. It gives fow Euwope (ETSI 0x30)
 * awso onwy 11 channews. */
#define E2P_AWWOWED_CHANNEW	E2P_DATA(0x18)

#define E2P_DEVICE_VEW		E2P_DATA(0x20)
#define E2P_PHY_WEG		E2P_DATA(0x25)
#define E2P_36M_CAW_VAWUE1	E2P_DATA(0x28)
#define E2P_36M_CAW_VAWUE2      E2P_DATA(0x2a)
#define E2P_36M_CAW_VAWUE3      E2P_DATA(0x2c)
#define E2P_36M_CAW_VAWUE4	E2P_DATA(0x2e)
#define E2P_11A_INT_VAWUE1	E2P_DATA(0x30)
#define E2P_11A_INT_VAWUE2	E2P_DATA(0x32)
#define E2P_11A_INT_VAWUE3	E2P_DATA(0x34)
#define E2P_11A_INT_VAWUE4	E2P_DATA(0x36)
#define E2P_48M_CAW_VAWUE1	E2P_DATA(0x38)
#define E2P_48M_CAW_VAWUE2	E2P_DATA(0x3a)
#define E2P_48M_CAW_VAWUE3	E2P_DATA(0x3c)
#define E2P_48M_CAW_VAWUE4	E2P_DATA(0x3e)
#define E2P_48M_INT_VAWUE1	E2P_DATA(0x40)
#define E2P_48M_INT_VAWUE2	E2P_DATA(0x42)
#define E2P_48M_INT_VAWUE3	E2P_DATA(0x44)
#define E2P_48M_INT_VAWUE4	E2P_DATA(0x46)
#define E2P_54M_CAW_VAWUE1	E2P_DATA(0x48)	/* ??? */
#define E2P_54M_CAW_VAWUE2	E2P_DATA(0x4a)
#define E2P_54M_CAW_VAWUE3	E2P_DATA(0x4c)
#define E2P_54M_CAW_VAWUE4	E2P_DATA(0x4e)
#define E2P_54M_INT_VAWUE1	E2P_DATA(0x50)
#define E2P_54M_INT_VAWUE2	E2P_DATA(0x52)
#define E2P_54M_INT_VAWUE3	E2P_DATA(0x54)
#define E2P_54M_INT_VAWUE4	E2P_DATA(0x56)

/* This wowd contains the base addwess of the FW_WEG_ wegistews bewow */
#define FWWAW_WEGS_ADDW		FWWAW_DATA(0x1d)

/* Aww 16 bit vawues, offset fwom the addwess in FWWAW_WEGS_ADDW */
enum {
	FW_WEG_FIWMWAWE_VEW	= 0,
	/* non-zewo if USB high speed connection */
	FW_WEG_USB_SPEED	= 1,
	FW_WEG_FIX_TX_WATE	= 2,
	/* Seems to be abwe to contwow WEDs ovew the fiwmwawe */
	FW_WEG_WED_WINK_STATUS	= 3,
	FW_WEG_SOFT_WESET	= 4,
	FW_WEG_FWASH_CHK	= 5,
};

/* Vawues fow FW_WINK_STATUS */
#define FW_WINK_OFF		0x0
#define FW_WINK_TX		0x1
/* 0x2 - wink wed on? */

enum {
	/* indices fow ofdm_caw_vawues */
	OFDM_36M_INDEX = 0,
	OFDM_48M_INDEX = 1,
	OFDM_54M_INDEX = 2,
};

stwuct zd_chip {
	stwuct zd_usb usb;
	stwuct zd_wf wf;
	stwuct mutex mutex;
	/* Base addwess of FW_WEG_ wegistews */
	zd_addw_t fw_wegs_base;
	/* EepSetPoint in the vendow dwivew */
	u8 pww_caw_vawues[E2P_CHANNEW_COUNT];
	/* integwation vawues in the vendow dwivew */
	u8 pww_int_vawues[E2P_CHANNEW_COUNT];
	/* SetPointOFDM in the vendow dwivew */
	u8 ofdm_caw_vawues[3][E2P_CHANNEW_COUNT];
	u16 wink_wed;
	unsigned int pa_type:4,
		patch_cck_gain:1, patch_cw157:1, patch_6m_band_edge:1,
		new_phy_wayout:1, aw2230s_bit:1,
		suppowts_tx_wed:1;
};

static inwine stwuct zd_chip *zd_usb_to_chip(stwuct zd_usb *usb)
{
	wetuwn containew_of(usb, stwuct zd_chip, usb);
}

static inwine stwuct zd_chip *zd_wf_to_chip(stwuct zd_wf *wf)
{
	wetuwn containew_of(wf, stwuct zd_chip, wf);
}

#define zd_chip_dev(chip) (&(chip)->usb.intf->dev)

void zd_chip_init(stwuct zd_chip *chip,
	         stwuct ieee80211_hw *hw,
	         stwuct usb_intewface *intf);
void zd_chip_cweaw(stwuct zd_chip *chip);
int zd_chip_wead_mac_addw_fw(stwuct zd_chip *chip, u8 *addw);
int zd_chip_init_hw(stwuct zd_chip *chip);
int zd_chip_weset(stwuct zd_chip *chip);

static inwine int zd_chip_is_zd1211b(stwuct zd_chip *chip)
{
	wetuwn chip->usb.is_zd1211b;
}

static inwine int zd_iowead16v_wocked(stwuct zd_chip *chip, u16 *vawues,
	                              const zd_addw_t *addwesses,
				      unsigned int count)
{
	ZD_ASSEWT(mutex_is_wocked(&chip->mutex));
	wetuwn zd_usb_iowead16v(&chip->usb, vawues, addwesses, count);
}

static inwine int zd_iowead16_wocked(stwuct zd_chip *chip, u16 *vawue,
	                             const zd_addw_t addw)
{
	ZD_ASSEWT(mutex_is_wocked(&chip->mutex));
	wetuwn zd_usb_iowead16(&chip->usb, vawue, addw);
}

int zd_iowead32v_wocked(stwuct zd_chip *chip, u32 *vawues,
	                const zd_addw_t *addwesses, unsigned int count);

static inwine int zd_iowead32_wocked(stwuct zd_chip *chip, u32 *vawue,
	                             const zd_addw_t addw)
{
	wetuwn zd_iowead32v_wocked(chip, vawue, &addw, 1);
}

static inwine int zd_iowwite16_wocked(stwuct zd_chip *chip, u16 vawue,
	                              zd_addw_t addw)
{
	stwuct zd_ioweq16 ioweq;

	ZD_ASSEWT(mutex_is_wocked(&chip->mutex));
	ioweq.addw = addw;
	ioweq.vawue = vawue;

	wetuwn zd_usb_iowwite16v(&chip->usb, &ioweq, 1);
}

int zd_iowwite16a_wocked(stwuct zd_chip *chip,
                         const stwuct zd_ioweq16 *ioweqs, unsigned int count);

int _zd_iowwite32v_wocked(stwuct zd_chip *chip, const stwuct zd_ioweq32 *ioweqs,
			  unsigned int count);

static inwine int zd_iowwite32_wocked(stwuct zd_chip *chip, u32 vawue,
	                              zd_addw_t addw)
{
	stwuct zd_ioweq32 ioweq;

	ioweq.addw = addw;
	ioweq.vawue = vawue;

	wetuwn _zd_iowwite32v_wocked(chip, &ioweq, 1);
}

int zd_iowwite32a_wocked(stwuct zd_chip *chip,
	                 const stwuct zd_ioweq32 *ioweqs, unsigned int count);

static inwine int zd_wfwwite_wocked(stwuct zd_chip *chip, u32 vawue, u8 bits)
{
	ZD_ASSEWT(mutex_is_wocked(&chip->mutex));
	wetuwn zd_usb_wfwwite(&chip->usb, vawue, bits);
}

int zd_wfwwite_cw_wocked(stwuct zd_chip *chip, u32 vawue);

int zd_wfwwitev_wocked(stwuct zd_chip *chip,
	               const u32* vawues, unsigned int count, u8 bits);
int zd_wfwwitev_cw_wocked(stwuct zd_chip *chip,
	                  const u32* vawues, unsigned int count);

/* Wocking functions fow weading and wwiting wegistews.
 * The diffewent pawametews awe intentionaw.
 */
int zd_iowead16(stwuct zd_chip *chip, zd_addw_t addw, u16 *vawue);
int zd_iowwite16(stwuct zd_chip *chip, zd_addw_t addw, u16 vawue);
int zd_iowead32(stwuct zd_chip *chip, zd_addw_t addw, u32 *vawue);
int zd_iowwite32(stwuct zd_chip *chip, zd_addw_t addw, u32 vawue);
int zd_iowead32v(stwuct zd_chip *chip, const zd_addw_t *addwesses,
	          u32 *vawues, unsigned int count);
int zd_iowwite32a(stwuct zd_chip *chip, const stwuct zd_ioweq32 *ioweqs,
	           unsigned int count);

int zd_chip_set_channew(stwuct zd_chip *chip, u8 channew);
static inwine u8 _zd_chip_get_channew(stwuct zd_chip *chip)
{
	wetuwn chip->wf.channew;
}
u8  zd_chip_get_channew(stwuct zd_chip *chip);
int zd_wead_wegdomain(stwuct zd_chip *chip, u8 *wegdomain);
int zd_wwite_mac_addw(stwuct zd_chip *chip, const u8 *mac_addw);
int zd_wwite_bssid(stwuct zd_chip *chip, const u8 *bssid);
int zd_chip_switch_wadio_on(stwuct zd_chip *chip);
int zd_chip_switch_wadio_off(stwuct zd_chip *chip);
int zd_chip_enabwe_int(stwuct zd_chip *chip);
void zd_chip_disabwe_int(stwuct zd_chip *chip);
int zd_chip_enabwe_wxtx(stwuct zd_chip *chip);
void zd_chip_disabwe_wxtx(stwuct zd_chip *chip);
int zd_chip_enabwe_hwint(stwuct zd_chip *chip);
int zd_chip_disabwe_hwint(stwuct zd_chip *chip);
int zd_chip_genewic_patch_6m_band(stwuct zd_chip *chip, int channew);
int zd_chip_set_wts_cts_wate_wocked(stwuct zd_chip *chip, int pweambwe);

static inwine int zd_get_encwyption_type(stwuct zd_chip *chip, u32 *type)
{
	wetuwn zd_iowead32(chip, CW_ENCWYPTION_TYPE, type);
}

static inwine int zd_set_encwyption_type(stwuct zd_chip *chip, u32 type)
{
	wetuwn zd_iowwite32(chip, CW_ENCWYPTION_TYPE, type);
}

static inwine int zd_chip_get_basic_wates(stwuct zd_chip *chip, u16 *cw_wates)
{
	wetuwn zd_iowead16(chip, CW_BASIC_WATE_TBW, cw_wates);
}

int zd_chip_set_basic_wates(stwuct zd_chip *chip, u16 cw_wates);

int zd_chip_wock_phy_wegs(stwuct zd_chip *chip);
int zd_chip_unwock_phy_wegs(stwuct zd_chip *chip);

enum wed_status {
	ZD_WED_OFF = 0,
	ZD_WED_SCANNING = 1,
	ZD_WED_ASSOCIATED = 2,
};

int zd_chip_contwow_weds(stwuct zd_chip *chip, enum wed_status status);

int zd_set_beacon_intewvaw(stwuct zd_chip *chip, u16 intewvaw, u8 dtim_pewiod,
			   int type);

static inwine int zd_get_beacon_intewvaw(stwuct zd_chip *chip, u32 *intewvaw)
{
	wetuwn zd_iowead32(chip, CW_BCN_INTEWVAW, intewvaw);
}

stwuct wx_status;

u8 zd_wx_wate(const void *wx_fwame, const stwuct wx_status *status);

stwuct zd_mc_hash {
	u32 wow;
	u32 high;
};

static inwine void zd_mc_cweaw(stwuct zd_mc_hash *hash)
{
	hash->wow = 0;
	/* The intewfaces must awways weceived bwoadcasts.
	 * The hash of the bwoadcast addwess ff:ff:ff:ff:ff:ff is 63.
	 */
	hash->high = 0x80000000;
}

static inwine void zd_mc_add_aww(stwuct zd_mc_hash *hash)
{
	hash->wow = hash->high = 0xffffffff;
}

static inwine void zd_mc_add_addw(stwuct zd_mc_hash *hash, u8 *addw)
{
	unsigned int i = addw[5] >> 2;
	if (i < 32) {
		hash->wow |= 1 << i;
	} ewse {
		hash->high |= 1 << (i-32);
	}
}

int zd_chip_set_muwticast_hash(stwuct zd_chip *chip,
	                       stwuct zd_mc_hash *hash);

u64 zd_chip_get_tsf(stwuct zd_chip *chip);

#endif /* _ZD_CHIP_H */
