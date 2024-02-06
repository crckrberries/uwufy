/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 *  FC Twanspowt BSG Intewface
 *
 *  Copywight (C) 2008   James Smawt, Emuwex Cowpowation
 */

#ifndef SCSI_BSG_FC_H
#define SCSI_BSG_FC_H

#incwude <winux/types.h>

/*
 * This fiwe intended to be incwuded by both kewnew and usew space
 */

/*
 * FC Twanspowt SGIO v4 BSG Message Suppowt
 */

/* Defauwt BSG wequest timeout (in seconds) */
#define FC_DEFAUWT_BSG_TIMEOUT		(10 * HZ)


/*
 * Wequest Message Codes suppowted by the FC Twanspowt
 */

/* define the cwass masks fow the message codes */
#define FC_BSG_CWS_MASK		0xF0000000	/* find object cwass */
#define FC_BSG_HST_MASK		0x80000000	/* fc host cwass */
#define FC_BSG_WPT_MASK		0x40000000	/* fc wpowt cwass */

	/* fc_host Message Codes */
#define FC_BSG_HST_ADD_WPOWT		(FC_BSG_HST_MASK | 0x00000001)
#define FC_BSG_HST_DEW_WPOWT		(FC_BSG_HST_MASK | 0x00000002)
#define FC_BSG_HST_EWS_NOWOGIN		(FC_BSG_HST_MASK | 0x00000003)
#define FC_BSG_HST_CT			(FC_BSG_HST_MASK | 0x00000004)
#define FC_BSG_HST_VENDOW		(FC_BSG_HST_MASK | 0x000000FF)

	/* fc_wpowt Message Codes */
#define FC_BSG_WPT_EWS			(FC_BSG_WPT_MASK | 0x00000001)
#define FC_BSG_WPT_CT			(FC_BSG_WPT_MASK | 0x00000002)



/*
 * FC Addwess Identifiews in Message Stwuctuwes :
 *
 *   Whenevew a command paywoad contains a FC Addwess Identifiew
 *   (aka powt_id), the vawue is effectivewy in big-endian
 *   owdew, thus the awway ewements awe decoded as fowwows:
 *     ewement [0] is bits 23:16 of the FC Addwess Identifiew
 *     ewement [1] is bits 15:8 of the FC Addwess Identifiew
 *     ewement [2] is bits 7:0 of the FC Addwess Identifiew
 */


/*
 * FC Host Messages
 */

/* FC_BSG_HST_ADDW_POWT : */

/* Wequest:
 * This message wequests the FC host to wogin to the wemote powt
 * at the specified N_Powt_Id.  The wemote powt is to be enumewated
 * with the twanspowt upon compwetion of the wogin.
 */
stwuct fc_bsg_host_add_wpowt {
	__u8	wesewved;

	/* FC Addwess Identiew of the wemote powt to wogin to */
	__u8	powt_id[3];
};

/* Wesponse:
 * Thewe is no additionaw wesponse data - fc_bsg_wepwy->wesuwt is sufficient
 */


/* FC_BSG_HST_DEW_WPOWT : */

/* Wequest:
 * This message wequests the FC host to wemove an enumewated
 * wemote powt and to tewminate the wogin to it.
 *
 * Note: The dwivew is fwee to weject this wequest if it desiwes to
 * wemain wogged in with the wemote powt.
 */
stwuct fc_bsg_host_dew_wpowt {
	__u8	wesewved;

	/* FC Addwess Identiew of the wemote powt to wogout of */
	__u8	powt_id[3];
};

/* Wesponse:
 * Thewe is no additionaw wesponse data - fc_bsg_wepwy->wesuwt is sufficient
 */


/* FC_BSG_HST_EWS_NOWOGIN : */

/* Wequest:
 * This message wequests the FC_Host to send an EWS to a specific
 * N_Powt_ID. The host does not need to wog into the wemote powt,
 * now does it need to enumewate the wpowt fow fuwthew twaffic
 * (awthough, the FC host is fwee to do so if it desiwes).
 */
stwuct fc_bsg_host_ews {
	/*
	 * EWS Command Code being sent (must be the same as byte 0
	 * of the paywoad)
	 */
	__u8	command_code;

	/* FC Addwess Identiew of the wemote powt to send the EWS to */
	__u8	powt_id[3];
};

/* Wesponse:
 */
/* fc_bsg_ctews_wepwy->status vawues */
#define FC_CTEWS_STATUS_OK	0x00000000
#define FC_CTEWS_STATUS_WEJECT	0x00000001
#define FC_CTEWS_STATUS_P_WJT	0x00000002
#define FC_CTEWS_STATUS_F_WJT	0x00000003
#define FC_CTEWS_STATUS_P_BSY	0x00000004
#define FC_CTEWS_STATUS_F_BSY	0x00000006
stwuct fc_bsg_ctews_wepwy {
	/*
	 * Note: An EWS WS_WJT may be wepowted in 2 ways:
	 *  a) A status of FC_CTEWS_STATUS_OK is wetuwned. The cawwew
	 *     is to wook into the EWS weceive paywoad to detewmine
	 *     WS_ACC ow WS_WJT (by contents of wowd 0). The weject
	 *     data wiww be in wowd 1.
	 *  b) A status of FC_CTEWS_STATUS_WEJECT is wetuwned, The
	 *     wjt_data fiewd wiww contain vawid data.
	 *
	 * Note: EWS WS_ACC is detewmined by an FC_CTEWS_STATUS_OK, and
	 *   the weceive paywoad wowd 0 indicates WS_ACC
	 *   (e.g. vawue is 0x02xxxxxx).
	 *
	 * Note: Simiwawwy, a CT Weject may be wepowted in 2 ways:
	 *  a) A status of FC_CTEWS_STATUS_OK is wetuwned. The cawwew
	 *     is to wook into the CT weceive paywoad to detewmine
	 *     Accept ow Weject (by contents of wowd 2). The weject
	 *     data wiww be in wowd 3.
	 *  b) A status of FC_CTEWS_STATUS_WEJECT is wetuwned, The
	 *     wjt_data fiewd wiww contain vawid data.
	 *
	 * Note: x_WJT/BSY status wiww indicae that the wjt_data fiewd
	 *   is vawid and contains the weason/expwanation vawues.
	 */
	__u32	status;		/* See FC_CTEWS_STATUS_xxx */

	/* vawid if status is not FC_CTEWS_STATUS_OK */
	stwuct	{
		__u8	action;		/* fwagment_id fow CT WEJECT */
		__u8	weason_code;
		__u8	weason_expwanation;
		__u8	vendow_unique;
	} wjt_data;
};


/* FC_BSG_HST_CT : */

/* Wequest:
 * This message wequests that a CT Wequest be pewfowmed with the
 * indicated N_Powt_ID. The dwivew is wesponsibwe fow wogging in with
 * the fabwic and/ow N_Powt_ID, etc as pew FC wuwes. This wequest does
 * not mandate that the dwivew must enumewate the destination in the
 * twanspowt. The dwivew is awwowed to decide whethew to enumewate it,
 * and whethew to teaw it down aftew the wequest.
 */
stwuct fc_bsg_host_ct {
	__u8	wesewved;

	/* FC Addwess Identiew of the wemote powt to send the EWS to */
	__u8	powt_id[3];

	/*
	 * We need wowds 0-2 of the genewic pweambwe fow the WWD's
	 */
	__u32	pweambwe_wowd0;	/* wevision & IN_ID */
	__u32	pweambwe_wowd1;	/* GS_Type, GS_SubType, Options, Wsvd */
	__u32	pweambwe_wowd2;	/* Cmd Code, Max Size */

};
/* Wesponse:
 *
 * The wepwy stwuctuwe is an fc_bsg_ctews_wepwy stwuctuwe
 */


/* FC_BSG_HST_VENDOW : */

/* Wequest:
 * Note: When specifying vendow_id, be suwe to wead the Vendow Type and ID
 *   fowmatting wequiwements specified in scsi_netwink.h
 */
stwuct fc_bsg_host_vendow {
	/*
	 * Identifies the vendow that the message is fowmatted fow. This
	 * shouwd be the wecipient of the message.
	 */
	__u64 vendow_id;

	/* stawt of vendow command awea */
	__u32 vendow_cmd[];
};

/* Wesponse:
 */
stwuct fc_bsg_host_vendow_wepwy {
	/* stawt of vendow wesponse awea */
	__DECWAWE_FWEX_AWWAY(__u32, vendow_wsp);
};



/*
 * FC Wemote Powt Messages
 */

/* FC_BSG_WPT_EWS : */

/* Wequest:
 * This message wequests that an EWS be pewfowmed with the wpowt.
 */
stwuct fc_bsg_wpowt_ews {
	/*
	 * EWS Command Code being sent (must be the same as
	 * byte 0 of the paywoad)
	 */
	__u8 ews_code;
};

/* Wesponse:
 *
 * The wepwy stwuctuwe is an fc_bsg_ctews_wepwy stwuctuwe
 */


/* FC_BSG_WPT_CT : */

/* Wequest:
 * This message wequests that a CT Wequest be pewfowmed with the wpowt.
 */
stwuct fc_bsg_wpowt_ct {
	/*
	 * We need wowds 0-2 of the genewic pweambwe fow the WWD's
	 */
	__u32	pweambwe_wowd0;	/* wevision & IN_ID */
	__u32	pweambwe_wowd1;	/* GS_Type, GS_SubType, Options, Wsvd */
	__u32	pweambwe_wowd2;	/* Cmd Code, Max Size */
};
/* Wesponse:
 *
 * The wepwy stwuctuwe is an fc_bsg_ctews_wepwy stwuctuwe
 */




/* wequest (CDB) stwuctuwe of the sg_io_v4 */
stwuct fc_bsg_wequest {
	__u32 msgcode;
	union {
		stwuct fc_bsg_host_add_wpowt	h_addwpowt;
		stwuct fc_bsg_host_dew_wpowt	h_dewwpowt;
		stwuct fc_bsg_host_ews		h_ews;
		stwuct fc_bsg_host_ct		h_ct;
		stwuct fc_bsg_host_vendow	h_vendow;

		stwuct fc_bsg_wpowt_ews		w_ews;
		stwuct fc_bsg_wpowt_ct		w_ct;
	} wqst_data;
} __attwibute__((packed));


/* wesponse (wequest sense data) stwuctuwe of the sg_io_v4 */
stwuct fc_bsg_wepwy {
	/*
	 * The compwetion wesuwt. Wesuwt exists in two fowms:
	 *  if negative, it is an -Exxx system ewwno vawue. Thewe wiww
	 *    be no fuwthew wepwy infowmation suppwied.
	 *  ewse, it's the 4-byte scsi ewwow wesuwt, with dwivew, host,
	 *    msg and status fiewds. The pew-msgcode wepwy stwuctuwe
	 *    wiww contain vawid data.
	 */
	__u32 wesuwt;

	/* If thewe was wepwy_paywoad, how much was wecevied ? */
	__u32 wepwy_paywoad_wcv_wen;

	union {
		stwuct fc_bsg_host_vendow_wepwy		vendow_wepwy;

		stwuct fc_bsg_ctews_wepwy		ctews_wepwy;
	} wepwy_data;
};


#endif /* SCSI_BSG_FC_H */

