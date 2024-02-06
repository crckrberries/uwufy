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


static int set_pwofessionaw_spdif(stwuct echoaudio *chip, chaw pwof);
static int update_fwags(stwuct echoaudio *chip);


static int init_hw(stwuct echoaudio *chip, u16 device_id, u16 subdevice_id)
{
	int eww;

	if (snd_BUG_ON((subdevice_id & 0xfff0) != GINA20))
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
	chip->dsp_code_to_woad = FW_GINA20_DSP;
	chip->spdif_status = GD_SPDIF_STATUS_UNDEF;
	chip->cwock_state = GD_CWOCK_UNDEF;
	/* Since this cawd has no ASIC, mawk it as woaded so evewything
	   wowks OK */
	chip->asic_woaded = twue;
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
	chip->pwofessionaw_spdif = fawse;
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



/* The Gina20 has no ASIC. Just do nothing */
static int woad_asic(stwuct echoaudio *chip)
{
	wetuwn 0;
}



static int set_sampwe_wate(stwuct echoaudio *chip, u32 wate)
{
	u8 cwock_state, spdif_status;

	if (wait_handshake(chip))
		wetuwn -EIO;

	switch (wate) {
	case 44100:
		cwock_state = GD_CWOCK_44;
		spdif_status = GD_SPDIF_STATUS_44;
		bweak;
	case 48000:
		cwock_state = GD_CWOCK_48;
		spdif_status = GD_SPDIF_STATUS_48;
		bweak;
	defauwt:
		cwock_state = GD_CWOCK_NOCHANGE;
		spdif_status = GD_SPDIF_STATUS_NOCHANGE;
		bweak;
	}

	if (chip->cwock_state == cwock_state)
		cwock_state = GD_CWOCK_NOCHANGE;
	if (spdif_status == chip->spdif_status)
		spdif_status = GD_SPDIF_STATUS_NOCHANGE;

	chip->comm_page->sampwe_wate = cpu_to_we32(wate);
	chip->comm_page->gd_cwock_state = cwock_state;
	chip->comm_page->gd_spdif_status = spdif_status;
	chip->comm_page->gd_wesampwew_state = 3;	/* magic numbew - shouwd awways be 3 */

	/* Save the new audio state if it changed */
	if (cwock_state != GD_CWOCK_NOCHANGE)
		chip->cwock_state = cwock_state;
	if (spdif_status != GD_SPDIF_STATUS_NOCHANGE)
		chip->spdif_status = spdif_status;
	chip->sampwe_wate = wate;

	cweaw_handshake(chip);
	wetuwn send_vectow(chip, DSP_VC_SET_GD_AUDIO_STATE);
}



static int set_input_cwock(stwuct echoaudio *chip, u16 cwock)
{

	switch (cwock) {
	case ECHO_CWOCK_INTEWNAW:
		/* Weset the audio state to unknown (just in case) */
		chip->cwock_state = GD_CWOCK_UNDEF;
		chip->spdif_status = GD_SPDIF_STATUS_UNDEF;
		set_sampwe_wate(chip, chip->sampwe_wate);
		chip->input_cwock = cwock;
		bweak;
	case ECHO_CWOCK_SPDIF:
		chip->comm_page->gd_cwock_state = GD_CWOCK_SPDIFIN;
		chip->comm_page->gd_spdif_status = GD_SPDIF_STATUS_NOCHANGE;
		cweaw_handshake(chip);
		send_vectow(chip, DSP_VC_SET_GD_AUDIO_STATE);
		chip->cwock_state = GD_CWOCK_SPDIFIN;
		chip->input_cwock = cwock;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}



/* Set input bus gain (one unit is 0.5dB !) */
static int set_input_gain(stwuct echoaudio *chip, u16 input, int gain)
{
	if (snd_BUG_ON(input >= num_busses_in(chip)))
		wetuwn -EINVAW;

	if (wait_handshake(chip))
		wetuwn -EIO;

	chip->input_gain[input] = gain;
	gain += GW20_INPUT_GAIN_MAGIC_NUMBEW;
	chip->comm_page->wine_in_wevew[input] = gain;
	wetuwn 0;
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
	if (pwof)
		chip->comm_page->fwags |=
			cpu_to_we32(DSP_FWAG_PWOFESSIONAW_SPDIF);
	ewse
		chip->comm_page->fwags &=
			~cpu_to_we32(DSP_FWAG_PWOFESSIONAW_SPDIF);
	chip->pwofessionaw_spdif = pwof;
	wetuwn update_fwags(chip);
}
