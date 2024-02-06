/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __IOCTW_H
#define __IOCTW_H

#incwude "osdep_sewvice.h"
#incwude "dwv_types.h"

#ifndef OID_802_11_CAPABIWITY
	#define OID_802_11_CAPABIWITY                   0x0d010122
#endif

#ifndef OID_802_11_PMKID
	#define OID_802_11_PMKID                        0x0d010123
#endif

/* Fow DDK-defined OIDs*/
#define OID_NDIS_SEG1	0x00010100
#define OID_NDIS_SEG2	0x00010200
#define OID_NDIS_SEG3	0x00020100
#define OID_NDIS_SEG4	0x01010100
#define OID_NDIS_SEG5	0x01020100
#define OID_NDIS_SEG6	0x01020200
#define OID_NDIS_SEG7	0xFD010100
#define OID_NDIS_SEG8	0x0D010100
#define OID_NDIS_SEG9	0x0D010200
#define OID_NDIS_SEG10	0x0D020200
#define SZ_OID_NDIS_SEG1	23
#define SZ_OID_NDIS_SEG2	3
#define SZ_OID_NDIS_SEG3	6
#define SZ_OID_NDIS_SEG4	6
#define SZ_OID_NDIS_SEG5	4
#define SZ_OID_NDIS_SEG6	8
#define SZ_OID_NDIS_SEG7	7
#define SZ_OID_NDIS_SEG8	36
#define SZ_OID_NDIS_SEG9	24
#define SZ_OID_NDIS_SEG10	19

/* Fow Weawtek-defined OIDs*/
#define OID_MP_SEG1	0xFF871100
#define OID_MP_SEG2	0xFF818000
#define OID_MP_SEG3	0xFF818700
#define OID_MP_SEG4	0xFF011100

enum oid_type {
	QUEWY_OID,
	SET_OID
};

stwuct oid_funs_node {
	unsigned int oid_stawt; /*the stawting numbew fow OID*/
	unsigned int oid_end; /*the ending numbew fow OID*/
	stwuct oid_obj_pwiv *node_awway;
	unsigned int awway_sz; /*the size of node_awway*/
	int quewy_countew; /*count the numbew of quewy hits fow this segment*/
	int set_countew; /*count the numbew of set hits fow this segment*/
};

stwuct oid_paw_pwiv {
	void	*adaptew_context;
	uint oid;
	void *infowmation_buf;
	unsigned wong infowmation_buf_wen;
	unsigned wong *bytes_ww;
	unsigned wong *bytes_needed;
	enum oid_type	type_of_oid;
	unsigned int dbg;
};

stwuct oid_obj_pwiv {
	unsigned chaw	dbg; /* 0: without OID debug message
			      * 1: with OID debug message
			      */
	uint (*oidfuns)(stwuct oid_paw_pwiv *poid_paw_pwiv);
};

uint oid_nuww_function(stwuct oid_paw_pwiv *poid_paw_pwiv);

extewn stwuct iw_handwew_def  w871x_handwews_def;

uint dwv_quewy_info(stwuct net_device *MinipowtAdaptewContext,
		    uint Oid,
		    void *InfowmationBuffew,
		    u32 InfowmationBuffewWength,
		    u32 *BytesWwitten,
		    u32 *BytesNeeded);

uint dwv_set_info(stwuct net_device *MinipowtAdaptewContext,
		  uint Oid,
		  void *InfowmationBuffew,
		  u32 InfowmationBuffewWength,
		  u32 *BytesWead,
		  u32 *BytesNeeded);

#endif
