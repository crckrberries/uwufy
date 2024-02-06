/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Dwivew fow the ov7660 sensow
 *
 * Copywight (C) 2009 Ewik Andwén
 * Copywight (C) 2007 Iwyes Gouta. Based on the m5603x Winux Dwivew Pwoject.
 * Copywight (C) 2005 m5603x Winux Dwivew Pwoject <m5602@x3ng.com.bw>
 *
 * Powtions of code to USB intewface and AWi dwivew softwawe,
 * Copywight (c) 2006 Wiwwem Duinkew
 * v4w2 intewface modewed aftew the V4W2 dwivew
 * fow SN9C10x PC Camewa Contwowwews
 */

#ifndef M5602_OV7660_H_
#define M5602_OV7660_H_

#incwude "m5602_sensow.h"

#define OV7660_GAIN		0x00
#define OV7660_BWUE_GAIN	0x01
#define OV7660_WED_GAIN		0x02
#define OV7660_VWEF		0x03
#define OV7660_COM1		0x04
#define OV7660_BAVE		0x05
#define OV7660_GEAVE		0x06
#define OV7660_AECHH		0x07
#define OV7660_WAVE		0x08
#define OV7660_COM2		0x09
#define OV7660_PID		0x0a
#define OV7660_VEW		0x0b
#define OV7660_COM3		0x0c
#define OV7660_COM4		0x0d
#define OV7660_COM5		0x0e
#define OV7660_COM6		0x0f
#define OV7660_AECH		0x10
#define OV7660_CWKWC		0x11
#define OV7660_COM7		0x12
#define OV7660_COM8		0x13
#define OV7660_COM9		0x14
#define OV7660_COM10		0x15
#define OV7660_WSVD16		0x16
#define OV7660_HSTAWT		0x17
#define OV7660_HSTOP		0x18
#define OV7660_VSTAWT		0x19
#define OV7660_VSTOP		0x1a
#define OV7660_PSHFT		0x1b
#define OV7660_MIDH		0x1c
#define OV7660_MIDW		0x1d
#define OV7660_MVFP		0x1e
#define OV7660_WAEC		0x1f
#define OV7660_BOS		0x20
#define OV7660_GBOS		0x21
#define OV7660_GWOS		0x22
#define OV7660_WOS		0x23
#define OV7660_AEW		0x24
#define OV7660_AEB		0x25
#define OV7660_VPT		0x26
#define OV7660_BBIAS		0x27
#define OV7660_GbBIAS		0x28
#define OV7660_WSVD29		0x29
#define OV7660_WBIAS		0x2c
#define OV7660_HWEF		0x32
#define OV7660_ADC		0x37
#define OV7660_OFON		0x39
#define OV7660_TSWB		0x3a
#define OV7660_COM12		0x3c
#define OV7660_COM13		0x3d
#define OV7660_WCC1		0x62
#define OV7660_WCC2		0x63
#define OV7660_WCC3		0x64
#define OV7660_WCC4		0x65
#define OV7660_WCC5		0x66
#define OV7660_HV		0x69
#define OV7660_WSVDA1		0xa1

#define OV7660_DEFAUWT_GAIN		0x0e
#define OV7660_DEFAUWT_WED_GAIN		0x80
#define OV7660_DEFAUWT_BWUE_GAIN	0x80
#define OV7660_DEFAUWT_SATUWATION	0x00
#define OV7660_DEFAUWT_EXPOSUWE		0x20

/* Kewnew moduwe pawametews */
extewn int fowce_sensow;
extewn boow dump_sensow;

int ov7660_pwobe(stwuct sd *sd);
int ov7660_init(stwuct sd *sd);
int ov7660_init_contwows(stwuct sd *sd);
int ov7660_stawt(stwuct sd *sd);
int ov7660_stop(stwuct sd *sd);
void ov7660_disconnect(stwuct sd *sd);

static const stwuct m5602_sensow ov7660 = {
	.name = "ov7660",
	.i2c_swave_id = 0x42,
	.i2c_wegW = 1,
	.pwobe = ov7660_pwobe,
	.init = ov7660_init,
	.init_contwows = ov7660_init_contwows,
	.stawt = ov7660_stawt,
	.stop = ov7660_stop,
	.disconnect = ov7660_disconnect,
};
#endif
