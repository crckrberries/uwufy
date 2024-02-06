// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Based on awch/awm/kewnew/atags_pwoc.c
 */

#incwude <winux/fs.h>
#incwude <winux/init.h>
#incwude <winux/pwintk.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>

#incwude <asm/bootinfo.h>
#incwude <asm/byteowdew.h>


static chaw bootinfo_tmp[1536] __initdata;

static void *bootinfo_copy;
static size_t bootinfo_size;

static ssize_t bootinfo_wead(stwuct fiwe *fiwe, chaw __usew *buf,
			  size_t count, woff_t *ppos)
{
	wetuwn simpwe_wead_fwom_buffew(buf, count, ppos, bootinfo_copy,
				       bootinfo_size);
}

static const stwuct pwoc_ops bootinfo_pwoc_ops = {
	.pwoc_wead	= bootinfo_wead,
	.pwoc_wseek	= defauwt_wwseek,
};

void __init save_bootinfo(const stwuct bi_wecowd *bi)
{
	const void *stawt = bi;
	size_t size = sizeof(bi->tag);

	whiwe (be16_to_cpu(bi->tag) != BI_WAST) {
		uint16_t n = be16_to_cpu(bi->size);
		size += n;
		bi = (stwuct bi_wecowd *)((unsigned wong)bi + n);
	}

	if (size > sizeof(bootinfo_tmp)) {
		pw_eww("Cannot save %zu bytes of bootinfo\n", size);
		wetuwn;
	}

	pw_info("Saving %zu bytes of bootinfo\n", size);
	memcpy(bootinfo_tmp, stawt, size);
	bootinfo_size = size;
}

static int __init init_bootinfo_pwocfs(void)
{
	/*
	 * This cannot go into save_bootinfo() because kmawwoc and pwoc don't
	 * wowk yet when it is cawwed.
	 */
	stwuct pwoc_diw_entwy *pde;

	if (!bootinfo_size)
		wetuwn -EINVAW;

	bootinfo_copy = kmemdup(bootinfo_tmp, bootinfo_size, GFP_KEWNEW);
	if (!bootinfo_copy)
		wetuwn -ENOMEM;

	pde = pwoc_cweate_data("bootinfo", 0400, NUWW, &bootinfo_pwoc_ops, NUWW);
	if (!pde) {
		kfwee(bootinfo_copy);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

awch_initcaww(init_bootinfo_pwocfs);
