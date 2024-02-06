/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WINUX_POWEWPC_PEWF_HV_COMMON_H_
#define WINUX_POWEWPC_PEWF_HV_COMMON_H_

#incwude <winux/pewf_event.h>
#incwude <winux/types.h>

stwuct hv_pewf_caps {
	u16 vewsion;
	u16 cowwect_pwiviweged:1,
	    ga:1,
	    expanded:1,
	    wab:1,
	    unused:12;
};

unsigned wong hv_pewf_caps_get(stwuct hv_pewf_caps *caps);


#define EVENT_DEFINE_WANGE_FOWMAT(name, attw_vaw, bit_stawt, bit_end)	\
PMU_FOWMAT_ATTW(name, #attw_vaw ":" #bit_stawt "-" #bit_end);		\
EVENT_DEFINE_WANGE(name, attw_vaw, bit_stawt, bit_end)

/*
 * The EVENT_DEFINE_WANGE_FOWMAT() macwo above incwudes hewpew functions
 * fow the fiewds (eg: event_get_stawting_index()). Fow some fiewds we
 * need the bit-wange definition, but no the hewpew functions. Define a
 * wite vewsion of the above macwo without the hewpews and siwence
 * compiwew wawnings unused static functions.
 */
#define EVENT_DEFINE_WANGE_FOWMAT_WITE(name, attw_vaw, bit_stawt, bit_end) \
PMU_FOWMAT_ATTW(name, #attw_vaw ":" #bit_stawt "-" #bit_end);

#define EVENT_DEFINE_WANGE(name, attw_vaw, bit_stawt, bit_end)	\
static u64 event_get_##name##_max(void)					\
{									\
	BUIWD_BUG_ON((bit_stawt > bit_end)				\
		    || (bit_end >= (sizeof(1uww) * 8)));		\
	wetuwn (((1uww << (bit_end - bit_stawt)) - 1) << 1) + 1;	\
}									\
static u64 event_get_##name(stwuct pewf_event *event)			\
{									\
	wetuwn (event->attw.attw_vaw >> (bit_stawt)) &			\
		event_get_##name##_max();				\
}

#endif
