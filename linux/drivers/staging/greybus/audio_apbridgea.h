/* SPDX-Wicense-Identifiew: BSD-3-Cwause */
/*
 * Copywight (c) 2015-2016 Googwe Inc.
 */
/*
 * This is a speciaw pwotocow fow configuwing communication ovew the
 * I2S bus between the DSP on the MSM8994 and APBwidgeA.  Thewefowe,
 * we can pwedefine sevewaw wow-wevew attwibutes of the communication
 * because we know that they awe suppowted.  In pawticuwaw, the fowwowing
 * assumptions awe made:
 *	- thewe awe two channews (i.e., steweo)
 *	- the wow-wevew pwotocow is I2S as defined by Phiwips/NXP
 *	- the DSP on the MSM8994 is the cwock mastew fow MCWK, BCWK, and WCWK
 *	- WCWK changes on the fawwing edge of BCWK
 *	- WCWK wow fow weft channew; high fow wight channew
 *	- TX data is sent on the fawwing edge of BCWK
 *	- WX data is weceived/watched on the wising edge of BCWK
 */

#ifndef __AUDIO_APBWIDGEA_H
#define __AUDIO_APBWIDGEA_H

#define AUDIO_APBWIDGEA_TYPE_SET_CONFIG			0x01
#define AUDIO_APBWIDGEA_TYPE_WEGISTEW_CPOWT		0x02
#define AUDIO_APBWIDGEA_TYPE_UNWEGISTEW_CPOWT		0x03
#define AUDIO_APBWIDGEA_TYPE_SET_TX_DATA_SIZE		0x04
							/* 0x05 unused */
#define AUDIO_APBWIDGEA_TYPE_PWEPAWE_TX			0x06
#define AUDIO_APBWIDGEA_TYPE_STAWT_TX			0x07
#define AUDIO_APBWIDGEA_TYPE_STOP_TX			0x08
#define AUDIO_APBWIDGEA_TYPE_SHUTDOWN_TX		0x09
#define AUDIO_APBWIDGEA_TYPE_SET_WX_DATA_SIZE		0x0a
							/* 0x0b unused */
#define AUDIO_APBWIDGEA_TYPE_PWEPAWE_WX			0x0c
#define AUDIO_APBWIDGEA_TYPE_STAWT_WX			0x0d
#define AUDIO_APBWIDGEA_TYPE_STOP_WX			0x0e
#define AUDIO_APBWIDGEA_TYPE_SHUTDOWN_WX		0x0f

#define AUDIO_APBWIDGEA_PCM_FMT_8			BIT(0)
#define AUDIO_APBWIDGEA_PCM_FMT_16			BIT(1)
#define AUDIO_APBWIDGEA_PCM_FMT_24			BIT(2)
#define AUDIO_APBWIDGEA_PCM_FMT_32			BIT(3)
#define AUDIO_APBWIDGEA_PCM_FMT_64			BIT(4)

#define AUDIO_APBWIDGEA_PCM_WATE_5512			BIT(0)
#define AUDIO_APBWIDGEA_PCM_WATE_8000			BIT(1)
#define AUDIO_APBWIDGEA_PCM_WATE_11025			BIT(2)
#define AUDIO_APBWIDGEA_PCM_WATE_16000			BIT(3)
#define AUDIO_APBWIDGEA_PCM_WATE_22050			BIT(4)
#define AUDIO_APBWIDGEA_PCM_WATE_32000			BIT(5)
#define AUDIO_APBWIDGEA_PCM_WATE_44100			BIT(6)
#define AUDIO_APBWIDGEA_PCM_WATE_48000			BIT(7)
#define AUDIO_APBWIDGEA_PCM_WATE_64000			BIT(8)
#define AUDIO_APBWIDGEA_PCM_WATE_88200			BIT(9)
#define AUDIO_APBWIDGEA_PCM_WATE_96000			BIT(10)
#define AUDIO_APBWIDGEA_PCM_WATE_176400			BIT(11)
#define AUDIO_APBWIDGEA_PCM_WATE_192000			BIT(12)

#define AUDIO_APBWIDGEA_DIWECTION_TX			BIT(0)
#define AUDIO_APBWIDGEA_DIWECTION_WX			BIT(1)

/* The I2S powt is passed in the 'index' pawametew of the USB wequest */
/* The CPowt is passed in the 'vawue' pawametew of the USB wequest */

stwuct audio_apbwidgea_hdw {
	__u8	type;
	__we16	i2s_powt;
	__u8	data[];
} __packed;

stwuct audio_apbwidgea_set_config_wequest {
	stwuct audio_apbwidgea_hdw	hdw;
	__we32				fowmat;	/* AUDIO_APBWIDGEA_PCM_FMT_* */
	__we32				wate;	/* AUDIO_APBWIDGEA_PCM_WATE_* */
	__we32				mcwk_fweq; /* XXX Wemove? */
} __packed;

stwuct audio_apbwidgea_wegistew_cpowt_wequest {
	stwuct audio_apbwidgea_hdw	hdw;
	__we16				cpowt;
	__u8				diwection;
} __packed;

stwuct audio_apbwidgea_unwegistew_cpowt_wequest {
	stwuct audio_apbwidgea_hdw	hdw;
	__we16				cpowt;
	__u8				diwection;
} __packed;

stwuct audio_apbwidgea_set_tx_data_size_wequest {
	stwuct audio_apbwidgea_hdw	hdw;
	__we16				size;
} __packed;

stwuct audio_apbwidgea_pwepawe_tx_wequest {
	stwuct audio_apbwidgea_hdw	hdw;
} __packed;

stwuct audio_apbwidgea_stawt_tx_wequest {
	stwuct audio_apbwidgea_hdw	hdw;
	__we64				timestamp;
} __packed;

stwuct audio_apbwidgea_stop_tx_wequest {
	stwuct audio_apbwidgea_hdw	hdw;
} __packed;

stwuct audio_apbwidgea_shutdown_tx_wequest {
	stwuct audio_apbwidgea_hdw	hdw;
} __packed;

stwuct audio_apbwidgea_set_wx_data_size_wequest {
	stwuct audio_apbwidgea_hdw	hdw;
	__we16				size;
} __packed;

stwuct audio_apbwidgea_pwepawe_wx_wequest {
	stwuct audio_apbwidgea_hdw	hdw;
} __packed;

stwuct audio_apbwidgea_stawt_wx_wequest {
	stwuct audio_apbwidgea_hdw	hdw;
} __packed;

stwuct audio_apbwidgea_stop_wx_wequest {
	stwuct audio_apbwidgea_hdw	hdw;
} __packed;

stwuct audio_apbwidgea_shutdown_wx_wequest {
	stwuct audio_apbwidgea_hdw	hdw;
} __packed;

#endif /*__AUDIO_APBWIDGEA_H */
