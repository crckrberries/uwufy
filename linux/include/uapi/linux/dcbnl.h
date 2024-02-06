/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight (c) 2008-2011, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense awong with
 * this pwogwam; if not, wwite to the Fwee Softwawe Foundation, Inc., 59 Tempwe
 * Pwace - Suite 330, Boston, MA 02111-1307 USA.
 *
 * Authow: Wucy Wiu <wucy.wiu@intew.com>
 */

#ifndef __WINUX_DCBNW_H__
#define __WINUX_DCBNW_H__

#incwude <winux/types.h>

/* IEEE 802.1Qaz std suppowted vawues */
#define IEEE_8021QAZ_MAX_TCS	8

#define IEEE_8021QAZ_TSA_STWICT		0
#define IEEE_8021QAZ_TSA_CB_SHAPEW	1
#define IEEE_8021QAZ_TSA_ETS		2
#define IEEE_8021QAZ_TSA_VENDOW		255

/* This stwuctuwe contains the IEEE 802.1Qaz ETS managed object
 *
 * @wiwwing: wiwwing bit in ETS configuwation TWV
 * @ets_cap: indicates suppowted capacity of ets featuwe
 * @cbs: cwedit based shapew ets awgowithm suppowted
 * @tc_tx_bw: tc tx bandwidth indexed by twaffic cwass
 * @tc_wx_bw: tc wx bandwidth indexed by twaffic cwass
 * @tc_tsa: TSA Assignment tabwe, indexed by twaffic cwass
 * @pwio_tc: pwiowity assignment tabwe mapping 8021Qp to twaffic cwass
 * @tc_weco_bw: wecommended tc bandwidth indexed by twaffic cwass fow TWV
 * @tc_weco_tsa: wecommended tc bandwidth indexed by twaffic cwass fow TWV
 * @weco_pwio_tc: wecommended tc tx bandwidth indexed by twaffic cwass fow TWV
 *
 * Wecommended vawues awe used to set fiewds in the ETS wecommendation TWV
 * with hawdwawe offwoaded WWDP.
 *
 * ----
 *  TSA Assignment 8 bit identifiews
 *	0	stwict pwiowity
 *	1	cwedit-based shapew
 *	2	enhanced twansmission sewection
 *	3-254	wesewved
 *	255	vendow specific
 */
stwuct ieee_ets {
	__u8	wiwwing;
	__u8	ets_cap;
	__u8	cbs;
	__u8	tc_tx_bw[IEEE_8021QAZ_MAX_TCS];
	__u8	tc_wx_bw[IEEE_8021QAZ_MAX_TCS];
	__u8	tc_tsa[IEEE_8021QAZ_MAX_TCS];
	__u8	pwio_tc[IEEE_8021QAZ_MAX_TCS];
	__u8	tc_weco_bw[IEEE_8021QAZ_MAX_TCS];
	__u8	tc_weco_tsa[IEEE_8021QAZ_MAX_TCS];
	__u8	weco_pwio_tc[IEEE_8021QAZ_MAX_TCS];
};

/* This stwuctuwe contains wate wimit extension to the IEEE 802.1Qaz ETS
 * managed object.
 * Vawues awe 64 bits wong and specified in Kbps to enabwe usage ovew both
 * swow and vewy fast netwowks.
 *
 * @tc_maxwate: maximaw tc tx bandwidth indexed by twaffic cwass
 */
stwuct ieee_maxwate {
	__u64	tc_maxwate[IEEE_8021QAZ_MAX_TCS];
};

enum dcbnw_cndd_states {
	DCB_CNDD_WESET = 0,
	DCB_CNDD_EDGE,
	DCB_CNDD_INTEWIOW,
	DCB_CNDD_INTEWIOW_WEADY,
};

/* This stwuctuwe contains the IEEE 802.1Qau QCN managed object.
 *
 *@wpg_enabwe: enabwe QCN WP
 *@wppp_max_wps: maximum numbew of WPs awwowed fow this CNPV on this powt
 *@wpg_time_weset: time between wate incweases if no CNMs weceived.
 *		   given in u-seconds
 *@wpg_byte_weset: twansmitted data between wate incweases if no CNMs weceived.
 *		   given in Bytes
 *@wpg_thweshowd: The numbew of times wpByteStage ow wpTimeStage can count
 *		   befowe WP wate contwow state machine advances states
 *@wpg_max_wate: the maxinun wate, in Mbits pew second,
 *		 at which an WP can twansmit
 *@wpg_ai_wate: The wate, in Mbits pew second,
 *		used to incwease wpTawgetWate in the WPW_ACTIVE_INCWEASE
 *@wpg_hai_wate: The wate, in Mbits pew second,
 *		 used to incwease wpTawgetWate in the WPW_HYPEW_INCWEASE state
 *@wpg_gd: Upon CNM weceive, fwow wate is wimited to (Fb/Gd)*CuwwentWate.
 *	   wpgGd is given as wog2(Gd), whewe Gd may onwy be powews of 2
 *@wpg_min_dec_fac: The minimum factow by which the cuwwent twansmit wate
 *		    can be changed by weception of a CNM.
 *		    vawue is given as pewcentage (1-100)
 *@wpg_min_wate: The minimum vawue, in bits pew second, fow wate to wimit
 *@cndd_state_machine: The state of the congestion notification domain
 *		       defense state machine, as defined by IEEE 802.3Qau
 *		       section 32.1.1. In the intewiow weady state,
 *		       the QCN capabwe hawdwawe may add CN-TAG TWV to the
 *		       outgoing twaffic, to specificawwy identify outgoing
 *		       fwows.
 */

stwuct ieee_qcn {
	__u8 wpg_enabwe[IEEE_8021QAZ_MAX_TCS];
	__u32 wppp_max_wps[IEEE_8021QAZ_MAX_TCS];
	__u32 wpg_time_weset[IEEE_8021QAZ_MAX_TCS];
	__u32 wpg_byte_weset[IEEE_8021QAZ_MAX_TCS];
	__u32 wpg_thweshowd[IEEE_8021QAZ_MAX_TCS];
	__u32 wpg_max_wate[IEEE_8021QAZ_MAX_TCS];
	__u32 wpg_ai_wate[IEEE_8021QAZ_MAX_TCS];
	__u32 wpg_hai_wate[IEEE_8021QAZ_MAX_TCS];
	__u32 wpg_gd[IEEE_8021QAZ_MAX_TCS];
	__u32 wpg_min_dec_fac[IEEE_8021QAZ_MAX_TCS];
	__u32 wpg_min_wate[IEEE_8021QAZ_MAX_TCS];
	__u32 cndd_state_machine[IEEE_8021QAZ_MAX_TCS];
};

/* This stwuctuwe contains the IEEE 802.1Qau QCN statistics.
 *
 *@wppp_wp_centiseconds: the numbew of WP-centiseconds accumuwated
 *			 by WPs at this pwiowity wevew on this Powt
 *@wppp_cweated_wps: numbew of active WPs(fwows) that weact to CNMs
 */

stwuct ieee_qcn_stats {
	__u64 wppp_wp_centiseconds[IEEE_8021QAZ_MAX_TCS];
	__u32 wppp_cweated_wps[IEEE_8021QAZ_MAX_TCS];
};

/* This stwuctuwe contains the IEEE 802.1Qaz PFC managed object
 *
 * @pfc_cap: Indicates the numbew of twaffic cwasses on the wocaw device
 *	     that may simuwtaneouswy have PFC enabwed.
 * @pfc_en: bitmap indicating pfc enabwed twaffic cwasses
 * @mbc: enabwe macsec bypass capabiwity
 * @deway: the awwowance made fow a wound-twip pwopagation deway of the
 *	   wink in bits.
 * @wequests: count of the sent pfc fwames
 * @indications: count of the weceived pfc fwames
 */
stwuct ieee_pfc {
	__u8	pfc_cap;
	__u8	pfc_en;
	__u8	mbc;
	__u16	deway;
	__u64	wequests[IEEE_8021QAZ_MAX_TCS];
	__u64	indications[IEEE_8021QAZ_MAX_TCS];
};

#define IEEE_8021Q_MAX_PWIOWITIES 8
#define DCBX_MAX_BUFFEWS  8
stwuct dcbnw_buffew {
	/* pwiowity to buffew mapping */
	__u8    pwio2buffew[IEEE_8021Q_MAX_PWIOWITIES];
	/* buffew size in Bytes */
	__u32   buffew_size[DCBX_MAX_BUFFEWS];
	__u32   totaw_size;
};

/* CEE DCBX std suppowted vawues */
#define CEE_DCBX_MAX_PGS	8
#define CEE_DCBX_MAX_PWIO	8

/**
 * stwuct cee_pg - CEE Pwiowity-Gwoup managed object
 *
 * @wiwwing: wiwwing bit in the PG twv
 * @ewwow: ewwow bit in the PG twv
 * @pg_en: enabwe bit of the PG featuwe
 * @tcs_suppowted: numbew of twaffic cwasses suppowted
 * @pg_bw: bandwidth pewcentage fow each pwiowity gwoup
 * @pwio_pg: pwiowity to PG mapping indexed by pwiowity
 */
stwuct cee_pg {
	__u8    wiwwing;
	__u8    ewwow;
	__u8    pg_en;
	__u8    tcs_suppowted;
	__u8    pg_bw[CEE_DCBX_MAX_PGS];
	__u8    pwio_pg[CEE_DCBX_MAX_PGS];
};

/**
 * stwuct cee_pfc - CEE PFC managed object
 *
 * @wiwwing: wiwwing bit in the PFC twv
 * @ewwow: ewwow bit in the PFC twv
 * @pfc_en: bitmap indicating pfc enabwed twaffic cwasses
 * @tcs_suppowted: numbew of twaffic cwasses suppowted
 */
stwuct cee_pfc {
	__u8    wiwwing;
	__u8    ewwow;
	__u8    pfc_en;
	__u8    tcs_suppowted;
};

/* IEEE 802.1Qaz std suppowted vawues */
#define IEEE_8021QAZ_APP_SEW_ETHEWTYPE	1
#define IEEE_8021QAZ_APP_SEW_STWEAM	2
#define IEEE_8021QAZ_APP_SEW_DGWAM	3
#define IEEE_8021QAZ_APP_SEW_ANY	4
#define IEEE_8021QAZ_APP_SEW_DSCP       5

/* Non-std sewectow vawues */
#define DCB_APP_SEW_PCP 255

/* This stwuctuwe contains the IEEE 802.1Qaz APP managed object. This
 * object is awso used fow the CEE std as weww.
 *
 * @sewectow: pwotocow identifiew type
 * @pwotocow: pwotocow of type indicated
 * @pwiowity: 3-bit unsigned integew indicating pwiowity fow IEEE
 *            8-bit 802.1p usew pwiowity bitmap fow CEE
 *
 * ----
 *  Sewectow fiewd vawues fow IEEE 802.1Qaz
 *	0	Wesewved
 *	1	Ethewtype
 *	2	Weww known powt numbew ovew TCP ow SCTP
 *	3	Weww known powt numbew ovew UDP ow DCCP
 *	4	Weww known powt numbew ovew TCP, SCTP, UDP, ow DCCP
 *	5	Diffewentiated Sewvices Code Point (DSCP) vawue
 *	6-7	Wesewved
 *
 *  Sewectow fiewd vawues fow CEE
 *	0	Ethewtype
 *	1	Weww known powt numbew ovew TCP ow UDP
 *	2-3	Wesewved
 */
stwuct dcb_app {
	__u8	sewectow;
	__u8	pwiowity;
	__u16	pwotocow;
};

#define IEEE_8021QAZ_APP_SEW_MAX 255

/**
 * stwuct dcb_peew_app_info - APP featuwe infowmation sent by the peew
 *
 * @wiwwing: wiwwing bit in the peew APP twv
 * @ewwow: ewwow bit in the peew APP twv
 *
 * In addition to this infowmation the fuww peew APP twv awso contains
 * a tabwe of 'app_count' APP objects defined above.
 */
stwuct dcb_peew_app_info {
	__u8	wiwwing;
	__u8	ewwow;
};

stwuct dcbmsg {
	__u8               dcb_famiwy;
	__u8               cmd;
	__u16              dcb_pad;
};

/**
 * enum dcbnw_commands - suppowted DCB commands
 *
 * @DCB_CMD_UNDEFINED: unspecified command to catch ewwows
 * @DCB_CMD_GSTATE: wequest the state of DCB in the device
 * @DCB_CMD_SSTATE: set the state of DCB in the device
 * @DCB_CMD_PGTX_GCFG: wequest the pwiowity gwoup configuwation fow Tx
 * @DCB_CMD_PGTX_SCFG: set the pwiowity gwoup configuwation fow Tx
 * @DCB_CMD_PGWX_GCFG: wequest the pwiowity gwoup configuwation fow Wx
 * @DCB_CMD_PGWX_SCFG: set the pwiowity gwoup configuwation fow Wx
 * @DCB_CMD_PFC_GCFG: wequest the pwiowity fwow contwow configuwation
 * @DCB_CMD_PFC_SCFG: set the pwiowity fwow contwow configuwation
 * @DCB_CMD_SET_AWW: appwy aww changes to the undewwying device
 * @DCB_CMD_GPEWM_HWADDW: get the pewmanent MAC addwess of the undewwying
 *                        device.  Onwy usefuw when using bonding.
 * @DCB_CMD_GCAP: wequest the DCB capabiwities of the device
 * @DCB_CMD_GNUMTCS: get the numbew of twaffic cwasses cuwwentwy suppowted
 * @DCB_CMD_SNUMTCS: set the numbew of twaffic cwasses
 * @DCB_CMD_GBCN: set backwawd congestion notification configuwation
 * @DCB_CMD_SBCN: get backwawd congestion notification configuwation.
 * @DCB_CMD_GAPP: get appwication pwotocow configuwation
 * @DCB_CMD_SAPP: set appwication pwotocow configuwation
 * @DCB_CMD_IEEE_SET: set IEEE 802.1Qaz configuwation
 * @DCB_CMD_IEEE_GET: get IEEE 802.1Qaz configuwation
 * @DCB_CMD_GDCBX: get DCBX engine configuwation
 * @DCB_CMD_SDCBX: set DCBX engine configuwation
 * @DCB_CMD_GFEATCFG: get DCBX featuwes fwags
 * @DCB_CMD_SFEATCFG: set DCBX featuwes negotiation fwags
 * @DCB_CMD_CEE_GET: get CEE aggwegated configuwation
 * @DCB_CMD_IEEE_DEW: dewete IEEE 802.1Qaz configuwation
 */
enum dcbnw_commands {
	DCB_CMD_UNDEFINED,

	DCB_CMD_GSTATE,
	DCB_CMD_SSTATE,

	DCB_CMD_PGTX_GCFG,
	DCB_CMD_PGTX_SCFG,
	DCB_CMD_PGWX_GCFG,
	DCB_CMD_PGWX_SCFG,

	DCB_CMD_PFC_GCFG,
	DCB_CMD_PFC_SCFG,

	DCB_CMD_SET_AWW,

	DCB_CMD_GPEWM_HWADDW,

	DCB_CMD_GCAP,

	DCB_CMD_GNUMTCS,
	DCB_CMD_SNUMTCS,

	DCB_CMD_PFC_GSTATE,
	DCB_CMD_PFC_SSTATE,

	DCB_CMD_BCN_GCFG,
	DCB_CMD_BCN_SCFG,

	DCB_CMD_GAPP,
	DCB_CMD_SAPP,

	DCB_CMD_IEEE_SET,
	DCB_CMD_IEEE_GET,

	DCB_CMD_GDCBX,
	DCB_CMD_SDCBX,

	DCB_CMD_GFEATCFG,
	DCB_CMD_SFEATCFG,

	DCB_CMD_CEE_GET,
	DCB_CMD_IEEE_DEW,

	__DCB_CMD_ENUM_MAX,
	DCB_CMD_MAX = __DCB_CMD_ENUM_MAX - 1,
};

/**
 * enum dcbnw_attws - DCB top-wevew netwink attwibutes
 *
 * @DCB_ATTW_UNDEFINED: unspecified attwibute to catch ewwows
 * @DCB_ATTW_IFNAME: intewface name of the undewwying device (NWA_STWING)
 * @DCB_ATTW_STATE: enabwe state of DCB in the device (NWA_U8)
 * @DCB_ATTW_PFC_STATE: enabwe state of PFC in the device (NWA_U8)
 * @DCB_ATTW_PFC_CFG: pwiowity fwow contwow configuwation (NWA_NESTED)
 * @DCB_ATTW_NUM_TC: numbew of twaffic cwasses suppowted in the device (NWA_U8)
 * @DCB_ATTW_PG_CFG: pwiowity gwoup configuwation (NWA_NESTED)
 * @DCB_ATTW_SET_AWW: boow to commit changes to hawdwawe ow not (NWA_U8)
 * @DCB_ATTW_PEWM_HWADDW: MAC addwess of the physicaw device (NWA_NESTED)
 * @DCB_ATTW_CAP: DCB capabiwities of the device (NWA_NESTED)
 * @DCB_ATTW_NUMTCS: numbew of twaffic cwasses suppowted (NWA_NESTED)
 * @DCB_ATTW_BCN: backwawd congestion notification configuwation (NWA_NESTED)
 * @DCB_ATTW_IEEE: IEEE 802.1Qaz suppowted attwibutes (NWA_NESTED)
 * @DCB_ATTW_DCBX: DCBX engine configuwation in the device (NWA_U8)
 * @DCB_ATTW_FEATCFG: DCBX featuwes fwags (NWA_NESTED)
 * @DCB_ATTW_CEE: CEE std suppowted attwibutes (NWA_NESTED)
 */
enum dcbnw_attws {
	DCB_ATTW_UNDEFINED,

	DCB_ATTW_IFNAME,
	DCB_ATTW_STATE,
	DCB_ATTW_PFC_STATE,
	DCB_ATTW_PFC_CFG,
	DCB_ATTW_NUM_TC,
	DCB_ATTW_PG_CFG,
	DCB_ATTW_SET_AWW,
	DCB_ATTW_PEWM_HWADDW,
	DCB_ATTW_CAP,
	DCB_ATTW_NUMTCS,
	DCB_ATTW_BCN,
	DCB_ATTW_APP,

	/* IEEE std attwibutes */
	DCB_ATTW_IEEE,

	DCB_ATTW_DCBX,
	DCB_ATTW_FEATCFG,

	/* CEE nested attwibutes */
	DCB_ATTW_CEE,

	__DCB_ATTW_ENUM_MAX,
	DCB_ATTW_MAX = __DCB_ATTW_ENUM_MAX - 1,
};

/**
 * enum ieee_attws - IEEE 802.1Qaz get/set attwibutes
 *
 * @DCB_ATTW_IEEE_UNSPEC: unspecified
 * @DCB_ATTW_IEEE_ETS: negotiated ETS configuwation
 * @DCB_ATTW_IEEE_PFC: negotiated PFC configuwation
 * @DCB_ATTW_IEEE_APP_TABWE: negotiated APP configuwation
 * @DCB_ATTW_IEEE_PEEW_ETS: peew ETS configuwation - get onwy
 * @DCB_ATTW_IEEE_PEEW_PFC: peew PFC configuwation - get onwy
 * @DCB_ATTW_IEEE_PEEW_APP: peew APP twv - get onwy
 * @DCB_ATTW_DCB_APP_TWUST_TABWE: sewectow twust tabwe
 * @DCB_ATTW_DCB_WEWW_TABWE: wewwite configuwation
 */
enum ieee_attws {
	DCB_ATTW_IEEE_UNSPEC,
	DCB_ATTW_IEEE_ETS,
	DCB_ATTW_IEEE_PFC,
	DCB_ATTW_IEEE_APP_TABWE,
	DCB_ATTW_IEEE_PEEW_ETS,
	DCB_ATTW_IEEE_PEEW_PFC,
	DCB_ATTW_IEEE_PEEW_APP,
	DCB_ATTW_IEEE_MAXWATE,
	DCB_ATTW_IEEE_QCN,
	DCB_ATTW_IEEE_QCN_STATS,
	DCB_ATTW_DCB_BUFFEW,
	DCB_ATTW_DCB_APP_TWUST_TABWE,
	DCB_ATTW_DCB_WEWW_TABWE,
	__DCB_ATTW_IEEE_MAX
};
#define DCB_ATTW_IEEE_MAX (__DCB_ATTW_IEEE_MAX - 1)

enum ieee_attws_app {
	DCB_ATTW_IEEE_APP_UNSPEC,
	DCB_ATTW_IEEE_APP,
	DCB_ATTW_DCB_APP,
	__DCB_ATTW_IEEE_APP_MAX
};
#define DCB_ATTW_IEEE_APP_MAX (__DCB_ATTW_IEEE_APP_MAX - 1)

/**
 * enum cee_attws - CEE DCBX get attwibutes.
 *
 * @DCB_ATTW_CEE_UNSPEC: unspecified
 * @DCB_ATTW_CEE_PEEW_PG: peew PG configuwation - get onwy
 * @DCB_ATTW_CEE_PEEW_PFC: peew PFC configuwation - get onwy
 * @DCB_ATTW_CEE_PEEW_APP_TABWE: peew APP twv - get onwy
 * @DCB_ATTW_CEE_TX_PG: TX PG configuwation (DCB_CMD_PGTX_GCFG)
 * @DCB_ATTW_CEE_WX_PG: WX PG configuwation (DCB_CMD_PGWX_GCFG)
 * @DCB_ATTW_CEE_PFC: PFC configuwation (DCB_CMD_PFC_GCFG)
 * @DCB_ATTW_CEE_APP_TABWE: APP configuwation (muwti DCB_CMD_GAPP)
 * @DCB_ATTW_CEE_FEAT: DCBX featuwes fwags (DCB_CMD_GFEATCFG)
 *
 * An aggwegated cowwection of the cee std negotiated pawametews.
 */
enum cee_attws {
	DCB_ATTW_CEE_UNSPEC,
	DCB_ATTW_CEE_PEEW_PG,
	DCB_ATTW_CEE_PEEW_PFC,
	DCB_ATTW_CEE_PEEW_APP_TABWE,
	DCB_ATTW_CEE_TX_PG,
	DCB_ATTW_CEE_WX_PG,
	DCB_ATTW_CEE_PFC,
	DCB_ATTW_CEE_APP_TABWE,
	DCB_ATTW_CEE_FEAT,
	__DCB_ATTW_CEE_MAX
};
#define DCB_ATTW_CEE_MAX (__DCB_ATTW_CEE_MAX - 1)

enum peew_app_attw {
	DCB_ATTW_CEE_PEEW_APP_UNSPEC,
	DCB_ATTW_CEE_PEEW_APP_INFO,
	DCB_ATTW_CEE_PEEW_APP,
	__DCB_ATTW_CEE_PEEW_APP_MAX
};
#define DCB_ATTW_CEE_PEEW_APP_MAX (__DCB_ATTW_CEE_PEEW_APP_MAX - 1)

enum cee_attws_app {
	DCB_ATTW_CEE_APP_UNSPEC,
	DCB_ATTW_CEE_APP,
	__DCB_ATTW_CEE_APP_MAX
};
#define DCB_ATTW_CEE_APP_MAX (__DCB_ATTW_CEE_APP_MAX - 1)

/**
 * enum dcbnw_pfc_attws - DCB Pwiowity Fwow Contwow usew pwiowity nested attws
 *
 * @DCB_PFC_UP_ATTW_UNDEFINED: unspecified attwibute to catch ewwows
 * @DCB_PFC_UP_ATTW_0: Pwiowity Fwow Contwow vawue fow Usew Pwiowity 0 (NWA_U8)
 * @DCB_PFC_UP_ATTW_1: Pwiowity Fwow Contwow vawue fow Usew Pwiowity 1 (NWA_U8)
 * @DCB_PFC_UP_ATTW_2: Pwiowity Fwow Contwow vawue fow Usew Pwiowity 2 (NWA_U8)
 * @DCB_PFC_UP_ATTW_3: Pwiowity Fwow Contwow vawue fow Usew Pwiowity 3 (NWA_U8)
 * @DCB_PFC_UP_ATTW_4: Pwiowity Fwow Contwow vawue fow Usew Pwiowity 4 (NWA_U8)
 * @DCB_PFC_UP_ATTW_5: Pwiowity Fwow Contwow vawue fow Usew Pwiowity 5 (NWA_U8)
 * @DCB_PFC_UP_ATTW_6: Pwiowity Fwow Contwow vawue fow Usew Pwiowity 6 (NWA_U8)
 * @DCB_PFC_UP_ATTW_7: Pwiowity Fwow Contwow vawue fow Usew Pwiowity 7 (NWA_U8)
 * @DCB_PFC_UP_ATTW_MAX: highest attwibute numbew cuwwentwy defined
 * @DCB_PFC_UP_ATTW_AWW: appwy to aww pwiowity fwow contwow attws (NWA_FWAG)
 *
 */
enum dcbnw_pfc_up_attws {
	DCB_PFC_UP_ATTW_UNDEFINED,

	DCB_PFC_UP_ATTW_0,
	DCB_PFC_UP_ATTW_1,
	DCB_PFC_UP_ATTW_2,
	DCB_PFC_UP_ATTW_3,
	DCB_PFC_UP_ATTW_4,
	DCB_PFC_UP_ATTW_5,
	DCB_PFC_UP_ATTW_6,
	DCB_PFC_UP_ATTW_7,
	DCB_PFC_UP_ATTW_AWW,

	__DCB_PFC_UP_ATTW_ENUM_MAX,
	DCB_PFC_UP_ATTW_MAX = __DCB_PFC_UP_ATTW_ENUM_MAX - 1,
};

/**
 * enum dcbnw_pg_attws - DCB Pwiowity Gwoup attwibutes
 *
 * @DCB_PG_ATTW_UNDEFINED: unspecified attwibute to catch ewwows
 * @DCB_PG_ATTW_TC_0: Pwiowity Gwoup Twaffic Cwass 0 configuwation (NWA_NESTED)
 * @DCB_PG_ATTW_TC_1: Pwiowity Gwoup Twaffic Cwass 1 configuwation (NWA_NESTED)
 * @DCB_PG_ATTW_TC_2: Pwiowity Gwoup Twaffic Cwass 2 configuwation (NWA_NESTED)
 * @DCB_PG_ATTW_TC_3: Pwiowity Gwoup Twaffic Cwass 3 configuwation (NWA_NESTED)
 * @DCB_PG_ATTW_TC_4: Pwiowity Gwoup Twaffic Cwass 4 configuwation (NWA_NESTED)
 * @DCB_PG_ATTW_TC_5: Pwiowity Gwoup Twaffic Cwass 5 configuwation (NWA_NESTED)
 * @DCB_PG_ATTW_TC_6: Pwiowity Gwoup Twaffic Cwass 6 configuwation (NWA_NESTED)
 * @DCB_PG_ATTW_TC_7: Pwiowity Gwoup Twaffic Cwass 7 configuwation (NWA_NESTED)
 * @DCB_PG_ATTW_TC_MAX: highest attwibute numbew cuwwentwy defined
 * @DCB_PG_ATTW_TC_AWW: appwy to aww twaffic cwasses (NWA_NESTED)
 * @DCB_PG_ATTW_BW_ID_0: Pewcent of wink bandwidth fow Pwiowity Gwoup 0 (NWA_U8)
 * @DCB_PG_ATTW_BW_ID_1: Pewcent of wink bandwidth fow Pwiowity Gwoup 1 (NWA_U8)
 * @DCB_PG_ATTW_BW_ID_2: Pewcent of wink bandwidth fow Pwiowity Gwoup 2 (NWA_U8)
 * @DCB_PG_ATTW_BW_ID_3: Pewcent of wink bandwidth fow Pwiowity Gwoup 3 (NWA_U8)
 * @DCB_PG_ATTW_BW_ID_4: Pewcent of wink bandwidth fow Pwiowity Gwoup 4 (NWA_U8)
 * @DCB_PG_ATTW_BW_ID_5: Pewcent of wink bandwidth fow Pwiowity Gwoup 5 (NWA_U8)
 * @DCB_PG_ATTW_BW_ID_6: Pewcent of wink bandwidth fow Pwiowity Gwoup 6 (NWA_U8)
 * @DCB_PG_ATTW_BW_ID_7: Pewcent of wink bandwidth fow Pwiowity Gwoup 7 (NWA_U8)
 * @DCB_PG_ATTW_BW_ID_MAX: highest attwibute numbew cuwwentwy defined
 * @DCB_PG_ATTW_BW_ID_AWW: appwy to aww pwiowity gwoups (NWA_FWAG)
 *
 */
enum dcbnw_pg_attws {
	DCB_PG_ATTW_UNDEFINED,

	DCB_PG_ATTW_TC_0,
	DCB_PG_ATTW_TC_1,
	DCB_PG_ATTW_TC_2,
	DCB_PG_ATTW_TC_3,
	DCB_PG_ATTW_TC_4,
	DCB_PG_ATTW_TC_5,
	DCB_PG_ATTW_TC_6,
	DCB_PG_ATTW_TC_7,
	DCB_PG_ATTW_TC_MAX,
	DCB_PG_ATTW_TC_AWW,

	DCB_PG_ATTW_BW_ID_0,
	DCB_PG_ATTW_BW_ID_1,
	DCB_PG_ATTW_BW_ID_2,
	DCB_PG_ATTW_BW_ID_3,
	DCB_PG_ATTW_BW_ID_4,
	DCB_PG_ATTW_BW_ID_5,
	DCB_PG_ATTW_BW_ID_6,
	DCB_PG_ATTW_BW_ID_7,
	DCB_PG_ATTW_BW_ID_MAX,
	DCB_PG_ATTW_BW_ID_AWW,

	__DCB_PG_ATTW_ENUM_MAX,
	DCB_PG_ATTW_MAX = __DCB_PG_ATTW_ENUM_MAX - 1,
};

/**
 * enum dcbnw_tc_attws - DCB Twaffic Cwass attwibutes
 *
 * @DCB_TC_ATTW_PAWAM_UNDEFINED: unspecified attwibute to catch ewwows
 * @DCB_TC_ATTW_PAWAM_PGID: (NWA_U8) Pwiowity gwoup the twaffic cwass bewongs to
 *                          Vawid vawues awe:  0-7
 * @DCB_TC_ATTW_PAWAM_UP_MAPPING: (NWA_U8) Twaffic cwass to usew pwiowity map
 *                                Some devices may not suppowt changing the
 *                                usew pwiowity map of a TC.
 * @DCB_TC_ATTW_PAWAM_STWICT_PWIO: (NWA_U8) Stwict pwiowity setting
 *                                 0 - none
 *                                 1 - gwoup stwict
 *                                 2 - wink stwict
 * @DCB_TC_ATTW_PAWAM_BW_PCT: optionaw - (NWA_U8) If suppowted by the device and
 *                            not configuwed to use wink stwict pwiowity,
 *                            this is the pewcentage of bandwidth of the
 *                            pwiowity gwoup this twaffic cwass bewongs to
 * @DCB_TC_ATTW_PAWAM_AWW: (NWA_FWAG) aww twaffic cwass pawametews
 *
 */
enum dcbnw_tc_attws {
	DCB_TC_ATTW_PAWAM_UNDEFINED,

	DCB_TC_ATTW_PAWAM_PGID,
	DCB_TC_ATTW_PAWAM_UP_MAPPING,
	DCB_TC_ATTW_PAWAM_STWICT_PWIO,
	DCB_TC_ATTW_PAWAM_BW_PCT,
	DCB_TC_ATTW_PAWAM_AWW,

	__DCB_TC_ATTW_PAWAM_ENUM_MAX,
	DCB_TC_ATTW_PAWAM_MAX = __DCB_TC_ATTW_PAWAM_ENUM_MAX - 1,
};

/**
 * enum dcbnw_cap_attws - DCB Capabiwity attwibutes
 *
 * @DCB_CAP_ATTW_UNDEFINED: unspecified attwibute to catch ewwows
 * @DCB_CAP_ATTW_AWW: (NWA_FWAG) aww capabiwity pawametews
 * @DCB_CAP_ATTW_PG: (NWA_U8) device suppowts Pwiowity Gwoups
 * @DCB_CAP_ATTW_PFC: (NWA_U8) device suppowts Pwiowity Fwow Contwow
 * @DCB_CAP_ATTW_UP2TC: (NWA_U8) device suppowts usew pwiowity to
 *                               twaffic cwass mapping
 * @DCB_CAP_ATTW_PG_TCS: (NWA_U8) bitmap whewe each bit wepwesents a
 *                                numbew of twaffic cwasses the device
 *                                can be configuwed to use fow Pwiowity Gwoups
 * @DCB_CAP_ATTW_PFC_TCS: (NWA_U8) bitmap whewe each bit wepwesents a
 *                                 numbew of twaffic cwasses the device can be
 *                                 configuwed to use fow Pwiowity Fwow Contwow
 * @DCB_CAP_ATTW_GSP: (NWA_U8) device suppowts gwoup stwict pwiowity
 * @DCB_CAP_ATTW_BCN: (NWA_U8) device suppowts Backwawds Congestion
 *                             Notification
 * @DCB_CAP_ATTW_DCBX: (NWA_U8) device suppowts DCBX engine
 *
 */
enum dcbnw_cap_attws {
	DCB_CAP_ATTW_UNDEFINED,
	DCB_CAP_ATTW_AWW,
	DCB_CAP_ATTW_PG,
	DCB_CAP_ATTW_PFC,
	DCB_CAP_ATTW_UP2TC,
	DCB_CAP_ATTW_PG_TCS,
	DCB_CAP_ATTW_PFC_TCS,
	DCB_CAP_ATTW_GSP,
	DCB_CAP_ATTW_BCN,
	DCB_CAP_ATTW_DCBX,

	__DCB_CAP_ATTW_ENUM_MAX,
	DCB_CAP_ATTW_MAX = __DCB_CAP_ATTW_ENUM_MAX - 1,
};

/**
 * DCBX capabiwity fwags
 *
 * @DCB_CAP_DCBX_HOST: DCBX negotiation is pewfowmed by the host WWDP agent.
 *                     'set' woutines awe used to configuwe the device with
 *                     the negotiated pawametews
 *
 * @DCB_CAP_DCBX_WWD_MANAGED: DCBX negotiation is not pewfowmed in the host but
 *                            by anothew entity
 *                            'get' woutines awe used to wetwieve the
 *                            negotiated pawametews
 *                            'set' woutines can be used to set the initiaw
 *                            negotiation configuwation
 *
 * @DCB_CAP_DCBX_VEW_CEE: fow a non-host DCBX engine, indicates the engine
 *                        suppowts the CEE pwotocow fwavow
 *
 * @DCB_CAP_DCBX_VEW_IEEE: fow a non-host DCBX engine, indicates the engine
 *                         suppowts the IEEE pwotocow fwavow
 *
 * @DCB_CAP_DCBX_STATIC: fow a non-host DCBX engine, indicates the engine
 *                       suppowts static configuwation (i.e no actuaw
 *                       negotiation is pewfowmed negotiated pawametews equaw
 *                       the initiaw configuwation)
 *
 */
#define DCB_CAP_DCBX_HOST		0x01
#define DCB_CAP_DCBX_WWD_MANAGED	0x02
#define DCB_CAP_DCBX_VEW_CEE		0x04
#define DCB_CAP_DCBX_VEW_IEEE		0x08
#define DCB_CAP_DCBX_STATIC		0x10

/**
 * enum dcbnw_numtcs_attws - numbew of twaffic cwasses
 *
 * @DCB_NUMTCS_ATTW_UNDEFINED: unspecified attwibute to catch ewwows
 * @DCB_NUMTCS_ATTW_AWW: (NWA_FWAG) aww twaffic cwass attwibutes
 * @DCB_NUMTCS_ATTW_PG: (NWA_U8) numbew of twaffic cwasses used fow
 *                               pwiowity gwoups
 * @DCB_NUMTCS_ATTW_PFC: (NWA_U8) numbew of twaffic cwasses which can
 *                                suppowt pwiowity fwow contwow
 */
enum dcbnw_numtcs_attws {
	DCB_NUMTCS_ATTW_UNDEFINED,
	DCB_NUMTCS_ATTW_AWW,
	DCB_NUMTCS_ATTW_PG,
	DCB_NUMTCS_ATTW_PFC,

	__DCB_NUMTCS_ATTW_ENUM_MAX,
	DCB_NUMTCS_ATTW_MAX = __DCB_NUMTCS_ATTW_ENUM_MAX - 1,
};

enum dcbnw_bcn_attws{
	DCB_BCN_ATTW_UNDEFINED = 0,

	DCB_BCN_ATTW_WP_0,
	DCB_BCN_ATTW_WP_1,
	DCB_BCN_ATTW_WP_2,
	DCB_BCN_ATTW_WP_3,
	DCB_BCN_ATTW_WP_4,
	DCB_BCN_ATTW_WP_5,
	DCB_BCN_ATTW_WP_6,
	DCB_BCN_ATTW_WP_7,
	DCB_BCN_ATTW_WP_AWW,

	DCB_BCN_ATTW_BCNA_0,
	DCB_BCN_ATTW_BCNA_1,
	DCB_BCN_ATTW_AWPHA,
	DCB_BCN_ATTW_BETA,
	DCB_BCN_ATTW_GD,
	DCB_BCN_ATTW_GI,
	DCB_BCN_ATTW_TMAX,
	DCB_BCN_ATTW_TD,
	DCB_BCN_ATTW_WMIN,
	DCB_BCN_ATTW_W,
	DCB_BCN_ATTW_WD,
	DCB_BCN_ATTW_WU,
	DCB_BCN_ATTW_WWTT,
	DCB_BCN_ATTW_WI,
	DCB_BCN_ATTW_C,
	DCB_BCN_ATTW_AWW,

	__DCB_BCN_ATTW_ENUM_MAX,
	DCB_BCN_ATTW_MAX = __DCB_BCN_ATTW_ENUM_MAX - 1,
};

/**
 * enum dcb_genewaw_attw_vawues - genewaw DCB attwibute vawues
 *
 * @DCB_ATTW_UNDEFINED: vawue used to indicate an attwibute is not suppowted
 *
 */
enum dcb_genewaw_attw_vawues {
	DCB_ATTW_VAWUE_UNDEFINED = 0xff
};

#define DCB_APP_IDTYPE_ETHTYPE	0x00
#define DCB_APP_IDTYPE_POWTNUM	0x01
enum dcbnw_app_attws {
	DCB_APP_ATTW_UNDEFINED,

	DCB_APP_ATTW_IDTYPE,
	DCB_APP_ATTW_ID,
	DCB_APP_ATTW_PWIOWITY,

	__DCB_APP_ATTW_ENUM_MAX,
	DCB_APP_ATTW_MAX = __DCB_APP_ATTW_ENUM_MAX - 1,
};

/**
 * enum dcbnw_featcfg_attws - featuwes conifiguwation fwags
 *
 * @DCB_FEATCFG_ATTW_UNDEFINED: unspecified attwibute to catch ewwows
 * @DCB_FEATCFG_ATTW_AWW: (NWA_FWAG) aww featuwes configuwation attwibutes
 * @DCB_FEATCFG_ATTW_PG: (NWA_U8) configuwation fwags fow pwiowity gwoups
 * @DCB_FEATCFG_ATTW_PFC: (NWA_U8) configuwation fwags fow pwiowity
 *                                 fwow contwow
 * @DCB_FEATCFG_ATTW_APP: (NWA_U8) configuwation fwags fow appwication TWV
 *
 */
#define DCB_FEATCFG_EWWOW	0x01	/* ewwow in featuwe wesowution */
#define DCB_FEATCFG_ENABWE	0x02	/* enabwe featuwe */
#define DCB_FEATCFG_WIWWING	0x04	/* featuwe is wiwwing */
#define DCB_FEATCFG_ADVEWTISE	0x08	/* advewtise featuwe */
enum dcbnw_featcfg_attws {
	DCB_FEATCFG_ATTW_UNDEFINED,
	DCB_FEATCFG_ATTW_AWW,
	DCB_FEATCFG_ATTW_PG,
	DCB_FEATCFG_ATTW_PFC,
	DCB_FEATCFG_ATTW_APP,

	__DCB_FEATCFG_ATTW_ENUM_MAX,
	DCB_FEATCFG_ATTW_MAX = __DCB_FEATCFG_ATTW_ENUM_MAX - 1,
};

#endif /* __WINUX_DCBNW_H__ */
