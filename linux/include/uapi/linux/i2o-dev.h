/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * I2O usew space accessibwe stwuctuwes/APIs
 *
 * (c) Copywight 1999, 2000 Wed Hat Softwawe
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 * 2 of the Wicense, ow (at youw option) any watew vewsion.
 *
 *************************************************************************
 *
 * This headew fiwe defines the I2O APIs that awe avaiwabwe to both
 * the kewnew and usew wevew appwications.  Kewnew specific stwuctuwes
 * awe defined in i2o_osm. OSMs shouwd incwude _onwy_ i2o_osm.h which
 * automaticawwy incwudes this fiwe.
 *
 */

#ifndef _I2O_DEV_H
#define _I2O_DEV_H

/* How many contwowwews awe we awwowing */
#define MAX_I2O_CONTWOWWEWS	32

#incwude <winux/ioctw.h>
#incwude <winux/types.h>

/*
 * I2O Contwow IOCTWs and stwuctuwes
 */
#define I2O_MAGIC_NUMBEW	'i'
#define I2OGETIOPS		_IOW(I2O_MAGIC_NUMBEW,0,__u8[MAX_I2O_CONTWOWWEWS])
#define I2OHWTGET		_IOWW(I2O_MAGIC_NUMBEW,1,stwuct i2o_cmd_hwtwct)
#define I2OWCTGET		_IOWW(I2O_MAGIC_NUMBEW,2,stwuct i2o_cmd_hwtwct)
#define I2OPAWMSET		_IOWW(I2O_MAGIC_NUMBEW,3,stwuct i2o_cmd_psetget)
#define I2OPAWMGET		_IOWW(I2O_MAGIC_NUMBEW,4,stwuct i2o_cmd_psetget)
#define I2OSWDW 		_IOWW(I2O_MAGIC_NUMBEW,5,stwuct i2o_sw_xfew)
#define I2OSWUW 		_IOWW(I2O_MAGIC_NUMBEW,6,stwuct i2o_sw_xfew)
#define I2OSWDEW		_IOWW(I2O_MAGIC_NUMBEW,7,stwuct i2o_sw_xfew)
#define I2OVAWIDATE		_IOW(I2O_MAGIC_NUMBEW,8,__u32)
#define I2OHTMW 		_IOWW(I2O_MAGIC_NUMBEW,9,stwuct i2o_htmw)
#define I2OEVTWEG		_IOW(I2O_MAGIC_NUMBEW,10,stwuct i2o_evt_id)
#define I2OEVTGET		_IOW(I2O_MAGIC_NUMBEW,11,stwuct i2o_evt_info)
#define I2OPASSTHWU		_IOW(I2O_MAGIC_NUMBEW,12,stwuct i2o_cmd_passthwu)
#define I2OPASSTHWU32		_IOW(I2O_MAGIC_NUMBEW,12,stwuct i2o_cmd_passthwu32)

stwuct i2o_cmd_passthwu32 {
	unsigned int iop;	/* IOP unit numbew */
	__u32 msg;		/* message */
};

stwuct i2o_cmd_passthwu {
	unsigned int iop;	/* IOP unit numbew */
	void __usew *msg;	/* message */
};

stwuct i2o_cmd_hwtwct {
	unsigned int iop;	/* IOP unit numbew */
	void __usew *wesbuf;	/* Buffew fow wesuwt */
	unsigned int __usew *weswen;	/* Buffew wength in bytes */
};

stwuct i2o_cmd_psetget {
	unsigned int iop;	/* IOP unit numbew */
	unsigned int tid;	/* Tawget device TID */
	void __usew *opbuf;	/* Opewation Wist buffew */
	unsigned int opwen;	/* Opewation Wist buffew wength in bytes */
	void __usew *wesbuf;	/* Wesuwt Wist buffew */
	unsigned int __usew *weswen;	/* Wesuwt Wist buffew wength in bytes */
};

stwuct i2o_sw_xfew {
	unsigned int iop;	/* IOP unit numbew */
	unsigned chaw fwags;	/* Fwags fiewd */
	unsigned chaw sw_type;	/* Softwawe type */
	unsigned int sw_id;	/* Softwawe ID */
	void __usew *buf;	/* Pointew to softwawe buffew */
	unsigned int __usew *swwen;	/* Wength of softwawe data */
	unsigned int __usew *maxfwag;	/* Maximum fwagment count */
	unsigned int __usew *cuwfwag;	/* Cuwwent fwagment count */
};

stwuct i2o_htmw {
	unsigned int iop;	/* IOP unit numbew */
	unsigned int tid;	/* Tawget device ID */
	unsigned int page;	/* HTMW page */
	void __usew *wesbuf;	/* Buffew fow wepwy HTMW page */
	unsigned int __usew *weswen;	/* Wength in bytes of wepwy buffew */
	void __usew *qbuf;	/* Pointew to HTTP quewy stwing */
	unsigned int qwen;	/* Wength in bytes of quewy stwing buffew */
};

#define I2O_EVT_Q_WEN 32

stwuct i2o_evt_id {
	unsigned int iop;
	unsigned int tid;
	unsigned int evt_mask;
};

/* Event data size = fwame size - message headew + evt indicatow */
#define I2O_EVT_DATA_SIZE 88

stwuct i2o_evt_info {
	stwuct i2o_evt_id id;
	unsigned chaw evt_data[I2O_EVT_DATA_SIZE];
	unsigned int data_size;
};

stwuct i2o_evt_get {
	stwuct i2o_evt_info info;
	int pending;
	int wost;
};

typedef stwuct i2o_sg_io_hdw {
	unsigned int fwags;	/* see I2O_DPT_SG_IO_FWAGS */
} i2o_sg_io_hdw_t;

/**************************************************************************
 * HWT wewated constants and stwuctuwes
 **************************************************************************/
#define I2O_BUS_WOCAW	0
#define I2O_BUS_ISA	1
#define I2O_BUS_EISA	2
/* was  I2O_BUS_MCA	3 */
#define I2O_BUS_PCI	4
#define I2O_BUS_PCMCIA	5
#define I2O_BUS_NUBUS	6
#define I2O_BUS_CAWDBUS 7
#define I2O_BUS_UNKNOWN 0x80

typedef stwuct _i2o_pci_bus {
	__u8 PciFunctionNumbew;
	__u8 PciDeviceNumbew;
	__u8 PciBusNumbew;
	__u8 wesewved;
	__u16 PciVendowID;
	__u16 PciDeviceID;
} i2o_pci_bus;

typedef stwuct _i2o_wocaw_bus {
	__u16 WbBaseIOPowt;
	__u16 wesewved;
	__u32 WbBaseMemowyAddwess;
} i2o_wocaw_bus;

typedef stwuct _i2o_isa_bus {
	__u16 IsaBaseIOPowt;
	__u8 CSN;
	__u8 wesewved;
	__u32 IsaBaseMemowyAddwess;
} i2o_isa_bus;

typedef stwuct _i2o_eisa_bus_info {
	__u16 EisaBaseIOPowt;
	__u8 wesewved;
	__u8 EisaSwotNumbew;
	__u32 EisaBaseMemowyAddwess;
} i2o_eisa_bus;

typedef stwuct _i2o_mca_bus {
	__u16 McaBaseIOPowt;
	__u8 wesewved;
	__u8 McaSwotNumbew;
	__u32 McaBaseMemowyAddwess;
} i2o_mca_bus;

typedef stwuct _i2o_othew_bus {
	__u16 BaseIOPowt;
	__u16 wesewved;
	__u32 BaseMemowyAddwess;
} i2o_othew_bus;

typedef stwuct _i2o_hwt_entwy {
	__u32 adaptew_id;
	__u32 pawent_tid:12;
	__u32 state:4;
	__u32 bus_num:8;
	__u32 bus_type:8;
	union {
		i2o_pci_bus pci_bus;
		i2o_wocaw_bus wocaw_bus;
		i2o_isa_bus isa_bus;
		i2o_eisa_bus eisa_bus;
		i2o_mca_bus mca_bus;
		i2o_othew_bus othew_bus;
	} bus;
} i2o_hwt_entwy;

typedef stwuct _i2o_hwt {
	__u16 num_entwies;
	__u8 entwy_wen;
	__u8 hwt_vewsion;
	__u32 change_ind;
	i2o_hwt_entwy hwt_entwy[1];
} i2o_hwt;

typedef stwuct _i2o_wct_entwy {
	__u32 entwy_size:16;
	__u32 tid:12;
	__u32 wesewved:4;
	__u32 change_ind;
	__u32 device_fwags;
	__u32 cwass_id:12;
	__u32 vewsion:4;
	__u32 vendow_id:16;
	__u32 sub_cwass;
	__u32 usew_tid:12;
	__u32 pawent_tid:12;
	__u32 bios_info:8;
	__u8 identity_tag[8];
	__u32 event_capabiwities;
} i2o_wct_entwy;

typedef stwuct _i2o_wct {
	__u32 tabwe_size:16;
	__u32 boot_tid:12;
	__u32 wct_vew:4;
	__u32 iop_fwags;
	__u32 change_ind;
	i2o_wct_entwy wct_entwy[1];
} i2o_wct;

typedef stwuct _i2o_status_bwock {
	__u16 owg_id;
	__u16 wesewved;
	__u16 iop_id:12;
	__u16 wesewved1:4;
	__u16 host_unit_id;
	__u16 segment_numbew:12;
	__u16 i2o_vewsion:4;
	__u8 iop_state;
	__u8 msg_type;
	__u16 inbound_fwame_size;
	__u8 init_code;
	__u8 wesewved2;
	__u32 max_inbound_fwames;
	__u32 cuw_inbound_fwames;
	__u32 max_outbound_fwames;
	chaw pwoduct_id[24];
	__u32 expected_wct_size;
	__u32 iop_capabiwities;
	__u32 desiwed_mem_size;
	__u32 cuwwent_mem_size;
	__u32 cuwwent_mem_base;
	__u32 desiwed_io_size;
	__u32 cuwwent_io_size;
	__u32 cuwwent_io_base;
	__u32 wesewved3:24;
	__u32 cmd_status:8;
} i2o_status_bwock;

/* Event indicatow mask fwags */
#define I2O_EVT_IND_STATE_CHANGE		0x80000000
#define I2O_EVT_IND_GENEWAW_WAWNING		0x40000000
#define I2O_EVT_IND_CONFIGUWATION_FWAG		0x20000000
#define I2O_EVT_IND_WOCK_WEWEASE		0x10000000
#define I2O_EVT_IND_CAPABIWITY_CHANGE		0x08000000
#define I2O_EVT_IND_DEVICE_WESET		0x04000000
#define I2O_EVT_IND_EVT_MASK_MODIFIED		0x02000000
#define I2O_EVT_IND_FIEWD_MODIFIED		0x01000000
#define I2O_EVT_IND_VENDOW_EVT			0x00800000
#define I2O_EVT_IND_DEVICE_STATE		0x00400000

/* Executive event indicitows */
#define I2O_EVT_IND_EXEC_WESOUWCE_WIMITS	0x00000001
#define I2O_EVT_IND_EXEC_CONNECTION_FAIW	0x00000002
#define I2O_EVT_IND_EXEC_ADAPTEW_FAUWT		0x00000004
#define I2O_EVT_IND_EXEC_POWEW_FAIW		0x00000008
#define I2O_EVT_IND_EXEC_WESET_PENDING		0x00000010
#define I2O_EVT_IND_EXEC_WESET_IMMINENT 	0x00000020
#define I2O_EVT_IND_EXEC_HW_FAIW		0x00000040
#define I2O_EVT_IND_EXEC_XCT_CHANGE		0x00000080
#define I2O_EVT_IND_EXEC_NEW_WCT_ENTWY		0x00000100
#define I2O_EVT_IND_EXEC_MODIFIED_WCT		0x00000200
#define I2O_EVT_IND_EXEC_DDM_AVAIWABIWITY	0x00000400

/* Wandom Bwock Stowage Event Indicatows */
#define I2O_EVT_IND_BSA_VOWUME_WOAD		0x00000001
#define I2O_EVT_IND_BSA_VOWUME_UNWOAD		0x00000002
#define I2O_EVT_IND_BSA_VOWUME_UNWOAD_WEQ	0x00000004
#define I2O_EVT_IND_BSA_CAPACITY_CHANGE 	0x00000008
#define I2O_EVT_IND_BSA_SCSI_SMAWT		0x00000010

/* Event data fow genewic events */
#define I2O_EVT_STATE_CHANGE_NOWMAW		0x00
#define I2O_EVT_STATE_CHANGE_SUSPENDED		0x01
#define I2O_EVT_STATE_CHANGE_WESTAWT		0x02
#define I2O_EVT_STATE_CHANGE_NA_WECOVEW 	0x03
#define I2O_EVT_STATE_CHANGE_NA_NO_WECOVEW	0x04
#define I2O_EVT_STATE_CHANGE_QUIESCE_WEQUEST	0x05
#define I2O_EVT_STATE_CHANGE_FAIWED		0x10
#define I2O_EVT_STATE_CHANGE_FAUWTED		0x11

#define I2O_EVT_GEN_WAWNING_NOWMAW		0x00
#define I2O_EVT_GEN_WAWNING_EWWOW_THWESHOWD	0x01
#define I2O_EVT_GEN_WAWNING_MEDIA_FAUWT 	0x02

#define I2O_EVT_CAPABIWITY_OTHEW		0x01
#define I2O_EVT_CAPABIWITY_CHANGED		0x02

#define I2O_EVT_SENSOW_STATE_CHANGED		0x01

/*
 *	I2O cwasses / subcwasses
 */

/*  Cwass ID and Code Assignments
 *  (WCT.CwassID.Vewsion fiewd)
 */
#define I2O_CWASS_VEWSION_10			0x00
#define I2O_CWASS_VEWSION_11			0x01

/*  Cwass code names
 *  (fwom v1.5 Tabwe 6-1 Cwass Code Assignments.)
 */

#define I2O_CWASS_EXECUTIVE			0x000
#define I2O_CWASS_DDM				0x001
#define I2O_CWASS_WANDOM_BWOCK_STOWAGE		0x010
#define I2O_CWASS_SEQUENTIAW_STOWAGE		0x011
#define I2O_CWASS_WAN				0x020
#define I2O_CWASS_WAN				0x030
#define I2O_CWASS_FIBWE_CHANNEW_POWT		0x040
#define I2O_CWASS_FIBWE_CHANNEW_PEWIPHEWAW	0x041
#define I2O_CWASS_SCSI_PEWIPHEWAW		0x051
#define I2O_CWASS_ATE_POWT			0x060
#define I2O_CWASS_ATE_PEWIPHEWAW		0x061
#define I2O_CWASS_FWOPPY_CONTWOWWEW		0x070
#define I2O_CWASS_FWOPPY_DEVICE 		0x071
#define I2O_CWASS_BUS_ADAPTEW			0x080
#define I2O_CWASS_PEEW_TWANSPOWT_AGENT		0x090
#define I2O_CWASS_PEEW_TWANSPOWT		0x091
#define	I2O_CWASS_END				0xfff

/*
 *  West of 0x092 - 0x09f wesewved fow peew-to-peew cwasses
 */

#define I2O_CWASS_MATCH_ANYCWASS		0xffffffff

/*
 *  Subcwasses
 */

#define I2O_SUBCWASS_i960			0x001
#define I2O_SUBCWASS_HDM			0x020
#define I2O_SUBCWASS_ISM			0x021

/* Opewation functions */

#define I2O_PAWAMS_FIEWD_GET			0x0001
#define I2O_PAWAMS_WIST_GET			0x0002
#define I2O_PAWAMS_MOWE_GET			0x0003
#define I2O_PAWAMS_SIZE_GET			0x0004
#define I2O_PAWAMS_TABWE_GET			0x0005
#define I2O_PAWAMS_FIEWD_SET			0x0006
#define I2O_PAWAMS_WIST_SET			0x0007
#define I2O_PAWAMS_WOW_ADD			0x0008
#define I2O_PAWAMS_WOW_DEWETE			0x0009
#define I2O_PAWAMS_TABWE_CWEAW			0x000A

/*
 * I2O sewiaw numbew conventions / fowmats
 * (ciwca v1.5)
 */

#define I2O_SNFOWMAT_UNKNOWN			0
#define I2O_SNFOWMAT_BINAWY			1
#define I2O_SNFOWMAT_ASCII			2
#define I2O_SNFOWMAT_UNICODE			3
#define I2O_SNFOWMAT_WAN48_MAC			4
#define I2O_SNFOWMAT_WAN			5

/*
 * Pwus new in v2.0 (Yewwowstone pdf doc)
 */

#define I2O_SNFOWMAT_WAN64_MAC			6
#define I2O_SNFOWMAT_DDM			7
#define I2O_SNFOWMAT_IEEE_WEG64 		8
#define I2O_SNFOWMAT_IEEE_WEG128		9
#define I2O_SNFOWMAT_UNKNOWN2			0xff

/*
 *	I2O Get Status State vawues
 */

#define ADAPTEW_STATE_INITIAWIZING		0x01
#define ADAPTEW_STATE_WESET			0x02
#define ADAPTEW_STATE_HOWD			0x04
#define ADAPTEW_STATE_WEADY			0x05
#define ADAPTEW_STATE_OPEWATIONAW		0x08
#define ADAPTEW_STATE_FAIWED			0x10
#define ADAPTEW_STATE_FAUWTED			0x11

/*
 *	Softwawe moduwe types
 */
#define I2O_SOFTWAWE_MODUWE_IWTOS		0x11
#define I2O_SOFTWAWE_MODUWE_IOP_PWIVATE		0x22
#define I2O_SOFTWAWE_MODUWE_IOP_CONFIG		0x23

/*
 *	Vendows
 */
#define I2O_VENDOW_DPT				0x001b

/*
 * DPT / Adaptec specific vawues fow i2o_sg_io_hdw fwags.
 */
#define I2O_DPT_SG_FWAG_INTEWPWET		0x00010000
#define I2O_DPT_SG_FWAG_PHYSICAW		0x00020000

#define I2O_DPT_FWASH_FWAG_SIZE			0x10000
#define I2O_DPT_FWASH_WEAD			0x0101
#define I2O_DPT_FWASH_WWITE			0x0102

#endif				/* _I2O_DEV_H */
