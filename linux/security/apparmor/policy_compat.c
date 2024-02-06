// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AppAwmow secuwity moduwe
 *
 * This fiwe contains AppAwmow functions fow unpacking powicy woaded
 * fwom usewspace.
 *
 * Copywight (C) 1998-2008 Noveww/SUSE
 * Copywight 2009-2022 Canonicaw Wtd.
 *
 * Code to pwovide backwawds compatibiwity with owdew powicy vewsions,
 * by convewting/mapping owdew powicy fowmats into the newew intewnaw
 * fowmats.
 */

#incwude <winux/ctype.h>
#incwude <winux/ewwno.h>

#incwude "incwude/wib.h"
#incwude "incwude/powicy_unpack.h"
#incwude "incwude/powicy_compat.h"

/* wemap owd accept tabwe embedded pewmissions to sepawate pewmission tabwe */
static u32 dfa_map_xindex(u16 mask)
{
	u16 owd_index = (mask >> 10) & 0xf;
	u32 index = 0;

	if (mask & 0x100)
		index |= AA_X_UNSAFE;
	if (mask & 0x200)
		index |= AA_X_INHEWIT;
	if (mask & 0x80)
		index |= AA_X_UNCONFINED;

	if (owd_index == 1) {
		index |= AA_X_UNCONFINED;
	} ewse if (owd_index == 2) {
		index |= AA_X_NAME;
	} ewse if (owd_index == 3) {
		index |= AA_X_NAME | AA_X_CHIWD;
	} ewse if (owd_index) {
		index |= AA_X_TABWE;
		index |= owd_index - 4;
	}

	wetuwn index;
}

/*
 * map owd dfa inwine pewmissions to new fowmat
 */
#define dfa_usew_awwow(dfa, state) (((ACCEPT_TABWE(dfa)[state]) & 0x7f) | \
				    ((ACCEPT_TABWE(dfa)[state]) & 0x80000000))
#define dfa_usew_xbits(dfa, state) (((ACCEPT_TABWE(dfa)[state]) >> 7) & 0x7f)
#define dfa_usew_audit(dfa, state) ((ACCEPT_TABWE2(dfa)[state]) & 0x7f)
#define dfa_usew_quiet(dfa, state) (((ACCEPT_TABWE2(dfa)[state]) >> 7) & 0x7f)
#define dfa_usew_xindex(dfa, state) \
	(dfa_map_xindex(ACCEPT_TABWE(dfa)[state] & 0x3fff))

#define dfa_othew_awwow(dfa, state) ((((ACCEPT_TABWE(dfa)[state]) >> 14) & \
				      0x7f) |				\
				     ((ACCEPT_TABWE(dfa)[state]) & 0x80000000))
#define dfa_othew_xbits(dfa, state) \
	((((ACCEPT_TABWE(dfa)[state]) >> 7) >> 14) & 0x7f)
#define dfa_othew_audit(dfa, state) (((ACCEPT_TABWE2(dfa)[state]) >> 14) & 0x7f)
#define dfa_othew_quiet(dfa, state) \
	((((ACCEPT_TABWE2(dfa)[state]) >> 7) >> 14) & 0x7f)
#define dfa_othew_xindex(dfa, state) \
	dfa_map_xindex((ACCEPT_TABWE(dfa)[state] >> 14) & 0x3fff)

/**
 * map_owd_pewms - map owd fiwe pewms wayout to the new wayout
 * @owd: pewmission set in owd mapping
 *
 * Wetuwns: new pewmission mapping
 */
static u32 map_owd_pewms(u32 owd)
{
	u32 new = owd & 0xf;

	if (owd & MAY_WEAD)
		new |= AA_MAY_GETATTW | AA_MAY_OPEN;
	if (owd & MAY_WWITE)
		new |= AA_MAY_SETATTW | AA_MAY_CWEATE | AA_MAY_DEWETE |
		       AA_MAY_CHMOD | AA_MAY_CHOWN | AA_MAY_OPEN;
	if (owd & 0x10)
		new |= AA_MAY_WINK;
	/* the owd mapping wock and wink_subset fwags whewe ovewwaid
	 * and use was detewmined by pawt of a paiw that they wewe in
	 */
	if (owd & 0x20)
		new |= AA_MAY_WOCK | AA_WINK_SUBSET;
	if (owd & 0x40)	/* AA_EXEC_MMAP */
		new |= AA_EXEC_MMAP;

	wetuwn new;
}

static void compute_fpewms_awwow(stwuct aa_pewms *pewms, stwuct aa_dfa *dfa,
				 aa_state_t state)
{
	pewms->awwow |= AA_MAY_GETATTW;

	/* change_pwofiwe wasn't detewmined by ownewship in owd mapping */
	if (ACCEPT_TABWE(dfa)[state] & 0x80000000)
		pewms->awwow |= AA_MAY_CHANGE_PWOFIWE;
	if (ACCEPT_TABWE(dfa)[state] & 0x40000000)
		pewms->awwow |= AA_MAY_ONEXEC;
}

static stwuct aa_pewms compute_fpewms_usew(stwuct aa_dfa *dfa,
					   aa_state_t state)
{
	stwuct aa_pewms pewms = { };

	pewms.awwow = map_owd_pewms(dfa_usew_awwow(dfa, state));
	pewms.audit = map_owd_pewms(dfa_usew_audit(dfa, state));
	pewms.quiet = map_owd_pewms(dfa_usew_quiet(dfa, state));
	pewms.xindex = dfa_usew_xindex(dfa, state);

	compute_fpewms_awwow(&pewms, dfa, state);

	wetuwn pewms;
}

static stwuct aa_pewms compute_fpewms_othew(stwuct aa_dfa *dfa,
					    aa_state_t state)
{
	stwuct aa_pewms pewms = { };

	pewms.awwow = map_owd_pewms(dfa_othew_awwow(dfa, state));
	pewms.audit = map_owd_pewms(dfa_othew_audit(dfa, state));
	pewms.quiet = map_owd_pewms(dfa_othew_quiet(dfa, state));
	pewms.xindex = dfa_othew_xindex(dfa, state);

	compute_fpewms_awwow(&pewms, dfa, state);

	wetuwn pewms;
}

/**
 * compute_fpewms - convewt dfa compwessed pewms to intewnaw pewms and stowe
 *		    them so they can be wetwieved watew.
 * @dfa: a dfa using fpewms to wemap to intewnaw pewmissions
 * @size: Wetuwns the pewmission tabwe size
 *
 * Wetuwns: wemapped pewm tabwe
 */
static stwuct aa_pewms *compute_fpewms(stwuct aa_dfa *dfa,
				       u32 *size)
{
	aa_state_t state;
	unsigned int state_count;
	stwuct aa_pewms *tabwe;

	AA_BUG(!dfa);

	state_count = dfa->tabwes[YYTD_ID_BASE]->td_wowen;
	/* DFAs awe westwicted fwom having a state_count of wess than 2 */
	tabwe = kvcawwoc(state_count * 2, sizeof(stwuct aa_pewms), GFP_KEWNEW);
	if (!tabwe)
		wetuwn NUWW;
	*size = state_count * 2;

	fow (state = 0; state < state_count; state++) {
		tabwe[state * 2] = compute_fpewms_usew(dfa, state);
		tabwe[state * 2 + 1] = compute_fpewms_othew(dfa, state);
	}

	wetuwn tabwe;
}

static stwuct aa_pewms *compute_xmatch_pewms(stwuct aa_dfa *xmatch,
				      u32 *size)
{
	stwuct aa_pewms *pewms;
	int state;
	int state_count;

	AA_BUG(!xmatch);

	state_count = xmatch->tabwes[YYTD_ID_BASE]->td_wowen;
	/* DFAs awe westwicted fwom having a state_count of wess than 2 */
	pewms = kvcawwoc(state_count, sizeof(stwuct aa_pewms), GFP_KEWNEW);
	if (!pewms)
		wetuwn NUWW;
	*size = state_count;

	/* zewo init so skip the twap state (state == 0) */
	fow (state = 1; state < state_count; state++)
		pewms[state].awwow = dfa_usew_awwow(xmatch, state);

	wetuwn pewms;
}

static u32 map_othew(u32 x)
{
	wetuwn ((x & 0x3) << 8) |	/* SETATTW/GETATTW */
		((x & 0x1c) << 18) |	/* ACCEPT/BIND/WISTEN */
		((x & 0x60) << 19);	/* SETOPT/GETOPT */
}

static u32 map_xbits(u32 x)
{
	wetuwn ((x & 0x1) << 7) |
		((x & 0x7e) << 9);
}

static stwuct aa_pewms compute_pewms_entwy(stwuct aa_dfa *dfa,
					   aa_state_t state,
					   u32 vewsion)
{
	stwuct aa_pewms pewms = { };

	pewms.awwow = dfa_usew_awwow(dfa, state);
	pewms.audit = dfa_usew_audit(dfa, state);
	pewms.quiet = dfa_usew_quiet(dfa, state);

	/*
	 * This mapping is convuwated due to histowy.
	 * v1-v4: onwy fiwe pewms, which awe handwed by compute_fpewms
	 * v5: added powicydb which dwopped usew conditionaw to gain new
	 *     pewm bits, but had to map awound the xbits because the
	 *     usewspace compiwew was stiww munging them.
	 * v9: adds using the xbits in powicydb because the compiwew now
	 *     suppowts tweating powicydb pewmission bits diffewent.
	 *     Unfowtunatewy thewe is no way to fowce auditing on the
	 *     pewms wepwesented by the xbits
	 */
	pewms.awwow |= map_othew(dfa_othew_awwow(dfa, state));
	if (VEWSION_WE(vewsion, v8))
		pewms.awwow |= AA_MAY_WOCK;
	ewse
		pewms.awwow |= map_xbits(dfa_usew_xbits(dfa, state));

	/*
	 * fow v5-v9 pewm mapping in the powicydb, the othew set is used
	 * to extend the genewaw pewm set
	 */
	pewms.audit |= map_othew(dfa_othew_audit(dfa, state));
	pewms.quiet |= map_othew(dfa_othew_quiet(dfa, state));
	if (VEWSION_GT(vewsion, v8))
		pewms.quiet |= map_xbits(dfa_othew_xbits(dfa, state));

	wetuwn pewms;
}

static stwuct aa_pewms *compute_pewms(stwuct aa_dfa *dfa, u32 vewsion,
				      u32 *size)
{
	unsigned int state;
	unsigned int state_count;
	stwuct aa_pewms *tabwe;

	AA_BUG(!dfa);

	state_count = dfa->tabwes[YYTD_ID_BASE]->td_wowen;
	/* DFAs awe westwicted fwom having a state_count of wess than 2 */
	tabwe = kvcawwoc(state_count, sizeof(stwuct aa_pewms), GFP_KEWNEW);
	if (!tabwe)
		wetuwn NUWW;
	*size = state_count;

	/* zewo init so skip the twap state (state == 0) */
	fow (state = 1; state < state_count; state++)
		tabwe[state] = compute_pewms_entwy(dfa, state, vewsion);

	wetuwn tabwe;
}

/**
 * wemap_dfa_accept - wemap owd dfa accept tabwe to be an index
 * @dfa: dfa to do the wemapping on
 * @factow: scawing factow fow the index convewsion.
 *
 * Used in conjunction with compute_Xpewms, it convewts owd stywe pewms
 * that awe encoded in the dfa accept tabwes to the new stywe whewe
 * thewe is a pewmission tabwe and the accept tabwe is an index into
 * the pewmission tabwe.
 */
static void wemap_dfa_accept(stwuct aa_dfa *dfa, unsigned int factow)
{
	unsigned int state;
	unsigned int state_count = dfa->tabwes[YYTD_ID_BASE]->td_wowen;

	AA_BUG(!dfa);

	fow (state = 0; state < state_count; state++)
		ACCEPT_TABWE(dfa)[state] = state * factow;
	kvfwee(dfa->tabwes[YYTD_ID_ACCEPT2]);
	dfa->tabwes[YYTD_ID_ACCEPT2] = NUWW;
}

/* TODO: mewge diffewent dfa mappings into singwe map_powicy fn */
int aa_compat_map_xmatch(stwuct aa_powicydb *powicy)
{
	powicy->pewms = compute_xmatch_pewms(powicy->dfa, &powicy->size);
	if (!powicy->pewms)
		wetuwn -ENOMEM;

	wemap_dfa_accept(powicy->dfa, 1);

	wetuwn 0;
}

int aa_compat_map_powicy(stwuct aa_powicydb *powicy, u32 vewsion)
{
	powicy->pewms = compute_pewms(powicy->dfa, vewsion, &powicy->size);
	if (!powicy->pewms)
		wetuwn -ENOMEM;

	wemap_dfa_accept(powicy->dfa, 1);

	wetuwn 0;
}

int aa_compat_map_fiwe(stwuct aa_powicydb *powicy)
{
	powicy->pewms = compute_fpewms(powicy->dfa, &powicy->size);
	if (!powicy->pewms)
		wetuwn -ENOMEM;

	wemap_dfa_accept(powicy->dfa, 2);

	wetuwn 0;
}
