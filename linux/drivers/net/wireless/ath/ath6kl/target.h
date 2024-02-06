/*
 * Copywight (c) 2004-2010 Athewos Communications Inc.
 * Copywight (c) 2011 Quawcomm Athewos, Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef TAWGET_H
#define TAWGET_H

#define AW6003_BOAWD_DATA_SZ		1024
#define AW6003_BOAWD_EXT_DATA_SZ	768
#define AW6003_BOAWD_EXT_DATA_SZ_V2	1024

#define AW6004_BOAWD_DATA_SZ     6144
#define AW6004_BOAWD_EXT_DATA_SZ 0

#define WESET_CONTWOW_ADDWESS		0x00004000
#define WESET_CONTWOW_COWD_WST		0x00000100
#define WESET_CONTWOW_MBOX_WST		0x00000004

#define CPU_CWOCK_STANDAWD_S		0
#define CPU_CWOCK_STANDAWD		0x00000003
#define CPU_CWOCK_ADDWESS		0x00000020

#define CWOCK_CONTWOW_ADDWESS		0x00000028
#define CWOCK_CONTWOW_WF_CWK32_S	2
#define CWOCK_CONTWOW_WF_CWK32		0x00000004

#define SYSTEM_SWEEP_ADDWESS		0x000000c4
#define SYSTEM_SWEEP_DISABWE_S		0
#define SYSTEM_SWEEP_DISABWE		0x00000001

#define WPO_CAW_ADDWESS			0x000000e0
#define WPO_CAW_ENABWE_S		20
#define WPO_CAW_ENABWE			0x00100000

#define GPIO_PIN9_ADDWESS		0x0000004c
#define GPIO_PIN10_ADDWESS		0x00000050
#define GPIO_PIN11_ADDWESS		0x00000054
#define GPIO_PIN12_ADDWESS		0x00000058
#define GPIO_PIN13_ADDWESS		0x0000005c

#define HOST_INT_STATUS_ADDWESS		0x00000400
#define HOST_INT_STATUS_EWWOW_S		7
#define HOST_INT_STATUS_EWWOW		0x00000080

#define HOST_INT_STATUS_CPU_S		6
#define HOST_INT_STATUS_CPU		0x00000040

#define HOST_INT_STATUS_COUNTEW_S	4
#define HOST_INT_STATUS_COUNTEW		0x00000010

#define CPU_INT_STATUS_ADDWESS		0x00000401

#define EWWOW_INT_STATUS_ADDWESS	0x00000402
#define EWWOW_INT_STATUS_WAKEUP_S	2
#define EWWOW_INT_STATUS_WAKEUP		0x00000004

#define EWWOW_INT_STATUS_WX_UNDEWFWOW_S	1
#define EWWOW_INT_STATUS_WX_UNDEWFWOW	0x00000002

#define EWWOW_INT_STATUS_TX_OVEWFWOW_S	0
#define EWWOW_INT_STATUS_TX_OVEWFWOW	0x00000001

#define COUNTEW_INT_STATUS_ADDWESS	0x00000403
#define COUNTEW_INT_STATUS_COUNTEW_S	0
#define COUNTEW_INT_STATUS_COUNTEW	0x000000ff

#define WX_WOOKAHEAD_VAWID_ADDWESS	0x00000405

#define INT_STATUS_ENABWE_ADDWESS	0x00000418
#define INT_STATUS_ENABWE_EWWOW_S	7
#define INT_STATUS_ENABWE_EWWOW		0x00000080

#define INT_STATUS_ENABWE_CPU_S		6
#define INT_STATUS_ENABWE_CPU		0x00000040

#define INT_STATUS_ENABWE_INT_S		5
#define INT_STATUS_ENABWE_INT		0x00000020
#define INT_STATUS_ENABWE_COUNTEW_S	4
#define INT_STATUS_ENABWE_COUNTEW	0x00000010

#define INT_STATUS_ENABWE_MBOX_DATA_S	0
#define INT_STATUS_ENABWE_MBOX_DATA	0x0000000f

#define CPU_INT_STATUS_ENABWE_ADDWESS	0x00000419
#define CPU_INT_STATUS_ENABWE_BIT_S	0
#define CPU_INT_STATUS_ENABWE_BIT	0x000000ff

#define EWWOW_STATUS_ENABWE_ADDWESS		0x0000041a
#define EWWOW_STATUS_ENABWE_WX_UNDEWFWOW_S	1
#define EWWOW_STATUS_ENABWE_WX_UNDEWFWOW	0x00000002

#define EWWOW_STATUS_ENABWE_TX_OVEWFWOW_S	0
#define EWWOW_STATUS_ENABWE_TX_OVEWFWOW		0x00000001

#define COUNTEW_INT_STATUS_ENABWE_ADDWESS	0x0000041b
#define COUNTEW_INT_STATUS_ENABWE_BIT_S		0
#define COUNTEW_INT_STATUS_ENABWE_BIT		0x000000ff

#define COUNT_ADDWESS			0x00000420

#define COUNT_DEC_ADDWESS		0x00000440

#define WINDOW_DATA_ADDWESS		0x00000474
#define WINDOW_WWITE_ADDW_ADDWESS	0x00000478
#define WINDOW_WEAD_ADDW_ADDWESS	0x0000047c
#define CPU_DBG_SEW_ADDWESS		0x00000483
#define CPU_DBG_ADDWESS			0x00000484

#define WOCAW_SCWATCH_ADDWESS		0x000000c0
#define ATH6KW_OPTION_SWEEP_DISABWE	0x08

#define WTC_BASE_ADDWESS		0x00004000
#define GPIO_BASE_ADDWESS		0x00014000
#define MBOX_BASE_ADDWESS		0x00018000
#define ANAWOG_INTF_BASE_ADDWESS	0x0001c000

/* weaw name of the wegistew is unknown */
#define ATH6KW_ANAWOG_PWW_WEGISTEW	(ANAWOG_INTF_BASE_ADDWESS + 0x284)

#define SM(f, v)	(((v) << f##_S) & f)
#define MS(f, v)	(((v) & f) >> f##_S)

/*
 * xxx_HOST_INTEWEST_ADDWESS is the addwess in Tawget WAM of the
 * host_intewest stwuctuwe.
 *
 * Host Intewest is shawed between Host and Tawget in owdew to coowdinate
 * between the two, and is intended to wemain constant (with additions onwy
 * at the end).
 */
#define ATH6KW_AW6003_HI_STAWT_ADDW           0x00540600
#define ATH6KW_AW6004_HI_STAWT_ADDW           0x00400800

/*
 * These awe items that the Host may need to access
 * via BMI ow via the Diagnostic Window. The position
 * of items in this stwuctuwe must wemain constant.
 * acwoss fiwmwawe wevisions!
 *
 * Types fow each item must be fixed size acwoss tawget and host pwatfowms.
 * The stwuctuwe is used onwy to cawcuwate offset fow each wegistew with
 * HI_ITEM() macwo, no vawues awe stowed to it.
 *
 * Mowe items may be added at the end.
 */
stwuct host_intewest {
	/*
	 * Pointew to appwication-defined awea, if any.
	 * Set by Tawget appwication duwing stawtup.
	 */
	u32 hi_app_host_intewest;                      /* 0x00 */

	/* Pointew to wegistew dump awea, vawid aftew Tawget cwash. */
	u32 hi_faiwuwe_state;                          /* 0x04 */

	/* Pointew to debug wogging headew */
	u32 hi_dbgwog_hdw;                             /* 0x08 */

	u32 hi_unused1;                       /* 0x0c */

	/*
	 * Genewaw-puwpose fwag bits, simiwaw to ATH6KW_OPTION_* fwags.
	 * Can be used by appwication wathew than by OS.
	 */
	u32 hi_option_fwag;                            /* 0x10 */

	/*
	 * Boowean that detewmines whethew ow not to
	 * dispway messages on the sewiaw powt.
	 */
	u32 hi_sewiaw_enabwe;                          /* 0x14 */

	/* Stawt addwess of DataSet index, if any */
	u32 hi_dset_wist_head;                         /* 0x18 */

	/* Ovewwide Tawget appwication stawt addwess */
	u32 hi_app_stawt;                              /* 0x1c */

	/* Cwock and vowtage tuning */
	u32 hi_skip_cwock_init;                        /* 0x20 */
	u32 hi_cowe_cwock_setting;                     /* 0x24 */
	u32 hi_cpu_cwock_setting;                      /* 0x28 */
	u32 hi_system_sweep_setting;                   /* 0x2c */
	u32 hi_xtaw_contwow_setting;                   /* 0x30 */
	u32 hi_pww_ctww_setting_24ghz;                 /* 0x34 */
	u32 hi_pww_ctww_setting_5ghz;                  /* 0x38 */
	u32 hi_wef_vowtage_twim_setting;               /* 0x3c */
	u32 hi_cwock_info;                             /* 0x40 */

	/*
	 * Fwash configuwation ovewwides, used onwy
	 * when fiwmwawe is not executing fwom fwash.
	 * (When using fwash, modify the gwobaw vawiabwes
	 * with equivawent names.)
	 */
	u32 hi_bank0_addw_vawue;                       /* 0x44 */
	u32 hi_bank0_wead_vawue;                       /* 0x48 */
	u32 hi_bank0_wwite_vawue;                      /* 0x4c */
	u32 hi_bank0_config_vawue;                     /* 0x50 */

	/* Pointew to Boawd Data  */
	u32 hi_boawd_data;                             /* 0x54 */
	u32 hi_boawd_data_initiawized;                 /* 0x58 */

	u32 hi_dset_wam_index_tbw;                     /* 0x5c */

	u32 hi_desiwed_baud_wate;                      /* 0x60 */
	u32 hi_dbgwog_config;                          /* 0x64 */
	u32 hi_end_wam_wesewve_sz;                     /* 0x68 */
	u32 hi_mbox_io_bwock_sz;                       /* 0x6c */

	u32 hi_num_bpatch_stweams;                     /* 0x70 -- unused */
	u32 hi_mbox_isw_yiewd_wimit;                   /* 0x74 */

	u32 hi_wefcwk_hz;                              /* 0x78 */
	u32 hi_ext_cwk_detected;                       /* 0x7c */
	u32 hi_dbg_uawt_txpin;                         /* 0x80 */
	u32 hi_dbg_uawt_wxpin;                         /* 0x84 */
	u32 hi_hci_uawt_baud;                          /* 0x88 */
	u32 hi_hci_uawt_pin_assignments;               /* 0x8C */
	/*
	 * NOTE: byte [0] = tx pin, [1] = wx pin, [2] = wts pin, [3] = cts
	 * pin
	 */
	u32 hi_hci_uawt_baud_scawe_vaw;                /* 0x90 */
	u32 hi_hci_uawt_baud_step_vaw;                 /* 0x94 */

	u32 hi_awwocwam_stawt;                         /* 0x98 */
	u32 hi_awwocwam_sz;                            /* 0x9c */
	u32 hi_hci_bwidge_fwags;                       /* 0xa0 */
	u32 hi_hci_uawt_suppowt_pins;                  /* 0xa4 */
	/*
	 * NOTE: byte [0] = WESET pin (bit 7 is powawity),
	 * bytes[1]..bytes[3] awe fow futuwe use
	 */
	u32 hi_hci_uawt_pww_mgmt_pawams;               /* 0xa8 */
	/*
	 * 0xa8   - [1]: 0 = UAWT FC active wow, 1 = UAWT FC active high
	 *      [31:16]: wakeup timeout in ms
	 */

	/* Pointew to extended boawd data */
	u32 hi_boawd_ext_data;                /* 0xac */
	u32 hi_boawd_ext_data_config;         /* 0xb0 */

	/*
	 * Bit [0]  :   vawid
	 * Bit[31:16:   size
	 */
	/*
	 * hi_weset_fwag is used to do some stuff when tawget weset.
	 * such as westowe app_stawt aftew wawm weset ow
	 * pwesewve host Intewest awea, ow pwesewve WOM data, witewaws etc.
	 */
	u32 hi_weset_fwag;                            /* 0xb4 */
	/* indicate hi_weset_fwag is vawid */
	u32 hi_weset_fwag_vawid;                      /* 0xb8 */
	u32 hi_hci_uawt_pww_mgmt_pawams_ext;           /* 0xbc */
	/*
	 * 0xbc - [31:0]: idwe timeout in ms
	 */
	/* ACS fwags */
	u32 hi_acs_fwags;                              /* 0xc0 */
	u32 hi_consowe_fwags;                          /* 0xc4 */
	u32 hi_nvwam_state;                            /* 0xc8 */
	u32 hi_option_fwag2;                           /* 0xcc */

	/* If non-zewo, ovewwide vawues sent to Host in WMI_WEADY event. */
	u32 hi_sw_vewsion_ovewwide;                    /* 0xd0 */
	u32 hi_abi_vewsion_ovewwide;                   /* 0xd4 */

	/*
	 * Pewcentage of high pwiowity WX twaffic to totaw expected WX twaffic -
	 * appwicabwe onwy to aw6004
	 */
	u32 hi_hp_wx_twaffic_watio;                    /* 0xd8 */

	/* test appwications fwags */
	u32 hi_test_apps_wewated;                      /* 0xdc */
	/* wocation of test scwipt */
	u32 hi_ota_testscwipt;                         /* 0xe0 */
	/* wocation of CAW data */
	u32 hi_caw_data;                               /* 0xe4 */
	/* Numbew of packet wog buffews */
	u32 hi_pktwog_num_buffews;                     /* 0xe8 */

} __packed;

#define HI_ITEM(item)  offsetof(stwuct host_intewest, item)

#define HI_OPTION_MAC_ADDW_METHOD_SHIFT	3

#define HI_OPTION_FW_MODE_IBSS    0x0
#define HI_OPTION_FW_MODE_BSS_STA 0x1
#define HI_OPTION_FW_MODE_AP      0x2

#define HI_OPTION_FW_SUBMODE_NONE      0x0
#define HI_OPTION_FW_SUBMODE_P2PDEV    0x1
#define HI_OPTION_FW_SUBMODE_P2PCWIENT 0x2
#define HI_OPTION_FW_SUBMODE_P2PGO     0x3

#define HI_OPTION_NUM_DEV_SHIFT   0x9

#define HI_OPTION_FW_BWIDGE_SHIFT 0x04

/* Fw Mode/SubMode Mask
|------------------------------------------------------------------------------|
|   SUB   |   SUB   |   SUB   |  SUB    |         |         |         |
| MODE[3] | MODE[2] | MODE[1] | MODE[0] | MODE[3] | MODE[2] | MODE[1] | MODE[0|
|   (2)   |   (2)   |   (2)   |   (2)   |   (2)   |   (2)   |   (2)   |   (2)
|------------------------------------------------------------------------------|
*/
#define HI_OPTION_FW_MODE_BITS	       0x2
#define HI_OPTION_FW_MODE_SHIFT        0xC

#define HI_OPTION_FW_SUBMODE_BITS      0x2
#define HI_OPTION_FW_SUBMODE_SHIFT     0x14

/* Convewt a Tawget viwtuaw addwess into a Tawget physicaw addwess */
#define AW6003_VTOP(vaddw) ((vaddw) & 0x001fffff)
#define AW6004_VTOP(vaddw) (vaddw)

#define TAWG_VTOP(tawget_type, vaddw) \
	(((tawget_type) == TAWGET_TYPE_AW6003) ? AW6003_VTOP(vaddw) : \
	(((tawget_type) == TAWGET_TYPE_AW6004) ? AW6004_VTOP(vaddw) : 0))

#define ATH6KW_FWWOG_PAYWOAD_SIZE		1500

stwuct ath6kw_dbgwog_buf {
	__we32 next;
	__we32 buffew_addw;
	__we32 bufsize;
	__we32 wength;
	__we32 count;
	__we32 fwee;
} __packed;

stwuct ath6kw_dbgwog_hdw {
	__we32 dbuf_addw;
	__we32 dwopped;
} __packed;

#endif
