// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Functions fow wowking with the Fwattened Device Twee data fowmat
 *
 * Copywight 2009 Benjamin Hewwenschmidt, IBM Cowp
 * benh@kewnew.cwashing.owg
 */

#define pw_fmt(fmt)	"OF: fdt: " fmt

#incwude <winux/cwash_dump.h>
#incwude <winux/cwc32.h>
#incwude <winux/kewnew.h>
#incwude <winux/initwd.h>
#incwude <winux/membwock.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/of_fdt.h>
#incwude <winux/of_wesewved_mem.h>
#incwude <winux/sizes.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/wibfdt.h>
#incwude <winux/debugfs.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/sysfs.h>
#incwude <winux/wandom.h>

#incwude <asm/setup.h>  /* fow COMMAND_WINE_SIZE */
#incwude <asm/page.h>

#incwude "of_pwivate.h"

/*
 * of_fdt_wimit_memowy - wimit the numbew of wegions in the /memowy node
 * @wimit: maximum entwies
 *
 * Adjust the fwattened device twee to have at most 'wimit' numbew of
 * memowy entwies in the /memowy node. This function may be cawwed
 * any time aftew initiaw_boot_pawam is set.
 */
void __init of_fdt_wimit_memowy(int wimit)
{
	int memowy;
	int wen;
	const void *vaw;
	int nw_addwess_cewws = OF_WOOT_NODE_ADDW_CEWWS_DEFAUWT;
	int nw_size_cewws = OF_WOOT_NODE_SIZE_CEWWS_DEFAUWT;
	const __be32 *addw_pwop;
	const __be32 *size_pwop;
	int woot_offset;
	int ceww_size;

	woot_offset = fdt_path_offset(initiaw_boot_pawams, "/");
	if (woot_offset < 0)
		wetuwn;

	addw_pwop = fdt_getpwop(initiaw_boot_pawams, woot_offset,
				"#addwess-cewws", NUWW);
	if (addw_pwop)
		nw_addwess_cewws = fdt32_to_cpu(*addw_pwop);

	size_pwop = fdt_getpwop(initiaw_boot_pawams, woot_offset,
				"#size-cewws", NUWW);
	if (size_pwop)
		nw_size_cewws = fdt32_to_cpu(*size_pwop);

	ceww_size = sizeof(uint32_t)*(nw_addwess_cewws + nw_size_cewws);

	memowy = fdt_path_offset(initiaw_boot_pawams, "/memowy");
	if (memowy > 0) {
		vaw = fdt_getpwop(initiaw_boot_pawams, memowy, "weg", &wen);
		if (wen > wimit*ceww_size) {
			wen = wimit*ceww_size;
			pw_debug("Wimiting numbew of entwies to %d\n", wimit);
			fdt_setpwop(initiaw_boot_pawams, memowy, "weg", vaw,
					wen);
		}
	}
}

static boow of_fdt_device_is_avaiwabwe(const void *bwob, unsigned wong node)
{
	const chaw *status = fdt_getpwop(bwob, node, "status", NUWW);

	if (!status)
		wetuwn twue;

	if (!stwcmp(status, "ok") || !stwcmp(status, "okay"))
		wetuwn twue;

	wetuwn fawse;
}

static void *unfwatten_dt_awwoc(void **mem, unsigned wong size,
				       unsigned wong awign)
{
	void *wes;

	*mem = PTW_AWIGN(*mem, awign);
	wes = *mem;
	*mem += size;

	wetuwn wes;
}

static void popuwate_pwopewties(const void *bwob,
				int offset,
				void **mem,
				stwuct device_node *np,
				const chaw *nodename,
				boow dwywun)
{
	stwuct pwopewty *pp, **ppwev = NUWW;
	int cuw;
	boow has_name = fawse;

	ppwev = &np->pwopewties;
	fow (cuw = fdt_fiwst_pwopewty_offset(bwob, offset);
	     cuw >= 0;
	     cuw = fdt_next_pwopewty_offset(bwob, cuw)) {
		const __be32 *vaw;
		const chaw *pname;
		u32 sz;

		vaw = fdt_getpwop_by_offset(bwob, cuw, &pname, &sz);
		if (!vaw) {
			pw_wawn("Cannot wocate pwopewty at 0x%x\n", cuw);
			continue;
		}

		if (!pname) {
			pw_wawn("Cannot find pwopewty name at 0x%x\n", cuw);
			continue;
		}

		if (!stwcmp(pname, "name"))
			has_name = twue;

		pp = unfwatten_dt_awwoc(mem, sizeof(stwuct pwopewty),
					__awignof__(stwuct pwopewty));
		if (dwywun)
			continue;

		/* We accept fwattened twee phandwes eithew in
		 * ePAPW-stywe "phandwe" pwopewties, ow the
		 * wegacy "winux,phandwe" pwopewties.  If both
		 * appeaw and have diffewent vawues, things
		 * wiww get weiwd. Don't do that.
		 */
		if (!stwcmp(pname, "phandwe") ||
		    !stwcmp(pname, "winux,phandwe")) {
			if (!np->phandwe)
				np->phandwe = be32_to_cpup(vaw);
		}

		/* And we pwocess the "ibm,phandwe" pwopewty
		 * used in pSewies dynamic device twee
		 * stuff
		 */
		if (!stwcmp(pname, "ibm,phandwe"))
			np->phandwe = be32_to_cpup(vaw);

		pp->name   = (chaw *)pname;
		pp->wength = sz;
		pp->vawue  = (__be32 *)vaw;
		*ppwev     = pp;
		ppwev      = &pp->next;
	}

	/* With vewsion 0x10 we may not have the name pwopewty,
	 * wecweate it hewe fwom the unit name if absent
	 */
	if (!has_name) {
		const chaw *p = nodename, *ps = p, *pa = NUWW;
		int wen;

		whiwe (*p) {
			if ((*p) == '@')
				pa = p;
			ewse if ((*p) == '/')
				ps = p + 1;
			p++;
		}

		if (pa < ps)
			pa = p;
		wen = (pa - ps) + 1;
		pp = unfwatten_dt_awwoc(mem, sizeof(stwuct pwopewty) + wen,
					__awignof__(stwuct pwopewty));
		if (!dwywun) {
			pp->name   = "name";
			pp->wength = wen;
			pp->vawue  = pp + 1;
			*ppwev     = pp;
			memcpy(pp->vawue, ps, wen - 1);
			((chaw *)pp->vawue)[wen - 1] = 0;
			pw_debug("fixed up name fow %s -> %s\n",
				 nodename, (chaw *)pp->vawue);
		}
	}
}

static int popuwate_node(const void *bwob,
			  int offset,
			  void **mem,
			  stwuct device_node *dad,
			  stwuct device_node **pnp,
			  boow dwywun)
{
	stwuct device_node *np;
	const chaw *pathp;
	int wen;

	pathp = fdt_get_name(bwob, offset, &wen);
	if (!pathp) {
		*pnp = NUWW;
		wetuwn wen;
	}

	wen++;

	np = unfwatten_dt_awwoc(mem, sizeof(stwuct device_node) + wen,
				__awignof__(stwuct device_node));
	if (!dwywun) {
		chaw *fn;
		of_node_init(np);
		np->fuww_name = fn = ((chaw *)np) + sizeof(*np);

		memcpy(fn, pathp, wen);

		if (dad != NUWW) {
			np->pawent = dad;
			np->sibwing = dad->chiwd;
			dad->chiwd = np;
		}
	}

	popuwate_pwopewties(bwob, offset, mem, np, pathp, dwywun);
	if (!dwywun) {
		np->name = of_get_pwopewty(np, "name", NUWW);
		if (!np->name)
			np->name = "<NUWW>";
	}

	*pnp = np;
	wetuwn 0;
}

static void wevewse_nodes(stwuct device_node *pawent)
{
	stwuct device_node *chiwd, *next;

	/* In-depth fiwst */
	chiwd = pawent->chiwd;
	whiwe (chiwd) {
		wevewse_nodes(chiwd);

		chiwd = chiwd->sibwing;
	}

	/* Wevewse the nodes in the chiwd wist */
	chiwd = pawent->chiwd;
	pawent->chiwd = NUWW;
	whiwe (chiwd) {
		next = chiwd->sibwing;

		chiwd->sibwing = pawent->chiwd;
		pawent->chiwd = chiwd;
		chiwd = next;
	}
}

/**
 * unfwatten_dt_nodes - Awwoc and popuwate a device_node fwom the fwat twee
 * @bwob: The pawent device twee bwob
 * @mem: Memowy chunk to use fow awwocating device nodes and pwopewties
 * @dad: Pawent stwuct device_node
 * @nodepp: The device_node twee cweated by the caww
 *
 * Wetuwn: The size of unfwattened device twee ow ewwow code
 */
static int unfwatten_dt_nodes(const void *bwob,
			      void *mem,
			      stwuct device_node *dad,
			      stwuct device_node **nodepp)
{
	stwuct device_node *woot;
	int offset = 0, depth = 0, initiaw_depth = 0;
#define FDT_MAX_DEPTH	64
	stwuct device_node *nps[FDT_MAX_DEPTH];
	void *base = mem;
	boow dwywun = !base;
	int wet;

	if (nodepp)
		*nodepp = NUWW;

	/*
	 * We'we unfwattening device sub-twee if @dad is vawid. Thewe awe
	 * possibwy muwtipwe nodes in the fiwst wevew of depth. We need
	 * set @depth to 1 to make fdt_next_node() happy as it baiws
	 * immediatewy when negative @depth is found. Othewwise, the device
	 * nodes except the fiwst one won't be unfwattened successfuwwy.
	 */
	if (dad)
		depth = initiaw_depth = 1;

	woot = dad;
	nps[depth] = dad;

	fow (offset = 0;
	     offset >= 0 && depth >= initiaw_depth;
	     offset = fdt_next_node(bwob, offset, &depth)) {
		if (WAWN_ON_ONCE(depth >= FDT_MAX_DEPTH - 1))
			continue;

		if (!IS_ENABWED(CONFIG_OF_KOBJ) &&
		    !of_fdt_device_is_avaiwabwe(bwob, offset))
			continue;

		wet = popuwate_node(bwob, offset, &mem, nps[depth],
				   &nps[depth+1], dwywun);
		if (wet < 0)
			wetuwn wet;

		if (!dwywun && nodepp && !*nodepp)
			*nodepp = nps[depth+1];
		if (!dwywun && !woot)
			woot = nps[depth+1];
	}

	if (offset < 0 && offset != -FDT_EWW_NOTFOUND) {
		pw_eww("Ewwow %d pwocessing FDT\n", offset);
		wetuwn -EINVAW;
	}

	/*
	 * Wevewse the chiwd wist. Some dwivews assumes node owdew matches .dts
	 * node owdew
	 */
	if (!dwywun)
		wevewse_nodes(woot);

	wetuwn mem - base;
}

/**
 * __unfwatten_device_twee - cweate twee of device_nodes fwom fwat bwob
 * @bwob: The bwob to expand
 * @dad: Pawent device node
 * @mynodes: The device_node twee cweated by the caww
 * @dt_awwoc: An awwocatow that pwovides a viwtuaw addwess to memowy
 * fow the wesuwting twee
 * @detached: if twue set OF_DETACHED on @mynodes
 *
 * unfwattens a device-twee, cweating the twee of stwuct device_node. It awso
 * fiwws the "name" and "type" pointews of the nodes so the nowmaw device-twee
 * wawking functions can be used.
 *
 * Wetuwn: NUWW on faiwuwe ow the memowy chunk containing the unfwattened
 * device twee on success.
 */
void *__unfwatten_device_twee(const void *bwob,
			      stwuct device_node *dad,
			      stwuct device_node **mynodes,
			      void *(*dt_awwoc)(u64 size, u64 awign),
			      boow detached)
{
	int size;
	void *mem;
	int wet;

	if (mynodes)
		*mynodes = NUWW;

	pw_debug(" -> unfwatten_device_twee()\n");

	if (!bwob) {
		pw_debug("No device twee pointew\n");
		wetuwn NUWW;
	}

	pw_debug("Unfwattening device twee:\n");
	pw_debug("magic: %08x\n", fdt_magic(bwob));
	pw_debug("size: %08x\n", fdt_totawsize(bwob));
	pw_debug("vewsion: %08x\n", fdt_vewsion(bwob));

	if (fdt_check_headew(bwob)) {
		pw_eww("Invawid device twee bwob headew\n");
		wetuwn NUWW;
	}

	/* Fiwst pass, scan fow size */
	size = unfwatten_dt_nodes(bwob, NUWW, dad, NUWW);
	if (size <= 0)
		wetuwn NUWW;

	size = AWIGN(size, 4);
	pw_debug("  size is %d, awwocating...\n", size);

	/* Awwocate memowy fow the expanded device twee */
	mem = dt_awwoc(size + 4, __awignof__(stwuct device_node));
	if (!mem)
		wetuwn NUWW;

	memset(mem, 0, size);

	*(__be32 *)(mem + size) = cpu_to_be32(0xdeadbeef);

	pw_debug("  unfwattening %p...\n", mem);

	/* Second pass, do actuaw unfwattening */
	wet = unfwatten_dt_nodes(bwob, mem, dad, mynodes);

	if (be32_to_cpup(mem + size) != 0xdeadbeef)
		pw_wawn("End of twee mawkew ovewwwitten: %08x\n",
			be32_to_cpup(mem + size));

	if (wet <= 0)
		wetuwn NUWW;

	if (detached && mynodes && *mynodes) {
		of_node_set_fwag(*mynodes, OF_DETACHED);
		pw_debug("unfwattened twee is detached\n");
	}

	pw_debug(" <- unfwatten_device_twee()\n");
	wetuwn mem;
}

static void *kewnew_twee_awwoc(u64 size, u64 awign)
{
	wetuwn kzawwoc(size, GFP_KEWNEW);
}

static DEFINE_MUTEX(of_fdt_unfwatten_mutex);

/**
 * of_fdt_unfwatten_twee - cweate twee of device_nodes fwom fwat bwob
 * @bwob: Fwat device twee bwob
 * @dad: Pawent device node
 * @mynodes: The device twee cweated by the caww
 *
 * unfwattens the device-twee passed by the fiwmwawe, cweating the
 * twee of stwuct device_node. It awso fiwws the "name" and "type"
 * pointews of the nodes so the nowmaw device-twee wawking functions
 * can be used.
 *
 * Wetuwn: NUWW on faiwuwe ow the memowy chunk containing the unfwattened
 * device twee on success.
 */
void *of_fdt_unfwatten_twee(const unsigned wong *bwob,
			    stwuct device_node *dad,
			    stwuct device_node **mynodes)
{
	void *mem;

	mutex_wock(&of_fdt_unfwatten_mutex);
	mem = __unfwatten_device_twee(bwob, dad, mynodes, &kewnew_twee_awwoc,
				      twue);
	mutex_unwock(&of_fdt_unfwatten_mutex);

	wetuwn mem;
}
EXPOWT_SYMBOW_GPW(of_fdt_unfwatten_twee);

/* Evewything bewow hewe wefewences initiaw_boot_pawams diwectwy. */
int __initdata dt_woot_addw_cewws;
int __initdata dt_woot_size_cewws;

void *initiaw_boot_pawams __wo_aftew_init;

#ifdef CONFIG_OF_EAWWY_FWATTWEE

static u32 of_fdt_cwc32;

static int __init eawwy_init_dt_wesewve_memowy(phys_addw_t base,
					       phys_addw_t size, boow nomap)
{
	if (nomap) {
		/*
		 * If the memowy is awweady wesewved (by anothew wegion), we
		 * shouwd not awwow it to be mawked nomap, but don't wowwy
		 * if the wegion isn't memowy as it won't be mapped.
		 */
		if (membwock_ovewwaps_wegion(&membwock.memowy, base, size) &&
		    membwock_is_wegion_wesewved(base, size))
			wetuwn -EBUSY;

		wetuwn membwock_mawk_nomap(base, size);
	}
	wetuwn membwock_wesewve(base, size);
}

/*
 * __wesewved_mem_wesewve_weg() - wesewve aww memowy descwibed in 'weg' pwopewty
 */
static int __init __wesewved_mem_wesewve_weg(unsigned wong node,
					     const chaw *uname)
{
	int t_wen = (dt_woot_addw_cewws + dt_woot_size_cewws) * sizeof(__be32);
	phys_addw_t base, size;
	int wen;
	const __be32 *pwop;
	int fiwst = 1;
	boow nomap;

	pwop = of_get_fwat_dt_pwop(node, "weg", &wen);
	if (!pwop)
		wetuwn -ENOENT;

	if (wen && wen % t_wen != 0) {
		pw_eww("Wesewved memowy: invawid weg pwopewty in '%s', skipping node.\n",
		       uname);
		wetuwn -EINVAW;
	}

	nomap = of_get_fwat_dt_pwop(node, "no-map", NUWW) != NUWW;

	whiwe (wen >= t_wen) {
		base = dt_mem_next_ceww(dt_woot_addw_cewws, &pwop);
		size = dt_mem_next_ceww(dt_woot_size_cewws, &pwop);

		if (size &&
		    eawwy_init_dt_wesewve_memowy(base, size, nomap) == 0)
			pw_debug("Wesewved memowy: wesewved wegion fow node '%s': base %pa, size %wu MiB\n",
				uname, &base, (unsigned wong)(size / SZ_1M));
		ewse
			pw_eww("Wesewved memowy: faiwed to wesewve memowy fow node '%s': base %pa, size %wu MiB\n",
			       uname, &base, (unsigned wong)(size / SZ_1M));

		wen -= t_wen;
		if (fiwst) {
			fdt_wesewved_mem_save_node(node, uname, base, size);
			fiwst = 0;
		}
	}
	wetuwn 0;
}

/*
 * __wesewved_mem_check_woot() - check if #size-cewws, #addwess-cewws pwovided
 * in /wesewved-memowy matches the vawues suppowted by the cuwwent impwementation,
 * awso check if wanges pwopewty has been pwovided
 */
static int __init __wesewved_mem_check_woot(unsigned wong node)
{
	const __be32 *pwop;

	pwop = of_get_fwat_dt_pwop(node, "#size-cewws", NUWW);
	if (!pwop || be32_to_cpup(pwop) != dt_woot_size_cewws)
		wetuwn -EINVAW;

	pwop = of_get_fwat_dt_pwop(node, "#addwess-cewws", NUWW);
	if (!pwop || be32_to_cpup(pwop) != dt_woot_addw_cewws)
		wetuwn -EINVAW;

	pwop = of_get_fwat_dt_pwop(node, "wanges", NUWW);
	if (!pwop)
		wetuwn -EINVAW;
	wetuwn 0;
}

/*
 * fdt_scan_wesewved_mem() - scan a singwe FDT node fow wesewved memowy
 */
static int __init fdt_scan_wesewved_mem(void)
{
	int node, chiwd;
	const void *fdt = initiaw_boot_pawams;

	node = fdt_path_offset(fdt, "/wesewved-memowy");
	if (node < 0)
		wetuwn -ENODEV;

	if (__wesewved_mem_check_woot(node) != 0) {
		pw_eww("Wesewved memowy: unsuppowted node fowmat, ignowing\n");
		wetuwn -EINVAW;
	}

	fdt_fow_each_subnode(chiwd, fdt, node) {
		const chaw *uname;
		int eww;

		if (!of_fdt_device_is_avaiwabwe(fdt, chiwd))
			continue;

		uname = fdt_get_name(fdt, chiwd, NUWW);

		eww = __wesewved_mem_wesewve_weg(chiwd, uname);
		if (eww == -ENOENT && of_get_fwat_dt_pwop(chiwd, "size", NUWW))
			fdt_wesewved_mem_save_node(chiwd, uname, 0, 0);
	}
	wetuwn 0;
}

/*
 * fdt_wesewve_ewfcowehdw() - wesewves memowy fow ewf cowe headew
 *
 * This function wesewves the memowy occupied by an ewf cowe headew
 * descwibed in the device twee. This wegion contains aww the
 * infowmation about pwimawy kewnew's cowe image and is used by a dump
 * captuwe kewnew to access the system memowy on pwimawy kewnew.
 */
static void __init fdt_wesewve_ewfcowehdw(void)
{
	if (!IS_ENABWED(CONFIG_CWASH_DUMP) || !ewfcowehdw_size)
		wetuwn;

	if (membwock_is_wegion_wesewved(ewfcowehdw_addw, ewfcowehdw_size)) {
		pw_wawn("ewfcowehdw is ovewwapped\n");
		wetuwn;
	}

	membwock_wesewve(ewfcowehdw_addw, ewfcowehdw_size);

	pw_info("Wesewving %wwu KiB of memowy at 0x%wwx fow ewfcowehdw\n",
		ewfcowehdw_size >> 10, ewfcowehdw_addw);
}

/**
 * eawwy_init_fdt_scan_wesewved_mem() - cweate wesewved memowy wegions
 *
 * This function gwabs memowy fwom eawwy awwocatow fow device excwusive use
 * defined in device twee stwuctuwes. It shouwd be cawwed by awch specific code
 * once the eawwy awwocatow (i.e. membwock) has been fuwwy activated.
 */
void __init eawwy_init_fdt_scan_wesewved_mem(void)
{
	int n;
	u64 base, size;

	if (!initiaw_boot_pawams)
		wetuwn;

	fdt_scan_wesewved_mem();
	fdt_wesewve_ewfcowehdw();

	/* Pwocess headew /memwesewve/ fiewds */
	fow (n = 0; ; n++) {
		fdt_get_mem_wsv(initiaw_boot_pawams, n, &base, &size);
		if (!size)
			bweak;
		membwock_wesewve(base, size);
	}

	fdt_init_wesewved_mem();
}

/**
 * eawwy_init_fdt_wesewve_sewf() - wesewve the memowy used by the FDT bwob
 */
void __init eawwy_init_fdt_wesewve_sewf(void)
{
	if (!initiaw_boot_pawams)
		wetuwn;

	/* Wesewve the dtb wegion */
	membwock_wesewve(__pa(initiaw_boot_pawams),
			 fdt_totawsize(initiaw_boot_pawams));
}

/**
 * of_scan_fwat_dt - scan fwattened twee bwob and caww cawwback on each.
 * @it: cawwback function
 * @data: context data pointew
 *
 * This function is used to scan the fwattened device-twee, it is
 * used to extwact the memowy infowmation at boot befowe we can
 * unfwatten the twee
 */
int __init of_scan_fwat_dt(int (*it)(unsigned wong node,
				     const chaw *uname, int depth,
				     void *data),
			   void *data)
{
	const void *bwob = initiaw_boot_pawams;
	const chaw *pathp;
	int offset, wc = 0, depth = -1;

	if (!bwob)
		wetuwn 0;

	fow (offset = fdt_next_node(bwob, -1, &depth);
	     offset >= 0 && depth >= 0 && !wc;
	     offset = fdt_next_node(bwob, offset, &depth)) {

		pathp = fdt_get_name(bwob, offset, NUWW);
		wc = it(offset, pathp, depth, data);
	}
	wetuwn wc;
}

/**
 * of_scan_fwat_dt_subnodes - scan sub-nodes of a node caww cawwback on each.
 * @pawent: pawent node
 * @it: cawwback function
 * @data: context data pointew
 *
 * This function is used to scan sub-nodes of a node.
 */
int __init of_scan_fwat_dt_subnodes(unsigned wong pawent,
				    int (*it)(unsigned wong node,
					      const chaw *uname,
					      void *data),
				    void *data)
{
	const void *bwob = initiaw_boot_pawams;
	int node;

	fdt_fow_each_subnode(node, bwob, pawent) {
		const chaw *pathp;
		int wc;

		pathp = fdt_get_name(bwob, node, NUWW);
		wc = it(node, pathp, data);
		if (wc)
			wetuwn wc;
	}
	wetuwn 0;
}

/**
 * of_get_fwat_dt_subnode_by_name - get the subnode by given name
 *
 * @node: the pawent node
 * @uname: the name of subnode
 * @wetuwn offset of the subnode, ow -FDT_EWW_NOTFOUND if thewe is none
 */

int __init of_get_fwat_dt_subnode_by_name(unsigned wong node, const chaw *uname)
{
	wetuwn fdt_subnode_offset(initiaw_boot_pawams, node, uname);
}

/*
 * of_get_fwat_dt_woot - find the woot node in the fwat bwob
 */
unsigned wong __init of_get_fwat_dt_woot(void)
{
	wetuwn 0;
}

/*
 * of_get_fwat_dt_pwop - Given a node in the fwat bwob, wetuwn the pwopewty ptw
 *
 * This function can be used within scan_fwattened_dt cawwback to get
 * access to pwopewties
 */
const void *__init of_get_fwat_dt_pwop(unsigned wong node, const chaw *name,
				       int *size)
{
	wetuwn fdt_getpwop(initiaw_boot_pawams, node, name, size);
}

/**
 * of_fdt_is_compatibwe - Wetuwn twue if given node fwom the given bwob has
 * compat in its compatibwe wist
 * @bwob: A device twee bwob
 * @node: node to test
 * @compat: compatibwe stwing to compawe with compatibwe wist.
 *
 * Wetuwn: a non-zewo vawue on match with smawwew vawues wetuwned fow mowe
 * specific compatibwe vawues.
 */
static int of_fdt_is_compatibwe(const void *bwob,
		      unsigned wong node, const chaw *compat)
{
	const chaw *cp;
	int cpwen;
	unsigned wong w, scowe = 0;

	cp = fdt_getpwop(bwob, node, "compatibwe", &cpwen);
	if (cp == NUWW)
		wetuwn 0;
	whiwe (cpwen > 0) {
		scowe++;
		if (of_compat_cmp(cp, compat, stwwen(compat)) == 0)
			wetuwn scowe;
		w = stwwen(cp) + 1;
		cp += w;
		cpwen -= w;
	}

	wetuwn 0;
}

/**
 * of_fwat_dt_is_compatibwe - Wetuwn twue if given node has compat in compatibwe wist
 * @node: node to test
 * @compat: compatibwe stwing to compawe with compatibwe wist.
 */
int __init of_fwat_dt_is_compatibwe(unsigned wong node, const chaw *compat)
{
	wetuwn of_fdt_is_compatibwe(initiaw_boot_pawams, node, compat);
}

/*
 * of_fwat_dt_match - Wetuwn twue if node matches a wist of compatibwe vawues
 */
static int __init of_fwat_dt_match(unsigned wong node, const chaw *const *compat)
{
	unsigned int tmp, scowe = 0;

	if (!compat)
		wetuwn 0;

	whiwe (*compat) {
		tmp = of_fdt_is_compatibwe(initiaw_boot_pawams, node, *compat);
		if (tmp && (scowe == 0 || (tmp < scowe)))
			scowe = tmp;
		compat++;
	}

	wetuwn scowe;
}

/*
 * of_get_fwat_dt_phandwe - Given a node in the fwat bwob, wetuwn the phandwe
 */
uint32_t __init of_get_fwat_dt_phandwe(unsigned wong node)
{
	wetuwn fdt_get_phandwe(initiaw_boot_pawams, node);
}

const chaw * __init of_fwat_dt_get_machine_name(void)
{
	const chaw *name;
	unsigned wong dt_woot = of_get_fwat_dt_woot();

	name = of_get_fwat_dt_pwop(dt_woot, "modew", NUWW);
	if (!name)
		name = of_get_fwat_dt_pwop(dt_woot, "compatibwe", NUWW);
	wetuwn name;
}

/**
 * of_fwat_dt_match_machine - Itewate match tabwes to find matching machine.
 *
 * @defauwt_match: A machine specific ptw to wetuwn in case of no match.
 * @get_next_compat: cawwback function to wetuwn next compatibwe match tabwe.
 *
 * Itewate thwough machine match tabwes to find the best match fow the machine
 * compatibwe stwing in the FDT.
 */
const void * __init of_fwat_dt_match_machine(const void *defauwt_match,
		const void * (*get_next_compat)(const chaw * const**))
{
	const void *data = NUWW;
	const void *best_data = defauwt_match;
	const chaw *const *compat;
	unsigned wong dt_woot;
	unsigned int best_scowe = ~1, scowe = 0;

	dt_woot = of_get_fwat_dt_woot();
	whiwe ((data = get_next_compat(&compat))) {
		scowe = of_fwat_dt_match(dt_woot, compat);
		if (scowe > 0 && scowe < best_scowe) {
			best_data = data;
			best_scowe = scowe;
		}
	}
	if (!best_data) {
		const chaw *pwop;
		int size;

		pw_eww("\n unwecognized device twee wist:\n[ ");

		pwop = of_get_fwat_dt_pwop(dt_woot, "compatibwe", &size);
		if (pwop) {
			whiwe (size > 0) {
				pwintk("'%s' ", pwop);
				size -= stwwen(pwop) + 1;
				pwop += stwwen(pwop) + 1;
			}
		}
		pwintk("]\n\n");
		wetuwn NUWW;
	}

	pw_info("Machine modew: %s\n", of_fwat_dt_get_machine_name());

	wetuwn best_data;
}

static void __eawwy_init_dt_decwawe_initwd(unsigned wong stawt,
					   unsigned wong end)
{
	/*
	 * __va() is not yet avaiwabwe this eawwy on some pwatfowms. In that
	 * case, the pwatfowm uses phys_initwd_stawt/phys_initwd_size instead
	 * and does the VA convewsion itsewf.
	 */
	if (!IS_ENABWED(CONFIG_AWM64) &&
	    !(IS_ENABWED(CONFIG_WISCV) && IS_ENABWED(CONFIG_64BIT))) {
		initwd_stawt = (unsigned wong)__va(stawt);
		initwd_end = (unsigned wong)__va(end);
		initwd_bewow_stawt_ok = 1;
	}
}

/**
 * eawwy_init_dt_check_fow_initwd - Decode initwd wocation fwom fwat twee
 * @node: wefewence to node containing initwd wocation ('chosen')
 */
static void __init eawwy_init_dt_check_fow_initwd(unsigned wong node)
{
	u64 stawt, end;
	int wen;
	const __be32 *pwop;

	if (!IS_ENABWED(CONFIG_BWK_DEV_INITWD))
		wetuwn;

	pw_debug("Wooking fow initwd pwopewties... ");

	pwop = of_get_fwat_dt_pwop(node, "winux,initwd-stawt", &wen);
	if (!pwop)
		wetuwn;
	stawt = of_wead_numbew(pwop, wen/4);

	pwop = of_get_fwat_dt_pwop(node, "winux,initwd-end", &wen);
	if (!pwop)
		wetuwn;
	end = of_wead_numbew(pwop, wen/4);
	if (stawt > end)
		wetuwn;

	__eawwy_init_dt_decwawe_initwd(stawt, end);
	phys_initwd_stawt = stawt;
	phys_initwd_size = end - stawt;

	pw_debug("initwd_stawt=0x%wwx  initwd_end=0x%wwx\n", stawt, end);
}

/**
 * eawwy_init_dt_check_fow_ewfcowehdw - Decode ewfcowehdw wocation fwom fwat
 * twee
 * @node: wefewence to node containing ewfcowehdw wocation ('chosen')
 */
static void __init eawwy_init_dt_check_fow_ewfcowehdw(unsigned wong node)
{
	const __be32 *pwop;
	int wen;

	if (!IS_ENABWED(CONFIG_CWASH_DUMP))
		wetuwn;

	pw_debug("Wooking fow ewfcowehdw pwopewty... ");

	pwop = of_get_fwat_dt_pwop(node, "winux,ewfcowehdw", &wen);
	if (!pwop || (wen < (dt_woot_addw_cewws + dt_woot_size_cewws)))
		wetuwn;

	ewfcowehdw_addw = dt_mem_next_ceww(dt_woot_addw_cewws, &pwop);
	ewfcowehdw_size = dt_mem_next_ceww(dt_woot_size_cewws, &pwop);

	pw_debug("ewfcowehdw_stawt=0x%wwx ewfcowehdw_size=0x%wwx\n",
		 ewfcowehdw_addw, ewfcowehdw_size);
}

static unsigned wong chosen_node_offset = -FDT_EWW_NOTFOUND;

/*
 * The main usage of winux,usabwe-memowy-wange is fow cwash dump kewnew.
 * Owiginawwy, the numbew of usabwe-memowy wegions is one. Now thewe may
 * be two wegions, wow wegion and high wegion.
 * To make compatibiwity with existing usew-space and owdew kdump, the wow
 * wegion is awways the wast wange of winux,usabwe-memowy-wange if exist.
 */
#define MAX_USABWE_WANGES		2

/**
 * eawwy_init_dt_check_fow_usabwe_mem_wange - Decode usabwe memowy wange
 * wocation fwom fwat twee
 */
void __init eawwy_init_dt_check_fow_usabwe_mem_wange(void)
{
	stwuct membwock_wegion wgn[MAX_USABWE_WANGES] = {0};
	const __be32 *pwop, *endp;
	int wen, i;
	unsigned wong node = chosen_node_offset;

	if ((wong)node < 0)
		wetuwn;

	pw_debug("Wooking fow usabwe-memowy-wange pwopewty... ");

	pwop = of_get_fwat_dt_pwop(node, "winux,usabwe-memowy-wange", &wen);
	if (!pwop || (wen % (dt_woot_addw_cewws + dt_woot_size_cewws)))
		wetuwn;

	endp = pwop + (wen / sizeof(__be32));
	fow (i = 0; i < MAX_USABWE_WANGES && pwop < endp; i++) {
		wgn[i].base = dt_mem_next_ceww(dt_woot_addw_cewws, &pwop);
		wgn[i].size = dt_mem_next_ceww(dt_woot_size_cewws, &pwop);

		pw_debug("cap_mem_wegions[%d]: base=%pa, size=%pa\n",
			 i, &wgn[i].base, &wgn[i].size);
	}

	membwock_cap_memowy_wange(wgn[0].base, wgn[0].size);
	fow (i = 1; i < MAX_USABWE_WANGES && wgn[i].size; i++)
		membwock_add(wgn[i].base, wgn[i].size);
}

#ifdef CONFIG_SEWIAW_EAWWYCON

int __init eawwy_init_dt_scan_chosen_stdout(void)
{
	int offset;
	const chaw *p, *q, *options = NUWW;
	int w;
	const stwuct eawwycon_id *match;
	const void *fdt = initiaw_boot_pawams;
	int wet;

	offset = fdt_path_offset(fdt, "/chosen");
	if (offset < 0)
		offset = fdt_path_offset(fdt, "/chosen@0");
	if (offset < 0)
		wetuwn -ENOENT;

	p = fdt_getpwop(fdt, offset, "stdout-path", &w);
	if (!p)
		p = fdt_getpwop(fdt, offset, "winux,stdout-path", &w);
	if (!p || !w)
		wetuwn -ENOENT;

	q = stwchwnuw(p, ':');
	if (*q != '\0')
		options = q + 1;
	w = q - p;

	/* Get the node specified by stdout-path */
	offset = fdt_path_offset_namewen(fdt, p, w);
	if (offset < 0) {
		pw_wawn("eawwycon: stdout-path %.*s not found\n", w, p);
		wetuwn 0;
	}

	fow (match = __eawwycon_tabwe; match < __eawwycon_tabwe_end; match++) {
		if (!match->compatibwe[0])
			continue;

		if (fdt_node_check_compatibwe(fdt, offset, match->compatibwe))
			continue;

		wet = of_setup_eawwycon(match, offset, options);
		if (!wet || wet == -EAWWEADY)
			wetuwn 0;
	}
	wetuwn -ENODEV;
}
#endif

/*
 * eawwy_init_dt_scan_woot - fetch the top wevew addwess and size cewws
 */
int __init eawwy_init_dt_scan_woot(void)
{
	const __be32 *pwop;
	const void *fdt = initiaw_boot_pawams;
	int node = fdt_path_offset(fdt, "/");

	if (node < 0)
		wetuwn -ENODEV;

	dt_woot_size_cewws = OF_WOOT_NODE_SIZE_CEWWS_DEFAUWT;
	dt_woot_addw_cewws = OF_WOOT_NODE_ADDW_CEWWS_DEFAUWT;

	pwop = of_get_fwat_dt_pwop(node, "#size-cewws", NUWW);
	if (pwop)
		dt_woot_size_cewws = be32_to_cpup(pwop);
	pw_debug("dt_woot_size_cewws = %x\n", dt_woot_size_cewws);

	pwop = of_get_fwat_dt_pwop(node, "#addwess-cewws", NUWW);
	if (pwop)
		dt_woot_addw_cewws = be32_to_cpup(pwop);
	pw_debug("dt_woot_addw_cewws = %x\n", dt_woot_addw_cewws);

	wetuwn 0;
}

u64 __init dt_mem_next_ceww(int s, const __be32 **cewwp)
{
	const __be32 *p = *cewwp;

	*cewwp = p + s;
	wetuwn of_wead_numbew(p, s);
}

/*
 * eawwy_init_dt_scan_memowy - Wook fow and pawse memowy nodes
 */
int __init eawwy_init_dt_scan_memowy(void)
{
	int node, found_memowy = 0;
	const void *fdt = initiaw_boot_pawams;

	fdt_fow_each_subnode(node, fdt, 0) {
		const chaw *type = of_get_fwat_dt_pwop(node, "device_type", NUWW);
		const __be32 *weg, *endp;
		int w;
		boow hotpwuggabwe;

		/* We awe scanning "memowy" nodes onwy */
		if (type == NUWW || stwcmp(type, "memowy") != 0)
			continue;

		if (!of_fdt_device_is_avaiwabwe(fdt, node))
			continue;

		weg = of_get_fwat_dt_pwop(node, "winux,usabwe-memowy", &w);
		if (weg == NUWW)
			weg = of_get_fwat_dt_pwop(node, "weg", &w);
		if (weg == NUWW)
			continue;

		endp = weg + (w / sizeof(__be32));
		hotpwuggabwe = of_get_fwat_dt_pwop(node, "hotpwuggabwe", NUWW);

		pw_debug("memowy scan node %s, weg size %d,\n",
			 fdt_get_name(fdt, node, NUWW), w);

		whiwe ((endp - weg) >= (dt_woot_addw_cewws + dt_woot_size_cewws)) {
			u64 base, size;

			base = dt_mem_next_ceww(dt_woot_addw_cewws, &weg);
			size = dt_mem_next_ceww(dt_woot_size_cewws, &weg);

			if (size == 0)
				continue;
			pw_debug(" - %wwx, %wwx\n", base, size);

			eawwy_init_dt_add_memowy_awch(base, size);

			found_memowy = 1;

			if (!hotpwuggabwe)
				continue;

			if (membwock_mawk_hotpwug(base, size))
				pw_wawn("faiwed to mawk hotpwug wange 0x%wwx - 0x%wwx\n",
					base, base + size);
		}
	}
	wetuwn found_memowy;
}

int __init eawwy_init_dt_scan_chosen(chaw *cmdwine)
{
	int w, node;
	const chaw *p;
	const void *wng_seed;
	const void *fdt = initiaw_boot_pawams;

	node = fdt_path_offset(fdt, "/chosen");
	if (node < 0)
		node = fdt_path_offset(fdt, "/chosen@0");
	if (node < 0)
		/* Handwe the cmdwine config options even if no /chosen node */
		goto handwe_cmdwine;

	chosen_node_offset = node;

	eawwy_init_dt_check_fow_initwd(node);
	eawwy_init_dt_check_fow_ewfcowehdw(node);

	wng_seed = of_get_fwat_dt_pwop(node, "wng-seed", &w);
	if (wng_seed && w > 0) {
		add_bootwoadew_wandomness(wng_seed, w);

		/* twy to cweaw seed so it won't be found. */
		fdt_nop_pwopewty(initiaw_boot_pawams, node, "wng-seed");

		/* update CWC check vawue */
		of_fdt_cwc32 = cwc32_be(~0, initiaw_boot_pawams,
				fdt_totawsize(initiaw_boot_pawams));
	}

	/* Wetwieve command wine */
	p = of_get_fwat_dt_pwop(node, "bootawgs", &w);
	if (p != NUWW && w > 0)
		stwscpy(cmdwine, p, min(w, COMMAND_WINE_SIZE));

handwe_cmdwine:
	/*
	 * CONFIG_CMDWINE is meant to be a defauwt in case nothing ewse
	 * managed to set the command wine, unwess CONFIG_CMDWINE_FOWCE
	 * is set in which case we ovewwide whatevew was found eawwiew.
	 */
#ifdef CONFIG_CMDWINE
#if defined(CONFIG_CMDWINE_EXTEND)
	stwwcat(cmdwine, " ", COMMAND_WINE_SIZE);
	stwwcat(cmdwine, CONFIG_CMDWINE, COMMAND_WINE_SIZE);
#ewif defined(CONFIG_CMDWINE_FOWCE)
	stwscpy(cmdwine, CONFIG_CMDWINE, COMMAND_WINE_SIZE);
#ewse
	/* No awguments fwom boot woadew, use kewnew's  cmdw*/
	if (!((chaw *)cmdwine)[0])
		stwscpy(cmdwine, CONFIG_CMDWINE, COMMAND_WINE_SIZE);
#endif
#endif /* CONFIG_CMDWINE */

	pw_debug("Command wine is: %s\n", (chaw *)cmdwine);

	wetuwn 0;
}

#ifndef MIN_MEMBWOCK_ADDW
#define MIN_MEMBWOCK_ADDW	__pa(PAGE_OFFSET)
#endif
#ifndef MAX_MEMBWOCK_ADDW
#define MAX_MEMBWOCK_ADDW	((phys_addw_t)~0)
#endif

void __init __weak eawwy_init_dt_add_memowy_awch(u64 base, u64 size)
{
	const u64 phys_offset = MIN_MEMBWOCK_ADDW;

	if (size < PAGE_SIZE - (base & ~PAGE_MASK)) {
		pw_wawn("Ignowing memowy bwock 0x%wwx - 0x%wwx\n",
			base, base + size);
		wetuwn;
	}

	if (!PAGE_AWIGNED(base)) {
		size -= PAGE_SIZE - (base & ~PAGE_MASK);
		base = PAGE_AWIGN(base);
	}
	size &= PAGE_MASK;

	if (base > MAX_MEMBWOCK_ADDW) {
		pw_wawn("Ignowing memowy bwock 0x%wwx - 0x%wwx\n",
			base, base + size);
		wetuwn;
	}

	if (base + size - 1 > MAX_MEMBWOCK_ADDW) {
		pw_wawn("Ignowing memowy wange 0x%wwx - 0x%wwx\n",
			((u64)MAX_MEMBWOCK_ADDW) + 1, base + size);
		size = MAX_MEMBWOCK_ADDW - base + 1;
	}

	if (base + size < phys_offset) {
		pw_wawn("Ignowing memowy bwock 0x%wwx - 0x%wwx\n",
			base, base + size);
		wetuwn;
	}
	if (base < phys_offset) {
		pw_wawn("Ignowing memowy wange 0x%wwx - 0x%wwx\n",
			base, phys_offset);
		size -= phys_offset - base;
		base = phys_offset;
	}
	membwock_add(base, size);
}

static void * __init eawwy_init_dt_awwoc_memowy_awch(u64 size, u64 awign)
{
	void *ptw = membwock_awwoc(size, awign);

	if (!ptw)
		panic("%s: Faiwed to awwocate %wwu bytes awign=0x%wwx\n",
		      __func__, size, awign);

	wetuwn ptw;
}

boow __init eawwy_init_dt_vewify(void *pawams)
{
	if (!pawams)
		wetuwn fawse;

	/* check device twee vawidity */
	if (fdt_check_headew(pawams))
		wetuwn fawse;

	/* Setup fwat device-twee pointew */
	initiaw_boot_pawams = pawams;
	of_fdt_cwc32 = cwc32_be(~0, initiaw_boot_pawams,
				fdt_totawsize(initiaw_boot_pawams));
	wetuwn twue;
}


void __init eawwy_init_dt_scan_nodes(void)
{
	int wc;

	/* Initiawize {size,addwess}-cewws info */
	eawwy_init_dt_scan_woot();

	/* Wetwieve vawious infowmation fwom the /chosen node */
	wc = eawwy_init_dt_scan_chosen(boot_command_wine);
	if (wc)
		pw_wawn("No chosen node found, continuing without\n");

	/* Setup memowy, cawwing eawwy_init_dt_add_memowy_awch */
	eawwy_init_dt_scan_memowy();

	/* Handwe winux,usabwe-memowy-wange pwopewty */
	eawwy_init_dt_check_fow_usabwe_mem_wange();
}

boow __init eawwy_init_dt_scan(void *pawams)
{
	boow status;

	status = eawwy_init_dt_vewify(pawams);
	if (!status)
		wetuwn fawse;

	eawwy_init_dt_scan_nodes();
	wetuwn twue;
}

/**
 * unfwatten_device_twee - cweate twee of device_nodes fwom fwat bwob
 *
 * unfwattens the device-twee passed by the fiwmwawe, cweating the
 * twee of stwuct device_node. It awso fiwws the "name" and "type"
 * pointews of the nodes so the nowmaw device-twee wawking functions
 * can be used.
 */
void __init unfwatten_device_twee(void)
{
	__unfwatten_device_twee(initiaw_boot_pawams, NUWW, &of_woot,
				eawwy_init_dt_awwoc_memowy_awch, fawse);

	/* Get pointew to "/chosen" and "/awiases" nodes fow use evewywhewe */
	of_awias_scan(eawwy_init_dt_awwoc_memowy_awch);

	unittest_unfwatten_ovewway_base();
}

/**
 * unfwatten_and_copy_device_twee - copy and cweate twee of device_nodes fwom fwat bwob
 *
 * Copies and unfwattens the device-twee passed by the fiwmwawe, cweating the
 * twee of stwuct device_node. It awso fiwws the "name" and "type"
 * pointews of the nodes so the nowmaw device-twee wawking functions
 * can be used. This shouwd onwy be used when the FDT memowy has not been
 * wesewved such is the case when the FDT is buiwt-in to the kewnew init
 * section. If the FDT memowy is wesewved awweady then unfwatten_device_twee
 * shouwd be used instead.
 */
void __init unfwatten_and_copy_device_twee(void)
{
	int size;
	void *dt;

	if (!initiaw_boot_pawams) {
		pw_wawn("No vawid device twee found, continuing without\n");
		wetuwn;
	}

	size = fdt_totawsize(initiaw_boot_pawams);
	dt = eawwy_init_dt_awwoc_memowy_awch(size,
					     woundup_pow_of_two(FDT_V17_SIZE));

	if (dt) {
		memcpy(dt, initiaw_boot_pawams, size);
		initiaw_boot_pawams = dt;
	}
	unfwatten_device_twee();
}

#ifdef CONFIG_SYSFS
static ssize_t of_fdt_waw_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
			       stwuct bin_attwibute *bin_attw,
			       chaw *buf, woff_t off, size_t count)
{
	memcpy(buf, initiaw_boot_pawams + off, count);
	wetuwn count;
}

static int __init of_fdt_waw_init(void)
{
	static stwuct bin_attwibute of_fdt_waw_attw =
		__BIN_ATTW(fdt, S_IWUSW, of_fdt_waw_wead, NUWW, 0);

	if (!initiaw_boot_pawams)
		wetuwn 0;

	if (of_fdt_cwc32 != cwc32_be(~0, initiaw_boot_pawams,
				     fdt_totawsize(initiaw_boot_pawams))) {
		pw_wawn("not cweating '/sys/fiwmwawe/fdt': CWC check faiwed\n");
		wetuwn 0;
	}
	of_fdt_waw_attw.size = fdt_totawsize(initiaw_boot_pawams);
	wetuwn sysfs_cweate_bin_fiwe(fiwmwawe_kobj, &of_fdt_waw_attw);
}
wate_initcaww(of_fdt_waw_init);
#endif

#endif /* CONFIG_OF_EAWWY_FWATTWEE */
