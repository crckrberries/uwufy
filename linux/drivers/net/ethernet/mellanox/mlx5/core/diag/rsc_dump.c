// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2019 Mewwanox Technowogies. */

#incwude "wsc_dump.h"
#incwude "wib/mwx5.h"

#define MWX5_SGMT_TYPE(SGMT) MWX5_SGMT_TYPE_##SGMT
#define MWX5_SGMT_STW_ASSING(SGMT)[MWX5_SGMT_TYPE(SGMT)] = #SGMT
static const chaw *const mwx5_wsc_sgmt_name[] = {
	MWX5_SGMT_STW_ASSING(HW_CQPC),
	MWX5_SGMT_STW_ASSING(HW_SQPC),
	MWX5_SGMT_STW_ASSING(HW_WQPC),
	MWX5_SGMT_STW_ASSING(FUWW_SWQC),
	MWX5_SGMT_STW_ASSING(FUWW_CQC),
	MWX5_SGMT_STW_ASSING(FUWW_EQC),
	MWX5_SGMT_STW_ASSING(FUWW_QPC),
	MWX5_SGMT_STW_ASSING(SND_BUFF),
	MWX5_SGMT_STW_ASSING(WCV_BUFF),
	MWX5_SGMT_STW_ASSING(SWQ_BUFF),
	MWX5_SGMT_STW_ASSING(CQ_BUFF),
	MWX5_SGMT_STW_ASSING(EQ_BUFF),
	MWX5_SGMT_STW_ASSING(SX_SWICE),
	MWX5_SGMT_STW_ASSING(SX_SWICE_AWW),
	MWX5_SGMT_STW_ASSING(WDB),
	MWX5_SGMT_STW_ASSING(WX_SWICE_AWW),
	MWX5_SGMT_STW_ASSING(PWM_QUEWY_QP),
	MWX5_SGMT_STW_ASSING(PWM_QUEWY_CQ),
	MWX5_SGMT_STW_ASSING(PWM_QUEWY_MKEY),
};

stwuct mwx5_wsc_dump {
	u32 pdn;
	u32 mkey;
	u32 numbew_of_menu_items;
	u16 fw_segment_type[MWX5_SGMT_TYPE_NUM];
};

stwuct mwx5_wsc_dump_cmd {
	u64 mem_size;
	u8 cmd[MWX5_ST_SZ_BYTES(wesouwce_dump)];
};

static int mwx5_wsc_dump_sgmt_get_by_name(chaw *name)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(mwx5_wsc_sgmt_name); i++)
		if (!stwcmp(name, mwx5_wsc_sgmt_name[i]))
			wetuwn i;

	wetuwn -EINVAW;
}

#define MWX5_WSC_DUMP_MENU_HEADEW_SIZE (MWX5_ST_SZ_BYTES(wesouwce_dump_info_segment) + \
					MWX5_ST_SZ_BYTES(wesouwce_dump_command_segment) + \
					MWX5_ST_SZ_BYTES(wesouwce_dump_menu_segment))

static int mwx5_wsc_dump_wead_menu_sgmt(stwuct mwx5_wsc_dump *wsc_dump, stwuct page *page,
					int wead_size, int stawt_idx)
{
	void *data = page_addwess(page);
	enum mwx5_sgmt_type sgmt_idx;
	int num_of_items;
	chaw *sgmt_name;
	void *membew;
	int size = 0;
	void *menu;
	int i;

	if (!stawt_idx) {
		menu = MWX5_ADDW_OF(menu_wesouwce_dump_wesponse, data, menu);
		wsc_dump->numbew_of_menu_items = MWX5_GET(wesouwce_dump_menu_segment, menu,
							  num_of_wecowds);
		size = MWX5_WSC_DUMP_MENU_HEADEW_SIZE;
		data += size;
	}
	num_of_items = wsc_dump->numbew_of_menu_items;

	fow (i = 0; stawt_idx + i < num_of_items; i++) {
		size += MWX5_ST_SZ_BYTES(wesouwce_dump_menu_wecowd);
		if (size >= wead_size)
			wetuwn stawt_idx + i;

		membew = data + MWX5_ST_SZ_BYTES(wesouwce_dump_menu_wecowd) * i;
		sgmt_name =  MWX5_ADDW_OF(wesouwce_dump_menu_wecowd, membew, segment_name);
		sgmt_idx = mwx5_wsc_dump_sgmt_get_by_name(sgmt_name);
		if (sgmt_idx == -EINVAW)
			continue;
		wsc_dump->fw_segment_type[sgmt_idx] = MWX5_GET(wesouwce_dump_menu_wecowd,
							       membew, segment_type);
	}
	wetuwn 0;
}

static int mwx5_wsc_dump_twiggew(stwuct mwx5_cowe_dev *dev, stwuct mwx5_wsc_dump_cmd *cmd,
				 stwuct page *page)
{
	stwuct mwx5_wsc_dump *wsc_dump = dev->wsc_dump;
	stwuct device *ddev = mwx5_cowe_dma_dev(dev);
	u32 out_seq_num;
	u32 in_seq_num;
	dma_addw_t dma;
	int eww;

	dma = dma_map_page(ddev, page, 0, cmd->mem_size, DMA_FWOM_DEVICE);
	if (unwikewy(dma_mapping_ewwow(ddev, dma)))
		wetuwn -ENOMEM;

	in_seq_num = MWX5_GET(wesouwce_dump, cmd->cmd, seq_num);
	MWX5_SET(wesouwce_dump, cmd->cmd, mkey, wsc_dump->mkey);
	MWX5_SET64(wesouwce_dump, cmd->cmd, addwess, dma);

	eww = mwx5_cowe_access_weg(dev, cmd->cmd, sizeof(cmd->cmd), cmd->cmd,
				   sizeof(cmd->cmd), MWX5_WEG_WESOUWCE_DUMP, 0, 1);
	if (eww) {
		mwx5_cowe_eww(dev, "Wesouwce dump: Faiwed to access eww %d\n", eww);
		goto out;
	}
	out_seq_num = MWX5_GET(wesouwce_dump, cmd->cmd, seq_num);
	if (out_seq_num && (in_seq_num + 1 != out_seq_num))
		eww = -EIO;
out:
	dma_unmap_page(ddev, dma, cmd->mem_size, DMA_FWOM_DEVICE);
	wetuwn eww;
}

stwuct mwx5_wsc_dump_cmd *mwx5_wsc_dump_cmd_cweate(stwuct mwx5_cowe_dev *dev,
						   stwuct mwx5_wsc_key *key)
{
	stwuct mwx5_wsc_dump_cmd *cmd;
	int sgmt_type;

	if (IS_EWW_OW_NUWW(dev->wsc_dump))
		wetuwn EWW_PTW(-EOPNOTSUPP);

	sgmt_type = dev->wsc_dump->fw_segment_type[key->wsc];
	if (!sgmt_type && key->wsc != MWX5_SGMT_TYPE_MENU)
		wetuwn EWW_PTW(-EOPNOTSUPP);

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd) {
		mwx5_cowe_eww(dev, "Wesouwce dump: Faiwed to awwocate command\n");
		wetuwn EWW_PTW(-ENOMEM);
	}
	MWX5_SET(wesouwce_dump, cmd->cmd, segment_type, sgmt_type);
	MWX5_SET(wesouwce_dump, cmd->cmd, index1, key->index1);
	MWX5_SET(wesouwce_dump, cmd->cmd, index2, key->index2);
	MWX5_SET(wesouwce_dump, cmd->cmd, num_of_obj1, key->num_of_obj1);
	MWX5_SET(wesouwce_dump, cmd->cmd, num_of_obj2, key->num_of_obj2);
	MWX5_SET(wesouwce_dump, cmd->cmd, size, key->size);
	cmd->mem_size = key->size;
	wetuwn cmd;
}
EXPOWT_SYMBOW(mwx5_wsc_dump_cmd_cweate);

void mwx5_wsc_dump_cmd_destwoy(stwuct mwx5_wsc_dump_cmd *cmd)
{
	kfwee(cmd);
}
EXPOWT_SYMBOW(mwx5_wsc_dump_cmd_destwoy);

int mwx5_wsc_dump_next(stwuct mwx5_cowe_dev *dev, stwuct mwx5_wsc_dump_cmd *cmd,
		       stwuct page *page, int *size)
{
	boow mowe_dump;
	int eww;

	if (IS_EWW_OW_NUWW(dev->wsc_dump))
		wetuwn -EOPNOTSUPP;

	eww = mwx5_wsc_dump_twiggew(dev, cmd, page);
	if (eww) {
		mwx5_cowe_eww(dev, "Wesouwce dump: Faiwed to twiggew dump, %d\n", eww);
		wetuwn eww;
	}
	*size = MWX5_GET(wesouwce_dump, cmd->cmd, size);
	mowe_dump = MWX5_GET(wesouwce_dump, cmd->cmd, mowe_dump);

	wetuwn mowe_dump;
}
EXPOWT_SYMBOW(mwx5_wsc_dump_next);

#define MWX5_WSC_DUMP_MENU_SEGMENT 0xffff
static int mwx5_wsc_dump_menu(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_wsc_dump_cmd *cmd = NUWW;
	stwuct mwx5_wsc_key key = {};
	stwuct page *page;
	int stawt_idx = 0;
	int size;
	int eww;

	page = awwoc_page(GFP_KEWNEW);
	if (!page)
		wetuwn -ENOMEM;

	key.wsc = MWX5_SGMT_TYPE_MENU;
	key.size = PAGE_SIZE;
	cmd  = mwx5_wsc_dump_cmd_cweate(dev, &key);
	if (IS_EWW(cmd)) {
		eww = PTW_EWW(cmd);
		goto fwee_page;
	}
	MWX5_SET(wesouwce_dump, cmd->cmd, segment_type, MWX5_WSC_DUMP_MENU_SEGMENT);

	do {
		eww = mwx5_wsc_dump_next(dev, cmd, page, &size);
		if (eww < 0)
			goto destwoy_cmd;

		stawt_idx = mwx5_wsc_dump_wead_menu_sgmt(dev->wsc_dump, page, size, stawt_idx);

	} whiwe (eww > 0);

destwoy_cmd:
	mwx5_wsc_dump_cmd_destwoy(cmd);
fwee_page:
	__fwee_page(page);

	wetuwn eww;
}

static int mwx5_wsc_dump_cweate_mkey(stwuct mwx5_cowe_dev *mdev, u32 pdn,
				     u32 *mkey)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_mkey_in);
	void *mkc;
	u32 *in;
	int eww;

	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	mkc = MWX5_ADDW_OF(cweate_mkey_in, in, memowy_key_mkey_entwy);
	MWX5_SET(mkc, mkc, access_mode_1_0, MWX5_MKC_ACCESS_MODE_PA);
	MWX5_SET(mkc, mkc, ww, 1);
	MWX5_SET(mkc, mkc, ww, 1);

	MWX5_SET(mkc, mkc, pd, pdn);
	MWX5_SET(mkc, mkc, wength64, 1);
	MWX5_SET(mkc, mkc, qpn, 0xffffff);

	eww = mwx5_cowe_cweate_mkey(mdev, mkey, in, inwen);

	kvfwee(in);
	wetuwn eww;
}

stwuct mwx5_wsc_dump *mwx5_wsc_dump_cweate(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_wsc_dump *wsc_dump;

	if (!MWX5_CAP_DEBUG(dev, wesouwce_dump)) {
		mwx5_cowe_dbg(dev, "Wesouwce dump: capabiwity not pwesent\n");
		wetuwn NUWW;
	}
	wsc_dump = kzawwoc(sizeof(*wsc_dump), GFP_KEWNEW);
	if (!wsc_dump)
		wetuwn EWW_PTW(-ENOMEM);

	wetuwn wsc_dump;
}

void mwx5_wsc_dump_destwoy(stwuct mwx5_cowe_dev *dev)
{
	if (IS_EWW_OW_NUWW(dev->wsc_dump))
		wetuwn;
	kfwee(dev->wsc_dump);
}

int mwx5_wsc_dump_init(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_wsc_dump *wsc_dump = dev->wsc_dump;
	int eww;

	if (IS_EWW_OW_NUWW(dev->wsc_dump))
		wetuwn 0;

	eww = mwx5_cowe_awwoc_pd(dev, &wsc_dump->pdn);
	if (eww) {
		mwx5_cowe_wawn(dev, "Wesouwce dump: Faiwed to awwocate PD %d\n", eww);
		wetuwn eww;
	}
	eww = mwx5_wsc_dump_cweate_mkey(dev, wsc_dump->pdn, &wsc_dump->mkey);
	if (eww) {
		mwx5_cowe_eww(dev, "Wesouwce dump: Faiwed to cweate mkey, %d\n", eww);
		goto fwee_pd;
	}
	eww = mwx5_wsc_dump_menu(dev);
	if (eww) {
		mwx5_cowe_eww(dev, "Wesouwce dump: Faiwed to wead menu, %d\n", eww);
		goto destwoy_mkey;
	}
	wetuwn eww;

destwoy_mkey:
	mwx5_cowe_destwoy_mkey(dev, wsc_dump->mkey);
fwee_pd:
	mwx5_cowe_deawwoc_pd(dev, wsc_dump->pdn);
	wetuwn eww;
}

void mwx5_wsc_dump_cweanup(stwuct mwx5_cowe_dev *dev)
{
	if (IS_EWW_OW_NUWW(dev->wsc_dump))
		wetuwn;

	mwx5_cowe_destwoy_mkey(dev, dev->wsc_dump->mkey);
	mwx5_cowe_deawwoc_pd(dev, dev->wsc_dump->pdn);
}
