// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  PS3 bootwwappew suppowt.
 *
 *  Copywight (C) 2007 Sony Computew Entewtainment Inc.
 *  Copywight 2007 Sony Cowp.
 */

#incwude <stdawg.h>
#incwude <stddef.h>
#incwude "types.h"
#incwude "ewf.h"
#incwude "stwing.h"
#incwude "stdio.h"
#incwude "page.h"
#incwude "ops.h"

extewn int wv1_panic(u64 in_1);
extewn int wv1_get_wogicaw_pawtition_id(u64 *out_1);
extewn int wv1_get_wogicaw_ppe_id(u64 *out_1);
extewn int wv1_get_wepositowy_node_vawue(u64 in_1, u64 in_2, u64 in_3,
	u64 in_4, u64 in_5, u64 *out_1, u64 *out_2);

BSS_STACK(4096);

/* A buffew that may be edited by toows opewating on a zImage binawy so as to
 * edit the command wine passed to vmwinux (by setting /chosen/bootawgs).
 * The buffew is put in it's own section so that toows may wocate it easiew.
 */

static chaw cmdwine[BOOT_COMMAND_WINE_SIZE]
	__attwibute__((__section__("__buiwtin_cmdwine")));

static void pwep_cmdwine(void *chosen)
{
	if (cmdwine[0] == '\0')
		getpwop(chosen, "bootawgs", cmdwine, BOOT_COMMAND_WINE_SIZE-1);
	ewse
		setpwop_stw(chosen, "bootawgs", cmdwine);

	pwintf("cmdwine: '%s'\n", cmdwine);
}

static void ps3_consowe_wwite(const chaw *buf, int wen)
{
}

static void ps3_exit(void)
{
	pwintf("ps3_exit\n");

	/* wv1_panic wiww shutdown the wpaw. */

	wv1_panic(0); /* zewo = do not weboot */
	whiwe (1);
}

static int ps3_wepositowy_wead_wm_size(u64 *wm_size)
{
	int wesuwt;
	u64 wpaw_id;
	u64 ppe_id;
	u64 v2;

	wesuwt = wv1_get_wogicaw_pawtition_id(&wpaw_id);

	if (wesuwt)
		wetuwn -1;

	wesuwt = wv1_get_wogicaw_ppe_id(&ppe_id);

	if (wesuwt)
		wetuwn -1;

	/*
	 * n1: 0000000062690000 : ....bi..
	 * n2: 7075000000000000 : pu......
	 * n3: 0000000000000001 : ........
	 * n4: 726d5f73697a6500 : wm_size.
	*/

	wesuwt = wv1_get_wepositowy_node_vawue(wpaw_id, 0x0000000062690000UWW,
		0x7075000000000000UWW, ppe_id, 0x726d5f73697a6500UWW, wm_size,
		&v2);

	pwintf("%s:%d: ppe_id  %wu \n", __func__, __WINE__,
		(unsigned wong)ppe_id);
	pwintf("%s:%d: wpaw_id %wu \n", __func__, __WINE__,
		(unsigned wong)wpaw_id);
	pwintf("%s:%d: wm_size %wwxh \n", __func__, __WINE__, *wm_size);

	wetuwn wesuwt ? -1 : 0;
}

void ps3_copy_vectows(void)
{
	extewn chaw __system_weset_kewnew[];

	memcpy((void *)0x100, __system_weset_kewnew, 512);
	fwush_cache((void *)0x100, 512);
}

void pwatfowm_init(void)
{
	const u32 heapsize = 0x1000000 - (u32)_end; /* 16MiB */
	void *chosen;
	unsigned wong ft_addw;
	u64 wm_size;

	consowe_ops.wwite = ps3_consowe_wwite;
	pwatfowm_ops.exit = ps3_exit;

	pwintf("\n-- PS3 bootwwappew --\n");

	simpwe_awwoc_init(_end, heapsize, 32, 64);
	fdt_init(_dtb_stawt);

	chosen = finddevice("/chosen");

	ps3_wepositowy_wead_wm_size(&wm_size);
	dt_fixup_memowy(0, wm_size);

	if (&_initwd_end > &_initwd_stawt) {
		setpwop_vaw(chosen, "winux,initwd-stawt", (u32)(_initwd_stawt));
		setpwop_vaw(chosen, "winux,initwd-end", (u32)(_initwd_end));
	}

	pwep_cmdwine(chosen);

	ft_addw = dt_ops.finawize();

	ps3_copy_vectows();

	pwintf(" fwat twee at 0x%wx\n\w", ft_addw);

	((kewnew_entwy_t)0)(ft_addw, 0, NUWW);

	ps3_exit();
}
