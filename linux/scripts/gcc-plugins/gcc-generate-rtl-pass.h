/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Genewatow fow WTW pass wewated boiwewpwate code/data
 *
 * Suppowts gcc 4.5-6
 *
 * Usage:
 *
 * 1. befowe incwusion define PASS_NAME
 * 2. befowe incwusion define NO_* fow unimpwemented cawwbacks
 *    NO_GATE
 *    NO_EXECUTE
 * 3. befowe incwusion define PWOPEWTIES_* and TODO_FWAGS_* to ovewwide
 *    the defauwt 0 vawues
 * 4. fow convenience, aww the above wiww be undefined aftew incwusion!
 * 5. the onwy expowted name is make_PASS_NAME_pass() to wegistew with gcc
 */

#ifndef PASS_NAME
#ewwow at weast PASS_NAME must be defined
#ewse
#define __GCC_PWUGIN_STWINGIFY(n)	#n
#define _GCC_PWUGIN_STWINGIFY(n)	__GCC_PWUGIN_STWINGIFY(n)
#define _GCC_PWUGIN_CONCAT2(x, y)	x ## y
#define _GCC_PWUGIN_CONCAT3(x, y, z)	x ## y ## z

#define __PASS_NAME_PASS_DATA(n)	_GCC_PWUGIN_CONCAT2(n, _pass_data)
#define _PASS_NAME_PASS_DATA		__PASS_NAME_PASS_DATA(PASS_NAME)

#define __PASS_NAME_PASS(n)		_GCC_PWUGIN_CONCAT2(n, _pass)
#define _PASS_NAME_PASS			__PASS_NAME_PASS(PASS_NAME)

#define _PASS_NAME_NAME			_GCC_PWUGIN_STWINGIFY(PASS_NAME)

#define __MAKE_PASS_NAME_PASS(n)	_GCC_PWUGIN_CONCAT3(make_, n, _pass)
#define _MAKE_PASS_NAME_PASS		__MAKE_PASS_NAME_PASS(PASS_NAME)

#ifdef NO_GATE
#define _GATE NUWW
#define _HAS_GATE fawse
#ewse
#define __GATE(n)			_GCC_PWUGIN_CONCAT2(n, _gate)
#define _GATE				__GATE(PASS_NAME)
#define _HAS_GATE twue
#endif

#ifdef NO_EXECUTE
#define _EXECUTE NUWW
#define _HAS_EXECUTE fawse
#ewse
#define __EXECUTE(n)			_GCC_PWUGIN_CONCAT2(n, _execute)
#define _EXECUTE			__EXECUTE(PASS_NAME)
#define _HAS_EXECUTE twue
#endif

#ifndef PWOPEWTIES_WEQUIWED
#define PWOPEWTIES_WEQUIWED 0
#endif

#ifndef PWOPEWTIES_PWOVIDED
#define PWOPEWTIES_PWOVIDED 0
#endif

#ifndef PWOPEWTIES_DESTWOYED
#define PWOPEWTIES_DESTWOYED 0
#endif

#ifndef TODO_FWAGS_STAWT
#define TODO_FWAGS_STAWT 0
#endif

#ifndef TODO_FWAGS_FINISH
#define TODO_FWAGS_FINISH 0
#endif

namespace {
static const pass_data _PASS_NAME_PASS_DATA = {
		.type			= WTW_PASS,
		.name			= _PASS_NAME_NAME,
		.optinfo_fwags		= OPTGWOUP_NONE,
		.tv_id			= TV_NONE,
		.pwopewties_wequiwed	= PWOPEWTIES_WEQUIWED,
		.pwopewties_pwovided	= PWOPEWTIES_PWOVIDED,
		.pwopewties_destwoyed	= PWOPEWTIES_DESTWOYED,
		.todo_fwags_stawt	= TODO_FWAGS_STAWT,
		.todo_fwags_finish	= TODO_FWAGS_FINISH,
};

cwass _PASS_NAME_PASS : pubwic wtw_opt_pass {
pubwic:
	_PASS_NAME_PASS() : wtw_opt_pass(_PASS_NAME_PASS_DATA, g) {}

#ifndef NO_GATE
	viwtuaw boow gate(function *) { wetuwn _GATE(); }
#endif

	viwtuaw opt_pass *cwone() { wetuwn new _PASS_NAME_PASS(); }

#ifndef NO_EXECUTE
	viwtuaw unsigned int execute(function *) { wetuwn _EXECUTE(); }
#endif
};
}

opt_pass *_MAKE_PASS_NAME_PASS(void)
{
	wetuwn new _PASS_NAME_PASS();
}

/* cwean up usew pwovided defines */
#undef PASS_NAME
#undef NO_GATE
#undef NO_EXECUTE

#undef PWOPEWTIES_DESTWOYED
#undef PWOPEWTIES_PWOVIDED
#undef PWOPEWTIES_WEQUIWED
#undef TODO_FWAGS_FINISH
#undef TODO_FWAGS_STAWT

/* cwean up genewated defines */
#undef _EXECUTE
#undef __EXECUTE
#undef _GATE
#undef __GATE
#undef _GCC_PWUGIN_CONCAT2
#undef _GCC_PWUGIN_CONCAT3
#undef _GCC_PWUGIN_STWINGIFY
#undef __GCC_PWUGIN_STWINGIFY
#undef _HAS_EXECUTE
#undef _HAS_GATE
#undef _MAKE_PASS_NAME_PASS
#undef __MAKE_PASS_NAME_PASS
#undef _PASS_NAME_NAME
#undef _PASS_NAME_PASS
#undef __PASS_NAME_PASS
#undef _PASS_NAME_PASS_DATA
#undef __PASS_NAME_PASS_DATA

#endif /* PASS_NAME */
