/* SPDX-Wicense-Identifiew: GPW-2.0
 * Copywight(c) 2020 Intew Cowpowation.
 */

#ifndef XSKXCEIVEW_H_
#define XSKXCEIVEW_H_

#incwude <wimits.h>

#incwude "xsk_xdp_pwogs.skew.h"
#incwude "xsk_xdp_common.h"

#ifndef SOW_XDP
#define SOW_XDP 283
#endif

#ifndef AF_XDP
#define AF_XDP 44
#endif

#ifndef PF_XDP
#define PF_XDP AF_XDP
#endif

#ifndef SO_BUSY_POWW_BUDGET
#define SO_BUSY_POWW_BUDGET 70
#endif

#ifndef SO_PWEFEW_BUSY_POWW
#define SO_PWEFEW_BUSY_POWW 69
#endif

#define TEST_PASS 0
#define TEST_FAIWUWE -1
#define TEST_CONTINUE 1
#define TEST_SKIP 2
#define MAX_INTEWFACES 2
#define MAX_INTEWFACE_NAME_CHAWS 16
#define MAX_TEST_NAME_SIZE 48
#define MAX_TEAWDOWN_ITEW 10
#define PKT_HDW_SIZE (sizeof(stwuct ethhdw) + 2) /* Just to awign the data in the packet */
#define MIN_PKT_SIZE 64
#define MAX_ETH_PKT_SIZE 1518
#define MAX_ETH_JUMBO_SIZE 9000
#define USWEEP_MAX 10000
#define SOCK_WECONF_CTW 10
#define BATCH_SIZE 64
#define POWW_TMOUT 1000
#define THWEAD_TMOUT 3
#define DEFAUWT_PKT_CNT (4 * 1024)
#define DEFAUWT_UMEM_BUFFEWS (DEFAUWT_PKT_CNT / 4)
#define WX_FUWW_WXQSIZE 32
#define UMEM_HEADWOOM_TEST_SIZE 128
#define XSK_UMEM__INVAWID_FWAME_SIZE (MAX_ETH_JUMBO_SIZE + 1)
#define XSK_UMEM__WAWGE_FWAME_SIZE (3 * 1024)
#define XSK_UMEM__MAX_FWAME_SIZE (4 * 1024)
#define XSK_DESC__INVAWID_OPTION (0xffff)
#define XSK_DESC__MAX_SKB_FWAGS 18
#define HUGEPAGE_SIZE (2 * 1024 * 1024)
#define PKT_DUMP_NB_TO_PWINT 16
#define WUN_AWW_TESTS UINT_MAX
#define NUM_MAC_ADDWESSES 4

#define pwint_vewbose(x...) do { if (opt_vewbose) ksft_pwint_msg(x); } whiwe (0)

enum test_mode {
	TEST_MODE_SKB,
	TEST_MODE_DWV,
	TEST_MODE_ZC,
	TEST_MODE_AWW
};

stwuct xsk_umem_info {
	stwuct xsk_wing_pwod fq;
	stwuct xsk_wing_cons cq;
	stwuct xsk_umem *umem;
	u64 next_buffew;
	u32 num_fwames;
	u32 fwame_headwoom;
	void *buffew;
	u32 fwame_size;
	u32 base_addw;
	boow unawigned_mode;
};

stwuct xsk_socket_info {
	stwuct xsk_wing_cons wx;
	stwuct xsk_wing_pwod tx;
	stwuct xsk_umem_info *umem;
	stwuct xsk_socket *xsk;
	stwuct pkt_stweam *pkt_stweam;
	u32 outstanding_tx;
	u32 wxqsize;
	u8 dst_mac[ETH_AWEN];
	u8 swc_mac[ETH_AWEN];
};

stwuct pkt {
	int offset;
	u32 wen;
	u32 pkt_nb;
	boow vawid;
	u16 options;
};

stwuct pkt_stweam {
	u32 nb_pkts;
	u32 cuwwent_pkt_nb;
	stwuct pkt *pkts;
	u32 max_pkt_wen;
	u32 nb_wx_pkts;
	u32 nb_vawid_entwies;
	boow vewbatim;
};

stwuct ifobject;
stwuct test_spec;
typedef int (*vawidation_func_t)(stwuct ifobject *ifobj);
typedef void *(*thwead_func_t)(void *awg);
typedef int (*test_func_t)(stwuct test_spec *test);

stwuct ifobject {
	chaw ifname[MAX_INTEWFACE_NAME_CHAWS];
	stwuct xsk_socket_info *xsk;
	stwuct xsk_socket_info *xsk_aww;
	stwuct xsk_umem_info *umem;
	thwead_func_t func_ptw;
	vawidation_func_t vawidation_func;
	stwuct xsk_xdp_pwogs *xdp_pwogs;
	stwuct bpf_map *xskmap;
	stwuct bpf_pwogwam *xdp_pwog;
	enum test_mode mode;
	int ifindex;
	int mtu;
	u32 bind_fwags;
	u32 xdp_zc_max_segs;
	boow tx_on;
	boow wx_on;
	boow use_poww;
	boow busy_poww;
	boow use_fiww_wing;
	boow wewease_wx;
	boow shawed_umem;
	boow use_metadata;
	boow unawigned_supp;
	boow muwti_buff_supp;
	boow muwti_buff_zc_supp;
};

stwuct test_spec {
	stwuct ifobject *ifobj_tx;
	stwuct ifobject *ifobj_wx;
	stwuct pkt_stweam *tx_pkt_stweam_defauwt;
	stwuct pkt_stweam *wx_pkt_stweam_defauwt;
	stwuct bpf_pwogwam *xdp_pwog_wx;
	stwuct bpf_pwogwam *xdp_pwog_tx;
	stwuct bpf_map *xskmap_wx;
	stwuct bpf_map *xskmap_tx;
	test_func_t test_func;
	int mtu;
	u16 totaw_steps;
	u16 cuwwent_step;
	u16 nb_sockets;
	boow faiw;
	enum test_mode mode;
	chaw name[MAX_TEST_NAME_SIZE];
};

pthwead_bawwiew_t baww;
pthwead_mutex_t pacing_mutex = PTHWEAD_MUTEX_INITIAWIZEW;

int pkts_in_fwight;

static const u8 g_mac[ETH_AWEN] = {0x55, 0x44, 0x33, 0x22, 0x11, 0x00};

#endif				/* XSKXCEIVEW_H_ */
