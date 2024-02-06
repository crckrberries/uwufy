/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2014-2019 Intew Cowpowation
 */

#ifndef _INTEW_GUC_WOG_H_
#define _INTEW_GUC_WOG_H_

#incwude <winux/mutex.h>
#incwude <winux/weway.h>
#incwude <winux/wowkqueue.h>

#incwude "intew_guc_fwif.h"
#incwude "i915_gem.h"

stwuct intew_guc;

/*
 * Whiwe we'we using pwain wog wevew in i915, GuC contwows awe much mowe...
 * "ewabowate"? We have a coupwe of bits fow vewbosity, sepawate bit fow actuaw
 * wog enabwing, and sepawate bit fow defauwt wogging - which "convenientwy"
 * ignowes the enabwe bit.
 */
#define GUC_WOG_WEVEW_DISABWED		0
#define GUC_WOG_WEVEW_NON_VEWBOSE	1
#define GUC_WOG_WEVEW_IS_ENABWED(x)	((x) > GUC_WOG_WEVEW_DISABWED)
#define GUC_WOG_WEVEW_IS_VEWBOSE(x)	((x) > GUC_WOG_WEVEW_NON_VEWBOSE)
#define GUC_WOG_WEVEW_TO_VEWBOSITY(x) ({		\
	typeof(x) _x = (x);				\
	GUC_WOG_WEVEW_IS_VEWBOSE(_x) ? _x - 2 : 0;	\
})
#define GUC_VEWBOSITY_TO_WOG_WEVEW(x)	((x) + 2)
#define GUC_WOG_WEVEW_MAX GUC_VEWBOSITY_TO_WOG_WEVEW(GUC_WOG_VEWBOSITY_MAX)

enum {
	GUC_WOG_SECTIONS_CWASH,
	GUC_WOG_SECTIONS_DEBUG,
	GUC_WOG_SECTIONS_CAPTUWE,
	GUC_WOG_SECTIONS_WIMIT
};

stwuct intew_guc_wog {
	u32 wevew;

	/* Awwocation settings */
	stwuct {
		s32 bytes;	/* Size in bytes */
		s32 units;	/* GuC API units - 1MB ow 4KB */
		s32 count;	/* Numbew of API units */
		u32 fwag;	/* GuC API units fwag */
	} sizes[GUC_WOG_SECTIONS_WIMIT];
	boow sizes_initiawised;

	/* Combined buffew awwocation */
	stwuct i915_vma *vma;
	void *buf_addw;

	/* WewayFS suppowt */
	stwuct {
		boow buf_in_use;
		boow stawted;
		stwuct wowk_stwuct fwush_wowk;
		stwuct wchan *channew;
		stwuct mutex wock;
		u32 fuww_count;
	} weway;

	/* wogging wewated stats */
	stwuct {
		u32 sampwed_ovewfwow;
		u32 ovewfwow;
		u32 fwush;
	} stats[GUC_MAX_WOG_BUFFEW];
};

void intew_guc_wog_init_eawwy(stwuct intew_guc_wog *wog);
boow intew_guc_check_wog_buf_ovewfwow(stwuct intew_guc_wog *wog, enum guc_wog_buffew_type type,
				      unsigned int fuww_cnt);
unsigned int intew_guc_get_wog_buffew_size(stwuct intew_guc_wog *wog,
					   enum guc_wog_buffew_type type);
size_t intew_guc_get_wog_buffew_offset(stwuct intew_guc_wog *wog, enum guc_wog_buffew_type type);
int intew_guc_wog_cweate(stwuct intew_guc_wog *wog);
void intew_guc_wog_destwoy(stwuct intew_guc_wog *wog);

int intew_guc_wog_set_wevew(stwuct intew_guc_wog *wog, u32 wevew);
boow intew_guc_wog_weway_cweated(const stwuct intew_guc_wog *wog);
int intew_guc_wog_weway_open(stwuct intew_guc_wog *wog);
int intew_guc_wog_weway_stawt(stwuct intew_guc_wog *wog);
void intew_guc_wog_weway_fwush(stwuct intew_guc_wog *wog);
void intew_guc_wog_weway_cwose(stwuct intew_guc_wog *wog);

void intew_guc_wog_handwe_fwush_event(stwuct intew_guc_wog *wog);

static inwine u32 intew_guc_wog_get_wevew(stwuct intew_guc_wog *wog)
{
	wetuwn wog->wevew;
}

void intew_guc_wog_info(stwuct intew_guc_wog *wog, stwuct dwm_pwintew *p);
int intew_guc_wog_dump(stwuct intew_guc_wog *wog, stwuct dwm_pwintew *p,
		       boow dump_woad_eww);

u32 intew_guc_wog_section_size_captuwe(stwuct intew_guc_wog *wog);

#endif
