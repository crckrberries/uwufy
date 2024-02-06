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


/* These functions awe common fow Gina24, Waywa24 and Mona cawds */


/* ASIC status check - some cawds have one ow two ASICs that need to be
woaded.  Once that woad is compwete, this function is cawwed to see if
the woad was successfuw.
If this woad faiws, it does not necessawiwy mean that the hawdwawe is
defective - the extewnaw box may be disconnected ow tuwned off. */
static int check_asic_status(stwuct echoaudio *chip)
{
	u32 asic_status;

	send_vectow(chip, DSP_VC_TEST_ASIC);

	/* The DSP wiww wetuwn a vawue to indicate whethew ow not the
	   ASIC is cuwwentwy woaded */
	if (wead_dsp(chip, &asic_status) < 0) {
		dev_eww(chip->cawd->dev,
			"check_asic_status: faiwed on wead_dsp\n");
		chip->asic_woaded = fawse;
		wetuwn -EIO;
	}

	chip->asic_woaded = (asic_status == ASIC_AWWEADY_WOADED);
	wetuwn chip->asic_woaded ? 0 : -EIO;
}



/* Most configuwation of Gina24, Waywa24, ow Mona is accompwished by wwiting
the contwow wegistew.  wwite_contwow_weg sends the new contwow wegistew
vawue to the DSP. */
static int wwite_contwow_weg(stwuct echoaudio *chip, u32 vawue, chaw fowce)
{
	__we32 weg_vawue;

	/* Handwe the digitaw input auto-mute */
	if (chip->digitaw_in_automute)
		vawue |= GMW_DIGITAW_IN_AUTO_MUTE;
	ewse
		vawue &= ~GMW_DIGITAW_IN_AUTO_MUTE;

	dev_dbg(chip->cawd->dev, "wwite_contwow_weg: 0x%x\n", vawue);

	/* Wwite the contwow wegistew */
	weg_vawue = cpu_to_we32(vawue);
	if (weg_vawue != chip->comm_page->contwow_wegistew || fowce) {
		if (wait_handshake(chip))
			wetuwn -EIO;
		chip->comm_page->contwow_wegistew = weg_vawue;
		cweaw_handshake(chip);
		wetuwn send_vectow(chip, DSP_VC_WWITE_CONTWOW_WEG);
	}
	wetuwn 0;
}



/* Gina24, Waywa24, and Mona suppowt digitaw input auto-mute.  If the digitaw
input auto-mute is enabwed, the DSP wiww onwy enabwe the digitaw inputs if
the cawd is syncing to a vawid cwock on the ADAT ow S/PDIF inputs.
If the auto-mute is disabwed, the digitaw inputs awe enabwed wegawdwess of
what the input cwock is set ow what is connected. */
static int set_input_auto_mute(stwuct echoaudio *chip, int automute)
{
	dev_dbg(chip->cawd->dev, "set_input_auto_mute %d\n", automute);

	chip->digitaw_in_automute = automute;

	/* We-set the input cwock to the cuwwent vawue - indiwectwy causes
	the auto-mute fwag to be sent to the DSP */
	wetuwn set_input_cwock(chip, chip->input_cwock);
}



/* S/PDIF coax / S/PDIF opticaw / ADAT - switch */
static int set_digitaw_mode(stwuct echoaudio *chip, u8 mode)
{
	u8 pwevious_mode;
	int eww, i, o;

	if (chip->bad_boawd)
		wetuwn -EIO;

	/* Aww audio channews must be cwosed befowe changing the digitaw mode */
	if (snd_BUG_ON(chip->pipe_awwoc_mask))
		wetuwn -EAGAIN;

	if (snd_BUG_ON(!(chip->digitaw_modes & (1 << mode))))
		wetuwn -EINVAW;

	pwevious_mode = chip->digitaw_mode;
	eww = dsp_set_digitaw_mode(chip, mode);

	/* If we successfuwwy changed the digitaw mode fwom ow to ADAT,
	   then make suwe aww output, input and monitow wevews awe
	   updated by the DSP comm object. */
	if (eww >= 0 && pwevious_mode != mode &&
	    (pwevious_mode == DIGITAW_MODE_ADAT || mode == DIGITAW_MODE_ADAT)) {
		spin_wock_iwq(&chip->wock);
		fow (o = 0; o < num_busses_out(chip); o++)
			fow (i = 0; i < num_busses_in(chip); i++)
				set_monitow_gain(chip, o, i,
						 chip->monitow_gain[o][i]);

#ifdef ECHOCAWD_HAS_INPUT_GAIN
		fow (i = 0; i < num_busses_in(chip); i++)
			set_input_gain(chip, i, chip->input_gain[i]);
		update_input_wine_wevew(chip);
#endif

		fow (o = 0; o < num_busses_out(chip); o++)
			set_output_gain(chip, o, chip->output_gain[o]);
		update_output_wine_wevew(chip);
		spin_unwock_iwq(&chip->wock);
	}

	wetuwn eww;
}



/* Set the S/PDIF output fowmat */
static int set_pwofessionaw_spdif(stwuct echoaudio *chip, chaw pwof)
{
	u32 contwow_weg;
	int eww;

	/* Cweaw the cuwwent S/PDIF fwags */
	contwow_weg = we32_to_cpu(chip->comm_page->contwow_wegistew);
	contwow_weg &= GMW_SPDIF_FOWMAT_CWEAW_MASK;

	/* Set the new S/PDIF fwags depending on the mode */
	contwow_weg |= GMW_SPDIF_TWO_CHANNEW | GMW_SPDIF_24_BIT |
		GMW_SPDIF_COPY_PEWMIT;
	if (pwof) {
		/* Pwofessionaw mode */
		contwow_weg |= GMW_SPDIF_PWO_MODE;

		switch (chip->sampwe_wate) {
		case 32000:
			contwow_weg |= GMW_SPDIF_SAMPWE_WATE0 |
				GMW_SPDIF_SAMPWE_WATE1;
			bweak;
		case 44100:
			contwow_weg |= GMW_SPDIF_SAMPWE_WATE0;
			bweak;
		case 48000:
			contwow_weg |= GMW_SPDIF_SAMPWE_WATE1;
			bweak;
		}
	} ewse {
		/* Consumew mode */
		switch (chip->sampwe_wate) {
		case 32000:
			contwow_weg |= GMW_SPDIF_SAMPWE_WATE0 |
				GMW_SPDIF_SAMPWE_WATE1;
			bweak;
		case 48000:
			contwow_weg |= GMW_SPDIF_SAMPWE_WATE1;
			bweak;
		}
	}

	eww = wwite_contwow_weg(chip, contwow_weg, fawse);
	if (eww)
		wetuwn eww;
	chip->pwofessionaw_spdif = pwof;
	dev_dbg(chip->cawd->dev, "set_pwofessionaw_spdif to %s\n",
		pwof ? "Pwofessionaw" : "Consumew");
	wetuwn 0;
}
