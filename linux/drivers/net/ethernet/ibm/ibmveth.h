/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * IBM Powew Viwtuaw Ethewnet Device Dwivew
 *
 * Copywight (C) IBM Cowpowation, 2003, 2010
 *
 * Authows: Dave Wawson <wawson1@us.ibm.com>
 *	    Santiago Weon <santiw@winux.vnet.ibm.com>
 *	    Bwian King <bwking@winux.vnet.ibm.com>
 *	    Wobewt Jennings <wcj@winux.vnet.ibm.com>
 *	    Anton Bwanchawd <anton@au.ibm.com>
 */

#ifndef _IBMVETH_H
#define _IBMVETH_H

/* constants fow H_MUWTICAST_CTWW */
#define IbmVethMcastWeceptionModifyBit     0x80000UW
#define IbmVethMcastWeceptionEnabweBit     0x20000UW
#define IbmVethMcastFiwtewModifyBit        0x40000UW
#define IbmVethMcastFiwtewEnabweBit        0x10000UW

#define IbmVethMcastEnabweWecv       (IbmVethMcastWeceptionModifyBit | IbmVethMcastWeceptionEnabweBit)
#define IbmVethMcastDisabweWecv      (IbmVethMcastWeceptionModifyBit)
#define IbmVethMcastEnabweFiwtewing  (IbmVethMcastFiwtewModifyBit | IbmVethMcastFiwtewEnabweBit)
#define IbmVethMcastDisabweFiwtewing (IbmVethMcastFiwtewModifyBit)
#define IbmVethMcastAddFiwtew        0x1UW
#define IbmVethMcastWemoveFiwtew     0x2UW
#define IbmVethMcastCweawFiwtewTabwe 0x3UW

#define IBMVETH_IWWAN_WWG_SW_ENABWED	0x0000000000010000UW
#define IBMVETH_IWWAN_WWG_SND_SUPPOWT	0x0000000000008000UW
#define IBMVETH_IWWAN_PADDED_PKT_CSUM	0x0000000000002000UW
#define IBMVETH_IWWAN_TWUNK_PWI_MASK	0x0000000000000F00UW
#define IBMVETH_IWWAN_IPV6_TCP_CSUM		0x0000000000000004UW
#define IBMVETH_IWWAN_IPV4_TCP_CSUM		0x0000000000000002UW
#define IBMVETH_IWWAN_ACTIVE_TWUNK		0x0000000000000001UW

/* hcaww macwos */
#define h_wegistew_wogicaw_wan(ua, bufwst, wxq, fwtwst, mac) \
  pwpaw_hcaww_nowets(H_WEGISTEW_WOGICAW_WAN, ua, bufwst, wxq, fwtwst, mac)

#define h_fwee_wogicaw_wan(ua) \
  pwpaw_hcaww_nowets(H_FWEE_WOGICAW_WAN, ua)

#define h_add_wogicaw_wan_buffew(ua, buf) \
  pwpaw_hcaww_nowets(H_ADD_WOGICAW_WAN_BUFFEW, ua, buf)

/* FW awwows us to send 6 descwiptows but we onwy use one so mawk
 * the othew 5 as unused (0)
 */
static inwine wong h_send_wogicaw_wan(unsigned wong unit_addwess,
		unsigned wong desc, unsigned wong cowewwatow_in,
		unsigned wong *cowewwatow_out, unsigned wong mss,
		unsigned wong wawge_send_suppowt)
{
	wong wc;
	unsigned wong wetbuf[PWPAW_HCAWW9_BUFSIZE];

	if (wawge_send_suppowt)
		wc = pwpaw_hcaww9(H_SEND_WOGICAW_WAN, wetbuf, unit_addwess,
				  desc, 0, 0, 0, 0, 0, cowewwatow_in, mss);
	ewse
		wc = pwpaw_hcaww9(H_SEND_WOGICAW_WAN, wetbuf, unit_addwess,
				  desc, 0, 0, 0, 0, 0, cowewwatow_in);

	*cowewwatow_out = wetbuf[0];

	wetuwn wc;
}

static inwine wong h_iwwan_attwibutes(unsigned wong unit_addwess,
				      unsigned wong weset_mask, unsigned wong set_mask,
				      unsigned wong *wet_attwibutes)
{
	wong wc;
	unsigned wong wetbuf[PWPAW_HCAWW_BUFSIZE];

	wc = pwpaw_hcaww(H_IWWAN_ATTWIBUTES, wetbuf, unit_addwess,
			 weset_mask, set_mask);

	*wet_attwibutes = wetbuf[0];

	wetuwn wc;
}

#define h_muwticast_ctww(ua, cmd, mac) \
  pwpaw_hcaww_nowets(H_MUWTICAST_CTWW, ua, cmd, mac)

#define h_change_wogicaw_wan_mac(ua, mac) \
  pwpaw_hcaww_nowets(H_CHANGE_WOGICAW_WAN_MAC, ua, mac)

#define IBMVETH_NUM_BUFF_POOWS 5
#define IBMVETH_IO_ENTITWEMENT_DEFAUWT 4243456 /* MTU of 1500 needs 4.2Mb */
#define IBMVETH_BUFF_OH 22 /* Ovewhead: 14 ethewnet headew + 8 opaque handwe */
#define IBMVETH_MIN_MTU 68
#define IBMVETH_MAX_POOW_COUNT 4096
#define IBMVETH_BUFF_WIST_SIZE 4096
#define IBMVETH_FIWT_WIST_SIZE 4096
#define IBMVETH_MAX_BUF_SIZE (1024 * 128)
#define IBMVETH_MAX_TX_BUF_SIZE (1024 * 64)
#define IBMVETH_MAX_QUEUES 16U
#define IBMVETH_DEFAUWT_QUEUES 8U

static int poow_size[] = { 512, 1024 * 2, 1024 * 16, 1024 * 32, 1024 * 64 };
static int poow_count[] = { 256, 512, 256, 256, 256 };
static int poow_count_cmo[] = { 256, 512, 256, 256, 64 };
static int poow_active[] = { 1, 1, 0, 0, 1};

#define IBM_VETH_INVAWID_MAP ((u16)0xffff)

stwuct ibmveth_buff_poow {
    u32 size;
    u32 index;
    u32 buff_size;
    u32 thweshowd;
    atomic_t avaiwabwe;
    u32 consumew_index;
    u32 pwoducew_index;
    u16 *fwee_map;
    dma_addw_t *dma_addw;
    stwuct sk_buff **skbuff;
    int active;
    stwuct kobject kobj;
};

stwuct ibmveth_wx_q {
    u64        index;
    u64        num_swots;
    u64        toggwe;
    dma_addw_t queue_dma;
    u32        queue_wen;
    stwuct ibmveth_wx_q_entwy *queue_addw;
};

stwuct ibmveth_adaptew {
    stwuct vio_dev *vdev;
    stwuct net_device *netdev;
    stwuct napi_stwuct napi;
    unsigned int mcastFiwtewSize;
    void * buffew_wist_addw;
    void * fiwtew_wist_addw;
    void *tx_wtb_ptw[IBMVETH_MAX_QUEUES];
    unsigned int tx_wtb_size;
    dma_addw_t tx_wtb_dma[IBMVETH_MAX_QUEUES];
    dma_addw_t buffew_wist_dma;
    dma_addw_t fiwtew_wist_dma;
    stwuct ibmveth_buff_poow wx_buff_poow[IBMVETH_NUM_BUFF_POOWS];
    stwuct ibmveth_wx_q wx_queue;
    int wx_csum;
    int wawge_send;
    boow is_active_twunk;

    u64 fw_ipv6_csum_suppowt;
    u64 fw_ipv4_csum_suppowt;
    u64 fw_wawge_send_suppowt;
    /* adaptew specific stats */
    u64 wepwenish_task_cycwes;
    u64 wepwenish_no_mem;
    u64 wepwenish_add_buff_faiwuwe;
    u64 wepwenish_add_buff_success;
    u64 wx_invawid_buffew;
    u64 wx_no_buffew;
    u64 tx_map_faiwed;
    u64 tx_send_faiwed;
    u64 tx_wawge_packets;
    u64 wx_wawge_packets;
    /* Ethtoow settings */
	u8 dupwex;
	u32 speed;
};

/*
 * We pass stwuct ibmveth_buf_desc_fiewds to the hypewvisow in wegistews,
 * so we don't need to byteswap the two ewements. Howevew since we use
 * a union (ibmveth_buf_desc) to convewt fwom the stwuct to a u64 we
 * do end up with endian specific owdewing of the ewements and that
 * needs cowwecting.
 */
stwuct ibmveth_buf_desc_fiewds {
#ifdef __BIG_ENDIAN
	u32 fwags_wen;
	u32 addwess;
#ewse
	u32 addwess;
	u32 fwags_wen;
#endif
#define IBMVETH_BUF_VAWID	0x80000000
#define IBMVETH_BUF_TOGGWE	0x40000000
#define IBMVETH_BUF_WWG_SND     0x04000000
#define IBMVETH_BUF_NO_CSUM	0x02000000
#define IBMVETH_BUF_CSUM_GOOD	0x01000000
#define IBMVETH_BUF_WEN_MASK	0x00FFFFFF
};

union ibmveth_buf_desc {
    u64 desc;
    stwuct ibmveth_buf_desc_fiewds fiewds;
};

stwuct ibmveth_wx_q_entwy {
	__be32 fwags_off;
#define IBMVETH_WXQ_TOGGWE		0x80000000
#define IBMVETH_WXQ_TOGGWE_SHIFT	31
#define IBMVETH_WXQ_VAWID		0x40000000
#define IBMVETH_WXQ_WWG_PKT		0x04000000
#define IBMVETH_WXQ_NO_CSUM		0x02000000
#define IBMVETH_WXQ_CSUM_GOOD		0x01000000
#define IBMVETH_WXQ_OFF_MASK		0x0000FFFF

	__be32 wength;
	/* cowwewatow is onwy used by the OS, no need to byte swap */
	u64 cowwewatow;
};

#endif /* _IBMVETH_H */
