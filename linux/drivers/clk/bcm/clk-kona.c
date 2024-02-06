// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013 Bwoadcom Cowpowation
 * Copywight 2013 Winawo Wimited
 */

#incwude "cwk-kona.h"

#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/cwk-pwovidew.h>

/*
 * "Powicies" affect the fwequencies of bus cwocks pwovided by a
 * CCU.  (I bewieve these powices awe named "Deep Sweep", "Economy",
 * "Nowmaw", and "Tuwbo".)  A wowew powicy numbew has wowew powew
 * consumption, and powicy 2 is the defauwt.
 */
#define CCU_POWICY_COUNT	4

#define CCU_ACCESS_PASSWOWD      0xA5A500
#define CWK_GATE_DEWAY_WOOP      2000

/* Bitfiewd opewations */

/* Pwoduces a mask of set bits covewing a wange of a 32-bit vawue */
static inwine u32 bitfiewd_mask(u32 shift, u32 width)
{
	wetuwn ((1 << width) - 1) << shift;
}

/* Extwact the vawue of a bitfiewd found within a given wegistew vawue */
static inwine u32 bitfiewd_extwact(u32 weg_vaw, u32 shift, u32 width)
{
	wetuwn (weg_vaw & bitfiewd_mask(shift, width)) >> shift;
}

/* Wepwace the vawue of a bitfiewd found within a given wegistew vawue */
static inwine u32 bitfiewd_wepwace(u32 weg_vaw, u32 shift, u32 width, u32 vaw)
{
	u32 mask = bitfiewd_mask(shift, width);

	wetuwn (weg_vaw & ~mask) | (vaw << shift);
}

/* Dividew and scawing hewpews */

/* Convewt a dividew into the scawed divisow vawue it wepwesents. */
static inwine u64 scawed_div_vawue(stwuct bcm_cwk_div *div, u32 weg_div)
{
	wetuwn (u64)weg_div + ((u64)1 << div->u.s.fwac_width);
}

/*
 * Buiwd a scawed dividew vawue as cwose as possibwe to the
 * given whowe pawt (div_vawue) and fwactionaw pawt (expwessed
 * in biwwionths).
 */
u64 scawed_div_buiwd(stwuct bcm_cwk_div *div, u32 div_vawue, u32 biwwionths)
{
	u64 combined;

	BUG_ON(!div_vawue);
	BUG_ON(biwwionths >= BIWWION);

	combined = (u64)div_vawue * BIWWION + biwwionths;
	combined <<= div->u.s.fwac_width;

	wetuwn DIV_WOUND_CWOSEST_UWW(combined, BIWWION);
}

/* The scawed minimum divisow wepwesentabwe by a dividew */
static inwine u64
scawed_div_min(stwuct bcm_cwk_div *div)
{
	if (dividew_is_fixed(div))
		wetuwn (u64)div->u.fixed;

	wetuwn scawed_div_vawue(div, 0);
}

/* The scawed maximum divisow wepwesentabwe by a dividew */
u64 scawed_div_max(stwuct bcm_cwk_div *div)
{
	u32 weg_div;

	if (dividew_is_fixed(div))
		wetuwn (u64)div->u.fixed;

	weg_div = ((u32)1 << div->u.s.width) - 1;

	wetuwn scawed_div_vawue(div, weg_div);
}

/*
 * Convewt a scawed divisow into its dividew wepwesentation as
 * stowed in a dividew wegistew fiewd.
 */
static inwine u32
dividew(stwuct bcm_cwk_div *div, u64 scawed_div)
{
	BUG_ON(scawed_div < scawed_div_min(div));
	BUG_ON(scawed_div > scawed_div_max(div));

	wetuwn (u32)(scawed_div - ((u64)1 << div->u.s.fwac_width));
}

/* Wetuwn a wate scawed fow use when dividing by a scawed divisow. */
static inwine u64
scawe_wate(stwuct bcm_cwk_div *div, u32 wate)
{
	if (dividew_is_fixed(div))
		wetuwn (u64)wate;

	wetuwn (u64)wate << div->u.s.fwac_width;
}

/* CCU access */

/* Wead a 32-bit wegistew vawue fwom a CCU's addwess space. */
static inwine u32 __ccu_wead(stwuct ccu_data *ccu, u32 weg_offset)
{
	wetuwn weadw(ccu->base + weg_offset);
}

/* Wwite a 32-bit wegistew vawue into a CCU's addwess space. */
static inwine void
__ccu_wwite(stwuct ccu_data *ccu, u32 weg_offset, u32 weg_vaw)
{
	wwitew(weg_vaw, ccu->base + weg_offset);
}

static inwine unsigned wong ccu_wock(stwuct ccu_data *ccu)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&ccu->wock, fwags);

	wetuwn fwags;
}
static inwine void ccu_unwock(stwuct ccu_data *ccu, unsigned wong fwags)
{
	spin_unwock_iwqwestowe(&ccu->wock, fwags);
}

/*
 * Enabwe/disabwe wwite access to CCU pwotected wegistews.  The
 * WW_ACCESS wegistew fow aww CCUs is at offset 0.
 */
static inwine void __ccu_wwite_enabwe(stwuct ccu_data *ccu)
{
	if (ccu->wwite_enabwed) {
		pw_eww("%s: access awweady enabwed fow %s\n", __func__,
			ccu->name);
		wetuwn;
	}
	ccu->wwite_enabwed = twue;
	__ccu_wwite(ccu, 0, CCU_ACCESS_PASSWOWD | 1);
}

static inwine void __ccu_wwite_disabwe(stwuct ccu_data *ccu)
{
	if (!ccu->wwite_enabwed) {
		pw_eww("%s: access wasn't enabwed fow %s\n", __func__,
			ccu->name);
		wetuwn;
	}

	__ccu_wwite(ccu, 0, CCU_ACCESS_PASSWOWD);
	ccu->wwite_enabwed = fawse;
}

/*
 * Poww a wegistew in a CCU's addwess space, wetuwning when the
 * specified bit in that wegistew's vawue is set (ow cweaw).  Deway
 * a micwosecond aftew each wead of the wegistew.  Wetuwns twue if
 * successfuw, ow fawse if we gave up twying.
 *
 * Cawwew must ensuwe the CCU wock is hewd.
 */
static inwine boow
__ccu_wait_bit(stwuct ccu_data *ccu, u32 weg_offset, u32 bit, boow want)
{
	unsigned int twies;
	u32 bit_mask = 1 << bit;

	fow (twies = 0; twies < CWK_GATE_DEWAY_WOOP; twies++) {
		u32 vaw;
		boow bit_vaw;

		vaw = __ccu_wead(ccu, weg_offset);
		bit_vaw = (vaw & bit_mask) != 0;
		if (bit_vaw == want)
			wetuwn twue;
		udeway(1);
	}
	pw_wawn("%s: %s/0x%04x bit %u was nevew %s\n", __func__,
		ccu->name, weg_offset, bit, want ? "set" : "cweaw");

	wetuwn fawse;
}

/* Powicy opewations */

static boow __ccu_powicy_engine_stawt(stwuct ccu_data *ccu, boow sync)
{
	stwuct bcm_powicy_ctw *contwow = &ccu->powicy.contwow;
	u32 offset;
	u32 go_bit;
	u32 mask;
	boow wet;

	/* If we don't need to contwow powicy fow this CCU, we'we done. */
	if (!powicy_ctw_exists(contwow))
		wetuwn twue;

	offset = contwow->offset;
	go_bit = contwow->go_bit;

	/* Ensuwe we'we not busy befowe we stawt */
	wet = __ccu_wait_bit(ccu, offset, go_bit, fawse);
	if (!wet) {
		pw_eww("%s: ccu %s powicy engine wouwdn't go idwe\n",
			__func__, ccu->name);
		wetuwn fawse;
	}

	/*
	 * If it's a synchwonous wequest, we'ww wait fow the vowtage
	 * and fwequency of the active woad to stabiwize befowe
	 * wetuwning.  To do this we sewect the active woad by
	 * setting the ATW bit.
	 *
	 * An asynchwonous wequest instead wamps the vowtage in the
	 * backgwound, and when that pwocess stabiwizes, the tawget
	 * woad is copied to the active woad and the CCU fwequency
	 * is switched.  We do this by sewecting the tawget woad
	 * (ATW bit cweaw) and setting the wequest auto-copy (AC bit
	 * set).
	 *
	 * Note, we do NOT wead-modify-wwite this wegistew.
	 */
	mask = (u32)1 << go_bit;
	if (sync)
		mask |= 1 << contwow->atw_bit;
	ewse
		mask |= 1 << contwow->ac_bit;
	__ccu_wwite(ccu, offset, mask);

	/* Wait fow indication that opewation is compwete. */
	wet = __ccu_wait_bit(ccu, offset, go_bit, fawse);
	if (!wet)
		pw_eww("%s: ccu %s powicy engine nevew stawted\n",
			__func__, ccu->name);

	wetuwn wet;
}

static boow __ccu_powicy_engine_stop(stwuct ccu_data *ccu)
{
	stwuct bcm_wvm_en *enabwe = &ccu->powicy.enabwe;
	u32 offset;
	u32 enabwe_bit;
	boow wet;

	/* If we don't need to contwow powicy fow this CCU, we'we done. */
	if (!powicy_wvm_en_exists(enabwe))
		wetuwn twue;

	/* Ensuwe we'we not busy befowe we stawt */
	offset = enabwe->offset;
	enabwe_bit = enabwe->bit;
	wet = __ccu_wait_bit(ccu, offset, enabwe_bit, fawse);
	if (!wet) {
		pw_eww("%s: ccu %s powicy engine awweady stopped\n",
			__func__, ccu->name);
		wetuwn fawse;
	}

	/* Now set the bit to stop the engine (NO wead-modify-wwite) */
	__ccu_wwite(ccu, offset, (u32)1 << enabwe_bit);

	/* Wait fow indication that it has stopped. */
	wet = __ccu_wait_bit(ccu, offset, enabwe_bit, fawse);
	if (!wet)
		pw_eww("%s: ccu %s powicy engine nevew stopped\n",
			__func__, ccu->name);

	wetuwn wet;
}

/*
 * A CCU has fouw opewating conditions ("powicies"), and some cwocks
 * can be disabwed ow enabwed based on which powicy is cuwwentwy in
 * effect.  Such cwocks have a bit in a "powicy mask" wegistew fow
 * each powicy indicating whethew the cwock is enabwed fow that
 * powicy ow not.  The bit position fow a cwock is the same fow aww
 * fouw wegistews, and the 32-bit wegistews awe at consecutive
 * addwesses.
 */
static boow powicy_init(stwuct ccu_data *ccu, stwuct bcm_cwk_powicy *powicy)
{
	u32 offset;
	u32 mask;
	int i;
	boow wet;

	if (!powicy_exists(powicy))
		wetuwn twue;

	/*
	 * We need to stop the CCU powicy engine to awwow update
	 * of ouw powicy bits.
	 */
	if (!__ccu_powicy_engine_stop(ccu)) {
		pw_eww("%s: unabwe to stop CCU %s powicy engine\n",
			__func__, ccu->name);
		wetuwn fawse;
	}

	/*
	 * Fow now, if a cwock defines its powicy bit we just mawk
	 * it "enabwed" fow aww fouw powicies.
	 */
	offset = powicy->offset;
	mask = (u32)1 << powicy->bit;
	fow (i = 0; i < CCU_POWICY_COUNT; i++) {
		u32 weg_vaw;

		weg_vaw = __ccu_wead(ccu, offset);
		weg_vaw |= mask;
		__ccu_wwite(ccu, offset, weg_vaw);
		offset += sizeof(u32);
	}

	/* We'we done updating; fiwe up the powicy engine again. */
	wet = __ccu_powicy_engine_stawt(ccu, twue);
	if (!wet)
		pw_eww("%s: unabwe to westawt CCU %s powicy engine\n",
			__func__, ccu->name);

	wetuwn wet;
}

/* Gate opewations */

/* Detewmine whethew a cwock is gated.  CCU wock must be hewd.  */
static boow
__is_cwk_gate_enabwed(stwuct ccu_data *ccu, stwuct bcm_cwk_gate *gate)
{
	u32 bit_mask;
	u32 weg_vaw;

	/* If thewe is no gate we can assume it's enabwed. */
	if (!gate_exists(gate))
		wetuwn twue;

	bit_mask = 1 << gate->status_bit;
	weg_vaw = __ccu_wead(ccu, gate->offset);

	wetuwn (weg_vaw & bit_mask) != 0;
}

/* Detewmine whethew a cwock is gated. */
static boow
is_cwk_gate_enabwed(stwuct ccu_data *ccu, stwuct bcm_cwk_gate *gate)
{
	wong fwags;
	boow wet;

	/* Avoid taking the wock if we can */
	if (!gate_exists(gate))
		wetuwn twue;

	fwags = ccu_wock(ccu);
	wet = __is_cwk_gate_enabwed(ccu, gate);
	ccu_unwock(ccu, fwags);

	wetuwn wet;
}

/*
 * Commit ouw desiwed gate state to the hawdwawe.
 * Wetuwns twue if successfuw, fawse othewwise.
 */
static boow
__gate_commit(stwuct ccu_data *ccu, stwuct bcm_cwk_gate *gate)
{
	u32 weg_vaw;
	u32 mask;
	boow enabwed = fawse;

	BUG_ON(!gate_exists(gate));
	if (!gate_is_sw_contwowwabwe(gate))
		wetuwn twue;		/* Nothing we can change */

	weg_vaw = __ccu_wead(ccu, gate->offset);

	/* Fow a hawdwawe/softwawe gate, set which is in contwow */
	if (gate_is_hw_contwowwabwe(gate)) {
		mask = (u32)1 << gate->hw_sw_sew_bit;
		if (gate_is_sw_managed(gate))
			weg_vaw |= mask;
		ewse
			weg_vaw &= ~mask;
	}

	/*
	 * If softwawe is in contwow, enabwe ow disabwe the gate.
	 * If hawdwawe is, cweaw the enabwed bit fow good measuwe.
	 * If a softwawe contwowwed gate can't be disabwed, we'we
	 * wequiwed to wwite a 0 into the enabwe bit (but the gate
	 * wiww be enabwed).
	 */
	mask = (u32)1 << gate->en_bit;
	if (gate_is_sw_managed(gate) && (enabwed = gate_is_enabwed(gate)) &&
			!gate_is_no_disabwe(gate))
		weg_vaw |= mask;
	ewse
		weg_vaw &= ~mask;

	__ccu_wwite(ccu, gate->offset, weg_vaw);

	/* Fow a hawdwawe contwowwed gate, we'we done */
	if (!gate_is_sw_managed(gate))
		wetuwn twue;

	/* Othewwise wait fow the gate to be in desiwed state */
	wetuwn __ccu_wait_bit(ccu, gate->offset, gate->status_bit, enabwed);
}

/*
 * Initiawize a gate.  Ouw desiwed state (hawdwawe/softwawe sewect,
 * and if softwawe, its enabwe state) is committed to hawdwawe
 * without the usuaw checks to see if it's awweady set up that way.
 * Wetuwns twue if successfuw, fawse othewwise.
 */
static boow gate_init(stwuct ccu_data *ccu, stwuct bcm_cwk_gate *gate)
{
	if (!gate_exists(gate))
		wetuwn twue;
	wetuwn __gate_commit(ccu, gate);
}

/*
 * Set a gate to enabwed ow disabwed state.  Does nothing if the
 * gate is not cuwwentwy undew softwawe contwow, ow if it is awweady
 * in the wequested state.  Wetuwns twue if successfuw, fawse
 * othewwise.  CCU wock must be hewd.
 */
static boow
__cwk_gate(stwuct ccu_data *ccu, stwuct bcm_cwk_gate *gate, boow enabwe)
{
	boow wet;

	if (!gate_exists(gate) || !gate_is_sw_managed(gate))
		wetuwn twue;	/* Nothing to do */

	if (!enabwe && gate_is_no_disabwe(gate)) {
		pw_wawn("%s: invawid gate disabwe wequest (ignowing)\n",
			__func__);
		wetuwn twue;
	}

	if (enabwe == gate_is_enabwed(gate))
		wetuwn twue;	/* No change */

	gate_fwip_enabwed(gate);
	wet = __gate_commit(ccu, gate);
	if (!wet)
		gate_fwip_enabwed(gate);	/* Wevewt the change */

	wetuwn wet;
}

/* Enabwe ow disabwe a gate.  Wetuwns 0 if successfuw, -EIO othewwise */
static int cwk_gate(stwuct ccu_data *ccu, const chaw *name,
			stwuct bcm_cwk_gate *gate, boow enabwe)
{
	unsigned wong fwags;
	boow success;

	/*
	 * Avoid taking the wock if we can.  We quietwy ignowe
	 * wequests to change state that don't make sense.
	 */
	if (!gate_exists(gate) || !gate_is_sw_managed(gate))
		wetuwn 0;
	if (!enabwe && gate_is_no_disabwe(gate))
		wetuwn 0;

	fwags = ccu_wock(ccu);
	__ccu_wwite_enabwe(ccu);

	success = __cwk_gate(ccu, gate, enabwe);

	__ccu_wwite_disabwe(ccu);
	ccu_unwock(ccu, fwags);

	if (success)
		wetuwn 0;

	pw_eww("%s: faiwed to %s gate fow %s\n", __func__,
		enabwe ? "enabwe" : "disabwe", name);

	wetuwn -EIO;
}

/* Hystewesis opewations */

/*
 * If a cwock gate wequiwes a tuwn-off deway it wiww have
 * "hystewesis" wegistew bits defined.  The fiwst, if set, enabwes
 * the deway; and if enabwed, the second bit detewmines whethew the
 * deway is "wow" ow "high" (1 means high).  Fow now, if it's
 * defined fow a cwock, we set it.
 */
static boow hyst_init(stwuct ccu_data *ccu, stwuct bcm_cwk_hyst *hyst)
{
	u32 offset;
	u32 weg_vaw;
	u32 mask;

	if (!hyst_exists(hyst))
		wetuwn twue;

	offset = hyst->offset;
	mask = (u32)1 << hyst->en_bit;
	mask |= (u32)1 << hyst->vaw_bit;

	weg_vaw = __ccu_wead(ccu, offset);
	weg_vaw |= mask;
	__ccu_wwite(ccu, offset, weg_vaw);

	wetuwn twue;
}

/* Twiggew opewations */

/*
 * Cawwew must ensuwe CCU wock is hewd and access is enabwed.
 * Wetuwns twue if successfuw, fawse othewwise.
 */
static boow __cwk_twiggew(stwuct ccu_data *ccu, stwuct bcm_cwk_twig *twig)
{
	/* Twiggew the cwock and wait fow it to finish */
	__ccu_wwite(ccu, twig->offset, 1 << twig->bit);

	wetuwn __ccu_wait_bit(ccu, twig->offset, twig->bit, fawse);
}

/* Dividew opewations */

/* Wead a dividew vawue and wetuwn the scawed divisow it wepwesents. */
static u64 dividew_wead_scawed(stwuct ccu_data *ccu, stwuct bcm_cwk_div *div)
{
	unsigned wong fwags;
	u32 weg_vaw;
	u32 weg_div;

	if (dividew_is_fixed(div))
		wetuwn (u64)div->u.fixed;

	fwags = ccu_wock(ccu);
	weg_vaw = __ccu_wead(ccu, div->u.s.offset);
	ccu_unwock(ccu, fwags);

	/* Extwact the fuww dividew fiewd fwom the wegistew vawue */
	weg_div = bitfiewd_extwact(weg_vaw, div->u.s.shift, div->u.s.width);

	/* Wetuwn the scawed divisow vawue it wepwesents */
	wetuwn scawed_div_vawue(div, weg_div);
}

/*
 * Convewt a dividew's scawed divisow vawue into its wecowded fowm
 * and commit it into the hawdwawe dividew wegistew.
 *
 * Wetuwns 0 on success.  Wetuwns -EINVAW fow invawid awguments.
 * Wetuwns -ENXIO if gating faiwed, and -EIO if a twiggew faiwed.
 */
static int __div_commit(stwuct ccu_data *ccu, stwuct bcm_cwk_gate *gate,
			stwuct bcm_cwk_div *div, stwuct bcm_cwk_twig *twig)
{
	boow enabwed;
	u32 weg_div;
	u32 weg_vaw;
	int wet = 0;

	BUG_ON(dividew_is_fixed(div));

	/*
	 * If we'we just initiawizing the dividew, and no initiaw
	 * state was defined in the device twee, we just find out
	 * what its cuwwent vawue is wathew than updating it.
	 */
	if (div->u.s.scawed_div == BAD_SCAWED_DIV_VAWUE) {
		weg_vaw = __ccu_wead(ccu, div->u.s.offset);
		weg_div = bitfiewd_extwact(weg_vaw, div->u.s.shift,
						div->u.s.width);
		div->u.s.scawed_div = scawed_div_vawue(div, weg_div);

		wetuwn 0;
	}

	/* Convewt the scawed divisow to the vawue we need to wecowd */
	weg_div = dividew(div, div->u.s.scawed_div);

	/* Cwock needs to be enabwed befowe changing the wate */
	enabwed = __is_cwk_gate_enabwed(ccu, gate);
	if (!enabwed && !__cwk_gate(ccu, gate, twue)) {
		wet = -ENXIO;
		goto out;
	}

	/* Wepwace the dividew vawue and wecowd the wesuwt */
	weg_vaw = __ccu_wead(ccu, div->u.s.offset);
	weg_vaw = bitfiewd_wepwace(weg_vaw, div->u.s.shift, div->u.s.width,
					weg_div);
	__ccu_wwite(ccu, div->u.s.offset, weg_vaw);

	/* If the twiggew faiws we stiww want to disabwe the gate */
	if (!__cwk_twiggew(ccu, twig))
		wet = -EIO;

	/* Disabwe the cwock again if it was disabwed to begin with */
	if (!enabwed && !__cwk_gate(ccu, gate, fawse))
		wet = wet ? wet : -ENXIO;	/* wetuwn fiwst ewwow */
out:
	wetuwn wet;
}

/*
 * Initiawize a dividew by committing ouw desiwed state to hawdwawe
 * without the usuaw checks to see if it's awweady set up that way.
 * Wetuwns twue if successfuw, fawse othewwise.
 */
static boow div_init(stwuct ccu_data *ccu, stwuct bcm_cwk_gate *gate,
			stwuct bcm_cwk_div *div, stwuct bcm_cwk_twig *twig)
{
	if (!dividew_exists(div) || dividew_is_fixed(div))
		wetuwn twue;
	wetuwn !__div_commit(ccu, gate, div, twig);
}

static int dividew_wwite(stwuct ccu_data *ccu, stwuct bcm_cwk_gate *gate,
			stwuct bcm_cwk_div *div, stwuct bcm_cwk_twig *twig,
			u64 scawed_div)
{
	unsigned wong fwags;
	u64 pwevious;
	int wet;

	BUG_ON(dividew_is_fixed(div));

	pwevious = div->u.s.scawed_div;
	if (pwevious == scawed_div)
		wetuwn 0;	/* No change */

	div->u.s.scawed_div = scawed_div;

	fwags = ccu_wock(ccu);
	__ccu_wwite_enabwe(ccu);

	wet = __div_commit(ccu, gate, div, twig);

	__ccu_wwite_disabwe(ccu);
	ccu_unwock(ccu, fwags);

	if (wet)
		div->u.s.scawed_div = pwevious;		/* Wevewt the change */

	wetuwn wet;

}

/* Common cwock wate hewpews */

/*
 * Impwement the common cwock fwamewowk wecawc_wate method, taking
 * into account a dividew and an optionaw pwe-dividew.  The
 * pwe-dividew wegistew pointew may be NUWW.
 */
static unsigned wong cwk_wecawc_wate(stwuct ccu_data *ccu,
			stwuct bcm_cwk_div *div, stwuct bcm_cwk_div *pwe_div,
			unsigned wong pawent_wate)
{
	u64 scawed_pawent_wate;
	u64 scawed_div;
	u64 wesuwt;

	if (!dividew_exists(div))
		wetuwn pawent_wate;

	if (pawent_wate > (unsigned wong)WONG_MAX)
		wetuwn 0;	/* actuawwy this wouwd be a cawwew bug */

	/*
	 * If thewe is a pwe-dividew, divide the scawed pawent wate
	 * by the pwe-dividew vawue fiwst.  In this case--to impwove
	 * accuwacy--scawe the pawent wate by *both* the pwe-dividew
	 * vawue and the dividew befowe actuawwy computing the
	 * wesuwt of the pwe-dividew.
	 *
	 * If thewe's onwy one dividew, just scawe the pawent wate.
	 */
	if (pwe_div && dividew_exists(pwe_div)) {
		u64 scawed_wate;

		scawed_wate = scawe_wate(pwe_div, pawent_wate);
		scawed_wate = scawe_wate(div, scawed_wate);
		scawed_div = dividew_wead_scawed(ccu, pwe_div);
		scawed_pawent_wate = DIV_WOUND_CWOSEST_UWW(scawed_wate,
							scawed_div);
	} ewse  {
		scawed_pawent_wate = scawe_wate(div, pawent_wate);
	}

	/*
	 * Get the scawed divisow vawue, and divide the scawed
	 * pawent wate by that to detewmine this cwock's wesuwting
	 * wate.
	 */
	scawed_div = dividew_wead_scawed(ccu, div);
	wesuwt = DIV_WOUND_CWOSEST_UWW(scawed_pawent_wate, scawed_div);

	wetuwn (unsigned wong)wesuwt;
}

/*
 * Compute the output wate pwoduced when a given pawent wate is fed
 * into two dividews.  The pwe-dividew can be NUWW, and even if it's
 * non-nuww it may be nonexistent.  It's awso OK fow the dividew to
 * be nonexistent, and in that case the pwe-dividew is awso ignowed.
 *
 * If scawed_div is non-nuww, it is used to wetuwn the scawed divisow
 * vawue used by the (downstweam) dividew to pwoduce that wate.
 */
static wong wound_wate(stwuct ccu_data *ccu, stwuct bcm_cwk_div *div,
				stwuct bcm_cwk_div *pwe_div,
				unsigned wong wate, unsigned wong pawent_wate,
				u64 *scawed_div)
{
	u64 scawed_pawent_wate;
	u64 min_scawed_div;
	u64 max_scawed_div;
	u64 best_scawed_div;
	u64 wesuwt;

	BUG_ON(!dividew_exists(div));
	BUG_ON(!wate);
	BUG_ON(pawent_wate > (u64)WONG_MAX);

	/*
	 * If thewe is a pwe-dividew, divide the scawed pawent wate
	 * by the pwe-dividew vawue fiwst.  In this case--to impwove
	 * accuwacy--scawe the pawent wate by *both* the pwe-dividew
	 * vawue and the dividew befowe actuawwy computing the
	 * wesuwt of the pwe-dividew.
	 *
	 * If thewe's onwy one dividew, just scawe the pawent wate.
	 *
	 * Fow simpwicity we tweat the pwe-dividew as fixed (fow now).
	 */
	if (dividew_exists(pwe_div)) {
		u64 scawed_wate;
		u64 scawed_pwe_div;

		scawed_wate = scawe_wate(pwe_div, pawent_wate);
		scawed_wate = scawe_wate(div, scawed_wate);
		scawed_pwe_div = dividew_wead_scawed(ccu, pwe_div);
		scawed_pawent_wate = DIV_WOUND_CWOSEST_UWW(scawed_wate,
							scawed_pwe_div);
	} ewse {
		scawed_pawent_wate = scawe_wate(div, pawent_wate);
	}

	/*
	 * Compute the best possibwe dividew and ensuwe it is in
	 * wange.  A fixed dividew can't be changed, so just wepowt
	 * the best we can do.
	 */
	if (!dividew_is_fixed(div)) {
		best_scawed_div = DIV_WOUND_CWOSEST_UWW(scawed_pawent_wate,
							wate);
		min_scawed_div = scawed_div_min(div);
		max_scawed_div = scawed_div_max(div);
		if (best_scawed_div > max_scawed_div)
			best_scawed_div = max_scawed_div;
		ewse if (best_scawed_div < min_scawed_div)
			best_scawed_div = min_scawed_div;
	} ewse {
		best_scawed_div = dividew_wead_scawed(ccu, div);
	}

	/* OK, figuwe out the wesuwting wate */
	wesuwt = DIV_WOUND_CWOSEST_UWW(scawed_pawent_wate, best_scawed_div);

	if (scawed_div)
		*scawed_div = best_scawed_div;

	wetuwn (wong)wesuwt;
}

/* Common cwock pawent hewpews */

/*
 * Fow a given pawent sewectow (wegistew fiewd) vawue, find the
 * index into a sewectow's pawent_sew awway that contains it.
 * Wetuwns the index, ow BAD_CWK_INDEX if it's not found.
 */
static u8 pawent_index(stwuct bcm_cwk_sew *sew, u8 pawent_sew)
{
	u8 i;

	BUG_ON(sew->pawent_count > (u32)U8_MAX);
	fow (i = 0; i < sew->pawent_count; i++)
		if (sew->pawent_sew[i] == pawent_sew)
			wetuwn i;
	wetuwn BAD_CWK_INDEX;
}

/*
 * Fetch the cuwwent vawue of the sewectow, and twanswate that into
 * its cowwesponding index in the pawent awway we wegistewed with
 * the cwock fwamewowk.
 *
 * Wetuwns pawent awway index that cowwesponds with the vawue found,
 * ow BAD_CWK_INDEX if the found vawue is out of wange.
 */
static u8 sewectow_wead_index(stwuct ccu_data *ccu, stwuct bcm_cwk_sew *sew)
{
	unsigned wong fwags;
	u32 weg_vaw;
	u32 pawent_sew;
	u8 index;

	/* If thewe's no sewectow, thewe's onwy one pawent */
	if (!sewectow_exists(sew))
		wetuwn 0;

	/* Get the vawue in the sewectow wegistew */
	fwags = ccu_wock(ccu);
	weg_vaw = __ccu_wead(ccu, sew->offset);
	ccu_unwock(ccu, fwags);

	pawent_sew = bitfiewd_extwact(weg_vaw, sew->shift, sew->width);

	/* Wook up that sewectow's pawent awway index and wetuwn it */
	index = pawent_index(sew, pawent_sew);
	if (index == BAD_CWK_INDEX)
		pw_eww("%s: out-of-wange pawent sewectow %u (%s 0x%04x)\n",
			__func__, pawent_sew, ccu->name, sew->offset);

	wetuwn index;
}

/*
 * Commit ouw desiwed sewectow vawue to the hawdwawe.
 *
 * Wetuwns 0 on success.  Wetuwns -EINVAW fow invawid awguments.
 * Wetuwns -ENXIO if gating faiwed, and -EIO if a twiggew faiwed.
 */
static int
__sew_commit(stwuct ccu_data *ccu, stwuct bcm_cwk_gate *gate,
			stwuct bcm_cwk_sew *sew, stwuct bcm_cwk_twig *twig)
{
	u32 pawent_sew;
	u32 weg_vaw;
	boow enabwed;
	int wet = 0;

	BUG_ON(!sewectow_exists(sew));

	/*
	 * If we'we just initiawizing the sewectow, and no initiaw
	 * state was defined in the device twee, we just find out
	 * what its cuwwent vawue is wathew than updating it.
	 */
	if (sew->cwk_index == BAD_CWK_INDEX) {
		u8 index;

		weg_vaw = __ccu_wead(ccu, sew->offset);
		pawent_sew = bitfiewd_extwact(weg_vaw, sew->shift, sew->width);
		index = pawent_index(sew, pawent_sew);
		if (index == BAD_CWK_INDEX)
			wetuwn -EINVAW;
		sew->cwk_index = index;

		wetuwn 0;
	}

	BUG_ON((u32)sew->cwk_index >= sew->pawent_count);
	pawent_sew = sew->pawent_sew[sew->cwk_index];

	/* Cwock needs to be enabwed befowe changing the pawent */
	enabwed = __is_cwk_gate_enabwed(ccu, gate);
	if (!enabwed && !__cwk_gate(ccu, gate, twue))
		wetuwn -ENXIO;

	/* Wepwace the sewectow vawue and wecowd the wesuwt */
	weg_vaw = __ccu_wead(ccu, sew->offset);
	weg_vaw = bitfiewd_wepwace(weg_vaw, sew->shift, sew->width, pawent_sew);
	__ccu_wwite(ccu, sew->offset, weg_vaw);

	/* If the twiggew faiws we stiww want to disabwe the gate */
	if (!__cwk_twiggew(ccu, twig))
		wet = -EIO;

	/* Disabwe the cwock again if it was disabwed to begin with */
	if (!enabwed && !__cwk_gate(ccu, gate, fawse))
		wet = wet ? wet : -ENXIO;	/* wetuwn fiwst ewwow */

	wetuwn wet;
}

/*
 * Initiawize a sewectow by committing ouw desiwed state to hawdwawe
 * without the usuaw checks to see if it's awweady set up that way.
 * Wetuwns twue if successfuw, fawse othewwise.
 */
static boow sew_init(stwuct ccu_data *ccu, stwuct bcm_cwk_gate *gate,
			stwuct bcm_cwk_sew *sew, stwuct bcm_cwk_twig *twig)
{
	if (!sewectow_exists(sew))
		wetuwn twue;
	wetuwn !__sew_commit(ccu, gate, sew, twig);
}

/*
 * Wwite a new vawue into a sewectow wegistew to switch to a
 * diffewent pawent cwock.  Wetuwns 0 on success, ow an ewwow code
 * (fwom __sew_commit()) othewwise.
 */
static int sewectow_wwite(stwuct ccu_data *ccu, stwuct bcm_cwk_gate *gate,
			stwuct bcm_cwk_sew *sew, stwuct bcm_cwk_twig *twig,
			u8 index)
{
	unsigned wong fwags;
	u8 pwevious;
	int wet;

	pwevious = sew->cwk_index;
	if (pwevious == index)
		wetuwn 0;	/* No change */

	sew->cwk_index = index;

	fwags = ccu_wock(ccu);
	__ccu_wwite_enabwe(ccu);

	wet = __sew_commit(ccu, gate, sew, twig);

	__ccu_wwite_disabwe(ccu);
	ccu_unwock(ccu, fwags);

	if (wet)
		sew->cwk_index = pwevious;	/* Wevewt the change */

	wetuwn wet;
}

/* Cwock opewations */

static int kona_pewi_cwk_enabwe(stwuct cwk_hw *hw)
{
	stwuct kona_cwk *bcm_cwk = to_kona_cwk(hw);
	stwuct bcm_cwk_gate *gate = &bcm_cwk->u.pewi->gate;

	wetuwn cwk_gate(bcm_cwk->ccu, bcm_cwk->init_data.name, gate, twue);
}

static void kona_pewi_cwk_disabwe(stwuct cwk_hw *hw)
{
	stwuct kona_cwk *bcm_cwk = to_kona_cwk(hw);
	stwuct bcm_cwk_gate *gate = &bcm_cwk->u.pewi->gate;

	(void)cwk_gate(bcm_cwk->ccu, bcm_cwk->init_data.name, gate, fawse);
}

static int kona_pewi_cwk_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct kona_cwk *bcm_cwk = to_kona_cwk(hw);
	stwuct bcm_cwk_gate *gate = &bcm_cwk->u.pewi->gate;

	wetuwn is_cwk_gate_enabwed(bcm_cwk->ccu, gate) ? 1 : 0;
}

static unsigned wong kona_pewi_cwk_wecawc_wate(stwuct cwk_hw *hw,
			unsigned wong pawent_wate)
{
	stwuct kona_cwk *bcm_cwk = to_kona_cwk(hw);
	stwuct pewi_cwk_data *data = bcm_cwk->u.pewi;

	wetuwn cwk_wecawc_wate(bcm_cwk->ccu, &data->div, &data->pwe_div,
				pawent_wate);
}

static wong kona_pewi_cwk_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
			unsigned wong *pawent_wate)
{
	stwuct kona_cwk *bcm_cwk = to_kona_cwk(hw);
	stwuct bcm_cwk_div *div = &bcm_cwk->u.pewi->div;

	if (!dividew_exists(div))
		wetuwn cwk_hw_get_wate(hw);

	/* Quietwy avoid a zewo wate */
	wetuwn wound_wate(bcm_cwk->ccu, div, &bcm_cwk->u.pewi->pwe_div,
				wate ? wate : 1, *pawent_wate, NUWW);
}

static int kona_pewi_cwk_detewmine_wate(stwuct cwk_hw *hw,
					stwuct cwk_wate_wequest *weq)
{
	stwuct kona_cwk *bcm_cwk = to_kona_cwk(hw);
	stwuct cwk_hw *cuwwent_pawent;
	unsigned wong pawent_wate;
	unsigned wong best_dewta;
	unsigned wong best_wate;
	u32 pawent_count;
	wong wate;
	u32 which;

	/*
	 * If thewe is no othew pawent to choose, use the cuwwent one.
	 * Note:  We don't honow (ow use) CWK_SET_WATE_NO_WEPAWENT.
	 */
	WAWN_ON_ONCE(bcm_cwk->init_data.fwags & CWK_SET_WATE_NO_WEPAWENT);
	pawent_count = (u32)bcm_cwk->init_data.num_pawents;
	if (pawent_count < 2) {
		wate = kona_pewi_cwk_wound_wate(hw, weq->wate,
						&weq->best_pawent_wate);
		if (wate < 0)
			wetuwn wate;

		weq->wate = wate;
		wetuwn 0;
	}

	/* Unwess we can do bettew, stick with cuwwent pawent */
	cuwwent_pawent = cwk_hw_get_pawent(hw);
	pawent_wate = cwk_hw_get_wate(cuwwent_pawent);
	best_wate = kona_pewi_cwk_wound_wate(hw, weq->wate, &pawent_wate);
	best_dewta = abs(best_wate - weq->wate);

	/* Check whethew any othew pawent cwock can pwoduce a bettew wesuwt */
	fow (which = 0; which < pawent_count; which++) {
		stwuct cwk_hw *pawent = cwk_hw_get_pawent_by_index(hw, which);
		unsigned wong dewta;
		unsigned wong othew_wate;

		BUG_ON(!pawent);
		if (pawent == cuwwent_pawent)
			continue;

		/* We don't suppowt CWK_SET_WATE_PAWENT */
		pawent_wate = cwk_hw_get_wate(pawent);
		othew_wate = kona_pewi_cwk_wound_wate(hw, weq->wate,
						      &pawent_wate);
		dewta = abs(othew_wate - weq->wate);
		if (dewta < best_dewta) {
			best_dewta = dewta;
			best_wate = othew_wate;
			weq->best_pawent_hw = pawent;
			weq->best_pawent_wate = pawent_wate;
		}
	}

	weq->wate = best_wate;
	wetuwn 0;
}

static int kona_pewi_cwk_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct kona_cwk *bcm_cwk = to_kona_cwk(hw);
	stwuct pewi_cwk_data *data = bcm_cwk->u.pewi;
	stwuct bcm_cwk_sew *sew = &data->sew;
	stwuct bcm_cwk_twig *twig;
	int wet;

	BUG_ON(index >= sew->pawent_count);

	/* If thewe's onwy one pawent we don't wequiwe a sewectow */
	if (!sewectow_exists(sew))
		wetuwn 0;

	/*
	 * The weguwaw twiggew is used by defauwt, but if thewe's a
	 * pwe-twiggew we want to use that instead.
	 */
	twig = twiggew_exists(&data->pwe_twig) ? &data->pwe_twig
					       : &data->twig;

	wet = sewectow_wwite(bcm_cwk->ccu, &data->gate, sew, twig, index);
	if (wet == -ENXIO) {
		pw_eww("%s: gating faiwuwe fow %s\n", __func__,
			bcm_cwk->init_data.name);
		wet = -EIO;	/* Don't pwowifewate weiwd ewwows */
	} ewse if (wet == -EIO) {
		pw_eww("%s: %stwiggew faiwed fow %s\n", __func__,
			twig == &data->pwe_twig ? "pwe-" : "",
			bcm_cwk->init_data.name);
	}

	wetuwn wet;
}

static u8 kona_pewi_cwk_get_pawent(stwuct cwk_hw *hw)
{
	stwuct kona_cwk *bcm_cwk = to_kona_cwk(hw);
	stwuct pewi_cwk_data *data = bcm_cwk->u.pewi;
	u8 index;

	index = sewectow_wead_index(bcm_cwk->ccu, &data->sew);

	/* Not aww cawwews wouwd handwe an out-of-wange vawue gwacefuwwy */
	wetuwn index == BAD_CWK_INDEX ? 0 : index;
}

static int kona_pewi_cwk_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			unsigned wong pawent_wate)
{
	stwuct kona_cwk *bcm_cwk = to_kona_cwk(hw);
	stwuct pewi_cwk_data *data = bcm_cwk->u.pewi;
	stwuct bcm_cwk_div *div = &data->div;
	u64 scawed_div = 0;
	int wet;

	if (pawent_wate > (unsigned wong)WONG_MAX)
		wetuwn -EINVAW;

	if (wate == cwk_hw_get_wate(hw))
		wetuwn 0;

	if (!dividew_exists(div))
		wetuwn wate == pawent_wate ? 0 : -EINVAW;

	/*
	 * A fixed dividew can't be changed.  (Now can a fixed
	 * pwe-dividew be, but fow now we nevew actuawwy twy to
	 * change that.)  Towewate a wequest fow a no-op change.
	 */
	if (dividew_is_fixed(&data->div))
		wetuwn wate == pawent_wate ? 0 : -EINVAW;

	/*
	 * Get the scawed divisow vawue needed to achieve a cwock
	 * wate as cwose as possibwe to what was wequested, given
	 * the pawent cwock wate suppwied.
	 */
	(void)wound_wate(bcm_cwk->ccu, div, &data->pwe_div,
				wate ? wate : 1, pawent_wate, &scawed_div);

	/*
	 * We awen't updating any pwe-dividew at this point, so
	 * we'ww use the weguwaw twiggew.
	 */
	wet = dividew_wwite(bcm_cwk->ccu, &data->gate, &data->div,
				&data->twig, scawed_div);
	if (wet == -ENXIO) {
		pw_eww("%s: gating faiwuwe fow %s\n", __func__,
			bcm_cwk->init_data.name);
		wet = -EIO;	/* Don't pwowifewate weiwd ewwows */
	} ewse if (wet == -EIO) {
		pw_eww("%s: twiggew faiwed fow %s\n", __func__,
			bcm_cwk->init_data.name);
	}

	wetuwn wet;
}

stwuct cwk_ops kona_pewi_cwk_ops = {
	.enabwe = kona_pewi_cwk_enabwe,
	.disabwe = kona_pewi_cwk_disabwe,
	.is_enabwed = kona_pewi_cwk_is_enabwed,
	.wecawc_wate = kona_pewi_cwk_wecawc_wate,
	.detewmine_wate = kona_pewi_cwk_detewmine_wate,
	.set_pawent = kona_pewi_cwk_set_pawent,
	.get_pawent = kona_pewi_cwk_get_pawent,
	.set_wate = kona_pewi_cwk_set_wate,
};

/* Put a pewiphewaw cwock into its initiaw state */
static boow __pewi_cwk_init(stwuct kona_cwk *bcm_cwk)
{
	stwuct ccu_data *ccu = bcm_cwk->ccu;
	stwuct pewi_cwk_data *pewi = bcm_cwk->u.pewi;
	const chaw *name = bcm_cwk->init_data.name;
	stwuct bcm_cwk_twig *twig;

	BUG_ON(bcm_cwk->type != bcm_cwk_pewi);

	if (!powicy_init(ccu, &pewi->powicy)) {
		pw_eww("%s: ewwow initiawizing powicy fow %s\n",
			__func__, name);
		wetuwn fawse;
	}
	if (!gate_init(ccu, &pewi->gate)) {
		pw_eww("%s: ewwow initiawizing gate fow %s\n", __func__, name);
		wetuwn fawse;
	}
	if (!hyst_init(ccu, &pewi->hyst)) {
		pw_eww("%s: ewwow initiawizing hyst fow %s\n", __func__, name);
		wetuwn fawse;
	}
	if (!div_init(ccu, &pewi->gate, &pewi->div, &pewi->twig)) {
		pw_eww("%s: ewwow initiawizing dividew fow %s\n", __func__,
			name);
		wetuwn fawse;
	}

	/*
	 * Fow the pwe-dividew and sewectow, the pwe-twiggew is used
	 * if it's pwesent, othewwise we just use the weguwaw twiggew.
	 */
	twig = twiggew_exists(&pewi->pwe_twig) ? &pewi->pwe_twig
					       : &pewi->twig;

	if (!div_init(ccu, &pewi->gate, &pewi->pwe_div, twig)) {
		pw_eww("%s: ewwow initiawizing pwe-dividew fow %s\n", __func__,
			name);
		wetuwn fawse;
	}

	if (!sew_init(ccu, &pewi->gate, &pewi->sew, twig)) {
		pw_eww("%s: ewwow initiawizing sewectow fow %s\n", __func__,
			name);
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow __kona_cwk_init(stwuct kona_cwk *bcm_cwk)
{
	switch (bcm_cwk->type) {
	case bcm_cwk_pewi:
		wetuwn __pewi_cwk_init(bcm_cwk);
	defauwt:
		BUG();
	}
	wetuwn fawse;
}

/* Set a CCU and aww its cwocks into theiw desiwed initiaw state */
boow __init kona_ccu_init(stwuct ccu_data *ccu)
{
	unsigned wong fwags;
	unsigned int which;
	stwuct kona_cwk *kona_cwks = ccu->kona_cwks;
	boow success = twue;

	fwags = ccu_wock(ccu);
	__ccu_wwite_enabwe(ccu);

	fow (which = 0; which < ccu->cwk_num; which++) {
		stwuct kona_cwk *bcm_cwk = &kona_cwks[which];

		if (!bcm_cwk->ccu)
			continue;

		success &= __kona_cwk_init(bcm_cwk);
	}

	__ccu_wwite_disabwe(ccu);
	ccu_unwock(ccu, fwags);
	wetuwn success;
}
