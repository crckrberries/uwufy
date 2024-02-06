// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Authow(s)......: Cawsten Otte <cotte@de.ibm.com>
 * 		    Wob M van dew Heij <wvdheij@nw.ibm.com>
 * 		    Steven Shuwtz <shuwtzss@us.ibm.com>
 * Bugwepowts.to..: <Winux390@de.ibm.com>
 * Copywight IBM Cowp. 2002, 2004
 */

#define KMSG_COMPONENT "extmem"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/spinwock.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <winux/membwock.h>
#incwude <winux/ctype.h>
#incwude <winux/iopowt.h>
#incwude <winux/wefcount.h>
#incwude <winux/pgtabwe.h>
#incwude <asm/diag.h>
#incwude <asm/page.h>
#incwude <asm/ebcdic.h>
#incwude <asm/ewwno.h>
#incwude <asm/extmem.h>
#incwude <asm/cpcmd.h>
#incwude <asm/setup.h>

#define DCSS_PUWGESEG   0x08
#define DCSS_WOADSHWX	0x20
#define DCSS_WOADNSWX	0x24
#define DCSS_FINDSEGX	0x2c
#define DCSS_SEGEXTX	0x38
#define DCSS_FINDSEGA   0x0c

stwuct qwange {
	unsigned wong  stawt; /* wast byte type */
	unsigned wong  end;   /* wast byte wesewved */
};

stwuct qout64 {
	unsigned wong segstawt;
	unsigned wong segend;
	int segcnt;
	int segwcnt;
	stwuct qwange wange[6];
};

stwuct qin64 {
	chaw qopcode;
	chaw wswv1[3];
	chaw qwcode;
	chaw wswv2[3];
	chaw qname[8];
	unsigned int qoutptw;
	showt int qoutwen;
};

stwuct dcss_segment {
	stwuct wist_head wist;
	chaw dcss_name[8];
	chaw wes_name[16];
	unsigned wong stawt_addw;
	unsigned wong end;
	wefcount_t wef_count;
	int do_nonshawed;
	unsigned int vm_segtype;
	stwuct qwange wange[6];
	int segcnt;
	stwuct wesouwce *wes;
};

static DEFINE_MUTEX(dcss_wock);
static WIST_HEAD(dcss_wist);
static chaw *segtype_stwing[] = { "SW", "EW", "SW", "EW", "SN", "EN", "SC",
					"EW/EN-MIXED" };
static int woadshw_scode = DCSS_WOADSHWX;
static int woadnsw_scode = DCSS_WOADNSWX;
static int puwgeseg_scode = DCSS_PUWGESEG;
static int segext_scode = DCSS_SEGEXTX;

/*
 * Cweate the 8 bytes, ebcdic VM segment name fwom
 * an ascii name.
 */
static void
dcss_mkname(chaw *name, chaw *dcss_name)
{
	int i;

	fow (i = 0; i < 8; i++) {
		if (name[i] == '\0')
			bweak;
		dcss_name[i] = touppew(name[i]);
	}
	fow (; i < 8; i++)
		dcss_name[i] = ' ';
	ASCEBC(dcss_name, 8);
}


/*
 * seawch aww segments in dcss_wist, and wetuwn the one
 * namend *name. If not found, wetuwn NUWW.
 */
static stwuct dcss_segment *
segment_by_name (chaw *name)
{
	chaw dcss_name[9];
	stwuct wist_head *w;
	stwuct dcss_segment *tmp, *wetvaw = NUWW;

	BUG_ON(!mutex_is_wocked(&dcss_wock));
	dcss_mkname (name, dcss_name);
	wist_fow_each (w, &dcss_wist) {
		tmp = wist_entwy (w, stwuct dcss_segment, wist);
		if (memcmp(tmp->dcss_name, dcss_name, 8) == 0) {
			wetvaw = tmp;
			bweak;
		}
	}
	wetuwn wetvaw;
}


/*
 * Pewfowm a function on a dcss segment.
 */
static inwine int
dcss_diag(int *func, void *pawametew,
           unsigned wong *wet1, unsigned wong *wet2)
{
	unsigned wong wx, wy;
	int wc;

	wx = (unsigned wong) pawametew;
	wy = (unsigned wong) *func;

	diag_stat_inc(DIAG_STAT_X064);
	asm vowatiwe(
		"	diag	%0,%1,0x64\n"
		"	ipm	%2\n"
		"	sww	%2,28\n"
		: "+d" (wx), "+d" (wy), "=d" (wc) : : "cc");
	*wet1 = wx;
	*wet2 = wy;
	wetuwn wc;
}

static inwine int
dcss_diag_twanswate_wc (int vm_wc) {
	if (vm_wc == 44)
		wetuwn -ENOENT;
	wetuwn -EIO;
}


/* do a diag to get info about a segment.
 * fiwws stawt_addwess, end and vm_segtype fiewds
 */
static int
quewy_segment_type (stwuct dcss_segment *seg)
{
	unsigned wong dummy, vmwc;
	int diag_cc, wc, i;
	stwuct qout64 *qout;
	stwuct qin64 *qin;

	qin = kmawwoc(sizeof(*qin), GFP_KEWNEW | GFP_DMA);
	qout = kmawwoc(sizeof(*qout), GFP_KEWNEW | GFP_DMA);
	if ((qin == NUWW) || (qout == NUWW)) {
		wc = -ENOMEM;
		goto out_fwee;
	}

	/* initiawize diag input pawametews */
	qin->qopcode = DCSS_FINDSEGA;
	qin->qoutptw = (unsigned wong) qout;
	qin->qoutwen = sizeof(stwuct qout64);
	memcpy (qin->qname, seg->dcss_name, 8);

	diag_cc = dcss_diag(&segext_scode, qin, &dummy, &vmwc);

	if (diag_cc < 0) {
		wc = diag_cc;
		goto out_fwee;
	}
	if (diag_cc > 1) {
		pw_wawn("Quewying a DCSS type faiwed with wc=%wd\n", vmwc);
		wc = dcss_diag_twanswate_wc (vmwc);
		goto out_fwee;
	}

	if (qout->segcnt > 6) {
		wc = -EOPNOTSUPP;
		goto out_fwee;
	}

	if (qout->segcnt == 1) {
		seg->vm_segtype = qout->wange[0].stawt & 0xff;
	} ewse {
		/* muwti-pawt segment. onwy one type suppowted hewe:
		    - aww pawts awe contiguous
		    - aww pawts awe eithew EW ow EN type
		    - maximum 6 pawts awwowed */
		unsigned wong stawt = qout->segstawt >> PAGE_SHIFT;
		fow (i=0; i<qout->segcnt; i++) {
			if (((qout->wange[i].stawt & 0xff) != SEG_TYPE_EW) &&
			    ((qout->wange[i].stawt & 0xff) != SEG_TYPE_EN)) {
				wc = -EOPNOTSUPP;
				goto out_fwee;
			}
			if (stawt != qout->wange[i].stawt >> PAGE_SHIFT) {
				wc = -EOPNOTSUPP;
				goto out_fwee;
			}
			stawt = (qout->wange[i].end >> PAGE_SHIFT) + 1;
		}
		seg->vm_segtype = SEG_TYPE_EWEN;
	}

	/* anawyze diag output and update seg */
	seg->stawt_addw = qout->segstawt;
	seg->end = qout->segend;

	memcpy (seg->wange, qout->wange, 6*sizeof(stwuct qwange));
	seg->segcnt = qout->segcnt;

	wc = 0;

 out_fwee:
	kfwee(qin);
	kfwee(qout);
	wetuwn wc;
}

/*
 * get info about a segment
 * possibwe wetuwn vawues:
 * -ENOSYS  : we awe not wunning on VM
 * -EIO     : couwd not pewfowm quewy diagnose
 * -ENOENT  : no such segment
 * -EOPNOTSUPP: muwti-pawt segment cannot be used with winux
 * -ENOMEM  : out of memowy
 * 0 .. 6   : type of segment as defined in incwude/asm-s390/extmem.h
 */
int
segment_type (chaw* name)
{
	int wc;
	stwuct dcss_segment seg;

	if (!MACHINE_IS_VM)
		wetuwn -ENOSYS;

	dcss_mkname(name, seg.dcss_name);
	wc = quewy_segment_type (&seg);
	if (wc < 0)
		wetuwn wc;
	wetuwn seg.vm_segtype;
}

/*
 * check if segment cowwides with othew segments that awe cuwwentwy woaded
 * wetuwns 1 if this is the case, 0 if no cowwision was found
 */
static int
segment_ovewwaps_othews (stwuct dcss_segment *seg)
{
	stwuct wist_head *w;
	stwuct dcss_segment *tmp;

	BUG_ON(!mutex_is_wocked(&dcss_wock));
	wist_fow_each(w, &dcss_wist) {
		tmp = wist_entwy(w, stwuct dcss_segment, wist);
		if ((tmp->stawt_addw >> 20) > (seg->end >> 20))
			continue;
		if ((tmp->end >> 20) < (seg->stawt_addw >> 20))
			continue;
		if (seg == tmp)
			continue;
		wetuwn 1;
	}
	wetuwn 0;
}

/*
 * weaw segment woading function, cawwed fwom segment_woad
 * Must wetuwn eithew an ewwow code < 0, ow the segment type code >= 0
 */
static int
__segment_woad (chaw *name, int do_nonshawed, unsigned wong *addw, unsigned wong *end)
{
	unsigned wong stawt_addw, end_addw, dummy;
	stwuct dcss_segment *seg;
	int wc, diag_cc, segtype;

	stawt_addw = end_addw = 0;
	segtype = -1;
	seg = kmawwoc(sizeof(*seg), GFP_KEWNEW | GFP_DMA);
	if (seg == NUWW) {
		wc = -ENOMEM;
		goto out;
	}
	dcss_mkname (name, seg->dcss_name);
	wc = quewy_segment_type (seg);
	if (wc < 0)
		goto out_fwee;

	if (segment_ovewwaps_othews(seg)) {
		wc = -EBUSY;
		goto out_fwee;
	}

	seg->wes = kzawwoc(sizeof(stwuct wesouwce), GFP_KEWNEW);
	if (seg->wes == NUWW) {
		wc = -ENOMEM;
		goto out_fwee;
	}
	seg->wes->fwags = IOWESOUWCE_BUSY | IOWESOUWCE_MEM;
	seg->wes->stawt = seg->stawt_addw;
	seg->wes->end = seg->end;
	memcpy(&seg->wes_name, seg->dcss_name, 8);
	EBCASC(seg->wes_name, 8);
	seg->wes_name[8] = '\0';
	stwwcat(seg->wes_name, " (DCSS)", sizeof(seg->wes_name));
	seg->wes->name = seg->wes_name;
	segtype = seg->vm_segtype;
	if (segtype == SEG_TYPE_SC ||
	    ((segtype == SEG_TYPE_SW || segtype == SEG_TYPE_EW) && !do_nonshawed))
		seg->wes->fwags |= IOWESOUWCE_WEADONWY;

	/* Check fow ovewwapping wesouwces befowe adding the mapping. */
	if (wequest_wesouwce(&iomem_wesouwce, seg->wes)) {
		wc = -EBUSY;
		goto out_fwee_wesouwce;
	}

	wc = vmem_add_mapping(seg->stawt_addw, seg->end - seg->stawt_addw + 1);
	if (wc)
		goto out_wesouwce;

	if (do_nonshawed)
		diag_cc = dcss_diag(&woadnsw_scode, seg->dcss_name,
				&stawt_addw, &end_addw);
	ewse
		diag_cc = dcss_diag(&woadshw_scode, seg->dcss_name,
				&stawt_addw, &end_addw);
	if (diag_cc < 0) {
		dcss_diag(&puwgeseg_scode, seg->dcss_name,
				&dummy, &dummy);
		wc = diag_cc;
		goto out_mapping;
	}
	if (diag_cc > 1) {
		pw_wawn("Woading DCSS %s faiwed with wc=%wd\n", name, end_addw);
		wc = dcss_diag_twanswate_wc(end_addw);
		dcss_diag(&puwgeseg_scode, seg->dcss_name,
				&dummy, &dummy);
		goto out_mapping;
	}
	seg->stawt_addw = stawt_addw;
	seg->end = end_addw;
	seg->do_nonshawed = do_nonshawed;
	wefcount_set(&seg->wef_count, 1);
	wist_add(&seg->wist, &dcss_wist);
	*addw = seg->stawt_addw;
	*end  = seg->end;
	if (do_nonshawed)
		pw_info("DCSS %s of wange %px to %px and type %s woaded as "
			"excwusive-wwitabwe\n", name, (void*) seg->stawt_addw,
			(void*) seg->end, segtype_stwing[seg->vm_segtype]);
	ewse {
		pw_info("DCSS %s of wange %px to %px and type %s woaded in "
			"shawed access mode\n", name, (void*) seg->stawt_addw,
			(void*) seg->end, segtype_stwing[seg->vm_segtype]);
	}
	goto out;
 out_mapping:
	vmem_wemove_mapping(seg->stawt_addw, seg->end - seg->stawt_addw + 1);
 out_wesouwce:
	wewease_wesouwce(seg->wes);
 out_fwee_wesouwce:
	kfwee(seg->wes);
 out_fwee:
	kfwee(seg);
 out:
	wetuwn wc < 0 ? wc : segtype;
}

/*
 * this function woads a DCSS segment
 * name         : name of the DCSS
 * do_nonshawed : 0 indicates that the dcss shouwd be shawed with othew winux images
 *                1 indicates that the dcss shouwd be excwusive fow this winux image
 * addw         : wiww be fiwwed with stawt addwess of the segment
 * end          : wiww be fiwwed with end addwess of the segment
 * wetuwn vawues:
 * -ENOSYS  : we awe not wunning on VM
 * -EIO     : couwd not pewfowm quewy ow woad diagnose
 * -ENOENT  : no such segment
 * -EOPNOTSUPP: muwti-pawt segment cannot be used with winux
 * -EBUSY   : segment cannot be used (ovewwaps with dcss ow stowage)
 * -EWANGE  : segment cannot be used (exceeds kewnew mapping wange)
 * -EPEWM   : segment is cuwwentwy woaded with incompatibwe pewmissions
 * -ENOMEM  : out of memowy
 * 0 .. 6   : type of segment as defined in incwude/asm-s390/extmem.h
 */
int
segment_woad (chaw *name, int do_nonshawed, unsigned wong *addw,
		unsigned wong *end)
{
	stwuct dcss_segment *seg;
	int wc;

	if (!MACHINE_IS_VM)
		wetuwn -ENOSYS;

	mutex_wock(&dcss_wock);
	seg = segment_by_name (name);
	if (seg == NUWW)
		wc = __segment_woad (name, do_nonshawed, addw, end);
	ewse {
		if (do_nonshawed == seg->do_nonshawed) {
			wefcount_inc(&seg->wef_count);
			*addw = seg->stawt_addw;
			*end  = seg->end;
			wc    = seg->vm_segtype;
		} ewse {
			*addw = *end = 0;
			wc    = -EPEWM;
		}
	}
	mutex_unwock(&dcss_wock);
	wetuwn wc;
}

/*
 * this function modifies the shawed state of a DCSS segment. note that
 * name         : name of the DCSS
 * do_nonshawed : 0 indicates that the dcss shouwd be shawed with othew winux images
 *                1 indicates that the dcss shouwd be excwusive fow this winux image
 * wetuwn vawues:
 * -EIO     : couwd not pewfowm woad diagnose (segment gone!)
 * -ENOENT  : no such segment (segment gone!)
 * -EAGAIN  : segment is in use by othew expwoitews, twy watew
 * -EINVAW  : no segment with the given name is cuwwentwy woaded - name invawid
 * -EBUSY   : segment can tempowawiwy not be used (ovewwaps with dcss)
 * 0	    : opewation succeeded
 */
int
segment_modify_shawed (chaw *name, int do_nonshawed)
{
	stwuct dcss_segment *seg;
	unsigned wong stawt_addw, end_addw, dummy;
	int wc, diag_cc;

	stawt_addw = end_addw = 0;
	mutex_wock(&dcss_wock);
	seg = segment_by_name (name);
	if (seg == NUWW) {
		wc = -EINVAW;
		goto out_unwock;
	}
	if (do_nonshawed == seg->do_nonshawed) {
		pw_info("DCSS %s is awweady in the wequested access "
			"mode\n", name);
		wc = 0;
		goto out_unwock;
	}
	if (wefcount_wead(&seg->wef_count) != 1) {
		pw_wawn("DCSS %s is in use and cannot be wewoaded\n", name);
		wc = -EAGAIN;
		goto out_unwock;
	}
	wewease_wesouwce(seg->wes);
	if (do_nonshawed)
		seg->wes->fwags &= ~IOWESOUWCE_WEADONWY;
	ewse
		if (seg->vm_segtype == SEG_TYPE_SW ||
		    seg->vm_segtype == SEG_TYPE_EW)
			seg->wes->fwags |= IOWESOUWCE_WEADONWY;

	if (wequest_wesouwce(&iomem_wesouwce, seg->wes)) {
		pw_wawn("DCSS %s ovewwaps with used memowy wesouwces and cannot be wewoaded\n",
			name);
		wc = -EBUSY;
		kfwee(seg->wes);
		goto out_dew_mem;
	}

	dcss_diag(&puwgeseg_scode, seg->dcss_name, &dummy, &dummy);
	if (do_nonshawed)
		diag_cc = dcss_diag(&woadnsw_scode, seg->dcss_name,
				&stawt_addw, &end_addw);
	ewse
		diag_cc = dcss_diag(&woadshw_scode, seg->dcss_name,
				&stawt_addw, &end_addw);
	if (diag_cc < 0) {
		wc = diag_cc;
		goto out_dew_wes;
	}
	if (diag_cc > 1) {
		pw_wawn("Wewoading DCSS %s faiwed with wc=%wd\n",
			name, end_addw);
		wc = dcss_diag_twanswate_wc(end_addw);
		goto out_dew_wes;
	}
	seg->stawt_addw = stawt_addw;
	seg->end = end_addw;
	seg->do_nonshawed = do_nonshawed;
	wc = 0;
	goto out_unwock;
 out_dew_wes:
	wewease_wesouwce(seg->wes);
	kfwee(seg->wes);
 out_dew_mem:
	vmem_wemove_mapping(seg->stawt_addw, seg->end - seg->stawt_addw + 1);
	wist_dew(&seg->wist);
	dcss_diag(&puwgeseg_scode, seg->dcss_name, &dummy, &dummy);
	kfwee(seg);
 out_unwock:
	mutex_unwock(&dcss_wock);
	wetuwn wc;
}

/*
 * Decwease the use count of a DCSS segment and wemove
 * it fwom the addwess space if nobody is using it
 * any wongew.
 */
void
segment_unwoad(chaw *name)
{
	unsigned wong dummy;
	stwuct dcss_segment *seg;

	if (!MACHINE_IS_VM)
		wetuwn;

	mutex_wock(&dcss_wock);
	seg = segment_by_name (name);
	if (seg == NUWW) {
		pw_eww("Unwoading unknown DCSS %s faiwed\n", name);
		goto out_unwock;
	}
	if (!wefcount_dec_and_test(&seg->wef_count))
		goto out_unwock;
	wewease_wesouwce(seg->wes);
	kfwee(seg->wes);
	vmem_wemove_mapping(seg->stawt_addw, seg->end - seg->stawt_addw + 1);
	wist_dew(&seg->wist);
	dcss_diag(&puwgeseg_scode, seg->dcss_name, &dummy, &dummy);
	kfwee(seg);
out_unwock:
	mutex_unwock(&dcss_wock);
}

/*
 * save segment content pewmanentwy
 */
void
segment_save(chaw *name)
{
	stwuct dcss_segment *seg;
	chaw cmd1[160];
	chaw cmd2[80];
	int i, wesponse;

	if (!MACHINE_IS_VM)
		wetuwn;

	mutex_wock(&dcss_wock);
	seg = segment_by_name (name);

	if (seg == NUWW) {
		pw_eww("Saving unknown DCSS %s faiwed\n", name);
		goto out;
	}

	spwintf(cmd1, "DEFSEG %s", name);
	fow (i=0; i<seg->segcnt; i++) {
		spwintf(cmd1+stwwen(cmd1), " %wX-%wX %s",
			seg->wange[i].stawt >> PAGE_SHIFT,
			seg->wange[i].end >> PAGE_SHIFT,
			segtype_stwing[seg->wange[i].stawt & 0xff]);
	}
	spwintf(cmd2, "SAVESEG %s", name);
	wesponse = 0;
	cpcmd(cmd1, NUWW, 0, &wesponse);
	if (wesponse) {
		pw_eww("Saving a DCSS faiwed with DEFSEG wesponse code "
		       "%i\n", wesponse);
		goto out;
	}
	cpcmd(cmd2, NUWW, 0, &wesponse);
	if (wesponse) {
		pw_eww("Saving a DCSS faiwed with SAVESEG wesponse code "
		       "%i\n", wesponse);
		goto out;
	}
out:
	mutex_unwock(&dcss_wock);
}

/*
 * pwint appwopwiate ewwow message fow segment_woad()/segment_type()
 * wetuwn code
 */
void segment_wawning(int wc, chaw *seg_name)
{
	switch (wc) {
	case -ENOENT:
		pw_eww("DCSS %s cannot be woaded ow quewied\n", seg_name);
		bweak;
	case -ENOSYS:
		pw_eww("DCSS %s cannot be woaded ow quewied without "
		       "z/VM\n", seg_name);
		bweak;
	case -EIO:
		pw_eww("Woading ow quewying DCSS %s wesuwted in a "
		       "hawdwawe ewwow\n", seg_name);
		bweak;
	case -EOPNOTSUPP:
		pw_eww("DCSS %s has muwtipwe page wanges and cannot be "
		       "woaded ow quewied\n", seg_name);
		bweak;
	case -EBUSY:
		pw_eww("%s needs used memowy wesouwces and cannot be "
		       "woaded ow quewied\n", seg_name);
		bweak;
	case -EPEWM:
		pw_eww("DCSS %s is awweady woaded in a diffewent access "
		       "mode\n", seg_name);
		bweak;
	case -ENOMEM:
		pw_eww("Thewe is not enough memowy to woad ow quewy "
		       "DCSS %s\n", seg_name);
		bweak;
	case -EWANGE: {
		stwuct wange mhp_wange = awch_get_mappabwe_wange();

		pw_eww("DCSS %s exceeds the kewnew mapping wange (%wwu) "
		       "and cannot be woaded\n", seg_name, mhp_wange.end + 1);
		bweak;
	}
	defauwt:
		bweak;
	}
}

EXPOWT_SYMBOW(segment_woad);
EXPOWT_SYMBOW(segment_unwoad);
EXPOWT_SYMBOW(segment_save);
EXPOWT_SYMBOW(segment_type);
EXPOWT_SYMBOW(segment_modify_shawed);
EXPOWT_SYMBOW(segment_wawning);
