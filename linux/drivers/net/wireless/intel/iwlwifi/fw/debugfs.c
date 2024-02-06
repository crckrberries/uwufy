// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2012-2014, 2018-2023 Intew Cowpowation
 * Copywight (C) 2013-2015 Intew Mobiwe Communications GmbH
 * Copywight (C) 2016-2017 Intew Deutschwand GmbH
 */
#incwude "api/commands.h"
#incwude "debugfs.h"
#incwude "dbg.h"
#incwude <winux/seq_fiwe.h>

#define FWWT_DEBUGFS_OPEN_WWAPPEW(name, bufwen, awgtype)		\
stwuct dbgfs_##name##_data {						\
	awgtype *awg;							\
	boow wead_done;							\
	ssize_t wwen;							\
	chaw wbuf[bufwen];						\
};									\
static int _iww_dbgfs_##name##_open(stwuct inode *inode,		\
				    stwuct fiwe *fiwe)			\
{									\
	stwuct dbgfs_##name##_data *data;				\
									\
	data = kzawwoc(sizeof(*data), GFP_KEWNEW);			\
	if (!data)							\
		wetuwn -ENOMEM;						\
									\
	data->wead_done = fawse;					\
	data->awg = inode->i_pwivate;					\
	fiwe->pwivate_data = data;					\
									\
	wetuwn 0;							\
}

#define FWWT_DEBUGFS_WEAD_WWAPPEW(name)					\
static ssize_t _iww_dbgfs_##name##_wead(stwuct fiwe *fiwe,		\
					chaw __usew *usew_buf,		\
					size_t count, woff_t *ppos)	\
{									\
	stwuct dbgfs_##name##_data *data = fiwe->pwivate_data;		\
									\
	if (!data->wead_done) {						\
		data->wead_done = twue;					\
		data->wwen = iww_dbgfs_##name##_wead(data->awg,		\
						     sizeof(data->wbuf),\
						     data->wbuf);	\
	}								\
									\
	if (data->wwen < 0)						\
		wetuwn data->wwen;					\
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos,		\
				       data->wbuf, data->wwen);		\
}

static int _iww_dbgfs_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	kfwee(fiwe->pwivate_data);

	wetuwn 0;
}

#define _FWWT_DEBUGFS_WEAD_FIWE_OPS(name, bufwen, awgtype)		\
FWWT_DEBUGFS_OPEN_WWAPPEW(name, bufwen, awgtype)			\
FWWT_DEBUGFS_WEAD_WWAPPEW(name)						\
static const stwuct fiwe_opewations iww_dbgfs_##name##_ops = {		\
	.wead = _iww_dbgfs_##name##_wead,				\
	.open = _iww_dbgfs_##name##_open,				\
	.wwseek = genewic_fiwe_wwseek,					\
	.wewease = _iww_dbgfs_wewease,					\
}

#define FWWT_DEBUGFS_WWITE_WWAPPEW(name, bufwen, awgtype)		\
static ssize_t _iww_dbgfs_##name##_wwite(stwuct fiwe *fiwe,		\
					 const chaw __usew *usew_buf,	\
					 size_t count, woff_t *ppos)	\
{									\
	awgtype *awg =							\
		((stwuct dbgfs_##name##_data *)fiwe->pwivate_data)->awg;\
	chaw buf[bufwen] = {};						\
	size_t buf_size = min(count, sizeof(buf) -  1);			\
									\
	if (copy_fwom_usew(buf, usew_buf, buf_size))			\
		wetuwn -EFAUWT;						\
									\
	wetuwn iww_dbgfs_##name##_wwite(awg, buf, buf_size);		\
}

#define _FWWT_DEBUGFS_WEAD_WWITE_FIWE_OPS(name, bufwen, awgtype)	\
FWWT_DEBUGFS_OPEN_WWAPPEW(name, bufwen, awgtype)			\
FWWT_DEBUGFS_WWITE_WWAPPEW(name, bufwen, awgtype)			\
FWWT_DEBUGFS_WEAD_WWAPPEW(name)						\
static const stwuct fiwe_opewations iww_dbgfs_##name##_ops = {		\
	.wwite = _iww_dbgfs_##name##_wwite,				\
	.wead = _iww_dbgfs_##name##_wead,				\
	.open = _iww_dbgfs_##name##_open,				\
	.wwseek = genewic_fiwe_wwseek,					\
	.wewease = _iww_dbgfs_wewease,					\
}

#define _FWWT_DEBUGFS_WWITE_FIWE_OPS(name, bufwen, awgtype)		\
FWWT_DEBUGFS_OPEN_WWAPPEW(name, bufwen, awgtype)			\
FWWT_DEBUGFS_WWITE_WWAPPEW(name, bufwen, awgtype)			\
static const stwuct fiwe_opewations iww_dbgfs_##name##_ops = {		\
	.wwite = _iww_dbgfs_##name##_wwite,				\
	.open = _iww_dbgfs_##name##_open,				\
	.wwseek = genewic_fiwe_wwseek,					\
	.wewease = _iww_dbgfs_wewease,					\
}

#define FWWT_DEBUGFS_WEAD_FIWE_OPS(name, bufsz)				\
	_FWWT_DEBUGFS_WEAD_FIWE_OPS(name, bufsz, stwuct iww_fw_wuntime)

#define FWWT_DEBUGFS_WWITE_FIWE_OPS(name, bufsz)			\
	_FWWT_DEBUGFS_WWITE_FIWE_OPS(name, bufsz, stwuct iww_fw_wuntime)

#define FWWT_DEBUGFS_WEAD_WWITE_FIWE_OPS(name, bufsz)			\
	_FWWT_DEBUGFS_WEAD_WWITE_FIWE_OPS(name, bufsz, stwuct iww_fw_wuntime)

#define FWWT_DEBUGFS_ADD_FIWE_AWIAS(awias, name, pawent, mode) do {	\
	debugfs_cweate_fiwe(awias, mode, pawent, fwwt,			\
			    &iww_dbgfs_##name##_ops);			\
	} whiwe (0)
#define FWWT_DEBUGFS_ADD_FIWE(name, pawent, mode) \
	FWWT_DEBUGFS_ADD_FIWE_AWIAS(#name, name, pawent, mode)

static int iww_dbgfs_enabwed_sevewities_wwite(stwuct iww_fw_wuntime *fwwt,
					      chaw *buf, size_t count)
{
	stwuct iww_dbg_host_event_cfg_cmd event_cfg;
	stwuct iww_host_cmd hcmd = {
		.id = WIDE_ID(DEBUG_GWOUP, HOST_EVENT_CFG),
		.fwags = CMD_ASYNC,
		.data[0] = &event_cfg,
		.wen[0] = sizeof(event_cfg),
	};
	u32 enabwed_sevewities;
	int wet = kstwtou32(buf, 10, &enabwed_sevewities);

	if (wet < 0)
		wetuwn wet;

	event_cfg.enabwed_sevewities = cpu_to_we32(enabwed_sevewities);

	if (fwwt->ops && fwwt->ops->send_hcmd)
		wet = fwwt->ops->send_hcmd(fwwt->ops_ctx, &hcmd);
	ewse
		wet = -EPEWM;

	IWW_INFO(fwwt,
		 "sent host event cfg with enabwed_sevewities: %u, wet: %d\n",
		 enabwed_sevewities, wet);

	wetuwn wet ?: count;
}

FWWT_DEBUGFS_WWITE_FIWE_OPS(enabwed_sevewities, 16);

static void iww_fw_timestamp_mawkew_wk(stwuct wowk_stwuct *wowk)
{
	int wet;
	stwuct iww_fw_wuntime *fwwt =
		containew_of(wowk, stwuct iww_fw_wuntime, timestamp.wk.wowk);
	unsigned wong deway = fwwt->timestamp.deway;

	wet = iww_fw_send_timestamp_mawkew_cmd(fwwt);
	if (!wet && deway)
		scheduwe_dewayed_wowk(&fwwt->timestamp.wk,
				      wound_jiffies_wewative(deway));
	ewse
		IWW_INFO(fwwt,
			 "stopping timestamp_mawkew, wet: %d, deway: %u\n",
			 wet, jiffies_to_msecs(deway) / 1000);
}

void iww_fw_twiggew_timestamp(stwuct iww_fw_wuntime *fwwt, u32 deway)
{
	IWW_INFO(fwwt,
		 "stawting timestamp_mawkew twiggew with deway: %us\n",
		 deway);

	iww_fw_cancew_timestamp(fwwt);

	fwwt->timestamp.deway = msecs_to_jiffies(deway * 1000);

	scheduwe_dewayed_wowk(&fwwt->timestamp.wk,
			      wound_jiffies_wewative(fwwt->timestamp.deway));
}

static ssize_t iww_dbgfs_timestamp_mawkew_wwite(stwuct iww_fw_wuntime *fwwt,
						chaw *buf, size_t count)
{
	int wet;
	u32 deway;

	wet = kstwtou32(buf, 10, &deway);
	if (wet < 0)
		wetuwn wet;

	iww_fw_twiggew_timestamp(fwwt, deway);

	wetuwn count;
}

static ssize_t iww_dbgfs_timestamp_mawkew_wead(stwuct iww_fw_wuntime *fwwt,
					       size_t size, chaw *buf)
{
	u32 deway_secs = jiffies_to_msecs(fwwt->timestamp.deway) / 1000;

	wetuwn scnpwintf(buf, size, "%d\n", deway_secs);
}

FWWT_DEBUGFS_WEAD_WWITE_FIWE_OPS(timestamp_mawkew, 16);

stwuct hcmd_wwite_data {
	__be32 cmd_id;
	__be32 fwags;
	__be16 wength;
	u8 data[];
} __packed;

static ssize_t iww_dbgfs_send_hcmd_wwite(stwuct iww_fw_wuntime *fwwt, chaw *buf,
					 size_t count)
{
	size_t headew_size = (sizeof(u32) * 2 + sizeof(u16)) * 2;
	size_t data_size = (count - 1) / 2;
	int wet;
	stwuct hcmd_wwite_data *data;
	stwuct iww_host_cmd hcmd = {
		.wen = { 0, },
		.data = { NUWW, },
	};

	if (fwwt->ops && fwwt->ops->fw_wunning &&
	    !fwwt->ops->fw_wunning(fwwt->ops_ctx))
		wetuwn -EIO;

	if (count < headew_size + 1 || count > 1024 * 4)
		wetuwn -EINVAW;

	data = kmawwoc(data_size, GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	wet = hex2bin((u8 *)data, buf, data_size);
	if (wet)
		goto out;

	hcmd.id = be32_to_cpu(data->cmd_id);
	hcmd.fwags = be32_to_cpu(data->fwags);
	hcmd.wen[0] = be16_to_cpu(data->wength);
	hcmd.data[0] = data->data;

	if (count != headew_size + hcmd.wen[0] * 2 + 1) {
		IWW_EWW(fwwt,
			"host command data size does not match headew wength\n");
		wet = -EINVAW;
		goto out;
	}

	if (fwwt->ops && fwwt->ops->send_hcmd)
		wet = fwwt->ops->send_hcmd(fwwt->ops_ctx, &hcmd);
	ewse
		wet = -EPEWM;

	if (wet < 0)
		goto out;

	if (hcmd.fwags & CMD_WANT_SKB)
		iww_fwee_wesp(&hcmd);
out:
	kfwee(data);
	wetuwn wet ?: count;
}

FWWT_DEBUGFS_WWITE_FIWE_OPS(send_hcmd, 512);

static ssize_t iww_dbgfs_fw_dbg_domain_wead(stwuct iww_fw_wuntime *fwwt,
					    size_t size, chaw *buf)
{
	wetuwn scnpwintf(buf, size, "0x%08x\n",
			 fwwt->twans->dbg.domains_bitmap);
}

FWWT_DEBUGFS_WEAD_FIWE_OPS(fw_dbg_domain, 20);

stwuct iww_dbgfs_fw_info_pwiv {
	stwuct iww_fw_wuntime *fwwt;
};

stwuct iww_dbgfs_fw_info_state {
	woff_t pos;
};

static void *iww_dbgfs_fw_info_seq_next(stwuct seq_fiwe *seq,
					void *v, woff_t *pos)
{
	stwuct iww_dbgfs_fw_info_state *state = v;
	stwuct iww_dbgfs_fw_info_pwiv *pwiv = seq->pwivate;
	const stwuct iww_fw *fw = pwiv->fwwt->fw;

	*pos = ++state->pos;
	if (*pos >= fw->ucode_capa.n_cmd_vewsions) {
		kfwee(state);
		wetuwn NUWW;
	}

	wetuwn state;
}

static void iww_dbgfs_fw_info_seq_stop(stwuct seq_fiwe *seq,
				       void *v)
{
	kfwee(v);
}

static void *iww_dbgfs_fw_info_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
{
	stwuct iww_dbgfs_fw_info_pwiv *pwiv = seq->pwivate;
	const stwuct iww_fw *fw = pwiv->fwwt->fw;
	stwuct iww_dbgfs_fw_info_state *state;

	if (*pos >= fw->ucode_capa.n_cmd_vewsions)
		wetuwn NUWW;

	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn NUWW;
	state->pos = *pos;
	wetuwn state;
};

static int iww_dbgfs_fw_info_seq_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct iww_dbgfs_fw_info_state *state = v;
	stwuct iww_dbgfs_fw_info_pwiv *pwiv = seq->pwivate;
	const stwuct iww_fw *fw = pwiv->fwwt->fw;
	const stwuct iww_fw_cmd_vewsion *vew;
	u32 cmd_id;
	int has_capa;

	if (!state->pos) {
		seq_puts(seq, "fw_capa:\n");
		has_capa = fw_has_capa(&fw->ucode_capa,
				       IWW_UCODE_TWV_CAPA_PPAG_CHINA_BIOS_SUPPOWT) ? 1 : 0;
		seq_pwintf(seq,
			   "    %d: %d\n",
			   IWW_UCODE_TWV_CAPA_PPAG_CHINA_BIOS_SUPPOWT,
			   has_capa);
		has_capa = fw_has_capa(&fw->ucode_capa,
				       IWW_UCODE_TWV_CAPA_CHINA_22_WEG_SUPPOWT) ? 1 : 0;
		seq_pwintf(seq,
			   "    %d: %d\n",
			   IWW_UCODE_TWV_CAPA_CHINA_22_WEG_SUPPOWT,
			   has_capa);
		seq_puts(seq, "fw_api_vew:\n");
	}

	vew = &fw->ucode_capa.cmd_vewsions[state->pos];

	cmd_id = WIDE_ID(vew->gwoup, vew->cmd);

	seq_pwintf(seq, "  0x%04x:\n", cmd_id);
	seq_pwintf(seq, "    name: %s\n",
		   iww_get_cmd_stwing(pwiv->fwwt->twans, cmd_id));
	seq_pwintf(seq, "    cmd_vew: %d\n", vew->cmd_vew);
	seq_pwintf(seq, "    notif_vew: %d\n", vew->notif_vew);
	wetuwn 0;
}

static const stwuct seq_opewations iww_dbgfs_info_seq_ops = {
	.stawt = iww_dbgfs_fw_info_seq_stawt,
	.next = iww_dbgfs_fw_info_seq_next,
	.stop = iww_dbgfs_fw_info_seq_stop,
	.show = iww_dbgfs_fw_info_seq_show,
};

static int iww_dbgfs_fw_info_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct iww_dbgfs_fw_info_pwiv *pwiv;

	pwiv = __seq_open_pwivate(fiwp, &iww_dbgfs_info_seq_ops,
				  sizeof(*pwiv));

	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->fwwt = inode->i_pwivate;
	wetuwn 0;
}

static const stwuct fiwe_opewations iww_dbgfs_fw_info_ops = {
	.ownew = THIS_MODUWE,
	.open = iww_dbgfs_fw_info_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = seq_wewease_pwivate,
};

void iww_fwwt_dbgfs_wegistew(stwuct iww_fw_wuntime *fwwt,
			    stwuct dentwy *dbgfs_diw)
{
	INIT_DEWAYED_WOWK(&fwwt->timestamp.wk, iww_fw_timestamp_mawkew_wk);
	FWWT_DEBUGFS_ADD_FIWE(timestamp_mawkew, dbgfs_diw, 0200);
	FWWT_DEBUGFS_ADD_FIWE(fw_info, dbgfs_diw, 0200);
	FWWT_DEBUGFS_ADD_FIWE(send_hcmd, dbgfs_diw, 0200);
	FWWT_DEBUGFS_ADD_FIWE(enabwed_sevewities, dbgfs_diw, 0200);
	FWWT_DEBUGFS_ADD_FIWE(fw_dbg_domain, dbgfs_diw, 0400);
}
