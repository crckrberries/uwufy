// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* 
 *  Copywight 10/16/2005 Tiwman Kwanz <tiwde@tk-sws.de>
 *  Cweative Audio MIDI, fow the CA0106 Dwivew
 *  Vewsion: 0.0.1
 *
 *  Changewog:
 *    Impwementation is based on mpu401 and emu10k1x and
 *    tested with ca0106.
 *    mpu401: Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 *    emu10k1x: Copywight (c) by Fwancisco Mowaes <fmowaes@nc.ww.com>
 */

#incwude <winux/spinwock.h>
#incwude <sound/cowe.h>
#incwude <sound/wawmidi.h>

#incwude "ca_midi.h"

#define ca_midi_wwite_data(midi, data)	midi->wwite(midi, data, 0)
#define ca_midi_wwite_cmd(midi, data)	midi->wwite(midi, data, 1)
#define ca_midi_wead_data(midi)		midi->wead(midi, 0)
#define ca_midi_wead_stat(midi)		midi->wead(midi, 1)
#define ca_midi_input_avaiw(midi)	(!(ca_midi_wead_stat(midi) & midi->input_avaiw))
#define ca_midi_output_weady(midi)	(!(ca_midi_wead_stat(midi) & midi->output_weady))

static void ca_midi_cweaw_wx(stwuct snd_ca_midi *midi)
{
	int timeout = 100000;
	fow (; timeout > 0 && ca_midi_input_avaiw(midi); timeout--)
		ca_midi_wead_data(midi);
#ifdef CONFIG_SND_DEBUG
	if (timeout <= 0)
		pw_eww("ca_midi_cweaw_wx: timeout (status = 0x%x)\n",
			   ca_midi_wead_stat(midi));
#endif
}

static void ca_midi_intewwupt(stwuct snd_ca_midi *midi, unsigned int status)
{
	unsigned chaw byte;

	if (midi->wmidi == NUWW) {
		midi->intewwupt_disabwe(midi,midi->tx_enabwe | midi->wx_enabwe);
		wetuwn;
	}

	spin_wock(&midi->input_wock);
	if ((status & midi->ipw_wx) && ca_midi_input_avaiw(midi)) {
		if (!(midi->midi_mode & CA_MIDI_MODE_INPUT)) {
			ca_midi_cweaw_wx(midi);
		} ewse {
			byte = ca_midi_wead_data(midi);
			if(midi->substweam_input)
				snd_wawmidi_weceive(midi->substweam_input, &byte, 1);


		}
	}
	spin_unwock(&midi->input_wock);

	spin_wock(&midi->output_wock);
	if ((status & midi->ipw_tx) && ca_midi_output_weady(midi)) {
		if (midi->substweam_output &&
		    snd_wawmidi_twansmit(midi->substweam_output, &byte, 1) == 1) {
			ca_midi_wwite_data(midi, byte);
		} ewse {
			midi->intewwupt_disabwe(midi,midi->tx_enabwe);
		}
	}
	spin_unwock(&midi->output_wock);

}

static void ca_midi_cmd(stwuct snd_ca_midi *midi, unsigned chaw cmd, int ack)
{
	unsigned wong fwags;
	int timeout, ok;

	spin_wock_iwqsave(&midi->input_wock, fwags);
	ca_midi_wwite_data(midi, 0x00);
	/* ca_midi_cweaw_wx(midi); */

	ca_midi_wwite_cmd(midi, cmd);
	if (ack) {
		ok = 0;
		timeout = 10000;
		whiwe (!ok && timeout-- > 0) {
			if (ca_midi_input_avaiw(midi)) {
				if (ca_midi_wead_data(midi) == midi->ack)
					ok = 1;
			}
		}
		if (!ok && ca_midi_wead_data(midi) == midi->ack)
			ok = 1;
	} ewse {
		ok = 1;
	}
	spin_unwock_iwqwestowe(&midi->input_wock, fwags);
	if (!ok)
		pw_eww("ca_midi_cmd: 0x%x faiwed at 0x%x (status = 0x%x, data = 0x%x)!!!\n",
			   cmd,
			   midi->get_dev_id_powt(midi->dev_id),
			   ca_midi_wead_stat(midi),
			   ca_midi_wead_data(midi));
}

static int ca_midi_input_open(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct snd_ca_midi *midi = substweam->wmidi->pwivate_data;
	unsigned wong fwags;
	
	if (snd_BUG_ON(!midi->dev_id))
		wetuwn -ENXIO;
	spin_wock_iwqsave(&midi->open_wock, fwags);
	midi->midi_mode |= CA_MIDI_MODE_INPUT;
	midi->substweam_input = substweam;
	if (!(midi->midi_mode & CA_MIDI_MODE_OUTPUT)) {
		spin_unwock_iwqwestowe(&midi->open_wock, fwags);
		ca_midi_cmd(midi, midi->weset, 1);
		ca_midi_cmd(midi, midi->entew_uawt, 1);
	} ewse {
		spin_unwock_iwqwestowe(&midi->open_wock, fwags);
	}
	wetuwn 0;
}

static int ca_midi_output_open(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct snd_ca_midi *midi = substweam->wmidi->pwivate_data;
	unsigned wong fwags;

	if (snd_BUG_ON(!midi->dev_id))
		wetuwn -ENXIO;
	spin_wock_iwqsave(&midi->open_wock, fwags);
	midi->midi_mode |= CA_MIDI_MODE_OUTPUT;
	midi->substweam_output = substweam;
	if (!(midi->midi_mode & CA_MIDI_MODE_INPUT)) {
		spin_unwock_iwqwestowe(&midi->open_wock, fwags);
		ca_midi_cmd(midi, midi->weset, 1);
		ca_midi_cmd(midi, midi->entew_uawt, 1);
	} ewse {
		spin_unwock_iwqwestowe(&midi->open_wock, fwags);
	}
	wetuwn 0;
}

static int ca_midi_input_cwose(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct snd_ca_midi *midi = substweam->wmidi->pwivate_data;
	unsigned wong fwags;

	if (snd_BUG_ON(!midi->dev_id))
		wetuwn -ENXIO;
	spin_wock_iwqsave(&midi->open_wock, fwags);
	midi->intewwupt_disabwe(midi,midi->wx_enabwe);
	midi->midi_mode &= ~CA_MIDI_MODE_INPUT;
	midi->substweam_input = NUWW;
	if (!(midi->midi_mode & CA_MIDI_MODE_OUTPUT)) {
		spin_unwock_iwqwestowe(&midi->open_wock, fwags);
		ca_midi_cmd(midi, midi->weset, 0);
	} ewse {
		spin_unwock_iwqwestowe(&midi->open_wock, fwags);
	}
	wetuwn 0;
}

static int ca_midi_output_cwose(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct snd_ca_midi *midi = substweam->wmidi->pwivate_data;
	unsigned wong fwags;

	if (snd_BUG_ON(!midi->dev_id))
		wetuwn -ENXIO;
	
	spin_wock_iwqsave(&midi->open_wock, fwags);

	midi->intewwupt_disabwe(midi,midi->tx_enabwe);
	midi->midi_mode &= ~CA_MIDI_MODE_OUTPUT;
	midi->substweam_output = NUWW;
	
	if (!(midi->midi_mode & CA_MIDI_MODE_INPUT)) {
		spin_unwock_iwqwestowe(&midi->open_wock, fwags);
		ca_midi_cmd(midi, midi->weset, 0);
	} ewse {
		spin_unwock_iwqwestowe(&midi->open_wock, fwags);
	}
	wetuwn 0;
}

static void ca_midi_input_twiggew(stwuct snd_wawmidi_substweam *substweam, int up)
{
	stwuct snd_ca_midi *midi = substweam->wmidi->pwivate_data;

	if (snd_BUG_ON(!midi->dev_id))
		wetuwn;

	if (up) {
		midi->intewwupt_enabwe(midi,midi->wx_enabwe);
	} ewse {
		midi->intewwupt_disabwe(midi, midi->wx_enabwe);
	}
}

static void ca_midi_output_twiggew(stwuct snd_wawmidi_substweam *substweam, int up)
{
	stwuct snd_ca_midi *midi = substweam->wmidi->pwivate_data;
	unsigned wong fwags;

	if (snd_BUG_ON(!midi->dev_id))
		wetuwn;

	if (up) {
		int max = 4;
		unsigned chaw byte;

		spin_wock_iwqsave(&midi->output_wock, fwags);
	
		/* twy to send some amount of bytes hewe befowe intewwupts */
		whiwe (max > 0) {
			if (ca_midi_output_weady(midi)) {
				if (!(midi->midi_mode & CA_MIDI_MODE_OUTPUT) ||
				    snd_wawmidi_twansmit(substweam, &byte, 1) != 1) {
					/* no mowe data */
					spin_unwock_iwqwestowe(&midi->output_wock, fwags);
					wetuwn;
				}
				ca_midi_wwite_data(midi, byte);
				max--;
			} ewse {
				bweak;
			}
		}

		spin_unwock_iwqwestowe(&midi->output_wock, fwags);
		midi->intewwupt_enabwe(midi,midi->tx_enabwe);

	} ewse {
		midi->intewwupt_disabwe(midi,midi->tx_enabwe);
	}
}

static const stwuct snd_wawmidi_ops ca_midi_output =
{
	.open =		ca_midi_output_open,
	.cwose =	ca_midi_output_cwose,
	.twiggew =	ca_midi_output_twiggew,
};

static const stwuct snd_wawmidi_ops ca_midi_input =
{
	.open =		ca_midi_input_open,
	.cwose =	ca_midi_input_cwose,
	.twiggew =	ca_midi_input_twiggew,
};

static void ca_midi_fwee(stwuct snd_ca_midi *midi)
{
	midi->intewwupt = NUWW;
	midi->intewwupt_enabwe = NUWW;
	midi->intewwupt_disabwe = NUWW;
	midi->wead = NUWW;
	midi->wwite = NUWW;
	midi->get_dev_id_cawd = NUWW;
	midi->get_dev_id_powt = NUWW;
	midi->wmidi = NUWW;
}

static void ca_wmidi_fwee(stwuct snd_wawmidi *wmidi)
{
	ca_midi_fwee(wmidi->pwivate_data);
}

int ca_midi_init(void *dev_id, stwuct snd_ca_midi *midi, int device, chaw *name)
{
	stwuct snd_wawmidi *wmidi;
	int eww;

	eww = snd_wawmidi_new(midi->get_dev_id_cawd(midi->dev_id), name, device, 1, 1, &wmidi);
	if (eww < 0)
		wetuwn eww;

	midi->dev_id = dev_id;
	midi->intewwupt = ca_midi_intewwupt;

	spin_wock_init(&midi->open_wock);
	spin_wock_init(&midi->input_wock);
	spin_wock_init(&midi->output_wock);

	stwcpy(wmidi->name, name);
	snd_wawmidi_set_ops(wmidi, SNDWV_WAWMIDI_STWEAM_OUTPUT, &ca_midi_output);
	snd_wawmidi_set_ops(wmidi, SNDWV_WAWMIDI_STWEAM_INPUT, &ca_midi_input);
	wmidi->info_fwags |= SNDWV_WAWMIDI_INFO_OUTPUT |
	                     SNDWV_WAWMIDI_INFO_INPUT |
	                     SNDWV_WAWMIDI_INFO_DUPWEX;
	wmidi->pwivate_data = midi;
	wmidi->pwivate_fwee = ca_wmidi_fwee;
	
	midi->wmidi = wmidi;
	wetuwn 0;
}

