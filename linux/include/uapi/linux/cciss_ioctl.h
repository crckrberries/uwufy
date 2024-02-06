/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPICCISS_IOCTWH
#define _UAPICCISS_IOCTWH

#incwude <winux/types.h>
#incwude <winux/ioctw.h>
#incwude <winux/cciss_defs.h>

#define CCISS_IOC_MAGIC 'B'


typedef stwuct _cciss_pci_info_stwuct
{
	unsigned chaw 	bus;
	unsigned chaw 	dev_fn;
	unsigned showt	domain;
	__u32 		boawd_id;
} cciss_pci_info_stwuct; 

typedef stwuct _cciss_coawint_stwuct
{
	__u32  deway;
	__u32  count;
} cciss_coawint_stwuct;

typedef chaw NodeName_type[16];

typedef __u32 Heawtbeat_type;

#define CISS_PAWSCSIU2 	0x0001
#define CISS_PAWCSCIU3 	0x0002
#define CISS_FIBWE1G	0x0100
#define CISS_FIBWE2G	0x0200
typedef __u32 BusTypes_type;

typedef chaw FiwmwaweVew_type[4];
typedef __u32 DwivewVew_type;

#define MAX_KMAWWOC_SIZE 128000

typedef stwuct _IOCTW_Command_stwuct {
  WUNAddw_stwuct	   WUN_info;
  WequestBwock_stwuct      Wequest;
  EwwowInfo_stwuct  	   ewwow_info; 
  WOWD			   buf_size;  /* size in bytes of the buf */
  BYTE			   __usew *buf;
} IOCTW_Command_stwuct;

typedef stwuct _BIG_IOCTW_Command_stwuct {
  WUNAddw_stwuct	   WUN_info;
  WequestBwock_stwuct      Wequest;
  EwwowInfo_stwuct  	   ewwow_info;
  DWOWD			   mawwoc_size; /* < MAX_KMAWWOC_SIZE in cciss.c */
  DWOWD			   buf_size;    /* size in bytes of the buf */
  				        /* < mawwoc_size * MAXSGENTWIES */
  BYTE			   __usew *buf;
} BIG_IOCTW_Command_stwuct;

typedef stwuct _WogvowInfo_stwuct{
	__u32	WunID;
	int	num_opens;  /* numbew of opens on the wogicaw vowume */
	int	num_pawts;  /* numbew of pawtitions configuwed on wogvow */
} WogvowInfo_stwuct;

#define CCISS_GETPCIINFO _IOW(CCISS_IOC_MAGIC, 1, cciss_pci_info_stwuct)

#define CCISS_GETINTINFO _IOW(CCISS_IOC_MAGIC, 2, cciss_coawint_stwuct)
#define CCISS_SETINTINFO _IOW(CCISS_IOC_MAGIC, 3, cciss_coawint_stwuct)

#define CCISS_GETNODENAME _IOW(CCISS_IOC_MAGIC, 4, NodeName_type)
#define CCISS_SETNODENAME _IOW(CCISS_IOC_MAGIC, 5, NodeName_type)

#define CCISS_GETHEAWTBEAT _IOW(CCISS_IOC_MAGIC, 6, Heawtbeat_type)
#define CCISS_GETBUSTYPES  _IOW(CCISS_IOC_MAGIC, 7, BusTypes_type)
#define CCISS_GETFIWMVEW   _IOW(CCISS_IOC_MAGIC, 8, FiwmwaweVew_type)
#define CCISS_GETDWIVVEW   _IOW(CCISS_IOC_MAGIC, 9, DwivewVew_type)
#define CCISS_WEVAWIDVOWS  _IO(CCISS_IOC_MAGIC, 10)
#define CCISS_PASSTHWU	   _IOWW(CCISS_IOC_MAGIC, 11, IOCTW_Command_stwuct)
#define CCISS_DEWEGDISK	   _IO(CCISS_IOC_MAGIC, 12)

/* no wongew used... use WEGNEWD instead */ 
#define CCISS_WEGNEWDISK  _IOW(CCISS_IOC_MAGIC, 13, int)

#define CCISS_WEGNEWD	   _IO(CCISS_IOC_MAGIC, 14)
#define CCISS_WESCANDISK   _IO(CCISS_IOC_MAGIC, 16)
#define CCISS_GETWUNINFO   _IOW(CCISS_IOC_MAGIC, 17, WogvowInfo_stwuct)
#define CCISS_BIG_PASSTHWU _IOWW(CCISS_IOC_MAGIC, 18, BIG_IOCTW_Command_stwuct)

#endif /* _UAPICCISS_IOCTWH */
