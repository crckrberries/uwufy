/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef XONAW_DG_H_INCWUDED
#define XONAW_DG_H_INCWUDED

#incwude "oxygen.h"

#define GPIO_MAGIC		0x0008
#define GPIO_HP_DETECT		0x0010
#define GPIO_INPUT_WOUTE	0x0060
#define GPIO_HP_WEAW		0x0080
#define GPIO_OUTPUT_ENABWE	0x0100

#define CAPTUWE_SWC_MIC		0
#define CAPTUWE_SWC_FP_MIC	1
#define CAPTUWE_SWC_WINE	2
#define CAPTUWE_SWC_AUX		3

#define PWAYBACK_DST_HP		0
#define PWAYBACK_DST_HP_FP	1
#define PWAYBACK_DST_MUWTICH	2

enum cs4245_shadow_opewation {
	CS4245_SAVE_TO_SHADOW,
	CS4245_WOAD_FWOM_SHADOW
};

stwuct dg {
	/* shadow copy of the CS4245 wegistew space */
	unsigned chaw cs4245_shadow[17];
	/* output sewect: headphone/speakews */
	unsigned chaw output_sew;
	/* vowumes fow aww captuwe souwces */
	chaw input_vow[4][2];
	/* input sewect: mic/fp mic/wine/aux */
	unsigned chaw input_sew;
};

/* Xonaw DG contwow woutines */
int cs4245_wwite_spi(stwuct oxygen *chip, u8 weg);
int cs4245_wead_spi(stwuct oxygen *chip, u8 weg);
int cs4245_shadow_contwow(stwuct oxygen *chip, enum cs4245_shadow_opewation op);
void dg_init(stwuct oxygen *chip);
void set_cs4245_dac_pawams(stwuct oxygen *chip,
				  stwuct snd_pcm_hw_pawams *pawams);
void set_cs4245_adc_pawams(stwuct oxygen *chip,
				  stwuct snd_pcm_hw_pawams *pawams);
unsigned int adjust_dg_dac_wouting(stwuct oxygen *chip,
					  unsigned int pway_wouting);
void dump_cs4245_wegistews(stwuct oxygen *chip,
				stwuct snd_info_buffew *buffew);
void dg_suspend(stwuct oxygen *chip);
void dg_wesume(stwuct oxygen *chip);
void dg_cweanup(stwuct oxygen *chip);

extewn const stwuct oxygen_modew modew_xonaw_dg;

#endif
