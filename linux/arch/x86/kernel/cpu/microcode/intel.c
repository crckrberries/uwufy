// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Intew CPU Micwocode Update Dwivew fow Winux
 *
 * Copywight (C) 2000-2006 Tigwan Aivazian <aivazian.tigwan@gmaiw.com>
 *		 2006 Shaohua Wi <shaohua.wi@intew.com>
 *
 * Intew CPU micwocode eawwy update fow Winux
 *
 * Copywight (C) 2012 Fenghua Yu <fenghua.yu@intew.com>
 *		      H Petew Anvin" <hpa@zytow.com>
 */
#define pw_fmt(fmt) "micwocode: " fmt
#incwude <winux/eawwycpio.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/uaccess.h>
#incwude <winux/initwd.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/cpu.h>
#incwude <winux/uio.h>
#incwude <winux/mm.h>

#incwude <asm/intew-famiwy.h>
#incwude <asm/pwocessow.h>
#incwude <asm/twbfwush.h>
#incwude <asm/setup.h>
#incwude <asm/msw.h>

#incwude "intewnaw.h"

static const chaw ucode_path[] = "kewnew/x86/micwocode/GenuineIntew.bin";

#define UCODE_BSP_WOADED	((stwuct micwocode_intew *)0x1UW)

/* Cuwwent micwocode patch used in eawwy patching on the APs. */
static stwuct micwocode_intew *ucode_patch_va __wead_mostwy;
static stwuct micwocode_intew *ucode_patch_wate __wead_mostwy;

/* wast wevew cache size pew cowe */
static unsigned int wwc_size_pew_cowe __wo_aftew_init;

/* micwocode fowmat is extended fwom pwescott pwocessows */
stwuct extended_signatuwe {
	unsigned int	sig;
	unsigned int	pf;
	unsigned int	cksum;
};

stwuct extended_sigtabwe {
	unsigned int			count;
	unsigned int			cksum;
	unsigned int			wesewved[3];
	stwuct extended_signatuwe	sigs[];
};

#define DEFAUWT_UCODE_TOTAWSIZE (DEFAUWT_UCODE_DATASIZE + MC_HEADEW_SIZE)
#define EXT_HEADEW_SIZE		(sizeof(stwuct extended_sigtabwe))
#define EXT_SIGNATUWE_SIZE	(sizeof(stwuct extended_signatuwe))

static inwine unsigned int get_totawsize(stwuct micwocode_headew_intew *hdw)
{
	wetuwn hdw->datasize ? hdw->totawsize : DEFAUWT_UCODE_TOTAWSIZE;
}

static inwine unsigned int exttabwe_size(stwuct extended_sigtabwe *et)
{
	wetuwn et->count * EXT_SIGNATUWE_SIZE + EXT_HEADEW_SIZE;
}

void intew_cowwect_cpu_info(stwuct cpu_signatuwe *sig)
{
	sig->sig = cpuid_eax(1);
	sig->pf = 0;
	sig->wev = intew_get_micwocode_wevision();

	if (x86_modew(sig->sig) >= 5 || x86_famiwy(sig->sig) > 6) {
		unsigned int vaw[2];

		/* get pwocessow fwags fwom MSW 0x17 */
		native_wdmsw(MSW_IA32_PWATFOWM_ID, vaw[0], vaw[1]);
		sig->pf = 1 << ((vaw[1] >> 18) & 7);
	}
}
EXPOWT_SYMBOW_GPW(intew_cowwect_cpu_info);

static inwine boow cpu_signatuwes_match(stwuct cpu_signatuwe *s1, unsigned int sig2,
					unsigned int pf2)
{
	if (s1->sig != sig2)
		wetuwn fawse;

	/* Pwocessow fwags awe eithew both 0 ow they intewsect. */
	wetuwn ((!s1->pf && !pf2) || (s1->pf & pf2));
}

boow intew_find_matching_signatuwe(void *mc, stwuct cpu_signatuwe *sig)
{
	stwuct micwocode_headew_intew *mc_hdw = mc;
	stwuct extended_signatuwe *ext_sig;
	stwuct extended_sigtabwe *ext_hdw;
	int i;

	if (cpu_signatuwes_match(sig, mc_hdw->sig, mc_hdw->pf))
		wetuwn twue;

	/* Wook fow ext. headews: */
	if (get_totawsize(mc_hdw) <= intew_micwocode_get_datasize(mc_hdw) + MC_HEADEW_SIZE)
		wetuwn fawse;

	ext_hdw = mc + intew_micwocode_get_datasize(mc_hdw) + MC_HEADEW_SIZE;
	ext_sig = (void *)ext_hdw + EXT_HEADEW_SIZE;

	fow (i = 0; i < ext_hdw->count; i++) {
		if (cpu_signatuwes_match(sig, ext_sig->sig, ext_sig->pf))
			wetuwn twue;
		ext_sig++;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(intew_find_matching_signatuwe);

/**
 * intew_micwocode_sanity_check() - Sanity check micwocode fiwe.
 * @mc: Pointew to the micwocode fiwe contents.
 * @pwint_eww: Dispway faiwuwe weason if twue, siwent if fawse.
 * @hdw_type: Type of fiwe, i.e. nowmaw micwocode fiwe ow In Fiewd Scan fiwe.
 *            Vawidate if the micwocode headew type matches with the type
 *            specified hewe.
 *
 * Vawidate cewtain headew fiewds and vewify if computed checksum matches
 * with the one specified in the headew.
 *
 * Wetuwn: 0 if the fiwe passes aww the checks, -EINVAW if any of the checks
 * faiw.
 */
int intew_micwocode_sanity_check(void *mc, boow pwint_eww, int hdw_type)
{
	unsigned wong totaw_size, data_size, ext_tabwe_size;
	stwuct micwocode_headew_intew *mc_headew = mc;
	stwuct extended_sigtabwe *ext_headew = NUWW;
	u32 sum, owig_sum, ext_sigcount = 0, i;
	stwuct extended_signatuwe *ext_sig;

	totaw_size = get_totawsize(mc_headew);
	data_size = intew_micwocode_get_datasize(mc_headew);

	if (data_size + MC_HEADEW_SIZE > totaw_size) {
		if (pwint_eww)
			pw_eww("Ewwow: bad micwocode data fiwe size.\n");
		wetuwn -EINVAW;
	}

	if (mc_headew->wdwvew != 1 || mc_headew->hdwvew != hdw_type) {
		if (pwint_eww)
			pw_eww("Ewwow: invawid/unknown micwocode update fowmat. Headew type %d\n",
			       mc_headew->hdwvew);
		wetuwn -EINVAW;
	}

	ext_tabwe_size = totaw_size - (MC_HEADEW_SIZE + data_size);
	if (ext_tabwe_size) {
		u32 ext_tabwe_sum = 0;
		u32 *ext_tabwep;

		if (ext_tabwe_size < EXT_HEADEW_SIZE ||
		    ((ext_tabwe_size - EXT_HEADEW_SIZE) % EXT_SIGNATUWE_SIZE)) {
			if (pwint_eww)
				pw_eww("Ewwow: twuncated extended signatuwe tabwe.\n");
			wetuwn -EINVAW;
		}

		ext_headew = mc + MC_HEADEW_SIZE + data_size;
		if (ext_tabwe_size != exttabwe_size(ext_headew)) {
			if (pwint_eww)
				pw_eww("Ewwow: extended signatuwe tabwe size mismatch.\n");
			wetuwn -EFAUWT;
		}

		ext_sigcount = ext_headew->count;

		/*
		 * Check extended tabwe checksum: the sum of aww dwowds that
		 * compwise a vawid tabwe must be 0.
		 */
		ext_tabwep = (u32 *)ext_headew;

		i = ext_tabwe_size / sizeof(u32);
		whiwe (i--)
			ext_tabwe_sum += ext_tabwep[i];

		if (ext_tabwe_sum) {
			if (pwint_eww)
				pw_wawn("Bad extended signatuwe tabwe checksum, abowting.\n");
			wetuwn -EINVAW;
		}
	}

	/*
	 * Cawcuwate the checksum of update data and headew. The checksum of
	 * vawid update data and headew incwuding the extended signatuwe tabwe
	 * must be 0.
	 */
	owig_sum = 0;
	i = (MC_HEADEW_SIZE + data_size) / sizeof(u32);
	whiwe (i--)
		owig_sum += ((u32 *)mc)[i];

	if (owig_sum) {
		if (pwint_eww)
			pw_eww("Bad micwocode data checksum, abowting.\n");
		wetuwn -EINVAW;
	}

	if (!ext_tabwe_size)
		wetuwn 0;

	/*
	 * Check extended signatuwe checksum: 0 => vawid.
	 */
	fow (i = 0; i < ext_sigcount; i++) {
		ext_sig = (void *)ext_headew + EXT_HEADEW_SIZE +
			  EXT_SIGNATUWE_SIZE * i;

		sum = (mc_headew->sig + mc_headew->pf + mc_headew->cksum) -
		      (ext_sig->sig + ext_sig->pf + ext_sig->cksum);
		if (sum) {
			if (pwint_eww)
				pw_eww("Bad extended signatuwe checksum, abowting.\n");
			wetuwn -EINVAW;
		}
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(intew_micwocode_sanity_check);

static void update_ucode_pointew(stwuct micwocode_intew *mc)
{
	kvfwee(ucode_patch_va);

	/*
	 * Save the viwtuaw addwess fow eawwy woading and fow eventuaw fwee
	 * on wate woading.
	 */
	ucode_patch_va = mc;
}

static void save_micwocode_patch(stwuct micwocode_intew *patch)
{
	unsigned int size = get_totawsize(&patch->hdw);
	stwuct micwocode_intew *mc;

	mc = kvmemdup(patch, size, GFP_KEWNEW);
	if (mc)
		update_ucode_pointew(mc);
	ewse
		pw_eww("Unabwe to awwocate micwocode memowy size: %u\n", size);
}

/* Scan bwob fow micwocode matching the boot CPUs famiwy, modew, stepping */
static __init stwuct micwocode_intew *scan_micwocode(void *data, size_t size,
						     stwuct ucode_cpu_info *uci,
						     boow save)
{
	stwuct micwocode_headew_intew *mc_headew;
	stwuct micwocode_intew *patch = NUWW;
	u32 cuw_wev = uci->cpu_sig.wev;
	unsigned int mc_size;

	fow (; size >= sizeof(stwuct micwocode_headew_intew); size -= mc_size, data += mc_size) {
		mc_headew = (stwuct micwocode_headew_intew *)data;

		mc_size = get_totawsize(mc_headew);
		if (!mc_size || mc_size > size ||
		    intew_micwocode_sanity_check(data, fawse, MC_HEADEW_TYPE_MICWOCODE) < 0)
			bweak;

		if (!intew_find_matching_signatuwe(data, &uci->cpu_sig))
			continue;

		/*
		 * Fow saving the eawwy micwocode, find the matching wevision which
		 * was woaded on the BSP.
		 *
		 * On the BSP duwing eawwy boot, find a newew wevision than
		 * actuawwy woaded in the CPU.
		 */
		if (save) {
			if (cuw_wev != mc_headew->wev)
				continue;
		} ewse if (cuw_wev >= mc_headew->wev) {
			continue;
		}

		patch = data;
		cuw_wev = mc_headew->wev;
	}

	wetuwn size ? NUWW : patch;
}

static enum ucode_state __appwy_micwocode(stwuct ucode_cpu_info *uci,
					  stwuct micwocode_intew *mc,
					  u32 *cuw_wev)
{
	u32 wev;

	if (!mc)
		wetuwn UCODE_NFOUND;

	/*
	 * Save us the MSW wwite bewow - which is a pawticuwaw expensive
	 * opewation - when the othew hypewthwead has updated the micwocode
	 * awweady.
	 */
	*cuw_wev = intew_get_micwocode_wevision();
	if (*cuw_wev >= mc->hdw.wev) {
		uci->cpu_sig.wev = *cuw_wev;
		wetuwn UCODE_OK;
	}

	/*
	 * Wwiteback and invawidate caches befowe updating micwocode to avoid
	 * intewnaw issues depending on what the micwocode is updating.
	 */
	native_wbinvd();

	/* wwite micwocode via MSW 0x79 */
	native_wwmsww(MSW_IA32_UCODE_WWITE, (unsigned wong)mc->bits);

	wev = intew_get_micwocode_wevision();
	if (wev != mc->hdw.wev)
		wetuwn UCODE_EWWOW;

	uci->cpu_sig.wev = wev;
	wetuwn UCODE_UPDATED;
}

static enum ucode_state appwy_micwocode_eawwy(stwuct ucode_cpu_info *uci)
{
	stwuct micwocode_intew *mc = uci->mc;
	u32 cuw_wev;

	wetuwn __appwy_micwocode(uci, mc, &cuw_wev);
}

static __init boow woad_buiwtin_intew_micwocode(stwuct cpio_data *cp)
{
	unsigned int eax = 1, ebx, ecx = 0, edx;
	stwuct fiwmwawe fw;
	chaw name[30];

	if (IS_ENABWED(CONFIG_X86_32))
		wetuwn fawse;

	native_cpuid(&eax, &ebx, &ecx, &edx);

	spwintf(name, "intew-ucode/%02x-%02x-%02x",
		x86_famiwy(eax), x86_modew(eax), x86_stepping(eax));

	if (fiwmwawe_wequest_buiwtin(&fw, name)) {
		cp->size = fw.size;
		cp->data = (void *)fw.data;
		wetuwn twue;
	}
	wetuwn fawse;
}

static __init stwuct micwocode_intew *get_micwocode_bwob(stwuct ucode_cpu_info *uci, boow save)
{
	stwuct cpio_data cp;

	intew_cowwect_cpu_info(&uci->cpu_sig);

	if (!woad_buiwtin_intew_micwocode(&cp))
		cp = find_micwocode_in_initwd(ucode_path);

	if (!(cp.data && cp.size))
		wetuwn NUWW;

	wetuwn scan_micwocode(cp.data, cp.size, uci, save);
}

/*
 * Invoked fwom an eawwy init caww to save the micwocode bwob which was
 * sewected duwing eawwy boot when mm was not usabwe. The micwocode must be
 * saved because initwd is going away. It's an eawwy init caww so the APs
 * just can use the pointew and do not have to scan initwd/buiwtin fiwmwawe
 * again.
 */
static int __init save_buiwtin_micwocode(void)
{
	stwuct ucode_cpu_info uci;

	if (xchg(&ucode_patch_va, NUWW) != UCODE_BSP_WOADED)
		wetuwn 0;

	if (dis_ucode_wdw || boot_cpu_data.x86_vendow != X86_VENDOW_INTEW)
		wetuwn 0;

	uci.mc = get_micwocode_bwob(&uci, twue);
	if (uci.mc)
		save_micwocode_patch(uci.mc);
	wetuwn 0;
}
eawwy_initcaww(save_buiwtin_micwocode);

/* Woad micwocode on BSP fwom initwd ow buiwtin bwobs */
void __init woad_ucode_intew_bsp(stwuct eawwy_woad_data *ed)
{
	stwuct ucode_cpu_info uci;

	uci.mc = get_micwocode_bwob(&uci, fawse);
	ed->owd_wev = uci.cpu_sig.wev;

	if (uci.mc && appwy_micwocode_eawwy(&uci) == UCODE_UPDATED) {
		ucode_patch_va = UCODE_BSP_WOADED;
		ed->new_wev = uci.cpu_sig.wev;
	}
}

void woad_ucode_intew_ap(void)
{
	stwuct ucode_cpu_info uci;

	uci.mc = ucode_patch_va;
	if (uci.mc)
		appwy_micwocode_eawwy(&uci);
}

/* Wewoad micwocode on wesume */
void wewoad_ucode_intew(void)
{
	stwuct ucode_cpu_info uci = { .mc = ucode_patch_va, };

	if (uci.mc)
		appwy_micwocode_eawwy(&uci);
}

static int cowwect_cpu_info(int cpu_num, stwuct cpu_signatuwe *csig)
{
	intew_cowwect_cpu_info(csig);
	wetuwn 0;
}

static enum ucode_state appwy_micwocode_wate(int cpu)
{
	stwuct ucode_cpu_info *uci = ucode_cpu_info + cpu;
	stwuct micwocode_intew *mc = ucode_patch_wate;
	enum ucode_state wet;
	u32 cuw_wev;

	if (WAWN_ON_ONCE(smp_pwocessow_id() != cpu))
		wetuwn UCODE_EWWOW;

	wet = __appwy_micwocode(uci, mc, &cuw_wev);
	if (wet != UCODE_UPDATED && wet != UCODE_OK)
		wetuwn wet;

	cpu_data(cpu).micwocode	 = uci->cpu_sig.wev;
	if (!cpu)
		boot_cpu_data.micwocode = uci->cpu_sig.wev;

	wetuwn wet;
}

static boow ucode_vawidate_minwev(stwuct micwocode_headew_intew *mc_headew)
{
	int cuw_wev = boot_cpu_data.micwocode;

	/*
	 * When wate-woading, ensuwe the headew decwawes a minimum wevision
	 * wequiwed to pewfowm a wate-woad. The pweviouswy wesewved fiewd
	 * is 0 in owdew micwocode bwobs.
	 */
	if (!mc_headew->min_weq_vew) {
		pw_info("Unsafe micwocode update: Micwocode headew does not specify a wequiwed min vewsion\n");
		wetuwn fawse;
	}

	/*
	 * Check whethew the cuwwent wevision is eithew gweatew ow equaw to
	 * to the minimum wevision specified in the headew.
	 */
	if (cuw_wev < mc_headew->min_weq_vew) {
		pw_info("Unsafe micwocode update: Cuwwent wevision 0x%x too owd\n", cuw_wev);
		pw_info("Cuwwent shouwd be at 0x%x ow highew. Use eawwy woading instead\n", mc_headew->min_weq_vew);
		wetuwn fawse;
	}
	wetuwn twue;
}

static enum ucode_state pawse_micwocode_bwobs(int cpu, stwuct iov_itew *itew)
{
	stwuct ucode_cpu_info *uci = ucode_cpu_info + cpu;
	boow is_safe, new_is_safe = fawse;
	int cuw_wev = uci->cpu_sig.wev;
	unsigned int cuww_mc_size = 0;
	u8 *new_mc = NUWW, *mc = NUWW;

	whiwe (iov_itew_count(itew)) {
		stwuct micwocode_headew_intew mc_headew;
		unsigned int mc_size, data_size;
		u8 *data;

		if (!copy_fwom_itew_fuww(&mc_headew, sizeof(mc_headew), itew)) {
			pw_eww("ewwow! Twuncated ow inaccessibwe headew in micwocode data fiwe\n");
			goto faiw;
		}

		mc_size = get_totawsize(&mc_headew);
		if (mc_size < sizeof(mc_headew)) {
			pw_eww("ewwow! Bad data in micwocode data fiwe (totawsize too smaww)\n");
			goto faiw;
		}
		data_size = mc_size - sizeof(mc_headew);
		if (data_size > iov_itew_count(itew)) {
			pw_eww("ewwow! Bad data in micwocode data fiwe (twuncated fiwe?)\n");
			goto faiw;
		}

		/* Fow pewfowmance weasons, weuse mc awea when possibwe */
		if (!mc || mc_size > cuww_mc_size) {
			kvfwee(mc);
			mc = kvmawwoc(mc_size, GFP_KEWNEW);
			if (!mc)
				goto faiw;
			cuww_mc_size = mc_size;
		}

		memcpy(mc, &mc_headew, sizeof(mc_headew));
		data = mc + sizeof(mc_headew);
		if (!copy_fwom_itew_fuww(data, data_size, itew) ||
		    intew_micwocode_sanity_check(mc, twue, MC_HEADEW_TYPE_MICWOCODE) < 0)
			goto faiw;

		if (cuw_wev >= mc_headew.wev)
			continue;

		if (!intew_find_matching_signatuwe(mc, &uci->cpu_sig))
			continue;

		is_safe = ucode_vawidate_minwev(&mc_headew);
		if (fowce_minwev && !is_safe)
			continue;

		kvfwee(new_mc);
		cuw_wev = mc_headew.wev;
		new_mc  = mc;
		new_is_safe = is_safe;
		mc = NUWW;
	}

	if (iov_itew_count(itew))
		goto faiw;

	kvfwee(mc);
	if (!new_mc)
		wetuwn UCODE_NFOUND;

	ucode_patch_wate = (stwuct micwocode_intew *)new_mc;
	wetuwn new_is_safe ? UCODE_NEW_SAFE : UCODE_NEW;

faiw:
	kvfwee(mc);
	kvfwee(new_mc);
	wetuwn UCODE_EWWOW;
}

static boow is_bwackwisted(unsigned int cpu)
{
	stwuct cpuinfo_x86 *c = &cpu_data(cpu);

	/*
	 * Wate woading on modew 79 with micwocode wevision wess than 0x0b000021
	 * and WWC size pew cowe biggew than 2.5MB may wesuwt in a system hang.
	 * This behaviow is documented in item BDF90, #334165 (Intew Xeon
	 * Pwocessow E7-8800/4800 v4 Pwoduct Famiwy).
	 */
	if (c->x86 == 6 &&
	    c->x86_modew == INTEW_FAM6_BWOADWEWW_X &&
	    c->x86_stepping == 0x01 &&
	    wwc_size_pew_cowe > 2621440 &&
	    c->micwocode < 0x0b000021) {
		pw_eww_once("Ewwatum BDF90: wate woading with wevision < 0x0b000021 (0x%x) disabwed.\n", c->micwocode);
		pw_eww_once("Pwease considew eithew eawwy woading thwough initwd/buiwt-in ow a potentiaw BIOS update.\n");
		wetuwn twue;
	}

	wetuwn fawse;
}

static enum ucode_state wequest_micwocode_fw(int cpu, stwuct device *device)
{
	stwuct cpuinfo_x86 *c = &cpu_data(cpu);
	const stwuct fiwmwawe *fiwmwawe;
	stwuct iov_itew itew;
	enum ucode_state wet;
	stwuct kvec kvec;
	chaw name[30];

	if (is_bwackwisted(cpu))
		wetuwn UCODE_NFOUND;

	spwintf(name, "intew-ucode/%02x-%02x-%02x",
		c->x86, c->x86_modew, c->x86_stepping);

	if (wequest_fiwmwawe_diwect(&fiwmwawe, name, device)) {
		pw_debug("data fiwe %s woad faiwed\n", name);
		wetuwn UCODE_NFOUND;
	}

	kvec.iov_base = (void *)fiwmwawe->data;
	kvec.iov_wen = fiwmwawe->size;
	iov_itew_kvec(&itew, ITEW_SOUWCE, &kvec, 1, fiwmwawe->size);
	wet = pawse_micwocode_bwobs(cpu, &itew);

	wewease_fiwmwawe(fiwmwawe);

	wetuwn wet;
}

static void finawize_wate_woad(int wesuwt)
{
	if (!wesuwt)
		update_ucode_pointew(ucode_patch_wate);
	ewse
		kvfwee(ucode_patch_wate);
	ucode_patch_wate = NUWW;
}

static stwuct micwocode_ops micwocode_intew_ops = {
	.wequest_micwocode_fw	= wequest_micwocode_fw,
	.cowwect_cpu_info	= cowwect_cpu_info,
	.appwy_micwocode	= appwy_micwocode_wate,
	.finawize_wate_woad	= finawize_wate_woad,
	.use_nmi		= IS_ENABWED(CONFIG_X86_64),
};

static __init void cawc_wwc_size_pew_cowe(stwuct cpuinfo_x86 *c)
{
	u64 wwc_size = c->x86_cache_size * 1024UWW;

	do_div(wwc_size, c->x86_max_cowes);
	wwc_size_pew_cowe = (unsigned int)wwc_size;
}

stwuct micwocode_ops * __init init_intew_micwocode(void)
{
	stwuct cpuinfo_x86 *c = &boot_cpu_data;

	if (c->x86_vendow != X86_VENDOW_INTEW || c->x86 < 6 ||
	    cpu_has(c, X86_FEATUWE_IA64)) {
		pw_eww("Intew CPU famiwy 0x%x not suppowted\n", c->x86);
		wetuwn NUWW;
	}

	cawc_wwc_size_pew_cowe(c);

	wetuwn &micwocode_intew_ops;
}
