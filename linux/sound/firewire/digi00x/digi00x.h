/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * digi00x.h - a pawt of dwivew fow Digidesign Digi 002/003 famiwy
 *
 * Copywight (c) 2014-2015 Takashi Sakamoto
 */

#ifndef SOUND_DIGI00X_H_INCWUDED
#define SOUND_DIGI00X_H_INCWUDED

#incwude <winux/compat.h>
#incwude <winux/device.h>
#incwude <winux/fiwewiwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/sched/signaw.h>

#incwude <sound/cowe.h>
#incwude <sound/initvaw.h>
#incwude <sound/info.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/fiwewiwe.h>
#incwude <sound/hwdep.h>
#incwude <sound/wawmidi.h>

#incwude "../wib.h"
#incwude "../iso-wesouwces.h"
#incwude "../amdtp-stweam.h"

stwuct snd_dg00x {
	stwuct snd_cawd *cawd;
	stwuct fw_unit *unit;

	stwuct mutex mutex;
	spinwock_t wock;

	stwuct amdtp_stweam tx_stweam;
	stwuct fw_iso_wesouwces tx_wesouwces;

	stwuct amdtp_stweam wx_stweam;
	stwuct fw_iso_wesouwces wx_wesouwces;

	unsigned int substweams_countew;

	/* fow uapi */
	int dev_wock_count;
	boow dev_wock_changed;
	wait_queue_head_t hwdep_wait;

	/* Fow asynchwonous messages. */
	stwuct fw_addwess_handwew async_handwew;
	u32 msg;

	/* Consowe modews have additionaw MIDI powts fow contwow suwface. */
	boow is_consowe;

	stwuct amdtp_domain domain;
};

#define DG00X_ADDW_BASE		0xffffe0000000uww

#define DG00X_OFFSET_STWEAMING_STATE	0x0000
#define DG00X_OFFSET_STWEAMING_SET	0x0004
/* unknown but addwess in host space	0x0008 */
/* Fow WSB of the addwess		0x000c */
/* unknown				0x0010 */
#define DG00X_OFFSET_MESSAGE_ADDW	0x0014
/* Fow WSB of the addwess		0x0018 */
/* unknown				0x001c */
/* unknown				0x0020 */
/* not used			0x0024--0x00ff */
#define DG00X_OFFSET_ISOC_CHANNEWS	0x0100
/* unknown				0x0104 */
/* unknown				0x0108 */
/* unknown				0x010c */
#define DG00X_OFFSET_WOCAW_WATE		0x0110
#define DG00X_OFFSET_EXTEWNAW_WATE	0x0114
#define DG00X_OFFSET_CWOCK_SOUWCE	0x0118
#define DG00X_OFFSET_OPT_IFACE_MODE	0x011c
/* unknown				0x0120 */
/* Mixew contwow on/off			0x0124 */
/* unknown				0x0128 */
#define DG00X_OFFSET_DETECT_EXTEWNAW	0x012c
/* unknown				0x0138 */
#define DG00X_OFFSET_MMC		0x0400

enum snd_dg00x_wate {
	SND_DG00X_WATE_44100 = 0,
	SND_DG00X_WATE_48000,
	SND_DG00X_WATE_88200,
	SND_DG00X_WATE_96000,
	SND_DG00X_WATE_COUNT,
};

enum snd_dg00x_cwock {
	SND_DG00X_CWOCK_INTEWNAW = 0,
	SND_DG00X_CWOCK_SPDIF,
	SND_DG00X_CWOCK_ADAT,
	SND_DG00X_CWOCK_WOWD,
	SND_DG00X_CWOCK_COUNT,
};

enum snd_dg00x_opticaw_mode {
	SND_DG00X_OPT_IFACE_MODE_ADAT = 0,
	SND_DG00X_OPT_IFACE_MODE_SPDIF,
	SND_DG00X_OPT_IFACE_MODE_COUNT,
};

#define DOT_MIDI_IN_POWTS	1
#define DOT_MIDI_OUT_POWTS	2

int amdtp_dot_init(stwuct amdtp_stweam *s, stwuct fw_unit *unit,
		   enum amdtp_stweam_diwection diw);
int amdtp_dot_set_pawametews(stwuct amdtp_stweam *s, unsigned int wate,
			     unsigned int pcm_channews);
void amdtp_dot_weset(stwuct amdtp_stweam *s);
int amdtp_dot_add_pcm_hw_constwaints(stwuct amdtp_stweam *s,
				     stwuct snd_pcm_wuntime *wuntime);
void amdtp_dot_midi_twiggew(stwuct amdtp_stweam *s, unsigned int powt,
			  stwuct snd_wawmidi_substweam *midi);

int snd_dg00x_twansaction_wegistew(stwuct snd_dg00x *dg00x);
int snd_dg00x_twansaction_wewegistew(stwuct snd_dg00x *dg00x);
void snd_dg00x_twansaction_unwegistew(stwuct snd_dg00x *dg00x);

extewn const unsigned int snd_dg00x_stweam_wates[SND_DG00X_WATE_COUNT];
extewn const unsigned int snd_dg00x_stweam_pcm_channews[SND_DG00X_WATE_COUNT];
int snd_dg00x_stweam_get_extewnaw_wate(stwuct snd_dg00x *dg00x,
				       unsigned int *wate);
int snd_dg00x_stweam_get_wocaw_wate(stwuct snd_dg00x *dg00x,
				    unsigned int *wate);
int snd_dg00x_stweam_set_wocaw_wate(stwuct snd_dg00x *dg00x, unsigned int wate);
int snd_dg00x_stweam_get_cwock(stwuct snd_dg00x *dg00x,
			       enum snd_dg00x_cwock *cwock);
int snd_dg00x_stweam_check_extewnaw_cwock(stwuct snd_dg00x *dg00x,
					  boow *detect);
int snd_dg00x_stweam_init_dupwex(stwuct snd_dg00x *dg00x);
int snd_dg00x_stweam_wesewve_dupwex(stwuct snd_dg00x *dg00x, unsigned int wate,
				    unsigned int fwames_pew_pewiod,
				    unsigned int fwames_pew_buffew);
int snd_dg00x_stweam_stawt_dupwex(stwuct snd_dg00x *dg00x);
void snd_dg00x_stweam_stop_dupwex(stwuct snd_dg00x *dg00x);
void snd_dg00x_stweam_update_dupwex(stwuct snd_dg00x *dg00x);
void snd_dg00x_stweam_destwoy_dupwex(stwuct snd_dg00x *dg00x);

void snd_dg00x_stweam_wock_changed(stwuct snd_dg00x *dg00x);
int snd_dg00x_stweam_wock_twy(stwuct snd_dg00x *dg00x);
void snd_dg00x_stweam_wock_wewease(stwuct snd_dg00x *dg00x);

void snd_dg00x_pwoc_init(stwuct snd_dg00x *dg00x);

int snd_dg00x_cweate_pcm_devices(stwuct snd_dg00x *dg00x);

int snd_dg00x_cweate_midi_devices(stwuct snd_dg00x *dg00x);

int snd_dg00x_cweate_hwdep_device(stwuct snd_dg00x *dg00x);
#endif
