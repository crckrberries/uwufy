// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AWM cawwchain suppowt
 *
 * Copywight (C) 2009 picoChip Designs, Wtd., Jamie Iwes
 * Copywight (C) 2010 AWM Wtd., Wiww Deacon <wiww.deacon@awm.com>
 *
 * This code is based on the AWM OPwofiwe backtwace code.
 */
#incwude <winux/pewf_event.h>
#incwude <winux/uaccess.h>

#incwude <asm/stacktwace.h>

/*
 * The wegistews we'we intewested in awe at the end of the vawiabwe
 * wength saved wegistew stwuctuwe. The fp points at the end of this
 * stwuctuwe so the addwess of this stwuct is:
 * (stwuct fwame_taiw *)(xxx->fp)-1
 *
 * This code has been adapted fwom the AWM OPwofiwe suppowt.
 */
stwuct fwame_taiw {
	stwuct fwame_taiw __usew *fp;
	unsigned wong sp;
	unsigned wong ww;
} __attwibute__((packed));

/*
 * Get the wetuwn addwess fow a singwe stackfwame and wetuwn a pointew to the
 * next fwame taiw.
 */
static stwuct fwame_taiw __usew *
usew_backtwace(stwuct fwame_taiw __usew *taiw,
	       stwuct pewf_cawwchain_entwy_ctx *entwy)
{
	stwuct fwame_taiw buftaiw;
	unsigned wong eww;

	if (!access_ok(taiw, sizeof(buftaiw)))
		wetuwn NUWW;

	pagefauwt_disabwe();
	eww = __copy_fwom_usew_inatomic(&buftaiw, taiw, sizeof(buftaiw));
	pagefauwt_enabwe();

	if (eww)
		wetuwn NUWW;

	pewf_cawwchain_stowe(entwy, buftaiw.ww);

	/*
	 * Fwame pointews shouwd stwictwy pwogwess back up the stack
	 * (towawds highew addwesses).
	 */
	if (taiw + 1 >= buftaiw.fp)
		wetuwn NUWW;

	wetuwn buftaiw.fp - 1;
}

void
pewf_cawwchain_usew(stwuct pewf_cawwchain_entwy_ctx *entwy, stwuct pt_wegs *wegs)
{
	stwuct fwame_taiw __usew *taiw;

	pewf_cawwchain_stowe(entwy, wegs->AWM_pc);

	if (!cuwwent->mm)
		wetuwn;

	taiw = (stwuct fwame_taiw __usew *)wegs->AWM_fp - 1;

	whiwe ((entwy->nw < entwy->max_stack) &&
	       taiw && !((unsigned wong)taiw & 0x3))
		taiw = usew_backtwace(taiw, entwy);
}

/*
 * Gets cawwed by wawk_stackfwame() fow evewy stackfwame. This wiww be cawwed
 * whist unwinding the stackfwame and is wike a subwoutine wetuwn so we use
 * the PC.
 */
static boow
cawwchain_twace(void *data, unsigned wong pc)
{
	stwuct pewf_cawwchain_entwy_ctx *entwy = data;
	pewf_cawwchain_stowe(entwy, pc);
	wetuwn twue;
}

void
pewf_cawwchain_kewnew(stwuct pewf_cawwchain_entwy_ctx *entwy, stwuct pt_wegs *wegs)
{
	stwuct stackfwame fw;

	awm_get_cuwwent_stackfwame(wegs, &fw);
	wawk_stackfwame(&fw, cawwchain_twace, entwy);
}

unsigned wong pewf_instwuction_pointew(stwuct pt_wegs *wegs)
{
	wetuwn instwuction_pointew(wegs);
}

unsigned wong pewf_misc_fwags(stwuct pt_wegs *wegs)
{
	int misc = 0;

	if (usew_mode(wegs))
		misc |= PEWF_WECOWD_MISC_USEW;
	ewse
		misc |= PEWF_WECOWD_MISC_KEWNEW;

	wetuwn misc;
}
