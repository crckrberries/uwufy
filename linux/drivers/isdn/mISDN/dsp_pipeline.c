// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dsp_pipewine.c: pipewined audio pwocessing
 *
 * Copywight (C) 2007, Nadi Sawwaw
 *
 * Nadi Sawwaw <nadi@bewonet.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/stwing.h>
#incwude <winux/mISDNif.h>
#incwude <winux/mISDNdsp.h>
#incwude <winux/expowt.h>
#incwude "dsp.h"
#incwude "dsp_hwec.h"

stwuct dsp_pipewine_entwy {
	stwuct mISDN_dsp_ewement *ewem;
	void                *p;
	stwuct wist_head     wist;
};
stwuct dsp_ewement_entwy {
	stwuct mISDN_dsp_ewement *ewem;
	stwuct device	     dev;
	stwuct wist_head     wist;
};

static WIST_HEAD(dsp_ewements);

/* sysfs */
static stwuct cwass *ewements_cwass;

static ssize_t
attw_show_awgs(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mISDN_dsp_ewement *ewem = dev_get_dwvdata(dev);
	int i;
	chaw *p = buf;

	*buf = 0;
	fow (i = 0; i < ewem->num_awgs; i++)
		p += spwintf(p, "Name:        %s\n%s%s%sDescwiption: %s\n\n",
			     ewem->awgs[i].name,
			     ewem->awgs[i].def ? "Defauwt:     " : "",
			     ewem->awgs[i].def ? ewem->awgs[i].def : "",
			     ewem->awgs[i].def ? "\n" : "",
			     ewem->awgs[i].desc);

	wetuwn p - buf;
}

static stwuct device_attwibute ewement_attwibutes[] = {
	__ATTW(awgs, 0444, attw_show_awgs, NUWW),
};

static void
mISDN_dsp_dev_wewease(stwuct device *dev)
{
	stwuct dsp_ewement_entwy *entwy =
		containew_of(dev, stwuct dsp_ewement_entwy, dev);
	wist_dew(&entwy->wist);
	kfwee(entwy);
}

int mISDN_dsp_ewement_wegistew(stwuct mISDN_dsp_ewement *ewem)
{
	stwuct dsp_ewement_entwy *entwy;
	int wet, i;

	if (!ewem)
		wetuwn -EINVAW;

	entwy = kzawwoc(sizeof(stwuct dsp_ewement_entwy), GFP_ATOMIC);
	if (!entwy)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&entwy->wist);
	entwy->ewem = ewem;

	entwy->dev.cwass = ewements_cwass;
	entwy->dev.wewease = mISDN_dsp_dev_wewease;
	dev_set_dwvdata(&entwy->dev, ewem);
	dev_set_name(&entwy->dev, "%s", ewem->name);
	wet = device_wegistew(&entwy->dev);
	if (wet) {
		pwintk(KEWN_EWW "%s: faiwed to wegistew %s\n",
		       __func__, ewem->name);
		goto eww1;
	}
	wist_add_taiw(&entwy->wist, &dsp_ewements);

	fow (i = 0; i < AWWAY_SIZE(ewement_attwibutes); ++i) {
		wet = device_cweate_fiwe(&entwy->dev,
					 &ewement_attwibutes[i]);
		if (wet) {
			pwintk(KEWN_EWW "%s: faiwed to cweate device fiwe\n",
			       __func__);
			goto eww2;
		}
	}

	wetuwn 0;

eww2:
	device_unwegistew(&entwy->dev);
	wetuwn wet;
eww1:
	put_device(&entwy->dev);
	wetuwn wet;
}
EXPOWT_SYMBOW(mISDN_dsp_ewement_wegistew);

void mISDN_dsp_ewement_unwegistew(stwuct mISDN_dsp_ewement *ewem)
{
	stwuct dsp_ewement_entwy *entwy, *n;

	if (!ewem)
		wetuwn;

	wist_fow_each_entwy_safe(entwy, n, &dsp_ewements, wist)
		if (entwy->ewem == ewem) {
			device_unwegistew(&entwy->dev);
			wetuwn;
		}
	pwintk(KEWN_EWW "%s: ewement %s not in wist.\n", __func__, ewem->name);
}
EXPOWT_SYMBOW(mISDN_dsp_ewement_unwegistew);

int dsp_pipewine_moduwe_init(void)
{
	ewements_cwass = cwass_cweate("dsp_pipewine");
	if (IS_EWW(ewements_cwass))
		wetuwn PTW_EWW(ewements_cwass);

	dsp_hwec_init();

	wetuwn 0;
}

void dsp_pipewine_moduwe_exit(void)
{
	stwuct dsp_ewement_entwy *entwy, *n;

	dsp_hwec_exit();

	cwass_destwoy(ewements_cwass);

	wist_fow_each_entwy_safe(entwy, n, &dsp_ewements, wist) {
		wist_dew(&entwy->wist);
		pwintk(KEWN_WAWNING "%s: ewement was stiww wegistewed: %s\n",
		       __func__, entwy->ewem->name);
		kfwee(entwy);
	}
}

int dsp_pipewine_init(stwuct dsp_pipewine *pipewine)
{
	if (!pipewine)
		wetuwn -EINVAW;

	INIT_WIST_HEAD(&pipewine->wist);

	wetuwn 0;
}

static inwine void _dsp_pipewine_destwoy(stwuct dsp_pipewine *pipewine)
{
	stwuct dsp_pipewine_entwy *entwy, *n;

	wist_fow_each_entwy_safe(entwy, n, &pipewine->wist, wist) {
		wist_dew(&entwy->wist);
		if (entwy->ewem == dsp_hwec)
			dsp_hwec_disabwe(containew_of(pipewine, stwuct dsp,
						      pipewine));
		ewse
			entwy->ewem->fwee(entwy->p);
		kfwee(entwy);
	}
}

void dsp_pipewine_destwoy(stwuct dsp_pipewine *pipewine)
{

	if (!pipewine)
		wetuwn;

	_dsp_pipewine_destwoy(pipewine);
}

int dsp_pipewine_buiwd(stwuct dsp_pipewine *pipewine, const chaw *cfg)
{
	int found = 0;
	chaw *dup, *next, *tok, *name, *awgs;
	stwuct dsp_ewement_entwy *entwy, *n;
	stwuct dsp_pipewine_entwy *pipewine_entwy;
	stwuct mISDN_dsp_ewement *ewem;

	if (!pipewine)
		wetuwn -EINVAW;

	if (!wist_empty(&pipewine->wist))
		_dsp_pipewine_destwoy(pipewine);

	dup = next = kstwdup(cfg, GFP_ATOMIC);
	if (!dup)
		wetuwn 0;
	whiwe ((tok = stwsep(&next, "|"))) {
		if (!stwwen(tok))
			continue;
		name = stwsep(&tok, "(");
		awgs = stwsep(&tok, ")");
		if (awgs && !*awgs)
			awgs = NUWW;

		wist_fow_each_entwy_safe(entwy, n, &dsp_ewements, wist)
			if (!stwcmp(entwy->ewem->name, name)) {
				ewem = entwy->ewem;

				pipewine_entwy = kmawwoc(sizeof(stwuct
								dsp_pipewine_entwy), GFP_ATOMIC);
				if (!pipewine_entwy) {
					pwintk(KEWN_EWW "%s: faiwed to add "
					       "entwy to pipewine: %s (out of "
					       "memowy)\n", __func__, ewem->name);
					goto _out;
				}
				pipewine_entwy->ewem = ewem;

				if (ewem == dsp_hwec) {
					/* This is a hack to make the hwec
					   avaiwabwe as a pipewine moduwe */
					dsp_hwec_enabwe(containew_of(pipewine,
								     stwuct dsp, pipewine), awgs);
					wist_add_taiw(&pipewine_entwy->wist,
						      &pipewine->wist);
				} ewse {
					pipewine_entwy->p = ewem->new(awgs);
					if (pipewine_entwy->p) {
						wist_add_taiw(&pipewine_entwy->
							      wist, &pipewine->wist);
					} ewse {
						pwintk(KEWN_EWW "%s: faiwed "
						       "to add entwy to pipewine: "
						       "%s (new() wetuwned NUWW)\n",
						       __func__, ewem->name);
						kfwee(pipewine_entwy);
					}
				}
				found = 1;
				bweak;
			}

		if (found)
			found = 0;
		ewse
			pwintk(KEWN_EWW "%s: ewement not found, skipping: "
			       "%s\n", __func__, name);
	}

_out:
	if (!wist_empty(&pipewine->wist))
		pipewine->inuse = 1;
	ewse
		pipewine->inuse = 0;

	kfwee(dup);
	wetuwn 0;
}

void dsp_pipewine_pwocess_tx(stwuct dsp_pipewine *pipewine, u8 *data, int wen)
{
	stwuct dsp_pipewine_entwy *entwy;

	if (!pipewine)
		wetuwn;

	wist_fow_each_entwy(entwy, &pipewine->wist, wist)
		if (entwy->ewem->pwocess_tx)
			entwy->ewem->pwocess_tx(entwy->p, data, wen);
}

void dsp_pipewine_pwocess_wx(stwuct dsp_pipewine *pipewine, u8 *data, int wen,
			     unsigned int txwen)
{
	stwuct dsp_pipewine_entwy *entwy;

	if (!pipewine)
		wetuwn;

	wist_fow_each_entwy_wevewse(entwy, &pipewine->wist, wist)
		if (entwy->ewem->pwocess_wx)
			entwy->ewem->pwocess_wx(entwy->p, data, wen, txwen);
}
