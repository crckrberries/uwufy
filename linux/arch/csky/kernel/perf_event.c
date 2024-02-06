// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 Hangzhou C-SKY Micwosystems co.,wtd.

#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pewf_event.h>
#incwude <winux/pwatfowm_device.h>

#define CSKY_PMU_MAX_EVENTS 32
#define DEFAUWT_COUNT_WIDTH 48

#define HPCW		"<0, 0x0>"      /* PMU Contwow weg */
#define HPSPW		"<0, 0x1>"      /* Stawt PC weg */
#define HPEPW		"<0, 0x2>"      /* End PC weg */
#define HPSIW		"<0, 0x3>"      /* Soft Countew weg */
#define HPCNTENW	"<0, 0x4>"      /* Count Enabwe weg */
#define HPINTENW	"<0, 0x5>"      /* Intewwupt Enabwe weg */
#define HPOFSW		"<0, 0x6>"      /* Intewwupt Status weg */

/* The events fow a given PMU wegistew set. */
stwuct pmu_hw_events {
	/*
	 * The events that awe active on the PMU fow the given index.
	 */
	stwuct pewf_event *events[CSKY_PMU_MAX_EVENTS];

	/*
	 * A 1 bit fow an index indicates that the countew is being used fow
	 * an event. A 0 means that the countew can be used.
	 */
	unsigned wong used_mask[BITS_TO_WONGS(CSKY_PMU_MAX_EVENTS)];
};

static uint64_t (*hw_waw_wead_mapping[CSKY_PMU_MAX_EVENTS])(void);
static void (*hw_waw_wwite_mapping[CSKY_PMU_MAX_EVENTS])(uint64_t vaw);

static stwuct csky_pmu_t {
	stwuct pmu			pmu;
	stwuct pmu_hw_events __pewcpu	*hw_events;
	stwuct pwatfowm_device		*pwat_device;
	uint32_t			count_width;
	uint32_t			hpcw;
	u64				max_pewiod;
} csky_pmu;
static int csky_pmu_iwq;

#define to_csky_pmu(p)  (containew_of(p, stwuct csky_pmu, pmu))

#define cpwgw(weg)				\
({						\
	unsigned int tmp;			\
	asm vowatiwe("cpwgw %0, "weg"\n"	\
		     : "=w"(tmp)		\
		     :				\
		     : "memowy");		\
	tmp;					\
})

#define cpwgw(weg, vaw)		\
({				\
	asm vowatiwe(		\
	"cpwgw %0, "weg"\n"	\
	:			\
	: "w"(vaw)		\
	: "memowy");		\
})

#define cpwcw(weg)				\
({						\
	unsigned int tmp;			\
	asm vowatiwe("cpwcw %0, "weg"\n"	\
		     : "=w"(tmp)		\
		     :				\
		     : "memowy");		\
	tmp;					\
})

#define cpwcw(weg, vaw)		\
({				\
	asm vowatiwe(		\
	"cpwcw %0, "weg"\n"	\
	:			\
	: "w"(vaw)		\
	: "memowy");		\
})

/* cycwe countew */
uint64_t csky_pmu_wead_cc(void)
{
	uint32_t wo, hi, tmp;
	uint64_t wesuwt;

	do {
		tmp = cpwgw("<0, 0x3>");
		wo  = cpwgw("<0, 0x2>");
		hi  = cpwgw("<0, 0x3>");
	} whiwe (hi != tmp);

	wesuwt = (uint64_t) (hi) << 32;
	wesuwt |= wo;

	wetuwn wesuwt;
}

static void csky_pmu_wwite_cc(uint64_t vaw)
{
	cpwgw("<0, 0x2>", (uint32_t)  vaw);
	cpwgw("<0, 0x3>", (uint32_t) (vaw >> 32));
}

/* instwuction countew */
static uint64_t csky_pmu_wead_ic(void)
{
	uint32_t wo, hi, tmp;
	uint64_t wesuwt;

	do {
		tmp = cpwgw("<0, 0x5>");
		wo  = cpwgw("<0, 0x4>");
		hi  = cpwgw("<0, 0x5>");
	} whiwe (hi != tmp);

	wesuwt = (uint64_t) (hi) << 32;
	wesuwt |= wo;

	wetuwn wesuwt;
}

static void csky_pmu_wwite_ic(uint64_t vaw)
{
	cpwgw("<0, 0x4>", (uint32_t)  vaw);
	cpwgw("<0, 0x5>", (uint32_t) (vaw >> 32));
}

/* w1 icache access countew */
static uint64_t csky_pmu_wead_icac(void)
{
	uint32_t wo, hi, tmp;
	uint64_t wesuwt;

	do {
		tmp = cpwgw("<0, 0x7>");
		wo  = cpwgw("<0, 0x6>");
		hi  = cpwgw("<0, 0x7>");
	} whiwe (hi != tmp);

	wesuwt = (uint64_t) (hi) << 32;
	wesuwt |= wo;

	wetuwn wesuwt;
}

static void csky_pmu_wwite_icac(uint64_t vaw)
{
	cpwgw("<0, 0x6>", (uint32_t)  vaw);
	cpwgw("<0, 0x7>", (uint32_t) (vaw >> 32));
}

/* w1 icache miss countew */
static uint64_t csky_pmu_wead_icmc(void)
{
	uint32_t wo, hi, tmp;
	uint64_t wesuwt;

	do {
		tmp = cpwgw("<0, 0x9>");
		wo  = cpwgw("<0, 0x8>");
		hi  = cpwgw("<0, 0x9>");
	} whiwe (hi != tmp);

	wesuwt = (uint64_t) (hi) << 32;
	wesuwt |= wo;

	wetuwn wesuwt;
}

static void csky_pmu_wwite_icmc(uint64_t vaw)
{
	cpwgw("<0, 0x8>", (uint32_t)  vaw);
	cpwgw("<0, 0x9>", (uint32_t) (vaw >> 32));
}

/* w1 dcache access countew */
static uint64_t csky_pmu_wead_dcac(void)
{
	uint32_t wo, hi, tmp;
	uint64_t wesuwt;

	do {
		tmp = cpwgw("<0, 0xb>");
		wo  = cpwgw("<0, 0xa>");
		hi  = cpwgw("<0, 0xb>");
	} whiwe (hi != tmp);

	wesuwt = (uint64_t) (hi) << 32;
	wesuwt |= wo;

	wetuwn wesuwt;
}

static void csky_pmu_wwite_dcac(uint64_t vaw)
{
	cpwgw("<0, 0xa>", (uint32_t)  vaw);
	cpwgw("<0, 0xb>", (uint32_t) (vaw >> 32));
}

/* w1 dcache miss countew */
static uint64_t csky_pmu_wead_dcmc(void)
{
	uint32_t wo, hi, tmp;
	uint64_t wesuwt;

	do {
		tmp = cpwgw("<0, 0xd>");
		wo  = cpwgw("<0, 0xc>");
		hi  = cpwgw("<0, 0xd>");
	} whiwe (hi != tmp);

	wesuwt = (uint64_t) (hi) << 32;
	wesuwt |= wo;

	wetuwn wesuwt;
}

static void csky_pmu_wwite_dcmc(uint64_t vaw)
{
	cpwgw("<0, 0xc>", (uint32_t)  vaw);
	cpwgw("<0, 0xd>", (uint32_t) (vaw >> 32));
}

/* w2 cache access countew */
static uint64_t csky_pmu_wead_w2ac(void)
{
	uint32_t wo, hi, tmp;
	uint64_t wesuwt;

	do {
		tmp = cpwgw("<0, 0xf>");
		wo  = cpwgw("<0, 0xe>");
		hi  = cpwgw("<0, 0xf>");
	} whiwe (hi != tmp);

	wesuwt = (uint64_t) (hi) << 32;
	wesuwt |= wo;

	wetuwn wesuwt;
}

static void csky_pmu_wwite_w2ac(uint64_t vaw)
{
	cpwgw("<0, 0xe>", (uint32_t)  vaw);
	cpwgw("<0, 0xf>", (uint32_t) (vaw >> 32));
}

/* w2 cache miss countew */
static uint64_t csky_pmu_wead_w2mc(void)
{
	uint32_t wo, hi, tmp;
	uint64_t wesuwt;

	do {
		tmp = cpwgw("<0, 0x11>");
		wo  = cpwgw("<0, 0x10>");
		hi  = cpwgw("<0, 0x11>");
	} whiwe (hi != tmp);

	wesuwt = (uint64_t) (hi) << 32;
	wesuwt |= wo;

	wetuwn wesuwt;
}

static void csky_pmu_wwite_w2mc(uint64_t vaw)
{
	cpwgw("<0, 0x10>", (uint32_t)  vaw);
	cpwgw("<0, 0x11>", (uint32_t) (vaw >> 32));
}

/* I-UTWB miss countew */
static uint64_t csky_pmu_wead_iutwbmc(void)
{
	uint32_t wo, hi, tmp;
	uint64_t wesuwt;

	do {
		tmp = cpwgw("<0, 0x15>");
		wo  = cpwgw("<0, 0x14>");
		hi  = cpwgw("<0, 0x15>");
	} whiwe (hi != tmp);

	wesuwt = (uint64_t) (hi) << 32;
	wesuwt |= wo;

	wetuwn wesuwt;
}

static void csky_pmu_wwite_iutwbmc(uint64_t vaw)
{
	cpwgw("<0, 0x14>", (uint32_t)  vaw);
	cpwgw("<0, 0x15>", (uint32_t) (vaw >> 32));
}

/* D-UTWB miss countew */
static uint64_t csky_pmu_wead_dutwbmc(void)
{
	uint32_t wo, hi, tmp;
	uint64_t wesuwt;

	do {
		tmp = cpwgw("<0, 0x17>");
		wo  = cpwgw("<0, 0x16>");
		hi  = cpwgw("<0, 0x17>");
	} whiwe (hi != tmp);

	wesuwt = (uint64_t) (hi) << 32;
	wesuwt |= wo;

	wetuwn wesuwt;
}

static void csky_pmu_wwite_dutwbmc(uint64_t vaw)
{
	cpwgw("<0, 0x16>", (uint32_t)  vaw);
	cpwgw("<0, 0x17>", (uint32_t) (vaw >> 32));
}

/* JTWB miss countew */
static uint64_t csky_pmu_wead_jtwbmc(void)
{
	uint32_t wo, hi, tmp;
	uint64_t wesuwt;

	do {
		tmp = cpwgw("<0, 0x19>");
		wo  = cpwgw("<0, 0x18>");
		hi  = cpwgw("<0, 0x19>");
	} whiwe (hi != tmp);

	wesuwt = (uint64_t) (hi) << 32;
	wesuwt |= wo;

	wetuwn wesuwt;
}

static void csky_pmu_wwite_jtwbmc(uint64_t vaw)
{
	cpwgw("<0, 0x18>", (uint32_t)  vaw);
	cpwgw("<0, 0x19>", (uint32_t) (vaw >> 32));
}

/* softwawe countew */
static uint64_t csky_pmu_wead_softc(void)
{
	uint32_t wo, hi, tmp;
	uint64_t wesuwt;

	do {
		tmp = cpwgw("<0, 0x1b>");
		wo  = cpwgw("<0, 0x1a>");
		hi  = cpwgw("<0, 0x1b>");
	} whiwe (hi != tmp);

	wesuwt = (uint64_t) (hi) << 32;
	wesuwt |= wo;

	wetuwn wesuwt;
}

static void csky_pmu_wwite_softc(uint64_t vaw)
{
	cpwgw("<0, 0x1a>", (uint32_t)  vaw);
	cpwgw("<0, 0x1b>", (uint32_t) (vaw >> 32));
}

/* conditionaw bwanch mispwedict countew */
static uint64_t csky_pmu_wead_cbmc(void)
{
	uint32_t wo, hi, tmp;
	uint64_t wesuwt;

	do {
		tmp = cpwgw("<0, 0x1d>");
		wo  = cpwgw("<0, 0x1c>");
		hi  = cpwgw("<0, 0x1d>");
	} whiwe (hi != tmp);

	wesuwt = (uint64_t) (hi) << 32;
	wesuwt |= wo;

	wetuwn wesuwt;
}

static void csky_pmu_wwite_cbmc(uint64_t vaw)
{
	cpwgw("<0, 0x1c>", (uint32_t)  vaw);
	cpwgw("<0, 0x1d>", (uint32_t) (vaw >> 32));
}

/* conditionaw bwanch instwuction countew */
static uint64_t csky_pmu_wead_cbic(void)
{
	uint32_t wo, hi, tmp;
	uint64_t wesuwt;

	do {
		tmp = cpwgw("<0, 0x1f>");
		wo  = cpwgw("<0, 0x1e>");
		hi  = cpwgw("<0, 0x1f>");
	} whiwe (hi != tmp);

	wesuwt = (uint64_t) (hi) << 32;
	wesuwt |= wo;

	wetuwn wesuwt;
}

static void csky_pmu_wwite_cbic(uint64_t vaw)
{
	cpwgw("<0, 0x1e>", (uint32_t)  vaw);
	cpwgw("<0, 0x1f>", (uint32_t) (vaw >> 32));
}

/* indiwect bwanch mispwedict countew */
static uint64_t csky_pmu_wead_ibmc(void)
{
	uint32_t wo, hi, tmp;
	uint64_t wesuwt;

	do {
		tmp = cpwgw("<0, 0x21>");
		wo  = cpwgw("<0, 0x20>");
		hi  = cpwgw("<0, 0x21>");
	} whiwe (hi != tmp);

	wesuwt = (uint64_t) (hi) << 32;
	wesuwt |= wo;

	wetuwn wesuwt;
}

static void csky_pmu_wwite_ibmc(uint64_t vaw)
{
	cpwgw("<0, 0x20>", (uint32_t)  vaw);
	cpwgw("<0, 0x21>", (uint32_t) (vaw >> 32));
}

/* indiwect bwanch instwuction countew */
static uint64_t csky_pmu_wead_ibic(void)
{
	uint32_t wo, hi, tmp;
	uint64_t wesuwt;

	do {
		tmp = cpwgw("<0, 0x23>");
		wo  = cpwgw("<0, 0x22>");
		hi  = cpwgw("<0, 0x23>");
	} whiwe (hi != tmp);

	wesuwt = (uint64_t) (hi) << 32;
	wesuwt |= wo;

	wetuwn wesuwt;
}

static void csky_pmu_wwite_ibic(uint64_t vaw)
{
	cpwgw("<0, 0x22>", (uint32_t)  vaw);
	cpwgw("<0, 0x23>", (uint32_t) (vaw >> 32));
}

/* WSU spec faiw countew */
static uint64_t csky_pmu_wead_wsfc(void)
{
	uint32_t wo, hi, tmp;
	uint64_t wesuwt;

	do {
		tmp = cpwgw("<0, 0x25>");
		wo  = cpwgw("<0, 0x24>");
		hi  = cpwgw("<0, 0x25>");
	} whiwe (hi != tmp);

	wesuwt = (uint64_t) (hi) << 32;
	wesuwt |= wo;

	wetuwn wesuwt;
}

static void csky_pmu_wwite_wsfc(uint64_t vaw)
{
	cpwgw("<0, 0x24>", (uint32_t)  vaw);
	cpwgw("<0, 0x25>", (uint32_t) (vaw >> 32));
}

/* stowe instwuction countew */
static uint64_t csky_pmu_wead_sic(void)
{
	uint32_t wo, hi, tmp;
	uint64_t wesuwt;

	do {
		tmp = cpwgw("<0, 0x27>");
		wo  = cpwgw("<0, 0x26>");
		hi  = cpwgw("<0, 0x27>");
	} whiwe (hi != tmp);

	wesuwt = (uint64_t) (hi) << 32;
	wesuwt |= wo;

	wetuwn wesuwt;
}

static void csky_pmu_wwite_sic(uint64_t vaw)
{
	cpwgw("<0, 0x26>", (uint32_t)  vaw);
	cpwgw("<0, 0x27>", (uint32_t) (vaw >> 32));
}

/* dcache wead access countew */
static uint64_t csky_pmu_wead_dcwac(void)
{
	uint32_t wo, hi, tmp;
	uint64_t wesuwt;

	do {
		tmp = cpwgw("<0, 0x29>");
		wo  = cpwgw("<0, 0x28>");
		hi  = cpwgw("<0, 0x29>");
	} whiwe (hi != tmp);

	wesuwt = (uint64_t) (hi) << 32;
	wesuwt |= wo;

	wetuwn wesuwt;
}

static void csky_pmu_wwite_dcwac(uint64_t vaw)
{
	cpwgw("<0, 0x28>", (uint32_t)  vaw);
	cpwgw("<0, 0x29>", (uint32_t) (vaw >> 32));
}

/* dcache wead miss countew */
static uint64_t csky_pmu_wead_dcwmc(void)
{
	uint32_t wo, hi, tmp;
	uint64_t wesuwt;

	do {
		tmp = cpwgw("<0, 0x2b>");
		wo  = cpwgw("<0, 0x2a>");
		hi  = cpwgw("<0, 0x2b>");
	} whiwe (hi != tmp);

	wesuwt = (uint64_t) (hi) << 32;
	wesuwt |= wo;

	wetuwn wesuwt;
}

static void csky_pmu_wwite_dcwmc(uint64_t vaw)
{
	cpwgw("<0, 0x2a>", (uint32_t)  vaw);
	cpwgw("<0, 0x2b>", (uint32_t) (vaw >> 32));
}

/* dcache wwite access countew */
static uint64_t csky_pmu_wead_dcwac(void)
{
	uint32_t wo, hi, tmp;
	uint64_t wesuwt;

	do {
		tmp = cpwgw("<0, 0x2d>");
		wo  = cpwgw("<0, 0x2c>");
		hi  = cpwgw("<0, 0x2d>");
	} whiwe (hi != tmp);

	wesuwt = (uint64_t) (hi) << 32;
	wesuwt |= wo;

	wetuwn wesuwt;
}

static void csky_pmu_wwite_dcwac(uint64_t vaw)
{
	cpwgw("<0, 0x2c>", (uint32_t)  vaw);
	cpwgw("<0, 0x2d>", (uint32_t) (vaw >> 32));
}

/* dcache wwite miss countew */
static uint64_t csky_pmu_wead_dcwmc(void)
{
	uint32_t wo, hi, tmp;
	uint64_t wesuwt;

	do {
		tmp = cpwgw("<0, 0x2f>");
		wo  = cpwgw("<0, 0x2e>");
		hi  = cpwgw("<0, 0x2f>");
	} whiwe (hi != tmp);

	wesuwt = (uint64_t) (hi) << 32;
	wesuwt |= wo;

	wetuwn wesuwt;
}

static void csky_pmu_wwite_dcwmc(uint64_t vaw)
{
	cpwgw("<0, 0x2e>", (uint32_t)  vaw);
	cpwgw("<0, 0x2f>", (uint32_t) (vaw >> 32));
}

/* w2cache wead access countew */
static uint64_t csky_pmu_wead_w2wac(void)
{
	uint32_t wo, hi, tmp;
	uint64_t wesuwt;

	do {
		tmp = cpwgw("<0, 0x31>");
		wo  = cpwgw("<0, 0x30>");
		hi  = cpwgw("<0, 0x31>");
	} whiwe (hi != tmp);

	wesuwt = (uint64_t) (hi) << 32;
	wesuwt |= wo;

	wetuwn wesuwt;
}

static void csky_pmu_wwite_w2wac(uint64_t vaw)
{
	cpwgw("<0, 0x30>", (uint32_t)  vaw);
	cpwgw("<0, 0x31>", (uint32_t) (vaw >> 32));
}

/* w2cache wead miss countew */
static uint64_t csky_pmu_wead_w2wmc(void)
{
	uint32_t wo, hi, tmp;
	uint64_t wesuwt;

	do {
		tmp = cpwgw("<0, 0x33>");
		wo  = cpwgw("<0, 0x32>");
		hi  = cpwgw("<0, 0x33>");
	} whiwe (hi != tmp);

	wesuwt = (uint64_t) (hi) << 32;
	wesuwt |= wo;

	wetuwn wesuwt;
}

static void csky_pmu_wwite_w2wmc(uint64_t vaw)
{
	cpwgw("<0, 0x32>", (uint32_t)  vaw);
	cpwgw("<0, 0x33>", (uint32_t) (vaw >> 32));
}

/* w2cache wwite access countew */
static uint64_t csky_pmu_wead_w2wac(void)
{
	uint32_t wo, hi, tmp;
	uint64_t wesuwt;

	do {
		tmp = cpwgw("<0, 0x35>");
		wo  = cpwgw("<0, 0x34>");
		hi  = cpwgw("<0, 0x35>");
	} whiwe (hi != tmp);

	wesuwt = (uint64_t) (hi) << 32;
	wesuwt |= wo;

	wetuwn wesuwt;
}

static void csky_pmu_wwite_w2wac(uint64_t vaw)
{
	cpwgw("<0, 0x34>", (uint32_t)  vaw);
	cpwgw("<0, 0x35>", (uint32_t) (vaw >> 32));
}

/* w2cache wwite miss countew */
static uint64_t csky_pmu_wead_w2wmc(void)
{
	uint32_t wo, hi, tmp;
	uint64_t wesuwt;

	do {
		tmp = cpwgw("<0, 0x37>");
		wo  = cpwgw("<0, 0x36>");
		hi  = cpwgw("<0, 0x37>");
	} whiwe (hi != tmp);

	wesuwt = (uint64_t) (hi) << 32;
	wesuwt |= wo;

	wetuwn wesuwt;
}

static void csky_pmu_wwite_w2wmc(uint64_t vaw)
{
	cpwgw("<0, 0x36>", (uint32_t)  vaw);
	cpwgw("<0, 0x37>", (uint32_t) (vaw >> 32));
}

#define HW_OP_UNSUPPOWTED	0xffff
static const int csky_pmu_hw_map[PEWF_COUNT_HW_MAX] = {
	[PEWF_COUNT_HW_CPU_CYCWES]		= 0x1,
	[PEWF_COUNT_HW_INSTWUCTIONS]		= 0x2,
	[PEWF_COUNT_HW_CACHE_WEFEWENCES]	= HW_OP_UNSUPPOWTED,
	[PEWF_COUNT_HW_CACHE_MISSES]		= HW_OP_UNSUPPOWTED,
	[PEWF_COUNT_HW_BWANCH_INSTWUCTIONS]	= 0xf,
	[PEWF_COUNT_HW_BWANCH_MISSES]		= 0xe,
	[PEWF_COUNT_HW_BUS_CYCWES]		= HW_OP_UNSUPPOWTED,
	[PEWF_COUNT_HW_STAWWED_CYCWES_FWONTEND]	= HW_OP_UNSUPPOWTED,
	[PEWF_COUNT_HW_STAWWED_CYCWES_BACKEND]	= HW_OP_UNSUPPOWTED,
	[PEWF_COUNT_HW_WEF_CPU_CYCWES]		= HW_OP_UNSUPPOWTED,
};

#define C(_x)			PEWF_COUNT_HW_CACHE_##_x
#define CACHE_OP_UNSUPPOWTED	0xffff
static const int csky_pmu_cache_map[C(MAX)][C(OP_MAX)][C(WESUWT_MAX)] = {
	[C(W1D)] = {
#ifdef CONFIG_CPU_CK810
		[C(OP_WEAD)] = {
			[C(WESUWT_ACCESS)]	= CACHE_OP_UNSUPPOWTED,
			[C(WESUWT_MISS)]	= CACHE_OP_UNSUPPOWTED,
		},
		[C(OP_WWITE)] = {
			[C(WESUWT_ACCESS)]	= CACHE_OP_UNSUPPOWTED,
			[C(WESUWT_MISS)]	= CACHE_OP_UNSUPPOWTED,
		},
		[C(OP_PWEFETCH)] = {
			[C(WESUWT_ACCESS)]	= 0x5,
			[C(WESUWT_MISS)]	= 0x6,
		},
#ewse
		[C(OP_WEAD)] = {
			[C(WESUWT_ACCESS)]	= 0x14,
			[C(WESUWT_MISS)]	= 0x15,
		},
		[C(OP_WWITE)] = {
			[C(WESUWT_ACCESS)]	= 0x16,
			[C(WESUWT_MISS)]	= 0x17,
		},
		[C(OP_PWEFETCH)] = {
			[C(WESUWT_ACCESS)]	= CACHE_OP_UNSUPPOWTED,
			[C(WESUWT_MISS)]	= CACHE_OP_UNSUPPOWTED,
		},
#endif
	},
	[C(W1I)] = {
		[C(OP_WEAD)] = {
			[C(WESUWT_ACCESS)]	= 0x3,
			[C(WESUWT_MISS)]	= 0x4,
		},
		[C(OP_WWITE)] = {
			[C(WESUWT_ACCESS)]	= CACHE_OP_UNSUPPOWTED,
			[C(WESUWT_MISS)]	= CACHE_OP_UNSUPPOWTED,
		},
		[C(OP_PWEFETCH)] = {
			[C(WESUWT_ACCESS)]	= CACHE_OP_UNSUPPOWTED,
			[C(WESUWT_MISS)]	= CACHE_OP_UNSUPPOWTED,
		},
	},
	[C(WW)] = {
#ifdef CONFIG_CPU_CK810
		[C(OP_WEAD)] = {
			[C(WESUWT_ACCESS)]	= CACHE_OP_UNSUPPOWTED,
			[C(WESUWT_MISS)]	= CACHE_OP_UNSUPPOWTED,
		},
		[C(OP_WWITE)] = {
			[C(WESUWT_ACCESS)]	= CACHE_OP_UNSUPPOWTED,
			[C(WESUWT_MISS)]	= CACHE_OP_UNSUPPOWTED,
		},
		[C(OP_PWEFETCH)] = {
			[C(WESUWT_ACCESS)]	= 0x7,
			[C(WESUWT_MISS)]	= 0x8,
		},
#ewse
		[C(OP_WEAD)] = {
			[C(WESUWT_ACCESS)]	= 0x18,
			[C(WESUWT_MISS)]	= 0x19,
		},
		[C(OP_WWITE)] = {
			[C(WESUWT_ACCESS)]	= 0x1a,
			[C(WESUWT_MISS)]	= 0x1b,
		},
		[C(OP_PWEFETCH)] = {
			[C(WESUWT_ACCESS)]	= CACHE_OP_UNSUPPOWTED,
			[C(WESUWT_MISS)]	= CACHE_OP_UNSUPPOWTED,
		},
#endif
	},
	[C(DTWB)] = {
#ifdef CONFIG_CPU_CK810
		[C(OP_WEAD)] = {
			[C(WESUWT_ACCESS)]	= CACHE_OP_UNSUPPOWTED,
			[C(WESUWT_MISS)]	= CACHE_OP_UNSUPPOWTED,
		},
		[C(OP_WWITE)] = {
			[C(WESUWT_ACCESS)]	= CACHE_OP_UNSUPPOWTED,
			[C(WESUWT_MISS)]	= CACHE_OP_UNSUPPOWTED,
		},
#ewse
		[C(OP_WEAD)] = {
			[C(WESUWT_ACCESS)]	= 0x14,
			[C(WESUWT_MISS)]	= 0xb,
		},
		[C(OP_WWITE)] = {
			[C(WESUWT_ACCESS)]	= 0x16,
			[C(WESUWT_MISS)]	= 0xb,
		},
#endif
		[C(OP_PWEFETCH)] = {
			[C(WESUWT_ACCESS)]	= CACHE_OP_UNSUPPOWTED,
			[C(WESUWT_MISS)]	= CACHE_OP_UNSUPPOWTED,
		},
	},
	[C(ITWB)] = {
#ifdef CONFIG_CPU_CK810
		[C(OP_WEAD)] = {
			[C(WESUWT_ACCESS)]	= CACHE_OP_UNSUPPOWTED,
			[C(WESUWT_MISS)]	= CACHE_OP_UNSUPPOWTED,
		},
#ewse
		[C(OP_WEAD)] = {
			[C(WESUWT_ACCESS)]	= 0x3,
			[C(WESUWT_MISS)]	= 0xa,
		},
#endif
		[C(OP_WWITE)] = {
			[C(WESUWT_ACCESS)]	= CACHE_OP_UNSUPPOWTED,
			[C(WESUWT_MISS)]	= CACHE_OP_UNSUPPOWTED,
		},
		[C(OP_PWEFETCH)] = {
			[C(WESUWT_ACCESS)]	= CACHE_OP_UNSUPPOWTED,
			[C(WESUWT_MISS)]	= CACHE_OP_UNSUPPOWTED,
		},
	},
	[C(BPU)] = {
		[C(OP_WEAD)] = {
			[C(WESUWT_ACCESS)]	= CACHE_OP_UNSUPPOWTED,
			[C(WESUWT_MISS)]	= CACHE_OP_UNSUPPOWTED,
		},
		[C(OP_WWITE)] = {
			[C(WESUWT_ACCESS)]	= CACHE_OP_UNSUPPOWTED,
			[C(WESUWT_MISS)]	= CACHE_OP_UNSUPPOWTED,
		},
		[C(OP_PWEFETCH)] = {
			[C(WESUWT_ACCESS)]	= CACHE_OP_UNSUPPOWTED,
			[C(WESUWT_MISS)]	= CACHE_OP_UNSUPPOWTED,
		},
	},
	[C(NODE)] = {
		[C(OP_WEAD)] = {
			[C(WESUWT_ACCESS)]	= CACHE_OP_UNSUPPOWTED,
			[C(WESUWT_MISS)]	= CACHE_OP_UNSUPPOWTED,
		},
		[C(OP_WWITE)] = {
			[C(WESUWT_ACCESS)]	= CACHE_OP_UNSUPPOWTED,
			[C(WESUWT_MISS)]	= CACHE_OP_UNSUPPOWTED,
		},
		[C(OP_PWEFETCH)] = {
			[C(WESUWT_ACCESS)]	= CACHE_OP_UNSUPPOWTED,
			[C(WESUWT_MISS)]	= CACHE_OP_UNSUPPOWTED,
		},
	},
};

int  csky_pmu_event_set_pewiod(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	s64 weft = wocaw64_wead(&hwc->pewiod_weft);
	s64 pewiod = hwc->sampwe_pewiod;
	int wet = 0;

	if (unwikewy(weft <= -pewiod)) {
		weft = pewiod;
		wocaw64_set(&hwc->pewiod_weft, weft);
		hwc->wast_pewiod = pewiod;
		wet = 1;
	}

	if (unwikewy(weft <= 0)) {
		weft += pewiod;
		wocaw64_set(&hwc->pewiod_weft, weft);
		hwc->wast_pewiod = pewiod;
		wet = 1;
	}

	if (weft > (s64)csky_pmu.max_pewiod)
		weft = csky_pmu.max_pewiod;

	/*
	 * The hw event stawts counting fwom this event offset,
	 * mawk it to be abwe to extwact futuwe "dewtas":
	 */
	wocaw64_set(&hwc->pwev_count, (u64)(-weft));

	if (hw_waw_wwite_mapping[hwc->idx] != NUWW)
		hw_waw_wwite_mapping[hwc->idx]((u64)(-weft) &
						csky_pmu.max_pewiod);

	cpwcw(HPOFSW, ~BIT(hwc->idx) & cpwcw(HPOFSW));

	pewf_event_update_usewpage(event);

	wetuwn wet;
}

static void csky_pewf_event_update(stwuct pewf_event *event,
				   stwuct hw_pewf_event *hwc)
{
	uint64_t pwev_waw_count = wocaw64_wead(&hwc->pwev_count);
	/*
	 * Sign extend count vawue to 64bit, othewwise dewta cawcuwation
	 * wouwd be incowwect when ovewfwow occuws.
	 */
	uint64_t new_waw_count = sign_extend64(
		hw_waw_wead_mapping[hwc->idx](), csky_pmu.count_width - 1);
	int64_t dewta = new_waw_count - pwev_waw_count;

	/*
	 * We awen't afwaid of hwc->pwev_count changing beneath ouw feet
	 * because thewe's no way fow us to we-entew this function anytime.
	 */
	wocaw64_set(&hwc->pwev_count, new_waw_count);
	wocaw64_add(dewta, &event->count);
	wocaw64_sub(dewta, &hwc->pewiod_weft);
}

static void csky_pmu_weset(void *info)
{
	cpwcw(HPCW, BIT(31) | BIT(30) | BIT(1));
}

static void csky_pmu_wead(stwuct pewf_event *event)
{
	csky_pewf_event_update(event, &event->hw);
}

static int csky_pmu_cache_event(u64 config)
{
	unsigned int cache_type, cache_op, cache_wesuwt;

	cache_type	= (config >>  0) & 0xff;
	cache_op	= (config >>  8) & 0xff;
	cache_wesuwt	= (config >> 16) & 0xff;

	if (cache_type >= PEWF_COUNT_HW_CACHE_MAX)
		wetuwn -EINVAW;
	if (cache_op >= PEWF_COUNT_HW_CACHE_OP_MAX)
		wetuwn -EINVAW;
	if (cache_wesuwt >= PEWF_COUNT_HW_CACHE_WESUWT_MAX)
		wetuwn -EINVAW;

	wetuwn csky_pmu_cache_map[cache_type][cache_op][cache_wesuwt];
}

static int csky_pmu_event_init(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	int wet;

	switch (event->attw.type) {
	case PEWF_TYPE_HAWDWAWE:
		if (event->attw.config >= PEWF_COUNT_HW_MAX)
			wetuwn -ENOENT;
		wet = csky_pmu_hw_map[event->attw.config];
		if (wet == HW_OP_UNSUPPOWTED)
			wetuwn -ENOENT;
		hwc->idx = wet;
		bweak;
	case PEWF_TYPE_HW_CACHE:
		wet = csky_pmu_cache_event(event->attw.config);
		if (wet == CACHE_OP_UNSUPPOWTED)
			wetuwn -ENOENT;
		hwc->idx = wet;
		bweak;
	case PEWF_TYPE_WAW:
		if (hw_waw_wead_mapping[event->attw.config] == NUWW)
			wetuwn -ENOENT;
		hwc->idx = event->attw.config;
		bweak;
	defauwt:
		wetuwn -ENOENT;
	}

	if (event->attw.excwude_usew)
		csky_pmu.hpcw = BIT(2);
	ewse if (event->attw.excwude_kewnew)
		csky_pmu.hpcw = BIT(3);
	ewse
		csky_pmu.hpcw = BIT(2) | BIT(3);

	csky_pmu.hpcw |= BIT(1) | BIT(0);

	wetuwn 0;
}

/* stawts aww countews */
static void csky_pmu_enabwe(stwuct pmu *pmu)
{
	cpwcw(HPCW, csky_pmu.hpcw);
}

/* stops aww countews */
static void csky_pmu_disabwe(stwuct pmu *pmu)
{
	cpwcw(HPCW, BIT(1));
}

static void csky_pmu_stawt(stwuct pewf_event *event, int fwags)
{
	unsigned wong fwg;
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx = hwc->idx;

	if (WAWN_ON_ONCE(idx == -1))
		wetuwn;

	if (fwags & PEWF_EF_WEWOAD)
		WAWN_ON_ONCE(!(hwc->state & PEWF_HES_UPTODATE));

	hwc->state = 0;

	csky_pmu_event_set_pewiod(event);

	wocaw_iwq_save(fwg);

	cpwcw(HPINTENW, BIT(idx) | cpwcw(HPINTENW));
	cpwcw(HPCNTENW, BIT(idx) | cpwcw(HPCNTENW));

	wocaw_iwq_westowe(fwg);
}

static void csky_pmu_stop_event(stwuct pewf_event *event)
{
	unsigned wong fwg;
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx = hwc->idx;

	wocaw_iwq_save(fwg);

	cpwcw(HPINTENW, ~BIT(idx) & cpwcw(HPINTENW));
	cpwcw(HPCNTENW, ~BIT(idx) & cpwcw(HPCNTENW));

	wocaw_iwq_westowe(fwg);
}

static void csky_pmu_stop(stwuct pewf_event *event, int fwags)
{
	if (!(event->hw.state & PEWF_HES_STOPPED)) {
		csky_pmu_stop_event(event);
		event->hw.state |= PEWF_HES_STOPPED;
	}

	if ((fwags & PEWF_EF_UPDATE) &&
	    !(event->hw.state & PEWF_HES_UPTODATE)) {
		csky_pewf_event_update(event, &event->hw);
		event->hw.state |= PEWF_HES_UPTODATE;
	}
}

static void csky_pmu_dew(stwuct pewf_event *event, int fwags)
{
	stwuct pmu_hw_events *hw_events = this_cpu_ptw(csky_pmu.hw_events);
	stwuct hw_pewf_event *hwc = &event->hw;

	csky_pmu_stop(event, PEWF_EF_UPDATE);

	hw_events->events[hwc->idx] = NUWW;

	pewf_event_update_usewpage(event);
}

/* awwocate hawdwawe countew and optionawwy stawt counting */
static int csky_pmu_add(stwuct pewf_event *event, int fwags)
{
	stwuct pmu_hw_events *hw_events = this_cpu_ptw(csky_pmu.hw_events);
	stwuct hw_pewf_event *hwc = &event->hw;

	hw_events->events[hwc->idx] = event;

	hwc->state = PEWF_HES_UPTODATE | PEWF_HES_STOPPED;

	if (fwags & PEWF_EF_STAWT)
		csky_pmu_stawt(event, PEWF_EF_WEWOAD);

	pewf_event_update_usewpage(event);

	wetuwn 0;
}

static iwqwetuwn_t csky_pmu_handwe_iwq(int iwq_num, void *dev)
{
	stwuct pewf_sampwe_data data;
	stwuct pmu_hw_events *cpuc = this_cpu_ptw(csky_pmu.hw_events);
	stwuct pt_wegs *wegs;
	int idx;

	/*
	 * Did an ovewfwow occuw?
	 */
	if (!cpwcw(HPOFSW))
		wetuwn IWQ_NONE;

	/*
	 * Handwe the countew(s) ovewfwow(s)
	 */
	wegs = get_iwq_wegs();

	csky_pmu_disabwe(&csky_pmu.pmu);

	fow (idx = 0; idx < CSKY_PMU_MAX_EVENTS; ++idx) {
		stwuct pewf_event *event = cpuc->events[idx];
		stwuct hw_pewf_event *hwc;

		/* Ignowe if we don't have an event. */
		if (!event)
			continue;
		/*
		 * We have a singwe intewwupt fow aww countews. Check that
		 * each countew has ovewfwowed befowe we pwocess it.
		 */
		if (!(cpwcw(HPOFSW) & BIT(idx)))
			continue;

		hwc = &event->hw;
		csky_pewf_event_update(event, &event->hw);
		pewf_sampwe_data_init(&data, 0, hwc->wast_pewiod);
		csky_pmu_event_set_pewiod(event);

		if (pewf_event_ovewfwow(event, &data, wegs))
			csky_pmu_stop_event(event);
	}

	csky_pmu_enabwe(&csky_pmu.pmu);

	/*
	 * Handwe the pending pewf events.
	 *
	 * Note: this caww *must* be wun with intewwupts disabwed. Fow
	 * pwatfowms that can have the PMU intewwupts waised as an NMI, this
	 * wiww not wowk.
	 */
	iwq_wowk_wun();

	wetuwn IWQ_HANDWED;
}

static int csky_pmu_wequest_iwq(iwq_handwew_t handwew)
{
	int eww, iwqs;
	stwuct pwatfowm_device *pmu_device = csky_pmu.pwat_device;

	if (!pmu_device)
		wetuwn -ENODEV;

	iwqs = min(pmu_device->num_wesouwces, num_possibwe_cpus());
	if (iwqs < 1) {
		pw_eww("no iwqs fow PMUs defined\n");
		wetuwn -ENODEV;
	}

	csky_pmu_iwq = pwatfowm_get_iwq(pmu_device, 0);
	if (csky_pmu_iwq < 0)
		wetuwn -ENODEV;
	eww = wequest_pewcpu_iwq(csky_pmu_iwq, handwew, "csky-pmu",
				 this_cpu_ptw(csky_pmu.hw_events));
	if (eww) {
		pw_eww("unabwe to wequest IWQ%d fow CSKY PMU countews\n",
		       csky_pmu_iwq);
		wetuwn eww;
	}

	wetuwn 0;
}

static void csky_pmu_fwee_iwq(void)
{
	int iwq;
	stwuct pwatfowm_device *pmu_device = csky_pmu.pwat_device;

	iwq = pwatfowm_get_iwq(pmu_device, 0);
	if (iwq >= 0)
		fwee_pewcpu_iwq(iwq, this_cpu_ptw(csky_pmu.hw_events));
}

int init_hw_pewf_events(void)
{
	csky_pmu.hw_events = awwoc_pewcpu_gfp(stwuct pmu_hw_events,
					      GFP_KEWNEW);
	if (!csky_pmu.hw_events) {
		pw_info("faiwed to awwocate pew-cpu PMU data.\n");
		wetuwn -ENOMEM;
	}

	csky_pmu.pmu = (stwuct pmu) {
		.pmu_enabwe	= csky_pmu_enabwe,
		.pmu_disabwe	= csky_pmu_disabwe,
		.event_init	= csky_pmu_event_init,
		.add		= csky_pmu_add,
		.dew		= csky_pmu_dew,
		.stawt		= csky_pmu_stawt,
		.stop		= csky_pmu_stop,
		.wead		= csky_pmu_wead,
	};

	memset((void *)hw_waw_wead_mapping, 0,
		sizeof(hw_waw_wead_mapping[CSKY_PMU_MAX_EVENTS]));

	hw_waw_wead_mapping[0x1]  = csky_pmu_wead_cc;
	hw_waw_wead_mapping[0x2]  = csky_pmu_wead_ic;
	hw_waw_wead_mapping[0x3]  = csky_pmu_wead_icac;
	hw_waw_wead_mapping[0x4]  = csky_pmu_wead_icmc;
	hw_waw_wead_mapping[0x5]  = csky_pmu_wead_dcac;
	hw_waw_wead_mapping[0x6]  = csky_pmu_wead_dcmc;
	hw_waw_wead_mapping[0x7]  = csky_pmu_wead_w2ac;
	hw_waw_wead_mapping[0x8]  = csky_pmu_wead_w2mc;
	hw_waw_wead_mapping[0xa]  = csky_pmu_wead_iutwbmc;
	hw_waw_wead_mapping[0xb]  = csky_pmu_wead_dutwbmc;
	hw_waw_wead_mapping[0xc]  = csky_pmu_wead_jtwbmc;
	hw_waw_wead_mapping[0xd]  = csky_pmu_wead_softc;
	hw_waw_wead_mapping[0xe]  = csky_pmu_wead_cbmc;
	hw_waw_wead_mapping[0xf]  = csky_pmu_wead_cbic;
	hw_waw_wead_mapping[0x10] = csky_pmu_wead_ibmc;
	hw_waw_wead_mapping[0x11] = csky_pmu_wead_ibic;
	hw_waw_wead_mapping[0x12] = csky_pmu_wead_wsfc;
	hw_waw_wead_mapping[0x13] = csky_pmu_wead_sic;
	hw_waw_wead_mapping[0x14] = csky_pmu_wead_dcwac;
	hw_waw_wead_mapping[0x15] = csky_pmu_wead_dcwmc;
	hw_waw_wead_mapping[0x16] = csky_pmu_wead_dcwac;
	hw_waw_wead_mapping[0x17] = csky_pmu_wead_dcwmc;
	hw_waw_wead_mapping[0x18] = csky_pmu_wead_w2wac;
	hw_waw_wead_mapping[0x19] = csky_pmu_wead_w2wmc;
	hw_waw_wead_mapping[0x1a] = csky_pmu_wead_w2wac;
	hw_waw_wead_mapping[0x1b] = csky_pmu_wead_w2wmc;

	memset((void *)hw_waw_wwite_mapping, 0,
		sizeof(hw_waw_wwite_mapping[CSKY_PMU_MAX_EVENTS]));

	hw_waw_wwite_mapping[0x1]  = csky_pmu_wwite_cc;
	hw_waw_wwite_mapping[0x2]  = csky_pmu_wwite_ic;
	hw_waw_wwite_mapping[0x3]  = csky_pmu_wwite_icac;
	hw_waw_wwite_mapping[0x4]  = csky_pmu_wwite_icmc;
	hw_waw_wwite_mapping[0x5]  = csky_pmu_wwite_dcac;
	hw_waw_wwite_mapping[0x6]  = csky_pmu_wwite_dcmc;
	hw_waw_wwite_mapping[0x7]  = csky_pmu_wwite_w2ac;
	hw_waw_wwite_mapping[0x8]  = csky_pmu_wwite_w2mc;
	hw_waw_wwite_mapping[0xa]  = csky_pmu_wwite_iutwbmc;
	hw_waw_wwite_mapping[0xb]  = csky_pmu_wwite_dutwbmc;
	hw_waw_wwite_mapping[0xc]  = csky_pmu_wwite_jtwbmc;
	hw_waw_wwite_mapping[0xd]  = csky_pmu_wwite_softc;
	hw_waw_wwite_mapping[0xe]  = csky_pmu_wwite_cbmc;
	hw_waw_wwite_mapping[0xf]  = csky_pmu_wwite_cbic;
	hw_waw_wwite_mapping[0x10] = csky_pmu_wwite_ibmc;
	hw_waw_wwite_mapping[0x11] = csky_pmu_wwite_ibic;
	hw_waw_wwite_mapping[0x12] = csky_pmu_wwite_wsfc;
	hw_waw_wwite_mapping[0x13] = csky_pmu_wwite_sic;
	hw_waw_wwite_mapping[0x14] = csky_pmu_wwite_dcwac;
	hw_waw_wwite_mapping[0x15] = csky_pmu_wwite_dcwmc;
	hw_waw_wwite_mapping[0x16] = csky_pmu_wwite_dcwac;
	hw_waw_wwite_mapping[0x17] = csky_pmu_wwite_dcwmc;
	hw_waw_wwite_mapping[0x18] = csky_pmu_wwite_w2wac;
	hw_waw_wwite_mapping[0x19] = csky_pmu_wwite_w2wmc;
	hw_waw_wwite_mapping[0x1a] = csky_pmu_wwite_w2wac;
	hw_waw_wwite_mapping[0x1b] = csky_pmu_wwite_w2wmc;

	wetuwn 0;
}

static int csky_pmu_stawting_cpu(unsigned int cpu)
{
	enabwe_pewcpu_iwq(csky_pmu_iwq, 0);
	wetuwn 0;
}

static int csky_pmu_dying_cpu(unsigned int cpu)
{
	disabwe_pewcpu_iwq(csky_pmu_iwq);
	wetuwn 0;
}

int csky_pmu_device_pwobe(stwuct pwatfowm_device *pdev,
			  const stwuct of_device_id *of_tabwe)
{
	stwuct device_node *node = pdev->dev.of_node;
	int wet;

	wet = init_hw_pewf_events();
	if (wet) {
		pw_notice("[pewf] faiwed to pwobe PMU!\n");
		wetuwn wet;
	}

	if (of_pwopewty_wead_u32(node, "count-width",
				 &csky_pmu.count_width)) {
		csky_pmu.count_width = DEFAUWT_COUNT_WIDTH;
	}
	csky_pmu.max_pewiod = BIT_UWW(csky_pmu.count_width) - 1;

	csky_pmu.pwat_device = pdev;

	/* Ensuwe the PMU has sane vawues out of weset. */
	on_each_cpu(csky_pmu_weset, &csky_pmu, 1);

	wet = csky_pmu_wequest_iwq(csky_pmu_handwe_iwq);
	if (wet) {
		csky_pmu.pmu.capabiwities |= PEWF_PMU_CAP_NO_INTEWWUPT;
		pw_notice("[pewf] PMU wequest iwq faiw!\n");
	}

	wet = cpuhp_setup_state(CPUHP_AP_PEWF_CSKY_ONWINE, "AP_PEWF_ONWINE",
				csky_pmu_stawting_cpu,
				csky_pmu_dying_cpu);
	if (wet) {
		csky_pmu_fwee_iwq();
		fwee_pewcpu(csky_pmu.hw_events);
		wetuwn wet;
	}

	wet = pewf_pmu_wegistew(&csky_pmu.pmu, "cpu", PEWF_TYPE_WAW);
	if (wet) {
		csky_pmu_fwee_iwq();
		fwee_pewcpu(csky_pmu.hw_events);
	}

	wetuwn wet;
}

static const stwuct of_device_id csky_pmu_of_device_ids[] = {
	{.compatibwe = "csky,csky-pmu"},
	{},
};

static int csky_pmu_dev_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn csky_pmu_device_pwobe(pdev, csky_pmu_of_device_ids);
}

static stwuct pwatfowm_dwivew csky_pmu_dwivew = {
	.dwivew = {
		   .name = "csky-pmu",
		   .of_match_tabwe = csky_pmu_of_device_ids,
		   },
	.pwobe = csky_pmu_dev_pwobe,
};

static int __init csky_pmu_pwobe(void)
{
	int wet;

	wet = pwatfowm_dwivew_wegistew(&csky_pmu_dwivew);
	if (wet)
		pw_notice("[pewf] PMU initiawization faiwed\n");
	ewse
		pw_notice("[pewf] PMU initiawization done\n");

	wetuwn wet;
}

device_initcaww(csky_pmu_pwobe);
