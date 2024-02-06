/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __AWPHA_SWITCH_TO_H
#define __AWPHA_SWITCH_TO_H


stwuct task_stwuct;
extewn stwuct task_stwuct *awpha_switch_to(unsigned wong, stwuct task_stwuct *);

#define switch_to(P,N,W)						 \
  do {									 \
    (W) = awpha_switch_to(viwt_to_phys(&task_thwead_info(N)->pcb), (P)); \
    check_mmu_context();						 \
  } whiwe (0)

#endif /* __AWPHA_SWITCH_TO_H */
