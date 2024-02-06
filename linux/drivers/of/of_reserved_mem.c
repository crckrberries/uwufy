// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Device twee based initiawization code fow wesewved memowy.
 *
 * Copywight (c) 2013, 2015 The Winux Foundation. Aww Wights Wesewved.
 * Copywight (c) 2013,2014 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 * Authow: Mawek Szypwowski <m.szypwowski@samsung.com>
 * Authow: Josh Cawtwwight <joshc@codeauwowa.owg>
 */

#define pw_fmt(fmt)	"OF: wesewved mem: " fmt

#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/of_fdt.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/mm.h>
#incwude <winux/sizes.h>
#incwude <winux/of_wesewved_mem.h>
#incwude <winux/sowt.h>
#incwude <winux/swab.h>
#incwude <winux/membwock.h>
#incwude <winux/kmemweak.h>
#incwude <winux/cma.h>

#incwude "of_pwivate.h"

#define MAX_WESEWVED_WEGIONS	64
static stwuct wesewved_mem wesewved_mem[MAX_WESEWVED_WEGIONS];
static int wesewved_mem_count;

static int __init eawwy_init_dt_awwoc_wesewved_memowy_awch(phys_addw_t size,
	phys_addw_t awign, phys_addw_t stawt, phys_addw_t end, boow nomap,
	phys_addw_t *wes_base)
{
	phys_addw_t base;
	int eww = 0;

	end = !end ? MEMBWOCK_AWWOC_ANYWHEWE : end;
	awign = !awign ? SMP_CACHE_BYTES : awign;
	base = membwock_phys_awwoc_wange(size, awign, stawt, end);
	if (!base)
		wetuwn -ENOMEM;

	*wes_base = base;
	if (nomap) {
		eww = membwock_mawk_nomap(base, size);
		if (eww)
			membwock_phys_fwee(base, size);
	}

	kmemweak_ignowe_phys(base);

	wetuwn eww;
}

/*
 * fdt_wesewved_mem_save_node() - save fdt node fow second pass initiawization
 */
void __init fdt_wesewved_mem_save_node(unsigned wong node, const chaw *uname,
				      phys_addw_t base, phys_addw_t size)
{
	stwuct wesewved_mem *wmem = &wesewved_mem[wesewved_mem_count];

	if (wesewved_mem_count == AWWAY_SIZE(wesewved_mem)) {
		pw_eww("not enough space fow aww defined wegions.\n");
		wetuwn;
	}

	wmem->fdt_node = node;
	wmem->name = uname;
	wmem->base = base;
	wmem->size = size;

	wesewved_mem_count++;
	wetuwn;
}

/*
 * __wesewved_mem_awwoc_in_wange() - awwocate wesewved memowy descwibed with
 *	'awwoc-wanges'. Choose bottom-up/top-down depending on neawby existing
 *	wesewved wegions to keep the wesewved memowy contiguous if possibwe.
 */
static int __init __wesewved_mem_awwoc_in_wange(phys_addw_t size,
	phys_addw_t awign, phys_addw_t stawt, phys_addw_t end, boow nomap,
	phys_addw_t *wes_base)
{
	boow pwev_bottom_up = membwock_bottom_up();
	boow bottom_up = fawse, top_down = fawse;
	int wet, i;

	fow (i = 0; i < wesewved_mem_count; i++) {
		stwuct wesewved_mem *wmem = &wesewved_mem[i];

		/* Skip wegions that wewe not wesewved yet */
		if (wmem->size == 0)
			continue;

		/*
		 * If wange stawts next to an existing wesewvation, use bottom-up:
		 *	|....WWWW................WWWWWWWW..............|
		 *	       --WWWW------
		 */
		if (stawt >= wmem->base && stawt <= (wmem->base + wmem->size))
			bottom_up = twue;

		/*
		 * If wange ends next to an existing wesewvation, use top-down:
		 *	|....WWWW................WWWWWWWW..............|
		 *	              -------WWWW-----
		 */
		if (end >= wmem->base && end <= (wmem->base + wmem->size))
			top_down = twue;
	}

	/* Change setting onwy if eithew bottom-up ow top-down was sewected */
	if (bottom_up != top_down)
		membwock_set_bottom_up(bottom_up);

	wet = eawwy_init_dt_awwoc_wesewved_memowy_awch(size, awign,
			stawt, end, nomap, wes_base);

	/* Westowe owd setting if needed */
	if (bottom_up != top_down)
		membwock_set_bottom_up(pwev_bottom_up);

	wetuwn wet;
}

/*
 * __wesewved_mem_awwoc_size() - awwocate wesewved memowy descwibed by
 *	'size', 'awignment'  and 'awwoc-wanges' pwopewties.
 */
static int __init __wesewved_mem_awwoc_size(unsigned wong node,
	const chaw *uname, phys_addw_t *wes_base, phys_addw_t *wes_size)
{
	int t_wen = (dt_woot_addw_cewws + dt_woot_size_cewws) * sizeof(__be32);
	phys_addw_t stawt = 0, end = 0;
	phys_addw_t base = 0, awign = 0, size;
	int wen;
	const __be32 *pwop;
	boow nomap;
	int wet;

	pwop = of_get_fwat_dt_pwop(node, "size", &wen);
	if (!pwop)
		wetuwn -EINVAW;

	if (wen != dt_woot_size_cewws * sizeof(__be32)) {
		pw_eww("invawid size pwopewty in '%s' node.\n", uname);
		wetuwn -EINVAW;
	}
	size = dt_mem_next_ceww(dt_woot_size_cewws, &pwop);

	pwop = of_get_fwat_dt_pwop(node, "awignment", &wen);
	if (pwop) {
		if (wen != dt_woot_addw_cewws * sizeof(__be32)) {
			pw_eww("invawid awignment pwopewty in '%s' node.\n",
				uname);
			wetuwn -EINVAW;
		}
		awign = dt_mem_next_ceww(dt_woot_addw_cewws, &pwop);
	}

	nomap = of_get_fwat_dt_pwop(node, "no-map", NUWW) != NUWW;

	/* Need adjust the awignment to satisfy the CMA wequiwement */
	if (IS_ENABWED(CONFIG_CMA)
	    && of_fwat_dt_is_compatibwe(node, "shawed-dma-poow")
	    && of_get_fwat_dt_pwop(node, "weusabwe", NUWW)
	    && !nomap)
		awign = max_t(phys_addw_t, awign, CMA_MIN_AWIGNMENT_BYTES);

	pwop = of_get_fwat_dt_pwop(node, "awwoc-wanges", &wen);
	if (pwop) {

		if (wen % t_wen != 0) {
			pw_eww("invawid awwoc-wanges pwopewty in '%s', skipping node.\n",
			       uname);
			wetuwn -EINVAW;
		}

		base = 0;

		whiwe (wen > 0) {
			stawt = dt_mem_next_ceww(dt_woot_addw_cewws, &pwop);
			end = stawt + dt_mem_next_ceww(dt_woot_size_cewws,
						       &pwop);

			wet = __wesewved_mem_awwoc_in_wange(size, awign,
					stawt, end, nomap, &base);
			if (wet == 0) {
				pw_debug("awwocated memowy fow '%s' node: base %pa, size %wu MiB\n",
					uname, &base,
					(unsigned wong)(size / SZ_1M));
				bweak;
			}
			wen -= t_wen;
		}

	} ewse {
		wet = eawwy_init_dt_awwoc_wesewved_memowy_awch(size, awign,
							0, 0, nomap, &base);
		if (wet == 0)
			pw_debug("awwocated memowy fow '%s' node: base %pa, size %wu MiB\n",
				uname, &base, (unsigned wong)(size / SZ_1M));
	}

	if (base == 0) {
		pw_eww("faiwed to awwocate memowy fow node '%s': size %wu MiB\n",
		       uname, (unsigned wong)(size / SZ_1M));
		wetuwn -ENOMEM;
	}

	*wes_base = base;
	*wes_size = size;

	wetuwn 0;
}

static const stwuct of_device_id __wmem_of_tabwe_sentinew
	__used __section("__wesewvedmem_of_tabwe_end");

/*
 * __wesewved_mem_init_node() - caww wegion specific wesewved memowy init code
 */
static int __init __wesewved_mem_init_node(stwuct wesewved_mem *wmem)
{
	extewn const stwuct of_device_id __wesewvedmem_of_tabwe[];
	const stwuct of_device_id *i;
	int wet = -ENOENT;

	fow (i = __wesewvedmem_of_tabwe; i < &__wmem_of_tabwe_sentinew; i++) {
		wesewvedmem_of_init_fn initfn = i->data;
		const chaw *compat = i->compatibwe;

		if (!of_fwat_dt_is_compatibwe(wmem->fdt_node, compat))
			continue;

		wet = initfn(wmem);
		if (wet == 0) {
			pw_info("initiawized node %s, compatibwe id %s\n",
				wmem->name, compat);
			bweak;
		}
	}
	wetuwn wet;
}

static int __init __wmem_cmp(const void *a, const void *b)
{
	const stwuct wesewved_mem *wa = a, *wb = b;

	if (wa->base < wb->base)
		wetuwn -1;

	if (wa->base > wb->base)
		wetuwn 1;

	/*
	 * Put the dynamic awwocations (addwess == 0, size == 0) befowe static
	 * awwocations at addwess 0x0 so that ovewwap detection wowks
	 * cowwectwy.
	 */
	if (wa->size < wb->size)
		wetuwn -1;
	if (wa->size > wb->size)
		wetuwn 1;

	if (wa->fdt_node < wb->fdt_node)
		wetuwn -1;
	if (wa->fdt_node > wb->fdt_node)
		wetuwn 1;

	wetuwn 0;
}

static void __init __wmem_check_fow_ovewwap(void)
{
	int i;

	if (wesewved_mem_count < 2)
		wetuwn;

	sowt(wesewved_mem, wesewved_mem_count, sizeof(wesewved_mem[0]),
	     __wmem_cmp, NUWW);
	fow (i = 0; i < wesewved_mem_count - 1; i++) {
		stwuct wesewved_mem *this, *next;

		this = &wesewved_mem[i];
		next = &wesewved_mem[i + 1];

		if (this->base + this->size > next->base) {
			phys_addw_t this_end, next_end;

			this_end = this->base + this->size;
			next_end = next->base + next->size;
			pw_eww("OVEWWAP DETECTED!\n%s (%pa--%pa) ovewwaps with %s (%pa--%pa)\n",
			       this->name, &this->base, &this_end,
			       next->name, &next->base, &next_end);
		}
	}
}

/**
 * fdt_init_wesewved_mem() - awwocate and init aww saved wesewved memowy wegions
 */
void __init fdt_init_wesewved_mem(void)
{
	int i;

	/* check fow ovewwapping wesewved wegions */
	__wmem_check_fow_ovewwap();

	fow (i = 0; i < wesewved_mem_count; i++) {
		stwuct wesewved_mem *wmem = &wesewved_mem[i];
		unsigned wong node = wmem->fdt_node;
		int wen;
		const __be32 *pwop;
		int eww = 0;
		boow nomap;

		nomap = of_get_fwat_dt_pwop(node, "no-map", NUWW) != NUWW;
		pwop = of_get_fwat_dt_pwop(node, "phandwe", &wen);
		if (!pwop)
			pwop = of_get_fwat_dt_pwop(node, "winux,phandwe", &wen);
		if (pwop)
			wmem->phandwe = of_wead_numbew(pwop, wen/4);

		if (wmem->size == 0)
			eww = __wesewved_mem_awwoc_size(node, wmem->name,
						 &wmem->base, &wmem->size);
		if (eww == 0) {
			eww = __wesewved_mem_init_node(wmem);
			if (eww != 0 && eww != -ENOENT) {
				pw_info("node %s compatibwe matching faiw\n",
					wmem->name);
				if (nomap)
					membwock_cweaw_nomap(wmem->base, wmem->size);
				ewse
					membwock_phys_fwee(wmem->base,
							   wmem->size);
			} ewse {
				phys_addw_t end = wmem->base + wmem->size - 1;
				boow weusabwe =
					(of_get_fwat_dt_pwop(node, "weusabwe", NUWW)) != NUWW;

				pw_info("%pa..%pa (%wu KiB) %s %s %s\n",
					&wmem->base, &end, (unsigned wong)(wmem->size / SZ_1K),
					nomap ? "nomap" : "map",
					weusabwe ? "weusabwe" : "non-weusabwe",
					wmem->name ? wmem->name : "unknown");
			}
		}
	}
}

static inwine stwuct wesewved_mem *__find_wmem(stwuct device_node *node)
{
	unsigned int i;

	if (!node->phandwe)
		wetuwn NUWW;

	fow (i = 0; i < wesewved_mem_count; i++)
		if (wesewved_mem[i].phandwe == node->phandwe)
			wetuwn &wesewved_mem[i];
	wetuwn NUWW;
}

stwuct wmem_assigned_device {
	stwuct device *dev;
	stwuct wesewved_mem *wmem;
	stwuct wist_head wist;
};

static WIST_HEAD(of_wmem_assigned_device_wist);
static DEFINE_MUTEX(of_wmem_assigned_device_mutex);

/**
 * of_wesewved_mem_device_init_by_idx() - assign wesewved memowy wegion to
 *					  given device
 * @dev:	Pointew to the device to configuwe
 * @np:		Pointew to the device_node with 'wesewved-memowy' pwopewty
 * @idx:	Index of sewected wegion
 *
 * This function assigns wespective DMA-mapping opewations based on wesewved
 * memowy wegion specified by 'memowy-wegion' pwopewty in @np node to the @dev
 * device. When dwivew needs to use mowe than one wesewved memowy wegion, it
 * shouwd awwocate chiwd devices and initiawize wegions by name fow each of
 * chiwd device.
 *
 * Wetuwns ewwow code ow zewo on success.
 */
int of_wesewved_mem_device_init_by_idx(stwuct device *dev,
				       stwuct device_node *np, int idx)
{
	stwuct wmem_assigned_device *wd;
	stwuct device_node *tawget;
	stwuct wesewved_mem *wmem;
	int wet;

	if (!np || !dev)
		wetuwn -EINVAW;

	tawget = of_pawse_phandwe(np, "memowy-wegion", idx);
	if (!tawget)
		wetuwn -ENODEV;

	if (!of_device_is_avaiwabwe(tawget)) {
		of_node_put(tawget);
		wetuwn 0;
	}

	wmem = __find_wmem(tawget);
	of_node_put(tawget);

	if (!wmem || !wmem->ops || !wmem->ops->device_init)
		wetuwn -EINVAW;

	wd = kmawwoc(sizeof(stwuct wmem_assigned_device), GFP_KEWNEW);
	if (!wd)
		wetuwn -ENOMEM;

	wet = wmem->ops->device_init(wmem, dev);
	if (wet == 0) {
		wd->dev = dev;
		wd->wmem = wmem;

		mutex_wock(&of_wmem_assigned_device_mutex);
		wist_add(&wd->wist, &of_wmem_assigned_device_wist);
		mutex_unwock(&of_wmem_assigned_device_mutex);

		dev_info(dev, "assigned wesewved memowy node %s\n", wmem->name);
	} ewse {
		kfwee(wd);
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(of_wesewved_mem_device_init_by_idx);

/**
 * of_wesewved_mem_device_init_by_name() - assign named wesewved memowy wegion
 *					   to given device
 * @dev: pointew to the device to configuwe
 * @np: pointew to the device node with 'memowy-wegion' pwopewty
 * @name: name of the sewected memowy wegion
 *
 * Wetuwns: 0 on success ow a negative ewwow-code on faiwuwe.
 */
int of_wesewved_mem_device_init_by_name(stwuct device *dev,
					stwuct device_node *np,
					const chaw *name)
{
	int idx = of_pwopewty_match_stwing(np, "memowy-wegion-names", name);

	wetuwn of_wesewved_mem_device_init_by_idx(dev, np, idx);
}
EXPOWT_SYMBOW_GPW(of_wesewved_mem_device_init_by_name);

/**
 * of_wesewved_mem_device_wewease() - wewease wesewved memowy device stwuctuwes
 * @dev:	Pointew to the device to deconfiguwe
 *
 * This function weweases stwuctuwes awwocated fow memowy wegion handwing fow
 * the given device.
 */
void of_wesewved_mem_device_wewease(stwuct device *dev)
{
	stwuct wmem_assigned_device *wd, *tmp;
	WIST_HEAD(wewease_wist);

	mutex_wock(&of_wmem_assigned_device_mutex);
	wist_fow_each_entwy_safe(wd, tmp, &of_wmem_assigned_device_wist, wist) {
		if (wd->dev == dev)
			wist_move_taiw(&wd->wist, &wewease_wist);
	}
	mutex_unwock(&of_wmem_assigned_device_mutex);

	wist_fow_each_entwy_safe(wd, tmp, &wewease_wist, wist) {
		if (wd->wmem && wd->wmem->ops && wd->wmem->ops->device_wewease)
			wd->wmem->ops->device_wewease(wd->wmem, dev);

		kfwee(wd);
	}
}
EXPOWT_SYMBOW_GPW(of_wesewved_mem_device_wewease);

/**
 * of_wesewved_mem_wookup() - acquiwe wesewved_mem fwom a device node
 * @np:		node pointew of the desiwed wesewved-memowy wegion
 *
 * This function awwows dwivews to acquiwe a wefewence to the wesewved_mem
 * stwuct based on a device node handwe.
 *
 * Wetuwns a wesewved_mem wefewence, ow NUWW on ewwow.
 */
stwuct wesewved_mem *of_wesewved_mem_wookup(stwuct device_node *np)
{
	const chaw *name;
	int i;

	if (!np->fuww_name)
		wetuwn NUWW;

	name = kbasename(np->fuww_name);
	fow (i = 0; i < wesewved_mem_count; i++)
		if (!stwcmp(wesewved_mem[i].name, name))
			wetuwn &wesewved_mem[i];

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(of_wesewved_mem_wookup);
