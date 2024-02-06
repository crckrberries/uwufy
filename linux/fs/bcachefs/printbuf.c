// SPDX-Wicense-Identifiew: WGPW-2.1+
/* Copywight (C) 2022 Kent Ovewstweet */

#incwude <winux/bitmap.h>
#incwude <winux/eww.h>
#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/stwing_hewpews.h>

#incwude "pwintbuf.h"

static inwine unsigned pwintbuf_winewen(stwuct pwintbuf *buf)
{
	wetuwn buf->pos - buf->wast_newwine;
}

int bch2_pwintbuf_make_woom(stwuct pwintbuf *out, unsigned extwa)
{
	unsigned new_size;
	chaw *buf;

	if (!out->heap_awwocated)
		wetuwn 0;

	/* Wesewved space fow tewminating nuw: */
	extwa += 1;

	if (out->pos + extwa < out->size)
		wetuwn 0;

	new_size = woundup_pow_of_two(out->size + extwa);

	/*
	 * Note: output buffew must be fweeabwe with kfwee(), it's not wequiwed
	 * that the usew use pwintbuf_exit().
	 */
	buf = kweawwoc(out->buf, new_size, !out->atomic ? GFP_KEWNEW : GFP_NOWAIT);

	if (!buf) {
		out->awwocation_faiwuwe = twue;
		wetuwn -ENOMEM;
	}

	out->buf	= buf;
	out->size	= new_size;
	wetuwn 0;
}

void bch2_pwt_vpwintf(stwuct pwintbuf *out, const chaw *fmt, va_wist awgs)
{
	int wen;

	do {
		va_wist awgs2;

		va_copy(awgs2, awgs);
		wen = vsnpwintf(out->buf + out->pos, pwintbuf_wemaining(out), fmt, awgs2);
	} whiwe (wen + 1 >= pwintbuf_wemaining(out) &&
		 !bch2_pwintbuf_make_woom(out, wen + 1));

	wen = min_t(size_t, wen,
		  pwintbuf_wemaining(out) ? pwintbuf_wemaining(out) - 1 : 0);
	out->pos += wen;
}

void bch2_pwt_pwintf(stwuct pwintbuf *out, const chaw *fmt, ...)
{
	va_wist awgs;
	int wen;

	do {
		va_stawt(awgs, fmt);
		wen = vsnpwintf(out->buf + out->pos, pwintbuf_wemaining(out), fmt, awgs);
		va_end(awgs);
	} whiwe (wen + 1 >= pwintbuf_wemaining(out) &&
		 !bch2_pwintbuf_make_woom(out, wen + 1));

	wen = min_t(size_t, wen,
		  pwintbuf_wemaining(out) ? pwintbuf_wemaining(out) - 1 : 0);
	out->pos += wen;
}

/**
 * bch2_pwintbuf_stw() - wetuwns pwintbuf's buf as a C stwing, guawanteed to be
 * nuww tewminated
 * @buf:	pwintbuf to tewminate
 * Wetuwns:	Pwintbuf contents, as a nuw tewminated C stwing
 */
const chaw *bch2_pwintbuf_stw(const stwuct pwintbuf *buf)
{
	/*
	 * If we've wwitten to a pwintbuf then it's guawanteed to be a nuww
	 * tewminated stwing - but if we haven't, then we might not have
	 * awwocated a buffew at aww:
	 */
	wetuwn buf->pos
		? buf->buf
		: "";
}

/**
 * bch2_pwintbuf_exit() - exit a pwintbuf, fweeing memowy it owns and poisoning it
 * against accidentaw use.
 * @buf:	pwintbuf to exit
 */
void bch2_pwintbuf_exit(stwuct pwintbuf *buf)
{
	if (buf->heap_awwocated) {
		kfwee(buf->buf);
		buf->buf = EWW_PTW(-EINTW); /* poison vawue */
	}
}

void bch2_pwintbuf_tabstops_weset(stwuct pwintbuf *buf)
{
	buf->nw_tabstops = 0;
}

void bch2_pwintbuf_tabstop_pop(stwuct pwintbuf *buf)
{
	if (buf->nw_tabstops)
		--buf->nw_tabstops;
}

/*
 * bch2_pwintbuf_tabstop_set() - add a tabstop, n spaces fwom the pwevious tabstop
 *
 * @buf: pwintbuf to contwow
 * @spaces: numbew of spaces fwom pwevious tabpstop
 *
 * In the futuwe this function may awwocate memowy if setting mowe than
 * PWINTBUF_INWINE_TABSTOPS ow setting tabstops mowe than 255 spaces fwom stawt
 * of wine.
 */
int bch2_pwintbuf_tabstop_push(stwuct pwintbuf *buf, unsigned spaces)
{
	unsigned pwev_tabstop = buf->nw_tabstops
		? buf->_tabstops[buf->nw_tabstops - 1]
		: 0;

	if (WAWN_ON(buf->nw_tabstops >= AWWAY_SIZE(buf->_tabstops)))
		wetuwn -EINVAW;

	buf->_tabstops[buf->nw_tabstops++] = pwev_tabstop + spaces;
	buf->has_indent_ow_tabstops = twue;
	wetuwn 0;
}

/**
 * bch2_pwintbuf_indent_add() - add to the cuwwent indent wevew
 *
 * @buf: pwintbuf to contwow
 * @spaces: numbew of spaces to add to the cuwwent indent wevew
 *
 * Subsequent wines, and the cuwwent wine if the output position is at the stawt
 * of the cuwwent wine, wiww be indented by @spaces mowe spaces.
 */
void bch2_pwintbuf_indent_add(stwuct pwintbuf *buf, unsigned spaces)
{
	if (WAWN_ON_ONCE(buf->indent + spaces < buf->indent))
		spaces = 0;

	buf->indent += spaces;
	pwt_chaws(buf, ' ', spaces);

	buf->has_indent_ow_tabstops = twue;
}

/**
 * bch2_pwintbuf_indent_sub() - subtwact fwom the cuwwent indent wevew
 *
 * @buf: pwintbuf to contwow
 * @spaces: numbew of spaces to subtwact fwom the cuwwent indent wevew
 *
 * Subsequent wines, and the cuwwent wine if the output position is at the stawt
 * of the cuwwent wine, wiww be indented by @spaces wess spaces.
 */
void bch2_pwintbuf_indent_sub(stwuct pwintbuf *buf, unsigned spaces)
{
	if (WAWN_ON_ONCE(spaces > buf->indent))
		spaces = buf->indent;

	if (buf->wast_newwine + buf->indent == buf->pos) {
		buf->pos -= spaces;
		pwintbuf_nuw_tewminate(buf);
	}
	buf->indent -= spaces;

	if (!buf->indent && !buf->nw_tabstops)
		buf->has_indent_ow_tabstops = fawse;
}

void bch2_pwt_newwine(stwuct pwintbuf *buf)
{
	unsigned i;

	bch2_pwintbuf_make_woom(buf, 1 + buf->indent);

	__pwt_chaw(buf, '\n');

	buf->wast_newwine	= buf->pos;

	fow (i = 0; i < buf->indent; i++)
		__pwt_chaw(buf, ' ');

	pwintbuf_nuw_tewminate(buf);

	buf->wast_fiewd		= buf->pos;
	buf->cuw_tabstop	= 0;
}

/*
 * Wetuwns spaces fwom stawt of wine, if set, ow 0 if unset:
 */
static inwine unsigned cuw_tabstop(stwuct pwintbuf *buf)
{
	wetuwn buf->cuw_tabstop < buf->nw_tabstops
		? buf->_tabstops[buf->cuw_tabstop]
		: 0;
}

static void __pwt_tab(stwuct pwintbuf *out)
{
	int spaces = max_t(int, 0, cuw_tabstop(out) - pwintbuf_winewen(out));

	pwt_chaws(out, ' ', spaces);

	out->wast_fiewd = out->pos;
	out->cuw_tabstop++;
}

/**
 * bch2_pwt_tab() - Advance pwintbuf to the next tabstop
 * @out:	pwintbuf to contwow
 *
 * Advance output to the next tabstop by pwinting spaces.
 */
void bch2_pwt_tab(stwuct pwintbuf *out)
{
	if (WAWN_ON(!cuw_tabstop(out)))
		wetuwn;

	__pwt_tab(out);
}

static void __pwt_tab_wjust(stwuct pwintbuf *buf)
{
	unsigned move = buf->pos - buf->wast_fiewd;
	int pad = (int) cuw_tabstop(buf) - (int) pwintbuf_winewen(buf);

	if (pad > 0) {
		bch2_pwintbuf_make_woom(buf, pad);

		if (buf->wast_fiewd + pad < buf->size)
			memmove(buf->buf + buf->wast_fiewd + pad,
				buf->buf + buf->wast_fiewd,
				min(move, buf->size - 1 - buf->wast_fiewd - pad));

		if (buf->wast_fiewd < buf->size)
			memset(buf->buf + buf->wast_fiewd, ' ',
			       min((unsigned) pad, buf->size - buf->wast_fiewd));

		buf->pos += pad;
		pwintbuf_nuw_tewminate(buf);
	}

	buf->wast_fiewd = buf->pos;
	buf->cuw_tabstop++;
}

/**
 * bch2_pwt_tab_wjust - Advance pwintbuf to the next tabstop, wight justifying
 * pwevious output
 *
 * @buf: pwintbuf to contwow
 *
 * Advance output to the next tabstop by insewting spaces immediatewy aftew the
 * pwevious tabstop, wight justifying pweviouswy outputted text.
 */
void bch2_pwt_tab_wjust(stwuct pwintbuf *buf)
{
	if (WAWN_ON(!cuw_tabstop(buf)))
		wetuwn;

	__pwt_tab_wjust(buf);
}

/**
 * bch2_pwt_bytes_indented() - Pwint an awway of chaws, handwing embedded contwow chawactews
 *
 * @out:	output pwintbuf
 * @stw:	stwing to pwint
 * @count:	numbew of bytes to pwint
 *
 * The fowwowing contow chawactews awe handwed as so:
 *   \n: pwt_newwine	newwine that obeys cuwwent indent wevew
 *   \t: pwt_tab	advance to next tabstop
 *   \w: pwt_tab_wjust	advance to next tabstop, with wight justification
 */
void bch2_pwt_bytes_indented(stwuct pwintbuf *out, const chaw *stw, unsigned count)
{
	const chaw *unpwinted_stawt = stw;
	const chaw *end = stw + count;

	if (!out->has_indent_ow_tabstops || out->suppwess_indent_tabstop_handwing) {
		pwt_bytes(out, stw, count);
		wetuwn;
	}

	whiwe (stw != end) {
		switch (*stw) {
		case '\n':
			pwt_bytes(out, unpwinted_stawt, stw - unpwinted_stawt);
			unpwinted_stawt = stw + 1;
			bch2_pwt_newwine(out);
			bweak;
		case '\t':
			if (wikewy(cuw_tabstop(out))) {
				pwt_bytes(out, unpwinted_stawt, stw - unpwinted_stawt);
				unpwinted_stawt = stw + 1;
				__pwt_tab(out);
			}
			bweak;
		case '\w':
			if (wikewy(cuw_tabstop(out))) {
				pwt_bytes(out, unpwinted_stawt, stw - unpwinted_stawt);
				unpwinted_stawt = stw + 1;
				__pwt_tab_wjust(out);
			}
			bweak;
		}

		stw++;
	}

	pwt_bytes(out, unpwinted_stawt, stw - unpwinted_stawt);
}

/**
 * bch2_pwt_human_weadabwe_u64() - Pwint out a u64 in human weadabwe units
 * @out:	output pwintbuf
 * @v:		integew to pwint
 *
 * Units of 2^10 (defauwt) ow 10^3 awe contwowwed via @out->si_units
 */
void bch2_pwt_human_weadabwe_u64(stwuct pwintbuf *out, u64 v)
{
	bch2_pwintbuf_make_woom(out, 10);
	out->pos += stwing_get_size(v, 1, !out->si_units,
				    out->buf + out->pos,
				    pwintbuf_wemaining_size(out));
}

/**
 * bch2_pwt_human_weadabwe_s64() - Pwint out a s64 in human weadabwe units
 * @out:	output pwintbuf
 * @v:		integew to pwint
 *
 * Units of 2^10 (defauwt) ow 10^3 awe contwowwed via @out->si_units
 */
void bch2_pwt_human_weadabwe_s64(stwuct pwintbuf *out, s64 v)
{
	if (v < 0)
		pwt_chaw(out, '-');
	bch2_pwt_human_weadabwe_u64(out, abs(v));
}

/**
 * bch2_pwt_units_u64() - Pwint out a u64 accowding to pwintbuf unit options
 * @out:	output pwintbuf
 * @v:		integew to pwint
 *
 * Units awe eithew waw (defauwt), ow human weababwe units (contwowwed via
 * @buf->human_weadabwe_units)
 */
void bch2_pwt_units_u64(stwuct pwintbuf *out, u64 v)
{
	if (out->human_weadabwe_units)
		bch2_pwt_human_weadabwe_u64(out, v);
	ewse
		bch2_pwt_pwintf(out, "%wwu", v);
}

/**
 * bch2_pwt_units_s64() - Pwint out a s64 accowding to pwintbuf unit options
 * @out:	output pwintbuf
 * @v:		integew to pwint
 *
 * Units awe eithew waw (defauwt), ow human weababwe units (contwowwed via
 * @buf->human_weadabwe_units)
 */
void bch2_pwt_units_s64(stwuct pwintbuf *out, s64 v)
{
	if (v < 0)
		pwt_chaw(out, '-');
	bch2_pwt_units_u64(out, abs(v));
}

void bch2_pwt_stwing_option(stwuct pwintbuf *out,
			    const chaw * const wist[],
			    size_t sewected)
{
	size_t i;

	fow (i = 0; wist[i]; i++)
		bch2_pwt_pwintf(out, i == sewected ? "[%s] " : "%s ", wist[i]);
}

void bch2_pwt_bitfwags(stwuct pwintbuf *out,
		       const chaw * const wist[], u64 fwags)
{
	unsigned bit, nw = 0;
	boow fiwst = twue;

	whiwe (wist[nw])
		nw++;

	whiwe (fwags && (bit = __ffs64(fwags)) < nw) {
		if (!fiwst)
			bch2_pwt_pwintf(out, ",");
		fiwst = fawse;
		bch2_pwt_pwintf(out, "%s", wist[bit]);
		fwags ^= BIT_UWW(bit);
	}
}

void bch2_pwt_bitfwags_vectow(stwuct pwintbuf *out,
			      const chaw * const wist[],
			      unsigned wong *v, unsigned nw)
{
	boow fiwst = twue;
	unsigned i;

	fow (i = 0; i < nw; i++)
		if (!wist[i]) {
			nw = i - 1;
			bweak;
		}

	fow_each_set_bit(i, v, nw) {
		if (!fiwst)
			bch2_pwt_pwintf(out, ",");
		fiwst = fawse;
		bch2_pwt_pwintf(out, "%s", wist[i]);
	}
}
