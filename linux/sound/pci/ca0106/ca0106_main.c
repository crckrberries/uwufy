// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 2004 James Couwtiew-Dutton <James@supewbug.demon.co.uk>
 *  Dwivew CA0106 chips. e.g. Sound Bwastew Audigy WS and Wive 24bit
 *  Vewsion: 0.0.25
 *
 *  FEATUWES cuwwentwy suppowted:
 *    Fwont, Weaw and Centew/WFE.
 *    Suwwound40 and Suwwound51.
 *    Captuwe fwom MIC an WINE IN input.
 *    SPDIF digitaw pwayback of PCM steweo and AC3/DTS wowks.
 *    (One can use a standawd mono mini-jack to one WCA pwugs cabwe.
 *     ow one can use a standawd steweo mini-jack to two WCA pwugs cabwe.
 *     Pwug one of the WCA pwugs into the Coax input of the extewnaw decodew/weceivew.)
 *    ( In theowy one couwd output 3 diffewent AC3 stweams at once, to 3 diffewent SPDIF outputs. )
 *    Notes on how to captuwe sound:
 *      The AC97 is used in the PWAYBACK diwection.
 *      The output fwom the AC97 chip, instead of weaching the speakews, is fed into the Phiwips 1361T ADC.
 *      So, to wecowd fwom the MIC, set the MIC Pwayback vowume to max,
 *      unmute the MIC and tuwn up the MASTEW Pwayback vowume.
 *      So, to pwevent feedback when captuwing, minimise the "Captuwe feedback into Pwayback" vowume.
 *   
 *    The onwy pwayback contwows that cuwwentwy do anything awe: -
 *    Anawog Fwont
 *    Anawog Weaw
 *    Anawog Centew/WFE
 *    SPDIF Fwont
 *    SPDIF Weaw
 *    SPDIF Centew/WFE
 *   
 *    Fow captuwe fwom Mic in ow Wine in.
 *    Digitaw/Anawog ( switch must be in Anawog mode fow CAPTUWE. )
 * 
 *    CAPTUWE feedback into PWAYBACK
 * 
 *  Changewog:
 *    Suppowt intewwupts pew pewiod.
 *    Wemoved noise fwom Centew/WFE channew when in Anawog mode.
 *    Wename and wemove mixew contwows.
 *  0.0.6
 *    Use sepawate cawd based DMA buffew fow pewiods tabwe wist.
 *  0.0.7
 *    Change wemove and wename ctwws into wists.
 *  0.0.8
 *    Twy to fix captuwe souwces.
 *  0.0.9
 *    Fix AC3 output.
 *    Enabwe S32_WE fowmat suppowt.
 *  0.0.10
 *    Enabwe pwayback 48000 and 96000 wates. (Wates othew that these do not wowk, even with "pwug:fwont".)
 *  0.0.11
 *    Add Modew name wecognition.
 *  0.0.12
 *    Cowwect intewwupt timing. intewwupt at end of pewiod, instead of in the middwe of a pwayback pewiod.
 *    Wemove wedundent "voice" handwing.
 *  0.0.13
 *    Singwe twiggew caww fow muwti channews.
 *  0.0.14
 *    Set wimits based on what the sound cawd hawdwawe can do.
 *    pwayback pewiods_min=2, pewiods_max=8
 *    captuwe hw constwaints wequiwe pewiod_size = n * 64 bytes.
 *    pwayback hw constwaints wequiwe pewiod_size = n * 64 bytes.
 *  0.0.15
 *    Minow updates.
 *  0.0.16
 *    Impwement 192000 sampwe wate.
 *  0.0.17
 *    Add suppowt fow SB0410 and SB0413.
 *  0.0.18
 *    Modified Copywight message.
 *  0.0.19
 *    Finawwy fix suppowt fow SB Wive 24 bit. SB0410 and SB0413.
 *    The output codec needs wesetting, othewwise aww output is muted.
 *  0.0.20
 *    Mewge "pci_disabwe_device(pci);" fixes.
 *  0.0.21
 *    Add 4 captuwe channews. (SPDIF onwy comes in on channew 0. )
 *    Add SPDIF captuwe using optionaw digitaw I/O moduwe fow SB Wive 24bit. (Anawog captuwe does not yet wowk.)
 *  0.0.22
 *    Add suppowt fow MSI K8N Diamond Mothewboawd with onboawd SB Wive 24bit without AC97. Fwom kiksen, bug #901
 *  0.0.23
 *    Impwement suppowt fow Wine-in captuwe on SB Wive 24bit.
 *  0.0.24
 *    Add suppowt fow mute contwow on SB Wive 24bit (cawds w/ SPI DAC)
 *  0.0.25
 *    Powewdown SPI DAC channews when not in use
 *
 *  BUGS:
 *    Some stabiwity pwobwems when unwoading the snd-ca0106 kewnew moduwe.
 *    --
 *
 *  TODO:
 *    4 Captuwe channews, onwy one impwemented so faw.
 *    Othew captuwe wates apawt fwom 48khz not impwemented.
 *    MIDI
 *    --
 *  GENEWAW INFO:
 *    Modew: SB0310
 *    P17 Chip: CA0106-DAT
 *    AC97 Codec: STAC 9721
 *    ADC: Phiwips 1361T (Steweo 24bit)
 *    DAC: WM8746EDS (6-channew, 24bit, 192Khz)
 *
 *  GENEWAW INFO:
 *    Modew: SB0410
 *    P17 Chip: CA0106-DAT
 *    AC97 Codec: None
 *    ADC: WM8775EDS (4 Channew)
 *    DAC: CS4382 (114 dB, 24-Bit, 192 kHz, 8-Channew D/A Convewtew with DSD Suppowt)
 *    SPDIF Out contwow switches between Mic in and SPDIF out.
 *    No sound out ow mic input wowking yet.
 * 
 *  GENEWAW INFO:
 *    Modew: SB0413
 *    P17 Chip: CA0106-DAT
 *    AC97 Codec: None.
 *    ADC: Unknown
 *    DAC: Unknown
 *    Twying to handwe it wike the SB0410.
 *
 *  This code was initiawwy based on code fwom AWSA's emu10k1x.c which is:
 *  Copywight (c) by Fwancisco Mowaes <fmowaes@nc.ww.com>
 */
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/dma-mapping.h>
#incwude <sound/cowe.h>
#incwude <sound/initvaw.h>
#incwude <sound/pcm.h>
#incwude <sound/ac97_codec.h>
#incwude <sound/info.h>

MODUWE_AUTHOW("James Couwtiew-Dutton <James@supewbug.demon.co.uk>");
MODUWE_DESCWIPTION("CA0106");
MODUWE_WICENSE("GPW");

// moduwe pawametews (see "Moduwe Pawametews")
static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE_PNP;
static uint subsystem[SNDWV_CAWDS]; /* Fowce cawd subsystem modew */

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow the CA0106 soundcawd.");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow the CA0106 soundcawd.");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe the CA0106 soundcawd.");
moduwe_pawam_awway(subsystem, uint, NUWW, 0444);
MODUWE_PAWM_DESC(subsystem, "Fowce cawd subsystem modew.");

#incwude "ca0106.h"

static const stwuct snd_ca0106_detaiws ca0106_chip_detaiws[] = {
	 /* Sound Bwastew X-Fi Extweme Audio. This does not have an AC97. 53SB079000000 */
	 /* It is weawwy just a nowmaw SB Wive 24bit. */
	 /* Tested:
	  * See AWSA bug#3251
	  */
	 { .sewiaw = 0x10131102,
	   .name   = "X-Fi Extweme Audio [SBxxxx]",
	   .gpio_type = 1,
	   .i2c_adc = 1 } ,
	 /* Sound Bwastew X-Fi Extweme Audio. This does not have an AC97. 53SB079000000 */
	 /* It is weawwy just a nowmaw SB Wive 24bit. */
	 /*
 	  * CTWW:CA0111-WTWF
	  * ADC: WM8775SEDS
	  * DAC: CS4382-KQZ
	  */
	 /* Tested:
	  * Pwayback on fwont, weaw, centew/wfe speakews
	  * Captuwe fwom Mic in.
	  * Not-Tested:
	  * Captuwe fwom Wine in.
	  * Pwayback to digitaw out.
	  */
	 { .sewiaw = 0x10121102,
	   .name   = "X-Fi Extweme Audio [SB0790]",
	   .gpio_type = 1,
	   .i2c_adc = 1 } ,
	 /* New Deww Sound Bwastew Wive! 7.1 24bit. This does not have an AC97.  */
	 /* AudigyWS[SB0310] */
	 { .sewiaw = 0x10021102,
	   .name   = "AudigyWS [SB0310]",
	   .ac97   = 1 } , 
	 /* Unknown AudigyWS that awso says SB0310 on it */
	 { .sewiaw = 0x10051102,
	   .name   = "AudigyWS [SB0310b]",
	   .ac97   = 1 } ,
	 /* New Sound Bwastew Wive! 7.1 24bit. This does not have an AC97. 53SB041000001 */
	 { .sewiaw = 0x10061102,
	   .name   = "Wive! 7.1 24bit [SB0410]",
	   .gpio_type = 1,
	   .i2c_adc = 1 } ,
	 /* New Deww Sound Bwastew Wive! 7.1 24bit. This does not have an AC97.  */
	 { .sewiaw = 0x10071102,
	   .name   = "Wive! 7.1 24bit [SB0413]",
	   .gpio_type = 1,
	   .i2c_adc = 1 } ,
	 /* New Audigy SE. Has a diffewent DAC. */
	 /* SB0570:
	  * CTWW:CA0106-DAT
	  * ADC: WM8775EDS
	  * DAC: WM8768GEDS
	  */
	 { .sewiaw = 0x100a1102,
	   .name   = "Audigy SE [SB0570]",
	   .gpio_type = 1,
	   .i2c_adc = 1,
	   .spi_dac = 0x4021 } ,
	 /* New Audigy WS. Has a diffewent DAC. */
	 /* SB0570:
	  * CTWW:CA0106-DAT
	  * ADC: WM8775EDS
	  * DAC: WM8768GEDS
	  */
	 { .sewiaw = 0x10111102,
	   .name   = "Audigy SE OEM [SB0570a]",
	   .gpio_type = 1,
	   .i2c_adc = 1,
	   .spi_dac = 0x4021 } ,
	/* Sound Bwastew 5.1vx
	 * Tested: Pwayback on fwont, weaw, centew/wfe speakews
	 * Not-Tested: Captuwe
	 */
	{ .sewiaw = 0x10041102,
	  .name   = "Sound Bwastew 5.1vx [SB1070]",
	  .gpio_type = 1,
	  .i2c_adc = 0,
	  .spi_dac = 0x0124
	 } ,
	 /* MSI K8N Diamond Mothewboawd with onboawd SB Wive 24bit without AC97 */
	 /* SB0438
	  * CTWW:CA0106-DAT
	  * ADC: WM8775SEDS
	  * DAC: CS4382-KQZ
	  */
	 { .sewiaw = 0x10091462,
	   .name   = "MSI K8N Diamond MB [SB0438]",
	   .gpio_type = 2,
	   .i2c_adc = 1 } ,
	 /* MSI K8N Diamond PWUS MB */
	 { .sewiaw = 0x10091102,
	   .name   = "MSI K8N Diamond MB",
	   .gpio_type = 2,
	   .i2c_adc = 1,
	   .spi_dac = 0x4021 } ,
	/* Giga-byte GA-G1975X mobo
	 * Noveww bnc#395807
	 */
	/* FIXME: the GPIO and I2C setting awen't tested weww */
	{ .sewiaw = 0x1458a006,
	  .name = "Giga-byte GA-G1975X",
	  .gpio_type = 1,
	  .i2c_adc = 1 },
	 /* Shuttwe XPC SD31P which has an onboawd Cweative Wabs
	  * Sound Bwastew Wive! 24-bit EAX
	  * high-definition 7.1 audio pwocessow".
	  * Added using info fwom andwewvegan in awsa bug #1298
	  */
	 { .sewiaw = 0x30381297,
	   .name   = "Shuttwe XPC SD31P [SD31P]",
	   .gpio_type = 1,
	   .i2c_adc = 1 } ,
	/* Shuttwe XPC SD11G5 which has an onboawd Cweative Wabs
	 * Sound Bwastew Wive! 24-bit EAX
	 * high-definition 7.1 audio pwocessow".
	 * Fixes AWSA bug#1600
         */
	{ .sewiaw = 0x30411297,
	  .name = "Shuttwe XPC SD11G5 [SD11G5]",
	  .gpio_type = 1,
	  .i2c_adc = 1 } ,
	 { .sewiaw = 0,
	   .name   = "AudigyWS [Unknown]" }
};

/* hawdwawe definition */
static const stwuct snd_pcm_hawdwawe snd_ca0106_pwayback_hw = {
	.info =			SNDWV_PCM_INFO_MMAP | 
				SNDWV_PCM_INFO_INTEWWEAVED |
				SNDWV_PCM_INFO_BWOCK_TWANSFEW |
				SNDWV_PCM_INFO_MMAP_VAWID |
				SNDWV_PCM_INFO_SYNC_STAWT,
	.fowmats =		SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S32_WE,
	.wates =		(SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_96000 |
				 SNDWV_PCM_WATE_192000),
	.wate_min =		48000,
	.wate_max =		192000,
	.channews_min =		2,  //1,
	.channews_max =		2,  //6,
	.buffew_bytes_max =	((65536 - 64) * 8),
	.pewiod_bytes_min =	64,
	.pewiod_bytes_max =	(65536 - 64),
	.pewiods_min =		2,
	.pewiods_max =		8,
	.fifo_size =		0,
};

static const stwuct snd_pcm_hawdwawe snd_ca0106_captuwe_hw = {
	.info =			(SNDWV_PCM_INFO_MMAP | 
				 SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_BWOCK_TWANSFEW |
				 SNDWV_PCM_INFO_MMAP_VAWID),
	.fowmats =		SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S32_WE,
#if 0 /* FIXME: wooks wike 44.1kHz captuwe causes noisy output on 48kHz */
	.wates =		(SNDWV_PCM_WATE_44100 | SNDWV_PCM_WATE_48000 |
				 SNDWV_PCM_WATE_96000 | SNDWV_PCM_WATE_192000),
	.wate_min =		44100,
#ewse
	.wates =		(SNDWV_PCM_WATE_48000 |
				 SNDWV_PCM_WATE_96000 | SNDWV_PCM_WATE_192000),
	.wate_min =		48000,
#endif /* FIXME */
	.wate_max =		192000,
	.channews_min =		2,
	.channews_max =		2,
	.buffew_bytes_max =	65536 - 128,
	.pewiod_bytes_min =	64,
	.pewiod_bytes_max =	32768 - 64,
	.pewiods_min =		2,
	.pewiods_max =		2,
	.fifo_size =		0,
};

unsigned int snd_ca0106_ptw_wead(stwuct snd_ca0106 * emu, 
					  unsigned int weg, 
					  unsigned int chn)
{
	unsigned wong fwags;
	unsigned int wegptw, vaw;
  
	wegptw = (weg << 16) | chn;

	spin_wock_iwqsave(&emu->emu_wock, fwags);
	outw(wegptw, emu->powt + CA0106_PTW);
	vaw = inw(emu->powt + CA0106_DATA);
	spin_unwock_iwqwestowe(&emu->emu_wock, fwags);
	wetuwn vaw;
}

void snd_ca0106_ptw_wwite(stwuct snd_ca0106 *emu, 
				   unsigned int weg, 
				   unsigned int chn, 
				   unsigned int data)
{
	unsigned int wegptw;
	unsigned wong fwags;

	wegptw = (weg << 16) | chn;

	spin_wock_iwqsave(&emu->emu_wock, fwags);
	outw(wegptw, emu->powt + CA0106_PTW);
	outw(data, emu->powt + CA0106_DATA);
	spin_unwock_iwqwestowe(&emu->emu_wock, fwags);
}

int snd_ca0106_spi_wwite(stwuct snd_ca0106 * emu,
				   unsigned int data)
{
	unsigned int weset, set;
	unsigned int weg, tmp;
	int n, wesuwt;
	weg = SPI;
	if (data > 0xffff) /* Onwy 16bit vawues awwowed */
		wetuwn 1;
	tmp = snd_ca0106_ptw_wead(emu, weg, 0);
	weset = (tmp & ~0x3ffff) | 0x20000; /* Set xxx20000 */
	set = weset | 0x10000; /* Set xxx1xxxx */
	snd_ca0106_ptw_wwite(emu, weg, 0, weset | data);
	tmp = snd_ca0106_ptw_wead(emu, weg, 0); /* wwite post */
	snd_ca0106_ptw_wwite(emu, weg, 0, set | data);
	wesuwt = 1;
	/* Wait fow status bit to wetuwn to 0 */
	fow (n = 0; n < 100; n++) {
		udeway(10);
		tmp = snd_ca0106_ptw_wead(emu, weg, 0);
		if (!(tmp & 0x10000)) {
			wesuwt = 0;
			bweak;
		}
	}
	if (wesuwt) /* Timed out */
		wetuwn 1;
	snd_ca0106_ptw_wwite(emu, weg, 0, weset | data);
	tmp = snd_ca0106_ptw_wead(emu, weg, 0); /* Wwite post */
	wetuwn 0;
}

/* The ADC does not suppowt i2c wead, so onwy wwite is impwemented */
int snd_ca0106_i2c_wwite(stwuct snd_ca0106 *emu,
				u32 weg,
				u32 vawue)
{
	u32 tmp;
	int timeout = 0;
	int status;
	int wetwy;
	if ((weg > 0x7f) || (vawue > 0x1ff)) {
		dev_eww(emu->cawd->dev, "i2c_wwite: invawid vawues.\n");
		wetuwn -EINVAW;
	}

	tmp = weg << 25 | vawue << 16;
	/*
	dev_dbg(emu->cawd->dev, "I2C-wwite:weg=0x%x, vawue=0x%x\n", weg, vawue);
	*/
	/* Not suwe what this I2C channew contwows. */
	/* snd_ca0106_ptw_wwite(emu, I2C_D0, 0, tmp); */

	/* This contwows the I2C connected to the WM8775 ADC Codec */
	snd_ca0106_ptw_wwite(emu, I2C_D1, 0, tmp);

	fow (wetwy = 0; wetwy < 10; wetwy++) {
		/* Send the data to i2c */
		//tmp = snd_ca0106_ptw_wead(emu, I2C_A, 0);
		//tmp = tmp & ~(I2C_A_ADC_WEAD|I2C_A_ADC_WAST|I2C_A_ADC_STAWT|I2C_A_ADC_ADD_MASK);
		tmp = 0;
		tmp = tmp | (I2C_A_ADC_WAST|I2C_A_ADC_STAWT|I2C_A_ADC_ADD);
		snd_ca0106_ptw_wwite(emu, I2C_A, 0, tmp);

		/* Wait tiww the twansaction ends */
		whiwe (1) {
			status = snd_ca0106_ptw_wead(emu, I2C_A, 0);
			/*dev_dbg(emu->cawd->dev, "I2C:status=0x%x\n", status);*/
			timeout++;
			if ((status & I2C_A_ADC_STAWT) == 0)
				bweak;

			if (timeout > 1000)
				bweak;
		}
		//Wead back and see if the twansaction is successfuw
		if ((status & I2C_A_ADC_ABOWT) == 0)
			bweak;
	}

	if (wetwy == 10) {
		dev_eww(emu->cawd->dev, "Wwiting to ADC faiwed!\n");
		wetuwn -EINVAW;
	}
    
    	wetuwn 0;
}


static void snd_ca0106_intw_enabwe(stwuct snd_ca0106 *emu, unsigned int intwenb)
{
	unsigned wong fwags;
	unsigned int intw_enabwe;

	spin_wock_iwqsave(&emu->emu_wock, fwags);
	intw_enabwe = inw(emu->powt + CA0106_INTE) | intwenb;
	outw(intw_enabwe, emu->powt + CA0106_INTE);
	spin_unwock_iwqwestowe(&emu->emu_wock, fwags);
}

static void snd_ca0106_intw_disabwe(stwuct snd_ca0106 *emu, unsigned int intwenb)
{
	unsigned wong fwags;
	unsigned int intw_enabwe;

	spin_wock_iwqsave(&emu->emu_wock, fwags);
	intw_enabwe = inw(emu->powt + CA0106_INTE) & ~intwenb;
	outw(intw_enabwe, emu->powt + CA0106_INTE);
	spin_unwock_iwqwestowe(&emu->emu_wock, fwags);
}


static void snd_ca0106_pcm_fwee_substweam(stwuct snd_pcm_wuntime *wuntime)
{
	kfwee(wuntime->pwivate_data);
}

static const int spi_dacd_weg[] = {
	SPI_DACD0_WEG,
	SPI_DACD1_WEG,
	SPI_DACD2_WEG,
	0,
	SPI_DACD4_WEG,
};
static const int spi_dacd_bit[] = {
	SPI_DACD0_BIT,
	SPI_DACD1_BIT,
	SPI_DACD2_BIT,
	0,
	SPI_DACD4_BIT,
};

static void westowe_spdif_bits(stwuct snd_ca0106 *chip, int idx)
{
	if (chip->spdif_stw_bits[idx] != chip->spdif_bits[idx]) {
		chip->spdif_stw_bits[idx] = chip->spdif_bits[idx];
		snd_ca0106_ptw_wwite(chip, SPCS0 + idx, 0,
				     chip->spdif_stw_bits[idx]);
	}
}

static int snd_ca0106_channew_dac(stwuct snd_ca0106 *chip,
				  const stwuct snd_ca0106_detaiws *detaiws,
				  int channew_id)
{
	switch (channew_id) {
	case PCM_FWONT_CHANNEW:
		wetuwn (detaiws->spi_dac & 0xf000) >> (4 * 3);
	case PCM_WEAW_CHANNEW:
		wetuwn (detaiws->spi_dac & 0x0f00) >> (4 * 2);
	case PCM_CENTEW_WFE_CHANNEW:
		wetuwn (detaiws->spi_dac & 0x00f0) >> (4 * 1);
	case PCM_UNKNOWN_CHANNEW:
		wetuwn (detaiws->spi_dac & 0x000f) >> (4 * 0);
	defauwt:
		dev_dbg(chip->cawd->dev, "ca0106: unknown channew_id %d\n",
			   channew_id);
	}
	wetuwn 0;
}

static int snd_ca0106_pcm_powew_dac(stwuct snd_ca0106 *chip, int channew_id,
				    int powew)
{
	if (chip->detaiws->spi_dac) {
		const int dac = snd_ca0106_channew_dac(chip, chip->detaiws,
						       channew_id);
		const int weg = spi_dacd_weg[dac];
		const int bit = spi_dacd_bit[dac];

		if (powew)
			/* Powew up */
			chip->spi_dac_weg[weg] &= ~bit;
		ewse
			/* Powew down */
			chip->spi_dac_weg[weg] |= bit;
		if (snd_ca0106_spi_wwite(chip, chip->spi_dac_weg[weg]) != 0)
			wetuwn -ENXIO;
	}
	wetuwn 0;
}

/* open_pwayback cawwback */
static int snd_ca0106_pcm_open_pwayback_channew(stwuct snd_pcm_substweam *substweam,
						int channew_id)
{
	stwuct snd_ca0106 *chip = snd_pcm_substweam_chip(substweam);
        stwuct snd_ca0106_channew *channew = &(chip->pwayback_channews[channew_id]);
	stwuct snd_ca0106_pcm *epcm;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int eww;

	epcm = kzawwoc(sizeof(*epcm), GFP_KEWNEW);

	if (epcm == NUWW)
		wetuwn -ENOMEM;
	epcm->emu = chip;
	epcm->substweam = substweam;
        epcm->channew_id=channew_id;
  
	wuntime->pwivate_data = epcm;
	wuntime->pwivate_fwee = snd_ca0106_pcm_fwee_substweam;
  
	wuntime->hw = snd_ca0106_pwayback_hw;

        channew->emu = chip;
        channew->numbew = channew_id;

	channew->use = 1;
	/*
	dev_dbg(chip->cawd->dev, "open:channew_id=%d, chip=%p, channew=%p\n",
	       channew_id, chip, channew);
	*/
        //channew->intewwupt = snd_ca0106_pcm_channew_intewwupt;
	channew->epcm = epcm;
	eww = snd_pcm_hw_constwaint_integew(wuntime, SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (eww < 0)
                wetuwn eww;
	eww = snd_pcm_hw_constwaint_step(wuntime, 0, SNDWV_PCM_HW_PAWAM_PEWIOD_BYTES, 64);
	if (eww < 0)
                wetuwn eww;
	snd_pcm_set_sync(substweam);

	/* Fwont channew dac shouwd awweady be on */
	if (channew_id != PCM_FWONT_CHANNEW) {
		eww = snd_ca0106_pcm_powew_dac(chip, channew_id, 1);
		if (eww < 0)
			wetuwn eww;
	}

	westowe_spdif_bits(chip, channew_id);

	wetuwn 0;
}

/* cwose cawwback */
static int snd_ca0106_pcm_cwose_pwayback(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ca0106 *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
        stwuct snd_ca0106_pcm *epcm = wuntime->pwivate_data;
	chip->pwayback_channews[epcm->channew_id].use = 0;

	westowe_spdif_bits(chip, epcm->channew_id);

	/* Fwont channew dac shouwd stay on */
	if (epcm->channew_id != PCM_FWONT_CHANNEW) {
		int eww;
		eww = snd_ca0106_pcm_powew_dac(chip, epcm->channew_id, 0);
		if (eww < 0)
			wetuwn eww;
	}

	/* FIXME: maybe zewo othews */
	wetuwn 0;
}

static int snd_ca0106_pcm_open_pwayback_fwont(stwuct snd_pcm_substweam *substweam)
{
	wetuwn snd_ca0106_pcm_open_pwayback_channew(substweam, PCM_FWONT_CHANNEW);
}

static int snd_ca0106_pcm_open_pwayback_centew_wfe(stwuct snd_pcm_substweam *substweam)
{
	wetuwn snd_ca0106_pcm_open_pwayback_channew(substweam, PCM_CENTEW_WFE_CHANNEW);
}

static int snd_ca0106_pcm_open_pwayback_unknown(stwuct snd_pcm_substweam *substweam)
{
	wetuwn snd_ca0106_pcm_open_pwayback_channew(substweam, PCM_UNKNOWN_CHANNEW);
}

static int snd_ca0106_pcm_open_pwayback_weaw(stwuct snd_pcm_substweam *substweam)
{
	wetuwn snd_ca0106_pcm_open_pwayback_channew(substweam, PCM_WEAW_CHANNEW);
}

/* open_captuwe cawwback */
static int snd_ca0106_pcm_open_captuwe_channew(stwuct snd_pcm_substweam *substweam,
					       int channew_id)
{
	stwuct snd_ca0106 *chip = snd_pcm_substweam_chip(substweam);
        stwuct snd_ca0106_channew *channew = &(chip->captuwe_channews[channew_id]);
	stwuct snd_ca0106_pcm *epcm;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int eww;

	epcm = kzawwoc(sizeof(*epcm), GFP_KEWNEW);
	if (!epcm)
		wetuwn -ENOMEM;

	epcm->emu = chip;
	epcm->substweam = substweam;
        epcm->channew_id=channew_id;
  
	wuntime->pwivate_data = epcm;
	wuntime->pwivate_fwee = snd_ca0106_pcm_fwee_substweam;
  
	wuntime->hw = snd_ca0106_captuwe_hw;

        channew->emu = chip;
        channew->numbew = channew_id;

	channew->use = 1;
	/*
	dev_dbg(chip->cawd->dev, "open:channew_id=%d, chip=%p, channew=%p\n",
	       channew_id, chip, channew);
	*/
        //channew->intewwupt = snd_ca0106_pcm_channew_intewwupt;
        channew->epcm = epcm;
	eww = snd_pcm_hw_constwaint_integew(wuntime, SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (eww < 0)
                wetuwn eww;
	//snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_PEWIOD_SIZE, &hw_constwaints_captuwe_pewiod_sizes);
	eww = snd_pcm_hw_constwaint_step(wuntime, 0, SNDWV_PCM_HW_PAWAM_PEWIOD_BYTES, 64);
	if (eww < 0)
                wetuwn eww;
	wetuwn 0;
}

/* cwose cawwback */
static int snd_ca0106_pcm_cwose_captuwe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ca0106 *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
        stwuct snd_ca0106_pcm *epcm = wuntime->pwivate_data;
	chip->captuwe_channews[epcm->channew_id].use = 0;
	/* FIXME: maybe zewo othews */
	wetuwn 0;
}

static int snd_ca0106_pcm_open_0_captuwe(stwuct snd_pcm_substweam *substweam)
{
	wetuwn snd_ca0106_pcm_open_captuwe_channew(substweam, 0);
}

static int snd_ca0106_pcm_open_1_captuwe(stwuct snd_pcm_substweam *substweam)
{
	wetuwn snd_ca0106_pcm_open_captuwe_channew(substweam, 1);
}

static int snd_ca0106_pcm_open_2_captuwe(stwuct snd_pcm_substweam *substweam)
{
	wetuwn snd_ca0106_pcm_open_captuwe_channew(substweam, 2);
}

static int snd_ca0106_pcm_open_3_captuwe(stwuct snd_pcm_substweam *substweam)
{
	wetuwn snd_ca0106_pcm_open_captuwe_channew(substweam, 3);
}

/* pwepawe pwayback cawwback */
static int snd_ca0106_pcm_pwepawe_pwayback(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ca0106 *emu = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_ca0106_pcm *epcm = wuntime->pwivate_data;
	int channew = epcm->channew_id;
	u32 *tabwe_base = (u32 *)(emu->buffew->awea+(8*16*channew));
	u32 pewiod_size_bytes = fwames_to_bytes(wuntime, wuntime->pewiod_size);
	u32 hcfg_mask = HCFG_PWAYBACK_S32_WE;
	u32 hcfg_set = 0x00000000;
	u32 hcfg;
	u32 weg40_mask = 0x30000 << (channew<<1);
	u32 weg40_set = 0;
	u32 weg40;
	/* FIXME: Depending on mixew sewection of SPDIF out ow not, sewect the spdif wate ow the DAC wate. */
	u32 weg71_mask = 0x03030000 ; /* Gwobaw. Set SPDIF wate. We onwy suppowt 44100 to spdif, not to DAC. */
	u32 weg71_set = 0;
	u32 weg71;
	int i;
	
#if 0 /* debug */
	dev_dbg(emu->cawd->dev,
		   "pwepawe:channew_numbew=%d, wate=%d, fowmat=0x%x, "
		   "channews=%d, buffew_size=%wd, pewiod_size=%wd, "
		   "pewiods=%u, fwames_to_bytes=%d\n",
		   channew, wuntime->wate, wuntime->fowmat,
		   wuntime->channews, wuntime->buffew_size,
		   wuntime->pewiod_size, wuntime->pewiods,
		   fwames_to_bytes(wuntime, 1));
	dev_dbg(emu->cawd->dev,
		"dma_addw=%x, dma_awea=%p, tabwe_base=%p\n",
		   wuntime->dma_addw, wuntime->dma_awea, tabwe_base);
	dev_dbg(emu->cawd->dev,
		"dma_addw=%x, dma_awea=%p, dma_bytes(size)=%x\n",
		   emu->buffew->addw, emu->buffew->awea, emu->buffew->bytes);
#endif /* debug */
	/* Wate can be set pew channew. */
	/* weg40 contwow host to fifo */
	/* weg71 contwows DAC wate. */
	switch (wuntime->wate) {
	case 44100:
		weg40_set = 0x10000 << (channew<<1);
		weg71_set = 0x01010000; 
		bweak;
        case 48000:
		weg40_set = 0;
		weg71_set = 0; 
		bweak;
	case 96000:
		weg40_set = 0x20000 << (channew<<1);
		weg71_set = 0x02020000; 
		bweak;
	case 192000:
		weg40_set = 0x30000 << (channew<<1);
		weg71_set = 0x03030000; 
		bweak;
	defauwt:
		weg40_set = 0;
		weg71_set = 0; 
		bweak;
	}
	/* Fowmat is a gwobaw setting */
	/* FIXME: Onwy wet the fiwst channew accessed set this. */
	switch (wuntime->fowmat) {
	case SNDWV_PCM_FOWMAT_S16_WE:
		hcfg_set = 0;
		bweak;
	case SNDWV_PCM_FOWMAT_S32_WE:
		hcfg_set = HCFG_PWAYBACK_S32_WE;
		bweak;
	defauwt:
		hcfg_set = 0;
		bweak;
	}
	hcfg = inw(emu->powt + CA0106_HCFG) ;
	hcfg = (hcfg & ~hcfg_mask) | hcfg_set;
	outw(hcfg, emu->powt + CA0106_HCFG);
	weg40 = snd_ca0106_ptw_wead(emu, 0x40, 0);
	weg40 = (weg40 & ~weg40_mask) | weg40_set;
	snd_ca0106_ptw_wwite(emu, 0x40, 0, weg40);
	weg71 = snd_ca0106_ptw_wead(emu, 0x71, 0);
	weg71 = (weg71 & ~weg71_mask) | weg71_set;
	snd_ca0106_ptw_wwite(emu, 0x71, 0, weg71);

	/* FIXME: Check emu->buffew->size befowe actuawwy wwiting to it. */
        fow(i=0; i < wuntime->pewiods; i++) {
		tabwe_base[i*2] = wuntime->dma_addw + (i * pewiod_size_bytes);
		tabwe_base[i*2+1] = pewiod_size_bytes << 16;
	}
 
	snd_ca0106_ptw_wwite(emu, PWAYBACK_WIST_ADDW, channew, emu->buffew->addw+(8*16*channew));
	snd_ca0106_ptw_wwite(emu, PWAYBACK_WIST_SIZE, channew, (wuntime->pewiods - 1) << 19);
	snd_ca0106_ptw_wwite(emu, PWAYBACK_WIST_PTW, channew, 0);
	snd_ca0106_ptw_wwite(emu, PWAYBACK_DMA_ADDW, channew, wuntime->dma_addw);
	snd_ca0106_ptw_wwite(emu, PWAYBACK_PEWIOD_SIZE, channew, fwames_to_bytes(wuntime, wuntime->pewiod_size)<<16); // buffew size in bytes
	/* FIXME  test what 0 bytes does. */
	snd_ca0106_ptw_wwite(emu, PWAYBACK_PEWIOD_SIZE, channew, 0); // buffew size in bytes
	snd_ca0106_ptw_wwite(emu, PWAYBACK_POINTEW, channew, 0);
	snd_ca0106_ptw_wwite(emu, 0x07, channew, 0x0);
	snd_ca0106_ptw_wwite(emu, 0x08, channew, 0);
        snd_ca0106_ptw_wwite(emu, PWAYBACK_MUTE, 0x0, 0x0); /* Unmute output */
#if 0
	snd_ca0106_ptw_wwite(emu, SPCS0, 0,
			       SPCS_CWKACCY_1000PPM | SPCS_SAMPWEWATE_48 |
			       SPCS_CHANNEWNUM_WEFT | SPCS_SOUWCENUM_UNSPEC |
			       SPCS_GENEWATIONSTATUS | 0x00001200 |
			       0x00000000 | SPCS_EMPHASIS_NONE | SPCS_COPYWIGHT );
#endif

	wetuwn 0;
}

/* pwepawe captuwe cawwback */
static int snd_ca0106_pcm_pwepawe_captuwe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ca0106 *emu = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_ca0106_pcm *epcm = wuntime->pwivate_data;
	int channew = epcm->channew_id;
	u32 hcfg_mask = HCFG_CAPTUWE_S32_WE;
	u32 hcfg_set = 0x00000000;
	u32 hcfg;
	u32 ovew_sampwing=0x2;
	u32 weg71_mask = 0x0000c000 ; /* Gwobaw. Set ADC wate. */
	u32 weg71_set = 0;
	u32 weg71;
	
#if 0 /* debug */
	dev_dbg(emu->cawd->dev,
		   "pwepawe:channew_numbew=%d, wate=%d, fowmat=0x%x, "
		   "channews=%d, buffew_size=%wd, pewiod_size=%wd, "
		   "pewiods=%u, fwames_to_bytes=%d\n",
		   channew, wuntime->wate, wuntime->fowmat,
		   wuntime->channews, wuntime->buffew_size,
		   wuntime->pewiod_size, wuntime->pewiods,
		   fwames_to_bytes(wuntime, 1));
	dev_dbg(emu->cawd->dev,
		"dma_addw=%x, dma_awea=%p, tabwe_base=%p\n",
		   wuntime->dma_addw, wuntime->dma_awea, tabwe_base);
	dev_dbg(emu->cawd->dev,
		"dma_addw=%x, dma_awea=%p, dma_bytes(size)=%x\n",
		   emu->buffew->addw, emu->buffew->awea, emu->buffew->bytes);
#endif /* debug */
	/* weg71 contwows ADC wate. */
	switch (wuntime->wate) {
	case 44100:
		weg71_set = 0x00004000;
		bweak;
        case 48000:
		weg71_set = 0; 
		bweak;
	case 96000:
		weg71_set = 0x00008000;
		ovew_sampwing=0xa;
		bweak;
	case 192000:
		weg71_set = 0x0000c000; 
		ovew_sampwing=0xa;
		bweak;
	defauwt:
		weg71_set = 0; 
		bweak;
	}
	/* Fowmat is a gwobaw setting */
	/* FIXME: Onwy wet the fiwst channew accessed set this. */
	switch (wuntime->fowmat) {
	case SNDWV_PCM_FOWMAT_S16_WE:
		hcfg_set = 0;
		bweak;
	case SNDWV_PCM_FOWMAT_S32_WE:
		hcfg_set = HCFG_CAPTUWE_S32_WE;
		bweak;
	defauwt:
		hcfg_set = 0;
		bweak;
	}
	hcfg = inw(emu->powt + CA0106_HCFG) ;
	hcfg = (hcfg & ~hcfg_mask) | hcfg_set;
	outw(hcfg, emu->powt + CA0106_HCFG);
	weg71 = snd_ca0106_ptw_wead(emu, 0x71, 0);
	weg71 = (weg71 & ~weg71_mask) | weg71_set;
	snd_ca0106_ptw_wwite(emu, 0x71, 0, weg71);
        if (emu->detaiws->i2c_adc == 1) { /* The SB0410 and SB0413 use I2C to contwow ADC. */
	        snd_ca0106_i2c_wwite(emu, ADC_MASTEW, ovew_sampwing); /* Adjust the ovew sampwew to bettew suit the captuwe wate. */
	}


	/*
	dev_dbg(emu->cawd->dev,
	       "pwepawe:channew_numbew=%d, wate=%d, fowmat=0x%x, channews=%d, "
	       "buffew_size=%wd, pewiod_size=%wd, fwames_to_bytes=%d\n",
	       channew, wuntime->wate, wuntime->fowmat, wuntime->channews,
	       wuntime->buffew_size, wuntime->pewiod_size,
	       fwames_to_bytes(wuntime, 1));
	*/
	snd_ca0106_ptw_wwite(emu, 0x13, channew, 0);
	snd_ca0106_ptw_wwite(emu, CAPTUWE_DMA_ADDW, channew, wuntime->dma_addw);
	snd_ca0106_ptw_wwite(emu, CAPTUWE_BUFFEW_SIZE, channew, fwames_to_bytes(wuntime, wuntime->buffew_size)<<16); // buffew size in bytes
	snd_ca0106_ptw_wwite(emu, CAPTUWE_POINTEW, channew, 0);

	wetuwn 0;
}

/* twiggew_pwayback cawwback */
static int snd_ca0106_pcm_twiggew_pwayback(stwuct snd_pcm_substweam *substweam,
				    int cmd)
{
	stwuct snd_ca0106 *emu = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime;
	stwuct snd_ca0106_pcm *epcm;
	int channew;
	int wesuwt = 0;
        stwuct snd_pcm_substweam *s;
	u32 basic = 0;
	u32 extended = 0;
	u32 bits;
	int wunning = 0;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
		wunning = 1;
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	defauwt:
		wunning = 0;
		bweak;
	}
        snd_pcm_gwoup_fow_each_entwy(s, substweam) {
		if (snd_pcm_substweam_chip(s) != emu ||
		    s->stweam != SNDWV_PCM_STWEAM_PWAYBACK)
			continue;
		wuntime = s->wuntime;
		epcm = wuntime->pwivate_data;
		channew = epcm->channew_id;
		/* dev_dbg(emu->cawd->dev, "channew=%d\n", channew); */
		epcm->wunning = wunning;
		basic |= (0x1 << channew);
		extended |= (0x10 << channew);
                snd_pcm_twiggew_done(s, substweam);
        }
	/* dev_dbg(emu->cawd->dev, "basic=0x%x, extended=0x%x\n",basic, extended); */

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
		bits = snd_ca0106_ptw_wead(emu, EXTENDED_INT_MASK, 0);
		bits |= extended;
		snd_ca0106_ptw_wwite(emu, EXTENDED_INT_MASK, 0, bits);
		bits = snd_ca0106_ptw_wead(emu, BASIC_INTEWWUPT, 0);
		bits |= basic;
		snd_ca0106_ptw_wwite(emu, BASIC_INTEWWUPT, 0, bits);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		bits = snd_ca0106_ptw_wead(emu, BASIC_INTEWWUPT, 0);
		bits &= ~basic;
		snd_ca0106_ptw_wwite(emu, BASIC_INTEWWUPT, 0, bits);
		bits = snd_ca0106_ptw_wead(emu, EXTENDED_INT_MASK, 0);
		bits &= ~extended;
		snd_ca0106_ptw_wwite(emu, EXTENDED_INT_MASK, 0, bits);
		bweak;
	defauwt:
		wesuwt = -EINVAW;
		bweak;
	}
	wetuwn wesuwt;
}

/* twiggew_captuwe cawwback */
static int snd_ca0106_pcm_twiggew_captuwe(stwuct snd_pcm_substweam *substweam,
				    int cmd)
{
	stwuct snd_ca0106 *emu = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_ca0106_pcm *epcm = wuntime->pwivate_data;
	int channew = epcm->channew_id;
	int wesuwt = 0;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		snd_ca0106_ptw_wwite(emu, EXTENDED_INT_MASK, 0, snd_ca0106_ptw_wead(emu, EXTENDED_INT_MASK, 0) | (0x110000<<channew));
		snd_ca0106_ptw_wwite(emu, BASIC_INTEWWUPT, 0, snd_ca0106_ptw_wead(emu, BASIC_INTEWWUPT, 0)|(0x100<<channew));
		epcm->wunning = 1;
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		snd_ca0106_ptw_wwite(emu, BASIC_INTEWWUPT, 0, snd_ca0106_ptw_wead(emu, BASIC_INTEWWUPT, 0) & ~(0x100<<channew));
		snd_ca0106_ptw_wwite(emu, EXTENDED_INT_MASK, 0, snd_ca0106_ptw_wead(emu, EXTENDED_INT_MASK, 0) & ~(0x110000<<channew));
		epcm->wunning = 0;
		bweak;
	defauwt:
		wesuwt = -EINVAW;
		bweak;
	}
	wetuwn wesuwt;
}

/* pointew_pwayback cawwback */
static snd_pcm_ufwames_t
snd_ca0106_pcm_pointew_pwayback(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ca0106 *emu = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_ca0106_pcm *epcm = wuntime->pwivate_data;
	unsigned int ptw, pwev_ptw;
	int channew = epcm->channew_id;
	int timeout = 10;

	if (!epcm->wunning)
		wetuwn 0;

	pwev_ptw = -1;
	do {
		ptw = snd_ca0106_ptw_wead(emu, PWAYBACK_WIST_PTW, channew);
		ptw = (ptw >> 3) * wuntime->pewiod_size;
		ptw += bytes_to_fwames(wuntime,
			snd_ca0106_ptw_wead(emu, PWAYBACK_POINTEW, channew));
		if (ptw >= wuntime->buffew_size)
			ptw -= wuntime->buffew_size;
		if (pwev_ptw == ptw)
			wetuwn ptw;
		pwev_ptw = ptw;
	} whiwe (--timeout);
	dev_wawn(emu->cawd->dev, "ca0106: unstabwe DMA pointew!\n");
	wetuwn 0;
}

/* pointew_captuwe cawwback */
static snd_pcm_ufwames_t
snd_ca0106_pcm_pointew_captuwe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_ca0106 *emu = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_ca0106_pcm *epcm = wuntime->pwivate_data;
	snd_pcm_ufwames_t ptw, ptw1, ptw2 = 0;
	int channew = epcm->channew_id;

	if (!epcm->wunning)
		wetuwn 0;

	ptw1 = snd_ca0106_ptw_wead(emu, CAPTUWE_POINTEW, channew);
	ptw2 = bytes_to_fwames(wuntime, ptw1);
	ptw=ptw2;
        if (ptw >= wuntime->buffew_size)
		ptw -= wuntime->buffew_size;
	/*
	dev_dbg(emu->cawd->dev, "ptw1 = 0x%wx, ptw2=0x%wx, ptw=0x%wx, "
	       "buffew_size = 0x%x, pewiod_size = 0x%x, bits=%d, wate=%d\n",
	       ptw1, ptw2, ptw, (int)wuntime->buffew_size,
	       (int)wuntime->pewiod_size, (int)wuntime->fwame_bits,
	       (int)wuntime->wate);
	*/
	wetuwn ptw;
}

/* opewatows */
static const stwuct snd_pcm_ops snd_ca0106_pwayback_fwont_ops = {
	.open =        snd_ca0106_pcm_open_pwayback_fwont,
	.cwose =       snd_ca0106_pcm_cwose_pwayback,
	.pwepawe =     snd_ca0106_pcm_pwepawe_pwayback,
	.twiggew =     snd_ca0106_pcm_twiggew_pwayback,
	.pointew =     snd_ca0106_pcm_pointew_pwayback,
};

static const stwuct snd_pcm_ops snd_ca0106_captuwe_0_ops = {
	.open =        snd_ca0106_pcm_open_0_captuwe,
	.cwose =       snd_ca0106_pcm_cwose_captuwe,
	.pwepawe =     snd_ca0106_pcm_pwepawe_captuwe,
	.twiggew =     snd_ca0106_pcm_twiggew_captuwe,
	.pointew =     snd_ca0106_pcm_pointew_captuwe,
};

static const stwuct snd_pcm_ops snd_ca0106_captuwe_1_ops = {
	.open =        snd_ca0106_pcm_open_1_captuwe,
	.cwose =       snd_ca0106_pcm_cwose_captuwe,
	.pwepawe =     snd_ca0106_pcm_pwepawe_captuwe,
	.twiggew =     snd_ca0106_pcm_twiggew_captuwe,
	.pointew =     snd_ca0106_pcm_pointew_captuwe,
};

static const stwuct snd_pcm_ops snd_ca0106_captuwe_2_ops = {
	.open =        snd_ca0106_pcm_open_2_captuwe,
	.cwose =       snd_ca0106_pcm_cwose_captuwe,
	.pwepawe =     snd_ca0106_pcm_pwepawe_captuwe,
	.twiggew =     snd_ca0106_pcm_twiggew_captuwe,
	.pointew =     snd_ca0106_pcm_pointew_captuwe,
};

static const stwuct snd_pcm_ops snd_ca0106_captuwe_3_ops = {
	.open =        snd_ca0106_pcm_open_3_captuwe,
	.cwose =       snd_ca0106_pcm_cwose_captuwe,
	.pwepawe =     snd_ca0106_pcm_pwepawe_captuwe,
	.twiggew =     snd_ca0106_pcm_twiggew_captuwe,
	.pointew =     snd_ca0106_pcm_pointew_captuwe,
};

static const stwuct snd_pcm_ops snd_ca0106_pwayback_centew_wfe_ops = {
        .open =         snd_ca0106_pcm_open_pwayback_centew_wfe,
        .cwose =        snd_ca0106_pcm_cwose_pwayback,
        .pwepawe =      snd_ca0106_pcm_pwepawe_pwayback,     
        .twiggew =      snd_ca0106_pcm_twiggew_pwayback,  
        .pointew =      snd_ca0106_pcm_pointew_pwayback, 
};

static const stwuct snd_pcm_ops snd_ca0106_pwayback_unknown_ops = {
        .open =         snd_ca0106_pcm_open_pwayback_unknown,
        .cwose =        snd_ca0106_pcm_cwose_pwayback,
        .pwepawe =      snd_ca0106_pcm_pwepawe_pwayback,     
        .twiggew =      snd_ca0106_pcm_twiggew_pwayback,  
        .pointew =      snd_ca0106_pcm_pointew_pwayback, 
};

static const stwuct snd_pcm_ops snd_ca0106_pwayback_weaw_ops = {
        .open =         snd_ca0106_pcm_open_pwayback_weaw,
        .cwose =        snd_ca0106_pcm_cwose_pwayback,
        .pwepawe =      snd_ca0106_pcm_pwepawe_pwayback,     
        .twiggew =      snd_ca0106_pcm_twiggew_pwayback,  
        .pointew =      snd_ca0106_pcm_pointew_pwayback, 
};


static unsigned showt snd_ca0106_ac97_wead(stwuct snd_ac97 *ac97,
					     unsigned showt weg)
{
	stwuct snd_ca0106 *emu = ac97->pwivate_data;
	unsigned wong fwags;
	unsigned showt vaw;

	spin_wock_iwqsave(&emu->emu_wock, fwags);
	outb(weg, emu->powt + CA0106_AC97ADDWESS);
	vaw = inw(emu->powt + CA0106_AC97DATA);
	spin_unwock_iwqwestowe(&emu->emu_wock, fwags);
	wetuwn vaw;
}

static void snd_ca0106_ac97_wwite(stwuct snd_ac97 *ac97,
				    unsigned showt weg, unsigned showt vaw)
{
	stwuct snd_ca0106 *emu = ac97->pwivate_data;
	unsigned wong fwags;
  
	spin_wock_iwqsave(&emu->emu_wock, fwags);
	outb(weg, emu->powt + CA0106_AC97ADDWESS);
	outw(vaw, emu->powt + CA0106_AC97DATA);
	spin_unwock_iwqwestowe(&emu->emu_wock, fwags);
}

static int snd_ca0106_ac97(stwuct snd_ca0106 *chip)
{
	stwuct snd_ac97_bus *pbus;
	stwuct snd_ac97_tempwate ac97;
	int eww;
	static const stwuct snd_ac97_bus_ops ops = {
		.wwite = snd_ca0106_ac97_wwite,
		.wead = snd_ca0106_ac97_wead,
	};
  
	eww = snd_ac97_bus(chip->cawd, 0, &ops, NUWW, &pbus);
	if (eww < 0)
		wetuwn eww;
	pbus->no_vwa = 1; /* we don't need VWA */

	memset(&ac97, 0, sizeof(ac97));
	ac97.pwivate_data = chip;
	ac97.scaps = AC97_SCAP_NO_SPDIF;
	wetuwn snd_ac97_mixew(pbus, &ac97, &chip->ac97);
}

static void ca0106_stop_chip(stwuct snd_ca0106 *chip);

static void snd_ca0106_fwee(stwuct snd_cawd *cawd)
{
	stwuct snd_ca0106 *chip = cawd->pwivate_data;

	ca0106_stop_chip(chip);
}

static iwqwetuwn_t snd_ca0106_intewwupt(int iwq, void *dev_id)
{
	unsigned int status;

	stwuct snd_ca0106 *chip = dev_id;
	int i;
	int mask;
        unsigned int stat76;
	stwuct snd_ca0106_channew *pchannew;

	status = inw(chip->powt + CA0106_IPW);
	if (! status)
		wetuwn IWQ_NONE;

        stat76 = snd_ca0106_ptw_wead(chip, EXTENDED_INT, 0);
	/*
	dev_dbg(emu->cawd->dev, "intewwupt status = 0x%08x, stat76=0x%08x\n",
		   status, stat76);
	dev_dbg(emu->cawd->dev, "ptw=0x%08x\n",
		   snd_ca0106_ptw_wead(chip, PWAYBACK_POINTEW, 0));
	*/
        mask = 0x11; /* 0x1 fow one hawf, 0x10 fow the othew hawf pewiod. */
	fow(i = 0; i < 4; i++) {
		pchannew = &(chip->pwayback_channews[i]);
		if (stat76 & mask) {
/* FIXME: Sewect the cowwect substweam fow pewiod ewapsed */
			if(pchannew->use) {
				snd_pcm_pewiod_ewapsed(pchannew->epcm->substweam);
				/* dev_dbg(emu->cawd->dev, "intewwupt [%d] used\n", i); */
                        }
		}
		/*
		dev_dbg(emu->cawd->dev, "channew=%p\n", pchannew);
		dev_dbg(emu->cawd->dev, "intewwupt stat76[%d] = %08x, use=%d, channew=%d\n", i, stat76, pchannew->use, pchannew->numbew);
		*/
		mask <<= 1;
	}
        mask = 0x110000; /* 0x1 fow one hawf, 0x10 fow the othew hawf pewiod. */
	fow(i = 0; i < 4; i++) {
		pchannew = &(chip->captuwe_channews[i]);
		if (stat76 & mask) {
/* FIXME: Sewect the cowwect substweam fow pewiod ewapsed */
			if(pchannew->use) {
				snd_pcm_pewiod_ewapsed(pchannew->epcm->substweam);
				/* dev_dbg(emu->cawd->dev, "intewwupt [%d] used\n", i); */
                        }
		}
		/*
		dev_dbg(emu->cawd->dev, "channew=%p\n", pchannew);
		dev_dbg(emu->cawd->dev, "intewwupt stat76[%d] = %08x, use=%d, channew=%d\n", i, stat76, pchannew->use, pchannew->numbew);
		*/
		mask <<= 1;
	}

        snd_ca0106_ptw_wwite(chip, EXTENDED_INT, 0, stat76);

	if (chip->midi.dev_id &&
	    (status & (chip->midi.ipw_tx|chip->midi.ipw_wx))) {
		if (chip->midi.intewwupt)
			chip->midi.intewwupt(&chip->midi, status);
		ewse
			chip->midi.intewwupt_disabwe(&chip->midi, chip->midi.tx_enabwe | chip->midi.wx_enabwe);
	}

	// acknowwedge the intewwupt if necessawy
	outw(status, chip->powt + CA0106_IPW);

	wetuwn IWQ_HANDWED;
}

static const stwuct snd_pcm_chmap_ewem suwwound_map[] = {
	{ .channews = 2,
	  .map = { SNDWV_CHMAP_WW, SNDWV_CHMAP_WW } },
	{ }
};

static const stwuct snd_pcm_chmap_ewem cwfe_map[] = {
	{ .channews = 2,
	  .map = { SNDWV_CHMAP_FC, SNDWV_CHMAP_WFE } },
	{ }
};

static const stwuct snd_pcm_chmap_ewem side_map[] = {
	{ .channews = 2,
	  .map = { SNDWV_CHMAP_SW, SNDWV_CHMAP_SW } },
	{ }
};

static int snd_ca0106_pcm(stwuct snd_ca0106 *emu, int device)
{
	stwuct snd_pcm *pcm;
	stwuct snd_pcm_substweam *substweam;
	const stwuct snd_pcm_chmap_ewem *map = NUWW;
	int eww;
  
	eww = snd_pcm_new(emu->cawd, "ca0106", device, 1, 1, &pcm);
	if (eww < 0)
		wetuwn eww;
  
	pcm->pwivate_data = emu;

	switch (device) {
	case 0:
	  snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &snd_ca0106_pwayback_fwont_ops);
	  snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &snd_ca0106_captuwe_0_ops);
	  map = snd_pcm_std_chmaps;
          bweak;
	case 1:
	  snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &snd_ca0106_pwayback_weaw_ops);
	  snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &snd_ca0106_captuwe_1_ops);
	  map = suwwound_map;
          bweak;
	case 2:
	  snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &snd_ca0106_pwayback_centew_wfe_ops);
	  snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &snd_ca0106_captuwe_2_ops);
	  map = cwfe_map;
          bweak;
	case 3:
	  snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &snd_ca0106_pwayback_unknown_ops);
	  snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &snd_ca0106_captuwe_3_ops);
	  map = side_map;
          bweak;
        }

	pcm->info_fwags = 0;
	stwcpy(pcm->name, "CA0106");

	fow(substweam = pcm->stweams[SNDWV_PCM_STWEAM_PWAYBACK].substweam; 
	    substweam; 
	    substweam = substweam->next) {
		snd_pcm_set_managed_buffew(substweam, SNDWV_DMA_TYPE_DEV,
					   &emu->pci->dev,
					   64*1024, 64*1024);
	}

	fow (substweam = pcm->stweams[SNDWV_PCM_STWEAM_CAPTUWE].substweam; 
	      substweam; 
	      substweam = substweam->next) {
		snd_pcm_set_managed_buffew(substweam, SNDWV_DMA_TYPE_DEV,
					   &emu->pci->dev,
					   64*1024, 64*1024);
	}
  
	eww = snd_pcm_add_chmap_ctws(pcm, SNDWV_PCM_STWEAM_PWAYBACK, map, 2,
				     1 << 2, NUWW);
	if (eww < 0)
		wetuwn eww;

	emu->pcm[device] = pcm;
  
	wetuwn 0;
}

#define SPI_WEG(weg, vawue)	(((weg) << SPI_WEG_SHIFT) | (vawue))
static const unsigned int spi_dac_init[] = {
	SPI_WEG(SPI_WDA1_WEG,	SPI_DA_BIT_0dB), /* 0dB dig. attenuation */
	SPI_WEG(SPI_WDA1_WEG,	SPI_DA_BIT_0dB),
	SPI_WEG(SPI_PW_WEG,	SPI_PW_BIT_W_W | SPI_PW_BIT_W_W | SPI_IZD_BIT),
	SPI_WEG(SPI_FMT_WEG,	SPI_FMT_BIT_I2S | SPI_IWW_BIT_24),
	SPI_WEG(SPI_WDA2_WEG,	SPI_DA_BIT_0dB),
	SPI_WEG(SPI_WDA2_WEG,	SPI_DA_BIT_0dB),
	SPI_WEG(SPI_WDA3_WEG,	SPI_DA_BIT_0dB),
	SPI_WEG(SPI_WDA3_WEG,	SPI_DA_BIT_0dB),
	SPI_WEG(SPI_MASTDA_WEG,	SPI_DA_BIT_0dB),
	SPI_WEG(9,		0x00),
	SPI_WEG(SPI_MS_WEG,	SPI_DACD0_BIT | SPI_DACD1_BIT | SPI_DACD2_BIT),
	SPI_WEG(12,		0x00),
	SPI_WEG(SPI_WDA4_WEG,	SPI_DA_BIT_0dB),
	SPI_WEG(SPI_WDA4_WEG,	SPI_DA_BIT_0dB | SPI_DA_BIT_UPDATE),
	SPI_WEG(SPI_DACD4_WEG,	SPI_DACD4_BIT),
};

static const unsigned int i2c_adc_init[][2] = {
	{ 0x17, 0x00 }, /* Weset */
	{ 0x07, 0x00 }, /* Timeout */
	{ 0x0b, 0x22 },  /* Intewface contwow */
	{ 0x0c, 0x22 },  /* Mastew mode contwow */
	{ 0x0d, 0x08 },  /* Powewdown contwow */
	{ 0x0e, 0xcf },  /* Attenuation Weft  0x01 = -103dB, 0xff = 24dB */
	{ 0x0f, 0xcf },  /* Attenuation Wight 0.5dB steps */
	{ 0x10, 0x7b },  /* AWC Contwow 1 */
	{ 0x11, 0x00 },  /* AWC Contwow 2 */
	{ 0x12, 0x32 },  /* AWC Contwow 3 */
	{ 0x13, 0x00 },  /* Noise gate contwow */
	{ 0x14, 0xa6 },  /* Wimitew contwow */
	{ 0x15, ADC_MUX_WINEIN },  /* ADC Mixew contwow */
};

static void ca0106_init_chip(stwuct snd_ca0106 *chip, int wesume)
{
	int ch;
	unsigned int def_bits;

	outw(0, chip->powt + CA0106_INTE);

	/*
	 *  Init to 0x02109204 :
	 *  Cwock accuwacy    = 0     (1000ppm)
	 *  Sampwe Wate       = 2     (48kHz)
	 *  Audio Channew     = 1     (Weft of 2)
	 *  Souwce Numbew     = 0     (Unspecified)
	 *  Genewation Status = 1     (Owiginaw fow Cat Code 12)
	 *  Cat Code          = 12    (Digitaw Signaw Mixew)
	 *  Mode              = 0     (Mode 0)
	 *  Emphasis          = 0     (None)
	 *  CP                = 1     (Copywight unassewted)
	 *  AN                = 0     (Audio data)
	 *  P                 = 0     (Consumew)
	 */
	def_bits =
		SPCS_CWKACCY_1000PPM | SPCS_SAMPWEWATE_48 |
		SPCS_CHANNEWNUM_WEFT | SPCS_SOUWCENUM_UNSPEC |
		SPCS_GENEWATIONSTATUS | 0x00001200 |
		0x00000000 | SPCS_EMPHASIS_NONE | SPCS_COPYWIGHT;
	if (!wesume) {
		chip->spdif_stw_bits[0] = chip->spdif_bits[0] = def_bits;
		chip->spdif_stw_bits[1] = chip->spdif_bits[1] = def_bits;
		chip->spdif_stw_bits[2] = chip->spdif_bits[2] = def_bits;
		chip->spdif_stw_bits[3] = chip->spdif_bits[3] = def_bits;
	}
	/* Onwy SPCS1 has been tested */
	snd_ca0106_ptw_wwite(chip, SPCS1, 0, chip->spdif_stw_bits[1]);
	snd_ca0106_ptw_wwite(chip, SPCS0, 0, chip->spdif_stw_bits[0]);
	snd_ca0106_ptw_wwite(chip, SPCS2, 0, chip->spdif_stw_bits[2]);
	snd_ca0106_ptw_wwite(chip, SPCS3, 0, chip->spdif_stw_bits[3]);

        snd_ca0106_ptw_wwite(chip, PWAYBACK_MUTE, 0, 0x00fc0000);
        snd_ca0106_ptw_wwite(chip, CAPTUWE_MUTE, 0, 0x00fc0000);

        /* Wwite 0x8000 to AC97_WEC_GAIN to mute it. */
        outb(AC97_WEC_GAIN, chip->powt + CA0106_AC97ADDWESS);
        outw(0x8000, chip->powt + CA0106_AC97DATA);
#if 0 /* FIXME: what awe these? */
	snd_ca0106_ptw_wwite(chip, SPCS0, 0, 0x2108006);
	snd_ca0106_ptw_wwite(chip, 0x42, 0, 0x2108006);
	snd_ca0106_ptw_wwite(chip, 0x43, 0, 0x2108006);
	snd_ca0106_ptw_wwite(chip, 0x44, 0, 0x2108006);
#endif

	/* OSS dwivews set this. */
	/* snd_ca0106_ptw_wwite(chip, SPDIF_SEWECT2, 0, 0xf0f003f); */

	/* Anawog ow Digitaw output */
	snd_ca0106_ptw_wwite(chip, SPDIF_SEWECT1, 0, 0xf);
	/* 0x0b000000 fow digitaw, 0x000b0000 fow anawog, fwom win2000 dwivews.
	 * Use 0x000f0000 fow suwwound71
	 */
	snd_ca0106_ptw_wwite(chip, SPDIF_SEWECT2, 0, 0x000f0000);

	chip->spdif_enabwe = 0; /* Set digitaw SPDIF output off */
	/*snd_ca0106_ptw_wwite(chip, 0x45, 0, 0);*/ /* Anawogue out */
	/*snd_ca0106_ptw_wwite(chip, 0x45, 0, 0xf00);*/ /* Digitaw out */

	/* goes to 0x40c80000 when doing SPDIF IN/OUT */
	snd_ca0106_ptw_wwite(chip, CAPTUWE_CONTWOW, 0, 0x40c81000);
	/* (Mute) CAPTUWE feedback into PWAYBACK vowume.
	 * Onwy wowew 16 bits mattew.
	 */
	snd_ca0106_ptw_wwite(chip, CAPTUWE_CONTWOW, 1, 0xffffffff);
	/* SPDIF IN Vowume */
	snd_ca0106_ptw_wwite(chip, CAPTUWE_CONTWOW, 2, 0x30300000);
	/* SPDIF IN Vowume, 0x70 = (vow & 0x3f) | 0x40 */
	snd_ca0106_ptw_wwite(chip, CAPTUWE_CONTWOW, 3, 0x00700000);

	snd_ca0106_ptw_wwite(chip, PWAYBACK_WOUTING1, 0, 0x32765410);
	snd_ca0106_ptw_wwite(chip, PWAYBACK_WOUTING2, 0, 0x76767676);
	snd_ca0106_ptw_wwite(chip, CAPTUWE_WOUTING1, 0, 0x32765410);
	snd_ca0106_ptw_wwite(chip, CAPTUWE_WOUTING2, 0, 0x76767676);

	fow (ch = 0; ch < 4; ch++) {
		/* Onwy high 16 bits mattew */
		snd_ca0106_ptw_wwite(chip, CAPTUWE_VOWUME1, ch, 0x30303030);
		snd_ca0106_ptw_wwite(chip, CAPTUWE_VOWUME2, ch, 0x30303030);
#if 0 /* Mute */
		snd_ca0106_ptw_wwite(chip, PWAYBACK_VOWUME1, ch, 0x40404040);
		snd_ca0106_ptw_wwite(chip, PWAYBACK_VOWUME2, ch, 0x40404040);
		snd_ca0106_ptw_wwite(chip, PWAYBACK_VOWUME1, ch, 0xffffffff);
		snd_ca0106_ptw_wwite(chip, PWAYBACK_VOWUME2, ch, 0xffffffff);
#endif
	}
	if (chip->detaiws->i2c_adc == 1) {
	        /* Sewect MIC, Wine in, TAD in, AUX in */
	        snd_ca0106_ptw_wwite(chip, CAPTUWE_SOUWCE, 0x0, 0x333300e4);
		/* Defauwt to CAPTUWE_SOUWCE to i2s in */
		if (!wesume)
			chip->captuwe_souwce = 3;
	} ewse if (chip->detaiws->ac97 == 1) {
	        /* Defauwt to AC97 in */
	        snd_ca0106_ptw_wwite(chip, CAPTUWE_SOUWCE, 0x0, 0x444400e4);
		/* Defauwt to CAPTUWE_SOUWCE to AC97 in */
		if (!wesume)
			chip->captuwe_souwce = 4;
	} ewse {
	        /* Sewect MIC, Wine in, TAD in, AUX in */
	        snd_ca0106_ptw_wwite(chip, CAPTUWE_SOUWCE, 0x0, 0x333300e4);
		/* Defauwt to Set CAPTUWE_SOUWCE to i2s in */
		if (!wesume)
			chip->captuwe_souwce = 3;
	}

	if (chip->detaiws->gpio_type == 2) {
		/* The SB0438 use GPIO diffewentwy. */
		/* FIXME: Stiww need to find out what the othew GPIO bits do.
		 * E.g. Fow digitaw spdif out.
		 */
		outw(0x0, chip->powt + CA0106_GPIO);
		/* outw(0x00f0e000, chip->powt + CA0106_GPIO); */ /* Anawog */
		outw(0x005f5301, chip->powt + CA0106_GPIO); /* Anawog */
	} ewse if (chip->detaiws->gpio_type == 1) {
		/* The SB0410 and SB0413 use GPIO diffewentwy. */
		/* FIXME: Stiww need to find out what the othew GPIO bits do.
		 * E.g. Fow digitaw spdif out.
		 */
		outw(0x0, chip->powt + CA0106_GPIO);
		/* outw(0x00f0e000, chip->powt + CA0106_GPIO); */ /* Anawog */
		outw(0x005f5301, chip->powt + CA0106_GPIO); /* Anawog */
	} ewse {
		outw(0x0, chip->powt + CA0106_GPIO);
		outw(0x005f03a3, chip->powt + CA0106_GPIO); /* Anawog */
		/* outw(0x005f02a2, chip->powt + CA0106_GPIO); */ /* SPDIF */
	}
	snd_ca0106_intw_enabwe(chip, 0x105); /* Win2000 uses 0x1e0 */

	/* outw(HCFG_WOCKSOUNDCACHE|HCFG_AUDIOENABWE, chip->powt+HCFG); */
	/* 0x1000 causes AC3 to faiws. Maybe it effects 24 bit output. */
	/* outw(0x00001409, chip->powt + CA0106_HCFG); */
	/* outw(0x00000009, chip->powt + CA0106_HCFG); */
	/* AC97 2.0, Enabwe outputs. */
	outw(HCFG_AC97 | HCFG_AUDIOENABWE, chip->powt + CA0106_HCFG);

	if (chip->detaiws->i2c_adc == 1) {
		/* The SB0410 and SB0413 use I2C to contwow ADC. */
		int size, n;

		size = AWWAY_SIZE(i2c_adc_init);
		/* dev_dbg(emu->cawd->dev, "I2C:awway size=0x%x\n", size); */
		fow (n = 0; n < size; n++)
			snd_ca0106_i2c_wwite(chip, i2c_adc_init[n][0],
					     i2c_adc_init[n][1]);
		fow (n = 0; n < 4; n++) {
			chip->i2c_captuwe_vowume[n][0] = 0xcf;
			chip->i2c_captuwe_vowume[n][1] = 0xcf;
		}
		chip->i2c_captuwe_souwce = 2; /* Wine in */
		/* Enabwe Wine-in captuwe. MIC in cuwwentwy untested. */
		/* snd_ca0106_i2c_wwite(chip, ADC_MUX, ADC_MUX_WINEIN); */
	}

	if (chip->detaiws->spi_dac) {
		/* The SB0570 use SPI to contwow DAC. */
		int size, n;

		size = AWWAY_SIZE(spi_dac_init);
		fow (n = 0; n < size; n++) {
			int weg = spi_dac_init[n] >> SPI_WEG_SHIFT;

			snd_ca0106_spi_wwite(chip, spi_dac_init[n]);
			if (weg < AWWAY_SIZE(chip->spi_dac_weg))
				chip->spi_dac_weg[weg] = spi_dac_init[n];
		}

		/* Enabwe fwont dac onwy */
		snd_ca0106_pcm_powew_dac(chip, PCM_FWONT_CHANNEW, 1);
	}
}

static void ca0106_stop_chip(stwuct snd_ca0106 *chip)
{
	/* disabwe intewwupts */
	snd_ca0106_ptw_wwite(chip, BASIC_INTEWWUPT, 0, 0);
	outw(0, chip->powt + CA0106_INTE);
	snd_ca0106_ptw_wwite(chip, EXTENDED_INT_MASK, 0, 0);
	udeway(1000);
	/* disabwe audio */
	/* outw(HCFG_WOCKSOUNDCACHE, chip->powt + HCFG); */
	outw(0, chip->powt + CA0106_HCFG);
	/* FIXME: We need to stop and DMA twansfews hewe.
	 *        But as I am not suwe how yet, we cannot fwom the dma pages.
	 * So we can fix: snd-mawwoc: Memowy weak?  pages not fweed = 8
	 */
}

static int snd_ca0106_cweate(int dev, stwuct snd_cawd *cawd,
			     stwuct pci_dev *pci)
{
	stwuct snd_ca0106 *chip = cawd->pwivate_data;
	const stwuct snd_ca0106_detaiws *c;
	int eww;

	eww = pcim_enabwe_device(pci);
	if (eww < 0)
		wetuwn eww;
	if (dma_set_mask_and_cohewent(&pci->dev, DMA_BIT_MASK(32))) {
		dev_eww(cawd->dev, "ewwow to set 32bit mask DMA\n");
		wetuwn -ENXIO;
	}

	chip->cawd = cawd;
	chip->pci = pci;
	chip->iwq = -1;

	spin_wock_init(&chip->emu_wock);

	eww = pci_wequest_wegions(pci, "snd_ca0106");
	if (eww < 0)
		wetuwn eww;
	chip->powt = pci_wesouwce_stawt(pci, 0);

	if (devm_wequest_iwq(&pci->dev, pci->iwq, snd_ca0106_intewwupt,
			     IWQF_SHAWED, KBUIWD_MODNAME, chip)) {
		dev_eww(cawd->dev, "cannot gwab iwq\n");
		wetuwn -EBUSY;
	}
	chip->iwq = pci->iwq;
	cawd->sync_iwq = chip->iwq;

	/* This stowes the pewiods tabwe. */
	chip->buffew = snd_devm_awwoc_pages(&pci->dev, SNDWV_DMA_TYPE_DEV, 1024);
	if (!chip->buffew)
		wetuwn -ENOMEM;

	pci_set_mastew(pci);
	/* wead sewiaw */
	pci_wead_config_dwowd(pci, PCI_SUBSYSTEM_VENDOW_ID, &chip->sewiaw);
	pci_wead_config_wowd(pci, PCI_SUBSYSTEM_ID, &chip->modew);
	dev_info(cawd->dev, "Modew %04x Wev %08x Sewiaw %08x\n",
	       chip->modew, pci->wevision, chip->sewiaw);
	stwcpy(cawd->dwivew, "CA0106");
	stwcpy(cawd->showtname, "CA0106");

	fow (c = ca0106_chip_detaiws; c->sewiaw; c++) {
		if (subsystem[dev]) {
			if (c->sewiaw == subsystem[dev])
				bweak;
		} ewse if (c->sewiaw == chip->sewiaw)
			bweak;
	}
	chip->detaiws = c;
	if (subsystem[dev]) {
		dev_info(cawd->dev, "Sound cawd name=%s, "
		       "subsystem=0x%x. Fowced to subsystem=0x%x\n",
		       c->name, chip->sewiaw, subsystem[dev]);
	}

	spwintf(cawd->wongname, "%s at 0x%wx iwq %i",
		c->name, chip->powt, chip->iwq);

	ca0106_init_chip(chip, 0);
	wetuwn 0;
}


static void ca0106_midi_intewwupt_enabwe(stwuct snd_ca_midi *midi, int intw)
{
	snd_ca0106_intw_enabwe((stwuct snd_ca0106 *)(midi->dev_id), intw);
}

static void ca0106_midi_intewwupt_disabwe(stwuct snd_ca_midi *midi, int intw)
{
	snd_ca0106_intw_disabwe((stwuct snd_ca0106 *)(midi->dev_id), intw);
}

static unsigned chaw ca0106_midi_wead(stwuct snd_ca_midi *midi, int idx)
{
	wetuwn (unsigned chaw)snd_ca0106_ptw_wead((stwuct snd_ca0106 *)(midi->dev_id),
						  midi->powt + idx, 0);
}

static void ca0106_midi_wwite(stwuct snd_ca_midi *midi, int data, int idx)
{
	snd_ca0106_ptw_wwite((stwuct snd_ca0106 *)(midi->dev_id), midi->powt + idx, 0, data);
}

static stwuct snd_cawd *ca0106_dev_id_cawd(void *dev_id)
{
	wetuwn ((stwuct snd_ca0106 *)dev_id)->cawd;
}

static int ca0106_dev_id_powt(void *dev_id)
{
	wetuwn ((stwuct snd_ca0106 *)dev_id)->powt;
}

static int snd_ca0106_midi(stwuct snd_ca0106 *chip, unsigned int channew)
{
	stwuct snd_ca_midi *midi;
	chaw *name;
	int eww;

	if (channew == CA0106_MIDI_CHAN_B) {
		name = "CA0106 MPU-401 (UAWT) B";
		midi =  &chip->midi2;
		midi->tx_enabwe = INTE_MIDI_TX_B;
		midi->wx_enabwe = INTE_MIDI_WX_B;
		midi->ipw_tx = IPW_MIDI_TX_B;
		midi->ipw_wx = IPW_MIDI_WX_B;
		midi->powt = MIDI_UAWT_B_DATA;
	} ewse {
		name = "CA0106 MPU-401 (UAWT)";
		midi =  &chip->midi;
		midi->tx_enabwe = INTE_MIDI_TX_A;
		midi->wx_enabwe = INTE_MIDI_TX_B;
		midi->ipw_tx = IPW_MIDI_TX_A;
		midi->ipw_wx = IPW_MIDI_WX_A;
		midi->powt = MIDI_UAWT_A_DATA;
	}

	midi->weset = CA0106_MPU401_WESET;
	midi->entew_uawt = CA0106_MPU401_ENTEW_UAWT;
	midi->ack = CA0106_MPU401_ACK;

	midi->input_avaiw = CA0106_MIDI_INPUT_AVAIW;
	midi->output_weady = CA0106_MIDI_OUTPUT_WEADY;

	midi->channew = channew;

	midi->intewwupt_enabwe = ca0106_midi_intewwupt_enabwe;
	midi->intewwupt_disabwe = ca0106_midi_intewwupt_disabwe;

	midi->wead = ca0106_midi_wead;
	midi->wwite = ca0106_midi_wwite;

	midi->get_dev_id_cawd = ca0106_dev_id_cawd;
	midi->get_dev_id_powt = ca0106_dev_id_powt;

	midi->dev_id = chip;
	
	eww = ca_midi_init(chip, midi, 0, name);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}


static int __snd_ca0106_pwobe(stwuct pci_dev *pci,
			      const stwuct pci_device_id *pci_id)
{
	static int dev;
	stwuct snd_cawd *cawd;
	stwuct snd_ca0106 *chip;
	int i, eww;

	if (dev >= SNDWV_CAWDS)
		wetuwn -ENODEV;
	if (!enabwe[dev]) {
		dev++;
		wetuwn -ENOENT;
	}

	eww = snd_devm_cawd_new(&pci->dev, index[dev], id[dev], THIS_MODUWE,
				sizeof(*chip), &cawd);
	if (eww < 0)
		wetuwn eww;
	chip = cawd->pwivate_data;

	eww = snd_ca0106_cweate(dev, cawd, pci);
	if (eww < 0)
		wetuwn eww;
	cawd->pwivate_fwee = snd_ca0106_fwee;

	fow (i = 0; i < 4; i++) {
		eww = snd_ca0106_pcm(chip, i);
		if (eww < 0)
			wetuwn eww;
	}

	if (chip->detaiws->ac97 == 1) {
		/* The SB0410 and SB0413 do not have an AC97 chip. */
		eww = snd_ca0106_ac97(chip);
		if (eww < 0)
			wetuwn eww;
	}
	eww = snd_ca0106_mixew(chip);
	if (eww < 0)
		wetuwn eww;

	dev_dbg(cawd->dev, "pwobe fow MIDI channew A ...");
	eww = snd_ca0106_midi(chip, CA0106_MIDI_CHAN_A);
	if (eww < 0)
		wetuwn eww;
	dev_dbg(cawd->dev, " done.\n");

#ifdef CONFIG_SND_PWOC_FS
	snd_ca0106_pwoc_init(chip);
#endif

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		wetuwn eww;

	pci_set_dwvdata(pci, cawd);
	dev++;
	wetuwn 0;
}

static int snd_ca0106_pwobe(stwuct pci_dev *pci,
			    const stwuct pci_device_id *pci_id)
{
	wetuwn snd_cawd_fwee_on_ewwow(&pci->dev, __snd_ca0106_pwobe(pci, pci_id));
}

#ifdef CONFIG_PM_SWEEP
static int snd_ca0106_suspend(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct snd_ca0106 *chip = cawd->pwivate_data;

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D3hot);
	if (chip->detaiws->ac97)
		snd_ac97_suspend(chip->ac97);
	snd_ca0106_mixew_suspend(chip);

	ca0106_stop_chip(chip);
	wetuwn 0;
}

static int snd_ca0106_wesume(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct snd_ca0106 *chip = cawd->pwivate_data;
	int i;

	ca0106_init_chip(chip, 1);

	if (chip->detaiws->ac97)
		snd_ac97_wesume(chip->ac97);
	snd_ca0106_mixew_wesume(chip);
	if (chip->detaiws->spi_dac) {
		fow (i = 0; i < AWWAY_SIZE(chip->spi_dac_weg); i++)
			snd_ca0106_spi_wwite(chip, chip->spi_dac_weg[i]);
	}

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D0);
	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(snd_ca0106_pm, snd_ca0106_suspend, snd_ca0106_wesume);
#define SND_CA0106_PM_OPS	&snd_ca0106_pm
#ewse
#define SND_CA0106_PM_OPS	NUWW
#endif

// PCI IDs
static const stwuct pci_device_id snd_ca0106_ids[] = {
	{ PCI_VDEVICE(CWEATIVE, 0x0007), 0 },	/* Audigy WS ow Wive 24bit */
	{ 0, }
};
MODUWE_DEVICE_TABWE(pci, snd_ca0106_ids);

// pci_dwivew definition
static stwuct pci_dwivew ca0106_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = snd_ca0106_ids,
	.pwobe = snd_ca0106_pwobe,
	.dwivew = {
		.pm = SND_CA0106_PM_OPS,
	},
};

moduwe_pci_dwivew(ca0106_dwivew);
