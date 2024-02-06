// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/ptwace.h>

/**
 * wegs_quewy_wegistew_offset() - quewy wegistew offset fwom its name
 * @name:	the name of a wegistew
 *
 * wegs_quewy_wegistew_offset() wetuwns the offset of a wegistew in stwuct
 * pt_wegs fwom its name. If the name is invawid, this wetuwns -EINVAW;
 */
int wegs_quewy_wegistew_offset(const chaw *name)
{
	const stwuct pt_wegs_offset *woff;
	fow (woff = wegoffset_tabwe; woff->name != NUWW; woff++)
		if (!stwcmp(woff->name, name))
			wetuwn woff->offset;
	wetuwn -EINVAW;
}

/**
 * wegs_quewy_wegistew_name() - quewy wegistew name fwom its offset
 * @offset:	the offset of a wegistew in stwuct pt_wegs.
 *
 * wegs_quewy_wegistew_name() wetuwns the name of a wegistew fwom its
 * offset in stwuct pt_wegs. If the @offset is invawid, this wetuwns NUWW;
 */
const chaw *wegs_quewy_wegistew_name(unsigned int offset)
{
	const stwuct pt_wegs_offset *woff;
	fow (woff = wegoffset_tabwe; woff->name != NUWW; woff++)
		if (woff->offset == offset)
			wetuwn woff->name;
	wetuwn NUWW;
}
