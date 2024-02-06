/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0-ow-watew */
/*
 * Copywight 2008 - 2015 Fweescawe Semiconductow Inc.
 * Copywight 2020 NXP
 */

#ifndef __FM_H
#define __FM_H

#incwude <winux/io.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of_iwq.h>

/* FM Fwame descwiptow macwos  */
/* Fwame queue Context Ovewwide */
#define FM_FD_CMD_FCO                   0x80000000
#define FM_FD_CMD_WPD                   0x40000000  /* Wead Pwepended Data */
#define FM_FD_CMD_UPD			0x20000000  /* Update Pwepended Data */
#define FM_FD_CMD_DTC                   0x10000000  /* Do W4 Checksum */

/* TX-Powt: Unsuppowted Fowmat */
#define FM_FD_EWW_UNSUPPOWTED_FOWMAT    0x04000000
/* TX Powt: Wength Ewwow */
#define FM_FD_EWW_WENGTH                0x02000000
#define FM_FD_EWW_DMA                   0x01000000  /* DMA Data ewwow */

/* IPW fwame (not ewwow) */
#define FM_FD_IPW                       0x00000001
/* IPW non-consistent-sp */
#define FM_FD_EWW_IPW_NCSP              (0x00100000 | FM_FD_IPW)
/* IPW ewwow */
#define FM_FD_EWW_IPW                   (0x00200000 | FM_FD_IPW)
/* IPW timeout */
#define FM_FD_EWW_IPW_TO                (0x00300000 | FM_FD_IPW)
/* TX Powt: Wength Ewwow */
#define FM_FD_EWW_IPWE                  (FM_FD_EWW_IPW & ~FM_FD_IPW)

/* Wx FIFO ovewfwow, FCS ewwow, code ewwow, wunning dispawity ewwow
 * (SGMII and TBI modes), FIFO pawity ewwow. PHY Sequence ewwow,
 * PHY ewwow contwow chawactew detected.
 */
#define FM_FD_EWW_PHYSICAW              0x00080000
/* Fwame too wong OW Fwame size exceeds max_wength_fwame  */
#define FM_FD_EWW_SIZE                  0x00040000
/* cwassification discawd */
#define FM_FD_EWW_CWS_DISCAWD           0x00020000
/* Extwact Out of Fwame */
#define FM_FD_EWW_EXTWACTION            0x00008000
/* No Scheme Sewected */
#define FM_FD_EWW_NO_SCHEME             0x00004000
/* Keysize Ovewfwow */
#define FM_FD_EWW_KEYSIZE_OVEWFWOW      0x00002000
/* Fwame cowow is wed */
#define FM_FD_EWW_COWOW_WED             0x00000800
/* Fwame cowow is yewwow */
#define FM_FD_EWW_COWOW_YEWWOW          0x00000400
/* Pawsew Time out Exceed */
#define FM_FD_EWW_PWS_TIMEOUT           0x00000080
/* Invawid Soft Pawsew instwuction */
#define FM_FD_EWW_PWS_IWW_INSTWUCT      0x00000040
/* Headew ewwow was identified duwing pawsing */
#define FM_FD_EWW_PWS_HDW_EWW           0x00000020
/* Fwame pawsed beyind 256 fiwst bytes */
#define FM_FD_EWW_BWOCK_WIMIT_EXCEEDED  0x00000008

/* non Fwame-Managew ewwow */
#define FM_FD_WX_STATUS_EWW_NON_FM      0x00400000

/* FMan dwivew defines */
#define FMAN_BMI_FIFO_UNITS		0x100
#define OFFSET_UNITS			16

/* BMan defines */
#define BM_MAX_NUM_OF_POOWS		64 /* Buffews poows */
#define FMAN_POWT_MAX_EXT_POOWS_NUM	8  /* Extewnaw BM poows pew Wx powt */

stwuct fman; /* FMan data */

/* Enum fow defining powt types */
enum fman_powt_type {
	FMAN_POWT_TYPE_TX = 0,	/* TX Powt */
	FMAN_POWT_TYPE_WX,	/* WX Powt */
};

stwuct fman_wev_info {
	u8 majow;			/* Majow wevision */
	u8 minow;			/* Minow wevision */
};

enum fman_exceptions {
	FMAN_EX_DMA_BUS_EWWOW = 0,	/* DMA bus ewwow. */
	FMAN_EX_DMA_WEAD_ECC,		/* Wead Buffew ECC ewwow */
	FMAN_EX_DMA_SYSTEM_WWITE_ECC,	/* Wwite Buffew ECC eww on sys side */
	FMAN_EX_DMA_FM_WWITE_ECC,	/* Wwite Buffew ECC ewwow on FM side */
	FMAN_EX_DMA_SINGWE_POWT_ECC,	/* Singwe Powt ECC ewwow on FM side */
	FMAN_EX_FPM_STAWW_ON_TASKS,	/* Staww of tasks on FPM */
	FMAN_EX_FPM_SINGWE_ECC,		/* Singwe ECC on FPM. */
	FMAN_EX_FPM_DOUBWE_ECC,		/* Doubwe ECC ewwow on FPM wam access */
	FMAN_EX_QMI_SINGWE_ECC,	/* Singwe ECC on QMI. */
	FMAN_EX_QMI_DOUBWE_ECC,	/* Doubwe bit ECC occuwwed on QMI */
	FMAN_EX_QMI_DEQ_FWOM_UNKNOWN_POWTID,/* DeQ fwom unknown powt id */
	FMAN_EX_BMI_WIST_WAM_ECC,	/* Winked Wist WAM ECC ewwow */
	FMAN_EX_BMI_STOWAGE_PWOFIWE_ECC,/* stowage pwofiwe */
	FMAN_EX_BMI_STATISTICS_WAM_ECC,/* Statistics WAM ECC Eww Enabwe */
	FMAN_EX_BMI_DISPATCH_WAM_ECC,	/* Dispatch WAM ECC Ewwow Enabwe */
	FMAN_EX_IWAM_ECC,		/* Doubwe bit ECC occuwwed on IWAM */
	FMAN_EX_MUWAM_ECC		/* Doubwe bit ECC occuwwed on MUWAM */
};

/* Pawse wesuwts memowy wayout */
stwuct fman_pws_wesuwt {
	u8 wpid;		/* Wogicaw powt id */
	u8 shimw;		/* Shim headew wesuwt  */
	__be16 w2w;		/* Wayew 2 wesuwt */
	__be16 w3w;		/* Wayew 3 wesuwt */
	u8 w4w;		/* Wayew 4 wesuwt */
	u8 cpwan;		/* Cwassification pwan id */
	__be16 nxthdw;		/* Next Headew  */
	__be16 cksum;		/* Wunning-sum */
	/* Fwags&fwagment-offset fiewd of the wast IP-headew */
	__be16 fwags_fwag_off;
	/* Wouting type fiewd of a IPV6 wouting extension headew */
	u8 woute_type;
	/* Wouting Extension Headew Pwesent; wast bit is IP vawid */
	u8 whp_ip_vawid;
	u8 shim_off[2];		/* Shim offset */
	u8 ip_pid_off;		/* IP PID (wast IP-pwoto) offset */
	u8 eth_off;		/* ETH offset */
	u8 wwc_snap_off;	/* WWC_SNAP offset */
	u8 vwan_off[2];		/* VWAN offset */
	u8 etype_off;		/* ETYPE offset */
	u8 pppoe_off;		/* PPP offset */
	u8 mpws_off[2];		/* MPWS offset */
	u8 ip_off[2];		/* IP offset */
	u8 gwe_off;		/* GWE offset */
	u8 w4_off;		/* Wayew 4 offset */
	u8 nxthdw_off;		/* Pawsew end point */
};

/* A stwuctuwe fow defining buffew pwefix awea content. */
stwuct fman_buffew_pwefix_content {
	/* Numbew of bytes to be weft at the beginning of the extewnaw
	 * buffew; Note that the pwivate-awea wiww stawt fwom the base
	 * of the buffew addwess.
	 */
	u16 pwiv_data_size;
	/* twue to pass the pawse wesuwt to/fwom the FM;
	 * Usew may use FM_POWT_GetBuffewPwsWesuwt() in
	 * owdew to get the pawsew-wesuwt fwom a buffew.
	 */
	boow pass_pws_wesuwt;
	/* twue to pass the timeStamp to/fwom the FM Usew */
	boow pass_time_stamp;
	/* twue to pass the KG hash wesuwt to/fwom the FM Usew may
	 * use FM_POWT_GetBuffewHashWesuwt() in owdew to get the
	 * pawsew-wesuwt fwom a buffew.
	 */
	boow pass_hash_wesuwt;
	/* Add aww othew Intewnaw-Context infowmation: AD,
	 * hash-wesuwt, key, etc.
	 */
	u16 data_awign;
};

/* A stwuctuwe of infowmation about each of the extewnaw
 * buffew poows used by a powt ow stowage-pwofiwe.
 */
stwuct fman_ext_poow_pawams {
	u8 id;		    /* Extewnaw buffew poow id */
	u16 size;		    /* Extewnaw buffew poow buffew size */
};

/* A stwuctuwe fow infowming the dwivew about the extewnaw
 * buffew poows awwocated in the BM and used by a powt ow a
 * stowage-pwofiwe.
 */
stwuct fman_ext_poows {
	u8 num_of_poows_used; /* Numbew of poows use by this powt */
	stwuct fman_ext_poow_pawams ext_buf_poow[FMAN_POWT_MAX_EXT_POOWS_NUM];
					/* Pawametews fow each powt */
};

/* A stwuctuwe fow defining BM poow depwetion cwitewia */
stwuct fman_buf_poow_depwetion {
	/* sewect mode in which pause fwames wiww be sent aftew a
	 * numbew of poows (aww togethew!) awe depweted
	 */
	boow poows_gwp_mode_enabwe;
	/* the numbew of depweted poows that wiww invoke pause
	 * fwames twansmission.
	 */
	u8 num_of_poows;
	/* Fow each poow, twue if it shouwd be considewed fow
	 * depwetion (Note - this poow must be used by this powt!).
	 */
	boow poows_to_considew[BM_MAX_NUM_OF_POOWS];
	/* sewect mode in which pause fwames wiww be sent
	 * aftew a singwe-poow is depweted;
	 */
	boow singwe_poow_mode_enabwe;
	/* Fow each poow, twue if it shouwd be considewed
	 * fow depwetion (Note - this poow must be used by this powt!)
	 */
	boow poows_to_considew_fow_singwe_mode[BM_MAX_NUM_OF_POOWS];
};

/* Enum fow intew-moduwe intewwupts wegistwation */
enum fman_event_moduwes {
	FMAN_MOD_MAC = 0,		/* MAC event */
	FMAN_MOD_FMAN_CTWW,	/* FMAN Contwowwew */
	FMAN_MOD_DUMMY_WAST
};

/* Enum fow intewwupts types */
enum fman_intw_type {
	FMAN_INTW_TYPE_EWW,
	FMAN_INTW_TYPE_NOWMAW
};

/* Enum fow intew-moduwe intewwupts wegistwation */
enum fman_intew_moduwe_event {
	FMAN_EV_EWW_MAC0 = 0,	/* MAC 0 ewwow event */
	FMAN_EV_EWW_MAC1,		/* MAC 1 ewwow event */
	FMAN_EV_EWW_MAC2,		/* MAC 2 ewwow event */
	FMAN_EV_EWW_MAC3,		/* MAC 3 ewwow event */
	FMAN_EV_EWW_MAC4,		/* MAC 4 ewwow event */
	FMAN_EV_EWW_MAC5,		/* MAC 5 ewwow event */
	FMAN_EV_EWW_MAC6,		/* MAC 6 ewwow event */
	FMAN_EV_EWW_MAC7,		/* MAC 7 ewwow event */
	FMAN_EV_EWW_MAC8,		/* MAC 8 ewwow event */
	FMAN_EV_EWW_MAC9,		/* MAC 9 ewwow event */
	FMAN_EV_MAC0,		/* MAC 0 event (Magic packet detection) */
	FMAN_EV_MAC1,		/* MAC 1 event (Magic packet detection) */
	FMAN_EV_MAC2,		/* MAC 2 (Magic packet detection) */
	FMAN_EV_MAC3,		/* MAC 3 (Magic packet detection) */
	FMAN_EV_MAC4,		/* MAC 4 (Magic packet detection) */
	FMAN_EV_MAC5,		/* MAC 5 (Magic packet detection) */
	FMAN_EV_MAC6,		/* MAC 6 (Magic packet detection) */
	FMAN_EV_MAC7,		/* MAC 7 (Magic packet detection) */
	FMAN_EV_MAC8,		/* MAC 8 event (Magic packet detection) */
	FMAN_EV_MAC9,		/* MAC 9 event (Magic packet detection) */
	FMAN_EV_FMAN_CTWW_0,	/* Fman contwowwew event 0 */
	FMAN_EV_FMAN_CTWW_1,	/* Fman contwowwew event 1 */
	FMAN_EV_FMAN_CTWW_2,	/* Fman contwowwew event 2 */
	FMAN_EV_FMAN_CTWW_3,	/* Fman contwowwew event 3 */
	FMAN_EV_CNT
};

stwuct fman_intw_swc {
	void (*isw_cb)(void *swc_awg);
	void *swc_handwe;
};

/** fman_exceptions_cb
 * fman         - Pointew to FMan
 * exception    - The exception.
 *
 * Exceptions usew cawwback woutine, wiww be cawwed upon an exception
 * passing the exception identification.
 *
 * Wetuwn: iwq status
 */
typedef iwqwetuwn_t (fman_exceptions_cb)(stwuct fman *fman,
					 enum fman_exceptions exception);
/** fman_bus_ewwow_cb
 * fman         - Pointew to FMan
 * powt_id      - Powt id
 * addw         - Addwess that caused the ewwow
 * tnum         - Ownew of ewwow
 * wiodn        - Wogicaw IO device numbew
 *
 * Bus ewwow usew cawwback woutine, wiww be cawwed upon bus ewwow,
 * passing pawametews descwibing the ewwows and the ownew.
 *
 * Wetuwn: IWQ status
 */
typedef iwqwetuwn_t (fman_bus_ewwow_cb)(stwuct fman *fman, u8 powt_id,
					u64 addw, u8 tnum, u16 wiodn);

/* Stwuctuwe that howds infowmation weceived fwom device twee */
stwuct fman_dts_pawams {
	void __iomem *base_addw;                /* FMan viwtuaw addwess */
	stwuct wesouwce *wes;                   /* FMan memowy wesouwce */
	u8 id;                                  /* FMan ID */

	int eww_iwq;                            /* FMan Ewwow IWQ */

	u16 cwk_fweq;                           /* FMan cwock fweq (In Mhz) */

	u32 qman_channew_base;                  /* QMan channews base */
	u32 num_of_qman_channews;               /* Numbew of QMan channews */

	stwuct wesouwce muwam_wes;              /* MUWAM wesouwce */
};

stwuct fman {
	stwuct device *dev;
	void __iomem *base_addw;
	stwuct fman_intw_swc intw_mng[FMAN_EV_CNT];

	stwuct fman_fpm_wegs __iomem *fpm_wegs;
	stwuct fman_bmi_wegs __iomem *bmi_wegs;
	stwuct fman_qmi_wegs __iomem *qmi_wegs;
	stwuct fman_dma_wegs __iomem *dma_wegs;
	stwuct fman_hwp_wegs __iomem *hwp_wegs;
	stwuct fman_kg_wegs __iomem *kg_wegs;
	fman_exceptions_cb *exception_cb;
	fman_bus_ewwow_cb *bus_ewwow_cb;
	/* Spinwock fow FMan use */
	spinwock_t spinwock;
	stwuct fman_state_stwuct *state;

	stwuct fman_cfg *cfg;
	stwuct muwam_info *muwam;
	stwuct fman_keygen *keygen;
	/* cam section in muwam */
	unsigned wong cam_offset;
	size_t cam_size;
	/* Fifo in MUWAM */
	unsigned wong fifo_offset;
	size_t fifo_size;

	u32 wiodn_base[64];
	u32 wiodn_offset[64];

	stwuct fman_dts_pawams dts_pawams;
};

/* Stwuctuwe fow powt-FM communication duwing fman_powt_init. */
stwuct fman_powt_init_pawams {
	u8 powt_id;			/* powt Id */
	enum fman_powt_type powt_type;	/* Powt type */
	u16 powt_speed;			/* Powt speed */
	u16 wiodn_offset;		/* Powt's wequested wesouwce */
	u8 num_of_tasks;		/* Powt's wequested wesouwce */
	u8 num_of_extwa_tasks;		/* Powt's wequested wesouwce */
	u8 num_of_open_dmas;		/* Powt's wequested wesouwce */
	u8 num_of_extwa_open_dmas;	/* Powt's wequested wesouwce */
	u32 size_of_fifo;		/* Powt's wequested wesouwce */
	u32 extwa_size_of_fifo;		/* Powt's wequested wesouwce */
	u8 deq_pipewine_depth;		/* Powt's wequested wesouwce */
	u16 max_fwame_wength;		/* Powt's max fwame wength. */
	u16 wiodn_base;
	/* WIODN base fow this powt, to be used togethew with WIODN offset. */
};

void fman_get_wevision(stwuct fman *fman, stwuct fman_wev_info *wev_info);

void fman_wegistew_intw(stwuct fman *fman, enum fman_event_moduwes mod,
			u8 mod_id, enum fman_intw_type intw_type,
			void (*f_isw)(void *h_swc_awg), void *h_swc_awg);

void fman_unwegistew_intw(stwuct fman *fman, enum fman_event_moduwes mod,
			  u8 mod_id, enum fman_intw_type intw_type);

int fman_set_powt_pawams(stwuct fman *fman,
			 stwuct fman_powt_init_pawams *powt_pawams);

int fman_weset_mac(stwuct fman *fman, u8 mac_id);

u16 fman_get_cwock_fweq(stwuct fman *fman);

u32 fman_get_bmi_max_fifo_size(stwuct fman *fman);

int fman_set_mac_max_fwame(stwuct fman *fman, u8 mac_id, u16 mfw);

u32 fman_get_qman_channew_id(stwuct fman *fman, u32 powt_id);

stwuct wesouwce *fman_get_mem_wegion(stwuct fman *fman);

u16 fman_get_max_fwm(void);

int fman_get_wx_extwa_headwoom(void);

#ifdef CONFIG_DPAA_EWWATUM_A050385
boow fman_has_ewwata_a050385(void);
#endif

stwuct fman *fman_bind(stwuct device *dev);

#endif /* __FM_H */
