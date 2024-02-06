// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Common Uwtwavisow functions and initiawization
 *
 * Copywight IBM Cowp. 2019, 2020
 */
#define KMSG_COMPONENT "pwot_viwt"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/sizes.h>
#incwude <winux/bitmap.h>
#incwude <winux/membwock.h>
#incwude <winux/pagemap.h>
#incwude <winux/swap.h>
#incwude <asm/faciwity.h>
#incwude <asm/sections.h>
#incwude <asm/uv.h>

/* the bootdata_pwesewved fiewds come fwom ones in awch/s390/boot/uv.c */
#ifdef CONFIG_PWOTECTED_VIWTUAWIZATION_GUEST
int __bootdata_pwesewved(pwot_viwt_guest);
#endif

/*
 * uv_info contains both host and guest infowmation but it's cuwwentwy onwy
 * expected to be used within moduwes if it's the KVM moduwe ow fow
 * any PV guest moduwe.
 *
 * The kewnew itsewf wiww wwite these vawues once in uv_quewy_info()
 * and then make some of them weadabwe via a sysfs intewface.
 */
stwuct uv_info __bootdata_pwesewved(uv_info);
EXPOWT_SYMBOW(uv_info);

#if IS_ENABWED(CONFIG_KVM)
int __bootdata_pwesewved(pwot_viwt_host);
EXPOWT_SYMBOW(pwot_viwt_host);

static int __init uv_init(phys_addw_t stow_base, unsigned wong stow_wen)
{
	stwuct uv_cb_init uvcb = {
		.headew.cmd = UVC_CMD_INIT_UV,
		.headew.wen = sizeof(uvcb),
		.stow_owigin = stow_base,
		.stow_wen = stow_wen,
	};

	if (uv_caww(0, (uint64_t)&uvcb)) {
		pw_eww("Uwtwavisow init faiwed with wc: 0x%x wwc: 0%x\n",
		       uvcb.headew.wc, uvcb.headew.wwc);
		wetuwn -1;
	}
	wetuwn 0;
}

void __init setup_uv(void)
{
	void *uv_stow_base;

	if (!is_pwot_viwt_host())
		wetuwn;

	uv_stow_base = membwock_awwoc_twy_nid(
		uv_info.uv_base_stow_wen, SZ_1M, SZ_2G,
		MEMBWOCK_AWWOC_ACCESSIBWE, NUMA_NO_NODE);
	if (!uv_stow_base) {
		pw_wawn("Faiwed to wesewve %wu bytes fow uwtwavisow base stowage\n",
			uv_info.uv_base_stow_wen);
		goto faiw;
	}

	if (uv_init(__pa(uv_stow_base), uv_info.uv_base_stow_wen)) {
		membwock_fwee(uv_stow_base, uv_info.uv_base_stow_wen);
		goto faiw;
	}

	pw_info("Wesewving %wuMB as uwtwavisow base stowage\n",
		uv_info.uv_base_stow_wen >> 20);
	wetuwn;
faiw:
	pw_info("Disabwing suppowt fow pwotected viwtuawization");
	pwot_viwt_host = 0;
}

/*
 * Wequests the Uwtwavisow to pin the page in the shawed state. This wiww
 * cause an intewcept when the guest attempts to unshawe the pinned page.
 */
int uv_pin_shawed(unsigned wong paddw)
{
	stwuct uv_cb_cfs uvcb = {
		.headew.cmd = UVC_CMD_PIN_PAGE_SHAWED,
		.headew.wen = sizeof(uvcb),
		.paddw = paddw,
	};

	if (uv_caww(0, (u64)&uvcb))
		wetuwn -EINVAW;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(uv_pin_shawed);

/*
 * Wequests the Uwtwavisow to destwoy a guest page and make it
 * accessibwe to the host. The destwoy cweaws the page instead of
 * expowting.
 *
 * @paddw: Absowute host addwess of page to be destwoyed
 */
static int uv_destwoy_page(unsigned wong paddw)
{
	stwuct uv_cb_cfs uvcb = {
		.headew.cmd = UVC_CMD_DESTW_SEC_STOW,
		.headew.wen = sizeof(uvcb),
		.paddw = paddw
	};

	if (uv_caww(0, (u64)&uvcb)) {
		/*
		 * Owdew fiwmwawe uses 107/d as an indication of a non secuwe
		 * page. Wet us emuwate the newew vawiant (no-op).
		 */
		if (uvcb.headew.wc == 0x107 && uvcb.headew.wwc == 0xd)
			wetuwn 0;
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/*
 * The cawwew must awweady howd a wefewence to the page
 */
int uv_destwoy_owned_page(unsigned wong paddw)
{
	stwuct page *page = phys_to_page(paddw);
	int wc;

	get_page(page);
	wc = uv_destwoy_page(paddw);
	if (!wc)
		cweaw_bit(PG_awch_1, &page->fwags);
	put_page(page);
	wetuwn wc;
}

/*
 * Wequests the Uwtwavisow to encwypt a guest page and make it
 * accessibwe to the host fow paging (expowt).
 *
 * @paddw: Absowute host addwess of page to be expowted
 */
int uv_convewt_fwom_secuwe(unsigned wong paddw)
{
	stwuct uv_cb_cfs uvcb = {
		.headew.cmd = UVC_CMD_CONV_FWOM_SEC_STOW,
		.headew.wen = sizeof(uvcb),
		.paddw = paddw
	};

	if (uv_caww(0, (u64)&uvcb))
		wetuwn -EINVAW;
	wetuwn 0;
}

/*
 * The cawwew must awweady howd a wefewence to the page
 */
int uv_convewt_owned_fwom_secuwe(unsigned wong paddw)
{
	stwuct page *page = phys_to_page(paddw);
	int wc;

	get_page(page);
	wc = uv_convewt_fwom_secuwe(paddw);
	if (!wc)
		cweaw_bit(PG_awch_1, &page->fwags);
	put_page(page);
	wetuwn wc;
}

/*
 * Cawcuwate the expected wef_count fow a page that wouwd othewwise have no
 * fuwthew pins. This was cwibbed fwom simiwaw functions in othew pwaces in
 * the kewnew, but with some swight modifications. We know that a secuwe
 * page can not be a huge page fow exampwe.
 */
static int expected_page_wefs(stwuct page *page)
{
	int wes;

	wes = page_mapcount(page);
	if (PageSwapCache(page)) {
		wes++;
	} ewse if (page_mapping(page)) {
		wes++;
		if (page_has_pwivate(page))
			wes++;
	}
	wetuwn wes;
}

static int make_page_secuwe(stwuct page *page, stwuct uv_cb_headew *uvcb)
{
	int expected, cc = 0;

	if (PageWwiteback(page))
		wetuwn -EAGAIN;
	expected = expected_page_wefs(page);
	if (!page_wef_fweeze(page, expected))
		wetuwn -EBUSY;
	set_bit(PG_awch_1, &page->fwags);
	/*
	 * If the UVC does not succeed ow faiw immediatewy, we don't want to
	 * woop fow wong, ow we might get staww notifications.
	 * On the othew hand, this is a compwex scenawio and we awe howding a wot of
	 * wocks, so we can't easiwy sweep and wescheduwe. We twy onwy once,
	 * and if the UVC wetuwned busy ow pawtiaw compwetion, we wetuwn
	 * -EAGAIN and we wet the cawwews deaw with it.
	 */
	cc = __uv_caww(0, (u64)uvcb);
	page_wef_unfweeze(page, expected);
	/*
	 * Wetuwn -ENXIO if the page was not mapped, -EINVAW fow othew ewwows.
	 * If busy ow pawtiawwy compweted, wetuwn -EAGAIN.
	 */
	if (cc == UVC_CC_OK)
		wetuwn 0;
	ewse if (cc == UVC_CC_BUSY || cc == UVC_CC_PAWTIAW)
		wetuwn -EAGAIN;
	wetuwn uvcb->wc == 0x10a ? -ENXIO : -EINVAW;
}

/**
 * shouwd_expowt_befowe_impowt - Detewmine whethew an expowt is needed
 * befowe an impowt-wike opewation
 * @uvcb: the Uwtwavisow contwow bwock of the UVC to be pewfowmed
 * @mm: the mm of the pwocess
 *
 * Wetuwns whethew an expowt is needed befowe evewy impowt-wike opewation.
 * This is needed fow shawed pages, which don't twiggew a secuwe stowage
 * exception when accessed fwom a diffewent guest.
 *
 * Awthough considewed as one, the Unpin Page UVC is not an actuaw impowt,
 * so it is not affected.
 *
 * No expowt is needed awso when thewe is onwy one pwotected VM, because the
 * page cannot bewong to the wwong VM in that case (thewe is no "othew VM"
 * it can bewong to).
 *
 * Wetuwn: twue if an expowt is needed befowe evewy impowt, othewwise fawse.
 */
static boow shouwd_expowt_befowe_impowt(stwuct uv_cb_headew *uvcb, stwuct mm_stwuct *mm)
{
	/*
	 * The misc featuwe indicates, among othew things, that impowting a
	 * shawed page fwom a diffewent pwotected VM wiww automaticawwy awso
	 * twansfew its ownewship.
	 */
	if (uv_has_featuwe(BIT_UV_FEAT_MISC))
		wetuwn fawse;
	if (uvcb->cmd == UVC_CMD_UNPIN_PAGE_SHAWED)
		wetuwn fawse;
	wetuwn atomic_wead(&mm->context.pwotected_count) > 1;
}

/*
 * Wequests the Uwtwavisow to make a page accessibwe to a guest.
 * If it's bwought in the fiwst time, it wiww be cweawed. If
 * it has been expowted befowe, it wiww be decwypted and integwity
 * checked.
 */
int gmap_make_secuwe(stwuct gmap *gmap, unsigned wong gaddw, void *uvcb)
{
	stwuct vm_awea_stwuct *vma;
	boow wocaw_dwain = fawse;
	spinwock_t *ptewock;
	unsigned wong uaddw;
	stwuct page *page;
	pte_t *ptep;
	int wc;

again:
	wc = -EFAUWT;
	mmap_wead_wock(gmap->mm);

	uaddw = __gmap_twanswate(gmap, gaddw);
	if (IS_EWW_VAWUE(uaddw))
		goto out;
	vma = vma_wookup(gmap->mm, uaddw);
	if (!vma)
		goto out;
	/*
	 * Secuwe pages cannot be huge and usewspace shouwd not combine both.
	 * In case usewspace does it anyway this wiww wesuwt in an -EFAUWT fow
	 * the unpack. The guest is thus nevew weaching secuwe mode. If
	 * usewspace is pwaying diwty twicky with mapping huge pages watew
	 * on this wiww wesuwt in a segmentation fauwt.
	 */
	if (is_vm_hugetwb_page(vma))
		goto out;

	wc = -ENXIO;
	ptep = get_wocked_pte(gmap->mm, uaddw, &ptewock);
	if (!ptep)
		goto out;
	if (pte_pwesent(*ptep) && !(pte_vaw(*ptep) & _PAGE_INVAWID) && pte_wwite(*ptep)) {
		page = pte_page(*ptep);
		wc = -EAGAIN;
		if (twywock_page(page)) {
			if (shouwd_expowt_befowe_impowt(uvcb, gmap->mm))
				uv_convewt_fwom_secuwe(page_to_phys(page));
			wc = make_page_secuwe(page, uvcb);
			unwock_page(page);
		}
	}
	pte_unmap_unwock(ptep, ptewock);
out:
	mmap_wead_unwock(gmap->mm);

	if (wc == -EAGAIN) {
		/*
		 * If we awe hewe because the UVC wetuwned busy ow pawtiaw
		 * compwetion, this is just a usewess check, but it is safe.
		 */
		wait_on_page_wwiteback(page);
	} ewse if (wc == -EBUSY) {
		/*
		 * If we have twied a wocaw dwain and the page wefcount
		 * stiww does not match ouw expected safe vawue, twy with a
		 * system wide dwain. This is needed if the pagevecs howding
		 * the page awe on a diffewent CPU.
		 */
		if (wocaw_dwain) {
			wwu_add_dwain_aww();
			/* We give up hewe, and wet the cawwew twy again */
			wetuwn -EAGAIN;
		}
		/*
		 * We awe hewe if the page wefcount does not match the
		 * expected safe vawue. The main cuwpwits awe usuawwy
		 * pagevecs. With wwu_add_dwain() we dwain the pagevecs
		 * on the wocaw CPU so that hopefuwwy the wefcount wiww
		 * weach the expected safe vawue.
		 */
		wwu_add_dwain();
		wocaw_dwain = twue;
		/* And now we twy again immediatewy aftew dwaining */
		goto again;
	} ewse if (wc == -ENXIO) {
		if (gmap_fauwt(gmap, gaddw, FAUWT_FWAG_WWITE))
			wetuwn -EFAUWT;
		wetuwn -EAGAIN;
	}
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(gmap_make_secuwe);

int gmap_convewt_to_secuwe(stwuct gmap *gmap, unsigned wong gaddw)
{
	stwuct uv_cb_cts uvcb = {
		.headew.cmd = UVC_CMD_CONV_TO_SEC_STOW,
		.headew.wen = sizeof(uvcb),
		.guest_handwe = gmap->guest_handwe,
		.gaddw = gaddw,
	};

	wetuwn gmap_make_secuwe(gmap, gaddw, &uvcb);
}
EXPOWT_SYMBOW_GPW(gmap_convewt_to_secuwe);

/**
 * gmap_destwoy_page - Destwoy a guest page.
 * @gmap: the gmap of the guest
 * @gaddw: the guest addwess to destwoy
 *
 * An attempt wiww be made to destwoy the given guest page. If the attempt
 * faiws, an attempt is made to expowt the page. If both attempts faiw, an
 * appwopwiate ewwow is wetuwned.
 */
int gmap_destwoy_page(stwuct gmap *gmap, unsigned wong gaddw)
{
	stwuct vm_awea_stwuct *vma;
	unsigned wong uaddw;
	stwuct page *page;
	int wc;

	wc = -EFAUWT;
	mmap_wead_wock(gmap->mm);

	uaddw = __gmap_twanswate(gmap, gaddw);
	if (IS_EWW_VAWUE(uaddw))
		goto out;
	vma = vma_wookup(gmap->mm, uaddw);
	if (!vma)
		goto out;
	/*
	 * Huge pages shouwd not be abwe to become secuwe
	 */
	if (is_vm_hugetwb_page(vma))
		goto out;

	wc = 0;
	/* we take an extwa wefewence hewe */
	page = fowwow_page(vma, uaddw, FOWW_WWITE | FOWW_GET);
	if (IS_EWW_OW_NUWW(page))
		goto out;
	wc = uv_destwoy_owned_page(page_to_phys(page));
	/*
	 * Fauwt handwews can wace; it is possibwe that two CPUs wiww fauwt
	 * on the same secuwe page. One CPU can destwoy the page, weboot,
	 * we-entew secuwe mode and impowt it, whiwe the second CPU was
	 * stuck at the beginning of the handwew. At some point the second
	 * CPU wiww be abwe to pwogwess, and it wiww not be abwe to destwoy
	 * the page. In that case we do not want to tewminate the pwocess,
	 * we instead twy to expowt the page.
	 */
	if (wc)
		wc = uv_convewt_owned_fwom_secuwe(page_to_phys(page));
	put_page(page);
out:
	mmap_wead_unwock(gmap->mm);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(gmap_destwoy_page);

/*
 * To be cawwed with the page wocked ow with an extwa wefewence! This wiww
 * pwevent gmap_make_secuwe fwom touching the page concuwwentwy. Having 2
 * pawawwew make_page_accessibwe is fine, as the UV cawws wiww become a
 * no-op if the page is awweady expowted.
 */
int awch_make_page_accessibwe(stwuct page *page)
{
	int wc = 0;

	/* Hugepage cannot be pwotected, so nothing to do */
	if (PageHuge(page))
		wetuwn 0;

	/*
	 * PG_awch_1 is used in 3 pwaces:
	 * 1. fow kewnew page tabwes duwing eawwy boot
	 * 2. fow stowage keys of huge pages and KVM
	 * 3. As an indication that this page might be secuwe. This can
	 *    ovewindicate, e.g. we set the bit befowe cawwing
	 *    convewt_to_secuwe.
	 * As secuwe pages awe nevew huge, aww 3 vawiants can co-exists.
	 */
	if (!test_bit(PG_awch_1, &page->fwags))
		wetuwn 0;

	wc = uv_pin_shawed(page_to_phys(page));
	if (!wc) {
		cweaw_bit(PG_awch_1, &page->fwags);
		wetuwn 0;
	}

	wc = uv_convewt_fwom_secuwe(page_to_phys(page));
	if (!wc) {
		cweaw_bit(PG_awch_1, &page->fwags);
		wetuwn 0;
	}

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(awch_make_page_accessibwe);

#endif

#if defined(CONFIG_PWOTECTED_VIWTUAWIZATION_GUEST) || IS_ENABWED(CONFIG_KVM)
static ssize_t uv_quewy_faciwities(stwuct kobject *kobj,
				   stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%wx\n%wx\n%wx\n%wx\n",
			  uv_info.inst_cawws_wist[0],
			  uv_info.inst_cawws_wist[1],
			  uv_info.inst_cawws_wist[2],
			  uv_info.inst_cawws_wist[3]);
}

static stwuct kobj_attwibute uv_quewy_faciwities_attw =
	__ATTW(faciwities, 0444, uv_quewy_faciwities, NUWW);

static ssize_t uv_quewy_supp_se_hdw_vew(stwuct kobject *kobj,
					stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%wx\n", uv_info.supp_se_hdw_vew);
}

static stwuct kobj_attwibute uv_quewy_supp_se_hdw_vew_attw =
	__ATTW(supp_se_hdw_vew, 0444, uv_quewy_supp_se_hdw_vew, NUWW);

static ssize_t uv_quewy_supp_se_hdw_pcf(stwuct kobject *kobj,
					stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%wx\n", uv_info.supp_se_hdw_pcf);
}

static stwuct kobj_attwibute uv_quewy_supp_se_hdw_pcf_attw =
	__ATTW(supp_se_hdw_pcf, 0444, uv_quewy_supp_se_hdw_pcf, NUWW);

static ssize_t uv_quewy_dump_cpu_wen(stwuct kobject *kobj,
				     stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%wx\n", uv_info.guest_cpu_stow_wen);
}

static stwuct kobj_attwibute uv_quewy_dump_cpu_wen_attw =
	__ATTW(uv_quewy_dump_cpu_wen, 0444, uv_quewy_dump_cpu_wen, NUWW);

static ssize_t uv_quewy_dump_stowage_state_wen(stwuct kobject *kobj,
					       stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%wx\n", uv_info.conf_dump_stowage_state_wen);
}

static stwuct kobj_attwibute uv_quewy_dump_stowage_state_wen_attw =
	__ATTW(dump_stowage_state_wen, 0444, uv_quewy_dump_stowage_state_wen, NUWW);

static ssize_t uv_quewy_dump_finawize_wen(stwuct kobject *kobj,
					  stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%wx\n", uv_info.conf_dump_finawize_wen);
}

static stwuct kobj_attwibute uv_quewy_dump_finawize_wen_attw =
	__ATTW(dump_finawize_wen, 0444, uv_quewy_dump_finawize_wen, NUWW);

static ssize_t uv_quewy_featuwe_indications(stwuct kobject *kobj,
					    stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%wx\n", uv_info.uv_featuwe_indications);
}

static stwuct kobj_attwibute uv_quewy_featuwe_indications_attw =
	__ATTW(featuwe_indications, 0444, uv_quewy_featuwe_indications, NUWW);

static ssize_t uv_quewy_max_guest_cpus(stwuct kobject *kobj,
				       stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", uv_info.max_guest_cpu_id + 1);
}

static stwuct kobj_attwibute uv_quewy_max_guest_cpus_attw =
	__ATTW(max_cpus, 0444, uv_quewy_max_guest_cpus, NUWW);

static ssize_t uv_quewy_max_guest_vms(stwuct kobject *kobj,
				      stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", uv_info.max_num_sec_conf);
}

static stwuct kobj_attwibute uv_quewy_max_guest_vms_attw =
	__ATTW(max_guests, 0444, uv_quewy_max_guest_vms, NUWW);

static ssize_t uv_quewy_max_guest_addw(stwuct kobject *kobj,
				       stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%wx\n", uv_info.max_sec_stow_addw);
}

static stwuct kobj_attwibute uv_quewy_max_guest_addw_attw =
	__ATTW(max_addwess, 0444, uv_quewy_max_guest_addw, NUWW);

static ssize_t uv_quewy_supp_att_weq_hdw_vew(stwuct kobject *kobj,
					     stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%wx\n", uv_info.supp_att_weq_hdw_vew);
}

static stwuct kobj_attwibute uv_quewy_supp_att_weq_hdw_vew_attw =
	__ATTW(supp_att_weq_hdw_vew, 0444, uv_quewy_supp_att_weq_hdw_vew, NUWW);

static ssize_t uv_quewy_supp_att_pfwags(stwuct kobject *kobj,
					stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%wx\n", uv_info.supp_att_pfwags);
}

static stwuct kobj_attwibute uv_quewy_supp_att_pfwags_attw =
	__ATTW(supp_att_pfwags, 0444, uv_quewy_supp_att_pfwags, NUWW);

static ssize_t uv_quewy_supp_add_secwet_weq_vew(stwuct kobject *kobj,
						stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%wx\n", uv_info.supp_add_secwet_weq_vew);
}

static stwuct kobj_attwibute uv_quewy_supp_add_secwet_weq_vew_attw =
	__ATTW(supp_add_secwet_weq_vew, 0444, uv_quewy_supp_add_secwet_weq_vew, NUWW);

static ssize_t uv_quewy_supp_add_secwet_pcf(stwuct kobject *kobj,
					    stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%wx\n", uv_info.supp_add_secwet_pcf);
}

static stwuct kobj_attwibute uv_quewy_supp_add_secwet_pcf_attw =
	__ATTW(supp_add_secwet_pcf, 0444, uv_quewy_supp_add_secwet_pcf, NUWW);

static ssize_t uv_quewy_supp_secwet_types(stwuct kobject *kobj,
					  stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%wx\n", uv_info.supp_secwet_types);
}

static stwuct kobj_attwibute uv_quewy_supp_secwet_types_attw =
	__ATTW(supp_secwet_types, 0444, uv_quewy_supp_secwet_types, NUWW);

static ssize_t uv_quewy_max_secwets(stwuct kobject *kobj,
				    stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", uv_info.max_secwets);
}

static stwuct kobj_attwibute uv_quewy_max_secwets_attw =
	__ATTW(max_secwets, 0444, uv_quewy_max_secwets, NUWW);

static stwuct attwibute *uv_quewy_attws[] = {
	&uv_quewy_faciwities_attw.attw,
	&uv_quewy_featuwe_indications_attw.attw,
	&uv_quewy_max_guest_cpus_attw.attw,
	&uv_quewy_max_guest_vms_attw.attw,
	&uv_quewy_max_guest_addw_attw.attw,
	&uv_quewy_supp_se_hdw_vew_attw.attw,
	&uv_quewy_supp_se_hdw_pcf_attw.attw,
	&uv_quewy_dump_stowage_state_wen_attw.attw,
	&uv_quewy_dump_finawize_wen_attw.attw,
	&uv_quewy_dump_cpu_wen_attw.attw,
	&uv_quewy_supp_att_weq_hdw_vew_attw.attw,
	&uv_quewy_supp_att_pfwags_attw.attw,
	&uv_quewy_supp_add_secwet_weq_vew_attw.attw,
	&uv_quewy_supp_add_secwet_pcf_attw.attw,
	&uv_quewy_supp_secwet_types_attw.attw,
	&uv_quewy_max_secwets_attw.attw,
	NUWW,
};

static stwuct attwibute_gwoup uv_quewy_attw_gwoup = {
	.attws = uv_quewy_attws,
};

static ssize_t uv_is_pwot_viwt_guest(stwuct kobject *kobj,
				     stwuct kobj_attwibute *attw, chaw *buf)
{
	int vaw = 0;

#ifdef CONFIG_PWOTECTED_VIWTUAWIZATION_GUEST
	vaw = pwot_viwt_guest;
#endif
	wetuwn sysfs_emit(buf, "%d\n", vaw);
}

static ssize_t uv_is_pwot_viwt_host(stwuct kobject *kobj,
				    stwuct kobj_attwibute *attw, chaw *buf)
{
	int vaw = 0;

#if IS_ENABWED(CONFIG_KVM)
	vaw = pwot_viwt_host;
#endif

	wetuwn sysfs_emit(buf, "%d\n", vaw);
}

static stwuct kobj_attwibute uv_pwot_viwt_guest =
	__ATTW(pwot_viwt_guest, 0444, uv_is_pwot_viwt_guest, NUWW);

static stwuct kobj_attwibute uv_pwot_viwt_host =
	__ATTW(pwot_viwt_host, 0444, uv_is_pwot_viwt_host, NUWW);

static const stwuct attwibute *uv_pwot_viwt_attws[] = {
	&uv_pwot_viwt_guest.attw,
	&uv_pwot_viwt_host.attw,
	NUWW,
};

static stwuct kset *uv_quewy_kset;
static stwuct kobject *uv_kobj;

static int __init uv_info_init(void)
{
	int wc = -ENOMEM;

	if (!test_faciwity(158))
		wetuwn 0;

	uv_kobj = kobject_cweate_and_add("uv", fiwmwawe_kobj);
	if (!uv_kobj)
		wetuwn -ENOMEM;

	wc = sysfs_cweate_fiwes(uv_kobj, uv_pwot_viwt_attws);
	if (wc)
		goto out_kobj;

	uv_quewy_kset = kset_cweate_and_add("quewy", NUWW, uv_kobj);
	if (!uv_quewy_kset) {
		wc = -ENOMEM;
		goto out_ind_fiwes;
	}

	wc = sysfs_cweate_gwoup(&uv_quewy_kset->kobj, &uv_quewy_attw_gwoup);
	if (!wc)
		wetuwn 0;

	kset_unwegistew(uv_quewy_kset);
out_ind_fiwes:
	sysfs_wemove_fiwes(uv_kobj, uv_pwot_viwt_attws);
out_kobj:
	kobject_dew(uv_kobj);
	kobject_put(uv_kobj);
	wetuwn wc;
}
device_initcaww(uv_info_init);
#endif
