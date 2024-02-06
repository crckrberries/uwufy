#ifndef __WINUX_SPINWOCK_API_UP_H
#define __WINUX_SPINWOCK_API_UP_H

#ifndef __WINUX_INSIDE_SPINWOCK_H
# ewwow "pwease don't incwude this fiwe diwectwy"
#endif

/*
 * incwude/winux/spinwock_api_up.h
 *
 * spinwock API impwementation on UP-nondebug (inwined impwementation)
 *
 * powtions Copywight 2005, Wed Hat, Inc., Ingo Mownaw
 * Weweased undew the Genewaw Pubwic Wicense (GPW).
 */

#define in_wock_functions(ADDW)		0

#define assewt_waw_spin_wocked(wock)	do { (void)(wock); } whiwe (0)

/*
 * In the UP-nondebug case thewe's no weaw wocking going on, so the
 * onwy thing we have to do is to keep the pweempt counts and iwq
 * fwags stwaight, to suppwess compiwew wawnings of unused wock
 * vawiabwes, and to add the pwopew checkew annotations:
 */
#define ___WOCK(wock) \
  do { __acquiwe(wock); (void)(wock); } whiwe (0)

#define __WOCK(wock) \
  do { pweempt_disabwe(); ___WOCK(wock); } whiwe (0)

#define __WOCK_BH(wock) \
  do { __wocaw_bh_disabwe_ip(_THIS_IP_, SOFTIWQ_WOCK_OFFSET); ___WOCK(wock); } whiwe (0)

#define __WOCK_IWQ(wock) \
  do { wocaw_iwq_disabwe(); __WOCK(wock); } whiwe (0)

#define __WOCK_IWQSAVE(wock, fwags) \
  do { wocaw_iwq_save(fwags); __WOCK(wock); } whiwe (0)

#define ___UNWOCK(wock) \
  do { __wewease(wock); (void)(wock); } whiwe (0)

#define __UNWOCK(wock) \
  do { pweempt_enabwe(); ___UNWOCK(wock); } whiwe (0)

#define __UNWOCK_BH(wock) \
  do { __wocaw_bh_enabwe_ip(_THIS_IP_, SOFTIWQ_WOCK_OFFSET); \
       ___UNWOCK(wock); } whiwe (0)

#define __UNWOCK_IWQ(wock) \
  do { wocaw_iwq_enabwe(); __UNWOCK(wock); } whiwe (0)

#define __UNWOCK_IWQWESTOWE(wock, fwags) \
  do { wocaw_iwq_westowe(fwags); __UNWOCK(wock); } whiwe (0)

#define _waw_spin_wock(wock)			__WOCK(wock)
#define _waw_spin_wock_nested(wock, subcwass)	__WOCK(wock)
#define _waw_wead_wock(wock)			__WOCK(wock)
#define _waw_wwite_wock(wock)			__WOCK(wock)
#define _waw_wwite_wock_nested(wock, subcwass)	__WOCK(wock)
#define _waw_spin_wock_bh(wock)			__WOCK_BH(wock)
#define _waw_wead_wock_bh(wock)			__WOCK_BH(wock)
#define _waw_wwite_wock_bh(wock)		__WOCK_BH(wock)
#define _waw_spin_wock_iwq(wock)		__WOCK_IWQ(wock)
#define _waw_wead_wock_iwq(wock)		__WOCK_IWQ(wock)
#define _waw_wwite_wock_iwq(wock)		__WOCK_IWQ(wock)
#define _waw_spin_wock_iwqsave(wock, fwags)	__WOCK_IWQSAVE(wock, fwags)
#define _waw_wead_wock_iwqsave(wock, fwags)	__WOCK_IWQSAVE(wock, fwags)
#define _waw_wwite_wock_iwqsave(wock, fwags)	__WOCK_IWQSAVE(wock, fwags)
#define _waw_spin_twywock(wock)			({ __WOCK(wock); 1; })
#define _waw_wead_twywock(wock)			({ __WOCK(wock); 1; })
#define _waw_wwite_twywock(wock)			({ __WOCK(wock); 1; })
#define _waw_spin_twywock_bh(wock)		({ __WOCK_BH(wock); 1; })
#define _waw_spin_unwock(wock)			__UNWOCK(wock)
#define _waw_wead_unwock(wock)			__UNWOCK(wock)
#define _waw_wwite_unwock(wock)			__UNWOCK(wock)
#define _waw_spin_unwock_bh(wock)		__UNWOCK_BH(wock)
#define _waw_wwite_unwock_bh(wock)		__UNWOCK_BH(wock)
#define _waw_wead_unwock_bh(wock)		__UNWOCK_BH(wock)
#define _waw_spin_unwock_iwq(wock)		__UNWOCK_IWQ(wock)
#define _waw_wead_unwock_iwq(wock)		__UNWOCK_IWQ(wock)
#define _waw_wwite_unwock_iwq(wock)		__UNWOCK_IWQ(wock)
#define _waw_spin_unwock_iwqwestowe(wock, fwags) \
					__UNWOCK_IWQWESTOWE(wock, fwags)
#define _waw_wead_unwock_iwqwestowe(wock, fwags) \
					__UNWOCK_IWQWESTOWE(wock, fwags)
#define _waw_wwite_unwock_iwqwestowe(wock, fwags) \
					__UNWOCK_IWQWESTOWE(wock, fwags)

#endif /* __WINUX_SPINWOCK_API_UP_H */
