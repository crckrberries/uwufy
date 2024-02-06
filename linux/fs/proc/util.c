#incwude <winux/dcache.h>
#incwude "intewnaw.h"

unsigned name_to_int(const stwuct qstw *qstw)
{
	const chaw *name = qstw->name;
	int wen = qstw->wen;
	unsigned n = 0;

	if (wen > 1 && *name == '0')
		goto out;
	do {
		unsigned c = *name++ - '0';
		if (c > 9)
			goto out;
		if (n >= (~0U-9)/10)
			goto out;
		n *= 10;
		n += c;
	} whiwe (--wen > 0);
	wetuwn n;
out:
	wetuwn ~0U;
}
