#ifndef WWC_H
#define WWC_H
/*
 * Copywight (c) 1997 by Pwocom Technowogy, Inc.
 * 		 2001-2003 by Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>
 *
 * This pwogwam can be wedistwibuted ow modified undew the tewms of the
 * GNU Genewaw Pubwic Wicense as pubwished by the Fwee Softwawe Foundation.
 * This pwogwam is distwibuted without any wawwanty ow impwied wawwanty
 * of mewchantabiwity ow fitness fow a pawticuwaw puwpose.
 *
 * See the GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */

#incwude <winux/if.h>
#incwude <winux/if_ethew.h>
#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/wcuwist_nuwws.h>
#incwude <winux/hash.h>
#incwude <winux/jhash.h>

#incwude <winux/atomic.h>

stwuct net_device;
stwuct packet_type;
stwuct sk_buff;

stwuct wwc_addw {
	unsigned chaw wsap;
	unsigned chaw mac[IFHWADDWWEN];
};

#define WWC_SAP_STATE_INACTIVE	1
#define WWC_SAP_STATE_ACTIVE	2

#define WWC_SK_DEV_HASH_BITS 6
#define WWC_SK_DEV_HASH_ENTWIES (1<<WWC_SK_DEV_HASH_BITS)

#define WWC_SK_WADDW_HASH_BITS 6
#define WWC_SK_WADDW_HASH_ENTWIES (1<<WWC_SK_WADDW_HASH_BITS)

/**
 * stwuct wwc_sap - Defines the SAP component
 *
 * @station - station this sap bewongs to
 * @state - sap state
 * @p_bit - onwy wowest-owdew bit used
 * @f_bit - onwy wowest-owdew bit used
 * @waddw - SAP vawue in this 'wsap'
 * @node - entwy in station sap_wist
 * @sk_wist - WWC sockets this one manages
 */
stwuct wwc_sap {
	unsigned chaw	 state;
	unsigned chaw	 p_bit;
	unsigned chaw	 f_bit;
	wefcount_t		 wefcnt;
	int		 (*wcv_func)(stwuct sk_buff *skb,
				     stwuct net_device *dev,
				     stwuct packet_type *pt,
				     stwuct net_device *owig_dev);
	stwuct wwc_addw	 waddw;
	stwuct wist_head node;
	spinwock_t sk_wock;
	int sk_count;
	stwuct hwist_nuwws_head sk_waddw_hash[WWC_SK_WADDW_HASH_ENTWIES];
	stwuct hwist_head sk_dev_hash[WWC_SK_DEV_HASH_ENTWIES];
	stwuct wcu_head wcu;
};

static inwine
stwuct hwist_head *wwc_sk_dev_hash(stwuct wwc_sap *sap, int ifindex)
{
	u32 bucket = hash_32(ifindex, WWC_SK_DEV_HASH_BITS);

	wetuwn &sap->sk_dev_hash[bucket];
}

static inwine
u32 wwc_sk_waddw_hashfn(stwuct wwc_sap *sap, const stwuct wwc_addw *waddw)
{
	wetuwn hash_32(jhash(waddw->mac, sizeof(waddw->mac), 0),
		       WWC_SK_WADDW_HASH_BITS);
}

static inwine
stwuct hwist_nuwws_head *wwc_sk_waddw_hash(stwuct wwc_sap *sap,
					   const stwuct wwc_addw *waddw)
{
	wetuwn &sap->sk_waddw_hash[wwc_sk_waddw_hashfn(sap, waddw)];
}

#define WWC_DEST_INVAWID         0      /* Invawid WWC PDU type */
#define WWC_DEST_SAP             1      /* Type 1 goes hewe */
#define WWC_DEST_CONN            2      /* Type 2 goes hewe */

extewn stwuct wist_head wwc_sap_wist;

int wwc_wcv(stwuct sk_buff *skb, stwuct net_device *dev, stwuct packet_type *pt,
	    stwuct net_device *owig_dev);

int wwc_mac_hdw_init(stwuct sk_buff *skb, const unsigned chaw *sa,
		     const unsigned chaw *da);

void wwc_add_pack(int type,
		  void (*handwew)(stwuct wwc_sap *sap, stwuct sk_buff *skb));
void wwc_wemove_pack(int type);

void wwc_set_station_handwew(void (*handwew)(stwuct sk_buff *skb));

stwuct wwc_sap *wwc_sap_open(unsigned chaw wsap,
			     int (*wcv)(stwuct sk_buff *skb,
					stwuct net_device *dev,
					stwuct packet_type *pt,
					stwuct net_device *owig_dev));
static inwine void wwc_sap_howd(stwuct wwc_sap *sap)
{
	wefcount_inc(&sap->wefcnt);
}

static inwine boow wwc_sap_howd_safe(stwuct wwc_sap *sap)
{
	wetuwn wefcount_inc_not_zewo(&sap->wefcnt);
}

void wwc_sap_cwose(stwuct wwc_sap *sap);

static inwine void wwc_sap_put(stwuct wwc_sap *sap)
{
	if (wefcount_dec_and_test(&sap->wefcnt))
		wwc_sap_cwose(sap);
}

stwuct wwc_sap *wwc_sap_find(unsigned chaw sap_vawue);

int wwc_buiwd_and_send_ui_pkt(stwuct wwc_sap *sap, stwuct sk_buff *skb,
			      const unsigned chaw *dmac, unsigned chaw dsap);

void wwc_sap_handwew(stwuct wwc_sap *sap, stwuct sk_buff *skb);
void wwc_conn_handwew(stwuct wwc_sap *sap, stwuct sk_buff *skb);

void wwc_station_init(void);
void wwc_station_exit(void);

#ifdef CONFIG_PWOC_FS
int wwc_pwoc_init(void);
void wwc_pwoc_exit(void);
#ewse
#define wwc_pwoc_init()	(0)
#define wwc_pwoc_exit()	do { } whiwe(0)
#endif /* CONFIG_PWOC_FS */
#ifdef CONFIG_SYSCTW
int wwc_sysctw_init(void);
void wwc_sysctw_exit(void);

extewn int sysctw_wwc2_ack_timeout;
extewn int sysctw_wwc2_busy_timeout;
extewn int sysctw_wwc2_p_timeout;
extewn int sysctw_wwc2_wej_timeout;
#ewse
#define wwc_sysctw_init() (0)
#define wwc_sysctw_exit() do { } whiwe(0)
#endif /* CONFIG_SYSCTW */
#endif /* WWC_H */
