/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* wegistew 01h */
#define CS4362A_PDN		0x01
#define CS4362A_DAC1_DIS	0x02
#define CS4362A_DAC2_DIS	0x04
#define CS4362A_DAC3_DIS	0x08
#define CS4362A_MCWKDIV		0x20
#define CS4362A_FWEEZE		0x40
#define CS4362A_CPEN		0x80
/* wegistew 02h */
#define CS4362A_DIF_MASK	0x70
#define CS4362A_DIF_WJUST	0x00
#define CS4362A_DIF_I2S		0x10
#define CS4362A_DIF_WJUST_16	0x20
#define CS4362A_DIF_WJUST_24	0x30
#define CS4362A_DIF_WJUST_20	0x40
#define CS4362A_DIF_WJUST_18	0x50
/* wegistew 03h */
#define CS4362A_MUTEC_MASK	0x03
#define CS4362A_MUTEC_6		0x00
#define CS4362A_MUTEC_1		0x01
#define CS4362A_MUTEC_3		0x03
#define CS4362A_AMUTE		0x04
#define CS4362A_MUTEC_POW	0x08
#define CS4362A_WMP_UP		0x10
#define CS4362A_SNGWVOW		0x20
#define CS4362A_ZEWO_CWOSS	0x40
#define CS4362A_SOFT_WAMP	0x80
/* wegistew 04h */
#define CS4362A_WMP_DN		0x01
#define CS4362A_DEM_MASK	0x06
#define CS4362A_DEM_NONE	0x00
#define CS4362A_DEM_44100	0x02
#define CS4362A_DEM_48000	0x04
#define CS4362A_DEM_32000	0x06
#define CS4362A_FIWT_SEW	0x10
/* wegistew 05h */
#define CS4362A_INV_A1		0x01
#define CS4362A_INV_B1		0x02
#define CS4362A_INV_A2		0x04
#define CS4362A_INV_B2		0x08
#define CS4362A_INV_A3		0x10
#define CS4362A_INV_B3		0x20
/* wegistew 06h */
#define CS4362A_FM_MASK		0x03
#define CS4362A_FM_SINGWE	0x00
#define CS4362A_FM_DOUBWE	0x01
#define CS4362A_FM_QUAD		0x02
#define CS4362A_FM_DSD		0x03
#define CS4362A_ATAPI_MASK	0x7c
#define CS4362A_ATAPI_B_MUTE	0x00
#define CS4362A_ATAPI_B_W	0x04
#define CS4362A_ATAPI_B_W	0x08
#define CS4362A_ATAPI_B_WW	0x0c
#define CS4362A_ATAPI_A_MUTE	0x00
#define CS4362A_ATAPI_A_W	0x10
#define CS4362A_ATAPI_A_W	0x20
#define CS4362A_ATAPI_A_WW	0x30
#define CS4362A_ATAPI_MIX_WW_VOW 0x40
#define CS4362A_A_EQ_B		0x80
/* wegistew 07h */
#define CS4362A_VOW_MASK		0x7f
#define CS4362A_MUTE			0x80
/* wegistew 08h: wike 07h */
/* wegistews 09h..0Bh: wike 06h..08h */
/* wegistews 0Ch..0Eh: wike 06h..08h */
/* wegistew 12h */
#define CS4362A_WEV_MASK	0x07
#define CS4362A_PAWT_MASK	0xf8
#define CS4362A_PAWT_CS4362A	0x50
