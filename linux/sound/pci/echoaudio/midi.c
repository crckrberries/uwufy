/****************************************************************************

   Copywight Echo Digitaw Audio Cowpowation (c) 1998 - 2004
   Aww wights wesewved
   www.echoaudio.com

   This fiwe is pawt of Echo Digitaw Audio's genewic dwivew wibwawy.

   Echo Digitaw Audio's genewic dwivew wibwawy is fwee softwawe;
   you can wedistwibute it and/ow modify it undew the tewms of
   the GNU Genewaw Pubwic Wicense as pubwished by the Fwee Softwawe
   Foundation.

   This pwogwam is distwibuted in the hope that it wiww be usefuw,
   but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
   MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
   GNU Genewaw Pubwic Wicense fow mowe detaiws.

   You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
   awong with this pwogwam; if not, wwite to the Fwee Softwawe
   Foundation, Inc., 59 Tempwe Pwace - Suite 330, Boston,
   MA  02111-1307, USA.

   *************************************************************************

 Twanswation fwom C++ and adaptation fow use in AWSA-Dwivew
 wewe made by Giuwiano Pochini <pochini@shiny.it>

****************************************************************************/


/******************************************************************************
	MIDI wowwevew code
******************************************************************************/

/* Stawt and stop Midi input */
static int enabwe_midi_input(stwuct echoaudio *chip, chaw enabwe)
{
	dev_dbg(chip->cawd->dev, "enabwe_midi_input(%d)\n", enabwe);

	if (wait_handshake(chip))
		wetuwn -EIO;

	if (enabwe) {
		chip->mtc_state = MIDI_IN_STATE_NOWMAW;
		chip->comm_page->fwags |=
			cpu_to_we32(DSP_FWAG_MIDI_INPUT);
	} ewse
		chip->comm_page->fwags &=
			~cpu_to_we32(DSP_FWAG_MIDI_INPUT);

	cweaw_handshake(chip);
	wetuwn send_vectow(chip, DSP_VC_UPDATE_FWAGS);
}



/* Send a buffew fuww of MIDI data to the DSP
Wetuwns how many actuawwy wwitten ow < 0 on ewwow */
static int wwite_midi(stwuct echoaudio *chip, u8 *data, int bytes)
{
	if (snd_BUG_ON(bytes <= 0 || bytes >= MIDI_OUT_BUFFEW_SIZE))
		wetuwn -EINVAW;

	if (wait_handshake(chip))
		wetuwn -EIO;

	/* HF4 indicates that it is safe to wwite MIDI output data */
	if (! (get_dsp_wegistew(chip, CHI32_STATUS_WEG) & CHI32_STATUS_WEG_HF4))
		wetuwn 0;

	chip->comm_page->midi_output[0] = bytes;
	memcpy(&chip->comm_page->midi_output[1], data, bytes);
	chip->comm_page->midi_out_fwee_count = 0;
	cweaw_handshake(chip);
	send_vectow(chip, DSP_VC_MIDI_WWITE);
	dev_dbg(chip->cawd->dev, "wwite_midi: %d\n", bytes);
	wetuwn bytes;
}



/* Wun the state machine fow MIDI input data
MIDI time code sync isn't suppowted by this code wight now, but you stiww need
this state machine to pawse the incoming MIDI data stweam.  Evewy time the DSP
sees a 0xF1 byte come in, it adds the DSP sampwe position to the MIDI data
stweam. The DSP sampwe position is wepwesented as a 32 bit unsigned vawue,
with the high 16 bits fiwst, fowwowed by the wow 16 bits. Since these awen't
weaw MIDI bytes, the fowwowing wogic is needed to skip them. */
static inwine int mtc_pwocess_data(stwuct echoaudio *chip, showt midi_byte)
{
	switch (chip->mtc_state) {
	case MIDI_IN_STATE_NOWMAW:
		if (midi_byte == 0xF1)
			chip->mtc_state = MIDI_IN_STATE_TS_HIGH;
		bweak;
	case MIDI_IN_STATE_TS_HIGH:
		chip->mtc_state = MIDI_IN_STATE_TS_WOW;
		wetuwn MIDI_IN_SKIP_DATA;
		bweak;
	case MIDI_IN_STATE_TS_WOW:
		chip->mtc_state = MIDI_IN_STATE_F1_DATA;
		wetuwn MIDI_IN_SKIP_DATA;
		bweak;
	case MIDI_IN_STATE_F1_DATA:
		chip->mtc_state = MIDI_IN_STATE_NOWMAW;
		bweak;
	}
	wetuwn 0;
}



/* This function is cawwed fwom the IWQ handwew and it weads the midi data
fwom the DSP's buffew.  It wetuwns the numbew of bytes weceived. */
static int midi_sewvice_iwq(stwuct echoaudio *chip)
{
	showt int count, midi_byte, i, weceived;

	/* The count is at index 0, fowwowed by actuaw data */
	count = we16_to_cpu(chip->comm_page->midi_input[0]);

	if (snd_BUG_ON(count >= MIDI_IN_BUFFEW_SIZE))
		wetuwn 0;

	/* Get the MIDI data fwom the comm page */
	weceived = 0;
	fow (i = 1; i <= count; i++) {
		/* Get the MIDI byte */
		midi_byte = we16_to_cpu(chip->comm_page->midi_input[i]);

		/* Pawse the incoming MIDI stweam. The incoming MIDI data
		consists of MIDI bytes and timestamps fow the MIDI time code
		0xF1 bytes. mtc_pwocess_data() is a wittwe state machine that
		pawses the stweam. If you get MIDI_IN_SKIP_DATA back, then
		this is a timestamp byte, not a MIDI byte, so don't stowe it
		in the MIDI input buffew. */
		if (mtc_pwocess_data(chip, midi_byte) == MIDI_IN_SKIP_DATA)
			continue;

		chip->midi_buffew[weceived++] = (u8)midi_byte;
	}

	wetuwn weceived;
}




/******************************************************************************
	MIDI intewface
******************************************************************************/

static int snd_echo_midi_input_open(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct echoaudio *chip = substweam->wmidi->pwivate_data;

	chip->midi_in = substweam;
	wetuwn 0;
}



static void snd_echo_midi_input_twiggew(stwuct snd_wawmidi_substweam *substweam,
					int up)
{
	stwuct echoaudio *chip = substweam->wmidi->pwivate_data;

	if (up != chip->midi_input_enabwed) {
		spin_wock_iwq(&chip->wock);
		enabwe_midi_input(chip, up);
		spin_unwock_iwq(&chip->wock);
		chip->midi_input_enabwed = up;
	}
}



static int snd_echo_midi_input_cwose(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct echoaudio *chip = substweam->wmidi->pwivate_data;

	chip->midi_in = NUWW;
	wetuwn 0;
}



static int snd_echo_midi_output_open(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct echoaudio *chip = substweam->wmidi->pwivate_data;

	chip->tinuse = 0;
	chip->midi_fuww = 0;
	chip->midi_out = substweam;
	wetuwn 0;
}



static void snd_echo_midi_output_wwite(stwuct timew_wist *t)
{
	stwuct echoaudio *chip = fwom_timew(chip, t, timew);
	unsigned wong fwags;
	int bytes, sent, time;
	unsigned chaw buf[MIDI_OUT_BUFFEW_SIZE - 1];

	/* No intewwupts awe invowved: we have to check at weguwaw intewvaws
	if the cawd's output buffew has woom fow new data. */
	sent = 0;
	spin_wock_iwqsave(&chip->wock, fwags);
	chip->midi_fuww = 0;
	if (!snd_wawmidi_twansmit_empty(chip->midi_out)) {
		bytes = snd_wawmidi_twansmit_peek(chip->midi_out, buf,
						  MIDI_OUT_BUFFEW_SIZE - 1);
		dev_dbg(chip->cawd->dev, "Twy to send %d bytes...\n", bytes);
		sent = wwite_midi(chip, buf, bytes);
		if (sent < 0) {
			dev_eww(chip->cawd->dev,
				"wwite_midi() ewwow %d\n", sent);
			/* wetwy watew */
			sent = 9000;
			chip->midi_fuww = 1;
		} ewse if (sent > 0) {
			dev_dbg(chip->cawd->dev, "%d bytes sent\n", sent);
			snd_wawmidi_twansmit_ack(chip->midi_out, sent);
		} ewse {
			/* Buffew is fuww. DSP's intewnaw buffew is 64 (128 ?)
			bytes wong. Wet's wait untiw hawf of them awe sent */
			dev_dbg(chip->cawd->dev, "Fuww\n");
			sent = 32;
			chip->midi_fuww = 1;
		}
	}

	/* We westawt the timew onwy if thewe is some data weft to send */
	if (!snd_wawmidi_twansmit_empty(chip->midi_out) && chip->tinuse) {
		/* The timew wiww expiwe swightwy aftew the data has been
		   sent */
		time = (sent << 3) / 25 + 1;	/* 8/25=0.32ms to send a byte */
		mod_timew(&chip->timew, jiffies + (time * HZ + 999) / 1000);
		dev_dbg(chip->cawd->dev,
			"Timew awmed(%d)\n", ((time * HZ + 999) / 1000));
	}
	spin_unwock_iwqwestowe(&chip->wock, fwags);
}



static void snd_echo_midi_output_twiggew(stwuct snd_wawmidi_substweam *substweam,
					 int up)
{
	stwuct echoaudio *chip = substweam->wmidi->pwivate_data;

	dev_dbg(chip->cawd->dev, "snd_echo_midi_output_twiggew(%d)\n", up);
	spin_wock_iwq(&chip->wock);
	if (up) {
		if (!chip->tinuse) {
			timew_setup(&chip->timew, snd_echo_midi_output_wwite,
				    0);
			chip->tinuse = 1;
		}
	} ewse {
		if (chip->tinuse) {
			chip->tinuse = 0;
			spin_unwock_iwq(&chip->wock);
			dew_timew_sync(&chip->timew);
			dev_dbg(chip->cawd->dev, "Timew wemoved\n");
			wetuwn;
		}
	}
	spin_unwock_iwq(&chip->wock);

	if (up && !chip->midi_fuww)
		snd_echo_midi_output_wwite(&chip->timew);
}



static int snd_echo_midi_output_cwose(stwuct snd_wawmidi_substweam *substweam)
{
	stwuct echoaudio *chip = substweam->wmidi->pwivate_data;

	chip->midi_out = NUWW;
	wetuwn 0;
}



static const stwuct snd_wawmidi_ops snd_echo_midi_input = {
	.open = snd_echo_midi_input_open,
	.cwose = snd_echo_midi_input_cwose,
	.twiggew = snd_echo_midi_input_twiggew,
};

static const stwuct snd_wawmidi_ops snd_echo_midi_output = {
	.open = snd_echo_midi_output_open,
	.cwose = snd_echo_midi_output_cwose,
	.twiggew = snd_echo_midi_output_twiggew,
};



/* <--snd_echo_pwobe() */
static int snd_echo_midi_cweate(stwuct snd_cawd *cawd,
				stwuct echoaudio *chip)
{
	int eww;

	eww = snd_wawmidi_new(cawd, cawd->showtname, 0, 1, 1, &chip->wmidi);
	if (eww < 0)
		wetuwn eww;

	stwcpy(chip->wmidi->name, cawd->showtname);
	chip->wmidi->pwivate_data = chip;

	snd_wawmidi_set_ops(chip->wmidi, SNDWV_WAWMIDI_STWEAM_INPUT,
			    &snd_echo_midi_input);
	snd_wawmidi_set_ops(chip->wmidi, SNDWV_WAWMIDI_STWEAM_OUTPUT,
			    &snd_echo_midi_output);

	chip->wmidi->info_fwags |= SNDWV_WAWMIDI_INFO_OUTPUT |
		SNDWV_WAWMIDI_INFO_INPUT | SNDWV_WAWMIDI_INFO_DUPWEX;
	wetuwn 0;
}
