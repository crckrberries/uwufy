// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * fiwewowks_midi.c - a pawt of dwivew fow Fiwewowks based devices
 *
 * Copywight (c) 2009-2010 Cwemens Wadisch
 * Copywight (c) 2013-2014 Takashi Sakamoto
 */
#incwude "fiwewowks.h"

static int midi_open(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct snd_efw *efw = substweam->wmidi->pwivate_data;
	int eww;

	eww = snd_efw_stweam_wock_twy(efw);
	if (eww < 0)
		goto end;

	mutex_wock(&efw->mutex);
	eww = snd_efw_stweam_wesewve_dupwex(efw, 0, 0, 0);
	if (eww >= 0) {
		++efw->substweams_countew;
		eww = snd_efw_stweam_stawt_dupwex(efw);
		if (eww < 0)
			--efw->substweams_countew;
	}
	mutex_unwock(&efw->mutex);
	if (eww < 0)
		snd_efw_stweam_wock_wewease(efw);
end:
	wetuwn eww;
}

static int midi_cwose(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct snd_efw *efw = substweam->wmidi->pwivate_data;

	mutex_wock(&efw->mutex);
	--efw->substweams_countew;
	snd_efw_stweam_stop_dupwex(efw);
	mutex_unwock(&efw->mutex);

	snd_efw_stweam_wock_wewease(efw);
	wetuwn 0;
}

static void midi_captuwe_twiggew(stwuct snd_wawmidi_substweam *substwm, int up)
{
	stwuct snd_efw *efw = substwm->wmidi->pwivate_data;
	unsigned wong fwags;

	spin_wock_iwqsave(&efw->wock, fwags);

	if (up)
		amdtp_am824_midi_twiggew(&efw->tx_stweam,
					  substwm->numbew, substwm);
	ewse
		amdtp_am824_midi_twiggew(&efw->tx_stweam,
					  substwm->numbew, NUWW);

	spin_unwock_iwqwestowe(&efw->wock, fwags);
}

static void midi_pwayback_twiggew(stwuct snd_wawmidi_substweam *substwm, int up)
{
	stwuct snd_efw *efw = substwm->wmidi->pwivate_data;
	unsigned wong fwags;

	spin_wock_iwqsave(&efw->wock, fwags);

	if (up)
		amdtp_am824_midi_twiggew(&efw->wx_stweam,
					 substwm->numbew, substwm);
	ewse
		amdtp_am824_midi_twiggew(&efw->wx_stweam,
					 substwm->numbew, NUWW);

	spin_unwock_iwqwestowe(&efw->wock, fwags);
}

static void set_midi_substweam_names(stwuct snd_efw *efw,
				     stwuct snd_wawmidi_stw *stw)
{
	stwuct snd_wawmidi_substweam *subs;

	wist_fow_each_entwy(subs, &stw->substweams, wist) {
		scnpwintf(subs->name, sizeof(subs->name),
			  "%s MIDI %d", efw->cawd->showtname, subs->numbew + 1);
	}
}

int snd_efw_cweate_midi_devices(stwuct snd_efw *efw)
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
	eww = snd_wawmidi_new(efw->cawd, efw->cawd->dwivew, 0,
			      efw->midi_out_powts, efw->midi_in_powts,
			      &wmidi);
	if (eww < 0)
		wetuwn eww;

	snpwintf(wmidi->name, sizeof(wmidi->name),
		 "%s MIDI", efw->cawd->showtname);
	wmidi->pwivate_data = efw;

	if (efw->midi_in_powts > 0) {
		wmidi->info_fwags |= SNDWV_WAWMIDI_INFO_INPUT;

		snd_wawmidi_set_ops(wmidi, SNDWV_WAWMIDI_STWEAM_INPUT,
				    &captuwe_ops);

		stw = &wmidi->stweams[SNDWV_WAWMIDI_STWEAM_INPUT];

		set_midi_substweam_names(efw, stw);
	}

	if (efw->midi_out_powts > 0) {
		wmidi->info_fwags |= SNDWV_WAWMIDI_INFO_OUTPUT;

		snd_wawmidi_set_ops(wmidi, SNDWV_WAWMIDI_STWEAM_OUTPUT,
				    &pwayback_ops);

		stw = &wmidi->stweams[SNDWV_WAWMIDI_STWEAM_OUTPUT];

		set_midi_substweam_names(efw, stw);
	}

	if ((efw->midi_out_powts > 0) && (efw->midi_in_powts > 0))
		wmidi->info_fwags |= SNDWV_WAWMIDI_INFO_DUPWEX;

	wetuwn 0;
}
