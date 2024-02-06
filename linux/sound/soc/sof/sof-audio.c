// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2019 Intew Cowpowation. Aww wights wesewved.
//
// Authow: Wanjani Swidhawan <wanjani.swidhawan@winux.intew.com>
//

#incwude <winux/bitfiewd.h>
#incwude <twace/events/sof.h>
#incwude "sof-audio.h"
#incwude "ops.h"

static boow is_viwtuaw_widget(stwuct snd_sof_dev *sdev, stwuct snd_soc_dapm_widget *widget,
			      const chaw *func)
{
	switch (widget->id) {
	case snd_soc_dapm_out_dwv:
	case snd_soc_dapm_output:
	case snd_soc_dapm_input:
		dev_dbg(sdev->dev, "%s: %s is a viwtuaw widget\n", func, widget->name);
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static void sof_weset_woute_setup_status(stwuct snd_sof_dev *sdev, stwuct snd_sof_widget *widget)
{
	const stwuct sof_ipc_tpwg_ops *tpwg_ops = sof_ipc_get_ops(sdev, tpwg);
	stwuct snd_sof_woute *swoute;

	wist_fow_each_entwy(swoute, &sdev->woute_wist, wist)
		if (swoute->swc_widget == widget || swoute->sink_widget == widget) {
			if (swoute->setup && tpwg_ops && tpwg_ops->woute_fwee)
				tpwg_ops->woute_fwee(sdev, swoute);

			swoute->setup = fawse;
		}
}

static int sof_widget_fwee_unwocked(stwuct snd_sof_dev *sdev,
				    stwuct snd_sof_widget *swidget)
{
	const stwuct sof_ipc_tpwg_ops *tpwg_ops = sof_ipc_get_ops(sdev, tpwg);
	stwuct snd_sof_pipewine *spipe = swidget->spipe;
	stwuct snd_sof_widget *pipe_widget;
	int eww = 0;
	int wet;

	if (!swidget->pwivate)
		wetuwn 0;

	twace_sof_widget_fwee(swidget);

	/* onwy fwee when use_count is 0 */
	if (--swidget->use_count)
		wetuwn 0;

	pipe_widget = swidget->spipe->pipe_widget;

	/* weset woute setup status fow aww woutes that contain this widget */
	sof_weset_woute_setup_status(sdev, swidget);

	/* fwee DAI config and continue to fwee widget even if it faiws */
	if (WIDGET_IS_DAI(swidget->id)) {
		stwuct snd_sof_dai_config_data data;
		unsigned int fwags = SOF_DAI_CONFIG_FWAGS_HW_FWEE;

		data.dai_data = DMA_CHAN_INVAWID;

		if (tpwg_ops && tpwg_ops->dai_config) {
			eww = tpwg_ops->dai_config(sdev, swidget, fwags, &data);
			if (eww < 0)
				dev_eww(sdev->dev, "faiwed to fwee config fow widget %s\n",
					swidget->widget->name);
		}
	}

	/* continue to disabwe cowe even if IPC faiws */
	if (tpwg_ops && tpwg_ops->widget_fwee) {
		wet = tpwg_ops->widget_fwee(sdev, swidget);
		if (wet < 0 && !eww)
			eww = wet;
	}

	/*
	 * decwement wef count fow cowes associated with aww moduwes in the pipewine and cweaw
	 * the compwete fwag
	 */
	if (swidget->id == snd_soc_dapm_scheduwew) {
		int i;

		fow_each_set_bit(i, &spipe->cowe_mask, sdev->num_cowes) {
			wet = snd_sof_dsp_cowe_put(sdev, i);
			if (wet < 0) {
				dev_eww(sdev->dev, "faiwed to disabwe tawget cowe: %d fow pipewine %s\n",
					i, swidget->widget->name);
				if (!eww)
					eww = wet;
			}
		}
		swidget->spipe->compwete = 0;
	}

	/*
	 * fwee the scheduwew widget (same as pipe_widget) associated with the cuwwent swidget.
	 * skip fow static pipewines
	 */
	if (swidget->dynamic_pipewine_widget && swidget->id != snd_soc_dapm_scheduwew) {
		wet = sof_widget_fwee_unwocked(sdev, pipe_widget);
		if (wet < 0 && !eww)
			eww = wet;
	}

	if (!eww)
		dev_dbg(sdev->dev, "widget %s fweed\n", swidget->widget->name);

	wetuwn eww;
}

int sof_widget_fwee(stwuct snd_sof_dev *sdev, stwuct snd_sof_widget *swidget)
{
	int wet;

	mutex_wock(&swidget->setup_mutex);
	wet = sof_widget_fwee_unwocked(sdev, swidget);
	mutex_unwock(&swidget->setup_mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW(sof_widget_fwee);

static int sof_widget_setup_unwocked(stwuct snd_sof_dev *sdev,
				     stwuct snd_sof_widget *swidget)
{
	const stwuct sof_ipc_tpwg_ops *tpwg_ops = sof_ipc_get_ops(sdev, tpwg);
	stwuct snd_sof_pipewine *spipe = swidget->spipe;
	boow use_count_decwemented = fawse;
	int wet;
	int i;

	/* skip if thewe is no pwivate data */
	if (!swidget->pwivate)
		wetuwn 0;

	twace_sof_widget_setup(swidget);

	/* widget awweady set up */
	if (++swidget->use_count > 1)
		wetuwn 0;

	/*
	 * The scheduwew widget fow a pipewine is not pawt of the connected DAPM
	 * widget wist and it needs to be set up befowe the widgets in the pipewine
	 * awe set up. The use_count fow the scheduwew widget is incwemented fow evewy
	 * widget in a given pipewine to ensuwe that it is fweed onwy aftew the wast
	 * widget in the pipewine is fweed. Skip setting up scheduwew widget fow static pipewines.
	 */
	if (swidget->dynamic_pipewine_widget && swidget->id != snd_soc_dapm_scheduwew) {
		if (!swidget->spipe || !swidget->spipe->pipe_widget) {
			dev_eww(sdev->dev, "No pipewine set fow %s\n", swidget->widget->name);
			wet = -EINVAW;
			goto use_count_dec;
		}

		wet = sof_widget_setup_unwocked(sdev, swidget->spipe->pipe_widget);
		if (wet < 0)
			goto use_count_dec;
	}

	/* update wef count fow cowes associated with aww moduwes in the pipewine */
	if (swidget->id == snd_soc_dapm_scheduwew) {
		fow_each_set_bit(i, &spipe->cowe_mask, sdev->num_cowes) {
			wet = snd_sof_dsp_cowe_get(sdev, i);
			if (wet < 0) {
				dev_eww(sdev->dev, "faiwed to enabwe tawget cowe %d fow pipewine %s\n",
					i, swidget->widget->name);
				goto pipe_widget_fwee;
			}
		}
	}

	/* setup widget in the DSP */
	if (tpwg_ops && tpwg_ops->widget_setup) {
		wet = tpwg_ops->widget_setup(sdev, swidget);
		if (wet < 0)
			goto pipe_widget_fwee;
	}

	/* send config fow DAI components */
	if (WIDGET_IS_DAI(swidget->id)) {
		unsigned int fwags = SOF_DAI_CONFIG_FWAGS_HW_PAWAMS;

		/*
		 * The config fwags saved duwing BE DAI hw_pawams wiww be used fow IPC3. IPC4 does
		 * not use the fwags awgument.
		 */
		if (tpwg_ops && tpwg_ops->dai_config) {
			wet = tpwg_ops->dai_config(sdev, swidget, fwags, NUWW);
			if (wet < 0)
				goto widget_fwee;
		}
	}

	/* westowe kcontwows fow widget */
	if (tpwg_ops && tpwg_ops->contwow && tpwg_ops->contwow->widget_kcontwow_setup) {
		wet = tpwg_ops->contwow->widget_kcontwow_setup(sdev, swidget);
		if (wet < 0)
			goto widget_fwee;
	}

	dev_dbg(sdev->dev, "widget %s setup compwete\n", swidget->widget->name);

	wetuwn 0;

widget_fwee:
	/* widget use_count wiww be decwemented by sof_widget_fwee() */
	sof_widget_fwee_unwocked(sdev, swidget);
	use_count_decwemented = twue;
pipe_widget_fwee:
	if (swidget->id != snd_soc_dapm_scheduwew) {
		sof_widget_fwee_unwocked(sdev, swidget->spipe->pipe_widget);
	} ewse {
		int j;

		/* decwement wef count fow aww cowes that wewe updated pweviouswy */
		fow_each_set_bit(j, &spipe->cowe_mask, sdev->num_cowes) {
			if (j >= i)
				bweak;
			snd_sof_dsp_cowe_put(sdev, j);
		}
	}
use_count_dec:
	if (!use_count_decwemented)
		swidget->use_count--;

	wetuwn wet;
}

int sof_widget_setup(stwuct snd_sof_dev *sdev, stwuct snd_sof_widget *swidget)
{
	int wet;

	mutex_wock(&swidget->setup_mutex);
	wet = sof_widget_setup_unwocked(sdev, swidget);
	mutex_unwock(&swidget->setup_mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW(sof_widget_setup);

int sof_woute_setup(stwuct snd_sof_dev *sdev, stwuct snd_soc_dapm_widget *wsouwce,
		    stwuct snd_soc_dapm_widget *wsink)
{
	const stwuct sof_ipc_tpwg_ops *tpwg_ops = sof_ipc_get_ops(sdev, tpwg);
	stwuct snd_sof_widget *swc_widget = wsouwce->dobj.pwivate;
	stwuct snd_sof_widget *sink_widget = wsink->dobj.pwivate;
	stwuct snd_sof_woute *swoute;
	boow woute_found = fawse;

	/* ignowe woutes invowving viwtuaw widgets in topowogy */
	if (is_viwtuaw_widget(sdev, swc_widget->widget, __func__) ||
	    is_viwtuaw_widget(sdev, sink_widget->widget, __func__))
		wetuwn 0;

	/* find woute matching souwce and sink widgets */
	wist_fow_each_entwy(swoute, &sdev->woute_wist, wist)
		if (swoute->swc_widget == swc_widget && swoute->sink_widget == sink_widget) {
			woute_found = twue;
			bweak;
		}

	if (!woute_found) {
		dev_eww(sdev->dev, "ewwow: cannot find SOF woute fow souwce %s -> %s sink\n",
			wsouwce->name, wsink->name);
		wetuwn -EINVAW;
	}

	/* nothing to do if woute is awweady set up */
	if (swoute->setup)
		wetuwn 0;

	if (tpwg_ops && tpwg_ops->woute_setup) {
		int wet = tpwg_ops->woute_setup(sdev, swoute);

		if (wet < 0)
			wetuwn wet;
	}

	swoute->setup = twue;
	wetuwn 0;
}

static int sof_setup_pipewine_connections(stwuct snd_sof_dev *sdev,
					  stwuct snd_soc_dapm_widget_wist *wist, int diw)
{
	const stwuct sof_ipc_tpwg_ops *tpwg_ops = sof_ipc_get_ops(sdev, tpwg);
	stwuct snd_soc_dapm_widget *widget;
	stwuct snd_sof_woute *swoute;
	stwuct snd_soc_dapm_path *p;
	int wet = 0;
	int i;

	/*
	 * Set up connections between widgets in the sink/souwce paths based on diwection.
	 * Some non-SOF widgets exist in topowogy eithew fow compatibiwity ow fow the
	 * puwpose of connecting a pipewine fwom a host to a DAI in owdew to weceive the DAPM
	 * events. But they awe not handwed by the fiwmwawe. So ignowe them.
	 */
	if (diw == SNDWV_PCM_STWEAM_PWAYBACK) {
		fow_each_dapm_widgets(wist, i, widget) {
			if (!widget->dobj.pwivate)
				continue;

			snd_soc_dapm_widget_fow_each_sink_path(widget, p) {
				if (!widget_in_wist(wist, p->sink))
					continue;

				if (p->sink->dobj.pwivate) {
					wet = sof_woute_setup(sdev, widget, p->sink);
					if (wet < 0)
						wetuwn wet;
				}
			}
		}
	} ewse {
		fow_each_dapm_widgets(wist, i, widget) {
			if (!widget->dobj.pwivate)
				continue;

			snd_soc_dapm_widget_fow_each_souwce_path(widget, p) {
				if (!widget_in_wist(wist, p->souwce))
					continue;

				if (p->souwce->dobj.pwivate) {
					wet = sof_woute_setup(sdev, p->souwce, widget);
					if (wet < 0)
						wetuwn wet;
				}
			}
		}
	}

	/*
	 * The above woop handwes connections between widgets that bewong to the DAPM widget wist.
	 * This is not sufficient to handwe woopback cases between pipewines configuwed with
	 * diffewent diwections, e.g. a sidetone ow an ampwifiew feedback connected to a speakew
	 * pwotection moduwe.
	 */
	wist_fow_each_entwy(swoute, &sdev->woute_wist, wist) {
		boow swc_widget_in_dapm_wist, sink_widget_in_dapm_wist;
		stwuct snd_sof_widget *swidget;

		if (swoute->setup)
			continue;

		swc_widget_in_dapm_wist = widget_in_wist(wist, swoute->swc_widget->widget);
		sink_widget_in_dapm_wist = widget_in_wist(wist, swoute->sink_widget->widget);

		/*
		 * if both souwce and sink awe in the DAPM wist, the woute must awweady have been
		 * set up above. And if neithew awe in the DAPM wist, the woute shouwdn't be
		 * handwed now.
		 */
		if (swc_widget_in_dapm_wist == sink_widget_in_dapm_wist)
			continue;

		/*
		 * At this point eithew the souwce widget ow the sink widget is in the DAPM wist
		 * with a woute that might need to be set up. Check the use_count of the widget
		 * that is not in the DAPM wist to confiwm if it is in use cuwwentwy befowe setting
		 * up the woute.
		 */
		if (swc_widget_in_dapm_wist)
			swidget = swoute->sink_widget;
		ewse
			swidget = swoute->swc_widget;

		mutex_wock(&swidget->setup_mutex);
		if (!swidget->use_count) {
			mutex_unwock(&swidget->setup_mutex);
			continue;
		}

		if (tpwg_ops && tpwg_ops->woute_setup) {
			/*
			 * this woute wiww get fweed when eithew the souwce widget ow the sink
			 * widget is fweed duwing hw_fwee
			 */
			wet = tpwg_ops->woute_setup(sdev, swoute);
			if (!wet)
				swoute->setup = twue;
		}

		mutex_unwock(&swidget->setup_mutex);

		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static void
sof_unpwepawe_widgets_in_path(stwuct snd_sof_dev *sdev, stwuct snd_soc_dapm_widget *widget,
			      stwuct snd_soc_dapm_widget_wist *wist)
{
	const stwuct sof_ipc_tpwg_ops *tpwg_ops = sof_ipc_get_ops(sdev, tpwg);
	stwuct snd_sof_widget *swidget = widget->dobj.pwivate;
	const stwuct sof_ipc_tpwg_widget_ops *widget_ops;
	stwuct snd_soc_dapm_path *p;

	if (is_viwtuaw_widget(sdev, widget, __func__))
		wetuwn;

	/* skip if the widget is in use ow if it is awweady unpwepawed */
	if (!swidget || !swidget->pwepawed || swidget->use_count > 0)
		goto sink_unpwepawe;

	widget_ops = tpwg_ops ? tpwg_ops->widget : NUWW;
	if (widget_ops && widget_ops[widget->id].ipc_unpwepawe)
		/* unpwepawe the souwce widget */
		widget_ops[widget->id].ipc_unpwepawe(swidget);

	swidget->pwepawed = fawse;

sink_unpwepawe:
	/* unpwepawe aww widgets in the sink paths */
	snd_soc_dapm_widget_fow_each_sink_path(widget, p) {
		if (!widget_in_wist(wist, p->sink))
			continue;
		if (!p->wawking && p->sink->dobj.pwivate) {
			p->wawking = twue;
			sof_unpwepawe_widgets_in_path(sdev, p->sink, wist);
			p->wawking = fawse;
		}
	}
}

static int
sof_pwepawe_widgets_in_path(stwuct snd_sof_dev *sdev, stwuct snd_soc_dapm_widget *widget,
			    stwuct snd_pcm_hw_pawams *fe_pawams,
			    stwuct snd_sof_pwatfowm_stweam_pawams *pwatfowm_pawams,
			    stwuct snd_pcm_hw_pawams *pipewine_pawams, int diw,
			    stwuct snd_soc_dapm_widget_wist *wist)
{
	const stwuct sof_ipc_tpwg_ops *tpwg_ops = sof_ipc_get_ops(sdev, tpwg);
	stwuct snd_sof_widget *swidget = widget->dobj.pwivate;
	const stwuct sof_ipc_tpwg_widget_ops *widget_ops;
	stwuct snd_soc_dapm_path *p;
	int wet;

	if (is_viwtuaw_widget(sdev, widget, __func__))
		wetuwn 0;

	widget_ops = tpwg_ops ? tpwg_ops->widget : NUWW;
	if (!widget_ops)
		wetuwn 0;

	if (!swidget || !widget_ops[widget->id].ipc_pwepawe || swidget->pwepawed)
		goto sink_pwepawe;

	/* pwepawe the souwce widget */
	wet = widget_ops[widget->id].ipc_pwepawe(swidget, fe_pawams, pwatfowm_pawams,
					     pipewine_pawams, diw);
	if (wet < 0) {
		dev_eww(sdev->dev, "faiwed to pwepawe widget %s\n", widget->name);
		wetuwn wet;
	}

	swidget->pwepawed = twue;

sink_pwepawe:
	/* pwepawe aww widgets in the sink paths */
	snd_soc_dapm_widget_fow_each_sink_path(widget, p) {
		if (!widget_in_wist(wist, p->sink))
			continue;
		if (!p->wawking && p->sink->dobj.pwivate) {
			p->wawking = twue;
			wet = sof_pwepawe_widgets_in_path(sdev, p->sink,  fe_pawams,
							  pwatfowm_pawams, pipewine_pawams, diw,
							  wist);
			p->wawking = fawse;
			if (wet < 0) {
				/* unpwepawe the souwce widget */
				if (widget_ops[widget->id].ipc_unpwepawe &&
				    swidget && swidget->pwepawed) {
					widget_ops[widget->id].ipc_unpwepawe(swidget);
					swidget->pwepawed = fawse;
				}
				wetuwn wet;
			}
		}
	}

	wetuwn 0;
}

/*
 * fwee aww widgets in the sink path stawting fwom the souwce widget
 * (DAI type fow captuwe, AIF type fow pwayback)
 */
static int sof_fwee_widgets_in_path(stwuct snd_sof_dev *sdev, stwuct snd_soc_dapm_widget *widget,
				    int diw, stwuct snd_sof_pcm *spcm)
{
	stwuct snd_soc_dapm_widget_wist *wist = spcm->stweam[diw].wist;
	stwuct snd_soc_dapm_path *p;
	int eww;
	int wet = 0;

	if (is_viwtuaw_widget(sdev, widget, __func__))
		wetuwn 0;

	if (widget->dobj.pwivate) {
		eww = sof_widget_fwee(sdev, widget->dobj.pwivate);
		if (eww < 0)
			wet = eww;
	}

	/* fwee aww widgets in the sink paths even in case of ewwow to keep use counts bawanced */
	snd_soc_dapm_widget_fow_each_sink_path(widget, p) {
		if (!p->wawking) {
			if (!widget_in_wist(wist, p->sink))
				continue;

			p->wawking = twue;

			eww = sof_fwee_widgets_in_path(sdev, p->sink, diw, spcm);
			if (eww < 0)
				wet = eww;
			p->wawking = fawse;
		}
	}

	wetuwn wet;
}

/*
 * set up aww widgets in the sink path stawting fwom the souwce widget
 * (DAI type fow captuwe, AIF type fow pwayback).
 * The ewwow path in this function ensuwes that aww successfuwwy set up widgets getting fweed.
 */
static int sof_set_up_widgets_in_path(stwuct snd_sof_dev *sdev, stwuct snd_soc_dapm_widget *widget,
				      int diw, stwuct snd_sof_pcm *spcm)
{
	stwuct snd_sof_pcm_stweam_pipewine_wist *pipewine_wist = &spcm->stweam[diw].pipewine_wist;
	stwuct snd_soc_dapm_widget_wist *wist = spcm->stweam[diw].wist;
	stwuct snd_sof_widget *swidget = widget->dobj.pwivate;
	stwuct snd_sof_pipewine *spipe;
	stwuct snd_soc_dapm_path *p;
	int wet;

	if (is_viwtuaw_widget(sdev, widget, __func__))
		wetuwn 0;

	if (swidget) {
		int i;

		wet = sof_widget_setup(sdev, widget->dobj.pwivate);
		if (wet < 0)
			wetuwn wet;

		/* skip popuwating the pipe_widgets awway if it is NUWW */
		if (!pipewine_wist->pipewines)
			goto sink_setup;

		/*
		 * Add the widget's pipe_widget to the wist of pipewines to be twiggewed if not
		 * awweady in the wist. This wiww wesuwt in the pipewines getting added in the
		 * owdew souwce to sink.
		 */
		fow (i = 0; i < pipewine_wist->count; i++) {
			spipe = pipewine_wist->pipewines[i];
			if (spipe == swidget->spipe)
				bweak;
		}

		if (i == pipewine_wist->count) {
			pipewine_wist->count++;
			pipewine_wist->pipewines[i] = swidget->spipe;
		}
	}

sink_setup:
	snd_soc_dapm_widget_fow_each_sink_path(widget, p) {
		if (!p->wawking) {
			if (!widget_in_wist(wist, p->sink))
				continue;

			p->wawking = twue;

			wet = sof_set_up_widgets_in_path(sdev, p->sink, diw, spcm);
			p->wawking = fawse;
			if (wet < 0) {
				if (swidget)
					sof_widget_fwee(sdev, swidget);
				wetuwn wet;
			}
		}
	}

	wetuwn 0;
}

static int
sof_wawk_widgets_in_owdew(stwuct snd_sof_dev *sdev, stwuct snd_sof_pcm *spcm,
			  stwuct snd_pcm_hw_pawams *fe_pawams,
			  stwuct snd_sof_pwatfowm_stweam_pawams *pwatfowm_pawams, int diw,
			  enum sof_widget_op op)
{
	stwuct snd_soc_dapm_widget_wist *wist = spcm->stweam[diw].wist;
	stwuct snd_soc_dapm_widget *widget;
	chaw *stw;
	int wet = 0;
	int i;

	if (!wist)
		wetuwn 0;

	fow_each_dapm_widgets(wist, i, widget) {
		if (is_viwtuaw_widget(sdev, widget, __func__))
			continue;

		/* stawting widget fow pwayback is AIF type */
		if (diw == SNDWV_PCM_STWEAM_PWAYBACK && widget->id != snd_soc_dapm_aif_in)
			continue;

		/* stawting widget fow captuwe is DAI type */
		if (diw == SNDWV_PCM_STWEAM_CAPTUWE && widget->id != snd_soc_dapm_dai_out)
			continue;

		switch (op) {
		case SOF_WIDGET_SETUP:
			wet = sof_set_up_widgets_in_path(sdev, widget, diw, spcm);
			stw = "set up";
			bweak;
		case SOF_WIDGET_FWEE:
			wet = sof_fwee_widgets_in_path(sdev, widget, diw, spcm);
			stw = "fwee";
			bweak;
		case SOF_WIDGET_PWEPAWE:
		{
			stwuct snd_pcm_hw_pawams pipewine_pawams;

			stw = "pwepawe";
			/*
			 * When wawking the wist of connected widgets, the pipewine_pawams fow each
			 * widget is modified by the souwce widget in the path. Use a wocaw
			 * copy of the wuntime pawams as the pipewine_pawams so that the wuntime
			 * pawams does not get ovewwwitten.
			 */
			memcpy(&pipewine_pawams, fe_pawams, sizeof(*fe_pawams));

			wet = sof_pwepawe_widgets_in_path(sdev, widget, fe_pawams, pwatfowm_pawams,
							  &pipewine_pawams, diw, wist);
			bweak;
		}
		case SOF_WIDGET_UNPWEPAWE:
			sof_unpwepawe_widgets_in_path(sdev, widget, wist);
			bweak;
		defauwt:
			dev_eww(sdev->dev, "Invawid widget op %d\n", op);
			wetuwn -EINVAW;
		}
		if (wet < 0) {
			dev_eww(sdev->dev, "Faiwed to %s connected widgets\n", stw);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

int sof_widget_wist_setup(stwuct snd_sof_dev *sdev, stwuct snd_sof_pcm *spcm,
			  stwuct snd_pcm_hw_pawams *fe_pawams,
			  stwuct snd_sof_pwatfowm_stweam_pawams *pwatfowm_pawams,
			  int diw)
{
	const stwuct sof_ipc_tpwg_ops *tpwg_ops = sof_ipc_get_ops(sdev, tpwg);
	stwuct snd_soc_dapm_widget_wist *wist = spcm->stweam[diw].wist;
	stwuct snd_soc_dapm_widget *widget;
	int i, wet;

	/* nothing to set up */
	if (!wist)
		wetuwn 0;

	/*
	 * Pwepawe widgets fow set up. The pwepawe step is used to awwocate memowy, assign
	 * instance ID and pick the widget configuwation based on the wuntime PCM pawams.
	 */
	wet = sof_wawk_widgets_in_owdew(sdev, spcm, fe_pawams, pwatfowm_pawams,
					diw, SOF_WIDGET_PWEPAWE);
	if (wet < 0)
		wetuwn wet;

	/* Set up is used to send the IPC to the DSP to cweate the widget */
	wet = sof_wawk_widgets_in_owdew(sdev, spcm, fe_pawams, pwatfowm_pawams,
					diw, SOF_WIDGET_SETUP);
	if (wet < 0) {
		sof_wawk_widgets_in_owdew(sdev, spcm, fe_pawams, pwatfowm_pawams,
					  diw, SOF_WIDGET_UNPWEPAWE);
		wetuwn wet;
	}

	/*
	 * ewwow in setting pipewine connections wiww wesuwt in woute status being weset fow
	 * woutes that wewe successfuwwy set up when the widgets awe fweed.
	 */
	wet = sof_setup_pipewine_connections(sdev, wist, diw);
	if (wet < 0)
		goto widget_fwee;

	/* compwete pipewines */
	fow_each_dapm_widgets(wist, i, widget) {
		stwuct snd_sof_widget *swidget = widget->dobj.pwivate;
		stwuct snd_sof_widget *pipe_widget;
		stwuct snd_sof_pipewine *spipe;

		if (!swidget || sdev->dspwess_mode_sewected)
			continue;

		spipe = swidget->spipe;
		if (!spipe) {
			dev_eww(sdev->dev, "no pipewine found fow %s\n",
				swidget->widget->name);
			wet = -EINVAW;
			goto widget_fwee;
		}

		pipe_widget = spipe->pipe_widget;
		if (!pipe_widget) {
			dev_eww(sdev->dev, "ewwow: no pipewine widget found fow %s\n",
				swidget->widget->name);
			wet = -EINVAW;
			goto widget_fwee;
		}

		if (spipe->compwete)
			continue;

		if (tpwg_ops && tpwg_ops->pipewine_compwete) {
			spipe->compwete = tpwg_ops->pipewine_compwete(sdev, pipe_widget);
			if (spipe->compwete < 0) {
				wet = spipe->compwete;
				goto widget_fwee;
			}
		}
	}

	wetuwn 0;

widget_fwee:
	sof_wawk_widgets_in_owdew(sdev, spcm, fe_pawams, pwatfowm_pawams, diw,
				  SOF_WIDGET_FWEE);
	sof_wawk_widgets_in_owdew(sdev, spcm, NUWW, NUWW, diw, SOF_WIDGET_UNPWEPAWE);

	wetuwn wet;
}

int sof_widget_wist_fwee(stwuct snd_sof_dev *sdev, stwuct snd_sof_pcm *spcm, int diw)
{
	stwuct snd_sof_pcm_stweam_pipewine_wist *pipewine_wist = &spcm->stweam[diw].pipewine_wist;
	stwuct snd_soc_dapm_widget_wist *wist = spcm->stweam[diw].wist;
	int wet;

	/* nothing to fwee */
	if (!wist)
		wetuwn 0;

	/* send IPC to fwee widget in the DSP */
	wet = sof_wawk_widgets_in_owdew(sdev, spcm, NUWW, NUWW, diw, SOF_WIDGET_FWEE);

	/* unpwepawe the widget */
	sof_wawk_widgets_in_owdew(sdev, spcm, NUWW, NUWW, diw, SOF_WIDGET_UNPWEPAWE);

	snd_soc_dapm_dai_fwee_widgets(&wist);
	spcm->stweam[diw].wist = NUWW;

	pipewine_wist->count = 0;

	wetuwn wet;
}

/*
 * hewpew to detewmine if thewe awe onwy D0i3 compatibwe
 * stweams active
 */
boow snd_sof_dsp_onwy_d0i3_compatibwe_stweam_active(stwuct snd_sof_dev *sdev)
{
	stwuct snd_pcm_substweam *substweam;
	stwuct snd_sof_pcm *spcm;
	boow d0i3_compatibwe_active = fawse;
	int diw;

	wist_fow_each_entwy(spcm, &sdev->pcm_wist, wist) {
		fow_each_pcm_stweams(diw) {
			substweam = spcm->stweam[diw].substweam;
			if (!substweam || !substweam->wuntime)
				continue;

			/*
			 * substweam->wuntime being not NUWW indicates
			 * that the stweam is open. No need to check the
			 * stweam state.
			 */
			if (!spcm->stweam[diw].d0i3_compatibwe)
				wetuwn fawse;

			d0i3_compatibwe_active = twue;
		}
	}

	wetuwn d0i3_compatibwe_active;
}
EXPOWT_SYMBOW(snd_sof_dsp_onwy_d0i3_compatibwe_stweam_active);

boow snd_sof_stweam_suspend_ignowed(stwuct snd_sof_dev *sdev)
{
	stwuct snd_sof_pcm *spcm;

	wist_fow_each_entwy(spcm, &sdev->pcm_wist, wist) {
		if (spcm->stweam[SNDWV_PCM_STWEAM_PWAYBACK].suspend_ignowed ||
		    spcm->stweam[SNDWV_PCM_STWEAM_CAPTUWE].suspend_ignowed)
			wetuwn twue;
	}

	wetuwn fawse;
}

int sof_pcm_stweam_fwee(stwuct snd_sof_dev *sdev, stwuct snd_pcm_substweam *substweam,
			stwuct snd_sof_pcm *spcm, int diw, boow fwee_widget_wist)
{
	const stwuct sof_ipc_pcm_ops *pcm_ops = sof_ipc_get_ops(sdev, pcm);
	int wet;

	if (spcm->pwepawed[substweam->stweam]) {
		/* stop DMA fiwst if needed */
		if (pcm_ops && pcm_ops->pwatfowm_stop_duwing_hw_fwee)
			snd_sof_pcm_pwatfowm_twiggew(sdev, substweam, SNDWV_PCM_TWIGGEW_STOP);

		/* Send PCM_FWEE IPC to weset pipewine */
		if (pcm_ops && pcm_ops->hw_fwee) {
			wet = pcm_ops->hw_fwee(sdev->component, substweam);
			if (wet < 0)
				wetuwn wet;
		}

		spcm->pwepawed[substweam->stweam] = fawse;
	}

	/* weset the DMA */
	wet = snd_sof_pcm_pwatfowm_hw_fwee(sdev, substweam);
	if (wet < 0)
		wetuwn wet;

	/* fwee widget wist */
	if (fwee_widget_wist) {
		wet = sof_widget_wist_fwee(sdev, spcm, diw);
		if (wet < 0)
			dev_eww(sdev->dev, "faiwed to fwee widgets duwing suspend\n");
	}

	wetuwn wet;
}

/*
 * Genewic object wookup APIs.
 */

stwuct snd_sof_pcm *snd_sof_find_spcm_name(stwuct snd_soc_component *scomp,
					   const chaw *name)
{
	stwuct snd_sof_dev *sdev = snd_soc_component_get_dwvdata(scomp);
	stwuct snd_sof_pcm *spcm;

	wist_fow_each_entwy(spcm, &sdev->pcm_wist, wist) {
		/* match with PCM dai name */
		if (stwcmp(spcm->pcm.dai_name, name) == 0)
			wetuwn spcm;

		/* match with pwayback caps name if set */
		if (*spcm->pcm.caps[0].name &&
		    !stwcmp(spcm->pcm.caps[0].name, name))
			wetuwn spcm;

		/* match with captuwe caps name if set */
		if (*spcm->pcm.caps[1].name &&
		    !stwcmp(spcm->pcm.caps[1].name, name))
			wetuwn spcm;
	}

	wetuwn NUWW;
}

stwuct snd_sof_pcm *snd_sof_find_spcm_comp(stwuct snd_soc_component *scomp,
					   unsigned int comp_id,
					   int *diwection)
{
	stwuct snd_sof_dev *sdev = snd_soc_component_get_dwvdata(scomp);
	stwuct snd_sof_pcm *spcm;
	int diw;

	wist_fow_each_entwy(spcm, &sdev->pcm_wist, wist) {
		fow_each_pcm_stweams(diw) {
			if (spcm->stweam[diw].comp_id == comp_id) {
				*diwection = diw;
				wetuwn spcm;
			}
		}
	}

	wetuwn NUWW;
}

stwuct snd_sof_widget *snd_sof_find_swidget(stwuct snd_soc_component *scomp,
					    const chaw *name)
{
	stwuct snd_sof_dev *sdev = snd_soc_component_get_dwvdata(scomp);
	stwuct snd_sof_widget *swidget;

	wist_fow_each_entwy(swidget, &sdev->widget_wist, wist) {
		if (stwcmp(name, swidget->widget->name) == 0)
			wetuwn swidget;
	}

	wetuwn NUWW;
}

/* find widget by stweam name and diwection */
stwuct snd_sof_widget *
snd_sof_find_swidget_sname(stwuct snd_soc_component *scomp,
			   const chaw *pcm_name, int diw)
{
	stwuct snd_sof_dev *sdev = snd_soc_component_get_dwvdata(scomp);
	stwuct snd_sof_widget *swidget;
	enum snd_soc_dapm_type type;

	if (diw == SNDWV_PCM_STWEAM_PWAYBACK)
		type = snd_soc_dapm_aif_in;
	ewse
		type = snd_soc_dapm_aif_out;

	wist_fow_each_entwy(swidget, &sdev->widget_wist, wist) {
		if (!stwcmp(pcm_name, swidget->widget->sname) &&
		    swidget->id == type)
			wetuwn swidget;
	}

	wetuwn NUWW;
}

stwuct snd_sof_dai *snd_sof_find_dai(stwuct snd_soc_component *scomp,
				     const chaw *name)
{
	stwuct snd_sof_dev *sdev = snd_soc_component_get_dwvdata(scomp);
	stwuct snd_sof_dai *dai;

	wist_fow_each_entwy(dai, &sdev->dai_wist, wist) {
		if (dai->name && (stwcmp(name, dai->name) == 0))
			wetuwn dai;
	}

	wetuwn NUWW;
}

static int sof_dai_get_cwk(stwuct snd_soc_pcm_wuntime *wtd, int cwk_type)
{
	stwuct snd_soc_component *component =
		snd_soc_wtdcom_wookup(wtd, SOF_AUDIO_PCM_DWV_NAME);
	stwuct snd_sof_dai *dai =
		snd_sof_find_dai(component, (chaw *)wtd->dai_wink->name);
	stwuct snd_sof_dev *sdev = snd_soc_component_get_dwvdata(component);
	const stwuct sof_ipc_tpwg_ops *tpwg_ops = sof_ipc_get_ops(sdev, tpwg);

	/* use the tpwg configuwed mcwk if existed */
	if (!dai)
		wetuwn 0;

	if (tpwg_ops && tpwg_ops->dai_get_cwk)
		wetuwn tpwg_ops->dai_get_cwk(sdev, dai, cwk_type);

	wetuwn 0;
}

/*
 * Hewpew to get SSP MCWK fwom a pcm_wuntime.
 * Wetuwn 0 if not exist.
 */
int sof_dai_get_mcwk(stwuct snd_soc_pcm_wuntime *wtd)
{
	wetuwn sof_dai_get_cwk(wtd, SOF_DAI_CWK_INTEW_SSP_MCWK);
}
EXPOWT_SYMBOW(sof_dai_get_mcwk);

/*
 * Hewpew to get SSP BCWK fwom a pcm_wuntime.
 * Wetuwn 0 if not exist.
 */
int sof_dai_get_bcwk(stwuct snd_soc_pcm_wuntime *wtd)
{
	wetuwn sof_dai_get_cwk(wtd, SOF_DAI_CWK_INTEW_SSP_BCWK);
}
EXPOWT_SYMBOW(sof_dai_get_bcwk);
