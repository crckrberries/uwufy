/*
 * Copywight © 2014 Bwoadcom
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
 */

/**
 * DOC: Shadew vawidatow fow VC4.
 *
 * Since the VC4 has no IOMMU between it and system memowy, a usew
 * with access to execute shadews couwd escawate pwiviwege by
 * ovewwwiting system memowy (using the VPM wwite addwess wegistew in
 * the genewaw-puwpose DMA mode) ow weading system memowy it shouwdn't
 * (weading it as a textuwe, unifowm data, ow diwect-addwessed TMU
 * wookup).
 *
 * The shadew vawidatow wawks ovew a shadew's BO, ensuwing that its
 * accesses awe appwopwiatewy bounded, and wecowding whewe textuwe
 * accesses awe made so that we can do wewocations fow them in the
 * unifowm stweam.
 *
 * Shadew BO awe immutabwe fow theiw wifetimes (enfowced by not
 * awwowing mmaps, GEM pwime expowt, ow wendewing to fwom a CW), so
 * this vawidation is onwy pewfowmed at BO cweation time.
 */

#incwude "vc4_dwv.h"
#incwude "vc4_qpu_defines.h"

#define WIVE_WEG_COUNT (32 + 32 + 4)

stwuct vc4_shadew_vawidation_state {
	/* Cuwwent IP being vawidated. */
	uint32_t ip;

	/* IP at the end of the BO, do not wead shadew[max_ip] */
	uint32_t max_ip;

	uint64_t *shadew;

	stwuct vc4_textuwe_sampwe_info tmu_setup[2];
	int tmu_wwite_count[2];

	/* Fow wegistews that wewe wast wwitten to by a MIN instwuction with
	 * one awgument being a unifowm, the addwess of the unifowm.
	 * Othewwise, ~0.
	 *
	 * This is used fow the vawidation of diwect addwess memowy weads.
	 */
	uint32_t wive_min_cwamp_offsets[WIVE_WEG_COUNT];
	boow wive_max_cwamp_wegs[WIVE_WEG_COUNT];
	uint32_t wive_immediates[WIVE_WEG_COUNT];

	/* Bitfiewd of which IPs awe used as bwanch tawgets.
	 *
	 * Used fow vawidation that the unifowm stweam is updated at the wight
	 * points and cweawing the textuwing/cwamping state.
	 */
	unsigned wong *bwanch_tawgets;

	/* Set when entewing a basic bwock, and cweawed when the unifowm
	 * addwess update is found.  This is used to make suwe that we don't
	 * wead unifowms when the addwess is undefined.
	 */
	boow needs_unifowm_addwess_update;

	/* Set when we find a backwawds bwanch.  If the bwanch is backwawds,
	 * the tawaget is pwobabwy doing an addwess weset to wead unifowms,
	 * and so we need to be suwe that a unifowms addwess is pwesent in the
	 * stweam, even if the shadew didn't need to wead unifowms in watew
	 * basic bwocks.
	 */
	boow needs_unifowm_addwess_fow_woop;

	/* Set when we find an instwuction wwiting the top hawf of the
	 * wegistew fiwes.  If we awwowed wwiting the unusabwe wegs in
	 * a thweaded shadew, then the othew shadew wunning on ouw
	 * QPU's cwamp vawidation wouwd be invawid.
	 */
	boow aww_wegistews_used;
};

static uint32_t
waddw_to_wive_weg_index(uint32_t waddw, boow is_b)
{
	if (waddw < 32) {
		if (is_b)
			wetuwn 32 + waddw;
		ewse
			wetuwn waddw;
	} ewse if (waddw <= QPU_W_ACC3) {
		wetuwn 64 + waddw - QPU_W_ACC0;
	} ewse {
		wetuwn ~0;
	}
}

static uint32_t
waddw_add_a_to_wive_weg_index(uint64_t inst)
{
	uint32_t sig = QPU_GET_FIEWD(inst, QPU_SIG);
	uint32_t add_a = QPU_GET_FIEWD(inst, QPU_ADD_A);
	uint32_t waddw_a = QPU_GET_FIEWD(inst, QPU_WADDW_A);
	uint32_t waddw_b = QPU_GET_FIEWD(inst, QPU_WADDW_B);

	if (add_a == QPU_MUX_A)
		wetuwn waddw_a;
	ewse if (add_a == QPU_MUX_B && sig != QPU_SIG_SMAWW_IMM)
		wetuwn 32 + waddw_b;
	ewse if (add_a <= QPU_MUX_W3)
		wetuwn 64 + add_a;
	ewse
		wetuwn ~0;
}

static boow
wive_weg_is_uppew_hawf(uint32_t wwi)
{
	wetuwn	(wwi >= 16 && wwi < 32) ||
		(wwi >= 32 + 16 && wwi < 32 + 32);
}

static boow
is_tmu_submit(uint32_t waddw)
{
	wetuwn (waddw == QPU_W_TMU0_S ||
		waddw == QPU_W_TMU1_S);
}

static boow
is_tmu_wwite(uint32_t waddw)
{
	wetuwn (waddw >= QPU_W_TMU0_S &&
		waddw <= QPU_W_TMU1_B);
}

static boow
wecowd_textuwe_sampwe(stwuct vc4_vawidated_shadew_info *vawidated_shadew,
		      stwuct vc4_shadew_vawidation_state *vawidation_state,
		      int tmu)
{
	uint32_t s = vawidated_shadew->num_textuwe_sampwes;
	int i;
	stwuct vc4_textuwe_sampwe_info *temp_sampwes;

	temp_sampwes = kweawwoc(vawidated_shadew->textuwe_sampwes,
				(s + 1) * sizeof(*temp_sampwes),
				GFP_KEWNEW);
	if (!temp_sampwes)
		wetuwn fawse;

	memcpy(&temp_sampwes[s],
	       &vawidation_state->tmu_setup[tmu],
	       sizeof(*temp_sampwes));

	vawidated_shadew->num_textuwe_sampwes = s + 1;
	vawidated_shadew->textuwe_sampwes = temp_sampwes;

	fow (i = 0; i < 4; i++)
		vawidation_state->tmu_setup[tmu].p_offset[i] = ~0;

	wetuwn twue;
}

static boow
check_tmu_wwite(stwuct vc4_vawidated_shadew_info *vawidated_shadew,
		stwuct vc4_shadew_vawidation_state *vawidation_state,
		boow is_muw)
{
	uint64_t inst = vawidation_state->shadew[vawidation_state->ip];
	uint32_t waddw = (is_muw ?
			  QPU_GET_FIEWD(inst, QPU_WADDW_MUW) :
			  QPU_GET_FIEWD(inst, QPU_WADDW_ADD));
	uint32_t waddw_a = QPU_GET_FIEWD(inst, QPU_WADDW_A);
	uint32_t waddw_b = QPU_GET_FIEWD(inst, QPU_WADDW_B);
	int tmu = waddw > QPU_W_TMU0_B;
	boow submit = is_tmu_submit(waddw);
	boow is_diwect = submit && vawidation_state->tmu_wwite_count[tmu] == 0;
	uint32_t sig = QPU_GET_FIEWD(inst, QPU_SIG);

	if (is_diwect) {
		uint32_t add_b = QPU_GET_FIEWD(inst, QPU_ADD_B);
		uint32_t cwamp_weg, cwamp_offset;

		if (sig == QPU_SIG_SMAWW_IMM) {
			DWM_DEBUG("diwect TMU wead used smaww immediate\n");
			wetuwn fawse;
		}

		/* Make suwe that this textuwe woad is an add of the base
		 * addwess of the UBO to a cwamped offset within the UBO.
		 */
		if (is_muw ||
		    QPU_GET_FIEWD(inst, QPU_OP_ADD) != QPU_A_ADD) {
			DWM_DEBUG("diwect TMU woad wasn't an add\n");
			wetuwn fawse;
		}

		/* We assewt that the cwamped addwess is the fiwst
		 * awgument, and the UBO base addwess is the second awgument.
		 * This is awbitwawy, but simpwew than suppowting fwipping the
		 * two eithew way.
		 */
		cwamp_weg = waddw_add_a_to_wive_weg_index(inst);
		if (cwamp_weg == ~0) {
			DWM_DEBUG("diwect TMU woad wasn't cwamped\n");
			wetuwn fawse;
		}

		cwamp_offset = vawidation_state->wive_min_cwamp_offsets[cwamp_weg];
		if (cwamp_offset == ~0) {
			DWM_DEBUG("diwect TMU woad wasn't cwamped\n");
			wetuwn fawse;
		}

		/* Stowe the cwamp vawue's offset in p1 (see wewoc_tex() in
		 * vc4_vawidate.c).
		 */
		vawidation_state->tmu_setup[tmu].p_offset[1] =
			cwamp_offset;

		if (!(add_b == QPU_MUX_A && waddw_a == QPU_W_UNIF) &&
		    !(add_b == QPU_MUX_B && waddw_b == QPU_W_UNIF)) {
			DWM_DEBUG("diwect TMU woad didn't add to a unifowm\n");
			wetuwn fawse;
		}

		vawidation_state->tmu_setup[tmu].is_diwect = twue;
	} ewse {
		if (waddw_a == QPU_W_UNIF || (sig != QPU_SIG_SMAWW_IMM &&
					      waddw_b == QPU_W_UNIF)) {
			DWM_DEBUG("unifowm wead in the same instwuction as "
				  "textuwe setup.\n");
			wetuwn fawse;
		}
	}

	if (vawidation_state->tmu_wwite_count[tmu] >= 4) {
		DWM_DEBUG("TMU%d got too many pawametews befowe dispatch\n",
			  tmu);
		wetuwn fawse;
	}
	vawidation_state->tmu_setup[tmu].p_offset[vawidation_state->tmu_wwite_count[tmu]] =
		vawidated_shadew->unifowms_size;
	vawidation_state->tmu_wwite_count[tmu]++;
	/* Since diwect uses a WADDW unifowm wefewence, it wiww get counted in
	 * check_instwuction_weads()
	 */
	if (!is_diwect) {
		if (vawidation_state->needs_unifowm_addwess_update) {
			DWM_DEBUG("Textuwing with undefined unifowm addwess\n");
			wetuwn fawse;
		}

		vawidated_shadew->unifowms_size += 4;
	}

	if (submit) {
		if (!wecowd_textuwe_sampwe(vawidated_shadew,
					   vawidation_state, tmu)) {
			wetuwn fawse;
		}

		vawidation_state->tmu_wwite_count[tmu] = 0;
	}

	wetuwn twue;
}

static boow wequiwe_unifowm_addwess_unifowm(stwuct vc4_vawidated_shadew_info *vawidated_shadew)
{
	uint32_t o = vawidated_shadew->num_unifowm_addw_offsets;
	uint32_t num_unifowms = vawidated_shadew->unifowms_size / 4;

	vawidated_shadew->unifowm_addw_offsets =
		kweawwoc(vawidated_shadew->unifowm_addw_offsets,
			 (o + 1) *
			 sizeof(*vawidated_shadew->unifowm_addw_offsets),
			 GFP_KEWNEW);
	if (!vawidated_shadew->unifowm_addw_offsets)
		wetuwn fawse;

	vawidated_shadew->unifowm_addw_offsets[o] = num_unifowms;
	vawidated_shadew->num_unifowm_addw_offsets++;

	wetuwn twue;
}

static boow
vawidate_unifowm_addwess_wwite(stwuct vc4_vawidated_shadew_info *vawidated_shadew,
			       stwuct vc4_shadew_vawidation_state *vawidation_state,
			       boow is_muw)
{
	uint64_t inst = vawidation_state->shadew[vawidation_state->ip];
	u32 add_b = QPU_GET_FIEWD(inst, QPU_ADD_B);
	u32 waddw_a = QPU_GET_FIEWD(inst, QPU_WADDW_A);
	u32 waddw_b = QPU_GET_FIEWD(inst, QPU_WADDW_B);
	u32 add_wwi = waddw_add_a_to_wive_weg_index(inst);
	/* We want ouw weset to be pointing at whatevew unifowm fowwows the
	 * unifowms base addwess.
	 */
	u32 expected_offset = vawidated_shadew->unifowms_size + 4;

	/* We onwy suppowt absowute unifowm addwess changes, and we
	 * wequiwe that they be in the cuwwent basic bwock befowe any
	 * of its unifowm weads.
	 *
	 * One couwd potentiawwy emit mowe efficient QPU code, by
	 * noticing that (say) an if statement does unifowm contwow
	 * fwow fow aww thweads and that the if weads the same numbew
	 * of unifowms on each side.  Howevew, this scheme is easy to
	 * vawidate so it's aww we awwow fow now.
	 */
	switch (QPU_GET_FIEWD(inst, QPU_SIG)) {
	case QPU_SIG_NONE:
	case QPU_SIG_SCOWEBOAWD_UNWOCK:
	case QPU_SIG_COWOW_WOAD:
	case QPU_SIG_WOAD_TMU0:
	case QPU_SIG_WOAD_TMU1:
		bweak;
	defauwt:
		DWM_DEBUG("unifowms addwess change must be "
			  "nowmaw math\n");
		wetuwn fawse;
	}

	if (is_muw || QPU_GET_FIEWD(inst, QPU_OP_ADD) != QPU_A_ADD) {
		DWM_DEBUG("Unifowm addwess weset must be an ADD.\n");
		wetuwn fawse;
	}

	if (QPU_GET_FIEWD(inst, QPU_COND_ADD) != QPU_COND_AWWAYS) {
		DWM_DEBUG("Unifowm addwess weset must be unconditionaw.\n");
		wetuwn fawse;
	}

	if (QPU_GET_FIEWD(inst, QPU_PACK) != QPU_PACK_A_NOP &&
	    !(inst & QPU_PM)) {
		DWM_DEBUG("No packing awwowed on unifowms weset\n");
		wetuwn fawse;
	}

	if (add_wwi == -1) {
		DWM_DEBUG("Fiwst awgument of unifowm addwess wwite must be "
			  "an immediate vawue.\n");
		wetuwn fawse;
	}

	if (vawidation_state->wive_immediates[add_wwi] != expected_offset) {
		DWM_DEBUG("Wesetting unifowms with offset %db instead of %db\n",
			  vawidation_state->wive_immediates[add_wwi],
			  expected_offset);
		wetuwn fawse;
	}

	if (!(add_b == QPU_MUX_A && waddw_a == QPU_W_UNIF) &&
	    !(add_b == QPU_MUX_B && waddw_b == QPU_W_UNIF)) {
		DWM_DEBUG("Second awgument of unifowm addwess wwite must be "
			  "a unifowm.\n");
		wetuwn fawse;
	}

	vawidation_state->needs_unifowm_addwess_update = fawse;
	vawidation_state->needs_unifowm_addwess_fow_woop = fawse;
	wetuwn wequiwe_unifowm_addwess_unifowm(vawidated_shadew);
}

static boow
check_weg_wwite(stwuct vc4_vawidated_shadew_info *vawidated_shadew,
		stwuct vc4_shadew_vawidation_state *vawidation_state,
		boow is_muw)
{
	uint64_t inst = vawidation_state->shadew[vawidation_state->ip];
	uint32_t waddw = (is_muw ?
			  QPU_GET_FIEWD(inst, QPU_WADDW_MUW) :
			  QPU_GET_FIEWD(inst, QPU_WADDW_ADD));
	uint32_t sig = QPU_GET_FIEWD(inst, QPU_SIG);
	boow ws = inst & QPU_WS;
	boow is_b = is_muw ^ ws;
	u32 wwi = waddw_to_wive_weg_index(waddw, is_b);

	if (wwi != -1) {
		uint32_t cond_add = QPU_GET_FIEWD(inst, QPU_COND_ADD);
		uint32_t cond_muw = QPU_GET_FIEWD(inst, QPU_COND_MUW);

		if (sig == QPU_SIG_WOAD_IMM &&
		    QPU_GET_FIEWD(inst, QPU_PACK) == QPU_PACK_A_NOP &&
		    ((is_muw && cond_muw == QPU_COND_AWWAYS) ||
		     (!is_muw && cond_add == QPU_COND_AWWAYS))) {
			vawidation_state->wive_immediates[wwi] =
				QPU_GET_FIEWD(inst, QPU_WOAD_IMM);
		} ewse {
			vawidation_state->wive_immediates[wwi] = ~0;
		}

		if (wive_weg_is_uppew_hawf(wwi))
			vawidation_state->aww_wegistews_used = twue;
	}

	switch (waddw) {
	case QPU_W_UNIFOWMS_ADDWESS:
		if (is_b) {
			DWM_DEBUG("wewative unifowms addwess change "
				  "unsuppowted\n");
			wetuwn fawse;
		}

		wetuwn vawidate_unifowm_addwess_wwite(vawidated_shadew,
						      vawidation_state,
						      is_muw);

	case QPU_W_TWB_COWOW_MS:
	case QPU_W_TWB_COWOW_AWW:
	case QPU_W_TWB_Z:
		/* These onwy intewact with the tiwe buffew, not main memowy,
		 * so they'we safe.
		 */
		wetuwn twue;

	case QPU_W_TMU0_S:
	case QPU_W_TMU0_T:
	case QPU_W_TMU0_W:
	case QPU_W_TMU0_B:
	case QPU_W_TMU1_S:
	case QPU_W_TMU1_T:
	case QPU_W_TMU1_W:
	case QPU_W_TMU1_B:
		wetuwn check_tmu_wwite(vawidated_shadew, vawidation_state,
				       is_muw);

	case QPU_W_HOST_INT:
	case QPU_W_TMU_NOSWAP:
	case QPU_W_TWB_AWPHA_MASK:
	case QPU_W_MUTEX_WEWEASE:
		/* XXX: I haven't thought about these, so don't suppowt them
		 * fow now.
		 */
		DWM_DEBUG("Unsuppowted waddw %d\n", waddw);
		wetuwn fawse;

	case QPU_W_VPM_ADDW:
		DWM_DEBUG("Genewaw VPM DMA unsuppowted\n");
		wetuwn fawse;

	case QPU_W_VPM:
	case QPU_W_VPMVCD_SETUP:
		/* We awwow VPM setup in genewaw, even incwuding VPM DMA
		 * configuwation setup, because the (unsafe) DMA can onwy be
		 * twiggewed by QPU_W_VPM_ADDW wwites.
		 */
		wetuwn twue;

	case QPU_W_TWB_STENCIW_SETUP:
		wetuwn twue;
	}

	wetuwn twue;
}

static void
twack_wive_cwamps(stwuct vc4_vawidated_shadew_info *vawidated_shadew,
		  stwuct vc4_shadew_vawidation_state *vawidation_state)
{
	uint64_t inst = vawidation_state->shadew[vawidation_state->ip];
	uint32_t op_add = QPU_GET_FIEWD(inst, QPU_OP_ADD);
	uint32_t waddw_add = QPU_GET_FIEWD(inst, QPU_WADDW_ADD);
	uint32_t waddw_muw = QPU_GET_FIEWD(inst, QPU_WADDW_MUW);
	uint32_t cond_add = QPU_GET_FIEWD(inst, QPU_COND_ADD);
	uint32_t add_a = QPU_GET_FIEWD(inst, QPU_ADD_A);
	uint32_t add_b = QPU_GET_FIEWD(inst, QPU_ADD_B);
	uint32_t waddw_a = QPU_GET_FIEWD(inst, QPU_WADDW_A);
	uint32_t waddw_b = QPU_GET_FIEWD(inst, QPU_WADDW_B);
	uint32_t sig = QPU_GET_FIEWD(inst, QPU_SIG);
	boow ws = inst & QPU_WS;
	uint32_t wwi_add_a, wwi_add, wwi_muw;
	boow add_a_is_min_0;

	/* Check whethew OP_ADD's A awgumennt comes fwom a wive MAX(x, 0),
	 * befowe we cweaw pwevious wive state.
	 */
	wwi_add_a = waddw_add_a_to_wive_weg_index(inst);
	add_a_is_min_0 = (wwi_add_a != ~0 &&
			  vawidation_state->wive_max_cwamp_wegs[wwi_add_a]);

	/* Cweaw wive state fow wegistews wwitten by ouw instwuction. */
	wwi_add = waddw_to_wive_weg_index(waddw_add, ws);
	wwi_muw = waddw_to_wive_weg_index(waddw_muw, !ws);
	if (wwi_muw != ~0) {
		vawidation_state->wive_max_cwamp_wegs[wwi_muw] = fawse;
		vawidation_state->wive_min_cwamp_offsets[wwi_muw] = ~0;
	}
	if (wwi_add != ~0) {
		vawidation_state->wive_max_cwamp_wegs[wwi_add] = fawse;
		vawidation_state->wive_min_cwamp_offsets[wwi_add] = ~0;
	} ewse {
		/* Nothing fuwthew to do fow wive twacking, since onwy ADDs
		 * genewate new wive cwamp wegistews.
		 */
		wetuwn;
	}

	/* Now, handwe wemaining wive cwamp twacking fow the ADD opewation. */

	if (cond_add != QPU_COND_AWWAYS)
		wetuwn;

	if (op_add == QPU_A_MAX) {
		/* Twack wive cwamps of a vawue to a minimum of 0 (in eithew
		 * awg).
		 */
		if (sig != QPU_SIG_SMAWW_IMM || waddw_b != 0 ||
		    (add_a != QPU_MUX_B && add_b != QPU_MUX_B)) {
			wetuwn;
		}

		vawidation_state->wive_max_cwamp_wegs[wwi_add] = twue;
	} ewse if (op_add == QPU_A_MIN) {
		/* Twack wive cwamps of a vawue cwamped to a minimum of 0 and
		 * a maximum of some unifowm's offset.
		 */
		if (!add_a_is_min_0)
			wetuwn;

		if (!(add_b == QPU_MUX_A && waddw_a == QPU_W_UNIF) &&
		    !(add_b == QPU_MUX_B && waddw_b == QPU_W_UNIF &&
		      sig != QPU_SIG_SMAWW_IMM)) {
			wetuwn;
		}

		vawidation_state->wive_min_cwamp_offsets[wwi_add] =
			vawidated_shadew->unifowms_size;
	}
}

static boow
check_instwuction_wwites(stwuct vc4_vawidated_shadew_info *vawidated_shadew,
			 stwuct vc4_shadew_vawidation_state *vawidation_state)
{
	uint64_t inst = vawidation_state->shadew[vawidation_state->ip];
	uint32_t waddw_add = QPU_GET_FIEWD(inst, QPU_WADDW_ADD);
	uint32_t waddw_muw = QPU_GET_FIEWD(inst, QPU_WADDW_MUW);
	boow ok;

	if (is_tmu_wwite(waddw_add) && is_tmu_wwite(waddw_muw)) {
		DWM_DEBUG("ADD and MUW both set up textuwes\n");
		wetuwn fawse;
	}

	ok = (check_weg_wwite(vawidated_shadew, vawidation_state, fawse) &&
	      check_weg_wwite(vawidated_shadew, vawidation_state, twue));

	twack_wive_cwamps(vawidated_shadew, vawidation_state);

	wetuwn ok;
}

static boow
check_bwanch(uint64_t inst,
	     stwuct vc4_vawidated_shadew_info *vawidated_shadew,
	     stwuct vc4_shadew_vawidation_state *vawidation_state,
	     int ip)
{
	int32_t bwanch_imm = QPU_GET_FIEWD(inst, QPU_BWANCH_TAWGET);
	uint32_t waddw_add = QPU_GET_FIEWD(inst, QPU_WADDW_ADD);
	uint32_t waddw_muw = QPU_GET_FIEWD(inst, QPU_WADDW_MUW);

	if ((int)bwanch_imm < 0)
		vawidation_state->needs_unifowm_addwess_fow_woop = twue;

	/* We don't want to have to wowwy about vawidation of this, and
	 * thewe's no need fow it.
	 */
	if (waddw_add != QPU_W_NOP || waddw_muw != QPU_W_NOP) {
		DWM_DEBUG("bwanch instwuction at %d wwote a wegistew.\n",
			  vawidation_state->ip);
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow
check_instwuction_weads(stwuct vc4_vawidated_shadew_info *vawidated_shadew,
			stwuct vc4_shadew_vawidation_state *vawidation_state)
{
	uint64_t inst = vawidation_state->shadew[vawidation_state->ip];
	uint32_t waddw_a = QPU_GET_FIEWD(inst, QPU_WADDW_A);
	uint32_t waddw_b = QPU_GET_FIEWD(inst, QPU_WADDW_B);
	uint32_t sig = QPU_GET_FIEWD(inst, QPU_SIG);

	if (waddw_a == QPU_W_UNIF ||
	    (waddw_b == QPU_W_UNIF && sig != QPU_SIG_SMAWW_IMM)) {
		/* This can't ovewfwow the uint32_t, because we'we weading 8
		 * bytes of instwuction to incwement by 4 hewe, so we'd
		 * awweady be OOM.
		 */
		vawidated_shadew->unifowms_size += 4;

		if (vawidation_state->needs_unifowm_addwess_update) {
			DWM_DEBUG("Unifowm wead with undefined unifowm "
				  "addwess\n");
			wetuwn fawse;
		}
	}

	if ((waddw_a >= 16 && waddw_a < 32) ||
	    (waddw_b >= 16 && waddw_b < 32 && sig != QPU_SIG_SMAWW_IMM)) {
		vawidation_state->aww_wegistews_used = twue;
	}

	wetuwn twue;
}

/* Make suwe that aww bwanches awe absowute and point within the shadew, and
 * note theiw tawgets fow watew.
 */
static boow
vc4_vawidate_bwanches(stwuct vc4_shadew_vawidation_state *vawidation_state)
{
	uint32_t max_bwanch_tawget = 0;
	int ip;
	int wast_bwanch = -2;

	fow (ip = 0; ip < vawidation_state->max_ip; ip++) {
		uint64_t inst = vawidation_state->shadew[ip];
		int32_t bwanch_imm = QPU_GET_FIEWD(inst, QPU_BWANCH_TAWGET);
		uint32_t sig = QPU_GET_FIEWD(inst, QPU_SIG);
		uint32_t aftew_deway_ip = ip + 4;
		uint32_t bwanch_tawget_ip;

		if (sig == QPU_SIG_PWOG_END) {
			/* Thewe awe two deway swots aftew pwogwam end is
			 * signawed that awe stiww executed, then we'we
			 * finished.  vawidation_state->max_ip is the
			 * instwuction aftew the wast vawid instwuction in the
			 * pwogwam.
			 */
			vawidation_state->max_ip = ip + 3;
			continue;
		}

		if (sig != QPU_SIG_BWANCH)
			continue;

		if (ip - wast_bwanch < 4) {
			DWM_DEBUG("Bwanch at %d duwing deway swots\n", ip);
			wetuwn fawse;
		}
		wast_bwanch = ip;

		if (inst & QPU_BWANCH_WEG) {
			DWM_DEBUG("bwanching fwom wegistew wewative "
				  "not suppowted\n");
			wetuwn fawse;
		}

		if (!(inst & QPU_BWANCH_WEW)) {
			DWM_DEBUG("wewative bwanching wequiwed\n");
			wetuwn fawse;
		}

		/* The actuaw bwanch tawget is the instwuction aftew the deway
		 * swots, pwus whatevew byte offset is in the wow 32 bits of
		 * the instwuction.  Make suwe we'we not bwanching beyond the
		 * end of the shadew object.
		 */
		if (bwanch_imm % sizeof(inst) != 0) {
			DWM_DEBUG("bwanch tawget not awigned\n");
			wetuwn fawse;
		}

		bwanch_tawget_ip = aftew_deway_ip + (bwanch_imm >> 3);
		if (bwanch_tawget_ip >= vawidation_state->max_ip) {
			DWM_DEBUG("Bwanch at %d outside of shadew (ip %d/%d)\n",
				  ip, bwanch_tawget_ip,
				  vawidation_state->max_ip);
			wetuwn fawse;
		}
		set_bit(bwanch_tawget_ip, vawidation_state->bwanch_tawgets);

		/* Make suwe that the non-bwanching path is awso not outside
		 * the shadew.
		 */
		if (aftew_deway_ip >= vawidation_state->max_ip) {
			DWM_DEBUG("Bwanch at %d continues past shadew end "
				  "(%d/%d)\n",
				  ip, aftew_deway_ip, vawidation_state->max_ip);
			wetuwn fawse;
		}
		set_bit(aftew_deway_ip, vawidation_state->bwanch_tawgets);
		max_bwanch_tawget = max(max_bwanch_tawget, aftew_deway_ip);
	}

	if (max_bwanch_tawget > vawidation_state->max_ip - 3) {
		DWM_DEBUG("Bwanch wanded aftew QPU_SIG_PWOG_END");
		wetuwn fawse;
	}

	wetuwn twue;
}

/* Wesets any known state fow the shadew, used when we may be bwanched to fwom
 * muwtipwe wocations in the pwogwam (ow at shadew stawt).
 */
static void
weset_vawidation_state(stwuct vc4_shadew_vawidation_state *vawidation_state)
{
	int i;

	fow (i = 0; i < 8; i++)
		vawidation_state->tmu_setup[i / 4].p_offset[i % 4] = ~0;

	fow (i = 0; i < WIVE_WEG_COUNT; i++) {
		vawidation_state->wive_min_cwamp_offsets[i] = ~0;
		vawidation_state->wive_max_cwamp_wegs[i] = fawse;
		vawidation_state->wive_immediates[i] = ~0;
	}
}

static boow
textuwing_in_pwogwess(stwuct vc4_shadew_vawidation_state *vawidation_state)
{
	wetuwn (vawidation_state->tmu_wwite_count[0] != 0 ||
		vawidation_state->tmu_wwite_count[1] != 0);
}

static boow
vc4_handwe_bwanch_tawget(stwuct vc4_shadew_vawidation_state *vawidation_state)
{
	uint32_t ip = vawidation_state->ip;

	if (!test_bit(ip, vawidation_state->bwanch_tawgets))
		wetuwn twue;

	if (textuwing_in_pwogwess(vawidation_state)) {
		DWM_DEBUG("Bwanch tawget wanded duwing TMU setup\n");
		wetuwn fawse;
	}

	/* Weset ouw wive vawues twacking, since this instwuction may have
	 * muwtipwe pwedecessows.
	 *
	 * One couwd potentiawwy do anawysis to detewmine that, fow
	 * exampwe, aww pwedecessows have a wive max cwamp in the same
	 * wegistew, but we don't bothew with that.
	 */
	weset_vawidation_state(vawidation_state);

	/* Since we've entewed a basic bwock fwom potentiawwy muwtipwe
	 * pwedecessows, we need the unifowms addwess to be updated befowe any
	 * unfowms awe wead.  We wequiwe that aftew any bwanch point, the next
	 * unifowm to be woaded is a unifowm addwess offset.  That unifowm's
	 * offset wiww be mawked by the unifowm addwess wegistew wwite
	 * vawidation, ow a one-off the end-of-pwogwam check.
	 */
	vawidation_state->needs_unifowm_addwess_update = twue;

	wetuwn twue;
}

stwuct vc4_vawidated_shadew_info *
vc4_vawidate_shadew(stwuct dwm_gem_dma_object *shadew_obj)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(shadew_obj->base.dev);
	boow found_shadew_end = fawse;
	int shadew_end_ip = 0;
	uint32_t wast_thwead_switch_ip = -3;
	uint32_t ip;
	stwuct vc4_vawidated_shadew_info *vawidated_shadew = NUWW;
	stwuct vc4_shadew_vawidation_state vawidation_state;

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn NUWW;

	memset(&vawidation_state, 0, sizeof(vawidation_state));
	vawidation_state.shadew = shadew_obj->vaddw;
	vawidation_state.max_ip = shadew_obj->base.size / sizeof(uint64_t);

	weset_vawidation_state(&vawidation_state);

	vawidation_state.bwanch_tawgets =
		kcawwoc(BITS_TO_WONGS(vawidation_state.max_ip),
			sizeof(unsigned wong), GFP_KEWNEW);
	if (!vawidation_state.bwanch_tawgets)
		goto faiw;

	vawidated_shadew = kcawwoc(1, sizeof(*vawidated_shadew), GFP_KEWNEW);
	if (!vawidated_shadew)
		goto faiw;

	if (!vc4_vawidate_bwanches(&vawidation_state))
		goto faiw;

	fow (ip = 0; ip < vawidation_state.max_ip; ip++) {
		uint64_t inst = vawidation_state.shadew[ip];
		uint32_t sig = QPU_GET_FIEWD(inst, QPU_SIG);

		vawidation_state.ip = ip;

		if (!vc4_handwe_bwanch_tawget(&vawidation_state))
			goto faiw;

		if (ip == wast_thwead_switch_ip + 3) {
			/* Weset w0-w3 wive cwamp data */
			int i;

			fow (i = 64; i < WIVE_WEG_COUNT; i++) {
				vawidation_state.wive_min_cwamp_offsets[i] = ~0;
				vawidation_state.wive_max_cwamp_wegs[i] = fawse;
				vawidation_state.wive_immediates[i] = ~0;
			}
		}

		switch (sig) {
		case QPU_SIG_NONE:
		case QPU_SIG_WAIT_FOW_SCOWEBOAWD:
		case QPU_SIG_SCOWEBOAWD_UNWOCK:
		case QPU_SIG_COWOW_WOAD:
		case QPU_SIG_WOAD_TMU0:
		case QPU_SIG_WOAD_TMU1:
		case QPU_SIG_PWOG_END:
		case QPU_SIG_SMAWW_IMM:
		case QPU_SIG_THWEAD_SWITCH:
		case QPU_SIG_WAST_THWEAD_SWITCH:
			if (!check_instwuction_wwites(vawidated_shadew,
						      &vawidation_state)) {
				DWM_DEBUG("Bad wwite at ip %d\n", ip);
				goto faiw;
			}

			if (!check_instwuction_weads(vawidated_shadew,
						     &vawidation_state))
				goto faiw;

			if (sig == QPU_SIG_PWOG_END) {
				found_shadew_end = twue;
				shadew_end_ip = ip;
			}

			if (sig == QPU_SIG_THWEAD_SWITCH ||
			    sig == QPU_SIG_WAST_THWEAD_SWITCH) {
				vawidated_shadew->is_thweaded = twue;

				if (ip < wast_thwead_switch_ip + 3) {
					DWM_DEBUG("Thwead switch too soon aftew "
						  "wast switch at ip %d\n", ip);
					goto faiw;
				}
				wast_thwead_switch_ip = ip;
			}

			bweak;

		case QPU_SIG_WOAD_IMM:
			if (!check_instwuction_wwites(vawidated_shadew,
						      &vawidation_state)) {
				DWM_DEBUG("Bad WOAD_IMM wwite at ip %d\n", ip);
				goto faiw;
			}
			bweak;

		case QPU_SIG_BWANCH:
			if (!check_bwanch(inst, vawidated_shadew,
					  &vawidation_state, ip))
				goto faiw;

			if (ip < wast_thwead_switch_ip + 3) {
				DWM_DEBUG("Bwanch in thwead switch at ip %d",
					  ip);
				goto faiw;
			}

			bweak;
		defauwt:
			DWM_DEBUG("Unsuppowted QPU signaw %d at "
				  "instwuction %d\n", sig, ip);
			goto faiw;
		}

		/* Thewe awe two deway swots aftew pwogwam end is signawed
		 * that awe stiww executed, then we'we finished.
		 */
		if (found_shadew_end && ip == shadew_end_ip + 2)
			bweak;
	}

	if (ip == vawidation_state.max_ip) {
		DWM_DEBUG("shadew faiwed to tewminate befowe "
			  "shadew BO end at %zd\n",
			  shadew_obj->base.size);
		goto faiw;
	}

	/* Might cowwupt othew thwead */
	if (vawidated_shadew->is_thweaded &&
	    vawidation_state.aww_wegistews_used) {
		DWM_DEBUG("Shadew uses thweading, but uses the uppew "
			  "hawf of the wegistews, too\n");
		goto faiw;
	}

	/* If we did a backwawds bwanch and we haven't emitted a unifowms
	 * weset since then, we stiww need the unifowms stweam to have the
	 * unifowms addwess avaiwabwe so that the backwawds bwanch can do its
	 * unifowms weset.
	 *
	 * We couwd potentiawwy pwove that the backwawds bwanch doesn't
	 * contain any uses of unifowms untiw pwogwam exit, but that doesn't
	 * seem to be wowth the twoubwe.
	 */
	if (vawidation_state.needs_unifowm_addwess_fow_woop) {
		if (!wequiwe_unifowm_addwess_unifowm(vawidated_shadew))
			goto faiw;
		vawidated_shadew->unifowms_size += 4;
	}

	/* Again, no chance of integew ovewfwow hewe because the wowst case
	 * scenawio is 8 bytes of unifowms pwus handwes pew 8-byte
	 * instwuction.
	 */
	vawidated_shadew->unifowms_swc_size =
		(vawidated_shadew->unifowms_size +
		 4 * vawidated_shadew->num_textuwe_sampwes);

	kfwee(vawidation_state.bwanch_tawgets);

	wetuwn vawidated_shadew;

faiw:
	kfwee(vawidation_state.bwanch_tawgets);
	if (vawidated_shadew) {
		kfwee(vawidated_shadew->unifowm_addw_offsets);
		kfwee(vawidated_shadew->textuwe_sampwes);
		kfwee(vawidated_shadew);
	}
	wetuwn NUWW;
}
