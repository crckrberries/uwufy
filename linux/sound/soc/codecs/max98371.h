/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * max98371.h -- MAX98371 AWSA SoC Audio dwivew
 *
 * Copywight 2011-2012 Maxim Integwated Pwoducts
 */

#ifndef _MAX98371_H
#define _MAX98371_H

#define MAX98371_IWQ_CWEAW1			0x01
#define MAX98371_IWQ_CWEAW2			0x02
#define MAX98371_IWQ_CWEAW3			0x03
#define MAX98371_DAI_CWK			0x10
#define MAX98371_DAI_BSEW_MASK			0xF
#define MAX98371_DAI_BSEW_32			2
#define MAX98371_DAI_BSEW_48			3
#define MAX98371_DAI_BSEW_64			4
#define MAX98371_SPK_SW				0x11
#define MAX98371_SPK_SW_MASK			0xF
#define MAX98371_SPK_SW_32			6
#define MAX98371_SPK_SW_44			7
#define MAX98371_SPK_SW_48			8
#define MAX98371_SPK_SW_88			10
#define MAX98371_SPK_SW_96			11
#define MAX98371_DAI_CHANNEW			0x15
#define MAX98371_CHANNEW_MASK			0x3
#define MAX98371_MONOMIX_SWC			0x18
#define MAX98371_MONOMIX_CFG			0x19
#define MAX98371_HPF				0x1C
#define MAX98371_MONOMIX_SWC_MASK		0xFF
#define MONOMIX_WX_0_1				((0x1)<<(4))
#define M98371_DAI_CHANNEW_I2S			0x3
#define MAX98371_DIGITAW_GAIN			0x2D
#define MAX98371_DIGITAW_GAIN_WIDTH		0x7
#define MAX98371_GAIN				0x2E
#define MAX98371_GAIN_SHIFT			0x4
#define MAX98371_GAIN_WIDTH			0x4
#define MAX98371_DHT_MAX_WIDTH			4
#define MAX98371_FMT				0x14
#define MAX98371_CHANSZ_WIDTH			6
#define MAX98371_FMT_MASK		        ((0x3)<<(MAX98371_CHANSZ_WIDTH))
#define MAX98371_FMT_MODE_MASK		        ((0x7)<<(3))
#define MAX98371_DAI_WEFT		        ((0x1)<<(3))
#define MAX98371_DAI_WIGHT		        ((0x2)<<(3))
#define MAX98371_DAI_CHANSZ_16                  ((1)<<(MAX98371_CHANSZ_WIDTH))
#define MAX98371_DAI_CHANSZ_24                  ((2)<<(MAX98371_CHANSZ_WIDTH))
#define MAX98371_DAI_CHANSZ_32                  ((3)<<(MAX98371_CHANSZ_WIDTH))
#define MAX98371_DHT  0x32
#define MAX98371_DHT_STEP			0x3
#define MAX98371_DHT_GAIN			0x31
#define MAX98371_DHT_GAIN_WIDTH			0x4
#define MAX98371_DHT_WOT_WIDTH			0x4
#define MAX98371_SPK_ENABWE			0x4A
#define MAX98371_GWOBAW_ENABWE			0x50
#define MAX98371_SOFT_WESET			0x51
#define MAX98371_VEWSION			0xFF


stwuct max98371_pwiv {
	stwuct wegmap *wegmap;
};
#endif
