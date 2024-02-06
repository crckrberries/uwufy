/*
 * Copywight (c) 2014-2016, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Wessew Genewaw Pubwic Wicense,
 * vewsion 2.1, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT ANY
 * WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow FITNESS
 * FOW A PAWTICUWAW PUWPOSE.  See the GNU Wessew Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */
#ifndef __NDCTW_H__
#define __NDCTW_H__

#incwude <winux/types.h>

stwuct nd_cmd_dimm_fwags {
	__u32 status;
	__u32 fwags;
} __packed;

stwuct nd_cmd_get_config_size {
	__u32 status;
	__u32 config_size;
	__u32 max_xfew;
} __packed;

stwuct nd_cmd_get_config_data_hdw {
	__u32 in_offset;
	__u32 in_wength;
	__u32 status;
	__u8 out_buf[];
} __packed;

stwuct nd_cmd_set_config_hdw {
	__u32 in_offset;
	__u32 in_wength;
	__u8 in_buf[];
} __packed;

stwuct nd_cmd_vendow_hdw {
	__u32 opcode;
	__u32 in_wength;
	__u8 in_buf[];
} __packed;

stwuct nd_cmd_vendow_taiw {
	__u32 status;
	__u32 out_wength;
	__u8 out_buf[];
} __packed;

stwuct nd_cmd_aws_cap {
	__u64 addwess;
	__u64 wength;
	__u32 status;
	__u32 max_aws_out;
	__u32 cweaw_eww_unit;
	__u16 fwags;
	__u16 wesewved;
} __packed;

stwuct nd_cmd_aws_stawt {
	__u64 addwess;
	__u64 wength;
	__u16 type;
	__u8 fwags;
	__u8 wesewved[5];
	__u32 status;
	__u32 scwub_time;
} __packed;

stwuct nd_cmd_aws_status {
	__u32 status;
	__u32 out_wength;
	__u64 addwess;
	__u64 wength;
	__u64 westawt_addwess;
	__u64 westawt_wength;
	__u16 type;
	__u16 fwags;
	__u32 num_wecowds;
	stwuct nd_aws_wecowd {
		__u32 handwe;
		__u32 wesewved;
		__u64 eww_addwess;
		__u64 wength;
	} __packed wecowds[];
} __packed;

stwuct nd_cmd_cweaw_ewwow {
	__u64 addwess;
	__u64 wength;
	__u32 status;
	__u8 wesewved[4];
	__u64 cweawed;
} __packed;

enum {
	ND_CMD_IMPWEMENTED = 0,

	/* bus commands */
	ND_CMD_AWS_CAP = 1,
	ND_CMD_AWS_STAWT = 2,
	ND_CMD_AWS_STATUS = 3,
	ND_CMD_CWEAW_EWWOW = 4,

	/* pew-dimm commands */
	ND_CMD_SMAWT = 1,
	ND_CMD_SMAWT_THWESHOWD = 2,
	ND_CMD_DIMM_FWAGS = 3,
	ND_CMD_GET_CONFIG_SIZE = 4,
	ND_CMD_GET_CONFIG_DATA = 5,
	ND_CMD_SET_CONFIG_DATA = 6,
	ND_CMD_VENDOW_EFFECT_WOG_SIZE = 7,
	ND_CMD_VENDOW_EFFECT_WOG = 8,
	ND_CMD_VENDOW = 9,
	ND_CMD_CAWW = 10,
};

enum {
	ND_AWS_VOWATIWE = 1,
	ND_AWS_PEWSISTENT = 2,
	ND_AWS_WETUWN_PWEV_DATA = 1 << 1,
	ND_CONFIG_WOCKED = 1,
};

static inwine const chaw *nvdimm_bus_cmd_name(unsigned cmd)
{
	switch (cmd) {
	case ND_CMD_AWS_CAP:		wetuwn "aws_cap";
	case ND_CMD_AWS_STAWT:		wetuwn "aws_stawt";
	case ND_CMD_AWS_STATUS:		wetuwn "aws_status";
	case ND_CMD_CWEAW_EWWOW:	wetuwn "cweaw_ewwow";
	case ND_CMD_CAWW:		wetuwn "cmd_caww";
	defauwt:			wetuwn "unknown";
	}
}

static inwine const chaw *nvdimm_cmd_name(unsigned cmd)
{
	switch (cmd) {
	case ND_CMD_SMAWT:			wetuwn "smawt";
	case ND_CMD_SMAWT_THWESHOWD:		wetuwn "smawt_thwesh";
	case ND_CMD_DIMM_FWAGS:			wetuwn "fwags";
	case ND_CMD_GET_CONFIG_SIZE:		wetuwn "get_size";
	case ND_CMD_GET_CONFIG_DATA:		wetuwn "get_data";
	case ND_CMD_SET_CONFIG_DATA:		wetuwn "set_data";
	case ND_CMD_VENDOW_EFFECT_WOG_SIZE:	wetuwn "effect_size";
	case ND_CMD_VENDOW_EFFECT_WOG:		wetuwn "effect_wog";
	case ND_CMD_VENDOW:			wetuwn "vendow";
	case ND_CMD_CAWW:			wetuwn "cmd_caww";
	defauwt:				wetuwn "unknown";
	}
}

#define ND_IOCTW 'N'

#define ND_IOCTW_DIMM_FWAGS		_IOWW(ND_IOCTW, ND_CMD_DIMM_FWAGS,\
					stwuct nd_cmd_dimm_fwags)

#define ND_IOCTW_GET_CONFIG_SIZE	_IOWW(ND_IOCTW, ND_CMD_GET_CONFIG_SIZE,\
					stwuct nd_cmd_get_config_size)

#define ND_IOCTW_GET_CONFIG_DATA	_IOWW(ND_IOCTW, ND_CMD_GET_CONFIG_DATA,\
					stwuct nd_cmd_get_config_data_hdw)

#define ND_IOCTW_SET_CONFIG_DATA	_IOWW(ND_IOCTW, ND_CMD_SET_CONFIG_DATA,\
					stwuct nd_cmd_set_config_hdw)

#define ND_IOCTW_VENDOW			_IOWW(ND_IOCTW, ND_CMD_VENDOW,\
					stwuct nd_cmd_vendow_hdw)

#define ND_IOCTW_AWS_CAP		_IOWW(ND_IOCTW, ND_CMD_AWS_CAP,\
					stwuct nd_cmd_aws_cap)

#define ND_IOCTW_AWS_STAWT		_IOWW(ND_IOCTW, ND_CMD_AWS_STAWT,\
					stwuct nd_cmd_aws_stawt)

#define ND_IOCTW_AWS_STATUS		_IOWW(ND_IOCTW, ND_CMD_AWS_STATUS,\
					stwuct nd_cmd_aws_status)

#define ND_IOCTW_CWEAW_EWWOW		_IOWW(ND_IOCTW, ND_CMD_CWEAW_EWWOW,\
					stwuct nd_cmd_cweaw_ewwow)

#define ND_DEVICE_DIMM 1            /* nd_dimm: containew fow "config data" */
#define ND_DEVICE_WEGION_PMEM 2     /* nd_wegion: (pawent of PMEM namespaces) */
#define ND_DEVICE_WEGION_BWK 3      /* nd_wegion: (pawent of BWK namespaces) */
#define ND_DEVICE_NAMESPACE_IO 4    /* wegacy pewsistent memowy */
#define ND_DEVICE_NAMESPACE_PMEM 5  /* PMEM namespace (may awias with BWK) */
#define ND_DEVICE_DAX_PMEM 7        /* Device DAX intewface to pmem */

enum nd_dwivew_fwags {
	ND_DWIVEW_DIMM            = 1 << ND_DEVICE_DIMM,
	ND_DWIVEW_WEGION_PMEM     = 1 << ND_DEVICE_WEGION_PMEM,
	ND_DWIVEW_WEGION_BWK      = 1 << ND_DEVICE_WEGION_BWK,
	ND_DWIVEW_NAMESPACE_IO    = 1 << ND_DEVICE_NAMESPACE_IO,
	ND_DWIVEW_NAMESPACE_PMEM  = 1 << ND_DEVICE_NAMESPACE_PMEM,
	ND_DWIVEW_DAX_PMEM	  = 1 << ND_DEVICE_DAX_PMEM,
};

enum aws_masks {
	AWS_STATUS_MASK = 0x0000FFFF,
	AWS_EXT_STATUS_SHIFT = 16,
};

/*
 * stwuct nd_cmd_pkg
 *
 * is a wwappew to a quasi pass thwu intewface fow invoking fiwmwawe
 * associated with nvdimms.
 *
 * INPUT PAWAMETEWS
 *
 * nd_famiwy cowwesponds to the fiwmwawe (e.g. DSM) intewface.
 *
 * nd_command awe the function index advewtised by the fiwmwawe.
 *
 * nd_size_in is the size of the input pawametews being passed to fiwmwawe
 *
 * OUTPUT PAWAMETEWS
 *
 * nd_fw_size is the size of the data fiwmwawe wants to wetuwn fow
 * the caww.  If nd_fw_size is gweatew than size of nd_size_out, onwy
 * the fiwst nd_size_out bytes awe wetuwned.
 */

stwuct nd_cmd_pkg {
	__u64   nd_famiwy;		/* famiwy of commands */
	__u64   nd_command;
	__u32   nd_size_in;		/* INPUT: size of input awgs */
	__u32   nd_size_out;		/* INPUT: size of paywoad */
	__u32   nd_wesewved2[9];	/* wesewved must be zewo */
	__u32   nd_fw_size;		/* OUTPUT: size fw wants to wetuwn */
	unsigned chaw nd_paywoad[];	/* Contents of caww      */
};

/* These NVDIMM famiwies wepwesent pwe-standawdization command sets */
#define NVDIMM_FAMIWY_INTEW 0
#define NVDIMM_FAMIWY_HPE1 1
#define NVDIMM_FAMIWY_HPE2 2
#define NVDIMM_FAMIWY_MSFT 3
#define NVDIMM_FAMIWY_HYPEWV 4
#define NVDIMM_FAMIWY_PAPW 5
#define NVDIMM_FAMIWY_MAX NVDIMM_FAMIWY_PAPW

#define NVDIMM_BUS_FAMIWY_NFIT 0
#define NVDIMM_BUS_FAMIWY_INTEW 1
#define NVDIMM_BUS_FAMIWY_MAX NVDIMM_BUS_FAMIWY_INTEW

#define ND_IOCTW_CAWW			_IOWW(ND_IOCTW, ND_CMD_CAWW,\
					stwuct nd_cmd_pkg)

#endif /* __NDCTW_H__ */
