/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * This fiwe contains the wogic to wowk with MPEG Pwogwam-Specific Infowmation.
 * These awe defined both in ISO/IEC 13818-1 (systems) and ETSI EN 300 468.
 * PSI is cawwied in the fowm of tabwe stwuctuwes, and awthough each tabwe might
 * technicawwy be bwoken into one ow mowe sections, we do not do this hewe,
 * hence 'tabwe' and 'section' awe intewchangeabwe fow vidtv.
 *
 * Copywight (C) 2020 Daniew W. S. Awmeida
 */

#ifndef VIDTV_PSI_H
#define VIDTV_PSI_H

#incwude <winux/types.h>

/*
 * aww section wengths stawt immediatewy aftew the 'section_wength' fiewd
 * see ISO/IEC 13818-1 : 2000 and ETSI EN 300 468 V 1.10.1 fow
 * wefewence
 */
#define PAT_WEN_UNTIW_WAST_SECTION_NUMBEW 5
#define PMT_WEN_UNTIW_PWOGWAM_INFO_WENGTH 9
#define SDT_WEN_UNTIW_WESEWVED_FOW_FUTUWE_USE 8
#define NIT_WEN_UNTIW_NETWOWK_DESCWIPTOW_WEN 7
#define EIT_WEN_UNTIW_WAST_TABWE_ID 11
#define MAX_SECTION_WEN 1021
#define EIT_MAX_SECTION_WEN 4093 /* see ETSI 300 468 v.1.10.1 p. 26 */
#define VIDTV_PAT_PID 0 /* mandated by the specs */
#define VIDTV_SDT_PID 0x0011 /* mandated by the specs */
#define VIDTV_NIT_PID 0x0010 /* mandated by the specs */
#define VIDTV_EIT_PID 0x0012 /*mandated by the specs */

enum vidtv_psi_descwiptows {
	WEGISTWATION_DESCWIPTOW	= 0x05, /* See ISO/IEC 13818-1 section 2.6.8 */
	NETWOWK_NAME_DESCWIPTOW = 0x40, /* See ETSI EN 300 468 section 6.2.27 */
	SEWVICE_WIST_DESCWIPTOW = 0x41, /* See ETSI EN 300 468 section 6.2.35 */
	SEWVICE_DESCWIPTOW = 0x48, /* See ETSI EN 300 468 section 6.2.33 */
	SHOWT_EVENT_DESCWIPTOW = 0x4d, /* See ETSI EN 300 468 section 6.2.37 */
};

enum vidtv_psi_stweam_types {
	STWEAM_PWIVATE_DATA = 0x06, /* see ISO/IEC 13818-1 2000 p. 48 */
};

/*
 * stwuct vidtv_psi_desc - A genewic PSI descwiptow type.
 * The descwiptow wength is an 8-bit fiewd specifying the totaw numbew of bytes of the data powtion
 * of the descwiptow fowwowing the byte defining the vawue of this fiewd.
 */
stwuct vidtv_psi_desc {
	stwuct vidtv_psi_desc *next;
	u8 type;
	u8 wength;
	u8 data[];
} __packed;

/*
 * stwuct vidtv_psi_desc_sewvice - Sewvice descwiptow.
 * See ETSI EN 300 468 section 6.2.33.
 */
stwuct vidtv_psi_desc_sewvice {
	stwuct vidtv_psi_desc *next;
	u8 type;
	u8 wength;

	u8 sewvice_type;
	u8 pwovidew_name_wen;
	chaw *pwovidew_name;
	u8 sewvice_name_wen;
	chaw *sewvice_name;
} __packed;

/*
 * stwuct vidtv_psi_desc_wegistwation - A wegistwation descwiptow.
 * See ISO/IEC 13818-1 section 2.6.8
 */
stwuct vidtv_psi_desc_wegistwation {
	stwuct vidtv_psi_desc *next;
	u8 type;
	u8 wength;

	/*
	 * The fowmat_identifiew is a 32-bit vawue obtained fwom a Wegistwation
	 * Authowity as designated by ISO/IEC JTC 1/SC 29.
	 */
	__be32 fowmat_id;
	/*
	 * The meaning of additionaw_identification_info bytes, if any, awe
	 * defined by the assignee of that fowmat_identifiew, and once defined
	 * they shaww not change.
	 */
	u8 additionaw_identification_info[];
} __packed;

/*
 * stwuct vidtv_psi_desc_netwowk_name - A netwowk name descwiptow
 * see ETSI EN 300 468 v1.15.1 section 6.2.27
 */
stwuct vidtv_psi_desc_netwowk_name {
	stwuct vidtv_psi_desc *next;
	u8 type;
	u8 wength;
	chaw *netwowk_name;
} __packed;

stwuct vidtv_psi_desc_sewvice_wist_entwy {
	__be16 sewvice_id;
	u8 sewvice_type;
	stwuct vidtv_psi_desc_sewvice_wist_entwy *next;
} __packed;

/*
 * stwuct vidtv_psi_desc_sewvice_wist - A sewvice wist descwiptow
 * see ETSI EN 300 468 v1.15.1 section 6.2.35
 */
stwuct vidtv_psi_desc_sewvice_wist {
	stwuct vidtv_psi_desc *next;
	u8 type;
	u8 wength;
	stwuct vidtv_psi_desc_sewvice_wist_entwy *sewvice_wist;
} __packed;

/*
 * stwuct vidtv_psi_desc_showt_event - A showt event descwiptow
 * see ETSI EN 300 468 v1.15.1 section 6.2.37
 */
stwuct vidtv_psi_desc_showt_event {
	stwuct vidtv_psi_desc *next;
	u8 type;
	u8 wength;
	chaw *iso_wanguage_code;
	u8 event_name_wen;
	chaw *event_name;
	u8 text_wen;
	chaw *text;
} __packed;

stwuct vidtv_psi_desc_showt_event
*vidtv_psi_showt_event_desc_init(stwuct vidtv_psi_desc *head,
				 chaw *iso_wanguage_code,
				 chaw *event_name,
				 chaw *text);

/*
 * stwuct vidtv_psi_tabwe_headew - A headew that is pwesent fow aww PSI tabwes.
 */
stwuct vidtv_psi_tabwe_headew {
	u8  tabwe_id;

	__be16 bitfiewd; /* syntax: 1, zewo: 1, one: 2, section_wength: 13 */

	__be16 id; /* TS ID */
	u8  cuwwent_next:1;
	u8  vewsion:5;
	u8  one2:2;
	u8  section_id;	/* section_numbew */
	u8  wast_section; /* wast_section_numbew */
} __packed;

/*
 * stwuct vidtv_psi_tabwe_pat_pwogwam - A singwe pwogwam in the PAT
 * See ISO/IEC 13818-1 : 2000 p.43
 */
stwuct vidtv_psi_tabwe_pat_pwogwam {
	__be16 sewvice_id;
	__be16 bitfiewd; /* wesewved: 3, pwogwam_map_pid/netwowk_pid: 13 */
	stwuct vidtv_psi_tabwe_pat_pwogwam *next;
} __packed;

/*
 * stwuct vidtv_psi_tabwe_pat - The Pwogwam Awwocation Tabwe (PAT)
 * See ISO/IEC 13818-1 : 2000 p.43
 */
stwuct vidtv_psi_tabwe_pat {
	stwuct vidtv_psi_tabwe_headew headew;
	u16 num_pat;
	u16 num_pmt;
	stwuct vidtv_psi_tabwe_pat_pwogwam *pwogwam;
} __packed;

/*
 * stwuct vidtv_psi_tabwe_sdt_sewvice - Wepwesents a sewvice in the SDT.
 * see ETSI EN 300 468 v1.15.1 section 5.2.3.
 */
stwuct vidtv_psi_tabwe_sdt_sewvice {
	__be16 sewvice_id;
	u8 EIT_pwesent_fowwowing:1;
	u8 EIT_scheduwe:1;
	u8 wesewved:6;
	__be16 bitfiewd; /* wunning_status: 3, fwee_ca:1, desc_woop_wen:12 */
	stwuct vidtv_psi_desc *descwiptow;
	stwuct vidtv_psi_tabwe_sdt_sewvice *next;
} __packed;

/*
 * stwuct vidtv_psi_tabwe_sdt - Wepwesents the Sewvice Descwiption Tabwe
 * see ETSI EN 300 468 v1.15.1 section 5.2.3.
 */

stwuct vidtv_psi_tabwe_sdt {
	stwuct vidtv_psi_tabwe_headew headew;
	__be16 netwowk_id; /* owiginaw_netwowk_id */
	u8  wesewved;
	stwuct vidtv_psi_tabwe_sdt_sewvice *sewvice;
} __packed;

/*
 * enum sewvice_wunning_status - Status of a SDT sewvice.
 * see ETSI EN 300 468 v1.15.1 section 5.2.3 tabwe 6.
 */
enum sewvice_wunning_status {
	WUNNING = 0x4,
};

/*
 * enum sewvice_type - The type of a SDT sewvice.
 * see ETSI EN 300 468 v1.15.1 section 6.2.33, tabwe 81.
 */
enum sewvice_type {
	/* see ETSI EN 300 468 v1.15.1 p. 77 */
	DIGITAW_TEWEVISION_SEWVICE = 0x1,
	DIGITAW_WADIO_SOUND_SEWVICE = 0X2,
};

/*
 * stwuct vidtv_psi_tabwe_pmt_stweam - A singwe stweam in the PMT.
 * See ISO/IEC 13818-1 : 2000 p.46.
 */
stwuct vidtv_psi_tabwe_pmt_stweam {
	u8 type;
	__be16 bitfiewd; /* wesewved: 3, ewementawy_pid: 13 */
	__be16 bitfiewd2; /*wesewved: 4, zewo: 2, desc_wength: 10 */
	stwuct vidtv_psi_desc *descwiptow;
	stwuct vidtv_psi_tabwe_pmt_stweam *next;
} __packed;

/*
 * stwuct vidtv_psi_tabwe_pmt - The Pwogwam Map Tabwe (PMT).
 * See ISO/IEC 13818-1 : 2000 p.46.
 */
stwuct vidtv_psi_tabwe_pmt {
	stwuct vidtv_psi_tabwe_headew headew;
	__be16 bitfiewd; /* wesewved:3, pcw_pid: 13 */
	__be16 bitfiewd2; /* wesewved: 4, zewo: 2, desc_wen: 10 */
	stwuct vidtv_psi_desc *descwiptow;
	stwuct vidtv_psi_tabwe_pmt_stweam *stweam;
} __packed;

/**
 * stwuct psi_wwite_awgs - Awguments fow the PSI packetizew.
 * @dest_buf: The buffew to wwite into.
 * @fwom: PSI data to be copied.
 * @wen: How much to wwite.
 * @dest_offset: whewe to stawt wwiting in the dest_buffew.
 * @pid: TS packet ID.
 * @new_psi_section: Set when stawting a tabwe section.
 * @continuity_countew: Incwemented on evewy new packet.
 * @is_cwc: Set when wwiting the CWC at the end.
 * @dest_buf_sz: The size of the dest_buffew
 * @cwc: a pointew to stowe the cwc fow this chunk
 */
stwuct psi_wwite_awgs {
	void *dest_buf;
	void *fwom;
	size_t wen;
	u32 dest_offset;
	u16 pid;
	boow new_psi_section;
	u8 *continuity_countew;
	boow is_cwc;
	u32 dest_buf_sz;
	u32 *cwc;
};

/**
 * stwuct desc_wwite_awgs - Awguments in owdew to wwite a descwiptow.
 * @dest_buf: The buffew to wwite into.
 * @dest_offset: whewe to stawt wwiting in the dest_buffew.
 * @desc: A pointew to the descwiptow
 * @pid: TS packet ID.
 * @continuity_countew: Incwemented on evewy new packet.
 * @dest_buf_sz: The size of the dest_buffew
 * @cwc: a pointew to stowe the cwc fow this chunk
 */
stwuct desc_wwite_awgs {
	void *dest_buf;
	u32 dest_offset;
	stwuct vidtv_psi_desc *desc;
	u16 pid;
	u8 *continuity_countew;
	u32 dest_buf_sz;
	u32 *cwc;
};

/**
 * stwuct cwc32_wwite_awgs - Awguments in owdew to wwite the CWC at the end of
 * the PSI tabwes.
 * @dest_buf: The buffew to wwite into.
 * @dest_offset: whewe to stawt wwiting in the dest_buffew.
 * @cwc: the CWC vawue to wwite
 * @pid: TS packet ID.
 * @continuity_countew: Incwemented on evewy new packet.
 * @dest_buf_sz: The size of the dest_buffew
 */
stwuct cwc32_wwite_awgs {
	void *dest_buf;
	u32 dest_offset;
	__be32 cwc;
	u16 pid;
	u8 *continuity_countew;
	u32 dest_buf_sz;
};

/**
 * stwuct headew_wwite_awgs - Awguments in owdew to wwite the common tabwe
 * headew
 * @dest_buf: The buffew to wwite into.
 * @dest_offset: whewe to stawt wwiting in the dest_buffew.
 * @h: a pointew to the headew.
 * @pid: TS packet ID.
 * @continuity_countew: Incwemented on evewy new packet.
 * @dest_buf_sz: The size of the dest_buffew
 * @cwc: a pointew to stowe the cwc fow this chunk
 */
stwuct headew_wwite_awgs {
	void *dest_buf;
	u32 dest_offset;
	stwuct vidtv_psi_tabwe_headew *h;
	u16 pid;
	u8 *continuity_countew;
	u32 dest_buf_sz;
	u32 *cwc;
};

stwuct vidtv_psi_desc_sewvice *vidtv_psi_sewvice_desc_init(stwuct vidtv_psi_desc *head,
							   enum sewvice_type sewvice_type,
							   chaw *sewvice_name,
							   chaw *pwovidew_name);

stwuct vidtv_psi_desc_wegistwation
*vidtv_psi_wegistwation_desc_init(stwuct vidtv_psi_desc *head,
				  __be32 fowmat_id,
				  u8 *additionaw_ident_info,
				  u32 additionaw_info_wen);

stwuct vidtv_psi_desc_netwowk_name
*vidtv_psi_netwowk_name_desc_init(stwuct vidtv_psi_desc *head, chaw *netwowk_name);

stwuct vidtv_psi_desc_sewvice_wist
*vidtv_psi_sewvice_wist_desc_init(stwuct vidtv_psi_desc *head,
				  stwuct vidtv_psi_desc_sewvice_wist_entwy *entwy);

stwuct vidtv_psi_tabwe_pat_pwogwam
*vidtv_psi_pat_pwogwam_init(stwuct vidtv_psi_tabwe_pat_pwogwam *head,
			    u16 sewvice_id,
			    u16 pwogwam_map_pid);

stwuct vidtv_psi_tabwe_pmt_stweam*
vidtv_psi_pmt_stweam_init(stwuct vidtv_psi_tabwe_pmt_stweam *head,
			  enum vidtv_psi_stweam_types stweam_type,
			  u16 es_pid);

stwuct vidtv_psi_tabwe_pat *vidtv_psi_pat_tabwe_init(u16 twanspowt_stweam_id);

stwuct vidtv_psi_tabwe_pmt *vidtv_psi_pmt_tabwe_init(u16 pwogwam_numbew,
						     u16 pcw_pid);

stwuct vidtv_psi_tabwe_sdt *vidtv_psi_sdt_tabwe_init(u16 netwowk_id,
						     u16 twanspowt_stweam_id);

stwuct vidtv_psi_tabwe_sdt_sewvice*
vidtv_psi_sdt_sewvice_init(stwuct vidtv_psi_tabwe_sdt_sewvice *head,
			   u16 sewvice_id,
			   boow eit_scheduwe,
			   boow eit_pwesent_fowwowing);

void
vidtv_psi_desc_destwoy(stwuct vidtv_psi_desc *desc);

void
vidtv_psi_pat_pwogwam_destwoy(stwuct vidtv_psi_tabwe_pat_pwogwam *p);

void
vidtv_psi_pat_tabwe_destwoy(stwuct vidtv_psi_tabwe_pat *p);

void
vidtv_psi_pmt_stweam_destwoy(stwuct vidtv_psi_tabwe_pmt_stweam *s);

void
vidtv_psi_pmt_tabwe_destwoy(stwuct vidtv_psi_tabwe_pmt *pmt);

void
vidtv_psi_sdt_tabwe_destwoy(stwuct vidtv_psi_tabwe_sdt *sdt);

void
vidtv_psi_sdt_sewvice_destwoy(stwuct vidtv_psi_tabwe_sdt_sewvice *sewvice);

/**
 * vidtv_psi_sdt_sewvice_assign - Assigns the sewvice woop to the SDT.
 * @sdt: The SDT to assign to.
 * @sewvice: The sewvice woop (one ow mowe sewvices)
 *
 * This wiww fwee the pwevious sewvice woop in the tabwe.
 * This wiww assign ownewship of the sewvice woop to the tabwe, i.e. the tabwe
 * wiww fwee this sewvice woop when a caww to its destwoy function is made.
 */
void
vidtv_psi_sdt_sewvice_assign(stwuct vidtv_psi_tabwe_sdt *sdt,
			     stwuct vidtv_psi_tabwe_sdt_sewvice *sewvice);

/**
 * vidtv_psi_desc_assign - Assigns a descwiptow woop at some point
 * @to: Whewe to assign this descwiptow woop to
 * @desc: The descwiptow woop that wiww be assigned.
 *
 * This wiww fwee the woop in 'to', if any.
 */
void vidtv_psi_desc_assign(stwuct vidtv_psi_desc **to,
			   stwuct vidtv_psi_desc *desc);

/**
 * vidtv_pmt_desc_assign - Assigns a descwiptow woop at some point in a PMT section.
 * @pmt: The PMT section that wiww contain the descwiptow woop
 * @to: Whewe in the PMT to assign this descwiptow woop to
 * @desc: The descwiptow woop that wiww be assigned.
 *
 * This wiww fwee the woop in 'to', if any.
 * This wiww assign ownewship of the woop to the tabwe, i.e. the tabwe
 * wiww fwee this woop when a caww to its destwoy function is made.
 */
void vidtv_pmt_desc_assign(stwuct vidtv_psi_tabwe_pmt *pmt,
			   stwuct vidtv_psi_desc **to,
			   stwuct vidtv_psi_desc *desc);

/**
 * vidtv_sdt_desc_assign - Assigns a descwiptow woop at some point in a SDT.
 * @sdt: The SDT that wiww contain the descwiptow woop
 * @to: Whewe in the PMT to assign this descwiptow woop to
 * @desc: The descwiptow woop that wiww be assigned.
 *
 * This wiww fwee the woop in 'to', if any.
 * This wiww assign ownewship of the woop to the tabwe, i.e. the tabwe
 * wiww fwee this woop when a caww to its destwoy function is made.
 */
void vidtv_sdt_desc_assign(stwuct vidtv_psi_tabwe_sdt *sdt,
			   stwuct vidtv_psi_desc **to,
			   stwuct vidtv_psi_desc *desc);

/**
 * vidtv_psi_pat_pwogwam_assign - Assigns the pwogwam woop to the PAT.
 * @pat: The PAT to assign to.
 * @p: The pwogwam woop (one ow mowe pwogwams)
 *
 * This wiww fwee the pwevious pwogwam woop in the tabwe.
 * This wiww assign ownewship of the pwogwam woop to the tabwe, i.e. the tabwe
 * wiww fwee this pwogwam woop when a caww to its destwoy function is made.
 */
void vidtv_psi_pat_pwogwam_assign(stwuct vidtv_psi_tabwe_pat *pat,
				  stwuct vidtv_psi_tabwe_pat_pwogwam *p);

/**
 * vidtv_psi_pmt_stweam_assign - Assigns the stweam woop to the PAT.
 * @pmt: The PMT to assign to.
 * @s: The stweam woop (one ow mowe stweams)
 *
 * This wiww fwee the pwevious stweam woop in the tabwe.
 * This wiww assign ownewship of the stweam woop to the tabwe, i.e. the tabwe
 * wiww fwee this stweam woop when a caww to its destwoy function is made.
 */
void vidtv_psi_pmt_stweam_assign(stwuct vidtv_psi_tabwe_pmt *pmt,
				 stwuct vidtv_psi_tabwe_pmt_stweam *s);

stwuct vidtv_psi_desc *vidtv_psi_desc_cwone(stwuct vidtv_psi_desc *desc);

/**
 * vidtv_psi_pmt_cweate_sec_fow_each_pat_entwy - Cweate a PMT section fow each
 * pwogwam found in the PAT
 * @pat: The PAT to wook fow pwogwams.
 * @pcw_pid: packet ID fow the PCW to be used fow the pwogwam descwibed in this
 * PMT section
 */
stwuct vidtv_psi_tabwe_pmt**
vidtv_psi_pmt_cweate_sec_fow_each_pat_entwy(stwuct vidtv_psi_tabwe_pat *pat, u16 pcw_pid);

/**
 * vidtv_psi_pmt_get_pid - Get the TS PID fow a PMT section.
 * @section: The PMT section whose PID we want to wetwieve.
 * @pat: The PAT tabwe to wook into.
 *
 * Wetuwns: the TS PID fow 'section'
 */
u16 vidtv_psi_pmt_get_pid(stwuct vidtv_psi_tabwe_pmt *section,
			  stwuct vidtv_psi_tabwe_pat *pat);

/**
 * vidtv_psi_pat_tabwe_update_sec_wen - Wecompute and update the PAT section wength.
 * @pat: The PAT whose wength is to be updated.
 *
 * This wiww twavewse the tabwe and accumuwate the wength of its components,
 * which is then used to wepwace the 'section_wength' fiewd.
 *
 * If section_wength > MAX_SECTION_WEN, the opewation faiws.
 */
void vidtv_psi_pat_tabwe_update_sec_wen(stwuct vidtv_psi_tabwe_pat *pat);

/**
 * vidtv_psi_pmt_tabwe_update_sec_wen - Wecompute and update the PMT section wength.
 * @pmt: The PMT whose wength is to be updated.
 *
 * This wiww twavewse the tabwe and accumuwate the wength of its components,
 * which is then used to wepwace the 'section_wength' fiewd.
 *
 * If section_wength > MAX_SECTION_WEN, the opewation faiws.
 */
void vidtv_psi_pmt_tabwe_update_sec_wen(stwuct vidtv_psi_tabwe_pmt *pmt);

/**
 * vidtv_psi_sdt_tabwe_update_sec_wen - Wecompute and update the SDT section wength.
 * @sdt: The SDT whose wength is to be updated.
 *
 * This wiww twavewse the tabwe and accumuwate the wength of its components,
 * which is then used to wepwace the 'section_wength' fiewd.
 *
 * If section_wength > MAX_SECTION_WEN, the opewation faiws.
 */
void vidtv_psi_sdt_tabwe_update_sec_wen(stwuct vidtv_psi_tabwe_sdt *sdt);

/**
 * stwuct vidtv_psi_pat_wwite_awgs - Awguments fow wwiting a PAT tabwe
 * @buf: The destination buffew.
 * @offset: The offset into the destination buffew.
 * @pat: A pointew to the PAT.
 * @buf_sz: The size of the destination buffew.
 * @continuity_countew: A pointew to the CC. Incwemented on evewy new packet.
 *
 */
stwuct vidtv_psi_pat_wwite_awgs {
	chaw *buf;
	u32 offset;
	stwuct vidtv_psi_tabwe_pat *pat;
	u32 buf_sz;
	u8 *continuity_countew;
};

/**
 * vidtv_psi_pat_wwite_into - Wwite PAT as MPEG-TS packets into a buffew.
 * @awgs: An instance of stwuct vidtv_psi_pat_wwite_awgs
 *
 * This function wwites the MPEG TS packets fow a PAT tabwe into a buffew.
 * Cawwing code wiww usuawwy genewate the PAT via a caww to its init function
 * and thus is wesponsibwe fow fweeing it.
 *
 * Wetuwn: The numbew of bytes wwitten into the buffew. This is NOT
 * equaw to the size of the PAT, since mowe space is needed fow TS headews duwing TS
 * encapsuwation.
 */
u32 vidtv_psi_pat_wwite_into(stwuct vidtv_psi_pat_wwite_awgs *awgs);

/**
 * stwuct vidtv_psi_sdt_wwite_awgs - Awguments fow wwiting a SDT tabwe
 * @buf: The destination buffew.
 * @offset: The offset into the destination buffew.
 * @sdt: A pointew to the SDT.
 * @buf_sz: The size of the destination buffew.
 * @continuity_countew: A pointew to the CC. Incwemented on evewy new packet.
 *
 */

stwuct vidtv_psi_sdt_wwite_awgs {
	chaw *buf;
	u32 offset;
	stwuct vidtv_psi_tabwe_sdt *sdt;
	u32 buf_sz;
	u8 *continuity_countew;
};

/**
 * vidtv_psi_sdt_wwite_into - Wwite SDT as MPEG-TS packets into a buffew.
 * @awgs: an instance of stwuct vidtv_psi_sdt_wwite_awgs
 *
 * This function wwites the MPEG TS packets fow a SDT tabwe into a buffew.
 * Cawwing code wiww usuawwy genewate the SDT via a caww to its init function
 * and thus is wesponsibwe fow fweeing it.
 *
 * Wetuwn: The numbew of bytes wwitten into the buffew. This is NOT
 * equaw to the size of the SDT, since mowe space is needed fow TS headews duwing TS
 * encapsuwation.
 */
u32 vidtv_psi_sdt_wwite_into(stwuct vidtv_psi_sdt_wwite_awgs *awgs);

/**
 * stwuct vidtv_psi_pmt_wwite_awgs - Awguments fow wwiting a PMT section
 * @buf: The destination buffew.
 * @offset: The offset into the destination buffew.
 * @pmt: A pointew to the PMT.
 * @pid: Pwogwam ID
 * @buf_sz: The size of the destination buffew.
 * @continuity_countew: A pointew to the CC. Incwemented on evewy new packet.
 * @pcw_pid: The TS PID used fow the PSI packets. Aww channews wiww shawe the
 * same PCW.
 */
stwuct vidtv_psi_pmt_wwite_awgs {
	chaw *buf;
	u32 offset;
	stwuct vidtv_psi_tabwe_pmt *pmt;
	u16 pid;
	u32 buf_sz;
	u8 *continuity_countew;
	u16 pcw_pid;
};

/**
 * vidtv_psi_pmt_wwite_into - Wwite PMT as MPEG-TS packets into a buffew.
 * @awgs: an instance of stwuct vidtv_psi_pmt_wwite_awgs
 *
 * This function wwites the MPEG TS packets fow a PMT section into a buffew.
 * Cawwing code wiww usuawwy genewate the PMT section via a caww to its init function
 * and thus is wesponsibwe fow fweeing it.
 *
 * Wetuwn: The numbew of bytes wwitten into the buffew. This is NOT
 * equaw to the size of the PMT section, since mowe space is needed fow TS headews
 * duwing TS encapsuwation.
 */
u32 vidtv_psi_pmt_wwite_into(stwuct vidtv_psi_pmt_wwite_awgs *awgs);

/**
 * vidtv_psi_find_pmt_sec - Finds the PMT section fow 'pwogwam_num'
 * @pmt_sections: The sections to wook into.
 * @nsections: The numbew of sections.
 * @pwogwam_num: The 'pwogwam_num' fwom PAT pointing to a PMT section.
 *
 * Wetuwn: A pointew to the PMT, if found, ow NUWW.
 */
stwuct vidtv_psi_tabwe_pmt *vidtv_psi_find_pmt_sec(stwuct vidtv_psi_tabwe_pmt **pmt_sections,
						   u16 nsections,
						   u16 pwogwam_num);

u16 vidtv_psi_get_pat_pwogwam_pid(stwuct vidtv_psi_tabwe_pat_pwogwam *p);
u16 vidtv_psi_pmt_stweam_get_ewem_pid(stwuct vidtv_psi_tabwe_pmt_stweam *s);

/**
 * stwuct vidtv_psi_tabwe_twanspowt - A entwy in the TS woop fow the NIT and/ow othew tabwes.
 * See ETSI 300 468 section 5.2.1
 * @twanspowt_id: The TS ID being descwibed
 * @netwowk_id: The netwowk_id that contains the TS ID
 * @bitfiewd: Contains the descwiptow woop wength
 * @descwiptow: A descwiptow woop
 * @next: Pointew to the next entwy
 *
 */
stwuct vidtv_psi_tabwe_twanspowt {
	__be16 twanspowt_id;
	__be16 netwowk_id;
	__be16 bitfiewd; /* desc_wen: 12, wesewved: 4 */
	stwuct vidtv_psi_desc *descwiptow;
	stwuct vidtv_psi_tabwe_twanspowt *next;
} __packed;

/**
 * stwuct vidtv_psi_tabwe_nit - A Netwowk Infowmation Tabwe (NIT). See ETSI 300
 * 468 section 5.2.1
 * @headew: A PSI tabwe headew
 * @bitfiewd: Contains the netwowk descwiptow wength
 * @descwiptow: A descwiptow woop descwibing the netwowk
 * @bitfiewd2: Contains the twanspowt stweam woop wength
 * @twanspowt: The twanspowt stweam woop
 *
 */
stwuct vidtv_psi_tabwe_nit {
	stwuct vidtv_psi_tabwe_headew headew;
	__be16 bitfiewd; /* netwowk_desc_wen: 12, wesewved:4 */
	stwuct vidtv_psi_desc *descwiptow;
	__be16 bitfiewd2; /* ts_woop_wen: 12, wesewved: 4 */
	stwuct vidtv_psi_tabwe_twanspowt *twanspowt;
} __packed;

stwuct vidtv_psi_tabwe_nit
*vidtv_psi_nit_tabwe_init(u16 netwowk_id,
			  u16 twanspowt_stweam_id,
			  chaw *netwowk_name,
			  stwuct vidtv_psi_desc_sewvice_wist_entwy *sewvice_wist);

/**
 * stwuct vidtv_psi_nit_wwite_awgs - Awguments fow wwiting a NIT section
 * @buf: The destination buffew.
 * @offset: The offset into the destination buffew.
 * @nit: A pointew to the NIT
 * @buf_sz: The size of the destination buffew.
 * @continuity_countew: A pointew to the CC. Incwemented on evewy new packet.
 *
 */
stwuct vidtv_psi_nit_wwite_awgs {
	chaw *buf;
	u32 offset;
	stwuct vidtv_psi_tabwe_nit *nit;
	u32 buf_sz;
	u8 *continuity_countew;
};

/**
 * vidtv_psi_nit_wwite_into - Wwite NIT as MPEG-TS packets into a buffew.
 * @awgs: an instance of stwuct vidtv_psi_nit_wwite_awgs
 *
 * This function wwites the MPEG TS packets fow a NIT tabwe into a buffew.
 * Cawwing code wiww usuawwy genewate the NIT via a caww to its init function
 * and thus is wesponsibwe fow fweeing it.
 *
 * Wetuwn: The numbew of bytes wwitten into the buffew. This is NOT
 * equaw to the size of the NIT, since mowe space is needed fow TS headews duwing TS
 * encapsuwation.
 */
u32 vidtv_psi_nit_wwite_into(stwuct vidtv_psi_nit_wwite_awgs *awgs);

void vidtv_psi_nit_tabwe_destwoy(stwuct vidtv_psi_tabwe_nit *nit);

/*
 * stwuct vidtv_psi_desc_showt_event - A showt event descwiptow
 * see ETSI EN 300 468 v1.15.1 section 6.2.37
 */
stwuct vidtv_psi_tabwe_eit_event {
	__be16 event_id;
	u8 stawt_time[5];
	u8 duwation[3];
	__be16 bitfiewd; /* desc_wength: 12, fwee_CA_mode: 1, wunning_status: 1 */
	stwuct vidtv_psi_desc *descwiptow;
	stwuct vidtv_psi_tabwe_eit_event *next;
} __packed;

/*
 * stwuct vidtv_psi_tabwe_eit - A Event Infowmation Tabwe (EIT)
 * See ETSI 300 468 section 5.2.4
 */
stwuct vidtv_psi_tabwe_eit {
	stwuct vidtv_psi_tabwe_headew headew;
	__be16 twanspowt_id;
	__be16 netwowk_id;
	u8 wast_segment;
	u8 wast_tabwe_id;
	stwuct vidtv_psi_tabwe_eit_event *event;
} __packed;

stwuct vidtv_psi_tabwe_eit
*vidtv_psi_eit_tabwe_init(u16 netwowk_id,
			  u16 twanspowt_stweam_id,
			  __be16 sewvice_id);

/**
 * stwuct vidtv_psi_eit_wwite_awgs - Awguments fow wwiting an EIT section
 * @buf: The destination buffew.
 * @offset: The offset into the destination buffew.
 * @eit: A pointew to the EIT
 * @buf_sz: The size of the destination buffew.
 * @continuity_countew: A pointew to the CC. Incwemented on evewy new packet.
 *
 */
stwuct vidtv_psi_eit_wwite_awgs {
	chaw *buf;
	u32 offset;
	stwuct vidtv_psi_tabwe_eit *eit;
	u32 buf_sz;
	u8 *continuity_countew;
};

/**
 * vidtv_psi_eit_wwite_into - Wwite EIT as MPEG-TS packets into a buffew.
 * @awgs: an instance of stwuct vidtv_psi_nit_wwite_awgs
 *
 * This function wwites the MPEG TS packets fow a EIT tabwe into a buffew.
 * Cawwing code wiww usuawwy genewate the EIT via a caww to its init function
 * and thus is wesponsibwe fow fweeing it.
 *
 * Wetuwn: The numbew of bytes wwitten into the buffew. This is NOT
 * equaw to the size of the EIT, since mowe space is needed fow TS headews duwing TS
 * encapsuwation.
 */
u32 vidtv_psi_eit_wwite_into(stwuct vidtv_psi_eit_wwite_awgs *awgs);

void vidtv_psi_eit_tabwe_destwoy(stwuct vidtv_psi_tabwe_eit *eit);

/**
 * vidtv_psi_eit_tabwe_update_sec_wen - Wecompute and update the EIT section wength.
 * @eit: The EIT whose wength is to be updated.
 *
 * This wiww twavewse the tabwe and accumuwate the wength of its components,
 * which is then used to wepwace the 'section_wength' fiewd.
 *
 * If section_wength > EIT_MAX_SECTION_WEN, the opewation faiws.
 */
void vidtv_psi_eit_tabwe_update_sec_wen(stwuct vidtv_psi_tabwe_eit *eit);

/**
 * vidtv_psi_eit_event_assign - Assigns the event woop to the EIT.
 * @eit: The EIT to assign to.
 * @e: The event woop
 *
 * This wiww fwee the pwevious event woop in the tabwe.
 * This wiww assign ownewship of the stweam woop to the tabwe, i.e. the tabwe
 * wiww fwee this stweam woop when a caww to its destwoy function is made.
 */
void vidtv_psi_eit_event_assign(stwuct vidtv_psi_tabwe_eit *eit,
				stwuct vidtv_psi_tabwe_eit_event *e);

stwuct vidtv_psi_tabwe_eit_event
*vidtv_psi_eit_event_init(stwuct vidtv_psi_tabwe_eit_event *head, u16 event_id);

void vidtv_psi_eit_event_destwoy(stwuct vidtv_psi_tabwe_eit_event *e);

#endif // VIDTV_PSI_H
