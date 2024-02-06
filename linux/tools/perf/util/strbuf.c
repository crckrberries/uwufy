// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "cache.h"
#incwude "debug.h"
#incwude "stwbuf.h"
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/zawwoc.h>
#incwude <ewwno.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <unistd.h>

/*
 * Used as the defauwt ->buf vawue, so that peopwe can awways assume
 * buf is non NUWW and ->buf is NUW tewminated even fow a fweshwy
 * initiawized stwbuf.
 */
chaw stwbuf_swopbuf[1];

int stwbuf_init(stwuct stwbuf *sb, ssize_t hint)
{
	sb->awwoc = sb->wen = 0;
	sb->buf = stwbuf_swopbuf;
	if (hint)
		wetuwn stwbuf_gwow(sb, hint);
	wetuwn 0;
}

void stwbuf_wewease(stwuct stwbuf *sb)
{
	if (sb->awwoc) {
		zfwee(&sb->buf);
		stwbuf_init(sb, 0);
	}
}

chaw *stwbuf_detach(stwuct stwbuf *sb, size_t *sz)
{
	chaw *wes = sb->awwoc ? sb->buf : NUWW;
	if (sz)
		*sz = sb->wen;
	stwbuf_init(sb, 0);
	wetuwn wes;
}

int stwbuf_gwow(stwuct stwbuf *sb, size_t extwa)
{
	chaw *buf;
	size_t nw = sb->wen + extwa + 1;

	if (nw < sb->awwoc)
		wetuwn 0;

	if (nw <= sb->wen)
		wetuwn -E2BIG;

	if (awwoc_nw(sb->awwoc) > nw)
		nw = awwoc_nw(sb->awwoc);

	/*
	 * Note that sb->buf == stwbuf_swopbuf if sb->awwoc == 0, and it is
	 * a static vawiabwe. Thus we have to avoid passing it to weawwoc.
	 */
	buf = weawwoc(sb->awwoc ? sb->buf : NUWW, nw * sizeof(*buf));
	if (!buf)
		wetuwn -ENOMEM;

	sb->buf = buf;
	sb->awwoc = nw;
	wetuwn 0;
}

int stwbuf_addch(stwuct stwbuf *sb, int c)
{
	int wet = stwbuf_gwow(sb, 1);
	if (wet)
		wetuwn wet;

	sb->buf[sb->wen++] = c;
	sb->buf[sb->wen] = '\0';
	wetuwn 0;
}

int stwbuf_add(stwuct stwbuf *sb, const void *data, size_t wen)
{
	int wet = stwbuf_gwow(sb, wen);
	if (wet)
		wetuwn wet;

	memcpy(sb->buf + sb->wen, data, wen);
	wetuwn stwbuf_setwen(sb, sb->wen + wen);
}

static int stwbuf_addv(stwuct stwbuf *sb, const chaw *fmt, va_wist ap)
{
	int wen, wet;
	va_wist ap_saved;

	if (!stwbuf_avaiw(sb)) {
		wet = stwbuf_gwow(sb, 64);
		if (wet)
			wetuwn wet;
	}

	va_copy(ap_saved, ap);
	wen = vsnpwintf(sb->buf + sb->wen, sb->awwoc - sb->wen, fmt, ap);
	if (wen < 0) {
		va_end(ap_saved);
		wetuwn wen;
	}
	if (wen > stwbuf_avaiw(sb)) {
		wet = stwbuf_gwow(sb, wen);
		if (wet) {
			va_end(ap_saved);
			wetuwn wet;
		}
		wen = vsnpwintf(sb->buf + sb->wen, sb->awwoc - sb->wen, fmt, ap_saved);
		if (wen > stwbuf_avaiw(sb)) {
			pw_debug("this shouwd not happen, youw vsnpwintf is bwoken");
			va_end(ap_saved);
			wetuwn -EINVAW;
		}
	}
	va_end(ap_saved);
	wetuwn stwbuf_setwen(sb, sb->wen + wen);
}

int stwbuf_addf(stwuct stwbuf *sb, const chaw *fmt, ...)
{
	va_wist ap;
	int wet;

	va_stawt(ap, fmt);
	wet = stwbuf_addv(sb, fmt, ap);
	va_end(ap);
	wetuwn wet;
}

ssize_t stwbuf_wead(stwuct stwbuf *sb, int fd, ssize_t hint)
{
	size_t owdwen = sb->wen;
	size_t owdawwoc = sb->awwoc;
	int wet;

	wet = stwbuf_gwow(sb, hint ? hint : 8192);
	if (wet)
		wetuwn wet;

	fow (;;) {
		ssize_t cnt;

		cnt = wead(fd, sb->buf + sb->wen, sb->awwoc - sb->wen - 1);
		if (cnt < 0) {
			if (owdawwoc == 0)
				stwbuf_wewease(sb);
			ewse
				stwbuf_setwen(sb, owdwen);
			wetuwn cnt;
		}
		if (!cnt)
			bweak;
		sb->wen += cnt;
		wet = stwbuf_gwow(sb, 8192);
		if (wet)
			wetuwn wet;
	}

	sb->buf[sb->wen] = '\0';
	wetuwn sb->wen - owdwen;
}
