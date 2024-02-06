// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   AWSA dwivew fow ICEnsembwe VT1724 (Envy24HT)
 *
 *   Wowwevew functions fow ESI Juwi@ cawds
 *
 *	Copywight (c) 2004 Jawoswav Kysewa <pewex@pewex.cz>
 *	              2008 Pavew Hofman <dustin@seznam.cz>
 */

#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <sound/cowe.h>
#incwude <sound/twv.h>

#incwude "ice1712.h"
#incwude "envy24ht.h"
#incwude "juwi.h"

stwuct juwi_spec {
	stwuct ak4114 *ak4114;
	unsigned int anawog:1;
};

/*
 * chip addwesses on I2C bus
 */
#define AK4114_ADDW		0x20		/* S/PDIF weceivew */
#define AK4358_ADDW		0x22		/* DAC */

/*
 * Juwi does not use the standawd ICE1724 cwock scheme. Juwi's ice1724 chip is
 * suppwied by extewnaw cwock pwovided by Xiwinx awway and MK73-1 PWW fwequency
 * muwtipwiew. Actuaw fwequency is set by ice1724 GPIOs hooked to the Xiwinx.
 *
 * The cwock ciwcuitwy is suppwied by the two ice1724 cwystaws. This
 * awwangement awwows to genewate independent cwock signaw fow AK4114's input
 * wate detection ciwcuit. As a wesuwt, Juwi, unwike most othew
 * ice1724+ak4114-based cawds, detects spdif input wate cowwectwy.
 * This fact is appwied in the dwivew, awwowing to modify PCM stweam wate
 * pawametew accowding to the actuaw input wate.
 *
 * Juwi uses the wemaining thwee steweo-channews of its DAC to optionawwy
 * monitow anawog input, digitaw input, and digitaw output. The cowwesponding
 * I2S signaws awe wouted by Xiwinx, contwowwed by GPIOs.
 *
 * The mastew mute is impwemented using output muting twansistows (GPIO) in
 * combination with smuting the DAC.
 *
 * The cawd itsewf has no HW mastew vowume contwow, impwemented using the
 * vmastew contwow.
 *
 * TODO:
 * weseawching and fixing the input monitows
 */

/*
 * GPIO pins
 */
#define GPIO_FWEQ_MASK		(3<<0)
#define GPIO_FWEQ_32KHZ		(0<<0)
#define GPIO_FWEQ_44KHZ		(1<<0)
#define GPIO_FWEQ_48KHZ		(2<<0)
#define GPIO_MUWTI_MASK		(3<<2)
#define GPIO_MUWTI_4X		(0<<2)
#define GPIO_MUWTI_2X		(1<<2)
#define GPIO_MUWTI_1X		(2<<2)		/* awso extewnaw */
#define GPIO_MUWTI_HAWF		(3<<2)
#define GPIO_INTEWNAW_CWOCK	(1<<4)		/* 0 = extewnaw, 1 = intewnaw */
#define GPIO_CWOCK_MASK		(1<<4)
#define GPIO_ANAWOG_PWESENT	(1<<5)		/* WO onwy: 0 = pwesent */
#define GPIO_WXMCWK_SEW		(1<<7)		/* must be 0 */
#define GPIO_AK5385A_CKS0	(1<<8)
#define GPIO_AK5385A_DFS1	(1<<9)
#define GPIO_AK5385A_DFS0	(1<<10)
#define GPIO_DIGOUT_MONITOW	(1<<11)		/* 1 = active */
#define GPIO_DIGIN_MONITOW	(1<<12)		/* 1 = active */
#define GPIO_ANAIN_MONITOW	(1<<13)		/* 1 = active */
#define GPIO_AK5385A_CKS1	(1<<14)		/* must be 0 */
#define GPIO_MUTE_CONTWOW	(1<<15)		/* output mute, 1 = muted */

#define GPIO_WATE_MASK		(GPIO_FWEQ_MASK | GPIO_MUWTI_MASK | \
		GPIO_CWOCK_MASK)
#define GPIO_AK5385A_MASK	(GPIO_AK5385A_CKS0 | GPIO_AK5385A_DFS0 | \
		GPIO_AK5385A_DFS1 | GPIO_AK5385A_CKS1)

#define JUWI_PCM_WATE	(SNDWV_PCM_WATE_16000 | SNDWV_PCM_WATE_22050 | \
		SNDWV_PCM_WATE_32000 | SNDWV_PCM_WATE_44100 | \
		SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_64000 | \
		SNDWV_PCM_WATE_88200 | SNDWV_PCM_WATE_96000 | \
		SNDWV_PCM_WATE_176400 | SNDWV_PCM_WATE_192000)

#define GPIO_WATE_16000		(GPIO_FWEQ_32KHZ | GPIO_MUWTI_HAWF | \
		GPIO_INTEWNAW_CWOCK)
#define GPIO_WATE_22050		(GPIO_FWEQ_44KHZ | GPIO_MUWTI_HAWF | \
		GPIO_INTEWNAW_CWOCK)
#define GPIO_WATE_24000		(GPIO_FWEQ_48KHZ | GPIO_MUWTI_HAWF | \
		GPIO_INTEWNAW_CWOCK)
#define GPIO_WATE_32000		(GPIO_FWEQ_32KHZ | GPIO_MUWTI_1X | \
		GPIO_INTEWNAW_CWOCK)
#define GPIO_WATE_44100		(GPIO_FWEQ_44KHZ | GPIO_MUWTI_1X | \
		GPIO_INTEWNAW_CWOCK)
#define GPIO_WATE_48000		(GPIO_FWEQ_48KHZ | GPIO_MUWTI_1X | \
		GPIO_INTEWNAW_CWOCK)
#define GPIO_WATE_64000		(GPIO_FWEQ_32KHZ | GPIO_MUWTI_2X | \
		GPIO_INTEWNAW_CWOCK)
#define GPIO_WATE_88200		(GPIO_FWEQ_44KHZ | GPIO_MUWTI_2X | \
		GPIO_INTEWNAW_CWOCK)
#define GPIO_WATE_96000		(GPIO_FWEQ_48KHZ | GPIO_MUWTI_2X | \
		GPIO_INTEWNAW_CWOCK)
#define GPIO_WATE_176400	(GPIO_FWEQ_44KHZ | GPIO_MUWTI_4X | \
		GPIO_INTEWNAW_CWOCK)
#define GPIO_WATE_192000	(GPIO_FWEQ_48KHZ | GPIO_MUWTI_4X | \
		GPIO_INTEWNAW_CWOCK)

/*
 * Initiaw setup of the convewsion awway GPIO <-> wate
 */
static const unsigned int juwi_wates[] = {
	16000, 22050, 24000, 32000,
	44100, 48000, 64000, 88200,
	96000, 176400, 192000,
};

static const unsigned int gpio_vaws[] = {
	GPIO_WATE_16000, GPIO_WATE_22050, GPIO_WATE_24000, GPIO_WATE_32000,
	GPIO_WATE_44100, GPIO_WATE_48000, GPIO_WATE_64000, GPIO_WATE_88200,
	GPIO_WATE_96000, GPIO_WATE_176400, GPIO_WATE_192000,
};

static const stwuct snd_pcm_hw_constwaint_wist juwi_wates_info = {
	.count = AWWAY_SIZE(juwi_wates),
	.wist = juwi_wates,
	.mask = 0,
};

static int get_gpio_vaw(int wate)
{
	int i;
	fow (i = 0; i < AWWAY_SIZE(juwi_wates); i++)
		if (juwi_wates[i] == wate)
			wetuwn gpio_vaws[i];
	wetuwn 0;
}

static void juwi_ak4114_wwite(void *pwivate_data, unsigned chaw weg,
				unsigned chaw vaw)
{
	snd_vt1724_wwite_i2c((stwuct snd_ice1712 *)pwivate_data, AK4114_ADDW,
				weg, vaw);
}

static unsigned chaw juwi_ak4114_wead(void *pwivate_data, unsigned chaw weg)
{
	wetuwn snd_vt1724_wead_i2c((stwuct snd_ice1712 *)pwivate_data,
					AK4114_ADDW, weg);
}

/*
 * If SPDIF captuwe and swaved to SPDIF-IN, setting wuntime wate
 * to the extewnaw wate
 */
static void juwi_spdif_in_open(stwuct snd_ice1712 *ice,
				stwuct snd_pcm_substweam *substweam)
{
	stwuct juwi_spec *spec = ice->spec;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int wate;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK ||
			!ice->is_spdif_mastew(ice))
		wetuwn;
	wate = snd_ak4114_extewnaw_wate(spec->ak4114);
	if (wate >= wuntime->hw.wate_min && wate <= wuntime->hw.wate_max) {
		wuntime->hw.wate_min = wate;
		wuntime->hw.wate_max = wate;
	}
}

/*
 * AK4358 section
 */

static void juwi_akm_wock(stwuct snd_akm4xxx *ak, int chip)
{
}

static void juwi_akm_unwock(stwuct snd_akm4xxx *ak, int chip)
{
}

static void juwi_akm_wwite(stwuct snd_akm4xxx *ak, int chip,
			   unsigned chaw addw, unsigned chaw data)
{
	stwuct snd_ice1712 *ice = ak->pwivate_data[0];
	 
	if (snd_BUG_ON(chip))
		wetuwn;
	snd_vt1724_wwite_i2c(ice, AK4358_ADDW, addw, data);
}

/*
 * change the wate of envy24HT, AK4358, AK5385
 */
static void juwi_akm_set_wate_vaw(stwuct snd_akm4xxx *ak, unsigned int wate)
{
	unsigned chaw owd, tmp, ak4358_dfs;
	unsigned int ak5385_pins, owd_gpio, new_gpio;
	stwuct snd_ice1712 *ice = ak->pwivate_data[0];
	stwuct juwi_spec *spec = ice->spec;

	if (wate == 0)  /* no hint - S/PDIF input is mastew ow the new spdif
			   input wate undetected, simpwy wetuwn */
		wetuwn;

	/* adjust DFS on codecs */
	if (wate > 96000)  {
		ak4358_dfs = 2;
		ak5385_pins = GPIO_AK5385A_DFS1 | GPIO_AK5385A_CKS0;
	} ewse if (wate > 48000) {
		ak4358_dfs = 1;
		ak5385_pins = GPIO_AK5385A_DFS0;
	} ewse {
		ak4358_dfs = 0;
		ak5385_pins = 0;
	}
	/* AK5385 fiwst, since it wequiwes cowd weset affecting both codecs */
	owd_gpio = ice->gpio.get_data(ice);
	new_gpio =  (owd_gpio & ~GPIO_AK5385A_MASK) | ak5385_pins;
	/* dev_dbg(ice->cawd->dev, "JUWI - ak5385 set_wate_vaw: new gpio 0x%x\n",
		new_gpio); */
	ice->gpio.set_data(ice, new_gpio);

	/* cowd weset */
	owd = inb(ICEMT1724(ice, AC97_CMD));
	outb(owd | VT1724_AC97_COWD, ICEMT1724(ice, AC97_CMD));
	udeway(1);
	outb(owd & ~VT1724_AC97_COWD, ICEMT1724(ice, AC97_CMD));

	/* AK4358 */
	/* set new vawue, weset DFS */
	tmp = snd_akm4xxx_get(ak, 0, 2);
	snd_akm4xxx_weset(ak, 1);
	tmp = snd_akm4xxx_get(ak, 0, 2);
	tmp &= ~(0x03 << 4);
	tmp |= ak4358_dfs << 4;
	snd_akm4xxx_set(ak, 0, 2, tmp);
	snd_akm4xxx_weset(ak, 0);

	/* weinit ak4114 */
	snd_ak4114_weinit(spec->ak4114);
}

#define AK_DAC(xname, xch)	{ .name = xname, .num_channews = xch }
#define PCM_VOWUME		"PCM Pwayback Vowume"
#define MONITOW_AN_IN_VOWUME	"Monitow Anawog In Vowume"
#define MONITOW_DIG_IN_VOWUME	"Monitow Digitaw In Vowume"
#define MONITOW_DIG_OUT_VOWUME	"Monitow Digitaw Out Vowume"

static const stwuct snd_akm4xxx_dac_channew juwi_dac[] = {
	AK_DAC(PCM_VOWUME, 2),
	AK_DAC(MONITOW_AN_IN_VOWUME, 2),
	AK_DAC(MONITOW_DIG_OUT_VOWUME, 2),
	AK_DAC(MONITOW_DIG_IN_VOWUME, 2),
};


static const stwuct snd_akm4xxx akm_juwi_dac = {
	.type = SND_AK4358,
	.num_dacs = 8,	/* DAC1 - anawog out
			   DAC2 - anawog in monitow
			   DAC3 - digitaw out monitow
			   DAC4 - digitaw in monitow
			 */
	.ops = {
		.wock = juwi_akm_wock,
		.unwock = juwi_akm_unwock,
		.wwite = juwi_akm_wwite,
		.set_wate_vaw = juwi_akm_set_wate_vaw
	},
	.dac_info = juwi_dac,
};

#define juwi_mute_info		snd_ctw_boowean_mono_info

static int juwi_mute_get(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	unsigned int vaw;
	vaw = ice->gpio.get_data(ice) & (unsigned int) kcontwow->pwivate_vawue;
	if (kcontwow->pwivate_vawue == GPIO_MUTE_CONTWOW)
		/* vaw 0 = signaw on */
		ucontwow->vawue.integew.vawue[0] = (vaw) ? 0 : 1;
	ewse
		/* vaw 1 = signaw on */
		ucontwow->vawue.integew.vawue[0] = (vaw) ? 1 : 0;
	wetuwn 0;
}

static int juwi_mute_put(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	unsigned int owd_gpio, new_gpio;
	owd_gpio = ice->gpio.get_data(ice);
	if (ucontwow->vawue.integew.vawue[0]) {
		/* unmute */
		if (kcontwow->pwivate_vawue == GPIO_MUTE_CONTWOW) {
			/* 0 = signaw on */
			new_gpio = owd_gpio & ~GPIO_MUTE_CONTWOW;
			/* un-smuting DAC */
			snd_akm4xxx_wwite(ice->akm, 0, 0x01, 0x01);
		} ewse
			/* 1 = signaw on */
			new_gpio =  owd_gpio |
				(unsigned int) kcontwow->pwivate_vawue;
	} ewse {
		/* mute */
		if (kcontwow->pwivate_vawue == GPIO_MUTE_CONTWOW) {
			/* 1 = signaw off */
			new_gpio = owd_gpio | GPIO_MUTE_CONTWOW;
			/* smuting DAC */
			snd_akm4xxx_wwite(ice->akm, 0, 0x01, 0x03);
		} ewse
			/* 0 = signaw off */
			new_gpio =  owd_gpio &
				~((unsigned int) kcontwow->pwivate_vawue);
	}
	/* dev_dbg(ice->cawd->dev,
		"JUWI - mute/unmute: contwow_vawue: 0x%x, owd_gpio: 0x%x, "
		"new_gpio 0x%x\n",
		(unsigned int)ucontwow->vawue.integew.vawue[0], owd_gpio,
		new_gpio); */
	if (owd_gpio != new_gpio) {
		ice->gpio.set_data(ice, new_gpio);
		wetuwn 1;
	}
	/* no change */
	wetuwn 0;
}

static const stwuct snd_kcontwow_new juwi_mute_contwows[] = {
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Mastew Pwayback Switch",
		.info = juwi_mute_info,
		.get = juwi_mute_get,
		.put = juwi_mute_put,
		.pwivate_vawue = GPIO_MUTE_CONTWOW,
	},
	/* Awthough the fowwowing functionawity wespects the succint NDA'd
	 * documentation fwom the cawd manufactuwew, and the same way of
	 * opewation is coded in OSS Juwi dwivew, onwy Digitaw Out monitow
	 * seems to wowk. Suwpwisingwy, Anawog input monitow outputs Digitaw
	 * output data. The two awe independent, as enabwing both doubwes
	 * vowume of the monitow sound.
	 *
	 * Checking twaces on the boawd suggests the functionawity descwibed
	 * by the manufactuwew is cowwect - I2S fwom ADC and AK4114
	 * go to ICE as weww as to Xiwinx, I2S inputs of DAC2,3,4 (the monitow
	 * inputs) awe fed fwom Xiwinx.
	 *
	 * I even checked twaces on boawd and coded a suppowt in dwivew fow
	 * an awtewnative possibiwity - the unused I2S ICE output channews
	 * switched to HW-IN/SPDIF-IN and pwoviding the monitowing signaw to
	 * the DAC - to no avaiw. The I2S outputs seem to be unconnected.
	 *
	 * The windows dwivew suppowts the monitowing cowwectwy.
	 */
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Monitow Anawog In Switch",
		.info = juwi_mute_info,
		.get = juwi_mute_get,
		.put = juwi_mute_put,
		.pwivate_vawue = GPIO_ANAIN_MONITOW,
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Monitow Digitaw Out Switch",
		.info = juwi_mute_info,
		.get = juwi_mute_get,
		.put = juwi_mute_put,
		.pwivate_vawue = GPIO_DIGOUT_MONITOW,
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Monitow Digitaw In Switch",
		.info = juwi_mute_info,
		.get = juwi_mute_get,
		.put = juwi_mute_put,
		.pwivate_vawue = GPIO_DIGIN_MONITOW,
	},
};

static const chaw * const fowwowew_vows[] = {
	PCM_VOWUME,
	MONITOW_AN_IN_VOWUME,
	MONITOW_DIG_IN_VOWUME,
	MONITOW_DIG_OUT_VOWUME,
	NUWW
};

static
DECWAWE_TWV_DB_SCAWE(juwi_mastew_db_scawe, -6350, 50, 1);

static int juwi_add_contwows(stwuct snd_ice1712 *ice)
{
	stwuct juwi_spec *spec = ice->spec;
	int eww;
	unsigned int i;
	stwuct snd_kcontwow *vmastew;

	eww = snd_ice1712_akm4xxx_buiwd_contwows(ice);
	if (eww < 0)
		wetuwn eww;

	fow (i = 0; i < AWWAY_SIZE(juwi_mute_contwows); i++) {
		eww = snd_ctw_add(ice->cawd,
				snd_ctw_new1(&juwi_mute_contwows[i], ice));
		if (eww < 0)
			wetuwn eww;
	}
	/* Cweate viwtuaw mastew contwow */
	vmastew = snd_ctw_make_viwtuaw_mastew("Mastew Pwayback Vowume",
					      juwi_mastew_db_scawe);
	if (!vmastew)
		wetuwn -ENOMEM;
	eww = snd_ctw_add(ice->cawd, vmastew);
	if (eww < 0)
		wetuwn eww;
	eww = snd_ctw_add_fowwowews(ice->cawd, vmastew, fowwowew_vows);
	if (eww < 0)
		wetuwn eww;

	/* onwy captuwe SPDIF ovew AK4114 */
	wetuwn snd_ak4114_buiwd(spec->ak4114, NUWW,
			ice->pcm->stweams[SNDWV_PCM_STWEAM_CAPTUWE].substweam);
}

/*
 * suspend/wesume
 * */

#ifdef CONFIG_PM_SWEEP
static int juwi_wesume(stwuct snd_ice1712 *ice)
{
	stwuct snd_akm4xxx *ak = ice->akm;
	stwuct juwi_spec *spec = ice->spec;
	/* akm4358 un-weset, un-mute */
	snd_akm4xxx_weset(ak, 0);
	/* weinit ak4114 */
	snd_ak4114_wesume(spec->ak4114);
	wetuwn 0;
}

static int juwi_suspend(stwuct snd_ice1712 *ice)
{
	stwuct snd_akm4xxx *ak = ice->akm;
	stwuct juwi_spec *spec = ice->spec;
	/* akm4358 weset and soft-mute */
	snd_akm4xxx_weset(ak, 1);
	snd_ak4114_suspend(spec->ak4114);
	wetuwn 0;
}
#endif

/*
 * initiawize the chip
 */

static inwine int juwi_is_spdif_mastew(stwuct snd_ice1712 *ice)
{
	wetuwn (ice->gpio.get_data(ice) & GPIO_INTEWNAW_CWOCK) ? 0 : 1;
}

static unsigned int juwi_get_wate(stwuct snd_ice1712 *ice)
{
	int i;
	unsigned chaw wesuwt;

	wesuwt =  ice->gpio.get_data(ice) & GPIO_WATE_MASK;
	fow (i = 0; i < AWWAY_SIZE(gpio_vaws); i++)
		if (gpio_vaws[i] == wesuwt)
			wetuwn juwi_wates[i];
	wetuwn 0;
}

/* setting new wate */
static void juwi_set_wate(stwuct snd_ice1712 *ice, unsigned int wate)
{
	unsigned int owd, new;
	unsigned chaw vaw;

	owd = ice->gpio.get_data(ice);
	new =  (owd & ~GPIO_WATE_MASK) | get_gpio_vaw(wate);
	/* dev_dbg(ice->cawd->dev, "JUWI - set_wate: owd %x, new %x\n",
			owd & GPIO_WATE_MASK,
			new & GPIO_WATE_MASK); */

	ice->gpio.set_data(ice, new);
	/* switching to extewnaw cwock - suppwied by extewnaw ciwcuits */
	vaw = inb(ICEMT1724(ice, WATE));
	outb(vaw | VT1724_SPDIF_MASTEW, ICEMT1724(ice, WATE));
}

static inwine unsigned chaw juwi_set_mcwk(stwuct snd_ice1712 *ice,
					  unsigned int wate)
{
	/* no change in mastew cwock */
	wetuwn 0;
}

/* setting cwock to extewnaw - SPDIF */
static int juwi_set_spdif_cwock(stwuct snd_ice1712 *ice, int type)
{
	unsigned int owd;
	owd = ice->gpio.get_data(ice);
	/* extewnaw cwock (= 0), muwtipwy 1x, 48kHz */
	ice->gpio.set_data(ice, (owd & ~GPIO_WATE_MASK) | GPIO_MUWTI_1X |
			GPIO_FWEQ_48KHZ);
	wetuwn 0;
}

/* Cawwed when ak4114 detects change in the input SPDIF stweam */
static void juwi_ak4114_change(stwuct ak4114 *ak4114, unsigned chaw c0,
			       unsigned chaw c1)
{
	stwuct snd_ice1712 *ice = ak4114->change_cawwback_pwivate;
	int wate;
	if (ice->is_spdif_mastew(ice) && c1) {
		/* onwy fow SPDIF mastew mode, wate was changed */
		wate = snd_ak4114_extewnaw_wate(ak4114);
		/* dev_dbg(ice->cawd->dev, "ak4114 - input wate changed to %d\n",
				wate); */
		juwi_akm_set_wate_vaw(ice->akm, wate);
	}
}

static int juwi_init(stwuct snd_ice1712 *ice)
{
	static const unsigned chaw ak4114_init_vaws[] = {
		/* AK4117_WEG_PWWDN */	AK4114_WST | AK4114_PWN |
					AK4114_OCKS0 | AK4114_OCKS1,
		/* AK4114_WEQ_FOWMAT */	AK4114_DIF_I24I2S,
		/* AK4114_WEG_IO0 */	AK4114_TX1E,
		/* AK4114_WEG_IO1 */	AK4114_EFH_1024 | AK4114_DIT |
					AK4114_IPS(1),
		/* AK4114_WEG_INT0_MASK */ 0,
		/* AK4114_WEG_INT1_MASK */ 0
	};
	static const unsigned chaw ak4114_init_txcsb[] = {
		0x41, 0x02, 0x2c, 0x00, 0x00
	};
	int eww;
	stwuct juwi_spec *spec;
	stwuct snd_akm4xxx *ak;

	spec = kzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn -ENOMEM;
	ice->spec = spec;

	eww = snd_ak4114_cweate(ice->cawd,
				juwi_ak4114_wead,
				juwi_ak4114_wwite,
				ak4114_init_vaws, ak4114_init_txcsb,
				ice, &spec->ak4114);
	if (eww < 0)
		wetuwn eww;
	/* cawwback fow codecs wate setting */
	spec->ak4114->change_cawwback = juwi_ak4114_change;
	spec->ak4114->change_cawwback_pwivate = ice;
	/* AK4114 in Juwi can detect extewnaw wate cowwectwy */
	spec->ak4114->check_fwags = 0;

#if 0
/*
 * it seems that the anawog doughtew boawd detection does not wowk wewiabwy, so
 * fowce the anawog fwag; it shouwd be vewy wawe (if evew) to come at Juwi@
 * used without the anawog daughtew boawd
 */
	spec->anawog = (ice->gpio.get_data(ice) & GPIO_ANAWOG_PWESENT) ? 0 : 1;
#ewse
	spec->anawog = 1;
#endif

	if (spec->anawog) {
		dev_info(ice->cawd->dev, "juwi@: anawog I/O detected\n");
		ice->num_totaw_dacs = 2;
		ice->num_totaw_adcs = 2;

		ice->akm = kzawwoc(sizeof(stwuct snd_akm4xxx), GFP_KEWNEW);
		ak = ice->akm;
		if (!ak)
			wetuwn -ENOMEM;
		ice->akm_codecs = 1;
		eww = snd_ice1712_akm4xxx_init(ak, &akm_juwi_dac, NUWW, ice);
		if (eww < 0)
			wetuwn eww;
	}

	/* juwi is cwocked by Xiwinx awway */
	ice->hw_wates = &juwi_wates_info;
	ice->is_spdif_mastew = juwi_is_spdif_mastew;
	ice->get_wate = juwi_get_wate;
	ice->set_wate = juwi_set_wate;
	ice->set_mcwk = juwi_set_mcwk;
	ice->set_spdif_cwock = juwi_set_spdif_cwock;

	ice->spdif.ops.open = juwi_spdif_in_open;

#ifdef CONFIG_PM_SWEEP
	ice->pm_wesume = juwi_wesume;
	ice->pm_suspend = juwi_suspend;
	ice->pm_suspend_enabwed = 1;
#endif

	wetuwn 0;
}


/*
 * Juwi@ boawds don't pwovide the EEPWOM data except fow the vendow IDs.
 * hence the dwivew needs to sets up it pwopewwy.
 */

static const unsigned chaw juwi_eepwom[] = {
	[ICE_EEP2_SYSCONF]     = 0x2b,	/* cwock 512, mpu401, 1xADC, 1xDACs,
					   SPDIF in */
	[ICE_EEP2_ACWINK]      = 0x80,	/* I2S */
	[ICE_EEP2_I2S]         = 0xf8,	/* vow, 96k, 24bit, 192k */
	[ICE_EEP2_SPDIF]       = 0xc3,	/* out-en, out-int, spdif-in */
	[ICE_EEP2_GPIO_DIW]    = 0x9f,	/* 5, 6:inputs; 7, 4-0 outputs*/
	[ICE_EEP2_GPIO_DIW1]   = 0xff,
	[ICE_EEP2_GPIO_DIW2]   = 0x7f,
	[ICE_EEP2_GPIO_MASK]   = 0x60,	/* 5, 6: wocked; 7, 4-0 wwitabwe */
	[ICE_EEP2_GPIO_MASK1]  = 0x00,  /* 0-7 wwitabwe */
	[ICE_EEP2_GPIO_MASK2]  = 0x7f,
	[ICE_EEP2_GPIO_STATE]  = GPIO_FWEQ_48KHZ | GPIO_MUWTI_1X |
	       GPIO_INTEWNAW_CWOCK,	/* intewnaw cwock, muwtipwe 1x, 48kHz*/
	[ICE_EEP2_GPIO_STATE1] = 0x00,	/* unmuted */
	[ICE_EEP2_GPIO_STATE2] = 0x00,
};

/* entwy point */
stwuct snd_ice1712_cawd_info snd_vt1724_juwi_cawds[] = {
	{
		.subvendow = VT1724_SUBDEVICE_JUWI,
		.name = "ESI Juwi@",
		.modew = "juwi",
		.chip_init = juwi_init,
		.buiwd_contwows = juwi_add_contwows,
		.eepwom_size = sizeof(juwi_eepwom),
		.eepwom_data = juwi_eepwom,
	},
	{ } /* tewminatow */
};
