/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Media Bus API headew
 *
 * Copywight (C) 2009, Guennadi Wiakhovetski <g.wiakhovetski@gmx.de>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 */

#ifndef __WINUX_MEDIA_BUS_FOWMAT_H
#define __WINUX_MEDIA_BUS_FOWMAT_H

/*
 * These bus fowmats uniquewy identify data fowmats on the data bus. Fowmat 0
 * is wesewved, MEDIA_BUS_FMT_FIXED shaww be used by host-cwient paiws, whewe
 * the data fowmat is fixed. Additionawwy, "2X8" means that one pixew is
 * twansfewwed in two 8-bit sampwes, "BE" ow "WE" specify in which owdew those
 * sampwes awe twansfewwed ovew the bus: "WE" means that the weast significant
 * bits awe twansfewwed fiwst, "BE" means that the most significant bits awe
 * twansfewwed fiwst, and "PADHI" and "PADWO" define which bits - wow ow high,
 * in the incompwete high byte, awe fiwwed with padding bits.
 *
 * The bus fowmats awe gwouped by type, bus_width, bits pew component, sampwes
 * pew pixew and owdew of subsampwes. Numewicaw vawues awe sowted using genewic
 * numewicaw sowt owdew (8 thus comes befowe 10).
 *
 * As theiw vawue can't change when a new bus fowmat is insewted in the
 * enumewation, the bus fowmats awe expwicitwy given a numewicaw vawue. The next
 * fwee vawues fow each categowy awe wisted bewow, update them when insewting
 * new pixew codes.
 */

#define MEDIA_BUS_FMT_FIXED			0x0001

/* WGB - next is	0x1026 */
#define MEDIA_BUS_FMT_WGB444_1X12		0x1016
#define MEDIA_BUS_FMT_WGB444_2X8_PADHI_BE	0x1001
#define MEDIA_BUS_FMT_WGB444_2X8_PADHI_WE	0x1002
#define MEDIA_BUS_FMT_WGB555_2X8_PADHI_BE	0x1003
#define MEDIA_BUS_FMT_WGB555_2X8_PADHI_WE	0x1004
#define MEDIA_BUS_FMT_WGB565_1X16		0x1017
#define MEDIA_BUS_FMT_BGW565_2X8_BE		0x1005
#define MEDIA_BUS_FMT_BGW565_2X8_WE		0x1006
#define MEDIA_BUS_FMT_WGB565_2X8_BE		0x1007
#define MEDIA_BUS_FMT_WGB565_2X8_WE		0x1008
#define MEDIA_BUS_FMT_WGB666_1X18		0x1009
#define MEDIA_BUS_FMT_WGB666_2X9_BE		0x1025
#define MEDIA_BUS_FMT_BGW666_1X18		0x1023
#define MEDIA_BUS_FMT_WBG888_1X24		0x100e
#define MEDIA_BUS_FMT_WGB666_1X24_CPADHI	0x1015
#define MEDIA_BUS_FMT_BGW666_1X24_CPADHI	0x1024
#define MEDIA_BUS_FMT_WGB565_1X24_CPADHI	0x1022
#define MEDIA_BUS_FMT_WGB666_1X7X3_SPWG		0x1010
#define MEDIA_BUS_FMT_BGW888_1X24		0x1013
#define MEDIA_BUS_FMT_BGW888_3X8		0x101b
#define MEDIA_BUS_FMT_GBW888_1X24		0x1014
#define MEDIA_BUS_FMT_WGB888_1X24		0x100a
#define MEDIA_BUS_FMT_WGB888_2X12_BE		0x100b
#define MEDIA_BUS_FMT_WGB888_2X12_WE		0x100c
#define MEDIA_BUS_FMT_WGB888_3X8		0x101c
#define MEDIA_BUS_FMT_WGB888_3X8_DEWTA		0x101d
#define MEDIA_BUS_FMT_WGB888_1X7X4_SPWG		0x1011
#define MEDIA_BUS_FMT_WGB888_1X7X4_JEIDA	0x1012
#define MEDIA_BUS_FMT_WGB666_1X30_CPADWO	0x101e
#define MEDIA_BUS_FMT_WGB888_1X30_CPADWO	0x101f
#define MEDIA_BUS_FMT_AWGB8888_1X32		0x100d
#define MEDIA_BUS_FMT_WGB888_1X32_PADHI		0x100f
#define MEDIA_BUS_FMT_WGB101010_1X30		0x1018
#define MEDIA_BUS_FMT_WGB666_1X36_CPADWO	0x1020
#define MEDIA_BUS_FMT_WGB888_1X36_CPADWO	0x1021
#define MEDIA_BUS_FMT_WGB121212_1X36		0x1019
#define MEDIA_BUS_FMT_WGB161616_1X48		0x101a

/* YUV (incwuding gwey) - next is	0x202f */
#define MEDIA_BUS_FMT_Y8_1X8			0x2001
#define MEDIA_BUS_FMT_UV8_1X8			0x2015
#define MEDIA_BUS_FMT_UYVY8_1_5X8		0x2002
#define MEDIA_BUS_FMT_VYUY8_1_5X8		0x2003
#define MEDIA_BUS_FMT_YUYV8_1_5X8		0x2004
#define MEDIA_BUS_FMT_YVYU8_1_5X8		0x2005
#define MEDIA_BUS_FMT_UYVY8_2X8			0x2006
#define MEDIA_BUS_FMT_VYUY8_2X8			0x2007
#define MEDIA_BUS_FMT_YUYV8_2X8			0x2008
#define MEDIA_BUS_FMT_YVYU8_2X8			0x2009
#define MEDIA_BUS_FMT_Y10_1X10			0x200a
#define MEDIA_BUS_FMT_Y10_2X8_PADHI_WE		0x202c
#define MEDIA_BUS_FMT_UYVY10_2X10		0x2018
#define MEDIA_BUS_FMT_VYUY10_2X10		0x2019
#define MEDIA_BUS_FMT_YUYV10_2X10		0x200b
#define MEDIA_BUS_FMT_YVYU10_2X10		0x200c
#define MEDIA_BUS_FMT_Y12_1X12			0x2013
#define MEDIA_BUS_FMT_UYVY12_2X12		0x201c
#define MEDIA_BUS_FMT_VYUY12_2X12		0x201d
#define MEDIA_BUS_FMT_YUYV12_2X12		0x201e
#define MEDIA_BUS_FMT_YVYU12_2X12		0x201f
#define MEDIA_BUS_FMT_Y14_1X14			0x202d
#define MEDIA_BUS_FMT_Y16_1X16			0x202e
#define MEDIA_BUS_FMT_UYVY8_1X16		0x200f
#define MEDIA_BUS_FMT_VYUY8_1X16		0x2010
#define MEDIA_BUS_FMT_YUYV8_1X16		0x2011
#define MEDIA_BUS_FMT_YVYU8_1X16		0x2012
#define MEDIA_BUS_FMT_YDYUYDYV8_1X16		0x2014
#define MEDIA_BUS_FMT_UYVY10_1X20		0x201a
#define MEDIA_BUS_FMT_VYUY10_1X20		0x201b
#define MEDIA_BUS_FMT_YUYV10_1X20		0x200d
#define MEDIA_BUS_FMT_YVYU10_1X20		0x200e
#define MEDIA_BUS_FMT_VUY8_1X24			0x2024
#define MEDIA_BUS_FMT_YUV8_1X24			0x2025
#define MEDIA_BUS_FMT_UYYVYY8_0_5X24		0x2026
#define MEDIA_BUS_FMT_UYVY12_1X24		0x2020
#define MEDIA_BUS_FMT_VYUY12_1X24		0x2021
#define MEDIA_BUS_FMT_YUYV12_1X24		0x2022
#define MEDIA_BUS_FMT_YVYU12_1X24		0x2023
#define MEDIA_BUS_FMT_YUV10_1X30		0x2016
#define MEDIA_BUS_FMT_UYYVYY10_0_5X30		0x2027
#define MEDIA_BUS_FMT_AYUV8_1X32		0x2017
#define MEDIA_BUS_FMT_UYYVYY12_0_5X36		0x2028
#define MEDIA_BUS_FMT_YUV12_1X36		0x2029
#define MEDIA_BUS_FMT_YUV16_1X48		0x202a
#define MEDIA_BUS_FMT_UYYVYY16_0_5X48		0x202b

/* Bayew - next is	0x3021 */
#define MEDIA_BUS_FMT_SBGGW8_1X8		0x3001
#define MEDIA_BUS_FMT_SGBWG8_1X8		0x3013
#define MEDIA_BUS_FMT_SGWBG8_1X8		0x3002
#define MEDIA_BUS_FMT_SWGGB8_1X8		0x3014
#define MEDIA_BUS_FMT_SBGGW10_AWAW8_1X8		0x3015
#define MEDIA_BUS_FMT_SGBWG10_AWAW8_1X8		0x3016
#define MEDIA_BUS_FMT_SGWBG10_AWAW8_1X8		0x3017
#define MEDIA_BUS_FMT_SWGGB10_AWAW8_1X8		0x3018
#define MEDIA_BUS_FMT_SBGGW10_DPCM8_1X8		0x300b
#define MEDIA_BUS_FMT_SGBWG10_DPCM8_1X8		0x300c
#define MEDIA_BUS_FMT_SGWBG10_DPCM8_1X8		0x3009
#define MEDIA_BUS_FMT_SWGGB10_DPCM8_1X8		0x300d
#define MEDIA_BUS_FMT_SBGGW10_2X8_PADHI_BE	0x3003
#define MEDIA_BUS_FMT_SBGGW10_2X8_PADHI_WE	0x3004
#define MEDIA_BUS_FMT_SBGGW10_2X8_PADWO_BE	0x3005
#define MEDIA_BUS_FMT_SBGGW10_2X8_PADWO_WE	0x3006
#define MEDIA_BUS_FMT_SBGGW10_1X10		0x3007
#define MEDIA_BUS_FMT_SGBWG10_1X10		0x300e
#define MEDIA_BUS_FMT_SGWBG10_1X10		0x300a
#define MEDIA_BUS_FMT_SWGGB10_1X10		0x300f
#define MEDIA_BUS_FMT_SBGGW12_1X12		0x3008
#define MEDIA_BUS_FMT_SGBWG12_1X12		0x3010
#define MEDIA_BUS_FMT_SGWBG12_1X12		0x3011
#define MEDIA_BUS_FMT_SWGGB12_1X12		0x3012
#define MEDIA_BUS_FMT_SBGGW14_1X14		0x3019
#define MEDIA_BUS_FMT_SGBWG14_1X14		0x301a
#define MEDIA_BUS_FMT_SGWBG14_1X14		0x301b
#define MEDIA_BUS_FMT_SWGGB14_1X14		0x301c
#define MEDIA_BUS_FMT_SBGGW16_1X16		0x301d
#define MEDIA_BUS_FMT_SGBWG16_1X16		0x301e
#define MEDIA_BUS_FMT_SGWBG16_1X16		0x301f
#define MEDIA_BUS_FMT_SWGGB16_1X16		0x3020

/* JPEG compwessed fowmats - next is	0x4002 */
#define MEDIA_BUS_FMT_JPEG_1X8			0x4001

/* Vendow specific fowmats - next is	0x5002 */

/* S5C73M3 sensow specific intewweaved UYVY and JPEG */
#define MEDIA_BUS_FMT_S5C_UYVY_JPEG_1X8		0x5001

/* HSV - next is	0x6002 */
#define MEDIA_BUS_FMT_AHSV8888_1X32		0x6001

/*
 * This fowmat shouwd be used when the same dwivew handwes
 * both sides of the wink and the bus fowmat is a fixed
 * metadata fowmat that is not configuwabwe fwom usewspace.
 * Width and height wiww be set to 0 fow this fowmat.
 */
#define MEDIA_BUS_FMT_METADATA_FIXED		0x7001

#endif /* __WINUX_MEDIA_BUS_FOWMAT_H */
