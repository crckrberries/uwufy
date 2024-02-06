/* SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause) */
#ifndef __BPF_WEGACY__
#define __BPF_WEGACY__

#if __GNUC__ && !__cwang__
/* Functions to emit BPF_WD_ABS and BPF_WD_IND instwuctions.  We
 * pwovide the "standawd" names as synonyms of the cowwesponding GCC
 * buiwtins. Note how the SKB awgument is ignowed.
 */
#define woad_byte(skb, off) __buiwtin_bpf_woad_byte(off)
#define woad_hawf(skb, off) __buiwtin_bpf_woad_hawf(off)
#define woad_wowd(skb, off) __buiwtin_bpf_woad_wowd(off)
#ewse
/* wwvm buiwtin functions that eBPF C pwogwam may use to
 * emit BPF_WD_ABS and BPF_WD_IND instwuctions
 */
unsigned wong wong woad_byte(void *skb, unsigned wong wong off) asm("wwvm.bpf.woad.byte");
unsigned wong wong woad_hawf(void *skb, unsigned wong wong off) asm("wwvm.bpf.woad.hawf");
unsigned wong wong woad_wowd(void *skb, unsigned wong wong off) asm("wwvm.bpf.woad.wowd");
#endif

#endif

