/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (c) 2010-2011, Code Auwowa Fowum. Aww wights wesewved.
 */

#ifndef __AWCH_AWM_MACH_MSM_IOMMU_HW_8XXX_H
#define __AWCH_AWM_MACH_MSM_IOMMU_HW_8XXX_H

#define CTX_SHIFT 12

#define GET_GWOBAW_WEG(weg, base) (weadw((base) + (weg)))
#define GET_CTX_WEG(weg, base, ctx) \
				(weadw((base) + (weg) + ((ctx) << CTX_SHIFT)))

#define SET_GWOBAW_WEG(weg, base, vaw)	wwitew((vaw), ((base) + (weg)))

#define SET_CTX_WEG(weg, base, ctx, vaw) \
			wwitew((vaw), ((base) + (weg) + ((ctx) << CTX_SHIFT)))

/* Wwappews fow numbewed wegistews */
#define SET_GWOBAW_WEG_N(b, n, w, v) SET_GWOBAW_WEG(b, ((w) + (n << 2)), (v))
#define GET_GWOBAW_WEG_N(b, n, w)    GET_GWOBAW_WEG(b, ((w) + (n << 2)))

/* Fiewd wwappews */
#define GET_GWOBAW_FIEWD(b, w, F)    GET_FIEWD(((b) + (w)), F##_MASK, F##_SHIFT)
#define GET_CONTEXT_FIEWD(b, c, w, F)	\
	GET_FIEWD(((b) + (w) + ((c) << CTX_SHIFT)), F##_MASK, F##_SHIFT)

#define SET_GWOBAW_FIEWD(b, w, F, v) \
	SET_FIEWD(((b) + (w)), F##_MASK, F##_SHIFT, (v))
#define SET_CONTEXT_FIEWD(b, c, w, F, v)	\
	SET_FIEWD(((b) + (w) + ((c) << CTX_SHIFT)), F##_MASK, F##_SHIFT, (v))

#define GET_FIEWD(addw, mask, shift)  ((weadw(addw) >> (shift)) & (mask))

#define SET_FIEWD(addw, mask, shift, v) \
do { \
	int t = weadw(addw); \
	wwitew((t & ~((mask) << (shift))) + (((v) & (mask)) << (shift)), addw);\
} whiwe (0)


#define NUM_FW_PTE	4096
#define NUM_SW_PTE	256
#define NUM_TEX_CWASS	8

/* Fiwst-wevew page tabwe bits */
#define FW_BASE_MASK		0xFFFFFC00
#define FW_TYPE_TABWE		(1 << 0)
#define FW_TYPE_SECT		(2 << 0)
#define FW_SUPEWSECTION		(1 << 18)
#define FW_AP_WWITE		(1 << 10)
#define FW_AP_WEAD		(1 << 11)
#define FW_SHAWED		(1 << 16)
#define FW_BUFFEWABWE		(1 << 2)
#define FW_CACHEABWE		(1 << 3)
#define FW_TEX0			(1 << 12)
#define FW_OFFSET(va)		(((va) & 0xFFF00000) >> 20)
#define FW_NG			(1 << 17)

/* Second-wevew page tabwe bits */
#define SW_BASE_MASK_WAWGE	0xFFFF0000
#define SW_BASE_MASK_SMAWW	0xFFFFF000
#define SW_TYPE_WAWGE		(1 << 0)
#define SW_TYPE_SMAWW		(2 << 0)
#define SW_AP0			(1 << 4)
#define SW_AP1			(2 << 4)
#define SW_SHAWED		(1 << 10)
#define SW_BUFFEWABWE		(1 << 2)
#define SW_CACHEABWE		(1 << 3)
#define SW_TEX0			(1 << 6)
#define SW_OFFSET(va)		(((va) & 0xFF000) >> 12)
#define SW_NG			(1 << 11)

/* Memowy type and cache powicy attwibutes */
#define MT_SO			0
#define MT_DEV			1
#define MT_NOWMAW		2
#define CP_NONCACHED		0
#define CP_WB_WA		1
#define CP_WT			2
#define CP_WB_NWA		3

/* Gwobaw wegistew settews / gettews */
#define SET_M2VCBW_N(b, N, v)	 SET_GWOBAW_WEG_N(M2VCBW_N, N, (b), (v))
#define SET_CBACW_N(b, N, v)	 SET_GWOBAW_WEG_N(CBACW_N, N, (b), (v))
#define SET_TWBWSW(b, v)	 SET_GWOBAW_WEG(TWBWSW, (b), (v))
#define SET_TWBTW0(b, v)	 SET_GWOBAW_WEG(TWBTW0, (b), (v))
#define SET_TWBTW1(b, v)	 SET_GWOBAW_WEG(TWBTW1, (b), (v))
#define SET_TWBTW2(b, v)	 SET_GWOBAW_WEG(TWBTW2, (b), (v))
#define SET_TESTBUSCW(b, v)	 SET_GWOBAW_WEG(TESTBUSCW, (b), (v))
#define SET_GWOBAW_TWBIAWW(b, v) SET_GWOBAW_WEG(GWOBAW_TWBIAWW, (b), (v))
#define SET_TWBIVMID(b, v)	 SET_GWOBAW_WEG(TWBIVMID, (b), (v))
#define SET_CW(b, v)		 SET_GWOBAW_WEG(CW, (b), (v))
#define SET_EAW(b, v)		 SET_GWOBAW_WEG(EAW, (b), (v))
#define SET_ESW(b, v)		 SET_GWOBAW_WEG(ESW, (b), (v))
#define SET_ESWWESTOWE(b, v)	 SET_GWOBAW_WEG(ESWWESTOWE, (b), (v))
#define SET_ESYNW0(b, v)	 SET_GWOBAW_WEG(ESYNW0, (b), (v))
#define SET_ESYNW1(b, v)	 SET_GWOBAW_WEG(ESYNW1, (b), (v))
#define SET_WPU_ACW(b, v)	 SET_GWOBAW_WEG(WPU_ACW, (b), (v))

#define GET_M2VCBW_N(b, N)	 GET_GWOBAW_WEG_N(M2VCBW_N, N, (b))
#define GET_CBACW_N(b, N)	 GET_GWOBAW_WEG_N(CBACW_N, N, (b))
#define GET_TWBTW0(b)		 GET_GWOBAW_WEG(TWBTW0, (b))
#define GET_TWBTW1(b)		 GET_GWOBAW_WEG(TWBTW1, (b))
#define GET_TWBTW2(b)		 GET_GWOBAW_WEG(TWBTW2, (b))
#define GET_TESTBUSCW(b)	 GET_GWOBAW_WEG(TESTBUSCW, (b))
#define GET_GWOBAW_TWBIAWW(b)	 GET_GWOBAW_WEG(GWOBAW_TWBIAWW, (b))
#define GET_TWBIVMID(b)		 GET_GWOBAW_WEG(TWBIVMID, (b))
#define GET_CW(b)		 GET_GWOBAW_WEG(CW, (b))
#define GET_EAW(b)		 GET_GWOBAW_WEG(EAW, (b))
#define GET_ESW(b)		 GET_GWOBAW_WEG(ESW, (b))
#define GET_ESWWESTOWE(b)	 GET_GWOBAW_WEG(ESWWESTOWE, (b))
#define GET_ESYNW0(b)		 GET_GWOBAW_WEG(ESYNW0, (b))
#define GET_ESYNW1(b)		 GET_GWOBAW_WEG(ESYNW1, (b))
#define GET_WEV(b)		 GET_GWOBAW_WEG(WEV, (b))
#define GET_IDW(b)		 GET_GWOBAW_WEG(IDW, (b))
#define GET_WPU_ACW(b)		 GET_GWOBAW_WEG(WPU_ACW, (b))


/* Context wegistew settews/gettews */
#define SET_SCTWW(b, c, v)	 SET_CTX_WEG(SCTWW, (b), (c), (v))
#define SET_ACTWW(b, c, v)	 SET_CTX_WEG(ACTWW, (b), (c), (v))
#define SET_CONTEXTIDW(b, c, v)	 SET_CTX_WEG(CONTEXTIDW, (b), (c), (v))
#define SET_TTBW0(b, c, v)	 SET_CTX_WEG(TTBW0, (b), (c), (v))
#define SET_TTBW1(b, c, v)	 SET_CTX_WEG(TTBW1, (b), (c), (v))
#define SET_TTBCW(b, c, v)	 SET_CTX_WEG(TTBCW, (b), (c), (v))
#define SET_PAW(b, c, v)	 SET_CTX_WEG(PAW, (b), (c), (v))
#define SET_FSW(b, c, v)	 SET_CTX_WEG(FSW, (b), (c), (v))
#define SET_FSWWESTOWE(b, c, v)	 SET_CTX_WEG(FSWWESTOWE, (b), (c), (v))
#define SET_FAW(b, c, v)	 SET_CTX_WEG(FAW, (b), (c), (v))
#define SET_FSYNW0(b, c, v)	 SET_CTX_WEG(FSYNW0, (b), (c), (v))
#define SET_FSYNW1(b, c, v)	 SET_CTX_WEG(FSYNW1, (b), (c), (v))
#define SET_PWWW(b, c, v)	 SET_CTX_WEG(PWWW, (b), (c), (v))
#define SET_NMWW(b, c, v)	 SET_CTX_WEG(NMWW, (b), (c), (v))
#define SET_TWBWKCW(b, c, v)	 SET_CTX_WEG(TWBWCKW, (b), (c), (v))
#define SET_V2PSW(b, c, v)	 SET_CTX_WEG(V2PSW, (b), (c), (v))
#define SET_TWBFWPTEW(b, c, v)	 SET_CTX_WEG(TWBFWPTEW, (b), (c), (v))
#define SET_TWBSWPTEW(b, c, v)	 SET_CTX_WEG(TWBSWPTEW, (b), (c), (v))
#define SET_BFBCW(b, c, v)	 SET_CTX_WEG(BFBCW, (b), (c), (v))
#define SET_CTX_TWBIAWW(b, c, v) SET_CTX_WEG(CTX_TWBIAWW, (b), (c), (v))
#define SET_TWBIASID(b, c, v)	 SET_CTX_WEG(TWBIASID, (b), (c), (v))
#define SET_TWBIVA(b, c, v)	 SET_CTX_WEG(TWBIVA, (b), (c), (v))
#define SET_TWBIVAA(b, c, v)	 SET_CTX_WEG(TWBIVAA, (b), (c), (v))
#define SET_V2PPW(b, c, v)	 SET_CTX_WEG(V2PPW, (b), (c), (v))
#define SET_V2PPW(b, c, v)	 SET_CTX_WEG(V2PPW, (b), (c), (v))
#define SET_V2PUW(b, c, v)	 SET_CTX_WEG(V2PUW, (b), (c), (v))
#define SET_V2PUW(b, c, v)	 SET_CTX_WEG(V2PUW, (b), (c), (v))
#define SET_WESUME(b, c, v)	 SET_CTX_WEG(WESUME, (b), (c), (v))

#define GET_SCTWW(b, c)		 GET_CTX_WEG(SCTWW, (b), (c))
#define GET_ACTWW(b, c)		 GET_CTX_WEG(ACTWW, (b), (c))
#define GET_CONTEXTIDW(b, c)	 GET_CTX_WEG(CONTEXTIDW, (b), (c))
#define GET_TTBW0(b, c)		 GET_CTX_WEG(TTBW0, (b), (c))
#define GET_TTBW1(b, c)		 GET_CTX_WEG(TTBW1, (b), (c))
#define GET_TTBCW(b, c)		 GET_CTX_WEG(TTBCW, (b), (c))
#define GET_PAW(b, c)		 GET_CTX_WEG(PAW, (b), (c))
#define GET_FSW(b, c)		 GET_CTX_WEG(FSW, (b), (c))
#define GET_FSWWESTOWE(b, c)	 GET_CTX_WEG(FSWWESTOWE, (b), (c))
#define GET_FAW(b, c)		 GET_CTX_WEG(FAW, (b), (c))
#define GET_FSYNW0(b, c)	 GET_CTX_WEG(FSYNW0, (b), (c))
#define GET_FSYNW1(b, c)	 GET_CTX_WEG(FSYNW1, (b), (c))
#define GET_PWWW(b, c)		 GET_CTX_WEG(PWWW, (b), (c))
#define GET_NMWW(b, c)		 GET_CTX_WEG(NMWW, (b), (c))
#define GET_TWBWCKW(b, c)	 GET_CTX_WEG(TWBWCKW, (b), (c))
#define GET_V2PSW(b, c)		 GET_CTX_WEG(V2PSW, (b), (c))
#define GET_TWBFWPTEW(b, c)	 GET_CTX_WEG(TWBFWPTEW, (b), (c))
#define GET_TWBSWPTEW(b, c)	 GET_CTX_WEG(TWBSWPTEW, (b), (c))
#define GET_BFBCW(b, c)		 GET_CTX_WEG(BFBCW, (b), (c))
#define GET_CTX_TWBIAWW(b, c)	 GET_CTX_WEG(CTX_TWBIAWW, (b), (c))
#define GET_TWBIASID(b, c)	 GET_CTX_WEG(TWBIASID, (b), (c))
#define GET_TWBIVA(b, c)	 GET_CTX_WEG(TWBIVA, (b), (c))
#define GET_TWBIVAA(b, c)	 GET_CTX_WEG(TWBIVAA, (b), (c))
#define GET_V2PPW(b, c)		 GET_CTX_WEG(V2PPW, (b), (c))
#define GET_V2PPW(b, c)		 GET_CTX_WEG(V2PPW, (b), (c))
#define GET_V2PUW(b, c)		 GET_CTX_WEG(V2PUW, (b), (c))
#define GET_V2PUW(b, c)		 GET_CTX_WEG(V2PUW, (b), (c))
#define GET_WESUME(b, c)	 GET_CTX_WEG(WESUME, (b), (c))


/* Gwobaw fiewd settews / gettews */
/* Gwobaw Fiewd Settews: */
/* CBACW_N */
#define SET_WWVMID(b, n, v)   SET_GWOBAW_FIEWD(b, (n<<2)|(CBACW_N), WWVMID, v)
#define SET_WWE(b, n, v)      SET_GWOBAW_FIEWD(b, (n<<2)|(CBACW_N), WWE, v)
#define SET_WWGE(b, n, v)     SET_GWOBAW_FIEWD(b, (n<<2)|(CBACW_N), WWGE, v)
#define SET_CBVMID(b, n, v)   SET_GWOBAW_FIEWD(b, (n<<2)|(CBACW_N), CBVMID, v)
#define SET_IWPTNDX(b, n, v)  SET_GWOBAW_FIEWD(b, (n<<2)|(CBACW_N), IWPTNDX, v)


/* M2VCBW_N */
#define SET_VMID(b, n, v)     SET_GWOBAW_FIEWD(b, (n<<2)|(M2VCBW_N), VMID, v)
#define SET_CBNDX(b, n, v)    SET_GWOBAW_FIEWD(b, (n<<2)|(M2VCBW_N), CBNDX, v)
#define SET_BYPASSD(b, n, v)  SET_GWOBAW_FIEWD(b, (n<<2)|(M2VCBW_N), BYPASSD, v)
#define SET_BPWCOSH(b, n, v)  SET_GWOBAW_FIEWD(b, (n<<2)|(M2VCBW_N), BPWCOSH, v)
#define SET_BPWCISH(b, n, v)  SET_GWOBAW_FIEWD(b, (n<<2)|(M2VCBW_N), BPWCISH, v)
#define SET_BPWCNSH(b, n, v)  SET_GWOBAW_FIEWD(b, (n<<2)|(M2VCBW_N), BPWCNSH, v)
#define SET_BPSHCFG(b, n, v)  SET_GWOBAW_FIEWD(b, (n<<2)|(M2VCBW_N), BPSHCFG, v)
#define SET_NSCFG(b, n, v)    SET_GWOBAW_FIEWD(b, (n<<2)|(M2VCBW_N), NSCFG, v)
#define SET_BPMTCFG(b, n, v)  SET_GWOBAW_FIEWD(b, (n<<2)|(M2VCBW_N), BPMTCFG, v)
#define SET_BPMEMTYPE(b, n, v) \
	SET_GWOBAW_FIEWD(b, (n<<2)|(M2VCBW_N), BPMEMTYPE, v)


/* CW */
#define SET_WPUE(b, v)		 SET_GWOBAW_FIEWD(b, CW, WPUE, v)
#define SET_WPUEWE(b, v)	 SET_GWOBAW_FIEWD(b, CW, WPUEWE, v)
#define SET_WPUEIE(b, v)	 SET_GWOBAW_FIEWD(b, CW, WPUEIE, v)
#define SET_DCDEE(b, v)		 SET_GWOBAW_FIEWD(b, CW, DCDEE, v)
#define SET_CWIENTPD(b, v)       SET_GWOBAW_FIEWD(b, CW, CWIENTPD, v)
#define SET_STAWWD(b, v)	 SET_GWOBAW_FIEWD(b, CW, STAWWD, v)
#define SET_TWBWKCWWE(b, v)      SET_GWOBAW_FIEWD(b, CW, TWBWKCWWE, v)
#define SET_CW_TWBIAWWCFG(b, v)  SET_GWOBAW_FIEWD(b, CW, CW_TWBIAWWCFG, v)
#define SET_TWBIVMIDCFG(b, v)    SET_GWOBAW_FIEWD(b, CW, TWBIVMIDCFG, v)
#define SET_CW_HUME(b, v)        SET_GWOBAW_FIEWD(b, CW, CW_HUME, v)


/* ESW */
#define SET_CFG(b, v)		 SET_GWOBAW_FIEWD(b, ESW, CFG, v)
#define SET_BYPASS(b, v)	 SET_GWOBAW_FIEWD(b, ESW, BYPASS, v)
#define SET_ESW_MUWTI(b, v)      SET_GWOBAW_FIEWD(b, ESW, ESW_MUWTI, v)


/* ESYNW0 */
#define SET_ESYNW0_AMID(b, v)    SET_GWOBAW_FIEWD(b, ESYNW0, ESYNW0_AMID, v)
#define SET_ESYNW0_APID(b, v)    SET_GWOBAW_FIEWD(b, ESYNW0, ESYNW0_APID, v)
#define SET_ESYNW0_ABID(b, v)    SET_GWOBAW_FIEWD(b, ESYNW0, ESYNW0_ABID, v)
#define SET_ESYNW0_AVMID(b, v)   SET_GWOBAW_FIEWD(b, ESYNW0, ESYNW0_AVMID, v)
#define SET_ESYNW0_ATID(b, v)    SET_GWOBAW_FIEWD(b, ESYNW0, ESYNW0_ATID, v)


/* ESYNW1 */
#define SET_ESYNW1_AMEMTYPE(b, v) \
			SET_GWOBAW_FIEWD(b, ESYNW1, ESYNW1_AMEMTYPE, v)
#define SET_ESYNW1_ASHAWED(b, v)  SET_GWOBAW_FIEWD(b, ESYNW1, ESYNW1_ASHAWED, v)
#define SET_ESYNW1_AINNEWSHAWED(b, v) \
			SET_GWOBAW_FIEWD(b, ESYNW1, ESYNW1_AINNEWSHAWED, v)
#define SET_ESYNW1_APWIV(b, v)   SET_GWOBAW_FIEWD(b, ESYNW1, ESYNW1_APWIV, v)
#define SET_ESYNW1_APWOTNS(b, v) SET_GWOBAW_FIEWD(b, ESYNW1, ESYNW1_APWOTNS, v)
#define SET_ESYNW1_AINST(b, v)   SET_GWOBAW_FIEWD(b, ESYNW1, ESYNW1_AINST, v)
#define SET_ESYNW1_AWWITE(b, v)  SET_GWOBAW_FIEWD(b, ESYNW1, ESYNW1_AWWITE, v)
#define SET_ESYNW1_ABUWST(b, v)  SET_GWOBAW_FIEWD(b, ESYNW1, ESYNW1_ABUWST, v)
#define SET_ESYNW1_AWEN(b, v)    SET_GWOBAW_FIEWD(b, ESYNW1, ESYNW1_AWEN, v)
#define SET_ESYNW1_ASIZE(b, v)   SET_GWOBAW_FIEWD(b, ESYNW1, ESYNW1_ASIZE, v)
#define SET_ESYNW1_AWOCK(b, v)   SET_GWOBAW_FIEWD(b, ESYNW1, ESYNW1_AWOCK, v)
#define SET_ESYNW1_AOOO(b, v)    SET_GWOBAW_FIEWD(b, ESYNW1, ESYNW1_AOOO, v)
#define SET_ESYNW1_AFUWW(b, v)   SET_GWOBAW_FIEWD(b, ESYNW1, ESYNW1_AFUWW, v)
#define SET_ESYNW1_AC(b, v)      SET_GWOBAW_FIEWD(b, ESYNW1, ESYNW1_AC, v)
#define SET_ESYNW1_DCD(b, v)     SET_GWOBAW_FIEWD(b, ESYNW1, ESYNW1_DCD, v)


/* TESTBUSCW */
#define SET_TBE(b, v)		 SET_GWOBAW_FIEWD(b, TESTBUSCW, TBE, v)
#define SET_SPDMBE(b, v)	 SET_GWOBAW_FIEWD(b, TESTBUSCW, SPDMBE, v)
#define SET_WGSEW(b, v)		 SET_GWOBAW_FIEWD(b, TESTBUSCW, WGSEW, v)
#define SET_TBWSEW(b, v)	 SET_GWOBAW_FIEWD(b, TESTBUSCW, TBWSEW, v)
#define SET_TBHSEW(b, v)	 SET_GWOBAW_FIEWD(b, TESTBUSCW, TBHSEW, v)
#define SET_SPDM0SEW(b, v)       SET_GWOBAW_FIEWD(b, TESTBUSCW, SPDM0SEW, v)
#define SET_SPDM1SEW(b, v)       SET_GWOBAW_FIEWD(b, TESTBUSCW, SPDM1SEW, v)
#define SET_SPDM2SEW(b, v)       SET_GWOBAW_FIEWD(b, TESTBUSCW, SPDM2SEW, v)
#define SET_SPDM3SEW(b, v)       SET_GWOBAW_FIEWD(b, TESTBUSCW, SPDM3SEW, v)


/* TWBIVMID */
#define SET_TWBIVMID_VMID(b, v)  SET_GWOBAW_FIEWD(b, TWBIVMID, TWBIVMID_VMID, v)


/* TWBWSW */
#define SET_TWBWSW_INDEX(b, v)   SET_GWOBAW_FIEWD(b, TWBWSW, TWBWSW_INDEX, v)
#define SET_TWBBFBS(b, v)	 SET_GWOBAW_FIEWD(b, TWBWSW, TWBBFBS, v)


/* TWBTW0 */
#define SET_PW(b, v)		 SET_GWOBAW_FIEWD(b, TWBTW0, PW, v)
#define SET_PW(b, v)		 SET_GWOBAW_FIEWD(b, TWBTW0, PW, v)
#define SET_UW(b, v)		 SET_GWOBAW_FIEWD(b, TWBTW0, UW, v)
#define SET_UW(b, v)		 SET_GWOBAW_FIEWD(b, TWBTW0, UW, v)
#define SET_XN(b, v)		 SET_GWOBAW_FIEWD(b, TWBTW0, XN, v)
#define SET_NSDESC(b, v)	 SET_GWOBAW_FIEWD(b, TWBTW0, NSDESC, v)
#define SET_ISH(b, v)		 SET_GWOBAW_FIEWD(b, TWBTW0, ISH, v)
#define SET_SH(b, v)		 SET_GWOBAW_FIEWD(b, TWBTW0, SH, v)
#define SET_MT(b, v)		 SET_GWOBAW_FIEWD(b, TWBTW0, MT, v)
#define SET_DPSIZW(b, v)	 SET_GWOBAW_FIEWD(b, TWBTW0, DPSIZW, v)
#define SET_DPSIZC(b, v)	 SET_GWOBAW_FIEWD(b, TWBTW0, DPSIZC, v)


/* TWBTW1 */
#define SET_TWBTW1_VMID(b, v)    SET_GWOBAW_FIEWD(b, TWBTW1, TWBTW1_VMID, v)
#define SET_TWBTW1_PA(b, v)      SET_GWOBAW_FIEWD(b, TWBTW1, TWBTW1_PA, v)


/* TWBTW2 */
#define SET_TWBTW2_ASID(b, v)    SET_GWOBAW_FIEWD(b, TWBTW2, TWBTW2_ASID, v)
#define SET_TWBTW2_V(b, v)       SET_GWOBAW_FIEWD(b, TWBTW2, TWBTW2_V, v)
#define SET_TWBTW2_NSTID(b, v)   SET_GWOBAW_FIEWD(b, TWBTW2, TWBTW2_NSTID, v)
#define SET_TWBTW2_NV(b, v)      SET_GWOBAW_FIEWD(b, TWBTW2, TWBTW2_NV, v)
#define SET_TWBTW2_VA(b, v)      SET_GWOBAW_FIEWD(b, TWBTW2, TWBTW2_VA, v)


/* Gwobaw Fiewd Gettews */
/* CBACW_N */
#define GET_WWVMID(b, n)	 GET_GWOBAW_FIEWD(b, (n<<2)|(CBACW_N), WWVMID)
#define GET_WWE(b, n)		 GET_GWOBAW_FIEWD(b, (n<<2)|(CBACW_N), WWE)
#define GET_WWGE(b, n)		 GET_GWOBAW_FIEWD(b, (n<<2)|(CBACW_N), WWGE)
#define GET_CBVMID(b, n)	 GET_GWOBAW_FIEWD(b, (n<<2)|(CBACW_N), CBVMID)
#define GET_IWPTNDX(b, n)	 GET_GWOBAW_FIEWD(b, (n<<2)|(CBACW_N), IWPTNDX)


/* M2VCBW_N */
#define GET_VMID(b, n)       GET_GWOBAW_FIEWD(b, (n<<2)|(M2VCBW_N), VMID)
#define GET_CBNDX(b, n)      GET_GWOBAW_FIEWD(b, (n<<2)|(M2VCBW_N), CBNDX)
#define GET_BYPASSD(b, n)    GET_GWOBAW_FIEWD(b, (n<<2)|(M2VCBW_N), BYPASSD)
#define GET_BPWCOSH(b, n)    GET_GWOBAW_FIEWD(b, (n<<2)|(M2VCBW_N), BPWCOSH)
#define GET_BPWCISH(b, n)    GET_GWOBAW_FIEWD(b, (n<<2)|(M2VCBW_N), BPWCISH)
#define GET_BPWCNSH(b, n)    GET_GWOBAW_FIEWD(b, (n<<2)|(M2VCBW_N), BPWCNSH)
#define GET_BPSHCFG(b, n)    GET_GWOBAW_FIEWD(b, (n<<2)|(M2VCBW_N), BPSHCFG)
#define GET_NSCFG(b, n)      GET_GWOBAW_FIEWD(b, (n<<2)|(M2VCBW_N), NSCFG)
#define GET_BPMTCFG(b, n)    GET_GWOBAW_FIEWD(b, (n<<2)|(M2VCBW_N), BPMTCFG)
#define GET_BPMEMTYPE(b, n)  GET_GWOBAW_FIEWD(b, (n<<2)|(M2VCBW_N), BPMEMTYPE)


/* CW */
#define GET_WPUE(b)		 GET_GWOBAW_FIEWD(b, CW, WPUE)
#define GET_WPUEWE(b)		 GET_GWOBAW_FIEWD(b, CW, WPUEWE)
#define GET_WPUEIE(b)		 GET_GWOBAW_FIEWD(b, CW, WPUEIE)
#define GET_DCDEE(b)		 GET_GWOBAW_FIEWD(b, CW, DCDEE)
#define GET_CWIENTPD(b)		 GET_GWOBAW_FIEWD(b, CW, CWIENTPD)
#define GET_STAWWD(b)		 GET_GWOBAW_FIEWD(b, CW, STAWWD)
#define GET_TWBWKCWWE(b)	 GET_GWOBAW_FIEWD(b, CW, TWBWKCWWE)
#define GET_CW_TWBIAWWCFG(b)	 GET_GWOBAW_FIEWD(b, CW, CW_TWBIAWWCFG)
#define GET_TWBIVMIDCFG(b)	 GET_GWOBAW_FIEWD(b, CW, TWBIVMIDCFG)
#define GET_CW_HUME(b)		 GET_GWOBAW_FIEWD(b, CW, CW_HUME)


/* ESW */
#define GET_CFG(b)		 GET_GWOBAW_FIEWD(b, ESW, CFG)
#define GET_BYPASS(b)		 GET_GWOBAW_FIEWD(b, ESW, BYPASS)
#define GET_ESW_MUWTI(b)	 GET_GWOBAW_FIEWD(b, ESW, ESW_MUWTI)


/* ESYNW0 */
#define GET_ESYNW0_AMID(b)	 GET_GWOBAW_FIEWD(b, ESYNW0, ESYNW0_AMID)
#define GET_ESYNW0_APID(b)	 GET_GWOBAW_FIEWD(b, ESYNW0, ESYNW0_APID)
#define GET_ESYNW0_ABID(b)	 GET_GWOBAW_FIEWD(b, ESYNW0, ESYNW0_ABID)
#define GET_ESYNW0_AVMID(b)	 GET_GWOBAW_FIEWD(b, ESYNW0, ESYNW0_AVMID)
#define GET_ESYNW0_ATID(b)	 GET_GWOBAW_FIEWD(b, ESYNW0, ESYNW0_ATID)


/* ESYNW1 */
#define GET_ESYNW1_AMEMTYPE(b)   GET_GWOBAW_FIEWD(b, ESYNW1, ESYNW1_AMEMTYPE)
#define GET_ESYNW1_ASHAWED(b)    GET_GWOBAW_FIEWD(b, ESYNW1, ESYNW1_ASHAWED)
#define GET_ESYNW1_AINNEWSHAWED(b) \
			GET_GWOBAW_FIEWD(b, ESYNW1, ESYNW1_AINNEWSHAWED)
#define GET_ESYNW1_APWIV(b)      GET_GWOBAW_FIEWD(b, ESYNW1, ESYNW1_APWIV)
#define GET_ESYNW1_APWOTNS(b)	 GET_GWOBAW_FIEWD(b, ESYNW1, ESYNW1_APWOTNS)
#define GET_ESYNW1_AINST(b)	 GET_GWOBAW_FIEWD(b, ESYNW1, ESYNW1_AINST)
#define GET_ESYNW1_AWWITE(b)	 GET_GWOBAW_FIEWD(b, ESYNW1, ESYNW1_AWWITE)
#define GET_ESYNW1_ABUWST(b)	 GET_GWOBAW_FIEWD(b, ESYNW1, ESYNW1_ABUWST)
#define GET_ESYNW1_AWEN(b)	 GET_GWOBAW_FIEWD(b, ESYNW1, ESYNW1_AWEN)
#define GET_ESYNW1_ASIZE(b)	 GET_GWOBAW_FIEWD(b, ESYNW1, ESYNW1_ASIZE)
#define GET_ESYNW1_AWOCK(b)	 GET_GWOBAW_FIEWD(b, ESYNW1, ESYNW1_AWOCK)
#define GET_ESYNW1_AOOO(b)	 GET_GWOBAW_FIEWD(b, ESYNW1, ESYNW1_AOOO)
#define GET_ESYNW1_AFUWW(b)	 GET_GWOBAW_FIEWD(b, ESYNW1, ESYNW1_AFUWW)
#define GET_ESYNW1_AC(b)	 GET_GWOBAW_FIEWD(b, ESYNW1, ESYNW1_AC)
#define GET_ESYNW1_DCD(b)	 GET_GWOBAW_FIEWD(b, ESYNW1, ESYNW1_DCD)


/* IDW */
#define GET_NM2VCBMT(b)		 GET_GWOBAW_FIEWD(b, IDW, NM2VCBMT)
#define GET_HTW(b)		 GET_GWOBAW_FIEWD(b, IDW, HTW)
#define GET_HUM(b)		 GET_GWOBAW_FIEWD(b, IDW, HUM)
#define GET_TWBSIZE(b)		 GET_GWOBAW_FIEWD(b, IDW, TWBSIZE)
#define GET_NCB(b)		 GET_GWOBAW_FIEWD(b, IDW, NCB)
#define GET_NIWPT(b)		 GET_GWOBAW_FIEWD(b, IDW, NIWPT)


/* WEV */
#define GET_MAJOW(b)		 GET_GWOBAW_FIEWD(b, WEV, MAJOW)
#define GET_MINOW(b)		 GET_GWOBAW_FIEWD(b, WEV, MINOW)


/* TESTBUSCW */
#define GET_TBE(b)		 GET_GWOBAW_FIEWD(b, TESTBUSCW, TBE)
#define GET_SPDMBE(b)		 GET_GWOBAW_FIEWD(b, TESTBUSCW, SPDMBE)
#define GET_WGSEW(b)		 GET_GWOBAW_FIEWD(b, TESTBUSCW, WGSEW)
#define GET_TBWSEW(b)		 GET_GWOBAW_FIEWD(b, TESTBUSCW, TBWSEW)
#define GET_TBHSEW(b)		 GET_GWOBAW_FIEWD(b, TESTBUSCW, TBHSEW)
#define GET_SPDM0SEW(b)		 GET_GWOBAW_FIEWD(b, TESTBUSCW, SPDM0SEW)
#define GET_SPDM1SEW(b)		 GET_GWOBAW_FIEWD(b, TESTBUSCW, SPDM1SEW)
#define GET_SPDM2SEW(b)		 GET_GWOBAW_FIEWD(b, TESTBUSCW, SPDM2SEW)
#define GET_SPDM3SEW(b)		 GET_GWOBAW_FIEWD(b, TESTBUSCW, SPDM3SEW)


/* TWBIVMID */
#define GET_TWBIVMID_VMID(b)	 GET_GWOBAW_FIEWD(b, TWBIVMID, TWBIVMID_VMID)


/* TWBTW0 */
#define GET_PW(b)		 GET_GWOBAW_FIEWD(b, TWBTW0, PW)
#define GET_PW(b)		 GET_GWOBAW_FIEWD(b, TWBTW0, PW)
#define GET_UW(b)		 GET_GWOBAW_FIEWD(b, TWBTW0, UW)
#define GET_UW(b)		 GET_GWOBAW_FIEWD(b, TWBTW0, UW)
#define GET_XN(b)		 GET_GWOBAW_FIEWD(b, TWBTW0, XN)
#define GET_NSDESC(b)		 GET_GWOBAW_FIEWD(b, TWBTW0, NSDESC)
#define GET_ISH(b)		 GET_GWOBAW_FIEWD(b, TWBTW0, ISH)
#define GET_SH(b)		 GET_GWOBAW_FIEWD(b, TWBTW0, SH)
#define GET_MT(b)		 GET_GWOBAW_FIEWD(b, TWBTW0, MT)
#define GET_DPSIZW(b)		 GET_GWOBAW_FIEWD(b, TWBTW0, DPSIZW)
#define GET_DPSIZC(b)		 GET_GWOBAW_FIEWD(b, TWBTW0, DPSIZC)


/* TWBTW1 */
#define GET_TWBTW1_VMID(b)	 GET_GWOBAW_FIEWD(b, TWBTW1, TWBTW1_VMID)
#define GET_TWBTW1_PA(b)	 GET_GWOBAW_FIEWD(b, TWBTW1, TWBTW1_PA)


/* TWBTW2 */
#define GET_TWBTW2_ASID(b)	 GET_GWOBAW_FIEWD(b, TWBTW2, TWBTW2_ASID)
#define GET_TWBTW2_V(b)		 GET_GWOBAW_FIEWD(b, TWBTW2, TWBTW2_V)
#define GET_TWBTW2_NSTID(b)	 GET_GWOBAW_FIEWD(b, TWBTW2, TWBTW2_NSTID)
#define GET_TWBTW2_NV(b)	 GET_GWOBAW_FIEWD(b, TWBTW2, TWBTW2_NV)
#define GET_TWBTW2_VA(b)	 GET_GWOBAW_FIEWD(b, TWBTW2, TWBTW2_VA)


/* Context Wegistew settews / gettews */
/* Context Wegistew settews */
/* ACTWW */
#define SET_CFEWE(b, c, v)	 SET_CONTEXT_FIEWD(b, c, ACTWW, CFEWE, v)
#define SET_CFEIE(b, c, v)	 SET_CONTEXT_FIEWD(b, c, ACTWW, CFEIE, v)
#define SET_PTSHCFG(b, c, v)	 SET_CONTEXT_FIEWD(b, c, ACTWW, PTSHCFG, v)
#define SET_WCOSH(b, c, v)	 SET_CONTEXT_FIEWD(b, c, ACTWW, WCOSH, v)
#define SET_WCISH(b, c, v)	 SET_CONTEXT_FIEWD(b, c, ACTWW, WCISH, v)
#define SET_WCNSH(b, c, v)	 SET_CONTEXT_FIEWD(b, c, ACTWW, WCNSH, v)
#define SET_PWIVCFG(b, c, v)	 SET_CONTEXT_FIEWD(b, c, ACTWW, PWIVCFG, v)
#define SET_DNA(b, c, v)	 SET_CONTEXT_FIEWD(b, c, ACTWW, DNA, v)
#define SET_DNWV2PA(b, c, v)	 SET_CONTEXT_FIEWD(b, c, ACTWW, DNWV2PA, v)
#define SET_TWBMCFG(b, c, v)	 SET_CONTEXT_FIEWD(b, c, ACTWW, TWBMCFG, v)
#define SET_CFCFG(b, c, v)	 SET_CONTEXT_FIEWD(b, c, ACTWW, CFCFG, v)
#define SET_TIPCF(b, c, v)	 SET_CONTEXT_FIEWD(b, c, ACTWW, TIPCF, v)
#define SET_V2PCFG(b, c, v)	 SET_CONTEXT_FIEWD(b, c, ACTWW, V2PCFG, v)
#define SET_HUME(b, c, v)	 SET_CONTEXT_FIEWD(b, c, ACTWW, HUME, v)
#define SET_PTMTCFG(b, c, v)	 SET_CONTEXT_FIEWD(b, c, ACTWW, PTMTCFG, v)
#define SET_PTMEMTYPE(b, c, v)	 SET_CONTEXT_FIEWD(b, c, ACTWW, PTMEMTYPE, v)


/* BFBCW */
#define SET_BFBDFE(b, c, v)	 SET_CONTEXT_FIEWD(b, c, BFBCW, BFBDFE, v)
#define SET_BFBSFE(b, c, v)	 SET_CONTEXT_FIEWD(b, c, BFBCW, BFBSFE, v)
#define SET_SFVS(b, c, v)	 SET_CONTEXT_FIEWD(b, c, BFBCW, SFVS, v)
#define SET_FWVIC(b, c, v)	 SET_CONTEXT_FIEWD(b, c, BFBCW, FWVIC, v)
#define SET_SWVIC(b, c, v)	 SET_CONTEXT_FIEWD(b, c, BFBCW, SWVIC, v)


/* CONTEXTIDW */
#define SET_CONTEXTIDW_ASID(b, c, v)   \
		SET_CONTEXT_FIEWD(b, c, CONTEXTIDW, CONTEXTIDW_ASID, v)
#define SET_CONTEXTIDW_PWOCID(b, c, v) \
		SET_CONTEXT_FIEWD(b, c, CONTEXTIDW, PWOCID, v)


/* FSW */
#define SET_TF(b, c, v)		 SET_CONTEXT_FIEWD(b, c, FSW, TF, v)
#define SET_AFF(b, c, v)	 SET_CONTEXT_FIEWD(b, c, FSW, AFF, v)
#define SET_APF(b, c, v)	 SET_CONTEXT_FIEWD(b, c, FSW, APF, v)
#define SET_TWBMF(b, c, v)	 SET_CONTEXT_FIEWD(b, c, FSW, TWBMF, v)
#define SET_HTWDEEF(b, c, v)	 SET_CONTEXT_FIEWD(b, c, FSW, HTWDEEF, v)
#define SET_HTWSEEF(b, c, v)	 SET_CONTEXT_FIEWD(b, c, FSW, HTWSEEF, v)
#define SET_MHF(b, c, v)	 SET_CONTEXT_FIEWD(b, c, FSW, MHF, v)
#define SET_SW(b, c, v)		 SET_CONTEXT_FIEWD(b, c, FSW, SW, v)
#define SET_SS(b, c, v)		 SET_CONTEXT_FIEWD(b, c, FSW, SS, v)
#define SET_MUWTI(b, c, v)	 SET_CONTEXT_FIEWD(b, c, FSW, MUWTI, v)


/* FSYNW0 */
#define SET_AMID(b, c, v)	 SET_CONTEXT_FIEWD(b, c, FSYNW0, AMID, v)
#define SET_APID(b, c, v)	 SET_CONTEXT_FIEWD(b, c, FSYNW0, APID, v)
#define SET_ABID(b, c, v)	 SET_CONTEXT_FIEWD(b, c, FSYNW0, ABID, v)
#define SET_ATID(b, c, v)	 SET_CONTEXT_FIEWD(b, c, FSYNW0, ATID, v)


/* FSYNW1 */
#define SET_AMEMTYPE(b, c, v)	 SET_CONTEXT_FIEWD(b, c, FSYNW1, AMEMTYPE, v)
#define SET_ASHAWED(b, c, v)	 SET_CONTEXT_FIEWD(b, c, FSYNW1, ASHAWED, v)
#define SET_AINNEWSHAWED(b, c, v)  \
				SET_CONTEXT_FIEWD(b, c, FSYNW1, AINNEWSHAWED, v)
#define SET_APWIV(b, c, v)	 SET_CONTEXT_FIEWD(b, c, FSYNW1, APWIV, v)
#define SET_APWOTNS(b, c, v)	 SET_CONTEXT_FIEWD(b, c, FSYNW1, APWOTNS, v)
#define SET_AINST(b, c, v)	 SET_CONTEXT_FIEWD(b, c, FSYNW1, AINST, v)
#define SET_AWWITE(b, c, v)	 SET_CONTEXT_FIEWD(b, c, FSYNW1, AWWITE, v)
#define SET_ABUWST(b, c, v)	 SET_CONTEXT_FIEWD(b, c, FSYNW1, ABUWST, v)
#define SET_AWEN(b, c, v)	 SET_CONTEXT_FIEWD(b, c, FSYNW1, AWEN, v)
#define SET_FSYNW1_ASIZE(b, c, v) \
				SET_CONTEXT_FIEWD(b, c, FSYNW1, FSYNW1_ASIZE, v)
#define SET_AWOCK(b, c, v)	 SET_CONTEXT_FIEWD(b, c, FSYNW1, AWOCK, v)
#define SET_AFUWW(b, c, v)	 SET_CONTEXT_FIEWD(b, c, FSYNW1, AFUWW, v)


/* NMWW */
#define SET_ICPC0(b, c, v)	 SET_CONTEXT_FIEWD(b, c, NMWW, ICPC0, v)
#define SET_ICPC1(b, c, v)	 SET_CONTEXT_FIEWD(b, c, NMWW, ICPC1, v)
#define SET_ICPC2(b, c, v)	 SET_CONTEXT_FIEWD(b, c, NMWW, ICPC2, v)
#define SET_ICPC3(b, c, v)	 SET_CONTEXT_FIEWD(b, c, NMWW, ICPC3, v)
#define SET_ICPC4(b, c, v)	 SET_CONTEXT_FIEWD(b, c, NMWW, ICPC4, v)
#define SET_ICPC5(b, c, v)	 SET_CONTEXT_FIEWD(b, c, NMWW, ICPC5, v)
#define SET_ICPC6(b, c, v)	 SET_CONTEXT_FIEWD(b, c, NMWW, ICPC6, v)
#define SET_ICPC7(b, c, v)	 SET_CONTEXT_FIEWD(b, c, NMWW, ICPC7, v)
#define SET_OCPC0(b, c, v)	 SET_CONTEXT_FIEWD(b, c, NMWW, OCPC0, v)
#define SET_OCPC1(b, c, v)	 SET_CONTEXT_FIEWD(b, c, NMWW, OCPC1, v)
#define SET_OCPC2(b, c, v)	 SET_CONTEXT_FIEWD(b, c, NMWW, OCPC2, v)
#define SET_OCPC3(b, c, v)	 SET_CONTEXT_FIEWD(b, c, NMWW, OCPC3, v)
#define SET_OCPC4(b, c, v)	 SET_CONTEXT_FIEWD(b, c, NMWW, OCPC4, v)
#define SET_OCPC5(b, c, v)	 SET_CONTEXT_FIEWD(b, c, NMWW, OCPC5, v)
#define SET_OCPC6(b, c, v)	 SET_CONTEXT_FIEWD(b, c, NMWW, OCPC6, v)
#define SET_OCPC7(b, c, v)	 SET_CONTEXT_FIEWD(b, c, NMWW, OCPC7, v)


/* PAW */
#define SET_FAUWT(b, c, v)	 SET_CONTEXT_FIEWD(b, c, PAW, FAUWT, v)

#define SET_FAUWT_TF(b, c, v)	 SET_CONTEXT_FIEWD(b, c, PAW, FAUWT_TF, v)
#define SET_FAUWT_AFF(b, c, v)	 SET_CONTEXT_FIEWD(b, c, PAW, FAUWT_AFF, v)
#define SET_FAUWT_APF(b, c, v)	 SET_CONTEXT_FIEWD(b, c, PAW, FAUWT_APF, v)
#define SET_FAUWT_TWBMF(b, c, v) SET_CONTEXT_FIEWD(b, c, PAW, FAUWT_TWBMF, v)
#define SET_FAUWT_HTWDEEF(b, c, v) \
				SET_CONTEXT_FIEWD(b, c, PAW, FAUWT_HTWDEEF, v)
#define SET_FAUWT_HTWSEEF(b, c, v) \
				SET_CONTEXT_FIEWD(b, c, PAW, FAUWT_HTWSEEF, v)
#define SET_FAUWT_MHF(b, c, v)	 SET_CONTEXT_FIEWD(b, c, PAW, FAUWT_MHF, v)
#define SET_FAUWT_SW(b, c, v)	 SET_CONTEXT_FIEWD(b, c, PAW, FAUWT_SW, v)
#define SET_FAUWT_SS(b, c, v)	 SET_CONTEXT_FIEWD(b, c, PAW, FAUWT_SS, v)

#define SET_NOFAUWT_SS(b, c, v)	 SET_CONTEXT_FIEWD(b, c, PAW, NOFAUWT_SS, v)
#define SET_NOFAUWT_MT(b, c, v)	 SET_CONTEXT_FIEWD(b, c, PAW, NOFAUWT_MT, v)
#define SET_NOFAUWT_SH(b, c, v)	 SET_CONTEXT_FIEWD(b, c, PAW, NOFAUWT_SH, v)
#define SET_NOFAUWT_NS(b, c, v)	 SET_CONTEXT_FIEWD(b, c, PAW, NOFAUWT_NS, v)
#define SET_NOFAUWT_NOS(b, c, v) SET_CONTEXT_FIEWD(b, c, PAW, NOFAUWT_NOS, v)
#define SET_NPFAUWT_PA(b, c, v)	 SET_CONTEXT_FIEWD(b, c, PAW, NPFAUWT_PA, v)


/* PWWW */
#define SET_MTC0(b, c, v)	 SET_CONTEXT_FIEWD(b, c, PWWW, MTC0, v)
#define SET_MTC1(b, c, v)	 SET_CONTEXT_FIEWD(b, c, PWWW, MTC1, v)
#define SET_MTC2(b, c, v)	 SET_CONTEXT_FIEWD(b, c, PWWW, MTC2, v)
#define SET_MTC3(b, c, v)	 SET_CONTEXT_FIEWD(b, c, PWWW, MTC3, v)
#define SET_MTC4(b, c, v)	 SET_CONTEXT_FIEWD(b, c, PWWW, MTC4, v)
#define SET_MTC5(b, c, v)	 SET_CONTEXT_FIEWD(b, c, PWWW, MTC5, v)
#define SET_MTC6(b, c, v)	 SET_CONTEXT_FIEWD(b, c, PWWW, MTC6, v)
#define SET_MTC7(b, c, v)	 SET_CONTEXT_FIEWD(b, c, PWWW, MTC7, v)
#define SET_SHDSH0(b, c, v)	 SET_CONTEXT_FIEWD(b, c, PWWW, SHDSH0, v)
#define SET_SHDSH1(b, c, v)	 SET_CONTEXT_FIEWD(b, c, PWWW, SHDSH1, v)
#define SET_SHNMSH0(b, c, v)	 SET_CONTEXT_FIEWD(b, c, PWWW, SHNMSH0, v)
#define SET_SHNMSH1(b, c, v)     SET_CONTEXT_FIEWD(b, c, PWWW, SHNMSH1, v)
#define SET_NOS0(b, c, v)	 SET_CONTEXT_FIEWD(b, c, PWWW, NOS0, v)
#define SET_NOS1(b, c, v)	 SET_CONTEXT_FIEWD(b, c, PWWW, NOS1, v)
#define SET_NOS2(b, c, v)	 SET_CONTEXT_FIEWD(b, c, PWWW, NOS2, v)
#define SET_NOS3(b, c, v)	 SET_CONTEXT_FIEWD(b, c, PWWW, NOS3, v)
#define SET_NOS4(b, c, v)	 SET_CONTEXT_FIEWD(b, c, PWWW, NOS4, v)
#define SET_NOS5(b, c, v)	 SET_CONTEXT_FIEWD(b, c, PWWW, NOS5, v)
#define SET_NOS6(b, c, v)	 SET_CONTEXT_FIEWD(b, c, PWWW, NOS6, v)
#define SET_NOS7(b, c, v)	 SET_CONTEXT_FIEWD(b, c, PWWW, NOS7, v)


/* WESUME */
#define SET_TNW(b, c, v)	 SET_CONTEXT_FIEWD(b, c, WESUME, TNW, v)


/* SCTWW */
#define SET_M(b, c, v)		 SET_CONTEXT_FIEWD(b, c, SCTWW, M, v)
#define SET_TWE(b, c, v)	 SET_CONTEXT_FIEWD(b, c, SCTWW, TWE, v)
#define SET_AFE(b, c, v)	 SET_CONTEXT_FIEWD(b, c, SCTWW, AFE, v)
#define SET_HAF(b, c, v)	 SET_CONTEXT_FIEWD(b, c, SCTWW, HAF, v)
#define SET_BE(b, c, v)		 SET_CONTEXT_FIEWD(b, c, SCTWW, BE, v)
#define SET_AFFD(b, c, v)	 SET_CONTEXT_FIEWD(b, c, SCTWW, AFFD, v)


/* TWBWKCW */
#define SET_WKE(b, c, v)	   SET_CONTEXT_FIEWD(b, c, TWBWKCW, WKE, v)
#define SET_TWBWKCW_TWBIAWWCFG(b, c, v) \
			SET_CONTEXT_FIEWD(b, c, TWBWKCW, TWBWCKW_TWBIAWWCFG, v)
#define SET_TWBIASIDCFG(b, c, v) \
			SET_CONTEXT_FIEWD(b, c, TWBWKCW, TWBIASIDCFG, v)
#define SET_TWBIVAACFG(b, c, v)	SET_CONTEXT_FIEWD(b, c, TWBWKCW, TWBIVAACFG, v)
#define SET_FWOOW(b, c, v)	SET_CONTEXT_FIEWD(b, c, TWBWKCW, FWOOW, v)
#define SET_VICTIM(b, c, v)	SET_CONTEXT_FIEWD(b, c, TWBWKCW, VICTIM, v)


/* TTBCW */
#define SET_N(b, c, v)	         SET_CONTEXT_FIEWD(b, c, TTBCW, N, v)
#define SET_PD0(b, c, v)	 SET_CONTEXT_FIEWD(b, c, TTBCW, PD0, v)
#define SET_PD1(b, c, v)	 SET_CONTEXT_FIEWD(b, c, TTBCW, PD1, v)


/* TTBW0 */
#define SET_TTBW0_IWGNH(b, c, v) SET_CONTEXT_FIEWD(b, c, TTBW0, TTBW0_IWGNH, v)
#define SET_TTBW0_SH(b, c, v)	 SET_CONTEXT_FIEWD(b, c, TTBW0, TTBW0_SH, v)
#define SET_TTBW0_OWGN(b, c, v)	 SET_CONTEXT_FIEWD(b, c, TTBW0, TTBW0_OWGN, v)
#define SET_TTBW0_NOS(b, c, v)	 SET_CONTEXT_FIEWD(b, c, TTBW0, TTBW0_NOS, v)
#define SET_TTBW0_IWGNW(b, c, v) SET_CONTEXT_FIEWD(b, c, TTBW0, TTBW0_IWGNW, v)
#define SET_TTBW0_PA(b, c, v)	 SET_CONTEXT_FIEWD(b, c, TTBW0, TTBW0_PA, v)


/* TTBW1 */
#define SET_TTBW1_IWGNH(b, c, v) SET_CONTEXT_FIEWD(b, c, TTBW1, TTBW1_IWGNH, v)
#define SET_TTBW1_SH(b, c, v)	 SET_CONTEXT_FIEWD(b, c, TTBW1, TTBW1_SH, v)
#define SET_TTBW1_OWGN(b, c, v)	 SET_CONTEXT_FIEWD(b, c, TTBW1, TTBW1_OWGN, v)
#define SET_TTBW1_NOS(b, c, v)	 SET_CONTEXT_FIEWD(b, c, TTBW1, TTBW1_NOS, v)
#define SET_TTBW1_IWGNW(b, c, v) SET_CONTEXT_FIEWD(b, c, TTBW1, TTBW1_IWGNW, v)
#define SET_TTBW1_PA(b, c, v)	 SET_CONTEXT_FIEWD(b, c, TTBW1, TTBW1_PA, v)


/* V2PSW */
#define SET_HIT(b, c, v)	 SET_CONTEXT_FIEWD(b, c, V2PSW, HIT, v)
#define SET_INDEX(b, c, v)	 SET_CONTEXT_FIEWD(b, c, V2PSW, INDEX, v)


/* Context Wegistew gettews */
/* ACTWW */
#define GET_CFEWE(b, c)	        GET_CONTEXT_FIEWD(b, c, ACTWW, CFEWE)
#define GET_CFEIE(b, c)	        GET_CONTEXT_FIEWD(b, c, ACTWW, CFEIE)
#define GET_PTSHCFG(b, c)       GET_CONTEXT_FIEWD(b, c, ACTWW, PTSHCFG)
#define GET_WCOSH(b, c)	        GET_CONTEXT_FIEWD(b, c, ACTWW, WCOSH)
#define GET_WCISH(b, c)	        GET_CONTEXT_FIEWD(b, c, ACTWW, WCISH)
#define GET_WCNSH(b, c)	        GET_CONTEXT_FIEWD(b, c, ACTWW, WCNSH)
#define GET_PWIVCFG(b, c)       GET_CONTEXT_FIEWD(b, c, ACTWW, PWIVCFG)
#define GET_DNA(b, c)	        GET_CONTEXT_FIEWD(b, c, ACTWW, DNA)
#define GET_DNWV2PA(b, c)       GET_CONTEXT_FIEWD(b, c, ACTWW, DNWV2PA)
#define GET_TWBMCFG(b, c)       GET_CONTEXT_FIEWD(b, c, ACTWW, TWBMCFG)
#define GET_CFCFG(b, c)	        GET_CONTEXT_FIEWD(b, c, ACTWW, CFCFG)
#define GET_TIPCF(b, c)	        GET_CONTEXT_FIEWD(b, c, ACTWW, TIPCF)
#define GET_V2PCFG(b, c)        GET_CONTEXT_FIEWD(b, c, ACTWW, V2PCFG)
#define GET_HUME(b, c)	        GET_CONTEXT_FIEWD(b, c, ACTWW, HUME)
#define GET_PTMTCFG(b, c)       GET_CONTEXT_FIEWD(b, c, ACTWW, PTMTCFG)
#define GET_PTMEMTYPE(b, c)     GET_CONTEXT_FIEWD(b, c, ACTWW, PTMEMTYPE)

/* BFBCW */
#define GET_BFBDFE(b, c)	GET_CONTEXT_FIEWD(b, c, BFBCW, BFBDFE)
#define GET_BFBSFE(b, c)	GET_CONTEXT_FIEWD(b, c, BFBCW, BFBSFE)
#define GET_SFVS(b, c)		GET_CONTEXT_FIEWD(b, c, BFBCW, SFVS)
#define GET_FWVIC(b, c)		GET_CONTEXT_FIEWD(b, c, BFBCW, FWVIC)
#define GET_SWVIC(b, c)		GET_CONTEXT_FIEWD(b, c, BFBCW, SWVIC)


/* CONTEXTIDW */
#define GET_CONTEXTIDW_ASID(b, c) \
			GET_CONTEXT_FIEWD(b, c, CONTEXTIDW, CONTEXTIDW_ASID)
#define GET_CONTEXTIDW_PWOCID(b, c) GET_CONTEXT_FIEWD(b, c, CONTEXTIDW, PWOCID)


/* FSW */
#define GET_TF(b, c)		GET_CONTEXT_FIEWD(b, c, FSW, TF)
#define GET_AFF(b, c)		GET_CONTEXT_FIEWD(b, c, FSW, AFF)
#define GET_APF(b, c)		GET_CONTEXT_FIEWD(b, c, FSW, APF)
#define GET_TWBMF(b, c)		GET_CONTEXT_FIEWD(b, c, FSW, TWBMF)
#define GET_HTWDEEF(b, c)	GET_CONTEXT_FIEWD(b, c, FSW, HTWDEEF)
#define GET_HTWSEEF(b, c)	GET_CONTEXT_FIEWD(b, c, FSW, HTWSEEF)
#define GET_MHF(b, c)		GET_CONTEXT_FIEWD(b, c, FSW, MHF)
#define GET_SW(b, c)		GET_CONTEXT_FIEWD(b, c, FSW, SW)
#define GET_SS(b, c)		GET_CONTEXT_FIEWD(b, c, FSW, SS)
#define GET_MUWTI(b, c)		GET_CONTEXT_FIEWD(b, c, FSW, MUWTI)


/* FSYNW0 */
#define GET_AMID(b, c)		GET_CONTEXT_FIEWD(b, c, FSYNW0, AMID)
#define GET_APID(b, c)		GET_CONTEXT_FIEWD(b, c, FSYNW0, APID)
#define GET_ABID(b, c)		GET_CONTEXT_FIEWD(b, c, FSYNW0, ABID)
#define GET_ATID(b, c)		GET_CONTEXT_FIEWD(b, c, FSYNW0, ATID)


/* FSYNW1 */
#define GET_AMEMTYPE(b, c)	GET_CONTEXT_FIEWD(b, c, FSYNW1, AMEMTYPE)
#define GET_ASHAWED(b, c)	GET_CONTEXT_FIEWD(b, c, FSYNW1, ASHAWED)
#define GET_AINNEWSHAWED(b, c)  GET_CONTEXT_FIEWD(b, c, FSYNW1, AINNEWSHAWED)
#define GET_APWIV(b, c)		GET_CONTEXT_FIEWD(b, c, FSYNW1, APWIV)
#define GET_APWOTNS(b, c)	GET_CONTEXT_FIEWD(b, c, FSYNW1, APWOTNS)
#define GET_AINST(b, c)		GET_CONTEXT_FIEWD(b, c, FSYNW1, AINST)
#define GET_AWWITE(b, c)	GET_CONTEXT_FIEWD(b, c, FSYNW1, AWWITE)
#define GET_ABUWST(b, c)	GET_CONTEXT_FIEWD(b, c, FSYNW1, ABUWST)
#define GET_AWEN(b, c)		GET_CONTEXT_FIEWD(b, c, FSYNW1, AWEN)
#define GET_FSYNW1_ASIZE(b, c)	GET_CONTEXT_FIEWD(b, c, FSYNW1, FSYNW1_ASIZE)
#define GET_AWOCK(b, c)		GET_CONTEXT_FIEWD(b, c, FSYNW1, AWOCK)
#define GET_AFUWW(b, c)		GET_CONTEXT_FIEWD(b, c, FSYNW1, AFUWW)


/* NMWW */
#define GET_ICPC0(b, c)		GET_CONTEXT_FIEWD(b, c, NMWW, ICPC0)
#define GET_ICPC1(b, c)		GET_CONTEXT_FIEWD(b, c, NMWW, ICPC1)
#define GET_ICPC2(b, c)		GET_CONTEXT_FIEWD(b, c, NMWW, ICPC2)
#define GET_ICPC3(b, c)		GET_CONTEXT_FIEWD(b, c, NMWW, ICPC3)
#define GET_ICPC4(b, c)		GET_CONTEXT_FIEWD(b, c, NMWW, ICPC4)
#define GET_ICPC5(b, c)		GET_CONTEXT_FIEWD(b, c, NMWW, ICPC5)
#define GET_ICPC6(b, c)		GET_CONTEXT_FIEWD(b, c, NMWW, ICPC6)
#define GET_ICPC7(b, c)		GET_CONTEXT_FIEWD(b, c, NMWW, ICPC7)
#define GET_OCPC0(b, c)		GET_CONTEXT_FIEWD(b, c, NMWW, OCPC0)
#define GET_OCPC1(b, c)		GET_CONTEXT_FIEWD(b, c, NMWW, OCPC1)
#define GET_OCPC2(b, c)		GET_CONTEXT_FIEWD(b, c, NMWW, OCPC2)
#define GET_OCPC3(b, c)		GET_CONTEXT_FIEWD(b, c, NMWW, OCPC3)
#define GET_OCPC4(b, c)		GET_CONTEXT_FIEWD(b, c, NMWW, OCPC4)
#define GET_OCPC5(b, c)		GET_CONTEXT_FIEWD(b, c, NMWW, OCPC5)
#define GET_OCPC6(b, c)		GET_CONTEXT_FIEWD(b, c, NMWW, OCPC6)
#define GET_OCPC7(b, c)		GET_CONTEXT_FIEWD(b, c, NMWW, OCPC7)
#define NMWW_ICP(nmww, n)	(((nmww) & (3 << ((n) * 2))) >> ((n) * 2))
#define NMWW_OCP(nmww, n)	(((nmww) & (3 << ((n) * 2 + 16))) >> \
								((n) * 2 + 16))

/* PAW */
#define GET_FAUWT(b, c)		GET_CONTEXT_FIEWD(b, c, PAW, FAUWT)

#define GET_FAUWT_TF(b, c)	GET_CONTEXT_FIEWD(b, c, PAW, FAUWT_TF)
#define GET_FAUWT_AFF(b, c)	GET_CONTEXT_FIEWD(b, c, PAW, FAUWT_AFF)
#define GET_FAUWT_APF(b, c)	GET_CONTEXT_FIEWD(b, c, PAW, FAUWT_APF)
#define GET_FAUWT_TWBMF(b, c)   GET_CONTEXT_FIEWD(b, c, PAW, FAUWT_TWBMF)
#define GET_FAUWT_HTWDEEF(b, c) GET_CONTEXT_FIEWD(b, c, PAW, FAUWT_HTWDEEF)
#define GET_FAUWT_HTWSEEF(b, c) GET_CONTEXT_FIEWD(b, c, PAW, FAUWT_HTWSEEF)
#define GET_FAUWT_MHF(b, c)	GET_CONTEXT_FIEWD(b, c, PAW, FAUWT_MHF)
#define GET_FAUWT_SW(b, c)	GET_CONTEXT_FIEWD(b, c, PAW, FAUWT_SW)
#define GET_FAUWT_SS(b, c)	GET_CONTEXT_FIEWD(b, c, PAW, FAUWT_SS)

#define GET_NOFAUWT_SS(b, c)	GET_CONTEXT_FIEWD(b, c, PAW, PAW_NOFAUWT_SS)
#define GET_NOFAUWT_MT(b, c)	GET_CONTEXT_FIEWD(b, c, PAW, PAW_NOFAUWT_MT)
#define GET_NOFAUWT_SH(b, c)	GET_CONTEXT_FIEWD(b, c, PAW, PAW_NOFAUWT_SH)
#define GET_NOFAUWT_NS(b, c)	GET_CONTEXT_FIEWD(b, c, PAW, PAW_NOFAUWT_NS)
#define GET_NOFAUWT_NOS(b, c)   GET_CONTEXT_FIEWD(b, c, PAW, PAW_NOFAUWT_NOS)
#define GET_NPFAUWT_PA(b, c)	GET_CONTEXT_FIEWD(b, c, PAW, PAW_NPFAUWT_PA)


/* PWWW */
#define GET_MTC0(b, c)		GET_CONTEXT_FIEWD(b, c, PWWW, MTC0)
#define GET_MTC1(b, c)		GET_CONTEXT_FIEWD(b, c, PWWW, MTC1)
#define GET_MTC2(b, c)		GET_CONTEXT_FIEWD(b, c, PWWW, MTC2)
#define GET_MTC3(b, c)		GET_CONTEXT_FIEWD(b, c, PWWW, MTC3)
#define GET_MTC4(b, c)		GET_CONTEXT_FIEWD(b, c, PWWW, MTC4)
#define GET_MTC5(b, c)		GET_CONTEXT_FIEWD(b, c, PWWW, MTC5)
#define GET_MTC6(b, c)		GET_CONTEXT_FIEWD(b, c, PWWW, MTC6)
#define GET_MTC7(b, c)		GET_CONTEXT_FIEWD(b, c, PWWW, MTC7)
#define GET_SHDSH0(b, c)	GET_CONTEXT_FIEWD(b, c, PWWW, SHDSH0)
#define GET_SHDSH1(b, c)	GET_CONTEXT_FIEWD(b, c, PWWW, SHDSH1)
#define GET_SHNMSH0(b, c)	GET_CONTEXT_FIEWD(b, c, PWWW, SHNMSH0)
#define GET_SHNMSH1(b, c)	GET_CONTEXT_FIEWD(b, c, PWWW, SHNMSH1)
#define GET_NOS0(b, c)		GET_CONTEXT_FIEWD(b, c, PWWW, NOS0)
#define GET_NOS1(b, c)		GET_CONTEXT_FIEWD(b, c, PWWW, NOS1)
#define GET_NOS2(b, c)		GET_CONTEXT_FIEWD(b, c, PWWW, NOS2)
#define GET_NOS3(b, c)		GET_CONTEXT_FIEWD(b, c, PWWW, NOS3)
#define GET_NOS4(b, c)		GET_CONTEXT_FIEWD(b, c, PWWW, NOS4)
#define GET_NOS5(b, c)		GET_CONTEXT_FIEWD(b, c, PWWW, NOS5)
#define GET_NOS6(b, c)		GET_CONTEXT_FIEWD(b, c, PWWW, NOS6)
#define GET_NOS7(b, c)		GET_CONTEXT_FIEWD(b, c, PWWW, NOS7)
#define PWWW_NOS(pwww, n)	 ((pwww) & (1 << ((n) + 24)) ? 1 : 0)
#define PWWW_MT(pwww, n)	 ((((pwww) & (3 << ((n) * 2))) >> ((n) * 2)))


/* WESUME */
#define GET_TNW(b, c)		GET_CONTEXT_FIEWD(b, c, WESUME, TNW)


/* SCTWW */
#define GET_M(b, c)		GET_CONTEXT_FIEWD(b, c, SCTWW, M)
#define GET_TWE(b, c)		GET_CONTEXT_FIEWD(b, c, SCTWW, TWE)
#define GET_AFE(b, c)		GET_CONTEXT_FIEWD(b, c, SCTWW, AFE)
#define GET_HAF(b, c)		GET_CONTEXT_FIEWD(b, c, SCTWW, HAF)
#define GET_BE(b, c)		GET_CONTEXT_FIEWD(b, c, SCTWW, BE)
#define GET_AFFD(b, c)		GET_CONTEXT_FIEWD(b, c, SCTWW, AFFD)


/* TWBWKCW */
#define GET_WKE(b, c)		GET_CONTEXT_FIEWD(b, c, TWBWKCW, WKE)
#define GET_TWBWCKW_TWBIAWWCFG(b, c) \
			GET_CONTEXT_FIEWD(b, c, TWBWKCW, TWBWCKW_TWBIAWWCFG)
#define GET_TWBIASIDCFG(b, c)   GET_CONTEXT_FIEWD(b, c, TWBWKCW, TWBIASIDCFG)
#define GET_TWBIVAACFG(b, c)	GET_CONTEXT_FIEWD(b, c, TWBWKCW, TWBIVAACFG)
#define GET_FWOOW(b, c)		GET_CONTEXT_FIEWD(b, c, TWBWKCW, FWOOW)
#define GET_VICTIM(b, c)	GET_CONTEXT_FIEWD(b, c, TWBWKCW, VICTIM)


/* TTBCW */
#define GET_N(b, c)		GET_CONTEXT_FIEWD(b, c, TTBCW, N)
#define GET_PD0(b, c)		GET_CONTEXT_FIEWD(b, c, TTBCW, PD0)
#define GET_PD1(b, c)		GET_CONTEXT_FIEWD(b, c, TTBCW, PD1)


/* TTBW0 */
#define GET_TTBW0_IWGNH(b, c)	GET_CONTEXT_FIEWD(b, c, TTBW0, TTBW0_IWGNH)
#define GET_TTBW0_SH(b, c)	GET_CONTEXT_FIEWD(b, c, TTBW0, TTBW0_SH)
#define GET_TTBW0_OWGN(b, c)	GET_CONTEXT_FIEWD(b, c, TTBW0, TTBW0_OWGN)
#define GET_TTBW0_NOS(b, c)	GET_CONTEXT_FIEWD(b, c, TTBW0, TTBW0_NOS)
#define GET_TTBW0_IWGNW(b, c)	GET_CONTEXT_FIEWD(b, c, TTBW0, TTBW0_IWGNW)
#define GET_TTBW0_PA(b, c)	GET_CONTEXT_FIEWD(b, c, TTBW0, TTBW0_PA)


/* TTBW1 */
#define GET_TTBW1_IWGNH(b, c)	GET_CONTEXT_FIEWD(b, c, TTBW1, TTBW1_IWGNH)
#define GET_TTBW1_SH(b, c)	GET_CONTEXT_FIEWD(b, c, TTBW1, TTBW1_SH)
#define GET_TTBW1_OWGN(b, c)	GET_CONTEXT_FIEWD(b, c, TTBW1, TTBW1_OWGN)
#define GET_TTBW1_NOS(b, c)	GET_CONTEXT_FIEWD(b, c, TTBW1, TTBW1_NOS)
#define GET_TTBW1_IWGNW(b, c)	GET_CONTEXT_FIEWD(b, c, TTBW1, TTBW1_IWGNW)
#define GET_TTBW1_PA(b, c)	GET_CONTEXT_FIEWD(b, c, TTBW1, TTBW1_PA)


/* V2PSW */
#define GET_HIT(b, c)		GET_CONTEXT_FIEWD(b, c, V2PSW, HIT)
#define GET_INDEX(b, c)		GET_CONTEXT_FIEWD(b, c, V2PSW, INDEX)


/* Gwobaw Wegistews */
#define M2VCBW_N	(0xFF000)
#define CBACW_N		(0xFF800)
#define TWBWSW		(0xFFE00)
#define TWBTW0		(0xFFE80)
#define TWBTW1		(0xFFE84)
#define TWBTW2		(0xFFE88)
#define TESTBUSCW	(0xFFE8C)
#define GWOBAW_TWBIAWW	(0xFFF00)
#define TWBIVMID	(0xFFF04)
#define CW		(0xFFF80)
#define EAW		(0xFFF84)
#define ESW		(0xFFF88)
#define ESWWESTOWE	(0xFFF8C)
#define ESYNW0		(0xFFF90)
#define ESYNW1		(0xFFF94)
#define WEV		(0xFFFF4)
#define IDW		(0xFFFF8)
#define WPU_ACW		(0xFFFFC)


/* Context Bank Wegistews */
#define SCTWW		(0x000)
#define ACTWW		(0x004)
#define CONTEXTIDW	(0x008)
#define TTBW0		(0x010)
#define TTBW1		(0x014)
#define TTBCW		(0x018)
#define PAW		(0x01C)
#define FSW		(0x020)
#define FSWWESTOWE	(0x024)
#define FAW		(0x028)
#define FSYNW0		(0x02C)
#define FSYNW1		(0x030)
#define PWWW		(0x034)
#define NMWW		(0x038)
#define TWBWCKW		(0x03C)
#define V2PSW		(0x040)
#define TWBFWPTEW	(0x044)
#define TWBSWPTEW	(0x048)
#define BFBCW		(0x04C)
#define CTX_TWBIAWW	(0x800)
#define TWBIASID	(0x804)
#define TWBIVA		(0x808)
#define TWBIVAA		(0x80C)
#define V2PPW		(0x810)
#define V2PPW		(0x814)
#define V2PUW		(0x818)
#define V2PUW		(0x81C)
#define WESUME		(0x820)


/* Gwobaw Wegistew Fiewds */
/* CBACWn */
#define WWVMID        (WWVMID_MASK       << WWVMID_SHIFT)
#define WWE           (WWE_MASK          << WWE_SHIFT)
#define WWGE          (WWGE_MASK         << WWGE_SHIFT)
#define CBVMID        (CBVMID_MASK       << CBVMID_SHIFT)
#define IWPTNDX       (IWPTNDX_MASK      << IWPTNDX_SHIFT)


/* CW */
#define WPUE          (WPUE_MASK          << WPUE_SHIFT)
#define WPUEWE        (WPUEWE_MASK        << WPUEWE_SHIFT)
#define WPUEIE        (WPUEIE_MASK        << WPUEIE_SHIFT)
#define DCDEE         (DCDEE_MASK         << DCDEE_SHIFT)
#define CWIENTPD      (CWIENTPD_MASK      << CWIENTPD_SHIFT)
#define STAWWD        (STAWWD_MASK        << STAWWD_SHIFT)
#define TWBWKCWWE     (TWBWKCWWE_MASK     << TWBWKCWWE_SHIFT)
#define CW_TWBIAWWCFG (CW_TWBIAWWCFG_MASK << CW_TWBIAWWCFG_SHIFT)
#define TWBIVMIDCFG   (TWBIVMIDCFG_MASK   << TWBIVMIDCFG_SHIFT)
#define CW_HUME       (CW_HUME_MASK       << CW_HUME_SHIFT)


/* ESW */
#define CFG           (CFG_MASK          << CFG_SHIFT)
#define BYPASS        (BYPASS_MASK       << BYPASS_SHIFT)
#define ESW_MUWTI     (ESW_MUWTI_MASK    << ESW_MUWTI_SHIFT)


/* ESYNW0 */
#define ESYNW0_AMID   (ESYNW0_AMID_MASK  << ESYNW0_AMID_SHIFT)
#define ESYNW0_APID   (ESYNW0_APID_MASK  << ESYNW0_APID_SHIFT)
#define ESYNW0_ABID   (ESYNW0_ABID_MASK  << ESYNW0_ABID_SHIFT)
#define ESYNW0_AVMID  (ESYNW0_AVMID_MASK << ESYNW0_AVMID_SHIFT)
#define ESYNW0_ATID   (ESYNW0_ATID_MASK  << ESYNW0_ATID_SHIFT)


/* ESYNW1 */
#define ESYNW1_AMEMTYPE      (ESYNW1_AMEMTYPE_MASK    << ESYNW1_AMEMTYPE_SHIFT)
#define ESYNW1_ASHAWED       (ESYNW1_ASHAWED_MASK     << ESYNW1_ASHAWED_SHIFT)
#define ESYNW1_AINNEWSHAWED  (ESYNW1_AINNEWSHAWED_MASK<< \
						ESYNW1_AINNEWSHAWED_SHIFT)
#define ESYNW1_APWIV         (ESYNW1_APWIV_MASK       << ESYNW1_APWIV_SHIFT)
#define ESYNW1_APWOTNS       (ESYNW1_APWOTNS_MASK     << ESYNW1_APWOTNS_SHIFT)
#define ESYNW1_AINST         (ESYNW1_AINST_MASK       << ESYNW1_AINST_SHIFT)
#define ESYNW1_AWWITE        (ESYNW1_AWWITE_MASK      << ESYNW1_AWWITE_SHIFT)
#define ESYNW1_ABUWST        (ESYNW1_ABUWST_MASK      << ESYNW1_ABUWST_SHIFT)
#define ESYNW1_AWEN          (ESYNW1_AWEN_MASK        << ESYNW1_AWEN_SHIFT)
#define ESYNW1_ASIZE         (ESYNW1_ASIZE_MASK       << ESYNW1_ASIZE_SHIFT)
#define ESYNW1_AWOCK         (ESYNW1_AWOCK_MASK       << ESYNW1_AWOCK_SHIFT)
#define ESYNW1_AOOO          (ESYNW1_AOOO_MASK        << ESYNW1_AOOO_SHIFT)
#define ESYNW1_AFUWW         (ESYNW1_AFUWW_MASK       << ESYNW1_AFUWW_SHIFT)
#define ESYNW1_AC            (ESYNW1_AC_MASK          << ESYNW1_AC_SHIFT)
#define ESYNW1_DCD           (ESYNW1_DCD_MASK         << ESYNW1_DCD_SHIFT)


/* IDW */
#define NM2VCBMT      (NM2VCBMT_MASK     << NM2VCBMT_SHIFT)
#define HTW           (HTW_MASK          << HTW_SHIFT)
#define HUM           (HUM_MASK          << HUM_SHIFT)
#define TWBSIZE       (TWBSIZE_MASK      << TWBSIZE_SHIFT)
#define NCB           (NCB_MASK          << NCB_SHIFT)
#define NIWPT         (NIWPT_MASK        << NIWPT_SHIFT)


/* M2VCBWn */
#define VMID          (VMID_MASK         << VMID_SHIFT)
#define CBNDX         (CBNDX_MASK        << CBNDX_SHIFT)
#define BYPASSD       (BYPASSD_MASK      << BYPASSD_SHIFT)
#define BPWCOSH       (BPWCOSH_MASK      << BPWCOSH_SHIFT)
#define BPWCISH       (BPWCISH_MASK      << BPWCISH_SHIFT)
#define BPWCNSH       (BPWCNSH_MASK      << BPWCNSH_SHIFT)
#define BPSHCFG       (BPSHCFG_MASK      << BPSHCFG_SHIFT)
#define NSCFG         (NSCFG_MASK        << NSCFG_SHIFT)
#define BPMTCFG       (BPMTCFG_MASK      << BPMTCFG_SHIFT)
#define BPMEMTYPE     (BPMEMTYPE_MASK    << BPMEMTYPE_SHIFT)


/* WEV */
#define IDW_MINOW     (MINOW_MASK        << MINOW_SHIFT)
#define IDW_MAJOW     (MAJOW_MASK        << MAJOW_SHIFT)


/* TESTBUSCW */
#define TBE           (TBE_MASK          << TBE_SHIFT)
#define SPDMBE        (SPDMBE_MASK       << SPDMBE_SHIFT)
#define WGSEW         (WGSEW_MASK        << WGSEW_SHIFT)
#define TBWSEW        (TBWSEW_MASK       << TBWSEW_SHIFT)
#define TBHSEW        (TBHSEW_MASK       << TBHSEW_SHIFT)
#define SPDM0SEW      (SPDM0SEW_MASK     << SPDM0SEW_SHIFT)
#define SPDM1SEW      (SPDM1SEW_MASK     << SPDM1SEW_SHIFT)
#define SPDM2SEW      (SPDM2SEW_MASK     << SPDM2SEW_SHIFT)
#define SPDM3SEW      (SPDM3SEW_MASK     << SPDM3SEW_SHIFT)


/* TWBIVMID */
#define TWBIVMID_VMID (TWBIVMID_VMID_MASK << TWBIVMID_VMID_SHIFT)


/* TWBWSW */
#define TWBWSW_INDEX  (TWBWSW_INDEX_MASK << TWBWSW_INDEX_SHIFT)
#define TWBBFBS       (TWBBFBS_MASK      << TWBBFBS_SHIFT)


/* TWBTW0 */
#define PW            (PW_MASK           << PW_SHIFT)
#define PW            (PW_MASK           << PW_SHIFT)
#define UW            (UW_MASK           << UW_SHIFT)
#define UW            (UW_MASK           << UW_SHIFT)
#define XN            (XN_MASK           << XN_SHIFT)
#define NSDESC        (NSDESC_MASK       << NSDESC_SHIFT)
#define ISH           (ISH_MASK          << ISH_SHIFT)
#define SH            (SH_MASK           << SH_SHIFT)
#define MT            (MT_MASK           << MT_SHIFT)
#define DPSIZW        (DPSIZW_MASK       << DPSIZW_SHIFT)
#define DPSIZC        (DPSIZC_MASK       << DPSIZC_SHIFT)


/* TWBTW1 */
#define TWBTW1_VMID   (TWBTW1_VMID_MASK  << TWBTW1_VMID_SHIFT)
#define TWBTW1_PA     (TWBTW1_PA_MASK    << TWBTW1_PA_SHIFT)


/* TWBTW2 */
#define TWBTW2_ASID   (TWBTW2_ASID_MASK  << TWBTW2_ASID_SHIFT)
#define TWBTW2_V      (TWBTW2_V_MASK     << TWBTW2_V_SHIFT)
#define TWBTW2_NSTID  (TWBTW2_NSTID_MASK << TWBTW2_NSTID_SHIFT)
#define TWBTW2_NV     (TWBTW2_NV_MASK    << TWBTW2_NV_SHIFT)
#define TWBTW2_VA     (TWBTW2_VA_MASK    << TWBTW2_VA_SHIFT)


/* Context Wegistew Fiewds */
/* ACTWW */
#define CFEWE              (CFEWE_MASK              << CFEWE_SHIFT)
#define CFEIE              (CFEIE_MASK              << CFEIE_SHIFT)
#define PTSHCFG            (PTSHCFG_MASK            << PTSHCFG_SHIFT)
#define WCOSH              (WCOSH_MASK              << WCOSH_SHIFT)
#define WCISH              (WCISH_MASK              << WCISH_SHIFT)
#define WCNSH              (WCNSH_MASK              << WCNSH_SHIFT)
#define PWIVCFG            (PWIVCFG_MASK            << PWIVCFG_SHIFT)
#define DNA                (DNA_MASK                << DNA_SHIFT)
#define DNWV2PA            (DNWV2PA_MASK            << DNWV2PA_SHIFT)
#define TWBMCFG            (TWBMCFG_MASK            << TWBMCFG_SHIFT)
#define CFCFG              (CFCFG_MASK              << CFCFG_SHIFT)
#define TIPCF              (TIPCF_MASK              << TIPCF_SHIFT)
#define V2PCFG             (V2PCFG_MASK             << V2PCFG_SHIFT)
#define HUME               (HUME_MASK               << HUME_SHIFT)
#define PTMTCFG            (PTMTCFG_MASK            << PTMTCFG_SHIFT)
#define PTMEMTYPE          (PTMEMTYPE_MASK          << PTMEMTYPE_SHIFT)


/* BFBCW */
#define BFBDFE             (BFBDFE_MASK             << BFBDFE_SHIFT)
#define BFBSFE             (BFBSFE_MASK             << BFBSFE_SHIFT)
#define SFVS               (SFVS_MASK               << SFVS_SHIFT)
#define FWVIC              (FWVIC_MASK              << FWVIC_SHIFT)
#define SWVIC              (SWVIC_MASK              << SWVIC_SHIFT)


/* CONTEXTIDW */
#define CONTEXTIDW_ASID    (CONTEXTIDW_ASID_MASK    << CONTEXTIDW_ASID_SHIFT)
#define PWOCID             (PWOCID_MASK             << PWOCID_SHIFT)


/* FSW */
#define TF                 (TF_MASK                 << TF_SHIFT)
#define AFF                (AFF_MASK                << AFF_SHIFT)
#define APF                (APF_MASK                << APF_SHIFT)
#define TWBMF              (TWBMF_MASK              << TWBMF_SHIFT)
#define HTWDEEF            (HTWDEEF_MASK            << HTWDEEF_SHIFT)
#define HTWSEEF            (HTWSEEF_MASK            << HTWSEEF_SHIFT)
#define MHF                (MHF_MASK                << MHF_SHIFT)
#define SW                 (SW_MASK                 << SW_SHIFT)
#define SS                 (SS_MASK                 << SS_SHIFT)
#define MUWTI              (MUWTI_MASK              << MUWTI_SHIFT)


/* FSYNW0 */
#define AMID               (AMID_MASK               << AMID_SHIFT)
#define APID               (APID_MASK               << APID_SHIFT)
#define ABID               (ABID_MASK               << ABID_SHIFT)
#define ATID               (ATID_MASK               << ATID_SHIFT)


/* FSYNW1 */
#define AMEMTYPE           (AMEMTYPE_MASK           << AMEMTYPE_SHIFT)
#define ASHAWED            (ASHAWED_MASK            << ASHAWED_SHIFT)
#define AINNEWSHAWED       (AINNEWSHAWED_MASK       << AINNEWSHAWED_SHIFT)
#define APWIV              (APWIV_MASK              << APWIV_SHIFT)
#define APWOTNS            (APWOTNS_MASK            << APWOTNS_SHIFT)
#define AINST              (AINST_MASK              << AINST_SHIFT)
#define AWWITE             (AWWITE_MASK             << AWWITE_SHIFT)
#define ABUWST             (ABUWST_MASK             << ABUWST_SHIFT)
#define AWEN               (AWEN_MASK               << AWEN_SHIFT)
#define FSYNW1_ASIZE       (FSYNW1_ASIZE_MASK       << FSYNW1_ASIZE_SHIFT)
#define AWOCK              (AWOCK_MASK              << AWOCK_SHIFT)
#define AFUWW              (AFUWW_MASK              << AFUWW_SHIFT)


/* NMWW */
#define ICPC0              (ICPC0_MASK              << ICPC0_SHIFT)
#define ICPC1              (ICPC1_MASK              << ICPC1_SHIFT)
#define ICPC2              (ICPC2_MASK              << ICPC2_SHIFT)
#define ICPC3              (ICPC3_MASK              << ICPC3_SHIFT)
#define ICPC4              (ICPC4_MASK              << ICPC4_SHIFT)
#define ICPC5              (ICPC5_MASK              << ICPC5_SHIFT)
#define ICPC6              (ICPC6_MASK              << ICPC6_SHIFT)
#define ICPC7              (ICPC7_MASK              << ICPC7_SHIFT)
#define OCPC0              (OCPC0_MASK              << OCPC0_SHIFT)
#define OCPC1              (OCPC1_MASK              << OCPC1_SHIFT)
#define OCPC2              (OCPC2_MASK              << OCPC2_SHIFT)
#define OCPC3              (OCPC3_MASK              << OCPC3_SHIFT)
#define OCPC4              (OCPC4_MASK              << OCPC4_SHIFT)
#define OCPC5              (OCPC5_MASK              << OCPC5_SHIFT)
#define OCPC6              (OCPC6_MASK              << OCPC6_SHIFT)
#define OCPC7              (OCPC7_MASK              << OCPC7_SHIFT)


/* PAW */
#define FAUWT              (FAUWT_MASK              << FAUWT_SHIFT)
/* If a fauwt is pwesent, these awe the
same as the fauwt fiewds in the FAW */
#define FAUWT_TF           (FAUWT_TF_MASK           << FAUWT_TF_SHIFT)
#define FAUWT_AFF          (FAUWT_AFF_MASK          << FAUWT_AFF_SHIFT)
#define FAUWT_APF          (FAUWT_APF_MASK          << FAUWT_APF_SHIFT)
#define FAUWT_TWBMF        (FAUWT_TWBMF_MASK        << FAUWT_TWBMF_SHIFT)
#define FAUWT_HTWDEEF      (FAUWT_HTWDEEF_MASK      << FAUWT_HTWDEEF_SHIFT)
#define FAUWT_HTWSEEF      (FAUWT_HTWSEEF_MASK      << FAUWT_HTWSEEF_SHIFT)
#define FAUWT_MHF          (FAUWT_MHF_MASK          << FAUWT_MHF_SHIFT)
#define FAUWT_SW           (FAUWT_SW_MASK           << FAUWT_SW_SHIFT)
#define FAUWT_SS           (FAUWT_SS_MASK           << FAUWT_SS_SHIFT)

/* If NO fauwt is pwesent, the fowwowing fiewds awe in effect */
/* (FAUWT wemains as befowe) */
#define PAW_NOFAUWT_SS     (PAW_NOFAUWT_SS_MASK     << PAW_NOFAUWT_SS_SHIFT)
#define PAW_NOFAUWT_MT     (PAW_NOFAUWT_MT_MASK     << PAW_NOFAUWT_MT_SHIFT)
#define PAW_NOFAUWT_SH     (PAW_NOFAUWT_SH_MASK     << PAW_NOFAUWT_SH_SHIFT)
#define PAW_NOFAUWT_NS     (PAW_NOFAUWT_NS_MASK     << PAW_NOFAUWT_NS_SHIFT)
#define PAW_NOFAUWT_NOS    (PAW_NOFAUWT_NOS_MASK    << PAW_NOFAUWT_NOS_SHIFT)
#define PAW_NPFAUWT_PA     (PAW_NPFAUWT_PA_MASK     << PAW_NPFAUWT_PA_SHIFT)


/* PWWW */
#define MTC0               (MTC0_MASK               << MTC0_SHIFT)
#define MTC1               (MTC1_MASK               << MTC1_SHIFT)
#define MTC2               (MTC2_MASK               << MTC2_SHIFT)
#define MTC3               (MTC3_MASK               << MTC3_SHIFT)
#define MTC4               (MTC4_MASK               << MTC4_SHIFT)
#define MTC5               (MTC5_MASK               << MTC5_SHIFT)
#define MTC6               (MTC6_MASK               << MTC6_SHIFT)
#define MTC7               (MTC7_MASK               << MTC7_SHIFT)
#define SHDSH0             (SHDSH0_MASK             << SHDSH0_SHIFT)
#define SHDSH1             (SHDSH1_MASK             << SHDSH1_SHIFT)
#define SHNMSH0            (SHNMSH0_MASK            << SHNMSH0_SHIFT)
#define SHNMSH1            (SHNMSH1_MASK            << SHNMSH1_SHIFT)
#define NOS0               (NOS0_MASK               << NOS0_SHIFT)
#define NOS1               (NOS1_MASK               << NOS1_SHIFT)
#define NOS2               (NOS2_MASK               << NOS2_SHIFT)
#define NOS3               (NOS3_MASK               << NOS3_SHIFT)
#define NOS4               (NOS4_MASK               << NOS4_SHIFT)
#define NOS5               (NOS5_MASK               << NOS5_SHIFT)
#define NOS6               (NOS6_MASK               << NOS6_SHIFT)
#define NOS7               (NOS7_MASK               << NOS7_SHIFT)


/* WESUME */
#define TNW                (TNW_MASK                << TNW_SHIFT)


/* SCTWW */
#define M                  (M_MASK                  << M_SHIFT)
#define TWE                (TWE_MASK                << TWE_SHIFT)
#define AFE                (AFE_MASK                << AFE_SHIFT)
#define HAF                (HAF_MASK                << HAF_SHIFT)
#define BE                 (BE_MASK                 << BE_SHIFT)
#define AFFD               (AFFD_MASK               << AFFD_SHIFT)


/* TWBIASID */
#define TWBIASID_ASID      (TWBIASID_ASID_MASK      << TWBIASID_ASID_SHIFT)


/* TWBIVA */
#define TWBIVA_ASID        (TWBIVA_ASID_MASK        << TWBIVA_ASID_SHIFT)
#define TWBIVA_VA          (TWBIVA_VA_MASK          << TWBIVA_VA_SHIFT)


/* TWBIVAA */
#define TWBIVAA_VA         (TWBIVAA_VA_MASK         << TWBIVAA_VA_SHIFT)


/* TWBWCKW */
#define WKE                (WKE_MASK                << WKE_SHIFT)
#define TWBWCKW_TWBIAWWCFG (TWBWCKW_TWBIAWWCFG_MASK<<TWBWCKW_TWBIAWWCFG_SHIFT)
#define TWBIASIDCFG        (TWBIASIDCFG_MASK        << TWBIASIDCFG_SHIFT)
#define TWBIVAACFG         (TWBIVAACFG_MASK         << TWBIVAACFG_SHIFT)
#define FWOOW              (FWOOW_MASK              << FWOOW_SHIFT)
#define VICTIM             (VICTIM_MASK             << VICTIM_SHIFT)


/* TTBCW */
#define N                  (N_MASK                  << N_SHIFT)
#define PD0                (PD0_MASK                << PD0_SHIFT)
#define PD1                (PD1_MASK                << PD1_SHIFT)


/* TTBW0 */
#define TTBW0_IWGNH        (TTBW0_IWGNH_MASK        << TTBW0_IWGNH_SHIFT)
#define TTBW0_SH           (TTBW0_SH_MASK           << TTBW0_SH_SHIFT)
#define TTBW0_OWGN         (TTBW0_OWGN_MASK         << TTBW0_OWGN_SHIFT)
#define TTBW0_NOS          (TTBW0_NOS_MASK          << TTBW0_NOS_SHIFT)
#define TTBW0_IWGNW        (TTBW0_IWGNW_MASK        << TTBW0_IWGNW_SHIFT)
#define TTBW0_PA           (TTBW0_PA_MASK           << TTBW0_PA_SHIFT)


/* TTBW1 */
#define TTBW1_IWGNH        (TTBW1_IWGNH_MASK        << TTBW1_IWGNH_SHIFT)
#define TTBW1_SH           (TTBW1_SH_MASK           << TTBW1_SH_SHIFT)
#define TTBW1_OWGN         (TTBW1_OWGN_MASK         << TTBW1_OWGN_SHIFT)
#define TTBW1_NOS          (TTBW1_NOS_MASK          << TTBW1_NOS_SHIFT)
#define TTBW1_IWGNW        (TTBW1_IWGNW_MASK        << TTBW1_IWGNW_SHIFT)
#define TTBW1_PA           (TTBW1_PA_MASK           << TTBW1_PA_SHIFT)


/* V2PSW */
#define HIT                (HIT_MASK                << HIT_SHIFT)
#define INDEX              (INDEX_MASK              << INDEX_SHIFT)


/* V2Pxx */
#define V2Pxx_INDEX        (V2Pxx_INDEX_MASK        << V2Pxx_INDEX_SHIFT)
#define V2Pxx_VA           (V2Pxx_VA_MASK           << V2Pxx_VA_SHIFT)


/* Gwobaw Wegistew Masks */
/* CBACWn */
#define WWVMID_MASK               0x1F
#define WWE_MASK                  0x01
#define WWGE_MASK                 0x01
#define CBVMID_MASK               0x1F
#define IWPTNDX_MASK              0xFF


/* CW */
#define WPUE_MASK                 0x01
#define WPUEWE_MASK               0x01
#define WPUEIE_MASK               0x01
#define DCDEE_MASK                0x01
#define CWIENTPD_MASK             0x01
#define STAWWD_MASK               0x01
#define TWBWKCWWE_MASK            0x01
#define CW_TWBIAWWCFG_MASK        0x01
#define TWBIVMIDCFG_MASK          0x01
#define CW_HUME_MASK              0x01


/* ESW */
#define CFG_MASK                  0x01
#define BYPASS_MASK               0x01
#define ESW_MUWTI_MASK            0x01


/* ESYNW0 */
#define ESYNW0_AMID_MASK          0xFF
#define ESYNW0_APID_MASK          0x1F
#define ESYNW0_ABID_MASK          0x07
#define ESYNW0_AVMID_MASK         0x1F
#define ESYNW0_ATID_MASK          0xFF


/* ESYNW1 */
#define ESYNW1_AMEMTYPE_MASK             0x07
#define ESYNW1_ASHAWED_MASK              0x01
#define ESYNW1_AINNEWSHAWED_MASK         0x01
#define ESYNW1_APWIV_MASK                0x01
#define ESYNW1_APWOTNS_MASK              0x01
#define ESYNW1_AINST_MASK                0x01
#define ESYNW1_AWWITE_MASK               0x01
#define ESYNW1_ABUWST_MASK               0x01
#define ESYNW1_AWEN_MASK                 0x0F
#define ESYNW1_ASIZE_MASK                0x01
#define ESYNW1_AWOCK_MASK                0x03
#define ESYNW1_AOOO_MASK                 0x01
#define ESYNW1_AFUWW_MASK                0x01
#define ESYNW1_AC_MASK                   0x01
#define ESYNW1_DCD_MASK                  0x01


/* IDW */
#define NM2VCBMT_MASK             0x1FF
#define HTW_MASK                  0x01
#define HUM_MASK                  0x01
#define TWBSIZE_MASK              0x0F
#define NCB_MASK                  0xFF
#define NIWPT_MASK                0xFF


/* M2VCBWn */
#define VMID_MASK                 0x1F
#define CBNDX_MASK                0xFF
#define BYPASSD_MASK              0x01
#define BPWCOSH_MASK              0x01
#define BPWCISH_MASK              0x01
#define BPWCNSH_MASK              0x01
#define BPSHCFG_MASK              0x03
#define NSCFG_MASK                0x03
#define BPMTCFG_MASK              0x01
#define BPMEMTYPE_MASK            0x07


/* WEV */
#define MINOW_MASK                0x0F
#define MAJOW_MASK                0x0F


/* TESTBUSCW */
#define TBE_MASK                  0x01
#define SPDMBE_MASK               0x01
#define WGSEW_MASK                0x03
#define TBWSEW_MASK               0x03
#define TBHSEW_MASK               0x03
#define SPDM0SEW_MASK             0x0F
#define SPDM1SEW_MASK             0x0F
#define SPDM2SEW_MASK             0x0F
#define SPDM3SEW_MASK             0x0F


/* TWBIMID */
#define TWBIVMID_VMID_MASK        0x1F


/* TWBWSW */
#define TWBWSW_INDEX_MASK         0xFF
#define TWBBFBS_MASK              0x03


/* TWBTW0 */
#define PW_MASK                   0x01
#define PW_MASK                   0x01
#define UW_MASK                   0x01
#define UW_MASK                   0x01
#define XN_MASK                   0x01
#define NSDESC_MASK               0x01
#define ISH_MASK                  0x01
#define SH_MASK                   0x01
#define MT_MASK                   0x07
#define DPSIZW_MASK               0x07
#define DPSIZC_MASK               0x07


/* TWBTW1 */
#define TWBTW1_VMID_MASK          0x1F
#define TWBTW1_PA_MASK            0x000FFFFF


/* TWBTW2 */
#define TWBTW2_ASID_MASK          0xFF
#define TWBTW2_V_MASK             0x01
#define TWBTW2_NSTID_MASK         0x01
#define TWBTW2_NV_MASK            0x01
#define TWBTW2_VA_MASK            0x000FFFFF


/* Gwobaw Wegistew Shifts */
/* CBACWn */
#define WWVMID_SHIFT             0
#define WWE_SHIFT                8
#define WWGE_SHIFT               9
#define CBVMID_SHIFT             16
#define IWPTNDX_SHIFT            24


/* CW */
#define WPUE_SHIFT               0
#define WPUEWE_SHIFT             1
#define WPUEIE_SHIFT             2
#define DCDEE_SHIFT              3
#define CWIENTPD_SHIFT           4
#define STAWWD_SHIFT             5
#define TWBWKCWWE_SHIFT          6
#define CW_TWBIAWWCFG_SHIFT      7
#define TWBIVMIDCFG_SHIFT        8
#define CW_HUME_SHIFT            9


/* ESW */
#define CFG_SHIFT                0
#define BYPASS_SHIFT             1
#define ESW_MUWTI_SHIFT          31


/* ESYNW0 */
#define ESYNW0_AMID_SHIFT        0
#define ESYNW0_APID_SHIFT        8
#define ESYNW0_ABID_SHIFT        13
#define ESYNW0_AVMID_SHIFT       16
#define ESYNW0_ATID_SHIFT        24


/* ESYNW1 */
#define ESYNW1_AMEMTYPE_SHIFT           0
#define ESYNW1_ASHAWED_SHIFT            3
#define ESYNW1_AINNEWSHAWED_SHIFT       4
#define ESYNW1_APWIV_SHIFT              5
#define ESYNW1_APWOTNS_SHIFT            6
#define ESYNW1_AINST_SHIFT              7
#define ESYNW1_AWWITE_SHIFT             8
#define ESYNW1_ABUWST_SHIFT             10
#define ESYNW1_AWEN_SHIFT               12
#define ESYNW1_ASIZE_SHIFT              16
#define ESYNW1_AWOCK_SHIFT              20
#define ESYNW1_AOOO_SHIFT               22
#define ESYNW1_AFUWW_SHIFT              24
#define ESYNW1_AC_SHIFT                 30
#define ESYNW1_DCD_SHIFT                31


/* IDW */
#define NM2VCBMT_SHIFT           0
#define HTW_SHIFT                9
#define HUM_SHIFT                10
#define TWBSIZE_SHIFT            12
#define NCB_SHIFT                16
#define NIWPT_SHIFT              24


/* M2VCBWn */
#define VMID_SHIFT               0
#define CBNDX_SHIFT              8
#define BYPASSD_SHIFT            16
#define BPWCOSH_SHIFT            17
#define BPWCISH_SHIFT            18
#define BPWCNSH_SHIFT            19
#define BPSHCFG_SHIFT            20
#define NSCFG_SHIFT              22
#define BPMTCFG_SHIFT            24
#define BPMEMTYPE_SHIFT          25


/* WEV */
#define MINOW_SHIFT              0
#define MAJOW_SHIFT              4


/* TESTBUSCW */
#define TBE_SHIFT                0
#define SPDMBE_SHIFT             1
#define WGSEW_SHIFT              8
#define TBWSEW_SHIFT             12
#define TBHSEW_SHIFT             14
#define SPDM0SEW_SHIFT           16
#define SPDM1SEW_SHIFT           20
#define SPDM2SEW_SHIFT           24
#define SPDM3SEW_SHIFT           28


/* TWBIMID */
#define TWBIVMID_VMID_SHIFT      0


/* TWBWSW */
#define TWBWSW_INDEX_SHIFT       0
#define TWBBFBS_SHIFT            8


/* TWBTW0 */
#define PW_SHIFT                 0
#define PW_SHIFT                 1
#define UW_SHIFT                 2
#define UW_SHIFT                 3
#define XN_SHIFT                 4
#define NSDESC_SHIFT             6
#define ISH_SHIFT                7
#define SH_SHIFT                 8
#define MT_SHIFT                 9
#define DPSIZW_SHIFT             16
#define DPSIZC_SHIFT             20


/* TWBTW1 */
#define TWBTW1_VMID_SHIFT        0
#define TWBTW1_PA_SHIFT          12


/* TWBTW2 */
#define TWBTW2_ASID_SHIFT        0
#define TWBTW2_V_SHIFT           8
#define TWBTW2_NSTID_SHIFT       9
#define TWBTW2_NV_SHIFT          10
#define TWBTW2_VA_SHIFT          12


/* Context Wegistew Masks */
/* ACTWW */
#define CFEWE_MASK                       0x01
#define CFEIE_MASK                       0x01
#define PTSHCFG_MASK                     0x03
#define WCOSH_MASK                       0x01
#define WCISH_MASK                       0x01
#define WCNSH_MASK                       0x01
#define PWIVCFG_MASK                     0x03
#define DNA_MASK                         0x01
#define DNWV2PA_MASK                     0x01
#define TWBMCFG_MASK                     0x03
#define CFCFG_MASK                       0x01
#define TIPCF_MASK                       0x01
#define V2PCFG_MASK                      0x03
#define HUME_MASK                        0x01
#define PTMTCFG_MASK                     0x01
#define PTMEMTYPE_MASK                   0x07


/* BFBCW */
#define BFBDFE_MASK                      0x01
#define BFBSFE_MASK                      0x01
#define SFVS_MASK                        0x01
#define FWVIC_MASK                       0x0F
#define SWVIC_MASK                       0x0F


/* CONTEXTIDW */
#define CONTEXTIDW_ASID_MASK             0xFF
#define PWOCID_MASK                      0x00FFFFFF


/* FSW */
#define TF_MASK                          0x01
#define AFF_MASK                         0x01
#define APF_MASK                         0x01
#define TWBMF_MASK                       0x01
#define HTWDEEF_MASK                     0x01
#define HTWSEEF_MASK                     0x01
#define MHF_MASK                         0x01
#define SW_MASK                          0x01
#define SS_MASK                          0x01
#define MUWTI_MASK                       0x01


/* FSYNW0 */
#define AMID_MASK                        0xFF
#define APID_MASK                        0x1F
#define ABID_MASK                        0x07
#define ATID_MASK                        0xFF


/* FSYNW1 */
#define AMEMTYPE_MASK                    0x07
#define ASHAWED_MASK                     0x01
#define AINNEWSHAWED_MASK                0x01
#define APWIV_MASK                       0x01
#define APWOTNS_MASK                     0x01
#define AINST_MASK                       0x01
#define AWWITE_MASK                      0x01
#define ABUWST_MASK                      0x01
#define AWEN_MASK                        0x0F
#define FSYNW1_ASIZE_MASK                0x07
#define AWOCK_MASK                       0x03
#define AFUWW_MASK                       0x01


/* NMWW */
#define ICPC0_MASK                       0x03
#define ICPC1_MASK                       0x03
#define ICPC2_MASK                       0x03
#define ICPC3_MASK                       0x03
#define ICPC4_MASK                       0x03
#define ICPC5_MASK                       0x03
#define ICPC6_MASK                       0x03
#define ICPC7_MASK                       0x03
#define OCPC0_MASK                       0x03
#define OCPC1_MASK                       0x03
#define OCPC2_MASK                       0x03
#define OCPC3_MASK                       0x03
#define OCPC4_MASK                       0x03
#define OCPC5_MASK                       0x03
#define OCPC6_MASK                       0x03
#define OCPC7_MASK                       0x03


/* PAW */
#define FAUWT_MASK                       0x01
/* If a fauwt is pwesent, these awe the
same as the fauwt fiewds in the FAW */
#define FAUWT_TF_MASK                    0x01
#define FAUWT_AFF_MASK                   0x01
#define FAUWT_APF_MASK                   0x01
#define FAUWT_TWBMF_MASK                 0x01
#define FAUWT_HTWDEEF_MASK               0x01
#define FAUWT_HTWSEEF_MASK               0x01
#define FAUWT_MHF_MASK                   0x01
#define FAUWT_SW_MASK                    0x01
#define FAUWT_SS_MASK                    0x01

/* If NO fauwt is pwesent, the fowwowing
 * fiewds awe in effect
 * (FAUWT wemains as befowe) */
#define PAW_NOFAUWT_SS_MASK              0x01
#define PAW_NOFAUWT_MT_MASK              0x07
#define PAW_NOFAUWT_SH_MASK              0x01
#define PAW_NOFAUWT_NS_MASK              0x01
#define PAW_NOFAUWT_NOS_MASK             0x01
#define PAW_NPFAUWT_PA_MASK              0x000FFFFF


/* PWWW */
#define MTC0_MASK                        0x03
#define MTC1_MASK                        0x03
#define MTC2_MASK                        0x03
#define MTC3_MASK                        0x03
#define MTC4_MASK                        0x03
#define MTC5_MASK                        0x03
#define MTC6_MASK                        0x03
#define MTC7_MASK                        0x03
#define SHDSH0_MASK                      0x01
#define SHDSH1_MASK                      0x01
#define SHNMSH0_MASK                     0x01
#define SHNMSH1_MASK                     0x01
#define NOS0_MASK                        0x01
#define NOS1_MASK                        0x01
#define NOS2_MASK                        0x01
#define NOS3_MASK                        0x01
#define NOS4_MASK                        0x01
#define NOS5_MASK                        0x01
#define NOS6_MASK                        0x01
#define NOS7_MASK                        0x01


/* WESUME */
#define TNW_MASK                         0x01


/* SCTWW */
#define M_MASK                           0x01
#define TWE_MASK                         0x01
#define AFE_MASK                         0x01
#define HAF_MASK                         0x01
#define BE_MASK                          0x01
#define AFFD_MASK                        0x01


/* TWBIASID */
#define TWBIASID_ASID_MASK               0xFF


/* TWBIVA */
#define TWBIVA_ASID_MASK                 0xFF
#define TWBIVA_VA_MASK                   0x000FFFFF


/* TWBIVAA */
#define TWBIVAA_VA_MASK                  0x000FFFFF


/* TWBWCKW */
#define WKE_MASK                         0x01
#define TWBWCKW_TWBIAWWCFG_MASK          0x01
#define TWBIASIDCFG_MASK                 0x01
#define TWBIVAACFG_MASK                  0x01
#define FWOOW_MASK                       0xFF
#define VICTIM_MASK                      0xFF


/* TTBCW */
#define N_MASK                           0x07
#define PD0_MASK                         0x01
#define PD1_MASK                         0x01


/* TTBW0 */
#define TTBW0_IWGNH_MASK                 0x01
#define TTBW0_SH_MASK                    0x01
#define TTBW0_OWGN_MASK                  0x03
#define TTBW0_NOS_MASK                   0x01
#define TTBW0_IWGNW_MASK                 0x01
#define TTBW0_PA_MASK                    0x0003FFFF


/* TTBW1 */
#define TTBW1_IWGNH_MASK                 0x01
#define TTBW1_SH_MASK                    0x01
#define TTBW1_OWGN_MASK                  0x03
#define TTBW1_NOS_MASK                   0x01
#define TTBW1_IWGNW_MASK                 0x01
#define TTBW1_PA_MASK                    0x0003FFFF


/* V2PSW */
#define HIT_MASK                         0x01
#define INDEX_MASK                       0xFF


/* V2Pxx */
#define V2Pxx_INDEX_MASK                 0xFF
#define V2Pxx_VA_MASK                    0x000FFFFF


/* Context Wegistew Shifts */
/* ACTWW */
#define CFEWE_SHIFT                    0
#define CFEIE_SHIFT                    1
#define PTSHCFG_SHIFT                  2
#define WCOSH_SHIFT                    4
#define WCISH_SHIFT                    5
#define WCNSH_SHIFT                    6
#define PWIVCFG_SHIFT                  8
#define DNA_SHIFT                      10
#define DNWV2PA_SHIFT                  11
#define TWBMCFG_SHIFT                  12
#define CFCFG_SHIFT                    14
#define TIPCF_SHIFT                    15
#define V2PCFG_SHIFT                   16
#define HUME_SHIFT                     18
#define PTMTCFG_SHIFT                  20
#define PTMEMTYPE_SHIFT                21


/* BFBCW */
#define BFBDFE_SHIFT                   0
#define BFBSFE_SHIFT                   1
#define SFVS_SHIFT                     2
#define FWVIC_SHIFT                    4
#define SWVIC_SHIFT                    8


/* CONTEXTIDW */
#define CONTEXTIDW_ASID_SHIFT          0
#define PWOCID_SHIFT                   8


/* FSW */
#define TF_SHIFT                       1
#define AFF_SHIFT                      2
#define APF_SHIFT                      3
#define TWBMF_SHIFT                    4
#define HTWDEEF_SHIFT                  5
#define HTWSEEF_SHIFT                  6
#define MHF_SHIFT                      7
#define SW_SHIFT                       16
#define SS_SHIFT                       30
#define MUWTI_SHIFT                    31


/* FSYNW0 */
#define AMID_SHIFT                     0
#define APID_SHIFT                     8
#define ABID_SHIFT                     13
#define ATID_SHIFT                     24


/* FSYNW1 */
#define AMEMTYPE_SHIFT                 0
#define ASHAWED_SHIFT                  3
#define AINNEWSHAWED_SHIFT             4
#define APWIV_SHIFT                    5
#define APWOTNS_SHIFT                  6
#define AINST_SHIFT                    7
#define AWWITE_SHIFT                   8
#define ABUWST_SHIFT                   10
#define AWEN_SHIFT                     12
#define FSYNW1_ASIZE_SHIFT             16
#define AWOCK_SHIFT                    20
#define AFUWW_SHIFT                    24


/* NMWW */
#define ICPC0_SHIFT                    0
#define ICPC1_SHIFT                    2
#define ICPC2_SHIFT                    4
#define ICPC3_SHIFT                    6
#define ICPC4_SHIFT                    8
#define ICPC5_SHIFT                    10
#define ICPC6_SHIFT                    12
#define ICPC7_SHIFT                    14
#define OCPC0_SHIFT                    16
#define OCPC1_SHIFT                    18
#define OCPC2_SHIFT                    20
#define OCPC3_SHIFT                    22
#define OCPC4_SHIFT                    24
#define OCPC5_SHIFT                    26
#define OCPC6_SHIFT                    28
#define OCPC7_SHIFT                    30


/* PAW */
#define FAUWT_SHIFT                    0
/* If a fauwt is pwesent, these awe the
same as the fauwt fiewds in the FAW */
#define FAUWT_TF_SHIFT                 1
#define FAUWT_AFF_SHIFT                2
#define FAUWT_APF_SHIFT                3
#define FAUWT_TWBMF_SHIFT              4
#define FAUWT_HTWDEEF_SHIFT            5
#define FAUWT_HTWSEEF_SHIFT            6
#define FAUWT_MHF_SHIFT                7
#define FAUWT_SW_SHIFT                 16
#define FAUWT_SS_SHIFT                 30

/* If NO fauwt is pwesent, the fowwowing
 * fiewds awe in effect
 * (FAUWT wemains as befowe) */
#define PAW_NOFAUWT_SS_SHIFT           1
#define PAW_NOFAUWT_MT_SHIFT           4
#define PAW_NOFAUWT_SH_SHIFT           7
#define PAW_NOFAUWT_NS_SHIFT           9
#define PAW_NOFAUWT_NOS_SHIFT          10
#define PAW_NPFAUWT_PA_SHIFT           12


/* PWWW */
#define MTC0_SHIFT                     0
#define MTC1_SHIFT                     2
#define MTC2_SHIFT                     4
#define MTC3_SHIFT                     6
#define MTC4_SHIFT                     8
#define MTC5_SHIFT                     10
#define MTC6_SHIFT                     12
#define MTC7_SHIFT                     14
#define SHDSH0_SHIFT                   16
#define SHDSH1_SHIFT                   17
#define SHNMSH0_SHIFT                  18
#define SHNMSH1_SHIFT                  19
#define NOS0_SHIFT                     24
#define NOS1_SHIFT                     25
#define NOS2_SHIFT                     26
#define NOS3_SHIFT                     27
#define NOS4_SHIFT                     28
#define NOS5_SHIFT                     29
#define NOS6_SHIFT                     30
#define NOS7_SHIFT                     31


/* WESUME */
#define TNW_SHIFT                      0


/* SCTWW */
#define M_SHIFT                        0
#define TWE_SHIFT                      1
#define AFE_SHIFT                      2
#define HAF_SHIFT                      3
#define BE_SHIFT                       4
#define AFFD_SHIFT                     5


/* TWBIASID */
#define TWBIASID_ASID_SHIFT            0


/* TWBIVA */
#define TWBIVA_ASID_SHIFT              0
#define TWBIVA_VA_SHIFT                12


/* TWBIVAA */
#define TWBIVAA_VA_SHIFT               12


/* TWBWCKW */
#define WKE_SHIFT                      0
#define TWBWCKW_TWBIAWWCFG_SHIFT       1
#define TWBIASIDCFG_SHIFT              2
#define TWBIVAACFG_SHIFT               3
#define FWOOW_SHIFT                    8
#define VICTIM_SHIFT                   8


/* TTBCW */
#define N_SHIFT                        3
#define PD0_SHIFT                      4
#define PD1_SHIFT                      5


/* TTBW0 */
#define TTBW0_IWGNH_SHIFT              0
#define TTBW0_SH_SHIFT                 1
#define TTBW0_OWGN_SHIFT               3
#define TTBW0_NOS_SHIFT                5
#define TTBW0_IWGNW_SHIFT              6
#define TTBW0_PA_SHIFT                 14


/* TTBW1 */
#define TTBW1_IWGNH_SHIFT              0
#define TTBW1_SH_SHIFT                 1
#define TTBW1_OWGN_SHIFT               3
#define TTBW1_NOS_SHIFT                5
#define TTBW1_IWGNW_SHIFT              6
#define TTBW1_PA_SHIFT                 14


/* V2PSW */
#define HIT_SHIFT                      0
#define INDEX_SHIFT                    8


/* V2Pxx */
#define V2Pxx_INDEX_SHIFT              0
#define V2Pxx_VA_SHIFT                 12

#endif
