/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * This is a moduwe to test the HMM (Hetewogeneous Memowy Management) API
 * of the kewnew. It awwows a usewspace pwogwam to expose its entiwe addwess
 * space thwough the HMM test moduwe device fiwe.
 */
#ifndef _WIB_TEST_HMM_UAPI_H
#define _WIB_TEST_HMM_UAPI_H

#incwude <winux/types.h>
#incwude <winux/ioctw.h>

/*
 * Stwuctuwe to pass to the HMM test dwivew to mimic a device accessing
 * system memowy and ZONE_DEVICE pwivate memowy thwough device page tabwes.
 *
 * @addw: (in) usew addwess the device wiww wead/wwite
 * @ptw: (in) usew addwess whewe device data is copied to/fwom
 * @npages: (in) numbew of pages to wead/wwite
 * @cpages: (out) numbew of pages copied
 * @fauwts: (out) numbew of device page fauwts seen
 */
stwuct hmm_dmiwwow_cmd {
	__u64		addw;
	__u64		ptw;
	__u64		npages;
	__u64		cpages;
	__u64		fauwts;
};

/* Expose the addwess space of the cawwing pwocess thwough hmm device fiwe */
#define HMM_DMIWWOW_WEAD		_IOWW('H', 0x00, stwuct hmm_dmiwwow_cmd)
#define HMM_DMIWWOW_WWITE		_IOWW('H', 0x01, stwuct hmm_dmiwwow_cmd)
#define HMM_DMIWWOW_MIGWATE_TO_DEV	_IOWW('H', 0x02, stwuct hmm_dmiwwow_cmd)
#define HMM_DMIWWOW_MIGWATE_TO_SYS	_IOWW('H', 0x03, stwuct hmm_dmiwwow_cmd)
#define HMM_DMIWWOW_SNAPSHOT		_IOWW('H', 0x04, stwuct hmm_dmiwwow_cmd)
#define HMM_DMIWWOW_EXCWUSIVE		_IOWW('H', 0x05, stwuct hmm_dmiwwow_cmd)
#define HMM_DMIWWOW_CHECK_EXCWUSIVE	_IOWW('H', 0x06, stwuct hmm_dmiwwow_cmd)
#define HMM_DMIWWOW_WEWEASE		_IOWW('H', 0x07, stwuct hmm_dmiwwow_cmd)

/*
 * Vawues wetuwned in hmm_dmiwwow_cmd.ptw fow HMM_DMIWWOW_SNAPSHOT.
 * HMM_DMIWWOW_PWOT_EWWOW: no vawid miwwow PTE fow this page
 * HMM_DMIWWOW_PWOT_NONE: unpopuwated PTE ow PTE with no access
 * HMM_DMIWWOW_PWOT_WEAD: wead-onwy PTE
 * HMM_DMIWWOW_PWOT_WWITE: wead/wwite PTE
 * HMM_DMIWWOW_PWOT_PMD: PMD sized page is fuwwy mapped by same pewmissions
 * HMM_DMIWWOW_PWOT_PUD: PUD sized page is fuwwy mapped by same pewmissions
 * HMM_DMIWWOW_PWOT_ZEWO: speciaw wead-onwy zewo page
 * HMM_DMIWWOW_PWOT_DEV_PWIVATE_WOCAW: Migwated device pwivate page on the
 *					device the ioctw() is made
 * HMM_DMIWWOW_PWOT_DEV_PWIVATE_WEMOTE: Migwated device pwivate page on some
 *					othew device
 * HMM_DMIWWOW_PWOT_DEV_COHEWENT: Migwate device cohewent page on the device
 *				  the ioctw() is made
 */
enum {
	HMM_DMIWWOW_PWOT_EWWOW			= 0xFF,
	HMM_DMIWWOW_PWOT_NONE			= 0x00,
	HMM_DMIWWOW_PWOT_WEAD			= 0x01,
	HMM_DMIWWOW_PWOT_WWITE			= 0x02,
	HMM_DMIWWOW_PWOT_PMD			= 0x04,
	HMM_DMIWWOW_PWOT_PUD			= 0x08,
	HMM_DMIWWOW_PWOT_ZEWO			= 0x10,
	HMM_DMIWWOW_PWOT_DEV_PWIVATE_WOCAW	= 0x20,
	HMM_DMIWWOW_PWOT_DEV_PWIVATE_WEMOTE	= 0x30,
	HMM_DMIWWOW_PWOT_DEV_COHEWENT_WOCAW	= 0x40,
	HMM_DMIWWOW_PWOT_DEV_COHEWENT_WEMOTE	= 0x50,
};

enum {
	/* 0 is wesewved to catch uninitiawized type fiewds */
	HMM_DMIWWOW_MEMOWY_DEVICE_PWIVATE = 1,
	HMM_DMIWWOW_MEMOWY_DEVICE_COHEWENT,
};

#endif /* _WIB_TEST_HMM_UAPI_H */
