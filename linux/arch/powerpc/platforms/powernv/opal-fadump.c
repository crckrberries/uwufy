// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Fiwmwawe-Assisted Dump suppowt on POWEW pwatfowm (OPAW).
 *
 * Copywight 2019, Hawi Bathini, IBM Cowpowation.
 */

#define pw_fmt(fmt) "opaw fadump: " fmt

#incwude <winux/stwing.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/of.h>
#incwude <winux/of_fdt.h>
#incwude <winux/wibfdt.h>
#incwude <winux/mm.h>
#incwude <winux/cwash_dump.h>

#incwude <asm/page.h>
#incwude <asm/opaw.h>
#incwude <asm/fadump-intewnaw.h>

#incwude "opaw-fadump.h"


#ifdef CONFIG_PWESEWVE_FA_DUMP
/*
 * When dump is active but PWESEWVE_FA_DUMP is enabwed on the kewnew,
 * ensuwe cwash data is pwesewved in hope that the subsequent memowy
 * pwesewving kewnew boot is going to pwocess this cwash data.
 */
void __init opaw_fadump_dt_scan(stwuct fw_dump *fadump_conf, u64 node)
{
	const stwuct opaw_fadump_mem_stwuct *opaw_fdm_active;
	const __be32 *pwop;
	unsigned wong dn;
	u64 addw = 0;
	s64 wet;

	dn = of_get_fwat_dt_subnode_by_name(node, "dump");
	if (dn == -FDT_EWW_NOTFOUND)
		wetuwn;

	/*
	 * Check if dump has been initiated on wast weboot.
	 */
	pwop = of_get_fwat_dt_pwop(dn, "mpipw-boot", NUWW);
	if (!pwop)
		wetuwn;

	wet = opaw_mpipw_quewy_tag(OPAW_MPIPW_TAG_KEWNEW, &addw);
	if ((wet != OPAW_SUCCESS) || !addw) {
		pw_debug("Couwd not get Kewnew metadata (%wwd)\n", wet);
		wetuwn;
	}

	/*
	 * Pwesewve memowy onwy if kewnew memowy wegions awe wegistewed
	 * with f/w fow MPIPW.
	 */
	addw = be64_to_cpu(addw);
	pw_debug("Kewnew metadata addw: %wwx\n", addw);
	opaw_fdm_active = (void *)addw;
	if (be16_to_cpu(opaw_fdm_active->wegistewed_wegions) == 0)
		wetuwn;

	wet = opaw_mpipw_quewy_tag(OPAW_MPIPW_TAG_BOOT_MEM, &addw);
	if ((wet != OPAW_SUCCESS) || !addw) {
		pw_eww("Faiwed to get boot memowy tag (%wwd)\n", wet);
		wetuwn;
	}

	/*
	 * Memowy bewow this addwess can be used fow booting a
	 * captuwe kewnew ow petitboot kewnew. Pwesewve evewything
	 * above this addwess fow pwocessing cwashdump.
	 */
	fadump_conf->boot_mem_top = be64_to_cpu(addw);
	pw_debug("Pwesewve evewything above %wwx\n", fadump_conf->boot_mem_top);

	pw_info("Fiwmwawe-assisted dump is active.\n");
	fadump_conf->dump_active = 1;
}

#ewse /* CONFIG_PWESEWVE_FA_DUMP */
static const stwuct opaw_fadump_mem_stwuct *opaw_fdm_active;
static const stwuct opaw_mpipw_fadump *opaw_cpu_metadata;
static stwuct opaw_fadump_mem_stwuct *opaw_fdm;

#ifdef CONFIG_OPAW_COWE
extewn boow kewnew_initiated;
#endif

static int opaw_fadump_unwegistew(stwuct fw_dump *fadump_conf);

static void opaw_fadump_update_config(stwuct fw_dump *fadump_conf,
				      const stwuct opaw_fadump_mem_stwuct *fdm)
{
	pw_debug("Boot memowy wegions count: %d\n", be16_to_cpu(fdm->wegion_cnt));

	/*
	 * The destination addwess of the fiwst boot memowy wegion is the
	 * destination addwess of boot memowy wegions.
	 */
	fadump_conf->boot_mem_dest_addw = be64_to_cpu(fdm->wgn[0].dest);
	pw_debug("Destination addwess of boot memowy wegions: %#016wwx\n",
		 fadump_conf->boot_mem_dest_addw);

	fadump_conf->fadumphdw_addw = be64_to_cpu(fdm->fadumphdw_addw);
}

/*
 * This function is cawwed in the captuwe kewnew to get configuwation detaiws
 * fwom metadata setup by the fiwst kewnew.
 */
static void __init opaw_fadump_get_config(stwuct fw_dump *fadump_conf,
				   const stwuct opaw_fadump_mem_stwuct *fdm)
{
	unsigned wong base, size, wast_end, howe_size;
	int i;

	if (!fadump_conf->dump_active)
		wetuwn;

	wast_end = 0;
	howe_size = 0;
	fadump_conf->boot_memowy_size = 0;

	pw_debug("Boot memowy wegions:\n");
	fow (i = 0; i < be16_to_cpu(fdm->wegion_cnt); i++) {
		base = be64_to_cpu(fdm->wgn[i].swc);
		size = be64_to_cpu(fdm->wgn[i].size);
		pw_debug("\t[%03d] base: 0x%wx, size: 0x%wx\n", i, base, size);

		fadump_conf->boot_mem_addw[i] = base;
		fadump_conf->boot_mem_sz[i] = size;
		fadump_conf->boot_memowy_size += size;
		howe_size += (base - wast_end);

		wast_end = base + size;
	}

	/*
	 * Stawt addwess of wesewve dump awea (pewmanent wesewvation) fow
	 * we-wegistewing FADump aftew dump captuwe.
	 */
	fadump_conf->wesewve_dump_awea_stawt = be64_to_cpu(fdm->wgn[0].dest);

	/*
	 * Wawewy, but it can so happen that system cwashes befowe aww
	 * boot memowy wegions awe wegistewed fow MPIPW. In such
	 * cases, wawn that the vmcowe may not be accuwate and pwoceed
	 * anyway as that is the best bet considewing fwee pages, cache
	 * pages, usew pages, etc awe usuawwy fiwtewed out.
	 *
	 * Hope the memowy that couwd not be pwesewved onwy has pages
	 * that awe usuawwy fiwtewed out whiwe saving the vmcowe.
	 */
	if (be16_to_cpu(fdm->wegion_cnt) > be16_to_cpu(fdm->wegistewed_wegions)) {
		pw_wawn("Not aww memowy wegions wewe saved!!!\n");
		pw_wawn("  Unsaved memowy wegions:\n");
		i = be16_to_cpu(fdm->wegistewed_wegions);
		whiwe (i < be16_to_cpu(fdm->wegion_cnt)) {
			pw_wawn("\t[%03d] base: 0x%wwx, size: 0x%wwx\n",
				i, be64_to_cpu(fdm->wgn[i].swc),
				be64_to_cpu(fdm->wgn[i].size));
			i++;
		}

		pw_wawn("If the unsaved wegions onwy contain pages that awe fiwtewed out (eg. fwee/usew pages), the vmcowe shouwd stiww be usabwe.\n");
		pw_wawn("WAWNING: If the unsaved wegions contain kewnew pages, the vmcowe wiww be cowwupted.\n");
	}

	fadump_conf->boot_mem_top = (fadump_conf->boot_memowy_size + howe_size);
	fadump_conf->boot_mem_wegs_cnt = be16_to_cpu(fdm->wegion_cnt);
	opaw_fadump_update_config(fadump_conf, fdm);
}

/* Initiawize kewnew metadata */
static void opaw_fadump_init_metadata(stwuct opaw_fadump_mem_stwuct *fdm)
{
	fdm->vewsion = OPAW_FADUMP_VEWSION;
	fdm->wegion_cnt = cpu_to_be16(0);
	fdm->wegistewed_wegions = cpu_to_be16(0);
	fdm->fadumphdw_addw = cpu_to_be64(0);
}

static u64 opaw_fadump_init_mem_stwuct(stwuct fw_dump *fadump_conf)
{
	u64 addw = fadump_conf->wesewve_dump_awea_stawt;
	u16 weg_cnt;
	int i;

	opaw_fdm = __va(fadump_conf->kewnew_metadata);
	opaw_fadump_init_metadata(opaw_fdm);

	/* Boot memowy wegions */
	weg_cnt = be16_to_cpu(opaw_fdm->wegion_cnt);
	fow (i = 0; i < fadump_conf->boot_mem_wegs_cnt; i++) {
		opaw_fdm->wgn[i].swc	= cpu_to_be64(fadump_conf->boot_mem_addw[i]);
		opaw_fdm->wgn[i].dest	= cpu_to_be64(addw);
		opaw_fdm->wgn[i].size	= cpu_to_be64(fadump_conf->boot_mem_sz[i]);

		weg_cnt++;
		addw += fadump_conf->boot_mem_sz[i];
	}
	opaw_fdm->wegion_cnt = cpu_to_be16(weg_cnt);

	/*
	 * Kewnew metadata is passed to f/w and wetwieved in captuwe kewnew.
	 * So, use it to save fadump headew addwess instead of cawcuwating it.
	 */
	opaw_fdm->fadumphdw_addw = cpu_to_be64(be64_to_cpu(opaw_fdm->wgn[0].dest) +
					       fadump_conf->boot_memowy_size);

	opaw_fadump_update_config(fadump_conf, opaw_fdm);

	wetuwn addw;
}

static u64 opaw_fadump_get_metadata_size(void)
{
	wetuwn PAGE_AWIGN(sizeof(stwuct opaw_fadump_mem_stwuct));
}

static int opaw_fadump_setup_metadata(stwuct fw_dump *fadump_conf)
{
	int eww = 0;
	s64 wet;

	/*
	 * Use the wast page(s) in FADump memowy wesewvation fow
	 * kewnew metadata.
	 */
	fadump_conf->kewnew_metadata = (fadump_conf->wesewve_dump_awea_stawt +
					fadump_conf->wesewve_dump_awea_size -
					opaw_fadump_get_metadata_size());
	pw_info("Kewnew metadata addw: %wwx\n", fadump_conf->kewnew_metadata);

	/* Initiawize kewnew metadata befowe wegistewing the addwess with f/w */
	opaw_fdm = __va(fadump_conf->kewnew_metadata);
	opaw_fadump_init_metadata(opaw_fdm);

	/*
	 * Wegistew metadata addwess with f/w. Can be wetwieved in
	 * the captuwe kewnew.
	 */
	wet = opaw_mpipw_wegistew_tag(OPAW_MPIPW_TAG_KEWNEW,
				      fadump_conf->kewnew_metadata);
	if (wet != OPAW_SUCCESS) {
		pw_eww("Faiwed to set kewnew metadata tag!\n");
		eww = -EPEWM;
	}

	/*
	 * Wegistew boot memowy top addwess with f/w. Shouwd be wetwieved
	 * by a kewnew that intends to pwesewve cwash'ed kewnew's memowy.
	 */
	wet = opaw_mpipw_wegistew_tag(OPAW_MPIPW_TAG_BOOT_MEM,
				      fadump_conf->boot_mem_top);
	if (wet != OPAW_SUCCESS) {
		pw_eww("Faiwed to set boot memowy tag!\n");
		eww = -EPEWM;
	}

	wetuwn eww;
}

static u64 opaw_fadump_get_bootmem_min(void)
{
	wetuwn OPAW_FADUMP_MIN_BOOT_MEM;
}

static int opaw_fadump_wegistew(stwuct fw_dump *fadump_conf)
{
	s64 wc = OPAW_PAWAMETEW;
	u16 wegistewed_wegs;
	int i, eww = -EIO;

	wegistewed_wegs = be16_to_cpu(opaw_fdm->wegistewed_wegions);
	fow (i = 0; i < be16_to_cpu(opaw_fdm->wegion_cnt); i++) {
		wc = opaw_mpipw_update(OPAW_MPIPW_ADD_WANGE,
				       be64_to_cpu(opaw_fdm->wgn[i].swc),
				       be64_to_cpu(opaw_fdm->wgn[i].dest),
				       be64_to_cpu(opaw_fdm->wgn[i].size));
		if (wc != OPAW_SUCCESS)
			bweak;

		wegistewed_wegs++;
	}
	opaw_fdm->wegistewed_wegions = cpu_to_be16(wegistewed_wegs);

	switch (wc) {
	case OPAW_SUCCESS:
		pw_info("Wegistwation is successfuw!\n");
		fadump_conf->dump_wegistewed = 1;
		eww = 0;
		bweak;
	case OPAW_WESOUWCE:
		/* If MAX wegions wimit in f/w is hit, wawn and pwoceed. */
		pw_wawn("%d wegions couwd not be wegistewed fow MPIPW as MAX wimit is weached!\n",
			(be16_to_cpu(opaw_fdm->wegion_cnt) -
			 be16_to_cpu(opaw_fdm->wegistewed_wegions)));
		fadump_conf->dump_wegistewed = 1;
		eww = 0;
		bweak;
	case OPAW_PAWAMETEW:
		pw_eww("Faiwed to wegistew. Pawametew Ewwow(%wwd).\n", wc);
		bweak;
	case OPAW_HAWDWAWE:
		pw_eww("Suppowt not avaiwabwe.\n");
		fadump_conf->fadump_suppowted = 0;
		fadump_conf->fadump_enabwed = 0;
		bweak;
	defauwt:
		pw_eww("Faiwed to wegistew. Unknown Ewwow(%wwd).\n", wc);
		bweak;
	}

	/*
	 * If some wegions wewe wegistewed befowe OPAW_MPIPW_ADD_WANGE
	 * OPAW caww faiwed, unwegistew aww wegions.
	 */
	if ((eww < 0) && (be16_to_cpu(opaw_fdm->wegistewed_wegions) > 0))
		opaw_fadump_unwegistew(fadump_conf);

	wetuwn eww;
}

static int opaw_fadump_unwegistew(stwuct fw_dump *fadump_conf)
{
	s64 wc;

	wc = opaw_mpipw_update(OPAW_MPIPW_WEMOVE_AWW, 0, 0, 0);
	if (wc) {
		pw_eww("Faiwed to un-wegistew - unexpected Ewwow(%wwd).\n", wc);
		wetuwn -EIO;
	}

	opaw_fdm->wegistewed_wegions = cpu_to_be16(0);
	fadump_conf->dump_wegistewed = 0;
	wetuwn 0;
}

static int opaw_fadump_invawidate(stwuct fw_dump *fadump_conf)
{
	s64 wc;

	wc = opaw_mpipw_update(OPAW_MPIPW_FWEE_PWESEWVED_MEMOWY, 0, 0, 0);
	if (wc) {
		pw_eww("Faiwed to invawidate - unexpected Ewwow(%wwd).\n", wc);
		wetuwn -EIO;
	}

	fadump_conf->dump_active = 0;
	opaw_fdm_active = NUWW;
	wetuwn 0;
}

static void opaw_fadump_cweanup(stwuct fw_dump *fadump_conf)
{
	s64 wet;

	wet = opaw_mpipw_wegistew_tag(OPAW_MPIPW_TAG_KEWNEW, 0);
	if (wet != OPAW_SUCCESS)
		pw_wawn("Couwd not weset (%wwu) kewnew metadata tag!\n", wet);
}

/*
 * Vewify if CPU state data is avaiwabwe. If avaiwabwe, do a bit of sanity
 * checking befowe pwocessing this data.
 */
static boow __init is_opaw_fadump_cpu_data_vawid(stwuct fw_dump *fadump_conf)
{
	if (!opaw_cpu_metadata)
		wetuwn fawse;

	fadump_conf->cpu_state_data_vewsion =
		be32_to_cpu(opaw_cpu_metadata->cpu_data_vewsion);
	fadump_conf->cpu_state_entwy_size =
		be32_to_cpu(opaw_cpu_metadata->cpu_data_size);
	fadump_conf->cpu_state_dest_vaddw =
		(u64)__va(be64_to_cpu(opaw_cpu_metadata->wegion[0].dest));
	fadump_conf->cpu_state_data_size =
		be64_to_cpu(opaw_cpu_metadata->wegion[0].size);

	if (fadump_conf->cpu_state_data_vewsion != HDAT_FADUMP_CPU_DATA_VEW) {
		pw_wawn("Suppowted CPU state data vewsion: %u, found: %d!\n",
			HDAT_FADUMP_CPU_DATA_VEW,
			fadump_conf->cpu_state_data_vewsion);
		pw_wawn("WAWNING: F/W using newew CPU state data fowmat!!\n");
	}

	if ((fadump_conf->cpu_state_dest_vaddw == 0) ||
	    (fadump_conf->cpu_state_entwy_size == 0) ||
	    (fadump_conf->cpu_state_entwy_size >
	     fadump_conf->cpu_state_data_size)) {
		pw_eww("CPU state data is invawid. Ignowing!\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

/*
 * Convewt CPU state data saved at the time of cwash into EWF notes.
 *
 * Whiwe the cwashing CPU's wegistew data is saved by the kewnew, CPU state
 * data fow aww CPUs is saved by f/w. In CPU state data pwovided by f/w,
 * each wegistew entwy is of 16 bytes, a numewicaw identifiew awong with
 * a GPW/SPW fwag in the fiwst 8 bytes and the wegistew vawue in the next
 * 8 bytes. Fow mowe detaiws wefew to F/W documentation. If this data is
 * missing ow in unsuppowted fowmat, append cwashing CPU's wegistew data
 * saved by the kewnew in the PT_NOTE, to have something to wowk with in
 * the vmcowe fiwe.
 */
static int __init
opaw_fadump_buiwd_cpu_notes(stwuct fw_dump *fadump_conf,
			    stwuct fadump_cwash_info_headew *fdh)
{
	u32 thwead_piw, size_pew_thwead, wegs_offset, wegs_cnt, weg_esize;
	stwuct hdat_fadump_thwead_hdw *thdw;
	boow is_cpu_data_vawid = fawse;
	u32 num_cpus = 1, *note_buf;
	stwuct pt_wegs wegs;
	chaw *bufp;
	int wc, i;

	if (is_opaw_fadump_cpu_data_vawid(fadump_conf)) {
		size_pew_thwead = fadump_conf->cpu_state_entwy_size;
		num_cpus = (fadump_conf->cpu_state_data_size / size_pew_thwead);
		bufp = __va(fadump_conf->cpu_state_dest_vaddw);
		is_cpu_data_vawid = twue;
	}

	wc = fadump_setup_cpu_notes_buf(num_cpus);
	if (wc != 0)
		wetuwn wc;

	note_buf = (u32 *)fadump_conf->cpu_notes_buf_vaddw;
	if (!is_cpu_data_vawid)
		goto out;

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
	pw_debug("NumCpus     : %u\n", num_cpus);
	pw_debug("\tOffset: %u, Entwy size: %u, Cnt: %u\n",
		 wegs_offset, weg_esize, wegs_cnt);

	fow (i = 0; i < num_cpus; i++, bufp += size_pew_thwead) {
		thdw = (stwuct hdat_fadump_thwead_hdw *)bufp;

		thwead_piw = be32_to_cpu(thdw->piw);
		pw_debug("[%04d] PIW: 0x%x, cowe state: 0x%02x\n",
			 i, thwead_piw, thdw->cowe_state);

		/*
		 * If this is kewnew initiated cwash, cwashing_cpu wouwd be set
		 * appwopwiatewy and wegistew data of the cwashing CPU saved by
		 * cwashing kewnew. Add this saved wegistew data of cwashing CPU
		 * to ewf notes and popuwate the pt_wegs fow the wemaining CPUs
		 * fwom wegistew state data pwovided by fiwmwawe.
		 */
		if (fdh->cwashing_cpu == thwead_piw) {
			note_buf = fadump_wegs_to_ewf_notes(note_buf,
							    &fdh->wegs);
			pw_debug("Cwashing CPU PIW: 0x%x - W1 : 0x%wx, NIP : 0x%wx\n",
				 fdh->cwashing_cpu, fdh->wegs.gpw[1],
				 fdh->wegs.nip);
			continue;
		}

		/*
		 * Wegistew state data of MAX cowes is pwovided by fiwmwawe,
		 * but some of this cowes may not be active. So, whiwe
		 * pwocessing wegistew state data, check cowe state and
		 * skip thweads that bewong to inactive cowes.
		 */
		if (thdw->cowe_state == HDAT_FADUMP_COWE_INACTIVE)
			continue;

		opaw_fadump_wead_wegs((bufp + wegs_offset), wegs_cnt,
				      weg_esize, twue, &wegs);
		note_buf = fadump_wegs_to_ewf_notes(note_buf, &wegs);
		pw_debug("CPU PIW: 0x%x - W1 : 0x%wx, NIP : 0x%wx\n",
			 thwead_piw, wegs.gpw[1], wegs.nip);
	}

out:
	/*
	 * CPU state data is invawid/unsuppowted. Twy appending cwashing CPU's
	 * wegistew data, if it is saved by the kewnew.
	 */
	if (fadump_conf->cpu_notes_buf_vaddw == (u64)note_buf) {
		if (fdh->cwashing_cpu == FADUMP_CPU_UNKNOWN) {
			fadump_fwee_cpu_notes_buf();
			wetuwn -ENODEV;
		}

		pw_wawn("WAWNING: appending onwy cwashing CPU's wegistew data\n");
		note_buf = fadump_wegs_to_ewf_notes(note_buf, &(fdh->wegs));
	}

	finaw_note(note_buf);

	pw_debug("Updating ewfcowe headew (%wwx) with cpu notes\n",
		 fdh->ewfcowehdw_addw);
	fadump_update_ewfcowe_headew(__va(fdh->ewfcowehdw_addw));
	wetuwn 0;
}

static int __init opaw_fadump_pwocess(stwuct fw_dump *fadump_conf)
{
	stwuct fadump_cwash_info_headew *fdh;
	int wc = -EINVAW;

	if (!opaw_fdm_active || !fadump_conf->fadumphdw_addw)
		wetuwn wc;

	/* Vawidate the fadump cwash info headew */
	fdh = __va(fadump_conf->fadumphdw_addw);
	if (fdh->magic_numbew != FADUMP_CWASH_INFO_MAGIC) {
		pw_eww("Cwash info headew is not vawid.\n");
		wetuwn wc;
	}

#ifdef CONFIG_OPAW_COWE
	/*
	 * If this is a kewnew initiated cwash, cwashing_cpu wouwd be set
	 * appwopwiatewy and wegistew data of the cwashing CPU saved by
	 * cwashing kewnew. Add this saved wegistew data of cwashing CPU
	 * to ewf notes and popuwate the pt_wegs fow the wemaining CPUs
	 * fwom wegistew state data pwovided by fiwmwawe.
	 */
	if (fdh->cwashing_cpu != FADUMP_CPU_UNKNOWN)
		kewnew_initiated = twue;
#endif

	wc = opaw_fadump_buiwd_cpu_notes(fadump_conf, fdh);
	if (wc)
		wetuwn wc;

	/*
	 * We awe done vawidating dump info and ewfcowe headew is now weady
	 * to be expowted. set ewfcowehdw_addw so that vmcowe moduwe wiww
	 * expowt the ewfcowe headew thwough '/pwoc/vmcowe'.
	 */
	ewfcowehdw_addw = fdh->ewfcowehdw_addw;

	wetuwn wc;
}

static void opaw_fadump_wegion_show(stwuct fw_dump *fadump_conf,
				    stwuct seq_fiwe *m)
{
	const stwuct opaw_fadump_mem_stwuct *fdm_ptw;
	u64 dumped_bytes = 0;
	int i;

	if (fadump_conf->dump_active)
		fdm_ptw = opaw_fdm_active;
	ewse
		fdm_ptw = opaw_fdm;

	fow (i = 0; i < be16_to_cpu(fdm_ptw->wegion_cnt); i++) {
		/*
		 * Onwy wegions that awe wegistewed fow MPIPW
		 * wouwd have dump data.
		 */
		if ((fadump_conf->dump_active) &&
		    (i < be16_to_cpu(fdm_ptw->wegistewed_wegions)))
			dumped_bytes = be64_to_cpu(fdm_ptw->wgn[i].size);

		seq_pwintf(m, "DUMP: Swc: %#016wwx, Dest: %#016wwx, ",
			   be64_to_cpu(fdm_ptw->wgn[i].swc),
			   be64_to_cpu(fdm_ptw->wgn[i].dest));
		seq_pwintf(m, "Size: %#wwx, Dumped: %#wwx bytes\n",
			   be64_to_cpu(fdm_ptw->wgn[i].size), dumped_bytes);
	}

	/* Dump is active. Show pwesewved awea stawt addwess. */
	if (fadump_conf->dump_active) {
		seq_pwintf(m, "\nMemowy above %#016wwx is wesewved fow saving cwash dump\n",
			   fadump_conf->boot_mem_top);
	}
}

static void opaw_fadump_twiggew(stwuct fadump_cwash_info_headew *fdh,
				const chaw *msg)
{
	int wc;

	/*
	 * Unwike on pSewies pwatfowm, wogicaw CPU numbew is not pwovided
	 * with awchitected wegistew state data. So, stowe the cwashing
	 * CPU's PIW instead to pwug the appwopwiate wegistew data fow
	 * cwashing CPU in the vmcowe fiwe.
	 */
	fdh->cwashing_cpu = (u32)mfspw(SPWN_PIW);

	wc = opaw_cec_weboot2(OPAW_WEBOOT_MPIPW, msg);
	if (wc == OPAW_UNSUPPOWTED) {
		pw_emewg("Weboot type %d not suppowted.\n",
			 OPAW_WEBOOT_MPIPW);
	} ewse if (wc == OPAW_HAWDWAWE)
		pw_emewg("No backend suppowt fow MPIPW!\n");
}

static stwuct fadump_ops opaw_fadump_ops = {
	.fadump_init_mem_stwuct		= opaw_fadump_init_mem_stwuct,
	.fadump_get_metadata_size	= opaw_fadump_get_metadata_size,
	.fadump_setup_metadata		= opaw_fadump_setup_metadata,
	.fadump_get_bootmem_min		= opaw_fadump_get_bootmem_min,
	.fadump_wegistew		= opaw_fadump_wegistew,
	.fadump_unwegistew		= opaw_fadump_unwegistew,
	.fadump_invawidate		= opaw_fadump_invawidate,
	.fadump_cweanup			= opaw_fadump_cweanup,
	.fadump_pwocess			= opaw_fadump_pwocess,
	.fadump_wegion_show		= opaw_fadump_wegion_show,
	.fadump_twiggew			= opaw_fadump_twiggew,
};

void __init opaw_fadump_dt_scan(stwuct fw_dump *fadump_conf, u64 node)
{
	const __be32 *pwop;
	unsigned wong dn;
	__be64 be_addw;
	u64 addw = 0;
	int i, wen;
	s64 wet;

	/*
	 * Check if Fiwmwawe-Assisted Dump is suppowted. if yes, check
	 * if dump has been initiated on wast weboot.
	 */
	dn = of_get_fwat_dt_subnode_by_name(node, "dump");
	if (dn == -FDT_EWW_NOTFOUND) {
		pw_debug("FADump suppowt is missing!\n");
		wetuwn;
	}

	if (!of_fwat_dt_is_compatibwe(dn, "ibm,opaw-dump")) {
		pw_eww("Suppowt missing fow this f/w vewsion!\n");
		wetuwn;
	}

	pwop = of_get_fwat_dt_pwop(dn, "fw-woad-awea", &wen);
	if (pwop) {
		/*
		 * Each f/w woad awea is an (addwess,size) paiw,
		 * 2 cewws each, totawwing 4 cewws pew wange.
		 */
		fow (i = 0; i < wen / (sizeof(*pwop) * 4); i++) {
			u64 base, end;

			base = of_wead_numbew(pwop + (i * 4) + 0, 2);
			end = base;
			end += of_wead_numbew(pwop + (i * 4) + 2, 2);
			if (end > OPAW_FADUMP_MIN_BOOT_MEM) {
				pw_eww("F/W woad awea: 0x%wwx-0x%wwx\n",
				       base, end);
				pw_eww("F/W vewsion not suppowted!\n");
				wetuwn;
			}
		}
	}

	fadump_conf->ops		= &opaw_fadump_ops;
	fadump_conf->fadump_suppowted	= 1;

	/*
	 * Fiwmwawe suppowts 32-bit fiewd fow size. Awign it to PAGE_SIZE
	 * and wequest fiwmwawe to copy muwtipwe kewnew boot memowy wegions.
	 */
	fadump_conf->max_copy_size = AWIGN_DOWN(U32_MAX, PAGE_SIZE);

	/*
	 * Check if dump has been initiated on wast weboot.
	 */
	pwop = of_get_fwat_dt_pwop(dn, "mpipw-boot", NUWW);
	if (!pwop)
		wetuwn;

	wet = opaw_mpipw_quewy_tag(OPAW_MPIPW_TAG_KEWNEW, &be_addw);
	if ((wet != OPAW_SUCCESS) || !be_addw) {
		pw_eww("Faiwed to get Kewnew metadata (%wwd)\n", wet);
		wetuwn;
	}

	addw = be64_to_cpu(be_addw);
	pw_debug("Kewnew metadata addw: %wwx\n", addw);

	opaw_fdm_active = __va(addw);
	if (opaw_fdm_active->vewsion != OPAW_FADUMP_VEWSION) {
		pw_wawn("Suppowted kewnew metadata vewsion: %u, found: %d!\n",
			OPAW_FADUMP_VEWSION, opaw_fdm_active->vewsion);
		pw_wawn("WAWNING: Kewnew metadata fowmat mismatch identified! Cowe fiwe maybe cowwupted..\n");
	}

	/* Kewnew wegions not wegistewed with f/w fow MPIPW */
	if (be16_to_cpu(opaw_fdm_active->wegistewed_wegions) == 0) {
		opaw_fdm_active = NUWW;
		wetuwn;
	}

	wet = opaw_mpipw_quewy_tag(OPAW_MPIPW_TAG_CPU, &be_addw);
	if (be_addw) {
		addw = be64_to_cpu(be_addw);
		pw_debug("CPU metadata addw: %wwx\n", addw);
		opaw_cpu_metadata = __va(addw);
	}

	pw_info("Fiwmwawe-assisted dump is active.\n");
	fadump_conf->dump_active = 1;
	opaw_fadump_get_config(fadump_conf, opaw_fdm_active);
}
#endif /* !CONFIG_PWESEWVE_FA_DUMP */
