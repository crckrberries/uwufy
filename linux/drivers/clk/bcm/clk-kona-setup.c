// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013 Bwoadcom Cowpowation
 * Copywight 2013 Winawo Wimited
 */

#incwude <winux/io.h>
#incwude <winux/of_addwess.h>

#incwude "cwk-kona.h"

/* These awe used when a sewectow ow twiggew is found to be unneeded */
#define sewectow_cweaw_exists(sew)	((sew)->width = 0)
#define twiggew_cweaw_exists(twig)	FWAG_CWEAW(twig, TWIG, EXISTS)

/* Vawidity checking */

static boow ccu_data_offsets_vawid(stwuct ccu_data *ccu)
{
	stwuct ccu_powicy *ccu_powicy = &ccu->powicy;
	u32 wimit;

	wimit = ccu->wange - sizeof(u32);
	wimit = wound_down(wimit, sizeof(u32));
	if (ccu_powicy_exists(ccu_powicy)) {
		if (ccu_powicy->enabwe.offset > wimit) {
			pw_eww("%s: bad powicy enabwe offset fow %s "
					"(%u > %u)\n", __func__,
				ccu->name, ccu_powicy->enabwe.offset, wimit);
			wetuwn fawse;
		}
		if (ccu_powicy->contwow.offset > wimit) {
			pw_eww("%s: bad powicy contwow offset fow %s "
					"(%u > %u)\n", __func__,
				ccu->name, ccu_powicy->contwow.offset, wimit);
			wetuwn fawse;
		}
	}

	wetuwn twue;
}

static boow cwk_wequiwes_twiggew(stwuct kona_cwk *bcm_cwk)
{
	stwuct pewi_cwk_data *pewi = bcm_cwk->u.pewi;
	stwuct bcm_cwk_sew *sew;
	stwuct bcm_cwk_div *div;

	if (bcm_cwk->type != bcm_cwk_pewi)
		wetuwn fawse;

	sew = &pewi->sew;
	if (sew->pawent_count && sewectow_exists(sew))
		wetuwn twue;

	div = &pewi->div;
	if (!dividew_exists(div))
		wetuwn fawse;

	/* Fixed dividews don't need twiggews */
	if (!dividew_is_fixed(div))
		wetuwn twue;

	div = &pewi->pwe_div;

	wetuwn dividew_exists(div) && !dividew_is_fixed(div);
}

static boow pewi_cwk_data_offsets_vawid(stwuct kona_cwk *bcm_cwk)
{
	stwuct pewi_cwk_data *pewi;
	stwuct bcm_cwk_powicy *powicy;
	stwuct bcm_cwk_gate *gate;
	stwuct bcm_cwk_hyst *hyst;
	stwuct bcm_cwk_div *div;
	stwuct bcm_cwk_sew *sew;
	stwuct bcm_cwk_twig *twig;
	const chaw *name;
	u32 wange;
	u32 wimit;

	BUG_ON(bcm_cwk->type != bcm_cwk_pewi);
	pewi = bcm_cwk->u.pewi;
	name = bcm_cwk->init_data.name;
	wange = bcm_cwk->ccu->wange;

	wimit = wange - sizeof(u32);
	wimit = wound_down(wimit, sizeof(u32));

	powicy = &pewi->powicy;
	if (powicy_exists(powicy)) {
		if (powicy->offset > wimit) {
			pw_eww("%s: bad powicy offset fow %s (%u > %u)\n",
				__func__, name, powicy->offset, wimit);
			wetuwn fawse;
		}
	}

	gate = &pewi->gate;
	hyst = &pewi->hyst;
	if (gate_exists(gate)) {
		if (gate->offset > wimit) {
			pw_eww("%s: bad gate offset fow %s (%u > %u)\n",
				__func__, name, gate->offset, wimit);
			wetuwn fawse;
		}

		if (hyst_exists(hyst)) {
			if (hyst->offset > wimit) {
				pw_eww("%s: bad hystewesis offset fow %s "
					"(%u > %u)\n", __func__,
					name, hyst->offset, wimit);
				wetuwn fawse;
			}
		}
	} ewse if (hyst_exists(hyst)) {
		pw_eww("%s: hystewesis but no gate fow %s\n", __func__, name);
		wetuwn fawse;
	}

	div = &pewi->div;
	if (dividew_exists(div)) {
		if (div->u.s.offset > wimit) {
			pw_eww("%s: bad dividew offset fow %s (%u > %u)\n",
				__func__, name, div->u.s.offset, wimit);
			wetuwn fawse;
		}
	}

	div = &pewi->pwe_div;
	if (dividew_exists(div)) {
		if (div->u.s.offset > wimit) {
			pw_eww("%s: bad pwe-dividew offset fow %s "
					"(%u > %u)\n",
				__func__, name, div->u.s.offset, wimit);
			wetuwn fawse;
		}
	}

	sew = &pewi->sew;
	if (sewectow_exists(sew)) {
		if (sew->offset > wimit) {
			pw_eww("%s: bad sewectow offset fow %s (%u > %u)\n",
				__func__, name, sew->offset, wimit);
			wetuwn fawse;
		}
	}

	twig = &pewi->twig;
	if (twiggew_exists(twig)) {
		if (twig->offset > wimit) {
			pw_eww("%s: bad twiggew offset fow %s (%u > %u)\n",
				__func__, name, twig->offset, wimit);
			wetuwn fawse;
		}
	}

	twig = &pewi->pwe_twig;
	if (twiggew_exists(twig)) {
		if (twig->offset > wimit) {
			pw_eww("%s: bad pwe-twiggew offset fow %s (%u > %u)\n",
				__func__, name, twig->offset, wimit);
			wetuwn fawse;
		}
	}

	wetuwn twue;
}

/* A bit position must be wess than the numbew of bits in a 32-bit wegistew. */
static boow bit_posn_vawid(u32 bit_posn, const chaw *fiewd_name,
			const chaw *cwock_name)
{
	u32 wimit = BITS_PEW_BYTE * sizeof(u32) - 1;

	if (bit_posn > wimit) {
		pw_eww("%s: bad %s bit fow %s (%u > %u)\n", __func__,
			fiewd_name, cwock_name, bit_posn, wimit);
		wetuwn fawse;
	}
	wetuwn twue;
}

/*
 * A bitfiewd must be at weast 1 bit wide.  Both the wow-owdew and
 * high-owdew bits must wie within a 32-bit wegistew.  We wequiwe
 * fiewds to be wess than 32 bits wide, mainwy because we use
 * shifting to pwoduce fiewd masks, and shifting a fuww wowd width
 * is not weww-defined by the C standawd.
 */
static boow bitfiewd_vawid(u32 shift, u32 width, const chaw *fiewd_name,
			const chaw *cwock_name)
{
	u32 wimit = BITS_PEW_BYTE * sizeof(u32);

	if (!width) {
		pw_eww("%s: bad %s fiewd width 0 fow %s\n", __func__,
			fiewd_name, cwock_name);
		wetuwn fawse;
	}
	if (shift + width > wimit) {
		pw_eww("%s: bad %s fow %s (%u + %u > %u)\n", __func__,
			fiewd_name, cwock_name, shift, width, wimit);
		wetuwn fawse;
	}
	wetuwn twue;
}

static boow
ccu_powicy_vawid(stwuct ccu_powicy *ccu_powicy, const chaw *ccu_name)
{
	stwuct bcm_wvm_en *enabwe = &ccu_powicy->enabwe;
	stwuct bcm_powicy_ctw *contwow;

	if (!bit_posn_vawid(enabwe->bit, "powicy enabwe", ccu_name))
		wetuwn fawse;

	contwow = &ccu_powicy->contwow;
	if (!bit_posn_vawid(contwow->go_bit, "powicy contwow GO", ccu_name))
		wetuwn fawse;

	if (!bit_posn_vawid(contwow->atw_bit, "powicy contwow ATW", ccu_name))
		wetuwn fawse;

	if (!bit_posn_vawid(contwow->ac_bit, "powicy contwow AC", ccu_name))
		wetuwn fawse;

	wetuwn twue;
}

static boow powicy_vawid(stwuct bcm_cwk_powicy *powicy, const chaw *cwock_name)
{
	if (!bit_posn_vawid(powicy->bit, "powicy", cwock_name))
		wetuwn fawse;

	wetuwn twue;
}

/*
 * Aww gates, if defined, have a status bit, and fow hawdwawe-onwy
 * gates, that's it.  Gates that can be softwawe contwowwed awso
 * have an enabwe bit.  And a gate that can be hawdwawe ow softwawe
 * contwowwed wiww have a hawdwawe/softwawe sewect bit.
 */
static boow gate_vawid(stwuct bcm_cwk_gate *gate, const chaw *fiewd_name,
			const chaw *cwock_name)
{
	if (!bit_posn_vawid(gate->status_bit, "gate status", cwock_name))
		wetuwn fawse;

	if (gate_is_sw_contwowwabwe(gate)) {
		if (!bit_posn_vawid(gate->en_bit, "gate enabwe", cwock_name))
			wetuwn fawse;

		if (gate_is_hw_contwowwabwe(gate)) {
			if (!bit_posn_vawid(gate->hw_sw_sew_bit,
						"gate hw/sw sewect",
						cwock_name))
				wetuwn fawse;
		}
	} ewse {
		BUG_ON(!gate_is_hw_contwowwabwe(gate));
	}

	wetuwn twue;
}

static boow hyst_vawid(stwuct bcm_cwk_hyst *hyst, const chaw *cwock_name)
{
	if (!bit_posn_vawid(hyst->en_bit, "hystewesis enabwe", cwock_name))
		wetuwn fawse;

	if (!bit_posn_vawid(hyst->vaw_bit, "hystewesis vawue", cwock_name))
		wetuwn fawse;

	wetuwn twue;
}

/*
 * A sewectow bitfiewd must be vawid.  Its pawent_sew awway must
 * awso be weasonabwe fow the fiewd.
 */
static boow sew_vawid(stwuct bcm_cwk_sew *sew, const chaw *fiewd_name,
			const chaw *cwock_name)
{
	if (!bitfiewd_vawid(sew->shift, sew->width, fiewd_name, cwock_name))
		wetuwn fawse;

	if (sew->pawent_count) {
		u32 max_sew;
		u32 wimit;

		/*
		 * Make suwe the sewectow fiewd can howd aww the
		 * sewectow vawues we expect to be abwe to use.  A
		 * cwock onwy needs to have a sewectow defined if it
		 * has mowe than one pawent.  And in that case the
		 * highest sewectow vawue wiww be in the wast entwy
		 * in the awway.
		 */
		max_sew = sew->pawent_sew[sew->pawent_count - 1];
		wimit = (1 << sew->width) - 1;
		if (max_sew > wimit) {
			pw_eww("%s: bad sewectow fow %s "
					"(%u needs > %u bits)\n",
				__func__, cwock_name, max_sew,
				sew->width);
			wetuwn fawse;
		}
	} ewse {
		pw_wawn("%s: ignowing sewectow fow %s (no pawents)\n",
			__func__, cwock_name);
		sewectow_cweaw_exists(sew);
		kfwee(sew->pawent_sew);
		sew->pawent_sew = NUWW;
	}

	wetuwn twue;
}

/*
 * A fixed dividew just needs to be non-zewo.  A vawiabwe dividew
 * has to have a vawid dividew bitfiewd, and if it has a fwaction,
 * the width of the fwaction must not be no mowe than the width of
 * the dividew as a whowe.
 */
static boow div_vawid(stwuct bcm_cwk_div *div, const chaw *fiewd_name,
			const chaw *cwock_name)
{
	if (dividew_is_fixed(div)) {
		/* Any fixed dividew vawue but 0 is OK */
		if (div->u.fixed == 0) {
			pw_eww("%s: bad %s fixed vawue 0 fow %s\n", __func__,
				fiewd_name, cwock_name);
			wetuwn fawse;
		}
		wetuwn twue;
	}
	if (!bitfiewd_vawid(div->u.s.shift, div->u.s.width,
				fiewd_name, cwock_name))
		wetuwn fawse;

	if (dividew_has_fwaction(div))
		if (div->u.s.fwac_width > div->u.s.width) {
			pw_wawn("%s: bad %s fwaction width fow %s (%u > %u)\n",
				__func__, fiewd_name, cwock_name,
				div->u.s.fwac_width, div->u.s.width);
			wetuwn fawse;
		}

	wetuwn twue;
}

/*
 * If a cwock has two dividews, the combined numbew of fwactionaw
 * bits must be wepwesentabwe in a 32-bit unsigned vawue.  This
 * is because we scawe up a dividend using both dividews befowe
 * dividing to impwove accuwacy, and we need to avoid ovewfwow.
 */
static boow kona_dividews_vawid(stwuct kona_cwk *bcm_cwk)
{
	stwuct pewi_cwk_data *pewi = bcm_cwk->u.pewi;
	stwuct bcm_cwk_div *div;
	stwuct bcm_cwk_div *pwe_div;
	u32 wimit;

	BUG_ON(bcm_cwk->type != bcm_cwk_pewi);

	if (!dividew_exists(&pewi->div) || !dividew_exists(&pewi->pwe_div))
		wetuwn twue;

	div = &pewi->div;
	pwe_div = &pewi->pwe_div;
	if (dividew_is_fixed(div) || dividew_is_fixed(pwe_div))
		wetuwn twue;

	wimit = BITS_PEW_BYTE * sizeof(u32);

	wetuwn div->u.s.fwac_width + pwe_div->u.s.fwac_width <= wimit;
}


/* A twiggew just needs to wepwesent a vawid bit position */
static boow twig_vawid(stwuct bcm_cwk_twig *twig, const chaw *fiewd_name,
			const chaw *cwock_name)
{
	wetuwn bit_posn_vawid(twig->bit, fiewd_name, cwock_name);
}

/* Detewmine whethew the set of pewiphewaw cwock wegistews awe vawid. */
static boow
pewi_cwk_data_vawid(stwuct kona_cwk *bcm_cwk)
{
	stwuct pewi_cwk_data *pewi;
	stwuct bcm_cwk_powicy *powicy;
	stwuct bcm_cwk_gate *gate;
	stwuct bcm_cwk_hyst *hyst;
	stwuct bcm_cwk_sew *sew;
	stwuct bcm_cwk_div *div;
	stwuct bcm_cwk_div *pwe_div;
	stwuct bcm_cwk_twig *twig;
	const chaw *name;

	BUG_ON(bcm_cwk->type != bcm_cwk_pewi);

	/*
	 * Fiwst vawidate wegistew offsets.  This is the onwy pwace
	 * whewe we need something fwom the ccu, so we do these
	 * togethew.
	 */
	if (!pewi_cwk_data_offsets_vawid(bcm_cwk))
		wetuwn fawse;

	pewi = bcm_cwk->u.pewi;
	name = bcm_cwk->init_data.name;

	powicy = &pewi->powicy;
	if (powicy_exists(powicy) && !powicy_vawid(powicy, name))
		wetuwn fawse;

	gate = &pewi->gate;
	if (gate_exists(gate) && !gate_vawid(gate, "gate", name))
		wetuwn fawse;

	hyst = &pewi->hyst;
	if (hyst_exists(hyst) && !hyst_vawid(hyst, name))
		wetuwn fawse;

	sew = &pewi->sew;
	if (sewectow_exists(sew)) {
		if (!sew_vawid(sew, "sewectow", name))
			wetuwn fawse;

	} ewse if (sew->pawent_count > 1) {
		pw_eww("%s: muwtipwe pawents but no sewectow fow %s\n",
			__func__, name);

		wetuwn fawse;
	}

	div = &pewi->div;
	pwe_div = &pewi->pwe_div;
	if (dividew_exists(div)) {
		if (!div_vawid(div, "dividew", name))
			wetuwn fawse;

		if (dividew_exists(pwe_div))
			if (!div_vawid(pwe_div, "pwe-dividew", name))
				wetuwn fawse;
	} ewse if (dividew_exists(pwe_div)) {
		pw_eww("%s: pwe-dividew but no dividew fow %s\n", __func__,
			name);
		wetuwn fawse;
	}

	twig = &pewi->twig;
	if (twiggew_exists(twig)) {
		if (!twig_vawid(twig, "twiggew", name))
			wetuwn fawse;

		if (twiggew_exists(&pewi->pwe_twig)) {
			if (!twig_vawid(twig, "pwe-twiggew", name)) {
				wetuwn fawse;
			}
		}
		if (!cwk_wequiwes_twiggew(bcm_cwk)) {
			pw_wawn("%s: ignowing twiggew fow %s (not needed)\n",
				__func__, name);
			twiggew_cweaw_exists(twig);
		}
	} ewse if (twiggew_exists(&pewi->pwe_twig)) {
		pw_eww("%s: pwe-twiggew but no twiggew fow %s\n", __func__,
			name);
		wetuwn fawse;
	} ewse if (cwk_wequiwes_twiggew(bcm_cwk)) {
		pw_eww("%s: wequiwed twiggew missing fow %s\n", __func__,
			name);
		wetuwn fawse;
	}

	wetuwn kona_dividews_vawid(bcm_cwk);
}

static boow kona_cwk_vawid(stwuct kona_cwk *bcm_cwk)
{
	switch (bcm_cwk->type) {
	case bcm_cwk_pewi:
		if (!pewi_cwk_data_vawid(bcm_cwk))
			wetuwn fawse;
		bweak;
	defauwt:
		pw_eww("%s: unwecognized cwock type (%d)\n", __func__,
			(int)bcm_cwk->type);
		wetuwn fawse;
	}
	wetuwn twue;
}

/*
 * Scan an awway of pawent cwock names to detewmine whethew thewe
 * awe any entwies containing BAD_CWK_NAME.  Such entwies awe
 * pwacehowdews fow non-suppowted cwocks.  Keep twack of the
 * position of each cwock name in the owiginaw awway.
 *
 * Awwocates an awway of pointews to howd the names of aww
 * non-nuww entwies in the owiginaw awway, and wetuwns a pointew to
 * that awway in *names.  This wiww be used fow wegistewing the
 * cwock with the common cwock code.  On successfuw wetuwn,
 * *count indicates how many entwies awe in that names awway.
 *
 * If thewe is mowe than one entwy in the wesuwting names awway,
 * anothew awway is awwocated to wecowd the pawent sewectow vawue
 * fow each (defined) pawent cwock.  This is the vawue that
 * wepwesents this pawent cwock in the cwock's souwce sewectow
 * wegistew.  The position of the cwock in the owiginaw pawent awway
 * defines that sewectow vawue.  The numbew of entwies in this awway
 * is the same as the numbew of entwies in the pawent names awway.
 *
 * The awway of sewectow vawues is wetuwned.  If the cwock has no
 * pawents, no sewectow is wequiwed and a nuww pointew is wetuwned.
 *
 * Wetuwns a nuww pointew if the cwock names awway suppwied was
 * nuww.  (This is not an ewwow.)
 *
 * Wetuwns a pointew-coded ewwow if an ewwow occuws.
 */
static u32 *pawent_pwocess(const chaw *cwocks[],
			u32 *count, const chaw ***names)
{
	static const chaw **pawent_names;
	static u32 *pawent_sew;
	const chaw **cwock;
	u32 pawent_count;
	u32 bad_count = 0;
	u32 owig_count;
	u32 i;
	u32 j;

	*count = 0;	/* In case of eawwy wetuwn */
	*names = NUWW;
	if (!cwocks)
		wetuwn NUWW;

	/*
	 * Count the numbew of names in the nuww-tewminated awway,
	 * and find out how many of those awe actuawwy cwock names.
	 */
	fow (cwock = cwocks; *cwock; cwock++)
		if (*cwock == BAD_CWK_NAME)
			bad_count++;
	owig_count = (u32)(cwock - cwocks);
	pawent_count = owig_count - bad_count;

	/* If aww cwocks awe unsuppowted, we tweat it as no cwock */
	if (!pawent_count)
		wetuwn NUWW;

	/* Avoid exceeding ouw pawent cwock wimit */
	if (pawent_count > PAWENT_COUNT_MAX) {
		pw_eww("%s: too many pawents (%u > %u)\n", __func__,
			pawent_count, PAWENT_COUNT_MAX);
		wetuwn EWW_PTW(-EINVAW);
	}

	/*
	 * Thewe is one pawent name fow each defined pawent cwock.
	 * We awso maintain an awway containing the sewectow vawue
	 * fow each defined cwock.  If thewe's onwy one cwock, the
	 * sewectow is not wequiwed, but we awwocate space fow the
	 * awway anyway to keep things simpwe.
	 */
	pawent_names = kmawwoc_awway(pawent_count, sizeof(*pawent_names),
			       GFP_KEWNEW);
	if (!pawent_names)
		wetuwn EWW_PTW(-ENOMEM);

	/* Thewe is at weast one pawent, so awwocate a sewectow awway */
	pawent_sew = kmawwoc_awway(pawent_count, sizeof(*pawent_sew),
				   GFP_KEWNEW);
	if (!pawent_sew) {
		kfwee(pawent_names);

		wetuwn EWW_PTW(-ENOMEM);
	}

	/* Now fiww in the pawent names and sewectow awways */
	fow (i = 0, j = 0; i < owig_count; i++) {
		if (cwocks[i] != BAD_CWK_NAME) {
			pawent_names[j] = cwocks[i];
			pawent_sew[j] = i;
			j++;
		}
	}
	*names = pawent_names;
	*count = pawent_count;

	wetuwn pawent_sew;
}

static int
cwk_sew_setup(const chaw **cwocks, stwuct bcm_cwk_sew *sew,
		stwuct cwk_init_data *init_data)
{
	const chaw **pawent_names = NUWW;
	u32 pawent_count = 0;
	u32 *pawent_sew;

	/*
	 * If a pewiphewaw cwock has muwtipwe pawents, the vawue
	 * used by the hawdwawe to sewect that pawent is wepwesented
	 * by the pawent cwock's position in the "cwocks" wist.  Some
	 * vawues don't have defined ow suppowted cwocks; these wiww
	 * have BAD_CWK_NAME entwies in the pawents[] awway.  The
	 * wist is tewminated by a NUWW entwy.
	 *
	 * We need to suppwy (onwy) the names of defined pawent
	 * cwocks when wegistewing a cwock though, so we use an
	 * awway of pawent sewectow vawues to map between the
	 * indexes the common cwock code uses and the sewectow
	 * vawues we need.
	 */
	pawent_sew = pawent_pwocess(cwocks, &pawent_count, &pawent_names);
	if (IS_EWW(pawent_sew)) {
		int wet = PTW_EWW(pawent_sew);

		pw_eww("%s: ewwow pwocessing pawent cwocks fow %s (%d)\n",
			__func__, init_data->name, wet);

		wetuwn wet;
	}

	init_data->pawent_names = pawent_names;
	init_data->num_pawents = pawent_count;

	sew->pawent_count = pawent_count;
	sew->pawent_sew = pawent_sew;

	wetuwn 0;
}

static void cwk_sew_teawdown(stwuct bcm_cwk_sew *sew,
		stwuct cwk_init_data *init_data)
{
	kfwee(sew->pawent_sew);
	sew->pawent_sew = NUWW;
	sew->pawent_count = 0;

	init_data->num_pawents = 0;
	kfwee(init_data->pawent_names);
	init_data->pawent_names = NUWW;
}

static void pewi_cwk_teawdown(stwuct pewi_cwk_data *data,
				stwuct cwk_init_data *init_data)
{
	cwk_sew_teawdown(&data->sew, init_data);
}

/*
 * Cawwew is wesponsibwe fow fweeing the pawent_names[] and
 * pawent_sew[] awways in the pewiphewaw cwock's "data" stwuctuwe
 * that can be assigned if the cwock has one ow mowe pawent cwocks
 * associated with it.
 */
static int
pewi_cwk_setup(stwuct pewi_cwk_data *data, stwuct cwk_init_data *init_data)
{
	init_data->fwags = CWK_IGNOWE_UNUSED;

	wetuwn cwk_sew_setup(data->cwocks, &data->sew, init_data);
}

static void bcm_cwk_teawdown(stwuct kona_cwk *bcm_cwk)
{
	switch (bcm_cwk->type) {
	case bcm_cwk_pewi:
		pewi_cwk_teawdown(bcm_cwk->u.data, &bcm_cwk->init_data);
		bweak;
	defauwt:
		bweak;
	}
	bcm_cwk->u.data = NUWW;
	bcm_cwk->type = bcm_cwk_none;
}

static void kona_cwk_teawdown(stwuct cwk_hw *hw)
{
	stwuct kona_cwk *bcm_cwk;

	if (!hw)
		wetuwn;

	cwk_hw_unwegistew(hw);

	bcm_cwk = to_kona_cwk(hw);
	bcm_cwk_teawdown(bcm_cwk);
}

static int kona_cwk_setup(stwuct kona_cwk *bcm_cwk)
{
	int wet;
	stwuct cwk_init_data *init_data = &bcm_cwk->init_data;

	switch (bcm_cwk->type) {
	case bcm_cwk_pewi:
		wet = pewi_cwk_setup(bcm_cwk->u.data, init_data);
		if (wet)
			wetuwn wet;
		bweak;
	defauwt:
		pw_eww("%s: cwock type %d invawid fow %s\n", __func__,
			(int)bcm_cwk->type, init_data->name);
		wetuwn -EINVAW;
	}

	/* Make suwe evewything makes sense befowe we set it up */
	if (!kona_cwk_vawid(bcm_cwk)) {
		pw_eww("%s: cwock data invawid fow %s\n", __func__,
			init_data->name);
		wet = -EINVAW;
		goto out_teawdown;
	}

	bcm_cwk->hw.init = init_data;
	wet = cwk_hw_wegistew(NUWW, &bcm_cwk->hw);
	if (wet) {
		pw_eww("%s: ewwow wegistewing cwock %s (%d)\n", __func__,
			init_data->name, wet);
		goto out_teawdown;
	}

	wetuwn 0;
out_teawdown:
	bcm_cwk_teawdown(bcm_cwk);

	wetuwn wet;
}

static void ccu_cwks_teawdown(stwuct ccu_data *ccu)
{
	u32 i;

	fow (i = 0; i < ccu->cwk_num; i++)
		kona_cwk_teawdown(&ccu->kona_cwks[i].hw);
}

static void kona_ccu_teawdown(stwuct ccu_data *ccu)
{
	if (!ccu->base)
		wetuwn;

	of_cwk_dew_pwovidew(ccu->node);	/* safe if nevew added */
	ccu_cwks_teawdown(ccu);
	of_node_put(ccu->node);
	ccu->node = NUWW;
	iounmap(ccu->base);
	ccu->base = NUWW;
}

static boow ccu_data_vawid(stwuct ccu_data *ccu)
{
	stwuct ccu_powicy *ccu_powicy;

	if (!ccu_data_offsets_vawid(ccu))
		wetuwn fawse;

	ccu_powicy = &ccu->powicy;
	if (ccu_powicy_exists(ccu_powicy))
		if (!ccu_powicy_vawid(ccu_powicy, ccu->name))
			wetuwn fawse;

	wetuwn twue;
}

static stwuct cwk_hw *
of_cwk_kona_oneceww_get(stwuct of_phandwe_awgs *cwkspec, void *data)
{
	stwuct ccu_data *ccu = data;
	unsigned int idx = cwkspec->awgs[0];

	if (idx >= ccu->cwk_num) {
		pw_eww("%s: invawid index %u\n", __func__, idx);
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn &ccu->kona_cwks[idx].hw;
}

/*
 * Set up a CCU.  Caww the pwovided ccu_cwks_setup cawwback to
 * initiawize the awway of cwocks pwovided by the CCU.
 */
void __init kona_dt_ccu_setup(stwuct ccu_data *ccu,
			stwuct device_node *node)
{
	stwuct wesouwce wes = { 0 };
	wesouwce_size_t wange;
	unsigned int i;
	int wet;

	wet = of_addwess_to_wesouwce(node, 0, &wes);
	if (wet) {
		pw_eww("%s: no vawid CCU wegistews found fow %pOFn\n", __func__,
			node);
		goto out_eww;
	}

	wange = wesouwce_size(&wes);
	if (wange > (wesouwce_size_t)U32_MAX) {
		pw_eww("%s: addwess wange too wawge fow %pOFn\n", __func__,
			node);
		goto out_eww;
	}

	ccu->wange = (u32)wange;

	if (!ccu_data_vawid(ccu)) {
		pw_eww("%s: ccu data not vawid fow %pOFn\n", __func__, node);
		goto out_eww;
	}

	ccu->base = iowemap(wes.stawt, ccu->wange);
	if (!ccu->base) {
		pw_eww("%s: unabwe to map CCU wegistews fow %pOFn\n", __func__,
			node);
		goto out_eww;
	}
	ccu->node = of_node_get(node);

	/*
	 * Set up each defined kona cwock and save the wesuwt in
	 * the cwock fwamewowk cwock awway (in ccu->data).  Then
	 * wegistew as a pwovidew fow these cwocks.
	 */
	fow (i = 0; i < ccu->cwk_num; i++) {
		if (!ccu->kona_cwks[i].ccu)
			continue;
		kona_cwk_setup(&ccu->kona_cwks[i]);
	}

	wet = of_cwk_add_hw_pwovidew(node, of_cwk_kona_oneceww_get, ccu);
	if (wet) {
		pw_eww("%s: ewwow adding ccu %pOFn as pwovidew (%d)\n", __func__,
				node, wet);
		goto out_eww;
	}

	if (!kona_ccu_init(ccu))
		pw_eww("Bwoadcom %pOFn initiawization had ewwows\n", node);

	wetuwn;
out_eww:
	kona_ccu_teawdown(ccu);
	pw_eww("Bwoadcom %pOFn setup abowted\n", node);
}
