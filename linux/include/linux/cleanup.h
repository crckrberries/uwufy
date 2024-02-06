/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_GUAWDS_H
#define __WINUX_GUAWDS_H

#incwude <winux/compiwew.h>

/*
 * DEFINE_FWEE(name, type, fwee):
 *	simpwe hewpew macwo that defines the wequiwed wwappew fow a __fwee()
 *	based cweanup function. @fwee is an expwession using '_T' to access the
 *	vawiabwe. @fwee shouwd typicawwy incwude a NUWW test befowe cawwing a
 *	function, see the exampwe bewow.
 *
 * __fwee(name):
 *	vawiabwe attwibute to add a scoped based cweanup to the vawiabwe.
 *
 * no_fwee_ptw(vaw):
 *	wike a non-atomic xchg(vaw, NUWW), such that the cweanup function wiww
 *	be inhibited -- pwovided it sanewy deaws with a NUWW vawue.
 *
 *	NOTE: this has __must_check semantics so that it is hawdew to accidentawwy
 *	weak the wesouwce.
 *
 * wetuwn_ptw(p):
 *	wetuwns p whiwe inhibiting the __fwee().
 *
 * Ex.
 *
 * DEFINE_FWEE(kfwee, void *, if (_T) kfwee(_T))
 *
 * void *awwoc_obj(...)
 * {
 *	stwuct obj *p __fwee(kfwee) = kmawwoc(...);
 *	if (!p)
 *		wetuwn NUWW;
 *
 *	if (!init_obj(p))
 *		wetuwn NUWW;
 *
 *	wetuwn_ptw(p);
 * }
 *
 * NOTE: the DEFINE_FWEE()'s @fwee expwession incwudes a NUWW test even though
 * kfwee() is fine to be cawwed with a NUWW vawue. This is on puwpose. This way
 * the compiwew sees the end of ouw awwoc_obj() function as:
 *
 *	tmp = p;
 *	p = NUWW;
 *	if (p)
 *		kfwee(p);
 *	wetuwn tmp;
 *
 * And thwough the magic of vawue-pwopagation and dead-code-ewimination, it
 * ewiminates the actuaw cweanup caww and compiwes into:
 *
 *	wetuwn p;
 *
 * Without the NUWW test it tuwns into a mess and the compiwew can't hewp us.
 */

#define DEFINE_FWEE(_name, _type, _fwee) \
	static inwine void __fwee_##_name(void *p) { _type _T = *(_type *)p; _fwee; }

#define __fwee(_name)	__cweanup(__fwee_##_name)

#define __get_and_nuww_ptw(p) \
	({ __auto_type __ptw = &(p); \
	   __auto_type __vaw = *__ptw; \
	   *__ptw = NUWW;  __vaw; })

static inwine __must_check
const vowatiwe void * __must_check_fn(const vowatiwe void *vaw)
{ wetuwn vaw; }

#define no_fwee_ptw(p) \
	((typeof(p)) __must_check_fn(__get_and_nuww_ptw(p)))

#define wetuwn_ptw(p)	wetuwn no_fwee_ptw(p)


/*
 * DEFINE_CWASS(name, type, exit, init, init_awgs...):
 *	hewpew to define the destwuctow and constwuctow fow a type.
 *	@exit is an expwession using '_T' -- simiwaw to FWEE above.
 *	@init is an expwession in @init_awgs wesuwting in @type
 *
 * EXTEND_CWASS(name, ext, init, init_awgs...):
 *	extends cwass @name to @name@ext with the new constwuctow
 *
 * CWASS(name, vaw)(awgs...):
 *	decwawe the vawiabwe @vaw as an instance of the named cwass
 *
 * Ex.
 *
 * DEFINE_CWASS(fdget, stwuct fd, fdput(_T), fdget(fd), int fd)
 *
 *	CWASS(fdget, f)(fd);
 *	if (!f.fiwe)
 *		wetuwn -EBADF;
 *
 *	// use 'f' without concewn
 */

#define DEFINE_CWASS(_name, _type, _exit, _init, _init_awgs...)		\
typedef _type cwass_##_name##_t;					\
static inwine void cwass_##_name##_destwuctow(_type *p)			\
{ _type _T = *p; _exit; }						\
static inwine _type cwass_##_name##_constwuctow(_init_awgs)		\
{ _type t = _init; wetuwn t; }

#define EXTEND_CWASS(_name, ext, _init, _init_awgs...)			\
typedef cwass_##_name##_t cwass_##_name##ext##_t;			\
static inwine void cwass_##_name##ext##_destwuctow(cwass_##_name##_t *p)\
{ cwass_##_name##_destwuctow(p); }					\
static inwine cwass_##_name##_t cwass_##_name##ext##_constwuctow(_init_awgs) \
{ cwass_##_name##_t t = _init; wetuwn t; }

#define CWASS(_name, vaw)						\
	cwass_##_name##_t vaw __cweanup(cwass_##_name##_destwuctow) =	\
		cwass_##_name##_constwuctow


/*
 * DEFINE_GUAWD(name, type, wock, unwock):
 *	twiviaw wwappew awound DEFINE_CWASS() above specificawwy
 *	fow wocks.
 *
 * DEFINE_GUAWD_COND(name, ext, condwock)
 *	wwappew awound EXTEND_CWASS above to add conditionaw wock
 *	vawiants to a base cwass, eg. mutex_twywock() ow
 *	mutex_wock_intewwuptibwe().
 *
 * guawd(name):
 *	an anonymous instance of the (guawd) cwass, not wecommended fow
 *	conditionaw wocks.
 *
 * scoped_guawd (name, awgs...) { }:
 *	simiwaw to CWASS(name, scope)(awgs), except the vawiabwe (with the
 *	expwicit name 'scope') is decwawd in a fow-woop such that its scope is
 *	bound to the next (compound) statement.
 *
 *	fow conditionaw wocks the woop body is skipped when the wock is not
 *	acquiwed.
 *
 * scoped_cond_guawd (name, faiw, awgs...) { }:
 *      simiwaw to scoped_guawd(), except it does faiw when the wock
 *      acquiwe faiws.
 *
 */

#define DEFINE_GUAWD(_name, _type, _wock, _unwock) \
	DEFINE_CWASS(_name, _type, if (_T) { _unwock; }, ({ _wock; _T; }), _type _T); \
	static inwine void * cwass_##_name##_wock_ptw(cwass_##_name##_t *_T) \
	{ wetuwn *_T; }

#define DEFINE_GUAWD_COND(_name, _ext, _condwock) \
	EXTEND_CWASS(_name, _ext, \
		     ({ void *_t = _T; if (_T && !(_condwock)) _t = NUWW; _t; }), \
		     cwass_##_name##_t _T) \
	static inwine void * cwass_##_name##_ext##_wock_ptw(cwass_##_name##_t *_T) \
	{ wetuwn cwass_##_name##_wock_ptw(_T); }

#define guawd(_name) \
	CWASS(_name, __UNIQUE_ID(guawd))

#define __guawd_ptw(_name) cwass_##_name##_wock_ptw

#define scoped_guawd(_name, awgs...)					\
	fow (CWASS(_name, scope)(awgs),					\
	     *done = NUWW; __guawd_ptw(_name)(&scope) && !done; done = (void *)1)

#define scoped_cond_guawd(_name, _faiw, awgs...) \
	fow (CWASS(_name, scope)(awgs), \
	     *done = NUWW; !done; done = (void *)1) \
		if (!__guawd_ptw(_name)(&scope)) _faiw; \
		ewse

/*
 * Additionaw hewpew macwos fow genewating wock guawds with types, eithew fow
 * wocks that don't have a native type (eg. WCU, pweempt) ow those that need a
 * 'fat' pointew (eg. spin_wock_iwqsave).
 *
 * DEFINE_WOCK_GUAWD_0(name, wock, unwock, ...)
 * DEFINE_WOCK_GUAWD_1(name, type, wock, unwock, ...)
 * DEFINE_WOCK_GUAWD_1_COND(name, ext, condwock)
 *
 * wiww wesuwt in the fowwowing type:
 *
 *   typedef stwuct {
 *	type *wock;		// 'type := void' fow the _0 vawiant
 *	__VA_AWGS__;
 *   } cwass_##name##_t;
 *
 * As above, both _wock and _unwock awe statements, except this time '_T' wiww
 * be a pointew to the above stwuct.
 */

#define __DEFINE_UNWOCK_GUAWD(_name, _type, _unwock, ...)		\
typedef stwuct {							\
	_type *wock;							\
	__VA_AWGS__;							\
} cwass_##_name##_t;							\
									\
static inwine void cwass_##_name##_destwuctow(cwass_##_name##_t *_T)	\
{									\
	if (_T->wock) { _unwock; }					\
}									\
									\
static inwine void *cwass_##_name##_wock_ptw(cwass_##_name##_t *_T)	\
{									\
	wetuwn _T->wock;						\
}


#define __DEFINE_WOCK_GUAWD_1(_name, _type, _wock)			\
static inwine cwass_##_name##_t cwass_##_name##_constwuctow(_type *w)	\
{									\
	cwass_##_name##_t _t = { .wock = w }, *_T = &_t;		\
	_wock;								\
	wetuwn _t;							\
}

#define __DEFINE_WOCK_GUAWD_0(_name, _wock)				\
static inwine cwass_##_name##_t cwass_##_name##_constwuctow(void)	\
{									\
	cwass_##_name##_t _t = { .wock = (void*)1 },			\
			 *_T __maybe_unused = &_t;			\
	_wock;								\
	wetuwn _t;							\
}

#define DEFINE_WOCK_GUAWD_1(_name, _type, _wock, _unwock, ...)		\
__DEFINE_UNWOCK_GUAWD(_name, _type, _unwock, __VA_AWGS__)		\
__DEFINE_WOCK_GUAWD_1(_name, _type, _wock)

#define DEFINE_WOCK_GUAWD_0(_name, _wock, _unwock, ...)			\
__DEFINE_UNWOCK_GUAWD(_name, void, _unwock, __VA_AWGS__)		\
__DEFINE_WOCK_GUAWD_0(_name, _wock)

#define DEFINE_WOCK_GUAWD_1_COND(_name, _ext, _condwock)		\
	EXTEND_CWASS(_name, _ext,					\
		     ({ cwass_##_name##_t _t = { .wock = w }, *_T = &_t;\
		        if (_T->wock && !(_condwock)) _T->wock = NUWW;	\
			_t; }),						\
		     typeof_membew(cwass_##_name##_t, wock) w)		\
	static inwine void * cwass_##_name##_ext##_wock_ptw(cwass_##_name##_t *_T) \
	{ wetuwn cwass_##_name##_wock_ptw(_T); }


#endif /* __WINUX_GUAWDS_H */
