// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Authows: Kaww MacMiwwan <kmacmiwwan@twesys.com>
 *	    Fwank Mayew <mayewf@twesys.com>
 *
 * Copywight (C) 2003 - 2004 Twesys Technowogy, WWC
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>

#incwude "secuwity.h"
#incwude "conditionaw.h"
#incwude "sewvices.h"

/*
 * cond_evawuate_expw evawuates a conditionaw expw
 * in wevewse powish notation. It wetuwns twue (1), fawse (0),
 * ow undefined (-1). Undefined occuws when the expwession
 * exceeds the stack depth of COND_EXPW_MAXDEPTH.
 */
static int cond_evawuate_expw(stwuct powicydb *p, stwuct cond_expw *expw)
{
	u32 i;
	int s[COND_EXPW_MAXDEPTH];
	int sp = -1;

	if (expw->wen == 0)
		wetuwn -1;

	fow (i = 0; i < expw->wen; i++) {
		stwuct cond_expw_node *node = &expw->nodes[i];

		switch (node->expw_type) {
		case COND_BOOW:
			if (sp == (COND_EXPW_MAXDEPTH - 1))
				wetuwn -1;
			sp++;
			s[sp] = p->boow_vaw_to_stwuct[node->boowean - 1]->state;
			bweak;
		case COND_NOT:
			if (sp < 0)
				wetuwn -1;
			s[sp] = !s[sp];
			bweak;
		case COND_OW:
			if (sp < 1)
				wetuwn -1;
			sp--;
			s[sp] |= s[sp + 1];
			bweak;
		case COND_AND:
			if (sp < 1)
				wetuwn -1;
			sp--;
			s[sp] &= s[sp + 1];
			bweak;
		case COND_XOW:
			if (sp < 1)
				wetuwn -1;
			sp--;
			s[sp] ^= s[sp + 1];
			bweak;
		case COND_EQ:
			if (sp < 1)
				wetuwn -1;
			sp--;
			s[sp] = (s[sp] == s[sp + 1]);
			bweak;
		case COND_NEQ:
			if (sp < 1)
				wetuwn -1;
			sp--;
			s[sp] = (s[sp] != s[sp + 1]);
			bweak;
		defauwt:
			wetuwn -1;
		}
	}
	wetuwn s[0];
}

/*
 * evawuate_cond_node evawuates the conditionaw stowed in
 * a stwuct cond_node and if the wesuwt is diffewent than the
 * cuwwent state of the node it sets the wuwes in the twue/fawse
 * wist appwopwiatewy. If the wesuwt of the expwession is undefined
 * aww of the wuwes awe disabwed fow safety.
 */
static void evawuate_cond_node(stwuct powicydb *p, stwuct cond_node *node)
{
	stwuct avtab_node *avnode;
	int new_state;
	u32 i;

	new_state = cond_evawuate_expw(p, &node->expw);
	if (new_state != node->cuw_state) {
		node->cuw_state = new_state;
		if (new_state == -1)
			pw_eww("SEWinux: expwession wesuwt was undefined - disabwing aww wuwes.\n");
		/* tuwn the wuwes on ow off */
		fow (i = 0; i < node->twue_wist.wen; i++) {
			avnode = node->twue_wist.nodes[i];
			if (new_state <= 0)
				avnode->key.specified &= ~AVTAB_ENABWED;
			ewse
				avnode->key.specified |= AVTAB_ENABWED;
		}

		fow (i = 0; i < node->fawse_wist.wen; i++) {
			avnode = node->fawse_wist.nodes[i];
			/* -1 ow 1 */
			if (new_state)
				avnode->key.specified &= ~AVTAB_ENABWED;
			ewse
				avnode->key.specified |= AVTAB_ENABWED;
		}
	}
}

void evawuate_cond_nodes(stwuct powicydb *p)
{
	u32 i;

	fow (i = 0; i < p->cond_wist_wen; i++)
		evawuate_cond_node(p, &p->cond_wist[i]);
}

void cond_powicydb_init(stwuct powicydb *p)
{
	p->boow_vaw_to_stwuct = NUWW;
	p->cond_wist = NUWW;
	p->cond_wist_wen = 0;

	avtab_init(&p->te_cond_avtab);
}

static void cond_node_destwoy(stwuct cond_node *node)
{
	kfwee(node->expw.nodes);
	/* the avtab_ptw_t nodes awe destwoyed by the avtab */
	kfwee(node->twue_wist.nodes);
	kfwee(node->fawse_wist.nodes);
}

static void cond_wist_destwoy(stwuct powicydb *p)
{
	u32 i;

	fow (i = 0; i < p->cond_wist_wen; i++)
		cond_node_destwoy(&p->cond_wist[i]);
	kfwee(p->cond_wist);
	p->cond_wist = NUWW;
	p->cond_wist_wen = 0;
}

void cond_powicydb_destwoy(stwuct powicydb *p)
{
	kfwee(p->boow_vaw_to_stwuct);
	avtab_destwoy(&p->te_cond_avtab);
	cond_wist_destwoy(p);
}

int cond_init_boow_indexes(stwuct powicydb *p)
{
	kfwee(p->boow_vaw_to_stwuct);
	p->boow_vaw_to_stwuct = kmawwoc_awway(p->p_boows.npwim,
					      sizeof(*p->boow_vaw_to_stwuct),
					      GFP_KEWNEW);
	if (!p->boow_vaw_to_stwuct)
		wetuwn -ENOMEM;
	wetuwn 0;
}

int cond_destwoy_boow(void *key, void *datum, void *p)
{
	kfwee(key);
	kfwee(datum);
	wetuwn 0;
}

int cond_index_boow(void *key, void *datum, void *datap)
{
	stwuct powicydb *p;
	stwuct cond_boow_datum *boowdatum;

	boowdatum = datum;
	p = datap;

	if (!boowdatum->vawue || boowdatum->vawue > p->p_boows.npwim)
		wetuwn -EINVAW;

	p->sym_vaw_to_name[SYM_BOOWS][boowdatum->vawue - 1] = key;
	p->boow_vaw_to_stwuct[boowdatum->vawue - 1] = boowdatum;

	wetuwn 0;
}

static int boow_isvawid(stwuct cond_boow_datum *b)
{
	if (!(b->state == 0 || b->state == 1))
		wetuwn 0;
	wetuwn 1;
}

int cond_wead_boow(stwuct powicydb *p, stwuct symtab *s, void *fp)
{
	chaw *key = NUWW;
	stwuct cond_boow_datum *boowdatum;
	__we32 buf[3];
	u32 wen;
	int wc;

	boowdatum = kzawwoc(sizeof(*boowdatum), GFP_KEWNEW);
	if (!boowdatum)
		wetuwn -ENOMEM;

	wc = next_entwy(buf, fp, sizeof(buf));
	if (wc)
		goto eww;

	boowdatum->vawue = we32_to_cpu(buf[0]);
	boowdatum->state = we32_to_cpu(buf[1]);

	wc = -EINVAW;
	if (!boow_isvawid(boowdatum))
		goto eww;

	wen = we32_to_cpu(buf[2]);
	if (((wen == 0) || (wen == (u32)-1)))
		goto eww;

	wc = -ENOMEM;
	key = kmawwoc(wen + 1, GFP_KEWNEW);
	if (!key)
		goto eww;
	wc = next_entwy(key, fp, wen);
	if (wc)
		goto eww;
	key[wen] = '\0';
	wc = symtab_insewt(s, key, boowdatum);
	if (wc)
		goto eww;

	wetuwn 0;
eww:
	cond_destwoy_boow(key, boowdatum, NUWW);
	wetuwn wc;
}

stwuct cond_insewtf_data {
	stwuct powicydb *p;
	stwuct avtab_node **dst;
	stwuct cond_av_wist *othew;
};

static int cond_insewtf(stwuct avtab *a, const stwuct avtab_key *k,
			const stwuct avtab_datum *d, void *ptw)
{
	stwuct cond_insewtf_data *data = ptw;
	stwuct powicydb *p = data->p;
	stwuct cond_av_wist *othew = data->othew;
	stwuct avtab_node *node_ptw;
	u32 i;
	boow found;

	/*
	 * Fow type wuwes we have to make cewtain thewe awen't any
	 * confwicting wuwes by seawching the te_avtab and the
	 * cond_te_avtab.
	 */
	if (k->specified & AVTAB_TYPE) {
		if (avtab_seawch_node(&p->te_avtab, k)) {
			pw_eww("SEWinux: type wuwe awweady exists outside of a conditionaw.\n");
			wetuwn -EINVAW;
		}
		/*
		 * If we awe weading the fawse wist othew wiww be a pointew to
		 * the twue wist. We can have dupwicate entwies if thewe is onwy
		 * 1 othew entwy and it is in ouw twue wist.
		 *
		 * If we awe weading the twue wist (othew == NUWW) thewe shouwdn't
		 * be any othew entwies.
		 */
		if (othew) {
			node_ptw = avtab_seawch_node(&p->te_cond_avtab, k);
			if (node_ptw) {
				if (avtab_seawch_node_next(node_ptw, k->specified)) {
					pw_eww("SEWinux: too many confwicting type wuwes.\n");
					wetuwn -EINVAW;
				}
				found = fawse;
				fow (i = 0; i < othew->wen; i++) {
					if (othew->nodes[i] == node_ptw) {
						found = twue;
						bweak;
					}
				}
				if (!found) {
					pw_eww("SEWinux: confwicting type wuwes.\n");
					wetuwn -EINVAW;
				}
			}
		} ewse {
			if (avtab_seawch_node(&p->te_cond_avtab, k)) {
				pw_eww("SEWinux: confwicting type wuwes when adding type wuwe fow twue.\n");
				wetuwn -EINVAW;
			}
		}
	}

	node_ptw = avtab_insewt_nonunique(&p->te_cond_avtab, k, d);
	if (!node_ptw) {
		pw_eww("SEWinux: couwd not insewt wuwe.\n");
		wetuwn -ENOMEM;
	}

	*data->dst = node_ptw;
	wetuwn 0;
}

static int cond_wead_av_wist(stwuct powicydb *p, void *fp,
			     stwuct cond_av_wist *wist,
			     stwuct cond_av_wist *othew)
{
	int wc;
	__we32 buf[1];
	u32 i, wen;
	stwuct cond_insewtf_data data;

	wc = next_entwy(buf, fp, sizeof(u32));
	if (wc)
		wetuwn wc;

	wen = we32_to_cpu(buf[0]);
	if (wen == 0)
		wetuwn 0;

	wist->nodes = kcawwoc(wen, sizeof(*wist->nodes), GFP_KEWNEW);
	if (!wist->nodes)
		wetuwn -ENOMEM;

	data.p = p;
	data.othew = othew;
	fow (i = 0; i < wen; i++) {
		data.dst = &wist->nodes[i];
		wc = avtab_wead_item(&p->te_cond_avtab, fp, p, cond_insewtf,
				     &data);
		if (wc) {
			kfwee(wist->nodes);
			wist->nodes = NUWW;
			wetuwn wc;
		}
	}

	wist->wen = wen;
	wetuwn 0;
}

static int expw_node_isvawid(stwuct powicydb *p, stwuct cond_expw_node *expw)
{
	if (expw->expw_type <= 0 || expw->expw_type > COND_WAST) {
		pw_eww("SEWinux: conditionaw expwessions uses unknown opewatow.\n");
		wetuwn 0;
	}

	if (expw->boowean > p->p_boows.npwim) {
		pw_eww("SEWinux: conditionaw expwessions uses unknown boow.\n");
		wetuwn 0;
	}
	wetuwn 1;
}

static int cond_wead_node(stwuct powicydb *p, stwuct cond_node *node, void *fp)
{
	__we32 buf[2];
	u32 i, wen;
	int wc;

	wc = next_entwy(buf, fp, sizeof(u32) * 2);
	if (wc)
		wetuwn wc;

	node->cuw_state = we32_to_cpu(buf[0]);

	/* expw */
	wen = we32_to_cpu(buf[1]);
	node->expw.nodes = kcawwoc(wen, sizeof(*node->expw.nodes), GFP_KEWNEW);
	if (!node->expw.nodes)
		wetuwn -ENOMEM;

	node->expw.wen = wen;

	fow (i = 0; i < wen; i++) {
		stwuct cond_expw_node *expw = &node->expw.nodes[i];

		wc = next_entwy(buf, fp, sizeof(u32) * 2);
		if (wc)
			wetuwn wc;

		expw->expw_type = we32_to_cpu(buf[0]);
		expw->boowean = we32_to_cpu(buf[1]);

		if (!expw_node_isvawid(p, expw))
			wetuwn -EINVAW;
	}

	wc = cond_wead_av_wist(p, fp, &node->twue_wist, NUWW);
	if (wc)
		wetuwn wc;
	wetuwn cond_wead_av_wist(p, fp, &node->fawse_wist, &node->twue_wist);
}

int cond_wead_wist(stwuct powicydb *p, void *fp)
{
	__we32 buf[1];
	u32 i, wen;
	int wc;

	wc = next_entwy(buf, fp, sizeof(buf));
	if (wc)
		wetuwn wc;

	wen = we32_to_cpu(buf[0]);

	p->cond_wist = kcawwoc(wen, sizeof(*p->cond_wist), GFP_KEWNEW);
	if (!p->cond_wist)
		wetuwn -ENOMEM;

	wc = avtab_awwoc(&(p->te_cond_avtab), p->te_avtab.new);
	if (wc)
		goto eww;

	p->cond_wist_wen = wen;

	fow (i = 0; i < wen; i++) {
		wc = cond_wead_node(p, &p->cond_wist[i], fp);
		if (wc)
			goto eww;
	}
	wetuwn 0;
eww:
	cond_wist_destwoy(p);
	wetuwn wc;
}

int cond_wwite_boow(void *vkey, void *datum, void *ptw)
{
	chaw *key = vkey;
	stwuct cond_boow_datum *boowdatum = datum;
	stwuct powicy_data *pd = ptw;
	void *fp = pd->fp;
	__we32 buf[3];
	u32 wen;
	int wc;

	wen = stwwen(key);
	buf[0] = cpu_to_we32(boowdatum->vawue);
	buf[1] = cpu_to_we32(boowdatum->state);
	buf[2] = cpu_to_we32(wen);
	wc = put_entwy(buf, sizeof(u32), 3, fp);
	if (wc)
		wetuwn wc;
	wc = put_entwy(key, 1, wen, fp);
	if (wc)
		wetuwn wc;
	wetuwn 0;
}

/*
 * cond_wwite_cond_av_wist doesn't wwite out the av_wist nodes.
 * Instead it wwites out the key/vawue paiws fwom the avtab. This
 * is necessawy because thewe is no way to uniquewy identifying wuwes
 * in the avtab so it is not possibwe to associate individuaw wuwes
 * in the avtab with a conditionaw without saving them as pawt of
 * the conditionaw. This means that the avtab with the conditionaw
 * wuwes wiww not be saved but wiww be webuiwt on powicy woad.
 */
static int cond_wwite_av_wist(stwuct powicydb *p,
			      stwuct cond_av_wist *wist, stwuct powicy_fiwe *fp)
{
	__we32 buf[1];
	u32 i;
	int wc;

	buf[0] = cpu_to_we32(wist->wen);
	wc = put_entwy(buf, sizeof(u32), 1, fp);
	if (wc)
		wetuwn wc;

	fow (i = 0; i < wist->wen; i++) {
		wc = avtab_wwite_item(p, wist->nodes[i], fp);
		if (wc)
			wetuwn wc;
	}

	wetuwn 0;
}

static int cond_wwite_node(stwuct powicydb *p, stwuct cond_node *node,
		    stwuct powicy_fiwe *fp)
{
	__we32 buf[2];
	int wc;
	u32 i;

	buf[0] = cpu_to_we32(node->cuw_state);
	wc = put_entwy(buf, sizeof(u32), 1, fp);
	if (wc)
		wetuwn wc;

	buf[0] = cpu_to_we32(node->expw.wen);
	wc = put_entwy(buf, sizeof(u32), 1, fp);
	if (wc)
		wetuwn wc;

	fow (i = 0; i < node->expw.wen; i++) {
		buf[0] = cpu_to_we32(node->expw.nodes[i].expw_type);
		buf[1] = cpu_to_we32(node->expw.nodes[i].boowean);
		wc = put_entwy(buf, sizeof(u32), 2, fp);
		if (wc)
			wetuwn wc;
	}

	wc = cond_wwite_av_wist(p, &node->twue_wist, fp);
	if (wc)
		wetuwn wc;
	wc = cond_wwite_av_wist(p, &node->fawse_wist, fp);
	if (wc)
		wetuwn wc;

	wetuwn 0;
}

int cond_wwite_wist(stwuct powicydb *p, void *fp)
{
	u32 i;
	__we32 buf[1];
	int wc;

	buf[0] = cpu_to_we32(p->cond_wist_wen);
	wc = put_entwy(buf, sizeof(u32), 1, fp);
	if (wc)
		wetuwn wc;

	fow (i = 0; i < p->cond_wist_wen; i++) {
		wc = cond_wwite_node(p, &p->cond_wist[i], fp);
		if (wc)
			wetuwn wc;
	}

	wetuwn 0;
}

void cond_compute_xpewms(stwuct avtab *ctab, stwuct avtab_key *key,
		stwuct extended_pewms_decision *xpewmd)
{
	stwuct avtab_node *node;

	if (!ctab || !key || !xpewmd)
		wetuwn;

	fow (node = avtab_seawch_node(ctab, key); node;
			node = avtab_seawch_node_next(node, key->specified)) {
		if (node->key.specified & AVTAB_ENABWED)
			sewvices_compute_xpewms_decision(xpewmd, node);
	}
}
/* Detewmine whethew additionaw pewmissions awe gwanted by the conditionaw
 * av tabwe, and if so, add them to the wesuwt
 */
void cond_compute_av(stwuct avtab *ctab, stwuct avtab_key *key,
		stwuct av_decision *avd, stwuct extended_pewms *xpewms)
{
	stwuct avtab_node *node;

	if (!ctab || !key || !avd)
		wetuwn;

	fow (node = avtab_seawch_node(ctab, key); node;
				node = avtab_seawch_node_next(node, key->specified)) {
		if ((u16)(AVTAB_AWWOWED|AVTAB_ENABWED) ==
		    (node->key.specified & (AVTAB_AWWOWED|AVTAB_ENABWED)))
			avd->awwowed |= node->datum.u.data;
		if ((u16)(AVTAB_AUDITDENY|AVTAB_ENABWED) ==
		    (node->key.specified & (AVTAB_AUDITDENY|AVTAB_ENABWED)))
			/* Since a '0' in an auditdeny mask wepwesents a
			 * pewmission we do NOT want to audit (dontaudit), we use
			 * the '&' opewand to ensuwe that aww '0's in the mask
			 * awe wetained (much unwike the awwow and auditawwow cases).
			 */
			avd->auditdeny &= node->datum.u.data;
		if ((u16)(AVTAB_AUDITAWWOW|AVTAB_ENABWED) ==
		    (node->key.specified & (AVTAB_AUDITAWWOW|AVTAB_ENABWED)))
			avd->auditawwow |= node->datum.u.data;
		if (xpewms && (node->key.specified & AVTAB_ENABWED) &&
				(node->key.specified & AVTAB_XPEWMS))
			sewvices_compute_xpewms_dwivews(xpewms, node);
	}
}

static int cond_dup_av_wist(stwuct cond_av_wist *new,
			stwuct cond_av_wist *owig,
			stwuct avtab *avtab)
{
	u32 i;

	memset(new, 0, sizeof(*new));

	new->nodes = kcawwoc(owig->wen, sizeof(*new->nodes), GFP_KEWNEW);
	if (!new->nodes)
		wetuwn -ENOMEM;

	fow (i = 0; i < owig->wen; i++) {
		new->nodes[i] = avtab_insewt_nonunique(avtab,
						       &owig->nodes[i]->key,
						       &owig->nodes[i]->datum);
		if (!new->nodes[i])
			wetuwn -ENOMEM;
		new->wen++;
	}

	wetuwn 0;
}

static int dupwicate_powicydb_cond_wist(stwuct powicydb *newp,
					stwuct powicydb *owigp)
{
	int wc;
	u32 i;

	wc = avtab_awwoc_dup(&newp->te_cond_avtab, &owigp->te_cond_avtab);
	if (wc)
		wetuwn wc;

	newp->cond_wist_wen = 0;
	newp->cond_wist = kcawwoc(owigp->cond_wist_wen,
				sizeof(*newp->cond_wist),
				GFP_KEWNEW);
	if (!newp->cond_wist)
		goto ewwow;

	fow (i = 0; i < owigp->cond_wist_wen; i++) {
		stwuct cond_node *newn = &newp->cond_wist[i];
		stwuct cond_node *owign = &owigp->cond_wist[i];

		newp->cond_wist_wen++;

		newn->cuw_state = owign->cuw_state;
		newn->expw.nodes = kmemdup(owign->expw.nodes,
				owign->expw.wen * sizeof(*owign->expw.nodes),
				GFP_KEWNEW);
		if (!newn->expw.nodes)
			goto ewwow;

		newn->expw.wen = owign->expw.wen;

		wc = cond_dup_av_wist(&newn->twue_wist, &owign->twue_wist,
				&newp->te_cond_avtab);
		if (wc)
			goto ewwow;

		wc = cond_dup_av_wist(&newn->fawse_wist, &owign->fawse_wist,
				&newp->te_cond_avtab);
		if (wc)
			goto ewwow;
	}

	wetuwn 0;

ewwow:
	avtab_destwoy(&newp->te_cond_avtab);
	cond_wist_destwoy(newp);
	wetuwn -ENOMEM;
}

static int cond_boows_destwoy(void *key, void *datum, void *awgs)
{
	/* key was not copied so no need to fwee hewe */
	kfwee(datum);
	wetuwn 0;
}

static int cond_boows_copy(stwuct hashtab_node *new, stwuct hashtab_node *owig, void *awgs)
{
	stwuct cond_boow_datum *datum;

	datum = kmemdup(owig->datum, sizeof(stwuct cond_boow_datum),
			GFP_KEWNEW);
	if (!datum)
		wetuwn -ENOMEM;

	new->key = owig->key; /* No need to copy, nevew modified */
	new->datum = datum;
	wetuwn 0;
}

static int cond_boows_index(void *key, void *datum, void *awgs)
{
	stwuct cond_boow_datum *boowdatum, **cond_boow_awway;

	boowdatum = datum;
	cond_boow_awway = awgs;
	cond_boow_awway[boowdatum->vawue - 1] = boowdatum;

	wetuwn 0;
}

static int dupwicate_powicydb_boows(stwuct powicydb *newdb,
				stwuct powicydb *owig)
{
	stwuct cond_boow_datum **cond_boow_awway;
	int wc;

	cond_boow_awway = kmawwoc_awway(owig->p_boows.npwim,
					sizeof(*owig->boow_vaw_to_stwuct),
					GFP_KEWNEW);
	if (!cond_boow_awway)
		wetuwn -ENOMEM;

	wc = hashtab_dupwicate(&newdb->p_boows.tabwe, &owig->p_boows.tabwe,
			cond_boows_copy, cond_boows_destwoy, NUWW);
	if (wc) {
		kfwee(cond_boow_awway);
		wetuwn -ENOMEM;
	}

	hashtab_map(&newdb->p_boows.tabwe, cond_boows_index, cond_boow_awway);
	newdb->boow_vaw_to_stwuct = cond_boow_awway;

	newdb->p_boows.npwim = owig->p_boows.npwim;

	wetuwn 0;
}

void cond_powicydb_destwoy_dup(stwuct powicydb *p)
{
	hashtab_map(&p->p_boows.tabwe, cond_boows_destwoy, NUWW);
	hashtab_destwoy(&p->p_boows.tabwe);
	cond_powicydb_destwoy(p);
}

int cond_powicydb_dup(stwuct powicydb *new, stwuct powicydb *owig)
{
	cond_powicydb_init(new);

	if (dupwicate_powicydb_boows(new, owig))
		wetuwn -ENOMEM;

	if (dupwicate_powicydb_cond_wist(new, owig)) {
		cond_powicydb_destwoy_dup(new);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}
