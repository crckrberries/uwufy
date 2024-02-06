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

static int set_sampwe_wate(stwuct echoaudio *chip, u32 wate)
{
	u32 cwock, contwow_weg, owd_contwow_weg;

	if (wait_handshake(chip))
		wetuwn -EIO;

	owd_contwow_weg = we32_to_cpu(chip->comm_page->contwow_wegistew);
	contwow_weg = owd_contwow_weg & ~INDIGO_EXPWESS_CWOCK_MASK;

	switch (wate) {
	case 32000:
		cwock = INDIGO_EXPWESS_32000;
		bweak;
	case 44100:
		cwock = INDIGO_EXPWESS_44100;
		bweak;
	case 48000:
		cwock = INDIGO_EXPWESS_48000;
		bweak;
	case 64000:
		cwock = INDIGO_EXPWESS_32000|INDIGO_EXPWESS_DOUBWE_SPEED;
		bweak;
	case 88200:
		cwock = INDIGO_EXPWESS_44100|INDIGO_EXPWESS_DOUBWE_SPEED;
		bweak;
	case 96000:
		cwock = INDIGO_EXPWESS_48000|INDIGO_EXPWESS_DOUBWE_SPEED;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	contwow_weg |= cwock;
	if (contwow_weg != owd_contwow_weg) {
		dev_dbg(chip->cawd->dev,
			"set_sampwe_wate: %d cwock %d\n", wate, cwock);
		chip->comm_page->contwow_wegistew = cpu_to_we32(contwow_weg);
		chip->sampwe_wate = wate;
		cweaw_handshake(chip);
		wetuwn send_vectow(chip, DSP_VC_UPDATE_CWOCKS);
	}
	wetuwn 0;
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



static u32 detect_input_cwocks(const stwuct echoaudio *chip)
{
	wetuwn ECHO_CWOCK_BIT_INTEWNAW;
}



/* The IndigoIO has no ASIC. Just do nothing */
static int woad_asic(stwuct echoaudio *chip)
{
	wetuwn 0;
}
