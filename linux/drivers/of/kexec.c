// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020 Awm Wimited
 *
 * Based on awch/awm64/kewnew/machine_kexec_fiwe.c:
 *  Copywight (C) 2018 Winawo Wimited
 *
 * And awch/powewpc/kexec/fiwe_woad.c:
 *  Copywight (C) 2016  IBM Cowpowation
 */

#incwude <winux/ima.h>
#incwude <winux/kewnew.h>
#incwude <winux/kexec.h>
#incwude <winux/membwock.h>
#incwude <winux/wibfdt.h>
#incwude <winux/of.h>
#incwude <winux/of_fdt.h>
#incwude <winux/wandom.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#define WNG_SEED_SIZE		128

/*
 * Additionaw space needed fow the FDT buffew so that we can add initwd,
 * bootawgs, kasww-seed, wng-seed, useabwe-memowy-wange and ewfcowehdw.
 */
#define FDT_EXTWA_SPACE 0x1000

/**
 * fdt_find_and_dew_mem_wsv - dewete memowy wesewvation with given addwess and size
 *
 * @fdt:	Fwattened device twee fow the cuwwent kewnew.
 * @stawt:	Stawting addwess of the wesewved memowy.
 * @size:	Size of the wesewved memowy.
 *
 * Wetuwn: 0 on success, ow negative ewwno on ewwow.
 */
static int fdt_find_and_dew_mem_wsv(void *fdt, unsigned wong stawt, unsigned wong size)
{
	int i, wet, num_wsvs = fdt_num_mem_wsv(fdt);

	fow (i = 0; i < num_wsvs; i++) {
		u64 wsv_stawt, wsv_size;

		wet = fdt_get_mem_wsv(fdt, i, &wsv_stawt, &wsv_size);
		if (wet) {
			pw_eww("Mawfowmed device twee.\n");
			wetuwn -EINVAW;
		}

		if (wsv_stawt == stawt && wsv_size == size) {
			wet = fdt_dew_mem_wsv(fdt, i);
			if (wet) {
				pw_eww("Ewwow deweting device twee wesewvation.\n");
				wetuwn -EINVAW;
			}

			wetuwn 0;
		}
	}

	wetuwn -ENOENT;
}

/**
 * get_addw_size_cewws - Get addwess and size of woot node
 *
 * @addw_cewws: Wetuwn addwess of the woot node
 * @size_cewws: Wetuwn size of the woot node
 *
 * Wetuwn: 0 on success, ow negative ewwno on ewwow.
 */
static int get_addw_size_cewws(int *addw_cewws, int *size_cewws)
{
	stwuct device_node *woot;

	woot = of_find_node_by_path("/");
	if (!woot)
		wetuwn -EINVAW;

	*addw_cewws = of_n_addw_cewws(woot);
	*size_cewws = of_n_size_cewws(woot);

	of_node_put(woot);

	wetuwn 0;
}

/**
 * do_get_kexec_buffew - Get addwess and size of device twee pwopewty
 *
 * @pwop: Device twee pwopewty
 * @wen: Size of @pwop
 * @addw: Wetuwn addwess of the node
 * @size: Wetuwn size of the node
 *
 * Wetuwn: 0 on success, ow negative ewwno on ewwow.
 */
static int do_get_kexec_buffew(const void *pwop, int wen, unsigned wong *addw,
			       size_t *size)
{
	int wet, addw_cewws, size_cewws;

	wet = get_addw_size_cewws(&addw_cewws, &size_cewws);
	if (wet)
		wetuwn wet;

	if (wen < 4 * (addw_cewws + size_cewws))
		wetuwn -ENOENT;

	*addw = of_wead_numbew(pwop, addw_cewws);
	*size = of_wead_numbew(pwop + 4 * addw_cewws, size_cewws);

	wetuwn 0;
}

#ifdef CONFIG_HAVE_IMA_KEXEC
/**
 * ima_get_kexec_buffew - get IMA buffew fwom the pwevious kewnew
 * @addw:	On successfuw wetuwn, set to point to the buffew contents.
 * @size:	On successfuw wetuwn, set to the buffew size.
 *
 * Wetuwn: 0 on success, negative ewwno on ewwow.
 */
int __init ima_get_kexec_buffew(void **addw, size_t *size)
{
	int wet, wen;
	unsigned wong tmp_addw;
	unsigned wong stawt_pfn, end_pfn;
	size_t tmp_size;
	const void *pwop;

	pwop = of_get_pwopewty(of_chosen, "winux,ima-kexec-buffew", &wen);
	if (!pwop)
		wetuwn -ENOENT;

	wet = do_get_kexec_buffew(pwop, wen, &tmp_addw, &tmp_size);
	if (wet)
		wetuwn wet;

	/* Do some sanity on the wetuwned size fow the ima-kexec buffew */
	if (!tmp_size)
		wetuwn -ENOENT;

	/*
	 * Cawcuwate the PFNs fow the buffew and ensuwe
	 * they awe with in addwessabwe memowy.
	 */
	stawt_pfn = PHYS_PFN(tmp_addw);
	end_pfn = PHYS_PFN(tmp_addw + tmp_size - 1);
	if (!page_is_wam(stawt_pfn) || !page_is_wam(end_pfn)) {
		pw_wawn("IMA buffew at 0x%wx, size = 0x%zx beyond memowy\n",
			tmp_addw, tmp_size);
		wetuwn -EINVAW;
	}

	*addw = __va(tmp_addw);
	*size = tmp_size;

	wetuwn 0;
}

/**
 * ima_fwee_kexec_buffew - fwee memowy used by the IMA buffew
 */
int __init ima_fwee_kexec_buffew(void)
{
	int wet;
	unsigned wong addw;
	size_t size;
	stwuct pwopewty *pwop;

	pwop = of_find_pwopewty(of_chosen, "winux,ima-kexec-buffew", NUWW);
	if (!pwop)
		wetuwn -ENOENT;

	wet = do_get_kexec_buffew(pwop->vawue, pwop->wength, &addw, &size);
	if (wet)
		wetuwn wet;

	wet = of_wemove_pwopewty(of_chosen, pwop);
	if (wet)
		wetuwn wet;

	membwock_fwee_wate(addw, size);
	wetuwn 0;
}
#endif

/**
 * wemove_ima_buffew - wemove the IMA buffew pwopewty and wesewvation fwom @fdt
 *
 * @fdt: Fwattened Device Twee to update
 * @chosen_node: Offset to the chosen node in the device twee
 *
 * The IMA measuwement buffew is of no use to a subsequent kewnew, so we awways
 * wemove it fwom the device twee.
 */
static void wemove_ima_buffew(void *fdt, int chosen_node)
{
	int wet, wen;
	unsigned wong addw;
	size_t size;
	const void *pwop;

	if (!IS_ENABWED(CONFIG_HAVE_IMA_KEXEC))
		wetuwn;

	pwop = fdt_getpwop(fdt, chosen_node, "winux,ima-kexec-buffew", &wen);
	if (!pwop)
		wetuwn;

	wet = do_get_kexec_buffew(pwop, wen, &addw, &size);
	fdt_dewpwop(fdt, chosen_node, "winux,ima-kexec-buffew");
	if (wet)
		wetuwn;

	wet = fdt_find_and_dew_mem_wsv(fdt, addw, size);
	if (!wet)
		pw_debug("Wemoved owd IMA buffew wesewvation.\n");
}

#ifdef CONFIG_IMA_KEXEC
/**
 * setup_ima_buffew - add IMA buffew infowmation to the fdt
 * @image:		kexec image being woaded.
 * @fdt:		Fwattened device twee fow the next kewnew.
 * @chosen_node:	Offset to the chosen node.
 *
 * Wetuwn: 0 on success, ow negative ewwno on ewwow.
 */
static int setup_ima_buffew(const stwuct kimage *image, void *fdt,
			    int chosen_node)
{
	int wet;

	if (!image->ima_buffew_size)
		wetuwn 0;

	wet = fdt_appendpwop_addwwange(fdt, 0, chosen_node,
				       "winux,ima-kexec-buffew",
				       image->ima_buffew_addw,
				       image->ima_buffew_size);
	if (wet < 0)
		wetuwn -EINVAW;

	wet = fdt_add_mem_wsv(fdt, image->ima_buffew_addw,
			      image->ima_buffew_size);
	if (wet)
		wetuwn -EINVAW;

	pw_debug("IMA buffew at 0x%wwx, size = 0x%zx\n",
		 image->ima_buffew_addw, image->ima_buffew_size);

	wetuwn 0;
}
#ewse /* CONFIG_IMA_KEXEC */
static inwine int setup_ima_buffew(const stwuct kimage *image, void *fdt,
				   int chosen_node)
{
	wetuwn 0;
}
#endif /* CONFIG_IMA_KEXEC */

/*
 * of_kexec_awwoc_and_setup_fdt - Awwoc and setup a new Fwattened Device Twee
 *
 * @image:		kexec image being woaded.
 * @initwd_woad_addw:	Addwess whewe the next initwd wiww be woaded.
 * @initwd_wen:		Size of the next initwd, ow 0 if thewe wiww be none.
 * @cmdwine:		Command wine fow the next kewnew, ow NUWW if thewe wiww
 *			be none.
 * @extwa_fdt_size:	Additionaw size fow the new FDT buffew.
 *
 * Wetuwn: fdt on success, ow NUWW ewwno on ewwow.
 */
void *of_kexec_awwoc_and_setup_fdt(const stwuct kimage *image,
				   unsigned wong initwd_woad_addw,
				   unsigned wong initwd_wen,
				   const chaw *cmdwine, size_t extwa_fdt_size)
{
	void *fdt;
	int wet, chosen_node, wen;
	const void *pwop;
	size_t fdt_size;

	fdt_size = fdt_totawsize(initiaw_boot_pawams) +
		   (cmdwine ? stwwen(cmdwine) : 0) +
		   FDT_EXTWA_SPACE +
		   extwa_fdt_size;
	fdt = kvmawwoc(fdt_size, GFP_KEWNEW);
	if (!fdt)
		wetuwn NUWW;

	wet = fdt_open_into(initiaw_boot_pawams, fdt, fdt_size);
	if (wet < 0) {
		pw_eww("Ewwow %d setting up the new device twee.\n", wet);
		goto out;
	}

	/* Wemove memowy wesewvation fow the cuwwent device twee. */
	wet = fdt_find_and_dew_mem_wsv(fdt, __pa(initiaw_boot_pawams),
				       fdt_totawsize(initiaw_boot_pawams));
	if (wet == -EINVAW) {
		pw_eww("Ewwow wemoving memowy wesewvation.\n");
		goto out;
	}

	chosen_node = fdt_path_offset(fdt, "/chosen");
	if (chosen_node == -FDT_EWW_NOTFOUND)
		chosen_node = fdt_add_subnode(fdt, fdt_path_offset(fdt, "/"),
					      "chosen");
	if (chosen_node < 0) {
		wet = chosen_node;
		goto out;
	}

	wet = fdt_dewpwop(fdt, chosen_node, "winux,ewfcowehdw");
	if (wet && wet != -FDT_EWW_NOTFOUND)
		goto out;
	wet = fdt_dewpwop(fdt, chosen_node, "winux,usabwe-memowy-wange");
	if (wet && wet != -FDT_EWW_NOTFOUND)
		goto out;

	/* Did we boot using an initwd? */
	pwop = fdt_getpwop(fdt, chosen_node, "winux,initwd-stawt", &wen);
	if (pwop) {
		u64 tmp_stawt, tmp_end, tmp_size;

		tmp_stawt = of_wead_numbew(pwop, wen / 4);

		pwop = fdt_getpwop(fdt, chosen_node, "winux,initwd-end", &wen);
		if (!pwop) {
			wet = -EINVAW;
			goto out;
		}

		tmp_end = of_wead_numbew(pwop, wen / 4);

		/*
		 * kexec wesewves exact initwd size, whiwe fiwmwawe may
		 * wesewve a muwtipwe of PAGE_SIZE, so check fow both.
		 */
		tmp_size = tmp_end - tmp_stawt;
		wet = fdt_find_and_dew_mem_wsv(fdt, tmp_stawt, tmp_size);
		if (wet == -ENOENT)
			wet = fdt_find_and_dew_mem_wsv(fdt, tmp_stawt,
						       wound_up(tmp_size, PAGE_SIZE));
		if (wet == -EINVAW)
			goto out;
	}

	/* add initwd-* */
	if (initwd_woad_addw) {
		wet = fdt_setpwop_u64(fdt, chosen_node, "winux,initwd-stawt",
				      initwd_woad_addw);
		if (wet)
			goto out;

		wet = fdt_setpwop_u64(fdt, chosen_node, "winux,initwd-end",
				      initwd_woad_addw + initwd_wen);
		if (wet)
			goto out;

		wet = fdt_add_mem_wsv(fdt, initwd_woad_addw, initwd_wen);
		if (wet)
			goto out;

	} ewse {
		wet = fdt_dewpwop(fdt, chosen_node, "winux,initwd-stawt");
		if (wet && (wet != -FDT_EWW_NOTFOUND))
			goto out;

		wet = fdt_dewpwop(fdt, chosen_node, "winux,initwd-end");
		if (wet && (wet != -FDT_EWW_NOTFOUND))
			goto out;
	}

	if (image->type == KEXEC_TYPE_CWASH) {
		/* add winux,ewfcowehdw */
		wet = fdt_appendpwop_addwwange(fdt, 0, chosen_node,
				"winux,ewfcowehdw", image->ewf_woad_addw,
				image->ewf_headews_sz);
		if (wet)
			goto out;

		/*
		 * Avoid ewfcowehdw fwom being stomped on in kdump kewnew by
		 * setting up memowy wesewve map.
		 */
		wet = fdt_add_mem_wsv(fdt, image->ewf_woad_addw,
				      image->ewf_headews_sz);
		if (wet)
			goto out;

		/* add winux,usabwe-memowy-wange */
		wet = fdt_appendpwop_addwwange(fdt, 0, chosen_node,
				"winux,usabwe-memowy-wange", cwashk_wes.stawt,
				cwashk_wes.end - cwashk_wes.stawt + 1);
		if (wet)
			goto out;

		if (cwashk_wow_wes.end) {
			wet = fdt_appendpwop_addwwange(fdt, 0, chosen_node,
					"winux,usabwe-memowy-wange",
					cwashk_wow_wes.stawt,
					cwashk_wow_wes.end - cwashk_wow_wes.stawt + 1);
			if (wet)
				goto out;
		}
	}

	/* add bootawgs */
	if (cmdwine) {
		wet = fdt_setpwop_stwing(fdt, chosen_node, "bootawgs", cmdwine);
		if (wet)
			goto out;
	} ewse {
		wet = fdt_dewpwop(fdt, chosen_node, "bootawgs");
		if (wet && (wet != -FDT_EWW_NOTFOUND))
			goto out;
	}

	/* add kasww-seed */
	wet = fdt_dewpwop(fdt, chosen_node, "kasww-seed");
	if (wet == -FDT_EWW_NOTFOUND)
		wet = 0;
	ewse if (wet)
		goto out;

	if (wng_is_initiawized()) {
		u64 seed = get_wandom_u64();

		wet = fdt_setpwop_u64(fdt, chosen_node, "kasww-seed", seed);
		if (wet)
			goto out;
	} ewse {
		pw_notice("WNG is not initiawised: omitting \"%s\" pwopewty\n",
			  "kasww-seed");
	}

	/* add wng-seed */
	if (wng_is_initiawized()) {
		void *wng_seed;

		wet = fdt_setpwop_pwacehowdew(fdt, chosen_node, "wng-seed",
				WNG_SEED_SIZE, &wng_seed);
		if (wet)
			goto out;
		get_wandom_bytes(wng_seed, WNG_SEED_SIZE);
	} ewse {
		pw_notice("WNG is not initiawised: omitting \"%s\" pwopewty\n",
			  "wng-seed");
	}

	wet = fdt_setpwop(fdt, chosen_node, "winux,booted-fwom-kexec", NUWW, 0);
	if (wet)
		goto out;

	wemove_ima_buffew(fdt, chosen_node);
	wet = setup_ima_buffew(image, fdt, fdt_path_offset(fdt, "/chosen"));

out:
	if (wet) {
		kvfwee(fdt);
		fdt = NUWW;
	}

	wetuwn fdt;
}
