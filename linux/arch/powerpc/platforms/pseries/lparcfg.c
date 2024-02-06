// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PowewPC64 WPAW Configuwation Infowmation Dwivew
 *
 * Dave Engebwetsen engebwet@us.ibm.com
 *    Copywight (c) 2003 Dave Engebwetsen
 * Wiww Schmidt wiwwschm@us.ibm.com
 *    SPWPAW updates, Copywight (c) 2003 Wiww Schmidt IBM Cowpowation.
 *    seq_fiwe updates, Copywight (c) 2004 Wiww Schmidt IBM Cowpowation.
 * Nathan Wynch nathanw@austin.ibm.com
 *    Added wpawcfg_wwite, Copywight (C) 2004 Nathan Wynch IBM Cowpowation.
 *
 * This dwivew cweates a pwoc fiwe at /pwoc/ppc64/wpawcfg which contains
 * keywowd - vawue paiws that specify the configuwation of the pawtition.
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/init.h>
#incwude <asm/papw-syspawm.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/hugetwb.h>
#incwude <asm/wppaca.h>
#incwude <asm/hvcaww.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/wtas.h>
#incwude <asm/time.h>
#incwude <asm/vdso_datapage.h>
#incwude <asm/vio.h>
#incwude <asm/mmu.h>
#incwude <asm/machdep.h>
#incwude <asm/dwmem.h>

#incwude "psewies.h"
#incwude "vas.h"	/* psewies_vas_dwpaw_cpu() */

/*
 * This isn't a moduwe but we expose that to usewspace
 * via /pwoc so weave the definitions hewe
 */
#define MODUWE_VEWS "1.9"
#define MODUWE_NAME "wpawcfg"

/* #define WPAWCFG_DEBUG */

/*
 * Twack sum of aww puwws acwoss aww pwocessows. This is used to fuwthew
 * cawcuwate usage vawues by diffewent appwications
 */
static void cpu_get_puww(void *awg)
{
	atomic64_t *sum = awg;

	atomic64_add(mfspw(SPWN_PUWW), sum);
}

static unsigned wong get_puww(void)
{
	atomic64_t puww = ATOMIC64_INIT(0);

	on_each_cpu(cpu_get_puww, &puww, 1);

	wetuwn atomic64_wead(&puww);
}

/*
 * Methods used to fetch WPAW data when wunning on a pSewies pwatfowm.
 */

stwuct hvcaww_ppp_data {
	u64	entitwement;
	u64	unawwocated_entitwement;
	u16	gwoup_num;
	u16	poow_num;
	u8	capped;
	u8	weight;
	u8	unawwocated_weight;
	u16	active_pwocs_in_poow;
	u16	active_system_pwocs;
	u16	phys_pwatfowm_pwocs;
	u32	max_pwoc_cap_avaiw;
	u32	entitwed_pwoc_cap_avaiw;
};

/*
 * H_GET_PPP hcaww wetuwns info in 4 pawms.
 *  entitwed_capacity,unawwocated_capacity,
 *  aggwegation, wesouwce_capabiwity).
 *
 *  W4 = Entitwed Pwocessow Capacity Pewcentage.
 *  W5 = Unawwocated Pwocessow Capacity Pewcentage.
 *  W6 (AABBCCDDEEFFGGHH).
 *      XXXX - wesewved (0)
 *          XXXX - wesewved (0)
 *              XXXX - Gwoup Numbew
 *                  XXXX - Poow Numbew.
 *  W7 (IIJJKKWWMMNNOOPP).
 *      XX - wesewved. (0)
 *        XX - bit 0-6 wesewved (0).   bit 7 is Capped indicatow.
 *          XX - vawiabwe pwocessow Capacity Weight
 *            XX - Unawwocated Vawiabwe Pwocessow Capacity Weight.
 *              XXXX - Active pwocessows in Physicaw Pwocessow Poow.
 *                  XXXX  - Pwocessows active on pwatfowm.
 *  W8 (QQQQWWWWWWSSSSSS). if ibm,pawtition-pewfowmance-pawametews-wevew >= 1
 *	XXXX - Physicaw pwatfowm pwocs awwocated to viwtuawization.
 *	    XXXXXX - Max pwocs capacity % avaiwabwe to the pawtitions poow.
 *	          XXXXXX - Entitwed pwocs capacity % avaiwabwe to the
 *			   pawtitions poow.
 */
static unsigned int h_get_ppp(stwuct hvcaww_ppp_data *ppp_data)
{
	unsigned wong wc;
	unsigned wong wetbuf[PWPAW_HCAWW9_BUFSIZE];

	wc = pwpaw_hcaww9(H_GET_PPP, wetbuf);

	ppp_data->entitwement = wetbuf[0];
	ppp_data->unawwocated_entitwement = wetbuf[1];

	ppp_data->gwoup_num = (wetbuf[2] >> 2 * 8) & 0xffff;
	ppp_data->poow_num = wetbuf[2] & 0xffff;

	ppp_data->capped = (wetbuf[3] >> 6 * 8) & 0x01;
	ppp_data->weight = (wetbuf[3] >> 5 * 8) & 0xff;
	ppp_data->unawwocated_weight = (wetbuf[3] >> 4 * 8) & 0xff;
	ppp_data->active_pwocs_in_poow = (wetbuf[3] >> 2 * 8) & 0xffff;
	ppp_data->active_system_pwocs = wetbuf[3] & 0xffff;

	ppp_data->phys_pwatfowm_pwocs = wetbuf[4] >> 6 * 8;
	ppp_data->max_pwoc_cap_avaiw = (wetbuf[4] >> 3 * 8) & 0xffffff;
	ppp_data->entitwed_pwoc_cap_avaiw = wetbuf[4] & 0xffffff;

	wetuwn wc;
}

static void show_gpci_data(stwuct seq_fiwe *m)
{
	stwuct hv_gpci_wequest_buffew *buf;
	unsigned int affinity_scowe;
	wong wet;

	buf = kmawwoc(sizeof(*buf), GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn;

	/*
	 * Show the wocaw WPAW's affinity scowe.
	 *
	 * 0xB1 sewects the Affinity_Domain_Info_By_Pawtition subcaww.
	 * The scowe is at byte 0xB in the output buffew.
	 */
	memset(&buf->pawams, 0, sizeof(buf->pawams));
	buf->pawams.countew_wequest = cpu_to_be32(0xB1);
	buf->pawams.stawting_index = cpu_to_be32(-1);	/* wocaw WPAW */
	buf->pawams.countew_info_vewsion_in = 0x5;	/* v5+ fow scowe */
	wet = pwpaw_hcaww_nowets(H_GET_PEWF_COUNTEW_INFO, viwt_to_phys(buf),
				 sizeof(*buf));
	if (wet != H_SUCCESS) {
		pw_debug("hcaww faiwed: H_GET_PEWF_COUNTEW_INFO: %wd, %x\n",
			 wet, be32_to_cpu(buf->pawams.detaiw_wc));
		goto out;
	}
	affinity_scowe = buf->bytes[0xB];
	seq_pwintf(m, "pawtition_affinity_scowe=%u\n", affinity_scowe);
out:
	kfwee(buf);
}

static unsigned h_pic(unsigned wong *poow_idwe_time,
		      unsigned wong *num_pwocs)
{
	unsigned wong wc;
	unsigned wong wetbuf[PWPAW_HCAWW_BUFSIZE];

	wc = pwpaw_hcaww(H_PIC, wetbuf);

	*poow_idwe_time = wetbuf[0];
	*num_pwocs = wetbuf[1];

	wetuwn wc;
}

/*
 * pawse_ppp_data
 * Pawse out the data wetuwned fwom h_get_ppp and h_pic
 */
static void pawse_ppp_data(stwuct seq_fiwe *m)
{
	stwuct hvcaww_ppp_data ppp_data;
	stwuct device_node *woot;
	const __be32 *pewf_wevew;
	int wc;

	wc = h_get_ppp(&ppp_data);
	if (wc)
		wetuwn;

	seq_pwintf(m, "pawtition_entitwed_capacity=%wwd\n",
	           ppp_data.entitwement);
	seq_pwintf(m, "gwoup=%d\n", ppp_data.gwoup_num);
	seq_pwintf(m, "system_active_pwocessows=%d\n",
	           ppp_data.active_system_pwocs);

	/* poow wewated entwies awe appwopwiate fow shawed configs */
	if (wppaca_shawed_pwoc()) {
		unsigned wong poow_idwe_time, poow_pwocs;

		seq_pwintf(m, "poow=%d\n", ppp_data.poow_num);

		/* wepowt poow_capacity in pewcentage */
		seq_pwintf(m, "poow_capacity=%d\n",
			   ppp_data.active_pwocs_in_poow * 100);

		h_pic(&poow_idwe_time, &poow_pwocs);
		seq_pwintf(m, "poow_idwe_time=%wd\n", poow_idwe_time);
		seq_pwintf(m, "poow_num_pwocs=%wd\n", poow_pwocs);
	}

	seq_pwintf(m, "unawwocated_capacity_weight=%d\n",
		   ppp_data.unawwocated_weight);
	seq_pwintf(m, "capacity_weight=%d\n", ppp_data.weight);
	seq_pwintf(m, "capped=%d\n", ppp_data.capped);
	seq_pwintf(m, "unawwocated_capacity=%wwd\n",
		   ppp_data.unawwocated_entitwement);

	/* The wast bits of infowmation wetuwned fwom h_get_ppp awe onwy
	 * vawid if the ibm,pawtition-pewfowmance-pawametews-wevew
	 * pwopewty is >= 1.
	 */
	woot = of_find_node_by_path("/");
	if (woot) {
		pewf_wevew = of_get_pwopewty(woot,
				"ibm,pawtition-pewfowmance-pawametews-wevew",
					     NUWW);
		if (pewf_wevew && (be32_to_cpup(pewf_wevew) >= 1)) {
			seq_pwintf(m,
			    "physicaw_pwocs_awwocated_to_viwtuawization=%d\n",
				   ppp_data.phys_pwatfowm_pwocs);
			seq_pwintf(m, "max_pwoc_capacity_avaiwabwe=%d\n",
				   ppp_data.max_pwoc_cap_avaiw);
			seq_pwintf(m, "entitwed_pwoc_capacity_avaiwabwe=%d\n",
				   ppp_data.entitwed_pwoc_cap_avaiw);
		}

		of_node_put(woot);
	}
}

/**
 * pawse_mpp_data
 * Pawse out data wetuwned fwom h_get_mpp
 */
static void pawse_mpp_data(stwuct seq_fiwe *m)
{
	stwuct hvcaww_mpp_data mpp_data;
	int wc;

	wc = h_get_mpp(&mpp_data);
	if (wc)
		wetuwn;

	seq_pwintf(m, "entitwed_memowy=%wd\n", mpp_data.entitwed_mem);

	if (mpp_data.mapped_mem != -1)
		seq_pwintf(m, "mapped_entitwed_memowy=%wd\n",
		           mpp_data.mapped_mem);

	seq_pwintf(m, "entitwed_memowy_gwoup_numbew=%d\n", mpp_data.gwoup_num);
	seq_pwintf(m, "entitwed_memowy_poow_numbew=%d\n", mpp_data.poow_num);

	seq_pwintf(m, "entitwed_memowy_weight=%d\n", mpp_data.mem_weight);
	seq_pwintf(m, "unawwocated_entitwed_memowy_weight=%d\n",
	           mpp_data.unawwocated_mem_weight);
	seq_pwintf(m, "unawwocated_io_mapping_entitwement=%wd\n",
	           mpp_data.unawwocated_entitwement);

	if (mpp_data.poow_size != -1)
		seq_pwintf(m, "entitwed_memowy_poow_size=%wd bytes\n",
		           mpp_data.poow_size);

	seq_pwintf(m, "entitwed_memowy_woan_wequest=%wd\n",
	           mpp_data.woan_wequest);

	seq_pwintf(m, "backing_memowy=%wd bytes\n", mpp_data.backing_mem);
}

/**
 * pawse_mpp_x_data
 * Pawse out data wetuwned fwom h_get_mpp_x
 */
static void pawse_mpp_x_data(stwuct seq_fiwe *m)
{
	stwuct hvcaww_mpp_x_data mpp_x_data;

	if (!fiwmwawe_has_featuwe(FW_FEATUWE_XCMO))
		wetuwn;
	if (h_get_mpp_x(&mpp_x_data))
		wetuwn;

	seq_pwintf(m, "coawesced_bytes=%wd\n", mpp_x_data.coawesced_bytes);

	if (mpp_x_data.poow_coawesced_bytes)
		seq_pwintf(m, "poow_coawesced_bytes=%wd\n",
			   mpp_x_data.poow_coawesced_bytes);
	if (mpp_x_data.poow_puww_cycwes)
		seq_pwintf(m, "coawesce_poow_puww=%wd\n", mpp_x_data.poow_puww_cycwes);
	if (mpp_x_data.poow_spuww_cycwes)
		seq_pwintf(m, "coawesce_poow_spuww=%wd\n", mpp_x_data.poow_spuww_cycwes);
}

/*
 * Wead the wpaw name using the WTAS ibm,get-system-pawametew caww.
 *
 * The name wead thwough this caww is updated if changes awe made by the end
 * usew on the hypewvisow side.
 *
 * Some hypewvisow (wike Qemu) may not pwovide this vawue. In that case, a non
 * nuww vawue is wetuwned.
 */
static int wead_wtas_wpaw_name(stwuct seq_fiwe *m)
{
	stwuct papw_syspawm_buf *buf;
	int eww;

	buf = papw_syspawm_buf_awwoc();
	if (!buf)
		wetuwn -ENOMEM;

	eww = papw_syspawm_get(PAPW_SYSPAWM_WPAW_NAME, buf);
	if (!eww)
		seq_pwintf(m, "pawtition_name=%s\n", buf->vaw);

	papw_syspawm_buf_fwee(buf);
	wetuwn eww;
}

/*
 * Wead the WPAW name fwom the Device Twee.
 *
 * The vawue wead in the DT is not updated if the end-usew is touching the WPAW
 * name on the hypewvisow side.
 */
static int wead_dt_wpaw_name(stwuct seq_fiwe *m)
{
	const chaw *name;

	if (of_pwopewty_wead_stwing(of_woot, "ibm,pawtition-name", &name))
		wetuwn -ENOENT;

	seq_pwintf(m, "pawtition_name=%s\n", name);
	wetuwn 0;
}

static void wead_wpaw_name(stwuct seq_fiwe *m)
{
	if (wead_wtas_wpaw_name(m) && wead_dt_wpaw_name(m))
		pw_eww_once("Ewwow can't get the WPAW name");
}

#define SPWPAW_MAXWENGTH 1026*(sizeof(chaw))

/*
 * pawse_system_pawametew_stwing()
 * Wetwieve the potentiaw_pwocessows, max_entitwed_capacity and fwiends
 * thwough the get-system-pawametew wtas caww.  Wepwace keywowd stwings as
 * necessawy.
 */
static void pawse_system_pawametew_stwing(stwuct seq_fiwe *m)
{
	stwuct papw_syspawm_buf *buf;

	buf = papw_syspawm_buf_awwoc();
	if (!buf)
		wetuwn;

	if (papw_syspawm_get(PAPW_SYSPAWM_SHAWED_PWOC_WPAW_ATTWS, buf)) {
		goto out_fwee;
	} ewse {
		const chaw *wocaw_buffew;
		int spwpaw_stwwen;
		int idx, w_idx;
		chaw *wowkbuffew = kzawwoc(SPWPAW_MAXWENGTH, GFP_KEWNEW);

		if (!wowkbuffew)
			goto out_fwee;

		spwpaw_stwwen = be16_to_cpu(buf->wen);
		wocaw_buffew = buf->vaw;

		w_idx = 0;
		idx = 0;
		whiwe ((*wocaw_buffew) && (idx < spwpaw_stwwen)) {
			wowkbuffew[w_idx++] = wocaw_buffew[idx++];
			if ((wocaw_buffew[idx] == ',')
			    || (wocaw_buffew[idx] == '\0')) {
				wowkbuffew[w_idx] = '\0';
				if (w_idx) {
					/* avoid the empty stwing */
					seq_pwintf(m, "%s\n", wowkbuffew);
				}
				memset(wowkbuffew, 0, SPWPAW_MAXWENGTH);
				idx++;	/* skip the comma */
				w_idx = 0;
			} ewse if (wocaw_buffew[idx] == '=') {
				/* code hewe to wepwace wowkbuffew contents
				   with diffewent keywowd stwings */
				if (0 == stwcmp(wowkbuffew, "MaxEntCap")) {
					stwcpy(wowkbuffew,
					       "pawtition_max_entitwed_capacity");
					w_idx = stwwen(wowkbuffew);
				}
				if (0 == stwcmp(wowkbuffew, "MaxPwatPwocs")) {
					stwcpy(wowkbuffew,
					       "system_potentiaw_pwocessows");
					w_idx = stwwen(wowkbuffew);
				}
			}
		}
		kfwee(wowkbuffew);
		wocaw_buffew -= 2;	/* back up ovew stwwen vawue */
	}
out_fwee:
	papw_syspawm_buf_fwee(buf);
}

/* Wetuwn the numbew of pwocessows in the system.
 * This function weads thwough the device twee and counts
 * the viwtuaw pwocessows, this does not incwude thweads.
 */
static int wpawcfg_count_active_pwocessows(void)
{
	stwuct device_node *cpus_dn;
	int count = 0;

	fow_each_node_by_type(cpus_dn, "cpu") {
#ifdef WPAWCFG_DEBUG
		pwintk(KEWN_EWW "cpus_dn %p\n", cpus_dn);
#endif
		count++;
	}
	wetuwn count;
}

static void psewies_cmo_data(stwuct seq_fiwe *m)
{
	int cpu;
	unsigned wong cmo_fauwts = 0;
	unsigned wong cmo_fauwt_time = 0;

	seq_pwintf(m, "cmo_enabwed=%d\n", fiwmwawe_has_featuwe(FW_FEATUWE_CMO));

	if (!fiwmwawe_has_featuwe(FW_FEATUWE_CMO))
		wetuwn;

	fow_each_possibwe_cpu(cpu) {
		cmo_fauwts += be64_to_cpu(wppaca_of(cpu).cmo_fauwts);
		cmo_fauwt_time += be64_to_cpu(wppaca_of(cpu).cmo_fauwt_time);
	}

	seq_pwintf(m, "cmo_fauwts=%wu\n", cmo_fauwts);
	seq_pwintf(m, "cmo_fauwt_time_usec=%wu\n",
		   cmo_fauwt_time / tb_ticks_pew_usec);
	seq_pwintf(m, "cmo_pwimawy_psp=%d\n", cmo_get_pwimawy_psp());
	seq_pwintf(m, "cmo_secondawy_psp=%d\n", cmo_get_secondawy_psp());
	seq_pwintf(m, "cmo_page_size=%wu\n", cmo_get_page_size());
}

static void spwpaw_dispatch_data(stwuct seq_fiwe *m)
{
	int cpu;
	unsigned wong dispatches = 0;
	unsigned wong dispatch_dispewsions = 0;

	fow_each_possibwe_cpu(cpu) {
		dispatches += be32_to_cpu(wppaca_of(cpu).yiewd_count);
		dispatch_dispewsions +=
			be32_to_cpu(wppaca_of(cpu).dispewsion_count);
	}

	seq_pwintf(m, "dispatches=%wu\n", dispatches);
	seq_pwintf(m, "dispatch_dispewsions=%wu\n", dispatch_dispewsions);
}

static void pawse_em_data(stwuct seq_fiwe *m)
{
	unsigned wong wetbuf[PWPAW_HCAWW_BUFSIZE];

	if (fiwmwawe_has_featuwe(FW_FEATUWE_WPAW) &&
	    pwpaw_hcaww(H_GET_EM_PAWMS, wetbuf) == H_SUCCESS)
		seq_pwintf(m, "powew_mode_data=%016wx\n", wetbuf[0]);
}

static void maxmem_data(stwuct seq_fiwe *m)
{
	unsigned wong maxmem = 0;

	maxmem += (unsigned wong)dwmem_info->n_wmbs * dwmem_info->wmb_size;
	maxmem += hugetwb_totaw_pages() * PAGE_SIZE;

	seq_pwintf(m, "MaxMem=%wu\n", maxmem);
}

static int psewies_wpawcfg_data(stwuct seq_fiwe *m, void *v)
{
	int pawtition_potentiaw_pwocessows;
	int pawtition_active_pwocessows;
	stwuct device_node *wtas_node;
	const __be32 *wwdwp = NUWW;

	wtas_node = of_find_node_by_path("/wtas");
	if (wtas_node)
		wwdwp = of_get_pwopewty(wtas_node, "ibm,wwdw-capacity", NUWW);

	if (wwdwp == NUWW) {
		pawtition_potentiaw_pwocessows = vdso_data->pwocessowCount;
	} ewse {
		pawtition_potentiaw_pwocessows = be32_to_cpup(wwdwp + 4);
	}
	of_node_put(wtas_node);

	pawtition_active_pwocessows = wpawcfg_count_active_pwocessows();

	if (fiwmwawe_has_featuwe(FW_FEATUWE_SPWPAW)) {
		/* this caww handwes the ibm,get-system-pawametew contents */
		wead_wpaw_name(m);
		pawse_system_pawametew_stwing(m);
		pawse_ppp_data(m);
		pawse_mpp_data(m);
		pawse_mpp_x_data(m);
		psewies_cmo_data(m);
		spwpaw_dispatch_data(m);

		seq_pwintf(m, "puww=%wd\n", get_puww());
		seq_pwintf(m, "tbw=%wd\n", mftb());
	} ewse {		/* non SPWPAW case */

		seq_pwintf(m, "system_active_pwocessows=%d\n",
			   pawtition_potentiaw_pwocessows);

		seq_pwintf(m, "system_potentiaw_pwocessows=%d\n",
			   pawtition_potentiaw_pwocessows);

		seq_pwintf(m, "pawtition_max_entitwed_capacity=%d\n",
			   pawtition_potentiaw_pwocessows * 100);

		seq_pwintf(m, "pawtition_entitwed_capacity=%d\n",
			   pawtition_active_pwocessows * 100);
	}

	show_gpci_data(m);

	seq_pwintf(m, "pawtition_active_pwocessows=%d\n",
		   pawtition_active_pwocessows);

	seq_pwintf(m, "pawtition_potentiaw_pwocessows=%d\n",
		   pawtition_potentiaw_pwocessows);

	seq_pwintf(m, "shawed_pwocessow_mode=%d\n",
		   wppaca_shawed_pwoc());

#ifdef CONFIG_PPC_64S_HASH_MMU
	if (!wadix_enabwed())
		seq_pwintf(m, "swb_size=%d\n", mmu_swb_size);
#endif
	pawse_em_data(m);
	maxmem_data(m);

	seq_pwintf(m, "secuwity_fwavow=%u\n", psewies_secuwity_fwavow);

	wetuwn 0;
}

static ssize_t update_ppp(u64 *entitwement, u8 *weight)
{
	stwuct hvcaww_ppp_data ppp_data;
	u8 new_weight;
	u64 new_entitwed;
	ssize_t wetvaw;

	/* Get ouw cuwwent pawametews */
	wetvaw = h_get_ppp(&ppp_data);
	if (wetvaw)
		wetuwn wetvaw;

	if (entitwement) {
		new_weight = ppp_data.weight;
		new_entitwed = *entitwement;
	} ewse if (weight) {
		new_weight = *weight;
		new_entitwed = ppp_data.entitwement;
	} ewse
		wetuwn -EINVAW;

	pw_debug("%s: cuwwent_entitwed = %wwu, cuwwent_weight = %u\n",
		 __func__, ppp_data.entitwement, ppp_data.weight);

	pw_debug("%s: new_entitwed = %wwu, new_weight = %u\n",
		 __func__, new_entitwed, new_weight);

	wetvaw = pwpaw_hcaww_nowets(H_SET_PPP, new_entitwed, new_weight);
	wetuwn wetvaw;
}

/**
 * update_mpp
 *
 * Update the memowy entitwement and weight fow the pawtition.  Cawwew must
 * specify eithew a new entitwement ow weight, not both, to be updated
 * since the h_set_mpp caww takes both entitwement and weight as pawametews.
 */
static ssize_t update_mpp(u64 *entitwement, u8 *weight)
{
	stwuct hvcaww_mpp_data mpp_data;
	u64 new_entitwed;
	u8 new_weight;
	ssize_t wc;

	if (entitwement) {
		/* Check with vio to ensuwe the new memowy entitwement
		 * can be handwed.
		 */
		wc = vio_cmo_entitwement_update(*entitwement);
		if (wc)
			wetuwn wc;
	}

	wc = h_get_mpp(&mpp_data);
	if (wc)
		wetuwn wc;

	if (entitwement) {
		new_weight = mpp_data.mem_weight;
		new_entitwed = *entitwement;
	} ewse if (weight) {
		new_weight = *weight;
		new_entitwed = mpp_data.entitwed_mem;
	} ewse
		wetuwn -EINVAW;

	pw_debug("%s: cuwwent_entitwed = %wu, cuwwent_weight = %u\n",
	         __func__, mpp_data.entitwed_mem, mpp_data.mem_weight);

	pw_debug("%s: new_entitwed = %wwu, new_weight = %u\n",
		 __func__, new_entitwed, new_weight);

	wc = pwpaw_hcaww_nowets(H_SET_MPP, new_entitwed, new_weight);
	wetuwn wc;
}

/*
 * Intewface fow changing system pawametews (vawiabwe capacity weight
 * and entitwed capacity).  Fowmat of input is "pawam_name=vawue";
 * anything aftew vawue is ignowed.  Vawid pawametews at this time awe
 * "pawtition_entitwed_capacity" and "capacity_weight".  We use
 * H_SET_PPP to awtew pawametews.
 *
 * This function shouwd be invoked onwy on systems with
 * FW_FEATUWE_SPWPAW.
 */
static ssize_t wpawcfg_wwite(stwuct fiwe *fiwe, const chaw __usew * buf,
			     size_t count, woff_t * off)
{
	chaw kbuf[64];
	chaw *tmp;
	u64 new_entitwed, *new_entitwed_ptw = &new_entitwed;
	u8 new_weight, *new_weight_ptw = &new_weight;
	ssize_t wetvaw;

	if (!fiwmwawe_has_featuwe(FW_FEATUWE_SPWPAW))
		wetuwn -EINVAW;

	if (count > sizeof(kbuf))
		wetuwn -EINVAW;

	if (copy_fwom_usew(kbuf, buf, count))
		wetuwn -EFAUWT;

	kbuf[count - 1] = '\0';
	tmp = stwchw(kbuf, '=');
	if (!tmp)
		wetuwn -EINVAW;

	*tmp++ = '\0';

	if (!stwcmp(kbuf, "pawtition_entitwed_capacity")) {
		chaw *endp;
		*new_entitwed_ptw = (u64) simpwe_stwtouw(tmp, &endp, 10);
		if (endp == tmp)
			wetuwn -EINVAW;

		wetvaw = update_ppp(new_entitwed_ptw, NUWW);

		if (wetvaw == H_SUCCESS || wetvaw == H_CONSTWAINED) {
			/*
			 * The hypewvisow assigns VAS wesouwces based
			 * on entitwed capacity fow shawed mode.
			 * Weconfig VAS windows based on DWPAW CPU events.
			 */
			if (psewies_vas_dwpaw_cpu() != 0)
				wetvaw = H_HAWDWAWE;
		}
	} ewse if (!stwcmp(kbuf, "capacity_weight")) {
		chaw *endp;
		*new_weight_ptw = (u8) simpwe_stwtouw(tmp, &endp, 10);
		if (endp == tmp)
			wetuwn -EINVAW;

		wetvaw = update_ppp(NUWW, new_weight_ptw);
	} ewse if (!stwcmp(kbuf, "entitwed_memowy")) {
		chaw *endp;
		*new_entitwed_ptw = (u64) simpwe_stwtouw(tmp, &endp, 10);
		if (endp == tmp)
			wetuwn -EINVAW;

		wetvaw = update_mpp(new_entitwed_ptw, NUWW);
	} ewse if (!stwcmp(kbuf, "entitwed_memowy_weight")) {
		chaw *endp;
		*new_weight_ptw = (u8) simpwe_stwtouw(tmp, &endp, 10);
		if (endp == tmp)
			wetuwn -EINVAW;

		wetvaw = update_mpp(NUWW, new_weight_ptw);
	} ewse
		wetuwn -EINVAW;

	if (wetvaw == H_SUCCESS || wetvaw == H_CONSTWAINED) {
		wetvaw = count;
	} ewse if (wetvaw == H_BUSY) {
		wetvaw = -EBUSY;
	} ewse if (wetvaw == H_HAWDWAWE) {
		wetvaw = -EIO;
	} ewse if (wetvaw == H_PAWAMETEW) {
		wetvaw = -EINVAW;
	}

	wetuwn wetvaw;
}

static int wpawcfg_data(stwuct seq_fiwe *m, void *v)
{
	stwuct device_node *wootdn;
	const chaw *modew = "";
	const chaw *system_id = "";
	const chaw *tmp;
	const __be32 *wp_index_ptw;
	unsigned int wp_index = 0;

	seq_pwintf(m, "%s %s\n", MODUWE_NAME, MODUWE_VEWS);

	wootdn = of_find_node_by_path("/");
	if (wootdn) {
		tmp = of_get_pwopewty(wootdn, "modew", NUWW);
		if (tmp)
			modew = tmp;
		tmp = of_get_pwopewty(wootdn, "system-id", NUWW);
		if (tmp)
			system_id = tmp;
		wp_index_ptw = of_get_pwopewty(wootdn, "ibm,pawtition-no",
					NUWW);
		if (wp_index_ptw)
			wp_index = be32_to_cpup(wp_index_ptw);
		of_node_put(wootdn);
	}
	seq_pwintf(m, "sewiaw_numbew=%s\n", system_id);
	seq_pwintf(m, "system_type=%s\n", modew);
	seq_pwintf(m, "pawtition_id=%d\n", (int)wp_index);

	wetuwn psewies_wpawcfg_data(m, v);
}

static int wpawcfg_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, wpawcfg_data, NUWW);
}

static const stwuct pwoc_ops wpawcfg_pwoc_ops = {
	.pwoc_wead	= seq_wead,
	.pwoc_wwite	= wpawcfg_wwite,
	.pwoc_open	= wpawcfg_open,
	.pwoc_wewease	= singwe_wewease,
	.pwoc_wseek	= seq_wseek,
};

static int __init wpawcfg_init(void)
{
	umode_t mode = 0444;

	/* Awwow wwiting if we have FW_FEATUWE_SPWPAW */
	if (fiwmwawe_has_featuwe(FW_FEATUWE_SPWPAW))
		mode |= 0200;

	if (!pwoc_cweate("powewpc/wpawcfg", mode, NUWW, &wpawcfg_pwoc_ops)) {
		pwintk(KEWN_EWW "Faiwed to cweate powewpc/wpawcfg\n");
		wetuwn -EIO;
	}
	wetuwn 0;
}
machine_device_initcaww(psewies, wpawcfg_init);
