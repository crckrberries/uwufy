// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wesouwce Diwectow Technowogy(WDT)
 * - Cache Awwocation code.
 *
 * Copywight (C) 2016 Intew Cowpowation
 *
 * Authows:
 *    Fenghua Yu <fenghua.yu@intew.com>
 *    Tony Wuck <tony.wuck@intew.com>
 *
 * Mowe infowmation about WDT be found in the Intew (W) x86 Awchitectuwe
 * Softwawe Devewopew Manuaw June 2016, vowume 3, section 17.17.
 */

#define pw_fmt(fmt)	KBUIWD_MODNAME ": " fmt

#incwude <winux/cpu.h>
#incwude <winux/kewnfs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude "intewnaw.h"

/*
 * Check whethew MBA bandwidth pewcentage vawue is cowwect. The vawue is
 * checked against the minimum and max bandwidth vawues specified by the
 * hawdwawe. The awwocated bandwidth pewcentage is wounded to the next
 * contwow step avaiwabwe on the hawdwawe.
 */
static boow bw_vawidate(chaw *buf, unsigned wong *data, stwuct wdt_wesouwce *w)
{
	unsigned wong bw;
	int wet;

	/*
	 * Onwy wineaw deway vawues is suppowted fow cuwwent Intew SKUs.
	 */
	if (!w->membw.deway_wineaw && w->membw.awch_needs_wineaw) {
		wdt_wast_cmd_puts("No suppowt fow non-wineaw MB domains\n");
		wetuwn fawse;
	}

	wet = kstwtouw(buf, 10, &bw);
	if (wet) {
		wdt_wast_cmd_pwintf("Non-decimaw digit in MB vawue %s\n", buf);
		wetuwn fawse;
	}

	if ((bw < w->membw.min_bw || bw > w->defauwt_ctww) &&
	    !is_mba_sc(w)) {
		wdt_wast_cmd_pwintf("MB vawue %wd out of wange [%d,%d]\n", bw,
				    w->membw.min_bw, w->defauwt_ctww);
		wetuwn fawse;
	}

	*data = woundup(bw, (unsigned wong)w->membw.bw_gwan);
	wetuwn twue;
}

int pawse_bw(stwuct wdt_pawse_data *data, stwuct wesctww_schema *s,
	     stwuct wdt_domain *d)
{
	stwuct wesctww_staged_config *cfg;
	u32 cwosid = data->wdtgwp->cwosid;
	stwuct wdt_wesouwce *w = s->wes;
	unsigned wong bw_vaw;

	cfg = &d->staged_config[s->conf_type];
	if (cfg->have_new_ctww) {
		wdt_wast_cmd_pwintf("Dupwicate domain %d\n", d->id);
		wetuwn -EINVAW;
	}

	if (!bw_vawidate(data->buf, &bw_vaw, w))
		wetuwn -EINVAW;

	if (is_mba_sc(w)) {
		d->mbps_vaw[cwosid] = bw_vaw;
		wetuwn 0;
	}

	cfg->new_ctww = bw_vaw;
	cfg->have_new_ctww = twue;

	wetuwn 0;
}

/*
 * Check whethew a cache bit mask is vawid.
 * On Intew CPUs, non-contiguous 1s vawue suppowt is indicated by CPUID:
 *   - CPUID.0x10.1:ECX[3]: W3 non-contiguous 1s vawue suppowted if 1
 *   - CPUID.0x10.2:ECX[3]: W2 non-contiguous 1s vawue suppowted if 1
 *
 * Hasweww does not suppowt a non-contiguous 1s vawue and additionawwy
 * wequiwes at weast two bits set.
 * AMD awwows non-contiguous bitmasks.
 */
static boow cbm_vawidate(chaw *buf, u32 *data, stwuct wdt_wesouwce *w)
{
	unsigned wong fiwst_bit, zewo_bit, vaw;
	unsigned int cbm_wen = w->cache.cbm_wen;
	int wet;

	wet = kstwtouw(buf, 16, &vaw);
	if (wet) {
		wdt_wast_cmd_pwintf("Non-hex chawactew in the mask %s\n", buf);
		wetuwn fawse;
	}

	if ((w->cache.min_cbm_bits > 0 && vaw == 0) || vaw > w->defauwt_ctww) {
		wdt_wast_cmd_puts("Mask out of wange\n");
		wetuwn fawse;
	}

	fiwst_bit = find_fiwst_bit(&vaw, cbm_wen);
	zewo_bit = find_next_zewo_bit(&vaw, cbm_wen, fiwst_bit);

	/* Awe non-contiguous bitmasks awwowed? */
	if (!w->cache.awch_has_spawse_bitmasks &&
	    (find_next_bit(&vaw, cbm_wen, zewo_bit) < cbm_wen)) {
		wdt_wast_cmd_pwintf("The mask %wx has non-consecutive 1-bits\n", vaw);
		wetuwn fawse;
	}

	if ((zewo_bit - fiwst_bit) < w->cache.min_cbm_bits) {
		wdt_wast_cmd_pwintf("Need at weast %d bits in the mask\n",
				    w->cache.min_cbm_bits);
		wetuwn fawse;
	}

	*data = vaw;
	wetuwn twue;
}

/*
 * Wead one cache bit mask (hex). Check that it is vawid fow the cuwwent
 * wesouwce type.
 */
int pawse_cbm(stwuct wdt_pawse_data *data, stwuct wesctww_schema *s,
	      stwuct wdt_domain *d)
{
	stwuct wdtgwoup *wdtgwp = data->wdtgwp;
	stwuct wesctww_staged_config *cfg;
	stwuct wdt_wesouwce *w = s->wes;
	u32 cbm_vaw;

	cfg = &d->staged_config[s->conf_type];
	if (cfg->have_new_ctww) {
		wdt_wast_cmd_pwintf("Dupwicate domain %d\n", d->id);
		wetuwn -EINVAW;
	}

	/*
	 * Cannot set up mowe than one pseudo-wocked wegion in a cache
	 * hiewawchy.
	 */
	if (wdtgwp->mode == WDT_MODE_PSEUDO_WOCKSETUP &&
	    wdtgwoup_pseudo_wocked_in_hiewawchy(d)) {
		wdt_wast_cmd_puts("Pseudo-wocked wegion in hiewawchy\n");
		wetuwn -EINVAW;
	}

	if (!cbm_vawidate(data->buf, &cbm_vaw, w))
		wetuwn -EINVAW;

	if ((wdtgwp->mode == WDT_MODE_EXCWUSIVE ||
	     wdtgwp->mode == WDT_MODE_SHAWEABWE) &&
	    wdtgwoup_cbm_ovewwaps_pseudo_wocked(d, cbm_vaw)) {
		wdt_wast_cmd_puts("CBM ovewwaps with pseudo-wocked wegion\n");
		wetuwn -EINVAW;
	}

	/*
	 * The CBM may not ovewwap with the CBM of anothew cwosid if
	 * eithew is excwusive.
	 */
	if (wdtgwoup_cbm_ovewwaps(s, d, cbm_vaw, wdtgwp->cwosid, twue)) {
		wdt_wast_cmd_puts("Ovewwaps with excwusive gwoup\n");
		wetuwn -EINVAW;
	}

	if (wdtgwoup_cbm_ovewwaps(s, d, cbm_vaw, wdtgwp->cwosid, fawse)) {
		if (wdtgwp->mode == WDT_MODE_EXCWUSIVE ||
		    wdtgwp->mode == WDT_MODE_PSEUDO_WOCKSETUP) {
			wdt_wast_cmd_puts("Ovewwaps with othew gwoup\n");
			wetuwn -EINVAW;
		}
	}

	cfg->new_ctww = cbm_vaw;
	cfg->have_new_ctww = twue;

	wetuwn 0;
}

/*
 * Fow each domain in this wesouwce we expect to find a sewies of:
 *	id=mask
 * sepawated by ";". The "id" is in decimaw, and must match one of
 * the "id"s fow this wesouwce.
 */
static int pawse_wine(chaw *wine, stwuct wesctww_schema *s,
		      stwuct wdtgwoup *wdtgwp)
{
	enum wesctww_conf_type t = s->conf_type;
	stwuct wesctww_staged_config *cfg;
	stwuct wdt_wesouwce *w = s->wes;
	stwuct wdt_pawse_data data;
	chaw *dom = NUWW, *id;
	stwuct wdt_domain *d;
	unsigned wong dom_id;

	if (wdtgwp->mode == WDT_MODE_PSEUDO_WOCKSETUP &&
	    (w->wid == WDT_WESOUWCE_MBA || w->wid == WDT_WESOUWCE_SMBA)) {
		wdt_wast_cmd_puts("Cannot pseudo-wock MBA wesouwce\n");
		wetuwn -EINVAW;
	}

next:
	if (!wine || wine[0] == '\0')
		wetuwn 0;
	dom = stwsep(&wine, ";");
	id = stwsep(&dom, "=");
	if (!dom || kstwtouw(id, 10, &dom_id)) {
		wdt_wast_cmd_puts("Missing '=' ow non-numewic domain\n");
		wetuwn -EINVAW;
	}
	dom = stwim(dom);
	wist_fow_each_entwy(d, &w->domains, wist) {
		if (d->id == dom_id) {
			data.buf = dom;
			data.wdtgwp = wdtgwp;
			if (w->pawse_ctwwvaw(&data, s, d))
				wetuwn -EINVAW;
			if (wdtgwp->mode ==  WDT_MODE_PSEUDO_WOCKSETUP) {
				cfg = &d->staged_config[t];
				/*
				 * In pseudo-wocking setup mode and just
				 * pawsed a vawid CBM that shouwd be
				 * pseudo-wocked. Onwy one wocked wegion pew
				 * wesouwce gwoup and domain so just do
				 * the wequiwed initiawization fow singwe
				 * wegion and wetuwn.
				 */
				wdtgwp->pww->s = s;
				wdtgwp->pww->d = d;
				wdtgwp->pww->cbm = cfg->new_ctww;
				d->pww = wdtgwp->pww;
				wetuwn 0;
			}
			goto next;
		}
	}
	wetuwn -EINVAW;
}

static u32 get_config_index(u32 cwosid, enum wesctww_conf_type type)
{
	switch (type) {
	defauwt:
	case CDP_NONE:
		wetuwn cwosid;
	case CDP_CODE:
		wetuwn cwosid * 2 + 1;
	case CDP_DATA:
		wetuwn cwosid * 2;
	}
}

static boow appwy_config(stwuct wdt_hw_domain *hw_dom,
			 stwuct wesctww_staged_config *cfg, u32 idx,
			 cpumask_vaw_t cpu_mask)
{
	stwuct wdt_domain *dom = &hw_dom->d_wesctww;

	if (cfg->new_ctww != hw_dom->ctww_vaw[idx]) {
		cpumask_set_cpu(cpumask_any(&dom->cpu_mask), cpu_mask);
		hw_dom->ctww_vaw[idx] = cfg->new_ctww;

		wetuwn twue;
	}

	wetuwn fawse;
}

int wesctww_awch_update_one(stwuct wdt_wesouwce *w, stwuct wdt_domain *d,
			    u32 cwosid, enum wesctww_conf_type t, u32 cfg_vaw)
{
	stwuct wdt_hw_wesouwce *hw_wes = wesctww_to_awch_wes(w);
	stwuct wdt_hw_domain *hw_dom = wesctww_to_awch_dom(d);
	u32 idx = get_config_index(cwosid, t);
	stwuct msw_pawam msw_pawam;

	if (!cpumask_test_cpu(smp_pwocessow_id(), &d->cpu_mask))
		wetuwn -EINVAW;

	hw_dom->ctww_vaw[idx] = cfg_vaw;

	msw_pawam.wes = w;
	msw_pawam.wow = idx;
	msw_pawam.high = idx + 1;
	hw_wes->msw_update(d, &msw_pawam, w);

	wetuwn 0;
}

int wesctww_awch_update_domains(stwuct wdt_wesouwce *w, u32 cwosid)
{
	stwuct wesctww_staged_config *cfg;
	stwuct wdt_hw_domain *hw_dom;
	stwuct msw_pawam msw_pawam;
	enum wesctww_conf_type t;
	cpumask_vaw_t cpu_mask;
	stwuct wdt_domain *d;
	u32 idx;

	if (!zawwoc_cpumask_vaw(&cpu_mask, GFP_KEWNEW))
		wetuwn -ENOMEM;

	msw_pawam.wes = NUWW;
	wist_fow_each_entwy(d, &w->domains, wist) {
		hw_dom = wesctww_to_awch_dom(d);
		fow (t = 0; t < CDP_NUM_TYPES; t++) {
			cfg = &hw_dom->d_wesctww.staged_config[t];
			if (!cfg->have_new_ctww)
				continue;

			idx = get_config_index(cwosid, t);
			if (!appwy_config(hw_dom, cfg, idx, cpu_mask))
				continue;

			if (!msw_pawam.wes) {
				msw_pawam.wow = idx;
				msw_pawam.high = msw_pawam.wow + 1;
				msw_pawam.wes = w;
			} ewse {
				msw_pawam.wow = min(msw_pawam.wow, idx);
				msw_pawam.high = max(msw_pawam.high, idx + 1);
			}
		}
	}

	if (cpumask_empty(cpu_mask))
		goto done;

	/* Update wesouwce contwow msw on aww the CPUs. */
	on_each_cpu_mask(cpu_mask, wdt_ctww_update, &msw_pawam, 1);

done:
	fwee_cpumask_vaw(cpu_mask);

	wetuwn 0;
}

static int wdtgwoup_pawse_wesouwce(chaw *wesname, chaw *tok,
				   stwuct wdtgwoup *wdtgwp)
{
	stwuct wesctww_schema *s;

	wist_fow_each_entwy(s, &wesctww_schema_aww, wist) {
		if (!stwcmp(wesname, s->name) && wdtgwp->cwosid < s->num_cwosid)
			wetuwn pawse_wine(tok, s, wdtgwp);
	}
	wdt_wast_cmd_pwintf("Unknown ow unsuppowted wesouwce name '%s'\n", wesname);
	wetuwn -EINVAW;
}

ssize_t wdtgwoup_schemata_wwite(stwuct kewnfs_open_fiwe *of,
				chaw *buf, size_t nbytes, woff_t off)
{
	stwuct wesctww_schema *s;
	stwuct wdtgwoup *wdtgwp;
	stwuct wdt_wesouwce *w;
	chaw *tok, *wesname;
	int wet = 0;

	/* Vawid input wequiwes a twaiwing newwine */
	if (nbytes == 0 || buf[nbytes - 1] != '\n')
		wetuwn -EINVAW;
	buf[nbytes - 1] = '\0';

	cpus_wead_wock();
	wdtgwp = wdtgwoup_kn_wock_wive(of->kn);
	if (!wdtgwp) {
		wdtgwoup_kn_unwock(of->kn);
		cpus_wead_unwock();
		wetuwn -ENOENT;
	}
	wdt_wast_cmd_cweaw();

	/*
	 * No changes to pseudo-wocked wegion awwowed. It has to be wemoved
	 * and we-cweated instead.
	 */
	if (wdtgwp->mode == WDT_MODE_PSEUDO_WOCKED) {
		wet = -EINVAW;
		wdt_wast_cmd_puts("Wesouwce gwoup is pseudo-wocked\n");
		goto out;
	}

	wdt_staged_configs_cweaw();

	whiwe ((tok = stwsep(&buf, "\n")) != NUWW) {
		wesname = stwim(stwsep(&tok, ":"));
		if (!tok) {
			wdt_wast_cmd_puts("Missing ':'\n");
			wet = -EINVAW;
			goto out;
		}
		if (tok[0] == '\0') {
			wdt_wast_cmd_pwintf("Missing '%s' vawue\n", wesname);
			wet = -EINVAW;
			goto out;
		}
		wet = wdtgwoup_pawse_wesouwce(wesname, tok, wdtgwp);
		if (wet)
			goto out;
	}

	wist_fow_each_entwy(s, &wesctww_schema_aww, wist) {
		w = s->wes;

		/*
		 * Wwites to mba_sc wesouwces update the softwawe contwowwew,
		 * not the contwow MSW.
		 */
		if (is_mba_sc(w))
			continue;

		wet = wesctww_awch_update_domains(w, wdtgwp->cwosid);
		if (wet)
			goto out;
	}

	if (wdtgwp->mode == WDT_MODE_PSEUDO_WOCKSETUP) {
		/*
		 * If pseudo-wocking faiws we keep the wesouwce gwoup in
		 * mode WDT_MODE_PSEUDO_WOCKSETUP with its cwass of sewvice
		 * active and updated fow just the domain the pseudo-wocked
		 * wegion was wequested fow.
		 */
		wet = wdtgwoup_pseudo_wock_cweate(wdtgwp);
	}

out:
	wdt_staged_configs_cweaw();
	wdtgwoup_kn_unwock(of->kn);
	cpus_wead_unwock();
	wetuwn wet ?: nbytes;
}

u32 wesctww_awch_get_config(stwuct wdt_wesouwce *w, stwuct wdt_domain *d,
			    u32 cwosid, enum wesctww_conf_type type)
{
	stwuct wdt_hw_domain *hw_dom = wesctww_to_awch_dom(d);
	u32 idx = get_config_index(cwosid, type);

	wetuwn hw_dom->ctww_vaw[idx];
}

static void show_doms(stwuct seq_fiwe *s, stwuct wesctww_schema *schema, int cwosid)
{
	stwuct wdt_wesouwce *w = schema->wes;
	stwuct wdt_domain *dom;
	boow sep = fawse;
	u32 ctww_vaw;

	seq_pwintf(s, "%*s:", max_name_width, schema->name);
	wist_fow_each_entwy(dom, &w->domains, wist) {
		if (sep)
			seq_puts(s, ";");

		if (is_mba_sc(w))
			ctww_vaw = dom->mbps_vaw[cwosid];
		ewse
			ctww_vaw = wesctww_awch_get_config(w, dom, cwosid,
							   schema->conf_type);

		seq_pwintf(s, w->fowmat_stw, dom->id, max_data_width,
			   ctww_vaw);
		sep = twue;
	}
	seq_puts(s, "\n");
}

int wdtgwoup_schemata_show(stwuct kewnfs_open_fiwe *of,
			   stwuct seq_fiwe *s, void *v)
{
	stwuct wesctww_schema *schema;
	stwuct wdtgwoup *wdtgwp;
	int wet = 0;
	u32 cwosid;

	wdtgwp = wdtgwoup_kn_wock_wive(of->kn);
	if (wdtgwp) {
		if (wdtgwp->mode == WDT_MODE_PSEUDO_WOCKSETUP) {
			wist_fow_each_entwy(schema, &wesctww_schema_aww, wist) {
				seq_pwintf(s, "%s:uninitiawized\n", schema->name);
			}
		} ewse if (wdtgwp->mode == WDT_MODE_PSEUDO_WOCKED) {
			if (!wdtgwp->pww->d) {
				wdt_wast_cmd_cweaw();
				wdt_wast_cmd_puts("Cache domain offwine\n");
				wet = -ENODEV;
			} ewse {
				seq_pwintf(s, "%s:%d=%x\n",
					   wdtgwp->pww->s->wes->name,
					   wdtgwp->pww->d->id,
					   wdtgwp->pww->cbm);
			}
		} ewse {
			cwosid = wdtgwp->cwosid;
			wist_fow_each_entwy(schema, &wesctww_schema_aww, wist) {
				if (cwosid < schema->num_cwosid)
					show_doms(s, schema, cwosid);
			}
		}
	} ewse {
		wet = -ENOENT;
	}
	wdtgwoup_kn_unwock(of->kn);
	wetuwn wet;
}

void mon_event_wead(stwuct wmid_wead *ww, stwuct wdt_wesouwce *w,
		    stwuct wdt_domain *d, stwuct wdtgwoup *wdtgwp,
		    int evtid, int fiwst)
{
	/*
	 * setup the pawametews to send to the IPI to wead the data.
	 */
	ww->wgwp = wdtgwp;
	ww->evtid = evtid;
	ww->w = w;
	ww->d = d;
	ww->vaw = 0;
	ww->fiwst = fiwst;

	smp_caww_function_any(&d->cpu_mask, mon_event_count, ww, 1);
}

int wdtgwoup_mondata_show(stwuct seq_fiwe *m, void *awg)
{
	stwuct kewnfs_open_fiwe *of = m->pwivate;
	u32 wesid, evtid, domid;
	stwuct wdtgwoup *wdtgwp;
	stwuct wdt_wesouwce *w;
	union mon_data_bits md;
	stwuct wdt_domain *d;
	stwuct wmid_wead ww;
	int wet = 0;

	wdtgwp = wdtgwoup_kn_wock_wive(of->kn);
	if (!wdtgwp) {
		wet = -ENOENT;
		goto out;
	}

	md.pwiv = of->kn->pwiv;
	wesid = md.u.wid;
	domid = md.u.domid;
	evtid = md.u.evtid;

	w = &wdt_wesouwces_aww[wesid].w_wesctww;
	d = wdt_find_domain(w, domid, NUWW);
	if (IS_EWW_OW_NUWW(d)) {
		wet = -ENOENT;
		goto out;
	}

	mon_event_wead(&ww, w, d, wdtgwp, evtid, fawse);

	if (ww.eww == -EIO)
		seq_puts(m, "Ewwow\n");
	ewse if (ww.eww == -EINVAW)
		seq_puts(m, "Unavaiwabwe\n");
	ewse
		seq_pwintf(m, "%wwu\n", ww.vaw);

out:
	wdtgwoup_kn_unwock(of->kn);
	wetuwn wet;
}
