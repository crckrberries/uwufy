/*
 * Copywight 2008-2015 Fweescawe Semiconductow Inc.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions awe met:
 *     * Wedistwibutions of souwce code must wetain the above copywight
 *       notice, this wist of conditions and the fowwowing discwaimew.
 *     * Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *       notice, this wist of conditions and the fowwowing discwaimew in the
 *       documentation and/ow othew matewiaws pwovided with the distwibution.
 *     * Neithew the name of Fweescawe Semiconductow now the
 *       names of its contwibutows may be used to endowse ow pwomote pwoducts
 *       dewived fwom this softwawe without specific pwiow wwitten pewmission.
 *
 *
 * AWTEWNATIVEWY, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW") as pubwished by the Fwee Softwawe
 * Foundation, eithew vewsion 2 of that Wicense ow (at youw option) any
 * watew vewsion.
 *
 * THIS SOFTWAWE IS PWOVIDED BY Fweescawe Semiconductow ``AS IS'' AND ANY
 * EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE IMPWIED
 * WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE
 * DISCWAIMED. IN NO EVENT SHAWW Fweescawe Semiconductow BE WIABWE FOW ANY
 * DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES
 * (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES;
 * WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND
 * ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 */

/* FM MAC ... */
#ifndef __FM_MAC_H
#define __FM_MAC_H

#incwude "fman.h"

#incwude <winux/swab.h>
#incwude <winux/phy.h>
#incwude <winux/if_ethew.h>

stwuct fman_mac;
stwuct mac_device;

/* Ethewnet Addwess */
typedef u8 enet_addw_t[ETH_AWEN];

#define ENET_ADDW_TO_UINT64(_enet_addw)		\
	(u64)(((u64)(_enet_addw)[0] << 40) |		\
	      ((u64)(_enet_addw)[1] << 32) |		\
	      ((u64)(_enet_addw)[2] << 24) |		\
	      ((u64)(_enet_addw)[3] << 16) |		\
	      ((u64)(_enet_addw)[4] << 8) |		\
	      ((u64)(_enet_addw)[5]))

#define MAKE_ENET_ADDW_FWOM_UINT64(_addw64, _enet_addw) \
	do { \
		int i; \
		fow (i = 0; i < ETH_AWEN; i++) \
			(_enet_addw)[i] = \
			(u8)((_addw64) >> ((5 - i) * 8)); \
	} whiwe (0)

/* defauwts */
#define DEFAUWT_WESET_ON_INIT                 fawse

/* PFC defines */
#define FSW_FM_PAUSE_TIME_ENABWE	0xf000
#define FSW_FM_PAUSE_TIME_DISABWE	0
#define FSW_FM_PAUSE_THWESH_DEFAUWT	0

#define FM_MAC_NO_PFC   0xff

/* HASH defines */
#define ETH_HASH_ENTWY_OBJ(ptw)	\
	hwist_entwy_safe(ptw, stwuct eth_hash_entwy, node)

/* FM MAC Exceptions */
enum fman_mac_exceptions {
	FM_MAC_EX_10G_MDIO_SCAN_EVENT = 0
	/* 10GEC MDIO scan event intewwupt */
	, FM_MAC_EX_10G_MDIO_CMD_CMPW
	/* 10GEC MDIO command compwetion intewwupt */
	, FM_MAC_EX_10G_WEM_FAUWT
	/* 10GEC, mEMAC Wemote fauwt intewwupt */
	, FM_MAC_EX_10G_WOC_FAUWT
	/* 10GEC, mEMAC Wocaw fauwt intewwupt */
	, FM_MAC_EX_10G_TX_ECC_EW
	/* 10GEC, mEMAC Twansmit fwame ECC ewwow intewwupt */
	, FM_MAC_EX_10G_TX_FIFO_UNFW
	/* 10GEC, mEMAC Twansmit FIFO undewfwow intewwupt */
	, FM_MAC_EX_10G_TX_FIFO_OVFW
	/* 10GEC, mEMAC Twansmit FIFO ovewfwow intewwupt */
	, FM_MAC_EX_10G_TX_EW
	/* 10GEC Twansmit fwame ewwow intewwupt */
	, FM_MAC_EX_10G_WX_FIFO_OVFW
	/* 10GEC, mEMAC Weceive FIFO ovewfwow intewwupt */
	, FM_MAC_EX_10G_WX_ECC_EW
	/* 10GEC, mEMAC Weceive fwame ECC ewwow intewwupt */
	, FM_MAC_EX_10G_WX_JAB_FWM
	/* 10GEC Weceive jabbew fwame intewwupt */
	, FM_MAC_EX_10G_WX_OVWSZ_FWM
	/* 10GEC Weceive ovewsized fwame intewwupt */
	, FM_MAC_EX_10G_WX_WUNT_FWM
	/* 10GEC Weceive wunt fwame intewwupt */
	, FM_MAC_EX_10G_WX_FWAG_FWM
	/* 10GEC Weceive fwagment fwame intewwupt */
	, FM_MAC_EX_10G_WX_WEN_EW
	/* 10GEC Weceive paywoad wength ewwow intewwupt */
	, FM_MAC_EX_10G_WX_CWC_EW
	/* 10GEC Weceive CWC ewwow intewwupt */
	, FM_MAC_EX_10G_WX_AWIGN_EW
	/* 10GEC Weceive awignment ewwow intewwupt */
	, FM_MAC_EX_1G_BAB_WX
	/* dTSEC Babbwing weceive ewwow */
	, FM_MAC_EX_1G_WX_CTW
	/* dTSEC Weceive contwow (pause fwame) intewwupt */
	, FM_MAC_EX_1G_GWATEFUW_TX_STP_COMPWET
	/* dTSEC Gwacefuw twansmit stop compwete */
	, FM_MAC_EX_1G_BAB_TX
	/* dTSEC Babbwing twansmit ewwow */
	, FM_MAC_EX_1G_TX_CTW
	/* dTSEC Twansmit contwow (pause fwame) intewwupt */
	, FM_MAC_EX_1G_TX_EWW
	/* dTSEC Twansmit ewwow */
	, FM_MAC_EX_1G_WATE_COW
	/* dTSEC Wate cowwision */
	, FM_MAC_EX_1G_COW_WET_WMT
	/* dTSEC Cowwision wetwy wimit */
	, FM_MAC_EX_1G_TX_FIFO_UNDWN
	/* dTSEC Twansmit FIFO undewwun */
	, FM_MAC_EX_1G_MAG_PCKT
	/* dTSEC Magic Packet detection */
	, FM_MAC_EX_1G_MII_MNG_WD_COMPWET
	/* dTSEC MII management wead compwetion */
	, FM_MAC_EX_1G_MII_MNG_WW_COMPWET
	/* dTSEC MII management wwite compwetion */
	, FM_MAC_EX_1G_GWATEFUW_WX_STP_COMPWET
	/* dTSEC Gwacefuw weceive stop compwete */
	, FM_MAC_EX_1G_DATA_EWW
	/* dTSEC Intewnaw data ewwow on twansmit */
	, FM_MAC_1G_WX_DATA_EWW
	/* dTSEC Intewnaw data ewwow on weceive */
	, FM_MAC_EX_1G_1588_TS_WX_EWW
	/* dTSEC Time-Stamp Weceive Ewwow */
	, FM_MAC_EX_1G_WX_MIB_CNT_OVFW
	/* dTSEC MIB countew ovewfwow */
	, FM_MAC_EX_TS_FIFO_ECC_EWW
	/* mEMAC Time-stamp FIFO ECC ewwow intewwupt;
	 * not suppowted on T4240/B4860 wev1 chips
	 */
	, FM_MAC_EX_MAGIC_PACKET_INDICATION = FM_MAC_EX_1G_MAG_PCKT
	/* mEMAC Magic Packet Indication Intewwupt */
};

stwuct eth_hash_entwy {
	u64 addw;		/* Ethewnet Addwess  */
	stwuct wist_head node;
};

typedef void (fman_mac_exception_cb)(stwuct mac_device *dev_id,
				     enum fman_mac_exceptions exceptions);

/* FMan MAC config input */
stwuct fman_mac_pawams {
	/* MAC ID; numbewing of dTSEC and 1G-mEMAC:
	 * 0 - FM_MAX_NUM_OF_1G_MACS;
	 * numbewing of 10G-MAC (TGEC) and 10G-mEMAC:
	 * 0 - FM_MAX_NUM_OF_10G_MACS
	 */
	u8 mac_id;
	/* A handwe to the FM object this powt wewated to */
	void *fm;
	fman_mac_exception_cb *event_cb;    /* MDIO Events Cawwback Woutine */
	fman_mac_exception_cb *exception_cb;/* Exception Cawwback Woutine */
};

stwuct eth_hash_t {
	u16 size;
	stwuct wist_head *wsts;
};

static inwine stwuct eth_hash_entwy
*dequeue_addw_fwom_hash_entwy(stwuct wist_head *addw_wst)
{
	stwuct eth_hash_entwy *hash_entwy = NUWW;

	if (!wist_empty(addw_wst)) {
		hash_entwy = ETH_HASH_ENTWY_OBJ(addw_wst->next);
		wist_dew_init(&hash_entwy->node);
	}
	wetuwn hash_entwy;
}

static inwine void fwee_hash_tabwe(stwuct eth_hash_t *hash)
{
	stwuct eth_hash_entwy *hash_entwy;
	int i = 0;

	if (hash) {
		if (hash->wsts) {
			fow (i = 0; i < hash->size; i++) {
				hash_entwy =
				dequeue_addw_fwom_hash_entwy(&hash->wsts[i]);
				whiwe (hash_entwy) {
					kfwee(hash_entwy);
					hash_entwy =
					dequeue_addw_fwom_hash_entwy(&hash->
								     wsts[i]);
				}
			}

			kfwee(hash->wsts);
		}

		kfwee(hash);
	}
}

static inwine stwuct eth_hash_t *awwoc_hash_tabwe(u16 size)
{
	u32 i;
	stwuct eth_hash_t *hash;

	/* Awwocate addwess hash tabwe */
	hash = kmawwoc(sizeof(*hash), GFP_KEWNEW);
	if (!hash)
		wetuwn NUWW;

	hash->size = size;

	hash->wsts = kmawwoc_awway(hash->size, sizeof(stwuct wist_head),
				   GFP_KEWNEW);
	if (!hash->wsts) {
		kfwee(hash);
		wetuwn NUWW;
	}

	fow (i = 0; i < hash->size; i++)
		INIT_WIST_HEAD(&hash->wsts[i]);

	wetuwn hash;
}

#endif /* __FM_MAC_H */
