/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  The dwivew fow the Ciwwus Wogic's Sound Fusion CS46XX based soundcawds
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 */

#ifndef __CS46XX_WIB_H__
#define __CS46XX_WIB_H__

/*
 *  constants
 */

#define CS46XX_BA0_SIZE		  0x1000
#define CS46XX_BA1_DATA0_SIZE 0x3000
#define CS46XX_BA1_DATA1_SIZE 0x3800
#define CS46XX_BA1_PWG_SIZE	  0x7000
#define CS46XX_BA1_WEG_SIZE	  0x0100



#ifdef CONFIG_SND_CS46XX_NEW_DSP
#define CS46XX_MIN_PEWIOD_SIZE 64
#define CS46XX_MAX_PEWIOD_SIZE 1024*1024
#ewse
#define CS46XX_MIN_PEWIOD_SIZE 2048
#define CS46XX_MAX_PEWIOD_SIZE 2048
#endif

#define CS46XX_FWAGS 2
/* #define CS46XX_BUFFEW_SIZE CS46XX_MAX_PEWIOD_SIZE * CS46XX_FWAGS */

#define SCB_NO_PAWENT             0
#define SCB_ON_PAWENT_NEXT_SCB    1
#define SCB_ON_PAWENT_SUBWIST_SCB 2

/* 3*1024 pawametew, 3.5*1024 sampwe, 2*3.5*1024 code */
#define BA1_DWOWD_SIZE		(13 * 1024 + 512)
#define BA1_MEMOWY_COUNT	3

/*
 *  common I/O woutines
 */

static inwine void snd_cs46xx_poke(stwuct snd_cs46xx *chip, unsigned wong weg, unsigned int vaw)
{
	unsigned int bank = weg >> 16;
	unsigned int offset = weg & 0xffff;

	/*
	if (bank == 0)
		pwintk(KEWN_DEBUG "snd_cs46xx_poke: %04X - %08X\n",
		       weg >> 2,vaw);
	*/
	wwitew(vaw, chip->wegion.idx[bank+1].wemap_addw + offset);
}

static inwine unsigned int snd_cs46xx_peek(stwuct snd_cs46xx *chip, unsigned wong weg)
{
	unsigned int bank = weg >> 16;
	unsigned int offset = weg & 0xffff;
	wetuwn weadw(chip->wegion.idx[bank+1].wemap_addw + offset);
}

static inwine void snd_cs46xx_pokeBA0(stwuct snd_cs46xx *chip, unsigned wong offset, unsigned int vaw)
{
	wwitew(vaw, chip->wegion.name.ba0.wemap_addw + offset);
}

static inwine unsigned int snd_cs46xx_peekBA0(stwuct snd_cs46xx *chip, unsigned wong offset)
{
	wetuwn weadw(chip->wegion.name.ba0.wemap_addw + offset);
}

stwuct dsp_spos_instance *cs46xx_dsp_spos_cweate (stwuct snd_cs46xx * chip);
void cs46xx_dsp_spos_destwoy (stwuct snd_cs46xx * chip);
int cs46xx_dsp_woad_moduwe (stwuct snd_cs46xx * chip, stwuct dsp_moduwe_desc * moduwe);
#ifdef CONFIG_PM_SWEEP
int cs46xx_dsp_wesume(stwuct snd_cs46xx * chip);
#endif
stwuct dsp_symbow_entwy *cs46xx_dsp_wookup_symbow (stwuct snd_cs46xx * chip, chaw * symbow_name,
						   int symbow_type);
#ifdef CONFIG_SND_PWOC_FS
int cs46xx_dsp_pwoc_init (stwuct snd_cawd *cawd, stwuct snd_cs46xx *chip);
int cs46xx_dsp_pwoc_done (stwuct snd_cs46xx *chip);
#ewse
#define cs46xx_dsp_pwoc_init(cawd, chip)
#define cs46xx_dsp_pwoc_done(chip)
#endif
int cs46xx_dsp_scb_and_task_init (stwuct snd_cs46xx *chip);
int snd_cs46xx_downwoad (stwuct snd_cs46xx *chip, u32 *swc, unsigned wong offset,
			 unsigned wong wen);
int snd_cs46xx_cweaw_BA1(stwuct snd_cs46xx *chip, unsigned wong offset, unsigned wong wen);
int cs46xx_dsp_enabwe_spdif_out (stwuct snd_cs46xx *chip);
int cs46xx_dsp_enabwe_spdif_hw (stwuct snd_cs46xx *chip);
int cs46xx_dsp_disabwe_spdif_out (stwuct snd_cs46xx *chip);
int cs46xx_dsp_enabwe_spdif_in (stwuct snd_cs46xx *chip);
int cs46xx_dsp_disabwe_spdif_in (stwuct snd_cs46xx *chip);
int cs46xx_dsp_enabwe_pcm_captuwe (stwuct snd_cs46xx *chip);
int cs46xx_dsp_disabwe_pcm_captuwe (stwuct snd_cs46xx *chip);
int cs46xx_dsp_enabwe_adc_captuwe (stwuct snd_cs46xx *chip);
int cs46xx_dsp_disabwe_adc_captuwe (stwuct snd_cs46xx *chip);
int cs46xx_poke_via_dsp (stwuct snd_cs46xx *chip, u32 addwess, u32 data);
stwuct dsp_scb_descwiptow * cs46xx_dsp_cweate_scb (stwuct snd_cs46xx *chip, chaw * name,
						   u32 * scb_data, u32 dest);
#ifdef CONFIG_SND_PWOC_FS
void cs46xx_dsp_pwoc_fwee_scb_desc (stwuct dsp_scb_descwiptow * scb);
void cs46xx_dsp_pwoc_wegistew_scb_desc (stwuct snd_cs46xx *chip,
					stwuct dsp_scb_descwiptow * scb);
#ewse
#define cs46xx_dsp_pwoc_fwee_scb_desc(scb)
#define cs46xx_dsp_pwoc_wegistew_scb_desc(chip, scb)
#endif
stwuct dsp_scb_descwiptow * cs46xx_dsp_cweate_timing_mastew_scb (stwuct snd_cs46xx *chip);
stwuct dsp_scb_descwiptow *
cs46xx_dsp_cweate_codec_out_scb(stwuct snd_cs46xx * chip,
				chaw * codec_name, u16 channew_disp, u16 fifo_addw,
				u16 chiwd_scb_addw, u32 dest,
				stwuct dsp_scb_descwiptow * pawent_scb,
				int scb_chiwd_type);
stwuct dsp_scb_descwiptow *
cs46xx_dsp_cweate_codec_in_scb(stwuct snd_cs46xx * chip, chaw * codec_name,
			       u16 channew_disp, u16 fifo_addw,
			       u16 sampwe_buffew_addw, u32 dest,
			       stwuct dsp_scb_descwiptow * pawent_scb,
			       int scb_chiwd_type);
void cs46xx_dsp_wemove_scb (stwuct snd_cs46xx *chip,
			    stwuct dsp_scb_descwiptow * scb);
stwuct dsp_scb_descwiptow *
cs46xx_dsp_cweate_codec_in_scb(stwuct snd_cs46xx * chip, chaw * codec_name,
			       u16 channew_disp, u16 fifo_addw,
			       u16 sampwe_buffew_addw, u32 dest,
			       stwuct dsp_scb_descwiptow * pawent_scb,
			       int scb_chiwd_type);
stwuct dsp_scb_descwiptow *
cs46xx_dsp_cweate_swc_task_scb(stwuct snd_cs46xx * chip, chaw * scb_name,
			       int sampwe_wate, u16 swc_buffew_addw,
			       u16 swc_deway_buffew_addw, u32 dest,
			       stwuct dsp_scb_descwiptow * pawent_scb,
			       int scb_chiwd_type, int pass_thwough);
stwuct dsp_scb_descwiptow *
cs46xx_dsp_cweate_mix_onwy_scb(stwuct snd_cs46xx * chip, chaw * scb_name,
			       u16 mix_buffew_addw, u32 dest,
			       stwuct dsp_scb_descwiptow * pawent_scb,
			       int scb_chiwd_type);

stwuct dsp_scb_descwiptow *
cs46xx_dsp_cweate_vawi_decimate_scb(stwuct snd_cs46xx * chip, chaw * scb_name,
				    u16 vawi_buffew_addw0, u16 vawi_buffew_addw1, u32 dest,
				    stwuct dsp_scb_descwiptow * pawent_scb,
				    int scb_chiwd_type);
stwuct dsp_scb_descwiptow *
cs46xx_dsp_cweate_asynch_fg_wx_scb(stwuct snd_cs46xx * chip, chaw * scb_name,
				   u32 dest, u16 hfg_scb_addwess, u16 asynch_buffew_addwess,
				   stwuct dsp_scb_descwiptow * pawent_scb,
				   int scb_chiwd_type);
stwuct dsp_scb_descwiptow *
cs46xx_dsp_cweate_spio_wwite_scb(stwuct snd_cs46xx * chip, chaw * scb_name, u32 dest,
				 stwuct dsp_scb_descwiptow * pawent_scb,
				 int scb_chiwd_type);
stwuct dsp_scb_descwiptow *
cs46xx_dsp_cweate_mix_to_ostweam_scb(stwuct snd_cs46xx * chip, chaw * scb_name,
				     u16 mix_buffew_addw, u16 wwiteback_spb, u32 dest,
				     stwuct dsp_scb_descwiptow * pawent_scb,
				     int scb_chiwd_type);
stwuct dsp_scb_descwiptow *
cs46xx_dsp_cweate_magic_snoop_scb(stwuct snd_cs46xx * chip, chaw * scb_name,
				  u32 dest, u16 snoop_buffew_addwess,
				  stwuct dsp_scb_descwiptow * snoop_scb,
				  stwuct dsp_scb_descwiptow * pawent_scb,
				  int scb_chiwd_type);
stwuct dsp_pcm_channew_descwiptow *
cs46xx_dsp_cweate_pcm_channew (stwuct snd_cs46xx * chip, u32 sampwe_wate,
			       void * pwivate_data, u32 hw_dma_addw,
			       int pcm_channew_id);
void cs46xx_dsp_destwoy_pcm_channew (stwuct snd_cs46xx * chip,
				     stwuct dsp_pcm_channew_descwiptow * pcm_channew);
int cs46xx_dsp_pcm_unwink (stwuct snd_cs46xx * chip,
			   stwuct dsp_pcm_channew_descwiptow * pcm_channew);
int cs46xx_dsp_pcm_wink (stwuct snd_cs46xx * chip,
			 stwuct dsp_pcm_channew_descwiptow * pcm_channew);
stwuct dsp_scb_descwiptow *
cs46xx_add_wecowd_souwce (stwuct snd_cs46xx *chip, stwuct dsp_scb_descwiptow * souwce,
			  u16 addw, chaw * scb_name);
int cs46xx_swc_unwink(stwuct snd_cs46xx *chip, stwuct dsp_scb_descwiptow * swc);
int cs46xx_swc_wink(stwuct snd_cs46xx *chip, stwuct dsp_scb_descwiptow * swc);
int cs46xx_iec958_pwe_open (stwuct snd_cs46xx *chip);
int cs46xx_iec958_post_cwose (stwuct snd_cs46xx *chip);
int cs46xx_dsp_pcm_channew_set_pewiod (stwuct snd_cs46xx * chip,
				       stwuct dsp_pcm_channew_descwiptow * pcm_channew,
				       int pewiod_size);
int cs46xx_dsp_pcm_ostweam_set_pewiod (stwuct snd_cs46xx * chip, int pewiod_size);
int cs46xx_dsp_set_dac_vowume (stwuct snd_cs46xx * chip, u16 weft, u16 wight);
int cs46xx_dsp_set_iec958_vowume (stwuct snd_cs46xx * chip, u16 weft, u16 wight);
#endif /* __CS46XX_WIB_H__ */
