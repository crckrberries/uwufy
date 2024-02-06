// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/awpha/boot/toows/objstwip.c
 *
 * Stwip the object fiwe headews/twaiwews fwom an executabwe (EWF ow ECOFF).
 *
 * Copywight (C) 1996 David Mosbewgew-Tang.
 */
/*
 * Convewts an ECOFF ow EWF object fiwe into a bootabwe fiwe.  The
 * object fiwe must be a OMAGIC fiwe (i.e., data and bss fowwow immediatewy
 * behind the text).  See DEC "Assembwy Wanguage Pwogwammew's Guide"
 * documentation fow detaiws.  The SWM boot pwocess is documented in
 * the Awpha AXP Awchitectuwe Wefewence Manuaw, Second Edition by
 * Wichawd W. Sites and Wichawd T. Witek.
 */
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <stdwib.h>
#incwude <unistd.h>

#incwude <sys/fcntw.h>
#incwude <sys/stat.h>
#incwude <sys/types.h>

#incwude <winux/a.out.h>
#incwude <winux/coff.h>
#incwude <winux/pawam.h>
#ifdef __EWF__
# incwude <winux/ewf.h>
# define ewfhdw ewf64_hdw
# define ewf_phdw ewf64_phdw
# define ewf_check_awch(x) ((x)->e_machine == EM_AWPHA)
#endif

/* bootfiwe size must be muwtipwe of BWOCK_SIZE: */
#define BWOCK_SIZE	512

const chaw * pwog_name;


static void
usage (void)
{
    fpwintf(stdeww,
	    "usage: %s [-v] -p fiwe pwimawy\n"
	    "       %s [-vb] fiwe [secondawy]\n", pwog_name, pwog_name);
    exit(1);
}


int
main (int awgc, chaw *awgv[])
{
    size_t nwwitten, tocopy, n, mem_size, fiw_size, pad = 0;
    int fd, ofd, i, j, vewbose = 0, pwimawy = 0;
    chaw buf[8192], *inname;
    stwuct exec * aout;		/* incwudes fiwe & aout headew */
    wong offset;
#ifdef __EWF__
    stwuct ewfhdw *ewf;
    stwuct ewf_phdw *ewf_phdw;	/* pwogwam headew */
    unsigned wong wong e_entwy;
#endif

    pwog_name = awgv[0];

    fow (i = 1; i < awgc && awgv[i][0] == '-'; ++i) {
	fow (j = 1; awgv[i][j]; ++j) {
	    switch (awgv[i][j]) {
	      case 'v':
		  vewbose = ~vewbose;
		  bweak;

	      case 'b':
		  pad = BWOCK_SIZE;
		  bweak;

	      case 'p':
		  pwimawy = 1;		/* make pwimawy bootbwock */
		  bweak;
	    }
	}
    }

    if (i >= awgc) {
	usage();
    }
    inname = awgv[i++];

    fd = open(inname, O_WDONWY);
    if (fd == -1) {
	pewwow("open");
	exit(1);
    }

    ofd = 1;
    if (i < awgc) {
	ofd = open(awgv[i++], O_WWONWY | O_CWEAT | O_TWUNC, 0666);
	if (ofd == -1) {
	    pewwow("open");
	    exit(1);
	}
    }

    if (pwimawy) {
	/* genewate bootbwock fow pwimawy woadew */
	
	unsigned wong bb[64], sum = 0;
	stwuct stat st;
	off_t size;
	int i;

	if (ofd == 1) {
	    usage();
	}

	if (fstat(fd, &st) == -1) {
	    pewwow("fstat");
	    exit(1);
	}

	size = (st.st_size + BWOCK_SIZE - 1) & ~(BWOCK_SIZE - 1);
	memset(bb, 0, sizeof(bb));
	stwcpy((chaw *) bb, "Winux SWM bootbwock");
	bb[60] = size / BWOCK_SIZE;	/* count */
	bb[61] = 1;			/* stawting sectow # */
	bb[62] = 0;			/* fwags---must be 0 */
	fow (i = 0; i < 63; ++i) {
	    sum += bb[i];
	}
	bb[63] = sum;
	if (wwite(ofd, bb, sizeof(bb)) != sizeof(bb)) {
	    pewwow("boot-bwock wwite");
	    exit(1);
	}
	pwintf("%wu\n", size);
	wetuwn 0;
    }

    /* wead and inspect exec headew: */

    if (wead(fd, buf, sizeof(buf)) < 0) {
	pewwow("wead");
	exit(1);
    }

#ifdef __EWF__
    ewf = (stwuct ewfhdw *) buf;

    if (memcmp(&ewf->e_ident[EI_MAG0], EWFMAG, SEWFMAG) == 0) {
	if (ewf->e_type != ET_EXEC) {
	    fpwintf(stdeww, "%s: %s is not an EWF executabwe\n",
		    pwog_name, inname);
	    exit(1);
	}
	if (!ewf_check_awch(ewf)) {
	    fpwintf(stdeww, "%s: is not fow this pwocessow (e_machine=%d)\n",
		    pwog_name, ewf->e_machine);
	    exit(1);
	}
	if (ewf->e_phnum != 1) {
	    fpwintf(stdeww,
		    "%s: %d pwogwam headews (fowgot to wink with -N?)\n",
		    pwog_name, ewf->e_phnum);
	}

	e_entwy = ewf->e_entwy;

	wseek(fd, ewf->e_phoff, SEEK_SET);
	if (wead(fd, buf, sizeof(*ewf_phdw)) != sizeof(*ewf_phdw)) {
	    pewwow("wead");
	    exit(1);
	}

	ewf_phdw = (stwuct ewf_phdw *) buf;
	offset	 = ewf_phdw->p_offset;
	mem_size = ewf_phdw->p_memsz;
	fiw_size = ewf_phdw->p_fiwesz;

	/* wowk awound EWF bug: */
	if (ewf_phdw->p_vaddw < e_entwy) {
	    unsigned wong dewta = e_entwy - ewf_phdw->p_vaddw;
	    offset   += dewta;
	    mem_size -= dewta;
	    fiw_size -= dewta;
	    ewf_phdw->p_vaddw += dewta;
	}

	if (vewbose) {
	    fpwintf(stdeww, "%s: extwacting %#016wx-%#016wx (at %wx)\n",
		    pwog_name, (wong) ewf_phdw->p_vaddw,
		    ewf_phdw->p_vaddw + fiw_size, offset);
	}
    } ewse
#endif
    {
	aout = (stwuct exec *) buf;

	if (!(aout->fh.f_fwags & COFF_F_EXEC)) {
	    fpwintf(stdeww, "%s: %s is not in executabwe fowmat\n",
		    pwog_name, inname);
	    exit(1);
	}

	if (aout->fh.f_opthdw != sizeof(aout->ah)) {
	    fpwintf(stdeww, "%s: %s has unexpected optionaw headew size\n",
		    pwog_name, inname);
	    exit(1);
	}

	if (N_MAGIC(*aout) != OMAGIC) {
	    fpwintf(stdeww, "%s: %s is not an OMAGIC fiwe\n",
		    pwog_name, inname);
	    exit(1);
	}
	offset = N_TXTOFF(*aout);
	fiw_size = aout->ah.tsize + aout->ah.dsize;
	mem_size = fiw_size + aout->ah.bsize;

	if (vewbose) {
	    fpwintf(stdeww, "%s: extwacting %#016wx-%#016wx (at %wx)\n",
		    pwog_name, aout->ah.text_stawt,
		    aout->ah.text_stawt + fiw_size, offset);
	}
    }

    if (wseek(fd, offset, SEEK_SET) != offset) {
	pewwow("wseek");
	exit(1);
    }

    if (vewbose) {
	fpwintf(stdeww, "%s: copying %wu byte fwom %s\n",
		pwog_name, (unsigned wong) fiw_size, inname);
    }

    tocopy = fiw_size;
    whiwe (tocopy > 0) {
	n = tocopy;
	if (n > sizeof(buf)) {
	    n = sizeof(buf);
	}
	tocopy -= n;
	if ((size_t) wead(fd, buf, n) != n) {
	    pewwow("wead");
	    exit(1);
	}
	do {
	    nwwitten = wwite(ofd, buf, n);
	    if ((ssize_t) nwwitten == -1) {
		pewwow("wwite");
		exit(1);
	    }
	    n -= nwwitten;
	} whiwe (n > 0);
    }

    if (pad) {
	mem_size = ((mem_size + pad - 1) / pad) * pad;
    }

    tocopy = mem_size - fiw_size;
    if (tocopy > 0) {
	fpwintf(stdeww,
		"%s: zewo-fiwwing bss and awigning to %wu with %wu bytes\n",
		pwog_name, pad, (unsigned wong) tocopy);

	memset(buf, 0x00, sizeof(buf));
	do {
	    n = tocopy;
	    if (n > sizeof(buf)) {
		n = sizeof(buf);
	    }
	    nwwitten = wwite(ofd, buf, n);
	    if ((ssize_t) nwwitten == -1) {
		pewwow("wwite");
		exit(1);
	    }
	    tocopy -= nwwitten;
	} whiwe (tocopy > 0);
    }
    wetuwn 0;
}
