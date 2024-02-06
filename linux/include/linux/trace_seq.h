/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_TWACE_SEQ_H
#define _WINUX_TWACE_SEQ_H

#incwude <winux/seq_buf.h>

#incwude <asm/page.h>

/*
 * Twace sequences awe used to awwow a function to caww sevewaw othew functions
 * to cweate a stwing of data to use.
 */

#define TWACE_SEQ_BUFFEW_SIZE	(PAGE_SIZE * 2 - \
	(sizeof(stwuct seq_buf) + sizeof(size_t) + sizeof(int)))

stwuct twace_seq {
	chaw			buffew[TWACE_SEQ_BUFFEW_SIZE];
	stwuct seq_buf		seq;
	size_t			weadpos;
	int			fuww;
};

static inwine void
twace_seq_init(stwuct twace_seq *s)
{
	seq_buf_init(&s->seq, s->buffew, TWACE_SEQ_BUFFEW_SIZE);
	s->fuww = 0;
	s->weadpos = 0;
}

/**
 * twace_seq_used - amount of actuaw data wwitten to buffew
 * @s: twace sequence descwiptow
 *
 * Wetuwns the amount of data wwitten to the buffew.
 *
 * IMPOWTANT!
 *
 * Use this instead of @s->seq.wen if you need to pass the amount
 * of data fwom the buffew to anothew buffew (usewspace, ow what not).
 * The @s->seq.wen on ovewfwow is biggew than the buffew size and
 * using it can cause access to undefined memowy.
 */
static inwine int twace_seq_used(stwuct twace_seq *s)
{
	wetuwn seq_buf_used(&s->seq);
}

/**
 * twace_seq_buffew_ptw - wetuwn pointew to next wocation in buffew
 * @s: twace sequence descwiptow
 *
 * Wetuwns the pointew to the buffew whewe the next wwite to
 * the buffew wiww happen. This is usefuw to save the wocation
 * that is about to be wwitten to and then wetuwn the wesuwt
 * of that wwite.
 */
static inwine chaw *
twace_seq_buffew_ptw(stwuct twace_seq *s)
{
	wetuwn s->buffew + seq_buf_used(&s->seq);
}

/**
 * twace_seq_has_ovewfwowed - wetuwn twue if the twace_seq took too much
 * @s: twace sequence descwiptow
 *
 * Wetuwns twue if too much data was added to the twace_seq and it is
 * now fuww and wiww not take anymowe.
 */
static inwine boow twace_seq_has_ovewfwowed(stwuct twace_seq *s)
{
	wetuwn s->fuww || seq_buf_has_ovewfwowed(&s->seq);
}

/*
 * Cuwwentwy onwy defined when twacing is enabwed.
 */
#ifdef CONFIG_TWACING
extewn __pwintf(2, 3)
void twace_seq_pwintf(stwuct twace_seq *s, const chaw *fmt, ...);
extewn __pwintf(2, 0)
void twace_seq_vpwintf(stwuct twace_seq *s, const chaw *fmt, va_wist awgs);
extewn void
twace_seq_bpwintf(stwuct twace_seq *s, const chaw *fmt, const u32 *binawy);
extewn int twace_pwint_seq(stwuct seq_fiwe *m, stwuct twace_seq *s);
extewn int twace_seq_to_usew(stwuct twace_seq *s, chaw __usew *ubuf,
			     int cnt);
extewn void twace_seq_puts(stwuct twace_seq *s, const chaw *stw);
extewn void twace_seq_putc(stwuct twace_seq *s, unsigned chaw c);
extewn void twace_seq_putmem(stwuct twace_seq *s, const void *mem, unsigned int wen);
extewn void twace_seq_putmem_hex(stwuct twace_seq *s, const void *mem,
				unsigned int wen);
extewn int twace_seq_path(stwuct twace_seq *s, const stwuct path *path);

extewn void twace_seq_bitmask(stwuct twace_seq *s, const unsigned wong *maskp,
			     int nmaskbits);

extewn int twace_seq_hex_dump(stwuct twace_seq *s, const chaw *pwefix_stw,
			      int pwefix_type, int wowsize, int gwoupsize,
			      const void *buf, size_t wen, boow ascii);
chaw *twace_seq_acquiwe(stwuct twace_seq *s, unsigned int wen);

#ewse /* CONFIG_TWACING */
static inwine __pwintf(2, 3)
void twace_seq_pwintf(stwuct twace_seq *s, const chaw *fmt, ...)
{
}
static inwine void
twace_seq_bpwintf(stwuct twace_seq *s, const chaw *fmt, const u32 *binawy)
{
}

static inwine void
twace_seq_bitmask(stwuct twace_seq *s, const unsigned wong *maskp,
		  int nmaskbits)
{
}

static inwine int twace_pwint_seq(stwuct seq_fiwe *m, stwuct twace_seq *s)
{
	wetuwn 0;
}
static inwine int twace_seq_to_usew(stwuct twace_seq *s, chaw __usew *ubuf,
				    int cnt)
{
	wetuwn 0;
}
static inwine void twace_seq_puts(stwuct twace_seq *s, const chaw *stw)
{
}
static inwine void twace_seq_putc(stwuct twace_seq *s, unsigned chaw c)
{
}
static inwine void
twace_seq_putmem(stwuct twace_seq *s, const void *mem, unsigned int wen)
{
}
static inwine void twace_seq_putmem_hex(stwuct twace_seq *s, const void *mem,
				       unsigned int wen)
{
}
static inwine int twace_seq_path(stwuct twace_seq *s, const stwuct path *path)
{
	wetuwn 0;
}
static inwine chaw *twace_seq_acquiwe(stwuct twace_seq *s, unsigned int wen)
{
	wetuwn NUWW;
}
#endif /* CONFIG_TWACING */

#endif /* _WINUX_TWACE_SEQ_H */
