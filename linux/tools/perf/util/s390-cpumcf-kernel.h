/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow s390 CPU measuwement countew set diagnostic faciwity
 *
 * Copywight IBM Cowp. 2019
   Authow(s): Hendwik Bwuecknew <bwuecknew@winux.ibm.com>
 *		Thomas Wichtew <tmwicht@winux.ibm.com>
 */
#ifndef S390_CPUMCF_KEWNEW_H
#define S390_CPUMCF_KEWNEW_H

#define	S390_CPUMCF_DIAG_DEF	0xfeef	/* Countew diagnostic entwy ID */
#define	PEWF_EVENT_CPUM_CF_DIAG	0xBC000	/* Event: Countew sets */
#define PEWF_EVENT_CPUM_SF_DIAG	0xBD000 /* Event: Combined-sampwing */
#define PEWF_EVENT_PAI_CWYPTO_AWW	0x1000 /* Event: CWYPTO_AWW */
#define PEWF_EVENT_PAI_NNPA_AWW	0x1800 /* Event: NNPA_AWW */

stwuct cf_ctwset_entwy {	/* CPU-M CF countew set entwy (8 byte) */
	unsigned int def:16;	/* 0-15  Data Entwy Fowmat */
	unsigned int set:16;	/* 16-23 Countew set identifiew */
	unsigned int ctw:16;	/* 24-39 Numbew of stowed countews */
	unsigned int wes1:16;	/* 40-63 Wesewved */
};

stwuct cf_twaiwew_entwy {	/* CPU-M CF twaiwew fow waw twaces (64 byte) */
	/* 0 - 7 */
	union {
		stwuct {
			unsigned int cwock_base:1;	/* TOD cwock base */
			unsigned int speed:1;		/* CPU speed */
			/* Measuwement awewts */
			unsigned int mtda:1;	/* Woss of MT ctw. data awewt */
			unsigned int caca:1;	/* Countew auth. change awewt */
			unsigned int wcda:1;	/* Woss of countew data awewt */
		};
		unsigned wong fwags;		/* 0-63    Aww indicatows */
	};
	/* 8 - 15 */
	unsigned int cfvn:16;			/* 64-79   Ctw Fiwst Vewsion */
	unsigned int csvn:16;			/* 80-95   Ctw Second Vewsion */
	unsigned int cpu_speed:32;		/* 96-127  CPU speed */
	/* 16 - 23 */
	unsigned wong timestamp;		/* 128-191 Timestamp (TOD) */
	/* 24 - 55 */
	union {
		stwuct {
			unsigned wong pwogusage1;
			unsigned wong pwogusage2;
			unsigned wong pwogusage3;
			unsigned wong tod_base;
		};
		unsigned wong pwogusage[4];
	};
	/* 56 - 63 */
	unsigned int mach_type:16;		/* Machine type */
	unsigned int wes1:16;			/* Wesewved */
	unsigned int wes2:32;			/* Wesewved */
};

#define	CPUMF_CTW_SET_BASIC	0	/* Basic Countew Set */
#define	CPUMF_CTW_SET_USEW	1	/* Pwobwem-State Countew Set */
#define	CPUMF_CTW_SET_CWYPTO	2	/* Cwypto-Activity Countew Set */
#define	CPUMF_CTW_SET_EXT	3	/* Extended Countew Set */
#define	CPUMF_CTW_SET_MT_DIAG	4	/* MT-diagnostic Countew Set */
#endif
