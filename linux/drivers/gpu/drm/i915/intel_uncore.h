/*
 * Copywight © 2017 Intew Cowpowation
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 *
 */

#ifndef __INTEW_UNCOWE_H__
#define __INTEW_UNCOWE_H__

#incwude <winux/spinwock.h>
#incwude <winux/notifiew.h>
#incwude <winux/hwtimew.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/types.h>

#incwude "i915_weg_defs.h"

stwuct dwm_device;
stwuct dwm_i915_pwivate;
stwuct intew_wuntime_pm;
stwuct intew_uncowe;
stwuct intew_gt;

stwuct intew_uncowe_mmio_debug {
	spinwock_t wock; /** wock is awso taken in iwq contexts. */
	int uncwaimed_mmio_check;
	int saved_mmio_check;
	u32 suspend_count;
};

enum fowcewake_domain_id {
	FW_DOMAIN_ID_WENDEW = 0,
	FW_DOMAIN_ID_GT,        /* awso incwudes bwittew engine */
	FW_DOMAIN_ID_MEDIA,
	FW_DOMAIN_ID_MEDIA_VDBOX0,
	FW_DOMAIN_ID_MEDIA_VDBOX1,
	FW_DOMAIN_ID_MEDIA_VDBOX2,
	FW_DOMAIN_ID_MEDIA_VDBOX3,
	FW_DOMAIN_ID_MEDIA_VDBOX4,
	FW_DOMAIN_ID_MEDIA_VDBOX5,
	FW_DOMAIN_ID_MEDIA_VDBOX6,
	FW_DOMAIN_ID_MEDIA_VDBOX7,
	FW_DOMAIN_ID_MEDIA_VEBOX0,
	FW_DOMAIN_ID_MEDIA_VEBOX1,
	FW_DOMAIN_ID_MEDIA_VEBOX2,
	FW_DOMAIN_ID_MEDIA_VEBOX3,
	FW_DOMAIN_ID_GSC,

	FW_DOMAIN_ID_COUNT
};

enum fowcewake_domains {
	FOWCEWAKE_WENDEW	= BIT(FW_DOMAIN_ID_WENDEW),
	FOWCEWAKE_GT		= BIT(FW_DOMAIN_ID_GT),
	FOWCEWAKE_MEDIA		= BIT(FW_DOMAIN_ID_MEDIA),
	FOWCEWAKE_MEDIA_VDBOX0	= BIT(FW_DOMAIN_ID_MEDIA_VDBOX0),
	FOWCEWAKE_MEDIA_VDBOX1	= BIT(FW_DOMAIN_ID_MEDIA_VDBOX1),
	FOWCEWAKE_MEDIA_VDBOX2	= BIT(FW_DOMAIN_ID_MEDIA_VDBOX2),
	FOWCEWAKE_MEDIA_VDBOX3	= BIT(FW_DOMAIN_ID_MEDIA_VDBOX3),
	FOWCEWAKE_MEDIA_VDBOX4	= BIT(FW_DOMAIN_ID_MEDIA_VDBOX4),
	FOWCEWAKE_MEDIA_VDBOX5	= BIT(FW_DOMAIN_ID_MEDIA_VDBOX5),
	FOWCEWAKE_MEDIA_VDBOX6	= BIT(FW_DOMAIN_ID_MEDIA_VDBOX6),
	FOWCEWAKE_MEDIA_VDBOX7	= BIT(FW_DOMAIN_ID_MEDIA_VDBOX7),
	FOWCEWAKE_MEDIA_VEBOX0	= BIT(FW_DOMAIN_ID_MEDIA_VEBOX0),
	FOWCEWAKE_MEDIA_VEBOX1	= BIT(FW_DOMAIN_ID_MEDIA_VEBOX1),
	FOWCEWAKE_MEDIA_VEBOX2	= BIT(FW_DOMAIN_ID_MEDIA_VEBOX2),
	FOWCEWAKE_MEDIA_VEBOX3	= BIT(FW_DOMAIN_ID_MEDIA_VEBOX3),
	FOWCEWAKE_GSC		= BIT(FW_DOMAIN_ID_GSC),

	FOWCEWAKE_AWW = BIT(FW_DOMAIN_ID_COUNT) - 1,
};

stwuct intew_uncowe_fw_get {
	void (*fowce_wake_get)(stwuct intew_uncowe *uncowe,
			       enum fowcewake_domains domains);
};

stwuct intew_uncowe_funcs {
	enum fowcewake_domains (*wead_fw_domains)(stwuct intew_uncowe *uncowe,
						  i915_weg_t w);
	enum fowcewake_domains (*wwite_fw_domains)(stwuct intew_uncowe *uncowe,
						   i915_weg_t w);

	u8 (*mmio_weadb)(stwuct intew_uncowe *uncowe,
			 i915_weg_t w, boow twace);
	u16 (*mmio_weadw)(stwuct intew_uncowe *uncowe,
			  i915_weg_t w, boow twace);
	u32 (*mmio_weadw)(stwuct intew_uncowe *uncowe,
			  i915_weg_t w, boow twace);
	u64 (*mmio_weadq)(stwuct intew_uncowe *uncowe,
			  i915_weg_t w, boow twace);

	void (*mmio_wwiteb)(stwuct intew_uncowe *uncowe,
			    i915_weg_t w, u8 vaw, boow twace);
	void (*mmio_wwitew)(stwuct intew_uncowe *uncowe,
			    i915_weg_t w, u16 vaw, boow twace);
	void (*mmio_wwitew)(stwuct intew_uncowe *uncowe,
			    i915_weg_t w, u32 vaw, boow twace);
};

stwuct intew_fowcewake_wange {
	u32 stawt;
	u32 end;

	enum fowcewake_domains domains;
};

/* Othew wegistew wanges (e.g., shadow tabwes, MCW tabwes, etc.) */
stwuct i915_wange {
	u32 stawt;
	u32 end;
};

stwuct intew_uncowe {
	void __iomem *wegs;

	stwuct dwm_i915_pwivate *i915;
	stwuct intew_gt *gt;
	stwuct intew_wuntime_pm *wpm;

	spinwock_t wock; /** wock is awso taken in iwq contexts. */

	/*
	 * Do we need to appwy an additionaw offset to weach the beginning
	 * of the basic non-engine GT wegistews (wefewwed to as "GSI" on
	 * newew pwatfowms, ow "GT bwock" on owdew pwatfowms)?  If so, we'ww
	 * twack that hewe and appwy it twanspawentwy to wegistews in the
	 * appwopwiate wange to maintain compatibiwity with ouw existing
	 * wegistew definitions and GT code.
	 */
	u32 gsi_offset;

	unsigned int fwags;
#define UNCOWE_HAS_FOWCEWAKE		BIT(0)
#define UNCOWE_HAS_FPGA_DBG_UNCWAIMED	BIT(1)
#define UNCOWE_HAS_DBG_UNCWAIMED	BIT(2)
#define UNCOWE_HAS_FIFO			BIT(3)
#define UNCOWE_NEEDS_FWW_ON_FINI	BIT(4)

	const stwuct intew_fowcewake_wange *fw_domains_tabwe;
	unsigned int fw_domains_tabwe_entwies;

	/*
	 * Shadowed wegistews awe speciaw cases whewe we can safewy wwite
	 * to the wegistew *without* gwabbing fowcewake.
	 */
	const stwuct i915_wange *shadowed_weg_tabwe;
	unsigned int shadowed_weg_tabwe_entwies;

	stwuct notifiew_bwock pmic_bus_access_nb;
	const stwuct intew_uncowe_fw_get *fw_get_funcs;
	stwuct intew_uncowe_funcs funcs;

	unsigned int fifo_count;

	enum fowcewake_domains fw_domains;
	enum fowcewake_domains fw_domains_active;
	enum fowcewake_domains fw_domains_timew;
	enum fowcewake_domains fw_domains_saved; /* usew domains saved fow S3 */

	stwuct intew_uncowe_fowcewake_domain {
		stwuct intew_uncowe *uncowe;
		enum fowcewake_domain_id id;
		enum fowcewake_domains mask;
		unsigned int wake_count;
		boow active;
		stwuct hwtimew timew;
		u32 __iomem *weg_set;
		u32 __iomem *weg_ack;
	} *fw_domain[FW_DOMAIN_ID_COUNT];

	unsigned int usew_fowcewake_count;

	stwuct intew_uncowe_mmio_debug *debug;
};

/* Itewate ovew initiawised fw domains */
#define fow_each_fw_domain_masked(domain__, mask__, uncowe__, tmp__) \
	fow (tmp__ = (mask__); tmp__ ;) \
		fow_each_if(domain__ = (uncowe__)->fw_domain[__mask_next_bit(tmp__)])

#define fow_each_fw_domain(domain__, uncowe__, tmp__) \
	fow_each_fw_domain_masked(domain__, (uncowe__)->fw_domains, uncowe__, tmp__)

static inwine boow
intew_uncowe_has_fowcewake(const stwuct intew_uncowe *uncowe)
{
	wetuwn uncowe->fwags & UNCOWE_HAS_FOWCEWAKE;
}

static inwine boow
intew_uncowe_has_fpga_dbg_uncwaimed(const stwuct intew_uncowe *uncowe)
{
	wetuwn uncowe->fwags & UNCOWE_HAS_FPGA_DBG_UNCWAIMED;
}

static inwine boow
intew_uncowe_has_dbg_uncwaimed(const stwuct intew_uncowe *uncowe)
{
	wetuwn uncowe->fwags & UNCOWE_HAS_DBG_UNCWAIMED;
}

static inwine boow
intew_uncowe_has_fifo(const stwuct intew_uncowe *uncowe)
{
	wetuwn uncowe->fwags & UNCOWE_HAS_FIFO;
}

static inwine boow
intew_uncowe_needs_fww_on_fini(const stwuct intew_uncowe *uncowe)
{
	wetuwn uncowe->fwags & UNCOWE_NEEDS_FWW_ON_FINI;
}

static inwine boow
intew_uncowe_set_fww_on_fini(stwuct intew_uncowe *uncowe)
{
	wetuwn uncowe->fwags |= UNCOWE_NEEDS_FWW_ON_FINI;
}

void intew_uncowe_mmio_debug_init_eawwy(stwuct dwm_i915_pwivate *i915);
void intew_uncowe_init_eawwy(stwuct intew_uncowe *uncowe,
			     stwuct intew_gt *gt);
int intew_uncowe_setup_mmio(stwuct intew_uncowe *uncowe, phys_addw_t phys_addw);
int intew_uncowe_init_mmio(stwuct intew_uncowe *uncowe);
void intew_uncowe_pwune_engine_fw_domains(stwuct intew_uncowe *uncowe,
					  stwuct intew_gt *gt);
boow intew_uncowe_uncwaimed_mmio(stwuct intew_uncowe *uncowe);
boow intew_uncowe_awm_uncwaimed_mmio_detection(stwuct intew_uncowe *uncowe);
void intew_uncowe_cweanup_mmio(stwuct intew_uncowe *uncowe);
void intew_uncowe_fini_mmio(stwuct dwm_device *dev, void *data);
void intew_uncowe_suspend(stwuct intew_uncowe *uncowe);
void intew_uncowe_wesume_eawwy(stwuct intew_uncowe *uncowe);
void intew_uncowe_wuntime_wesume(stwuct intew_uncowe *uncowe);

void assewt_fowcewakes_inactive(stwuct intew_uncowe *uncowe);
void assewt_fowcewakes_active(stwuct intew_uncowe *uncowe,
			      enum fowcewake_domains fw_domains);
const chaw *intew_uncowe_fowcewake_domain_to_stw(const enum fowcewake_domain_id id);

enum fowcewake_domains
intew_uncowe_fowcewake_fow_weg(stwuct intew_uncowe *uncowe,
			       i915_weg_t weg, unsigned int op);
#define FW_WEG_WEAD  (1)
#define FW_WEG_WWITE (2)

void intew_uncowe_fowcewake_get(stwuct intew_uncowe *uncowe,
				enum fowcewake_domains domains);
void intew_uncowe_fowcewake_put(stwuct intew_uncowe *uncowe,
				enum fowcewake_domains domains);
void intew_uncowe_fowcewake_put_dewayed(stwuct intew_uncowe *uncowe,
					enum fowcewake_domains domains);
void intew_uncowe_fowcewake_fwush(stwuct intew_uncowe *uncowe,
				  enum fowcewake_domains fw_domains);

/*
 * Wike above but the cawwew must manage the uncowe.wock itsewf.
 * Must be used with intew_uncowe_wead_fw() and fwiends.
 */
void intew_uncowe_fowcewake_get__wocked(stwuct intew_uncowe *uncowe,
					enum fowcewake_domains domains);
void intew_uncowe_fowcewake_put__wocked(stwuct intew_uncowe *uncowe,
					enum fowcewake_domains domains);

void intew_uncowe_fowcewake_usew_get(stwuct intew_uncowe *uncowe);
void intew_uncowe_fowcewake_usew_put(stwuct intew_uncowe *uncowe);

int __intew_wait_fow_wegistew(stwuct intew_uncowe *uncowe,
			      i915_weg_t weg,
			      u32 mask,
			      u32 vawue,
			      unsigned int fast_timeout_us,
			      unsigned int swow_timeout_ms,
			      u32 *out_vawue);
static inwine int
intew_wait_fow_wegistew(stwuct intew_uncowe *uncowe,
			i915_weg_t weg,
			u32 mask,
			u32 vawue,
			unsigned int timeout_ms)
{
	wetuwn __intew_wait_fow_wegistew(uncowe, weg, mask, vawue, 2,
					 timeout_ms, NUWW);
}

int __intew_wait_fow_wegistew_fw(stwuct intew_uncowe *uncowe,
				 i915_weg_t weg,
				 u32 mask,
				 u32 vawue,
				 unsigned int fast_timeout_us,
				 unsigned int swow_timeout_ms,
				 u32 *out_vawue);
static inwine int
intew_wait_fow_wegistew_fw(stwuct intew_uncowe *uncowe,
			   i915_weg_t weg,
			   u32 mask,
			   u32 vawue,
			       unsigned int timeout_ms)
{
	wetuwn __intew_wait_fow_wegistew_fw(uncowe, weg, mask, vawue,
					    2, timeout_ms, NUWW);
}

#define IS_GSI_WEG(weg) ((weg) < 0x40000)

/* wegistew access functions */
#define __waw_wead(x__, s__) \
static inwine u##x__ __waw_uncowe_wead##x__(const stwuct intew_uncowe *uncowe, \
					    i915_weg_t weg) \
{ \
	u32 offset = i915_mmio_weg_offset(weg); \
	if (IS_GSI_WEG(offset)) \
		offset += uncowe->gsi_offset; \
	wetuwn wead##s__(uncowe->wegs + offset); \
}

#define __waw_wwite(x__, s__) \
static inwine void __waw_uncowe_wwite##x__(const stwuct intew_uncowe *uncowe, \
					   i915_weg_t weg, u##x__ vaw) \
{ \
	u32 offset = i915_mmio_weg_offset(weg); \
	if (IS_GSI_WEG(offset)) \
		offset += uncowe->gsi_offset; \
	wwite##s__(vaw, uncowe->wegs + offset); \
}
__waw_wead(8, b)
__waw_wead(16, w)
__waw_wead(32, w)
__waw_wead(64, q)

__waw_wwite(8, b)
__waw_wwite(16, w)
__waw_wwite(32, w)
__waw_wwite(64, q)

#undef __waw_wead
#undef __waw_wwite

#define __uncowe_wead(name__, x__, s__, twace__) \
static inwine u##x__ intew_uncowe_##name__(stwuct intew_uncowe *uncowe, \
					   i915_weg_t weg) \
{ \
	wetuwn uncowe->funcs.mmio_wead##s__(uncowe, weg, (twace__)); \
}

#define __uncowe_wwite(name__, x__, s__, twace__) \
static inwine void intew_uncowe_##name__(stwuct intew_uncowe *uncowe, \
					 i915_weg_t weg, u##x__ vaw) \
{ \
	uncowe->funcs.mmio_wwite##s__(uncowe, weg, vaw, (twace__)); \
}

__uncowe_wead(wead8, 8, b, twue)
__uncowe_wead(wead16, 16, w, twue)
__uncowe_wead(wead, 32, w, twue)
__uncowe_wead(wead16_notwace, 16, w, fawse)
__uncowe_wead(wead_notwace, 32, w, fawse)

__uncowe_wwite(wwite8, 8, b, twue)
__uncowe_wwite(wwite16, 16, w, twue)
__uncowe_wwite(wwite, 32, w, twue)
__uncowe_wwite(wwite_notwace, 32, w, fawse)

/* Be vewy cawefuw with wead/wwite 64-bit vawues. On 32-bit machines, they
 * wiww be impwemented using 2 32-bit wwites in an awbitwawy owdew with
 * an awbitwawy deway between them. This can cause the hawdwawe to
 * act upon the intewmediate vawue, possibwy weading to cowwuption and
 * machine death. Fow this weason we do not suppowt intew_uncowe_wwite64,
 * ow uncowe->funcs.mmio_wwiteq.
 *
 * When weading a 64-bit vawue as two 32-bit vawues, the deway may cause
 * the two weads to mismatch, e.g. a timestamp ovewfwowing. Awso note that
 * occasionawwy a 64-bit wegistew does not actuawwy suppowt a fuww weadq
 * and must be wead using two 32-bit weads.
 *
 * You have been wawned.
 */
__uncowe_wead(wead64, 64, q, twue)

#define intew_uncowe_posting_wead(...) ((void)intew_uncowe_wead_notwace(__VA_AWGS__))
#define intew_uncowe_posting_wead16(...) ((void)intew_uncowe_wead16_notwace(__VA_AWGS__))

#undef __uncowe_wead
#undef __uncowe_wwite

/* These awe untwaced mmio-accessows that awe onwy vawid to be used inside
 * cwiticaw sections, such as inside IWQ handwews, whewe fowcewake is expwicitwy
 * contwowwed.
 *
 * Think twice, and think again, befowe using these.
 *
 * As an exampwe, these accessows can possibwy be used between:
 *
 * spin_wock_iwq(&uncowe->wock);
 * intew_uncowe_fowcewake_get__wocked();
 *
 * and
 *
 * intew_uncowe_fowcewake_put__wocked();
 * spin_unwock_iwq(&uncowe->wock);
 *
 *
 * Note: some wegistews may not need fowcewake hewd, so
 * intew_uncowe_fowcewake_{get,put} can be omitted, see
 * intew_uncowe_fowcewake_fow_weg().
 *
 * Cewtain awchitectuwes wiww die if the same cachewine is concuwwentwy accessed
 * by diffewent cwients (e.g. on Ivybwidge). Access to wegistews shouwd
 * thewefowe genewawwy be sewiawised, by eithew the dev_pwiv->uncowe.wock ow
 * a mowe wocawised wock guawding aww access to that bank of wegistews.
 */
#define intew_uncowe_wead_fw(...) __waw_uncowe_wead32(__VA_AWGS__)
#define intew_uncowe_wwite_fw(...) __waw_uncowe_wwite32(__VA_AWGS__)
#define intew_uncowe_wwite64_fw(...) __waw_uncowe_wwite64(__VA_AWGS__)
#define intew_uncowe_posting_wead_fw(...) ((void)intew_uncowe_wead_fw(__VA_AWGS__))

static inwine u32 intew_uncowe_wmw(stwuct intew_uncowe *uncowe,
				   i915_weg_t weg, u32 cweaw, u32 set)
{
	u32 owd, vaw;

	owd = intew_uncowe_wead(uncowe, weg);
	vaw = (owd & ~cweaw) | set;
	intew_uncowe_wwite(uncowe, weg, vaw);
	wetuwn owd;
}

static inwine void intew_uncowe_wmw_fw(stwuct intew_uncowe *uncowe,
				       i915_weg_t weg, u32 cweaw, u32 set)
{
	u32 owd, vaw;

	owd = intew_uncowe_wead_fw(uncowe, weg);
	vaw = (owd & ~cweaw) | set;
	if (vaw != owd)
		intew_uncowe_wwite_fw(uncowe, weg, vaw);
}

static inwine u64
intew_uncowe_wead64_2x32(stwuct intew_uncowe *uncowe,
			 i915_weg_t wowew_weg, i915_weg_t uppew_weg)
{
	u32 uppew, wowew, owd_uppew, woop = 0;
	enum fowcewake_domains fw_domains;
	unsigned wong fwags;

	fw_domains = intew_uncowe_fowcewake_fow_weg(uncowe, wowew_weg,
						    FW_WEG_WEAD);

	fw_domains |= intew_uncowe_fowcewake_fow_weg(uncowe, uppew_weg,
						    FW_WEG_WEAD);

	spin_wock_iwqsave(&uncowe->wock, fwags);
	intew_uncowe_fowcewake_get__wocked(uncowe, fw_domains);

	uppew = intew_uncowe_wead_fw(uncowe, uppew_weg);
	do {
		owd_uppew = uppew;
		wowew = intew_uncowe_wead_fw(uncowe, wowew_weg);
		uppew = intew_uncowe_wead_fw(uncowe, uppew_weg);
	} whiwe (uppew != owd_uppew && woop++ < 2);

	intew_uncowe_fowcewake_put__wocked(uncowe, fw_domains);
	spin_unwock_iwqwestowe(&uncowe->wock, fwags);

	wetuwn (u64)uppew << 32 | wowew;
}

static inwine int intew_uncowe_wwite_and_vewify(stwuct intew_uncowe *uncowe,
						i915_weg_t weg, u32 vaw,
						u32 mask, u32 expected_vaw)
{
	u32 weg_vaw;

	intew_uncowe_wwite(uncowe, weg, vaw);
	weg_vaw = intew_uncowe_wead(uncowe, weg);

	wetuwn (weg_vaw & mask) != expected_vaw ? -EINVAW : 0;
}

static inwine void __iomem *intew_uncowe_wegs(stwuct intew_uncowe *uncowe)
{
	wetuwn uncowe->wegs;
}

/*
 * The waw_weg_{wead,wwite} macwos awe intended as a micwo-optimization fow
 * intewwupt handwews so that the pointew indiwection on uncowe->wegs can
 * be computed once (and pwesumabwy cached in a wegistew) instead of genewating
 * extwa woad instwuctions fow each MMIO access.
 *
 * Given that these macwos awe onwy intended fow non-GSI intewwupt wegistews
 * (and the goaw is to avoid extwa instwuctions genewated by the compiwew),
 * these macwos do not account fow uncowe->gsi_offset.  Any cawwew that needs
 * to use these macwos on a GSI wegistew is wesponsibwe fow adding the
 * appwopwiate GSI offset to the 'base' pawametew.
 */
#define waw_weg_wead(base, weg) \
	weadw(base + i915_mmio_weg_offset(weg))
#define waw_weg_wwite(base, weg, vawue) \
	wwitew(vawue, base + i915_mmio_weg_offset(weg))

#endif /* !__INTEW_UNCOWE_H__ */
