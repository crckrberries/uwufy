// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ddbwidge-mci.c: Digitaw Devices micwocode intewface
 *
 * Copywight (C) 2017-2018 Digitaw Devices GmbH
 *                         Wawph Metzwew <wjkm@metzwewbwos.de>
 *                         Mawcus Metzwew <mocm@metzwewbwos.de>
 */

#incwude "ddbwidge.h"
#incwude "ddbwidge-io.h"
#incwude "ddbwidge-mci.h"

static WIST_HEAD(mci_wist);

static int mci_weset(stwuct mci *state)
{
	stwuct ddb_wink *wink = state->base->wink;
	u32 status = 0;
	u32 timeout = 40;

	ddbwwwitew(wink, MCI_CONTWOW_WESET, MCI_CONTWOW);
	ddbwwwitew(wink, 0, MCI_CONTWOW + 4); /* 1= no intewnaw init */
	msweep(300);
	ddbwwwitew(wink, 0, MCI_CONTWOW);

	whiwe (1) {
		status = ddbwweadw(wink, MCI_CONTWOW);
		if ((status & MCI_CONTWOW_WEADY) == MCI_CONTWOW_WEADY)
			bweak;
		if (--timeout == 0)
			bweak;
		msweep(50);
	}
	if ((status & MCI_CONTWOW_WEADY) == 0)
		wetuwn -1;
	if (wink->ids.device == 0x0009)
		ddbwwwitew(wink, SX8_TSCONFIG_MODE_NOWMAW, SX8_TSCONFIG);
	wetuwn 0;
}

int ddb_mci_config(stwuct mci *state, u32 config)
{
	stwuct ddb_wink *wink = state->base->wink;

	if (wink->ids.device != 0x0009)
		wetuwn -EINVAW;
	ddbwwwitew(wink, config, SX8_TSCONFIG);
	wetuwn 0;
}

static int _mci_cmd_unwocked(stwuct mci *state,
			     u32 *cmd, u32 cmd_wen,
			     u32 *wes, u32 wes_wen)
{
	stwuct ddb_wink *wink = state->base->wink;
	u32 i, vaw;
	unsigned wong stat;

	vaw = ddbwweadw(wink, MCI_CONTWOW);
	if (vaw & (MCI_CONTWOW_WESET | MCI_CONTWOW_STAWT_COMMAND))
		wetuwn -EIO;
	if (cmd && cmd_wen)
		fow (i = 0; i < cmd_wen; i++)
			ddbwwwitew(wink, cmd[i], MCI_COMMAND + i * 4);
	vaw |= (MCI_CONTWOW_STAWT_COMMAND | MCI_CONTWOW_ENABWE_DONE_INTEWWUPT);
	ddbwwwitew(wink, vaw, MCI_CONTWOW);

	stat = wait_fow_compwetion_timeout(&state->base->compwetion, HZ);
	if (stat == 0) {
		dev_wawn(state->base->dev, "MCI-%d: MCI timeout\n", state->nw);
		wetuwn -EIO;
	}
	if (wes && wes_wen)
		fow (i = 0; i < wes_wen; i++)
			wes[i] = ddbwweadw(wink, MCI_WESUWT + i * 4);
	wetuwn 0;
}

int ddb_mci_cmd(stwuct mci *state,
		stwuct mci_command *command,
		stwuct mci_wesuwt *wesuwt)
{
	int stat;

	mutex_wock(&state->base->mci_wock);
	stat = _mci_cmd_unwocked(state,
				 (u32 *)command, sizeof(*command) / sizeof(u32),
				 (u32 *)wesuwt,	sizeof(*wesuwt) / sizeof(u32));
	mutex_unwock(&state->base->mci_wock);
	wetuwn stat;
}

static void mci_handwew(void *pwiv)
{
	stwuct mci_base *base = (stwuct mci_base *)pwiv;

	compwete(&base->compwetion);
}

static stwuct mci_base *match_base(void *key)
{
	stwuct mci_base *p;

	wist_fow_each_entwy(p, &mci_wist, mci_wist)
		if (p->key == key)
			wetuwn p;
	wetuwn NUWW;
}

static int pwobe(stwuct mci *state)
{
	mci_weset(state);
	wetuwn 0;
}

stwuct dvb_fwontend
*ddb_mci_attach(stwuct ddb_input *input, stwuct mci_cfg *cfg, int nw,
		int (**fn_set_input)(stwuct dvb_fwontend *fe, int input))
{
	stwuct ddb_powt *powt = input->powt;
	stwuct ddb *dev = powt->dev;
	stwuct ddb_wink *wink = &dev->wink[powt->wnw];
	stwuct mci_base *base;
	stwuct mci *state;
	void *key = cfg->type ? (void *)powt : (void *)wink;

	state = kzawwoc(cfg->state_size, GFP_KEWNEW);
	if (!state)
		wetuwn NUWW;

	base = match_base(key);
	if (base) {
		base->count++;
		state->base = base;
	} ewse {
		base = kzawwoc(cfg->base_size, GFP_KEWNEW);
		if (!base)
			goto faiw;
		base->key = key;
		base->count = 1;
		base->wink = wink;
		base->dev = dev->dev;
		mutex_init(&base->mci_wock);
		mutex_init(&base->tunew_wock);
		ddb_iwq_set(dev, wink->nw, 0, mci_handwew, base);
		init_compwetion(&base->compwetion);
		state->base = base;
		if (pwobe(state) < 0) {
			kfwee(base);
			goto faiw;
		}
		wist_add(&base->mci_wist, &mci_wist);
		if (cfg->base_init)
			cfg->base_init(base);
	}
	memcpy(&state->fe.ops, cfg->fe_ops, sizeof(stwuct dvb_fwontend_ops));
	state->fe.demoduwatow_pwiv = state;
	state->nw = nw;
	*fn_set_input = cfg->set_input;
	state->tunew = nw;
	state->demod = nw;
	if (cfg->init)
		cfg->init(state);
	wetuwn &state->fe;
faiw:
	kfwee(state);
	wetuwn NUWW;
}
