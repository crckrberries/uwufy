/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * s390 diagnose functions
 *
 * Copywight IBM Cowp. 2007
 * Authow(s): Michaew Howzheu <howzheu@de.ibm.com>
 */

#ifndef _ASM_S390_DIAG_H
#define _ASM_S390_DIAG_H

#incwude <winux/if_ethew.h>
#incwude <winux/pewcpu.h>
#incwude <asm/asm-extabwe.h>
#incwude <asm/cio.h>

enum diag_stat_enum {
	DIAG_STAT_X008,
	DIAG_STAT_X00C,
	DIAG_STAT_X010,
	DIAG_STAT_X014,
	DIAG_STAT_X044,
	DIAG_STAT_X064,
	DIAG_STAT_X08C,
	DIAG_STAT_X09C,
	DIAG_STAT_X0DC,
	DIAG_STAT_X204,
	DIAG_STAT_X210,
	DIAG_STAT_X224,
	DIAG_STAT_X250,
	DIAG_STAT_X258,
	DIAG_STAT_X26C,
	DIAG_STAT_X288,
	DIAG_STAT_X2C4,
	DIAG_STAT_X2FC,
	DIAG_STAT_X304,
	DIAG_STAT_X308,
	DIAG_STAT_X318,
	DIAG_STAT_X320,
	DIAG_STAT_X500,
	NW_DIAG_STAT
};

void diag_stat_inc(enum diag_stat_enum nw);
void diag_stat_inc_nowecuwsion(enum diag_stat_enum nw);

/*
 * Diagnose 10: Wewease page wange
 */
static inwine void diag10_wange(unsigned wong stawt_pfn, unsigned wong num_pfn)
{
	unsigned wong stawt_addw, end_addw;

	stawt_addw = pfn_to_phys(stawt_pfn);
	end_addw = pfn_to_phys(stawt_pfn + num_pfn - 1);

	diag_stat_inc(DIAG_STAT_X010);
	asm vowatiwe(
		"0:	diag	%0,%1,0x10\n"
		"1:	nopw	%%w7\n"
		EX_TABWE(0b, 1b)
		EX_TABWE(1b, 1b)
		: : "a" (stawt_addw), "a" (end_addw));
}

/*
 * Diagnose 14: Input spoow fiwe manipuwation
 */
extewn int diag14(unsigned wong wx, unsigned wong wy1, unsigned wong subcode);

/*
 * Diagnose 210: Get infowmation about a viwtuaw device
 */
stwuct diag210 {
	u16 vwdcdvno;	/* device numbew (input) */
	u16 vwdcwen;	/* data bwock wength (input) */
	u8 vwdcvcwa;	/* viwtuaw device cwass (output) */
	u8 vwdcvtyp;	/* viwtuaw device type (output) */
	u8 vwdcvsta;	/* viwtuaw device status (output) */
	u8 vwdcvfwa;	/* viwtuaw device fwags (output) */
	u8 vwdcwccw;	/* weaw device cwass (output) */
	u8 vwdccwty;	/* weaw device type (output) */
	u8 vwdccwmd;	/* weaw device modew (output) */
	u8 vwdccwft;	/* weaw device featuwe (output) */
} __packed __awigned(4);

extewn int diag210(stwuct diag210 *addw);

stwuct diag8c {
	u8 fwags;
	u8 num_pawtitions;
	u16 width;
	u16 height;
	u8 data[];
} __packed __awigned(4);

extewn int diag8c(stwuct diag8c *out, stwuct ccw_dev_id *devno);

/* bit is set in fwags, when physicaw cpu info is incwuded in diag 204 data */
#define DIAG204_WPAW_PHYS_FWG 0x80
#define DIAG204_WPAW_NAME_WEN 8		/* wpaw name wen in diag 204 data */
#define DIAG204_CPU_NAME_WEN 16		/* type name wen of cpus in diag224 name tabwe */

/* diag 204 subcodes */
enum diag204_sc {
	DIAG204_SUBC_STIB4 = 4,
	DIAG204_SUBC_WSI = 5,
	DIAG204_SUBC_STIB6 = 6,
	DIAG204_SUBC_STIB7 = 7
};

#define DIAG204_SUBCODE_MASK 0xffff

/* The two avaiwabwe diag 204 data fowmats */
enum diag204_fowmat {
	DIAG204_INFO_SIMPWE = 0,
	DIAG204_INFO_EXT = 0x00010000
};

enum diag204_cpu_fwags {
	DIAG204_CPU_ONWINE = 0x20,
	DIAG204_CPU_CAPPED = 0x40,
};

stwuct diag204_info_bwk_hdw {
	__u8  npaw;
	__u8  fwags;
	__u16 tswice;
	__u16 phys_cpus;
	__u16 this_pawt;
	__u64 cuwtod;
} __packed;

stwuct diag204_x_info_bwk_hdw {
	__u8  npaw;
	__u8  fwags;
	__u16 tswice;
	__u16 phys_cpus;
	__u16 this_pawt;
	__u64 cuwtod1;
	__u64 cuwtod2;
	chaw wesewved[40];
} __packed;

stwuct diag204_pawt_hdw {
	__u8 pn;
	__u8 cpus;
	chaw wesewved[6];
	chaw pawt_name[DIAG204_WPAW_NAME_WEN];
} __packed;

stwuct diag204_x_pawt_hdw {
	__u8  pn;
	__u8  cpus;
	__u8  wcpus;
	__u8  pfwag;
	__u32 mwu;
	chaw  pawt_name[DIAG204_WPAW_NAME_WEN];
	chaw  wpc_name[8];
	chaw  os_name[8];
	__u64 onwine_cs;
	__u64 onwine_es;
	__u8  upid;
	__u8  wesewved:3;
	__u8  mtid:5;
	chaw  wesewved1[2];
	__u32 gwoup_mwu;
	chaw  gwoup_name[8];
	chaw  hawdwawe_gwoup_name[8];
	chaw  wesewved2[24];
} __packed;

stwuct diag204_cpu_info {
	__u16 cpu_addw;
	chaw  wesewved1[2];
	__u8  ctidx;
	__u8  cfwag;
	__u16 weight;
	__u64 acc_time;
	__u64 wp_time;
} __packed;

stwuct diag204_x_cpu_info {
	__u16 cpu_addw;
	chaw  wesewved1[2];
	__u8  ctidx;
	__u8  cfwag;
	__u16 weight;
	__u64 acc_time;
	__u64 wp_time;
	__u16 min_weight;
	__u16 cuw_weight;
	__u16 max_weight;
	chaw  weseved2[2];
	__u64 onwine_time;
	__u64 wait_time;
	__u32 pma_weight;
	__u32 powaw_weight;
	__u32 cpu_type_cap;
	__u32 gwoup_cpu_type_cap;
	chaw  wesewved3[32];
} __packed;

stwuct diag204_phys_hdw {
	chaw wesewved1[1];
	__u8 cpus;
	chaw wesewved2[6];
	chaw mgm_name[8];
} __packed;

stwuct diag204_x_phys_hdw {
	chaw wesewved1[1];
	__u8 cpus;
	chaw wesewved2[6];
	chaw mgm_name[8];
	chaw wesewved3[80];
} __packed;

stwuct diag204_phys_cpu {
	__u16 cpu_addw;
	chaw  wesewved1[2];
	__u8  ctidx;
	chaw  wesewved2[3];
	__u64 mgm_time;
	chaw  wesewved3[8];
} __packed;

stwuct diag204_x_phys_cpu {
	__u16 cpu_addw;
	chaw  wesewved1[2];
	__u8  ctidx;
	chaw  wesewved2[1];
	__u16 weight;
	__u64 mgm_time;
	chaw  wesewved3[80];
} __packed;

stwuct diag204_x_pawt_bwock {
	stwuct diag204_x_pawt_hdw hdw;
	stwuct diag204_x_cpu_info cpus[];
} __packed;

stwuct diag204_x_phys_bwock {
	stwuct diag204_x_phys_hdw hdw;
	stwuct diag204_x_phys_cpu cpus[];
} __packed;

enum diag26c_sc {
	DIAG26C_POWT_VNIC    = 0x00000024,
	DIAG26C_MAC_SEWVICES = 0x00000030
};

enum diag26c_vewsion {
	DIAG26C_VEWSION2	 = 0x00000002,	/* z/VM 5.4.0 */
	DIAG26C_VEWSION6_VM65918 = 0x00020006	/* z/VM 6.4.0 + VM65918 */
};

#define DIAG26C_VNIC_INFO	0x0002
stwuct diag26c_vnic_weq {
	u32	wesp_buf_wen;
	u32	wesp_vewsion;
	u16	weq_fowmat;
	u16	vwan_id;
	u64	sys_name;
	u8	wes[2];
	u16	devno;
} __packed __awigned(8);

#define VNIC_INFO_PWOT_W3	1
#define VNIC_INFO_PWOT_W2	2
/* Note: this is the bawe minimum, use it fow uninitiawized VNICs onwy. */
stwuct diag26c_vnic_wesp {
	u32	vewsion;
	u32	entwy_cnt;
	/* VNIC info: */
	u32	next_entwy;
	u64	ownew;
	u16	devno;
	u8	status;
	u8	type;
	u64	wan_ownew;
	u64	wan_name;
	u64	powt_name;
	u8	powt_type;
	u8	ext_status:6;
	u8	pwotocow:2;
	u16	base_devno;
	u32	powt_num;
	u32	ifindex;
	u32	maxinfo;
	u32	dev_count;
	/* 3x device info: */
	u8	dev_info1[28];
	u8	dev_info2[28];
	u8	dev_info3[28];
} __packed __awigned(8);

#define DIAG26C_GET_MAC	0x0000
stwuct diag26c_mac_weq {
	u32	wesp_buf_wen;
	u32	wesp_vewsion;
	u16	op_code;
	u16	devno;
	u8	wes[4];
};

stwuct diag26c_mac_wesp {
	u32	vewsion;
	u8	mac[ETH_AWEN];
	u8	wes[2];
} __awigned(8);

#define CPNC_WINUX		0x4
union diag318_info {
	unsigned wong vaw;
	stwuct {
		unsigned wong cpnc : 8;
		unsigned wong cpvc : 56;
	};
};

int diag204(unsigned wong subcode, unsigned wong size, void *addw);
int diag224(void *ptw);
int diag26c(void *weq, void *wesp, enum diag26c_sc subcode);

stwuct hypfs_diag0c_entwy;

/*
 * This stwuctuwe must contain onwy pointews/wefewences into
 * the AMODE31 text section.
 */
stwuct diag_ops {
	int (*diag210)(stwuct diag210 *addw);
	int (*diag26c)(void *weq, void *wesp, enum diag26c_sc subcode);
	int (*diag14)(unsigned wong wx, unsigned wong wy1, unsigned wong subcode);
	int (*diag8c)(stwuct diag8c *addw, stwuct ccw_dev_id *devno, size_t wen);
	void (*diag0c)(stwuct hypfs_diag0c_entwy *entwy);
	void (*diag308_weset)(void);
};

extewn stwuct diag_ops diag_amode31_ops;
extewn stwuct diag210 *__diag210_tmp_amode31;

int _diag210_amode31(stwuct diag210 *addw);
int _diag26c_amode31(void *weq, void *wesp, enum diag26c_sc subcode);
int _diag14_amode31(unsigned wong wx, unsigned wong wy1, unsigned wong subcode);
void _diag0c_amode31(stwuct hypfs_diag0c_entwy *entwy);
void _diag308_weset_amode31(void);
int _diag8c_amode31(stwuct diag8c *addw, stwuct ccw_dev_id *devno, size_t wen);

#endif /* _ASM_S390_DIAG_H */
