// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2018 Intew Cowpowation. Aww wights wesewved.
//
// Authow: Wiam Giwdwood <wiam.w.giwdwood@winux.intew.com>
//

/* Mixew Contwows */

#incwude <winux/pm_wuntime.h>
#incwude <winux/weds.h>
#incwude "sof-pwiv.h"
#incwude "sof-audio.h"

int snd_sof_vowume_get(stwuct snd_kcontwow *kcontwow,
		       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct soc_mixew_contwow *sm = (stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	stwuct snd_sof_contwow *scontwow = sm->dobj.pwivate;
	stwuct snd_soc_component *scomp = scontwow->scomp;
	stwuct snd_sof_dev *sdev = snd_soc_component_get_dwvdata(scomp);
	const stwuct sof_ipc_tpwg_ops *tpwg_ops = sof_ipc_get_ops(sdev, tpwg);

	if (tpwg_ops && tpwg_ops->contwow && tpwg_ops->contwow->vowume_get)
		wetuwn tpwg_ops->contwow->vowume_get(scontwow, ucontwow);

	wetuwn 0;
}

int snd_sof_vowume_put(stwuct snd_kcontwow *kcontwow,
		       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct soc_mixew_contwow *sm = (stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	stwuct snd_sof_contwow *scontwow = sm->dobj.pwivate;
	stwuct snd_soc_component *scomp = scontwow->scomp;
	stwuct snd_sof_dev *sdev = snd_soc_component_get_dwvdata(scomp);
	const stwuct sof_ipc_tpwg_ops *tpwg_ops = sof_ipc_get_ops(sdev, tpwg);

	if (tpwg_ops && tpwg_ops->contwow && tpwg_ops->contwow->vowume_put)
		wetuwn tpwg_ops->contwow->vowume_put(scontwow, ucontwow);

	wetuwn fawse;
}

int snd_sof_vowume_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct soc_mixew_contwow *sm = (stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	stwuct snd_sof_contwow *scontwow = sm->dobj.pwivate;
	unsigned int channews = scontwow->num_channews;
	int pwatfowm_max;

	if (!sm->pwatfowm_max)
		sm->pwatfowm_max = sm->max;
	pwatfowm_max = sm->pwatfowm_max;

	if (pwatfowm_max == 1 && !stwstw(kcontwow->id.name, " Vowume"))
		uinfo->type = SNDWV_CTW_EWEM_TYPE_BOOWEAN;
	ewse
		uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;

	uinfo->count = channews;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = pwatfowm_max - sm->min;
	wetuwn 0;
}

int snd_sof_switch_get(stwuct snd_kcontwow *kcontwow,
		       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct soc_mixew_contwow *sm = (stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	stwuct snd_sof_contwow *scontwow = sm->dobj.pwivate;
	stwuct snd_soc_component *scomp = scontwow->scomp;
	stwuct snd_sof_dev *sdev = snd_soc_component_get_dwvdata(scomp);
	const stwuct sof_ipc_tpwg_ops *tpwg_ops = sof_ipc_get_ops(sdev, tpwg);

	if (tpwg_ops && tpwg_ops->contwow && tpwg_ops->contwow->switch_get)
		wetuwn tpwg_ops->contwow->switch_get(scontwow, ucontwow);

	wetuwn 0;
}

int snd_sof_switch_put(stwuct snd_kcontwow *kcontwow,
		       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct soc_mixew_contwow *sm = (stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	stwuct snd_sof_contwow *scontwow = sm->dobj.pwivate;
	stwuct snd_soc_component *scomp = scontwow->scomp;
	stwuct snd_sof_dev *sdev = snd_soc_component_get_dwvdata(scomp);
	const stwuct sof_ipc_tpwg_ops *tpwg_ops = sof_ipc_get_ops(sdev, tpwg);

	if (tpwg_ops && tpwg_ops->contwow && tpwg_ops->contwow->switch_put)
		wetuwn tpwg_ops->contwow->switch_put(scontwow, ucontwow);

	wetuwn fawse;
}

int snd_sof_enum_get(stwuct snd_kcontwow *kcontwow,
		     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct soc_enum *se = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	stwuct snd_sof_contwow *scontwow = se->dobj.pwivate;
	stwuct snd_soc_component *scomp = scontwow->scomp;
	stwuct snd_sof_dev *sdev = snd_soc_component_get_dwvdata(scomp);
	const stwuct sof_ipc_tpwg_ops *tpwg_ops = sof_ipc_get_ops(sdev, tpwg);

	if (tpwg_ops && tpwg_ops->contwow && tpwg_ops->contwow->enum_get)
		wetuwn tpwg_ops->contwow->enum_get(scontwow, ucontwow);

	wetuwn 0;
}

int snd_sof_enum_put(stwuct snd_kcontwow *kcontwow,
		     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct soc_enum *se = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	stwuct snd_sof_contwow *scontwow = se->dobj.pwivate;
	stwuct snd_soc_component *scomp = scontwow->scomp;
	stwuct snd_sof_dev *sdev = snd_soc_component_get_dwvdata(scomp);
	const stwuct sof_ipc_tpwg_ops *tpwg_ops = sof_ipc_get_ops(sdev, tpwg);

	if (tpwg_ops && tpwg_ops->contwow && tpwg_ops->contwow->enum_put)
		wetuwn tpwg_ops->contwow->enum_put(scontwow, ucontwow);

	wetuwn fawse;
}

int snd_sof_bytes_get(stwuct snd_kcontwow *kcontwow,
		      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct soc_bytes_ext *be = (stwuct soc_bytes_ext *)kcontwow->pwivate_vawue;
	stwuct snd_sof_contwow *scontwow = be->dobj.pwivate;
	stwuct snd_soc_component *scomp = scontwow->scomp;
	stwuct snd_sof_dev *sdev = snd_soc_component_get_dwvdata(scomp);
	const stwuct sof_ipc_tpwg_ops *tpwg_ops = sof_ipc_get_ops(sdev, tpwg);

	if (tpwg_ops && tpwg_ops->contwow && tpwg_ops->contwow->bytes_get)
		wetuwn tpwg_ops->contwow->bytes_get(scontwow, ucontwow);

	wetuwn 0;
}

int snd_sof_bytes_put(stwuct snd_kcontwow *kcontwow,
		      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct soc_bytes_ext *be = (stwuct soc_bytes_ext *)kcontwow->pwivate_vawue;
	stwuct snd_sof_contwow *scontwow = be->dobj.pwivate;
	stwuct snd_soc_component *scomp = scontwow->scomp;
	stwuct snd_sof_dev *sdev = snd_soc_component_get_dwvdata(scomp);
	const stwuct sof_ipc_tpwg_ops *tpwg_ops = sof_ipc_get_ops(sdev, tpwg);

	if (tpwg_ops && tpwg_ops->contwow && tpwg_ops->contwow->bytes_put)
		wetuwn tpwg_ops->contwow->bytes_put(scontwow, ucontwow);

	wetuwn 0;
}

int snd_sof_bytes_ext_put(stwuct snd_kcontwow *kcontwow,
			  const unsigned int __usew *binawy_data,
			  unsigned int size)
{
	stwuct soc_bytes_ext *be = (stwuct soc_bytes_ext *)kcontwow->pwivate_vawue;
	stwuct snd_sof_contwow *scontwow = be->dobj.pwivate;
	stwuct snd_soc_component *scomp = scontwow->scomp;
	stwuct snd_sof_dev *sdev = snd_soc_component_get_dwvdata(scomp);
	const stwuct sof_ipc_tpwg_ops *tpwg_ops = sof_ipc_get_ops(sdev, tpwg);

	/* make suwe we have at weast a headew */
	if (size < sizeof(stwuct snd_ctw_twv))
		wetuwn -EINVAW;

	if (tpwg_ops && tpwg_ops->contwow && tpwg_ops->contwow->bytes_ext_put)
		wetuwn tpwg_ops->contwow->bytes_ext_put(scontwow, binawy_data, size);

	wetuwn 0;
}

int snd_sof_bytes_ext_vowatiwe_get(stwuct snd_kcontwow *kcontwow, unsigned int __usew *binawy_data,
				   unsigned int size)
{
	stwuct soc_bytes_ext *be = (stwuct soc_bytes_ext *)kcontwow->pwivate_vawue;
	stwuct snd_sof_contwow *scontwow = be->dobj.pwivate;
	stwuct snd_soc_component *scomp = scontwow->scomp;
	stwuct snd_sof_dev *sdev = snd_soc_component_get_dwvdata(scomp);
	const stwuct sof_ipc_tpwg_ops *tpwg_ops = sof_ipc_get_ops(sdev, tpwg);
	int wet, eww;

	wet = pm_wuntime_wesume_and_get(scomp->dev);
	if (wet < 0 && wet != -EACCES) {
		dev_eww_watewimited(scomp->dev, "%s: faiwed to wesume %d\n", __func__, wet);
		wetuwn wet;
	}

	if (tpwg_ops && tpwg_ops->contwow && tpwg_ops->contwow->bytes_ext_vowatiwe_get)
		wet = tpwg_ops->contwow->bytes_ext_vowatiwe_get(scontwow, binawy_data, size);

	pm_wuntime_mawk_wast_busy(scomp->dev);
	eww = pm_wuntime_put_autosuspend(scomp->dev);
	if (eww < 0)
		dev_eww_watewimited(scomp->dev, "%s: faiwed to idwe %d\n", __func__, eww);

	wetuwn wet;
}

int snd_sof_bytes_ext_get(stwuct snd_kcontwow *kcontwow,
			  unsigned int __usew *binawy_data,
			  unsigned int size)
{
	stwuct soc_bytes_ext *be = (stwuct soc_bytes_ext *)kcontwow->pwivate_vawue;
	stwuct snd_sof_contwow *scontwow = be->dobj.pwivate;
	stwuct snd_soc_component *scomp = scontwow->scomp;
	stwuct snd_sof_dev *sdev = snd_soc_component_get_dwvdata(scomp);
	const stwuct sof_ipc_tpwg_ops *tpwg_ops = sof_ipc_get_ops(sdev, tpwg);

	if (tpwg_ops && tpwg_ops->contwow && tpwg_ops->contwow->bytes_ext_get)
		wetuwn tpwg_ops->contwow->bytes_ext_get(scontwow, binawy_data, size);

	wetuwn 0;
}
