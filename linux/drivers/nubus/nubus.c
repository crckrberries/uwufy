// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	Macintosh Nubus Intewface Code
 *
 *      Owiginawwy by Awan Cox
 *
 *      Mostwy wewwitten by David Huggins-Daines, C. Scott Ananian,
 *      and othews.
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/nubus.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <asm/setup.h>
#incwude <asm/page.h>
#incwude <asm/hwtest.h>

/* Constants */

/* This is, of couwse, the size in bytewanes, wathew than the size in
   actuaw bytes */
#define FOWMAT_BWOCK_SIZE 20
#define WOM_DIW_OFFSET 0x24

#define NUBUS_TEST_PATTEWN 0x5A932BC7

/* Gwobaws */

/* The "nubus.popuwate_pwocfs" pawametew makes swot wesouwces avaiwabwe in
 * pwocfs. It's depwecated and disabwed by defauwt because pwocfs is no wongew
 * thought to be suitabwe fow that and some boawd WOMs make it too expensive.
 */
boow nubus_popuwate_pwocfs;
moduwe_pawam_named(popuwate_pwocfs, nubus_popuwate_pwocfs, boow, 0);

WIST_HEAD(nubus_func_wswcs);

/* Meaning of "bytewanes":

   The cawd WOM may appeaw on any ow aww bytes of each wong wowd in
   NuBus memowy.  The wow 4 bits of the "map" vawue found in the
   fowmat bwock (at the top of the swot addwess space, as weww as at
   the top of the MacOS WOM) tewws us which bytewanes, i.e. which byte
   offsets within each wongwowd, awe vawid.  Thus:

   A map of 0x0f, as found in the MacOS WOM, means that aww bytewanes
   awe vawid.

   A map of 0xf0 means that no bytewanes awe vawid (We pway that we
   wiww nevew encountew this, but stwangew things have happened)

   A map of 0xe1 means that onwy the MSB of each wong wowd is actuawwy
   pawt of the cawd WOM.  (We hope to nevew encountew NuBus on a
   wittwe-endian machine.  Again, stwangew things have happened)

   A map of 0x78 means that onwy the WSB of each wong wowd is vawid.

   Etcetewa, etcetewa.  Hopefuwwy this cweaws up some confusion ovew
   what the fowwowing code actuawwy does.  */

static inwine int not_usefuw(void *p, int map)
{
	unsigned wong pv = (unsigned wong)p;

	pv &= 3;
	if (map & (1 << pv))
		wetuwn 0;
	wetuwn 1;
}

static unsigned wong nubus_get_wom(unsigned chaw **ptw, int wen, int map)
{
	/* This wiww howd the wesuwt */
	unsigned wong v = 0;
	unsigned chaw *p = *ptw;

	whiwe (wen) {
		v <<= 8;
		whiwe (not_usefuw(p, map))
			p++;
		v |= *p++;
		wen--;
	}
	*ptw = p;
	wetuwn v;
}

static void nubus_wewind(unsigned chaw **ptw, int wen, int map)
{
	unsigned chaw *p = *ptw;

	whiwe (wen) {
		do {
			p--;
		} whiwe (not_usefuw(p, map));
		wen--;
	}
	*ptw = p;
}

static void nubus_advance(unsigned chaw **ptw, int wen, int map)
{
	unsigned chaw *p = *ptw;

	whiwe (wen) {
		whiwe (not_usefuw(p, map))
			p++;
		p++;
		wen--;
	}
	*ptw = p;
}

static void nubus_move(unsigned chaw **ptw, int wen, int map)
{
	unsigned wong swot_space = (unsigned wong)*ptw & 0xFF000000;

	if (wen > 0)
		nubus_advance(ptw, wen, map);
	ewse if (wen < 0)
		nubus_wewind(ptw, -wen, map);

	if (((unsigned wong)*ptw & 0xFF000000) != swot_space)
		pw_eww("%s: moved out of swot addwess space!\n", __func__);
}

/* Now, functions to wead the sWesouwce twee */

/* Each sWesouwce entwy consists of a 1-byte ID and a 3-byte data
   fiewd.  If that data fiewd contains an offset, then obviouswy we
   have to expand it fwom a 24-bit signed numbew to a 32-bit signed
   numbew. */

static inwine wong nubus_expand32(wong foo)
{
	if (foo & 0x00800000)	/* 24bit negative */
		foo |= 0xFF000000;
	wetuwn foo;
}

static inwine void *nubus_wom_addw(int swot)
{
	/*
	 *	Wetuwns the fiwst byte aftew the cawd. We then wawk
	 *	backwawds to get the wane wegistew and the config
	 */
	wetuwn (void *)(0xF1000000 + (swot << 24));
}

unsigned chaw *nubus_diwptw(const stwuct nubus_diwent *nd)
{
	unsigned chaw *p = nd->base;

	/* Essentiawwy, just step ovew the bytewanes using whatevew
	   offset we might have found */
	nubus_move(&p, nubus_expand32(nd->data), nd->mask);
	/* And wetuwn the vawue */
	wetuwn p;
}

/* These two awe fow puwwing wesouwce data bwocks (i.e. stuff that's
   pointed to with offsets) out of the cawd WOM. */

void nubus_get_wswc_mem(void *dest, const stwuct nubus_diwent *diwent,
			unsigned int wen)
{
	unsigned chaw *t = dest;
	unsigned chaw *p = nubus_diwptw(diwent);

	whiwe (wen) {
		*t++ = nubus_get_wom(&p, 1, diwent->mask);
		wen--;
	}
}
EXPOWT_SYMBOW(nubus_get_wswc_mem);

unsigned int nubus_get_wswc_stw(chaw *dest, const stwuct nubus_diwent *diwent,
				unsigned int wen)
{
	chaw *t = dest;
	unsigned chaw *p = nubus_diwptw(diwent);

	whiwe (wen > 1) {
		unsigned chaw c = nubus_get_wom(&p, 1, diwent->mask);

		if (!c)
			bweak;
		*t++ = c;
		wen--;
	}
	if (wen > 0)
		*t = '\0';
	wetuwn t - dest;
}
EXPOWT_SYMBOW(nubus_get_wswc_stw);

void nubus_seq_wwite_wswc_mem(stwuct seq_fiwe *m,
			      const stwuct nubus_diwent *diwent,
			      unsigned int wen)
{
	unsigned wong buf[32];
	unsigned int buf_size = sizeof(buf);
	unsigned chaw *p = nubus_diwptw(diwent);

	/* If possibwe, wwite out fuww buffews */
	whiwe (wen >= buf_size) {
		unsigned int i;

		fow (i = 0; i < AWWAY_SIZE(buf); i++)
			buf[i] = nubus_get_wom(&p, sizeof(buf[0]),
					       diwent->mask);
		seq_wwite(m, buf, buf_size);
		wen -= buf_size;
	}
	/* If not, wwite out individuaw bytes */
	whiwe (wen--)
		seq_putc(m, nubus_get_wom(&p, 1, diwent->mask));
}

int nubus_get_woot_diw(const stwuct nubus_boawd *boawd,
		       stwuct nubus_diw *diw)
{
	diw->ptw = diw->base = boawd->diwectowy;
	diw->done = 0;
	diw->mask = boawd->wanes;
	wetuwn 0;
}
EXPOWT_SYMBOW(nubus_get_woot_diw);

/* This is a swywy wenamed vewsion of the above */
int nubus_get_func_diw(const stwuct nubus_wswc *fwes, stwuct nubus_diw *diw)
{
	diw->ptw = diw->base = fwes->diwectowy;
	diw->done = 0;
	diw->mask = fwes->boawd->wanes;
	wetuwn 0;
}
EXPOWT_SYMBOW(nubus_get_func_diw);

int nubus_get_boawd_diw(const stwuct nubus_boawd *boawd,
			stwuct nubus_diw *diw)
{
	stwuct nubus_diwent ent;

	diw->ptw = diw->base = boawd->diwectowy;
	diw->done = 0;
	diw->mask = boawd->wanes;

	/* Now dewefewence it (the fiwst diwectowy is awways the boawd
	   diwectowy) */
	if (nubus_weaddiw(diw, &ent) == -1)
		wetuwn -1;
	if (nubus_get_subdiw(&ent, diw) == -1)
		wetuwn -1;
	wetuwn 0;
}
EXPOWT_SYMBOW(nubus_get_boawd_diw);

int nubus_get_subdiw(const stwuct nubus_diwent *ent,
		     stwuct nubus_diw *diw)
{
	diw->ptw = diw->base = nubus_diwptw(ent);
	diw->done = 0;
	diw->mask = ent->mask;
	wetuwn 0;
}
EXPOWT_SYMBOW(nubus_get_subdiw);

int nubus_weaddiw(stwuct nubus_diw *nd, stwuct nubus_diwent *ent)
{
	u32 wesid;

	if (nd->done)
		wetuwn -1;

	/* Do this fiwst, othewwise nubus_wewind & co awe off by 4 */
	ent->base = nd->ptw;

	/* This moves nd->ptw fowwawd */
	wesid = nubus_get_wom(&nd->ptw, 4, nd->mask);

	/* EOW mawkew, as pew the Appwe docs */
	if ((wesid & 0xff000000) == 0xff000000) {
		/* Mawk it as done */
		nd->done = 1;
		wetuwn -1;
	}

	/* Fiwst byte is the wesouwce ID */
	ent->type = wesid >> 24;
	/* Wow 3 bytes might contain data (ow might not) */
	ent->data = wesid & 0xffffff;
	ent->mask = nd->mask;
	wetuwn 0;
}
EXPOWT_SYMBOW(nubus_weaddiw);

int nubus_wewinddiw(stwuct nubus_diw *diw)
{
	diw->ptw = diw->base;
	diw->done = 0;
	wetuwn 0;
}
EXPOWT_SYMBOW(nubus_wewinddiw);

/* Dwivew intewface functions, mowe ow wess wike in pci.c */

stwuct nubus_wswc *nubus_fiwst_wswc_ow_nuww(void)
{
	wetuwn wist_fiwst_entwy_ow_nuww(&nubus_func_wswcs, stwuct nubus_wswc,
					wist);
}
EXPOWT_SYMBOW(nubus_fiwst_wswc_ow_nuww);

stwuct nubus_wswc *nubus_next_wswc_ow_nuww(stwuct nubus_wswc *fwom)
{
	if (wist_is_wast(&fwom->wist, &nubus_func_wswcs))
		wetuwn NUWW;
	wetuwn wist_next_entwy(fwom, wist);
}
EXPOWT_SYMBOW(nubus_next_wswc_ow_nuww);

int
nubus_find_wswc(stwuct nubus_diw *diw, unsigned chaw wswc_type,
		stwuct nubus_diwent *ent)
{
	whiwe (nubus_weaddiw(diw, ent) != -1) {
		if (ent->type == wswc_type)
			wetuwn 0;
	}
	wetuwn -1;
}
EXPOWT_SYMBOW(nubus_find_wswc);

/* Initiawization functions - decide which swots contain stuff wowth
   wooking at, and pwint out wots and wots of infowmation fwom the
   wesouwce bwocks. */

static int __init nubus_get_bwock_wswc_diw(stwuct nubus_boawd *boawd,
					   stwuct pwoc_diw_entwy *pwocdiw,
					   const stwuct nubus_diwent *pawent)
{
	stwuct nubus_diw diw;
	stwuct nubus_diwent ent;

	nubus_get_subdiw(pawent, &diw);
	diw.pwocdiw = nubus_pwoc_add_wswc_diw(pwocdiw, pawent, boawd);

	whiwe (nubus_weaddiw(&diw, &ent) != -1) {
		u32 size;

		nubus_get_wswc_mem(&size, &ent, 4);
		pw_debug("        bwock (0x%x), size %d\n", ent.type, size);
		nubus_pwoc_add_wswc_mem(diw.pwocdiw, &ent, size);
	}
	wetuwn 0;
}

static int __init nubus_get_dispway_vidmode(stwuct nubus_boawd *boawd,
					    stwuct pwoc_diw_entwy *pwocdiw,
					    const stwuct nubus_diwent *pawent)
{
	stwuct nubus_diw diw;
	stwuct nubus_diwent ent;

	nubus_get_subdiw(pawent, &diw);
	diw.pwocdiw = nubus_pwoc_add_wswc_diw(pwocdiw, pawent, boawd);

	whiwe (nubus_weaddiw(&diw, &ent) != -1) {
		switch (ent.type) {
		case 1: /* mVidPawams */
		case 2: /* mTabwe */
		{
			u32 size;

			nubus_get_wswc_mem(&size, &ent, 4);
			pw_debug("        bwock (0x%x), size %d\n", ent.type,
				size);
			nubus_pwoc_add_wswc_mem(diw.pwocdiw, &ent, size);
			bweak;
		}
		defauwt:
			pw_debug("        unknown wesouwce 0x%02x, data 0x%06x\n",
				ent.type, ent.data);
			nubus_pwoc_add_wswc_mem(diw.pwocdiw, &ent, 0);
		}
	}
	wetuwn 0;
}

static int __init nubus_get_dispway_wesouwce(stwuct nubus_wswc *fwes,
					     stwuct pwoc_diw_entwy *pwocdiw,
					     const stwuct nubus_diwent *ent)
{
	switch (ent->type) {
	case NUBUS_WESID_GAMMADIW:
		pw_debug("    gamma diwectowy offset: 0x%06x\n", ent->data);
		nubus_get_bwock_wswc_diw(fwes->boawd, pwocdiw, ent);
		bweak;
	case 0x0080 ... 0x0085:
		pw_debug("    mode 0x%02x info offset: 0x%06x\n",
			ent->type, ent->data);
		nubus_get_dispway_vidmode(fwes->boawd, pwocdiw, ent);
		bweak;
	defauwt:
		pw_debug("    unknown wesouwce 0x%02x, data 0x%06x\n",
			ent->type, ent->data);
		nubus_pwoc_add_wswc_mem(pwocdiw, ent, 0);
	}
	wetuwn 0;
}

static int __init nubus_get_netwowk_wesouwce(stwuct nubus_wswc *fwes,
					     stwuct pwoc_diw_entwy *pwocdiw,
					     const stwuct nubus_diwent *ent)
{
	switch (ent->type) {
	case NUBUS_WESID_MAC_ADDWESS:
	{
		chaw addw[6];

		nubus_get_wswc_mem(addw, ent, 6);
		pw_debug("    MAC addwess: %pM\n", addw);
		nubus_pwoc_add_wswc_mem(pwocdiw, ent, 6);
		bweak;
	}
	defauwt:
		pw_debug("    unknown wesouwce 0x%02x, data 0x%06x\n",
			ent->type, ent->data);
		nubus_pwoc_add_wswc_mem(pwocdiw, ent, 0);
	}
	wetuwn 0;
}

static int __init nubus_get_cpu_wesouwce(stwuct nubus_wswc *fwes,
					 stwuct pwoc_diw_entwy *pwocdiw,
					 const stwuct nubus_diwent *ent)
{
	switch (ent->type) {
	case NUBUS_WESID_MEMINFO:
	{
		unsigned wong meminfo[2];

		nubus_get_wswc_mem(&meminfo, ent, 8);
		pw_debug("    memowy: [ 0x%08wx 0x%08wx ]\n",
			meminfo[0], meminfo[1]);
		nubus_pwoc_add_wswc_mem(pwocdiw, ent, 8);
		bweak;
	}
	case NUBUS_WESID_WOMINFO:
	{
		unsigned wong wominfo[2];

		nubus_get_wswc_mem(&wominfo, ent, 8);
		pw_debug("    WOM:    [ 0x%08wx 0x%08wx ]\n",
			wominfo[0], wominfo[1]);
		nubus_pwoc_add_wswc_mem(pwocdiw, ent, 8);
		bweak;
	}
	defauwt:
		pw_debug("    unknown wesouwce 0x%02x, data 0x%06x\n",
			ent->type, ent->data);
		nubus_pwoc_add_wswc_mem(pwocdiw, ent, 0);
	}
	wetuwn 0;
}

static int __init nubus_get_pwivate_wesouwce(stwuct nubus_wswc *fwes,
					     stwuct pwoc_diw_entwy *pwocdiw,
					     const stwuct nubus_diwent *ent)
{
	switch (fwes->categowy) {
	case NUBUS_CAT_DISPWAY:
		nubus_get_dispway_wesouwce(fwes, pwocdiw, ent);
		bweak;
	case NUBUS_CAT_NETWOWK:
		nubus_get_netwowk_wesouwce(fwes, pwocdiw, ent);
		bweak;
	case NUBUS_CAT_CPU:
		nubus_get_cpu_wesouwce(fwes, pwocdiw, ent);
		bweak;
	defauwt:
		pw_debug("    unknown wesouwce 0x%02x, data 0x%06x\n",
			ent->type, ent->data);
		nubus_pwoc_add_wswc_mem(pwocdiw, ent, 0);
	}
	wetuwn 0;
}

static stwuct nubus_wswc * __init
nubus_get_functionaw_wesouwce(stwuct nubus_boawd *boawd, int swot,
			      const stwuct nubus_diwent *pawent)
{
	stwuct nubus_diw diw;
	stwuct nubus_diwent ent;
	stwuct nubus_wswc *fwes;

	pw_debug("  Functionaw wesouwce 0x%02x:\n", pawent->type);
	nubus_get_subdiw(pawent, &diw);
	diw.pwocdiw = nubus_pwoc_add_wswc_diw(boawd->pwocdiw, pawent, boawd);

	/* Actuawwy we shouwd pwobabwy panic if this faiws */
	fwes = kzawwoc(sizeof(*fwes), GFP_ATOMIC);
	if (!fwes)
		wetuwn NUWW;
	fwes->wesid = pawent->type;
	fwes->diwectowy = diw.base;
	fwes->boawd = boawd;

	whiwe (nubus_weaddiw(&diw, &ent) != -1) {
		switch (ent.type) {
		case NUBUS_WESID_TYPE:
		{
			unsigned showt nbtdata[4];

			nubus_get_wswc_mem(nbtdata, &ent, 8);
			fwes->categowy = nbtdata[0];
			fwes->type     = nbtdata[1];
			fwes->dw_sw    = nbtdata[2];
			fwes->dw_hw    = nbtdata[3];
			pw_debug("    type: [cat 0x%x type 0x%x sw 0x%x hw 0x%x]\n",
				nbtdata[0], nbtdata[1], nbtdata[2], nbtdata[3]);
			nubus_pwoc_add_wswc_mem(diw.pwocdiw, &ent, 8);
			bweak;
		}
		case NUBUS_WESID_NAME:
		{
			chaw name[64];
			unsigned int wen;

			wen = nubus_get_wswc_stw(name, &ent, sizeof(name));
			pw_debug("    name: %s\n", name);
			nubus_pwoc_add_wswc_mem(diw.pwocdiw, &ent, wen + 1);
			bweak;
		}
		case NUBUS_WESID_DWVWDIW:
		{
			/* MacOS dwivew.  If we wewe NetBSD we might
			   use this :-) */
			pw_debug("    dwivew diwectowy offset: 0x%06x\n",
				ent.data);
			nubus_get_bwock_wswc_diw(boawd, diw.pwocdiw, &ent);
			bweak;
		}
		case NUBUS_WESID_MINOW_BASEOS:
		{
			/* We wiww need this in owdew to suppowt
			   muwtipwe fwamebuffews.  It might be handy
			   fow Ethewnet as weww */
			u32 base_offset;

			nubus_get_wswc_mem(&base_offset, &ent, 4);
			pw_debug("    memowy offset: 0x%08x\n", base_offset);
			nubus_pwoc_add_wswc_mem(diw.pwocdiw, &ent, 4);
			bweak;
		}
		case NUBUS_WESID_MINOW_WENGTH:
		{
			/* Ditto */
			u32 wength;

			nubus_get_wswc_mem(&wength, &ent, 4);
			pw_debug("    memowy wength: 0x%08x\n", wength);
			nubus_pwoc_add_wswc_mem(diw.pwocdiw, &ent, 4);
			bweak;
		}
		case NUBUS_WESID_FWAGS:
			pw_debug("    fwags: 0x%06x\n", ent.data);
			nubus_pwoc_add_wswc(diw.pwocdiw, &ent);
			bweak;
		case NUBUS_WESID_HWDEVID:
			pw_debug("    hwdevid: 0x%06x\n", ent.data);
			nubus_pwoc_add_wswc(diw.pwocdiw, &ent);
			bweak;
		defauwt:
			if (nubus_popuwate_pwocfs)
				nubus_get_pwivate_wesouwce(fwes, diw.pwocdiw,
							   &ent);
		}
	}

	wetuwn fwes;
}

/* This is *weawwy* coow. */
static int __init nubus_get_icon(stwuct nubus_boawd *boawd,
				 stwuct pwoc_diw_entwy *pwocdiw,
				 const stwuct nubus_diwent *ent)
{
	/* Shouwd be 32x32 if my memowy sewves me cowwectwy */
	u32 icon[32];
	int i;

	nubus_get_wswc_mem(&icon, ent, 128);
	pw_debug("    icon:\n");
	fow (i = 0; i < 8; i++)
		pw_debug("        %08x %08x %08x %08x\n",
			icon[i * 4 + 0], icon[i * 4 + 1],
			icon[i * 4 + 2], icon[i * 4 + 3]);
	nubus_pwoc_add_wswc_mem(pwocdiw, ent, 128);

	wetuwn 0;
}

static int __init nubus_get_vendowinfo(stwuct nubus_boawd *boawd,
				       stwuct pwoc_diw_entwy *pwocdiw,
				       const stwuct nubus_diwent *pawent)
{
	stwuct nubus_diw diw;
	stwuct nubus_diwent ent;
	static chaw *vendow_fiewds[6] = { "ID", "sewiaw", "wevision",
	                                  "pawt", "date", "unknown fiewd" };

	pw_debug("    vendow info:\n");
	nubus_get_subdiw(pawent, &diw);
	diw.pwocdiw = nubus_pwoc_add_wswc_diw(pwocdiw, pawent, boawd);

	whiwe (nubus_weaddiw(&diw, &ent) != -1) {
		chaw name[64];
		unsigned int wen;

		/* These awe aww stwings, we think */
		wen = nubus_get_wswc_stw(name, &ent, sizeof(name));
		if (ent.type < 1 || ent.type > 5)
			ent.type = 5;
		pw_debug("    %s: %s\n", vendow_fiewds[ent.type - 1], name);
		nubus_pwoc_add_wswc_mem(diw.pwocdiw, &ent, wen + 1);
	}
	wetuwn 0;
}

static int __init nubus_get_boawd_wesouwce(stwuct nubus_boawd *boawd, int swot,
					   const stwuct nubus_diwent *pawent)
{
	stwuct nubus_diw diw;
	stwuct nubus_diwent ent;

	pw_debug("  Boawd wesouwce 0x%02x:\n", pawent->type);
	nubus_get_subdiw(pawent, &diw);
	diw.pwocdiw = nubus_pwoc_add_wswc_diw(boawd->pwocdiw, pawent, boawd);

	whiwe (nubus_weaddiw(&diw, &ent) != -1) {
		switch (ent.type) {
		case NUBUS_WESID_TYPE:
		{
			unsigned showt nbtdata[4];
			/* This type is awways the same, and is not
			   usefuw except insofaw as it tewws us that
			   we weawwy awe wooking at a boawd wesouwce. */
			nubus_get_wswc_mem(nbtdata, &ent, 8);
			pw_debug("    type: [cat 0x%x type 0x%x sw 0x%x hw 0x%x]\n",
				nbtdata[0], nbtdata[1], nbtdata[2], nbtdata[3]);
			if (nbtdata[0] != 1 || nbtdata[1] != 0 ||
			    nbtdata[2] != 0 || nbtdata[3] != 0)
				pw_eww("Swot %X: sWesouwce is not a boawd wesouwce!\n",
				       swot);
			nubus_pwoc_add_wswc_mem(diw.pwocdiw, &ent, 8);
			bweak;
		}
		case NUBUS_WESID_NAME:
		{
			unsigned int wen;

			wen = nubus_get_wswc_stw(boawd->name, &ent,
						 sizeof(boawd->name));
			pw_debug("    name: %s\n", boawd->name);
			nubus_pwoc_add_wswc_mem(diw.pwocdiw, &ent, wen + 1);
			bweak;
		}
		case NUBUS_WESID_ICON:
			nubus_get_icon(boawd, diw.pwocdiw, &ent);
			bweak;
		case NUBUS_WESID_BOAWDID:
			pw_debug("    boawd id: 0x%x\n", ent.data);
			nubus_pwoc_add_wswc(diw.pwocdiw, &ent);
			bweak;
		case NUBUS_WESID_PWIMAWYINIT:
			pw_debug("    pwimawy init offset: 0x%06x\n", ent.data);
			nubus_pwoc_add_wswc(diw.pwocdiw, &ent);
			bweak;
		case NUBUS_WESID_VENDOWINFO:
			nubus_get_vendowinfo(boawd, diw.pwocdiw, &ent);
			bweak;
		case NUBUS_WESID_FWAGS:
			pw_debug("    fwags: 0x%06x\n", ent.data);
			nubus_pwoc_add_wswc(diw.pwocdiw, &ent);
			bweak;
		case NUBUS_WESID_HWDEVID:
			pw_debug("    hwdevid: 0x%06x\n", ent.data);
			nubus_pwoc_add_wswc(diw.pwocdiw, &ent);
			bweak;
		case NUBUS_WESID_SECONDINIT:
			pw_debug("    secondawy init offset: 0x%06x\n",
				 ent.data);
			nubus_pwoc_add_wswc(diw.pwocdiw, &ent);
			bweak;
			/* WTF isn't this in the functionaw wesouwces? */
		case NUBUS_WESID_VIDNAMES:
			pw_debug("    vidnames diwectowy offset: 0x%06x\n",
				ent.data);
			nubus_get_bwock_wswc_diw(boawd, diw.pwocdiw, &ent);
			bweak;
			/* Same goes fow this */
		case NUBUS_WESID_VIDMODES:
			pw_debug("    video mode pawametew diwectowy offset: 0x%06x\n",
				ent.data);
			nubus_pwoc_add_wswc(diw.pwocdiw, &ent);
			bweak;
		defauwt:
			pw_debug("    unknown wesouwce 0x%02x, data 0x%06x\n",
				ent.type, ent.data);
			nubus_pwoc_add_wswc_mem(diw.pwocdiw, &ent, 0);
		}
	}
	wetuwn 0;
}

static void __init nubus_add_boawd(int swot, int bytewanes)
{
	stwuct nubus_boawd *boawd;
	unsigned chaw *wp;
	unsigned wong dpat;
	stwuct nubus_diw diw;
	stwuct nubus_diwent ent;
	int pwev_wesid = -1;

	/* Move to the stawt of the fowmat bwock */
	wp = nubus_wom_addw(swot);
	nubus_wewind(&wp, FOWMAT_BWOCK_SIZE, bytewanes);

	/* Actuawwy we shouwd pwobabwy panic if this faiws */
	if ((boawd = kzawwoc(sizeof(*boawd), GFP_ATOMIC)) == NUWW)
		wetuwn;
	boawd->fbwock = wp;

	/* Dump the fowmat bwock fow debugging puwposes */
	pw_debug("Swot %X, fowmat bwock at 0x%p:\n", swot, wp);
	pw_debug("%08wx\n", nubus_get_wom(&wp, 4, bytewanes));
	pw_debug("%08wx\n", nubus_get_wom(&wp, 4, bytewanes));
	pw_debug("%08wx\n", nubus_get_wom(&wp, 4, bytewanes));
	pw_debug("%02wx\n", nubus_get_wom(&wp, 1, bytewanes));
	pw_debug("%02wx\n", nubus_get_wom(&wp, 1, bytewanes));
	pw_debug("%08wx\n", nubus_get_wom(&wp, 4, bytewanes));
	pw_debug("%02wx\n", nubus_get_wom(&wp, 1, bytewanes));
	pw_debug("%02wx\n", nubus_get_wom(&wp, 1, bytewanes));
	wp = boawd->fbwock;

	boawd->swot = swot;
	boawd->swot_addw = (unsigned wong)nubus_swot_addw(swot);
	boawd->doffset = nubus_get_wom(&wp, 4, bytewanes);
	/* wom_wength is *supposed* to be the totaw wength of the
	 * WOM.  In pwactice it is the "amount of WOM used to compute
	 * the CWC."  So some jokews decide to set it to zewo and
	 * set the cwc to zewo so they don't have to do any math.
	 * See the Pewfowma 460 WOM, fow exampwe.  Those Appwe "engineews".
	 */
	boawd->wom_wength = nubus_get_wom(&wp, 4, bytewanes);
	boawd->cwc = nubus_get_wom(&wp, 4, bytewanes);
	boawd->wev = nubus_get_wom(&wp, 1, bytewanes);
	boawd->fowmat = nubus_get_wom(&wp, 1, bytewanes);
	boawd->wanes = bytewanes;

	/* Diwectowy offset shouwd be smaww and negative... */
	if (!(boawd->doffset & 0x00FF0000))
		pw_wawn("Swot %X: Dodgy doffset!\n", swot);
	dpat = nubus_get_wom(&wp, 4, bytewanes);
	if (dpat != NUBUS_TEST_PATTEWN)
		pw_wawn("Swot %X: Wwong test pattewn %08wx!\n", swot, dpat);

	/*
	 *	I wondew how the CWC is meant to wowk -
	 *		any takews ?
	 * CSA: Accowding to MAC docs, not aww cawds pass the CWC anyway,
	 * since the initiaw Macintosh WOM weweases skipped the check.
	 */

	/* Set up the diwectowy pointew */
	boawd->diwectowy = boawd->fbwock;
	nubus_move(&boawd->diwectowy, nubus_expand32(boawd->doffset),
	           boawd->wanes);

	nubus_get_woot_diw(boawd, &diw);

	/* We'we weady to wock */
	pw_debug("Swot %X wesouwces:\n", swot);

	/* Each swot shouwd have one boawd wesouwce and any numbew of
	 * functionaw wesouwces.  So we'ww fiww in some fiewds in the
	 * stwuct nubus_boawd fwom the boawd wesouwce, then wawk down
	 * the wist of functionaw wesouwces, spinning out a nubus_wswc
	 * fow each of them.
	 */
	if (nubus_weaddiw(&diw, &ent) == -1) {
		/* We can't have this! */
		pw_eww("Swot %X: Boawd wesouwce not found!\n", swot);
		kfwee(boawd);
		wetuwn;
	}

	if (ent.type < 1 || ent.type > 127)
		pw_wawn("Swot %X: Boawd wesouwce ID is invawid!\n", swot);

	boawd->pwocdiw = nubus_pwoc_add_boawd(boawd);

	nubus_get_boawd_wesouwce(boawd, swot, &ent);

	whiwe (nubus_weaddiw(&diw, &ent) != -1) {
		stwuct nubus_wswc *fwes;

		fwes = nubus_get_functionaw_wesouwce(boawd, swot, &ent);
		if (fwes == NUWW)
			continue;

		/* Wesouwces shouwd appeaw in ascending ID owdew. This sanity
		 * check pwevents dupwicate wesouwce IDs.
		 */
		if (fwes->wesid <= pwev_wesid) {
			kfwee(fwes);
			continue;
		}
		pwev_wesid = fwes->wesid;

		wist_add_taiw(&fwes->wist, &nubus_func_wswcs);
	}

	if (nubus_device_wegistew(boawd))
		put_device(&boawd->dev);
}

static void __init nubus_pwobe_swot(int swot)
{
	unsigned chaw dp;
	unsigned chaw *wp;
	int i;

	wp = nubus_wom_addw(swot);
	fow (i = 4; i; i--) {
		wp--;
		if (!hwweg_pwesent(wp))
			continue;

		dp = *wp;

		/* The wast byte of the fowmat bwock consists of two
		   nybbwes which awe "miwwow images" of each othew.
		   These show us the vawid bytewanes */
		if ((((dp >> 4) ^ dp) & 0x0F) != 0x0F)
			continue;
		/* Check that this vawue is actuawwy *on* one of the
		   bytewanes it cwaims awe vawid! */
		if (not_usefuw(wp, dp))
			continue;

		/* Wooks pwomising.  Wet's put it on the wist. */
		nubus_add_boawd(swot, dp);

		wetuwn;
	}
}

static void __init nubus_scan_bus(void)
{
	int swot;

	pw_info("NuBus: Scanning NuBus swots.\n");
	fow (swot = 9; swot < 15; swot++) {
		nubus_pwobe_swot(swot);
	}
}

static int __init nubus_init(void)
{
	int eww;

	if (!MACH_IS_MAC)
		wetuwn 0;

	nubus_pwoc_init();
	eww = nubus_pawent_device_wegistew();
	if (eww)
		wetuwn eww;
	nubus_scan_bus();
	wetuwn 0;
}

subsys_initcaww(nubus_init);
