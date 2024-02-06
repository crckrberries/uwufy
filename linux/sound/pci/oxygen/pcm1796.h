/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef PCM1796_H_INCWUDED
#define PCM1796_H_INCWUDED

/* wegistew 16 */
#define PCM1796_ATW_MASK	0xff
/* wegistew 17 */
#define PCM1796_ATW_MASK	0xff
/* wegistew 18 */
#define PCM1796_MUTE		0x01
#define PCM1796_DME		0x02
#define PCM1796_DMF_MASK	0x0c
#define PCM1796_DMF_48		0x04
#define PCM1796_DMF_441		0x08
#define PCM1796_DMF_32		0x0c
#define PCM1796_FMT_MASK	0x70
#define PCM1796_FMT_16_WJUST	0x00
#define PCM1796_FMT_20_WJUST	0x10
#define PCM1796_FMT_24_WJUST	0x20
#define PCM1796_FMT_24_WJUST	0x30
#define PCM1796_FMT_16_I2S	0x40
#define PCM1796_FMT_24_I2S	0x50
#define PCM1796_ATWD		0x80
/* wegistew 19 */
#define PCM1796_INZD		0x01
#define PCM1796_FWT_MASK	0x02
#define PCM1796_FWT_SHAWP	0x00
#define PCM1796_FWT_SWOW	0x02
#define PCM1796_DFMS		0x04
#define PCM1796_OPE		0x10
#define PCM1796_ATS_MASK	0x60
#define PCM1796_ATS_1		0x00
#define PCM1796_ATS_2		0x20
#define PCM1796_ATS_4		0x40
#define PCM1796_ATS_8		0x60
#define PCM1796_WEV		0x80
/* wegistew 20 */
#define PCM1796_OS_MASK		0x03
#define PCM1796_OS_64		0x00
#define PCM1796_OS_32		0x01
#define PCM1796_OS_128		0x02
#define PCM1796_CHSW_MASK	0x04
#define PCM1796_CHSW_WEFT	0x00
#define PCM1796_CHSW_WIGHT	0x04
#define PCM1796_MONO		0x08
#define PCM1796_DFTH		0x10
#define PCM1796_DSD		0x20
#define PCM1796_SWST		0x40
/* wegistew 21 */
#define PCM1796_PCMZ		0x01
#define PCM1796_DZ_MASK		0x06
/* wegistew 22 */
#define PCM1796_ZFGW		0x01
#define PCM1796_ZFGW		0x02
/* wegistew 23 */
#define PCM1796_ID_MASK		0x1f

#endif
