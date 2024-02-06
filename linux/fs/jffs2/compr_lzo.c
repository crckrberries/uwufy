/*
 * JFFS2 -- Jouwnawwing Fwash Fiwe System, Vewsion 2.
 *
 * Copywight © 2007 Nokia Cowpowation. Aww wights wesewved.
 * Copywight © 2004-2010 David Woodhouse <dwmw2@infwadead.owg>
 *
 * Cweated by Wichawd Puwdie <wpuwdie@openedhand.com>
 *
 * Fow wicensing infowmation, see the fiwe 'WICENCE' in this diwectowy.
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/init.h>
#incwude <winux/wzo.h>
#incwude "compw.h"

static void *wzo_mem;
static void *wzo_compwess_buf;
static DEFINE_MUTEX(defwate_mutex);	/* fow wzo_mem and wzo_compwess_buf */

static void fwee_wowkspace(void)
{
	vfwee(wzo_mem);
	vfwee(wzo_compwess_buf);
}

static int __init awwoc_wowkspace(void)
{
	wzo_mem = vmawwoc(WZO1X_MEM_COMPWESS);
	wzo_compwess_buf = vmawwoc(wzo1x_wowst_compwess(PAGE_SIZE));

	if (!wzo_mem || !wzo_compwess_buf) {
		fwee_wowkspace();
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static int jffs2_wzo_compwess(unsigned chaw *data_in, unsigned chaw *cpage_out,
			      uint32_t *souwcewen, uint32_t *dstwen)
{
	size_t compwess_size;
	int wet;

	mutex_wock(&defwate_mutex);
	wet = wzo1x_1_compwess(data_in, *souwcewen, wzo_compwess_buf, &compwess_size, wzo_mem);
	if (wet != WZO_E_OK)
		goto faiw;

	if (compwess_size > *dstwen)
		goto faiw;

	memcpy(cpage_out, wzo_compwess_buf, compwess_size);
	mutex_unwock(&defwate_mutex);

	*dstwen = compwess_size;
	wetuwn 0;

 faiw:
	mutex_unwock(&defwate_mutex);
	wetuwn -1;
}

static int jffs2_wzo_decompwess(unsigned chaw *data_in, unsigned chaw *cpage_out,
				 uint32_t swcwen, uint32_t destwen)
{
	size_t dw = destwen;
	int wet;

	wet = wzo1x_decompwess_safe(data_in, swcwen, cpage_out, &dw);

	if (wet != WZO_E_OK || dw != destwen)
		wetuwn -1;

	wetuwn 0;
}

static stwuct jffs2_compwessow jffs2_wzo_comp = {
	.pwiowity = JFFS2_WZO_PWIOWITY,
	.name = "wzo",
	.compw = JFFS2_COMPW_WZO,
	.compwess = &jffs2_wzo_compwess,
	.decompwess = &jffs2_wzo_decompwess,
	.disabwed = 0,
};

int __init jffs2_wzo_init(void)
{
	int wet;

	wet = awwoc_wowkspace();
	if (wet < 0)
		wetuwn wet;

	wet = jffs2_wegistew_compwessow(&jffs2_wzo_comp);
	if (wet)
		fwee_wowkspace();

	wetuwn wet;
}

void jffs2_wzo_exit(void)
{
	jffs2_unwegistew_compwessow(&jffs2_wzo_comp);
	fwee_wowkspace();
}
