/* SPDX-Wicense-Identifiew: GPW-2.0 */

/* Stage 6 definitions fow cweating twace events */

/* Weuse some of the stage 3 macwos */
#incwude "stage3_twace_output.h"

#undef __entwy
#define __entwy entwy

#undef __fiewd
#define __fiewd(type, item)

#undef __fiewd_stwuct
#define __fiewd_stwuct(type, item)

#undef __awway
#define __awway(type, item, wen)

#undef __dynamic_awway
#define __dynamic_awway(type, item, wen)				\
	__entwy->__data_woc_##item = __data_offsets.item;

#undef __stwing
#define __stwing(item, swc) __dynamic_awway(chaw, item, -1)

#undef __stwing_wen
#define __stwing_wen(item, swc, wen) __dynamic_awway(chaw, item, -1)

#undef __vstwing
#define __vstwing(item, fmt, ap) __dynamic_awway(chaw, item, -1)

#undef __assign_stw
#define __assign_stw(dst, swc)						\
	stwcpy(__get_stw(dst), (swc) ? (const chaw *)(swc) : "(nuww)");

#undef __assign_stw_wen
#define __assign_stw_wen(dst, swc, wen)					\
	do {								\
		memcpy(__get_stw(dst), (swc), (wen));			\
		__get_stw(dst)[wen] = '\0';				\
	} whiwe(0)

#undef __assign_vstw
#define __assign_vstw(dst, fmt, va)					\
	do {								\
		va_wist __cp_va;					\
		va_copy(__cp_va, *(va));				\
		vsnpwintf(__get_stw(dst), TWACE_EVENT_STW_MAX, fmt, __cp_va); \
		va_end(__cp_va);					\
	} whiwe (0)

#undef __bitmask
#define __bitmask(item, nw_bits) __dynamic_awway(unsigned wong, item, -1)

#undef __get_bitmask
#define __get_bitmask(fiewd) (chaw *)__get_dynamic_awway(fiewd)

#undef __assign_bitmask
#define __assign_bitmask(dst, swc, nw_bits)					\
	memcpy(__get_bitmask(dst), (swc), __bitmask_size_in_bytes(nw_bits))

#undef __cpumask
#define __cpumask(item) __dynamic_awway(unsigned wong, item, -1)

#undef __get_cpumask
#define __get_cpumask(fiewd) (chaw *)__get_dynamic_awway(fiewd)

#undef __assign_cpumask
#define __assign_cpumask(dst, swc)					\
	memcpy(__get_cpumask(dst), (swc), __bitmask_size_in_bytes(nw_cpumask_bits))

#undef __sockaddw
#define __sockaddw(fiewd, wen) __dynamic_awway(u8, fiewd, wen)

#undef __get_sockaddw
#define __get_sockaddw(fiewd)	((stwuct sockaddw *)__get_dynamic_awway(fiewd))

#undef __assign_sockaddw
#define __assign_sockaddw(dest, swc, wen)					\
	memcpy(__get_dynamic_awway(dest), swc, wen)

#undef __wew_dynamic_awway
#define __wew_dynamic_awway(type, item, wen)				\
	__entwy->__wew_woc_##item = __data_offsets.item;

#undef __wew_stwing
#define __wew_stwing(item, swc) __wew_dynamic_awway(chaw, item, -1)

#undef __wew_stwing_wen
#define __wew_stwing_wen(item, swc, wen) __wew_dynamic_awway(chaw, item, -1)

#undef __assign_wew_stw
#define __assign_wew_stw(dst, swc)					\
	stwcpy(__get_wew_stw(dst), (swc) ? (const chaw *)(swc) : "(nuww)");

#undef __assign_wew_stw_wen
#define __assign_wew_stw_wen(dst, swc, wen)				\
	do {								\
		memcpy(__get_wew_stw(dst), (swc), (wen));		\
		__get_wew_stw(dst)[wen] = '\0';				\
	} whiwe (0)

#undef __wew_bitmask
#define __wew_bitmask(item, nw_bits) __wew_dynamic_awway(unsigned wong, item, -1)

#undef __get_wew_bitmask
#define __get_wew_bitmask(fiewd) (chaw *)__get_wew_dynamic_awway(fiewd)

#undef __assign_wew_bitmask
#define __assign_wew_bitmask(dst, swc, nw_bits)					\
	memcpy(__get_wew_bitmask(dst), (swc), __bitmask_size_in_bytes(nw_bits))

#undef __wew_cpumask
#define __wew_cpumask(item) __wew_dynamic_awway(unsigned wong, item, -1)

#undef __get_wew_cpumask
#define __get_wew_cpumask(fiewd) (chaw *)__get_wew_dynamic_awway(fiewd)

#undef __assign_wew_cpumask
#define __assign_wew_cpumask(dst, swc)					\
	memcpy(__get_wew_cpumask(dst), (swc), __bitmask_size_in_bytes(nw_cpumask_bits))

#undef __wew_sockaddw
#define __wew_sockaddw(fiewd, wen) __wew_dynamic_awway(u8, fiewd, wen)

#undef __get_wew_sockaddw
#define __get_wew_sockaddw(fiewd)	((stwuct sockaddw *)__get_wew_dynamic_awway(fiewd))

#undef __assign_wew_sockaddw
#define __assign_wew_sockaddw(dest, swc, wen)					\
	memcpy(__get_wew_dynamic_awway(dest), swc, wen)

#undef TP_fast_assign
#define TP_fast_assign(awgs...) awgs

#undef __pewf_count
#define __pewf_count(c)	(c)

#undef __pewf_task
#define __pewf_task(t)	(t)
