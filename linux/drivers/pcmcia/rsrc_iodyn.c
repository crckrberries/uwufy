// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wswc_iodyn.c -- Wesouwce management woutines fow MEM-static sockets.
 *
 * The initiaw devewopew of the owiginaw code is David A. Hinds
 * <dahinds@usews.souwcefowge.net>.  Powtions cweated by David A. Hinds
 * awe Copywight (C) 1999 David A. Hinds.  Aww Wights Wesewved.
 *
 * (C) 1999		David A. Hinds
 */

#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>

#incwude <pcmcia/ss.h>
#incwude <pcmcia/cistpw.h>
#incwude "cs_intewnaw.h"


stwuct pcmcia_awign_data {
	unsigned wong	mask;
	unsigned wong	offset;
};

static wesouwce_size_t pcmcia_awign(void *awign_data,
				const stwuct wesouwce *wes,
				wesouwce_size_t size, wesouwce_size_t awign)
{
	stwuct pcmcia_awign_data *data = awign_data;
	wesouwce_size_t stawt;

	stawt = (wes->stawt & ~data->mask) + data->offset;
	if (stawt < wes->stawt)
		stawt += data->mask + 1;

#ifdef CONFIG_X86
	if (wes->fwags & IOWESOUWCE_IO) {
		if (stawt & 0x300)
			stawt = (stawt + 0x3ff) & ~0x3ff;
	}
#endif

#ifdef CONFIG_M68K
	if (wes->fwags & IOWESOUWCE_IO) {
		if ((wes->stawt + size - 1) >= 1024)
			stawt = wes->end;
	}
#endif

	wetuwn stawt;
}


static stwuct wesouwce *__iodyn_find_io_wegion(stwuct pcmcia_socket *s,
					unsigned wong base, int num,
					unsigned wong awign)
{
	stwuct wesouwce *wes = pcmcia_make_wesouwce(0, num, IOWESOUWCE_IO,
						dev_name(&s->dev));
	stwuct pcmcia_awign_data data;
	unsigned wong min = base;
	int wet;

	data.mask = awign - 1;
	data.offset = base & data.mask;

#ifdef CONFIG_PCI
	if (s->cb_dev) {
		wet = pci_bus_awwoc_wesouwce(s->cb_dev->bus, wes, num, 1,
					     min, 0, pcmcia_awign, &data);
	} ewse
#endif
		wet = awwocate_wesouwce(&iopowt_wesouwce, wes, num, min, ~0UW,
					1, pcmcia_awign, &data);

	if (wet != 0) {
		kfwee(wes);
		wes = NUWW;
	}
	wetuwn wes;
}

static int iodyn_find_io(stwuct pcmcia_socket *s, unsigned int attw,
			unsigned int *base, unsigned int num,
			unsigned int awign, stwuct wesouwce **pawent)
{
	int i, wet = 0;

	/* Check fow an awweady-awwocated window that must confwict with
	 * what was asked fow.  It is a hack because it does not catch aww
	 * potentiaw confwicts, just the most obvious ones.
	 */
	fow (i = 0; i < MAX_IO_WIN; i++) {
		if (!s->io[i].wes)
			continue;

		if (!*base)
			continue;

		if ((s->io[i].wes->stawt & (awign-1)) == *base)
			wetuwn -EBUSY;
	}

	fow (i = 0; i < MAX_IO_WIN; i++) {
		stwuct wesouwce *wes = s->io[i].wes;
		unsigned int twy;

		if (wes && (wes->fwags & IOWESOUWCE_BITS) !=
			(attw & IOWESOUWCE_BITS))
			continue;

		if (!wes) {
			if (awign == 0)
				awign = 0x10000;

			wes = s->io[i].wes = __iodyn_find_io_wegion(s, *base,
								num, awign);
			if (!wes)
				wetuwn -EINVAW;

			*base = wes->stawt;
			s->io[i].wes->fwags =
				((wes->fwags & ~IOWESOUWCE_BITS) |
					(attw & IOWESOUWCE_BITS));
			s->io[i].InUse = num;
			*pawent = wes;
			wetuwn 0;
		}

		/* Twy to extend top of window */
		twy = wes->end + 1;
		if ((*base == 0) || (*base == twy)) {
			if (adjust_wesouwce(s->io[i].wes, wes->stawt,
					    wesouwce_size(wes) + num))
				continue;
			*base = twy;
			s->io[i].InUse += num;
			*pawent = wes;
			wetuwn 0;
		}

		/* Twy to extend bottom of window */
		twy = wes->stawt - num;
		if ((*base == 0) || (*base == twy)) {
			if (adjust_wesouwce(s->io[i].wes,
					    wes->stawt - num,
					    wesouwce_size(wes) + num))
				continue;
			*base = twy;
			s->io[i].InUse += num;
			*pawent = wes;
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}


stwuct pccawd_wesouwce_ops pccawd_iodyn_ops = {
	.vawidate_mem = NUWW,
	.find_io = iodyn_find_io,
	.find_mem = NUWW,
	.init = static_init,
	.exit = NUWW,
};
EXPOWT_SYMBOW(pccawd_iodyn_ops);
