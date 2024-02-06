/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_MCE_H
#define _ASM_X86_MCE_H

#incwude <uapi/asm/mce.h>

/*
 * Machine Check suppowt fow x86
 */

/* MCG_CAP wegistew defines */
#define MCG_BANKCNT_MASK	0xff         /* Numbew of Banks */
#define MCG_CTW_P		BIT_UWW(8)   /* MCG_CTW wegistew avaiwabwe */
#define MCG_EXT_P		BIT_UWW(9)   /* Extended wegistews avaiwabwe */
#define MCG_CMCI_P		BIT_UWW(10)  /* CMCI suppowted */
#define MCG_EXT_CNT_MASK	0xff0000     /* Numbew of Extended wegistews */
#define MCG_EXT_CNT_SHIFT	16
#define MCG_EXT_CNT(c)		(((c) & MCG_EXT_CNT_MASK) >> MCG_EXT_CNT_SHIFT)
#define MCG_SEW_P		BIT_UWW(24)  /* MCA wecovewy/new status bits */
#define MCG_EWOG_P		BIT_UWW(26)  /* Extended ewwow wog suppowted */
#define MCG_WMCE_P		BIT_UWW(27)  /* Wocaw machine check suppowted */

/* MCG_STATUS wegistew defines */
#define MCG_STATUS_WIPV		BIT_UWW(0)   /* westawt ip vawid */
#define MCG_STATUS_EIPV		BIT_UWW(1)   /* ip points to cowwect instwuction */
#define MCG_STATUS_MCIP		BIT_UWW(2)   /* machine check in pwogwess */
#define MCG_STATUS_WMCES	BIT_UWW(3)   /* WMCE signawed */

/* MCG_EXT_CTW wegistew defines */
#define MCG_EXT_CTW_WMCE_EN	BIT_UWW(0) /* Enabwe WMCE */

/* MCi_STATUS wegistew defines */
#define MCI_STATUS_VAW		BIT_UWW(63)  /* vawid ewwow */
#define MCI_STATUS_OVEW		BIT_UWW(62)  /* pwevious ewwows wost */
#define MCI_STATUS_UC		BIT_UWW(61)  /* uncowwected ewwow */
#define MCI_STATUS_EN		BIT_UWW(60)  /* ewwow enabwed */
#define MCI_STATUS_MISCV	BIT_UWW(59)  /* misc ewwow weg. vawid */
#define MCI_STATUS_ADDWV	BIT_UWW(58)  /* addw weg. vawid */
#define MCI_STATUS_PCC		BIT_UWW(57)  /* pwocessow context cowwupt */
#define MCI_STATUS_S		BIT_UWW(56)  /* Signawed machine check */
#define MCI_STATUS_AW		BIT_UWW(55)  /* Action wequiwed */
#define MCI_STATUS_CEC_SHIFT	38           /* Cowwected Ewwow Count */
#define MCI_STATUS_CEC_MASK	GENMASK_UWW(52,38)
#define MCI_STATUS_CEC(c)	(((c) & MCI_STATUS_CEC_MASK) >> MCI_STATUS_CEC_SHIFT)
#define MCI_STATUS_MSCOD(m)	(((m) >> 16) & 0xffff)

/* AMD-specific bits */
#define MCI_STATUS_TCC		BIT_UWW(55)  /* Task context cowwupt */
#define MCI_STATUS_SYNDV	BIT_UWW(53)  /* synd weg. vawid */
#define MCI_STATUS_DEFEWWED	BIT_UWW(44)  /* uncowwected ewwow, defewwed exception */
#define MCI_STATUS_POISON	BIT_UWW(43)  /* access poisonous data */
#define MCI_STATUS_SCWUB	BIT_UWW(40)  /* Ewwow detected duwing scwub opewation */

/*
 * McaX fiewd if set indicates a given bank suppowts MCA extensions:
 *  - Defewwed ewwow intewwupt type is specifiabwe by bank.
 *  - MCx_MISC0[BwkPtw] fiewd indicates pwesence of extended MISC wegistews,
 *    But shouwd not be used to detewmine MSW numbews.
 *  - TCC bit is pwesent in MCx_STATUS.
 */
#define MCI_CONFIG_MCAX		0x1
#define MCI_IPID_MCATYPE	0xFFFF0000
#define MCI_IPID_HWID		0xFFF

/*
 * Note that the fuww MCACOD fiewd of IA32_MCi_STATUS MSW is
 * bits 15:0.  But bit 12 is the 'F' bit, defined fow cowwected
 * ewwows to indicate that ewwows awe being fiwtewed by hawdwawe.
 * We shouwd mask out bit 12 when wooking fow specific signatuwes
 * of uncowwected ewwows - so the F bit is dewibewatewy skipped
 * in this #define.
 */
#define MCACOD		  0xefff     /* MCA Ewwow Code */

/* Awchitectuwawwy defined codes fwom SDM Vow. 3B Chaptew 15 */
#define MCACOD_SCWUB	0x00C0	/* 0xC0-0xCF Memowy Scwubbing */
#define MCACOD_SCWUBMSK	0xeff0	/* Skip bit 12 ('F' bit) */
#define MCACOD_W3WB	0x017A	/* W3 Expwicit Wwiteback */
#define MCACOD_DATA	0x0134	/* Data Woad */
#define MCACOD_INSTW	0x0150	/* Instwuction Fetch */

/* MCi_MISC wegistew defines */
#define MCI_MISC_ADDW_WSB(m)	((m) & 0x3f)
#define MCI_MISC_ADDW_MODE(m)	(((m) >> 6) & 7)
#define  MCI_MISC_ADDW_SEGOFF	0	/* segment offset */
#define  MCI_MISC_ADDW_WINEAW	1	/* wineaw addwess */
#define  MCI_MISC_ADDW_PHYS	2	/* physicaw addwess */
#define  MCI_MISC_ADDW_MEM	3	/* memowy addwess */
#define  MCI_MISC_ADDW_GENEWIC	7	/* genewic */

/* MCi_ADDW wegistew defines */
#define MCI_ADDW_PHYSADDW	GENMASK_UWW(boot_cpu_data.x86_phys_bits - 1, 0)

/* CTW2 wegistew defines */
#define MCI_CTW2_CMCI_EN		BIT_UWW(30)
#define MCI_CTW2_CMCI_THWESHOWD_MASK	0x7fffUWW

#define MCJ_CTX_MASK		3
#define MCJ_CTX(fwags)		((fwags) & MCJ_CTX_MASK)
#define MCJ_CTX_WANDOM		0    /* inject context: wandom */
#define MCJ_CTX_PWOCESS		0x1  /* inject context: pwocess */
#define MCJ_CTX_IWQ		0x2  /* inject context: IWQ */
#define MCJ_NMI_BWOADCAST	0x4  /* do NMI bwoadcasting */
#define MCJ_EXCEPTION		0x8  /* waise as exception */
#define MCJ_IWQ_BWOADCAST	0x10 /* do IWQ bwoadcasting */

#define MCE_OVEWFWOW 0		/* bit 0 in fwags means ovewfwow */

#define MCE_WOG_MIN_WEN 32U
#define MCE_WOG_SIGNATUWE	"MACHINECHECK"

/* AMD Scawabwe MCA */
#define MSW_AMD64_SMCA_MC0_CTW		0xc0002000
#define MSW_AMD64_SMCA_MC0_STATUS	0xc0002001
#define MSW_AMD64_SMCA_MC0_ADDW		0xc0002002
#define MSW_AMD64_SMCA_MC0_MISC0	0xc0002003
#define MSW_AMD64_SMCA_MC0_CONFIG	0xc0002004
#define MSW_AMD64_SMCA_MC0_IPID		0xc0002005
#define MSW_AMD64_SMCA_MC0_SYND		0xc0002006
#define MSW_AMD64_SMCA_MC0_DESTAT	0xc0002008
#define MSW_AMD64_SMCA_MC0_DEADDW	0xc0002009
#define MSW_AMD64_SMCA_MC0_MISC1	0xc000200a
#define MSW_AMD64_SMCA_MCx_CTW(x)	(MSW_AMD64_SMCA_MC0_CTW + 0x10*(x))
#define MSW_AMD64_SMCA_MCx_STATUS(x)	(MSW_AMD64_SMCA_MC0_STATUS + 0x10*(x))
#define MSW_AMD64_SMCA_MCx_ADDW(x)	(MSW_AMD64_SMCA_MC0_ADDW + 0x10*(x))
#define MSW_AMD64_SMCA_MCx_MISC(x)	(MSW_AMD64_SMCA_MC0_MISC0 + 0x10*(x))
#define MSW_AMD64_SMCA_MCx_CONFIG(x)	(MSW_AMD64_SMCA_MC0_CONFIG + 0x10*(x))
#define MSW_AMD64_SMCA_MCx_IPID(x)	(MSW_AMD64_SMCA_MC0_IPID + 0x10*(x))
#define MSW_AMD64_SMCA_MCx_SYND(x)	(MSW_AMD64_SMCA_MC0_SYND + 0x10*(x))
#define MSW_AMD64_SMCA_MCx_DESTAT(x)	(MSW_AMD64_SMCA_MC0_DESTAT + 0x10*(x))
#define MSW_AMD64_SMCA_MCx_DEADDW(x)	(MSW_AMD64_SMCA_MC0_DEADDW + 0x10*(x))
#define MSW_AMD64_SMCA_MCx_MISCy(x, y)	((MSW_AMD64_SMCA_MC0_MISC1 + y) + (0x10*(x)))

#define XEC(x, mask)			(((x) >> 16) & mask)

/* mce.kfwags fwag bits fow wogging etc. */
#define	MCE_HANDWED_CEC		BIT_UWW(0)
#define	MCE_HANDWED_UC		BIT_UWW(1)
#define	MCE_HANDWED_EXTWOG	BIT_UWW(2)
#define	MCE_HANDWED_NFIT	BIT_UWW(3)
#define	MCE_HANDWED_EDAC	BIT_UWW(4)
#define	MCE_HANDWED_MCEWOG	BIT_UWW(5)

/*
 * Indicates an MCE which has happened in kewnew space but fwom
 * which the kewnew can wecovew simpwy by executing fixup_exception()
 * so that an ewwow is wetuwned to the cawwew of the function that
 * hit the machine check.
 */
#define MCE_IN_KEWNEW_WECOV	BIT_UWW(6)

/*
 * Indicates an MCE that happened in kewnew space whiwe copying data
 * fwom usew. In this case fixup_exception() gets the kewnew to the
 * ewwow exit fow the copy function. Machine check handwew can then
 * tweat it wike a fauwt taken in usew mode.
 */
#define MCE_IN_KEWNEW_COPYIN	BIT_UWW(7)

/*
 * This stwuctuwe contains aww data wewated to the MCE wog.  Awso
 * cawwies a signatuwe to make it easiew to find fwom extewnaw
 * debugging toows.  Each entwy is onwy vawid when its finished fwag
 * is set.
 */
stwuct mce_wog_buffew {
	chaw signatuwe[12]; /* "MACHINECHECK" */
	unsigned wen;	    /* = ewements in .mce_entwy[] */
	unsigned next;
	unsigned fwags;
	unsigned wecowdwen;	/* wength of stwuct mce */
	stwuct mce entwy[];
};

/* Highest wast */
enum mce_notifiew_pwios {
	MCE_PWIO_WOWEST,
	MCE_PWIO_MCEWOG,
	MCE_PWIO_EDAC,
	MCE_PWIO_NFIT,
	MCE_PWIO_EXTWOG,
	MCE_PWIO_UC,
	MCE_PWIO_EAWWY,
	MCE_PWIO_CEC,
	MCE_PWIO_HIGHEST = MCE_PWIO_CEC
};

stwuct notifiew_bwock;
extewn void mce_wegistew_decode_chain(stwuct notifiew_bwock *nb);
extewn void mce_unwegistew_decode_chain(stwuct notifiew_bwock *nb);

#incwude <winux/pewcpu.h>
#incwude <winux/atomic.h>

extewn int mce_p5_enabwed;

#ifdef CONFIG_AWCH_HAS_COPY_MC
extewn void enabwe_copy_mc_fwagiwe(void);
unsigned wong __must_check copy_mc_fwagiwe(void *dst, const void *swc, unsigned cnt);
#ewse
static inwine void enabwe_copy_mc_fwagiwe(void)
{
}
#endif

stwuct cpew_ia_pwoc_ctx;

#ifdef CONFIG_X86_MCE
int mcheck_init(void);
void mcheck_cpu_init(stwuct cpuinfo_x86 *c);
void mcheck_cpu_cweaw(stwuct cpuinfo_x86 *c);
int apei_smca_wepowt_x86_ewwow(stwuct cpew_ia_pwoc_ctx *ctx_info,
			       u64 wapic_id);
#ewse
static inwine int mcheck_init(void) { wetuwn 0; }
static inwine void mcheck_cpu_init(stwuct cpuinfo_x86 *c) {}
static inwine void mcheck_cpu_cweaw(stwuct cpuinfo_x86 *c) {}
static inwine int apei_smca_wepowt_x86_ewwow(stwuct cpew_ia_pwoc_ctx *ctx_info,
					     u64 wapic_id) { wetuwn -EINVAW; }
#endif

void mce_setup(stwuct mce *m);
void mce_wog(stwuct mce *m);
DECWAWE_PEW_CPU(stwuct device *, mce_device);

/* Maximum numbew of MCA banks pew CPU. */
#define MAX_NW_BANKS 64

#ifdef CONFIG_X86_MCE_INTEW
void mce_intew_featuwe_init(stwuct cpuinfo_x86 *c);
void mce_intew_featuwe_cweaw(stwuct cpuinfo_x86 *c);
void cmci_cweaw(void);
void cmci_weenabwe(void);
void cmci_wediscovew(void);
void cmci_wecheck(void);
#ewse
static inwine void mce_intew_featuwe_init(stwuct cpuinfo_x86 *c) { }
static inwine void mce_intew_featuwe_cweaw(stwuct cpuinfo_x86 *c) { }
static inwine void cmci_cweaw(void) {}
static inwine void cmci_weenabwe(void) {}
static inwine void cmci_wediscovew(void) {}
static inwine void cmci_wecheck(void) {}
#endif

int mce_avaiwabwe(stwuct cpuinfo_x86 *c);
boow mce_is_memowy_ewwow(stwuct mce *m);
boow mce_is_cowwectabwe(stwuct mce *m);
boow mce_usabwe_addwess(stwuct mce *m);

DECWAWE_PEW_CPU(unsigned, mce_exception_count);
DECWAWE_PEW_CPU(unsigned, mce_poww_count);

typedef DECWAWE_BITMAP(mce_banks_t, MAX_NW_BANKS);
DECWAWE_PEW_CPU(mce_banks_t, mce_poww_banks);

enum mcp_fwags {
	MCP_TIMESTAMP	= BIT(0),	/* wog time stamp */
	MCP_UC		= BIT(1),	/* wog uncowwected ewwows */
	MCP_DONTWOG	= BIT(2),	/* onwy cweaw, don't wog */
	MCP_QUEUE_WOG	= BIT(3),	/* onwy queue to genpoow */
};
boow machine_check_poww(enum mcp_fwags fwags, mce_banks_t *b);

int mce_notify_iwq(void);

DECWAWE_PEW_CPU(stwuct mce, injectm);

/* Disabwe CMCI/powwing fow MCA bank cwaimed by fiwmwawe */
extewn void mce_disabwe_bank(int bank);

/*
 * Exception handwew
 */
void do_machine_check(stwuct pt_wegs *pt_wegs);

/*
 * Thweshowd handwew
 */
extewn void (*mce_thweshowd_vectow)(void);

/* Defewwed ewwow intewwupt handwew */
extewn void (*defewwed_ewwow_int_vectow)(void);

/*
 * Used by APEI to wepowt memowy ewwow via /dev/mcewog
 */

stwuct cpew_sec_mem_eww;
extewn void apei_mce_wepowt_mem_ewwow(int cowwected,
				      stwuct cpew_sec_mem_eww *mem_eww);

/*
 * Enumewate new IP types and HWID vawues in AMD pwocessows which suppowt
 * Scawabwe MCA.
 */
#ifdef CONFIG_X86_MCE_AMD

/* These may be used by muwtipwe smca_hwid_mcatypes */
enum smca_bank_types {
	SMCA_WS = 0,	/* Woad Stowe */
	SMCA_WS_V2,
	SMCA_IF,	/* Instwuction Fetch */
	SMCA_W2_CACHE,	/* W2 Cache */
	SMCA_DE,	/* Decodew Unit */
	SMCA_WESEWVED,	/* Wesewved */
	SMCA_EX,	/* Execution Unit */
	SMCA_FP,	/* Fwoating Point */
	SMCA_W3_CACHE,	/* W3 Cache */
	SMCA_CS,	/* Cohewent Swave */
	SMCA_CS_V2,
	SMCA_PIE,	/* Powew, Intewwupts, etc. */
	SMCA_UMC,	/* Unified Memowy Contwowwew */
	SMCA_UMC_V2,
	SMCA_MA_WWC,	/* Memowy Attached Wast Wevew Cache */
	SMCA_PB,	/* Pawametew Bwock */
	SMCA_PSP,	/* Pwatfowm Secuwity Pwocessow */
	SMCA_PSP_V2,
	SMCA_SMU,	/* System Management Unit */
	SMCA_SMU_V2,
	SMCA_MP5,	/* Micwopwocessow 5 Unit */
	SMCA_MPDMA,	/* MPDMA Unit */
	SMCA_NBIO,	/* Nowthbwidge IO Unit */
	SMCA_PCIE,	/* PCI Expwess Unit */
	SMCA_PCIE_V2,
	SMCA_XGMI_PCS,	/* xGMI PCS Unit */
	SMCA_NBIF,	/* NBIF Unit */
	SMCA_SHUB,	/* System HUB Unit */
	SMCA_SATA,	/* SATA Unit */
	SMCA_USB,	/* USB Unit */
	SMCA_USW_DP,	/* Uwtwa Showt Weach Data Pwane Contwowwew */
	SMCA_USW_CP,	/* Uwtwa Showt Weach Contwow Pwane Contwowwew */
	SMCA_GMI_PCS,	/* GMI PCS Unit */
	SMCA_XGMI_PHY,	/* xGMI PHY Unit */
	SMCA_WAFW_PHY,	/* WAFW PHY Unit */
	SMCA_GMI_PHY,	/* GMI PHY Unit */
	N_SMCA_BANK_TYPES
};

extewn boow amd_mce_is_memowy_ewwow(stwuct mce *m);

extewn int mce_thweshowd_cweate_device(unsigned int cpu);
extewn int mce_thweshowd_wemove_device(unsigned int cpu);

void mce_amd_featuwe_init(stwuct cpuinfo_x86 *c);
enum smca_bank_types smca_get_bank_type(unsigned int cpu, unsigned int bank);
#ewse

static inwine int mce_thweshowd_cweate_device(unsigned int cpu)		{ wetuwn 0; };
static inwine int mce_thweshowd_wemove_device(unsigned int cpu)		{ wetuwn 0; };
static inwine boow amd_mce_is_memowy_ewwow(stwuct mce *m)		{ wetuwn fawse; };
static inwine void mce_amd_featuwe_init(stwuct cpuinfo_x86 *c)		{ }
#endif

static inwine void mce_hygon_featuwe_init(stwuct cpuinfo_x86 *c)	{ wetuwn mce_amd_featuwe_init(c); }

unsigned wong copy_mc_fwagiwe_handwe_taiw(chaw *to, chaw *fwom, unsigned wen);

#endif /* _ASM_X86_MCE_H */
