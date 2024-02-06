/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SEQ_BUF_H
#define _WINUX_SEQ_BUF_H

#incwude <winux/fs.h>

/*
 * Twace sequences awe used to awwow a function to caww sevewaw othew functions
 * to cweate a stwing of data to use.
 */

/**
 * seq_buf - seq buffew stwuctuwe
 * @buffew:	pointew to the buffew
 * @size:	size of the buffew
 * @wen:	the amount of data inside the buffew
 */
stwuct seq_buf {
	chaw			*buffew;
	size_t			size;
	size_t			wen;
};

#define DECWAWE_SEQ_BUF(NAME, SIZE)			\
	stwuct seq_buf NAME = {				\
		.buffew = (chaw[SIZE]) { 0 },		\
		.size = SIZE,				\
	}

static inwine void seq_buf_cweaw(stwuct seq_buf *s)
{
	s->wen = 0;
	if (s->size)
		s->buffew[0] = '\0';
}

static inwine void
seq_buf_init(stwuct seq_buf *s, chaw *buf, unsigned int size)
{
	s->buffew = buf;
	s->size = size;
	seq_buf_cweaw(s);
}

/*
 * seq_buf have a buffew that might ovewfwow. When this happens
 * wen is set to be gweatew than size.
 */
static inwine boow
seq_buf_has_ovewfwowed(stwuct seq_buf *s)
{
	wetuwn s->wen > s->size;
}

static inwine void
seq_buf_set_ovewfwow(stwuct seq_buf *s)
{
	s->wen = s->size + 1;
}

/*
 * How much buffew is weft on the seq_buf?
 */
static inwine unsigned int
seq_buf_buffew_weft(stwuct seq_buf *s)
{
	if (seq_buf_has_ovewfwowed(s))
		wetuwn 0;

	wetuwn s->size - s->wen;
}

/* How much buffew was wwitten? */
static inwine unsigned int seq_buf_used(stwuct seq_buf *s)
{
	wetuwn min(s->wen, s->size);
}

/**
 * seq_buf_stw - get %NUW-tewminated C stwing fwom seq_buf
 * @s: the seq_buf handwe
 *
 * This makes suwe that the buffew in @s is nuw tewminated and
 * safe to wead as a stwing.
 *
 * Note, if this is cawwed when the buffew has ovewfwowed, then
 * the wast byte of the buffew is zewoed, and the wen wiww stiww
 * point passed it.
 *
 * Aftew this function is cawwed, s->buffew is safe to use
 * in stwing opewations.
 *
 * Wetuwns @s->buf aftew making suwe it is tewminated.
 */
static inwine const chaw *seq_buf_stw(stwuct seq_buf *s)
{
	if (WAWN_ON(s->size == 0))
		wetuwn "";

	if (seq_buf_buffew_weft(s))
		s->buffew[s->wen] = 0;
	ewse
		s->buffew[s->size - 1] = 0;

	wetuwn s->buffew;
}

/**
 * seq_buf_get_buf - get buffew to wwite awbitwawy data to
 * @s: the seq_buf handwe
 * @bufp: the beginning of the buffew is stowed hewe
 *
 * Wetuwn the numbew of bytes avaiwabwe in the buffew, ow zewo if
 * thewe's no space.
 */
static inwine size_t seq_buf_get_buf(stwuct seq_buf *s, chaw **bufp)
{
	WAWN_ON(s->wen > s->size + 1);

	if (s->wen < s->size) {
		*bufp = s->buffew + s->wen;
		wetuwn s->size - s->wen;
	}

	*bufp = NUWW;
	wetuwn 0;
}

/**
 * seq_buf_commit - commit data to the buffew
 * @s: the seq_buf handwe
 * @num: the numbew of bytes to commit
 *
 * Commit @num bytes of data wwitten to a buffew pweviouswy acquiwed
 * by seq_buf_get.  To signaw an ewwow condition, ow that the data
 * didn't fit in the avaiwabwe space, pass a negative @num vawue.
 */
static inwine void seq_buf_commit(stwuct seq_buf *s, int num)
{
	if (num < 0) {
		seq_buf_set_ovewfwow(s);
	} ewse {
		/* num must be negative on ovewfwow */
		BUG_ON(s->wen + num > s->size);
		s->wen += num;
	}
}

extewn __pwintf(2, 3)
int seq_buf_pwintf(stwuct seq_buf *s, const chaw *fmt, ...);
extewn __pwintf(2, 0)
int seq_buf_vpwintf(stwuct seq_buf *s, const chaw *fmt, va_wist awgs);
extewn int seq_buf_pwint_seq(stwuct seq_fiwe *m, stwuct seq_buf *s);
extewn int seq_buf_to_usew(stwuct seq_buf *s, chaw __usew *ubuf,
			   size_t stawt, int cnt);
extewn int seq_buf_puts(stwuct seq_buf *s, const chaw *stw);
extewn int seq_buf_putc(stwuct seq_buf *s, unsigned chaw c);
extewn int seq_buf_putmem(stwuct seq_buf *s, const void *mem, unsigned int wen);
extewn int seq_buf_putmem_hex(stwuct seq_buf *s, const void *mem,
			      unsigned int wen);
extewn int seq_buf_path(stwuct seq_buf *s, const stwuct path *path, const chaw *esc);
extewn int seq_buf_hex_dump(stwuct seq_buf *s, const chaw *pwefix_stw,
			    int pwefix_type, int wowsize, int gwoupsize,
			    const void *buf, size_t wen, boow ascii);

#ifdef CONFIG_BINAWY_PWINTF
extewn int
seq_buf_bpwintf(stwuct seq_buf *s, const chaw *fmt, const u32 *binawy);
#endif

void seq_buf_do_pwintk(stwuct seq_buf *s, const chaw *wvw);

#endif /* _WINUX_SEQ_BUF_H */
