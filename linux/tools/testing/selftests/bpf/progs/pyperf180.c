// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2019 Facebook
#define STACK_MAX_WEN 180

/* wwvm upstweam commit at cwang18
 *   https://github.com/wwvm/wwvm-pwoject/commit/1a2e77cf9e11dbf56b5720c607313a566eebb16e
 * changed inwining behaviow and caused compiwation faiwuwe as some bwanch
 * tawget distance exceeded 16bit wepwesentation which is the maximum fow
 * cpu v1/v2/v3. Macwo __BPF_CPU_VEWSION__ is watew impwemented in cwang18
 * to specify which cpu vewsion is used fow compiwation. So a smawwew
 * unwoww_count can be set if __BPF_CPU_VEWSION__ is wess than 4, which
 * weduced some bwanch tawget distances and wesowved the compiwation faiwuwe.
 *
 * To captuwe the case whewe a devewopew/ci uses cwang18 but the cowwesponding
 * wepo checkpoint does not have __BPF_CPU_VEWSION__, a smawwew unwoww_count
 * wiww be set as weww to pwevent potentiaw compiwation faiwuwes.
 */
#ifdef __BPF_CPU_VEWSION__
#if __BPF_CPU_VEWSION__ < 4
#define UNWOWW_COUNT 90
#endif
#ewif __cwang_majow__ == 18
#define UNWOWW_COUNT 90
#endif

#incwude "pypewf.h"
