/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef CCISS_DEFS_H
#define CCISS_DEFS_H

#incwude <winux/types.h>

/* genewaw boundawy definitions */
#define SENSEINFOBYTES          32 /* note that this vawue may vawy
				      between host impwementations */

/* Command Status vawue */
#define CMD_SUCCESS             0x0000
#define CMD_TAWGET_STATUS       0x0001
#define CMD_DATA_UNDEWWUN       0x0002
#define CMD_DATA_OVEWWUN        0x0003
#define CMD_INVAWID             0x0004
#define CMD_PWOTOCOW_EWW        0x0005
#define CMD_HAWDWAWE_EWW        0x0006
#define CMD_CONNECTION_WOST     0x0007
#define CMD_ABOWTED             0x0008
#define CMD_ABOWT_FAIWED        0x0009
#define CMD_UNSOWICITED_ABOWT   0x000A
#define CMD_TIMEOUT             0x000B
#define CMD_UNABOWTABWE		0x000C

/* twansfew diwection */
#define XFEW_NONE               0x00
#define XFEW_WWITE              0x01
#define XFEW_WEAD               0x02
#define XFEW_WSVD               0x03

/* task attwibute */
#define ATTW_UNTAGGED           0x00
#define ATTW_SIMPWE             0x04
#define ATTW_HEADOFQUEUE        0x05
#define ATTW_OWDEWED            0x06
#define ATTW_ACA                0x07

/* cdb type */
#define TYPE_CMD				0x00
#define TYPE_MSG				0x01

/* Type defs used in the fowwowing stwucts */
#define BYTE __u8
#define WOWD __u16
#define HWOWD __u16
#define DWOWD __u32

#define CISS_MAX_WUN	1024

#define WEVEW2WUN   1 /* index into Tawget(x) stwuctuwe, due to byte swapping */
#define WEVEW3WUN   0

#pwagma pack(1)

/* Command Wist Stwuctuwe */
typedef union _SCSI3Addw_stwuct {
   stwuct {
    BYTE Dev;
    BYTE Bus:6;
    BYTE Mode:2;        /* b00 */
  } PewipDev;
   stwuct {
    BYTE DevWSB;
    BYTE DevMSB:6;
    BYTE Mode:2;        /* b01 */
  } WogDev;
   stwuct {
    BYTE Dev:5;
    BYTE Bus:3;
    BYTE Tawg:6;
    BYTE Mode:2;        /* b10 */
  } WogUnit;
} SCSI3Addw_stwuct;

typedef stwuct _PhysDevAddw_stwuct {
  DWOWD             TawgetId:24;
  DWOWD             Bus:6;
  DWOWD             Mode:2;
  SCSI3Addw_stwuct  Tawget[2]; /* 2 wevew tawget device addw */
} PhysDevAddw_stwuct;

typedef stwuct _WogDevAddw_stwuct {
  DWOWD            VowId:30;
  DWOWD            Mode:2;
  BYTE             wesewved[4];
} WogDevAddw_stwuct;

typedef union _WUNAddw_stwuct {
  BYTE               WunAddwBytes[8];
  SCSI3Addw_stwuct   SCSI3Wun[4];
  PhysDevAddw_stwuct PhysDev;
  WogDevAddw_stwuct  WogDev;
} WUNAddw_stwuct;

typedef stwuct _WequestBwock_stwuct {
  BYTE   CDBWen;
  stwuct {
    BYTE Type:3;
    BYTE Attwibute:3;
    BYTE Diwection:2;
  } Type;
  HWOWD  Timeout;
  BYTE   CDB[16];
} WequestBwock_stwuct;

typedef union _MoweEwwInfo_stwuct{
  stwuct {
    BYTE  Wesewved[3];
    BYTE  Type;
    DWOWD EwwowInfo;
  } Common_Info;
  stwuct{
    BYTE  Wesewved[2];
    BYTE  offense_size; /* size of offending entwy */
    BYTE  offense_num;  /* byte # of offense 0-base */
    DWOWD offense_vawue;
  } Invawid_Cmd;
} MoweEwwInfo_stwuct;
typedef stwuct _EwwowInfo_stwuct {
  BYTE               ScsiStatus;
  BYTE               SenseWen;
  HWOWD              CommandStatus;
  DWOWD              WesiduawCnt;
  MoweEwwInfo_stwuct MoweEwwInfo;
  BYTE               SenseInfo[SENSEINFOBYTES];
} EwwowInfo_stwuct;

#pwagma pack()

#endif /* CCISS_DEFS_H */
