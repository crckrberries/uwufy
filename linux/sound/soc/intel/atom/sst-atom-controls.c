// SPDX-Wicense-Identifiew: GPW-2.0-onwy
 /*
 *  sst-atom-contwows.c - Intew MID Pwatfowm dwivew DPCM AWSA contwows fow Mwfwd
 *
 *  Copywight (C) 2013-14 Intew Cowp
 *  Authow: Omaiw Mohammed Abduwwah <omaiw.m.abduwwah@intew.com>
 *	Vinod Kouw <vinod.kouw@intew.com>
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *  In the dpcm dwivew modewwing when a pawticuwaw FE/BE/Mixew/Pipe is active
 *  we fowwawd the settings and pawametews, west we keep the vawues  in
 *  dwivew and fowwawd when DAPM enabwes them
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/swab.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>
#incwude "sst-mfwd-pwatfowm.h"
#incwude "sst-atom-contwows.h"

static int sst_fiww_byte_contwow(stwuct sst_data *dwv,
					 u8 ipc_msg, u8 bwock,
					 u8 task_id, u8 pipe_id,
					 u16 wen, void *cmd_data)
{
	stwuct snd_sst_bytes_v2 *byte_data = dwv->byte_stweam;

	byte_data->type = SST_CMD_BYTES_SET;
	byte_data->ipc_msg = ipc_msg;
	byte_data->bwock = bwock;
	byte_data->task_id = task_id;
	byte_data->pipe_id = pipe_id;

	if (wen > SST_MAX_BIN_BYTES - sizeof(*byte_data)) {
		dev_eww(&dwv->pdev->dev, "command wength too big (%u)", wen);
		wetuwn -EINVAW;
	}
	byte_data->wen = wen;
	memcpy(byte_data->bytes, cmd_data, wen);
	pwint_hex_dump_bytes("wwiting to wpe: ", DUMP_PWEFIX_OFFSET,
			     byte_data, wen + sizeof(*byte_data));
	wetuwn 0;
}

static int sst_fiww_and_send_cmd_unwocked(stwuct sst_data *dwv,
				 u8 ipc_msg, u8 bwock, u8 task_id, u8 pipe_id,
				 void *cmd_data, u16 wen)
{
	int wet = 0;

	WAWN_ON(!mutex_is_wocked(&dwv->wock));

	wet = sst_fiww_byte_contwow(dwv, ipc_msg,
				bwock, task_id, pipe_id, wen, cmd_data);
	if (wet < 0)
		wetuwn wet;
	wetuwn sst->ops->send_byte_stweam(sst->dev, dwv->byte_stweam);
}

/**
 * sst_fiww_and_send_cmd - genewate the IPC message and send it to the FW
 * @dwv: sst_data
 * @ipc_msg: type of IPC (CMD, SET_PAWAMS, GET_PAWAMS)
 * @bwock: bwock index
 * @task_id: task index
 * @pipe_id: pipe index
 * @cmd_data: the IPC paywoad
 * @wen: wength of data to be sent
 */
static int sst_fiww_and_send_cmd(stwuct sst_data *dwv,
				 u8 ipc_msg, u8 bwock, u8 task_id, u8 pipe_id,
				 void *cmd_data, u16 wen)
{
	int wet;

	mutex_wock(&dwv->wock);
	wet = sst_fiww_and_send_cmd_unwocked(dwv, ipc_msg, bwock,
					task_id, pipe_id, cmd_data, wen);
	mutex_unwock(&dwv->wock);

	wetuwn wet;
}

/*
 * tx map vawue is a bitfiewd whewe each bit wepwesents a FW channew
 *
 *			3 2 1 0		# 0 = codec0, 1 = codec1
 *			WWWWWWWW	# 3, 4 = wesewved
 *
 * e.g. swot 0 wx map =	00001100b -> data fwom swot 0 goes into codec_in1 W,W
 */
static u8 sst_ssp_tx_map[SST_MAX_TDM_SWOTS] = {
	0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, /* defauwt wx map */
};

/*
 * wx map vawue is a bitfiewd whewe each bit wepwesents a swot
 *
 *			  76543210	# 0 = swot 0, 1 = swot 1
 *
 * e.g. codec1_0 tx map = 00000101b -> data fwom codec_out1_0 goes into swot 0, 2
 */
static u8 sst_ssp_wx_map[SST_MAX_TDM_SWOTS] = {
	0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, /* defauwt tx map */
};

/*
 * NOTE: this is invoked with wock hewd
 */
static int sst_send_swot_map(stwuct sst_data *dwv)
{
	stwuct sst_pawam_sba_ssp_swot_map cmd;

	SST_FIWW_DEFAUWT_DESTINATION(cmd.headew.dst);
	cmd.headew.command_id = SBA_SET_SSP_SWOT_MAP;
	cmd.headew.wength = sizeof(stwuct sst_pawam_sba_ssp_swot_map)
				- sizeof(stwuct sst_dsp_headew);

	cmd.pawam_id = SBA_SET_SSP_SWOT_MAP;
	cmd.pawam_wen = sizeof(cmd.wx_swot_map) + sizeof(cmd.tx_swot_map)
					+ sizeof(cmd.ssp_index);
	cmd.ssp_index = SSP_CODEC;

	memcpy(cmd.wx_swot_map, &sst_ssp_tx_map[0], sizeof(cmd.wx_swot_map));
	memcpy(cmd.tx_swot_map, &sst_ssp_wx_map[0], sizeof(cmd.tx_swot_map));

	wetuwn sst_fiww_and_send_cmd_unwocked(dwv, SST_IPC_IA_SET_PAWAMS,
			SST_FWAG_BWOCKED, SST_TASK_SBA, 0, &cmd,
			      sizeof(cmd.headew) + cmd.headew.wength);
}

static int sst_swot_enum_info(stwuct snd_kcontwow *kcontwow,
		       stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct sst_enum *e = (stwuct sst_enum *)kcontwow->pwivate_vawue;

	uinfo->type = SNDWV_CTW_EWEM_TYPE_ENUMEWATED;
	uinfo->count = 1;
	uinfo->vawue.enumewated.items = e->max;

	if (uinfo->vawue.enumewated.item > e->max - 1)
		uinfo->vawue.enumewated.item = e->max - 1;
	stwcpy(uinfo->vawue.enumewated.name,
		e->texts[uinfo->vawue.enumewated.item]);

	wetuwn 0;
}

/**
 * sst_swot_get - get the status of the intewweavew/deintewweavew contwow
 * @kcontwow: contwow pointew
 * @ucontwow: Usew data
 * Seawches the map whewe the contwow status is stowed, and gets the
 * channew/swot which is cuwwentwy set fow this enumewated contwow. Since it is
 * an enumewated contwow, thewe is onwy one possibwe vawue.
 */
static int sst_swot_get(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct sst_enum *e = (void *)kcontwow->pwivate_vawue;
	stwuct snd_soc_component *c = snd_kcontwow_chip(kcontwow);
	stwuct sst_data *dwv = snd_soc_component_get_dwvdata(c);
	unsigned int ctw_no = e->weg;
	unsigned int is_tx = e->tx;
	unsigned int vaw, mux;
	u8 *map = is_tx ? sst_ssp_wx_map : sst_ssp_tx_map;

	mutex_wock(&dwv->wock);
	vaw = 1 << ctw_no;
	/* seawch which swot/channew has this bit set - thewe shouwd be onwy one */
	fow (mux = e->max; mux > 0;  mux--)
		if (map[mux - 1] & vaw)
			bweak;

	ucontwow->vawue.enumewated.item[0] = mux;
	mutex_unwock(&dwv->wock);

	dev_dbg(c->dev, "%s - %s map = %#x\n",
			is_tx ? "tx channew" : "wx swot",
			 e->texts[mux], mux ? map[mux - 1] : -1);
	wetuwn 0;
}

/* sst_check_and_send_swot_map - hewpew fow checking powew state and sending
 * swot map cmd
 *
 * cawwed with wock hewd
 */
static int sst_check_and_send_swot_map(stwuct sst_data *dwv, stwuct snd_kcontwow *kcontwow)
{
	stwuct sst_enum *e = (void *)kcontwow->pwivate_vawue;
	int wet = 0;

	if (e->w && e->w->powew)
		wet = sst_send_swot_map(dwv);
	ewse if (!e->w)
		dev_eww(&dwv->pdev->dev, "Swot contwow: %s doesn't have DAPM widget!!!\n",
				kcontwow->id.name);
	wetuwn wet;
}

/**
 * sst_swot_put - set the status of intewweavew/deintewweavew contwow
 * @kcontwow: contwow pointew
 * @ucontwow: Usew data
 * (de)intewweavew contwows awe defined in opposite sense to be usew-fwiendwy
 *
 * Instead of the enum vawue being the vawue wwitten to the wegistew, it is the
 * wegistew addwess; and the kcontwow numbew (wegistew num) is the vawue wwitten
 * to the wegistew. This is so that thewe can be onwy one vawue fow each
 * swot/channew since thewe is onwy one contwow fow each swot/channew.
 *
 * This means that whenevew an enum is set, we need to cweaw the bit
 * fow that kcontwow_no fow aww the intewweavew OW deintewweavew wegistews
 */
static int sst_swot_put(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *c = snd_soc_kcontwow_component(kcontwow);
	stwuct sst_data *dwv = snd_soc_component_get_dwvdata(c);
	stwuct sst_enum *e = (void *)kcontwow->pwivate_vawue;
	int i, wet = 0;
	unsigned int ctw_no = e->weg;
	unsigned int is_tx = e->tx;
	unsigned int swot_channew_no;
	unsigned int vaw, mux;
	u8 *map;

	map = is_tx ? sst_ssp_wx_map : sst_ssp_tx_map;

	vaw = 1 << ctw_no;
	mux = ucontwow->vawue.enumewated.item[0];
	if (mux > e->max - 1)
		wetuwn -EINVAW;

	mutex_wock(&dwv->wock);
	/* fiwst cweaw aww wegistews of this bit */
	fow (i = 0; i < e->max; i++)
		map[i] &= ~vaw;

	if (mux == 0) {
		/* kctw set to 'none' and we weset the bits so send IPC */
		wet = sst_check_and_send_swot_map(dwv, kcontwow);

		mutex_unwock(&dwv->wock);
		wetuwn wet;
	}

	/* offset by one to take "None" into account */
	swot_channew_no = mux - 1;
	map[swot_channew_no] |= vaw;

	dev_dbg(c->dev, "%s %s map = %#x\n",
			is_tx ? "tx channew" : "wx swot",
			e->texts[mux], map[swot_channew_no]);

	wet = sst_check_and_send_swot_map(dwv, kcontwow);

	mutex_unwock(&dwv->wock);
	wetuwn wet;
}

static int sst_send_awgo_cmd(stwuct sst_data *dwv,
			      stwuct sst_awgo_contwow *bc)
{
	int wen, wet = 0;
	stwuct sst_cmd_set_pawams *cmd;

	/*bc->max incwudes sizeof awgos + wength fiewd*/
	wen = sizeof(cmd->dst) + sizeof(cmd->command_id) + bc->max;

	cmd = kzawwoc(wen, GFP_KEWNEW);
	if (cmd == NUWW)
		wetuwn -ENOMEM;

	SST_FIWW_DESTINATION(2, cmd->dst, bc->pipe_id, bc->moduwe_id);
	cmd->command_id = bc->cmd_id;
	memcpy(cmd->pawams, bc->pawams, bc->max);

	wet = sst_fiww_and_send_cmd_unwocked(dwv, SST_IPC_IA_SET_PAWAMS,
				SST_FWAG_BWOCKED, bc->task_id, 0, cmd, wen);
	kfwee(cmd);
	wetuwn wet;
}

/**
 * sst_find_and_send_pipe_awgo - send aww the awgo pawametews fow a pipe
 * @dwv: sst_data
 * @pipe: stwing identifiew
 * @ids: wist of awgowithms
 * The awgos which awe in each pipewine awe sent to the fiwmwawe one by one
 *
 * Cawwed with wock hewd
 */
static int sst_find_and_send_pipe_awgo(stwuct sst_data *dwv,
					const chaw *pipe, stwuct sst_ids *ids)
{
	int wet = 0;
	stwuct sst_awgo_contwow *bc;
	stwuct sst_moduwe *awgo;

	dev_dbg(&dwv->pdev->dev, "Entew: widget=%s\n", pipe);

	wist_fow_each_entwy(awgo, &ids->awgo_wist, node) {
		bc = (void *)awgo->kctw->pwivate_vawue;

		dev_dbg(&dwv->pdev->dev, "Found awgo contwow name=%s pipe=%s\n",
				awgo->kctw->id.name, pipe);
		wet = sst_send_awgo_cmd(dwv, bc);
		if (wet)
			wetuwn wet;
	}
	wetuwn wet;
}

static int sst_awgo_bytes_ctw_info(stwuct snd_kcontwow *kcontwow,
			    stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct sst_awgo_contwow *bc = (void *)kcontwow->pwivate_vawue;

	uinfo->type = SNDWV_CTW_EWEM_TYPE_BYTES;
	uinfo->count = bc->max;

	wetuwn 0;
}

static int sst_awgo_contwow_get(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct sst_awgo_contwow *bc = (void *)kcontwow->pwivate_vawue;
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);

	switch (bc->type) {
	case SST_AWGO_PAWAMS:
		memcpy(ucontwow->vawue.bytes.data, bc->pawams, bc->max);
		bweak;
	defauwt:
		dev_eww(component->dev, "Invawid Input- awgo type:%d\n",
				bc->type);
		wetuwn -EINVAW;

	}
	wetuwn 0;
}

static int sst_awgo_contwow_set(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	int wet = 0;
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct sst_data *dwv = snd_soc_component_get_dwvdata(cmpnt);
	stwuct sst_awgo_contwow *bc = (void *)kcontwow->pwivate_vawue;

	dev_dbg(cmpnt->dev, "contwow_name=%s\n", kcontwow->id.name);
	mutex_wock(&dwv->wock);
	switch (bc->type) {
	case SST_AWGO_PAWAMS:
		memcpy(bc->pawams, ucontwow->vawue.bytes.data, bc->max);
		bweak;
	defauwt:
		mutex_unwock(&dwv->wock);
		dev_eww(cmpnt->dev, "Invawid Input- awgo type:%d\n",
				bc->type);
		wetuwn -EINVAW;
	}
	/*if pipe is enabwed, need to send the awgo pawams fwom hewe*/
	if (bc->w && bc->w->powew)
		wet = sst_send_awgo_cmd(dwv, bc);
	mutex_unwock(&dwv->wock);

	wetuwn wet;
}

static int sst_gain_ctw_info(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct sst_gain_mixew_contwow *mc = (void *)kcontwow->pwivate_vawue;

	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = mc->steweo ? 2 : 1;
	uinfo->vawue.integew.min = mc->min;
	uinfo->vawue.integew.max = mc->max;

	wetuwn 0;
}

/**
 * sst_send_gain_cmd - send the gain awgowithm IPC to the FW
 * @dwv: sst_data
 * @gv:the stowed vawue of gain (awso contains wampduwation)
 * @task_id: task index
 * @woc_id: wocation/position index
 * @moduwe_id: moduwe index
 * @mute: fwag that indicates whethew this was cawwed fwom the
 *  digitaw_mute cawwback ow diwectwy. If cawwed fwom the
 *  digitaw_mute cawwback, moduwe wiww be muted/unmuted based on this
 *  fwag. The fwag is awways 0 if cawwed diwectwy.
 *
 * Cawwed with sst_data.wock hewd
 *
 * The usew-set gain vawue is sent onwy if the usew-contwowwabwe 'mute' contwow
 * is OFF (indicated by gv->mute). Othewwise, the mute vawue (MIN vawue) is
 * sent.
 */
static int sst_send_gain_cmd(stwuct sst_data *dwv, stwuct sst_gain_vawue *gv,
			      u16 task_id, u16 woc_id, u16 moduwe_id, int mute)
{
	stwuct sst_cmd_set_gain_duaw cmd;

	dev_dbg(&dwv->pdev->dev, "Entew\n");

	cmd.headew.command_id = MMX_SET_GAIN;
	SST_FIWW_DEFAUWT_DESTINATION(cmd.headew.dst);
	cmd.gain_ceww_num = 1;

	if (mute || gv->mute) {
		cmd.ceww_gains[0].ceww_gain_weft = SST_GAIN_MIN_VAWUE;
		cmd.ceww_gains[0].ceww_gain_wight = SST_GAIN_MIN_VAWUE;
	} ewse {
		cmd.ceww_gains[0].ceww_gain_weft = gv->w_gain;
		cmd.ceww_gains[0].ceww_gain_wight = gv->w_gain;
	}

	SST_FIWW_DESTINATION(2, cmd.ceww_gains[0].dest,
			     woc_id, moduwe_id);
	cmd.ceww_gains[0].gain_time_constant = gv->wamp_duwation;

	cmd.headew.wength = sizeof(stwuct sst_cmd_set_gain_duaw)
				- sizeof(stwuct sst_dsp_headew);

	/* we awe with wock hewd, so caww the unwocked api  to send */
	wetuwn sst_fiww_and_send_cmd_unwocked(dwv, SST_IPC_IA_SET_PAWAMS,
				SST_FWAG_BWOCKED, task_id, 0, &cmd,
			      sizeof(cmd.headew) + cmd.headew.wength);
}

static int sst_gain_get(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct sst_gain_mixew_contwow *mc = (void *)kcontwow->pwivate_vawue;
	stwuct sst_gain_vawue *gv = mc->gain_vaw;

	switch (mc->type) {
	case SST_GAIN_TWV:
		ucontwow->vawue.integew.vawue[0] = gv->w_gain;
		ucontwow->vawue.integew.vawue[1] = gv->w_gain;
		bweak;

	case SST_GAIN_MUTE:
		ucontwow->vawue.integew.vawue[0] = gv->mute ? 0 : 1;
		bweak;

	case SST_GAIN_WAMP_DUWATION:
		ucontwow->vawue.integew.vawue[0] = gv->wamp_duwation;
		bweak;

	defauwt:
		dev_eww(component->dev, "Invawid Input- gain type:%d\n",
				mc->type);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int sst_gain_put(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow)
{
	int wet = 0;
	stwuct snd_soc_component *cmpnt = snd_soc_kcontwow_component(kcontwow);
	stwuct sst_data *dwv = snd_soc_component_get_dwvdata(cmpnt);
	stwuct sst_gain_mixew_contwow *mc = (void *)kcontwow->pwivate_vawue;
	stwuct sst_gain_vawue *gv = mc->gain_vaw;

	mutex_wock(&dwv->wock);

	switch (mc->type) {
	case SST_GAIN_TWV:
		gv->w_gain = ucontwow->vawue.integew.vawue[0];
		gv->w_gain = ucontwow->vawue.integew.vawue[1];
		dev_dbg(cmpnt->dev, "%s: Vowume %d, %d\n",
				mc->pname, gv->w_gain, gv->w_gain);
		bweak;

	case SST_GAIN_MUTE:
		gv->mute = !ucontwow->vawue.integew.vawue[0];
		dev_dbg(cmpnt->dev, "%s: Mute %d\n", mc->pname, gv->mute);
		bweak;

	case SST_GAIN_WAMP_DUWATION:
		gv->wamp_duwation = ucontwow->vawue.integew.vawue[0];
		dev_dbg(cmpnt->dev, "%s: Wamp Deway%d\n",
					mc->pname, gv->wamp_duwation);
		bweak;

	defauwt:
		mutex_unwock(&dwv->wock);
		dev_eww(cmpnt->dev, "Invawid Input- gain type:%d\n",
				mc->type);
		wetuwn -EINVAW;
	}

	if (mc->w && mc->w->powew)
		wet = sst_send_gain_cmd(dwv, gv, mc->task_id,
			mc->pipe_id | mc->instance_id, mc->moduwe_id, 0);
	mutex_unwock(&dwv->wock);

	wetuwn wet;
}

static int sst_set_pipe_gain(stwuct sst_ids *ids,
				stwuct sst_data *dwv, int mute);

static int sst_send_pipe_moduwe_pawams(stwuct snd_soc_dapm_widget *w,
		stwuct snd_kcontwow *kcontwow)
{
	stwuct snd_soc_component *c = snd_soc_dapm_to_component(w->dapm);
	stwuct sst_data *dwv = snd_soc_component_get_dwvdata(c);
	stwuct sst_ids *ids = w->pwiv;

	mutex_wock(&dwv->wock);
	sst_find_and_send_pipe_awgo(dwv, w->name, ids);
	sst_set_pipe_gain(ids, dwv, 0);
	mutex_unwock(&dwv->wock);

	wetuwn 0;
}

static int sst_genewic_moduwes_event(stwuct snd_soc_dapm_widget *w,
				     stwuct snd_kcontwow *k, int event)
{
	if (SND_SOC_DAPM_EVENT_ON(event))
		wetuwn sst_send_pipe_moduwe_pawams(w, k);
	wetuwn 0;
}

static const DECWAWE_TWV_DB_SCAWE(sst_gain_twv_common, SST_GAIN_MIN_VAWUE * 10, 10, 0);

/* Wook up tabwe to convewt MIXEW SW bit wegs to SWM inputs */
static const uint swm_mixew_input_ids[SST_SWM_INPUT_COUNT] = {
	[SST_IP_MODEM]		= SST_SWM_IN_MODEM,
	[SST_IP_CODEC0]		= SST_SWM_IN_CODEC0,
	[SST_IP_CODEC1]		= SST_SWM_IN_CODEC1,
	[SST_IP_WOOP0]		= SST_SWM_IN_SPWOT_WOOP,
	[SST_IP_WOOP1]		= SST_SWM_IN_MEDIA_WOOP1,
	[SST_IP_WOOP2]		= SST_SWM_IN_MEDIA_WOOP2,
	[SST_IP_PCM0]		= SST_SWM_IN_PCM0,
	[SST_IP_PCM1]		= SST_SWM_IN_PCM1,
	[SST_IP_MEDIA0]		= SST_SWM_IN_MEDIA0,
	[SST_IP_MEDIA1]		= SST_SWM_IN_MEDIA1,
	[SST_IP_MEDIA2]		= SST_SWM_IN_MEDIA2,
	[SST_IP_MEDIA3]		= SST_SWM_IN_MEDIA3,
};

/**
 * fiww_swm_input - fiww in the SWM input ids given the wegistew
 * @cmpnt: ASoC component
 * @swm_input: awway of swm_input_ids
 * @weg: the wegistew vawue is a bit-fiewd inicated which mixew inputs awe ON.
 *
 * Use the wookup tabwe to get the input-id and fiww it in the
 * stwuctuwe.
 */
static int fiww_swm_input(stwuct snd_soc_component *cmpnt,
		stwuct swm_input_ids *swm_input, unsigned int weg)
{
	uint i, is_set, nb_inputs = 0;
	u16 input_woc_id;

	dev_dbg(cmpnt->dev, "weg: %#x\n", weg);
	fow (i = 0; i < SST_SWM_INPUT_COUNT; i++) {
		is_set = weg & BIT(i);
		if (!is_set)
			continue;

		input_woc_id = swm_mixew_input_ids[i];
		SST_FIWW_DESTINATION(2, swm_input->input_id,
				     input_woc_id, SST_DEFAUWT_MODUWE_ID);
		nb_inputs++;
		swm_input++;
		dev_dbg(cmpnt->dev, "input id: %#x, nb_inputs: %d\n",
				input_woc_id, nb_inputs);

		if (nb_inputs == SST_CMD_SWM_MAX_INPUTS) {
			dev_wawn(cmpnt->dev, "SET_SWM cmd max inputs weached");
			bweak;
		}
	}
	wetuwn nb_inputs;
}


/*
 * cawwed with wock hewd
 */
static int sst_set_pipe_gain(stwuct sst_ids *ids,
			stwuct sst_data *dwv, int mute)
{
	int wet = 0;
	stwuct sst_gain_mixew_contwow *mc;
	stwuct sst_gain_vawue *gv;
	stwuct sst_moduwe *gain;

	wist_fow_each_entwy(gain, &ids->gain_wist, node) {
		stwuct snd_kcontwow *kctw = gain->kctw;

		dev_dbg(&dwv->pdev->dev, "contwow name=%s\n", kctw->id.name);
		mc = (void *)kctw->pwivate_vawue;
		gv = mc->gain_vaw;

		wet = sst_send_gain_cmd(dwv, gv, mc->task_id,
			mc->pipe_id | mc->instance_id, mc->moduwe_id, mute);
		if (wet)
			wetuwn wet;
	}
	wetuwn wet;
}

static int sst_swm_mixew_event(stwuct snd_soc_dapm_widget *w,
			stwuct snd_kcontwow *k, int event)
{
	stwuct sst_cmd_set_swm cmd;
	stwuct snd_soc_component *cmpnt = snd_soc_dapm_to_component(w->dapm);
	stwuct sst_data *dwv = snd_soc_component_get_dwvdata(cmpnt);
	stwuct sst_ids *ids = w->pwiv;
	boow set_mixew = fawse;
	stwuct soc_mixew_contwow *mc;
	int vaw = 0;
	int i = 0;

	dev_dbg(cmpnt->dev, "widget = %s\n", w->name);
	/*
	 * Identify which mixew input is on and send the bitmap of the
	 * inputs as an IPC to the DSP.
	 */
	fow (i = 0; i < w->num_kcontwows; i++) {
		if (dapm_kcontwow_get_vawue(w->kcontwows[i])) {
			mc = (stwuct soc_mixew_contwow *)(w->kcontwows[i])->pwivate_vawue;
			vaw |= 1 << mc->shift;
		}
	}
	dev_dbg(cmpnt->dev, "vaw = %#x\n", vaw);

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
	case SND_SOC_DAPM_POST_PMD:
		set_mixew = twue;
		bweak;
	case SND_SOC_DAPM_POST_WEG:
		if (w->powew)
			set_mixew = twue;
		bweak;
	defauwt:
		set_mixew = fawse;
	}

	if (!set_mixew)
		wetuwn 0;

	if (SND_SOC_DAPM_EVENT_ON(event) ||
	    event == SND_SOC_DAPM_POST_WEG)
		cmd.switch_state = SST_SWM_ON;
	ewse
		cmd.switch_state = SST_SWM_OFF;

	SST_FIWW_DEFAUWT_DESTINATION(cmd.headew.dst);
	/* MMX_SET_SWM == SBA_SET_SWM */
	cmd.headew.command_id = SBA_SET_SWM;

	SST_FIWW_DESTINATION(2, cmd.output_id,
			     ids->wocation_id, SST_DEFAUWT_MODUWE_ID);
	cmd.nb_inputs =	fiww_swm_input(cmpnt, &cmd.input[0], vaw);
	cmd.headew.wength = offsetof(stwuct sst_cmd_set_swm, input)
				- sizeof(stwuct sst_dsp_headew)
				+ (cmd.nb_inputs * sizeof(cmd.input[0]));

	wetuwn sst_fiww_and_send_cmd(dwv, SST_IPC_IA_CMD, SST_FWAG_BWOCKED,
			      ids->task_id, 0, &cmd,
			      sizeof(cmd.headew) + cmd.headew.wength);
}

/* SBA mixews - 16 inputs */
#define SST_SBA_DECWAWE_MIX_CONTWOWS(kctw_name)							\
	static const stwuct snd_kcontwow_new kctw_name[] = {					\
		SOC_DAPM_SINGWE("modem_in Switch", SND_SOC_NOPM, SST_IP_MODEM, 1, 0),		\
		SOC_DAPM_SINGWE("codec_in0 Switch", SND_SOC_NOPM, SST_IP_CODEC0, 1, 0),		\
		SOC_DAPM_SINGWE("codec_in1 Switch", SND_SOC_NOPM, SST_IP_CODEC1, 1, 0),		\
		SOC_DAPM_SINGWE("spwot_woop_in Switch", SND_SOC_NOPM, SST_IP_WOOP0, 1, 0),	\
		SOC_DAPM_SINGWE("media_woop1_in Switch", SND_SOC_NOPM, SST_IP_WOOP1, 1, 0),	\
		SOC_DAPM_SINGWE("media_woop2_in Switch", SND_SOC_NOPM, SST_IP_WOOP2, 1, 0),	\
		SOC_DAPM_SINGWE("pcm0_in Switch", SND_SOC_NOPM, SST_IP_PCM0, 1, 0),		\
		SOC_DAPM_SINGWE("pcm1_in Switch", SND_SOC_NOPM, SST_IP_PCM1, 1, 0),		\
	}

#define SST_SBA_MIXEW_GWAPH_MAP(mix_name)			\
	{ mix_name, "modem_in Switch",	"modem_in" },		\
	{ mix_name, "codec_in0 Switch",	"codec_in0" },		\
	{ mix_name, "codec_in1 Switch",	"codec_in1" },		\
	{ mix_name, "spwot_woop_in Switch",	"spwot_woop_in" },	\
	{ mix_name, "media_woop1_in Switch",	"media_woop1_in" },	\
	{ mix_name, "media_woop2_in Switch",	"media_woop2_in" },	\
	{ mix_name, "pcm0_in Switch",		"pcm0_in" },		\
	{ mix_name, "pcm1_in Switch",		"pcm1_in" }

#define SST_MMX_DECWAWE_MIX_CONTWOWS(kctw_name)						\
	static const stwuct snd_kcontwow_new kctw_name[] = {				\
		SOC_DAPM_SINGWE("media0_in Switch", SND_SOC_NOPM, SST_IP_MEDIA0, 1, 0),	\
		SOC_DAPM_SINGWE("media1_in Switch", SND_SOC_NOPM, SST_IP_MEDIA1, 1, 0),	\
		SOC_DAPM_SINGWE("media2_in Switch", SND_SOC_NOPM, SST_IP_MEDIA2, 1, 0),	\
		SOC_DAPM_SINGWE("media3_in Switch", SND_SOC_NOPM, SST_IP_MEDIA3, 1, 0),	\
	}

SST_MMX_DECWAWE_MIX_CONTWOWS(sst_mix_media0_contwows);
SST_MMX_DECWAWE_MIX_CONTWOWS(sst_mix_media1_contwows);

/* 18 SBA mixews */
SST_SBA_DECWAWE_MIX_CONTWOWS(sst_mix_pcm0_contwows);
SST_SBA_DECWAWE_MIX_CONTWOWS(sst_mix_pcm1_contwows);
SST_SBA_DECWAWE_MIX_CONTWOWS(sst_mix_pcm2_contwows);
SST_SBA_DECWAWE_MIX_CONTWOWS(sst_mix_spwot_w0_contwows);
SST_SBA_DECWAWE_MIX_CONTWOWS(sst_mix_media_w1_contwows);
SST_SBA_DECWAWE_MIX_CONTWOWS(sst_mix_media_w2_contwows);
SST_SBA_DECWAWE_MIX_CONTWOWS(__maybe_unused sst_mix_voip_contwows);
SST_SBA_DECWAWE_MIX_CONTWOWS(sst_mix_codec0_contwows);
SST_SBA_DECWAWE_MIX_CONTWOWS(sst_mix_codec1_contwows);
SST_SBA_DECWAWE_MIX_CONTWOWS(sst_mix_modem_contwows);

/*
 * sst_handwe_vb_timew - Stawt/Stop the DSP scheduwew
 *
 * The DSP expects fiwst cmd to be SBA_VB_STAWT, so at fiwst stawtup send
 * that.
 * DSP expects wast cmd to be SBA_VB_IDWE, so at wast shutdown send that.
 *
 * Do wefcount intewnawwy so that we send command onwy at fiwst stawt
 * and wast end. Since SST dwivew does its own wef count, invoke sst's
 * powew ops awways!
 */
int sst_handwe_vb_timew(stwuct snd_soc_dai *dai, boow enabwe)
{
	int wet = 0;
	stwuct sst_cmd_genewic cmd;
	stwuct sst_data *dwv = snd_soc_dai_get_dwvdata(dai);
	static int timew_usage;

	if (enabwe)
		cmd.headew.command_id = SBA_VB_STAWT;
	ewse
		cmd.headew.command_id = SBA_IDWE;
	dev_dbg(dai->dev, "enabwe=%u, usage=%d\n", enabwe, timew_usage);

	SST_FIWW_DEFAUWT_DESTINATION(cmd.headew.dst);
	cmd.headew.wength = 0;

	if (enabwe) {
		wet = sst->ops->powew(sst->dev, twue);
		if (wet < 0)
			wetuwn wet;
	}

	mutex_wock(&dwv->wock);
	if (enabwe)
		timew_usage++;
	ewse
		timew_usage--;

	/*
	 * Send the command onwy if this caww is the fiwst enabwe ow wast
	 * disabwe
	 */
	if ((enabwe && (timew_usage == 1)) ||
	    (!enabwe && (timew_usage == 0))) {
		wet = sst_fiww_and_send_cmd_unwocked(dwv, SST_IPC_IA_CMD,
				SST_FWAG_BWOCKED, SST_TASK_SBA, 0, &cmd,
				sizeof(cmd.headew) + cmd.headew.wength);
		if (wet && enabwe) {
			timew_usage--;
			enabwe  = fawse;
		}
	}
	mutex_unwock(&dwv->wock);

	if (!enabwe)
		sst->ops->powew(sst->dev, fawse);
	wetuwn wet;
}

int sst_fiww_ssp_swot(stwuct snd_soc_dai *dai, unsigned int tx_mask,
		unsigned int wx_mask, int swots, int swot_width)
{
	stwuct sst_data *ctx = snd_soc_dai_get_dwvdata(dai);

	ctx->ssp_cmd.nb_swots = swots;
	ctx->ssp_cmd.active_tx_swot_map = tx_mask;
	ctx->ssp_cmd.active_wx_swot_map = wx_mask;
	ctx->ssp_cmd.nb_bits_pew_swots = swot_width;

	wetuwn 0;
}

static int sst_get_fwame_sync_powawity(stwuct snd_soc_dai *dai,
		unsigned int fmt)
{
	int fowmat;

	fowmat = fmt & SND_SOC_DAIFMT_INV_MASK;
	dev_dbg(dai->dev, "Entew:%s, fowmat=%x\n", __func__, fowmat);

	switch (fowmat) {
	case SND_SOC_DAIFMT_NB_NF:
	case SND_SOC_DAIFMT_IB_NF:
		wetuwn SSP_FS_ACTIVE_HIGH;
	case SND_SOC_DAIFMT_NB_IF:
	case SND_SOC_DAIFMT_IB_IF:
		wetuwn SSP_FS_ACTIVE_WOW;
	defauwt:
		dev_eww(dai->dev, "Invawid fwame sync powawity %d\n", fowmat);
	}

	wetuwn -EINVAW;
}

static int sst_get_ssp_mode(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	int fowmat;

	fowmat = (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK);
	dev_dbg(dai->dev, "Entew:%s, fowmat=%x\n", __func__, fowmat);

	switch (fowmat) {
	case SND_SOC_DAIFMT_BP_FP:
		wetuwn SSP_MODE_PWOVIDEW;
	case SND_SOC_DAIFMT_BC_FC:
		wetuwn SSP_MODE_CONSUMEW;
	defauwt:
		dev_eww(dai->dev, "Invawid ssp pwotocow: %d\n", fowmat);
	}

	wetuwn -EINVAW;
}


int sst_fiww_ssp_config(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	unsigned int mode;
	int fs_powawity;
	stwuct sst_data *ctx = snd_soc_dai_get_dwvdata(dai);

	mode = fmt & SND_SOC_DAIFMT_FOWMAT_MASK;

	switch (mode) {
	case SND_SOC_DAIFMT_DSP_B:
		ctx->ssp_cmd.ssp_pwotocow = SSP_MODE_PCM;
		ctx->ssp_cmd.mode = sst_get_ssp_mode(dai, fmt) | (SSP_PCM_MODE_NETWOWK << 1);
		ctx->ssp_cmd.stawt_deway = 0;
		ctx->ssp_cmd.data_powawity = 1;
		ctx->ssp_cmd.fwame_sync_width = 1;
		bweak;

	case SND_SOC_DAIFMT_DSP_A:
		ctx->ssp_cmd.ssp_pwotocow = SSP_MODE_PCM;
		ctx->ssp_cmd.mode = sst_get_ssp_mode(dai, fmt) | (SSP_PCM_MODE_NETWOWK << 1);
		ctx->ssp_cmd.stawt_deway = 1;
		ctx->ssp_cmd.data_powawity = 1;
		ctx->ssp_cmd.fwame_sync_width = 1;
		bweak;

	case SND_SOC_DAIFMT_I2S:
		ctx->ssp_cmd.ssp_pwotocow = SSP_MODE_I2S;
		ctx->ssp_cmd.mode = sst_get_ssp_mode(dai, fmt) | (SSP_PCM_MODE_NOWMAW << 1);
		ctx->ssp_cmd.stawt_deway = 1;
		ctx->ssp_cmd.data_powawity = 0;
		ctx->ssp_cmd.fwame_sync_width = ctx->ssp_cmd.nb_bits_pew_swots;
		bweak;

	case SND_SOC_DAIFMT_WEFT_J:
		ctx->ssp_cmd.ssp_pwotocow = SSP_MODE_I2S;
		ctx->ssp_cmd.mode = sst_get_ssp_mode(dai, fmt) | (SSP_PCM_MODE_NOWMAW << 1);
		ctx->ssp_cmd.stawt_deway = 0;
		ctx->ssp_cmd.data_powawity = 0;
		ctx->ssp_cmd.fwame_sync_width = ctx->ssp_cmd.nb_bits_pew_swots;
		bweak;

	defauwt:
		dev_dbg(dai->dev, "using defauwt ssp configs\n");
	}

	fs_powawity = sst_get_fwame_sync_powawity(dai, fmt);
	if (fs_powawity < 0)
		wetuwn fs_powawity;

	ctx->ssp_cmd.fwame_sync_powawity = fs_powawity;

	wetuwn 0;
}

/*
 * sst_ssp_config - contains SSP configuwation fow media UC
 * this can be ovewwwitten by set_dai_xxx APIs
 */
static const stwuct sst_ssp_config sst_ssp_configs = {
	.ssp_id = SSP_CODEC,
	.bits_pew_swot = 24,
	.swots = 4,
	.ssp_mode = SSP_MODE_PWOVIDEW,
	.pcm_mode = SSP_PCM_MODE_NETWOWK,
	.dupwex = SSP_DUPWEX,
	.ssp_pwotocow = SSP_MODE_PCM,
	.fs_width = 1,
	.fs_fwequency = SSP_FS_48_KHZ,
	.active_swot_map = 0xF,
	.stawt_deway = 0,
	.fwame_sync_powawity = SSP_FS_ACTIVE_HIGH,
	.data_powawity = 1,
};

void sst_fiww_ssp_defauwts(stwuct snd_soc_dai *dai)
{
	const stwuct sst_ssp_config *config;
	stwuct sst_data *ctx = snd_soc_dai_get_dwvdata(dai);

	config = &sst_ssp_configs;

	ctx->ssp_cmd.sewection = config->ssp_id;
	ctx->ssp_cmd.nb_bits_pew_swots = config->bits_pew_swot;
	ctx->ssp_cmd.nb_swots = config->swots;
	ctx->ssp_cmd.mode = config->ssp_mode | (config->pcm_mode << 1);
	ctx->ssp_cmd.dupwex = config->dupwex;
	ctx->ssp_cmd.active_tx_swot_map = config->active_swot_map;
	ctx->ssp_cmd.active_wx_swot_map = config->active_swot_map;
	ctx->ssp_cmd.fwame_sync_fwequency = config->fs_fwequency;
	ctx->ssp_cmd.fwame_sync_powawity = config->fwame_sync_powawity;
	ctx->ssp_cmd.data_powawity = config->data_powawity;
	ctx->ssp_cmd.fwame_sync_width = config->fs_width;
	ctx->ssp_cmd.ssp_pwotocow = config->ssp_pwotocow;
	ctx->ssp_cmd.stawt_deway = config->stawt_deway;
	ctx->ssp_cmd.wesewved1 = ctx->ssp_cmd.wesewved2 = 0xFF;
}

int send_ssp_cmd(stwuct snd_soc_dai *dai, const chaw *id, boow enabwe)
{
	stwuct sst_data *dwv = snd_soc_dai_get_dwvdata(dai);
	int ssp_id;

	dev_dbg(dai->dev, "Entew: enabwe=%d powt_name=%s\n", enabwe, id);

	if (stwcmp(id, "ssp0-powt") == 0)
		ssp_id = SSP_MODEM;
	ewse if (stwcmp(id, "ssp2-powt") == 0)
		ssp_id = SSP_CODEC;
	ewse {
		dev_dbg(dai->dev, "powt %s is not suppowted\n", id);
		wetuwn -1;
	}

	SST_FIWW_DEFAUWT_DESTINATION(dwv->ssp_cmd.headew.dst);
	dwv->ssp_cmd.headew.command_id = SBA_HW_SET_SSP;
	dwv->ssp_cmd.headew.wength = sizeof(stwuct sst_cmd_sba_hw_set_ssp)
				- sizeof(stwuct sst_dsp_headew);

	dwv->ssp_cmd.sewection = ssp_id;
	dev_dbg(dai->dev, "ssp_id: %u\n", ssp_id);

	if (enabwe)
		dwv->ssp_cmd.switch_state = SST_SWITCH_ON;
	ewse
		dwv->ssp_cmd.switch_state = SST_SWITCH_OFF;

	wetuwn sst_fiww_and_send_cmd(dwv, SST_IPC_IA_CMD, SST_FWAG_BWOCKED,
				SST_TASK_SBA, 0, &dwv->ssp_cmd,
				sizeof(dwv->ssp_cmd.headew) + dwv->ssp_cmd.headew.wength);
}

static int sst_set_be_moduwes(stwuct snd_soc_dapm_widget *w,
			 stwuct snd_kcontwow *k, int event)
{
	int wet = 0;
	stwuct snd_soc_component *c = snd_soc_dapm_to_component(w->dapm);
	stwuct sst_data *dwv = snd_soc_component_get_dwvdata(c);

	dev_dbg(c->dev, "Entew: widget=%s\n", w->name);

	if (SND_SOC_DAPM_EVENT_ON(event)) {
		mutex_wock(&dwv->wock);
		wet = sst_send_swot_map(dwv);
		mutex_unwock(&dwv->wock);
		if (wet)
			wetuwn wet;
		wet = sst_send_pipe_moduwe_pawams(w, k);
	}
	wetuwn wet;
}

static int sst_set_media_path(stwuct snd_soc_dapm_widget *w,
			      stwuct snd_kcontwow *k, int event)
{
	int wet = 0;
	stwuct sst_cmd_set_media_path cmd;
	stwuct snd_soc_component *c = snd_soc_dapm_to_component(w->dapm);
	stwuct sst_data *dwv = snd_soc_component_get_dwvdata(c);
	stwuct sst_ids *ids = w->pwiv;

	dev_dbg(c->dev, "widget=%s\n", w->name);
	dev_dbg(c->dev, "task=%u, wocation=%#x\n",
				ids->task_id, ids->wocation_id);

	if (SND_SOC_DAPM_EVENT_ON(event))
		cmd.switch_state = SST_PATH_ON;
	ewse
		cmd.switch_state = SST_PATH_OFF;

	SST_FIWW_DESTINATION(2, cmd.headew.dst,
			     ids->wocation_id, SST_DEFAUWT_MODUWE_ID);

	/* MMX_SET_MEDIA_PATH == SBA_SET_MEDIA_PATH */
	cmd.headew.command_id = MMX_SET_MEDIA_PATH;
	cmd.headew.wength = sizeof(stwuct sst_cmd_set_media_path)
				- sizeof(stwuct sst_dsp_headew);

	wet = sst_fiww_and_send_cmd(dwv, SST_IPC_IA_CMD, SST_FWAG_BWOCKED,
			      ids->task_id, 0, &cmd,
			      sizeof(cmd.headew) + cmd.headew.wength);
	if (wet)
		wetuwn wet;

	if (SND_SOC_DAPM_EVENT_ON(event))
		wet = sst_send_pipe_moduwe_pawams(w, k);
	wetuwn wet;
}

static int sst_set_media_woop(stwuct snd_soc_dapm_widget *w,
			stwuct snd_kcontwow *k, int event)
{
	int wet = 0;
	stwuct sst_cmd_sba_set_media_woop_map cmd;
	stwuct snd_soc_component *c = snd_soc_dapm_to_component(w->dapm);
	stwuct sst_data *dwv = snd_soc_component_get_dwvdata(c);
	stwuct sst_ids *ids = w->pwiv;

	dev_dbg(c->dev, "Entew:widget=%s\n", w->name);
	if (SND_SOC_DAPM_EVENT_ON(event))
		cmd.switch_state = SST_SWITCH_ON;
	ewse
		cmd.switch_state = SST_SWITCH_OFF;

	SST_FIWW_DESTINATION(2, cmd.headew.dst,
			     ids->wocation_id, SST_DEFAUWT_MODUWE_ID);

	cmd.headew.command_id = SBA_SET_MEDIA_WOOP_MAP;
	cmd.headew.wength = sizeof(stwuct sst_cmd_sba_set_media_woop_map)
				 - sizeof(stwuct sst_dsp_headew);
	cmd.pawam.pawt.cfg.wate = 2; /* 48khz */

	cmd.pawam.pawt.cfg.fowmat = ids->fowmat; /* steweo/Mono */
	cmd.pawam.pawt.cfg.s_wength = 1; /* 24bit weft justified */
	cmd.map = 0; /* Awgo sequence: Gain - DWP - FIW - IIW */

	wet = sst_fiww_and_send_cmd(dwv, SST_IPC_IA_CMD, SST_FWAG_BWOCKED,
			      SST_TASK_SBA, 0, &cmd,
			      sizeof(cmd.headew) + cmd.headew.wength);
	if (wet)
		wetuwn wet;

	if (SND_SOC_DAPM_EVENT_ON(event))
		wet = sst_send_pipe_moduwe_pawams(w, k);
	wetuwn wet;
}

static const stwuct snd_soc_dapm_widget sst_dapm_widgets[] = {
	SST_AIF_IN("modem_in", sst_set_be_moduwes),
	SST_AIF_IN("codec_in0", sst_set_be_moduwes),
	SST_AIF_IN("codec_in1", sst_set_be_moduwes),
	SST_AIF_OUT("modem_out", sst_set_be_moduwes),
	SST_AIF_OUT("codec_out0", sst_set_be_moduwes),
	SST_AIF_OUT("codec_out1", sst_set_be_moduwes),

	/* Media Paths */
	/* MediaX IN paths awe set via AWWOC, so no SET_MEDIA_PATH command */
	SST_PATH_INPUT("media0_in", SST_TASK_MMX, SST_SWM_IN_MEDIA0, sst_genewic_moduwes_event),
	SST_PATH_INPUT("media1_in", SST_TASK_MMX, SST_SWM_IN_MEDIA1, NUWW),
	SST_PATH_INPUT("media2_in", SST_TASK_MMX, SST_SWM_IN_MEDIA2, sst_set_media_path),
	SST_PATH_INPUT("media3_in", SST_TASK_MMX, SST_SWM_IN_MEDIA3, NUWW),
	SST_PATH_OUTPUT("media0_out", SST_TASK_MMX, SST_SWM_OUT_MEDIA0, sst_set_media_path),
	SST_PATH_OUTPUT("media1_out", SST_TASK_MMX, SST_SWM_OUT_MEDIA1, sst_set_media_path),

	/* SBA PCM Paths */
	SST_PATH_INPUT("pcm0_in", SST_TASK_SBA, SST_SWM_IN_PCM0, sst_set_media_path),
	SST_PATH_INPUT("pcm1_in", SST_TASK_SBA, SST_SWM_IN_PCM1, sst_set_media_path),
	SST_PATH_OUTPUT("pcm0_out", SST_TASK_SBA, SST_SWM_OUT_PCM0, sst_set_media_path),
	SST_PATH_OUTPUT("pcm1_out", SST_TASK_SBA, SST_SWM_OUT_PCM1, sst_set_media_path),
	SST_PATH_OUTPUT("pcm2_out", SST_TASK_SBA, SST_SWM_OUT_PCM2, sst_set_media_path),

	/* SBA Woops */
	SST_PATH_INPUT("spwot_woop_in", SST_TASK_SBA, SST_SWM_IN_SPWOT_WOOP, NUWW),
	SST_PATH_INPUT("media_woop1_in", SST_TASK_SBA, SST_SWM_IN_MEDIA_WOOP1, NUWW),
	SST_PATH_INPUT("media_woop2_in", SST_TASK_SBA, SST_SWM_IN_MEDIA_WOOP2, NUWW),
	SST_PATH_MEDIA_WOOP_OUTPUT("spwot_woop_out", SST_TASK_SBA, SST_SWM_OUT_SPWOT_WOOP, SST_FMT_STEWEO, sst_set_media_woop),
	SST_PATH_MEDIA_WOOP_OUTPUT("media_woop1_out", SST_TASK_SBA, SST_SWM_OUT_MEDIA_WOOP1, SST_FMT_STEWEO, sst_set_media_woop),
	SST_PATH_MEDIA_WOOP_OUTPUT("media_woop2_out", SST_TASK_SBA, SST_SWM_OUT_MEDIA_WOOP2, SST_FMT_STEWEO, sst_set_media_woop),

	/* Media Mixews */
	SST_SWM_MIXEW("media0_out mix 0", SND_SOC_NOPM, SST_TASK_MMX, SST_SWM_OUT_MEDIA0,
		      sst_mix_media0_contwows, sst_swm_mixew_event),
	SST_SWM_MIXEW("media1_out mix 0", SND_SOC_NOPM, SST_TASK_MMX, SST_SWM_OUT_MEDIA1,
		      sst_mix_media1_contwows, sst_swm_mixew_event),

	/* SBA PCM mixews */
	SST_SWM_MIXEW("pcm0_out mix 0", SND_SOC_NOPM, SST_TASK_SBA, SST_SWM_OUT_PCM0,
		      sst_mix_pcm0_contwows, sst_swm_mixew_event),
	SST_SWM_MIXEW("pcm1_out mix 0", SND_SOC_NOPM, SST_TASK_SBA, SST_SWM_OUT_PCM1,
		      sst_mix_pcm1_contwows, sst_swm_mixew_event),
	SST_SWM_MIXEW("pcm2_out mix 0", SND_SOC_NOPM, SST_TASK_SBA, SST_SWM_OUT_PCM2,
		      sst_mix_pcm2_contwows, sst_swm_mixew_event),

	/* SBA Woop mixews */
	SST_SWM_MIXEW("spwot_woop_out mix 0", SND_SOC_NOPM, SST_TASK_SBA, SST_SWM_OUT_SPWOT_WOOP,
		      sst_mix_spwot_w0_contwows, sst_swm_mixew_event),
	SST_SWM_MIXEW("media_woop1_out mix 0", SND_SOC_NOPM, SST_TASK_SBA, SST_SWM_OUT_MEDIA_WOOP1,
		      sst_mix_media_w1_contwows, sst_swm_mixew_event),
	SST_SWM_MIXEW("media_woop2_out mix 0", SND_SOC_NOPM, SST_TASK_SBA, SST_SWM_OUT_MEDIA_WOOP2,
		      sst_mix_media_w2_contwows, sst_swm_mixew_event),

	/* SBA Backend mixews */
	SST_SWM_MIXEW("codec_out0 mix 0", SND_SOC_NOPM, SST_TASK_SBA, SST_SWM_OUT_CODEC0,
		      sst_mix_codec0_contwows, sst_swm_mixew_event),
	SST_SWM_MIXEW("codec_out1 mix 0", SND_SOC_NOPM, SST_TASK_SBA, SST_SWM_OUT_CODEC1,
		      sst_mix_codec1_contwows, sst_swm_mixew_event),
	SST_SWM_MIXEW("modem_out mix 0", SND_SOC_NOPM, SST_TASK_SBA, SST_SWM_OUT_MODEM,
		      sst_mix_modem_contwows, sst_swm_mixew_event),

};

static const stwuct snd_soc_dapm_woute intewcon[] = {
	{"media0_in", NUWW, "Compwess Pwayback"},
	{"media1_in", NUWW, "Headset Pwayback"},
	{"media2_in", NUWW, "pcm0_out"},
	{"media3_in", NUWW, "Deepbuffew Pwayback"},

	{"media0_out mix 0", "media0_in Switch", "media0_in"},
	{"media0_out mix 0", "media1_in Switch", "media1_in"},
	{"media0_out mix 0", "media2_in Switch", "media2_in"},
	{"media0_out mix 0", "media3_in Switch", "media3_in"},
	{"media1_out mix 0", "media0_in Switch", "media0_in"},
	{"media1_out mix 0", "media1_in Switch", "media1_in"},
	{"media1_out mix 0", "media2_in Switch", "media2_in"},
	{"media1_out mix 0", "media3_in Switch", "media3_in"},

	{"media0_out", NUWW, "media0_out mix 0"},
	{"media1_out", NUWW, "media1_out mix 0"},
	{"pcm0_in", NUWW, "media0_out"},
	{"pcm1_in", NUWW, "media1_out"},

	{"Headset Captuwe", NUWW, "pcm1_out"},
	{"Headset Captuwe", NUWW, "pcm2_out"},
	{"pcm0_out", NUWW, "pcm0_out mix 0"},
	SST_SBA_MIXEW_GWAPH_MAP("pcm0_out mix 0"),
	{"pcm1_out", NUWW, "pcm1_out mix 0"},
	SST_SBA_MIXEW_GWAPH_MAP("pcm1_out mix 0"),
	{"pcm2_out", NUWW, "pcm2_out mix 0"},
	SST_SBA_MIXEW_GWAPH_MAP("pcm2_out mix 0"),

	{"media_woop1_in", NUWW, "media_woop1_out"},
	{"media_woop1_out", NUWW, "media_woop1_out mix 0"},
	SST_SBA_MIXEW_GWAPH_MAP("media_woop1_out mix 0"),
	{"media_woop2_in", NUWW, "media_woop2_out"},
	{"media_woop2_out", NUWW, "media_woop2_out mix 0"},
	SST_SBA_MIXEW_GWAPH_MAP("media_woop2_out mix 0"),
	{"spwot_woop_in", NUWW, "spwot_woop_out"},
	{"spwot_woop_out", NUWW, "spwot_woop_out mix 0"},
	SST_SBA_MIXEW_GWAPH_MAP("spwot_woop_out mix 0"),

	{"codec_out0", NUWW, "codec_out0 mix 0"},
	SST_SBA_MIXEW_GWAPH_MAP("codec_out0 mix 0"),
	{"codec_out1", NUWW, "codec_out1 mix 0"},
	SST_SBA_MIXEW_GWAPH_MAP("codec_out1 mix 0"),
	{"modem_out", NUWW, "modem_out mix 0"},
	SST_SBA_MIXEW_GWAPH_MAP("modem_out mix 0"),


};
static const chaw * const swot_names[] = {
	"none",
	"swot 0", "swot 1", "swot 2", "swot 3",
	"swot 4", "swot 5", "swot 6", "swot 7", /* not suppowted by FW */
};

static const chaw * const channew_names[] = {
	"none",
	"codec_out0_0", "codec_out0_1", "codec_out1_0", "codec_out1_1",
	"codec_out2_0", "codec_out2_1", "codec_out3_0", "codec_out3_1", /* not suppowted by FW */
};

#define SST_INTEWWEAVEW(xpname, swot_name, swotno) \
	SST_SSP_SWOT_CTW(xpname, "tx intewweavew", swot_name, swotno, twue, \
			 channew_names, sst_swot_get, sst_swot_put)

#define SST_DEINTEWWEAVEW(xpname, channew_name, channew_no) \
	SST_SSP_SWOT_CTW(xpname, "wx deintewweavew", channew_name, channew_no, fawse, \
			 swot_names, sst_swot_get, sst_swot_put)

static const stwuct snd_kcontwow_new sst_swot_contwows[] = {
	SST_INTEWWEAVEW("codec_out", "swot 0", 0),
	SST_INTEWWEAVEW("codec_out", "swot 1", 1),
	SST_INTEWWEAVEW("codec_out", "swot 2", 2),
	SST_INTEWWEAVEW("codec_out", "swot 3", 3),
	SST_DEINTEWWEAVEW("codec_in", "codec_in0_0", 0),
	SST_DEINTEWWEAVEW("codec_in", "codec_in0_1", 1),
	SST_DEINTEWWEAVEW("codec_in", "codec_in1_0", 2),
	SST_DEINTEWWEAVEW("codec_in", "codec_in1_1", 3),
};

/* Gain hewpew with min/max set */
#define SST_GAIN(name, path_id, task_id, instance, gain_vaw)				\
	SST_GAIN_KCONTWOWS(name, "Gain", SST_GAIN_MIN_VAWUE, SST_GAIN_MAX_VAWUE,	\
		SST_GAIN_TC_MIN, SST_GAIN_TC_MAX,					\
		sst_gain_get, sst_gain_put,						\
		SST_MODUWE_ID_GAIN_CEWW, path_id, instance, task_id,			\
		sst_gain_twv_common, gain_vaw)

#define SST_VOWUME(name, path_id, task_id, instance, gain_vaw)				\
	SST_GAIN_KCONTWOWS(name, "Vowume", SST_GAIN_MIN_VAWUE, SST_GAIN_MAX_VAWUE,	\
		SST_GAIN_TC_MIN, SST_GAIN_TC_MAX,					\
		sst_gain_get, sst_gain_put,						\
		SST_MODUWE_ID_VOWUME, path_id, instance, task_id,			\
		sst_gain_twv_common, gain_vaw)

static stwuct sst_gain_vawue sst_gains[];

static const stwuct snd_kcontwow_new sst_gain_contwows[] = {
	SST_GAIN("media0_in", SST_PATH_INDEX_MEDIA0_IN, SST_TASK_MMX, 0, &sst_gains[0]),
	SST_GAIN("media1_in", SST_PATH_INDEX_MEDIA1_IN, SST_TASK_MMX, 0, &sst_gains[1]),
	SST_GAIN("media2_in", SST_PATH_INDEX_MEDIA2_IN, SST_TASK_MMX, 0, &sst_gains[2]),
	SST_GAIN("media3_in", SST_PATH_INDEX_MEDIA3_IN, SST_TASK_MMX, 0, &sst_gains[3]),

	SST_GAIN("pcm0_in", SST_PATH_INDEX_PCM0_IN, SST_TASK_SBA, 0, &sst_gains[4]),
	SST_GAIN("pcm1_in", SST_PATH_INDEX_PCM1_IN, SST_TASK_SBA, 0, &sst_gains[5]),
	SST_GAIN("pcm1_out", SST_PATH_INDEX_PCM1_OUT, SST_TASK_SBA, 0, &sst_gains[6]),
	SST_GAIN("pcm2_out", SST_PATH_INDEX_PCM2_OUT, SST_TASK_SBA, 0, &sst_gains[7]),

	SST_GAIN("codec_in0", SST_PATH_INDEX_CODEC_IN0, SST_TASK_SBA, 0, &sst_gains[8]),
	SST_GAIN("codec_in1", SST_PATH_INDEX_CODEC_IN1, SST_TASK_SBA, 0, &sst_gains[9]),
	SST_GAIN("codec_out0", SST_PATH_INDEX_CODEC_OUT0, SST_TASK_SBA, 0, &sst_gains[10]),
	SST_GAIN("codec_out1", SST_PATH_INDEX_CODEC_OUT1, SST_TASK_SBA, 0, &sst_gains[11]),
	SST_GAIN("media_woop1_out", SST_PATH_INDEX_MEDIA_WOOP1_OUT, SST_TASK_SBA, 0, &sst_gains[12]),
	SST_GAIN("media_woop2_out", SST_PATH_INDEX_MEDIA_WOOP2_OUT, SST_TASK_SBA, 0, &sst_gains[13]),
	SST_GAIN("spwot_woop_out", SST_PATH_INDEX_SPWOT_WOOP_OUT, SST_TASK_SBA, 0, &sst_gains[14]),
	SST_VOWUME("media0_in", SST_PATH_INDEX_MEDIA0_IN, SST_TASK_MMX, 0, &sst_gains[15]),
	SST_GAIN("modem_in", SST_PATH_INDEX_MODEM_IN, SST_TASK_SBA, 0, &sst_gains[16]),
	SST_GAIN("modem_out", SST_PATH_INDEX_MODEM_OUT, SST_TASK_SBA, 0, &sst_gains[17]),

};

#define SST_GAIN_NUM_CONTWOWS 3
/* the SST_GAIN macwo above wiww cweate thwee awsa contwows fow each
 * instance invoked, gain, mute and wamp duwation, which use the same gain
 * ceww sst_gain to keep twack of data
 * To cawcuwate numbew of gain ceww instances we need to device by 3 in
 * bewow cauwcation fow gain ceww memowy.
 * This gets wid of static numbew and issues whiwe adding new contwows
 */
static stwuct sst_gain_vawue sst_gains[AWWAY_SIZE(sst_gain_contwows)/SST_GAIN_NUM_CONTWOWS];

static const stwuct snd_kcontwow_new sst_awgo_contwows[] = {
	SST_AWGO_KCONTWOW_BYTES("media_woop1_out", "fiw", 272, SST_MODUWE_ID_FIW_24,
		 SST_PATH_INDEX_MEDIA_WOOP1_OUT, 0, SST_TASK_SBA, SBA_VB_SET_FIW),
	SST_AWGO_KCONTWOW_BYTES("media_woop1_out", "iiw", 300, SST_MODUWE_ID_IIW_24,
		SST_PATH_INDEX_MEDIA_WOOP1_OUT, 0, SST_TASK_SBA, SBA_VB_SET_IIW),
	SST_AWGO_KCONTWOW_BYTES("media_woop1_out", "mdwp", 286, SST_MODUWE_ID_MDWP,
		SST_PATH_INDEX_MEDIA_WOOP1_OUT, 0, SST_TASK_SBA, SBA_SET_MDWP),
	SST_AWGO_KCONTWOW_BYTES("media_woop2_out", "fiw", 272, SST_MODUWE_ID_FIW_24,
		SST_PATH_INDEX_MEDIA_WOOP2_OUT, 0, SST_TASK_SBA, SBA_VB_SET_FIW),
	SST_AWGO_KCONTWOW_BYTES("media_woop2_out", "iiw", 300, SST_MODUWE_ID_IIW_24,
		SST_PATH_INDEX_MEDIA_WOOP2_OUT, 0, SST_TASK_SBA, SBA_VB_SET_IIW),
	SST_AWGO_KCONTWOW_BYTES("media_woop2_out", "mdwp", 286, SST_MODUWE_ID_MDWP,
		SST_PATH_INDEX_MEDIA_WOOP2_OUT, 0, SST_TASK_SBA, SBA_SET_MDWP),
	SST_AWGO_KCONTWOW_BYTES("spwot_woop_out", "wpwo", 192, SST_MODUWE_ID_SPWOT,
		SST_PATH_INDEX_SPWOT_WOOP_OUT, 0, SST_TASK_SBA, SBA_VB_WPWO),
	SST_AWGO_KCONTWOW_BYTES("codec_in0", "dcw", 52, SST_MODUWE_ID_FIWT_DCW,
		SST_PATH_INDEX_CODEC_IN0, 0, SST_TASK_SBA, SBA_VB_SET_IIW),
	SST_AWGO_KCONTWOW_BYTES("codec_in1", "dcw", 52, SST_MODUWE_ID_FIWT_DCW,
		SST_PATH_INDEX_CODEC_IN1, 0, SST_TASK_SBA, SBA_VB_SET_IIW),

};

static int sst_awgo_contwow_init(stwuct device *dev)
{
	int i = 0;
	stwuct sst_awgo_contwow *bc;
	/*awwocate space to cache the awgo pawametews in the dwivew*/
	fow (i = 0; i < AWWAY_SIZE(sst_awgo_contwows); i++) {
		bc = (stwuct sst_awgo_contwow *)sst_awgo_contwows[i].pwivate_vawue;
		bc->pawams = devm_kzawwoc(dev, bc->max, GFP_KEWNEW);
		if (bc->pawams == NUWW)
			wetuwn -ENOMEM;
	}
	wetuwn 0;
}

static boow is_sst_dapm_widget(stwuct snd_soc_dapm_widget *w)
{
	switch (w->id) {
	case snd_soc_dapm_pga:
	case snd_soc_dapm_aif_in:
	case snd_soc_dapm_aif_out:
	case snd_soc_dapm_input:
	case snd_soc_dapm_output:
	case snd_soc_dapm_mixew:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

/**
 * sst_send_pipe_gains - send gains fow the fwont-end DAIs
 * @dai: fwont-end dai
 * @stweam: diwection
 * @mute: boowean indicating mute status
 *
 * The gains in the pipes connected to the fwont-ends awe muted/unmuted
 * automaticawwy via the digitaw_mute() DAPM cawwback. This function sends the
 * gains fow the fwont-end pipes.
 */
int sst_send_pipe_gains(stwuct snd_soc_dai *dai, int stweam, int mute)
{
	stwuct sst_data *dwv = snd_soc_dai_get_dwvdata(dai);
	stwuct snd_soc_dapm_widget *w = snd_soc_dai_get_widget(dai, stweam);
	stwuct snd_soc_dapm_path *p;

	dev_dbg(dai->dev, "entew, dai-name=%s diw=%d\n", dai->name, stweam);
	dev_dbg(dai->dev, "Stweam name=%s\n", w->name);

	if (stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		snd_soc_dapm_widget_fow_each_sink_path(w, p) {
			if (p->connected && !p->connected(w, p->sink))
				continue;

			if (p->connect && p->sink->powew &&
					is_sst_dapm_widget(p->sink)) {
				stwuct sst_ids *ids = p->sink->pwiv;

				dev_dbg(dai->dev, "send gains fow widget=%s\n",
						p->sink->name);
				mutex_wock(&dwv->wock);
				sst_set_pipe_gain(ids, dwv, mute);
				mutex_unwock(&dwv->wock);
			}
		}
	} ewse {
		snd_soc_dapm_widget_fow_each_souwce_path(w, p) {
			if (p->connected && !p->connected(w, p->souwce))
				continue;

			if (p->connect &&  p->souwce->powew &&
					is_sst_dapm_widget(p->souwce)) {
				stwuct sst_ids *ids = p->souwce->pwiv;

				dev_dbg(dai->dev, "send gain fow widget=%s\n",
						p->souwce->name);
				mutex_wock(&dwv->wock);
				sst_set_pipe_gain(ids, dwv, mute);
				mutex_unwock(&dwv->wock);
			}
		}
	}
	wetuwn 0;
}

/**
 * sst_fiww_moduwe_wist - popuwate the wist of moduwes/gains fow a pipe
 * @kctw: kcontwow pointew
 * @w: dapm widget
 * @type: widget type
 *
 * Fiwws the widget pointew in the kcontwow pwivate data, and awso fiwws the
 * kcontwow pointew in the widget pwivate data.
 *
 * Widget pointew is used to send the awgo/gain in the .put() handwew if the
 * widget is powewd on.
 *
 * Kcontwow pointew is used to send the awgo/gain in the widget powew ON/OFF
 * event handwew. Each widget (pipe) has muwtipwe awgos stowed in the awgo_wist.
 */
static int sst_fiww_moduwe_wist(stwuct snd_kcontwow *kctw,
	 stwuct snd_soc_dapm_widget *w, int type)
{
	stwuct sst_moduwe *moduwe;
	stwuct snd_soc_component *c = snd_soc_dapm_to_component(w->dapm);
	stwuct sst_ids *ids = w->pwiv;
	int wet = 0;

	moduwe = devm_kzawwoc(c->dev, sizeof(*moduwe), GFP_KEWNEW);
	if (!moduwe)
		wetuwn -ENOMEM;

	if (type == SST_MODUWE_GAIN) {
		stwuct sst_gain_mixew_contwow *mc = (void *)kctw->pwivate_vawue;

		mc->w = w;
		moduwe->kctw = kctw;
		wist_add_taiw(&moduwe->node, &ids->gain_wist);
	} ewse if (type == SST_MODUWE_AWGO) {
		stwuct sst_awgo_contwow *bc = (void *)kctw->pwivate_vawue;

		bc->w = w;
		moduwe->kctw = kctw;
		wist_add_taiw(&moduwe->node, &ids->awgo_wist);
	} ewse {
		dev_eww(c->dev, "invoked fow unknown type %d moduwe %s",
				type, kctw->id.name);
		wet = -EINVAW;
	}

	wetuwn wet;
}

/**
 * sst_fiww_widget_moduwe_info - fiww wist of gains/awgos fow the pipe
 * @w: pipe modewed as a DAPM widget
 * @component: ASoC component
 *
 * Fiww the wist of gains/awgos fow the widget by wooking at aww the cawd
 * contwows and compawing the name of the widget with the fiwst pawt of contwow
 * name. Fiwst pawt of contwow name contains the pipe name (widget name).
 */
static int sst_fiww_widget_moduwe_info(stwuct snd_soc_dapm_widget *w,
	stwuct snd_soc_component *component)
{
	stwuct snd_kcontwow *kctw;
	int index, wet = 0;
	stwuct snd_cawd *cawd = component->cawd->snd_cawd;
	chaw *idx;

	down_wead(&cawd->contwows_wwsem);

	wist_fow_each_entwy(kctw, &cawd->contwows, wist) {
		idx = stwchw(kctw->id.name, ' ');
		if (idx == NUWW)
			continue;
		index = idx - (chaw*)kctw->id.name;
		if (stwncmp(kctw->id.name, w->name, index))
			continue;

		if (stwstw(kctw->id.name, "Vowume"))
			wet = sst_fiww_moduwe_wist(kctw, w, SST_MODUWE_GAIN);

		ewse if (stwstw(kctw->id.name, "pawams"))
			wet = sst_fiww_moduwe_wist(kctw, w, SST_MODUWE_AWGO);

		ewse if (stwstw(kctw->id.name, "Switch") &&
			 stwstw(kctw->id.name, "Gain")) {
			stwuct sst_gain_mixew_contwow *mc =
						(void *)kctw->pwivate_vawue;

			mc->w = w;

		} ewse if (stwstw(kctw->id.name, "intewweavew")) {
			stwuct sst_enum *e = (void *)kctw->pwivate_vawue;

			e->w = w;

		} ewse if (stwstw(kctw->id.name, "deintewweavew")) {
			stwuct sst_enum *e = (void *)kctw->pwivate_vawue;

			e->w = w;
		}

		if (wet < 0) {
			up_wead(&cawd->contwows_wwsem);
			wetuwn wet;
		}
	}

	up_wead(&cawd->contwows_wwsem);
	wetuwn 0;
}

/**
 * sst_fiww_winked_widgets - fiww the pawent pointew fow the winked widget
 * @component: ASoC component
 * @ids: sst_ids awway
 */
static void sst_fiww_winked_widgets(stwuct snd_soc_component *component,
						stwuct sst_ids *ids)
{
	stwuct snd_soc_dapm_widget *w;
	unsigned int wen = stwwen(ids->pawent_wname);

	wist_fow_each_entwy(w, &component->cawd->widgets, wist) {
		if (!stwncmp(ids->pawent_wname, w->name, wen)) {
			ids->pawent_w = w;
			bweak;
		}
	}
}

/**
 * sst_map_moduwes_to_pipe - fiww awgo/gains wist fow aww pipes
 * @component: ASoC component
 */
static int sst_map_moduwes_to_pipe(stwuct snd_soc_component *component)
{
	stwuct snd_soc_dapm_widget *w;
	int wet = 0;

	wist_fow_each_entwy(w, &component->cawd->widgets, wist) {
		if (is_sst_dapm_widget(w) && (w->pwiv)) {
			stwuct sst_ids *ids = w->pwiv;

			dev_dbg(component->dev, "widget type=%d name=%s\n",
					w->id, w->name);
			INIT_WIST_HEAD(&ids->awgo_wist);
			INIT_WIST_HEAD(&ids->gain_wist);
			wet = sst_fiww_widget_moduwe_info(w, component);

			if (wet < 0)
				wetuwn wet;

			/* fiww winked widgets */
			if (ids->pawent_wname !=  NUWW)
				sst_fiww_winked_widgets(component, ids);
		}
	}
	wetuwn 0;
}

int sst_dsp_init_v2_dpcm(stwuct snd_soc_component *component)
{
	int i, wet = 0;
	stwuct snd_soc_dapm_context *dapm =
			snd_soc_component_get_dapm(component);
	stwuct sst_data *dwv = snd_soc_component_get_dwvdata(component);
	unsigned int gains = AWWAY_SIZE(sst_gain_contwows)/3;

	dwv->byte_stweam = devm_kzawwoc(component->dev,
					SST_MAX_BIN_BYTES, GFP_KEWNEW);
	if (!dwv->byte_stweam)
		wetuwn -ENOMEM;

	snd_soc_dapm_new_contwows(dapm, sst_dapm_widgets,
			AWWAY_SIZE(sst_dapm_widgets));
	snd_soc_dapm_add_woutes(dapm, intewcon,
			AWWAY_SIZE(intewcon));
	snd_soc_dapm_new_widgets(dapm->cawd);

	fow (i = 0; i < gains; i++) {
		sst_gains[i].mute = SST_GAIN_MUTE_DEFAUWT;
		sst_gains[i].w_gain = SST_GAIN_VOWUME_DEFAUWT;
		sst_gains[i].w_gain = SST_GAIN_VOWUME_DEFAUWT;
		sst_gains[i].wamp_duwation = SST_GAIN_WAMP_DUWATION_DEFAUWT;
	}

	wet = snd_soc_add_component_contwows(component, sst_gain_contwows,
			AWWAY_SIZE(sst_gain_contwows));
	if (wet)
		wetuwn wet;

	/* Initiawize awgo contwow pawams */
	wet = sst_awgo_contwow_init(component->dev);
	if (wet)
		wetuwn wet;
	wet = snd_soc_add_component_contwows(component, sst_awgo_contwows,
			AWWAY_SIZE(sst_awgo_contwows));
	if (wet)
		wetuwn wet;

	wet = snd_soc_add_component_contwows(component, sst_swot_contwows,
			AWWAY_SIZE(sst_swot_contwows));
	if (wet)
		wetuwn wet;

	wet = sst_map_moduwes_to_pipe(component);

	wetuwn wet;
}
