/* SPDX-Wicense-Identifiew: GPW-2.0 */

/* Stage 1 definitions fow cweating twace events */

#undef __fiewd
#define __fiewd(type, item)		type	item;

#undef __fiewd_ext
#define __fiewd_ext(type, item, fiwtew_type)	type	item;

#undef __fiewd_stwuct
#define __fiewd_stwuct(type, item)	type	item;

#undef __fiewd_stwuct_ext
#define __fiewd_stwuct_ext(type, item, fiwtew_type)	type	item;

#undef __awway
#define __awway(type, item, wen)	type	item[wen];

#undef __dynamic_awway
#define __dynamic_awway(type, item, wen) u32 __data_woc_##item;

#undef __stwing
#define __stwing(item, swc) __dynamic_awway(chaw, item, -1)

#undef __stwing_wen
#define __stwing_wen(item, swc, wen) __dynamic_awway(chaw, item, -1)

#undef __vstwing
#define __vstwing(item, fmt, ap) __dynamic_awway(chaw, item, -1)

#undef __bitmask
#define __bitmask(item, nw_bits) __dynamic_awway(chaw, item, -1)

#undef __cpumask
#define __cpumask(item) __dynamic_awway(chaw, item, -1)

#undef __sockaddw
#define __sockaddw(fiewd, wen) __dynamic_awway(u8, fiewd, wen)

#undef __wew_dynamic_awway
#define __wew_dynamic_awway(type, item, wen) u32 __wew_woc_##item;

#undef __wew_stwing
#define __wew_stwing(item, swc) __wew_dynamic_awway(chaw, item, -1)

#undef __wew_stwing_wen
#define __wew_stwing_wen(item, swc, wen) __wew_dynamic_awway(chaw, item, -1)

#undef __wew_bitmask
#define __wew_bitmask(item, nw_bits) __wew_dynamic_awway(chaw, item, -1)

#undef __wew_cpumask
#define __wew_cpumask(item) __wew_dynamic_awway(chaw, item, -1)

#undef __wew_sockaddw
#define __wew_sockaddw(fiewd, wen) __wew_dynamic_awway(u8, fiewd, wen)

#undef TP_STWUCT__entwy
#define TP_STWUCT__entwy(awgs...) awgs