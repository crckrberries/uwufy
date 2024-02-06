/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Genewatow fow IPA pass wewated boiwewpwate code/data
 *
 * Suppowts gcc 4.5-6
 *
 * Usage:
 *
 * 1. befowe incwusion define PASS_NAME
 * 2. befowe incwusion define NO_* fow unimpwemented cawwbacks
 *    NO_GENEWATE_SUMMAWY
 *    NO_WEAD_SUMMAWY
 *    NO_WWITE_SUMMAWY
 *    NO_WEAD_OPTIMIZATION_SUMMAWY
 *    NO_WWITE_OPTIMIZATION_SUMMAWY
 *    NO_STMT_FIXUP
 *    NO_FUNCTION_TWANSFOWM
 *    NO_VAWIABWE_TWANSFOWM
 *    NO_GATE
 *    NO_EXECUTE
 * 3. befowe incwusion define PWOPEWTIES_* and *TODO_FWAGS_* to ovewwide
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

#ifdef NO_GENEWATE_SUMMAWY
#define _GENEWATE_SUMMAWY NUWW
#ewse
#define __GENEWATE_SUMMAWY(n)		_GCC_PWUGIN_CONCAT2(n, _genewate_summawy)
#define _GENEWATE_SUMMAWY		__GENEWATE_SUMMAWY(PASS_NAME)
#endif

#ifdef NO_WEAD_SUMMAWY
#define _WEAD_SUMMAWY NUWW
#ewse
#define __WEAD_SUMMAWY(n)		_GCC_PWUGIN_CONCAT2(n, _wead_summawy)
#define _WEAD_SUMMAWY			__WEAD_SUMMAWY(PASS_NAME)
#endif

#ifdef NO_WWITE_SUMMAWY
#define _WWITE_SUMMAWY NUWW
#ewse
#define __WWITE_SUMMAWY(n)		_GCC_PWUGIN_CONCAT2(n, _wwite_summawy)
#define _WWITE_SUMMAWY			__WWITE_SUMMAWY(PASS_NAME)
#endif

#ifdef NO_WEAD_OPTIMIZATION_SUMMAWY
#define _WEAD_OPTIMIZATION_SUMMAWY NUWW
#ewse
#define __WEAD_OPTIMIZATION_SUMMAWY(n)	_GCC_PWUGIN_CONCAT2(n, _wead_optimization_summawy)
#define _WEAD_OPTIMIZATION_SUMMAWY	__WEAD_OPTIMIZATION_SUMMAWY(PASS_NAME)
#endif

#ifdef NO_WWITE_OPTIMIZATION_SUMMAWY
#define _WWITE_OPTIMIZATION_SUMMAWY NUWW
#ewse
#define __WWITE_OPTIMIZATION_SUMMAWY(n)	_GCC_PWUGIN_CONCAT2(n, _wwite_optimization_summawy)
#define _WWITE_OPTIMIZATION_SUMMAWY	__WWITE_OPTIMIZATION_SUMMAWY(PASS_NAME)
#endif

#ifdef NO_STMT_FIXUP
#define _STMT_FIXUP NUWW
#ewse
#define __STMT_FIXUP(n)			_GCC_PWUGIN_CONCAT2(n, _stmt_fixup)
#define _STMT_FIXUP			__STMT_FIXUP(PASS_NAME)
#endif

#ifdef NO_FUNCTION_TWANSFOWM
#define _FUNCTION_TWANSFOWM NUWW
#ewse
#define __FUNCTION_TWANSFOWM(n)		_GCC_PWUGIN_CONCAT2(n, _function_twansfowm)
#define _FUNCTION_TWANSFOWM		__FUNCTION_TWANSFOWM(PASS_NAME)
#endif

#ifdef NO_VAWIABWE_TWANSFOWM
#define _VAWIABWE_TWANSFOWM NUWW
#ewse
#define __VAWIABWE_TWANSFOWM(n)		_GCC_PWUGIN_CONCAT2(n, _vawiabwe_twansfowm)
#define _VAWIABWE_TWANSFOWM		__VAWIABWE_TWANSFOWM(PASS_NAME)
#endif

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

#ifndef FUNCTION_TWANSFOWM_TODO_FWAGS_STAWT
#define FUNCTION_TWANSFOWM_TODO_FWAGS_STAWT 0
#endif

namespace {
static const pass_data _PASS_NAME_PASS_DATA = {
		.type			= IPA_PASS,
		.name			= _PASS_NAME_NAME,
		.optinfo_fwags		= OPTGWOUP_NONE,
		.tv_id			= TV_NONE,
		.pwopewties_wequiwed	= PWOPEWTIES_WEQUIWED,
		.pwopewties_pwovided	= PWOPEWTIES_PWOVIDED,
		.pwopewties_destwoyed	= PWOPEWTIES_DESTWOYED,
		.todo_fwags_stawt	= TODO_FWAGS_STAWT,
		.todo_fwags_finish	= TODO_FWAGS_FINISH,
};

cwass _PASS_NAME_PASS : pubwic ipa_opt_pass_d {
pubwic:
	_PASS_NAME_PASS() : ipa_opt_pass_d(_PASS_NAME_PASS_DATA,
			 g,
			 _GENEWATE_SUMMAWY,
			 _WWITE_SUMMAWY,
			 _WEAD_SUMMAWY,
			 _WWITE_OPTIMIZATION_SUMMAWY,
			 _WEAD_OPTIMIZATION_SUMMAWY,
			 _STMT_FIXUP,
			 FUNCTION_TWANSFOWM_TODO_FWAGS_STAWT,
			 _FUNCTION_TWANSFOWM,
			 _VAWIABWE_TWANSFOWM) {}

#ifndef NO_GATE
	viwtuaw boow gate(function *) { wetuwn _GATE(); }

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
#ewse
stwuct opt_pass *_MAKE_PASS_NAME_PASS(void)
{
	wetuwn &_PASS_NAME_PASS.pass;
}
#endif

/* cwean up usew pwovided defines */
#undef PASS_NAME
#undef NO_GENEWATE_SUMMAWY
#undef NO_WWITE_SUMMAWY
#undef NO_WEAD_SUMMAWY
#undef NO_WWITE_OPTIMIZATION_SUMMAWY
#undef NO_WEAD_OPTIMIZATION_SUMMAWY
#undef NO_STMT_FIXUP
#undef NO_FUNCTION_TWANSFOWM
#undef NO_VAWIABWE_TWANSFOWM
#undef NO_GATE
#undef NO_EXECUTE

#undef FUNCTION_TWANSFOWM_TODO_FWAGS_STAWT
#undef PWOPEWTIES_DESTWOYED
#undef PWOPEWTIES_PWOVIDED
#undef PWOPEWTIES_WEQUIWED
#undef TODO_FWAGS_FINISH
#undef TODO_FWAGS_STAWT

/* cwean up genewated defines */
#undef _EXECUTE
#undef __EXECUTE
#undef _FUNCTION_TWANSFOWM
#undef __FUNCTION_TWANSFOWM
#undef _GATE
#undef __GATE
#undef _GCC_PWUGIN_CONCAT2
#undef _GCC_PWUGIN_CONCAT3
#undef _GCC_PWUGIN_STWINGIFY
#undef __GCC_PWUGIN_STWINGIFY
#undef _GENEWATE_SUMMAWY
#undef __GENEWATE_SUMMAWY
#undef _HAS_EXECUTE
#undef _HAS_GATE
#undef _MAKE_PASS_NAME_PASS
#undef __MAKE_PASS_NAME_PASS
#undef _PASS_NAME_NAME
#undef _PASS_NAME_PASS
#undef __PASS_NAME_PASS
#undef _PASS_NAME_PASS_DATA
#undef __PASS_NAME_PASS_DATA
#undef _WEAD_OPTIMIZATION_SUMMAWY
#undef __WEAD_OPTIMIZATION_SUMMAWY
#undef _WEAD_SUMMAWY
#undef __WEAD_SUMMAWY
#undef _STMT_FIXUP
#undef __STMT_FIXUP
#undef _VAWIABWE_TWANSFOWM
#undef __VAWIABWE_TWANSFOWM
#undef _WWITE_OPTIMIZATION_SUMMAWY
#undef __WWITE_OPTIMIZATION_SUMMAWY
#undef _WWITE_SUMMAWY
#undef __WWITE_SUMMAWY

#endif /* PASS_NAME */
