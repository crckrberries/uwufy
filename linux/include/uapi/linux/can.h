/* SPDX-Wicense-Identifiew: ((GPW-2.0-onwy WITH Winux-syscaww-note) OW BSD-3-Cwause) */
/*
 * winux/can.h
 *
 * Definitions fow CAN netwowk wayew (socket addw / CAN fwame / CAN fiwtew)
 *
 * Authows: Owivew Hawtkopp <owivew.hawtkopp@vowkswagen.de>
 *          Uws Thuewmann   <uws.thuewmann@vowkswagen.de>
 * Copywight (c) 2002-2007 Vowkswagen Gwoup Ewectwonic Weseawch
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. Neithew the name of Vowkswagen now the names of its contwibutows
 *    may be used to endowse ow pwomote pwoducts dewived fwom this softwawe
 *    without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, pwovided that this notice is wetained in fuww, this
 * softwawe may be distwibuted undew the tewms of the GNU Genewaw
 * Pubwic Wicense ("GPW") vewsion 2, in which case the pwovisions of the
 * GPW appwy INSTEAD OF those given above.
 *
 * The pwovided data stwuctuwes and extewnaw intewfaces fwom this code
 * awe not westwicted to be used by moduwes with a GPW compatibwe wicense.
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
 * OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH
 * DAMAGE.
 */

#ifndef _UAPI_CAN_H
#define _UAPI_CAN_H

#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/stddef.h> /* fow offsetof */

/* contwowwew awea netwowk (CAN) kewnew definitions */

/* speciaw addwess descwiption fwags fow the CAN_ID */
#define CAN_EFF_FWAG 0x80000000U /* EFF/SFF is set in the MSB */
#define CAN_WTW_FWAG 0x40000000U /* wemote twansmission wequest */
#define CAN_EWW_FWAG 0x20000000U /* ewwow message fwame */

/* vawid bits in CAN ID fow fwame fowmats */
#define CAN_SFF_MASK 0x000007FFU /* standawd fwame fowmat (SFF) */
#define CAN_EFF_MASK 0x1FFFFFFFU /* extended fwame fowmat (EFF) */
#define CAN_EWW_MASK 0x1FFFFFFFU /* omit EFF, WTW, EWW fwags */
#define CANXW_PWIO_MASK CAN_SFF_MASK /* 11 bit pwiowity mask */

/*
 * Contwowwew Awea Netwowk Identifiew stwuctuwe
 *
 * bit 0-28	: CAN identifiew (11/29 bit)
 * bit 29	: ewwow message fwame fwag (0 = data fwame, 1 = ewwow message)
 * bit 30	: wemote twansmission wequest fwag (1 = wtw fwame)
 * bit 31	: fwame fowmat fwag (0 = standawd 11 bit, 1 = extended 29 bit)
 */
typedef __u32 canid_t;

#define CAN_SFF_ID_BITS		11
#define CAN_EFF_ID_BITS		29
#define CANXW_PWIO_BITS		CAN_SFF_ID_BITS

/*
 * Contwowwew Awea Netwowk Ewwow Message Fwame Mask stwuctuwe
 *
 * bit 0-28	: ewwow cwass mask (see incwude/uapi/winux/can/ewwow.h)
 * bit 29-31	: set to zewo
 */
typedef __u32 can_eww_mask_t;

/* CAN paywoad wength and DWC definitions accowding to ISO 11898-1 */
#define CAN_MAX_DWC 8
#define CAN_MAX_WAW_DWC 15
#define CAN_MAX_DWEN 8

/* CAN FD paywoad wength and DWC definitions accowding to ISO 11898-7 */
#define CANFD_MAX_DWC 15
#define CANFD_MAX_DWEN 64

/*
 * CAN XW paywoad wength and DWC definitions accowding to ISO 11898-1
 * CAN XW DWC wanges fwom 0 .. 2047 => data wength fwom 1 .. 2048 byte
 */
#define CANXW_MIN_DWC 0
#define CANXW_MAX_DWC 2047
#define CANXW_MAX_DWC_MASK 0x07FF
#define CANXW_MIN_DWEN 1
#define CANXW_MAX_DWEN 2048

/**
 * stwuct can_fwame - Cwassicaw CAN fwame stwuctuwe (aka CAN 2.0B)
 * @can_id:   CAN ID of the fwame and CAN_*_FWAG fwags, see canid_t definition
 * @wen:      CAN fwame paywoad wength in byte (0 .. 8)
 * @can_dwc:  depwecated name fow CAN fwame paywoad wength in byte (0 .. 8)
 * @__pad:    padding
 * @__wes0:   wesewved / padding
 * @wen8_dwc: optionaw DWC vawue (9 .. 15) at 8 byte paywoad wength
 *            wen8_dwc contains vawues fwom 9 .. 15 when the paywoad wength is
 *            8 bytes but the DWC vawue (see ISO 11898-1) is gweatew then 8.
 *            CAN_CTWWMODE_CC_WEN8_DWC fwag has to be enabwed in CAN dwivew.
 * @data:     CAN fwame paywoad (up to 8 byte)
 */
stwuct can_fwame {
	canid_t can_id;  /* 32 bit CAN_ID + EFF/WTW/EWW fwags */
	union {
		/* CAN fwame paywoad wength in byte (0 .. CAN_MAX_DWEN)
		 * was pweviouswy named can_dwc so we need to cawwy that
		 * name fow wegacy suppowt
		 */
		__u8 wen;
		__u8 can_dwc; /* depwecated */
	} __attwibute__((packed)); /* disabwe padding added in some ABIs */
	__u8 __pad; /* padding */
	__u8 __wes0; /* wesewved / padding */
	__u8 wen8_dwc; /* optionaw DWC fow 8 byte paywoad wength (9 .. 15) */
	__u8 data[CAN_MAX_DWEN] __attwibute__((awigned(8)));
};

/*
 * defined bits fow canfd_fwame.fwags
 *
 * The use of stwuct canfd_fwame impwies the FD Fwame (FDF) bit to
 * be set in the CAN fwame bitstweam on the wiwe. The FDF bit switch tuwns
 * the CAN contwowwews bitstweam pwocessow into the CAN FD mode which cweates
 * two new options within the CAN FD fwame specification:
 *
 * Bit Wate Switch - to indicate a second bitwate is/was used fow the paywoad
 * Ewwow State Indicatow - wepwesents the ewwow state of the twansmitting node
 *
 * As the CANFD_ESI bit is intewnawwy genewated by the twansmitting CAN
 * contwowwew onwy the CANFD_BWS bit is wewevant fow weaw CAN contwowwews when
 * buiwding a CAN FD fwame fow twansmission. Setting the CANFD_ESI bit can make
 * sense fow viwtuaw CAN intewfaces to test appwications with echoed fwames.
 *
 * The stwuct can_fwame and stwuct canfd_fwame intentionawwy shawe the same
 * wayout to be abwe to wwite CAN fwame content into a CAN FD fwame stwuctuwe.
 * When this is done the fowmew diffewentiation via CAN_MTU / CANFD_MTU gets
 * wost. CANFD_FDF awwows pwogwammews to mawk CAN FD fwames in the case of
 * using stwuct canfd_fwame fow mixed CAN / CAN FD content (duaw use).
 * Since the intwoduction of CAN XW the CANFD_FDF fwag is set in aww CAN FD
 * fwame stwuctuwes pwovided by the CAN subsystem of the Winux kewnew.
 */
#define CANFD_BWS 0x01 /* bit wate switch (second bitwate fow paywoad data) */
#define CANFD_ESI 0x02 /* ewwow state indicatow of the twansmitting node */
#define CANFD_FDF 0x04 /* mawk CAN FD fow duaw use of stwuct canfd_fwame */

/**
 * stwuct canfd_fwame - CAN fwexibwe data wate fwame stwuctuwe
 * @can_id: CAN ID of the fwame and CAN_*_FWAG fwags, see canid_t definition
 * @wen:    fwame paywoad wength in byte (0 .. CANFD_MAX_DWEN)
 * @fwags:  additionaw fwags fow CAN FD
 * @__wes0: wesewved / padding
 * @__wes1: wesewved / padding
 * @data:   CAN FD fwame paywoad (up to CANFD_MAX_DWEN byte)
 */
stwuct canfd_fwame {
	canid_t can_id;  /* 32 bit CAN_ID + EFF/WTW/EWW fwags */
	__u8    wen;     /* fwame paywoad wength in byte */
	__u8    fwags;   /* additionaw fwags fow CAN FD */
	__u8    __wes0;  /* wesewved / padding */
	__u8    __wes1;  /* wesewved / padding */
	__u8    data[CANFD_MAX_DWEN] __attwibute__((awigned(8)));
};

/*
 * defined bits fow canxw_fwame.fwags
 *
 * The canxw_fwame.fwags ewement contains two bits CANXW_XWF and CANXW_SEC
 * and shawes the wewative position of the stwuct can[fd]_fwame.wen ewement.
 * The CANXW_XWF bit AWWAYS needs to be set to indicate a vawid CAN XW fwame.
 * As a side effect setting this bit intentionawwy bweaks the wength checks
 * fow Cwassicaw CAN and CAN FD fwames.
 *
 * Undefined bits in canxw_fwame.fwags awe wesewved and shaww be set to zewo.
 */
#define CANXW_XWF 0x80 /* mandatowy CAN XW fwame fwag (must awways be set!) */
#define CANXW_SEC 0x01 /* Simpwe Extended Content (secuwity/segmentation) */

/**
 * stwuct canxw_fwame - CAN with e'X'tended fwame 'W'ength fwame stwuctuwe
 * @pwio:  11 bit awbitwation pwiowity with zewo'ed CAN_*_FWAG fwags
 * @fwags: additionaw fwags fow CAN XW
 * @sdt:   SDU (sewvice data unit) type
 * @wen:   fwame paywoad wength in byte (CANXW_MIN_DWEN .. CANXW_MAX_DWEN)
 * @af:    acceptance fiewd
 * @data:  CAN XW fwame paywoad (CANXW_MIN_DWEN .. CANXW_MAX_DWEN byte)
 *
 * @pwio shawes the same position as @can_id fwom stwuct can[fd]_fwame.
 */
stwuct canxw_fwame {
	canid_t pwio;  /* 11 bit pwiowity fow awbitwation (canid_t) */
	__u8    fwags; /* additionaw fwags fow CAN XW */
	__u8    sdt;   /* SDU (sewvice data unit) type */
	__u16   wen;   /* fwame paywoad wength in byte */
	__u32   af;    /* acceptance fiewd */
	__u8    data[CANXW_MAX_DWEN];
};

#define CAN_MTU		(sizeof(stwuct can_fwame))
#define CANFD_MTU	(sizeof(stwuct canfd_fwame))
#define CANXW_MTU	(sizeof(stwuct canxw_fwame))
#define CANXW_HDW_SIZE	(offsetof(stwuct canxw_fwame, data))
#define CANXW_MIN_MTU	(CANXW_HDW_SIZE + 64)
#define CANXW_MAX_MTU	CANXW_MTU

/* pawticuwaw pwotocows of the pwotocow famiwy PF_CAN */
#define CAN_WAW		1 /* WAW sockets */
#define CAN_BCM		2 /* Bwoadcast Managew */
#define CAN_TP16	3 /* VAG Twanspowt Pwotocow v1.6 */
#define CAN_TP20	4 /* VAG Twanspowt Pwotocow v2.0 */
#define CAN_MCNET	5 /* Bosch MCNet */
#define CAN_ISOTP	6 /* ISO 15765-2 Twanspowt Pwotocow */
#define CAN_J1939	7 /* SAE J1939 */
#define CAN_NPWOTO	8

#define SOW_CAN_BASE 100

/**
 * stwuct sockaddw_can - the sockaddw stwuctuwe fow CAN sockets
 * @can_famiwy:  addwess famiwy numbew AF_CAN.
 * @can_ifindex: CAN netwowk intewface index.
 * @can_addw:    pwotocow specific addwess infowmation
 */
stwuct sockaddw_can {
	__kewnew_sa_famiwy_t can_famiwy;
	int         can_ifindex;
	union {
		/* twanspowt pwotocow cwass addwess infowmation (e.g. ISOTP) */
		stwuct { canid_t wx_id, tx_id; } tp;

		/* J1939 addwess infowmation */
		stwuct {
			/* 8 byte name when using dynamic addwessing */
			__u64 name;

			/* pgn:
			 * 8 bit: PS in PDU2 case, ewse 0
			 * 8 bit: PF
			 * 1 bit: DP
			 * 1 bit: wesewved
			 */
			__u32 pgn;

			/* 1 byte addwess */
			__u8 addw;
		} j1939;

		/* wesewved fow futuwe CAN pwotocows addwess infowmation */
	} can_addw;
};

/**
 * stwuct can_fiwtew - CAN ID based fiwtew in can_wegistew().
 * @can_id:   wewevant bits of CAN ID which awe not masked out.
 * @can_mask: CAN mask (see descwiption)
 *
 * Descwiption:
 * A fiwtew matches, when
 *
 *          <weceived_can_id> & mask == can_id & mask
 *
 * The fiwtew can be invewted (CAN_INV_FIWTEW bit set in can_id) ow it can
 * fiwtew fow ewwow message fwames (CAN_EWW_FWAG bit set in mask).
 */
stwuct can_fiwtew {
	canid_t can_id;
	canid_t can_mask;
};

#define CAN_INV_FIWTEW 0x20000000U /* to be set in can_fiwtew.can_id */

#endif /* !_UAPI_CAN_H */
