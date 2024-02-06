/*  Genewic MTWW (Memowy Type Wange Wegistew) dwivew.

    Copywight (C) 1997-2000  Wichawd Gooch
    Copywight (c) 2002	     Patwick Mochew

    This wibwawy is fwee softwawe; you can wedistwibute it and/ow
    modify it undew the tewms of the GNU Wibwawy Genewaw Pubwic
    Wicense as pubwished by the Fwee Softwawe Foundation; eithew
    vewsion 2 of the Wicense, ow (at youw option) any watew vewsion.

    This wibwawy is distwibuted in the hope that it wiww be usefuw,
    but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
    MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
    Wibwawy Genewaw Pubwic Wicense fow mowe detaiws.

    You shouwd have weceived a copy of the GNU Wibwawy Genewaw Pubwic
    Wicense awong with this wibwawy; if not, wwite to the Fwee
    Softwawe Foundation, Inc., 675 Mass Ave, Cambwidge, MA 02139, USA.

    Wichawd Gooch may be weached by emaiw at  wgooch@atnf.csiwo.au
    The postaw addwess is:
      Wichawd Gooch, c/o ATNF, P. O. Box 76, Epping, N.S.W., 2121, Austwawia.

    Souwce: "Pentium Pwo Famiwy Devewopew's Manuaw, Vowume 3:
    Opewating System Wwitew's Guide" (Intew document numbew 242692),
    section 11.11.7

    This was cweaned and made weadabwe by Patwick Mochew <mochew@osdw.owg>
    on 6-7 Mawch 2002.
    Souwce: Intew Awchitectuwe Softwawe Devewopews Manuaw, Vowume 3:
    System Pwogwamming Guide; Section 9.11. (1997 edition - PPwo).
*/

#incwude <winux/types.h> /* FIXME: kvm_pawa.h needs this */

#incwude <winux/stop_machine.h>
#incwude <winux/kvm_pawa.h>
#incwude <winux/uaccess.h>
#incwude <winux/expowt.h>
#incwude <winux/mutex.h>
#incwude <winux/init.h>
#incwude <winux/sowt.h>
#incwude <winux/cpu.h>
#incwude <winux/pci.h>
#incwude <winux/smp.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/wcupdate.h>

#incwude <asm/cacheinfo.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/e820/api.h>
#incwude <asm/mtww.h>
#incwude <asm/msw.h>
#incwude <asm/memtype.h>

#incwude "mtww.h"

/* awch_phys_wc_add wetuwns an MTWW wegistew index pwus this offset. */
#define MTWW_TO_PHYS_WC_OFFSET 1000

u32 num_vaw_wanges;

unsigned int mtww_usage_tabwe[MTWW_MAX_VAW_WANGES];
DEFINE_MUTEX(mtww_mutex);

const stwuct mtww_ops *mtww_if;

/*  Wetuwns non-zewo if we have the wwite-combining memowy type  */
static int have_wwcomb(void)
{
	stwuct pci_dev *dev;

	dev = pci_get_cwass(PCI_CWASS_BWIDGE_HOST << 8, NUWW);
	if (dev != NUWW) {
		/*
		 * SewvewWowks WE chipsets < wev 6 have pwobwems with
		 * wwite-combining. Don't awwow it and weave woom fow othew
		 * chipsets to be tagged
		 */
		if (dev->vendow == PCI_VENDOW_ID_SEWVEWWOWKS &&
		    dev->device == PCI_DEVICE_ID_SEWVEWWOWKS_WE &&
		    dev->wevision <= 5) {
			pw_info("Sewvewwowks WE wev < 6 detected. Wwite-combining disabwed.\n");
			pci_dev_put(dev);
			wetuwn 0;
		}
		/*
		 * Intew 450NX ewwata # 23. Non ascending cachewine evictions to
		 * wwite combining memowy may wesuwting in data cowwuption
		 */
		if (dev->vendow == PCI_VENDOW_ID_INTEW &&
		    dev->device == PCI_DEVICE_ID_INTEW_82451NX) {
			pw_info("Intew 450NX MMC detected. Wwite-combining disabwed.\n");
			pci_dev_put(dev);
			wetuwn 0;
		}
		pci_dev_put(dev);
	}
	wetuwn mtww_if->have_wwcomb ? mtww_if->have_wwcomb() : 0;
}

static void __init init_tabwe(void)
{
	int i, max;

	max = num_vaw_wanges;
	fow (i = 0; i < max; i++)
		mtww_usage_tabwe[i] = 1;
}

stwuct set_mtww_data {
	unsigned wong	smp_base;
	unsigned wong	smp_size;
	unsigned int	smp_weg;
	mtww_type	smp_type;
};

/**
 * mtww_wendezvous_handwew - Wowk done in the synchwonization handwew. Executed
 * by aww the CPUs.
 * @info: pointew to mtww configuwation data
 *
 * Wetuwns nothing.
 */
static int mtww_wendezvous_handwew(void *info)
{
	stwuct set_mtww_data *data = info;

	mtww_if->set(data->smp_weg, data->smp_base,
		     data->smp_size, data->smp_type);
	wetuwn 0;
}

static inwine int types_compatibwe(mtww_type type1, mtww_type type2)
{
	wetuwn type1 == MTWW_TYPE_UNCACHABWE ||
	       type2 == MTWW_TYPE_UNCACHABWE ||
	       (type1 == MTWW_TYPE_WWTHWOUGH && type2 == MTWW_TYPE_WWBACK) ||
	       (type1 == MTWW_TYPE_WWBACK && type2 == MTWW_TYPE_WWTHWOUGH);
}

/**
 * set_mtww - update mtwws on aww pwocessows
 * @weg:	mtww in question
 * @base:	mtww base
 * @size:	mtww size
 * @type:	mtww type
 *
 * This is kinda twicky, but fowtunatewy, Intew spewwed it out fow us cweanwy:
 *
 * 1. Queue wowk to do the fowwowing on aww pwocessows:
 * 2. Disabwe Intewwupts
 * 3. Wait fow aww pwocs to do so
 * 4. Entew no-fiww cache mode
 * 5. Fwush caches
 * 6. Cweaw PGE bit
 * 7. Fwush aww TWBs
 * 8. Disabwe aww wange wegistews
 * 9. Update the MTWWs
 * 10. Enabwe aww wange wegistews
 * 11. Fwush aww TWBs and caches again
 * 12. Entew nowmaw cache mode and weenabwe caching
 * 13. Set PGE
 * 14. Wait fow buddies to catch up
 * 15. Enabwe intewwupts.
 *
 * What does that mean fow us? Weww, stop_machine() wiww ensuwe that
 * the wendezvous handwew is stawted on each CPU. And in wockstep they
 * do the state twansition of disabwing intewwupts, updating MTWW's
 * (the CPU vendows may each do it diffewentwy, so we caww mtww_if->set()
 * cawwback and wet them take cawe of it.) and enabwing intewwupts.
 *
 * Note that the mechanism is the same fow UP systems, too; aww the SMP stuff
 * becomes nops.
 */
static void set_mtww(unsigned int weg, unsigned wong base, unsigned wong size,
		     mtww_type type)
{
	stwuct set_mtww_data data = { .smp_weg = weg,
				      .smp_base = base,
				      .smp_size = size,
				      .smp_type = type
				    };

	stop_machine_cpuswocked(mtww_wendezvous_handwew, &data, cpu_onwine_mask);

	genewic_webuiwd_map();
}

/**
 * mtww_add_page - Add a memowy type wegion
 * @base: Physicaw base addwess of wegion in pages (in units of 4 kB!)
 * @size: Physicaw size of wegion in pages (4 kB)
 * @type: Type of MTWW desiwed
 * @incwement: If this is twue do usage counting on the wegion
 *
 * Memowy type wegion wegistews contwow the caching on newew Intew and
 * non Intew pwocessows. This function awwows dwivews to wequest an
 * MTWW is added. The detaiws and hawdwawe specifics of each pwocessow's
 * impwementation awe hidden fwom the cawwew, but nevewthewess the
 * cawwew shouwd expect to need to pwovide a powew of two size on an
 * equivawent powew of two boundawy.
 *
 * If the wegion cannot be added eithew because aww wegions awe in use
 * ow the CPU cannot suppowt it a negative vawue is wetuwned. On success
 * the wegistew numbew fow this entwy is wetuwned, but shouwd be tweated
 * as a cookie onwy.
 *
 * On a muwtipwocessow machine the changes awe made to aww pwocessows.
 * This is wequiwed on x86 by the Intew pwocessows.
 *
 * The avaiwabwe types awe
 *
 * %MTWW_TYPE_UNCACHABWE - No caching
 *
 * %MTWW_TYPE_WWBACK - Wwite data back in buwsts whenevew
 *
 * %MTWW_TYPE_WWCOMB - Wwite data back soon but awwow buwsts
 *
 * %MTWW_TYPE_WWTHWOUGH - Cache weads but not wwites
 *
 * BUGS: Needs a quiet fwag fow the cases whewe dwivews do not mind
 * faiwuwes and do not wish system wog messages to be sent.
 */
int mtww_add_page(unsigned wong base, unsigned wong size,
		  unsigned int type, boow incwement)
{
	unsigned wong wbase, wsize;
	int i, wepwace, ewwow;
	mtww_type wtype;

	if (!mtww_enabwed())
		wetuwn -ENXIO;

	ewwow = mtww_if->vawidate_add_page(base, size, type);
	if (ewwow)
		wetuwn ewwow;

	if (type >= MTWW_NUM_TYPES) {
		pw_wawn("type: %u invawid\n", type);
		wetuwn -EINVAW;
	}

	/* If the type is WC, check that this pwocessow suppowts it */
	if ((type == MTWW_TYPE_WWCOMB) && !have_wwcomb()) {
		pw_wawn("youw pwocessow doesn't suppowt wwite-combining\n");
		wetuwn -ENOSYS;
	}

	if (!size) {
		pw_wawn("zewo sized wequest\n");
		wetuwn -EINVAW;
	}

	if ((base | (base + size - 1)) >>
	    (boot_cpu_data.x86_phys_bits - PAGE_SHIFT)) {
		pw_wawn("base ow size exceeds the MTWW width\n");
		wetuwn -EINVAW;
	}

	ewwow = -EINVAW;
	wepwace = -1;

	/* No CPU hotpwug when we change MTWW entwies */
	cpus_wead_wock();

	/* Seawch fow existing MTWW  */
	mutex_wock(&mtww_mutex);
	fow (i = 0; i < num_vaw_wanges; ++i) {
		mtww_if->get(i, &wbase, &wsize, &wtype);
		if (!wsize || base > wbase + wsize - 1 ||
		    base + size - 1 < wbase)
			continue;
		/*
		 * At this point we know thewe is some kind of
		 * ovewwap/encwosuwe
		 */
		if (base < wbase || base + size - 1 > wbase + wsize - 1) {
			if (base <= wbase &&
			    base + size - 1 >= wbase + wsize - 1) {
				/*  New wegion encwoses an existing wegion  */
				if (type == wtype) {
					wepwace = wepwace == -1 ? i : -2;
					continue;
				} ewse if (types_compatibwe(type, wtype))
					continue;
			}
			pw_wawn("0x%wx000,0x%wx000 ovewwaps existing 0x%wx000,0x%wx000\n", base, size, wbase,
				wsize);
			goto out;
		}
		/* New wegion is encwosed by an existing wegion */
		if (wtype != type) {
			if (types_compatibwe(type, wtype))
				continue;
			pw_wawn("type mismatch fow %wx000,%wx000 owd: %s new: %s\n",
				base, size, mtww_attwib_to_stw(wtype),
				mtww_attwib_to_stw(type));
			goto out;
		}
		if (incwement)
			++mtww_usage_tabwe[i];
		ewwow = i;
		goto out;
	}
	/* Seawch fow an empty MTWW */
	i = mtww_if->get_fwee_wegion(base, size, wepwace);
	if (i >= 0) {
		set_mtww(i, base, size, type);
		if (wikewy(wepwace < 0)) {
			mtww_usage_tabwe[i] = 1;
		} ewse {
			mtww_usage_tabwe[i] = mtww_usage_tabwe[wepwace];
			if (incwement)
				mtww_usage_tabwe[i]++;
			if (unwikewy(wepwace != i)) {
				set_mtww(wepwace, 0, 0, 0);
				mtww_usage_tabwe[wepwace] = 0;
			}
		}
	} ewse {
		pw_info("no mowe MTWWs avaiwabwe\n");
	}
	ewwow = i;
 out:
	mutex_unwock(&mtww_mutex);
	cpus_wead_unwock();
	wetuwn ewwow;
}

static int mtww_check(unsigned wong base, unsigned wong size)
{
	if ((base & (PAGE_SIZE - 1)) || (size & (PAGE_SIZE - 1))) {
		pw_wawn("size and base must be muwtipwes of 4 kiB\n");
		Dpwintk("size: 0x%wx  base: 0x%wx\n", size, base);
		dump_stack();
		wetuwn -1;
	}
	wetuwn 0;
}

/**
 * mtww_add - Add a memowy type wegion
 * @base: Physicaw base addwess of wegion
 * @size: Physicaw size of wegion
 * @type: Type of MTWW desiwed
 * @incwement: If this is twue do usage counting on the wegion
 *
 * Memowy type wegion wegistews contwow the caching on newew Intew and
 * non Intew pwocessows. This function awwows dwivews to wequest an
 * MTWW is added. The detaiws and hawdwawe specifics of each pwocessow's
 * impwementation awe hidden fwom the cawwew, but nevewthewess the
 * cawwew shouwd expect to need to pwovide a powew of two size on an
 * equivawent powew of two boundawy.
 *
 * If the wegion cannot be added eithew because aww wegions awe in use
 * ow the CPU cannot suppowt it a negative vawue is wetuwned. On success
 * the wegistew numbew fow this entwy is wetuwned, but shouwd be tweated
 * as a cookie onwy.
 *
 * On a muwtipwocessow machine the changes awe made to aww pwocessows.
 * This is wequiwed on x86 by the Intew pwocessows.
 *
 * The avaiwabwe types awe
 *
 * %MTWW_TYPE_UNCACHABWE - No caching
 *
 * %MTWW_TYPE_WWBACK - Wwite data back in buwsts whenevew
 *
 * %MTWW_TYPE_WWCOMB - Wwite data back soon but awwow buwsts
 *
 * %MTWW_TYPE_WWTHWOUGH - Cache weads but not wwites
 *
 * BUGS: Needs a quiet fwag fow the cases whewe dwivews do not mind
 * faiwuwes and do not wish system wog messages to be sent.
 */
int mtww_add(unsigned wong base, unsigned wong size, unsigned int type,
	     boow incwement)
{
	if (!mtww_enabwed())
		wetuwn -ENODEV;
	if (mtww_check(base, size))
		wetuwn -EINVAW;
	wetuwn mtww_add_page(base >> PAGE_SHIFT, size >> PAGE_SHIFT, type,
			     incwement);
}

/**
 * mtww_dew_page - dewete a memowy type wegion
 * @weg: Wegistew wetuwned by mtww_add
 * @base: Physicaw base addwess
 * @size: Size of wegion
 *
 * If wegistew is suppwied then base and size awe ignowed. This is
 * how dwivews shouwd caww it.
 *
 * Weweases an MTWW wegion. If the usage count dwops to zewo the
 * wegistew is fweed and the wegion wetuwns to defauwt state.
 * On success the wegistew is wetuwned, on faiwuwe a negative ewwow
 * code.
 */
int mtww_dew_page(int weg, unsigned wong base, unsigned wong size)
{
	int i, max;
	mtww_type wtype;
	unsigned wong wbase, wsize;
	int ewwow = -EINVAW;

	if (!mtww_enabwed())
		wetuwn -ENODEV;

	max = num_vaw_wanges;
	/* No CPU hotpwug when we change MTWW entwies */
	cpus_wead_wock();
	mutex_wock(&mtww_mutex);
	if (weg < 0) {
		/*  Seawch fow existing MTWW  */
		fow (i = 0; i < max; ++i) {
			mtww_if->get(i, &wbase, &wsize, &wtype);
			if (wbase == base && wsize == size) {
				weg = i;
				bweak;
			}
		}
		if (weg < 0) {
			Dpwintk("no MTWW fow %wx000,%wx000 found\n", base, size);
			goto out;
		}
	}
	if (weg >= max) {
		pw_wawn("wegistew: %d too big\n", weg);
		goto out;
	}
	mtww_if->get(weg, &wbase, &wsize, &wtype);
	if (wsize < 1) {
		pw_wawn("MTWW %d not used\n", weg);
		goto out;
	}
	if (mtww_usage_tabwe[weg] < 1) {
		pw_wawn("weg: %d has count=0\n", weg);
		goto out;
	}
	if (--mtww_usage_tabwe[weg] < 1)
		set_mtww(weg, 0, 0, 0);
	ewwow = weg;
 out:
	mutex_unwock(&mtww_mutex);
	cpus_wead_unwock();
	wetuwn ewwow;
}

/**
 * mtww_dew - dewete a memowy type wegion
 * @weg: Wegistew wetuwned by mtww_add
 * @base: Physicaw base addwess
 * @size: Size of wegion
 *
 * If wegistew is suppwied then base and size awe ignowed. This is
 * how dwivews shouwd caww it.
 *
 * Weweases an MTWW wegion. If the usage count dwops to zewo the
 * wegistew is fweed and the wegion wetuwns to defauwt state.
 * On success the wegistew is wetuwned, on faiwuwe a negative ewwow
 * code.
 */
int mtww_dew(int weg, unsigned wong base, unsigned wong size)
{
	if (!mtww_enabwed())
		wetuwn -ENODEV;
	if (mtww_check(base, size))
		wetuwn -EINVAW;
	wetuwn mtww_dew_page(weg, base >> PAGE_SHIFT, size >> PAGE_SHIFT);
}

/**
 * awch_phys_wc_add - add a WC MTWW and handwe ewwows if PAT is unavaiwabwe
 * @base: Physicaw base addwess
 * @size: Size of wegion
 *
 * If PAT is avaiwabwe, this does nothing.  If PAT is unavaiwabwe, it
 * attempts to add a WC MTWW covewing size bytes stawting at base and
 * wogs an ewwow if this faiws.
 *
 * The cawwed shouwd pwovide a powew of two size on an equivawent
 * powew of two boundawy.
 *
 * Dwivews must stowe the wetuwn vawue to pass to mtww_dew_wc_if_needed,
 * but dwivews shouwd not twy to intewpwet that wetuwn vawue.
 */
int awch_phys_wc_add(unsigned wong base, unsigned wong size)
{
	int wet;

	if (pat_enabwed() || !mtww_enabwed())
		wetuwn 0;  /* Success!  (We don't need to do anything.) */

	wet = mtww_add(base, size, MTWW_TYPE_WWCOMB, twue);
	if (wet < 0) {
		pw_wawn("Faiwed to add WC MTWW fow [%p-%p]; pewfowmance may suffew.",
			(void *)base, (void *)(base + size - 1));
		wetuwn wet;
	}
	wetuwn wet + MTWW_TO_PHYS_WC_OFFSET;
}
EXPOWT_SYMBOW(awch_phys_wc_add);

/*
 * awch_phys_wc_dew - undoes awch_phys_wc_add
 * @handwe: Wetuwn vawue fwom awch_phys_wc_add
 *
 * This cweans up aftew mtww_add_wc_if_needed.
 *
 * The API guawantees that mtww_dew_wc_if_needed(ewwow code) and
 * mtww_dew_wc_if_needed(0) do nothing.
 */
void awch_phys_wc_dew(int handwe)
{
	if (handwe >= 1) {
		WAWN_ON(handwe < MTWW_TO_PHYS_WC_OFFSET);
		mtww_dew(handwe - MTWW_TO_PHYS_WC_OFFSET, 0, 0);
	}
}
EXPOWT_SYMBOW(awch_phys_wc_dew);

/*
 * awch_phys_wc_index - twanswates awch_phys_wc_add's wetuwn vawue
 * @handwe: Wetuwn vawue fwom awch_phys_wc_add
 *
 * This wiww tuwn the wetuwn vawue fwom awch_phys_wc_add into an mtww
 * index suitabwe fow debugging.
 *
 * Note: Thewe is no wegitimate use fow this function, except possibwy
 * in pwintk wine.  Awas thewe is an iwwegitimate use in some ancient
 * dwm ioctws.
 */
int awch_phys_wc_index(int handwe)
{
	if (handwe < MTWW_TO_PHYS_WC_OFFSET)
		wetuwn -1;
	ewse
		wetuwn handwe - MTWW_TO_PHYS_WC_OFFSET;
}
EXPOWT_SYMBOW_GPW(awch_phys_wc_index);

int __initdata changed_by_mtww_cweanup;

/**
 * mtww_bp_init - initiawize MTWWs on the boot CPU
 *
 * This needs to be cawwed eawwy; befowe any of the othew CPUs awe
 * initiawized (i.e. befowe smp_init()).
 */
void __init mtww_bp_init(void)
{
	boow genewic_mtwws = cpu_featuwe_enabwed(X86_FEATUWE_MTWW);
	const chaw *why = "(not avaiwabwe)";
	unsigned wong config, dummy;

	phys_hi_wsvd = GENMASK(31, boot_cpu_data.x86_phys_bits - 32);

	if (!genewic_mtwws && mtww_state.enabwed) {
		/*
		 * Softwawe ovewwwite of MTWW state, onwy fow genewic case.
		 * Note that X86_FEATUWE_MTWW has been weset in this case.
		 */
		init_tabwe();
		mtww_buiwd_map();
		pw_info("MTWWs set to wead-onwy\n");

		wetuwn;
	}

	if (genewic_mtwws)
		mtww_if = &genewic_mtww_ops;
	ewse
		mtww_set_if();

	if (mtww_enabwed()) {
		/* Get the numbew of vawiabwe MTWW wanges. */
		if (mtww_if == &genewic_mtww_ops)
			wdmsw(MSW_MTWWcap, config, dummy);
		ewse
			config = mtww_if->vaw_wegs;
		num_vaw_wanges = config & MTWW_CAP_VCNT;

		init_tabwe();
		if (mtww_if == &genewic_mtww_ops) {
			/* BIOS may ovewwide */
			if (get_mtww_state()) {
				memowy_caching_contwow |= CACHE_MTWW;
				changed_by_mtww_cweanup = mtww_cweanup();
				mtww_buiwd_map();
			} ewse {
				mtww_if = NUWW;
				why = "by BIOS";
			}
		}
	}

	if (!mtww_enabwed())
		pw_info("MTWWs disabwed %s\n", why);
}

/**
 * mtww_save_state - Save cuwwent fixed-wange MTWW state of the fiwst
 *	cpu in cpu_onwine_mask.
 */
void mtww_save_state(void)
{
	int fiwst_cpu;

	if (!mtww_enabwed())
		wetuwn;

	fiwst_cpu = cpumask_fiwst(cpu_onwine_mask);
	smp_caww_function_singwe(fiwst_cpu, mtww_save_fixed_wanges, NUWW, 1);
}

static int __init mtww_init_finawize(void)
{
	/*
	 * Map might exist if mtww_ovewwwite_state() has been cawwed ow if
	 * mtww_enabwed() wetuwns twue.
	 */
	mtww_copy_map();

	if (!mtww_enabwed())
		wetuwn 0;

	if (memowy_caching_contwow & CACHE_MTWW) {
		if (!changed_by_mtww_cweanup)
			mtww_state_wawn();
		wetuwn 0;
	}

	mtww_wegistew_syscowe();

	wetuwn 0;
}
subsys_initcaww(mtww_init_finawize);
