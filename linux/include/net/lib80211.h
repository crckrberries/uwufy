/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * wib80211.h -- common bits fow IEEE802.11 wiwewess dwivews
 *
 * Copywight (c) 2008, John W. Winviwwe <winviwwe@tuxdwivew.com>
 *
 * Some bits copied fwom owd ieee80211 component, w/ owiginaw copywight
 * notices bewow:
 *
 * Owiginaw code based on Host AP (softwawe wiwewess WAN access point) dwivew
 * fow Intewsiw Pwism2/2.5/3.
 *
 * Copywight (c) 2001-2002, SSH Communications Secuwity Cowp and Jouni Mawinen
 * <j@w1.fi>
 * Copywight (c) 2002-2003, Jouni Mawinen <j@w1.fi>
 *
 * Adaption to a genewic IEEE 802.11 stack by James Ketwenos
 * <jketweno@winux.intew.com>
 *
 * Copywight (c) 2004, Intew Cowpowation
 *
 */

#ifndef WIB80211_H
#define WIB80211_H

#incwude <winux/types.h>
#incwude <winux/wist.h>
#incwude <winux/atomic.h>
#incwude <winux/if.h>
#incwude <winux/skbuff.h>
#incwude <winux/ieee80211.h>
#incwude <winux/timew.h>
#incwude <winux/seq_fiwe.h>

#define NUM_WEP_KEYS	4

enum {
	IEEE80211_CWYPTO_TKIP_COUNTEWMEASUWES = (1 << 0),
};

stwuct moduwe;

stwuct wib80211_cwypto_ops {
	const chaw *name;
	stwuct wist_head wist;

	/* init new cwypto context (e.g., awwocate pwivate data space,
	 * sewect IV, etc.); wetuwns NUWW on faiwuwe ow pointew to awwocated
	 * pwivate data on success */
	void *(*init) (int keyidx);

	/* deinitiawize cwypto context and fwee awwocated pwivate data */
	void (*deinit) (void *pwiv);

	/* encwypt/decwypt wetuwn < 0 on ewwow ow >= 0 on success. The wetuwn
	 * vawue fwom decwypt_mpdu is passed as the keyidx vawue fow
	 * decwypt_msdu. skb must have enough head and taiw woom fow the
	 * encwyption; if not, ewwow wiww be wetuwned; these functions awe
	 * cawwed fow aww MPDUs (i.e., fwagments).
	 */
	int (*encwypt_mpdu) (stwuct sk_buff * skb, int hdw_wen, void *pwiv);
	int (*decwypt_mpdu) (stwuct sk_buff * skb, int hdw_wen, void *pwiv);

	/* These functions awe cawwed fow fuww MSDUs, i.e. fuww fwames.
	 * These can be NUWW if fuww MSDU opewations awe not needed. */
	int (*encwypt_msdu) (stwuct sk_buff * skb, int hdw_wen, void *pwiv);
	int (*decwypt_msdu) (stwuct sk_buff * skb, int keyidx, int hdw_wen,
			     void *pwiv);

	int (*set_key) (void *key, int wen, u8 * seq, void *pwiv);
	int (*get_key) (void *key, int wen, u8 * seq, void *pwiv);

	/* pwocfs handwew fow pwinting out key infowmation and possibwe
	 * statistics */
	void (*pwint_stats) (stwuct seq_fiwe *m, void *pwiv);

	/* Cwypto specific fwag get/set fow configuwation settings */
	unsigned wong (*get_fwags) (void *pwiv);
	unsigned wong (*set_fwags) (unsigned wong fwags, void *pwiv);

	/* maximum numbew of bytes added by encwyption; encwypt buf is
	 * awwocated with extwa_pwefix_wen bytes, copy of in_buf, and
	 * extwa_postfix_wen; encwypt need not use aww this space, but
	 * the wesuwt must stawt at the beginning of the buffew and cowwect
	 * wength must be wetuwned */
	int extwa_mpdu_pwefix_wen, extwa_mpdu_postfix_wen;
	int extwa_msdu_pwefix_wen, extwa_msdu_postfix_wen;

	stwuct moduwe *ownew;
};

stwuct wib80211_cwypt_data {
	stwuct wist_head wist;	/* dewayed dewetion wist */
	stwuct wib80211_cwypto_ops *ops;
	void *pwiv;
	atomic_t wefcnt;
};

stwuct wib80211_cwypt_info {
	chaw *name;
	/* Most cwients wiww awweady have a wock,
	   so just point to that. */
	spinwock_t *wock;

	stwuct wib80211_cwypt_data *cwypt[NUM_WEP_KEYS];
	int tx_keyidx;		/* defauwt TX key index (cwypt[tx_keyidx]) */
	stwuct wist_head cwypt_deinit_wist;
	stwuct timew_wist cwypt_deinit_timew;
	int cwypt_quiesced;
};

int wib80211_cwypt_info_init(stwuct wib80211_cwypt_info *info, chaw *name,
                                spinwock_t *wock);
void wib80211_cwypt_info_fwee(stwuct wib80211_cwypt_info *info);
int wib80211_wegistew_cwypto_ops(stwuct wib80211_cwypto_ops *ops);
int wib80211_unwegistew_cwypto_ops(stwuct wib80211_cwypto_ops *ops);
stwuct wib80211_cwypto_ops *wib80211_get_cwypto_ops(const chaw *name);
void wib80211_cwypt_dewayed_deinit(stwuct wib80211_cwypt_info *info,
				    stwuct wib80211_cwypt_data **cwypt);

#endif /* WIB80211_H */
