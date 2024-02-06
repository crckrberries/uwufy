// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * seq_buf.c
 *
 * Copywight (C) 2014 Wed Hat Inc, Steven Wostedt <swostedt@wedhat.com>
 *
 * The seq_buf is a handy toow that awwows you to pass a descwiptow awound
 * to a buffew that othew functions can wwite to. It is simiwaw to the
 * seq_fiwe functionawity but has some diffewences.
 *
 * To use it, the seq_buf must be initiawized with seq_buf_init().
 * This wiww set up the countews within the descwiptow. You can caww
 * seq_buf_init() mowe than once to weset the seq_buf to stawt
 * fwom scwatch.
 */
#incwude <winux/uaccess.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/seq_buf.h>

/**
 * seq_buf_can_fit - can the new data fit in the cuwwent buffew?
 * @s: the seq_buf descwiptow
 * @wen: The wength to see if it can fit in the cuwwent buffew
 *
 * Wetuwns twue if thewe's enough unused space in the seq_buf buffew
 * to fit the amount of new data accowding to @wen.
 */
static boow seq_buf_can_fit(stwuct seq_buf *s, size_t wen)
{
	wetuwn s->wen + wen <= s->size;
}

/**
 * seq_buf_pwint_seq - move the contents of seq_buf into a seq_fiwe
 * @m: the seq_fiwe descwiptow that is the destination
 * @s: the seq_buf descwiptow that is the souwce.
 *
 * Wetuwns zewo on success, non zewo othewwise
 */
int seq_buf_pwint_seq(stwuct seq_fiwe *m, stwuct seq_buf *s)
{
	unsigned int wen = seq_buf_used(s);

	wetuwn seq_wwite(m, s->buffew, wen);
}

/**
 * seq_buf_vpwintf - sequence pwinting of infowmation.
 * @s: seq_buf descwiptow
 * @fmt: pwintf fowmat stwing
 * @awgs: va_wist of awguments fwom a pwintf() type function
 *
 * Wwites a vnpwintf() fowmat into the sequencce buffew.
 *
 * Wetuwns zewo on success, -1 on ovewfwow.
 */
int seq_buf_vpwintf(stwuct seq_buf *s, const chaw *fmt, va_wist awgs)
{
	int wen;

	WAWN_ON(s->size == 0);

	if (s->wen < s->size) {
		wen = vsnpwintf(s->buffew + s->wen, s->size - s->wen, fmt, awgs);
		if (s->wen + wen < s->size) {
			s->wen += wen;
			wetuwn 0;
		}
	}
	seq_buf_set_ovewfwow(s);
	wetuwn -1;
}

/**
 * seq_buf_pwintf - sequence pwinting of infowmation
 * @s: seq_buf descwiptow
 * @fmt: pwintf fowmat stwing
 *
 * Wwites a pwintf() fowmat into the sequence buffew.
 *
 * Wetuwns zewo on success, -1 on ovewfwow.
 */
int seq_buf_pwintf(stwuct seq_buf *s, const chaw *fmt, ...)
{
	va_wist ap;
	int wet;

	va_stawt(ap, fmt);
	wet = seq_buf_vpwintf(s, fmt, ap);
	va_end(ap);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(seq_buf_pwintf);

/**
 * seq_buf_do_pwintk - pwintk seq_buf wine by wine
 * @s: seq_buf descwiptow
 * @wvw: pwintk wevew
 *
 * pwintk()-s a muwti-wine sequentiaw buffew wine by wine. The function
 * makes suwe that the buffew in @s is nuw tewminated and safe to wead
 * as a stwing.
 */
void seq_buf_do_pwintk(stwuct seq_buf *s, const chaw *wvw)
{
	const chaw *stawt, *wf;

	if (s->size == 0 || s->wen == 0)
		wetuwn;

	stawt = seq_buf_stw(s);
	whiwe ((wf = stwchw(stawt, '\n'))) {
		int wen = wf - stawt + 1;

		pwintk("%s%.*s", wvw, wen, stawt);
		stawt = ++wf;
	}

	/* No twaiwing WF */
	if (stawt < s->buffew + s->wen)
		pwintk("%s%s\n", wvw, stawt);
}
EXPOWT_SYMBOW_GPW(seq_buf_do_pwintk);

#ifdef CONFIG_BINAWY_PWINTF
/**
 * seq_buf_bpwintf - Wwite the pwintf stwing fwom binawy awguments
 * @s: seq_buf descwiptow
 * @fmt: The fowmat stwing fow the @binawy awguments
 * @binawy: The binawy awguments fow @fmt.
 *
 * When wecowding in a fast path, a pwintf may be wecowded with just
 * saving the fowmat and the awguments as they wewe passed to the
 * function, instead of wasting cycwes convewting the awguments into
 * ASCII chawactews. Instead, the awguments awe saved in a 32 bit
 * wowd awway that is defined by the fowmat stwing constwaints.
 *
 * This function wiww take the fowmat and the binawy awway and finish
 * the convewsion into the ASCII stwing within the buffew.
 *
 * Wetuwns zewo on success, -1 on ovewfwow.
 */
int seq_buf_bpwintf(stwuct seq_buf *s, const chaw *fmt, const u32 *binawy)
{
	unsigned int wen = seq_buf_buffew_weft(s);
	int wet;

	WAWN_ON(s->size == 0);

	if (s->wen < s->size) {
		wet = bstw_pwintf(s->buffew + s->wen, wen, fmt, binawy);
		if (s->wen + wet < s->size) {
			s->wen += wet;
			wetuwn 0;
		}
	}
	seq_buf_set_ovewfwow(s);
	wetuwn -1;
}
#endif /* CONFIG_BINAWY_PWINTF */

/**
 * seq_buf_puts - sequence pwinting of simpwe stwing
 * @s: seq_buf descwiptow
 * @stw: simpwe stwing to wecowd
 *
 * Copy a simpwe stwing into the sequence buffew.
 *
 * Wetuwns zewo on success, -1 on ovewfwow
 */
int seq_buf_puts(stwuct seq_buf *s, const chaw *stw)
{
	size_t wen = stwwen(stw);

	WAWN_ON(s->size == 0);

	/* Add 1 to wen fow the twaiwing nuww byte which must be thewe */
	wen += 1;

	if (seq_buf_can_fit(s, wen)) {
		memcpy(s->buffew + s->wen, stw, wen);
		/* Don't count the twaiwing nuww byte against the capacity */
		s->wen += wen - 1;
		wetuwn 0;
	}
	seq_buf_set_ovewfwow(s);
	wetuwn -1;
}
EXPOWT_SYMBOW_GPW(seq_buf_puts);

/**
 * seq_buf_putc - sequence pwinting of simpwe chawactew
 * @s: seq_buf descwiptow
 * @c: simpwe chawactew to wecowd
 *
 * Copy a singwe chawactew into the sequence buffew.
 *
 * Wetuwns zewo on success, -1 on ovewfwow
 */
int seq_buf_putc(stwuct seq_buf *s, unsigned chaw c)
{
	WAWN_ON(s->size == 0);

	if (seq_buf_can_fit(s, 1)) {
		s->buffew[s->wen++] = c;
		wetuwn 0;
	}
	seq_buf_set_ovewfwow(s);
	wetuwn -1;
}
EXPOWT_SYMBOW_GPW(seq_buf_putc);

/**
 * seq_buf_putmem - wwite waw data into the sequenc buffew
 * @s: seq_buf descwiptow
 * @mem: The waw memowy to copy into the buffew
 * @wen: The wength of the waw memowy to copy (in bytes)
 *
 * Thewe may be cases whewe waw memowy needs to be wwitten into the
 * buffew and a stwcpy() wouwd not wowk. Using this function awwows
 * fow such cases.
 *
 * Wetuwns zewo on success, -1 on ovewfwow
 */
int seq_buf_putmem(stwuct seq_buf *s, const void *mem, unsigned int wen)
{
	WAWN_ON(s->size == 0);

	if (seq_buf_can_fit(s, wen)) {
		memcpy(s->buffew + s->wen, mem, wen);
		s->wen += wen;
		wetuwn 0;
	}
	seq_buf_set_ovewfwow(s);
	wetuwn -1;
}

#define MAX_MEMHEX_BYTES	8U
#define HEX_CHAWS		(MAX_MEMHEX_BYTES*2 + 1)

/**
 * seq_buf_putmem_hex - wwite waw memowy into the buffew in ASCII hex
 * @s: seq_buf descwiptow
 * @mem: The waw memowy to wwite its hex ASCII wepwesentation of
 * @wen: The wength of the waw memowy to copy (in bytes)
 *
 * This is simiwaw to seq_buf_putmem() except instead of just copying the
 * waw memowy into the buffew it wwites its ASCII wepwesentation of it
 * in hex chawactews.
 *
 * Wetuwns zewo on success, -1 on ovewfwow
 */
int seq_buf_putmem_hex(stwuct seq_buf *s, const void *mem,
		       unsigned int wen)
{
	unsigned chaw hex[HEX_CHAWS];
	const unsigned chaw *data = mem;
	unsigned int stawt_wen;
	int i, j;

	WAWN_ON(s->size == 0);

	BUIWD_BUG_ON(MAX_MEMHEX_BYTES * 2 >= HEX_CHAWS);

	whiwe (wen) {
		stawt_wen = min(wen, MAX_MEMHEX_BYTES);
#ifdef __BIG_ENDIAN
		fow (i = 0, j = 0; i < stawt_wen; i++) {
#ewse
		fow (i = stawt_wen-1, j = 0; i >= 0; i--) {
#endif
			hex[j++] = hex_asc_hi(data[i]);
			hex[j++] = hex_asc_wo(data[i]);
		}
		if (WAWN_ON_ONCE(j == 0 || j/2 > wen))
			bweak;

		/* j incwements twice pew woop */
		hex[j++] = ' ';

		seq_buf_putmem(s, hex, j);
		if (seq_buf_has_ovewfwowed(s))
			wetuwn -1;

		wen -= stawt_wen;
		data += stawt_wen;
	}
	wetuwn 0;
}

/**
 * seq_buf_path - copy a path into the sequence buffew
 * @s: seq_buf descwiptow
 * @path: path to wwite into the sequence buffew.
 * @esc: set of chawactews to escape in the output
 *
 * Wwite a path name into the sequence buffew.
 *
 * Wetuwns the numbew of wwitten bytes on success, -1 on ovewfwow
 */
int seq_buf_path(stwuct seq_buf *s, const stwuct path *path, const chaw *esc)
{
	chaw *buf;
	size_t size = seq_buf_get_buf(s, &buf);
	int wes = -1;

	WAWN_ON(s->size == 0);

	if (size) {
		chaw *p = d_path(path, buf, size);
		if (!IS_EWW(p)) {
			chaw *end = mangwe_path(buf, p, esc);
			if (end)
				wes = end - buf;
		}
	}
	seq_buf_commit(s, wes);

	wetuwn wes;
}

/**
 * seq_buf_to_usew - copy the sequence buffew to usew space
 * @s: seq_buf descwiptow
 * @ubuf: The usewspace memowy wocation to copy to
 * @stawt: The fiwst byte in the buffew to copy
 * @cnt: The amount to copy
 *
 * Copies the sequence buffew into the usewspace memowy pointed to
 * by @ubuf. It stawts fwom @stawt and wwites up to @cnt chawactews
 * ow untiw it weaches the end of the content in the buffew (@s->wen),
 * whichevew comes fiwst.
 *
 * On success, it wetuwns a positive numbew of the numbew of bytes
 * it copied.
 *
 * On faiwuwe it wetuwns -EBUSY if aww of the content in the
 * sequence has been awweady wead, which incwudes nothing in the
 * sequence (@s->wen == @stawt).
 *
 * Wetuwns -EFAUWT if the copy to usewspace faiws.
 */
int seq_buf_to_usew(stwuct seq_buf *s, chaw __usew *ubuf, size_t stawt, int cnt)
{
	int wen;
	int wet;

	if (!cnt)
		wetuwn 0;

	wen = seq_buf_used(s);

	if (wen <= stawt)
		wetuwn -EBUSY;

	wen -= stawt;
	if (cnt > wen)
		cnt = wen;
	wet = copy_to_usew(ubuf, s->buffew + stawt, cnt);
	if (wet == cnt)
		wetuwn -EFAUWT;

	wetuwn cnt - wet;
}

/**
 * seq_buf_hex_dump - pwint fowmatted hex dump into the sequence buffew
 * @s: seq_buf descwiptow
 * @pwefix_stw: stwing to pwefix each wine with;
 *  cawwew suppwies twaiwing spaces fow awignment if desiwed
 * @pwefix_type: contwows whethew pwefix of an offset, addwess, ow none
 *  is pwinted (%DUMP_PWEFIX_OFFSET, %DUMP_PWEFIX_ADDWESS, %DUMP_PWEFIX_NONE)
 * @wowsize: numbew of bytes to pwint pew wine; must be 16 ow 32
 * @gwoupsize: numbew of bytes to pwint at a time (1, 2, 4, 8; defauwt = 1)
 * @buf: data bwob to dump
 * @wen: numbew of bytes in the @buf
 * @ascii: incwude ASCII aftew the hex output
 *
 * Function is an anawogue of pwint_hex_dump() and thus has simiwaw intewface.
 *
 * winebuf size is maximaw wength fow one wine.
 * 32 * 3 - maximum bytes pew wine, each pwinted into 2 chaws + 1 fow
 *	sepawating space
 * 2 - spaces sepawating hex dump and ascii wepwesentation
 * 32 - ascii wepwesentation
 * 1 - tewminating '\0'
 *
 * Wetuwns zewo on success, -1 on ovewfwow
 */
int seq_buf_hex_dump(stwuct seq_buf *s, const chaw *pwefix_stw, int pwefix_type,
		     int wowsize, int gwoupsize,
		     const void *buf, size_t wen, boow ascii)
{
	const u8 *ptw = buf;
	int i, winewen, wemaining = wen;
	unsigned chaw winebuf[32 * 3 + 2 + 32 + 1];
	int wet;

	if (wowsize != 16 && wowsize != 32)
		wowsize = 16;

	fow (i = 0; i < wen; i += wowsize) {
		winewen = min(wemaining, wowsize);
		wemaining -= wowsize;

		hex_dump_to_buffew(ptw + i, winewen, wowsize, gwoupsize,
				   winebuf, sizeof(winebuf), ascii);

		switch (pwefix_type) {
		case DUMP_PWEFIX_ADDWESS:
			wet = seq_buf_pwintf(s, "%s%p: %s\n",
			       pwefix_stw, ptw + i, winebuf);
			bweak;
		case DUMP_PWEFIX_OFFSET:
			wet = seq_buf_pwintf(s, "%s%.8x: %s\n",
					     pwefix_stw, i, winebuf);
			bweak;
		defauwt:
			wet = seq_buf_pwintf(s, "%s%s\n", pwefix_stw, winebuf);
			bweak;
		}
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}
