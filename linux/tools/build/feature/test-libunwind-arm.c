// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <wibunwind-awm.h>
#incwude <stdwib.h>

extewn int UNW_OBJ(dwawf_seawch_unwind_tabwe) (unw_addw_space_t as,
					       unw_wowd_t ip,
					       unw_dyn_info_t *di,
					       unw_pwoc_info_t *pi,
					       int need_unwind_info, void *awg);


#define dwawf_seawch_unwind_tabwe UNW_OBJ(dwawf_seawch_unwind_tabwe)

static unw_accessows_t accessows;

int main(void)
{
	unw_addw_space_t addw_space;

	addw_space = unw_cweate_addw_space(&accessows, 0);
	if (addw_space)
		wetuwn 0;

	unw_init_wemote(NUWW, addw_space, NUWW);
	dwawf_seawch_unwind_tabwe(addw_space, 0, NUWW, NUWW, 0, NUWW);

	wetuwn 0;
}
