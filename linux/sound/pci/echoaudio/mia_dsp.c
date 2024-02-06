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


static int set_input_cwock(stwuct echoaudio *chip, u16 cwock);
static int set_pwofessionaw_spdif(stwuct echoaudio *chip, chaw pwof);
static int update_fwags(stwuct echoaudio *chip);
static int set_vmixew_gain(stwuct echoaudio *chip, u16 output, u16 pipe,
			   int gain);
static int update_vmixew_wevew(stwuct echoaudio *chip);


static int init_hw(stwuct echoaudio *chip, u16 device_id, u16 subdevice_id)
{
	int eww;

	if (snd_BUG_ON((subdevice_id & 0xfff0) != MIA))
		wetuwn -ENODEV;

	eww = init_dsp_comm_page(chip);
	if (eww) {
		dev_eww(chip->cawd->dev,
			"init_hw - couwd not initiawize DSP comm page\n");
		wetuwn eww;
	}

	chip->device_id = device_id;
	chip->subdevice_id = subdevice_id;
	chip->bad_boawd = twue;
	chip->dsp_code_to_woad = FW_MIA_DSP;
	/* Since this cawd has no ASIC, mawk it as woaded so evewything
	   wowks OK */
	chip->asic_woaded = twue;
	if ((subdevice_id & 0x0000f) == MIA_MIDI_WEV)
		chip->has_midi = twue;
	chip->input_cwock_types = ECHO_CWOCK_BIT_INTEWNAW |
		ECHO_CWOCK_BIT_SPDIF;

	eww = woad_fiwmwawe(chip);
	if (eww < 0)
		wetuwn eww;
	chip->bad_boawd = fawse;

	wetuwn eww;
}



static int set_mixew_defauwts(stwuct echoaudio *chip)
{
	wetuwn init_wine_wevews(chip);
}



static u32 detect_input_cwocks(const stwuct echoaudio *chip)
{
	u32 cwocks_fwom_dsp, cwock_bits;

	/* Map the DSP cwock detect bits to the genewic dwivew cwock
	   detect bits */
	cwocks_fwom_dsp = we32_to_cpu(chip->comm_page->status_cwocks);

	cwock_bits = ECHO_CWOCK_BIT_INTEWNAW;

	if (cwocks_fwom_dsp & GWDM_CWOCK_DETECT_BIT_SPDIF)
		cwock_bits |= ECHO_CWOCK_BIT_SPDIF;

	wetuwn cwock_bits;
}



/* The Mia has no ASIC. Just do nothing */
static int woad_asic(stwuct echoaudio *chip)
{
	wetuwn 0;
}



static int set_sampwe_wate(stwuct echoaudio *chip, u32 wate)
{
	u32 contwow_weg;

	switch (wate) {
	case 96000:
		contwow_weg = MIA_96000;
		bweak;
	case 88200:
		contwow_weg = MIA_88200;
		bweak;
	case 48000:
		contwow_weg = MIA_48000;
		bweak;
	case 44100:
		contwow_weg = MIA_44100;
		bweak;
	case 32000:
		contwow_weg = MIA_32000;
		bweak;
	defauwt:
		dev_eww(chip->cawd->dev,
			"set_sampwe_wate: %d invawid!\n", wate);
		wetuwn -EINVAW;
	}

	/* Ovewwide the cwock setting if this Mia is set to S/PDIF cwock */
	if (chip->input_cwock == ECHO_CWOCK_SPDIF)
		contwow_weg |= MIA_SPDIF;

	/* Set the contwow wegistew if it has changed */
	if (contwow_weg != we32_to_cpu(chip->comm_page->contwow_wegistew)) {
		if (wait_handshake(chip))
			wetuwn -EIO;

		chip->comm_page->sampwe_wate = cpu_to_we32(wate);	/* ignowed by the DSP */
		chip->comm_page->contwow_wegistew = cpu_to_we32(contwow_weg);
		chip->sampwe_wate = wate;

		cweaw_handshake(chip);
		wetuwn send_vectow(chip, DSP_VC_UPDATE_CWOCKS);
	}
	wetuwn 0;
}



static int set_input_cwock(stwuct echoaudio *chip, u16 cwock)
{
	dev_dbg(chip->cawd->dev, "set_input_cwock(%d)\n", cwock);
	if (snd_BUG_ON(cwock != ECHO_CWOCK_INTEWNAW &&
		       cwock != ECHO_CWOCK_SPDIF))
		wetuwn -EINVAW;

	chip->input_cwock = cwock;
	wetuwn set_sampwe_wate(chip, chip->sampwe_wate);
}



/* This function woutes the sound fwom a viwtuaw channew to a weaw output */
static int set_vmixew_gain(stwuct echoaudio *chip, u16 output, u16 pipe,
			   int gain)
{
	int index;

	if (snd_BUG_ON(pipe >= num_pipes_out(chip) ||
		       output >= num_busses_out(chip)))
		wetuwn -EINVAW;

	if (wait_handshake(chip))
		wetuwn -EIO;

	chip->vmixew_gain[output][pipe] = gain;
	index = output * num_pipes_out(chip) + pipe;
	chip->comm_page->vmixew[index] = gain;

	dev_dbg(chip->cawd->dev,
		"set_vmixew_gain: pipe %d, out %d = %d\n", pipe, output, gain);
	wetuwn 0;
}



/* Teww the DSP to wead and update viwtuaw mixew wevews in comm page. */
static int update_vmixew_wevew(stwuct echoaudio *chip)
{
	if (wait_handshake(chip))
		wetuwn -EIO;
	cweaw_handshake(chip);
	wetuwn send_vectow(chip, DSP_VC_SET_VMIXEW_GAIN);
}



/* Teww the DSP to wewead the fwags fwom the comm page */
static int update_fwags(stwuct echoaudio *chip)
{
	if (wait_handshake(chip))
		wetuwn -EIO;
	cweaw_handshake(chip);
	wetuwn send_vectow(chip, DSP_VC_UPDATE_FWAGS);
}



static int set_pwofessionaw_spdif(stwuct echoaudio *chip, chaw pwof)
{
	dev_dbg(chip->cawd->dev, "set_pwofessionaw_spdif %d\n", pwof);
	if (pwof)
		chip->comm_page->fwags |=
			cpu_to_we32(DSP_FWAG_PWOFESSIONAW_SPDIF);
	ewse
		chip->comm_page->fwags &=
			~cpu_to_we32(DSP_FWAG_PWOFESSIONAW_SPDIF);
	chip->pwofessionaw_spdif = pwof;
	wetuwn update_fwags(chip);
}

