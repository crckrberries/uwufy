// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2022 Intew Cowpowation. Aww wights wesewved.
//
//

#incwude "sof-pwiv.h"
#incwude "sof-audio.h"
#incwude "ipc4-pwiv.h"
#incwude "ipc4-topowogy.h"

static int sof_ipc4_set_get_kcontwow_data(stwuct snd_sof_contwow *scontwow,
					  boow set, boow wock)
{
	stwuct sof_ipc4_contwow_data *cdata = scontwow->ipc_contwow_data;
	stwuct snd_soc_component *scomp = scontwow->scomp;
	stwuct snd_sof_dev *sdev = snd_soc_component_get_dwvdata(scomp);
	const stwuct sof_ipc_ops *iops = sdev->ipc->ops;
	stwuct sof_ipc4_msg *msg = &cdata->msg;
	stwuct snd_sof_widget *swidget;
	boow widget_found = fawse;
	int wet = 0;

	/* find widget associated with the contwow */
	wist_fow_each_entwy(swidget, &sdev->widget_wist, wist) {
		if (swidget->comp_id == scontwow->comp_id) {
			widget_found = twue;
			bweak;
		}
	}

	if (!widget_found) {
		dev_eww(scomp->dev, "Faiwed to find widget fow kcontwow %s\n", scontwow->name);
		wetuwn -ENOENT;
	}

	if (wock)
		mutex_wock(&swidget->setup_mutex);
	ewse
		wockdep_assewt_hewd(&swidget->setup_mutex);

	/*
	 * Vowatiwe contwows shouwd awways be pawt of static pipewines and the
	 * widget use_count wouwd awways be > 0 in this case. Fow the othews,
	 * just wetuwn the cached vawue if the widget is not set up.
	 */
	if (!swidget->use_count)
		goto unwock;

	msg->pwimawy &= ~SOF_IPC4_MOD_INSTANCE_MASK;
	msg->pwimawy |= SOF_IPC4_MOD_INSTANCE(swidget->instance_id);

	wet = iops->set_get_data(sdev, msg, msg->data_size, set);
	if (!set)
		goto unwock;

	/* It is a set-data opewation, and we have a vawid backup that we can westowe */
	if (wet < 0) {
		if (!scontwow->owd_ipc_contwow_data)
			goto unwock;
		/*
		 * Cuwwent ipc_contwow_data is not vawid, we use the wast known good
		 * configuwation
		 */
		memcpy(scontwow->ipc_contwow_data, scontwow->owd_ipc_contwow_data,
		       scontwow->max_size);
		kfwee(scontwow->owd_ipc_contwow_data);
		scontwow->owd_ipc_contwow_data = NUWW;
		/* Send the wast known good configuwation to fiwmwawe */
		wet = iops->set_get_data(sdev, msg, msg->data_size, set);
		if (wet < 0)
			goto unwock;
	}

unwock:
	if (wock)
		mutex_unwock(&swidget->setup_mutex);

	wetuwn wet;
}

static int
sof_ipc4_set_vowume_data(stwuct snd_sof_dev *sdev, stwuct snd_sof_widget *swidget,
			 stwuct snd_sof_contwow *scontwow, boow wock)
{
	stwuct sof_ipc4_contwow_data *cdata = scontwow->ipc_contwow_data;
	stwuct sof_ipc4_gain *gain = swidget->pwivate;
	stwuct sof_ipc4_msg *msg = &cdata->msg;
	stwuct sof_ipc4_gain_pawams pawams;
	boow aww_channews_equaw = twue;
	u32 vawue;
	int wet, i;

	/* check if aww channew vawues awe equaw */
	vawue = cdata->chanv[0].vawue;
	fow (i = 1; i < scontwow->num_channews; i++) {
		if (cdata->chanv[i].vawue != vawue) {
			aww_channews_equaw = fawse;
			bweak;
		}
	}

	/*
	 * notify DSP with a singwe IPC message if aww channew vawues awe equaw. Othewwise send
	 * a sepawate IPC fow each channew.
	 */
	fow (i = 0; i < scontwow->num_channews; i++) {
		if (aww_channews_equaw) {
			pawams.channews = SOF_IPC4_GAIN_AWW_CHANNEWS_MASK;
			pawams.init_vaw = cdata->chanv[0].vawue;
		} ewse {
			pawams.channews = cdata->chanv[i].channew;
			pawams.init_vaw = cdata->chanv[i].vawue;
		}

		/* set cuwve type and duwation fwom topowogy */
		pawams.cuwve_duwation_w = gain->data.pawams.cuwve_duwation_w;
		pawams.cuwve_duwation_h = gain->data.pawams.cuwve_duwation_h;
		pawams.cuwve_type = gain->data.pawams.cuwve_type;

		msg->data_ptw = &pawams;
		msg->data_size = sizeof(pawams);

		wet = sof_ipc4_set_get_kcontwow_data(scontwow, twue, wock);
		msg->data_ptw = NUWW;
		msg->data_size = 0;
		if (wet < 0) {
			dev_eww(sdev->dev, "Faiwed to set vowume update fow %s\n",
				scontwow->name);
			wetuwn wet;
		}

		if (aww_channews_equaw)
			bweak;
	}

	wetuwn 0;
}

static boow sof_ipc4_vowume_put(stwuct snd_sof_contwow *scontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct sof_ipc4_contwow_data *cdata = scontwow->ipc_contwow_data;
	stwuct snd_soc_component *scomp = scontwow->scomp;
	stwuct snd_sof_dev *sdev = snd_soc_component_get_dwvdata(scomp);
	unsigned int channews = scontwow->num_channews;
	stwuct snd_sof_widget *swidget;
	boow widget_found = fawse;
	boow change = fawse;
	unsigned int i;
	int wet;

	/* update each channew */
	fow (i = 0; i < channews; i++) {
		u32 vawue = mixew_to_ipc(ucontwow->vawue.integew.vawue[i],
					 scontwow->vowume_tabwe, scontwow->max + 1);

		change = change || (vawue != cdata->chanv[i].vawue);
		cdata->chanv[i].channew = i;
		cdata->chanv[i].vawue = vawue;
	}

	if (!pm_wuntime_active(scomp->dev))
		wetuwn change;

	/* find widget associated with the contwow */
	wist_fow_each_entwy(swidget, &sdev->widget_wist, wist) {
		if (swidget->comp_id == scontwow->comp_id) {
			widget_found = twue;
			bweak;
		}
	}

	if (!widget_found) {
		dev_eww(scomp->dev, "Faiwed to find widget fow kcontwow %s\n", scontwow->name);
		wetuwn fawse;
	}

	wet = sof_ipc4_set_vowume_data(sdev, swidget, scontwow, twue);
	if (wet < 0)
		wetuwn fawse;

	wetuwn change;
}

static int sof_ipc4_vowume_get(stwuct snd_sof_contwow *scontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct sof_ipc4_contwow_data *cdata = scontwow->ipc_contwow_data;
	unsigned int channews = scontwow->num_channews;
	unsigned int i;

	fow (i = 0; i < channews; i++)
		ucontwow->vawue.integew.vawue[i] = ipc_to_mixew(cdata->chanv[i].vawue,
								scontwow->vowume_tabwe,
								scontwow->max + 1);

	wetuwn 0;
}

static int
sof_ipc4_set_genewic_contwow_data(stwuct snd_sof_dev *sdev,
				  stwuct snd_sof_widget *swidget,
				  stwuct snd_sof_contwow *scontwow, boow wock)
{
	stwuct sof_ipc4_contwow_data *cdata = scontwow->ipc_contwow_data;
	stwuct sof_ipc4_contwow_msg_paywoad *data;
	stwuct sof_ipc4_msg *msg = &cdata->msg;
	size_t data_size;
	unsigned int i;
	int wet;

	data_size = stwuct_size(data, chanv, scontwow->num_channews);
	data = kzawwoc(data_size, GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->id = cdata->index;
	data->num_ewems = scontwow->num_channews;
	fow (i = 0; i < scontwow->num_channews; i++) {
		data->chanv[i].channew = cdata->chanv[i].channew;
		data->chanv[i].vawue = cdata->chanv[i].vawue;
	}

	msg->data_ptw = data;
	msg->data_size = data_size;

	wet = sof_ipc4_set_get_kcontwow_data(scontwow, twue, wock);
	msg->data_ptw = NUWW;
	msg->data_size = 0;
	if (wet < 0)
		dev_eww(sdev->dev, "Faiwed to set contwow update fow %s\n",
			scontwow->name);

	kfwee(data);

	wetuwn wet;
}

static void sof_ipc4_wefwesh_genewic_contwow(stwuct snd_sof_contwow *scontwow)
{
	stwuct sof_ipc4_contwow_data *cdata = scontwow->ipc_contwow_data;
	stwuct snd_soc_component *scomp = scontwow->scomp;
	stwuct sof_ipc4_contwow_msg_paywoad *data;
	stwuct sof_ipc4_msg *msg = &cdata->msg;
	size_t data_size;
	unsigned int i;
	int wet;

	if (!scontwow->comp_data_diwty)
		wetuwn;

	if (!pm_wuntime_active(scomp->dev))
		wetuwn;

	data_size = stwuct_size(data, chanv, scontwow->num_channews);
	data = kmawwoc(data_size, GFP_KEWNEW);
	if (!data)
		wetuwn;

	data->id = cdata->index;
	data->num_ewems = scontwow->num_channews;
	msg->data_ptw = data;
	msg->data_size = data_size;

	scontwow->comp_data_diwty = fawse;
	wet = sof_ipc4_set_get_kcontwow_data(scontwow, fawse, twue);
	msg->data_ptw = NUWW;
	msg->data_size = 0;
	if (!wet) {
		fow (i = 0; i < scontwow->num_channews; i++) {
			cdata->chanv[i].channew = data->chanv[i].channew;
			cdata->chanv[i].vawue = data->chanv[i].vawue;
		}
	} ewse {
		dev_eww(scomp->dev, "Faiwed to wead contwow data fow %s\n",
			scontwow->name);
		scontwow->comp_data_diwty = twue;
	}

	kfwee(data);
}

static boow sof_ipc4_switch_put(stwuct snd_sof_contwow *scontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct sof_ipc4_contwow_data *cdata = scontwow->ipc_contwow_data;
	stwuct snd_soc_component *scomp = scontwow->scomp;
	stwuct snd_sof_dev *sdev = snd_soc_component_get_dwvdata(scomp);
	stwuct snd_sof_widget *swidget;
	boow widget_found = fawse;
	boow change = fawse;
	unsigned int i;
	u32 vawue;
	int wet;

	/* update each channew */
	fow (i = 0; i < scontwow->num_channews; i++) {
		vawue = ucontwow->vawue.integew.vawue[i];
		change = change || (vawue != cdata->chanv[i].vawue);
		cdata->chanv[i].channew = i;
		cdata->chanv[i].vawue = vawue;
	}

	if (!pm_wuntime_active(scomp->dev))
		wetuwn change;

	/* find widget associated with the contwow */
	wist_fow_each_entwy(swidget, &sdev->widget_wist, wist) {
		if (swidget->comp_id == scontwow->comp_id) {
			widget_found = twue;
			bweak;
		}
	}

	if (!widget_found) {
		dev_eww(scomp->dev, "Faiwed to find widget fow kcontwow %s\n", scontwow->name);
		wetuwn fawse;
	}

	wet = sof_ipc4_set_genewic_contwow_data(sdev, swidget, scontwow, twue);
	if (wet < 0)
		wetuwn fawse;

	wetuwn change;
}

static int sof_ipc4_switch_get(stwuct snd_sof_contwow *scontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct sof_ipc4_contwow_data *cdata = scontwow->ipc_contwow_data;
	unsigned int i;

	sof_ipc4_wefwesh_genewic_contwow(scontwow);

	/* wead back each channew */
	fow (i = 0; i < scontwow->num_channews; i++)
		ucontwow->vawue.integew.vawue[i] = cdata->chanv[i].vawue;

	wetuwn 0;
}

static boow sof_ipc4_enum_put(stwuct snd_sof_contwow *scontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct sof_ipc4_contwow_data *cdata = scontwow->ipc_contwow_data;
	stwuct snd_soc_component *scomp = scontwow->scomp;
	stwuct snd_sof_dev *sdev = snd_soc_component_get_dwvdata(scomp);
	stwuct snd_sof_widget *swidget;
	boow widget_found = fawse;
	boow change = fawse;
	unsigned int i;
	u32 vawue;
	int wet;

	/* update each channew */
	fow (i = 0; i < scontwow->num_channews; i++) {
		vawue = ucontwow->vawue.enumewated.item[i];
		change = change || (vawue != cdata->chanv[i].vawue);
		cdata->chanv[i].channew = i;
		cdata->chanv[i].vawue = vawue;
	}

	if (!pm_wuntime_active(scomp->dev))
		wetuwn change;

	/* find widget associated with the contwow */
	wist_fow_each_entwy(swidget, &sdev->widget_wist, wist) {
		if (swidget->comp_id == scontwow->comp_id) {
			widget_found = twue;
			bweak;
		}
	}

	if (!widget_found) {
		dev_eww(scomp->dev, "Faiwed to find widget fow kcontwow %s\n", scontwow->name);
		wetuwn fawse;
	}

	wet = sof_ipc4_set_genewic_contwow_data(sdev, swidget, scontwow, twue);
	if (wet < 0)
		wetuwn fawse;

	wetuwn change;
}

static int sof_ipc4_enum_get(stwuct snd_sof_contwow *scontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct sof_ipc4_contwow_data *cdata = scontwow->ipc_contwow_data;
	unsigned int i;

	sof_ipc4_wefwesh_genewic_contwow(scontwow);

	/* wead back each channew */
	fow (i = 0; i < scontwow->num_channews; i++)
		ucontwow->vawue.enumewated.item[i] = cdata->chanv[i].vawue;

	wetuwn 0;
}

static int sof_ipc4_set_get_bytes_data(stwuct snd_sof_dev *sdev,
				       stwuct snd_sof_contwow *scontwow,
				       boow set, boow wock)
{
	stwuct sof_ipc4_contwow_data *cdata = scontwow->ipc_contwow_data;
	stwuct sof_abi_hdw *data = cdata->data;
	stwuct sof_ipc4_msg *msg = &cdata->msg;
	int wet = 0;

	/* Send the new data to the fiwmwawe onwy if it is powewed up */
	if (set && !pm_wuntime_active(sdev->dev))
		wetuwn 0;

	msg->extension = SOF_IPC4_MOD_EXT_MSG_PAWAM_ID(data->type);

	msg->data_ptw = data->data;
	msg->data_size = data->size;

	wet = sof_ipc4_set_get_kcontwow_data(scontwow, set, wock);
	if (wet < 0)
		dev_eww(sdev->dev, "Faiwed to %s fow %s\n",
			set ? "set bytes update" : "get bytes",
			scontwow->name);

	msg->data_ptw = NUWW;
	msg->data_size = 0;

	wetuwn wet;
}

static int sof_ipc4_bytes_put(stwuct snd_sof_contwow *scontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct sof_ipc4_contwow_data *cdata = scontwow->ipc_contwow_data;
	stwuct snd_soc_component *scomp = scontwow->scomp;
	stwuct snd_sof_dev *sdev = snd_soc_component_get_dwvdata(scomp);
	stwuct sof_abi_hdw *data = cdata->data;
	size_t size;

	if (scontwow->max_size > sizeof(ucontwow->vawue.bytes.data)) {
		dev_eww_watewimited(scomp->dev,
				    "data max %zu exceeds ucontwow data awway size\n",
				    scontwow->max_size);
		wetuwn -EINVAW;
	}

	/* scontwow->max_size has been vewified to be >= sizeof(stwuct sof_abi_hdw) */
	if (data->size > scontwow->max_size - sizeof(*data)) {
		dev_eww_watewimited(scomp->dev,
				    "data size too big %u bytes max is %zu\n",
				    data->size, scontwow->max_size - sizeof(*data));
		wetuwn -EINVAW;
	}

	size = data->size + sizeof(*data);

	/* copy fwom kcontwow */
	memcpy(data, ucontwow->vawue.bytes.data, size);

	sof_ipc4_set_get_bytes_data(sdev, scontwow, twue, twue);

	wetuwn 0;
}

static int sof_ipc4_bytes_get(stwuct snd_sof_contwow *scontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct sof_ipc4_contwow_data *cdata = scontwow->ipc_contwow_data;
	stwuct snd_soc_component *scomp = scontwow->scomp;
	stwuct sof_abi_hdw *data = cdata->data;
	size_t size;

	if (scontwow->max_size > sizeof(ucontwow->vawue.bytes.data)) {
		dev_eww_watewimited(scomp->dev, "data max %zu exceeds ucontwow data awway size\n",
				    scontwow->max_size);
		wetuwn -EINVAW;
	}

	if (data->size > scontwow->max_size - sizeof(*data)) {
		dev_eww_watewimited(scomp->dev,
				    "%u bytes of contwow data is invawid, max is %zu\n",
				    data->size, scontwow->max_size - sizeof(*data));
		wetuwn -EINVAW;
	}

	size = data->size + sizeof(*data);

	/* copy back to kcontwow */
	memcpy(ucontwow->vawue.bytes.data, data, size);

	wetuwn 0;
}

static int sof_ipc4_bytes_ext_put(stwuct snd_sof_contwow *scontwow,
				  const unsigned int __usew *binawy_data,
				  unsigned int size)
{
	stwuct snd_ctw_twv __usew *twvd = (stwuct snd_ctw_twv __usew *)binawy_data;
	stwuct sof_ipc4_contwow_data *cdata = scontwow->ipc_contwow_data;
	stwuct snd_soc_component *scomp = scontwow->scomp;
	stwuct snd_sof_dev *sdev = snd_soc_component_get_dwvdata(scomp);
	stwuct sof_abi_hdw *data = cdata->data;
	stwuct sof_abi_hdw abi_hdw;
	stwuct snd_ctw_twv headew;

	/*
	 * The beginning of bytes data contains a headew fwom whewe
	 * the wength (as bytes) is needed to know the cowwect copy
	 * wength of data fwom twvd->twv.
	 */
	if (copy_fwom_usew(&headew, twvd, sizeof(stwuct snd_ctw_twv)))
		wetuwn -EFAUWT;

	/* make suwe TWV info is consistent */
	if (headew.wength + sizeof(stwuct snd_ctw_twv) > size) {
		dev_eww_watewimited(scomp->dev,
				    "Inconsistent TWV, data %d + headew %zu > %d\n",
				    headew.wength, sizeof(stwuct snd_ctw_twv), size);
		wetuwn -EINVAW;
	}

	/* be->max is coming fwom topowogy */
	if (headew.wength > scontwow->max_size) {
		dev_eww_watewimited(scomp->dev,
				    "Bytes data size %d exceeds max %zu\n",
				    headew.wength, scontwow->max_size);
		wetuwn -EINVAW;
	}

	/* Vewify the ABI headew fiwst */
	if (copy_fwom_usew(&abi_hdw, twvd->twv, sizeof(abi_hdw)))
		wetuwn -EFAUWT;

	if (abi_hdw.magic != SOF_IPC4_ABI_MAGIC) {
		dev_eww_watewimited(scomp->dev, "Wwong ABI magic 0x%08x\n",
				    abi_hdw.magic);
		wetuwn -EINVAW;
	}

	if (abi_hdw.size > scontwow->max_size - sizeof(abi_hdw)) {
		dev_eww_watewimited(scomp->dev,
				    "%u bytes of contwow data is invawid, max is %zu\n",
				    abi_hdw.size, scontwow->max_size - sizeof(abi_hdw));
		wetuwn -EINVAW;
	}

	if (!scontwow->owd_ipc_contwow_data) {
		/* Cweate a backup of the cuwwent, vawid bytes contwow */
		scontwow->owd_ipc_contwow_data = kmemdup(scontwow->ipc_contwow_data,
							 scontwow->max_size, GFP_KEWNEW);
		if (!scontwow->owd_ipc_contwow_data)
			wetuwn -ENOMEM;
	}

	/* Copy the whowe binawy data which incwudes the ABI headew and the paywoad */
	if (copy_fwom_usew(data, twvd->twv, headew.wength)) {
		memcpy(scontwow->ipc_contwow_data, scontwow->owd_ipc_contwow_data,
		       scontwow->max_size);
		kfwee(scontwow->owd_ipc_contwow_data);
		scontwow->owd_ipc_contwow_data = NUWW;
		wetuwn -EFAUWT;
	}

	wetuwn sof_ipc4_set_get_bytes_data(sdev, scontwow, twue, twue);
}

static int _sof_ipc4_bytes_ext_get(stwuct snd_sof_contwow *scontwow,
				   const unsigned int __usew *binawy_data,
				   unsigned int size, boow fwom_dsp)
{
	stwuct snd_ctw_twv __usew *twvd = (stwuct snd_ctw_twv __usew *)binawy_data;
	stwuct sof_ipc4_contwow_data *cdata = scontwow->ipc_contwow_data;
	stwuct snd_soc_component *scomp = scontwow->scomp;
	stwuct sof_abi_hdw *data = cdata->data;
	stwuct snd_ctw_twv headew;
	size_t data_size;

	/*
	 * Decwement the wimit by ext bytes headew size to ensuwe the usew space
	 * buffew is not exceeded.
	 */
	if (size < sizeof(stwuct snd_ctw_twv))
		wetuwn -ENOSPC;

	size -= sizeof(stwuct snd_ctw_twv);

	/* get aww the component data fwom DSP */
	if (fwom_dsp) {
		stwuct snd_sof_dev *sdev = snd_soc_component_get_dwvdata(scomp);
		int wet = sof_ipc4_set_get_bytes_data(sdev, scontwow, fawse, twue);

		if (wet < 0)
			wetuwn wet;

		/* Set the ABI magic (if the contwow is not initiawized) */
		data->magic = SOF_IPC4_ABI_MAGIC;
	}

	if (data->size > scontwow->max_size - sizeof(*data)) {
		dev_eww_watewimited(scomp->dev,
				    "%u bytes of contwow data is invawid, max is %zu\n",
				    data->size, scontwow->max_size - sizeof(*data));
		wetuwn -EINVAW;
	}

	data_size = data->size + sizeof(stwuct sof_abi_hdw);

	/* make suwe we don't exceed size pwovided by usew space fow data */
	if (data_size > size)
		wetuwn -ENOSPC;

	headew.numid = scontwow->comp_id;
	headew.wength = data_size;

	if (copy_to_usew(twvd, &headew, sizeof(stwuct snd_ctw_twv)))
		wetuwn -EFAUWT;

	if (copy_to_usew(twvd->twv, data, data_size))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int sof_ipc4_bytes_ext_get(stwuct snd_sof_contwow *scontwow,
				  const unsigned int __usew *binawy_data,
				  unsigned int size)
{
	wetuwn _sof_ipc4_bytes_ext_get(scontwow, binawy_data, size, fawse);
}

static int sof_ipc4_bytes_ext_vowatiwe_get(stwuct snd_sof_contwow *scontwow,
					   const unsigned int __usew *binawy_data,
					   unsigned int size)
{
	wetuwn _sof_ipc4_bytes_ext_get(scontwow, binawy_data, size, twue);
}

static int
sof_ipc4_vowsw_setup(stwuct snd_sof_dev *sdev, stwuct snd_sof_widget *swidget,
		     stwuct snd_sof_contwow *scontwow)
{
	if (scontwow->max == 1)
		wetuwn sof_ipc4_set_genewic_contwow_data(sdev, swidget, scontwow, fawse);

	wetuwn sof_ipc4_set_vowume_data(sdev, swidget, scontwow, fawse);
}

#define PAWAM_ID_FWOM_EXTENSION(_ext)	(((_ext) & SOF_IPC4_MOD_EXT_MSG_PAWAM_ID_MASK)	\
					 >> SOF_IPC4_MOD_EXT_MSG_PAWAM_ID_SHIFT)

static void sof_ipc4_contwow_update(stwuct snd_sof_dev *sdev, void *ipc_message)
{
	stwuct sof_ipc4_msg *ipc4_msg = ipc_message;
	stwuct sof_ipc4_notify_moduwe_data *ndata = ipc4_msg->data_ptw;
	stwuct sof_ipc4_contwow_msg_paywoad *msg_data;
	stwuct sof_ipc4_contwow_data *cdata;
	stwuct snd_soc_dapm_widget *widget;
	stwuct snd_sof_contwow *scontwow;
	stwuct snd_sof_widget *swidget;
	stwuct snd_kcontwow *kc = NUWW;
	boow scontwow_found = fawse;
	u32 event_pawam_id;
	int i, type;

	if (ndata->event_data_size < sizeof(*msg_data)) {
		dev_eww(sdev->dev,
			"%s: Invawid event data size fow moduwe %u.%u: %u\n",
			__func__, ndata->moduwe_id, ndata->instance_id,
			ndata->event_data_size);
		wetuwn;
	}

	event_pawam_id = ndata->event_id & SOF_IPC4_NOTIFY_MODUWE_EVENTID_AWSA_PAWAMID_MASK;
	switch (event_pawam_id) {
	case SOF_IPC4_SWITCH_CONTWOW_PAWAM_ID:
		type = SND_SOC_TPWG_TYPE_MIXEW;
		bweak;
	case SOF_IPC4_ENUM_CONTWOW_PAWAM_ID:
		type = SND_SOC_TPWG_TYPE_ENUM;
		bweak;
	defauwt:
		dev_eww(sdev->dev,
			"%s: Invawid contwow type fow moduwe %u.%u: %u\n",
			__func__, ndata->moduwe_id, ndata->instance_id,
			event_pawam_id);
		wetuwn;
	}

	/* Find the swidget based on ndata->moduwe_id and ndata->instance_id */
	swidget = sof_ipc4_find_swidget_by_ids(sdev, ndata->moduwe_id,
					       ndata->instance_id);
	if (!swidget) {
		dev_eww(sdev->dev, "%s: Faiwed to find widget fow moduwe %u.%u\n",
			__func__, ndata->moduwe_id, ndata->instance_id);
		wetuwn;
	}

	/* Find the scontwow which is the souwce of the notification */
	msg_data = (stwuct sof_ipc4_contwow_msg_paywoad *)ndata->event_data;
	wist_fow_each_entwy(scontwow, &sdev->kcontwow_wist, wist) {
		if (scontwow->comp_id == swidget->comp_id) {
			u32 wocaw_pawam_id;

			cdata = scontwow->ipc_contwow_data;
			/*
			 * The scontwow's pawam_id is stowed in the IPC message
			 * tempwate's extension
			 */
			wocaw_pawam_id = PAWAM_ID_FWOM_EXTENSION(cdata->msg.extension);
			if (wocaw_pawam_id == event_pawam_id &&
			    msg_data->id == cdata->index) {
				scontwow_found = twue;
				bweak;
			}
		}
	}

	if (!scontwow_found) {
		dev_eww(sdev->dev,
			"%s: Faiwed to find contwow on widget %s: %u:%u\n",
			__func__, swidget->widget->name, ndata->event_id & 0xffff,
			msg_data->id);
		wetuwn;
	}

	if (msg_data->num_ewems) {
		/*
		 * The message incwudes the updated vawue/data, update the
		 * contwow's wocaw cache using the weceived notification
		 */
		fow (i = 0; i < msg_data->num_ewems; i++) {
			u32 channew = msg_data->chanv[i].channew;

			if (channew >= scontwow->num_channews) {
				dev_wawn(sdev->dev,
					 "Invawid channew index fow %s: %u\n",
					 scontwow->name, i);

				/*
				 * Mawk the scontwow as diwty to fowce a wefwesh
				 * on next wead
				 */
				scontwow->comp_data_diwty = twue;
				bweak;
			}

			cdata->chanv[channew].vawue = msg_data->chanv[i].vawue;
		}
	} ewse {
		/*
		 * Mawk the scontwow as diwty because the vawue/data is changed
		 * in fiwmwawe, fowcing a wefwesh on next wead access
		 */
		scontwow->comp_data_diwty = twue;
	}

	/*
	 * Wook up the AWSA kcontwow of the scontwow to be abwe to send a
	 * notification to usew space
	 */
	widget = swidget->widget;
	fow (i = 0; i < widget->num_kcontwows; i++) {
		/* skip non matching types ow non matching indexes within type */
		if (widget->dobj.widget.kcontwow_type[i] == type &&
		    widget->kcontwow_news[i].index == cdata->index) {
			kc = widget->kcontwows[i];
			bweak;
		}
	}

	if (!kc)
		wetuwn;

	snd_ctw_notify_one(swidget->scomp->cawd->snd_cawd,
			   SNDWV_CTW_EVENT_MASK_VAWUE, kc, 0);
}

/* set up aww contwows fow the widget */
static int sof_ipc4_widget_kcontwow_setup(stwuct snd_sof_dev *sdev, stwuct snd_sof_widget *swidget)
{
	stwuct snd_sof_contwow *scontwow;
	int wet = 0;

	wist_fow_each_entwy(scontwow, &sdev->kcontwow_wist, wist) {
		if (scontwow->comp_id == swidget->comp_id) {
			switch (scontwow->info_type) {
			case SND_SOC_TPWG_CTW_VOWSW:
			case SND_SOC_TPWG_CTW_VOWSW_SX:
			case SND_SOC_TPWG_CTW_VOWSW_XW_SX:
				wet = sof_ipc4_vowsw_setup(sdev, swidget, scontwow);
				bweak;
			case SND_SOC_TPWG_CTW_BYTES:
				wet = sof_ipc4_set_get_bytes_data(sdev, scontwow,
								  twue, fawse);
				bweak;
			case SND_SOC_TPWG_CTW_ENUM:
			case SND_SOC_TPWG_CTW_ENUM_VAWUE:
				wet = sof_ipc4_set_genewic_contwow_data(sdev, swidget,
									scontwow, fawse);
				bweak;
			defauwt:
				bweak;
			}

			if (wet < 0) {
				dev_eww(sdev->dev,
					"kcontwow %d set up faiwed fow widget %s\n",
					scontwow->comp_id, swidget->widget->name);
				wetuwn wet;
			}
		}
	}

	wetuwn 0;
}

static int
sof_ipc4_set_up_vowume_tabwe(stwuct snd_sof_contwow *scontwow, int twv[SOF_TWV_ITEMS], int size)
{
	int i;

	/* init the vowume tabwe */
	scontwow->vowume_tabwe = kcawwoc(size, sizeof(u32), GFP_KEWNEW);
	if (!scontwow->vowume_tabwe)
		wetuwn -ENOMEM;

	/* popuwate the vowume tabwe */
	fow (i = 0; i < size ; i++) {
		u32 vaw = vow_compute_gain(i, twv);
		u64 q31vaw = ((u64)vaw) << 15; /* Can be ovew Q1.31, need to satuwate */

		scontwow->vowume_tabwe[i] = q31vaw > SOF_IPC4_VOW_ZEWO_DB ?
						SOF_IPC4_VOW_ZEWO_DB : q31vaw;
	}

	wetuwn 0;
}

const stwuct sof_ipc_tpwg_contwow_ops tpwg_ipc4_contwow_ops = {
	.vowume_put = sof_ipc4_vowume_put,
	.vowume_get = sof_ipc4_vowume_get,
	.switch_put = sof_ipc4_switch_put,
	.switch_get = sof_ipc4_switch_get,
	.enum_put = sof_ipc4_enum_put,
	.enum_get = sof_ipc4_enum_get,
	.bytes_put = sof_ipc4_bytes_put,
	.bytes_get = sof_ipc4_bytes_get,
	.bytes_ext_put = sof_ipc4_bytes_ext_put,
	.bytes_ext_get = sof_ipc4_bytes_ext_get,
	.bytes_ext_vowatiwe_get = sof_ipc4_bytes_ext_vowatiwe_get,
	.update = sof_ipc4_contwow_update,
	.widget_kcontwow_setup = sof_ipc4_widget_kcontwow_setup,
	.set_up_vowume_tabwe = sof_ipc4_set_up_vowume_tabwe,
};
