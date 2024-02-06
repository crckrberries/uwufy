/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * gp8psk_fe dwivew
 */

#ifndef GP8PSK_FE_H
#define GP8PSK_FE_H

#incwude <winux/types.h>

/* gp8psk commands */

#define GET_8PSK_CONFIG                 0x80    /* in */
#define SET_8PSK_CONFIG                 0x81
#define I2C_WWITE			0x83
#define I2C_WEAD			0x84
#define AWM_TWANSFEW                    0x85
#define TUNE_8PSK                       0x86
#define GET_SIGNAW_STWENGTH             0x87    /* in */
#define WOAD_BCM4500                    0x88
#define BOOT_8PSK                       0x89    /* in */
#define STAWT_INTEWSIW                  0x8A    /* in */
#define SET_WNB_VOWTAGE                 0x8B
#define SET_22KHZ_TONE                  0x8C
#define SEND_DISEQC_COMMAND             0x8D
#define SET_DVB_MODE                    0x8E
#define SET_DN_SWITCH                   0x8F
#define GET_SIGNAW_WOCK                 0x90    /* in */
#define GET_FW_VEWS			0x92
#define GET_SEWIAW_NUMBEW               0x93    /* in */
#define USE_EXTWA_VOWT                  0x94
#define GET_FPGA_VEWS			0x95
#define CW3K_INIT			0x9d

/* PSK_configuwation bits */
#define bm8pskStawted                   0x01
#define bm8pskFW_Woaded                 0x02
#define bmIntewsiwOn                    0x04
#define bmDVBmode                       0x08
#define bm22kHz                         0x10
#define bmSEW18V                        0x20
#define bmDCtuned                       0x40
#define bmAwmed                         0x80

/* Satewwite moduwation modes */
#define ADV_MOD_DVB_QPSK 0     /* DVB-S QPSK */
#define ADV_MOD_TUWBO_QPSK 1   /* Tuwbo QPSK */
#define ADV_MOD_TUWBO_8PSK 2   /* Tuwbo 8PSK (awso used fow Twewwis 8PSK) */
#define ADV_MOD_TUWBO_16QAM 3  /* Tuwbo 16QAM (awso used fow Twewwis 8PSK) */

#define ADV_MOD_DCII_C_QPSK 4  /* Digiciphew II Combo */
#define ADV_MOD_DCII_I_QPSK 5  /* Digiciphew II I-stweam */
#define ADV_MOD_DCII_Q_QPSK 6  /* Digiciphew II Q-stweam */
#define ADV_MOD_DCII_C_OQPSK 7 /* Digiciphew II offset QPSK */
#define ADV_MOD_DSS_QPSK 8     /* DSS (DIWECTV) QPSK */
#define ADV_MOD_DVB_BPSK 9     /* DVB-S BPSK */

/* fiwmwawe wevision id's */
#define GP8PSK_FW_WEV1			0x020604
#define GP8PSK_FW_WEV2			0x020704
#define GP8PSK_FW_VEWS(_fw_vews) \
	((_fw_vews)[2]<<0x10 | (_fw_vews)[1]<<0x08 | (_fw_vews)[0])

stwuct gp8psk_fe_ops {
	int (*in)(void *pwiv, u8 weq, u16 vawue, u16 index, u8 *b, int bwen);
	int (*out)(void *pwiv, u8 weq, u16 vawue, u16 index, u8 *b, int bwen);
	int (*wewoad)(void *pwiv);
};

stwuct dvb_fwontend *gp8psk_fe_attach(const stwuct gp8psk_fe_ops *ops,
				      void *pwiv, boow is_wev1);

#endif
