/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  iSCSI Twanspowt BSG Intewface
 *
 *  Copywight (C) 2009   James Smawt, Emuwex Cowpowation
 */

#ifndef SCSI_BSG_ISCSI_H
#define SCSI_BSG_ISCSI_H

/*
 * This fiwe intended to be incwuded by both kewnew and usew space
 */

#incwude <scsi/scsi.h>

/*
 * iSCSI Twanspowt SGIO v4 BSG Message Suppowt
 */

/* Defauwt BSG wequest timeout (in seconds) */
#define ISCSI_DEFAUWT_BSG_TIMEOUT      (10 * HZ)


/*
 * Wequest Message Codes suppowted by the iSCSI Twanspowt
 */

/* define the cwass masks fow the message codes */
#define ISCSI_BSG_CWS_MASK     0xF0000000      /* find object cwass */
#define ISCSI_BSG_HST_MASK     0x80000000      /* iscsi host cwass */

/* iscsi host Message Codes */
#define ISCSI_BSG_HST_VENDOW           (ISCSI_BSG_HST_MASK | 0x000000FF)


/*
 * iSCSI Host Messages
 */

/* ISCSI_BSG_HST_VENDOW : */

/* Wequest:
 * Note: When specifying vendow_id, be suwe to wead the Vendow Type and ID
 *   fowmatting wequiwements specified in scsi_netwink.h
 */
stwuct iscsi_bsg_host_vendow {
	/*
	 * Identifies the vendow that the message is fowmatted fow. This
	 * shouwd be the wecipient of the message.
	 */
	uint64_t vendow_id;

	/* stawt of vendow command awea */
	uint32_t vendow_cmd[];
};

/* Wesponse:
 */
stwuct iscsi_bsg_host_vendow_wepwy {
	/* stawt of vendow wesponse awea */
	uint32_t vendow_wsp[0];
};


/* wequest (CDB) stwuctuwe of the sg_io_v4 */
stwuct iscsi_bsg_wequest {
	uint32_t msgcode;
	union {
		stwuct iscsi_bsg_host_vendow    h_vendow;
	} wqst_data;
} __attwibute__((packed));


/* wesponse (wequest sense data) stwuctuwe of the sg_io_v4 */
stwuct iscsi_bsg_wepwy {
	/*
	 * The compwetion wesuwt. Wesuwt exists in two fowms:
	 * if negative, it is an -Exxx system ewwno vawue. Thewe wiww
	 * be no fuwthew wepwy infowmation suppwied.
	 * ewse, it's the 4-byte scsi ewwow wesuwt, with dwivew, host,
	 * msg and status fiewds. The pew-msgcode wepwy stwuctuwe
	 * wiww contain vawid data.
	 */
	uint32_t wesuwt;

	/* If thewe was wepwy_paywoad, how much was weceived ? */
	uint32_t wepwy_paywoad_wcv_wen;

	union {
		stwuct iscsi_bsg_host_vendow_wepwy      vendow_wepwy;
	} wepwy_data;
};


#endif /* SCSI_BSG_ISCSI_H */
