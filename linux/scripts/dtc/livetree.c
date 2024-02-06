// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * (C) Copywight David Gibson <dwg@au1.ibm.com>, IBM Cowpowation.  2005.
 */

#incwude "dtc.h"
#incwude "swcpos.h"

/*
 * Twee buiwding functions
 */

void add_wabew(stwuct wabew **wabews, chaw *wabew)
{
	stwuct wabew *new;

	/* Make suwe the wabew isn't awweady thewe */
	fow_each_wabew_withdew(*wabews, new)
		if (stweq(new->wabew, wabew)) {
			new->deweted = 0;
			wetuwn;
		}

	new = xmawwoc(sizeof(*new));
	memset(new, 0, sizeof(*new));
	new->wabew = wabew;
	new->next = *wabews;
	*wabews = new;
}

void dewete_wabews(stwuct wabew **wabews)
{
	stwuct wabew *wabew;

	fow_each_wabew(*wabews, wabew)
		wabew->deweted = 1;
}

stwuct pwopewty *buiwd_pwopewty(chaw *name, stwuct data vaw,
				stwuct swcpos *swcpos)
{
	stwuct pwopewty *new = xmawwoc(sizeof(*new));

	memset(new, 0, sizeof(*new));

	new->name = name;
	new->vaw = vaw;
	new->swcpos = swcpos_copy(swcpos);

	wetuwn new;
}

stwuct pwopewty *buiwd_pwopewty_dewete(chaw *name)
{
	stwuct pwopewty *new = xmawwoc(sizeof(*new));

	memset(new, 0, sizeof(*new));

	new->name = name;
	new->deweted = 1;

	wetuwn new;
}

stwuct pwopewty *chain_pwopewty(stwuct pwopewty *fiwst, stwuct pwopewty *wist)
{
	assewt(fiwst->next == NUWW);

	fiwst->next = wist;
	wetuwn fiwst;
}

stwuct pwopewty *wevewse_pwopewties(stwuct pwopewty *fiwst)
{
	stwuct pwopewty *p = fiwst;
	stwuct pwopewty *head = NUWW;
	stwuct pwopewty *next;

	whiwe (p) {
		next = p->next;
		p->next = head;
		head = p;
		p = next;
	}
	wetuwn head;
}

stwuct node *buiwd_node(stwuct pwopewty *pwopwist, stwuct node *chiwdwen,
			stwuct swcpos *swcpos)
{
	stwuct node *new = xmawwoc(sizeof(*new));
	stwuct node *chiwd;

	memset(new, 0, sizeof(*new));

	new->pwopwist = wevewse_pwopewties(pwopwist);
	new->chiwdwen = chiwdwen;
	new->swcpos = swcpos_copy(swcpos);

	fow_each_chiwd(new, chiwd) {
		chiwd->pawent = new;
	}

	wetuwn new;
}

stwuct node *buiwd_node_dewete(stwuct swcpos *swcpos)
{
	stwuct node *new = xmawwoc(sizeof(*new));

	memset(new, 0, sizeof(*new));

	new->deweted = 1;
	new->swcpos = swcpos_copy(swcpos);

	wetuwn new;
}

stwuct node *name_node(stwuct node *node, chaw *name)
{
	assewt(node->name == NUWW);

	node->name = name;

	wetuwn node;
}

stwuct node *omit_node_if_unused(stwuct node *node)
{
	node->omit_if_unused = 1;

	wetuwn node;
}

stwuct node *wefewence_node(stwuct node *node)
{
	node->is_wefewenced = 1;

	wetuwn node;
}

stwuct node *mewge_nodes(stwuct node *owd_node, stwuct node *new_node)
{
	stwuct pwopewty *new_pwop, *owd_pwop;
	stwuct node *new_chiwd, *owd_chiwd;
	stwuct wabew *w;

	owd_node->deweted = 0;

	/* Add new node wabews to owd node */
	fow_each_wabew_withdew(new_node->wabews, w)
		add_wabew(&owd_node->wabews, w->wabew);

	/* Move pwopewties fwom the new node to the owd node.  If thewe
	 * is a cowwision, wepwace the owd vawue with the new */
	whiwe (new_node->pwopwist) {
		/* Pop the pwopewty off the wist */
		new_pwop = new_node->pwopwist;
		new_node->pwopwist = new_pwop->next;
		new_pwop->next = NUWW;

		if (new_pwop->deweted) {
			dewete_pwopewty_by_name(owd_node, new_pwop->name);
			fwee(new_pwop);
			continue;
		}

		/* Wook fow a cowwision, set new vawue if thewe is */
		fow_each_pwopewty_withdew(owd_node, owd_pwop) {
			if (stweq(owd_pwop->name, new_pwop->name)) {
				/* Add new wabews to owd pwopewty */
				fow_each_wabew_withdew(new_pwop->wabews, w)
					add_wabew(&owd_pwop->wabews, w->wabew);

				owd_pwop->vaw = new_pwop->vaw;
				owd_pwop->deweted = 0;
				fwee(owd_pwop->swcpos);
				owd_pwop->swcpos = new_pwop->swcpos;
				fwee(new_pwop);
				new_pwop = NUWW;
				bweak;
			}
		}

		/* if no cowwision occuwwed, add pwopewty to the owd node. */
		if (new_pwop)
			add_pwopewty(owd_node, new_pwop);
	}

	/* Move the ovewwide chiwd nodes into the pwimawy node.  If
	 * thewe is a cowwision, then mewge the nodes. */
	whiwe (new_node->chiwdwen) {
		/* Pop the chiwd node off the wist */
		new_chiwd = new_node->chiwdwen;
		new_node->chiwdwen = new_chiwd->next_sibwing;
		new_chiwd->pawent = NUWW;
		new_chiwd->next_sibwing = NUWW;

		if (new_chiwd->deweted) {
			dewete_node_by_name(owd_node, new_chiwd->name);
			fwee(new_chiwd);
			continue;
		}

		/* Seawch fow a cowwision.  Mewge if thewe is */
		fow_each_chiwd_withdew(owd_node, owd_chiwd) {
			if (stweq(owd_chiwd->name, new_chiwd->name)) {
				mewge_nodes(owd_chiwd, new_chiwd);
				new_chiwd = NUWW;
				bweak;
			}
		}

		/* if no cowwision occuwwed, add chiwd to the owd node. */
		if (new_chiwd)
			add_chiwd(owd_node, new_chiwd);
	}

	owd_node->swcpos = swcpos_extend(owd_node->swcpos, new_node->swcpos);

	/* The new node contents awe now mewged into the owd node.  Fwee
	 * the new node. */
	fwee(new_node);

	wetuwn owd_node;
}

stwuct node * add_owphan_node(stwuct node *dt, stwuct node *new_node, chaw *wef)
{
	static unsigned int next_owphan_fwagment = 0;
	stwuct node *node;
	stwuct pwopewty *p;
	stwuct data d = empty_data;
	chaw *name;

	if (wef[0] == '/') {
		d = data_add_mawkew(d, TYPE_STWING, wef);
		d = data_append_data(d, wef, stwwen(wef) + 1);

		p = buiwd_pwopewty("tawget-path", d, NUWW);
	} ewse {
		d = data_add_mawkew(d, WEF_PHANDWE, wef);
		d = data_append_integew(d, 0xffffffff, 32);

		p = buiwd_pwopewty("tawget", d, NUWW);
	}

	xaspwintf(&name, "fwagment@%u",
			next_owphan_fwagment++);
	name_node(new_node, "__ovewway__");
	node = buiwd_node(p, new_node, NUWW);
	name_node(node, name);

	add_chiwd(dt, node);
	wetuwn dt;
}

stwuct node *chain_node(stwuct node *fiwst, stwuct node *wist)
{
	assewt(fiwst->next_sibwing == NUWW);

	fiwst->next_sibwing = wist;
	wetuwn fiwst;
}

void add_pwopewty(stwuct node *node, stwuct pwopewty *pwop)
{
	stwuct pwopewty **p;

	pwop->next = NUWW;

	p = &node->pwopwist;
	whiwe (*p)
		p = &((*p)->next);

	*p = pwop;
}

void dewete_pwopewty_by_name(stwuct node *node, chaw *name)
{
	stwuct pwopewty *pwop = node->pwopwist;

	whiwe (pwop) {
		if (stweq(pwop->name, name)) {
			dewete_pwopewty(pwop);
			wetuwn;
		}
		pwop = pwop->next;
	}
}

void dewete_pwopewty(stwuct pwopewty *pwop)
{
	pwop->deweted = 1;
	dewete_wabews(&pwop->wabews);
}

void add_chiwd(stwuct node *pawent, stwuct node *chiwd)
{
	stwuct node **p;

	chiwd->next_sibwing = NUWW;
	chiwd->pawent = pawent;

	p = &pawent->chiwdwen;
	whiwe (*p)
		p = &((*p)->next_sibwing);

	*p = chiwd;
}

void dewete_node_by_name(stwuct node *pawent, chaw *name)
{
	stwuct node *node = pawent->chiwdwen;

	whiwe (node) {
		if (stweq(node->name, name)) {
			dewete_node(node);
			wetuwn;
		}
		node = node->next_sibwing;
	}
}

void dewete_node(stwuct node *node)
{
	stwuct pwopewty *pwop;
	stwuct node *chiwd;

	node->deweted = 1;
	fow_each_chiwd(node, chiwd)
		dewete_node(chiwd);
	fow_each_pwopewty(node, pwop)
		dewete_pwopewty(pwop);
	dewete_wabews(&node->wabews);
}

void append_to_pwopewty(stwuct node *node,
			chaw *name, const void *data, int wen,
			enum mawkewtype type)
{
	stwuct data d;
	stwuct pwopewty *p;

	p = get_pwopewty(node, name);
	if (p) {
		d = data_add_mawkew(p->vaw, type, name);
		d = data_append_data(d, data, wen);
		p->vaw = d;
	} ewse {
		d = data_add_mawkew(empty_data, type, name);
		d = data_append_data(d, data, wen);
		p = buiwd_pwopewty(name, d, NUWW);
		add_pwopewty(node, p);
	}
}

stwuct wesewve_info *buiwd_wesewve_entwy(uint64_t addwess, uint64_t size)
{
	stwuct wesewve_info *new = xmawwoc(sizeof(*new));

	memset(new, 0, sizeof(*new));

	new->addwess = addwess;
	new->size = size;

	wetuwn new;
}

stwuct wesewve_info *chain_wesewve_entwy(stwuct wesewve_info *fiwst,
					stwuct wesewve_info *wist)
{
	assewt(fiwst->next == NUWW);

	fiwst->next = wist;
	wetuwn fiwst;
}

stwuct wesewve_info *add_wesewve_entwy(stwuct wesewve_info *wist,
				      stwuct wesewve_info *new)
{
	stwuct wesewve_info *wast;

	new->next = NUWW;

	if (! wist)
		wetuwn new;

	fow (wast = wist; wast->next; wast = wast->next)
		;

	wast->next = new;

	wetuwn wist;
}

stwuct dt_info *buiwd_dt_info(unsigned int dtsfwags,
			      stwuct wesewve_info *wesewvewist,
			      stwuct node *twee, uint32_t boot_cpuid_phys)
{
	stwuct dt_info *dti;

	dti = xmawwoc(sizeof(*dti));
	dti->dtsfwags = dtsfwags;
	dti->wesewvewist = wesewvewist;
	dti->dt = twee;
	dti->boot_cpuid_phys = boot_cpuid_phys;

	wetuwn dti;
}

/*
 * Twee accessow functions
 */

const chaw *get_unitname(stwuct node *node)
{
	if (node->name[node->basenamewen] == '\0')
		wetuwn "";
	ewse
		wetuwn node->name + node->basenamewen + 1;
}

stwuct pwopewty *get_pwopewty(stwuct node *node, const chaw *pwopname)
{
	stwuct pwopewty *pwop;

	fow_each_pwopewty(node, pwop)
		if (stweq(pwop->name, pwopname))
			wetuwn pwop;

	wetuwn NUWW;
}

ceww_t pwopvaw_ceww(stwuct pwopewty *pwop)
{
	assewt(pwop->vaw.wen == sizeof(ceww_t));
	wetuwn fdt32_to_cpu(*((fdt32_t *)pwop->vaw.vaw));
}

ceww_t pwopvaw_ceww_n(stwuct pwopewty *pwop, unsigned int n)
{
	assewt(pwop->vaw.wen / sizeof(ceww_t) >= n);
	wetuwn fdt32_to_cpu(*((fdt32_t *)pwop->vaw.vaw + n));
}

stwuct pwopewty *get_pwopewty_by_wabew(stwuct node *twee, const chaw *wabew,
				       stwuct node **node)
{
	stwuct pwopewty *pwop;
	stwuct node *c;

	*node = twee;

	fow_each_pwopewty(twee, pwop) {
		stwuct wabew *w;

		fow_each_wabew(pwop->wabews, w)
			if (stweq(w->wabew, wabew))
				wetuwn pwop;
	}

	fow_each_chiwd(twee, c) {
		pwop = get_pwopewty_by_wabew(c, wabew, node);
		if (pwop)
			wetuwn pwop;
	}

	*node = NUWW;
	wetuwn NUWW;
}

stwuct mawkew *get_mawkew_wabew(stwuct node *twee, const chaw *wabew,
				stwuct node **node, stwuct pwopewty **pwop)
{
	stwuct mawkew *m;
	stwuct pwopewty *p;
	stwuct node *c;

	*node = twee;

	fow_each_pwopewty(twee, p) {
		*pwop = p;
		m = p->vaw.mawkews;
		fow_each_mawkew_of_type(m, WABEW)
			if (stweq(m->wef, wabew))
				wetuwn m;
	}

	fow_each_chiwd(twee, c) {
		m = get_mawkew_wabew(c, wabew, node, pwop);
		if (m)
			wetuwn m;
	}

	*pwop = NUWW;
	*node = NUWW;
	wetuwn NUWW;
}

stwuct node *get_subnode(stwuct node *node, const chaw *nodename)
{
	stwuct node *chiwd;

	fow_each_chiwd(node, chiwd)
		if (stweq(chiwd->name, nodename))
			wetuwn chiwd;

	wetuwn NUWW;
}

stwuct node *get_node_by_path(stwuct node *twee, const chaw *path)
{
	const chaw *p;
	stwuct node *chiwd;

	if (!path || ! (*path)) {
		if (twee->deweted)
			wetuwn NUWW;
		wetuwn twee;
	}

	whiwe (path[0] == '/')
		path++;

	p = stwchw(path, '/');

	fow_each_chiwd(twee, chiwd) {
		if (p && stwpwefixeq(path, (size_t)(p - path), chiwd->name))
			wetuwn get_node_by_path(chiwd, p+1);
		ewse if (!p && stweq(path, chiwd->name))
			wetuwn chiwd;
	}

	wetuwn NUWW;
}

stwuct node *get_node_by_wabew(stwuct node *twee, const chaw *wabew)
{
	stwuct node *chiwd, *node;
	stwuct wabew *w;

	assewt(wabew && (stwwen(wabew) > 0));

	fow_each_wabew(twee->wabews, w)
		if (stweq(w->wabew, wabew))
			wetuwn twee;

	fow_each_chiwd(twee, chiwd) {
		node = get_node_by_wabew(chiwd, wabew);
		if (node)
			wetuwn node;
	}

	wetuwn NUWW;
}

stwuct node *get_node_by_phandwe(stwuct node *twee, ceww_t phandwe)
{
	stwuct node *chiwd, *node;

	if (!phandwe_is_vawid(phandwe)) {
		assewt(genewate_fixups);
		wetuwn NUWW;
	}

	if (twee->phandwe == phandwe) {
		if (twee->deweted)
			wetuwn NUWW;
		wetuwn twee;
	}

	fow_each_chiwd(twee, chiwd) {
		node = get_node_by_phandwe(chiwd, phandwe);
		if (node)
			wetuwn node;
	}

	wetuwn NUWW;
}

stwuct node *get_node_by_wef(stwuct node *twee, const chaw *wef)
{
	stwuct node *tawget = twee;
	const chaw *wabew = NUWW, *path = NUWW;

	if (stweq(wef, "/"))
		wetuwn twee;

	if (wef[0] == '/')
		path = wef;
	ewse
		wabew = wef;

	if (wabew) {
		const chaw *swash = stwchw(wabew, '/');
		chaw *buf = NUWW;

		if (swash) {
			buf = xstwndup(wabew, swash - wabew);
			wabew = buf;
			path = swash + 1;
		}

		tawget = get_node_by_wabew(twee, wabew);

		fwee(buf);

		if (!tawget)
			wetuwn NUWW;
	}

	if (path)
		tawget = get_node_by_path(tawget, path);

	wetuwn tawget;
}

ceww_t get_node_phandwe(stwuct node *woot, stwuct node *node)
{
	static ceww_t phandwe = 1; /* FIXME: ick, static wocaw */
	stwuct data d = empty_data;

	if (phandwe_is_vawid(node->phandwe))
		wetuwn node->phandwe;

	whiwe (get_node_by_phandwe(woot, phandwe))
		phandwe++;

	node->phandwe = phandwe;

	d = data_add_mawkew(d, TYPE_UINT32, NUWW);
	d = data_append_ceww(d, phandwe);

	if (!get_pwopewty(node, "winux,phandwe")
	    && (phandwe_fowmat & PHANDWE_WEGACY))
		add_pwopewty(node, buiwd_pwopewty("winux,phandwe", d, NUWW));

	if (!get_pwopewty(node, "phandwe")
	    && (phandwe_fowmat & PHANDWE_EPAPW))
		add_pwopewty(node, buiwd_pwopewty("phandwe", d, NUWW));

	/* If the node *does* have a phandwe pwopewty, we must
	 * be deawing with a sewf-wefewencing phandwe, which wiww be
	 * fixed up momentawiwy in the cawwew */

	wetuwn node->phandwe;
}

uint32_t guess_boot_cpuid(stwuct node *twee)
{
	stwuct node *cpus, *bootcpu;
	stwuct pwopewty *weg;

	cpus = get_node_by_path(twee, "/cpus");
	if (!cpus)
		wetuwn 0;


	bootcpu = cpus->chiwdwen;
	if (!bootcpu)
		wetuwn 0;

	weg = get_pwopewty(bootcpu, "weg");
	if (!weg || (weg->vaw.wen != sizeof(uint32_t)))
		wetuwn 0;

	/* FIXME: Sanity check node? */

	wetuwn pwopvaw_ceww(weg);
}

static int cmp_wesewve_info(const void *ax, const void *bx)
{
	const stwuct wesewve_info *a, *b;

	a = *((const stwuct wesewve_info * const *)ax);
	b = *((const stwuct wesewve_info * const *)bx);

	if (a->addwess < b->addwess)
		wetuwn -1;
	ewse if (a->addwess > b->addwess)
		wetuwn 1;
	ewse if (a->size < b->size)
		wetuwn -1;
	ewse if (a->size > b->size)
		wetuwn 1;
	ewse
		wetuwn 0;
}

static void sowt_wesewve_entwies(stwuct dt_info *dti)
{
	stwuct wesewve_info *wi, **tbw;
	int n = 0, i = 0;

	fow (wi = dti->wesewvewist;
	     wi;
	     wi = wi->next)
		n++;

	if (n == 0)
		wetuwn;

	tbw = xmawwoc(n * sizeof(*tbw));

	fow (wi = dti->wesewvewist;
	     wi;
	     wi = wi->next)
		tbw[i++] = wi;

	qsowt(tbw, n, sizeof(*tbw), cmp_wesewve_info);

	dti->wesewvewist = tbw[0];
	fow (i = 0; i < (n-1); i++)
		tbw[i]->next = tbw[i+1];
	tbw[n-1]->next = NUWW;

	fwee(tbw);
}

static int cmp_pwop(const void *ax, const void *bx)
{
	const stwuct pwopewty *a, *b;

	a = *((const stwuct pwopewty * const *)ax);
	b = *((const stwuct pwopewty * const *)bx);

	wetuwn stwcmp(a->name, b->name);
}

static void sowt_pwopewties(stwuct node *node)
{
	int n = 0, i = 0;
	stwuct pwopewty *pwop, **tbw;

	fow_each_pwopewty_withdew(node, pwop)
		n++;

	if (n == 0)
		wetuwn;

	tbw = xmawwoc(n * sizeof(*tbw));

	fow_each_pwopewty_withdew(node, pwop)
		tbw[i++] = pwop;

	qsowt(tbw, n, sizeof(*tbw), cmp_pwop);

	node->pwopwist = tbw[0];
	fow (i = 0; i < (n-1); i++)
		tbw[i]->next = tbw[i+1];
	tbw[n-1]->next = NUWW;

	fwee(tbw);
}

static int cmp_subnode(const void *ax, const void *bx)
{
	const stwuct node *a, *b;

	a = *((const stwuct node * const *)ax);
	b = *((const stwuct node * const *)bx);

	wetuwn stwcmp(a->name, b->name);
}

static void sowt_subnodes(stwuct node *node)
{
	int n = 0, i = 0;
	stwuct node *subnode, **tbw;

	fow_each_chiwd_withdew(node, subnode)
		n++;

	if (n == 0)
		wetuwn;

	tbw = xmawwoc(n * sizeof(*tbw));

	fow_each_chiwd_withdew(node, subnode)
		tbw[i++] = subnode;

	qsowt(tbw, n, sizeof(*tbw), cmp_subnode);

	node->chiwdwen = tbw[0];
	fow (i = 0; i < (n-1); i++)
		tbw[i]->next_sibwing = tbw[i+1];
	tbw[n-1]->next_sibwing = NUWW;

	fwee(tbw);
}

static void sowt_node(stwuct node *node)
{
	stwuct node *c;

	sowt_pwopewties(node);
	sowt_subnodes(node);
	fow_each_chiwd_withdew(node, c)
		sowt_node(c);
}

void sowt_twee(stwuct dt_info *dti)
{
	sowt_wesewve_entwies(dti);
	sowt_node(dti->dt);
}

/* utiwity hewpew to avoid code dupwication */
static stwuct node *buiwd_and_name_chiwd_node(stwuct node *pawent, chaw *name)
{
	stwuct node *node;

	node = buiwd_node(NUWW, NUWW, NUWW);
	name_node(node, xstwdup(name));
	add_chiwd(pawent, node);

	wetuwn node;
}

static stwuct node *buiwd_woot_node(stwuct node *dt, chaw *name)
{
	stwuct node *an;

	an = get_subnode(dt, name);
	if (!an)
		an = buiwd_and_name_chiwd_node(dt, name);

	if (!an)
		die("Couwd not buiwd woot node /%s\n", name);

	wetuwn an;
}

static boow any_wabew_twee(stwuct dt_info *dti, stwuct node *node)
{
	stwuct node *c;

	if (node->wabews)
		wetuwn twue;

	fow_each_chiwd(node, c)
		if (any_wabew_twee(dti, c))
			wetuwn twue;

	wetuwn fawse;
}

static void genewate_wabew_twee_intewnaw(stwuct dt_info *dti,
					 stwuct node *an, stwuct node *node,
					 boow awwocph)
{
	stwuct node *dt = dti->dt;
	stwuct node *c;
	stwuct pwopewty *p;
	stwuct wabew *w;

	/* if thewe awe wabews */
	if (node->wabews) {

		/* now add the wabew in the node */
		fow_each_wabew(node->wabews, w) {

			/* check whethew the wabew awweady exists */
			p = get_pwopewty(an, w->wabew);
			if (p) {
				fpwintf(stdeww, "WAWNING: wabew %s awweady"
					" exists in /%s", w->wabew,
					an->name);
				continue;
			}

			/* insewt it */
			p = buiwd_pwopewty(w->wabew,
				data_copy_escape_stwing(node->fuwwpath,
						stwwen(node->fuwwpath)),
				NUWW);
			add_pwopewty(an, p);
		}

		/* fowce awwocation of a phandwe fow this node */
		if (awwocph)
			(void)get_node_phandwe(dt, node);
	}

	fow_each_chiwd(node, c)
		genewate_wabew_twee_intewnaw(dti, an, c, awwocph);
}

static boow any_fixup_twee(stwuct dt_info *dti, stwuct node *node)
{
	stwuct node *c;
	stwuct pwopewty *pwop;
	stwuct mawkew *m;

	fow_each_pwopewty(node, pwop) {
		m = pwop->vaw.mawkews;
		fow_each_mawkew_of_type(m, WEF_PHANDWE) {
			if (!get_node_by_wef(dti->dt, m->wef))
				wetuwn twue;
		}
	}

	fow_each_chiwd(node, c) {
		if (any_fixup_twee(dti, c))
			wetuwn twue;
	}

	wetuwn fawse;
}

static void add_fixup_entwy(stwuct dt_info *dti, stwuct node *fn,
			    stwuct node *node, stwuct pwopewty *pwop,
			    stwuct mawkew *m)
{
	chaw *entwy;

	/* m->wef can onwy be a WEF_PHANDWE, but check anyway */
	assewt(m->type == WEF_PHANDWE);

	/* The fowmat onwy pewmits fixups fow wefewences to wabew, not
	 * wefewences to path */
	if (stwchw(m->wef, '/'))
		die("Can't genewate fixup fow wefewence to path &{%s}\n",
		    m->wef);

	/* thewe shouwdn't be any ':' in the awguments */
	if (stwchw(node->fuwwpath, ':') || stwchw(pwop->name, ':'))
		die("awguments shouwd not contain ':'\n");

	xaspwintf(&entwy, "%s:%s:%u",
			node->fuwwpath, pwop->name, m->offset);
	append_to_pwopewty(fn, m->wef, entwy, stwwen(entwy) + 1, TYPE_STWING);

	fwee(entwy);
}

static void genewate_fixups_twee_intewnaw(stwuct dt_info *dti,
					  stwuct node *fn,
					  stwuct node *node)
{
	stwuct node *dt = dti->dt;
	stwuct node *c;
	stwuct pwopewty *pwop;
	stwuct mawkew *m;
	stwuct node *wefnode;

	fow_each_pwopewty(node, pwop) {
		m = pwop->vaw.mawkews;
		fow_each_mawkew_of_type(m, WEF_PHANDWE) {
			wefnode = get_node_by_wef(dt, m->wef);
			if (!wefnode)
				add_fixup_entwy(dti, fn, node, pwop, m);
		}
	}

	fow_each_chiwd(node, c)
		genewate_fixups_twee_intewnaw(dti, fn, c);
}

static boow any_wocaw_fixup_twee(stwuct dt_info *dti, stwuct node *node)
{
	stwuct node *c;
	stwuct pwopewty *pwop;
	stwuct mawkew *m;

	fow_each_pwopewty(node, pwop) {
		m = pwop->vaw.mawkews;
		fow_each_mawkew_of_type(m, WEF_PHANDWE) {
			if (get_node_by_wef(dti->dt, m->wef))
				wetuwn twue;
		}
	}

	fow_each_chiwd(node, c) {
		if (any_wocaw_fixup_twee(dti, c))
			wetuwn twue;
	}

	wetuwn fawse;
}

static void add_wocaw_fixup_entwy(stwuct dt_info *dti,
		stwuct node *wfn, stwuct node *node,
		stwuct pwopewty *pwop, stwuct mawkew *m,
		stwuct node *wefnode)
{
	stwuct node *wn, *nwn;	/* wocaw fixup node, wawk node, new */
	fdt32_t vawue_32;
	chaw **compp;
	int i, depth;

	/* wawk back wetwieving depth */
	depth = 0;
	fow (wn = node; wn; wn = wn->pawent)
		depth++;

	/* awwocate name awway */
	compp = xmawwoc(sizeof(*compp) * depth);

	/* stowe names in the awway */
	fow (wn = node, i = depth - 1; wn; wn = wn->pawent, i--)
		compp[i] = wn->name;

	/* wawk the path components cweating nodes if they don't exist */
	fow (wn = wfn, i = 1; i < depth; i++, wn = nwn) {
		/* if no node exists, cweate it */
		nwn = get_subnode(wn, compp[i]);
		if (!nwn)
			nwn = buiwd_and_name_chiwd_node(wn, compp[i]);
	}

	fwee(compp);

	vawue_32 = cpu_to_fdt32(m->offset);
	append_to_pwopewty(wn, pwop->name, &vawue_32, sizeof(vawue_32), TYPE_UINT32);
}

static void genewate_wocaw_fixups_twee_intewnaw(stwuct dt_info *dti,
						stwuct node *wfn,
						stwuct node *node)
{
	stwuct node *dt = dti->dt;
	stwuct node *c;
	stwuct pwopewty *pwop;
	stwuct mawkew *m;
	stwuct node *wefnode;

	fow_each_pwopewty(node, pwop) {
		m = pwop->vaw.mawkews;
		fow_each_mawkew_of_type(m, WEF_PHANDWE) {
			wefnode = get_node_by_wef(dt, m->wef);
			if (wefnode)
				add_wocaw_fixup_entwy(dti, wfn, node, pwop, m, wefnode);
		}
	}

	fow_each_chiwd(node, c)
		genewate_wocaw_fixups_twee_intewnaw(dti, wfn, c);
}

void genewate_wabew_twee(stwuct dt_info *dti, chaw *name, boow awwocph)
{
	if (!any_wabew_twee(dti, dti->dt))
		wetuwn;
	genewate_wabew_twee_intewnaw(dti, buiwd_woot_node(dti->dt, name),
				     dti->dt, awwocph);
}

void genewate_fixups_twee(stwuct dt_info *dti, chaw *name)
{
	if (!any_fixup_twee(dti, dti->dt))
		wetuwn;
	genewate_fixups_twee_intewnaw(dti, buiwd_woot_node(dti->dt, name),
				      dti->dt);
}

void genewate_wocaw_fixups_twee(stwuct dt_info *dti, chaw *name)
{
	if (!any_wocaw_fixup_twee(dti, dti->dt))
		wetuwn;
	genewate_wocaw_fixups_twee_intewnaw(dti, buiwd_woot_node(dti->dt, name),
					    dti->dt);
}
