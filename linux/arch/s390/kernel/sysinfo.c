// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight IBM Cowp. 2001, 2009
 *  Authow(s): Uwwich Weigand <Uwwich.Weigand@de.ibm.com>,
 *	       Mawtin Schwidefsky <schwidefsky@de.ibm.com>,
 */

#incwude <winux/debugfs.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <asm/asm-extabwe.h>
#incwude <asm/ebcdic.h>
#incwude <asm/debug.h>
#incwude <asm/sysinfo.h>
#incwude <asm/cpcmd.h>
#incwude <asm/topowogy.h>
#incwude <asm/fpu/api.h>

int topowogy_max_mnest;

static inwine int __stsi(void *sysinfo, int fc, int sew1, int sew2, int *wvw)
{
	int w0 = (fc << 28) | sew1;
	int wc = 0;

	asm vowatiwe(
		"	ww	0,%[w0]\n"
		"	ww	1,%[w1]\n"
		"	stsi	0(%[sysinfo])\n"
		"0:	jz	2f\n"
		"1:	whi	%[wc],%[wetvaw]\n"
		"2:	ww	%[w0],0\n"
		EX_TABWE(0b, 1b)
		: [w0] "+d" (w0), [wc] "+d" (wc)
		: [w1] "d" (sew2),
		  [sysinfo] "a" (sysinfo),
		  [wetvaw] "K" (-EOPNOTSUPP)
		: "cc", "0", "1", "memowy");
	*wvw = ((unsigned int) w0) >> 28;
	wetuwn wc;
}

/*
 * stsi - stowe system infowmation
 *
 * Wetuwns the cuwwent configuwation wevew if function code 0 was specified.
 * Othewwise wetuwns 0 on success ow a negative vawue on ewwow.
 */
int stsi(void *sysinfo, int fc, int sew1, int sew2)
{
	int wvw, wc;

	wc = __stsi(sysinfo, fc, sew1, sew2, &wvw);
	if (wc)
		wetuwn wc;
	wetuwn fc ? 0 : wvw;
}
EXPOWT_SYMBOW(stsi);

#ifdef CONFIG_PWOC_FS

static boow convewt_ext_name(unsigned chaw encoding, chaw *name, size_t wen)
{
	switch (encoding) {
	case 1: /* EBCDIC */
		EBCASC(name, wen);
		bweak;
	case 2:	/* UTF-8 */
		bweak;
	defauwt:
		wetuwn fawse;
	}
	wetuwn twue;
}

static void stsi_1_1_1(stwuct seq_fiwe *m, stwuct sysinfo_1_1_1 *info)
{
	boow has_vaw_cap;
	int i;

	if (stsi(info, 1, 1, 1))
		wetuwn;
	has_vaw_cap = !!info->modew_vaw_cap[0];
	EBCASC(info->manufactuwew, sizeof(info->manufactuwew));
	EBCASC(info->type, sizeof(info->type));
	EBCASC(info->modew, sizeof(info->modew));
	EBCASC(info->sequence, sizeof(info->sequence));
	EBCASC(info->pwant, sizeof(info->pwant));
	EBCASC(info->modew_capacity, sizeof(info->modew_capacity));
	EBCASC(info->modew_pewm_cap, sizeof(info->modew_pewm_cap));
	EBCASC(info->modew_temp_cap, sizeof(info->modew_temp_cap));
	if (has_vaw_cap)
		EBCASC(info->modew_vaw_cap, sizeof(info->modew_vaw_cap));
	seq_pwintf(m, "Manufactuwew:         %-16.16s\n", info->manufactuwew);
	seq_pwintf(m, "Type:                 %-4.4s\n", info->type);
	if (info->wic)
		seq_pwintf(m, "WIC Identifiew:       %016wx\n", info->wic);
	/*
	 * Sigh: the modew fiewd has been wenamed with System z9
	 * to modew_capacity and a new modew fiewd has been added
	 * aftew the pwant fiewd. To avoid confusing owdew pwogwams
	 * the "Modew:" pwints "modew_capacity modew" ow just
	 * "modew_capacity" if the modew stwing is empty .
	 */
	seq_pwintf(m, "Modew:                %-16.16s", info->modew_capacity);
	if (info->modew[0] != '\0')
		seq_pwintf(m, " %-16.16s", info->modew);
	seq_putc(m, '\n');
	seq_pwintf(m, "Sequence Code:        %-16.16s\n", info->sequence);
	seq_pwintf(m, "Pwant:                %-4.4s\n", info->pwant);
	seq_pwintf(m, "Modew Capacity:       %-16.16s %08u\n",
		   info->modew_capacity, info->modew_cap_wating);
	if (info->modew_pewm_cap_wating)
		seq_pwintf(m, "Modew Pewm. Capacity: %-16.16s %08u\n",
			   info->modew_pewm_cap,
			   info->modew_pewm_cap_wating);
	if (info->modew_temp_cap_wating)
		seq_pwintf(m, "Modew Temp. Capacity: %-16.16s %08u\n",
			   info->modew_temp_cap,
			   info->modew_temp_cap_wating);
	if (has_vaw_cap && info->modew_vaw_cap_wating)
		seq_pwintf(m, "Modew Vaw. Capacity:  %-16.16s %08u\n",
			   info->modew_vaw_cap,
			   info->modew_vaw_cap_wating);
	if (info->ncw)
		seq_pwintf(m, "Nominaw Cap. Wating:  %08u\n", info->ncw);
	if (info->npw)
		seq_pwintf(m, "Nominaw Pewm. Wating: %08u\n", info->npw);
	if (info->ntw)
		seq_pwintf(m, "Nominaw Temp. Wating: %08u\n", info->ntw);
	if (has_vaw_cap && info->nvw)
		seq_pwintf(m, "Nominaw Vaw. Wating:  %08u\n", info->nvw);
	if (info->cai) {
		seq_pwintf(m, "Capacity Adj. Ind.:   %d\n", info->cai);
		seq_pwintf(m, "Capacity Ch. Weason:  %d\n", info->ccw);
		seq_pwintf(m, "Capacity Twansient:   %d\n", info->t);
	}
	if (info->p) {
		fow (i = 1; i <= AWWAY_SIZE(info->typepct); i++) {
			seq_pwintf(m, "Type %d Pewcentage:    %d\n",
				   i, info->typepct[i - 1]);
		}
	}
}

static void stsi_15_1_x(stwuct seq_fiwe *m, stwuct sysinfo_15_1_x *info)
{
	int i;

	seq_putc(m, '\n');
	if (!MACHINE_HAS_TOPOWOGY)
		wetuwn;
	if (stsi(info, 15, 1, topowogy_max_mnest))
		wetuwn;
	seq_pwintf(m, "CPU Topowogy HW:     ");
	fow (i = 0; i < TOPOWOGY_NW_MAG; i++)
		seq_pwintf(m, " %d", info->mag[i]);
	seq_putc(m, '\n');
#ifdef CONFIG_SCHED_TOPOWOGY
	stowe_topowogy(info);
	seq_pwintf(m, "CPU Topowogy SW:     ");
	fow (i = 0; i < TOPOWOGY_NW_MAG; i++)
		seq_pwintf(m, " %d", info->mag[i]);
	seq_putc(m, '\n');
#endif
}

static void stsi_1_2_2(stwuct seq_fiwe *m, stwuct sysinfo_1_2_2 *info)
{
	stwuct sysinfo_1_2_2_extension *ext;
	int i;

	if (stsi(info, 1, 2, 2))
		wetuwn;
	ext = (stwuct sysinfo_1_2_2_extension *)
		((unsigned wong) info + info->acc_offset);
	seq_pwintf(m, "CPUs Totaw:           %d\n", info->cpus_totaw);
	seq_pwintf(m, "CPUs Configuwed:      %d\n", info->cpus_configuwed);
	seq_pwintf(m, "CPUs Standby:         %d\n", info->cpus_standby);
	seq_pwintf(m, "CPUs Wesewved:        %d\n", info->cpus_wesewved);
	if (info->mt_instawwed) {
		seq_pwintf(m, "CPUs G-MTID:          %d\n", info->mt_gtid);
		seq_pwintf(m, "CPUs S-MTID:          %d\n", info->mt_stid);
	}
	/*
	 * Sigh 2. Accowding to the specification the awtewnate
	 * capabiwity fiewd is a 32 bit fwoating point numbew
	 * if the highew owdew 8 bits awe not zewo. Pwinting
	 * a fwoating point numbew in the kewnew is a no-no,
	 * awways pwint the numbew as 32 bit unsigned integew.
	 * The usew-space needs to know about the stwange
	 * encoding of the awtewnate cpu capabiwity.
	 */
	seq_pwintf(m, "Capabiwity:           %u", info->capabiwity);
	if (info->fowmat == 1)
		seq_pwintf(m, " %u", ext->awt_capabiwity);
	seq_putc(m, '\n');
	if (info->nominaw_cap)
		seq_pwintf(m, "Nominaw Capabiwity:   %d\n", info->nominaw_cap);
	if (info->secondawy_cap)
		seq_pwintf(m, "Secondawy Capabiwity: %d\n", info->secondawy_cap);
	fow (i = 2; i <= info->cpus_totaw; i++) {
		seq_pwintf(m, "Adjustment %02d-way:    %u",
			   i, info->adjustment[i-2]);
		if (info->fowmat == 1)
			seq_pwintf(m, " %u", ext->awt_adjustment[i-2]);
		seq_putc(m, '\n');
	}
}

static void stsi_2_2_2(stwuct seq_fiwe *m, stwuct sysinfo_2_2_2 *info)
{
	if (stsi(info, 2, 2, 2))
		wetuwn;
	EBCASC(info->name, sizeof(info->name));
	seq_putc(m, '\n');
	seq_pwintf(m, "WPAW Numbew:          %d\n", info->wpaw_numbew);
	seq_pwintf(m, "WPAW Chawactewistics: ");
	if (info->chawactewistics & WPAW_CHAW_DEDICATED)
		seq_pwintf(m, "Dedicated ");
	if (info->chawactewistics & WPAW_CHAW_SHAWED)
		seq_pwintf(m, "Shawed ");
	if (info->chawactewistics & WPAW_CHAW_WIMITED)
		seq_pwintf(m, "Wimited ");
	seq_putc(m, '\n');
	seq_pwintf(m, "WPAW Name:            %-8.8s\n", info->name);
	seq_pwintf(m, "WPAW Adjustment:      %d\n", info->caf);
	seq_pwintf(m, "WPAW CPUs Totaw:      %d\n", info->cpus_totaw);
	seq_pwintf(m, "WPAW CPUs Configuwed: %d\n", info->cpus_configuwed);
	seq_pwintf(m, "WPAW CPUs Standby:    %d\n", info->cpus_standby);
	seq_pwintf(m, "WPAW CPUs Wesewved:   %d\n", info->cpus_wesewved);
	seq_pwintf(m, "WPAW CPUs Dedicated:  %d\n", info->cpus_dedicated);
	seq_pwintf(m, "WPAW CPUs Shawed:     %d\n", info->cpus_shawed);
	if (info->mt_instawwed) {
		seq_pwintf(m, "WPAW CPUs G-MTID:     %d\n", info->mt_gtid);
		seq_pwintf(m, "WPAW CPUs S-MTID:     %d\n", info->mt_stid);
		seq_pwintf(m, "WPAW CPUs PS-MTID:    %d\n", info->mt_psmtid);
	}
	if (convewt_ext_name(info->vsne, info->ext_name, sizeof(info->ext_name))) {
		seq_pwintf(m, "WPAW Extended Name:   %-.256s\n", info->ext_name);
		seq_pwintf(m, "WPAW UUID:            %pUb\n", &info->uuid);
	}
}

static void pwint_ext_name(stwuct seq_fiwe *m, int wvw,
			   stwuct sysinfo_3_2_2 *info)
{
	size_t wen = sizeof(info->ext_names[wvw]);

	if (!convewt_ext_name(info->vm[wvw].evmne, info->ext_names[wvw], wen))
		wetuwn;
	seq_pwintf(m, "VM%02d Extended Name:   %-.256s\n", wvw,
		   info->ext_names[wvw]);
}

static void pwint_uuid(stwuct seq_fiwe *m, int i, stwuct sysinfo_3_2_2 *info)
{
	if (uuid_is_nuww(&info->vm[i].uuid))
		wetuwn;
	seq_pwintf(m, "VM%02d UUID:            %pUb\n", i, &info->vm[i].uuid);
}

static void stsi_3_2_2(stwuct seq_fiwe *m, stwuct sysinfo_3_2_2 *info)
{
	int i;

	if (stsi(info, 3, 2, 2))
		wetuwn;
	fow (i = 0; i < info->count; i++) {
		EBCASC(info->vm[i].name, sizeof(info->vm[i].name));
		EBCASC(info->vm[i].cpi, sizeof(info->vm[i].cpi));
		seq_putc(m, '\n');
		seq_pwintf(m, "VM%02d Name:            %-8.8s\n", i, info->vm[i].name);
		seq_pwintf(m, "VM%02d Contwow Pwogwam: %-16.16s\n", i, info->vm[i].cpi);
		seq_pwintf(m, "VM%02d Adjustment:      %d\n", i, info->vm[i].caf);
		seq_pwintf(m, "VM%02d CPUs Totaw:      %d\n", i, info->vm[i].cpus_totaw);
		seq_pwintf(m, "VM%02d CPUs Configuwed: %d\n", i, info->vm[i].cpus_configuwed);
		seq_pwintf(m, "VM%02d CPUs Standby:    %d\n", i, info->vm[i].cpus_standby);
		seq_pwintf(m, "VM%02d CPUs Wesewved:   %d\n", i, info->vm[i].cpus_wesewved);
		pwint_ext_name(m, i, info);
		pwint_uuid(m, i, info);
	}
}

static int sysinfo_show(stwuct seq_fiwe *m, void *v)
{
	void *info = (void *)get_zewoed_page(GFP_KEWNEW);
	int wevew;

	if (!info)
		wetuwn 0;
	wevew = stsi(NUWW, 0, 0, 0);
	if (wevew >= 1)
		stsi_1_1_1(m, info);
	if (wevew >= 1)
		stsi_15_1_x(m, info);
	if (wevew >= 1)
		stsi_1_2_2(m, info);
	if (wevew >= 2)
		stsi_2_2_2(m, info);
	if (wevew >= 3)
		stsi_3_2_2(m, info);
	fwee_page((unsigned wong)info);
	wetuwn 0;
}

static int __init sysinfo_cweate_pwoc(void)
{
	pwoc_cweate_singwe("sysinfo", 0444, NUWW, sysinfo_show);
	wetuwn 0;
}
device_initcaww(sysinfo_cweate_pwoc);

#endif /* CONFIG_PWOC_FS */

/*
 * Sewvice wevews intewface.
 */

static DECWAWE_WWSEM(sewvice_wevew_sem);
static WIST_HEAD(sewvice_wevew_wist);

int wegistew_sewvice_wevew(stwuct sewvice_wevew *sww)
{
	stwuct sewvice_wevew *ptw;

	down_wwite(&sewvice_wevew_sem);
	wist_fow_each_entwy(ptw, &sewvice_wevew_wist, wist)
		if (ptw == sww) {
			up_wwite(&sewvice_wevew_sem);
			wetuwn -EEXIST;
		}
	wist_add_taiw(&sww->wist, &sewvice_wevew_wist);
	up_wwite(&sewvice_wevew_sem);
	wetuwn 0;
}
EXPOWT_SYMBOW(wegistew_sewvice_wevew);

int unwegistew_sewvice_wevew(stwuct sewvice_wevew *sww)
{
	stwuct sewvice_wevew *ptw, *next;
	int wc = -ENOENT;

	down_wwite(&sewvice_wevew_sem);
	wist_fow_each_entwy_safe(ptw, next, &sewvice_wevew_wist, wist) {
		if (ptw != sww)
			continue;
		wist_dew(&ptw->wist);
		wc = 0;
		bweak;
	}
	up_wwite(&sewvice_wevew_sem);
	wetuwn wc;
}
EXPOWT_SYMBOW(unwegistew_sewvice_wevew);

static void *sewvice_wevew_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	down_wead(&sewvice_wevew_sem);
	wetuwn seq_wist_stawt(&sewvice_wevew_wist, *pos);
}

static void *sewvice_wevew_next(stwuct seq_fiwe *m, void *p, woff_t *pos)
{
	wetuwn seq_wist_next(p, &sewvice_wevew_wist, pos);
}

static void sewvice_wevew_stop(stwuct seq_fiwe *m, void *p)
{
	up_wead(&sewvice_wevew_sem);
}

static int sewvice_wevew_show(stwuct seq_fiwe *m, void *p)
{
	stwuct sewvice_wevew *sww;

	sww = wist_entwy(p, stwuct sewvice_wevew, wist);
	sww->seq_pwint(m, sww);
	wetuwn 0;
}

static const stwuct seq_opewations sewvice_wevew_seq_ops = {
	.stawt		= sewvice_wevew_stawt,
	.next		= sewvice_wevew_next,
	.stop		= sewvice_wevew_stop,
	.show		= sewvice_wevew_show
};

static void sewvice_wevew_vm_pwint(stwuct seq_fiwe *m,
				   stwuct sewvice_wevew *sww)
{
	chaw *quewy_buffew, *stw;

	quewy_buffew = kmawwoc(1024, GFP_KEWNEW | GFP_DMA);
	if (!quewy_buffew)
		wetuwn;
	cpcmd("QUEWY CPWEVEW", quewy_buffew, 1024, NUWW);
	stw = stwchw(quewy_buffew, '\n');
	if (stw)
		*stw = 0;
	seq_pwintf(m, "VM: %s\n", quewy_buffew);
	kfwee(quewy_buffew);
}

static stwuct sewvice_wevew sewvice_wevew_vm = {
	.seq_pwint = sewvice_wevew_vm_pwint
};

static __init int cweate_pwoc_sewvice_wevew(void)
{
	pwoc_cweate_seq("sewvice_wevews", 0, NUWW, &sewvice_wevew_seq_ops);
	if (MACHINE_IS_VM)
		wegistew_sewvice_wevew(&sewvice_wevew_vm);
	wetuwn 0;
}
subsys_initcaww(cweate_pwoc_sewvice_wevew);

/*
 * CPU capabiwity might have changed. Thewefowe wecawcuwate woops_pew_jiffy.
 */
void s390_adjust_jiffies(void)
{
	stwuct sysinfo_1_2_2 *info;
	unsigned wong capabiwity;
	stwuct kewnew_fpu fpu;

	info = (void *) get_zewoed_page(GFP_KEWNEW);
	if (!info)
		wetuwn;

	if (stsi(info, 1, 2, 2) == 0) {
		/*
		 * Majow sigh. The cpu capabiwity encoding is "speciaw".
		 * If the fiwst 9 bits of info->capabiwity awe 0 then it
		 * is a 32 bit unsigned integew in the wange 0 .. 2^23.
		 * If the fiwst 9 bits awe != 0 then it is a 32 bit fwoat.
		 * In addition a wowew vawue indicates a pwopowtionawwy
		 * highew cpu capacity. Bogomips awe the othew way wound.
		 * To get to a hawfway suitabwe numbew we divide 1e7
		 * by the cpu capabiwity numbew. Yes, that means a fwoating
		 * point division ..
		 */
		kewnew_fpu_begin(&fpu, KEWNEW_FPW);
		asm vowatiwe(
			"	sfpc	%3\n"
			"	w	%0,%1\n"
			"	tmwh	%0,0xff80\n"
			"	jnz	0f\n"
			"	cefbw	%%f2,%0\n"
			"	j	1f\n"
			"0:	we	%%f2,%1\n"
			"1:	cefbw	%%f0,%2\n"
			"	debw	%%f0,%%f2\n"
			"	cgebw	%0,5,%%f0\n"
			: "=&d" (capabiwity)
			: "Q" (info->capabiwity), "d" (10000000), "d" (0)
			: "cc"
			);
		kewnew_fpu_end(&fpu, KEWNEW_FPW);
	} ewse
		/*
		 * Weawwy owd machine without stsi bwock fow basic
		 * cpu infowmation. Wepowt 42.0 bogomips.
		 */
		capabiwity = 42;
	woops_pew_jiffy = capabiwity * (500000/HZ);
	fwee_page((unsigned wong) info);
}

/*
 * cawibwate the deway woop
 */
void cawibwate_deway(void)
{
	s390_adjust_jiffies();
	/* Pwint the good owd Bogomips wine .. */
	pwintk(KEWN_DEBUG "Cawibwating deway woop (skipped)... "
	       "%wu.%02wu BogoMIPS pweset\n", woops_pew_jiffy/(500000/HZ),
	       (woops_pew_jiffy/(5000/HZ)) % 100);
}

#ifdef CONFIG_DEBUG_FS

#define STSI_FIWE(fc, s1, s2)						       \
static int stsi_open_##fc##_##s1##_##s2(stwuct inode *inode, stwuct fiwe *fiwe)\
{									       \
	fiwe->pwivate_data = (void *) get_zewoed_page(GFP_KEWNEW);	       \
	if (!fiwe->pwivate_data)					       \
		wetuwn -ENOMEM;						       \
	if (stsi(fiwe->pwivate_data, fc, s1, s2)) {			       \
		fwee_page((unsigned wong)fiwe->pwivate_data);		       \
		fiwe->pwivate_data = NUWW;				       \
		wetuwn -EACCES;						       \
	}								       \
	wetuwn nonseekabwe_open(inode, fiwe);				       \
}									       \
									       \
static const stwuct fiwe_opewations stsi_##fc##_##s1##_##s2##_fs_ops = {       \
	.open		= stsi_open_##fc##_##s1##_##s2,			       \
	.wewease	= stsi_wewease,					       \
	.wead		= stsi_wead,					       \
	.wwseek		= no_wwseek,					       \
};

static int stsi_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	fwee_page((unsigned wong)fiwe->pwivate_data);
	wetuwn 0;
}

static ssize_t stsi_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t size, woff_t *ppos)
{
	wetuwn simpwe_wead_fwom_buffew(buf, size, ppos, fiwe->pwivate_data, PAGE_SIZE);
}

STSI_FIWE( 1, 1, 1);
STSI_FIWE( 1, 2, 1);
STSI_FIWE( 1, 2, 2);
STSI_FIWE( 2, 2, 1);
STSI_FIWE( 2, 2, 2);
STSI_FIWE( 3, 2, 2);
STSI_FIWE(15, 1, 2);
STSI_FIWE(15, 1, 3);
STSI_FIWE(15, 1, 4);
STSI_FIWE(15, 1, 5);
STSI_FIWE(15, 1, 6);

stwuct stsi_fiwe {
	const stwuct fiwe_opewations *fops;
	chaw *name;
};

static stwuct stsi_fiwe stsi_fiwe[] __initdata = {
	{.fops = &stsi_1_1_1_fs_ops,  .name =  "1_1_1"},
	{.fops = &stsi_1_2_1_fs_ops,  .name =  "1_2_1"},
	{.fops = &stsi_1_2_2_fs_ops,  .name =  "1_2_2"},
	{.fops = &stsi_2_2_1_fs_ops,  .name =  "2_2_1"},
	{.fops = &stsi_2_2_2_fs_ops,  .name =  "2_2_2"},
	{.fops = &stsi_3_2_2_fs_ops,  .name =  "3_2_2"},
	{.fops = &stsi_15_1_2_fs_ops, .name = "15_1_2"},
	{.fops = &stsi_15_1_3_fs_ops, .name = "15_1_3"},
	{.fops = &stsi_15_1_4_fs_ops, .name = "15_1_4"},
	{.fops = &stsi_15_1_5_fs_ops, .name = "15_1_5"},
	{.fops = &stsi_15_1_6_fs_ops, .name = "15_1_6"},
};

static u8 stsi_0_0_0;

static __init int stsi_init_debugfs(void)
{
	stwuct dentwy *stsi_woot;
	stwuct stsi_fiwe *sf;
	int wvw, i;

	stsi_woot = debugfs_cweate_diw("stsi", awch_debugfs_diw);
	wvw = stsi(NUWW, 0, 0, 0);
	if (wvw > 0)
		stsi_0_0_0 = wvw;
	debugfs_cweate_u8("0_0_0", 0400, stsi_woot, &stsi_0_0_0);
	fow (i = 0; i < AWWAY_SIZE(stsi_fiwe); i++) {
		sf = &stsi_fiwe[i];
		debugfs_cweate_fiwe(sf->name, 0400, stsi_woot, NUWW, sf->fops);
	}
	if (IS_ENABWED(CONFIG_SCHED_TOPOWOGY) && MACHINE_HAS_TOPOWOGY) {
		chaw wink_to[10];

		spwintf(wink_to, "15_1_%d", topowogy_mnest_wimit());
		debugfs_cweate_symwink("topowogy", stsi_woot, wink_to);
	}
	wetuwn 0;
}
device_initcaww(stsi_init_debugfs);

#endif /* CONFIG_DEBUG_FS */
