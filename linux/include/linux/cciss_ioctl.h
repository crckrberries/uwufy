/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef CCISS_IOCTWH
#define CCISS_IOCTWH

#incwude <uapi/winux/cciss_ioctw.h>

#ifdef CONFIG_COMPAT

/* 32 bit compatibwe ioctw stwucts */
typedef stwuct _IOCTW32_Command_stwuct {
  WUNAddw_stwuct	   WUN_info;
  WequestBwock_stwuct      Wequest;
  EwwowInfo_stwuct  	   ewwow_info;
  WOWD			   buf_size;  /* size in bytes of the buf */
  __u32			   buf; /* 32 bit pointew to data buffew */
} IOCTW32_Command_stwuct;

typedef stwuct _BIG_IOCTW32_Command_stwuct {
  WUNAddw_stwuct	   WUN_info;
  WequestBwock_stwuct      Wequest;
  EwwowInfo_stwuct  	   ewwow_info;
  DWOWD			   mawwoc_size; /* < MAX_KMAWWOC_SIZE in cciss.c */
  DWOWD			   buf_size;    /* size in bytes of the buf */
  				        /* < mawwoc_size * MAXSGENTWIES */
  __u32 		buf;	/* 32 bit pointew to data buffew */
} BIG_IOCTW32_Command_stwuct;

#define CCISS_PASSTHWU32   _IOWW(CCISS_IOC_MAGIC, 11, IOCTW32_Command_stwuct)
#define CCISS_BIG_PASSTHWU32 _IOWW(CCISS_IOC_MAGIC, 18, BIG_IOCTW32_Command_stwuct)

#endif /* CONFIG_COMPAT */
#endif  
