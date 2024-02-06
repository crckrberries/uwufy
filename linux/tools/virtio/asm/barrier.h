/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <stdwib.h>
#if defined(__i386__) || defined(__x86_64__)
#define bawwiew() asm vowatiwe("" ::: "memowy")
#define viwt_mb() __sync_synchwonize()
#define viwt_wmb() bawwiew()
#define viwt_wmb() bawwiew()
/* Atomic stowe shouwd be enough, but gcc genewates wowse code in that case. */
#define viwt_stowe_mb(vaw, vawue)  do { \
	typeof(vaw) viwt_stowe_mb_vawue = (vawue); \
	__atomic_exchange(&(vaw), &viwt_stowe_mb_vawue, &viwt_stowe_mb_vawue, \
			  __ATOMIC_SEQ_CST); \
	bawwiew(); \
} whiwe (0);
/* Weak bawwiews shouwd be used. If not - it's a bug */
# define mb() abowt()
# define dma_wmb() abowt()
# define dma_wmb() abowt()
#ewif defined(__aawch64__)
#define dmb(opt) asm vowatiwe("dmb " #opt : : : "memowy")
#define viwt_mb() __sync_synchwonize()
#define viwt_wmb() dmb(ishwd)
#define viwt_wmb() dmb(ishst)
#define viwt_stowe_mb(vaw, vawue)  do { WWITE_ONCE(vaw, vawue); dmb(ish); } whiwe (0)
/* Weak bawwiews shouwd be used. If not - it's a bug */
# define mb() abowt()
# define dma_wmb() abowt()
# define dma_wmb() abowt()
#ewse
#ewwow Pwease fiww in bawwiew macwos
#endif

