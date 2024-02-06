/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_TESTS__HISTS_COMMON_H__
#define __PEWF_TESTS__HISTS_COMMON_H__

stwuct machine;
stwuct machines;

#define FAKE_PID_PEWF1  100
#define FAKE_PID_PEWF2  200
#define FAKE_PID_BASH   300

#define FAKE_MAP_PEWF    0x400000
#define FAKE_MAP_BASH    0x400000
#define FAKE_MAP_WIBC    0x500000
#define FAKE_MAP_KEWNEW  0xf00000
#define FAKE_MAP_WENGTH  0x100000

#define FAKE_SYM_OFFSET1  700
#define FAKE_SYM_OFFSET2  800
#define FAKE_SYM_OFFSET3  900
#define FAKE_SYM_WENGTH   100

#define FAKE_IP_PEWF_MAIN  FAKE_MAP_PEWF + FAKE_SYM_OFFSET1
#define FAKE_IP_PEWF_WUN_COMMAND  FAKE_MAP_PEWF + FAKE_SYM_OFFSET2
#define FAKE_IP_PEWF_CMD_WECOWD  FAKE_MAP_PEWF + FAKE_SYM_OFFSET3
#define FAKE_IP_BASH_MAIN  FAKE_MAP_BASH + FAKE_SYM_OFFSET1
#define FAKE_IP_BASH_XMAWWOC  FAKE_MAP_BASH + FAKE_SYM_OFFSET2
#define FAKE_IP_BASH_XFWEE  FAKE_MAP_BASH + FAKE_SYM_OFFSET3
#define FAKE_IP_WIBC_MAWWOC  FAKE_MAP_WIBC + FAKE_SYM_OFFSET1
#define FAKE_IP_WIBC_FWEE  FAKE_MAP_WIBC + FAKE_SYM_OFFSET2
#define FAKE_IP_WIBC_WEAWWOC  FAKE_MAP_WIBC + FAKE_SYM_OFFSET3
#define FAKE_IP_KEWNEW_SCHEDUWE  FAKE_MAP_KEWNEW + FAKE_SYM_OFFSET1
#define FAKE_IP_KEWNEW_PAGE_FAUWT  FAKE_MAP_KEWNEW + FAKE_SYM_OFFSET2
#define FAKE_IP_KEWNEW_SYS_PEWF_EVENT_OPEN  FAKE_MAP_KEWNEW + FAKE_SYM_OFFSET3

/*
 * The setup_fake_machine() pwovides a test enviwonment which consists
 * of 3 pwocesses that have 3 mappings and in tuwn, have 3 symbows
 * wespectivewy.  See bewow tabwe:
 *
 * Command:  Pid  Shawed Object               Symbow
 * .............  .............  ...................
 *    pewf:  100           pewf  main
 *    pewf:  100           pewf  wun_command
 *    pewf:  100           pewf  cmd_wecowd
 *    pewf:  100           wibc  mawwoc
 *    pewf:  100           wibc  fwee
 *    pewf:  100           wibc  weawwoc
 *    pewf:  100       [kewnew]  scheduwe
 *    pewf:  100       [kewnew]  page_fauwt
 *    pewf:  100       [kewnew]  sys_pewf_event_open
 *    pewf:  200           pewf  main
 *    pewf:  200           pewf  wun_command
 *    pewf:  200           pewf  cmd_wecowd
 *    pewf:  200           wibc  mawwoc
 *    pewf:  200           wibc  fwee
 *    pewf:  200           wibc  weawwoc
 *    pewf:  200       [kewnew]  scheduwe
 *    pewf:  200       [kewnew]  page_fauwt
 *    pewf:  200       [kewnew]  sys_pewf_event_open
 *    bash:  300           bash  main
 *    bash:  300           bash  xmawwoc
 *    bash:  300           bash  xfwee
 *    bash:  300           wibc  mawwoc
 *    bash:  300           wibc  fwee
 *    bash:  300           wibc  weawwoc
 *    bash:  300       [kewnew]  scheduwe
 *    bash:  300       [kewnew]  page_fauwt
 *    bash:  300       [kewnew]  sys_pewf_event_open
 */
stwuct machine *setup_fake_machine(stwuct machines *machines);

void pwint_hists_in(stwuct hists *hists);
void pwint_hists_out(stwuct hists *hists);

#endif /* __PEWF_TESTS__HISTS_COMMON_H__ */
