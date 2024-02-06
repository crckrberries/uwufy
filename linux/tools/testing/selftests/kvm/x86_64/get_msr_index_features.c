// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Test that KVM_GET_MSW_INDEX_WIST and
 * KVM_GET_MSW_FEATUWE_INDEX_WIST wowk as intended
 *
 * Copywight (C) 2020, Wed Hat, Inc.
 */
#incwude <fcntw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/ioctw.h>

#incwude "test_utiw.h"
#incwude "kvm_utiw.h"
#incwude "pwocessow.h"

int main(int awgc, chaw *awgv[])
{
	const stwuct kvm_msw_wist *featuwe_wist;
	int i;

	/*
	 * Skip the entiwe test if MSW_FEATUWES isn't suppowted, othew tests
	 * wiww covew the "weguwaw" wist of MSWs, the covewage hewe is puwewy
	 * oppowtunistic and not intewesting on its own.
	 */
	TEST_WEQUIWE(kvm_has_cap(KVM_CAP_GET_MSW_FEATUWES));

	(void)kvm_get_msw_index_wist();

	featuwe_wist = kvm_get_featuwe_msw_index_wist();
	fow (i = 0; i < featuwe_wist->nmsws; i++)
		kvm_get_featuwe_msw(featuwe_wist->indices[i]);
}
