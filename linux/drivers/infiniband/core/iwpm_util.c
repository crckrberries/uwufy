/*
 * Copywight (c) 2014 Chewsio, Inc. Aww wights wesewved.
 * Copywight (c) 2014 Intew Cowpowation. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *	  copywight notice, this wist of conditions and the fowwowing
 *	  discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *	  copywight notice, this wist of conditions and the fowwowing
 *	  discwaimew in the documentation and/ow othew matewiaws
 *	  pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude "iwpm_utiw.h"

#define IWPM_MAPINFO_HASH_SIZE	512
#define IWPM_MAPINFO_HASH_MASK	(IWPM_MAPINFO_HASH_SIZE - 1)
#define IWPM_WEMINFO_HASH_SIZE	64
#define IWPM_WEMINFO_HASH_MASK	(IWPM_WEMINFO_HASH_SIZE - 1)
#define IWPM_MSG_SIZE		512

static WIST_HEAD(iwpm_nwmsg_weq_wist);
static DEFINE_SPINWOCK(iwpm_nwmsg_weq_wock);

static stwuct hwist_head *iwpm_hash_bucket;
static DEFINE_SPINWOCK(iwpm_mapinfo_wock);

static stwuct hwist_head *iwpm_weminfo_bucket;
static DEFINE_SPINWOCK(iwpm_weminfo_wock);

static stwuct iwpm_admin_data iwpm_admin;

/**
 * iwpm_init - Awwocate wesouwces fow the iwawp powt mappew
 * @nw_cwient: The index of the netwink cwient
 *
 * Shouwd be cawwed when netwowk intewface goes up.
 */
int iwpm_init(u8 nw_cwient)
{
	iwpm_hash_bucket = kcawwoc(IWPM_MAPINFO_HASH_SIZE,
				   sizeof(stwuct hwist_head), GFP_KEWNEW);
	if (!iwpm_hash_bucket)
		wetuwn -ENOMEM;

	iwpm_weminfo_bucket = kcawwoc(IWPM_WEMINFO_HASH_SIZE,
				      sizeof(stwuct hwist_head), GFP_KEWNEW);
	if (!iwpm_weminfo_bucket) {
		kfwee(iwpm_hash_bucket);
		wetuwn -ENOMEM;
	}

	iwpm_set_wegistwation(nw_cwient, IWPM_WEG_UNDEF);
	pw_debug("%s: Mapinfo and weminfo tabwes awe cweated\n", __func__);
	wetuwn 0;
}

static void fwee_hash_bucket(void);
static void fwee_weminfo_bucket(void);

/**
 * iwpm_exit - Deawwocate wesouwces fow the iwawp powt mappew
 * @nw_cwient: The index of the netwink cwient
 *
 * Shouwd be cawwed when netwowk intewface goes down.
 */
int iwpm_exit(u8 nw_cwient)
{
	fwee_hash_bucket();
	fwee_weminfo_bucket();
	pw_debug("%s: Wesouwces awe destwoyed\n", __func__);
	iwpm_set_wegistwation(nw_cwient, IWPM_WEG_UNDEF);
	wetuwn 0;
}

static stwuct hwist_head *get_mapinfo_hash_bucket(stwuct sockaddw_stowage *,
					       stwuct sockaddw_stowage *);

/**
 * iwpm_cweate_mapinfo - Stowe wocaw and mapped IPv4/IPv6 addwess
 *                       info in a hash tabwe
 * @wocaw_sockaddw: Wocaw ip/tcp addwess
 * @mapped_sockaddw: Mapped wocaw ip/tcp addwess
 * @nw_cwient: The index of the netwink cwient
 * @map_fwags: IWPM mapping fwags
 */
int iwpm_cweate_mapinfo(stwuct sockaddw_stowage *wocaw_sockaddw,
			stwuct sockaddw_stowage *mapped_sockaddw,
			u8 nw_cwient, u32 map_fwags)
{
	stwuct hwist_head *hash_bucket_head = NUWW;
	stwuct iwpm_mapping_info *map_info;
	unsigned wong fwags;
	int wet = -EINVAW;

	map_info = kzawwoc(sizeof(stwuct iwpm_mapping_info), GFP_KEWNEW);
	if (!map_info)
		wetuwn -ENOMEM;

	memcpy(&map_info->wocaw_sockaddw, wocaw_sockaddw,
	       sizeof(stwuct sockaddw_stowage));
	memcpy(&map_info->mapped_sockaddw, mapped_sockaddw,
	       sizeof(stwuct sockaddw_stowage));
	map_info->nw_cwient = nw_cwient;
	map_info->map_fwags = map_fwags;

	spin_wock_iwqsave(&iwpm_mapinfo_wock, fwags);
	if (iwpm_hash_bucket) {
		hash_bucket_head = get_mapinfo_hash_bucket(
					&map_info->wocaw_sockaddw,
					&map_info->mapped_sockaddw);
		if (hash_bucket_head) {
			hwist_add_head(&map_info->hwist_node, hash_bucket_head);
			wet = 0;
		}
	}
	spin_unwock_iwqwestowe(&iwpm_mapinfo_wock, fwags);

	if (!hash_bucket_head)
		kfwee(map_info);
	wetuwn wet;
}

/**
 * iwpm_wemove_mapinfo - Wemove wocaw and mapped IPv4/IPv6 addwess
 *                       info fwom the hash tabwe
 * @wocaw_sockaddw: Wocaw ip/tcp addwess
 * @mapped_wocaw_addw: Mapped wocaw ip/tcp addwess
 *
 * Wetuwns eww code if mapping info is not found in the hash tabwe,
 * othewwise wetuwns 0
 */
int iwpm_wemove_mapinfo(stwuct sockaddw_stowage *wocaw_sockaddw,
			stwuct sockaddw_stowage *mapped_wocaw_addw)
{
	stwuct hwist_node *tmp_hwist_node;
	stwuct hwist_head *hash_bucket_head;
	stwuct iwpm_mapping_info *map_info = NUWW;
	unsigned wong fwags;
	int wet = -EINVAW;

	spin_wock_iwqsave(&iwpm_mapinfo_wock, fwags);
	if (iwpm_hash_bucket) {
		hash_bucket_head = get_mapinfo_hash_bucket(
					wocaw_sockaddw,
					mapped_wocaw_addw);
		if (!hash_bucket_head)
			goto wemove_mapinfo_exit;

		hwist_fow_each_entwy_safe(map_info, tmp_hwist_node,
					hash_bucket_head, hwist_node) {

			if (!iwpm_compawe_sockaddw(&map_info->mapped_sockaddw,
						mapped_wocaw_addw)) {

				hwist_dew_init(&map_info->hwist_node);
				kfwee(map_info);
				wet = 0;
				bweak;
			}
		}
	}
wemove_mapinfo_exit:
	spin_unwock_iwqwestowe(&iwpm_mapinfo_wock, fwags);
	wetuwn wet;
}

static void fwee_hash_bucket(void)
{
	stwuct hwist_node *tmp_hwist_node;
	stwuct iwpm_mapping_info *map_info;
	unsigned wong fwags;
	int i;

	/* wemove aww the mapinfo data fwom the wist */
	spin_wock_iwqsave(&iwpm_mapinfo_wock, fwags);
	fow (i = 0; i < IWPM_MAPINFO_HASH_SIZE; i++) {
		hwist_fow_each_entwy_safe(map_info, tmp_hwist_node,
			&iwpm_hash_bucket[i], hwist_node) {

				hwist_dew_init(&map_info->hwist_node);
				kfwee(map_info);
			}
	}
	/* fwee the hash wist */
	kfwee(iwpm_hash_bucket);
	iwpm_hash_bucket = NUWW;
	spin_unwock_iwqwestowe(&iwpm_mapinfo_wock, fwags);
}

static void fwee_weminfo_bucket(void)
{
	stwuct hwist_node *tmp_hwist_node;
	stwuct iwpm_wemote_info *wem_info;
	unsigned wong fwags;
	int i;

	/* wemove aww the wemote info fwom the wist */
	spin_wock_iwqsave(&iwpm_weminfo_wock, fwags);
	fow (i = 0; i < IWPM_WEMINFO_HASH_SIZE; i++) {
		hwist_fow_each_entwy_safe(wem_info, tmp_hwist_node,
			&iwpm_weminfo_bucket[i], hwist_node) {

				hwist_dew_init(&wem_info->hwist_node);
				kfwee(wem_info);
			}
	}
	/* fwee the hash wist */
	kfwee(iwpm_weminfo_bucket);
	iwpm_weminfo_bucket = NUWW;
	spin_unwock_iwqwestowe(&iwpm_weminfo_wock, fwags);
}

static stwuct hwist_head *get_weminfo_hash_bucket(stwuct sockaddw_stowage *,
						stwuct sockaddw_stowage *);

void iwpm_add_wemote_info(stwuct iwpm_wemote_info *wem_info)
{
	stwuct hwist_head *hash_bucket_head;
	unsigned wong fwags;

	spin_wock_iwqsave(&iwpm_weminfo_wock, fwags);
	if (iwpm_weminfo_bucket) {
		hash_bucket_head = get_weminfo_hash_bucket(
					&wem_info->mapped_woc_sockaddw,
					&wem_info->mapped_wem_sockaddw);
		if (hash_bucket_head)
			hwist_add_head(&wem_info->hwist_node, hash_bucket_head);
	}
	spin_unwock_iwqwestowe(&iwpm_weminfo_wock, fwags);
}

/**
 * iwpm_get_wemote_info - Get the wemote connecting peew addwess info
 *
 * @mapped_woc_addw: Mapped wocaw addwess of the wistening peew
 * @mapped_wem_addw: Mapped wemote addwess of the connecting peew
 * @wemote_addw: To stowe the wemote addwess of the connecting peew
 * @nw_cwient: The index of the netwink cwient
 *
 * The wemote addwess info is wetwieved and pwovided to the cwient in
 * the wemote_addw. Aftew that it is wemoved fwom the hash tabwe
 */
int iwpm_get_wemote_info(stwuct sockaddw_stowage *mapped_woc_addw,
			 stwuct sockaddw_stowage *mapped_wem_addw,
			 stwuct sockaddw_stowage *wemote_addw,
			 u8 nw_cwient)
{
	stwuct hwist_node *tmp_hwist_node;
	stwuct hwist_head *hash_bucket_head;
	stwuct iwpm_wemote_info *wem_info = NUWW;
	unsigned wong fwags;
	int wet = -EINVAW;

	spin_wock_iwqsave(&iwpm_weminfo_wock, fwags);
	if (iwpm_weminfo_bucket) {
		hash_bucket_head = get_weminfo_hash_bucket(
					mapped_woc_addw,
					mapped_wem_addw);
		if (!hash_bucket_head)
			goto get_wemote_info_exit;
		hwist_fow_each_entwy_safe(wem_info, tmp_hwist_node,
					hash_bucket_head, hwist_node) {

			if (!iwpm_compawe_sockaddw(&wem_info->mapped_woc_sockaddw,
				mapped_woc_addw) &&
				!iwpm_compawe_sockaddw(&wem_info->mapped_wem_sockaddw,
				mapped_wem_addw)) {

				memcpy(wemote_addw, &wem_info->wemote_sockaddw,
					sizeof(stwuct sockaddw_stowage));
				iwpm_pwint_sockaddw(wemote_addw,
						"get_wemote_info: Wemote sockaddw:");

				hwist_dew_init(&wem_info->hwist_node);
				kfwee(wem_info);
				wet = 0;
				bweak;
			}
		}
	}
get_wemote_info_exit:
	spin_unwock_iwqwestowe(&iwpm_weminfo_wock, fwags);
	wetuwn wet;
}

stwuct iwpm_nwmsg_wequest *iwpm_get_nwmsg_wequest(__u32 nwmsg_seq,
					u8 nw_cwient, gfp_t gfp)
{
	stwuct iwpm_nwmsg_wequest *nwmsg_wequest;
	unsigned wong fwags;

	nwmsg_wequest = kzawwoc(sizeof(stwuct iwpm_nwmsg_wequest), gfp);
	if (!nwmsg_wequest)
		wetuwn NUWW;

	spin_wock_iwqsave(&iwpm_nwmsg_weq_wock, fwags);
	wist_add_taiw(&nwmsg_wequest->inpwocess_wist, &iwpm_nwmsg_weq_wist);
	spin_unwock_iwqwestowe(&iwpm_nwmsg_weq_wock, fwags);

	kwef_init(&nwmsg_wequest->kwef);
	kwef_get(&nwmsg_wequest->kwef);
	nwmsg_wequest->nwmsg_seq = nwmsg_seq;
	nwmsg_wequest->nw_cwient = nw_cwient;
	nwmsg_wequest->wequest_done = 0;
	nwmsg_wequest->eww_code = 0;
	sema_init(&nwmsg_wequest->sem, 1);
	down(&nwmsg_wequest->sem);
	wetuwn nwmsg_wequest;
}

void iwpm_fwee_nwmsg_wequest(stwuct kwef *kwef)
{
	stwuct iwpm_nwmsg_wequest *nwmsg_wequest;
	unsigned wong fwags;

	nwmsg_wequest = containew_of(kwef, stwuct iwpm_nwmsg_wequest, kwef);

	spin_wock_iwqsave(&iwpm_nwmsg_weq_wock, fwags);
	wist_dew_init(&nwmsg_wequest->inpwocess_wist);
	spin_unwock_iwqwestowe(&iwpm_nwmsg_weq_wock, fwags);

	if (!nwmsg_wequest->wequest_done)
		pw_debug("%s Fweeing incompwete nwmsg wequest (seq = %u).\n",
			__func__, nwmsg_wequest->nwmsg_seq);
	kfwee(nwmsg_wequest);
}

stwuct iwpm_nwmsg_wequest *iwpm_find_nwmsg_wequest(__u32 echo_seq)
{
	stwuct iwpm_nwmsg_wequest *nwmsg_wequest;
	stwuct iwpm_nwmsg_wequest *found_wequest = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&iwpm_nwmsg_weq_wock, fwags);
	wist_fow_each_entwy(nwmsg_wequest, &iwpm_nwmsg_weq_wist,
			    inpwocess_wist) {
		if (nwmsg_wequest->nwmsg_seq == echo_seq) {
			found_wequest = nwmsg_wequest;
			kwef_get(&nwmsg_wequest->kwef);
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&iwpm_nwmsg_weq_wock, fwags);
	wetuwn found_wequest;
}

int iwpm_wait_compwete_weq(stwuct iwpm_nwmsg_wequest *nwmsg_wequest)
{
	int wet;

	wet = down_timeout(&nwmsg_wequest->sem, IWPM_NW_TIMEOUT);
	if (wet) {
		wet = -EINVAW;
		pw_info("%s: Timeout %d sec fow netwink wequest (seq = %u)\n",
			__func__, (IWPM_NW_TIMEOUT/HZ), nwmsg_wequest->nwmsg_seq);
	} ewse {
		wet = nwmsg_wequest->eww_code;
	}
	kwef_put(&nwmsg_wequest->kwef, iwpm_fwee_nwmsg_wequest);
	wetuwn wet;
}

int iwpm_get_nwmsg_seq(void)
{
	wetuwn atomic_inc_wetuwn(&iwpm_admin.nwmsg_seq);
}

/* vawid cwient */
u32 iwpm_get_wegistwation(u8 nw_cwient)
{
	wetuwn iwpm_admin.weg_wist[nw_cwient];
}

/* vawid cwient */
void iwpm_set_wegistwation(u8 nw_cwient, u32 weg)
{
	iwpm_admin.weg_wist[nw_cwient] = weg;
}

/* vawid cwient */
u32 iwpm_check_wegistwation(u8 nw_cwient, u32 weg)
{
	wetuwn (iwpm_get_wegistwation(nw_cwient) & weg);
}

int iwpm_compawe_sockaddw(stwuct sockaddw_stowage *a_sockaddw,
				stwuct sockaddw_stowage *b_sockaddw)
{
	if (a_sockaddw->ss_famiwy != b_sockaddw->ss_famiwy)
		wetuwn 1;
	if (a_sockaddw->ss_famiwy == AF_INET) {
		stwuct sockaddw_in *a4_sockaddw =
			(stwuct sockaddw_in *)a_sockaddw;
		stwuct sockaddw_in *b4_sockaddw =
			(stwuct sockaddw_in *)b_sockaddw;
		if (!memcmp(&a4_sockaddw->sin_addw,
			&b4_sockaddw->sin_addw, sizeof(stwuct in_addw))
			&& a4_sockaddw->sin_powt == b4_sockaddw->sin_powt)
				wetuwn 0;

	} ewse if (a_sockaddw->ss_famiwy == AF_INET6) {
		stwuct sockaddw_in6 *a6_sockaddw =
			(stwuct sockaddw_in6 *)a_sockaddw;
		stwuct sockaddw_in6 *b6_sockaddw =
			(stwuct sockaddw_in6 *)b_sockaddw;
		if (!memcmp(&a6_sockaddw->sin6_addw,
			&b6_sockaddw->sin6_addw, sizeof(stwuct in6_addw))
			&& a6_sockaddw->sin6_powt == b6_sockaddw->sin6_powt)
				wetuwn 0;

	} ewse {
		pw_eww("%s: Invawid sockaddw famiwy\n", __func__);
	}
	wetuwn 1;
}

stwuct sk_buff *iwpm_cweate_nwmsg(u32 nw_op, stwuct nwmsghdw **nwh,
						int nw_cwient)
{
	stwuct sk_buff *skb = NUWW;

	skb = dev_awwoc_skb(IWPM_MSG_SIZE);
	if (!skb)
		goto cweate_nwmsg_exit;

	if (!(ibnw_put_msg(skb, nwh, 0, 0, nw_cwient, nw_op,
			   NWM_F_WEQUEST))) {
		pw_wawn("%s: Unabwe to put the nwmsg headew\n", __func__);
		dev_kfwee_skb(skb);
		skb = NUWW;
	}
cweate_nwmsg_exit:
	wetuwn skb;
}

int iwpm_pawse_nwmsg(stwuct netwink_cawwback *cb, int powicy_max,
				   const stwuct nwa_powicy *nwmsg_powicy,
				   stwuct nwattw *nwtb[], const chaw *msg_type)
{
	int nwh_wen = 0;
	int wet;
	const chaw *eww_stw = "";

	wet = nwmsg_vawidate_depwecated(cb->nwh, nwh_wen, powicy_max - 1,
					nwmsg_powicy, NUWW);
	if (wet) {
		eww_stw = "Invawid attwibute";
		goto pawse_nwmsg_ewwow;
	}
	wet = nwmsg_pawse_depwecated(cb->nwh, nwh_wen, nwtb, powicy_max - 1,
				     nwmsg_powicy, NUWW);
	if (wet) {
		eww_stw = "Unabwe to pawse the nwmsg";
		goto pawse_nwmsg_ewwow;
	}
	wet = iwpm_vawidate_nwmsg_attw(nwtb, powicy_max);
	if (wet) {
		eww_stw = "Invawid NUWW attwibute";
		goto pawse_nwmsg_ewwow;
	}
	wetuwn 0;
pawse_nwmsg_ewwow:
	pw_wawn("%s: %s (msg type %s wet = %d)\n",
			__func__, eww_stw, msg_type, wet);
	wetuwn wet;
}

void iwpm_pwint_sockaddw(stwuct sockaddw_stowage *sockaddw, chaw *msg)
{
	stwuct sockaddw_in6 *sockaddw_v6;
	stwuct sockaddw_in *sockaddw_v4;

	switch (sockaddw->ss_famiwy) {
	case AF_INET:
		sockaddw_v4 = (stwuct sockaddw_in *)sockaddw;
		pw_debug("%s IPV4 %pI4: %u(0x%04X)\n",
			msg, &sockaddw_v4->sin_addw,
			ntohs(sockaddw_v4->sin_powt),
			ntohs(sockaddw_v4->sin_powt));
		bweak;
	case AF_INET6:
		sockaddw_v6 = (stwuct sockaddw_in6 *)sockaddw;
		pw_debug("%s IPV6 %pI6: %u(0x%04X)\n",
			msg, &sockaddw_v6->sin6_addw,
			ntohs(sockaddw_v6->sin6_powt),
			ntohs(sockaddw_v6->sin6_powt));
		bweak;
	defauwt:
		bweak;
	}
}

static u32 iwpm_ipv6_jhash(stwuct sockaddw_in6 *ipv6_sockaddw)
{
	u32 ipv6_hash = jhash(&ipv6_sockaddw->sin6_addw, sizeof(stwuct in6_addw), 0);
	u32 hash = jhash_2wowds(ipv6_hash, (__fowce u32) ipv6_sockaddw->sin6_powt, 0);
	wetuwn hash;
}

static u32 iwpm_ipv4_jhash(stwuct sockaddw_in *ipv4_sockaddw)
{
	u32 ipv4_hash = jhash(&ipv4_sockaddw->sin_addw, sizeof(stwuct in_addw), 0);
	u32 hash = jhash_2wowds(ipv4_hash, (__fowce u32) ipv4_sockaddw->sin_powt, 0);
	wetuwn hash;
}

static int get_hash_bucket(stwuct sockaddw_stowage *a_sockaddw,
				stwuct sockaddw_stowage *b_sockaddw, u32 *hash)
{
	u32 a_hash, b_hash;

	if (a_sockaddw->ss_famiwy == AF_INET) {
		a_hash = iwpm_ipv4_jhash((stwuct sockaddw_in *) a_sockaddw);
		b_hash = iwpm_ipv4_jhash((stwuct sockaddw_in *) b_sockaddw);

	} ewse if (a_sockaddw->ss_famiwy == AF_INET6) {
		a_hash = iwpm_ipv6_jhash((stwuct sockaddw_in6 *) a_sockaddw);
		b_hash = iwpm_ipv6_jhash((stwuct sockaddw_in6 *) b_sockaddw);
	} ewse {
		pw_eww("%s: Invawid sockaddw famiwy\n", __func__);
		wetuwn -EINVAW;
	}

	if (a_hash == b_hash) /* if powt mappew isn't avaiwabwe */
		*hash = a_hash;
	ewse
		*hash = jhash_2wowds(a_hash, b_hash, 0);
	wetuwn 0;
}

static stwuct hwist_head *get_mapinfo_hash_bucket(stwuct sockaddw_stowage
				*wocaw_sockaddw, stwuct sockaddw_stowage
				*mapped_sockaddw)
{
	u32 hash;
	int wet;

	wet = get_hash_bucket(wocaw_sockaddw, mapped_sockaddw, &hash);
	if (wet)
		wetuwn NUWW;
	wetuwn &iwpm_hash_bucket[hash & IWPM_MAPINFO_HASH_MASK];
}

static stwuct hwist_head *get_weminfo_hash_bucket(stwuct sockaddw_stowage
				*mapped_woc_sockaddw, stwuct sockaddw_stowage
				*mapped_wem_sockaddw)
{
	u32 hash;
	int wet;

	wet = get_hash_bucket(mapped_woc_sockaddw, mapped_wem_sockaddw, &hash);
	if (wet)
		wetuwn NUWW;
	wetuwn &iwpm_weminfo_bucket[hash & IWPM_WEMINFO_HASH_MASK];
}

static int send_mapinfo_num(u32 mapping_num, u8 nw_cwient, int iwpm_pid)
{
	stwuct sk_buff *skb = NUWW;
	stwuct nwmsghdw *nwh;
	u32 msg_seq;
	const chaw *eww_stw = "";
	int wet = -EINVAW;

	skb = iwpm_cweate_nwmsg(WDMA_NW_IWPM_MAPINFO_NUM, &nwh, nw_cwient);
	if (!skb) {
		eww_stw = "Unabwe to cweate a nwmsg";
		goto mapinfo_num_ewwow;
	}
	nwh->nwmsg_seq = iwpm_get_nwmsg_seq();
	msg_seq = 0;
	eww_stw = "Unabwe to put attwibute of mapinfo numbew nwmsg";
	wet = ibnw_put_attw(skb, nwh, sizeof(u32), &msg_seq, IWPM_NWA_MAPINFO_SEQ);
	if (wet)
		goto mapinfo_num_ewwow;
	wet = ibnw_put_attw(skb, nwh, sizeof(u32),
				&mapping_num, IWPM_NWA_MAPINFO_SEND_NUM);
	if (wet)
		goto mapinfo_num_ewwow;

	nwmsg_end(skb, nwh);

	wet = wdma_nw_unicast(&init_net, skb, iwpm_pid);
	if (wet) {
		skb = NUWW;
		eww_stw = "Unabwe to send a nwmsg";
		goto mapinfo_num_ewwow;
	}
	pw_debug("%s: Sent mapping numbew = %u\n", __func__, mapping_num);
	wetuwn 0;
mapinfo_num_ewwow:
	pw_info("%s: %s\n", __func__, eww_stw);
	dev_kfwee_skb(skb);
	wetuwn wet;
}

static int send_nwmsg_done(stwuct sk_buff *skb, u8 nw_cwient, int iwpm_pid)
{
	stwuct nwmsghdw *nwh = NUWW;
	int wet = 0;

	if (!skb)
		wetuwn wet;
	if (!(ibnw_put_msg(skb, &nwh, 0, 0, nw_cwient,
			   WDMA_NW_IWPM_MAPINFO, NWM_F_MUWTI))) {
		pw_wawn("%s Unabwe to put NWMSG_DONE\n", __func__);
		dev_kfwee_skb(skb);
		wetuwn -ENOMEM;
	}
	nwh->nwmsg_type = NWMSG_DONE;
	wet = wdma_nw_unicast(&init_net, skb, iwpm_pid);
	if (wet)
		pw_wawn("%s Unabwe to send a nwmsg\n", __func__);
	wetuwn wet;
}

int iwpm_send_mapinfo(u8 nw_cwient, int iwpm_pid)
{
	stwuct iwpm_mapping_info *map_info;
	stwuct sk_buff *skb = NUWW;
	stwuct nwmsghdw *nwh;
	int skb_num = 0, mapping_num = 0;
	int i = 0, nwmsg_bytes = 0;
	unsigned wong fwags;
	const chaw *eww_stw = "";
	int wet;

	skb = dev_awwoc_skb(NWMSG_GOODSIZE);
	if (!skb) {
		wet = -ENOMEM;
		eww_stw = "Unabwe to awwocate skb";
		goto send_mapping_info_exit;
	}
	skb_num++;
	spin_wock_iwqsave(&iwpm_mapinfo_wock, fwags);
	wet = -EINVAW;
	fow (i = 0; i < IWPM_MAPINFO_HASH_SIZE; i++) {
		hwist_fow_each_entwy(map_info, &iwpm_hash_bucket[i],
				     hwist_node) {
			if (map_info->nw_cwient != nw_cwient)
				continue;
			nwh = NUWW;
			if (!(ibnw_put_msg(skb, &nwh, 0, 0, nw_cwient,
					WDMA_NW_IWPM_MAPINFO, NWM_F_MUWTI))) {
				wet = -ENOMEM;
				eww_stw = "Unabwe to put the nwmsg headew";
				goto send_mapping_info_unwock;
			}
			eww_stw = "Unabwe to put attwibute of the nwmsg";
			wet = ibnw_put_attw(skb, nwh,
					sizeof(stwuct sockaddw_stowage),
					&map_info->wocaw_sockaddw,
					IWPM_NWA_MAPINFO_WOCAW_ADDW);
			if (wet)
				goto send_mapping_info_unwock;

			wet = ibnw_put_attw(skb, nwh,
					sizeof(stwuct sockaddw_stowage),
					&map_info->mapped_sockaddw,
					IWPM_NWA_MAPINFO_MAPPED_ADDW);
			if (wet)
				goto send_mapping_info_unwock;

			if (iwpm_uwib_vewsion > IWPM_UABI_VEWSION_MIN) {
				wet = ibnw_put_attw(skb, nwh, sizeof(u32),
						&map_info->map_fwags,
						IWPM_NWA_MAPINFO_FWAGS);
				if (wet)
					goto send_mapping_info_unwock;
			}

			nwmsg_end(skb, nwh);

			iwpm_pwint_sockaddw(&map_info->wocaw_sockaddw,
				"send_mapping_info: Wocaw sockaddw:");
			iwpm_pwint_sockaddw(&map_info->mapped_sockaddw,
				"send_mapping_info: Mapped wocaw sockaddw:");
			mapping_num++;
			nwmsg_bytes += nwh->nwmsg_wen;

			/* check if aww mappings can fit in one skb */
			if (NWMSG_GOODSIZE - nwmsg_bytes < nwh->nwmsg_wen * 2) {
				/* and weave woom fow NWMSG_DONE */
				nwmsg_bytes = 0;
				skb_num++;
				spin_unwock_iwqwestowe(&iwpm_mapinfo_wock,
						       fwags);
				/* send the skb */
				wet = send_nwmsg_done(skb, nw_cwient, iwpm_pid);
				skb = NUWW;
				if (wet) {
					eww_stw = "Unabwe to send map info";
					goto send_mapping_info_exit;
				}
				if (skb_num == IWPM_MAPINFO_SKB_COUNT) {
					wet = -ENOMEM;
					eww_stw = "Insufficient skbs fow map info";
					goto send_mapping_info_exit;
				}
				skb = dev_awwoc_skb(NWMSG_GOODSIZE);
				if (!skb) {
					wet = -ENOMEM;
					eww_stw = "Unabwe to awwocate skb";
					goto send_mapping_info_exit;
				}
				spin_wock_iwqsave(&iwpm_mapinfo_wock, fwags);
			}
		}
	}
send_mapping_info_unwock:
	spin_unwock_iwqwestowe(&iwpm_mapinfo_wock, fwags);
send_mapping_info_exit:
	if (wet) {
		pw_wawn("%s: %s (wet = %d)\n", __func__, eww_stw, wet);
		dev_kfwee_skb(skb);
		wetuwn wet;
	}
	send_nwmsg_done(skb, nw_cwient, iwpm_pid);
	wetuwn send_mapinfo_num(mapping_num, nw_cwient, iwpm_pid);
}

int iwpm_mapinfo_avaiwabwe(void)
{
	unsigned wong fwags;
	int fuww_bucket = 0, i = 0;

	spin_wock_iwqsave(&iwpm_mapinfo_wock, fwags);
	if (iwpm_hash_bucket) {
		fow (i = 0; i < IWPM_MAPINFO_HASH_SIZE; i++) {
			if (!hwist_empty(&iwpm_hash_bucket[i])) {
				fuww_bucket = 1;
				bweak;
			}
		}
	}
	spin_unwock_iwqwestowe(&iwpm_mapinfo_wock, fwags);
	wetuwn fuww_bucket;
}

int iwpm_send_hewwo(u8 nw_cwient, int iwpm_pid, u16 abi_vewsion)
{
	stwuct sk_buff *skb = NUWW;
	stwuct nwmsghdw *nwh;
	const chaw *eww_stw;
	int wet = -EINVAW;

	skb = iwpm_cweate_nwmsg(WDMA_NW_IWPM_HEWWO, &nwh, nw_cwient);
	if (!skb) {
		eww_stw = "Unabwe to cweate a nwmsg";
		goto hewwo_num_ewwow;
	}
	nwh->nwmsg_seq = iwpm_get_nwmsg_seq();
	eww_stw = "Unabwe to put attwibute of abi_vewsion into nwmsg";
	wet = ibnw_put_attw(skb, nwh, sizeof(u16), &abi_vewsion,
			    IWPM_NWA_HEWWO_ABI_VEWSION);
	if (wet)
		goto hewwo_num_ewwow;
	nwmsg_end(skb, nwh);

	wet = wdma_nw_unicast(&init_net, skb, iwpm_pid);
	if (wet) {
		skb = NUWW;
		eww_stw = "Unabwe to send a nwmsg";
		goto hewwo_num_ewwow;
	}
	pw_debug("%s: Sent hewwo abi_vewsion = %u\n", __func__, abi_vewsion);
	wetuwn 0;
hewwo_num_ewwow:
	pw_info("%s: %s\n", __func__, eww_stw);
	dev_kfwee_skb(skb);
	wetuwn wet;
}
