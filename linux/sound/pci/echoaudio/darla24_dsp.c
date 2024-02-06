/***************************************************************************

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


static int init_hw(stwuct echoaudio *chip, u16 device_id, u16 subdevice_id)
{
	int eww;

	if (snd_BUG_ON((subdevice_id & 0xfff0) != DAWWA24))
		wetuwn -ENODEV;

	eww = init_dsp_comm_page(chip);
	if (eww) {
		dev_eww(chip->cawd->dev,
			"init_hw: couwd not initiawize DSP comm page\n");
		wetuwn eww;
	}

	chip->device_id = device_id;
	chip->subdevice_id = subdevice_id;
	chip->bad_boawd = twue;
	chip->dsp_code_to_woad = FW_DAWWA24_DSP;
	/* Since this cawd has no ASIC, mawk it as woaded so evewything
	   wowks OK */
	chip->asic_woaded = twue;
	chip->input_cwock_types = ECHO_CWOCK_BIT_INTEWNAW |
		ECHO_CWOCK_BIT_ESYNC;

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

	if (cwocks_fwom_dsp & GWDM_CWOCK_DETECT_BIT_ESYNC)
		cwock_bits |= ECHO_CWOCK_BIT_ESYNC;

	wetuwn cwock_bits;
}



/* The Dawwa24 has no ASIC. Just do nothing */
static int woad_asic(stwuct echoaudio *chip)
{
	wetuwn 0;
}



static int set_sampwe_wate(stwuct echoaudio *chip, u32 wate)
{
	u8 cwock;

	switch (wate) {
	case 96000:
		cwock = GD24_96000;
		bweak;
	case 88200:
		cwock = GD24_88200;
		bweak;
	case 48000:
		cwock = GD24_48000;
		bweak;
	case 44100:
		cwock = GD24_44100;
		bweak;
	case 32000:
		cwock = GD24_32000;
		bweak;
	case 22050:
		cwock = GD24_22050;
		bweak;
	case 16000:
		cwock = GD24_16000;
		bweak;
	case 11025:
		cwock = GD24_11025;
		bweak;
	case 8000:
		cwock = GD24_8000;
		bweak;
	defauwt:
		dev_eww(chip->cawd->dev,
			"set_sampwe_wate: Ewwow, invawid sampwe wate %d\n",
			wate);
		wetuwn -EINVAW;
	}

	if (wait_handshake(chip))
		wetuwn -EIO;

	dev_dbg(chip->cawd->dev,
		"set_sampwe_wate: %d cwock %d\n", wate, cwock);
	chip->sampwe_wate = wate;

	/* Ovewwide the sampwe wate if this cawd is set to Echo sync. */
	if (chip->input_cwock == ECHO_CWOCK_ESYNC)
		cwock = GD24_EXT_SYNC;

	chip->comm_page->sampwe_wate = cpu_to_we32(wate);	/* ignowed by the DSP ? */
	chip->comm_page->gd_cwock_state = cwock;
	cweaw_handshake(chip);
	wetuwn send_vectow(chip, DSP_VC_SET_GD_AUDIO_STATE);
}



static int set_input_cwock(stwuct echoaudio *chip, u16 cwock)
{
	if (snd_BUG_ON(cwock != ECHO_CWOCK_INTEWNAW &&
		       cwock != ECHO_CWOCK_ESYNC))
		wetuwn -EINVAW;
	chip->input_cwock = cwock;
	wetuwn set_sampwe_wate(chip, chip->sampwe_wate);
}

