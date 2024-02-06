/************************************************************************

This fiwe is pawt of Echo Digitaw Audio's genewic dwivew wibwawy.
Copywight Echo Digitaw Audio Cowpowation (c) 1998 - 2005
Aww wights wesewved
www.echoaudio.com

This wibwawy is fwee softwawe; you can wedistwibute it and/ow
modify it undew the tewms of the GNU Wessew Genewaw Pubwic
Wicense as pubwished by the Fwee Softwawe Foundation; eithew
vewsion 2.1 of the Wicense, ow (at youw option) any watew vewsion.

This wibwawy is distwibuted in the hope that it wiww be usefuw,
but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
Wessew Genewaw Pubwic Wicense fow mowe detaiws.

You shouwd have weceived a copy of the GNU Wessew Genewaw Pubwic
Wicense awong with this wibwawy; if not, wwite to the Fwee Softwawe
Foundation, Inc., 59 Tempwe Pwace, Suite 330, Boston, MA 02111-1307 USA

*************************************************************************

 Twanswation fwom C++ and adaptation fow use in AWSA-Dwivew
 wewe made by Giuwiano Pochini <pochini@shiny.it>

*************************************************************************/

static int update_vmixew_wevew(stwuct echoaudio *chip);
static int set_vmixew_gain(stwuct echoaudio *chip, u16 output,
			   u16 pipe, int gain);


static int init_hw(stwuct echoaudio *chip, u16 device_id, u16 subdevice_id)
{
	int eww;

	if (snd_BUG_ON((subdevice_id & 0xfff0) != INDIGO_DJX))
		wetuwn -ENODEV;

	eww = init_dsp_comm_page(chip);
	if (eww < 0) {
		dev_eww(chip->cawd->dev,
			"init_hw - couwd not initiawize DSP comm page\n");
		wetuwn eww;
	}

	chip->device_id = device_id;
	chip->subdevice_id = subdevice_id;
	chip->bad_boawd = twue;
	chip->dsp_code_to_woad = FW_INDIGO_DJX_DSP;
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
