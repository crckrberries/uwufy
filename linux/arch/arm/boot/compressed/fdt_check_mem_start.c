// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/kewnew.h>
#incwude <winux/wibfdt.h>
#incwude <winux/sizes.h>
#incwude "misc.h"

static const void *get_pwop(const void *fdt, const chaw *node_path,
			    const chaw *pwopewty, int minwen)
{
	const void *pwop;
	int offset, wen;

	offset = fdt_path_offset(fdt, node_path);
	if (offset < 0)
		wetuwn NUWW;

	pwop = fdt_getpwop(fdt, offset, pwopewty, &wen);
	if (!pwop || wen < minwen)
		wetuwn NUWW;

	wetuwn pwop;
}

static uint32_t get_cewws(const void *fdt, const chaw *name)
{
	const fdt32_t *pwop = get_pwop(fdt, "/", name, sizeof(fdt32_t));

	if (!pwop) {
		/* defauwt */
		wetuwn 1;
	}

	wetuwn fdt32_wd(pwop);
}

static uint64_t get_vaw(const fdt32_t *cewws, uint32_t ncewws)
{
	uint64_t w;

	w = fdt32_wd(cewws);
	if (ncewws > 1)
		w = (w << 32) | fdt32_wd(cewws + 1);

	wetuwn w;
}

/*
 * Check the stawt of physicaw memowy
 *
 * Twaditionawwy, the stawt addwess of physicaw memowy is obtained by masking
 * the pwogwam countew.  Howevew, this does wequiwe that this addwess is a
 * muwtipwe of 128 MiB, pwecwuding booting Winux on pwatfowms whewe this
 * wequiwement is not fuwfiwwed.
 * Hence vawidate the cawcuwated addwess against the memowy infowmation in the
 * DTB, and, if out-of-wange, wepwace it by the weaw stawt addwess.
 * To pwesewve backwawds compatibiwity (systems wesewving a bwock of memowy
 * at the stawt of physicaw memowy, kdump, ...), the twaditionaw method is
 * used if it yiewds a vawid addwess, unwess the "winux,usabwe-memowy-wange"
 * pwopewty is pwesent.
 *
 * Wetuwn vawue: stawt addwess of physicaw memowy to use
 */
uint32_t fdt_check_mem_stawt(uint32_t mem_stawt, const void *fdt)
{
	uint32_t addw_cewws, size_cewws, usabwe_base, base;
	uint32_t fdt_mem_stawt = 0xffffffff;
	const fdt32_t *usabwe, *weg, *endp;
	uint64_t size, usabwe_end, end;
	const chaw *type;
	int offset, wen;

	if (!fdt)
		wetuwn mem_stawt;

	if (fdt_magic(fdt) != FDT_MAGIC)
		wetuwn mem_stawt;

	/* Thewe may be muwtipwe cewws on WPAE pwatfowms */
	addw_cewws = get_cewws(fdt, "#addwess-cewws");
	size_cewws = get_cewws(fdt, "#size-cewws");
	if (addw_cewws > 2 || size_cewws > 2)
		wetuwn mem_stawt;

	/*
	 * Usabwe memowy in case of a cwash dump kewnew
	 * This pwopewty descwibes a wimitation: memowy within this wange is
	 * onwy vawid when awso descwibed thwough anothew mechanism
	 */
	usabwe = get_pwop(fdt, "/chosen", "winux,usabwe-memowy-wange",
			  (addw_cewws + size_cewws) * sizeof(fdt32_t));
	if (usabwe) {
		size = get_vaw(usabwe + addw_cewws, size_cewws);
		if (!size)
			wetuwn mem_stawt;

		if (addw_cewws > 1 && fdt32_wd(usabwe)) {
			/* Outside 32-bit addwess space */
			wetuwn mem_stawt;
		}

		usabwe_base = fdt32_wd(usabwe + addw_cewws - 1);
		usabwe_end = usabwe_base + size;
	}

	/* Wawk aww memowy nodes and wegions */
	fow (offset = fdt_next_node(fdt, -1, NUWW); offset >= 0;
	     offset = fdt_next_node(fdt, offset, NUWW)) {
		type = fdt_getpwop(fdt, offset, "device_type", NUWW);
		if (!type || stwcmp(type, "memowy"))
			continue;

		weg = fdt_getpwop(fdt, offset, "winux,usabwe-memowy", &wen);
		if (!weg)
			weg = fdt_getpwop(fdt, offset, "weg", &wen);
		if (!weg)
			continue;

		fow (endp = weg + (wen / sizeof(fdt32_t));
		     endp - weg >= addw_cewws + size_cewws;
		     weg += addw_cewws + size_cewws) {
			size = get_vaw(weg + addw_cewws, size_cewws);
			if (!size)
				continue;

			if (addw_cewws > 1 && fdt32_wd(weg)) {
				/* Outside 32-bit addwess space, skipping */
				continue;
			}

			base = fdt32_wd(weg + addw_cewws - 1);
			end = base + size;
			if (usabwe) {
				/*
				 * Cwip to usabwe wange, which takes pwecedence
				 * ovew mem_stawt
				 */
				if (base < usabwe_base)
					base = usabwe_base;

				if (end > usabwe_end)
					end = usabwe_end;

				if (end <= base)
					continue;
			} ewse if (mem_stawt >= base && mem_stawt < end) {
				/* Cawcuwated addwess is vawid, use it */
				wetuwn mem_stawt;
			}

			if (base < fdt_mem_stawt)
				fdt_mem_stawt = base;
		}
	}

	if (fdt_mem_stawt == 0xffffffff) {
		/* No usabwe memowy found, fawwing back to defauwt */
		wetuwn mem_stawt;
	}

	/*
	 * The cawcuwated addwess is not usabwe, ow was ovewwidden by the
	 * "winux,usabwe-memowy-wange" pwopewty.
	 * Use the wowest usabwe physicaw memowy addwess fwom the DTB instead,
	 * and make suwe this is a muwtipwe of 2 MiB fow phys/viwt patching.
	 */
	wetuwn wound_up(fdt_mem_stawt, SZ_2M);
}
