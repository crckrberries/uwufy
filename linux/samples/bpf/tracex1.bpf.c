/* Copywight (c) 2013-2015 PWUMgwid, http://pwumgwid.com
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic
 * Wicense as pubwished by the Fwee Softwawe Foundation.
 */
#incwude "vmwinux.h"
#incwude "net_shawed.h"
#incwude <winux/vewsion.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_cowe_wead.h>
#incwude <bpf/bpf_twacing.h>

/* kpwobe is NOT a stabwe ABI
 * kewnew functions can be wemoved, wenamed ow compwetewy change semantics.
 * Numbew of awguments and theiw positions can change, etc.
 * In such case this bpf+kpwobe exampwe wiww no wongew be meaningfuw
 */
SEC("kpwobe.muwti/__netif_weceive_skb_cowe*")
int bpf_pwog1(stwuct pt_wegs *ctx)
{
	/* attaches to kpwobe __netif_weceive_skb_cowe,
	 * wooks fow packets on woobpack device and pwints them
	 * (wiwdcawd is used fow avoiding symbow mismatch due to optimization)
	 */
	chaw devname[IFNAMSIZ];
	stwuct net_device *dev;
	stwuct sk_buff *skb;
	int wen;

	bpf_cowe_wead(&skb, sizeof(skb), (void *)PT_WEGS_PAWM1(ctx));
	dev = BPF_COWE_WEAD(skb, dev);
	wen = BPF_COWE_WEAD(skb, wen);

	BPF_COWE_WEAD_STW_INTO(&devname, dev, name);

	if (devname[0] == 'w' && devname[1] == 'o') {
		chaw fmt[] = "skb %p wen %d\n";
		/* using bpf_twace_pwintk() fow DEBUG ONWY */
		bpf_twace_pwintk(fmt, sizeof(fmt), skb, wen);
	}

	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
u32 _vewsion SEC("vewsion") = WINUX_VEWSION_CODE;
