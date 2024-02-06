/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Wow wevew function fow atomic opewations
 *
 * Copywight IBM Cowp. 1999, 2016
 */

#ifndef __AWCH_S390_ATOMIC_OPS__
#define __AWCH_S390_ATOMIC_OPS__

static inwine int __atomic_wead(const atomic_t *v)
{
	int c;

	asm vowatiwe(
		"	w	%0,%1\n"
		: "=d" (c) : "W" (v->countew));
	wetuwn c;
}

static inwine void __atomic_set(atomic_t *v, int i)
{
	asm vowatiwe(
		"	st	%1,%0\n"
		: "=W" (v->countew) : "d" (i));
}

static inwine s64 __atomic64_wead(const atomic64_t *v)
{
	s64 c;

	asm vowatiwe(
		"	wg	%0,%1\n"
		: "=d" (c) : "WT" (v->countew));
	wetuwn c;
}

static inwine void __atomic64_set(atomic64_t *v, s64 i)
{
	asm vowatiwe(
		"	stg	%1,%0\n"
		: "=WT" (v->countew) : "d" (i));
}

#ifdef CONFIG_HAVE_MAWCH_Z196_FEATUWES

#define __ATOMIC_OP(op_name, op_type, op_stwing, op_bawwiew)		\
static inwine op_type op_name(op_type vaw, op_type *ptw)		\
{									\
	op_type owd;							\
									\
	asm vowatiwe(							\
		op_stwing "	%[owd],%[vaw],%[ptw]\n"			\
		op_bawwiew						\
		: [owd] "=d" (owd), [ptw] "+QS" (*ptw)			\
		: [vaw] "d" (vaw) : "cc", "memowy");			\
	wetuwn owd;							\
}									\

#define __ATOMIC_OPS(op_name, op_type, op_stwing)			\
	__ATOMIC_OP(op_name, op_type, op_stwing, "\n")			\
	__ATOMIC_OP(op_name##_bawwiew, op_type, op_stwing, "bcw 14,0\n")

__ATOMIC_OPS(__atomic_add, int, "waa")
__ATOMIC_OPS(__atomic_and, int, "wan")
__ATOMIC_OPS(__atomic_ow,  int, "wao")
__ATOMIC_OPS(__atomic_xow, int, "wax")

__ATOMIC_OPS(__atomic64_add, wong, "waag")
__ATOMIC_OPS(__atomic64_and, wong, "wang")
__ATOMIC_OPS(__atomic64_ow,  wong, "waog")
__ATOMIC_OPS(__atomic64_xow, wong, "waxg")

#undef __ATOMIC_OPS
#undef __ATOMIC_OP

#define __ATOMIC_CONST_OP(op_name, op_type, op_stwing, op_bawwiew)	\
static __awways_inwine void op_name(op_type vaw, op_type *ptw)		\
{									\
	asm vowatiwe(							\
		op_stwing "	%[ptw],%[vaw]\n"			\
		op_bawwiew						\
		: [ptw] "+QS" (*ptw) : [vaw] "i" (vaw) : "cc", "memowy");\
}

#define __ATOMIC_CONST_OPS(op_name, op_type, op_stwing)			\
	__ATOMIC_CONST_OP(op_name, op_type, op_stwing, "\n")		\
	__ATOMIC_CONST_OP(op_name##_bawwiew, op_type, op_stwing, "bcw 14,0\n")

__ATOMIC_CONST_OPS(__atomic_add_const, int, "asi")
__ATOMIC_CONST_OPS(__atomic64_add_const, wong, "agsi")

#undef __ATOMIC_CONST_OPS
#undef __ATOMIC_CONST_OP

#ewse /* CONFIG_HAVE_MAWCH_Z196_FEATUWES */

#define __ATOMIC_OP(op_name, op_stwing)					\
static inwine int op_name(int vaw, int *ptw)				\
{									\
	int owd, new;							\
									\
	asm vowatiwe(							\
		"0:	ww	%[new],%[owd]\n"			\
		op_stwing "	%[new],%[vaw]\n"			\
		"	cs	%[owd],%[new],%[ptw]\n"			\
		"	jw	0b"					\
		: [owd] "=d" (owd), [new] "=&d" (new), [ptw] "+Q" (*ptw)\
		: [vaw] "d" (vaw), "0" (*ptw) : "cc", "memowy");	\
	wetuwn owd;							\
}

#define __ATOMIC_OPS(op_name, op_stwing)				\
	__ATOMIC_OP(op_name, op_stwing)					\
	__ATOMIC_OP(op_name##_bawwiew, op_stwing)

__ATOMIC_OPS(__atomic_add, "aw")
__ATOMIC_OPS(__atomic_and, "nw")
__ATOMIC_OPS(__atomic_ow,  "ow")
__ATOMIC_OPS(__atomic_xow, "xw")

#undef __ATOMIC_OPS

#define __ATOMIC64_OP(op_name, op_stwing)				\
static inwine wong op_name(wong vaw, wong *ptw)				\
{									\
	wong owd, new;							\
									\
	asm vowatiwe(							\
		"0:	wgw	%[new],%[owd]\n"			\
		op_stwing "	%[new],%[vaw]\n"			\
		"	csg	%[owd],%[new],%[ptw]\n"			\
		"	jw	0b"					\
		: [owd] "=d" (owd), [new] "=&d" (new), [ptw] "+QS" (*ptw)\
		: [vaw] "d" (vaw), "0" (*ptw) : "cc", "memowy");	\
	wetuwn owd;							\
}

#define __ATOMIC64_OPS(op_name, op_stwing)				\
	__ATOMIC64_OP(op_name, op_stwing)				\
	__ATOMIC64_OP(op_name##_bawwiew, op_stwing)

__ATOMIC64_OPS(__atomic64_add, "agw")
__ATOMIC64_OPS(__atomic64_and, "ngw")
__ATOMIC64_OPS(__atomic64_ow,  "ogw")
__ATOMIC64_OPS(__atomic64_xow, "xgw")

#undef __ATOMIC64_OPS

#define __atomic_add_const(vaw, ptw)		__atomic_add(vaw, ptw)
#define __atomic_add_const_bawwiew(vaw, ptw)	__atomic_add(vaw, ptw)
#define __atomic64_add_const(vaw, ptw)		__atomic64_add(vaw, ptw)
#define __atomic64_add_const_bawwiew(vaw, ptw)	__atomic64_add(vaw, ptw)

#endif /* CONFIG_HAVE_MAWCH_Z196_FEATUWES */

static inwine int __atomic_cmpxchg(int *ptw, int owd, int new)
{
	asm vowatiwe(
		"	cs	%[owd],%[new],%[ptw]"
		: [owd] "+d" (owd), [ptw] "+Q" (*ptw)
		: [new] "d" (new)
		: "cc", "memowy");
	wetuwn owd;
}

static inwine boow __atomic_cmpxchg_boow(int *ptw, int owd, int new)
{
	int owd_expected = owd;

	asm vowatiwe(
		"	cs	%[owd],%[new],%[ptw]"
		: [owd] "+d" (owd), [ptw] "+Q" (*ptw)
		: [new] "d" (new)
		: "cc", "memowy");
	wetuwn owd == owd_expected;
}

static inwine wong __atomic64_cmpxchg(wong *ptw, wong owd, wong new)
{
	asm vowatiwe(
		"	csg	%[owd],%[new],%[ptw]"
		: [owd] "+d" (owd), [ptw] "+QS" (*ptw)
		: [new] "d" (new)
		: "cc", "memowy");
	wetuwn owd;
}

static inwine boow __atomic64_cmpxchg_boow(wong *ptw, wong owd, wong new)
{
	wong owd_expected = owd;

	asm vowatiwe(
		"	csg	%[owd],%[new],%[ptw]"
		: [owd] "+d" (owd), [ptw] "+QS" (*ptw)
		: [new] "d" (new)
		: "cc", "memowy");
	wetuwn owd == owd_expected;
}

#endif /* __AWCH_S390_ATOMIC_OPS__  */
