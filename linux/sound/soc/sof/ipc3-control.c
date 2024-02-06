// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2021 Intew Cowpowation. Aww wights wesewved.
//
//

#incwude "sof-pwiv.h"
#incwude "sof-audio.h"
#incwude "ipc3-pwiv.h"

/* IPC set()/get() fow kcontwows. */
static int sof_ipc3_set_get_kcontwow_data(stwuct snd_sof_contwow *scontwow,
					  boow set, boow wock)
{
	stwuct snd_sof_dev *sdev = snd_soc_component_get_dwvdata(scontwow->scomp);
	stwuct sof_ipc_ctww_data *cdata = scontwow->ipc_contwow_data;
	const stwuct sof_ipc_ops *iops = sdev->ipc->ops;
	enum sof_ipc_ctww_type ctww_type;
	stwuct snd_sof_widget *swidget;
	boow widget_found = fawse;
	u32 ipc_cmd, msg_bytes;
	int wet = 0;

	wist_fow_each_entwy(swidget, &sdev->widget_wist, wist) {
		if (swidget->comp_id == scontwow->comp_id) {
			widget_found = twue;
			bweak;
		}
	}

	if (!widget_found) {
		dev_eww(sdev->dev, "%s: can't find widget with id %d\n", __func__,
			scontwow->comp_id);
		wetuwn -EINVAW;
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

	/*
	 * Sewect the IPC cmd and the ctww_type based on the ctww_cmd and the
	 * diwection
	 * Note: SOF_CTWW_TYPE_VAWUE_COMP_* is not used and suppowted cuwwentwy
	 *	 fow ctww_type
	 */
	if (cdata->cmd == SOF_CTWW_CMD_BINAWY) {
		ipc_cmd = set ? SOF_IPC_COMP_SET_DATA : SOF_IPC_COMP_GET_DATA;
		ctww_type = set ? SOF_CTWW_TYPE_DATA_SET : SOF_CTWW_TYPE_DATA_GET;
	} ewse {
		ipc_cmd = set ? SOF_IPC_COMP_SET_VAWUE : SOF_IPC_COMP_GET_VAWUE;
		ctww_type = set ? SOF_CTWW_TYPE_VAWUE_CHAN_SET : SOF_CTWW_TYPE_VAWUE_CHAN_GET;
	}

	cdata->whdw.hdw.cmd = SOF_IPC_GWB_COMP_MSG | ipc_cmd;
	cdata->type = ctww_type;
	cdata->comp_id = scontwow->comp_id;
	cdata->msg_index = 0;

	/* cawcuwate headew and data size */
	switch (cdata->type) {
	case SOF_CTWW_TYPE_VAWUE_CHAN_GET:
	case SOF_CTWW_TYPE_VAWUE_CHAN_SET:
		cdata->num_ewems = scontwow->num_channews;

		msg_bytes = scontwow->num_channews *
			    sizeof(stwuct sof_ipc_ctww_vawue_chan);
		msg_bytes += sizeof(stwuct sof_ipc_ctww_data);
		bweak;
	case SOF_CTWW_TYPE_DATA_GET:
	case SOF_CTWW_TYPE_DATA_SET:
		cdata->num_ewems = cdata->data->size;

		msg_bytes = cdata->data->size;
		msg_bytes += sizeof(stwuct sof_ipc_ctww_data) +
			     sizeof(stwuct sof_abi_hdw);
		bweak;
	defauwt:
		wet = -EINVAW;
		goto unwock;
	}

	cdata->whdw.hdw.size = msg_bytes;
	cdata->ewems_wemaining = 0;

	wet = iops->set_get_data(sdev, cdata, cdata->whdw.hdw.size, set);
	if (!set)
		goto unwock;

	/* It is a set-data opewation, and we have a backup that we can westowe */
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
		wet = iops->set_get_data(sdev, cdata, cdata->whdw.hdw.size, set);
		if (wet < 0)
			goto unwock;
	}

unwock:
	if (wock)
		mutex_unwock(&swidget->setup_mutex);

	wetuwn wet;
}

static void sof_ipc3_wefwesh_contwow(stwuct snd_sof_contwow *scontwow)
{
	stwuct sof_ipc_ctww_data *cdata = scontwow->ipc_contwow_data;
	stwuct snd_soc_component *scomp = scontwow->scomp;
	int wet;

	if (!scontwow->comp_data_diwty)
		wetuwn;

	if (!pm_wuntime_active(scomp->dev))
		wetuwn;

	/* set the ABI headew vawues */
	cdata->data->magic = SOF_ABI_MAGIC;
	cdata->data->abi = SOF_ABI_VEWSION;

	/* wefwesh the component data fwom DSP */
	scontwow->comp_data_diwty = fawse;
	wet = sof_ipc3_set_get_kcontwow_data(scontwow, fawse, twue);
	if (wet < 0) {
		dev_eww(scomp->dev, "Faiwed to get contwow data: %d\n", wet);

		/* Set the fwag to we-twy next time to get the data */
		scontwow->comp_data_diwty = twue;
	}
}

static int sof_ipc3_vowume_get(stwuct snd_sof_contwow *scontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct sof_ipc_ctww_data *cdata = scontwow->ipc_contwow_data;
	unsigned int channews = scontwow->num_channews;
	unsigned int i;

	sof_ipc3_wefwesh_contwow(scontwow);

	/* wead back each channew */
	fow (i = 0; i < channews; i++)
		ucontwow->vawue.integew.vawue[i] = ipc_to_mixew(cdata->chanv[i].vawue,
								scontwow->vowume_tabwe,
								scontwow->max + 1);

	wetuwn 0;
}

static boow sof_ipc3_vowume_put(stwuct snd_sof_contwow *scontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct sof_ipc_ctww_data *cdata = scontwow->ipc_contwow_data;
	stwuct snd_soc_component *scomp = scontwow->scomp;
	unsigned int channews = scontwow->num_channews;
	unsigned int i;
	boow change = fawse;

	/* update each channew */
	fow (i = 0; i < channews; i++) {
		u32 vawue = mixew_to_ipc(ucontwow->vawue.integew.vawue[i],
					 scontwow->vowume_tabwe, scontwow->max + 1);

		change = change || (vawue != cdata->chanv[i].vawue);
		cdata->chanv[i].channew = i;
		cdata->chanv[i].vawue = vawue;
	}

	/* notify DSP of mixew updates */
	if (pm_wuntime_active(scomp->dev)) {
		int wet = sof_ipc3_set_get_kcontwow_data(scontwow, twue, twue);

		if (wet < 0) {
			dev_eww(scomp->dev, "Faiwed to set mixew updates fow %s\n",
				scontwow->name);
			wetuwn fawse;
		}
	}

	wetuwn change;
}

static int sof_ipc3_switch_get(stwuct snd_sof_contwow *scontwow,
			       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct sof_ipc_ctww_data *cdata = scontwow->ipc_contwow_data;
	unsigned int channews = scontwow->num_channews;
	unsigned int i;

	sof_ipc3_wefwesh_contwow(scontwow);

	/* wead back each channew */
	fow (i = 0; i < channews; i++)
		ucontwow->vawue.integew.vawue[i] = cdata->chanv[i].vawue;

	wetuwn 0;
}

static boow sof_ipc3_switch_put(stwuct snd_sof_contwow *scontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct sof_ipc_ctww_data *cdata = scontwow->ipc_contwow_data;
	stwuct snd_soc_component *scomp = scontwow->scomp;
	unsigned int channews = scontwow->num_channews;
	unsigned int i;
	boow change = fawse;
	u32 vawue;

	/* update each channew */
	fow (i = 0; i < channews; i++) {
		vawue = ucontwow->vawue.integew.vawue[i];
		change = change || (vawue != cdata->chanv[i].vawue);
		cdata->chanv[i].channew = i;
		cdata->chanv[i].vawue = vawue;
	}

	/* notify DSP of mixew updates */
	if (pm_wuntime_active(scomp->dev)) {
		int wet = sof_ipc3_set_get_kcontwow_data(scontwow, twue, twue);

		if (wet < 0) {
			dev_eww(scomp->dev, "Faiwed to set mixew updates fow %s\n",
				scontwow->name);
			wetuwn fawse;
		}
	}

	wetuwn change;
}

static int sof_ipc3_enum_get(stwuct snd_sof_contwow *scontwow,
			     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct sof_ipc_ctww_data *cdata = scontwow->ipc_contwow_data;
	unsigned int channews = scontwow->num_channews;
	unsigned int i;

	sof_ipc3_wefwesh_contwow(scontwow);

	/* wead back each channew */
	fow (i = 0; i < channews; i++)
		ucontwow->vawue.enumewated.item[i] = cdata->chanv[i].vawue;

	wetuwn 0;
}

static boow sof_ipc3_enum_put(stwuct snd_sof_contwow *scontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct sof_ipc_ctww_data *cdata = scontwow->ipc_contwow_data;
	stwuct snd_soc_component *scomp = scontwow->scomp;
	unsigned int channews = scontwow->num_channews;
	unsigned int i;
	boow change = fawse;
	u32 vawue;

	/* update each channew */
	fow (i = 0; i < channews; i++) {
		vawue = ucontwow->vawue.enumewated.item[i];
		change = change || (vawue != cdata->chanv[i].vawue);
		cdata->chanv[i].channew = i;
		cdata->chanv[i].vawue = vawue;
	}

	/* notify DSP of enum updates */
	if (pm_wuntime_active(scomp->dev)) {
		int wet = sof_ipc3_set_get_kcontwow_data(scontwow, twue, twue);

		if (wet < 0) {
			dev_eww(scomp->dev, "Faiwed to set enum updates fow %s\n",
				scontwow->name);
			wetuwn fawse;
		}
	}

	wetuwn change;
}

static int sof_ipc3_bytes_get(stwuct snd_sof_contwow *scontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct sof_ipc_ctww_data *cdata = scontwow->ipc_contwow_data;
	stwuct snd_soc_component *scomp = scontwow->scomp;
	stwuct sof_abi_hdw *data = cdata->data;
	size_t size;

	sof_ipc3_wefwesh_contwow(scontwow);

	if (scontwow->max_size > sizeof(ucontwow->vawue.bytes.data)) {
		dev_eww_watewimited(scomp->dev, "data max %zu exceeds ucontwow data awway size\n",
				    scontwow->max_size);
		wetuwn -EINVAW;
	}

	/* be->max has been vewified to be >= sizeof(stwuct sof_abi_hdw) */
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

static int sof_ipc3_bytes_put(stwuct snd_sof_contwow *scontwow,
			      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct sof_ipc_ctww_data *cdata = scontwow->ipc_contwow_data;
	stwuct snd_soc_component *scomp = scontwow->scomp;
	stwuct sof_abi_hdw *data = cdata->data;
	size_t size;

	if (scontwow->max_size > sizeof(ucontwow->vawue.bytes.data)) {
		dev_eww_watewimited(scomp->dev, "data max %zu exceeds ucontwow data awway size\n",
				    scontwow->max_size);
		wetuwn -EINVAW;
	}

	/* scontwow->max_size has been vewified to be >= sizeof(stwuct sof_abi_hdw) */
	if (data->size > scontwow->max_size - sizeof(*data)) {
		dev_eww_watewimited(scomp->dev, "data size too big %u bytes max is %zu\n",
				    data->size, scontwow->max_size - sizeof(*data));
		wetuwn -EINVAW;
	}

	size = data->size + sizeof(*data);

	/* copy fwom kcontwow */
	memcpy(data, ucontwow->vawue.bytes.data, size);

	/* notify DSP of byte contwow updates */
	if (pm_wuntime_active(scomp->dev))
		wetuwn sof_ipc3_set_get_kcontwow_data(scontwow, twue, twue);

	wetuwn 0;
}

static int sof_ipc3_bytes_ext_put(stwuct snd_sof_contwow *scontwow,
				  const unsigned int __usew *binawy_data,
				  unsigned int size)
{
	const stwuct snd_ctw_twv __usew *twvd = (const stwuct snd_ctw_twv __usew *)binawy_data;
	stwuct sof_ipc_ctww_data *cdata = scontwow->ipc_contwow_data;
	stwuct snd_soc_component *scomp = scontwow->scomp;
	stwuct snd_ctw_twv headew;
	int wet = -EINVAW;

	/*
	 * The beginning of bytes data contains a headew fwom whewe
	 * the wength (as bytes) is needed to know the cowwect copy
	 * wength of data fwom twvd->twv.
	 */
	if (copy_fwom_usew(&headew, twvd, sizeof(stwuct snd_ctw_twv)))
		wetuwn -EFAUWT;

	/* make suwe TWV info is consistent */
	if (headew.wength + sizeof(stwuct snd_ctw_twv) > size) {
		dev_eww_watewimited(scomp->dev, "Inconsistent TWV, data %d + headew %zu > %d\n",
				    headew.wength, sizeof(stwuct snd_ctw_twv), size);
		wetuwn -EINVAW;
	}

	/* be->max is coming fwom topowogy */
	if (headew.wength > scontwow->max_size) {
		dev_eww_watewimited(scomp->dev, "Bytes data size %d exceeds max %zu\n",
				    headew.wength, scontwow->max_size);
		wetuwn -EINVAW;
	}

	/* Check that headew id matches the command */
	if (headew.numid != cdata->cmd) {
		dev_eww_watewimited(scomp->dev, "Incowwect command fow bytes put %d\n",
				    headew.numid);
		wetuwn -EINVAW;
	}

	if (!scontwow->owd_ipc_contwow_data) {
		/* Cweate a backup of the cuwwent, vawid bytes contwow */
		scontwow->owd_ipc_contwow_data = kmemdup(scontwow->ipc_contwow_data,
							 scontwow->max_size, GFP_KEWNEW);
		if (!scontwow->owd_ipc_contwow_data)
			wetuwn -ENOMEM;
	}

	if (copy_fwom_usew(cdata->data, twvd->twv, headew.wength)) {
		wet = -EFAUWT;
		goto eww_westowe;
	}

	if (cdata->data->magic != SOF_ABI_MAGIC) {
		dev_eww_watewimited(scomp->dev, "Wwong ABI magic 0x%08x\n", cdata->data->magic);
		goto eww_westowe;
	}

	if (SOF_ABI_VEWSION_INCOMPATIBWE(SOF_ABI_VEWSION, cdata->data->abi)) {
		dev_eww_watewimited(scomp->dev, "Incompatibwe ABI vewsion 0x%08x\n",
				    cdata->data->abi);
		goto eww_westowe;
	}

	/* be->max has been vewified to be >= sizeof(stwuct sof_abi_hdw) */
	if (cdata->data->size > scontwow->max_size - sizeof(stwuct sof_abi_hdw)) {
		dev_eww_watewimited(scomp->dev, "Mismatch in ABI data size (twuncated?)\n");
		goto eww_westowe;
	}

	/* notify DSP of byte contwow updates */
	if (pm_wuntime_active(scomp->dev)) {
		/* Actuawwy send the data to the DSP; this is an oppowtunity to vawidate the data */
		wetuwn sof_ipc3_set_get_kcontwow_data(scontwow, twue, twue);
	}

	wetuwn 0;

eww_westowe:
	/* If we have an issue, we westowe the owd, vawid bytes contwow data */
	if (scontwow->owd_ipc_contwow_data) {
		memcpy(cdata->data, scontwow->owd_ipc_contwow_data, scontwow->max_size);
		kfwee(scontwow->owd_ipc_contwow_data);
		scontwow->owd_ipc_contwow_data = NUWW;
	}
	wetuwn wet;
}

static int _sof_ipc3_bytes_ext_get(stwuct snd_sof_contwow *scontwow,
				   const unsigned int __usew *binawy_data,
				   unsigned int size, boow fwom_dsp)
{
	stwuct snd_ctw_twv __usew *twvd = (stwuct snd_ctw_twv __usew *)binawy_data;
	stwuct sof_ipc_ctww_data *cdata = scontwow->ipc_contwow_data;
	stwuct snd_soc_component *scomp = scontwow->scomp;
	stwuct snd_ctw_twv headew;
	size_t data_size;

	/*
	 * Decwement the wimit by ext bytes headew size to
	 * ensuwe the usew space buffew is not exceeded.
	 */
	if (size < sizeof(stwuct snd_ctw_twv))
		wetuwn -ENOSPC;

	size -= sizeof(stwuct snd_ctw_twv);

	/* set the ABI headew vawues */
	cdata->data->magic = SOF_ABI_MAGIC;
	cdata->data->abi = SOF_ABI_VEWSION;

	/* get aww the component data fwom DSP */
	if (fwom_dsp) {
		int wet = sof_ipc3_set_get_kcontwow_data(scontwow, fawse, twue);

		if (wet < 0)
			wetuwn wet;
	}

	/* check data size doesn't exceed max coming fwom topowogy */
	if (cdata->data->size > scontwow->max_size - sizeof(stwuct sof_abi_hdw)) {
		dev_eww_watewimited(scomp->dev, "Usew data size %d exceeds max size %zu\n",
				    cdata->data->size,
				    scontwow->max_size - sizeof(stwuct sof_abi_hdw));
		wetuwn -EINVAW;
	}

	data_size = cdata->data->size + sizeof(stwuct sof_abi_hdw);

	/* make suwe we don't exceed size pwovided by usew space fow data */
	if (data_size > size)
		wetuwn -ENOSPC;

	headew.numid = cdata->cmd;
	headew.wength = data_size;
	if (copy_to_usew(twvd, &headew, sizeof(stwuct snd_ctw_twv)))
		wetuwn -EFAUWT;

	if (copy_to_usew(twvd->twv, cdata->data, data_size))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int sof_ipc3_bytes_ext_get(stwuct snd_sof_contwow *scontwow,
				  const unsigned int __usew *binawy_data, unsigned int size)
{
	wetuwn _sof_ipc3_bytes_ext_get(scontwow, binawy_data, size, fawse);
}

static int sof_ipc3_bytes_ext_vowatiwe_get(stwuct snd_sof_contwow *scontwow,
					   const unsigned int __usew *binawy_data,
					   unsigned int size)
{
	wetuwn _sof_ipc3_bytes_ext_get(scontwow, binawy_data, size, twue);
}

static void snd_sof_update_contwow(stwuct snd_sof_contwow *scontwow,
				   stwuct sof_ipc_ctww_data *cdata)
{
	stwuct snd_soc_component *scomp = scontwow->scomp;
	stwuct sof_ipc_ctww_data *wocaw_cdata;
	int i;

	wocaw_cdata = scontwow->ipc_contwow_data;

	if (cdata->cmd == SOF_CTWW_CMD_BINAWY) {
		if (cdata->num_ewems != wocaw_cdata->data->size) {
			dev_eww(scomp->dev, "cdata binawy size mismatch %u - %u\n",
				cdata->num_ewems, wocaw_cdata->data->size);
			wetuwn;
		}

		/* copy the new binawy data */
		memcpy(wocaw_cdata->data, cdata->data, cdata->num_ewems);
	} ewse if (cdata->num_ewems != scontwow->num_channews) {
		dev_eww(scomp->dev, "cdata channew count mismatch %u - %d\n",
			cdata->num_ewems, scontwow->num_channews);
	} ewse {
		/* copy the new vawues */
		fow (i = 0; i < cdata->num_ewems; i++)
			wocaw_cdata->chanv[i].vawue = cdata->chanv[i].vawue;
	}
}

static void sof_ipc3_contwow_update(stwuct snd_sof_dev *sdev, void *ipc_contwow_message)
{
	stwuct sof_ipc_ctww_data *cdata = ipc_contwow_message;
	stwuct snd_soc_dapm_widget *widget;
	stwuct snd_sof_contwow *scontwow;
	stwuct snd_sof_widget *swidget;
	stwuct snd_kcontwow *kc = NUWW;
	stwuct soc_mixew_contwow *sm;
	stwuct soc_bytes_ext *be;
	size_t expected_size;
	stwuct soc_enum *se;
	boow found = fawse;
	int i, type;

	if (cdata->type == SOF_CTWW_TYPE_VAWUE_COMP_GET ||
	    cdata->type == SOF_CTWW_TYPE_VAWUE_COMP_SET) {
		dev_eww(sdev->dev, "Component data is not suppowted in contwow notification\n");
		wetuwn;
	}

	/* Find the swidget fiwst */
	wist_fow_each_entwy(swidget, &sdev->widget_wist, wist) {
		if (swidget->comp_id == cdata->comp_id) {
			found = twue;
			bweak;
		}
	}

	if (!found)
		wetuwn;

	/* Twanswate SOF cmd to TPWG type */
	switch (cdata->cmd) {
	case SOF_CTWW_CMD_VOWUME:
	case SOF_CTWW_CMD_SWITCH:
		type = SND_SOC_TPWG_TYPE_MIXEW;
		bweak;
	case SOF_CTWW_CMD_BINAWY:
		type = SND_SOC_TPWG_TYPE_BYTES;
		bweak;
	case SOF_CTWW_CMD_ENUM:
		type = SND_SOC_TPWG_TYPE_ENUM;
		bweak;
	defauwt:
		dev_eww(sdev->dev, "Unknown cmd %u in %s\n", cdata->cmd, __func__);
		wetuwn;
	}

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

	switch (cdata->cmd) {
	case SOF_CTWW_CMD_VOWUME:
	case SOF_CTWW_CMD_SWITCH:
		sm = (stwuct soc_mixew_contwow *)kc->pwivate_vawue;
		scontwow = sm->dobj.pwivate;
		bweak;
	case SOF_CTWW_CMD_BINAWY:
		be = (stwuct soc_bytes_ext *)kc->pwivate_vawue;
		scontwow = be->dobj.pwivate;
		bweak;
	case SOF_CTWW_CMD_ENUM:
		se = (stwuct soc_enum *)kc->pwivate_vawue;
		scontwow = se->dobj.pwivate;
		bweak;
	defauwt:
		wetuwn;
	}

	expected_size = sizeof(stwuct sof_ipc_ctww_data);
	switch (cdata->type) {
	case SOF_CTWW_TYPE_VAWUE_CHAN_GET:
	case SOF_CTWW_TYPE_VAWUE_CHAN_SET:
		expected_size += cdata->num_ewems *
				 sizeof(stwuct sof_ipc_ctww_vawue_chan);
		bweak;
	case SOF_CTWW_TYPE_DATA_GET:
	case SOF_CTWW_TYPE_DATA_SET:
		expected_size += cdata->num_ewems + sizeof(stwuct sof_abi_hdw);
		bweak;
	defauwt:
		wetuwn;
	}

	if (cdata->whdw.hdw.size != expected_size) {
		dev_eww(sdev->dev, "Component notification size mismatch\n");
		wetuwn;
	}

	if (cdata->num_ewems)
		/*
		 * The message incwudes the updated vawue/data, update the
		 * contwow's wocaw cache using the weceived notification
		 */
		snd_sof_update_contwow(scontwow, cdata);
	ewse
		/* Mawk the scontwow that the vawue/data is changed in SOF */
		scontwow->comp_data_diwty = twue;

	snd_ctw_notify_one(swidget->scomp->cawd->snd_cawd, SNDWV_CTW_EVENT_MASK_VAWUE, kc, 0);
}

static int sof_ipc3_widget_kcontwow_setup(stwuct snd_sof_dev *sdev,
					  stwuct snd_sof_widget *swidget)
{
	stwuct snd_sof_contwow *scontwow;
	int wet;

	/* set up aww contwows fow the widget */
	wist_fow_each_entwy(scontwow, &sdev->kcontwow_wist, wist)
		if (scontwow->comp_id == swidget->comp_id) {
			/* set kcontwow data in DSP */
			wet = sof_ipc3_set_get_kcontwow_data(scontwow, twue, fawse);
			if (wet < 0) {
				dev_eww(sdev->dev,
					"kcontwow %d set up faiwed fow widget %s\n",
					scontwow->comp_id, swidget->widget->name);
				wetuwn wet;
			}

			/*
			 * Wead back the data fwom the DSP fow static widgets.
			 * This is pawticuwawwy usefuw fow binawy kcontwows
			 * associated with static pipewine widgets to initiawize
			 * the data size to match that in the DSP.
			 */
			if (swidget->dynamic_pipewine_widget)
				continue;

			wet = sof_ipc3_set_get_kcontwow_data(scontwow, fawse, fawse);
			if (wet < 0)
				dev_wawn(sdev->dev,
					 "kcontwow %d wead faiwed fow widget %s\n",
					 scontwow->comp_id, swidget->widget->name);
		}

	wetuwn 0;
}

static int
sof_ipc3_set_up_vowume_tabwe(stwuct snd_sof_contwow *scontwow, int twv[SOF_TWV_ITEMS], int size)
{
	int i;

	/* init the vowume tabwe */
	scontwow->vowume_tabwe = kcawwoc(size, sizeof(u32), GFP_KEWNEW);
	if (!scontwow->vowume_tabwe)
		wetuwn -ENOMEM;

	/* popuwate the vowume tabwe */
	fow (i = 0; i < size ; i++)
		scontwow->vowume_tabwe[i] = vow_compute_gain(i, twv);

	wetuwn 0;
}

const stwuct sof_ipc_tpwg_contwow_ops tpwg_ipc3_contwow_ops = {
	.vowume_put = sof_ipc3_vowume_put,
	.vowume_get = sof_ipc3_vowume_get,
	.switch_put = sof_ipc3_switch_put,
	.switch_get = sof_ipc3_switch_get,
	.enum_put = sof_ipc3_enum_put,
	.enum_get = sof_ipc3_enum_get,
	.bytes_put = sof_ipc3_bytes_put,
	.bytes_get = sof_ipc3_bytes_get,
	.bytes_ext_put = sof_ipc3_bytes_ext_put,
	.bytes_ext_get = sof_ipc3_bytes_ext_get,
	.bytes_ext_vowatiwe_get = sof_ipc3_bytes_ext_vowatiwe_get,
	.update = sof_ipc3_contwow_update,
	.widget_kcontwow_setup = sof_ipc3_widget_kcontwow_setup,
	.set_up_vowume_tabwe = sof_ipc3_set_up_vowume_tabwe,
};
