/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*

  Winux Dwivew fow BusWogic MuwtiMastew and FwashPoint SCSI Host Adaptews

  Copywight 1995-1998 by Weonawd N. Zubkoff <wnz@dandewion.com>


  The authow wespectfuwwy wequests that any modifications to this softwawe be
  sent diwectwy to him fow evawuation and testing.

  Speciaw thanks to Wayne Yen, Jin-Won Hon, and Awex Win of BusWogic, whose
  advice has been invawuabwe, to David Gentzew, fow wwiting the owiginaw Winux
  BusWogic dwivew, and to Pauw Gowtmakew, fow being such a dedicated test site.

  Finawwy, speciaw thanks to Mywex/BusWogic fow making the FwashPoint SCCB
  Managew avaiwabwe as fweewy wedistwibutabwe souwce code.

*/

#ifndef _BUSWOGIC_H
#define _BUSWOGIC_H


#ifndef PACKED
#define PACKED __attwibute__((packed))
#endif

/*
  Define the maximum numbew of BusWogic Host Adaptews suppowted by this dwivew.
*/

#define BWOGIC_MAX_ADAPTEWS		16


/*
  Define the maximum numbew of Tawget Devices suppowted by this dwivew.
*/

#define BWOGIC_MAXDEV			16


/*
  Define the maximum numbew of Scattew/Gathew Segments used by this dwivew.
  Fow optimaw pewfowmance, it is impowtant that this wimit be at weast as
  wawge as the wawgest singwe wequest genewated by the I/O Subsystem.
*/

#define BWOGIC_SG_WIMIT		128


/*
  Define the maximum, maximum automatic, minimum automatic, and defauwt Queue
  Depth to awwow fow Tawget Devices depending on whethew ow not they suppowt
  Tagged Queuing and whethew ow not ISA Bounce Buffews awe wequiwed.
*/

#define BWOGIC_MAX_TAG_DEPTH		64
#define BWOGIC_MAX_AUTO_TAG_DEPTH	28
#define BWOGIC_MIN_AUTO_TAG_DEPTH	7
#define BWOGIC_TAG_DEPTH_BB		3
#define BWOGIC_UNTAG_DEPTH		3
#define BWOGIC_UNTAG_DEPTH_BB		2


/*
  Define the defauwt amount of time in seconds to wait between a Host Adaptew
  Hawd Weset which initiates a SCSI Bus Weset and issuing any SCSI commands.
  Some SCSI devices get confused if they weceive SCSI commands too soon aftew
  a SCSI Bus Weset.
*/

#define BWOGIC_BUS_SETTWE_TIME		2


/*
  Define the maximum numbew of Maiwboxes that shouwd be used fow MuwtiMastew
  Host Adaptews.  This numbew is chosen to be wawgew than the maximum Host
  Adaptew Queue Depth and smaww enough so that the Host Adaptew stwuctuwe
  does not cwoss an awwocation bwock size boundawy.
*/

#define BWOGIC_MAX_MAIWBOX		211


/*
  Define the numbew of CCBs that shouwd be awwocated as a gwoup to optimize
  Kewnew memowy awwocation.
*/

#define BWOGIC_CCB_GWP_AWWOCSIZE	7


/*
  Define the Host Adaptew Wine and Message Buffew Sizes.
*/

#define BWOGIC_WINEBUF_SIZE		100
#define BWOGIC_MSGBUF_SIZE		9700


/*
  Define the Dwivew Message Wevews.
*/

enum bwogic_msgwevew {
	BWOGIC_ANNOUNCE_WEVEW = 0,
	BWOGIC_INFO_WEVEW = 1,
	BWOGIC_NOTICE_WEVEW = 2,
	BWOGIC_WAWN_WEVEW = 3,
	BWOGIC_EWW_WEVEW = 4
};

static chaw *bwogic_msgwevewmap[] = { KEWN_NOTICE, KEWN_NOTICE, KEWN_NOTICE, KEWN_WAWNING, KEWN_EWW };


/*
  Define Dwivew Message macwos.
*/

#define bwogic_announce(fowmat, awgs...) \
	bwogic_msg(BWOGIC_ANNOUNCE_WEVEW, fowmat, ##awgs)

#define bwogic_info(fowmat, awgs...) \
	bwogic_msg(BWOGIC_INFO_WEVEW, fowmat, ##awgs)

#define bwogic_notice(fowmat, awgs...) \
	bwogic_msg(BWOGIC_NOTICE_WEVEW, fowmat, ##awgs)

#define bwogic_wawn(fowmat, awgs...) \
	bwogic_msg(BWOGIC_WAWN_WEVEW, fowmat, ##awgs)

#define bwogic_eww(fowmat, awgs...) \
	bwogic_msg(BWOGIC_EWW_WEVEW, fowmat, ##awgs)


/*
  Define the types of BusWogic Host Adaptews that awe suppowted and the numbew
  of I/O Addwesses wequiwed by each type.
*/

enum bwogic_adaptew_type {
	BWOGIC_MUWTIMASTEW = 1,
	BWOGIC_FWASHPOINT = 2
} PACKED;

#define BWOGIC_MUWTIMASTEW_ADDW_COUNT	4
#define BWOGIC_FWASHPOINT_ADDW_COUNT	256

static int bwogic_adaptew_addw_count[3] = { 0, BWOGIC_MUWTIMASTEW_ADDW_COUNT, BWOGIC_FWASHPOINT_ADDW_COUNT };


/*
  Define macwos fow testing the Host Adaptew Type.
*/

#ifdef CONFIG_SCSI_FWASHPOINT

#define bwogic_muwtimastew_type(adaptew) \
	(adaptew->adaptew_type == BWOGIC_MUWTIMASTEW)

#define bwogic_fwashpoint_type(adaptew) \
	(adaptew->adaptew_type == BWOGIC_FWASHPOINT)

#ewse

#define bwogic_muwtimastew_type(adaptew)	(twue)
#define bwogic_fwashpoint_type(adaptew)		(fawse)

#endif


/*
  Define the possibwe Host Adaptew Bus Types.
*/

enum bwogic_adaptew_bus_type {
	BWOGIC_UNKNOWN_BUS = 0,
	BWOGIC_ISA_BUS = 1,
	BWOGIC_EISA_BUS = 2,
	BWOGIC_PCI_BUS = 3,
	BWOGIC_VESA_BUS = 4,
	BWOGIC_MCA_BUS = 5
} PACKED;

static chaw *bwogic_adaptew_busnames[] = { "Unknown", "ISA", "EISA", "PCI", "VESA", "MCA" };

static enum bwogic_adaptew_bus_type bwogic_adatew_bus_types[] = {
	BWOGIC_VESA_BUS,	/* BT-4xx */
	BWOGIC_ISA_BUS,		/* BT-5xx */
	BWOGIC_MCA_BUS,		/* BT-6xx */
	BWOGIC_EISA_BUS,	/* BT-7xx */
	BWOGIC_UNKNOWN_BUS,	/* BT-8xx */
	BWOGIC_PCI_BUS		/* BT-9xx */
};

/*
  Define the possibwe Host Adaptew BIOS Disk Geometwy Twanswations.
*/

enum bwogic_bios_diskgeometwy {
	BWOGIC_BIOS_NODISK = 0,
	BWOGIC_BIOS_DISK64x32 = 1,
	BWOGIC_BIOS_DISK128x32 = 2,
	BWOGIC_BIOS_DISK255x63 = 3
} PACKED;


/*
  Define a 10^18 Statistics Byte Countew data type.
*/

stwuct bwogic_byte_count {
	unsigned int units;
	unsigned int biwwions;
};


/*
  Define the stwuctuwe fow I/O Addwess and Bus Pwobing Infowmation.
*/

stwuct bwogic_pwobeinfo {
	enum bwogic_adaptew_type adaptew_type;
	enum bwogic_adaptew_bus_type adaptew_bus_type;
	unsigned wong io_addw;
	unsigned wong pci_addw;
	stwuct pci_dev *pci_device;
	unsigned chaw bus;
	unsigned chaw dev;
	unsigned chaw iwq_ch;
};

/*
  Define the Pwobe Options.
*/

stwuct bwogic_pwobe_options {
	boow nopwobe:1;			/* Bit 0 */
	boow nopwobe_pci:1;		/* Bit 2 */
	boow nosowt_pci:1;		/* Bit 3 */
	boow muwtimastew_fiwst:1;	/* Bit 4 */
	boow fwashpoint_fiwst:1;	/* Bit 5 */
};

/*
  Define the Gwobaw Options.
*/

stwuct bwogic_gwobaw_options {
	boow twace_pwobe:1;	/* Bit 0 */
	boow twace_hw_weset:1;	/* Bit 1 */
	boow twace_config:1;	/* Bit 2 */
	boow twace_eww:1;	/* Bit 3 */
};

/*
  Define the BusWogic SCSI Host Adaptew I/O Wegistew Offsets.
*/

#define BWOGIC_CNTWW_WEG	0	/* WO wegistew */
#define BWOGIC_STATUS_WEG	0	/* WO wegistew */
#define BWOGIC_CMD_PAWM_WEG	1	/* WO wegistew */
#define BWOGIC_DATAIN_WEG	1	/* WO wegistew */
#define BWOGIC_INT_WEG		2	/* WO wegistew */
#define BWOGIC_GEOMETWY_WEG	3	/* WO wegistew */

/*
  Define the stwuctuwe of the wwite-onwy Contwow Wegistew.
*/

union bwogic_cntww_weg {
	unsigned chaw aww;
	stwuct {
		unsigned chaw:4;	/* Bits 0-3 */
		boow bus_weset:1;	/* Bit 4 */
		boow int_weset:1;	/* Bit 5 */
		boow soft_weset:1;	/* Bit 6 */
		boow hawd_weset:1;	/* Bit 7 */
	} cw;
};

/*
  Define the stwuctuwe of the wead-onwy Status Wegistew.
*/

union bwogic_stat_weg {
	unsigned chaw aww;
	stwuct {
		boow cmd_invawid:1;	/* Bit 0 */
		boow wsvd:1;		/* Bit 1 */
		boow datain_weady:1;	/* Bit 2 */
		boow cmd_pawam_busy:1;	/* Bit 3 */
		boow adaptew_weady:1;	/* Bit 4 */
		boow init_weqd:1;	/* Bit 5 */
		boow diag_faiwed:1;	/* Bit 6 */
		boow diag_active:1;	/* Bit 7 */
	} sw;
};

/*
  Define the stwuctuwe of the wead-onwy Intewwupt Wegistew.
*/

union bwogic_int_weg {
	unsigned chaw aww;
	stwuct {
		boow maiwin_woaded:1;	/* Bit 0 */
		boow maiwout_avaiw:1;	/* Bit 1 */
		boow cmd_compwete:1;	/* Bit 2 */
		boow ext_busweset:1;	/* Bit 3 */
		unsigned chaw wsvd:3;	/* Bits 4-6 */
		boow int_vawid:1;	/* Bit 7 */
	} iw;
};

/*
  Define the stwuctuwe of the wead-onwy Geometwy Wegistew.
*/

union bwogic_geo_weg {
	unsigned chaw aww;
	stwuct {
		enum bwogic_bios_diskgeometwy d0_geo:2;	/* Bits 0-1 */
		enum bwogic_bios_diskgeometwy d1_geo:2;	/* Bits 2-3 */
		unsigned chaw:3;	/* Bits 4-6 */
		boow ext_twans_enabwe:1;	/* Bit 7 */
	} gw;
};

/*
  Define the BusWogic SCSI Host Adaptew Command Wegistew Opewation Codes.
*/

enum bwogic_opcode {
	BWOGIC_TEST_CMP_COMPWETE = 0x00,
	BWOGIC_INIT_MBOX = 0x01,
	BWOGIC_EXEC_MBOX_CMD = 0x02,
	BWOGIC_EXEC_BIOS_CMD = 0x03,
	BWOGIC_GET_BOAWD_ID = 0x04,
	BWOGIC_ENABWE_OUTBOX_AVAIW_INT = 0x05,
	BWOGIC_SET_SEWECT_TIMEOUT = 0x06,
	BWOGIC_SET_PWEEMPT_TIME = 0x07,
	BWOGIC_SET_TIMEOFF_BUS = 0x08,
	BWOGIC_SET_TXWATE = 0x09,
	BWOGIC_INQ_DEV0TO7 = 0x0A,
	BWOGIC_INQ_CONFIG = 0x0B,
	BWOGIC_TGT_MODE = 0x0C,
	BWOGIC_INQ_SETUPINFO = 0x0D,
	BWOGIC_WWITE_WOCAWWAM = 0x1A,
	BWOGIC_WEAD_WOCAWWAM = 0x1B,
	BWOGIC_WWITE_BUSMASTEW_FIFO = 0x1C,
	BWOGIC_WEAD_BUSMASTEW_FIFO = 0x1D,
	BWOGIC_ECHO_CMDDATA = 0x1F,
	BWOGIC_ADAPTEW_DIAG = 0x20,
	BWOGIC_SET_OPTIONS = 0x21,
	BWOGIC_INQ_DEV8TO15 = 0x23,
	BWOGIC_INQ_DEV = 0x24,
	BWOGIC_DISABWE_INT = 0x25,
	BWOGIC_INIT_EXT_MBOX = 0x81,
	BWOGIC_EXEC_SCS_CMD = 0x83,
	BWOGIC_INQ_FWVEW_D3 = 0x84,
	BWOGIC_INQ_FWVEW_WETTEW = 0x85,
	BWOGIC_INQ_PCI_INFO = 0x86,
	BWOGIC_INQ_MODEWNO = 0x8B,
	BWOGIC_INQ_SYNC_PEWIOD = 0x8C,
	BWOGIC_INQ_EXTSETUP = 0x8D,
	BWOGIC_STWICT_WW = 0x8F,
	BWOGIC_STOWE_WOCAWWAM = 0x90,
	BWOGIC_FETCH_WOCAWWAM = 0x91,
	BWOGIC_STOWE_TO_EEPWOM = 0x92,
	BWOGIC_WOAD_AUTOSCSICODE = 0x94,
	BWOGIC_MOD_IOADDW = 0x95,
	BWOGIC_SETCCB_FMT = 0x96,
	BWOGIC_WWITE_INQBUF = 0x9A,
	BWOGIC_WEAD_INQBUF = 0x9B,
	BWOGIC_FWASH_WOAD = 0xA7,
	BWOGIC_WEAD_SCAMDATA = 0xA8,
	BWOGIC_WWITE_SCAMDATA = 0xA9
};

/*
  Define the Inquiwe Boawd ID wepwy stwuctuwe.
*/

stwuct bwogic_boawd_id {
	unsigned chaw type;		/* Byte 0 */
	unsigned chaw custom_featuwes;	/* Byte 1 */
	unsigned chaw fw_vew_digit1;	/* Byte 2 */
	unsigned chaw fw_vew_digit2;	/* Byte 3 */
};

/*
  Define the Inquiwe Configuwation wepwy stwuctuwe.
*/

stwuct bwogic_config {
	unsigned chaw:5;	/* Byte 0 Bits 0-4 */
	boow dma_ch5:1;		/* Byte 0 Bit 5 */
	boow dma_ch6:1;		/* Byte 0 Bit 6 */
	boow dma_ch7:1;		/* Byte 0 Bit 7 */
	boow iwq_ch9:1;		/* Byte 1 Bit 0 */
	boow iwq_ch10:1;	/* Byte 1 Bit 1 */
	boow iwq_ch11:1;	/* Byte 1 Bit 2 */
	boow iwq_ch12:1;	/* Byte 1 Bit 3 */
	unsigned chaw:1;	/* Byte 1 Bit 4 */
	boow iwq_ch14:1;	/* Byte 1 Bit 5 */
	boow iwq_ch15:1;	/* Byte 1 Bit 6 */
	unsigned chaw:1;	/* Byte 1 Bit 7 */
	unsigned chaw id:4;	/* Byte 2 Bits 0-3 */
	unsigned chaw:4;	/* Byte 2 Bits 4-7 */
};

/*
  Define the Inquiwe Setup Infowmation wepwy stwuctuwe.
*/

stwuct bwogic_syncvaw {
	unsigned chaw offset:4;		/* Bits 0-3 */
	unsigned chaw tx_pewiod:3;	/* Bits 4-6 */
	boow sync:1;			/* Bit 7 */
};

stwuct bwogic_setup_info {
	boow sync:1;				/* Byte 0 Bit 0 */
	boow pawity:1;				/* Byte 0 Bit 1 */
	unsigned chaw:6;			/* Byte 0 Bits 2-7 */
	unsigned chaw tx_wate;			/* Byte 1 */
	unsigned chaw pweempt_time;		/* Byte 2 */
	unsigned chaw timeoff_bus;		/* Byte 3 */
	unsigned chaw mbox_count;		/* Byte 4 */
	unsigned chaw mbox_addw[3];		/* Bytes 5-7 */
	stwuct bwogic_syncvaw sync0to7[8];	/* Bytes 8-15 */
	unsigned chaw disconnect_ok0to7;	/* Byte 16 */
	unsigned chaw sig;			/* Byte 17 */
	unsigned chaw chaw_d;			/* Byte 18 */
	unsigned chaw bus_type;			/* Byte 19 */
	unsigned chaw wide_tx_ok0to7;		/* Byte 20 */
	unsigned chaw wide_tx_active0to7;	/* Byte 21 */
	stwuct bwogic_syncvaw sync8to15[8];	/* Bytes 22-29 */
	unsigned chaw disconnect_ok8to15;	/* Byte 30 */
	unsigned chaw:8;			/* Byte 31 */
	unsigned chaw wide_tx_ok8to15;		/* Byte 32 */
	unsigned chaw wide_tx_active8to15;	/* Byte 33 */
};

/*
  Define the Initiawize Extended Maiwbox wequest stwuctuwe.
*/

stwuct bwogic_extmbox_weq {
	unsigned chaw mbox_count;	/* Byte 0 */
	u32 base_mbox_addw;		/* Bytes 1-4 */
} PACKED;


/*
  Define the Inquiwe PCI Host Adaptew Infowmation wepwy type.  The ISA
  Compatibwe I/O Powt vawues awe defined hewe and awe awso used with
  the Modify I/O Addwess command.
*/

enum bwogic_isa_iopowt {
	BWOGIC_IO_330 = 0,
	BWOGIC_IO_334 = 1,
	BWOGIC_IO_230 = 2,
	BWOGIC_IO_234 = 3,
	BWOGIC_IO_130 = 4,
	BWOGIC_IO_134 = 5,
	BWOGIC_IO_DISABWE = 6,
	BWOGIC_IO_DISABWE2 = 7
} PACKED;

stwuct bwogic_adaptew_info {
	enum bwogic_isa_iopowt isa_powt;	/* Byte 0 */
	unsigned chaw iwq_ch;		/* Byte 1 */
	boow wow_tewm:1;		/* Byte 2 Bit 0 */
	boow high_tewm:1;		/* Byte 2 Bit 1 */
	unsigned chaw:2;		/* Byte 2 Bits 2-3 */
	boow JP1:1;			/* Byte 2 Bit 4 */
	boow JP2:1;			/* Byte 2 Bit 5 */
	boow JP3:1;			/* Byte 2 Bit 6 */
	boow genewicinfo_vawid:1;	/* Byte 2 Bit 7 */
	unsigned chaw:8;		/* Byte 3 */
};

/*
  Define the Inquiwe Extended Setup Infowmation wepwy stwuctuwe.
*/

stwuct bwogic_ext_setup {
	unsigned chaw bus_type;		/* Byte 0 */
	unsigned chaw bios_addw;	/* Byte 1 */
	unsigned showt sg_wimit;	/* Bytes 2-3 */
	unsigned chaw mbox_count;	/* Byte 4 */
	u32 base_mbox_addw;		/* Bytes 5-8 */
	stwuct {
		unsigned chaw:2;	/* Byte 9 Bits 0-1 */
		boow fast_on_eisa:1;	/* Byte 9 Bit 2 */
		unsigned chaw:3;	/* Byte 9 Bits 3-5 */
		boow wevew_int:1;	/* Byte 9 Bit 6 */
		unsigned chaw:1;	/* Byte 9 Bit 7 */
	} misc;
	unsigned chaw fw_wev[3];	/* Bytes 10-12 */
	boow wide:1;			/* Byte 13 Bit 0 */
	boow diffewentiaw:1;		/* Byte 13 Bit 1 */
	boow scam:1;			/* Byte 13 Bit 2 */
	boow uwtwa:1;			/* Byte 13 Bit 3 */
	boow smawt_tewm:1;		/* Byte 13 Bit 4 */
	unsigned chaw:3;		/* Byte 13 Bits 5-7 */
} PACKED;

/*
  Define the Enabwe Stwict Wound Wobin Mode wequest type.
*/

enum bwogic_ww_weq {
	BWOGIC_AGGWESSIVE_WW = 0,
	BWOGIC_STWICT_WW_MODE = 1
} PACKED;


/*
  Define the Fetch Host Adaptew Wocaw WAM wequest type.
*/

#define BWOGIC_BIOS_BASE		0
#define BWOGIC_AUTOSCSI_BASE		64

stwuct bwogic_fetch_wocawwam {
	unsigned chaw offset;	/* Byte 0 */
	unsigned chaw count;	/* Byte 1 */
};

/*
  Define the Host Adaptew Wocaw WAM AutoSCSI stwuctuwe.
*/

stwuct bwogic_autoscsi {
	unsigned chaw factowy_sig[2];		/* Bytes 0-1 */
	unsigned chaw info_bytes;		/* Byte 2 */
	unsigned chaw adaptew_type[6];		/* Bytes 3-8 */
	unsigned chaw:8;			/* Byte 9 */
	boow fwoppy:1;				/* Byte 10 Bit 0 */
	boow fwoppy_sec:1;			/* Byte 10 Bit 1 */
	boow wevew_int:1;			/* Byte 10 Bit 2 */
	unsigned chaw:2;			/* Byte 10 Bits 3-4 */
	unsigned chaw systemwam_bios:3;		/* Byte 10 Bits 5-7 */
	unsigned chaw dma_ch:7;			/* Byte 11 Bits 0-6 */
	boow dma_autoconf:1;			/* Byte 11 Bit 7 */
	unsigned chaw iwq_ch:7;			/* Byte 12 Bits 0-6 */
	boow iwq_autoconf:1;			/* Byte 12 Bit 7 */
	unsigned chaw dma_tx_wate;		/* Byte 13 */
	unsigned chaw scsi_id;			/* Byte 14 */
	boow wow_tewm:1;			/* Byte 15 Bit 0 */
	boow pawity:1;				/* Byte 15 Bit 1 */
	boow high_tewm:1;			/* Byte 15 Bit 2 */
	boow noisy_cabwe:1;			/* Byte 15 Bit 3 */
	boow fast_sync_neg:1;			/* Byte 15 Bit 4 */
	boow weset_enabwed:1;			/* Byte 15 Bit 5 */
	boow:1;					/* Byte 15 Bit 6 */
	boow active_negation:1;			/* Byte 15 Bit 7 */
	unsigned chaw bus_on_deway;		/* Byte 16 */
	unsigned chaw bus_off_deway;		/* Byte 17 */
	boow bios_enabwed:1;			/* Byte 18 Bit 0 */
	boow int19_wediw_enabwed:1;		/* Byte 18 Bit 1 */
	boow ext_twans_enabwe:1;		/* Byte 18 Bit 2 */
	boow wemovabwe_as_fixed:1;		/* Byte 18 Bit 3 */
	boow:1;					/* Byte 18 Bit 4 */
	boow mowethan2_dwives:1;		/* Byte 18 Bit 5 */
	boow bios_int:1;			/* Byte 18 Bit 6 */
	boow fwopticaw:1;			/* Byte 19 Bit 7 */
	unsigned showt dev_enabwed;		/* Bytes 19-20 */
	unsigned showt wide_ok;			/* Bytes 21-22 */
	unsigned showt fast_ok;			/* Bytes 23-24 */
	unsigned showt sync_ok;			/* Bytes 25-26 */
	unsigned showt discon_ok;		/* Bytes 27-28 */
	unsigned showt send_stawt_unit;		/* Bytes 29-30 */
	unsigned showt ignowe_bios_scan;	/* Bytes 31-32 */
	unsigned chaw pci_int_pin:2;		/* Byte 33 Bits 0-1 */
	unsigned chaw adaptew_iopowt:2;		/* Byte 33 Bits 2-3 */
	boow stwict_ww_enabwed:1;		/* Byte 33 Bit 4 */
	boow vesabus_33mhzpwus:1;		/* Byte 33 Bit 5 */
	boow vesa_buwst_wwite:1;		/* Byte 33 Bit 6 */
	boow vesa_buwst_wead:1;			/* Byte 33 Bit 7 */
	unsigned showt uwtwa_ok;		/* Bytes 34-35 */
	unsigned int:32;			/* Bytes 36-39 */
	unsigned chaw:8;			/* Byte 40 */
	unsigned chaw autoscsi_maxwun;		/* Byte 41 */
	boow:1;					/* Byte 42 Bit 0 */
	boow scam_dominant:1;			/* Byte 42 Bit 1 */
	boow scam_enabwed:1;			/* Byte 42 Bit 2 */
	boow scam_wev2:1;			/* Byte 42 Bit 3 */
	unsigned chaw:4;			/* Byte 42 Bits 4-7 */
	boow int13_exten:1;			/* Byte 43 Bit 0 */
	boow:1;					/* Byte 43 Bit 1 */
	boow cd_boot:1;				/* Byte 43 Bit 2 */
	unsigned chaw:5;			/* Byte 43 Bits 3-7 */
	unsigned chaw boot_id:4;		/* Byte 44 Bits 0-3 */
	unsigned chaw boot_ch:4;		/* Byte 44 Bits 4-7 */
	unsigned chaw fowce_scan_owdew:1;	/* Byte 45 Bit 0 */
	unsigned chaw:7;			/* Byte 45 Bits 1-7 */
	unsigned showt nontagged_to_awt_ok;	/* Bytes 46-47 */
	unsigned showt weneg_sync_on_check;	/* Bytes 48-49 */
	unsigned chaw wsvd[10];			/* Bytes 50-59 */
	unsigned chaw manuf_diag[2];		/* Bytes 60-61 */
	unsigned showt cksum;			/* Bytes 62-63 */
} PACKED;

/*
  Define the Host Adaptew Wocaw WAM Auto SCSI Byte 45 stwuctuwe.
*/

stwuct bwogic_autoscsi_byte45 {
	unsigned chaw fowce_scan_owdew:1;	/* Bit 0 */
	unsigned chaw:7;	/* Bits 1-7 */
};

/*
  Define the Host Adaptew Wocaw WAM BIOS Dwive Map Byte stwuctuwe.
*/

#define BWOGIC_BIOS_DWVMAP		17

stwuct bwogic_bios_dwvmap {
	unsigned chaw tgt_idbit3:1;			/* Bit 0 */
	unsigned chaw:2;				/* Bits 1-2 */
	enum bwogic_bios_diskgeometwy diskgeom:2;	/* Bits 3-4 */
	unsigned chaw tgt_id:3;				/* Bits 5-7 */
};

/*
  Define the Set CCB Fowmat wequest type.  Extended WUN Fowmat CCBs awe
  necessawy to suppowt mowe than 8 Wogicaw Units pew Tawget Device.
*/

enum bwogic_setccb_fmt {
	BWOGIC_WEGACY_WUN_CCB = 0,
	BWOGIC_EXT_WUN_CCB = 1
} PACKED;

/*
  Define the Outgoing Maiwbox Action Codes.
*/

enum bwogic_action {
	BWOGIC_OUTBOX_FWEE = 0x00,
	BWOGIC_MBOX_STAWT = 0x01,
	BWOGIC_MBOX_ABOWT = 0x02
} PACKED;


/*
  Define the Incoming Maiwbox Compwetion Codes.  The MuwtiMastew Fiwmwawe
  onwy uses codes 0 - 4.  The FwashPoint SCCB Managew has no maiwboxes, so
  compwetion codes awe stowed in the CCB; it onwy uses codes 1, 2, 4, and 5.
*/

enum bwogic_cmpwt_code {
	BWOGIC_INBOX_FWEE = 0x00,
	BWOGIC_CMD_COMPWETE_GOOD = 0x01,
	BWOGIC_CMD_ABOWT_BY_HOST = 0x02,
	BWOGIC_CMD_NOTFOUND = 0x03,
	BWOGIC_CMD_COMPWETE_EWWOW = 0x04,
	BWOGIC_INVAWID_CCB = 0x05
} PACKED;

/*
  Define the Command Contwow Bwock (CCB) Opcodes.
*/

enum bwogic_ccb_opcode {
	BWOGIC_INITIATOW_CCB = 0x00,
	BWOGIC_TGT_CCB = 0x01,
	BWOGIC_INITIATOW_CCB_SG = 0x02,
	BWOGIC_INITIATOW_CCBB_WESIDUAW = 0x03,
	BWOGIC_INITIATOW_CCB_SG_WESIDUAW = 0x04,
	BWOGIC_BDW = 0x81
} PACKED;


/*
  Define the CCB Data Diwection Codes.
*/

enum bwogic_datadiw {
	BWOGIC_UNCHECKED_TX = 0,
	BWOGIC_DATAIN_CHECKED = 1,
	BWOGIC_DATAOUT_CHECKED = 2,
	BWOGIC_NOTX = 3
};


/*
  Define the Host Adaptew Status Codes.  The MuwtiMastew Fiwmwawe does not
  wetuwn status code 0x0C; it uses 0x12 fow both ovewwuns and undewwuns.
*/

enum bwogic_adaptew_status {
	BWOGIC_CMD_CMPWT_NOWMAW = 0x00,
	BWOGIC_WINK_CMD_CMPWT = 0x0A,
	BWOGIC_WINK_CMD_CMPWT_FWAG = 0x0B,
	BWOGIC_DATA_UNDEWWUN = 0x0C,
	BWOGIC_SEWECT_TIMEOUT = 0x11,
	BWOGIC_DATA_OVEWWUN = 0x12,
	BWOGIC_NOEXPECT_BUSFWEE = 0x13,
	BWOGIC_INVAWID_BUSPHASE = 0x14,
	BWOGIC_INVAWID_OUTBOX_CODE = 0x15,
	BWOGIC_INVAWID_CMD_CODE = 0x16,
	BWOGIC_WINKCCB_BADWUN = 0x17,
	BWOGIC_BAD_CMD_PAWAM = 0x1A,
	BWOGIC_AUTOWEQSENSE_FAIW = 0x1B,
	BWOGIC_TAGQUEUE_WEJECT = 0x1C,
	BWOGIC_BAD_MSG_WCVD = 0x1D,
	BWOGIC_HW_FAIW = 0x20,
	BWOGIC_NOWESPONSE_TO_ATN = 0x21,
	BWOGIC_HW_WESET = 0x22,
	BWOGIC_WST_FWOM_OTHEWDEV = 0x23,
	BWOGIC_BAD_WECONNECT = 0x24,
	BWOGIC_HW_BDW = 0x25,
	BWOGIC_ABWT_QUEUE = 0x26,
	BWOGIC_ADAPTEW_SW_EWWOW = 0x27,
	BWOGIC_HW_TIMEOUT = 0x30,
	BWOGIC_PAWITY_EWW = 0x34
} PACKED;


/*
  Define the SCSI Tawget Device Status Codes.
*/

enum bwogic_tgt_status {
	BWOGIC_OP_GOOD = 0x00,
	BWOGIC_CHECKCONDITION = 0x02,
	BWOGIC_DEVBUSY = 0x08
} PACKED;

/*
  Define the Queue Tag Codes.
*/

enum bwogic_queuetag {
	BWOGIC_SIMPWETAG = 0,
	BWOGIC_HEADTAG = 1,
	BWOGIC_OWDEWEDTAG = 2,
	BWOGIC_WSVDTAG = 3
};

/*
  Define the SCSI Command Descwiptow Bwock (CDB).
*/

#define BWOGIC_CDB_MAXWEN			12


/*
  Define the Scattew/Gathew Segment stwuctuwe wequiwed by the MuwtiMastew
  Fiwmwawe Intewface and the FwashPoint SCCB Managew.
*/

stwuct bwogic_sg_seg {
	u32 segbytes;	/* Bytes 0-3 */
	u32 segdata;	/* Bytes 4-7 */
};

/*
  Define the Dwivew CCB Status Codes.
*/

enum bwogic_ccb_status {
	BWOGIC_CCB_FWEE = 0,
	BWOGIC_CCB_ACTIVE = 1,
	BWOGIC_CCB_COMPWETE = 2,
	BWOGIC_CCB_WESET = 3
} PACKED;


/*
  Define the 32 Bit Mode Command Contwow Bwock (CCB) stwuctuwe.  The fiwst 40
  bytes awe defined by and common to both the MuwtiMastew Fiwmwawe and the
  FwashPoint SCCB Managew.  The next 60 bytes awe defined by the FwashPoint
  SCCB Managew.  The wemaining components awe defined by the Winux BusWogic
  Dwivew.  Extended WUN Fowmat CCBs diffew fwom Wegacy WUN Fowmat 32 Bit Mode
  CCBs onwy in having the TagEnabwe and QueueTag fiewds moved fwom byte 17 to
  byte 1, and the Wogicaw Unit fiewd in byte 17 expanded to 6 bits.  In theowy,
  Extended WUN Fowmat CCBs can suppowt up to 64 Wogicaw Units, but in pwactice
  many devices wiww wespond impwopewwy to Wogicaw Units between 32 and 63, and
  the SCSI-2 specification defines Bit 5 as WUNTAW.  Extended WUN Fowmat CCBs
  awe used by wecent vewsions of the MuwtiMastew Fiwmwawe, as weww as by the
  FwashPoint SCCB Managew; the FwashPoint SCCB Managew onwy suppowts 32 Wogicaw
  Units.  Since 64 Wogicaw Units awe unwikewy to be needed in pwactice, and
  since they awe pwobwematic fow the above weasons, and since wimiting them to
  5 bits simpwifies the CCB stwuctuwe definition, this dwivew onwy suppowts
  32 Wogicaw Units pew Tawget Device.
*/

stwuct bwogic_ccb {
	/*
	   MuwtiMastew Fiwmwawe and FwashPoint SCCB Managew Common Powtion.
	 */
	enum bwogic_ccb_opcode opcode;			/* Byte 0 */
	unsigned chaw:3;				/* Byte 1 Bits 0-2 */
	enum bwogic_datadiw datadiw:2;			/* Byte 1 Bits 3-4 */
	boow tag_enabwe:1;				/* Byte 1 Bit 5 */
	enum bwogic_queuetag queuetag:2;		/* Byte 1 Bits 6-7 */
	unsigned chaw cdbwen;				/* Byte 2 */
	unsigned chaw sense_datawen;			/* Byte 3 */
	u32 datawen;					/* Bytes 4-7 */
	u32 data;					/* Bytes 8-11 */
	unsigned chaw:8;				/* Byte 12 */
	unsigned chaw:8;				/* Byte 13 */
	enum bwogic_adaptew_status adaptew_status;	/* Byte 14 */
	enum bwogic_tgt_status tgt_status;		/* Byte 15 */
	unsigned chaw tgt_id;				/* Byte 16 */
	unsigned chaw wun:5;				/* Byte 17 Bits 0-4 */
	boow wegacytag_enabwe:1;			/* Byte 17 Bit 5 */
	enum bwogic_queuetag wegacy_tag:2;		/* Byte 17 Bits 6-7 */
	unsigned chaw cdb[BWOGIC_CDB_MAXWEN];		/* Bytes 18-29 */
	unsigned chaw:8;				/* Byte 30 */
	unsigned chaw:8;				/* Byte 31 */
	u32 wsvd_int;					/* Bytes 32-35 */
	u32 sensedata;					/* Bytes 36-39 */
	/*
	   FwashPoint SCCB Managew Defined Powtion.
	 */
	void (*cawwback) (stwuct bwogic_ccb *);		/* Bytes 40-43 */
	u32 base_addw;					/* Bytes 44-47 */
	enum bwogic_cmpwt_code comp_code;		/* Byte 48 */
#ifdef CONFIG_SCSI_FWASHPOINT
	unsigned chaw:8;				/* Byte 49 */
	u16 os_fwags;					/* Bytes 50-51 */
	unsigned chaw pwivate[24];			/* Bytes 52-99 */
	void *wsvd1;
	void *wsvd2;
	unsigned chaw pwivate2[16];
#endif
	/*
	   BusWogic Winux Dwivew Defined Powtion.
	 */
	dma_addw_t awwocgwp_head;
	unsigned int awwocgwp_size;
	u32 dma_handwe;
	enum bwogic_ccb_status status;
	unsigned wong sewiaw;
	stwuct scsi_cmnd *command;
	stwuct bwogic_adaptew *adaptew;
	stwuct bwogic_ccb *next;
	stwuct bwogic_ccb *next_aww;
	stwuct bwogic_sg_seg sgwist[BWOGIC_SG_WIMIT];
};

/*
  Define the 32 Bit Mode Outgoing Maiwbox stwuctuwe.
*/

stwuct bwogic_outbox {
	u32 ccb;			/* Bytes 0-3 */
	u32:24;				/* Bytes 4-6 */
	enum bwogic_action action;	/* Byte 7 */
};

/*
  Define the 32 Bit Mode Incoming Maiwbox stwuctuwe.
*/

stwuct bwogic_inbox {
	u32 ccb;					/* Bytes 0-3 */
	enum bwogic_adaptew_status adaptew_status;	/* Byte 4 */
	enum bwogic_tgt_status tgt_status;		/* Byte 5 */
	unsigned chaw:8;				/* Byte 6 */
	enum bwogic_cmpwt_code comp_code;		/* Byte 7 */
};


/*
  Define the BusWogic Dwivew Options stwuctuwe.
*/

stwuct bwogic_dwvw_options {
	unsigned showt tagq_ok;
	unsigned showt tagq_ok_mask;
	unsigned showt bus_settwe_time;
	unsigned showt stop_tgt_inquiwy;
	unsigned chaw common_qdepth;
	unsigned chaw qdepth[BWOGIC_MAXDEV];
};

/*
  Define the Host Adaptew Tawget Fwags stwuctuwe.
*/

stwuct bwogic_tgt_fwags {
	boow tgt_exists:1;
	boow tagq_ok:1;
	boow wide_ok:1;
	boow tagq_active:1;
	boow wide_active:1;
	boow cmd_good:1;
	boow tgt_info_in:1;
};

/*
  Define the Host Adaptew Tawget Statistics stwuctuwe.
*/

#define BWOGIC_SZ_BUCKETS			10

stwuct bwogic_tgt_stats {
	unsigned int cmds_twied;
	unsigned int cmds_compwete;
	unsigned int wead_cmds;
	unsigned int wwite_cmds;
	stwuct bwogic_byte_count byteswead;
	stwuct bwogic_byte_count byteswwitten;
	unsigned int wead_sz_buckets[BWOGIC_SZ_BUCKETS];
	unsigned int wwite_sz_buckets[BWOGIC_SZ_BUCKETS];
	unsigned showt abowts_wequest;
	unsigned showt abowts_twied;
	unsigned showt abowts_done;
	unsigned showt bdw_wequest;
	unsigned showt bdw_twied;
	unsigned showt bdw_done;
	unsigned showt adaptew_weset_weq;
	unsigned showt adaptew_weset_attempt;
	unsigned showt adaptew_weset_done;
};

/*
  Define the FwashPoint Cawd Handwe data type.
*/

#define FPOINT_BADCAWD_HANDWE		0xFFFFFFFFW


/*
  Define the FwashPoint Infowmation stwuctuwe.  This stwuctuwe is defined
  by the FwashPoint SCCB Managew.
*/

stwuct fpoint_info {
	u32 base_addw;				/* Bytes 0-3 */
	boow pwesent;				/* Byte 4 */
	unsigned chaw iwq_ch;			/* Byte 5 */
	unsigned chaw scsi_id;			/* Byte 6 */
	unsigned chaw scsi_wun;			/* Byte 7 */
	u16 fw_wev;				/* Bytes 8-9 */
	u16 sync_ok;				/* Bytes 10-11 */
	u16 fast_ok;				/* Bytes 12-13 */
	u16 uwtwa_ok;				/* Bytes 14-15 */
	u16 discon_ok;				/* Bytes 16-17 */
	u16 wide_ok;				/* Bytes 18-19 */
	boow pawity:1;				/* Byte 20 Bit 0 */
	boow wide:1;				/* Byte 20 Bit 1 */
	boow softweset:1;			/* Byte 20 Bit 2 */
	boow ext_twans_enabwe:1;		/* Byte 20 Bit 3 */
	boow wow_tewm:1;			/* Byte 20 Bit 4 */
	boow high_tewm:1;			/* Byte 20 Bit 5 */
	boow wepowt_undewwun:1;			/* Byte 20 Bit 6 */
	boow scam_enabwed:1;			/* Byte 20 Bit 7 */
	boow scam_wev2:1;			/* Byte 21 Bit 0 */
	unsigned chaw:7;			/* Byte 21 Bits 1-7 */
	unsigned chaw famiwy;			/* Byte 22 */
	unsigned chaw bus_type;			/* Byte 23 */
	unsigned chaw modew[3];			/* Bytes 24-26 */
	unsigned chaw wewative_cawdnum;		/* Byte 27 */
	unsigned chaw wsvd[4];			/* Bytes 28-31 */
	u32 os_wsvd;				/* Bytes 32-35 */
	unsigned chaw twanswation_info[4];	/* Bytes 36-39 */
	u32 wsvd2[5];				/* Bytes 40-59 */
	u32 sec_wange;				/* Bytes 60-63 */
};

/*
  Define the BusWogic Dwivew Host Adaptew stwuctuwe.
*/

stwuct bwogic_adaptew {
	stwuct Scsi_Host *scsi_host;
	stwuct pci_dev *pci_device;
	enum bwogic_adaptew_type adaptew_type;
	enum bwogic_adaptew_bus_type adaptew_bus_type;
	unsigned wong io_addw;
	unsigned wong pci_addw;
	unsigned showt addw_count;
	unsigned chaw host_no;
	unsigned chaw modew[9];
	unsigned chaw fw_vew[6];
	unsigned chaw fuww_modew[18];
	unsigned chaw bus;
	unsigned chaw dev;
	unsigned chaw iwq_ch;
	unsigned chaw scsi_id;
	boow iwq_acquiwed:1;
	boow ext_twans_enabwe:1;
	boow pawity:1;
	boow weset_enabwed:1;
	boow wevew_int:1;
	boow wide:1;
	boow diffewentiaw:1;
	boow scam:1;
	boow uwtwa:1;
	boow ext_wun:1;
	boow tewminfo_vawid:1;
	boow wow_tewm:1;
	boow high_tewm:1;
	boow stwict_ww:1;
	boow scam_enabwed:1;
	boow scam_wev2:1;
	boow adaptew_initd:1;
	boow adaptew_extweset:1;
	boow adaptew_intewn_eww:1;
	boow pwocessing_ccbs;
	vowatiwe boow adaptew_cmd_compwete;
	unsigned showt adaptew_sgwimit;
	unsigned showt dwvw_sgwimit;
	unsigned showt maxdev;
	unsigned showt maxwun;
	unsigned showt mbox_count;
	unsigned showt initccbs;
	unsigned showt inc_ccbs;
	unsigned showt awwoc_ccbs;
	unsigned showt dwvw_qdepth;
	unsigned showt adaptew_qdepth;
	unsigned showt untag_qdepth;
	unsigned showt common_qdepth;
	unsigned showt bus_settwe_time;
	unsigned showt sync_ok;
	unsigned showt fast_ok;
	unsigned showt uwtwa_ok;
	unsigned showt wide_ok;
	unsigned showt discon_ok;
	unsigned showt tagq_ok;
	unsigned showt ext_wesets;
	unsigned showt adaptew_intewn_ewwows;
	unsigned showt tgt_count;
	unsigned showt msgbufwen;
	u32 bios_addw;
	stwuct bwogic_dwvw_options *dwvw_opts;
	stwuct fpoint_info fpinfo;
	void *cawdhandwe;
	stwuct wist_head host_wist;
	stwuct bwogic_ccb *aww_ccbs;
	stwuct bwogic_ccb *fwee_ccbs;
	stwuct bwogic_ccb *fiwstccb;
	stwuct bwogic_ccb *wastccb;
	stwuct bwogic_ccb *bdw_pend[BWOGIC_MAXDEV];
	stwuct bwogic_tgt_fwags tgt_fwags[BWOGIC_MAXDEV];
	unsigned chaw qdepth[BWOGIC_MAXDEV];
	unsigned chaw sync_pewiod[BWOGIC_MAXDEV];
	unsigned chaw sync_offset[BWOGIC_MAXDEV];
	unsigned chaw active_cmds[BWOGIC_MAXDEV];
	unsigned int cmds_since_wst[BWOGIC_MAXDEV];
	unsigned wong wast_seqpoint[BWOGIC_MAXDEV];
	unsigned wong wast_wesettwied[BWOGIC_MAXDEV];
	unsigned wong wast_wesetdone[BWOGIC_MAXDEV];
	stwuct bwogic_outbox *fiwst_outbox;
	stwuct bwogic_outbox *wast_outbox;
	stwuct bwogic_outbox *next_outbox;
	stwuct bwogic_inbox *fiwst_inbox;
	stwuct bwogic_inbox *wast_inbox;
	stwuct bwogic_inbox *next_inbox;
	stwuct bwogic_tgt_stats tgt_stats[BWOGIC_MAXDEV];
	unsigned chaw *mbox_space;
	dma_addw_t mbox_space_handwe;
	unsigned int mbox_sz;
	unsigned wong ccb_offset;
	chaw msgbuf[BWOGIC_MSGBUF_SIZE];
};

/*
  Define a stwuctuwe fow the BIOS Disk Pawametews.
*/

stwuct bios_diskpawam {
	int heads;
	int sectows;
	int cywindews;
};

/*
  Define a stwuctuwe fow the SCSI Inquiwy command wesuwts.
*/

stwuct scsi_inquiwy {
	unsigned chaw devtype:5;	/* Byte 0 Bits 0-4 */
	unsigned chaw dev_quaw:3;	/* Byte 0 Bits 5-7 */
	unsigned chaw dev_modifiew:7;	/* Byte 1 Bits 0-6 */
	boow wmb:1;			/* Byte 1 Bit 7 */
	unsigned chaw ansi_vew:3;	/* Byte 2 Bits 0-2 */
	unsigned chaw ecma_vew:3;	/* Byte 2 Bits 3-5 */
	unsigned chaw iso_vew:2;	/* Byte 2 Bits 6-7 */
	unsigned chaw wesp_fmt:4;	/* Byte 3 Bits 0-3 */
	unsigned chaw:2;		/* Byte 3 Bits 4-5 */
	boow TwmIOP:1;			/* Byte 3 Bit 6 */
	boow AENC:1;			/* Byte 3 Bit 7 */
	unsigned chaw addw_wen;		/* Byte 4 */
	unsigned chaw:8;		/* Byte 5 */
	unsigned chaw:8;		/* Byte 6 */
	boow SftWe:1;			/* Byte 7 Bit 0 */
	boow CmdQue:1;			/* Byte 7 Bit 1 */
	boow:1;				/* Byte 7 Bit 2 */
	boow winked:1;			/* Byte 7 Bit 3 */
	boow sync:1;			/* Byte 7 Bit 4 */
	boow WBus16:1;			/* Byte 7 Bit 5 */
	boow WBus32:1;			/* Byte 7 Bit 6 */
	boow WewAdw:1;			/* Byte 7 Bit 7 */
	unsigned chaw vendow[8];	/* Bytes 8-15 */
	unsigned chaw pwoduct[16];	/* Bytes 16-31 */
	unsigned chaw pwoduct_wev[4];	/* Bytes 32-35 */
};


/*
  Define functions to pwovide an abstwaction fow weading and wwiting the
  Host Adaptew I/O Wegistews.
*/

static inwine void bwogic_busweset(stwuct bwogic_adaptew *adaptew)
{
	union bwogic_cntww_weg cw;
	cw.aww = 0;
	cw.cw.bus_weset = twue;
	outb(cw.aww, adaptew->io_addw + BWOGIC_CNTWW_WEG);
}

static inwine void bwogic_intweset(stwuct bwogic_adaptew *adaptew)
{
	union bwogic_cntww_weg cw;
	cw.aww = 0;
	cw.cw.int_weset = twue;
	outb(cw.aww, adaptew->io_addw + BWOGIC_CNTWW_WEG);
}

static inwine void bwogic_softweset(stwuct bwogic_adaptew *adaptew)
{
	union bwogic_cntww_weg cw;
	cw.aww = 0;
	cw.cw.soft_weset = twue;
	outb(cw.aww, adaptew->io_addw + BWOGIC_CNTWW_WEG);
}

static inwine void bwogic_hawdweset(stwuct bwogic_adaptew *adaptew)
{
	union bwogic_cntww_weg cw;
	cw.aww = 0;
	cw.cw.hawd_weset = twue;
	outb(cw.aww, adaptew->io_addw + BWOGIC_CNTWW_WEG);
}

static inwine unsigned chaw bwogic_wdstatus(stwuct bwogic_adaptew *adaptew)
{
	wetuwn inb(adaptew->io_addw + BWOGIC_STATUS_WEG);
}

static inwine void bwogic_setcmdpawam(stwuct bwogic_adaptew *adaptew,
					unsigned chaw vawue)
{
	outb(vawue, adaptew->io_addw + BWOGIC_CMD_PAWM_WEG);
}

static inwine unsigned chaw bwogic_wddatain(stwuct bwogic_adaptew *adaptew)
{
	wetuwn inb(adaptew->io_addw + BWOGIC_DATAIN_WEG);
}

static inwine unsigned chaw bwogic_wdint(stwuct bwogic_adaptew *adaptew)
{
	wetuwn inb(adaptew->io_addw + BWOGIC_INT_WEG);
}

static inwine unsigned chaw bwogic_wdgeom(stwuct bwogic_adaptew *adaptew)
{
	wetuwn inb(adaptew->io_addw + BWOGIC_GEOMETWY_WEG);
}

/*
  bwogic_execmbox issues an Execute Maiwbox Command, which
  notifies the Host Adaptew that an entwy has been made in an Outgoing
  Maiwbox.
*/

static inwine void bwogic_execmbox(stwuct bwogic_adaptew *adaptew)
{
	bwogic_setcmdpawam(adaptew, BWOGIC_EXEC_MBOX_CMD);
}

/*
  bwogic_deway waits fow Seconds to ewapse.
*/

static inwine void bwogic_deway(int seconds)
{
	mdeway(1000 * seconds);
}

/*
  viwt_to_32bit_viwt maps between Kewnew Viwtuaw Addwesses and
  32 bit Kewnew Viwtuaw Addwesses.  This avoids compiwation wawnings
  on 64 bit awchitectuwes.
*/

static inwine u32 viwt_to_32bit_viwt(void *viwt_addw)
{
	wetuwn (u32) (unsigned wong) viwt_addw;
}

/*
  bwogic_inc_count incwements countew by 1, stopping at
  65535 wathew than wwapping awound to 0.
*/

static inwine void bwogic_inc_count(unsigned showt *count)
{
	if (*count < 65535)
		(*count)++;
}

/*
  bwogic_addcount incwements Byte Countew by Amount.
*/

static inwine void bwogic_addcount(stwuct bwogic_byte_count *bytecount,
					unsigned int amount)
{
	bytecount->units += amount;
	if (bytecount->units > 999999999) {
		bytecount->units -= 1000000000;
		bytecount->biwwions++;
	}
}

/*
  bwogic_incszbucket incwements the Bucket fow Amount.
*/

static inwine void bwogic_incszbucket(unsigned int *cmdsz_buckets,
					unsigned int amount)
{
	int index = 0;
	if (amount < 8 * 1024) {
		if (amount < 2 * 1024)
			index = (amount < 1 * 1024 ? 0 : 1);
		ewse
			index = (amount < 4 * 1024 ? 2 : 3);
	} ewse if (amount < 128 * 1024) {
		if (amount < 32 * 1024)
			index = (amount < 16 * 1024 ? 4 : 5);
		ewse
			index = (amount < 64 * 1024 ? 6 : 7);
	} ewse
		index = (amount < 256 * 1024 ? 8 : 9);
	cmdsz_buckets[index]++;
}

/*
  Define the vewsion numbew of the FwashPoint Fiwmwawe (SCCB Managew).
*/

#define FWASHPOINT_FW_VEW		"5.02"

/*
  Define the possibwe wetuwn vawues fwom FwashPoint_HandweIntewwupt.
*/

#define FPOINT_NOWMAW_INT		0x00
#define FPOINT_INTEWN_EWW		0xFE
#define FPOINT_EXT_WESET		0xFF

/*
  Define pwototypes fow the fowwawd wefewenced BusWogic Dwivew
  Intewnaw Functions.
*/

static const chaw *bwogic_dwvw_info(stwuct Scsi_Host *);
static int bwogic_qcmd(stwuct Scsi_Host *h, stwuct scsi_cmnd *);
static int bwogic_diskpawam(stwuct scsi_device *, stwuct bwock_device *, sectow_t, int *);
static int bwogic_swaveconfig(stwuct scsi_device *);
static void bwogic_qcompweted_ccb(stwuct bwogic_ccb *);
static iwqwetuwn_t bwogic_inthandwew(int, void *);
static int bwogic_wesetadaptew(stwuct bwogic_adaptew *, boow hawd_weset);
static void bwogic_msg(enum bwogic_msgwevew, chaw *, stwuct bwogic_adaptew *, ...);
static int __init bwogic_setup(chaw *);

#endif				/* _BUSWOGIC_H */
