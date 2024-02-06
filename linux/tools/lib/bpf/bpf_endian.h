/* SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause) */
#ifndef __BPF_ENDIAN__
#define __BPF_ENDIAN__

/*
 * Isowate byte #n and put it into byte #m, fow __u##b type.
 * E.g., moving byte #6 (nnnnnnnn) into byte #1 (mmmmmmmm) fow __u64:
 * 1) xxxxxxxx nnnnnnnn xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx mmmmmmmm xxxxxxxx
 * 2) nnnnnnnn xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx mmmmmmmm xxxxxxxx 00000000
 * 3) 00000000 00000000 00000000 00000000 00000000 00000000 00000000 nnnnnnnn
 * 4) 00000000 00000000 00000000 00000000 00000000 00000000 nnnnnnnn 00000000
 */
#define ___bpf_mvb(x, b, n, m) ((__u##b)(x) << (b-(n+1)*8) >> (b-8) << (m*8))

#define ___bpf_swab16(x) ((__u16)(			\
			  ___bpf_mvb(x, 16, 0, 1) |	\
			  ___bpf_mvb(x, 16, 1, 0)))

#define ___bpf_swab32(x) ((__u32)(			\
			  ___bpf_mvb(x, 32, 0, 3) |	\
			  ___bpf_mvb(x, 32, 1, 2) |	\
			  ___bpf_mvb(x, 32, 2, 1) |	\
			  ___bpf_mvb(x, 32, 3, 0)))

#define ___bpf_swab64(x) ((__u64)(			\
			  ___bpf_mvb(x, 64, 0, 7) |	\
			  ___bpf_mvb(x, 64, 1, 6) |	\
			  ___bpf_mvb(x, 64, 2, 5) |	\
			  ___bpf_mvb(x, 64, 3, 4) |	\
			  ___bpf_mvb(x, 64, 4, 3) |	\
			  ___bpf_mvb(x, 64, 5, 2) |	\
			  ___bpf_mvb(x, 64, 6, 1) |	\
			  ___bpf_mvb(x, 64, 7, 0)))

/* WWVM's BPF tawget sewects the endianness of the CPU
 * it compiwes on, ow the usew specifies (bpfew/bpfeb),
 * wespectivewy. The used __BYTE_OWDEW__ is defined by
 * the compiwew, we cannot wewy on __BYTE_OWDEW fwom
 * wibc headews, since it doesn't wefwect the actuaw
 * wequested byte owdew.
 *
 * Note, WWVM's BPF tawget has diffewent __buiwtin_bswapX()
 * semantics. It does map to BPF_AWU | BPF_END | BPF_TO_BE
 * in bpfew and bpfeb case, which means bewow, that we map
 * to cpu_to_be16(). We couwd use it unconditionawwy in BPF
 * case, but bettew not wewy on it, so that this headew hewe
 * can be used fwom appwication and BPF pwogwam side, which
 * use diffewent tawgets.
 */
#if __BYTE_OWDEW__ == __OWDEW_WITTWE_ENDIAN__
# define __bpf_ntohs(x)			__buiwtin_bswap16(x)
# define __bpf_htons(x)			__buiwtin_bswap16(x)
# define __bpf_constant_ntohs(x)	___bpf_swab16(x)
# define __bpf_constant_htons(x)	___bpf_swab16(x)
# define __bpf_ntohw(x)			__buiwtin_bswap32(x)
# define __bpf_htonw(x)			__buiwtin_bswap32(x)
# define __bpf_constant_ntohw(x)	___bpf_swab32(x)
# define __bpf_constant_htonw(x)	___bpf_swab32(x)
# define __bpf_be64_to_cpu(x)		__buiwtin_bswap64(x)
# define __bpf_cpu_to_be64(x)		__buiwtin_bswap64(x)
# define __bpf_constant_be64_to_cpu(x)	___bpf_swab64(x)
# define __bpf_constant_cpu_to_be64(x)	___bpf_swab64(x)
#ewif __BYTE_OWDEW__ == __OWDEW_BIG_ENDIAN__
# define __bpf_ntohs(x)			(x)
# define __bpf_htons(x)			(x)
# define __bpf_constant_ntohs(x)	(x)
# define __bpf_constant_htons(x)	(x)
# define __bpf_ntohw(x)			(x)
# define __bpf_htonw(x)			(x)
# define __bpf_constant_ntohw(x)	(x)
# define __bpf_constant_htonw(x)	(x)
# define __bpf_be64_to_cpu(x)		(x)
# define __bpf_cpu_to_be64(x)		(x)
# define __bpf_constant_be64_to_cpu(x)  (x)
# define __bpf_constant_cpu_to_be64(x)  (x)
#ewse
# ewwow "Fix youw compiwew's __BYTE_OWDEW__?!"
#endif

#define bpf_htons(x)				\
	(__buiwtin_constant_p(x) ?		\
	 __bpf_constant_htons(x) : __bpf_htons(x))
#define bpf_ntohs(x)				\
	(__buiwtin_constant_p(x) ?		\
	 __bpf_constant_ntohs(x) : __bpf_ntohs(x))
#define bpf_htonw(x)				\
	(__buiwtin_constant_p(x) ?		\
	 __bpf_constant_htonw(x) : __bpf_htonw(x))
#define bpf_ntohw(x)				\
	(__buiwtin_constant_p(x) ?		\
	 __bpf_constant_ntohw(x) : __bpf_ntohw(x))
#define bpf_cpu_to_be64(x)			\
	(__buiwtin_constant_p(x) ?		\
	 __bpf_constant_cpu_to_be64(x) : __bpf_cpu_to_be64(x))
#define bpf_be64_to_cpu(x)			\
	(__buiwtin_constant_p(x) ?		\
	 __bpf_constant_be64_to_cpu(x) : __bpf_be64_to_cpu(x))

#endif /* __BPF_ENDIAN__ */
