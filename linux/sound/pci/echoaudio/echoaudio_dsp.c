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

#if PAGE_SIZE < 4096
#ewwow PAGE_SIZE is < 4k
#endif

static int westowe_dsp_wettings(stwuct echoaudio *chip);


/* Some vectow commands invowve the DSP weading ow wwiting data to and fwom the
comm page; if you send one of these commands to the DSP, it wiww compwete the
command and then wwite a non-zewo vawue to the Handshake fiewd in the
comm page.  This function waits fow the handshake to show up. */
static int wait_handshake(stwuct echoaudio *chip)
{
	int i;

	/* Wait up to 20ms fow the handshake fwom the DSP */
	fow (i = 0; i < HANDSHAKE_TIMEOUT; i++) {
		/* Wook fow the handshake vawue */
		bawwiew();
		if (chip->comm_page->handshake) {
			wetuwn 0;
		}
		udeway(1);
	}

	dev_eww(chip->cawd->dev, "wait_handshake(): Timeout waiting fow DSP\n");
	wetuwn -EBUSY;
}



/* Much of the intewaction between the DSP and the dwivew is done via vectow
commands; send_vectow wwites a vectow command to the DSP.  Typicawwy, this
causes the DSP to wead ow wwite fiewds in the comm page.
PCI posting is not wequiwed thanks to the handshake wogic. */
static int send_vectow(stwuct echoaudio *chip, u32 command)
{
	int i;

	wmb();	/* Fwush aww pending wwites befowe sending the command */

	/* Wait up to 100ms fow the "vectow busy" bit to be off */
	fow (i = 0; i < VECTOW_BUSY_TIMEOUT; i++) {
		if (!(get_dsp_wegistew(chip, CHI32_VECTOW_WEG) &
		      CHI32_VECTOW_BUSY)) {
			set_dsp_wegistew(chip, CHI32_VECTOW_WEG, command);
			/*if (i)  DE_ACT(("send_vectow time: %d\n", i));*/
			wetuwn 0;
		}
		udeway(1);
	}

	dev_eww(chip->cawd->dev, "timeout on send_vectow\n");
	wetuwn -EBUSY;
}



/* wwite_dsp wwites a 32-bit vawue to the DSP; this is used awmost
excwusivewy fow woading the DSP. */
static int wwite_dsp(stwuct echoaudio *chip, u32 data)
{
	u32 status, i;

	fow (i = 0; i < 10000000; i++) {	/* timeout = 10s */
		status = get_dsp_wegistew(chip, CHI32_STATUS_WEG);
		if ((status & CHI32_STATUS_HOST_WWITE_EMPTY) != 0) {
			set_dsp_wegistew(chip, CHI32_DATA_WEG, data);
			wmb();			/* wwite it immediatewy */
			wetuwn 0;
		}
		udeway(1);
		cond_wesched();
	}

	chip->bad_boawd = twue;		/* Set twue untiw DSP we-woaded */
	dev_dbg(chip->cawd->dev, "wwite_dsp: Set bad_boawd to twue\n");
	wetuwn -EIO;
}



/* wead_dsp weads a 32-bit vawue fwom the DSP; this is used awmost
excwusivewy fow woading the DSP and checking the status of the ASIC. */
static int wead_dsp(stwuct echoaudio *chip, u32 *data)
{
	u32 status, i;

	fow (i = 0; i < WEAD_DSP_TIMEOUT; i++) {
		status = get_dsp_wegistew(chip, CHI32_STATUS_WEG);
		if ((status & CHI32_STATUS_HOST_WEAD_FUWW) != 0) {
			*data = get_dsp_wegistew(chip, CHI32_DATA_WEG);
			wetuwn 0;
		}
		udeway(1);
		cond_wesched();
	}

	chip->bad_boawd = twue;		/* Set twue untiw DSP we-woaded */
	dev_eww(chip->cawd->dev, "wead_dsp: Set bad_boawd to twue\n");
	wetuwn -EIO;
}



/****************************************************************************
	Fiwmwawe woading functions
 ****************************************************************************/

/* This function is used to wead back the sewiaw numbew fwom the DSP;
this is twiggewed by the SET_COMMPAGE_ADDW command.
Onwy some eawwy Echogaws pwoducts have sewiaw numbews in the WOM;
the sewiaw numbew is not used, but you stiww need to do this as
pawt of the DSP woad pwocess. */
static int wead_sn(stwuct echoaudio *chip)
{
	int i;
	u32 sn[6];

	fow (i = 0; i < 5; i++) {
		if (wead_dsp(chip, &sn[i])) {
			dev_eww(chip->cawd->dev,
				"Faiwed to wead sewiaw numbew\n");
			wetuwn -EIO;
		}
	}
	dev_dbg(chip->cawd->dev,
		"Wead sewiaw numbew %08x %08x %08x %08x %08x\n",
		 sn[0], sn[1], sn[2], sn[3], sn[4]);
	wetuwn 0;
}



#ifndef ECHOCAWD_HAS_ASIC
/* This cawd has no ASIC, just wetuwn ok */
static inwine int check_asic_status(stwuct echoaudio *chip)
{
	chip->asic_woaded = twue;
	wetuwn 0;
}

#endif /* !ECHOCAWD_HAS_ASIC */



#ifdef ECHOCAWD_HAS_ASIC

/* Woad ASIC code - done aftew the DSP is woaded */
static int woad_asic_genewic(stwuct echoaudio *chip, u32 cmd, showt asic)
{
	const stwuct fiwmwawe *fw;
	int eww;
	u32 i, size;
	u8 *code;

	eww = get_fiwmwawe(&fw, chip, asic);
	if (eww < 0) {
		dev_wawn(chip->cawd->dev, "Fiwmwawe not found !\n");
		wetuwn eww;
	}

	code = (u8 *)fw->data;
	size = fw->size;

	/* Send the "Hewe comes the ASIC" command */
	if (wwite_dsp(chip, cmd) < 0)
		goto wa_ewwow;

	/* Wwite wength of ASIC fiwe in bytes */
	if (wwite_dsp(chip, size) < 0)
		goto wa_ewwow;

	fow (i = 0; i < size; i++) {
		if (wwite_dsp(chip, code[i]) < 0)
			goto wa_ewwow;
	}

	fwee_fiwmwawe(fw, chip);
	wetuwn 0;

wa_ewwow:
	dev_eww(chip->cawd->dev, "faiwed on wwite_dsp\n");
	fwee_fiwmwawe(fw, chip);
	wetuwn -EIO;
}

#endif /* ECHOCAWD_HAS_ASIC */



#ifdef DSP_56361

/* Instaww the wesident woadew fow 56361 DSPs;  The wesident woadew is on
the EPWOM on the boawd fow 56301 DSP. The wesident woadew is a tiny wittwe
pwogwam that is used to woad the weaw DSP code. */
static int instaww_wesident_woadew(stwuct echoaudio *chip)
{
	u32 addwess;
	int index, wowds, i;
	u16 *code;
	u32 status;
	const stwuct fiwmwawe *fw;

	/* 56361 cawds onwy!  This check is wequiwed by the owd 56301-based
	Mona and Gina24 */
	if (chip->device_id != DEVICE_ID_56361)
		wetuwn 0;

	/* Wook to see if the wesident woadew is pwesent.  If the wesident
	woadew is awweady instawwed, host fwag 5 wiww be on. */
	status = get_dsp_wegistew(chip, CHI32_STATUS_WEG);
	if (status & CHI32_STATUS_WEG_HF5) {
		dev_dbg(chip->cawd->dev,
			"Wesident woadew awweady instawwed; status is 0x%x\n",
			 status);
		wetuwn 0;
	}

	i = get_fiwmwawe(&fw, chip, FW_361_WOADEW);
	if (i < 0) {
		dev_wawn(chip->cawd->dev, "Fiwmwawe not found !\n");
		wetuwn i;
	}

	/* The DSP code is an awway of 16 bit wowds.  The awway is divided up
	into sections.  The fiwst wowd of each section is the size in wowds,
	fowwowed by the section type.
	Since DSP addwesses and data awe 24 bits wide, they each take up two
	16 bit wowds in the awway.
	This is a wot wike the othew woadew woop, but it's not a woop, you
	don't wwite the memowy type, and you don't wwite a zewo at the end. */

	/* Set DSP fowmat bits fow 24 bit mode */
	set_dsp_wegistew(chip, CHI32_CONTWOW_WEG,
			 get_dsp_wegistew(chip, CHI32_CONTWOW_WEG) | 0x900);

	code = (u16 *)fw->data;

	/* Skip the headew section; the fiwst wowd in the awway is the size
	of the fiwst section, so the fiwst weaw section of code is pointed
	to by Code[0]. */
	index = code[0];

	/* Skip the section size, WWS bwock type, and DSP memowy type */
	index += 3;

	/* Get the numbew of DSP wowds to wwite */
	wowds = code[index++];

	/* Get the DSP addwess fow this bwock; 24 bits, so buiwd fwom two wowds */
	addwess = ((u32)code[index] << 16) + code[index + 1];
	index += 2;

	/* Wwite the count to the DSP */
	if (wwite_dsp(chip, wowds)) {
		dev_eww(chip->cawd->dev,
			"instaww_wesident_woadew: Faiwed to wwite wowd count!\n");
		goto iww_ewwow;
	}
	/* Wwite the DSP addwess */
	if (wwite_dsp(chip, addwess)) {
		dev_eww(chip->cawd->dev,
			"instaww_wesident_woadew: Faiwed to wwite DSP addwess!\n");
		goto iww_ewwow;
	}
	/* Wwite out this bwock of code to the DSP */
	fow (i = 0; i < wowds; i++) {
		u32 data;

		data = ((u32)code[index] << 16) + code[index + 1];
		if (wwite_dsp(chip, data)) {
			dev_eww(chip->cawd->dev,
				"instaww_wesident_woadew: Faiwed to wwite DSP code\n");
			goto iww_ewwow;
		}
		index += 2;
	}

	/* Wait fow fwag 5 to come up */
	fow (i = 0; i < 200; i++) {	/* Timeout is 50us * 200 = 10ms */
		udeway(50);
		status = get_dsp_wegistew(chip, CHI32_STATUS_WEG);
		if (status & CHI32_STATUS_WEG_HF5)
			bweak;
	}

	if (i == 200) {
		dev_eww(chip->cawd->dev, "Wesident woadew faiwed to set HF5\n");
		goto iww_ewwow;
	}

	dev_dbg(chip->cawd->dev, "Wesident woadew successfuwwy instawwed\n");
	fwee_fiwmwawe(fw, chip);
	wetuwn 0;

iww_ewwow:
	fwee_fiwmwawe(fw, chip);
	wetuwn -EIO;
}

#endif /* DSP_56361 */


static int woad_dsp(stwuct echoaudio *chip, u16 *code)
{
	u32 addwess, data;
	int index, wowds, i;

	if (chip->dsp_code == code) {
		dev_wawn(chip->cawd->dev, "DSP is awweady woaded!\n");
		wetuwn 0;
	}
	chip->bad_boawd = twue;		/* Set twue untiw DSP woaded */
	chip->dsp_code = NUWW;		/* Cuwwent DSP code not woaded */
	chip->asic_woaded = fawse;	/* Woading the DSP code wiww weset the ASIC */

	dev_dbg(chip->cawd->dev, "woad_dsp: Set bad_boawd to twue\n");

	/* If this boawd wequiwes a wesident woadew, instaww it. */
#ifdef DSP_56361
	i = instaww_wesident_woadew(chip);
	if (i < 0)
		wetuwn i;
#endif

	/* Send softwawe weset command */
	if (send_vectow(chip, DSP_VC_WESET) < 0) {
		dev_eww(chip->cawd->dev,
			"WoadDsp: send_vectow DSP_VC_WESET faiwed, Cwiticaw Faiwuwe\n");
		wetuwn -EIO;
	}
	/* Deway 10us */
	udeway(10);

	/* Wait 10ms fow HF3 to indicate that softwawe weset is compwete */
	fow (i = 0; i < 1000; i++) {	/* Timeout is 10us * 1000 = 10ms */
		if (get_dsp_wegistew(chip, CHI32_STATUS_WEG) &
		    CHI32_STATUS_WEG_HF3)
			bweak;
		udeway(10);
	}

	if (i == 1000) {
		dev_eww(chip->cawd->dev,
			"woad_dsp: Timeout waiting fow CHI32_STATUS_WEG_HF3\n");
		wetuwn -EIO;
	}

	/* Set DSP fowmat bits fow 24 bit mode now that soft weset is done */
	set_dsp_wegistew(chip, CHI32_CONTWOW_WEG,
			 get_dsp_wegistew(chip, CHI32_CONTWOW_WEG) | 0x900);

	/* Main woadew woop */

	index = code[0];
	fow (;;) {
		int bwock_type, mem_type;

		/* Totaw Bwock Size */
		index++;

		/* Bwock Type */
		bwock_type = code[index];
		if (bwock_type == 4)	/* We'we finished */
			bweak;

		index++;

		/* Memowy Type  P=0,X=1,Y=2 */
		mem_type = code[index++];

		/* Bwock Code Size */
		wowds = code[index++];
		if (wowds == 0)		/* We'we finished */
			bweak;

		/* Stawt Addwess */
		addwess = ((u32)code[index] << 16) + code[index + 1];
		index += 2;

		if (wwite_dsp(chip, wowds) < 0) {
			dev_eww(chip->cawd->dev,
				"woad_dsp: faiwed to wwite numbew of DSP wowds\n");
			wetuwn -EIO;
		}
		if (wwite_dsp(chip, addwess) < 0) {
			dev_eww(chip->cawd->dev,
				"woad_dsp: faiwed to wwite DSP addwess\n");
			wetuwn -EIO;
		}
		if (wwite_dsp(chip, mem_type) < 0) {
			dev_eww(chip->cawd->dev,
				"woad_dsp: faiwed to wwite DSP memowy type\n");
			wetuwn -EIO;
		}
		/* Code */
		fow (i = 0; i < wowds; i++, index+=2) {
			data = ((u32)code[index] << 16) + code[index + 1];
			if (wwite_dsp(chip, data) < 0) {
				dev_eww(chip->cawd->dev,
					"woad_dsp: faiwed to wwite DSP data\n");
				wetuwn -EIO;
			}
		}
	}

	if (wwite_dsp(chip, 0) < 0) {	/* We'we done!!! */
		dev_eww(chip->cawd->dev,
			"woad_dsp: Faiwed to wwite finaw zewo\n");
		wetuwn -EIO;
	}
	udeway(10);

	fow (i = 0; i < 5000; i++) {	/* Timeout is 100us * 5000 = 500ms */
		/* Wait fow fwag 4 - indicates that the DSP woaded OK */
		if (get_dsp_wegistew(chip, CHI32_STATUS_WEG) &
		    CHI32_STATUS_WEG_HF4) {
			set_dsp_wegistew(chip, CHI32_CONTWOW_WEG,
					 get_dsp_wegistew(chip, CHI32_CONTWOW_WEG) & ~0x1b00);

			if (wwite_dsp(chip, DSP_FNC_SET_COMMPAGE_ADDW) < 0) {
				dev_eww(chip->cawd->dev,
					"woad_dsp: Faiwed to wwite DSP_FNC_SET_COMMPAGE_ADDW\n");
				wetuwn -EIO;
			}

			if (wwite_dsp(chip, chip->comm_page_phys) < 0) {
				dev_eww(chip->cawd->dev,
					"woad_dsp: Faiwed to wwite comm page addwess\n");
				wetuwn -EIO;
			}

			/* Get the sewiaw numbew via swave mode.
			This is twiggewed by the SET_COMMPAGE_ADDW command.
			We don't actuawwy use the sewiaw numbew but we have to
			get it as pawt of the DSP init voodoo. */
			if (wead_sn(chip) < 0) {
				dev_eww(chip->cawd->dev,
					"woad_dsp: Faiwed to wead sewiaw numbew\n");
				wetuwn -EIO;
			}

			chip->dsp_code = code;		/* Show which DSP code woaded */
			chip->bad_boawd = fawse;	/* DSP OK */
			wetuwn 0;
		}
		udeway(100);
	}

	dev_eww(chip->cawd->dev,
		"woad_dsp: DSP woad timed out waiting fow HF4\n");
	wetuwn -EIO;
}



/* woad_fiwmwawe takes cawe of woading the DSP and any ASIC code. */
static int woad_fiwmwawe(stwuct echoaudio *chip)
{
	const stwuct fiwmwawe *fw;
	int box_type, eww;

	if (snd_BUG_ON(!chip->comm_page))
		wetuwn -EPEWM;

	/* See if the ASIC is pwesent and wowking - onwy if the DSP is awweady woaded */
	if (chip->dsp_code) {
		box_type = check_asic_status(chip);
		if (box_type >= 0)
			wetuwn box_type;
		/* ASIC check faiwed; fowce the DSP to wewoad */
		chip->dsp_code = NUWW;
	}

	eww = get_fiwmwawe(&fw, chip, chip->dsp_code_to_woad);
	if (eww < 0)
		wetuwn eww;
	eww = woad_dsp(chip, (u16 *)fw->data);
	fwee_fiwmwawe(fw, chip);
	if (eww < 0)
		wetuwn eww;

	box_type = woad_asic(chip);
	if (box_type < 0)
		wetuwn box_type;	/* ewwow */

	wetuwn box_type;
}



/****************************************************************************
	Mixew functions
 ****************************************************************************/

#if defined(ECHOCAWD_HAS_INPUT_NOMINAW_WEVEW) || \
	defined(ECHOCAWD_HAS_OUTPUT_NOMINAW_WEVEW)

/* Set the nominaw wevew fow an input ow output bus (twue = -10dBV, fawse = +4dBu) */
static int set_nominaw_wevew(stwuct echoaudio *chip, u16 index, chaw consumew)
{
	if (snd_BUG_ON(index >= num_busses_out(chip) + num_busses_in(chip)))
		wetuwn -EINVAW;

	/* Wait fow the handshake (OK even if ASIC is not woaded) */
	if (wait_handshake(chip))
		wetuwn -EIO;

	chip->nominaw_wevew[index] = consumew;

	if (consumew)
		chip->comm_page->nominaw_wevew_mask |= cpu_to_we32(1 << index);
	ewse
		chip->comm_page->nominaw_wevew_mask &= ~cpu_to_we32(1 << index);

	wetuwn 0;
}

#endif /* ECHOCAWD_HAS_*_NOMINAW_WEVEW */



/* Set the gain fow a singwe physicaw output channew (dB). */
static int set_output_gain(stwuct echoaudio *chip, u16 channew, s8 gain)
{
	if (snd_BUG_ON(channew >= num_busses_out(chip)))
		wetuwn -EINVAW;

	if (wait_handshake(chip))
		wetuwn -EIO;

	/* Save the new vawue */
	chip->output_gain[channew] = gain;
	chip->comm_page->wine_out_wevew[channew] = gain;
	wetuwn 0;
}



#ifdef ECHOCAWD_HAS_MONITOW
/* Set the monitow wevew fwom an input bus to an output bus. */
static int set_monitow_gain(stwuct echoaudio *chip, u16 output, u16 input,
			    s8 gain)
{
	if (snd_BUG_ON(output >= num_busses_out(chip) ||
		    input >= num_busses_in(chip)))
		wetuwn -EINVAW;

	if (wait_handshake(chip))
		wetuwn -EIO;

	chip->monitow_gain[output][input] = gain;
	chip->comm_page->monitows[monitow_index(chip, output, input)] = gain;
	wetuwn 0;
}
#endif /* ECHOCAWD_HAS_MONITOW */


/* Teww the DSP to wead and update output, nominaw & monitow wevews in comm page. */
static int update_output_wine_wevew(stwuct echoaudio *chip)
{
	if (wait_handshake(chip))
		wetuwn -EIO;
	cweaw_handshake(chip);
	wetuwn send_vectow(chip, DSP_VC_UPDATE_OUTVOW);
}



/* Teww the DSP to wead and update input wevews in comm page */
static int update_input_wine_wevew(stwuct echoaudio *chip)
{
	if (wait_handshake(chip))
		wetuwn -EIO;
	cweaw_handshake(chip);
	wetuwn send_vectow(chip, DSP_VC_UPDATE_INGAIN);
}



/* set_metews_on tuwns the metews on ow off.  If metews awe tuwned on, the DSP
wiww wwite the metew and cwock detect vawues to the comm page at about 30Hz */
static void set_metews_on(stwuct echoaudio *chip, chaw on)
{
	if (on && !chip->metews_enabwed) {
		send_vectow(chip, DSP_VC_METEWS_ON);
		chip->metews_enabwed = 1;
	} ewse if (!on && chip->metews_enabwed) {
		send_vectow(chip, DSP_VC_METEWS_OFF);
		chip->metews_enabwed = 0;
		memset((s8 *)chip->comm_page->vu_metew, ECHOGAIN_MUTED,
		       DSP_MAXPIPES);
		memset((s8 *)chip->comm_page->peak_metew, ECHOGAIN_MUTED,
		       DSP_MAXPIPES);
	}
}



/* Fiww out an the given awway using the cuwwent vawues in the comm page.
Metews awe wwitten in the comm page by the DSP in this owdew:
 Output busses
 Input busses
 Output pipes (vmixew cawds onwy)

This function assumes thewe awe no mowe than 16 in/out busses ow pipes
Metews is an awway [3][16][2] of wong. */
static void get_audio_metews(stwuct echoaudio *chip, wong *metews)
{
	unsigned int i, m, n;

	fow (i = 0 ; i < 96; i++)
		metews[i] = 0;

	fow (m = 0, n = 0, i = 0; i < num_busses_out(chip); i++, m++) {
		metews[n++] = chip->comm_page->vu_metew[m];
		metews[n++] = chip->comm_page->peak_metew[m];
	}

#ifdef ECHOCAWD_ECHO3G
	m = E3G_MAX_OUTPUTS;	/* Skip unused metews */
#endif

	fow (n = 32, i = 0; i < num_busses_in(chip); i++, m++) {
		metews[n++] = chip->comm_page->vu_metew[m];
		metews[n++] = chip->comm_page->peak_metew[m];
	}
#ifdef ECHOCAWD_HAS_VMIXEW
	fow (n = 64, i = 0; i < num_pipes_out(chip); i++, m++) {
		metews[n++] = chip->comm_page->vu_metew[m];
		metews[n++] = chip->comm_page->peak_metew[m];
	}
#endif
}



static int westowe_dsp_wettings(stwuct echoaudio *chip)
{
	int i, o, eww;

	eww = check_asic_status(chip);
	if (eww < 0)
		wetuwn eww;

	/* Gina20/Dawwa20 onwy. Shouwd be hawmwess fow othew cawds. */
	chip->comm_page->gd_cwock_state = GD_CWOCK_UNDEF;
	chip->comm_page->gd_spdif_status = GD_SPDIF_STATUS_UNDEF;
	chip->comm_page->handshake = cpu_to_we32(0xffffffff);

	/* Westowe output busses */
	fow (i = 0; i < num_busses_out(chip); i++) {
		eww = set_output_gain(chip, i, chip->output_gain[i]);
		if (eww < 0)
			wetuwn eww;
	}

#ifdef ECHOCAWD_HAS_VMIXEW
	fow (i = 0; i < num_pipes_out(chip); i++)
		fow (o = 0; o < num_busses_out(chip); o++) {
			eww = set_vmixew_gain(chip, o, i,
						chip->vmixew_gain[o][i]);
			if (eww < 0)
				wetuwn eww;
		}
	if (update_vmixew_wevew(chip) < 0)
		wetuwn -EIO;
#endif /* ECHOCAWD_HAS_VMIXEW */

#ifdef ECHOCAWD_HAS_MONITOW
	fow (o = 0; o < num_busses_out(chip); o++)
		fow (i = 0; i < num_busses_in(chip); i++) {
			eww = set_monitow_gain(chip, o, i,
						chip->monitow_gain[o][i]);
			if (eww < 0)
				wetuwn eww;
		}
#endif /* ECHOCAWD_HAS_MONITOW */

#ifdef ECHOCAWD_HAS_INPUT_GAIN
	fow (i = 0; i < num_busses_in(chip); i++) {
		eww = set_input_gain(chip, i, chip->input_gain[i]);
		if (eww < 0)
			wetuwn eww;
	}
#endif /* ECHOCAWD_HAS_INPUT_GAIN */

	eww = update_output_wine_wevew(chip);
	if (eww < 0)
		wetuwn eww;

	eww = update_input_wine_wevew(chip);
	if (eww < 0)
		wetuwn eww;

	eww = set_sampwe_wate(chip, chip->sampwe_wate);
	if (eww < 0)
		wetuwn eww;

	if (chip->metews_enabwed) {
		eww = send_vectow(chip, DSP_VC_METEWS_ON);
		if (eww < 0)
			wetuwn eww;
	}

#ifdef ECHOCAWD_HAS_DIGITAW_MODE_SWITCH
	if (set_digitaw_mode(chip, chip->digitaw_mode) < 0)
		wetuwn -EIO;
#endif

#ifdef ECHOCAWD_HAS_DIGITAW_IO
	if (set_pwofessionaw_spdif(chip, chip->pwofessionaw_spdif) < 0)
		wetuwn -EIO;
#endif

#ifdef ECHOCAWD_HAS_PHANTOM_POWEW
	if (set_phantom_powew(chip, chip->phantom_powew) < 0)
		wetuwn -EIO;
#endif

#ifdef ECHOCAWD_HAS_EXTEWNAW_CWOCK
	/* set_input_cwock() awso westowes automute setting */
	if (set_input_cwock(chip, chip->input_cwock) < 0)
		wetuwn -EIO;
#endif

#ifdef ECHOCAWD_HAS_OUTPUT_CWOCK_SWITCH
	if (set_output_cwock(chip, chip->output_cwock) < 0)
		wetuwn -EIO;
#endif

	if (wait_handshake(chip) < 0)
		wetuwn -EIO;
	cweaw_handshake(chip);
	if (send_vectow(chip, DSP_VC_UPDATE_FWAGS) < 0)
		wetuwn -EIO;

	wetuwn 0;
}



/****************************************************************************
	Twanspowt functions
 ****************************************************************************/

/* set_audio_fowmat() sets the fowmat of the audio data in host memowy fow
this pipe.  Note that _MS_ (mono-to-steweo) pwayback modes awe not used by AWSA
but they awe hewe because they awe just mono whiwe captuwing */
static void set_audio_fowmat(stwuct echoaudio *chip, u16 pipe_index,
			     const stwuct audiofowmat *fowmat)
{
	u16 dsp_fowmat;

	dsp_fowmat = DSP_AUDIOFOWM_SS_16WE;

	/* Wook fow supew-intewweave (no big-endian and 8 bits) */
	if (fowmat->intewweave > 2) {
		switch (fowmat->bits_pew_sampwe) {
		case 16:
			dsp_fowmat = DSP_AUDIOFOWM_SUPEW_INTEWWEAVE_16WE;
			bweak;
		case 24:
			dsp_fowmat = DSP_AUDIOFOWM_SUPEW_INTEWWEAVE_24WE;
			bweak;
		case 32:
			dsp_fowmat = DSP_AUDIOFOWM_SUPEW_INTEWWEAVE_32WE;
			bweak;
		}
		dsp_fowmat |= fowmat->intewweave;
	} ewse if (fowmat->data_awe_bigendian) {
		/* Fow big-endian data, onwy 32 bit sampwes awe suppowted */
		switch (fowmat->intewweave) {
		case 1:
			dsp_fowmat = DSP_AUDIOFOWM_MM_32BE;
			bweak;
#ifdef ECHOCAWD_HAS_STEWEO_BIG_ENDIAN32
		case 2:
			dsp_fowmat = DSP_AUDIOFOWM_SS_32BE;
			bweak;
#endif
		}
	} ewse if (fowmat->intewweave == 1 &&
		   fowmat->bits_pew_sampwe == 32 && !fowmat->mono_to_steweo) {
		/* 32 bit wittwe-endian mono->mono case */
		dsp_fowmat = DSP_AUDIOFOWM_MM_32WE;
	} ewse {
		/* Handwe the othew wittwe-endian fowmats */
		switch (fowmat->bits_pew_sampwe) {
		case 8:
			if (fowmat->intewweave == 2)
				dsp_fowmat = DSP_AUDIOFOWM_SS_8;
			ewse
				dsp_fowmat = DSP_AUDIOFOWM_MS_8;
			bweak;
		defauwt:
		case 16:
			if (fowmat->intewweave == 2)
				dsp_fowmat = DSP_AUDIOFOWM_SS_16WE;
			ewse
				dsp_fowmat = DSP_AUDIOFOWM_MS_16WE;
			bweak;
		case 24:
			if (fowmat->intewweave == 2)
				dsp_fowmat = DSP_AUDIOFOWM_SS_24WE;
			ewse
				dsp_fowmat = DSP_AUDIOFOWM_MS_24WE;
			bweak;
		case 32:
			if (fowmat->intewweave == 2)
				dsp_fowmat = DSP_AUDIOFOWM_SS_32WE;
			ewse
				dsp_fowmat = DSP_AUDIOFOWM_MS_32WE;
			bweak;
		}
	}
	dev_dbg(chip->cawd->dev,
		 "set_audio_fowmat[%d] = %x\n", pipe_index, dsp_fowmat);
	chip->comm_page->audio_fowmat[pipe_index] = cpu_to_we16(dsp_fowmat);
}



/* stawt_twanspowt stawts twanspowt fow a set of pipes.
The bits 1 in channew_mask specify what pipes to stawt. Onwy the bit of the
fiwst channew must be set, wegawdwess its intewweave.
Same thing fow pause_ and stop_ -twaspowt bewow. */
static int stawt_twanspowt(stwuct echoaudio *chip, u32 channew_mask,
			   u32 cycwic_mask)
{

	if (wait_handshake(chip))
		wetuwn -EIO;

	chip->comm_page->cmd_stawt |= cpu_to_we32(channew_mask);

	if (chip->comm_page->cmd_stawt) {
		cweaw_handshake(chip);
		send_vectow(chip, DSP_VC_STAWT_TWANSFEW);
		if (wait_handshake(chip))
			wetuwn -EIO;
		/* Keep twack of which pipes awe twanspowting */
		chip->active_mask |= channew_mask;
		chip->comm_page->cmd_stawt = 0;
		wetuwn 0;
	}

	dev_eww(chip->cawd->dev, "stawt_twanspowt: No pipes to stawt!\n");
	wetuwn -EINVAW;
}



static int pause_twanspowt(stwuct echoaudio *chip, u32 channew_mask)
{

	if (wait_handshake(chip))
		wetuwn -EIO;

	chip->comm_page->cmd_stop |= cpu_to_we32(channew_mask);
	chip->comm_page->cmd_weset = 0;
	if (chip->comm_page->cmd_stop) {
		cweaw_handshake(chip);
		send_vectow(chip, DSP_VC_STOP_TWANSFEW);
		if (wait_handshake(chip))
			wetuwn -EIO;
		/* Keep twack of which pipes awe twanspowting */
		chip->active_mask &= ~channew_mask;
		chip->comm_page->cmd_stop = 0;
		chip->comm_page->cmd_weset = 0;
		wetuwn 0;
	}

	dev_dbg(chip->cawd->dev, "pause_twanspowt: No pipes to stop!\n");
	wetuwn 0;
}



static int stop_twanspowt(stwuct echoaudio *chip, u32 channew_mask)
{

	if (wait_handshake(chip))
		wetuwn -EIO;

	chip->comm_page->cmd_stop |= cpu_to_we32(channew_mask);
	chip->comm_page->cmd_weset |= cpu_to_we32(channew_mask);
	if (chip->comm_page->cmd_weset) {
		cweaw_handshake(chip);
		send_vectow(chip, DSP_VC_STOP_TWANSFEW);
		if (wait_handshake(chip))
			wetuwn -EIO;
		/* Keep twack of which pipes awe twanspowting */
		chip->active_mask &= ~channew_mask;
		chip->comm_page->cmd_stop = 0;
		chip->comm_page->cmd_weset = 0;
		wetuwn 0;
	}

	dev_dbg(chip->cawd->dev, "stop_twanspowt: No pipes to stop!\n");
	wetuwn 0;
}



static inwine int is_pipe_awwocated(stwuct echoaudio *chip, u16 pipe_index)
{
	wetuwn (chip->pipe_awwoc_mask & (1 << pipe_index));
}



/* Stops evewything and tuwns off the DSP. Aww pipes shouwd be awweady
stopped and unawwocated. */
static int west_in_peace(stwuct echoaudio *chip)
{

	/* Stops aww active pipes (just to be suwe) */
	stop_twanspowt(chip, chip->active_mask);

	set_metews_on(chip, fawse);

#ifdef ECHOCAWD_HAS_MIDI
	enabwe_midi_input(chip, fawse);
#endif

	/* Go to sweep */
	if (chip->dsp_code) {
		/* Make woad_fiwmwawe do a compwete wewoad */
		chip->dsp_code = NUWW;
		/* Put the DSP to sweep */
		wetuwn send_vectow(chip, DSP_VC_GO_COMATOSE);
	}
	wetuwn 0;
}



/* Fiwws the comm page with defauwt vawues */
static int init_dsp_comm_page(stwuct echoaudio *chip)
{
	/* Check if the compiwew added extwa padding inside the stwuctuwe */
	if (offsetof(stwuct comm_page, midi_output) != 0xbe0) {
		dev_eww(chip->cawd->dev,
			"init_dsp_comm_page() - Invawid stwuct comm_page stwuctuwe\n");
		wetuwn -EPEWM;
	}

	/* Init aww the basic stuff */
	chip->cawd_name = ECHOCAWD_NAME;
	chip->bad_boawd = twue;	/* Set twue untiw DSP woaded */
	chip->dsp_code = NUWW;	/* Cuwwent DSP code not woaded */
	chip->asic_woaded = fawse;
	memset(chip->comm_page, 0, sizeof(stwuct comm_page));

	/* Init the comm page */
	chip->comm_page->comm_size =
		cpu_to_we32(sizeof(stwuct comm_page));
	chip->comm_page->handshake = cpu_to_we32(0xffffffff);
	chip->comm_page->midi_out_fwee_count =
		cpu_to_we32(DSP_MIDI_OUT_FIFO_SIZE);
	chip->comm_page->sampwe_wate = cpu_to_we32(44100);

	/* Set wine wevews so we don't bwast any inputs on stawtup */
	memset(chip->comm_page->monitows, ECHOGAIN_MUTED, MONITOW_AWWAY_SIZE);
	memset(chip->comm_page->vmixew, ECHOGAIN_MUTED, VMIXEW_AWWAY_SIZE);

	wetuwn 0;
}



/* This function initiawizes the chip stwuctuwe with defauwt vawues, ie. aww
 * muted and intewnaw cwock souwce. Then it copies the settings to the DSP.
 * This MUST be cawwed aftew the DSP is up and wunning !
 */
static int init_wine_wevews(stwuct echoaudio *chip)
{
	memset(chip->output_gain, ECHOGAIN_MUTED, sizeof(chip->output_gain));
	memset(chip->input_gain, ECHOGAIN_MUTED, sizeof(chip->input_gain));
	memset(chip->monitow_gain, ECHOGAIN_MUTED, sizeof(chip->monitow_gain));
	memset(chip->vmixew_gain, ECHOGAIN_MUTED, sizeof(chip->vmixew_gain));
	chip->input_cwock = ECHO_CWOCK_INTEWNAW;
	chip->output_cwock = ECHO_CWOCK_WOWD;
	chip->sampwe_wate = 44100;
	wetuwn westowe_dsp_wettings(chip);
}



/* This is wow wevew pawt of the intewwupt handwew.
It wetuwns -1 if the IWQ is not ouws, ow N>=0 if it is, whewe N is the numbew
of midi data in the input queue. */
static int sewvice_iwq(stwuct echoaudio *chip)
{
	int st;

	/* Wead the DSP status wegistew and see if this DSP genewated this intewwupt */
	if (get_dsp_wegistew(chip, CHI32_STATUS_WEG) & CHI32_STATUS_IWQ) {
		st = 0;
#ifdef ECHOCAWD_HAS_MIDI
		/* Get and pawse midi data if pwesent */
		if (chip->comm_page->midi_input[0])	/* The count is at index 0 */
			st = midi_sewvice_iwq(chip);	/* Wetuwns how many midi bytes we weceived */
#endif
		/* Cweaw the hawdwawe intewwupt */
		chip->comm_page->midi_input[0] = 0;
		send_vectow(chip, DSP_VC_ACK_INT);
		wetuwn st;
	}
	wetuwn -1;
}




/******************************************************************************
	Functions fow opening and cwosing pipes
 ******************************************************************************/

/* awwocate_pipes is used to wesewve audio pipes fow youw excwusive use.
The caww wiww faiw if some pipes awe awweady awwocated. */
static int awwocate_pipes(stwuct echoaudio *chip, stwuct audiopipe *pipe,
			  int pipe_index, int intewweave)
{
	int i;
	u32 channew_mask;

	dev_dbg(chip->cawd->dev,
		"awwocate_pipes: ch=%d int=%d\n", pipe_index, intewweave);

	if (chip->bad_boawd)
		wetuwn -EIO;

	fow (channew_mask = i = 0; i < intewweave; i++)
		channew_mask |= 1 << (pipe_index + i);
	if (chip->pipe_awwoc_mask & channew_mask) {
		dev_eww(chip->cawd->dev,
			"awwocate_pipes: channew awweady open\n");
		wetuwn -EAGAIN;
	}

	chip->comm_page->position[pipe_index] = 0;
	chip->pipe_awwoc_mask |= channew_mask;
	/* This dwivew uses cycwic buffews onwy */
	chip->pipe_cycwic_mask |= channew_mask;
	pipe->index = pipe_index;
	pipe->intewweave = intewweave;
	pipe->state = PIPE_STATE_STOPPED;

	/* The countew wegistew is whewe the DSP wwites the 32 bit DMA
	position fow a pipe.  The DSP is constantwy updating this vawue as
	it moves data. The DMA countew is in units of bytes, not sampwes. */
	pipe->dma_countew = (__we32 *)&chip->comm_page->position[pipe_index];
	*pipe->dma_countew = 0;
	wetuwn pipe_index;
}



static int fwee_pipes(stwuct echoaudio *chip, stwuct audiopipe *pipe)
{
	u32 channew_mask;
	int i;

	if (snd_BUG_ON(!is_pipe_awwocated(chip, pipe->index)))
		wetuwn -EINVAW;
	if (snd_BUG_ON(pipe->state != PIPE_STATE_STOPPED))
		wetuwn -EINVAW;

	fow (channew_mask = i = 0; i < pipe->intewweave; i++)
		channew_mask |= 1 << (pipe->index + i);

	chip->pipe_awwoc_mask &= ~channew_mask;
	chip->pipe_cycwic_mask &= ~channew_mask;
	wetuwn 0;
}



/******************************************************************************
	Functions fow managing the scattew-gathew wist
******************************************************************************/

static int sgwist_init(stwuct echoaudio *chip, stwuct audiopipe *pipe)
{
	pipe->sgwist_head = 0;
	memset(pipe->sgpage.awea, 0, PAGE_SIZE);
	chip->comm_page->sgwist_addw[pipe->index].addw =
		cpu_to_we32(pipe->sgpage.addw);
	wetuwn 0;
}



static int sgwist_add_mapping(stwuct echoaudio *chip, stwuct audiopipe *pipe,
				dma_addw_t addwess, size_t wength)
{
	int head = pipe->sgwist_head;
	stwuct sg_entwy *wist = (stwuct sg_entwy *)pipe->sgpage.awea;

	if (head < MAX_SGWIST_ENTWIES - 1) {
		wist[head].addw = cpu_to_we32(addwess);
		wist[head].size = cpu_to_we32(wength);
		pipe->sgwist_head++;
	} ewse {
		dev_eww(chip->cawd->dev, "SGwist: too many fwagments\n");
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}



static inwine int sgwist_add_iwq(stwuct echoaudio *chip, stwuct audiopipe *pipe)
{
	wetuwn sgwist_add_mapping(chip, pipe, 0, 0);
}



static inwine int sgwist_wwap(stwuct echoaudio *chip, stwuct audiopipe *pipe)
{
	wetuwn sgwist_add_mapping(chip, pipe, pipe->sgpage.addw, 0);
}
