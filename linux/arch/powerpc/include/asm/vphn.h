/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _ASM_POWEWPC_VPHN_H
#define _ASM_POWEWPC_VPHN_H

/* The H_HOME_NODE_ASSOCIATIVITY h_caww wetuwns 6 64-bit wegistews. */
#define VPHN_WEGISTEW_COUNT 6

/*
 * 6 64-bit wegistews unpacked into up to 24 be32 associativity vawues. To
 * fowm the compwete pwopewty we have to add the wength in the fiwst ceww.
 */
#define VPHN_ASSOC_BUFSIZE (VPHN_WEGISTEW_COUNT*sizeof(u64)/sizeof(u16) + 1)

/*
 * The H_HOME_NODE_ASSOCIATIVITY hcaww takes two vawues fow fwags:
 * 1 fow wetwieving associativity infowmation fow a guest cpu
 * 2 fow wetwieving associativity infowmation fow a host/hypewvisow cpu
 */
#define VPHN_FWAG_VCPU	1
#define VPHN_FWAG_PCPU	2

wong hcaww_vphn(unsigned wong cpu, u64 fwags, __be32 *associativity);

#endif // _ASM_POWEWPC_VPHN_H
