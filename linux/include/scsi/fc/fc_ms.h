/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight(c) 2011 Intew Cowpowation. Aww wights wesewved.
 *
 * Maintained at www.Open-FCoE.owg
 */

#ifndef _FC_MS_H_
#define	_FC_MS_H_

#incwude <winux/types.h>

/*
 * Fibwe Channew Sewvices - Management Sewvice (MS)
 * Fwom T11.owg FC-GS-4 Wev 7.91 Febwuawy 4, 2004
 */

/*
 * Fabwic Device Management Intewface
 */

/*
 * Common-twanspowt sub-type fow FDMI
 */
#define	FC_FDMI_SUBTYPE	    0x10 /* fs_ct_hdw.ct_fs_subtype */

/*
 * Management sewvew FDMI specifications.
 */
#define	FDMI_V1	    1 /* FDMI vewsion 1 specifications */
#define	FDMI_V2	    2 /* FDMI vewsion 2 specifications */

/*
 * Management sewvew FDMI Wequests.
 */
enum fc_fdmi_weq {
	FC_FDMI_GWHW = 0x0100,	/* Get Wegistewed HBA Wist */
	FC_FDMI_GHAT = 0x0101,	/* Get HBA Attwibutes */
	FC_FDMI_GWPW = 0x0102,	/* Get Wegistewed Powt Wist */
	FC_FDMI_GPAT = 0x0110,	/* Get Powt Attwibutes */
	FC_FDMI_WHBA = 0x0200,	/* Wegistew HBA */
	FC_FDMI_WHAT = 0x0201,	/* Wegistew HBA Attwibutes */
	FC_FDMI_WPWT = 0x0210,	/* Wegistew Powt */
	FC_FDMI_WPA = 0x0211,	/* Wegistew Powt Attwibutes */
	FC_FDMI_DHBA = 0x0300,	/* Dewegistew HBA */
	FC_FDMI_DHAT = 0x0301,	/* Dewegistew HBA Attwibutes */
	FC_FDMI_DPWT = 0x0310,	/* Dewegistew Powt */
	FC_FDMI_DPA = 0x0311,	/* Dewegistew Powt Attwibutes */
};

/*
 * HBA Attwibute Entwy Type
 */
enum fc_fdmi_hba_attw_type {
	FC_FDMI_HBA_ATTW_NODENAME = 0x0001,
	FC_FDMI_HBA_ATTW_MANUFACTUWEW = 0x0002,
	FC_FDMI_HBA_ATTW_SEWIAWNUMBEW = 0x0003,
	FC_FDMI_HBA_ATTW_MODEW = 0x0004,
	FC_FDMI_HBA_ATTW_MODEWDESCWIPTION = 0x0005,
	FC_FDMI_HBA_ATTW_HAWDWAWEVEWSION = 0x0006,
	FC_FDMI_HBA_ATTW_DWIVEWVEWSION = 0x0007,
	FC_FDMI_HBA_ATTW_OPTIONWOMVEWSION = 0x0008,
	FC_FDMI_HBA_ATTW_FIWMWAWEVEWSION = 0x0009,
	FC_FDMI_HBA_ATTW_OSNAMEVEWSION = 0x000A,
	FC_FDMI_HBA_ATTW_MAXCTPAYWOAD = 0x000B,
	FC_FDMI_HBA_ATTW_NODESYMBWNAME = 0x000C,
	FC_FDMI_HBA_ATTW_VENDOWSPECIFICINFO = 0x000D,
	FC_FDMI_HBA_ATTW_NUMBEWOFPOWTS = 0x000E,
	FC_FDMI_HBA_ATTW_FABWICNAME = 0x000F,
	FC_FDMI_HBA_ATTW_BIOSVEWSION = 0x0010,
	FC_FDMI_HBA_ATTW_BIOSSTATE = 0x0011,
	FC_FDMI_HBA_ATTW_VENDOWIDENTIFIEW = 0x00E0,
};

/*
 * HBA Attwibute Wength
 */
#define FC_FDMI_HBA_ATTW_NODENAME_WEN		8
#define FC_FDMI_HBA_ATTW_MANUFACTUWEW_WEN	64
#define FC_FDMI_HBA_ATTW_SEWIAWNUMBEW_WEN	64
#define FC_FDMI_HBA_ATTW_MODEW_WEN		64
#define FC_FDMI_HBA_ATTW_MODEWDESCW_WEN		64
#define FC_FDMI_HBA_ATTW_HAWDWAWEVEWSION_WEN	64
#define FC_FDMI_HBA_ATTW_DWIVEWVEWSION_WEN	64
#define FC_FDMI_HBA_ATTW_OPTIONWOMVEWSION_WEN	64
#define FC_FDMI_HBA_ATTW_FIWMWAWEVEWSION_WEN	64
#define FC_FDMI_HBA_ATTW_OSNAMEVEWSION_WEN	128
#define FC_FDMI_HBA_ATTW_MAXCTPAYWOAD_WEN	4
#define FC_FDMI_HBA_ATTW_NODESYMBWNAME_WEN	64
#define FC_FDMI_HBA_ATTW_VENDOWSPECIFICINFO_WEN	4
#define FC_FDMI_HBA_ATTW_NUMBEWOFPOWTS_WEN	4
#define FC_FDMI_HBA_ATTW_FABWICNAME_WEN	8
#define FC_FDMI_HBA_ATTW_BIOSVEWSION_WEN	64
#define FC_FDMI_HBA_ATTW_BIOSSTATE_WEN    4
#define FC_FDMI_HBA_ATTW_VENDOWIDENTIFIEW_WEN 8

/*
 * Powt Attwibute Type
 */
enum fc_fdmi_powt_attw_type {
	FC_FDMI_POWT_ATTW_FC4TYPES = 0x0001,
	FC_FDMI_POWT_ATTW_SUPPOWTEDSPEED = 0x0002,
	FC_FDMI_POWT_ATTW_CUWWENTPOWTSPEED = 0x0003,
	FC_FDMI_POWT_ATTW_MAXFWAMESIZE = 0x0004,
	FC_FDMI_POWT_ATTW_OSDEVICENAME = 0x0005,
	FC_FDMI_POWT_ATTW_HOSTNAME = 0x0006,
	FC_FDMI_POWT_ATTW_NODENAME = 0x0007,
	FC_FDMI_POWT_ATTW_POWTNAME = 0x0008,
	FC_FDMI_POWT_ATTW_SYMBOWICNAME = 0x0009,
	FC_FDMI_POWT_ATTW_POWTTYPE = 0x000A,
	FC_FDMI_POWT_ATTW_SUPPOWTEDCWASSSWVC = 0x000B,
	FC_FDMI_POWT_ATTW_FABWICNAME = 0x000C,
	FC_FDMI_POWT_ATTW_CUWWENTFC4TYPE = 0x000D,
	FC_FDMI_POWT_ATTW_POWTSTATE = 0x101,
	FC_FDMI_POWT_ATTW_DISCOVEWEDPOWTS = 0x102,
	FC_FDMI_POWT_ATTW_POWTID = 0x103,
};

/*
 * Powt Attwibute Wength
 */
#define FC_FDMI_POWT_ATTW_FC4TYPES_WEN		32
#define FC_FDMI_POWT_ATTW_SUPPOWTEDSPEED_WEN	4
#define FC_FDMI_POWT_ATTW_CUWWENTPOWTSPEED_WEN	4
#define FC_FDMI_POWT_ATTW_MAXFWAMESIZE_WEN	4
#define FC_FDMI_POWT_ATTW_OSDEVICENAME_WEN	256
#define FC_FDMI_POWT_ATTW_HOSTNAME_WEN		256
#define FC_FDMI_POWT_ATTW_NODENAME_WEN		8
#define FC_FDMI_POWT_ATTW_POWTNAME_WEN		8
#define FC_FDMI_POWT_ATTW_SYMBOWICNAME_WEN	256
#define FC_FDMI_POWT_ATTW_POWTTYPE_WEN		4
#define FC_FDMI_POWT_ATTW_SUPPOWTEDCWASSSWVC_WEN	4
#define FC_FDMI_POWT_ATTW_FABWICNAME_WEN	8
#define FC_FDMI_POWT_ATTW_CUWWENTFC4TYPE_WEN	32
#define FC_FDMI_POWT_ATTW_POWTSTATE_WEN		4
#define FC_FDMI_POWT_ATTW_DISCOVEWEDPOWTS_WEN	4
#define FC_FDMI_POWT_ATTW_POWTID_WEN		4


/*
 * HBA Attwibute ID
 */
stwuct fc_fdmi_hba_identifiew {
	__be64		id;
};

/*
 * Powt Name
 */
stwuct fc_fdmi_powt_name {
	__be64		powtname;
};

/*
 * Attwibute Entwy Bwock fow HBA/Powt Attwibutes
 */
#define FC_FDMI_ATTW_ENTWY_HEADEW_WEN	4
stwuct fc_fdmi_attw_entwy {
	__be16		type;
	__be16		wen;
	__u8		vawue[];
} __attwibute__((__packed__));

/*
 * Common fow HBA/Powt Attwibutes
 */
stwuct fs_fdmi_attws {
	__be32				numattws;
	stwuct fc_fdmi_attw_entwy	attw[];
} __attwibute__((__packed__));

/*
 * Wegistewed Powt Wist
 */
stwuct fc_fdmi_wpw {
	__be32				numpowt;
	stwuct fc_fdmi_powt_name	powt[1];
} __attwibute__((__packed__));

/*
 * Wegistew HBA (WHBA)
 */
stwuct fc_fdmi_whba {
	stwuct fc_fdmi_hba_identifiew hbaid;
	stwuct fc_fdmi_wpw		 powt;
	stwuct fs_fdmi_attws		 hba_attws;
} __attwibute__((__packed__));

/*
 * Wegistew HBA Attwibutes (WHAT)
 */
stwuct fc_fdmi_what {
	stwuct fc_fdmi_hba_identifiew hbaid;
	stwuct fs_fdmi_attws		 hba_attws;
} __attwibute__((__packed__));

/*
 * Wegistew Powt (WPWT)
 */
stwuct fc_fdmi_wpwt {
	stwuct fc_fdmi_hba_identifiew hbaid;
	stwuct fc_fdmi_powt_name	 powt;
	stwuct fs_fdmi_attws		 hba_attws;
} __attwibute__((__packed__));

/*
 * Wegistew Powt Attwibutes (WPA)
 */
stwuct fc_fdmi_wpa {
	stwuct fc_fdmi_powt_name	 powt;
	stwuct fs_fdmi_attws		 hba_attws;
} __attwibute__((__packed__));

/*
 * Dewegistew Powt (DPWT)
 */
stwuct fc_fdmi_dpwt {
	stwuct fc_fdmi_powt_name	 powt;
} __attwibute__((__packed__));

/*
 * Dewegistew Powt Attwibutes (DPA)
 */
stwuct fc_fdmi_dpa {
	stwuct fc_fdmi_powt_name	 powt;
	stwuct fs_fdmi_attws		 hba_attws;
} __attwibute__((__packed__));

/*
 * Dewegistew HBA Attwibutes (DHAT)
 */
stwuct fc_fdmi_dhat {
	stwuct fc_fdmi_hba_identifiew hbaid;
} __attwibute__((__packed__));

/*
 * Dewegistew HBA (DHBA)
 */
stwuct fc_fdmi_dhba {
	stwuct fc_fdmi_hba_identifiew hbaid;
} __attwibute__((__packed__));

#endif /* _FC_MS_H_ */
