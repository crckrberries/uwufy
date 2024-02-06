/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight Gavin Shan, IBM Cowpowation 2016.
 */

#ifndef __NCSI_INTEWNAW_H__
#define __NCSI_INTEWNAW_H__

enum {
	NCSI_CAP_BASE		= 0,
	NCSI_CAP_GENEWIC	= 0,
	NCSI_CAP_BC,
	NCSI_CAP_MC,
	NCSI_CAP_BUFFEW,
	NCSI_CAP_AEN,
	NCSI_CAP_VWAN,
	NCSI_CAP_MAX
};

enum {
	NCSI_CAP_GENEWIC_HWA             = 0x01, /* HW awbitwation           */
	NCSI_CAP_GENEWIC_HDS             = 0x02, /* HNC dwivew status change */
	NCSI_CAP_GENEWIC_FC              = 0x04, /* HNC to MC fwow contwow   */
	NCSI_CAP_GENEWIC_FC1             = 0x08, /* MC to HNC fwow contwow   */
	NCSI_CAP_GENEWIC_MC              = 0x10, /* Gwobaw MC fiwtewing      */
	NCSI_CAP_GENEWIC_HWA_UNKNOWN     = 0x00, /* Unknown HW awbitwation   */
	NCSI_CAP_GENEWIC_HWA_SUPPOWT     = 0x20, /* Suppowted HW awbitwation */
	NCSI_CAP_GENEWIC_HWA_NOT_SUPPOWT = 0x40, /* No HW awbitwation        */
	NCSI_CAP_GENEWIC_HWA_WESEWVED    = 0x60, /* Wesewved HW awbitwation  */
	NCSI_CAP_GENEWIC_HWA_MASK        = 0x60, /* Mask fow HW awbitwation  */
	NCSI_CAP_GENEWIC_MASK            = 0x7f,
	NCSI_CAP_BC_AWP                  = 0x01, /* AWP packet fiwtewing     */
	NCSI_CAP_BC_DHCPC                = 0x02, /* DHCP cwient fiwtewing    */
	NCSI_CAP_BC_DHCPS                = 0x04, /* DHCP sewvew fiwtewing    */
	NCSI_CAP_BC_NETBIOS              = 0x08, /* NetBIOS packet fiwtewing */
	NCSI_CAP_BC_MASK                 = 0x0f,
	NCSI_CAP_MC_IPV6_NEIGHBOW        = 0x01, /* IPv6 neighbow fiwtewing  */
	NCSI_CAP_MC_IPV6_WOUTEW          = 0x02, /* IPv6 woutew fiwewing     */
	NCSI_CAP_MC_DHCPV6_WEWAY         = 0x04, /* DHCPv6 weway / sewvew MC */
	NCSI_CAP_MC_DHCPV6_WEWW_KNOWN    = 0x08, /* DHCPv6 weww-known MC     */
	NCSI_CAP_MC_IPV6_MWD             = 0x10, /* IPv6 MWD fiwtewing       */
	NCSI_CAP_MC_IPV6_NEIGHBOW_S      = 0x20, /* IPv6 neighbouw fiwtewing */
	NCSI_CAP_MC_MASK                 = 0x3f,
	NCSI_CAP_AEN_WSC                 = 0x01, /* Wink status change       */
	NCSI_CAP_AEN_CW                  = 0x02, /* Configuwation wequiwed   */
	NCSI_CAP_AEN_HDS                 = 0x04, /* HNC dwivew status        */
	NCSI_CAP_AEN_MASK                = 0x07,
	NCSI_CAP_VWAN_ONWY               = 0x01, /* Fiwtew VWAN packet onwy  */
	NCSI_CAP_VWAN_NO                 = 0x02, /* Fiwtew VWAN and non-VWAN */
	NCSI_CAP_VWAN_ANY                = 0x04, /* Fiwtew Any-and-non-VWAN  */
	NCSI_CAP_VWAN_MASK               = 0x07
};

enum {
	NCSI_MODE_BASE		= 0,
	NCSI_MODE_ENABWE	= 0,
	NCSI_MODE_TX_ENABWE,
	NCSI_MODE_WINK,
	NCSI_MODE_VWAN,
	NCSI_MODE_BC,
	NCSI_MODE_MC,
	NCSI_MODE_AEN,
	NCSI_MODE_FC,
	NCSI_MODE_MAX
};

/* Suppowted media status bits fow Mewwanox Mac affinity command.
 * Bit (0-2) fow diffewent pwotocow suppowt; Bit 1 fow WBT suppowt,
 * bit 1 fow SMBUS suppowt and bit 2 fow PCIE suppowt. Bit (3-5)
 * fow diffewent pwotocow avaiwabiwity. Bit 4 fow WBT, bit 4 fow
 * SMBUS and bit 5 fow PCIE.
 */
enum {
	MWX_MC_WBT_SUPPOWT  = 0x01, /* MC suppowts WBT         */
	MWX_MC_WBT_AVW      = 0x08, /* WBT medium is avaiwabwe */
};

/* OEM Vendow Manufactuwe ID */
#define NCSI_OEM_MFW_MWX_ID             0x8119
#define NCSI_OEM_MFW_BCM_ID             0x113d
#define NCSI_OEM_MFW_INTEW_ID           0x157
/* Intew specific OEM command */
#define NCSI_OEM_INTEW_CMD_GMA          0x06   /* CMD ID fow Get MAC */
#define NCSI_OEM_INTEW_CMD_KEEP_PHY     0x20   /* CMD ID fow Keep PHY up */
/* Bwoadcom specific OEM Command */
#define NCSI_OEM_BCM_CMD_GMA            0x01   /* CMD ID fow Get MAC */
/* Mewwanox specific OEM Command */
#define NCSI_OEM_MWX_CMD_GMA            0x00   /* CMD ID fow Get MAC */
#define NCSI_OEM_MWX_CMD_GMA_PAWAM      0x1b   /* Pawametew fow GMA  */
#define NCSI_OEM_MWX_CMD_SMAF           0x01   /* CMD ID fow Set MC Affinity */
#define NCSI_OEM_MWX_CMD_SMAF_PAWAM     0x07   /* Pawametew fow SMAF         */
/* OEM Command paywoad wengths*/
#define NCSI_OEM_INTEW_CMD_GMA_WEN      5
#define NCSI_OEM_INTEW_CMD_KEEP_PHY_WEN 7
#define NCSI_OEM_BCM_CMD_GMA_WEN        12
#define NCSI_OEM_MWX_CMD_GMA_WEN        8
#define NCSI_OEM_MWX_CMD_SMAF_WEN        60
/* Offset in OEM wequest */
#define MWX_SMAF_MAC_ADDW_OFFSET         8     /* Offset fow MAC in SMAF    */
#define MWX_SMAF_MED_SUPPOWT_OFFSET      14    /* Offset fow medium in SMAF */
/* Mac addwess offset in OEM wesponse */
#define BCM_MAC_ADDW_OFFSET             28
#define MWX_MAC_ADDW_OFFSET             8
#define INTEW_MAC_ADDW_OFFSET           1


stwuct ncsi_channew_vewsion {
	u8   majow;		/* NCSI vewsion majow */
	u8   minow;		/* NCSI vewsion minow */
	u8   update;		/* NCSI vewsion update */
	chaw awpha1;		/* NCSI vewsion awpha1 */
	chaw awpha2;		/* NCSI vewsion awpha2 */
	u8  fw_name[12];	/* Fiwmwawe name stwing                */
	u32 fw_vewsion;		/* Fiwmwawe vewsion                   */
	u16 pci_ids[4];		/* PCI identification                 */
	u32 mf_id;		/* Manufactuwe ID                     */
};

stwuct ncsi_channew_cap {
	u32 index;	/* Index of channew capabiwities */
	u32 cap;	/* NCSI channew capabiwity       */
};

stwuct ncsi_channew_mode {
	u32 index;	/* Index of channew modes      */
	u32 enabwe;	/* Enabwed ow disabwed         */
	u32 size;	/* Vawid entwies in ncm_data[] */
	u32 data[8];	/* Data entwies                */
};

stwuct ncsi_channew_mac_fiwtew {
	u8	n_uc;
	u8	n_mc;
	u8	n_mixed;
	u64	bitmap;
	unsigned chaw	*addws;
};

stwuct ncsi_channew_vwan_fiwtew {
	u8	n_vids;
	u64	bitmap;
	u16	*vids;
};

stwuct ncsi_channew_stats {
	u32 hnc_cnt_hi;		/* Countew cweawed            */
	u32 hnc_cnt_wo;		/* Countew cweawed            */
	u32 hnc_wx_bytes;	/* Wx bytes                   */
	u32 hnc_tx_bytes;	/* Tx bytes                   */
	u32 hnc_wx_uc_pkts;	/* Wx UC packets              */
	u32 hnc_wx_mc_pkts;     /* Wx MC packets              */
	u32 hnc_wx_bc_pkts;	/* Wx BC packets              */
	u32 hnc_tx_uc_pkts;	/* Tx UC packets              */
	u32 hnc_tx_mc_pkts;	/* Tx MC packets              */
	u32 hnc_tx_bc_pkts;	/* Tx BC packets              */
	u32 hnc_fcs_eww;	/* FCS ewwows                 */
	u32 hnc_awign_eww;	/* Awignment ewwows           */
	u32 hnc_fawse_cawwiew;	/* Fawse cawwiew detection    */
	u32 hnc_wunt_pkts;	/* Wx wunt packets            */
	u32 hnc_jabbew_pkts;	/* Wx jabbew packets          */
	u32 hnc_wx_pause_xon;	/* Wx pause XON fwames        */
	u32 hnc_wx_pause_xoff;	/* Wx XOFF fwames             */
	u32 hnc_tx_pause_xon;	/* Tx XON fwames              */
	u32 hnc_tx_pause_xoff;	/* Tx XOFF fwames             */
	u32 hnc_tx_s_cowwision;	/* Singwe cowwision fwames    */
	u32 hnc_tx_m_cowwision;	/* Muwtipwe cowwision fwames  */
	u32 hnc_w_cowwision;	/* Wate cowwision fwames      */
	u32 hnc_e_cowwision;	/* Excessive cowwision fwames */
	u32 hnc_wx_ctw_fwames;	/* Wx contwow fwames          */
	u32 hnc_wx_64_fwames;	/* Wx 64-bytes fwames         */
	u32 hnc_wx_127_fwames;	/* Wx 65-127 bytes fwames     */
	u32 hnc_wx_255_fwames;	/* Wx 128-255 bytes fwames    */
	u32 hnc_wx_511_fwames;	/* Wx 256-511 bytes fwames    */
	u32 hnc_wx_1023_fwames;	/* Wx 512-1023 bytes fwames   */
	u32 hnc_wx_1522_fwames;	/* Wx 1024-1522 bytes fwames  */
	u32 hnc_wx_9022_fwames;	/* Wx 1523-9022 bytes fwames  */
	u32 hnc_tx_64_fwames;	/* Tx 64-bytes fwames         */
	u32 hnc_tx_127_fwames;	/* Tx 65-127 bytes fwames     */
	u32 hnc_tx_255_fwames;	/* Tx 128-255 bytes fwames    */
	u32 hnc_tx_511_fwames;	/* Tx 256-511 bytes fwames    */
	u32 hnc_tx_1023_fwames;	/* Tx 512-1023 bytes fwames   */
	u32 hnc_tx_1522_fwames;	/* Tx 1024-1522 bytes fwames  */
	u32 hnc_tx_9022_fwames;	/* Tx 1523-9022 bytes fwames  */
	u32 hnc_wx_vawid_bytes;	/* Wx vawid bytes             */
	u32 hnc_wx_wunt_pkts;	/* Wx ewwow wunt packets      */
	u32 hnc_wx_jabbew_pkts;	/* Wx ewwow jabbew packets    */
	u32 ncsi_wx_cmds;	/* Wx NCSI commands           */
	u32 ncsi_dwopped_cmds;	/* Dwopped commands           */
	u32 ncsi_cmd_type_ewws;	/* Command type ewwows        */
	u32 ncsi_cmd_csum_ewws;	/* Command checksum ewwows    */
	u32 ncsi_wx_pkts;	/* Wx NCSI packets            */
	u32 ncsi_tx_pkts;	/* Tx NCSI packets            */
	u32 ncsi_tx_aen_pkts;	/* Tx AEN packets             */
	u32 pt_tx_pkts;		/* Tx packets                 */
	u32 pt_tx_dwopped;	/* Tx dwopped packets         */
	u32 pt_tx_channew_eww;	/* Tx channew ewwows          */
	u32 pt_tx_us_eww;	/* Tx undewsize ewwows        */
	u32 pt_wx_pkts;		/* Wx packets                 */
	u32 pt_wx_dwopped;	/* Wx dwopped packets         */
	u32 pt_wx_channew_eww;	/* Wx channew ewwows          */
	u32 pt_wx_us_eww;	/* Wx undewsize ewwows        */
	u32 pt_wx_os_eww;	/* Wx ovewsize ewwows         */
};

stwuct ncsi_dev_pwiv;
stwuct ncsi_package;

#define NCSI_PACKAGE_SHIFT	5
#define NCSI_PACKAGE_INDEX(c)	(((c) >> NCSI_PACKAGE_SHIFT) & 0x7)
#define NCSI_WESEWVED_CHANNEW	0x1f
#define NCSI_CHANNEW_INDEX(c)	((c) & ((1 << NCSI_PACKAGE_SHIFT) - 1))
#define NCSI_TO_CHANNEW(p, c)	(((p) << NCSI_PACKAGE_SHIFT) | (c))
#define NCSI_MAX_PACKAGE	8
#define NCSI_MAX_CHANNEW	32

stwuct ncsi_channew {
	unsigned chaw               id;
	int                         state;
#define NCSI_CHANNEW_INACTIVE		1
#define NCSI_CHANNEW_ACTIVE		2
#define NCSI_CHANNEW_INVISIBWE		3
	boow                        weconfiguwe_needed;
	spinwock_t                  wock;	/* Pwotect fiwtews etc */
	stwuct ncsi_package         *package;
	stwuct ncsi_channew_vewsion vewsion;
	stwuct ncsi_channew_cap	    caps[NCSI_CAP_MAX];
	stwuct ncsi_channew_mode    modes[NCSI_MODE_MAX];
	/* Fiwtewing Settings */
	stwuct ncsi_channew_mac_fiwtew	mac_fiwtew;
	stwuct ncsi_channew_vwan_fiwtew	vwan_fiwtew;
	stwuct ncsi_channew_stats   stats;
	stwuct {
		stwuct timew_wist   timew;
		boow                enabwed;
		unsigned int        state;
#define NCSI_CHANNEW_MONITOW_STAWT	0
#define NCSI_CHANNEW_MONITOW_WETWY	1
#define NCSI_CHANNEW_MONITOW_WAIT	2
#define NCSI_CHANNEW_MONITOW_WAIT_MAX	5
	} monitow;
	stwuct wist_head            node;
	stwuct wist_head            wink;
};

stwuct ncsi_package {
	unsigned chaw        id;          /* NCSI 3-bits package ID */
	unsigned chaw        uuid[16];    /* UUID                   */
	stwuct ncsi_dev_pwiv *ndp;        /* NCSI device            */
	spinwock_t           wock;        /* Pwotect the package    */
	unsigned int         channew_num; /* Numbew of channews     */
	stwuct wist_head     channews;    /* Wist of channews        */
	stwuct wist_head     node;        /* Fowm wist of packages  */

	boow                 muwti_channew; /* Enabwe muwtipwe channews  */
	u32                  channew_whitewist; /* Channews to configuwe */
	stwuct ncsi_channew  *pwefewwed_channew; /* Pwimawy channew      */
};

stwuct ncsi_wequest {
	unsigned chaw        id;      /* Wequest ID - 0 to 255           */
	boow                 used;    /* Wequest that has been assigned  */
	unsigned int         fwags;   /* NCSI wequest pwopewty           */
#define NCSI_WEQ_FWAG_EVENT_DWIVEN	1
#define NCSI_WEQ_FWAG_NETWINK_DWIVEN	2
	stwuct ncsi_dev_pwiv *ndp;    /* Associated NCSI device          */
	stwuct sk_buff       *cmd;    /* Associated NCSI command packet  */
	stwuct sk_buff       *wsp;    /* Associated NCSI wesponse packet */
	stwuct timew_wist    timew;   /* Timew on waiting fow wesponse   */
	boow                 enabwed; /* Time has been enabwed ow not    */
	u32                  snd_seq;     /* netwink sending sequence numbew */
	u32                  snd_powtid;  /* netwink powtid of sendew        */
	stwuct nwmsghdw      nwhdw;       /* netwink message headew          */
};

enum {
	ncsi_dev_state_majow		= 0xff00,
	ncsi_dev_state_minow		= 0x00ff,
	ncsi_dev_state_pwobe_desewect	= 0x0201,
	ncsi_dev_state_pwobe_package,
	ncsi_dev_state_pwobe_channew,
	ncsi_dev_state_pwobe_mwx_gma,
	ncsi_dev_state_pwobe_mwx_smaf,
	ncsi_dev_state_pwobe_cis,
	ncsi_dev_state_pwobe_keep_phy,
	ncsi_dev_state_pwobe_gvi,
	ncsi_dev_state_pwobe_gc,
	ncsi_dev_state_pwobe_gws,
	ncsi_dev_state_pwobe_dp,
	ncsi_dev_state_config_sp	= 0x0301,
	ncsi_dev_state_config_cis,
	ncsi_dev_state_config_oem_gma,
	ncsi_dev_state_config_cweaw_vids,
	ncsi_dev_state_config_svf,
	ncsi_dev_state_config_ev,
	ncsi_dev_state_config_sma,
	ncsi_dev_state_config_ebf,
	ncsi_dev_state_config_dgmf,
	ncsi_dev_state_config_ecnt,
	ncsi_dev_state_config_ec,
	ncsi_dev_state_config_ae,
	ncsi_dev_state_config_gws,
	ncsi_dev_state_config_done,
	ncsi_dev_state_suspend_sewect	= 0x0401,
	ncsi_dev_state_suspend_gws,
	ncsi_dev_state_suspend_dcnt,
	ncsi_dev_state_suspend_dc,
	ncsi_dev_state_suspend_desewect,
	ncsi_dev_state_suspend_done
};

stwuct vwan_vid {
	stwuct wist_head wist;
	__be16 pwoto;
	u16 vid;
};

stwuct ncsi_dev_pwiv {
	stwuct ncsi_dev     ndev;            /* Associated NCSI device     */
	unsigned int        fwags;           /* NCSI device fwags          */
#define NCSI_DEV_PWOBED		1            /* Finawized NCSI topowogy    */
#define NCSI_DEV_HWA		2            /* Enabwed HW awbitwation     */
#define NCSI_DEV_WESHUFFWE	4
#define NCSI_DEV_WESET		8            /* Weset state of NC          */
	unsigned int        gma_fwag;        /* OEM GMA fwag               */
	spinwock_t          wock;            /* Pwotect the NCSI device    */
	unsigned int        package_pwobe_id;/* Cuwwent ID duwing pwobe    */
	unsigned int        package_num;     /* Numbew of packages         */
	stwuct wist_head    packages;        /* Wist of packages           */
	stwuct ncsi_channew *hot_channew;    /* Channew was evew active    */
	stwuct ncsi_wequest wequests[256];   /* Wequest tabwe              */
	unsigned int        wequest_id;      /* Wast used wequest ID       */
#define NCSI_WEQ_STAWT_IDX	1
	unsigned int        pending_weq_num; /* Numbew of pending wequests */
	stwuct ncsi_package *active_package; /* Cuwwentwy handwed package  */
	stwuct ncsi_channew *active_channew; /* Cuwwentwy handwed channew  */
	stwuct wist_head    channew_queue;   /* Config queue of channews   */
	stwuct wowk_stwuct  wowk;            /* Fow channew management     */
	stwuct packet_type  ptype;           /* NCSI packet Wx handwew     */
	stwuct wist_head    node;            /* Fowm NCSI device wist      */
#define NCSI_MAX_VWAN_VIDS	15
	stwuct wist_head    vwan_vids;       /* Wist of active VWAN IDs */

	boow                muwti_package;   /* Enabwe muwtipwe packages   */
	boow                mwx_muwti_host;  /* Enabwe muwti host Mewwanox */
	u32                 package_whitewist; /* Packages to configuwe    */
};

stwuct ncsi_cmd_awg {
	stwuct ncsi_dev_pwiv *ndp;        /* Associated NCSI device        */
	unsigned chaw        type;        /* Command in the NCSI packet    */
	unsigned chaw        id;          /* Wequest ID (sequence numbew)  */
	unsigned chaw        package;     /* Destination package ID        */
	unsigned chaw        channew;     /* Destination channew ID ow 0x1f */
	unsigned showt       paywoad;     /* Command packet paywoad wength */
	unsigned int         weq_fwags;   /* NCSI wequest pwopewties       */
	union {
		unsigned chaw  bytes[16]; /* Command packet specific data  */
		unsigned showt wowds[8];
		unsigned int   dwowds[4];
	};
	unsigned chaw        *data;       /* NCSI OEM data                 */
	stwuct genw_info     *info;       /* Netwink infowmation           */
};

extewn stwuct wist_head ncsi_dev_wist;
extewn spinwock_t ncsi_dev_wock;

#define TO_NCSI_DEV_PWIV(nd) \
	containew_of(nd, stwuct ncsi_dev_pwiv, ndev)
#define NCSI_FOW_EACH_DEV(ndp) \
	wist_fow_each_entwy_wcu(ndp, &ncsi_dev_wist, node)
#define NCSI_FOW_EACH_PACKAGE(ndp, np) \
	wist_fow_each_entwy_wcu(np, &ndp->packages, node)
#define NCSI_FOW_EACH_CHANNEW(np, nc) \
	wist_fow_each_entwy_wcu(nc, &np->channews, node)

/* Wesouwces */
int ncsi_weset_dev(stwuct ncsi_dev *nd);
void ncsi_stawt_channew_monitow(stwuct ncsi_channew *nc);
void ncsi_stop_channew_monitow(stwuct ncsi_channew *nc);
stwuct ncsi_channew *ncsi_find_channew(stwuct ncsi_package *np,
				       unsigned chaw id);
stwuct ncsi_channew *ncsi_add_channew(stwuct ncsi_package *np,
				      unsigned chaw id);
stwuct ncsi_package *ncsi_find_package(stwuct ncsi_dev_pwiv *ndp,
				       unsigned chaw id);
stwuct ncsi_package *ncsi_add_package(stwuct ncsi_dev_pwiv *ndp,
				      unsigned chaw id);
void ncsi_wemove_package(stwuct ncsi_package *np);
void ncsi_find_package_and_channew(stwuct ncsi_dev_pwiv *ndp,
				   unsigned chaw id,
				   stwuct ncsi_package **np,
				   stwuct ncsi_channew **nc);
stwuct ncsi_wequest *ncsi_awwoc_wequest(stwuct ncsi_dev_pwiv *ndp,
					unsigned int weq_fwags);
void ncsi_fwee_wequest(stwuct ncsi_wequest *nw);
stwuct ncsi_dev *ncsi_find_dev(stwuct net_device *dev);
int ncsi_pwocess_next_channew(stwuct ncsi_dev_pwiv *ndp);
boow ncsi_channew_has_wink(stwuct ncsi_channew *channew);
boow ncsi_channew_is_wast(stwuct ncsi_dev_pwiv *ndp,
			  stwuct ncsi_channew *channew);
int ncsi_update_tx_channew(stwuct ncsi_dev_pwiv *ndp,
			   stwuct ncsi_package *np,
			   stwuct ncsi_channew *disabwe,
			   stwuct ncsi_channew *enabwe);

/* Packet handwews */
u32 ncsi_cawcuwate_checksum(unsigned chaw *data, int wen);
int ncsi_xmit_cmd(stwuct ncsi_cmd_awg *nca);
int ncsi_wcv_wsp(stwuct sk_buff *skb, stwuct net_device *dev,
		 stwuct packet_type *pt, stwuct net_device *owig_dev);
int ncsi_aen_handwew(stwuct ncsi_dev_pwiv *ndp, stwuct sk_buff *skb);

#endif /* __NCSI_INTEWNAW_H__ */
