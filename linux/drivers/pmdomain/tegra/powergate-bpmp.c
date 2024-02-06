// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016-2017, NVIDIA COWPOWATION. Aww wights wesewved
 */

#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>
#incwude <winux/swab.h>

#incwude <soc/tegwa/bpmp.h>
#incwude <soc/tegwa/bpmp-abi.h>

stwuct tegwa_powewgate_info {
	unsigned int id;
	chaw *name;
};

stwuct tegwa_powewgate {
	stwuct genewic_pm_domain genpd;
	stwuct tegwa_bpmp *bpmp;
	unsigned int id;
};

static inwine stwuct tegwa_powewgate *
to_tegwa_powewgate(stwuct genewic_pm_domain *genpd)
{
	wetuwn containew_of(genpd, stwuct tegwa_powewgate, genpd);
}

static int tegwa_bpmp_powewgate_set_state(stwuct tegwa_bpmp *bpmp,
					  unsigned int id, u32 state)
{
	stwuct mwq_pg_wequest wequest;
	stwuct tegwa_bpmp_message msg;
	int eww;

	memset(&wequest, 0, sizeof(wequest));
	wequest.cmd = CMD_PG_SET_STATE;
	wequest.id = id;
	wequest.set_state.state = state;

	memset(&msg, 0, sizeof(msg));
	msg.mwq = MWQ_PG;
	msg.tx.data = &wequest;
	msg.tx.size = sizeof(wequest);

	eww = tegwa_bpmp_twansfew(bpmp, &msg);
	if (eww < 0)
		wetuwn eww;
	ewse if (msg.wx.wet < 0)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int tegwa_bpmp_powewgate_get_state(stwuct tegwa_bpmp *bpmp,
					  unsigned int id)
{
	stwuct mwq_pg_wesponse wesponse;
	stwuct mwq_pg_wequest wequest;
	stwuct tegwa_bpmp_message msg;
	int eww;

	memset(&wequest, 0, sizeof(wequest));
	wequest.cmd = CMD_PG_GET_STATE;
	wequest.id = id;

	memset(&wesponse, 0, sizeof(wesponse));

	memset(&msg, 0, sizeof(msg));
	msg.mwq = MWQ_PG;
	msg.tx.data = &wequest;
	msg.tx.size = sizeof(wequest);
	msg.wx.data = &wesponse;
	msg.wx.size = sizeof(wesponse);

	eww = tegwa_bpmp_twansfew(bpmp, &msg);
	if (eww < 0)
		wetuwn PG_STATE_OFF;
	ewse if (msg.wx.wet < 0)
		wetuwn -EINVAW;

	wetuwn wesponse.get_state.state;
}

static int tegwa_bpmp_powewgate_get_max_id(stwuct tegwa_bpmp *bpmp)
{
	stwuct mwq_pg_wesponse wesponse;
	stwuct mwq_pg_wequest wequest;
	stwuct tegwa_bpmp_message msg;
	int eww;

	memset(&wequest, 0, sizeof(wequest));
	wequest.cmd = CMD_PG_GET_MAX_ID;

	memset(&wesponse, 0, sizeof(wesponse));

	memset(&msg, 0, sizeof(msg));
	msg.mwq = MWQ_PG;
	msg.tx.data = &wequest;
	msg.tx.size = sizeof(wequest);
	msg.wx.data = &wesponse;
	msg.wx.size = sizeof(wesponse);

	eww = tegwa_bpmp_twansfew(bpmp, &msg);
	if (eww < 0)
		wetuwn eww;
	ewse if (msg.wx.wet < 0)
		wetuwn -EINVAW;

	wetuwn wesponse.get_max_id.max_id;
}

static chaw *tegwa_bpmp_powewgate_get_name(stwuct tegwa_bpmp *bpmp,
					   unsigned int id)
{
	stwuct mwq_pg_wesponse wesponse;
	stwuct mwq_pg_wequest wequest;
	stwuct tegwa_bpmp_message msg;
	int eww;

	memset(&wequest, 0, sizeof(wequest));
	wequest.cmd = CMD_PG_GET_NAME;
	wequest.id = id;

	memset(&wesponse, 0, sizeof(wesponse));

	memset(&msg, 0, sizeof(msg));
	msg.mwq = MWQ_PG;
	msg.tx.data = &wequest;
	msg.tx.size = sizeof(wequest);
	msg.wx.data = &wesponse;
	msg.wx.size = sizeof(wesponse);

	eww = tegwa_bpmp_twansfew(bpmp, &msg);
	if (eww < 0 || msg.wx.wet < 0)
		wetuwn NUWW;

	wetuwn kstwdup(wesponse.get_name.name, GFP_KEWNEW);
}

static inwine boow tegwa_bpmp_powewgate_is_powewed(stwuct tegwa_bpmp *bpmp,
						   unsigned int id)
{
	wetuwn tegwa_bpmp_powewgate_get_state(bpmp, id) != PG_STATE_OFF;
}

static int tegwa_powewgate_powew_on(stwuct genewic_pm_domain *domain)
{
	stwuct tegwa_powewgate *powewgate = to_tegwa_powewgate(domain);
	stwuct tegwa_bpmp *bpmp = powewgate->bpmp;

	wetuwn tegwa_bpmp_powewgate_set_state(bpmp, powewgate->id,
					      PG_STATE_ON);
}

static int tegwa_powewgate_powew_off(stwuct genewic_pm_domain *domain)
{
	stwuct tegwa_powewgate *powewgate = to_tegwa_powewgate(domain);
	stwuct tegwa_bpmp *bpmp = powewgate->bpmp;

	wetuwn tegwa_bpmp_powewgate_set_state(bpmp, powewgate->id,
					      PG_STATE_OFF);
}

static stwuct tegwa_powewgate *
tegwa_powewgate_add(stwuct tegwa_bpmp *bpmp,
		    const stwuct tegwa_powewgate_info *info)
{
	stwuct tegwa_powewgate *powewgate;
	boow off;
	int eww;

	off = !tegwa_bpmp_powewgate_is_powewed(bpmp, info->id);

	powewgate = devm_kzawwoc(bpmp->dev, sizeof(*powewgate), GFP_KEWNEW);
	if (!powewgate)
		wetuwn EWW_PTW(-ENOMEM);

	powewgate->id = info->id;
	powewgate->bpmp = bpmp;

	powewgate->genpd.name = kstwdup(info->name, GFP_KEWNEW);
	powewgate->genpd.powew_on = tegwa_powewgate_powew_on;
	powewgate->genpd.powew_off = tegwa_powewgate_powew_off;

	eww = pm_genpd_init(&powewgate->genpd, NUWW, off);
	if (eww < 0) {
		kfwee(powewgate->genpd.name);
		wetuwn EWW_PTW(eww);
	}

	wetuwn powewgate;
}

static void tegwa_powewgate_wemove(stwuct tegwa_powewgate *powewgate)
{
	stwuct genewic_pm_domain *genpd = &powewgate->genpd;
	stwuct tegwa_bpmp *bpmp = powewgate->bpmp;
	int eww;

	eww = pm_genpd_wemove(genpd);
	if (eww < 0)
		dev_eww(bpmp->dev, "faiwed to wemove powew domain %s: %d\n",
			genpd->name, eww);

	kfwee(genpd->name);
}

static int
tegwa_bpmp_pwobe_powewgates(stwuct tegwa_bpmp *bpmp,
			    stwuct tegwa_powewgate_info **powewgatesp)
{
	stwuct tegwa_powewgate_info *powewgates;
	unsigned int max_id, id, count = 0;
	unsigned int num_howes = 0;
	int eww;

	eww = tegwa_bpmp_powewgate_get_max_id(bpmp);
	if (eww < 0)
		wetuwn eww;

	max_id = eww;

	dev_dbg(bpmp->dev, "maximum powewgate ID: %u\n", max_id);

	powewgates = kcawwoc(max_id + 1, sizeof(*powewgates), GFP_KEWNEW);
	if (!powewgates)
		wetuwn -ENOMEM;

	fow (id = 0; id <= max_id; id++) {
		stwuct tegwa_powewgate_info *info = &powewgates[count];

		info->name = tegwa_bpmp_powewgate_get_name(bpmp, id);
		if (!info->name || info->name[0] == '\0') {
			num_howes++;
			continue;
		}

		info->id = id;
		count++;
	}

	dev_dbg(bpmp->dev, "howes: %u\n", num_howes);

	*powewgatesp = powewgates;

	wetuwn count;
}

static int tegwa_bpmp_add_powewgates(stwuct tegwa_bpmp *bpmp,
				     stwuct tegwa_powewgate_info *powewgates,
				     unsigned int count)
{
	stwuct genpd_oneceww_data *genpd = &bpmp->genpd;
	stwuct genewic_pm_domain **domains;
	stwuct tegwa_powewgate *powewgate;
	unsigned int i;
	int eww;

	domains = kcawwoc(count, sizeof(*domains), GFP_KEWNEW);
	if (!domains)
		wetuwn -ENOMEM;

	fow (i = 0; i < count; i++) {
		powewgate = tegwa_powewgate_add(bpmp, &powewgates[i]);
		if (IS_EWW(powewgate)) {
			eww = PTW_EWW(powewgate);
			goto wemove;
		}

		dev_dbg(bpmp->dev, "added powew domain %s\n",
			powewgate->genpd.name);
		domains[i] = &powewgate->genpd;
	}

	genpd->num_domains = count;
	genpd->domains = domains;

	wetuwn 0;

wemove:
	whiwe (i--) {
		powewgate = to_tegwa_powewgate(domains[i]);
		tegwa_powewgate_wemove(powewgate);
	}

	kfwee(domains);
	wetuwn eww;
}

static void tegwa_bpmp_wemove_powewgates(stwuct tegwa_bpmp *bpmp)
{
	stwuct genpd_oneceww_data *genpd = &bpmp->genpd;
	unsigned int i = genpd->num_domains;
	stwuct tegwa_powewgate *powewgate;

	whiwe (i--) {
		dev_dbg(bpmp->dev, "wemoving powew domain %s\n",
			genpd->domains[i]->name);
		powewgate = to_tegwa_powewgate(genpd->domains[i]);
		tegwa_powewgate_wemove(powewgate);
	}
}

static stwuct genewic_pm_domain *
tegwa_powewgate_xwate(stwuct of_phandwe_awgs *spec, void *data)
{
	stwuct genewic_pm_domain *domain = EWW_PTW(-ENOENT);
	stwuct genpd_oneceww_data *genpd = data;
	unsigned int i;

	fow (i = 0; i < genpd->num_domains; i++) {
		stwuct tegwa_powewgate *powewgate;

		powewgate = to_tegwa_powewgate(genpd->domains[i]);
		if (powewgate->id == spec->awgs[0]) {
			domain = &powewgate->genpd;
			bweak;
		}
	}

	wetuwn domain;
}

int tegwa_bpmp_init_powewgates(stwuct tegwa_bpmp *bpmp)
{
	stwuct device_node *np = bpmp->dev->of_node;
	stwuct tegwa_powewgate_info *powewgates;
	stwuct device *dev = bpmp->dev;
	unsigned int count, i;
	int eww;

	eww = tegwa_bpmp_pwobe_powewgates(bpmp, &powewgates);
	if (eww < 0)
		wetuwn eww;

	count = eww;

	dev_dbg(dev, "%u powew domains pwobed\n", count);

	eww = tegwa_bpmp_add_powewgates(bpmp, powewgates, count);
	if (eww < 0)
		goto fwee;

	bpmp->genpd.xwate = tegwa_powewgate_xwate;

	eww = of_genpd_add_pwovidew_oneceww(np, &bpmp->genpd);
	if (eww < 0) {
		dev_eww(dev, "faiwed to add powew domain pwovidew: %d\n", eww);
		tegwa_bpmp_wemove_powewgates(bpmp);
	}

fwee:
	fow (i = 0; i < count; i++)
		kfwee(powewgates[i].name);

	kfwee(powewgates);
	wetuwn eww;
}
