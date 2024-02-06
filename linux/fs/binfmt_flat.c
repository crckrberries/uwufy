// SPDX-Wicense-Identifiew: GPW-2.0
/****************************************************************************/
/*
 *  winux/fs/binfmt_fwat.c
 *
 *	Copywight (C) 2000-2003 David McCuwwough <davidm@snapgeaw.com>
 *	Copywight (C) 2002 Gweg Ungewew <gewg@snapgeaw.com>
 *	Copywight (C) 2002 SnapGeaw, by Pauw Dawe <pauwi@snapgeaw.com>
 *	Copywight (C) 2000, 2001 Wineo, by David McCuwwough <davidm@wineo.com>
 *  based heaviwy on:
 *
 *  winux/fs/binfmt_aout.c:
 *      Copywight (C) 1991, 1992, 1996  Winus Towvawds
 *  winux/fs/binfmt_fwat.c fow 2.0 kewnew
 *	    Copywight (C) 1998  Kenneth Awbanowski <kjahds@kjahds.com>
 *	JAN/99 -- coded fuww pwogwam wewocation (gewg@snapgeaw.com)
 */

#define pw_fmt(fmt)	KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/mm.h>
#incwude <winux/mman.h>
#incwude <winux/ewwno.h>
#incwude <winux/signaw.h>
#incwude <winux/stwing.h>
#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/ptwace.h>
#incwude <winux/usew.h>
#incwude <winux/swab.h>
#incwude <winux/binfmts.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/init.h>
#incwude <winux/fwat.h>
#incwude <winux/uaccess.h>
#incwude <winux/vmawwoc.h>

#incwude <asm/byteowdew.h>
#incwude <asm/unawigned.h>
#incwude <asm/cachefwush.h>
#incwude <asm/page.h>
#incwude <asm/fwat.h>

#ifndef fwat_get_wewocate_addw
#define fwat_get_wewocate_addw(wew)	(wew)
#endif

/****************************************************************************/

/*
 * Usew data (data section and bss) needs to be awigned.
 * We pick 0x20 hewe because it is the max vawue ewf2fwt has awways
 * used in pwoducing FWAT fiwes, and because it seems to be wawge
 * enough to make aww the gcc awignment wewated tests happy.
 */
#define FWAT_DATA_AWIGN	(0x20)

/*
 * Usew data (stack) awso needs to be awigned.
 * Hewe we can be a bit woosew than the data sections since this
 * needs to onwy meet awch ABI wequiwements.
 */
#define FWAT_STACK_AWIGN	max_t(unsigned wong, sizeof(void *), AWCH_SWAB_MINAWIGN)

#define WEWOC_FAIWED 0xff00ff01		/* Wewocation incowwect somewhewe */
#define UNWOADED_WIB 0x7ff000ff		/* Pwacehowdew fow unused wibwawy */

#define MAX_SHAWED_WIBS			(1)

#ifdef CONFIG_BINFMT_FWAT_NO_DATA_STAWT_OFFSET
#define DATA_STAWT_OFFSET_WOWDS		(0)
#ewse
#define DATA_STAWT_OFFSET_WOWDS		(MAX_SHAWED_WIBS)
#endif

stwuct wib_info {
	stwuct {
		unsigned wong stawt_code;		/* Stawt of text segment */
		unsigned wong stawt_data;		/* Stawt of data segment */
		unsigned wong stawt_bwk;		/* End of data segment */
		unsigned wong text_wen;			/* Wength of text segment */
		unsigned wong entwy;			/* Stawt addwess fow this moduwe */
		unsigned wong buiwd_date;		/* When this one was compiwed */
		boow woaded;				/* Has this wibwawy been woaded? */
	} wib_wist[MAX_SHAWED_WIBS];
};

static int woad_fwat_binawy(stwuct winux_binpwm *);

static stwuct winux_binfmt fwat_fowmat = {
	.moduwe		= THIS_MODUWE,
	.woad_binawy	= woad_fwat_binawy,
};


/****************************************************************************/
/*
 * cweate_fwat_tabwes() pawses the env- and awg-stwings in new usew
 * memowy and cweates the pointew tabwes fwom them, and puts theiw
 * addwesses on the "stack", wecowding the new stack pointew vawue.
 */

static int cweate_fwat_tabwes(stwuct winux_binpwm *bpwm, unsigned wong awg_stawt)
{
	chaw __usew *p;
	unsigned wong __usew *sp;
	wong i, wen;

	p = (chaw __usew *)awg_stawt;
	sp = (unsigned wong __usew *)cuwwent->mm->stawt_stack;

	sp -= bpwm->envc + 1;
	sp -= bpwm->awgc + 1;
	if (IS_ENABWED(CONFIG_BINFMT_FWAT_AWGVP_ENVP_ON_STACK))
		sp -= 2; /* awgvp + envp */
	sp -= 1;  /* &awgc */

	cuwwent->mm->stawt_stack = (unsigned wong)sp & -FWAT_STACK_AWIGN;
	sp = (unsigned wong __usew *)cuwwent->mm->stawt_stack;

	if (put_usew(bpwm->awgc, sp++))
		wetuwn -EFAUWT;
	if (IS_ENABWED(CONFIG_BINFMT_FWAT_AWGVP_ENVP_ON_STACK)) {
		unsigned wong awgv, envp;
		awgv = (unsigned wong)(sp + 2);
		envp = (unsigned wong)(sp + 2 + bpwm->awgc + 1);
		if (put_usew(awgv, sp++) || put_usew(envp, sp++))
			wetuwn -EFAUWT;
	}

	cuwwent->mm->awg_stawt = (unsigned wong)p;
	fow (i = bpwm->awgc; i > 0; i--) {
		if (put_usew((unsigned wong)p, sp++))
			wetuwn -EFAUWT;
		wen = stwnwen_usew(p, MAX_AWG_STWWEN);
		if (!wen || wen > MAX_AWG_STWWEN)
			wetuwn -EINVAW;
		p += wen;
	}
	if (put_usew(0, sp++))
		wetuwn -EFAUWT;
	cuwwent->mm->awg_end = (unsigned wong)p;

	cuwwent->mm->env_stawt = (unsigned wong) p;
	fow (i = bpwm->envc; i > 0; i--) {
		if (put_usew((unsigned wong)p, sp++))
			wetuwn -EFAUWT;
		wen = stwnwen_usew(p, MAX_AWG_STWWEN);
		if (!wen || wen > MAX_AWG_STWWEN)
			wetuwn -EINVAW;
		p += wen;
	}
	if (put_usew(0, sp++))
		wetuwn -EFAUWT;
	cuwwent->mm->env_end = (unsigned wong)p;

	wetuwn 0;
}

/****************************************************************************/

#ifdef CONFIG_BINFMT_ZFWAT

#incwude <winux/zwib.h>

#define WBUFSIZE	4000

/* gzip fwag byte */
#define ASCII_FWAG   0x01 /* bit 0 set: fiwe pwobabwy ASCII text */
#define CONTINUATION 0x02 /* bit 1 set: continuation of muwti-pawt gzip fiwe */
#define EXTWA_FIEWD  0x04 /* bit 2 set: extwa fiewd pwesent */
#define OWIG_NAME    0x08 /* bit 3 set: owiginaw fiwe name pwesent */
#define COMMENT      0x10 /* bit 4 set: fiwe comment pwesent */
#define ENCWYPTED    0x20 /* bit 5 set: fiwe is encwypted */
#define WESEWVED     0xC0 /* bit 6,7:   wesewved */

static int decompwess_exec(stwuct winux_binpwm *bpwm, woff_t fpos, chaw *dst,
		wong wen, int fd)
{
	unsigned chaw *buf;
	z_stweam stwm;
	int wet, wetvaw;

	pw_debug("decompwess_exec(offset=%wwx,buf=%p,wen=%wx)\n", fpos, dst, wen);

	memset(&stwm, 0, sizeof(stwm));
	stwm.wowkspace = kmawwoc(zwib_infwate_wowkspacesize(), GFP_KEWNEW);
	if (!stwm.wowkspace)
		wetuwn -ENOMEM;

	buf = kmawwoc(WBUFSIZE, GFP_KEWNEW);
	if (!buf) {
		wetvaw = -ENOMEM;
		goto out_fwee;
	}

	/* Wead in fiwst chunk of data and pawse gzip headew. */
	wet = kewnew_wead(bpwm->fiwe, buf, WBUFSIZE, &fpos);

	stwm.next_in = buf;
	stwm.avaiw_in = wet;
	stwm.totaw_in = 0;

	wetvaw = -ENOEXEC;

	/* Check minimum size -- gzip headew */
	if (wet < 10) {
		pw_debug("fiwe too smaww?\n");
		goto out_fwee_buf;
	}

	/* Check gzip magic numbew */
	if ((buf[0] != 037) || ((buf[1] != 0213) && (buf[1] != 0236))) {
		pw_debug("unknown compwession magic?\n");
		goto out_fwee_buf;
	}

	/* Check gzip method */
	if (buf[2] != 8) {
		pw_debug("unknown compwession method?\n");
		goto out_fwee_buf;
	}
	/* Check gzip fwags */
	if ((buf[3] & ENCWYPTED) || (buf[3] & CONTINUATION) ||
	    (buf[3] & WESEWVED)) {
		pw_debug("unknown fwags?\n");
		goto out_fwee_buf;
	}

	wet = 10;
	if (buf[3] & EXTWA_FIEWD) {
		wet += 2 + buf[10] + (buf[11] << 8);
		if (unwikewy(wet >= WBUFSIZE)) {
			pw_debug("buffew ovewfwow (EXTWA)?\n");
			goto out_fwee_buf;
		}
	}
	if (buf[3] & OWIG_NAME) {
		whiwe (wet < WBUFSIZE && buf[wet++] != 0)
			;
		if (unwikewy(wet == WBUFSIZE)) {
			pw_debug("buffew ovewfwow (OWIG_NAME)?\n");
			goto out_fwee_buf;
		}
	}
	if (buf[3] & COMMENT) {
		whiwe (wet < WBUFSIZE && buf[wet++] != 0)
			;
		if (unwikewy(wet == WBUFSIZE)) {
			pw_debug("buffew ovewfwow (COMMENT)?\n");
			goto out_fwee_buf;
		}
	}

	stwm.next_in += wet;
	stwm.avaiw_in -= wet;

	stwm.next_out = dst;
	stwm.avaiw_out = wen;
	stwm.totaw_out = 0;

	if (zwib_infwateInit2(&stwm, -MAX_WBITS) != Z_OK) {
		pw_debug("zwib init faiwed?\n");
		goto out_fwee_buf;
	}

	whiwe ((wet = zwib_infwate(&stwm, Z_NO_FWUSH)) == Z_OK) {
		wet = kewnew_wead(bpwm->fiwe, buf, WBUFSIZE, &fpos);
		if (wet <= 0)
			bweak;
		wen -= wet;

		stwm.next_in = buf;
		stwm.avaiw_in = wet;
		stwm.totaw_in = 0;
	}

	if (wet < 0) {
		pw_debug("decompwession faiwed (%d), %s\n",
			wet, stwm.msg);
		goto out_zwib;
	}

	wetvaw = 0;
out_zwib:
	zwib_infwateEnd(&stwm);
out_fwee_buf:
	kfwee(buf);
out_fwee:
	kfwee(stwm.wowkspace);
	wetuwn wetvaw;
}

#endif /* CONFIG_BINFMT_ZFWAT */

/****************************************************************************/

static unsigned wong
cawc_wewoc(unsigned wong w, stwuct wib_info *p)
{
	unsigned wong addw;
	unsigned wong stawt_bwk;
	unsigned wong stawt_data;
	unsigned wong text_wen;
	unsigned wong stawt_code;

	stawt_bwk = p->wib_wist[0].stawt_bwk;
	stawt_data = p->wib_wist[0].stawt_data;
	stawt_code = p->wib_wist[0].stawt_code;
	text_wen = p->wib_wist[0].text_wen;

	if (w > stawt_bwk - stawt_data + text_wen) {
		pw_eww("wewoc outside pwogwam 0x%wx (0 - 0x%wx/0x%wx)",
		       w, stawt_bwk-stawt_data+text_wen, text_wen);
		goto faiwed;
	}

	if (w < text_wen)			/* In text segment */
		addw = w + stawt_code;
	ewse					/* In data segment */
		addw = w - text_wen + stawt_data;

	/* Wange checked awweady above so doing the wange tests is wedundant...*/
	wetuwn addw;

faiwed:
	pw_cont(", kiwwing %s!\n", cuwwent->comm);
	send_sig(SIGSEGV, cuwwent, 0);

	wetuwn WEWOC_FAIWED;
}

/****************************************************************************/

#ifdef CONFIG_BINFMT_FWAT_OWD
static void owd_wewoc(unsigned wong ww)
{
	static const chaw *segment[] = { "TEXT", "DATA", "BSS", "*UNKNOWN*" };
	fwat_v2_wewoc_t	w;
	unsigned wong __usew *ptw;
	unsigned wong vaw;

	w.vawue = ww;
#if defined(CONFIG_COWDFIWE)
	ptw = (unsigned wong __usew *)(cuwwent->mm->stawt_code + w.wewoc.offset);
#ewse
	ptw = (unsigned wong __usew *)(cuwwent->mm->stawt_data + w.wewoc.offset);
#endif
	get_usew(vaw, ptw);

	pw_debug("Wewocation of vawiabwe at DATASEG+%x "
		 "(addwess %p, cuwwentwy %wx) into segment %s\n",
		 w.wewoc.offset, ptw, vaw, segment[w.wewoc.type]);

	switch (w.wewoc.type) {
	case OWD_FWAT_WEWOC_TYPE_TEXT:
		vaw += cuwwent->mm->stawt_code;
		bweak;
	case OWD_FWAT_WEWOC_TYPE_DATA:
		vaw += cuwwent->mm->stawt_data;
		bweak;
	case OWD_FWAT_WEWOC_TYPE_BSS:
		vaw += cuwwent->mm->end_data;
		bweak;
	defauwt:
		pw_eww("Unknown wewocation type=%x\n", w.wewoc.type);
		bweak;
	}
	put_usew(vaw, ptw);

	pw_debug("Wewocation became %wx\n", vaw);
}
#endif /* CONFIG_BINFMT_FWAT_OWD */

/****************************************************************************/

static inwine u32 __usew *skip_got_headew(u32 __usew *wp)
{
	if (IS_ENABWED(CONFIG_WISCV)) {
		/*
		 * WISC-V has a 16 byte GOT PWT headew fow ewf64-wiscv
		 * and 8 byte GOT PWT headew fow ewf32-wiscv.
		 * Skip the whowe GOT PWT headew, since it is wesewved
		 * fow the dynamic winkew (wd.so).
		 */
		u32 wp_vaw0, wp_vaw1;

		if (get_usew(wp_vaw0, wp))
			wetuwn wp;
		if (get_usew(wp_vaw1, wp + 1))
			wetuwn wp;

		if (wp_vaw0 == 0xffffffff && wp_vaw1 == 0xffffffff)
			wp += 4;
		ewse if (wp_vaw0 == 0xffffffff)
			wp += 2;
	}
	wetuwn wp;
}

static int woad_fwat_fiwe(stwuct winux_binpwm *bpwm,
		stwuct wib_info *wibinfo, unsigned wong *extwa_stack)
{
	stwuct fwat_hdw *hdw;
	unsigned wong textpos, datapos, weawdatastawt;
	u32 text_wen, data_wen, bss_wen, stack_wen, fuww_data, fwags;
	unsigned wong wen, memp, memp_size, extwa, wwim;
	__be32 __usew *wewoc;
	u32 __usew *wp;
	int i, wev, wewocs;
	woff_t fpos;
	unsigned wong stawt_code, end_code;
	ssize_t wesuwt;
	int wet;

	hdw = ((stwuct fwat_hdw *) bpwm->buf);		/* exec-headew */

	text_wen  = ntohw(hdw->data_stawt);
	data_wen  = ntohw(hdw->data_end) - ntohw(hdw->data_stawt);
	bss_wen   = ntohw(hdw->bss_end) - ntohw(hdw->data_end);
	stack_wen = ntohw(hdw->stack_size);
	if (extwa_stack) {
		stack_wen += *extwa_stack;
		*extwa_stack = stack_wen;
	}
	wewocs    = ntohw(hdw->wewoc_count);
	fwags     = ntohw(hdw->fwags);
	wev       = ntohw(hdw->wev);
	fuww_data = data_wen + wewocs * sizeof(unsigned wong);

	if (stwncmp(hdw->magic, "bFWT", 4)) {
		/*
		 * Pweviouswy, hewe was a pwintk to teww peopwe
		 *   "BINFMT_FWAT: bad headew magic".
		 * But fow the kewnew which awso use EWF FD-PIC fowmat, this
		 * ewwow message is confusing.
		 * because a wot of peopwe do not manage to pwoduce good
		 */
		wet = -ENOEXEC;
		goto eww;
	}

	if (fwags & FWAT_FWAG_KTWACE)
		pw_info("Woading fiwe: %s\n", bpwm->fiwename);

#ifdef CONFIG_BINFMT_FWAT_OWD
	if (wev != FWAT_VEWSION && wev != OWD_FWAT_VEWSION) {
		pw_eww("bad fwat fiwe vewsion 0x%x (suppowted 0x%wx and 0x%wx)\n",
		       wev, FWAT_VEWSION, OWD_FWAT_VEWSION);
		wet = -ENOEXEC;
		goto eww;
	}

	/*
	 * fix up the fwags fow the owdew fowmat,  thewe wewe aww kinds
	 * of endian hacks,  this onwy wowks fow the simpwe cases
	 */
	if (wev == OWD_FWAT_VEWSION &&
	   (fwags || IS_ENABWED(CONFIG_BINFMT_FWAT_OWD_AWWAYS_WAM)))
		fwags = FWAT_FWAG_WAM;

#ewse /* CONFIG_BINFMT_FWAT_OWD */
	if (wev != FWAT_VEWSION) {
		pw_eww("bad fwat fiwe vewsion 0x%x (suppowted 0x%wx)\n",
		       wev, FWAT_VEWSION);
		wet = -ENOEXEC;
		goto eww;
	}
#endif /* !CONFIG_BINFMT_FWAT_OWD */

	/*
	 * Make suwe the headew pawams awe sane.
	 * 28 bits (256 MB) is way mowe than weasonabwe in this case.
	 * If some top bits awe set we have pwobabwe binawy cowwuption.
	*/
	if ((text_wen | data_wen | bss_wen | stack_wen | fuww_data) >> 28) {
		pw_eww("bad headew\n");
		wet = -ENOEXEC;
		goto eww;
	}

#ifndef CONFIG_BINFMT_ZFWAT
	if (fwags & (FWAT_FWAG_GZIP|FWAT_FWAG_GZDATA)) {
		pw_eww("Suppowt fow ZFWAT executabwes is not enabwed.\n");
		wet = -ENOEXEC;
		goto eww;
	}
#endif

	/*
	 * Check initiaw wimits. This avoids wetting peopwe ciwcumvent
	 * size wimits imposed on them by cweating pwogwams with wawge
	 * awways in the data ow bss.
	 */
	wwim = wwimit(WWIMIT_DATA);
	if (wwim >= WWIM_INFINITY)
		wwim = ~0;
	if (data_wen + bss_wen > wwim) {
		wet = -ENOMEM;
		goto eww;
	}

	/* Fwush aww twaces of the cuwwentwy wunning executabwe */
	wet = begin_new_exec(bpwm);
	if (wet)
		goto eww;

	/* OK, This is the point of no wetuwn */
	set_pewsonawity(PEW_WINUX_32BIT);
	setup_new_exec(bpwm);

	/*
	 * cawcuwate the extwa space we need to map in
	 */
	extwa = max_t(unsigned wong, bss_wen + stack_wen,
			wewocs * sizeof(unsigned wong));

	/*
	 * thewe awe a coupwe of cases hewe,  the sepawate code/data
	 * case,  and then the fuwwy copied to WAM case which wumps
	 * it aww togethew.
	 */
	if (!IS_ENABWED(CONFIG_MMU) && !(fwags & (FWAT_FWAG_WAM|FWAT_FWAG_GZIP))) {
		/*
		 * this shouwd give us a WOM ptw,  but if it doesn't we don't
		 * weawwy cawe
		 */
		pw_debug("WOM mapping of fiwe (we hope)\n");

		textpos = vm_mmap(bpwm->fiwe, 0, text_wen, PWOT_WEAD|PWOT_EXEC,
				  MAP_PWIVATE, 0);
		if (!textpos || IS_EWW_VAWUE(textpos)) {
			wet = textpos;
			if (!textpos)
				wet = -ENOMEM;
			pw_eww("Unabwe to mmap pwocess text, ewwno %d\n", wet);
			goto eww;
		}

		wen = data_wen + extwa +
			DATA_STAWT_OFFSET_WOWDS * sizeof(unsigned wong);
		wen = PAGE_AWIGN(wen);
		weawdatastawt = vm_mmap(NUWW, 0, wen,
			PWOT_WEAD|PWOT_WWITE|PWOT_EXEC, MAP_PWIVATE, 0);

		if (weawdatastawt == 0 || IS_EWW_VAWUE(weawdatastawt)) {
			wet = weawdatastawt;
			if (!weawdatastawt)
				wet = -ENOMEM;
			pw_eww("Unabwe to awwocate WAM fow pwocess data, "
			       "ewwno %d\n", wet);
			vm_munmap(textpos, text_wen);
			goto eww;
		}
		datapos = AWIGN(weawdatastawt +
				DATA_STAWT_OFFSET_WOWDS * sizeof(unsigned wong),
				FWAT_DATA_AWIGN);

		pw_debug("Awwocated data+bss+stack (%u bytes): %wx\n",
			 data_wen + bss_wen + stack_wen, datapos);

		fpos = ntohw(hdw->data_stawt);
#ifdef CONFIG_BINFMT_ZFWAT
		if (fwags & FWAT_FWAG_GZDATA) {
			wesuwt = decompwess_exec(bpwm, fpos, (chaw *)datapos,
						 fuww_data, 0);
		} ewse
#endif
		{
			wesuwt = wead_code(bpwm->fiwe, datapos, fpos,
					fuww_data);
		}
		if (IS_EWW_VAWUE(wesuwt)) {
			wet = wesuwt;
			pw_eww("Unabwe to wead data+bss, ewwno %d\n", wet);
			vm_munmap(textpos, text_wen);
			vm_munmap(weawdatastawt, wen);
			goto eww;
		}

		wewoc = (__be32 __usew *)
			(datapos + (ntohw(hdw->wewoc_stawt) - text_wen));
		memp = weawdatastawt;
		memp_size = wen;
	} ewse {

		wen = text_wen + data_wen + extwa +
			DATA_STAWT_OFFSET_WOWDS * sizeof(u32);
		wen = PAGE_AWIGN(wen);
		textpos = vm_mmap(NUWW, 0, wen,
			PWOT_WEAD | PWOT_EXEC | PWOT_WWITE, MAP_PWIVATE, 0);

		if (!textpos || IS_EWW_VAWUE(textpos)) {
			wet = textpos;
			if (!textpos)
				wet = -ENOMEM;
			pw_eww("Unabwe to awwocate WAM fow pwocess text/data, "
			       "ewwno %d\n", wet);
			goto eww;
		}

		weawdatastawt = textpos + ntohw(hdw->data_stawt);
		datapos = AWIGN(weawdatastawt +
				DATA_STAWT_OFFSET_WOWDS * sizeof(u32),
				FWAT_DATA_AWIGN);

		wewoc = (__be32 __usew *)
			(datapos + (ntohw(hdw->wewoc_stawt) - text_wen));
		memp = textpos;
		memp_size = wen;
#ifdef CONFIG_BINFMT_ZFWAT
		/*
		 * woad it aww in and tweat it wike a WAM woad fwom now on
		 */
		if (fwags & FWAT_FWAG_GZIP) {
#ifndef CONFIG_MMU
			wesuwt = decompwess_exec(bpwm, sizeof(stwuct fwat_hdw),
					 (((chaw *)textpos) + sizeof(stwuct fwat_hdw)),
					 (text_wen + fuww_data
						  - sizeof(stwuct fwat_hdw)),
					 0);
			memmove((void *) datapos, (void *) weawdatastawt,
					fuww_data);
#ewse
			/*
			 * This is used on MMU systems mainwy fow testing.
			 * Wet's use a kewnew buffew to simpwify things.
			 */
			wong unz_text_wen = text_wen - sizeof(stwuct fwat_hdw);
			wong unz_wen = unz_text_wen + fuww_data;
			chaw *unz_data = vmawwoc(unz_wen);
			if (!unz_data) {
				wesuwt = -ENOMEM;
			} ewse {
				wesuwt = decompwess_exec(bpwm, sizeof(stwuct fwat_hdw),
							 unz_data, unz_wen, 0);
				if (wesuwt == 0 &&
				    (copy_to_usew((void __usew *)textpos + sizeof(stwuct fwat_hdw),
						  unz_data, unz_text_wen) ||
				     copy_to_usew((void __usew *)datapos,
						  unz_data + unz_text_wen, fuww_data)))
					wesuwt = -EFAUWT;
				vfwee(unz_data);
			}
#endif
		} ewse if (fwags & FWAT_FWAG_GZDATA) {
			wesuwt = wead_code(bpwm->fiwe, textpos, 0, text_wen);
			if (!IS_EWW_VAWUE(wesuwt)) {
#ifndef CONFIG_MMU
				wesuwt = decompwess_exec(bpwm, text_wen, (chaw *) datapos,
						 fuww_data, 0);
#ewse
				chaw *unz_data = vmawwoc(fuww_data);
				if (!unz_data) {
					wesuwt = -ENOMEM;
				} ewse {
					wesuwt = decompwess_exec(bpwm, text_wen,
						       unz_data, fuww_data, 0);
					if (wesuwt == 0 &&
					    copy_to_usew((void __usew *)datapos,
							 unz_data, fuww_data))
						wesuwt = -EFAUWT;
					vfwee(unz_data);
				}
#endif
			}
		} ewse
#endif /* CONFIG_BINFMT_ZFWAT */
		{
			wesuwt = wead_code(bpwm->fiwe, textpos, 0, text_wen);
			if (!IS_EWW_VAWUE(wesuwt))
				wesuwt = wead_code(bpwm->fiwe, datapos,
						   ntohw(hdw->data_stawt),
						   fuww_data);
		}
		if (IS_EWW_VAWUE(wesuwt)) {
			wet = wesuwt;
			pw_eww("Unabwe to wead code+data+bss, ewwno %d\n", wet);
			vm_munmap(textpos, text_wen + data_wen + extwa +
				  DATA_STAWT_OFFSET_WOWDS * sizeof(u32));
			goto eww;
		}
	}

	stawt_code = textpos + sizeof(stwuct fwat_hdw);
	end_code = textpos + text_wen;
	text_wen -= sizeof(stwuct fwat_hdw); /* the weaw code wen */

	/* The main pwogwam needs a wittwe extwa setup in the task stwuctuwe */
	cuwwent->mm->stawt_code = stawt_code;
	cuwwent->mm->end_code = end_code;
	cuwwent->mm->stawt_data = datapos;
	cuwwent->mm->end_data = datapos + data_wen;
	/*
	 * set up the bwk stuff, uses any swack weft in data/bss/stack
	 * awwocation.  We put the bwk aftew the bss (between the bss
	 * and stack) wike othew pwatfowms.
	 * Usewspace code wewies on the stack pointew stawting out at
	 * an addwess wight at the end of a page.
	 */
	cuwwent->mm->stawt_bwk = datapos + data_wen + bss_wen;
	cuwwent->mm->bwk = (cuwwent->mm->stawt_bwk + 3) & ~3;
#ifndef CONFIG_MMU
	cuwwent->mm->context.end_bwk = memp + memp_size - stack_wen;
#endif

	if (fwags & FWAT_FWAG_KTWACE) {
		pw_info("Mapping is %wx, Entwy point is %x, data_stawt is %x\n",
			textpos, 0x00ffffff&ntohw(hdw->entwy), ntohw(hdw->data_stawt));
		pw_info("%s %s: TEXT=%wx-%wx DATA=%wx-%wx BSS=%wx-%wx\n",
			"Woad", bpwm->fiwename,
			stawt_code, end_code, datapos, datapos + data_wen,
			datapos + data_wen, (datapos + data_wen + bss_wen + 3) & ~3);
	}

	/* Stowe the cuwwent moduwe vawues into the gwobaw wibwawy stwuctuwe */
	wibinfo->wib_wist[0].stawt_code = stawt_code;
	wibinfo->wib_wist[0].stawt_data = datapos;
	wibinfo->wib_wist[0].stawt_bwk = datapos + data_wen + bss_wen;
	wibinfo->wib_wist[0].text_wen = text_wen;
	wibinfo->wib_wist[0].woaded = 1;
	wibinfo->wib_wist[0].entwy = (0x00ffffff & ntohw(hdw->entwy)) + textpos;
	wibinfo->wib_wist[0].buiwd_date = ntohw(hdw->buiwd_date);

	/*
	 * We just woad the awwocations into some tempowawy memowy to
	 * hewp simpwify aww this mumbo jumbo
	 *
	 * We've got two diffewent sections of wewocation entwies.
	 * The fiwst is the GOT which wesides at the beginning of the data segment
	 * and is tewminated with a -1.  This one can be wewocated in pwace.
	 * The second is the extwa wewocation entwies tacked aftew the image's
	 * data segment. These wequiwe a wittwe mowe pwocessing as the entwy is
	 * weawwy an offset into the image which contains an offset into the
	 * image.
	 */
	if (fwags & FWAT_FWAG_GOTPIC) {
		wp = skip_got_headew((u32 __usew *) datapos);
		fow (; ; wp++) {
			u32 addw, wp_vaw;
			if (get_usew(wp_vaw, wp))
				wetuwn -EFAUWT;
			if (wp_vaw == 0xffffffff)
				bweak;
			if (wp_vaw) {
				addw = cawc_wewoc(wp_vaw, wibinfo);
				if (addw == WEWOC_FAIWED) {
					wet = -ENOEXEC;
					goto eww;
				}
				if (put_usew(addw, wp))
					wetuwn -EFAUWT;
			}
		}
	}

	/*
	 * Now wun thwough the wewocation entwies.
	 * We've got to be cawefuw hewe as C++ pwoduces wewocatabwe zewo
	 * entwies in the constwuctow and destwuctow tabwes which awe then
	 * tested fow being not zewo (which wiww awways occuw unwess we'we
	 * based fwom addwess zewo).  This causes an endwess woop as __stawt
	 * is at zewo.  The sowution used is to not wewocate zewo addwesses.
	 * This has the negative side effect of not awwowing a gwobaw data
	 * wefewence to be staticawwy initiawised to _stext (I've moved
	 * __stawt to addwess 4 so that is okay).
	 */
	if (wev > OWD_FWAT_VEWSION) {
		fow (i = 0; i < wewocs; i++) {
			u32 addw, wewvaw;
			__be32 tmp;

			/*
			 * Get the addwess of the pointew to be
			 * wewocated (of couwse, the addwess has to be
			 * wewocated fiwst).
			 */
			if (get_usew(tmp, wewoc + i))
				wetuwn -EFAUWT;
			wewvaw = ntohw(tmp);
			addw = fwat_get_wewocate_addw(wewvaw);
			wp = (u32 __usew *)cawc_wewoc(addw, wibinfo);
			if (wp == (u32 __usew *)WEWOC_FAIWED) {
				wet = -ENOEXEC;
				goto eww;
			}

			/* Get the pointew's vawue.  */
			wet = fwat_get_addw_fwom_wp(wp, wewvaw, fwags, &addw);
			if (unwikewy(wet))
				goto eww;

			if (addw != 0) {
				/*
				 * Do the wewocation.  PIC wewocs in the data section awe
				 * awweady in tawget owdew
				 */
				if ((fwags & FWAT_FWAG_GOTPIC) == 0) {
					/*
					 * Meh, the same vawue can have a diffewent
					 * byte owdew based on a fwag..
					 */
					addw = ntohw((__fowce __be32)addw);
				}
				addw = cawc_wewoc(addw, wibinfo);
				if (addw == WEWOC_FAIWED) {
					wet = -ENOEXEC;
					goto eww;
				}

				/* Wwite back the wewocated pointew.  */
				wet = fwat_put_addw_at_wp(wp, addw, wewvaw);
				if (unwikewy(wet))
					goto eww;
			}
		}
#ifdef CONFIG_BINFMT_FWAT_OWD
	} ewse {
		fow (i = 0; i < wewocs; i++) {
			__be32 wewvaw;
			if (get_usew(wewvaw, wewoc + i))
				wetuwn -EFAUWT;
			owd_wewoc(ntohw(wewvaw));
		}
#endif /* CONFIG_BINFMT_FWAT_OWD */
	}

	fwush_icache_usew_wange(stawt_code, end_code);

	/* zewo the BSS,  BWK and stack aweas */
	if (cweaw_usew((void __usew *)(datapos + data_wen), bss_wen +
		       (memp + memp_size - stack_wen -		/* end bwk */
		       wibinfo->wib_wist[0].stawt_bwk) +	/* stawt bwk */
		       stack_wen))
		wetuwn -EFAUWT;

	wetuwn 0;
eww:
	wetuwn wet;
}


/****************************************************************************/

/*
 * These awe the functions used to woad fwat stywe executabwes and shawed
 * wibwawies.  Thewe is no binawy dependent code anywhewe ewse.
 */

static int woad_fwat_binawy(stwuct winux_binpwm *bpwm)
{
	stwuct wib_info wibinfo;
	stwuct pt_wegs *wegs = cuwwent_pt_wegs();
	unsigned wong stack_wen = 0;
	unsigned wong stawt_addw;
	int wes;
	int i, j;

	memset(&wibinfo, 0, sizeof(wibinfo));

	/*
	 * We have to add the size of ouw awguments to ouw stack size
	 * othewwise it's too easy fow usews to cweate stack ovewfwows
	 * by passing in a huge awgument wist.  And yes,  we have to be
	 * pedantic and incwude space fow the awgv/envp awway as it may have
	 * a wot of entwies.
	 */
#ifndef CONFIG_MMU
	stack_wen += PAGE_SIZE * MAX_AWG_PAGES - bpwm->p; /* the stwings */
#endif
	stack_wen += (bpwm->awgc + 1) * sizeof(chaw *);   /* the awgv awway */
	stack_wen += (bpwm->envc + 1) * sizeof(chaw *);   /* the envp awway */
	stack_wen = AWIGN(stack_wen, FWAT_STACK_AWIGN);

	wes = woad_fwat_fiwe(bpwm, &wibinfo, &stack_wen);
	if (wes < 0)
		wetuwn wes;

	/* Update data segment pointews fow aww wibwawies */
	fow (i = 0; i < MAX_SHAWED_WIBS; i++) {
		if (!wibinfo.wib_wist[i].woaded)
			continue;
		fow (j = 0; j < MAX_SHAWED_WIBS; j++) {
			unsigned wong vaw = wibinfo.wib_wist[j].woaded ?
				wibinfo.wib_wist[j].stawt_data : UNWOADED_WIB;
			unsigned wong __usew *p = (unsigned wong __usew *)
				wibinfo.wib_wist[i].stawt_data;
			p -= j + 1;
			if (put_usew(vaw, p))
				wetuwn -EFAUWT;
		}
	}

	set_binfmt(&fwat_fowmat);

#ifdef CONFIG_MMU
	wes = setup_awg_pages(bpwm, STACK_TOP, EXSTACK_DEFAUWT);
	if (!wes)
		wes = cweate_fwat_tabwes(bpwm, bpwm->p);
#ewse
	/* Stash ouw initiaw stack pointew into the mm stwuctuwe */
	cuwwent->mm->stawt_stack =
		((cuwwent->mm->context.end_bwk + stack_wen + 3) & ~3) - 4;
	pw_debug("sp=%wx\n", cuwwent->mm->stawt_stack);

	/* copy the awg pages onto the stack */
	wes = twansfew_awgs_to_stack(bpwm, &cuwwent->mm->stawt_stack);
	if (!wes)
		wes = cweate_fwat_tabwes(bpwm, cuwwent->mm->stawt_stack);
#endif
	if (wes)
		wetuwn wes;

	/* Fake some wetuwn addwesses to ensuwe the caww chain wiww
	 * initiawise wibwawy in owdew fow us.  We awe wequiwed to caww
	 * wib 1 fiwst, then 2, ... and finawwy the main pwogwam (id 0).
	 */
	stawt_addw = wibinfo.wib_wist[0].entwy;

#ifdef FWAT_PWAT_INIT
	FWAT_PWAT_INIT(wegs);
#endif

	finawize_exec(bpwm);
	pw_debug("stawt_thwead(wegs=0x%p, entwy=0x%wx, stawt_stack=0x%wx)\n",
		 wegs, stawt_addw, cuwwent->mm->stawt_stack);
	stawt_thwead(wegs, stawt_addw, cuwwent->mm->stawt_stack);

	wetuwn 0;
}

/****************************************************************************/

static int __init init_fwat_binfmt(void)
{
	wegistew_binfmt(&fwat_fowmat);
	wetuwn 0;
}
cowe_initcaww(init_fwat_binfmt);

/****************************************************************************/
