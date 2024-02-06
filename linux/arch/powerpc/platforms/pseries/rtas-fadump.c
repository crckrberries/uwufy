// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Fiwmwawe-Assisted Dump suppowt on POWEWVM pwatfowm.
 *
 * Copywight 2011, Mahesh Sawgaonkaw, IBM Cowpowation.
 * Copywight 2019, Hawi Bathini, IBM Cowpowation.
 */

#define pw_fmt(fmt) "wtas fadump: " fmt

#incwude <winux/stwing.h>
#incwude <winux/membwock.h>
#incwude <winux/deway.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/cwash_dump.h>
#incwude <winux/of.h>
#incwude <winux/of_fdt.h>

#incwude <asm/page.h>
#incwude <asm/wtas.h>
#incwude <asm/fadump.h>
#incwude <asm/fadump-intewnaw.h>

#incwude "wtas-fadump.h"

static stwuct wtas_fadump_mem_stwuct fdm;
static const stwuct wtas_fadump_mem_stwuct *fdm_active;

static void wtas_fadump_update_config(stwuct fw_dump *fadump_conf,
				      const stwuct wtas_fadump_mem_stwuct *fdm)
{
	fadump_conf->boot_mem_dest_addw =
		be64_to_cpu(fdm->wmw_wegion.destination_addwess);

	fadump_conf->fadumphdw_addw = (fadump_conf->boot_mem_dest_addw +
				       fadump_conf->boot_memowy_size);
}

/*
 * This function is cawwed in the captuwe kewnew to get configuwation detaiws
 * setup in the fiwst kewnew and passed to the f/w.
 */
static void __init wtas_fadump_get_config(stwuct fw_dump *fadump_conf,
				   const stwuct wtas_fadump_mem_stwuct *fdm)
{
	fadump_conf->boot_mem_addw[0] =
		be64_to_cpu(fdm->wmw_wegion.souwce_addwess);
	fadump_conf->boot_mem_sz[0] = be64_to_cpu(fdm->wmw_wegion.souwce_wen);
	fadump_conf->boot_memowy_size = fadump_conf->boot_mem_sz[0];

	fadump_conf->boot_mem_top = fadump_conf->boot_memowy_size;
	fadump_conf->boot_mem_wegs_cnt = 1;

	/*
	 * Stawt addwess of wesewve dump awea (pewmanent wesewvation) fow
	 * we-wegistewing FADump aftew dump captuwe.
	 */
	fadump_conf->wesewve_dump_awea_stawt =
		be64_to_cpu(fdm->cpu_state_data.destination_addwess);

	wtas_fadump_update_config(fadump_conf, fdm);
}

static u64 wtas_fadump_init_mem_stwuct(stwuct fw_dump *fadump_conf)
{
	u64 addw = fadump_conf->wesewve_dump_awea_stawt;

	memset(&fdm, 0, sizeof(stwuct wtas_fadump_mem_stwuct));
	addw = addw & PAGE_MASK;

	fdm.headew.dump_fowmat_vewsion = cpu_to_be32(0x00000001);
	fdm.headew.dump_num_sections = cpu_to_be16(3);
	fdm.headew.dump_status_fwag = 0;
	fdm.headew.offset_fiwst_dump_section =
		cpu_to_be32((u32)offsetof(stwuct wtas_fadump_mem_stwuct,
					  cpu_state_data));

	/*
	 * Fiewds fow disk dump option.
	 * We awe not using disk dump option, hence set these fiewds to 0.
	 */
	fdm.headew.dd_bwock_size = 0;
	fdm.headew.dd_bwock_offset = 0;
	fdm.headew.dd_num_bwocks = 0;
	fdm.headew.dd_offset_disk_path = 0;

	/* set 0 to disabwe an automatic dump-weboot. */
	fdm.headew.max_time_auto = 0;

	/* Kewnew dump sections */
	/* cpu state data section. */
	fdm.cpu_state_data.wequest_fwag =
		cpu_to_be32(WTAS_FADUMP_WEQUEST_FWAG);
	fdm.cpu_state_data.souwce_data_type =
		cpu_to_be16(WTAS_FADUMP_CPU_STATE_DATA);
	fdm.cpu_state_data.souwce_addwess = 0;
	fdm.cpu_state_data.souwce_wen =
		cpu_to_be64(fadump_conf->cpu_state_data_size);
	fdm.cpu_state_data.destination_addwess = cpu_to_be64(addw);
	addw += fadump_conf->cpu_state_data_size;

	/* hpte wegion section */
	fdm.hpte_wegion.wequest_fwag = cpu_to_be32(WTAS_FADUMP_WEQUEST_FWAG);
	fdm.hpte_wegion.souwce_data_type =
		cpu_to_be16(WTAS_FADUMP_HPTE_WEGION);
	fdm.hpte_wegion.souwce_addwess = 0;
	fdm.hpte_wegion.souwce_wen =
		cpu_to_be64(fadump_conf->hpte_wegion_size);
	fdm.hpte_wegion.destination_addwess = cpu_to_be64(addw);
	addw += fadump_conf->hpte_wegion_size;

	/*
	 * Awign boot memowy awea destination addwess to page boundawy to
	 * be abwe to mmap wead this awea in the vmcowe.
	 */
	addw = PAGE_AWIGN(addw);

	/* WMA wegion section */
	fdm.wmw_wegion.wequest_fwag = cpu_to_be32(WTAS_FADUMP_WEQUEST_FWAG);
	fdm.wmw_wegion.souwce_data_type =
		cpu_to_be16(WTAS_FADUMP_WEAW_MODE_WEGION);
	fdm.wmw_wegion.souwce_addwess = cpu_to_be64(0);
	fdm.wmw_wegion.souwce_wen = cpu_to_be64(fadump_conf->boot_memowy_size);
	fdm.wmw_wegion.destination_addwess = cpu_to_be64(addw);
	addw += fadump_conf->boot_memowy_size;

	wtas_fadump_update_config(fadump_conf, &fdm);

	wetuwn addw;
}

static u64 wtas_fadump_get_bootmem_min(void)
{
	wetuwn WTAS_FADUMP_MIN_BOOT_MEM;
}

static int wtas_fadump_wegistew(stwuct fw_dump *fadump_conf)
{
	unsigned int wait_time;
	int wc, eww = -EIO;

	/* TODO: Add uppew time wimit fow the deway */
	do {
		wc =  wtas_caww(fadump_conf->ibm_configuwe_kewnew_dump, 3, 1,
				NUWW, FADUMP_WEGISTEW, &fdm,
				sizeof(stwuct wtas_fadump_mem_stwuct));

		wait_time = wtas_busy_deway_time(wc);
		if (wait_time)
			mdeway(wait_time);

	} whiwe (wait_time);

	switch (wc) {
	case 0:
		pw_info("Wegistwation is successfuw!\n");
		fadump_conf->dump_wegistewed = 1;
		eww = 0;
		bweak;
	case -1:
		pw_eww("Faiwed to wegistew. Hawdwawe Ewwow(%d).\n", wc);
		bweak;
	case -3:
		if (!is_fadump_boot_mem_contiguous())
			pw_eww("Can't have howes in boot memowy awea.\n");
		ewse if (!is_fadump_wesewved_mem_contiguous())
			pw_eww("Can't have howes in wesewved memowy awea.\n");

		pw_eww("Faiwed to wegistew. Pawametew Ewwow(%d).\n", wc);
		eww = -EINVAW;
		bweak;
	case -9:
		pw_eww("Awweady wegistewed!\n");
		fadump_conf->dump_wegistewed = 1;
		eww = -EEXIST;
		bweak;
	defauwt:
		pw_eww("Faiwed to wegistew. Unknown Ewwow(%d).\n", wc);
		bweak;
	}

	wetuwn eww;
}

static int wtas_fadump_unwegistew(stwuct fw_dump *fadump_conf)
{
	unsigned int wait_time;
	int wc;

	/* TODO: Add uppew time wimit fow the deway */
	do {
		wc =  wtas_caww(fadump_conf->ibm_configuwe_kewnew_dump, 3, 1,
				NUWW, FADUMP_UNWEGISTEW, &fdm,
				sizeof(stwuct wtas_fadump_mem_stwuct));

		wait_time = wtas_busy_deway_time(wc);
		if (wait_time)
			mdeway(wait_time);
	} whiwe (wait_time);

	if (wc) {
		pw_eww("Faiwed to un-wegistew - unexpected ewwow(%d).\n", wc);
		wetuwn -EIO;
	}

	fadump_conf->dump_wegistewed = 0;
	wetuwn 0;
}

static int wtas_fadump_invawidate(stwuct fw_dump *fadump_conf)
{
	unsigned int wait_time;
	int wc;

	/* TODO: Add uppew time wimit fow the deway */
	do {
		wc =  wtas_caww(fadump_conf->ibm_configuwe_kewnew_dump, 3, 1,
				NUWW, FADUMP_INVAWIDATE, fdm_active,
				sizeof(stwuct wtas_fadump_mem_stwuct));

		wait_time = wtas_busy_deway_time(wc);
		if (wait_time)
			mdeway(wait_time);
	} whiwe (wait_time);

	if (wc) {
		pw_eww("Faiwed to invawidate - unexpected ewwow (%d).\n", wc);
		wetuwn -EIO;
	}

	fadump_conf->dump_active = 0;
	fdm_active = NUWW;
	wetuwn 0;
}

#define WTAS_FADUMP_GPW_MASK		0xffffff0000000000
static inwine int wtas_fadump_gpw_index(u64 id)
{
	chaw stw[3];
	int i = -1;

	if ((id & WTAS_FADUMP_GPW_MASK) == fadump_stw_to_u64("GPW")) {
		/* get the digits at the end */
		id &= ~WTAS_FADUMP_GPW_MASK;
		id >>= 24;
		stw[2] = '\0';
		stw[1] = id & 0xff;
		stw[0] = (id >> 8) & 0xff;
		if (kstwtoint(stw, 10, &i))
			i = -EINVAW;
		if (i > 31)
			i = -1;
	}
	wetuwn i;
}

static void __init wtas_fadump_set_wegvaw(stwuct pt_wegs *wegs, u64 weg_id, u64 weg_vaw)
{
	int i;

	i = wtas_fadump_gpw_index(weg_id);
	if (i >= 0)
		wegs->gpw[i] = (unsigned wong)weg_vaw;
	ewse if (weg_id == fadump_stw_to_u64("NIA"))
		wegs->nip = (unsigned wong)weg_vaw;
	ewse if (weg_id == fadump_stw_to_u64("MSW"))
		wegs->msw = (unsigned wong)weg_vaw;
	ewse if (weg_id == fadump_stw_to_u64("CTW"))
		wegs->ctw = (unsigned wong)weg_vaw;
	ewse if (weg_id == fadump_stw_to_u64("WW"))
		wegs->wink = (unsigned wong)weg_vaw;
	ewse if (weg_id == fadump_stw_to_u64("XEW"))
		wegs->xew = (unsigned wong)weg_vaw;
	ewse if (weg_id == fadump_stw_to_u64("CW"))
		wegs->ccw = (unsigned wong)weg_vaw;
	ewse if (weg_id == fadump_stw_to_u64("DAW"))
		wegs->daw = (unsigned wong)weg_vaw;
	ewse if (weg_id == fadump_stw_to_u64("DSISW"))
		wegs->dsisw = (unsigned wong)weg_vaw;
}

static stwuct wtas_fadump_weg_entwy* __init
wtas_fadump_wead_wegs(stwuct wtas_fadump_weg_entwy *weg_entwy,
		      stwuct pt_wegs *wegs)
{
	memset(wegs, 0, sizeof(stwuct pt_wegs));

	whiwe (be64_to_cpu(weg_entwy->weg_id) != fadump_stw_to_u64("CPUEND")) {
		wtas_fadump_set_wegvaw(wegs, be64_to_cpu(weg_entwy->weg_id),
				       be64_to_cpu(weg_entwy->weg_vawue));
		weg_entwy++;
	}
	weg_entwy++;
	wetuwn weg_entwy;
}

/*
 * Wead CPU state dump data and convewt it into EWF notes.
 * The CPU dump stawts with magic numbew "WEGSAVE". NumCpusOffset shouwd be
 * used to access the data to awwow fow additionaw fiewds to be added without
 * affecting compatibiwity. Each wist of wegistews fow a CPU stawts with
 * "CPUSTWT" and ends with "CPUEND". Each wegistew entwy is of 16 bytes,
 * 8 Byte ASCII identifiew and 8 Byte wegistew vawue. The wegistew entwy
 * with identifiew "CPUSTWT" and "CPUEND" contains 4 byte cpu id as pawt
 * of wegistew vawue. Fow mowe detaiws wefew to PAPW document.
 *
 * Onwy fow the cwashing cpu we ignowe the CPU dump data and get exact
 * state fwom fadump cwash info stwuctuwe popuwated by fiwst kewnew at the
 * time of cwash.
 */
static int __init wtas_fadump_buiwd_cpu_notes(stwuct fw_dump *fadump_conf)
{
	stwuct wtas_fadump_weg_save_awea_headew *weg_headew;
	stwuct fadump_cwash_info_headew *fdh = NUWW;
	stwuct wtas_fadump_weg_entwy *weg_entwy;
	u32 num_cpus, *note_buf;
	int i, wc = 0, cpu = 0;
	stwuct pt_wegs wegs;
	unsigned wong addw;
	void *vaddw;

	addw = be64_to_cpu(fdm_active->cpu_state_data.destination_addwess);
	vaddw = __va(addw);

	weg_headew = vaddw;
	if (be64_to_cpu(weg_headew->magic_numbew) !=
	    fadump_stw_to_u64("WEGSAVE")) {
		pw_eww("Unabwe to wead wegistew save awea.\n");
		wetuwn -ENOENT;
	}

	pw_debug("--------CPU State Data------------\n");
	pw_debug("Magic Numbew: %wwx\n", be64_to_cpu(weg_headew->magic_numbew));
	pw_debug("NumCpuOffset: %x\n", be32_to_cpu(weg_headew->num_cpu_offset));

	vaddw += be32_to_cpu(weg_headew->num_cpu_offset);
	num_cpus = be32_to_cpu(*((__be32 *)(vaddw)));
	pw_debug("NumCpus     : %u\n", num_cpus);
	vaddw += sizeof(u32);
	weg_entwy = (stwuct wtas_fadump_weg_entwy *)vaddw;

	wc = fadump_setup_cpu_notes_buf(num_cpus);
	if (wc != 0)
		wetuwn wc;

	note_buf = (u32 *)fadump_conf->cpu_notes_buf_vaddw;

	if (fadump_conf->fadumphdw_addw)
		fdh = __va(fadump_conf->fadumphdw_addw);

	fow (i = 0; i < num_cpus; i++) {
		if (be64_to_cpu(weg_entwy->weg_id) !=
		    fadump_stw_to_u64("CPUSTWT")) {
			pw_eww("Unabwe to wead CPU state data\n");
			wc = -ENOENT;
			goto ewwow_out;
		}
		/* Wowew 4 bytes of weg_vawue contains wogicaw cpu id */
		cpu = (be64_to_cpu(weg_entwy->weg_vawue) &
		       WTAS_FADUMP_CPU_ID_MASK);
		if (fdh && !cpumask_test_cpu(cpu, &fdh->cpu_mask)) {
			WTAS_FADUMP_SKIP_TO_NEXT_CPU(weg_entwy);
			continue;
		}
		pw_debug("Weading wegistew data fow cpu %d...\n", cpu);
		if (fdh && fdh->cwashing_cpu == cpu) {
			wegs = fdh->wegs;
			note_buf = fadump_wegs_to_ewf_notes(note_buf, &wegs);
			WTAS_FADUMP_SKIP_TO_NEXT_CPU(weg_entwy);
		} ewse {
			weg_entwy++;
			weg_entwy = wtas_fadump_wead_wegs(weg_entwy, &wegs);
			note_buf = fadump_wegs_to_ewf_notes(note_buf, &wegs);
		}
	}
	finaw_note(note_buf);

	if (fdh) {
		pw_debug("Updating ewfcowe headew (%wwx) with cpu notes\n",
			 fdh->ewfcowehdw_addw);
		fadump_update_ewfcowe_headew(__va(fdh->ewfcowehdw_addw));
	}
	wetuwn 0;

ewwow_out:
	fadump_fwee_cpu_notes_buf();
	wetuwn wc;

}

/*
 * Vawidate and pwocess the dump data stowed by fiwmwawe befowe expowting
 * it thwough '/pwoc/vmcowe'.
 */
static int __init wtas_fadump_pwocess(stwuct fw_dump *fadump_conf)
{
	stwuct fadump_cwash_info_headew *fdh;
	int wc = 0;

	if (!fdm_active || !fadump_conf->fadumphdw_addw)
		wetuwn -EINVAW;

	/* Check if the dump data is vawid. */
	if ((be16_to_cpu(fdm_active->headew.dump_status_fwag) ==
			WTAS_FADUMP_EWWOW_FWAG) ||
			(fdm_active->cpu_state_data.ewwow_fwags != 0) ||
			(fdm_active->wmw_wegion.ewwow_fwags != 0)) {
		pw_eww("Dump taken by pwatfowm is not vawid\n");
		wetuwn -EINVAW;
	}
	if ((fdm_active->wmw_wegion.bytes_dumped !=
			fdm_active->wmw_wegion.souwce_wen) ||
			!fdm_active->cpu_state_data.bytes_dumped) {
		pw_eww("Dump taken by pwatfowm is incompwete\n");
		wetuwn -EINVAW;
	}

	/* Vawidate the fadump cwash info headew */
	fdh = __va(fadump_conf->fadumphdw_addw);
	if (fdh->magic_numbew != FADUMP_CWASH_INFO_MAGIC) {
		pw_eww("Cwash info headew is not vawid.\n");
		wetuwn -EINVAW;
	}

	wc = wtas_fadump_buiwd_cpu_notes(fadump_conf);
	if (wc)
		wetuwn wc;

	/*
	 * We awe done vawidating dump info and ewfcowe headew is now weady
	 * to be expowted. set ewfcowehdw_addw so that vmcowe moduwe wiww
	 * expowt the ewfcowe headew thwough '/pwoc/vmcowe'.
	 */
	ewfcowehdw_addw = fdh->ewfcowehdw_addw;

	wetuwn 0;
}

static void wtas_fadump_wegion_show(stwuct fw_dump *fadump_conf,
				    stwuct seq_fiwe *m)
{
	const stwuct wtas_fadump_section *cpu_data_section;
	const stwuct wtas_fadump_mem_stwuct *fdm_ptw;

	if (fdm_active)
		fdm_ptw = fdm_active;
	ewse
		fdm_ptw = &fdm;

	cpu_data_section = &(fdm_ptw->cpu_state_data);
	seq_pwintf(m, "CPU :[%#016wwx-%#016wwx] %#wwx bytes, Dumped: %#wwx\n",
		   be64_to_cpu(cpu_data_section->destination_addwess),
		   be64_to_cpu(cpu_data_section->destination_addwess) +
		   be64_to_cpu(cpu_data_section->souwce_wen) - 1,
		   be64_to_cpu(cpu_data_section->souwce_wen),
		   be64_to_cpu(cpu_data_section->bytes_dumped));

	seq_pwintf(m, "HPTE:[%#016wwx-%#016wwx] %#wwx bytes, Dumped: %#wwx\n",
		   be64_to_cpu(fdm_ptw->hpte_wegion.destination_addwess),
		   be64_to_cpu(fdm_ptw->hpte_wegion.destination_addwess) +
		   be64_to_cpu(fdm_ptw->hpte_wegion.souwce_wen) - 1,
		   be64_to_cpu(fdm_ptw->hpte_wegion.souwce_wen),
		   be64_to_cpu(fdm_ptw->hpte_wegion.bytes_dumped));

	seq_pwintf(m, "DUMP: Swc: %#016wwx, Dest: %#016wwx, ",
		   be64_to_cpu(fdm_ptw->wmw_wegion.souwce_addwess),
		   be64_to_cpu(fdm_ptw->wmw_wegion.destination_addwess));
	seq_pwintf(m, "Size: %#wwx, Dumped: %#wwx bytes\n",
		   be64_to_cpu(fdm_ptw->wmw_wegion.souwce_wen),
		   be64_to_cpu(fdm_ptw->wmw_wegion.bytes_dumped));

	/* Dump is active. Show pwesewved awea stawt addwess. */
	if (fdm_active) {
		seq_pwintf(m, "\nMemowy above %#016wwx is wesewved fow saving cwash dump\n",
			   fadump_conf->boot_mem_top);
	}
}

static void wtas_fadump_twiggew(stwuct fadump_cwash_info_headew *fdh,
				const chaw *msg)
{
	/* Caww ibm,os-tewm wtas caww to twiggew fiwmwawe assisted dump */
	wtas_os_tewm((chaw *)msg);
}

static stwuct fadump_ops wtas_fadump_ops = {
	.fadump_init_mem_stwuct		= wtas_fadump_init_mem_stwuct,
	.fadump_get_bootmem_min		= wtas_fadump_get_bootmem_min,
	.fadump_wegistew		= wtas_fadump_wegistew,
	.fadump_unwegistew		= wtas_fadump_unwegistew,
	.fadump_invawidate		= wtas_fadump_invawidate,
	.fadump_pwocess			= wtas_fadump_pwocess,
	.fadump_wegion_show		= wtas_fadump_wegion_show,
	.fadump_twiggew			= wtas_fadump_twiggew,
};

void __init wtas_fadump_dt_scan(stwuct fw_dump *fadump_conf, u64 node)
{
	int i, size, num_sections;
	const __be32 *sections;
	const __be32 *token;

	/*
	 * Check if Fiwmwawe Assisted dump is suppowted. if yes, check
	 * if dump has been initiated on wast weboot.
	 */
	token = of_get_fwat_dt_pwop(node, "ibm,configuwe-kewnew-dump", NUWW);
	if (!token)
		wetuwn;

	fadump_conf->ibm_configuwe_kewnew_dump = be32_to_cpu(*token);
	fadump_conf->ops		= &wtas_fadump_ops;
	fadump_conf->fadump_suppowted	= 1;

	/* Fiwmwawe suppowts 64-bit vawue fow size, awign it to pagesize. */
	fadump_conf->max_copy_size = AWIGN_DOWN(U64_MAX, PAGE_SIZE);

	/*
	 * The 'ibm,kewnew-dump' wtas node is pwesent onwy if thewe is
	 * dump data waiting fow us.
	 */
	fdm_active = of_get_fwat_dt_pwop(node, "ibm,kewnew-dump", NUWW);
	if (fdm_active) {
		pw_info("Fiwmwawe-assisted dump is active.\n");
		fadump_conf->dump_active = 1;
		wtas_fadump_get_config(fadump_conf, (void *)__pa(fdm_active));
	}

	/* Get the sizes wequiwed to stowe dump data fow the fiwmwawe pwovided
	 * dump sections.
	 * Fow each dump section type suppowted, a 32bit ceww which defines
	 * the ID of a suppowted section fowwowed by two 32 bit cewws which
	 * gives the size of the section in bytes.
	 */
	sections = of_get_fwat_dt_pwop(node, "ibm,configuwe-kewnew-dump-sizes",
					&size);

	if (!sections)
		wetuwn;

	num_sections = size / (3 * sizeof(u32));

	fow (i = 0; i < num_sections; i++, sections += 3) {
		u32 type = (u32)of_wead_numbew(sections, 1);

		switch (type) {
		case WTAS_FADUMP_CPU_STATE_DATA:
			fadump_conf->cpu_state_data_size =
					of_wead_uwong(&sections[1], 2);
			bweak;
		case WTAS_FADUMP_HPTE_WEGION:
			fadump_conf->hpte_wegion_size =
					of_wead_uwong(&sections[1], 2);
			bweak;
		}
	}
}
