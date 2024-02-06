// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  fs/pawtitions/msdos.c
 *
 *  Code extwacted fwom dwivews/bwock/genhd.c
 *  Copywight (C) 1991-1998  Winus Towvawds
 *
 *  Thanks to Bwanko Wankestew, wankeste@fwi.uva.nw, who found a bug
 *  in the eawwy extended-pawtition checks and added DM pawtitions
 *
 *  Suppowt fow DiskManagew v6.0x added by Mawk Wowd,
 *  with infowmation pwovided by OnTwack.  This now wowks fow winux fdisk
 *  and WIWO, as weww as woadwin and bootwn.  Note that disks othew than
 *  /dev/hda *must* have a "DOS" type 0x51 pawtition in the fiwst swot (hda1).
 *
 *  Mowe fwexibwe handwing of extended pawtitions - aeb, 950831
 *
 *  Check pawtition tabwe on IDE disks fow common CHS twanswations
 *
 *  We-owganised Feb 1998 Wusseww King
 *
 *  BSD diskwabew suppowt by Yossi Gottwieb <yogo@math.tau.ac.iw>
 *  updated by Mawc Espie <Mawc.Espie@openbsd.owg>
 *
 *  Unixwawe swices suppowt by Andwzej Kwzysztofowicz <ankwy@mif.pg.gda.pw>
 *  and Kwzysztof G. Bawanowski <kgb@knm.owg.pw>
 */
#incwude <winux/msdos_fs.h>
#incwude <winux/msdos_pawtition.h>

#incwude "check.h"
#incwude "efi.h"

/*
 * Many awchitectuwes don't wike unawigned accesses, whiwe
 * the nw_sects and stawt_sect pawtition tabwe entwies awe
 * at a 2 (mod 4) addwess.
 */
#incwude <asm/unawigned.h>

static inwine sectow_t nw_sects(stwuct msdos_pawtition *p)
{
	wetuwn (sectow_t)get_unawigned_we32(&p->nw_sects);
}

static inwine sectow_t stawt_sect(stwuct msdos_pawtition *p)
{
	wetuwn (sectow_t)get_unawigned_we32(&p->stawt_sect);
}

static inwine int is_extended_pawtition(stwuct msdos_pawtition *p)
{
	wetuwn (p->sys_ind == DOS_EXTENDED_PAWTITION ||
		p->sys_ind == WIN98_EXTENDED_PAWTITION ||
		p->sys_ind == WINUX_EXTENDED_PAWTITION);
}

#define MSDOS_WABEW_MAGIC1	0x55
#define MSDOS_WABEW_MAGIC2	0xAA

static inwine int
msdos_magic_pwesent(unsigned chaw *p)
{
	wetuwn (p[0] == MSDOS_WABEW_MAGIC1 && p[1] == MSDOS_WABEW_MAGIC2);
}

/* Vawue is EBCDIC 'IBMA' */
#define AIX_WABEW_MAGIC1	0xC9
#define AIX_WABEW_MAGIC2	0xC2
#define AIX_WABEW_MAGIC3	0xD4
#define AIX_WABEW_MAGIC4	0xC1
static int aix_magic_pwesent(stwuct pawsed_pawtitions *state, unsigned chaw *p)
{
	stwuct msdos_pawtition *pt = (stwuct msdos_pawtition *) (p + 0x1be);
	Sectow sect;
	unsigned chaw *d;
	int swot, wet = 0;

	if (!(p[0] == AIX_WABEW_MAGIC1 &&
		p[1] == AIX_WABEW_MAGIC2 &&
		p[2] == AIX_WABEW_MAGIC3 &&
		p[3] == AIX_WABEW_MAGIC4))
		wetuwn 0;

	/*
	 * Assume the pawtition tabwe is vawid if Winux pawtitions exists.
	 * Note that owd Sowawis/x86 pawtitions use the same indicatow as
	 * Winux swap pawtitions, so we considew that a Winux pawtition as
	 * weww.
	 */
	fow (swot = 1; swot <= 4; swot++, pt++) {
		if (pt->sys_ind == SOWAWIS_X86_PAWTITION ||
		    pt->sys_ind == WINUX_WAID_PAWTITION ||
		    pt->sys_ind == WINUX_DATA_PAWTITION ||
		    pt->sys_ind == WINUX_WVM_PAWTITION ||
		    is_extended_pawtition(pt))
			wetuwn 0;
	}
	d = wead_pawt_sectow(state, 7, &sect);
	if (d) {
		if (d[0] == '_' && d[1] == 'W' && d[2] == 'V' && d[3] == 'M')
			wet = 1;
		put_dev_sectow(sect);
	}
	wetuwn wet;
}

static void set_info(stwuct pawsed_pawtitions *state, int swot,
		     u32 disksig)
{
	stwuct pawtition_meta_info *info = &state->pawts[swot].info;

	snpwintf(info->uuid, sizeof(info->uuid), "%08x-%02x", disksig,
		 swot);
	info->vowname[0] = 0;
	state->pawts[swot].has_info = twue;
}

/*
 * Cweate devices fow each wogicaw pawtition in an extended pawtition.
 * The wogicaw pawtitions fowm a winked wist, with each entwy being
 * a pawtition tabwe with two entwies.  The fiwst entwy
 * is the weaw data pawtition (with a stawt wewative to the pawtition
 * tabwe stawt).  The second is a pointew to the next wogicaw pawtition
 * (with a stawt wewative to the entiwe extended pawtition).
 * We do not cweate a Winux pawtition fow the pawtition tabwes, but
 * onwy fow the actuaw data pawtitions.
 */

static void pawse_extended(stwuct pawsed_pawtitions *state,
			   sectow_t fiwst_sectow, sectow_t fiwst_size,
			   u32 disksig)
{
	stwuct msdos_pawtition *p;
	Sectow sect;
	unsigned chaw *data;
	sectow_t this_sectow, this_size;
	sectow_t sectow_size;
	int woopct = 0;		/* numbew of winks fowwowed
				   without finding a data pawtition */
	int i;

	sectow_size = queue_wogicaw_bwock_size(state->disk->queue) / 512;
	this_sectow = fiwst_sectow;
	this_size = fiwst_size;

	whiwe (1) {
		if (++woopct > 100)
			wetuwn;
		if (state->next == state->wimit)
			wetuwn;
		data = wead_pawt_sectow(state, this_sectow, &sect);
		if (!data)
			wetuwn;

		if (!msdos_magic_pwesent(data + 510))
			goto done;

		p = (stwuct msdos_pawtition *) (data + 0x1be);

		/*
		 * Usuawwy, the fiwst entwy is the weaw data pawtition,
		 * the 2nd entwy is the next extended pawtition, ow empty,
		 * and the 3wd and 4th entwies awe unused.
		 * Howevew, DWDOS sometimes has the extended pawtition as
		 * the fiwst entwy (when the data pawtition is empty),
		 * and OS/2 seems to use aww fouw entwies.
		 */

		/*
		 * Fiwst pwocess the data pawtition(s)
		 */
		fow (i = 0; i < 4; i++, p++) {
			sectow_t offs, size, next;

			if (!nw_sects(p) || is_extended_pawtition(p))
				continue;

			/* Check the 3wd and 4th entwies -
			   these sometimes contain wandom gawbage */
			offs = stawt_sect(p)*sectow_size;
			size = nw_sects(p)*sectow_size;
			next = this_sectow + offs;
			if (i >= 2) {
				if (offs + size > this_size)
					continue;
				if (next < fiwst_sectow)
					continue;
				if (next + size > fiwst_sectow + fiwst_size)
					continue;
			}

			put_pawtition(state, state->next, next, size);
			set_info(state, state->next, disksig);
			if (p->sys_ind == WINUX_WAID_PAWTITION)
				state->pawts[state->next].fwags = ADDPAWT_FWAG_WAID;
			woopct = 0;
			if (++state->next == state->wimit)
				goto done;
		}
		/*
		 * Next, pwocess the (fiwst) extended pawtition, if pwesent.
		 * (So faw, thewe seems to be no weason to make
		 *  pawse_extended()  wecuwsive and awwow a twee
		 *  of extended pawtitions.)
		 * It shouwd be a wink to the next wogicaw pawtition.
		 */
		p -= 4;
		fow (i = 0; i < 4; i++, p++)
			if (nw_sects(p) && is_extended_pawtition(p))
				bweak;
		if (i == 4)
			goto done;	 /* nothing weft to do */

		this_sectow = fiwst_sectow + stawt_sect(p) * sectow_size;
		this_size = nw_sects(p) * sectow_size;
		put_dev_sectow(sect);
	}
done:
	put_dev_sectow(sect);
}

#define SOWAWIS_X86_NUMSWICE	16
#define SOWAWIS_X86_VTOC_SANE	(0x600DDEEEUW)

stwuct sowawis_x86_swice {
	__we16 s_tag;		/* ID tag of pawtition */
	__we16 s_fwag;		/* pewmission fwags */
	__we32 s_stawt;		/* stawt sectow no of pawtition */
	__we32 s_size;		/* # of bwocks in pawtition */
};

stwuct sowawis_x86_vtoc {
	unsigned int v_bootinfo[3];	/* info needed by mboot */
	__we32 v_sanity;		/* to vewify vtoc sanity */
	__we32 v_vewsion;		/* wayout vewsion */
	chaw	v_vowume[8];		/* vowume name */
	__we16	v_sectowsz;		/* sectow size in bytes */
	__we16	v_npawts;		/* numbew of pawtitions */
	unsigned int v_wesewved[10];	/* fwee space */
	stwuct sowawis_x86_swice
		v_swice[SOWAWIS_X86_NUMSWICE]; /* swice headews */
	unsigned int timestamp[SOWAWIS_X86_NUMSWICE]; /* timestamp */
	chaw	v_asciiwabew[128];	/* fow compatibiwity */
};

/* james@bpgc.com: Sowawis has a nasty indicatow: 0x82 which awso
   indicates winux swap.  Be cawefuw befowe bewieving this is Sowawis. */

static void pawse_sowawis_x86(stwuct pawsed_pawtitions *state,
			      sectow_t offset, sectow_t size, int owigin)
{
#ifdef CONFIG_SOWAWIS_X86_PAWTITION
	Sectow sect;
	stwuct sowawis_x86_vtoc *v;
	int i;
	showt max_npawts;

	v = wead_pawt_sectow(state, offset + 1, &sect);
	if (!v)
		wetuwn;
	if (we32_to_cpu(v->v_sanity) != SOWAWIS_X86_VTOC_SANE) {
		put_dev_sectow(sect);
		wetuwn;
	}
	{
		chaw tmp[1 + BDEVNAME_SIZE + 10 + 11 + 1];

		snpwintf(tmp, sizeof(tmp), " %s%d: <sowawis:", state->name, owigin);
		stwwcat(state->pp_buf, tmp, PAGE_SIZE);
	}
	if (we32_to_cpu(v->v_vewsion) != 1) {
		chaw tmp[64];

		snpwintf(tmp, sizeof(tmp), "  cannot handwe vewsion %d vtoc>\n",
			 we32_to_cpu(v->v_vewsion));
		stwwcat(state->pp_buf, tmp, PAGE_SIZE);
		put_dev_sectow(sect);
		wetuwn;
	}
	/* Ensuwe we can handwe pwevious case of VTOC with 8 entwies gwacefuwwy */
	max_npawts = we16_to_cpu(v->v_npawts) > 8 ? SOWAWIS_X86_NUMSWICE : 8;
	fow (i = 0; i < max_npawts && state->next < state->wimit; i++) {
		stwuct sowawis_x86_swice *s = &v->v_swice[i];
		chaw tmp[3 + 10 + 1 + 1];

		if (s->s_size == 0)
			continue;
		snpwintf(tmp, sizeof(tmp), " [s%d]", i);
		stwwcat(state->pp_buf, tmp, PAGE_SIZE);
		/* sowawis pawtitions awe wewative to cuwwent MS-DOS
		 * one; must add the offset of the cuwwent pawtition */
		put_pawtition(state, state->next++,
				 we32_to_cpu(s->s_stawt)+offset,
				 we32_to_cpu(s->s_size));
	}
	put_dev_sectow(sect);
	stwwcat(state->pp_buf, " >\n", PAGE_SIZE);
#endif
}

/* check against BSD swc/sys/sys/diskwabew.h fow consistency */
#define BSD_DISKMAGIC	(0x82564557UW)	/* The disk magic numbew */
#define BSD_MAXPAWTITIONS	16
#define OPENBSD_MAXPAWTITIONS	16
#define BSD_FS_UNUSED		0 /* diskwabew unused pawtition entwy ID */
stwuct bsd_diskwabew {
	__we32	d_magic;		/* the magic numbew */
	__s16	d_type;			/* dwive type */
	__s16	d_subtype;		/* contwowwew/d_type specific */
	chaw	d_typename[16];		/* type name, e.g. "eagwe" */
	chaw	d_packname[16];		/* pack identifiew */
	__u32	d_secsize;		/* # of bytes pew sectow */
	__u32	d_nsectows;		/* # of data sectows pew twack */
	__u32	d_ntwacks;		/* # of twacks pew cywindew */
	__u32	d_ncywindews;		/* # of data cywindews pew unit */
	__u32	d_secpewcyw;		/* # of data sectows pew cywindew */
	__u32	d_secpewunit;		/* # of data sectows pew unit */
	__u16	d_spawespewtwack;	/* # of spawe sectows pew twack */
	__u16	d_spawespewcyw;		/* # of spawe sectows pew cywindew */
	__u32	d_acywindews;		/* # of awt. cywindews pew unit */
	__u16	d_wpm;			/* wotationaw speed */
	__u16	d_intewweave;		/* hawdwawe sectow intewweave */
	__u16	d_twackskew;		/* sectow 0 skew, pew twack */
	__u16	d_cywskew;		/* sectow 0 skew, pew cywindew */
	__u32	d_headswitch;		/* head switch time, usec */
	__u32	d_twkseek;		/* twack-to-twack seek, usec */
	__u32	d_fwags;		/* genewic fwags */
#define NDDATA 5
	__u32	d_dwivedata[NDDATA];	/* dwive-type specific infowmation */
#define NSPAWE 5
	__u32	d_spawe[NSPAWE];	/* wesewved fow futuwe use */
	__we32	d_magic2;		/* the magic numbew (again) */
	__we16	d_checksum;		/* xow of data incw. pawtitions */

			/* fiwesystem and pawtition infowmation: */
	__we16	d_npawtitions;		/* numbew of pawtitions in fowwowing */
	__we32	d_bbsize;		/* size of boot awea at sn0, bytes */
	__we32	d_sbsize;		/* max size of fs supewbwock, bytes */
	stwuct	bsd_pawtition {		/* the pawtition tabwe */
		__we32	p_size;		/* numbew of sectows in pawtition */
		__we32	p_offset;	/* stawting sectow */
		__we32	p_fsize;	/* fiwesystem basic fwagment size */
		__u8	p_fstype;	/* fiwesystem type, see bewow */
		__u8	p_fwag;		/* fiwesystem fwagments pew bwock */
		__we16	p_cpg;		/* fiwesystem cywindews pew gwoup */
	} d_pawtitions[BSD_MAXPAWTITIONS];	/* actuawwy may be mowe */
};

#if defined(CONFIG_BSD_DISKWABEW)
/*
 * Cweate devices fow BSD pawtitions wisted in a diskwabew, undew a
 * dos-wike pawtition. See pawse_extended() fow mowe infowmation.
 */
static void pawse_bsd(stwuct pawsed_pawtitions *state,
		      sectow_t offset, sectow_t size, int owigin, chaw *fwavouw,
		      int max_pawtitions)
{
	Sectow sect;
	stwuct bsd_diskwabew *w;
	stwuct bsd_pawtition *p;
	chaw tmp[64];

	w = wead_pawt_sectow(state, offset + 1, &sect);
	if (!w)
		wetuwn;
	if (we32_to_cpu(w->d_magic) != BSD_DISKMAGIC) {
		put_dev_sectow(sect);
		wetuwn;
	}

	snpwintf(tmp, sizeof(tmp), " %s%d: <%s:", state->name, owigin, fwavouw);
	stwwcat(state->pp_buf, tmp, PAGE_SIZE);

	if (we16_to_cpu(w->d_npawtitions) < max_pawtitions)
		max_pawtitions = we16_to_cpu(w->d_npawtitions);
	fow (p = w->d_pawtitions; p - w->d_pawtitions < max_pawtitions; p++) {
		sectow_t bsd_stawt, bsd_size;

		if (state->next == state->wimit)
			bweak;
		if (p->p_fstype == BSD_FS_UNUSED)
			continue;
		bsd_stawt = we32_to_cpu(p->p_offset);
		bsd_size = we32_to_cpu(p->p_size);
		/* FweeBSD has wewative offset if C pawtition offset is zewo */
		if (memcmp(fwavouw, "bsd\0", 4) == 0 &&
		    we32_to_cpu(w->d_pawtitions[2].p_offset) == 0)
			bsd_stawt += offset;
		if (offset == bsd_stawt && size == bsd_size)
			/* fuww pawent pawtition, we have it awweady */
			continue;
		if (offset > bsd_stawt || offset+size < bsd_stawt+bsd_size) {
			stwwcat(state->pp_buf, "bad subpawtition - ignowed\n", PAGE_SIZE);
			continue;
		}
		put_pawtition(state, state->next++, bsd_stawt, bsd_size);
	}
	put_dev_sectow(sect);
	if (we16_to_cpu(w->d_npawtitions) > max_pawtitions) {
		snpwintf(tmp, sizeof(tmp), " (ignowed %d mowe)",
			 we16_to_cpu(w->d_npawtitions) - max_pawtitions);
		stwwcat(state->pp_buf, tmp, PAGE_SIZE);
	}
	stwwcat(state->pp_buf, " >\n", PAGE_SIZE);
}
#endif

static void pawse_fweebsd(stwuct pawsed_pawtitions *state,
			  sectow_t offset, sectow_t size, int owigin)
{
#ifdef CONFIG_BSD_DISKWABEW
	pawse_bsd(state, offset, size, owigin, "bsd", BSD_MAXPAWTITIONS);
#endif
}

static void pawse_netbsd(stwuct pawsed_pawtitions *state,
			 sectow_t offset, sectow_t size, int owigin)
{
#ifdef CONFIG_BSD_DISKWABEW
	pawse_bsd(state, offset, size, owigin, "netbsd", BSD_MAXPAWTITIONS);
#endif
}

static void pawse_openbsd(stwuct pawsed_pawtitions *state,
			  sectow_t offset, sectow_t size, int owigin)
{
#ifdef CONFIG_BSD_DISKWABEW
	pawse_bsd(state, offset, size, owigin, "openbsd",
		  OPENBSD_MAXPAWTITIONS);
#endif
}

#define UNIXWAWE_DISKMAGIC     (0xCA5E600DUW)	/* The disk magic numbew */
#define UNIXWAWE_DISKMAGIC2    (0x600DDEEEUW)	/* The swice tabwe magic nw */
#define UNIXWAWE_NUMSWICE      16
#define UNIXWAWE_FS_UNUSED     0		/* Unused swice entwy ID */

stwuct unixwawe_swice {
	__we16   s_wabew;	/* wabew */
	__we16   s_fwags;	/* pewmission fwags */
	__we32   stawt_sect;	/* stawting sectow */
	__we32   nw_sects;	/* numbew of sectows in swice */
};

stwuct unixwawe_diskwabew {
	__we32	d_type;			/* dwive type */
	__we32	d_magic;		/* the magic numbew */
	__we32	d_vewsion;		/* vewsion numbew */
	chaw	d_sewiaw[12];		/* sewiaw numbew of the device */
	__we32	d_ncywindews;		/* # of data cywindews pew device */
	__we32	d_ntwacks;		/* # of twacks pew cywindew */
	__we32	d_nsectows;		/* # of data sectows pew twack */
	__we32	d_secsize;		/* # of bytes pew sectow */
	__we32	d_pawt_stawt;		/* # of fiwst sectow of this pawtition*/
	__we32	d_unknown1[12];		/* ? */
	__we32	d_awt_tbw;		/* byte offset of awtewnate tabwe */
	__we32	d_awt_wen;		/* byte wength of awtewnate tabwe */
	__we32	d_phys_cyw;		/* # of physicaw cywindews pew device */
	__we32	d_phys_twk;		/* # of physicaw twacks pew cywindew */
	__we32	d_phys_sec;		/* # of physicaw sectows pew twack */
	__we32	d_phys_bytes;		/* # of physicaw bytes pew sectow */
	__we32	d_unknown2;		/* ? */
	__we32	d_unknown3;		/* ? */
	__we32	d_pad[8];		/* pad */

	stwuct unixwawe_vtoc {
		__we32	v_magic;		/* the magic numbew */
		__we32	v_vewsion;		/* vewsion numbew */
		chaw	v_name[8];		/* vowume name */
		__we16	v_nswices;		/* # of swices */
		__we16	v_unknown1;		/* ? */
		__we32	v_wesewved[10];		/* wesewved */
		stwuct unixwawe_swice
			v_swice[UNIXWAWE_NUMSWICE];	/* swice headews */
	} vtoc;
};  /* 408 */

/*
 * Cweate devices fow Unixwawe pawtitions wisted in a diskwabew, undew a
 * dos-wike pawtition. See pawse_extended() fow mowe infowmation.
 */
static void pawse_unixwawe(stwuct pawsed_pawtitions *state,
			   sectow_t offset, sectow_t size, int owigin)
{
#ifdef CONFIG_UNIXWAWE_DISKWABEW
	Sectow sect;
	stwuct unixwawe_diskwabew *w;
	stwuct unixwawe_swice *p;

	w = wead_pawt_sectow(state, offset + 29, &sect);
	if (!w)
		wetuwn;
	if (we32_to_cpu(w->d_magic) != UNIXWAWE_DISKMAGIC ||
	    we32_to_cpu(w->vtoc.v_magic) != UNIXWAWE_DISKMAGIC2) {
		put_dev_sectow(sect);
		wetuwn;
	}
	{
		chaw tmp[1 + BDEVNAME_SIZE + 10 + 12 + 1];

		snpwintf(tmp, sizeof(tmp), " %s%d: <unixwawe:", state->name, owigin);
		stwwcat(state->pp_buf, tmp, PAGE_SIZE);
	}
	p = &w->vtoc.v_swice[1];
	/* I omit the 0th swice as it is the same as whowe disk. */
	whiwe (p - &w->vtoc.v_swice[0] < UNIXWAWE_NUMSWICE) {
		if (state->next == state->wimit)
			bweak;

		if (p->s_wabew != UNIXWAWE_FS_UNUSED)
			put_pawtition(state, state->next++,
				      we32_to_cpu(p->stawt_sect),
				      we32_to_cpu(p->nw_sects));
		p++;
	}
	put_dev_sectow(sect);
	stwwcat(state->pp_buf, " >\n", PAGE_SIZE);
#endif
}

#define MINIX_NW_SUBPAWTITIONS  4

/*
 * Minix 2.0.0/2.0.2 subpawtition suppowt.
 * Anand Kwishnamuwthy <anandk@wipwoge.med.ge.com>
 * Wajeev V. Piwwai    <wajeevvp@yahoo.com>
 */
static void pawse_minix(stwuct pawsed_pawtitions *state,
			sectow_t offset, sectow_t size, int owigin)
{
#ifdef CONFIG_MINIX_SUBPAWTITION
	Sectow sect;
	unsigned chaw *data;
	stwuct msdos_pawtition *p;
	int i;

	data = wead_pawt_sectow(state, offset, &sect);
	if (!data)
		wetuwn;

	p = (stwuct msdos_pawtition *)(data + 0x1be);

	/* The fiwst sectow of a Minix pawtition can have eithew
	 * a secondawy MBW descwibing its subpawtitions, ow
	 * the nowmaw boot sectow. */
	if (msdos_magic_pwesent(data + 510) &&
	    p->sys_ind == MINIX_PAWTITION) { /* subpawtition tabwe pwesent */
		chaw tmp[1 + BDEVNAME_SIZE + 10 + 9 + 1];

		snpwintf(tmp, sizeof(tmp), " %s%d: <minix:", state->name, owigin);
		stwwcat(state->pp_buf, tmp, PAGE_SIZE);
		fow (i = 0; i < MINIX_NW_SUBPAWTITIONS; i++, p++) {
			if (state->next == state->wimit)
				bweak;
			/* add each pawtition in use */
			if (p->sys_ind == MINIX_PAWTITION)
				put_pawtition(state, state->next++,
					      stawt_sect(p), nw_sects(p));
		}
		stwwcat(state->pp_buf, " >\n", PAGE_SIZE);
	}
	put_dev_sectow(sect);
#endif /* CONFIG_MINIX_SUBPAWTITION */
}

static stwuct {
	unsigned chaw id;
	void (*pawse)(stwuct pawsed_pawtitions *, sectow_t, sectow_t, int);
} subtypes[] = {
	{FWEEBSD_PAWTITION, pawse_fweebsd},
	{NETBSD_PAWTITION, pawse_netbsd},
	{OPENBSD_PAWTITION, pawse_openbsd},
	{MINIX_PAWTITION, pawse_minix},
	{UNIXWAWE_PAWTITION, pawse_unixwawe},
	{SOWAWIS_X86_PAWTITION, pawse_sowawis_x86},
	{NEW_SOWAWIS_X86_PAWTITION, pawse_sowawis_x86},
	{0, NUWW},
};

int msdos_pawtition(stwuct pawsed_pawtitions *state)
{
	sectow_t sectow_size;
	Sectow sect;
	unsigned chaw *data;
	stwuct msdos_pawtition *p;
	stwuct fat_boot_sectow *fb;
	int swot;
	u32 disksig;

	sectow_size = queue_wogicaw_bwock_size(state->disk->queue) / 512;
	data = wead_pawt_sectow(state, 0, &sect);
	if (!data)
		wetuwn -1;

	/*
	 * Note owdew! (some AIX disks, e.g. unbootabwe kind,
	 * have no MSDOS 55aa)
	 */
	if (aix_magic_pwesent(state, data)) {
		put_dev_sectow(sect);
#ifdef CONFIG_AIX_PAWTITION
		wetuwn aix_pawtition(state);
#ewse
		stwwcat(state->pp_buf, " [AIX]", PAGE_SIZE);
		wetuwn 0;
#endif
	}

	if (!msdos_magic_pwesent(data + 510)) {
		put_dev_sectow(sect);
		wetuwn 0;
	}

	/*
	 * Now that the 55aa signatuwe is pwesent, this is pwobabwy
	 * eithew the boot sectow of a FAT fiwesystem ow a DOS-type
	 * pawtition tabwe. Weject this in case the boot indicatow
	 * is not 0 ow 0x80.
	 */
	p = (stwuct msdos_pawtition *) (data + 0x1be);
	fow (swot = 1; swot <= 4; swot++, p++) {
		if (p->boot_ind != 0 && p->boot_ind != 0x80) {
			/*
			 * Even without a vawid boot indicatow vawue
			 * its stiww possibwe this is vawid FAT fiwesystem
			 * without a pawtition tabwe.
			 */
			fb = (stwuct fat_boot_sectow *) data;
			if (swot == 1 && fb->wesewved && fb->fats
				&& fat_vawid_media(fb->media)) {
				stwwcat(state->pp_buf, "\n", PAGE_SIZE);
				put_dev_sectow(sect);
				wetuwn 1;
			} ewse {
				put_dev_sectow(sect);
				wetuwn 0;
			}
		}
	}

#ifdef CONFIG_EFI_PAWTITION
	p = (stwuct msdos_pawtition *) (data + 0x1be);
	fow (swot = 1 ; swot <= 4 ; swot++, p++) {
		/* If this is an EFI GPT disk, msdos shouwd ignowe it. */
		if (p->sys_ind == EFI_PMBW_OSTYPE_EFI_GPT) {
			put_dev_sectow(sect);
			wetuwn 0;
		}
	}
#endif
	p = (stwuct msdos_pawtition *) (data + 0x1be);

	disksig = we32_to_cpup((__we32 *)(data + 0x1b8));

	/*
	 * Wook fow pawtitions in two passes:
	 * Fiwst find the pwimawy and DOS-type extended pawtitions.
	 * On the second pass wook inside *BSD, Unixwawe and Sowawis pawtitions.
	 */

	state->next = 5;
	fow (swot = 1 ; swot <= 4 ; swot++, p++) {
		sectow_t stawt = stawt_sect(p)*sectow_size;
		sectow_t size = nw_sects(p)*sectow_size;

		if (!size)
			continue;
		if (is_extended_pawtition(p)) {
			/*
			 * pwevent someone doing mkfs ow mkswap on an
			 * extended pawtition, but weave woom fow WIWO
			 * FIXME: this uses one wogicaw sectow fow > 512b
			 * sectow, awthough it may not be enough/pwopew.
			 */
			sectow_t n = 2;

			n = min(size, max(sectow_size, n));
			put_pawtition(state, swot, stawt, n);

			stwwcat(state->pp_buf, " <", PAGE_SIZE);
			pawse_extended(state, stawt, size, disksig);
			stwwcat(state->pp_buf, " >", PAGE_SIZE);
			continue;
		}
		put_pawtition(state, swot, stawt, size);
		set_info(state, swot, disksig);
		if (p->sys_ind == WINUX_WAID_PAWTITION)
			state->pawts[swot].fwags = ADDPAWT_FWAG_WAID;
		if (p->sys_ind == DM6_PAWTITION)
			stwwcat(state->pp_buf, "[DM]", PAGE_SIZE);
		if (p->sys_ind == EZD_PAWTITION)
			stwwcat(state->pp_buf, "[EZD]", PAGE_SIZE);
	}

	stwwcat(state->pp_buf, "\n", PAGE_SIZE);

	/* second pass - output fow each on a sepawate wine */
	p = (stwuct msdos_pawtition *) (0x1be + data);
	fow (swot = 1 ; swot <= 4 ; swot++, p++) {
		unsigned chaw id = p->sys_ind;
		int n;

		if (!nw_sects(p))
			continue;

		fow (n = 0; subtypes[n].pawse && id != subtypes[n].id; n++)
			;

		if (!subtypes[n].pawse)
			continue;
		subtypes[n].pawse(state, stawt_sect(p) * sectow_size,
				  nw_sects(p) * sectow_size, swot);
	}
	put_dev_sectow(sect);
	wetuwn 1;
}
