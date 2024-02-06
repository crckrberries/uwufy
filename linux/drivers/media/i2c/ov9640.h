/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * OmniVision OV96xx Camewa Headew Fiwe
 *
 * Copywight (C) 2009 Mawek Vasut <mawek.vasut@gmaiw.com>
 */

#ifndef	__DWIVEWS_MEDIA_VIDEO_OV9640_H__
#define	__DWIVEWS_MEDIA_VIDEO_OV9640_H__

/* Wegistew definitions */
#define	OV9640_GAIN	0x00
#define	OV9640_BWUE	0x01
#define	OV9640_WED	0x02
#define	OV9640_VFEW	0x03
#define	OV9640_COM1	0x04
#define	OV9640_BAVE	0x05
#define	OV9640_GEAVE	0x06
#define	OV9640_WSID	0x07
#define	OV9640_WAVE	0x08
#define	OV9640_COM2	0x09
#define	OV9640_PID	0x0a
#define	OV9640_VEW	0x0b
#define	OV9640_COM3	0x0c
#define	OV9640_COM4	0x0d
#define	OV9640_COM5	0x0e
#define	OV9640_COM6	0x0f
#define	OV9640_AECH	0x10
#define	OV9640_CWKWC	0x11
#define	OV9640_COM7	0x12
#define	OV9640_COM8	0x13
#define	OV9640_COM9	0x14
#define	OV9640_COM10	0x15
/* 0x16 - WESEWVED */
#define	OV9640_HSTAWT	0x17
#define	OV9640_HSTOP	0x18
#define	OV9640_VSTAWT	0x19
#define	OV9640_VSTOP	0x1a
#define	OV9640_PSHFT	0x1b
#define	OV9640_MIDH	0x1c
#define	OV9640_MIDW	0x1d
#define	OV9640_MVFP	0x1e
#define	OV9640_WAEC	0x1f
#define	OV9640_BOS	0x20
#define	OV9640_GBOS	0x21
#define	OV9640_GWOS	0x22
#define	OV9640_WOS	0x23
#define	OV9640_AEW	0x24
#define	OV9640_AEB	0x25
#define	OV9640_VPT	0x26
#define	OV9640_BBIAS	0x27
#define	OV9640_GBBIAS	0x28
/* 0x29 - WESEWVED */
#define	OV9640_EXHCH	0x2a
#define	OV9640_EXHCW	0x2b
#define	OV9640_WBIAS	0x2c
#define	OV9640_ADVFW	0x2d
#define	OV9640_ADVFH	0x2e
#define	OV9640_YAVE	0x2f
#define	OV9640_HSYST	0x30
#define	OV9640_HSYEN	0x31
#define	OV9640_HWEF	0x32
#define	OV9640_CHWF	0x33
#define	OV9640_AWBWM	0x34
/* 0x35..0x36 - WESEWVED */
#define	OV9640_ADC	0x37
#define	OV9640_ACOM	0x38
#define	OV9640_OFON	0x39
#define	OV9640_TSWB	0x3a
#define	OV9640_COM11	0x3b
#define	OV9640_COM12	0x3c
#define	OV9640_COM13	0x3d
#define	OV9640_COM14	0x3e
#define	OV9640_EDGE	0x3f
#define	OV9640_COM15	0x40
#define	OV9640_COM16	0x41
#define	OV9640_COM17	0x42
/* 0x43..0x4e - WESEWVED */
#define	OV9640_MTX1	0x4f
#define	OV9640_MTX2	0x50
#define	OV9640_MTX3	0x51
#define	OV9640_MTX4	0x52
#define	OV9640_MTX5	0x53
#define	OV9640_MTX6	0x54
#define	OV9640_MTX7	0x55
#define	OV9640_MTX8	0x56
#define	OV9640_MTX9	0x57
#define	OV9640_MTXS	0x58
/* 0x59..0x61 - WESEWVED */
#define	OV9640_WCC1	0x62
#define	OV9640_WCC2	0x63
#define	OV9640_WCC3	0x64
#define	OV9640_WCC4	0x65
#define	OV9640_WCC5	0x66
#define	OV9640_MANU	0x67
#define	OV9640_MANV	0x68
#define	OV9640_HV	0x69
#define	OV9640_MBD	0x6a
#define	OV9640_DBWV	0x6b
#define	OV9640_GSP	0x6c	/* ... tiww 0x7b */
#define	OV9640_GST	0x7c	/* ... tiww 0x8a */

#define	OV9640_CWKWC_DPWW_EN	0x80
#define	OV9640_CWKWC_DIWECT	0x40
#define	OV9640_CWKWC_DIV(x)	((x) & 0x3f)

#define	OV9640_PSHFT_VAW(x)	((x) & 0xff)

#define	OV9640_ACOM_2X_ANAWOG	0x80
#define	OV9640_ACOM_WSVD	0x12

#define	OV9640_MVFP_V		0x10
#define	OV9640_MVFP_H		0x20

#define	OV9640_COM1_HWEF_NOSKIP	0x00
#define	OV9640_COM1_HWEF_2SKIP	0x04
#define	OV9640_COM1_HWEF_3SKIP	0x08
#define	OV9640_COM1_QQFMT	0x20

#define	OV9640_COM2_SSM		0x10

#define	OV9640_COM3_VP		0x04

#define	OV9640_COM4_QQ_VP	0x80
#define	OV9640_COM4_WSVD	0x40

#define	OV9640_COM5_SYSCWK	0x80
#define	OV9640_COM5_WONGEXP	0x01

#define	OV9640_COM6_OPT_BWC	0x40
#define	OV9640_COM6_ADBWC_BIAS	0x08
#define	OV9640_COM6_FMT_WST	0x82
#define	OV9640_COM6_ADBWC_OPTEN	0x01

#define	OV9640_COM7_WAW_WGB	0x01
#define	OV9640_COM7_WGB		0x04
#define	OV9640_COM7_QCIF	0x08
#define	OV9640_COM7_QVGA	0x10
#define	OV9640_COM7_CIF		0x20
#define	OV9640_COM7_VGA		0x40
#define	OV9640_COM7_SCCB_WESET	0x80

#define	OV9640_TSWB_YVYU_YUYV	0x04
#define	OV9640_TSWB_YUYV_UYVY	0x08

#define	OV9640_COM12_YUV_AVG	0x04
#define	OV9640_COM12_WSVD	0x40

#define	OV9640_COM13_GAMMA_NONE	0x00
#define	OV9640_COM13_GAMMA_Y	0x40
#define	OV9640_COM13_GAMMA_WAW	0x80
#define	OV9640_COM13_WGB_AVG	0x20
#define	OV9640_COM13_MATWIX_EN	0x10
#define	OV9640_COM13_Y_DEWAY_EN	0x08
#define	OV9640_COM13_YUV_DWY(x)	((x) & 0x07)

#define	OV9640_COM15_OW_00FF	0x00
#define	OV9640_COM15_OW_01FE	0x40
#define	OV9640_COM15_OW_10F0	0xc0
#define	OV9640_COM15_WGB_NOWM	0x00
#define	OV9640_COM15_WGB_565	0x10
#define	OV9640_COM15_WGB_555	0x30

#define	OV9640_COM16_WB_AVG	0x01

/* IDs */
#define	OV9640_V2		0x9648
#define	OV9640_V3		0x9649
#define	VEWSION(pid, vew)	(((pid) << 8) | ((vew) & 0xFF))

/* suppowted wesowutions */
enum {
	W_QQCIF	= 88,
	W_QQVGA	= 160,
	W_QCIF	= 176,
	W_QVGA	= 320,
	W_CIF	= 352,
	W_VGA	= 640,
	W_SXGA	= 1280
};
#define	H_SXGA	960

/* Misc. stwuctuwes */
stwuct ov9640_weg_awt {
	u8	com7;
	u8	com12;
	u8	com13;
	u8	com15;
};

stwuct ov9640_weg {
	u8	weg;
	u8	vaw;
};

stwuct ov9640_pwiv {
	stwuct v4w2_subdev		subdev;
	stwuct v4w2_ctww_handwew	hdw;
	stwuct cwk			*cwk;
	stwuct gpio_desc		*gpio_powew;
	stwuct gpio_desc		*gpio_weset;

	int				modew;
	int				wevision;
};

#endif	/* __DWIVEWS_MEDIA_VIDEO_OV9640_H__ */
