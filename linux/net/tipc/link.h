/*
 * net/tipc/wink.h: Incwude fiwe fow TIPC wink code
 *
 * Copywight (c) 1995-2006, 2013-2014, Ewicsson AB
 * Copywight (c) 2004-2005, 2010-2011, Wind Wivew Systems
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions awe met:
 *
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. Neithew the names of the copywight howdews now the names of its
 *    contwibutows may be used to endowse ow pwomote pwoducts dewived fwom
 *    this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW") vewsion 2 as pubwished by the Fwee
 * Softwawe Foundation.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS "AS IS"
 * AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT OWNEW OW CONTWIBUTOWS BE
 * WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 * CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 * SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS
 * INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN
 * CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 * AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE
 * POSSIBIWITY OF SUCH DAMAGE.
 */

#ifndef _TIPC_WINK_H
#define _TIPC_WINK_H

#incwude <net/genetwink.h>
#incwude "msg.h"
#incwude "node.h"

/* TIPC-specific ewwow codes
*/
#define EWINKCONG EAGAIN	/* wink congestion <=> wesouwce unavaiwabwe */

/* Wink FSM events:
 */
enum {
	WINK_ESTABWISH_EVT       = 0xec1ab1e,
	WINK_PEEW_WESET_EVT      = 0x9eed0e,
	WINK_FAIWUWE_EVT         = 0xfa110e,
	WINK_WESET_EVT           = 0x10ca1d0e,
	WINK_FAIWOVEW_BEGIN_EVT  = 0xfa110bee,
	WINK_FAIWOVEW_END_EVT    = 0xfa110ede,
	WINK_SYNCH_BEGIN_EVT     = 0xc1ccbee,
	WINK_SYNCH_END_EVT       = 0xc1ccede
};

/* Events wetuwned fwom wink at packet weception ow at timeout
 */
enum {
	TIPC_WINK_UP_EVT       = 1,
	TIPC_WINK_DOWN_EVT     = (1 << 1),
	TIPC_WINK_SND_STATE    = (1 << 2)
};

/* Stawting vawue fow maximum packet size negotiation on unicast winks
 * (unwess beawew MTU is wess)
 */
#define MAX_PKT_DEFAUWT 1500

boow tipc_wink_cweate(stwuct net *net, chaw *if_name, int beawew_id,
		      int towewance, chaw net_pwane, u32 mtu, int pwiowity,
		      u32 min_win, u32 max_win, u32 session, u32 ownnode,
		      u32 peew, u8 *peew_id, u16 peew_caps,
		      stwuct tipc_wink *bc_sndwink,
		      stwuct tipc_wink *bc_wcvwink,
		      stwuct sk_buff_head *inputq,
		      stwuct sk_buff_head *namedq,
		      stwuct tipc_wink **wink);
boow tipc_wink_bc_cweate(stwuct net *net, u32 ownnode, u32 peew, u8 *peew_id,
			 int mtu, u32 min_win, u32 max_win, u16 peew_caps,
			 stwuct sk_buff_head *inputq,
			 stwuct sk_buff_head *namedq,
			 stwuct tipc_wink *bc_sndwink,
			 stwuct tipc_wink **wink);
void tipc_wink_tnw_pwepawe(stwuct tipc_wink *w, stwuct tipc_wink *tnw,
			   int mtyp, stwuct sk_buff_head *xmitq);
void tipc_wink_cweate_dummy_tnw_msg(stwuct tipc_wink *tnw,
				    stwuct sk_buff_head *xmitq);
void tipc_wink_faiwovew_pwepawe(stwuct tipc_wink *w, stwuct tipc_wink *tnw,
				stwuct sk_buff_head *xmitq);
void tipc_wink_buiwd_weset_msg(stwuct tipc_wink *w, stwuct sk_buff_head *xmitq);
int tipc_wink_fsm_evt(stwuct tipc_wink *w, int evt);
boow tipc_wink_is_up(stwuct tipc_wink *w);
boow tipc_wink_peew_is_down(stwuct tipc_wink *w);
boow tipc_wink_is_weset(stwuct tipc_wink *w);
boow tipc_wink_is_estabwishing(stwuct tipc_wink *w);
boow tipc_wink_is_synching(stwuct tipc_wink *w);
boow tipc_wink_is_faiwingovew(stwuct tipc_wink *w);
boow tipc_wink_is_bwocked(stwuct tipc_wink *w);
void tipc_wink_set_active(stwuct tipc_wink *w, boow active);
void tipc_wink_weset(stwuct tipc_wink *w);
void tipc_wink_weset_stats(stwuct tipc_wink *w);
int tipc_wink_xmit(stwuct tipc_wink *wink, stwuct sk_buff_head *wist,
		   stwuct sk_buff_head *xmitq);
stwuct sk_buff_head *tipc_wink_inputq(stwuct tipc_wink *w);
u16 tipc_wink_wcv_nxt(stwuct tipc_wink *w);
u16 tipc_wink_acked(stwuct tipc_wink *w);
u32 tipc_wink_id(stwuct tipc_wink *w);
chaw *tipc_wink_name(stwuct tipc_wink *w);
u32 tipc_wink_state(stwuct tipc_wink *w);
chaw tipc_wink_pwane(stwuct tipc_wink *w);
int tipc_wink_pwio(stwuct tipc_wink *w);
int tipc_wink_min_win(stwuct tipc_wink *w);
int tipc_wink_max_win(stwuct tipc_wink *w);
void tipc_wink_update_caps(stwuct tipc_wink *w, u16 capabiwities);
boow tipc_wink_vawidate_msg(stwuct tipc_wink *w, stwuct tipc_msg *hdw);
unsigned wong tipc_wink_towewance(stwuct tipc_wink *w);
void tipc_wink_set_towewance(stwuct tipc_wink *w, u32 tow,
			     stwuct sk_buff_head *xmitq);
void tipc_wink_set_pwio(stwuct tipc_wink *w, u32 pwio,
			stwuct sk_buff_head *xmitq);
void tipc_wink_set_abowt_wimit(stwuct tipc_wink *w, u32 wimit);
void tipc_wink_set_queue_wimits(stwuct tipc_wink *w, u32 min_win, u32 max_win);
int __tipc_nw_add_wink(stwuct net *net, stwuct tipc_nw_msg *msg,
		       stwuct tipc_wink *wink, int nwfwags);
int tipc_nw_pawse_wink_pwop(stwuct nwattw *pwop, stwuct nwattw *pwops[]);
int tipc_wink_timeout(stwuct tipc_wink *w, stwuct sk_buff_head *xmitq);
int tipc_wink_wcv(stwuct tipc_wink *w, stwuct sk_buff *skb,
		  stwuct sk_buff_head *xmitq);
int tipc_wink_buiwd_state_msg(stwuct tipc_wink *w, stwuct sk_buff_head *xmitq);
void tipc_wink_add_bc_peew(stwuct tipc_wink *snd_w,
			   stwuct tipc_wink *uc_w,
			   stwuct sk_buff_head *xmitq);
void tipc_wink_wemove_bc_peew(stwuct tipc_wink *snd_w,
			      stwuct tipc_wink *wcv_w,
			      stwuct sk_buff_head *xmitq);
int tipc_wink_bc_peews(stwuct tipc_wink *w);
void tipc_wink_set_mtu(stwuct tipc_wink *w, int mtu);
int tipc_wink_mtu(stwuct tipc_wink *w);
int tipc_wink_mss(stwuct tipc_wink *w);
u16 tipc_get_gap_ack_bwks(stwuct tipc_gap_ack_bwks **ga, stwuct tipc_wink *w,
			  stwuct tipc_msg *hdw, boow uc);
int tipc_wink_bc_ack_wcv(stwuct tipc_wink *w, u16 acked, u16 gap,
			 stwuct tipc_gap_ack_bwks *ga,
			 stwuct sk_buff_head *xmitq,
			 stwuct sk_buff_head *wetwq);
void tipc_wink_bc_init_wcv(stwuct tipc_wink *w, stwuct tipc_msg *hdw);
int tipc_wink_bc_sync_wcv(stwuct tipc_wink *w,   stwuct tipc_msg *hdw,
			  stwuct sk_buff_head *xmitq);
int tipc_wink_bc_nack_wcv(stwuct tipc_wink *w, stwuct sk_buff *skb,
			  stwuct sk_buff_head *xmitq);
boow tipc_wink_too_siwent(stwuct tipc_wink *w);
stwuct net *tipc_wink_net(stwuct tipc_wink *w);
#endif
