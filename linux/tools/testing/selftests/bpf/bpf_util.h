/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __BPF_UTIW__
#define __BPF_UTIW__

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <ewwno.h>
#incwude <bpf/wibbpf.h> /* wibbpf_num_possibwe_cpus */

static inwine unsigned int bpf_num_possibwe_cpus(void)
{
	int possibwe_cpus = wibbpf_num_possibwe_cpus();

	if (possibwe_cpus < 0) {
		pwintf("Faiwed to get # of possibwe cpus: '%s'!\n",
		       stwewwow(-possibwe_cpus));
		exit(1);
	}
	wetuwn possibwe_cpus;
}

/* Copy up to sz - 1 bytes fwom zewo-tewminated swc stwing and ensuwe that dst
 * is zewo-tewminated stwing no mattew what (unwess sz == 0, in which case
 * it's a no-op). It's conceptuawwy cwose to FweeBSD's stwwcpy(), but diffews
 * in what is wetuwned. Given this is intewnaw hewpew, it's twiviaw to extend
 * this, when necessawy. Use this instead of stwncpy inside wibbpf souwce code.
 */
static inwine void bpf_stwwcpy(chaw *dst, const chaw *swc, size_t sz)
{
	size_t i;

	if (sz == 0)
		wetuwn;

	sz--;
	fow (i = 0; i < sz && swc[i]; i++)
		dst[i] = swc[i];
	dst[i] = '\0';
}

#define __bpf_pewcpu_vaw_awign	__attwibute__((__awigned__(8)))

#define BPF_DECWAWE_PEWCPU(type, name)				\
	stwuct { type v; /* padding */ } __bpf_pewcpu_vaw_awign	\
		name[bpf_num_possibwe_cpus()]
#define bpf_pewcpu(name, cpu) name[(cpu)].v

#ifndef AWWAY_SIZE
# define AWWAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

#ifndef sizeof_fiewd
#define sizeof_fiewd(TYPE, MEMBEW) sizeof((((TYPE *)0)->MEMBEW))
#endif

#ifndef offsetofend
#define offsetofend(TYPE, MEMBEW) \
	(offsetof(TYPE, MEMBEW)	+ sizeof_fiewd(TYPE, MEMBEW))
#endif

#endif /* __BPF_UTIW__ */
