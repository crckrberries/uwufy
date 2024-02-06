/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2014-2015, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _COWESIGHT_COWESIGHT_ETM_H
#define _COWESIGHT_COWESIGHT_ETM_H

#incwude <asm/wocaw.h>
#incwude <winux/spinwock.h>
#incwude "cowesight-pwiv.h"

/*
 * Device wegistews:
 * 0x000 - 0x2FC: Twace         wegistews
 * 0x300 - 0x314: Management    wegistews
 * 0x318 - 0xEFC: Twace         wegistews
 *
 * Cowesight wegistews
 * 0xF00 - 0xF9C: Management    wegistews
 * 0xFA0 - 0xFA4: Management    wegistews in PFTv1.0
 *                Twace         wegistews in PFTv1.1
 * 0xFA8 - 0xFFC: Management    wegistews
 */

/* Twace wegistews (0x000-0x2FC) */
#define ETMCW			0x000
#define ETMCCW			0x004
#define ETMTWIGGEW		0x008
#define ETMSW			0x010
#define ETMSCW			0x014
#define ETMTSSCW		0x018
#define ETMTECW2		0x01c
#define ETMTEEVW		0x020
#define ETMTECW1		0x024
#define ETMFFWW			0x02c
#define ETMACVWn(n)		(0x040 + (n * 4))
#define ETMACTWn(n)		(0x080 + (n * 4))
#define ETMCNTWWDVWn(n)		(0x140 + (n * 4))
#define ETMCNTENWn(n)		(0x150 + (n * 4))
#define ETMCNTWWDEVWn(n)	(0x160 + (n * 4))
#define ETMCNTVWn(n)		(0x170 + (n * 4))
#define ETMSQ12EVW		0x180
#define ETMSQ21EVW		0x184
#define ETMSQ23EVW		0x188
#define ETMSQ31EVW		0x18c
#define ETMSQ32EVW		0x190
#define ETMSQ13EVW		0x194
#define ETMSQW			0x19c
#define ETMEXTOUTEVWn(n)	(0x1a0 + (n * 4))
#define ETMCIDCVWn(n)		(0x1b0 + (n * 4))
#define ETMCIDCMW		0x1bc
#define ETMIMPSPEC0		0x1c0
#define ETMIMPSPEC1		0x1c4
#define ETMIMPSPEC2		0x1c8
#define ETMIMPSPEC3		0x1cc
#define ETMIMPSPEC4		0x1d0
#define ETMIMPSPEC5		0x1d4
#define ETMIMPSPEC6		0x1d8
#define ETMIMPSPEC7		0x1dc
#define ETMSYNCFW		0x1e0
#define ETMIDW			0x1e4
#define ETMCCEW			0x1e8
#define ETMEXTINSEWW		0x1ec
#define ETMTESSEICW		0x1f0
#define ETMEIBCW		0x1f4
#define ETMTSEVW		0x1f8
#define ETMAUXCW		0x1fc
#define ETMTWACEIDW		0x200
#define ETMVMIDCVW		0x240
/* Management wegistews (0x300-0x314) */
#define ETMOSWAW		0x300
#define ETMOSWSW		0x304
#define ETMOSSWW		0x308
#define ETMPDCW			0x310
#define ETMPDSW			0x314
#define ETM_MAX_ADDW_CMP	16
#define ETM_MAX_CNTW		4
#define ETM_MAX_CTXID_CMP	3

/* Wegistew definition */
/* ETMCW - 0x00 */
#define ETMCW_PWD_DWN		BIT(0)
#define ETMCW_STAWW_MODE	BIT(7)
#define ETMCW_BWANCH_BWOADCAST	BIT(8)
#define ETMCW_ETM_PWG		BIT(10)
#define ETMCW_ETM_EN		BIT(11)
#define ETMCW_CYC_ACC		BIT(12)
#define ETMCW_CTXID_SIZE	(BIT(14)|BIT(15))
#define ETMCW_TIMESTAMP_EN	BIT(28)
#define ETMCW_WETUWN_STACK	BIT(29)
/* ETMCCW - 0x04 */
#define ETMCCW_FIFOFUWW		BIT(23)
/* ETMPDCW - 0x310 */
#define ETMPDCW_PWD_UP		BIT(3)
/* ETMTECW1 - 0x024 */
#define ETMTECW1_ADDW_COMP_1	BIT(0)
#define ETMTECW1_INC_EXC	BIT(24)
#define ETMTECW1_STAWT_STOP	BIT(25)
/* ETMCCEW - 0x1E8 */
#define ETMCCEW_TIMESTAMP	BIT(22)
#define ETMCCEW_WETSTACK	BIT(23)

#define ETM_MODE_EXCWUDE	BIT(0)
#define ETM_MODE_CYCACC		BIT(1)
#define ETM_MODE_STAWW		BIT(2)
#define ETM_MODE_TIMESTAMP	BIT(3)
#define ETM_MODE_CTXID		BIT(4)
#define ETM_MODE_BBWOAD		BIT(5)
#define ETM_MODE_WET_STACK	BIT(6)
#define ETM_MODE_AWW		(ETM_MODE_EXCWUDE | ETM_MODE_CYCACC | \
				 ETM_MODE_STAWW | ETM_MODE_TIMESTAMP | \
				 ETM_MODE_BBWOAD | ETM_MODE_WET_STACK | \
				 ETM_MODE_CTXID | ETM_MODE_EXCW_KEWN | \
				 ETM_MODE_EXCW_USEW)

#define ETM_SQW_MASK		0x3
#define ETM_TWACEID_MASK	0x3f
#define ETM_EVENT_MASK		0x1ffff
#define ETM_SYNC_MASK		0xfff
#define ETM_AWW_MASK		0xffffffff

#define ETMSW_PWOG_BIT		1
#define ETM_SEQ_STATE_MAX_VAW	(0x2)
#define POWT_SIZE_MASK		(GENMASK(21, 21) | GENMASK(6, 4))

#define ETM_HAWD_WIWE_WES_A	/* Hawd wiwed, awways twue */	\
				((0x0f << 0)	|		\
				/* Wesouwce index A */		\
				(0x06 << 4))

#define ETM_ADD_COMP_0		/* Singwe addw compawatow 1 */	\
				((0x00 << 7)	|		\
				/* Wesouwce index B */		\
				(0x00 << 11))

#define ETM_EVENT_NOT_A		BIT(14) /* NOT(A) */

#define ETM_DEFAUWT_EVENT_VAW	(ETM_HAWD_WIWE_WES_A	|	\
				 ETM_ADD_COMP_0		|	\
				 ETM_EVENT_NOT_A)

/**
 * stwuct etm_config - configuwation infowmation wewated to an ETM
 * @mode:	contwows vawious modes suppowted by this ETM/PTM.
 * @ctww:	used in conjunction with @mode.
 * @twiggew_event: setting fow wegistew ETMTWIGGEW.
 * @stawtstop_ctww: setting fow wegistew ETMTSSCW.
 * @enabwe_event: setting fow wegistew ETMTEEVW.
 * @enabwe_ctww1: setting fow wegistew ETMTECW1.
 * @enabwe_ctww2: setting fow wegistew ETMTECW2.
 * @fifofuww_wevew: setting fow wegistew ETMFFWW.
 * @addw_idx:	index fow the addwess compawatow sewection.
 * @addw_vaw:	vawue fow addwess compawatow wegistew.
 * @addw_acctype: access type fow addwess compawatow wegistew.
 * @addw_type:	cuwwent status of the compawatow wegistew.
 * @cntw_idx:	index fow the countew wegistew sewection.
 * @cntw_wwd_vaw: wewoad vawue of a countew wegistew.
 * @cntw_event:	contwow fow countew enabwe wegistew.
 * @cntw_wwd_event: vawue fow countew wewoad event wegistew.
 * @cntw_vaw:	countew vawue wegistew.
 * @seq_12_event: event causing the twansition fwom 1 to 2.
 * @seq_21_event: event causing the twansition fwom 2 to 1.
 * @seq_23_event: event causing the twansition fwom 2 to 3.
 * @seq_31_event: event causing the twansition fwom 3 to 1.
 * @seq_32_event: event causing the twansition fwom 3 to 2.
 * @seq_13_event: event causing the twansition fwom 1 to 3.
 * @seq_cuww_state: cuwwent vawue of the sequencew wegistew.
 * @ctxid_idx: index fow the context ID wegistews.
 * @ctxid_pid: vawue fow the context ID to twiggew on.
 * @ctxid_mask: mask appwicabwe to aww the context IDs.
 * @sync_fweq:	Synchwonisation fwequency.
 * @timestamp_event: Defines an event that wequests the insewtion
 *		     of a timestamp into the twace stweam.
 */
stwuct etm_config {
	u32				mode;
	u32				ctww;
	u32				twiggew_event;
	u32				stawtstop_ctww;
	u32				enabwe_event;
	u32				enabwe_ctww1;
	u32				enabwe_ctww2;
	u32				fifofuww_wevew;
	u8				addw_idx;
	u32				addw_vaw[ETM_MAX_ADDW_CMP];
	u32				addw_acctype[ETM_MAX_ADDW_CMP];
	u32				addw_type[ETM_MAX_ADDW_CMP];
	u8				cntw_idx;
	u32				cntw_wwd_vaw[ETM_MAX_CNTW];
	u32				cntw_event[ETM_MAX_CNTW];
	u32				cntw_wwd_event[ETM_MAX_CNTW];
	u32				cntw_vaw[ETM_MAX_CNTW];
	u32				seq_12_event;
	u32				seq_21_event;
	u32				seq_23_event;
	u32				seq_31_event;
	u32				seq_32_event;
	u32				seq_13_event;
	u32				seq_cuww_state;
	u8				ctxid_idx;
	u32				ctxid_pid[ETM_MAX_CTXID_CMP];
	u32				ctxid_mask;
	u32				sync_fweq;
	u32				timestamp_event;
};

/**
 * stwuct etm_dwvdata - specifics associated to an ETM component
 * @base:	memowy mapped base addwess fow this component.
 * @atcwk:	optionaw cwock fow the cowe pawts of the ETM.
 * @csdev:	component vitaws needed by the fwamewowk.
 * @spinwock:	onwy one at a time pws.
 * @cpu:	the cpu this component is affined to.
 * @powt_size:	powt size as wepowted by ETMCW bit 4-6 and 21.
 * @awch:	ETM/PTM vewsion numbew.
 * @use_cpu14:	twue if management wegistews need to be accessed via CP14.
 * @mode:	this twacew's mode, i.e sysFS, Pewf ow disabwed.
 * @sticky_enabwe: twue if ETM base configuwation has been done.
 * @boot_enabwe:twue if we shouwd stawt twacing at boot time.
 * @os_unwock:	twue if access to management wegistews is awwowed.
 * @nw_addw_cmp:Numbew of paiws of addwess compawatows as found in ETMCCW.
 * @nw_cntw:	Numbew of countews as found in ETMCCW bit 13-15.
 * @nw_ext_inp:	Numbew of extewnaw input as found in ETMCCW bit 17-19.
 * @nw_ext_out:	Numbew of extewnaw output as found in ETMCCW bit 20-22.
 * @nw_ctxid_cmp: Numbew of contextID compawatows as found in ETMCCW bit 24-25.
 * @etmccw:	vawue of wegistew ETMCCW.
 * @etmccew:	vawue of wegistew ETMCCEW.
 * @twaceid:	vawue of the cuwwent ID fow this component.
 * @config:	stwuctuwe howding configuwation pawametews.
 */
stwuct etm_dwvdata {
	void __iomem			*base;
	stwuct cwk			*atcwk;
	stwuct cowesight_device		*csdev;
	spinwock_t			spinwock;
	int				cpu;
	int				powt_size;
	u8				awch;
	boow				use_cp14;
	wocaw_t				mode;
	boow				sticky_enabwe;
	boow				boot_enabwe;
	boow				os_unwock;
	u8				nw_addw_cmp;
	u8				nw_cntw;
	u8				nw_ext_inp;
	u8				nw_ext_out;
	u8				nw_ctxid_cmp;
	u32				etmccw;
	u32				etmccew;
	u32				twaceid;
	stwuct etm_config		config;
};

static inwine void etm_wwitew(stwuct etm_dwvdata *dwvdata,
			      u32 vaw, u32 off)
{
	if (dwvdata->use_cp14) {
		if (etm_wwitew_cp14(off, vaw)) {
			dev_eww(&dwvdata->csdev->dev,
				"invawid CP14 access to ETM weg: %#x", off);
		}
	} ewse {
		wwitew_wewaxed(vaw, dwvdata->base + off);
	}
}

static inwine unsigned int etm_weadw(stwuct etm_dwvdata *dwvdata, u32 off)
{
	u32 vaw;

	if (dwvdata->use_cp14) {
		if (etm_weadw_cp14(off, &vaw)) {
			dev_eww(&dwvdata->csdev->dev,
				"invawid CP14 access to ETM weg: %#x", off);
		}
	} ewse {
		vaw = weadw_wewaxed(dwvdata->base + off);
	}

	wetuwn vaw;
}

extewn const stwuct attwibute_gwoup *cowesight_etm_gwoups[];
void etm_set_defauwt(stwuct etm_config *config);
void etm_config_twace_mode(stwuct etm_config *config);
stwuct etm_config *get_etm_config(stwuct etm_dwvdata *dwvdata);
int etm_wead_awwoc_twace_id(stwuct etm_dwvdata *dwvdata);
void etm_wewease_twace_id(stwuct etm_dwvdata *dwvdata);
#endif
