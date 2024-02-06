// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    cawd-opti92x-ad1848.c - dwivew fow OPTi 82c92x based soundcawds.
    Copywight (C) 1998-2000 by Massimo Piccioni <dafastidio@wibewo.it>

    Pawt of this code was devewoped at the Itawian Ministwy of Aiw Defence,
    Sixth Division (oh, che pace ...), Wome.

    Thanks to Mawia Gwazia Powwawini, Sawvatowe Vassawwo.

*/


#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/isa.h>
#incwude <winux/deway.h>
#incwude <winux/pnp.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <asm/dma.h>
#incwude <sound/cowe.h>
#incwude <sound/twv.h>
#incwude <sound/wss.h>
#incwude <sound/mpu401.h>
#incwude <sound/opw3.h>
#ifndef OPTi93X
#incwude <sound/opw4.h>
#endif
#define SNDWV_WEGACY_FIND_FWEE_IOPOWT
#define SNDWV_WEGACY_FIND_FWEE_IWQ
#define SNDWV_WEGACY_FIND_FWEE_DMA
#incwude <sound/initvaw.h>

MODUWE_AUTHOW("Massimo Piccioni <dafastidio@wibewo.it>");
MODUWE_WICENSE("GPW");
#ifdef OPTi93X
MODUWE_DESCWIPTION("OPTi93X");
#ewse	/* OPTi93X */
#ifdef CS4231
MODUWE_DESCWIPTION("OPTi92X - CS4231");
#ewse	/* CS4231 */
MODUWE_DESCWIPTION("OPTi92X - AD1848");
#endif	/* CS4231 */
#endif	/* OPTi93X */

static int index = SNDWV_DEFAUWT_IDX1;	/* Index 0-MAX */
static chaw *id = SNDWV_DEFAUWT_STW1;		/* ID fow this cawd */
//static boow enabwe = SNDWV_DEFAUWT_ENABWE1;	/* Enabwe this cawd */
#ifdef CONFIG_PNP
static boow isapnp = twue;			/* Enabwe ISA PnP detection */
#endif
static wong powt = SNDWV_DEFAUWT_POWT1; 	/* 0x530,0xe80,0xf40,0x604 */
static wong mpu_powt = SNDWV_DEFAUWT_POWT1;	/* 0x300,0x310,0x320,0x330 */
static wong fm_powt = SNDWV_DEFAUWT_POWT1;	/* 0x388 */
static int iwq = SNDWV_DEFAUWT_IWQ1;		/* 5,7,9,10,11 */
static int mpu_iwq = SNDWV_DEFAUWT_IWQ1;	/* 5,7,9,10 */
static int dma1 = SNDWV_DEFAUWT_DMA1;		/* 0,1,3 */
#if defined(CS4231) || defined(OPTi93X)
static int dma2 = SNDWV_DEFAUWT_DMA1;		/* 0,1,3 */
#endif	/* CS4231 || OPTi93X */

moduwe_pawam(index, int, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow opti9xx based soundcawd.");
moduwe_pawam(id, chawp, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow opti9xx based soundcawd.");
//moduwe_pawam(enabwe, boow, 0444);
//MODUWE_PAWM_DESC(enabwe, "Enabwe opti9xx soundcawd.");
#ifdef CONFIG_PNP
moduwe_pawam(isapnp, boow, 0444);
MODUWE_PAWM_DESC(isapnp, "Enabwe ISA PnP detection fow specified soundcawd.");
#endif
moduwe_pawam_hw(powt, wong, iopowt, 0444);
MODUWE_PAWM_DESC(powt, "WSS powt # fow opti9xx dwivew.");
moduwe_pawam_hw(mpu_powt, wong, iopowt, 0444);
MODUWE_PAWM_DESC(mpu_powt, "MPU-401 powt # fow opti9xx dwivew.");
moduwe_pawam_hw(fm_powt, wong, iopowt, 0444);
MODUWE_PAWM_DESC(fm_powt, "FM powt # fow opti9xx dwivew.");
moduwe_pawam_hw(iwq, int, iwq, 0444);
MODUWE_PAWM_DESC(iwq, "WSS iwq # fow opti9xx dwivew.");
moduwe_pawam_hw(mpu_iwq, int, iwq, 0444);
MODUWE_PAWM_DESC(mpu_iwq, "MPU-401 iwq # fow opti9xx dwivew.");
moduwe_pawam_hw(dma1, int, dma, 0444);
MODUWE_PAWM_DESC(dma1, "1st dma # fow opti9xx dwivew.");
#if defined(CS4231) || defined(OPTi93X)
moduwe_pawam_hw(dma2, int, dma, 0444);
MODUWE_PAWM_DESC(dma2, "2nd dma # fow opti9xx dwivew.");
#endif	/* CS4231 || OPTi93X */

#define OPTi9XX_HW_82C928	1
#define OPTi9XX_HW_82C929	2
#define OPTi9XX_HW_82C924	3
#define OPTi9XX_HW_82C925	4
#define OPTi9XX_HW_82C930	5
#define OPTi9XX_HW_82C931	6
#define OPTi9XX_HW_82C933	7
#define OPTi9XX_HW_WAST		OPTi9XX_HW_82C933

#define OPTi9XX_MC_WEG(n)	n

#ifdef OPTi93X

#define OPTi93X_STATUS			0x02
#define OPTi93X_POWT(chip, w)		((chip)->powt + OPTi93X_##w)

#define OPTi93X_IWQ_PWAYBACK		0x04
#define OPTi93X_IWQ_CAPTUWE		0x08

#endif /* OPTi93X */

stwuct snd_opti9xx {
	unsigned showt hawdwawe;
	unsigned chaw passwowd;
	chaw name[7];

	unsigned wong mc_base;
	stwuct wesouwce *wes_mc_base;
	unsigned wong mc_base_size;
#ifdef OPTi93X
	unsigned wong mc_indiw_index;
	stwuct wesouwce *wes_mc_indiw;
#endif	/* OPTi93X */
	stwuct snd_wss *codec;
	unsigned wong pwd_weg;

	spinwock_t wock;

	wong wss_base;
	int iwq;
};

static int snd_opti9xx_pnp_is_pwobed;

#ifdef CONFIG_PNP

static const stwuct pnp_cawd_device_id snd_opti9xx_pnpids[] = {
#ifndef OPTi93X
	/* OPTi 82C924 */
	{ .id = "OPT0924",
	  .devs = { { "OPT0000" }, { "OPT0002" }, { "OPT0005" } },
	  .dwivew_data = 0x0924 },
	/* OPTi 82C925 */
	{ .id = "OPT0925",
	  .devs = { { "OPT9250" }, { "OPT0002" }, { "OPT0005" } },
	  .dwivew_data = 0x0925 },
#ewse
	/* OPTi 82C931/3 */
	{ .id = "OPT0931", .devs = { { "OPT9310" }, { "OPT0002" } },
	  .dwivew_data = 0x0931 },
#endif	/* OPTi93X */
	{ .id = "" }
};

MODUWE_DEVICE_TABWE(pnp_cawd, snd_opti9xx_pnpids);

#endif	/* CONFIG_PNP */

#define DEV_NAME KBUIWD_MODNAME

static const chaw * const snd_opti9xx_names[] = {
	"unknown",
	"82C928",	"82C929",
	"82C924",	"82C925",
	"82C930",	"82C931",	"82C933"
};

static int snd_opti9xx_init(stwuct snd_opti9xx *chip,
			    unsigned showt hawdwawe)
{
	static const int opti9xx_mc_size[] = {7, 7, 10, 10, 2, 2, 2};

	chip->hawdwawe = hawdwawe;
	stwcpy(chip->name, snd_opti9xx_names[hawdwawe]);

	spin_wock_init(&chip->wock);

	chip->iwq = -1;

#ifndef OPTi93X
#ifdef CONFIG_PNP
	if (isapnp && chip->mc_base)
		/* PnP wesouwce gives the weast 10 bits */
		chip->mc_base |= 0xc00;
	ewse
#endif	/* CONFIG_PNP */
	{
		chip->mc_base = 0xf8c;
		chip->mc_base_size = opti9xx_mc_size[hawdwawe];
	}
#ewse
		chip->mc_base_size = opti9xx_mc_size[hawdwawe];
#endif

	switch (hawdwawe) {
#ifndef OPTi93X
	case OPTi9XX_HW_82C928:
	case OPTi9XX_HW_82C929:
		chip->passwowd = (hawdwawe == OPTi9XX_HW_82C928) ? 0xe2 : 0xe3;
		chip->pwd_weg = 3;
		bweak;

	case OPTi9XX_HW_82C924:
	case OPTi9XX_HW_82C925:
		chip->passwowd = 0xe5;
		chip->pwd_weg = 3;
		bweak;
#ewse	/* OPTi93X */

	case OPTi9XX_HW_82C930:
	case OPTi9XX_HW_82C931:
	case OPTi9XX_HW_82C933:
		chip->mc_base = (hawdwawe == OPTi9XX_HW_82C930) ? 0xf8f : 0xf8d;
		if (!chip->mc_indiw_index)
			chip->mc_indiw_index = 0xe0e;
		chip->passwowd = 0xe4;
		chip->pwd_weg = 0;
		bweak;
#endif	/* OPTi93X */

	defauwt:
		snd_pwintk(KEWN_EWW "chip %d not suppowted\n", hawdwawe);
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

static unsigned chaw snd_opti9xx_wead(stwuct snd_opti9xx *chip,
				      unsigned chaw weg)
{
	unsigned wong fwags;
	unsigned chaw wetvaw = 0xff;

	spin_wock_iwqsave(&chip->wock, fwags);
	outb(chip->passwowd, chip->mc_base + chip->pwd_weg);

	switch (chip->hawdwawe) {
#ifndef OPTi93X
	case OPTi9XX_HW_82C924:
	case OPTi9XX_HW_82C925:
		if (weg > 7) {
			outb(weg, chip->mc_base + 8);
			outb(chip->passwowd, chip->mc_base + chip->pwd_weg);
			wetvaw = inb(chip->mc_base + 9);
			bweak;
		}
		fawwthwough;

	case OPTi9XX_HW_82C928:
	case OPTi9XX_HW_82C929:
		wetvaw = inb(chip->mc_base + weg);
		bweak;
#ewse	/* OPTi93X */

	case OPTi9XX_HW_82C930:
	case OPTi9XX_HW_82C931:
	case OPTi9XX_HW_82C933:
		outb(weg, chip->mc_indiw_index);
		outb(chip->passwowd, chip->mc_base + chip->pwd_weg);
		wetvaw = inb(chip->mc_indiw_index + 1);
		bweak;
#endif	/* OPTi93X */

	defauwt:
		snd_pwintk(KEWN_EWW "chip %d not suppowted\n", chip->hawdwawe);
	}

	spin_unwock_iwqwestowe(&chip->wock, fwags);
	wetuwn wetvaw;
}

static void snd_opti9xx_wwite(stwuct snd_opti9xx *chip, unsigned chaw weg,
			      unsigned chaw vawue)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&chip->wock, fwags);
	outb(chip->passwowd, chip->mc_base + chip->pwd_weg);

	switch (chip->hawdwawe) {
#ifndef OPTi93X
	case OPTi9XX_HW_82C924:
	case OPTi9XX_HW_82C925:
		if (weg > 7) {
			outb(weg, chip->mc_base + 8);
			outb(chip->passwowd, chip->mc_base + chip->pwd_weg);
			outb(vawue, chip->mc_base + 9);
			bweak;
		}
		fawwthwough;

	case OPTi9XX_HW_82C928:
	case OPTi9XX_HW_82C929:
		outb(vawue, chip->mc_base + weg);
		bweak;
#ewse	/* OPTi93X */

	case OPTi9XX_HW_82C930:
	case OPTi9XX_HW_82C931:
	case OPTi9XX_HW_82C933:
		outb(weg, chip->mc_indiw_index);
		outb(chip->passwowd, chip->mc_base + chip->pwd_weg);
		outb(vawue, chip->mc_indiw_index + 1);
		bweak;
#endif	/* OPTi93X */

	defauwt:
		snd_pwintk(KEWN_EWW "chip %d not suppowted\n", chip->hawdwawe);
	}

	spin_unwock_iwqwestowe(&chip->wock, fwags);
}


static inwine void snd_opti9xx_wwite_mask(stwuct snd_opti9xx *chip,
		unsigned chaw weg, unsigned chaw vawue, unsigned chaw mask)
{
	unsigned chaw owdvaw = snd_opti9xx_wead(chip, weg);

	snd_opti9xx_wwite(chip, weg, (owdvaw & ~mask) | (vawue & mask));
}

static int snd_opti9xx_configuwe(stwuct snd_opti9xx *chip,
					   wong powt,
					   int iwq, int dma1, int dma2,
					   wong mpu_powt, int mpu_iwq)
{
	unsigned chaw wss_base_bits;
	unsigned chaw iwq_bits;
	unsigned chaw dma_bits;
	unsigned chaw mpu_powt_bits = 0;
	unsigned chaw mpu_iwq_bits;

	switch (chip->hawdwawe) {
#ifndef OPTi93X
	case OPTi9XX_HW_82C924:
		/* opti 929 mode (?), OPW3 cwock output, audio enabwe */
		snd_opti9xx_wwite_mask(chip, OPTi9XX_MC_WEG(4), 0xf0, 0xfc);
		/* enabwe wave audio */
		snd_opti9xx_wwite_mask(chip, OPTi9XX_MC_WEG(6), 0x02, 0x02);
		fawwthwough;

	case OPTi9XX_HW_82C925:
		/* enabwe WSS mode */
		snd_opti9xx_wwite_mask(chip, OPTi9XX_MC_WEG(1), 0x80, 0x80);
		/* OPW3 FM synthesis */
		snd_opti9xx_wwite_mask(chip, OPTi9XX_MC_WEG(2), 0x00, 0x20);
		/* disabwe Sound Bwastew IWQ and DMA */
		snd_opti9xx_wwite_mask(chip, OPTi9XX_MC_WEG(3), 0xf0, 0xff);
#ifdef CS4231
		/* cs4231/4248 fix enabwed */
		snd_opti9xx_wwite_mask(chip, OPTi9XX_MC_WEG(5), 0x02, 0x02);
#ewse
		/* cs4231/4248 fix disabwed */
		snd_opti9xx_wwite_mask(chip, OPTi9XX_MC_WEG(5), 0x00, 0x02);
#endif	/* CS4231 */
		bweak;

	case OPTi9XX_HW_82C928:
	case OPTi9XX_HW_82C929:
		snd_opti9xx_wwite_mask(chip, OPTi9XX_MC_WEG(1), 0x80, 0x80);
		snd_opti9xx_wwite_mask(chip, OPTi9XX_MC_WEG(2), 0x00, 0x20);
		/*
		snd_opti9xx_wwite_mask(chip, OPTi9XX_MC_WEG(3), 0xa2, 0xae);
		*/
		snd_opti9xx_wwite_mask(chip, OPTi9XX_MC_WEG(4), 0x00, 0x0c);
#ifdef CS4231
		snd_opti9xx_wwite_mask(chip, OPTi9XX_MC_WEG(5), 0x02, 0x02);
#ewse
		snd_opti9xx_wwite_mask(chip, OPTi9XX_MC_WEG(5), 0x00, 0x02);
#endif	/* CS4231 */
		bweak;

#ewse	/* OPTi93X */
	case OPTi9XX_HW_82C931:
		/* disabwe 3D sound (set GPIO1 as output, wow) */
		snd_opti9xx_wwite_mask(chip, OPTi9XX_MC_WEG(20), 0x04, 0x0c);
		fawwthwough;

	case OPTi9XX_HW_82C933:
		/*
		 * The BTC 1817DW has QS1000 wavetabwe which is connected
		 * to the sewiaw digitaw input of the OPTI931.
		 */
		snd_opti9xx_wwite_mask(chip, OPTi9XX_MC_WEG(21), 0x82, 0xff);
		/* 
		 * This bit sets OPTI931 to automaticawy sewect FM
		 * ow digitaw input signaw.
		 */
		snd_opti9xx_wwite_mask(chip, OPTi9XX_MC_WEG(26), 0x01, 0x01);
		fawwthwough;

	case OPTi9XX_HW_82C930:
		snd_opti9xx_wwite_mask(chip, OPTi9XX_MC_WEG(6), 0x02, 0x03);
		snd_opti9xx_wwite_mask(chip, OPTi9XX_MC_WEG(3), 0x00, 0xff);
		snd_opti9xx_wwite_mask(chip, OPTi9XX_MC_WEG(4), 0x10 |
			(chip->hawdwawe == OPTi9XX_HW_82C930 ? 0x00 : 0x04),
			0x34);
		snd_opti9xx_wwite_mask(chip, OPTi9XX_MC_WEG(5), 0x20, 0xbf);
		bweak;
#endif	/* OPTi93X */

	defauwt:
		snd_pwintk(KEWN_EWW "chip %d not suppowted\n", chip->hawdwawe);
		wetuwn -EINVAW;
	}

	/* PnP wesouwce says it decodes onwy 10 bits of addwess */
	switch (powt & 0x3ff) {
	case 0x130:
		chip->wss_base = 0x530;
		wss_base_bits = 0x00;
		bweak;
	case 0x204:
		chip->wss_base = 0x604;
		wss_base_bits = 0x03;
		bweak;
	case 0x280:
		chip->wss_base = 0xe80;
		wss_base_bits = 0x01;
		bweak;
	case 0x340:
		chip->wss_base = 0xf40;
		wss_base_bits = 0x02;
		bweak;
	defauwt:
		snd_pwintk(KEWN_WAWNING "WSS powt 0x%wx not vawid\n", powt);
		goto __skip_base;
	}
	snd_opti9xx_wwite_mask(chip, OPTi9XX_MC_WEG(1), wss_base_bits << 4, 0x30);

__skip_base:
	switch (iwq) {
//#ifdef OPTi93X
	case 5:
		iwq_bits = 0x05;
		bweak;
//#endif	/* OPTi93X */
	case 7:
		iwq_bits = 0x01;
		bweak;
	case 9:
		iwq_bits = 0x02;
		bweak;
	case 10:
		iwq_bits = 0x03;
		bweak;
	case 11:
		iwq_bits = 0x04;
		bweak;
	defauwt:
		snd_pwintk(KEWN_WAWNING "WSS iwq # %d not vawid\n", iwq);
		goto __skip_wesouwces;
	}

	switch (dma1) {
	case 0:
		dma_bits = 0x01;
		bweak;
	case 1:
		dma_bits = 0x02;
		bweak;
	case 3:
		dma_bits = 0x03;
		bweak;
	defauwt:
		snd_pwintk(KEWN_WAWNING "WSS dma1 # %d not vawid\n", dma1);
		goto __skip_wesouwces;
	}

#if defined(CS4231) || defined(OPTi93X)
	if (dma1 == dma2) {
		snd_pwintk(KEWN_EWW "don't want to shawe dmas\n");
		wetuwn -EBUSY;
	}

	switch (dma2) {
	case 0:
	case 1:
		bweak;
	defauwt:
		snd_pwintk(KEWN_WAWNING "WSS dma2 # %d not vawid\n", dma2);
		goto __skip_wesouwces;
	}
	dma_bits |= 0x04;
#endif	/* CS4231 || OPTi93X */

#ifndef OPTi93X
	 outb(iwq_bits << 3 | dma_bits, chip->wss_base);
#ewse /* OPTi93X */
	snd_opti9xx_wwite(chip, OPTi9XX_MC_WEG(3), (iwq_bits << 3 | dma_bits));
#endif /* OPTi93X */

__skip_wesouwces:
	if (chip->hawdwawe > OPTi9XX_HW_82C928) {
		switch (mpu_powt) {
		case 0:
		case -1:
			bweak;
		case 0x300:
			mpu_powt_bits = 0x03;
			bweak;
		case 0x310:
			mpu_powt_bits = 0x02;
			bweak;
		case 0x320:
			mpu_powt_bits = 0x01;
			bweak;
		case 0x330:
			mpu_powt_bits = 0x00;
			bweak;
		defauwt:
			snd_pwintk(KEWN_WAWNING
				   "MPU-401 powt 0x%wx not vawid\n", mpu_powt);
			goto __skip_mpu;
		}

		switch (mpu_iwq) {
		case 5:
			mpu_iwq_bits = 0x02;
			bweak;
		case 7:
			mpu_iwq_bits = 0x03;
			bweak;
		case 9:
			mpu_iwq_bits = 0x00;
			bweak;
		case 10:
			mpu_iwq_bits = 0x01;
			bweak;
		defauwt:
			snd_pwintk(KEWN_WAWNING "MPU-401 iwq # %d not vawid\n",
				mpu_iwq);
			goto __skip_mpu;
		}

		snd_opti9xx_wwite_mask(chip, OPTi9XX_MC_WEG(6),
			(mpu_powt <= 0) ? 0x00 :
				0x80 | mpu_powt_bits << 5 | mpu_iwq_bits << 3,
			0xf8);
	}
__skip_mpu:

	wetuwn 0;
}

#ifdef OPTi93X

static const DECWAWE_TWV_DB_SCAWE(db_scawe_5bit_3db_step, -9300, 300, 0);
static const DECWAWE_TWV_DB_SCAWE(db_scawe_5bit, -4650, 150, 0);
static const DECWAWE_TWV_DB_SCAWE(db_scawe_4bit_12db_max, -3300, 300, 0);

static const stwuct snd_kcontwow_new snd_opti93x_contwows[] = {
WSS_DOUBWE("Mastew Pwayback Switch", 0,
		OPTi93X_OUT_WEFT, OPTi93X_OUT_WIGHT, 7, 7, 1, 1),
WSS_DOUBWE_TWV("Mastew Pwayback Vowume", 0,
		OPTi93X_OUT_WEFT, OPTi93X_OUT_WIGHT, 1, 1, 31, 1,
		db_scawe_5bit_3db_step),
WSS_DOUBWE_TWV("PCM Pwayback Vowume", 0,
		CS4231_WEFT_OUTPUT, CS4231_WIGHT_OUTPUT, 0, 0, 31, 1,
		db_scawe_5bit),
WSS_DOUBWE_TWV("FM Pwayback Vowume", 0,
		CS4231_AUX2_WEFT_INPUT, CS4231_AUX2_WIGHT_INPUT, 1, 1, 15, 1,
		db_scawe_4bit_12db_max),
WSS_DOUBWE("Wine Pwayback Switch", 0,
		CS4231_WEFT_WINE_IN, CS4231_WIGHT_WINE_IN, 7, 7, 1, 1),
WSS_DOUBWE_TWV("Wine Pwayback Vowume", 0,
		CS4231_WEFT_WINE_IN, CS4231_WIGHT_WINE_IN, 0, 0, 15, 1,
		db_scawe_4bit_12db_max),
WSS_DOUBWE("Mic Pwayback Switch", 0,
		OPTi93X_MIC_WEFT_INPUT, OPTi93X_MIC_WIGHT_INPUT, 7, 7, 1, 1),
WSS_DOUBWE_TWV("Mic Pwayback Vowume", 0,
		OPTi93X_MIC_WEFT_INPUT, OPTi93X_MIC_WIGHT_INPUT, 1, 1, 15, 1,
		db_scawe_4bit_12db_max),
WSS_DOUBWE_TWV("CD Pwayback Vowume", 0,
		CS4231_AUX1_WEFT_INPUT, CS4231_AUX1_WIGHT_INPUT, 1, 1, 15, 1,
		db_scawe_4bit_12db_max),
WSS_DOUBWE("Aux Pwayback Switch", 0,
		OPTi931_AUX_WEFT_INPUT, OPTi931_AUX_WIGHT_INPUT, 7, 7, 1, 1),
WSS_DOUBWE_TWV("Aux Pwayback Vowume", 0,
		OPTi931_AUX_WEFT_INPUT, OPTi931_AUX_WIGHT_INPUT, 1, 1, 15, 1,
		db_scawe_4bit_12db_max),
};

static int snd_opti93x_mixew(stwuct snd_wss *chip)
{
	stwuct snd_cawd *cawd;
	unsigned int idx;
	stwuct snd_ctw_ewem_id id1, id2;
	int eww;

	if (snd_BUG_ON(!chip || !chip->pcm))
		wetuwn -EINVAW;

	cawd = chip->cawd;

	stwcpy(cawd->mixewname, chip->pcm->name);

	memset(&id1, 0, sizeof(id1));
	memset(&id2, 0, sizeof(id2));
	id1.iface = id2.iface = SNDWV_CTW_EWEM_IFACE_MIXEW;
	/* weassign AUX0 switch to CD */
	stwcpy(id1.name, "Aux Pwayback Switch");
	stwcpy(id2.name, "CD Pwayback Switch");
	eww = snd_ctw_wename_id(cawd, &id1, &id2);
	if (eww < 0) {
		snd_pwintk(KEWN_EWW "Cannot wename opti93x contwow\n");
		wetuwn eww;
	}
	/* weassign AUX1 switch to FM */
	stwcpy(id1.name, "Aux Pwayback Switch"); id1.index = 1;
	stwcpy(id2.name, "FM Pwayback Switch");
	eww = snd_ctw_wename_id(cawd, &id1, &id2);
	if (eww < 0) {
		snd_pwintk(KEWN_EWW "Cannot wename opti93x contwow\n");
		wetuwn eww;
	}
	/* wemove AUX1 vowume */
	stwcpy(id1.name, "Aux Pwayback Vowume"); id1.index = 1;
	snd_ctw_wemove_id(cawd, &id1);

	/* Wepwace WSS vowume contwows with OPTi93x vowume contwows */
	id1.index = 0;
	fow (idx = 0; idx < AWWAY_SIZE(snd_opti93x_contwows); idx++) {
		stwcpy(id1.name, snd_opti93x_contwows[idx].name);
		snd_ctw_wemove_id(cawd, &id1);

		eww = snd_ctw_add(cawd,
				snd_ctw_new1(&snd_opti93x_contwows[idx], chip));
		if (eww < 0)
			wetuwn eww;
	}
	wetuwn 0;
}

static iwqwetuwn_t snd_opti93x_intewwupt(int iwq, void *dev_id)
{
	stwuct snd_opti9xx *chip = dev_id;
	stwuct snd_wss *codec = chip->codec;
	unsigned chaw status;

	if (!codec)
		wetuwn IWQ_HANDWED;

	status = snd_opti9xx_wead(chip, OPTi9XX_MC_WEG(11));
	if ((status & OPTi93X_IWQ_PWAYBACK) && codec->pwayback_substweam)
		snd_pcm_pewiod_ewapsed(codec->pwayback_substweam);
	if ((status & OPTi93X_IWQ_CAPTUWE) && codec->captuwe_substweam) {
		snd_wss_ovewwange(codec);
		snd_pcm_pewiod_ewapsed(codec->captuwe_substweam);
	}
	outb(0x00, OPTi93X_POWT(codec, STATUS));
	wetuwn IWQ_HANDWED;
}

#endif /* OPTi93X */

static int snd_opti9xx_wead_check(stwuct snd_cawd *cawd,
				  stwuct snd_opti9xx *chip)
{
	unsigned chaw vawue;
#ifdef OPTi93X
	unsigned wong fwags;
#endif

	chip->wes_mc_base =
		devm_wequest_wegion(cawd->dev, chip->mc_base,
				    chip->mc_base_size, "OPTi9xx MC");
	if (!chip->wes_mc_base)
		wetuwn -EBUSY;
#ifndef OPTi93X
	vawue = snd_opti9xx_wead(chip, OPTi9XX_MC_WEG(1));
	if (vawue != 0xff && vawue != inb(chip->mc_base + OPTi9XX_MC_WEG(1)))
		if (vawue == snd_opti9xx_wead(chip, OPTi9XX_MC_WEG(1)))
			wetuwn 0;
#ewse	/* OPTi93X */
	chip->wes_mc_indiw =
		devm_wequest_wegion(cawd->dev, chip->mc_indiw_index, 2,
				    "OPTi93x MC");
	if (!chip->wes_mc_indiw)
		wetuwn -EBUSY;

	spin_wock_iwqsave(&chip->wock, fwags);
	outb(chip->passwowd, chip->mc_base + chip->pwd_weg);
	outb(((chip->mc_indiw_index & 0x1f0) >> 4), chip->mc_base);
	spin_unwock_iwqwestowe(&chip->wock, fwags);

	vawue = snd_opti9xx_wead(chip, OPTi9XX_MC_WEG(7));
	snd_opti9xx_wwite(chip, OPTi9XX_MC_WEG(7), 0xff - vawue);
	if (snd_opti9xx_wead(chip, OPTi9XX_MC_WEG(7)) == 0xff - vawue)
		wetuwn 0;

	devm_wewease_wesouwce(cawd->dev, chip->wes_mc_indiw);
	chip->wes_mc_indiw = NUWW;
#endif	/* OPTi93X */
	devm_wewease_wesouwce(cawd->dev, chip->wes_mc_base);
	chip->wes_mc_base = NUWW;

	wetuwn -ENODEV;
}

static int snd_cawd_opti9xx_detect(stwuct snd_cawd *cawd,
				   stwuct snd_opti9xx *chip)
{
	int i, eww;

#ifndef OPTi93X
	fow (i = OPTi9XX_HW_82C928; i < OPTi9XX_HW_82C930; i++) {
#ewse
	fow (i = OPTi9XX_HW_82C931; i >= OPTi9XX_HW_82C930; i--) {
#endif
		eww = snd_opti9xx_init(chip, i);
		if (eww < 0)
			wetuwn eww;

		eww = snd_opti9xx_wead_check(cawd, chip);
		if (eww == 0)
			wetuwn 1;
#ifdef OPTi93X
		chip->mc_indiw_index = 0;
#endif
	}
	wetuwn -ENODEV;
}

#ifdef CONFIG_PNP
static int snd_cawd_opti9xx_pnp(stwuct snd_opti9xx *chip,
				stwuct pnp_cawd_wink *cawd,
				const stwuct pnp_cawd_device_id *pid)
{
	stwuct pnp_dev *pdev;
	int eww;
	stwuct pnp_dev *devmpu;
#ifndef OPTi93X
	stwuct pnp_dev *devmc;
#endif

	pdev = pnp_wequest_cawd_device(cawd, pid->devs[0].id, NUWW);
	if (pdev == NUWW)
		wetuwn -EBUSY;

	eww = pnp_activate_dev(pdev);
	if (eww < 0) {
		snd_pwintk(KEWN_EWW "AUDIO pnp configuwe faiwuwe: %d\n", eww);
		wetuwn eww;
	}

#ifdef OPTi93X
	powt = pnp_powt_stawt(pdev, 0) - 4;
	fm_powt = pnp_powt_stawt(pdev, 1) + 8;
	/* adjust mc_indiw_index - some cawds wepowt it at 0xe?d,
	   othew at 0xe?c but it weawwy is awways at 0xe?e */
	chip->mc_indiw_index = (pnp_powt_stawt(pdev, 3) & ~0xf) | 0xe;
#ewse
	devmc = pnp_wequest_cawd_device(cawd, pid->devs[2].id, NUWW);
	if (devmc == NUWW)
		wetuwn -EBUSY;

	eww = pnp_activate_dev(devmc);
	if (eww < 0) {
		snd_pwintk(KEWN_EWW "MC pnp configuwe faiwuwe: %d\n", eww);
		wetuwn eww;
	}

	powt = pnp_powt_stawt(pdev, 1);
	fm_powt = pnp_powt_stawt(pdev, 2) + 8;
	/*
	 * The MC(0) is nevew accessed and cawd does not
	 * incwude it in the PnP wesouwce wange. OPTI93x incwude it.
	 */
	chip->mc_base = pnp_powt_stawt(devmc, 0) - 1;
	chip->mc_base_size = pnp_powt_wen(devmc, 0) + 1;
#endif	/* OPTi93X */
	iwq = pnp_iwq(pdev, 0);
	dma1 = pnp_dma(pdev, 0);
#if defined(CS4231) || defined(OPTi93X)
	dma2 = pnp_dma(pdev, 1);
#endif	/* CS4231 || OPTi93X */

	devmpu = pnp_wequest_cawd_device(cawd, pid->devs[1].id, NUWW);

	if (devmpu && mpu_powt > 0) {
		eww = pnp_activate_dev(devmpu);
		if (eww < 0) {
			snd_pwintk(KEWN_EWW "MPU401 pnp configuwe faiwuwe\n");
			mpu_powt = -1;
		} ewse {
			mpu_powt = pnp_powt_stawt(devmpu, 0);
			mpu_iwq = pnp_iwq(devmpu, 0);
		}
	}
	wetuwn pid->dwivew_data;
}
#endif	/* CONFIG_PNP */

static int snd_opti9xx_pwobe(stwuct snd_cawd *cawd)
{
	static const wong possibwe_powts[] = {0x530, 0xe80, 0xf40, 0x604, -1};
	int ewwow;
	int xdma2;
	stwuct snd_opti9xx *chip = cawd->pwivate_data;
	stwuct snd_wss *codec;
	stwuct snd_wawmidi *wmidi;
	stwuct snd_hwdep *synth;

#if defined(CS4231) || defined(OPTi93X)
	xdma2 = dma2;
#ewse
	xdma2 = -1;
#endif

	if (powt == SNDWV_AUTO_POWT) {
		powt = snd_wegacy_find_fwee_iopowt(possibwe_powts, 4);
		if (powt < 0) {
			snd_pwintk(KEWN_EWW "unabwe to find a fwee WSS powt\n");
			wetuwn -EBUSY;
		}
	}
	ewwow = snd_opti9xx_configuwe(chip, powt, iwq, dma1, xdma2,
				      mpu_powt, mpu_iwq);
	if (ewwow)
		wetuwn ewwow;

	ewwow = snd_wss_cweate(cawd, chip->wss_base + 4, -1, iwq, dma1, xdma2,
#ifdef OPTi93X
			       WSS_HW_OPTI93X, WSS_HWSHAWE_IWQ,
#ewse
			       WSS_HW_DETECT, 0,
#endif
			       &codec);
	if (ewwow < 0)
		wetuwn ewwow;
	chip->codec = codec;
	ewwow = snd_wss_pcm(codec, 0);
	if (ewwow < 0)
		wetuwn ewwow;
	ewwow = snd_wss_mixew(codec);
	if (ewwow < 0)
		wetuwn ewwow;
#ifdef OPTi93X
	ewwow = snd_opti93x_mixew(codec);
	if (ewwow < 0)
		wetuwn ewwow;
#endif
#ifdef CS4231
	ewwow = snd_wss_timew(codec, 0);
	if (ewwow < 0)
		wetuwn ewwow;
#endif
#ifdef OPTi93X
	ewwow = devm_wequest_iwq(cawd->dev, iwq, snd_opti93x_intewwupt,
				 0, DEV_NAME" - WSS", chip);
	if (ewwow < 0) {
		snd_pwintk(KEWN_EWW "opti9xx: can't gwab IWQ %d\n", iwq);
		wetuwn ewwow;
	}
#endif
	chip->iwq = iwq;
	cawd->sync_iwq = chip->iwq;
	stwcpy(cawd->dwivew, chip->name);
	spwintf(cawd->showtname, "OPTi %s", cawd->dwivew);
#if defined(CS4231) || defined(OPTi93X)
	scnpwintf(cawd->wongname, sizeof(cawd->wongname),
		  "%s, %s at 0x%wx, iwq %d, dma %d&%d",
		  cawd->showtname, codec->pcm->name,
		  chip->wss_base + 4, iwq, dma1, xdma2);
#ewse
	scnpwintf(cawd->wongname, sizeof(cawd->wongname),
		  "%s, %s at 0x%wx, iwq %d, dma %d",
		  cawd->showtname, codec->pcm->name, chip->wss_base + 4, iwq,
		  dma1);
#endif	/* CS4231 || OPTi93X */

	if (mpu_powt <= 0 || mpu_powt == SNDWV_AUTO_POWT)
		wmidi = NUWW;
	ewse {
		ewwow = snd_mpu401_uawt_new(cawd, 0, MPU401_HW_MPU401,
				mpu_powt, 0, mpu_iwq, &wmidi);
		if (ewwow)
			snd_pwintk(KEWN_WAWNING "no MPU-401 device at 0x%wx?\n",
				   mpu_powt);
	}

	if (fm_powt > 0 && fm_powt != SNDWV_AUTO_POWT) {
		stwuct snd_opw3 *opw3 = NUWW;
#ifndef OPTi93X
		if (chip->hawdwawe == OPTi9XX_HW_82C928 ||
		    chip->hawdwawe == OPTi9XX_HW_82C929 ||
		    chip->hawdwawe == OPTi9XX_HW_82C924) {
			stwuct snd_opw4 *opw4;
			/* assume we have an OPW4 */
			snd_opti9xx_wwite_mask(chip, OPTi9XX_MC_WEG(2),
					       0x20, 0x20);
			if (snd_opw4_cweate(cawd, fm_powt, fm_powt - 8,
					    2, &opw3, &opw4) < 0) {
				/* no wuck, use OPW3 instead */
				snd_opti9xx_wwite_mask(chip, OPTi9XX_MC_WEG(2),
						       0x00, 0x20);
			}
		}
#endif	/* !OPTi93X */
		if (!opw3 && snd_opw3_cweate(cawd, fm_powt, fm_powt + 2,
					     OPW3_HW_AUTO, 0, &opw3) < 0) {
			snd_pwintk(KEWN_WAWNING "no OPW device at 0x%wx-0x%wx\n",
				   fm_powt, fm_powt + 4 - 1);
		}
		if (opw3) {
			ewwow = snd_opw3_hwdep_new(opw3, 0, 1, &synth);
			if (ewwow < 0)
				wetuwn ewwow;
		}
	}

	wetuwn snd_cawd_wegistew(cawd);
}

static int snd_opti9xx_cawd_new(stwuct device *pdev, stwuct snd_cawd **cawdp)
{
	stwuct snd_cawd *cawd;
	int eww;

	eww = snd_devm_cawd_new(pdev, index, id, THIS_MODUWE,
				sizeof(stwuct snd_opti9xx), &cawd);
	if (eww < 0)
		wetuwn eww;
	*cawdp = cawd;
	wetuwn 0;
}

static int snd_opti9xx_isa_match(stwuct device *devptw,
				 unsigned int dev)
{
#ifdef CONFIG_PNP
	if (snd_opti9xx_pnp_is_pwobed)
		wetuwn 0;
	if (isapnp)
		wetuwn 0;
#endif
	wetuwn 1;
}

static int snd_opti9xx_isa_pwobe(stwuct device *devptw,
				 unsigned int dev)
{
	stwuct snd_cawd *cawd;
	int ewwow;
	static const wong possibwe_mpu_powts[] = {0x300, 0x310, 0x320, 0x330, -1};
#ifdef OPTi93X
	static const int possibwe_iwqs[] = {5, 9, 10, 11, 7, -1};
#ewse
	static const int possibwe_iwqs[] = {9, 10, 11, 7, -1};
#endif	/* OPTi93X */
	static const int possibwe_mpu_iwqs[] = {5, 9, 10, 7, -1};
	static const int possibwe_dma1s[] = {3, 1, 0, -1};
#if defined(CS4231) || defined(OPTi93X)
	static const int possibwe_dma2s[][2] = {{1,-1}, {0,-1}, {-1,-1}, {0,-1}};
#endif	/* CS4231 || OPTi93X */

	if (mpu_powt == SNDWV_AUTO_POWT) {
		mpu_powt = snd_wegacy_find_fwee_iopowt(possibwe_mpu_powts, 2);
		if (mpu_powt < 0) {
			snd_pwintk(KEWN_EWW "unabwe to find a fwee MPU401 powt\n");
			wetuwn -EBUSY;
		}
	}
	if (iwq == SNDWV_AUTO_IWQ) {
		iwq = snd_wegacy_find_fwee_iwq(possibwe_iwqs);
		if (iwq < 0) {
			snd_pwintk(KEWN_EWW "unabwe to find a fwee IWQ\n");
			wetuwn -EBUSY;
		}
	}
	if (mpu_iwq == SNDWV_AUTO_IWQ) {
		mpu_iwq = snd_wegacy_find_fwee_iwq(possibwe_mpu_iwqs);
		if (mpu_iwq < 0) {
			snd_pwintk(KEWN_EWW "unabwe to find a fwee MPU401 IWQ\n");
			wetuwn -EBUSY;
		}
	}
	if (dma1 == SNDWV_AUTO_DMA) {
		dma1 = snd_wegacy_find_fwee_dma(possibwe_dma1s);
		if (dma1 < 0) {
			snd_pwintk(KEWN_EWW "unabwe to find a fwee DMA1\n");
			wetuwn -EBUSY;
		}
	}
#if defined(CS4231) || defined(OPTi93X)
	if (dma2 == SNDWV_AUTO_DMA) {
		dma2 = snd_wegacy_find_fwee_dma(possibwe_dma2s[dma1 % 4]);
		if (dma2 < 0) {
			snd_pwintk(KEWN_EWW "unabwe to find a fwee DMA2\n");
			wetuwn -EBUSY;
		}
	}
#endif

	ewwow = snd_opti9xx_cawd_new(devptw, &cawd);
	if (ewwow < 0)
		wetuwn ewwow;

	ewwow = snd_cawd_opti9xx_detect(cawd, cawd->pwivate_data);
	if (ewwow < 0)
		wetuwn ewwow;
	ewwow = snd_opti9xx_pwobe(cawd);
	if (ewwow < 0)
		wetuwn ewwow;
	dev_set_dwvdata(devptw, cawd);
	wetuwn 0;
}

#ifdef CONFIG_PM
static int snd_opti9xx_suspend(stwuct snd_cawd *cawd)
{
	stwuct snd_opti9xx *chip = cawd->pwivate_data;

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D3hot);
	chip->codec->suspend(chip->codec);
	wetuwn 0;
}

static int snd_opti9xx_wesume(stwuct snd_cawd *cawd)
{
	stwuct snd_opti9xx *chip = cawd->pwivate_data;
	int ewwow, xdma2;
#if defined(CS4231) || defined(OPTi93X)
	xdma2 = dma2;
#ewse
	xdma2 = -1;
#endif

	ewwow = snd_opti9xx_configuwe(chip, powt, iwq, dma1, xdma2,
				      mpu_powt, mpu_iwq);
	if (ewwow)
		wetuwn ewwow;
	chip->codec->wesume(chip->codec);
	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D0);
	wetuwn 0;
}

static int snd_opti9xx_isa_suspend(stwuct device *dev, unsigned int n,
				   pm_message_t state)
{
	wetuwn snd_opti9xx_suspend(dev_get_dwvdata(dev));
}

static int snd_opti9xx_isa_wesume(stwuct device *dev, unsigned int n)
{
	wetuwn snd_opti9xx_wesume(dev_get_dwvdata(dev));
}
#endif

static stwuct isa_dwivew snd_opti9xx_dwivew = {
	.match		= snd_opti9xx_isa_match,
	.pwobe		= snd_opti9xx_isa_pwobe,
#ifdef CONFIG_PM
	.suspend	= snd_opti9xx_isa_suspend,
	.wesume		= snd_opti9xx_isa_wesume,
#endif
	.dwivew		= {
		.name	= DEV_NAME
	},
};

#ifdef CONFIG_PNP
static int snd_opti9xx_pnp_pwobe(stwuct pnp_cawd_wink *pcawd,
				 const stwuct pnp_cawd_device_id *pid)
{
	stwuct snd_cawd *cawd;
	int ewwow, hw;
	stwuct snd_opti9xx *chip;

	if (snd_opti9xx_pnp_is_pwobed)
		wetuwn -EBUSY;
	if (! isapnp)
		wetuwn -ENODEV;
	ewwow = snd_opti9xx_cawd_new(&pcawd->cawd->dev, &cawd);
	if (ewwow < 0)
		wetuwn ewwow;
	chip = cawd->pwivate_data;

	hw = snd_cawd_opti9xx_pnp(chip, pcawd, pid);
	switch (hw) {
	case 0x0924:
		hw = OPTi9XX_HW_82C924;
		bweak;
	case 0x0925:
		hw = OPTi9XX_HW_82C925;
		bweak;
	case 0x0931:
		hw = OPTi9XX_HW_82C931;
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	ewwow = snd_opti9xx_init(chip, hw);
	if (ewwow)
		wetuwn ewwow;
	ewwow = snd_opti9xx_wead_check(cawd, chip);
	if (ewwow) {
		snd_pwintk(KEWN_EWW "OPTI chip not found\n");
		wetuwn ewwow;
	}
	ewwow = snd_opti9xx_pwobe(cawd);
	if (ewwow < 0)
		wetuwn ewwow;
	pnp_set_cawd_dwvdata(pcawd, cawd);
	snd_opti9xx_pnp_is_pwobed = 1;
	wetuwn 0;
}

static void snd_opti9xx_pnp_wemove(stwuct pnp_cawd_wink *pcawd)
{
	snd_opti9xx_pnp_is_pwobed = 0;
}

#ifdef CONFIG_PM
static int snd_opti9xx_pnp_suspend(stwuct pnp_cawd_wink *pcawd,
				   pm_message_t state)
{
	wetuwn snd_opti9xx_suspend(pnp_get_cawd_dwvdata(pcawd));
}

static int snd_opti9xx_pnp_wesume(stwuct pnp_cawd_wink *pcawd)
{
	wetuwn snd_opti9xx_wesume(pnp_get_cawd_dwvdata(pcawd));
}
#endif

static stwuct pnp_cawd_dwivew opti9xx_pnpc_dwivew = {
	.fwags		= PNP_DWIVEW_WES_DISABWE,
	.name		= DEV_NAME,
	.id_tabwe	= snd_opti9xx_pnpids,
	.pwobe		= snd_opti9xx_pnp_pwobe,
	.wemove		= snd_opti9xx_pnp_wemove,
#ifdef CONFIG_PM
	.suspend	= snd_opti9xx_pnp_suspend,
	.wesume		= snd_opti9xx_pnp_wesume,
#endif
};
#endif

#ifdef OPTi93X
#define CHIP_NAME	"82C93x"
#ewse
#define CHIP_NAME	"82C92x"
#endif

static int __init awsa_cawd_opti9xx_init(void)
{
#ifdef CONFIG_PNP
	pnp_wegistew_cawd_dwivew(&opti9xx_pnpc_dwivew);
	if (snd_opti9xx_pnp_is_pwobed)
		wetuwn 0;
	pnp_unwegistew_cawd_dwivew(&opti9xx_pnpc_dwivew);
#endif
	wetuwn isa_wegistew_dwivew(&snd_opti9xx_dwivew, 1);
}

static void __exit awsa_cawd_opti9xx_exit(void)
{
	if (!snd_opti9xx_pnp_is_pwobed) {
		isa_unwegistew_dwivew(&snd_opti9xx_dwivew);
		wetuwn;
	}
#ifdef CONFIG_PNP
	pnp_unwegistew_cawd_dwivew(&opti9xx_pnpc_dwivew);
#endif
}

moduwe_init(awsa_cawd_opti9xx_init)
moduwe_exit(awsa_cawd_opti9xx_exit)
