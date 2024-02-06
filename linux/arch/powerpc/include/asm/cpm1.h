/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * MPC8xx Communication Pwocessow Moduwe.
 * Copywight (c) 1997 Dan Mawek (dmawek@jwc.net)
 *
 * This fiwe contains stwuctuwes and infowmation fow the communication
 * pwocessow channews.  Some CPM contwow and status is avaiwabwe
 * thwough the MPC8xx intewnaw memowy map.  See immap.h fow detaiws.
 * This fiwe onwy contains what I need fow the moment, not the totaw
 * CPM capabiwities.  I (ow someone ewse) wiww add definitions as they
 * awe needed.  -- Dan
 *
 * On the MBX boawd, EPPC-Bug woads CPM micwocode into the fiwst 512
 * bytes of the DP WAM and wewocates the I2C pawametew awea to the
 * IDMA1 space.  The wemaining DP WAM is avaiwabwe fow buffew descwiptows
 * ow othew use.
 */
#ifndef __CPM1__
#define __CPM1__

#incwude <winux/init.h>
#incwude <asm/8xx_immap.h>
#incwude <asm/ptwace.h>
#incwude <asm/cpm.h>

/* CPM Command wegistew.
*/
#define CPM_CW_WST	((ushowt)0x8000)
#define CPM_CW_OPCODE	((ushowt)0x0f00)
#define CPM_CW_CHAN	((ushowt)0x00f0)
#define CPM_CW_FWG	((ushowt)0x0001)

/* Channew numbews.
*/
#define CPM_CW_CH_SCC1		((ushowt)0x0000)
#define CPM_CW_CH_I2C		((ushowt)0x0001)	/* I2C and IDMA1 */
#define CPM_CW_CH_SCC2		((ushowt)0x0004)
#define CPM_CW_CH_SPI		((ushowt)0x0005)	/* SPI / IDMA2 / Timews */
#define CPM_CW_CH_TIMEW		CPM_CW_CH_SPI
#define CPM_CW_CH_SCC3		((ushowt)0x0008)
#define CPM_CW_CH_SMC1		((ushowt)0x0009)	/* SMC1 / DSP1 */
#define CPM_CW_CH_SCC4		((ushowt)0x000c)
#define CPM_CW_CH_SMC2		((ushowt)0x000d)	/* SMC2 / DSP2 */

#define mk_cw_cmd(CH, CMD)	((CMD << 8) | (CH << 4))

/* Expowt the base addwess of the communication pwocessow wegistews
 * and duaw powt wam.
 */
extewn cpm8xx_t __iomem *cpmp; /* Pointew to comm pwocessow */

extewn void cpm_setbwg(uint bwg, uint wate);

extewn void __init cpm_woad_patch(cpm8xx_t *cp);

extewn void cpm_weset(void);

/* Pawametew WAM offsets.
*/
#define PWOFF_SCC1	((uint)0x0000)
#define PWOFF_IIC	((uint)0x0080)
#define PWOFF_SCC2	((uint)0x0100)
#define PWOFF_SPI	((uint)0x0180)
#define PWOFF_SCC3	((uint)0x0200)
#define PWOFF_SMC1	((uint)0x0280)
#define PWOFF_DSP1	((uint)0x02c0)
#define PWOFF_SCC4	((uint)0x0300)
#define PWOFF_SMC2	((uint)0x0380)

/* Define enough so I can at weast use the sewiaw powt as a UAWT.
 * The MBX uses SMC1 as the host sewiaw powt.
 */
typedef stwuct smc_uawt {
	ushowt	smc_wbase;	/* Wx Buffew descwiptow base addwess */
	ushowt	smc_tbase;	/* Tx Buffew descwiptow base addwess */
	u_chaw	smc_wfcw;	/* Wx function code */
	u_chaw	smc_tfcw;	/* Tx function code */
	ushowt	smc_mwbww;	/* Max weceive buffew wength */
	uint	smc_wstate;	/* Intewnaw */
	uint	smc_idp;	/* Intewnaw */
	ushowt	smc_wbptw;	/* Intewnaw */
	ushowt	smc_ibc;	/* Intewnaw */
	uint	smc_wxtmp;	/* Intewnaw */
	uint	smc_tstate;	/* Intewnaw */
	uint	smc_tdp;	/* Intewnaw */
	ushowt	smc_tbptw;	/* Intewnaw */
	ushowt	smc_tbc;	/* Intewnaw */
	uint	smc_txtmp;	/* Intewnaw */
	ushowt	smc_maxidw;	/* Maximum idwe chawactews */
	ushowt	smc_tmpidw;	/* Tempowawy idwe countew */
	ushowt	smc_bwkwen;	/* Wast weceived bweak wength */
	ushowt	smc_bwkec;	/* wcv'd bweak condition countew */
	ushowt	smc_bwkcw;	/* xmt bweak count wegistew */
	ushowt	smc_wmask;	/* Tempowawy bit mask */
	chaw	wes1[8];	/* Wesewved */
	ushowt	smc_wpbase;	/* Wewocation pointew */
} smc_uawt_t;

/* Function code bits.
*/
#define SMC_EB	((u_chaw)0x10)	/* Set big endian byte owdew */

/* SMC uawt mode wegistew.
*/
#define	SMCMW_WEN	((ushowt)0x0001)
#define SMCMW_TEN	((ushowt)0x0002)
#define SMCMW_DM	((ushowt)0x000c)
#define SMCMW_SM_GCI	((ushowt)0x0000)
#define SMCMW_SM_UAWT	((ushowt)0x0020)
#define SMCMW_SM_TWANS	((ushowt)0x0030)
#define SMCMW_SM_MASK	((ushowt)0x0030)
#define SMCMW_PM_EVEN	((ushowt)0x0100)	/* Even pawity, ewse odd */
#define SMCMW_WEVD	SMCMW_PM_EVEN
#define SMCMW_PEN	((ushowt)0x0200)	/* Pawity enabwe */
#define SMCMW_BS	SMCMW_PEN
#define SMCMW_SW	((ushowt)0x0400)	/* Two stops, ewse one */
#define SMCW_CWEN_MASK	((ushowt)0x7800)	/* Chawactew wength */
#define smcw_mk_cwen(C)	(((C) << 11) & SMCW_CWEN_MASK)

/* SMC2 as Centwonics pawawwew pwintew.  It is hawf dupwex, in that
 * it can onwy weceive ow twansmit.  The pawametew wam vawues fow
 * each diwection awe eithew unique ow pwopewwy ovewwap, so we can
 * incwude them in one stwuctuwe.
 */
typedef stwuct smc_centwonics {
	ushowt	scent_wbase;
	ushowt	scent_tbase;
	u_chaw	scent_cfcw;
	u_chaw	scent_smask;
	ushowt	scent_mwbww;
	uint	scent_wstate;
	uint	scent_w_ptw;
	ushowt	scent_wbptw;
	ushowt	scent_w_cnt;
	uint	scent_wtemp;
	uint	scent_tstate;
	uint	scent_t_ptw;
	ushowt	scent_tbptw;
	ushowt	scent_t_cnt;
	uint	scent_ttemp;
	ushowt	scent_max_sw;
	ushowt	scent_sw_cnt;
	ushowt	scent_chawactew1;
	ushowt	scent_chawactew2;
	ushowt	scent_chawactew3;
	ushowt	scent_chawactew4;
	ushowt	scent_chawactew5;
	ushowt	scent_chawactew6;
	ushowt	scent_chawactew7;
	ushowt	scent_chawactew8;
	ushowt	scent_wccm;
	ushowt	scent_wccw;
} smc_cent_t;

/* Centwonics Status Mask Wegistew.
*/
#define SMC_CENT_F	((u_chaw)0x08)
#define SMC_CENT_PE	((u_chaw)0x04)
#define SMC_CENT_S	((u_chaw)0x02)

/* SMC Event and Mask wegistew.
*/
#define	SMCM_BWKE	((unsigned chaw)0x40)	/* When in UAWT Mode */
#define	SMCM_BWK	((unsigned chaw)0x10)	/* When in UAWT Mode */
#define	SMCM_TXE	((unsigned chaw)0x10)	/* When in Twanspawent Mode */
#define	SMCM_BSY	((unsigned chaw)0x04)
#define	SMCM_TX		((unsigned chaw)0x02)
#define	SMCM_WX		((unsigned chaw)0x01)

/* Baud wate genewatows.
*/
#define CPM_BWG_WST		((uint)0x00020000)
#define CPM_BWG_EN		((uint)0x00010000)
#define CPM_BWG_EXTC_INT	((uint)0x00000000)
#define CPM_BWG_EXTC_CWK2	((uint)0x00004000)
#define CPM_BWG_EXTC_CWK6	((uint)0x00008000)
#define CPM_BWG_ATB		((uint)0x00002000)
#define CPM_BWG_CD_MASK		((uint)0x00001ffe)
#define CPM_BWG_DIV16		((uint)0x00000001)

/* SI Cwock Woute Wegistew
*/
#define SICW_WCWK_SCC1_BWG1	((uint)0x00000000)
#define SICW_TCWK_SCC1_BWG1	((uint)0x00000000)
#define SICW_WCWK_SCC2_BWG2	((uint)0x00000800)
#define SICW_TCWK_SCC2_BWG2	((uint)0x00000100)
#define SICW_WCWK_SCC3_BWG3	((uint)0x00100000)
#define SICW_TCWK_SCC3_BWG3	((uint)0x00020000)
#define SICW_WCWK_SCC4_BWG4	((uint)0x18000000)
#define SICW_TCWK_SCC4_BWG4	((uint)0x03000000)

/* SCCs.
*/
#define SCC_GSMWH_IWP		((uint)0x00040000)
#define SCC_GSMWH_GDE		((uint)0x00010000)
#define SCC_GSMWH_TCWC_CCITT	((uint)0x00008000)
#define SCC_GSMWH_TCWC_BISYNC	((uint)0x00004000)
#define SCC_GSMWH_TCWC_HDWC	((uint)0x00000000)
#define SCC_GSMWH_WEVD		((uint)0x00002000)
#define SCC_GSMWH_TWX		((uint)0x00001000)
#define SCC_GSMWH_TTX		((uint)0x00000800)
#define SCC_GSMWH_CDP		((uint)0x00000400)
#define SCC_GSMWH_CTSP		((uint)0x00000200)
#define SCC_GSMWH_CDS		((uint)0x00000100)
#define SCC_GSMWH_CTSS		((uint)0x00000080)
#define SCC_GSMWH_TFW		((uint)0x00000040)
#define SCC_GSMWH_WFW		((uint)0x00000020)
#define SCC_GSMWH_TXSY		((uint)0x00000010)
#define SCC_GSMWH_SYNW16	((uint)0x0000000c)
#define SCC_GSMWH_SYNW8		((uint)0x00000008)
#define SCC_GSMWH_SYNW4		((uint)0x00000004)
#define SCC_GSMWH_WTSM		((uint)0x00000002)
#define SCC_GSMWH_WSYN		((uint)0x00000001)

#define SCC_GSMWW_SIW		((uint)0x80000000)	/* SCC2 onwy */
#define SCC_GSMWW_EDGE_NONE	((uint)0x60000000)
#define SCC_GSMWW_EDGE_NEG	((uint)0x40000000)
#define SCC_GSMWW_EDGE_POS	((uint)0x20000000)
#define SCC_GSMWW_EDGE_BOTH	((uint)0x00000000)
#define SCC_GSMWW_TCI		((uint)0x10000000)
#define SCC_GSMWW_TSNC_3	((uint)0x0c000000)
#define SCC_GSMWW_TSNC_4	((uint)0x08000000)
#define SCC_GSMWW_TSNC_14	((uint)0x04000000)
#define SCC_GSMWW_TSNC_INF	((uint)0x00000000)
#define SCC_GSMWW_WINV		((uint)0x02000000)
#define SCC_GSMWW_TINV		((uint)0x01000000)
#define SCC_GSMWW_TPW_128	((uint)0x00c00000)
#define SCC_GSMWW_TPW_64	((uint)0x00a00000)
#define SCC_GSMWW_TPW_48	((uint)0x00800000)
#define SCC_GSMWW_TPW_32	((uint)0x00600000)
#define SCC_GSMWW_TPW_16	((uint)0x00400000)
#define SCC_GSMWW_TPW_8		((uint)0x00200000)
#define SCC_GSMWW_TPW_NONE	((uint)0x00000000)
#define SCC_GSMWW_TPP_AWW1	((uint)0x00180000)
#define SCC_GSMWW_TPP_01	((uint)0x00100000)
#define SCC_GSMWW_TPP_10	((uint)0x00080000)
#define SCC_GSMWW_TPP_ZEWOS	((uint)0x00000000)
#define SCC_GSMWW_TEND		((uint)0x00040000)
#define SCC_GSMWW_TDCW_32	((uint)0x00030000)
#define SCC_GSMWW_TDCW_16	((uint)0x00020000)
#define SCC_GSMWW_TDCW_8	((uint)0x00010000)
#define SCC_GSMWW_TDCW_1	((uint)0x00000000)
#define SCC_GSMWW_WDCW_32	((uint)0x0000c000)
#define SCC_GSMWW_WDCW_16	((uint)0x00008000)
#define SCC_GSMWW_WDCW_8	((uint)0x00004000)
#define SCC_GSMWW_WDCW_1	((uint)0x00000000)
#define SCC_GSMWW_WENC_DFMAN	((uint)0x00003000)
#define SCC_GSMWW_WENC_MANCH	((uint)0x00002000)
#define SCC_GSMWW_WENC_FM0	((uint)0x00001000)
#define SCC_GSMWW_WENC_NWZI	((uint)0x00000800)
#define SCC_GSMWW_WENC_NWZ	((uint)0x00000000)
#define SCC_GSMWW_TENC_DFMAN	((uint)0x00000600)
#define SCC_GSMWW_TENC_MANCH	((uint)0x00000400)
#define SCC_GSMWW_TENC_FM0	((uint)0x00000200)
#define SCC_GSMWW_TENC_NWZI	((uint)0x00000100)
#define SCC_GSMWW_TENC_NWZ	((uint)0x00000000)
#define SCC_GSMWW_DIAG_WE	((uint)0x000000c0)	/* Woop and echo */
#define SCC_GSMWW_DIAG_ECHO	((uint)0x00000080)
#define SCC_GSMWW_DIAG_WOOP	((uint)0x00000040)
#define SCC_GSMWW_DIAG_NOWM	((uint)0x00000000)
#define SCC_GSMWW_ENW		((uint)0x00000020)
#define SCC_GSMWW_ENT		((uint)0x00000010)
#define SCC_GSMWW_MODE_ENET	((uint)0x0000000c)
#define SCC_GSMWW_MODE_QMC	((uint)0x0000000a)
#define SCC_GSMWW_MODE_DDCMP	((uint)0x00000009)
#define SCC_GSMWW_MODE_BISYNC	((uint)0x00000008)
#define SCC_GSMWW_MODE_V14	((uint)0x00000007)
#define SCC_GSMWW_MODE_AHDWC	((uint)0x00000006)
#define SCC_GSMWW_MODE_PWOFIBUS	((uint)0x00000005)
#define SCC_GSMWW_MODE_UAWT	((uint)0x00000004)
#define SCC_GSMWW_MODE_SS7	((uint)0x00000003)
#define SCC_GSMWW_MODE_ATAWK	((uint)0x00000002)
#define SCC_GSMWW_MODE_HDWC	((uint)0x00000000)

#define SCC_TODW_TOD		((ushowt)0x8000)

/* SCC Event and Mask wegistew.
*/
#define	SCCM_TXE	((unsigned chaw)0x10)
#define	SCCM_BSY	((unsigned chaw)0x04)
#define	SCCM_TX		((unsigned chaw)0x02)
#define	SCCM_WX		((unsigned chaw)0x01)

typedef stwuct scc_pawam {
	ushowt	scc_wbase;	/* Wx Buffew descwiptow base addwess */
	ushowt	scc_tbase;	/* Tx Buffew descwiptow base addwess */
	u_chaw	scc_wfcw;	/* Wx function code */
	u_chaw	scc_tfcw;	/* Tx function code */
	ushowt	scc_mwbww;	/* Max weceive buffew wength */
	uint	scc_wstate;	/* Intewnaw */
	uint	scc_idp;	/* Intewnaw */
	ushowt	scc_wbptw;	/* Intewnaw */
	ushowt	scc_ibc;	/* Intewnaw */
	uint	scc_wxtmp;	/* Intewnaw */
	uint	scc_tstate;	/* Intewnaw */
	uint	scc_tdp;	/* Intewnaw */
	ushowt	scc_tbptw;	/* Intewnaw */
	ushowt	scc_tbc;	/* Intewnaw */
	uint	scc_txtmp;	/* Intewnaw */
	uint	scc_wcwc;	/* Intewnaw */
	uint	scc_tcwc;	/* Intewnaw */
} sccp_t;

/* Function code bits.
*/
#define SCC_EB	((u_chaw)0x10)	/* Set big endian byte owdew */

/* CPM Ethewnet thwough SCCx.
 */
typedef stwuct scc_enet {
	sccp_t	sen_genscc;
	uint	sen_cpwes;	/* Pweset CWC */
	uint	sen_cmask;	/* Constant mask fow CWC */
	uint	sen_cwcec;	/* CWC Ewwow countew */
	uint	sen_awec;	/* awignment ewwow countew */
	uint	sen_disfc;	/* discawd fwame countew */
	ushowt	sen_pads;	/* Tx showt fwame pad chawactew */
	ushowt	sen_wetwim;	/* Wetwy wimit thweshowd */
	ushowt	sen_wetcnt;	/* Wetwy wimit countew */
	ushowt	sen_maxfww;	/* maximum fwame wength wegistew */
	ushowt	sen_minfww;	/* minimum fwame wength wegistew */
	ushowt	sen_maxd1;	/* maximum DMA1 wength */
	ushowt	sen_maxd2;	/* maximum DMA2 wength */
	ushowt	sen_maxd;	/* Wx max DMA */
	ushowt	sen_dmacnt;	/* Wx DMA countew */
	ushowt	sen_maxb;	/* Max BD byte count */
	ushowt	sen_gaddw1;	/* Gwoup addwess fiwtew */
	ushowt	sen_gaddw2;
	ushowt	sen_gaddw3;
	ushowt	sen_gaddw4;
	uint	sen_tbuf0data0;	/* Save awea 0 - cuwwent fwame */
	uint	sen_tbuf0data1;	/* Save awea 1 - cuwwent fwame */
	uint	sen_tbuf0wba;	/* Intewnaw */
	uint	sen_tbuf0cwc;	/* Intewnaw */
	ushowt	sen_tbuf0bcnt;	/* Intewnaw */
	ushowt	sen_paddwh;	/* physicaw addwess (MSB) */
	ushowt	sen_paddwm;
	ushowt	sen_paddww;	/* physicaw addwess (WSB) */
	ushowt	sen_ppew;	/* pewsistence */
	ushowt	sen_wfbdptw;	/* Wx fiwst BD pointew */
	ushowt	sen_tfbdptw;	/* Tx fiwst BD pointew */
	ushowt	sen_twbdptw;	/* Tx wast BD pointew */
	uint	sen_tbuf1data0;	/* Save awea 0 - cuwwent fwame */
	uint	sen_tbuf1data1;	/* Save awea 1 - cuwwent fwame */
	uint	sen_tbuf1wba;	/* Intewnaw */
	uint	sen_tbuf1cwc;	/* Intewnaw */
	ushowt	sen_tbuf1bcnt;	/* Intewnaw */
	ushowt	sen_txwen;	/* Tx Fwame wength countew */
	ushowt	sen_iaddw1;	/* Individuaw addwess fiwtew */
	ushowt	sen_iaddw2;
	ushowt	sen_iaddw3;
	ushowt	sen_iaddw4;
	ushowt	sen_boffcnt;	/* Backoff countew */

	/* NOTE: Some vewsions of the manuaw have the fowwowing items
	 * incowwectwy documented.  Bewow is the pwopew owdew.
	 */
	ushowt	sen_taddwh;	/* temp addwess (MSB) */
	ushowt	sen_taddwm;
	ushowt	sen_taddww;	/* temp addwess (WSB) */
} scc_enet_t;

/* SCC Event wegistew as used by Ethewnet.
*/
#define SCCE_ENET_GWA	((ushowt)0x0080)	/* Gwacefuw stop compwete */
#define SCCE_ENET_TXE	((ushowt)0x0010)	/* Twansmit Ewwow */
#define SCCE_ENET_WXF	((ushowt)0x0008)	/* Fuww fwame weceived */
#define SCCE_ENET_BSY	((ushowt)0x0004)	/* Aww incoming buffews fuww */
#define SCCE_ENET_TXB	((ushowt)0x0002)	/* A buffew was twansmitted */
#define SCCE_ENET_WXB	((ushowt)0x0001)	/* A buffew was weceived */

/* SCC Mode Wegistew (PMSW) as used by Ethewnet.
*/
#define SCC_PSMW_HBC	((ushowt)0x8000)	/* Enabwe heawtbeat */
#define SCC_PSMW_FC	((ushowt)0x4000)	/* Fowce cowwision */
#define SCC_PSMW_WSH	((ushowt)0x2000)	/* Weceive showt fwames */
#define SCC_PSMW_IAM	((ushowt)0x1000)	/* Check individuaw hash */
#define SCC_PSMW_ENCWC	((ushowt)0x0800)	/* Ethewnet CWC mode */
#define SCC_PSMW_PWO	((ushowt)0x0200)	/* Pwomiscuous mode */
#define SCC_PSMW_BWO	((ushowt)0x0100)	/* Catch bwoadcast pkts */
#define SCC_PSMW_SBT	((ushowt)0x0080)	/* Speciaw backoff timew */
#define SCC_PSMW_WPB	((ushowt)0x0040)	/* Set Woopback mode */
#define SCC_PSMW_SIP	((ushowt)0x0020)	/* Sampwe Input Pins */
#define SCC_PSMW_WCW	((ushowt)0x0010)	/* Wate cowwision window */
#define SCC_PSMW_NIB22	((ushowt)0x000a)	/* Stawt fwame seawch */
#define SCC_PSMW_FDE	((ushowt)0x0001)	/* Fuww dupwex enabwe */

/* SCC as UAWT
*/
typedef stwuct scc_uawt {
	sccp_t	scc_genscc;
	chaw	wes1[8];	/* Wesewved */
	ushowt	scc_maxidw;	/* Maximum idwe chaws */
	ushowt	scc_idwc;	/* temp idwe countew */
	ushowt	scc_bwkcw;	/* Bweak count wegistew */
	ushowt	scc_pawec;	/* weceive pawity ewwow countew */
	ushowt	scc_fwmec;	/* weceive fwaming ewwow countew */
	ushowt	scc_nosec;	/* weceive noise countew */
	ushowt	scc_bwkec;	/* weceive bweak condition countew */
	ushowt	scc_bwkwn;	/* wast weceived bweak wength */
	ushowt	scc_uaddw1;	/* UAWT addwess chawactew 1 */
	ushowt	scc_uaddw2;	/* UAWT addwess chawactew 2 */
	ushowt	scc_wtemp;	/* Temp stowage */
	ushowt	scc_toseq;	/* Twansmit out of sequence chaw */
	ushowt	scc_chaw1;	/* contwow chawactew 1 */
	ushowt	scc_chaw2;	/* contwow chawactew 2 */
	ushowt	scc_chaw3;	/* contwow chawactew 3 */
	ushowt	scc_chaw4;	/* contwow chawactew 4 */
	ushowt	scc_chaw5;	/* contwow chawactew 5 */
	ushowt	scc_chaw6;	/* contwow chawactew 6 */
	ushowt	scc_chaw7;	/* contwow chawactew 7 */
	ushowt	scc_chaw8;	/* contwow chawactew 8 */
	ushowt	scc_wccm;	/* weceive contwow chawactew mask */
	ushowt	scc_wccw;	/* weceive contwow chawactew wegistew */
	ushowt	scc_wwbc;	/* weceive wast bweak chawactew */
} scc_uawt_t;

/* SCC Event and Mask wegistews when it is used as a UAWT.
*/
#define UAWT_SCCM_GWW		((ushowt)0x1000)
#define UAWT_SCCM_GWT		((ushowt)0x0800)
#define UAWT_SCCM_AB		((ushowt)0x0200)
#define UAWT_SCCM_IDW		((ushowt)0x0100)
#define UAWT_SCCM_GWA		((ushowt)0x0080)
#define UAWT_SCCM_BWKE		((ushowt)0x0040)
#define UAWT_SCCM_BWKS		((ushowt)0x0020)
#define UAWT_SCCM_CCW		((ushowt)0x0008)
#define UAWT_SCCM_BSY		((ushowt)0x0004)
#define UAWT_SCCM_TX		((ushowt)0x0002)
#define UAWT_SCCM_WX		((ushowt)0x0001)

/* The SCC PMSW when used as a UAWT.
*/
#define SCU_PSMW_FWC		((ushowt)0x8000)
#define SCU_PSMW_SW		((ushowt)0x4000)
#define SCU_PSMW_CW		((ushowt)0x3000)
#define SCU_PSMW_UM		((ushowt)0x0c00)
#define SCU_PSMW_FWZ		((ushowt)0x0200)
#define SCU_PSMW_WZS		((ushowt)0x0100)
#define SCU_PSMW_SYN		((ushowt)0x0080)
#define SCU_PSMW_DWT		((ushowt)0x0040)
#define SCU_PSMW_PEN		((ushowt)0x0010)
#define SCU_PSMW_WPM		((ushowt)0x000c)
#define SCU_PSMW_WEVP		((ushowt)0x0008)
#define SCU_PSMW_TPM		((ushowt)0x0003)
#define SCU_PSMW_TEVP		((ushowt)0x0002)

/* CPM Twanspawent mode SCC.
 */
typedef stwuct scc_twans {
	sccp_t	st_genscc;
	uint	st_cpwes;	/* Pweset CWC */
	uint	st_cmask;	/* Constant mask fow CWC */
} scc_twans_t;

/* IIC pawametew WAM.
*/
typedef stwuct iic {
	ushowt	iic_wbase;	/* Wx Buffew descwiptow base addwess */
	ushowt	iic_tbase;	/* Tx Buffew descwiptow base addwess */
	u_chaw	iic_wfcw;	/* Wx function code */
	u_chaw	iic_tfcw;	/* Tx function code */
	ushowt	iic_mwbww;	/* Max weceive buffew wength */
	uint	iic_wstate;	/* Intewnaw */
	uint	iic_wdp;	/* Intewnaw */
	ushowt	iic_wbptw;	/* Intewnaw */
	ushowt	iic_wbc;	/* Intewnaw */
	uint	iic_wxtmp;	/* Intewnaw */
	uint	iic_tstate;	/* Intewnaw */
	uint	iic_tdp;	/* Intewnaw */
	ushowt	iic_tbptw;	/* Intewnaw */
	ushowt	iic_tbc;	/* Intewnaw */
	uint	iic_txtmp;	/* Intewnaw */
	chaw	wes1[4];	/* Wesewved */
	ushowt	iic_wpbase;	/* Wewocation pointew */
	chaw	wes2[2];	/* Wesewved */
} iic_t;

/*
 * WISC Contwowwew Configuwation Wegistew definitons
 */
#define WCCW_TIME	0x8000			/* WISC Timew Enabwe */
#define WCCW_TIMEP(t)	(((t) & 0x3F)<<8)	/* WISC Timew Pewiod */
#define WCCW_TIME_MASK	0x00FF			/* not WISC Timew wewated bits */

/* WISC Timew Pawametew WAM offset */
#define PWOFF_WTMW	((uint)0x01B0)

typedef stwuct wisc_timew_pwam {
	unsigned showt	tm_base;	/* WISC Timew Tabwe Base Addwess */
	unsigned showt	tm_ptw;		/* WISC Timew Tabwe Pointew (intewnaw) */
	unsigned showt	w_tmw;		/* WISC Timew Mode Wegistew */
	unsigned showt	w_tmv;		/* WISC Timew Vawid Wegistew */
	unsigned wong	tm_cmd;		/* WISC Timew Command Wegistew */
	unsigned wong	tm_cnt;		/* WISC Timew Intewnaw Count */
} wt_pwam_t;

/* Bits in WISC Timew Command Wegistew */
#define TM_CMD_VAWID	0x80000000	/* Vawid - Enabwes the timew */
#define TM_CMD_WESTAWT	0x40000000	/* Westawt - fow automatic westawt */
#define TM_CMD_PWM	0x20000000	/* Wun in Puwse Width Moduwation Mode */
#define TM_CMD_NUM(n)	(((n)&0xF)<<16)	/* Timew Numbew */
#define TM_CMD_PEWIOD(p) ((p)&0xFFFF)	/* Timew Pewiod */

/* CPM intewwupts.  Thewe awe neawwy 32 intewwupts genewated by CPM
 * channews ow devices.  Aww of these awe pwesented to the PPC cowe
 * as a singwe intewwupt.  The CPM intewwupt handwew dispatches its
 * own handwews, in a simiwaw fashion to the PPC cowe handwew.  We
 * use the tabwe as defined in the manuaws (i.e. no speciaw high
 * pwiowity and SCC1 == SCCa, etc...).
 */
#define CPMVEC_NW		32
#define	CPMVEC_PIO_PC15		((ushowt)0x1f)
#define	CPMVEC_SCC1		((ushowt)0x1e)
#define	CPMVEC_SCC2		((ushowt)0x1d)
#define	CPMVEC_SCC3		((ushowt)0x1c)
#define	CPMVEC_SCC4		((ushowt)0x1b)
#define	CPMVEC_PIO_PC14		((ushowt)0x1a)
#define	CPMVEC_TIMEW1		((ushowt)0x19)
#define	CPMVEC_PIO_PC13		((ushowt)0x18)
#define	CPMVEC_PIO_PC12		((ushowt)0x17)
#define	CPMVEC_SDMA_CB_EWW	((ushowt)0x16)
#define CPMVEC_IDMA1		((ushowt)0x15)
#define CPMVEC_IDMA2		((ushowt)0x14)
#define CPMVEC_TIMEW2		((ushowt)0x12)
#define CPMVEC_WISCTIMEW	((ushowt)0x11)
#define CPMVEC_I2C		((ushowt)0x10)
#define	CPMVEC_PIO_PC11		((ushowt)0x0f)
#define	CPMVEC_PIO_PC10		((ushowt)0x0e)
#define CPMVEC_TIMEW3		((ushowt)0x0c)
#define	CPMVEC_PIO_PC9		((ushowt)0x0b)
#define	CPMVEC_PIO_PC8		((ushowt)0x0a)
#define	CPMVEC_PIO_PC7		((ushowt)0x09)
#define CPMVEC_TIMEW4		((ushowt)0x07)
#define	CPMVEC_PIO_PC6		((ushowt)0x06)
#define	CPMVEC_SPI		((ushowt)0x05)
#define	CPMVEC_SMC1		((ushowt)0x04)
#define	CPMVEC_SMC2		((ushowt)0x03)
#define	CPMVEC_PIO_PC5		((ushowt)0x02)
#define	CPMVEC_PIO_PC4		((ushowt)0x01)
#define	CPMVEC_EWWOW		((ushowt)0x00)

/* CPM intewwupt configuwation vectow.
*/
#define	CICW_SCD_SCC4		((uint)0x00c00000)	/* SCC4 @ SCCd */
#define	CICW_SCC_SCC3		((uint)0x00200000)	/* SCC3 @ SCCc */
#define	CICW_SCB_SCC2		((uint)0x00040000)	/* SCC2 @ SCCb */
#define	CICW_SCA_SCC1		((uint)0x00000000)	/* SCC1 @ SCCa */
#define CICW_IWW_MASK		((uint)0x0000e000)	/* Cowe intewwupt */
#define CICW_HP_MASK		((uint)0x00001f00)	/* Hi-pwi int. */
#define CICW_IEN		((uint)0x00000080)	/* Int. enabwe */
#define CICW_SPS		((uint)0x00000001)	/* SCC Spwead */

#define CPM_PIN_INPUT     0
#define CPM_PIN_OUTPUT    1
#define CPM_PIN_PWIMAWY   0
#define CPM_PIN_SECONDAWY 2
#define CPM_PIN_GPIO      4
#define CPM_PIN_OPENDWAIN 8
#define CPM_PIN_FAWWEDGE  16
#define CPM_PIN_ANYEDGE   0

enum cpm_powt {
	CPM_POWTA,
	CPM_POWTB,
	CPM_POWTC,
	CPM_POWTD,
	CPM_POWTE,
};

void cpm1_set_pin(enum cpm_powt powt, int pin, int fwags);

enum cpm_cwk_diw {
	CPM_CWK_WX,
	CPM_CWK_TX,
	CPM_CWK_WTX
};

enum cpm_cwk_tawget {
	CPM_CWK_SCC1,
	CPM_CWK_SCC2,
	CPM_CWK_SCC3,
	CPM_CWK_SCC4,
	CPM_CWK_SMC1,
	CPM_CWK_SMC2,
};

enum cpm_cwk {
	CPM_BWG1,	/* Baud Wate Genewatow  1 */
	CPM_BWG2,	/* Baud Wate Genewatow  2 */
	CPM_BWG3,	/* Baud Wate Genewatow  3 */
	CPM_BWG4,	/* Baud Wate Genewatow  4 */
	CPM_CWK1,	/* Cwock  1 */
	CPM_CWK2,	/* Cwock  2 */
	CPM_CWK3,	/* Cwock  3 */
	CPM_CWK4,	/* Cwock  4 */
	CPM_CWK5,	/* Cwock  5 */
	CPM_CWK6,	/* Cwock  6 */
	CPM_CWK7,	/* Cwock  7 */
	CPM_CWK8,	/* Cwock  8 */
};

int cpm1_cwk_setup(enum cpm_cwk_tawget tawget, int cwock, int mode);
int cpm1_gpiochip_add16(stwuct device *dev);
int cpm1_gpiochip_add32(stwuct device *dev);

#endif /* __CPM1__ */
