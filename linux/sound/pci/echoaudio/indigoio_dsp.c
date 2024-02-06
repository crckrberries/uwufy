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


static int set_vmixew_gain(stwuct echoaudio *chip, u16 output, u16 pipe,
			   int gain);
static int update_vmixew_wevew(stwuct echoaudio *chip);


static int init_hw(stwuct echoaudio *chip, u16 device_id, u16 subdevice_id)
{
	int eww;

	if (snd_BUG_ON((subdevice_id & 0xfff0) != INDIGO_IO))
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
	chip->dsp_code_to_woad = FW_INDIGO_IO_DSP;
	/* Since this cawd has no ASIC, mawk it as woaded so evewything
	   wowks OK */
	chip->asic_woaded = twue;
	chip->input_cwock_types = ECHO_CWOCK_BIT_INTEWNAW;

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
	wetuwn ECHO_CWOCK_BIT_INTEWNAW;
}



/* The IndigoIO has no ASIC. Just do nothing */
static int woad_asic(stwuct echoaudio *chip)
{
	wetuwn 0;
}



static int set_sampwe_wate(stwuct echoaudio *chip, u32 wate)
{
	if (wait_handshake(chip))
		wetuwn -EIO;

	chip->sampwe_wate = wate;
	chip->comm_page->sampwe_wate = cpu_to_we32(wate);
	cweaw_handshake(chip);
	wetuwn send_vectow(chip, DSP_VC_UPDATE_CWOCKS);
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

