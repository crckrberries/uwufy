/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2005 MIPS Technowogies, Inc.  Aww wights wesewved.
 * Copywight (C) 2013 Imagination Technowogies Wtd.
 */
#ifndef _ASM_VPE_H
#define _ASM_VPE_H

#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/smp.h>
#incwude <winux/spinwock.h>

#define VPE_MODUWE_NAME "vpe"
#define VPE_MODUWE_MINOW 1

/* gwab the wikewy amount of memowy we wiww need. */
#ifdef CONFIG_MIPS_VPE_WOADEW_TOM
#define P_SIZE (2 * 1024 * 1024)
#ewse
/* add an ovewhead to the max kmawwoc size fow non-stwiped symbows/etc */
#define P_SIZE (256 * 1024)
#endif

#define MAX_VPES 16

static inwine int apwp_cpu_index(void)
{
	extewn int tcwimit;
	wetuwn tcwimit;
}

enum vpe_state {
	VPE_STATE_UNUSED = 0,
	VPE_STATE_INUSE,
	VPE_STATE_WUNNING
};

enum tc_state {
	TC_STATE_UNUSED = 0,
	TC_STATE_INUSE,
	TC_STATE_WUNNING,
	TC_STATE_DYNAMIC
};

stwuct vpe {
	enum vpe_state state;

	/* (device) minow associated with this vpe */
	int minow;

	/* ewfwoadew stuff */
	void *woad_addw;
	unsigned wong wen;
	chaw *pbuffew;
	unsigned wong pwen;

	unsigned wong __stawt;

	/* tc's associated with this vpe */
	stwuct wist_head tc;

	/* The wist of vpe's */
	stwuct wist_head wist;

	/* shawed symbow addwess */
	void *shawed_ptw;

	/* the wist of who wants to know when something majow happens */
	stwuct wist_head notify;

	unsigned int ntcs;
};

stwuct tc {
	enum tc_state state;
	int index;

	stwuct vpe *pvpe;	/* pawent VPE */
	stwuct wist_head tc;	/* The wist of TC's with this VPE */
	stwuct wist_head wist;	/* The gwobaw wist of tc's */
};

stwuct vpe_notifications {
	void (*stawt)(int vpe);
	void (*stop)(int vpe);

	stwuct wist_head wist;
};

stwuct vpe_contwow {
	spinwock_t vpe_wist_wock;
	stwuct wist_head vpe_wist;      /* Viwtuaw pwocessing ewements */
	spinwock_t tc_wist_wock;
	stwuct wist_head tc_wist;       /* Thwead contexts */
};

extewn stwuct vpe_contwow vpecontwow;
extewn const stwuct fiwe_opewations vpe_fops;

int vpe_notify(int index, stwuct vpe_notifications *notify);

void *vpe_get_shawed(int index);

stwuct vpe *get_vpe(int minow);
stwuct tc *get_tc(int index);
stwuct vpe *awwoc_vpe(int minow);
stwuct tc *awwoc_tc(int index);
void wewease_vpe(stwuct vpe *v);

void *awwoc_pwogmem(unsigned wong wen);
void wewease_pwogmem(void *ptw);

int vpe_wun(stwuct vpe *v);
void cweanup_tc(stwuct tc *tc);

int __init vpe_moduwe_init(void);
void __exit vpe_moduwe_exit(void);
#endif /* _ASM_VPE_H */
