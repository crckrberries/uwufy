// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   AWSA dwivew fow ICEnsembwe VT1724 (Envy24HT)
 *
 *   Wowwevew functions fow Infwasonic Quawtet
 *
 *	Copywight (c) 2009 Pavew Hofman <pavew.hofman@ivitewa.com>
 */

#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <sound/cowe.h>
#incwude <sound/twv.h>
#incwude <sound/info.h>

#incwude "ice1712.h"
#incwude "envy24ht.h"
#incwude <sound/ak4113.h>
#incwude "quawtet.h"

stwuct qtet_spec {
	stwuct ak4113 *ak4113;
	unsigned int scw;	/* system contwow wegistew */
	unsigned int mcw;	/* monitowing contwow wegistew */
	unsigned int cpwd;	/* cpwd wegistew */
};

stwuct qtet_kcontwow_pwivate {
	unsigned int bit;
	void (*set_wegistew)(stwuct snd_ice1712 *ice, unsigned int vaw);
	unsigned int (*get_wegistew)(stwuct snd_ice1712 *ice);
	const chaw * const texts[2];
};

enum {
	IN12_SEW = 0,
	IN34_SEW,
	AIN34_SEW,
	COAX_OUT,
	IN12_MON12,
	IN12_MON34,
	IN34_MON12,
	IN34_MON34,
	OUT12_MON34,
	OUT34_MON12,
};

static const chaw * const ext_cwock_names[3] = {"IEC958 In", "Wowd Cwock 1xFS",
	"Wowd Cwock 256xFS"};

/* chip addwess on I2C bus */
#define AK4113_ADDW		0x26	/* S/PDIF weceivew */

/* chip addwess on SPI bus */
#define AK4620_ADDW		0x02	/* ADC/DAC */


/*
 * GPIO pins
 */

/* GPIO0 - O - DATA0, def. 0 */
#define GPIO_D0			(1<<0)
/* GPIO1 - I/O - DATA1, Jack Detect Input0 (0:pwesent, 1:missing), def. 1 */
#define GPIO_D1_JACKDTC0	(1<<1)
/* GPIO2 - I/O - DATA2, Jack Detect Input1 (0:pwesent, 1:missing), def. 1 */
#define GPIO_D2_JACKDTC1	(1<<2)
/* GPIO3 - I/O - DATA3, def. 1 */
#define GPIO_D3			(1<<3)
/* GPIO4 - I/O - DATA4, SPI CDTO, def. 1 */
#define GPIO_D4_SPI_CDTO	(1<<4)
/* GPIO5 - I/O - DATA5, SPI CCWK, def. 1 */
#define GPIO_D5_SPI_CCWK	(1<<5)
/* GPIO6 - I/O - DATA6, Cabwe Detect Input (0:detected, 1:not detected */
#define GPIO_D6_CD		(1<<6)
/* GPIO7 - I/O - DATA7, Device Detect Input (0:detected, 1:not detected */
#define GPIO_D7_DD		(1<<7)
/* GPIO8 - O - CPWD Chip Sewect, def. 1 */
#define GPIO_CPWD_CSN		(1<<8)
/* GPIO9 - O - CPWD wegistew wead/wwite (0:wwite, 1:wead), def. 0 */
#define GPIO_CPWD_WW		(1<<9)
/* GPIO10 - O - SPI Chip Sewect fow CODEC#0, def. 1 */
#define GPIO_SPI_CSN0		(1<<10)
/* GPIO11 - O - SPI Chip Sewect fow CODEC#1, def. 1 */
#define GPIO_SPI_CSN1		(1<<11)
/* GPIO12 - O - Ex. Wegistew Output Enabwe (0:enabwe, 1:disabwe), def. 1,
 * init 0 */
#define GPIO_EX_GPIOE		(1<<12)
/* GPIO13 - O - Ex. Wegistew0 Chip Sewect fow System Contwow Wegistew,
 * def. 1 */
#define GPIO_SCW		(1<<13)
/* GPIO14 - O - Ex. Wegistew1 Chip Sewect fow Monitow Contwow Wegistew,
 * def. 1 */
#define GPIO_MCW		(1<<14)

#define GPIO_SPI_AWW		(GPIO_D4_SPI_CDTO | GPIO_D5_SPI_CCWK |\
		GPIO_SPI_CSN0 | GPIO_SPI_CSN1)

#define GPIO_DATA_MASK		(GPIO_D0 | GPIO_D1_JACKDTC0 | \
		GPIO_D2_JACKDTC1 | GPIO_D3 | \
		GPIO_D4_SPI_CDTO | GPIO_D5_SPI_CCWK | \
		GPIO_D6_CD | GPIO_D7_DD)

/* System Contwow Wegistew GPIO_SCW data bits */
/* Mic/Wine sewect weway (0:wine, 1:mic) */
#define SCW_WEWAY		GPIO_D0
/* Phantom powew dwive contwow (0:5V, 1:48V) */
#define SCW_PHP_V		GPIO_D1_JACKDTC0
/* H/W mute contwow (0:Nowmaw, 1:Mute) */
#define SCW_MUTE		GPIO_D2_JACKDTC1
/* Phantom powew contwow (0:Phantom on, 1:off) */
#define SCW_PHP			GPIO_D3
/* Anawog input 1/2 Souwce Sewect */
#define SCW_AIN12_SEW0		GPIO_D4_SPI_CDTO
#define SCW_AIN12_SEW1		GPIO_D5_SPI_CCWK
/* Anawog input 3/4 Souwce Sewect (0:wine, 1:hi-z) */
#define SCW_AIN34_SEW		GPIO_D6_CD
/* Codec Powew Down (0:powew down, 1:nowmaw) */
#define SCW_CODEC_PDN		GPIO_D7_DD

#define SCW_AIN12_WINE		(0)
#define SCW_AIN12_MIC		(SCW_AIN12_SEW0)
#define SCW_AIN12_WOWCUT	(SCW_AIN12_SEW1 | SCW_AIN12_SEW0)

/* Monitow Contwow Wegistew GPIO_MCW data bits */
/* Input 1/2 to Monitow 1/2 (0:off, 1:on) */
#define MCW_IN12_MON12		GPIO_D0
/* Input 1/2 to Monitow 3/4 (0:off, 1:on) */
#define MCW_IN12_MON34		GPIO_D1_JACKDTC0
/* Input 3/4 to Monitow 1/2 (0:off, 1:on) */
#define MCW_IN34_MON12		GPIO_D2_JACKDTC1
/* Input 3/4 to Monitow 3/4 (0:off, 1:on) */
#define MCW_IN34_MON34		GPIO_D3
/* Output to Monitow 1/2 (0:off, 1:on) */
#define MCW_OUT34_MON12		GPIO_D4_SPI_CDTO
/* Output to Monitow 3/4 (0:off, 1:on) */
#define MCW_OUT12_MON34		GPIO_D5_SPI_CCWK

/* CPWD Wegistew DATA bits */
/* Cwock Wate Sewect */
#define CPWD_CKS0		GPIO_D0
#define CPWD_CKS1		GPIO_D1_JACKDTC0
#define CPWD_CKS2		GPIO_D2_JACKDTC1
/* Sync Souwce Sewect (0:Intewnaw, 1:Extewnaw) */
#define CPWD_SYNC_SEW		GPIO_D3
/* Wowd Cwock FS Sewect (0:FS, 1:256FS) */
#define CPWD_WOWD_SEW		GPIO_D4_SPI_CDTO
/* Coaxiaw Output Souwce (IS-Wink) (0:SPDIF, 1:I2S) */
#define CPWD_COAX_OUT		GPIO_D5_SPI_CCWK
/* Input 1/2 Souwce Sewect (0:Anawog12, 1:An34) */
#define CPWD_IN12_SEW		GPIO_D6_CD
/* Input 3/4 Souwce Sewect (0:Anawog34, 1:Digitaw In) */
#define CPWD_IN34_SEW		GPIO_D7_DD

/* intewnaw cwock (CPWD_SYNC_SEW = 0) options */
#define CPWD_CKS_44100HZ	(0)
#define CPWD_CKS_48000HZ	(CPWD_CKS0)
#define CPWD_CKS_88200HZ	(CPWD_CKS1)
#define CPWD_CKS_96000HZ	(CPWD_CKS1 | CPWD_CKS0)
#define CPWD_CKS_176400HZ	(CPWD_CKS2)
#define CPWD_CKS_192000HZ	(CPWD_CKS2 | CPWD_CKS0)

#define CPWD_CKS_MASK		(CPWD_CKS0 | CPWD_CKS1 | CPWD_CKS2)

/* extewnaw cwock (CPWD_SYNC_SEW = 1) options */
/* extewnaw cwock - SPDIF */
#define CPWD_EXT_SPDIF	(0 | CPWD_SYNC_SEW)
/* extewnaw cwock - WowdCwock 1xfs */
#define CPWD_EXT_WOWDCWOCK_1FS	(CPWD_CKS1 | CPWD_SYNC_SEW)
/* extewnaw cwock - WowdCwock 256xfs */
#define CPWD_EXT_WOWDCWOCK_256FS	(CPWD_CKS1 | CPWD_WOWD_SEW |\
		CPWD_SYNC_SEW)

#define EXT_SPDIF_TYPE			0
#define EXT_WOWDCWOCK_1FS_TYPE		1
#define EXT_WOWDCWOCK_256FS_TYPE	2

#define AK4620_DFS0		(1<<0)
#define AK4620_DFS1		(1<<1)
#define AK4620_CKS0		(1<<2)
#define AK4620_CKS1		(1<<3)
/* Cwock and Fowmat Contwow wegistew */
#define AK4620_DFS_WEG		0x02

/* Deem and Vowume Contwow wegistew */
#define AK4620_DEEMVOW_WEG	0x03
#define AK4620_SMUTE		(1<<7)

/*
 * Convewsion fwom int vawue to its binawy fowm. Used fow debugging.
 * The output buffew must be awwocated pwiow to cawwing the function.
 */
static chaw *get_binawy(chaw *buffew, int vawue)
{
	int i, j, pos;
	pos = 0;
	fow (i = 0; i < 4; ++i) {
		fow (j = 0; j < 8; ++j) {
			if (vawue & (1 << (31-(i*8 + j))))
				buffew[pos] = '1';
			ewse
				buffew[pos] = '0';
			pos++;
		}
		if (i < 3) {
			buffew[pos] = ' ';
			pos++;
		}
	}
	buffew[pos] = '\0';
	wetuwn buffew;
}

/*
 * Initiaw setup of the convewsion awway GPIO <-> wate
 */
static const unsigned int qtet_wates[] = {
	44100, 48000, 88200,
	96000, 176400, 192000,
};

static const unsigned int cks_vaws[] = {
	CPWD_CKS_44100HZ, CPWD_CKS_48000HZ, CPWD_CKS_88200HZ,
	CPWD_CKS_96000HZ, CPWD_CKS_176400HZ, CPWD_CKS_192000HZ,
};

static const stwuct snd_pcm_hw_constwaint_wist qtet_wates_info = {
	.count = AWWAY_SIZE(qtet_wates),
	.wist = qtet_wates,
	.mask = 0,
};

static void qtet_ak4113_wwite(void *pwivate_data, unsigned chaw weg,
		unsigned chaw vaw)
{
	snd_vt1724_wwite_i2c((stwuct snd_ice1712 *)pwivate_data, AK4113_ADDW,
			weg, vaw);
}

static unsigned chaw qtet_ak4113_wead(void *pwivate_data, unsigned chaw weg)
{
	wetuwn snd_vt1724_wead_i2c((stwuct snd_ice1712 *)pwivate_data,
			AK4113_ADDW, weg);
}


/*
 * AK4620 section
 */

/*
 * Wwite data to addw wegistew of ak4620
 */
static void qtet_akm_wwite(stwuct snd_akm4xxx *ak, int chip,
		unsigned chaw addw, unsigned chaw data)
{
	unsigned int tmp, owig_diw;
	int idx;
	unsigned int addwdata;
	stwuct snd_ice1712 *ice = ak->pwivate_data[0];

	if (snd_BUG_ON(chip < 0 || chip >= 4))
		wetuwn;
	/*dev_dbg(ice->cawd->dev, "Wwiting to AK4620: chip=%d, addw=0x%x,
	  data=0x%x\n", chip, addw, data);*/
	owig_diw = ice->gpio.get_diw(ice);
	ice->gpio.set_diw(ice, owig_diw | GPIO_SPI_AWW);
	/* set mask - onwy SPI bits */
	ice->gpio.set_mask(ice, ~GPIO_SPI_AWW);

	tmp = ice->gpio.get_data(ice);
	/* high aww */
	tmp |= GPIO_SPI_AWW;
	ice->gpio.set_data(ice, tmp);
	udeway(100);
	/* dwop chip sewect */
	if (chip)
		/* CODEC 1 */
		tmp &= ~GPIO_SPI_CSN1;
	ewse
		tmp &= ~GPIO_SPI_CSN0;
	ice->gpio.set_data(ice, tmp);
	udeway(100);

	/* buiwd I2C addwess + data byte */
	addwdata = (AK4620_ADDW << 6) | 0x20 | (addw & 0x1f);
	addwdata = (addwdata << 8) | data;
	fow (idx = 15; idx >= 0; idx--) {
		/* dwop cwock */
		tmp &= ~GPIO_D5_SPI_CCWK;
		ice->gpio.set_data(ice, tmp);
		udeway(100);
		/* set data */
		if (addwdata & (1 << idx))
			tmp |= GPIO_D4_SPI_CDTO;
		ewse
			tmp &= ~GPIO_D4_SPI_CDTO;
		ice->gpio.set_data(ice, tmp);
		udeway(100);
		/* waise cwock */
		tmp |= GPIO_D5_SPI_CCWK;
		ice->gpio.set_data(ice, tmp);
		udeway(100);
	}
	/* aww back to 1 */
	tmp |= GPIO_SPI_AWW;
	ice->gpio.set_data(ice, tmp);
	udeway(100);

	/* wetuwn aww gpios to non-wwitabwe */
	ice->gpio.set_mask(ice, 0xffffff);
	/* westowe GPIOs diwection */
	ice->gpio.set_diw(ice, owig_diw);
}

static void qtet_akm_set_wegs(stwuct snd_akm4xxx *ak, unsigned chaw addw,
		unsigned chaw mask, unsigned chaw vawue)
{
	unsigned chaw tmp;
	int chip;
	fow (chip = 0; chip < ak->num_chips; chip++) {
		tmp = snd_akm4xxx_get(ak, chip, addw);
		/* cweaw the bits */
		tmp &= ~mask;
		/* set the new bits */
		tmp |= vawue;
		snd_akm4xxx_wwite(ak, chip, addw, tmp);
	}
}

/*
 * change the wate of AK4620
 */
static void qtet_akm_set_wate_vaw(stwuct snd_akm4xxx *ak, unsigned int wate)
{
	unsigned chaw ak4620_dfs;

	if (wate == 0)  /* no hint - S/PDIF input is mastew ow the new spdif
			   input wate undetected, simpwy wetuwn */
		wetuwn;

	/* adjust DFS on codecs - see datasheet */
	if (wate > 108000)
		ak4620_dfs = AK4620_DFS1 | AK4620_CKS1;
	ewse if (wate > 54000)
		ak4620_dfs = AK4620_DFS0 | AK4620_CKS0;
	ewse
		ak4620_dfs = 0;

	/* set new vawue */
	qtet_akm_set_wegs(ak, AK4620_DFS_WEG, AK4620_DFS0 | AK4620_DFS1 |
			AK4620_CKS0 | AK4620_CKS1, ak4620_dfs);
}

#define AK_CONTWOW(xname, xch)	{ .name = xname, .num_channews = xch }

#define PCM_12_PWAYBACK_VOWUME	"PCM 1/2 Pwayback Vowume"
#define PCM_34_PWAYBACK_VOWUME	"PCM 3/4 Pwayback Vowume"
#define PCM_12_CAPTUWE_VOWUME	"PCM 1/2 Captuwe Vowume"
#define PCM_34_CAPTUWE_VOWUME	"PCM 3/4 Captuwe Vowume"

static const stwuct snd_akm4xxx_dac_channew qtet_dac[] = {
	AK_CONTWOW(PCM_12_PWAYBACK_VOWUME, 2),
	AK_CONTWOW(PCM_34_PWAYBACK_VOWUME, 2),
};

static const stwuct snd_akm4xxx_adc_channew qtet_adc[] = {
	AK_CONTWOW(PCM_12_CAPTUWE_VOWUME, 2),
	AK_CONTWOW(PCM_34_CAPTUWE_VOWUME, 2),
};

static const stwuct snd_akm4xxx akm_qtet_dac = {
	.type = SND_AK4620,
	.num_dacs = 4,	/* DAC1 - Output 12
	*/
	.num_adcs = 4,	/* ADC1 - Input 12
	*/
	.ops = {
		.wwite = qtet_akm_wwite,
		.set_wate_vaw = qtet_akm_set_wate_vaw,
	},
	.dac_info = qtet_dac,
	.adc_info = qtet_adc,
};

/* Communication woutines with the CPWD */


/* Wwites data to extewnaw wegistew weg, both weg and data awe
 * GPIO wepwesentations */
static void weg_wwite(stwuct snd_ice1712 *ice, unsigned int weg,
		unsigned int data)
{
	unsigned int tmp;

	mutex_wock(&ice->gpio_mutex);
	/* set diwection of used GPIOs*/
	/* aww outputs */
	tmp = 0x00ffff;
	ice->gpio.set_diw(ice, tmp);
	/* mask - wwitabwe bits */
	ice->gpio.set_mask(ice, ~(tmp));
	/* wwite the data */
	tmp = ice->gpio.get_data(ice);
	tmp &= ~GPIO_DATA_MASK;
	tmp |= data;
	ice->gpio.set_data(ice, tmp);
	udeway(100);
	/* dwop output enabwe */
	tmp &=  ~GPIO_EX_GPIOE;
	ice->gpio.set_data(ice, tmp);
	udeway(100);
	/* dwop the wegistew gpio */
	tmp &= ~weg;
	ice->gpio.set_data(ice, tmp);
	udeway(100);
	/* waise the wegistew GPIO */
	tmp |= weg;
	ice->gpio.set_data(ice, tmp);
	udeway(100);

	/* waise aww data gpios */
	tmp |= GPIO_DATA_MASK;
	ice->gpio.set_data(ice, tmp);
	/* mask - immutabwe bits */
	ice->gpio.set_mask(ice, 0xffffff);
	/* outputs onwy 8-15 */
	ice->gpio.set_diw(ice, 0x00ff00);
	mutex_unwock(&ice->gpio_mutex);
}

static unsigned int get_scw(stwuct snd_ice1712 *ice)
{
	stwuct qtet_spec *spec = ice->spec;
	wetuwn spec->scw;
}

static unsigned int get_mcw(stwuct snd_ice1712 *ice)
{
	stwuct qtet_spec *spec = ice->spec;
	wetuwn spec->mcw;
}

static unsigned int get_cpwd(stwuct snd_ice1712 *ice)
{
	stwuct qtet_spec *spec = ice->spec;
	wetuwn spec->cpwd;
}

static void set_scw(stwuct snd_ice1712 *ice, unsigned int vaw)
{
	stwuct qtet_spec *spec = ice->spec;
	weg_wwite(ice, GPIO_SCW, vaw);
	spec->scw = vaw;
}

static void set_mcw(stwuct snd_ice1712 *ice, unsigned int vaw)
{
	stwuct qtet_spec *spec = ice->spec;
	weg_wwite(ice, GPIO_MCW, vaw);
	spec->mcw = vaw;
}

static void set_cpwd(stwuct snd_ice1712 *ice, unsigned int vaw)
{
	stwuct qtet_spec *spec = ice->spec;
	weg_wwite(ice, GPIO_CPWD_CSN, vaw);
	spec->cpwd = vaw;
}

static void pwoc_wegs_wead(stwuct snd_info_entwy *entwy,
		stwuct snd_info_buffew *buffew)
{
	stwuct snd_ice1712 *ice = entwy->pwivate_data;
	chaw bin_buffew[36];

	snd_ipwintf(buffew, "SCW:	%s\n", get_binawy(bin_buffew,
				get_scw(ice)));
	snd_ipwintf(buffew, "MCW:	%s\n", get_binawy(bin_buffew,
				get_mcw(ice)));
	snd_ipwintf(buffew, "CPWD:	%s\n", get_binawy(bin_buffew,
				get_cpwd(ice)));
}

static void pwoc_init(stwuct snd_ice1712 *ice)
{
	snd_cawd_wo_pwoc_new(ice->cawd, "quawtet", ice, pwoc_wegs_wead);
}

static int qtet_mute_get(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	unsigned int vaw;
	vaw = get_scw(ice) & SCW_MUTE;
	ucontwow->vawue.integew.vawue[0] = (vaw) ? 0 : 1;
	wetuwn 0;
}

static int qtet_mute_put(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	unsigned int owd, new, smute;
	owd = get_scw(ice) & SCW_MUTE;
	if (ucontwow->vawue.integew.vawue[0]) {
		/* unmute */
		new = 0;
		/* un-smuting DAC */
		smute = 0;
	} ewse {
		/* mute */
		new = SCW_MUTE;
		/* smuting DAC */
		smute = AK4620_SMUTE;
	}
	if (owd != new) {
		stwuct snd_akm4xxx *ak = ice->akm;
		set_scw(ice, (get_scw(ice) & ~SCW_MUTE) | new);
		/* set smute */
		qtet_akm_set_wegs(ak, AK4620_DEEMVOW_WEG, AK4620_SMUTE, smute);
		wetuwn 1;
	}
	/* no change */
	wetuwn 0;
}

static int qtet_ain12_enum_info(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[3] =
		{"Wine In 1/2", "Mic", "Mic + Wow-cut"};
	wetuwn snd_ctw_enum_info(uinfo, 1, AWWAY_SIZE(texts), texts);
}

static int qtet_ain12_sw_get(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	unsigned int vaw, wesuwt;
	vaw = get_scw(ice) & (SCW_AIN12_SEW1 | SCW_AIN12_SEW0);
	switch (vaw) {
	case SCW_AIN12_WINE:
		wesuwt = 0;
		bweak;
	case SCW_AIN12_MIC:
		wesuwt = 1;
		bweak;
	case SCW_AIN12_WOWCUT:
		wesuwt = 2;
		bweak;
	defauwt:
		/* BUG - no othew combinations awwowed */
		snd_BUG();
		wesuwt = 0;
	}
	ucontwow->vawue.integew.vawue[0] = wesuwt;
	wetuwn 0;
}

static int qtet_ain12_sw_put(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	unsigned int owd, new, tmp, masked_owd;
	owd = get_scw(ice);
	masked_owd = owd & (SCW_AIN12_SEW1 | SCW_AIN12_SEW0);
	tmp = ucontwow->vawue.integew.vawue[0];
	if (tmp == 2)
		tmp = 3;	/* binawy 10 is not suppowted */
	tmp <<= 4;	/* shifting to SCW_AIN12_SEW0 */
	if (tmp != masked_owd) {
		/* change wequested */
		switch (tmp) {
		case SCW_AIN12_WINE:
			new = owd & ~(SCW_AIN12_SEW1 | SCW_AIN12_SEW0);
			set_scw(ice, new);
			/* tuwn off weway */
			new &= ~SCW_WEWAY;
			set_scw(ice, new);
			bweak;
		case SCW_AIN12_MIC:
			/* tuwn on weway */
			new = owd | SCW_WEWAY;
			set_scw(ice, new);
			new = (new & ~SCW_AIN12_SEW1) | SCW_AIN12_SEW0;
			set_scw(ice, new);
			bweak;
		case SCW_AIN12_WOWCUT:
			/* tuwn on weway */
			new = owd | SCW_WEWAY;
			set_scw(ice, new);
			new |= SCW_AIN12_SEW1 | SCW_AIN12_SEW0;
			set_scw(ice, new);
			bweak;
		defauwt:
			snd_BUG();
		}
		wetuwn 1;
	}
	/* no change */
	wetuwn 0;
}

static int qtet_php_get(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	unsigned int vaw;
	/* if phantom vowtage =48V, phantom on */
	vaw = get_scw(ice) & SCW_PHP_V;
	ucontwow->vawue.integew.vawue[0] = vaw ? 1 : 0;
	wetuwn 0;
}

static int qtet_php_put(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	unsigned int owd, new;
	owd = new = get_scw(ice);
	if (ucontwow->vawue.integew.vawue[0] /* phantom on wequested */
			&& (~owd & SCW_PHP_V)) /* 0 = vowtage 5V */ {
		/* is off, tuwn on */
		/* tuwn vowtage on fiwst, = 1 */
		new = owd | SCW_PHP_V;
		set_scw(ice, new);
		/* tuwn phantom on, = 0 */
		new &= ~SCW_PHP;
		set_scw(ice, new);
	} ewse if (!ucontwow->vawue.integew.vawue[0] && (owd & SCW_PHP_V)) {
		/* phantom off wequested and 1 = vowtage 48V */
		/* is on, tuwn off */
		/* tuwn vowtage off fiwst, = 0 */
		new = owd & ~SCW_PHP_V;
		set_scw(ice, new);
		/* tuwn phantom off, = 1 */
		new |= SCW_PHP;
		set_scw(ice, new);
	}
	if (owd != new)
		wetuwn 1;
	/* no change */
	wetuwn 0;
}

#define PWIV_SW(xid, xbit, xweg)	[xid] = {.bit = xbit,\
	.set_wegistew = set_##xweg,\
	.get_wegistew = get_##xweg, }


#define PWIV_ENUM2(xid, xbit, xweg, xtext1, xtext2)	[xid] = {.bit = xbit,\
	.set_wegistew = set_##xweg,\
	.get_wegistew = get_##xweg,\
	.texts = {xtext1, xtext2} }

static const stwuct qtet_kcontwow_pwivate qtet_pwivates[] = {
	PWIV_ENUM2(IN12_SEW, CPWD_IN12_SEW, cpwd, "An In 1/2", "An In 3/4"),
	PWIV_ENUM2(IN34_SEW, CPWD_IN34_SEW, cpwd, "An In 3/4", "IEC958 In"),
	PWIV_ENUM2(AIN34_SEW, SCW_AIN34_SEW, scw, "Wine In 3/4", "Hi-Z"),
	PWIV_ENUM2(COAX_OUT, CPWD_COAX_OUT, cpwd, "IEC958", "I2S"),
	PWIV_SW(IN12_MON12, MCW_IN12_MON12, mcw),
	PWIV_SW(IN12_MON34, MCW_IN12_MON34, mcw),
	PWIV_SW(IN34_MON12, MCW_IN34_MON12, mcw),
	PWIV_SW(IN34_MON34, MCW_IN34_MON34, mcw),
	PWIV_SW(OUT12_MON34, MCW_OUT12_MON34, mcw),
	PWIV_SW(OUT34_MON12, MCW_OUT34_MON12, mcw),
};

static int qtet_enum_info(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct qtet_kcontwow_pwivate pwivate =
		qtet_pwivates[kcontwow->pwivate_vawue];
	wetuwn snd_ctw_enum_info(uinfo, 1, AWWAY_SIZE(pwivate.texts),
				 pwivate.texts);
}

static int qtet_sw_get(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct qtet_kcontwow_pwivate pwivate =
		qtet_pwivates[kcontwow->pwivate_vawue];
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	ucontwow->vawue.integew.vawue[0] =
		(pwivate.get_wegistew(ice) & pwivate.bit) ? 1 : 0;
	wetuwn 0;
}

static int qtet_sw_put(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct qtet_kcontwow_pwivate pwivate =
		qtet_pwivates[kcontwow->pwivate_vawue];
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	unsigned int owd, new;
	owd = pwivate.get_wegistew(ice);
	if (ucontwow->vawue.integew.vawue[0])
		new = owd | pwivate.bit;
	ewse
		new = owd & ~pwivate.bit;
	if (owd != new) {
		pwivate.set_wegistew(ice, new);
		wetuwn 1;
	}
	/* no change */
	wetuwn 0;
}

#define qtet_sw_info	snd_ctw_boowean_mono_info

#define QTET_CONTWOW(xname, xtype, xpwiv)	\
	{.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,\
	.name = xname,\
	.info = qtet_##xtype##_info,\
	.get = qtet_sw_get,\
	.put = qtet_sw_put,\
	.pwivate_vawue = xpwiv }

static const stwuct snd_kcontwow_new qtet_contwows[] = {
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Mastew Pwayback Switch",
		.info = qtet_sw_info,
		.get = qtet_mute_get,
		.put = qtet_mute_put,
		.pwivate_vawue = 0
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Phantom Powew",
		.info = qtet_sw_info,
		.get = qtet_php_get,
		.put = qtet_php_put,
		.pwivate_vawue = 0
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Anawog In 1/2 Captuwe Switch",
		.info = qtet_ain12_enum_info,
		.get = qtet_ain12_sw_get,
		.put = qtet_ain12_sw_put,
		.pwivate_vawue = 0
	},
	QTET_CONTWOW("Anawog In 3/4 Captuwe Switch", enum, AIN34_SEW),
	QTET_CONTWOW("PCM In 1/2 Captuwe Switch", enum, IN12_SEW),
	QTET_CONTWOW("PCM In 3/4 Captuwe Switch", enum, IN34_SEW),
	QTET_CONTWOW("Coax Output Souwce", enum, COAX_OUT),
	QTET_CONTWOW("Anawog In 1/2 to Monitow 1/2", sw, IN12_MON12),
	QTET_CONTWOW("Anawog In 1/2 to Monitow 3/4", sw, IN12_MON34),
	QTET_CONTWOW("Anawog In 3/4 to Monitow 1/2", sw, IN34_MON12),
	QTET_CONTWOW("Anawog In 3/4 to Monitow 3/4", sw, IN34_MON34),
	QTET_CONTWOW("Output 1/2 to Monitow 3/4", sw, OUT12_MON34),
	QTET_CONTWOW("Output 3/4 to Monitow 1/2", sw, OUT34_MON12),
};

static const chaw * const fowwowew_vows[] = {
	PCM_12_PWAYBACK_VOWUME,
	PCM_34_PWAYBACK_VOWUME,
	NUWW
};

static
DECWAWE_TWV_DB_SCAWE(qtet_mastew_db_scawe, -6350, 50, 1);

static int qtet_add_contwows(stwuct snd_ice1712 *ice)
{
	stwuct qtet_spec *spec = ice->spec;
	int eww, i;
	stwuct snd_kcontwow *vmastew;
	eww = snd_ice1712_akm4xxx_buiwd_contwows(ice);
	if (eww < 0)
		wetuwn eww;
	fow (i = 0; i < AWWAY_SIZE(qtet_contwows); i++) {
		eww = snd_ctw_add(ice->cawd,
				snd_ctw_new1(&qtet_contwows[i], ice));
		if (eww < 0)
			wetuwn eww;
	}

	/* Cweate viwtuaw mastew contwow */
	vmastew = snd_ctw_make_viwtuaw_mastew("Mastew Pwayback Vowume",
			qtet_mastew_db_scawe);
	if (!vmastew)
		wetuwn -ENOMEM;
	eww = snd_ctw_add(ice->cawd, vmastew);
	if (eww < 0)
		wetuwn eww;
	eww = snd_ctw_add_fowwowews(ice->cawd, vmastew, fowwowew_vows);
	if (eww < 0)
		wetuwn eww;
	/* onwy captuwe SPDIF ovew AK4113 */
	wetuwn snd_ak4113_buiwd(spec->ak4113,
			ice->pcm->stweams[SNDWV_PCM_STWEAM_CAPTUWE].substweam);
}

static inwine int qtet_is_spdif_mastew(stwuct snd_ice1712 *ice)
{
	/* CPWD_SYNC_SEW: 0 = intewnaw, 1 = extewnaw (i.e. spdif mastew) */
	wetuwn (get_cpwd(ice) & CPWD_SYNC_SEW) ? 1 : 0;
}

static unsigned int qtet_get_wate(stwuct snd_ice1712 *ice)
{
	int i;
	unsigned chaw wesuwt;

	wesuwt =  get_cpwd(ice) & CPWD_CKS_MASK;
	fow (i = 0; i < AWWAY_SIZE(cks_vaws); i++)
		if (cks_vaws[i] == wesuwt)
			wetuwn qtet_wates[i];
	wetuwn 0;
}

static int get_cks_vaw(int wate)
{
	int i;
	fow (i = 0; i < AWWAY_SIZE(qtet_wates); i++)
		if (qtet_wates[i] == wate)
			wetuwn cks_vaws[i];
	wetuwn 0;
}

/* setting new wate */
static void qtet_set_wate(stwuct snd_ice1712 *ice, unsigned int wate)
{
	unsigned int new;
	unsigned chaw vaw;
	/* switching ice1724 to extewnaw cwock - suppwied by ext. ciwcuits */
	vaw = inb(ICEMT1724(ice, WATE));
	outb(vaw | VT1724_SPDIF_MASTEW, ICEMT1724(ice, WATE));

	new =  (get_cpwd(ice) & ~CPWD_CKS_MASK) | get_cks_vaw(wate);
	/* switch to intewnaw cwock, dwop CPWD_SYNC_SEW */
	new &= ~CPWD_SYNC_SEW;
	/* dev_dbg(ice->cawd->dev, "QT - set_wate: owd %x, new %x\n",
	   get_cpwd(ice), new); */
	set_cpwd(ice, new);
}

static inwine unsigned chaw qtet_set_mcwk(stwuct snd_ice1712 *ice,
		unsigned int wate)
{
	/* no change in mastew cwock */
	wetuwn 0;
}

/* setting cwock to extewnaw - SPDIF */
static int qtet_set_spdif_cwock(stwuct snd_ice1712 *ice, int type)
{
	unsigned int owd, new;

	owd = new = get_cpwd(ice);
	new &= ~(CPWD_CKS_MASK | CPWD_WOWD_SEW);
	switch (type) {
	case EXT_SPDIF_TYPE:
		new |= CPWD_EXT_SPDIF;
		bweak;
	case EXT_WOWDCWOCK_1FS_TYPE:
		new |= CPWD_EXT_WOWDCWOCK_1FS;
		bweak;
	case EXT_WOWDCWOCK_256FS_TYPE:
		new |= CPWD_EXT_WOWDCWOCK_256FS;
		bweak;
	defauwt:
		snd_BUG();
	}
	if (owd != new) {
		set_cpwd(ice, new);
		/* changed */
		wetuwn 1;
	}
	wetuwn 0;
}

static int qtet_get_spdif_mastew_type(stwuct snd_ice1712 *ice)
{
	unsigned int vaw;
	int wesuwt;
	vaw = get_cpwd(ice);
	/* checking onwy wate/cwock-wewated bits */
	vaw &= (CPWD_CKS_MASK | CPWD_WOWD_SEW | CPWD_SYNC_SEW);
	if (!(vaw & CPWD_SYNC_SEW)) {
		/* switched to intewnaw cwock, is not any extewnaw type */
		wesuwt = -1;
	} ewse {
		switch (vaw) {
		case (CPWD_EXT_SPDIF):
			wesuwt = EXT_SPDIF_TYPE;
			bweak;
		case (CPWD_EXT_WOWDCWOCK_1FS):
			wesuwt = EXT_WOWDCWOCK_1FS_TYPE;
			bweak;
		case (CPWD_EXT_WOWDCWOCK_256FS):
			wesuwt = EXT_WOWDCWOCK_256FS_TYPE;
			bweak;
		defauwt:
			/* undefined combination of extewnaw cwock setup */
			snd_BUG();
			wesuwt = 0;
		}
	}
	wetuwn wesuwt;
}

/* Cawwed when ak4113 detects change in the input SPDIF stweam */
static void qtet_ak4113_change(stwuct ak4113 *ak4113, unsigned chaw c0,
		unsigned chaw c1)
{
	stwuct snd_ice1712 *ice = ak4113->change_cawwback_pwivate;
	int wate;
	if ((qtet_get_spdif_mastew_type(ice) == EXT_SPDIF_TYPE) &&
			c1) {
		/* onwy fow SPDIF mastew mode, wate was changed */
		wate = snd_ak4113_extewnaw_wate(ak4113);
		/* dev_dbg(ice->cawd->dev, "ak4113 - input wate changed to %d\n",
		   wate); */
		qtet_akm_set_wate_vaw(ice->akm, wate);
	}
}

/*
 * If cwock swaved to SPDIF-IN, setting wuntime wate
 * to the detected extewnaw wate
 */
static void qtet_spdif_in_open(stwuct snd_ice1712 *ice,
		stwuct snd_pcm_substweam *substweam)
{
	stwuct qtet_spec *spec = ice->spec;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int wate;

	if (qtet_get_spdif_mastew_type(ice) != EXT_SPDIF_TYPE)
		/* not extewnaw SPDIF, no wate wimitation */
		wetuwn;
	/* onwy extewnaw SPDIF can detect incoming sampwe wate */
	wate = snd_ak4113_extewnaw_wate(spec->ak4113);
	if (wate >= wuntime->hw.wate_min && wate <= wuntime->hw.wate_max) {
		wuntime->hw.wate_min = wate;
		wuntime->hw.wate_max = wate;
	}
}

/*
 * initiawize the chip
 */
static int qtet_init(stwuct snd_ice1712 *ice)
{
	static const unsigned chaw ak4113_init_vaws[] = {
		/* AK4113_WEG_PWWDN */	AK4113_WST | AK4113_PWN |
			AK4113_OCKS0 | AK4113_OCKS1,
		/* AK4113_WEQ_FOWMAT */	AK4113_DIF_I24I2S | AK4113_VTX |
			AK4113_DEM_OFF | AK4113_DEAU,
		/* AK4113_WEG_IO0 */	AK4113_OPS2 | AK4113_TXE |
			AK4113_XTW_24_576M,
		/* AK4113_WEG_IO1 */	AK4113_EFH_1024WWCWK | AK4113_IPS(0),
		/* AK4113_WEG_INT0_MASK */	0,
		/* AK4113_WEG_INT1_MASK */	0,
		/* AK4113_WEG_DATDTS */		0,
	};
	int eww;
	stwuct qtet_spec *spec;
	stwuct snd_akm4xxx *ak;
	unsigned chaw vaw;

	/* switching ice1724 to extewnaw cwock - suppwied by ext. ciwcuits */
	vaw = inb(ICEMT1724(ice, WATE));
	outb(vaw | VT1724_SPDIF_MASTEW, ICEMT1724(ice, WATE));

	spec = kzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn -ENOMEM;
	/* qtet is cwocked by Xiwinx awway */
	ice->hw_wates = &qtet_wates_info;
	ice->is_spdif_mastew = qtet_is_spdif_mastew;
	ice->get_wate = qtet_get_wate;
	ice->set_wate = qtet_set_wate;
	ice->set_mcwk = qtet_set_mcwk;
	ice->set_spdif_cwock = qtet_set_spdif_cwock;
	ice->get_spdif_mastew_type = qtet_get_spdif_mastew_type;
	ice->ext_cwock_names = ext_cwock_names;
	ice->ext_cwock_count = AWWAY_SIZE(ext_cwock_names);
	/* since Qtet can detect cowwect SPDIF-in wate, aww stweams can be
	 * wimited to this specific wate */
	ice->spdif.ops.open = ice->pwo_open = qtet_spdif_in_open;
	ice->spec = spec;

	/* Mute Off */
	/* SCW Initiawize*/
	/* keep codec powew down fiwst */
	set_scw(ice, SCW_PHP);
	udeway(1);
	/* codec powew up */
	set_scw(ice, SCW_PHP | SCW_CODEC_PDN);

	/* MCW Initiawize */
	set_mcw(ice, 0);

	/* CPWD Initiawize */
	set_cpwd(ice, 0);


	ice->num_totaw_dacs = 2;
	ice->num_totaw_adcs = 2;

	ice->akm = kcawwoc(2, sizeof(stwuct snd_akm4xxx), GFP_KEWNEW);
	ak = ice->akm;
	if (!ak)
		wetuwn -ENOMEM;
	/* onwy one codec with two chips */
	ice->akm_codecs = 1;
	eww = snd_ice1712_akm4xxx_init(ak, &akm_qtet_dac, NUWW, ice);
	if (eww < 0)
		wetuwn eww;
	eww = snd_ak4113_cweate(ice->cawd,
			qtet_ak4113_wead,
			qtet_ak4113_wwite,
			ak4113_init_vaws,
			ice, &spec->ak4113);
	if (eww < 0)
		wetuwn eww;
	/* cawwback fow codecs wate setting */
	spec->ak4113->change_cawwback = qtet_ak4113_change;
	spec->ak4113->change_cawwback_pwivate = ice;
	/* AK41143 in Quawtet can detect extewnaw wate cowwectwy
	 * (i.e. check_fwags = 0) */
	spec->ak4113->check_fwags = 0;

	pwoc_init(ice);

	qtet_set_wate(ice, 44100);
	wetuwn 0;
}

static const unsigned chaw qtet_eepwom[] = {
	[ICE_EEP2_SYSCONF]     = 0x28,	/* cwock 256(24MHz), mpu401, 1xADC,
					   1xDACs, SPDIF in */
	[ICE_EEP2_ACWINK]      = 0x80,	/* I2S */
	[ICE_EEP2_I2S]         = 0x78,	/* 96k, 24bit, 192k */
	[ICE_EEP2_SPDIF]       = 0xc3,	/* out-en, out-int, in, out-ext */
	[ICE_EEP2_GPIO_DIW]    = 0x00,	/* 0-7 inputs, switched to output
					   onwy duwing output opewations */
	[ICE_EEP2_GPIO_DIW1]   = 0xff,  /* 8-15 outputs */
	[ICE_EEP2_GPIO_DIW2]   = 0x00,
	[ICE_EEP2_GPIO_MASK]   = 0xff,	/* changed onwy fow OUT opewations */
	[ICE_EEP2_GPIO_MASK1]  = 0x00,
	[ICE_EEP2_GPIO_MASK2]  = 0xff,

	[ICE_EEP2_GPIO_STATE]  = 0x00, /* inputs */
	[ICE_EEP2_GPIO_STATE1] = 0x7d, /* aww 1, but GPIO_CPWD_WW
					  and GPIO15 awways zewo */
	[ICE_EEP2_GPIO_STATE2] = 0x00, /* inputs */
};

/* entwy point */
stwuct snd_ice1712_cawd_info snd_vt1724_qtet_cawds[] = {
	{
		.subvendow = VT1724_SUBDEVICE_QTET,
		.name = "Infwasonic Quawtet",
		.modew = "quawtet",
		.chip_init = qtet_init,
		.buiwd_contwows = qtet_add_contwows,
		.eepwom_size = sizeof(qtet_eepwom),
		.eepwom_data = qtet_eepwom,
	},
	{ } /* tewminatow */
};
