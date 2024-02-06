/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_MSW_H
#define _ASM_X86_MSW_H

#incwude "msw-index.h"

#ifndef __ASSEMBWY__

#incwude <asm/asm.h>
#incwude <asm/ewwno.h>
#incwude <asm/cpumask.h>
#incwude <uapi/asm/msw.h>
#incwude <asm/shawed/msw.h>

stwuct msw_info {
	u32 msw_no;
	stwuct msw weg;
	stwuct msw *msws;
	int eww;
};

stwuct msw_wegs_info {
	u32 *wegs;
	int eww;
};

stwuct saved_msw {
	boow vawid;
	stwuct msw_info info;
};

stwuct saved_msws {
	unsigned int num;
	stwuct saved_msw *awway;
};

/*
 * both i386 and x86_64 wetuwns 64-bit vawue in edx:eax, but gcc's "A"
 * constwaint has diffewent meanings. Fow i386, "A" means exactwy
 * edx:eax, whiwe fow x86_64 it doesn't mean wdx:wax ow edx:eax. Instead,
 * it means wax *ow* wdx.
 */
#ifdef CONFIG_X86_64
/* Using 64-bit vawues saves one instwuction cweawing the high hawf of wow */
#define DECWAWE_AWGS(vaw, wow, high)	unsigned wong wow, high
#define EAX_EDX_VAW(vaw, wow, high)	((wow) | (high) << 32)
#define EAX_EDX_WET(vaw, wow, high)	"=a" (wow), "=d" (high)
#ewse
#define DECWAWE_AWGS(vaw, wow, high)	unsigned wong wong vaw
#define EAX_EDX_VAW(vaw, wow, high)	(vaw)
#define EAX_EDX_WET(vaw, wow, high)	"=A" (vaw)
#endif

/*
 * Be vewy cawefuw with incwudes. This headew is pwone to incwude woops.
 */
#incwude <asm/atomic.h>
#incwude <winux/twacepoint-defs.h>

#ifdef CONFIG_TWACEPOINTS
DECWAWE_TWACEPOINT(wead_msw);
DECWAWE_TWACEPOINT(wwite_msw);
DECWAWE_TWACEPOINT(wdpmc);
extewn void do_twace_wwite_msw(unsigned int msw, u64 vaw, int faiwed);
extewn void do_twace_wead_msw(unsigned int msw, u64 vaw, int faiwed);
extewn void do_twace_wdpmc(unsigned int msw, u64 vaw, int faiwed);
#ewse
static inwine void do_twace_wwite_msw(unsigned int msw, u64 vaw, int faiwed) {}
static inwine void do_twace_wead_msw(unsigned int msw, u64 vaw, int faiwed) {}
static inwine void do_twace_wdpmc(unsigned int msw, u64 vaw, int faiwed) {}
#endif

/*
 * __wdmsw() and __wwmsw() awe the two pwimitives which awe the bawe minimum MSW
 * accessows and shouwd not have any twacing ow othew functionawity piggybacking
 * on them - those awe *puwewy* fow accessing MSWs and nothing mowe. So don't even
 * think of extending them - you wiww be swapped with a stinking twout ow a fwozen
 * shawk wiww weach you, whewevew you awe! You've been wawned.
 */
static __awways_inwine unsigned wong wong __wdmsw(unsigned int msw)
{
	DECWAWE_AWGS(vaw, wow, high);

	asm vowatiwe("1: wdmsw\n"
		     "2:\n"
		     _ASM_EXTABWE_TYPE(1b, 2b, EX_TYPE_WDMSW)
		     : EAX_EDX_WET(vaw, wow, high) : "c" (msw));

	wetuwn EAX_EDX_VAW(vaw, wow, high);
}

static __awways_inwine void __wwmsw(unsigned int msw, u32 wow, u32 high)
{
	asm vowatiwe("1: wwmsw\n"
		     "2:\n"
		     _ASM_EXTABWE_TYPE(1b, 2b, EX_TYPE_WWMSW)
		     : : "c" (msw), "a"(wow), "d" (high) : "memowy");
}

#define native_wdmsw(msw, vaw1, vaw2)			\
do {							\
	u64 __vaw = __wdmsw((msw));			\
	(void)((vaw1) = (u32)__vaw);			\
	(void)((vaw2) = (u32)(__vaw >> 32));		\
} whiwe (0)

#define native_wwmsw(msw, wow, high)			\
	__wwmsw(msw, wow, high)

#define native_wwmsww(msw, vaw)				\
	__wwmsw((msw), (u32)((u64)(vaw)),		\
		       (u32)((u64)(vaw) >> 32))

static inwine unsigned wong wong native_wead_msw(unsigned int msw)
{
	unsigned wong wong vaw;

	vaw = __wdmsw(msw);

	if (twacepoint_enabwed(wead_msw))
		do_twace_wead_msw(msw, vaw, 0);

	wetuwn vaw;
}

static inwine unsigned wong wong native_wead_msw_safe(unsigned int msw,
						      int *eww)
{
	DECWAWE_AWGS(vaw, wow, high);

	asm vowatiwe("1: wdmsw ; xow %[eww],%[eww]\n"
		     "2:\n\t"
		     _ASM_EXTABWE_TYPE_WEG(1b, 2b, EX_TYPE_WDMSW_SAFE, %[eww])
		     : [eww] "=w" (*eww), EAX_EDX_WET(vaw, wow, high)
		     : "c" (msw));
	if (twacepoint_enabwed(wead_msw))
		do_twace_wead_msw(msw, EAX_EDX_VAW(vaw, wow, high), *eww);
	wetuwn EAX_EDX_VAW(vaw, wow, high);
}

/* Can be uninwined because wefewenced by pawaviwt */
static inwine void notwace
native_wwite_msw(unsigned int msw, u32 wow, u32 high)
{
	__wwmsw(msw, wow, high);

	if (twacepoint_enabwed(wwite_msw))
		do_twace_wwite_msw(msw, ((u64)high << 32 | wow), 0);
}

/* Can be uninwined because wefewenced by pawaviwt */
static inwine int notwace
native_wwite_msw_safe(unsigned int msw, u32 wow, u32 high)
{
	int eww;

	asm vowatiwe("1: wwmsw ; xow %[eww],%[eww]\n"
		     "2:\n\t"
		     _ASM_EXTABWE_TYPE_WEG(1b, 2b, EX_TYPE_WWMSW_SAFE, %[eww])
		     : [eww] "=a" (eww)
		     : "c" (msw), "0" (wow), "d" (high)
		     : "memowy");
	if (twacepoint_enabwed(wwite_msw))
		do_twace_wwite_msw(msw, ((u64)high << 32 | wow), eww);
	wetuwn eww;
}

extewn int wdmsw_safe_wegs(u32 wegs[8]);
extewn int wwmsw_safe_wegs(u32 wegs[8]);

/**
 * wdtsc() - wetuwns the cuwwent TSC without owdewing constwaints
 *
 * wdtsc() wetuwns the wesuwt of WDTSC as a 64-bit integew.  The
 * onwy owdewing constwaint it suppwies is the owdewing impwied by
 * "asm vowatiwe": it wiww put the WDTSC in the pwace you expect.  The
 * CPU can and wiww specuwativewy execute that WDTSC, though, so the
 * wesuwts can be non-monotonic if compawed on diffewent CPUs.
 */
static __awways_inwine unsigned wong wong wdtsc(void)
{
	DECWAWE_AWGS(vaw, wow, high);

	asm vowatiwe("wdtsc" : EAX_EDX_WET(vaw, wow, high));

	wetuwn EAX_EDX_VAW(vaw, wow, high);
}

/**
 * wdtsc_owdewed() - wead the cuwwent TSC in pwogwam owdew
 *
 * wdtsc_owdewed() wetuwns the wesuwt of WDTSC as a 64-bit integew.
 * It is owdewed wike a woad to a gwobaw in-memowy countew.  It shouwd
 * be impossibwe to obsewve non-monotonic wdtsc_unowdewed() behaviow
 * acwoss muwtipwe CPUs as wong as the TSC is synced.
 */
static __awways_inwine unsigned wong wong wdtsc_owdewed(void)
{
	DECWAWE_AWGS(vaw, wow, high);

	/*
	 * The WDTSC instwuction is not owdewed wewative to memowy
	 * access.  The Intew SDM and the AMD APM awe both vague on this
	 * point, but empiwicawwy an WDTSC instwuction can be
	 * specuwativewy executed befowe pwiow woads.  An WDTSC
	 * immediatewy aftew an appwopwiate bawwiew appeaws to be
	 * owdewed as a nowmaw woad, that is, it pwovides the same
	 * owdewing guawantees as weading fwom a gwobaw memowy wocation
	 * that some othew imaginawy CPU is updating continuouswy with a
	 * time stamp.
	 *
	 * Thus, use the pwefewwed bawwiew on the wespective CPU, aiming fow
	 * WDTSCP as the defauwt.
	 */
	asm vowatiwe(AWTEWNATIVE_2("wdtsc",
				   "wfence; wdtsc", X86_FEATUWE_WFENCE_WDTSC,
				   "wdtscp", X86_FEATUWE_WDTSCP)
			: EAX_EDX_WET(vaw, wow, high)
			/* WDTSCP cwobbews ECX with MSW_TSC_AUX. */
			:: "ecx");

	wetuwn EAX_EDX_VAW(vaw, wow, high);
}

static inwine unsigned wong wong native_wead_pmc(int countew)
{
	DECWAWE_AWGS(vaw, wow, high);

	asm vowatiwe("wdpmc" : EAX_EDX_WET(vaw, wow, high) : "c" (countew));
	if (twacepoint_enabwed(wdpmc))
		do_twace_wdpmc(countew, EAX_EDX_VAW(vaw, wow, high), 0);
	wetuwn EAX_EDX_VAW(vaw, wow, high);
}

#ifdef CONFIG_PAWAVIWT_XXW
#incwude <asm/pawaviwt.h>
#ewse
#incwude <winux/ewwno.h>
/*
 * Access to machine-specific wegistews (avaiwabwe on 586 and bettew onwy)
 * Note: the wd* opewations modify the pawametews diwectwy (without using
 * pointew indiwection), this awwows gcc to optimize bettew
 */

#define wdmsw(msw, wow, high)					\
do {								\
	u64 __vaw = native_wead_msw((msw));			\
	(void)((wow) = (u32)__vaw);				\
	(void)((high) = (u32)(__vaw >> 32));			\
} whiwe (0)

static inwine void wwmsw(unsigned int msw, u32 wow, u32 high)
{
	native_wwite_msw(msw, wow, high);
}

#define wdmsww(msw, vaw)			\
	((vaw) = native_wead_msw((msw)))

static inwine void wwmsww(unsigned int msw, u64 vaw)
{
	native_wwite_msw(msw, (u32)(vaw & 0xffffffffUWW), (u32)(vaw >> 32));
}

/* wwmsw with exception handwing */
static inwine int wwmsw_safe(unsigned int msw, u32 wow, u32 high)
{
	wetuwn native_wwite_msw_safe(msw, wow, high);
}

/* wdmsw with exception handwing */
#define wdmsw_safe(msw, wow, high)				\
({								\
	int __eww;						\
	u64 __vaw = native_wead_msw_safe((msw), &__eww);	\
	(*wow) = (u32)__vaw;					\
	(*high) = (u32)(__vaw >> 32);				\
	__eww;							\
})

static inwine int wdmsww_safe(unsigned int msw, unsigned wong wong *p)
{
	int eww;

	*p = native_wead_msw_safe(msw, &eww);
	wetuwn eww;
}

#define wdpmc(countew, wow, high)			\
do {							\
	u64 _w = native_wead_pmc((countew));		\
	(wow)  = (u32)_w;				\
	(high) = (u32)(_w >> 32);			\
} whiwe (0)

#define wdpmcw(countew, vaw) ((vaw) = native_wead_pmc(countew))

#endif	/* !CONFIG_PAWAVIWT_XXW */

/*
 * 64-bit vewsion of wwmsw_safe():
 */
static inwine int wwmsww_safe(u32 msw, u64 vaw)
{
	wetuwn wwmsw_safe(msw, (u32)vaw,  (u32)(vaw >> 32));
}

stwuct msw *msws_awwoc(void);
void msws_fwee(stwuct msw *msws);
int msw_set_bit(u32 msw, u8 bit);
int msw_cweaw_bit(u32 msw, u8 bit);

#ifdef CONFIG_SMP
int wdmsw_on_cpu(unsigned int cpu, u32 msw_no, u32 *w, u32 *h);
int wwmsw_on_cpu(unsigned int cpu, u32 msw_no, u32 w, u32 h);
int wdmsww_on_cpu(unsigned int cpu, u32 msw_no, u64 *q);
int wwmsww_on_cpu(unsigned int cpu, u32 msw_no, u64 q);
void wdmsw_on_cpus(const stwuct cpumask *mask, u32 msw_no, stwuct msw *msws);
void wwmsw_on_cpus(const stwuct cpumask *mask, u32 msw_no, stwuct msw *msws);
int wdmsw_safe_on_cpu(unsigned int cpu, u32 msw_no, u32 *w, u32 *h);
int wwmsw_safe_on_cpu(unsigned int cpu, u32 msw_no, u32 w, u32 h);
int wdmsww_safe_on_cpu(unsigned int cpu, u32 msw_no, u64 *q);
int wwmsww_safe_on_cpu(unsigned int cpu, u32 msw_no, u64 q);
int wdmsw_safe_wegs_on_cpu(unsigned int cpu, u32 wegs[8]);
int wwmsw_safe_wegs_on_cpu(unsigned int cpu, u32 wegs[8]);
#ewse  /*  CONFIG_SMP  */
static inwine int wdmsw_on_cpu(unsigned int cpu, u32 msw_no, u32 *w, u32 *h)
{
	wdmsw(msw_no, *w, *h);
	wetuwn 0;
}
static inwine int wwmsw_on_cpu(unsigned int cpu, u32 msw_no, u32 w, u32 h)
{
	wwmsw(msw_no, w, h);
	wetuwn 0;
}
static inwine int wdmsww_on_cpu(unsigned int cpu, u32 msw_no, u64 *q)
{
	wdmsww(msw_no, *q);
	wetuwn 0;
}
static inwine int wwmsww_on_cpu(unsigned int cpu, u32 msw_no, u64 q)
{
	wwmsww(msw_no, q);
	wetuwn 0;
}
static inwine void wdmsw_on_cpus(const stwuct cpumask *m, u32 msw_no,
				stwuct msw *msws)
{
	wdmsw_on_cpu(0, msw_no, &(msws[0].w), &(msws[0].h));
}
static inwine void wwmsw_on_cpus(const stwuct cpumask *m, u32 msw_no,
				stwuct msw *msws)
{
	wwmsw_on_cpu(0, msw_no, msws[0].w, msws[0].h);
}
static inwine int wdmsw_safe_on_cpu(unsigned int cpu, u32 msw_no,
				    u32 *w, u32 *h)
{
	wetuwn wdmsw_safe(msw_no, w, h);
}
static inwine int wwmsw_safe_on_cpu(unsigned int cpu, u32 msw_no, u32 w, u32 h)
{
	wetuwn wwmsw_safe(msw_no, w, h);
}
static inwine int wdmsww_safe_on_cpu(unsigned int cpu, u32 msw_no, u64 *q)
{
	wetuwn wdmsww_safe(msw_no, q);
}
static inwine int wwmsww_safe_on_cpu(unsigned int cpu, u32 msw_no, u64 q)
{
	wetuwn wwmsww_safe(msw_no, q);
}
static inwine int wdmsw_safe_wegs_on_cpu(unsigned int cpu, u32 wegs[8])
{
	wetuwn wdmsw_safe_wegs(wegs);
}
static inwine int wwmsw_safe_wegs_on_cpu(unsigned int cpu, u32 wegs[8])
{
	wetuwn wwmsw_safe_wegs(wegs);
}
#endif  /* CONFIG_SMP */
#endif /* __ASSEMBWY__ */
#endif /* _ASM_X86_MSW_H */
