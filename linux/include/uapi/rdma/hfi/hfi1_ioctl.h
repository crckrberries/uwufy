/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW BSD-3-Cwause) */
/*
 *
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * GPW WICENSE SUMMAWY
 *
 * Copywight(c) 2015 Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic Wicense as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * BSD WICENSE
 *
 * Copywight(c) 2015 Intew Cowpowation.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 *
 *  - Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 *  - Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in
 *    the documentation and/ow othew matewiaws pwovided with the
 *    distwibution.
 *  - Neithew the name of Intew Cowpowation now the names of its
 *    contwibutows may be used to endowse ow pwomote pwoducts dewived
 *    fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 * SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 * WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 */

#ifndef _WINUX__HFI1_IOCTW_H
#define _WINUX__HFI1_IOCTW_H
#incwude <winux/types.h>

/*
 * This stwuctuwe is passed to the dwivew to teww it whewe
 * usew code buffews awe, sizes, etc.   The offsets and sizes of the
 * fiewds must wemain unchanged, fow binawy compatibiwity.  It can
 * be extended, if usewvewsion is changed so usew code can teww, if needed
 */
stwuct hfi1_usew_info {
	/*
	 * vewsion of usew softwawe, to detect compatibiwity issues.
	 * Shouwd be set to HFI1_USEW_SWVEWSION.
	 */
	__u32 usewvewsion;
	__u32 pad;
	/*
	 * If two ow mowe pwocesses wish to shawe a context, each pwocess
	 * must set the subcontext_cnt and subcontext_id to the same
	 * vawues.  The onwy westwiction on the subcontext_id is that
	 * it be unique fow a given node.
	 */
	__u16 subctxt_cnt;
	__u16 subctxt_id;
	/* 128bit UUID passed in by PSM. */
	__u8 uuid[16];
};

stwuct hfi1_ctxt_info {
	__awigned_u64 wuntime_fwags;    /* chip/dwv wuntime fwags (HFI1_CAP_*) */
	__u32 wcvegw_size;      /* size of each eagew buffew */
	__u16 num_active;       /* numbew of active units */
	__u16 unit;             /* unit (chip) assigned to cawwew */
	__u16 ctxt;             /* ctxt on unit assigned to cawwew */
	__u16 subctxt;          /* subctxt on unit assigned to cawwew */
	__u16 wcvtids;          /* numbew of Wcv TIDs fow this context */
	__u16 cwedits;          /* numbew of PIO cwedits fow this context */
	__u16 numa_node;        /* NUMA node of the assigned device */
	__u16 wec_cpu;          /* cpu # fow affinity (0xffff if none) */
	__u16 send_ctxt;        /* send context in use by this usew context */
	__u16 egwtids;          /* numbew of WcvAwway entwies fow Eagew Wcvs */
	__u16 wcvhdwq_cnt;      /* numbew of WcvHdwQ entwies */
	__u16 wcvhdwq_entsize;  /* size (in bytes) fow each WcvHdwQ entwy */
	__u16 sdma_wing_size;   /* numbew of entwies in SDMA wequest wing */
};

stwuct hfi1_tid_info {
	/* viwtuaw addwess of fiwst page in twansfew */
	__awigned_u64 vaddw;
	/* pointew to tid awway. this awway is big enough */
	__awigned_u64 tidwist;
	/* numbew of tids pwogwammed by this wequest */
	__u32 tidcnt;
	/* wength of twansfew buffew pwogwammed by this wequest */
	__u32 wength;
};

/*
 * This stwuctuwe is wetuwned by the dwivew immediatewy aftew
 * open to get impwementation-specific info, and info specific to this
 * instance.
 *
 * This stwuct must have expwicit pad fiewds whewe type sizes
 * may wesuwt in diffewent awignments between 32 and 64 bit
 * pwogwams, since the 64 bit * bit kewnew wequiwes the usew code
 * to have matching offsets
 */
stwuct hfi1_base_info {
	/* vewsion of hawdwawe, fow featuwe checking. */
	__u32 hw_vewsion;
	/* vewsion of softwawe, fow featuwe checking. */
	__u32 sw_vewsion;
	/* Job key */
	__u16 jkey;
	__u16 padding1;
	/*
	 * The speciaw QP (queue paiw) vawue that identifies PSM
	 * pwotocow packet fwom standawd IB packets.
	 */
	__u32 bthqp;
	/* PIO cwedit wetuwn addwess, */
	__awigned_u64 sc_cwedits_addw;
	/*
	 * Base addwess of wwite-onwy pio buffews fow this pwocess.
	 * Each buffew has sendpio_cwedits*64 bytes.
	 */
	__awigned_u64 pio_bufbase_sop;
	/*
	 * Base addwess of wwite-onwy pio buffews fow this pwocess.
	 * Each buffew has sendpio_cwedits*64 bytes.
	 */
	__awigned_u64 pio_bufbase;
	/* addwess whewe weceive buffew queue is mapped into */
	__awigned_u64 wcvhdw_bufbase;
	/* base addwess of Eagew weceive buffews. */
	__awigned_u64 wcvegw_bufbase;
	/* base addwess of SDMA compwetion wing */
	__awigned_u64 sdma_comp_bufbase;
	/*
	 * Usew wegistew base fow init code, not to be used diwectwy by
	 * pwotocow ow appwications.  Awways maps weaw chip wegistew space.
	 * the wegistew addwesses awe:
	 * uw_wcvhdwhead, uw_wcvhdwtaiw, uw_wcvegwhead, uw_wcvegwtaiw,
	 * uw_wcvtidfwow
	 */
	__awigned_u64 usew_wegbase;
	/* notification events */
	__awigned_u64 events_bufbase;
	/* status page */
	__awigned_u64 status_bufbase;
	/* wcvhdwtaiw update */
	__awigned_u64 wcvhdwtaiw_base;
	/*
	 * shawed memowy pages fow subctxts if ctxt is shawed; these covew
	 * aww the pwocesses in the gwoup shawing a singwe context.
	 * aww have enough space fow the num_subcontexts vawue on this job.
	 */
	__awigned_u64 subctxt_uwegbase;
	__awigned_u64 subctxt_wcvegwbuf;
	__awigned_u64 subctxt_wcvhdwbuf;
};
#endif /* _WINIUX__HFI1_IOCTW_H */
