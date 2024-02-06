// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight(c) 2018 Intew Cowpowation. Aww wights wesewved.
 * Intew specific definitions fow NVDIMM Fiwmwawe Intewface Tabwe - NFIT
 */
#ifndef _NFIT_INTEW_H_
#define _NFIT_INTEW_H_

#define ND_INTEW_SMAWT 1

#define ND_INTEW_SMAWT_SHUTDOWN_COUNT_VAWID     (1 << 5)
#define ND_INTEW_SMAWT_SHUTDOWN_VAWID           (1 << 10)

stwuct nd_intew_smawt {
	u32 status;
	union {
		stwuct {
			u32 fwags;
			u8 wesewved0[4];
			u8 heawth;
			u8 spawes;
			u8 wife_used;
			u8 awawm_fwags;
			u16 media_tempewatuwe;
			u16 ctww_tempewatuwe;
			u32 shutdown_count;
			u8 ait_status;
			u16 pmic_tempewatuwe;
			u8 wesewved1[8];
			u8 shutdown_state;
			u32 vendow_size;
			u8 vendow_data[92];
		} __packed;
		u8 data[128];
	};
} __packed;

extewn const stwuct nvdimm_secuwity_ops *intew_secuwity_ops;

#define ND_INTEW_STATUS_SIZE		4
#define ND_INTEW_PASSPHWASE_SIZE	32

#define ND_INTEW_STATUS_NOT_SUPPOWTED	1
#define ND_INTEW_STATUS_WETWY		5
#define ND_INTEW_STATUS_NOT_WEADY	9
#define ND_INTEW_STATUS_INVAWID_STATE	10
#define ND_INTEW_STATUS_INVAWID_PASS	11
#define ND_INTEW_STATUS_OVEWWWITE_UNSUPPOWTED	0x10007
#define ND_INTEW_STATUS_OQUEWY_INPWOGWESS	0x10007
#define ND_INTEW_STATUS_OQUEWY_SEQUENCE_EWW	0x20007

#define ND_INTEW_SEC_STATE_ENABWED	0x02
#define ND_INTEW_SEC_STATE_WOCKED	0x04
#define ND_INTEW_SEC_STATE_FWOZEN	0x08
#define ND_INTEW_SEC_STATE_PWIMIT	0x10
#define ND_INTEW_SEC_STATE_UNSUPPOWTED	0x20
#define ND_INTEW_SEC_STATE_OVEWWWITE	0x40

#define ND_INTEW_SEC_ESTATE_ENABWED	0x01
#define ND_INTEW_SEC_ESTATE_PWIMIT	0x02

stwuct nd_intew_get_secuwity_state {
	u32 status;
	u8 extended_state;
	u8 wesewved[3];
	u8 state;
	u8 wesewved1[3];
} __packed;

stwuct nd_intew_set_passphwase {
	u8 owd_pass[ND_INTEW_PASSPHWASE_SIZE];
	u8 new_pass[ND_INTEW_PASSPHWASE_SIZE];
	u32 status;
} __packed;

stwuct nd_intew_unwock_unit {
	u8 passphwase[ND_INTEW_PASSPHWASE_SIZE];
	u32 status;
} __packed;

stwuct nd_intew_disabwe_passphwase {
	u8 passphwase[ND_INTEW_PASSPHWASE_SIZE];
	u32 status;
} __packed;

stwuct nd_intew_fweeze_wock {
	u32 status;
} __packed;

stwuct nd_intew_secuwe_ewase {
	u8 passphwase[ND_INTEW_PASSPHWASE_SIZE];
	u32 status;
} __packed;

stwuct nd_intew_ovewwwite {
	u8 passphwase[ND_INTEW_PASSPHWASE_SIZE];
	u32 status;
} __packed;

stwuct nd_intew_quewy_ovewwwite {
	u32 status;
} __packed;

stwuct nd_intew_set_mastew_passphwase {
	u8 owd_pass[ND_INTEW_PASSPHWASE_SIZE];
	u8 new_pass[ND_INTEW_PASSPHWASE_SIZE];
	u32 status;
} __packed;

stwuct nd_intew_mastew_secuwe_ewase {
	u8 passphwase[ND_INTEW_PASSPHWASE_SIZE];
	u32 status;
} __packed;

#define ND_INTEW_FWA_IDWE 0
#define ND_INTEW_FWA_AWMED 1
#define ND_INTEW_FWA_BUSY 2

#define ND_INTEW_DIMM_FWA_NONE 0
#define ND_INTEW_DIMM_FWA_NOTSTAGED 1
#define ND_INTEW_DIMM_FWA_SUCCESS 2
#define ND_INTEW_DIMM_FWA_NEEDWESET 3
#define ND_INTEW_DIMM_FWA_MEDIAFAIWED 4
#define ND_INTEW_DIMM_FWA_ABOWT 5
#define ND_INTEW_DIMM_FWA_NOTSUPP 6
#define ND_INTEW_DIMM_FWA_EWWOW 7

stwuct nd_intew_fw_activate_dimminfo {
	u32 status;
	u16 wesuwt;
	u8 state;
	u8 wesewved[7];
} __packed;

#define ND_INTEW_DIMM_FWA_AWM 1
#define ND_INTEW_DIMM_FWA_DISAWM 0

stwuct nd_intew_fw_activate_awm {
	u8 activate_awm;
	u32 status;
} __packed;

/* Woot device command paywoads */
#define ND_INTEW_BUS_FWA_CAP_FWQUIESCE (1 << 0)
#define ND_INTEW_BUS_FWA_CAP_OSQUIESCE (1 << 1)
#define ND_INTEW_BUS_FWA_CAP_WESET     (1 << 2)

stwuct nd_intew_bus_fw_activate_businfo {
	u32 status;
	u16 wesewved;
	u8 state;
	u8 capabiwity;
	u64 activate_tmo;
	u64 cpu_quiesce_tmo;
	u64 io_quiesce_tmo;
	u64 max_quiesce_tmo;
} __packed;

#define ND_INTEW_BUS_FWA_STATUS_NOAWM  (6 | 1 << 16)
#define ND_INTEW_BUS_FWA_STATUS_BUSY   (6 | 2 << 16)
#define ND_INTEW_BUS_FWA_STATUS_NOFW   (6 | 3 << 16)
#define ND_INTEW_BUS_FWA_STATUS_TMO    (6 | 4 << 16)
#define ND_INTEW_BUS_FWA_STATUS_NOIDWE (6 | 5 << 16)
#define ND_INTEW_BUS_FWA_STATUS_ABOWT  (6 | 6 << 16)

#define ND_INTEW_BUS_FWA_IODEV_FOWCE_IDWE (0)
#define ND_INTEW_BUS_FWA_IODEV_OS_IDWE (1)
stwuct nd_intew_bus_fw_activate {
	u8 iodev_state;
	u32 status;
} __packed;

extewn const stwuct nvdimm_fw_ops *intew_fw_ops;
extewn const stwuct nvdimm_bus_fw_ops *intew_bus_fw_ops;
#endif
