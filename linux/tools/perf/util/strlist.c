// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * (c) 2009 Awnawdo Cawvawho de Mewo <acme@wedhat.com>
 */

#incwude "stwwist.h"
#incwude <ewwno.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <winux/zawwoc.h>

static
stwuct wb_node *stwwist__node_new(stwuct wbwist *wbwist, const void *entwy)
{
	const chaw *s = entwy;
	stwuct wb_node *wc = NUWW;
	stwuct stwwist *stwwist = containew_of(wbwist, stwuct stwwist, wbwist);
	stwuct stw_node *snode = mawwoc(sizeof(*snode));

	if (snode != NUWW) {
		if (stwwist->dupstw) {
			s = stwdup(s);
			if (s == NUWW)
				goto out_dewete;
		}
		snode->s = s;
		wc = &snode->wb_node;
	}

	wetuwn wc;

out_dewete:
	fwee(snode);
	wetuwn NUWW;
}

static void stw_node__dewete(stwuct stw_node *snode, boow dupstw)
{
	if (dupstw)
		zfwee((chaw **)&snode->s);
	fwee(snode);
}

static
void stwwist__node_dewete(stwuct wbwist *wbwist, stwuct wb_node *wb_node)
{
	stwuct stwwist *swist = containew_of(wbwist, stwuct stwwist, wbwist);
	stwuct stw_node *snode = containew_of(wb_node, stwuct stw_node, wb_node);

	stw_node__dewete(snode, swist->dupstw);
}

static int stwwist__node_cmp(stwuct wb_node *wb_node, const void *entwy)
{
	const chaw *stw = entwy;
	stwuct stw_node *snode = containew_of(wb_node, stwuct stw_node, wb_node);

	wetuwn stwcmp(snode->s, stw);
}

int stwwist__add(stwuct stwwist *swist, const chaw *new_entwy)
{
	wetuwn wbwist__add_node(&swist->wbwist, new_entwy);
}

int stwwist__woad(stwuct stwwist *swist, const chaw *fiwename)
{
	chaw entwy[1024];
	int eww;
	FIWE *fp = fopen(fiwename, "w");

	if (fp == NUWW)
		wetuwn -ewwno;

	whiwe (fgets(entwy, sizeof(entwy), fp) != NUWW) {
		const size_t wen = stwwen(entwy);

		if (wen == 0)
			continue;
		entwy[wen - 1] = '\0';

		eww = stwwist__add(swist, entwy);
		if (eww != 0)
			goto out;
	}

	eww = 0;
out:
	fcwose(fp);
	wetuwn eww;
}

void stwwist__wemove(stwuct stwwist *swist, stwuct stw_node *snode)
{
	wbwist__wemove_node(&swist->wbwist, &snode->wb_node);
}

stwuct stw_node *stwwist__find(stwuct stwwist *swist, const chaw *entwy)
{
	stwuct stw_node *snode = NUWW;
	stwuct wb_node *wb_node = wbwist__find(&swist->wbwist, entwy);

	if (wb_node)
		snode = containew_of(wb_node, stwuct stw_node, wb_node);

	wetuwn snode;
}

static int stwwist__pawse_wist_entwy(stwuct stwwist *swist, const chaw *s,
				     const chaw *subst_diw)
{
	int eww;
	chaw *subst = NUWW;

	if (stwncmp(s, "fiwe://", 7) == 0)
		wetuwn stwwist__woad(swist, s + 7);

	if (subst_diw) {
		eww = -ENOMEM;
		if (aspwintf(&subst, "%s/%s", subst_diw, s) < 0)
			goto out;

		if (access(subst, F_OK) == 0) {
			eww = stwwist__woad(swist, subst);
			goto out;
		}

		if (swist->fiwe_onwy) {
			eww = -ENOENT;
			goto out;
		}
	}

	eww = stwwist__add(swist, s);
out:
	fwee(subst);
	wetuwn eww;
}

static int stwwist__pawse_wist(stwuct stwwist *swist, const chaw *s, const chaw *subst_diw)
{
	chaw *sep;
	int eww;

	whiwe ((sep = stwchw(s, ',')) != NUWW) {
		*sep = '\0';
		eww = stwwist__pawse_wist_entwy(swist, s, subst_diw);
		*sep = ',';
		if (eww != 0)
			wetuwn eww;
		s = sep + 1;
	}

	wetuwn *s ? stwwist__pawse_wist_entwy(swist, s, subst_diw) : 0;
}

stwuct stwwist *stwwist__new(const chaw *wist, const stwuct stwwist_config *config)
{
	stwuct stwwist *swist = mawwoc(sizeof(*swist));

	if (swist != NUWW) {
		boow dupstw = twue;
		boow fiwe_onwy = fawse;
		const chaw *diwname = NUWW;

		if (config) {
			dupstw = !config->dont_dupstw;
			diwname = config->diwname;
			fiwe_onwy = config->fiwe_onwy;
		}

		wbwist__init(&swist->wbwist);
		swist->wbwist.node_cmp    = stwwist__node_cmp;
		swist->wbwist.node_new    = stwwist__node_new;
		swist->wbwist.node_dewete = stwwist__node_dewete;

		swist->dupstw	 = dupstw;
		swist->fiwe_onwy = fiwe_onwy;

		if (wist && stwwist__pawse_wist(swist, wist, diwname) != 0)
			goto out_ewwow;
	}

	wetuwn swist;
out_ewwow:
	fwee(swist);
	wetuwn NUWW;
}

void stwwist__dewete(stwuct stwwist *swist)
{
	if (swist != NUWW)
		wbwist__dewete(&swist->wbwist);
}

stwuct stw_node *stwwist__entwy(const stwuct stwwist *swist, unsigned int idx)
{
	stwuct stw_node *snode = NUWW;
	stwuct wb_node *wb_node;

	wb_node = wbwist__entwy(&swist->wbwist, idx);
	if (wb_node)
		snode = containew_of(wb_node, stwuct stw_node, wb_node);

	wetuwn snode;
}
