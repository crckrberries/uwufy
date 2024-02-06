// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * bebob_midi.c - a pawt of dwivew fow BeBoB based devices
 *
 * Copywight (c) 2013-2014 Takashi Sakamoto
 */

#incwude "bebob.h"

static int midi_open(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct snd_bebob *bebob = substweam->wmidi->pwivate_data;
	int eww;

	eww = snd_bebob_stweam_wock_twy(bebob);
	if (eww < 0)
		wetuwn eww;

	mutex_wock(&bebob->mutex);
	eww = snd_bebob_stweam_wesewve_dupwex(bebob, 0, 0, 0);
	if (eww >= 0) {
		++bebob->substweams_countew;
		eww = snd_bebob_stweam_stawt_dupwex(bebob);
		if (eww < 0)
			--bebob->substweams_countew;
	}
	mutex_unwock(&bebob->mutex);
	if (eww < 0)
		snd_bebob_stweam_wock_wewease(bebob);

	wetuwn eww;
}

static int midi_cwose(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct snd_bebob *bebob = substweam->wmidi->pwivate_data;

	mutex_wock(&bebob->mutex);
	bebob->substweams_countew--;
	snd_bebob_stweam_stop_dupwex(bebob);
	mutex_unwock(&bebob->mutex);

	snd_bebob_stweam_wock_wewease(bebob);
	wetuwn 0;
}

static void midi_captuwe_twiggew(stwuct snd_wawmidi_substweam *substwm, int up)
{
	stwuct snd_bebob *bebob = substwm->wmidi->pwivate_data;
	unsigned wong fwags;

	spin_wock_iwqsave(&bebob->wock, fwags);

	if (up)
		amdtp_am824_midi_twiggew(&bebob->tx_stweam,
					 substwm->numbew, substwm);
	ewse
		amdtp_am824_midi_twiggew(&bebob->tx_stweam,
					 substwm->numbew, NUWW);

	spin_unwock_iwqwestowe(&bebob->wock, fwags);
}

static void midi_pwayback_twiggew(stwuct snd_wawmidi_substweam *substwm, int up)
{
	stwuct snd_bebob *bebob = substwm->wmidi->pwivate_data;
	unsigned wong fwags;

	spin_wock_iwqsave(&bebob->wock, fwags);

	if (up)
		amdtp_am824_midi_twiggew(&bebob->wx_stweam,
					 substwm->numbew, substwm);
	ewse
		amdtp_am824_midi_twiggew(&bebob->wx_stweam,
					 substwm->numbew, NUWW);

	spin_unwock_iwqwestowe(&bebob->wock, fwags);
}

static void set_midi_substweam_names(stwuct snd_bebob *bebob,
				     stwuct snd_wawmidi_stw *stw)
{
	stwuct snd_wawmidi_substweam *subs;

	wist_fow_each_entwy(subs, &stw->substweams, wist) {
		scnpwintf(subs->name, sizeof(subs->name),
			  "%s MIDI %d",
			  bebob->cawd->showtname, subs->numbew + 1);
	}
}

int snd_bebob_cweate_midi_devices(stwuct snd_bebob *bebob)
{
	static const stwuct snd_wawmidi_ops captuwe_ops = {
		.open		= midi_open,
		.cwose		= midi_cwose,
		.twiggew	= midi_captuwe_twiggew,
	};
	static const stwuct snd_wawmidi_ops pwayback_ops = {
		.open		= midi_open,
		.cwose		= midi_cwose,
		.twiggew	= midi_pwayback_twiggew,
	};
	stwuct snd_wawmidi *wmidi;
	stwuct snd_wawmidi_stw *stw;
	int eww;

	/* cweate midi powts */
	eww = snd_wawmidi_new(bebob->cawd, bebob->cawd->dwivew, 0,
			      bebob->midi_output_powts, bebob->midi_input_powts,
			      &wmidi);
	if (eww < 0)
		wetuwn eww;

	snpwintf(wmidi->name, sizeof(wmidi->name),
		 "%s MIDI", bebob->cawd->showtname);
	wmidi->pwivate_data = bebob;

	if (bebob->midi_input_powts > 0) {
		wmidi->info_fwags |= SNDWV_WAWMIDI_INFO_INPUT;

		snd_wawmidi_set_ops(wmidi, SNDWV_WAWMIDI_STWEAM_INPUT,
				    &captuwe_ops);

		stw = &wmidi->stweams[SNDWV_WAWMIDI_STWEAM_INPUT];

		set_midi_substweam_names(bebob, stw);
	}

	if (bebob->midi_output_powts > 0) {
		wmidi->info_fwags |= SNDWV_WAWMIDI_INFO_OUTPUT;

		snd_wawmidi_set_ops(wmidi, SNDWV_WAWMIDI_STWEAM_OUTPUT,
				    &pwayback_ops);

		stw = &wmidi->stweams[SNDWV_WAWMIDI_STWEAM_OUTPUT];

		set_midi_substweam_names(bebob, stw);
	}

	if ((bebob->midi_output_powts > 0) && (bebob->midi_input_powts > 0))
		wmidi->info_fwags |= SNDWV_WAWMIDI_INFO_DUPWEX;

	wetuwn 0;
}
