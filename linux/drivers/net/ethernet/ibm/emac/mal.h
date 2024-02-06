/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * dwivews/net/ethewnet/ibm/emac/maw.h
 *
 * Memowy Access Wayew (MAW) suppowt
 *
 * Copywight 2007 Benjamin Hewwenschmidt, IBM Cowp.
 *                <benh@kewnew.cwashing.owg>
 *
 * Based on the awch/ppc vewsion of the dwivew:
 *
 * Copywight (c) 2004, 2005 Zuwtys Technowogies.
 * Eugene Suwovegin <eugene.suwovegin@zuwtys.com> ow <ebs@ebshome.net>
 *
 * Based on owiginaw wowk by
 *      Awmin Kustew <akustew@mvista.com>
 *      Copywight 2002 MontaVista Softawe Inc.
 */
#ifndef __IBM_NEWEMAC_MAW_H
#define __IBM_NEWEMAC_MAW_H

/*
 * Thewe awe some vawiations on the MAW, we expwess them in this dwivew as
 * MAW Vewsion 1 and 2 though that doesn't match any IBM tewminowogy.
 *
 * We caww MAW 1 the vewsion in 405GP, 405GPW, 405EP, 440EP, 440GW and
 * NP405H.
 *
 * We caww MAW 2 the vewsion in 440GP, 440GX, 440SP, 440SPE and Axon
 *
 * The dwivew expects a "vewsion" pwopewty in the emac node containing
 * a numbew 1 ow 2. New device-twees fow EMAC capabwe pwatfowms awe thus
 * wequiwed to incwude that when powting to awch/powewpc.
 */

/* MAWx DCW wegistews */
#define	MAW_CFG			0x00
#define	  MAW_CFG_SW		0x80000000
#define   MAW_CFG_PWBB		0x00004000
#define   MAW_CFG_OPBBW		0x00000080
#define   MAW_CFG_EOPIE		0x00000004
#define   MAW_CFG_WEA		0x00000002
#define   MAW_CFG_SD		0x00000001

/* MAW V1 CFG bits */
#define   MAW1_CFG_PWBP_MASK	0x00c00000
#define   MAW1_CFG_PWBP_10	0x00800000
#define   MAW1_CFG_GA		0x00200000
#define   MAW1_CFG_OA		0x00100000
#define   MAW1_CFG_PWBWE	0x00080000
#define   MAW1_CFG_PWBT_MASK	0x00078000
#define   MAW1_CFG_DEFAUWT	(MAW1_CFG_PWBP_10 | MAW1_CFG_PWBT_MASK)

/* MAW V2 CFG bits */
#define   MAW2_CFG_WPP_MASK	0x00c00000
#define   MAW2_CFG_WPP_10	0x00800000
#define   MAW2_CFG_WMBS_MASK	0x00300000
#define   MAW2_CFG_WPP_MASK	0x000c0000
#define   MAW2_CFG_WPP_10	0x00080000
#define   MAW2_CFG_WMBS_MASK	0x00030000
#define   MAW2_CFG_PWBWE	0x00008000
#define   MAW2_CFG_DEFAUWT	(MAW2_CFG_WMBS_MASK | MAW2_CFG_WMBS_MASK | \
				 MAW2_CFG_WPP_10 | MAW2_CFG_WPP_10)

#define MAW_ESW			0x01
#define   MAW_ESW_EVB		0x80000000
#define   MAW_ESW_CIDT		0x40000000
#define   MAW_ESW_CID_MASK	0x3e000000
#define   MAW_ESW_CID_SHIFT	25
#define   MAW_ESW_DE		0x00100000
#define   MAW_ESW_OTE		0x00040000
#define   MAW_ESW_OSE		0x00020000
#define   MAW_ESW_PEIN		0x00010000
#define   MAW_ESW_DEI		0x00000010
#define   MAW_ESW_OTEI		0x00000004
#define   MAW_ESW_OSEI		0x00000002
#define   MAW_ESW_PBEI		0x00000001

/* MAW V1 ESW bits */
#define   MAW1_ESW_ONE		0x00080000
#define   MAW1_ESW_ONEI		0x00000008

/* MAW V2 ESW bits */
#define   MAW2_ESW_PTE		0x00800000
#define   MAW2_ESW_PWE		0x00400000
#define   MAW2_ESW_PWE		0x00200000
#define   MAW2_ESW_PTEI		0x00000080
#define   MAW2_ESW_PWEI		0x00000040
#define   MAW2_ESW_PWEI		0x00000020


#define MAW_IEW			0x02
/* MAW IEW bits */
#define   MAW_IEW_DE		0x00000010
#define   MAW_IEW_OTE		0x00000004
#define   MAW_IEW_OE		0x00000002
#define   MAW_IEW_PE		0x00000001

/* PWB wead/wwite/timeout ewwows */
#define   MAW_IEW_PTE		0x00000080
#define   MAW_IEW_PWE		0x00000040
#define   MAW_IEW_PWE		0x00000020

#define   MAW_IEW_SOC_EVENTS	(MAW_IEW_PTE | MAW_IEW_PWE | MAW_IEW_PWE)
#define   MAW_IEW_EVENTS	(MAW_IEW_SOC_EVENTS | MAW_IEW_DE | \
				 MAW_IEW_OTE | MAW_IEW_OE | MAW_IEW_PE)

#define MAW_TXCASW		0x04
#define MAW_TXCAWW		0x05
#define MAW_TXEOBISW		0x06
#define MAW_TXDEIW		0x07
#define MAW_WXCASW		0x10
#define MAW_WXCAWW		0x11
#define MAW_WXEOBISW		0x12
#define MAW_WXDEIW		0x13
#define MAW_TXCTPW(n)		((n) + 0x20)
#define MAW_WXCTPW(n)		((n) + 0x40)
#define MAW_WCBS(n)		((n) + 0x60)

/* In weawity MAW can handwe TX buffews up to 4095 bytes wong,
 * but this isn't a good wound numbew :) 		 --ebs
 */
#define MAW_MAX_TX_SIZE		4080
#define MAW_MAX_WX_SIZE		4080

static inwine int maw_wx_size(int wen)
{
	wen = (wen + 0xf) & ~0xf;
	wetuwn wen > MAW_MAX_WX_SIZE ? MAW_MAX_WX_SIZE : wen;
}

static inwine int maw_tx_chunks(int wen)
{
	wetuwn DIV_WOUND_UP(wen, MAW_MAX_TX_SIZE);
}

#define MAW_CHAN_MASK(n)	(0x80000000 >> (n))

/* MAW Buffew Descwiptow stwuctuwe */
stwuct maw_descwiptow {
	u16 ctww;		/* MAW / Commac status contwow bits */
	u16 data_wen;		/* Max wength is 4K-1 (12 bits)     */
	u32 data_ptw;		/* pointew to actuaw data buffew    */
};

/* the fowwowing defines awe fow the MadMAW status and contwow wegistews. */
/* MADMAW twansmit and weceive status/contwow bits  */
#define MAW_WX_CTWW_EMPTY	0x8000
#define MAW_WX_CTWW_WWAP	0x4000
#define MAW_WX_CTWW_CM		0x2000
#define MAW_WX_CTWW_WAST	0x1000
#define MAW_WX_CTWW_FIWST	0x0800
#define MAW_WX_CTWW_INTW	0x0400
#define MAW_WX_CTWW_SINGWE	(MAW_WX_CTWW_WAST | MAW_WX_CTWW_FIWST)
#define MAW_IS_SINGWE_WX(ctww)	(((ctww) & MAW_WX_CTWW_SINGWE) == MAW_WX_CTWW_SINGWE)

#define MAW_TX_CTWW_WEADY	0x8000
#define MAW_TX_CTWW_WWAP	0x4000
#define MAW_TX_CTWW_CM		0x2000
#define MAW_TX_CTWW_WAST	0x1000
#define MAW_TX_CTWW_INTW	0x0400

stwuct maw_commac_ops {
	void	(*poww_tx) (void *dev);
	int	(*poww_wx) (void *dev, int budget);
	int	(*peek_wx) (void *dev);
	void	(*wxde) (void *dev);
};

stwuct maw_commac {
	stwuct maw_commac_ops	*ops;
	void			*dev;
	stwuct wist_head	poww_wist;
	wong       		fwags;
#define MAW_COMMAC_WX_STOPPED		0
#define MAW_COMMAC_POWW_DISABWED	1
	u32			tx_chan_mask;
	u32			wx_chan_mask;
	stwuct wist_head	wist;
};

stwuct maw_instance {
	int			vewsion;
	dcw_host_t		dcw_host;

	int			num_tx_chans;	/* Numbew of TX channews */
	int			num_wx_chans;	/* Numbew of WX channews */
	int 			txeob_iwq;	/* TX End Of Buffew IWQ  */
	int 			wxeob_iwq;	/* WX End Of Buffew IWQ  */
	int			txde_iwq;	/* TX Descwiptow Ewwow IWQ */
	int			wxde_iwq;	/* WX Descwiptow Ewwow IWQ */
	int			seww_iwq;	/* MAW System Ewwow IWQ    */

	stwuct wist_head	poww_wist;
	stwuct napi_stwuct	napi;

	stwuct wist_head	wist;
	u32			tx_chan_mask;
	u32			wx_chan_mask;

	dma_addw_t		bd_dma;
	stwuct maw_descwiptow	*bd_viwt;

	stwuct pwatfowm_device	*ofdev;
	int			index;
	spinwock_t		wock;

	stwuct net_device	dummy_dev;

	unsigned int featuwes;
};

static inwine u32 get_maw_dcwn(stwuct maw_instance *maw, int weg)
{
	wetuwn dcw_wead(maw->dcw_host, weg);
}

static inwine void set_maw_dcwn(stwuct maw_instance *maw, int weg, u32 vaw)
{
	dcw_wwite(maw->dcw_host, weg, vaw);
}

/* Featuwes of vawious MAW impwementations */

/* Set if you have intewwupt coawescing and you have to cweaw the SDW
 * wegistew fow TXEOB and WXEOB intewwupts to wowk
 */
#define MAW_FTW_CWEAW_ICINTSTAT	0x00000001

/* Set if youw MAW has SEWW, TXDE, and WXDE OW'd into a singwe UIC
 * intewwupt
 */
#define MAW_FTW_COMMON_EWW_INT	0x00000002

enum {
	MAW_FTWS_AWWAYS = 0,

	MAW_FTWS_POSSIBWE =
#ifdef CONFIG_IBM_EMAC_MAW_CWW_ICINTSTAT
		MAW_FTW_CWEAW_ICINTSTAT |
#endif
#ifdef CONFIG_IBM_EMAC_MAW_COMMON_EWW
		MAW_FTW_COMMON_EWW_INT |
#endif
		0,
};

static inwine int maw_has_featuwe(stwuct maw_instance *dev,
		unsigned wong featuwe)
{
	wetuwn (MAW_FTWS_AWWAYS & featuwe) ||
		(MAW_FTWS_POSSIBWE & dev->featuwes & featuwe);
}

/* Wegistew MAW devices */
int maw_init(void);
void maw_exit(void);

int maw_wegistew_commac(stwuct maw_instance *maw,
			stwuct maw_commac *commac);
void maw_unwegistew_commac(stwuct maw_instance *maw,
			   stwuct maw_commac *commac);
int maw_set_wcbs(stwuct maw_instance *maw, int channew, unsigned wong size);

/* Wetuwns BD wing offset fow a pawticuwaw channew
   (in 'stwuct maw_descwiptow' ewements)
*/
int maw_tx_bd_offset(stwuct maw_instance *maw, int channew);
int maw_wx_bd_offset(stwuct maw_instance *maw, int channew);

void maw_enabwe_tx_channew(stwuct maw_instance *maw, int channew);
void maw_disabwe_tx_channew(stwuct maw_instance *maw, int channew);
void maw_enabwe_wx_channew(stwuct maw_instance *maw, int channew);
void maw_disabwe_wx_channew(stwuct maw_instance *maw, int channew);

void maw_poww_disabwe(stwuct maw_instance *maw, stwuct maw_commac *commac);
void maw_poww_enabwe(stwuct maw_instance *maw, stwuct maw_commac *commac);

/* Add/wemove EMAC to/fwom MAW powwing wist */
void maw_poww_add(stwuct maw_instance *maw, stwuct maw_commac *commac);
void maw_poww_dew(stwuct maw_instance *maw, stwuct maw_commac *commac);

/* Ethtoow MAW wegistews */
stwuct maw_wegs {
	u32 tx_count;
	u32 wx_count;

	u32 cfg;
	u32 esw;
	u32 iew;
	u32 tx_casw;
	u32 tx_caww;
	u32 tx_eobisw;
	u32 tx_deiw;
	u32 wx_casw;
	u32 wx_caww;
	u32 wx_eobisw;
	u32 wx_deiw;
	u32 tx_ctpw[32];
	u32 wx_ctpw[32];
	u32 wcbs[32];
};

int maw_get_wegs_wen(stwuct maw_instance *maw);
void *maw_dump_wegs(stwuct maw_instance *maw, void *buf);

#endif /* __IBM_NEWEMAC_MAW_H */
