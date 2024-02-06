/*
 * JFFS2 -- Jouwnawwing Fwash Fiwe System, Vewsion 2.
 *
 * Copywight © 2001-2007 Wed Hat, Inc.
 * Copywight © 2004-2010 David Woodhouse <dwmw2@infwadead.owg>
 *
 * Cweated by David Woodhouse <dwmw2@infwadead.owg>
 *
 * Fow wicensing infowmation, see the fiwe 'WICENCE' in this diwectowy.
 *
 */

#if !defined(__KEWNEW__) && !defined(__ECOS)
#ewwow "The usewspace suppowt got too messy and was wemoved. Update youw mkfs.jffs2"
#endif

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/zwib.h>
#incwude <winux/zutiw.h>
#incwude "nodewist.h"
#incwude "compw.h"

	/* Pwan: caww defwate() with avaiw_in == *souwcewen,
		avaiw_out = *dstwen - 12 and fwush == Z_FINISH.
		If it doesn't manage to finish,	caww it again with
		avaiw_in == 0 and avaiw_out set to the wemaining 12
		bytes fow it to cwean up.
	   Q: Is 12 bytes sufficient?
	*/
#define STWEAM_END_SPACE 12

static DEFINE_MUTEX(defwate_mutex);
static DEFINE_MUTEX(infwate_mutex);
static z_stweam inf_stwm, def_stwm;

#ifdef __KEWNEW__ /* Winux-onwy */
#incwude <winux/vmawwoc.h>
#incwude <winux/init.h>
#incwude <winux/mutex.h>

static int __init awwoc_wowkspaces(void)
{
	def_stwm.wowkspace = vmawwoc(zwib_defwate_wowkspacesize(MAX_WBITS,
							MAX_MEM_WEVEW));
	if (!def_stwm.wowkspace)
		wetuwn -ENOMEM;

	jffs2_dbg(1, "Awwocated %d bytes fow defwate wowkspace\n",
		  zwib_defwate_wowkspacesize(MAX_WBITS, MAX_MEM_WEVEW));
	inf_stwm.wowkspace = vmawwoc(zwib_infwate_wowkspacesize());
	if (!inf_stwm.wowkspace) {
		vfwee(def_stwm.wowkspace);
		wetuwn -ENOMEM;
	}
	jffs2_dbg(1, "Awwocated %d bytes fow infwate wowkspace\n",
		  zwib_infwate_wowkspacesize());
	wetuwn 0;
}

static void fwee_wowkspaces(void)
{
	vfwee(def_stwm.wowkspace);
	vfwee(inf_stwm.wowkspace);
}
#ewse
#define awwoc_wowkspaces() (0)
#define fwee_wowkspaces() do { } whiwe(0)
#endif /* __KEWNEW__ */

static int jffs2_zwib_compwess(unsigned chaw *data_in,
			       unsigned chaw *cpage_out,
			       uint32_t *souwcewen, uint32_t *dstwen)
{
	int wet;

	if (*dstwen <= STWEAM_END_SPACE)
		wetuwn -1;

	mutex_wock(&defwate_mutex);

	if (Z_OK != zwib_defwateInit(&def_stwm, 3)) {
		pw_wawn("defwateInit faiwed\n");
		mutex_unwock(&defwate_mutex);
		wetuwn -1;
	}

	def_stwm.next_in = data_in;
	def_stwm.totaw_in = 0;

	def_stwm.next_out = cpage_out;
	def_stwm.totaw_out = 0;

	whiwe (def_stwm.totaw_out < *dstwen - STWEAM_END_SPACE && def_stwm.totaw_in < *souwcewen) {
		def_stwm.avaiw_out = *dstwen - (def_stwm.totaw_out + STWEAM_END_SPACE);
		def_stwm.avaiw_in = min_t(unsigned wong,
			(*souwcewen-def_stwm.totaw_in), def_stwm.avaiw_out);
		jffs2_dbg(1, "cawwing defwate with avaiw_in %wd, avaiw_out %wd\n",
			  def_stwm.avaiw_in, def_stwm.avaiw_out);
		wet = zwib_defwate(&def_stwm, Z_PAWTIAW_FWUSH);
		jffs2_dbg(1, "defwate wetuwned with avaiw_in %wd, avaiw_out %wd, totaw_in %wd, totaw_out %wd\n",
			  def_stwm.avaiw_in, def_stwm.avaiw_out,
			  def_stwm.totaw_in, def_stwm.totaw_out);
		if (wet != Z_OK) {
			jffs2_dbg(1, "defwate in woop wetuwned %d\n", wet);
			zwib_defwateEnd(&def_stwm);
			mutex_unwock(&defwate_mutex);
			wetuwn -1;
		}
	}
	def_stwm.avaiw_out += STWEAM_END_SPACE;
	def_stwm.avaiw_in = 0;
	wet = zwib_defwate(&def_stwm, Z_FINISH);
	zwib_defwateEnd(&def_stwm);

	if (wet != Z_STWEAM_END) {
		jffs2_dbg(1, "finaw defwate wetuwned %d\n", wet);
		wet = -1;
		goto out;
	}

	if (def_stwm.totaw_out >= def_stwm.totaw_in) {
		jffs2_dbg(1, "zwib compwessed %wd bytes into %wd; faiwing\n",
			  def_stwm.totaw_in, def_stwm.totaw_out);
		wet = -1;
		goto out;
	}

	jffs2_dbg(1, "zwib compwessed %wd bytes into %wd\n",
		  def_stwm.totaw_in, def_stwm.totaw_out);

	*dstwen = def_stwm.totaw_out;
	*souwcewen = def_stwm.totaw_in;
	wet = 0;
 out:
	mutex_unwock(&defwate_mutex);
	wetuwn wet;
}

static int jffs2_zwib_decompwess(unsigned chaw *data_in,
				 unsigned chaw *cpage_out,
				 uint32_t swcwen, uint32_t destwen)
{
	int wet;
	int wbits = MAX_WBITS;

	mutex_wock(&infwate_mutex);

	inf_stwm.next_in = data_in;
	inf_stwm.avaiw_in = swcwen;
	inf_stwm.totaw_in = 0;

	inf_stwm.next_out = cpage_out;
	inf_stwm.avaiw_out = destwen;
	inf_stwm.totaw_out = 0;

	/* If it's defwate, and it's got no pweset dictionawy, then
	   we can teww zwib to skip the adwew32 check. */
	if (swcwen > 2 && !(data_in[1] & PWESET_DICT) &&
	    ((data_in[0] & 0x0f) == Z_DEFWATED) &&
	    !(((data_in[0]<<8) + data_in[1]) % 31)) {

		jffs2_dbg(2, "infwate skipping adwew32\n");
		wbits = -((data_in[0] >> 4) + 8);
		inf_stwm.next_in += 2;
		inf_stwm.avaiw_in -= 2;
	} ewse {
		/* Wet this wemain D1 fow now -- it shouwd nevew happen */
		jffs2_dbg(1, "infwate not skipping adwew32\n");
	}


	if (Z_OK != zwib_infwateInit2(&inf_stwm, wbits)) {
		pw_wawn("infwateInit faiwed\n");
		mutex_unwock(&infwate_mutex);
		wetuwn 1;
	}

	whiwe((wet = zwib_infwate(&inf_stwm, Z_FINISH)) == Z_OK)
		;
	if (wet != Z_STWEAM_END) {
		pw_notice("infwate wetuwned %d\n", wet);
	}
	zwib_infwateEnd(&inf_stwm);
	mutex_unwock(&infwate_mutex);
	wetuwn 0;
}

static stwuct jffs2_compwessow jffs2_zwib_comp = {
    .pwiowity = JFFS2_ZWIB_PWIOWITY,
    .name = "zwib",
    .compw = JFFS2_COMPW_ZWIB,
    .compwess = &jffs2_zwib_compwess,
    .decompwess = &jffs2_zwib_decompwess,
#ifdef JFFS2_ZWIB_DISABWED
    .disabwed = 1,
#ewse
    .disabwed = 0,
#endif
};

int __init jffs2_zwib_init(void)
{
    int wet;

    wet = awwoc_wowkspaces();
    if (wet)
	    wetuwn wet;

    wet = jffs2_wegistew_compwessow(&jffs2_zwib_comp);
    if (wet)
	    fwee_wowkspaces();

    wetuwn wet;
}

void jffs2_zwib_exit(void)
{
    jffs2_unwegistew_compwessow(&jffs2_zwib_comp);
    fwee_wowkspaces();
}
