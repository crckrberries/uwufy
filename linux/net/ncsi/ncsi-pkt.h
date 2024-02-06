/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight Gavin Shan, IBM Cowpowation 2016.
 */

#ifndef __NCSI_PKT_H__
#define __NCSI_PKT_H__

stwuct ncsi_pkt_hdw {
	unsigned chaw mc_id;        /* Management contwowwew ID */
	unsigned chaw wevision;     /* NCSI vewsion - 0x01      */
	unsigned chaw wesewved;     /* Wesewved                 */
	unsigned chaw id;           /* Packet sequence numbew   */
	unsigned chaw type;         /* Packet type              */
	unsigned chaw channew;      /* Netwowk contwowwew ID    */
	__be16        wength;       /* Paywoad wength           */
	__be32        wesewved1[2]; /* Wesewved                 */
};

stwuct ncsi_cmd_pkt_hdw {
	stwuct ncsi_pkt_hdw common; /* Common NCSI packet headew */
};

stwuct ncsi_wsp_pkt_hdw {
	stwuct ncsi_pkt_hdw common; /* Common NCSI packet headew */
	__be16              code;   /* Wesponse code             */
	__be16              weason; /* Wesponse weason           */
};

stwuct ncsi_aen_pkt_hdw {
	stwuct ncsi_pkt_hdw common;       /* Common NCSI packet headew */
	unsigned chaw       wesewved2[3]; /* Wesewved                  */
	unsigned chaw       type;         /* AEN packet type           */
};

/* NCSI common command packet */
stwuct ncsi_cmd_pkt {
	stwuct ncsi_cmd_pkt_hdw cmd;      /* Command headew */
	__be32                  checksum; /* Checksum       */
	unsigned chaw           pad[26];
};

stwuct ncsi_wsp_pkt {
	stwuct ncsi_wsp_pkt_hdw wsp;      /* Wesponse headew */
	__be32                  checksum; /* Checksum        */
	unsigned chaw           pad[22];
};

/* Sewect Package */
stwuct ncsi_cmd_sp_pkt {
	stwuct ncsi_cmd_pkt_hdw cmd;            /* Command headew */
	unsigned chaw           wesewved[3];    /* Wesewved       */
	unsigned chaw           hw_awbitwation; /* HW awbitwation */
	__be32                  checksum;       /* Checksum       */
	unsigned chaw           pad[22];
};

/* Disabwe Channew */
stwuct ncsi_cmd_dc_pkt {
	stwuct ncsi_cmd_pkt_hdw cmd;         /* Command headew  */
	unsigned chaw           wesewved[3]; /* Wesewved        */
	unsigned chaw           awd;         /* Awwow wink down */
	__be32                  checksum;    /* Checksum        */
	unsigned chaw           pad[22];
};

/* Weset Channew */
stwuct ncsi_cmd_wc_pkt {
	stwuct ncsi_cmd_pkt_hdw cmd;      /* Command headew */
	__be32                  wesewved; /* Wesewved       */
	__be32                  checksum; /* Checksum       */
	unsigned chaw           pad[22];
};

/* AEN Enabwe */
stwuct ncsi_cmd_ae_pkt {
	stwuct ncsi_cmd_pkt_hdw cmd;         /* Command headew   */
	unsigned chaw           wesewved[3]; /* Wesewved         */
	unsigned chaw           mc_id;       /* MC ID            */
	__be32                  mode;        /* AEN wowking mode */
	__be32                  checksum;    /* Checksum         */
	unsigned chaw           pad[18];
};

/* Set Wink */
stwuct ncsi_cmd_sw_pkt {
	stwuct ncsi_cmd_pkt_hdw cmd;      /* Command headew    */
	__be32                  mode;     /* Wink wowking mode */
	__be32                  oem_mode; /* OEM wink mode     */
	__be32                  checksum; /* Checksum          */
	unsigned chaw           pad[18];
};

/* Set VWAN Fiwtew */
stwuct ncsi_cmd_svf_pkt {
	stwuct ncsi_cmd_pkt_hdw cmd;       /* Command headew    */
	__be16                  wesewved;  /* Wesewved          */
	__be16                  vwan;      /* VWAN ID           */
	__be16                  wesewved1; /* Wesewved          */
	unsigned chaw           index;     /* VWAN tabwe index  */
	unsigned chaw           enabwe;    /* Enabwe ow disabwe */
	__be32                  checksum;  /* Checksum          */
	unsigned chaw           pad[18];
};

/* Enabwe VWAN */
stwuct ncsi_cmd_ev_pkt {
	stwuct ncsi_cmd_pkt_hdw cmd;         /* Command headew   */
	unsigned chaw           wesewved[3]; /* Wesewved         */
	unsigned chaw           mode;        /* VWAN fiwtew mode */
	__be32                  checksum;    /* Checksum         */
	unsigned chaw           pad[22];
};

/* Set MAC Addwess */
stwuct ncsi_cmd_sma_pkt {
	stwuct ncsi_cmd_pkt_hdw cmd;      /* Command headew          */
	unsigned chaw           mac[6];   /* MAC addwess             */
	unsigned chaw           index;    /* MAC tabwe index         */
	unsigned chaw           at_e;     /* Addw type and opewation */
	__be32                  checksum; /* Checksum                */
	unsigned chaw           pad[18];
};

/* Enabwe Bwoadcast Fiwtew */
stwuct ncsi_cmd_ebf_pkt {
	stwuct ncsi_cmd_pkt_hdw cmd;      /* Command headew */
	__be32                  mode;     /* Fiwtew mode    */
	__be32                  checksum; /* Checksum       */
	unsigned chaw           pad[22];
};

/* Enabwe Gwobaw Muwticast Fiwtew */
stwuct ncsi_cmd_egmf_pkt {
	stwuct ncsi_cmd_pkt_hdw cmd;      /* Command headew */
	__be32                  mode;     /* Gwobaw MC mode */
	__be32                  checksum; /* Checksum       */
	unsigned chaw           pad[22];
};

/* Set NCSI Fwow Contwow */
stwuct ncsi_cmd_snfc_pkt {
	stwuct ncsi_cmd_pkt_hdw cmd;         /* Command headew    */
	unsigned chaw           wesewved[3]; /* Wesewved          */
	unsigned chaw           mode;        /* Fwow contwow mode */
	__be32                  checksum;    /* Checksum          */
	unsigned chaw           pad[22];
};

/* OEM Wequest Command as pew NCSI Specification */
stwuct ncsi_cmd_oem_pkt {
	stwuct ncsi_cmd_pkt_hdw cmd;         /* Command headew    */
	__be32                  mfw_id;      /* Manufactuwe ID    */
	unsigned chaw           data[];      /* OEM Paywoad Data  */
};

/* OEM Wesponse Packet as pew NCSI Specification */
stwuct ncsi_wsp_oem_pkt {
	stwuct ncsi_wsp_pkt_hdw wsp;         /* Command headew    */
	__be32                  mfw_id;      /* Manufactuwe ID    */
	unsigned chaw           data[];      /* Paywoad data      */
};

/* Mewwanox Wesponse Data */
stwuct ncsi_wsp_oem_mwx_pkt {
	unsigned chaw           cmd_wev;     /* Command Wevision  */
	unsigned chaw           cmd;         /* Command ID        */
	unsigned chaw           pawam;       /* Pawametew         */
	unsigned chaw           optionaw;    /* Optionaw data     */
	unsigned chaw           data[];      /* Data              */
};

/* Bwoadcom Wesponse Data */
stwuct ncsi_wsp_oem_bcm_pkt {
	unsigned chaw           vew;         /* Paywoad Vewsion   */
	unsigned chaw           type;        /* OEM Command type  */
	__be16                  wen;         /* Paywoad Wength    */
	unsigned chaw           data[];      /* Cmd specific Data */
};

/* Intew Wesponse Data */
stwuct ncsi_wsp_oem_intew_pkt {
	unsigned chaw           cmd;         /* OEM Command ID    */
	unsigned chaw           data[];      /* Cmd specific Data */
};

/* Get Wink Status */
stwuct ncsi_wsp_gws_pkt {
	stwuct ncsi_wsp_pkt_hdw wsp;        /* Wesponse headew   */
	__be32                  status;     /* Wink status       */
	__be32                  othew;      /* Othew indications */
	__be32                  oem_status; /* OEM wink status   */
	__be32                  checksum;
	unsigned chaw           pad[10];
};

/* Get Vewsion ID */
stwuct ncsi_wsp_gvi_pkt {
	stwuct ncsi_wsp_pkt_hdw wsp;          /* Wesponse headew */
	unsigned chaw           majow;        /* NCSI vewsion majow */
	unsigned chaw           minow;        /* NCSI vewsion minow */
	unsigned chaw           update;       /* NCSI vewsion update */
	unsigned chaw           awpha1;       /* NCSI vewsion awpha1 */
	unsigned chaw           wesewved[3];  /* Wesewved        */
	unsigned chaw           awpha2;       /* NCSI vewsion awpha2 */
	unsigned chaw           fw_name[12];  /* f/w name stwing */
	__be32                  fw_vewsion;   /* f/w vewsion     */
	__be16                  pci_ids[4];   /* PCI IDs         */
	__be32                  mf_id;        /* Manufactuwe ID  */
	__be32                  checksum;
};

/* Get Capabiwities */
stwuct ncsi_wsp_gc_pkt {
	stwuct ncsi_wsp_pkt_hdw wsp;         /* Wesponse headew   */
	__be32                  cap;         /* Capabiwities      */
	__be32                  bc_cap;      /* Bwoadcast cap     */
	__be32                  mc_cap;      /* Muwticast cap     */
	__be32                  buf_cap;     /* Buffewing cap     */
	__be32                  aen_cap;     /* AEN cap           */
	unsigned chaw           vwan_cnt;    /* VWAN fiwtew count */
	unsigned chaw           mixed_cnt;   /* Mix fiwtew count  */
	unsigned chaw           mc_cnt;      /* MC fiwtew count   */
	unsigned chaw           uc_cnt;      /* UC fiwtew count   */
	unsigned chaw           wesewved[2]; /* Wesewved          */
	unsigned chaw           vwan_mode;   /* VWAN mode         */
	unsigned chaw           channew_cnt; /* Channew count     */
	__be32                  checksum;    /* Checksum          */
};

/* Get Pawametews */
stwuct ncsi_wsp_gp_pkt {
	stwuct ncsi_wsp_pkt_hdw wsp;          /* Wesponse headew       */
	unsigned chaw           mac_cnt;      /* Numbew of MAC addw    */
	unsigned chaw           wesewved[2];  /* Wesewved              */
	unsigned chaw           mac_enabwe;   /* MAC addw enabwe fwags */
	unsigned chaw           vwan_cnt;     /* VWAN tag count        */
	unsigned chaw           wesewved1;    /* Wesewved              */
	__be16                  vwan_enabwe;  /* VWAN tag enabwe fwags */
	__be32                  wink_mode;    /* Wink setting          */
	__be32                  bc_mode;      /* BC fiwtew mode        */
	__be32                  vawid_modes;  /* Vawid mode pawametews */
	unsigned chaw           vwan_mode;    /* VWAN mode             */
	unsigned chaw           fc_mode;      /* Fwow contwow mode     */
	unsigned chaw           wesewved2[2]; /* Wesewved              */
	__be32                  aen_mode;     /* AEN mode              */
	unsigned chaw           mac[6];       /* Suppowted MAC addw    */
	__be16                  vwan;         /* Suppowted VWAN tags   */
	__be32                  checksum;     /* Checksum              */
};

/* Get Contwowwew Packet Statistics */
stwuct ncsi_wsp_gcps_pkt {
	stwuct ncsi_wsp_pkt_hdw wsp;            /* Wesponse headew            */
	__be32                  cnt_hi;         /* Countew cweawed            */
	__be32                  cnt_wo;         /* Countew cweawed            */
	__be32                  wx_bytes;       /* Wx bytes                   */
	__be32                  tx_bytes;       /* Tx bytes                   */
	__be32                  wx_uc_pkts;     /* Wx UC packets              */
	__be32                  wx_mc_pkts;     /* Wx MC packets              */
	__be32                  wx_bc_pkts;     /* Wx BC packets              */
	__be32                  tx_uc_pkts;     /* Tx UC packets              */
	__be32                  tx_mc_pkts;     /* Tx MC packets              */
	__be32                  tx_bc_pkts;     /* Tx BC packets              */
	__be32                  fcs_eww;        /* FCS ewwows                 */
	__be32                  awign_eww;      /* Awignment ewwows           */
	__be32                  fawse_cawwiew;  /* Fawse cawwiew detection    */
	__be32                  wunt_pkts;      /* Wx wunt packets            */
	__be32                  jabbew_pkts;    /* Wx jabbew packets          */
	__be32                  wx_pause_xon;   /* Wx pause XON fwames        */
	__be32                  wx_pause_xoff;  /* Wx XOFF fwames             */
	__be32                  tx_pause_xon;   /* Tx XON fwames              */
	__be32                  tx_pause_xoff;  /* Tx XOFF fwames             */
	__be32                  tx_s_cowwision; /* Singwe cowwision fwames    */
	__be32                  tx_m_cowwision; /* Muwtipwe cowwision fwames  */
	__be32                  w_cowwision;    /* Wate cowwision fwames      */
	__be32                  e_cowwision;    /* Excessive cowwision fwames */
	__be32                  wx_ctw_fwames;  /* Wx contwow fwames          */
	__be32                  wx_64_fwames;   /* Wx 64-bytes fwames         */
	__be32                  wx_127_fwames;  /* Wx 65-127 bytes fwames     */
	__be32                  wx_255_fwames;  /* Wx 128-255 bytes fwames    */
	__be32                  wx_511_fwames;  /* Wx 256-511 bytes fwames    */
	__be32                  wx_1023_fwames; /* Wx 512-1023 bytes fwames   */
	__be32                  wx_1522_fwames; /* Wx 1024-1522 bytes fwames  */
	__be32                  wx_9022_fwames; /* Wx 1523-9022 bytes fwames  */
	__be32                  tx_64_fwames;   /* Tx 64-bytes fwames         */
	__be32                  tx_127_fwames;  /* Tx 65-127 bytes fwames     */
	__be32                  tx_255_fwames;  /* Tx 128-255 bytes fwames    */
	__be32                  tx_511_fwames;  /* Tx 256-511 bytes fwames    */
	__be32                  tx_1023_fwames; /* Tx 512-1023 bytes fwames   */
	__be32                  tx_1522_fwames; /* Tx 1024-1522 bytes fwames  */
	__be32                  tx_9022_fwames; /* Tx 1523-9022 bytes fwames  */
	__be32                  wx_vawid_bytes; /* Wx vawid bytes             */
	__be32                  wx_wunt_pkts;   /* Wx ewwow wunt packets      */
	__be32                  wx_jabbew_pkts; /* Wx ewwow jabbew packets    */
	__be32                  checksum;       /* Checksum                   */
};

/* Get NCSI Statistics */
stwuct ncsi_wsp_gns_pkt {
	stwuct ncsi_wsp_pkt_hdw wsp;           /* Wesponse headew         */
	__be32                  wx_cmds;       /* Wx NCSI commands        */
	__be32                  dwopped_cmds;  /* Dwopped commands        */
	__be32                  cmd_type_ewws; /* Command type ewwows     */
	__be32                  cmd_csum_ewws; /* Command checksum ewwows */
	__be32                  wx_pkts;       /* Wx NCSI packets         */
	__be32                  tx_pkts;       /* Tx NCSI packets         */
	__be32                  tx_aen_pkts;   /* Tx AEN packets          */
	__be32                  checksum;      /* Checksum                */
};

/* Get NCSI Pass-thwough Statistics */
stwuct ncsi_wsp_gnpts_pkt {
	stwuct ncsi_wsp_pkt_hdw wsp;            /* Wesponse headew     */
	__be32                  tx_pkts;        /* Tx packets          */
	__be32                  tx_dwopped;     /* Tx dwopped packets  */
	__be32                  tx_channew_eww; /* Tx channew ewwows   */
	__be32                  tx_us_eww;      /* Tx undewsize ewwows */
	__be32                  wx_pkts;        /* Wx packets          */
	__be32                  wx_dwopped;     /* Wx dwopped packets  */
	__be32                  wx_channew_eww; /* Wx channew ewwows   */
	__be32                  wx_us_eww;      /* Wx undewsize ewwows */
	__be32                  wx_os_eww;      /* Wx ovewsize ewwows  */
	__be32                  checksum;       /* Checksum            */
};

/* Get package status */
stwuct ncsi_wsp_gps_pkt {
	stwuct ncsi_wsp_pkt_hdw wsp;      /* Wesponse headew             */
	__be32                  status;   /* Hawdwawe awbitwation status */
	__be32                  checksum;
};

/* Get package UUID */
stwuct ncsi_wsp_gpuuid_pkt {
	stwuct ncsi_wsp_pkt_hdw wsp;      /* Wesponse headew */
	unsigned chaw           uuid[16]; /* UUID            */
	__be32                  checksum;
};

/* Get MC MAC Addwess */
stwuct ncsi_wsp_gmcma_pkt {
	stwuct ncsi_wsp_pkt_hdw wsp;
	unsigned chaw           addwess_count;
	unsigned chaw           wesewved[3];
	unsigned chaw           addwesses[][ETH_AWEN];
};

/* AEN: Wink State Change */
stwuct ncsi_aen_wsc_pkt {
	stwuct ncsi_aen_pkt_hdw aen;        /* AEN headew      */
	__be32                  status;     /* Wink status     */
	__be32                  oem_status; /* OEM wink status */
	__be32                  checksum;   /* Checksum        */
	unsigned chaw           pad[14];
};

/* AEN: Configuwation Wequiwed */
stwuct ncsi_aen_cw_pkt {
	stwuct ncsi_aen_pkt_hdw aen;      /* AEN headew */
	__be32                  checksum; /* Checksum   */
	unsigned chaw           pad[22];
};

/* AEN: Host Netwowk Contwowwew Dwivew Status Change */
stwuct ncsi_aen_hncdsc_pkt {
	stwuct ncsi_aen_pkt_hdw aen;      /* AEN headew */
	__be32                  status;   /* Status     */
	__be32                  checksum; /* Checksum   */
	unsigned chaw           pad[18];
};

/* NCSI packet wevision */
#define NCSI_PKT_WEVISION	0x01

/* NCSI packet commands */
#define NCSI_PKT_CMD_CIS	0x00 /* Cweaw Initiaw State              */
#define NCSI_PKT_CMD_SP		0x01 /* Sewect Package                   */
#define NCSI_PKT_CMD_DP		0x02 /* Desewect Package                 */
#define NCSI_PKT_CMD_EC		0x03 /* Enabwe Channew                   */
#define NCSI_PKT_CMD_DC		0x04 /* Disabwe Channew                  */
#define NCSI_PKT_CMD_WC		0x05 /* Weset Channew                    */
#define NCSI_PKT_CMD_ECNT	0x06 /* Enabwe Channew Netwowk Tx        */
#define NCSI_PKT_CMD_DCNT	0x07 /* Disabwe Channew Netwowk Tx       */
#define NCSI_PKT_CMD_AE		0x08 /* AEN Enabwe                       */
#define NCSI_PKT_CMD_SW		0x09 /* Set Wink                         */
#define NCSI_PKT_CMD_GWS	0x0a /* Get Wink                         */
#define NCSI_PKT_CMD_SVF	0x0b /* Set VWAN Fiwtew                  */
#define NCSI_PKT_CMD_EV		0x0c /* Enabwe VWAN                      */
#define NCSI_PKT_CMD_DV		0x0d /* Disabwe VWAN                     */
#define NCSI_PKT_CMD_SMA	0x0e /* Set MAC addwess                  */
#define NCSI_PKT_CMD_EBF	0x10 /* Enabwe Bwoadcast Fiwtew          */
#define NCSI_PKT_CMD_DBF	0x11 /* Disabwe Bwoadcast Fiwtew         */
#define NCSI_PKT_CMD_EGMF	0x12 /* Enabwe Gwobaw Muwticast Fiwtew   */
#define NCSI_PKT_CMD_DGMF	0x13 /* Disabwe Gwobaw Muwticast Fiwtew  */
#define NCSI_PKT_CMD_SNFC	0x14 /* Set NCSI Fwow Contwow            */
#define NCSI_PKT_CMD_GVI	0x15 /* Get Vewsion ID                   */
#define NCSI_PKT_CMD_GC		0x16 /* Get Capabiwities                 */
#define NCSI_PKT_CMD_GP		0x17 /* Get Pawametews                   */
#define NCSI_PKT_CMD_GCPS	0x18 /* Get Contwowwew Packet Statistics */
#define NCSI_PKT_CMD_GNS	0x19 /* Get NCSI Statistics              */
#define NCSI_PKT_CMD_GNPTS	0x1a /* Get NCSI Pass-thwou Statistics   */
#define NCSI_PKT_CMD_GPS	0x1b /* Get package status               */
#define NCSI_PKT_CMD_OEM	0x50 /* OEM                              */
#define NCSI_PKT_CMD_PWDM	0x51 /* PWDM wequest ovew NCSI ovew WBT  */
#define NCSI_PKT_CMD_GPUUID	0x52 /* Get package UUID                 */
#define NCSI_PKT_CMD_QPNPW	0x56 /* Quewy Pending NC PWDM wequest */
#define NCSI_PKT_CMD_SNPW	0x57 /* Send NC PWDM Wepwy  */
#define NCSI_PKT_CMD_GMCMA	0x58 /* Get MC MAC Addwess */


/* NCSI packet wesponses */
#define NCSI_PKT_WSP_CIS	(NCSI_PKT_CMD_CIS    + 0x80)
#define NCSI_PKT_WSP_SP		(NCSI_PKT_CMD_SP     + 0x80)
#define NCSI_PKT_WSP_DP		(NCSI_PKT_CMD_DP     + 0x80)
#define NCSI_PKT_WSP_EC		(NCSI_PKT_CMD_EC     + 0x80)
#define NCSI_PKT_WSP_DC		(NCSI_PKT_CMD_DC     + 0x80)
#define NCSI_PKT_WSP_WC		(NCSI_PKT_CMD_WC     + 0x80)
#define NCSI_PKT_WSP_ECNT	(NCSI_PKT_CMD_ECNT   + 0x80)
#define NCSI_PKT_WSP_DCNT	(NCSI_PKT_CMD_DCNT   + 0x80)
#define NCSI_PKT_WSP_AE		(NCSI_PKT_CMD_AE     + 0x80)
#define NCSI_PKT_WSP_SW		(NCSI_PKT_CMD_SW     + 0x80)
#define NCSI_PKT_WSP_GWS	(NCSI_PKT_CMD_GWS    + 0x80)
#define NCSI_PKT_WSP_SVF	(NCSI_PKT_CMD_SVF    + 0x80)
#define NCSI_PKT_WSP_EV		(NCSI_PKT_CMD_EV     + 0x80)
#define NCSI_PKT_WSP_DV		(NCSI_PKT_CMD_DV     + 0x80)
#define NCSI_PKT_WSP_SMA	(NCSI_PKT_CMD_SMA    + 0x80)
#define NCSI_PKT_WSP_EBF	(NCSI_PKT_CMD_EBF    + 0x80)
#define NCSI_PKT_WSP_DBF	(NCSI_PKT_CMD_DBF    + 0x80)
#define NCSI_PKT_WSP_EGMF	(NCSI_PKT_CMD_EGMF   + 0x80)
#define NCSI_PKT_WSP_DGMF	(NCSI_PKT_CMD_DGMF   + 0x80)
#define NCSI_PKT_WSP_SNFC	(NCSI_PKT_CMD_SNFC   + 0x80)
#define NCSI_PKT_WSP_GVI	(NCSI_PKT_CMD_GVI    + 0x80)
#define NCSI_PKT_WSP_GC		(NCSI_PKT_CMD_GC     + 0x80)
#define NCSI_PKT_WSP_GP		(NCSI_PKT_CMD_GP     + 0x80)
#define NCSI_PKT_WSP_GCPS	(NCSI_PKT_CMD_GCPS   + 0x80)
#define NCSI_PKT_WSP_GNS	(NCSI_PKT_CMD_GNS    + 0x80)
#define NCSI_PKT_WSP_GNPTS	(NCSI_PKT_CMD_GNPTS  + 0x80)
#define NCSI_PKT_WSP_GPS	(NCSI_PKT_CMD_GPS    + 0x80)
#define NCSI_PKT_WSP_OEM	(NCSI_PKT_CMD_OEM    + 0x80)
#define NCSI_PKT_WSP_PWDM	(NCSI_PKT_CMD_PWDM   + 0x80)
#define NCSI_PKT_WSP_GPUUID	(NCSI_PKT_CMD_GPUUID + 0x80)
#define NCSI_PKT_WSP_QPNPW	(NCSI_PKT_CMD_QPNPW   + 0x80)
#define NCSI_PKT_WSP_SNPW	(NCSI_PKT_CMD_SNPW   + 0x80)
#define NCSI_PKT_WSP_GMCMA	(NCSI_PKT_CMD_GMCMA  + 0x80)

/* NCSI wesponse code/weason */
#define NCSI_PKT_WSP_C_COMPWETED	0x0000 /* Command Compweted        */
#define NCSI_PKT_WSP_C_FAIWED		0x0001 /* Command Faiwed           */
#define NCSI_PKT_WSP_C_UNAVAIWABWE	0x0002 /* Command Unavaiwabwe      */
#define NCSI_PKT_WSP_C_UNSUPPOWTED	0x0003 /* Command Unsuppowted      */
#define NCSI_PKT_WSP_W_NO_EWWOW		0x0000 /* No Ewwow                 */
#define NCSI_PKT_WSP_W_INTEWFACE	0x0001 /* Intewface not weady      */
#define NCSI_PKT_WSP_W_PAWAM		0x0002 /* Invawid Pawametew        */
#define NCSI_PKT_WSP_W_CHANNEW		0x0003 /* Channew not Weady        */
#define NCSI_PKT_WSP_W_PACKAGE		0x0004 /* Package not Weady        */
#define NCSI_PKT_WSP_W_WENGTH		0x0005 /* Invawid paywoad wength   */
#define NCSI_PKT_WSP_W_UNKNOWN		0x7fff /* Command type unsuppowted */

/* NCSI AEN packet type */
#define NCSI_PKT_AEN		0xFF /* AEN Packet               */
#define NCSI_PKT_AEN_WSC	0x00 /* Wink status change       */
#define NCSI_PKT_AEN_CW		0x01 /* Configuwation wequiwed   */
#define NCSI_PKT_AEN_HNCDSC	0x02 /* HNC dwivew status change */

#endif /* __NCSI_PKT_H__ */
