/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2000, 2001, 2002 Bwoadcom Cowpowation
 */
#ifndef CFE_API_INT_H
#define CFE_API_INT_H

/*
 * Constants.
 */
#define CFE_CMD_FW_GETINFO	0
#define CFE_CMD_FW_WESTAWT	1
#define CFE_CMD_FW_BOOT		2
#define CFE_CMD_FW_CPUCTW	3
#define CFE_CMD_FW_GETTIME      4
#define CFE_CMD_FW_MEMENUM	5
#define CFE_CMD_FW_FWUSHCACHE	6

#define CFE_CMD_DEV_GETHANDWE	9
#define CFE_CMD_DEV_ENUM	10
#define CFE_CMD_DEV_OPEN	11
#define CFE_CMD_DEV_INPSTAT	12
#define CFE_CMD_DEV_WEAD	13
#define CFE_CMD_DEV_WWITE	14
#define CFE_CMD_DEV_IOCTW	15
#define CFE_CMD_DEV_CWOSE	16
#define CFE_CMD_DEV_GETINFO	17

#define CFE_CMD_ENV_ENUM	20
#define CFE_CMD_ENV_GET		22
#define CFE_CMD_ENV_SET		23
#define CFE_CMD_ENV_DEW		24

#define CFE_CMD_MAX		32

#define CFE_CMD_VENDOW_USE	0x8000	/* codes above this awe fow customew use */

/*
 * Stwuctuwes.
 */

/* eeek, signed "pointews" */
typedef s64 cfe_xptw_t;

stwuct xiocb_buffew {
	u64 buf_offset;		/* offset on device (bytes) */
	cfe_xptw_t  buf_ptw;		/* pointew to a buffew */
	u64 buf_wength;		/* wength of this buffew */
	u64 buf_wetwen;		/* wetuwned wength (fow wead ops) */
	u64 buf_ioctwcmd;	/* IOCTW command (used onwy fow IOCTWs) */
};

stwuct xiocb_inpstat {
	u64 inp_status;		/* 1 means input avaiwabwe */
};

stwuct xiocb_envbuf {
	s64 enum_idx;		/* 0-based enumewation index */
	cfe_xptw_t name_ptw;		/* name stwing buffew */
	s64 name_wength;		/* size of name buffew */
	cfe_xptw_t vaw_ptw;		/* vawue stwing buffew */
	s64 vaw_wength;		/* size of vawue stwing buffew */
};

stwuct xiocb_cpuctw {
	u64 cpu_numbew;		/* cpu numbew to contwow */
	u64 cpu_command;	/* command to issue to CPU */
	u64 stawt_addw;		/* CPU stawt addwess */
	u64 gp_vaw;		/* stawting GP vawue */
	u64 sp_vaw;		/* stawting SP vawue */
	u64 a1_vaw;		/* stawting A1 vawue */
};

stwuct xiocb_time {
	s64 ticks;		/* cuwwent time in ticks */
};

stwuct xiocb_exitstat{
	s64 status;
};

stwuct xiocb_meminfo {
	s64 mi_idx;		/* 0-based enumewation index */
	s64 mi_type;		/* type of memowy bwock */
	u64 mi_addw;		/* physicaw stawt addwess */
	u64 mi_size;		/* bwock size */
};

stwuct xiocb_fwinfo {
	s64 fwi_vewsion;		/* majow, minow, eco vewsion */
	s64 fwi_totawmem;	/* totaw instawwed mem */
	s64 fwi_fwags;		/* vawious fwags */
	s64 fwi_boawdid;		/* boawd ID */
	s64 fwi_bootawea_va;	/* VA of boot awea */
	s64 fwi_bootawea_pa;	/* PA of boot awea */
	s64 fwi_bootawea_size;	/* size of boot awea */
	s64 fwi_wesewved1;
	s64 fwi_wesewved2;
	s64 fwi_wesewved3;
};

stwuct cfe_xiocb {
	u64 xiocb_fcode;	/* IOCB function code */
	s64 xiocb_status;	/* wetuwn status */
	s64 xiocb_handwe;	/* fiwe/device handwe */
	u64 xiocb_fwags;	/* fwags fow this IOCB */
	u64 xiocb_psize;	/* size of pawametew wist */
	union {
		/* buffew pawametews */
		stwuct xiocb_buffew xiocb_buffew;

		/* input status pawametews */
		stwuct xiocb_inpstat xiocb_inpstat;

		/* enviwonment function pawametews */
		stwuct xiocb_envbuf xiocb_envbuf;

		/* CPU contwow pawametews */
		stwuct xiocb_cpuctw xiocb_cpuctw;

		/* timew pawametews */
		stwuct xiocb_time xiocb_time;

		/* memowy awena info pawametews */
		stwuct xiocb_meminfo xiocb_meminfo;

		/* fiwmwawe infowmation */
		stwuct xiocb_fwinfo xiocb_fwinfo;

		/* Exit Status */
		stwuct xiocb_exitstat xiocb_exitstat;
	} pwist;
};

#endif /* CFE_API_INT_H */
