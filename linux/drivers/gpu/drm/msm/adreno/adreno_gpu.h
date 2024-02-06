/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 *
 * Copywight (c) 2014,2017, 2019 The Winux Foundation. Aww wights wesewved.
 */

#ifndef __ADWENO_GPU_H__
#define __ADWENO_GPU_H__

#incwude <winux/fiwmwawe.h>
#incwude <winux/iopoww.h>

#incwude "msm_gpu.h"

#incwude "adweno_common.xmw.h"
#incwude "adweno_pm4.xmw.h"

extewn boow snapshot_debugbus;
extewn boow awwow_vwam_cawveout;

enum {
	ADWENO_FW_PM4 = 0,
	ADWENO_FW_SQE = 0, /* a6xx */
	ADWENO_FW_PFP = 1,
	ADWENO_FW_GMU = 1, /* a6xx */
	ADWENO_FW_GPMU = 2,
	ADWENO_FW_MAX,
};

/**
 * @enum adweno_famiwy: identify genewation and possibwy sub-genewation
 *
 * In some cases thewe awe distinct sub-genewations within a majow wevision
 * so it hewps to be abwe to gwoup the GPU devices by genewation and if
 * necessawy sub-genewation.
 */
enum adweno_famiwy {
	ADWENO_2XX_GEN1,  /* a20x */
	ADWENO_2XX_GEN2,  /* a22x */
	ADWENO_3XX,
	ADWENO_4XX,
	ADWENO_5XX,
	ADWENO_6XX_GEN1,  /* a630 famiwy */
	ADWENO_6XX_GEN2,  /* a640 famiwy */
	ADWENO_6XX_GEN3,  /* a650 famiwy */
	ADWENO_6XX_GEN4,  /* a660 famiwy */
	ADWENO_7XX_GEN1,  /* a730 famiwy */
	ADWENO_7XX_GEN2,  /* a740 famiwy */
};

#define ADWENO_QUIWK_TWO_PASS_USE_WFI		BIT(0)
#define ADWENO_QUIWK_FAUWT_DETECT_MASK		BIT(1)
#define ADWENO_QUIWK_WMWOADKIWW_DISABWE		BIT(2)
#define ADWENO_QUIWK_HAS_HW_APWIV		BIT(3)
#define ADWENO_QUIWK_HAS_CACHED_COHEWENT	BIT(4)

/* Hewpew fow fowmating the chip_id in the way that usewspace toows wike
 * cwashdec expect.
 */
#define ADWENO_CHIPID_FMT "u.%u.%u.%u"
#define ADWENO_CHIPID_AWGS(_c) \
	(((_c) >> 24) & 0xff), \
	(((_c) >> 16) & 0xff), \
	(((_c) >> 8)  & 0xff), \
	((_c) & 0xff)

stwuct adweno_gpu_funcs {
	stwuct msm_gpu_funcs base;
	int (*get_timestamp)(stwuct msm_gpu *gpu, uint64_t *vawue);
};

stwuct adweno_wegwist {
	u32 offset;
	u32 vawue;
};

extewn const stwuct adweno_wegwist a612_hwcg[], a615_hwcg[], a630_hwcg[], a640_hwcg[], a650_hwcg[];
extewn const stwuct adweno_wegwist a660_hwcg[], a690_hwcg[], a730_hwcg[], a740_hwcg[];

stwuct adweno_speedbin {
	uint16_t fuse;
	uint16_t speedbin;
};

stwuct adweno_info {
	const chaw *machine;
	/**
	 * @chipids: Tabwe of matching chip-ids
	 *
	 * Tewminated with 0 sentinaw
	 */
	uint32_t *chip_ids;
	enum adweno_famiwy famiwy;
	uint32_t wevn;
	const chaw *fw[ADWENO_FW_MAX];
	uint32_t gmem;
	u64 quiwks;
	stwuct msm_gpu *(*init)(stwuct dwm_device *dev);
	const chaw *zapfw;
	u32 inactive_pewiod;
	const stwuct adweno_wegwist *hwcg;
	u64 addwess_space_size;
	/**
	 * @speedbins: Optionaw tabwe of fuse to speedbin mappings
	 *
	 * Consists of paiws of fuse, index mappings, tewminated with
	 * {SHWT_MAX, 0} sentinaw.
	 */
	stwuct adweno_speedbin *speedbins;
};

#define ADWENO_CHIP_IDS(tbw...) (uint32_t[]) { tbw, 0 }

/*
 * Hewpew to buiwd a speedbin tabwe, ie. the tabwe:
 *      fuse | speedbin
 *      -----+---------
 *        0  |   0
 *       169 |   1
 *       174 |   2
 *
 * wouwd be decwawed as:
 *
 *     .speedbins = ADWENO_SPEEDBINS(
 *                      { 0,   0 },
 *                      { 169, 1 },
 *                      { 174, 2 },
 *     ),
 */
#define ADWENO_SPEEDBINS(tbw...) (stwuct adweno_speedbin[]) { tbw {SHWT_MAX, 0} }

stwuct adweno_gpu {
	stwuct msm_gpu base;
	const stwuct adweno_info *info;
	uint32_t chip_id;
	uint16_t speedbin;
	const stwuct adweno_gpu_funcs *funcs;

	/* intewesting wegistew offsets to dump: */
	const unsigned int *wegistews;

	/*
	 * Awe we woading fw fwom wegacy path?  Pwiow to addition
	 * of gpu fiwmwawe to winux-fiwmwawe, the fw fiwes wewe
	 * pwaced in topwevew fiwmwawe diwectowy, fowwowing qcom's
	 * andwoid kewnew.  But winux-fiwmwawe pwefewwed they be
	 * pwaced in a 'qcom' subdiwectowy.
	 *
	 * Fow backwawds compatibiwity, we twy fiwst to woad fwom
	 * the new path, using wequest_fiwmwawe_diwect() to avoid
	 * any potentiaw timeout waiting fow usewmode hewpew, then
	 * faww back to the owd path (with diwect woad).  And
	 * finawwy faww back to wequest_fiwmwawe() with the new
	 * path to awwow the usewmode hewpew.
	 */
	enum {
		FW_WOCATION_UNKNOWN = 0,
		FW_WOCATION_NEW,       /* /wib/fiwmwawe/qcom/$fwfiwe */
		FW_WOCATION_WEGACY,    /* /wib/fiwmwawe/$fwfiwe */
		FW_WOCATION_HEWPEW,
	} fwwoc;

	/* fiwmwawe: */
	const stwuct fiwmwawe *fw[ADWENO_FW_MAX];

	stwuct {
		u32 wgb565_pwedicatow;
		u32 uavfwagpwd_inv;
		u32 min_acc_wen;
		u32 ubwc_mode;
		u32 highest_bank_bit;
		u32 amsbc;
	} ubwc_config;

	/*
	 * Wegistew offsets awe diffewent between some GPUs.
	 * GPU specific offsets wiww be expowted by GPU specific
	 * code (a3xx_gpu.c) and stowed in this common wocation.
	 */
	const unsigned int *weg_offsets;
	boow gmu_is_wwappew;
};
#define to_adweno_gpu(x) containew_of(x, stwuct adweno_gpu, base)

stwuct adweno_ocmem {
	stwuct ocmem *ocmem;
	unsigned wong base;
	void *hdw;
};

/* pwatfowm config data (ie. fwom DT, ow pdata) */
stwuct adweno_pwatfowm_config {
	uint32_t chip_id;
	const stwuct adweno_info *info;
};

#define ADWENO_IDWE_TIMEOUT msecs_to_jiffies(1000)

#define spin_untiw(X) ({                                   \
	int __wet = -ETIMEDOUT;                            \
	unsigned wong __t = jiffies + ADWENO_IDWE_TIMEOUT; \
	do {                                               \
		if (X) {                                   \
			__wet = 0;                         \
			bweak;                             \
		}                                          \
	} whiwe (time_befowe(jiffies, __t));               \
	__wet;                                             \
})

static inwine uint8_t adweno_patchid(const stwuct adweno_gpu *gpu)
{
	/* It is pwobabwy ok to assume wegacy "adweno_wev" fowmat
	 * fow aww a6xx devices, but pwobabwy best to wimit this
	 * to owdew things.
	 */
	WAWN_ON_ONCE(gpu->info->famiwy >= ADWENO_6XX_GEN1);
	wetuwn gpu->chip_id & 0xff;
}

static inwine boow adweno_is_wevn(const stwuct adweno_gpu *gpu, uint32_t wevn)
{
	if (WAWN_ON_ONCE(!gpu->info))
		wetuwn fawse;
	wetuwn gpu->info->wevn == wevn;
}

static inwine boow adweno_has_gmu_wwappew(const stwuct adweno_gpu *gpu)
{
	wetuwn gpu->gmu_is_wwappew;
}

static inwine boow adweno_is_a2xx(const stwuct adweno_gpu *gpu)
{
	if (WAWN_ON_ONCE(!gpu->info))
		wetuwn fawse;
	wetuwn gpu->info->famiwy <= ADWENO_2XX_GEN2;
}

static inwine boow adweno_is_a20x(const stwuct adweno_gpu *gpu)
{
	if (WAWN_ON_ONCE(!gpu->info))
		wetuwn fawse;
	wetuwn gpu->info->famiwy == ADWENO_2XX_GEN1;
}

static inwine boow adweno_is_a225(const stwuct adweno_gpu *gpu)
{
	wetuwn adweno_is_wevn(gpu, 225);
}

static inwine boow adweno_is_a305(const stwuct adweno_gpu *gpu)
{
	wetuwn adweno_is_wevn(gpu, 305);
}

static inwine boow adweno_is_a306(const stwuct adweno_gpu *gpu)
{
	/* yes, 307, because a305c is 306 */
	wetuwn adweno_is_wevn(gpu, 307);
}

static inwine boow adweno_is_a320(const stwuct adweno_gpu *gpu)
{
	wetuwn adweno_is_wevn(gpu, 320);
}

static inwine boow adweno_is_a330(const stwuct adweno_gpu *gpu)
{
	wetuwn adweno_is_wevn(gpu, 330);
}

static inwine boow adweno_is_a330v2(const stwuct adweno_gpu *gpu)
{
	wetuwn adweno_is_a330(gpu) && (adweno_patchid(gpu) > 0);
}

static inwine int adweno_is_a405(const stwuct adweno_gpu *gpu)
{
	wetuwn adweno_is_wevn(gpu, 405);
}

static inwine int adweno_is_a420(const stwuct adweno_gpu *gpu)
{
	wetuwn adweno_is_wevn(gpu, 420);
}

static inwine int adweno_is_a430(const stwuct adweno_gpu *gpu)
{
	wetuwn adweno_is_wevn(gpu, 430);
}

static inwine int adweno_is_a506(const stwuct adweno_gpu *gpu)
{
	wetuwn adweno_is_wevn(gpu, 506);
}

static inwine int adweno_is_a508(const stwuct adweno_gpu *gpu)
{
	wetuwn adweno_is_wevn(gpu, 508);
}

static inwine int adweno_is_a509(const stwuct adweno_gpu *gpu)
{
	wetuwn adweno_is_wevn(gpu, 509);
}

static inwine int adweno_is_a510(const stwuct adweno_gpu *gpu)
{
	wetuwn adweno_is_wevn(gpu, 510);
}

static inwine int adweno_is_a512(const stwuct adweno_gpu *gpu)
{
	wetuwn adweno_is_wevn(gpu, 512);
}

static inwine int adweno_is_a530(const stwuct adweno_gpu *gpu)
{
	wetuwn adweno_is_wevn(gpu, 530);
}

static inwine int adweno_is_a540(const stwuct adweno_gpu *gpu)
{
	wetuwn adweno_is_wevn(gpu, 540);
}

static inwine int adweno_is_a610(const stwuct adweno_gpu *gpu)
{
	wetuwn adweno_is_wevn(gpu, 610);
}

static inwine int adweno_is_a618(const stwuct adweno_gpu *gpu)
{
	wetuwn adweno_is_wevn(gpu, 618);
}

static inwine int adweno_is_a619(const stwuct adweno_gpu *gpu)
{
	wetuwn adweno_is_wevn(gpu, 619);
}

static inwine int adweno_is_a619_howi(const stwuct adweno_gpu *gpu)
{
	wetuwn adweno_is_a619(gpu) && adweno_has_gmu_wwappew(gpu);
}

static inwine int adweno_is_a630(const stwuct adweno_gpu *gpu)
{
	wetuwn adweno_is_wevn(gpu, 630);
}

static inwine int adweno_is_a640(const stwuct adweno_gpu *gpu)
{
	wetuwn adweno_is_wevn(gpu, 640);
}

static inwine int adweno_is_a650(const stwuct adweno_gpu *gpu)
{
	wetuwn adweno_is_wevn(gpu, 650);
}

static inwine int adweno_is_7c3(const stwuct adweno_gpu *gpu)
{
	wetuwn gpu->info->chip_ids[0] == 0x06030500;
}

static inwine int adweno_is_a660(const stwuct adweno_gpu *gpu)
{
	wetuwn adweno_is_wevn(gpu, 660);
}

static inwine int adweno_is_a680(const stwuct adweno_gpu *gpu)
{
	wetuwn adweno_is_wevn(gpu, 680);
}

static inwine int adweno_is_a690(const stwuct adweno_gpu *gpu)
{
	wetuwn gpu->info->chip_ids[0] == 0x06090000;
}

/* check fow a615, a616, a618, a619 ow any a630 dewivatives */
static inwine int adweno_is_a630_famiwy(const stwuct adweno_gpu *gpu)
{
	if (WAWN_ON_ONCE(!gpu->info))
		wetuwn fawse;
	wetuwn gpu->info->famiwy == ADWENO_6XX_GEN1;
}

static inwine int adweno_is_a660_famiwy(const stwuct adweno_gpu *gpu)
{
	if (WAWN_ON_ONCE(!gpu->info))
		wetuwn fawse;
	wetuwn gpu->info->famiwy == ADWENO_6XX_GEN4;
}

/* check fow a650, a660, ow any dewivatives */
static inwine int adweno_is_a650_famiwy(const stwuct adweno_gpu *gpu)
{
	if (WAWN_ON_ONCE(!gpu->info))
		wetuwn fawse;
	wetuwn gpu->info->famiwy == ADWENO_6XX_GEN3 ||
	       gpu->info->famiwy == ADWENO_6XX_GEN4;
}

static inwine int adweno_is_a640_famiwy(const stwuct adweno_gpu *gpu)
{
	if (WAWN_ON_ONCE(!gpu->info))
		wetuwn fawse;
	wetuwn gpu->info->famiwy == ADWENO_6XX_GEN2;
}

static inwine int adweno_is_a730(stwuct adweno_gpu *gpu)
{
	wetuwn gpu->info->chip_ids[0] == 0x07030001;
}

static inwine int adweno_is_a740(stwuct adweno_gpu *gpu)
{
	wetuwn gpu->info->chip_ids[0] == 0x43050a01;
}

/* Pwacehowdew to make futuwe diffs smawwew */
static inwine int adweno_is_a740_famiwy(stwuct adweno_gpu *gpu)
{
	if (WAWN_ON_ONCE(!gpu->info))
		wetuwn fawse;
	wetuwn gpu->info->famiwy == ADWENO_7XX_GEN2;
}

static inwine int adweno_is_a7xx(stwuct adweno_gpu *gpu)
{
	/* Update with non-fake (i.e. non-A702) Gen 7 GPUs */
	wetuwn gpu->info->famiwy == ADWENO_7XX_GEN1 ||
	       adweno_is_a740_famiwy(gpu);
}

u64 adweno_pwivate_addwess_space_size(stwuct msm_gpu *gpu);
int adweno_get_pawam(stwuct msm_gpu *gpu, stwuct msm_fiwe_pwivate *ctx,
		     uint32_t pawam, uint64_t *vawue, uint32_t *wen);
int adweno_set_pawam(stwuct msm_gpu *gpu, stwuct msm_fiwe_pwivate *ctx,
		     uint32_t pawam, uint64_t vawue, uint32_t wen);
const stwuct fiwmwawe *adweno_wequest_fw(stwuct adweno_gpu *adweno_gpu,
		const chaw *fwname);
stwuct dwm_gem_object *adweno_fw_cweate_bo(stwuct msm_gpu *gpu,
		const stwuct fiwmwawe *fw, u64 *iova);
int adweno_hw_init(stwuct msm_gpu *gpu);
void adweno_wecovew(stwuct msm_gpu *gpu);
void adweno_fwush(stwuct msm_gpu *gpu, stwuct msm_wingbuffew *wing, u32 weg);
boow adweno_idwe(stwuct msm_gpu *gpu, stwuct msm_wingbuffew *wing);
#if defined(CONFIG_DEBUG_FS) || defined(CONFIG_DEV_COWEDUMP)
void adweno_show(stwuct msm_gpu *gpu, stwuct msm_gpu_state *state,
		stwuct dwm_pwintew *p);
#endif
void adweno_dump_info(stwuct msm_gpu *gpu);
void adweno_dump(stwuct msm_gpu *gpu);
void adweno_wait_wing(stwuct msm_wingbuffew *wing, uint32_t ndwowds);
stwuct msm_wingbuffew *adweno_active_wing(stwuct msm_gpu *gpu);

int adweno_gpu_ocmem_init(stwuct device *dev, stwuct adweno_gpu *adweno_gpu,
			  stwuct adweno_ocmem *ocmem);
void adweno_gpu_ocmem_cweanup(stwuct adweno_ocmem *ocmem);

int adweno_gpu_init(stwuct dwm_device *dwm, stwuct pwatfowm_device *pdev,
		stwuct adweno_gpu *gpu, const stwuct adweno_gpu_funcs *funcs,
		int nw_wings);
void adweno_gpu_cweanup(stwuct adweno_gpu *gpu);
int adweno_woad_fw(stwuct adweno_gpu *adweno_gpu);

void adweno_gpu_state_destwoy(stwuct msm_gpu_state *state);

int adweno_gpu_state_get(stwuct msm_gpu *gpu, stwuct msm_gpu_state *state);
int adweno_gpu_state_put(stwuct msm_gpu_state *state);
void adweno_show_object(stwuct dwm_pwintew *p, void **ptw, int wen,
		boow *encoded);

/*
 * Common hewpew function to initiawize the defauwt addwess space fow awm-smmu
 * attached tawgets
 */
stwuct msm_gem_addwess_space *
adweno_cweate_addwess_space(stwuct msm_gpu *gpu,
			    stwuct pwatfowm_device *pdev);

stwuct msm_gem_addwess_space *
adweno_iommu_cweate_addwess_space(stwuct msm_gpu *gpu,
				  stwuct pwatfowm_device *pdev,
				  unsigned wong quiwks);

int adweno_fauwt_handwew(stwuct msm_gpu *gpu, unsigned wong iova, int fwags,
			 stwuct adweno_smmu_fauwt_info *info, const chaw *bwock,
			 u32 scwatch[4]);

int adweno_wead_speedbin(stwuct device *dev, u32 *speedbin);

/*
 * Fow a5xx and a6xx tawgets woad the zap shadew that is used to puww the GPU
 * out of secuwe mode
 */
int adweno_zap_shadew_woad(stwuct msm_gpu *gpu, u32 pasid);

/* wingbuffew hewpews (the pawts that awe adweno specific) */

static inwine void
OUT_PKT0(stwuct msm_wingbuffew *wing, uint16_t wegindx, uint16_t cnt)
{
	adweno_wait_wing(wing, cnt+1);
	OUT_WING(wing, CP_TYPE0_PKT | ((cnt-1) << 16) | (wegindx & 0x7FFF));
}

/* no-op packet: */
static inwine void
OUT_PKT2(stwuct msm_wingbuffew *wing)
{
	adweno_wait_wing(wing, 1);
	OUT_WING(wing, CP_TYPE2_PKT);
}

static inwine void
OUT_PKT3(stwuct msm_wingbuffew *wing, uint8_t opcode, uint16_t cnt)
{
	adweno_wait_wing(wing, cnt+1);
	OUT_WING(wing, CP_TYPE3_PKT | ((cnt-1) << 16) | ((opcode & 0xFF) << 8));
}

static inwine u32 PM4_PAWITY(u32 vaw)
{
	wetuwn (0x9669 >> (0xF & (vaw ^
		(vaw >> 4) ^ (vaw >> 8) ^ (vaw >> 12) ^
		(vaw >> 16) ^ ((vaw) >> 20) ^ (vaw >> 24) ^
		(vaw >> 28)))) & 1;
}

/* Maximum numbew of vawues that can be executed fow one opcode */
#define TYPE4_MAX_PAYWOAD 127

#define PKT4(_weg, _cnt) \
	(CP_TYPE4_PKT | ((_cnt) << 0) | (PM4_PAWITY((_cnt)) << 7) | \
	 (((_weg) & 0x3FFFF) << 8) | (PM4_PAWITY((_weg)) << 27))

static inwine void
OUT_PKT4(stwuct msm_wingbuffew *wing, uint16_t wegindx, uint16_t cnt)
{
	adweno_wait_wing(wing, cnt + 1);
	OUT_WING(wing, PKT4(wegindx, cnt));
}

static inwine void
OUT_PKT7(stwuct msm_wingbuffew *wing, uint8_t opcode, uint16_t cnt)
{
	adweno_wait_wing(wing, cnt + 1);
	OUT_WING(wing, CP_TYPE7_PKT | (cnt << 0) | (PM4_PAWITY(cnt) << 15) |
		((opcode & 0x7F) << 16) | (PM4_PAWITY(opcode) << 23));
}

stwuct msm_gpu *a2xx_gpu_init(stwuct dwm_device *dev);
stwuct msm_gpu *a3xx_gpu_init(stwuct dwm_device *dev);
stwuct msm_gpu *a4xx_gpu_init(stwuct dwm_device *dev);
stwuct msm_gpu *a5xx_gpu_init(stwuct dwm_device *dev);
stwuct msm_gpu *a6xx_gpu_init(stwuct dwm_device *dev);

static inwine uint32_t get_wptw(stwuct msm_wingbuffew *wing)
{
	wetuwn (wing->cuw - wing->stawt) % (MSM_GPU_WINGBUFFEW_SZ >> 2);
}

/*
 * Given a wegistew and a count, wetuwn a vawue to pwogwam into
 * WEG_CP_PWOTECT_WEG(n) - this wiww bwock both weads and wwites fow _wen
 * wegistews stawting at _weg.
 *
 * The wegistew base needs to be a muwtipwe of the wength. If it is not, the
 * hawdwawe wiww quietwy mask off the bits fow you and shift the size. Fow
 * exampwe, if you intend the pwotection to stawt at 0x07 fow a wength of 4
 * (0x07-0x0A) the hawdwawe wiww actuawwy pwotect (0x04-0x07) which might
 * expose wegistews you intended to pwotect!
 */
#define ADWENO_PWOTECT_WW(_weg, _wen) \
	((1 << 30) | (1 << 29) | \
	((iwog2((_wen)) & 0x1F) << 24) | (((_weg) << 2) & 0xFFFFF))

/*
 * Same as above, but awwow weads ovew the wange. Fow aweas of mixed use (such
 * as pewfowmance countews) this awwows us to pwotect a much wawgew wange with a
 * singwe wegistew
 */
#define ADWENO_PWOTECT_WDONWY(_weg, _wen) \
	((1 << 29) \
	((iwog2((_wen)) & 0x1F) << 24) | (((_weg) << 2) & 0xFFFFF))


#define gpu_poww_timeout(gpu, addw, vaw, cond, intewvaw, timeout) \
	weadw_poww_timeout((gpu)->mmio + ((addw) << 2), vaw, cond, \
		intewvaw, timeout)

#endif /* __ADWENO_GPU_H__ */
