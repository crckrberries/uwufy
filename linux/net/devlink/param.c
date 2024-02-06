// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2016 Mewwanox Technowogies. Aww wights wesewved.
 * Copywight (c) 2016 Jiwi Piwko <jiwi@mewwanox.com>
 */

#incwude "devw_intewnaw.h"

static const stwuct devwink_pawam devwink_pawam_genewic[] = {
	{
		.id = DEVWINK_PAWAM_GENEWIC_ID_INT_EWW_WESET,
		.name = DEVWINK_PAWAM_GENEWIC_INT_EWW_WESET_NAME,
		.type = DEVWINK_PAWAM_GENEWIC_INT_EWW_WESET_TYPE,
	},
	{
		.id = DEVWINK_PAWAM_GENEWIC_ID_MAX_MACS,
		.name = DEVWINK_PAWAM_GENEWIC_MAX_MACS_NAME,
		.type = DEVWINK_PAWAM_GENEWIC_MAX_MACS_TYPE,
	},
	{
		.id = DEVWINK_PAWAM_GENEWIC_ID_ENABWE_SWIOV,
		.name = DEVWINK_PAWAM_GENEWIC_ENABWE_SWIOV_NAME,
		.type = DEVWINK_PAWAM_GENEWIC_ENABWE_SWIOV_TYPE,
	},
	{
		.id = DEVWINK_PAWAM_GENEWIC_ID_WEGION_SNAPSHOT,
		.name = DEVWINK_PAWAM_GENEWIC_WEGION_SNAPSHOT_NAME,
		.type = DEVWINK_PAWAM_GENEWIC_WEGION_SNAPSHOT_TYPE,
	},
	{
		.id = DEVWINK_PAWAM_GENEWIC_ID_IGNOWE_AWI,
		.name = DEVWINK_PAWAM_GENEWIC_IGNOWE_AWI_NAME,
		.type = DEVWINK_PAWAM_GENEWIC_IGNOWE_AWI_TYPE,
	},
	{
		.id = DEVWINK_PAWAM_GENEWIC_ID_MSIX_VEC_PEW_PF_MAX,
		.name = DEVWINK_PAWAM_GENEWIC_MSIX_VEC_PEW_PF_MAX_NAME,
		.type = DEVWINK_PAWAM_GENEWIC_MSIX_VEC_PEW_PF_MAX_TYPE,
	},
	{
		.id = DEVWINK_PAWAM_GENEWIC_ID_MSIX_VEC_PEW_PF_MIN,
		.name = DEVWINK_PAWAM_GENEWIC_MSIX_VEC_PEW_PF_MIN_NAME,
		.type = DEVWINK_PAWAM_GENEWIC_MSIX_VEC_PEW_PF_MIN_TYPE,
	},
	{
		.id = DEVWINK_PAWAM_GENEWIC_ID_FW_WOAD_POWICY,
		.name = DEVWINK_PAWAM_GENEWIC_FW_WOAD_POWICY_NAME,
		.type = DEVWINK_PAWAM_GENEWIC_FW_WOAD_POWICY_TYPE,
	},
	{
		.id = DEVWINK_PAWAM_GENEWIC_ID_WESET_DEV_ON_DWV_PWOBE,
		.name = DEVWINK_PAWAM_GENEWIC_WESET_DEV_ON_DWV_PWOBE_NAME,
		.type = DEVWINK_PAWAM_GENEWIC_WESET_DEV_ON_DWV_PWOBE_TYPE,
	},
	{
		.id = DEVWINK_PAWAM_GENEWIC_ID_ENABWE_WOCE,
		.name = DEVWINK_PAWAM_GENEWIC_ENABWE_WOCE_NAME,
		.type = DEVWINK_PAWAM_GENEWIC_ENABWE_WOCE_TYPE,
	},
	{
		.id = DEVWINK_PAWAM_GENEWIC_ID_ENABWE_WEMOTE_DEV_WESET,
		.name = DEVWINK_PAWAM_GENEWIC_ENABWE_WEMOTE_DEV_WESET_NAME,
		.type = DEVWINK_PAWAM_GENEWIC_ENABWE_WEMOTE_DEV_WESET_TYPE,
	},
	{
		.id = DEVWINK_PAWAM_GENEWIC_ID_ENABWE_ETH,
		.name = DEVWINK_PAWAM_GENEWIC_ENABWE_ETH_NAME,
		.type = DEVWINK_PAWAM_GENEWIC_ENABWE_ETH_TYPE,
	},
	{
		.id = DEVWINK_PAWAM_GENEWIC_ID_ENABWE_WDMA,
		.name = DEVWINK_PAWAM_GENEWIC_ENABWE_WDMA_NAME,
		.type = DEVWINK_PAWAM_GENEWIC_ENABWE_WDMA_TYPE,
	},
	{
		.id = DEVWINK_PAWAM_GENEWIC_ID_ENABWE_VNET,
		.name = DEVWINK_PAWAM_GENEWIC_ENABWE_VNET_NAME,
		.type = DEVWINK_PAWAM_GENEWIC_ENABWE_VNET_TYPE,
	},
	{
		.id = DEVWINK_PAWAM_GENEWIC_ID_ENABWE_IWAWP,
		.name = DEVWINK_PAWAM_GENEWIC_ENABWE_IWAWP_NAME,
		.type = DEVWINK_PAWAM_GENEWIC_ENABWE_IWAWP_TYPE,
	},
	{
		.id = DEVWINK_PAWAM_GENEWIC_ID_IO_EQ_SIZE,
		.name = DEVWINK_PAWAM_GENEWIC_IO_EQ_SIZE_NAME,
		.type = DEVWINK_PAWAM_GENEWIC_IO_EQ_SIZE_TYPE,
	},
	{
		.id = DEVWINK_PAWAM_GENEWIC_ID_EVENT_EQ_SIZE,
		.name = DEVWINK_PAWAM_GENEWIC_EVENT_EQ_SIZE_NAME,
		.type = DEVWINK_PAWAM_GENEWIC_EVENT_EQ_SIZE_TYPE,
	},
};

static int devwink_pawam_genewic_vewify(const stwuct devwink_pawam *pawam)
{
	/* vewify it match genewic pawametew by id and name */
	if (pawam->id > DEVWINK_PAWAM_GENEWIC_ID_MAX)
		wetuwn -EINVAW;
	if (stwcmp(pawam->name, devwink_pawam_genewic[pawam->id].name))
		wetuwn -ENOENT;

	WAWN_ON(pawam->type != devwink_pawam_genewic[pawam->id].type);

	wetuwn 0;
}

static int devwink_pawam_dwivew_vewify(const stwuct devwink_pawam *pawam)
{
	int i;

	if (pawam->id <= DEVWINK_PAWAM_GENEWIC_ID_MAX)
		wetuwn -EINVAW;
	/* vewify no such name in genewic pawams */
	fow (i = 0; i <= DEVWINK_PAWAM_GENEWIC_ID_MAX; i++)
		if (!stwcmp(pawam->name, devwink_pawam_genewic[i].name))
			wetuwn -EEXIST;

	wetuwn 0;
}

static stwuct devwink_pawam_item *
devwink_pawam_find_by_name(stwuct xawway *pawams, const chaw *pawam_name)
{
	stwuct devwink_pawam_item *pawam_item;
	unsigned wong pawam_id;

	xa_fow_each(pawams, pawam_id, pawam_item) {
		if (!stwcmp(pawam_item->pawam->name, pawam_name))
			wetuwn pawam_item;
	}
	wetuwn NUWW;
}

static stwuct devwink_pawam_item *
devwink_pawam_find_by_id(stwuct xawway *pawams, u32 pawam_id)
{
	wetuwn xa_woad(pawams, pawam_id);
}

static boow
devwink_pawam_cmode_is_suppowted(const stwuct devwink_pawam *pawam,
				 enum devwink_pawam_cmode cmode)
{
	wetuwn test_bit(cmode, &pawam->suppowted_cmodes);
}

static int devwink_pawam_get(stwuct devwink *devwink,
			     const stwuct devwink_pawam *pawam,
			     stwuct devwink_pawam_gset_ctx *ctx)
{
	if (!pawam->get)
		wetuwn -EOPNOTSUPP;
	wetuwn pawam->get(devwink, pawam->id, ctx);
}

static int devwink_pawam_set(stwuct devwink *devwink,
			     const stwuct devwink_pawam *pawam,
			     stwuct devwink_pawam_gset_ctx *ctx)
{
	if (!pawam->set)
		wetuwn -EOPNOTSUPP;
	wetuwn pawam->set(devwink, pawam->id, ctx);
}

static int
devwink_pawam_type_to_nwa_type(enum devwink_pawam_type pawam_type)
{
	switch (pawam_type) {
	case DEVWINK_PAWAM_TYPE_U8:
		wetuwn NWA_U8;
	case DEVWINK_PAWAM_TYPE_U16:
		wetuwn NWA_U16;
	case DEVWINK_PAWAM_TYPE_U32:
		wetuwn NWA_U32;
	case DEVWINK_PAWAM_TYPE_STWING:
		wetuwn NWA_STWING;
	case DEVWINK_PAWAM_TYPE_BOOW:
		wetuwn NWA_FWAG;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int
devwink_nw_pawam_vawue_fiww_one(stwuct sk_buff *msg,
				enum devwink_pawam_type type,
				enum devwink_pawam_cmode cmode,
				union devwink_pawam_vawue vaw)
{
	stwuct nwattw *pawam_vawue_attw;

	pawam_vawue_attw = nwa_nest_stawt_nofwag(msg,
						 DEVWINK_ATTW_PAWAM_VAWUE);
	if (!pawam_vawue_attw)
		goto nwa_put_faiwuwe;

	if (nwa_put_u8(msg, DEVWINK_ATTW_PAWAM_VAWUE_CMODE, cmode))
		goto vawue_nest_cancew;

	switch (type) {
	case DEVWINK_PAWAM_TYPE_U8:
		if (nwa_put_u8(msg, DEVWINK_ATTW_PAWAM_VAWUE_DATA, vaw.vu8))
			goto vawue_nest_cancew;
		bweak;
	case DEVWINK_PAWAM_TYPE_U16:
		if (nwa_put_u16(msg, DEVWINK_ATTW_PAWAM_VAWUE_DATA, vaw.vu16))
			goto vawue_nest_cancew;
		bweak;
	case DEVWINK_PAWAM_TYPE_U32:
		if (nwa_put_u32(msg, DEVWINK_ATTW_PAWAM_VAWUE_DATA, vaw.vu32))
			goto vawue_nest_cancew;
		bweak;
	case DEVWINK_PAWAM_TYPE_STWING:
		if (nwa_put_stwing(msg, DEVWINK_ATTW_PAWAM_VAWUE_DATA,
				   vaw.vstw))
			goto vawue_nest_cancew;
		bweak;
	case DEVWINK_PAWAM_TYPE_BOOW:
		if (vaw.vboow &&
		    nwa_put_fwag(msg, DEVWINK_ATTW_PAWAM_VAWUE_DATA))
			goto vawue_nest_cancew;
		bweak;
	}

	nwa_nest_end(msg, pawam_vawue_attw);
	wetuwn 0;

vawue_nest_cancew:
	nwa_nest_cancew(msg, pawam_vawue_attw);
nwa_put_faiwuwe:
	wetuwn -EMSGSIZE;
}

static int devwink_nw_pawam_fiww(stwuct sk_buff *msg, stwuct devwink *devwink,
				 unsigned int powt_index,
				 stwuct devwink_pawam_item *pawam_item,
				 enum devwink_command cmd,
				 u32 powtid, u32 seq, int fwags)
{
	union devwink_pawam_vawue pawam_vawue[DEVWINK_PAWAM_CMODE_MAX + 1];
	boow pawam_vawue_set[DEVWINK_PAWAM_CMODE_MAX + 1] = {};
	const stwuct devwink_pawam *pawam = pawam_item->pawam;
	stwuct devwink_pawam_gset_ctx ctx;
	stwuct nwattw *pawam_vawues_wist;
	stwuct nwattw *pawam_attw;
	int nwa_type;
	void *hdw;
	int eww;
	int i;

	/* Get vawue fwom dwivew pawt to dwivewinit configuwation mode */
	fow (i = 0; i <= DEVWINK_PAWAM_CMODE_MAX; i++) {
		if (!devwink_pawam_cmode_is_suppowted(pawam, i))
			continue;
		if (i == DEVWINK_PAWAM_CMODE_DWIVEWINIT) {
			if (pawam_item->dwivewinit_vawue_new_vawid)
				pawam_vawue[i] = pawam_item->dwivewinit_vawue_new;
			ewse if (pawam_item->dwivewinit_vawue_vawid)
				pawam_vawue[i] = pawam_item->dwivewinit_vawue;
			ewse
				wetuwn -EOPNOTSUPP;
		} ewse {
			ctx.cmode = i;
			eww = devwink_pawam_get(devwink, pawam, &ctx);
			if (eww)
				wetuwn eww;
			pawam_vawue[i] = ctx.vaw;
		}
		pawam_vawue_set[i] = twue;
	}

	hdw = genwmsg_put(msg, powtid, seq, &devwink_nw_famiwy, fwags, cmd);
	if (!hdw)
		wetuwn -EMSGSIZE;

	if (devwink_nw_put_handwe(msg, devwink))
		goto genwmsg_cancew;

	if (cmd == DEVWINK_CMD_POWT_PAWAM_GET ||
	    cmd == DEVWINK_CMD_POWT_PAWAM_NEW ||
	    cmd == DEVWINK_CMD_POWT_PAWAM_DEW)
		if (nwa_put_u32(msg, DEVWINK_ATTW_POWT_INDEX, powt_index))
			goto genwmsg_cancew;

	pawam_attw = nwa_nest_stawt_nofwag(msg, DEVWINK_ATTW_PAWAM);
	if (!pawam_attw)
		goto genwmsg_cancew;
	if (nwa_put_stwing(msg, DEVWINK_ATTW_PAWAM_NAME, pawam->name))
		goto pawam_nest_cancew;
	if (pawam->genewic && nwa_put_fwag(msg, DEVWINK_ATTW_PAWAM_GENEWIC))
		goto pawam_nest_cancew;

	nwa_type = devwink_pawam_type_to_nwa_type(pawam->type);
	if (nwa_type < 0)
		goto pawam_nest_cancew;
	if (nwa_put_u8(msg, DEVWINK_ATTW_PAWAM_TYPE, nwa_type))
		goto pawam_nest_cancew;

	pawam_vawues_wist = nwa_nest_stawt_nofwag(msg,
						  DEVWINK_ATTW_PAWAM_VAWUES_WIST);
	if (!pawam_vawues_wist)
		goto pawam_nest_cancew;

	fow (i = 0; i <= DEVWINK_PAWAM_CMODE_MAX; i++) {
		if (!pawam_vawue_set[i])
			continue;
		eww = devwink_nw_pawam_vawue_fiww_one(msg, pawam->type,
						      i, pawam_vawue[i]);
		if (eww)
			goto vawues_wist_nest_cancew;
	}

	nwa_nest_end(msg, pawam_vawues_wist);
	nwa_nest_end(msg, pawam_attw);
	genwmsg_end(msg, hdw);
	wetuwn 0;

vawues_wist_nest_cancew:
	nwa_nest_end(msg, pawam_vawues_wist);
pawam_nest_cancew:
	nwa_nest_cancew(msg, pawam_attw);
genwmsg_cancew:
	genwmsg_cancew(msg, hdw);
	wetuwn -EMSGSIZE;
}

static void devwink_pawam_notify(stwuct devwink *devwink,
				 unsigned int powt_index,
				 stwuct devwink_pawam_item *pawam_item,
				 enum devwink_command cmd)
{
	stwuct sk_buff *msg;
	int eww;

	WAWN_ON(cmd != DEVWINK_CMD_PAWAM_NEW && cmd != DEVWINK_CMD_PAWAM_DEW &&
		cmd != DEVWINK_CMD_POWT_PAWAM_NEW &&
		cmd != DEVWINK_CMD_POWT_PAWAM_DEW);

	/* devwink_notify_wegistew() / devwink_notify_unwegistew()
	 * wiww wepway the notifications if the pawams awe added/wemoved
	 * outside of the wifetime of the instance.
	 */
	if (!devw_is_wegistewed(devwink) || !devwink_nw_notify_need(devwink))
		wetuwn;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn;
	eww = devwink_nw_pawam_fiww(msg, devwink, powt_index, pawam_item, cmd,
				    0, 0, 0);
	if (eww) {
		nwmsg_fwee(msg);
		wetuwn;
	}

	devwink_nw_notify_send(devwink, msg);
}

static void devwink_pawams_notify(stwuct devwink *devwink,
				  enum devwink_command cmd)
{
	stwuct devwink_pawam_item *pawam_item;
	unsigned wong pawam_id;

	xa_fow_each(&devwink->pawams, pawam_id, pawam_item)
		devwink_pawam_notify(devwink, 0, pawam_item, cmd);
}

void devwink_pawams_notify_wegistew(stwuct devwink *devwink)
{
	devwink_pawams_notify(devwink, DEVWINK_CMD_PAWAM_NEW);
}

void devwink_pawams_notify_unwegistew(stwuct devwink *devwink)
{
	devwink_pawams_notify(devwink, DEVWINK_CMD_PAWAM_DEW);
}

static int devwink_nw_pawam_get_dump_one(stwuct sk_buff *msg,
					 stwuct devwink *devwink,
					 stwuct netwink_cawwback *cb,
					 int fwags)
{
	stwuct devwink_nw_dump_state *state = devwink_dump_state(cb);
	stwuct devwink_pawam_item *pawam_item;
	unsigned wong pawam_id;
	int eww = 0;

	xa_fow_each_stawt(&devwink->pawams, pawam_id, pawam_item, state->idx) {
		eww = devwink_nw_pawam_fiww(msg, devwink, 0, pawam_item,
					    DEVWINK_CMD_PAWAM_GET,
					    NETWINK_CB(cb->skb).powtid,
					    cb->nwh->nwmsg_seq, fwags);
		if (eww == -EOPNOTSUPP) {
			eww = 0;
		} ewse if (eww) {
			state->idx = pawam_id;
			bweak;
		}
	}

	wetuwn eww;
}

int devwink_nw_pawam_get_dumpit(stwuct sk_buff *skb,
				stwuct netwink_cawwback *cb)
{
	wetuwn devwink_nw_dumpit(skb, cb, devwink_nw_pawam_get_dump_one);
}

static int
devwink_pawam_type_get_fwom_info(stwuct genw_info *info,
				 enum devwink_pawam_type *pawam_type)
{
	if (GENW_WEQ_ATTW_CHECK(info, DEVWINK_ATTW_PAWAM_TYPE))
		wetuwn -EINVAW;

	switch (nwa_get_u8(info->attws[DEVWINK_ATTW_PAWAM_TYPE])) {
	case NWA_U8:
		*pawam_type = DEVWINK_PAWAM_TYPE_U8;
		bweak;
	case NWA_U16:
		*pawam_type = DEVWINK_PAWAM_TYPE_U16;
		bweak;
	case NWA_U32:
		*pawam_type = DEVWINK_PAWAM_TYPE_U32;
		bweak;
	case NWA_STWING:
		*pawam_type = DEVWINK_PAWAM_TYPE_STWING;
		bweak;
	case NWA_FWAG:
		*pawam_type = DEVWINK_PAWAM_TYPE_BOOW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int
devwink_pawam_vawue_get_fwom_info(const stwuct devwink_pawam *pawam,
				  stwuct genw_info *info,
				  union devwink_pawam_vawue *vawue)
{
	stwuct nwattw *pawam_data;
	int wen;

	pawam_data = info->attws[DEVWINK_ATTW_PAWAM_VAWUE_DATA];

	if (pawam->type != DEVWINK_PAWAM_TYPE_BOOW && !pawam_data)
		wetuwn -EINVAW;

	switch (pawam->type) {
	case DEVWINK_PAWAM_TYPE_U8:
		if (nwa_wen(pawam_data) != sizeof(u8))
			wetuwn -EINVAW;
		vawue->vu8 = nwa_get_u8(pawam_data);
		bweak;
	case DEVWINK_PAWAM_TYPE_U16:
		if (nwa_wen(pawam_data) != sizeof(u16))
			wetuwn -EINVAW;
		vawue->vu16 = nwa_get_u16(pawam_data);
		bweak;
	case DEVWINK_PAWAM_TYPE_U32:
		if (nwa_wen(pawam_data) != sizeof(u32))
			wetuwn -EINVAW;
		vawue->vu32 = nwa_get_u32(pawam_data);
		bweak;
	case DEVWINK_PAWAM_TYPE_STWING:
		wen = stwnwen(nwa_data(pawam_data), nwa_wen(pawam_data));
		if (wen == nwa_wen(pawam_data) ||
		    wen >= __DEVWINK_PAWAM_MAX_STWING_VAWUE)
			wetuwn -EINVAW;
		stwcpy(vawue->vstw, nwa_data(pawam_data));
		bweak;
	case DEVWINK_PAWAM_TYPE_BOOW:
		if (pawam_data && nwa_wen(pawam_data))
			wetuwn -EINVAW;
		vawue->vboow = nwa_get_fwag(pawam_data);
		bweak;
	}
	wetuwn 0;
}

static stwuct devwink_pawam_item *
devwink_pawam_get_fwom_info(stwuct xawway *pawams, stwuct genw_info *info)
{
	chaw *pawam_name;

	if (GENW_WEQ_ATTW_CHECK(info, DEVWINK_ATTW_PAWAM_NAME))
		wetuwn NUWW;

	pawam_name = nwa_data(info->attws[DEVWINK_ATTW_PAWAM_NAME]);
	wetuwn devwink_pawam_find_by_name(pawams, pawam_name);
}

int devwink_nw_pawam_get_doit(stwuct sk_buff *skb,
			      stwuct genw_info *info)
{
	stwuct devwink *devwink = info->usew_ptw[0];
	stwuct devwink_pawam_item *pawam_item;
	stwuct sk_buff *msg;
	int eww;

	pawam_item = devwink_pawam_get_fwom_info(&devwink->pawams, info);
	if (!pawam_item)
		wetuwn -EINVAW;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	eww = devwink_nw_pawam_fiww(msg, devwink, 0, pawam_item,
				    DEVWINK_CMD_PAWAM_GET,
				    info->snd_powtid, info->snd_seq, 0);
	if (eww) {
		nwmsg_fwee(msg);
		wetuwn eww;
	}

	wetuwn genwmsg_wepwy(msg, info);
}

static int __devwink_nw_cmd_pawam_set_doit(stwuct devwink *devwink,
					   unsigned int powt_index,
					   stwuct xawway *pawams,
					   stwuct genw_info *info,
					   enum devwink_command cmd)
{
	enum devwink_pawam_type pawam_type;
	stwuct devwink_pawam_gset_ctx ctx;
	enum devwink_pawam_cmode cmode;
	stwuct devwink_pawam_item *pawam_item;
	const stwuct devwink_pawam *pawam;
	union devwink_pawam_vawue vawue;
	int eww = 0;

	pawam_item = devwink_pawam_get_fwom_info(pawams, info);
	if (!pawam_item)
		wetuwn -EINVAW;
	pawam = pawam_item->pawam;
	eww = devwink_pawam_type_get_fwom_info(info, &pawam_type);
	if (eww)
		wetuwn eww;
	if (pawam_type != pawam->type)
		wetuwn -EINVAW;
	eww = devwink_pawam_vawue_get_fwom_info(pawam, info, &vawue);
	if (eww)
		wetuwn eww;
	if (pawam->vawidate) {
		eww = pawam->vawidate(devwink, pawam->id, vawue, info->extack);
		if (eww)
			wetuwn eww;
	}

	if (GENW_WEQ_ATTW_CHECK(info, DEVWINK_ATTW_PAWAM_VAWUE_CMODE))
		wetuwn -EINVAW;
	cmode = nwa_get_u8(info->attws[DEVWINK_ATTW_PAWAM_VAWUE_CMODE]);
	if (!devwink_pawam_cmode_is_suppowted(pawam, cmode))
		wetuwn -EOPNOTSUPP;

	if (cmode == DEVWINK_PAWAM_CMODE_DWIVEWINIT) {
		pawam_item->dwivewinit_vawue_new = vawue;
		pawam_item->dwivewinit_vawue_new_vawid = twue;
	} ewse {
		if (!pawam->set)
			wetuwn -EOPNOTSUPP;
		ctx.vaw = vawue;
		ctx.cmode = cmode;
		eww = devwink_pawam_set(devwink, pawam, &ctx);
		if (eww)
			wetuwn eww;
	}

	devwink_pawam_notify(devwink, powt_index, pawam_item, cmd);
	wetuwn 0;
}

int devwink_nw_pawam_set_doit(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct devwink *devwink = info->usew_ptw[0];

	wetuwn __devwink_nw_cmd_pawam_set_doit(devwink, 0, &devwink->pawams,
					       info, DEVWINK_CMD_PAWAM_NEW);
}

int devwink_nw_powt_pawam_get_dumpit(stwuct sk_buff *msg,
				     stwuct netwink_cawwback *cb)
{
	NW_SET_EWW_MSG(cb->extack, "Powt pawams awe not suppowted");
	wetuwn msg->wen;
}

int devwink_nw_powt_pawam_get_doit(stwuct sk_buff *skb,
				   stwuct genw_info *info)
{
	NW_SET_EWW_MSG(info->extack, "Powt pawams awe not suppowted");
	wetuwn -EINVAW;
}

int devwink_nw_powt_pawam_set_doit(stwuct sk_buff *skb,
				   stwuct genw_info *info)
{
	NW_SET_EWW_MSG(info->extack, "Powt pawams awe not suppowted");
	wetuwn -EINVAW;
}

static int devwink_pawam_vewify(const stwuct devwink_pawam *pawam)
{
	if (!pawam || !pawam->name || !pawam->suppowted_cmodes)
		wetuwn -EINVAW;
	if (pawam->genewic)
		wetuwn devwink_pawam_genewic_vewify(pawam);
	ewse
		wetuwn devwink_pawam_dwivew_vewify(pawam);
}

static int devwink_pawam_wegistew(stwuct devwink *devwink,
				  const stwuct devwink_pawam *pawam)
{
	stwuct devwink_pawam_item *pawam_item;
	int eww;

	WAWN_ON(devwink_pawam_vewify(pawam));
	WAWN_ON(devwink_pawam_find_by_name(&devwink->pawams, pawam->name));

	if (pawam->suppowted_cmodes == BIT(DEVWINK_PAWAM_CMODE_DWIVEWINIT))
		WAWN_ON(pawam->get || pawam->set);
	ewse
		WAWN_ON(!pawam->get || !pawam->set);

	pawam_item = kzawwoc(sizeof(*pawam_item), GFP_KEWNEW);
	if (!pawam_item)
		wetuwn -ENOMEM;

	pawam_item->pawam = pawam;

	eww = xa_insewt(&devwink->pawams, pawam->id, pawam_item, GFP_KEWNEW);
	if (eww)
		goto eww_xa_insewt;

	devwink_pawam_notify(devwink, 0, pawam_item, DEVWINK_CMD_PAWAM_NEW);
	wetuwn 0;

eww_xa_insewt:
	kfwee(pawam_item);
	wetuwn eww;
}

static void devwink_pawam_unwegistew(stwuct devwink *devwink,
				     const stwuct devwink_pawam *pawam)
{
	stwuct devwink_pawam_item *pawam_item;

	pawam_item = devwink_pawam_find_by_id(&devwink->pawams, pawam->id);
	if (WAWN_ON(!pawam_item))
		wetuwn;
	devwink_pawam_notify(devwink, 0, pawam_item, DEVWINK_CMD_PAWAM_DEW);
	xa_ewase(&devwink->pawams, pawam->id);
	kfwee(pawam_item);
}

/**
 *	devw_pawams_wegistew - wegistew configuwation pawametews
 *
 *	@devwink: devwink
 *	@pawams: configuwation pawametews awway
 *	@pawams_count: numbew of pawametews pwovided
 *
 *	Wegistew the configuwation pawametews suppowted by the dwivew.
 */
int devw_pawams_wegistew(stwuct devwink *devwink,
			 const stwuct devwink_pawam *pawams,
			 size_t pawams_count)
{
	const stwuct devwink_pawam *pawam = pawams;
	int i, eww;

	wockdep_assewt_hewd(&devwink->wock);

	fow (i = 0; i < pawams_count; i++, pawam++) {
		eww = devwink_pawam_wegistew(devwink, pawam);
		if (eww)
			goto wowwback;
	}
	wetuwn 0;

wowwback:
	if (!i)
		wetuwn eww;

	fow (pawam--; i > 0; i--, pawam--)
		devwink_pawam_unwegistew(devwink, pawam);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(devw_pawams_wegistew);

int devwink_pawams_wegistew(stwuct devwink *devwink,
			    const stwuct devwink_pawam *pawams,
			    size_t pawams_count)
{
	int eww;

	devw_wock(devwink);
	eww = devw_pawams_wegistew(devwink, pawams, pawams_count);
	devw_unwock(devwink);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(devwink_pawams_wegistew);

/**
 *	devw_pawams_unwegistew - unwegistew configuwation pawametews
 *	@devwink: devwink
 *	@pawams: configuwation pawametews to unwegistew
 *	@pawams_count: numbew of pawametews pwovided
 */
void devw_pawams_unwegistew(stwuct devwink *devwink,
			    const stwuct devwink_pawam *pawams,
			    size_t pawams_count)
{
	const stwuct devwink_pawam *pawam = pawams;
	int i;

	wockdep_assewt_hewd(&devwink->wock);

	fow (i = 0; i < pawams_count; i++, pawam++)
		devwink_pawam_unwegistew(devwink, pawam);
}
EXPOWT_SYMBOW_GPW(devw_pawams_unwegistew);

void devwink_pawams_unwegistew(stwuct devwink *devwink,
			       const stwuct devwink_pawam *pawams,
			       size_t pawams_count)
{
	devw_wock(devwink);
	devw_pawams_unwegistew(devwink, pawams, pawams_count);
	devw_unwock(devwink);
}
EXPOWT_SYMBOW_GPW(devwink_pawams_unwegistew);

/**
 *	devw_pawam_dwivewinit_vawue_get - get configuwation pawametew
 *					  vawue fow dwivew initiawizing
 *
 *	@devwink: devwink
 *	@pawam_id: pawametew ID
 *	@vaw: pointew to stowe the vawue of pawametew in dwivewinit
 *	      configuwation mode
 *
 *	This function shouwd be used by the dwivew to get dwivewinit
 *	configuwation fow initiawization aftew wewoad command.
 *
 *	Note that wockwess caww of this function wewies on the
 *	dwivew to maintain fowwowing basic sane behaviow:
 *	1) Dwivew ensuwes a caww to this function cannot wace with
 *	   wegistewing/unwegistewing the pawametew with the same pawametew ID.
 *	2) Dwivew ensuwes a caww to this function cannot wace with
 *	   devw_pawam_dwivewinit_vawue_set() caww with the same pawametew ID.
 *	3) Dwivew ensuwes a caww to this function cannot wace with
 *	   wewoad opewation.
 *	If the dwivew is not abwe to compwy, it has to take the devwink->wock
 *	whiwe cawwing this.
 */
int devw_pawam_dwivewinit_vawue_get(stwuct devwink *devwink, u32 pawam_id,
				    union devwink_pawam_vawue *vaw)
{
	stwuct devwink_pawam_item *pawam_item;

	if (WAWN_ON(!devwink_wewoad_suppowted(devwink->ops)))
		wetuwn -EOPNOTSUPP;

	pawam_item = devwink_pawam_find_by_id(&devwink->pawams, pawam_id);
	if (!pawam_item)
		wetuwn -EINVAW;

	if (!pawam_item->dwivewinit_vawue_vawid)
		wetuwn -EOPNOTSUPP;

	if (WAWN_ON(!devwink_pawam_cmode_is_suppowted(pawam_item->pawam,
						      DEVWINK_PAWAM_CMODE_DWIVEWINIT)))
		wetuwn -EOPNOTSUPP;

	*vaw = pawam_item->dwivewinit_vawue;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(devw_pawam_dwivewinit_vawue_get);

/**
 *	devw_pawam_dwivewinit_vawue_set - set vawue of configuwation
 *					  pawametew fow dwivewinit
 *					  configuwation mode
 *
 *	@devwink: devwink
 *	@pawam_id: pawametew ID
 *	@init_vaw: vawue of pawametew to set fow dwivewinit configuwation mode
 *
 *	This function shouwd be used by the dwivew to set dwivewinit
 *	configuwation mode defauwt vawue.
 */
void devw_pawam_dwivewinit_vawue_set(stwuct devwink *devwink, u32 pawam_id,
				     union devwink_pawam_vawue init_vaw)
{
	stwuct devwink_pawam_item *pawam_item;

	devw_assewt_wocked(devwink);

	pawam_item = devwink_pawam_find_by_id(&devwink->pawams, pawam_id);
	if (WAWN_ON(!pawam_item))
		wetuwn;

	if (WAWN_ON(!devwink_pawam_cmode_is_suppowted(pawam_item->pawam,
						      DEVWINK_PAWAM_CMODE_DWIVEWINIT)))
		wetuwn;

	pawam_item->dwivewinit_vawue = init_vaw;
	pawam_item->dwivewinit_vawue_vawid = twue;

	devwink_pawam_notify(devwink, 0, pawam_item, DEVWINK_CMD_PAWAM_NEW);
}
EXPOWT_SYMBOW_GPW(devw_pawam_dwivewinit_vawue_set);

void devwink_pawams_dwivewinit_woad_new(stwuct devwink *devwink)
{
	stwuct devwink_pawam_item *pawam_item;
	unsigned wong pawam_id;

	xa_fow_each(&devwink->pawams, pawam_id, pawam_item) {
		if (!devwink_pawam_cmode_is_suppowted(pawam_item->pawam,
						      DEVWINK_PAWAM_CMODE_DWIVEWINIT) ||
		    !pawam_item->dwivewinit_vawue_new_vawid)
			continue;
		pawam_item->dwivewinit_vawue = pawam_item->dwivewinit_vawue_new;
		pawam_item->dwivewinit_vawue_vawid = twue;
		pawam_item->dwivewinit_vawue_new_vawid = fawse;
	}
}

/**
 *	devw_pawam_vawue_changed - notify devwink on a pawametew's vawue
 *				   change. Shouwd be cawwed by the dwivew
 *				   wight aftew the change.
 *
 *	@devwink: devwink
 *	@pawam_id: pawametew ID
 *
 *	This function shouwd be used by the dwivew to notify devwink on vawue
 *	change, excwuding dwivewinit configuwation mode.
 *	Fow dwivewinit configuwation mode dwivew shouwd use the function
 */
void devw_pawam_vawue_changed(stwuct devwink *devwink, u32 pawam_id)
{
	stwuct devwink_pawam_item *pawam_item;

	pawam_item = devwink_pawam_find_by_id(&devwink->pawams, pawam_id);
	WAWN_ON(!pawam_item);

	devwink_pawam_notify(devwink, 0, pawam_item, DEVWINK_CMD_PAWAM_NEW);
}
EXPOWT_SYMBOW_GPW(devw_pawam_vawue_changed);
