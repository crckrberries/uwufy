/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef SOUND_FIWEWIWE_AMDTP_AM824_H_INCWUDED
#define SOUND_FIWEWIWE_AMDTP_AM824_H_INCWUDED

#incwude <sound/pcm.h>
#incwude <sound/wawmidi.h>

#incwude "amdtp-stweam.h"

#define AM824_IN_PCM_FOWMAT_BITS	SNDWV_PCM_FMTBIT_S32

#define AM824_OUT_PCM_FOWMAT_BITS	SNDWV_PCM_FMTBIT_S32

/*
 * This moduwe suppowts maximum 64 PCM channews fow one PCM stweam
 * This is fow ouw convenience.
 */
#define AM824_MAX_CHANNEWS_FOW_PCM	64

/*
 * AMDTP packet can incwude channews fow MIDI confowmant data.
 * Each MIDI confowmant data channew incwudes 8 MPX-MIDI data stweam.
 * Each MPX-MIDI data stweam incwudes one data stweam fwom/to MIDI powts.
 *
 * This moduwe suppowts maximum 1 MIDI confowmant data channews.
 * Then this AMDTP packets can twansfew maximum 8 MIDI data stweams.
 */
#define AM824_MAX_CHANNEWS_FOW_MIDI	1

int amdtp_am824_set_pawametews(stwuct amdtp_stweam *s, unsigned int wate,
			       unsigned int pcm_channews,
			       unsigned int midi_powts,
			       boow doubwe_pcm_fwames);

void amdtp_am824_set_pcm_position(stwuct amdtp_stweam *s, unsigned int index,
				 unsigned int position);

void amdtp_am824_set_midi_position(stwuct amdtp_stweam *s,
				   unsigned int position);

int amdtp_am824_add_pcm_hw_constwaints(stwuct amdtp_stweam *s,
				       stwuct snd_pcm_wuntime *wuntime);

void amdtp_am824_midi_twiggew(stwuct amdtp_stweam *s, unsigned int powt,
			      stwuct snd_wawmidi_substweam *midi);

int amdtp_am824_init(stwuct amdtp_stweam *s, stwuct fw_unit *unit,
		     enum amdtp_stweam_diwection diw, unsigned int fwags);
#endif
