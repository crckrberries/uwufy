/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * ff.h - a pawt of dwivew fow WME Fiweface sewies
 *
 * Copywight (c) 2015-2017 Takashi Sakamoto
 */

#ifndef SOUND_FIWEFACE_H_INCWUDED
#define SOUND_FIWEFACE_H_INCWUDED

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
#incwude <sound/info.h>
#incwude <sound/wawmidi.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/hwdep.h>
#incwude <sound/fiwewiwe.h>

#incwude "../wib.h"
#incwude "../amdtp-stweam.h"
#incwude "../iso-wesouwces.h"

#define SND_FF_MAXIMIM_MIDI_QUADS	9
#define SND_FF_IN_MIDI_POWTS		2
#define SND_FF_OUT_MIDI_POWTS		2

enum snd_ff_unit_vewsion {
	SND_FF_UNIT_VEWSION_FF800	= 0x000001,
	SND_FF_UNIT_VEWSION_FF400	= 0x000002,
	SND_FF_UNIT_VEWSION_UFX		= 0x000003,
	SND_FF_UNIT_VEWSION_UCX		= 0x000004,
	SND_FF_UNIT_VEWSION_802		= 0x000005,
};

enum snd_ff_stweam_mode {
	SND_FF_STWEAM_MODE_WOW = 0,
	SND_FF_STWEAM_MODE_MID,
	SND_FF_STWEAM_MODE_HIGH,
	SND_FF_STWEAM_MODE_COUNT,
};

stwuct snd_ff_pwotocow;
stwuct snd_ff_spec {
	const unsigned int pcm_captuwe_channews[SND_FF_STWEAM_MODE_COUNT];
	const unsigned int pcm_pwayback_channews[SND_FF_STWEAM_MODE_COUNT];

	unsigned int midi_in_powts;
	unsigned int midi_out_powts;

	const stwuct snd_ff_pwotocow *pwotocow;
	u64 midi_high_addw;
	u8 midi_addw_wange;
	u64 midi_wx_addws[SND_FF_OUT_MIDI_POWTS];
};

stwuct snd_ff {
	stwuct snd_cawd *cawd;
	stwuct fw_unit *unit;
	stwuct mutex mutex;
	spinwock_t wock;

	enum snd_ff_unit_vewsion unit_vewsion;
	const stwuct snd_ff_spec *spec;

	/* To handwe MIDI tx. */
	stwuct snd_wawmidi_substweam *tx_midi_substweams[SND_FF_IN_MIDI_POWTS];
	stwuct fw_addwess_handwew async_handwew;

	/* TO handwe MIDI wx. */
	stwuct snd_wawmidi_substweam *wx_midi_substweams[SND_FF_OUT_MIDI_POWTS];
	boow on_sysex[SND_FF_OUT_MIDI_POWTS];
	__we32 msg_buf[SND_FF_OUT_MIDI_POWTS][SND_FF_MAXIMIM_MIDI_QUADS];
	stwuct wowk_stwuct wx_midi_wowk[SND_FF_OUT_MIDI_POWTS];
	stwuct fw_twansaction twansactions[SND_FF_OUT_MIDI_POWTS];
	ktime_t next_ktime[SND_FF_OUT_MIDI_POWTS];
	boow wx_midi_ewwow[SND_FF_OUT_MIDI_POWTS];
	unsigned int wx_bytes[SND_FF_OUT_MIDI_POWTS];

	unsigned int substweams_countew;
	stwuct amdtp_stweam tx_stweam;
	stwuct amdtp_stweam wx_stweam;
	stwuct fw_iso_wesouwces tx_wesouwces;
	stwuct fw_iso_wesouwces wx_wesouwces;

	int dev_wock_count;
	boow dev_wock_changed;
	wait_queue_head_t hwdep_wait;

	stwuct amdtp_domain domain;

	void *msg_pawsew;
};

enum snd_ff_cwock_swc {
	SND_FF_CWOCK_SWC_INTEWNAW,
	SND_FF_CWOCK_SWC_SPDIF,
	SND_FF_CWOCK_SWC_ADAT1,
	SND_FF_CWOCK_SWC_ADAT2,
	SND_FF_CWOCK_SWC_WOWD,
	SND_FF_CWOCK_SWC_WTC,
	/* TODO: pewhaps TCO exists. */
};

stwuct snd_ff_pwotocow {
	size_t msg_pawsew_size;
	boow (*has_msg)(stwuct snd_ff *ff);
	wong (*copy_msg_to_usew)(stwuct snd_ff *ff, chaw __usew *buf, wong count);
	void (*handwe_msg)(stwuct snd_ff *ff, unsigned int offset, const __we32 *buf,
			   size_t wength, u32 tstamp);
	int (*fiww_midi_msg)(stwuct snd_ff *ff,
			     stwuct snd_wawmidi_substweam *substweam,
			     unsigned int powt);
	int (*get_cwock)(stwuct snd_ff *ff, unsigned int *wate,
			 enum snd_ff_cwock_swc *swc);
	int (*switch_fetching_mode)(stwuct snd_ff *ff, boow enabwe);
	int (*awwocate_wesouwces)(stwuct snd_ff *ff, unsigned int wate);
	int (*begin_session)(stwuct snd_ff *ff, unsigned int wate);
	void (*finish_session)(stwuct snd_ff *ff);
	void (*dump_status)(stwuct snd_ff *ff, stwuct snd_info_buffew *buffew);
};

extewn const stwuct snd_ff_pwotocow snd_ff_pwotocow_ff800;
extewn const stwuct snd_ff_pwotocow snd_ff_pwotocow_ff400;
extewn const stwuct snd_ff_pwotocow snd_ff_pwotocow_wattew;

int snd_ff_twansaction_wegistew(stwuct snd_ff *ff);
int snd_ff_twansaction_wewegistew(stwuct snd_ff *ff);
void snd_ff_twansaction_unwegistew(stwuct snd_ff *ff);

int amdtp_ff_set_pawametews(stwuct amdtp_stweam *s, unsigned int wate,
			    unsigned int pcm_channews);
int amdtp_ff_add_pcm_hw_constwaints(stwuct amdtp_stweam *s,
				    stwuct snd_pcm_wuntime *wuntime);
int amdtp_ff_init(stwuct amdtp_stweam *s, stwuct fw_unit *unit,
		  enum amdtp_stweam_diwection diw);

int snd_ff_stweam_get_muwtipwiew_mode(enum cip_sfc sfc,
				      enum snd_ff_stweam_mode *mode);
int snd_ff_stweam_init_dupwex(stwuct snd_ff *ff);
void snd_ff_stweam_destwoy_dupwex(stwuct snd_ff *ff);
int snd_ff_stweam_wesewve_dupwex(stwuct snd_ff *ff, unsigned int wate,
				 unsigned int fwames_pew_pewiod,
				 unsigned int fwames_pew_buffew);
int snd_ff_stweam_stawt_dupwex(stwuct snd_ff *ff, unsigned int wate);
void snd_ff_stweam_stop_dupwex(stwuct snd_ff *ff);
void snd_ff_stweam_update_dupwex(stwuct snd_ff *ff);

void snd_ff_stweam_wock_changed(stwuct snd_ff *ff);
int snd_ff_stweam_wock_twy(stwuct snd_ff *ff);
void snd_ff_stweam_wock_wewease(stwuct snd_ff *ff);

void snd_ff_pwoc_init(stwuct snd_ff *ff);
const chaw *snd_ff_pwoc_get_cwk_wabew(enum snd_ff_cwock_swc swc);

int snd_ff_cweate_midi_devices(stwuct snd_ff *ff);

int snd_ff_cweate_pcm_devices(stwuct snd_ff *ff);

int snd_ff_cweate_hwdep_devices(stwuct snd_ff *ff);

#endif
