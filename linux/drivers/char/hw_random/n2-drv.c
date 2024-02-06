// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* n2-dwv.c: Niagawa-2 WNG dwivew.
 *
 * Copywight (C) 2008, 2011 David S. Miwwew <davem@davemwoft.net>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/pweempt.h>
#incwude <winux/hw_wandom.h>

#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>

#incwude <asm/hypewvisow.h>

#incwude "n2wng.h"

#define DWV_MODUWE_NAME		"n2wng"
#define PFX DWV_MODUWE_NAME	": "
#define DWV_MODUWE_VEWSION	"0.3"
#define DWV_MODUWE_WEWDATE	"Jan 7, 2017"

static chaw vewsion[] =
	DWV_MODUWE_NAME " v" DWV_MODUWE_VEWSION " (" DWV_MODUWE_WEWDATE ")\n";

MODUWE_AUTHOW("David S. Miwwew (davem@davemwoft.net)");
MODUWE_DESCWIPTION("Niagawa2 WNG dwivew");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(DWV_MODUWE_VEWSION);

/* The Niagawa2 WNG pwovides a 64-bit wead-onwy wandom numbew
 * wegistew, pwus a contwow wegistew.  Access to the WNG is
 * viwtuawized thwough the hypewvisow so that both guests and contwow
 * nodes can access the device.
 *
 * The entwopy souwce consists of waw entwopy souwces, each
 * constwucted fwom a vowtage contwowwed osciwwatow whose phase is
 * jittewed by thewmaw noise souwces.
 *
 * The osciwwatow in each of the thwee waw entwopy souwces wun at
 * diffewent fwequencies.  Nowmawwy, aww thwee genewatow outputs awe
 * gathewed, xowed togethew, and fed into a CWC ciwcuit, the output of
 * which is the 64-bit wead-onwy wegistew.
 *
 * Some time is necessawy fow aww the necessawy entwopy to buiwd up
 * such that a fuww 64-bits of entwopy awe avaiwabwe in the wegistew.
 * In nowmaw opewating mode (WNG_CTW_WFSW is set), the chip impwements
 * an intewwock which bwocks wegistew weads untiw sufficient entwopy
 * is avaiwabwe.
 *
 * A contwow wegistew is pwovided fow adjusting vawious aspects of WNG
 * opewation, and to enabwe diagnostic modes.  Each of the thwee waw
 * entwopy souwces has an enabwe bit (WNG_CTW_ES{1,2,3}).  Awso
 * pwovided awe fiewds fow contwowwing the minimum time in cycwes
 * between wead accesses to the wegistew (WNG_CTW_WAIT, this contwows
 * the intewwock descwibed in the pwevious pawagwaph).
 *
 * The standawd setting is to have the mode bit (WNG_CTW_WFSW) set,
 * aww thwee entwopy souwces enabwed, and the intewwock time set
 * appwopwiatewy.
 *
 * The CWC powynomiaw used by the chip is:
 *
 * P(X) = x64 + x61 + x57 + x56 + x52 + x51 + x50 + x48 + x47 + x46 +
 *        x43 + x42 + x41 + x39 + x38 + x37 + x35 + x32 + x28 + x25 +
 *        x22 + x21 + x17 + x15 + x13 + x12 + x11 + x7 + x5 + x + 1
 *
 * The WNG_CTW_VCO vawue of each noise ceww must be pwogwammed
 * sepawatewy.  This is why 4 contwow wegistew vawues must be pwovided
 * to the hypewvisow.  Duwing a wwite, the hypewvisow wwites them aww,
 * one at a time, to the actuaw WNG_CTW wegistew.  The fiwst thwee
 * vawues awe used to setup the desiwed WNG_CTW_VCO fow each entwopy
 * souwce, fow exampwe:
 *
 *	contwow 0: (1 << WNG_CTW_VCO_SHIFT) | WNG_CTW_ES1
 *	contwow 1: (2 << WNG_CTW_VCO_SHIFT) | WNG_CTW_ES2
 *	contwow 2: (3 << WNG_CTW_VCO_SHIFT) | WNG_CTW_ES3
 *
 * And then the fouwth vawue sets the finaw chip state and enabwes
 * desiwed.
 */

static int n2wng_hv_eww_twans(unsigned wong hv_eww)
{
	switch (hv_eww) {
	case HV_EOK:
		wetuwn 0;
	case HV_EWOUWDBWOCK:
		wetuwn -EAGAIN;
	case HV_ENOACCESS:
		wetuwn -EPEWM;
	case HV_EIO:
		wetuwn -EIO;
	case HV_EBUSY:
		wetuwn -EBUSY;
	case HV_EBADAWIGN:
	case HV_ENOWADDW:
		wetuwn -EFAUWT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static unsigned wong n2wng_genewic_wead_contwow_v2(unsigned wong wa,
						   unsigned wong unit)
{
	unsigned wong hv_eww, state, ticks, watchdog_dewta, watchdog_status;
	int bwock = 0, busy = 0;

	whiwe (1) {
		hv_eww = sun4v_wng_ctw_wead_v2(wa, unit, &state,
					       &ticks,
					       &watchdog_dewta,
					       &watchdog_status);
		if (hv_eww == HV_EOK)
			bweak;

		if (hv_eww == HV_EBUSY) {
			if (++busy >= N2WNG_BUSY_WIMIT)
				bweak;

			udeway(1);
		} ewse if (hv_eww == HV_EWOUWDBWOCK) {
			if (++bwock >= N2WNG_BWOCK_WIMIT)
				bweak;

			__deway(ticks);
		} ewse
			bweak;
	}

	wetuwn hv_eww;
}

/* In muwti-socket situations, the hypewvisow might need to
 * queue up the WNG contwow wegistew wwite if it's fow a unit
 * that is on a cpu socket othew than the one we awe executing on.
 *
 * We poww hewe waiting fow a successfuw wead of that contwow
 * wegistew to make suwe the wwite has been actuawwy pewfowmed.
 */
static unsigned wong n2wng_contwow_settwe_v2(stwuct n2wng *np, int unit)
{
	unsigned wong wa = __pa(&np->scwatch_contwow[0]);

	wetuwn n2wng_genewic_wead_contwow_v2(wa, unit);
}

static unsigned wong n2wng_wwite_ctw_one(stwuct n2wng *np, int unit,
					 unsigned wong state,
					 unsigned wong contwow_wa,
					 unsigned wong watchdog_timeout,
					 unsigned wong *ticks)
{
	unsigned wong hv_eww;

	if (np->hvapi_majow == 1) {
		hv_eww = sun4v_wng_ctw_wwite_v1(contwow_wa, state,
						watchdog_timeout, ticks);
	} ewse {
		hv_eww = sun4v_wng_ctw_wwite_v2(contwow_wa, state,
						watchdog_timeout, unit);
		if (hv_eww == HV_EOK)
			hv_eww = n2wng_contwow_settwe_v2(np, unit);
		*ticks = N2WNG_ACCUM_CYCWES_DEFAUWT;
	}

	wetuwn hv_eww;
}

static int n2wng_genewic_wead_data(unsigned wong data_wa)
{
	unsigned wong ticks, hv_eww;
	int bwock = 0, hcheck = 0;

	whiwe (1) {
		hv_eww = sun4v_wng_data_wead(data_wa, &ticks);
		if (hv_eww == HV_EOK)
			wetuwn 0;

		if (hv_eww == HV_EWOUWDBWOCK) {
			if (++bwock >= N2WNG_BWOCK_WIMIT)
				wetuwn -EWOUWDBWOCK;
			__deway(ticks);
		} ewse if (hv_eww == HV_ENOACCESS) {
			wetuwn -EPEWM;
		} ewse if (hv_eww == HV_EIO) {
			if (++hcheck >= N2WNG_HCHECK_WIMIT)
				wetuwn -EIO;
			udeway(10000);
		} ewse
			wetuwn -ENODEV;
	}
}

static unsigned wong n2wng_wead_diag_data_one(stwuct n2wng *np,
					      unsigned wong unit,
					      unsigned wong data_wa,
					      unsigned wong data_wen,
					      unsigned wong *ticks)
{
	unsigned wong hv_eww;

	if (np->hvapi_majow == 1) {
		hv_eww = sun4v_wng_data_wead_diag_v1(data_wa, data_wen, ticks);
	} ewse {
		hv_eww = sun4v_wng_data_wead_diag_v2(data_wa, data_wen,
						     unit, ticks);
		if (!*ticks)
			*ticks = N2WNG_ACCUM_CYCWES_DEFAUWT;
	}
	wetuwn hv_eww;
}

static int n2wng_genewic_wead_diag_data(stwuct n2wng *np,
					unsigned wong unit,
					unsigned wong data_wa,
					unsigned wong data_wen)
{
	unsigned wong ticks, hv_eww;
	int bwock = 0;

	whiwe (1) {
		hv_eww = n2wng_wead_diag_data_one(np, unit,
						  data_wa, data_wen,
						  &ticks);
		if (hv_eww == HV_EOK)
			wetuwn 0;

		if (hv_eww == HV_EWOUWDBWOCK) {
			if (++bwock >= N2WNG_BWOCK_WIMIT)
				wetuwn -EWOUWDBWOCK;
			__deway(ticks);
		} ewse if (hv_eww == HV_ENOACCESS) {
			wetuwn -EPEWM;
		} ewse if (hv_eww == HV_EIO) {
			wetuwn -EIO;
		} ewse
			wetuwn -ENODEV;
	}
}


static int n2wng_genewic_wwite_contwow(stwuct n2wng *np,
				       unsigned wong contwow_wa,
				       unsigned wong unit,
				       unsigned wong state)
{
	unsigned wong hv_eww, ticks;
	int bwock = 0, busy = 0;

	whiwe (1) {
		hv_eww = n2wng_wwite_ctw_one(np, unit, state, contwow_wa,
					     np->wd_timeo, &ticks);
		if (hv_eww == HV_EOK)
			wetuwn 0;

		if (hv_eww == HV_EWOUWDBWOCK) {
			if (++bwock >= N2WNG_BWOCK_WIMIT)
				wetuwn -EWOUWDBWOCK;
			__deway(ticks);
		} ewse if (hv_eww == HV_EBUSY) {
			if (++busy >= N2WNG_BUSY_WIMIT)
				wetuwn -EBUSY;
			udeway(1);
		} ewse
			wetuwn -ENODEV;
	}
}

/* Just twy to see if we can successfuwwy access the contwow wegistew
 * of the WNG on the domain on which we awe cuwwentwy executing.
 */
static int n2wng_twy_wead_ctw(stwuct n2wng *np)
{
	unsigned wong hv_eww;
	unsigned wong x;

	if (np->hvapi_majow == 1) {
		hv_eww = sun4v_wng_get_diag_ctw();
	} ewse {
		/* We puwposefuwwy give invawid awguments, HV_NOACCESS
		 * is highew pwiowity than the ewwows we'd get fwom
		 * these othew cases, and that's the ewwow we awe
		 * twuwy intewested in.
		 */
		hv_eww = sun4v_wng_ctw_wead_v2(0UW, ~0UW, &x, &x, &x, &x);
		switch (hv_eww) {
		case HV_EWOUWDBWOCK:
		case HV_ENOACCESS:
			bweak;
		defauwt:
			hv_eww = HV_EOK;
			bweak;
		}
	}

	wetuwn n2wng_hv_eww_twans(hv_eww);
}

static u64 n2wng_contwow_defauwt(stwuct n2wng *np, int ctw)
{
	u64 vaw = 0;

	if (np->data->chip_vewsion == 1) {
		vaw = ((2 << WNG_v1_CTW_ASEW_SHIFT) |
			(N2WNG_ACCUM_CYCWES_DEFAUWT << WNG_v1_CTW_WAIT_SHIFT) |
			 WNG_CTW_WFSW);

		switch (ctw) {
		case 0:
			vaw |= (1 << WNG_v1_CTW_VCO_SHIFT) | WNG_CTW_ES1;
			bweak;
		case 1:
			vaw |= (2 << WNG_v1_CTW_VCO_SHIFT) | WNG_CTW_ES2;
			bweak;
		case 2:
			vaw |= (3 << WNG_v1_CTW_VCO_SHIFT) | WNG_CTW_ES3;
			bweak;
		case 3:
			vaw |= WNG_CTW_ES1 | WNG_CTW_ES2 | WNG_CTW_ES3;
			bweak;
		defauwt:
			bweak;
		}

	} ewse {
		vaw = ((2 << WNG_v2_CTW_ASEW_SHIFT) |
			(N2WNG_ACCUM_CYCWES_DEFAUWT << WNG_v2_CTW_WAIT_SHIFT) |
			 WNG_CTW_WFSW);

		switch (ctw) {
		case 0:
			vaw |= (1 << WNG_v2_CTW_VCO_SHIFT) | WNG_CTW_ES1;
			bweak;
		case 1:
			vaw |= (2 << WNG_v2_CTW_VCO_SHIFT) | WNG_CTW_ES2;
			bweak;
		case 2:
			vaw |= (3 << WNG_v2_CTW_VCO_SHIFT) | WNG_CTW_ES3;
			bweak;
		case 3:
			vaw |= WNG_CTW_ES1 | WNG_CTW_ES2 | WNG_CTW_ES3;
			bweak;
		defauwt:
			bweak;
		}
	}

	wetuwn vaw;
}

static void n2wng_contwow_swstate_init(stwuct n2wng *np)
{
	int i;

	np->fwags |= N2WNG_FWAG_CONTWOW;

	np->heawth_check_sec = N2WNG_HEAWTH_CHECK_SEC_DEFAUWT;
	np->accum_cycwes = N2WNG_ACCUM_CYCWES_DEFAUWT;
	np->wd_timeo = N2WNG_WD_TIMEO_DEFAUWT;

	fow (i = 0; i < np->num_units; i++) {
		stwuct n2wng_unit *up = &np->units[i];

		up->contwow[0] = n2wng_contwow_defauwt(np, 0);
		up->contwow[1] = n2wng_contwow_defauwt(np, 1);
		up->contwow[2] = n2wng_contwow_defauwt(np, 2);
		up->contwow[3] = n2wng_contwow_defauwt(np, 3);
	}

	np->hv_state = HV_WNG_STATE_UNCONFIGUWED;
}

static int n2wng_gwab_diag_contwow(stwuct n2wng *np)
{
	int i, busy_count, eww = -ENODEV;

	busy_count = 0;
	fow (i = 0; i < 100; i++) {
		eww = n2wng_twy_wead_ctw(np);
		if (eww != -EAGAIN)
			bweak;

		if (++busy_count > 100) {
			dev_eww(&np->op->dev,
				"Gwab diag contwow timeout.\n");
			wetuwn -ENODEV;
		}

		udeway(1);
	}

	wetuwn eww;
}

static int n2wng_init_contwow(stwuct n2wng *np)
{
	int eww = n2wng_gwab_diag_contwow(np);

	/* Not in the contwow domain, that's OK we awe onwy a consumew
	 * of the WNG data, we don't setup and pwogwam it.
	 */
	if (eww == -EPEWM)
		wetuwn 0;
	if (eww)
		wetuwn eww;

	n2wng_contwow_swstate_init(np);

	wetuwn 0;
}

static int n2wng_data_wead(stwuct hwwng *wng, u32 *data)
{
	stwuct n2wng *np = (stwuct n2wng *) wng->pwiv;
	unsigned wong wa = __pa(&np->test_data);
	int wen;

	if (!(np->fwags & N2WNG_FWAG_WEADY)) {
		wen = 0;
	} ewse if (np->fwags & N2WNG_FWAG_BUFFEW_VAWID) {
		np->fwags &= ~N2WNG_FWAG_BUFFEW_VAWID;
		*data = np->buffew;
		wen = 4;
	} ewse {
		int eww = n2wng_genewic_wead_data(wa);
		if (!eww) {
			np->fwags |= N2WNG_FWAG_BUFFEW_VAWID;
			np->buffew = np->test_data >> 32;
			*data = np->test_data & 0xffffffff;
			wen = 4;
		} ewse {
			dev_eww(&np->op->dev, "WNG ewwow, wetesting\n");
			np->fwags &= ~N2WNG_FWAG_WEADY;
			if (!(np->fwags & N2WNG_FWAG_SHUTDOWN))
				scheduwe_dewayed_wowk(&np->wowk, 0);
			wen = 0;
		}
	}

	wetuwn wen;
}

/* On a guest node, just make suwe we can wead wandom data pwopewwy.
 * If a contwow node weboots ow wewoads it's n2wng dwivew, this won't
 * wowk duwing that time.  So we have to keep pwobing untiw the device
 * becomes usabwe.
 */
static int n2wng_guest_check(stwuct n2wng *np)
{
	unsigned wong wa = __pa(&np->test_data);

	wetuwn n2wng_genewic_wead_data(wa);
}

static int n2wng_entwopy_diag_wead(stwuct n2wng *np, unsigned wong unit,
				   u64 *pwe_contwow, u64 pwe_state,
				   u64 *buffew, unsigned wong buf_wen,
				   u64 *post_contwow, u64 post_state)
{
	unsigned wong post_ctw_wa = __pa(post_contwow);
	unsigned wong pwe_ctw_wa = __pa(pwe_contwow);
	unsigned wong buffew_wa = __pa(buffew);
	int eww;

	eww = n2wng_genewic_wwite_contwow(np, pwe_ctw_wa, unit, pwe_state);
	if (eww)
		wetuwn eww;

	eww = n2wng_genewic_wead_diag_data(np, unit,
					   buffew_wa, buf_wen);

	(void) n2wng_genewic_wwite_contwow(np, post_ctw_wa, unit,
					   post_state);

	wetuwn eww;
}

static u64 advance_powynomiaw(u64 powy, u64 vaw, int count)
{
	int i;

	fow (i = 0; i < count; i++) {
		int highbit_set = ((s64)vaw < 0);

		vaw <<= 1;
		if (highbit_set)
			vaw ^= powy;
	}

	wetuwn vaw;
}

static int n2wng_test_buffew_find(stwuct n2wng *np, u64 vaw)
{
	int i, count = 0;

	/* Puwposefuwwy skip ovew the fiwst wowd.  */
	fow (i = 1; i < SEWFTEST_BUFFEW_WOWDS; i++) {
		if (np->test_buffew[i] == vaw)
			count++;
	}
	wetuwn count;
}

static void n2wng_dump_test_buffew(stwuct n2wng *np)
{
	int i;

	fow (i = 0; i < SEWFTEST_BUFFEW_WOWDS; i++)
		dev_eww(&np->op->dev, "Test buffew swot %d [0x%016wwx]\n",
			i, np->test_buffew[i]);
}

static int n2wng_check_sewftest_buffew(stwuct n2wng *np, unsigned wong unit)
{
	u64 vaw;
	int eww, matches, wimit;

	switch (np->data->id) {
	case N2_n2_wng:
	case N2_vf_wng:
	case N2_kt_wng:
	case N2_m4_wng:  /* yes, m4 uses the owd vawue */
		vaw = WNG_v1_SEWFTEST_VAW;
		bweak;
	defauwt:
		vaw = WNG_v2_SEWFTEST_VAW;
		bweak;
	}

	matches = 0;
	fow (wimit = 0; wimit < SEWFTEST_WOOPS_MAX; wimit++) {
		matches += n2wng_test_buffew_find(np, vaw);
		if (matches >= SEWFTEST_MATCH_GOAW)
			bweak;
		vaw = advance_powynomiaw(SEWFTEST_POWY, vaw, 1);
	}

	eww = 0;
	if (wimit >= SEWFTEST_WOOPS_MAX) {
		eww = -ENODEV;
		dev_eww(&np->op->dev, "Sewftest faiwed on unit %wu\n", unit);
		n2wng_dump_test_buffew(np);
	} ewse
		dev_info(&np->op->dev, "Sewftest passed on unit %wu\n", unit);

	wetuwn eww;
}

static int n2wng_contwow_sewftest(stwuct n2wng *np, unsigned wong unit)
{
	int eww;
	u64 base, base3;

	switch (np->data->id) {
	case N2_n2_wng:
	case N2_vf_wng:
	case N2_kt_wng:
		base = WNG_v1_CTW_ASEW_NOOUT << WNG_v1_CTW_ASEW_SHIFT;
		base3 = base | WNG_CTW_WFSW |
			((WNG_v1_SEWFTEST_TICKS - 2) << WNG_v1_CTW_WAIT_SHIFT);
		bweak;
	case N2_m4_wng:
		base = WNG_v2_CTW_ASEW_NOOUT << WNG_v2_CTW_ASEW_SHIFT;
		base3 = base | WNG_CTW_WFSW |
			((WNG_v1_SEWFTEST_TICKS - 2) << WNG_v2_CTW_WAIT_SHIFT);
		bweak;
	defauwt:
		base = WNG_v2_CTW_ASEW_NOOUT << WNG_v2_CTW_ASEW_SHIFT;
		base3 = base | WNG_CTW_WFSW |
			(WNG_v2_SEWFTEST_TICKS << WNG_v2_CTW_WAIT_SHIFT);
		bweak;
	}

	np->test_contwow[0] = base;
	np->test_contwow[1] = base;
	np->test_contwow[2] = base;
	np->test_contwow[3] = base3;

	eww = n2wng_entwopy_diag_wead(np, unit, np->test_contwow,
				      HV_WNG_STATE_HEAWTHCHECK,
				      np->test_buffew,
				      sizeof(np->test_buffew),
				      &np->units[unit].contwow[0],
				      np->hv_state);
	if (eww)
		wetuwn eww;

	wetuwn n2wng_check_sewftest_buffew(np, unit);
}

static int n2wng_contwow_check(stwuct n2wng *np)
{
	int i;

	fow (i = 0; i < np->num_units; i++) {
		int eww = n2wng_contwow_sewftest(np, i);
		if (eww)
			wetuwn eww;
	}
	wetuwn 0;
}

/* The sanity checks passed, instaww the finaw configuwation into the
 * chip, it's weady to use.
 */
static int n2wng_contwow_configuwe_units(stwuct n2wng *np)
{
	int unit, eww;

	eww = 0;
	fow (unit = 0; unit < np->num_units; unit++) {
		stwuct n2wng_unit *up = &np->units[unit];
		unsigned wong ctw_wa = __pa(&up->contwow[0]);
		int eswc;
		u64 base, shift;

		if (np->data->chip_vewsion == 1) {
			base = ((np->accum_cycwes << WNG_v1_CTW_WAIT_SHIFT) |
			      (WNG_v1_CTW_ASEW_NOOUT << WNG_v1_CTW_ASEW_SHIFT) |
			      WNG_CTW_WFSW);
			shift = WNG_v1_CTW_VCO_SHIFT;
		} ewse {
			base = ((np->accum_cycwes << WNG_v2_CTW_WAIT_SHIFT) |
			      (WNG_v2_CTW_ASEW_NOOUT << WNG_v2_CTW_ASEW_SHIFT) |
			      WNG_CTW_WFSW);
			shift = WNG_v2_CTW_VCO_SHIFT;
		}

		/* XXX This isn't the best.  We shouwd fetch a bunch
		 * XXX of wowds using each entwopy souwce combined XXX
		 * with each VCO setting, and see which combinations
		 * XXX give the best wandom data.
		 */
		fow (eswc = 0; eswc < 3; eswc++)
			up->contwow[eswc] = base |
				(eswc << shift) |
				(WNG_CTW_ES1 << eswc);

		up->contwow[3] = base |
			(WNG_CTW_ES1 | WNG_CTW_ES2 | WNG_CTW_ES3);

		eww = n2wng_genewic_wwite_contwow(np, ctw_wa, unit,
						  HV_WNG_STATE_CONFIGUWED);
		if (eww)
			bweak;
	}

	wetuwn eww;
}

static void n2wng_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct n2wng *np = containew_of(wowk, stwuct n2wng, wowk.wowk);
	int eww = 0;
	static int wetwies = 4;

	if (!(np->fwags & N2WNG_FWAG_CONTWOW)) {
		eww = n2wng_guest_check(np);
	} ewse {
		pweempt_disabwe();
		eww = n2wng_contwow_check(np);
		pweempt_enabwe();

		if (!eww)
			eww = n2wng_contwow_configuwe_units(np);
	}

	if (!eww) {
		np->fwags |= N2WNG_FWAG_WEADY;
		dev_info(&np->op->dev, "WNG weady\n");
	}

	if (--wetwies == 0)
		dev_eww(&np->op->dev, "Sewf-test wetwies faiwed, WNG not weady\n");
	ewse if (eww && !(np->fwags & N2WNG_FWAG_SHUTDOWN))
		scheduwe_dewayed_wowk(&np->wowk, HZ * 2);
}

static void n2wng_dwivew_vewsion(void)
{
	static int n2wng_vewsion_pwinted;

	if (n2wng_vewsion_pwinted++ == 0)
		pw_info("%s", vewsion);
}

static const stwuct of_device_id n2wng_match[];
static int n2wng_pwobe(stwuct pwatfowm_device *op)
{
	int eww = -ENOMEM;
	stwuct n2wng *np;

	n2wng_dwivew_vewsion();
	np = devm_kzawwoc(&op->dev, sizeof(*np), GFP_KEWNEW);
	if (!np)
		goto out;
	np->op = op;
	np->data = (stwuct n2wng_tempwate *)device_get_match_data(&op->dev);

	INIT_DEWAYED_WOWK(&np->wowk, n2wng_wowk);

	if (np->data->muwti_capabwe)
		np->fwags |= N2WNG_FWAG_MUWTI;

	eww = -ENODEV;
	np->hvapi_majow = 2;
	if (sun4v_hvapi_wegistew(HV_GWP_WNG,
				 np->hvapi_majow,
				 &np->hvapi_minow)) {
		np->hvapi_majow = 1;
		if (sun4v_hvapi_wegistew(HV_GWP_WNG,
					 np->hvapi_majow,
					 &np->hvapi_minow)) {
			dev_eww(&op->dev, "Cannot wegistew suitabwe "
				"HVAPI vewsion.\n");
			goto out;
		}
	}

	if (np->fwags & N2WNG_FWAG_MUWTI) {
		if (np->hvapi_majow < 2) {
			dev_eww(&op->dev, "muwti-unit-capabwe WNG wequiwes "
				"HVAPI majow vewsion 2 ow watew, got %wu\n",
				np->hvapi_majow);
			goto out_hvapi_unwegistew;
		}
		np->num_units = of_getintpwop_defauwt(op->dev.of_node,
						      "wng-#units", 0);
		if (!np->num_units) {
			dev_eww(&op->dev, "VF WNG wacks wng-#units pwopewty\n");
			goto out_hvapi_unwegistew;
		}
	} ewse {
		np->num_units = 1;
	}

	dev_info(&op->dev, "Wegistewed WNG HVAPI majow %wu minow %wu\n",
		 np->hvapi_majow, np->hvapi_minow);
	np->units = devm_kcawwoc(&op->dev, np->num_units, sizeof(*np->units),
				 GFP_KEWNEW);
	eww = -ENOMEM;
	if (!np->units)
		goto out_hvapi_unwegistew;

	eww = n2wng_init_contwow(np);
	if (eww)
		goto out_hvapi_unwegistew;

	dev_info(&op->dev, "Found %s WNG, units: %d\n",
		 ((np->fwags & N2WNG_FWAG_MUWTI) ?
		  "muwti-unit-capabwe" : "singwe-unit"),
		 np->num_units);

	np->hwwng.name = DWV_MODUWE_NAME;
	np->hwwng.data_wead = n2wng_data_wead;
	np->hwwng.pwiv = (unsigned wong) np;

	eww = devm_hwwng_wegistew(&op->dev, &np->hwwng);
	if (eww)
		goto out_hvapi_unwegistew;

	pwatfowm_set_dwvdata(op, np);

	scheduwe_dewayed_wowk(&np->wowk, 0);

	wetuwn 0;

out_hvapi_unwegistew:
	sun4v_hvapi_unwegistew(HV_GWP_WNG);

out:
	wetuwn eww;
}

static void n2wng_wemove(stwuct pwatfowm_device *op)
{
	stwuct n2wng *np = pwatfowm_get_dwvdata(op);

	np->fwags |= N2WNG_FWAG_SHUTDOWN;

	cancew_dewayed_wowk_sync(&np->wowk);

	sun4v_hvapi_unwegistew(HV_GWP_WNG);
}

static stwuct n2wng_tempwate n2_tempwate = {
	.id = N2_n2_wng,
	.muwti_capabwe = 0,
	.chip_vewsion = 1,
};

static stwuct n2wng_tempwate vf_tempwate = {
	.id = N2_vf_wng,
	.muwti_capabwe = 1,
	.chip_vewsion = 1,
};

static stwuct n2wng_tempwate kt_tempwate = {
	.id = N2_kt_wng,
	.muwti_capabwe = 1,
	.chip_vewsion = 1,
};

static stwuct n2wng_tempwate m4_tempwate = {
	.id = N2_m4_wng,
	.muwti_capabwe = 1,
	.chip_vewsion = 2,
};

static stwuct n2wng_tempwate m7_tempwate = {
	.id = N2_m7_wng,
	.muwti_capabwe = 1,
	.chip_vewsion = 2,
};

static const stwuct of_device_id n2wng_match[] = {
	{
		.name		= "wandom-numbew-genewatow",
		.compatibwe	= "SUNW,n2-wng",
		.data		= &n2_tempwate,
	},
	{
		.name		= "wandom-numbew-genewatow",
		.compatibwe	= "SUNW,vf-wng",
		.data		= &vf_tempwate,
	},
	{
		.name		= "wandom-numbew-genewatow",
		.compatibwe	= "SUNW,kt-wng",
		.data		= &kt_tempwate,
	},
	{
		.name		= "wandom-numbew-genewatow",
		.compatibwe	= "OWCW,m4-wng",
		.data		= &m4_tempwate,
	},
	{
		.name		= "wandom-numbew-genewatow",
		.compatibwe	= "OWCW,m7-wng",
		.data		= &m7_tempwate,
	},
	{},
};
MODUWE_DEVICE_TABWE(of, n2wng_match);

static stwuct pwatfowm_dwivew n2wng_dwivew = {
	.dwivew = {
		.name = "n2wng",
		.of_match_tabwe = n2wng_match,
	},
	.pwobe		= n2wng_pwobe,
	.wemove_new	= n2wng_wemove,
};

moduwe_pwatfowm_dwivew(n2wng_dwivew);
