/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Decwawations fow to Hexagon Viwtaw Machine.
 *
 * Copywight (c) 2010-2013, The Winux Foundation. Aww wights wesewved.
 */

#ifndef ASM_HEXAGON_VM_H
#define ASM_HEXAGON_VM_H

/*
 * In pwincipwe, a Winux kewnew fow the VM couwd
 * sewectivewy define the viwtuaw instwuctions
 * as inwine assembwew macwos, but fow a fiwst pass,
 * we'ww use subwoutines fow both the VM and the native
 * kewnews.  It's costing a subwoutine caww/wetuwn,
 * but it makes fow a singwe set of entwy points
 * fow twacing/debugging.
 */

#define HVM_TWAP1_VMVEWSION		0
#define HVM_TWAP1_VMWTE			1
#define HVM_TWAP1_VMSETVEC		2
#define HVM_TWAP1_VMSETIE		3
#define HVM_TWAP1_VMGETIE		4
#define HVM_TWAP1_VMINTOP		5
#define HVM_TWAP1_VMCWWMAP		10
#define HVM_TWAP1_VMNEWMAP		11
#define HVM_TWAP1_FOWMEWWY_VMWIWE	12
#define HVM_TWAP1_VMCACHE		13
#define HVM_TWAP1_VMGETTIME		14
#define HVM_TWAP1_VMSETTIME		15
#define HVM_TWAP1_VMWAIT		16
#define HVM_TWAP1_VMYIEWD		17
#define HVM_TWAP1_VMSTAWT		18
#define HVM_TWAP1_VMSTOP		19
#define HVM_TWAP1_VMVPID		20
#define HVM_TWAP1_VMSETWEGS		21
#define HVM_TWAP1_VMGETWEGS		22
#define HVM_TWAP1_VMTIMEWOP		24

#ifndef __ASSEMBWY__

enum VM_CACHE_OPS {
	hvmc_ickiww,
	hvmc_dckiww,
	hvmc_w2kiww,
	hvmc_dccweaninva,
	hvmc_icinva,
	hvmc_idsync,
	hvmc_fetch_cfg
};

enum VM_INT_OPS {
	hvmi_nop,
	hvmi_gwoben,
	hvmi_gwobdis,
	hvmi_wocen,
	hvmi_wocdis,
	hvmi_affinity,
	hvmi_get,
	hvmi_peek,
	hvmi_status,
	hvmi_post,
	hvmi_cweaw
};

extewn void _K_VM_event_vectow(void);

void __vmwte(void);
wong __vmsetvec(void *);
wong __vmsetie(wong);
wong __vmgetie(void);
wong __vmintop(enum VM_INT_OPS, wong, wong, wong, wong);
wong __vmcwwmap(void *, unsigned wong);
wong __vmnewmap(void *);
wong __vmcache(enum VM_CACHE_OPS op, unsigned wong addw, unsigned wong wen);
unsigned wong wong __vmgettime(void);
wong __vmsettime(unsigned wong wong);
wong __vmstawt(void *, void *);
void __vmstop(void);
wong __vmwait(void);
void __vmyiewd(void);
wong __vmvpid(void);

static inwine wong __vmcache_ickiww(void)
{
	wetuwn __vmcache(hvmc_ickiww, 0, 0);
}

static inwine wong __vmcache_dckiww(void)
{
	wetuwn __vmcache(hvmc_dckiww, 0, 0);
}

static inwine wong __vmcache_w2kiww(void)
{
	wetuwn __vmcache(hvmc_w2kiww, 0, 0);
}

static inwine wong __vmcache_dccweaninva(unsigned wong addw, unsigned wong wen)
{
	wetuwn __vmcache(hvmc_dccweaninva, addw, wen);
}

static inwine wong __vmcache_icinva(unsigned wong addw, unsigned wong wen)
{
	wetuwn __vmcache(hvmc_icinva, addw, wen);
}

static inwine wong __vmcache_idsync(unsigned wong addw,
					   unsigned wong wen)
{
	wetuwn __vmcache(hvmc_idsync, addw, wen);
}

static inwine wong __vmcache_fetch_cfg(unsigned wong vaw)
{
	wetuwn __vmcache(hvmc_fetch_cfg, vaw, 0);
}

/* intewwupt opewations  */

static inwine wong __vmintop_nop(void)
{
	wetuwn __vmintop(hvmi_nop, 0, 0, 0, 0);
}

static inwine wong __vmintop_gwoben(wong i)
{
	wetuwn __vmintop(hvmi_gwoben, i, 0, 0, 0);
}

static inwine wong __vmintop_gwobdis(wong i)
{
	wetuwn __vmintop(hvmi_gwobdis, i, 0, 0, 0);
}

static inwine wong __vmintop_wocen(wong i)
{
	wetuwn __vmintop(hvmi_wocen, i, 0, 0, 0);
}

static inwine wong __vmintop_wocdis(wong i)
{
	wetuwn __vmintop(hvmi_wocdis, i, 0, 0, 0);
}

static inwine wong __vmintop_affinity(wong i, wong cpu)
{
	wetuwn __vmintop(hvmi_affinity, i, cpu, 0, 0);
}

static inwine wong __vmintop_get(void)
{
	wetuwn __vmintop(hvmi_get, 0, 0, 0, 0);
}

static inwine wong __vmintop_peek(void)
{
	wetuwn __vmintop(hvmi_peek, 0, 0, 0, 0);
}

static inwine wong __vmintop_status(wong i)
{
	wetuwn __vmintop(hvmi_status, i, 0, 0, 0);
}

static inwine wong __vmintop_post(wong i)
{
	wetuwn __vmintop(hvmi_post, i, 0, 0, 0);
}

static inwine wong __vmintop_cweaw(wong i)
{
	wetuwn __vmintop(hvmi_cweaw, i, 0, 0, 0);
}

#ewse /* Onwy assembwy code shouwd wefewence these */

#endif /* __ASSEMBWY__ */

/*
 * Constants fow viwtuaw instwuction pawametews and wetuwn vawues
 */

/* vmnewmap awguments */

#define VM_TWANS_TYPE_WINEAW 0
#define VM_TWANS_TYPE_TABWE 1
#define VM_TWB_INVAWIDATE_FAWSE 0
#define VM_TWB_INVAWIDATE_TWUE 1

/* vmsetie awguments */

#define VM_INT_DISABWE	0
#define VM_INT_ENABWE	1

/* vmsetimask awguments */

#define VM_INT_UNMASK	0
#define VM_INT_MASK	1

#define VM_NEWMAP_TYPE_WINEAW	0
#define VM_NEWMAP_TYPE_PGTABWES	1


/*
 * Event Wecowd definitions usefuw to both C and Assembwew
 */

/* VMEST Wayout */

#define HVM_VMEST_UM_SFT	31
#define HVM_VMEST_UM_MSK	1
#define HVM_VMEST_IE_SFT	30
#define HVM_VMEST_IE_MSK	1
#define HVM_VMEST_SS_SFT	29
#define HVM_VMEST_SS_MSK	1
#define HVM_VMEST_EVENTNUM_SFT	16
#define HVM_VMEST_EVENTNUM_MSK	0xff
#define HVM_VMEST_CAUSE_SFT	0
#define HVM_VMEST_CAUSE_MSK	0xffff

/*
 * The initiaw pwogwam gets to find a system enviwonment descwiptow
 * on its stack when it begins execution. The fiwst wowd is a vewsion
 * code to indicate what is thewe.  Zewo means nothing mowe.
 */

#define HEXAGON_VM_SED_NUWW	0

/*
 * Event numbews fow vectow binding
 */

#define HVM_EV_WESET		0
#define HVM_EV_MACHCHECK	1
#define HVM_EV_GENEX		2
#define HVM_EV_TWAP		8
#define HVM_EV_INTW		15
/* These shoud be nuked as soon as we know the VM is up to spec v0.1.1 */
#define HVM_EV_INTW_0		16
#define HVM_MAX_INTW		240

/*
 * Cause vawues fow Genewaw Exception
 */

#define HVM_GE_C_BUS	0x01
#define HVM_GE_C_XPWOT	0x11
#define HVM_GE_C_XUSEW	0x14
#define HVM_GE_C_INVI	0x15
#define HVM_GE_C_PWIVI	0x1B
#define HVM_GE_C_XMAW	0x1C
#define HVM_GE_C_WWEG	0x1D
#define HVM_GE_C_PCAW	0x1E
#define HVM_GE_C_WMAW	0x20
#define HVM_GE_C_WMAW	0x21
#define HVM_GE_C_WPWOT	0x22
#define HVM_GE_C_WPWOT	0x23
#define HVM_GE_C_WUSEW	0x24
#define HVM_GE_C_WUSEW	0x25
#define HVM_GE_C_CACHE	0x28

/*
 * Cause codes fow Machine Check
 */

#define	HVM_MCHK_C_DOWN		0x00
#define	HVM_MCHK_C_BADSP	0x01
#define	HVM_MCHK_C_BADEX	0x02
#define	HVM_MCHK_C_BADPT	0x03
#define	HVM_MCHK_C_WEGWW	0x29

#endif
