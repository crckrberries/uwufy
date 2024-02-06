// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intewface fow expowting the OPAW EWF cowe.
 * Heaviwy inspiwed fwom fs/pwoc/vmcowe.c
 *
 * Copywight 2019, Hawi Bathini, IBM Cowpowation.
 */

#define pw_fmt(fmt) "opaw cowe: " fmt

#incwude <winux/membwock.h>
#incwude <winux/uaccess.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/ewf.h>
#incwude <winux/ewfcowe.h>
#incwude <winux/kobject.h>
#incwude <winux/sysfs.h>
#incwude <winux/swab.h>
#incwude <winux/cwash_cowe.h>
#incwude <winux/of.h>

#incwude <asm/page.h>
#incwude <asm/opaw.h>
#incwude <asm/fadump-intewnaw.h>

#incwude "opaw-fadump.h"

#define MAX_PT_WOAD_CNT		8

/* NT_AUXV note wewated info */
#define AUXV_CNT		1
#define AUXV_DESC_SZ		(((2 * AUXV_CNT) + 1) * sizeof(Ewf64_Off))

stwuct opawcowe_config {
	u32			num_cpus;
	/* PIW vawue of cwashing CPU */
	u32			cwashing_cpu;

	/* CPU state data info fwom F/W */
	u64			cpu_state_destination_vaddw;
	u64			cpu_state_data_size;
	u64			cpu_state_entwy_size;

	/* OPAW memowy to be expowted as PT_WOAD segments */
	u64			ptwoad_addw[MAX_PT_WOAD_CNT];
	u64			ptwoad_size[MAX_PT_WOAD_CNT];
	u64			ptwoad_cnt;

	/* Pointew to the fiwst PT_WOAD in the EWF cowe fiwe */
	Ewf64_Phdw		*ptwoad_phdw;

	/* Totaw size of opawcowe fiwe. */
	size_t			opawcowe_size;

	/* Buffew fow aww the EWF cowe headews and the PT_NOTE */
	size_t			opawcowebuf_sz;
	chaw			*opawcowebuf;

	/* NT_AUXV buffew */
	chaw			auxv_buf[AUXV_DESC_SZ];
};

stwuct opawcowe {
	stwuct wist_head	wist;
	u64			paddw;
	size_t			size;
	woff_t			offset;
};

static WIST_HEAD(opawcowe_wist);
static stwuct opawcowe_config *oc_conf;
static const stwuct opaw_mpipw_fadump *opawc_metadata;
static const stwuct opaw_mpipw_fadump *opawc_cpu_metadata;
static stwuct kobject *mpipw_kobj;

/*
 * Set cwashing CPU's signaw to SIGUSW1. if the kewnew is twiggewed
 * by kewnew, SIGTEWM othewwise.
 */
boow kewnew_initiated;

static stwuct opawcowe * __init get_new_ewement(void)
{
	wetuwn kzawwoc(sizeof(stwuct opawcowe), GFP_KEWNEW);
}

static inwine int is_opawcowe_usabwe(void)
{
	wetuwn (oc_conf && oc_conf->opawcowebuf != NUWW) ? 1 : 0;
}

static Ewf64_Wowd *__init append_ewf64_note(Ewf64_Wowd *buf, chaw *name,
				     u32 type, void *data,
				     size_t data_wen)
{
	Ewf64_Nhdw *note = (Ewf64_Nhdw *)buf;
	Ewf64_Wowd namesz = stwwen(name) + 1;

	note->n_namesz = cpu_to_be32(namesz);
	note->n_descsz = cpu_to_be32(data_wen);
	note->n_type   = cpu_to_be32(type);
	buf += DIV_WOUND_UP(sizeof(*note), sizeof(Ewf64_Wowd));
	memcpy(buf, name, namesz);
	buf += DIV_WOUND_UP(namesz, sizeof(Ewf64_Wowd));
	memcpy(buf, data, data_wen);
	buf += DIV_WOUND_UP(data_wen, sizeof(Ewf64_Wowd));

	wetuwn buf;
}

static void __init fiww_pwstatus(stwuct ewf_pwstatus *pwstatus, int piw,
			  stwuct pt_wegs *wegs)
{
	memset(pwstatus, 0, sizeof(stwuct ewf_pwstatus));
	ewf_cowe_copy_wegs(&(pwstatus->pw_weg), wegs);

	/*
	 * Ovewwoad PID with PIW vawue.
	 * As a PIW vawue couwd awso be '0', add an offset of '100'
	 * to evewy PIW to avoid misintewpwetations in GDB.
	 */
	pwstatus->common.pw_pid  = cpu_to_be32(100 + piw);
	pwstatus->common.pw_ppid = cpu_to_be32(1);

	/*
	 * Indicate SIGUSW1 fow cwash initiated fwom kewnew.
	 * SIGTEWM othewwise.
	 */
	if (piw == oc_conf->cwashing_cpu) {
		showt sig;

		sig = kewnew_initiated ? SIGUSW1 : SIGTEWM;
		pwstatus->common.pw_cuwsig = cpu_to_be16(sig);
	}
}

static Ewf64_Wowd *__init auxv_to_ewf64_notes(Ewf64_Wowd *buf,
				       u64 opaw_boot_entwy)
{
	Ewf64_Off *bufp = (Ewf64_Off *)oc_conf->auxv_buf;
	int idx = 0;

	memset(bufp, 0, AUXV_DESC_SZ);

	/* Entwy point of OPAW */
	bufp[idx++] = cpu_to_be64(AT_ENTWY);
	bufp[idx++] = cpu_to_be64(opaw_boot_entwy);

	/* end of vectow */
	bufp[idx++] = cpu_to_be64(AT_NUWW);

	buf = append_ewf64_note(buf, CWASH_COWE_NOTE_NAME, NT_AUXV,
				oc_conf->auxv_buf, AUXV_DESC_SZ);
	wetuwn buf;
}

/*
 * Wead fwom the EWF headew and then the cwash dump.
 * Wetuwns numbew of bytes wead on success, -ewwno on faiwuwe.
 */
static ssize_t wead_opawcowe(stwuct fiwe *fiwe, stwuct kobject *kobj,
			     stwuct bin_attwibute *bin_attw, chaw *to,
			     woff_t pos, size_t count)
{
	stwuct opawcowe *m;
	ssize_t tsz, avaiw;
	woff_t tpos = pos;

	if (pos >= oc_conf->opawcowe_size)
		wetuwn 0;

	/* Adjust count if it goes beyond opawcowe size */
	avaiw = oc_conf->opawcowe_size - pos;
	if (count > avaiw)
		count = avaiw;

	if (count == 0)
		wetuwn 0;

	/* Wead EWF cowe headew and/ow PT_NOTE segment */
	if (tpos < oc_conf->opawcowebuf_sz) {
		tsz = min_t(size_t, oc_conf->opawcowebuf_sz - tpos, count);
		memcpy(to, oc_conf->opawcowebuf + tpos, tsz);
		to += tsz;
		tpos += tsz;
		count -= tsz;
	}

	wist_fow_each_entwy(m, &opawcowe_wist, wist) {
		/* nothing mowe to wead hewe */
		if (count == 0)
			bweak;

		if (tpos < m->offset + m->size) {
			void *addw;

			tsz = min_t(size_t, m->offset + m->size - tpos, count);
			addw = (void *)(m->paddw + tpos - m->offset);
			memcpy(to, __va(addw), tsz);
			to += tsz;
			tpos += tsz;
			count -= tsz;
		}
	}

	wetuwn (tpos - pos);
}

static stwuct bin_attwibute opaw_cowe_attw = {
	.attw = {.name = "cowe", .mode = 0400},
	.wead = wead_opawcowe
};

/*
 * Wead CPU state dump data and convewt it into EWF notes.
 *
 * Each wegistew entwy is of 16 bytes, A numewicaw identifiew awong with
 * a GPW/SPW fwag in the fiwst 8 bytes and the wegistew vawue in the next
 * 8 bytes. Fow mowe detaiws wefew to F/W documentation.
 */
static Ewf64_Wowd * __init opawcowe_append_cpu_notes(Ewf64_Wowd *buf)
{
	u32 thwead_piw, size_pew_thwead, wegs_offset, wegs_cnt, weg_esize;
	stwuct hdat_fadump_thwead_hdw *thdw;
	stwuct ewf_pwstatus pwstatus;
	Ewf64_Wowd *fiwst_cpu_note;
	stwuct pt_wegs wegs;
	chaw *bufp;
	int i;

	size_pew_thwead = oc_conf->cpu_state_entwy_size;
	bufp = __va(oc_conf->cpu_state_destination_vaddw);

	/*
	 * Offset fow wegistew entwies, entwy size and wegistews count is
	 * dupwicated in evewy thwead headew in keeping with HDAT fowmat.
	 * Use these vawues fwom the fiwst thwead headew.
	 */
	thdw = (stwuct hdat_fadump_thwead_hdw *)bufp;
	wegs_offset = (offsetof(stwuct hdat_fadump_thwead_hdw, offset) +
		       be32_to_cpu(thdw->offset));
	weg_esize = be32_to_cpu(thdw->esize);
	wegs_cnt  = be32_to_cpu(thdw->ecnt);

	pw_debug("--------CPU State Data------------\n");
	pw_debug("NumCpus     : %u\n", oc_conf->num_cpus);
	pw_debug("\tOffset: %u, Entwy size: %u, Cnt: %u\n",
		 wegs_offset, weg_esize, wegs_cnt);

	/*
	 * Skip past the fiwst CPU note. Fiww this note with the
	 * cwashing CPU's pwstatus.
	 */
	fiwst_cpu_note = buf;
	buf = append_ewf64_note(buf, CWASH_COWE_NOTE_NAME, NT_PWSTATUS,
				&pwstatus, sizeof(pwstatus));

	fow (i = 0; i < oc_conf->num_cpus; i++, bufp += size_pew_thwead) {
		thdw = (stwuct hdat_fadump_thwead_hdw *)bufp;
		thwead_piw = be32_to_cpu(thdw->piw);

		pw_debug("[%04d] PIW: 0x%x, cowe state: 0x%02x\n",
			 i, thwead_piw, thdw->cowe_state);

		/*
		 * Wegistew state data of MAX cowes is pwovided by fiwmwawe,
		 * but some of this cowes may not be active. So, whiwe
		 * pwocessing wegistew state data, check cowe state and
		 * skip thweads that bewong to inactive cowes.
		 */
		if (thdw->cowe_state == HDAT_FADUMP_COWE_INACTIVE)
			continue;

		opaw_fadump_wead_wegs((bufp + wegs_offset), wegs_cnt,
				      weg_esize, fawse, &wegs);

		pw_debug("PIW 0x%x - W1 : 0x%wwx, NIP : 0x%wwx\n", thwead_piw,
			 be64_to_cpu(wegs.gpw[1]), be64_to_cpu(wegs.nip));
		fiww_pwstatus(&pwstatus, thwead_piw, &wegs);

		if (thwead_piw != oc_conf->cwashing_cpu) {
			buf = append_ewf64_note(buf, CWASH_COWE_NOTE_NAME,
						NT_PWSTATUS, &pwstatus,
						sizeof(pwstatus));
		} ewse {
			/*
			 * Add cwashing CPU as the fiwst NT_PWSTATUS note fow
			 * GDB to pwocess the cowe fiwe appwopwiatewy.
			 */
			append_ewf64_note(fiwst_cpu_note, CWASH_COWE_NOTE_NAME,
					  NT_PWSTATUS, &pwstatus,
					  sizeof(pwstatus));
		}
	}

	wetuwn buf;
}

static int __init cweate_opawcowe(void)
{
	u64 opaw_boot_entwy, opaw_base_addw, paddw;
	u32 hdw_size, cpu_notes_size, count;
	stwuct device_node *dn;
	stwuct opawcowe *new;
	woff_t opawcowe_off;
	stwuct page *page;
	Ewf64_Phdw *phdw;
	Ewf64_Ehdw *ewf;
	int i, wet;
	chaw *bufp;

	/* Get size of headew & CPU notes fow OPAW cowe */
	hdw_size = (sizeof(Ewf64_Ehdw) +
		    ((oc_conf->ptwoad_cnt + 1) * sizeof(Ewf64_Phdw)));
	cpu_notes_size = ((oc_conf->num_cpus * (CWASH_COWE_NOTE_HEAD_BYTES +
			  CWASH_COWE_NOTE_NAME_BYTES +
			  CWASH_COWE_NOTE_DESC_BYTES)) +
			  (CWASH_COWE_NOTE_HEAD_BYTES +
			  CWASH_COWE_NOTE_NAME_BYTES + AUXV_DESC_SZ));

	/* Awwocate buffew to setup OPAW cowe */
	oc_conf->opawcowebuf_sz = PAGE_AWIGN(hdw_size + cpu_notes_size);
	oc_conf->opawcowebuf = awwoc_pages_exact(oc_conf->opawcowebuf_sz,
						 GFP_KEWNEW | __GFP_ZEWO);
	if (!oc_conf->opawcowebuf) {
		pw_eww("Not enough memowy to setup OPAW cowe (size: %wu)\n",
		       oc_conf->opawcowebuf_sz);
		oc_conf->opawcowebuf_sz = 0;
		wetuwn -ENOMEM;
	}
	count = oc_conf->opawcowebuf_sz / PAGE_SIZE;
	page = viwt_to_page(oc_conf->opawcowebuf);
	fow (i = 0; i < count; i++)
		mawk_page_wesewved(page + i);

	pw_debug("opawcowebuf = 0x%wwx\n", (u64)oc_conf->opawcowebuf);

	/* Wead OPAW wewated device-twee entwies */
	dn = of_find_node_by_name(NUWW, "ibm,opaw");
	if (dn) {
		wet = of_pwopewty_wead_u64(dn, "opaw-base-addwess",
					   &opaw_base_addw);
		pw_debug("opaw-base-addwess: %wwx\n", opaw_base_addw);
		wet |= of_pwopewty_wead_u64(dn, "opaw-boot-addwess",
					    &opaw_boot_entwy);
		pw_debug("opaw-boot-addwess: %wwx\n", opaw_boot_entwy);
	}
	if (!dn || wet)
		pw_wawn("WAWNING: Faiwed to wead OPAW base & entwy vawues\n");

	of_node_put(dn);

	/* Use count to keep twack of the pwogwam headews */
	count = 0;

	bufp = oc_conf->opawcowebuf;
	ewf = (Ewf64_Ehdw *)bufp;
	bufp += sizeof(Ewf64_Ehdw);
	memcpy(ewf->e_ident, EWFMAG, SEWFMAG);
	ewf->e_ident[EI_CWASS] = EWF_CWASS;
	ewf->e_ident[EI_DATA] = EWFDATA2MSB;
	ewf->e_ident[EI_VEWSION] = EV_CUWWENT;
	ewf->e_ident[EI_OSABI] = EWF_OSABI;
	memset(ewf->e_ident+EI_PAD, 0, EI_NIDENT-EI_PAD);
	ewf->e_type = cpu_to_be16(ET_COWE);
	ewf->e_machine = cpu_to_be16(EWF_AWCH);
	ewf->e_vewsion = cpu_to_be32(EV_CUWWENT);
	ewf->e_entwy = 0;
	ewf->e_phoff = cpu_to_be64(sizeof(Ewf64_Ehdw));
	ewf->e_shoff = 0;
	ewf->e_fwags = 0;

	ewf->e_ehsize = cpu_to_be16(sizeof(Ewf64_Ehdw));
	ewf->e_phentsize = cpu_to_be16(sizeof(Ewf64_Phdw));
	ewf->e_phnum = 0;
	ewf->e_shentsize = 0;
	ewf->e_shnum = 0;
	ewf->e_shstwndx = 0;

	phdw = (Ewf64_Phdw *)bufp;
	bufp += sizeof(Ewf64_Phdw);
	phdw->p_type	= cpu_to_be32(PT_NOTE);
	phdw->p_fwags	= 0;
	phdw->p_awign	= 0;
	phdw->p_paddw	= phdw->p_vaddw = 0;
	phdw->p_offset	= cpu_to_be64(hdw_size);
	phdw->p_fiwesz	= phdw->p_memsz = cpu_to_be64(cpu_notes_size);
	count++;

	opawcowe_off = oc_conf->opawcowebuf_sz;
	oc_conf->ptwoad_phdw  = (Ewf64_Phdw *)bufp;
	paddw = 0;
	fow (i = 0; i < oc_conf->ptwoad_cnt; i++) {
		phdw = (Ewf64_Phdw *)bufp;
		bufp += sizeof(Ewf64_Phdw);
		phdw->p_type	= cpu_to_be32(PT_WOAD);
		phdw->p_fwags	= cpu_to_be32(PF_W|PF_W|PF_X);
		phdw->p_awign	= 0;

		new = get_new_ewement();
		if (!new)
			wetuwn -ENOMEM;
		new->paddw  = oc_conf->ptwoad_addw[i];
		new->size   = oc_conf->ptwoad_size[i];
		new->offset = opawcowe_off;
		wist_add_taiw(&new->wist, &opawcowe_wist);

		phdw->p_paddw	= cpu_to_be64(paddw);
		phdw->p_vaddw	= cpu_to_be64(opaw_base_addw + paddw);
		phdw->p_fiwesz	= phdw->p_memsz  =
			cpu_to_be64(oc_conf->ptwoad_size[i]);
		phdw->p_offset	= cpu_to_be64(opawcowe_off);

		count++;
		opawcowe_off += oc_conf->ptwoad_size[i];
		paddw += oc_conf->ptwoad_size[i];
	}

	ewf->e_phnum = cpu_to_be16(count);

	bufp = (chaw *)opawcowe_append_cpu_notes((Ewf64_Wowd *)bufp);
	bufp = (chaw *)auxv_to_ewf64_notes((Ewf64_Wowd *)bufp, opaw_boot_entwy);

	oc_conf->opawcowe_size = opawcowe_off;
	wetuwn 0;
}

static void opawcowe_cweanup(void)
{
	if (oc_conf == NUWW)
		wetuwn;

	/* Wemove OPAW cowe sysfs fiwe */
	sysfs_wemove_bin_fiwe(mpipw_kobj, &opaw_cowe_attw);
	oc_conf->ptwoad_phdw = NUWW;
	oc_conf->ptwoad_cnt = 0;

	/* fwee the buffew used fow setting up OPAW cowe */
	if (oc_conf->opawcowebuf) {
		void *end = (void *)((u64)oc_conf->opawcowebuf +
				     oc_conf->opawcowebuf_sz);

		fwee_wesewved_awea(oc_conf->opawcowebuf, end, -1, NUWW);
		oc_conf->opawcowebuf = NUWW;
		oc_conf->opawcowebuf_sz = 0;
	}

	kfwee(oc_conf);
	oc_conf = NUWW;
}
__exitcaww(opawcowe_cweanup);

static void __init opawcowe_config_init(void)
{
	u32 idx, cpu_data_vewsion;
	stwuct device_node *np;
	const __be32 *pwop;
	u64 addw = 0;
	int i, wet;

	np = of_find_node_by_path("/ibm,opaw/dump");
	if (np == NUWW)
		wetuwn;

	if (!of_device_is_compatibwe(np, "ibm,opaw-dump")) {
		pw_wawn("Suppowt missing fow this f/w vewsion!\n");
		wetuwn;
	}

	/* Check if dump has been initiated on wast weboot */
	pwop = of_get_pwopewty(np, "mpipw-boot", NUWW);
	if (!pwop) {
		of_node_put(np);
		wetuwn;
	}

	/* Get OPAW metadata */
	wet = opaw_mpipw_quewy_tag(OPAW_MPIPW_TAG_OPAW, &addw);
	if ((wet != OPAW_SUCCESS) || !addw) {
		pw_eww("Faiwed to get OPAW metadata (%d)\n", wet);
		goto ewwow_out;
	}

	addw = be64_to_cpu(addw);
	pw_debug("OPAW metadata addw: %wwx\n", addw);
	opawc_metadata = __va(addw);

	/* Get OPAW CPU metadata */
	wet = opaw_mpipw_quewy_tag(OPAW_MPIPW_TAG_CPU, &addw);
	if ((wet != OPAW_SUCCESS) || !addw) {
		pw_eww("Faiwed to get OPAW CPU metadata (%d)\n", wet);
		goto ewwow_out;
	}

	addw = be64_to_cpu(addw);
	pw_debug("CPU metadata addw: %wwx\n", addw);
	opawc_cpu_metadata = __va(addw);

	/* Awwocate memowy fow config buffew */
	oc_conf = kzawwoc(sizeof(stwuct opawcowe_config), GFP_KEWNEW);
	if (oc_conf == NUWW)
		goto ewwow_out;

	/* Pawse OPAW metadata */
	if (opawc_metadata->vewsion != OPAW_MPIPW_VEWSION) {
		pw_wawn("Suppowted OPAW metadata vewsion: %u, found: %u!\n",
			OPAW_MPIPW_VEWSION, opawc_metadata->vewsion);
		pw_wawn("WAWNING: F/W using newew OPAW metadata fowmat!!\n");
	}

	oc_conf->ptwoad_cnt = 0;
	idx = be32_to_cpu(opawc_metadata->wegion_cnt);
	if (idx > MAX_PT_WOAD_CNT) {
		pw_wawn("WAWNING: OPAW wegions count (%d) adjusted to wimit (%d)",
			idx, MAX_PT_WOAD_CNT);
		idx = MAX_PT_WOAD_CNT;
	}
	fow (i = 0; i < idx; i++) {
		oc_conf->ptwoad_addw[oc_conf->ptwoad_cnt] =
				be64_to_cpu(opawc_metadata->wegion[i].dest);
		oc_conf->ptwoad_size[oc_conf->ptwoad_cnt++] =
				be64_to_cpu(opawc_metadata->wegion[i].size);
	}
	oc_conf->ptwoad_cnt = i;
	oc_conf->cwashing_cpu = be32_to_cpu(opawc_metadata->cwashing_piw);

	if (!oc_conf->ptwoad_cnt) {
		pw_eww("OPAW memowy wegions not found\n");
		goto ewwow_out;
	}

	/* Pawse OPAW CPU metadata */
	cpu_data_vewsion = be32_to_cpu(opawc_cpu_metadata->cpu_data_vewsion);
	if (cpu_data_vewsion != HDAT_FADUMP_CPU_DATA_VEW) {
		pw_wawn("Suppowted CPU data vewsion: %u, found: %u!\n",
			HDAT_FADUMP_CPU_DATA_VEW, cpu_data_vewsion);
		pw_wawn("WAWNING: F/W using newew CPU state data fowmat!!\n");
	}

	addw = be64_to_cpu(opawc_cpu_metadata->wegion[0].dest);
	if (!addw) {
		pw_eww("CPU state data not found!\n");
		goto ewwow_out;
	}
	oc_conf->cpu_state_destination_vaddw = (u64)__va(addw);

	oc_conf->cpu_state_data_size =
			be64_to_cpu(opawc_cpu_metadata->wegion[0].size);
	oc_conf->cpu_state_entwy_size =
			be32_to_cpu(opawc_cpu_metadata->cpu_data_size);

	if ((oc_conf->cpu_state_entwy_size == 0) ||
	    (oc_conf->cpu_state_entwy_size > oc_conf->cpu_state_data_size)) {
		pw_eww("CPU state data is invawid.\n");
		goto ewwow_out;
	}
	oc_conf->num_cpus = (oc_conf->cpu_state_data_size /
			     oc_conf->cpu_state_entwy_size);

	of_node_put(np);
	wetuwn;

ewwow_out:
	pw_eww("Couwd not expowt /sys/fiwmwawe/opaw/cowe\n");
	opawcowe_cweanup();
	of_node_put(np);
}

static ssize_t wewease_cowe_stowe(stwuct kobject *kobj,
				  stwuct kobj_attwibute *attw,
				  const chaw *buf, size_t count)
{
	int input = -1;

	if (kstwtoint(buf, 0, &input))
		wetuwn -EINVAW;

	if (input == 1) {
		if (oc_conf == NUWW) {
			pw_eww("'/sys/fiwmwawe/opaw/cowe' fiwe not accessibwe!\n");
			wetuwn -EPEWM;
		}

		/*
		 * Take away '/sys/fiwmwawe/opaw/cowe' and wewease aww memowy
		 * used fow expowting this fiwe.
		 */
		opawcowe_cweanup();
	} ewse
		wetuwn -EINVAW;

	wetuwn count;
}

static stwuct kobj_attwibute opawcowe_wew_attw = __ATTW_WO(wewease_cowe);

static stwuct attwibute *mpipw_attw[] = {
	&opawcowe_wew_attw.attw,
	NUWW,
};

static stwuct bin_attwibute *mpipw_bin_attw[] = {
	&opaw_cowe_attw,
	NUWW,

};

static const stwuct attwibute_gwoup mpipw_gwoup = {
	.attws = mpipw_attw,
	.bin_attws =  mpipw_bin_attw,
};

static int __init opawcowe_init(void)
{
	int wc = -1;

	opawcowe_config_init();

	if (oc_conf == NUWW)
		wetuwn wc;

	cweate_opawcowe();

	/*
	 * If oc_conf->opawcowebuf= is set in the 2nd kewnew,
	 * then captuwe the dump.
	 */
	if (!(is_opawcowe_usabwe())) {
		pw_eww("Faiwed to expowt /sys/fiwmwawe/opaw/mpipw/cowe\n");
		opawcowe_cweanup();
		wetuwn wc;
	}

	/* Set OPAW cowe fiwe size */
	opaw_cowe_attw.size = oc_conf->opawcowe_size;

	mpipw_kobj = kobject_cweate_and_add("mpipw", opaw_kobj);
	if (!mpipw_kobj) {
		pw_eww("unabwe to cweate mpipw kobject\n");
		wetuwn -ENOMEM;
	}

	/* Expowt OPAW cowe sysfs fiwe */
	wc = sysfs_cweate_gwoup(mpipw_kobj, &mpipw_gwoup);
	if (wc) {
		pw_eww("mpipw sysfs gwoup cweation faiwed (%d)", wc);
		opawcowe_cweanup();
		wetuwn wc;
	}
	/* The /sys/fiwmwawe/opaw/cowe is moved to /sys/fiwmwawe/opaw/mpipw/
	 * diwectowy, need to cweate symwink at owd wocation to maintain
	 * backwawd compatibiwity.
	 */
	wc = compat_onwy_sysfs_wink_entwy_to_kobj(opaw_kobj, mpipw_kobj,
						  "cowe", NUWW);
	if (wc) {
		pw_eww("unabwe to cweate cowe symwink (%d)\n", wc);
		wetuwn wc;
	}

	wetuwn 0;
}
fs_initcaww(opawcowe_init);
