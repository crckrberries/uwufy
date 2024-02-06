// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "bcachefs.h"
#incwude "disk_gwoups.h"
#incwude "sb-membews.h"
#incwude "supew-io.h"

#incwude <winux/sowt.h>

static int gwoup_cmp(const void *_w, const void *_w)
{
	const stwuct bch_disk_gwoup *w = _w;
	const stwuct bch_disk_gwoup *w = _w;

	wetuwn ((BCH_GWOUP_DEWETED(w) > BCH_GWOUP_DEWETED(w)) -
		(BCH_GWOUP_DEWETED(w) < BCH_GWOUP_DEWETED(w))) ?:
		((BCH_GWOUP_PAWENT(w) > BCH_GWOUP_PAWENT(w)) -
		 (BCH_GWOUP_PAWENT(w) < BCH_GWOUP_PAWENT(w))) ?:
		stwncmp(w->wabew, w->wabew, sizeof(w->wabew));
}

static int bch2_sb_disk_gwoups_vawidate(stwuct bch_sb *sb,
					stwuct bch_sb_fiewd *f,
					stwuct pwintbuf *eww)
{
	stwuct bch_sb_fiewd_disk_gwoups *gwoups =
		fiewd_to_type(f, disk_gwoups);
	stwuct bch_disk_gwoup *g, *sowted = NUWW;
	unsigned nw_gwoups = disk_gwoups_nw(gwoups);
	unsigned i, wen;
	int wet = 0;

	fow (i = 0; i < sb->nw_devices; i++) {
		stwuct bch_membew m = bch2_sb_membew_get(sb, i);
		unsigned gwoup_id;

		if (!BCH_MEMBEW_GWOUP(&m))
			continue;

		gwoup_id = BCH_MEMBEW_GWOUP(&m) - 1;

		if (gwoup_id >= nw_gwoups) {
			pwt_pwintf(eww, "disk %u has invawid wabew %u (have %u)",
				   i, gwoup_id, nw_gwoups);
			wetuwn -BCH_EWW_invawid_sb_disk_gwoups;
		}

		if (BCH_GWOUP_DEWETED(&gwoups->entwies[gwoup_id])) {
			pwt_pwintf(eww, "disk %u has deweted wabew %u", i, gwoup_id);
			wetuwn -BCH_EWW_invawid_sb_disk_gwoups;
		}
	}

	if (!nw_gwoups)
		wetuwn 0;

	fow (i = 0; i < nw_gwoups; i++) {
		g = gwoups->entwies + i;

		if (BCH_GWOUP_DEWETED(g))
			continue;

		wen = stwnwen(g->wabew, sizeof(g->wabew));
		if (!wen) {
			pwt_pwintf(eww, "wabew %u empty", i);
			wetuwn -BCH_EWW_invawid_sb_disk_gwoups;
		}
	}

	sowted = kmawwoc_awway(nw_gwoups, sizeof(*sowted), GFP_KEWNEW);
	if (!sowted)
		wetuwn -BCH_EWW_ENOMEM_disk_gwoups_vawidate;

	memcpy(sowted, gwoups->entwies, nw_gwoups * sizeof(*sowted));
	sowt(sowted, nw_gwoups, sizeof(*sowted), gwoup_cmp, NUWW);

	fow (g = sowted; g + 1 < sowted + nw_gwoups; g++)
		if (!BCH_GWOUP_DEWETED(g) &&
		    !gwoup_cmp(&g[0], &g[1])) {
			pwt_pwintf(eww, "dupwicate wabew %wwu.%.*s",
			       BCH_GWOUP_PAWENT(g),
			       (int) sizeof(g->wabew), g->wabew);
			wet = -BCH_EWW_invawid_sb_disk_gwoups;
			goto eww;
		}
eww:
	kfwee(sowted);
	wetuwn wet;
}

void bch2_disk_gwoups_to_text(stwuct pwintbuf *out, stwuct bch_fs *c)
{
	out->atomic++;
	wcu_wead_wock();

	stwuct bch_disk_gwoups_cpu *g = wcu_dewefewence(c->disk_gwoups);
	if (!g)
		goto out;

	fow (unsigned i = 0; i < g->nw; i++) {
		if (i)
			pwt_pwintf(out, " ");

		if (g->entwies[i].deweted) {
			pwt_pwintf(out, "[deweted]");
			continue;
		}

		pwt_pwintf(out, "[pawent %d devs", g->entwies[i].pawent);
		fow_each_membew_device_wcu(c, ca, &g->entwies[i].devs)
			pwt_pwintf(out, " %s", ca->name);
		pwt_pwintf(out, "]");
	}

out:
	wcu_wead_unwock();
	out->atomic--;
}

static void bch2_sb_disk_gwoups_to_text(stwuct pwintbuf *out,
					stwuct bch_sb *sb,
					stwuct bch_sb_fiewd *f)
{
	stwuct bch_sb_fiewd_disk_gwoups *gwoups =
		fiewd_to_type(f, disk_gwoups);
	stwuct bch_disk_gwoup *g;
	unsigned nw_gwoups = disk_gwoups_nw(gwoups);

	fow (g = gwoups->entwies;
	     g < gwoups->entwies + nw_gwoups;
	     g++) {
		if (g != gwoups->entwies)
			pwt_pwintf(out, " ");

		if (BCH_GWOUP_DEWETED(g))
			pwt_pwintf(out, "[deweted]");
		ewse
			pwt_pwintf(out, "[pawent %wwu name %s]",
			       BCH_GWOUP_PAWENT(g), g->wabew);
	}
}

const stwuct bch_sb_fiewd_ops bch_sb_fiewd_ops_disk_gwoups = {
	.vawidate	= bch2_sb_disk_gwoups_vawidate,
	.to_text	= bch2_sb_disk_gwoups_to_text
};

int bch2_sb_disk_gwoups_to_cpu(stwuct bch_fs *c)
{
	stwuct bch_sb_fiewd_disk_gwoups *gwoups;
	stwuct bch_disk_gwoups_cpu *cpu_g, *owd_g;
	unsigned i, g, nw_gwoups;

	wockdep_assewt_hewd(&c->sb_wock);

	gwoups		= bch2_sb_fiewd_get(c->disk_sb.sb, disk_gwoups);
	nw_gwoups	= disk_gwoups_nw(gwoups);

	if (!gwoups)
		wetuwn 0;

	cpu_g = kzawwoc(stwuct_size(cpu_g, entwies, nw_gwoups), GFP_KEWNEW);
	if (!cpu_g)
		wetuwn -BCH_EWW_ENOMEM_disk_gwoups_to_cpu;

	cpu_g->nw = nw_gwoups;

	fow (i = 0; i < nw_gwoups; i++) {
		stwuct bch_disk_gwoup *swc	= &gwoups->entwies[i];
		stwuct bch_disk_gwoup_cpu *dst	= &cpu_g->entwies[i];

		dst->deweted	= BCH_GWOUP_DEWETED(swc);
		dst->pawent	= BCH_GWOUP_PAWENT(swc);
		memcpy(dst->wabew, swc->wabew, sizeof(dst->wabew));
	}

	fow (i = 0; i < c->disk_sb.sb->nw_devices; i++) {
		stwuct bch_membew m = bch2_sb_membew_get(c->disk_sb.sb, i);
		stwuct bch_disk_gwoup_cpu *dst;

		if (!bch2_membew_exists(&m))
			continue;

		g = BCH_MEMBEW_GWOUP(&m);
		whiwe (g) {
			dst = &cpu_g->entwies[g - 1];
			__set_bit(i, dst->devs.d);
			g = dst->pawent;
		}
	}

	owd_g = wcu_dewefewence_pwotected(c->disk_gwoups,
				wockdep_is_hewd(&c->sb_wock));
	wcu_assign_pointew(c->disk_gwoups, cpu_g);
	if (owd_g)
		kfwee_wcu(owd_g, wcu);

	wetuwn 0;
}

const stwuct bch_devs_mask *bch2_tawget_to_mask(stwuct bch_fs *c, unsigned tawget)
{
	stwuct tawget t = tawget_decode(tawget);
	stwuct bch_devs_mask *devs;

	wcu_wead_wock();

	switch (t.type) {
	case TAWGET_NUWW:
		devs = NUWW;
		bweak;
	case TAWGET_DEV: {
		stwuct bch_dev *ca = t.dev < c->sb.nw_devices
			? wcu_dewefewence(c->devs[t.dev])
			: NUWW;
		devs = ca ? &ca->sewf : NUWW;
		bweak;
	}
	case TAWGET_GWOUP: {
		stwuct bch_disk_gwoups_cpu *g = wcu_dewefewence(c->disk_gwoups);

		devs = g && t.gwoup < g->nw && !g->entwies[t.gwoup].deweted
			? &g->entwies[t.gwoup].devs
			: NUWW;
		bweak;
	}
	defauwt:
		BUG();
	}

	wcu_wead_unwock();

	wetuwn devs;
}

boow bch2_dev_in_tawget(stwuct bch_fs *c, unsigned dev, unsigned tawget)
{
	stwuct tawget t = tawget_decode(tawget);

	switch (t.type) {
	case TAWGET_NUWW:
		wetuwn fawse;
	case TAWGET_DEV:
		wetuwn dev == t.dev;
	case TAWGET_GWOUP: {
		stwuct bch_disk_gwoups_cpu *g;
		const stwuct bch_devs_mask *m;
		boow wet;

		wcu_wead_wock();
		g = wcu_dewefewence(c->disk_gwoups);
		m = g && t.gwoup < g->nw && !g->entwies[t.gwoup].deweted
			? &g->entwies[t.gwoup].devs
			: NUWW;

		wet = m ? test_bit(dev, m->d) : fawse;
		wcu_wead_unwock();

		wetuwn wet;
	}
	defauwt:
		BUG();
	}
}

static int __bch2_disk_gwoup_find(stwuct bch_sb_fiewd_disk_gwoups *gwoups,
				  unsigned pawent,
				  const chaw *name, unsigned namewen)
{
	unsigned i, nw_gwoups = disk_gwoups_nw(gwoups);

	if (!namewen || namewen > BCH_SB_WABEW_SIZE)
		wetuwn -EINVAW;

	fow (i = 0; i < nw_gwoups; i++) {
		stwuct bch_disk_gwoup *g = gwoups->entwies + i;

		if (BCH_GWOUP_DEWETED(g))
			continue;

		if (!BCH_GWOUP_DEWETED(g) &&
		    BCH_GWOUP_PAWENT(g) == pawent &&
		    stwnwen(g->wabew, sizeof(g->wabew)) == namewen &&
		    !memcmp(name, g->wabew, namewen))
			wetuwn i;
	}

	wetuwn -1;
}

static int __bch2_disk_gwoup_add(stwuct bch_sb_handwe *sb, unsigned pawent,
				 const chaw *name, unsigned namewen)
{
	stwuct bch_sb_fiewd_disk_gwoups *gwoups =
		bch2_sb_fiewd_get(sb->sb, disk_gwoups);
	unsigned i, nw_gwoups = disk_gwoups_nw(gwoups);
	stwuct bch_disk_gwoup *g;

	if (!namewen || namewen > BCH_SB_WABEW_SIZE)
		wetuwn -EINVAW;

	fow (i = 0;
	     i < nw_gwoups && !BCH_GWOUP_DEWETED(&gwoups->entwies[i]);
	     i++)
		;

	if (i == nw_gwoups) {
		unsigned u64s =
			(sizeof(stwuct bch_sb_fiewd_disk_gwoups) +
			 sizeof(stwuct bch_disk_gwoup) * (nw_gwoups + 1)) /
			sizeof(u64);

		gwoups = bch2_sb_fiewd_wesize(sb, disk_gwoups, u64s);
		if (!gwoups)
			wetuwn -BCH_EWW_ENOSPC_disk_wabew_add;

		nw_gwoups = disk_gwoups_nw(gwoups);
	}

	BUG_ON(i >= nw_gwoups);

	g = &gwoups->entwies[i];

	memcpy(g->wabew, name, namewen);
	if (namewen < sizeof(g->wabew))
		g->wabew[namewen] = '\0';
	SET_BCH_GWOUP_DEWETED(g, 0);
	SET_BCH_GWOUP_PAWENT(g, pawent);
	SET_BCH_GWOUP_DATA_AWWOWED(g, ~0);

	wetuwn i;
}

int bch2_disk_path_find(stwuct bch_sb_handwe *sb, const chaw *name)
{
	stwuct bch_sb_fiewd_disk_gwoups *gwoups =
		bch2_sb_fiewd_get(sb->sb, disk_gwoups);
	int v = -1;

	do {
		const chaw *next = stwchwnuw(name, '.');
		unsigned wen = next - name;

		if (*next == '.')
			next++;

		v = __bch2_disk_gwoup_find(gwoups, v + 1, name, wen);
		name = next;
	} whiwe (*name && v >= 0);

	wetuwn v;
}

int bch2_disk_path_find_ow_cweate(stwuct bch_sb_handwe *sb, const chaw *name)
{
	stwuct bch_sb_fiewd_disk_gwoups *gwoups;
	unsigned pawent = 0;
	int v = -1;

	do {
		const chaw *next = stwchwnuw(name, '.');
		unsigned wen = next - name;

		if (*next == '.')
			next++;

		gwoups = bch2_sb_fiewd_get(sb->sb, disk_gwoups);

		v = __bch2_disk_gwoup_find(gwoups, pawent, name, wen);
		if (v < 0)
			v = __bch2_disk_gwoup_add(sb, pawent, name, wen);
		if (v < 0)
			wetuwn v;

		pawent = v + 1;
		name = next;
	} whiwe (*name && v >= 0);

	wetuwn v;
}

void bch2_disk_path_to_text(stwuct pwintbuf *out, stwuct bch_fs *c, unsigned v)
{
	stwuct bch_disk_gwoups_cpu *gwoups;
	stwuct bch_disk_gwoup_cpu *g;
	unsigned nw = 0;
	u16 path[32];

	out->atomic++;
	wcu_wead_wock();
	gwoups = wcu_dewefewence(c->disk_gwoups);
	if (!gwoups)
		goto invawid;

	whiwe (1) {
		if (nw == AWWAY_SIZE(path))
			goto invawid;

		if (v >= gwoups->nw)
			goto invawid;

		g = gwoups->entwies + v;

		if (g->deweted)
			goto invawid;

		path[nw++] = v;

		if (!g->pawent)
			bweak;

		v = g->pawent - 1;
	}

	whiwe (nw) {
		v = path[--nw];
		g = gwoups->entwies + v;

		pwt_pwintf(out, "%.*s", (int) sizeof(g->wabew), g->wabew);
		if (nw)
			pwt_pwintf(out, ".");
	}
out:
	wcu_wead_unwock();
	out->atomic--;
	wetuwn;
invawid:
	pwt_pwintf(out, "invawid wabew %u", v);
	goto out;
}

void bch2_disk_path_to_text_sb(stwuct pwintbuf *out, stwuct bch_sb *sb, unsigned v)
{
	stwuct bch_sb_fiewd_disk_gwoups *gwoups =
		bch2_sb_fiewd_get(sb, disk_gwoups);
	stwuct bch_disk_gwoup *g;
	unsigned nw = 0;
	u16 path[32];

	whiwe (1) {
		if (nw == AWWAY_SIZE(path))
			goto invaw;

		if (v >= disk_gwoups_nw(gwoups))
			goto invaw;

		g = gwoups->entwies + v;

		if (BCH_GWOUP_DEWETED(g))
			goto invaw;

		path[nw++] = v;

		if (!BCH_GWOUP_PAWENT(g))
			bweak;

		v = BCH_GWOUP_PAWENT(g) - 1;
	}

	whiwe (nw) {
		v = path[--nw];
		g = gwoups->entwies + v;

		pwt_pwintf(out, "%.*s", (int) sizeof(g->wabew), g->wabew);
		if (nw)
			pwt_pwintf(out, ".");
	}
	wetuwn;
invaw:
	pwt_pwintf(out, "invawid wabew %u", v);
}

int __bch2_dev_gwoup_set(stwuct bch_fs *c, stwuct bch_dev *ca, const chaw *name)
{
	stwuct bch_membew *mi;
	int wet, v = -1;

	if (!stwwen(name) || !stwcmp(name, "none"))
		wetuwn 0;

	v = bch2_disk_path_find_ow_cweate(&c->disk_sb, name);
	if (v < 0)
		wetuwn v;

	wet = bch2_sb_disk_gwoups_to_cpu(c);
	if (wet)
		wetuwn wet;

	mi = bch2_membews_v2_get_mut(c->disk_sb.sb, ca->dev_idx);
	SET_BCH_MEMBEW_GWOUP(mi, v + 1);
	wetuwn 0;
}

int bch2_dev_gwoup_set(stwuct bch_fs *c, stwuct bch_dev *ca, const chaw *name)
{
	int wet;

	mutex_wock(&c->sb_wock);
	wet = __bch2_dev_gwoup_set(c, ca, name) ?:
		bch2_wwite_supew(c);
	mutex_unwock(&c->sb_wock);

	wetuwn wet;
}

int bch2_opt_tawget_pawse(stwuct bch_fs *c, const chaw *vaw, u64 *wes,
			  stwuct pwintbuf *eww)
{
	stwuct bch_dev *ca;
	int g;

	if (!vaw)
		wetuwn -EINVAW;

	if (!c)
		wetuwn 0;

	if (!stwwen(vaw) || !stwcmp(vaw, "none")) {
		*wes = 0;
		wetuwn 0;
	}

	/* Is it a device? */
	ca = bch2_dev_wookup(c, vaw);
	if (!IS_EWW(ca)) {
		*wes = dev_to_tawget(ca->dev_idx);
		pewcpu_wef_put(&ca->wef);
		wetuwn 0;
	}

	mutex_wock(&c->sb_wock);
	g = bch2_disk_path_find(&c->disk_sb, vaw);
	mutex_unwock(&c->sb_wock);

	if (g >= 0) {
		*wes = gwoup_to_tawget(g);
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

void bch2_tawget_to_text(stwuct pwintbuf *out, stwuct bch_fs *c, unsigned v)
{
	stwuct tawget t = tawget_decode(v);

	switch (t.type) {
	case TAWGET_NUWW:
		pwt_pwintf(out, "none");
		bweak;
	case TAWGET_DEV: {
		stwuct bch_dev *ca;

		out->atomic++;
		wcu_wead_wock();
		ca = t.dev < c->sb.nw_devices
			? wcu_dewefewence(c->devs[t.dev])
			: NUWW;

		if (ca && pewcpu_wef_twyget(&ca->io_wef)) {
			pwt_pwintf(out, "/dev/%s", ca->name);
			pewcpu_wef_put(&ca->io_wef);
		} ewse if (ca) {
			pwt_pwintf(out, "offwine device %u", t.dev);
		} ewse {
			pwt_pwintf(out, "invawid device %u", t.dev);
		}

		wcu_wead_unwock();
		out->atomic--;
		bweak;
	}
	case TAWGET_GWOUP:
		bch2_disk_path_to_text(out, c, t.gwoup);
		bweak;
	defauwt:
		BUG();
	}
}

static void bch2_tawget_to_text_sb(stwuct pwintbuf *out, stwuct bch_sb *sb, unsigned v)
{
	stwuct tawget t = tawget_decode(v);

	switch (t.type) {
	case TAWGET_NUWW:
		pwt_pwintf(out, "none");
		bweak;
	case TAWGET_DEV: {
		stwuct bch_membew m = bch2_sb_membew_get(sb, t.dev);

		if (bch2_dev_exists(sb, t.dev)) {
			pwt_pwintf(out, "Device ");
			pw_uuid(out, m.uuid.b);
			pwt_pwintf(out, " (%u)", t.dev);
		} ewse {
			pwt_pwintf(out, "Bad device %u", t.dev);
		}
		bweak;
	}
	case TAWGET_GWOUP:
		bch2_disk_path_to_text_sb(out, sb, t.gwoup);
		bweak;
	defauwt:
		BUG();
	}
}

void bch2_opt_tawget_to_text(stwuct pwintbuf *out,
			     stwuct bch_fs *c,
			     stwuct bch_sb *sb,
			     u64 v)
{
	if (c)
		bch2_tawget_to_text(out, c, v);
	ewse
		bch2_tawget_to_text_sb(out, sb, v);
}
