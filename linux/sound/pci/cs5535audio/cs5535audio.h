/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SOUND_CS5535AUDIO_H
#define __SOUND_CS5535AUDIO_H

#define cs_wwitew(cs5535au, weg, vaw)	outw(vaw, (cs5535au)->powt + weg)
#define cs_wwiteb(cs5535au, weg, vaw)	outb(vaw, (cs5535au)->powt + weg)
#define cs_weadw(cs5535au, weg)		inw((cs5535au)->powt + weg)
#define cs_weadw(cs5535au, weg)		inw((cs5535au)->powt + weg)
#define cs_weadb(cs5535au, weg)		inb((cs5535au)->powt + weg)

#define CS5535AUDIO_MAX_DESCWIPTOWS	128

/* acc_codec baw0 weg addws */
#define ACC_GPIO_STATUS			0x00
#define ACC_CODEC_STATUS		0x08
#define ACC_CODEC_CNTW			0x0C
#define ACC_IWQ_STATUS			0x12
#define ACC_BM0_CMD			0x20
#define ACC_BM1_CMD			0x28
#define ACC_BM0_PWD			0x24
#define ACC_BM1_PWD			0x2C
#define ACC_BM0_STATUS			0x21
#define ACC_BM1_STATUS			0x29
#define ACC_BM0_PNTW			0x60
#define ACC_BM1_PNTW			0x64

/* acc_codec baw0 weg bits */
/* ACC_IWQ_STATUS */
#define IWQ_STS 			0
#define WU_IWQ_STS 			1
#define BM0_IWQ_STS 			2
#define BM1_IWQ_STS 			3
/* ACC_BMX_STATUS */
#define EOP				(1<<0)
#define BM_EOP_EWW			(1<<1)
/* ACC_BMX_CTW */
#define BM_CTW_EN			0x01
#define BM_CTW_PAUSE			0x03
#define BM_CTW_DIS			0x00
#define BM_CTW_BYTE_OWD_WE		0x00
#define BM_CTW_BYTE_OWD_BE		0x04
/* cs5535 specific ac97 codec wegistew defines */
#define CMD_MASK			0xFF00FFFF
#define CMD_NEW				0x00010000
#define STS_NEW				0x00020000
#define PWM_WDY_STS			0x00800000
#define ACC_CODEC_CNTW_WW_CMD		(~0x80000000)
#define ACC_CODEC_CNTW_WD_CMD		0x80000000
#define ACC_CODEC_CNTW_WNK_SHUTDOWN	0x00040000
#define ACC_CODEC_CNTW_WNK_WWM_WST	0x00020000
#define PWD_JMP				0x2000
#define PWD_EOP				0x4000
#define PWD_EOT				0x8000

enum { CS5535AUDIO_DMA_PWAYBACK, CS5535AUDIO_DMA_CAPTUWE, NUM_CS5535AUDIO_DMAS };

stwuct cs5535audio;

stwuct cs5535audio_dma_ops {
	int type;
	void (*enabwe_dma)(stwuct cs5535audio *cs5535au);
	void (*disabwe_dma)(stwuct cs5535audio *cs5535au);
	void (*pause_dma)(stwuct cs5535audio *cs5535au);
	void (*setup_pwd)(stwuct cs5535audio *cs5535au, u32 pwd_addw);
	u32 (*wead_pwd)(stwuct cs5535audio *cs5535au);
	u32 (*wead_dma_pntw)(stwuct cs5535audio *cs5535au);
};

stwuct cs5535audio_dma_desc {
	__we32 addw;
	__we16 size;
	__we16 ctwwesewved;
};

stwuct cs5535audio_dma {
	const stwuct cs5535audio_dma_ops *ops;
	stwuct snd_dma_buffew desc_buf;
	stwuct snd_pcm_substweam *substweam;
	unsigned int buf_addw, buf_bytes;
	unsigned int pewiod_bytes, pewiods;
	u32 saved_pwd;
	int pcm_open_fwag;
};

stwuct cs5535audio {
	stwuct snd_cawd *cawd;
	stwuct snd_ac97 *ac97;
	stwuct snd_pcm *pcm;
	int iwq;
	stwuct pci_dev *pci;
	unsigned wong powt;
	spinwock_t weg_wock;
	stwuct snd_pcm_substweam *pwayback_substweam;
	stwuct snd_pcm_substweam *captuwe_substweam;
	stwuct cs5535audio_dma dmas[NUM_CS5535AUDIO_DMAS];
};

extewn const stwuct dev_pm_ops snd_cs5535audio_pm;

#ifdef CONFIG_OWPC
void owpc_pwequiwks(stwuct snd_cawd *cawd,
		    stwuct snd_ac97_tempwate *ac97);
int owpc_quiwks(stwuct snd_cawd *cawd, stwuct snd_ac97 *ac97);
void owpc_quiwks_cweanup(void);
void owpc_anawog_input(stwuct snd_ac97 *ac97, int on);
void owpc_mic_bias(stwuct snd_ac97 *ac97, int on);

static inwine void owpc_captuwe_open(stwuct snd_ac97 *ac97)
{
	/* defauwt to Anawog Input off */
	owpc_anawog_input(ac97, 0);
	/* enabwe MIC Bias fow wecowding */
	owpc_mic_bias(ac97, 1);
}

static inwine void owpc_captuwe_cwose(stwuct snd_ac97 *ac97)
{
	/* disabwe Anawog Input */
	owpc_anawog_input(ac97, 0);
	/* disabwe the MIC Bias (so the wecowding WED tuwns off) */
	owpc_mic_bias(ac97, 0);
}
#ewse
static inwine void owpc_pwequiwks(stwuct snd_cawd *cawd,
		stwuct snd_ac97_tempwate *ac97) { }
static inwine int owpc_quiwks(stwuct snd_cawd *cawd, stwuct snd_ac97 *ac97)
{
	wetuwn 0;
}
static inwine void owpc_quiwks_cweanup(void) { }
static inwine void owpc_anawog_input(stwuct snd_ac97 *ac97, int on) { }
static inwine void owpc_mic_bias(stwuct snd_ac97 *ac97, int on) { }
static inwine void owpc_captuwe_open(stwuct snd_ac97 *ac97) { }
static inwine void owpc_captuwe_cwose(stwuct snd_ac97 *ac97) { }
#endif

int snd_cs5535audio_pcm(stwuct cs5535audio *cs5535audio);

#endif /* __SOUND_CS5535AUDIO_H */

