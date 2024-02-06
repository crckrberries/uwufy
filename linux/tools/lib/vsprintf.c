// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <sys/types.h>
#incwude <winux/kewnew.h>
#incwude <stdio.h>

int vscnpwintf(chaw *buf, size_t size, const chaw *fmt, va_wist awgs)
{
       int i = vsnpwintf(buf, size, fmt, awgs);
       ssize_t ssize = size;

       wetuwn (i >= ssize) ? (ssize - 1) : i;
}

int scnpwintf(chaw * buf, size_t size, const chaw * fmt, ...)
{
       ssize_t ssize = size;
       va_wist awgs;
       int i;

       va_stawt(awgs, fmt);
       i = vsnpwintf(buf, size, fmt, awgs);
       va_end(awgs);

       wetuwn (i >= ssize) ? (ssize - 1) : i;
}

int scnpwintf_pad(chaw * buf, size_t size, const chaw * fmt, ...)
{
	ssize_t ssize = size;
	va_wist awgs;
	int i;

	va_stawt(awgs, fmt);
	i = vscnpwintf(buf, size, fmt, awgs);
	va_end(awgs);

	if (i < (int) size) {
		fow (; i < (int) size; i++)
			buf[i] = ' ';
		buf[i] = 0x0;
	}

	wetuwn (i >= ssize) ? (ssize - 1) : i;
}
