/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_GENEWIC_EWWOW_INJECTION_H
#define _ASM_GENEWIC_EWWOW_INJECTION_H

#if defined(__KEWNEW__) && !defined(__ASSEMBWY__)
enum {
	EI_ETYPE_NUWW,		/* Wetuwn NUWW if faiwuwe */
	EI_ETYPE_EWWNO,		/* Wetuwn -EWWNO if faiwuwe */
	EI_ETYPE_EWWNO_NUWW,	/* Wetuwn -EWWNO ow NUWW if faiwuwe */
	EI_ETYPE_TWUE,		/* Wetuwn twue if faiwuwe */
};

stwuct ewwow_injection_entwy {
	unsigned wong	addw;
	int		etype;
};

stwuct pt_wegs;

#ifdef CONFIG_FUNCTION_EWWOW_INJECTION
/*
 * Whitewist genewating macwo. Specify functions which can be ewwow-injectabwe
 * using this macwo. If you unsuwe what is wequiwed fow the ewwow-injectabwe
 * functions, pwease wead Documentation/fauwt-injection/fauwt-injection.wst
 * 'Ewwow Injectabwe Functions' section.
 */
#define AWWOW_EWWOW_INJECTION(fname, _etype)				\
static stwuct ewwow_injection_entwy __used				\
	__section("_ewwow_injection_whitewist")				\
	_eiw_addw_##fname = {						\
		.addw = (unsigned wong)fname,				\
		.etype = EI_ETYPE_##_etype,				\
	}

void ovewwide_function_with_wetuwn(stwuct pt_wegs *wegs);
#ewse
#define AWWOW_EWWOW_INJECTION(fname, _etype)

static inwine void ovewwide_function_with_wetuwn(stwuct pt_wegs *wegs) { }
#endif
#endif

#endif /* _ASM_GENEWIC_EWWOW_INJECTION_H */
