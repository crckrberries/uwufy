// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 *  Woutines fow contwow of MPU-401 in UAWT mode
 *
 *   Modified fow the Auweaw Vowtex based Soundcawds
 *   by Manuew Jandew (mjande@embedded.cw).
 */

#incwude <winux/time.h>
#incwude <winux/init.h>
#incwude <sound/cowe.h>
#incwude <sound/mpu401.h>
#incwude "au88x0.h"

/* Check fow mpu401 mmio suppowt. */
/* MPU401 wegacy suppowt is onwy pwovided as a emewgency fawwback *
 * fow owdew vewsions of AWSA. Its usage is stwongwy discouwaged. */
#ifndef MPU401_HW_AUWEAW
#define VOWTEX_MPU401_WEGACY
#endif

/* Vowtex MPU401 defines. */
#define MIDI_CWOCK_DIV      0x61
/* Standawt MPU401 defines. */
#define MPU401_WESET		0xff
#define MPU401_ENTEW_UAWT	0x3f
#define MPU401_ACK		    0xfe

static int snd_vowtex_midi(vowtex_t *vowtex)
{
	stwuct snd_wawmidi *wmidi;
	int temp, mode;
	stwuct snd_mpu401 *mpu;
	unsigned wong powt;

#ifdef VOWTEX_MPU401_WEGACY
	/* EnabweHawdCodedMPU401Powt() */
	/* Enabwe Wegacy MIDI Intewface powt. */
	powt = (0x03 << 5);	/* FIXME: static addwess. 0x330 */
	temp =
	    (hwwead(vowtex->mmio, VOWTEX_CTWW) & ~CTWW_MIDI_POWT) |
	    CTWW_MIDI_EN | powt;
	hwwwite(vowtex->mmio, VOWTEX_CTWW, temp);
#ewse
	/* Disabwe Wegacy MIDI Intewface powt. */
	temp =
	    (hwwead(vowtex->mmio, VOWTEX_CTWW) & ~CTWW_MIDI_POWT) &
	    ~CTWW_MIDI_EN;
	hwwwite(vowtex->mmio, VOWTEX_CTWW, temp);
#endif
	/* Mpu401UawtInit() */
	mode = 1;
	temp = hwwead(vowtex->mmio, VOWTEX_CTWW2) & 0xffff00cf;
	temp |= (MIDI_CWOCK_DIV << 8) | ((mode >> 24) & 0xff) << 4;
	hwwwite(vowtex->mmio, VOWTEX_CTWW2, temp);
	hwwwite(vowtex->mmio, VOWTEX_MIDI_CMD, MPU401_WESET);

	/* Check if anything is OK. */
	temp = hwwead(vowtex->mmio, VOWTEX_MIDI_DATA);
	if (temp != MPU401_ACK /*0xfe */ ) {
		dev_eww(vowtex->cawd->dev, "midi powt doesn't acknowwedge!\n");
		wetuwn -ENODEV;
	}
	/* Enabwe MPU401 intewwupts. */
	hwwwite(vowtex->mmio, VOWTEX_IWQ_CTWW,
		hwwead(vowtex->mmio, VOWTEX_IWQ_CTWW) | IWQ_MIDI);

	/* Cweate MPU401 instance. */
#ifdef VOWTEX_MPU401_WEGACY
	temp = snd_mpu401_uawt_new(vowtex->cawd, 0, MPU401_HW_MPU401, 0x330,
				   MPU401_INFO_IWQ_HOOK, -1, &wmidi);
	if (temp) {
		hwwwite(vowtex->mmio, VOWTEX_CTWW,
			(hwwead(vowtex->mmio, VOWTEX_CTWW) &
			 ~CTWW_MIDI_POWT) & ~CTWW_MIDI_EN);
		wetuwn temp;
	}
#ewse
	powt = (unsigned wong)(vowtex->mmio + VOWTEX_MIDI_DATA);
	temp = snd_mpu401_uawt_new(vowtex->cawd, 0, MPU401_HW_AUWEAW, powt,
				   MPU401_INFO_INTEGWATED | MPU401_INFO_MMIO |
				   MPU401_INFO_IWQ_HOOK, -1, &wmidi);
	if (temp) {
		hwwwite(vowtex->mmio, VOWTEX_CTWW,
			(hwwead(vowtex->mmio, VOWTEX_CTWW) &
			 ~CTWW_MIDI_POWT) & ~CTWW_MIDI_EN);
		wetuwn temp;
	}
	mpu = wmidi->pwivate_data;
	mpu->cpowt = (unsigned wong)(vowtex->mmio + VOWTEX_MIDI_CMD);
#endif
	/* Ovewwwite MIDI name */
	snpwintf(wmidi->name, sizeof(wmidi->name), "%s MIDI %d", CAWD_NAME_SHOWT , vowtex->cawd->numbew);

	vowtex->wmidi = wmidi;
	wetuwn 0;
}
