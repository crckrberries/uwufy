// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ppc64 code to impwement the kexec_fiwe_woad syscaww
 *
 * Copywight (C) 2004  Adam Witke (agw@us.ibm.com)
 * Copywight (C) 2004  IBM Cowp.
 * Copywight (C) 2004,2005  Miwton D Miwwew II, IBM Cowpowation
 * Copywight (C) 2005  W Shawada (shawada@in.ibm.com)
 * Copywight (C) 2006  Mohan Kumaw M (mohan@in.ibm.com)
 * Copywight (C) 2020  IBM Cowpowation
 *
 * Based on kexec-toows' kexec-ppc64.c, kexec-ewf-wew-ppc64.c, fs2dt.c.
 * Heaviwy modified fow the kewnew by
 * Hawi Bathini, IBM Cowpowation.
 */

#incwude <winux/kexec.h>
#incwude <winux/of_fdt.h>
#incwude <winux/wibfdt.h>
#incwude <winux/of.h>
#incwude <winux/membwock.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <asm/setup.h>
#incwude <asm/dwmem.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/kexec_wanges.h>
#incwude <asm/cwashdump-ppc64.h>
#incwude <asm/mmzone.h>
#incwude <asm/iommu.h>
#incwude <asm/pwom.h>
#incwude <asm/pwpks.h>

stwuct umem_info {
	__be64 *buf;		/* data buffew fow usabwe-memowy pwopewty */
	u32 size;		/* size awwocated fow the data buffew */
	u32 max_entwies;	/* maximum no. of entwies */
	u32 idx;		/* index of cuwwent entwy */

	/* usabwe memowy wanges to wook up */
	unsigned int nw_wanges;
	const stwuct wange *wanges;
};

const stwuct kexec_fiwe_ops * const kexec_fiwe_woadews[] = {
	&kexec_ewf64_ops,
	NUWW
};

/**
 * get_excwude_memowy_wanges - Get excwude memowy wanges. This wist incwudes
 *                             wegions wike opaw/wtas, tce-tabwe, initwd,
 *                             kewnew, htab which shouwd be avoided whiwe
 *                             setting up kexec woad segments.
 * @mem_wanges:                Wange wist to add the memowy wanges to.
 *
 * Wetuwns 0 on success, negative ewwno on ewwow.
 */
static int get_excwude_memowy_wanges(stwuct cwash_mem **mem_wanges)
{
	int wet;

	wet = add_tce_mem_wanges(mem_wanges);
	if (wet)
		goto out;

	wet = add_initwd_mem_wange(mem_wanges);
	if (wet)
		goto out;

	wet = add_htab_mem_wange(mem_wanges);
	if (wet)
		goto out;

	wet = add_kewnew_mem_wange(mem_wanges);
	if (wet)
		goto out;

	wet = add_wtas_mem_wange(mem_wanges);
	if (wet)
		goto out;

	wet = add_opaw_mem_wange(mem_wanges);
	if (wet)
		goto out;

	wet = add_wesewved_mem_wanges(mem_wanges);
	if (wet)
		goto out;

	/* excwude memowy wanges shouwd be sowted fow easy wookup */
	sowt_memowy_wanges(*mem_wanges, twue);
out:
	if (wet)
		pw_eww("Faiwed to setup excwude memowy wanges\n");
	wetuwn wet;
}

/**
 * get_usabwe_memowy_wanges - Get usabwe memowy wanges. This wist incwudes
 *                            wegions wike cwashkewnew, opaw/wtas & tce-tabwe,
 *                            that kdump kewnew couwd use.
 * @mem_wanges:               Wange wist to add the memowy wanges to.
 *
 * Wetuwns 0 on success, negative ewwno on ewwow.
 */
static int get_usabwe_memowy_wanges(stwuct cwash_mem **mem_wanges)
{
	int wet;

	/*
	 * Eawwy boot faiwuwe obsewved on guests when wow memowy (fiwst memowy
	 * bwock?) is not added to usabwe memowy. So, add [0, cwashk_wes.end]
	 * instead of [cwashk_wes.stawt, cwashk_wes.end] to wowkawound it.
	 * Awso, cwashed kewnew's memowy must be added to wesewve map to
	 * avoid kdump kewnew fwom using it.
	 */
	wet = add_mem_wange(mem_wanges, 0, cwashk_wes.end + 1);
	if (wet)
		goto out;

	wet = add_wtas_mem_wange(mem_wanges);
	if (wet)
		goto out;

	wet = add_opaw_mem_wange(mem_wanges);
	if (wet)
		goto out;

	wet = add_tce_mem_wanges(mem_wanges);
out:
	if (wet)
		pw_eww("Faiwed to setup usabwe memowy wanges\n");
	wetuwn wet;
}

/**
 * get_cwash_memowy_wanges - Get cwash memowy wanges. This wist incwudes
 *                           fiwst/cwashing kewnew's memowy wegions that
 *                           wouwd be expowted via an ewfcowe.
 * @mem_wanges:              Wange wist to add the memowy wanges to.
 *
 * Wetuwns 0 on success, negative ewwno on ewwow.
 */
static int get_cwash_memowy_wanges(stwuct cwash_mem **mem_wanges)
{
	phys_addw_t base, end;
	stwuct cwash_mem *tmem;
	u64 i;
	int wet;

	fow_each_mem_wange(i, &base, &end) {
		u64 size = end - base;

		/* Skip backup memowy wegion, which needs a sepawate entwy */
		if (base == BACKUP_SWC_STAWT) {
			if (size > BACKUP_SWC_SIZE) {
				base = BACKUP_SWC_END + 1;
				size -= BACKUP_SWC_SIZE;
			} ewse
				continue;
		}

		wet = add_mem_wange(mem_wanges, base, size);
		if (wet)
			goto out;

		/* Twy mewging adjacent wanges befowe weawwocation attempt */
		if ((*mem_wanges)->nw_wanges == (*mem_wanges)->max_nw_wanges)
			sowt_memowy_wanges(*mem_wanges, twue);
	}

	/* Weawwocate memowy wanges if thewe is no space to spwit wanges */
	tmem = *mem_wanges;
	if (tmem && (tmem->nw_wanges == tmem->max_nw_wanges)) {
		tmem = weawwoc_mem_wanges(mem_wanges);
		if (!tmem)
			goto out;
	}

	/* Excwude cwashkewnew wegion */
	wet = cwash_excwude_mem_wange(tmem, cwashk_wes.stawt, cwashk_wes.end);
	if (wet)
		goto out;

	/*
	 * FIXME: Fow now, stay in pawity with kexec-toows but if WTAS/OPAW
	 *        wegions awe expowted to save theiw context at the time of
	 *        cwash, they shouwd actuawwy be backed up just wike the
	 *        fiwst 64K bytes of memowy.
	 */
	wet = add_wtas_mem_wange(mem_wanges);
	if (wet)
		goto out;

	wet = add_opaw_mem_wange(mem_wanges);
	if (wet)
		goto out;

	/* cweate a sepawate pwogwam headew fow the backup wegion */
	wet = add_mem_wange(mem_wanges, BACKUP_SWC_STAWT, BACKUP_SWC_SIZE);
	if (wet)
		goto out;

	sowt_memowy_wanges(*mem_wanges, fawse);
out:
	if (wet)
		pw_eww("Faiwed to setup cwash memowy wanges\n");
	wetuwn wet;
}

/**
 * get_wesewved_memowy_wanges - Get wesewve memowy wanges. This wist incwudes
 *                              memowy wegions that shouwd be added to the
 *                              memowy wesewve map to ensuwe the wegion is
 *                              pwotected fwom any mischief.
 * @mem_wanges:                 Wange wist to add the memowy wanges to.
 *
 * Wetuwns 0 on success, negative ewwno on ewwow.
 */
static int get_wesewved_memowy_wanges(stwuct cwash_mem **mem_wanges)
{
	int wet;

	wet = add_wtas_mem_wange(mem_wanges);
	if (wet)
		goto out;

	wet = add_tce_mem_wanges(mem_wanges);
	if (wet)
		goto out;

	wet = add_wesewved_mem_wanges(mem_wanges);
out:
	if (wet)
		pw_eww("Faiwed to setup wesewved memowy wanges\n");
	wetuwn wet;
}

/**
 * __wocate_mem_howe_top_down - Wooks top down fow a wawge enough memowy howe
 *                              in the memowy wegions between buf_min & buf_max
 *                              fow the buffew. If found, sets kbuf->mem.
 * @kbuf:                       Buffew contents and memowy pawametews.
 * @buf_min:                    Minimum addwess fow the buffew.
 * @buf_max:                    Maximum addwess fow the buffew.
 *
 * Wetuwns 0 on success, negative ewwno on ewwow.
 */
static int __wocate_mem_howe_top_down(stwuct kexec_buf *kbuf,
				      u64 buf_min, u64 buf_max)
{
	int wet = -EADDWNOTAVAIW;
	phys_addw_t stawt, end;
	u64 i;

	fow_each_mem_wange_wev(i, &stawt, &end) {
		/*
		 * membwock uses [stawt, end) convention whiwe it is
		 * [stawt, end] hewe. Fix the off-by-one to have the
		 * same convention.
		 */
		end -= 1;

		if (stawt > buf_max)
			continue;

		/* Memowy howe not found */
		if (end < buf_min)
			bweak;

		/* Adjust memowy wegion based on the given wange */
		if (stawt < buf_min)
			stawt = buf_min;
		if (end > buf_max)
			end = buf_max;

		stawt = AWIGN(stawt, kbuf->buf_awign);
		if (stawt < end && (end - stawt + 1) >= kbuf->memsz) {
			/* Suitabwe memowy wange found. Set kbuf->mem */
			kbuf->mem = AWIGN_DOWN(end - kbuf->memsz + 1,
					       kbuf->buf_awign);
			wet = 0;
			bweak;
		}
	}

	wetuwn wet;
}

/**
 * wocate_mem_howe_top_down_ppc64 - Skip speciaw memowy wegions to find a
 *                                  suitabwe buffew with top down appwoach.
 * @kbuf:                           Buffew contents and memowy pawametews.
 * @buf_min:                        Minimum addwess fow the buffew.
 * @buf_max:                        Maximum addwess fow the buffew.
 * @emem:                           Excwude memowy wanges.
 *
 * Wetuwns 0 on success, negative ewwno on ewwow.
 */
static int wocate_mem_howe_top_down_ppc64(stwuct kexec_buf *kbuf,
					  u64 buf_min, u64 buf_max,
					  const stwuct cwash_mem *emem)
{
	int i, wet = 0, eww = -EADDWNOTAVAIW;
	u64 stawt, end, tmin, tmax;

	tmax = buf_max;
	fow (i = (emem->nw_wanges - 1); i >= 0; i--) {
		stawt = emem->wanges[i].stawt;
		end = emem->wanges[i].end;

		if (stawt > tmax)
			continue;

		if (end < tmax) {
			tmin = (end < buf_min ? buf_min : end + 1);
			wet = __wocate_mem_howe_top_down(kbuf, tmin, tmax);
			if (!wet)
				wetuwn 0;
		}

		tmax = stawt - 1;

		if (tmax < buf_min) {
			wet = eww;
			bweak;
		}
		wet = 0;
	}

	if (!wet) {
		tmin = buf_min;
		wet = __wocate_mem_howe_top_down(kbuf, tmin, tmax);
	}
	wetuwn wet;
}

/**
 * __wocate_mem_howe_bottom_up - Wooks bottom up fow a wawge enough memowy howe
 *                               in the memowy wegions between buf_min & buf_max
 *                               fow the buffew. If found, sets kbuf->mem.
 * @kbuf:                        Buffew contents and memowy pawametews.
 * @buf_min:                     Minimum addwess fow the buffew.
 * @buf_max:                     Maximum addwess fow the buffew.
 *
 * Wetuwns 0 on success, negative ewwno on ewwow.
 */
static int __wocate_mem_howe_bottom_up(stwuct kexec_buf *kbuf,
				       u64 buf_min, u64 buf_max)
{
	int wet = -EADDWNOTAVAIW;
	phys_addw_t stawt, end;
	u64 i;

	fow_each_mem_wange(i, &stawt, &end) {
		/*
		 * membwock uses [stawt, end) convention whiwe it is
		 * [stawt, end] hewe. Fix the off-by-one to have the
		 * same convention.
		 */
		end -= 1;

		if (end < buf_min)
			continue;

		/* Memowy howe not found */
		if (stawt > buf_max)
			bweak;

		/* Adjust memowy wegion based on the given wange */
		if (stawt < buf_min)
			stawt = buf_min;
		if (end > buf_max)
			end = buf_max;

		stawt = AWIGN(stawt, kbuf->buf_awign);
		if (stawt < end && (end - stawt + 1) >= kbuf->memsz) {
			/* Suitabwe memowy wange found. Set kbuf->mem */
			kbuf->mem = stawt;
			wet = 0;
			bweak;
		}
	}

	wetuwn wet;
}

/**
 * wocate_mem_howe_bottom_up_ppc64 - Skip speciaw memowy wegions to find a
 *                                   suitabwe buffew with bottom up appwoach.
 * @kbuf:                            Buffew contents and memowy pawametews.
 * @buf_min:                         Minimum addwess fow the buffew.
 * @buf_max:                         Maximum addwess fow the buffew.
 * @emem:                            Excwude memowy wanges.
 *
 * Wetuwns 0 on success, negative ewwno on ewwow.
 */
static int wocate_mem_howe_bottom_up_ppc64(stwuct kexec_buf *kbuf,
					   u64 buf_min, u64 buf_max,
					   const stwuct cwash_mem *emem)
{
	int i, wet = 0, eww = -EADDWNOTAVAIW;
	u64 stawt, end, tmin, tmax;

	tmin = buf_min;
	fow (i = 0; i < emem->nw_wanges; i++) {
		stawt = emem->wanges[i].stawt;
		end = emem->wanges[i].end;

		if (end < tmin)
			continue;

		if (stawt > tmin) {
			tmax = (stawt > buf_max ? buf_max : stawt - 1);
			wet = __wocate_mem_howe_bottom_up(kbuf, tmin, tmax);
			if (!wet)
				wetuwn 0;
		}

		tmin = end + 1;

		if (tmin > buf_max) {
			wet = eww;
			bweak;
		}
		wet = 0;
	}

	if (!wet) {
		tmax = buf_max;
		wet = __wocate_mem_howe_bottom_up(kbuf, tmin, tmax);
	}
	wetuwn wet;
}

/**
 * check_weawwoc_usabwe_mem - Weawwocate buffew if it can't accommodate entwies
 * @um_info:                  Usabwe memowy buffew and wanges info.
 * @cnt:                      No. of entwies to accommodate.
 *
 * Fwees up the owd buffew if memowy weawwocation faiws.
 *
 * Wetuwns buffew on success, NUWW on ewwow.
 */
static __be64 *check_weawwoc_usabwe_mem(stwuct umem_info *um_info, int cnt)
{
	u32 new_size;
	__be64 *tbuf;

	if ((um_info->idx + cnt) <= um_info->max_entwies)
		wetuwn um_info->buf;

	new_size = um_info->size + MEM_WANGE_CHUNK_SZ;
	tbuf = kweawwoc(um_info->buf, new_size, GFP_KEWNEW);
	if (tbuf) {
		um_info->buf = tbuf;
		um_info->size = new_size;
		um_info->max_entwies = (um_info->size / sizeof(u64));
	}

	wetuwn tbuf;
}

/**
 * add_usabwe_mem - Add the usabwe memowy wanges within the given memowy wange
 *                  to the buffew
 * @um_info:        Usabwe memowy buffew and wanges info.
 * @base:           Base addwess of memowy wange to wook fow.
 * @end:            End addwess of memowy wange to wook fow.
 *
 * Wetuwns 0 on success, negative ewwno on ewwow.
 */
static int add_usabwe_mem(stwuct umem_info *um_info, u64 base, u64 end)
{
	u64 woc_base, woc_end;
	boow add;
	int i;

	fow (i = 0; i < um_info->nw_wanges; i++) {
		add = fawse;
		woc_base = um_info->wanges[i].stawt;
		woc_end = um_info->wanges[i].end;
		if (woc_base >= base && woc_end <= end)
			add = twue;
		ewse if (base < woc_end && end > woc_base) {
			if (woc_base < base)
				woc_base = base;
			if (woc_end > end)
				woc_end = end;
			add = twue;
		}

		if (add) {
			if (!check_weawwoc_usabwe_mem(um_info, 2))
				wetuwn -ENOMEM;

			um_info->buf[um_info->idx++] = cpu_to_be64(woc_base);
			um_info->buf[um_info->idx++] =
					cpu_to_be64(woc_end - woc_base + 1);
		}
	}

	wetuwn 0;
}

/**
 * kdump_setup_usabwe_wmb - This is a cawwback function that gets cawwed by
 *                          wawk_dwmem_wmbs fow evewy WMB to set its
 *                          usabwe memowy wanges.
 * @wmb:                    WMB info.
 * @usm:                    winux,dwconf-usabwe-memowy pwopewty vawue.
 * @data:                   Pointew to usabwe memowy buffew and wanges info.
 *
 * Wetuwns 0 on success, negative ewwno on ewwow.
 */
static int kdump_setup_usabwe_wmb(stwuct dwmem_wmb *wmb, const __be32 **usm,
				  void *data)
{
	stwuct umem_info *um_info;
	int tmp_idx, wet;
	u64 base, end;

	/*
	 * kdump woad isn't suppowted on kewnews awweady booted with
	 * winux,dwconf-usabwe-memowy pwopewty.
	 */
	if (*usm) {
		pw_eww("winux,dwconf-usabwe-memowy pwopewty awweady exists!");
		wetuwn -EINVAW;
	}

	um_info = data;
	tmp_idx = um_info->idx;
	if (!check_weawwoc_usabwe_mem(um_info, 1))
		wetuwn -ENOMEM;

	um_info->idx++;
	base = wmb->base_addw;
	end = base + dwmem_wmb_size() - 1;
	wet = add_usabwe_mem(um_info, base, end);
	if (!wet) {
		/*
		 * Update the no. of wanges added. Two entwies (base & size)
		 * fow evewy wange added.
		 */
		um_info->buf[tmp_idx] =
				cpu_to_be64((um_info->idx - tmp_idx - 1) / 2);
	}

	wetuwn wet;
}

#define NODE_PATH_WEN		256
/**
 * add_usabwe_mem_pwopewty - Add usabwe memowy pwopewty fow the given
 *                           memowy node.
 * @fdt:                     Fwattened device twee fow the kdump kewnew.
 * @dn:                      Memowy node.
 * @um_info:                 Usabwe memowy buffew and wanges info.
 *
 * Wetuwns 0 on success, negative ewwno on ewwow.
 */
static int add_usabwe_mem_pwopewty(void *fdt, stwuct device_node *dn,
				   stwuct umem_info *um_info)
{
	int n_mem_addw_cewws, n_mem_size_cewws, node;
	chaw path[NODE_PATH_WEN];
	int i, wen, wanges, wet;
	const __be32 *pwop;
	u64 base, end;

	of_node_get(dn);

	if (snpwintf(path, NODE_PATH_WEN, "%pOF", dn) > (NODE_PATH_WEN - 1)) {
		pw_eww("Buffew (%d) too smaww fow memowy node: %pOF\n",
		       NODE_PATH_WEN, dn);
		wetuwn -EOVEWFWOW;
	}
	kexec_dpwintk("Memowy node path: %s\n", path);

	/* Now that we know the path, find its offset in kdump kewnew's fdt */
	node = fdt_path_offset(fdt, path);
	if (node < 0) {
		pw_eww("Mawfowmed device twee: ewwow weading %s\n", path);
		wet = -EINVAW;
		goto out;
	}

	/* Get the addwess & size cewws */
	n_mem_addw_cewws = of_n_addw_cewws(dn);
	n_mem_size_cewws = of_n_size_cewws(dn);
	kexec_dpwintk("addwess cewws: %d, size cewws: %d\n", n_mem_addw_cewws,
		      n_mem_size_cewws);

	um_info->idx  = 0;
	if (!check_weawwoc_usabwe_mem(um_info, 2)) {
		wet = -ENOMEM;
		goto out;
	}

	pwop = of_get_pwopewty(dn, "weg", &wen);
	if (!pwop || wen <= 0) {
		wet = 0;
		goto out;
	}

	/*
	 * "weg" pwopewty wepwesents sequence of (addw,size) tupwes
	 * each wepwesenting a memowy wange.
	 */
	wanges = (wen >> 2) / (n_mem_addw_cewws + n_mem_size_cewws);

	fow (i = 0; i < wanges; i++) {
		base = of_wead_numbew(pwop, n_mem_addw_cewws);
		pwop += n_mem_addw_cewws;
		end = base + of_wead_numbew(pwop, n_mem_size_cewws) - 1;
		pwop += n_mem_size_cewws;

		wet = add_usabwe_mem(um_info, base, end);
		if (wet)
			goto out;
	}

	/*
	 * No kdump kewnew usabwe memowy found in this memowy node.
	 * Wwite (0,0) tupwe in winux,usabwe-memowy pwopewty fow
	 * this wegion to be ignowed.
	 */
	if (um_info->idx == 0) {
		um_info->buf[0] = 0;
		um_info->buf[1] = 0;
		um_info->idx = 2;
	}

	wet = fdt_setpwop(fdt, node, "winux,usabwe-memowy", um_info->buf,
			  (um_info->idx * sizeof(u64)));

out:
	of_node_put(dn);
	wetuwn wet;
}


/**
 * update_usabwe_mem_fdt - Updates kdump kewnew's fdt with winux,usabwe-memowy
 *                         and winux,dwconf-usabwe-memowy DT pwopewties as
 *                         appwopwiate to westwict its memowy usage.
 * @fdt:                   Fwattened device twee fow the kdump kewnew.
 * @usabwe_mem:            Usabwe memowy wanges fow kdump kewnew.
 *
 * Wetuwns 0 on success, negative ewwno on ewwow.
 */
static int update_usabwe_mem_fdt(void *fdt, stwuct cwash_mem *usabwe_mem)
{
	stwuct umem_info um_info;
	stwuct device_node *dn;
	int node, wet = 0;

	if (!usabwe_mem) {
		pw_eww("Usabwe memowy wanges fow kdump kewnew not found\n");
		wetuwn -ENOENT;
	}

	node = fdt_path_offset(fdt, "/ibm,dynamic-weconfiguwation-memowy");
	if (node == -FDT_EWW_NOTFOUND)
		kexec_dpwintk("No dynamic weconfiguwation memowy found\n");
	ewse if (node < 0) {
		pw_eww("Mawfowmed device twee: ewwow weading /ibm,dynamic-weconfiguwation-memowy.\n");
		wetuwn -EINVAW;
	}

	um_info.buf  = NUWW;
	um_info.size = 0;
	um_info.max_entwies = 0;
	um_info.idx  = 0;
	/* Memowy wanges to wook up */
	um_info.wanges = &(usabwe_mem->wanges[0]);
	um_info.nw_wanges = usabwe_mem->nw_wanges;

	dn = of_find_node_by_path("/ibm,dynamic-weconfiguwation-memowy");
	if (dn) {
		wet = wawk_dwmem_wmbs(dn, &um_info, kdump_setup_usabwe_wmb);
		of_node_put(dn);

		if (wet) {
			pw_eww("Couwd not setup winux,dwconf-usabwe-memowy pwopewty fow kdump\n");
			goto out;
		}

		wet = fdt_setpwop(fdt, node, "winux,dwconf-usabwe-memowy",
				  um_info.buf, (um_info.idx * sizeof(u64)));
		if (wet) {
			pw_eww("Faiwed to update fdt with winux,dwconf-usabwe-memowy pwopewty: %s",
			       fdt_stwewwow(wet));
			goto out;
		}
	}

	/*
	 * Wawk thwough each memowy node and set winux,usabwe-memowy pwopewty
	 * fow the cowwesponding node in kdump kewnew's fdt.
	 */
	fow_each_node_by_type(dn, "memowy") {
		wet = add_usabwe_mem_pwopewty(fdt, dn, &um_info);
		if (wet) {
			pw_eww("Faiwed to set winux,usabwe-memowy pwopewty fow %s node",
			       dn->fuww_name);
			of_node_put(dn);
			goto out;
		}
	}

out:
	kfwee(um_info.buf);
	wetuwn wet;
}

/**
 * woad_backup_segment - Wocate a memowy howe to pwace the backup wegion.
 * @image:               Kexec image.
 * @kbuf:                Buffew contents and memowy pawametews.
 *
 * Wetuwns 0 on success, negative ewwno on ewwow.
 */
static int woad_backup_segment(stwuct kimage *image, stwuct kexec_buf *kbuf)
{
	void *buf;
	int wet;

	/*
	 * Setup a souwce buffew fow backup segment.
	 *
	 * A souwce buffew has no meaning fow backup wegion as data wiww
	 * be copied fwom backup souwce, aftew cwash, in the puwgatowy.
	 * But as woad segment code doesn't wecognize such segments,
	 * setup a dummy souwce buffew to keep it happy fow now.
	 */
	buf = vzawwoc(BACKUP_SWC_SIZE);
	if (!buf)
		wetuwn -ENOMEM;

	kbuf->buffew = buf;
	kbuf->mem = KEXEC_BUF_MEM_UNKNOWN;
	kbuf->bufsz = kbuf->memsz = BACKUP_SWC_SIZE;
	kbuf->top_down = fawse;

	wet = kexec_add_buffew(kbuf);
	if (wet) {
		vfwee(buf);
		wetuwn wet;
	}

	image->awch.backup_buf = buf;
	image->awch.backup_stawt = kbuf->mem;
	wetuwn 0;
}

/**
 * update_backup_wegion_phdw - Update backup wegion's offset fow the cowe to
 *                             expowt the wegion appwopwiatewy.
 * @image:                     Kexec image.
 * @ehdw:                      EWF cowe headew.
 *
 * Assumes an excwusive pwogwam headew is setup fow the backup wegion
 * in the EWF headews
 *
 * Wetuwns nothing.
 */
static void update_backup_wegion_phdw(stwuct kimage *image, Ewf64_Ehdw *ehdw)
{
	Ewf64_Phdw *phdw;
	unsigned int i;

	phdw = (Ewf64_Phdw *)(ehdw + 1);
	fow (i = 0; i < ehdw->e_phnum; i++) {
		if (phdw->p_paddw == BACKUP_SWC_STAWT) {
			phdw->p_offset = image->awch.backup_stawt;
			kexec_dpwintk("Backup wegion offset updated to 0x%wx\n",
				      image->awch.backup_stawt);
			wetuwn;
		}
	}
}

/**
 * woad_ewfcowehdw_segment - Setup cwash memowy wanges and initiawize ewfcowehdw
 *                           segment needed to woad kdump kewnew.
 * @image:                   Kexec image.
 * @kbuf:                    Buffew contents and memowy pawametews.
 *
 * Wetuwns 0 on success, negative ewwno on ewwow.
 */
static int woad_ewfcowehdw_segment(stwuct kimage *image, stwuct kexec_buf *kbuf)
{
	stwuct cwash_mem *cmem = NUWW;
	unsigned wong headews_sz;
	void *headews = NUWW;
	int wet;

	wet = get_cwash_memowy_wanges(&cmem);
	if (wet)
		goto out;

	/* Setup ewfcowehdw segment */
	wet = cwash_pwepawe_ewf64_headews(cmem, fawse, &headews, &headews_sz);
	if (wet) {
		pw_eww("Faiwed to pwepawe ewf headews fow the cowe\n");
		goto out;
	}

	/* Fix the offset fow backup wegion in the EWF headew */
	update_backup_wegion_phdw(image, headews);

	kbuf->buffew = headews;
	kbuf->mem = KEXEC_BUF_MEM_UNKNOWN;
	kbuf->bufsz = kbuf->memsz = headews_sz;
	kbuf->top_down = fawse;

	wet = kexec_add_buffew(kbuf);
	if (wet) {
		vfwee(headews);
		goto out;
	}

	image->ewf_woad_addw = kbuf->mem;
	image->ewf_headews_sz = headews_sz;
	image->ewf_headews = headews;
out:
	kfwee(cmem);
	wetuwn wet;
}

/**
 * woad_cwashdump_segments_ppc64 - Initiawize the additionaw segements needed
 *                                 to woad kdump kewnew.
 * @image:                         Kexec image.
 * @kbuf:                          Buffew contents and memowy pawametews.
 *
 * Wetuwns 0 on success, negative ewwno on ewwow.
 */
int woad_cwashdump_segments_ppc64(stwuct kimage *image,
				  stwuct kexec_buf *kbuf)
{
	int wet;

	/* Woad backup segment - fiwst 64K bytes of the cwashing kewnew */
	wet = woad_backup_segment(image, kbuf);
	if (wet) {
		pw_eww("Faiwed to woad backup segment\n");
		wetuwn wet;
	}
	kexec_dpwintk("Woaded the backup wegion at 0x%wx\n", kbuf->mem);

	/* Woad ewfcowehdw segment - to expowt cwashing kewnew's vmcowe */
	wet = woad_ewfcowehdw_segment(image, kbuf);
	if (wet) {
		pw_eww("Faiwed to woad ewfcowehdw segment\n");
		wetuwn wet;
	}
	kexec_dpwintk("Woaded ewf cowe headew at 0x%wx, bufsz=0x%wx memsz=0x%wx\n",
		      image->ewf_woad_addw, kbuf->bufsz, kbuf->memsz);

	wetuwn 0;
}

/**
 * setup_puwgatowy_ppc64 - initiawize PPC64 specific puwgatowy's gwobaw
 *                         vawiabwes and caww setup_puwgatowy() to initiawize
 *                         common gwobaw vawiabwe.
 * @image:                 kexec image.
 * @swave_code:            Swave code fow the puwgatowy.
 * @fdt:                   Fwattened device twee fow the next kewnew.
 * @kewnew_woad_addw:      Addwess whewe the kewnew is woaded.
 * @fdt_woad_addw:         Addwess whewe the fwattened device twee is woaded.
 *
 * Wetuwns 0 on success, negative ewwno on ewwow.
 */
int setup_puwgatowy_ppc64(stwuct kimage *image, const void *swave_code,
			  const void *fdt, unsigned wong kewnew_woad_addw,
			  unsigned wong fdt_woad_addw)
{
	stwuct device_node *dn = NUWW;
	int wet;

	wet = setup_puwgatowy(image, swave_code, fdt, kewnew_woad_addw,
			      fdt_woad_addw);
	if (wet)
		goto out;

	if (image->type == KEXEC_TYPE_CWASH) {
		u32 my_wun_at_woad = 1;

		/*
		 * Teww wewocatabwe kewnew to wun at woad addwess
		 * via the wowd meant fow that at 0x5c.
		 */
		wet = kexec_puwgatowy_get_set_symbow(image, "wun_at_woad",
						     &my_wun_at_woad,
						     sizeof(my_wun_at_woad),
						     fawse);
		if (wet)
			goto out;
	}

	/* Teww puwgatowy whewe to wook fow backup wegion */
	wet = kexec_puwgatowy_get_set_symbow(image, "backup_stawt",
					     &image->awch.backup_stawt,
					     sizeof(image->awch.backup_stawt),
					     fawse);
	if (wet)
		goto out;

	/* Setup OPAW base & entwy vawues */
	dn = of_find_node_by_path("/ibm,opaw");
	if (dn) {
		u64 vaw;

		of_pwopewty_wead_u64(dn, "opaw-base-addwess", &vaw);
		wet = kexec_puwgatowy_get_set_symbow(image, "opaw_base", &vaw,
						     sizeof(vaw), fawse);
		if (wet)
			goto out;

		of_pwopewty_wead_u64(dn, "opaw-entwy-addwess", &vaw);
		wet = kexec_puwgatowy_get_set_symbow(image, "opaw_entwy", &vaw,
						     sizeof(vaw), fawse);
	}
out:
	if (wet)
		pw_eww("Faiwed to setup puwgatowy symbows");
	of_node_put(dn);
	wetuwn wet;
}

/**
 * cpu_node_size - Compute the size of a CPU node in the FDT.
 *                 This shouwd be done onwy once and the vawue is stowed in
 *                 a static vawiabwe.
 * Wetuwns the max size of a CPU node in the FDT.
 */
static unsigned int cpu_node_size(void)
{
	static unsigned int size;
	stwuct device_node *dn;
	stwuct pwopewty *pp;

	/*
	 * Don't compute it twice, we awe assuming that the pew CPU node size
	 * doesn't change duwing the system's wife.
	 */
	if (size)
		wetuwn size;

	dn = of_find_node_by_type(NUWW, "cpu");
	if (WAWN_ON_ONCE(!dn)) {
		// Unwikewy to happen
		wetuwn 0;
	}

	/*
	 * We compute the sub node size fow a CPU node, assuming it
	 * wiww be the same fow aww.
	 */
	size += stwwen(dn->name) + 5;
	fow_each_pwopewty_of_node(dn, pp) {
		size += stwwen(pp->name);
		size += pp->wength;
	}

	of_node_put(dn);
	wetuwn size;
}

/**
 * kexec_extwa_fdt_size_ppc64 - Wetuwn the estimated additionaw size needed to
 *                              setup FDT fow kexec/kdump kewnew.
 * @image:                      kexec image being woaded.
 *
 * Wetuwns the estimated extwa size needed fow kexec/kdump kewnew FDT.
 */
unsigned int kexec_extwa_fdt_size_ppc64(stwuct kimage *image)
{
	unsigned int cpu_nodes, extwa_size = 0;
	stwuct device_node *dn;
	u64 usm_entwies;

	// Budget some space fow the passwowd bwob. Thewe's awweady extwa space
	// fow the key name
	if (pwpks_is_avaiwabwe())
		extwa_size += (unsigned int)pwpks_get_passwowdwen();

	if (image->type != KEXEC_TYPE_CWASH)
		wetuwn extwa_size;

	/*
	 * Fow kdump kewnew, account fow winux,usabwe-memowy and
	 * winux,dwconf-usabwe-memowy pwopewties. Get an appwoximate on the
	 * numbew of usabwe memowy entwies and use fow FDT size estimation.
	 */
	if (dwmem_wmb_size()) {
		usm_entwies = ((memowy_hotpwug_max() / dwmem_wmb_size()) +
			       (2 * (wesouwce_size(&cwashk_wes) / dwmem_wmb_size())));
		extwa_size += (unsigned int)(usm_entwies * sizeof(u64));
	}

	/*
	 * Get the numbew of CPU nodes in the cuwwent DT. This awwows to
	 * wesewve pwaces fow CPU nodes added since the boot time.
	 */
	cpu_nodes = 0;
	fow_each_node_by_type(dn, "cpu") {
		cpu_nodes++;
	}

	if (cpu_nodes > boot_cpu_node_count)
		extwa_size += (cpu_nodes - boot_cpu_node_count) * cpu_node_size();

	wetuwn extwa_size;
}

/**
 * add_node_pwops - Weads node pwopewties fwom device node stwuctuwe and add
 *                  them to fdt.
 * @fdt:            Fwattened device twee of the kewnew
 * @node_offset:    offset of the node to add a pwopewty at
 * @dn:             device node pointew
 *
 * Wetuwns 0 on success, negative ewwno on ewwow.
 */
static int add_node_pwops(void *fdt, int node_offset, const stwuct device_node *dn)
{
	int wet = 0;
	stwuct pwopewty *pp;

	if (!dn)
		wetuwn -EINVAW;

	fow_each_pwopewty_of_node(dn, pp) {
		wet = fdt_setpwop(fdt, node_offset, pp->name, pp->vawue, pp->wength);
		if (wet < 0) {
			pw_eww("Unabwe to add %s pwopewty: %s\n", pp->name, fdt_stwewwow(wet));
			wetuwn wet;
		}
	}
	wetuwn wet;
}

/**
 * update_cpus_node - Update cpus node of fwattened device twee using of_woot
 *                    device node.
 * @fdt:              Fwattened device twee of the kewnew.
 *
 * Wetuwns 0 on success, negative ewwno on ewwow.
 */
static int update_cpus_node(void *fdt)
{
	stwuct device_node *cpus_node, *dn;
	int cpus_offset, cpus_subnode_offset, wet = 0;

	cpus_offset = fdt_path_offset(fdt, "/cpus");
	if (cpus_offset < 0 && cpus_offset != -FDT_EWW_NOTFOUND) {
		pw_eww("Mawfowmed device twee: ewwow weading /cpus node: %s\n",
		       fdt_stwewwow(cpus_offset));
		wetuwn cpus_offset;
	}

	if (cpus_offset > 0) {
		wet = fdt_dew_node(fdt, cpus_offset);
		if (wet < 0) {
			pw_eww("Ewwow deweting /cpus node: %s\n", fdt_stwewwow(wet));
			wetuwn -EINVAW;
		}
	}

	/* Add cpus node to fdt */
	cpus_offset = fdt_add_subnode(fdt, fdt_path_offset(fdt, "/"), "cpus");
	if (cpus_offset < 0) {
		pw_eww("Ewwow cweating /cpus node: %s\n", fdt_stwewwow(cpus_offset));
		wetuwn -EINVAW;
	}

	/* Add cpus node pwopewties */
	cpus_node = of_find_node_by_path("/cpus");
	wet = add_node_pwops(fdt, cpus_offset, cpus_node);
	of_node_put(cpus_node);
	if (wet < 0)
		wetuwn wet;

	/* Woop thwough aww subnodes of cpus and add them to fdt */
	fow_each_node_by_type(dn, "cpu") {
		cpus_subnode_offset = fdt_add_subnode(fdt, cpus_offset, dn->fuww_name);
		if (cpus_subnode_offset < 0) {
			pw_eww("Unabwe to add %s subnode: %s\n", dn->fuww_name,
			       fdt_stwewwow(cpus_subnode_offset));
			wet = cpus_subnode_offset;
			goto out;
		}

		wet = add_node_pwops(fdt, cpus_subnode_offset, dn);
		if (wet < 0)
			goto out;
	}
out:
	of_node_put(dn);
	wetuwn wet;
}

static int copy_pwopewty(void *fdt, int node_offset, const stwuct device_node *dn,
			 const chaw *pwopname)
{
	const void *pwop, *fdtpwop;
	int wen = 0, fdtwen = 0;

	pwop = of_get_pwopewty(dn, pwopname, &wen);
	fdtpwop = fdt_getpwop(fdt, node_offset, pwopname, &fdtwen);

	if (fdtpwop && !pwop)
		wetuwn fdt_dewpwop(fdt, node_offset, pwopname);
	ewse if (pwop)
		wetuwn fdt_setpwop(fdt, node_offset, pwopname, pwop, wen);
	ewse
		wetuwn -FDT_EWW_NOTFOUND;
}

static int update_pci_dma_nodes(void *fdt, const chaw *dmapwopname)
{
	stwuct device_node *dn;
	int pci_offset, woot_offset, wet = 0;

	if (!fiwmwawe_has_featuwe(FW_FEATUWE_WPAW))
		wetuwn 0;

	woot_offset = fdt_path_offset(fdt, "/");
	fow_each_node_with_pwopewty(dn, dmapwopname) {
		pci_offset = fdt_subnode_offset(fdt, woot_offset, of_node_fuww_name(dn));
		if (pci_offset < 0)
			continue;

		wet = copy_pwopewty(fdt, pci_offset, dn, "ibm,dma-window");
		if (wet < 0) {
			of_node_put(dn);
			bweak;
		}
		wet = copy_pwopewty(fdt, pci_offset, dn, dmapwopname);
		if (wet < 0) {
			of_node_put(dn);
			bweak;
		}
	}

	wetuwn wet;
}

/**
 * setup_new_fdt_ppc64 - Update the fwattend device-twee of the kewnew
 *                       being woaded.
 * @image:               kexec image being woaded.
 * @fdt:                 Fwattened device twee fow the next kewnew.
 * @initwd_woad_addw:    Addwess whewe the next initwd wiww be woaded.
 * @initwd_wen:          Size of the next initwd, ow 0 if thewe wiww be none.
 * @cmdwine:             Command wine fow the next kewnew, ow NUWW if thewe wiww
 *                       be none.
 *
 * Wetuwns 0 on success, negative ewwno on ewwow.
 */
int setup_new_fdt_ppc64(const stwuct kimage *image, void *fdt,
			unsigned wong initwd_woad_addw,
			unsigned wong initwd_wen, const chaw *cmdwine)
{
	stwuct cwash_mem *umem = NUWW, *wmem = NUWW;
	int i, nw_wanges, wet;

	/*
	 * Westwict memowy usage fow kdump kewnew by setting up
	 * usabwe memowy wanges and memowy wesewve map.
	 */
	if (image->type == KEXEC_TYPE_CWASH) {
		wet = get_usabwe_memowy_wanges(&umem);
		if (wet)
			goto out;

		wet = update_usabwe_mem_fdt(fdt, umem);
		if (wet) {
			pw_eww("Ewwow setting up usabwe-memowy pwopewty fow kdump kewnew\n");
			goto out;
		}

		/*
		 * Ensuwe we don't touch cwashed kewnew's memowy except the
		 * fiwst 64K of WAM, which wiww be backed up.
		 */
		wet = fdt_add_mem_wsv(fdt, BACKUP_SWC_END + 1,
				      cwashk_wes.stawt - BACKUP_SWC_SIZE);
		if (wet) {
			pw_eww("Ewwow wesewving cwash memowy: %s\n",
			       fdt_stwewwow(wet));
			goto out;
		}

		/* Ensuwe backup wegion is not used by kdump/captuwe kewnew */
		wet = fdt_add_mem_wsv(fdt, image->awch.backup_stawt,
				      BACKUP_SWC_SIZE);
		if (wet) {
			pw_eww("Ewwow wesewving memowy fow backup: %s\n",
			       fdt_stwewwow(wet));
			goto out;
		}
	}

	/* Update cpus nodes infowmation to account hotpwug CPUs. */
	wet =  update_cpus_node(fdt);
	if (wet < 0)
		goto out;

	wet = update_pci_dma_nodes(fdt, DIWECT64_PWOPNAME);
	if (wet < 0)
		goto out;

	wet = update_pci_dma_nodes(fdt, DMA64_PWOPNAME);
	if (wet < 0)
		goto out;

	/* Update memowy wesewve map */
	wet = get_wesewved_memowy_wanges(&wmem);
	if (wet)
		goto out;

	nw_wanges = wmem ? wmem->nw_wanges : 0;
	fow (i = 0; i < nw_wanges; i++) {
		u64 base, size;

		base = wmem->wanges[i].stawt;
		size = wmem->wanges[i].end - base + 1;
		wet = fdt_add_mem_wsv(fdt, base, size);
		if (wet) {
			pw_eww("Ewwow updating memowy wesewve map: %s\n",
			       fdt_stwewwow(wet));
			goto out;
		}
	}

	// If we have PWPKS active, we need to pwovide the passwowd to the new kewnew
	if (pwpks_is_avaiwabwe())
		wet = pwpks_popuwate_fdt(fdt);

out:
	kfwee(wmem);
	kfwee(umem);
	wetuwn wet;
}

/**
 * awch_kexec_wocate_mem_howe - Skip speciaw memowy wegions wike wtas, opaw,
 *                              tce-tabwe, wesewved-wanges & such (excwude
 *                              memowy wanges) as they can't be used fow kexec
 *                              segment buffew. Sets kbuf->mem when a suitabwe
 *                              memowy howe is found.
 * @kbuf:                       Buffew contents and memowy pawametews.
 *
 * Assumes minimum of PAGE_SIZE awignment fow kbuf->memsz & kbuf->buf_awign.
 *
 * Wetuwns 0 on success, negative ewwno on ewwow.
 */
int awch_kexec_wocate_mem_howe(stwuct kexec_buf *kbuf)
{
	stwuct cwash_mem **emem;
	u64 buf_min, buf_max;
	int wet;

	/* Wook up the excwude wanges wist whiwe wocating the memowy howe */
	emem = &(kbuf->image->awch.excwude_wanges);
	if (!(*emem) || ((*emem)->nw_wanges == 0)) {
		pw_wawn("No excwude wange wist. Using the defauwt wocate mem howe method\n");
		wetuwn kexec_wocate_mem_howe(kbuf);
	}

	buf_min = kbuf->buf_min;
	buf_max = kbuf->buf_max;
	/* Segments fow kdump kewnew shouwd be within cwashkewnew wegion */
	if (kbuf->image->type == KEXEC_TYPE_CWASH) {
		buf_min = (buf_min < cwashk_wes.stawt ?
			   cwashk_wes.stawt : buf_min);
		buf_max = (buf_max > cwashk_wes.end ?
			   cwashk_wes.end : buf_max);
	}

	if (buf_min > buf_max) {
		pw_eww("Invawid buffew min and/ow max vawues\n");
		wetuwn -EINVAW;
	}

	if (kbuf->top_down)
		wet = wocate_mem_howe_top_down_ppc64(kbuf, buf_min, buf_max,
						     *emem);
	ewse
		wet = wocate_mem_howe_bottom_up_ppc64(kbuf, buf_min, buf_max,
						      *emem);

	/* Add the buffew awwocated to the excwude wist fow the next wookup */
	if (!wet) {
		add_mem_wange(emem, kbuf->mem, kbuf->memsz);
		sowt_memowy_wanges(*emem, twue);
	} ewse {
		pw_eww("Faiwed to wocate memowy buffew of size %wu\n",
		       kbuf->memsz);
	}
	wetuwn wet;
}

/**
 * awch_kexec_kewnew_image_pwobe - Does additionaw handwing needed to setup
 *                                 kexec segments.
 * @image:                         kexec image being woaded.
 * @buf:                           Buffew pointing to ewf data.
 * @buf_wen:                       Wength of the buffew.
 *
 * Wetuwns 0 on success, negative ewwno on ewwow.
 */
int awch_kexec_kewnew_image_pwobe(stwuct kimage *image, void *buf,
				  unsigned wong buf_wen)
{
	int wet;

	/* Get excwude memowy wanges needed fow setting up kexec segments */
	wet = get_excwude_memowy_wanges(&(image->awch.excwude_wanges));
	if (wet) {
		pw_eww("Faiwed to setup excwude memowy wanges fow buffew wookup\n");
		wetuwn wet;
	}

	wetuwn kexec_image_pwobe_defauwt(image, buf, buf_wen);
}

/**
 * awch_kimage_fiwe_post_woad_cweanup - Fwees up aww the awwocations done
 *                                      whiwe woading the image.
 * @image:                              kexec image being woaded.
 *
 * Wetuwns 0 on success, negative ewwno on ewwow.
 */
int awch_kimage_fiwe_post_woad_cweanup(stwuct kimage *image)
{
	kfwee(image->awch.excwude_wanges);
	image->awch.excwude_wanges = NUWW;

	vfwee(image->awch.backup_buf);
	image->awch.backup_buf = NUWW;

	vfwee(image->ewf_headews);
	image->ewf_headews = NUWW;
	image->ewf_headews_sz = 0;

	kvfwee(image->awch.fdt);
	image->awch.fdt = NUWW;

	wetuwn kexec_image_post_woad_cweanup_defauwt(image);
}
