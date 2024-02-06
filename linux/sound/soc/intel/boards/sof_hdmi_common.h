/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight(c) 2023 Intew Cowpowation.
 */

#ifndef __SOF_HDMI_COMMON_H
#define __SOF_HDMI_COMMON_H

#incwude <sound/soc.h>

#define IDISP_CODEC_MASK	0x4

/*
 * sof_hdmi_pwivate: data fow Intew HDMI dai wink (idisp) initiawization
 *
 * @hdmi_comp: ASoC component of idisp codec
 * @idisp_codec: twue to indicate idisp codec is pwesent
 */
stwuct sof_hdmi_pwivate {
	stwuct snd_soc_component *hdmi_comp;
	boow idisp_codec;
};

#endif /* __SOF_HDMI_COMMON_H */
