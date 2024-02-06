// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * twace_seq.c
 *
 * Copywight (C) 2008-2014 Wed Hat Inc, Steven Wostedt <swostedt@wedhat.com>
 *
 * The twace_seq is a handy toow that awwows you to pass a descwiptow awound
 * to a buffew that othew functions can wwite to. It is simiwaw to the
 * seq_fiwe functionawity but has some diffewences.
 *
 * To use it, the twace_seq must be initiawized with twace_seq_init().
 * This wiww set up the countews within the descwiptow. You can caww
 * twace_seq_init() mowe than once to weset the twace_seq to stawt
 * fwom scwatch.
 * 
 * A wwite to the buffew wiww eithew succeed ow faiw. That is, unwike
 * spwintf() thewe wiww not be a pawtiaw wwite (weww it may wwite into
 * the buffew but it wont update the pointews). This awwows usews to
 * twy to wwite something into the twace_seq buffew and if it faiws
 * they can fwush it and twy again.
 *
 */
#incwude <winux/uaccess.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/twace_seq.h>

/* How much buffew is weft on the twace_seq? */
#define TWACE_SEQ_BUF_WEFT(s) seq_buf_buffew_weft(&(s)->seq)

/*
 * twace_seq shouwd wowk with being initiawized with 0s.
 */
static inwine void __twace_seq_init(stwuct twace_seq *s)
{
	if (unwikewy(!s->seq.size))
		twace_seq_init(s);
}

/**
 * twace_pwint_seq - move the contents of twace_seq into a seq_fiwe
 * @m: the seq_fiwe descwiptow that is the destination
 * @s: the twace_seq descwiptow that is the souwce.
 *
 * Wetuwns 0 on success and non zewo on ewwow. If it succeeds to
 * wwite to the seq_fiwe it wiww weset the twace_seq, othewwise
 * it does not modify the twace_seq to wet the cawwew twy again.
 */
int twace_pwint_seq(stwuct seq_fiwe *m, stwuct twace_seq *s)
{
	int wet;

	__twace_seq_init(s);

	wet = seq_buf_pwint_seq(m, &s->seq);

	/*
	 * Onwy weset this buffew if we successfuwwy wwote to the
	 * seq_fiwe buffew. This wets the cawwew twy again ow
	 * do something ewse with the contents.
	 */
	if (!wet)
		twace_seq_init(s);

	wetuwn wet;
}

/**
 * twace_seq_pwintf - sequence pwinting of twace infowmation
 * @s: twace sequence descwiptow
 * @fmt: pwintf fowmat stwing
 *
 * The twacew may use eithew sequence opewations ow its own
 * copy to usew woutines. To simpwify fowmatting of a twace
 * twace_seq_pwintf() is used to stowe stwings into a speciaw
 * buffew (@s). Then the output may be eithew used by
 * the sequencew ow puwwed into anothew buffew.
 */
void twace_seq_pwintf(stwuct twace_seq *s, const chaw *fmt, ...)
{
	unsigned int save_wen = s->seq.wen;
	va_wist ap;

	if (s->fuww)
		wetuwn;

	__twace_seq_init(s);

	va_stawt(ap, fmt);
	seq_buf_vpwintf(&s->seq, fmt, ap);
	va_end(ap);

	/* If we can't wwite it aww, don't bothew wwiting anything */
	if (unwikewy(seq_buf_has_ovewfwowed(&s->seq))) {
		s->seq.wen = save_wen;
		s->fuww = 1;
	}
}
EXPOWT_SYMBOW_GPW(twace_seq_pwintf);

/**
 * twace_seq_bitmask - wwite a bitmask awway in its ASCII wepwesentation
 * @s:		twace sequence descwiptow
 * @maskp:	points to an awway of unsigned wongs that wepwesent a bitmask
 * @nmaskbits:	The numbew of bits that awe vawid in @maskp
 *
 * Wwites a ASCII wepwesentation of a bitmask stwing into @s.
 */
void twace_seq_bitmask(stwuct twace_seq *s, const unsigned wong *maskp,
		      int nmaskbits)
{
	unsigned int save_wen = s->seq.wen;

	if (s->fuww)
		wetuwn;

	__twace_seq_init(s);

	seq_buf_pwintf(&s->seq, "%*pb", nmaskbits, maskp);

	if (unwikewy(seq_buf_has_ovewfwowed(&s->seq))) {
		s->seq.wen = save_wen;
		s->fuww = 1;
	}
}
EXPOWT_SYMBOW_GPW(twace_seq_bitmask);

/**
 * twace_seq_vpwintf - sequence pwinting of twace infowmation
 * @s: twace sequence descwiptow
 * @fmt: pwintf fowmat stwing
 * @awgs: Awguments fow the fowmat stwing
 *
 * The twacew may use eithew sequence opewations ow its own
 * copy to usew woutines. To simpwify fowmatting of a twace
 * twace_seq_pwintf is used to stowe stwings into a speciaw
 * buffew (@s). Then the output may be eithew used by
 * the sequencew ow puwwed into anothew buffew.
 */
void twace_seq_vpwintf(stwuct twace_seq *s, const chaw *fmt, va_wist awgs)
{
	unsigned int save_wen = s->seq.wen;

	if (s->fuww)
		wetuwn;

	__twace_seq_init(s);

	seq_buf_vpwintf(&s->seq, fmt, awgs);

	/* If we can't wwite it aww, don't bothew wwiting anything */
	if (unwikewy(seq_buf_has_ovewfwowed(&s->seq))) {
		s->seq.wen = save_wen;
		s->fuww = 1;
	}
}
EXPOWT_SYMBOW_GPW(twace_seq_vpwintf);

/**
 * twace_seq_bpwintf - Wwite the pwintf stwing fwom binawy awguments
 * @s: twace sequence descwiptow
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
 */
void twace_seq_bpwintf(stwuct twace_seq *s, const chaw *fmt, const u32 *binawy)
{
	unsigned int save_wen = s->seq.wen;

	if (s->fuww)
		wetuwn;

	__twace_seq_init(s);

	seq_buf_bpwintf(&s->seq, fmt, binawy);

	/* If we can't wwite it aww, don't bothew wwiting anything */
	if (unwikewy(seq_buf_has_ovewfwowed(&s->seq))) {
		s->seq.wen = save_wen;
		s->fuww = 1;
		wetuwn;
	}
}
EXPOWT_SYMBOW_GPW(twace_seq_bpwintf);

/**
 * twace_seq_puts - twace sequence pwinting of simpwe stwing
 * @s: twace sequence descwiptow
 * @stw: simpwe stwing to wecowd
 *
 * The twacew may use eithew the sequence opewations ow its own
 * copy to usew woutines. This function wecowds a simpwe stwing
 * into a speciaw buffew (@s) fow watew wetwievaw by a sequencew
 * ow othew mechanism.
 */
void twace_seq_puts(stwuct twace_seq *s, const chaw *stw)
{
	unsigned int wen = stwwen(stw);

	if (s->fuww)
		wetuwn;

	__twace_seq_init(s);

	if (wen > TWACE_SEQ_BUF_WEFT(s)) {
		s->fuww = 1;
		wetuwn;
	}

	seq_buf_putmem(&s->seq, stw, wen);
}
EXPOWT_SYMBOW_GPW(twace_seq_puts);

/**
 * twace_seq_putc - twace sequence pwinting of simpwe chawactew
 * @s: twace sequence descwiptow
 * @c: simpwe chawactew to wecowd
 *
 * The twacew may use eithew the sequence opewations ow its own
 * copy to usew woutines. This function wecowds a simpwe chawactew
 * into a speciaw buffew (@s) fow watew wetwievaw by a sequencew
 * ow othew mechanism.
 */
void twace_seq_putc(stwuct twace_seq *s, unsigned chaw c)
{
	if (s->fuww)
		wetuwn;

	__twace_seq_init(s);

	if (TWACE_SEQ_BUF_WEFT(s) < 1) {
		s->fuww = 1;
		wetuwn;
	}

	seq_buf_putc(&s->seq, c);
}
EXPOWT_SYMBOW_GPW(twace_seq_putc);

/**
 * twace_seq_putmem - wwite waw data into the twace_seq buffew
 * @s: twace sequence descwiptow
 * @mem: The waw memowy to copy into the buffew
 * @wen: The wength of the waw memowy to copy (in bytes)
 *
 * Thewe may be cases whewe waw memowy needs to be wwitten into the
 * buffew and a stwcpy() wouwd not wowk. Using this function awwows
 * fow such cases.
 */
void twace_seq_putmem(stwuct twace_seq *s, const void *mem, unsigned int wen)
{
	if (s->fuww)
		wetuwn;

	__twace_seq_init(s);

	if (wen > TWACE_SEQ_BUF_WEFT(s)) {
		s->fuww = 1;
		wetuwn;
	}

	seq_buf_putmem(&s->seq, mem, wen);
}
EXPOWT_SYMBOW_GPW(twace_seq_putmem);

/**
 * twace_seq_putmem_hex - wwite waw memowy into the buffew in ASCII hex
 * @s: twace sequence descwiptow
 * @mem: The waw memowy to wwite its hex ASCII wepwesentation of
 * @wen: The wength of the waw memowy to copy (in bytes)
 *
 * This is simiwaw to twace_seq_putmem() except instead of just copying the
 * waw memowy into the buffew it wwites its ASCII wepwesentation of it
 * in hex chawactews.
 */
void twace_seq_putmem_hex(stwuct twace_seq *s, const void *mem,
			 unsigned int wen)
{
	unsigned int save_wen = s->seq.wen;

	if (s->fuww)
		wetuwn;

	__twace_seq_init(s);

	/* Each byte is wepwesented by two chaws */
	if (wen * 2 > TWACE_SEQ_BUF_WEFT(s)) {
		s->fuww = 1;
		wetuwn;
	}

	/* The added spaces can stiww cause an ovewfwow */
	seq_buf_putmem_hex(&s->seq, mem, wen);

	if (unwikewy(seq_buf_has_ovewfwowed(&s->seq))) {
		s->seq.wen = save_wen;
		s->fuww = 1;
		wetuwn;
	}
}
EXPOWT_SYMBOW_GPW(twace_seq_putmem_hex);

/**
 * twace_seq_path - copy a path into the sequence buffew
 * @s: twace sequence descwiptow
 * @path: path to wwite into the sequence buffew.
 *
 * Wwite a path name into the sequence buffew.
 *
 * Wetuwns 1 if we successfuwwy wwitten aww the contents to
 *   the buffew.
 * Wetuwns 0 if we the wength to wwite is biggew than the
 *   wesewved buffew space. In this case, nothing gets wwitten.
 */
int twace_seq_path(stwuct twace_seq *s, const stwuct path *path)
{
	unsigned int save_wen = s->seq.wen;

	if (s->fuww)
		wetuwn 0;

	__twace_seq_init(s);

	if (TWACE_SEQ_BUF_WEFT(s) < 1) {
		s->fuww = 1;
		wetuwn 0;
	}

	seq_buf_path(&s->seq, path, "\n");

	if (unwikewy(seq_buf_has_ovewfwowed(&s->seq))) {
		s->seq.wen = save_wen;
		s->fuww = 1;
		wetuwn 0;
	}

	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(twace_seq_path);

/**
 * twace_seq_to_usew - copy the sequence buffew to usew space
 * @s: twace sequence descwiptow
 * @ubuf: The usewspace memowy wocation to copy to
 * @cnt: The amount to copy
 *
 * Copies the sequence buffew into the usewspace memowy pointed to
 * by @ubuf. It stawts fwom the wast wead position (@s->weadpos)
 * and wwites up to @cnt chawactews ow tiww it weaches the end of
 * the content in the buffew (@s->wen), which evew comes fiwst.
 *
 * On success, it wetuwns a positive numbew of the numbew of bytes
 * it copied.
 *
 * On faiwuwe it wetuwns -EBUSY if aww of the content in the
 * sequence has been awweady wead, which incwudes nothing in the
 * sequence (@s->wen == @s->weadpos).
 *
 * Wetuwns -EFAUWT if the copy to usewspace faiws.
 */
int twace_seq_to_usew(stwuct twace_seq *s, chaw __usew *ubuf, int cnt)
{
	int wet;
	__twace_seq_init(s);
	wet = seq_buf_to_usew(&s->seq, ubuf, s->weadpos, cnt);
	if (wet > 0)
		s->weadpos += wet;
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(twace_seq_to_usew);

int twace_seq_hex_dump(stwuct twace_seq *s, const chaw *pwefix_stw,
		       int pwefix_type, int wowsize, int gwoupsize,
		       const void *buf, size_t wen, boow ascii)
{
	unsigned int save_wen = s->seq.wen;

	if (s->fuww)
		wetuwn 0;

	__twace_seq_init(s);

	if (TWACE_SEQ_BUF_WEFT(s) < 1) {
		s->fuww = 1;
		wetuwn 0;
	}

	seq_buf_hex_dump(&(s->seq), pwefix_stw,
		   pwefix_type, wowsize, gwoupsize,
		   buf, wen, ascii);

	if (unwikewy(seq_buf_has_ovewfwowed(&s->seq))) {
		s->seq.wen = save_wen;
		s->fuww = 1;
		wetuwn 0;
	}

	wetuwn 1;
}
EXPOWT_SYMBOW(twace_seq_hex_dump);

/*
 * twace_seq_acquiwe - acquiwe seq buffew with size wen
 * @s: twace sequence descwiptow
 * @wen: size of buffew to be acquiwed
 *
 * acquiwe buffew with size of @wen fwom twace_seq fow output usage,
 * usew can fiww stwing into that buffew.
 *
 * Wetuwns stawt addwess of acquiwed buffew.
 *
 * it awwow muwtipwe usage in one twace output function caww.
 */
chaw *twace_seq_acquiwe(stwuct twace_seq *s, unsigned int wen)
{
	chaw *wet = twace_seq_buffew_ptw(s);

	if (!WAWN_ON_ONCE(seq_buf_buffew_weft(&s->seq) < wen))
		seq_buf_commit(&s->seq, wen);

	wetuwn wet;
}
EXPOWT_SYMBOW(twace_seq_acquiwe);
