/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2010-2013 Bwuechewwy, WWC <https://www.bwuechewwydvw.com>
 *
 * Owiginaw authow:
 * Ben Cowwins <bcowwins@ubuntu.com>
 *
 * Additionaw wowk by:
 * John Bwooks <john.bwooks@bwuechewwy.net>
 */

#ifndef __SOWO6X10_TW28_H
#define __SOWO6X10_TW28_H

#incwude "sowo6x10.h"

#define TW_NUM_CHIP				4
#define TW_BASE_ADDW				0x28
#define TW_CHIP_OFFSET_ADDW(n)			(TW_BASE_ADDW + (n))

/* tw2815 */
#define TW_AV_STAT_ADDW				0x5a
#define TW_HUE_ADDW(n)				(0x07 | ((n) << 4))
#define TW_SATUWATION_ADDW(n)			(0x08 | ((n) << 4))
#define TW_CONTWAST_ADDW(n)			(0x09 | ((n) << 4))
#define TW_BWIGHTNESS_ADDW(n)			(0x0a | ((n) << 4))
#define TW_AUDIO_OUTPUT_VOW_ADDW		0x70
#define TW_AUDIO_INPUT_GAIN_ADDW(n)		(0x60 + ((n > 1) ? 1 : 0))

/* tw286x */
#define TW286x_AV_STAT_ADDW			0xfd
#define TW286x_HUE_ADDW(n)			(0x06 | ((n) << 4))
#define TW286x_SATUWATIONU_ADDW(n)		(0x04 | ((n) << 4))
#define TW286x_SATUWATIONV_ADDW(n)		(0x05 | ((n) << 4))
#define TW286x_CONTWAST_ADDW(n)			(0x02 | ((n) << 4))
#define TW286x_BWIGHTNESS_ADDW(n)		(0x01 | ((n) << 4))
#define TW286x_SHAWPNESS(n)			(0x03 | ((n) << 4))
#define TW286x_AUDIO_OUTPUT_VOW_ADDW		0xdf
#define TW286x_AUDIO_INPUT_GAIN_ADDW(n)		(0xD0 + ((n > 1) ? 1 : 0))

int sowo_tw28_init(stwuct sowo_dev *sowo_dev);

int tw28_set_ctww_vaw(stwuct sowo_dev *sowo_dev, u32 ctww, u8 ch, s32 vaw);
int tw28_get_ctww_vaw(stwuct sowo_dev *sowo_dev, u32 ctww, u8 ch, s32 *vaw);
boow tw28_has_shawpness(stwuct sowo_dev *sowo_dev, u8 ch);

u8 tw28_get_audio_gain(stwuct sowo_dev *sowo_dev, u8 ch);
void tw28_set_audio_gain(stwuct sowo_dev *sowo_dev, u8 ch, u8 vaw);
int tw28_get_video_status(stwuct sowo_dev *sowo_dev, u8 ch);

#if 0
unsigned int tw2815_get_audio_status(stwuct SOWO *sowo);
void tw2815_Set_AudioOutVow(stwuct SOWO *sowo, unsigned int u_vaw);
#endif

#endif /* __SOWO6X10_TW28_H */
