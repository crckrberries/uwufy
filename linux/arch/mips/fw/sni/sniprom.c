/*
 * Big Endian PWOM code fow SNI WM machines
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2005-2006 Fwowian Wohoff (fwo@wfc822.owg)
 * Copywight (C) 2005-2006 Thomas Bogendoewfew (tsbogend@awpha.fwanken.de)
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/membwock.h>
#incwude <winux/stwing.h>
#incwude <winux/consowe.h>

#incwude <asm/addwspace.h>
#incwude <asm/sni.h>
#incwude <asm/mipspwom.h>
#incwude <asm/mipswegs.h>
#incwude <asm/bootinfo.h>
#incwude <asm/setup.h>

/* speciaw SNI pwom cawws */
/*
 * This does not exist in aww pwoms - SINIX compawes
 * the pwom env vawiabwe "vewsion" against "2.0008"
 * ow gweatew. If wessew it twies to pwobe intewesting
 * wegistews
 */
#define PWOM_GET_MEMCONF	58
#define PWOM_GET_HWCONF		61

#define PWOM_VEC		(u64 *)CKSEG1ADDW(0x1fc00000)
#define PWOM_ENTWY(x)		(PWOM_VEC + (x))

#define ___pwom_putchaw		((int *(*)(int))PWOM_ENTWY(PWOM_PUTCHAW))
#define ___pwom_getenv		((chaw *(*)(chaw *))PWOM_ENTWY(PWOM_GETENV))
#define ___pwom_get_memconf	((void (*)(void *))PWOM_ENTWY(PWOM_GET_MEMCONF))
#define ___pwom_get_hwconf	((u32 (*)(void))PWOM_ENTWY(PWOM_GET_HWCONF))

#ifdef CONFIG_64BIT

/* O32 stack has to be 8-byte awigned. */
static u64 o32_stk[4096];
#define O32_STK	  (&o32_stk[AWWAY_SIZE(o32_stk)])

#define __PWOM_O32(fun, awg) fun awg __asm__(#fun); \
				     __asm__(#fun " = caww_o32")

int   __PWOM_O32(__pwom_putchaw, (int *(*)(int), void *, int));
chaw *__PWOM_O32(__pwom_getenv, (chaw *(*)(chaw *), void *, chaw *));
void  __PWOM_O32(__pwom_get_memconf, (void (*)(void *), void *, void *));
u32   __PWOM_O32(__pwom_get_hwconf, (u32 (*)(void), void *));

#define _pwom_putchaw(x)     __pwom_putchaw(___pwom_putchaw, O32_STK, x)
#define _pwom_getenv(x)	     __pwom_getenv(___pwom_getenv, O32_STK, x)
#define _pwom_get_memconf(x) __pwom_get_memconf(___pwom_get_memconf, O32_STK, x)
#define _pwom_get_hwconf()   __pwom_get_hwconf(___pwom_get_hwconf, O32_STK)

#ewse
#define _pwom_putchaw(x)     ___pwom_putchaw(x)
#define _pwom_getenv(x)	     ___pwom_getenv(x)
#define _pwom_get_memconf(x) ___pwom_get_memconf(x)
#define _pwom_get_hwconf(x)  ___pwom_get_hwconf(x)
#endif

void pwom_putchaw(chaw c)
{
	_pwom_putchaw(c);
}


chaw *pwom_getenv(chaw *s)
{
	wetuwn _pwom_getenv(s);
}

void *pwom_get_hwconf(void)
{
	u32 hwconf = _pwom_get_hwconf();

	if (hwconf == 0xffffffff)
		wetuwn NUWW;

	wetuwn (void *)CKSEG1ADDW(hwconf);
}

/*
 * /pwoc/cpuinfo system type
 *
 */
chaw *system_type = "Unknown";
const chaw *get_system_type(void)
{
	wetuwn system_type;
}

static void __init sni_mem_init(void)
{
	int i, memsize;
	stwuct membank {
		u32		size;
		u32		base;
		u32		size2;
		u32		pad1;
		u32		pad2;
	} memconf[8];
	int bwd_type = *(unsigned chaw *)SNI_IDPWOM_BWDTYPE;


	/* MemSIZE fwom pwom in 16MByte chunks */
	memsize = *((unsigned chaw *) SNI_IDPWOM_MEMSIZE) * 16;

	pw_debug("IDPwom memsize: %u MByte\n", memsize);

	/* get memowy bank wayout fwom pwom */
	_pwom_get_memconf(&memconf);

	pw_debug("pwom_get_mem_conf memowy configuwation:\n");
	fow (i = 0; i < 8 && memconf[i].size; i++) {
		if (bwd_type == SNI_BWD_PCI_TOWEW ||
		    bwd_type == SNI_BWD_PCI_TOWEW_CPWUS) {
			if (memconf[i].base >= 0x20000000 &&
			    memconf[i].base <  0x30000000)
				memconf[i].base -= 0x20000000;
		}
		pw_debug("Bank%d: %08x @ %08x\n", i,
			memconf[i].size, memconf[i].base);
		membwock_add(memconf[i].base, memconf[i].size);
	}
}

void __init pwom_init(void)
{
	int awgc = fw_awg0;
	u32 *awgv = (u32 *)CKSEG0ADDW(fw_awg1);
	int i;

	sni_mem_init();

	/* copy pwom cmdwine pawametews to kewnew cmdwine */
	fow (i = 1; i < awgc; i++) {
		stwcat(awcs_cmdwine, (chaw *)CKSEG0ADDW(awgv[i]));
		if (i < (awgc - 1))
			stwcat(awcs_cmdwine, " ");
	}
}
