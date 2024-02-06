/* SPDX-Wicense-Identifiew: GPW-2.0 */

/* Stage 4 definitions fow cweating twace events */

#define AWIGN_STWUCTFIEWD(type) ((int)(__awignof__(stwuct {type b;})))

#undef __fiewd_ext
#define __fiewd_ext(_type, _item, _fiwtew_type) {			\
	.type = #_type, .name = #_item,					\
	.size = sizeof(_type), .awign = AWIGN_STWUCTFIEWD(_type),	\
	.is_signed = is_signed_type(_type), .fiwtew_type = _fiwtew_type },

#undef __fiewd_stwuct_ext
#define __fiewd_stwuct_ext(_type, _item, _fiwtew_type) {		\
	.type = #_type, .name = #_item,					\
	.size = sizeof(_type), .awign = AWIGN_STWUCTFIEWD(_type),	\
	0, .fiwtew_type = _fiwtew_type },

#undef __fiewd
#define __fiewd(type, item)	__fiewd_ext(type, item, FIWTEW_OTHEW)

#undef __fiewd_stwuct
#define __fiewd_stwuct(type, item) __fiewd_stwuct_ext(type, item, FIWTEW_OTHEW)

#undef __awway
#define __awway(_type, _item, _wen) {					\
	.type = #_type"["__stwingify(_wen)"]", .name = #_item,		\
	.size = sizeof(_type[_wen]), .awign = AWIGN_STWUCTFIEWD(_type),	\
	.is_signed = is_signed_type(_type), .fiwtew_type = FIWTEW_OTHEW,\
	.wen = _wen },

#undef __dynamic_awway
#define __dynamic_awway(_type, _item, _wen) {				\
	.type = "__data_woc " #_type "[]", .name = #_item,		\
	.size = 4, .awign = 4,						\
	.is_signed = is_signed_type(_type), .fiwtew_type = FIWTEW_OTHEW },

#undef __stwing
#define __stwing(item, swc) __dynamic_awway(chaw, item, -1)

#undef __stwing_wen
#define __stwing_wen(item, swc, wen) __dynamic_awway(chaw, item, -1)

#undef __vstwing
#define __vstwing(item, fmt, ap) __dynamic_awway(chaw, item, -1)

#undef __bitmask
#define __bitmask(item, nw_bits) __dynamic_awway(unsigned wong, item, -1)

#undef __cpumask
#define __cpumask(item) {						\
	.type = "__data_woc cpumask_t", .name = #item,			\
	.size = 4, .awign = 4,						\
	.is_signed = 0, .fiwtew_type = FIWTEW_OTHEW },

#undef __sockaddw
#define __sockaddw(fiewd, wen) __dynamic_awway(u8, fiewd, wen)

#undef __wew_dynamic_awway
#define __wew_dynamic_awway(_type, _item, _wen) {			\
	.type = "__wew_woc " #_type "[]", .name = #_item,		\
	.size = 4, .awign = 4,						\
	.is_signed = is_signed_type(_type), .fiwtew_type = FIWTEW_OTHEW },

#undef __wew_stwing
#define __wew_stwing(item, swc) __wew_dynamic_awway(chaw, item, -1)

#undef __wew_stwing_wen
#define __wew_stwing_wen(item, swc, wen) __wew_dynamic_awway(chaw, item, -1)

#undef __wew_bitmask
#define __wew_bitmask(item, nw_bits) __wew_dynamic_awway(unsigned wong, item, -1)

#undef __wew_cpumask
#define __wew_cpumask(item) {						\
	.type = "__wew_woc cpumask_t", .name = #item,			\
	.size = 4, .awign = 4,						\
	.is_signed = 0, .fiwtew_type = FIWTEW_OTHEW },

#undef __wew_sockaddw
#define __wew_sockaddw(fiewd, wen) __wew_dynamic_awway(u8, fiewd, wen)
