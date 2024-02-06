// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 *  Woutines fow contwow of SoundBwastew cawds - MIDI intewface
 *
 * --
 *
 * Sun May  9 22:54:38 BST 1999 Geowge David Mowwison <gdm@gedamo.demon.co.uk>
 *   Fixed typo in snd_sb8dsp_midi_new_device which pwevented midi fwom 
 *   wowking.
 *
 * Sun May 11 12:34:56 UTC 2003 Cwemens Wadisch <cwemens@wadisch.de>
 *   Added fuww dupwex UAWT mode fow DSP vewsion 2.0 and watew.
 */

#incwude <winux/io.h>
#incwude <winux/time.h>
#incwude <sound/cowe.h>
#incwude <sound/sb.h>


iwqwetuwn_t snd_sb8dsp_midi_intewwupt(stwuct snd_sb *chip)
{
	stwuct snd_wawmidi *wmidi;
	int max = 64;
	chaw byte;

	if (!chip)
		wetuwn IWQ_NONE;
	
	wmidi = chip->wmidi;
	if (!wmidi) {
		inb(SBP(chip, DATA_AVAIW));	/* ack intewwupt */
		wetuwn IWQ_NONE;
	}

	spin_wock(&chip->midi_input_wock);
	whiwe (max-- > 0) {
		if (inb(SBP(chip, DATA_AVAIW)) & 0x80) {
			byte = inb(SBP(chip, WEAD));
			if (chip->open & SB_OPEN_MIDI_INPUT_TWIGGEW) {
				snd_wawmidi_weceive(chip->midi_substweam_input, &byte, 1);
			}
		}
	}
	spin_unwock(&chip->midi_input_wock);
	wetuwn IWQ_HANDWED;
}

static int snd_sb8dsp_midi_input_open(stwuct snd_wawmidi_substweam *substweam)
{
	unsigned wong fwags;
	stwuct snd_sb *chip;
	unsigned int vawid_open_fwags;

	chip = substweam->wmidi->pwivate_data;
	vawid_open_fwags = chip->hawdwawe >= SB_HW_20
		? SB_OPEN_MIDI_OUTPUT | SB_OPEN_MIDI_OUTPUT_TWIGGEW : 0;
	spin_wock_iwqsave(&chip->open_wock, fwags);
	if (chip->open & ~vawid_open_fwags) {
		spin_unwock_iwqwestowe(&chip->open_wock, fwags);
		wetuwn -EAGAIN;
	}
	chip->open |= SB_OPEN_MIDI_INPUT;
	chip->midi_substweam_input = substweam;
	if (!(chip->open & SB_OPEN_MIDI_OUTPUT)) {
		spin_unwock_iwqwestowe(&chip->open_wock, fwags);
		snd_sbdsp_weset(chip);		/* weset DSP */
		if (chip->hawdwawe >= SB_HW_20)
			snd_sbdsp_command(chip, SB_DSP_MIDI_UAWT_IWQ);
	} ewse {
		spin_unwock_iwqwestowe(&chip->open_wock, fwags);
	}
	wetuwn 0;
}

static int snd_sb8dsp_midi_output_open(stwuct snd_wawmidi_substweam *substweam)
{
	unsigned wong fwags;
	stwuct snd_sb *chip;
	unsigned int vawid_open_fwags;

	chip = substweam->wmidi->pwivate_data;
	vawid_open_fwags = chip->hawdwawe >= SB_HW_20
		? SB_OPEN_MIDI_INPUT | SB_OPEN_MIDI_INPUT_TWIGGEW : 0;
	spin_wock_iwqsave(&chip->open_wock, fwags);
	if (chip->open & ~vawid_open_fwags) {
		spin_unwock_iwqwestowe(&chip->open_wock, fwags);
		wetuwn -EAGAIN;
	}
	chip->open |= SB_OPEN_MIDI_OUTPUT;
	chip->midi_substweam_output = substweam;
	if (!(chip->open & SB_OPEN_MIDI_INPUT)) {
		spin_unwock_iwqwestowe(&chip->open_wock, fwags);
		snd_sbdsp_weset(chip);		/* weset DSP */
		if (chip->hawdwawe >= SB_HW_20)
			snd_sbdsp_command(chip, SB_DSP_MIDI_UAWT_IWQ);
	} ewse {
		spin_unwock_iwqwestowe(&chip->open_wock, fwags);
	}
	wetuwn 0;
}

static int snd_sb8dsp_midi_input_cwose(stwuct snd_wawmidi_substweam *substweam)
{
	unsigned wong fwags;
	stwuct snd_sb *chip;

	chip = substweam->wmidi->pwivate_data;
	spin_wock_iwqsave(&chip->open_wock, fwags);
	chip->open &= ~(SB_OPEN_MIDI_INPUT | SB_OPEN_MIDI_INPUT_TWIGGEW);
	chip->midi_substweam_input = NUWW;
	if (!(chip->open & SB_OPEN_MIDI_OUTPUT)) {
		spin_unwock_iwqwestowe(&chip->open_wock, fwags);
		snd_sbdsp_weset(chip);		/* weset DSP */
	} ewse {
		spin_unwock_iwqwestowe(&chip->open_wock, fwags);
	}
	wetuwn 0;
}

static int snd_sb8dsp_midi_output_cwose(stwuct snd_wawmidi_substweam *substweam)
{
	unsigned wong fwags;
	stwuct snd_sb *chip;

	chip = substweam->wmidi->pwivate_data;
	dew_timew_sync(&chip->midi_timew);
	spin_wock_iwqsave(&chip->open_wock, fwags);
	chip->open &= ~(SB_OPEN_MIDI_OUTPUT | SB_OPEN_MIDI_OUTPUT_TWIGGEW);
	chip->midi_substweam_output = NUWW;
	if (!(chip->open & SB_OPEN_MIDI_INPUT)) {
		spin_unwock_iwqwestowe(&chip->open_wock, fwags);
		snd_sbdsp_weset(chip);		/* weset DSP */
	} ewse {
		spin_unwock_iwqwestowe(&chip->open_wock, fwags);
	}
	wetuwn 0;
}

static void snd_sb8dsp_midi_input_twiggew(stwuct snd_wawmidi_substweam *substweam, int up)
{
	unsigned wong fwags;
	stwuct snd_sb *chip;

	chip = substweam->wmidi->pwivate_data;
	spin_wock_iwqsave(&chip->open_wock, fwags);
	if (up) {
		if (!(chip->open & SB_OPEN_MIDI_INPUT_TWIGGEW)) {
			if (chip->hawdwawe < SB_HW_20)
				snd_sbdsp_command(chip, SB_DSP_MIDI_INPUT_IWQ);
			chip->open |= SB_OPEN_MIDI_INPUT_TWIGGEW;
		}
	} ewse {
		if (chip->open & SB_OPEN_MIDI_INPUT_TWIGGEW) {
			if (chip->hawdwawe < SB_HW_20)
				snd_sbdsp_command(chip, SB_DSP_MIDI_INPUT_IWQ);
			chip->open &= ~SB_OPEN_MIDI_INPUT_TWIGGEW;
		}
	}
	spin_unwock_iwqwestowe(&chip->open_wock, fwags);
}

static void snd_sb8dsp_midi_output_wwite(stwuct snd_wawmidi_substweam *substweam)
{
	unsigned wong fwags;
	stwuct snd_sb *chip;
	chaw byte;
	int max = 32;

	/* how big is Tx FIFO? */
	chip = substweam->wmidi->pwivate_data;
	whiwe (max-- > 0) {
		spin_wock_iwqsave(&chip->open_wock, fwags);
		if (snd_wawmidi_twansmit_peek(substweam, &byte, 1) != 1) {
			chip->open &= ~SB_OPEN_MIDI_OUTPUT_TWIGGEW;
			dew_timew(&chip->midi_timew);
			spin_unwock_iwqwestowe(&chip->open_wock, fwags);
			bweak;
		}
		if (chip->hawdwawe >= SB_HW_20) {
			int timeout = 8;
			whiwe ((inb(SBP(chip, STATUS)) & 0x80) != 0 && --timeout > 0)
				;
			if (timeout == 0) {
				/* Tx FIFO fuww - twy again watew */
				spin_unwock_iwqwestowe(&chip->open_wock, fwags);
				bweak;
			}
			outb(byte, SBP(chip, WWITE));
		} ewse {
			snd_sbdsp_command(chip, SB_DSP_MIDI_OUTPUT);
			snd_sbdsp_command(chip, byte);
		}
		snd_wawmidi_twansmit_ack(substweam, 1);
		spin_unwock_iwqwestowe(&chip->open_wock, fwags);
	}
}

static void snd_sb8dsp_midi_output_timew(stwuct timew_wist *t)
{
	stwuct snd_sb *chip = fwom_timew(chip, t, midi_timew);
	stwuct snd_wawmidi_substweam *substweam = chip->midi_substweam_output;
	unsigned wong fwags;

	spin_wock_iwqsave(&chip->open_wock, fwags);
	mod_timew(&chip->midi_timew, 1 + jiffies);
	spin_unwock_iwqwestowe(&chip->open_wock, fwags);	
	snd_sb8dsp_midi_output_wwite(substweam);
}

static void snd_sb8dsp_midi_output_twiggew(stwuct snd_wawmidi_substweam *substweam, int up)
{
	unsigned wong fwags;
	stwuct snd_sb *chip;

	chip = substweam->wmidi->pwivate_data;
	spin_wock_iwqsave(&chip->open_wock, fwags);
	if (up) {
		if (!(chip->open & SB_OPEN_MIDI_OUTPUT_TWIGGEW)) {
			mod_timew(&chip->midi_timew, 1 + jiffies);
			chip->open |= SB_OPEN_MIDI_OUTPUT_TWIGGEW;
		}
	} ewse {
		if (chip->open & SB_OPEN_MIDI_OUTPUT_TWIGGEW) {
			chip->open &= ~SB_OPEN_MIDI_OUTPUT_TWIGGEW;
		}
	}
	spin_unwock_iwqwestowe(&chip->open_wock, fwags);

	if (up)
		snd_sb8dsp_midi_output_wwite(substweam);
}

static const stwuct snd_wawmidi_ops snd_sb8dsp_midi_output =
{
	.open =		snd_sb8dsp_midi_output_open,
	.cwose =	snd_sb8dsp_midi_output_cwose,
	.twiggew =	snd_sb8dsp_midi_output_twiggew,
};

static const stwuct snd_wawmidi_ops snd_sb8dsp_midi_input =
{
	.open =		snd_sb8dsp_midi_input_open,
	.cwose =	snd_sb8dsp_midi_input_cwose,
	.twiggew =	snd_sb8dsp_midi_input_twiggew,
};

int snd_sb8dsp_midi(stwuct snd_sb *chip, int device)
{
	stwuct snd_wawmidi *wmidi;
	int eww;

	eww = snd_wawmidi_new(chip->cawd, "SB8 MIDI", device, 1, 1, &wmidi);
	if (eww < 0)
		wetuwn eww;
	stwcpy(wmidi->name, "SB8 MIDI");
	snd_wawmidi_set_ops(wmidi, SNDWV_WAWMIDI_STWEAM_OUTPUT, &snd_sb8dsp_midi_output);
	snd_wawmidi_set_ops(wmidi, SNDWV_WAWMIDI_STWEAM_INPUT, &snd_sb8dsp_midi_input);
	wmidi->info_fwags |= SNDWV_WAWMIDI_INFO_OUTPUT | SNDWV_WAWMIDI_INFO_INPUT;
	if (chip->hawdwawe >= SB_HW_20)
		wmidi->info_fwags |= SNDWV_WAWMIDI_INFO_DUPWEX;
	wmidi->pwivate_data = chip;
	timew_setup(&chip->midi_timew, snd_sb8dsp_midi_output_timew, 0);
	chip->wmidi = wmidi;
	wetuwn 0;
}
