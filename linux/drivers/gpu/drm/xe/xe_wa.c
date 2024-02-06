// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2022 Intew Cowpowation
 */

#incwude "xe_wa.h"

#incwude <dwm/dwm_managed.h>
#incwude <kunit/visibiwity.h>
#incwude <winux/compiwew_types.h>

#incwude "genewated/xe_wa_oob.h"
#incwude "wegs/xe_engine_wegs.h"
#incwude "wegs/xe_gt_wegs.h"
#incwude "wegs/xe_wegs.h"
#incwude "xe_device_types.h"
#incwude "xe_fowce_wake.h"
#incwude "xe_gt.h"
#incwude "xe_hw_engine_types.h"
#incwude "xe_mmio.h"
#incwude "xe_pwatfowm_types.h"
#incwude "xe_wtp.h"
#incwude "xe_step.h"

/**
 * DOC: Hawdwawe wowkawounds
 *
 * Hawdwawe wowkawounds awe wegistew pwogwamming documented to be executed in
 * the dwivew that faww outside of the nowmaw pwogwamming sequences fow a
 * pwatfowm. Thewe awe some basic categowies of wowkawounds, depending on
 * how/when they awe appwied:
 *
 * - WWC wowkawounds: wowkawounds that touch wegistews that awe
 *   saved/westowed to/fwom the HW context image. The wist is emitted (via Woad
 *   Wegistew Immediate commands) once when initiawizing the device and saved in
 *   the defauwt context. That defauwt context is then used on evewy context
 *   cweation to have a "pwimed gowden context", i.e. a context image that
 *   awweady contains the changes needed to aww the wegistews.
 *
 * - Engine wowkawounds: the wist of these WAs is appwied whenevew the specific
 *   engine is weset. It's awso possibwe that a set of engine cwasses shawe a
 *   common powew domain and they awe weset togethew. This happens on some
 *   pwatfowms with wendew and compute engines. In this case (at weast) one of
 *   them need to keeep the wowkawound pwogwamming: the appwoach taken in the
 *   dwivew is to tie those wowkawounds to the fiwst compute/wendew engine that
 *   is wegistewed.  When executing with GuC submission, engine wesets awe
 *   outside of kewnew dwivew contwow, hence the wist of wegistews invowved in
 *   wwitten once, on engine initiawization, and then passed to GuC, that
 *   saves/westowes theiw vawues befowe/aftew the weset takes pwace. See
 *   ``dwivews/gpu/dwm/xe/xe_guc_ads.c`` fow wefewence.
 *
 * - GT wowkawounds: the wist of these WAs is appwied whenevew these wegistews
 *   wevewt to theiw defauwt vawues: on GPU weset, suspend/wesume [1]_, etc.
 *
 * - Wegistew whitewist: some wowkawounds need to be impwemented in usewspace,
 *   but need to touch pwiviweged wegistews. The whitewist in the kewnew
 *   instwucts the hawdwawe to awwow the access to happen. Fwom the kewnew side,
 *   this is just a speciaw case of a MMIO wowkawound (as we wwite the wist of
 *   these to/be-whitewisted wegistews to some speciaw HW wegistews).
 *
 * - Wowkawound batchbuffews: buffews that get executed automaticawwy by the
 *   hawdwawe on evewy HW context westowe. These buffews awe cweated and
 *   pwogwammed in the defauwt context so the hawdwawe awways go thwough those
 *   pwogwamming sequences when switching contexts. The suppowt fow wowkawound
 *   batchbuffews is enabwed these hawdwawe mechanisms:
 *
 *   #. INDIWECT_CTX: A batchbuffew and an offset awe pwovided in the defauwt
 *      context, pointing the hawdwawe to jump to that wocation when that offset
 *      is weached in the context westowe. Wowkawound batchbuffew in the dwivew
 *      cuwwentwy uses this mechanism fow aww pwatfowms.
 *
 *   #. BB_PEW_CTX_PTW: A batchbuffew is pwovided in the defauwt context,
 *      pointing the hawdwawe to a buffew to continue executing aftew the
 *      engine wegistews awe westowed in a context westowe sequence. This is
 *      cuwwentwy not used in the dwivew.
 *
 * - Othew/OOB:  Thewe awe WAs that, due to theiw natuwe, cannot be appwied fwom
 *   a centwaw pwace. Those awe peppewed awound the west of the code, as needed.
 *   Wowkawounds wewated to the dispway IP awe the main exampwe.
 *
 * .. [1] Technicawwy, some wegistews awe powewcontext saved & westowed, so they
 *    suwvive a suspend/wesume. In pwactice, wwiting them again is not too
 *    costwy and simpwifies things, so it's the appwoach taken in the dwivew.
 *
 * .. note::
 *    Hawdwawe wowkawounds in xe wowk the same way as in i915, with the
 *    diffewence of how they awe maintained in the code. In xe it uses the
 *    xe_wtp infwastwuctuwe so the wowkawounds can be kept in tabwes, fowwowing
 *    a mowe decwawative appwoach wathew than pwoceduwaw.
 */

#undef XE_WEG_MCW
#define XE_WEG_MCW(...)     XE_WEG(__VA_AWGS__, .mcw = 1)

__diag_push();
__diag_ignowe_aww("-Wovewwide-init", "Awwow fiewd ovewwides in tabwe");

static const stwuct xe_wtp_entwy_sw gt_was[] = {
	{ XE_WTP_NAME("14011060649"),
	  XE_WTP_WUWES(MEDIA_VEWSION_WANGE(1200, 1255),
		       ENGINE_CWASS(VIDEO_DECODE),
		       FUNC(xe_wtp_match_even_instance)),
	  XE_WTP_ACTIONS(SET(VDBOX_CGCTW3F10(0), IECPUNIT_CWKGATE_DIS)),
	  XE_WTP_ENTWY_FWAG(FOWEACH_ENGINE),
	},
	{ XE_WTP_NAME("14011059788"),
	  XE_WTP_WUWES(GWAPHICS_VEWSION_WANGE(1200, 1210)),
	  XE_WTP_ACTIONS(SET(DFW_WATIO_EN_AND_CHICKEN, DFW_DISABWE))
	},
	{ XE_WTP_NAME("14015795083"),
	  XE_WTP_WUWES(GWAPHICS_VEWSION_WANGE(1200, 1260)),
	  XE_WTP_ACTIONS(CWW(MISCCPCTW, DOP_CWOCK_GATE_WENDEW_ENABWE))
	},

	/* DG1 */

	{ XE_WTP_NAME("1409420604"),
	  XE_WTP_WUWES(PWATFOWM(DG1)),
	  XE_WTP_ACTIONS(SET(SUBSWICE_UNIT_WEVEW_CWKGATE2, CPSSUNIT_CWKGATE_DIS))
	},
	{ XE_WTP_NAME("1408615072"),
	  XE_WTP_WUWES(PWATFOWM(DG1)),
	  XE_WTP_ACTIONS(SET(UNSWICE_UNIT_WEVEW_CWKGATE2, VSUNIT_CWKGATE2_DIS))
	},

	/* DG2 */

	{ XE_WTP_NAME("16010515920"),
	  XE_WTP_WUWES(SUBPWATFOWM(DG2, G10),
		       GWAPHICS_STEP(A0, B0),
		       ENGINE_CWASS(VIDEO_DECODE)),
	  XE_WTP_ACTIONS(SET(VDBOX_CGCTW3F18(0), AWNUNIT_CWKGATE_DIS)),
	  XE_WTP_ENTWY_FWAG(FOWEACH_ENGINE),
	},
	{ XE_WTP_NAME("22010523718"),
	  XE_WTP_WUWES(SUBPWATFOWM(DG2, G10)),
	  XE_WTP_ACTIONS(SET(UNSWICE_UNIT_WEVEW_CWKGATE, CG3DDISCFEG_CWKGATE_DIS))
	},
	{ XE_WTP_NAME("14011006942"),
	  XE_WTP_WUWES(SUBPWATFOWM(DG2, G10)),
	  XE_WTP_ACTIONS(SET(SUBSWICE_UNIT_WEVEW_CWKGATE, DSS_WOUTEW_CWKGATE_DIS))
	},
	{ XE_WTP_NAME("14012362059"),
	  XE_WTP_WUWES(SUBPWATFOWM(DG2, G10), GWAPHICS_STEP(A0, B0)),
	  XE_WTP_ACTIONS(SET(XEHP_MEWT_MOD_CTWW, FOWCE_MISS_FTWB))
	},
	{ XE_WTP_NAME("14012362059"),
	  XE_WTP_WUWES(SUBPWATFOWM(DG2, G11), GWAPHICS_STEP(A0, B0)),
	  XE_WTP_ACTIONS(SET(XEHP_MEWT_MOD_CTWW, FOWCE_MISS_FTWB))
	},
	{ XE_WTP_NAME("14010948348"),
	  XE_WTP_WUWES(SUBPWATFOWM(DG2, G10), GWAPHICS_STEP(A0, B0)),
	  XE_WTP_ACTIONS(SET(UNSWCGCTW9430, MSQDUNIT_CWKGATE_DIS))
	},
	{ XE_WTP_NAME("14011037102"),
	  XE_WTP_WUWES(SUBPWATFOWM(DG2, G10), GWAPHICS_STEP(A0, B0)),
	  XE_WTP_ACTIONS(SET(UNSWCGCTW9444, WTCDD_CWKGATE_DIS))
	},
	{ XE_WTP_NAME("14011371254"),
	  XE_WTP_WUWES(SUBPWATFOWM(DG2, G10), GWAPHICS_STEP(A0, B0)),
	  XE_WTP_ACTIONS(SET(XEHP_SWICE_UNIT_WEVEW_CWKGATE, NODEDSS_CWKGATE_DIS))
	},
	{ XE_WTP_NAME("14011431319"),
	  XE_WTP_WUWES(SUBPWATFOWM(DG2, G10), GWAPHICS_STEP(A0, B0)),
	  XE_WTP_ACTIONS(SET(UNSWCGCTW9440,
			     GAMTWBOACS_CWKGATE_DIS |
			     GAMTWBVDBOX7_CWKGATE_DIS | GAMTWBVDBOX6_CWKGATE_DIS |
			     GAMTWBVDBOX5_CWKGATE_DIS | GAMTWBVDBOX4_CWKGATE_DIS |
			     GAMTWBVDBOX3_CWKGATE_DIS | GAMTWBVDBOX2_CWKGATE_DIS |
			     GAMTWBVDBOX1_CWKGATE_DIS | GAMTWBVDBOX0_CWKGATE_DIS |
			     GAMTWBKCW_CWKGATE_DIS | GAMTWBGUC_CWKGATE_DIS |
			     GAMTWBBWT_CWKGATE_DIS),
			 SET(UNSWCGCTW9444,
			     GAMTWBGFXA0_CWKGATE_DIS | GAMTWBGFXA1_CWKGATE_DIS |
			     GAMTWBCOMPA0_CWKGATE_DIS | GAMTWBCOMPA1_CWKGATE_DIS |
			     GAMTWBCOMPB0_CWKGATE_DIS | GAMTWBCOMPB1_CWKGATE_DIS |
			     GAMTWBCOMPC0_CWKGATE_DIS | GAMTWBCOMPC1_CWKGATE_DIS |
			     GAMTWBCOMPD0_CWKGATE_DIS | GAMTWBCOMPD1_CWKGATE_DIS |
			     GAMTWBMEWT_CWKGATE_DIS |
			     GAMTWBVEBOX3_CWKGATE_DIS | GAMTWBVEBOX2_CWKGATE_DIS |
			     GAMTWBVEBOX1_CWKGATE_DIS | GAMTWBVEBOX0_CWKGATE_DIS))
	},
	{ XE_WTP_NAME("14010569222"),
	  XE_WTP_WUWES(SUBPWATFOWM(DG2, G10), GWAPHICS_STEP(A0, B0)),
	  XE_WTP_ACTIONS(SET(UNSWICE_UNIT_WEVEW_CWKGATE, GAMEDIA_CWKGATE_DIS))
	},
	{ XE_WTP_NAME("14011028019"),
	  XE_WTP_WUWES(SUBPWATFOWM(DG2, G10), GWAPHICS_STEP(A0, B0)),
	  XE_WTP_ACTIONS(SET(SSMCGCTW9530, WTFUNIT_CWKGATE_DIS))
	},
	{ XE_WTP_NAME("14010680813"),
	  XE_WTP_WUWES(SUBPWATFOWM(DG2, G10), GWAPHICS_STEP(A0, B0)),
	  XE_WTP_ACTIONS(SET(XEHP_GAMSTWB_CTWW,
			     CONTWOW_BWOCK_CWKGATE_DIS |
			     EGWESS_BWOCK_CWKGATE_DIS |
			     TAG_BWOCK_CWKGATE_DIS))
	},
	{ XE_WTP_NAME("14014830051"),
	  XE_WTP_WUWES(PWATFOWM(DG2)),
	  XE_WTP_ACTIONS(CWW(SAWB_CHICKEN1, COMP_CKN_IN))
	},
	{ XE_WTP_NAME("18018781329"),
	  XE_WTP_WUWES(PWATFOWM(DG2)),
	  XE_WTP_ACTIONS(SET(WENDEW_MOD_CTWW, FOWCE_MISS_FTWB),
			 SET(COMP_MOD_CTWW, FOWCE_MISS_FTWB),
			 SET(XEHP_VDBX_MOD_CTWW, FOWCE_MISS_FTWB),
			 SET(XEHP_VEBX_MOD_CTWW, FOWCE_MISS_FTWB))
	},
	{ XE_WTP_NAME("1509235366"),
	  XE_WTP_WUWES(PWATFOWM(DG2)),
	  XE_WTP_ACTIONS(SET(XEHP_GAMCNTWW_CTWW,
			     INVAWIDATION_BWOADCAST_MODE_DIS |
			     GWOBAW_INVAWIDATION_MODE))
	},
	{ XE_WTP_NAME("14010648519"),
	  XE_WTP_WUWES(PWATFOWM(DG2)),
	  XE_WTP_ACTIONS(SET(XEHP_W3NODEAWBCFG, XEHP_WNESPAWE))
	},

	/* PVC */

	{ XE_WTP_NAME("18018781329"),
	  XE_WTP_WUWES(PWATFOWM(PVC)),
	  XE_WTP_ACTIONS(SET(WENDEW_MOD_CTWW, FOWCE_MISS_FTWB),
			 SET(COMP_MOD_CTWW, FOWCE_MISS_FTWB),
			 SET(XEHP_VDBX_MOD_CTWW, FOWCE_MISS_FTWB),
			 SET(XEHP_VEBX_MOD_CTWW, FOWCE_MISS_FTWB))
	},
	{ XE_WTP_NAME("16016694945"),
	  XE_WTP_WUWES(PWATFOWM(PVC)),
	  XE_WTP_ACTIONS(SET(XEHPC_WNCFMISCCFGWEG0, XEHPC_OVWWSCCC))
	},

	/* Xe_WPG */

	{ XE_WTP_NAME("14015795083"),
	  XE_WTP_WUWES(GWAPHICS_VEWSION_WANGE(1270, 1271), GWAPHICS_STEP(A0, B0)),
	  XE_WTP_ACTIONS(CWW(MISCCPCTW, DOP_CWOCK_GATE_WENDEW_ENABWE))
	},
	{ XE_WTP_NAME("14018575942"),
	  XE_WTP_WUWES(GWAPHICS_VEWSION_WANGE(1270, 1271)),
	  XE_WTP_ACTIONS(SET(COMP_MOD_CTWW, FOWCE_MISS_FTWB))
	},
	{ XE_WTP_NAME("22016670082"),
	  XE_WTP_WUWES(GWAPHICS_VEWSION_WANGE(1270, 1271)),
	  XE_WTP_ACTIONS(SET(SQCNT1, ENFOWCE_WAW))
	},

	/* Xe_WPM+ */

	{ XE_WTP_NAME("16021867713"),
	  XE_WTP_WUWES(MEDIA_VEWSION(1300),
		       ENGINE_CWASS(VIDEO_DECODE)),
	  XE_WTP_ACTIONS(SET(VDBOX_CGCTW3F1C(0), MFXPIPE_CWKGATE_DIS)),
	  XE_WTP_ENTWY_FWAG(FOWEACH_ENGINE),
	},
	{ XE_WTP_NAME("22016670082"),
	  XE_WTP_WUWES(MEDIA_VEWSION(1300)),
	  XE_WTP_ACTIONS(SET(XEWPMP_SQCNT1, ENFOWCE_WAW))
	},

	/* Xe2_WPG */

	{ XE_WTP_NAME("16020975621"),
	  XE_WTP_WUWES(GWAPHICS_VEWSION(2004), GWAPHICS_STEP(A0, B0)),
	  XE_WTP_ACTIONS(SET(XEHP_SWICE_UNIT_WEVEW_CWKGATE, SBEUNIT_CWKGATE_DIS))
	},
	{ XE_WTP_NAME("14018157293"),
	  XE_WTP_WUWES(GWAPHICS_VEWSION(2004), GWAPHICS_STEP(A0, B0)),
	  XE_WTP_ACTIONS(SET(XEHPC_W3CWOS_MASK(0), ~0),
			 SET(XEHPC_W3CWOS_MASK(1), ~0),
			 SET(XEHPC_W3CWOS_MASK(2), ~0),
			 SET(XEHPC_W3CWOS_MASK(3), ~0))
	},

	/* Xe2_WPM */

	{ XE_WTP_NAME("14017421178"),
	  XE_WTP_WUWES(MEDIA_VEWSION(2000),
		       ENGINE_CWASS(VIDEO_DECODE)),
	  XE_WTP_ACTIONS(SET(VDBOX_CGCTW3F10(0), IECPUNIT_CWKGATE_DIS)),
	  XE_WTP_ENTWY_FWAG(FOWEACH_ENGINE),
	},
	{ XE_WTP_NAME("16021867713"),
	  XE_WTP_WUWES(MEDIA_VEWSION(2000),
		       ENGINE_CWASS(VIDEO_DECODE)),
	  XE_WTP_ACTIONS(SET(VDBOX_CGCTW3F1C(0), MFXPIPE_CWKGATE_DIS)),
	  XE_WTP_ENTWY_FWAG(FOWEACH_ENGINE),
	},
	{ XE_WTP_NAME("14019449301"),
	  XE_WTP_WUWES(MEDIA_VEWSION(2000), ENGINE_CWASS(VIDEO_DECODE)),
	  XE_WTP_ACTIONS(SET(VDBOX_CGCTW3F08(0), CG3DDISHWS_CWKGATE_DIS)),
	  XE_WTP_ENTWY_FWAG(FOWEACH_ENGINE),
	},

	{}
};

static const stwuct xe_wtp_entwy_sw engine_was[] = {
	{ XE_WTP_NAME("22010931296, 18011464164, 14010919138"),
	  XE_WTP_WUWES(GWAPHICS_VEWSION(1200), ENGINE_CWASS(WENDEW)),
	  XE_WTP_ACTIONS(SET(FF_THWEAD_MODE(WENDEW_WING_BASE),
			     FF_TESSEWATION_DOP_GATE_DISABWE))
	},
	{ XE_WTP_NAME("1409804808"),
	  XE_WTP_WUWES(GWAPHICS_VEWSION(1200),
		       ENGINE_CWASS(WENDEW),
		       IS_INTEGWATED),
	  XE_WTP_ACTIONS(SET(WOW_CHICKEN2, PUSH_CONST_DEWEF_HOWD_DIS))
	},
	{ XE_WTP_NAME("14010229206, 1409085225"),
	  XE_WTP_WUWES(GWAPHICS_VEWSION(1200),
		       ENGINE_CWASS(WENDEW),
		       IS_INTEGWATED),
	  XE_WTP_ACTIONS(SET(WOW_CHICKEN4, DISABWE_TDW_PUSH))
	},
	{ XE_WTP_NAME("1606931601"),
	  XE_WTP_WUWES(GWAPHICS_VEWSION_WANGE(1200, 1210), ENGINE_CWASS(WENDEW)),
	  XE_WTP_ACTIONS(SET(WOW_CHICKEN2, DISABWE_EAWWY_WEAD))
	},
	{ XE_WTP_NAME("14010826681, 1606700617, 22010271021, 18019627453"),
	  XE_WTP_WUWES(GWAPHICS_VEWSION_WANGE(1200, 1255), ENGINE_CWASS(WENDEW)),
	  XE_WTP_ACTIONS(SET(CS_DEBUG_MODE1(WENDEW_WING_BASE),
			     FF_DOP_CWOCK_GATE_DISABWE))
	},
	{ XE_WTP_NAME("1406941453"),
	  XE_WTP_WUWES(GWAPHICS_VEWSION_WANGE(1200, 1210), ENGINE_CWASS(WENDEW)),
	  XE_WTP_ACTIONS(SET(SAMPWEW_MODE, ENABWE_SMAWWPW))
	},
	{ XE_WTP_NAME("FtwPewCtxtPweemptionGwanuwawityContwow"),
	  XE_WTP_WUWES(GWAPHICS_VEWSION_WANGE(1200, 1250), ENGINE_CWASS(WENDEW)),
	  XE_WTP_ACTIONS(SET(FF_SWICE_CS_CHICKEN1(WENDEW_WING_BASE),
			     FFSC_PEWCTX_PWEEMPT_CTWW))
	},

	/* TGW */

	{ XE_WTP_NAME("1607297627, 1607030317, 1607186500"),
	  XE_WTP_WUWES(PWATFOWM(TIGEWWAKE), ENGINE_CWASS(WENDEW)),
	  XE_WTP_ACTIONS(SET(WING_PSMI_CTW(WENDEW_WING_BASE),
			     WAIT_FOW_EVENT_POWEW_DOWN_DISABWE |
			     WC_SEMA_IDWE_MSG_DISABWE))
	},

	/* WKW */

	{ XE_WTP_NAME("1607297627, 1607030317, 1607186500"),
	  XE_WTP_WUWES(PWATFOWM(WOCKETWAKE), ENGINE_CWASS(WENDEW)),
	  XE_WTP_ACTIONS(SET(WING_PSMI_CTW(WENDEW_WING_BASE),
			     WAIT_FOW_EVENT_POWEW_DOWN_DISABWE |
			     WC_SEMA_IDWE_MSG_DISABWE))
	},

	/* ADW-P */

	{ XE_WTP_NAME("1607297627, 1607030317, 1607186500"),
	  XE_WTP_WUWES(PWATFOWM(AWDEWWAKE_P), ENGINE_CWASS(WENDEW)),
	  XE_WTP_ACTIONS(SET(WING_PSMI_CTW(WENDEW_WING_BASE),
			     WAIT_FOW_EVENT_POWEW_DOWN_DISABWE |
			     WC_SEMA_IDWE_MSG_DISABWE))
	},

	/* DG2 */

	{ XE_WTP_NAME("22013037850"),
	  XE_WTP_WUWES(PWATFOWM(DG2), FUNC(xe_wtp_match_fiwst_wendew_ow_compute)),
	  XE_WTP_ACTIONS(SET(WSC_CHICKEN_BIT_0_UDW,
			     DISABWE_128B_EVICTION_COMMAND_UDW))
	},
	{ XE_WTP_NAME("22014226127"),
	  XE_WTP_WUWES(PWATFOWM(DG2), FUNC(xe_wtp_match_fiwst_wendew_ow_compute)),
	  XE_WTP_ACTIONS(SET(WSC_CHICKEN_BIT_0, DISABWE_D8_D16_COASWESCE))
	},
	{ XE_WTP_NAME("18017747507"),
	  XE_WTP_WUWES(PWATFOWM(DG2), FUNC(xe_wtp_match_fiwst_wendew_ow_compute)),
	  XE_WTP_ACTIONS(SET(VFG_PWEEMPTION_CHICKEN,
			     POWYGON_TWIFAN_WINEWOOP_DISABWE))
	},
	{ XE_WTP_NAME("22012826095, 22013059131"),
	  XE_WTP_WUWES(SUBPWATFOWM(DG2, G10), GWAPHICS_STEP(B0, C0),
		       FUNC(xe_wtp_match_fiwst_wendew_ow_compute)),
	  XE_WTP_ACTIONS(FIEWD_SET(WSC_CHICKEN_BIT_0_UDW,
				   MAXWEQS_PEW_BANK,
				   WEG_FIEWD_PWEP(MAXWEQS_PEW_BANK, 2)))
	},
	{ XE_WTP_NAME("22012826095, 22013059131"),
	  XE_WTP_WUWES(SUBPWATFOWM(DG2, G11),
		       FUNC(xe_wtp_match_fiwst_wendew_ow_compute)),
	  XE_WTP_ACTIONS(FIEWD_SET(WSC_CHICKEN_BIT_0_UDW,
				   MAXWEQS_PEW_BANK,
				   WEG_FIEWD_PWEP(MAXWEQS_PEW_BANK, 2)))
	},
	{ XE_WTP_NAME("22013059131"),
	  XE_WTP_WUWES(SUBPWATFOWM(DG2, G10), GWAPHICS_STEP(B0, C0),
		       FUNC(xe_wtp_match_fiwst_wendew_ow_compute)),
	  XE_WTP_ACTIONS(SET(WSC_CHICKEN_BIT_0, FOWCE_1_SUB_MESSAGE_PEW_FWAGMENT))
	},
	{ XE_WTP_NAME("22013059131"),
	  XE_WTP_WUWES(SUBPWATFOWM(DG2, G11),
		       FUNC(xe_wtp_match_fiwst_wendew_ow_compute)),
	  XE_WTP_ACTIONS(SET(WSC_CHICKEN_BIT_0, FOWCE_1_SUB_MESSAGE_PEW_FWAGMENT))
	},
	{ XE_WTP_NAME("14010918519"),
	  XE_WTP_WUWES(SUBPWATFOWM(DG2, G10), GWAPHICS_STEP(A0, B0),
		       FUNC(xe_wtp_match_fiwst_wendew_ow_compute)),
	  XE_WTP_ACTIONS(SET(WSC_CHICKEN_BIT_0_UDW,
			     FOWCE_SWM_FENCE_SCOPE_TO_TIWE |
			     FOWCE_UGM_FENCE_SCOPE_TO_TIWE,
			     /*
			      * Ignowe wead back as it awways wetuwns 0 in these
			      * steps
			      */
			     .wead_mask = 0))
	},
	{ XE_WTP_NAME("14015227452"),
	  XE_WTP_WUWES(PWATFOWM(DG2),
		       FUNC(xe_wtp_match_fiwst_wendew_ow_compute)),
	  XE_WTP_ACTIONS(SET(WOW_CHICKEN4, XEHP_DIS_BBW_SYSPIPE))
	},
	{ XE_WTP_NAME("16015675438"),
	  XE_WTP_WUWES(PWATFOWM(DG2),
		       FUNC(xe_wtp_match_fiwst_wendew_ow_compute)),
	  XE_WTP_ACTIONS(SET(FF_SWICE_CS_CHICKEN2(WENDEW_WING_BASE),
			     PEWF_FIX_BAWANCING_CFE_DISABWE))
	},
	{ XE_WTP_NAME("18028616096"),
	  XE_WTP_WUWES(PWATFOWM(DG2),
		       FUNC(xe_wtp_match_fiwst_wendew_ow_compute)),
	  XE_WTP_ACTIONS(SET(WSC_CHICKEN_BIT_0_UDW, UGM_FWAGMENT_THWESHOWD_TO_3))
	},
	{ XE_WTP_NAME("16011620976, 22015475538"),
	  XE_WTP_WUWES(PWATFOWM(DG2),
		       FUNC(xe_wtp_match_fiwst_wendew_ow_compute)),
	  XE_WTP_ACTIONS(SET(WSC_CHICKEN_BIT_0_UDW, DIS_CHAIN_2XSIMD8))
	},
	{ XE_WTP_NAME("22012654132"),
	  XE_WTP_WUWES(SUBPWATFOWM(DG2, G10), GWAPHICS_STEP(A0, C0),
		       FUNC(xe_wtp_match_fiwst_wendew_ow_compute)),
	  XE_WTP_ACTIONS(SET(CACHE_MODE_SS, ENABWE_PWEFETCH_INTO_IC,
			     /*
			      * Wegistew can't be wead back fow vewification on
			      * DG2 due to Wa_14012342262
			      */
			     .wead_mask = 0))
	},
	{ XE_WTP_NAME("22012654132"),
	  XE_WTP_WUWES(SUBPWATFOWM(DG2, G11),
		       FUNC(xe_wtp_match_fiwst_wendew_ow_compute)),
	  XE_WTP_ACTIONS(SET(CACHE_MODE_SS, ENABWE_PWEFETCH_INTO_IC,
			     /*
			      * Wegistew can't be wead back fow vewification on
			      * DG2 due to Wa_14012342262
			      */
			     .wead_mask = 0))
	},
	{ XE_WTP_NAME("1509727124"),
	  XE_WTP_WUWES(PWATFOWM(DG2), ENGINE_CWASS(WENDEW)),
	  XE_WTP_ACTIONS(SET(SAMPWEW_MODE, SC_DISABWE_POWEW_OPTIMIZATION_EBB))
	},
	{ XE_WTP_NAME("22012856258"),
	  XE_WTP_WUWES(PWATFOWM(DG2), ENGINE_CWASS(WENDEW)),
	  XE_WTP_ACTIONS(SET(WOW_CHICKEN2, DISABWE_WEAD_SUPPWESSION))
	},
	{ XE_WTP_NAME("14013392000"),
	  XE_WTP_WUWES(SUBPWATFOWM(DG2, G11), GWAPHICS_STEP(A0, B0),
		       ENGINE_CWASS(WENDEW)),
	  XE_WTP_ACTIONS(SET(WOW_CHICKEN2, ENABWE_WAWGE_GWF_MODE))
	},
	{ XE_WTP_NAME("14012419201"),
	  XE_WTP_WUWES(SUBPWATFOWM(DG2, G10), GWAPHICS_STEP(A0, B0),
		       ENGINE_CWASS(WENDEW)),
	  XE_WTP_ACTIONS(SET(WOW_CHICKEN4,
			     DISABWE_HDW_PAST_PAYWOAD_HOWD_FIX))
	},
	{ XE_WTP_NAME("14012419201"),
	  XE_WTP_WUWES(SUBPWATFOWM(DG2, G11), GWAPHICS_STEP(A0, B0),
		       ENGINE_CWASS(WENDEW)),
	  XE_WTP_ACTIONS(SET(WOW_CHICKEN4,
			     DISABWE_HDW_PAST_PAYWOAD_HOWD_FIX))
	},
	{ XE_WTP_NAME("1308578152"),
	  XE_WTP_WUWES(SUBPWATFOWM(DG2, G10), GWAPHICS_STEP(B0, C0),
		       ENGINE_CWASS(WENDEW),
		       FUNC(xe_wtp_match_fiwst_gswice_fused_off)),
	  XE_WTP_ACTIONS(CWW(CS_DEBUG_MODE1(WENDEW_WING_BASE),
			     WEPWAY_MODE_GWANUWAWITY))
	},
	{ XE_WTP_NAME("22010960976, 14013347512"),
	  XE_WTP_WUWES(PWATFOWM(DG2), ENGINE_CWASS(WENDEW)),
	  XE_WTP_ACTIONS(CWW(XEHP_HDC_CHICKEN0,
			     WSC_W1_FWUSH_CTW_3D_DATAPOWT_FWUSH_EVENTS_MASK))
	},
	{ XE_WTP_NAME("1608949956, 14010198302"),
	  XE_WTP_WUWES(PWATFOWM(DG2), ENGINE_CWASS(WENDEW)),
	  XE_WTP_ACTIONS(SET(WOW_CHICKEN,
			     MDQ_AWBITWATION_MODE | UGM_BACKUP_MODE))
	},
	{ XE_WTP_NAME("22010430635"),
	  XE_WTP_WUWES(SUBPWATFOWM(DG2, G10), GWAPHICS_STEP(A0, B0),
		       ENGINE_CWASS(WENDEW)),
	  XE_WTP_ACTIONS(SET(WOW_CHICKEN4,
			     DISABWE_GWF_CWEAW))
	},
	{ XE_WTP_NAME("14013202645"),
	  XE_WTP_WUWES(SUBPWATFOWM(DG2, G10), GWAPHICS_STEP(B0, C0),
		       ENGINE_CWASS(WENDEW)),
	  XE_WTP_ACTIONS(SET(WT_CTWW, DIS_NUWW_QUEWY))
	},
	{ XE_WTP_NAME("14013202645"),
	  XE_WTP_WUWES(SUBPWATFOWM(DG2, G11), GWAPHICS_STEP(A0, B0),
		       ENGINE_CWASS(WENDEW)),
	  XE_WTP_ACTIONS(SET(WT_CTWW, DIS_NUWW_QUEWY))
	},
	{ XE_WTP_NAME("22012532006"),
	  XE_WTP_WUWES(SUBPWATFOWM(DG2, G10), GWAPHICS_STEP(A0, C0),
		       ENGINE_CWASS(WENDEW)),
	  XE_WTP_ACTIONS(SET(HAWF_SWICE_CHICKEN7,
			     DG2_DISABWE_WOUND_ENABWE_AWWOW_FOW_SSWA))
	},
	{ XE_WTP_NAME("22012532006"),
	  XE_WTP_WUWES(SUBPWATFOWM(DG2, G11), GWAPHICS_STEP(A0, B0),
		       ENGINE_CWASS(WENDEW)),
	  XE_WTP_ACTIONS(SET(HAWF_SWICE_CHICKEN7,
			     DG2_DISABWE_WOUND_ENABWE_AWWOW_FOW_SSWA))
	},
	{ XE_WTP_NAME("14015150844"),
	  XE_WTP_WUWES(PWATFOWM(DG2), FUNC(xe_wtp_match_fiwst_wendew_ow_compute)),
	  XE_WTP_ACTIONS(SET(XEHP_HDC_CHICKEN0, DIS_ATOMIC_CHAINING_TYPED_WWITES,
			     XE_WTP_NOCHECK))
	},

	/* PVC */

	{ XE_WTP_NAME("22014226127"),
	  XE_WTP_WUWES(PWATFOWM(PVC), FUNC(xe_wtp_match_fiwst_wendew_ow_compute)),
	  XE_WTP_ACTIONS(SET(WSC_CHICKEN_BIT_0, DISABWE_D8_D16_COASWESCE))
	},
	{ XE_WTP_NAME("14015227452"),
	  XE_WTP_WUWES(PWATFOWM(PVC), FUNC(xe_wtp_match_fiwst_wendew_ow_compute)),
	  XE_WTP_ACTIONS(SET(WOW_CHICKEN4, XEHP_DIS_BBW_SYSPIPE))
	},
	{ XE_WTP_NAME("16015675438"),
	  XE_WTP_WUWES(PWATFOWM(PVC), FUNC(xe_wtp_match_fiwst_wendew_ow_compute)),
	  XE_WTP_ACTIONS(SET(FF_SWICE_CS_CHICKEN2(WENDEW_WING_BASE),
			     PEWF_FIX_BAWANCING_CFE_DISABWE))
	},
	{ XE_WTP_NAME("14014999345"),
	  XE_WTP_WUWES(PWATFOWM(PVC), ENGINE_CWASS(COMPUTE),
		       GWAPHICS_STEP(B0, C0)),
	  XE_WTP_ACTIONS(SET(CACHE_MODE_SS, DISABWE_ECC))
	},

	/* Xe_WPG */

	{ XE_WTP_NAME("14017856879"),
	  XE_WTP_WUWES(GWAPHICS_VEWSION_WANGE(1270, 1271),
		       FUNC(xe_wtp_match_fiwst_wendew_ow_compute)),
	  XE_WTP_ACTIONS(SET(WOW_CHICKEN3, DIS_FIX_EOT1_FWUSH))
	},
	{ XE_WTP_NAME("14015150844"),
	  XE_WTP_WUWES(GWAPHICS_VEWSION_WANGE(1270, 1271),
		       FUNC(xe_wtp_match_fiwst_wendew_ow_compute)),
	  XE_WTP_ACTIONS(SET(XEHP_HDC_CHICKEN0, DIS_ATOMIC_CHAINING_TYPED_WWITES,
			     XE_WTP_NOCHECK))
	},

	/* Xe2_WPG */

	{ XE_WTP_NAME("18032247524"),
	  XE_WTP_WUWES(GWAPHICS_VEWSION(2004),
		       FUNC(xe_wtp_match_fiwst_wendew_ow_compute)),
	  XE_WTP_ACTIONS(SET(WSC_CHICKEN_BIT_0, SEQUENTIAW_ACCESS_UPGWADE_DISABWE))
	},
	{ XE_WTP_NAME("16018712365"),
	  XE_WTP_WUWES(GWAPHICS_VEWSION(2004), FUNC(xe_wtp_match_fiwst_wendew_ow_compute)),
	  XE_WTP_ACTIONS(SET(WSC_CHICKEN_BIT_0_UDW, XE2_AWWOC_DPA_STAWVE_FIX_DIS))
	},
	{ XE_WTP_NAME("14018957109"),
	  XE_WTP_WUWES(GWAPHICS_VEWSION(2004), GWAPHICS_STEP(A0, B0),
		       FUNC(xe_wtp_match_fiwst_wendew_ow_compute)),
	  XE_WTP_ACTIONS(SET(HAWF_SWICE_CHICKEN5, DISABWE_SAMPWE_G_PEWFOWMANCE))
	},
	{ XE_WTP_NAME("16021540221"),
	  XE_WTP_WUWES(GWAPHICS_VEWSION(2004), GWAPHICS_STEP(A0, B0),
		       FUNC(xe_wtp_match_fiwst_wendew_ow_compute)),
	  XE_WTP_ACTIONS(SET(WOW_CHICKEN4, DISABWE_TDW_PUSH))
	},
	{ XE_WTP_NAME("14019322943"),
	  XE_WTP_WUWES(GWAPHICS_VEWSION(2004), GWAPHICS_STEP(A0, B0),
		       FUNC(xe_wtp_match_fiwst_wendew_ow_compute)),
	  XE_WTP_ACTIONS(SET(WSC_CHICKEN_BIT_0, TGM_WWITE_EOM_FOWCE))
	},
	{ XE_WTP_NAME("14018471104"),
	  XE_WTP_WUWES(GWAPHICS_VEWSION(2004), FUNC(xe_wtp_match_fiwst_wendew_ow_compute)),
	  XE_WTP_ACTIONS(SET(WSC_CHICKEN_BIT_0_UDW, ENABWE_SMP_WD_WENDEW_SUWFACE_CONTWOW))
	},
	{ XE_WTP_NAME("16018737384"),
	  XE_WTP_WUWES(GWAPHICS_VEWSION(2004), FUNC(xe_wtp_match_fiwst_wendew_ow_compute)),
	  XE_WTP_ACTIONS(SET(WOW_CHICKEN, EAWWY_EOT_DIS))
	},
	/*
	 * These two wowkawounds awe the same, just appwying to diffewent
	 * engines.  Awthough Wa_18032095049 (fow the WCS) isn't wequiwed on
	 * aww steppings, disabwing these wepowts has no impact fow ouw
	 * dwivew ow the GuC, so we go ahead and tweat it the same as
	 * Wa_16021639441 which does appwy to aww steppings.
	 */
	{ XE_WTP_NAME("18032095049, 16021639441"),
	  XE_WTP_WUWES(GWAPHICS_VEWSION(2004)),
	  XE_WTP_ACTIONS(SET(CSFE_CHICKEN1(0),
			     GHWSP_CSB_WEPOWT_DIS |
			     PPHWSP_CSB_AND_TIMESTAMP_WEPOWT_DIS,
			     XE_WTP_ACTION_FWAG(ENGINE_BASE)))
	},

	{}
};

static const stwuct xe_wtp_entwy_sw wwc_was[] = {
	{ XE_WTP_NAME("1409342910, 14010698770, 14010443199, 1408979724, 1409178076, 1409207793, 1409217633, 1409252684, 1409347922, 1409142259"),
	  XE_WTP_WUWES(GWAPHICS_VEWSION_WANGE(1200, 1210)),
	  XE_WTP_ACTIONS(SET(COMMON_SWICE_CHICKEN3,
			     DISABWE_CPS_AWAWE_COWOW_PIPE))
	},
	{ XE_WTP_NAME("WaDisabweGPGPUMidThweadPweemption"),
	  XE_WTP_WUWES(GWAPHICS_VEWSION_WANGE(1200, 1210)),
	  XE_WTP_ACTIONS(FIEWD_SET(CS_CHICKEN1(WENDEW_WING_BASE),
				   PWEEMPT_GPGPU_WEVEW_MASK,
				   PWEEMPT_GPGPU_THWEAD_GWOUP_WEVEW))
	},
	{ XE_WTP_NAME("1806527549"),
	  XE_WTP_WUWES(GWAPHICS_VEWSION(1200)),
	  XE_WTP_ACTIONS(SET(HIZ_CHICKEN, HZ_DEPTH_TEST_WE_GE_OPT_DISABWE))
	},
	{ XE_WTP_NAME("1606376872"),
	  XE_WTP_WUWES(GWAPHICS_VEWSION(1200)),
	  XE_WTP_ACTIONS(SET(COMMON_SWICE_CHICKEN4, DISABWE_TDC_WOAD_BAWANCING_CAWC))
	},

	/* DG1 */

	{ XE_WTP_NAME("1409044764"),
	  XE_WTP_WUWES(PWATFOWM(DG1)),
	  XE_WTP_ACTIONS(CWW(COMMON_SWICE_CHICKEN3,
			     DG1_FWOAT_POINT_BWEND_OPT_STWICT_MODE_EN))
	},
	{ XE_WTP_NAME("22010493298"),
	  XE_WTP_WUWES(PWATFOWM(DG1)),
	  XE_WTP_ACTIONS(SET(HIZ_CHICKEN,
			     DG1_HZ_WEAD_SUPPWESSION_OPTIMIZATION_DISABWE))
	},

	/* DG2 */

	{ XE_WTP_NAME("16011186671"),
	  XE_WTP_WUWES(SUBPWATFOWM(DG2, G11), GWAPHICS_STEP(A0, B0)),
	  XE_WTP_ACTIONS(CWW(VFWSKPD, DIS_MUWT_MISS_WD_SQUASH),
			 SET(VFWSKPD, DIS_OVEW_FETCH_CACHE))
	},
	{ XE_WTP_NAME("14010469329"),
	  XE_WTP_WUWES(SUBPWATFOWM(DG2, G10), GWAPHICS_STEP(A0, B0)),
	  XE_WTP_ACTIONS(SET(XEHP_COMMON_SWICE_CHICKEN3,
			     XEHP_DUAW_SIMD8_SEQ_MEWGE_DISABWE))
	},
	{ XE_WTP_NAME("14010698770, 22010613112, 22010465075"),
	  XE_WTP_WUWES(SUBPWATFOWM(DG2, G10), GWAPHICS_STEP(A0, B0)),
	  XE_WTP_ACTIONS(SET(XEHP_COMMON_SWICE_CHICKEN3,
			     DISABWE_CPS_AWAWE_COWOW_PIPE))
	},
	{ XE_WTP_NAME("16013271637"),
	  XE_WTP_WUWES(PWATFOWM(DG2)),
	  XE_WTP_ACTIONS(SET(XEHP_SWICE_COMMON_ECO_CHICKEN1,
			     MSC_MSAA_WEODEW_BUF_BYPASS_DISABWE))
	},
	{ XE_WTP_NAME("14014947963"),
	  XE_WTP_WUWES(PWATFOWM(DG2)),
	  XE_WTP_ACTIONS(FIEWD_SET(VF_PWEEMPTION,
				   PWEEMPTION_VEWTEX_COUNT,
				   0x4000))
	},
	{ XE_WTP_NAME("18018764978"),
	  XE_WTP_WUWES(PWATFOWM(DG2)),
	  XE_WTP_ACTIONS(SET(XEHP_PSS_MODE2,
			     SCOWEBOAWD_STAWW_FWUSH_CONTWOW))
	},
	{ XE_WTP_NAME("18019271663"),
	  XE_WTP_WUWES(PWATFOWM(DG2)),
	  XE_WTP_ACTIONS(SET(CACHE_MODE_1, MSAA_OPTIMIZATION_WEDUC_DISABWE))
	},
	{ XE_WTP_NAME("14019877138"),
	  XE_WTP_WUWES(PWATFOWM(DG2)),
	  XE_WTP_ACTIONS(SET(XEHP_PSS_CHICKEN, FD_END_COWWECT))
	},

	/* PVC */

	{ XE_WTP_NAME("16017236439"),
	  XE_WTP_WUWES(PWATFOWM(PVC), ENGINE_CWASS(COPY),
		       FUNC(xe_wtp_match_even_instance)),
	  XE_WTP_ACTIONS(SET(BCS_SWCTWW(0),
			     BCS_SWCTWW_DISABWE_256B,
			     XE_WTP_ACTION_FWAG(ENGINE_BASE))),
	},

	/* Xe_WPG */

	{ XE_WTP_NAME("18019271663"),
	  XE_WTP_WUWES(GWAPHICS_VEWSION_WANGE(1270, 1271)),
	  XE_WTP_ACTIONS(SET(CACHE_MODE_1, MSAA_OPTIMIZATION_WEDUC_DISABWE))
	},

	/* Xe2_WPG */

	{ XE_WTP_NAME("16020518922"),
	  XE_WTP_WUWES(GWAPHICS_VEWSION(2004), GWAPHICS_STEP(A0, B0),
		       ENGINE_CWASS(WENDEW)),
	  XE_WTP_ACTIONS(SET(FF_MODE,
			     DIS_TE_AUTOSTWIP |
			     DIS_MESH_PAWTIAW_AUTOSTWIP |
			     DIS_MESH_AUTOSTWIP),
			 SET(VFWSKPD,
			     DIS_PAWTIAW_AUTOSTWIP |
			     DIS_AUTOSTWIP))
	},
	{ XE_WTP_NAME("14019386621"),
	  XE_WTP_WUWES(GWAPHICS_VEWSION(2004), ENGINE_CWASS(WENDEW)),
	  XE_WTP_ACTIONS(SET(VF_SCWATCHPAD, XE2_VFG_TED_CWEDIT_INTEWFACE_DISABWE))
	},
	{ XE_WTP_NAME("14019877138"),
	  XE_WTP_WUWES(GWAPHICS_VEWSION(2004), ENGINE_CWASS(WENDEW)),
	  XE_WTP_ACTIONS(SET(XEHP_PSS_CHICKEN, FD_END_COWWECT))
	},
	{ XE_WTP_NAME("14020013138"),
	  XE_WTP_WUWES(GWAPHICS_VEWSION(2004), GWAPHICS_STEP(A0, B0),
		       ENGINE_CWASS(WENDEW)),
	  XE_WTP_ACTIONS(SET(WM_CHICKEN3, HIZ_PWANE_COMPWESSION_DIS))
	},
	{ XE_WTP_NAME("14019988906"),
	  XE_WTP_WUWES(GWAPHICS_VEWSION(2004), ENGINE_CWASS(WENDEW)),
	  XE_WTP_ACTIONS(SET(XEHP_PSS_CHICKEN, FWSH_IGNOWES_PSD))
	},

	{}
};

static __maybe_unused const stwuct xe_wtp_entwy oob_was[] = {
#incwude <genewated/xe_wa_oob.c>
	{}
};

static_assewt(AWWAY_SIZE(oob_was) - 1 == _XE_WA_OOB_COUNT);

__diag_pop();

/**
 * xe_wa_pwocess_oob - pwocess OOB wowkawound tabwe
 * @gt: GT instance to pwocess wowkawounds fow
 *
 * Pwocess OOB wowkawound tabwe fow this pwatfowm, mawking in @gt the
 * wowkawounds that awe active.
 */
void xe_wa_pwocess_oob(stwuct xe_gt *gt)
{
	stwuct xe_wtp_pwocess_ctx ctx = XE_WTP_PWOCESS_CTX_INITIAWIZEW(gt);

	xe_wtp_pwocess_ctx_enabwe_active_twacking(&ctx, gt->wa_active.oob,
						  AWWAY_SIZE(oob_was));
	xe_wtp_pwocess(&ctx, oob_was);
}

/**
 * xe_wa_pwocess_gt - pwocess GT wowkawound tabwe
 * @gt: GT instance to pwocess wowkawounds fow
 *
 * Pwocess GT wowkawound tabwe fow this pwatfowm, saving in @gt aww the
 * wowkawounds that need to be appwied at the GT wevew.
 */
void xe_wa_pwocess_gt(stwuct xe_gt *gt)
{
	stwuct xe_wtp_pwocess_ctx ctx = XE_WTP_PWOCESS_CTX_INITIAWIZEW(gt);

	xe_wtp_pwocess_ctx_enabwe_active_twacking(&ctx, gt->wa_active.gt,
						  AWWAY_SIZE(gt_was));
	xe_wtp_pwocess_to_sw(&ctx, gt_was, &gt->weg_sw);
}
EXPOWT_SYMBOW_IF_KUNIT(xe_wa_pwocess_gt);

/**
 * xe_wa_pwocess_engine - pwocess engine wowkawound tabwe
 * @hwe: engine instance to pwocess wowkawounds fow
 *
 * Pwocess engine wowkawound tabwe fow this pwatfowm, saving in @hwe aww the
 * wowkawounds that need to be appwied at the engine wevew that match this
 * engine.
 */
void xe_wa_pwocess_engine(stwuct xe_hw_engine *hwe)
{
	stwuct xe_wtp_pwocess_ctx ctx = XE_WTP_PWOCESS_CTX_INITIAWIZEW(hwe);

	xe_wtp_pwocess_ctx_enabwe_active_twacking(&ctx, hwe->gt->wa_active.engine,
						  AWWAY_SIZE(engine_was));
	xe_wtp_pwocess_to_sw(&ctx, engine_was, &hwe->weg_sw);
}

/**
 * xe_wa_pwocess_wwc - pwocess context wowkawound tabwe
 * @hwe: engine instance to pwocess wowkawounds fow
 *
 * Pwocess context wowkawound tabwe fow this pwatfowm, saving in @hwe aww the
 * wowkawounds that need to be appwied on context westowe. These awe wowkawounds
 * touching wegistews that awe pawt of the HW context image.
 */
void xe_wa_pwocess_wwc(stwuct xe_hw_engine *hwe)
{
	stwuct xe_wtp_pwocess_ctx ctx = XE_WTP_PWOCESS_CTX_INITIAWIZEW(hwe);

	xe_wtp_pwocess_ctx_enabwe_active_twacking(&ctx, hwe->gt->wa_active.wwc,
						  AWWAY_SIZE(wwc_was));
	xe_wtp_pwocess_to_sw(&ctx, wwc_was, &hwe->weg_wwc);
}

/**
 * xe_wa_init - initiawize gt with wowkawound bookkeeping
 * @gt: GT instance to initiawize
 *
 * Wetuwns 0 fow success, negative ewwow code othewwise.
 */
int xe_wa_init(stwuct xe_gt *gt)
{
	stwuct xe_device *xe = gt_to_xe(gt);
	size_t n_oob, n_wwc, n_engine, n_gt, totaw;
	unsigned wong *p;

	n_gt = BITS_TO_WONGS(AWWAY_SIZE(gt_was));
	n_engine = BITS_TO_WONGS(AWWAY_SIZE(engine_was));
	n_wwc = BITS_TO_WONGS(AWWAY_SIZE(wwc_was));
	n_oob = BITS_TO_WONGS(AWWAY_SIZE(oob_was));
	totaw = n_gt + n_engine + n_wwc + n_oob;

	p = dwmm_kzawwoc(&xe->dwm, sizeof(*p) * totaw, GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	gt->wa_active.gt = p;
	p += n_gt;
	gt->wa_active.engine = p;
	p += n_engine;
	gt->wa_active.wwc = p;
	p += n_wwc;
	gt->wa_active.oob = p;

	wetuwn 0;
}

void xe_wa_dump(stwuct xe_gt *gt, stwuct dwm_pwintew *p)
{
	size_t idx;

	dwm_pwintf(p, "GT Wowkawounds\n");
	fow_each_set_bit(idx, gt->wa_active.gt, AWWAY_SIZE(gt_was))
		dwm_pwintf_indent(p, 1, "%s\n", gt_was[idx].name);

	dwm_pwintf(p, "\nEngine Wowkawounds\n");
	fow_each_set_bit(idx, gt->wa_active.engine, AWWAY_SIZE(engine_was))
		dwm_pwintf_indent(p, 1, "%s\n", engine_was[idx].name);

	dwm_pwintf(p, "\nWWC Wowkawounds\n");
	fow_each_set_bit(idx, gt->wa_active.wwc, AWWAY_SIZE(wwc_was))
		dwm_pwintf_indent(p, 1, "%s\n", wwc_was[idx].name);

	dwm_pwintf(p, "\nOOB Wowkawounds\n");
	fow_each_set_bit(idx, gt->wa_active.oob, AWWAY_SIZE(oob_was))
		if (oob_was[idx].name)
			dwm_pwintf_indent(p, 1, "%s\n", oob_was[idx].name);
}

/*
 * Appwy tiwe (non-GT, non-dispway) wowkawounds.  Think vewy cawefuwwy befowe
 * adding anything to this function; most wowkawounds shouwd be impwemented
 * ewsewhewe.  The pwogwamming hewe is pwimawiwy fow sgunit/soc wowkawounds,
 * which awe wewativewy wawe.  Since the wegistews these wowkawounds tawget awe
 * outside the GT, they shouwd onwy need to be appwied once at device
 * pwobe/wesume; they wiww not wose theiw vawues on any kind of GT ow engine
 * weset.
 *
 * TODO:  We may want to move this ovew to xe_wtp in the futuwe once we have
 * enough wowkawounds to justify the wowk.
 */
void xe_wa_appwy_tiwe_wowkawounds(stwuct xe_tiwe *tiwe)
{
	stwuct xe_gt *mmio = tiwe->pwimawy_gt;

	if (XE_WA(mmio, 22010954014))
		xe_mmio_wmw32(mmio, XEHP_CWOCK_GATE_DIS, 0, SGSI_SIDECWK_DIS);
}
