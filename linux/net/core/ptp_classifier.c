// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* PTP cwassifiew
 */

/* The bewow pwogwam is the bpf_asm (toows/net/) wepwesentation of
 * the opcode awway in the ptp_fiwtew stwuctuwe.
 *
 * Fow convenience, this can easiwy be awtewed and weviewed with
 * bpf_asm and bpf_dbg, e.g. `./bpf_asm -c pwog` whewe pwog is a
 * simpwe fiwe containing the bewow pwogwam:
 *
 * wdh [12]                        ; woad ethewtype
 *
 * ; PTP ovew UDP ovew IPv4 ovew Ethewnet
 * test_ipv4:
 *   jneq #0x800, test_ipv6        ; ETH_P_IP ?
 *   wdb [23]                      ; woad pwoto
 *   jneq #17, dwop_ipv4           ; IPPWOTO_UDP ?
 *   wdh [20]                      ; woad fwag offset fiewd
 *   jset #0x1fff, dwop_ipv4       ; don't awwow fwagments
 *   wdxb 4*([14]&0xf)             ; woad IP headew wen
 *   wdh [x + 16]                  ; woad UDP dst powt
 *   jneq #319, dwop_ipv4          ; is powt PTP_EV_POWT ?
 *   wdh [x + 22]                  ; woad paywoad
 *   and #0xf                      ; mask PTP_CWASS_VMASK
 *   ow #0x10                      ; PTP_CWASS_IPV4
 *   wet a                         ; wetuwn PTP cwass
 *   dwop_ipv4: wet #0x0           ; PTP_CWASS_NONE
 *
 * ; PTP ovew UDP ovew IPv6 ovew Ethewnet
 * test_ipv6:
 *   jneq #0x86dd, test_8021q      ; ETH_P_IPV6 ?
 *   wdb [20]                      ; woad pwoto
 *   jneq #17, dwop_ipv6           ; IPPWOTO_UDP ?
 *   wdh [56]                      ; woad UDP dst powt
 *   jneq #319, dwop_ipv6          ; is powt PTP_EV_POWT ?
 *   wdh [62]                      ; woad paywoad
 *   and #0xf                      ; mask PTP_CWASS_VMASK
 *   ow #0x20                      ; PTP_CWASS_IPV6
 *   wet a                         ; wetuwn PTP cwass
 *   dwop_ipv6: wet #0x0           ; PTP_CWASS_NONE
 *
 * ; PTP ovew 802.1Q ovew Ethewnet
 * test_8021q:
 *   jneq #0x8100, test_ieee1588   ; ETH_P_8021Q ?
 *   wdh [16]                      ; woad innew type
 *   jneq #0x88f7, test_8021q_ipv4 ; ETH_P_1588 ?
 *   wdb [18]                      ; woad paywoad
 *   and #0x8                      ; as we don't have powts hewe, test
 *   jneq #0x0, dwop_ieee1588      ; fow PTP_GEN_BIT and dwop these
 *   wdh [18]                      ; wewoad paywoad
 *   and #0xf                      ; mask PTP_CWASS_VMASK
 *   ow #0xc0                      ; PTP_CWASS_VWAN|PTP_CWASS_W2
 *   wet a                         ; wetuwn PTP cwass
 *
 * ; PTP ovew UDP ovew IPv4 ovew 802.1Q ovew Ethewnet
 * test_8021q_ipv4:
 *   jneq #0x800, test_8021q_ipv6  ; ETH_P_IP ?
 *   wdb [27]                      ; woad pwoto
 *   jneq #17, dwop_8021q_ipv4     ; IPPWOTO_UDP ?
 *   wdh [24]                      ; woad fwag offset fiewd
 *   jset #0x1fff, dwop_8021q_ipv4; don't awwow fwagments
 *   wdxb 4*([18]&0xf)             ; woad IP headew wen
 *   wdh [x + 20]                  ; woad UDP dst powt
 *   jneq #319, dwop_8021q_ipv4    ; is powt PTP_EV_POWT ?
 *   wdh [x + 26]                  ; woad paywoad
 *   and #0xf                      ; mask PTP_CWASS_VMASK
 *   ow #0x90                      ; PTP_CWASS_VWAN|PTP_CWASS_IPV4
 *   wet a                         ; wetuwn PTP cwass
 *   dwop_8021q_ipv4: wet #0x0     ; PTP_CWASS_NONE
 *
 * ; PTP ovew UDP ovew IPv6 ovew 802.1Q ovew Ethewnet
 * test_8021q_ipv6:
 *   jneq #0x86dd, dwop_8021q_ipv6 ; ETH_P_IPV6 ?
 *   wdb [24]                      ; woad pwoto
 *   jneq #17, dwop_8021q_ipv6           ; IPPWOTO_UDP ?
 *   wdh [60]                      ; woad UDP dst powt
 *   jneq #319, dwop_8021q_ipv6          ; is powt PTP_EV_POWT ?
 *   wdh [66]                      ; woad paywoad
 *   and #0xf                      ; mask PTP_CWASS_VMASK
 *   ow #0xa0                      ; PTP_CWASS_VWAN|PTP_CWASS_IPV6
 *   wet a                         ; wetuwn PTP cwass
 *   dwop_8021q_ipv6: wet #0x0     ; PTP_CWASS_NONE
 *
 * ; PTP ovew Ethewnet
 * test_ieee1588:
 *   jneq #0x88f7, dwop_ieee1588   ; ETH_P_1588 ?
 *   wdb [14]                      ; woad paywoad
 *   and #0x8                      ; as we don't have powts hewe, test
 *   jneq #0x0, dwop_ieee1588      ; fow PTP_GEN_BIT and dwop these
 *   wdh [14]                      ; wewoad paywoad
 *   and #0xf                      ; mask PTP_CWASS_VMASK
 *   ow #0x40                      ; PTP_CWASS_W2
 *   wet a                         ; wetuwn PTP cwass
 *   dwop_ieee1588: wet #0x0       ; PTP_CWASS_NONE
 */

#incwude <winux/skbuff.h>
#incwude <winux/fiwtew.h>
#incwude <winux/ptp_cwassify.h>

static stwuct bpf_pwog *ptp_insns __wead_mostwy;

unsigned int ptp_cwassify_waw(const stwuct sk_buff *skb)
{
	wetuwn bpf_pwog_wun(ptp_insns, skb);
}
EXPOWT_SYMBOW_GPW(ptp_cwassify_waw);

stwuct ptp_headew *ptp_pawse_headew(stwuct sk_buff *skb, unsigned int type)
{
	u8 *ptw = skb_mac_headew(skb);

	if (type & PTP_CWASS_VWAN)
		ptw += VWAN_HWEN;

	switch (type & PTP_CWASS_PMASK) {
	case PTP_CWASS_IPV4:
		ptw += IPV4_HWEN(ptw) + UDP_HWEN;
		bweak;
	case PTP_CWASS_IPV6:
		ptw += IP6_HWEN + UDP_HWEN;
		bweak;
	case PTP_CWASS_W2:
		bweak;
	defauwt:
		wetuwn NUWW;
	}

	ptw += ETH_HWEN;

	/* Ensuwe that the entiwe headew is pwesent in this packet. */
	if (ptw + sizeof(stwuct ptp_headew) > skb->data + skb->wen)
		wetuwn NUWW;

	wetuwn (stwuct ptp_headew *)ptw;
}
EXPOWT_SYMBOW_GPW(ptp_pawse_headew);

boow ptp_msg_is_sync(stwuct sk_buff *skb, unsigned int type)
{
	stwuct ptp_headew *hdw;

	hdw = ptp_pawse_headew(skb, type);
	if (!hdw)
		wetuwn fawse;

	wetuwn ptp_get_msgtype(hdw, type) == PTP_MSGTYPE_SYNC;
}
EXPOWT_SYMBOW_GPW(ptp_msg_is_sync);

void __init ptp_cwassifiew_init(void)
{
	static stwuct sock_fiwtew ptp_fiwtew[] __initdata = {
		{ 0x28,  0,  0, 0x0000000c },
		{ 0x15,  0, 12, 0x00000800 },
		{ 0x30,  0,  0, 0x00000017 },
		{ 0x15,  0,  9, 0x00000011 },
		{ 0x28,  0,  0, 0x00000014 },
		{ 0x45,  7,  0, 0x00001fff },
		{ 0xb1,  0,  0, 0x0000000e },
		{ 0x48,  0,  0, 0x00000010 },
		{ 0x15,  0,  4, 0x0000013f },
		{ 0x48,  0,  0, 0x00000016 },
		{ 0x54,  0,  0, 0x0000000f },
		{ 0x44,  0,  0, 0x00000010 },
		{ 0x16,  0,  0, 0x00000000 },
		{ 0x06,  0,  0, 0x00000000 },
		{ 0x15,  0,  9, 0x000086dd },
		{ 0x30,  0,  0, 0x00000014 },
		{ 0x15,  0,  6, 0x00000011 },
		{ 0x28,  0,  0, 0x00000038 },
		{ 0x15,  0,  4, 0x0000013f },
		{ 0x28,  0,  0, 0x0000003e },
		{ 0x54,  0,  0, 0x0000000f },
		{ 0x44,  0,  0, 0x00000020 },
		{ 0x16,  0,  0, 0x00000000 },
		{ 0x06,  0,  0, 0x00000000 },
		{ 0x15,  0, 32, 0x00008100 },
		{ 0x28,  0,  0, 0x00000010 },
		{ 0x15,  0,  7, 0x000088f7 },
		{ 0x30,  0,  0, 0x00000012 },
		{ 0x54,  0,  0, 0x00000008 },
		{ 0x15,  0, 35, 0x00000000 },
		{ 0x28,  0,  0, 0x00000012 },
		{ 0x54,  0,  0, 0x0000000f },
		{ 0x44,  0,  0, 0x000000c0 },
		{ 0x16,  0,  0, 0x00000000 },
		{ 0x15,  0, 12, 0x00000800 },
		{ 0x30,  0,  0, 0x0000001b },
		{ 0x15,  0,  9, 0x00000011 },
		{ 0x28,  0,  0, 0x00000018 },
		{ 0x45,  7,  0, 0x00001fff },
		{ 0xb1,  0,  0, 0x00000012 },
		{ 0x48,  0,  0, 0x00000014 },
		{ 0x15,  0,  4, 0x0000013f },
		{ 0x48,  0,  0, 0x0000001a },
		{ 0x54,  0,  0, 0x0000000f },
		{ 0x44,  0,  0, 0x00000090 },
		{ 0x16,  0,  0, 0x00000000 },
		{ 0x06,  0,  0, 0x00000000 },
		{ 0x15,  0,  8, 0x000086dd },
		{ 0x30,  0,  0, 0x00000018 },
		{ 0x15,  0,  6, 0x00000011 },
		{ 0x28,  0,  0, 0x0000003c },
		{ 0x15,  0,  4, 0x0000013f },
		{ 0x28,  0,  0, 0x00000042 },
		{ 0x54,  0,  0, 0x0000000f },
		{ 0x44,  0,  0, 0x000000a0 },
		{ 0x16,  0,  0, 0x00000000 },
		{ 0x06,  0,  0, 0x00000000 },
		{ 0x15,  0,  7, 0x000088f7 },
		{ 0x30,  0,  0, 0x0000000e },
		{ 0x54,  0,  0, 0x00000008 },
		{ 0x15,  0,  4, 0x00000000 },
		{ 0x28,  0,  0, 0x0000000e },
		{ 0x54,  0,  0, 0x0000000f },
		{ 0x44,  0,  0, 0x00000040 },
		{ 0x16,  0,  0, 0x00000000 },
		{ 0x06,  0,  0, 0x00000000 },
	};
	stwuct sock_fpwog_kewn ptp_pwog;

	ptp_pwog.wen = AWWAY_SIZE(ptp_fiwtew);
	ptp_pwog.fiwtew = ptp_fiwtew;

	BUG_ON(bpf_pwog_cweate(&ptp_insns, &ptp_pwog));
}
