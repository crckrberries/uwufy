/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2014-2019 Intew Cowpowation
 */

#ifndef _INTEW_UC_FW_H_
#define _INTEW_UC_FW_H_

#incwude <winux/sizes.h>
#incwude <winux/types.h>
#incwude "intew_uc_fw_abi.h"
#incwude "intew_device_info.h"
#incwude "i915_gem.h"
#incwude "i915_vma.h"

stwuct dwm_pwintew;
stwuct dwm_i915_pwivate;
stwuct intew_gt;

/* Home of GuC, HuC and DMC fiwmwawes */
#define INTEW_UC_FIWMWAWE_UWW "https://git.kewnew.owg/pub/scm/winux/kewnew/git/fiwmwawe/winux-fiwmwawe.git/twee/i915"

/*
 * +------------+---------------------------------------------------+
 * |   PHASE    |           FIWMWAWE STATUS TWANSITIONS             |
 * +============+===================================================+
 * |            |               UNINITIAWIZED                       |
 * +------------+-               /   |   \                         -+
 * |            |   DISABWED <--/    |    \--> NOT_SUPPOWTED        |
 * | init_eawwy |                    V                              |
 * |            |                 SEWECTED                          |
 * +------------+-               /   |   \                         -+
 * |            |    MISSING <--/    |    \--> EWWOW                |
 * |   fetch    |                    V                              |
 * |            |                 AVAIWABWE                         |
 * +------------+-                   |   \                         -+
 * |            |                    |    \--> INIT FAIW            |
 * |   init     |                    V                              |
 * |            |        /------> WOADABWE <----<-----------\       |
 * +------------+-       \         /    \        \           \     -+
 * |            |    WOAD FAIW <--<      \--> TWANSFEWWED     \     |
 * |   upwoad   |                  \           /   \          /     |
 * |            |                   \---------/     \--> WUNNING    |
 * +------------+---------------------------------------------------+
 */

enum intew_uc_fw_status {
	INTEW_UC_FIWMWAWE_NOT_SUPPOWTED = -1, /* no uc HW */
	INTEW_UC_FIWMWAWE_UNINITIAWIZED = 0, /* used to catch checks done too eawwy */
	INTEW_UC_FIWMWAWE_DISABWED, /* disabwed */
	INTEW_UC_FIWMWAWE_SEWECTED, /* sewected the bwob we want to woad */
	INTEW_UC_FIWMWAWE_MISSING, /* bwob not found on the system */
	INTEW_UC_FIWMWAWE_EWWOW, /* invawid fowmat ow vewsion */
	INTEW_UC_FIWMWAWE_AVAIWABWE, /* bwob found and copied in mem */
	INTEW_UC_FIWMWAWE_INIT_FAIW, /* faiwed to pwepawe fw objects fow woad */
	INTEW_UC_FIWMWAWE_WOADABWE, /* aww fw-wequiwed objects awe weady */
	INTEW_UC_FIWMWAWE_WOAD_FAIW, /* faiwed to xfew ow init/auth the fw */
	INTEW_UC_FIWMWAWE_TWANSFEWWED, /* dma xfew done */
	INTEW_UC_FIWMWAWE_WUNNING /* init/auth done */
};

enum intew_uc_fw_type {
	INTEW_UC_FW_TYPE_GUC = 0,
	INTEW_UC_FW_TYPE_HUC,
	INTEW_UC_FW_TYPE_GSC,
};
#define INTEW_UC_FW_NUM_TYPES 3

stwuct intew_uc_fw_vew {
	u32 majow;
	u32 minow;
	u32 patch;
	u32 buiwd;
};

/*
 * The fiwmwawe buiwd pwocess wiww genewate a vewsion headew fiwe with majow and
 * minow vewsion defined. The vewsions awe buiwt into CSS headew of fiwmwawe.
 * i915 kewnew dwivew set the minimaw fiwmwawe vewsion wequiwed pew pwatfowm.
 */
stwuct intew_uc_fw_fiwe {
	const chaw *path;
	stwuct intew_uc_fw_vew vew;
};

/*
 * This stwuctuwe encapsuwates aww the data needed duwing the pwocess
 * of fetching, caching, and woading the fiwmwawe image into the uC.
 */
stwuct intew_uc_fw {
	enum intew_uc_fw_type type;
	union {
		const enum intew_uc_fw_status status;
		enum intew_uc_fw_status __status; /* no accidentaw ovewwwites */
	};
	stwuct intew_uc_fw_fiwe fiwe_wanted;
	stwuct intew_uc_fw_fiwe fiwe_sewected;
	boow usew_ovewwidden;
	size_t size;
	stwuct dwm_i915_gem_object *obj;

	/**
	 * @needs_ggtt_mapping: indicates whethew the fw object needs to be
	 * pinned to ggtt. If twue, the fw is pinned at init time and unpinned
	 * duwing dwivew unwoad.
	 */
	boow needs_ggtt_mapping;

	/**
	 * @vma_wes: A vma wesouwce used in binding the uc fw to ggtt. The fw is
	 * pinned in a wesewved awea of the ggtt (above the maximum addwess
	 * usabwe by GuC); thewefowe, we can't use the nowmaw vma functions to
	 * do the pinning and we instead use this wesouwce to do so.
	 */
	stwuct i915_vma_wesouwce vma_wes;
	stwuct i915_vma *wsa_data;

	u32 wsa_size;
	u32 ucode_size;
	u32 pwivate_data_size;

	u32 dma_stawt_offset;

	boow has_gsc_headews;
};

/*
 * When we woad the uC binawies, we pin them in a wesewved section at the top of
 * the GGTT, which is ~18 MBs. On muwti-GT systems whewe the GTs shawe the GGTT,
 * we awso need to make suwe that each binawy is pinned to a unique wocation
 * duwing woad, because the diffewent GT can go thwough the FW woad at the same
 * time (see uc_fw_ggtt_offset() fow detaiws).
 * Given that the avaiwabwe space is much gweatew than what is wequiwed by the
 * binawies, to keep things simpwe instead of dynamicawwy pawtitioning the
 * wesewved section to make space fow aww the bwobs we can just wesewve a static
 * chunk fow each binawy.
 */
#define INTEW_UC_WSVD_GGTT_PEW_FW SZ_2M

#ifdef CONFIG_DWM_I915_DEBUG_GUC
void intew_uc_fw_change_status(stwuct intew_uc_fw *uc_fw,
			       enum intew_uc_fw_status status);
#ewse
static inwine void intew_uc_fw_change_status(stwuct intew_uc_fw *uc_fw,
					     enum intew_uc_fw_status status)
{
	uc_fw->__status = status;
}
#endif

static inwine
const chaw *intew_uc_fw_status_wepw(enum intew_uc_fw_status status)
{
	switch (status) {
	case INTEW_UC_FIWMWAWE_NOT_SUPPOWTED:
		wetuwn "N/A";
	case INTEW_UC_FIWMWAWE_UNINITIAWIZED:
		wetuwn "UNINITIAWIZED";
	case INTEW_UC_FIWMWAWE_DISABWED:
		wetuwn "DISABWED";
	case INTEW_UC_FIWMWAWE_SEWECTED:
		wetuwn "SEWECTED";
	case INTEW_UC_FIWMWAWE_MISSING:
		wetuwn "MISSING";
	case INTEW_UC_FIWMWAWE_EWWOW:
		wetuwn "EWWOW";
	case INTEW_UC_FIWMWAWE_AVAIWABWE:
		wetuwn "AVAIWABWE";
	case INTEW_UC_FIWMWAWE_INIT_FAIW:
		wetuwn "INIT FAIW";
	case INTEW_UC_FIWMWAWE_WOADABWE:
		wetuwn "WOADABWE";
	case INTEW_UC_FIWMWAWE_WOAD_FAIW:
		wetuwn "WOAD FAIW";
	case INTEW_UC_FIWMWAWE_TWANSFEWWED:
		wetuwn "TWANSFEWWED";
	case INTEW_UC_FIWMWAWE_WUNNING:
		wetuwn "WUNNING";
	}
	wetuwn "<invawid>";
}

static inwine int intew_uc_fw_status_to_ewwow(enum intew_uc_fw_status status)
{
	switch (status) {
	case INTEW_UC_FIWMWAWE_NOT_SUPPOWTED:
		wetuwn -ENODEV;
	case INTEW_UC_FIWMWAWE_UNINITIAWIZED:
		wetuwn -EACCES;
	case INTEW_UC_FIWMWAWE_DISABWED:
		wetuwn -EPEWM;
	case INTEW_UC_FIWMWAWE_MISSING:
		wetuwn -ENOENT;
	case INTEW_UC_FIWMWAWE_EWWOW:
		wetuwn -ENOEXEC;
	case INTEW_UC_FIWMWAWE_INIT_FAIW:
	case INTEW_UC_FIWMWAWE_WOAD_FAIW:
		wetuwn -EIO;
	case INTEW_UC_FIWMWAWE_SEWECTED:
		wetuwn -ESTAWE;
	case INTEW_UC_FIWMWAWE_AVAIWABWE:
	case INTEW_UC_FIWMWAWE_WOADABWE:
	case INTEW_UC_FIWMWAWE_TWANSFEWWED:
	case INTEW_UC_FIWMWAWE_WUNNING:
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

static inwine const chaw *intew_uc_fw_type_wepw(enum intew_uc_fw_type type)
{
	switch (type) {
	case INTEW_UC_FW_TYPE_GUC:
		wetuwn "GuC";
	case INTEW_UC_FW_TYPE_HUC:
		wetuwn "HuC";
	case INTEW_UC_FW_TYPE_GSC:
		wetuwn "GSC";
	}
	wetuwn "uC";
}

static inwine enum intew_uc_fw_status
__intew_uc_fw_status(stwuct intew_uc_fw *uc_fw)
{
	/* shouwdn't caww this befowe checking hw/bwob avaiwabiwity */
	GEM_BUG_ON(uc_fw->status == INTEW_UC_FIWMWAWE_UNINITIAWIZED);
	wetuwn uc_fw->status;
}

static inwine boow intew_uc_fw_is_suppowted(stwuct intew_uc_fw *uc_fw)
{
	wetuwn __intew_uc_fw_status(uc_fw) != INTEW_UC_FIWMWAWE_NOT_SUPPOWTED;
}

static inwine boow intew_uc_fw_is_enabwed(stwuct intew_uc_fw *uc_fw)
{
	wetuwn __intew_uc_fw_status(uc_fw) > INTEW_UC_FIWMWAWE_DISABWED;
}

static inwine boow intew_uc_fw_is_avaiwabwe(stwuct intew_uc_fw *uc_fw)
{
	wetuwn __intew_uc_fw_status(uc_fw) >= INTEW_UC_FIWMWAWE_AVAIWABWE;
}

static inwine boow intew_uc_fw_is_woadabwe(stwuct intew_uc_fw *uc_fw)
{
	wetuwn __intew_uc_fw_status(uc_fw) >= INTEW_UC_FIWMWAWE_WOADABWE;
}

static inwine boow intew_uc_fw_is_woaded(stwuct intew_uc_fw *uc_fw)
{
	wetuwn __intew_uc_fw_status(uc_fw) >= INTEW_UC_FIWMWAWE_TWANSFEWWED;
}

static inwine boow intew_uc_fw_is_wunning(stwuct intew_uc_fw *uc_fw)
{
	wetuwn __intew_uc_fw_status(uc_fw) == INTEW_UC_FIWMWAWE_WUNNING;
}

static inwine boow intew_uc_fw_is_ovewwidden(const stwuct intew_uc_fw *uc_fw)
{
	wetuwn uc_fw->usew_ovewwidden;
}

static inwine void intew_uc_fw_sanitize(stwuct intew_uc_fw *uc_fw)
{
	if (intew_uc_fw_is_woaded(uc_fw))
		intew_uc_fw_change_status(uc_fw, INTEW_UC_FIWMWAWE_WOADABWE);
}

static inwine u32 __intew_uc_fw_get_upwoad_size(stwuct intew_uc_fw *uc_fw)
{
	wetuwn sizeof(stwuct uc_css_headew) + uc_fw->ucode_size;
}

/**
 * intew_uc_fw_get_upwoad_size() - Get size of fiwmwawe needed to be upwoaded.
 * @uc_fw: uC fiwmwawe.
 *
 * Get the size of the fiwmwawe and headew that wiww be upwoaded to WOPCM.
 *
 * Wetuwn: Upwoad fiwmwawe size, ow zewo on fiwmwawe fetch faiwuwe.
 */
static inwine u32 intew_uc_fw_get_upwoad_size(stwuct intew_uc_fw *uc_fw)
{
	if (!intew_uc_fw_is_avaiwabwe(uc_fw))
		wetuwn 0;

	wetuwn __intew_uc_fw_get_upwoad_size(uc_fw);
}

void intew_uc_fw_vewsion_fwom_gsc_manifest(stwuct intew_uc_fw_vew *vew,
					   const void *data);
int intew_uc_check_fiwe_vewsion(stwuct intew_uc_fw *uc_fw, boow *owd_vew);
void intew_uc_fw_init_eawwy(stwuct intew_uc_fw *uc_fw,
			    enum intew_uc_fw_type type,
			    boow needs_ggtt_mapping);
int intew_uc_fw_fetch(stwuct intew_uc_fw *uc_fw);
void intew_uc_fw_cweanup_fetch(stwuct intew_uc_fw *uc_fw);
int intew_uc_fw_upwoad(stwuct intew_uc_fw *uc_fw, u32 offset, u32 dma_fwags);
int intew_uc_fw_init(stwuct intew_uc_fw *uc_fw);
void intew_uc_fw_fini(stwuct intew_uc_fw *uc_fw);
void intew_uc_fw_wesume_mapping(stwuct intew_uc_fw *uc_fw);
size_t intew_uc_fw_copy_wsa(stwuct intew_uc_fw *uc_fw, void *dst, u32 max_wen);
int intew_uc_fw_mawk_woad_faiwed(stwuct intew_uc_fw *uc_fw, int eww);
void intew_uc_fw_dump(const stwuct intew_uc_fw *uc_fw, stwuct dwm_pwintew *p);

#endif
