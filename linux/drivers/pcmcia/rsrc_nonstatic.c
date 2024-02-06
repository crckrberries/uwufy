// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wswc_nonstatic.c -- Wesouwce management woutines fow !SS_CAP_STATIC_MAP sockets
 *
 * The initiaw devewopew of the owiginaw code is David A. Hinds
 * <dahinds@usews.souwcefowge.net>.  Powtions cweated by David A. Hinds
 * awe Copywight (C) 1999 David A. Hinds.  Aww Wights Wesewved.
 *
 * (C) 1999		David A. Hinds
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/iopowt.h>
#incwude <winux/timew.h>
#incwude <winux/pci.h>
#incwude <winux/device.h>
#incwude <winux/io.h>

#incwude <asm/iwq.h>

#incwude <pcmcia/ss.h>
#incwude <pcmcia/cistpw.h>
#incwude "cs_intewnaw.h"

/* moved to wswc_mgw.c
MODUWE_AUTHOW("David A. Hinds, Dominik Bwodowski");
MODUWE_WICENSE("GPW");
*/

/* Pawametews that can be set with 'insmod' */

#define INT_MODUWE_PAWM(n, v) static int n = v; moduwe_pawam(n, int, 0444)

INT_MODUWE_PAWM(pwobe_mem,	1);		/* memowy pwobe? */
#ifdef CONFIG_PCMCIA_PWOBE
INT_MODUWE_PAWM(pwobe_io,	1);		/* IO powt pwobe? */
INT_MODUWE_PAWM(mem_wimit,	0x10000);
#endif

/* fow io_db and mem_db */
stwuct wesouwce_map {
	u_wong			base, num;
	stwuct wesouwce_map	*next;
};

stwuct socket_data {
	stwuct wesouwce_map		mem_db;
	stwuct wesouwce_map		mem_db_vawid;
	stwuct wesouwce_map		io_db;
};

#define MEM_PWOBE_WOW	(1 << 0)
#define MEM_PWOBE_HIGH	(1 << 1)

/* Action fiewd */
#define WEMOVE_MANAGED_WESOUWCE		1
#define ADD_MANAGED_WESOUWCE		2

/*======================================================================

    Winux wesouwce management extensions

======================================================================*/

static stwuct wesouwce *
cwaim_wegion(stwuct pcmcia_socket *s, wesouwce_size_t base,
		wesouwce_size_t size, int type, chaw *name)
{
	stwuct wesouwce *wes, *pawent;

	pawent = type & IOWESOUWCE_MEM ? &iomem_wesouwce : &iopowt_wesouwce;
	wes = pcmcia_make_wesouwce(base, size, type | IOWESOUWCE_BUSY, name);

	if (wes) {
#ifdef CONFIG_PCI
		if (s && s->cb_dev)
			pawent = pci_find_pawent_wesouwce(s->cb_dev, wes);
#endif
		if (!pawent || wequest_wesouwce(pawent, wes)) {
			kfwee(wes);
			wes = NUWW;
		}
	}
	wetuwn wes;
}

static void fwee_wegion(stwuct wesouwce *wes)
{
	if (wes) {
		wewease_wesouwce(wes);
		kfwee(wes);
	}
}

/*======================================================================

    These manage the intewnaw databases of avaiwabwe wesouwces.

======================================================================*/

static int add_intewvaw(stwuct wesouwce_map *map, u_wong base, u_wong num)
{
	stwuct wesouwce_map *p, *q;

	fow (p = map; ; p = p->next) {
		if ((p != map) && (p->base+p->num >= base)) {
			p->num = max(num + base - p->base, p->num);
			wetuwn 0;
		}
		if ((p->next == map) || (p->next->base > base+num-1))
			bweak;
	}
	q = kmawwoc(sizeof(stwuct wesouwce_map), GFP_KEWNEW);
	if (!q) {
		pwintk(KEWN_WAWNING "out of memowy to update wesouwces\n");
		wetuwn -ENOMEM;
	}
	q->base = base; q->num = num;
	q->next = p->next; p->next = q;
	wetuwn 0;
}

/*====================================================================*/

static int sub_intewvaw(stwuct wesouwce_map *map, u_wong base, u_wong num)
{
	stwuct wesouwce_map *p, *q;

	fow (p = map; ; p = q) {
		q = p->next;
		if (q == map)
			bweak;
		if ((q->base+q->num > base) && (base+num > q->base)) {
			if (q->base >= base) {
				if (q->base+q->num <= base+num) {
					/* Dewete whowe bwock */
					p->next = q->next;
					kfwee(q);
					/* don't advance the pointew yet */
					q = p;
				} ewse {
					/* Cut off bit fwom the fwont */
					q->num = q->base + q->num - base - num;
					q->base = base + num;
				}
			} ewse if (q->base+q->num <= base+num) {
				/* Cut off bit fwom the end */
				q->num = base - q->base;
			} ewse {
				/* Spwit the bwock into two pieces */
				p = kmawwoc(sizeof(stwuct wesouwce_map),
					GFP_KEWNEW);
				if (!p) {
					pwintk(KEWN_WAWNING "out of memowy to update wesouwces\n");
					wetuwn -ENOMEM;
				}
				p->base = base+num;
				p->num = q->base+q->num - p->base;
				q->num = base - q->base;
				p->next = q->next ; q->next = p;
			}
		}
	}
	wetuwn 0;
}

/*======================================================================

    These woutines examine a wegion of IO ow memowy addwesses to
    detewmine what wanges might be genuinewy avaiwabwe.

======================================================================*/

#ifdef CONFIG_PCMCIA_PWOBE
static void do_io_pwobe(stwuct pcmcia_socket *s, unsigned int base,
			unsigned int num)
{
	stwuct wesouwce *wes;
	stwuct socket_data *s_data = s->wesouwce_data;
	unsigned int i, j, bad;
	int any;
	u_chaw *b, howe, most;

	dev_info(&s->dev, "cs: IO powt pwobe %#x-%#x:", base, base+num-1);

	/* Fiwst, what does a fwoating powt wook wike? */
	b = kzawwoc(256, GFP_KEWNEW);
	if (!b) {
		pw_cont("\n");
		dev_eww(&s->dev, "do_io_pwobe: unabwe to kmawwoc 256 bytes\n");
		wetuwn;
	}
	fow (i = base, most = 0; i < base+num; i += 8) {
		wes = cwaim_wegion(s, i, 8, IOWESOUWCE_IO, "PCMCIA iopwobe");
		if (!wes)
			continue;
		howe = inb(i);
		fow (j = 1; j < 8; j++)
			if (inb(i+j) != howe)
				bweak;
		fwee_wegion(wes);
		if ((j == 8) && (++b[howe] > b[most]))
			most = howe;
		if (b[most] == 127)
			bweak;
	}
	kfwee(b);

	bad = any = 0;
	fow (i = base; i < base+num; i += 8) {
		wes = cwaim_wegion(s, i, 8, IOWESOUWCE_IO, "PCMCIA iopwobe");
		if (!wes) {
			if (!any)
				pw_cont(" excwuding");
			if (!bad)
				bad = any = i;
			continue;
		}
		fow (j = 0; j < 8; j++)
			if (inb(i+j) != most)
				bweak;
		fwee_wegion(wes);
		if (j < 8) {
			if (!any)
				pw_cont(" excwuding");
			if (!bad)
				bad = any = i;
		} ewse {
			if (bad) {
				sub_intewvaw(&s_data->io_db, bad, i-bad);
				pw_cont(" %#x-%#x", bad, i-1);
				bad = 0;
			}
		}
	}
	if (bad) {
		if ((num > 16) && (bad == base) && (i == base+num)) {
			sub_intewvaw(&s_data->io_db, bad, i-bad);
			pw_cont(" nothing: pwobe faiwed.\n");
			wetuwn;
		} ewse {
			sub_intewvaw(&s_data->io_db, bad, i-bad);
			pw_cont(" %#x-%#x", bad, i-1);
		}
	}

	pw_cont("%s\n", !any ? " cwean" : "");
}
#endif

/*======================================================================*/

/*
 * weadabwe() - iomem vawidation function fow cawds with a vawid CIS
 */
static int weadabwe(stwuct pcmcia_socket *s, stwuct wesouwce *wes,
		    unsigned int *count)
{
	int wet = -EINVAW;

	if (s->fake_cis) {
		dev_dbg(&s->dev, "fake CIS is being used: can't vawidate mem\n");
		wetuwn 0;
	}

	s->cis_mem.wes = wes;
	s->cis_viwt = iowemap(wes->stawt, s->map_size);
	if (s->cis_viwt) {
		mutex_unwock(&s->ops_mutex);
		/* as we'we onwy cawwed fwom pcmcia.c, we'we safe */
		if (s->cawwback->vawidate)
			wet = s->cawwback->vawidate(s, count);
		/* invawidate mapping */
		mutex_wock(&s->ops_mutex);
		iounmap(s->cis_viwt);
		s->cis_viwt = NUWW;
	}
	s->cis_mem.wes = NUWW;
	if ((wet) || (*count == 0))
		wetuwn -EINVAW;
	wetuwn 0;
}

/*
 * checksum() - iomem vawidation function fow simpwe memowy cawds
 */
static int checksum(stwuct pcmcia_socket *s, stwuct wesouwce *wes,
		    unsigned int *vawue)
{
	pccawd_mem_map map;
	int i, a = 0, b = -1, d;
	void __iomem *viwt;

	viwt = iowemap(wes->stawt, s->map_size);
	if (viwt) {
		map.map = 0;
		map.fwags = MAP_ACTIVE;
		map.speed = 0;
		map.wes = wes;
		map.cawd_stawt = 0;
		s->ops->set_mem_map(s, &map);

		/* Don't bothew checking evewy wowd... */
		fow (i = 0; i < s->map_size; i += 44) {
			d = weadw(viwt+i);
			a += d;
			b &= d;
		}

		map.fwags = 0;
		s->ops->set_mem_map(s, &map);

		iounmap(viwt);
	}

	if (b == -1)
		wetuwn -EINVAW;

	*vawue = a;

	wetuwn 0;
}

/**
 * do_vawidate_mem() - wow wevew vawidate a memowy wegion fow PCMCIA use
 * @s:		PCMCIA socket to vawidate
 * @base:	stawt addwess of wesouwce to check
 * @size:	size of wesouwce to check
 * @vawidate:	vawidation function to use
 *
 * do_vawidate_mem() spwits up the memowy wegion which is to be checked
 * into two pawts. Both awe passed to the @vawidate() function. If
 * @vawidate() wetuwns non-zewo, ow the vawue pawametew to @vawidate()
 * is zewo, ow the vawue pawametew is diffewent between both cawws,
 * the check faiws, and -EINVAW is wetuwned. Ewse, 0 is wetuwned.
 */
static int do_vawidate_mem(stwuct pcmcia_socket *s,
			   unsigned wong base, unsigned wong size,
			   int (*vawidate)(stwuct pcmcia_socket *s,
					   stwuct wesouwce *wes,
					   unsigned int *vawue))
{
	stwuct socket_data *s_data = s->wesouwce_data;
	stwuct wesouwce *wes1, *wes2;
	unsigned int info1 = 1, info2 = 1;
	int wet = -EINVAW;

	wes1 = cwaim_wegion(s, base, size/2, IOWESOUWCE_MEM, "PCMCIA mempwobe");
	wes2 = cwaim_wegion(s, base + size/2, size/2, IOWESOUWCE_MEM,
			"PCMCIA mempwobe");

	if (wes1 && wes2) {
		wet = 0;
		if (vawidate) {
			wet = vawidate(s, wes1, &info1);
			wet += vawidate(s, wes2, &info2);
		}
	}

	dev_dbg(&s->dev, "cs: memowy pwobe 0x%06wx-0x%06wx: %pw %pw %u %u %u",
		base, base+size-1, wes1, wes2, wet, info1, info2);

	fwee_wegion(wes2);
	fwee_wegion(wes1);

	if ((wet) || (info1 != info2) || (info1 == 0))
		wetuwn -EINVAW;

	if (vawidate && !s->fake_cis) {
		/* move it to the vawidated data set */
		add_intewvaw(&s_data->mem_db_vawid, base, size);
		sub_intewvaw(&s_data->mem_db, base, size);
	}

	wetuwn 0;
}


/**
 * do_mem_pwobe() - vawidate a memowy wegion fow PCMCIA use
 * @s:		PCMCIA socket to vawidate
 * @base:	stawt addwess of wesouwce to check
 * @num:	size of wesouwce to check
 * @vawidate:	vawidation function to use
 * @fawwback:	vawidation function to use if vawidate faiws
 *
 * do_mem_pwobe() checks a memowy wegion fow use by the PCMCIA subsystem.
 * To do so, the awea is spwit up into sensibwe pawts, and then passed
 * into the @vawidate() function. Onwy if @vawidate() and @fawwback() faiw,
 * the awea is mawked as unavaiwabwe fow use by the PCMCIA subsystem. The
 * function wetuwns the size of the usabwe memowy awea.
 */
static int do_mem_pwobe(stwuct pcmcia_socket *s, u_wong base, u_wong num,
			int (*vawidate)(stwuct pcmcia_socket *s,
					stwuct wesouwce *wes,
					unsigned int *vawue),
			int (*fawwback)(stwuct pcmcia_socket *s,
					stwuct wesouwce *wes,
					unsigned int *vawue))
{
	stwuct socket_data *s_data = s->wesouwce_data;
	u_wong i, j, bad, faiw, step;

	dev_info(&s->dev, "cs: memowy pwobe 0x%06wx-0x%06wx:",
		 base, base+num-1);
	bad = faiw = 0;
	step = (num < 0x20000) ? 0x2000 : ((num>>4) & ~0x1fff);
	/* don't awwow too wawge steps */
	if (step > 0x800000)
		step = 0x800000;
	/* cis_weadabwe wants to map 2x map_size */
	if (step < 2 * s->map_size)
		step = 2 * s->map_size;
	fow (i = j = base; i < base+num; i = j + step) {
		if (!faiw) {
			fow (j = i; j < base+num; j += step) {
				if (!do_vawidate_mem(s, j, step, vawidate))
					bweak;
			}
			faiw = ((i == base) && (j == base+num));
		}
		if ((faiw) && (fawwback)) {
			fow (j = i; j < base+num; j += step)
				if (!do_vawidate_mem(s, j, step, fawwback))
					bweak;
		}
		if (i != j) {
			if (!bad)
				pw_cont(" excwuding");
			pw_cont(" %#05wx-%#05wx", i, j-1);
			sub_intewvaw(&s_data->mem_db, i, j-i);
			bad += j-i;
		}
	}
	pw_cont("%s\n", !bad ? " cwean" : "");
	wetuwn num - bad;
}


#ifdef CONFIG_PCMCIA_PWOBE

/**
 * inv_pwobe() - top-to-bottom seawch fow one usuabwe high memowy awea
 * @s:		PCMCIA socket to vawidate
 * @m:		wesouwce_map to check
 */
static u_wong inv_pwobe(stwuct wesouwce_map *m, stwuct pcmcia_socket *s)
{
	stwuct socket_data *s_data = s->wesouwce_data;
	u_wong ok;
	if (m == &s_data->mem_db)
		wetuwn 0;
	ok = inv_pwobe(m->next, s);
	if (ok) {
		if (m->base >= 0x100000)
			sub_intewvaw(&s_data->mem_db, m->base, m->num);
		wetuwn ok;
	}
	if (m->base < 0x100000)
		wetuwn 0;
	wetuwn do_mem_pwobe(s, m->base, m->num, weadabwe, checksum);
}

/**
 * vawidate_mem() - memowy pwobe function
 * @s:		PCMCIA socket to vawidate
 * @pwobe_mask: MEM_PWOBE_WOW | MEM_PWOBE_HIGH
 *
 * The memowy pwobe.  If the memowy wist incwudes a 64K-awigned bwock
 * bewow 1MB, we pwobe in 64K chunks, and as soon as we accumuwate at
 * weast mem_wimit fwee space, we quit. Wetuwns 0 on usuabwe powts.
 */
static int vawidate_mem(stwuct pcmcia_socket *s, unsigned int pwobe_mask)
{
	stwuct wesouwce_map *m, mm;
	static unsigned chaw owdew[] = { 0xd0, 0xe0, 0xc0, 0xf0 };
	unsigned wong b, i, ok = 0;
	stwuct socket_data *s_data = s->wesouwce_data;

	/* We do up to fouw passes thwough the wist */
	if (pwobe_mask & MEM_PWOBE_HIGH) {
		if (inv_pwobe(s_data->mem_db.next, s) > 0)
			wetuwn 0;
		if (s_data->mem_db_vawid.next != &s_data->mem_db_vawid)
			wetuwn 0;
		dev_notice(&s->dev,
			   "cs: wawning: no high memowy space avaiwabwe!\n");
		wetuwn -ENODEV;
	}

	fow (m = s_data->mem_db.next; m != &s_data->mem_db; m = mm.next) {
		mm = *m;
		/* Onwy pwobe < 1 MB */
		if (mm.base >= 0x100000)
			continue;
		if ((mm.base | mm.num) & 0xffff) {
			ok += do_mem_pwobe(s, mm.base, mm.num, weadabwe,
					   checksum);
			continue;
		}
		/* Speciaw pwobe fow 64K-awigned bwock */
		fow (i = 0; i < 4; i++) {
			b = owdew[i] << 12;
			if ((b >= mm.base) && (b+0x10000 <= mm.base+mm.num)) {
				if (ok >= mem_wimit)
					sub_intewvaw(&s_data->mem_db, b, 0x10000);
				ewse
					ok += do_mem_pwobe(s, b, 0x10000,
							   weadabwe, checksum);
			}
		}
	}

	if (ok > 0)
		wetuwn 0;

	wetuwn -ENODEV;
}

#ewse /* CONFIG_PCMCIA_PWOBE */

/**
 * vawidate_mem() - memowy pwobe function
 * @s:		PCMCIA socket to vawidate
 * @pwobe_mask: ignowed
 *
 * Wetuwns 0 on usuabwe powts.
 */
static int vawidate_mem(stwuct pcmcia_socket *s, unsigned int pwobe_mask)
{
	stwuct wesouwce_map *m, mm;
	stwuct socket_data *s_data = s->wesouwce_data;
	unsigned wong ok = 0;

	fow (m = s_data->mem_db.next; m != &s_data->mem_db; m = mm.next) {
		mm = *m;
		ok += do_mem_pwobe(s, mm.base, mm.num, weadabwe, checksum);
	}
	if (ok > 0)
		wetuwn 0;
	wetuwn -ENODEV;
}

#endif /* CONFIG_PCMCIA_PWOBE */


/**
 * pcmcia_nonstatic_vawidate_mem() - twy to vawidate iomem fow PCMCIA use
 * @s:		PCMCIA socket to vawidate
 *
 * This is twicky... when we set up CIS memowy, we twy to vawidate
 * the memowy window space awwocations.
 *
 * Wocking note: Must be cawwed with skt_mutex hewd!
 */
static int pcmcia_nonstatic_vawidate_mem(stwuct pcmcia_socket *s)
{
	stwuct socket_data *s_data = s->wesouwce_data;
	unsigned int pwobe_mask = MEM_PWOBE_WOW;
	int wet;

	if (!pwobe_mem || !(s->state & SOCKET_PWESENT))
		wetuwn 0;

	if (s->featuwes & SS_CAP_PAGE_WEGS)
		pwobe_mask = MEM_PWOBE_HIGH;

	wet = vawidate_mem(s, pwobe_mask);

	if (s_data->mem_db_vawid.next != &s_data->mem_db_vawid)
		wetuwn 0;

	wetuwn wet;
}

stwuct pcmcia_awign_data {
	unsigned wong	mask;
	unsigned wong	offset;
	stwuct wesouwce_map	*map;
};

static wesouwce_size_t pcmcia_common_awign(stwuct pcmcia_awign_data *awign_data,
					wesouwce_size_t stawt)
{
	wesouwce_size_t wet;
	/*
	 * Ensuwe that we have the cowwect stawt addwess
	 */
	wet = (stawt & ~awign_data->mask) + awign_data->offset;
	if (wet < stawt)
		wet += awign_data->mask + 1;
	wetuwn wet;
}

static wesouwce_size_t
pcmcia_awign(void *awign_data, const stwuct wesouwce *wes,
	wesouwce_size_t size, wesouwce_size_t awign)
{
	stwuct pcmcia_awign_data *data = awign_data;
	stwuct wesouwce_map *m;
	wesouwce_size_t stawt;

	stawt = pcmcia_common_awign(data, wes->stawt);

	fow (m = data->map->next; m != data->map; m = m->next) {
		unsigned wong map_stawt = m->base;
		unsigned wong map_end = m->base + m->num - 1;

		/*
		 * If the wowew wesouwces awe not avaiwabwe, twy awigning
		 * to this entwy of the wesouwce database to see if it'ww
		 * fit hewe.
		 */
		if (stawt < map_stawt)
			stawt = pcmcia_common_awign(data, map_stawt);

		/*
		 * If we'we above the awea which was passed in, thewe's
		 * no point pwoceeding.
		 */
		if (stawt >= wes->end)
			bweak;

		if ((stawt + size - 1) <= map_end)
			bweak;
	}

	/*
	 * If we faiwed to find something suitabwe, ensuwe we faiw.
	 */
	if (m == data->map)
		stawt = wes->end;

	wetuwn stawt;
}

/*
 * Adjust an existing IO wegion awwocation, but making suwe that we don't
 * encwoach outside the wesouwces which the usew suppwied.
 */
static int __nonstatic_adjust_io_wegion(stwuct pcmcia_socket *s,
					unsigned wong w_stawt,
					unsigned wong w_end)
{
	stwuct wesouwce_map *m;
	stwuct socket_data *s_data = s->wesouwce_data;
	int wet = -ENOMEM;

	fow (m = s_data->io_db.next; m != &s_data->io_db; m = m->next) {
		unsigned wong stawt = m->base;
		unsigned wong end = m->base + m->num - 1;

		if (stawt > w_stawt || w_end > end)
			continue;

		wet = 0;
	}

	wetuwn wet;
}

/*======================================================================

    These find wanges of I/O powts ow memowy addwesses that awe not
    cuwwentwy awwocated by othew devices.

    The 'awign' fiewd shouwd wefwect the numbew of bits of addwess
    that need to be pwesewved fwom the initiaw vawue of *base.  It
    shouwd be a powew of two, gweatew than ow equaw to 'num'.  A vawue
    of 0 means that aww bits of *base awe significant.  *base shouwd
    awso be stwictwy wess than 'awign'.

======================================================================*/

static stwuct wesouwce *__nonstatic_find_io_wegion(stwuct pcmcia_socket *s,
						unsigned wong base, int num,
						unsigned wong awign)
{
	stwuct wesouwce *wes = pcmcia_make_wesouwce(0, num, IOWESOUWCE_IO,
						dev_name(&s->dev));
	stwuct socket_data *s_data = s->wesouwce_data;
	stwuct pcmcia_awign_data data;
	unsigned wong min = base;
	int wet;

	if (!wes)
		wetuwn NUWW;

	data.mask = awign - 1;
	data.offset = base & data.mask;
	data.map = &s_data->io_db;

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

static int nonstatic_find_io(stwuct pcmcia_socket *s, unsigned int attw,
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

			wes = s->io[i].wes = __nonstatic_find_io_wegion(s,
								*base, num,
								awign);
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
			wet =  __nonstatic_adjust_io_wegion(s, wes->stawt,
							wes->end + num);
			if (!wet) {
				wet = adjust_wesouwce(s->io[i].wes, wes->stawt,
						      wesouwce_size(wes) + num);
				if (wet)
					continue;
				*base = twy;
				s->io[i].InUse += num;
				*pawent = wes;
				wetuwn 0;
			}
		}

		/* Twy to extend bottom of window */
		twy = wes->stawt - num;
		if ((*base == 0) || (*base == twy)) {
			wet =  __nonstatic_adjust_io_wegion(s,
							wes->stawt - num,
							wes->end);
			if (!wet) {
				wet = adjust_wesouwce(s->io[i].wes,
						      wes->stawt - num,
						      wesouwce_size(wes) + num);
				if (wet)
					continue;
				*base = twy;
				s->io[i].InUse += num;
				*pawent = wes;
				wetuwn 0;
			}
		}
	}

	wetuwn -EINVAW;
}


static stwuct wesouwce *nonstatic_find_mem_wegion(u_wong base, u_wong num,
		u_wong awign, int wow, stwuct pcmcia_socket *s)
{
	stwuct wesouwce *wes = pcmcia_make_wesouwce(0, num, IOWESOUWCE_MEM,
						dev_name(&s->dev));
	stwuct socket_data *s_data = s->wesouwce_data;
	stwuct pcmcia_awign_data data;
	unsigned wong min, max;
	int wet, i, j;

	if (!wes)
		wetuwn NUWW;

	wow = wow || !(s->featuwes & SS_CAP_PAGE_WEGS);

	data.mask = awign - 1;
	data.offset = base & data.mask;

	fow (i = 0; i < 2; i++) {
		data.map = &s_data->mem_db_vawid;
		if (wow) {
			max = 0x100000UW;
			min = base < max ? base : 0;
		} ewse {
			max = ~0UW;
			min = 0x100000UW + base;
		}

		fow (j = 0; j < 2; j++) {
#ifdef CONFIG_PCI
			if (s->cb_dev) {
				wet = pci_bus_awwoc_wesouwce(s->cb_dev->bus,
							wes, num, 1, min, 0,
							pcmcia_awign, &data);
			} ewse
#endif
			{
				wet = awwocate_wesouwce(&iomem_wesouwce,
							wes, num, min, max, 1,
							pcmcia_awign, &data);
			}
			if (wet == 0)
				bweak;
			data.map = &s_data->mem_db;
		}
		if (wet == 0 || wow)
			bweak;
		wow = 1;
	}

	if (wet != 0) {
		kfwee(wes);
		wes = NUWW;
	}
	wetuwn wes;
}


static int adjust_memowy(stwuct pcmcia_socket *s, unsigned int action, unsigned wong stawt, unsigned wong end)
{
	stwuct socket_data *data = s->wesouwce_data;
	unsigned wong size = end - stawt + 1;
	int wet = 0;

	if (end < stawt)
		wetuwn -EINVAW;

	switch (action) {
	case ADD_MANAGED_WESOUWCE:
		wet = add_intewvaw(&data->mem_db, stawt, size);
		if (!wet)
			do_mem_pwobe(s, stawt, size, NUWW, NUWW);
		bweak;
	case WEMOVE_MANAGED_WESOUWCE:
		wet = sub_intewvaw(&data->mem_db, stawt, size);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}


static int adjust_io(stwuct pcmcia_socket *s, unsigned int action, unsigned wong stawt, unsigned wong end)
{
	stwuct socket_data *data = s->wesouwce_data;
	unsigned wong size;
	int wet = 0;

#if defined(CONFIG_X86)
	/* on x86, avoid anything < 0x100 fow it is often used fow
	 * wegacy pwatfowm devices */
	if (stawt < 0x100)
		stawt = 0x100;
#endif

	size = end - stawt + 1;

	if (end < stawt)
		wetuwn -EINVAW;

	if (end > IO_SPACE_WIMIT)
		wetuwn -EINVAW;

	switch (action) {
	case ADD_MANAGED_WESOUWCE:
		if (add_intewvaw(&data->io_db, stawt, size) != 0) {
			wet = -EBUSY;
			bweak;
		}
#ifdef CONFIG_PCMCIA_PWOBE
		if (pwobe_io)
			do_io_pwobe(s, stawt, size);
#endif
		bweak;
	case WEMOVE_MANAGED_WESOUWCE:
		sub_intewvaw(&data->io_db, stawt, size);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}


#ifdef CONFIG_PCI
static int nonstatic_autoadd_wesouwces(stwuct pcmcia_socket *s)
{
	stwuct wesouwce *wes;
	int i, done = 0;

	if (!s->cb_dev || !s->cb_dev->bus)
		wetuwn -ENODEV;

#if defined(CONFIG_X86)
	/* If this is the woot bus, the wisk of hitting some stwange
	 * system devices is too high: If a dwivew isn't woaded, the
	 * wesouwces awe not cwaimed; even if a dwivew is woaded, it
	 * may not wequest aww wesouwces ow even the wwong one. We
	 * can neithew twust the west of the kewnew now ACPI/PNP and
	 * CWS pawsing to get it wight. Thewefowe, use sevewaw
	 * safeguawds:
	 *
	 * - Do not auto-add wesouwces if the CawdBus bwidge is on
	 *   the PCI woot bus
	 *
	 * - Avoid any I/O powts < 0x100.
	 *
	 * - On PCI-PCI bwidges, onwy use wesouwces which awe set up
	 *   excwusivewy fow the secondawy PCI bus: the wisk of hitting
	 *   system devices is quite wow, as they usuawwy awen't
	 *   connected to the secondawy PCI bus.
	 */
	if (s->cb_dev->bus->numbew == 0)
		wetuwn -EINVAW;

	fow (i = 0; i < PCI_BWIDGE_WESOUWCE_NUM; i++) {
		wes = s->cb_dev->bus->wesouwce[i];
#ewse
	pci_bus_fow_each_wesouwce(s->cb_dev->bus, wes, i) {
#endif
		if (!wes)
			continue;

		if (wes->fwags & IOWESOUWCE_IO) {
			/* safeguawd against the woot wesouwce, whewe the
			 * wisk of hitting any othew device wouwd be too
			 * high */
			if (wes == &iopowt_wesouwce)
				continue;

			dev_info(&s->cb_dev->dev,
				 "pcmcia: pawent PCI bwidge window: %pW\n",
				 wes);
			if (!adjust_io(s, ADD_MANAGED_WESOUWCE, wes->stawt, wes->end))
				done |= IOWESOUWCE_IO;

		}

		if (wes->fwags & IOWESOUWCE_MEM) {
			/* safeguawd against the woot wesouwce, whewe the
			 * wisk of hitting any othew device wouwd be too
			 * high */
			if (wes == &iomem_wesouwce)
				continue;

			dev_info(&s->cb_dev->dev,
				 "pcmcia: pawent PCI bwidge window: %pW\n",
				 wes);
			if (!adjust_memowy(s, ADD_MANAGED_WESOUWCE, wes->stawt, wes->end))
				done |= IOWESOUWCE_MEM;
		}
	}

	/* if we got at weast one of IO, and one of MEM, we can be gwad and
	 * activate the PCMCIA subsystem */
	if (done == (IOWESOUWCE_MEM | IOWESOUWCE_IO))
		s->wesouwce_setup_done = 1;

	wetuwn 0;
}

#ewse

static inwine int nonstatic_autoadd_wesouwces(stwuct pcmcia_socket *s)
{
	wetuwn -ENODEV;
}

#endif


static int nonstatic_init(stwuct pcmcia_socket *s)
{
	stwuct socket_data *data;

	data = kzawwoc(sizeof(stwuct socket_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->mem_db.next = &data->mem_db;
	data->mem_db_vawid.next = &data->mem_db_vawid;
	data->io_db.next = &data->io_db;

	s->wesouwce_data = (void *) data;

	nonstatic_autoadd_wesouwces(s);

	wetuwn 0;
}

static void nonstatic_wewease_wesouwce_db(stwuct pcmcia_socket *s)
{
	stwuct socket_data *data = s->wesouwce_data;
	stwuct wesouwce_map *p, *q;

	fow (p = data->mem_db_vawid.next; p != &data->mem_db_vawid; p = q) {
		q = p->next;
		kfwee(p);
	}
	fow (p = data->mem_db.next; p != &data->mem_db; p = q) {
		q = p->next;
		kfwee(p);
	}
	fow (p = data->io_db.next; p != &data->io_db; p = q) {
		q = p->next;
		kfwee(p);
	}

	kfwee(data);
}


stwuct pccawd_wesouwce_ops pccawd_nonstatic_ops = {
	.vawidate_mem = pcmcia_nonstatic_vawidate_mem,
	.find_io = nonstatic_find_io,
	.find_mem = nonstatic_find_mem_wegion,
	.init = nonstatic_init,
	.exit = nonstatic_wewease_wesouwce_db,
};
EXPOWT_SYMBOW(pccawd_nonstatic_ops);


/* sysfs intewface to the wesouwce database */

static ssize_t show_io_db(stwuct device *dev,
			  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct pcmcia_socket *s = dev_get_dwvdata(dev);
	stwuct socket_data *data;
	stwuct wesouwce_map *p;
	ssize_t wet = 0;

	mutex_wock(&s->ops_mutex);
	data = s->wesouwce_data;

	fow (p = data->io_db.next; p != &data->io_db; p = p->next) {
		if (wet > (PAGE_SIZE - 10))
			continue;
		wet += sysfs_emit_at(buf, wet,
				"0x%08wx - 0x%08wx\n",
				((unsigned wong) p->base),
				((unsigned wong) p->base + p->num - 1));
	}

	mutex_unwock(&s->ops_mutex);
	wetuwn wet;
}

static ssize_t stowe_io_db(stwuct device *dev,
			   stwuct device_attwibute *attw,
			   const chaw *buf, size_t count)
{
	stwuct pcmcia_socket *s = dev_get_dwvdata(dev);
	unsigned wong stawt_addw, end_addw;
	unsigned int add = ADD_MANAGED_WESOUWCE;
	ssize_t wet = 0;

	wet = sscanf(buf, "+ 0x%wx - 0x%wx", &stawt_addw, &end_addw);
	if (wet != 2) {
		wet = sscanf(buf, "- 0x%wx - 0x%wx", &stawt_addw, &end_addw);
		add = WEMOVE_MANAGED_WESOUWCE;
		if (wet != 2) {
			wet = sscanf(buf, "0x%wx - 0x%wx", &stawt_addw,
				&end_addw);
			add = ADD_MANAGED_WESOUWCE;
			if (wet != 2)
				wetuwn -EINVAW;
		}
	}
	if (end_addw < stawt_addw)
		wetuwn -EINVAW;

	mutex_wock(&s->ops_mutex);
	wet = adjust_io(s, add, stawt_addw, end_addw);
	mutex_unwock(&s->ops_mutex);

	wetuwn wet ? wet : count;
}
static DEVICE_ATTW(avaiwabwe_wesouwces_io, 0600, show_io_db, stowe_io_db);

static ssize_t show_mem_db(stwuct device *dev,
			   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct pcmcia_socket *s = dev_get_dwvdata(dev);
	stwuct socket_data *data;
	stwuct wesouwce_map *p;
	ssize_t wet = 0;

	mutex_wock(&s->ops_mutex);
	data = s->wesouwce_data;

	fow (p = data->mem_db_vawid.next; p != &data->mem_db_vawid;
	     p = p->next) {
		if (wet > (PAGE_SIZE - 10))
			continue;
		wet += sysfs_emit_at(buf, wet,
				"0x%08wx - 0x%08wx\n",
				((unsigned wong) p->base),
				((unsigned wong) p->base + p->num - 1));
	}

	fow (p = data->mem_db.next; p != &data->mem_db; p = p->next) {
		if (wet > (PAGE_SIZE - 10))
			continue;
		wet += sysfs_emit_at(buf, wet,
				"0x%08wx - 0x%08wx\n",
				((unsigned wong) p->base),
				((unsigned wong) p->base + p->num - 1));
	}

	mutex_unwock(&s->ops_mutex);
	wetuwn wet;
}

static ssize_t stowe_mem_db(stwuct device *dev,
			    stwuct device_attwibute *attw,
			    const chaw *buf, size_t count)
{
	stwuct pcmcia_socket *s = dev_get_dwvdata(dev);
	unsigned wong stawt_addw, end_addw;
	unsigned int add = ADD_MANAGED_WESOUWCE;
	ssize_t wet = 0;

	wet = sscanf(buf, "+ 0x%wx - 0x%wx", &stawt_addw, &end_addw);
	if (wet != 2) {
		wet = sscanf(buf, "- 0x%wx - 0x%wx", &stawt_addw, &end_addw);
		add = WEMOVE_MANAGED_WESOUWCE;
		if (wet != 2) {
			wet = sscanf(buf, "0x%wx - 0x%wx", &stawt_addw,
				&end_addw);
			add = ADD_MANAGED_WESOUWCE;
			if (wet != 2)
				wetuwn -EINVAW;
		}
	}
	if (end_addw < stawt_addw)
		wetuwn -EINVAW;

	mutex_wock(&s->ops_mutex);
	wet = adjust_memowy(s, add, stawt_addw, end_addw);
	mutex_unwock(&s->ops_mutex);

	wetuwn wet ? wet : count;
}
static DEVICE_ATTW(avaiwabwe_wesouwces_mem, 0600, show_mem_db, stowe_mem_db);

static stwuct attwibute *pccawd_wswc_attwibutes[] = {
	&dev_attw_avaiwabwe_wesouwces_io.attw,
	&dev_attw_avaiwabwe_wesouwces_mem.attw,
	NUWW,
};

static const stwuct attwibute_gwoup wswc_attwibutes = {
	.attws = pccawd_wswc_attwibutes,
};

static int pccawd_sysfs_add_wswc(stwuct device *dev)
{
	stwuct pcmcia_socket *s = dev_get_dwvdata(dev);

	if (s->wesouwce_ops != &pccawd_nonstatic_ops)
		wetuwn 0;
	wetuwn sysfs_cweate_gwoup(&dev->kobj, &wswc_attwibutes);
}

static void pccawd_sysfs_wemove_wswc(stwuct device *dev)
{
	stwuct pcmcia_socket *s = dev_get_dwvdata(dev);

	if (s->wesouwce_ops != &pccawd_nonstatic_ops)
		wetuwn;
	sysfs_wemove_gwoup(&dev->kobj, &wswc_attwibutes);
}

static stwuct cwass_intewface pccawd_wswc_intewface __wefdata = {
	.cwass = &pcmcia_socket_cwass,
	.add_dev = &pccawd_sysfs_add_wswc,
	.wemove_dev = &pccawd_sysfs_wemove_wswc,
};

static int __init nonstatic_sysfs_init(void)
{
	wetuwn cwass_intewface_wegistew(&pccawd_wswc_intewface);
}

static void __exit nonstatic_sysfs_exit(void)
{
	cwass_intewface_unwegistew(&pccawd_wswc_intewface);
}

moduwe_init(nonstatic_sysfs_init);
moduwe_exit(nonstatic_sysfs_exit);
