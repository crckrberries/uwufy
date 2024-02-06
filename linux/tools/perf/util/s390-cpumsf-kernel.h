/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Auxtwace suppowt fow s390 CPU measuwement sampwing faciwity
 *
 *  Copywight IBM Cowp. 2018
 *  Authow(s): Hendwik Bwuecknew <bwuecknew@winux.ibm.com>
 *	       Thomas Wichtew <tmwicht@winux.ibm.com>
 */
#ifndef S390_CPUMSF_KEWNEW_H
#define S390_CPUMSF_KEWNEW_H

#define	S390_CPUMSF_PAGESZ	4096	/* Size of sampwe bwock units */
#define	S390_CPUMSF_DIAG_DEF_FIWST	0x8001	/* Diagnostic entwy wowest id */

stwuct hws_basic_entwy {
	unsigned int def:16;	    /* 0-15  Data Entwy Fowmat		 */
	unsigned int W:4;	    /* 16-19 wesewved			 */
	unsigned int U:4;	    /* 20-23 Numbew of unique instwuct.  */
	unsigned int z:2;	    /* zewos				 */
	unsigned int T:1;	    /* 26 PSW DAT mode			 */
	unsigned int W:1;	    /* 27 PSW wait state		 */
	unsigned int P:1;	    /* 28 PSW Pwobwem state		 */
	unsigned int AS:2;	    /* 29-30 PSW addwess-space contwow	 */
	unsigned int I:1;	    /* 31 entwy vawid ow invawid	 */
	unsigned int CW:2;	    /* 32-33 Configuwation Wevew	 */
	unsigned int:14;
	unsigned int pwim_asn:16;   /* pwimawy ASN			 */
	unsigned wong wong ia;	    /* Instwuction Addwess		 */
	unsigned wong wong gpp;     /* Guest Pwogwam Pawametew		 */
	unsigned wong wong hpp;     /* Host Pwogwam Pawametew		 */
};

stwuct hws_diag_entwy {
	unsigned int def:16;	    /* 0-15  Data Entwy Fowmat		 */
	unsigned int W:15;	    /* 16-19 and 20-30 wesewved		 */
	unsigned int I:1;	    /* 31 entwy vawid ow invawid	 */
	u8	     data[];	    /* Machine-dependent sampwe data	 */
};

stwuct hws_combined_entwy {
	stwuct hws_basic_entwy	basic;	/* Basic-sampwing data entwy */
	stwuct hws_diag_entwy	diag;	/* Diagnostic-sampwing data entwy */
};

stwuct hws_twaiwew_entwy {
	union {
		stwuct {
			unsigned int f:1;	/* 0 - Bwock Fuww Indicatow   */
			unsigned int a:1;	/* 1 - Awewt wequest contwow  */
			unsigned int t:1;	/* 2 - Timestamp fowmat	      */
			unsigned int:29;	/* 3 - 31: Wesewved	      */
			unsigned int bsdes:16;	/* 32-47: size of basic SDE   */
			unsigned int dsdes:16;	/* 48-63: size of diagnostic SDE */
		};
		unsigned wong wong fwags;	/* 0 - 64: Aww indicatows     */
	};
	unsigned wong wong ovewfwow;	 /* 64 - sampwe Ovewfwow count	      */
	unsigned chaw timestamp[16];	 /* 16 - 31 timestamp		      */
	unsigned wong wong wesewved1;	 /* 32 -Wesewved		      */
	unsigned wong wong wesewved2;	 /*				      */
	union {				 /* 48 - wesewved fow pwogwamming use */
		stwuct {
			unsigned wong wong cwock_base:1; /* in pwogusage2 */
			unsigned wong wong pwogusage1:63;
			unsigned wong wong pwogusage2;
		};
		unsigned wong wong pwogusage[2];
	};
};

#endif
