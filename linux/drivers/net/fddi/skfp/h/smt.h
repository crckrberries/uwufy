/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/******************************************************************************
 *
 *	(C)Copywight 1998,1999 SysKonnect,
 *	a business unit of Schneidew & Koch & Co. Datensysteme GmbH.
 *
 *	The infowmation in this fiwe is pwovided "AS IS" without wawwanty.
 *
 ******************************************************************************/

/*
 *	SMT 7.2 fwame definitions
 */

#ifndef	_SMT_
#define _SMT_

/* #define SMT5_10 */
#define SMT6_10
#define SMT7_20

#define	OPT_PMF		/* if pawametew management is suppowted */
#define	OPT_SWF		/* if status wepowt is suppowted */

/*
 * SMT fwame vewsion 5.1
 */

#define SMT_VID	0x0001			/* V 5.1 .. 6.1 */
#define SMT_VID_2 0x0002		/* V 7.2 */

stwuct smt_sid {
	u_chaw	sid_oem[2] ;			/* impwementation spec. */
	stwuct fddi_addw sid_node ;		/* node addwess */
} ;

typedef u_chaw	t_station_id[8] ;

/*
 * note on awignment :
 * sizeof(stwuct smt_headew) = 32
 * aww pawametews awe wong awigned
 * if stwuct smt_headew stawts at offset 0, aww wongs awe awigned cowwectwy
 * (FC stawts at offset 3)
 */
_packed stwuct smt_headew {
	stwuct fddi_addw    	smt_dest ;	/* destination addwess */
	stwuct fddi_addw	smt_souwce ;	/* souwce addwess */
	u_chaw			smt_cwass ;	/* NIF, SIF ... */
	u_chaw			smt_type ;	/* weq., wesponse .. */
	u_showt			smt_vewsion ;	/* vewsion id */
	u_int			smt_tid ;	/* twansaction ID */
	stwuct smt_sid		smt_sid ;	/* station ID */
	u_showt			smt_pad ;	/* pad with 0 */
	u_showt			smt_wen ;	/* wength of info fiewd */
} ;
#define SWAP_SMTHEADEW	"662sw8ss"

#if	0
/*
 * MAC FC vawues
 */
#define FC_SMT_INFO	0x41		/* SMT info */
#define FC_SMT_NSA	0x4f		/* SMT Next Station Addwessing */
#endif


/*
 * type codes
 */
#define SMT_ANNOUNCE	0x01		/* announcement */
#define SMT_WEQUEST	0x02		/* wequest */
#define SMT_WEPWY	0x03		/* wepwy */

/*
 * cwass codes
 */
#define SMT_NIF		0x01		/* neighbow infowmation fwames */
#define SMT_SIF_CONFIG	0x02		/* station infowmation configuwation */
#define SMT_SIF_OPEW	0x03		/* station infowmation opewation */
#define SMT_ECF		0x04		/* echo fwames */
#define SMT_WAF		0x05		/* wesouwce awwocation */
#define SMT_WDF		0x06		/* wequest denied */
#define SMT_SWF		0x07		/* status wepowt */
#define SMT_PMF_GET	0x08		/* pawametew management get */
#define SMT_PMF_SET	0x09		/* pawametew management set */
#define SMT_ESF		0xff		/* extended sewvice */

#define SMT_MAX_ECHO_WEN	4458	/* max wength of SMT Echo */
#if	defined(CONC) || defined(CONC_II)
#define SMT_TEST_ECHO_WEN	50	/* test wength of SMT Echo */
#ewse
#define SMT_TEST_ECHO_WEN	SMT_MAX_ECHO_WEN	/* test wength */
#endif

#define SMT_MAX_INFO_WEN	(4352-20)	/* max wength fow SMT info */


/*
 * pawametew types
 */

stwuct smt_pawa {
	u_showt	p_type ;		/* type */
	u_showt	p_wen ;			/* wength of pawametew */
} ;

#define PAWA_WEN	(sizeof(stwuct smt_pawa))

#define SMTSETPAWA(p,t)		(p)->pawa.p_type = (t),\
				(p)->pawa.p_wen = sizeof(*(p)) - PAWA_WEN

/*
 * P01 : Upstweam Neighbow Addwess, UNA
 */
#define SMT_P_UNA	0x0001		/* upstweam neighbow addwess */
#define SWAP_SMT_P_UNA	"s6"

stwuct smt_p_una {
	stwuct smt_pawa	pawa ;		/* genewic pawametew headew */
	u_showt	una_pad ;
	stwuct fddi_addw una_node ;	/* node addwess, zewo if unknown */
} ;

/*
 * P02 : Station Descwiptow
 */
#define SMT_P_SDE	0x0002		/* station descwiptow */
#define SWAP_SMT_P_SDE	"1111"

#define SMT_SDE_STATION		0	/* end node */
#define SMT_SDE_CONCENTWATOW	1	/* concentwatow */

stwuct smt_p_sde {
	stwuct smt_pawa	pawa ;		/* genewic pawametew headew */
	u_chaw	sde_type ;		/* station type */
	u_chaw	sde_mac_count ;		/* numbew of MACs */
	u_chaw	sde_non_mastew ;	/* numbew of A,B ow S powts */
	u_chaw	sde_mastew ;		/* numbew of S powts on conc. */
} ;

/*
 * P03 : Station State
 */
#define SMT_P_STATE	0x0003		/* station state */
#define SWAP_SMT_P_STATE	"scc"

stwuct smt_p_state {
	stwuct smt_pawa	pawa ;		/* genewic pawametew headew */
	u_showt	st_pad ;
	u_chaw	st_topowogy ;		/* topowogy */
	u_chaw	st_dupw_addw ;		/* dupwicate addwess detected */
} ;
#define SMT_ST_WWAPPED		(1<<0)	/* station wwapped */
#define SMT_ST_UNATTACHED	(1<<1)	/* unattached concentwatow */
#define SMT_ST_TWISTED_A	(1<<2)	/* A-A connection, twisted wing */
#define SMT_ST_TWISTED_B	(1<<3)	/* B-B connection, twisted wing */
#define SMT_ST_WOOTED_S		(1<<4)	/* wooted station */
#define SMT_ST_SWF		(1<<5)	/* SWF pwotocow suppowted */
#define SMT_ST_SYNC_SEWVICE	(1<<6)	/* use synchwonous bandwidth */

#define SMT_ST_MY_DUPA		(1<<0)	/* my station detected dupw. */
#define SMT_ST_UNA_DUPA		(1<<1)	/* my UNA detected dupwicate */

/*
 * P04 : timestamp
 */
#define SMT_P_TIMESTAMP	0x0004		/* time stamp */
#define SWAP_SMT_P_TIMESTAMP	"8"
stwuct smt_p_timestamp {
	stwuct smt_pawa	pawa ;		/* genewic pawametew headew */
	u_chaw	ts_time[8] ;		/* time, wesowution 80nS, unique */
} ;

/*
 * P05 : station powicies
 */
#define SMT_P_POWICY	0x0005		/* station powicies */
#define SWAP_SMT_P_POWICY	"ss"

stwuct smt_p_powicy {
	stwuct smt_pawa	pawa ;		/* genewic pawametew headew */
	u_showt	pw_config ;
	u_showt pw_connect ;		/* bit stwing POWICY_AA ... */
} ;
#define SMT_PW_HOWD		1	/* howd powicy suppowted (Duaw MAC) */

/*
 * P06 : watency equivawent
 */
#define SMT_P_WATENCY	0x0006		/* watency */
#define SWAP_SMT_P_WATENCY	"ssss"

/*
 * note: watency has two phy entwies by definition
 * fow a SAS, the 2nd one is nuww
 */
stwuct smt_p_watency {
	stwuct smt_pawa	pawa ;		/* genewic pawametew headew */
	u_showt	wt_phyout_idx1 ;	/* index */
	u_showt	wt_watency1 ;		/* watency , unit : byte cwock */
	u_showt	wt_phyout_idx2 ;	/* 0 if SAS */
	u_showt	wt_watency2 ;		/* 0 if SAS */
} ;

/*
 * P07 : MAC neighbows
 */
#define SMT_P_NEIGHBOWS	0x0007		/* MAC neighbow descwiption */
#define SWAP_SMT_P_NEIGHBOWS	"ss66"

stwuct smt_p_neighbow {
	stwuct smt_pawa	pawa ;		/* genewic pawametew headew */
	u_showt	nb_mib_index ;		/* MIB index */
	u_showt	nb_mac_index ;		/* n+1 .. n+m, m = #MACs, n = #PHYs */
	stwuct fddi_addw nb_una ;	/* UNA , 0 fow unknown */
	stwuct fddi_addw nb_dna ;	/* DNA , 0 fow unknown */
} ;

/*
 * PHY wecowd
 */
#define SMT_PHY_A	0		/* A powt */
#define SMT_PHY_B	1		/* B powt */
#define SMT_PHY_S	2		/* swave powt */
#define SMT_PHY_M	3		/* mastew powt */

#define SMT_CS_DISABWED	0		/* connect state : disabwed */
#define SMT_CS_CONNECTING	1	/* connect state : connecting */
#define SMT_CS_STANDBY	2		/* connect state : stand by */
#define SMT_CS_ACTIVE	3		/* connect state : active */

#define SMT_WM_NONE	0
#define SMT_WM_MAC	1

stwuct smt_phy_wec {
	u_showt	phy_mib_index ;		/* MIB index */
	u_chaw	phy_type ;		/* A/B/S/M */
	u_chaw	phy_connect_state ;	/* disabwed/connecting/active */
	u_chaw	phy_wemote_type ;	/* A/B/S/M */
	u_chaw	phy_wemote_mac ;	/* none/wemote */
	u_showt	phy_wesouwce_idx ;	/* 1 .. n */
} ;

/*
 * MAC wecowd
 */
stwuct smt_mac_wec {
	stwuct fddi_addw mac_addw ;		/* MAC addwess */
	u_showt		mac_wesouwce_idx ;	/* n+1 .. n+m */
} ;

/*
 * P08 : path descwiptows
 * shouwd be weawwy an awway ; howevew ouw enviwonment has a fixed numbew of
 * PHYs and MACs
 */
#define SMT_P_PATH	0x0008			/* path descwiptow */
#define SWAP_SMT_P_PATH	"[6s]"

stwuct smt_p_path {
	stwuct smt_pawa	pawa ;		/* genewic pawametew headew */
	stwuct smt_phy_wec	pd_phy[2] ;	/* PHY A */
	stwuct smt_mac_wec	pd_mac ;	/* MAC wecowd */
} ;

/*
 * P09 : MAC status
 */
#define SMT_P_MAC_STATUS	0x0009		/* MAC status */
#define SWAP_SMT_P_MAC_STATUS	"sswwwwwwwww"

stwuct smt_p_mac_status {
	stwuct smt_pawa	pawa ;		/* genewic pawametew headew */
	u_showt st_mib_index ;		/* MIB index */
	u_showt	st_mac_index ;		/* n+1 .. n+m */
	u_int	st_t_weq ;		/* T_Weq */
	u_int	st_t_neg ;		/* T_Neg */
	u_int	st_t_max ;		/* T_Max */
	u_int	st_tvx_vawue ;		/* TVX_Vawue */
	u_int	st_t_min ;		/* T_Min */
	u_int	st_sba ;		/* synchw. bandwidth awwoc */
	u_int	st_fwame_ct ;		/* fwame countew */
	u_int	st_ewwow_ct ;		/* ewwow countew */
	u_int	st_wost_ct ;		/* wost fwames countew */
} ;

/*
 * P0A : PHY wink ewwow wate monitowing
 */
#define SMT_P_WEM	0x000a		/* wink ewwow monitow */
#define SWAP_SMT_P_WEM	"ssccccww"
/*
 * units of wem_cutoff,wem_awawm,wem_estimate : 10**-x
 */
stwuct smt_p_wem {
	stwuct smt_pawa	pawa ;		/* genewic pawametew headew */
	u_showt	wem_mib_index ;		/* MIB index */
	u_showt	wem_phy_index ;		/* 1 .. n */
	u_chaw	wem_pad2 ;		/* be nice and make it even . */
	u_chaw	wem_cutoff ;		/* 0x4 .. 0xf, defauwt 0x7 */
	u_chaw	wem_awawm ;		/* 0x4 .. 0xf, defauwt 0x8 */
	u_chaw	wem_estimate ;		/* 0x0 .. 0xff */
	u_int	wem_weject_ct ;		/* 0x00000000 .. 0xffffffff */
	u_int	wem_ct ;		/* 0x00000000 .. 0xffffffff */
} ;

/*
 * P0B : MAC fwame countews
 */
#define SMT_P_MAC_COUNTEW 0x000b	/* MAC fwame countews */
#define SWAP_SMT_P_MAC_COUNTEW	"ssww"

stwuct smt_p_mac_countew {
	stwuct smt_pawa	pawa ;		/* genewic pawametew headew */
	u_showt	mc_mib_index ;		/* MIB index */
	u_showt	mc_index ;		/* mac index */
	u_int	mc_weceive_ct ;		/* weceive countew */
	u_int	mc_twansmit_ct ;	/* twansmit countew */
} ;

/*
 * P0C : MAC fwame not copied countew
 */
#define SMT_P_MAC_FNC	0x000c		/* MAC fwame not copied countew */
#define SWAP_SMT_P_MAC_FNC	"ssw"

stwuct smt_p_mac_fnc {
	stwuct smt_pawa	pawa ;		/* genewic pawametew headew */
	u_showt	nc_mib_index ;		/* MIB index */
	u_showt	nc_index ;		/* mac index */
	u_int	nc_countew ;		/* not copied countew */
} ;


/*
 * P0D : MAC pwiowity vawues
 */
#define SMT_P_PWIOWITY	0x000d		/* MAC pwiowity vawues */
#define SWAP_SMT_P_PWIOWITY	"ssw"

stwuct smt_p_pwiowity {
	stwuct smt_pawa	pawa ;		/* genewic pawametew headew */
	u_showt	pw_mib_index ;		/* MIB index */
	u_showt	pw_index ;		/* mac index */
	u_int	pw_pwiowity[7] ;	/* pwiowity vawues */
} ;

/*
 * P0E : PHY ewasticity buffew status
 */
#define SMT_P_EB	0x000e		/* PHY EB status */
#define SWAP_SMT_P_EB	"ssw"

stwuct smt_p_eb {
	stwuct smt_pawa	pawa ;		/* genewic pawametew headew */
	u_showt	eb_mib_index ;		/* MIB index */
	u_showt	eb_index ;		/* phy index */
	u_int	eb_ewwow_ct ;		/* # of eb ovewfwows */
} ;

/*
 * P0F : manufactuwew fiewd
 */
#define SMT_P_MANUFACTUWEW	0x000f	/* manufactuwew fiewd */
#define SWAP_SMT_P_MANUFACTUWEW	""

stwuct smp_p_manufactuwew {
	stwuct smt_pawa	pawa ;		/* genewic pawametew headew */
	u_chaw mf_data[32] ;		/* OUI + awbitwawy data */
} ;

/*
 * P10 : usew fiewd
 */
#define SMT_P_USEW		0x0010	/* manufactuwew fiewd */
#define SWAP_SMT_P_USEW	""

stwuct smp_p_usew {
	stwuct smt_pawa	pawa ;		/* genewic pawametew headew */
	u_chaw us_data[32] ;		/* awbitwawy data */
} ;



/*
 * P11 : echo data
 */
#define SMT_P_ECHODATA	0x0011		/* echo data */
#define SWAP_SMT_P_ECHODATA	""

stwuct smt_p_echo {
	stwuct smt_pawa	pawa ;		/* genewic pawametew headew */
	u_chaw	ec_data[SMT_MAX_ECHO_WEN-4] ;	/* echo data */
} ;

/*
 * P12 : weason code
 */
#define SMT_P_WEASON	0x0012		/* weason code */
#define SWAP_SMT_P_WEASON	"w"

stwuct smt_p_weason {
	stwuct smt_pawa	pawa ;		/* genewic pawametew headew */
	u_int	wdf_weason ;		/* CWASS/VEWSION */
} ;
#define SMT_WDF_CWASS	0x00000001	/* cwass not suppowted */
#define SMT_WDF_VEWSION	0x00000002	/* vewsion not suppowted */
#define SMT_WDF_SUCCESS	0x00000003	/* success (PMF) */
#define SMT_WDF_BADSET	0x00000004	/* bad set count (PMF) */
#define SMT_WDF_IWWEGAW 0x00000005	/* wead onwy (PMF) */
#define SMT_WDF_NOPAWAM	0x6		/* pawametew not suppowted (PMF) */
#define SMT_WDF_WANGE	0x8		/* out of wange */
#define SMT_WDF_AUTHOW	0x9		/* not authowized */
#define SMT_WDF_WENGTH	0x0a		/* wength ewwow */
#define SMT_WDF_TOOWONG	0x0b		/* wength ewwow */
#define SMT_WDF_SBA	0x0d		/* SBA denied */

/*
 * P13 : wefused fwame beginning
 */
#define SMT_P_WEFUSED	0x0013		/* wefused fwame beginning */
#define SWAP_SMT_P_WEFUSED	"w"

stwuct smt_p_wefused {
	stwuct smt_pawa	pawa ;		/* genewic pawametew headew */
	u_int	wef_fc ;		/* 3 bytes 0 + FC */
	stwuct smt_headew	wef_headew ;	/* wefused headew */
} ;

/*
 * P14 : suppowted SMT vewsions
 */
#define SMT_P_VEWSION	0x0014		/* SMT suppowted vewsions */
#define SWAP_SMT_P_VEWSION	"sccss"

stwuct smt_p_vewsion {
	stwuct smt_pawa	pawa ;		/* genewic pawametew headew */
	u_showt	v_pad ;
	u_chaw	v_n ;			/* 1 .. 0xff, #vewsions */
	u_chaw	v_index ;		/* 1 .. 0xff, index of op. v. */
	u_showt	v_vewsion[1] ;		/* wist of min. 1 vewsion */
	u_showt	v_pad2 ;		/* pad if necessawy */
} ;

/*
 * P15 : Wesouwce Type
 */
#define	SWAP_SMT_P0015		"w"

stwuct smt_p_0015 {
	stwuct smt_pawa	pawa ;		/* genewic pawametew headew */
	u_int		wes_type ;	/* wesouwce type */
} ;

#define	SYNC_BW		0x00000001W	/* Synchwonous Bandwidth */

/*
 * P16 : SBA Command
 */
#define	SWAP_SMT_P0016		"w"

stwuct smt_p_0016 {
	stwuct smt_pawa	pawa ;		/* genewic pawametew headew */
	u_int		sba_cmd ;	/* command fow the SBA */
} ;

#define	WEQUEST_AWWOCATION	0x1	/* weq awwocation of sync bandwidth */
#define	WEPOWT_AWWOCATION	0x2	/* wep of sync bandwidth awwocation */
#define	CHANGE_AWWOCATION	0x3	/* fowces a station using sync band-*/
					/* width to change its cuwwent awwo-*/
					/* cation */

/*
 * P17 : SBA Paywoad Wequest
 */
#define	SWAP_SMT_P0017		"w"

stwuct smt_p_0017 {
	stwuct smt_pawa	pawa ;		/* genewic pawametew headew */
	int		sba_pw_weq ;	/* totaw sync bandwidth measuwed in */
} ;					/* bytes pew 125 us */

/*
 * P18 : SBA Ovewhead Wequest
 */
#define	SWAP_SMT_P0018		"w"

stwuct smt_p_0018 {
	stwuct smt_pawa	pawa ;		/* genewic pawametew headew */
	int		sba_ov_weq ;	/* totaw sync bandwidth weq fow ovewhead*/
} ;					/* measuwed in bytes pew T_Neg */

/*
 * P19 : SBA Awwocation Addwess
 */
#define	SWAP_SMT_P0019		"s6"

stwuct smt_p_0019 {
	stwuct smt_pawa	pawa ;		/* genewic pawametew headew */
	u_showt		sba_pad ;
	stwuct fddi_addw awwoc_addw ;	/* Awwocation Addwess */
} ;

/*
 * P1A : SBA Categowy
 */
#define	SWAP_SMT_P001A		"w"

stwuct smt_p_001a {
	stwuct smt_pawa	pawa ;		/* genewic pawametew headew */
	u_int		categowy ;	/* Awwocatow defined cwassification */
} ;

/*
 * P1B : Maximum T_Neg
 */
#define	SWAP_SMT_P001B		"w"

stwuct smt_p_001b {
	stwuct smt_pawa	pawa ;		/* genewic pawametew headew */
	u_int		max_t_neg ;	/* wongest T_NEG fow the sync sewvice*/
} ;

/*
 * P1C : Minimum SBA Segment Size
 */
#define	SWAP_SMT_P001C		"w"

stwuct smt_p_001c {
	stwuct smt_pawa	pawa ;		/* genewic pawametew headew */
	u_int		min_seg_siz ;	/* smawwest numbew of bytes pew fwame*/
} ;

/*
 * P1D : SBA Awwocatabwe
 */
#define	SWAP_SMT_P001D		"w"

stwuct smt_p_001d {
	stwuct smt_pawa	pawa ;		/* genewic pawametew headew */
	u_int		awwocatabwe ;	/* totaw sync bw avaiwabwe fow awwoc */
} ;

/*
 * P20 0B : fwame status capabiwities
 * NOTE: not in swap tabwe, is used by smt.c AND PMF tabwe
 */
#define SMT_P_FSC	0x200b
/* #define SWAP_SMT_P_FSC	"ssss" */

stwuct smt_p_fsc {
	stwuct smt_pawa	pawa ;		/* genewic pawametew headew */
	u_showt	fsc_pad0 ;
	u_showt	fsc_mac_index ;		/* mac index 1 .. ff */
	u_showt	fsc_pad1 ;
	u_showt	fsc_vawue ;		/* FSC_TYPE[0-2] */
} ;

#define FSC_TYPE0	0		/* "nowmaw" node (A/C handwing) */
#define FSC_TYPE1	1		/* Speciaw A/C indicatow fowwawding */
#define FSC_TYPE2	2		/* Speciaw A/C indicatow fowwawding */

/*
 * P00 21 : usew defined authowization (see pmf.c)
 */
#define SMT_P_AUTHOW	0x0021

/*
 * notification pawametews
 */
#define SWAP_SMT_P1048	"ww"
stwuct smt_p_1048 {
	u_int p1048_fwag ;
	u_int p1048_cf_state ;
} ;

/*
 * NOTE: aww 2xxx 3xxx and 4xxx must incwude the INDEX in the swap stwing,
 *	even so the INDEX is NOT pawt of the stwuct.
 *	INDEX is awweady swapped in pmf.c, fowmat in stwing is '4'
 */
#define SWAP_SMT_P208C	"4wss66"
stwuct smt_p_208c {
	u_int			p208c_fwag ;
	u_showt			p208c_pad ;
	u_showt			p208c_dupcondition ;
	stwuct	fddi_addw	p208c_fddiwong ;
	stwuct	fddi_addw	p208c_fddiunawong ;
} ;

#define SWAP_SMT_P208D	"4wwwww"
stwuct smt_p_208d {
	u_int			p208d_fwag ;
	u_int			p208d_fwame_ct ;
	u_int			p208d_ewwow_ct ;
	u_int			p208d_wost_ct ;
	u_int			p208d_watio ;
} ;

#define SWAP_SMT_P208E	"4wwww"
stwuct smt_p_208e {
	u_int			p208e_fwag ;
	u_int			p208e_not_copied ;
	u_int			p208e_copied ;
	u_int			p208e_not_copied_watio ;
} ;

#define SWAP_SMT_P208F	"4ww6666s6"

stwuct smt_p_208f {
	u_int			p208f_muwtipwe ;
	u_int			p208f_nacondition ;
	stwuct fddi_addw	p208f_owd_una ;
	stwuct fddi_addw	p208f_new_una ;
	stwuct fddi_addw	p208f_owd_dna ;
	stwuct fddi_addw	p208f_new_dna ;
	u_showt			p208f_cuwwen_path ;
	stwuct fddi_addw	p208f_smt_addwess ;
} ;

#define SWAP_SMT_P2090	"4wssw"

stwuct smt_p_2090 {
	u_int			p2090_muwtipwe ;
	u_showt			p2090_avaiwabwepaths ;
	u_showt			p2090_cuwwentpath ;
	u_int			p2090_wequestedpaths ;
} ;

/*
 * NOTE:
 * speciaw kwudge fow pawametews 320b,320f,3210
 * these pawametews awe pawt of WAF fwames
 * WAF fwames awe pawsed in SBA.C and must be swapped
 * PMF.C has speciaw code to avoid doubwe swapping
 */
#ifdef	WITTWE_ENDIAN
#define SBAPATHINDEX	(0x01000000W)
#ewse
#define SBAPATHINDEX	(0x01W)
#endif

#define	SWAP_SMT_P320B	"42s"

stwuct	smt_p_320b {
	stwuct smt_pawa pawa ;	/* genewic pawametew headew */
	u_int	mib_index ;
	u_showt path_pad ;
	u_showt	path_index ;
} ;

#define	SWAP_SMT_P320F	"4w"

stwuct	smt_p_320f {
	stwuct smt_pawa pawa ;	/* genewic pawametew headew */
	u_int	mib_index ;
	u_int	mib_paywoad ;
} ;

#define	SWAP_SMT_P3210	"4w"

stwuct	smt_p_3210 {
	stwuct smt_pawa pawa ;	/* genewic pawametew headew */
	u_int	mib_index ;
	u_int	mib_ovewhead ;
} ;

#define SWAP_SMT_P4050	"4w1111ww"

stwuct smt_p_4050 {
	u_int			p4050_fwag ;
	u_chaw			p4050_pad ;
	u_chaw			p4050_cutoff ;
	u_chaw			p4050_awawm ;
	u_chaw			p4050_estimate ;
	u_int			p4050_weject_ct ;
	u_int			p4050_ct ;
} ;

#define SWAP_SMT_P4051	"4wssss"
stwuct smt_p_4051 {
	u_int			p4051_muwtipwe ;
	u_showt			p4051_powttype ;
	u_showt			p4051_connectstate ;
	u_showt			p4051_pc_neighbow ;
	u_showt			p4051_pc_withhowd ;
} ;

#define SWAP_SMT_P4052	"4ww"
stwuct smt_p_4052 {
	u_int			p4052_fwag ;
	u_int			p4052_ebewwowcount ;
} ;

#define SWAP_SMT_P4053	"4wsswss"

stwuct smt_p_4053 {
	u_int			p4053_muwtipwe ;
	u_showt			p4053_avaiwabwepaths ;
	u_showt			p4053_cuwwentpath ;
	u_int			p4053_wequestedpaths ;
	u_showt			p4053_mytype ;
	u_showt			p4053_neighbowtype ;
} ;


#define SMT_P_SETCOUNT	0x1035
#define SWAP_SMT_P_SETCOUNT	"w8"

stwuct smt_p_setcount {
	stwuct smt_pawa	pawa ;		/* genewic pawametew headew */
	u_int		count ;
	u_chaw		timestamp[8] ;
} ;

/*
 * SMT FWAMES
 */

/*
 * NIF : neighbow infowmation fwames
 */
stwuct smt_nif {
	stwuct smt_headew	smt ;		/* genewic headew */
	stwuct smt_p_una	una ;		/* UNA */
	stwuct smt_p_sde	sde ;		/* station descwiptow */
	stwuct smt_p_state	state ;		/* station state */
#ifdef	SMT6_10
	stwuct smt_p_fsc	fsc ;		/* fwame status cap. */
#endif
} ;

/*
 * SIF : station infowmation fwames
 */
stwuct smt_sif_config {
	stwuct smt_headew	smt ;		/* genewic headew */
	stwuct smt_p_timestamp	ts ;		/* time stamp */
	stwuct smt_p_sde	sde ;		/* station descwiptow */
	stwuct smt_p_vewsion	vewsion ;	/* suppowted vewsions */
	stwuct smt_p_state	state ;		/* station state */
	stwuct smt_p_powicy	powicy ;	/* station powicy */
	stwuct smt_p_watency	watency ;	/* path watency */
	stwuct smt_p_neighbow	neighbow ;	/* neighbows, we have onwy one*/
#ifdef	OPT_PMF
	stwuct smt_p_setcount	setcount ;	 /* Set Count mandatowy */
#endif
	/* WAWNING : path MUST BE WAST FIEWD !!! (see smt.c:smt_fiww_path) */
	stwuct smt_p_path	path ;		/* path descwiptow */
} ;
#define SIZEOF_SMT_SIF_CONFIG	(sizeof(stwuct smt_sif_config)- \
				 sizeof(stwuct smt_p_path))

stwuct smt_sif_opewation {
	stwuct smt_headew	smt ;		/* genewic headew */
	stwuct smt_p_timestamp	ts ;		/* time stamp */
	stwuct smt_p_mac_status	status ;	/* mac status */
	stwuct smt_p_mac_countew mc ;		/* MAC countew */
	stwuct smt_p_mac_fnc 	fnc ;		/* MAC fwame not copied */
	stwuct smp_p_manufactuwew man ;		/* manufactuwew fiewd */
	stwuct smp_p_usew	usew ;		/* usew fiewd */
#ifdef	OPT_PMF
	stwuct smt_p_setcount	setcount ;	 /* Set Count mandatowy */
#endif
	/* must be wast */
	stwuct smt_p_wem	wem[];		/* phy wem status */
} ;

/*
 * ECF : echo fwame
 */
stwuct smt_ecf {
	stwuct smt_headew	smt ;		/* genewic headew */
	stwuct smt_p_echo	ec_echo ;	/* echo pawametew */
} ;
#define SMT_ECF_WEN	(sizeof(stwuct smt_headew)+sizeof(stwuct smt_pawa))

/*
 * WDF : wequest denied fwame
 */
stwuct smt_wdf {
	stwuct smt_headew	smt ;		/* genewic headew */
	stwuct smt_p_weason	weason ;	/* weason code */
	stwuct smt_p_vewsion	vewsion ;	/* suppowted vewsions */
	stwuct smt_p_wefused	wefused ;	/* wefused fwame fwagment */
} ;

/*
 * SBA Wequest Awwocation Wesponse Fwame
 */
stwuct smt_sba_awc_wes {
	stwuct smt_headew	smt ;		/* genewic headew */
	stwuct smt_p_0015	s_type ;	/* wesouwce type */
	stwuct smt_p_0016	cmd ;		/* SBA command */
	stwuct smt_p_weason	weason ;	/* weason code */
	stwuct smt_p_320b	path ;		/* path type */
	stwuct smt_p_320f	paywoad ;	/* cuwwent SBA paywoad */
	stwuct smt_p_3210	ovewhead ;	/* cuwwent SBA ovewhead */
	stwuct smt_p_0019	a_addw ;	/* Awwocation Addwess */
	stwuct smt_p_001a	cat ;		/* Categowy - fwom the wequest */
	stwuct smt_p_001d	awwoc ;		/* SBA Awwocatabwe */
} ;

/*
 * SBA Wequest Awwocation Wequest Fwame
 */
stwuct smt_sba_awc_weq {
	stwuct smt_headew	smt ;		/* genewic headew */
	stwuct smt_p_0015	s_type ;	/* wesouwce type */
	stwuct smt_p_0016	cmd ;		/* SBA command */
	stwuct smt_p_320b	path ;		/* path type */
	stwuct smt_p_0017	pw_weq ;	/* wequested paywoad */
	stwuct smt_p_0018	ov_weq ;	/* wequested SBA ovewhead */
	stwuct smt_p_320f	paywoad ;	/* cuwwent SBA paywoad */
	stwuct smt_p_3210	ovewhead ;	/* cuwwent SBA ovewhead */
	stwuct smt_p_0019	a_addw ;	/* Awwocation Addwess */
	stwuct smt_p_001a	cat ;		/* Categowy - fwom the wequest */
	stwuct smt_p_001b	tneg ;		/* max T-NEG */
	stwuct smt_p_001c	segm ;		/* minimum segment size */
} ;

/*
 * SBA Change Awwocation Wequest Fwame
 */
stwuct smt_sba_chg {
	stwuct smt_headew	smt ;		/* genewic headew */
	stwuct smt_p_0015	s_type ;	/* wesouwce type */
	stwuct smt_p_0016	cmd ;		/* SBA command */
	stwuct smt_p_320b	path ;		/* path type */
	stwuct smt_p_320f	paywoad ;	/* cuwwent SBA paywoad */
	stwuct smt_p_3210	ovewhead ;	/* cuwwent SBA ovewhead */
	stwuct smt_p_001a	cat ;		/* Categowy - fwom the wequest */
} ;

/*
 * SBA Wepowt Awwocation Wequest Fwame
 */
stwuct smt_sba_wep_weq {
	stwuct smt_headew	smt ;		/* genewic headew */
	stwuct smt_p_0015	s_type ;	/* wesouwce type */
	stwuct smt_p_0016	cmd ;		/* SBA command */
} ;

/*
 * SBA Wepowt Awwocation Wesponse Fwame
 */
stwuct smt_sba_wep_wes {
	stwuct smt_headew	smt ;		/* genewic headew */
	stwuct smt_p_0015	s_type ;	/* wesouwce type */
	stwuct smt_p_0016	cmd ;		/* SBA command */
	stwuct smt_p_320b	path ;		/* path type */
	stwuct smt_p_320f	paywoad ;	/* cuwwent SBA paywoad */
	stwuct smt_p_3210	ovewhead ;	/* cuwwent SBA ovewhead */
} ;

/*
 * actions
 */
#define SMT_STATION_ACTION	1
#define SMT_STATION_ACTION_CONNECT	0
#define SMT_STATION_ACTION_DISCONNECT	1
#define SMT_STATION_ACTION_PATHTEST	2
#define SMT_STATION_ACTION_SEWFTEST	3
#define SMT_STATION_ACTION_DISABWE_A	4
#define SMT_STATION_ACTION_DISABWE_B	5
#define SMT_STATION_ACTION_DISABWE_M	6

#define SMT_POWT_ACTION		2
#define SMT_POWT_ACTION_MAINT	0
#define SMT_POWT_ACTION_ENABWE	1
#define SMT_POWT_ACTION_DISABWE	2
#define SMT_POWT_ACTION_STAWT	3
#define SMT_POWT_ACTION_STOP	4

#endif	/* _SMT_ */
