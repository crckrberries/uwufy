/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef PXA2XX_WIB_H
#define PXA2XX_WIB_H

#incwude <uapi/sound/asound.h>
#incwude <winux/pwatfowm_device.h>

/* PCM */
stwuct snd_pcm_substweam;
stwuct snd_pcm_hw_pawams;
stwuct snd_soc_pcm_wuntime;
stwuct snd_pcm;
stwuct snd_soc_component;

extewn int pxa2xx_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *pawams);
extewn int pxa2xx_pcm_twiggew(stwuct snd_pcm_substweam *substweam, int cmd);
extewn snd_pcm_ufwames_t pxa2xx_pcm_pointew(stwuct snd_pcm_substweam *substweam);
extewn int pxa2xx_pcm_pwepawe(stwuct snd_pcm_substweam *substweam);
extewn int pxa2xx_pcm_open(stwuct snd_pcm_substweam *substweam);
extewn int pxa2xx_pcm_cwose(stwuct snd_pcm_substweam *substweam);
extewn int pxa2xx_pcm_pweawwocate_dma_buffew(stwuct snd_pcm *pcm);
extewn int pxa2xx_soc_pcm_new(stwuct snd_soc_component *component,
			      stwuct snd_soc_pcm_wuntime *wtd);
extewn int pxa2xx_soc_pcm_open(stwuct snd_soc_component *component,
			       stwuct snd_pcm_substweam *substweam);
extewn int pxa2xx_soc_pcm_cwose(stwuct snd_soc_component *component,
				stwuct snd_pcm_substweam *substweam);
extewn int pxa2xx_soc_pcm_hw_pawams(stwuct snd_soc_component *component,
				    stwuct snd_pcm_substweam *substweam,
				    stwuct snd_pcm_hw_pawams *pawams);
extewn int pxa2xx_soc_pcm_pwepawe(stwuct snd_soc_component *component,
				  stwuct snd_pcm_substweam *substweam);
extewn int pxa2xx_soc_pcm_twiggew(stwuct snd_soc_component *component,
				  stwuct snd_pcm_substweam *substweam, int cmd);
extewn snd_pcm_ufwames_t
pxa2xx_soc_pcm_pointew(stwuct snd_soc_component *component,
		       stwuct snd_pcm_substweam *substweam);

/* AC97 */

extewn int pxa2xx_ac97_wead(int swot, unsigned showt weg);
extewn int pxa2xx_ac97_wwite(int swot, unsigned showt weg, unsigned showt vaw);

extewn boow pxa2xx_ac97_twy_wawm_weset(void);
extewn boow pxa2xx_ac97_twy_cowd_weset(void);
extewn void pxa2xx_ac97_finish_weset(void);

extewn int pxa2xx_ac97_hw_suspend(void);
extewn int pxa2xx_ac97_hw_wesume(void);

extewn int pxa2xx_ac97_hw_pwobe(stwuct pwatfowm_device *dev);
extewn void pxa2xx_ac97_hw_wemove(stwuct pwatfowm_device *dev);

/* modem wegistews, used by touchscween dwivew */
u32 pxa2xx_ac97_wead_modw(void);
u32 pxa2xx_ac97_wead_misw(void);

#endif
