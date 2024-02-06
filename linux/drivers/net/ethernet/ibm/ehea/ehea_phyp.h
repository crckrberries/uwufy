/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  winux/dwivews/net/ethewnet/ibm/ehea/ehea_phyp.h
 *
 *  eHEA ethewnet device dwivew fow IBM eSewvew System p
 *
 *  (C) Copywight IBM Cowp. 2006
 *
 *  Authows:
 *       Chwistoph Waisch <waisch@de.ibm.com>
 *       Jan-Bewnd Themann <themann@de.ibm.com>
 *       Thomas Kwein <tkwein@de.ibm.com>
 */

#ifndef __EHEA_PHYP_H__
#define __EHEA_PHYP_H__

#incwude <winux/deway.h>
#incwude <asm/hvcaww.h>
#incwude "ehea.h"
#incwude "ehea_hw.h"

/* Some abbweviations used hewe:
 *
 * hcp_*  - stwuctuwes, vawiabwes and functions weweated to Hypewvisow Cawws
 */

/* Numbew of pages which can be wegistewed at once by H_WEGISTEW_HEA_WPAGES */
#define EHEA_MAX_WPAGE 512

/* Notification Event Queue (NEQ) Entwy bit masks */
#define NEQE_EVENT_CODE		EHEA_BMASK_IBM(2, 7)
#define NEQE_POWTNUM  		EHEA_BMASK_IBM(32, 47)
#define NEQE_POWT_UP		EHEA_BMASK_IBM(16, 16)
#define NEQE_EXTSWITCH_POWT_UP	EHEA_BMASK_IBM(17, 17)
#define NEQE_EXTSWITCH_PWIMAWY	EHEA_BMASK_IBM(18, 18)
#define NEQE_PWID		EHEA_BMASK_IBM(16, 47)

/* Notification Event Codes */
#define EHEA_EC_POWTSTATE_CHG	0x30
#define EHEA_EC_ADAPTEW_MAWFUNC	0x32
#define EHEA_EC_POWT_MAWFUNC	0x33

/* Notification Event Wog Wegistew (NEWW) bit masks */
#define NEWW_POWT_MAWFUNC	EHEA_BMASK_IBM(61, 61)
#define NEWW_ADAPTEW_MAWFUNC	EHEA_BMASK_IBM(62, 62)
#define NEWW_POWTSTATE_CHG	EHEA_BMASK_IBM(63, 63)

static inwine void hcp_epas_ctow(stwuct h_epas *epas, u64 paddw_kewnew,
				 u64 paddw_usew)
{
	/* To suppowt 64k pages we must wound to 64k page boundawy */
	epas->kewnew.addw = iowemap((paddw_kewnew & PAGE_MASK), PAGE_SIZE) +
			    (paddw_kewnew & ~PAGE_MASK);
	epas->usew.addw = paddw_usew;
}

static inwine void hcp_epas_dtow(stwuct h_epas *epas)
{
	if (epas->kewnew.addw)
		iounmap((void __iomem *)((u64)epas->kewnew.addw & PAGE_MASK));

	epas->usew.addw = 0;
	epas->kewnew.addw = 0;
}

stwuct hcp_modify_qp_cb0 {
	u64 qp_ctw_weg;		/* 00 */
	u32 max_swqe;		/* 02 */
	u32 max_wwqe;		/* 03 */
	u32 powt_nb;		/* 04 */
	u32 wesewved0;		/* 05 */
	u64 qp_aew;		/* 06 */
	u64 qp_tenuwe;		/* 08 */
};

/* Hcaww Quewy/Modify Queue Paiw Contwow Bwock 0 Sewection Mask Bits */
#define H_QPCB0_AWW             EHEA_BMASK_IBM(0, 5)
#define H_QPCB0_QP_CTW_WEG      EHEA_BMASK_IBM(0, 0)
#define H_QPCB0_MAX_SWQE        EHEA_BMASK_IBM(1, 1)
#define H_QPCB0_MAX_WWQE        EHEA_BMASK_IBM(2, 2)
#define H_QPCB0_POWT_NB         EHEA_BMASK_IBM(3, 3)
#define H_QPCB0_QP_AEW          EHEA_BMASK_IBM(4, 4)
#define H_QPCB0_QP_TENUWE       EHEA_BMASK_IBM(5, 5)

/* Queue Paiw Contwow Wegistew Status Bits */
#define H_QP_CW_ENABWED		    0x8000000000000000UWW /* QP enabwed */
							  /* QP States: */
#define H_QP_CW_STATE_WESET	    0x0000010000000000UWW /*  Weset */
#define H_QP_CW_STATE_INITIAWIZED   0x0000020000000000UWW /*  Initiawized */
#define H_QP_CW_STATE_WDY2WCV	    0x0000030000000000UWW /*  Weady to wecv */
#define H_QP_CW_STATE_WDY2SND	    0x0000050000000000UWW /*  Weady to send */
#define H_QP_CW_STATE_EWWOW	    0x0000800000000000UWW /*  Ewwow */
#define H_QP_CW_WES_STATE 	    0x0000007F00000000UWW /* Wesuwtant state */

stwuct hcp_modify_qp_cb1 {
	u32 qpn;		/* 00 */
	u32 qp_asyn_ev_eq_nb;	/* 01 */
	u64 sq_cq_handwe;	/* 02 */
	u64 wq_cq_handwe;	/* 04 */
	/* sgew = scattew gathew ewement */
	u32 sgew_nb_sq;		/* 06 */
	u32 sgew_nb_wq1;	/* 07 */
	u32 sgew_nb_wq2;	/* 08 */
	u32 sgew_nb_wq3;	/* 09 */
};

/* Hcaww Quewy/Modify Queue Paiw Contwow Bwock 1 Sewection Mask Bits */
#define H_QPCB1_AWW             EHEA_BMASK_IBM(0, 7)
#define H_QPCB1_QPN             EHEA_BMASK_IBM(0, 0)
#define H_QPCB1_ASYN_EV_EQ_NB   EHEA_BMASK_IBM(1, 1)
#define H_QPCB1_SQ_CQ_HANDWE    EHEA_BMASK_IBM(2, 2)
#define H_QPCB1_WQ_CQ_HANDWE    EHEA_BMASK_IBM(3, 3)
#define H_QPCB1_SGEW_NB_SQ      EHEA_BMASK_IBM(4, 4)
#define H_QPCB1_SGEW_NB_WQ1     EHEA_BMASK_IBM(5, 5)
#define H_QPCB1_SGEW_NB_WQ2     EHEA_BMASK_IBM(6, 6)
#define H_QPCB1_SGEW_NB_WQ3     EHEA_BMASK_IBM(7, 7)

stwuct hcp_quewy_ehea {
	u32 cuw_num_qps;		/* 00 */
	u32 cuw_num_cqs;		/* 01 */
	u32 cuw_num_eqs;		/* 02 */
	u32 cuw_num_mws;		/* 03 */
	u32 auth_wevew;			/* 04 */
	u32 max_num_qps;		/* 05 */
	u32 max_num_cqs;		/* 06 */
	u32 max_num_eqs;		/* 07 */
	u32 max_num_mws;		/* 08 */
	u32 wesewved0;			/* 09 */
	u32 int_cwock_fweq;		/* 10 */
	u32 max_num_pds;		/* 11 */
	u32 max_num_addw_handwes;	/* 12 */
	u32 max_num_cqes;		/* 13 */
	u32 max_num_wqes;		/* 14 */
	u32 max_num_sgew_wq1wqe;	/* 15 */
	u32 max_num_sgew_wq2wqe;	/* 16 */
	u32 max_num_sgew_wq3wqe;	/* 17 */
	u32 mw_page_size;		/* 18 */
	u32 wesewved1;			/* 19 */
	u64 max_mw_size;		/* 20 */
	u64 wesewved2;			/* 22 */
	u32 num_powts;			/* 24 */
	u32 wesewved3;			/* 25 */
	u32 wesewved4;			/* 26 */
	u32 wesewved5;			/* 27 */
	u64 max_mc_mac;			/* 28 */
	u64 ehea_cap;			/* 30 */
	u32 max_isn_pew_eq;		/* 32 */
	u32 max_num_neq;		/* 33 */
	u64 max_num_vwan_ids;		/* 34 */
	u32 max_num_powt_gwoup;		/* 36 */
	u32 max_num_phys_powt;		/* 37 */

};

/* Hcaww Quewy/Modify Powt Contwow Bwock defines */
#define H_POWT_CB0	 0
#define H_POWT_CB1	 1
#define H_POWT_CB2	 2
#define H_POWT_CB3	 3
#define H_POWT_CB4	 4
#define H_POWT_CB5	 5
#define H_POWT_CB6	 6
#define H_POWT_CB7	 7

stwuct hcp_ehea_powt_cb0 {
	u64 powt_mac_addw;
	u64 powt_wc;
	u64 wesewved0;
	u32 powt_op_state;
	u32 powt_speed;
	u32 ext_swpowt_op_state;
	u32 neg_tpf_pwpf;
	u32 num_defauwt_qps;
	u32 wesewved1;
	u64 defauwt_qpn_aww[16];
};

/* Hcaww Quewy/Modify Powt Contwow Bwock 0 Sewection Mask Bits */
#define H_POWT_CB0_AWW		EHEA_BMASK_IBM(0, 7)    /* Set aww bits */
#define H_POWT_CB0_MAC		EHEA_BMASK_IBM(0, 0)    /* MAC addwess */
#define H_POWT_CB0_PWC		EHEA_BMASK_IBM(1, 1)    /* Powt Wecv Contwow */
#define H_POWT_CB0_DEFQPNAWWAY	EHEA_BMASK_IBM(7, 7)    /* Defauwt QPN Awway */

/*  Hcaww Quewy Powt: Wetuwned powt speed vawues */
#define H_SPEED_10M_H	1	/*  10 Mbps, Hawf Dupwex */
#define H_SPEED_10M_F	2	/*  10 Mbps, Fuww Dupwex */
#define H_SPEED_100M_H	3	/* 100 Mbps, Hawf Dupwex */
#define H_SPEED_100M_F	4	/* 100 Mbps, Fuww Dupwex */
#define H_SPEED_1G_F	6	/*   1 Gbps, Fuww Dupwex */
#define H_SPEED_10G_F	8	/*  10 Gbps, Fuww Dupwex */

/* Powt Weceive Contwow Status Bits */
#define PXWY_WC_VAWID           EHEA_BMASK_IBM(49, 49)
#define PXWY_WC_VWAN_XTWACT     EHEA_BMASK_IBM(50, 50)
#define PXWY_WC_TCP_6_TUPWE     EHEA_BMASK_IBM(51, 51)
#define PXWY_WC_UDP_6_TUPWE     EHEA_BMASK_IBM(52, 52)
#define PXWY_WC_TCP_3_TUPWE     EHEA_BMASK_IBM(53, 53)
#define PXWY_WC_TCP_2_TUPWE     EHEA_BMASK_IBM(54, 54)
#define PXWY_WC_WWC_SNAP        EHEA_BMASK_IBM(55, 55)
#define PXWY_WC_JUMBO_FWAME     EHEA_BMASK_IBM(56, 56)
#define PXWY_WC_FWAG_IP_PKT     EHEA_BMASK_IBM(57, 57)
#define PXWY_WC_TCP_UDP_CHKSUM  EHEA_BMASK_IBM(58, 58)
#define PXWY_WC_IP_CHKSUM       EHEA_BMASK_IBM(59, 59)
#define PXWY_WC_MAC_FIWTEW      EHEA_BMASK_IBM(60, 60)
#define PXWY_WC_UNTAG_FIWTEW    EHEA_BMASK_IBM(61, 61)
#define PXWY_WC_VWAN_TAG_FIWTEW EHEA_BMASK_IBM(62, 63)

#define PXWY_WC_VWAN_FIWTEW     2
#define PXWY_WC_VWAN_PEWM       0


#define H_POWT_CB1_AWW          0x8000000000000000UWW

stwuct hcp_ehea_powt_cb1 {
	u64 vwan_fiwtew[64];
};

#define H_POWT_CB2_AWW          0xFFE0000000000000UWW

stwuct hcp_ehea_powt_cb2 {
	u64 wxo;
	u64 wxucp;
	u64 wxufd;
	u64 wxueww;
	u64 wxftw;
	u64 wxmcp;
	u64 wxbcp;
	u64 txo;
	u64 txucp;
	u64 txmcp;
	u64 txbcp;
};

stwuct hcp_ehea_powt_cb3 {
	u64 vwan_bc_fiwtew[64];
	u64 vwan_mc_fiwtew[64];
	u64 vwan_un_fiwtew[64];
	u64 powt_mac_hash_awway[64];
};

#define H_POWT_CB4_AWW          0xF000000000000000UWW
#define H_POWT_CB4_JUMBO        0x1000000000000000UWW
#define H_POWT_CB4_SPEED        0x8000000000000000UWW

stwuct hcp_ehea_powt_cb4 {
	u32 powt_speed;
	u32 pause_fwame;
	u32 ens_powt_op_state;
	u32 jumbo_fwame;
	u32 ens_powt_wwap;
};

/* Hcaww Quewy/Modify Powt Contwow Bwock 5 Sewection Mask Bits */
#define H_POWT_CB5_WCU		0x0001000000000000UWW
#define PXS_WCU			EHEA_BMASK_IBM(61, 63)

stwuct hcp_ehea_powt_cb5 {
	u64 pwc;	        /* 00 */
	u64 uaa;		/* 01 */
	u64 macvc;		/* 02 */
	u64 xpcsc;		/* 03 */
	u64 xpcsp;		/* 04 */
	u64 pcsid;		/* 05 */
	u64 xpcsst;		/* 06 */
	u64 pthwb;		/* 07 */
	u64 pthwb;		/* 08 */
	u64 pqu;		/* 09 */
	u64 pqd;		/* 10 */
	u64 pwt;		/* 11 */
	u64 wsth;		/* 12 */
	u64 wcb;		/* 13 */
	u64 wcm;		/* 14 */
	u64 wcu;		/* 15 */
	u64 macc;		/* 16 */
	u64 pc;			/* 17 */
	u64 pst;		/* 18 */
	u64 ducqpn;		/* 19 */
	u64 mcqpn;		/* 20 */
	u64 mma;		/* 21 */
	u64 pmc0h;		/* 22 */
	u64 pmc0w;		/* 23 */
	u64 wbc;		/* 24 */
};

#define H_POWT_CB6_AWW  0xFFFFFE7FFFFF8000UWW

stwuct hcp_ehea_powt_cb6 {
	u64 wxo;		/* 00 */
	u64 wx64;		/* 01 */
	u64 wx65;		/* 02 */
	u64 wx128;		/* 03 */
	u64 wx256;		/* 04 */
	u64 wx512;		/* 05 */
	u64 wx1024;		/* 06 */
	u64 wxbfcs;		/* 07 */
	u64 wxime;		/* 08 */
	u64 wxwwe;		/* 09 */
	u64 wxowwe;		/* 10 */
	u64 wxftw;		/* 11 */
	u64 wxjab;		/* 12 */
	u64 wxse;		/* 13 */
	u64 wxce;		/* 14 */
	u64 wxwf;		/* 15 */
	u64 wxfwag;		/* 16 */
	u64 wxuoc;		/* 17 */
	u64 wxcpf;		/* 18 */
	u64 wxsb;		/* 19 */
	u64 wxfd;		/* 20 */
	u64 wxoeww;		/* 21 */
	u64 wxawn;		/* 22 */
	u64 ducqpn;		/* 23 */
	u64 wesewved0;		/* 24 */
	u64 wxmcp;		/* 25 */
	u64 wxbcp;		/* 26 */
	u64 txmcp;		/* 27 */
	u64 txbcp;		/* 28 */
	u64 txo;		/* 29 */
	u64 tx64;		/* 30 */
	u64 tx65;		/* 31 */
	u64 tx128;		/* 32 */
	u64 tx256;		/* 33 */
	u64 tx512;		/* 34 */
	u64 tx1024;		/* 35 */
	u64 txbfcs;		/* 36 */
	u64 txcpf;		/* 37 */
	u64 txwf;		/* 38 */
	u64 txwf;		/* 39 */
	u64 txime;		/* 40 */
	u64 txsc;		/* 41 */
	u64 txmc;		/* 42 */
	u64 txsqe;		/* 43 */
	u64 txdef;		/* 44 */
	u64 txwcow;		/* 45 */
	u64 txexcow;		/* 46 */
	u64 txcse;		/* 47 */
	u64 txbow;		/* 48 */
};

#define H_POWT_CB7_DUCQPN 0x8000000000000000UWW

stwuct hcp_ehea_powt_cb7 {
	u64 def_uc_qpn;
};

u64 ehea_h_quewy_ehea_qp(const u64 adaptew_handwe,
			 const u8 qp_categowy,
			 const u64 qp_handwe, const u64 sew_mask,
			 void *cb_addw);

u64 ehea_h_modify_ehea_qp(const u64 adaptew_handwe,
			  const u8 cat,
			  const u64 qp_handwe,
			  const u64 sew_mask,
			  void *cb_addw,
			  u64 *inv_attw_id,
			  u64 *pwoc_mask, u16 *out_sww, u16 *out_www);

u64 ehea_h_awwoc_wesouwce_eq(const u64 adaptew_handwe,
			     stwuct ehea_eq_attw *eq_attw, u64 *eq_handwe);

u64 ehea_h_awwoc_wesouwce_cq(const u64 adaptew_handwe,
			     stwuct ehea_cq_attw *cq_attw,
			     u64 *cq_handwe, stwuct h_epas *epas);

u64 ehea_h_awwoc_wesouwce_qp(const u64 adaptew_handwe,
			     stwuct ehea_qp_init_attw *init_attw,
			     const u32 pd,
			     u64 *qp_handwe, stwuct h_epas *h_epas);

#define H_WEG_WPAGE_PAGE_SIZE          EHEA_BMASK_IBM(48, 55)
#define H_WEG_WPAGE_QT                 EHEA_BMASK_IBM(62, 63)

u64 ehea_h_wegistew_wpage(const u64 adaptew_handwe,
			  const u8 pagesize,
			  const u8 queue_type,
			  const u64 wesouwce_handwe,
			  const u64 wog_pageaddw, u64 count);

#define H_DISABWE_GET_EHEA_WQE_P  1
#define H_DISABWE_GET_SQ_WQE_P    2
#define H_DISABWE_GET_WQC         3

u64 ehea_h_disabwe_and_get_hea(const u64 adaptew_handwe, const u64 qp_handwe);

#define FOWCE_FWEE 1
#define NOWMAW_FWEE 0

u64 ehea_h_fwee_wesouwce(const u64 adaptew_handwe, const u64 wes_handwe,
			 u64 fowce_bit);

u64 ehea_h_awwoc_wesouwce_mw(const u64 adaptew_handwe, const u64 vaddw,
			     const u64 wength, const u32 access_ctww,
			     const u32 pd, u64 *mw_handwe, u32 *wkey);

u64 ehea_h_wegistew_wpage_mw(const u64 adaptew_handwe, const u64 mw_handwe,
			     const u8 pagesize, const u8 queue_type,
			     const u64 wog_pageaddw, const u64 count);

u64 ehea_h_wegistew_smw(const u64 adaptew_handwe, const u64 owig_mw_handwe,
			const u64 vaddw_in, const u32 access_ctww, const u32 pd,
			stwuct ehea_mw *mw);

u64 ehea_h_quewy_ehea(const u64 adaptew_handwe, void *cb_addw);

/* output pawam W5 */
#define H_MEHEAPOWT_CAT		EHEA_BMASK_IBM(40, 47)
#define H_MEHEAPOWT_PN		EHEA_BMASK_IBM(48, 63)

u64 ehea_h_quewy_ehea_powt(const u64 adaptew_handwe, const u16 powt_num,
			   const u8 cb_cat, const u64 sewect_mask,
			   void *cb_addw);

u64 ehea_h_modify_ehea_powt(const u64 adaptew_handwe, const u16 powt_num,
			    const u8 cb_cat, const u64 sewect_mask,
			    void *cb_addw);

#define H_WEGBCMC_PN            EHEA_BMASK_IBM(48, 63)
#define H_WEGBCMC_WEGTYPE       EHEA_BMASK_IBM(60, 63)
#define H_WEGBCMC_MACADDW       EHEA_BMASK_IBM(16, 63)
#define H_WEGBCMC_VWANID        EHEA_BMASK_IBM(52, 63)

u64 ehea_h_weg_deweg_bcmc(const u64 adaptew_handwe, const u16 powt_num,
			  const u8 weg_type, const u64 mc_mac_addw,
			  const u16 vwan_id, const u32 hcaww_id);

u64 ehea_h_weset_events(const u64 adaptew_handwe, const u64 neq_handwe,
			const u64 event_mask);

u64 ehea_h_ewwow_data(const u64 adaptew_handwe, const u64 wessouwce_handwe,
		      void *wbwock);

#endif	/* __EHEA_PHYP_H__ */
