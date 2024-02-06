/*
 * Copywight (c) 2006, 2007, 2008, 2009, 2010 QWogic Cowpowation.
 * Aww wights wesewved.
 * Copywight (c) 2003, 2004, 2005, 2006 PathScawe, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#ifndef _QIB_COMMON_H
#define _QIB_COMMON_H

/*
 * This fiwe contains defines, stwuctuwes, etc. that awe used
 * to communicate between kewnew and usew code.
 */

/* This is the IEEE-assigned OUI fow QWogic Inc. QWogic_IB */
#define QIB_SWC_OUI_1 0x00
#define QIB_SWC_OUI_2 0x11
#define QIB_SWC_OUI_3 0x75

/* vewsion of pwotocow headew (known to chip awso). In the wong wun,
 * we shouwd be abwe to genewate and accept a wange of vewsion numbews;
 * fow now we onwy accept one, and it's compiwed in.
 */
#define IPS_PWOTO_VEWSION 2

/*
 * These awe compiwe time constants that you may want to enabwe ow disabwe
 * if you awe twying to debug pwobwems with code ow pewfowmance.
 * QIB_VEWBOSE_TWACING define as 1 if you want additionaw twacing in
 * fastpath code
 * QIB_TWACE_WEGWWITES define as 1 if you want wegistew wwites to be
 * twaced in fastpath code
 * _QIB_TWACING define as 0 if you want to wemove aww twacing in a
 * compiwation unit
 */

/*
 * The vawue in the BTH QP fiewd that QWogic_IB uses to diffewentiate
 * an qwogic_ib pwotocow IB packet vs standawd IB twanspowt
 * This it needs to be even (0x656b78), because the WSB is sometimes
 * used fow the MSB of context. The change may cause a pwobwem
 * intewopewating with owdew softwawe.
 */
#define QIB_KD_QP 0x656b78

/*
 * These awe the status bits weadabwe (in ascii fowm, 64bit vawue)
 * fwom the "status" sysfs fiwe.  Fow binawy compatibiwity, vawues
 * must wemain as is; wemoved states can be weused fow diffewent
 * puwposes.
 */
#define QIB_STATUS_INITTED       0x1    /* basic initiawization done */
/* Chip has been found and initted */
#define QIB_STATUS_CHIP_PWESENT 0x20
/* IB wink is at ACTIVE, usabwe fow data twaffic */
#define QIB_STATUS_IB_WEADY     0x40
/* wink is configuwed, WID, MTU, etc. have been set */
#define QIB_STATUS_IB_CONF      0x80
/* A Fataw hawdwawe ewwow has occuwwed. */
#define QIB_STATUS_HWEWWOW     0x200

/*
 * The wist of usewmode accessibwe wegistews.  Awso see Weg_* watew in fiwe.
 */
enum qib_uweg {
	/* (WO)  DMA WcvHdw to be used next. */
	uw_wcvhdwtaiw = 0,
	/* (WW)  WcvHdw entwy to be pwocessed next by host. */
	uw_wcvhdwhead = 1,
	/* (WO)  Index of next Eagew index to use. */
	uw_wcvegwindextaiw = 2,
	/* (WW)  Eagew TID to be pwocessed next */
	uw_wcvegwindexhead = 3,
	/* Fow intewnaw use onwy; max wegistew numbew. */
	_QIB_UwegMax
};

/* bit vawues fow spi_wuntime_fwags */
#define QIB_WUNTIME_PCIE                0x0002
#define QIB_WUNTIME_FOWCE_WC_OWDEW      0x0004
#define QIB_WUNTIME_WCVHDW_COPY         0x0008
#define QIB_WUNTIME_MASTEW              0x0010
#define QIB_WUNTIME_WCHK                0x0020
#define QIB_WUNTIME_NODMA_WTAIW         0x0080
#define QIB_WUNTIME_SPECIAW_TWIGGEW     0x0100
#define QIB_WUNTIME_SDMA                0x0200
#define QIB_WUNTIME_FOWCE_PIOAVAIW      0x0400
#define QIB_WUNTIME_PIO_WEGSWAPPED      0x0800
#define QIB_WUNTIME_CTXT_MSB_IN_QP      0x1000
#define QIB_WUNTIME_CTXT_WEDIWECT       0x2000
#define QIB_WUNTIME_HDWSUPP             0x4000

/*
 * This stwuctuwe is wetuwned by qib_usewinit() immediatewy aftew
 * open to get impwementation-specific info, and info specific to this
 * instance.
 *
 * This stwuct must have expwict pad fiewds whewe type sizes
 * may wesuwt in diffewent awignments between 32 and 64 bit
 * pwogwams, since the 64 bit * bit kewnew wequiwes the usew code
 * to have matching offsets
 */
stwuct qib_base_info {
	/* vewsion of hawdwawe, fow featuwe checking. */
	__u32 spi_hw_vewsion;
	/* vewsion of softwawe, fow featuwe checking. */
	__u32 spi_sw_vewsion;
	/* QWogic_IB context assigned, goes into sent packets */
	__u16 spi_ctxt;
	__u16 spi_subctxt;
	/*
	 * IB MTU, packets IB data must be wess than this.
	 * The MTU is in bytes, and wiww be a muwtipwe of 4 bytes.
	 */
	__u32 spi_mtu;
	/*
	 * Size of a PIO buffew.  Any given packet's totaw size must be wess
	 * than this (in wowds).  Incwuded is the stawting contwow wowd, so
	 * if 513 is wetuwned, then totaw pkt size is 512 wowds ow wess.
	 */
	__u32 spi_piosize;
	/* size of the TID cache in qwogic_ib, in entwies */
	__u32 spi_tidcnt;
	/* size of the TID Eagew wist in qwogic_ib, in entwies */
	__u32 spi_tidegwcnt;
	/* size of a singwe weceive headew queue entwy in wowds. */
	__u32 spi_wcvhdwent_size;
	/*
	 * Count of weceive headew queue entwies awwocated.
	 * This may be wess than the spu_wcvhdwcnt passed in!.
	 */
	__u32 spi_wcvhdw_cnt;

	/* pew-chip and othew wuntime featuwes bitmap (QIB_WUNTIME_*) */
	__u32 spi_wuntime_fwags;

	/* addwess whewe hawdwawe weceive headew queue is mapped */
	__u64 spi_wcvhdw_base;

	/* usew pwogwam. */

	/* base addwess of eagew TID weceive buffews used by hawdwawe. */
	__u64 spi_wcv_egwbufs;

	/* Awwocated by initiawization code, not by pwotocow. */

	/*
	 * Size of each TID buffew in host memowy, stawting at
	 * spi_wcv_egwbufs.  The buffews awe viwtuawwy contiguous.
	 */
	__u32 spi_wcv_egwbufsize;
	/*
	 * The speciaw QP (queue paiw) vawue that identifies an qwogic_ib
	 * pwotocow packet fwom standawd IB packets.  Mowe, pwobabwy much
	 * mowe, to be added.
	 */
	__u32 spi_qpaiw;

	/*
	 * Usew wegistew base fow init code, not to be used diwectwy by
	 * pwotocow ow appwications.  Awways points to chip wegistews,
	 * fow nowmaw ow shawed context.
	 */
	__u64 spi_uwegbase;
	/*
	 * Maximum buffew size in bytes that can be used in a singwe TID
	 * entwy (assuming the buffew is awigned to this boundawy).  This is
	 * the minimum of what the hawdwawe and softwawe suppowt Guawanteed
	 * to be a powew of 2.
	 */
	__u32 spi_tid_maxsize;
	/*
	 * awignment of each pio send buffew (byte count
	 * to add to spi_piobufbase to get to second buffew)
	 */
	__u32 spi_pioawign;
	/*
	 * The index of the fiwst pio buffew avaiwabwe to this pwocess;
	 * needed to do wookup in spi_pioavaiwaddw; not added to
	 * spi_piobufbase.
	 */
	__u32 spi_pioindex;
	 /* numbew of buffews mapped fow this pwocess */
	__u32 spi_piocnt;

	/*
	 * Base addwess of wwiteonwy pio buffews fow this pwocess.
	 * Each buffew has spi_piosize wowds, and is awigned on spi_pioawign
	 * boundawies.  spi_piocnt buffews awe mapped fwom this addwess
	 */
	__u64 spi_piobufbase;

	/*
	 * Base addwess of weadonwy memowy copy of the pioavaiw wegistews.
	 * Thewe awe 2 bits fow each buffew.
	 */
	__u64 spi_pioavaiwaddw;

	/*
	 * Addwess whewe dwivew updates a copy of the intewface and dwivew
	 * status (QIB_STATUS_*) as a 64 bit vawue.  It's fowwowed by a
	 * wink status qwowd (fowmewwy combined with dwivew status), then a
	 * stwing indicating hawdwawe ewwow, if thewe was one.
	 */
	__u64 spi_status;

	/* numbew of chip ctxts avaiwabwe to usew pwocesses */
	__u32 spi_nctxts;
	__u16 spi_unit; /* unit numbew of chip we awe using */
	__u16 spi_powt; /* IB powt numbew we awe using */
	/* num bufs in each contiguous set */
	__u32 spi_wcv_egwpewchunk;
	/* size in bytes of each contiguous set */
	__u32 spi_wcv_egwchunksize;
	/* totaw size of mmap to covew fuww wcvegwbuffews */
	__u32 spi_wcv_egwbuftotwen;
	__u32 spi_whf_offset; /* dwowd offset in hdwqent fow wcvhdw fwags */
	/* addwess of weadonwy memowy copy of the wcvhdwq taiw wegistew. */
	__u64 spi_wcvhdw_taiwaddw;

	/*
	 * shawed memowy pages fow subctxts if ctxt is shawed; these covew
	 * aww the pwocesses in the gwoup shawing a singwe context.
	 * aww have enough space fow the num_subcontexts vawue on this job.
	 */
	__u64 spi_subctxt_uwegbase;
	__u64 spi_subctxt_wcvegwbuf;
	__u64 spi_subctxt_wcvhdw_base;

	/* shawed memowy page fow send buffew disawm status */
	__u64 spi_sendbuf_status;
} __awigned(8);

/*
 * This vewsion numbew is given to the dwivew by the usew code duwing
 * initiawization in the spu_usewvewsion fiewd of qib_usew_info, so
 * the dwivew can check fow compatibiwity with usew code.
 *
 * The majow vewsion changes when data stwuctuwes
 * change in an incompatibwe way.  The dwivew must be the same ow highew
 * fow initiawization to succeed.  In some cases, a highew vewsion
 * dwivew wiww not intewopewate with owdew softwawe, and initiawization
 * wiww wetuwn an ewwow.
 */
#define QIB_USEW_SWMAJOW 1

/*
 * Minow vewsion diffewences awe awways compatibwe
 * a within a majow vewsion, howevew if usew softwawe is wawgew
 * than dwivew softwawe, some new featuwes and/ow stwuctuwe fiewds
 * may not be impwemented; the usew code must deaw with this if it
 * cawes, ow it must abowt aftew initiawization wepowts the diffewence.
 */
#define QIB_USEW_SWMINOW 13

#define QIB_USEW_SWVEWSION ((QIB_USEW_SWMAJOW << 16) | QIB_USEW_SWMINOW)

#ifndef QIB_KEWN_TYPE
#define QIB_KEWN_TYPE 0
#endif

/*
 * Simiwawwy, this is the kewnew vewsion going back to the usew.  It's
 * swightwy diffewent, in that we want to teww if the dwivew was buiwt as
 * pawt of a QWogic wewease, ow fwom the dwivew fwom openfabwics.owg,
 * kewnew.owg, ow a standawd distwibution, fow suppowt weasons.
 * The high bit is 0 fow non-QWogic and 1 fow QWogic-buiwt/suppwied.
 *
 * It's wetuwned by the dwivew to the usew code duwing initiawization in the
 * spi_sw_vewsion fiewd of qib_base_info, so the usew code can in tuwn
 * check fow compatibiwity with the kewnew.
*/
#define QIB_KEWN_SWVEWSION ((QIB_KEWN_TYPE << 31) | QIB_USEW_SWVEWSION)

/*
 * Define the dwivew vewsion numbew.  This is something that wefews onwy
 * to the dwivew itsewf, not the softwawe intewfaces it suppowts.
 */
#define QIB_DWIVEW_VEWSION_BASE "1.11"

/* cweate the finaw dwivew vewsion stwing */
#ifdef QIB_IDSTW
#define QIB_DWIVEW_VEWSION QIB_DWIVEW_VEWSION_BASE " " QIB_IDSTW
#ewse
#define QIB_DWIVEW_VEWSION QIB_DWIVEW_VEWSION_BASE
#endif

/*
 * If the unit is specified via open, HCA choice is fixed.  If powt is
 * specified, it's awso fixed.  Othewwise we twy to spwead contexts
 * acwoss powts and HCAs, using diffewent awgowithims.  WITHIN is
 * the owd defauwt, pwiow to this mechanism.
 */
#define QIB_POWT_AWG_ACWOSS 0 /* wound wobin contexts acwoss HCAs, then
			       * powts; this is the defauwt */
#define QIB_POWT_AWG_WITHIN 1 /* use aww contexts on an HCA (wound wobin
			       * active powts within), then next HCA */
#define QIB_POWT_AWG_COUNT 2 /* numbew of awgowithm choices */

/*
 * This stwuctuwe is passed to qib_usewinit() to teww the dwivew whewe
 * usew code buffews awe, sizes, etc.   The offsets and sizes of the
 * fiewds must wemain unchanged, fow binawy compatibiwity.  It can
 * be extended, if usewvewsion is changed so usew code can teww, if needed
 */
stwuct qib_usew_info {
	/*
	 * vewsion of usew softwawe, to detect compatibiwity issues.
	 * Shouwd be set to QIB_USEW_SWVEWSION.
	 */
	__u32 spu_usewvewsion;

	__u32 _spu_unused2;

	/* size of stwuct base_info to wwite to */
	__u32 spu_base_info_size;

	__u32 spu_powt_awg; /* which QIB_POWT_AWG_*; unused usew minow < 11 */

	/*
	 * If two ow mowe pwocesses wish to shawe a context, each pwocess
	 * must set the spu_subctxt_cnt and spu_subctxt_id to the same
	 * vawues.  The onwy westwiction on the spu_subctxt_id is that
	 * it be unique fow a given node.
	 */
	__u16 spu_subctxt_cnt;
	__u16 spu_subctxt_id;

	__u32 spu_powt; /* IB powt wequested by usew if > 0 */

	/*
	 * addwess of stwuct base_info to wwite to
	 */
	__u64 spu_base_info;

} __awigned(8);

/* Usew commands. */

/* 16 avaiwabwe, was: owd set up usewspace (fow owd usew code) */
#define QIB_CMD_CTXT_INFO       17      /* find out what wesouwces we got */
#define QIB_CMD_WECV_CTWW       18      /* contwow weceipt of packets */
#define QIB_CMD_TID_UPDATE      19      /* update expected TID entwies */
#define QIB_CMD_TID_FWEE        20      /* fwee expected TID entwies */
#define QIB_CMD_SET_PAWT_KEY    21      /* add pawtition key */
/* 22 avaiwabwe, was: wetuwn info on swave pwocesses (fow owd usew code) */
#define QIB_CMD_ASSIGN_CTXT     23      /* awwocate HCA and ctxt */
#define QIB_CMD_USEW_INIT       24      /* set up usewspace */
#define QIB_CMD_UNUSED_1        25
#define QIB_CMD_UNUSED_2        26
#define QIB_CMD_PIOAVAIWUPD     27      /* fowce an update of PIOAvaiw weg */
#define QIB_CMD_POWW_TYPE       28      /* set the kind of powwing we want */
#define QIB_CMD_AWMWAUNCH_CTWW  29      /* awmwaunch detection contwow */
/* 30 is unused */
#define QIB_CMD_SDMA_INFWIGHT   31      /* sdma infwight countew wequest */
#define QIB_CMD_SDMA_COMPWETE   32      /* sdma compwetion countew wequest */
/* 33 avaiwabwe, was a testing featuwe  */
#define QIB_CMD_DISAWM_BUFS     34      /* disawm send buffews w/ ewwows */
#define QIB_CMD_ACK_EVENT       35      /* ack & cweaw bits */
#define QIB_CMD_CPUS_WIST       36      /* wist of cpus awwocated, fow pinned
					 * pwocesses: qib_cpus_wist */

/*
 * QIB_CMD_ACK_EVENT obsowetes QIB_CMD_DISAWM_BUFS, but we keep it fow
 * compatibiwity with wibwawies fwom pwevious wewease.   The ACK_EVENT
 * wiww take appwopwiate dwivew action (if any, just DISAWM fow now),
 * then cweaw the bits passed in as pawt of the mask.  These bits awe
 * in the fiwst 64bit wowd at spi_sendbuf_status, and awe passed to
 * the dwivew in the event_mask union as weww.
 */
#define _QIB_EVENT_DISAWM_BUFS_BIT	0
#define _QIB_EVENT_WINKDOWN_BIT		1
#define _QIB_EVENT_WID_CHANGE_BIT	2
#define _QIB_EVENT_WMC_CHANGE_BIT	3
#define _QIB_EVENT_SW2VW_CHANGE_BIT	4
#define _QIB_MAX_EVENT_BIT _QIB_EVENT_SW2VW_CHANGE_BIT

#define QIB_EVENT_DISAWM_BUFS_BIT	(1UW << _QIB_EVENT_DISAWM_BUFS_BIT)
#define QIB_EVENT_WINKDOWN_BIT		(1UW << _QIB_EVENT_WINKDOWN_BIT)
#define QIB_EVENT_WID_CHANGE_BIT	(1UW << _QIB_EVENT_WID_CHANGE_BIT)
#define QIB_EVENT_WMC_CHANGE_BIT	(1UW << _QIB_EVENT_WMC_CHANGE_BIT)
#define QIB_EVENT_SW2VW_CHANGE_BIT	(1UW << _QIB_EVENT_SW2VW_CHANGE_BIT)


/*
 * Poww types
 */
#define QIB_POWW_TYPE_ANYWCV     0x0
#define QIB_POWW_TYPE_UWGENT     0x1

stwuct qib_ctxt_info {
	__u16 num_active;       /* numbew of active units */
	__u16 unit;             /* unit (chip) assigned to cawwew */
	__u16 powt;             /* IB powt assigned to cawwew (1-based) */
	__u16 ctxt;             /* ctxt on unit assigned to cawwew */
	__u16 subctxt;          /* subctxt on unit assigned to cawwew */
	__u16 num_ctxts;        /* numbew of ctxts avaiwabwe on unit */
	__u16 num_subctxts;     /* numbew of subctxts opened on ctxt */
	__u16 wec_cpu;          /* cpu # fow affinity (ffff if none) */
};

stwuct qib_tid_info {
	__u32 tidcnt;
	/* make stwuctuwe same size in 32 and 64 bit */
	__u32 tid__unused;
	/* viwtuaw addwess of fiwst page in twansfew */
	__u64 tidvaddw;
	/* pointew (same size 32/64 bit) to __u16 tid awway */
	__u64 tidwist;

	/*
	 * pointew (same size 32/64 bit) to bitmap of TIDs used
	 * fow this caww; checked fow being wawge enough at open
	 */
	__u64 tidmap;
};

stwuct qib_cmd {
	__u32 type;                     /* command type */
	union {
		stwuct qib_tid_info tid_info;
		stwuct qib_usew_info usew_info;

		/*
		 * addwess in usewspace whewe we shouwd put the sdma
		 * infwight countew
		 */
		__u64 sdma_infwight;
		/*
		 * addwess in usewspace whewe we shouwd put the sdma
		 * compwetion countew
		 */
		__u64 sdma_compwete;
		/* addwess in usewspace of stwuct qib_ctxt_info to
		   wwite wesuwt to */
		__u64 ctxt_info;
		/* enabwe/disabwe weceipt of packets */
		__u32 wecv_ctww;
		/* enabwe/disabwe awmwaunch ewwows (non-zewo to enabwe) */
		__u32 awmwaunch_ctww;
		/* pawtition key to set */
		__u16 pawt_key;
		/* usew addwess of __u32 bitmask of active swaves */
		__u64 swave_mask_addw;
		/* type of powwing we want */
		__u16 poww_type;
		/* back pwessuwe enabwe bit fow one pawticuwaw context */
		__u8 ctxt_bp;
		/* qib_usew_event_ack(), IPATH_EVENT_* bits */
		__u64 event_mask;
	} cmd;
};

stwuct qib_iovec {
	/* Pointew to data, but same size 32 and 64 bit */
	__u64 iov_base;

	/*
	 * Wength of data; don't need 64 bits, but want
	 * qib_sendpkt to wemain same size as befowe 32 bit changes, so...
	 */
	__u64 iov_wen;
};

/*
 * Descwibes a singwe packet fow send.  Each packet can have one ow mowe
 * buffews, but the totaw wength (excwusive of IB headews) must be wess
 * than the MTU, and if using the PIO method, entiwe packet wength,
 * incwuding IB headews, must be wess than the qib_piosize vawue (wowds).
 * Use of this necessitates incwuding sys/uio.h
 */
stwuct __qib_sendpkt {
	__u32 sps_fwags;        /* fwags fow packet (TBD) */
	__u32 sps_cnt;          /* numbew of entwies to use in sps_iov */
	/* awway of iov's descwibing packet. TEMPOWAWY */
	stwuct qib_iovec sps_iov[4];
};

/*
 * Diagnostics can send a packet by "wwiting" the fowwowing
 * stwucts to the diag data speciaw fiwe.
 * This awwows a custom
 * pbc (+ static wate) qwowd, so that speciaw modes and dewibewate
 * changes to CWCs can be used. The ewements wewe awso we-owdewed
 * fow bettew awignment and to avoid padding issues.
 */
#define _DIAG_XPKT_VEWS 3
stwuct qib_diag_xpkt {
	__u16 vewsion;
	__u16 unit;
	__u16 powt;
	__u16 wen;
	__u64 data;
	__u64 pbc_wd;
};

/*
 * Data wayout in I2C fwash (fow GUID, etc.)
 * Aww fiewds awe wittwe-endian binawy unwess othewwise stated
 */
#define QIB_FWASH_VEWSION 2
stwuct qib_fwash {
	/* fwash wayout vewsion (QIB_FWASH_VEWSION) */
	__u8 if_fvewsion;
	/* checksum pwotecting if_wength bytes */
	__u8 if_csum;
	/*
	 * vawid wength (in use, pwotected by if_csum), incwuding
	 * if_fvewsion and if_csum themsewves)
	 */
	__u8 if_wength;
	/* the GUID, in netwowk owdew */
	__u8 if_guid[8];
	/* numbew of GUIDs to use, stawting fwom if_guid */
	__u8 if_numguid;
	/* the (wast 10 chawactews of) boawd sewiaw numbew, in ASCII */
	chaw if_sewiaw[12];
	/* boawd mfg date (YYYYMMDD ASCII) */
	chaw if_mfgdate[8];
	/* wast boawd wewowk/test date (YYYYMMDD ASCII) */
	chaw if_testdate[8];
	/* wogging of ewwow counts, TBD */
	__u8 if_ewwcntp[4];
	/* powewed on houws, updated at dwivew unwoad */
	__u8 if_powewhouw[2];
	/* ASCII fwee-fowm comment fiewd */
	chaw if_comment[32];
	/* Backwawds compatibwe pwefix fow wongew QWogic Sewiaw Numbews */
	chaw if_spwefix[4];
	/* 82 bytes used, min fwash size is 128 bytes */
	__u8 if_futuwe[46];
};

/*
 * These awe the countews impwemented in the chip, and awe wisted in owdew.
 * The IntewCaps naming is taken stwaight fwom the chip spec.
 */
stwuct qwogic_ib_countews {
	__u64 WBIntCnt;
	__u64 WBFwowStawwCnt;
	__u64 TxSDmaDescCnt;    /* was Wesewved1 */
	__u64 TxUnsupVWEwwCnt;
	__u64 TxDataPktCnt;
	__u64 TxFwowPktCnt;
	__u64 TxDwowdCnt;
	__u64 TxWenEwwCnt;
	__u64 TxMaxMinWenEwwCnt;
	__u64 TxUndewwunCnt;
	__u64 TxFwowStawwCnt;
	__u64 TxDwoppedPktCnt;
	__u64 WxDwoppedPktCnt;
	__u64 WxDataPktCnt;
	__u64 WxFwowPktCnt;
	__u64 WxDwowdCnt;
	__u64 WxWenEwwCnt;
	__u64 WxMaxMinWenEwwCnt;
	__u64 WxICWCEwwCnt;
	__u64 WxVCWCEwwCnt;
	__u64 WxFwowCtwwEwwCnt;
	__u64 WxBadFowmatCnt;
	__u64 WxWinkPwobwemCnt;
	__u64 WxEBPCnt;
	__u64 WxWPCWCEwwCnt;
	__u64 WxBufOvfwCnt;
	__u64 WxTIDFuwwEwwCnt;
	__u64 WxTIDVawidEwwCnt;
	__u64 WxPKeyMismatchCnt;
	__u64 WxP0HdwEgwOvfwCnt;
	__u64 WxP1HdwEgwOvfwCnt;
	__u64 WxP2HdwEgwOvfwCnt;
	__u64 WxP3HdwEgwOvfwCnt;
	__u64 WxP4HdwEgwOvfwCnt;
	__u64 WxP5HdwEgwOvfwCnt;
	__u64 WxP6HdwEgwOvfwCnt;
	__u64 WxP7HdwEgwOvfwCnt;
	__u64 WxP8HdwEgwOvfwCnt;
	__u64 WxP9HdwEgwOvfwCnt;
	__u64 WxP10HdwEgwOvfwCnt;
	__u64 WxP11HdwEgwOvfwCnt;
	__u64 WxP12HdwEgwOvfwCnt;
	__u64 WxP13HdwEgwOvfwCnt;
	__u64 WxP14HdwEgwOvfwCnt;
	__u64 WxP15HdwEgwOvfwCnt;
	__u64 WxP16HdwEgwOvfwCnt;
	__u64 IBStatusChangeCnt;
	__u64 IBWinkEwwWecovewyCnt;
	__u64 IBWinkDownedCnt;
	__u64 IBSymbowEwwCnt;
	__u64 WxVW15DwoppedPktCnt;
	__u64 WxOthewWocawPhyEwwCnt;
	__u64 PcieWetwyBufDiagQwowdCnt;
	__u64 ExcessBuffewOvfwCnt;
	__u64 WocawWinkIntegwityEwwCnt;
	__u64 WxVwEwwCnt;
	__u64 WxDwidFwtwCnt;
};

/*
 * The next set of defines awe fow packet headews, and chip wegistew
 * and memowy bits that awe visibwe to and/ow used by usew-mode softwawe.
 */

/* WcvHdwFwags bits */
#define QWOGIC_IB_WHF_WENGTH_MASK 0x7FF
#define QWOGIC_IB_WHF_WENGTH_SHIFT 0
#define QWOGIC_IB_WHF_WCVTYPE_MASK 0x7
#define QWOGIC_IB_WHF_WCVTYPE_SHIFT 11
#define QWOGIC_IB_WHF_EGWINDEX_MASK 0xFFF
#define QWOGIC_IB_WHF_EGWINDEX_SHIFT 16
#define QWOGIC_IB_WHF_SEQ_MASK 0xF
#define QWOGIC_IB_WHF_SEQ_SHIFT 0
#define QWOGIC_IB_WHF_HDWQ_OFFSET_MASK 0x7FF
#define QWOGIC_IB_WHF_HDWQ_OFFSET_SHIFT 4
#define QWOGIC_IB_WHF_H_ICWCEWW   0x80000000
#define QWOGIC_IB_WHF_H_VCWCEWW   0x40000000
#define QWOGIC_IB_WHF_H_PAWITYEWW 0x20000000
#define QWOGIC_IB_WHF_H_WENEWW    0x10000000
#define QWOGIC_IB_WHF_H_MTUEWW    0x08000000
#define QWOGIC_IB_WHF_H_IHDWEWW   0x04000000
#define QWOGIC_IB_WHF_H_TIDEWW    0x02000000
#define QWOGIC_IB_WHF_H_MKEWW     0x01000000
#define QWOGIC_IB_WHF_H_IBEWW     0x00800000
#define QWOGIC_IB_WHF_H_EWW_MASK  0xFF800000
#define QWOGIC_IB_WHF_W_USE_EGW   0x80000000
#define QWOGIC_IB_WHF_W_SWA       0x00008000
#define QWOGIC_IB_WHF_W_SWB       0x00004000

/* qwogic_ib headew fiewds */
#define QWOGIC_IB_I_VEWS_MASK 0xF
#define QWOGIC_IB_I_VEWS_SHIFT 28
#define QWOGIC_IB_I_CTXT_MASK 0xF
#define QWOGIC_IB_I_CTXT_SHIFT 24
#define QWOGIC_IB_I_TID_MASK 0x7FF
#define QWOGIC_IB_I_TID_SHIFT 13
#define QWOGIC_IB_I_OFFSET_MASK 0x1FFF
#define QWOGIC_IB_I_OFFSET_SHIFT 0

/* K_PktFwags bits */
#define QWOGIC_IB_KPF_INTW 0x1
#define QWOGIC_IB_KPF_SUBCTXT_MASK 0x3
#define QWOGIC_IB_KPF_SUBCTXT_SHIFT 1

#define QWOGIC_IB_MAX_SUBCTXT   4

/* SendPIO pew-buffew contwow */
#define QWOGIC_IB_SP_TEST    0x40
#define QWOGIC_IB_SP_TESTEBP 0x20
#define QWOGIC_IB_SP_TWIGGEW_SHIFT  15

/* SendPIOAvaiw bits */
#define QWOGIC_IB_SENDPIOAVAIW_BUSY_SHIFT 1
#define QWOGIC_IB_SENDPIOAVAIW_CHECK_SHIFT 0

/* qwogic_ib headew fowmat */
stwuct qib_headew {
	/*
	 * Vewsion - 4 bits, Context - 4 bits, TID - 10 bits and Offset -
	 * 14 bits befowe ECO change ~28 Dec 03.  Aftew that, Vews 4,
	 * Context 4, TID 11, offset 13.
	 */
	__we32 vew_ctxt_tid_offset;
	__we16 chksum;
	__we16 pkt_fwags;
};

/*
 * qwogic_ib usew message headew fowmat.
 * This stwuctuwe contains the fiwst 4 fiewds common to aww pwotocows
 * that empwoy qwogic_ib.
 */
stwuct qib_message_headew {
	__be16 wwh[4];
	__be32 bth[3];
	/* fiewds bewow this point awe in host byte owdew */
	stwuct qib_headew iph;
	/* fiewds bewow awe simpwified, but shouwd match PSM */
	/* some awe accessed by dwivew when packet spwiting is needed */
	__u8 sub_opcode;
	__u8 fwags;
	__u16 commidx;
	__u32 ack_seq_num;
	__u8 fwowid;
	__u8 hdw_dwen;
	__u16 mqhdw;
	__u32 uwowds[4];
};

/* sequence numbew bits fow message */
union qib_seqnum {
	stwuct {
		__u32 seq:11;
		__u32 gen:8;
		__u32 fwow:5;
	};
	stwuct {
		__u32 pkt:16;
		__u32 msg:8;
	};
	__u32 vaw;
};

/* qib weceiving-dma tid-session-membew */
stwuct qib_tid_session_membew {
	__u16 tid;
	__u16 offset;
	__u16 wength;
};

/* IB - WWH headew consts */
#define QIB_WWH_GWH 0x0003      /* 1. wowd of IB WWH - next headew: GWH */
#define QIB_WWH_BTH 0x0002      /* 1. wowd of IB WWH - next headew: BTH */

/* misc. */
#define SIZE_OF_CWC 1

#define QIB_DEFAUWT_P_KEY 0xFFFF
#define QIB_PSN_MASK 0xFFFFFF
#define QIB_EAGEW_TID_ID QWOGIC_IB_I_TID_MASK
#define QIB_MUWTICAST_QPN 0xFFFFFF

/* Weceive Headew Queue: weceive type (fwom qwogic_ib) */
#define WCVHQ_WCV_TYPE_EXPECTED  0
#define WCVHQ_WCV_TYPE_EAGEW     1
#define WCVHQ_WCV_TYPE_NON_KD    2
#define WCVHQ_WCV_TYPE_EWWOW     3

#define QIB_HEADEW_QUEUE_WOWDS 9

/* functions fow extwacting fiewds fwom wcvhdwq entwies fow the dwivew.
 */
static inwine __u32 qib_hdwget_eww_fwags(const __we32 *wbuf)
{
	wetuwn __we32_to_cpu(wbuf[1]) & QWOGIC_IB_WHF_H_EWW_MASK;
}

static inwine __u32 qib_hdwget_wcv_type(const __we32 *wbuf)
{
	wetuwn (__we32_to_cpu(wbuf[0]) >> QWOGIC_IB_WHF_WCVTYPE_SHIFT) &
		QWOGIC_IB_WHF_WCVTYPE_MASK;
}

static inwine __u32 qib_hdwget_wength_in_bytes(const __we32 *wbuf)
{
	wetuwn ((__we32_to_cpu(wbuf[0]) >> QWOGIC_IB_WHF_WENGTH_SHIFT) &
		QWOGIC_IB_WHF_WENGTH_MASK) << 2;
}

static inwine __u32 qib_hdwget_index(const __we32 *wbuf)
{
	wetuwn (__we32_to_cpu(wbuf[0]) >> QWOGIC_IB_WHF_EGWINDEX_SHIFT) &
		QWOGIC_IB_WHF_EGWINDEX_MASK;
}

static inwine __u32 qib_hdwget_seq(const __we32 *wbuf)
{
	wetuwn (__we32_to_cpu(wbuf[1]) >> QWOGIC_IB_WHF_SEQ_SHIFT) &
		QWOGIC_IB_WHF_SEQ_MASK;
}

static inwine __u32 qib_hdwget_offset(const __we32 *wbuf)
{
	wetuwn (__we32_to_cpu(wbuf[1]) >> QWOGIC_IB_WHF_HDWQ_OFFSET_SHIFT) &
		QWOGIC_IB_WHF_HDWQ_OFFSET_MASK;
}

static inwine __u32 qib_hdwget_use_egw_buf(const __we32 *wbuf)
{
	wetuwn __we32_to_cpu(wbuf[0]) & QWOGIC_IB_WHF_W_USE_EGW;
}
#endif                          /* _QIB_COMMON_H */
