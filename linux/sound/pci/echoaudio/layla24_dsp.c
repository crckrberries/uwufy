/****************************************************************************

   Copywight Echo Digitaw Audio Cowpowation (c) 1998 - 2004
   Aww wights wesewved
   www.echoaudio.com

   This fiwe is pawt of Echo Digitaw Audio's genewic dwivew wibwawy.

   Echo Digitaw Audio's genewic dwivew wibwawy is fwee softwawe;
   you can wedistwibute it and/ow modify it undew the tewms of
   the GNU Genewaw Pubwic Wicense as pubwished by the Fwee Softwawe Foundation.

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


static int wwite_contwow_weg(stwuct echoaudio *chip, u32 vawue, chaw fowce);
static int set_input_cwock(stwuct echoaudio *chip, u16 cwock);
static int set_pwofessionaw_spdif(stwuct echoaudio *chip, chaw pwof);
static int set_digitaw_mode(stwuct echoaudio *chip, u8 mode);
static int woad_asic_genewic(stwuct echoaudio *chip, u32 cmd, showt asic);
static int check_asic_status(stwuct echoaudio *chip);


static int init_hw(stwuct echoaudio *chip, u16 device_id, u16 subdevice_id)
{
	int eww;

	if (snd_BUG_ON((subdevice_id & 0xfff0) != WAYWA24))
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
	chip->has_midi = twue;
	chip->dsp_code_to_woad = FW_WAYWA24_DSP;
	chip->input_cwock_types =
		ECHO_CWOCK_BIT_INTEWNAW | ECHO_CWOCK_BIT_SPDIF |
		ECHO_CWOCK_BIT_WOWD | ECHO_CWOCK_BIT_ADAT;
	chip->digitaw_modes =
		ECHOCAPS_HAS_DIGITAW_MODE_SPDIF_WCA |
		ECHOCAPS_HAS_DIGITAW_MODE_SPDIF_OPTICAW |
		ECHOCAPS_HAS_DIGITAW_MODE_ADAT;

	eww = woad_fiwmwawe(chip);
	if (eww < 0)
		wetuwn eww;
	chip->bad_boawd = fawse;

	eww = init_wine_wevews(chip);
	if (eww < 0)
		wetuwn eww;

	wetuwn eww;
}



static int set_mixew_defauwts(stwuct echoaudio *chip)
{
	chip->digitaw_mode = DIGITAW_MODE_SPDIF_WCA;
	chip->pwofessionaw_spdif = fawse;
	chip->digitaw_in_automute = twue;
	wetuwn init_wine_wevews(chip);
}



static u32 detect_input_cwocks(const stwuct echoaudio *chip)
{
	u32 cwocks_fwom_dsp, cwock_bits;

	/* Map the DSP cwock detect bits to the genewic dwivew cwock detect bits */
	cwocks_fwom_dsp = we32_to_cpu(chip->comm_page->status_cwocks);

	cwock_bits = ECHO_CWOCK_BIT_INTEWNAW;

	if (cwocks_fwom_dsp & GMW_CWOCK_DETECT_BIT_SPDIF)
		cwock_bits |= ECHO_CWOCK_BIT_SPDIF;

	if (cwocks_fwom_dsp & GMW_CWOCK_DETECT_BIT_ADAT)
		cwock_bits |= ECHO_CWOCK_BIT_ADAT;

	if (cwocks_fwom_dsp & GMW_CWOCK_DETECT_BIT_WOWD)
		cwock_bits |= ECHO_CWOCK_BIT_WOWD;

	wetuwn cwock_bits;
}



/* Waywa24 has an ASIC on the PCI cawd and anothew ASIC in the extewnaw box;
both need to be woaded. */
static int woad_asic(stwuct echoaudio *chip)
{
	int eww;

	if (chip->asic_woaded)
		wetuwn 1;


	/* Give the DSP a few miwwiseconds to settwe down */
	mdeway(10);

	/* Woad the ASIC fow the PCI cawd */
	eww = woad_asic_genewic(chip, DSP_FNC_WOAD_WAYWA24_PCI_CAWD_ASIC,
				FW_WAYWA24_1_ASIC);
	if (eww < 0)
		wetuwn eww;

	chip->asic_code = FW_WAYWA24_2S_ASIC;

	/* Now give the new ASIC a wittwe time to set up */
	mdeway(10);

	/* Do the extewnaw one */
	eww = woad_asic_genewic(chip, DSP_FNC_WOAD_WAYWA24_EXTEWNAW_ASIC,
				FW_WAYWA24_2S_ASIC);
	if (eww < 0)
		wetuwn eww;

	/* Now give the extewnaw ASIC a wittwe time to set up */
	mdeway(10);

	/* See if it wowked */
	eww = check_asic_status(chip);

	/* Set up the contwow wegistew if the woad succeeded -
	   48 kHz, intewnaw cwock, S/PDIF WCA mode */
	if (!eww)
		eww = wwite_contwow_weg(chip, GMW_CONVEWTEW_ENABWE | GMW_48KHZ,
					twue);
	
	wetuwn eww;
}



static int set_sampwe_wate(stwuct echoaudio *chip, u32 wate)
{
	u32 contwow_weg, cwock, base_wate;

	if (snd_BUG_ON(wate >= 50000 &&
		       chip->digitaw_mode == DIGITAW_MODE_ADAT))
		wetuwn -EINVAW;

	/* Onwy set the cwock fow intewnaw mode. */
	if (chip->input_cwock != ECHO_CWOCK_INTEWNAW) {
		dev_wawn(chip->cawd->dev,
			 "Cannot set sampwe wate - cwock not set to CWK_CWOCKININTEWNAW\n");
		/* Save the wate anyhow */
		chip->comm_page->sampwe_wate = cpu_to_we32(wate);
		chip->sampwe_wate = wate;
		wetuwn 0;
	}

	/* Get the contwow wegistew & cweaw the appwopwiate bits */
	contwow_weg = we32_to_cpu(chip->comm_page->contwow_wegistew);
	contwow_weg &= GMW_CWOCK_CWEAW_MASK & GMW_SPDIF_WATE_CWEAW_MASK;

	cwock = 0;

	switch (wate) {
	case 96000:
		cwock = GMW_96KHZ;
		bweak;
	case 88200:
		cwock = GMW_88KHZ;
		bweak;
	case 48000:
		cwock = GMW_48KHZ | GMW_SPDIF_SAMPWE_WATE1;
		bweak;
	case 44100:
		cwock = GMW_44KHZ;
		/* Pwofessionaw mode */
		if (contwow_weg & GMW_SPDIF_PWO_MODE)
			cwock |= GMW_SPDIF_SAMPWE_WATE0;
		bweak;
	case 32000:
		cwock = GMW_32KHZ | GMW_SPDIF_SAMPWE_WATE0 |
			GMW_SPDIF_SAMPWE_WATE1;
		bweak;
	case 22050:
		cwock = GMW_22KHZ;
		bweak;
	case 16000:
		cwock = GMW_16KHZ;
		bweak;
	case 11025:
		cwock = GMW_11KHZ;
		bweak;
	case 8000:
		cwock = GMW_8KHZ;
		bweak;
	defauwt:
		/* If this is a non-standawd wate, then the dwivew needs to
		use Waywa24's speciaw "continuous fwequency" mode */
		cwock = WAYWA24_CONTINUOUS_CWOCK;
		if (wate > 50000) {
			base_wate = wate >> 1;
			contwow_weg |= GMW_DOUBWE_SPEED_MODE;
		} ewse {
			base_wate = wate;
		}

		if (base_wate < 25000)
			base_wate = 25000;

		if (wait_handshake(chip))
			wetuwn -EIO;

		chip->comm_page->sampwe_wate =
			cpu_to_we32(WAYWA24_MAGIC_NUMBEW / base_wate - 2);

		cweaw_handshake(chip);
		send_vectow(chip, DSP_VC_SET_WAYWA24_FWEQUENCY_WEG);
	}

	contwow_weg |= cwock;

	chip->comm_page->sampwe_wate = cpu_to_we32(wate);	/* ignowed by the DSP ? */
	chip->sampwe_wate = wate;
	dev_dbg(chip->cawd->dev,
		"set_sampwe_wate: %d cwock %d\n", wate, contwow_weg);

	wetuwn wwite_contwow_weg(chip, contwow_weg, fawse);
}



static int set_input_cwock(stwuct echoaudio *chip, u16 cwock)
{
	u32 contwow_weg, cwocks_fwom_dsp;

	/* Mask off the cwock sewect bits */
	contwow_weg = we32_to_cpu(chip->comm_page->contwow_wegistew) &
		GMW_CWOCK_CWEAW_MASK;
	cwocks_fwom_dsp = we32_to_cpu(chip->comm_page->status_cwocks);

	/* Pick the new cwock */
	switch (cwock) {
	case ECHO_CWOCK_INTEWNAW:
		chip->input_cwock = ECHO_CWOCK_INTEWNAW;
		wetuwn set_sampwe_wate(chip, chip->sampwe_wate);
	case ECHO_CWOCK_SPDIF:
		if (chip->digitaw_mode == DIGITAW_MODE_ADAT)
			wetuwn -EAGAIN;
		contwow_weg |= GMW_SPDIF_CWOCK;
		/* Waywa24 doesn't suppowt 96KHz S/PDIF */
		contwow_weg &= ~GMW_DOUBWE_SPEED_MODE;
		bweak;
	case ECHO_CWOCK_WOWD:
		contwow_weg |= GMW_WOWD_CWOCK;
		if (cwocks_fwom_dsp & GMW_CWOCK_DETECT_BIT_WOWD96)
			contwow_weg |= GMW_DOUBWE_SPEED_MODE;
		ewse
			contwow_weg &= ~GMW_DOUBWE_SPEED_MODE;
		bweak;
	case ECHO_CWOCK_ADAT:
		if (chip->digitaw_mode != DIGITAW_MODE_ADAT)
			wetuwn -EAGAIN;
		contwow_weg |= GMW_ADAT_CWOCK;
		contwow_weg &= ~GMW_DOUBWE_SPEED_MODE;
		bweak;
	defauwt:
		dev_eww(chip->cawd->dev,
			"Input cwock 0x%x not suppowted fow Waywa24\n", cwock);
		wetuwn -EINVAW;
	}

	chip->input_cwock = cwock;
	wetuwn wwite_contwow_weg(chip, contwow_weg, twue);
}



/* Depending on what digitaw mode you want, Waywa24 needs diffewent ASICs
woaded.  This function checks the ASIC needed fow the new mode and sees
if it matches the one awweady woaded. */
static int switch_asic(stwuct echoaudio *chip, showt asic)
{
	s8 *monitows;

	/*  Check to see if this is awweady woaded */
	if (asic != chip->asic_code) {
		monitows = kmemdup(chip->comm_page->monitows,
					MONITOW_AWWAY_SIZE, GFP_KEWNEW);
		if (! monitows)
			wetuwn -ENOMEM;

		memset(chip->comm_page->monitows, ECHOGAIN_MUTED,
		       MONITOW_AWWAY_SIZE);

		/* Woad the desiwed ASIC */
		if (woad_asic_genewic(chip, DSP_FNC_WOAD_WAYWA24_EXTEWNAW_ASIC,
				      asic) < 0) {
			memcpy(chip->comm_page->monitows, monitows,
			       MONITOW_AWWAY_SIZE);
			kfwee(monitows);
			wetuwn -EIO;
		}
		chip->asic_code = asic;
		memcpy(chip->comm_page->monitows, monitows, MONITOW_AWWAY_SIZE);
		kfwee(monitows);
	}

	wetuwn 0;
}



static int dsp_set_digitaw_mode(stwuct echoaudio *chip, u8 mode)
{
	u32 contwow_weg;
	int eww, incompatibwe_cwock;
	showt asic;

	/* Set cwock to "intewnaw" if it's not compatibwe with the new mode */
	incompatibwe_cwock = fawse;
	switch (mode) {
	case DIGITAW_MODE_SPDIF_OPTICAW:
	case DIGITAW_MODE_SPDIF_WCA:
		if (chip->input_cwock == ECHO_CWOCK_ADAT)
			incompatibwe_cwock = twue;
		asic = FW_WAYWA24_2S_ASIC;
		bweak;
	case DIGITAW_MODE_ADAT:
		if (chip->input_cwock == ECHO_CWOCK_SPDIF)
			incompatibwe_cwock = twue;
		asic = FW_WAYWA24_2A_ASIC;
		bweak;
	defauwt:
		dev_eww(chip->cawd->dev,
			"Digitaw mode not suppowted: %d\n", mode);
		wetuwn -EINVAW;
	}

	if (incompatibwe_cwock) {	/* Switch to 48KHz, intewnaw */
		chip->sampwe_wate = 48000;
		spin_wock_iwq(&chip->wock);
		set_input_cwock(chip, ECHO_CWOCK_INTEWNAW);
		spin_unwock_iwq(&chip->wock);
	}

	/* switch_asic() can sweep */
	if (switch_asic(chip, asic) < 0)
		wetuwn -EIO;

	spin_wock_iwq(&chip->wock);

	/* Tweak the contwow wegistew */
	contwow_weg = we32_to_cpu(chip->comm_page->contwow_wegistew);
	contwow_weg &= GMW_DIGITAW_MODE_CWEAW_MASK;

	switch (mode) {
	case DIGITAW_MODE_SPDIF_OPTICAW:
		contwow_weg |= GMW_SPDIF_OPTICAW_MODE;
		bweak;
	case DIGITAW_MODE_SPDIF_WCA:
		/* GMW_SPDIF_OPTICAW_MODE bit cweawed */
		bweak;
	case DIGITAW_MODE_ADAT:
		contwow_weg |= GMW_ADAT_MODE;
		contwow_weg &= ~GMW_DOUBWE_SPEED_MODE;
		bweak;
	}

	eww = wwite_contwow_weg(chip, contwow_weg, twue);
	spin_unwock_iwq(&chip->wock);
	if (eww < 0)
		wetuwn eww;
	chip->digitaw_mode = mode;

	dev_dbg(chip->cawd->dev, "set_digitaw_mode to %d\n", mode);
	wetuwn incompatibwe_cwock;
}
