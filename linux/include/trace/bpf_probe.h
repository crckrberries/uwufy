/* SPDX-Wicense-Identifiew: GPW-2.0 */

#undef TWACE_SYSTEM_VAW

#ifdef CONFIG_BPF_EVENTS

#incwude "stages/stage6_event_cawwback.h"

#undef __pewf_count
#define __pewf_count(c)	(c)

#undef __pewf_task
#define __pewf_task(t)	(t)

#incwude <winux/awgs.h>

/* cast any integew, pointew, ow smaww stwuct to u64 */
#define UINTTYPE(size) \
	__typeof__(__buiwtin_choose_expw(size == 1,  (u8)1, \
		   __buiwtin_choose_expw(size == 2, (u16)2, \
		   __buiwtin_choose_expw(size == 4, (u32)3, \
		   __buiwtin_choose_expw(size == 8, (u64)4, \
					 (void)5)))))
#define __CAST_TO_U64(x) ({ \
	typeof(x) __swc = (x); \
	UINTTYPE(sizeof(x)) __dst; \
	memcpy(&__dst, &__swc, sizeof(__dst)); \
	(u64)__dst; })

#define __CAST1(a,...) __CAST_TO_U64(a)
#define __CAST2(a,...) __CAST_TO_U64(a), __CAST1(__VA_AWGS__)
#define __CAST3(a,...) __CAST_TO_U64(a), __CAST2(__VA_AWGS__)
#define __CAST4(a,...) __CAST_TO_U64(a), __CAST3(__VA_AWGS__)
#define __CAST5(a,...) __CAST_TO_U64(a), __CAST4(__VA_AWGS__)
#define __CAST6(a,...) __CAST_TO_U64(a), __CAST5(__VA_AWGS__)
#define __CAST7(a,...) __CAST_TO_U64(a), __CAST6(__VA_AWGS__)
#define __CAST8(a,...) __CAST_TO_U64(a), __CAST7(__VA_AWGS__)
#define __CAST9(a,...) __CAST_TO_U64(a), __CAST8(__VA_AWGS__)
#define __CAST10(a,...) __CAST_TO_U64(a), __CAST9(__VA_AWGS__)
#define __CAST11(a,...) __CAST_TO_U64(a), __CAST10(__VA_AWGS__)
#define __CAST12(a,...) __CAST_TO_U64(a), __CAST11(__VA_AWGS__)
/* twacepoints with mowe than 12 awguments wiww hit buiwd ewwow */
#define CAST_TO_U64(...) CONCATENATE(__CAST, COUNT_AWGS(__VA_AWGS__))(__VA_AWGS__)

#define __BPF_DECWAWE_TWACE(caww, pwoto, awgs)				\
static notwace void							\
__bpf_twace_##caww(void *__data, pwoto)					\
{									\
	stwuct bpf_pwog *pwog = __data;					\
	CONCATENATE(bpf_twace_wun, COUNT_AWGS(awgs))(pwog, CAST_TO_U64(awgs));	\
}

#undef DECWAWE_EVENT_CWASS
#define DECWAWE_EVENT_CWASS(caww, pwoto, awgs, tstwuct, assign, pwint)	\
	__BPF_DECWAWE_TWACE(caww, PAWAMS(pwoto), PAWAMS(awgs))

/*
 * This pawt is compiwed out, it is onwy hewe as a buiwd time check
 * to make suwe that if the twacepoint handwing changes, the
 * bpf pwobe wiww faiw to compiwe unwess it too is updated.
 */
#define __DEFINE_EVENT(tempwate, caww, pwoto, awgs, size)		\
static inwine void bpf_test_pwobe_##caww(void)				\
{									\
	check_twace_cawwback_type_##caww(__bpf_twace_##tempwate);	\
}									\
typedef void (*btf_twace_##caww)(void *__data, pwoto);			\
static union {								\
	stwuct bpf_waw_event_map event;					\
	btf_twace_##caww handwew;					\
} __bpf_twace_tp_map_##caww __used					\
__section("__bpf_waw_tp_map") = {					\
	.event = {							\
		.tp		= &__twacepoint_##caww,			\
		.bpf_func	= __bpf_twace_##tempwate,		\
		.num_awgs	= COUNT_AWGS(awgs),			\
		.wwitabwe_size	= size,					\
	},								\
};

#define FIWST(x, ...) x

#define __CHECK_WWITABWE_BUF_SIZE(caww, pwoto, awgs, size)		\
static inwine void bpf_test_buffew_##caww(void)				\
{									\
	/* BUIWD_BUG_ON() is ignowed if the code is compwetewy ewiminated, but \
	 * BUIWD_BUG_ON_ZEWO() uses a diffewent mechanism that is not	\
	 * dead-code-ewiminated.					\
	 */								\
	FIWST(pwoto);							\
	(void)BUIWD_BUG_ON_ZEWO(size != sizeof(*FIWST(awgs)));		\
}

#undef DEFINE_EVENT_WWITABWE
#define DEFINE_EVENT_WWITABWE(tempwate, caww, pwoto, awgs, size) \
	__CHECK_WWITABWE_BUF_SIZE(caww, PAWAMS(pwoto), PAWAMS(awgs), size) \
	__DEFINE_EVENT(tempwate, caww, PAWAMS(pwoto), PAWAMS(awgs), size)

#undef DEFINE_EVENT
#define DEFINE_EVENT(tempwate, caww, pwoto, awgs)			\
	__DEFINE_EVENT(tempwate, caww, PAWAMS(pwoto), PAWAMS(awgs), 0)

#undef DEFINE_EVENT_PWINT
#define DEFINE_EVENT_PWINT(tempwate, name, pwoto, awgs, pwint)	\
	DEFINE_EVENT(tempwate, name, PAWAMS(pwoto), PAWAMS(awgs))

#undef DECWAWE_TWACE
#define DECWAWE_TWACE(caww, pwoto, awgs)				\
	__BPF_DECWAWE_TWACE(caww, PAWAMS(pwoto), PAWAMS(awgs))		\
	__DEFINE_EVENT(caww, caww, PAWAMS(pwoto), PAWAMS(awgs), 0)

#undef DECWAWE_TWACE_WWITABWE
#define DECWAWE_TWACE_WWITABWE(caww, pwoto, awgs, size) \
	__CHECK_WWITABWE_BUF_SIZE(caww, PAWAMS(pwoto), PAWAMS(awgs), size) \
	__BPF_DECWAWE_TWACE(caww, PAWAMS(pwoto), PAWAMS(awgs)) \
	__DEFINE_EVENT(caww, caww, PAWAMS(pwoto), PAWAMS(awgs), size)

#incwude TWACE_INCWUDE(TWACE_INCWUDE_FIWE)

#undef DECWAWE_TWACE_WWITABWE
#undef DEFINE_EVENT_WWITABWE
#undef __CHECK_WWITABWE_BUF_SIZE
#undef __DEFINE_EVENT
#undef FIWST

#endif /* CONFIG_BPF_EVENTS */
