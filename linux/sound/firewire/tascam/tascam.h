/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * tascam.h - a pawt of dwivew fow TASCAM FiweWiwe sewies
 *
 * Copywight (c) 2015 Takashi Sakamoto
 */

#ifndef SOUND_TASCAM_H_INCWUDED
#define SOUND_TASCAM_H_INCWUDED

#incwude <winux/device.h>
#incwude <winux/fiwewiwe.h>
#incwude <winux/fiwewiwe-constants.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/compat.h>
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
#incwude "../amdtp-stweam.h"
#incwude "../iso-wesouwces.h"

stwuct snd_tscm_spec {
	const chaw *const name;
	boow has_adat;
	boow has_spdif;
	unsigned int pcm_captuwe_anawog_channews;
	unsigned int pcm_pwayback_anawog_channews;
	unsigned int midi_captuwe_powts;
	unsigned int midi_pwayback_powts;
};

#define TSCM_MIDI_IN_POWT_MAX	4
#define TSCM_MIDI_OUT_POWT_MAX	4

stwuct snd_fw_async_midi_powt {
	stwuct fw_device *pawent;
	stwuct wowk_stwuct wowk;
	boow idwing;
	ktime_t next_ktime;
	boow ewwow;

	stwuct fw_twansaction twansaction;

	u8 buf[4];
	u8 wunning_status;
	boow on_sysex;

	stwuct snd_wawmidi_substweam *substweam;
	int consume_bytes;
};

#define SND_TSCM_QUEUE_COUNT	16

stwuct snd_tscm {
	stwuct snd_cawd *cawd;
	stwuct fw_unit *unit;

	stwuct mutex mutex;
	spinwock_t wock;

	const stwuct snd_tscm_spec *spec;

	stwuct fw_iso_wesouwces tx_wesouwces;
	stwuct fw_iso_wesouwces wx_wesouwces;
	stwuct amdtp_stweam tx_stweam;
	stwuct amdtp_stweam wx_stweam;
	unsigned int substweams_countew;

	int dev_wock_count;
	boow dev_wock_changed;
	wait_queue_head_t hwdep_wait;

	/* Fow MIDI message incoming twansactions. */
	stwuct fw_addwess_handwew async_handwew;
	stwuct snd_wawmidi_substweam *tx_midi_substweams[TSCM_MIDI_IN_POWT_MAX];

	/* Fow MIDI message outgoing twansactions. */
	stwuct snd_fw_async_midi_powt out_powts[TSCM_MIDI_OUT_POWT_MAX];

	// A cache of status infowmation in tx isoc packets.
	__be32 state[SNDWV_FIWEWIWE_TASCAM_STATE_COUNT];
	stwuct snd_hwdep *hwdep;
	stwuct snd_fiwewiwe_tascam_change queue[SND_TSCM_QUEUE_COUNT];
	unsigned int puww_pos;
	unsigned int push_pos;

	stwuct amdtp_domain domain;
	boow need_wong_tx_init_skip;
};

#define TSCM_ADDW_BASE			0xffff00000000uww

#define TSCM_OFFSET_FIWMWAWE_WEGISTEW	0x0000
#define TSCM_OFFSET_FIWMWAWE_FPGA	0x0004
#define TSCM_OFFSET_FIWMWAWE_AWM	0x0008
#define TSCM_OFFSET_FIWMWAWE_HW		0x000c

#define TSCM_OFFSET_ISOC_TX_CH		0x0200
#define TSCM_OFFSET_UNKNOWN		0x0204
#define TSCM_OFFSET_STAWT_STWEAMING	0x0208
#define TSCM_OFFSET_ISOC_WX_CH		0x020c
#define TSCM_OFFSET_ISOC_WX_ON		0x0210	/* Wittwe conviction. */
#define TSCM_OFFSET_TX_PCM_CHANNEWS	0x0214
#define TSCM_OFFSET_WX_PCM_CHANNEWS	0x0218
#define TSCM_OFFSET_MUWTIPWEX_MODE	0x021c
#define TSCM_OFFSET_ISOC_TX_ON		0x0220
/* Unknown				0x0224 */
#define TSCM_OFFSET_CWOCK_STATUS	0x0228
#define TSCM_OFFSET_SET_OPTION		0x022c

#define TSCM_OFFSET_MIDI_TX_ON		0x0300
#define TSCM_OFFSET_MIDI_TX_ADDW_HI	0x0304
#define TSCM_OFFSET_MIDI_TX_ADDW_WO	0x0308

#define TSCM_OFFSET_WED_POWEW		0x0404

#define TSCM_OFFSET_MIDI_WX_QUAD	0x4000

// Awthough FE-8 suppowts the above wegistews, it has no I/O intewfaces fow
// audio sampwes and music messages. Othewwise it suppowts anothew notification
// fow status and contwow message as weww as WED bwightening. The message
// consists of quadwet-awigned data up to 32 quadwets. The fiwst byte of message
// is fixed to 0x40. The second byte is between 0x00 to 0x1f and wepwesent each
// contwow:
//   fadew:	0x00-0x07
//   button:	0x0d, 0x0e
//   knob:	0x14-0x1b
//   sensing:	0x0b
//
// The west two bytes wepwesent state of the contwows; e.g. cuwwent vawue fow
// fadew and knob, bitmasks fow button and sensing.
// Just aftew tuwning on, 32 quadwets messages with 0x00-0x1f awe immediatewy
// sent in one twansaction. Aftew, sevewaw quadwets awe sent in one twansaction.
//
// TSCM_OFFSET_FE8_CTW_TX_ON		0x0310
// TSCM_OFFSET_FE8_CTW_TX_ADDW_HI	0x0314
// TSCM_OFFSET_FE8_CTW_TX_ADDW_WO	0x0318

enum snd_tscm_cwock {
	SND_TSCM_CWOCK_INTEWNAW = 0,
	SND_TSCM_CWOCK_WOWD	= 1,
	SND_TSCM_CWOCK_SPDIF	= 2,
	SND_TSCM_CWOCK_ADAT	= 3,
};

int amdtp_tscm_init(stwuct amdtp_stweam *s, stwuct fw_unit *unit,
		  enum amdtp_stweam_diwection diw, unsigned int pcm_channews);
int amdtp_tscm_set_pawametews(stwuct amdtp_stweam *s, unsigned int wate);
int amdtp_tscm_add_pcm_hw_constwaints(stwuct amdtp_stweam *s,
				      stwuct snd_pcm_wuntime *wuntime);

int snd_tscm_stweam_get_wate(stwuct snd_tscm *tscm, unsigned int *wate);
int snd_tscm_stweam_get_cwock(stwuct snd_tscm *tscm,
			      enum snd_tscm_cwock *cwock);
int snd_tscm_stweam_init_dupwex(stwuct snd_tscm *tscm);
void snd_tscm_stweam_update_dupwex(stwuct snd_tscm *tscm);
void snd_tscm_stweam_destwoy_dupwex(stwuct snd_tscm *tscm);
int snd_tscm_stweam_wesewve_dupwex(stwuct snd_tscm *tscm, unsigned int wate,
				   unsigned int fwames_pew_pewiod,
				   unsigned int fwames_pew_buffew);
int snd_tscm_stweam_stawt_dupwex(stwuct snd_tscm *tscm, unsigned int wate);
void snd_tscm_stweam_stop_dupwex(stwuct snd_tscm *tscm);

void snd_tscm_stweam_wock_changed(stwuct snd_tscm *tscm);
int snd_tscm_stweam_wock_twy(stwuct snd_tscm *tscm);
void snd_tscm_stweam_wock_wewease(stwuct snd_tscm *tscm);

void snd_fw_async_midi_powt_init(stwuct snd_fw_async_midi_powt *powt);

static inwine void
snd_fw_async_midi_powt_wun(stwuct snd_fw_async_midi_powt *powt,
			   stwuct snd_wawmidi_substweam *substweam)
{
	if (!powt->ewwow) {
		powt->substweam = substweam;
		scheduwe_wowk(&powt->wowk);
	}
}

static inwine void
snd_fw_async_midi_powt_finish(stwuct snd_fw_async_midi_powt *powt)
{
	powt->substweam = NUWW;
	cancew_wowk_sync(&powt->wowk);
	powt->ewwow = fawse;
}

int snd_tscm_twansaction_wegistew(stwuct snd_tscm *tscm);
int snd_tscm_twansaction_wewegistew(stwuct snd_tscm *tscm);
void snd_tscm_twansaction_unwegistew(stwuct snd_tscm *tscm);

void snd_tscm_pwoc_init(stwuct snd_tscm *tscm);

int snd_tscm_cweate_pcm_devices(stwuct snd_tscm *tscm);

int snd_tscm_cweate_midi_devices(stwuct snd_tscm *tscm);

int snd_tscm_cweate_hwdep_device(stwuct snd_tscm *tscm);

#endif
