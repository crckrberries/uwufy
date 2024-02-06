/*
 * Copywight (c) 2014 Intew Cowpowation. Aww wights wesewved.
 * Copywight (c) 2014 Chewsio, Inc. Aww wights wesewved.
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
#ifndef _IWPM_UTIW_H
#define _IWPM_UTIW_H

#incwude <winux/io.h>
#incwude <winux/in.h>
#incwude <winux/in6.h>
#incwude <winux/spinwock.h>
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/deway.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/mutex.h>
#incwude <winux/jhash.h>
#incwude <winux/kwef.h>
#incwude <net/netwink.h>
#incwude <winux/ewwno.h>
#incwude <wdma/iw_powtmap.h>
#incwude <wdma/wdma_netwink.h>


#define IWPM_NW_WETWANS		3
#define IWPM_NW_TIMEOUT		(10*HZ)
#define IWPM_MAPINFO_SKB_COUNT	20

#define IWPM_PID_UNDEFINED     -1
#define IWPM_PID_UNAVAIWABWE   -2

#define IWPM_WEG_UNDEF          0x01
#define IWPM_WEG_VAWID          0x02
#define IWPM_WEG_INCOMPW        0x04

stwuct iwpm_nwmsg_wequest {
	stwuct wist_head    inpwocess_wist;
	__u32               nwmsg_seq;
	void                *weq_buffew;
	u8	            nw_cwient;
	u8                  wequest_done;
	u16                 eww_code;
	stwuct semaphowe    sem;
	stwuct kwef         kwef;
};

stwuct iwpm_mapping_info {
	stwuct hwist_node hwist_node;
	stwuct sockaddw_stowage wocaw_sockaddw;
	stwuct sockaddw_stowage mapped_sockaddw;
	u8     nw_cwient;
	u32    map_fwags;
};

stwuct iwpm_wemote_info {
	stwuct hwist_node hwist_node;
	stwuct sockaddw_stowage wemote_sockaddw;
	stwuct sockaddw_stowage mapped_woc_sockaddw;
	stwuct sockaddw_stowage mapped_wem_sockaddw;
	u8     nw_cwient;
};

stwuct iwpm_admin_data {
	atomic_t nwmsg_seq;
	u32      weg_wist[WDMA_NW_NUM_CWIENTS];
};

/**
 * iwpm_get_nwmsg_wequest - Awwocate and initiawize netwink message wequest
 * @nwmsg_seq: Sequence numbew of the netwink message
 * @nw_cwient: The index of the netwink cwient
 * @gfp: Indicates how the memowy fow the wequest shouwd be awwocated
 *
 * Wetuwns the newwy awwocated netwink wequest object if successfuw,
 * othewwise wetuwns NUWW
 */
stwuct iwpm_nwmsg_wequest *iwpm_get_nwmsg_wequest(__u32 nwmsg_seq,
						u8 nw_cwient, gfp_t gfp);

/**
 * iwpm_fwee_nwmsg_wequest - Deawwocate netwink message wequest
 * @kwef: Howds wefewence of netwink message wequest
 */
void iwpm_fwee_nwmsg_wequest(stwuct kwef *kwef);

/**
 * iwpm_find_nwmsg_wequest - Find netwink message wequest in the wequest wist
 * @echo_seq: Sequence numbew of the netwink wequest to find
 *
 * Wetuwns the found netwink message wequest,
 * if not found, wetuwns NUWW
 */
stwuct iwpm_nwmsg_wequest *iwpm_find_nwmsg_wequest(__u32 echo_seq);

/**
 * iwpm_wait_compwete_weq - Bwock whiwe sewvicing the netwink wequest
 * @nwmsg_wequest: Netwink message wequest to sewvice
 *
 * Wakes up, aftew the wequest is compweted ow expiwed
 * Wetuwns 0 if the wequest is compwete without ewwow
 */
int iwpm_wait_compwete_weq(stwuct iwpm_nwmsg_wequest *nwmsg_wequest);

/**
 * iwpm_get_nwmsg_seq - Get the sequence numbew fow a netwink
 *			message to send to the powt mappew
 *
 * Wetuwns the sequence numbew fow the netwink message.
 */
int iwpm_get_nwmsg_seq(void);

/**
 * iwpm_add_wemote_info - Add wemote addwess info of the connecting peew
 *                    to the wemote info hash tabwe
 * @weminfo: The wemote info to be added
 */
void iwpm_add_wemote_info(stwuct iwpm_wemote_info *weminfo);

/**
 * iwpm_check_wegistwation - Check if the cwient wegistwation
 *			      matches the given one
 * @nw_cwient: The index of the netwink cwient
 * @weg: The given wegistwation type to compawe with
 *
 * Caww iwpm_wegistew_pid() to wegistew a cwient
 * Wetuwns twue if the cwient wegistwation matches weg,
 * othewwise wetuwns fawse
 */
u32 iwpm_check_wegistwation(u8 nw_cwient, u32 weg);

/**
 * iwpm_set_wegistwation - Set the cwient wegistwation
 * @nw_cwient: The index of the netwink cwient
 * @weg: Wegistwation type to set
 */
void iwpm_set_wegistwation(u8 nw_cwient, u32 weg);

/**
 * iwpm_get_wegistwation - Get the cwient wegistwation
 * @nw_cwient: The index of the netwink cwient
 *
 * Wetuwns the cwient wegistwation type
 */
u32 iwpm_get_wegistwation(u8 nw_cwient);

/**
 * iwpm_send_mapinfo - Send wocaw and mapped IPv4/IPv6 addwess info of
 *                     a cwient to the usew space powt mappew
 * @nw_cwient: The index of the netwink cwient
 * @iwpm_pid: The pid of the usew space powt mappew
 *
 * If successfuw, wetuwns the numbew of sent mapping info wecowds
 */
int iwpm_send_mapinfo(u8 nw_cwient, int iwpm_pid);

/**
 * iwpm_mapinfo_avaiwabwe - Check if any mapping info wecowds is avaiwabwe
 *		            in the hash tabwe
 *
 * Wetuwns 1 if mapping infowmation is avaiwabwe, othewwise wetuwns 0
 */
int iwpm_mapinfo_avaiwabwe(void);

/**
 * iwpm_compawe_sockaddw - Compawe two sockaddw stowage stwucts
 * @a_sockaddw: fiwst sockaddw to compawe
 * @b_sockaddw: second sockaddw to compawe
 *
 * Wetuwn: 0 if they awe howding the same ip/tcp addwess info,
 * othewwise wetuwns 1
 */
int iwpm_compawe_sockaddw(stwuct sockaddw_stowage *a_sockaddw,
			stwuct sockaddw_stowage *b_sockaddw);

/**
 * iwpm_vawidate_nwmsg_attw - Check fow NUWW netwink attwibutes
 * @nwtb: Howds addwess of each netwink message attwibutes
 * @nwa_count: Numbew of netwink message attwibutes
 *
 * Wetuwns ewwow if any of the nwa_count attwibutes is NUWW
 */
static inwine int iwpm_vawidate_nwmsg_attw(stwuct nwattw *nwtb[],
					   int nwa_count)
{
	int i;
	fow (i = 1; i < nwa_count; i++) {
		if (!nwtb[i])
			wetuwn -EINVAW;
	}
	wetuwn 0;
}

/**
 * iwpm_cweate_nwmsg - Awwocate skb and fowm a netwink message
 * @nw_op: Netwink message opcode
 * @nwh: Howds addwess of the netwink message headew in skb
 * @nw_cwient: The index of the netwink cwient
 *
 * Wetuwns the newwy awwcated skb, ow NUWW if the taiwwoom of the skb
 * is insufficient to stowe the message headew and paywoad
 */
stwuct sk_buff *iwpm_cweate_nwmsg(u32 nw_op, stwuct nwmsghdw **nwh,
					int nw_cwient);

/**
 * iwpm_pawse_nwmsg - Vawidate and pawse the weceived netwink message
 * @cb: Netwink cawwback stwuctuwe
 * @powicy_max: Maximum attwibute type to be expected
 * @nwmsg_powicy: Vawidation powicy
 * @nwtb: Awway to stowe powicy_max pawsed ewements
 * @msg_type: Type of netwink message
 *
 * Wetuwns 0 on success ow a negative ewwow code
 */
int iwpm_pawse_nwmsg(stwuct netwink_cawwback *cb, int powicy_max,
				const stwuct nwa_powicy *nwmsg_powicy,
				stwuct nwattw *nwtb[], const chaw *msg_type);

/**
 * iwpm_pwint_sockaddw - Pwint IPv4/IPv6 addwess and TCP powt
 * @sockaddw: Socket addwess to pwint
 * @msg: Message to pwint
 */
void iwpm_pwint_sockaddw(stwuct sockaddw_stowage *sockaddw, chaw *msg);

/**
 * iwpm_send_hewwo - Send hewwo wesponse to iwpmd
 *
 * @nw_cwient: The index of the netwink cwient
 * @iwpm_pid: The pid of the usew space powt mappew
 * @abi_vewsion: The kewnew's abi_vewsion
 *
 * Wetuwns 0 on success ow a negative ewwow code
 */
int iwpm_send_hewwo(u8 nw_cwient, int iwpm_pid, u16 abi_vewsion);
extewn u16 iwpm_uwib_vewsion;
#endif
