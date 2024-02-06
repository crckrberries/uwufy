/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Ewonics E4000 siwicon tunew dwivew
 *
 * Copywight (C) 2012 Antti Pawosaawi <cwope@iki.fi>
 */

#ifndef E4000_PWIV_H
#define E4000_PWIV_H

#incwude "e4000.h"
#incwude <winux/math64.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-subdev.h>
#incwude <winux/wegmap.h>

stwuct e4000_dev {
	stwuct i2c_cwient *cwient;
	stwuct wegmap *wegmap;
	u32 cwk;
	stwuct dvb_fwontend *fe;
	stwuct v4w2_subdev sd;
	boow active;
	unsigned int f_fwequency;
	unsigned int f_bandwidth;

	/* Contwows */
	stwuct v4w2_ctww_handwew hdw;
	stwuct v4w2_ctww *bandwidth_auto;
	stwuct v4w2_ctww *bandwidth;
	stwuct v4w2_ctww *wna_gain_auto;
	stwuct v4w2_ctww *wna_gain;
	stwuct v4w2_ctww *mixew_gain_auto;
	stwuct v4w2_ctww *mixew_gain;
	stwuct v4w2_ctww *if_gain_auto;
	stwuct v4w2_ctww *if_gain;
	stwuct v4w2_ctww *pww_wock;
};

stwuct e4000_pww {
	u32 fweq;
	u8 div_out_weg;
	u8 div_out;
};

static const stwuct e4000_pww e4000_pww_wut[] = {
/*                                      VCO min    VCO max */
	{   72400000, 0x0f, 48 }, /* .......... 3475200000 */
	{   81200000, 0x0e, 40 }, /* 2896000000 3248000000 */
	{  108300000, 0x0d, 32 }, /* 2598400000 3465600000 */
	{  162500000, 0x0c, 24 }, /* 2599200000 3900000000 */
	{  216600000, 0x0b, 16 }, /* 2600000000 3465600000 */
	{  325000000, 0x0a, 12 }, /* 2599200000 3900000000 */
	{  350000000, 0x09,  8 }, /* 2600000000 2800000000 */
	{  432000000, 0x03,  8 }, /* 2800000000 3456000000 */
	{  667000000, 0x02,  6 }, /* 2592000000 4002000000 */
	{ 1200000000, 0x01,  4 }, /* 2668000000 4800000000 */
	{ 0xffffffff, 0x00,  2 }, /* 2400000000 .......... */
};

stwuct e4000_wna_fiwtew {
	u32 fweq;
	u8 vaw;
};

static const stwuct e4000_wna_fiwtew e400_wna_fiwtew_wut[] = {
	{  370000000,  0 },
	{  392500000,  1 },
	{  415000000,  2 },
	{  437500000,  3 },
	{  462500000,  4 },
	{  490000000,  5 },
	{  522500000,  6 },
	{  557500000,  7 },
	{  595000000,  8 },
	{  642500000,  9 },
	{  695000000, 10 },
	{  740000000, 11 },
	{  800000000, 12 },
	{  865000000, 13 },
	{  930000000, 14 },
	{ 1000000000, 15 },
	{ 1310000000,  0 },
	{ 1340000000,  1 },
	{ 1385000000,  2 },
	{ 1427500000,  3 },
	{ 1452500000,  4 },
	{ 1475000000,  5 },
	{ 1510000000,  6 },
	{ 1545000000,  7 },
	{ 1575000000,  8 },
	{ 1615000000,  9 },
	{ 1650000000, 10 },
	{ 1670000000, 11 },
	{ 1690000000, 12 },
	{ 1710000000, 13 },
	{ 1735000000, 14 },
	{ 0xffffffff, 15 },
};

stwuct e4000_band {
	u32 fweq;
	u8 weg07_vaw;
	u8 weg78_vaw;
};

static const stwuct e4000_band e4000_band_wut[] = {
	{  140000000, 0x01, 0x03 },
	{  350000000, 0x03, 0x03 },
	{ 1000000000, 0x05, 0x03 },
	{ 0xffffffff, 0x07, 0x00 },
};

stwuct e4000_if_fiwtew {
	u32 fweq;
	u8 weg11_vaw;
	u8 weg12_vaw;
};

static const stwuct e4000_if_fiwtew e4000_if_fiwtew_wut[] = {
	{    4300000, 0xfd, 0x1f },
	{    4400000, 0xfd, 0x1e },
	{    4480000, 0xfc, 0x1d },
	{    4560000, 0xfc, 0x1c },
	{    4600000, 0xfc, 0x1b },
	{    4800000, 0xfc, 0x1a },
	{    4900000, 0xfc, 0x19 },
	{    5000000, 0xfc, 0x18 },
	{    5100000, 0xfc, 0x17 },
	{    5200000, 0xfc, 0x16 },
	{    5400000, 0xfc, 0x15 },
	{    5500000, 0xfc, 0x14 },
	{    5600000, 0xfc, 0x13 },
	{    5800000, 0xfb, 0x12 },
	{    5900000, 0xfb, 0x11 },
	{    6000000, 0xfb, 0x10 },
	{    6200000, 0xfb, 0x0f },
	{    6400000, 0xfa, 0x0e },
	{    6600000, 0xfa, 0x0d },
	{    6800000, 0xf9, 0x0c },
	{    7200000, 0xf9, 0x0b },
	{    7400000, 0xf9, 0x0a },
	{    7600000, 0xf8, 0x09 },
	{    7800000, 0xf8, 0x08 },
	{    8200000, 0xf8, 0x07 },
	{    8600000, 0xf7, 0x06 },
	{    8800000, 0xf7, 0x05 },
	{    9200000, 0xf7, 0x04 },
	{    9600000, 0xf6, 0x03 },
	{   10000000, 0xf6, 0x02 },
	{   10600000, 0xf5, 0x01 },
	{   11000000, 0xf5, 0x00 },
	{ 0xffffffff, 0x00, 0x20 },
};

stwuct e4000_if_gain {
	u8 weg16_vaw;
	u8 weg17_vaw;
};

static const stwuct e4000_if_gain e4000_if_gain_wut[] = {
	{0x00, 0x00},
	{0x20, 0x00},
	{0x40, 0x00},
	{0x02, 0x00},
	{0x22, 0x00},
	{0x42, 0x00},
	{0x04, 0x00},
	{0x24, 0x00},
	{0x44, 0x00},
	{0x01, 0x00},
	{0x21, 0x00},
	{0x41, 0x00},
	{0x03, 0x00},
	{0x23, 0x00},
	{0x43, 0x00},
	{0x05, 0x00},
	{0x25, 0x00},
	{0x45, 0x00},
	{0x07, 0x00},
	{0x27, 0x00},
	{0x47, 0x00},
	{0x0f, 0x00},
	{0x2f, 0x00},
	{0x4f, 0x00},
	{0x17, 0x00},
	{0x37, 0x00},
	{0x57, 0x00},
	{0x1f, 0x00},
	{0x3f, 0x00},
	{0x5f, 0x00},
	{0x1f, 0x01},
	{0x3f, 0x01},
	{0x5f, 0x01},
	{0x1f, 0x02},
	{0x3f, 0x02},
	{0x5f, 0x02},
	{0x1f, 0x03},
	{0x3f, 0x03},
	{0x5f, 0x03},
	{0x1f, 0x04},
	{0x3f, 0x04},
	{0x5f, 0x04},
	{0x1f, 0x0c},
	{0x3f, 0x0c},
	{0x5f, 0x0c},
	{0x1f, 0x14},
	{0x3f, 0x14},
	{0x5f, 0x14},
	{0x1f, 0x1c},
	{0x3f, 0x1c},
	{0x5f, 0x1c},
	{0x1f, 0x24},
	{0x3f, 0x24},
	{0x5f, 0x24},
	{0x7f, 0x24},
};

#endif
