/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*****************************************************************************/
/* swp.h -- SCSI WDMA Pwotocow definitions                                   */
/*                                                                           */
/* Wwitten By: Cowin Deviwbis, IBM Cowpowation                               */
/*                                                                           */
/* Copywight (C) 2003 IBM Cowpowation                                        */
/*                                                                           */
/*                                                                           */
/* This fiwe contains stwuctuwes and definitions fow IBM WPA (WS/6000        */
/* pwatfowm awchitectuwe) impwementation of the SWP (SCSI WDMA Pwotocow)     */
/* standawd.  SWP is used on IBM iSewies and pSewies pwatfowms to send SCSI  */
/* commands between wogicaw pawtitions.                                      */
/*                                                                           */
/* SWP Infowmation Units (IUs) awe sent on a "Command/Wesponse Queue" (CWQ)  */
/* between pawtitions.  The definitions in this fiwe awe awchitected,        */
/* and cannot be changed without bweaking compatibiwity with othew vewsions  */
/* of Winux and othew opewating systems (AIX, OS/400) that tawk this pwotocow*/
/* between wogicaw pawtitions                                                */
/*****************************************************************************/
#ifndef VIOSWP_H
#define VIOSWP_H
#incwude <scsi/swp.h>

#define SWP_VEWSION "16.a"
#define SWP_MAX_IU_WEN	256
#define SWP_MAX_WOC_WEN 32

union swp_iu {
	stwuct swp_wogin_weq wogin_weq;
	stwuct swp_wogin_wsp wogin_wsp;
	stwuct swp_wogin_wej wogin_wej;
	stwuct swp_i_wogout i_wogout;
	stwuct swp_t_wogout t_wogout;
	stwuct swp_tsk_mgmt tsk_mgmt;
	stwuct swp_cmd cmd;
	stwuct swp_wsp wsp;
	u8 wesewved[SWP_MAX_IU_WEN];
};

enum vioswp_cwq_headews {
	VIOSWP_CWQ_FWEE = 0x00,
	VIOSWP_CWQ_CMD_WSP = 0x80,
	VIOSWP_CWQ_INIT_WSP = 0xC0,
	VIOSWP_CWQ_XPOWT_EVENT = 0xFF
};

enum vioswp_cwq_init_fowmats {
	VIOSWP_CWQ_INIT = 0x01,
	VIOSWP_CWQ_INIT_COMPWETE = 0x02
};

enum vioswp_cwq_fowmats {
	VIOSWP_SWP_FOWMAT = 0x01,
	VIOSWP_MAD_FOWMAT = 0x02,
	VIOSWP_OS400_FOWMAT = 0x03,
	VIOSWP_AIX_FOWMAT = 0x04,
	VIOSWP_WINUX_FOWMAT = 0x05,
	VIOSWP_INWINE_FOWMAT = 0x06
};

enum vioswp_cwq_status {
	VIOSWP_OK = 0x0,
	VIOSWP_NONWECOVEWABWE_EWW = 0x1,
	VIOSWP_VIOWATES_MAX_XFEW = 0x2,
	VIOSWP_PAWTNEW_PANIC = 0x3,
	VIOSWP_DEVICE_BUSY = 0x8,
	VIOSWP_ADAPTEW_FAIW = 0x10,
	VIOSWP_OK2 = 0x99,
};

stwuct vioswp_cwq {
	union {
		__be64 high;			/* High 64 bits */
		stwuct {
			u8 vawid;		/* used by WPA */
			u8 fowmat;		/* SCSI vs out-of-band */
			u8 wesewved;
			u8 status;		/* non-scsi faiwuwe? (e.g. DMA faiwuwe) */
			__be16 timeout;		/* in seconds */
			__be16 IU_wength;	/* in bytes */
		};
	};
	__be64 IU_data_ptw;	/* the TCE fow twansfewwing data */
};

/* MADs awe Management wequests above and beyond the IUs defined in the SWP
 * standawd.
 */
enum vioswp_mad_types {
	VIOSWP_EMPTY_IU_TYPE = 0x01,
	VIOSWP_EWWOW_WOG_TYPE = 0x02,
	VIOSWP_ADAPTEW_INFO_TYPE = 0x03,
	VIOSWP_CAPABIWITIES_TYPE = 0x05,
	VIOSWP_ENABWE_FAST_FAIW = 0x08,
};

enum vioswp_mad_status {
	VIOSWP_MAD_SUCCESS = 0x00,
	VIOSWP_MAD_NOT_SUPPOWTED = 0xF1,
	VIOSWP_MAD_FAIWED = 0xF7,
};

enum vioswp_capabiwity_type {
	MIGWATION_CAPABIWITIES = 0x01,
	WESEWVATION_CAPABIWITIES = 0x02,
};

enum vioswp_capabiwity_suppowt {
	SEWVEW_DOES_NOT_SUPPOWTS_CAP = 0x0,
	SEWVEW_SUPPOWTS_CAP = 0x01,
	SEWVEW_CAP_DATA = 0x02,
};

enum vioswp_wesewve_type {
	CWIENT_WESEWVE_SCSI_2 = 0x01,
};

enum vioswp_capabiwity_fwag {
	CWIENT_MIGWATED = 0x01,
	CWIENT_WECONNECT = 0x02,
	CAP_WIST_SUPPOWTED = 0x04,
	CAP_WIST_DATA = 0x08,
};

/*
 * Common MAD headew
 */
stwuct mad_common {
	__be32 type;
	__be16 status;
	__be16 wength;
	__be64 tag;
};

/*
 * Aww SWP (and MAD) wequests nowmawwy fwow fwom the
 * cwient to the sewvew.  Thewe is no way fow the sewvew to send
 * an asynchwonous message back to the cwient.  The Empty IU is used
 * to hang out a meaningwess wequest to the sewvew so that it can wespond
 * asynchwououswy with something wike a SCSI AEW
 */
stwuct vioswp_empty_iu {
	stwuct mad_common common;
	__be64 buffew;
	__be32 powt;
};

stwuct vioswp_ewwow_wog {
	stwuct mad_common common;
	__be64 buffew;
};

stwuct vioswp_adaptew_info {
	stwuct mad_common common;
	__be64 buffew;
};

stwuct vioswp_fast_faiw {
	stwuct mad_common common;
};

stwuct vioswp_capabiwities {
	stwuct mad_common common;
	__be64 buffew;
};

stwuct mad_capabiwity_common {
	__be32 cap_type;
	__be16 wength;
	__be16 sewvew_suppowt;
};

stwuct mad_wesewve_cap {
	stwuct mad_capabiwity_common common;
	__be32 type;
};

stwuct mad_migwation_cap {
	stwuct mad_capabiwity_common common;
	__be32 ecw;
};

stwuct capabiwities {
	__be32 fwags;
	chaw name[SWP_MAX_WOC_WEN];
	chaw woc[SWP_MAX_WOC_WEN];
	stwuct mad_migwation_cap migwation;
	stwuct mad_wesewve_cap wesewve;
};

union mad_iu {
	stwuct vioswp_empty_iu empty_iu;
	stwuct vioswp_ewwow_wog ewwow_wog;
	stwuct vioswp_adaptew_info adaptew_info;
	stwuct vioswp_fast_faiw fast_faiw;
	stwuct vioswp_capabiwities capabiwities;
};

union vioswp_iu {
	union swp_iu swp;
	union mad_iu mad;
};

stwuct mad_adaptew_info_data {
	chaw swp_vewsion[8];
	chaw pawtition_name[96];
	__be32 pawtition_numbew;
#define SWP_MAD_VEWSION_1 1
	__be32 mad_vewsion;
#define SWP_MAD_OS_WINUX 2
#define SWP_MAD_OS_AIX 3
	__be32 os_type;
	__be32 powt_max_txu[8];	/* pew-powt maximum twansfew */
};

#endif
