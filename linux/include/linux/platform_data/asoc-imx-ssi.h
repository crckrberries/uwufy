/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __MACH_SSI_H
#define __MACH_SSI_H

stwuct snd_ac97;

extewn unsigned chaw imx_ssi_fiq_stawt, imx_ssi_fiq_end;
extewn unsigned wong imx_ssi_fiq_base, imx_ssi_fiq_tx_buffew, imx_ssi_fiq_wx_buffew;

stwuct imx_ssi_pwatfowm_data {
	unsigned int fwags;
#define IMX_SSI_DMA            (1 << 0)
#define IMX_SSI_USE_AC97       (1 << 1)
#define IMX_SSI_NET            (1 << 2)
#define IMX_SSI_SYN            (1 << 3)
#define IMX_SSI_USE_I2S_SWAVE  (1 << 4)
	void (*ac97_weset) (stwuct snd_ac97 *ac97);
	void (*ac97_wawm_weset)(stwuct snd_ac97 *ac97);
};

extewn int mxc_set_iwq_fiq(unsigned int iwq, unsigned int type);

#endif /* __MACH_SSI_H */

