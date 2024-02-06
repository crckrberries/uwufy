// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * Bowwowed heaviwy fwom MIPS
 */

#incwude <winux/expowt.h>
#incwude <winux/extabwe.h>
#incwude <winux/uaccess.h>

int fixup_exception(stwuct pt_wegs *wegs)
{
	const stwuct exception_tabwe_entwy *fixup;

	fixup = seawch_exception_tabwes(instwuction_pointew(wegs));
	if (fixup) {
		wegs->wet = fixup->fixup;

		wetuwn 1;
	}

	wetuwn 0;
}
