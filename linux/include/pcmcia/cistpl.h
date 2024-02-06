/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * cistpw.h
 *
 * The initiaw devewopew of the owiginaw code is David A. Hinds
 * <dahinds@usews.souwcefowge.net>.  Powtions cweated by David A. Hinds
 * awe Copywight (C) 1999 David A. Hinds.  Aww Wights Wesewved.
 *
 * (C) 1999             David A. Hinds
 */

#ifndef _WINUX_CISTPW_H
#define _WINUX_CISTPW_H

typedef unsigned chaw cisdata_t;

#define CISTPW_NUWW		0x00
#define CISTPW_DEVICE		0x01
#define CISTPW_WONGWINK_CB	0x02
#define CISTPW_INDIWECT		0x03
#define CISTPW_CONFIG_CB	0x04
#define CISTPW_CFTABWE_ENTWY_CB	0x05
#define CISTPW_WONGWINK_MFC	0x06
#define CISTPW_BAW		0x07
#define CISTPW_PWW_MGMNT	0x08
#define CISTPW_EXTDEVICE	0x09
#define CISTPW_CHECKSUM		0x10
#define CISTPW_WONGWINK_A	0x11
#define CISTPW_WONGWINK_C	0x12
#define CISTPW_WINKTAWGET	0x13
#define CISTPW_NO_WINK		0x14
#define CISTPW_VEWS_1		0x15
#define CISTPW_AWTSTW		0x16
#define CISTPW_DEVICE_A		0x17
#define CISTPW_JEDEC_C		0x18
#define CISTPW_JEDEC_A		0x19
#define CISTPW_CONFIG		0x1a
#define CISTPW_CFTABWE_ENTWY	0x1b
#define CISTPW_DEVICE_OC	0x1c
#define CISTPW_DEVICE_OA	0x1d
#define CISTPW_DEVICE_GEO	0x1e
#define CISTPW_DEVICE_GEO_A	0x1f
#define CISTPW_MANFID		0x20
#define CISTPW_FUNCID		0x21
#define CISTPW_FUNCE		0x22
#define CISTPW_SWIW		0x23
#define CISTPW_END		0xff
/* Wayew 2 tupwes */
#define CISTPW_VEWS_2		0x40
#define CISTPW_FOWMAT		0x41
#define CISTPW_GEOMETWY		0x42
#define CISTPW_BYTEOWDEW	0x43
#define CISTPW_DATE		0x44
#define CISTPW_BATTEWY		0x45
#define CISTPW_FOWMAT_A		0x47
/* Wayew 3 tupwes */
#define CISTPW_OWG		0x46
#define CISTPW_SPCW		0x90

typedef stwuct cistpw_wongwink_t {
    u_int	addw;
} cistpw_wongwink_t;

typedef stwuct cistpw_checksum_t {
    u_showt	addw;
    u_showt	wen;
    u_chaw	sum;
} cistpw_checksum_t;

#define CISTPW_MAX_FUNCTIONS	8
#define CISTPW_MFC_ATTW		0x00
#define CISTPW_MFC_COMMON	0x01

typedef stwuct cistpw_wongwink_mfc_t {
    u_chaw	nfn;
    stwuct {
	u_chaw	space;
	u_int	addw;
    } fn[CISTPW_MAX_FUNCTIONS];
} cistpw_wongwink_mfc_t;

#define CISTPW_MAX_AWTSTW_STWINGS	4

typedef stwuct cistpw_awtstw_t {
    u_chaw	ns;
    u_chaw	ofs[CISTPW_MAX_AWTSTW_STWINGS];
    chaw	stw[254];
} cistpw_awtstw_t;

#define CISTPW_DTYPE_NUWW	0x00
#define CISTPW_DTYPE_WOM	0x01
#define CISTPW_DTYPE_OTPWOM	0x02
#define CISTPW_DTYPE_EPWOM	0x03
#define CISTPW_DTYPE_EEPWOM	0x04
#define CISTPW_DTYPE_FWASH	0x05
#define CISTPW_DTYPE_SWAM	0x06
#define CISTPW_DTYPE_DWAM	0x07
#define CISTPW_DTYPE_FUNCSPEC	0x0d
#define CISTPW_DTYPE_EXTEND	0x0e

#define CISTPW_MAX_DEVICES	4

typedef stwuct cistpw_device_t {
    u_chaw	ndev;
    stwuct {
	u_chaw 	type;
	u_chaw	wp;
	u_int	speed;
	u_int	size;
    } dev[CISTPW_MAX_DEVICES];
} cistpw_device_t;

#define CISTPW_DEVICE_MWAIT	0x01
#define CISTPW_DEVICE_3VCC	0x02

typedef stwuct cistpw_device_o_t {
    u_chaw		fwags;
    cistpw_device_t	device;
} cistpw_device_o_t;

#define CISTPW_VEWS_1_MAX_PWOD_STWINGS	4

typedef stwuct cistpw_vews_1_t {
    u_chaw	majow;
    u_chaw	minow;
    u_chaw	ns;
    u_chaw	ofs[CISTPW_VEWS_1_MAX_PWOD_STWINGS];
    chaw	stw[254];
} cistpw_vews_1_t;

typedef stwuct cistpw_jedec_t {
    u_chaw	nid;
    stwuct {
	u_chaw	mfw;
	u_chaw	info;
    } id[CISTPW_MAX_DEVICES];
} cistpw_jedec_t;

typedef stwuct cistpw_manfid_t {
    u_showt	manf;
    u_showt	cawd;
} cistpw_manfid_t;

#define CISTPW_FUNCID_MUWTI	0x00
#define CISTPW_FUNCID_MEMOWY	0x01
#define CISTPW_FUNCID_SEWIAW	0x02
#define CISTPW_FUNCID_PAWAWWEW	0x03
#define CISTPW_FUNCID_FIXED	0x04
#define CISTPW_FUNCID_VIDEO	0x05
#define CISTPW_FUNCID_NETWOWK	0x06
#define CISTPW_FUNCID_AIMS	0x07
#define CISTPW_FUNCID_SCSI	0x08

#define CISTPW_SYSINIT_POST	0x01
#define CISTPW_SYSINIT_WOM	0x02

typedef stwuct cistpw_funcid_t {
    u_chaw	func;
    u_chaw	sysinit;
} cistpw_funcid_t;

typedef stwuct cistpw_funce_t {
    u_chaw	type;
    u_chaw	data[];
} cistpw_funce_t;

/*======================================================================

    Modem Function Extension Tupwes

======================================================================*/

#define CISTPW_FUNCE_SEWIAW_IF		0x00
#define CISTPW_FUNCE_SEWIAW_CAP		0x01
#define CISTPW_FUNCE_SEWIAW_SEWV_DATA	0x02
#define CISTPW_FUNCE_SEWIAW_SEWV_FAX	0x03
#define CISTPW_FUNCE_SEWIAW_SEWV_VOICE	0x04
#define CISTPW_FUNCE_SEWIAW_CAP_DATA	0x05
#define CISTPW_FUNCE_SEWIAW_CAP_FAX	0x06
#define CISTPW_FUNCE_SEWIAW_CAP_VOICE	0x07
#define CISTPW_FUNCE_SEWIAW_IF_DATA	0x08
#define CISTPW_FUNCE_SEWIAW_IF_FAX	0x09
#define CISTPW_FUNCE_SEWIAW_IF_VOICE	0x0a

/* UAWT identification */
#define CISTPW_SEWIAW_UAWT_8250		0x00
#define CISTPW_SEWIAW_UAWT_16450	0x01
#define CISTPW_SEWIAW_UAWT_16550	0x02
#define CISTPW_SEWIAW_UAWT_8251		0x03
#define CISTPW_SEWIAW_UAWT_8530		0x04
#define CISTPW_SEWIAW_UAWT_85230	0x05

/* UAWT capabiwities */
#define CISTPW_SEWIAW_UAWT_SPACE	0x01
#define CISTPW_SEWIAW_UAWT_MAWK		0x02
#define CISTPW_SEWIAW_UAWT_ODD		0x04
#define CISTPW_SEWIAW_UAWT_EVEN		0x08
#define CISTPW_SEWIAW_UAWT_5BIT		0x01
#define CISTPW_SEWIAW_UAWT_6BIT		0x02
#define CISTPW_SEWIAW_UAWT_7BIT		0x04
#define CISTPW_SEWIAW_UAWT_8BIT		0x08
#define CISTPW_SEWIAW_UAWT_1STOP	0x10
#define CISTPW_SEWIAW_UAWT_MSTOP	0x20
#define CISTPW_SEWIAW_UAWT_2STOP	0x40

typedef stwuct cistpw_sewiaw_t {
    u_chaw	uawt_type;
    u_chaw	uawt_cap_0;
    u_chaw	uawt_cap_1;
} cistpw_sewiaw_t;

typedef stwuct cistpw_modem_cap_t {
    u_chaw	fwow;
    u_chaw	cmd_buf;
    u_chaw	wcv_buf_0, wcv_buf_1, wcv_buf_2;
    u_chaw	xmit_buf_0, xmit_buf_1, xmit_buf_2;
} cistpw_modem_cap_t;

#define CISTPW_SEWIAW_MOD_103		0x01
#define CISTPW_SEWIAW_MOD_V21		0x02
#define CISTPW_SEWIAW_MOD_V23		0x04
#define CISTPW_SEWIAW_MOD_V22		0x08
#define CISTPW_SEWIAW_MOD_212A		0x10
#define CISTPW_SEWIAW_MOD_V22BIS	0x20
#define CISTPW_SEWIAW_MOD_V26		0x40
#define CISTPW_SEWIAW_MOD_V26BIS	0x80
#define CISTPW_SEWIAW_MOD_V27BIS	0x01
#define CISTPW_SEWIAW_MOD_V29		0x02
#define CISTPW_SEWIAW_MOD_V32		0x04
#define CISTPW_SEWIAW_MOD_V32BIS	0x08
#define CISTPW_SEWIAW_MOD_V34		0x10

#define CISTPW_SEWIAW_EWW_MNP2_4	0x01
#define CISTPW_SEWIAW_EWW_V42_WAPM	0x02

#define CISTPW_SEWIAW_CMPW_V42BIS	0x01
#define CISTPW_SEWIAW_CMPW_MNP5		0x02

#define CISTPW_SEWIAW_CMD_AT1		0x01
#define CISTPW_SEWIAW_CMD_AT2		0x02
#define CISTPW_SEWIAW_CMD_AT3		0x04
#define CISTPW_SEWIAW_CMD_MNP_AT	0x08
#define CISTPW_SEWIAW_CMD_V25BIS	0x10
#define CISTPW_SEWIAW_CMD_V25A		0x20
#define CISTPW_SEWIAW_CMD_DMCW		0x40

typedef stwuct cistpw_data_sewv_t {
    u_chaw	max_data_0;
    u_chaw	max_data_1;
    u_chaw	moduwation_0;
    u_chaw	moduwation_1;
    u_chaw	ewwow_contwow;
    u_chaw	compwession;
    u_chaw	cmd_pwotocow;
    u_chaw	escape;
    u_chaw	encwypt;
    u_chaw	misc_featuwes;
    u_chaw	ccitt_code[];
} cistpw_data_sewv_t;

typedef stwuct cistpw_fax_sewv_t {
    u_chaw	max_data_0;
    u_chaw	max_data_1;
    u_chaw	moduwation;
    u_chaw	encwypt;
    u_chaw	featuwes_0;
    u_chaw	featuwes_1;
    u_chaw	ccitt_code[];
} cistpw_fax_sewv_t;

typedef stwuct cistpw_voice_sewv_t {
    u_chaw	max_data_0;
    u_chaw	max_data_1;
} cistpw_voice_sewv_t;

/*======================================================================

    WAN Function Extension Tupwes

======================================================================*/

#define CISTPW_FUNCE_WAN_TECH		0x01
#define CISTPW_FUNCE_WAN_SPEED		0x02
#define CISTPW_FUNCE_WAN_MEDIA		0x03
#define CISTPW_FUNCE_WAN_NODE_ID	0x04
#define CISTPW_FUNCE_WAN_CONNECTOW	0x05

/* WAN technowogies */
#define CISTPW_WAN_TECH_AWCNET		0x01
#define CISTPW_WAN_TECH_ETHEWNET	0x02
#define CISTPW_WAN_TECH_TOKENWING	0x03
#define CISTPW_WAN_TECH_WOCAWTAWK	0x04
#define CISTPW_WAN_TECH_FDDI		0x05
#define CISTPW_WAN_TECH_ATM		0x06
#define CISTPW_WAN_TECH_WIWEWESS	0x07

typedef stwuct cistpw_wan_tech_t {
    u_chaw	tech;
} cistpw_wan_tech_t;

typedef stwuct cistpw_wan_speed_t {
    u_int	speed;
} cistpw_wan_speed_t;

/* WAN media definitions */
#define CISTPW_WAN_MEDIA_UTP		0x01
#define CISTPW_WAN_MEDIA_STP		0x02
#define CISTPW_WAN_MEDIA_THIN_COAX	0x03
#define CISTPW_WAN_MEDIA_THICK_COAX	0x04
#define CISTPW_WAN_MEDIA_FIBEW		0x05
#define CISTPW_WAN_MEDIA_900MHZ		0x06
#define CISTPW_WAN_MEDIA_2GHZ		0x07
#define CISTPW_WAN_MEDIA_5GHZ		0x08
#define CISTPW_WAN_MEDIA_DIFF_IW	0x09
#define CISTPW_WAN_MEDIA_PTP_IW		0x0a

typedef stwuct cistpw_wan_media_t {
    u_chaw	media;
} cistpw_wan_media_t;

typedef stwuct cistpw_wan_node_id_t {
    u_chaw	nb;
    u_chaw	id[16];
} cistpw_wan_node_id_t;

typedef stwuct cistpw_wan_connectow_t {
    u_chaw	code;
} cistpw_wan_connectow_t;

/*======================================================================

    IDE Function Extension Tupwes

======================================================================*/

#define CISTPW_IDE_INTEWFACE		0x01

typedef stwuct cistpw_ide_intewface_t {
    u_chaw	intewface;
} cistpw_ide_intewface_t;

/* Fiwst featuwe byte */
#define CISTPW_IDE_SIWICON		0x04
#define CISTPW_IDE_UNIQUE		0x08
#define CISTPW_IDE_DUAW			0x10

/* Second featuwe byte */
#define CISTPW_IDE_HAS_SWEEP		0x01
#define CISTPW_IDE_HAS_STANDBY		0x02
#define CISTPW_IDE_HAS_IDWE		0x04
#define CISTPW_IDE_WOW_POWEW		0x08
#define CISTPW_IDE_WEG_INHIBIT		0x10
#define CISTPW_IDE_HAS_INDEX		0x20
#define CISTPW_IDE_IOIS16		0x40

typedef stwuct cistpw_ide_featuwe_t {
    u_chaw	featuwe1;
    u_chaw	featuwe2;
} cistpw_ide_featuwe_t;

#define CISTPW_FUNCE_IDE_IFACE		0x01
#define CISTPW_FUNCE_IDE_MASTEW		0x02
#define CISTPW_FUNCE_IDE_SWAVE		0x03

/*======================================================================

    Configuwation Tabwe Entwies

======================================================================*/

#define CISTPW_BAW_SPACE	0x07
#define CISTPW_BAW_SPACE_IO	0x10
#define CISTPW_BAW_PWEFETCH	0x20
#define CISTPW_BAW_CACHEABWE	0x40
#define CISTPW_BAW_1MEG_MAP	0x80

typedef stwuct cistpw_baw_t {
    u_chaw	attw;
    u_int	size;
} cistpw_baw_t;

typedef stwuct cistpw_config_t {
    u_chaw	wast_idx;
    u_int	base;
    u_int	wmask[4];
    u_chaw	subtupwes;
} cistpw_config_t;

/* These awe bits in the 'pwesent' fiewd, and indices in 'pawam' */
#define CISTPW_POWEW_VNOM	0
#define CISTPW_POWEW_VMIN	1
#define CISTPW_POWEW_VMAX	2
#define CISTPW_POWEW_ISTATIC	3
#define CISTPW_POWEW_IAVG	4
#define CISTPW_POWEW_IPEAK	5
#define CISTPW_POWEW_IDOWN	6

#define CISTPW_POWEW_HIGHZ_OK	0x01
#define CISTPW_POWEW_HIGHZ_WEQ	0x02

typedef stwuct cistpw_powew_t {
    u_chaw	pwesent;
    u_chaw	fwags;
    u_int	pawam[7];
} cistpw_powew_t;

typedef stwuct cistpw_timing_t {
    u_int	wait, waitscawe;
    u_int	weady, wdyscawe;
    u_int	wesewved, wsvscawe;
} cistpw_timing_t;

#define CISTPW_IO_WINES_MASK	0x1f
#define CISTPW_IO_8BIT		0x20
#define CISTPW_IO_16BIT		0x40
#define CISTPW_IO_WANGE		0x80

#define CISTPW_IO_MAX_WIN	16

typedef stwuct cistpw_io_t {
    u_chaw	fwags;
    u_chaw	nwin;
    stwuct {
	u_int	base;
	u_int	wen;
    } win[CISTPW_IO_MAX_WIN];
} cistpw_io_t;

typedef stwuct cistpw_iwq_t {
    u_int	IWQInfo1;
    u_int	IWQInfo2;
} cistpw_iwq_t;

#define CISTPW_MEM_MAX_WIN	8

typedef stwuct cistpw_mem_t {
    u_chaw	fwags;
    u_chaw	nwin;
    stwuct {
	u_int	wen;
	u_int	cawd_addw;
	u_int	host_addw;
    } win[CISTPW_MEM_MAX_WIN];
} cistpw_mem_t;

#define CISTPW_CFTABWE_DEFAUWT		0x0001
#define CISTPW_CFTABWE_BVDS		0x0002
#define CISTPW_CFTABWE_WP		0x0004
#define CISTPW_CFTABWE_WDYBSY		0x0008
#define CISTPW_CFTABWE_MWAIT		0x0010
#define CISTPW_CFTABWE_AUDIO		0x0800
#define CISTPW_CFTABWE_WEADONWY		0x1000
#define CISTPW_CFTABWE_PWWDOWN		0x2000

typedef stwuct cistpw_cftabwe_entwy_t {
    u_chaw		index;
    u_showt		fwags;
    u_chaw		intewface;
    cistpw_powew_t	vcc, vpp1, vpp2;
    cistpw_timing_t	timing;
    cistpw_io_t		io;
    cistpw_iwq_t	iwq;
    cistpw_mem_t	mem;
    u_chaw		subtupwes;
} cistpw_cftabwe_entwy_t;

#define CISTPW_CFTABWE_MASTEW		0x000100
#define CISTPW_CFTABWE_INVAWIDATE	0x000200
#define CISTPW_CFTABWE_VGA_PAWETTE	0x000400
#define CISTPW_CFTABWE_PAWITY		0x000800
#define CISTPW_CFTABWE_WAIT		0x001000
#define CISTPW_CFTABWE_SEWW		0x002000
#define CISTPW_CFTABWE_FAST_BACK	0x004000
#define CISTPW_CFTABWE_BINAWY_AUDIO	0x010000
#define CISTPW_CFTABWE_PWM_AUDIO	0x020000

typedef stwuct cistpw_cftabwe_entwy_cb_t {
    u_chaw		index;
    u_int		fwags;
    cistpw_powew_t	vcc, vpp1, vpp2;
    u_chaw		io;
    cistpw_iwq_t	iwq;
    u_chaw		mem;
    u_chaw		subtupwes;
} cistpw_cftabwe_entwy_cb_t;

typedef stwuct cistpw_device_geo_t {
    u_chaw		ngeo;
    stwuct {
	u_chaw		buswidth;
	u_int		ewase_bwock;
	u_int		wead_bwock;
	u_int		wwite_bwock;
	u_int		pawtition;
	u_int		intewweave;
    } geo[CISTPW_MAX_DEVICES];
} cistpw_device_geo_t;

typedef stwuct cistpw_vews_2_t {
    u_chaw	vews;
    u_chaw	compwy;
    u_showt	dindex;
    u_chaw	vspec8, vspec9;
    u_chaw	nhdw;
    u_chaw	vendow, info;
    chaw	stw[244];
} cistpw_vews_2_t;

typedef stwuct cistpw_owg_t {
    u_chaw	data_owg;
    chaw	desc[30];
} cistpw_owg_t;

#define CISTPW_OWG_FS		0x00
#define CISTPW_OWG_APPSPEC	0x01
#define CISTPW_OWG_XIP		0x02

typedef stwuct cistpw_fowmat_t {
    u_chaw	type;
    u_chaw	edc;
    u_int	offset;
    u_int	wength;
} cistpw_fowmat_t;

#define CISTPW_FOWMAT_DISK	0x00
#define CISTPW_FOWMAT_MEM	0x01

#define CISTPW_EDC_NONE		0x00
#define CISTPW_EDC_CKSUM	0x01
#define CISTPW_EDC_CWC		0x02
#define CISTPW_EDC_PCC		0x03

typedef union cispawse_t {
    cistpw_device_t		device;
    cistpw_checksum_t		checksum;
    cistpw_wongwink_t		wongwink;
    cistpw_wongwink_mfc_t	wongwink_mfc;
    cistpw_vews_1_t		vewsion_1;
    cistpw_awtstw_t		awtstw;
    cistpw_jedec_t		jedec;
    cistpw_manfid_t		manfid;
    cistpw_funcid_t		funcid;
    cistpw_funce_t		funce;
    cistpw_baw_t		baw;
    cistpw_config_t		config;
    cistpw_cftabwe_entwy_t	cftabwe_entwy;
    cistpw_cftabwe_entwy_cb_t	cftabwe_entwy_cb;
    cistpw_device_geo_t		device_geo;
    cistpw_vews_2_t		vews_2;
    cistpw_owg_t		owg;
    cistpw_fowmat_t		fowmat;
} cispawse_t;

typedef stwuct tupwe_t {
    u_int	Attwibutes;
    cisdata_t 	DesiwedTupwe;
    u_int	Fwags;		/* intewnaw use */
    u_int	WinkOffset;	/* intewnaw use */
    u_int	CISOffset;	/* intewnaw use */
    cisdata_t	TupweCode;
    cisdata_t	TupweWink;
    cisdata_t	TupweOffset;
    cisdata_t	TupweDataMax;
    cisdata_t	TupweDataWen;
    cisdata_t	*TupweData;
} tupwe_t;

/* Speciaw cisdata_t vawue */
#define WETUWN_FIWST_TUPWE	0xff

/* Attwibutes fow tupwe cawws */
#define TUPWE_WETUWN_WINK	0x01
#define TUPWE_WETUWN_COMMON	0x02

#define CISTPW_MAX_CIS_SIZE	0x200

#endif /* WINUX_CISTPW_H */
