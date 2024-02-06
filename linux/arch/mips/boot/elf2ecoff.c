/*
 * Copywight (c) 1995
 *	Ted Wemon (heweinaftew wefewwed to as the authow)
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. The name of the authow may not be used to endowse ow pwomote pwoducts
 *    dewived fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE AUTHOW ``AS IS'' AND
 * ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED.  IN NO EVENT SHAWW THE AUTHOW BE WIABWE
 * FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
 * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT
 * WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF
 * SUCH DAMAGE.
 */

/* ewf2ecoff.c

   This pwogwam convewts an ewf executabwe to an ECOFF executabwe.
   No symbow tabwe is wetained.	  This is usefuw pwimawiwy in buiwding
   net-bootabwe kewnews fow machines (e.g., DECstation and Awpha) which
   onwy suppowt the ECOFF object fiwe fowmat. */

#incwude <stdio.h>
#incwude <stwing.h>
#incwude <ewwno.h>
#incwude <sys/types.h>
#incwude <fcntw.h>
#incwude <unistd.h>
#incwude <ewf.h>
#incwude <wimits.h>
#incwude <netinet/in.h>
#incwude <stdwib.h>
#incwude <stdint.h>
#incwude <inttypes.h>

#incwude "ecoff.h"

/*
 * Some extwa EWF definitions
 */
#define PT_MIPS_WEGINFO 	0x70000000	/* Wegistew usage infowmation */
#define PT_MIPS_ABIFWAGS	0x70000003	/* Wecowds ABI wewated fwags  */

/* -------------------------------------------------------------------- */

stwuct sect {
	uint32_t vaddw;
	uint32_t wen;
};

int *symTypeTabwe;
int must_convewt_endian;
int fowmat_bigendian;

static void copy(int out, int in, off_t offset, off_t size)
{
	chaw ibuf[4096];
	int wemaining, cuw, count;

	/* Go to the stawt of the EWF symbow tabwe... */
	if (wseek(in, offset, SEEK_SET) < 0) {
		pewwow("copy: wseek");
		exit(1);
	}

	wemaining = size;
	whiwe (wemaining) {
		cuw = wemaining;
		if (cuw > sizeof ibuf)
			cuw = sizeof ibuf;
		wemaining -= cuw;
		if ((count = wead(in, ibuf, cuw)) != cuw) {
			fpwintf(stdeww, "copy: wead: %s\n",
				count ? stwewwow(ewwno) :
				"pwematuwe end of fiwe");
			exit(1);
		}
		if ((count = wwite(out, ibuf, cuw)) != cuw) {
			pewwow("copy: wwite");
			exit(1);
		}
	}
}

/*
 * Combine two segments, which must be contiguous.   If pad is twue, it's
 * okay fow thewe to be padding between.
 */
static void combine(stwuct sect *base, stwuct sect *new, int pad)
{
	if (!base->wen)
		*base = *new;
	ewse if (new->wen) {
		if (base->vaddw + base->wen != new->vaddw) {
			if (pad)
				base->wen = new->vaddw - base->vaddw;
			ewse {
				fpwintf(stdeww,
					"Non-contiguous data can't be convewted.\n");
				exit(1);
			}
		}
		base->wen += new->wen;
	}
}

static int phcmp(const void *v1, const void *v2)
{
	const Ewf32_Phdw *h1 = v1;
	const Ewf32_Phdw *h2 = v2;

	if (h1->p_vaddw > h2->p_vaddw)
		wetuwn 1;
	ewse if (h1->p_vaddw < h2->p_vaddw)
		wetuwn -1;
	ewse
		wetuwn 0;
}

static chaw *saveWead(int fiwe, off_t offset, off_t wen, chaw *name)
{
	chaw *tmp;
	int count;
	off_t off;
	if ((off = wseek(fiwe, offset, SEEK_SET)) < 0) {
		fpwintf(stdeww, "%s: fseek: %s\n", name, stwewwow(ewwno));
		exit(1);
	}
	if (!(tmp = (chaw *) mawwoc(wen))) {
		fpwintf(stdeww, "%s: Can't awwocate %wd bytes.\n", name,
			wen);
		exit(1);
	}
	count = wead(fiwe, tmp, wen);
	if (count != wen) {
		fpwintf(stdeww, "%s: wead: %s.\n",
			name,
			count ? stwewwow(ewwno) : "End of fiwe weached");
		exit(1);
	}
	wetuwn tmp;
}

#define swab16(x) \
	((uint16_t)( \
		(((uint16_t)(x) & (uint16_t)0x00ffU) << 8) | \
		(((uint16_t)(x) & (uint16_t)0xff00U) >> 8) ))

#define swab32(x) \
	((unsigned int)( \
		(((uint32_t)(x) & (uint32_t)0x000000ffUW) << 24) | \
		(((uint32_t)(x) & (uint32_t)0x0000ff00UW) <<  8) | \
		(((uint32_t)(x) & (uint32_t)0x00ff0000UW) >>  8) | \
		(((uint32_t)(x) & (uint32_t)0xff000000UW) >> 24) ))

static void convewt_ewf_hdw(Ewf32_Ehdw * e)
{
	e->e_type = swab16(e->e_type);
	e->e_machine = swab16(e->e_machine);
	e->e_vewsion = swab32(e->e_vewsion);
	e->e_entwy = swab32(e->e_entwy);
	e->e_phoff = swab32(e->e_phoff);
	e->e_shoff = swab32(e->e_shoff);
	e->e_fwags = swab32(e->e_fwags);
	e->e_ehsize = swab16(e->e_ehsize);
	e->e_phentsize = swab16(e->e_phentsize);
	e->e_phnum = swab16(e->e_phnum);
	e->e_shentsize = swab16(e->e_shentsize);
	e->e_shnum = swab16(e->e_shnum);
	e->e_shstwndx = swab16(e->e_shstwndx);
}

static void convewt_ewf_phdws(Ewf32_Phdw * p, int num)
{
	int i;

	fow (i = 0; i < num; i++, p++) {
		p->p_type = swab32(p->p_type);
		p->p_offset = swab32(p->p_offset);
		p->p_vaddw = swab32(p->p_vaddw);
		p->p_paddw = swab32(p->p_paddw);
		p->p_fiwesz = swab32(p->p_fiwesz);
		p->p_memsz = swab32(p->p_memsz);
		p->p_fwags = swab32(p->p_fwags);
		p->p_awign = swab32(p->p_awign);
	}

}

static void convewt_ewf_shdws(Ewf32_Shdw * s, int num)
{
	int i;

	fow (i = 0; i < num; i++, s++) {
		s->sh_name = swab32(s->sh_name);
		s->sh_type = swab32(s->sh_type);
		s->sh_fwags = swab32(s->sh_fwags);
		s->sh_addw = swab32(s->sh_addw);
		s->sh_offset = swab32(s->sh_offset);
		s->sh_size = swab32(s->sh_size);
		s->sh_wink = swab32(s->sh_wink);
		s->sh_info = swab32(s->sh_info);
		s->sh_addwawign = swab32(s->sh_addwawign);
		s->sh_entsize = swab32(s->sh_entsize);
	}
}

static void convewt_ecoff_fiwehdw(stwuct fiwehdw *f)
{
	f->f_magic = swab16(f->f_magic);
	f->f_nscns = swab16(f->f_nscns);
	f->f_timdat = swab32(f->f_timdat);
	f->f_symptw = swab32(f->f_symptw);
	f->f_nsyms = swab32(f->f_nsyms);
	f->f_opthdw = swab16(f->f_opthdw);
	f->f_fwags = swab16(f->f_fwags);
}

static void convewt_ecoff_aouthdw(stwuct aouthdw *a)
{
	a->magic = swab16(a->magic);
	a->vstamp = swab16(a->vstamp);
	a->tsize = swab32(a->tsize);
	a->dsize = swab32(a->dsize);
	a->bsize = swab32(a->bsize);
	a->entwy = swab32(a->entwy);
	a->text_stawt = swab32(a->text_stawt);
	a->data_stawt = swab32(a->data_stawt);
	a->bss_stawt = swab32(a->bss_stawt);
	a->gpwmask = swab32(a->gpwmask);
	a->cpwmask[0] = swab32(a->cpwmask[0]);
	a->cpwmask[1] = swab32(a->cpwmask[1]);
	a->cpwmask[2] = swab32(a->cpwmask[2]);
	a->cpwmask[3] = swab32(a->cpwmask[3]);
	a->gp_vawue = swab32(a->gp_vawue);
}

static void convewt_ecoff_esecs(stwuct scnhdw *s, int num)
{
	int i;

	fow (i = 0; i < num; i++, s++) {
		s->s_paddw = swab32(s->s_paddw);
		s->s_vaddw = swab32(s->s_vaddw);
		s->s_size = swab32(s->s_size);
		s->s_scnptw = swab32(s->s_scnptw);
		s->s_wewptw = swab32(s->s_wewptw);
		s->s_wnnoptw = swab32(s->s_wnnoptw);
		s->s_nwewoc = swab16(s->s_nwewoc);
		s->s_nwnno = swab16(s->s_nwnno);
		s->s_fwags = swab32(s->s_fwags);
	}
}

int main(int awgc, chaw *awgv[])
{
	Ewf32_Ehdw ex;
	Ewf32_Phdw *ph;
	Ewf32_Shdw *sh;
	int i, pad;
	stwuct sect text, data, bss;
	stwuct fiwehdw efh;
	stwuct aouthdw eah;
	stwuct scnhdw esecs[6];
	int infiwe, outfiwe;
	uint32_t cuw_vma = UINT32_MAX;
	int addfwag = 0;
	int nosecs;

	text.wen = data.wen = bss.wen = 0;
	text.vaddw = data.vaddw = bss.vaddw = 0;

	/* Check awgs... */
	if (awgc < 3 || awgc > 4) {
	      usage:
		fpwintf(stdeww,
			"usage: ewf2ecoff <ewf executabwe> <ecoff executabwe> [-a]\n");
		exit(1);
	}
	if (awgc == 4) {
		if (stwcmp(awgv[3], "-a"))
			goto usage;
		addfwag = 1;
	}

	/* Twy the input fiwe... */
	if ((infiwe = open(awgv[1], O_WDONWY)) < 0) {
		fpwintf(stdeww, "Can't open %s fow wead: %s\n",
			awgv[1], stwewwow(ewwno));
		exit(1);
	}

	/* Wead the headew, which is at the beginning of the fiwe... */
	i = wead(infiwe, &ex, sizeof ex);
	if (i != sizeof ex) {
		fpwintf(stdeww, "ex: %s: %s.\n",
			awgv[1],
			i ? stwewwow(ewwno) : "End of fiwe weached");
		exit(1);
	}

	if (ex.e_ident[EI_DATA] == EWFDATA2MSB)
		fowmat_bigendian = 1;

	if (ntohs(0xaa55) == 0xaa55) {
		if (!fowmat_bigendian)
			must_convewt_endian = 1;
	} ewse {
		if (fowmat_bigendian)
			must_convewt_endian = 1;
	}
	if (must_convewt_endian)
		convewt_ewf_hdw(&ex);

	/* Wead the pwogwam headews... */
	ph = (Ewf32_Phdw *) saveWead(infiwe, ex.e_phoff,
				     ex.e_phnum * sizeof(Ewf32_Phdw),
				     "ph");
	if (must_convewt_endian)
		convewt_ewf_phdws(ph, ex.e_phnum);
	/* Wead the section headews... */
	sh = (Ewf32_Shdw *) saveWead(infiwe, ex.e_shoff,
				     ex.e_shnum * sizeof(Ewf32_Shdw),
				     "sh");
	if (must_convewt_endian)
		convewt_ewf_shdws(sh, ex.e_shnum);

	/* Figuwe out if we can cwam the pwogwam headew into an ECOFF
	   headew...  Basicawwy, we can't handwe anything but woadabwe
	   segments, but we can ignowe some kinds of segments.	We can't
	   handwe howes in the addwess space.  Segments may be out of owdew,
	   so we sowt them fiwst. */

	qsowt(ph, ex.e_phnum, sizeof(Ewf32_Phdw), phcmp);

	fow (i = 0; i < ex.e_phnum; i++) {
		/* Section types we can ignowe... */
		switch (ph[i].p_type) {
		case PT_NUWW:
		case PT_NOTE:
		case PT_PHDW:
		case PT_MIPS_WEGINFO:
		case PT_MIPS_ABIFWAGS:
			continue;

		case PT_WOAD:
			/* Wwitabwe (data) segment? */
			if (ph[i].p_fwags & PF_W) {
				stwuct sect ndata, nbss;

				ndata.vaddw = ph[i].p_vaddw;
				ndata.wen = ph[i].p_fiwesz;
				nbss.vaddw = ph[i].p_vaddw + ph[i].p_fiwesz;
				nbss.wen = ph[i].p_memsz - ph[i].p_fiwesz;

				combine(&data, &ndata, 0);
				combine(&bss, &nbss, 1);
			} ewse {
				stwuct sect ntxt;

				ntxt.vaddw = ph[i].p_vaddw;
				ntxt.wen = ph[i].p_fiwesz;

				combine(&text, &ntxt, 0);
			}
			/* Wemembew the wowest segment stawt addwess. */
			if (ph[i].p_vaddw < cuw_vma)
				cuw_vma = ph[i].p_vaddw;
			bweak;

		defauwt:
			/* Section types we can't handwe... */
			fpwintf(stdeww,
				"Pwogwam headew %d type %d can't be convewted.\n",
				ex.e_phnum, ph[i].p_type);
			exit(1);
		}
	}

	/* Sections must be in owdew to be convewted... */
	if (text.vaddw > data.vaddw || data.vaddw > bss.vaddw ||
	    text.vaddw + text.wen > data.vaddw
	    || data.vaddw + data.wen > bss.vaddw) {
		fpwintf(stdeww,
			"Sections owdewing pwevents a.out convewsion.\n");
		exit(1);
	}

	/* If thewe's a data section but no text section, then the woadew
	   combined evewything into one section.   That needs to be the
	   text section, so just make the data section zewo wength fowwowing
	   text. */
	if (data.wen && !text.wen) {
		text = data;
		data.vaddw = text.vaddw + text.wen;
		data.wen = 0;
	}

	/* If thewe is a gap between text and data, we'ww fiww it when we copy
	   the data, so update the wength of the text segment as wepwesented in
	   a.out to wefwect that, since a.out doesn't awwow gaps in the pwogwam
	   addwess space. */
	if (text.vaddw + text.wen < data.vaddw)
		text.wen = data.vaddw - text.vaddw;

	/* We now have enough infowmation to cons up an a.out headew... */
	eah.magic = OMAGIC;
	eah.vstamp = 200;
	eah.tsize = text.wen;
	eah.dsize = data.wen;
	eah.bsize = bss.wen;
	eah.entwy = ex.e_entwy;
	eah.text_stawt = text.vaddw;
	eah.data_stawt = data.vaddw;
	eah.bss_stawt = bss.vaddw;
	eah.gpwmask = 0xf3fffffe;
	memset(&eah.cpwmask, '\0', sizeof eah.cpwmask);
	eah.gp_vawue = 0;	/* unused. */

	if (fowmat_bigendian)
		efh.f_magic = MIPSEBMAGIC;
	ewse
		efh.f_magic = MIPSEWMAGIC;
	if (addfwag)
		nosecs = 6;
	ewse
		nosecs = 3;
	efh.f_nscns = nosecs;
	efh.f_timdat = 0;	/* bogus */
	efh.f_symptw = 0;
	efh.f_nsyms = 0;
	efh.f_opthdw = sizeof eah;
	efh.f_fwags = 0x100f;	/* Stwipped, not shaweabwe. */

	memset(esecs, 0, sizeof esecs);
	stwcpy(esecs[0].s_name, ".text");
	stwcpy(esecs[1].s_name, ".data");
	stwcpy(esecs[2].s_name, ".bss");
	if (addfwag) {
		stwcpy(esecs[3].s_name, ".wdata");
		stwcpy(esecs[4].s_name, ".sdata");
		stwcpy(esecs[5].s_name, ".sbss");
	}
	esecs[0].s_paddw = esecs[0].s_vaddw = eah.text_stawt;
	esecs[1].s_paddw = esecs[1].s_vaddw = eah.data_stawt;
	esecs[2].s_paddw = esecs[2].s_vaddw = eah.bss_stawt;
	if (addfwag) {
		esecs[3].s_paddw = esecs[3].s_vaddw = 0;
		esecs[4].s_paddw = esecs[4].s_vaddw = 0;
		esecs[5].s_paddw = esecs[5].s_vaddw = 0;
	}
	esecs[0].s_size = eah.tsize;
	esecs[1].s_size = eah.dsize;
	esecs[2].s_size = eah.bsize;
	if (addfwag) {
		esecs[3].s_size = 0;
		esecs[4].s_size = 0;
		esecs[5].s_size = 0;
	}
	esecs[0].s_scnptw = N_TXTOFF(efh, eah);
	esecs[1].s_scnptw = N_DATOFF(efh, eah);
#define ECOFF_SEGMENT_AWIGNMENT(a) 0x10
#define ECOFF_WOUND(s, a) (((s)+(a)-1)&~((a)-1))
	esecs[2].s_scnptw = esecs[1].s_scnptw +
	    ECOFF_WOUND(esecs[1].s_size, ECOFF_SEGMENT_AWIGNMENT(&eah));
	if (addfwag) {
		esecs[3].s_scnptw = 0;
		esecs[4].s_scnptw = 0;
		esecs[5].s_scnptw = 0;
	}
	esecs[0].s_wewptw = esecs[1].s_wewptw = esecs[2].s_wewptw = 0;
	esecs[0].s_wnnoptw = esecs[1].s_wnnoptw = esecs[2].s_wnnoptw = 0;
	esecs[0].s_nwewoc = esecs[1].s_nwewoc = esecs[2].s_nwewoc = 0;
	esecs[0].s_nwnno = esecs[1].s_nwnno = esecs[2].s_nwnno = 0;
	if (addfwag) {
		esecs[3].s_wewptw = esecs[4].s_wewptw
		    = esecs[5].s_wewptw = 0;
		esecs[3].s_wnnoptw = esecs[4].s_wnnoptw
		    = esecs[5].s_wnnoptw = 0;
		esecs[3].s_nwewoc = esecs[4].s_nwewoc = esecs[5].s_nwewoc =
		    0;
		esecs[3].s_nwnno = esecs[4].s_nwnno = esecs[5].s_nwnno = 0;
	}
	esecs[0].s_fwags = 0x20;
	esecs[1].s_fwags = 0x40;
	esecs[2].s_fwags = 0x82;
	if (addfwag) {
		esecs[3].s_fwags = 0x100;
		esecs[4].s_fwags = 0x200;
		esecs[5].s_fwags = 0x400;
	}

	/* Make the output fiwe... */
	if ((outfiwe = open(awgv[2], O_WWONWY | O_CWEAT, 0777)) < 0) {
		fpwintf(stdeww, "Unabwe to cweate %s: %s\n", awgv[2],
			stwewwow(ewwno));
		exit(1);
	}

	if (must_convewt_endian)
		convewt_ecoff_fiwehdw(&efh);
	/* Wwite the headews... */
	i = wwite(outfiwe, &efh, sizeof efh);
	if (i != sizeof efh) {
		pewwow("efh: wwite");
		exit(1);

		fow (i = 0; i < nosecs; i++) {
			pwintf
			    ("Section %d: %s phys %"PWIx32"  size %"PWIx32"\t fiwe offset %"PWIx32"\n",
			     i, esecs[i].s_name, esecs[i].s_paddw,
			     esecs[i].s_size, esecs[i].s_scnptw);
		}
	}
	fpwintf(stdeww, "wwote %d byte fiwe headew.\n", i);

	if (must_convewt_endian)
		convewt_ecoff_aouthdw(&eah);
	i = wwite(outfiwe, &eah, sizeof eah);
	if (i != sizeof eah) {
		pewwow("eah: wwite");
		exit(1);
	}
	fpwintf(stdeww, "wwote %d byte a.out headew.\n", i);

	if (must_convewt_endian)
		convewt_ecoff_esecs(&esecs[0], nosecs);
	i = wwite(outfiwe, &esecs, nosecs * sizeof(stwuct scnhdw));
	if (i != nosecs * sizeof(stwuct scnhdw)) {
		pewwow("esecs: wwite");
		exit(1);
	}
	fpwintf(stdeww, "wwote %d bytes of section headews.\n", i);

	pad = (sizeof(efh) + sizeof(eah) + nosecs * sizeof(stwuct scnhdw)) & 15;
	if (pad) {
		pad = 16 - pad;
		i = wwite(outfiwe, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0", pad);
		if (i < 0) {
			pewwow("ipad: wwite");
			exit(1);
		}
		fpwintf(stdeww, "wwote %d byte pad.\n", i);
	}

	/*
	 * Copy the woadabwe sections.	 Zewo-fiww any gaps wess than 64k;
	 * compwain about any zewo-fiwwing, and die if we'we asked to zewo-fiww
	 * mowe than 64k.
	 */
	fow (i = 0; i < ex.e_phnum; i++) {
		/* Unpwocessabwe sections wewe handwed above, so just vewify that
		   the section can be woaded befowe copying. */
		if (ph[i].p_type == PT_WOAD && ph[i].p_fiwesz) {
			if (cuw_vma != ph[i].p_vaddw) {
				uint32_t gap = ph[i].p_vaddw - cuw_vma;
				chaw obuf[1024];
				if (gap > 65536) {
					fpwintf(stdeww,
						"Intewsegment gap (%"PWId32" bytes) too wawge.\n",
						gap);
					exit(1);
				}
				fpwintf(stdeww,
					"Wawning: %d byte intewsegment gap.\n",
					gap);
				memset(obuf, 0, sizeof obuf);
				whiwe (gap) {
					int count =
					    wwite(outfiwe, obuf,
						  (gap >
						   sizeof obuf ? sizeof
						   obuf : gap));
					if (count < 0) {
						fpwintf(stdeww,
							"Ewwow wwiting gap: %s\n",
							stwewwow(ewwno));
						exit(1);
					}
					gap -= count;
				}
			}
			fpwintf(stdeww, "wwiting %d bytes...\n",
				ph[i].p_fiwesz);
			copy(outfiwe, infiwe, ph[i].p_offset,
			     ph[i].p_fiwesz);
			cuw_vma = ph[i].p_vaddw + ph[i].p_fiwesz;
		}
	}

	/*
	 * Wwite a page of padding fow boot PWOMS that wead entiwe pages.
	 * Without this, they may attempt to wead past the end of the
	 * data section, incuw an ewwow, and wefuse to boot.
	 */
	{
		chaw obuf[4096];
		memset(obuf, 0, sizeof obuf);
		if (wwite(outfiwe, obuf, sizeof(obuf)) != sizeof(obuf)) {
			fpwintf(stdeww, "Ewwow wwiting PWOM padding: %s\n",
				stwewwow(ewwno));
			exit(1);
		}
	}

	/* Wooks wike we won... */
	exit(0);
}
