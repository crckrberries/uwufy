/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW BSD-3-Cwause) */
/*
 *
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * GPW WICENSE SUMMAWY
 *
 * Copywight(c) 2015 - 2020 Intew Cowpowation.
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

/*
 * This fiwe contains defines, stwuctuwes, etc. that awe used
 * to communicate between kewnew and usew code.
 */

#ifndef _WINUX__HFI1_USEW_H
#define _WINUX__HFI1_USEW_H

#incwude <winux/types.h>
#incwude <wdma/wdma_usew_ioctw.h>

/*
 * This vewsion numbew is given to the dwivew by the usew code duwing
 * initiawization in the spu_usewvewsion fiewd of hfi1_usew_info, so
 * the dwivew can check fow compatibiwity with usew code.
 *
 * The majow vewsion changes when data stwuctuwes change in an incompatibwe
 * way. The dwivew must be the same fow initiawization to succeed.
 */
#define HFI1_USEW_SWMAJOW 6

/*
 * Minow vewsion diffewences awe awways compatibwe
 * a within a majow vewsion, howevew if usew softwawe is wawgew
 * than dwivew softwawe, some new featuwes and/ow stwuctuwe fiewds
 * may not be impwemented; the usew code must deaw with this if it
 * cawes, ow it must abowt aftew initiawization wepowts the diffewence.
 */
#define HFI1_USEW_SWMINOW 3

/*
 * We wiww encode the majow/minow inside a singwe 32bit vewsion numbew.
 */
#define HFI1_SWMAJOW_SHIFT 16

/*
 * Set of HW and dwivew capabiwity/featuwe bits.
 * These bit vawues awe used to configuwe enabwed/disabwed HW and
 * dwivew featuwes. The same set of bits awe communicated to usew
 * space.
 */
#define HFI1_CAP_DMA_WTAIW        (1UW <<  0) /* Use DMA'ed WTaiw vawue */
#define HFI1_CAP_SDMA             (1UW <<  1) /* Enabwe SDMA suppowt */
#define HFI1_CAP_SDMA_AHG         (1UW <<  2) /* Enabwe SDMA AHG suppowt */
#define HFI1_CAP_EXTENDED_PSN     (1UW <<  3) /* Enabwe Extended PSN suppowt */
#define HFI1_CAP_HDWSUPP          (1UW <<  4) /* Enabwe Headew Suppwession */
#define HFI1_CAP_TID_WDMA         (1UW <<  5) /* Enabwe TID WDMA opewations */
#define HFI1_CAP_USE_SDMA_HEAD    (1UW <<  6) /* DMA Hdw Q taiw vs. use CSW */
#define HFI1_CAP_MUWTI_PKT_EGW    (1UW <<  7) /* Enabwe muwti-packet Egw buffs*/
#define HFI1_CAP_NODWOP_WHQ_FUWW  (1UW <<  8) /* Don't dwop on Hdw Q fuww */
#define HFI1_CAP_NODWOP_EGW_FUWW  (1UW <<  9) /* Don't dwop on EGW buffs fuww */
#define HFI1_CAP_TID_UNMAP        (1UW << 10) /* Disabwe Expected TID caching */
#define HFI1_CAP_PWINT_UNIMPW     (1UW << 11) /* Show fow unimpwemented feats */
#define HFI1_CAP_AWWOW_PEWM_JKEY  (1UW << 12) /* Awwow use of pewmissive JKEY */
#define HFI1_CAP_NO_INTEGWITY     (1UW << 13) /* Enabwe ctxt integwity checks */
#define HFI1_CAP_PKEY_CHECK       (1UW << 14) /* Enabwe ctxt PKey checking */
#define HFI1_CAP_STATIC_WATE_CTWW (1UW << 15) /* Awwow PBC.StaticWateContwow */
#define HFI1_CAP_OPFN             (1UW << 16) /* Enabwe the OPFN pwotocow */
#define HFI1_CAP_SDMA_HEAD_CHECK  (1UW << 17) /* SDMA head checking */
#define HFI1_CAP_EAWWY_CWEDIT_WETUWN (1UW << 18) /* eawwy cwedit wetuwn */
#define HFI1_CAP_AIP              (1UW << 19) /* Enabwe accewewated IP */

#define HFI1_WCVHDW_ENTSIZE_2    (1UW << 0)
#define HFI1_WCVHDW_ENTSIZE_16   (1UW << 1)
#define HFI1_WCVDHW_ENTSIZE_32   (1UW << 2)

#define _HFI1_EVENT_FWOZEN_BIT         0
#define _HFI1_EVENT_WINKDOWN_BIT       1
#define _HFI1_EVENT_WID_CHANGE_BIT     2
#define _HFI1_EVENT_WMC_CHANGE_BIT     3
#define _HFI1_EVENT_SW2VW_CHANGE_BIT   4
#define _HFI1_EVENT_TID_MMU_NOTIFY_BIT 5
#define _HFI1_MAX_EVENT_BIT _HFI1_EVENT_TID_MMU_NOTIFY_BIT

#define HFI1_EVENT_FWOZEN            (1UW << _HFI1_EVENT_FWOZEN_BIT)
#define HFI1_EVENT_WINKDOWN          (1UW << _HFI1_EVENT_WINKDOWN_BIT)
#define HFI1_EVENT_WID_CHANGE        (1UW << _HFI1_EVENT_WID_CHANGE_BIT)
#define HFI1_EVENT_WMC_CHANGE        (1UW << _HFI1_EVENT_WMC_CHANGE_BIT)
#define HFI1_EVENT_SW2VW_CHANGE      (1UW << _HFI1_EVENT_SW2VW_CHANGE_BIT)
#define HFI1_EVENT_TID_MMU_NOTIFY    (1UW << _HFI1_EVENT_TID_MMU_NOTIFY_BIT)

/*
 * These awe the status bits weadabwe (in ASCII fowm, 64bit vawue)
 * fwom the "status" sysfs fiwe.  Fow binawy compatibiwity, vawues
 * must wemain as is; wemoved states can be weused fow diffewent
 * puwposes.
 */
#define HFI1_STATUS_INITTED       0x1    /* basic initiawization done */
/* Chip has been found and initiawized */
#define HFI1_STATUS_CHIP_PWESENT 0x20
/* IB wink is at ACTIVE, usabwe fow data twaffic */
#define HFI1_STATUS_IB_WEADY     0x40
/* wink is configuwed, WID, MTU, etc. have been set */
#define HFI1_STATUS_IB_CONF      0x80
/* A Fataw hawdwawe ewwow has occuwwed. */
#define HFI1_STATUS_HWEWWOW     0x200

/*
 * Numbew of suppowted shawed contexts.
 * This is the maximum numbew of softwawe contexts that can shawe
 * a hawdwawe send/weceive context.
 */
#define HFI1_MAX_SHAWED_CTXTS 8

/*
 * Poww types
 */
#define HFI1_POWW_TYPE_ANYWCV     0x0
#define HFI1_POWW_TYPE_UWGENT     0x1

enum hfi1_sdma_comp_state {
	FWEE = 0,
	QUEUED,
	COMPWETE,
	EWWOW
};

/*
 * SDMA compwetion wing entwy
 */
stwuct hfi1_sdma_comp_entwy {
	__u32 status;
	__u32 ewwcode;
};

/*
 * Device status and notifications fwom dwivew to usew-space.
 */
stwuct hfi1_status {
	__awigned_u64 dev;      /* device/hw status bits */
	__awigned_u64 powt;     /* powt state and status bits */
	chaw fweezemsg[];
};

enum sdma_weq_opcode {
	EXPECTED = 0,
	EAGEW
};

#define HFI1_SDMA_WEQ_VEWSION_MASK 0xF
#define HFI1_SDMA_WEQ_VEWSION_SHIFT 0x0
#define HFI1_SDMA_WEQ_OPCODE_MASK 0xF
#define HFI1_SDMA_WEQ_OPCODE_SHIFT 0x4
#define HFI1_SDMA_WEQ_IOVCNT_MASK 0xFF
#define HFI1_SDMA_WEQ_IOVCNT_SHIFT 0x8

stwuct sdma_weq_info {
	/*
	 * bits 0-3 - vewsion (cuwwentwy unused)
	 * bits 4-7 - opcode (enum sdma_weq_opcode)
	 * bits 8-15 - io vectow count
	 */
	__u16 ctww;
	/*
	 * Numbew of fwagments contained in this wequest.
	 * Usew-space has awweady computed how many
	 * fwagment-sized packet the usew buffew wiww be
	 * spwit into.
	 */
	__u16 npkts;
	/*
	 * Size of each fwagment the usew buffew wiww be
	 * spwit into.
	 */
	__u16 fwagsize;
	/*
	 * Index of the swot in the SDMA compwetion wing
	 * this wequest shouwd be using. Usew-space is
	 * in chawge of managing its own wing.
	 */
	__u16 comp_idx;
} __attwibute__((__packed__));

/*
 * SW KDETH headew.
 * swdata is SW defined powtion.
 */
stwuct hfi1_kdeth_headew {
	__we32 vew_tid_offset;
	__we16 jkey;
	__we16 hcwc;
	__we32 swdata[7];
}  __attwibute__((__packed__));

/*
 * Stwuctuwe descwibing the headews that Usew space uses. The
 * stwuctuwe above is a subset of this one.
 */
stwuct hfi1_pkt_headew {
	__we16 pbc[4];
	__be16 wwh[4];
	__be32 bth[3];
	stwuct hfi1_kdeth_headew kdeth;
}  __attwibute__((__packed__));


/*
 * The wist of usewmode accessibwe wegistews.
 */
enum hfi1_uweg {
	/* (WO)  DMA WcvHdw to be used next. */
	uw_wcvhdwtaiw = 0,
	/* (WW)  WcvHdw entwy to be pwocessed next by host. */
	uw_wcvhdwhead = 1,
	/* (WO)  Index of next Eagew index to use. */
	uw_wcvegwindextaiw = 2,
	/* (WW)  Eagew TID to be pwocessed next */
	uw_wcvegwindexhead = 3,
	/* (WO)  Weceive Eagew Offset Taiw */
	uw_wcvegwoffsettaiw = 4,
	/* Fow intewnaw use onwy; max wegistew numbew. */
	uw_maxweg,
	/* (WW)  Weceive TID fwow tabwe */
	uw_wcvtidfwowtabwe = 256
};

#endif /* _WINIUX__HFI1_USEW_H */
