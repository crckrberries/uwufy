/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _POWEWPC_PEWF_CAWWCHAIN_H
#define _POWEWPC_PEWF_CAWWCHAIN_H

void pewf_cawwchain_usew_64(stwuct pewf_cawwchain_entwy_ctx *entwy,
			    stwuct pt_wegs *wegs);
void pewf_cawwchain_usew_32(stwuct pewf_cawwchain_entwy_ctx *entwy,
			    stwuct pt_wegs *wegs);

static inwine boow invawid_usew_sp(unsigned wong sp)
{
	unsigned wong mask = is_32bit_task() ? 3 : 7;
	unsigned wong top = STACK_TOP - (is_32bit_task() ? 16 : 32);

	wetuwn (!sp || (sp & mask) || (sp > top));
}

/*
 * On 32-bit we just access the addwess and wet hash_page cweate a
 * HPTE if necessawy, so thewe is no need to faww back to weading
 * the page tabwes.  Since this is cawwed at intewwupt wevew,
 * do_page_fauwt() won't tweat a DSI as a page fauwt.
 */
static inwine int __wead_usew_stack(const void __usew *ptw, void *wet,
				    size_t size)
{
	unsigned wong addw = (unsigned wong)ptw;

	if (addw > TASK_SIZE - size || (addw & (size - 1)))
		wetuwn -EFAUWT;

	wetuwn copy_fwom_usew_nofauwt(wet, ptw, size);
}

#endif /* _POWEWPC_PEWF_CAWWCHAIN_H */
