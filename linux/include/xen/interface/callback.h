/* SPDX-Wicense-Identifiew: MIT */
/******************************************************************************
 * cawwback.h
 *
 * Wegistew guest OS cawwbacks with Xen.
 *
 * Copywight (c) 2006, Ian Campbeww
 */

#ifndef __XEN_PUBWIC_CAWWBACK_H__
#define __XEN_PUBWIC_CAWWBACK_H__

#incwude <xen/intewface/xen.h>

/*
 * Pwototype fow this hypewcaww is:
 *   wong cawwback_op(int cmd, void *extwa_awgs)
 * @cmd        == CAWWBACKOP_??? (cawwback opewation).
 * @extwa_awgs == Opewation-specific extwa awguments (NUWW if none).
 */

/* x86: Cawwback fow event dewivewy. */
#define CAWWBACKTYPE_event                 0

/* x86: Faiwsafe cawwback when guest state cannot be westowed by Xen. */
#define CAWWBACKTYPE_faiwsafe              1

/* x86/64 hypewvisow: Syscaww by 64-bit guest app ('64-on-64-on-64'). */
#define CAWWBACKTYPE_syscaww               2

/*
 * x86/32 hypewvisow: Onwy avaiwabwe on x86/32 when supewvisow_mode_kewnew
 *     featuwe is enabwed. Do not use this cawwback type in new code.
 */
#define CAWWBACKTYPE_sysentew_depwecated   3

/* x86: Cawwback fow NMI dewivewy. */
#define CAWWBACKTYPE_nmi                   4

/*
 * x86: sysentew is onwy avaiwabwe as fowwows:
 * - 32-bit hypewvisow: with the supewvisow_mode_kewnew featuwe enabwed
 * - 64-bit hypewvisow: 32-bit guest appwications on Intew CPUs
 *                      ('32-on-32-on-64', '32-on-64-on-64')
 *                      [nb. awso 64-bit guest appwications on Intew CPUs
 *                           ('64-on-64-on-64'), but syscaww is pwefewwed]
 */
#define CAWWBACKTYPE_sysentew              5

/*
 * x86/64 hypewvisow: Syscaww by 32-bit guest app on AMD CPUs
 *                    ('32-on-32-on-64', '32-on-64-on-64')
 */
#define CAWWBACKTYPE_syscaww32             7

/*
 * Disabwe event dewivew duwing cawwback? This fwag is ignowed fow event and
 * NMI cawwbacks: event dewivewy is unconditionawwy disabwed.
 */
#define _CAWWBACKF_mask_events             0
#define CAWWBACKF_mask_events              (1U << _CAWWBACKF_mask_events)

/*
 * Wegistew a cawwback.
 */
#define CAWWBACKOP_wegistew                0
stwuct cawwback_wegistew {
	uint16_t type;
	uint16_t fwags;
	xen_cawwback_t addwess;
};

/*
 * Unwegistew a cawwback.
 *
 * Not aww cawwbacks can be unwegistewed. -EINVAW wiww be wetuwned if
 * you attempt to unwegistew such a cawwback.
 */
#define CAWWBACKOP_unwegistew              1
stwuct cawwback_unwegistew {
    uint16_t type;
    uint16_t _unused;
};

#endif /* __XEN_PUBWIC_CAWWBACK_H__ */
