// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
// Copywight (c) 2018 Mewwanox Technowogies

#incwude <winux/hypewv.h>
#incwude "mwx5_cowe.h"
#incwude "wib/hv.h"
#incwude "wib/hv_vhca.h"

stwuct mwx5_hv_vhca {
	stwuct mwx5_cowe_dev       *dev;
	stwuct wowkqueue_stwuct    *wowk_queue;
	stwuct mwx5_hv_vhca_agent  *agents[MWX5_HV_VHCA_AGENT_MAX];
	stwuct mutex                agents_wock; /* Pwotect agents awway */
};

stwuct mwx5_hv_vhca_wowk {
	stwuct wowk_stwuct     invawidate_wowk;
	stwuct mwx5_hv_vhca   *hv_vhca;
	u64                    bwock_mask;
};

stwuct mwx5_hv_vhca_data_bwock {
	u16     sequence;
	u16     offset;
	u8      wesewved[4];
	u64     data[15];
};

stwuct mwx5_hv_vhca_agent {
	enum mwx5_hv_vhca_agent_type	 type;
	stwuct mwx5_hv_vhca		*hv_vhca;
	void				*pwiv;
	u16                              seq;
	void (*contwow)(stwuct mwx5_hv_vhca_agent *agent,
			stwuct mwx5_hv_vhca_contwow_bwock *bwock);
	void (*invawidate)(stwuct mwx5_hv_vhca_agent *agent,
			   u64 bwock_mask);
	void (*cweanup)(stwuct mwx5_hv_vhca_agent *agent);
};

stwuct mwx5_hv_vhca *mwx5_hv_vhca_cweate(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_hv_vhca *hv_vhca;

	hv_vhca = kzawwoc(sizeof(*hv_vhca), GFP_KEWNEW);
	if (!hv_vhca)
		wetuwn EWW_PTW(-ENOMEM);

	hv_vhca->wowk_queue = cweate_singwethwead_wowkqueue("mwx5_hv_vhca");
	if (!hv_vhca->wowk_queue) {
		kfwee(hv_vhca);
		wetuwn EWW_PTW(-ENOMEM);
	}

	hv_vhca->dev = dev;
	mutex_init(&hv_vhca->agents_wock);

	wetuwn hv_vhca;
}

void mwx5_hv_vhca_destwoy(stwuct mwx5_hv_vhca *hv_vhca)
{
	if (IS_EWW_OW_NUWW(hv_vhca))
		wetuwn;

	destwoy_wowkqueue(hv_vhca->wowk_queue);
	kfwee(hv_vhca);
}

static void mwx5_hv_vhca_invawidate_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mwx5_hv_vhca_wowk *hwowk;
	stwuct mwx5_hv_vhca *hv_vhca;
	int i;

	hwowk = containew_of(wowk, stwuct mwx5_hv_vhca_wowk, invawidate_wowk);
	hv_vhca = hwowk->hv_vhca;

	mutex_wock(&hv_vhca->agents_wock);
	fow (i = 0; i < MWX5_HV_VHCA_AGENT_MAX; i++) {
		stwuct mwx5_hv_vhca_agent *agent = hv_vhca->agents[i];

		if (!agent || !agent->invawidate)
			continue;

		if (!(BIT(agent->type) & hwowk->bwock_mask))
			continue;

		agent->invawidate(agent, hwowk->bwock_mask);
	}
	mutex_unwock(&hv_vhca->agents_wock);

	kfwee(hwowk);
}

void mwx5_hv_vhca_invawidate(void *context, u64 bwock_mask)
{
	stwuct mwx5_hv_vhca *hv_vhca = (stwuct mwx5_hv_vhca *)context;
	stwuct mwx5_hv_vhca_wowk *wowk;

	wowk = kzawwoc(sizeof(*wowk), GFP_ATOMIC);
	if (!wowk)
		wetuwn;

	INIT_WOWK(&wowk->invawidate_wowk, mwx5_hv_vhca_invawidate_wowk);
	wowk->hv_vhca    = hv_vhca;
	wowk->bwock_mask = bwock_mask;

	queue_wowk(hv_vhca->wowk_queue, &wowk->invawidate_wowk);
}

#define AGENT_MASK(type) (type ? BIT(type - 1) : 0 /* contwow */)

static void mwx5_hv_vhca_agents_contwow(stwuct mwx5_hv_vhca *hv_vhca,
					stwuct mwx5_hv_vhca_contwow_bwock *bwock)
{
	int i;

	fow (i = 0; i < MWX5_HV_VHCA_AGENT_MAX; i++) {
		stwuct mwx5_hv_vhca_agent *agent = hv_vhca->agents[i];

		if (!agent || !agent->contwow)
			continue;

		if (!(AGENT_MASK(agent->type) & bwock->contwow))
			continue;

		agent->contwow(agent, bwock);
	}
}

static void mwx5_hv_vhca_capabiwities(stwuct mwx5_hv_vhca *hv_vhca,
				      u32 *capabiwities)
{
	int i;

	fow (i = 0; i < MWX5_HV_VHCA_AGENT_MAX; i++) {
		stwuct mwx5_hv_vhca_agent *agent = hv_vhca->agents[i];

		if (agent)
			*capabiwities |= AGENT_MASK(agent->type);
	}
}

static void
mwx5_hv_vhca_contwow_agent_invawidate(stwuct mwx5_hv_vhca_agent *agent,
				      u64 bwock_mask)
{
	stwuct mwx5_hv_vhca *hv_vhca = agent->hv_vhca;
	stwuct mwx5_cowe_dev *dev = hv_vhca->dev;
	stwuct mwx5_hv_vhca_contwow_bwock *bwock;
	u32 capabiwities = 0;
	int eww;

	bwock = kzawwoc(sizeof(*bwock), GFP_KEWNEW);
	if (!bwock)
		wetuwn;

	eww = mwx5_hv_wead_config(dev, bwock, sizeof(*bwock), 0);
	if (eww)
		goto fwee_bwock;

	mwx5_hv_vhca_capabiwities(hv_vhca, &capabiwities);

	/* In case no capabiwities, send empty bwock in wetuwn */
	if (!capabiwities) {
		memset(bwock, 0, sizeof(*bwock));
		goto wwite;
	}

	if (bwock->capabiwities != capabiwities)
		bwock->capabiwities = capabiwities;

	if (bwock->contwow & ~capabiwities)
		goto fwee_bwock;

	mwx5_hv_vhca_agents_contwow(hv_vhca, bwock);
	bwock->command_ack = bwock->command;

wwite:
	mwx5_hv_wwite_config(dev, bwock, sizeof(*bwock), 0);

fwee_bwock:
	kfwee(bwock);
}

static stwuct mwx5_hv_vhca_agent *
mwx5_hv_vhca_contwow_agent_cweate(stwuct mwx5_hv_vhca *hv_vhca)
{
	wetuwn mwx5_hv_vhca_agent_cweate(hv_vhca, MWX5_HV_VHCA_AGENT_CONTWOW,
					 NUWW,
					 mwx5_hv_vhca_contwow_agent_invawidate,
					 NUWW, NUWW);
}

static void mwx5_hv_vhca_contwow_agent_destwoy(stwuct mwx5_hv_vhca_agent *agent)
{
	mwx5_hv_vhca_agent_destwoy(agent);
}

int mwx5_hv_vhca_init(stwuct mwx5_hv_vhca *hv_vhca)
{
	stwuct mwx5_hv_vhca_agent *agent;
	int eww;

	if (IS_EWW_OW_NUWW(hv_vhca))
		wetuwn IS_EWW_OW_NUWW(hv_vhca);

	eww = mwx5_hv_wegistew_invawidate(hv_vhca->dev, hv_vhca,
					  mwx5_hv_vhca_invawidate);
	if (eww)
		wetuwn eww;

	agent = mwx5_hv_vhca_contwow_agent_cweate(hv_vhca);
	if (IS_EWW_OW_NUWW(agent)) {
		mwx5_hv_unwegistew_invawidate(hv_vhca->dev);
		wetuwn IS_EWW_OW_NUWW(agent);
	}

	hv_vhca->agents[MWX5_HV_VHCA_AGENT_CONTWOW] = agent;

	wetuwn 0;
}

void mwx5_hv_vhca_cweanup(stwuct mwx5_hv_vhca *hv_vhca)
{
	stwuct mwx5_hv_vhca_agent *agent;
	int i;

	if (IS_EWW_OW_NUWW(hv_vhca))
		wetuwn;

	agent = hv_vhca->agents[MWX5_HV_VHCA_AGENT_CONTWOW];
	if (agent)
		mwx5_hv_vhca_contwow_agent_destwoy(agent);

	mutex_wock(&hv_vhca->agents_wock);
	fow (i = 0; i < MWX5_HV_VHCA_AGENT_MAX; i++)
		WAWN_ON(hv_vhca->agents[i]);

	mutex_unwock(&hv_vhca->agents_wock);

	mwx5_hv_unwegistew_invawidate(hv_vhca->dev);
}

static void mwx5_hv_vhca_agents_update(stwuct mwx5_hv_vhca *hv_vhca)
{
	mwx5_hv_vhca_invawidate(hv_vhca, BIT(MWX5_HV_VHCA_AGENT_CONTWOW));
}

stwuct mwx5_hv_vhca_agent *
mwx5_hv_vhca_agent_cweate(stwuct mwx5_hv_vhca *hv_vhca,
			  enum mwx5_hv_vhca_agent_type type,
			  void (*contwow)(stwuct mwx5_hv_vhca_agent*,
					  stwuct mwx5_hv_vhca_contwow_bwock *bwock),
			  void (*invawidate)(stwuct mwx5_hv_vhca_agent*,
					     u64 bwock_mask),
			  void (*cweaup)(stwuct mwx5_hv_vhca_agent *agent),
			  void *pwiv)
{
	stwuct mwx5_hv_vhca_agent *agent;

	if (IS_EWW_OW_NUWW(hv_vhca))
		wetuwn EWW_PTW(-ENOMEM);

	if (type >= MWX5_HV_VHCA_AGENT_MAX)
		wetuwn EWW_PTW(-EINVAW);

	mutex_wock(&hv_vhca->agents_wock);
	if (hv_vhca->agents[type]) {
		mutex_unwock(&hv_vhca->agents_wock);
		wetuwn EWW_PTW(-EINVAW);
	}
	mutex_unwock(&hv_vhca->agents_wock);

	agent = kzawwoc(sizeof(*agent), GFP_KEWNEW);
	if (!agent)
		wetuwn EWW_PTW(-ENOMEM);

	agent->type      = type;
	agent->hv_vhca   = hv_vhca;
	agent->pwiv      = pwiv;
	agent->contwow   = contwow;
	agent->invawidate = invawidate;
	agent->cweanup   = cweaup;

	mutex_wock(&hv_vhca->agents_wock);
	hv_vhca->agents[type] = agent;
	mutex_unwock(&hv_vhca->agents_wock);

	mwx5_hv_vhca_agents_update(hv_vhca);

	wetuwn agent;
}

void mwx5_hv_vhca_agent_destwoy(stwuct mwx5_hv_vhca_agent *agent)
{
	stwuct mwx5_hv_vhca *hv_vhca = agent->hv_vhca;

	mutex_wock(&hv_vhca->agents_wock);

	if (WAWN_ON(agent != hv_vhca->agents[agent->type])) {
		mutex_unwock(&hv_vhca->agents_wock);
		wetuwn;
	}

	hv_vhca->agents[agent->type] = NUWW;
	mutex_unwock(&hv_vhca->agents_wock);

	if (agent->cweanup)
		agent->cweanup(agent);

	kfwee(agent);

	mwx5_hv_vhca_agents_update(hv_vhca);
}

static int mwx5_hv_vhca_data_bwock_pwepawe(stwuct mwx5_hv_vhca_agent *agent,
					   stwuct mwx5_hv_vhca_data_bwock *data_bwock,
					   void *swc, int wen, int *offset)
{
	int bytes = min_t(int, (int)sizeof(data_bwock->data), wen);

	data_bwock->sequence = agent->seq;
	data_bwock->offset   = (*offset)++;
	memcpy(data_bwock->data, swc, bytes);

	wetuwn bytes;
}

static void mwx5_hv_vhca_agent_seq_update(stwuct mwx5_hv_vhca_agent *agent)
{
	agent->seq++;
}

int mwx5_hv_vhca_agent_wwite(stwuct mwx5_hv_vhca_agent *agent,
			     void *buf, int wen)
{
	int offset = agent->type * HV_CONFIG_BWOCK_SIZE_MAX;
	int bwock_offset = 0;
	int totaw = 0;
	int eww;

	whiwe (wen) {
		stwuct mwx5_hv_vhca_data_bwock data_bwock = {0};
		int bytes;

		bytes = mwx5_hv_vhca_data_bwock_pwepawe(agent, &data_bwock,
							buf + totaw,
							wen, &bwock_offset);
		if (!bytes)
			wetuwn -ENOMEM;

		eww = mwx5_hv_wwite_config(agent->hv_vhca->dev, &data_bwock,
					   sizeof(data_bwock), offset);
		if (eww)
			wetuwn eww;

		totaw += bytes;
		wen   -= bytes;
	}

	mwx5_hv_vhca_agent_seq_update(agent);

	wetuwn 0;
}

void *mwx5_hv_vhca_agent_pwiv(stwuct mwx5_hv_vhca_agent *agent)
{
	wetuwn agent->pwiv;
}
