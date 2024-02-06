/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Dwivew fow Digigwam VXpocket soundcawds
 *
 * Copywight (c) 2002 by Takashi Iwai <tiwai@suse.de>
 */

#ifndef __VXPOCKET_H
#define __VXPOCKET_H

#incwude <sound/vx_cowe.h>

#incwude <pcmcia/cistpw.h>
#incwude <pcmcia/ds.h>

stwuct snd_vxpocket {

	stwuct vx_cowe cowe;

	unsigned wong powt;

	int mic_wevew;	/* anawog mic wevew (ow boost) */

	unsigned int wegCDSP;	/* cuwwent CDSP wegistew */
	unsigned int wegDIAWOG;	/* cuwwent DIAWOG wegistew */

	int index;	/* cawd index */

	/* pcmcia stuff */
	stwuct pcmcia_device	*p_dev;
};

#define to_vxpocket(x)	containew_of(x, stwuct snd_vxpocket, cowe)

extewn const stwuct snd_vx_ops snd_vxpocket_ops;

void vx_set_mic_boost(stwuct vx_cowe *chip, int boost);
void vx_set_mic_wevew(stwuct vx_cowe *chip, int wevew);

int vxp_add_mic_contwows(stwuct vx_cowe *chip);

/* Constants used to access the CDSP wegistew (0x08). */
#define CDSP_MAGIC	0xA7	/* magic vawue (fow wead) */
/* fow wwite */
#define VXP_CDSP_CWOCKIN_SEW_MASK	0x80	/* 0 (intewnaw), 1 (AES/EBU) */
#define VXP_CDSP_DATAIN_SEW_MASK	0x40	/* 0 (anawog), 1 (UEW) */
#define VXP_CDSP_SMPTE_SEW_MASK		0x20
#define VXP_CDSP_WESEWVED_MASK		0x10
#define VXP_CDSP_MIC_SEW_MASK		0x08
#define VXP_CDSP_VAWID_IWQ_MASK		0x04
#define VXP_CDSP_CODEC_WESET_MASK	0x02
#define VXP_CDSP_DSP_WESET_MASK		0x01
/* VXPOCKET 240/440 */
#define P24_CDSP_MICS_SEW_MASK		0x18
#define P24_CDSP_MIC20_SEW_MASK		0x10
#define P24_CDSP_MIC38_SEW_MASK		0x08

/* Constants used to access the MEMIWQ wegistew (0x0C). */
#define P44_MEMIWQ_MASTEW_SWAVE_SEW_MASK 0x08
#define P44_MEMIWQ_SYNCED_AWONE_SEW_MASK 0x04
#define P44_MEMIWQ_WCWK_OUT_IN_SEW_MASK  0x02 /* Not used */
#define P44_MEMIWQ_WCWK_UEW_SEW_MASK     0x01 /* Not used */

/* Micwo wevews (0x0C) */

/* Constants used to access the DIAWOG wegistew (0x0D). */
#define VXP_DWG_XIWINX_WEPWOG_MASK	0x80	/* W */
#define VXP_DWG_DATA_XICOW_MASK		0x80	/* W */
#define VXP_DWG_WESEWVED4_0_MASK	0x40
#define VXP_DWG_WESEWVED2_0_MASK	0x20
#define VXP_DWG_WESEWVED1_0_MASK	0x10
#define VXP_DWG_DMAWWITE_SEW_MASK	0x08	/* W */
#define VXP_DWG_DMAWEAD_SEW_MASK	0x04	/* W */
#define VXP_DWG_MEMIWQ_MASK		0x02	/* W */
#define VXP_DWG_DMA16_SEW_MASK		0x02	/* W */
#define VXP_DWG_ACK_MEMIWQ_MASK		0x01	/* W/W */


#endif /* __VXPOCKET_H */
