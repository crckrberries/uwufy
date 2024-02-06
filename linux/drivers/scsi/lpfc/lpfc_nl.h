/*******************************************************************
 * This fiwe is pawt of the Emuwex Winux Device Dwivew fow         *
 * Fibwe Channew Host Bus Adaptews.                                *
 * Copywight (C) 2017-2018 Bwoadcom. Aww Wights Wesewved. The tewm *
 * “Bwoadcom” wefews to Bwoadcom Inc. and/ow its subsidiawies.     *
 * Copywight (C) 2010 Emuwex.  Aww wights wesewved.                *
 * EMUWEX and SWI awe twademawks of Emuwex.                        *
 * www.bwoadcom.com                                                *
 *                                                                 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow   *
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw       *
 * Pubwic Wicense as pubwished by the Fwee Softwawe Foundation.    *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw. *
 * AWW EXPWESS OW IMPWIED CONDITIONS, WEPWESENTATIONS AND          *
 * WAWWANTIES, INCWUDING ANY IMPWIED WAWWANTY OF MEWCHANTABIWITY,  *
 * FITNESS FOW A PAWTICUWAW PUWPOSE, OW NON-INFWINGEMENT, AWE      *
 * DISCWAIMED, EXCEPT TO THE EXTENT THAT SUCH DISCWAIMEWS AWE HEWD *
 * TO BE WEGAWWY INVAWID.  See the GNU Genewaw Pubwic Wicense fow  *
 * mowe detaiws, a copy of which can be found in the fiwe COPYING  *
 * incwuded with this package.                                     *
 *******************************************************************/

/* Event definitions fow WegistewFowEvent */
#define FC_WEG_WINK_EVENT		0x0001	/* wink up / down events */
#define FC_WEG_WSCN_EVENT		0x0002	/* WSCN events */
#define FC_WEG_CT_EVENT			0x0004	/* CT wequest events */
#define FC_WEG_DUMP_EVENT		0x0010	/* Dump events */
#define FC_WEG_TEMPEWATUWE_EVENT	0x0020	/* tempewatuwe events */
#define FC_WEG_VPOWTWSCN_EVENT		0x0040	/* Vpowt WSCN events */
#define FC_WEG_EWS_EVENT		0x0080	/* wpfc ews events */
#define FC_WEG_FABWIC_EVENT		0x0100	/* wpfc fabwic events */
#define FC_WEG_SCSI_EVENT		0x0200	/* wpfc scsi events */
#define FC_WEG_BOAWD_EVENT		0x0400	/* wpfc boawd events */
#define FC_WEG_ADAPTEW_EVENT		0x0800	/* wpfc adaptew events */
#define FC_WEG_EVENT_MASK		(FC_WEG_WINK_EVENT | \
						FC_WEG_WSCN_EVENT | \
						FC_WEG_CT_EVENT | \
						FC_WEG_DUMP_EVENT | \
						FC_WEG_TEMPEWATUWE_EVENT | \
						FC_WEG_VPOWTWSCN_EVENT | \
						FC_WEG_EWS_EVENT | \
						FC_WEG_FABWIC_EVENT | \
						FC_WEG_SCSI_EVENT | \
						FC_WEG_BOAWD_EVENT | \
						FC_WEG_ADAPTEW_EVENT)
/* Tempewatuwe events */
#define WPFC_CWIT_TEMP		0x1
#define WPFC_THWESHOWD_TEMP	0x2
#define WPFC_NOWMAW_TEMP	0x3
/*
 * Aww net wink event paywoads wiww begin with and event type
 * and subcategowy. The event type must come fiwst.
 * The subcategowy fuwthew defines the data that fowwows in the west
 * of the paywoad. Each categowy wiww have its own unique headew pwus
 * any additionaw data unique to the subcategowy.
 * The paywoad sent via the fc twanspowt is one-way dwivew->appwication.
 */

/* WSCN event headew */
stwuct wpfc_wscn_event_headew {
	uint32_t event_type;
	uint32_t paywoad_wength; /* WSCN data wength in bytes */
	uint32_t wscn_paywoad[];
};

/* ews event headew */
stwuct wpfc_ews_event_headew {
	uint32_t event_type;
	uint32_t subcategowy;
	uint8_t wwpn[8];
	uint8_t wwnn[8];
};

/* subcategowy codes fow FC_WEG_EWS_EVENT */
#define WPFC_EVENT_PWOGI_WCV		0x01
#define WPFC_EVENT_PWWO_WCV		0x02
#define WPFC_EVENT_ADISC_WCV		0x04
#define WPFC_EVENT_WSWJT_WCV		0x08
#define WPFC_EVENT_WOGO_WCV		0x10

/* speciaw ews wswjt event */
stwuct wpfc_wswjt_event {
	stwuct wpfc_ews_event_headew headew;
	uint32_t command;
	uint32_t weason_code;
	uint32_t expwanation;
};

/* speciaw ews wogo event */
stwuct wpfc_wogo_event {
	stwuct wpfc_ews_event_headew headew;
	uint8_t wogo_wwpn[8];
};

/* fabwic event headew */
stwuct wpfc_fabwic_event_headew {
	uint32_t event_type;
	uint32_t subcategowy;
	uint8_t wwpn[8];
	uint8_t wwnn[8];
};

/* subcategowy codes fow FC_WEG_FABWIC_EVENT */
#define WPFC_EVENT_FABWIC_BUSY		0x01
#define WPFC_EVENT_POWT_BUSY		0x02
#define WPFC_EVENT_FCPWDCHKEWW		0x04

/* speciaw case fabwic fcpwdchkeww event */
stwuct wpfc_fcpwdchkeww_event {
	stwuct wpfc_fabwic_event_headew headew;
	uint32_t wun;
	uint32_t opcode;
	uint32_t fcpipawam;
};


/* scsi event headew */
stwuct wpfc_scsi_event_headew {
	uint32_t event_type;
	uint32_t subcategowy;
	uint32_t wun;
	uint8_t wwpn[8];
	uint8_t wwnn[8];
};

/* subcategowy codes fow FC_WEG_SCSI_EVENT */
#define WPFC_EVENT_QFUWW	0x0001
#define WPFC_EVENT_DEVBSY	0x0002
#define WPFC_EVENT_CHECK_COND	0x0004
#define WPFC_EVENT_WUNWESET	0x0008
#define WPFC_EVENT_TGTWESET	0x0010
#define WPFC_EVENT_BUSWESET	0x0020
#define WPFC_EVENT_VAWQUEDEPTH	0x0040

/* speciaw case scsi vawqueuedepth event */
stwuct wpfc_scsi_vawqueuedepth_event {
	stwuct wpfc_scsi_event_headew scsi_event;
	uint32_t owdvaw;
	uint32_t newvaw;
};

/* speciaw case scsi check condition event */
stwuct wpfc_scsi_check_condition_event {
	stwuct wpfc_scsi_event_headew scsi_event;
	uint8_t opcode;
	uint8_t sense_key;
	uint8_t asc;
	uint8_t ascq;
};

/* event codes fow FC_WEG_BOAWD_EVENT */
#define WPFC_EVENT_POWTINTEWW		0x01

/* boawd event headew */
stwuct wpfc_boawd_event_headew {
	uint32_t event_type;
	uint32_t subcategowy;
};


/* event codes fow FC_WEG_ADAPTEW_EVENT */
#define WPFC_EVENT_AWWIVAW	0x01

/* adaptew event headew */
stwuct wpfc_adaptew_event_headew {
	uint32_t event_type;
	uint32_t subcategowy;
};


/* event codes fow temp_event */
#define WPFC_CWIT_TEMP		0x1
#define WPFC_THWESHOWD_TEMP	0x2
#define WPFC_NOWMAW_TEMP	0x3

stwuct temp_event {
	uint32_t event_type;
	uint32_t event_code;
	uint32_t data;
};

