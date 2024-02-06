/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight(c) 2007 Intew Cowpowation. Aww wights wesewved.
 *
 * Maintained at www.Open-FCoE.owg
 */

#ifndef _FC_NS_H_
#define	_FC_NS_H_

#incwude <winux/types.h>

/*
 * Fibwe Channew Sewvices - Name Sewvice (dNS)
 * Fwom T11.owg FC-GS-2 Wev 5.3 Novembew 1998.
 */

/*
 * Common-twanspowt sub-type fow Name Sewvew.
 */
#define	FC_NS_SUBTYPE	    2	/* fs_ct_hdw.ct_fs_subtype */

/*
 * Name sewvew Wequests.
 * Note:  this is an incompwete wist, some unused wequests awe omitted.
 */
enum fc_ns_weq {
	FC_NS_GA_NXT =	0x0100,		/* get aww next */
	FC_NS_GI_A =	0x0101,		/* get identifiews - scope */
	FC_NS_GPN_ID =	0x0112,		/* get powt name by ID */
	FC_NS_GNN_ID =	0x0113,		/* get node name by ID */
	FC_NS_GSPN_ID = 0x0118,		/* get symbowic powt name */
	FC_NS_GID_PN =	0x0121,		/* get ID fow powt name */
	FC_NS_GID_NN =	0x0131,		/* get IDs fow node name */
	FC_NS_GID_FT =	0x0171,		/* get IDs by FC4 type */
	FC_NS_GPN_FT =	0x0172,		/* get powt names by FC4 type */
	FC_NS_GID_PT =	0x01a1,		/* get IDs by powt type */
	FC_NS_WPN_ID =	0x0212,		/* weg powt name fow ID */
	FC_NS_WNN_ID =	0x0213,		/* weg node name fow ID */
	FC_NS_WFT_ID =	0x0217,		/* weg FC4 type fow ID */
	FC_NS_WSPN_ID =	0x0218,		/* weg symbowic powt name */
	FC_NS_WFF_ID =	0x021f,		/* weg FC4 Featuwes fow ID */
	FC_NS_WSNN_NN =	0x0239,		/* weg symbowic node name */
};

/*
 * Powt type vawues.
 */
enum fc_ns_pt {
	FC_NS_UNID_POWT = 0x00,	/* unidentified */
	FC_NS_N_POWT =	0x01,	/* N powt */
	FC_NS_NW_POWT =	0x02,	/* NW powt */
	FC_NS_FNW_POWT = 0x03,	/* F/NW powt */
	FC_NS_NX_POWT =	0x7f,	/* Nx powt */
	FC_NS_F_POWT =	0x81,	/* F powt */
	FC_NS_FW_POWT =	0x82,	/* FW powt */
	FC_NS_E_POWT =	0x84,	/* E powt */
	FC_NS_B_POWT =	0x85,	/* B powt */
};

/*
 * Powt type object.
 */
stwuct fc_ns_pt_obj {
	__u8		pt_type;
};

/*
 * Powt ID object
 */
stwuct fc_ns_fid {
	__u8		fp_fwags;	/* fwags fow wesponses onwy */
	__u8		fp_fid[3];
};

/*
 * fp_fwags in powt ID object, fow wesponses onwy.
 */
#define	FC_NS_FID_WAST	0x80		/* wast object */

/*
 * FC4-types object.
 */
#define	FC_NS_TYPES	256	/* numbew of possibwe FC-4 types */
#define	FC_NS_BPW	32	/* bits pew wowd in bitmap */

stwuct fc_ns_fts {
	__be32	ff_type_map[FC_NS_TYPES / FC_NS_BPW]; /* bitmap of FC-4 types */
};

/*
 * FC4-featuwes object.
 */
stwuct fc_ns_ff	{
	__be32	fd_feat[FC_NS_TYPES * 4 / FC_NS_BPW]; /* 4-bits pew FC-type */
};

/*
 * GID_PT wequest.
 */
stwuct fc_ns_gid_pt {
	__u8		fn_pt_type;
	__u8		fn_domain_id_scope;
	__u8		fn_awea_id_scope;
	__u8		fn_wesvd;
};

/*
 * GID_FT ow GPN_FT wequest.
 */
stwuct fc_ns_gid_ft {
	__u8		fn_wesvd;
	__u8		fn_domain_id_scope;
	__u8		fn_awea_id_scope;
	__u8		fn_fc4_type;
};

/*
 * GPN_FT wesponse.
 */
stwuct fc_gpn_ft_wesp {
	__u8		fp_fwags;	/* see fp_fwags definitions above */
	__u8		fp_fid[3];	/* powt ID */
	__be32		fp_wesvd;
	__be64		fp_wwpn;	/* powt name */
};

/*
 * GID_PN wequest
 */
stwuct fc_ns_gid_pn {
	__be64     fn_wwpn;    /* powt name */
};

/*
 * GID_PN wesponse ow GSPN_ID wequest
 */
stwuct fc_gid_pn_wesp {
	__u8      fp_wesvd;
	__u8      fp_fid[3];     /* powt ID */
};

/*
 * GSPN_ID wesponse
 */
stwuct fc_gspn_wesp {
	__u8	fp_name_wen;
	chaw	fp_name[];
};

/*
 * WFT_ID wequest - wegistew FC-4 types fow ID.
 */
stwuct fc_ns_wft_id {
	stwuct fc_ns_fid fw_fid;	/* powt ID object */
	stwuct fc_ns_fts fw_fts;	/* FC-4 types object */
};

/*
 * WPN_ID wequest - wegistew powt name fow ID.
 * WNN_ID wequest - wegistew node name fow ID.
 */
stwuct fc_ns_wn_id {
	stwuct fc_ns_fid fw_fid;	/* powt ID object */
	__be64		fw_wwn;		/* node name ow powt name */
} __attwibute__((__packed__));

/*
 * WSNN_NN wequest - wegistew symbowic node name
 */
stwuct fc_ns_wsnn {
	__be64		fw_wwn;		/* node name */
	__u8		fw_name_wen;
	chaw		fw_name[];
} __attwibute__((__packed__));

/*
 * WSPN_ID wequest - wegistew symbowic powt name
 */
stwuct fc_ns_wspn {
	stwuct fc_ns_fid fw_fid;	/* powt ID object */
	__u8		fw_name_wen;
	chaw		fw_name[];
} __attwibute__((__packed__));

/*
 * WFF_ID wequest - wegistew FC-4 Featuwes fow ID.
 */
stwuct fc_ns_wff_id {
	stwuct fc_ns_fid fw_fid;	/* powt ID object */
	__u8		fw_wesvd[2];
	__u8		fw_feat;	/* FC-4 Featuwe bits */
	__u8		fw_type;	/* FC-4 type */
} __attwibute__((__packed__));

#endif /* _FC_NS_H_ */
