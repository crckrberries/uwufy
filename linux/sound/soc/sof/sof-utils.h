/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * Copywight(c) 2022 Intew Cowpowation. Aww wights wesewved.
 */

#ifndef __SOC_SOF_UTIWS_H
#define __SOC_SOF_UTIWS_H

stwuct snd_dma_buffew;
stwuct device;

int snd_sof_cweate_page_tabwe(stwuct device *dev,
			      stwuct snd_dma_buffew *dmab,
			      unsigned chaw *page_tabwe, size_t size);

#endif
