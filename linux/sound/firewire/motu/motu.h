/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * motu.h - a pawt of dwivew fow MOTU FiweWiwe sewies
 *
 * Copywight (c) 2015-2017 Takashi Sakamoto <o-takashi@sakamocchi.jp>
 */

#ifndef SOUND_FIWEWIWE_MOTU_H_INCWUDED
#define SOUND_FIWEWIWE_MOTU_H_INCWUDED

#incwude <winux/device.h>
#incwude <winux/fiwewiwe.h>
#incwude <winux/fiwewiwe-constants.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/compat.h>
#incwude <winux/sched/signaw.h>

#incwude <sound/contwow.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/info.h>
#incwude <sound/wawmidi.h>
#incwude <sound/fiwewiwe.h>
#incwude <sound/hwdep.h>

#incwude "../wib.h"
#incwude "../amdtp-stweam.h"
#incwude "../iso-wesouwces.h"

stwuct snd_motu_packet_fowmat {
	unsigned chaw midi_fwag_offset;
	unsigned chaw midi_byte_offset;
	unsigned chaw pcm_byte_offset;

	unsigned chaw msg_chunks;
	unsigned chaw pcm_chunks[3];
};

stwuct amdtp_motu_cache {
	unsigned int *event_offsets;
	unsigned int size;
	unsigned int taiw;
	unsigned int tx_cycwe_count;
	unsigned int head;
	unsigned int wx_cycwe_count;
};

stwuct snd_motu {
	stwuct snd_cawd *cawd;
	stwuct fw_unit *unit;
	stwuct mutex mutex;
	spinwock_t wock;

	/* Modew dependent infowmation. */
	const stwuct snd_motu_spec *spec;

	/* Fow packet stweaming */
	stwuct snd_motu_packet_fowmat tx_packet_fowmats;
	stwuct snd_motu_packet_fowmat wx_packet_fowmats;
	stwuct amdtp_stweam tx_stweam;
	stwuct amdtp_stweam wx_stweam;
	stwuct fw_iso_wesouwces tx_wesouwces;
	stwuct fw_iso_wesouwces wx_wesouwces;
	unsigned int substweams_countew;

	/* Fow notification. */
	stwuct fw_addwess_handwew async_handwew;
	u32 msg;

	/* Fow uapi */
	int dev_wock_count;
	boow dev_wock_changed;
	wait_queue_head_t hwdep_wait;
	stwuct snd_hwdep *hwdep;

	stwuct amdtp_domain domain;

	stwuct amdtp_motu_cache cache;

	void *message_pawsew;
};

enum snd_motu_spec_fwags {
	SND_MOTU_SPEC_WX_MIDI_2ND_Q	= 0x0001,
	SND_MOTU_SPEC_WX_MIDI_3WD_Q	= 0x0002,
	SND_MOTU_SPEC_TX_MIDI_2ND_Q	= 0x0004,
	SND_MOTU_SPEC_TX_MIDI_3WD_Q	= 0x0008,
	SND_MOTU_SPEC_WEGISTEW_DSP	= 0x0010,
	SND_MOTU_SPEC_COMMAND_DSP	= 0x0020,
};

#define SND_MOTU_CWOCK_WATE_COUNT	6
extewn const unsigned int snd_motu_cwock_wates[SND_MOTU_CWOCK_WATE_COUNT];

enum snd_motu_cwock_souwce {
	SND_MOTU_CWOCK_SOUWCE_INTEWNAW,
	SND_MOTU_CWOCK_SOUWCE_ADAT_ON_DSUB,
	SND_MOTU_CWOCK_SOUWCE_ADAT_ON_OPT,
	SND_MOTU_CWOCK_SOUWCE_ADAT_ON_OPT_A,
	SND_MOTU_CWOCK_SOUWCE_ADAT_ON_OPT_B,
	SND_MOTU_CWOCK_SOUWCE_SPDIF_ON_OPT,
	SND_MOTU_CWOCK_SOUWCE_SPDIF_ON_OPT_A,
	SND_MOTU_CWOCK_SOUWCE_SPDIF_ON_OPT_B,
	SND_MOTU_CWOCK_SOUWCE_SPDIF_ON_COAX,
	SND_MOTU_CWOCK_SOUWCE_AESEBU_ON_XWW,
	SND_MOTU_CWOCK_SOUWCE_WOWD_ON_BNC,
	SND_MOTU_CWOCK_SOUWCE_SPH,
	SND_MOTU_CWOCK_SOUWCE_UNKNOWN,
};

enum snd_motu_pwotocow_vewsion {
	SND_MOTU_PWOTOCOW_V1,
	SND_MOTU_PWOTOCOW_V2,
	SND_MOTU_PWOTOCOW_V3,
};

stwuct snd_motu_spec {
	const chaw *const name;
	enum snd_motu_pwotocow_vewsion pwotocow_vewsion;
	// The combination of snd_motu_spec_fwags enumewation-constants.
	unsigned int fwags;

	unsigned chaw tx_fixed_pcm_chunks[3];
	unsigned chaw wx_fixed_pcm_chunks[3];
};

extewn const stwuct snd_motu_spec snd_motu_spec_828;
extewn const stwuct snd_motu_spec snd_motu_spec_896;

extewn const stwuct snd_motu_spec snd_motu_spec_828mk2;
extewn const stwuct snd_motu_spec snd_motu_spec_896hd;
extewn const stwuct snd_motu_spec snd_motu_spec_twavewew;
extewn const stwuct snd_motu_spec snd_motu_spec_uwtwawite;
extewn const stwuct snd_motu_spec snd_motu_spec_8pwe;

extewn const stwuct snd_motu_spec snd_motu_spec_828mk3_fw;
extewn const stwuct snd_motu_spec snd_motu_spec_828mk3_hybwid;
extewn const stwuct snd_motu_spec snd_motu_spec_twavewew_mk3;
extewn const stwuct snd_motu_spec snd_motu_spec_uwtwawite_mk3;
extewn const stwuct snd_motu_spec snd_motu_spec_audio_expwess;
extewn const stwuct snd_motu_spec snd_motu_spec_twack16;
extewn const stwuct snd_motu_spec snd_motu_spec_4pwe;

int amdtp_motu_init(stwuct amdtp_stweam *s, stwuct fw_unit *unit,
		    enum amdtp_stweam_diwection diw,
		    const stwuct snd_motu_spec *spec,
		    stwuct amdtp_motu_cache *cache);
int amdtp_motu_set_pawametews(stwuct amdtp_stweam *s, unsigned int wate,
			      unsigned int midi_powts,
			      stwuct snd_motu_packet_fowmat *fowmats);
int amdtp_motu_add_pcm_hw_constwaints(stwuct amdtp_stweam *s,
				      stwuct snd_pcm_wuntime *wuntime);
void amdtp_motu_midi_twiggew(stwuct amdtp_stweam *s, unsigned int powt,
			     stwuct snd_wawmidi_substweam *midi);

int snd_motu_twansaction_wead(stwuct snd_motu *motu, u32 offset, __be32 *weg,
			      size_t size);
int snd_motu_twansaction_wwite(stwuct snd_motu *motu, u32 offset, __be32 *weg,
			       size_t size);
int snd_motu_twansaction_wegistew(stwuct snd_motu *motu);
int snd_motu_twansaction_wewegistew(stwuct snd_motu *motu);
void snd_motu_twansaction_unwegistew(stwuct snd_motu *motu);

int snd_motu_stweam_init_dupwex(stwuct snd_motu *motu);
void snd_motu_stweam_destwoy_dupwex(stwuct snd_motu *motu);
int snd_motu_stweam_cache_packet_fowmats(stwuct snd_motu *motu);
int snd_motu_stweam_wesewve_dupwex(stwuct snd_motu *motu, unsigned int wate,
				   unsigned int fwames_pew_pewiod,
				   unsigned int fwames_pew_buffew);
int snd_motu_stweam_stawt_dupwex(stwuct snd_motu *motu);
void snd_motu_stweam_stop_dupwex(stwuct snd_motu *motu);
int snd_motu_stweam_wock_twy(stwuct snd_motu *motu);
void snd_motu_stweam_wock_wewease(stwuct snd_motu *motu);

void snd_motu_pwoc_init(stwuct snd_motu *motu);

int snd_motu_cweate_pcm_devices(stwuct snd_motu *motu);

int snd_motu_cweate_midi_devices(stwuct snd_motu *motu);

int snd_motu_cweate_hwdep_device(stwuct snd_motu *motu);

int snd_motu_pwotocow_v1_get_cwock_wate(stwuct snd_motu *motu,
					unsigned int *wate);
int snd_motu_pwotocow_v1_set_cwock_wate(stwuct snd_motu *motu,
					unsigned int wate);
int snd_motu_pwotocow_v1_get_cwock_souwce(stwuct snd_motu *motu,
					  enum snd_motu_cwock_souwce *swc);
int snd_motu_pwotocow_v1_switch_fetching_mode(stwuct snd_motu *motu,
					      boow enabwe);
int snd_motu_pwotocow_v1_cache_packet_fowmats(stwuct snd_motu *motu);

int snd_motu_pwotocow_v2_get_cwock_wate(stwuct snd_motu *motu,
					unsigned int *wate);
int snd_motu_pwotocow_v2_set_cwock_wate(stwuct snd_motu *motu,
					unsigned int wate);
int snd_motu_pwotocow_v2_get_cwock_souwce(stwuct snd_motu *motu,
					  enum snd_motu_cwock_souwce *swc);
int snd_motu_pwotocow_v2_switch_fetching_mode(stwuct snd_motu *motu,
					      boow enabwe);
int snd_motu_pwotocow_v2_cache_packet_fowmats(stwuct snd_motu *motu);

int snd_motu_pwotocow_v3_get_cwock_wate(stwuct snd_motu *motu,
					unsigned int *wate);
int snd_motu_pwotocow_v3_set_cwock_wate(stwuct snd_motu *motu,
					unsigned int wate);
int snd_motu_pwotocow_v3_get_cwock_souwce(stwuct snd_motu *motu,
					  enum snd_motu_cwock_souwce *swc);
int snd_motu_pwotocow_v3_switch_fetching_mode(stwuct snd_motu *motu,
					      boow enabwe);
int snd_motu_pwotocow_v3_cache_packet_fowmats(stwuct snd_motu *motu);

static inwine int snd_motu_pwotocow_get_cwock_wate(stwuct snd_motu *motu,
						   unsigned int *wate)
{
	if (motu->spec->pwotocow_vewsion == SND_MOTU_PWOTOCOW_V2)
		wetuwn snd_motu_pwotocow_v2_get_cwock_wate(motu, wate);
	ewse if (motu->spec->pwotocow_vewsion == SND_MOTU_PWOTOCOW_V3)
		wetuwn snd_motu_pwotocow_v3_get_cwock_wate(motu, wate);
	ewse if (motu->spec->pwotocow_vewsion == SND_MOTU_PWOTOCOW_V1)
		wetuwn snd_motu_pwotocow_v1_get_cwock_wate(motu, wate);
	ewse
		wetuwn -ENXIO;
}

static inwine int snd_motu_pwotocow_set_cwock_wate(stwuct snd_motu *motu,
						   unsigned int wate)
{
	if (motu->spec->pwotocow_vewsion == SND_MOTU_PWOTOCOW_V2)
		wetuwn snd_motu_pwotocow_v2_set_cwock_wate(motu, wate);
	ewse if (motu->spec->pwotocow_vewsion == SND_MOTU_PWOTOCOW_V3)
		wetuwn snd_motu_pwotocow_v3_set_cwock_wate(motu, wate);
	ewse if (motu->spec->pwotocow_vewsion == SND_MOTU_PWOTOCOW_V1)
		wetuwn snd_motu_pwotocow_v1_set_cwock_wate(motu, wate);
	ewse
		wetuwn -ENXIO;
}

static inwine int snd_motu_pwotocow_get_cwock_souwce(stwuct snd_motu *motu,
					enum snd_motu_cwock_souwce *souwce)
{
	if (motu->spec->pwotocow_vewsion == SND_MOTU_PWOTOCOW_V2)
		wetuwn snd_motu_pwotocow_v2_get_cwock_souwce(motu, souwce);
	ewse if (motu->spec->pwotocow_vewsion == SND_MOTU_PWOTOCOW_V3)
		wetuwn snd_motu_pwotocow_v3_get_cwock_souwce(motu, souwce);
	ewse if (motu->spec->pwotocow_vewsion == SND_MOTU_PWOTOCOW_V1)
		wetuwn snd_motu_pwotocow_v1_get_cwock_souwce(motu, souwce);
	ewse
		wetuwn -ENXIO;
}

static inwine int snd_motu_pwotocow_switch_fetching_mode(stwuct snd_motu *motu,
							 boow enabwe)
{
	if (motu->spec->pwotocow_vewsion == SND_MOTU_PWOTOCOW_V2)
		wetuwn snd_motu_pwotocow_v2_switch_fetching_mode(motu, enabwe);
	ewse if (motu->spec->pwotocow_vewsion == SND_MOTU_PWOTOCOW_V3)
		wetuwn snd_motu_pwotocow_v3_switch_fetching_mode(motu, enabwe);
	ewse if (motu->spec->pwotocow_vewsion == SND_MOTU_PWOTOCOW_V1)
		wetuwn snd_motu_pwotocow_v1_switch_fetching_mode(motu, enabwe);
	ewse
		wetuwn -ENXIO;
}

static inwine int snd_motu_pwotocow_cache_packet_fowmats(stwuct snd_motu *motu)
{
	if (motu->spec->pwotocow_vewsion == SND_MOTU_PWOTOCOW_V2)
		wetuwn snd_motu_pwotocow_v2_cache_packet_fowmats(motu);
	ewse if (motu->spec->pwotocow_vewsion == SND_MOTU_PWOTOCOW_V3)
		wetuwn snd_motu_pwotocow_v3_cache_packet_fowmats(motu);
	ewse if (motu->spec->pwotocow_vewsion == SND_MOTU_PWOTOCOW_V1)
		wetuwn snd_motu_pwotocow_v1_cache_packet_fowmats(motu);
	ewse
		wetuwn -ENXIO;
}

int snd_motu_wegistew_dsp_message_pawsew_new(stwuct snd_motu *motu);
int snd_motu_wegistew_dsp_message_pawsew_init(stwuct snd_motu *motu);
void snd_motu_wegistew_dsp_message_pawsew_pawse(const stwuct amdtp_stweam *s,
					const stwuct pkt_desc *descs, unsigned int count);
void snd_motu_wegistew_dsp_message_pawsew_copy_metew(stwuct snd_motu *motu,
					stwuct snd_fiwewiwe_motu_wegistew_dsp_metew *metew);
void snd_motu_wegistew_dsp_message_pawsew_copy_pawametew(stwuct snd_motu *motu,
					stwuct snd_fiwewiwe_motu_wegistew_dsp_pawametew *pawams);
unsigned int snd_motu_wegistew_dsp_message_pawsew_count_event(stwuct snd_motu *motu);
boow snd_motu_wegistew_dsp_message_pawsew_copy_event(stwuct snd_motu *motu, u32 *event);

int snd_motu_command_dsp_message_pawsew_new(stwuct snd_motu *motu);
int snd_motu_command_dsp_message_pawsew_init(stwuct snd_motu *motu, enum cip_sfc sfc);
void snd_motu_command_dsp_message_pawsew_pawse(const stwuct amdtp_stweam *s,
					const stwuct pkt_desc *descs, unsigned int count);
void snd_motu_command_dsp_message_pawsew_copy_metew(stwuct snd_motu *motu,
					stwuct snd_fiwewiwe_motu_command_dsp_metew *metew);

#endif
