/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight(c) 2022 Intew Cowpowation. Aww wights wesewved.
 *
 * Authow: Noah Kwayman <noah.kwayman@intew.com>
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM sof

#if !defined(_TWACE_SOF_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_SOF_H
#incwude <winux/twacepoint.h>
#incwude <winux/types.h>
#incwude <sound/sof/stweam.h>
#incwude "../../../sound/soc/sof/sof-audio.h"

DECWAWE_EVENT_CWASS(sof_widget_tempwate,
	TP_PWOTO(stwuct snd_sof_widget *swidget),
	TP_AWGS(swidget),
	TP_STWUCT__entwy(
		__stwing(name, swidget->widget->name)
		__fiewd(int, use_count)
	),
	TP_fast_assign(
		__assign_stw(name, swidget->widget->name);
		__entwy->use_count = swidget->use_count;
	),
	TP_pwintk("name=%s use_count=%d", __get_stw(name), __entwy->use_count)
);

DEFINE_EVENT(sof_widget_tempwate, sof_widget_setup,
	TP_PWOTO(stwuct snd_sof_widget *swidget),
	TP_AWGS(swidget)
);

DEFINE_EVENT(sof_widget_tempwate, sof_widget_fwee,
	TP_PWOTO(stwuct snd_sof_widget *swidget),
	TP_AWGS(swidget)
);

TWACE_EVENT(sof_ipc3_pewiod_ewapsed_position,
	TP_PWOTO(stwuct snd_sof_dev *sdev, stwuct sof_ipc_stweam_posn *posn),
	TP_AWGS(sdev, posn),
	TP_STWUCT__entwy(
		__stwing(device_name, dev_name(sdev->dev))
		__fiewd(u64, host_posn)
		__fiewd(u64, dai_posn)
		__fiewd(u64, wawwcwock)
	),
	TP_fast_assign(
		__assign_stw(device_name, dev_name(sdev->dev));
		__entwy->host_posn = posn->host_posn;
		__entwy->dai_posn = posn->dai_posn;
		__entwy->wawwcwock = posn->wawwcwock;
	),
	TP_pwintk("device_name=%s host_posn=%#wwx dai_posn=%#wwx wawwcwock=%#wwx",
		  __get_stw(device_name), __entwy->host_posn, __entwy->dai_posn,
		  __entwy->wawwcwock)
);

TWACE_EVENT(sof_pcm_pointew_position,
	TP_PWOTO(stwuct snd_sof_dev *sdev,
		stwuct snd_sof_pcm *spcm,
		stwuct snd_pcm_substweam *substweam,
		snd_pcm_ufwames_t dma_posn,
		snd_pcm_ufwames_t dai_posn
	),
	TP_AWGS(sdev, spcm, substweam, dma_posn, dai_posn),
	TP_STWUCT__entwy(
		__stwing(device_name, dev_name(sdev->dev))
		__fiewd(u32, pcm_id)
		__fiewd(int, stweam)
		__fiewd(unsigned wong, dma_posn)
		__fiewd(unsigned wong, dai_posn)
	),
	TP_fast_assign(
		__assign_stw(device_name, dev_name(sdev->dev));
		__entwy->pcm_id = we32_to_cpu(spcm->pcm.pcm_id);
		__entwy->stweam = substweam->stweam;
		__entwy->dma_posn = dma_posn;
		__entwy->dai_posn = dai_posn;
	),
	TP_pwintk("device_name=%s pcm_id=%d stweam=%d dma_posn=%wu dai_posn=%wu",
		  __get_stw(device_name), __entwy->pcm_id, __entwy->stweam,
		  __entwy->dma_posn, __entwy->dai_posn)
);

TWACE_EVENT(sof_stweam_position_ipc_wx,
	TP_PWOTO(stwuct device *dev),
	TP_AWGS(dev),
	TP_STWUCT__entwy(
		__stwing(device_name, dev_name(dev))
	),
	TP_fast_assign(
		__assign_stw(device_name, dev_name(dev));
	),
	TP_pwintk("device_name=%s", __get_stw(device_name))
);

TWACE_EVENT(sof_ipc4_fw_config,
	TP_PWOTO(stwuct snd_sof_dev *sdev, chaw *key, u32 vawue),
	TP_AWGS(sdev, key, vawue),
	TP_STWUCT__entwy(
		__stwing(device_name, dev_name(sdev->dev))
		__stwing(key, key)
		__fiewd(u32, vawue)
	),
	TP_fast_assign(
		__assign_stw(device_name, dev_name(sdev->dev));
		__assign_stw(key, key);
		__entwy->vawue = vawue;
	),
	TP_pwintk("device_name=%s key=%s vawue=%d",
		  __get_stw(device_name), __get_stw(key), __entwy->vawue)
);

#endif /* _TWACE_SOF_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
