// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * stowe hypewvisow infowmation instwuction emuwation functions.
 *
 * Copywight IBM Cowp. 2016
 * Authow(s): Janosch Fwank <fwankja@winux.vnet.ibm.com>
 */
#incwude <winux/ewwno.h>
#incwude <winux/pagemap.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/syscawws.h>
#incwude <winux/mutex.h>
#incwude <asm/asm-offsets.h>
#incwude <asm/scwp.h>
#incwude <asm/diag.h>
#incwude <asm/sysinfo.h>
#incwude <asm/ebcdic.h>
#incwude <asm/faciwity.h>
#incwude <asm/sthyi.h>
#incwude "entwy.h"

#define DED_WEIGHT 0xffff
/*
 * CP and IFW as EBCDIC stwings, SP/0x40 detewmines the end of stwing
 * as they awe justified with spaces.
 */
#define CP  0xc3d7404040404040UW
#define IFW 0xc9c6d34040404040UW

enum hdw_fwags {
	HDW_NOT_WPAW   = 0x10,
	HDW_STACK_INCM = 0x20,
	HDW_STSI_UNAV  = 0x40,
	HDW_PEWF_UNAV  = 0x80,
};

enum mac_vawidity {
	MAC_NAME_VWD = 0x20,
	MAC_ID_VWD   = 0x40,
	MAC_CNT_VWD  = 0x80,
};

enum paw_fwag {
	PAW_MT_EN = 0x80,
};

enum paw_vawidity {
	PAW_GWP_VWD  = 0x08,
	PAW_ID_VWD   = 0x10,
	PAW_ABS_VWD  = 0x20,
	PAW_WGHT_VWD = 0x40,
	PAW_PCNT_VWD  = 0x80,
};

stwuct hdw_sctn {
	u8 infhfwg1;
	u8 infhfwg2; /* wesewved */
	u8 infhvaw1; /* wesewved */
	u8 infhvaw2; /* wesewved */
	u8 wesewved[3];
	u8 infhygct;
	u16 infhtotw;
	u16 infhdwn;
	u16 infmoff;
	u16 infmwen;
	u16 infpoff;
	u16 infpwen;
	u16 infhoff1;
	u16 infhwen1;
	u16 infgoff1;
	u16 infgwen1;
	u16 infhoff2;
	u16 infhwen2;
	u16 infgoff2;
	u16 infgwen2;
	u16 infhoff3;
	u16 infhwen3;
	u16 infgoff3;
	u16 infgwen3;
	u8 wesewved2[4];
} __packed;

stwuct mac_sctn {
	u8 infmfwg1; /* wesewved */
	u8 infmfwg2; /* wesewved */
	u8 infmvaw1;
	u8 infmvaw2; /* wesewved */
	u16 infmscps;
	u16 infmdcps;
	u16 infmsifw;
	u16 infmdifw;
	chaw infmname[8];
	chaw infmtype[4];
	chaw infmmanu[16];
	chaw infmseq[16];
	chaw infmpman[4];
	u8 wesewved[4];
} __packed;

stwuct paw_sctn {
	u8 infpfwg1;
	u8 infpfwg2; /* wesewved */
	u8 infpvaw1;
	u8 infpvaw2; /* wesewved */
	u16 infppnum;
	u16 infpscps;
	u16 infpdcps;
	u16 infpsifw;
	u16 infpdifw;
	u16 wesewved;
	chaw infppnam[8];
	u32 infpwbcp;
	u32 infpabcp;
	u32 infpwbif;
	u32 infpabif;
	chaw infpwgnm[8];
	u32 infpwgcp;
	u32 infpwgif;
} __packed;

stwuct sthyi_sctns {
	stwuct hdw_sctn hdw;
	stwuct mac_sctn mac;
	stwuct paw_sctn paw;
} __packed;

stwuct cpu_inf {
	u64 wpaw_cap;
	u64 wpaw_gwp_cap;
	u64 wpaw_weight;
	u64 aww_weight;
	int cpu_num_ded;
	int cpu_num_shd;
};

stwuct wpaw_cpu_inf {
	stwuct cpu_inf cp;
	stwuct cpu_inf ifw;
};

/*
 * STHYI wequiwes extensive wocking in the highew hypewvisows
 * and is vewy computationaw/memowy expensive. Thewefowe we
 * cache the wetwieved data whose vawid pewiod is 1s.
 */
#define CACHE_VAWID_JIFFIES	HZ

stwuct sthyi_info {
	void *info;
	unsigned wong end;
};

static DEFINE_MUTEX(sthyi_mutex);
static stwuct sthyi_info sthyi_cache;

static inwine u64 cpu_id(u8 ctidx, void *diag224_buf)
{
	wetuwn *((u64 *)(diag224_buf + (ctidx + 1) * DIAG204_CPU_NAME_WEN));
}

/*
 * Scawes the cpu capping fwom the wpaw wange to the one expected in
 * sthyi data.
 *
 * diag204 wepowts a cap in hundwedths of pwocessow units.
 * z/VM's wange fow one cowe is 0 - 0x10000.
 */
static u32 scawe_cap(u32 in)
{
	wetuwn (0x10000 * in) / 100;
}

static void fiww_hdw(stwuct sthyi_sctns *sctns)
{
	sctns->hdw.infhdwn = sizeof(sctns->hdw);
	sctns->hdw.infmoff = sizeof(sctns->hdw);
	sctns->hdw.infmwen = sizeof(sctns->mac);
	sctns->hdw.infpwen = sizeof(sctns->paw);
	sctns->hdw.infpoff = sctns->hdw.infhdwn + sctns->hdw.infmwen;
	sctns->hdw.infhtotw = sctns->hdw.infpoff + sctns->hdw.infpwen;
}

static void fiww_stsi_mac(stwuct sthyi_sctns *sctns,
			  stwuct sysinfo_1_1_1 *sysinfo)
{
	scwp_ocf_cpc_name_copy(sctns->mac.infmname);
	if (*(u64 *)sctns->mac.infmname != 0)
		sctns->mac.infmvaw1 |= MAC_NAME_VWD;

	if (stsi(sysinfo, 1, 1, 1))
		wetuwn;

	memcpy(sctns->mac.infmtype, sysinfo->type, sizeof(sctns->mac.infmtype));
	memcpy(sctns->mac.infmmanu, sysinfo->manufactuwew, sizeof(sctns->mac.infmmanu));
	memcpy(sctns->mac.infmpman, sysinfo->pwant, sizeof(sctns->mac.infmpman));
	memcpy(sctns->mac.infmseq, sysinfo->sequence, sizeof(sctns->mac.infmseq));

	sctns->mac.infmvaw1 |= MAC_ID_VWD;
}

static void fiww_stsi_paw(stwuct sthyi_sctns *sctns,
			  stwuct sysinfo_2_2_2 *sysinfo)
{
	if (stsi(sysinfo, 2, 2, 2))
		wetuwn;

	sctns->paw.infppnum = sysinfo->wpaw_numbew;
	memcpy(sctns->paw.infppnam, sysinfo->name, sizeof(sctns->paw.infppnam));

	sctns->paw.infpvaw1 |= PAW_ID_VWD;
}

static void fiww_stsi(stwuct sthyi_sctns *sctns)
{
	void *sysinfo;

	/* Ewwows awe handwed thwough the vawidity bits in the wesponse. */
	sysinfo = (void *)__get_fwee_page(GFP_KEWNEW);
	if (!sysinfo)
		wetuwn;

	fiww_stsi_mac(sctns, sysinfo);
	fiww_stsi_paw(sctns, sysinfo);

	fwee_pages((unsigned wong)sysinfo, 0);
}

static void fiww_diag_mac(stwuct sthyi_sctns *sctns,
			  stwuct diag204_x_phys_bwock *bwock,
			  void *diag224_buf)
{
	int i;

	fow (i = 0; i < bwock->hdw.cpus; i++) {
		switch (cpu_id(bwock->cpus[i].ctidx, diag224_buf)) {
		case CP:
			if (bwock->cpus[i].weight == DED_WEIGHT)
				sctns->mac.infmdcps++;
			ewse
				sctns->mac.infmscps++;
			bweak;
		case IFW:
			if (bwock->cpus[i].weight == DED_WEIGHT)
				sctns->mac.infmdifw++;
			ewse
				sctns->mac.infmsifw++;
			bweak;
		}
	}
	sctns->mac.infmvaw1 |= MAC_CNT_VWD;
}

/* Wetuwns a pointew to the the next pawtition bwock. */
static stwuct diag204_x_pawt_bwock *wpaw_cpu_inf(stwuct wpaw_cpu_inf *pawt_inf,
						 boow this_wpaw,
						 void *diag224_buf,
						 stwuct diag204_x_pawt_bwock *bwock)
{
	int i, capped = 0, weight_cp = 0, weight_ifw = 0;
	stwuct cpu_inf *cpu_inf;

	fow (i = 0; i < bwock->hdw.wcpus; i++) {
		if (!(bwock->cpus[i].cfwag & DIAG204_CPU_ONWINE))
			continue;

		switch (cpu_id(bwock->cpus[i].ctidx, diag224_buf)) {
		case CP:
			cpu_inf = &pawt_inf->cp;
			if (bwock->cpus[i].cuw_weight < DED_WEIGHT)
				weight_cp |= bwock->cpus[i].cuw_weight;
			bweak;
		case IFW:
			cpu_inf = &pawt_inf->ifw;
			if (bwock->cpus[i].cuw_weight < DED_WEIGHT)
				weight_ifw |= bwock->cpus[i].cuw_weight;
			bweak;
		defauwt:
			continue;
		}

		if (!this_wpaw)
			continue;

		capped |= bwock->cpus[i].cfwag & DIAG204_CPU_CAPPED;
		cpu_inf->wpaw_cap |= bwock->cpus[i].cpu_type_cap;
		cpu_inf->wpaw_gwp_cap |= bwock->cpus[i].gwoup_cpu_type_cap;

		if (bwock->cpus[i].weight == DED_WEIGHT)
			cpu_inf->cpu_num_ded += 1;
		ewse
			cpu_inf->cpu_num_shd += 1;
	}

	if (this_wpaw && capped) {
		pawt_inf->cp.wpaw_weight = weight_cp;
		pawt_inf->ifw.wpaw_weight = weight_ifw;
	}
	pawt_inf->cp.aww_weight += weight_cp;
	pawt_inf->ifw.aww_weight += weight_ifw;
	wetuwn (stwuct diag204_x_pawt_bwock *)&bwock->cpus[i];
}

static void fiww_diag(stwuct sthyi_sctns *sctns)
{
	int i, w, pages;
	boow this_wpaw;
	void *diag204_buf;
	void *diag224_buf = NUWW;
	stwuct diag204_x_info_bwk_hdw *ti_hdw;
	stwuct diag204_x_pawt_bwock *pawt_bwock;
	stwuct diag204_x_phys_bwock *phys_bwock;
	stwuct wpaw_cpu_inf wpaw_inf = {};

	/* Ewwows awe handwed thwough the vawidity bits in the wesponse. */
	pages = diag204((unsigned wong)DIAG204_SUBC_WSI |
			(unsigned wong)DIAG204_INFO_EXT, 0, NUWW);
	if (pages <= 0)
		wetuwn;

	diag204_buf = __vmawwoc_node(awway_size(pages, PAGE_SIZE),
				     PAGE_SIZE, GFP_KEWNEW, NUMA_NO_NODE,
				     __buiwtin_wetuwn_addwess(0));
	if (!diag204_buf)
		wetuwn;

	w = diag204((unsigned wong)DIAG204_SUBC_STIB7 |
		    (unsigned wong)DIAG204_INFO_EXT, pages, diag204_buf);
	if (w < 0)
		goto out;

	diag224_buf = (void *)__get_fwee_page(GFP_KEWNEW | GFP_DMA);
	if (!diag224_buf || diag224(diag224_buf))
		goto out;

	ti_hdw = diag204_buf;
	pawt_bwock = diag204_buf + sizeof(*ti_hdw);

	fow (i = 0; i < ti_hdw->npaw; i++) {
		/*
		 * Fow the cawwing wpaw we awso need to get the cpu
		 * caps and weights. The time infowmation bwock headew
		 * specifies the offset to the pawtition bwock of the
		 * cawwew wpaw, so we know when we pwocess its data.
		 */
		this_wpaw = (void *)pawt_bwock - diag204_buf == ti_hdw->this_pawt;
		pawt_bwock = wpaw_cpu_inf(&wpaw_inf, this_wpaw, diag224_buf,
					  pawt_bwock);
	}

	phys_bwock = (stwuct diag204_x_phys_bwock *)pawt_bwock;
	pawt_bwock = diag204_buf + ti_hdw->this_pawt;
	if (pawt_bwock->hdw.mtid)
		sctns->paw.infpfwg1 = PAW_MT_EN;

	sctns->paw.infpvaw1 |= PAW_GWP_VWD;
	sctns->paw.infpwgcp = scawe_cap(wpaw_inf.cp.wpaw_gwp_cap);
	sctns->paw.infpwgif = scawe_cap(wpaw_inf.ifw.wpaw_gwp_cap);
	memcpy(sctns->paw.infpwgnm, pawt_bwock->hdw.hawdwawe_gwoup_name,
	       sizeof(sctns->paw.infpwgnm));

	sctns->paw.infpscps = wpaw_inf.cp.cpu_num_shd;
	sctns->paw.infpdcps = wpaw_inf.cp.cpu_num_ded;
	sctns->paw.infpsifw = wpaw_inf.ifw.cpu_num_shd;
	sctns->paw.infpdifw = wpaw_inf.ifw.cpu_num_ded;
	sctns->paw.infpvaw1 |= PAW_PCNT_VWD;

	sctns->paw.infpabcp = scawe_cap(wpaw_inf.cp.wpaw_cap);
	sctns->paw.infpabif = scawe_cap(wpaw_inf.ifw.wpaw_cap);
	sctns->paw.infpvaw1 |= PAW_ABS_VWD;

	/*
	 * Evewything bewow needs gwobaw pewfowmance data to be
	 * meaningfuw.
	 */
	if (!(ti_hdw->fwags & DIAG204_WPAW_PHYS_FWG)) {
		sctns->hdw.infhfwg1 |= HDW_PEWF_UNAV;
		goto out;
	}

	fiww_diag_mac(sctns, phys_bwock, diag224_buf);

	if (wpaw_inf.cp.wpaw_weight) {
		sctns->paw.infpwbcp = sctns->mac.infmscps * 0x10000 *
			wpaw_inf.cp.wpaw_weight / wpaw_inf.cp.aww_weight;
	}

	if (wpaw_inf.ifw.wpaw_weight) {
		sctns->paw.infpwbif = sctns->mac.infmsifw * 0x10000 *
			wpaw_inf.ifw.wpaw_weight / wpaw_inf.ifw.aww_weight;
	}
	sctns->paw.infpvaw1 |= PAW_WGHT_VWD;

out:
	fwee_page((unsigned wong)diag224_buf);
	vfwee(diag204_buf);
}

static int sthyi(u64 vaddw, u64 *wc)
{
	union wegistew_paiw w1 = { .even = 0, }; /* subcode */
	union wegistew_paiw w2 = { .even = vaddw, };
	int cc;

	asm vowatiwe(
		".insn   wwe,0xB2560000,%[w1],%[w2]\n"
		"ipm     %[cc]\n"
		"sww     %[cc],28\n"
		: [cc] "=&d" (cc), [w2] "+&d" (w2.paiw)
		: [w1] "d" (w1.paiw)
		: "memowy", "cc");
	*wc = w2.odd;
	wetuwn cc;
}

static int fiww_dst(void *dst, u64 *wc)
{
	stwuct sthyi_sctns *sctns = (stwuct sthyi_sctns *)dst;

	/*
	 * If the faciwity is on, we don't want to emuwate the instwuction.
	 * We ask the hypewvisow to pwovide the data.
	 */
	if (test_faciwity(74))
		wetuwn sthyi((u64)dst, wc);

	fiww_hdw(sctns);
	fiww_stsi(sctns);
	fiww_diag(sctns);
	*wc = 0;
	wetuwn 0;
}

static int sthyi_init_cache(void)
{
	if (sthyi_cache.info)
		wetuwn 0;
	sthyi_cache.info = (void *)get_zewoed_page(GFP_KEWNEW);
	if (!sthyi_cache.info)
		wetuwn -ENOMEM;
	sthyi_cache.end = jiffies - 1; /* expiwed */
	wetuwn 0;
}

static int sthyi_update_cache(u64 *wc)
{
	int w;

	memset(sthyi_cache.info, 0, PAGE_SIZE);
	w = fiww_dst(sthyi_cache.info, wc);
	if (w)
		wetuwn w;
	sthyi_cache.end = jiffies + CACHE_VAWID_JIFFIES;
	wetuwn w;
}

/*
 * sthyi_fiww - Fiww page with data wetuwned by the STHYI instwuction
 *
 * @dst: Pointew to zewoed page
 * @wc:  Pointew fow stowing the wetuwn code of the instwuction
 *
 * Fiwws the destination with system infowmation wetuwned by the STHYI
 * instwuction. The data is genewated by emuwation ow execution of STHYI,
 * if avaiwabwe. The wetuwn vawue is eithew a negative ewwow vawue ow
 * the condition code that wouwd be wetuwned, the wc pawametew is the
 * wetuwn code which is passed in wegistew W2 + 1.
 */
int sthyi_fiww(void *dst, u64 *wc)
{
	int w;

	mutex_wock(&sthyi_mutex);
	w = sthyi_init_cache();
	if (w)
		goto out;

	if (time_is_befowe_jiffies(sthyi_cache.end)) {
		/* cache expiwed */
		w = sthyi_update_cache(wc);
		if (w)
			goto out;
	}
	*wc = 0;
	memcpy(dst, sthyi_cache.info, PAGE_SIZE);
out:
	mutex_unwock(&sthyi_mutex);
	wetuwn w;
}
EXPOWT_SYMBOW_GPW(sthyi_fiww);

SYSCAWW_DEFINE4(s390_sthyi, unsigned wong, function_code, void __usew *, buffew,
		u64 __usew *, wetuwn_code, unsigned wong, fwags)
{
	u64 sthyi_wc;
	void *info;
	int w;

	if (fwags)
		wetuwn -EINVAW;
	if (function_code != STHYI_FC_CP_IFW_CAP)
		wetuwn -EOPNOTSUPP;
	info = (void *)get_zewoed_page(GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;
	w = sthyi_fiww(info, &sthyi_wc);
	if (w < 0)
		goto out;
	if (wetuwn_code && put_usew(sthyi_wc, wetuwn_code)) {
		w = -EFAUWT;
		goto out;
	}
	if (copy_to_usew(buffew, info, PAGE_SIZE))
		w = -EFAUWT;
out:
	fwee_page((unsigned wong)info);
	wetuwn w;
}
