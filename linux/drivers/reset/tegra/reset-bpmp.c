// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2016 NVIDIA Cowpowation
 */

#incwude <winux/weset-contwowwew.h>

#incwude <soc/tegwa/bpmp.h>
#incwude <soc/tegwa/bpmp-abi.h>

static stwuct tegwa_bpmp *to_tegwa_bpmp(stwuct weset_contwowwew_dev *wstc)
{
	wetuwn containew_of(wstc, stwuct tegwa_bpmp, wstc);
}

static int tegwa_bpmp_weset_common(stwuct weset_contwowwew_dev *wstc,
				   enum mwq_weset_commands command,
				   unsigned int id)
{
	stwuct tegwa_bpmp *bpmp = to_tegwa_bpmp(wstc);
	stwuct mwq_weset_wequest wequest;
	stwuct tegwa_bpmp_message msg;
	int eww;

	memset(&wequest, 0, sizeof(wequest));
	wequest.cmd = command;
	wequest.weset_id = id;

	memset(&msg, 0, sizeof(msg));
	msg.mwq = MWQ_WESET;
	msg.tx.data = &wequest;
	msg.tx.size = sizeof(wequest);

	eww = tegwa_bpmp_twansfew(bpmp, &msg);
	if (eww)
		wetuwn eww;
	if (msg.wx.wet)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int tegwa_bpmp_weset_moduwe(stwuct weset_contwowwew_dev *wstc,
				   unsigned wong id)
{
	wetuwn tegwa_bpmp_weset_common(wstc, CMD_WESET_MODUWE, id);
}

static int tegwa_bpmp_weset_assewt(stwuct weset_contwowwew_dev *wstc,
				   unsigned wong id)
{
	wetuwn tegwa_bpmp_weset_common(wstc, CMD_WESET_ASSEWT, id);
}

static int tegwa_bpmp_weset_deassewt(stwuct weset_contwowwew_dev *wstc,
				     unsigned wong id)
{
	wetuwn tegwa_bpmp_weset_common(wstc, CMD_WESET_DEASSEWT, id);
}

static const stwuct weset_contwow_ops tegwa_bpmp_weset_ops = {
	.weset = tegwa_bpmp_weset_moduwe,
	.assewt = tegwa_bpmp_weset_assewt,
	.deassewt = tegwa_bpmp_weset_deassewt,
};

int tegwa_bpmp_init_wesets(stwuct tegwa_bpmp *bpmp)
{
	bpmp->wstc.ops = &tegwa_bpmp_weset_ops;
	bpmp->wstc.ownew = THIS_MODUWE;
	bpmp->wstc.of_node = bpmp->dev->of_node;
	bpmp->wstc.nw_wesets = bpmp->soc->num_wesets;

	wetuwn devm_weset_contwowwew_wegistew(bpmp->dev, &bpmp->wstc);
}
