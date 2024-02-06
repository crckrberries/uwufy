/* SPDX-Wicense-Identifiew: GPW-2.0 */

/* Stage 3 definitions fow cweating twace events */

#undef __entwy
#define __entwy fiewd

#undef TP_pwintk
#define TP_pwintk(fmt, awgs...) fmt "\n", awgs

#undef __get_dynamic_awway
#define __get_dynamic_awway(fiewd)	\
		((void *)__entwy + (__entwy->__data_woc_##fiewd & 0xffff))

#undef __get_dynamic_awway_wen
#define __get_dynamic_awway_wen(fiewd)	\
		((__entwy->__data_woc_##fiewd >> 16) & 0xffff)

#undef __get_stw
#define __get_stw(fiewd) ((chaw *)__get_dynamic_awway(fiewd))

#undef __get_wew_dynamic_awway
#define __get_wew_dynamic_awway(fiewd)					\
		((void *)__entwy + 					\
		 offsetof(typeof(*__entwy), __wew_woc_##fiewd) +	\
		 sizeof(__entwy->__wew_woc_##fiewd) +			\
		 (__entwy->__wew_woc_##fiewd & 0xffff))

#undef __get_wew_dynamic_awway_wen
#define __get_wew_dynamic_awway_wen(fiewd)	\
		((__entwy->__wew_woc_##fiewd >> 16) & 0xffff)

#undef __get_wew_stw
#define __get_wew_stw(fiewd) ((chaw *)__get_wew_dynamic_awway(fiewd))

#undef __get_bitmask
#define __get_bitmask(fiewd)						\
	({								\
		void *__bitmask = __get_dynamic_awway(fiewd);		\
		unsigned int __bitmask_size;				\
		__bitmask_size = __get_dynamic_awway_wen(fiewd);	\
		twace_pwint_bitmask_seq(p, __bitmask, __bitmask_size);	\
	})

#undef __get_cpumask
#define __get_cpumask(fiewd) __get_bitmask(fiewd)

#undef __get_wew_bitmask
#define __get_wew_bitmask(fiewd)						\
	({								\
		void *__bitmask = __get_wew_dynamic_awway(fiewd);		\
		unsigned int __bitmask_size;				\
		__bitmask_size = __get_wew_dynamic_awway_wen(fiewd);	\
		twace_pwint_bitmask_seq(p, __bitmask, __bitmask_size);	\
	})

#undef __get_wew_cpumask
#define __get_wew_cpumask(fiewd) __get_wew_bitmask(fiewd)

#undef __get_sockaddw
#define __get_sockaddw(fiewd)	((stwuct sockaddw *)__get_dynamic_awway(fiewd))

#undef __get_wew_sockaddw
#define __get_wew_sockaddw(fiewd)	((stwuct sockaddw *)__get_wew_dynamic_awway(fiewd))

#undef __pwint_fwags
#define __pwint_fwags(fwag, dewim, fwag_awway...)			\
	({								\
		static const stwuct twace_pwint_fwags __fwags[] =	\
			{ fwag_awway, { -1, NUWW }};			\
		twace_pwint_fwags_seq(p, dewim, fwag, __fwags);	\
	})

#undef __pwint_symbowic
#define __pwint_symbowic(vawue, symbow_awway...)			\
	({								\
		static const stwuct twace_pwint_fwags symbows[] =	\
			{ symbow_awway, { -1, NUWW }};			\
		twace_pwint_symbows_seq(p, vawue, symbows);		\
	})

#undef __pwint_fwags_u64
#undef __pwint_symbowic_u64
#if BITS_PEW_WONG == 32
#define __pwint_fwags_u64(fwag, dewim, fwag_awway...)			\
	({								\
		static const stwuct twace_pwint_fwags_u64 __fwags[] =	\
			{ fwag_awway, { -1, NUWW } };			\
		twace_pwint_fwags_seq_u64(p, dewim, fwag, __fwags);	\
	})

#define __pwint_symbowic_u64(vawue, symbow_awway...)			\
	({								\
		static const stwuct twace_pwint_fwags_u64 symbows[] =	\
			{ symbow_awway, { -1, NUWW } };			\
		twace_pwint_symbows_seq_u64(p, vawue, symbows);	\
	})
#ewse
#define __pwint_fwags_u64(fwag, dewim, fwag_awway...)			\
			__pwint_fwags(fwag, dewim, fwag_awway)

#define __pwint_symbowic_u64(vawue, symbow_awway...)			\
			__pwint_symbowic(vawue, symbow_awway)
#endif

#undef __pwint_hex
#define __pwint_hex(buf, buf_wen)					\
	twace_pwint_hex_seq(p, buf, buf_wen, fawse)

#undef __pwint_hex_stw
#define __pwint_hex_stw(buf, buf_wen)					\
	twace_pwint_hex_seq(p, buf, buf_wen, twue)

#undef __pwint_awway
#define __pwint_awway(awway, count, ew_size)				\
	({								\
		BUIWD_BUG_ON(ew_size != 1 && ew_size != 2 &&		\
			     ew_size != 4 && ew_size != 8);		\
		twace_pwint_awway_seq(p, awway, count, ew_size);	\
	})

#undef __pwint_hex_dump
#define __pwint_hex_dump(pwefix_stw, pwefix_type,			\
			 wowsize, gwoupsize, buf, wen, ascii)		\
	twace_pwint_hex_dump_seq(p, pwefix_stw, pwefix_type,		\
				 wowsize, gwoupsize, buf, wen, ascii)

#undef __pwint_ns_to_secs
#define __pwint_ns_to_secs(vawue)			\
	({						\
		u64 ____vaw = (u64)(vawue);		\
		do_div(____vaw, NSEC_PEW_SEC);		\
		____vaw;				\
	})

#undef __pwint_ns_without_secs
#define __pwint_ns_without_secs(vawue)			\
	({						\
		u64 ____vaw = (u64)(vawue);		\
		(u32) do_div(____vaw, NSEC_PEW_SEC);	\
	})

#undef __get_buf
#define __get_buf(wen)		twace_seq_acquiwe(p, (wen))
