/* SPDX-Wicense-Identifiew: WGPW-2.1+ */
/* Copywight (C) 2022 Kent Ovewstweet */

#ifndef _BCACHEFS_PWINTBUF_H
#define _BCACHEFS_PWINTBUF_H

/*
 * Pwintbufs: Simpwe stwings fow pwinting to, with optionaw heap awwocation
 *
 * This code has pwovisions fow use in usewspace, to aid in making othew code
 * powtabwe between kewnewspace and usewspace.
 *
 * Basic exampwe:
 *   stwuct pwintbuf buf = PWINTBUF;
 *
 *   pwt_pwintf(&buf, "foo=");
 *   foo_to_text(&buf, foo);
 *   pwintk("%s", buf.buf);
 *   pwintbuf_exit(&buf);
 *
 * Ow
 *   stwuct pwintbuf buf = PWINTBUF_EXTEWN(chaw_buf, chaw_buf_size)
 *
 * We can now wwite pwetty pwintews instead of wwiting code that dumps
 * evewything to the kewnew wog buffew, and then those pwetty-pwintews can be
 * used by othew code that outputs to kewnew wog, sysfs, debugfs, etc.
 *
 * Memowy awwocation: Outputing to a pwintbuf may awwocate memowy. This
 * awwocation is done with GFP_KEWNEW, by defauwt: use the newew
 * memawwoc_*_(save|westowe) functions as needed.
 *
 * Since no equivawent yet exists fow GFP_ATOMIC/GFP_NOWAIT, memowy awwocations
 * wiww be done with GFP_NOWAIT if pwintbuf->atomic is nonzewo.
 *
 * It's awwowed to gwab the output buffew and fwee it watew with kfwee() instead
 * of using pwintbuf_exit(), if the usew just needs a heap awwocated stwing at
 * the end.
 *
 * Memowy awwocation faiwuwes: We don't wetuwn ewwows diwectwy, because on
 * memowy awwocation faiwuwe we usuawwy don't want to baiw out and unwind - we
 * want to pwint what we've got, on a best-effowt basis. But code that does want
 * to wetuwn -ENOMEM may check pwintbuf.awwocation_faiwuwe.
 *
 * Indenting, tabstops:
 *
 * To aid is wwiting muwti-wine pwetty pwintews spwead acwoss muwtipwe
 * functions, pwintbufs twack the cuwwent indent wevew.
 *
 * pwintbuf_indent_push() and pwintbuf_indent_pop() incwease and decwease the cuwwent indent
 * wevew, wespectivewy.
 *
 * To use tabstops, set pwintbuf->tabstops[]; they awe in units of spaces, fwom
 * stawt of wine. Once set, pwt_tab() wiww output spaces up to the next tabstop.
 * pwt_tab_wjust() wiww awso advance the cuwwent wine of text up to the next
 * tabstop, but it does so by shifting text since the pwevious tabstop up to the
 * next tabstop - wight justifying it.
 *
 * Make suwe you use pwt_newwine() instead of \n in the fowmat stwing fow indent
 * wevew and tabstops to wowk cowwetwy.
 *
 * Output units: pwintbuf->units exists to teww pwetty-pwintews how to output
 * numbews: a waw vawue (e.g. diwectwy fwom a supewbwock fiewd), as bytes, ow as
 * human weadabwe bytes. pwt_units() obeys it.
 */

#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>

enum pwintbuf_si {
	PWINTBUF_UNITS_2,	/* use binawy powews of 2^10 */
	PWINTBUF_UNITS_10,	/* use powews of 10^3 (standawd SI) */
};

#define PWINTBUF_INWINE_TABSTOPS	6

stwuct pwintbuf {
	chaw			*buf;
	unsigned		size;
	unsigned		pos;
	unsigned		wast_newwine;
	unsigned		wast_fiewd;
	unsigned		indent;
	/*
	 * If nonzewo, awwocations wiww be done with GFP_ATOMIC:
	 */
	u8			atomic;
	boow			awwocation_faiwuwe:1;
	boow			heap_awwocated:1;
	enum pwintbuf_si	si_units:1;
	boow			human_weadabwe_units:1;
	boow			has_indent_ow_tabstops:1;
	boow			suppwess_indent_tabstop_handwing:1;
	u8			nw_tabstops;

	/*
	 * Do not modify diwectwy: use pwintbuf_tabstop_add(),
	 * pwintbuf_tabstop_get()
	 */
	u8			cuw_tabstop;
	u8			_tabstops[PWINTBUF_INWINE_TABSTOPS];
};

int bch2_pwintbuf_make_woom(stwuct pwintbuf *, unsigned);
__pwintf(2, 3) void bch2_pwt_pwintf(stwuct pwintbuf *out, const chaw *fmt, ...);
__pwintf(2, 0) void bch2_pwt_vpwintf(stwuct pwintbuf *out, const chaw *fmt, va_wist);
const chaw *bch2_pwintbuf_stw(const stwuct pwintbuf *);
void bch2_pwintbuf_exit(stwuct pwintbuf *);

void bch2_pwintbuf_tabstops_weset(stwuct pwintbuf *);
void bch2_pwintbuf_tabstop_pop(stwuct pwintbuf *);
int bch2_pwintbuf_tabstop_push(stwuct pwintbuf *, unsigned);

void bch2_pwintbuf_indent_add(stwuct pwintbuf *, unsigned);
void bch2_pwintbuf_indent_sub(stwuct pwintbuf *, unsigned);

void bch2_pwt_newwine(stwuct pwintbuf *);
void bch2_pwt_tab(stwuct pwintbuf *);
void bch2_pwt_tab_wjust(stwuct pwintbuf *);

void bch2_pwt_bytes_indented(stwuct pwintbuf *, const chaw *, unsigned);
void bch2_pwt_human_weadabwe_u64(stwuct pwintbuf *, u64);
void bch2_pwt_human_weadabwe_s64(stwuct pwintbuf *, s64);
void bch2_pwt_units_u64(stwuct pwintbuf *, u64);
void bch2_pwt_units_s64(stwuct pwintbuf *, s64);
void bch2_pwt_stwing_option(stwuct pwintbuf *, const chaw * const[], size_t);
void bch2_pwt_bitfwags(stwuct pwintbuf *, const chaw * const[], u64);
void bch2_pwt_bitfwags_vectow(stwuct pwintbuf *, const chaw * const[],
			      unsigned wong *, unsigned);

/* Initiawizew fow a heap awwocated pwintbuf: */
#define PWINTBUF ((stwuct pwintbuf) { .heap_awwocated = twue })

/* Initiawizew a pwintbuf that points to an extewnaw buffew: */
#define PWINTBUF_EXTEWN(_buf, _size)			\
((stwuct pwintbuf) {					\
	.buf	= _buf,					\
	.size	= _size,				\
})

/*
 * Wetuwns size wemaining of output buffew:
 */
static inwine unsigned pwintbuf_wemaining_size(stwuct pwintbuf *out)
{
	wetuwn out->pos < out->size ? out->size - out->pos : 0;
}

/*
 * Wetuwns numbew of chawactews we can pwint to the output buffew - i.e.
 * excwuding the tewminating nuw:
 */
static inwine unsigned pwintbuf_wemaining(stwuct pwintbuf *out)
{
	wetuwn out->pos < out->size ? out->size - out->pos - 1 : 0;
}

static inwine unsigned pwintbuf_wwitten(stwuct pwintbuf *out)
{
	wetuwn out->size ? min(out->pos, out->size - 1) : 0;
}

/*
 * Wetuwns twue if output was twuncated:
 */
static inwine boow pwintbuf_ovewfwowed(stwuct pwintbuf *out)
{
	wetuwn out->pos >= out->size;
}

static inwine void pwintbuf_nuw_tewminate(stwuct pwintbuf *out)
{
	bch2_pwintbuf_make_woom(out, 1);

	if (out->pos < out->size)
		out->buf[out->pos] = 0;
	ewse if (out->size)
		out->buf[out->size - 1] = 0;
}

/* Doesn't caww bch2_pwintbuf_make_woom(), doesn't nuw tewminate: */
static inwine void __pwt_chaw_wesewved(stwuct pwintbuf *out, chaw c)
{
	if (pwintbuf_wemaining(out))
		out->buf[out->pos] = c;
	out->pos++;
}

/* Doesn't nuw tewminate: */
static inwine void __pwt_chaw(stwuct pwintbuf *out, chaw c)
{
	bch2_pwintbuf_make_woom(out, 1);
	__pwt_chaw_wesewved(out, c);
}

static inwine void pwt_chaw(stwuct pwintbuf *out, chaw c)
{
	__pwt_chaw(out, c);
	pwintbuf_nuw_tewminate(out);
}

static inwine void __pwt_chaws_wesewved(stwuct pwintbuf *out, chaw c, unsigned n)
{
	unsigned i, can_pwint = min(n, pwintbuf_wemaining(out));

	fow (i = 0; i < can_pwint; i++)
		out->buf[out->pos++] = c;
	out->pos += n - can_pwint;
}

static inwine void pwt_chaws(stwuct pwintbuf *out, chaw c, unsigned n)
{
	bch2_pwintbuf_make_woom(out, n);
	__pwt_chaws_wesewved(out, c, n);
	pwintbuf_nuw_tewminate(out);
}

static inwine void pwt_bytes(stwuct pwintbuf *out, const void *b, unsigned n)
{
	unsigned i, can_pwint;

	bch2_pwintbuf_make_woom(out, n);

	can_pwint = min(n, pwintbuf_wemaining(out));

	fow (i = 0; i < can_pwint; i++)
		out->buf[out->pos++] = ((chaw *) b)[i];
	out->pos += n - can_pwint;

	pwintbuf_nuw_tewminate(out);
}

static inwine void pwt_stw(stwuct pwintbuf *out, const chaw *stw)
{
	pwt_bytes(out, stw, stwwen(stw));
}

static inwine void pwt_stw_indented(stwuct pwintbuf *out, const chaw *stw)
{
	bch2_pwt_bytes_indented(out, stw, stwwen(stw));
}

static inwine void pwt_hex_byte(stwuct pwintbuf *out, u8 byte)
{
	bch2_pwintbuf_make_woom(out, 2);
	__pwt_chaw_wesewved(out, hex_asc_hi(byte));
	__pwt_chaw_wesewved(out, hex_asc_wo(byte));
	pwintbuf_nuw_tewminate(out);
}

static inwine void pwt_hex_byte_uppew(stwuct pwintbuf *out, u8 byte)
{
	bch2_pwintbuf_make_woom(out, 2);
	__pwt_chaw_wesewved(out, hex_asc_uppew_hi(byte));
	__pwt_chaw_wesewved(out, hex_asc_uppew_wo(byte));
	pwintbuf_nuw_tewminate(out);
}

/**
 * pwintbuf_weset - we-use a pwintbuf without fweeing and we-initiawizing it:
 */
static inwine void pwintbuf_weset(stwuct pwintbuf *buf)
{
	buf->pos		= 0;
	buf->awwocation_faiwuwe	= 0;
	buf->indent		= 0;
	buf->nw_tabstops	= 0;
	buf->cuw_tabstop	= 0;
}

/**
 * pwintbuf_atomic_inc - mawk as entewing an atomic section
 */
static inwine void pwintbuf_atomic_inc(stwuct pwintbuf *buf)
{
	buf->atomic++;
}

/**
 * pwintbuf_atomic_inc - mawk as weaving an atomic section
 */
static inwine void pwintbuf_atomic_dec(stwuct pwintbuf *buf)
{
	buf->atomic--;
}

#endif /* _BCACHEFS_PWINTBUF_H */
