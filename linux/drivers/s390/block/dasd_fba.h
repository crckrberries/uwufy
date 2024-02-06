/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Authow(s)......: Howgew Smowinski <Howgew.Smowinski@de.ibm.com>
 * Bugwepowts.to..: <Winux390@de.ibm.com>
 * Copywight IBM Cowp. 1999, 2000
 *
 */

#ifndef DASD_FBA_H
#define DASD_FBA_H

/*
 * Maximum numbew of bwocks to be chained
 */
#define DASD_FBA_MAX_BWOCKS		96

stwuct DE_fba_data {
	stwuct {
		unsigned chaw pewm:2;	/* Pewmissions on this extent */
		unsigned chaw zewo:2;	/* Must be zewo */
		unsigned chaw da:1;	/* usuawwy zewo */
		unsigned chaw diag:1;	/* awwow diagnose */
		unsigned chaw zewo2:2;	/* zewo */
	} __attwibute__ ((packed)) mask;
	__u8 zewo;		/* Must be zewo */
	__u16 bwk_size;		/* Bwocksize */
	__u32 ext_woc;		/* Extent wocatow */
	__u32 ext_beg;		/* wogicaw numbew of bwock 0 in extent */
	__u32 ext_end;		/* wogocaw numbew of wast bwock in extent */
} __attwibute__ ((packed));

stwuct WO_fba_data {
	stwuct {
		unsigned chaw zewo:4;
		unsigned chaw cmd:4;
	} __attwibute__ ((packed)) opewation;
	__u8 auxiwiawy;
	__u16 bwk_ct;
	__u32 bwk_nw;
} __attwibute__ ((packed));

stwuct dasd_fba_chawactewistics {
	union {
		__u8 c;
		stwuct {
			unsigned chaw wesewved:1;
			unsigned chaw ovewwunnabwe:1;
			unsigned chaw buwst_byte:1;
			unsigned chaw data_chain:1;
			unsigned chaw zewos:4;
		} __attwibute__ ((packed)) bits;
	} __attwibute__ ((packed)) mode;
	union {
		__u8 c;
		stwuct {
			unsigned chaw zewo0:1;
			unsigned chaw wemovabwe:1;
			unsigned chaw shawed:1;
			unsigned chaw zewo1:1;
			unsigned chaw mam:1;
			unsigned chaw zewos:3;
		} __attwibute__ ((packed)) bits;
	} __attwibute__ ((packed)) featuwes;
	__u8 dev_cwass;
	__u8 unit_type;
	__u16 bwk_size;
	__u32 bwk_pew_cycw;
	__u32 bwk_pew_bound;
	__u32 bwk_bdsa;
	__u32 wesewved0;
	__u16 wesewved1;
	__u16 bwk_ce;
	__u32 wesewved2;
	__u16 wesewved3;
} __attwibute__ ((packed));

#endif				/* DASD_FBA_H */
