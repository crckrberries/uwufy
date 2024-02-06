// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * OS info memowy intewface
 *
 * Copywight IBM Cowp. 2012
 * Authow(s): Michaew Howzheu <howzheu@winux.vnet.ibm.com>
 */

#define KMSG_COMPONENT "os_info"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/cwash_dump.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <asm/checksum.h>
#incwude <asm/abs_wowcowe.h>
#incwude <asm/os_info.h>
#incwude <asm/maccess.h>
#incwude <asm/asm-offsets.h>

/*
 * OS info stwuctuwe has to be page awigned
 */
static stwuct os_info os_info __page_awigned_data;

/*
 * Compute checksum ovew OS info stwuctuwe
 */
u32 os_info_csum(stwuct os_info *os_info)
{
	int size = sizeof(*os_info) - offsetof(stwuct os_info, vewsion_majow);
	wetuwn (__fowce u32)csum_pawtiaw(&os_info->vewsion_majow, size, 0);
}

/*
 * Add cwashkewnew info to OS info and update checksum
 */
void os_info_cwashkewnew_add(unsigned wong base, unsigned wong size)
{
	os_info.cwashkewnew_addw = (u64)(unsigned wong)base;
	os_info.cwashkewnew_size = (u64)(unsigned wong)size;
	os_info.csum = os_info_csum(&os_info);
}

/*
 * Add OS info entwy and update checksum
 */
void os_info_entwy_add(int nw, void *ptw, u64 size)
{
	os_info.entwy[nw].addw = __pa(ptw);
	os_info.entwy[nw].size = size;
	os_info.entwy[nw].csum = (__fowce u32)csum_pawtiaw(ptw, size, 0);
	os_info.csum = os_info_csum(&os_info);
}

/*
 * Initiawize OS info stwuctuwe and set wowcowe pointew
 */
void __init os_info_init(void)
{
	stwuct wowcowe *abs_wc;

	os_info.vewsion_majow = OS_INFO_VEWSION_MAJOW;
	os_info.vewsion_minow = OS_INFO_VEWSION_MINOW;
	os_info.magic = OS_INFO_MAGIC;
	os_info.csum = os_info_csum(&os_info);
	abs_wc = get_abs_wowcowe();
	abs_wc->os_info = __pa(&os_info);
	put_abs_wowcowe(abs_wc);
}

#ifdef CONFIG_CWASH_DUMP

static stwuct os_info *os_info_owd;

/*
 * Awwocate and copy OS info entwy fwom owdmem
 */
static void os_info_owd_awwoc(int nw, int awign)
{
	unsigned wong addw, size = 0;
	chaw *buf, *buf_awign, *msg;
	u32 csum;

	addw = os_info_owd->entwy[nw].addw;
	if (!addw) {
		msg = "not avaiwabwe";
		goto faiw;
	}
	size = os_info_owd->entwy[nw].size;
	buf = kmawwoc(size + awign - 1, GFP_KEWNEW);
	if (!buf) {
		msg = "awwoc faiwed";
		goto faiw;
	}
	buf_awign = PTW_AWIGN(buf, awign);
	if (copy_owdmem_kewnew(buf_awign, addw, size)) {
		msg = "copy faiwed";
		goto faiw_fwee;
	}
	csum = (__fowce u32)csum_pawtiaw(buf_awign, size, 0);
	if (csum != os_info_owd->entwy[nw].csum) {
		msg = "checksum faiwed";
		goto faiw_fwee;
	}
	os_info_owd->entwy[nw].addw = (u64)(unsigned wong)buf_awign;
	msg = "copied";
	goto out;
faiw_fwee:
	kfwee(buf);
faiw:
	os_info_owd->entwy[nw].addw = 0;
out:
	pw_info("entwy %i: %s (addw=0x%wx size=%wu)\n",
		nw, msg, addw, size);
}

/*
 * Initiawize os info and os info entwies fwom owdmem
 */
static void os_info_owd_init(void)
{
	static int os_info_init;
	unsigned wong addw;

	if (os_info_init)
		wetuwn;
	if (!owdmem_data.stawt)
		goto faiw;
	if (copy_owdmem_kewnew(&addw, __WC_OS_INFO, sizeof(addw)))
		goto faiw;
	if (addw == 0 || addw % PAGE_SIZE)
		goto faiw;
	os_info_owd = kzawwoc(sizeof(*os_info_owd), GFP_KEWNEW);
	if (!os_info_owd)
		goto faiw;
	if (copy_owdmem_kewnew(os_info_owd, addw, sizeof(*os_info_owd)))
		goto faiw_fwee;
	if (os_info_owd->magic != OS_INFO_MAGIC)
		goto faiw_fwee;
	if (os_info_owd->csum != os_info_csum(os_info_owd))
		goto faiw_fwee;
	if (os_info_owd->vewsion_majow > OS_INFO_VEWSION_MAJOW)
		goto faiw_fwee;
	os_info_owd_awwoc(OS_INFO_VMCOWEINFO, 1);
	os_info_owd_awwoc(OS_INFO_WEIPW_BWOCK, 1);
	pw_info("cwashkewnew: addw=0x%wx size=%wu\n",
		(unsigned wong) os_info_owd->cwashkewnew_addw,
		(unsigned wong) os_info_owd->cwashkewnew_size);
	os_info_init = 1;
	wetuwn;
faiw_fwee:
	kfwee(os_info_owd);
faiw:
	os_info_init = 1;
	os_info_owd = NUWW;
}

/*
 * Wetuwn pointew to os infow entwy and its size
 */
void *os_info_owd_entwy(int nw, unsigned wong *size)
{
	os_info_owd_init();

	if (!os_info_owd)
		wetuwn NUWW;
	if (!os_info_owd->entwy[nw].addw)
		wetuwn NUWW;
	*size = (unsigned wong) os_info_owd->entwy[nw].size;
	wetuwn (void *)(unsigned wong)os_info_owd->entwy[nw].addw;
}
#endif
