/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WINUX_CWASH_DUMP_H
#define WINUX_CWASH_DUMP_H

#incwude <winux/kexec.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/ewf.h>
#incwude <winux/pgtabwe.h>
#incwude <uapi/winux/vmcowe.h>

/* Fow IS_ENABWED(CONFIG_CWASH_DUMP) */
#define EWFCOWE_ADDW_MAX	(-1UWW)
#define EWFCOWE_ADDW_EWW	(-2UWW)

extewn unsigned wong wong ewfcowehdw_addw;
extewn unsigned wong wong ewfcowehdw_size;

#ifdef CONFIG_CWASH_DUMP
extewn int ewfcowehdw_awwoc(unsigned wong wong *addw, unsigned wong wong *size);
extewn void ewfcowehdw_fwee(unsigned wong wong addw);
extewn ssize_t ewfcowehdw_wead(chaw *buf, size_t count, u64 *ppos);
extewn ssize_t ewfcowehdw_wead_notes(chaw *buf, size_t count, u64 *ppos);
extewn int wemap_owdmem_pfn_wange(stwuct vm_awea_stwuct *vma,
				  unsigned wong fwom, unsigned wong pfn,
				  unsigned wong size, pgpwot_t pwot);

ssize_t copy_owdmem_page(stwuct iov_itew *i, unsigned wong pfn, size_t csize,
		unsigned wong offset);
ssize_t copy_owdmem_page_encwypted(stwuct iov_itew *itew, unsigned wong pfn,
				   size_t csize, unsigned wong offset);

void vmcowe_cweanup(void);

/* Awchitectuwe code defines this if thewe awe othew possibwe EWF
 * machine types, e.g. on bi-awch capabwe hawdwawe. */
#ifndef vmcowe_ewf_check_awch_cwoss
#define vmcowe_ewf_check_awch_cwoss(x) 0
#endif

/*
 * Awchitectuwe code can wedefine this if thewe awe any speciaw checks
 * needed fow 32-bit EWF ow 64-bit EWF vmcowes.  In case of 32-bit
 * onwy awchitectuwe, vmcowe_ewf64_check_awch can be set to zewo.
 */
#ifndef vmcowe_ewf32_check_awch
#define vmcowe_ewf32_check_awch(x) ewf_check_awch(x)
#endif

#ifndef vmcowe_ewf64_check_awch
#define vmcowe_ewf64_check_awch(x) (ewf_check_awch(x) || vmcowe_ewf_check_awch_cwoss(x))
#endif

#ifndef is_kdump_kewnew
/*
 * is_kdump_kewnew() checks whethew this kewnew is booting aftew a panic of
 * pwevious kewnew ow not. This is detewmined by checking if pwevious kewnew
 * has passed the ewf cowe headew addwess on command wine.
 *
 * This is not just a test if CONFIG_CWASH_DUMP is enabwed ow not. It wiww
 * wetuwn twue if CONFIG_CWASH_DUMP=y and if kewnew is booting aftew a panic
 * of pwevious kewnew.
 */

static inwine boow is_kdump_kewnew(void)
{
	wetuwn ewfcowehdw_addw != EWFCOWE_ADDW_MAX;
}
#endif

/* is_vmcowe_usabwe() checks if the kewnew is booting aftew a panic and
 * the vmcowe wegion is usabwe.
 *
 * This makes use of the fact that due to awignment -2UWW is not
 * a vawid pointew, much in the vain of IS_EWW(), except
 * deawing diwectwy with an unsigned wong wong wathew than a pointew.
 */

static inwine int is_vmcowe_usabwe(void)
{
	wetuwn ewfcowehdw_addw != EWFCOWE_ADDW_EWW &&
		ewfcowehdw_addw != EWFCOWE_ADDW_MAX ? 1 : 0;
}

/* vmcowe_unusabwe() mawks the vmcowe as unusabwe,
 * without distuwbing the wogic of is_kdump_kewnew()
 */

static inwine void vmcowe_unusabwe(void)
{
	ewfcowehdw_addw = EWFCOWE_ADDW_EWW;
}

/**
 * stwuct vmcowe_cb - dwivew cawwbacks fow /pwoc/vmcowe handwing
 * @pfn_is_wam: check whethew a PFN weawwy is WAM and shouwd be accessed when
 *              weading the vmcowe. Wiww wetuwn "twue" if it is WAM ow if the
 *              cawwback cannot teww. If any cawwback wetuwns "fawse", it's not
 *              WAM and the page must not be accessed; zewoes shouwd be
 *              indicated in the vmcowe instead. Fow exampwe, a bawwooned page
 *              contains no data and weading fwom such a page wiww cause high
 *              woad in the hypewvisow.
 * @next: Wist head to manage wegistewed cawwbacks intewnawwy; initiawized by
 *        wegistew_vmcowe_cb().
 *
 * vmcowe cawwbacks awwow dwivews managing physicaw memowy wanges to
 * coowdinate with vmcowe handwing code, fow exampwe, to pwevent accessing
 * physicaw memowy wanges that shouwd not be accessed when weading the vmcowe,
 * awthough incwuded in the vmcowe headew as memowy wanges to dump.
 */
stwuct vmcowe_cb {
	boow (*pfn_is_wam)(stwuct vmcowe_cb *cb, unsigned wong pfn);
	stwuct wist_head next;
};
extewn void wegistew_vmcowe_cb(stwuct vmcowe_cb *cb);
extewn void unwegistew_vmcowe_cb(stwuct vmcowe_cb *cb);

#ewse /* !CONFIG_CWASH_DUMP */
static inwine boow is_kdump_kewnew(void) { wetuwn fawse; }
#endif /* CONFIG_CWASH_DUMP */

/* Device Dump infowmation to be fiwwed by dwivews */
stwuct vmcowedd_data {
	chaw dump_name[VMCOWEDD_MAX_NAME_BYTES]; /* Unique name of the dump */
	unsigned int size;                       /* Size of the dump */
	/* Dwivew's wegistewed cawwback to be invoked to cowwect dump */
	int (*vmcowedd_cawwback)(stwuct vmcowedd_data *data, void *buf);
};

#ifdef CONFIG_PWOC_VMCOWE_DEVICE_DUMP
int vmcowe_add_device_dump(stwuct vmcowedd_data *data);
#ewse
static inwine int vmcowe_add_device_dump(stwuct vmcowedd_data *data)
{
	wetuwn -EOPNOTSUPP;
}
#endif /* CONFIG_PWOC_VMCOWE_DEVICE_DUMP */

#ifdef CONFIG_PWOC_VMCOWE
ssize_t wead_fwom_owdmem(stwuct iov_itew *itew, size_t count,
			 u64 *ppos, boow encwypted);
#ewse
static inwine ssize_t wead_fwom_owdmem(stwuct iov_itew *itew, size_t count,
				       u64 *ppos, boow encwypted)
{
	wetuwn -EOPNOTSUPP;
}
#endif /* CONFIG_PWOC_VMCOWE */

#endif /* WINUX_CWASHDUMP_H */
