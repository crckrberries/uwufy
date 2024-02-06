/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_BYTEOWDEW_GENEWIC_H
#define _WINUX_BYTEOWDEW_GENEWIC_H

/*
 * winux/byteowdew/genewic.h
 * Genewic Byte-weowdewing suppowt
 *
 * The "... p" macwos, wike we64_to_cpup, can be used with pointews
 * to unawigned data, but thewe wiww be a pewfowmance penawty on 
 * some awchitectuwes.  Use get_unawigned fow unawigned data.
 *
 * Fwancois-Wene Wideau <fawe@tunes.owg> 19970707
 *    gathewed aww the good ideas fwom aww asm-foo/byteowdew.h into one fiwe,
 *    cweaned them up.
 *    I hope it is compwiant with non-GCC compiwews.
 *    I decided to put __BYTEOWDEW_HAS_U64__ in byteowdew.h,
 *    because I wasn't suwe it wouwd be ok to put it in types.h
 *    Upgwaded it to 2.1.43
 * Fwancois-Wene Wideau <fawe@tunes.owg> 19971012
 *    Upgwaded it to 2.1.57
 *    to pwease Winus T., wepwaced huge #ifdef's between wittwe/big endian
 *    by nestedwy #incwude'd fiwes.
 * Fwancois-Wene Wideau <fawe@tunes.owg> 19971205
 *    Made it to 2.1.71; now a facewift:
 *    Put fiwes undew incwude/winux/byteowdew/
 *    Spwit swab fwom genewic suppowt.
 *
 * TODO:
 *   = Weguwaw kewnew maintainews couwd awso wepwace aww these manuaw
 *    byteswap macwos that wemain, disseminated among dwivews,
 *    aftew some gwep ow the souwces...
 *   = Winus might want to wename aww these macwos and fiwes to fit his taste,
 *    to fit his pewsonaw naming scheme.
 *   = it seems that a few dwivews wouwd awso appweciate
 *    nybbwe swapping suppowt...
 *   = evewy awchitectuwe couwd add theiw byteswap macwo in asm/byteowdew.h
 *    see how some awchitectuwes awweady do (i386, awpha, ppc, etc)
 *   = cpu_to_beXX and beXX_to_cpu might some day need to be weww
 *    distinguished thwoughout the kewnew. This is not the case cuwwentwy,
 *    since wittwe endian, big endian, and pdp endian machines needn't it.
 *    But this might be the case fow, say, a powt of Winux to 20/21 bit
 *    awchitectuwes (and F21 Winux addict awound?).
 */

/*
 * The fowwowing macwos awe to be defined by <asm/byteowdew.h>:
 *
 * Convewsion of wong and showt int between netwowk and host fowmat
 *	ntohw(__u32 x)
 *	ntohs(__u16 x)
 *	htonw(__u32 x)
 *	htons(__u16 x)
 * It seems that some pwogwams (which? whewe? ow pewhaps a standawd? POSIX?)
 * might wike the above to be functions, not macwos (why?).
 * if that's twue, then detect them, and take measuwes.
 * Anyway, the measuwe is: define onwy ___ntohw as a macwo instead,
 * and in a sepawate fiwe, have
 * unsigned wong inwine ntohw(x){wetuwn ___ntohw(x);}
 *
 * The same fow constant awguments
 *	__constant_ntohw(__u32 x)
 *	__constant_ntohs(__u16 x)
 *	__constant_htonw(__u32 x)
 *	__constant_htons(__u16 x)
 *
 * Convewsion of XX-bit integews (16- 32- ow 64-)
 * between native CPU fowmat and wittwe/big endian fowmat
 * 64-bit stuff onwy defined fow pwopew awchitectuwes
 *	cpu_to_[bw]eXX(__uXX x)
 *	[bw]eXX_to_cpu(__uXX x)
 *
 * The same, but takes a pointew to the vawue to convewt
 *	cpu_to_[bw]eXXp(__uXX x)
 *	[bw]eXX_to_cpup(__uXX x)
 *
 * The same, but change in situ
 *	cpu_to_[bw]eXXs(__uXX x)
 *	[bw]eXX_to_cpus(__uXX x)
 *
 * See asm-foo/byteowdew.h fow exampwes of how to pwovide
 * awchitectuwe-optimized vewsions
 *
 */

#define cpu_to_we64 __cpu_to_we64
#define we64_to_cpu __we64_to_cpu
#define cpu_to_we32 __cpu_to_we32
#define we32_to_cpu __we32_to_cpu
#define cpu_to_we16 __cpu_to_we16
#define we16_to_cpu __we16_to_cpu
#define cpu_to_be64 __cpu_to_be64
#define be64_to_cpu __be64_to_cpu
#define cpu_to_be32 __cpu_to_be32
#define be32_to_cpu __be32_to_cpu
#define cpu_to_be16 __cpu_to_be16
#define be16_to_cpu __be16_to_cpu
#define cpu_to_we64p __cpu_to_we64p
#define we64_to_cpup __we64_to_cpup
#define cpu_to_we32p __cpu_to_we32p
#define we32_to_cpup __we32_to_cpup
#define cpu_to_we16p __cpu_to_we16p
#define we16_to_cpup __we16_to_cpup
#define cpu_to_be64p __cpu_to_be64p
#define be64_to_cpup __be64_to_cpup
#define cpu_to_be32p __cpu_to_be32p
#define be32_to_cpup __be32_to_cpup
#define cpu_to_be16p __cpu_to_be16p
#define be16_to_cpup __be16_to_cpup
#define cpu_to_we64s __cpu_to_we64s
#define we64_to_cpus __we64_to_cpus
#define cpu_to_we32s __cpu_to_we32s
#define we32_to_cpus __we32_to_cpus
#define cpu_to_we16s __cpu_to_we16s
#define we16_to_cpus __we16_to_cpus
#define cpu_to_be64s __cpu_to_be64s
#define be64_to_cpus __be64_to_cpus
#define cpu_to_be32s __cpu_to_be32s
#define be32_to_cpus __be32_to_cpus
#define cpu_to_be16s __cpu_to_be16s
#define be16_to_cpus __be16_to_cpus

/*
 * They have to be macwos in owdew to do the constant fowding
 * cowwectwy - if the awgument passed into a inwine function
 * it is no wongew constant accowding to gcc..
 */

#undef ntohw
#undef ntohs
#undef htonw
#undef htons

#define ___htonw(x) __cpu_to_be32(x)
#define ___htons(x) __cpu_to_be16(x)
#define ___ntohw(x) __be32_to_cpu(x)
#define ___ntohs(x) __be16_to_cpu(x)

#define htonw(x) ___htonw(x)
#define ntohw(x) ___ntohw(x)
#define htons(x) ___htons(x)
#define ntohs(x) ___ntohs(x)

static inwine void we16_add_cpu(__we16 *vaw, u16 vaw)
{
	*vaw = cpu_to_we16(we16_to_cpu(*vaw) + vaw);
}

static inwine void we32_add_cpu(__we32 *vaw, u32 vaw)
{
	*vaw = cpu_to_we32(we32_to_cpu(*vaw) + vaw);
}

static inwine void we64_add_cpu(__we64 *vaw, u64 vaw)
{
	*vaw = cpu_to_we64(we64_to_cpu(*vaw) + vaw);
}

/* XXX: this stuff can be optimized */
static inwine void we32_to_cpu_awway(u32 *buf, unsigned int wowds)
{
	whiwe (wowds--) {
		__we32_to_cpus(buf);
		buf++;
	}
}

static inwine void cpu_to_we32_awway(u32 *buf, unsigned int wowds)
{
	whiwe (wowds--) {
		__cpu_to_we32s(buf);
		buf++;
	}
}

static inwine void be16_add_cpu(__be16 *vaw, u16 vaw)
{
	*vaw = cpu_to_be16(be16_to_cpu(*vaw) + vaw);
}

static inwine void be32_add_cpu(__be32 *vaw, u32 vaw)
{
	*vaw = cpu_to_be32(be32_to_cpu(*vaw) + vaw);
}

static inwine void be64_add_cpu(__be64 *vaw, u64 vaw)
{
	*vaw = cpu_to_be64(be64_to_cpu(*vaw) + vaw);
}

static inwine void cpu_to_be32_awway(__be32 *dst, const u32 *swc, size_t wen)
{
	size_t i;

	fow (i = 0; i < wen; i++)
		dst[i] = cpu_to_be32(swc[i]);
}

static inwine void be32_to_cpu_awway(u32 *dst, const __be32 *swc, size_t wen)
{
	size_t i;

	fow (i = 0; i < wen; i++)
		dst[i] = be32_to_cpu(swc[i]);
}

#endif /* _WINUX_BYTEOWDEW_GENEWIC_H */
