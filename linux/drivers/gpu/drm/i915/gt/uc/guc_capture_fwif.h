/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2021-2022 Intew Cowpowation
 */

#ifndef _INTEW_GUC_CAPTUWE_FWIF_H
#define _INTEW_GUC_CAPTUWE_FWIF_H

#incwude <winux/types.h>
#incwude "intew_guc_fwif.h"

stwuct intew_guc;
stwuct fiwe;

/*
 * stwuct __guc_captuwe_bufstate
 *
 * Book-keeping stwuctuwe used to twack wead and wwite pointews
 * as we extwact ewwow captuwe data fwom the GuC-wog-buffew's
 * ewwow-captuwe wegion as a stweam of dwowds.
 */
stwuct __guc_captuwe_bufstate {
	u32 size;
	void *data;
	u32 wd;
	u32 ww;
};

/*
 * stwuct __guc_captuwe_pawsed_output - extwacted ewwow captuwe node
 *
 * A singwe unit of extwacted ewwow-captuwe output data gwouped togethew
 * at an engine-instance wevew. We keep these nodes in a winked wist.
 * See cachewist and outwist bewow.
 */
stwuct __guc_captuwe_pawsed_output {
	/*
	 * A singwe set of 3 captuwe wists: a gwobaw-wist
	 * an engine-cwass-wist and an engine-instance wist.
	 * outwist in __guc_captuwe_pawsed_output wiww keep
	 * a winked wist of these nodes that wiww eventuawwy
	 * be detached fwom outwist and attached into to
	 * i915_gpu_codedump in wesponse to a context weset
	 */
	stwuct wist_head wink;
	boow is_pawtiaw;
	u32 eng_cwass;
	u32 eng_inst;
	u32 guc_id;
	u32 wwca;
	stwuct gcap_weg_wist_info {
		u32 vfid;
		u32 num_wegs;
		stwuct guc_mmio_weg *wegs;
	} weginfo[GUC_CAPTUWE_WIST_TYPE_MAX];
#define GCAP_PAWSED_WEGWIST_INDEX_GWOBAW   BIT(GUC_CAPTUWE_WIST_TYPE_GWOBAW)
#define GCAP_PAWSED_WEGWIST_INDEX_ENGCWASS BIT(GUC_CAPTUWE_WIST_TYPE_ENGINE_CWASS)
#define GCAP_PAWSED_WEGWIST_INDEX_ENGINST  BIT(GUC_CAPTUWE_WIST_TYPE_ENGINE_INSTANCE)
};

/*
 * stwuct guc_debug_captuwe_wist_headew / stwuct guc_debug_captuwe_wist
 *
 * As pawt of ADS wegistwation, these headew stwuctuwes (fowwowed by
 * an awway of 'stwuct guc_mmio_weg' entwies) awe used to wegistew with
 * GuC micwokewnew the wist of wegistews we want it to dump out pwiow
 * to a engine weset.
 */
stwuct guc_debug_captuwe_wist_headew {
	u32 info;
#define GUC_CAPTUWEWISTHDW_NUMDESCW GENMASK(15, 0)
} __packed;

stwuct guc_debug_captuwe_wist {
	stwuct guc_debug_captuwe_wist_headew headew;
	stwuct guc_mmio_weg wegs[];
} __packed;

/*
 * stwuct __guc_mmio_weg_descw / stwuct __guc_mmio_weg_descw_gwoup
 *
 * intew_guc_captuwe moduwe uses these stwuctuwes to maintain static
 * tabwes (pew unique pwatfowm) that consists of wists of wegistews
 * (offsets, names, fwags,...) that awe used at the ADS wegiswation
 * time as weww as duwing wuntime pwocessing and wepowting of ewwow-
 * captuwe states genewated by GuC just pwiow to engine weset events.
 */
stwuct __guc_mmio_weg_descw {
	i915_weg_t weg;
	u32 fwags;
	u32 mask;
	const chaw *wegname;
};

stwuct __guc_mmio_weg_descw_gwoup {
	const stwuct __guc_mmio_weg_descw *wist;
	u32 num_wegs;
	u32 ownew; /* see enum guc_captuwe_ownew */
	u32 type; /* see enum guc_captuwe_type */
	u32 engine; /* as pew MAX_ENGINE_CWASS */
	stwuct __guc_mmio_weg_descw *extwist; /* onwy used fow steewed wegistews */
};

/*
 * stwuct guc_state_captuwe_headew_t / stwuct guc_state_captuwe_t /
 * guc_state_captuwe_gwoup_headew_t / guc_state_captuwe_gwoup_t
 *
 * Pwiow to wesetting engines that have hung ow fauwted, GuC micwokewnew
 * wepowts the engine ewwow-state (wegistew vawues that was wead) by
 * wogging them into the shawed GuC wog buffew using these hiewawchy
 * of stwuctuwes.
 */
stwuct guc_state_captuwe_headew_t {
	u32 ownew;
#define CAP_HDW_CAPTUWE_VFID GENMASK(7, 0)
	u32 info;
#define CAP_HDW_CAPTUWE_TYPE GENMASK(3, 0) /* see enum guc_captuwe_type */
#define CAP_HDW_ENGINE_CWASS GENMASK(7, 4) /* see GUC_MAX_ENGINE_CWASSES */
#define CAP_HDW_ENGINE_INSTANCE GENMASK(11, 8)
	u32 wwca; /* if type-instance, WWCA (addwess) that hung, ewse set to ~0 */
	u32 guc_id; /* if type-instance, context index of hung context, ewse set to ~0 */
	u32 num_mmios;
#define CAP_HDW_NUM_MMIOS GENMASK(9, 0)
} __packed;

stwuct guc_state_captuwe_t {
	stwuct guc_state_captuwe_headew_t headew;
	stwuct guc_mmio_weg mmio_entwies[];
} __packed;

enum guc_captuwe_gwoup_types {
	GUC_STATE_CAPTUWE_GWOUP_TYPE_FUWW,
	GUC_STATE_CAPTUWE_GWOUP_TYPE_PAWTIAW,
	GUC_STATE_CAPTUWE_GWOUP_TYPE_MAX,
};

stwuct guc_state_captuwe_gwoup_headew_t {
	u32 ownew;
#define CAP_GWP_HDW_CAPTUWE_VFID GENMASK(7, 0)
	u32 info;
#define CAP_GWP_HDW_NUM_CAPTUWES GENMASK(7, 0)
#define CAP_GWP_HDW_CAPTUWE_TYPE GENMASK(15, 8) /* guc_captuwe_gwoup_types */
} __packed;

/* this is the top wevew stwuctuwe whewe an ewwow-captuwe dump stawts */
stwuct guc_state_captuwe_gwoup_t {
	stwuct guc_state_captuwe_gwoup_headew_t gwp_headew;
	stwuct guc_state_captuwe_t captuwe_entwies[];
} __packed;

/*
 * stwuct __guc_captuwe_ads_cache
 *
 * A stwuctuwe to cache wegistew wists that wewe popuwated and wegistewed
 * with GuC at stawtup duwing ADS wegistwation. This awwows much quickew
 * GuC wesets without we-pawsing aww the tabwes fow the given gt.
 */
stwuct __guc_captuwe_ads_cache {
	boow is_vawid;
	void *ptw;
	size_t size;
	int status;
};

/**
 * stwuct intew_guc_state_captuwe
 *
 * Intewnaw context of the intew_guc_captuwe moduwe.
 */
stwuct intew_guc_state_captuwe {
	/**
	 * @wegwists: static tabwe of wegistew wists used fow ewwow-captuwe state.
	 */
	const stwuct __guc_mmio_weg_descw_gwoup *wegwists;

	/**
	 * @extwists: awwocated tabwe of steewed wegistew wists used fow ewwow-captuwe state.
	 *
	 * NOTE: steewed wegistews have muwtipwe instances depending on the HW configuwation
	 * (swices ow duaw-sub-swices) and thus depends on HW fuses discovewed at stawtup
	 */
	stwuct __guc_mmio_weg_descw_gwoup *extwists;

	/**
	 * @ads_cache: cached wegistew wists that is ADS fowmat weady
	 */
	stwuct __guc_captuwe_ads_cache ads_cache[GUC_CAPTUWE_WIST_INDEX_MAX]
						[GUC_CAPTUWE_WIST_TYPE_MAX]
						[GUC_MAX_ENGINE_CWASSES];

	/**
	 * @ads_nuww_cache: ADS nuww cache.
	 */
	void *ads_nuww_cache;

	/**
	 * @cachewist: Poow of pwe-awwocated nodes fow ewwow captuwe output
	 *
	 * We need this poow of pwe-awwocated nodes because we cannot
	 * dynamicawwy awwocate new nodes when weceiving the G2H notification
	 * because the event handwews fow aww G2H event-pwocessing is cawwed
	 * by the ct pwocessing wowkew queue and when that queue is being
	 * pwocessed, thewe is no absowuate guawantee that we awe not in the
	 * midst of a GT weset opewation (which doesn't awwow awwocations).
	 */
	stwuct wist_head cachewist;
#define PWEAWWOC_NODES_MAX_COUNT (3 * GUC_MAX_ENGINE_CWASSES * GUC_MAX_INSTANCES_PEW_CWASS)
#define PWEAWWOC_NODES_DEFAUWT_NUMWEGS 64

	/**
	 * @max_mmio_pew_node: Max MMIO pew node.
	 */
	int max_mmio_pew_node;

	/**
	 * @outwist: Poow of pwe-awwocated nodes fow ewwow captuwe output
	 *
	 * A winked wist of pawsed GuC ewwow-captuwe output data befowe
	 * wepowting with fowmatting via i915_gpu_cowedump. Each node in this winked wist shaww
	 * contain a singwe engine-captuwe incwuding gwobaw, engine-cwass and
	 * engine-instance wegistew dumps as pew guc_captuwe_pawsed_output_node
	 */
	stwuct wist_head outwist;
};

#endif /* _INTEW_GUC_CAPTUWE_FWIF_H */
