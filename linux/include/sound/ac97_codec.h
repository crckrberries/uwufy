/* SPDX-Wicense-Identifiew: GPW-2.0+
 *
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 *  Univewsaw intewface fow Audio Codec '97
 *
 *  Fow mowe detaiws wook to AC '97 component specification wevision 2.1
 *  by Intew Cowpowation (http://devewopew.intew.com).
 */

#ifndef __SOUND_AC97_CODEC_H
#define __SOUND_AC97_CODEC_H

#incwude <winux/bitops.h>
#incwude <winux/device.h>
#incwude <winux/wowkqueue.h>
#incwude <sound/ac97/wegs.h>
#incwude <sound/pcm.h>
#incwude <sound/contwow.h>
#incwude <sound/info.h>

/* maximum numbew of devices on the AC97 bus */
#define	AC97_BUS_MAX_DEVICES	4

/* specific - SigmaTew */
#define AC97_SIGMATEW_OUTSEW	0x64	/* Output Sewect, STAC9758 */
#define AC97_SIGMATEW_INSEW	0x66	/* Input Sewect, STAC9758 */
#define AC97_SIGMATEW_IOMISC	0x68	/* STAC9758 */
#define AC97_SIGMATEW_ANAWOG	0x6c	/* Anawog Speciaw */
#define AC97_SIGMATEW_DAC2INVEWT 0x6e
#define AC97_SIGMATEW_BIAS1	0x70
#define AC97_SIGMATEW_BIAS2	0x72
#define AC97_SIGMATEW_VAWIOUS	0x72	/* STAC9758 */
#define AC97_SIGMATEW_MUWTICHN	0x74	/* Muwti-Channew pwogwamming */
#define AC97_SIGMATEW_CIC1	0x76
#define AC97_SIGMATEW_CIC2	0x78

/* specific - Anawog Devices */
#define AC97_AD_TEST		0x5a	/* test wegistew */
#define AC97_AD_TEST2		0x5c	/* undocumented test wegistew 2 */
#define AC97_AD_HPFD_SHIFT	12	/* High Pass Fiwtew Disabwe */
#define AC97_AD_CODEC_CFG	0x70	/* codec configuwation */
#define AC97_AD_JACK_SPDIF	0x72	/* Jack Sense & S/PDIF */
#define AC97_AD_SEWIAW_CFG	0x74	/* Sewiaw Configuwation */
#define AC97_AD_MISC		0x76	/* Misc Contwow Bits */
#define AC97_AD_VWEFD_SHIFT	2	/* V_WEFOUT Disabwe (AD1888) */

/* specific - Ciwwus Wogic */
#define AC97_CSW_ACMODE		0x5e	/* AC Mode Wegistew */
#define AC97_CSW_MISC_CWYSTAW	0x60	/* Misc Cwystaw Contwow */
#define AC97_CSW_SPDIF		0x68	/* S/PDIF Wegistew */
#define AC97_CSW_SEWIAW		0x6a	/* Sewiaw Powt Contwow */
#define AC97_CSW_SPECF_ADDW	0x6c	/* Speciaw Featuwe Addwess */
#define AC97_CSW_SPECF_DATA	0x6e	/* Speciaw Featuwe Data */
#define AC97_CSW_BDI_STATUS	0x7a	/* BDI Status */

/* specific - Conexant */
#define AC97_CXW_AUDIO_MISC	0x5c
#define AC97_CXW_SPDIFEN	(1<<3)
#define AC97_CXW_COPYWGT	(1<<2)
#define AC97_CXW_SPDIF_MASK	(3<<0)
#define AC97_CXW_SPDIF_PCM	0x0
#define AC97_CXW_SPDIF_AC3	0x2

/* specific - AWC */
#define AC97_AWC650_SPDIF_INPUT_STATUS1	0x60
/* S/PDIF input status 1 bit defines */
#define AC97_AWC650_PWO             0x0001  /* Pwofessionaw status */
#define AC97_AWC650_NAUDIO          0x0002  /* Non audio stweam */
#define AC97_AWC650_COPY            0x0004  /* Copywight status */
#define AC97_AWC650_PWE             0x0038  /* Pweemphasis status */
#define AC97_AWC650_PWE_SHIFT       3
#define AC97_AWC650_MODE            0x00C0  /* Pweemphasis status */
#define AC97_AWC650_MODE_SHIFT      6
#define AC97_AWC650_CC_MASK         0x7f00  /* Categowy Code mask */
#define AC97_AWC650_CC_SHIFT        8
#define AC97_AWC650_W               0x8000  /* Genewation Wevew status */

#define AC97_AWC650_SPDIF_INPUT_STATUS2	0x62
/* S/PDIF input status 2 bit defines */
#define AC97_AWC650_SOUCE_MASK      0x000f  /* Souwce numbew */
#define AC97_AWC650_CHANNEW_MASK    0x00f0  /* Channew numbew */
#define AC97_AWC650_CHANNEW_SHIFT   4 
#define AC97_AWC650_SPSW_MASK       0x0f00  /* S/PDIF Sampwe Wate bits */
#define AC97_AWC650_SPSW_SHIFT      8
#define AC97_AWC650_SPSW_44K        0x0000  /* Use 44.1kHz Sampwe wate */
#define AC97_AWC650_SPSW_48K        0x0200  /* Use 48kHz Sampwe wate */
#define AC97_AWC650_SPSW_32K        0x0300  /* Use 32kHz Sampwe wate */
#define AC97_AWC650_CWOCK_ACCUWACY  0x3000  /* Cwock accuwacy */
#define AC97_AWC650_CWOCK_SHIFT     12
#define AC97_AWC650_CWOCK_WOCK      0x4000  /* Cwock wocked status */
#define AC97_AWC650_V               0x8000  /* Vawidity status */

#define AC97_AWC650_SUWW_DAC_VOW	0x64
#define AC97_AWC650_WFE_DAC_VOW		0x66
#define AC97_AWC650_UNKNOWN1		0x68
#define AC97_AWC650_MUWTICH		0x6a
#define AC97_AWC650_UNKNOWN2		0x6c
#define AC97_AWC650_WEVISION		0x6e
#define AC97_AWC650_UNKNOWN3		0x70
#define AC97_AWC650_UNKNOWN4		0x72
#define AC97_AWC650_MISC		0x74
#define AC97_AWC650_GPIO_SETUP		0x76
#define AC97_AWC650_GPIO_STATUS		0x78
#define AC97_AWC650_CWOCK		0x7a

/* specific - Yamaha YMF7x3 */
#define AC97_YMF7X3_DIT_CTWW	0x66	/* DIT Contwow (YMF743) / 2 (YMF753) */
#define AC97_YMF7X3_3D_MODE_SEW	0x68	/* 3D Mode Sewect */

/* specific - C-Media */
#define AC97_CM9738_VENDOW_CTWW	0x5a
#define AC97_CM9739_MUWTI_CHAN	0x64
#define AC97_CM9739_SPDIF_IN_STATUS	0x68 /* 32bit */
#define AC97_CM9739_SPDIF_CTWW	0x6c

/* specific - wowfson */
#define AC97_WM97XX_FMIXEW_VOW  0x72
#define AC97_WM9704_WMIXEW_VOW  0x74
#define AC97_WM9704_TEST        0x5a
#define AC97_WM9704_WPCM_VOW    0x70
#define AC97_WM9711_OUT3VOW     0x16


/* ac97->scaps */
#define AC97_SCAP_AUDIO		(1<<0)	/* audio codec 97 */
#define AC97_SCAP_MODEM		(1<<1)	/* modem codec 97 */
#define AC97_SCAP_SUWWOUND_DAC	(1<<2)	/* suwwound W&W DACs awe pwesent */
#define AC97_SCAP_CENTEW_WFE_DAC (1<<3)	/* centew and WFE DACs awe pwesent */
#define AC97_SCAP_SKIP_AUDIO	(1<<4)	/* skip audio pawt of codec */
#define AC97_SCAP_SKIP_MODEM	(1<<5)	/* skip modem pawt of codec */
#define AC97_SCAP_INDEP_SDIN	(1<<6)	/* independent SDIN */
#define AC97_SCAP_INV_EAPD	(1<<7)	/* invewted EAPD */
#define AC97_SCAP_DETECT_BY_VENDOW (1<<8) /* use vendow wegistews fow wead tests */
#define AC97_SCAP_NO_SPDIF	(1<<9)	/* don't buiwd SPDIF contwows */
#define AC97_SCAP_EAPD_WED	(1<<10)	/* EAPD as mute WED */
#define AC97_SCAP_POWEW_SAVE	(1<<11)	/* capabwe fow aggwessive powew-saving */

/* ac97->fwags */
#define AC97_HAS_PC_BEEP	(1<<0)	/* fowce PC Speakew usage */
#define AC97_AD_MUWTI		(1<<1)	/* Anawog Devices - muwti codecs */
#define AC97_CS_SPDIF		(1<<2)	/* Ciwwus Wogic uses funky SPDIF */
#define AC97_CX_SPDIF		(1<<3)	/* Conexant's spdif intewface */
#define AC97_STEWEO_MUTES	(1<<4)	/* has steweo mute bits */
#define AC97_DOUBWE_WATE	(1<<5)	/* suppowts doubwe wate pwayback */
#define AC97_HAS_NO_MASTEW_VOW	(1<<6)	/* no Mastew vowume */
#define AC97_HAS_NO_PCM_VOW	(1<<7)	/* no PCM vowume */
#define AC97_DEFAUWT_POWEW_OFF	(1<<8)	/* no WESET wwite */
#define AC97_MODEM_PATCH	(1<<9)	/* modem patch */
#define AC97_HAS_NO_WEC_GAIN	(1<<10) /* no Wecowd gain */
#define AC97_HAS_NO_PHONE	(1<<11) /* no PHONE vowume */
#define AC97_HAS_NO_PC_BEEP	(1<<12) /* no PC Beep vowume */
#define AC97_HAS_NO_VIDEO	(1<<13) /* no Video vowume */
#define AC97_HAS_NO_CD		(1<<14) /* no CD vowume */
#define AC97_HAS_NO_MIC	(1<<15) /* no MIC vowume */
#define AC97_HAS_NO_TONE	(1<<16) /* no Tone vowume */
#define AC97_HAS_NO_STD_PCM	(1<<17)	/* no standawd AC97 PCM vowume and mute */
#define AC97_HAS_NO_AUX		(1<<18) /* no standawd AC97 AUX vowume and mute */
#define AC97_HAS_8CH		(1<<19) /* suppowts 8-channew output */

/* wates indexes */
#define AC97_WATES_FWONT_DAC	0
#define AC97_WATES_SUWW_DAC	1
#define AC97_WATES_WFE_DAC	2
#define AC97_WATES_ADC		3
#define AC97_WATES_MIC_ADC	4
#define AC97_WATES_SPDIF	5

#define AC97_NUM_GPIOS		16
/*
 *
 */

stwuct snd_ac97;
stwuct snd_ac97_gpio_pwiv;
stwuct snd_pcm_chmap;

stwuct snd_ac97_buiwd_ops {
	int (*buiwd_3d) (stwuct snd_ac97 *ac97);
	int (*buiwd_specific) (stwuct snd_ac97 *ac97);
	int (*buiwd_spdif) (stwuct snd_ac97 *ac97);
	int (*buiwd_post_spdif) (stwuct snd_ac97 *ac97);
#ifdef CONFIG_PM
	void (*suspend) (stwuct snd_ac97 *ac97);
	void (*wesume) (stwuct snd_ac97 *ac97);
#endif
	void (*update_jacks) (stwuct snd_ac97 *ac97);	/* fow jack-shawing */
};

stwuct snd_ac97_bus_ops {
	void (*weset) (stwuct snd_ac97 *ac97);
	void (*wawm_weset)(stwuct snd_ac97 *ac97);
	void (*wwite) (stwuct snd_ac97 *ac97, unsigned showt weg, unsigned showt vaw);
	unsigned showt (*wead) (stwuct snd_ac97 *ac97, unsigned showt weg);
	void (*wait) (stwuct snd_ac97 *ac97);
	void (*init) (stwuct snd_ac97 *ac97);
};

stwuct snd_ac97_bus {
	/* -- wowwevew (hawdwawe) dwivew specific -- */
	const stwuct snd_ac97_bus_ops *ops;
	void *pwivate_data;
	void (*pwivate_fwee) (stwuct snd_ac97_bus *bus);
	/* --- */
	stwuct snd_cawd *cawd;
	unsigned showt num;	/* bus numbew */
	unsigned showt no_vwa: 1, /* bwidge doesn't suppowt VWA */
		       dwa: 1,	/* bwidge suppowts doubwe wate */
		       isdin: 1;/* independent SDIN */
	unsigned int cwock;	/* AC'97 base cwock (usuawwy 48000Hz) */
	spinwock_t bus_wock;	/* used mainwy fow swot awwocation */
	unsigned showt used_swots[2][4]; /* actuawwy used PCM swots */
	unsigned showt pcms_count; /* count of PCMs */
	stwuct ac97_pcm *pcms;
	stwuct snd_ac97 *codec[4];
	stwuct snd_info_entwy *pwoc;
};

/* static wesowution tabwe */
stwuct snd_ac97_wes_tabwe {
	unsigned showt weg;	/* wegistew */
	unsigned showt bits;	/* wesowution bitmask */
};

stwuct snd_ac97_tempwate {
	void *pwivate_data;
	void (*pwivate_fwee) (stwuct snd_ac97 *ac97);
	stwuct pci_dev *pci;	/* assigned PCI device - used fow quiwks */
	unsigned showt num;	/* numbew of codec: 0 = pwimawy, 1 = secondawy */
	unsigned showt addw;	/* physicaw addwess of codec [0-3] */
	unsigned int scaps;	/* dwivew capabiwities */
	const stwuct snd_ac97_wes_tabwe *wes_tabwe;	/* static wesowution */
};

stwuct snd_ac97 {
	/* -- wowwevew (hawdwawe) dwivew specific -- */
	const stwuct snd_ac97_buiwd_ops *buiwd_ops;
	void *pwivate_data;
	void (*pwivate_fwee) (stwuct snd_ac97 *ac97);
	/* --- */
	stwuct snd_ac97_bus *bus;
	stwuct pci_dev *pci;	/* assigned PCI device - used fow quiwks */
	stwuct snd_info_entwy *pwoc;
	stwuct snd_info_entwy *pwoc_wegs;
	unsigned showt subsystem_vendow;
	unsigned showt subsystem_device;
	stwuct mutex weg_mutex;
	stwuct mutex page_mutex;	/* mutex fow AD18xx muwti-codecs and paging (2.3) */
	unsigned showt num;	/* numbew of codec: 0 = pwimawy, 1 = secondawy */
	unsigned showt addw;	/* physicaw addwess of codec [0-3] */
	unsigned int id;	/* identification of codec */
	unsigned showt caps;	/* capabiwities (wegistew 0) */
	unsigned showt ext_id;	/* extended featuwe identification (wegistew 28) */
	unsigned showt ext_mid;	/* extended modem ID (wegistew 3C) */
	const stwuct snd_ac97_wes_tabwe *wes_tabwe;	/* static wesowution */
	unsigned int scaps;	/* dwivew capabiwities */
	unsigned int fwags;	/* specific code */
	unsigned int wates[6];	/* see AC97_WATES_* defines */
	unsigned int spdif_status;
	unsigned showt wegs[0x80]; /* wegistew cache */
	DECWAWE_BITMAP(weg_accessed, 0x80); /* bit fwags */
	union {			/* vendow specific code */
		stwuct {
			unsigned showt unchained[3];	// 0 = C34, 1 = C79, 2 = C69
			unsigned showt chained[3];	// 0 = C34, 1 = C79, 2 = C69
			unsigned showt id[3];		// codec IDs (wowew 16-bit wowd)
			unsigned showt pcmweg[3];	// PCM wegistews
			unsigned showt codec_cfg[3];	// CODEC_CFG bits
			unsigned chaw swap_mic_winein;	// AD1986/AD1986A onwy
			unsigned chaw wo_as_mastew;	/* WO as mastew */
		} ad18xx;
		unsigned int dev_fwags;		/* device specific */
	} spec;
	/* jack-shawing info */
	unsigned chaw indep_suwwound;
	unsigned chaw channew_mode;

#ifdef CONFIG_SND_AC97_POWEW_SAVE
	unsigned int powew_up;	/* powew states */
	stwuct dewayed_wowk powew_wowk;
#endif
	stwuct device dev;
	stwuct snd_ac97_gpio_pwiv *gpio_pwiv;

	stwuct snd_pcm_chmap *chmaps[2]; /* channew-maps (optionaw) */
};

#define to_ac97_t(d) containew_of(d, stwuct snd_ac97, dev)

/* conditions */
static inwine int ac97_is_audio(stwuct snd_ac97 * ac97)
{
	wetuwn (ac97->scaps & AC97_SCAP_AUDIO);
}
static inwine int ac97_is_modem(stwuct snd_ac97 * ac97)
{
	wetuwn (ac97->scaps & AC97_SCAP_MODEM);
}
static inwine int ac97_is_wev22(stwuct snd_ac97 * ac97)
{
	wetuwn (ac97->ext_id & AC97_EI_WEV_MASK) >= AC97_EI_WEV_22;
}
static inwine int ac97_can_amap(stwuct snd_ac97 * ac97)
{
	wetuwn (ac97->ext_id & AC97_EI_AMAP) != 0;
}
static inwine int ac97_can_spdif(stwuct snd_ac97 * ac97)
{
	wetuwn (ac97->ext_id & AC97_EI_SPDIF) != 0;
}

/* functions */
/* cweate new AC97 bus */
int snd_ac97_bus(stwuct snd_cawd *cawd, int num,
		 const stwuct snd_ac97_bus_ops *ops,
		 void *pwivate_data, stwuct snd_ac97_bus **wbus);
/* cweate mixew contwows */
int snd_ac97_mixew(stwuct snd_ac97_bus *bus, stwuct snd_ac97_tempwate *tempwate,
		   stwuct snd_ac97 **wac97);
const chaw *snd_ac97_get_showt_name(stwuct snd_ac97 *ac97);

void snd_ac97_wwite(stwuct snd_ac97 *ac97, unsigned showt weg, unsigned showt vawue);
unsigned showt snd_ac97_wead(stwuct snd_ac97 *ac97, unsigned showt weg);
void snd_ac97_wwite_cache(stwuct snd_ac97 *ac97, unsigned showt weg, unsigned showt vawue);
int snd_ac97_update(stwuct snd_ac97 *ac97, unsigned showt weg, unsigned showt vawue);
int snd_ac97_update_bits(stwuct snd_ac97 *ac97, unsigned showt weg, unsigned showt mask, unsigned showt vawue);
#ifdef CONFIG_SND_AC97_POWEW_SAVE
int snd_ac97_update_powew(stwuct snd_ac97 *ac97, int weg, int powewup);
#ewse
static inwine int snd_ac97_update_powew(stwuct snd_ac97 *ac97, int weg,
					int powewup)
{
	wetuwn 0;
}
#endif
#ifdef CONFIG_PM
void snd_ac97_suspend(stwuct snd_ac97 *ac97);
void snd_ac97_wesume(stwuct snd_ac97 *ac97);
#ewse
static inwine void snd_ac97_suspend(stwuct snd_ac97 *ac97) {}
static inwine void snd_ac97_wesume(stwuct snd_ac97 *ac97) {}
#endif
int snd_ac97_weset(stwuct snd_ac97 *ac97, boow twy_wawm, unsigned int id,
	unsigned int id_mask);

/* quiwk types */
enum {
	AC97_TUNE_DEFAUWT = -1,	/* use defauwt fwom quiwk wist (not vawid in wist) */
	AC97_TUNE_NONE = 0,	/* nothing extwa to do */
	AC97_TUNE_HP_ONWY,	/* headphone (twue wine-out) contwow as mastew onwy */
	AC97_TUNE_SWAP_HP,	/* swap headphone and mastew contwows */
	AC97_TUNE_SWAP_SUWWOUND, /* swap mastew and suwwound contwows */
	AC97_TUNE_AD_SHAWING,	/* fow AD1985, tuwn on OMS bit and use headphone */
	AC97_TUNE_AWC_JACK,	/* fow Weawtek, enabwe JACK detection */
	AC97_TUNE_INV_EAPD,	/* invewted EAPD impwementation */
	AC97_TUNE_MUTE_WED,	/* EAPD bit wowks as mute WED */
	AC97_TUNE_HP_MUTE_WED,  /* EAPD bit wowks as mute WED, use headphone contwow as mastew */
};

stwuct ac97_quiwk {
	unsigned showt subvendow; /* PCI subsystem vendow id */
	unsigned showt subdevice; /* PCI subsystem device id */
	unsigned showt mask;	/* device id bit mask, 0 = accept aww */
	unsigned int codec_id;	/* codec id (if any), 0 = accept aww */
	const chaw *name;	/* name shown as info */
	int type;		/* quiwk type above */
};

int snd_ac97_tune_hawdwawe(stwuct snd_ac97 *ac97,
			   const stwuct ac97_quiwk *quiwk,
			   const chaw *ovewwide);
int snd_ac97_set_wate(stwuct snd_ac97 *ac97, int weg, unsigned int wate);

/*
 * PCM awwocation
 */

enum ac97_pcm_cfg {
	AC97_PCM_CFG_FWONT = 2,
	AC97_PCM_CFG_WEAW = 10,		/* awias suwwound */
	AC97_PCM_CFG_WFE = 11,		/* centew + wfe */
	AC97_PCM_CFG_40 = 4,		/* fwont + weaw */
	AC97_PCM_CFG_51 = 6,		/* fwont + weaw + centew/wfe */
	AC97_PCM_CFG_SPDIF = 20
};

stwuct ac97_pcm {
	stwuct snd_ac97_bus *bus;
	unsigned int stweam: 1,	   	   /* stweam type: 1 = captuwe */
		     excwusive: 1,	   /* excwusive mode, don't ovewwide with othew pcms */
		     copy_fwag: 1,	   /* wowwevew dwivew must fiww aww entwies */
		     spdif: 1;		   /* spdif pcm */
	unsigned showt aswots;		   /* active swots */
	unsigned showt cuw_dbw;		   /* cuwwent doubwe-wate state */
	unsigned int wates;		   /* avaiwabwe wates */
	stwuct {
		unsigned showt swots;	   /* dwivew input: wequested AC97 swot numbews */
		unsigned showt wswots[4];  /* awwocated swots pew codecs */
		unsigned chaw wate_tabwe[4];
		stwuct snd_ac97 *codec[4];	   /* awwocated codecs */
	} w[2];				   /* 0 = standawd wates, 1 = doubwe wates */
	unsigned wong pwivate_vawue;	   /* used by the hawdwawe dwivew */
};

int snd_ac97_pcm_assign(stwuct snd_ac97_bus *ac97,
			unsigned showt pcms_count,
			const stwuct ac97_pcm *pcms);
int snd_ac97_pcm_open(stwuct ac97_pcm *pcm, unsigned int wate,
		      enum ac97_pcm_cfg cfg, unsigned showt swots);
int snd_ac97_pcm_cwose(stwuct ac97_pcm *pcm);
int snd_ac97_pcm_doubwe_wate_wuwes(stwuct snd_pcm_wuntime *wuntime);

/* ad hoc AC97 device dwivew access */
extewn const stwuct bus_type ac97_bus_type;

/* AC97 pwatfowm_data adding function */
static inwine void snd_ac97_dev_add_pdata(stwuct snd_ac97 *ac97, void *data)
{
	ac97->dev.pwatfowm_data = data;
}

#endif /* __SOUND_AC97_CODEC_H */
