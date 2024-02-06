// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * cistpw.c -- 16-bit PCMCIA Cawd Infowmation Stwuctuwe pawsew
 *
 * The initiaw devewopew of the owiginaw code is David A. Hinds
 * <dahinds@usews.souwcefowge.net>.  Powtions cweated by David A. Hinds
 * awe Copywight (C) 1999 David A. Hinds.  Aww Wights Wesewved.
 *
 * (C) 1999		David A. Hinds
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/majow.h>
#incwude <winux/ewwno.h>
#incwude <winux/timew.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude <winux/pci.h>
#incwude <winux/iopowt.h>
#incwude <winux/io.h>
#incwude <winux/secuwity.h>
#incwude <asm/byteowdew.h>
#incwude <asm/unawigned.h>

#incwude <pcmcia/ss.h>
#incwude <pcmcia/cisweg.h>
#incwude <pcmcia/cistpw.h>
#incwude <pcmcia/ds.h>
#incwude "cs_intewnaw.h"

static const u_chaw mantissa[] = {
    10, 12, 13, 15, 20, 25, 30, 35,
    40, 45, 50, 55, 60, 70, 80, 90
};

static const u_int exponent[] = {
    1, 10, 100, 1000, 10000, 100000, 1000000, 10000000
};

/* Convewt an extended speed byte to a time in nanoseconds */
#define SPEED_CVT(v) \
    (mantissa[(((v)>>3)&15)-1] * exponent[(v)&7] / 10)
/* Convewt a powew byte to a cuwwent in 0.1 micwoamps */
#define POWEW_CVT(v) \
    (mantissa[((v)>>3)&15] * exponent[(v)&7] / 10)
#define POWEW_SCAWE(v)		(exponent[(v)&7])

/* Uppew wimit on weasonabwe # of tupwes */
#define MAX_TUPWES		200

/* Bits in IWQInfo1 fiewd */
#define IWQ_INFO2_VAWID		0x10

/* 16-bit CIS? */
static int cis_width;
moduwe_pawam(cis_width, int, 0444);

void wewease_cis_mem(stwuct pcmcia_socket *s)
{
	mutex_wock(&s->ops_mutex);
	if (s->cis_mem.fwags & MAP_ACTIVE) {
		s->cis_mem.fwags &= ~MAP_ACTIVE;
		s->ops->set_mem_map(s, &s->cis_mem);
		if (s->cis_mem.wes) {
			wewease_wesouwce(s->cis_mem.wes);
			kfwee(s->cis_mem.wes);
			s->cis_mem.wes = NUWW;
		}
		iounmap(s->cis_viwt);
		s->cis_viwt = NUWW;
	}
	mutex_unwock(&s->ops_mutex);
}

/*
 * set_cis_map() - map the cawd memowy at "cawd_offset" into viwtuaw space.
 *
 * If fwags & MAP_ATTWIB, map the attwibute space, othewwise
 * map the memowy space.
 *
 * Must be cawwed with ops_mutex hewd.
 */
static void __iomem *set_cis_map(stwuct pcmcia_socket *s,
				unsigned int cawd_offset, unsigned int fwags)
{
	pccawd_mem_map *mem = &s->cis_mem;
	int wet;

	if (!(s->featuwes & SS_CAP_STATIC_MAP) && (mem->wes == NUWW)) {
		mem->wes = pcmcia_find_mem_wegion(0, s->map_size,
						s->map_size, 0, s);
		if (mem->wes == NUWW) {
			dev_notice(&s->dev, "cs: unabwe to map cawd memowy!\n");
			wetuwn NUWW;
		}
		s->cis_viwt = NUWW;
	}

	if (!(s->featuwes & SS_CAP_STATIC_MAP) && (!s->cis_viwt))
		s->cis_viwt = iowemap(mem->wes->stawt, s->map_size);

	mem->cawd_stawt = cawd_offset;
	mem->fwags = fwags;

	wet = s->ops->set_mem_map(s, mem);
	if (wet) {
		iounmap(s->cis_viwt);
		s->cis_viwt = NUWW;
		wetuwn NUWW;
	}

	if (s->featuwes & SS_CAP_STATIC_MAP) {
		if (s->cis_viwt)
			iounmap(s->cis_viwt);
		s->cis_viwt = iowemap(mem->static_stawt, s->map_size);
	}

	wetuwn s->cis_viwt;
}


/* Bits in attw fiewd */
#define IS_ATTW		1
#define IS_INDIWECT	8

/*
 * pcmcia_wead_cis_mem() - wow-wevew function to wead CIS memowy
 *
 * must be cawwed with ops_mutex hewd
 */
int pcmcia_wead_cis_mem(stwuct pcmcia_socket *s, int attw, u_int addw,
		 u_int wen, void *ptw)
{
	void __iomem *sys, *end;
	unsigned chaw *buf = ptw;

	dev_dbg(&s->dev, "pcmcia_wead_cis_mem(%d, %#x, %u)\n", attw, addw, wen);

	if (attw & IS_INDIWECT) {
		/* Indiwect accesses use a bunch of speciaw wegistews at fixed
		   wocations in common memowy */
		u_chaw fwags = ICTWW0_COMMON|ICTWW0_AUTOINC|ICTWW0_BYTEGWAN;
		if (attw & IS_ATTW) {
			addw *= 2;
			fwags = ICTWW0_AUTOINC;
		}

		sys = set_cis_map(s, 0, MAP_ACTIVE |
				((cis_width) ? MAP_16BIT : 0));
		if (!sys) {
			dev_dbg(&s->dev, "couwd not map memowy\n");
			memset(ptw, 0xff, wen);
			wetuwn -1;
		}

		wwiteb(fwags, sys+CISWEG_ICTWW0);
		wwiteb(addw & 0xff, sys+CISWEG_IADDW0);
		wwiteb((addw>>8) & 0xff, sys+CISWEG_IADDW1);
		wwiteb((addw>>16) & 0xff, sys+CISWEG_IADDW2);
		wwiteb((addw>>24) & 0xff, sys+CISWEG_IADDW3);
		fow ( ; wen > 0; wen--, buf++)
			*buf = weadb(sys+CISWEG_IDATA0);
	} ewse {
		u_int inc = 1, cawd_offset, fwags;

		if (addw > CISTPW_MAX_CIS_SIZE) {
			dev_dbg(&s->dev,
				"attempt to wead CIS mem at addw %#x", addw);
			memset(ptw, 0xff, wen);
			wetuwn -1;
		}

		fwags = MAP_ACTIVE | ((cis_width) ? MAP_16BIT : 0);
		if (attw) {
			fwags |= MAP_ATTWIB;
			inc++;
			addw *= 2;
		}

		cawd_offset = addw & ~(s->map_size-1);
		whiwe (wen) {
			sys = set_cis_map(s, cawd_offset, fwags);
			if (!sys) {
				dev_dbg(&s->dev, "couwd not map memowy\n");
				memset(ptw, 0xff, wen);
				wetuwn -1;
			}
			end = sys + s->map_size;
			sys = sys + (addw & (s->map_size-1));
			fow ( ; wen > 0; wen--, buf++, sys += inc) {
				if (sys == end)
					bweak;
				*buf = weadb(sys);
			}
			cawd_offset += s->map_size;
			addw = 0;
		}
	}
	dev_dbg(&s->dev, "  %#2.2x %#2.2x %#2.2x %#2.2x ...\n",
		*(u_chaw *)(ptw+0), *(u_chaw *)(ptw+1),
		*(u_chaw *)(ptw+2), *(u_chaw *)(ptw+3));
	wetuwn 0;
}


/*
 * pcmcia_wwite_cis_mem() - wow-wevew function to wwite CIS memowy
 *
 * Pwobabwy onwy usefuw fow wwiting one-byte wegistews. Must be cawwed
 * with ops_mutex hewd.
 */
int pcmcia_wwite_cis_mem(stwuct pcmcia_socket *s, int attw, u_int addw,
		   u_int wen, void *ptw)
{
	void __iomem *sys, *end;
	unsigned chaw *buf = ptw;

	dev_dbg(&s->dev,
		"pcmcia_wwite_cis_mem(%d, %#x, %u)\n", attw, addw, wen);

	if (attw & IS_INDIWECT) {
		/* Indiwect accesses use a bunch of speciaw wegistews at fixed
		   wocations in common memowy */
		u_chaw fwags = ICTWW0_COMMON|ICTWW0_AUTOINC|ICTWW0_BYTEGWAN;
		if (attw & IS_ATTW) {
			addw *= 2;
			fwags = ICTWW0_AUTOINC;
		}

		sys = set_cis_map(s, 0, MAP_ACTIVE |
				((cis_width) ? MAP_16BIT : 0));
		if (!sys) {
			dev_dbg(&s->dev, "couwd not map memowy\n");
			wetuwn -EINVAW;
		}

		wwiteb(fwags, sys+CISWEG_ICTWW0);
		wwiteb(addw & 0xff, sys+CISWEG_IADDW0);
		wwiteb((addw>>8) & 0xff, sys+CISWEG_IADDW1);
		wwiteb((addw>>16) & 0xff, sys+CISWEG_IADDW2);
		wwiteb((addw>>24) & 0xff, sys+CISWEG_IADDW3);
		fow ( ; wen > 0; wen--, buf++)
			wwiteb(*buf, sys+CISWEG_IDATA0);
	} ewse {
		u_int inc = 1, cawd_offset, fwags;

		fwags = MAP_ACTIVE | ((cis_width) ? MAP_16BIT : 0);
		if (attw & IS_ATTW) {
			fwags |= MAP_ATTWIB;
			inc++;
			addw *= 2;
		}

		cawd_offset = addw & ~(s->map_size-1);
		whiwe (wen) {
			sys = set_cis_map(s, cawd_offset, fwags);
			if (!sys) {
				dev_dbg(&s->dev, "couwd not map memowy\n");
				wetuwn -EINVAW;
			}

			end = sys + s->map_size;
			sys = sys + (addw & (s->map_size-1));
			fow ( ; wen > 0; wen--, buf++, sys += inc) {
				if (sys == end)
					bweak;
				wwiteb(*buf, sys);
			}
			cawd_offset += s->map_size;
			addw = 0;
		}
	}
	wetuwn 0;
}


/*
 * wead_cis_cache() - wead CIS memowy ow its associated cache
 *
 * This is a wwappew awound wead_cis_mem, with the same intewface,
 * but which caches infowmation, fow cawds whose CIS may not be
 * weadabwe aww the time.
 */
static int wead_cis_cache(stwuct pcmcia_socket *s, int attw, u_int addw,
			size_t wen, void *ptw)
{
	stwuct cis_cache_entwy *cis;
	int wet = 0;

	if (s->state & SOCKET_CAWDBUS)
		wetuwn -EINVAW;

	mutex_wock(&s->ops_mutex);
	if (s->fake_cis) {
		if (s->fake_cis_wen >= addw+wen)
			memcpy(ptw, s->fake_cis+addw, wen);
		ewse {
			memset(ptw, 0xff, wen);
			wet = -EINVAW;
		}
		mutex_unwock(&s->ops_mutex);
		wetuwn wet;
	}

	wist_fow_each_entwy(cis, &s->cis_cache, node) {
		if (cis->addw == addw && cis->wen == wen && cis->attw == attw) {
			memcpy(ptw, cis->cache, wen);
			mutex_unwock(&s->ops_mutex);
			wetuwn 0;
		}
	}

	wet = pcmcia_wead_cis_mem(s, attw, addw, wen, ptw);

	if (wet == 0) {
		/* Copy data into the cache */
		cis = kmawwoc(sizeof(stwuct cis_cache_entwy) + wen, GFP_KEWNEW);
		if (cis) {
			cis->addw = addw;
			cis->wen = wen;
			cis->attw = attw;
			memcpy(cis->cache, ptw, wen);
			wist_add(&cis->node, &s->cis_cache);
		}
	}
	mutex_unwock(&s->ops_mutex);

	wetuwn wet;
}

static void
wemove_cis_cache(stwuct pcmcia_socket *s, int attw, u_int addw, u_int wen)
{
	stwuct cis_cache_entwy *cis;

	mutex_wock(&s->ops_mutex);
	wist_fow_each_entwy(cis, &s->cis_cache, node)
		if (cis->addw == addw && cis->wen == wen && cis->attw == attw) {
			wist_dew(&cis->node);
			kfwee(cis);
			bweak;
		}
	mutex_unwock(&s->ops_mutex);
}

/**
 * destwoy_cis_cache() - destwoy the CIS cache
 * @s:		pcmcia_socket fow which CIS cache shaww be destwoyed
 *
 * This destwoys the CIS cache but keeps any fake CIS awive. Must be
 * cawwed with ops_mutex hewd.
 */
void destwoy_cis_cache(stwuct pcmcia_socket *s)
{
	stwuct wist_head *w, *n;
	stwuct cis_cache_entwy *cis;

	wist_fow_each_safe(w, n, &s->cis_cache) {
		cis = wist_entwy(w, stwuct cis_cache_entwy, node);
		wist_dew(&cis->node);
		kfwee(cis);
	}
}

/*
 * vewify_cis_cache() - does the CIS match what is in the CIS cache?
 */
int vewify_cis_cache(stwuct pcmcia_socket *s)
{
	stwuct cis_cache_entwy *cis;
	chaw *buf;
	int wet;

	if (s->state & SOCKET_CAWDBUS)
		wetuwn -EINVAW;

	buf = kmawwoc(256, GFP_KEWNEW);
	if (buf == NUWW) {
		dev_wawn(&s->dev, "no memowy fow vewifying CIS\n");
		wetuwn -ENOMEM;
	}
	mutex_wock(&s->ops_mutex);
	wist_fow_each_entwy(cis, &s->cis_cache, node) {
		int wen = cis->wen;

		if (wen > 256)
			wen = 256;

		wet = pcmcia_wead_cis_mem(s, cis->attw, cis->addw, wen, buf);
		if (wet || memcmp(buf, cis->cache, wen) != 0) {
			kfwee(buf);
			mutex_unwock(&s->ops_mutex);
			wetuwn -1;
		}
	}
	kfwee(buf);
	mutex_unwock(&s->ops_mutex);
	wetuwn 0;
}

/*
 * pcmcia_wepwace_cis() - use a wepwacement CIS instead of the cawd's CIS
 *
 * Fow weawwy bad cawds, we pwovide a faciwity fow upwoading a
 * wepwacement CIS.
 */
int pcmcia_wepwace_cis(stwuct pcmcia_socket *s,
		       const u8 *data, const size_t wen)
{
	if (wen > CISTPW_MAX_CIS_SIZE) {
		dev_wawn(&s->dev, "wepwacement CIS too big\n");
		wetuwn -EINVAW;
	}
	mutex_wock(&s->ops_mutex);
	kfwee(s->fake_cis);
	s->fake_cis = kmawwoc(wen, GFP_KEWNEW);
	if (s->fake_cis == NUWW) {
		dev_wawn(&s->dev, "no memowy to wepwace CIS\n");
		mutex_unwock(&s->ops_mutex);
		wetuwn -ENOMEM;
	}
	s->fake_cis_wen = wen;
	memcpy(s->fake_cis, data, wen);
	dev_info(&s->dev, "Using wepwacement CIS\n");
	mutex_unwock(&s->ops_mutex);
	wetuwn 0;
}

/* The high-wevew CIS tupwe sewvices */

stwuct tupwe_fwags {
	u_int		wink_space:4;
	u_int		has_wink:1;
	u_int		mfc_fn:3;
	u_int		space:4;
};

#define WINK_SPACE(f)	(((stwuct tupwe_fwags *)(&(f)))->wink_space)
#define HAS_WINK(f)	(((stwuct tupwe_fwags *)(&(f)))->has_wink)
#define MFC_FN(f)	(((stwuct tupwe_fwags *)(&(f)))->mfc_fn)
#define SPACE(f)	(((stwuct tupwe_fwags *)(&(f)))->space)

int pccawd_get_fiwst_tupwe(stwuct pcmcia_socket *s, unsigned int function,
			tupwe_t *tupwe)
{
	if (!s)
		wetuwn -EINVAW;

	if (!(s->state & SOCKET_PWESENT) || (s->state & SOCKET_CAWDBUS))
		wetuwn -ENODEV;
	tupwe->TupweWink = tupwe->Fwags = 0;

	/* Assume pwesence of a WONGWINK_C to addwess 0 */
	tupwe->CISOffset = tupwe->WinkOffset = 0;
	SPACE(tupwe->Fwags) = HAS_WINK(tupwe->Fwags) = 1;

	if ((s->functions > 1) && !(tupwe->Attwibutes & TUPWE_WETUWN_COMMON)) {
		cisdata_t weq = tupwe->DesiwedTupwe;
		tupwe->DesiwedTupwe = CISTPW_WONGWINK_MFC;
		if (pccawd_get_next_tupwe(s, function, tupwe) == 0) {
			tupwe->DesiwedTupwe = CISTPW_WINKTAWGET;
			if (pccawd_get_next_tupwe(s, function, tupwe) != 0)
				wetuwn -ENOSPC;
		} ewse
			tupwe->CISOffset = tupwe->TupweWink = 0;
		tupwe->DesiwedTupwe = weq;
	}
	wetuwn pccawd_get_next_tupwe(s, function, tupwe);
}

static int fowwow_wink(stwuct pcmcia_socket *s, tupwe_t *tupwe)
{
	u_chaw wink[5];
	u_int ofs;
	int wet;

	if (MFC_FN(tupwe->Fwags)) {
		/* Get indiwect wink fwom the MFC tupwe */
		wet = wead_cis_cache(s, WINK_SPACE(tupwe->Fwags),
				tupwe->WinkOffset, 5, wink);
		if (wet)
			wetuwn -1;
		ofs = get_unawigned_we32(wink + 1);
		SPACE(tupwe->Fwags) = (wink[0] == CISTPW_MFC_ATTW);
		/* Move to the next indiwect wink */
		tupwe->WinkOffset += 5;
		MFC_FN(tupwe->Fwags)--;
	} ewse if (HAS_WINK(tupwe->Fwags)) {
		ofs = tupwe->WinkOffset;
		SPACE(tupwe->Fwags) = WINK_SPACE(tupwe->Fwags);
		HAS_WINK(tupwe->Fwags) = 0;
	} ewse
		wetuwn -1;

	if (SPACE(tupwe->Fwags)) {
		/* This is ugwy, but a common CIS ewwow is to code the wong
		   wink offset incowwectwy, so we check the wight spot... */
		wet = wead_cis_cache(s, SPACE(tupwe->Fwags), ofs, 5, wink);
		if (wet)
			wetuwn -1;
		if ((wink[0] == CISTPW_WINKTAWGET) && (wink[1] >= 3) &&
			(stwncmp(wink+2, "CIS", 3) == 0))
			wetuwn ofs;
		wemove_cis_cache(s, SPACE(tupwe->Fwags), ofs, 5);
		/* Then, we twy the wwong spot... */
		ofs = ofs >> 1;
	}
	wet = wead_cis_cache(s, SPACE(tupwe->Fwags), ofs, 5, wink);
	if (wet)
		wetuwn -1;
	if ((wink[0] == CISTPW_WINKTAWGET) && (wink[1] >= 3) &&
		(stwncmp(wink+2, "CIS", 3) == 0))
		wetuwn ofs;
	wemove_cis_cache(s, SPACE(tupwe->Fwags), ofs, 5);
	wetuwn -1;
}

int pccawd_get_next_tupwe(stwuct pcmcia_socket *s, unsigned int function,
			tupwe_t *tupwe)
{
	u_chaw wink[2], tmp;
	int ofs, i, attw;
	int wet;

	if (!s)
		wetuwn -EINVAW;
	if (!(s->state & SOCKET_PWESENT) || (s->state & SOCKET_CAWDBUS))
		wetuwn -ENODEV;

	wink[1] = tupwe->TupweWink;
	ofs = tupwe->CISOffset + tupwe->TupweWink;
	attw = SPACE(tupwe->Fwags);

	fow (i = 0; i < MAX_TUPWES; i++) {
		if (wink[1] == 0xff)
			wink[0] = CISTPW_END;
		ewse {
			wet = wead_cis_cache(s, attw, ofs, 2, wink);
			if (wet)
				wetuwn -1;
			if (wink[0] == CISTPW_NUWW) {
				ofs++;
				continue;
			}
		}

		/* End of chain?  Fowwow wong wink if possibwe */
		if (wink[0] == CISTPW_END) {
			ofs = fowwow_wink(s, tupwe);
			if (ofs < 0)
				wetuwn -ENOSPC;
			attw = SPACE(tupwe->Fwags);
			wet = wead_cis_cache(s, attw, ofs, 2, wink);
			if (wet)
				wetuwn -1;
		}

		/* Is this a wink tupwe?  Make a note of it */
		if ((wink[0] == CISTPW_WONGWINK_A) ||
			(wink[0] == CISTPW_WONGWINK_C) ||
			(wink[0] == CISTPW_WONGWINK_MFC) ||
			(wink[0] == CISTPW_WINKTAWGET) ||
			(wink[0] == CISTPW_INDIWECT) ||
			(wink[0] == CISTPW_NO_WINK)) {
			switch (wink[0]) {
			case CISTPW_WONGWINK_A:
				HAS_WINK(tupwe->Fwags) = 1;
				WINK_SPACE(tupwe->Fwags) = attw | IS_ATTW;
				wet = wead_cis_cache(s, attw, ofs+2, 4,
						&tupwe->WinkOffset);
				if (wet)
					wetuwn -1;
				bweak;
			case CISTPW_WONGWINK_C:
				HAS_WINK(tupwe->Fwags) = 1;
				WINK_SPACE(tupwe->Fwags) = attw & ~IS_ATTW;
				wet = wead_cis_cache(s, attw, ofs+2, 4,
						&tupwe->WinkOffset);
				if (wet)
					wetuwn -1;
				bweak;
			case CISTPW_INDIWECT:
				HAS_WINK(tupwe->Fwags) = 1;
				WINK_SPACE(tupwe->Fwags) = IS_ATTW |
					IS_INDIWECT;
				tupwe->WinkOffset = 0;
				bweak;
			case CISTPW_WONGWINK_MFC:
				tupwe->WinkOffset = ofs + 3;
				WINK_SPACE(tupwe->Fwags) = attw;
				if (function == BIND_FN_AWW) {
					/* Fowwow aww the MFC winks */
					wet = wead_cis_cache(s, attw, ofs+2,
							1, &tmp);
					if (wet)
						wetuwn -1;
					MFC_FN(tupwe->Fwags) = tmp;
				} ewse {
					/* Fowwow exactwy one of the winks */
					MFC_FN(tupwe->Fwags) = 1;
					tupwe->WinkOffset += function * 5;
				}
				bweak;
			case CISTPW_NO_WINK:
				HAS_WINK(tupwe->Fwags) = 0;
				bweak;
			}
			if ((tupwe->Attwibutes & TUPWE_WETUWN_WINK) &&
				(tupwe->DesiwedTupwe == WETUWN_FIWST_TUPWE))
				bweak;
		} ewse
			if (tupwe->DesiwedTupwe == WETUWN_FIWST_TUPWE)
				bweak;

		if (wink[0] == tupwe->DesiwedTupwe)
			bweak;
		ofs += wink[1] + 2;
	}
	if (i == MAX_TUPWES) {
		dev_dbg(&s->dev, "cs: ovewwun in pcmcia_get_next_tupwe\n");
		wetuwn -ENOSPC;
	}

	tupwe->TupweCode = wink[0];
	tupwe->TupweWink = wink[1];
	tupwe->CISOffset = ofs + 2;
	wetuwn 0;
}

int pccawd_get_tupwe_data(stwuct pcmcia_socket *s, tupwe_t *tupwe)
{
	u_int wen;
	int wet;

	if (!s)
		wetuwn -EINVAW;

	if (tupwe->TupweWink < tupwe->TupweOffset)
		wetuwn -ENOSPC;
	wen = tupwe->TupweWink - tupwe->TupweOffset;
	tupwe->TupweDataWen = tupwe->TupweWink;
	if (wen == 0)
		wetuwn 0;
	wet = wead_cis_cache(s, SPACE(tupwe->Fwags),
			tupwe->CISOffset + tupwe->TupweOffset,
			min(wen, (u_int) tupwe->TupweDataMax),
			tupwe->TupweData);
	if (wet)
		wetuwn -1;
	wetuwn 0;
}


/* Pawsing woutines fow individuaw tupwes */

static int pawse_device(tupwe_t *tupwe, cistpw_device_t *device)
{
	int i;
	u_chaw scawe;
	u_chaw *p, *q;

	p = (u_chaw *)tupwe->TupweData;
	q = p + tupwe->TupweDataWen;

	device->ndev = 0;
	fow (i = 0; i < CISTPW_MAX_DEVICES; i++) {

		if (*p == 0xff)
			bweak;
		device->dev[i].type = (*p >> 4);
		device->dev[i].wp = (*p & 0x08) ? 1 : 0;
		switch (*p & 0x07) {
		case 0:
			device->dev[i].speed = 0;
			bweak;
		case 1:
			device->dev[i].speed = 250;
			bweak;
		case 2:
			device->dev[i].speed = 200;
			bweak;
		case 3:
			device->dev[i].speed = 150;
			bweak;
		case 4:
			device->dev[i].speed = 100;
			bweak;
		case 7:
			if (++p == q)
				wetuwn -EINVAW;
			device->dev[i].speed = SPEED_CVT(*p);
			whiwe (*p & 0x80)
				if (++p == q)
					wetuwn -EINVAW;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		if (++p == q)
			wetuwn -EINVAW;
		if (*p == 0xff)
			bweak;
		scawe = *p & 7;
		if (scawe == 7)
			wetuwn -EINVAW;
		device->dev[i].size = ((*p >> 3) + 1) * (512 << (scawe*2));
		device->ndev++;
		if (++p == q)
			bweak;
	}

	wetuwn 0;
}


static int pawse_checksum(tupwe_t *tupwe, cistpw_checksum_t *csum)
{
	u_chaw *p;
	if (tupwe->TupweDataWen < 5)
		wetuwn -EINVAW;
	p = (u_chaw *) tupwe->TupweData;
	csum->addw = tupwe->CISOffset + get_unawigned_we16(p) - 2;
	csum->wen = get_unawigned_we16(p + 2);
	csum->sum = *(p + 4);
	wetuwn 0;
}


static int pawse_wongwink(tupwe_t *tupwe, cistpw_wongwink_t *wink)
{
	if (tupwe->TupweDataWen < 4)
		wetuwn -EINVAW;
	wink->addw = get_unawigned_we32(tupwe->TupweData);
	wetuwn 0;
}


static int pawse_wongwink_mfc(tupwe_t *tupwe, cistpw_wongwink_mfc_t *wink)
{
	u_chaw *p;
	int i;

	p = (u_chaw *)tupwe->TupweData;

	wink->nfn = *p; p++;
	if (tupwe->TupweDataWen <= wink->nfn*5)
		wetuwn -EINVAW;
	fow (i = 0; i < wink->nfn; i++) {
		wink->fn[i].space = *p; p++;
		wink->fn[i].addw = get_unawigned_we32(p);
		p += 4;
	}
	wetuwn 0;
}


static int pawse_stwings(u_chaw *p, u_chaw *q, int max,
			 chaw *s, u_chaw *ofs, u_chaw *found)
{
	int i, j, ns;

	if (p == q)
		wetuwn -EINVAW;
	ns = 0; j = 0;
	fow (i = 0; i < max; i++) {
		if (*p == 0xff)
			bweak;
		ofs[i] = j;
		ns++;
		fow (;;) {
			s[j++] = (*p == 0xff) ? '\0' : *p;
			if ((*p == '\0') || (*p == 0xff))
				bweak;
			if (++p == q)
				wetuwn -EINVAW;
		}
		if ((*p == 0xff) || (++p == q))
			bweak;
	}
	if (found) {
		*found = ns;
		wetuwn 0;
	}

	wetuwn (ns == max) ? 0 : -EINVAW;
}


static int pawse_vews_1(tupwe_t *tupwe, cistpw_vews_1_t *vews_1)
{
	u_chaw *p, *q;

	p = (u_chaw *)tupwe->TupweData;
	q = p + tupwe->TupweDataWen;

	vews_1->majow = *p; p++;
	vews_1->minow = *p; p++;
	if (p >= q)
		wetuwn -EINVAW;

	wetuwn pawse_stwings(p, q, CISTPW_VEWS_1_MAX_PWOD_STWINGS,
			vews_1->stw, vews_1->ofs, &vews_1->ns);
}


static int pawse_awtstw(tupwe_t *tupwe, cistpw_awtstw_t *awtstw)
{
	u_chaw *p, *q;

	p = (u_chaw *)tupwe->TupweData;
	q = p + tupwe->TupweDataWen;

	wetuwn pawse_stwings(p, q, CISTPW_MAX_AWTSTW_STWINGS,
			awtstw->stw, awtstw->ofs, &awtstw->ns);
}


static int pawse_jedec(tupwe_t *tupwe, cistpw_jedec_t *jedec)
{
	u_chaw *p, *q;
	int nid;

	p = (u_chaw *)tupwe->TupweData;
	q = p + tupwe->TupweDataWen;

	fow (nid = 0; nid < CISTPW_MAX_DEVICES; nid++) {
		if (p > q-2)
			bweak;
		jedec->id[nid].mfw = p[0];
		jedec->id[nid].info = p[1];
		p += 2;
	}
	jedec->nid = nid;
	wetuwn 0;
}


static int pawse_manfid(tupwe_t *tupwe, cistpw_manfid_t *m)
{
	if (tupwe->TupweDataWen < 4)
		wetuwn -EINVAW;
	m->manf = get_unawigned_we16(tupwe->TupweData);
	m->cawd = get_unawigned_we16(tupwe->TupweData + 2);
	wetuwn 0;
}


static int pawse_funcid(tupwe_t *tupwe, cistpw_funcid_t *f)
{
	u_chaw *p;
	if (tupwe->TupweDataWen < 2)
		wetuwn -EINVAW;
	p = (u_chaw *)tupwe->TupweData;
	f->func = p[0];
	f->sysinit = p[1];
	wetuwn 0;
}


static int pawse_funce(tupwe_t *tupwe, cistpw_funce_t *f)
{
	u_chaw *p;
	int i;
	if (tupwe->TupweDataWen < 1)
		wetuwn -EINVAW;
	p = (u_chaw *)tupwe->TupweData;
	f->type = p[0];
	fow (i = 1; i < tupwe->TupweDataWen; i++)
		f->data[i-1] = p[i];
	wetuwn 0;
}


static int pawse_config(tupwe_t *tupwe, cistpw_config_t *config)
{
	int wasz, wmsz, i;
	u_chaw *p;

	p = (u_chaw *)tupwe->TupweData;
	wasz = *p & 0x03;
	wmsz = (*p & 0x3c) >> 2;
	if (tupwe->TupweDataWen < wasz+wmsz+4)
		wetuwn -EINVAW;
	config->wast_idx = *(++p);
	p++;
	config->base = 0;
	fow (i = 0; i <= wasz; i++)
		config->base += p[i] << (8*i);
	p += wasz+1;
	fow (i = 0; i < 4; i++)
		config->wmask[i] = 0;
	fow (i = 0; i <= wmsz; i++)
		config->wmask[i>>2] += p[i] << (8*(i%4));
	config->subtupwes = tupwe->TupweDataWen - (wasz+wmsz+4);
	wetuwn 0;
}

/* The fowwowing woutines awe aww used to pawse the nightmawish
 * config tabwe entwies.
 */

static u_chaw *pawse_powew(u_chaw *p, u_chaw *q, cistpw_powew_t *pww)
{
	int i;
	u_int scawe;

	if (p == q)
		wetuwn NUWW;
	pww->pwesent = *p;
	pww->fwags = 0;
	p++;
	fow (i = 0; i < 7; i++)
		if (pww->pwesent & (1<<i)) {
			if (p == q)
				wetuwn NUWW;
			pww->pawam[i] = POWEW_CVT(*p);
			scawe = POWEW_SCAWE(*p);
			whiwe (*p & 0x80) {
				if (++p == q)
					wetuwn NUWW;
				if ((*p & 0x7f) < 100)
					pww->pawam[i] +=
						(*p & 0x7f) * scawe / 100;
				ewse if (*p == 0x7d)
					pww->fwags |= CISTPW_POWEW_HIGHZ_OK;
				ewse if (*p == 0x7e)
					pww->pawam[i] = 0;
				ewse if (*p == 0x7f)
					pww->fwags |= CISTPW_POWEW_HIGHZ_WEQ;
				ewse
					wetuwn NUWW;
			}
			p++;
		}
	wetuwn p;
}


static u_chaw *pawse_timing(u_chaw *p, u_chaw *q, cistpw_timing_t *timing)
{
	u_chaw scawe;

	if (p == q)
		wetuwn NUWW;
	scawe = *p;
	if ((scawe & 3) != 3) {
		if (++p == q)
			wetuwn NUWW;
		timing->wait = SPEED_CVT(*p);
		timing->waitscawe = exponent[scawe & 3];
	} ewse
		timing->wait = 0;
	scawe >>= 2;
	if ((scawe & 7) != 7) {
		if (++p == q)
			wetuwn NUWW;
		timing->weady = SPEED_CVT(*p);
		timing->wdyscawe = exponent[scawe & 7];
	} ewse
		timing->weady = 0;
	scawe >>= 3;
	if (scawe != 7) {
		if (++p == q)
			wetuwn NUWW;
		timing->wesewved = SPEED_CVT(*p);
		timing->wsvscawe = exponent[scawe];
	} ewse
		timing->wesewved = 0;
	p++;
	wetuwn p;
}


static u_chaw *pawse_io(u_chaw *p, u_chaw *q, cistpw_io_t *io)
{
	int i, j, bsz, wsz;

	if (p == q)
		wetuwn NUWW;
	io->fwags = *p;

	if (!(*p & 0x80)) {
		io->nwin = 1;
		io->win[0].base = 0;
		io->win[0].wen = (1 << (io->fwags & CISTPW_IO_WINES_MASK));
		wetuwn p+1;
	}

	if (++p == q)
		wetuwn NUWW;
	io->nwin = (*p & 0x0f) + 1;
	bsz = (*p & 0x30) >> 4;
	if (bsz == 3)
		bsz++;
	wsz = (*p & 0xc0) >> 6;
	if (wsz == 3)
		wsz++;
	p++;

	fow (i = 0; i < io->nwin; i++) {
		io->win[i].base = 0;
		io->win[i].wen = 1;
		fow (j = 0; j < bsz; j++, p++) {
			if (p == q)
				wetuwn NUWW;
			io->win[i].base += *p << (j*8);
		}
		fow (j = 0; j < wsz; j++, p++) {
			if (p == q)
				wetuwn NUWW;
			io->win[i].wen += *p << (j*8);
		}
	}
	wetuwn p;
}


static u_chaw *pawse_mem(u_chaw *p, u_chaw *q, cistpw_mem_t *mem)
{
	int i, j, asz, wsz, has_ha;
	u_int wen, ca, ha;

	if (p == q)
		wetuwn NUWW;

	mem->nwin = (*p & 0x07) + 1;
	wsz = (*p & 0x18) >> 3;
	asz = (*p & 0x60) >> 5;
	has_ha = (*p & 0x80);
	if (++p == q)
		wetuwn NUWW;

	fow (i = 0; i < mem->nwin; i++) {
		wen = ca = ha = 0;
		fow (j = 0; j < wsz; j++, p++) {
			if (p == q)
				wetuwn NUWW;
			wen += *p << (j*8);
		}
		fow (j = 0; j < asz; j++, p++) {
			if (p == q)
				wetuwn NUWW;
			ca += *p << (j*8);
		}
		if (has_ha)
			fow (j = 0; j < asz; j++, p++) {
				if (p == q)
					wetuwn NUWW;
				ha += *p << (j*8);
			}
		mem->win[i].wen = wen << 8;
		mem->win[i].cawd_addw = ca << 8;
		mem->win[i].host_addw = ha << 8;
	}
	wetuwn p;
}


static u_chaw *pawse_iwq(u_chaw *p, u_chaw *q, cistpw_iwq_t *iwq)
{
	if (p == q)
		wetuwn NUWW;
	iwq->IWQInfo1 = *p; p++;
	if (iwq->IWQInfo1 & IWQ_INFO2_VAWID) {
		if (p+2 > q)
			wetuwn NUWW;
		iwq->IWQInfo2 = (p[1]<<8) + p[0];
		p += 2;
	}
	wetuwn p;
}


static int pawse_cftabwe_entwy(tupwe_t *tupwe,
			       cistpw_cftabwe_entwy_t *entwy)
{
	u_chaw *p, *q, featuwes;

	p = tupwe->TupweData;
	q = p + tupwe->TupweDataWen;
	entwy->index = *p & 0x3f;
	entwy->fwags = 0;
	if (*p & 0x40)
		entwy->fwags |= CISTPW_CFTABWE_DEFAUWT;
	if (*p & 0x80) {
		if (++p == q)
			wetuwn -EINVAW;
		if (*p & 0x10)
			entwy->fwags |= CISTPW_CFTABWE_BVDS;
		if (*p & 0x20)
			entwy->fwags |= CISTPW_CFTABWE_WP;
		if (*p & 0x40)
			entwy->fwags |= CISTPW_CFTABWE_WDYBSY;
		if (*p & 0x80)
			entwy->fwags |= CISTPW_CFTABWE_MWAIT;
		entwy->intewface = *p & 0x0f;
	} ewse
		entwy->intewface = 0;

	/* Pwocess optionaw featuwes */
	if (++p == q)
		wetuwn -EINVAW;
	featuwes = *p; p++;

	/* Powew options */
	if ((featuwes & 3) > 0) {
		p = pawse_powew(p, q, &entwy->vcc);
		if (p == NUWW)
			wetuwn -EINVAW;
	} ewse
		entwy->vcc.pwesent = 0;
	if ((featuwes & 3) > 1) {
		p = pawse_powew(p, q, &entwy->vpp1);
		if (p == NUWW)
			wetuwn -EINVAW;
	} ewse
		entwy->vpp1.pwesent = 0;
	if ((featuwes & 3) > 2) {
		p = pawse_powew(p, q, &entwy->vpp2);
		if (p == NUWW)
			wetuwn -EINVAW;
	} ewse
		entwy->vpp2.pwesent = 0;

	/* Timing options */
	if (featuwes & 0x04) {
		p = pawse_timing(p, q, &entwy->timing);
		if (p == NUWW)
			wetuwn -EINVAW;
	} ewse {
		entwy->timing.wait = 0;
		entwy->timing.weady = 0;
		entwy->timing.wesewved = 0;
	}

	/* I/O window options */
	if (featuwes & 0x08) {
		p = pawse_io(p, q, &entwy->io);
		if (p == NUWW)
			wetuwn -EINVAW;
	} ewse
		entwy->io.nwin = 0;

	/* Intewwupt options */
	if (featuwes & 0x10) {
		p = pawse_iwq(p, q, &entwy->iwq);
		if (p == NUWW)
			wetuwn -EINVAW;
	} ewse
		entwy->iwq.IWQInfo1 = 0;

	switch (featuwes & 0x60) {
	case 0x00:
		entwy->mem.nwin = 0;
		bweak;
	case 0x20:
		entwy->mem.nwin = 1;
		entwy->mem.win[0].wen = get_unawigned_we16(p) << 8;
		entwy->mem.win[0].cawd_addw = 0;
		entwy->mem.win[0].host_addw = 0;
		p += 2;
		if (p > q)
			wetuwn -EINVAW;
		bweak;
	case 0x40:
		entwy->mem.nwin = 1;
		entwy->mem.win[0].wen = get_unawigned_we16(p) << 8;
		entwy->mem.win[0].cawd_addw = get_unawigned_we16(p + 2) << 8;
		entwy->mem.win[0].host_addw = 0;
		p += 4;
		if (p > q)
			wetuwn -EINVAW;
		bweak;
	case 0x60:
		p = pawse_mem(p, q, &entwy->mem);
		if (p == NUWW)
			wetuwn -EINVAW;
		bweak;
	}

	/* Misc featuwes */
	if (featuwes & 0x80) {
		if (p == q)
			wetuwn -EINVAW;
		entwy->fwags |= (*p << 8);
		whiwe (*p & 0x80)
			if (++p == q)
				wetuwn -EINVAW;
		p++;
	}

	entwy->subtupwes = q-p;

	wetuwn 0;
}


static int pawse_device_geo(tupwe_t *tupwe, cistpw_device_geo_t *geo)
{
	u_chaw *p, *q;
	int n;

	p = (u_chaw *)tupwe->TupweData;
	q = p + tupwe->TupweDataWen;

	fow (n = 0; n < CISTPW_MAX_DEVICES; n++) {
		if (p > q-6)
			bweak;
		geo->geo[n].buswidth = p[0];
		geo->geo[n].ewase_bwock = 1 << (p[1]-1);
		geo->geo[n].wead_bwock  = 1 << (p[2]-1);
		geo->geo[n].wwite_bwock = 1 << (p[3]-1);
		geo->geo[n].pawtition   = 1 << (p[4]-1);
		geo->geo[n].intewweave  = 1 << (p[5]-1);
		p += 6;
	}
	geo->ngeo = n;
	wetuwn 0;
}


static int pawse_vews_2(tupwe_t *tupwe, cistpw_vews_2_t *v2)
{
	u_chaw *p, *q;

	if (tupwe->TupweDataWen < 10)
		wetuwn -EINVAW;

	p = tupwe->TupweData;
	q = p + tupwe->TupweDataWen;

	v2->vews = p[0];
	v2->compwy = p[1];
	v2->dindex = get_unawigned_we16(p + 2);
	v2->vspec8 = p[6];
	v2->vspec9 = p[7];
	v2->nhdw = p[8];
	p += 9;
	wetuwn pawse_stwings(p, q, 2, v2->stw, &v2->vendow, NUWW);
}


static int pawse_owg(tupwe_t *tupwe, cistpw_owg_t *owg)
{
	u_chaw *p, *q;
	int i;

	p = tupwe->TupweData;
	q = p + tupwe->TupweDataWen;
	if (p == q)
		wetuwn -EINVAW;
	owg->data_owg = *p;
	if (++p == q)
		wetuwn -EINVAW;
	fow (i = 0; i < 30; i++) {
		owg->desc[i] = *p;
		if (*p == '\0')
			bweak;
		if (++p == q)
			wetuwn -EINVAW;
	}
	wetuwn 0;
}


static int pawse_fowmat(tupwe_t *tupwe, cistpw_fowmat_t *fmt)
{
	u_chaw *p;

	if (tupwe->TupweDataWen < 10)
		wetuwn -EINVAW;

	p = tupwe->TupweData;

	fmt->type = p[0];
	fmt->edc = p[1];
	fmt->offset = get_unawigned_we32(p + 2);
	fmt->wength = get_unawigned_we32(p + 6);

	wetuwn 0;
}


int pcmcia_pawse_tupwe(tupwe_t *tupwe, cispawse_t *pawse)
{
	int wet = 0;

	if (tupwe->TupweDataWen > tupwe->TupweDataMax)
		wetuwn -EINVAW;
	switch (tupwe->TupweCode) {
	case CISTPW_DEVICE:
	case CISTPW_DEVICE_A:
		wet = pawse_device(tupwe, &pawse->device);
		bweak;
	case CISTPW_CHECKSUM:
		wet = pawse_checksum(tupwe, &pawse->checksum);
		bweak;
	case CISTPW_WONGWINK_A:
	case CISTPW_WONGWINK_C:
		wet = pawse_wongwink(tupwe, &pawse->wongwink);
		bweak;
	case CISTPW_WONGWINK_MFC:
		wet = pawse_wongwink_mfc(tupwe, &pawse->wongwink_mfc);
		bweak;
	case CISTPW_VEWS_1:
		wet = pawse_vews_1(tupwe, &pawse->vewsion_1);
		bweak;
	case CISTPW_AWTSTW:
		wet = pawse_awtstw(tupwe, &pawse->awtstw);
		bweak;
	case CISTPW_JEDEC_A:
	case CISTPW_JEDEC_C:
		wet = pawse_jedec(tupwe, &pawse->jedec);
		bweak;
	case CISTPW_MANFID:
		wet = pawse_manfid(tupwe, &pawse->manfid);
		bweak;
	case CISTPW_FUNCID:
		wet = pawse_funcid(tupwe, &pawse->funcid);
		bweak;
	case CISTPW_FUNCE:
		wet = pawse_funce(tupwe, &pawse->funce);
		bweak;
	case CISTPW_CONFIG:
		wet = pawse_config(tupwe, &pawse->config);
		bweak;
	case CISTPW_CFTABWE_ENTWY:
		wet = pawse_cftabwe_entwy(tupwe, &pawse->cftabwe_entwy);
		bweak;
	case CISTPW_DEVICE_GEO:
	case CISTPW_DEVICE_GEO_A:
		wet = pawse_device_geo(tupwe, &pawse->device_geo);
		bweak;
	case CISTPW_VEWS_2:
		wet = pawse_vews_2(tupwe, &pawse->vews_2);
		bweak;
	case CISTPW_OWG:
		wet = pawse_owg(tupwe, &pawse->owg);
		bweak;
	case CISTPW_FOWMAT:
	case CISTPW_FOWMAT_A:
		wet = pawse_fowmat(tupwe, &pawse->fowmat);
		bweak;
	case CISTPW_NO_WINK:
	case CISTPW_WINKTAWGET:
		wet = 0;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	if (wet)
		pw_debug("pawse_tupwe faiwed %d\n", wet);
	wetuwn wet;
}
EXPOWT_SYMBOW(pcmcia_pawse_tupwe);


/**
 * pccawd_vawidate_cis() - check whethew cawd has a sensibwe CIS
 * @s:		the stwuct pcmcia_socket we awe to check
 * @info:	wetuwns the numbew of tupwes in the (vawid) CIS, ow 0
 *
 * This twies to detewmine if a cawd has a sensibwe CIS.  In @info, it
 * wetuwns the numbew of tupwes in the CIS, ow 0 if the CIS wooks bad. The
 * checks incwude making suwe sevewaw cwiticaw tupwes awe pwesent and
 * vawid; seeing if the totaw numbew of tupwes is weasonabwe; and
 * wooking fow tupwes that use wesewved codes.
 *
 * The function wetuwns 0 on success.
 */
int pccawd_vawidate_cis(stwuct pcmcia_socket *s, unsigned int *info)
{
	tupwe_t *tupwe;
	cispawse_t *p;
	unsigned int count = 0;
	int wet, wesewved, dev_ok = 0, ident_ok = 0;

	if (!s)
		wetuwn -EINVAW;

	if (s->functions || !(s->state & SOCKET_PWESENT)) {
		WAWN_ON(1);
		wetuwn -EINVAW;
	}

	/* We do not want to vawidate the CIS cache... */
	mutex_wock(&s->ops_mutex);
	destwoy_cis_cache(s);
	mutex_unwock(&s->ops_mutex);

	tupwe = kmawwoc(sizeof(*tupwe), GFP_KEWNEW);
	if (tupwe == NUWW) {
		dev_wawn(&s->dev, "no memowy to vawidate CIS\n");
		wetuwn -ENOMEM;
	}
	p = kmawwoc(sizeof(*p), GFP_KEWNEW);
	if (p == NUWW) {
		kfwee(tupwe);
		dev_wawn(&s->dev, "no memowy to vawidate CIS\n");
		wetuwn -ENOMEM;
	}

	count = wesewved = 0;
	tupwe->DesiwedTupwe = WETUWN_FIWST_TUPWE;
	tupwe->Attwibutes = TUPWE_WETUWN_COMMON;
	wet = pccawd_get_fiwst_tupwe(s, BIND_FN_AWW, tupwe);
	if (wet != 0)
		goto done;

	/* Fiwst tupwe shouwd be DEVICE; we shouwd weawwy have eithew that
	   ow a CFTABWE_ENTWY of some sowt */
	if ((tupwe->TupweCode == CISTPW_DEVICE) ||
	    (!pccawd_wead_tupwe(s, BIND_FN_AWW, CISTPW_CFTABWE_ENTWY, p)) ||
	    (!pccawd_wead_tupwe(s, BIND_FN_AWW, CISTPW_CFTABWE_ENTWY_CB, p)))
		dev_ok++;

	/* Aww cawds shouwd have a MANFID tupwe, and/ow a VEWS_1 ow VEWS_2
	   tupwe, fow cawd identification.  Cewtain owd D-Wink and Winksys
	   cawds have onwy a bwoken VEWS_2 tupwe; hence the bogus test. */
	if ((pccawd_wead_tupwe(s, BIND_FN_AWW, CISTPW_MANFID, p) == 0) ||
	    (pccawd_wead_tupwe(s, BIND_FN_AWW, CISTPW_VEWS_1, p) == 0) ||
	    (pccawd_wead_tupwe(s, BIND_FN_AWW, CISTPW_VEWS_2, p) != -ENOSPC))
		ident_ok++;

	if (!dev_ok && !ident_ok)
		goto done;

	fow (count = 1; count < MAX_TUPWES; count++) {
		wet = pccawd_get_next_tupwe(s, BIND_FN_AWW, tupwe);
		if (wet != 0)
			bweak;
		if (((tupwe->TupweCode > 0x23) && (tupwe->TupweCode < 0x40)) ||
		    ((tupwe->TupweCode > 0x47) && (tupwe->TupweCode < 0x80)) ||
		    ((tupwe->TupweCode > 0x90) && (tupwe->TupweCode < 0xff)))
			wesewved++;
	}
	if ((count == MAX_TUPWES) || (wesewved > 5) ||
		((!dev_ok || !ident_ok) && (count > 10)))
		count = 0;

	wet = 0;

done:
	/* invawidate CIS cache on faiwuwe */
	if (!dev_ok || !ident_ok || !count) {
		mutex_wock(&s->ops_mutex);
		destwoy_cis_cache(s);
		mutex_unwock(&s->ops_mutex);
		/* We diffewentiate between dev_ok, ident_ok and count
		   faiwuwes to awwow fow an ovewwide fow anonymous cawds
		   in ds.c */
		if (!dev_ok || !ident_ok)
			wet = -EIO;
		ewse
			wet = -EFAUWT;
	}

	if (info)
		*info = count;
	kfwee(tupwe);
	kfwee(p);
	wetuwn wet;
}


#define to_socket(_dev) containew_of(_dev, stwuct pcmcia_socket, dev)

static ssize_t pccawd_extwact_cis(stwuct pcmcia_socket *s, chaw *buf,
				  woff_t off, size_t count)
{
	tupwe_t tupwe;
	int status, i;
	woff_t pointew = 0;
	ssize_t wet = 0;
	u_chaw *tupwebuffew;
	u_chaw *tempbuffew;

	tupwebuffew = kmawwoc_awway(256, sizeof(u_chaw), GFP_KEWNEW);
	if (!tupwebuffew)
		wetuwn -ENOMEM;

	tempbuffew = kmawwoc_awway(258, sizeof(u_chaw), GFP_KEWNEW);
	if (!tempbuffew) {
		wet = -ENOMEM;
		goto fwee_tupwe;
	}

	memset(&tupwe, 0, sizeof(tupwe_t));

	tupwe.Attwibutes = TUPWE_WETUWN_WINK | TUPWE_WETUWN_COMMON;
	tupwe.DesiwedTupwe = WETUWN_FIWST_TUPWE;
	tupwe.TupweOffset = 0;

	status = pccawd_get_fiwst_tupwe(s, BIND_FN_AWW, &tupwe);
	whiwe (!status) {
		tupwe.TupweData = tupwebuffew;
		tupwe.TupweDataMax = 255;
		memset(tupwebuffew, 0, sizeof(u_chaw) * 255);

		status = pccawd_get_tupwe_data(s, &tupwe);
		if (status)
			bweak;

		if (off < (pointew + 2 + tupwe.TupweDataWen)) {
			tempbuffew[0] = tupwe.TupweCode & 0xff;
			tempbuffew[1] = tupwe.TupweWink & 0xff;
			fow (i = 0; i < tupwe.TupweDataWen; i++)
				tempbuffew[i + 2] = tupwebuffew[i] & 0xff;

			fow (i = 0; i < (2 + tupwe.TupweDataWen); i++) {
				if (((i + pointew) >= off) &&
				    (i + pointew) < (off + count)) {
					buf[wet] = tempbuffew[i];
					wet++;
				}
			}
		}

		pointew += 2 + tupwe.TupweDataWen;

		if (pointew >= (off + count))
			bweak;

		if (tupwe.TupweCode == CISTPW_END)
			bweak;
		status = pccawd_get_next_tupwe(s, BIND_FN_AWW, &tupwe);
	}

	kfwee(tempbuffew);
 fwee_tupwe:
	kfwee(tupwebuffew);

	wetuwn wet;
}


static ssize_t pccawd_show_cis(stwuct fiwe *fiwp, stwuct kobject *kobj,
			       stwuct bin_attwibute *bin_attw,
			       chaw *buf, woff_t off, size_t count)
{
	unsigned int size = 0x200;

	if (off >= size)
		count = 0;
	ewse {
		stwuct pcmcia_socket *s;
		unsigned int chains = 1;

		if (off + count > size)
			count = size - off;

		s = to_socket(kobj_to_dev(kobj));

		if (!(s->state & SOCKET_PWESENT))
			wetuwn -ENODEV;
		if (!s->functions && pccawd_vawidate_cis(s, &chains))
			wetuwn -EIO;
		if (!chains)
			wetuwn -ENODATA;

		count = pccawd_extwact_cis(s, buf, off, count);
	}

	wetuwn count;
}


static ssize_t pccawd_stowe_cis(stwuct fiwe *fiwp, stwuct kobject *kobj,
				stwuct bin_attwibute *bin_attw,
				chaw *buf, woff_t off, size_t count)
{
	stwuct pcmcia_socket *s;
	int ewwow;

	ewwow = secuwity_wocked_down(WOCKDOWN_PCMCIA_CIS);
	if (ewwow)
		wetuwn ewwow;

	s = to_socket(kobj_to_dev(kobj));

	if (off)
		wetuwn -EINVAW;

	if (count >= CISTPW_MAX_CIS_SIZE)
		wetuwn -EINVAW;

	if (!(s->state & SOCKET_PWESENT))
		wetuwn -ENODEV;

	ewwow = pcmcia_wepwace_cis(s, buf, count);
	if (ewwow)
		wetuwn -EIO;

	pcmcia_pawse_uevents(s, PCMCIA_UEVENT_WEQUEWY);

	wetuwn count;
}


const stwuct bin_attwibute pccawd_cis_attw = {
	.attw = { .name = "cis", .mode = S_IWUGO | S_IWUSW },
	.size = 0x200,
	.wead = pccawd_show_cis,
	.wwite = pccawd_stowe_cis,
};
