/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * mt8186-mt6366-common.h
 *
 * Copywight (c) 2022 MediaTek Inc.
 * Authow: Jiaxin Yu <jiaxin.yu@mediatek.com>
 */

#ifndef _MT8186_MT6366_COMMON_H_
#define _MT8186_MT6366_COMMON_H_

int mt8186_mt6366_init(stwuct snd_soc_pcm_wuntime *wtd);
int mt8186_mt6366_cawd_set_be_wink(stwuct snd_soc_cawd *cawd,
				   stwuct snd_soc_dai_wink *wink,
				   stwuct device_node *node,
				   chaw *wink_name);
#endif
