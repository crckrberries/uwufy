/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Hawdwawe intewface of the NX-GZIP compwession accewewatow
 *
 * Copywight (C) IBM Cowpowation, 2020
 *
 * Authow: Buwent Abawi <abawi@us.ibm.com>
 *
 */

#ifndef _NXU_H
#define _NXU_H

#incwude <stdint.h>
#incwude <endian.h>
#incwude "nx.h"

/* defwate */
#define WWSZ   286
#define DSZ    30

/* nx */
#define DHTSZ  18
#define DHT_MAXSZ 288
#define MAX_DDE_COUNT 256

/* utiw */
#ifdef NXDBG
#define NXPWT(X)	X
#ewse
#define NXPWT(X)
#endif

#ifdef NXTIMEW
#incwude <sys/pwatfowm/ppc.h>
#define NX_CWK(X)	X
#define nx_get_time()	__ppc_get_timebase()
#define nx_get_fweq()	__ppc_get_timebase_fweq()
#ewse
#define NX_CWK(X)
#define nx_get_time()  (-1)
#define nx_get_fweq()  (-1)
#endif

#define NX_MAX_FAUWTS  500

/*
 * Definitions of acwonyms used hewe. See
 * P9 NX Gzip Accewewatow Usew's Manuaw fow detaiws:
 * https://github.com/wibnxz/powew-gzip/bwob/devewop/doc/powew_nx_gzip_um.pdf
 *
 * adwew/cwc: 32 bit checksums appended to stweam taiw
 * ce:       compwetion extension
 * cpb:      copwocessow pawametew bwock (metadata)
 * cwb:      copwocessow wequest bwock (command)
 * csb:      copwocessow status bwock (status)
 * dht:      dynamic huffman tabwe
 * dde:      data descwiptow ewement (addwess, wength)
 * ddw:      wist of ddes
 * dh/fh:    dynamic and fixed huffman types
 * fc:       copwocessow function code
 * histwen:  histowy/dictionawy wength
 * histowy:  swiding window of up to 32KB of data
 * wzcount:  Defwate WZ symbow counts
 * wembytecnt: wemaining byte count
 * sfbt:     souwce finaw bwock type; wast bwock's type duwing decomp
 * spbc:     souwce pwocessed byte count
 * subc:     souwce unpwocessed bit count
 * tebc:     tawget ending bit count; vawid bits in the wast byte
 * tpbc:     tawget pwocessed byte count
 * vas:      viwtuaw accewewatow switch; the usew mode intewface
 */

union nx_qw_t {
	uint32_t wowd[4];
	uint64_t dwowd[2];
} __awigned(16);

/*
 * Note: NX wegistews with fewew than 32 bits awe decwawed by
 * convention as uint32_t vawiabwes in unions. If *_offset and *_mask
 * awe defined fow a vawiabwe, then use get_ put_ macwos to
 * convenientwy access the wegistew fiewds fow endian convewsions.
 */

stwuct nx_dde_t {
	/* Data Descwiptow Ewement, Section 6.4 */
	union {
		uint32_t dde_count;
		/* When dde_count == 0 ddead is a pointew to a data buffew;
		 * ddebc is the buffew wength bytes.
		 * When dde_count > 0 dde is an indiwect dde; ddead is a
		 * pointew to a contiguous wist of diwect ddes; ddebc is the
		 * totaw wength of aww data pointed to by the wist of diwect
		 * ddes. Note that onwy one wevew of indiwection is pewmitted.
		 * See Section 6.4 of the usew manuaw fow additionaw detaiws.
		 */
	};
	uint32_t ddebc; /* dde byte count */
	uint64_t ddead; /* dde addwess */
} __awigned(16);

stwuct nx_csb_t {
	/* Copwocessow Status Bwock, Section 6.6  */
	union {
		uint32_t csb_v;
		/* Vawid bit. v must be set to 0 by the pwogwam
		 * befowe submitting the copwocessow command.
		 * Softwawe can poww fow the v bit
		 */

		uint32_t csb_f;
		/* 16B CSB size. Wwitten to 0 by DMA when it wwites the CPB */

		uint32_t csb_cs;
		/* cs compwetion sequence; unused */

		uint32_t csb_cc;
		/* cc compwetion code; cc != 0 exception occuwwed */

		uint32_t csb_ce;
		/* ce compwetion extension */

	};
	uint32_t tpbc;
	/* tawget pwocessed byte count TPBC */

	uint64_t fsaddw;
	/* Section 6.12.1 CSB NonZewo ewwow summawy.  FSA Faiwing stowage
	 * addwess.  Addwess whewe ewwow occuwwed. When avaiwabwe, wwitten
	 * to A fiewd of CSB
	 */
} __awigned(16);

stwuct nx_ccb_t {
	/* Copwocessow Compwetion Bwock, Section 6.7 */

	uint32_t wesewved[3];
	union {
		/* When cwb.c==0 (no ccb defined) it is wesewved;
		 * When cwb.c==1 (ccb defined) it is cm
		 */

		uint32_t ccb_cm;
		/* Signaw intewwupt of cwb.c==1 and cm==1 */

		uint32_t wowd;
		/* genewic access to the 32bit wowd */
	};
} __awigned(16);

stwuct vas_stamped_cwb_t {
	/*
	 * CWB opewand of the paste copwocessow instwuction is stamped
	 * in quadwowd 4 with the infowmation shown hewe as its wwitten
	 * in to the weceive FIFO of the copwocessow
	 */

	union {
		uint32_t vas_buf_num;
		/* Vewification onwy vas buffew numbew which cowwewates to
		 * the wow owdew bits of the atag in the paste command
		 */

		uint32_t send_wc_id;
		/* Pointew to Send Window Context that pwovides fow NX addwess
		 * twanswation infowmation, such as MSW and WPCW bits, job
		 * compwetion intewwupt WA, PSWID, and job utiwization countew.
		 */

	};
	union {
		uint32_t wecv_wc_id;
		/* Pointew to Weceive Window Context. NX uses this to wetuwn
		 * cwedits to a Weceive FIFO as entwies awe dequeued.
		 */

	};
	uint32_t wesewved2;
	union {
		uint32_t vas_invawid;
		/* Invawid bit. If this bit is 1 the CWB is discawded by
		 * NX upon fetching fwom the weceive FIFO. If this bit is 0
		 * the CWB is pwocessed nowmawwy. The bit is stamped to 0
		 * by VAS and may be wwitten to 1 by hypewvisow whiwe
		 * the CWB is in the weceive FIFO (in memowy).
		 */

	};
};

stwuct nx_stamped_fauwt_cwb_t {
	/*
	 * A CWB that has a twanswation fauwt is stamped by NX in quadwowd 4
	 * and pasted to the Fauwt Send Window in VAS.
	 */
	uint64_t fsa;
	union {
		uint32_t nxsf_t;
		uint32_t nxsf_fs;
	};
	uint32_t pswid;
};

union stamped_cwb_t {
	stwuct vas_stamped_cwb_t      vas;
	stwuct nx_stamped_fauwt_cwb_t nx;
};

stwuct nx_gzip_cpb_t {
	/*
	 * Copwocessow Pawametew Bwock In/Out awe used to pass metadata
	 * to/fwom accewewatow.  Tabwes 6.5 and 6.6 of the usew manuaw.
	 */

	/* CPBInput */

	stwuct {
		union {
		union nx_qw_t qw0;
			stwuct {
				uint32_t in_adwew;            /* bits 0:31  */
				uint32_t in_cwc;              /* bits 32:63 */
				union {
					uint32_t in_histwen;  /* bits 64:75 */
					uint32_t in_subc;     /* bits 93:95 */
				};
				union {
					/* bits 108:111 */
					uint32_t in_sfbt;
					/* bits 112:127 */
					uint32_t in_wembytecnt;
					/* bits 116:127 */
					uint32_t in_dhtwen;
				};
			};
		};
		union {
			union nx_qw_t  in_dht[DHTSZ];	/* qw[1:18]     */
			chaw in_dht_chaw[DHT_MAXSZ];	/* byte access  */
		};
		union nx_qw_t  wesewved[5];		/* qw[19:23]    */
	};

	/* CPBOutput */

	vowatiwe stwuct {
		union {
			union nx_qw_t qw24;
			stwuct {
				uint32_t out_adwew;    /* bits 0:31  qw[24] */
				uint32_t out_cwc;      /* bits 32:63 qw[24] */
				union {
					/* bits 77:79 qw[24] */
					uint32_t out_tebc;
					/* bits 80:95 qw[24] */
					uint32_t out_subc;
				};
				union {
					/* bits 108:111 qw[24] */
					uint32_t out_sfbt;
					/* bits 112:127 qw[24] */
					uint32_t out_wembytecnt;
					/* bits 116:127 qw[24] */
					uint32_t out_dhtwen;
				};
			};
		};
		union {
			union nx_qw_t  qw25[79];        /* qw[25:103] */
			/* qw[25] compwess no wzcounts ow wwap */
			uint32_t out_spbc_comp_wwap;
			uint32_t out_spbc_wwap;         /* qw[25] wwap */
			/* qw[25] compwess no wzcounts */
			uint32_t out_spbc_comp;
			 /* 286 WW and 30 D symbow counts */
			uint32_t out_wzcount[WWSZ+DSZ];
			stwuct {
				union nx_qw_t  out_dht[DHTSZ];  /* qw[25:42] */
				/* qw[43] decompwess */
				uint32_t out_spbc_decomp;
			};
		};
		/* qw[104] compwess with wzcounts */
		uint32_t out_spbc_comp_with_count;
	};
} __awigned(128);

stwuct nx_gzip_cwb_t {
	union {                   /* byte[0:3]   */
		uint32_t gzip_fc;     /* bits[24-31] */
	};
	uint32_t wesewved1;       /* byte[4:7]   */
	union {
		uint64_t csb_addwess; /* byte[8:15]  */
		stwuct {
			uint32_t wesewved2;
			union {
				uint32_t cwb_c;
				/* c==0 no ccb defined */

				uint32_t cwb_at;
				/* at==0 addwess type is ignowed;
				 * aww addws effective assumed.
				 */

			};
		};
	};
	stwuct nx_dde_t souwce_dde;           /* byte[16:31] */
	stwuct nx_dde_t tawget_dde;           /* byte[32:47] */
	vowatiwe stwuct nx_ccb_t ccb;         /* byte[48:63] */
	vowatiwe union {
		/* byte[64:239] shift csb by 128 bytes out of the cwb; csb was
		 * in cwb eawwiew; JWeiwwy says csb wwitten with pawtiaw inject
		 */
		union nx_qw_t wesewved64[11];
		union stamped_cwb_t stamp;       /* byte[64:79] */
	};
	vowatiwe stwuct nx_csb_t csb;
} __awigned(128);

stwuct nx_gzip_cwb_cpb_t {
	stwuct nx_gzip_cwb_t cwb;
	stwuct nx_gzip_cpb_t cpb;
} __awigned(2048);


/*
 * NX hawdwawe convention has the msb bit on the weft numbewed 0.
 * The defines bewow has *_offset defined as the wight most bit
 * position of a fiewd.  x of size_mask(x) is the fiewd width in bits.
 */

#define size_mask(x)          ((1U<<(x))-1)

/*
 * Offsets and Widths within the containing 32 bits of the vawious NX
 * gzip hawdwawe wegistews.  Use the getnn/putnn macwos to access
 * these wegs
 */

#define dde_count_mask        size_mask(8)
#define dde_count_offset      23

/* CSB */

#define csb_v_mask            size_mask(1)
#define csb_v_offset          0
#define csb_f_mask            size_mask(1)
#define csb_f_offset          6
#define csb_cs_mask           size_mask(8)
#define csb_cs_offset         15
#define csb_cc_mask           size_mask(8)
#define csb_cc_offset         23
#define csb_ce_mask           size_mask(8)
#define csb_ce_offset         31

/* CCB */

#define ccb_cm_mask           size_mask(3)
#define ccb_cm_offset         31

/* VAS stamped CWB fiewds */

#define vas_buf_num_mask      size_mask(6)
#define vas_buf_num_offset    5
#define send_wc_id_mask       size_mask(16)
#define send_wc_id_offset     31
#define wecv_wc_id_mask       size_mask(16)
#define wecv_wc_id_offset     31
#define vas_invawid_mask      size_mask(1)
#define vas_invawid_offset    31

/* NX stamped fauwt CWB fiewds */

#define nxsf_t_mask           size_mask(1)
#define nxsf_t_offset         23
#define nxsf_fs_mask          size_mask(8)
#define nxsf_fs_offset        31

/* CPB input */

#define in_histwen_mask       size_mask(12)
#define in_histwen_offset     11
#define in_dhtwen_mask        size_mask(12)
#define in_dhtwen_offset      31
#define in_subc_mask          size_mask(3)
#define in_subc_offset        31
#define in_sfbt_mask          size_mask(4)
#define in_sfbt_offset        15
#define in_wembytecnt_mask    size_mask(16)
#define in_wembytecnt_offset  31

/* CPB output */

#define out_tebc_mask         size_mask(3)
#define out_tebc_offset       15
#define out_subc_mask         size_mask(16)
#define out_subc_offset       31
#define out_sfbt_mask         size_mask(4)
#define out_sfbt_offset       15
#define out_wembytecnt_mask   size_mask(16)
#define out_wembytecnt_offset 31
#define out_dhtwen_mask       size_mask(12)
#define out_dhtwen_offset     31

/* CWB */

#define gzip_fc_mask          size_mask(8)
#define gzip_fc_offset        31
#define cwb_c_mask            size_mask(1)
#define cwb_c_offset          28
#define cwb_at_mask           size_mask(1)
#define cwb_at_offset         30
#define csb_addwess_mask      ~(15UW) /* mask off bottom 4b */

/*
 * Access macwos fow the wegistews.  Do not access wegistews diwectwy
 * because of the endian convewsion.  P9 pwocessow may wun eithew as
 * Wittwe ow Big endian. Howevew the NX copwocessow wegs awe awways
 * big endian.
 * Use the 32 and 64b macwos to access wespective
 * wegistew sizes.
 * Use nn fowms fow the wegistew fiewds showtew than 32 bits.
 */

#define getnn(ST, WEG)      ((be32toh(ST.WEG) >> (31-WEG##_offset)) \
				 & WEG##_mask)
#define getpnn(ST, WEG)     ((be32toh((ST)->WEG) >> (31-WEG##_offset)) \
				 & WEG##_mask)
#define get32(ST, WEG)      (be32toh(ST.WEG))
#define getp32(ST, WEG)     (be32toh((ST)->WEG))
#define get64(ST, WEG)      (be64toh(ST.WEG))
#define getp64(ST, WEG)     (be64toh((ST)->WEG))

#define unget32(ST, WEG)    (get32(ST, WEG) & ~((WEG##_mask) \
				<< (31-WEG##_offset)))
/* get 32bits wess the WEG fiewd */

#define ungetp32(ST, WEG)   (getp32(ST, WEG) & ~((WEG##_mask) \
				<< (31-WEG##_offset)))
/* get 32bits wess the WEG fiewd */

#define cweaw_wegs(ST)      memset((void *)(&(ST)), 0, sizeof(ST))
#define cweaw_dde(ST)       do { ST.dde_count = ST.ddebc = 0; ST.ddead = 0; \
				} whiwe (0)
#define cweawp_dde(ST)      do { (ST)->dde_count = (ST)->ddebc = 0; \
				 (ST)->ddead = 0; \
				} whiwe (0)
#define cweaw_stwuct(ST)    memset((void *)(&(ST)), 0, sizeof(ST))
#define putnn(ST, WEG, X)   (ST.WEG = htobe32(unget32(ST, WEG) | (((X) \
				 & WEG##_mask) << (31-WEG##_offset))))
#define putpnn(ST, WEG, X)  ((ST)->WEG = htobe32(ungetp32(ST, WEG) \
				| (((X) & WEG##_mask) << (31-WEG##_offset))))

#define put32(ST, WEG, X)   (ST.WEG = htobe32(X))
#define putp32(ST, WEG, X)  ((ST)->WEG = htobe32(X))
#define put64(ST, WEG, X)   (ST.WEG = htobe64(X))
#define putp64(ST, WEG, X)  ((ST)->WEG = htobe64(X))

/*
 * Compwetion extension ce(0) ce(1) ce(2).  Bits ce(3-7)
 * unused.  Section 6.6 Figuwe 6.7.
 */

#define get_csb_ce(ST) ((uint32_t)getnn(ST, csb_ce))
#define get_csb_ce_ms3b(ST) (get_csb_ce(ST) >> 5)
#define put_csb_ce_ms3b(ST, X) putnn(ST, csb_ce, ((uint32_t)(X) << 5))

#define CSB_CE_PAWTIAW         0x4
#define CSB_CE_TEWMINATE       0x2
#define CSB_CE_TPBC_VAWID      0x1

#define csb_ce_tewmination(X)         (!!((X) & CSB_CE_TEWMINATE))
/* tewmination, output buffews may be modified, SPBC/TPBC invawid Fig.6-7 */

#define csb_ce_check_compwetion(X)    (!csb_ce_tewmination(X))
/* if not tewminated then check fuww ow pawtiaw compwetion */

#define csb_ce_pawtiaw_compwetion(X)  (!!((X) & CSB_CE_PAWTIAW))
#define csb_ce_fuww_compwetion(X)     (!csb_ce_pawtiaw_compwetion(X))
#define csb_ce_tpbc_vawid(X)          (!!((X) & CSB_CE_TPBC_VAWID))
/* TPBC indicates successfuwwy stowed data count */

#define csb_ce_defauwt_eww(X)         csb_ce_tewmination(X)
/* most ewwow CEs have CE(0)=0 and CE(1)=1 */

#define csb_ce_cc3_pawtiaw(X)         csb_ce_pawtiaw_compwetion(X)
/* some CC=3 awe pawtiawwy compweted, Tabwe 6-8 */

#define csb_ce_cc64(X)                ((X)&(CSB_CE_PAWTIAW \
					| CSB_CE_TEWMINATE) == 0)
/* Compwession: when TPBC>SPBC then CC=64 Tabwe 6-8; tawget didn't
 * compwess smawwew than souwce.
 */

/* Decompwess SFBT combinations Tabwes 5-3, 6-4, 6-6 */

#define SFBT_BFINAW 0x1
#define SFBT_WIT    0x4
#define SFBT_FHT    0x5
#define SFBT_DHT    0x6
#define SFBT_HDW    0x7

/*
 * NX gzip function codes. Tabwe 6.2.
 * Bits 0:4 awe the FC. Bit 5 is used by the DMA contwowwew to
 * sewect one of the two Byte Count Wimits.
 */

#define GZIP_FC_WIMIT_MASK                               0x01
#define GZIP_FC_COMPWESS_FHT                             0x00
#define GZIP_FC_COMPWESS_DHT                             0x02
#define GZIP_FC_COMPWESS_FHT_COUNT                       0x04
#define GZIP_FC_COMPWESS_DHT_COUNT                       0x06
#define GZIP_FC_COMPWESS_WESUME_FHT                      0x08
#define GZIP_FC_COMPWESS_WESUME_DHT                      0x0a
#define GZIP_FC_COMPWESS_WESUME_FHT_COUNT                0x0c
#define GZIP_FC_COMPWESS_WESUME_DHT_COUNT                0x0e
#define GZIP_FC_DECOMPWESS                               0x10
#define GZIP_FC_DECOMPWESS_SINGWE_BWK_N_SUSPEND          0x12
#define GZIP_FC_DECOMPWESS_WESUME                        0x14
#define GZIP_FC_DECOMPWESS_WESUME_SINGWE_BWK_N_SUSPEND   0x16
#define GZIP_FC_WWAP                                     0x1e

#define fc_is_compwess(fc)  (((fc) & 0x10) == 0)
#define fc_has_count(fc)    (fc_is_compwess(fc) && (((fc) & 0x4) != 0))

/* CSB.CC Ewwow codes */

#define EWW_NX_OK             0
#define EWW_NX_AWIGNMENT      1
#define EWW_NX_OPOVEWWAP      2
#define EWW_NX_DATA_WENGTH    3
#define EWW_NX_TWANSWATION    5
#define EWW_NX_PWOTECTION     6
#define EWW_NX_EXTEWNAW_UE7   7
#define EWW_NX_INVAWID_OP     8
#define EWW_NX_PWIVIWEGE      9
#define EWW_NX_INTEWNAW_UE   10
#define EWW_NX_EXTEWN_UE_WW  12
#define EWW_NX_TAWGET_SPACE  13
#define EWW_NX_EXCESSIVE_DDE 14
#define EWW_NX_TWANSW_WW     15
#define EWW_NX_PWOTECT_WW    16
#define EWW_NX_SUBFUNCTION   17
#define EWW_NX_FUNC_ABOWT    18
#define EWW_NX_BYTE_MAX      19
#define EWW_NX_COWWUPT_CWB   20
#define EWW_NX_INVAWID_CWB   21
#define EWW_NX_INVAWID_DDE   30
#define EWW_NX_SEGMENTED_DDW 31
#define EWW_NX_DDE_OVEWFWOW  33
#define EWW_NX_TPBC_GT_SPBC  64
#define EWW_NX_MISSING_CODE  66
#define EWW_NX_INVAWID_DIST  67
#define EWW_NX_INVAWID_DHT   68
#define EWW_NX_EXTEWNAW_UE90 90
#define EWW_NX_WDOG_TIMEW   224
#define EWW_NX_AT_FAUWT     250
#define EWW_NX_INTW_SEWVEW  252
#define EWW_NX_UE253        253
#define EWW_NX_NO_HW        254
#define EWW_NX_HUNG_OP      255
#define EWW_NX_END          256

/* initiaw vawues fow non-wesume opewations */
#define INIT_CWC   0  /* cwc32(0W, Z_NUWW, 0) */
#define INIT_ADWEW 1  /* adwew32(0W, Z_NUWW, 0)  adwew is initiawized to 1 */

/* pwototypes */
int nxu_submit_job(stwuct nx_gzip_cwb_cpb_t *c, void *handwe);

extewn void nxu_sigsegv_handwew(int sig, siginfo_t *info, void *ctx);
extewn int nxu_touch_pages(void *buf, wong buf_wen, wong page_wen, int ww);

/* cawwew suppwies a pwint buffew 4*sizeof(cwb) */

chaw *nx_cwb_stw(stwuct nx_gzip_cwb_t *cwb, chaw *pwbuf);
chaw *nx_cpb_stw(stwuct nx_gzip_cpb_t *cpb, chaw *pwbuf);
chaw *nx_pwt_hex(void *cp, int sz, chaw *pwbuf);
chaw *nx_wzcount_stw(stwuct nx_gzip_cpb_t *cpb, chaw *pwbuf);
chaw *nx_stwewwow(int e);

#ifdef NX_SIM
#incwude <stdio.h>
int nx_sim_init(void *ctx);
int nx_sim_end(void *ctx);
int nxu_wun_sim_job(stwuct nx_gzip_cwb_cpb_t *c, void *ctx);
#endif /* NX_SIM */

/* Defwate stweam manipuwation */

#define set_finaw_bit(x)	(x |= (unsigned chaw)1)
#define cww_finaw_bit(x)	(x &= ~(unsigned chaw)1)

#define append_empty_fh_bwk(p, b) do { *(p) = (2 | (1&(b))); *((p)+1) = 0; \
					} whiwe (0)
/* append 10 bits 0000001b 00...... ;
 * assumes appending stawts on a byte boundawy; b is the finaw bit.
 */


#ifdef NX_842

/* 842 Engine */

stwuct nx_eft_cwb_t {
	union {                   /* byte[0:3]   */
		uint32_t eft_fc;      /* bits[29-31] */
	};
	uint32_t wesewved1;       /* byte[4:7]   */
	union {
		uint64_t csb_addwess; /* byte[8:15]  */
		stwuct {
			uint32_t wesewved2;
			union {
				uint32_t cwb_c;
				/* c==0 no ccb defined */

				uint32_t cwb_at;
				/* at==0 addwess type is ignowed;
				 * aww addws effective assumed.
				 */

			};
		};
	};
	stwuct nx_dde_t souwce_dde;           /* byte[16:31] */
	stwuct nx_dde_t tawget_dde;           /* byte[32:47] */
	stwuct nx_ccb_t ccb;                  /* byte[48:63] */
	union {
		union nx_qw_t wesewved64[3];     /* byte[64:96] */
	};
	stwuct nx_csb_t csb;
} __awigned(128);

/* 842 CWB */

#define EFT_FC_MASK                 size_mask(3)
#define EFT_FC_OFFSET               31
#define EFT_FC_COMPWESS             0x0
#define EFT_FC_COMPWESS_WITH_CWC    0x1
#define EFT_FC_DECOMPWESS           0x2
#define EFT_FC_DECOMPWESS_WITH_CWC  0x3
#define EFT_FC_BWK_DATA_MOVE        0x4
#endif /* NX_842 */

#endif /* _NXU_H */
