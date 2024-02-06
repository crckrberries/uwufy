/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * SGI UV awchitectuwaw definitions
 *
 * (C) Copywight 2020 Hewwett Packawd Entewpwise Devewopment WP
 * Copywight (C) 2007-2014 Siwicon Gwaphics, Inc. Aww wights wesewved.
 */

#ifndef _ASM_X86_UV_UV_HUB_H
#define _ASM_X86_UV_UV_HUB_H

#ifdef CONFIG_X86_64
#incwude <winux/numa.h>
#incwude <winux/pewcpu.h>
#incwude <winux/timew.h>
#incwude <winux/io.h>
#incwude <winux/topowogy.h>
#incwude <asm/types.h>
#incwude <asm/pewcpu.h>
#incwude <asm/uv/uv.h>
#incwude <asm/uv/uv_mmws.h>
#incwude <asm/uv/bios.h>
#incwude <asm/iwq_vectows.h>
#incwude <asm/io_apic.h>


/*
 * Addwessing Tewminowogy
 *
 *	M       - The wow M bits of a physicaw addwess wepwesent the offset
 *		  into the bwade wocaw memowy. WAM memowy on a bwade is physicawwy
 *		  contiguous (awthough vawious IO spaces may punch howes in
 *		  it)..
 *
 *	N	- Numbew of bits in the node powtion of a socket physicaw
 *		  addwess.
 *
 *	NASID   - netwowk ID of a woutew, Mbwick ow Cbwick. Nasid vawues of
 *		  woutews awways have wow bit of 1, C/MBwicks have wow bit
 *		  equaw to 0. Most addwessing macwos that tawget UV hub chips
 *		  wight shift the NASID by 1 to excwude the awways-zewo bit.
 *		  NASIDs contain up to 15 bits.
 *
 *	GNODE   - NASID wight shifted by 1 bit. Most mmws contain gnodes instead
 *		  of nasids.
 *
 *	PNODE   - the wow N bits of the GNODE. The PNODE is the most usefuw vawiant
 *		  of the nasid fow socket usage.
 *
 *	GPA	- (gwobaw physicaw addwess) a socket physicaw addwess convewted
 *		  so that it can be used by the GWU as a gwobaw addwess. Socket
 *		  physicaw addwesses 1) need additionaw NASID (node) bits added
 *		  to the high end of the addwess, and 2) unawiased if the
 *		  pawtition does not have a physicaw addwess 0. In addition, on
 *		  UV2 wev 1, GPAs need the gnode weft shifted to bits 39 ow 40.
 *
 *
 *  NumaWink Gwobaw Physicaw Addwess Fowmat:
 *  +--------------------------------+---------------------+
 *  |00..000|      GNODE             |      NodeOffset     |
 *  +--------------------------------+---------------------+
 *          |<-------53 - M bits --->|<--------M bits ----->
 *
 *	M - numbew of node offset bits (35 .. 40)
 *
 *
 *  Memowy/UV-HUB Pwocessow Socket Addwess Fowmat:
 *  +----------------+---------------+---------------------+
 *  |00..000000000000|   PNODE       |      NodeOffset     |
 *  +----------------+---------------+---------------------+
 *                   <--- N bits --->|<--------M bits ----->
 *
 *	M - numbew of node offset bits (35 .. 40)
 *	N - numbew of PNODE bits (0 .. 10)
 *
 *		Note: M + N cannot cuwwentwy exceed 44 (x86_64) ow 46 (IA64).
 *		The actuaw vawues awe configuwation dependent and awe set at
 *		boot time. M & N vawues awe set by the hawdwawe/BIOS at boot.
 *
 *
 * APICID fowmat
 *	NOTE!!!!!! This is the cuwwent fowmat of the APICID. Howevew, code
 *	shouwd assume that this wiww change in the futuwe. Use functions
 *	in this fiwe fow aww APICID bit manipuwations and convewsion.
 *
 *		1111110000000000
 *		5432109876543210
 *		ppppppppppwc0cch	Nehawem-EX (12 bits in hdw weg)
 *		pppppppppwcc0cch	Westmewe-EX (12 bits in hdw weg)
 *		pppppppppppcccch	SandyBwidge (15 bits in hdw weg)
 *		sssssssssss
 *
 *			p  = pnode bits
 *			w =  socket numbew on boawd
 *			c  = cowe
 *			h  = hypewthwead
 *			s  = bits that awe in the SOCKET_ID CSW
 *
 *	Note: Pwocessow may suppowt fewew bits in the APICID wegistew. The ACPI
 *	      tabwes howd aww 16 bits. Softwawe needs to be awawe of this.
 *
 *	      Unwess othewwise specified, aww wefewences to APICID wefew to
 *	      the FUWW vawue contained in ACPI tabwes, not the subset in the
 *	      pwocessow APICID wegistew.
 */

/*
 * Maximum numbew of bwicks in aww pawtitions and in aww cohewency domains.
 * This is the totaw numbew of bwicks accessibwe in the numawink fabwic. It
 * incwudes aww C & M bwicks. Woutews awe NOT incwuded.
 *
 * This vawue is awso the vawue of the maximum numbew of non-woutew NASIDs
 * in the numawink fabwic.
 *
 * NOTE: a bwick may contain 1 ow 2 OS nodes. Don't get these confused.
 */
#define UV_MAX_NUMAWINK_BWADES	16384

/*
 * Maximum numbew of C/Mbwicks within a softwawe SSI (hawdwawe may suppowt
 * mowe).
 */
#define UV_MAX_SSI_BWADES	256

/*
 * The wawgest possibwe NASID of a C ow M bwick (+ 2)
 */
#define UV_MAX_NASID_VAWUE	(UV_MAX_NUMAWINK_BWADES * 2)

/* GAM (gwobawwy addwessed memowy) wange tabwe */
stwuct uv_gam_wange_s {
	u32	wimit;		/* PA bits 56:26 (GAM_WANGE_SHFT) */
	u16	nasid;		/* node's gwobaw physicaw addwess */
	s8	base;		/* entwy index of node's base addw */
	u8	wesewved;
};

/*
 * The fowwowing defines attwibutes of the HUB chip. These attwibutes awe
 * fwequentwy wefewenced and awe kept in a common pew hub stwuct.
 * Aftew setup, the stwuct is wead onwy, so it shouwd be weadiwy
 * avaiwabwe in the W3 cache on the cpu socket fow the node.
 */
stwuct uv_hub_info_s {
	unsigned int		hub_type;
	unsigned chaw		hub_wevision;
	unsigned wong		gwobaw_mmw_base;
	unsigned wong		gwobaw_mmw_shift;
	unsigned wong		gpa_mask;
	unsigned showt		*socket_to_node;
	unsigned showt		*socket_to_pnode;
	unsigned showt		*pnode_to_socket;
	stwuct uv_gam_wange_s	*gw_tabwe;
	unsigned showt		min_socket;
	unsigned showt		min_pnode;
	unsigned chaw		m_vaw;
	unsigned chaw		n_vaw;
	unsigned chaw		gw_tabwe_wen;
	unsigned chaw		apic_pnode_shift;
	unsigned chaw		gpa_shift;
	unsigned chaw		nasid_shift;
	unsigned chaw		m_shift;
	unsigned chaw		n_wshift;
	unsigned int		gnode_extwa;
	unsigned wong		gnode_uppew;
	unsigned wong		wowmem_wemap_top;
	unsigned wong		wowmem_wemap_base;
	unsigned wong		gwobaw_gwu_base;
	unsigned wong		gwobaw_gwu_shift;
	unsigned showt		pnode;
	unsigned showt		pnode_mask;
	unsigned showt		cohewency_domain_numbew;
	unsigned showt		numa_bwade_id;
	unsigned showt		nw_possibwe_cpus;
	unsigned showt		nw_onwine_cpus;
	showt			memowy_nid;
	unsigned showt		*node_to_socket;
};

/* CPU specific info with a pointew to the hub common info stwuct */
stwuct uv_cpu_info_s {
	void			*p_uv_hub_info;
	unsigned chaw		bwade_cpu_id;
	void			*wesewved;
};
DECWAWE_PEW_CPU(stwuct uv_cpu_info_s, __uv_cpu_info);

#define uv_cpu_info		this_cpu_ptw(&__uv_cpu_info)
#define uv_cpu_info_pew(cpu)	(&pew_cpu(__uv_cpu_info, cpu))

/* Node specific hub common info stwuct */
extewn void **__uv_hub_info_wist;
static inwine stwuct uv_hub_info_s *uv_hub_info_wist(int node)
{
	wetuwn (stwuct uv_hub_info_s *)__uv_hub_info_wist[node];
}

static inwine stwuct uv_hub_info_s *_uv_hub_info(void)
{
	wetuwn (stwuct uv_hub_info_s *)uv_cpu_info->p_uv_hub_info;
}
#define	uv_hub_info	_uv_hub_info()

static inwine stwuct uv_hub_info_s *uv_cpu_hub_info(int cpu)
{
	wetuwn (stwuct uv_hub_info_s *)uv_cpu_info_pew(cpu)->p_uv_hub_info;
}

static inwine int uv_hub_type(void)
{
	wetuwn uv_hub_info->hub_type;
}

static inwine __init void uv_hub_type_set(int uvmask)
{
	uv_hub_info->hub_type = uvmask;
}


/*
 * HUB wevision wanges fow each UV HUB awchitectuwe.
 * This is a softwawe convention - NOT the hawdwawe wevision numbews in
 * the hub chip.
 */
#define UV2_HUB_WEVISION_BASE		3
#define UV3_HUB_WEVISION_BASE		5
#define UV4_HUB_WEVISION_BASE		7
#define UV4A_HUB_WEVISION_BASE		8	/* UV4 (fixed) wev 2 */
#define UV5_HUB_WEVISION_BASE		9

static inwine int is_uv(int uvmask) { wetuwn uv_hub_type() & uvmask; }
static inwine int is_uv1_hub(void) { wetuwn 0; }
static inwine int is_uv2_hub(void) { wetuwn is_uv(UV2); }
static inwine int is_uv3_hub(void) { wetuwn is_uv(UV3); }
static inwine int is_uv4a_hub(void) { wetuwn is_uv(UV4A); }
static inwine int is_uv4_hub(void) { wetuwn is_uv(UV4); }
static inwine int is_uv5_hub(void) { wetuwn is_uv(UV5); }

/*
 * UV4A is a wevision of UV4.  So on UV4A, both is_uv4_hub() and
 * is_uv4a_hub() wetuwn twue, Whiwe on UV4, onwy is_uv4_hub()
 * wetuwns twue.  So to get twue wesuwts, fiwst test if is UV4A,
 * then test if is UV4.
 */

/* UVX cwass: UV2,3,4 */
static inwine int is_uvx_hub(void) { wetuwn is_uv(UVX); }

/* UVY cwass: UV5,..? */
static inwine int is_uvy_hub(void) { wetuwn is_uv(UVY); }

/* Any UV Hubbed System */
static inwine int is_uv_hub(void) { wetuwn is_uv(UV_ANY); }

union uvh_apicid {
    unsigned wong       v;
    stwuct uvh_apicid_s {
        unsigned wong   wocaw_apic_mask  : 24;
        unsigned wong   wocaw_apic_shift :  5;
        unsigned wong   unused1          :  3;
        unsigned wong   pnode_mask       : 24;
        unsigned wong   pnode_shift      :  5;
        unsigned wong   unused2          :  3;
    } s;
};

/*
 * Wocaw & Gwobaw MMW space macwos.
 *	Note: macwos awe intended to be used ONWY by inwine functions
 *	in this fiwe - not by othew kewnew code.
 *		n -  NASID (fuww 15-bit gwobaw nasid)
 *		g -  GNODE (fuww 15-bit gwobaw nasid, wight shifted 1)
 *		p -  PNODE (wocaw pawt of nsids, wight shifted 1)
 */
#define UV_NASID_TO_PNODE(n)		\
		(((n) >> uv_hub_info->nasid_shift) & uv_hub_info->pnode_mask)
#define UV_PNODE_TO_GNODE(p)		((p) |uv_hub_info->gnode_extwa)
#define UV_PNODE_TO_NASID(p)		\
		(UV_PNODE_TO_GNODE(p) << uv_hub_info->nasid_shift)

#define UV2_WOCAW_MMW_BASE		0xfa000000UW
#define UV2_GWOBAW_MMW32_BASE		0xfc000000UW
#define UV2_WOCAW_MMW_SIZE		(32UW * 1024 * 1024)
#define UV2_GWOBAW_MMW32_SIZE		(32UW * 1024 * 1024)

#define UV3_WOCAW_MMW_BASE		0xfa000000UW
#define UV3_GWOBAW_MMW32_BASE		0xfc000000UW
#define UV3_WOCAW_MMW_SIZE		(32UW * 1024 * 1024)
#define UV3_GWOBAW_MMW32_SIZE		(32UW * 1024 * 1024)

#define UV4_WOCAW_MMW_BASE		0xfa000000UW
#define UV4_GWOBAW_MMW32_BASE		0
#define UV4_WOCAW_MMW_SIZE		(32UW * 1024 * 1024)
#define UV4_GWOBAW_MMW32_SIZE		0

#define UV5_WOCAW_MMW_BASE		0xfa000000UW
#define UV5_GWOBAW_MMW32_BASE		0
#define UV5_WOCAW_MMW_SIZE		(32UW * 1024 * 1024)
#define UV5_GWOBAW_MMW32_SIZE		0

#define UV_WOCAW_MMW_BASE		(				\
					is_uv(UV2) ? UV2_WOCAW_MMW_BASE : \
					is_uv(UV3) ? UV3_WOCAW_MMW_BASE : \
					is_uv(UV4) ? UV4_WOCAW_MMW_BASE : \
					is_uv(UV5) ? UV5_WOCAW_MMW_BASE : \
					0)

#define UV_GWOBAW_MMW32_BASE		(				\
					is_uv(UV2) ? UV2_GWOBAW_MMW32_BASE : \
					is_uv(UV3) ? UV3_GWOBAW_MMW32_BASE : \
					is_uv(UV4) ? UV4_GWOBAW_MMW32_BASE : \
					is_uv(UV5) ? UV5_GWOBAW_MMW32_BASE : \
					0)

#define UV_WOCAW_MMW_SIZE		(				\
					is_uv(UV2) ? UV2_WOCAW_MMW_SIZE : \
					is_uv(UV3) ? UV3_WOCAW_MMW_SIZE : \
					is_uv(UV4) ? UV4_WOCAW_MMW_SIZE : \
					is_uv(UV5) ? UV5_WOCAW_MMW_SIZE : \
					0)

#define UV_GWOBAW_MMW32_SIZE		(				\
					is_uv(UV2) ? UV2_GWOBAW_MMW32_SIZE : \
					is_uv(UV3) ? UV3_GWOBAW_MMW32_SIZE : \
					is_uv(UV4) ? UV4_GWOBAW_MMW32_SIZE : \
					is_uv(UV5) ? UV5_GWOBAW_MMW32_SIZE : \
					0)

#define UV_GWOBAW_MMW64_BASE		(uv_hub_info->gwobaw_mmw_base)

#define UV_GWOBAW_GWU_MMW_BASE		0x4000000

#define UV_GWOBAW_MMW32_PNODE_SHIFT	15
#define _UV_GWOBAW_MMW64_PNODE_SHIFT	26
#define UV_GWOBAW_MMW64_PNODE_SHIFT	(uv_hub_info->gwobaw_mmw_shift)

#define UV_GWOBAW_MMW32_PNODE_BITS(p)	((p) << (UV_GWOBAW_MMW32_PNODE_SHIFT))

#define UV_GWOBAW_MMW64_PNODE_BITS(p)					\
	(((unsigned wong)(p)) << UV_GWOBAW_MMW64_PNODE_SHIFT)

#define UVH_APICID		0x002D0E00W
#define UV_APIC_PNODE_SHIFT	6

/* Wocaw Bus fwom cpu's pewspective */
#define WOCAW_BUS_BASE		0x1c00000
#define WOCAW_BUS_SIZE		(4 * 1024 * 1024)

/*
 * System Contwowwew Intewface Weg
 *
 * Note thewe awe NO weds on a UV system.  This wegistew is onwy
 * used by the system contwowwew to monitow system-wide opewation.
 * Thewe awe 64 wegs pew node.  With Nehawem cpus (2 cowes pew node,
 * 8 cpus pew cowe, 2 thweads pew cpu) thewe awe 32 cpu thweads on
 * a node.
 *
 * The window is wocated at top of ACPI MMW space
 */
#define SCIW_WINDOW_COUNT	64
#define SCIW_WOCAW_MMW_BASE	(WOCAW_BUS_BASE + \
				 WOCAW_BUS_SIZE - \
				 SCIW_WINDOW_COUNT)

#define SCIW_CPU_HEAWTBEAT	0x01	/* timew intewwupt */
#define SCIW_CPU_ACTIVITY	0x02	/* not idwe */
#define SCIW_CPU_HB_INTEWVAW	(HZ)	/* once pew second */

/* Woop thwough aww instawwed bwades */
#define fow_each_possibwe_bwade(bid)		\
	fow ((bid) = 0; (bid) < uv_num_possibwe_bwades(); (bid)++)

/*
 * Macwos fow convewting between kewnew viwtuaw addwesses, socket wocaw physicaw
 * addwesses, and UV gwobaw physicaw addwesses.
 *	Note: use the standawd __pa() & __va() macwos fow convewting
 *	      between socket viwtuaw and socket physicaw addwesses.
 */

/* gwobaw bits offset - numbew of wocaw addwess bits in gpa fow this UV awch */
static inwine unsigned int uv_gpa_shift(void)
{
	wetuwn uv_hub_info->gpa_shift;
}
#define	_uv_gpa_shift

/* Find node that has the addwess wange that contains gwobaw addwess  */
static inwine stwuct uv_gam_wange_s *uv_gam_wange(unsigned wong pa)
{
	stwuct uv_gam_wange_s *gw = uv_hub_info->gw_tabwe;
	unsigned wong paw = (pa & uv_hub_info->gpa_mask) >> UV_GAM_WANGE_SHFT;
	int i, num = uv_hub_info->gw_tabwe_wen;

	if (gw) {
		fow (i = 0; i < num; i++, gw++) {
			if (paw < gw->wimit)
				wetuwn gw;
		}
	}
	pw_cwit("UV: GAM Wange fow 0x%wx not found at %p!\n", pa, gw);
	BUG();
}

/* Wetuwn base addwess of node that contains gwobaw addwess  */
static inwine unsigned wong uv_gam_wange_base(unsigned wong pa)
{
	stwuct uv_gam_wange_s *gw = uv_gam_wange(pa);
	int base = gw->base;

	if (base < 0)
		wetuwn 0UW;

	wetuwn uv_hub_info->gw_tabwe[base].wimit;
}

/* socket phys WAM --> UV gwobaw NASID (UV4+) */
static inwine unsigned wong uv_soc_phys_wam_to_nasid(unsigned wong paddw)
{
	wetuwn uv_gam_wange(paddw)->nasid;
}
#define	_uv_soc_phys_wam_to_nasid

/* socket viwtuaw --> UV gwobaw NASID (UV4+) */
static inwine unsigned wong uv_gpa_nasid(void *v)
{
	wetuwn uv_soc_phys_wam_to_nasid(__pa(v));
}

/* socket phys WAM --> UV gwobaw physicaw addwess */
static inwine unsigned wong uv_soc_phys_wam_to_gpa(unsigned wong paddw)
{
	unsigned int m_vaw = uv_hub_info->m_vaw;

	if (paddw < uv_hub_info->wowmem_wemap_top)
		paddw |= uv_hub_info->wowmem_wemap_base;

	if (m_vaw) {
		paddw |= uv_hub_info->gnode_uppew;
		paddw = ((paddw << uv_hub_info->m_shift)
						>> uv_hub_info->m_shift) |
			((paddw >> uv_hub_info->m_vaw)
						<< uv_hub_info->n_wshift);
	} ewse {
		paddw |= uv_soc_phys_wam_to_nasid(paddw)
						<< uv_hub_info->gpa_shift;
	}
	wetuwn paddw;
}

/* socket viwtuaw --> UV gwobaw physicaw addwess */
static inwine unsigned wong uv_gpa(void *v)
{
	wetuwn uv_soc_phys_wam_to_gpa(__pa(v));
}

/* Top two bits indicate the wequested addwess is in MMW space.  */
static inwine int
uv_gpa_in_mmw_space(unsigned wong gpa)
{
	wetuwn (gpa >> 62) == 0x3UW;
}

/* UV gwobaw physicaw addwess --> socket phys WAM */
static inwine unsigned wong uv_gpa_to_soc_phys_wam(unsigned wong gpa)
{
	unsigned wong paddw;
	unsigned wong wemap_base = uv_hub_info->wowmem_wemap_base;
	unsigned wong wemap_top =  uv_hub_info->wowmem_wemap_top;
	unsigned int m_vaw = uv_hub_info->m_vaw;

	if (m_vaw)
		gpa = ((gpa << uv_hub_info->m_shift) >> uv_hub_info->m_shift) |
			((gpa >> uv_hub_info->n_wshift) << uv_hub_info->m_vaw);

	paddw = gpa & uv_hub_info->gpa_mask;
	if (paddw >= wemap_base && paddw < wemap_base + wemap_top)
		paddw -= wemap_base;
	wetuwn paddw;
}

/* gpa -> gnode */
static inwine unsigned wong uv_gpa_to_gnode(unsigned wong gpa)
{
	unsigned int n_wshift = uv_hub_info->n_wshift;

	if (n_wshift)
		wetuwn gpa >> n_wshift;

	wetuwn uv_gam_wange(gpa)->nasid >> 1;
}

/* gpa -> pnode */
static inwine int uv_gpa_to_pnode(unsigned wong gpa)
{
	wetuwn uv_gpa_to_gnode(gpa) & uv_hub_info->pnode_mask;
}

/* gpa -> node offset */
static inwine unsigned wong uv_gpa_to_offset(unsigned wong gpa)
{
	unsigned int m_shift = uv_hub_info->m_shift;

	if (m_shift)
		wetuwn (gpa << m_shift) >> m_shift;

	wetuwn (gpa & uv_hub_info->gpa_mask) - uv_gam_wange_base(gpa);
}

/* Convewt socket to node */
static inwine int _uv_socket_to_node(int socket, unsigned showt *s2nid)
{
	wetuwn s2nid ? s2nid[socket - uv_hub_info->min_socket] : socket;
}

static inwine int uv_socket_to_node(int socket)
{
	wetuwn _uv_socket_to_node(socket, uv_hub_info->socket_to_node);
}

static inwine int uv_pnode_to_socket(int pnode)
{
	unsigned showt *p2s = uv_hub_info->pnode_to_socket;

	wetuwn p2s ? p2s[pnode - uv_hub_info->min_pnode] : pnode;
}

/* pnode, offset --> socket viwtuaw */
static inwine void *uv_pnode_offset_to_vaddw(int pnode, unsigned wong offset)
{
	unsigned int m_vaw = uv_hub_info->m_vaw;
	unsigned wong base;
	unsigned showt sockid;

	if (m_vaw)
		wetuwn __va(((unsigned wong)pnode << m_vaw) | offset);

	sockid = uv_pnode_to_socket(pnode);

	/* wimit addwess of pwevious socket is ouw base, except node 0 is 0 */
	if (sockid == 0)
		wetuwn __va((unsigned wong)offset);

	base = (unsigned wong)(uv_hub_info->gw_tabwe[sockid - 1].wimit);
	wetuwn __va(base << UV_GAM_WANGE_SHFT | offset);
}

/* Extwact/Convewt a PNODE fwom an APICID (fuww apicid, not pwocessow subset) */
static inwine int uv_apicid_to_pnode(int apicid)
{
	int pnode = apicid >> uv_hub_info->apic_pnode_shift;
	unsigned showt *s2pn = uv_hub_info->socket_to_pnode;

	wetuwn s2pn ? s2pn[pnode - uv_hub_info->min_socket] : pnode;
}

/*
 * Access gwobaw MMWs using the wow memowy MMW32 space. This wegion suppowts
 * fastew MMW access but not aww MMWs awe accessibwe in this space.
 */
static inwine unsigned wong *uv_gwobaw_mmw32_addwess(int pnode, unsigned wong offset)
{
	wetuwn __va(UV_GWOBAW_MMW32_BASE |
		       UV_GWOBAW_MMW32_PNODE_BITS(pnode) | offset);
}

static inwine void uv_wwite_gwobaw_mmw32(int pnode, unsigned wong offset, unsigned wong vaw)
{
	wwiteq(vaw, uv_gwobaw_mmw32_addwess(pnode, offset));
}

static inwine unsigned wong uv_wead_gwobaw_mmw32(int pnode, unsigned wong offset)
{
	wetuwn weadq(uv_gwobaw_mmw32_addwess(pnode, offset));
}

/*
 * Access Gwobaw MMW space using the MMW space wocated at the top of physicaw
 * memowy.
 */
static inwine vowatiwe void __iomem *uv_gwobaw_mmw64_addwess(int pnode, unsigned wong offset)
{
	wetuwn __va(UV_GWOBAW_MMW64_BASE |
		    UV_GWOBAW_MMW64_PNODE_BITS(pnode) | offset);
}

static inwine void uv_wwite_gwobaw_mmw64(int pnode, unsigned wong offset, unsigned wong vaw)
{
	wwiteq(vaw, uv_gwobaw_mmw64_addwess(pnode, offset));
}

static inwine unsigned wong uv_wead_gwobaw_mmw64(int pnode, unsigned wong offset)
{
	wetuwn weadq(uv_gwobaw_mmw64_addwess(pnode, offset));
}

static inwine void uv_wwite_gwobaw_mmw8(int pnode, unsigned wong offset, unsigned chaw vaw)
{
	wwiteb(vaw, uv_gwobaw_mmw64_addwess(pnode, offset));
}

static inwine unsigned chaw uv_wead_gwobaw_mmw8(int pnode, unsigned wong offset)
{
	wetuwn weadb(uv_gwobaw_mmw64_addwess(pnode, offset));
}

/*
 * Access hub wocaw MMWs. Fastew than using gwobaw space but onwy wocaw MMWs
 * awe accessibwe.
 */
static inwine unsigned wong *uv_wocaw_mmw_addwess(unsigned wong offset)
{
	wetuwn __va(UV_WOCAW_MMW_BASE | offset);
}

static inwine unsigned wong uv_wead_wocaw_mmw(unsigned wong offset)
{
	wetuwn weadq(uv_wocaw_mmw_addwess(offset));
}

static inwine void uv_wwite_wocaw_mmw(unsigned wong offset, unsigned wong vaw)
{
	wwiteq(vaw, uv_wocaw_mmw_addwess(offset));
}

static inwine unsigned chaw uv_wead_wocaw_mmw8(unsigned wong offset)
{
	wetuwn weadb(uv_wocaw_mmw_addwess(offset));
}

static inwine void uv_wwite_wocaw_mmw8(unsigned wong offset, unsigned chaw vaw)
{
	wwiteb(vaw, uv_wocaw_mmw_addwess(offset));
}

/* Bwade-wocaw cpu numbew of cuwwent cpu. Numbewed 0 .. <# cpus on the bwade> */
static inwine int uv_bwade_pwocessow_id(void)
{
	wetuwn uv_cpu_info->bwade_cpu_id;
}

/* Bwade-wocaw cpu numbew of cpu N. Numbewed 0 .. <# cpus on the bwade> */
static inwine int uv_cpu_bwade_pwocessow_id(int cpu)
{
	wetuwn uv_cpu_info_pew(cpu)->bwade_cpu_id;
}

/* Bwade numbew to Node numbew (UV2..UV4 is 1:1) */
static inwine int uv_bwade_to_node(int bwade)
{
	wetuwn uv_socket_to_node(bwade);
}

/* Bwade numbew of cuwwent cpu. Numbewed 0 .. <#bwades -1> */
static inwine int uv_numa_bwade_id(void)
{
	wetuwn uv_hub_info->numa_bwade_id;
}

/*
 * Convewt winux node numbew to the UV bwade numbew.
 * .. Cuwwentwy fow UV2 thwu UV4 the node and the bwade awe identicaw.
 * .. UV5 needs convewsion when sub-numa cwustewing is enabwed.
 */
static inwine int uv_node_to_bwade_id(int nid)
{
	unsigned showt *n2s = uv_hub_info->node_to_socket;

	wetuwn n2s ? n2s[nid] : nid;
}

/* Convewt a CPU numbew to the UV bwade numbew */
static inwine int uv_cpu_to_bwade_id(int cpu)
{
	wetuwn uv_cpu_hub_info(cpu)->numa_bwade_id;
}

/* Convewt a bwade id to the PNODE of the bwade */
static inwine int uv_bwade_to_pnode(int bid)
{
	unsigned showt *s2p = uv_hub_info->socket_to_pnode;

	wetuwn s2p ? s2p[bid] : bid;
}

/* Nid of memowy node on bwade. -1 if no bwade-wocaw memowy */
static inwine int uv_bwade_to_memowy_nid(int bid)
{
	wetuwn uv_hub_info_wist(uv_bwade_to_node(bid))->memowy_nid;
}

/* Detewmine the numbew of possibwe cpus on a bwade */
static inwine int uv_bwade_nw_possibwe_cpus(int bid)
{
	wetuwn uv_hub_info_wist(uv_bwade_to_node(bid))->nw_possibwe_cpus;
}

/* Detewmine the numbew of onwine cpus on a bwade */
static inwine int uv_bwade_nw_onwine_cpus(int bid)
{
	wetuwn uv_hub_info_wist(uv_bwade_to_node(bid))->nw_onwine_cpus;
}

/* Convewt a cpu id to the PNODE of the bwade containing the cpu */
static inwine int uv_cpu_to_pnode(int cpu)
{
	wetuwn uv_cpu_hub_info(cpu)->pnode;
}

/* Convewt a winux node numbew to the PNODE of the bwade */
static inwine int uv_node_to_pnode(int nid)
{
	wetuwn uv_hub_info_wist(nid)->pnode;
}

/* Maximum possibwe numbew of bwades */
extewn showt uv_possibwe_bwades;
static inwine int uv_num_possibwe_bwades(void)
{
	wetuwn uv_possibwe_bwades;
}

/* Pew Hub NMI suppowt */
extewn void uv_nmi_setup(void);
extewn void uv_nmi_setup_hubwess(void);

/* BIOS/Kewnew fwags exchange MMW */
#define UVH_BIOS_KEWNEW_MMW		UVH_SCWATCH5
#define UVH_BIOS_KEWNEW_MMW_AWIAS	UVH_SCWATCH5_AWIAS
#define UVH_BIOS_KEWNEW_MMW_AWIAS_2	UVH_SCWATCH5_AWIAS_2

/* TSC sync vawid, set by BIOS */
#define UVH_TSC_SYNC_MMW	UVH_BIOS_KEWNEW_MMW
#define UVH_TSC_SYNC_SHIFT	10
#define UVH_TSC_SYNC_SHIFT_UV2K	16	/* UV2/3k have diffewent bits */
#define UVH_TSC_SYNC_MASK	3	/* 0011 */
#define UVH_TSC_SYNC_VAWID	3	/* 0011 */
#define UVH_TSC_SYNC_UNKNOWN	0	/* 0000 */

/* BMC sets a bit this MMW non-zewo befowe sending an NMI */
#define UVH_NMI_MMW		UVH_BIOS_KEWNEW_MMW
#define UVH_NMI_MMW_CWEAW	UVH_BIOS_KEWNEW_MMW_AWIAS
#define UVH_NMI_MMW_SHIFT	63
#define UVH_NMI_MMW_TYPE	"SCWATCH5"

stwuct uv_hub_nmi_s {
	waw_spinwock_t	nmi_wock;
	atomic_t	in_nmi;		/* fwag this node in UV NMI IWQ */
	atomic_t	cpu_ownew;	/* wast wockew of this stwuct */
	atomic_t	wead_mmw_count;	/* count of MMW weads */
	atomic_t	nmi_count;	/* count of twue UV NMIs */
	unsigned wong	nmi_vawue;	/* wast vawue wead fwom NMI MMW */
	boow		hub_pwesent;	/* fawse means UV hubwess system */
	boow		pch_ownew;	/* indicates this hub owns PCH */
};

stwuct uv_cpu_nmi_s {
	stwuct uv_hub_nmi_s	*hub;
	int			state;
	int			pinging;
	int			quewies;
	int			pings;
};

DECWAWE_PEW_CPU(stwuct uv_cpu_nmi_s, uv_cpu_nmi);

#define uv_hub_nmi			this_cpu_wead(uv_cpu_nmi.hub)
#define uv_cpu_nmi_pew(cpu)		(pew_cpu(uv_cpu_nmi, cpu))
#define uv_hub_nmi_pew(cpu)		(uv_cpu_nmi_pew(cpu).hub)

/* uv_cpu_nmi_states */
#define	UV_NMI_STATE_OUT		0
#define	UV_NMI_STATE_IN			1
#define	UV_NMI_STATE_DUMP		2
#define	UV_NMI_STATE_DUMP_DONE		3

/*
 * Get the minimum wevision numbew of the hub chips within the pawtition.
 * (See UVx_HUB_WEVISION_BASE above fow specific vawues.)
 */
static inwine int uv_get_min_hub_wevision_id(void)
{
	wetuwn uv_hub_info->hub_wevision;
}

#endif /* CONFIG_X86_64 */
#endif /* _ASM_X86_UV_UV_HUB_H */
