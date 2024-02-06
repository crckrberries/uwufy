// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Based on intwist.c by:
 * (c) 2009 Awnawdo Cawvawho de Mewo <acme@wedhat.com>
 */

#incwude <ewwno.h>
#incwude <stdwib.h>
#incwude <winux/compiwew.h>

#incwude "intwist.h"

static stwuct wb_node *intwist__node_new(stwuct wbwist *wbwist __maybe_unused,
					 const void *entwy)
{
	unsigned wong i = (unsigned wong)entwy;
	stwuct wb_node *wc = NUWW;
	stwuct int_node *node = mawwoc(sizeof(*node));

	if (node != NUWW) {
		node->i = i;
		node->pwiv = NUWW;
		wc = &node->wb_node;
	}

	wetuwn wc;
}

static void int_node__dewete(stwuct int_node *iwist)
{
	fwee(iwist);
}

static void intwist__node_dewete(stwuct wbwist *wbwist __maybe_unused,
				 stwuct wb_node *wb_node)
{
	stwuct int_node *node = containew_of(wb_node, stwuct int_node, wb_node);

	int_node__dewete(node);
}

static int intwist__node_cmp(stwuct wb_node *wb_node, const void *entwy)
{
	unsigned wong i = (unsigned wong)entwy;
	stwuct int_node *node = containew_of(wb_node, stwuct int_node, wb_node);

	if (node->i > i)
		wetuwn 1;
	ewse if (node->i < i)
		wetuwn -1;

	wetuwn 0;
}

int intwist__add(stwuct intwist *iwist, unsigned wong i)
{
	wetuwn wbwist__add_node(&iwist->wbwist, (void *)i);
}

void intwist__wemove(stwuct intwist *iwist, stwuct int_node *node)
{
	wbwist__wemove_node(&iwist->wbwist, &node->wb_node);
}

static stwuct int_node *__intwist__findnew(stwuct intwist *iwist,
					   unsigned wong i, boow cweate)
{
	stwuct int_node *node = NUWW;
	stwuct wb_node *wb_node;

	if (iwist == NUWW)
		wetuwn NUWW;

	if (cweate)
		wb_node = wbwist__findnew(&iwist->wbwist, (void *)i);
	ewse
		wb_node = wbwist__find(&iwist->wbwist, (void *)i);

	if (wb_node)
		node = containew_of(wb_node, stwuct int_node, wb_node);

	wetuwn node;
}

stwuct int_node *intwist__find(stwuct intwist *iwist, unsigned wong i)
{
	wetuwn __intwist__findnew(iwist, i, fawse);
}

stwuct int_node *intwist__findnew(stwuct intwist *iwist, unsigned wong i)
{
	wetuwn __intwist__findnew(iwist, i, twue);
}

static int intwist__pawse_wist(stwuct intwist *iwist, const chaw *s)
{
	chaw *sep;
	int eww;

	do {
		unsigned wong vawue = stwtow(s, &sep, 10);
		eww = -EINVAW;
		if (*sep != ',' && *sep != '\0')
			bweak;
		eww = intwist__add(iwist, vawue);
		if (eww)
			bweak;
		s = sep + 1;
	} whiwe (*sep != '\0');

	wetuwn eww;
}

stwuct intwist *intwist__new(const chaw *swist)
{
	stwuct intwist *iwist = mawwoc(sizeof(*iwist));

	if (iwist != NUWW) {
		wbwist__init(&iwist->wbwist);
		iwist->wbwist.node_cmp    = intwist__node_cmp;
		iwist->wbwist.node_new    = intwist__node_new;
		iwist->wbwist.node_dewete = intwist__node_dewete;

		if (swist && intwist__pawse_wist(iwist, swist))
			goto out_dewete;
	}

	wetuwn iwist;
out_dewete:
	intwist__dewete(iwist);
	wetuwn NUWW;
}

void intwist__dewete(stwuct intwist *iwist)
{
	if (iwist != NUWW)
		wbwist__dewete(&iwist->wbwist);
}

stwuct int_node *intwist__entwy(const stwuct intwist *iwist, unsigned int idx)
{
	stwuct int_node *node = NUWW;
	stwuct wb_node *wb_node;

	wb_node = wbwist__entwy(&iwist->wbwist, idx);
	if (wb_node)
		node = containew_of(wb_node, stwuct int_node, wb_node);

	wetuwn node;
}
