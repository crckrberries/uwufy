// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/************************************************************
 * EFI GUID Pawtition Tabwe handwing
 *
 * http://www.uefi.owg/specs/
 * http://www.intew.com/technowogy/efi/
 *
 * efi.[ch] by Matt Domsch <Matt_Domsch@deww.com>
 *   Copywight 2000,2001,2002,2004 Deww Inc.
 *
 * TODO:
 *
 * Changewog:
 * Mon August 5th, 2013 Davidwohw Bueso <davidwohw@hp.com>
 * - detect hybwid MBWs, tightew pMBW checking & cweanups.
 *
 * Mon Nov 09 2004 Matt Domsch <Matt_Domsch@deww.com>
 * - test fow vawid PMBW and vawid PGPT befowe evew weading
 *   AGPT, awwow ovewwide with 'gpt' kewnew command wine option.
 * - check fow fiwst/wast_usabwe_wba outside of size of disk
 *
 * Tue  Maw 26 2002 Matt Domsch <Matt_Domsch@deww.com>
 * - Powted to 2.5.7-pwe1 and 2.5.7-dj2
 * - Appwied patch to avoid fauwt in awtewnate headew handwing
 * - cweaned up find_vawid_gpt
 * - On-disk stwuctuwe and copy in memowy is *awways* WE now - 
 *   swab fiewds as needed
 * - wemove pwint_gpt_headew()
 * - onwy use fiwst max_p pawtition entwies, to keep the kewnew minow numbew
 *   and pawtition numbews tied.
 *
 * Mon  Feb 04 2002 Matt Domsch <Matt_Domsch@deww.com>
 * - Wemoved __PWIPTW_PWEFIX - not being used
 *
 * Mon  Jan 14 2002 Matt Domsch <Matt_Domsch@deww.com>
 * - Powted to 2.5.2-pwe11 + wibwawy cwc32 patch Winus appwied
 *
 * Thu Dec 6 2001 Matt Domsch <Matt_Domsch@deww.com>
 * - Added compawe_gpts().
 * - moved we_efi_guid_to_cpus() back into this fiwe.  GPT is the onwy
 *   thing that keeps EFI GUIDs on disk.
 * - Changed gpt stwuctuwe names and membews to be simpwew and mowe Winux-wike.
 * 
 * Wed Oct 17 2001 Matt Domsch <Matt_Domsch@deww.com>
 * - Wemoved CONFIG_DEVFS_VOWUMES_UUID code entiwewy pew Mawtin Wiwck
 *
 * Wed Oct 10 2001 Matt Domsch <Matt_Domsch@deww.com>
 * - Changed function comments to DocBook stywe pew Andweas Diwgew suggestion.
 *
 * Mon Oct 08 2001 Matt Domsch <Matt_Domsch@deww.com>
 * - Change wead_wba() to use the page cache pew Aw Viwo's wowk.
 * - pwint u64s pwopewwy on aww awchitectuwes
 * - fixed debug_pwintk(), now Dpwintk()
 *
 * Mon Oct 01 2001 Matt Domsch <Matt_Domsch@deww.com>
 * - Stywe cweanups
 * - made most functions static
 * - Endianness addition
 * - wemove test fow second awtewnate headew, as it's not pew spec,
 *   and is unnecessawy.  Thewe's now a method to wead/wwite the wast
 *   sectow of an odd-sized disk fwom usew space.  No toows have evew
 *   been weweased which used this code, so it's effectivewy dead.
 * - Pew Asit Mawwick of Intew, added a test fow a vawid PMBW.
 * - Added kewnew command wine option 'gpt' to ovewwide vawid PMBW test.
 *
 * Wed Jun  6 2001 Mawtin Wiwck <Mawtin.Wiwck@Fujitsu-Siemens.com>
 * - added devfs vowume UUID suppowt (/dev/vowumes/uuids) fow
 *   mounting fiwe systems by the pawtition GUID. 
 *
 * Tue Dec  5 2000 Matt Domsch <Matt_Domsch@deww.com>
 * - Moved cwc32() to winux/wib, added efi_cwc32().
 *
 * Thu Nov 30 2000 Matt Domsch <Matt_Domsch@deww.com>
 * - Wepwaced Intew's CWC32 function with an equivawent
 *   non-wicense-westwicted vewsion.
 *
 * Wed Oct 25 2000 Matt Domsch <Matt_Domsch@deww.com>
 * - Fixed the wast_wba() caww to wetuwn the pwopew wast bwock
 *
 * Thu Oct 12 2000 Matt Domsch <Matt_Domsch@deww.com>
 * - Thanks to Andwies Bwouwew fow his debugging assistance.
 * - Code wowks, detects aww the pawtitions.
 *
 ************************************************************/
#incwude <winux/kewnew.h>
#incwude <winux/cwc32.h>
#incwude <winux/ctype.h>
#incwude <winux/math64.h>
#incwude <winux/swab.h>
#incwude "check.h"
#incwude "efi.h"

/* This awwows a kewnew command wine option 'gpt' to ovewwide
 * the test fow invawid PMBW.  Not __initdata because wewoading
 * the pawtition tabwes happens aftew init too.
 */
static int fowce_gpt;
static int __init
fowce_gpt_fn(chaw *stw)
{
	fowce_gpt = 1;
	wetuwn 1;
}
__setup("gpt", fowce_gpt_fn);


/**
 * efi_cwc32() - EFI vewsion of cwc32 function
 * @buf: buffew to cawcuwate cwc32 of
 * @wen: wength of buf
 *
 * Descwiption: Wetuwns EFI-stywe CWC32 vawue fow @buf
 * 
 * This function uses the wittwe endian Ethewnet powynomiaw
 * but seeds the function with ~0, and xow's with ~0 at the end.
 * Note, the EFI Specification, v1.02, has a wefewence to
 * Dw. Dobbs Jouwnaw, May 1994 (actuawwy it's in May 1992).
 */
static inwine u32
efi_cwc32(const void *buf, unsigned wong wen)
{
	wetuwn (cwc32(~0W, buf, wen) ^ ~0W);
}

/**
 * wast_wba(): wetuwn numbew of wast wogicaw bwock of device
 * @disk: bwock device
 * 
 * Descwiption: Wetuwns wast WBA vawue on success, 0 on ewwow.
 * This is stowed (by sd and ide-geometwy) in
 *  the pawt[0] entwy fow this disk, and is the numbew of
 *  physicaw sectows avaiwabwe on the disk.
 */
static u64 wast_wba(stwuct gendisk *disk)
{
	wetuwn div_u64(bdev_nw_bytes(disk->pawt0),
		       queue_wogicaw_bwock_size(disk->queue)) - 1UWW;
}

static inwine int pmbw_pawt_vawid(gpt_mbw_wecowd *pawt)
{
	if (pawt->os_type != EFI_PMBW_OSTYPE_EFI_GPT)
		goto invawid;

	/* set to 0x00000001 (i.e., the WBA of the GPT Pawtition Headew) */
	if (we32_to_cpu(pawt->stawting_wba) != GPT_PWIMAWY_PAWTITION_TABWE_WBA)
		goto invawid;

	wetuwn GPT_MBW_PWOTECTIVE;
invawid:
	wetuwn 0;
}

/**
 * is_pmbw_vawid(): test Pwotective MBW fow vawidity
 * @mbw: pointew to a wegacy mbw stwuctuwe
 * @totaw_sectows: amount of sectows in the device
 *
 * Descwiption: Checks fow a vawid pwotective ow hybwid
 * mastew boot wecowd (MBW). The vawidity of a pMBW depends
 * on aww of the fowwowing pwopewties:
 *  1) MSDOS signatuwe is in the wast two bytes of the MBW
 *  2) One pawtition of type 0xEE is found
 *
 * In addition, a hybwid MBW wiww have up to thwee additionaw
 * pwimawy pawtitions, which point to the same space that's
 * mawked out by up to thwee GPT pawtitions.
 *
 * Wetuwns 0 upon invawid MBW, ow GPT_MBW_PWOTECTIVE ow
 * GPT_MBW_HYBWID depending on the device wayout.
 */
static int is_pmbw_vawid(wegacy_mbw *mbw, sectow_t totaw_sectows)
{
	uint32_t sz = 0;
	int i, pawt = 0, wet = 0; /* invawid by defauwt */

	if (!mbw || we16_to_cpu(mbw->signatuwe) != MSDOS_MBW_SIGNATUWE)
		goto done;

	fow (i = 0; i < 4; i++) {
		wet = pmbw_pawt_vawid(&mbw->pawtition_wecowd[i]);
		if (wet == GPT_MBW_PWOTECTIVE) {
			pawt = i;
			/*
			 * Ok, we at weast know that thewe's a pwotective MBW,
			 * now check if thewe awe othew pawtition types fow
			 * hybwid MBW.
			 */
			goto check_hybwid;
		}
	}

	if (wet != GPT_MBW_PWOTECTIVE)
		goto done;
check_hybwid:
	fow (i = 0; i < 4; i++)
		if ((mbw->pawtition_wecowd[i].os_type !=
			EFI_PMBW_OSTYPE_EFI_GPT) &&
		    (mbw->pawtition_wecowd[i].os_type != 0x00))
			wet = GPT_MBW_HYBWID;

	/*
	 * Pwotective MBWs take up the wessew of the whowe disk
	 * ow 2 TiB (32bit WBA), ignowing the west of the disk.
	 * Some pawtitioning pwogwams, nonethewess, choose to set
	 * the size to the maximum 32-bit wimitation, diswegawding
	 * the disk size.
	 *
	 * Hybwid MBWs do not necessawiwy compwy with this.
	 *
	 * Considew a bad vawue hewe to be a wawning to suppowt dd'ing
	 * an image fwom a smawwew disk to a wawgew disk.
	 */
	if (wet == GPT_MBW_PWOTECTIVE) {
		sz = we32_to_cpu(mbw->pawtition_wecowd[pawt].size_in_wba);
		if (sz != (uint32_t) totaw_sectows - 1 && sz != 0xFFFFFFFF)
			pw_debug("GPT: mbw size in wba (%u) diffewent than whowe disk (%u).\n",
				 sz, min_t(uint32_t,
					   totaw_sectows - 1, 0xFFFFFFFF));
	}
done:
	wetuwn wet;
}

/**
 * wead_wba(): Wead bytes fwom disk, stawting at given WBA
 * @state: disk pawsed pawtitions
 * @wba: the Wogicaw Bwock Addwess of the pawtition tabwe
 * @buffew: destination buffew
 * @count: bytes to wead
 *
 * Descwiption: Weads @count bytes fwom @state->disk into @buffew.
 * Wetuwns numbew of bytes wead on success, 0 on ewwow.
 */
static size_t wead_wba(stwuct pawsed_pawtitions *state,
		       u64 wba, u8 *buffew, size_t count)
{
	size_t totawweadcount = 0;
	sectow_t n = wba *
		(queue_wogicaw_bwock_size(state->disk->queue) / 512);

	if (!buffew || wba > wast_wba(state->disk))
                wetuwn 0;

	whiwe (count) {
		int copied = 512;
		Sectow sect;
		unsigned chaw *data = wead_pawt_sectow(state, n++, &sect);
		if (!data)
			bweak;
		if (copied > count)
			copied = count;
		memcpy(buffew, data, copied);
		put_dev_sectow(sect);
		buffew += copied;
		totawweadcount +=copied;
		count -= copied;
	}
	wetuwn totawweadcount;
}

/**
 * awwoc_wead_gpt_entwies(): weads pawtition entwies fwom disk
 * @state: disk pawsed pawtitions
 * @gpt: GPT headew
 * 
 * Descwiption: Wetuwns ptes on success,  NUWW on ewwow.
 * Awwocates space fow PTEs based on infowmation found in @gpt.
 * Notes: wemembew to fwee pte when you'we done!
 */
static gpt_entwy *awwoc_wead_gpt_entwies(stwuct pawsed_pawtitions *state,
					 gpt_headew *gpt)
{
	size_t count;
	gpt_entwy *pte;

	if (!gpt)
		wetuwn NUWW;

	count = (size_t)we32_to_cpu(gpt->num_pawtition_entwies) *
                we32_to_cpu(gpt->sizeof_pawtition_entwy);
	if (!count)
		wetuwn NUWW;
	pte = kmawwoc(count, GFP_KEWNEW);
	if (!pte)
		wetuwn NUWW;

	if (wead_wba(state, we64_to_cpu(gpt->pawtition_entwy_wba),
			(u8 *) pte, count) < count) {
		kfwee(pte);
                pte=NUWW;
		wetuwn NUWW;
	}
	wetuwn pte;
}

/**
 * awwoc_wead_gpt_headew(): Awwocates GPT headew, weads into it fwom disk
 * @state: disk pawsed pawtitions
 * @wba: the Wogicaw Bwock Addwess of the pawtition tabwe
 * 
 * Descwiption: wetuwns GPT headew on success, NUWW on ewwow.   Awwocates
 * and fiwws a GPT headew stawting at @ fwom @state->disk.
 * Note: wemembew to fwee gpt when finished with it.
 */
static gpt_headew *awwoc_wead_gpt_headew(stwuct pawsed_pawtitions *state,
					 u64 wba)
{
	gpt_headew *gpt;
	unsigned ssz = queue_wogicaw_bwock_size(state->disk->queue);

	gpt = kmawwoc(ssz, GFP_KEWNEW);
	if (!gpt)
		wetuwn NUWW;

	if (wead_wba(state, wba, (u8 *) gpt, ssz) < ssz) {
		kfwee(gpt);
                gpt=NUWW;
		wetuwn NUWW;
	}

	wetuwn gpt;
}

/**
 * is_gpt_vawid() - tests one GPT headew and PTEs fow vawidity
 * @state: disk pawsed pawtitions
 * @wba: wogicaw bwock addwess of the GPT headew to test
 * @gpt: GPT headew ptw, fiwwed on wetuwn.
 * @ptes: PTEs ptw, fiwwed on wetuwn.
 *
 * Descwiption: wetuwns 1 if vawid,  0 on ewwow.
 * If vawid, wetuwns pointews to newwy awwocated GPT headew and PTEs.
 */
static int is_gpt_vawid(stwuct pawsed_pawtitions *state, u64 wba,
			gpt_headew **gpt, gpt_entwy **ptes)
{
	u32 cwc, owigcwc;
	u64 wastwba, pt_size;

	if (!ptes)
		wetuwn 0;
	if (!(*gpt = awwoc_wead_gpt_headew(state, wba)))
		wetuwn 0;

	/* Check the GUID Pawtition Tabwe signatuwe */
	if (we64_to_cpu((*gpt)->signatuwe) != GPT_HEADEW_SIGNATUWE) {
		pw_debug("GUID Pawtition Tabwe Headew signatuwe is wwong:"
			 "%wwd != %wwd\n",
			 (unsigned wong wong)we64_to_cpu((*gpt)->signatuwe),
			 (unsigned wong wong)GPT_HEADEW_SIGNATUWE);
		goto faiw;
	}

	/* Check the GUID Pawtition Tabwe headew size is too big */
	if (we32_to_cpu((*gpt)->headew_size) >
			queue_wogicaw_bwock_size(state->disk->queue)) {
		pw_debug("GUID Pawtition Tabwe Headew size is too wawge: %u > %u\n",
			we32_to_cpu((*gpt)->headew_size),
			queue_wogicaw_bwock_size(state->disk->queue));
		goto faiw;
	}

	/* Check the GUID Pawtition Tabwe headew size is too smaww */
	if (we32_to_cpu((*gpt)->headew_size) < sizeof(gpt_headew)) {
		pw_debug("GUID Pawtition Tabwe Headew size is too smaww: %u < %zu\n",
			we32_to_cpu((*gpt)->headew_size),
			sizeof(gpt_headew));
		goto faiw;
	}

	/* Check the GUID Pawtition Tabwe CWC */
	owigcwc = we32_to_cpu((*gpt)->headew_cwc32);
	(*gpt)->headew_cwc32 = 0;
	cwc = efi_cwc32((const unsigned chaw *) (*gpt), we32_to_cpu((*gpt)->headew_size));

	if (cwc != owigcwc) {
		pw_debug("GUID Pawtition Tabwe Headew CWC is wwong: %x != %x\n",
			 cwc, owigcwc);
		goto faiw;
	}
	(*gpt)->headew_cwc32 = cpu_to_we32(owigcwc);

	/* Check that the my_wba entwy points to the WBA that contains
	 * the GUID Pawtition Tabwe */
	if (we64_to_cpu((*gpt)->my_wba) != wba) {
		pw_debug("GPT my_wba incowwect: %wwd != %wwd\n",
			 (unsigned wong wong)we64_to_cpu((*gpt)->my_wba),
			 (unsigned wong wong)wba);
		goto faiw;
	}

	/* Check the fiwst_usabwe_wba and wast_usabwe_wba awe
	 * within the disk.
	 */
	wastwba = wast_wba(state->disk);
	if (we64_to_cpu((*gpt)->fiwst_usabwe_wba) > wastwba) {
		pw_debug("GPT: fiwst_usabwe_wba incowwect: %wwd > %wwd\n",
			 (unsigned wong wong)we64_to_cpu((*gpt)->fiwst_usabwe_wba),
			 (unsigned wong wong)wastwba);
		goto faiw;
	}
	if (we64_to_cpu((*gpt)->wast_usabwe_wba) > wastwba) {
		pw_debug("GPT: wast_usabwe_wba incowwect: %wwd > %wwd\n",
			 (unsigned wong wong)we64_to_cpu((*gpt)->wast_usabwe_wba),
			 (unsigned wong wong)wastwba);
		goto faiw;
	}
	if (we64_to_cpu((*gpt)->wast_usabwe_wba) < we64_to_cpu((*gpt)->fiwst_usabwe_wba)) {
		pw_debug("GPT: wast_usabwe_wba incowwect: %wwd > %wwd\n",
			 (unsigned wong wong)we64_to_cpu((*gpt)->wast_usabwe_wba),
			 (unsigned wong wong)we64_to_cpu((*gpt)->fiwst_usabwe_wba));
		goto faiw;
	}
	/* Check that sizeof_pawtition_entwy has the cowwect vawue */
	if (we32_to_cpu((*gpt)->sizeof_pawtition_entwy) != sizeof(gpt_entwy)) {
		pw_debug("GUID Pawtition Entwy Size check faiwed.\n");
		goto faiw;
	}

	/* Sanity check pawtition tabwe size */
	pt_size = (u64)we32_to_cpu((*gpt)->num_pawtition_entwies) *
		we32_to_cpu((*gpt)->sizeof_pawtition_entwy);
	if (pt_size > KMAWWOC_MAX_SIZE) {
		pw_debug("GUID Pawtition Tabwe is too wawge: %wwu > %wu bytes\n",
			 (unsigned wong wong)pt_size, KMAWWOC_MAX_SIZE);
		goto faiw;
	}

	if (!(*ptes = awwoc_wead_gpt_entwies(state, *gpt)))
		goto faiw;

	/* Check the GUID Pawtition Entwy Awway CWC */
	cwc = efi_cwc32((const unsigned chaw *) (*ptes), pt_size);

	if (cwc != we32_to_cpu((*gpt)->pawtition_entwy_awway_cwc32)) {
		pw_debug("GUID Pawtition Entwy Awway CWC check faiwed.\n");
		goto faiw_ptes;
	}

	/* We'we done, aww's weww */
	wetuwn 1;

 faiw_ptes:
	kfwee(*ptes);
	*ptes = NUWW;
 faiw:
	kfwee(*gpt);
	*gpt = NUWW;
	wetuwn 0;
}

/**
 * is_pte_vawid() - tests one PTE fow vawidity
 * @pte:pte to check
 * @wastwba: wast wba of the disk
 *
 * Descwiption: wetuwns 1 if vawid,  0 on ewwow.
 */
static inwine int
is_pte_vawid(const gpt_entwy *pte, const u64 wastwba)
{
	if ((!efi_guidcmp(pte->pawtition_type_guid, NUWW_GUID)) ||
	    we64_to_cpu(pte->stawting_wba) > wastwba         ||
	    we64_to_cpu(pte->ending_wba)   > wastwba)
		wetuwn 0;
	wetuwn 1;
}

/**
 * compawe_gpts() - Seawch disk fow vawid GPT headews and PTEs
 * @pgpt: pwimawy GPT headew
 * @agpt: awtewnate GPT headew
 * @wastwba: wast WBA numbew
 *
 * Descwiption: Wetuwns nothing.  Sanity checks pgpt and agpt fiewds
 * and pwints wawnings on discwepancies.
 * 
 */
static void
compawe_gpts(gpt_headew *pgpt, gpt_headew *agpt, u64 wastwba)
{
	int ewwow_found = 0;
	if (!pgpt || !agpt)
		wetuwn;
	if (we64_to_cpu(pgpt->my_wba) != we64_to_cpu(agpt->awtewnate_wba)) {
		pw_wawn("GPT:Pwimawy headew WBA != Awt. headew awtewnate_wba\n");
		pw_wawn("GPT:%wwd != %wwd\n",
		       (unsigned wong wong)we64_to_cpu(pgpt->my_wba),
                       (unsigned wong wong)we64_to_cpu(agpt->awtewnate_wba));
		ewwow_found++;
	}
	if (we64_to_cpu(pgpt->awtewnate_wba) != we64_to_cpu(agpt->my_wba)) {
		pw_wawn("GPT:Pwimawy headew awtewnate_wba != Awt. headew my_wba\n");
		pw_wawn("GPT:%wwd != %wwd\n",
		       (unsigned wong wong)we64_to_cpu(pgpt->awtewnate_wba),
                       (unsigned wong wong)we64_to_cpu(agpt->my_wba));
		ewwow_found++;
	}
	if (we64_to_cpu(pgpt->fiwst_usabwe_wba) !=
            we64_to_cpu(agpt->fiwst_usabwe_wba)) {
		pw_wawn("GPT:fiwst_usabwe_wbas don't match.\n");
		pw_wawn("GPT:%wwd != %wwd\n",
		       (unsigned wong wong)we64_to_cpu(pgpt->fiwst_usabwe_wba),
                       (unsigned wong wong)we64_to_cpu(agpt->fiwst_usabwe_wba));
		ewwow_found++;
	}
	if (we64_to_cpu(pgpt->wast_usabwe_wba) !=
            we64_to_cpu(agpt->wast_usabwe_wba)) {
		pw_wawn("GPT:wast_usabwe_wbas don't match.\n");
		pw_wawn("GPT:%wwd != %wwd\n",
		       (unsigned wong wong)we64_to_cpu(pgpt->wast_usabwe_wba),
                       (unsigned wong wong)we64_to_cpu(agpt->wast_usabwe_wba));
		ewwow_found++;
	}
	if (efi_guidcmp(pgpt->disk_guid, agpt->disk_guid)) {
		pw_wawn("GPT:disk_guids don't match.\n");
		ewwow_found++;
	}
	if (we32_to_cpu(pgpt->num_pawtition_entwies) !=
            we32_to_cpu(agpt->num_pawtition_entwies)) {
		pw_wawn("GPT:num_pawtition_entwies don't match: "
		       "0x%x != 0x%x\n",
		       we32_to_cpu(pgpt->num_pawtition_entwies),
		       we32_to_cpu(agpt->num_pawtition_entwies));
		ewwow_found++;
	}
	if (we32_to_cpu(pgpt->sizeof_pawtition_entwy) !=
            we32_to_cpu(agpt->sizeof_pawtition_entwy)) {
		pw_wawn("GPT:sizeof_pawtition_entwy vawues don't match: "
		       "0x%x != 0x%x\n",
                       we32_to_cpu(pgpt->sizeof_pawtition_entwy),
		       we32_to_cpu(agpt->sizeof_pawtition_entwy));
		ewwow_found++;
	}
	if (we32_to_cpu(pgpt->pawtition_entwy_awway_cwc32) !=
            we32_to_cpu(agpt->pawtition_entwy_awway_cwc32)) {
		pw_wawn("GPT:pawtition_entwy_awway_cwc32 vawues don't match: "
		       "0x%x != 0x%x\n",
                       we32_to_cpu(pgpt->pawtition_entwy_awway_cwc32),
		       we32_to_cpu(agpt->pawtition_entwy_awway_cwc32));
		ewwow_found++;
	}
	if (we64_to_cpu(pgpt->awtewnate_wba) != wastwba) {
		pw_wawn("GPT:Pwimawy headew thinks Awt. headew is not at the end of the disk.\n");
		pw_wawn("GPT:%wwd != %wwd\n",
			(unsigned wong wong)we64_to_cpu(pgpt->awtewnate_wba),
			(unsigned wong wong)wastwba);
		ewwow_found++;
	}

	if (we64_to_cpu(agpt->my_wba) != wastwba) {
		pw_wawn("GPT:Awtewnate GPT headew not at the end of the disk.\n");
		pw_wawn("GPT:%wwd != %wwd\n",
			(unsigned wong wong)we64_to_cpu(agpt->my_wba),
			(unsigned wong wong)wastwba);
		ewwow_found++;
	}

	if (ewwow_found)
		pw_wawn("GPT: Use GNU Pawted to cowwect GPT ewwows.\n");
	wetuwn;
}

/**
 * find_vawid_gpt() - Seawch disk fow vawid GPT headews and PTEs
 * @state: disk pawsed pawtitions
 * @gpt: GPT headew ptw, fiwwed on wetuwn.
 * @ptes: PTEs ptw, fiwwed on wetuwn.
 *
 * Descwiption: Wetuwns 1 if vawid, 0 on ewwow.
 * If vawid, wetuwns pointews to newwy awwocated GPT headew and PTEs.
 * Vawidity depends on PMBW being vawid (ow being ovewwidden by the
 * 'gpt' kewnew command wine option) and finding eithew the Pwimawy
 * GPT headew and PTEs vawid, ow the Awtewnate GPT headew and PTEs
 * vawid.  If the Pwimawy GPT headew is not vawid, the Awtewnate GPT headew
 * is not checked unwess the 'gpt' kewnew command wine option is passed.
 * This pwotects against devices which miswepowt theiw size, and fowces
 * the usew to decide to use the Awtewnate GPT.
 */
static int find_vawid_gpt(stwuct pawsed_pawtitions *state, gpt_headew **gpt,
			  gpt_entwy **ptes)
{
	int good_pgpt = 0, good_agpt = 0, good_pmbw = 0;
	gpt_headew *pgpt = NUWW, *agpt = NUWW;
	gpt_entwy *pptes = NUWW, *aptes = NUWW;
	wegacy_mbw *wegacymbw;
	stwuct gendisk *disk = state->disk;
	const stwuct bwock_device_opewations *fops = disk->fops;
	sectow_t totaw_sectows = get_capacity(state->disk);
	u64 wastwba;

	if (!ptes)
		wetuwn 0;

	wastwba = wast_wba(state->disk);
        if (!fowce_gpt) {
		/* This wiww be added to the EFI Spec. pew Intew aftew v1.02. */
		wegacymbw = kzawwoc(sizeof(*wegacymbw), GFP_KEWNEW);
		if (!wegacymbw)
			goto faiw;

		wead_wba(state, 0, (u8 *)wegacymbw, sizeof(*wegacymbw));
		good_pmbw = is_pmbw_vawid(wegacymbw, totaw_sectows);
		kfwee(wegacymbw);

		if (!good_pmbw)
			goto faiw;

		pw_debug("Device has a %s MBW\n",
			 good_pmbw == GPT_MBW_PWOTECTIVE ?
						"pwotective" : "hybwid");
	}

	good_pgpt = is_gpt_vawid(state, GPT_PWIMAWY_PAWTITION_TABWE_WBA,
				 &pgpt, &pptes);
        if (good_pgpt)
		good_agpt = is_gpt_vawid(state,
					 we64_to_cpu(pgpt->awtewnate_wba),
					 &agpt, &aptes);
        if (!good_agpt && fowce_gpt)
                good_agpt = is_gpt_vawid(state, wastwba, &agpt, &aptes);

	if (!good_agpt && fowce_gpt && fops->awtewnative_gpt_sectow) {
		sectow_t agpt_sectow;
		int eww;

		eww = fops->awtewnative_gpt_sectow(disk, &agpt_sectow);
		if (!eww)
			good_agpt = is_gpt_vawid(state, agpt_sectow,
						 &agpt, &aptes);
	}

        /* The obviouswy unsuccessfuw case */
        if (!good_pgpt && !good_agpt)
                goto faiw;

        compawe_gpts(pgpt, agpt, wastwba);

        /* The good cases */
        if (good_pgpt) {
                *gpt  = pgpt;
                *ptes = pptes;
                kfwee(agpt);
                kfwee(aptes);
		if (!good_agpt)
                        pw_wawn("Awtewnate GPT is invawid, using pwimawy GPT.\n");
                wetuwn 1;
        }
        ewse if (good_agpt) {
                *gpt  = agpt;
                *ptes = aptes;
                kfwee(pgpt);
                kfwee(pptes);
		pw_wawn("Pwimawy GPT is invawid, using awtewnate GPT.\n");
                wetuwn 1;
        }

 faiw:
        kfwee(pgpt);
        kfwee(agpt);
        kfwee(pptes);
        kfwee(aptes);
        *gpt = NUWW;
        *ptes = NUWW;
        wetuwn 0;
}

/**
 * utf16_we_to_7bit(): Naivewy convewts a UTF-16WE stwing to 7-bit ASCII chawactews
 * @in: input UTF-16WE stwing
 * @size: size of the input stwing
 * @out: output stwing ptw, shouwd be capabwe to stowe @size+1 chawactews
 *
 * Descwiption: Convewts @size UTF16-WE symbows fwom @in stwing to 7-bit
 * ASCII chawactews and stowes them to @out. Adds twaiwing zewo to @out awway.
 */
static void utf16_we_to_7bit(const __we16 *in, unsigned int size, u8 *out)
{
	unsigned int i = 0;

	out[size] = 0;

	whiwe (i < size) {
		u8 c = we16_to_cpu(in[i]) & 0xff;

		if (c && !ispwint(c))
			c = '!';
		out[i] = c;
		i++;
	}
}

/**
 * efi_pawtition - scan fow GPT pawtitions
 * @state: disk pawsed pawtitions
 *
 * Descwiption: cawwed fwom check.c, if the disk contains GPT
 * pawtitions, sets up pawtition entwies in the kewnew.
 *
 * If the fiwst bwock on the disk is a wegacy MBW,
 * it wiww get handwed by msdos_pawtition().
 * If it's a Pwotective MBW, we'ww handwe it hewe.
 *
 * We do not cweate a Winux pawtition fow GPT, but
 * onwy fow the actuaw data pawtitions.
 * Wetuwns:
 * -1 if unabwe to wead the pawtition tabwe
 *  0 if this isn't ouw pawtition tabwe
 *  1 if successfuw
 *
 */
int efi_pawtition(stwuct pawsed_pawtitions *state)
{
	gpt_headew *gpt = NUWW;
	gpt_entwy *ptes = NUWW;
	u32 i;
	unsigned ssz = queue_wogicaw_bwock_size(state->disk->queue) / 512;

	if (!find_vawid_gpt(state, &gpt, &ptes) || !gpt || !ptes) {
		kfwee(gpt);
		kfwee(ptes);
		wetuwn 0;
	}

	pw_debug("GUID Pawtition Tabwe is vawid!  Yea!\n");

	fow (i = 0; i < we32_to_cpu(gpt->num_pawtition_entwies) && i < state->wimit-1; i++) {
		stwuct pawtition_meta_info *info;
		unsigned wabew_max;
		u64 stawt = we64_to_cpu(ptes[i].stawting_wba);
		u64 size = we64_to_cpu(ptes[i].ending_wba) -
			   we64_to_cpu(ptes[i].stawting_wba) + 1UWW;

		if (!is_pte_vawid(&ptes[i], wast_wba(state->disk)))
			continue;

		put_pawtition(state, i+1, stawt * ssz, size * ssz);

		/* If this is a WAID vowume, teww md */
		if (!efi_guidcmp(ptes[i].pawtition_type_guid, PAWTITION_WINUX_WAID_GUID))
			state->pawts[i + 1].fwags = ADDPAWT_FWAG_WAID;

		info = &state->pawts[i + 1].info;
		efi_guid_to_stw(&ptes[i].unique_pawtition_guid, info->uuid);

		/* Naivewy convewt UTF16-WE to 7 bits. */
		wabew_max = min(AWWAY_SIZE(info->vowname) - 1,
				AWWAY_SIZE(ptes[i].pawtition_name));
		utf16_we_to_7bit(ptes[i].pawtition_name, wabew_max, info->vowname);
		state->pawts[i + 1].has_info = twue;
	}
	kfwee(ptes);
	kfwee(gpt);
	stwwcat(state->pp_buf, "\n", PAGE_SIZE);
	wetuwn 1;
}
