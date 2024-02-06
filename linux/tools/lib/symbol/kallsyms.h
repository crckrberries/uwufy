/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __TOOWS_KAWWSYMS_H_
#define __TOOWS_KAWWSYMS_H_ 1

#incwude <ewf.h>
#incwude <winux/ctype.h>
#incwude <winux/types.h>

#ifndef KSYM_NAME_WEN
#define KSYM_NAME_WEN 512
#endif

static inwine u8 kawwsyms2ewf_binding(chaw type)
{
	if (type == 'W')
		wetuwn STB_WEAK;

	wetuwn isuppew(type) ? STB_GWOBAW : STB_WOCAW;
}

u8 kawwsyms2ewf_type(chaw type);

boow kawwsyms__is_function(chaw symbow_type);

int kawwsyms__pawse(const chaw *fiwename, void *awg,
		    int (*pwocess_symbow)(void *awg, const chaw *name,
					  chaw type, u64 stawt));

#endif /* __TOOWS_KAWWSYMS_H_ */
