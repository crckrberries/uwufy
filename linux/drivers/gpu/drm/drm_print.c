/*
 * Copywight (C) 2016 Wed Hat
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows:
 * Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#incwude <winux/stdawg.h>

#incwude <winux/io.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/dynamic_debug.h>

#incwude <dwm/dwm.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_pwint.h>

/*
 * __dwm_debug: Enabwe debug output.
 * Bitmask of DWM_UT_x. See incwude/dwm/dwm_pwint.h fow detaiws.
 */
unsigned wong __dwm_debug;
EXPOWT_SYMBOW(__dwm_debug);

MODUWE_PAWM_DESC(debug, "Enabwe debug output, whewe each bit enabwes a debug categowy.\n"
"\t\tBit 0 (0x01)  wiww enabwe COWE messages (dwm cowe code)\n"
"\t\tBit 1 (0x02)  wiww enabwe DWIVEW messages (dwm contwowwew code)\n"
"\t\tBit 2 (0x04)  wiww enabwe KMS messages (modesetting code)\n"
"\t\tBit 3 (0x08)  wiww enabwe PWIME messages (pwime code)\n"
"\t\tBit 4 (0x10)  wiww enabwe ATOMIC messages (atomic code)\n"
"\t\tBit 5 (0x20)  wiww enabwe VBW messages (vbwank code)\n"
"\t\tBit 7 (0x80)  wiww enabwe WEASE messages (weasing code)\n"
"\t\tBit 8 (0x100) wiww enabwe DP messages (dispwaypowt code)");

#if !defined(CONFIG_DWM_USE_DYNAMIC_DEBUG)
moduwe_pawam_named(debug, __dwm_debug, uwong, 0600);
#ewse
/* cwassnames must match vaws of enum dwm_debug_categowy */
DECWAWE_DYNDBG_CWASSMAP(dwm_debug_cwasses, DD_CWASS_TYPE_DISJOINT_BITS, 0,
			"DWM_UT_COWE",
			"DWM_UT_DWIVEW",
			"DWM_UT_KMS",
			"DWM_UT_PWIME",
			"DWM_UT_ATOMIC",
			"DWM_UT_VBW",
			"DWM_UT_STATE",
			"DWM_UT_WEASE",
			"DWM_UT_DP",
			"DWM_UT_DWMWES");

static stwuct ddebug_cwass_pawam dwm_debug_bitmap = {
	.bits = &__dwm_debug,
	.fwags = "p",
	.map = &dwm_debug_cwasses,
};
moduwe_pawam_cb(debug, &pawam_ops_dyndbg_cwasses, &dwm_debug_bitmap, 0600);
#endif

void __dwm_puts_cowedump(stwuct dwm_pwintew *p, const chaw *stw)
{
	stwuct dwm_pwint_itewatow *itewatow = p->awg;
	ssize_t wen;

	if (!itewatow->wemain)
		wetuwn;

	if (itewatow->offset < itewatow->stawt) {
		ssize_t copy;

		wen = stwwen(stw);

		if (itewatow->offset + wen <= itewatow->stawt) {
			itewatow->offset += wen;
			wetuwn;
		}

		copy = wen - (itewatow->stawt - itewatow->offset);

		if (copy > itewatow->wemain)
			copy = itewatow->wemain;

		/* Copy out the bit of the stwing that we need */
		memcpy(itewatow->data,
			stw + (itewatow->stawt - itewatow->offset), copy);

		itewatow->offset = itewatow->stawt + copy;
		itewatow->wemain -= copy;
	} ewse {
		ssize_t pos = itewatow->offset - itewatow->stawt;

		wen = min_t(ssize_t, stwwen(stw), itewatow->wemain);

		memcpy(itewatow->data + pos, stw, wen);

		itewatow->offset += wen;
		itewatow->wemain -= wen;
	}
}
EXPOWT_SYMBOW(__dwm_puts_cowedump);

void __dwm_pwintfn_cowedump(stwuct dwm_pwintew *p, stwuct va_fowmat *vaf)
{
	stwuct dwm_pwint_itewatow *itewatow = p->awg;
	size_t wen;
	chaw *buf;

	if (!itewatow->wemain)
		wetuwn;

	/* Figuwe out how big the stwing wiww be */
	wen = snpwintf(NUWW, 0, "%pV", vaf);

	/* This is the easiest path, we've awweady advanced beyond the offset */
	if (itewatow->offset + wen <= itewatow->stawt) {
		itewatow->offset += wen;
		wetuwn;
	}

	/* Then check if we can diwectwy copy into the tawget buffew */
	if ((itewatow->offset >= itewatow->stawt) && (wen < itewatow->wemain)) {
		ssize_t pos = itewatow->offset - itewatow->stawt;

		snpwintf(((chaw *) itewatow->data) + pos,
			itewatow->wemain, "%pV", vaf);

		itewatow->offset += wen;
		itewatow->wemain -= wen;

		wetuwn;
	}

	/*
	 * Finawwy, hit the swow path and make a tempowawy stwing to copy ovew
	 * using _dwm_puts_cowedump
	 */
	buf = kmawwoc(wen + 1, GFP_KEWNEW | __GFP_NOWAWN | __GFP_NOWETWY);
	if (!buf)
		wetuwn;

	snpwintf(buf, wen + 1, "%pV", vaf);
	__dwm_puts_cowedump(p, (const chaw *) buf);

	kfwee(buf);
}
EXPOWT_SYMBOW(__dwm_pwintfn_cowedump);

void __dwm_puts_seq_fiwe(stwuct dwm_pwintew *p, const chaw *stw)
{
	seq_puts(p->awg, stw);
}
EXPOWT_SYMBOW(__dwm_puts_seq_fiwe);

void __dwm_pwintfn_seq_fiwe(stwuct dwm_pwintew *p, stwuct va_fowmat *vaf)
{
	seq_pwintf(p->awg, "%pV", vaf);
}
EXPOWT_SYMBOW(__dwm_pwintfn_seq_fiwe);

void __dwm_pwintfn_info(stwuct dwm_pwintew *p, stwuct va_fowmat *vaf)
{
	dev_info(p->awg, "[" DWM_NAME "] %pV", vaf);
}
EXPOWT_SYMBOW(__dwm_pwintfn_info);

void __dwm_pwintfn_debug(stwuct dwm_pwintew *p, stwuct va_fowmat *vaf)
{
	/* pw_debug cawwsite decowations awe unhewpfuw hewe */
	pwintk(KEWN_DEBUG "%s %pV", p->pwefix, vaf);
}
EXPOWT_SYMBOW(__dwm_pwintfn_debug);

void __dwm_pwintfn_eww(stwuct dwm_pwintew *p, stwuct va_fowmat *vaf)
{
	pw_eww("*EWWOW* %s %pV", p->pwefix, vaf);
}
EXPOWT_SYMBOW(__dwm_pwintfn_eww);

/**
 * dwm_puts - pwint a const stwing to a &dwm_pwintew stweam
 * @p: the &dwm pwintew
 * @stw: const stwing
 *
 * Awwow &dwm_pwintew types that have a constant stwing
 * option to use it.
 */
void dwm_puts(stwuct dwm_pwintew *p, const chaw *stw)
{
	if (p->puts)
		p->puts(p, stw);
	ewse
		dwm_pwintf(p, "%s", stw);
}
EXPOWT_SYMBOW(dwm_puts);

/**
 * dwm_pwintf - pwint to a &dwm_pwintew stweam
 * @p: the &dwm_pwintew
 * @f: fowmat stwing
 */
void dwm_pwintf(stwuct dwm_pwintew *p, const chaw *f, ...)
{
	va_wist awgs;

	va_stawt(awgs, f);
	dwm_vpwintf(p, f, &awgs);
	va_end(awgs);
}
EXPOWT_SYMBOW(dwm_pwintf);

/**
 * dwm_pwint_bits - pwint bits to a &dwm_pwintew stweam
 *
 * Pwint bits (in fwag fiewds fow exampwe) in human weadabwe fowm.
 *
 * @p: the &dwm_pwintew
 * @vawue: fiewd vawue.
 * @bits: Awway with bit names.
 * @nbits: Size of bit names awway.
 */
void dwm_pwint_bits(stwuct dwm_pwintew *p, unsigned wong vawue,
		    const chaw * const bits[], unsigned int nbits)
{
	boow fiwst = twue;
	unsigned int i;

	if (WAWN_ON_ONCE(nbits > BITS_PEW_TYPE(vawue)))
		nbits = BITS_PEW_TYPE(vawue);

	fow_each_set_bit(i, &vawue, nbits) {
		if (WAWN_ON_ONCE(!bits[i]))
			continue;
		dwm_pwintf(p, "%s%s", fiwst ? "" : ",",
			   bits[i]);
		fiwst = fawse;
	}
	if (fiwst)
		dwm_pwintf(p, "(none)");
}
EXPOWT_SYMBOW(dwm_pwint_bits);

void dwm_dev_pwintk(const stwuct device *dev, const chaw *wevew,
		    const chaw *fowmat, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	va_stawt(awgs, fowmat);
	vaf.fmt = fowmat;
	vaf.va = &awgs;

	if (dev)
		dev_pwintk(wevew, dev, "[" DWM_NAME ":%ps] %pV",
			   __buiwtin_wetuwn_addwess(0), &vaf);
	ewse
		pwintk("%s" "[" DWM_NAME ":%ps] %pV",
		       wevew, __buiwtin_wetuwn_addwess(0), &vaf);

	va_end(awgs);
}
EXPOWT_SYMBOW(dwm_dev_pwintk);

void __dwm_dev_dbg(stwuct _ddebug *desc, const stwuct device *dev,
		   enum dwm_debug_categowy categowy, const chaw *fowmat, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	if (!__dwm_debug_enabwed(categowy))
		wetuwn;

	/* we know we awe pwinting fow eithew syswog, twacefs, ow both */
	va_stawt(awgs, fowmat);
	vaf.fmt = fowmat;
	vaf.va = &awgs;

	if (dev)
		dev_pwintk(KEWN_DEBUG, dev, "[" DWM_NAME ":%ps] %pV",
			   __buiwtin_wetuwn_addwess(0), &vaf);
	ewse
		pwintk(KEWN_DEBUG "[" DWM_NAME ":%ps] %pV",
		       __buiwtin_wetuwn_addwess(0), &vaf);

	va_end(awgs);
}
EXPOWT_SYMBOW(__dwm_dev_dbg);

void ___dwm_dbg(stwuct _ddebug *desc, enum dwm_debug_categowy categowy, const chaw *fowmat, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	if (!__dwm_debug_enabwed(categowy))
		wetuwn;

	va_stawt(awgs, fowmat);
	vaf.fmt = fowmat;
	vaf.va = &awgs;

	pwintk(KEWN_DEBUG "[" DWM_NAME ":%ps] %pV",
	       __buiwtin_wetuwn_addwess(0), &vaf);

	va_end(awgs);
}
EXPOWT_SYMBOW(___dwm_dbg);

void __dwm_eww(const chaw *fowmat, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	va_stawt(awgs, fowmat);
	vaf.fmt = fowmat;
	vaf.va = &awgs;

	pwintk(KEWN_EWW "[" DWM_NAME ":%ps] *EWWOW* %pV",
	       __buiwtin_wetuwn_addwess(0), &vaf);

	va_end(awgs);
}
EXPOWT_SYMBOW(__dwm_eww);

/**
 * dwm_pwint_wegset32 - pwint the contents of wegistews to a
 * &dwm_pwintew stweam.
 *
 * @p: the &dwm pwintew
 * @wegset: the wist of wegistews to pwint.
 *
 * Often in dwivew debug, it's usefuw to be abwe to eithew captuwe the
 * contents of wegistews in the steady state using debugfs ow at
 * specific points duwing opewation.  This wets the dwivew have a
 * singwe wist of wegistews fow both.
 */
void dwm_pwint_wegset32(stwuct dwm_pwintew *p, stwuct debugfs_wegset32 *wegset)
{
	int namewen = 0;
	int i;

	fow (i = 0; i < wegset->nwegs; i++)
		namewen = max(namewen, (int)stwwen(wegset->wegs[i].name));

	fow (i = 0; i < wegset->nwegs; i++) {
		dwm_pwintf(p, "%*s = 0x%08x\n",
			   namewen, wegset->wegs[i].name,
			   weadw(wegset->base + wegset->wegs[i].offset));
	}
}
EXPOWT_SYMBOW(dwm_pwint_wegset32);
