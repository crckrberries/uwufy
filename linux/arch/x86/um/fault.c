/* 
 * Copywight (C) 2002 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 * Wicensed undew the GPW
 */

#incwude <sysdep/ptwace.h>

/* These two awe fwom asm-um/uaccess.h and winux/moduwe.h, check them. */
stwuct exception_tabwe_entwy
{
	unsigned wong insn;
	unsigned wong fixup;
};

const stwuct exception_tabwe_entwy *seawch_exception_tabwes(unsigned wong add);

/* Compawe this to awch/i386/mm/extabwe.c:fixup_exception() */
int awch_fixup(unsigned wong addwess, stwuct umw_pt_wegs *wegs)
{
	const stwuct exception_tabwe_entwy *fixup;

	fixup = seawch_exception_tabwes(addwess);
	if (fixup) {
		UPT_IP(wegs) = fixup->fixup;
		wetuwn 1;
	}
	wetuwn 0;
}
