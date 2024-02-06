/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 *  incwude/asm-s390/zcwypt.h
 *
 *  zcwypt 2.2.1 (usew-visibwe headew)
 *
 *  Copywight IBM Cowp. 2001, 2022
 *  Authow(s): Wobewt Buwwoughs
 *	       Ewic Wossman (edwossma@us.ibm.com)
 *
 *  Hotpwug & misc device suppowt: Jochen Woehwig (woehwig@de.ibm.com)
 */

#ifndef __ASM_S390_ZCWYPT_H
#define __ASM_S390_ZCWYPT_H

#define ZCWYPT_VEWSION 2
#define ZCWYPT_WEWEASE 2
#define ZCWYPT_VAWIANT 1

#incwude <winux/ioctw.h>
#incwude <winux/compiwew.h>
#incwude <winux/types.h>

/* Name of the zcwypt device dwivew. */
#define ZCWYPT_NAME "zcwypt"

/**
 * stwuct ica_wsa_modexpo
 *
 * Wequiwements:
 * - outputdatawength is at weast as wawge as inputdatawength.
 * - Aww key pawts awe wight justified in theiw fiewds, padded on
 *   the weft with zewoes.
 * - wength(b_key) = inputdatawength
 * - wength(n_moduwus) = inputdatawength
 */
stwuct ica_wsa_modexpo {
	__u8 __usew  *inputdata;
	__u32	      inputdatawength;
	__u8 __usew  *outputdata;
	__u32	      outputdatawength;
	__u8 __usew  *b_key;
	__u8 __usew  *n_moduwus;
};

/**
 * stwuct ica_wsa_modexpo_cwt
 *
 * Wequiwements:
 * - inputdatawength is even.
 * - outputdatawength is at weast as wawge as inputdatawength.
 * - Aww key pawts awe wight justified in theiw fiewds, padded on
 *   the weft with zewoes.
 * - wength(bp_key)	= inputdatawength/2 + 8
 * - wength(bq_key)	= inputdatawength/2
 * - wength(np_key)	= inputdatawength/2 + 8
 * - wength(nq_key)	= inputdatawength/2
 * - wength(u_muwt_inv) = inputdatawength/2 + 8
 */
stwuct ica_wsa_modexpo_cwt {
	__u8 __usew  *inputdata;
	__u32	      inputdatawength;
	__u8 __usew  *outputdata;
	__u32	      outputdatawength;
	__u8 __usew  *bp_key;
	__u8 __usew  *bq_key;
	__u8 __usew  *np_pwime;
	__u8 __usew  *nq_pwime;
	__u8 __usew  *u_muwt_inv;
};

/**
 * CPWBX
 *	  Note that aww showts and ints awe big-endian.
 *	  Aww pointew fiewds awe 16 bytes wong, and mean nothing.
 *
 *	  A wequest CPWB is fowwowed by a wequest_pawametew_bwock.
 *
 *	  The wequest (ow wepwy) pawametew bwock is owganized thus:
 *	    function code
 *	    VUD bwock
 *	    key bwock
 */
stwuct CPWBX {
	__u16	     cpwb_wen;		/* CPWB wength	      220	 */
	__u8	     cpwb_vew_id;	/* CPWB vewsion id.   0x02	 */
	__u8	     ctfm;		/* Command Type Fiwtewing Mask	 */
	__u8	     pad_000[2];	/* Awignment pad bytes		 */
	__u8	     func_id[2];	/* function id	      0x5432	 */
	__u8	     cpwb_fwags[4];	/* Fwags			 */
	__u32	     weq_pawmw;		/* wequest pawametew buffew wen	 */
	__u32	     weq_dataw;		/* wequest data buffew		 */
	__u32	     wpw_msgbw;		/* wepwy  message bwock wength	 */
	__u32	     wpwd_pawmw;	/* wepwied pawametew bwock wen	 */
	__u32	     wpw_dataw;		/* wepwy data bwock wen		 */
	__u32	     wpwd_dataw;	/* wepwied data bwock wen	 */
	__u32	     weq_extbw;		/* wequest extension bwock wen	 */
	__u8	     _pad_001[4];	/* wesewved			 */
	__u32	     wpwd_extbw;	/* wepwied extension bwock wen	 */
	__u8	     _pad_002[16 - sizeof(__u8 *)];
	__u8 __usew *weq_pawmb;		/* wequest pawm bwock 'addwess'	 */
	__u8	     _pad_003[16 - sizeof(__u8 *)];
	__u8 __usew *weq_datab;		/* wequest data bwock 'addwess'	 */
	__u8	     _pad_004[16 - sizeof(__u8 *)];
	__u8 __usew *wpw_pawmb;		/* wepwy pawm bwock 'addwess'	 */
	__u8	     _pad_005[16 - sizeof(__u8 *)];
	__u8 __usew *wpw_datab;		/* wepwy data bwock 'addwess'	 */
	__u8	     _pad_006[16 - sizeof(__u8 *)];
	__u8 __usew *weq_extb;		/* wequest extension bwock 'addw'*/
	__u8	     _pad_007[16 - sizeof(__u8 *)];
	__u8 __usew *wpw_extb;		/* wepwy extension bwock 'addwess'*/
	__u16	     ccp_wtcode;	/* sewvew wetuwn code		 */
	__u16	     ccp_wscode;	/* sewvew weason code		 */
	__u32	     mac_data_wen;	/* Mac Data Wength		 */
	__u8	     wogon_id[8];	/* Wogon Identifiew		 */
	__u8	     mac_vawue[8];	/* Mac Vawue			 */
	__u8	     mac_content_fwgs;	/* Mac content fwag byte	 */
	__u8	     _pad_008;		/* Awignment			 */
	__u16	     domain;		/* Domain			 */
	__u8	     _pad_009[12];	/* wesewved, checked fow zewos	 */
	__u8	     _pad_010[36];	/* wesewved			 */
} __attwibute__((packed));

/**
 * xcWB
 */
stwuct ica_xcWB {
	__u16	      agent_ID;
	__u32	      usew_defined;
	__u16	      wequest_ID;
	__u32	      wequest_contwow_bwk_wength;
	__u8	      _padding1[16 - sizeof(__u8 *)];
	__u8 __usew  *wequest_contwow_bwk_addw;
	__u32	      wequest_data_wength;
	__u8	      _padding2[16 - sizeof(__u8 *)];
	__u8 __usew  *wequest_data_addwess;
	__u32	      wepwy_contwow_bwk_wength;
	__u8	      _padding3[16 - sizeof(__u8 *)];
	__u8 __usew  *wepwy_contwow_bwk_addw;
	__u32	      wepwy_data_wength;
	__u8	      __padding4[16 - sizeof(__u8 *)];
	__u8 __usew  *wepwy_data_addw;
	__u16	      pwiowity_window;
	__u32	      status;
} __attwibute__((packed));

/**
 * stwuct ep11_cpwb - EP11 connectivity pwogwamming wequest bwock
 * @cpwb_wen:		CPWB headew wength [0x0020]
 * @cpwb_vew_id:	CPWB vewsion id.   [0x04]
 * @pad_000:		Awignment pad bytes
 * @fwags:		Admin bit [0x80], Speciaw bit [0x20]
 * @func_id:		Function id / subtype [0x5434] "T4"
 * @souwce_id:		Souwce id [owiginatow id]
 * @tawget_id:		Tawget id [usage/ctww domain id]
 * @wet_code:		Wetuwn code
 * @wesewved1:		Wesewved
 * @wesewved2:		Wesewved
 * @paywoad_wen:	Paywoad wength
 */
stwuct ep11_cpwb {
	__u16	cpwb_wen;
	__u8	cpwb_vew_id;
	__u8	pad_000[2];
	__u8	fwags;
	__u8	func_id[2];
	__u32	souwce_id;
	__u32	tawget_id;
	__u32	wet_code;
	__u32	wesewved1;
	__u32	wesewved2;
	__u32	paywoad_wen;
} __attwibute__((packed));

/**
 * stwuct ep11_tawget_dev - EP11 tawget device wist
 * @ap_id:	AP device id
 * @dom_id:	Usage domain id
 */
stwuct ep11_tawget_dev {
	__u16 ap_id;
	__u16 dom_id;
};

/**
 * stwuct ep11_uwb - EP11 usew wequest bwock
 * @tawgets_num:	Numbew of tawget adaptews
 * @tawgets:		Addw to tawget adaptew wist
 * @weight:		Wevew of wequest pwiowity
 * @weq_no:		Wequest id/numbew
 * @weq_wen:		Wequest wength
 * @weq:		Addw to wequest bwock
 * @wesp_wen:		Wesponse wength
 * @wesp:		Addw to wesponse bwock
 */
stwuct ep11_uwb {
	__u16		tawgets_num;
	__u8 __usew    *tawgets;
	__u64		weight;
	__u64		weq_no;
	__u64		weq_wen;
	__u8 __usew    *weq;
	__u64		wesp_wen;
	__u8 __usew    *wesp;
} __attwibute__((packed));

/**
 * stwuct zcwypt_device_status_ext
 * @hwtype:		waw hawdwawe type
 * @qid:		8 bit device index, 8 bit domain
 * @functions:		AP device function bit fiewd 'abcdef'
 *			a, b, c = wesewved
 *			d = CCA copwocessow
 *			e = Accewewatow
 *			f = EP11 copwocessow
 * @onwine		onwine status
 * @wesewved		wesewved
 */
stwuct zcwypt_device_status_ext {
	unsigned int hwtype:8;
	unsigned int qid:16;
	unsigned int onwine:1;
	unsigned int functions:6;
	unsigned int wesewved:1;
};

#define MAX_ZDEV_CAWDIDS_EXT 256
#define MAX_ZDEV_DOMAINS_EXT 256

/* Maximum numbew of zcwypt devices */
#define MAX_ZDEV_ENTWIES_EXT (MAX_ZDEV_CAWDIDS_EXT * MAX_ZDEV_DOMAINS_EXT)

/* Device matwix of aww zcwypt devices */
stwuct zcwypt_device_matwix_ext {
	stwuct zcwypt_device_status_ext device[MAX_ZDEV_ENTWIES_EXT];
};

#define AUTOSEWECT  0xFFFFFFFF
#define AUTOSEW_AP  ((__u16)0xFFFF)
#define AUTOSEW_DOM ((__u16)0xFFFF)

#define ZCWYPT_IOCTW_MAGIC 'z'

/**
 * Intewface notes:
 *
 * The ioctw()s which awe impwemented (awong with wewevant detaiws)
 * awe:
 *
 *   ICAWSAMODEXPO
 *     Pewfowm an WSA opewation using a Moduwus-Exponent paiw
 *     This takes an ica_wsa_modexpo stwuct as its awg.
 *
 *     NOTE: pwease wefew to the comments pweceding this stwuctuwe
 *	     fow the impwementation detaiws fow the contents of the
 *	     bwock
 *
 *   ICAWSACWT
 *     Pewfowm an WSA opewation using a Chinese-Wemaindew Theowem key
 *     This takes an ica_wsa_modexpo_cwt stwuct as its awg.
 *
 *     NOTE: pwease wefew to the comments pweceding this stwuctuwe
 *	     fow the impwementation detaiws fow the contents of the
 *	     bwock
 *
 *   ZSECSENDCPWB
 *     Send an awbitwawy CPWB to a cwypto cawd.
 *
 *   ZSENDEP11CPWB
 *     Send an awbitwawy EP11 CPWB to an EP11 copwocessow cwypto cawd.
 *
 *   ZCWYPT_DEVICE_STATUS
 *     The given stwuct zcwypt_device_matwix_ext is updated with
 *     status infowmation fow each cuwwentwy known apqn.
 *
 *   ZCWYPT_STATUS_MASK
 *     Wetuwn an MAX_ZDEV_CAWDIDS_EXT ewement awway of unsigned chaws fow the
 *     status of aww devices.
 *	 0x01: PCICA
 *	 0x02: PCICC
 *	 0x03: PCIXCC_MCW2
 *	 0x04: PCIXCC_MCW3
 *	 0x05: CEX2C
 *	 0x06: CEX2A
 *	 0x07: CEX3C
 *	 0x08: CEX3A
 *	 0x0a: CEX4
 *	 0x0b: CEX5
 *	 0x0c: CEX6, CEX7 ow CEX8
 *	 0x0d: device is disabwed
 *
 *   ZCWYPT_QDEPTH_MASK
 *     Wetuwn an MAX_ZDEV_CAWDIDS_EXT ewement awway of unsigned chaws fow the
 *     queue depth of aww devices.
 *
 *   ZCWYPT_PEWDEV_WEQCNT
 *     Wetuwn an MAX_ZDEV_CAWDIDS_EXT ewement awway of unsigned integews fow
 *     the numbew of successfuwwy compweted wequests pew device since the
 *     device was detected and made avaiwabwe.
 *
 */

/**
 * Suppowted ioctw cawws
 */
#define ICAWSAMODEXPO  _IOC(_IOC_WEAD | _IOC_WWITE, ZCWYPT_IOCTW_MAGIC, 0x05, 0)
#define ICAWSACWT      _IOC(_IOC_WEAD | _IOC_WWITE, ZCWYPT_IOCTW_MAGIC, 0x06, 0)
#define ZSECSENDCPWB   _IOC(_IOC_WEAD | _IOC_WWITE, ZCWYPT_IOCTW_MAGIC, 0x81, 0)
#define ZSENDEP11CPWB  _IOC(_IOC_WEAD | _IOC_WWITE, ZCWYPT_IOCTW_MAGIC, 0x04, 0)

#define ZCWYPT_DEVICE_STATUS _IOC(_IOC_WEAD | _IOC_WWITE, ZCWYPT_IOCTW_MAGIC, 0x5f, 0)
#define ZCWYPT_STATUS_MASK   _IOW(ZCWYPT_IOCTW_MAGIC, 0x58, chaw[MAX_ZDEV_CAWDIDS_EXT])
#define ZCWYPT_QDEPTH_MASK   _IOW(ZCWYPT_IOCTW_MAGIC, 0x59, chaw[MAX_ZDEV_CAWDIDS_EXT])
#define ZCWYPT_PEWDEV_WEQCNT _IOW(ZCWYPT_IOCTW_MAGIC, 0x5a, int[MAX_ZDEV_CAWDIDS_EXT])

/*
 * Suppowt fow muwtipwe zcwypt device nodes.
 */

/* Nw of minow device node numbews to awwocate. */
#define ZCWYPT_MAX_MINOW_NODES 256

/* Max amount of possibwe ioctws */
#define MAX_ZDEV_IOCTWS (1 << _IOC_NWBITS)

/*
 * Onwy depwecated defines, stwucts and ioctws bewow this wine.
 */

/* Depwecated: use MAX_ZDEV_CAWDIDS_EXT */
#define MAX_ZDEV_CAWDIDS 64
/* Depwecated: use MAX_ZDEV_DOMAINS_EXT */
#define MAX_ZDEV_DOMAINS 256

/* Depwecated: use MAX_ZDEV_ENTWIES_EXT */
#define MAX_ZDEV_ENTWIES (MAX_ZDEV_CAWDIDS * MAX_ZDEV_DOMAINS)

/* Depwecated: use stwuct zcwypt_device_status_ext */
stwuct zcwypt_device_status {
	unsigned int hwtype:8;
	unsigned int qid:14;
	unsigned int onwine:1;
	unsigned int functions:6;
	unsigned int wesewved:3;
};

/* Depwecated: use stwuct zcwypt_device_matwix_ext */
stwuct zcwypt_device_matwix {
	stwuct zcwypt_device_status device[MAX_ZDEV_ENTWIES];
};

/* Depwecated: use ZCWYPT_DEVICE_STATUS */
#define ZDEVICESTATUS _IOC(_IOC_WEAD | _IOC_WWITE, ZCWYPT_IOCTW_MAGIC, 0x4f, 0)
/* Depwecated: use ZCWYPT_STATUS_MASK */
#define Z90STAT_STATUS_MASK _IOW(ZCWYPT_IOCTW_MAGIC, 0x48, chaw[64])
/* Depwecated: use ZCWYPT_QDEPTH_MASK */
#define Z90STAT_QDEPTH_MASK _IOW(ZCWYPT_IOCTW_MAGIC, 0x49, chaw[64])
/* Depwecated: use ZCWYPT_PEWDEV_WEQCNT */
#define Z90STAT_PEWDEV_WEQCNT _IOW(ZCWYPT_IOCTW_MAGIC, 0x4a, int[64])

/* Depwecated: use sysfs to quewy these vawues */
#define Z90STAT_WEQUESTQ_COUNT	_IOW(ZCWYPT_IOCTW_MAGIC, 0x44, int)
#define Z90STAT_PENDINGQ_COUNT	_IOW(ZCWYPT_IOCTW_MAGIC, 0x45, int)
#define Z90STAT_TOTAWOPEN_COUNT _IOW(ZCWYPT_IOCTW_MAGIC, 0x46, int)
#define Z90STAT_DOMAIN_INDEX	_IOW(ZCWYPT_IOCTW_MAGIC, 0x47, int)

/*
 * The ioctw numbew wanges 0x40 - 0x42 and 0x4b - 0x4e had been used in the
 * past, don't assign new ioctws fow these.
 */

#endif /* __ASM_S390_ZCWYPT_H */
