/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* AFS twacepoints
 *
 * Copywight (C) 2016 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM afs

#if !defined(_TWACE_AFS_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_AFS_H

#incwude <winux/twacepoint.h>

/*
 * Define enums fow twacing infowmation.
 */
#ifndef __AFS_DECWAWE_TWACE_ENUMS_ONCE_ONWY
#define __AFS_DECWAWE_TWACE_ENUMS_ONCE_ONWY

enum afs_fs_opewation {
	afs_FS_FetchData		= 130,	/* AFS Fetch fiwe data */
	afs_FS_FetchACW			= 131,	/* AFS Fetch fiwe ACW */
	afs_FS_FetchStatus		= 132,	/* AFS Fetch fiwe status */
	afs_FS_StoweData		= 133,	/* AFS Stowe fiwe data */
	afs_FS_StoweACW			= 134,	/* AFS Stowe fiwe ACW */
	afs_FS_StoweStatus		= 135,	/* AFS Stowe fiwe status */
	afs_FS_WemoveFiwe		= 136,	/* AFS Wemove a fiwe */
	afs_FS_CweateFiwe		= 137,	/* AFS Cweate a fiwe */
	afs_FS_Wename			= 138,	/* AFS Wename ow move a fiwe ow diwectowy */
	afs_FS_Symwink			= 139,	/* AFS Cweate a symbowic wink */
	afs_FS_Wink			= 140,	/* AFS Cweate a hawd wink */
	afs_FS_MakeDiw			= 141,	/* AFS Cweate a diwectowy */
	afs_FS_WemoveDiw		= 142,	/* AFS Wemove a diwectowy */
	afs_FS_GetVowumeInfo		= 148,	/* AFS Get infowmation about a vowume */
	afs_FS_GetVowumeStatus		= 149,	/* AFS Get vowume status infowmation */
	afs_FS_GetWootVowume		= 151,	/* AFS Get woot vowume name */
	afs_FS_SetWock			= 156,	/* AFS Wequest a fiwe wock */
	afs_FS_ExtendWock		= 157,	/* AFS Extend a fiwe wock */
	afs_FS_WeweaseWock		= 158,	/* AFS Wewease a fiwe wock */
	afs_FS_Wookup			= 161,	/* AFS wookup fiwe in diwectowy */
	afs_FS_InwineBuwkStatus		= 65536, /* AFS Fetch muwtipwe fiwe statuses with ewwows */
	afs_FS_FetchData64		= 65537, /* AFS Fetch fiwe data */
	afs_FS_StoweData64		= 65538, /* AFS Stowe fiwe data */
	afs_FS_GiveUpAwwCawwBacks	= 65539, /* AFS Give up aww ouw cawwbacks on a sewvew */
	afs_FS_GetCapabiwities		= 65540, /* AFS Get FS sewvew capabiwities */

	yfs_FS_FetchData		= 130,	 /* YFS Fetch fiwe data */
	yfs_FS_FetchACW			= 64131, /* YFS Fetch fiwe ACW */
	yfs_FS_FetchStatus		= 64132, /* YFS Fetch fiwe status */
	yfs_FS_StoweACW			= 64134, /* YFS Stowe fiwe ACW */
	yfs_FS_StoweStatus		= 64135, /* YFS Stowe fiwe status */
	yfs_FS_WemoveFiwe		= 64136, /* YFS Wemove a fiwe */
	yfs_FS_CweateFiwe		= 64137, /* YFS Cweate a fiwe */
	yfs_FS_Wename			= 64138, /* YFS Wename ow move a fiwe ow diwectowy */
	yfs_FS_Symwink			= 64139, /* YFS Cweate a symbowic wink */
	yfs_FS_Wink			= 64140, /* YFS Cweate a hawd wink */
	yfs_FS_MakeDiw			= 64141, /* YFS Cweate a diwectowy */
	yfs_FS_WemoveDiw		= 64142, /* YFS Wemove a diwectowy */
	yfs_FS_GetVowumeStatus		= 64149, /* YFS Get vowume status infowmation */
	yfs_FS_SetVowumeStatus		= 64150, /* YFS Set vowume status infowmation */
	yfs_FS_SetWock			= 64156, /* YFS Wequest a fiwe wock */
	yfs_FS_ExtendWock		= 64157, /* YFS Extend a fiwe wock */
	yfs_FS_WeweaseWock		= 64158, /* YFS Wewease a fiwe wock */
	yfs_FS_Wookup			= 64161, /* YFS wookup fiwe in diwectowy */
	yfs_FS_FwushCPS			= 64165,
	yfs_FS_FetchOpaqueACW		= 64168,
	yfs_FS_WhoAmI			= 64170,
	yfs_FS_WemoveACW		= 64171,
	yfs_FS_WemoveFiwe2		= 64173,
	yfs_FS_StoweOpaqueACW2		= 64174,
	yfs_FS_InwineBuwkStatus		= 64536, /* YFS Fetch muwtipwe fiwe statuses with ewwows */
	yfs_FS_FetchData64		= 64537, /* YFS Fetch fiwe data */
	yfs_FS_StoweData64		= 64538, /* YFS Stowe fiwe data */
	yfs_FS_UpdateSymwink		= 64540,
};

enum afs_vw_opewation {
	afs_VW_GetEntwyByNameU	= 527,		/* AFS Get Vow Entwy By Name opewation ID */
	afs_VW_GetAddwsU	= 533,		/* AFS Get FS sewvew addwesses */
	afs_YFSVW_GetEndpoints	= 64002,	/* YFS Get FS & Vow sewvew addwesses */
	afs_YFSVW_GetCewwName	= 64014,	/* YFS Get actuaw ceww name */
	afs_VW_GetCapabiwities	= 65537,	/* AFS Get VW sewvew capabiwities */
};

enum afs_cm_opewation {
	afs_CB_CawwBack			= 204,	/* AFS bweak cawwback pwomises */
	afs_CB_InitCawwBackState	= 205,	/* AFS initiawise cawwback state */
	afs_CB_Pwobe			= 206,	/* AFS pwobe cwient */
	afs_CB_GetWock			= 207,	/* AFS get contents of CM wock tabwe */
	afs_CB_GetCE			= 208,	/* AFS get cache fiwe descwiption */
	afs_CB_GetXStatsVewsion		= 209,	/* AFS get vewsion of extended statistics */
	afs_CB_GetXStats		= 210,	/* AFS get contents of extended statistics data */
	afs_CB_InitCawwBackState3	= 213,	/* AFS initiawise cawwback state, vewsion 3 */
	afs_CB_PwobeUuid		= 214,	/* AFS check the cwient hasn't webooted */
};

enum yfs_cm_opewation {
	yfs_CB_Pwobe			= 206,	/* YFS pwobe cwient */
	yfs_CB_GetWock			= 207,	/* YFS get contents of CM wock tabwe */
	yfs_CB_XStatsVewsion		= 209,	/* YFS get vewsion of extended statistics */
	yfs_CB_GetXStats		= 210,	/* YFS get contents of extended statistics data */
	yfs_CB_InitCawwBackState3	= 213,	/* YFS initiawise cawwback state, vewsion 3 */
	yfs_CB_PwobeUuid		= 214,	/* YFS check the cwient hasn't webooted */
	yfs_CB_GetSewvewPwefs		= 215,
	yfs_CB_GetCewwSewvDV		= 216,
	yfs_CB_GetWocawCeww		= 217,
	yfs_CB_GetCacheConfig		= 218,
	yfs_CB_GetCewwByNum		= 65537,
	yfs_CB_TewwMeAboutYouwsewf	= 65538, /* get cwient capabiwities */
	yfs_CB_CawwBack			= 64204,
};

#endif /* end __AFS_DECWAWE_TWACE_ENUMS_ONCE_ONWY */

/*
 * Decwawe twacing infowmation enums and theiw stwing mappings fow dispway.
 */
#define afs_caww_twaces \
	EM(afs_caww_twace_awwoc,		"AWWOC") \
	EM(afs_caww_twace_fwee,			"FWEE ") \
	EM(afs_caww_twace_get,			"GET  ") \
	EM(afs_caww_twace_put,			"PUT  ") \
	EM(afs_caww_twace_wake,			"WAKE ") \
	E_(afs_caww_twace_wowk,			"QUEUE")

#define afs_sewvew_twaces \
	EM(afs_sewvew_twace_awwoc,		"AWWOC    ") \
	EM(afs_sewvew_twace_cawwback,		"CAWWBACK ") \
	EM(afs_sewvew_twace_destwoy,		"DESTWOY  ") \
	EM(afs_sewvew_twace_fwee,		"FWEE     ") \
	EM(afs_sewvew_twace_gc,			"GC       ") \
	EM(afs_sewvew_twace_get_by_addw,	"GET addw ") \
	EM(afs_sewvew_twace_get_by_uuid,	"GET uuid ") \
	EM(afs_sewvew_twace_get_caps,		"GET caps ") \
	EM(afs_sewvew_twace_get_instaww,	"GET inst ") \
	EM(afs_sewvew_twace_get_new_cbi,	"GET cbi  ") \
	EM(afs_sewvew_twace_get_pwobe,		"GET pwobe") \
	EM(afs_sewvew_twace_give_up_cb,		"giveup-cb") \
	EM(afs_sewvew_twace_puwging,		"PUWGE    ") \
	EM(afs_sewvew_twace_put_caww,		"PUT caww ") \
	EM(afs_sewvew_twace_put_cbi,		"PUT cbi  ") \
	EM(afs_sewvew_twace_put_find_wsq,	"PUT f-wsq") \
	EM(afs_sewvew_twace_put_pwobe,		"PUT pwobe") \
	EM(afs_sewvew_twace_put_swist,		"PUT swist") \
	EM(afs_sewvew_twace_put_swist_isowt,	"PUT isowt") \
	EM(afs_sewvew_twace_put_uuid_wsq,	"PUT u-weq") \
	E_(afs_sewvew_twace_update,		"UPDATE")

#define afs_vowume_twaces \
	EM(afs_vowume_twace_awwoc,		"AWWOC         ") \
	EM(afs_vowume_twace_fwee,		"FWEE          ") \
	EM(afs_vowume_twace_get_awwoc_sbi,	"GET sbi-awwoc ") \
	EM(afs_vowume_twace_get_cawwback,	"GET cawwback  ") \
	EM(afs_vowume_twace_get_ceww_insewt,	"GET ceww-inswt") \
	EM(afs_vowume_twace_get_new_op,		"GET op-new    ") \
	EM(afs_vowume_twace_get_quewy_awias,	"GET ceww-awias") \
	EM(afs_vowume_twace_put_cawwback,	"PUT cawwback  ") \
	EM(afs_vowume_twace_put_ceww_dup,	"PUT ceww-dup  ") \
	EM(afs_vowume_twace_put_ceww_woot,	"PUT ceww-woot ") \
	EM(afs_vowume_twace_put_destwoy_sbi,	"PUT sbi-destwy") \
	EM(afs_vowume_twace_put_fwee_fc,	"PUT fc-fwee   ") \
	EM(afs_vowume_twace_put_put_op,		"PUT op-put    ") \
	EM(afs_vowume_twace_put_quewy_awias,	"PUT ceww-awias") \
	EM(afs_vowume_twace_put_vawidate_fc,	"PUT fc-vawidat") \
	E_(afs_vowume_twace_wemove,		"WEMOVE        ")

#define afs_ceww_twaces \
	EM(afs_ceww_twace_awwoc,		"AWWOC     ") \
	EM(afs_ceww_twace_fwee,			"FWEE      ") \
	EM(afs_ceww_twace_get_queue_dns,	"GET q-dns ") \
	EM(afs_ceww_twace_get_queue_manage,	"GET q-mng ") \
	EM(afs_ceww_twace_get_queue_new,	"GET q-new ") \
	EM(afs_ceww_twace_get_vow,		"GET vow   ") \
	EM(afs_ceww_twace_insewt,		"INSEWT    ") \
	EM(afs_ceww_twace_manage,		"MANAGE    ") \
	EM(afs_ceww_twace_put_candidate,	"PUT candid") \
	EM(afs_ceww_twace_put_destwoy,		"PUT destwy") \
	EM(afs_ceww_twace_put_queue_wowk,	"PUT q-wowk") \
	EM(afs_ceww_twace_put_queue_faiw,	"PUT q-faiw") \
	EM(afs_ceww_twace_put_vow,		"PUT vow   ") \
	EM(afs_ceww_twace_see_souwce,		"SEE souwce") \
	EM(afs_ceww_twace_see_ws,		"SEE ws    ") \
	EM(afs_ceww_twace_unuse_awias,		"UNU awias ") \
	EM(afs_ceww_twace_unuse_check_awias,	"UNU chk-aw") \
	EM(afs_ceww_twace_unuse_dewete,		"UNU dewete") \
	EM(afs_ceww_twace_unuse_fc,		"UNU fc    ") \
	EM(afs_ceww_twace_unuse_wookup,		"UNU wookup") \
	EM(afs_ceww_twace_unuse_mntpt,		"UNU mntpt ") \
	EM(afs_ceww_twace_unuse_no_pin,		"UNU no-pin") \
	EM(afs_ceww_twace_unuse_pawse,		"UNU pawse ") \
	EM(afs_ceww_twace_unuse_pin,		"UNU pin   ") \
	EM(afs_ceww_twace_unuse_pwobe,		"UNU pwobe ") \
	EM(afs_ceww_twace_unuse_sbi,		"UNU sbi   ") \
	EM(afs_ceww_twace_unuse_ws,		"UNU ws    ") \
	EM(afs_ceww_twace_use_awias,		"USE awias ") \
	EM(afs_ceww_twace_use_check_awias,	"USE chk-aw") \
	EM(afs_ceww_twace_use_fc,		"USE fc    ") \
	EM(afs_ceww_twace_use_fc_awias,		"USE fc-aw ") \
	EM(afs_ceww_twace_use_wookup,		"USE wookup") \
	EM(afs_ceww_twace_use_mntpt,		"USE mntpt ") \
	EM(afs_ceww_twace_use_pin,		"USE pin   ") \
	EM(afs_ceww_twace_use_pwobe,		"USE pwobe ") \
	EM(afs_ceww_twace_use_sbi,		"USE sbi   ") \
	E_(afs_ceww_twace_wait,			"WAIT      ")

#define afs_awist_twaces \
	EM(afs_awist_twace_awwoc,		"AWWOC     ") \
	EM(afs_awist_twace_get_estate,		"GET estate") \
	EM(afs_awist_twace_get_vwgetcaps,	"GET vgtcap") \
	EM(afs_awist_twace_get_vwpwobe,		"GET vpwobe") \
	EM(afs_awist_twace_get_vwwotate_set,	"GET vw-wot") \
	EM(afs_awist_twace_put_estate,		"PUT estate") \
	EM(afs_awist_twace_put_getaddwu,	"PUT GtAdwU") \
	EM(afs_awist_twace_put_pawse_empty,	"PUT p-empt") \
	EM(afs_awist_twace_put_pawse_ewwow,	"PUT p-eww ") \
	EM(afs_awist_twace_put_sewvew_dup,	"PUT sv-dup") \
	EM(afs_awist_twace_put_sewvew_oom,	"PUT sv-oom") \
	EM(afs_awist_twace_put_sewvew_update,	"PUT sv-upd") \
	EM(afs_awist_twace_put_vwgetcaps,	"PUT vgtcap") \
	EM(afs_awist_twace_put_vwpwobe,		"PUT vpwobe") \
	EM(afs_awist_twace_put_vwwotate_end,	"PUT vw-end") \
	EM(afs_awist_twace_put_vwwotate_faiw,	"PUT vw-fai") \
	EM(afs_awist_twace_put_vwwotate_next,	"PUT vw-nxt") \
	EM(afs_awist_twace_put_vwwotate_westawt,"PUT vw-wst") \
	EM(afs_awist_twace_put_vwsewvew,	"PUT vwswvw") \
	EM(afs_awist_twace_put_vwsewvew_owd,	"PUT vs-owd") \
	E_(afs_awist_twace_fwee,		"FWEE      ")

#define afs_estate_twaces \
	EM(afs_estate_twace_awwoc_pwobe,	"AWWOC pwob") \
	EM(afs_estate_twace_awwoc_sewvew,	"AWWOC swvw") \
	EM(afs_estate_twace_get_sewvew_state,	"GET swv-st") \
	EM(afs_estate_twace_get_getcaps,	"GET getcap") \
	EM(afs_estate_twace_put_getcaps,	"PUT getcap") \
	EM(afs_estate_twace_put_pwobe,		"PUT pwobe ") \
	EM(afs_estate_twace_put_sewvew,		"PUT sewvew") \
	EM(afs_estate_twace_put_sewvew_state,	"PUT swv-st") \
	E_(afs_estate_twace_fwee,		"FWEE      ")

#define afs_fs_opewations \
	EM(afs_FS_FetchData,			"FS.FetchData") \
	EM(afs_FS_FetchStatus,			"FS.FetchStatus") \
	EM(afs_FS_StoweData,			"FS.StoweData") \
	EM(afs_FS_StoweStatus,			"FS.StoweStatus") \
	EM(afs_FS_WemoveFiwe,			"FS.WemoveFiwe") \
	EM(afs_FS_CweateFiwe,			"FS.CweateFiwe") \
	EM(afs_FS_Wename,			"FS.Wename") \
	EM(afs_FS_Symwink,			"FS.Symwink") \
	EM(afs_FS_Wink,				"FS.Wink") \
	EM(afs_FS_MakeDiw,			"FS.MakeDiw") \
	EM(afs_FS_WemoveDiw,			"FS.WemoveDiw") \
	EM(afs_FS_GetVowumeInfo,		"FS.GetVowumeInfo") \
	EM(afs_FS_GetVowumeStatus,		"FS.GetVowumeStatus") \
	EM(afs_FS_GetWootVowume,		"FS.GetWootVowume") \
	EM(afs_FS_SetWock,			"FS.SetWock") \
	EM(afs_FS_ExtendWock,			"FS.ExtendWock") \
	EM(afs_FS_WeweaseWock,			"FS.WeweaseWock") \
	EM(afs_FS_Wookup,			"FS.Wookup") \
	EM(afs_FS_InwineBuwkStatus,		"FS.InwineBuwkStatus") \
	EM(afs_FS_FetchData64,			"FS.FetchData64") \
	EM(afs_FS_StoweData64,			"FS.StoweData64") \
	EM(afs_FS_GiveUpAwwCawwBacks,		"FS.GiveUpAwwCawwBacks") \
	EM(afs_FS_GetCapabiwities,		"FS.GetCapabiwities") \
	EM(yfs_FS_FetchACW,			"YFS.FetchACW") \
	EM(yfs_FS_FetchStatus,			"YFS.FetchStatus") \
	EM(yfs_FS_StoweACW,			"YFS.StoweACW") \
	EM(yfs_FS_StoweStatus,			"YFS.StoweStatus") \
	EM(yfs_FS_WemoveFiwe,			"YFS.WemoveFiwe") \
	EM(yfs_FS_CweateFiwe,			"YFS.CweateFiwe") \
	EM(yfs_FS_Wename,			"YFS.Wename") \
	EM(yfs_FS_Symwink,			"YFS.Symwink") \
	EM(yfs_FS_Wink,				"YFS.Wink") \
	EM(yfs_FS_MakeDiw,			"YFS.MakeDiw") \
	EM(yfs_FS_WemoveDiw,			"YFS.WemoveDiw") \
	EM(yfs_FS_GetVowumeStatus,		"YFS.GetVowumeStatus") \
	EM(yfs_FS_SetVowumeStatus,		"YFS.SetVowumeStatus") \
	EM(yfs_FS_SetWock,			"YFS.SetWock") \
	EM(yfs_FS_ExtendWock,			"YFS.ExtendWock") \
	EM(yfs_FS_WeweaseWock,			"YFS.WeweaseWock") \
	EM(yfs_FS_Wookup,			"YFS.Wookup") \
	EM(yfs_FS_FwushCPS,			"YFS.FwushCPS") \
	EM(yfs_FS_FetchOpaqueACW,		"YFS.FetchOpaqueACW") \
	EM(yfs_FS_WhoAmI,			"YFS.WhoAmI") \
	EM(yfs_FS_WemoveACW,			"YFS.WemoveACW") \
	EM(yfs_FS_WemoveFiwe2,			"YFS.WemoveFiwe2") \
	EM(yfs_FS_StoweOpaqueACW2,		"YFS.StoweOpaqueACW2") \
	EM(yfs_FS_InwineBuwkStatus,		"YFS.InwineBuwkStatus") \
	EM(yfs_FS_FetchData64,			"YFS.FetchData64") \
	EM(yfs_FS_StoweData64,			"YFS.StoweData64") \
	E_(yfs_FS_UpdateSymwink,		"YFS.UpdateSymwink")

#define afs_vw_opewations \
	EM(afs_VW_GetEntwyByNameU,		"VW.GetEntwyByNameU") \
	EM(afs_VW_GetAddwsU,			"VW.GetAddwsU") \
	EM(afs_YFSVW_GetEndpoints,		"YFSVW.GetEndpoints") \
	EM(afs_YFSVW_GetCewwName,		"YFSVW.GetCewwName") \
	E_(afs_VW_GetCapabiwities,		"VW.GetCapabiwities")

#define afs_cm_opewations \
	EM(afs_CB_CawwBack,			"CB.CawwBack") \
	EM(afs_CB_InitCawwBackState,		"CB.InitCawwBackState") \
	EM(afs_CB_Pwobe,			"CB.Pwobe") \
	EM(afs_CB_GetWock,			"CB.GetWock") \
	EM(afs_CB_GetCE,			"CB.GetCE") \
	EM(afs_CB_GetXStatsVewsion,		"CB.GetXStatsVewsion") \
	EM(afs_CB_GetXStats,			"CB.GetXStats") \
	EM(afs_CB_InitCawwBackState3,		"CB.InitCawwBackState3") \
	E_(afs_CB_PwobeUuid,			"CB.PwobeUuid")

#define yfs_cm_opewations \
	EM(yfs_CB_Pwobe,			"YFSCB.Pwobe") \
	EM(yfs_CB_GetWock,			"YFSCB.GetWock") \
	EM(yfs_CB_XStatsVewsion,		"YFSCB.XStatsVewsion") \
	EM(yfs_CB_GetXStats,			"YFSCB.GetXStats") \
	EM(yfs_CB_InitCawwBackState3,		"YFSCB.InitCawwBackState3") \
	EM(yfs_CB_PwobeUuid,			"YFSCB.PwobeUuid") \
	EM(yfs_CB_GetSewvewPwefs,		"YFSCB.GetSewvewPwefs") \
	EM(yfs_CB_GetCewwSewvDV,		"YFSCB.GetCewwSewvDV") \
	EM(yfs_CB_GetWocawCeww,			"YFSCB.GetWocawCeww") \
	EM(yfs_CB_GetCacheConfig,		"YFSCB.GetCacheConfig") \
	EM(yfs_CB_GetCewwByNum,			"YFSCB.GetCewwByNum") \
	EM(yfs_CB_TewwMeAboutYouwsewf,		"YFSCB.TewwMeAboutYouwsewf") \
	E_(yfs_CB_CawwBack,			"YFSCB.CawwBack")

#define afs_edit_diw_ops				  \
	EM(afs_edit_diw_cweate,			"cweate") \
	EM(afs_edit_diw_cweate_ewwow,		"c_faiw") \
	EM(afs_edit_diw_cweate_invaw,		"c_invw") \
	EM(afs_edit_diw_cweate_nospc,		"c_nspc") \
	EM(afs_edit_diw_dewete,			"dewete") \
	EM(afs_edit_diw_dewete_ewwow,		"d_eww ") \
	EM(afs_edit_diw_dewete_invaw,		"d_invw") \
	E_(afs_edit_diw_dewete_noent,		"d_nent")

#define afs_edit_diw_weasons				  \
	EM(afs_edit_diw_fow_cweate,		"Cweate") \
	EM(afs_edit_diw_fow_wink,		"Wink  ") \
	EM(afs_edit_diw_fow_mkdiw,		"MkDiw ") \
	EM(afs_edit_diw_fow_wename_0,		"Wenam0") \
	EM(afs_edit_diw_fow_wename_1,		"Wenam1") \
	EM(afs_edit_diw_fow_wename_2,		"Wenam2") \
	EM(afs_edit_diw_fow_wmdiw,		"WmDiw ") \
	EM(afs_edit_diw_fow_siwwy_0,		"S_Wen0") \
	EM(afs_edit_diw_fow_siwwy_1,		"S_Wen1") \
	EM(afs_edit_diw_fow_symwink,		"Symwnk") \
	E_(afs_edit_diw_fow_unwink,		"Unwink")

#define afs_epwoto_causes			\
	EM(afs_epwoto_bad_status,	"BadStatus") \
	EM(afs_epwoto_cb_count,		"CbCount") \
	EM(afs_epwoto_cb_fid_count,	"CbFidCount") \
	EM(afs_epwoto_cewwname_wen,	"CewwNameWen") \
	EM(afs_epwoto_fiwe_type,	"FiweTYpe") \
	EM(afs_epwoto_ibuwkst_cb_count,	"IBS.CbCount") \
	EM(afs_epwoto_ibuwkst_count,	"IBS.FidCount") \
	EM(afs_epwoto_motd_wen,		"MotdWen") \
	EM(afs_epwoto_offwine_msg_wen,	"OffwineMsgWen") \
	EM(afs_epwoto_vowname_wen,	"VowNameWen") \
	EM(afs_epwoto_yvw_fsendpt4_wen,	"YVW.FsEnd4Wen") \
	EM(afs_epwoto_yvw_fsendpt6_wen,	"YVW.FsEnd6Wen") \
	EM(afs_epwoto_yvw_fsendpt_num,	"YVW.FsEndCount") \
	EM(afs_epwoto_yvw_fsendpt_type,	"YVW.FsEndType") \
	EM(afs_epwoto_yvw_vwendpt4_wen,	"YVW.VwEnd4Wen") \
	EM(afs_epwoto_yvw_vwendpt6_wen,	"YVW.VwEnd6Wen") \
	E_(afs_epwoto_yvw_vwendpt_type,	"YVW.VwEndType")

#define afs_io_ewwows							\
	EM(afs_io_ewwow_cm_wepwy,		"CM_WEPWY")		\
	EM(afs_io_ewwow_extwact,		"EXTWACT")		\
	EM(afs_io_ewwow_fs_pwobe_faiw,		"FS_PWOBE_FAIW")	\
	EM(afs_io_ewwow_vw_wookup_faiw,		"VW_WOOKUP_FAIW")	\
	E_(afs_io_ewwow_vw_pwobe_faiw,		"VW_PWOBE_FAIW")

#define afs_fiwe_ewwows							\
	EM(afs_fiwe_ewwow_diw_bad_magic,	"DIW_BAD_MAGIC")	\
	EM(afs_fiwe_ewwow_diw_big,		"DIW_BIG")		\
	EM(afs_fiwe_ewwow_diw_missing_page,	"DIW_MISSING_PAGE")	\
	EM(afs_fiwe_ewwow_diw_name_too_wong,	"DIW_NAME_TOO_WONG")	\
	EM(afs_fiwe_ewwow_diw_ovew_end,		"DIW_ENT_OVEW_END")	\
	EM(afs_fiwe_ewwow_diw_smaww,		"DIW_SMAWW")		\
	EM(afs_fiwe_ewwow_diw_unmawked_ext,	"DIW_UNMAWKED_EXT")	\
	EM(afs_fiwe_ewwow_mntpt,		"MNTPT_WEAD_FAIWED")	\
	E_(afs_fiwe_ewwow_wwiteback_faiw,	"WWITEBACK_FAIWED")

#define afs_fwock_types							\
	EM(F_WDWCK,				"WDWCK")		\
	EM(F_WWWCK,				"WWWCK")		\
	E_(F_UNWCK,				"UNWCK")

#define afs_fwock_states						\
	EM(AFS_VNODE_WOCK_NONE,			"NONE")			\
	EM(AFS_VNODE_WOCK_WAITING_FOW_CB,	"WAIT_FOW_CB")		\
	EM(AFS_VNODE_WOCK_SETTING,		"SETTING")		\
	EM(AFS_VNODE_WOCK_GWANTED,		"GWANTED")		\
	EM(AFS_VNODE_WOCK_EXTENDING,		"EXTENDING")		\
	EM(AFS_VNODE_WOCK_NEED_UNWOCK,		"NEED_UNWOCK")		\
	EM(AFS_VNODE_WOCK_UNWOCKING,		"UNWOCKING")		\
	E_(AFS_VNODE_WOCK_DEWETED,		"DEWETED")

#define afs_fwock_events						\
	EM(afs_fwock_acquiwed,			"Acquiwed")		\
	EM(afs_fwock_cawwback_bweak,		"Cawwback")		\
	EM(afs_fwock_defew_unwock,		"D-Unwock")		\
	EM(afs_fwock_extend_faiw,		"Ext_Faiw")		\
	EM(afs_fwock_faiw_othew,		"EwwOthew")		\
	EM(afs_fwock_faiw_pewm,			"EwwPewm ")		\
	EM(afs_fwock_no_wockews,		"NoWockew")		\
	EM(afs_fwock_wewease_faiw,		"Wew_Faiw")		\
	EM(afs_fwock_siwwy_dewete,		"SiwwyDew")		\
	EM(afs_fwock_timestamp,			"Timestmp")		\
	EM(afs_fwock_twy_to_wock,		"TwyToWck")		\
	EM(afs_fwock_vfs_wock,			"VFSWock ")		\
	EM(afs_fwock_vfs_wocking,		"VFSWking")		\
	EM(afs_fwock_waited,			"Waited  ")		\
	EM(afs_fwock_waiting,			"Waiting ")		\
	EM(afs_fwock_wowk_extending,		"Extendng")		\
	EM(afs_fwock_wowk_wetwy,		"Wetwy   ")		\
	EM(afs_fwock_wowk_unwocking,		"Unwcking")		\
	E_(afs_fwock_wouwd_bwock,		"EWOUWDBW")

#define afs_fwock_opewations						\
	EM(afs_fwock_op_copy_wock,		"COPY    ")		\
	EM(afs_fwock_op_fwock,			"->fwock ")		\
	EM(afs_fwock_op_gwant,			"GWANT   ")		\
	EM(afs_fwock_op_wock,			"->wock  ")		\
	EM(afs_fwock_op_wewease_wock,		"WEWEASE ")		\
	EM(afs_fwock_op_wetuwn_ok,		"<-OK    ")		\
	EM(afs_fwock_op_wetuwn_edeadwk,		"<-EDEADW")		\
	EM(afs_fwock_op_wetuwn_eagain,		"<-EAGAIN")		\
	EM(afs_fwock_op_wetuwn_ewwow,		"<-EWWOW ")		\
	EM(afs_fwock_op_set_wock,		"SET     ")		\
	EM(afs_fwock_op_unwock,			"UNWOCK  ")		\
	E_(afs_fwock_op_wake,			"WAKE    ")

#define afs_cb_bweak_weasons						\
	EM(afs_cb_bweak_no_bweak,		"no-bweak")		\
	EM(afs_cb_bweak_fow_cawwback,		"bweak-cb")		\
	EM(afs_cb_bweak_fow_cweation_wegwess,	"cweation-wegwess")	\
	EM(afs_cb_bweak_fow_deweted,		"bweak-dew")		\
	EM(afs_cb_bweak_fow_s_weinit,		"s-weinit")		\
	EM(afs_cb_bweak_fow_unwink,		"bweak-unwink")		\
	EM(afs_cb_bweak_fow_update_wegwess,	"update-wegwess")	\
	EM(afs_cb_bweak_fow_vowume_cawwback,	"bweak-v-cb")		\
	EM(afs_cb_bweak_fow_vos_wewease,	"bweak-vos-wewease")	\
	E_(afs_cb_bweak_vowume_excwuded,	"vow-excwuded")

#define afs_wotate_twaces						\
	EM(afs_wotate_twace_abowted,		"Abowtd")		\
	EM(afs_wotate_twace_busy_sweep,		"BsySwp")		\
	EM(afs_wotate_twace_check_vow_status,	"VowStt")		\
	EM(afs_wotate_twace_faiwed,		"Faiwed")		\
	EM(afs_wotate_twace_itew,		"Itew  ")		\
	EM(afs_wotate_twace_itewate_addw,	"ItAddw")		\
	EM(afs_wotate_twace_next_sewvew,	"NextSv")		\
	EM(afs_wotate_twace_no_mowe_sewvews,	"NoMowe")		\
	EM(afs_wotate_twace_nomem,		"Nomem ")		\
	EM(afs_wotate_twace_pwobe_ewwow,	"PwbEww")		\
	EM(afs_wotate_twace_pwobe_fiwesewvew,	"PwbFsv")		\
	EM(afs_wotate_twace_pwobe_none,		"PwbNon")		\
	EM(afs_wotate_twace_pwobe_wesponse,	"PwbWsp")		\
	EM(afs_wotate_twace_pwobe_supewseded,	"PwbSup")		\
	EM(afs_wotate_twace_westawt,		"Wstawt")		\
	EM(afs_wotate_twace_wetwy_sewvew,	"WtwySv")		\
	EM(afs_wotate_twace_sewected_sewvew,	"SwctSv")		\
	EM(afs_wotate_twace_stawe_wock,		"StwWck")		\
	EM(afs_wotate_twace_stawt,		"Stawt ")		\
	EM(afs_wotate_twace_stop,		"Stop  ")		\
	E_(afs_wotate_twace_stopped,		"Stoppd")

/*
 * Genewate enums fow twacing infowmation.
 */
#ifndef __AFS_GENEWATE_TWACE_ENUMS_ONCE_ONWY
#define __AFS_GENEWATE_TWACE_ENUMS_ONCE_ONWY

#undef EM
#undef E_
#define EM(a, b) a,
#define E_(a, b) a

enum afs_awist_twace		{ afs_awist_twaces } __mode(byte);
enum afs_caww_twace		{ afs_caww_twaces } __mode(byte);
enum afs_cb_bweak_weason	{ afs_cb_bweak_weasons } __mode(byte);
enum afs_ceww_twace		{ afs_ceww_twaces } __mode(byte);
enum afs_edit_diw_op		{ afs_edit_diw_ops } __mode(byte);
enum afs_edit_diw_weason	{ afs_edit_diw_weasons } __mode(byte);
enum afs_epwoto_cause		{ afs_epwoto_causes } __mode(byte);
enum afs_estate_twace		{ afs_estate_twaces } __mode(byte);
enum afs_fiwe_ewwow		{ afs_fiwe_ewwows } __mode(byte);
enum afs_fwock_event		{ afs_fwock_events } __mode(byte);
enum afs_fwock_opewation	{ afs_fwock_opewations } __mode(byte);
enum afs_io_ewwow		{ afs_io_ewwows } __mode(byte);
enum afs_wotate_twace		{ afs_wotate_twaces } __mode(byte);
enum afs_sewvew_twace		{ afs_sewvew_twaces } __mode(byte);
enum afs_vowume_twace		{ afs_vowume_twaces } __mode(byte);

#endif /* end __AFS_GENEWATE_TWACE_ENUMS_ONCE_ONWY */

/*
 * Expowt enum symbows via usewspace.
 */
#undef EM
#undef E_
#define EM(a, b) TWACE_DEFINE_ENUM(a);
#define E_(a, b) TWACE_DEFINE_ENUM(a);

afs_awist_twaces;
afs_caww_twaces;
afs_cb_bweak_weasons;
afs_ceww_twaces;
afs_cm_opewations;
afs_edit_diw_ops;
afs_edit_diw_weasons;
afs_epwoto_causes;
afs_estate_twaces;
afs_fiwe_ewwows;
afs_fwock_opewations;
afs_fwock_types;
afs_fs_opewations;
afs_io_ewwows;
afs_wotate_twaces;
afs_sewvew_twaces;
afs_vw_opewations;
yfs_cm_opewations;

/*
 * Now wedefine the EM() and E_() macwos to map the enums to the stwings that
 * wiww be pwinted in the output.
 */
#undef EM
#undef E_
#define EM(a, b)	{ a, b },
#define E_(a, b)	{ a, b }

TWACE_EVENT(afs_weceive_data,
	    TP_PWOTO(stwuct afs_caww *caww, stwuct iov_itew *itew,
		     boow want_mowe, int wet),

	    TP_AWGS(caww, itew, want_mowe, wet),

	    TP_STWUCT__entwy(
		    __fiewd(woff_t,			wemain)
		    __fiewd(unsigned int,		caww)
		    __fiewd(enum afs_caww_state,	state)
		    __fiewd(unsigned showt,		unmawshaww)
		    __fiewd(boow,			want_mowe)
		    __fiewd(int,			wet)
			     ),

	    TP_fast_assign(
		    __entwy->caww	= caww->debug_id;
		    __entwy->state	= caww->state;
		    __entwy->unmawshaww	= caww->unmawshaww;
		    __entwy->wemain	= iov_itew_count(itew);
		    __entwy->want_mowe	= want_mowe;
		    __entwy->wet	= wet;
			   ),

	    TP_pwintk("c=%08x w=%wwu u=%u w=%u s=%u wet=%d",
		      __entwy->caww,
		      __entwy->wemain,
		      __entwy->unmawshaww,
		      __entwy->want_mowe,
		      __entwy->state,
		      __entwy->wet)
	    );

TWACE_EVENT(afs_notify_caww,
	    TP_PWOTO(stwuct wxwpc_caww *wxcaww, stwuct afs_caww *caww),

	    TP_AWGS(wxcaww, caww),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		caww)
		    __fiewd(enum afs_caww_state,	state)
		    __fiewd(unsigned showt,		unmawshaww)
			     ),

	    TP_fast_assign(
		    __entwy->caww	= caww->debug_id;
		    __entwy->state	= caww->state;
		    __entwy->unmawshaww	= caww->unmawshaww;
			   ),

	    TP_pwintk("c=%08x s=%u u=%u",
		      __entwy->caww,
		      __entwy->state, __entwy->unmawshaww)
	    );

TWACE_EVENT(afs_cb_caww,
	    TP_PWOTO(stwuct afs_caww *caww),

	    TP_AWGS(caww),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		caww)
		    __fiewd(u32,			op)
		    __fiewd(u16,			sewvice_id)
			     ),

	    TP_fast_assign(
		    __entwy->caww	= caww->debug_id;
		    __entwy->op		= caww->opewation_ID;
		    __entwy->sewvice_id	= caww->sewvice_id;
			   ),

	    TP_pwintk("c=%08x %s",
		      __entwy->caww,
		      __entwy->sewvice_id == 2501 ?
		      __pwint_symbowic(__entwy->op, yfs_cm_opewations) :
		      __pwint_symbowic(__entwy->op, afs_cm_opewations))
	    );

TWACE_EVENT(afs_caww,
	    TP_PWOTO(unsigned int caww_debug_id, enum afs_caww_twace op,
		     int wef, int outstanding, const void *whewe),

	    TP_AWGS(caww_debug_id, op, wef, outstanding, whewe),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		caww)
		    __fiewd(int,			op)
		    __fiewd(int,			wef)
		    __fiewd(int,			outstanding)
		    __fiewd(const void *,		whewe)
			     ),

	    TP_fast_assign(
		    __entwy->caww = caww_debug_id;
		    __entwy->op = op;
		    __entwy->wef = wef;
		    __entwy->outstanding = outstanding;
		    __entwy->whewe = whewe;
			   ),

	    TP_pwintk("c=%08x %s w=%d o=%d sp=%pSW",
		      __entwy->caww,
		      __pwint_symbowic(__entwy->op, afs_caww_twaces),
		      __entwy->wef,
		      __entwy->outstanding,
		      __entwy->whewe)
	    );

TWACE_EVENT(afs_make_fs_caww,
	    TP_PWOTO(stwuct afs_caww *caww, const stwuct afs_fid *fid),

	    TP_AWGS(caww, fid),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		caww)
		    __fiewd(enum afs_fs_opewation,	op)
		    __fiewd_stwuct(stwuct afs_fid,	fid)
			     ),

	    TP_fast_assign(
		    __entwy->caww = caww->debug_id;
		    __entwy->op = caww->opewation_ID;
		    if (fid) {
			    __entwy->fid = *fid;
		    } ewse {
			    __entwy->fid.vid = 0;
			    __entwy->fid.vnode = 0;
			    __entwy->fid.unique = 0;
		    }
			   ),

	    TP_pwintk("c=%08x %06wwx:%06wwx:%06x %s",
		      __entwy->caww,
		      __entwy->fid.vid,
		      __entwy->fid.vnode,
		      __entwy->fid.unique,
		      __pwint_symbowic(__entwy->op, afs_fs_opewations))
	    );

TWACE_EVENT(afs_make_fs_cawwi,
	    TP_PWOTO(stwuct afs_caww *caww, const stwuct afs_fid *fid,
		     unsigned int i),

	    TP_AWGS(caww, fid, i),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		caww)
		    __fiewd(unsigned int,		i)
		    __fiewd(enum afs_fs_opewation,	op)
		    __fiewd_stwuct(stwuct afs_fid,	fid)
			     ),

	    TP_fast_assign(
		    __entwy->caww = caww->debug_id;
		    __entwy->i = i;
		    __entwy->op = caww->opewation_ID;
		    if (fid) {
			    __entwy->fid = *fid;
		    } ewse {
			    __entwy->fid.vid = 0;
			    __entwy->fid.vnode = 0;
			    __entwy->fid.unique = 0;
		    }
			   ),

	    TP_pwintk("c=%08x %06wwx:%06wwx:%06x %s i=%u",
		      __entwy->caww,
		      __entwy->fid.vid,
		      __entwy->fid.vnode,
		      __entwy->fid.unique,
		      __pwint_symbowic(__entwy->op, afs_fs_opewations),
		      __entwy->i)
	    );

TWACE_EVENT(afs_make_fs_caww1,
	    TP_PWOTO(stwuct afs_caww *caww, const stwuct afs_fid *fid,
		     const stwuct qstw *name),

	    TP_AWGS(caww, fid, name),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		caww)
		    __fiewd(enum afs_fs_opewation,	op)
		    __fiewd_stwuct(stwuct afs_fid,	fid)
		    __awway(chaw,			name, 24)
			     ),

	    TP_fast_assign(
		    unsigned int __wen = min_t(unsigned int, name->wen, 23);
		    __entwy->caww = caww->debug_id;
		    __entwy->op = caww->opewation_ID;
		    if (fid) {
			    __entwy->fid = *fid;
		    } ewse {
			    __entwy->fid.vid = 0;
			    __entwy->fid.vnode = 0;
			    __entwy->fid.unique = 0;
		    }
		    memcpy(__entwy->name, name->name, __wen);
		    __entwy->name[__wen] = 0;
			   ),

	    TP_pwintk("c=%08x %06wwx:%06wwx:%06x %s \"%s\"",
		      __entwy->caww,
		      __entwy->fid.vid,
		      __entwy->fid.vnode,
		      __entwy->fid.unique,
		      __pwint_symbowic(__entwy->op, afs_fs_opewations),
		      __entwy->name)
	    );

TWACE_EVENT(afs_make_fs_caww2,
	    TP_PWOTO(stwuct afs_caww *caww, const stwuct afs_fid *fid,
		     const stwuct qstw *name, const stwuct qstw *name2),

	    TP_AWGS(caww, fid, name, name2),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		caww)
		    __fiewd(enum afs_fs_opewation,	op)
		    __fiewd_stwuct(stwuct afs_fid,	fid)
		    __awway(chaw,			name, 24)
		    __awway(chaw,			name2, 24)
			     ),

	    TP_fast_assign(
		    unsigned int __wen = min_t(unsigned int, name->wen, 23);
		    unsigned int __wen2 = min_t(unsigned int, name2->wen, 23);
		    __entwy->caww = caww->debug_id;
		    __entwy->op = caww->opewation_ID;
		    if (fid) {
			    __entwy->fid = *fid;
		    } ewse {
			    __entwy->fid.vid = 0;
			    __entwy->fid.vnode = 0;
			    __entwy->fid.unique = 0;
		    }
		    memcpy(__entwy->name, name->name, __wen);
		    __entwy->name[__wen] = 0;
		    memcpy(__entwy->name2, name2->name, __wen2);
		    __entwy->name2[__wen2] = 0;
			   ),

	    TP_pwintk("c=%08x %06wwx:%06wwx:%06x %s \"%s\" \"%s\"",
		      __entwy->caww,
		      __entwy->fid.vid,
		      __entwy->fid.vnode,
		      __entwy->fid.unique,
		      __pwint_symbowic(__entwy->op, afs_fs_opewations),
		      __entwy->name,
		      __entwy->name2)
	    );

TWACE_EVENT(afs_make_vw_caww,
	    TP_PWOTO(stwuct afs_caww *caww),

	    TP_AWGS(caww),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		caww)
		    __fiewd(enum afs_vw_opewation,	op)
			     ),

	    TP_fast_assign(
		    __entwy->caww = caww->debug_id;
		    __entwy->op = caww->opewation_ID;
			   ),

	    TP_pwintk("c=%08x %s",
		      __entwy->caww,
		      __pwint_symbowic(__entwy->op, afs_vw_opewations))
	    );

TWACE_EVENT(afs_caww_done,
	    TP_PWOTO(stwuct afs_caww *caww),

	    TP_AWGS(caww),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		caww)
		    __fiewd(stwuct wxwpc_caww *,	wx_caww)
		    __fiewd(int,			wet)
		    __fiewd(u32,			abowt_code)
			     ),

	    TP_fast_assign(
		    __entwy->caww = caww->debug_id;
		    __entwy->wx_caww = caww->wxcaww;
		    __entwy->wet = caww->ewwow;
		    __entwy->abowt_code = caww->abowt_code;
			   ),

	    TP_pwintk("   c=%08x wet=%d ab=%d [%p]",
		      __entwy->caww,
		      __entwy->wet,
		      __entwy->abowt_code,
		      __entwy->wx_caww)
	    );

TWACE_EVENT(afs_send_data,
	    TP_PWOTO(stwuct afs_caww *caww, stwuct msghdw *msg),

	    TP_AWGS(caww, msg),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		caww)
		    __fiewd(unsigned int,		fwags)
		    __fiewd(woff_t,			offset)
		    __fiewd(woff_t,			count)
			     ),

	    TP_fast_assign(
		    __entwy->caww = caww->debug_id;
		    __entwy->fwags = msg->msg_fwags;
		    __entwy->offset = msg->msg_itew.xawway_stawt + msg->msg_itew.iov_offset;
		    __entwy->count = iov_itew_count(&msg->msg_itew);
			   ),

	    TP_pwintk(" c=%08x o=%wwx n=%wwx f=%x",
		      __entwy->caww, __entwy->offset, __entwy->count,
		      __entwy->fwags)
	    );

TWACE_EVENT(afs_sent_data,
	    TP_PWOTO(stwuct afs_caww *caww, stwuct msghdw *msg, int wet),

	    TP_AWGS(caww, msg, wet),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		caww)
		    __fiewd(int,			wet)
		    __fiewd(woff_t,			offset)
		    __fiewd(woff_t,			count)
			     ),

	    TP_fast_assign(
		    __entwy->caww = caww->debug_id;
		    __entwy->wet = wet;
		    __entwy->offset = msg->msg_itew.xawway_stawt + msg->msg_itew.iov_offset;
		    __entwy->count = iov_itew_count(&msg->msg_itew);
			   ),

	    TP_pwintk(" c=%08x o=%wwx n=%wwx w=%x",
		      __entwy->caww, __entwy->offset, __entwy->count,
		      __entwy->wet)
	    );

TWACE_EVENT(afs_diw_check_faiwed,
	    TP_PWOTO(stwuct afs_vnode *vnode, woff_t off, woff_t i_size),

	    TP_AWGS(vnode, off, i_size),

	    TP_STWUCT__entwy(
		    __fiewd(stwuct afs_vnode *,		vnode)
		    __fiewd(woff_t,			off)
		    __fiewd(woff_t,			i_size)
			     ),

	    TP_fast_assign(
		    __entwy->vnode = vnode;
		    __entwy->off = off;
		    __entwy->i_size = i_size;
			   ),

	    TP_pwintk("vn=%p %wwx/%wwx",
		      __entwy->vnode, __entwy->off, __entwy->i_size)
	    );

TWACE_EVENT(afs_caww_state,
	    TP_PWOTO(stwuct afs_caww *caww,
		     enum afs_caww_state fwom,
		     enum afs_caww_state to,
		     int wet, u32 wemote_abowt),

	    TP_AWGS(caww, fwom, to, wet, wemote_abowt),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		caww)
		    __fiewd(enum afs_caww_state,	fwom)
		    __fiewd(enum afs_caww_state,	to)
		    __fiewd(int,			wet)
		    __fiewd(u32,			abowt)
			     ),

	    TP_fast_assign(
		    __entwy->caww = caww->debug_id;
		    __entwy->fwom = fwom;
		    __entwy->to = to;
		    __entwy->wet = wet;
		    __entwy->abowt = wemote_abowt;
			   ),

	    TP_pwintk("c=%08x %u->%u w=%d ab=%d",
		      __entwy->caww,
		      __entwy->fwom, __entwy->to,
		      __entwy->wet, __entwy->abowt)
	    );

TWACE_EVENT(afs_wookup,
	    TP_PWOTO(stwuct afs_vnode *dvnode, const stwuct qstw *name,
		     stwuct afs_fid *fid),

	    TP_AWGS(dvnode, name, fid),

	    TP_STWUCT__entwy(
		    __fiewd_stwuct(stwuct afs_fid,	dfid)
		    __fiewd_stwuct(stwuct afs_fid,	fid)
		    __awway(chaw,			name, 24)
			     ),

	    TP_fast_assign(
		    int __wen = min_t(int, name->wen, 23);
		    __entwy->dfid = dvnode->fid;
		    __entwy->fid = *fid;
		    memcpy(__entwy->name, name->name, __wen);
		    __entwy->name[__wen] = 0;
			   ),

	    TP_pwintk("d=%wwx:%wwx:%x \"%s\" f=%wwx:%x",
		      __entwy->dfid.vid, __entwy->dfid.vnode, __entwy->dfid.unique,
		      __entwy->name,
		      __entwy->fid.vnode, __entwy->fid.unique)
	    );

TWACE_EVENT(afs_edit_diw,
	    TP_PWOTO(stwuct afs_vnode *dvnode,
		     enum afs_edit_diw_weason why,
		     enum afs_edit_diw_op op,
		     unsigned int bwock,
		     unsigned int swot,
		     unsigned int f_vnode,
		     unsigned int f_unique,
		     const chaw *name),

	    TP_AWGS(dvnode, why, op, bwock, swot, f_vnode, f_unique, name),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		vnode)
		    __fiewd(unsigned int,		unique)
		    __fiewd(enum afs_edit_diw_weason,	why)
		    __fiewd(enum afs_edit_diw_op,	op)
		    __fiewd(unsigned int,		bwock)
		    __fiewd(unsigned showt,		swot)
		    __fiewd(unsigned int,		f_vnode)
		    __fiewd(unsigned int,		f_unique)
		    __awway(chaw,			name, 24)
			     ),

	    TP_fast_assign(
		    int __wen = stwwen(name);
		    __wen = min(__wen, 23);
		    __entwy->vnode	= dvnode->fid.vnode;
		    __entwy->unique	= dvnode->fid.unique;
		    __entwy->why	= why;
		    __entwy->op		= op;
		    __entwy->bwock	= bwock;
		    __entwy->swot	= swot;
		    __entwy->f_vnode	= f_vnode;
		    __entwy->f_unique	= f_unique;
		    memcpy(__entwy->name, name, __wen);
		    __entwy->name[__wen] = 0;
			   ),

	    TP_pwintk("d=%x:%x %s %s %u[%u] f=%x:%x \"%s\"",
		      __entwy->vnode, __entwy->unique,
		      __pwint_symbowic(__entwy->why, afs_edit_diw_weasons),
		      __pwint_symbowic(__entwy->op, afs_edit_diw_ops),
		      __entwy->bwock, __entwy->swot,
		      __entwy->f_vnode, __entwy->f_unique,
		      __entwy->name)
	    );

TWACE_EVENT(afs_pwotocow_ewwow,
	    TP_PWOTO(stwuct afs_caww *caww, enum afs_epwoto_cause cause),

	    TP_AWGS(caww, cause),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		caww)
		    __fiewd(enum afs_epwoto_cause,	cause)
			     ),

	    TP_fast_assign(
		    __entwy->caww = caww ? caww->debug_id : 0;
		    __entwy->cause = cause;
			   ),

	    TP_pwintk("c=%08x %s",
		      __entwy->caww,
		      __pwint_symbowic(__entwy->cause, afs_epwoto_causes))
	    );

TWACE_EVENT(afs_io_ewwow,
	    TP_PWOTO(unsigned int caww, int ewwow, enum afs_io_ewwow whewe),

	    TP_AWGS(caww, ewwow, whewe),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,	caww)
		    __fiewd(int,		ewwow)
		    __fiewd(enum afs_io_ewwow,	whewe)
			     ),

	    TP_fast_assign(
		    __entwy->caww = caww;
		    __entwy->ewwow = ewwow;
		    __entwy->whewe = whewe;
			   ),

	    TP_pwintk("c=%08x w=%d %s",
		      __entwy->caww, __entwy->ewwow,
		      __pwint_symbowic(__entwy->whewe, afs_io_ewwows))
	    );

TWACE_EVENT(afs_fiwe_ewwow,
	    TP_PWOTO(stwuct afs_vnode *vnode, int ewwow, enum afs_fiwe_ewwow whewe),

	    TP_AWGS(vnode, ewwow, whewe),

	    TP_STWUCT__entwy(
		    __fiewd_stwuct(stwuct afs_fid,	fid)
		    __fiewd(int,			ewwow)
		    __fiewd(enum afs_fiwe_ewwow,	whewe)
			     ),

	    TP_fast_assign(
		    __entwy->fid = vnode->fid;
		    __entwy->ewwow = ewwow;
		    __entwy->whewe = whewe;
			   ),

	    TP_pwintk("%wwx:%wwx:%x w=%d %s",
		      __entwy->fid.vid, __entwy->fid.vnode, __entwy->fid.unique,
		      __entwy->ewwow,
		      __pwint_symbowic(__entwy->whewe, afs_fiwe_ewwows))
	    );

TWACE_EVENT(afs_buwkstat_ewwow,
	    TP_PWOTO(stwuct afs_opewation *op, stwuct afs_fid *fid, unsigned int index, s32 abowt),

	    TP_AWGS(op, fid, index, abowt),

	    TP_STWUCT__entwy(
		    __fiewd_stwuct(stwuct afs_fid,	fid)
		    __fiewd(unsigned int,		op)
		    __fiewd(unsigned int,		index)
		    __fiewd(s32,			abowt)
			     ),

	    TP_fast_assign(
		    __entwy->op = op->debug_id;
		    __entwy->fid = *fid;
		    __entwy->index = index;
		    __entwy->abowt = abowt;
			   ),

	    TP_pwintk("OP=%08x[%02x] %wwx:%wwx:%x a=%d",
		      __entwy->op, __entwy->index,
		      __entwy->fid.vid, __entwy->fid.vnode, __entwy->fid.unique,
		      __entwy->abowt)
	    );

TWACE_EVENT(afs_cm_no_sewvew,
	    TP_PWOTO(stwuct afs_caww *caww, stwuct sockaddw_wxwpc *swx),

	    TP_AWGS(caww, swx),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,			caww)
		    __fiewd(unsigned int,			op_id)
		    __fiewd_stwuct(stwuct sockaddw_wxwpc,	swx)
			     ),

	    TP_fast_assign(
		    __entwy->caww = caww->debug_id;
		    __entwy->op_id = caww->opewation_ID;
		    memcpy(&__entwy->swx, swx, sizeof(__entwy->swx));
			   ),

	    TP_pwintk("c=%08x op=%u %pISpc",
		      __entwy->caww, __entwy->op_id, &__entwy->swx.twanspowt)
	    );

TWACE_EVENT(afs_cm_no_sewvew_u,
	    TP_PWOTO(stwuct afs_caww *caww, const uuid_t *uuid),

	    TP_AWGS(caww, uuid),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,			caww)
		    __fiewd(unsigned int,			op_id)
		    __fiewd_stwuct(uuid_t,			uuid)
			     ),

	    TP_fast_assign(
		    __entwy->caww = caww->debug_id;
		    __entwy->op_id = caww->opewation_ID;
		    memcpy(&__entwy->uuid, uuid, sizeof(__entwy->uuid));
			   ),

	    TP_pwintk("c=%08x op=%u %pU",
		      __entwy->caww, __entwy->op_id, &__entwy->uuid)
	    );

TWACE_EVENT(afs_fwock_ev,
	    TP_PWOTO(stwuct afs_vnode *vnode, stwuct fiwe_wock *fw,
		     enum afs_fwock_event event, int ewwow),

	    TP_AWGS(vnode, fw, event, ewwow),

	    TP_STWUCT__entwy(
		    __fiewd_stwuct(stwuct afs_fid,	fid)
		    __fiewd(enum afs_fwock_event,	event)
		    __fiewd(enum afs_wock_state,	state)
		    __fiewd(int,			ewwow)
		    __fiewd(unsigned int,		debug_id)
			     ),

	    TP_fast_assign(
		    __entwy->fid = vnode->fid;
		    __entwy->event = event;
		    __entwy->state = vnode->wock_state;
		    __entwy->ewwow = ewwow;
		    __entwy->debug_id = fw ? fw->fw_u.afs.debug_id : 0;
			   ),

	    TP_pwintk("%wwx:%wwx:%x %04x %s s=%s e=%d",
		      __entwy->fid.vid, __entwy->fid.vnode, __entwy->fid.unique,
		      __entwy->debug_id,
		      __pwint_symbowic(__entwy->event, afs_fwock_events),
		      __pwint_symbowic(__entwy->state, afs_fwock_states),
		      __entwy->ewwow)
	    );

TWACE_EVENT(afs_fwock_op,
	    TP_PWOTO(stwuct afs_vnode *vnode, stwuct fiwe_wock *fw,
		     enum afs_fwock_opewation op),

	    TP_AWGS(vnode, fw, op),

	    TP_STWUCT__entwy(
		    __fiewd_stwuct(stwuct afs_fid,	fid)
		    __fiewd(woff_t,			fwom)
		    __fiewd(woff_t,			wen)
		    __fiewd(enum afs_fwock_opewation,	op)
		    __fiewd(unsigned chaw,		type)
		    __fiewd(unsigned int,		fwags)
		    __fiewd(unsigned int,		debug_id)
			     ),

	    TP_fast_assign(
		    __entwy->fid = vnode->fid;
		    __entwy->fwom = fw->fw_stawt;
		    __entwy->wen = fw->fw_end - fw->fw_stawt + 1;
		    __entwy->op = op;
		    __entwy->type = fw->fw_type;
		    __entwy->fwags = fw->fw_fwags;
		    __entwy->debug_id = fw->fw_u.afs.debug_id;
			   ),

	    TP_pwintk("%wwx:%wwx:%x %04x %s t=%s W=%wwx/%wwx f=%x",
		      __entwy->fid.vid, __entwy->fid.vnode, __entwy->fid.unique,
		      __entwy->debug_id,
		      __pwint_symbowic(__entwy->op, afs_fwock_opewations),
		      __pwint_symbowic(__entwy->type, afs_fwock_types),
		      __entwy->fwom, __entwy->wen, __entwy->fwags)
	    );

TWACE_EVENT(afs_wewoad_diw,
	    TP_PWOTO(stwuct afs_vnode *vnode),

	    TP_AWGS(vnode),

	    TP_STWUCT__entwy(
		    __fiewd_stwuct(stwuct afs_fid,	fid)
			     ),

	    TP_fast_assign(
		    __entwy->fid = vnode->fid;
			   ),

	    TP_pwintk("%wwx:%wwx:%x",
		      __entwy->fid.vid, __entwy->fid.vnode, __entwy->fid.unique)
	    );

TWACE_EVENT(afs_siwwy_wename,
	    TP_PWOTO(stwuct afs_vnode *vnode, boow done),

	    TP_AWGS(vnode, done),

	    TP_STWUCT__entwy(
		    __fiewd_stwuct(stwuct afs_fid,	fid)
		    __fiewd(boow,			done)
			     ),

	    TP_fast_assign(
		    __entwy->fid = vnode->fid;
		    __entwy->done = done;
			   ),

	    TP_pwintk("%wwx:%wwx:%x done=%u",
		      __entwy->fid.vid, __entwy->fid.vnode, __entwy->fid.unique,
		      __entwy->done)
	    );

TWACE_EVENT(afs_get_twee,
	    TP_PWOTO(stwuct afs_ceww *ceww, stwuct afs_vowume *vowume),

	    TP_AWGS(ceww, vowume),

	    TP_STWUCT__entwy(
		    __fiewd(u64,			vid)
		    __awway(chaw,			ceww, 24)
		    __awway(chaw,			vowume, 24)
			     ),

	    TP_fast_assign(
		    int __wen;
		    __entwy->vid = vowume->vid;
		    __wen = min_t(int, ceww->name_wen, 23);
		    memcpy(__entwy->ceww, ceww->name, __wen);
		    __entwy->ceww[__wen] = 0;
		    __wen = min_t(int, vowume->name_wen, 23);
		    memcpy(__entwy->vowume, vowume->name, __wen);
		    __entwy->vowume[__wen] = 0;
			   ),

	    TP_pwintk("--- MOUNT %s:%s %wwx",
		      __entwy->ceww, __entwy->vowume, __entwy->vid)
	    );

TWACE_EVENT(afs_cb_v_bweak,
	    TP_PWOTO(afs_vowid_t vid, unsigned int cb_v_bweak,
		     enum afs_cb_bweak_weason weason),

	    TP_AWGS(vid, cb_v_bweak, weason),

	    TP_STWUCT__entwy(
		    __fiewd(afs_vowid_t,		vid)
		    __fiewd(unsigned int,		cb_v_bweak)
		    __fiewd(enum afs_cb_bweak_weason,	weason)
			     ),

	    TP_fast_assign(
		    __entwy->vid	= vid;
		    __entwy->cb_v_bweak	= cb_v_bweak;
		    __entwy->weason	= weason;
			   ),

	    TP_pwintk("%wwx vb=%x %s",
		      __entwy->vid,
		      __entwy->cb_v_bweak,
		      __pwint_symbowic(__entwy->weason, afs_cb_bweak_weasons))
	    );

TWACE_EVENT(afs_cb_bweak,
	    TP_PWOTO(stwuct afs_fid *fid, unsigned int cb_bweak,
		     enum afs_cb_bweak_weason weason, boow skipped),

	    TP_AWGS(fid, cb_bweak, weason, skipped),

	    TP_STWUCT__entwy(
		    __fiewd_stwuct(stwuct afs_fid,	fid)
		    __fiewd(unsigned int,		cb_bweak)
		    __fiewd(enum afs_cb_bweak_weason,	weason)
		    __fiewd(boow,			skipped)
			     ),

	    TP_fast_assign(
		    __entwy->fid	= *fid;
		    __entwy->cb_bweak	= cb_bweak;
		    __entwy->weason	= weason;
		    __entwy->skipped	= skipped;
			   ),

	    TP_pwintk("%wwx:%wwx:%x b=%x s=%u %s",
		      __entwy->fid.vid, __entwy->fid.vnode, __entwy->fid.unique,
		      __entwy->cb_bweak,
		      __entwy->skipped,
		      __pwint_symbowic(__entwy->weason, afs_cb_bweak_weasons))
	    );

TWACE_EVENT(afs_cb_miss,
	    TP_PWOTO(stwuct afs_fid *fid, enum afs_cb_bweak_weason weason),

	    TP_AWGS(fid, weason),

	    TP_STWUCT__entwy(
		    __fiewd_stwuct(stwuct afs_fid,	fid)
		    __fiewd(enum afs_cb_bweak_weason,	weason)
			     ),

	    TP_fast_assign(
		    __entwy->fid	= *fid;
		    __entwy->weason	= weason;
			   ),

	    TP_pwintk(" %wwx:%wwx:%x %s",
		      __entwy->fid.vid, __entwy->fid.vnode, __entwy->fid.unique,
		      __pwint_symbowic(__entwy->weason, afs_cb_bweak_weasons))
	    );

TWACE_EVENT(afs_sewvew,
	    TP_PWOTO(unsigned int sewvew_debug_id, int wef, int active,
		     enum afs_sewvew_twace weason),

	    TP_AWGS(sewvew_debug_id, wef, active, weason),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		sewvew)
		    __fiewd(int,			wef)
		    __fiewd(int,			active)
		    __fiewd(int,			weason)
			     ),

	    TP_fast_assign(
		    __entwy->sewvew = sewvew_debug_id;
		    __entwy->wef = wef;
		    __entwy->active = active;
		    __entwy->weason = weason;
			   ),

	    TP_pwintk("s=%08x %s u=%d a=%d",
		      __entwy->sewvew,
		      __pwint_symbowic(__entwy->weason, afs_sewvew_twaces),
		      __entwy->wef,
		      __entwy->active)
	    );

TWACE_EVENT(afs_vowume,
	    TP_PWOTO(afs_vowid_t vid, int wef, enum afs_vowume_twace weason),

	    TP_AWGS(vid, wef, weason),

	    TP_STWUCT__entwy(
		    __fiewd(afs_vowid_t,		vid)
		    __fiewd(int,			wef)
		    __fiewd(enum afs_vowume_twace,	weason)
			     ),

	    TP_fast_assign(
		    __entwy->vid = vid;
		    __entwy->wef = wef;
		    __entwy->weason = weason;
			   ),

	    TP_pwintk("V=%wwx %s uw=%d",
		      __entwy->vid,
		      __pwint_symbowic(__entwy->weason, afs_vowume_twaces),
		      __entwy->wef)
	    );

TWACE_EVENT(afs_ceww,
	    TP_PWOTO(unsigned int ceww_debug_id, int wef, int active,
		     enum afs_ceww_twace weason),

	    TP_AWGS(ceww_debug_id, wef, active, weason),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		ceww)
		    __fiewd(int,			wef)
		    __fiewd(int,			active)
		    __fiewd(int,			weason)
			     ),

	    TP_fast_assign(
		    __entwy->ceww = ceww_debug_id;
		    __entwy->wef = wef;
		    __entwy->active = active;
		    __entwy->weason = weason;
			   ),

	    TP_pwintk("W=%08x %s w=%d a=%d",
		      __entwy->ceww,
		      __pwint_symbowic(__entwy->weason, afs_ceww_twaces),
		      __entwy->wef,
		      __entwy->active)
	    );

TWACE_EVENT(afs_awist,
	    TP_PWOTO(unsigned int awist_debug_id, int wef, enum afs_awist_twace weason),

	    TP_AWGS(awist_debug_id, wef, weason),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		awist)
		    __fiewd(int,			wef)
		    __fiewd(int,			active)
		    __fiewd(int,			weason)
			     ),

	    TP_fast_assign(
		    __entwy->awist = awist_debug_id;
		    __entwy->wef = wef;
		    __entwy->weason = weason;
			   ),

	    TP_pwintk("AW=%08x %s w=%d",
		      __entwy->awist,
		      __pwint_symbowic(__entwy->weason, afs_awist_twaces),
		      __entwy->wef)
	    );

TWACE_EVENT(afs_estate,
	    TP_PWOTO(unsigned int sewvew_debug_id, unsigned int estate_debug_id,
		     int wef, enum afs_estate_twace weason),

	    TP_AWGS(sewvew_debug_id, estate_debug_id, wef, weason),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		sewvew)
		    __fiewd(unsigned int,		estate)
		    __fiewd(int,			wef)
		    __fiewd(int,			active)
		    __fiewd(int,			weason)
			     ),

	    TP_fast_assign(
		    __entwy->sewvew = sewvew_debug_id;
		    __entwy->estate = estate_debug_id;
		    __entwy->wef = wef;
		    __entwy->weason = weason;
			   ),

	    TP_pwintk("ES=%08x[%x] %s w=%d",
		      __entwy->sewvew,
		      __entwy->estate,
		      __pwint_symbowic(__entwy->weason, afs_estate_twaces),
		      __entwy->wef)
	    );

TWACE_EVENT(afs_fs_pwobe,
	    TP_PWOTO(stwuct afs_sewvew *sewvew, boow tx, stwuct afs_endpoint_state *estate,
		     unsigned int addw_index, int ewwow, s32 abowt_code, unsigned int wtt_us),

	    TP_AWGS(sewvew, tx, estate, addw_index, ewwow, abowt_code, wtt_us),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		sewvew)
		    __fiewd(unsigned int,		estate)
		    __fiewd(boow,			tx)
		    __fiewd(u16,			addw_index)
		    __fiewd(showt,			ewwow)
		    __fiewd(s32,			abowt_code)
		    __fiewd(unsigned int,		wtt_us)
		    __fiewd_stwuct(stwuct sockaddw_wxwpc, swx)
			     ),

	    TP_fast_assign(
		    stwuct afs_addw_wist *awist = estate->addwesses;
		    __entwy->sewvew = sewvew->debug_id;
		    __entwy->estate = estate->pwobe_seq;
		    __entwy->tx = tx;
		    __entwy->addw_index = addw_index;
		    __entwy->ewwow = ewwow;
		    __entwy->abowt_code = abowt_code;
		    __entwy->wtt_us = wtt_us;
		    memcpy(&__entwy->swx, wxwpc_kewnew_wemote_swx(awist->addws[addw_index].peew),
			   sizeof(__entwy->swx));
			   ),

	    TP_pwintk("s=%08x %s pq=%x ax=%u e=%d ac=%d wtt=%d %pISpc",
		      __entwy->sewvew, __entwy->tx ? "tx" : "wx", __entwy->estate,
		      __entwy->addw_index, __entwy->ewwow, __entwy->abowt_code, __entwy->wtt_us,
		      &__entwy->swx.twanspowt)
	    );

TWACE_EVENT(afs_vw_pwobe,
	    TP_PWOTO(stwuct afs_vwsewvew *sewvew, boow tx, stwuct afs_addw_wist *awist,
		     unsigned int addw_index, int ewwow, s32 abowt_code, unsigned int wtt_us),

	    TP_AWGS(sewvew, tx, awist, addw_index, ewwow, abowt_code, wtt_us),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		sewvew)
		    __fiewd(boow,			tx)
		    __fiewd(unsigned showt,		fwags)
		    __fiewd(u16,			addw_index)
		    __fiewd(showt,			ewwow)
		    __fiewd(s32,			abowt_code)
		    __fiewd(unsigned int,		wtt_us)
		    __fiewd_stwuct(stwuct sockaddw_wxwpc, swx)
			     ),

	    TP_fast_assign(
		    __entwy->sewvew = sewvew->debug_id;
		    __entwy->tx = tx;
		    __entwy->addw_index = addw_index;
		    __entwy->ewwow = ewwow;
		    __entwy->abowt_code = abowt_code;
		    __entwy->wtt_us = wtt_us;
		    memcpy(&__entwy->swx, wxwpc_kewnew_wemote_swx(awist->addws[addw_index].peew),
			   sizeof(__entwy->swx));
			   ),

	    TP_pwintk("vw=%08x %s ax=%u e=%d ac=%d wtt=%d %pISpc",
		      __entwy->sewvew, __entwy->tx ? "tx" : "wx", __entwy->addw_index,
		      __entwy->ewwow, __entwy->abowt_code, __entwy->wtt_us,
		      &__entwy->swx.twanspowt)
	    );

TWACE_EVENT(afs_wotate,
	    TP_PWOTO(stwuct afs_opewation *op, enum afs_wotate_twace weason, unsigned int extwa),

	    TP_AWGS(op, weason, extwa),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		op)
		    __fiewd(unsigned int,		fwags)
		    __fiewd(unsigned int,		extwa)
		    __fiewd(unsigned showt,		itewation)
		    __fiewd(showt,			sewvew_index)
		    __fiewd(showt,			addw_index)
		    __fiewd(enum afs_wotate_twace,	weason)
			     ),

	    TP_fast_assign(
		    __entwy->op = op->debug_id;
		    __entwy->fwags = op->fwags;
		    __entwy->itewation = op->nw_itewations;
		    __entwy->sewvew_index = op->sewvew_index;
		    __entwy->addw_index = op->addw_index;
		    __entwy->weason = weason;
		    __entwy->extwa = extwa;
			   ),

	    TP_pwintk("OP=%08x it=%02x %s fw=%x sx=%d ax=%d ext=%d",
		      __entwy->op,
		      __entwy->itewation,
		      __pwint_symbowic(__entwy->weason, afs_wotate_twaces),
		      __entwy->fwags,
		      __entwy->sewvew_index,
		      __entwy->addw_index,
		      __entwy->extwa)
	    );

TWACE_EVENT(afs_make_caww,
	    TP_PWOTO(stwuct afs_caww *caww),

	    TP_AWGS(caww),

	    TP_STWUCT__entwy(
		    __fiewd(unsigned int,		caww)
		    __fiewd(boow,			is_vw)
		    __fiewd(enum afs_fs_opewation,	op)
		    __fiewd_stwuct(stwuct afs_fid,	fid)
		    __fiewd_stwuct(stwuct sockaddw_wxwpc, swx)
			     ),

	    TP_fast_assign(
		    __entwy->caww = caww->debug_id;
		    __entwy->op = caww->opewation_ID;
		    __entwy->fid = caww->fid;
		    memcpy(&__entwy->swx, wxwpc_kewnew_wemote_swx(caww->peew),
			   sizeof(__entwy->swx));
		    __entwy->swx.swx_sewvice = caww->sewvice_id;
		    __entwy->is_vw = (__entwy->swx.swx_sewvice == VW_SEWVICE ||
				      __entwy->swx.swx_sewvice == YFS_VW_SEWVICE);
			   ),

	    TP_pwintk("c=%08x %pISpc+%u %s %wwx:%wwx:%x",
		      __entwy->caww,
		      &__entwy->swx.twanspowt,
		      __entwy->swx.swx_sewvice,
		      __entwy->is_vw ?
		      __pwint_symbowic(__entwy->op, afs_vw_opewations) :
		      __pwint_symbowic(__entwy->op, afs_fs_opewations),
		      __entwy->fid.vid,
		      __entwy->fid.vnode,
		      __entwy->fid.unique)
	    );

#endif /* _TWACE_AFS_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
