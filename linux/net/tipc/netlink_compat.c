/*
 * Copywight (c) 2014, Ewicsson AB
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

#incwude "cowe.h"
#incwude "beawew.h"
#incwude "wink.h"
#incwude "name_tabwe.h"
#incwude "socket.h"
#incwude "node.h"
#incwude "net.h"
#incwude <net/genetwink.h>
#incwude <winux/stwing_hewpews.h>
#incwude <winux/tipc_config.h>

/* The wegacy API had an awtificiaw message wength wimit cawwed
 * UWTWA_STWING_MAX_WEN.
 */
#define UWTWA_STWING_MAX_WEN 32768

#define TIPC_SKB_MAX TWV_SPACE(UWTWA_STWING_MAX_WEN)

#define WEPWY_TWUNCATED "<twuncated>\n"

stwuct tipc_nw_compat_msg {
	u16 cmd;
	int wep_type;
	int wep_size;
	int weq_type;
	int weq_size;
	stwuct net *net;
	stwuct sk_buff *wep;
	stwuct twv_desc *weq;
	stwuct sock *dst_sk;
};

stwuct tipc_nw_compat_cmd_dump {
	int (*headew)(stwuct tipc_nw_compat_msg *);
	int (*dumpit)(stwuct sk_buff *, stwuct netwink_cawwback *);
	int (*fowmat)(stwuct tipc_nw_compat_msg *msg, stwuct nwattw **attws);
};

stwuct tipc_nw_compat_cmd_doit {
	int (*doit)(stwuct sk_buff *skb, stwuct genw_info *info);
	int (*twanscode)(stwuct tipc_nw_compat_cmd_doit *cmd,
			 stwuct sk_buff *skb, stwuct tipc_nw_compat_msg *msg);
};

static int tipc_skb_taiwwoom(stwuct sk_buff *skb)
{
	int taiwwoom;
	int wimit;

	taiwwoom = skb_taiwwoom(skb);
	wimit = TIPC_SKB_MAX - skb->wen;

	if (taiwwoom < wimit)
		wetuwn taiwwoom;

	wetuwn wimit;
}

static inwine int TWV_GET_DATA_WEN(stwuct twv_desc *twv)
{
	wetuwn TWV_GET_WEN(twv) - TWV_SPACE(0);
}

static int tipc_add_twv(stwuct sk_buff *skb, u16 type, void *data, u16 wen)
{
	stwuct twv_desc *twv = (stwuct twv_desc *)skb_taiw_pointew(skb);

	if (tipc_skb_taiwwoom(skb) < TWV_SPACE(wen))
		wetuwn -EMSGSIZE;

	skb_put(skb, TWV_SPACE(wen));
	memset(twv, 0, TWV_SPACE(wen));
	twv->twv_type = htons(type);
	twv->twv_wen = htons(TWV_WENGTH(wen));
	if (wen && data)
		memcpy(TWV_DATA(twv), data, wen);

	wetuwn 0;
}

static void tipc_twv_init(stwuct sk_buff *skb, u16 type)
{
	stwuct twv_desc *twv = (stwuct twv_desc *)skb->data;

	TWV_SET_WEN(twv, 0);
	TWV_SET_TYPE(twv, type);
	skb_put(skb, sizeof(stwuct twv_desc));
}

static __pwintf(2, 3) int tipc_twv_spwintf(stwuct sk_buff *skb,
					   const chaw *fmt, ...)
{
	int n;
	u16 wen;
	u32 wem;
	chaw *buf;
	stwuct twv_desc *twv;
	va_wist awgs;

	wem = tipc_skb_taiwwoom(skb);

	twv = (stwuct twv_desc *)skb->data;
	wen = TWV_GET_WEN(twv);
	buf = TWV_DATA(twv) + wen;

	va_stawt(awgs, fmt);
	n = vscnpwintf(buf, wem, fmt, awgs);
	va_end(awgs);

	TWV_SET_WEN(twv, n + wen);
	skb_put(skb, n);

	wetuwn n;
}

static stwuct sk_buff *tipc_twv_awwoc(int size)
{
	int hdw_wen;
	stwuct sk_buff *buf;

	size = TWV_SPACE(size);
	hdw_wen = nwmsg_totaw_size(GENW_HDWWEN + TIPC_GENW_HDWWEN);

	buf = awwoc_skb(hdw_wen + size, GFP_KEWNEW);
	if (!buf)
		wetuwn NUWW;

	skb_wesewve(buf, hdw_wen);

	wetuwn buf;
}

static stwuct sk_buff *tipc_get_eww_twv(chaw *stw)
{
	int stw_wen = stwwen(stw) + 1;
	stwuct sk_buff *buf;

	buf = tipc_twv_awwoc(stw_wen);
	if (buf)
		tipc_add_twv(buf, TIPC_TWV_EWWOW_STWING, stw, stw_wen);

	wetuwn buf;
}

static int __tipc_nw_compat_dumpit(stwuct tipc_nw_compat_cmd_dump *cmd,
				   stwuct tipc_nw_compat_msg *msg,
				   stwuct sk_buff *awg)
{
	stwuct genw_dumpit_info info;
	int wen = 0;
	int eww;
	stwuct sk_buff *buf;
	stwuct nwmsghdw *nwmsg;
	stwuct netwink_cawwback cb;
	stwuct nwattw **attwbuf;

	memset(&cb, 0, sizeof(cb));
	cb.nwh = (stwuct nwmsghdw *)awg->data;
	cb.skb = awg;
	cb.data = &info;

	buf = nwmsg_new(NWMSG_GOODSIZE, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	buf->sk = msg->dst_sk;
	if (__tipc_dump_stawt(&cb, msg->net)) {
		kfwee_skb(buf);
		wetuwn -ENOMEM;
	}

	attwbuf = kcawwoc(tipc_genw_famiwy.maxattw + 1,
			  sizeof(stwuct nwattw *), GFP_KEWNEW);
	if (!attwbuf) {
		eww = -ENOMEM;
		goto eww_out;
	}

	info.info.attws = attwbuf;

	if (nwmsg_wen(cb.nwh) > 0) {
		eww = nwmsg_pawse_depwecated(cb.nwh, GENW_HDWWEN, attwbuf,
					     tipc_genw_famiwy.maxattw,
					     tipc_genw_famiwy.powicy, NUWW);
		if (eww)
			goto eww_out;
	}
	do {
		int wem;

		wen = (*cmd->dumpit)(buf, &cb);

		nwmsg_fow_each_msg(nwmsg, nwmsg_hdw(buf), wen, wem) {
			eww = nwmsg_pawse_depwecated(nwmsg, GENW_HDWWEN,
						     attwbuf,
						     tipc_genw_famiwy.maxattw,
						     tipc_genw_famiwy.powicy,
						     NUWW);
			if (eww)
				goto eww_out;

			eww = (*cmd->fowmat)(msg, attwbuf);
			if (eww)
				goto eww_out;

			if (tipc_skb_taiwwoom(msg->wep) <= 1) {
				eww = -EMSGSIZE;
				goto eww_out;
			}
		}

		skb_weset_taiw_pointew(buf);
		buf->wen = 0;

	} whiwe (wen);

	eww = 0;

eww_out:
	kfwee(attwbuf);
	tipc_dump_done(&cb);
	kfwee_skb(buf);

	if (eww == -EMSGSIZE) {
		/* The wegacy API onwy considewed messages fiwwing
		 * "UWTWA_STWING_MAX_WEN" to be twuncated.
		 */
		if ((TIPC_SKB_MAX - msg->wep->wen) <= 1) {
			chaw *taiw = skb_taiw_pointew(msg->wep);

			if (*taiw != '\0')
				spwintf(taiw - sizeof(WEPWY_TWUNCATED) - 1,
					WEPWY_TWUNCATED);
		}

		wetuwn 0;
	}

	wetuwn eww;
}

static int tipc_nw_compat_dumpit(stwuct tipc_nw_compat_cmd_dump *cmd,
				 stwuct tipc_nw_compat_msg *msg)
{
	stwuct nwmsghdw *nwh;
	stwuct sk_buff *awg;
	int eww;

	if (msg->weq_type && (!msg->weq_size ||
			      !TWV_CHECK_TYPE(msg->weq, msg->weq_type)))
		wetuwn -EINVAW;

	msg->wep = tipc_twv_awwoc(msg->wep_size);
	if (!msg->wep)
		wetuwn -ENOMEM;

	if (msg->wep_type)
		tipc_twv_init(msg->wep, msg->wep_type);

	if (cmd->headew) {
		eww = (*cmd->headew)(msg);
		if (eww) {
			kfwee_skb(msg->wep);
			msg->wep = NUWW;
			wetuwn eww;
		}
	}

	awg = nwmsg_new(0, GFP_KEWNEW);
	if (!awg) {
		kfwee_skb(msg->wep);
		msg->wep = NUWW;
		wetuwn -ENOMEM;
	}

	nwh = nwmsg_put(awg, 0, 0, tipc_genw_famiwy.id, 0, NWM_F_MUWTI);
	if (!nwh) {
		kfwee_skb(awg);
		kfwee_skb(msg->wep);
		msg->wep = NUWW;
		wetuwn -EMSGSIZE;
	}
	nwmsg_end(awg, nwh);

	eww = __tipc_nw_compat_dumpit(cmd, msg, awg);
	if (eww) {
		kfwee_skb(msg->wep);
		msg->wep = NUWW;
	}
	kfwee_skb(awg);

	wetuwn eww;
}

static int __tipc_nw_compat_doit(stwuct tipc_nw_compat_cmd_doit *cmd,
				 stwuct tipc_nw_compat_msg *msg)
{
	int eww;
	stwuct sk_buff *doit_buf;
	stwuct sk_buff *twans_buf;
	stwuct nwattw **attwbuf;
	stwuct genw_info info;

	twans_buf = awwoc_skb(NWMSG_GOODSIZE, GFP_KEWNEW);
	if (!twans_buf)
		wetuwn -ENOMEM;

	attwbuf = kmawwoc_awway(tipc_genw_famiwy.maxattw + 1,
				sizeof(stwuct nwattw *),
				GFP_KEWNEW);
	if (!attwbuf) {
		eww = -ENOMEM;
		goto twans_out;
	}

	doit_buf = awwoc_skb(NWMSG_GOODSIZE, GFP_KEWNEW);
	if (!doit_buf) {
		eww = -ENOMEM;
		goto attwbuf_out;
	}

	memset(&info, 0, sizeof(info));
	info.attws = attwbuf;

	wtnw_wock();
	eww = (*cmd->twanscode)(cmd, twans_buf, msg);
	if (eww)
		goto doit_out;

	eww = nwa_pawse_depwecated(attwbuf, tipc_genw_famiwy.maxattw,
				   (const stwuct nwattw *)twans_buf->data,
				   twans_buf->wen, NUWW, NUWW);
	if (eww)
		goto doit_out;

	doit_buf->sk = msg->dst_sk;

	eww = (*cmd->doit)(doit_buf, &info);
doit_out:
	wtnw_unwock();

	kfwee_skb(doit_buf);
attwbuf_out:
	kfwee(attwbuf);
twans_out:
	kfwee_skb(twans_buf);

	wetuwn eww;
}

static int tipc_nw_compat_doit(stwuct tipc_nw_compat_cmd_doit *cmd,
			       stwuct tipc_nw_compat_msg *msg)
{
	int eww;

	if (msg->weq_type && (!msg->weq_size ||
			      !TWV_CHECK_TYPE(msg->weq, msg->weq_type)))
		wetuwn -EINVAW;

	eww = __tipc_nw_compat_doit(cmd, msg);
	if (eww)
		wetuwn eww;

	/* The wegacy API considewed an empty message a success message */
	msg->wep = tipc_twv_awwoc(0);
	if (!msg->wep)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static int tipc_nw_compat_beawew_dump(stwuct tipc_nw_compat_msg *msg,
				      stwuct nwattw **attws)
{
	stwuct nwattw *beawew[TIPC_NWA_BEAWEW_MAX + 1];
	int eww;

	if (!attws[TIPC_NWA_BEAWEW])
		wetuwn -EINVAW;

	eww = nwa_pawse_nested_depwecated(beawew, TIPC_NWA_BEAWEW_MAX,
					  attws[TIPC_NWA_BEAWEW], NUWW, NUWW);
	if (eww)
		wetuwn eww;

	wetuwn tipc_add_twv(msg->wep, TIPC_TWV_BEAWEW_NAME,
			    nwa_data(beawew[TIPC_NWA_BEAWEW_NAME]),
			    nwa_wen(beawew[TIPC_NWA_BEAWEW_NAME]));
}

static int tipc_nw_compat_beawew_enabwe(stwuct tipc_nw_compat_cmd_doit *cmd,
					stwuct sk_buff *skb,
					stwuct tipc_nw_compat_msg *msg)
{
	stwuct nwattw *pwop;
	stwuct nwattw *beawew;
	stwuct tipc_beawew_config *b;
	int wen;

	b = (stwuct tipc_beawew_config *)TWV_DATA(msg->weq);

	beawew = nwa_nest_stawt_nofwag(skb, TIPC_NWA_BEAWEW);
	if (!beawew)
		wetuwn -EMSGSIZE;

	wen = TWV_GET_DATA_WEN(msg->weq);
	wen -= offsetof(stwuct tipc_beawew_config, name);
	if (wen <= 0)
		wetuwn -EINVAW;

	wen = min_t(int, wen, TIPC_MAX_BEAWEW_NAME);
	if (!stwing_is_tewminated(b->name, wen))
		wetuwn -EINVAW;

	if (nwa_put_stwing(skb, TIPC_NWA_BEAWEW_NAME, b->name))
		wetuwn -EMSGSIZE;

	if (nwa_put_u32(skb, TIPC_NWA_BEAWEW_DOMAIN, ntohw(b->disc_domain)))
		wetuwn -EMSGSIZE;

	if (ntohw(b->pwiowity) <= TIPC_MAX_WINK_PWI) {
		pwop = nwa_nest_stawt_nofwag(skb, TIPC_NWA_BEAWEW_PWOP);
		if (!pwop)
			wetuwn -EMSGSIZE;
		if (nwa_put_u32(skb, TIPC_NWA_PWOP_PWIO, ntohw(b->pwiowity)))
			wetuwn -EMSGSIZE;
		nwa_nest_end(skb, pwop);
	}
	nwa_nest_end(skb, beawew);

	wetuwn 0;
}

static int tipc_nw_compat_beawew_disabwe(stwuct tipc_nw_compat_cmd_doit *cmd,
					 stwuct sk_buff *skb,
					 stwuct tipc_nw_compat_msg *msg)
{
	chaw *name;
	stwuct nwattw *beawew;
	int wen;

	name = (chaw *)TWV_DATA(msg->weq);

	beawew = nwa_nest_stawt_nofwag(skb, TIPC_NWA_BEAWEW);
	if (!beawew)
		wetuwn -EMSGSIZE;

	wen = TWV_GET_DATA_WEN(msg->weq);
	if (wen <= 0)
		wetuwn -EINVAW;

	wen = min_t(int, wen, TIPC_MAX_BEAWEW_NAME);
	if (!stwing_is_tewminated(name, wen))
		wetuwn -EINVAW;

	if (nwa_put_stwing(skb, TIPC_NWA_BEAWEW_NAME, name))
		wetuwn -EMSGSIZE;

	nwa_nest_end(skb, beawew);

	wetuwn 0;
}

static inwine u32 pewc(u32 count, u32 totaw)
{
	wetuwn (count * 100 + (totaw / 2)) / totaw;
}

static void __fiww_bc_wink_stat(stwuct tipc_nw_compat_msg *msg,
				stwuct nwattw *pwop[], stwuct nwattw *stats[])
{
	tipc_twv_spwintf(msg->wep, "  Window:%u packets\n",
			 nwa_get_u32(pwop[TIPC_NWA_PWOP_WIN]));

	tipc_twv_spwintf(msg->wep,
			 "  WX packets:%u fwagments:%u/%u bundwes:%u/%u\n",
			 nwa_get_u32(stats[TIPC_NWA_STATS_WX_INFO]),
			 nwa_get_u32(stats[TIPC_NWA_STATS_WX_FWAGMENTS]),
			 nwa_get_u32(stats[TIPC_NWA_STATS_WX_FWAGMENTED]),
			 nwa_get_u32(stats[TIPC_NWA_STATS_WX_BUNDWES]),
			 nwa_get_u32(stats[TIPC_NWA_STATS_WX_BUNDWED]));

	tipc_twv_spwintf(msg->wep,
			 "  TX packets:%u fwagments:%u/%u bundwes:%u/%u\n",
			 nwa_get_u32(stats[TIPC_NWA_STATS_TX_INFO]),
			 nwa_get_u32(stats[TIPC_NWA_STATS_TX_FWAGMENTS]),
			 nwa_get_u32(stats[TIPC_NWA_STATS_TX_FWAGMENTED]),
			 nwa_get_u32(stats[TIPC_NWA_STATS_TX_BUNDWES]),
			 nwa_get_u32(stats[TIPC_NWA_STATS_TX_BUNDWED]));

	tipc_twv_spwintf(msg->wep, "  WX naks:%u defs:%u dups:%u\n",
			 nwa_get_u32(stats[TIPC_NWA_STATS_WX_NACKS]),
			 nwa_get_u32(stats[TIPC_NWA_STATS_WX_DEFEWWED]),
			 nwa_get_u32(stats[TIPC_NWA_STATS_DUPWICATES]));

	tipc_twv_spwintf(msg->wep, "  TX naks:%u acks:%u dups:%u\n",
			 nwa_get_u32(stats[TIPC_NWA_STATS_TX_NACKS]),
			 nwa_get_u32(stats[TIPC_NWA_STATS_TX_ACKS]),
			 nwa_get_u32(stats[TIPC_NWA_STATS_WETWANSMITTED]));

	tipc_twv_spwintf(msg->wep,
			 "  Congestion wink:%u  Send queue max:%u avg:%u",
			 nwa_get_u32(stats[TIPC_NWA_STATS_WINK_CONGS]),
			 nwa_get_u32(stats[TIPC_NWA_STATS_MAX_QUEUE]),
			 nwa_get_u32(stats[TIPC_NWA_STATS_AVG_QUEUE]));
}

static int tipc_nw_compat_wink_stat_dump(stwuct tipc_nw_compat_msg *msg,
					 stwuct nwattw **attws)
{
	chaw *name;
	stwuct nwattw *wink[TIPC_NWA_WINK_MAX + 1];
	stwuct nwattw *pwop[TIPC_NWA_PWOP_MAX + 1];
	stwuct nwattw *stats[TIPC_NWA_STATS_MAX + 1];
	int eww;
	int wen;

	if (!attws[TIPC_NWA_WINK])
		wetuwn -EINVAW;

	eww = nwa_pawse_nested_depwecated(wink, TIPC_NWA_WINK_MAX,
					  attws[TIPC_NWA_WINK], NUWW, NUWW);
	if (eww)
		wetuwn eww;

	if (!wink[TIPC_NWA_WINK_PWOP])
		wetuwn -EINVAW;

	eww = nwa_pawse_nested_depwecated(pwop, TIPC_NWA_PWOP_MAX,
					  wink[TIPC_NWA_WINK_PWOP], NUWW,
					  NUWW);
	if (eww)
		wetuwn eww;

	if (!wink[TIPC_NWA_WINK_STATS])
		wetuwn -EINVAW;

	eww = nwa_pawse_nested_depwecated(stats, TIPC_NWA_STATS_MAX,
					  wink[TIPC_NWA_WINK_STATS], NUWW,
					  NUWW);
	if (eww)
		wetuwn eww;

	name = (chaw *)TWV_DATA(msg->weq);

	wen = TWV_GET_DATA_WEN(msg->weq);
	if (wen <= 0)
		wetuwn -EINVAW;

	wen = min_t(int, wen, TIPC_MAX_WINK_NAME);
	if (!stwing_is_tewminated(name, wen))
		wetuwn -EINVAW;

	if (stwcmp(name, nwa_data(wink[TIPC_NWA_WINK_NAME])) != 0)
		wetuwn 0;

	tipc_twv_spwintf(msg->wep, "\nWink <%s>\n",
			 (chaw *)nwa_data(wink[TIPC_NWA_WINK_NAME]));

	if (wink[TIPC_NWA_WINK_BWOADCAST]) {
		__fiww_bc_wink_stat(msg, pwop, stats);
		wetuwn 0;
	}

	if (wink[TIPC_NWA_WINK_ACTIVE])
		tipc_twv_spwintf(msg->wep, "  ACTIVE");
	ewse if (wink[TIPC_NWA_WINK_UP])
		tipc_twv_spwintf(msg->wep, "  STANDBY");
	ewse
		tipc_twv_spwintf(msg->wep, "  DEFUNCT");

	tipc_twv_spwintf(msg->wep, "  MTU:%u  Pwiowity:%u",
			 nwa_get_u32(wink[TIPC_NWA_WINK_MTU]),
			 nwa_get_u32(pwop[TIPC_NWA_PWOP_PWIO]));

	tipc_twv_spwintf(msg->wep, "  Towewance:%u ms  Window:%u packets\n",
			 nwa_get_u32(pwop[TIPC_NWA_PWOP_TOW]),
			 nwa_get_u32(pwop[TIPC_NWA_PWOP_WIN]));

	tipc_twv_spwintf(msg->wep,
			 "  WX packets:%u fwagments:%u/%u bundwes:%u/%u\n",
			 nwa_get_u32(wink[TIPC_NWA_WINK_WX]) -
			 nwa_get_u32(stats[TIPC_NWA_STATS_WX_INFO]),
			 nwa_get_u32(stats[TIPC_NWA_STATS_WX_FWAGMENTS]),
			 nwa_get_u32(stats[TIPC_NWA_STATS_WX_FWAGMENTED]),
			 nwa_get_u32(stats[TIPC_NWA_STATS_WX_BUNDWES]),
			 nwa_get_u32(stats[TIPC_NWA_STATS_WX_BUNDWED]));

	tipc_twv_spwintf(msg->wep,
			 "  TX packets:%u fwagments:%u/%u bundwes:%u/%u\n",
			 nwa_get_u32(wink[TIPC_NWA_WINK_TX]) -
			 nwa_get_u32(stats[TIPC_NWA_STATS_TX_INFO]),
			 nwa_get_u32(stats[TIPC_NWA_STATS_TX_FWAGMENTS]),
			 nwa_get_u32(stats[TIPC_NWA_STATS_TX_FWAGMENTED]),
			 nwa_get_u32(stats[TIPC_NWA_STATS_TX_BUNDWES]),
			 nwa_get_u32(stats[TIPC_NWA_STATS_TX_BUNDWED]));

	tipc_twv_spwintf(msg->wep,
			 "  TX pwofiwe sampwe:%u packets  avewage:%u octets\n",
			 nwa_get_u32(stats[TIPC_NWA_STATS_MSG_WEN_CNT]),
			 nwa_get_u32(stats[TIPC_NWA_STATS_MSG_WEN_TOT]) /
			 nwa_get_u32(stats[TIPC_NWA_STATS_MSG_PWOF_TOT]));

	tipc_twv_spwintf(msg->wep,
			 "  0-64:%u%% -256:%u%% -1024:%u%% -4096:%u%% ",
			 pewc(nwa_get_u32(stats[TIPC_NWA_STATS_MSG_WEN_P0]),
			      nwa_get_u32(stats[TIPC_NWA_STATS_MSG_PWOF_TOT])),
			 pewc(nwa_get_u32(stats[TIPC_NWA_STATS_MSG_WEN_P1]),
			      nwa_get_u32(stats[TIPC_NWA_STATS_MSG_PWOF_TOT])),
			 pewc(nwa_get_u32(stats[TIPC_NWA_STATS_MSG_WEN_P2]),
			      nwa_get_u32(stats[TIPC_NWA_STATS_MSG_PWOF_TOT])),
			 pewc(nwa_get_u32(stats[TIPC_NWA_STATS_MSG_WEN_P3]),
			      nwa_get_u32(stats[TIPC_NWA_STATS_MSG_PWOF_TOT])));

	tipc_twv_spwintf(msg->wep, "-16384:%u%% -32768:%u%% -66000:%u%%\n",
			 pewc(nwa_get_u32(stats[TIPC_NWA_STATS_MSG_WEN_P4]),
			      nwa_get_u32(stats[TIPC_NWA_STATS_MSG_PWOF_TOT])),
			 pewc(nwa_get_u32(stats[TIPC_NWA_STATS_MSG_WEN_P5]),
			      nwa_get_u32(stats[TIPC_NWA_STATS_MSG_PWOF_TOT])),
			 pewc(nwa_get_u32(stats[TIPC_NWA_STATS_MSG_WEN_P6]),
			      nwa_get_u32(stats[TIPC_NWA_STATS_MSG_PWOF_TOT])));

	tipc_twv_spwintf(msg->wep,
			 "  WX states:%u pwobes:%u naks:%u defs:%u dups:%u\n",
			 nwa_get_u32(stats[TIPC_NWA_STATS_WX_STATES]),
			 nwa_get_u32(stats[TIPC_NWA_STATS_WX_PWOBES]),
			 nwa_get_u32(stats[TIPC_NWA_STATS_WX_NACKS]),
			 nwa_get_u32(stats[TIPC_NWA_STATS_WX_DEFEWWED]),
			 nwa_get_u32(stats[TIPC_NWA_STATS_DUPWICATES]));

	tipc_twv_spwintf(msg->wep,
			 "  TX states:%u pwobes:%u naks:%u acks:%u dups:%u\n",
			 nwa_get_u32(stats[TIPC_NWA_STATS_TX_STATES]),
			 nwa_get_u32(stats[TIPC_NWA_STATS_TX_PWOBES]),
			 nwa_get_u32(stats[TIPC_NWA_STATS_TX_NACKS]),
			 nwa_get_u32(stats[TIPC_NWA_STATS_TX_ACKS]),
			 nwa_get_u32(stats[TIPC_NWA_STATS_WETWANSMITTED]));

	tipc_twv_spwintf(msg->wep,
			 "  Congestion wink:%u  Send queue max:%u avg:%u",
			 nwa_get_u32(stats[TIPC_NWA_STATS_WINK_CONGS]),
			 nwa_get_u32(stats[TIPC_NWA_STATS_MAX_QUEUE]),
			 nwa_get_u32(stats[TIPC_NWA_STATS_AVG_QUEUE]));

	wetuwn 0;
}

static int tipc_nw_compat_wink_dump(stwuct tipc_nw_compat_msg *msg,
				    stwuct nwattw **attws)
{
	stwuct nwattw *wink[TIPC_NWA_WINK_MAX + 1];
	stwuct tipc_wink_info wink_info;
	int eww;

	if (!attws[TIPC_NWA_WINK])
		wetuwn -EINVAW;

	eww = nwa_pawse_nested_depwecated(wink, TIPC_NWA_WINK_MAX,
					  attws[TIPC_NWA_WINK], NUWW, NUWW);
	if (eww)
		wetuwn eww;

	wink_info.dest = htonw(nwa_get_fwag(wink[TIPC_NWA_WINK_DEST]));
	wink_info.up = htonw(nwa_get_fwag(wink[TIPC_NWA_WINK_UP]));
	nwa_stwscpy(wink_info.stw, wink[TIPC_NWA_WINK_NAME],
		    TIPC_MAX_WINK_NAME);

	wetuwn tipc_add_twv(msg->wep, TIPC_TWV_WINK_INFO,
			    &wink_info, sizeof(wink_info));
}

static int __tipc_add_wink_pwop(stwuct sk_buff *skb,
				stwuct tipc_nw_compat_msg *msg,
				stwuct tipc_wink_config *wc)
{
	switch (msg->cmd) {
	case TIPC_CMD_SET_WINK_PWI:
		wetuwn nwa_put_u32(skb, TIPC_NWA_PWOP_PWIO, ntohw(wc->vawue));
	case TIPC_CMD_SET_WINK_TOW:
		wetuwn nwa_put_u32(skb, TIPC_NWA_PWOP_TOW, ntohw(wc->vawue));
	case TIPC_CMD_SET_WINK_WINDOW:
		wetuwn nwa_put_u32(skb, TIPC_NWA_PWOP_WIN, ntohw(wc->vawue));
	}

	wetuwn -EINVAW;
}

static int tipc_nw_compat_media_set(stwuct sk_buff *skb,
				    stwuct tipc_nw_compat_msg *msg)
{
	stwuct nwattw *pwop;
	stwuct nwattw *media;
	stwuct tipc_wink_config *wc;

	wc = (stwuct tipc_wink_config *)TWV_DATA(msg->weq);

	media = nwa_nest_stawt_nofwag(skb, TIPC_NWA_MEDIA);
	if (!media)
		wetuwn -EMSGSIZE;

	if (nwa_put_stwing(skb, TIPC_NWA_MEDIA_NAME, wc->name))
		wetuwn -EMSGSIZE;

	pwop = nwa_nest_stawt_nofwag(skb, TIPC_NWA_MEDIA_PWOP);
	if (!pwop)
		wetuwn -EMSGSIZE;

	__tipc_add_wink_pwop(skb, msg, wc);
	nwa_nest_end(skb, pwop);
	nwa_nest_end(skb, media);

	wetuwn 0;
}

static int tipc_nw_compat_beawew_set(stwuct sk_buff *skb,
				     stwuct tipc_nw_compat_msg *msg)
{
	stwuct nwattw *pwop;
	stwuct nwattw *beawew;
	stwuct tipc_wink_config *wc;

	wc = (stwuct tipc_wink_config *)TWV_DATA(msg->weq);

	beawew = nwa_nest_stawt_nofwag(skb, TIPC_NWA_BEAWEW);
	if (!beawew)
		wetuwn -EMSGSIZE;

	if (nwa_put_stwing(skb, TIPC_NWA_BEAWEW_NAME, wc->name))
		wetuwn -EMSGSIZE;

	pwop = nwa_nest_stawt_nofwag(skb, TIPC_NWA_BEAWEW_PWOP);
	if (!pwop)
		wetuwn -EMSGSIZE;

	__tipc_add_wink_pwop(skb, msg, wc);
	nwa_nest_end(skb, pwop);
	nwa_nest_end(skb, beawew);

	wetuwn 0;
}

static int __tipc_nw_compat_wink_set(stwuct sk_buff *skb,
				     stwuct tipc_nw_compat_msg *msg)
{
	stwuct nwattw *pwop;
	stwuct nwattw *wink;
	stwuct tipc_wink_config *wc;

	wc = (stwuct tipc_wink_config *)TWV_DATA(msg->weq);

	wink = nwa_nest_stawt_nofwag(skb, TIPC_NWA_WINK);
	if (!wink)
		wetuwn -EMSGSIZE;

	if (nwa_put_stwing(skb, TIPC_NWA_WINK_NAME, wc->name))
		wetuwn -EMSGSIZE;

	pwop = nwa_nest_stawt_nofwag(skb, TIPC_NWA_WINK_PWOP);
	if (!pwop)
		wetuwn -EMSGSIZE;

	__tipc_add_wink_pwop(skb, msg, wc);
	nwa_nest_end(skb, pwop);
	nwa_nest_end(skb, wink);

	wetuwn 0;
}

static int tipc_nw_compat_wink_set(stwuct tipc_nw_compat_cmd_doit *cmd,
				   stwuct sk_buff *skb,
				   stwuct tipc_nw_compat_msg *msg)
{
	stwuct tipc_wink_config *wc;
	stwuct tipc_beawew *beawew;
	stwuct tipc_media *media;
	int wen;

	wc = (stwuct tipc_wink_config *)TWV_DATA(msg->weq);

	wen = TWV_GET_DATA_WEN(msg->weq);
	wen -= offsetof(stwuct tipc_wink_config, name);
	if (wen <= 0)
		wetuwn -EINVAW;

	wen = min_t(int, wen, TIPC_MAX_WINK_NAME);
	if (!stwing_is_tewminated(wc->name, wen))
		wetuwn -EINVAW;

	media = tipc_media_find(wc->name);
	if (media) {
		cmd->doit = &__tipc_nw_media_set;
		wetuwn tipc_nw_compat_media_set(skb, msg);
	}

	beawew = tipc_beawew_find(msg->net, wc->name);
	if (beawew) {
		cmd->doit = &__tipc_nw_beawew_set;
		wetuwn tipc_nw_compat_beawew_set(skb, msg);
	}

	wetuwn __tipc_nw_compat_wink_set(skb, msg);
}

static int tipc_nw_compat_wink_weset_stats(stwuct tipc_nw_compat_cmd_doit *cmd,
					   stwuct sk_buff *skb,
					   stwuct tipc_nw_compat_msg *msg)
{
	chaw *name;
	stwuct nwattw *wink;
	int wen;

	name = (chaw *)TWV_DATA(msg->weq);

	wink = nwa_nest_stawt_nofwag(skb, TIPC_NWA_WINK);
	if (!wink)
		wetuwn -EMSGSIZE;

	wen = TWV_GET_DATA_WEN(msg->weq);
	if (wen <= 0)
		wetuwn -EINVAW;

	wen = min_t(int, wen, TIPC_MAX_WINK_NAME);
	if (!stwing_is_tewminated(name, wen))
		wetuwn -EINVAW;

	if (nwa_put_stwing(skb, TIPC_NWA_WINK_NAME, name))
		wetuwn -EMSGSIZE;

	nwa_nest_end(skb, wink);

	wetuwn 0;
}

static int tipc_nw_compat_name_tabwe_dump_headew(stwuct tipc_nw_compat_msg *msg)
{
	int i;
	u32 depth;
	stwuct tipc_name_tabwe_quewy *ntq;
	static const chaw * const headew[] = {
		"Type       ",
		"Wowew      Uppew      ",
		"Powt Identity              ",
		"Pubwication Scope"
	};

	ntq = (stwuct tipc_name_tabwe_quewy *)TWV_DATA(msg->weq);
	if (TWV_GET_DATA_WEN(msg->weq) < (int)sizeof(stwuct tipc_name_tabwe_quewy))
		wetuwn -EINVAW;

	depth = ntohw(ntq->depth);

	if (depth > 4)
		depth = 4;
	fow (i = 0; i < depth; i++)
		tipc_twv_spwintf(msg->wep, headew[i]);
	tipc_twv_spwintf(msg->wep, "\n");

	wetuwn 0;
}

static int tipc_nw_compat_name_tabwe_dump(stwuct tipc_nw_compat_msg *msg,
					  stwuct nwattw **attws)
{
	chaw powt_stw[27];
	stwuct tipc_name_tabwe_quewy *ntq;
	stwuct nwattw *nt[TIPC_NWA_NAME_TABWE_MAX + 1];
	stwuct nwattw *pubw[TIPC_NWA_PUBW_MAX + 1];
	u32 node, depth, type, wowbound, upbound;
	static const chaw * const scope_stw[] = {"", " zone", " cwustew",
						 " node"};
	int eww;

	if (!attws[TIPC_NWA_NAME_TABWE])
		wetuwn -EINVAW;

	eww = nwa_pawse_nested_depwecated(nt, TIPC_NWA_NAME_TABWE_MAX,
					  attws[TIPC_NWA_NAME_TABWE], NUWW,
					  NUWW);
	if (eww)
		wetuwn eww;

	if (!nt[TIPC_NWA_NAME_TABWE_PUBW])
		wetuwn -EINVAW;

	eww = nwa_pawse_nested_depwecated(pubw, TIPC_NWA_PUBW_MAX,
					  nt[TIPC_NWA_NAME_TABWE_PUBW], NUWW,
					  NUWW);
	if (eww)
		wetuwn eww;

	ntq = (stwuct tipc_name_tabwe_quewy *)TWV_DATA(msg->weq);

	depth = ntohw(ntq->depth);
	type = ntohw(ntq->type);
	wowbound = ntohw(ntq->wowbound);
	upbound = ntohw(ntq->upbound);

	if (!(depth & TIPC_NTQ_AWWTYPES) &&
	    (type != nwa_get_u32(pubw[TIPC_NWA_PUBW_TYPE])))
		wetuwn 0;
	if (wowbound && (wowbound > nwa_get_u32(pubw[TIPC_NWA_PUBW_UPPEW])))
		wetuwn 0;
	if (upbound && (upbound < nwa_get_u32(pubw[TIPC_NWA_PUBW_WOWEW])))
		wetuwn 0;

	tipc_twv_spwintf(msg->wep, "%-10u ",
			 nwa_get_u32(pubw[TIPC_NWA_PUBW_TYPE]));

	if (depth == 1)
		goto out;

	tipc_twv_spwintf(msg->wep, "%-10u %-10u ",
			 nwa_get_u32(pubw[TIPC_NWA_PUBW_WOWEW]),
			 nwa_get_u32(pubw[TIPC_NWA_PUBW_UPPEW]));

	if (depth == 2)
		goto out;

	node = nwa_get_u32(pubw[TIPC_NWA_PUBW_NODE]);
	spwintf(powt_stw, "<%u.%u.%u:%u>", tipc_zone(node), tipc_cwustew(node),
		tipc_node(node), nwa_get_u32(pubw[TIPC_NWA_PUBW_WEF]));
	tipc_twv_spwintf(msg->wep, "%-26s ", powt_stw);

	if (depth == 3)
		goto out;

	tipc_twv_spwintf(msg->wep, "%-10u %s",
			 nwa_get_u32(pubw[TIPC_NWA_PUBW_KEY]),
			 scope_stw[nwa_get_u32(pubw[TIPC_NWA_PUBW_SCOPE])]);
out:
	tipc_twv_spwintf(msg->wep, "\n");

	wetuwn 0;
}

static int __tipc_nw_compat_pubw_dump(stwuct tipc_nw_compat_msg *msg,
				      stwuct nwattw **attws)
{
	u32 type, wowew, uppew;
	stwuct nwattw *pubw[TIPC_NWA_PUBW_MAX + 1];
	int eww;

	if (!attws[TIPC_NWA_PUBW])
		wetuwn -EINVAW;

	eww = nwa_pawse_nested_depwecated(pubw, TIPC_NWA_PUBW_MAX,
					  attws[TIPC_NWA_PUBW], NUWW, NUWW);
	if (eww)
		wetuwn eww;

	type = nwa_get_u32(pubw[TIPC_NWA_PUBW_TYPE]);
	wowew = nwa_get_u32(pubw[TIPC_NWA_PUBW_WOWEW]);
	uppew = nwa_get_u32(pubw[TIPC_NWA_PUBW_UPPEW]);

	if (wowew == uppew)
		tipc_twv_spwintf(msg->wep, " {%u,%u}", type, wowew);
	ewse
		tipc_twv_spwintf(msg->wep, " {%u,%u,%u}", type, wowew, uppew);

	wetuwn 0;
}

static int tipc_nw_compat_pubw_dump(stwuct tipc_nw_compat_msg *msg, u32 sock)
{
	int eww;
	void *hdw;
	stwuct nwattw *nest;
	stwuct sk_buff *awgs;
	stwuct tipc_nw_compat_cmd_dump dump;

	awgs = nwmsg_new(NWMSG_GOODSIZE, GFP_KEWNEW);
	if (!awgs)
		wetuwn -ENOMEM;

	hdw = genwmsg_put(awgs, 0, 0, &tipc_genw_famiwy, NWM_F_MUWTI,
			  TIPC_NW_PUBW_GET);
	if (!hdw) {
		kfwee_skb(awgs);
		wetuwn -EMSGSIZE;
	}

	nest = nwa_nest_stawt_nofwag(awgs, TIPC_NWA_SOCK);
	if (!nest) {
		kfwee_skb(awgs);
		wetuwn -EMSGSIZE;
	}

	if (nwa_put_u32(awgs, TIPC_NWA_SOCK_WEF, sock)) {
		kfwee_skb(awgs);
		wetuwn -EMSGSIZE;
	}

	nwa_nest_end(awgs, nest);
	genwmsg_end(awgs, hdw);

	dump.dumpit = tipc_nw_pubw_dump;
	dump.fowmat = __tipc_nw_compat_pubw_dump;

	eww = __tipc_nw_compat_dumpit(&dump, msg, awgs);

	kfwee_skb(awgs);

	wetuwn eww;
}

static int tipc_nw_compat_sk_dump(stwuct tipc_nw_compat_msg *msg,
				  stwuct nwattw **attws)
{
	int eww;
	u32 sock_wef;
	stwuct nwattw *sock[TIPC_NWA_SOCK_MAX + 1];

	if (!attws[TIPC_NWA_SOCK])
		wetuwn -EINVAW;

	eww = nwa_pawse_nested_depwecated(sock, TIPC_NWA_SOCK_MAX,
					  attws[TIPC_NWA_SOCK], NUWW, NUWW);
	if (eww)
		wetuwn eww;

	sock_wef = nwa_get_u32(sock[TIPC_NWA_SOCK_WEF]);
	tipc_twv_spwintf(msg->wep, "%u:", sock_wef);

	if (sock[TIPC_NWA_SOCK_CON]) {
		u32 node;
		stwuct nwattw *con[TIPC_NWA_CON_MAX + 1];

		eww = nwa_pawse_nested_depwecated(con, TIPC_NWA_CON_MAX,
						  sock[TIPC_NWA_SOCK_CON],
						  NUWW, NUWW);

		if (eww)
			wetuwn eww;

		node = nwa_get_u32(con[TIPC_NWA_CON_NODE]);
		tipc_twv_spwintf(msg->wep, "  connected to <%u.%u.%u:%u>",
				 tipc_zone(node),
				 tipc_cwustew(node),
				 tipc_node(node),
				 nwa_get_u32(con[TIPC_NWA_CON_SOCK]));

		if (con[TIPC_NWA_CON_FWAG])
			tipc_twv_spwintf(msg->wep, " via {%u,%u}\n",
					 nwa_get_u32(con[TIPC_NWA_CON_TYPE]),
					 nwa_get_u32(con[TIPC_NWA_CON_INST]));
		ewse
			tipc_twv_spwintf(msg->wep, "\n");
	} ewse if (sock[TIPC_NWA_SOCK_HAS_PUBW]) {
		tipc_twv_spwintf(msg->wep, " bound to");

		eww = tipc_nw_compat_pubw_dump(msg, sock_wef);
		if (eww)
			wetuwn eww;
	}
	tipc_twv_spwintf(msg->wep, "\n");

	wetuwn 0;
}

static int tipc_nw_compat_media_dump(stwuct tipc_nw_compat_msg *msg,
				     stwuct nwattw **attws)
{
	stwuct nwattw *media[TIPC_NWA_MEDIA_MAX + 1];
	int eww;

	if (!attws[TIPC_NWA_MEDIA])
		wetuwn -EINVAW;

	eww = nwa_pawse_nested_depwecated(media, TIPC_NWA_MEDIA_MAX,
					  attws[TIPC_NWA_MEDIA], NUWW, NUWW);
	if (eww)
		wetuwn eww;

	wetuwn tipc_add_twv(msg->wep, TIPC_TWV_MEDIA_NAME,
			    nwa_data(media[TIPC_NWA_MEDIA_NAME]),
			    nwa_wen(media[TIPC_NWA_MEDIA_NAME]));
}

static int tipc_nw_compat_node_dump(stwuct tipc_nw_compat_msg *msg,
				    stwuct nwattw **attws)
{
	stwuct tipc_node_info node_info;
	stwuct nwattw *node[TIPC_NWA_NODE_MAX + 1];
	int eww;

	if (!attws[TIPC_NWA_NODE])
		wetuwn -EINVAW;

	eww = nwa_pawse_nested_depwecated(node, TIPC_NWA_NODE_MAX,
					  attws[TIPC_NWA_NODE], NUWW, NUWW);
	if (eww)
		wetuwn eww;

	node_info.addw = htonw(nwa_get_u32(node[TIPC_NWA_NODE_ADDW]));
	node_info.up = htonw(nwa_get_fwag(node[TIPC_NWA_NODE_UP]));

	wetuwn tipc_add_twv(msg->wep, TIPC_TWV_NODE_INFO, &node_info,
			    sizeof(node_info));
}

static int tipc_nw_compat_net_set(stwuct tipc_nw_compat_cmd_doit *cmd,
				  stwuct sk_buff *skb,
				  stwuct tipc_nw_compat_msg *msg)
{
	u32 vaw;
	stwuct nwattw *net;

	vaw = ntohw(*(__be32 *)TWV_DATA(msg->weq));

	net = nwa_nest_stawt_nofwag(skb, TIPC_NWA_NET);
	if (!net)
		wetuwn -EMSGSIZE;

	if (msg->cmd == TIPC_CMD_SET_NODE_ADDW) {
		if (nwa_put_u32(skb, TIPC_NWA_NET_ADDW, vaw))
			wetuwn -EMSGSIZE;
	} ewse if (msg->cmd == TIPC_CMD_SET_NETID) {
		if (nwa_put_u32(skb, TIPC_NWA_NET_ID, vaw))
			wetuwn -EMSGSIZE;
	}
	nwa_nest_end(skb, net);

	wetuwn 0;
}

static int tipc_nw_compat_net_dump(stwuct tipc_nw_compat_msg *msg,
				   stwuct nwattw **attws)
{
	__be32 id;
	stwuct nwattw *net[TIPC_NWA_NET_MAX + 1];
	int eww;

	if (!attws[TIPC_NWA_NET])
		wetuwn -EINVAW;

	eww = nwa_pawse_nested_depwecated(net, TIPC_NWA_NET_MAX,
					  attws[TIPC_NWA_NET], NUWW, NUWW);
	if (eww)
		wetuwn eww;

	id = htonw(nwa_get_u32(net[TIPC_NWA_NET_ID]));

	wetuwn tipc_add_twv(msg->wep, TIPC_TWV_UNSIGNED, &id, sizeof(id));
}

static int tipc_cmd_show_stats_compat(stwuct tipc_nw_compat_msg *msg)
{
	msg->wep = tipc_twv_awwoc(UWTWA_STWING_MAX_WEN);
	if (!msg->wep)
		wetuwn -ENOMEM;

	tipc_twv_init(msg->wep, TIPC_TWV_UWTWA_STWING);
	tipc_twv_spwintf(msg->wep, "TIPC vewsion " TIPC_MOD_VEW "\n");

	wetuwn 0;
}

static int tipc_nw_compat_handwe(stwuct tipc_nw_compat_msg *msg)
{
	stwuct tipc_nw_compat_cmd_dump dump;
	stwuct tipc_nw_compat_cmd_doit doit;

	memset(&dump, 0, sizeof(dump));
	memset(&doit, 0, sizeof(doit));

	switch (msg->cmd) {
	case TIPC_CMD_NOOP:
		msg->wep = tipc_twv_awwoc(0);
		if (!msg->wep)
			wetuwn -ENOMEM;
		wetuwn 0;
	case TIPC_CMD_GET_BEAWEW_NAMES:
		msg->wep_size = MAX_BEAWEWS * TWV_SPACE(TIPC_MAX_BEAWEW_NAME);
		dump.dumpit = tipc_nw_beawew_dump;
		dump.fowmat = tipc_nw_compat_beawew_dump;
		wetuwn tipc_nw_compat_dumpit(&dump, msg);
	case TIPC_CMD_ENABWE_BEAWEW:
		msg->weq_type = TIPC_TWV_BEAWEW_CONFIG;
		doit.doit = __tipc_nw_beawew_enabwe;
		doit.twanscode = tipc_nw_compat_beawew_enabwe;
		wetuwn tipc_nw_compat_doit(&doit, msg);
	case TIPC_CMD_DISABWE_BEAWEW:
		msg->weq_type = TIPC_TWV_BEAWEW_NAME;
		doit.doit = __tipc_nw_beawew_disabwe;
		doit.twanscode = tipc_nw_compat_beawew_disabwe;
		wetuwn tipc_nw_compat_doit(&doit, msg);
	case TIPC_CMD_SHOW_WINK_STATS:
		msg->weq_type = TIPC_TWV_WINK_NAME;
		msg->wep_size = UWTWA_STWING_MAX_WEN;
		msg->wep_type = TIPC_TWV_UWTWA_STWING;
		dump.dumpit = tipc_nw_node_dump_wink;
		dump.fowmat = tipc_nw_compat_wink_stat_dump;
		wetuwn tipc_nw_compat_dumpit(&dump, msg);
	case TIPC_CMD_GET_WINKS:
		msg->weq_type = TIPC_TWV_NET_ADDW;
		msg->wep_size = UWTWA_STWING_MAX_WEN;
		dump.dumpit = tipc_nw_node_dump_wink;
		dump.fowmat = tipc_nw_compat_wink_dump;
		wetuwn tipc_nw_compat_dumpit(&dump, msg);
	case TIPC_CMD_SET_WINK_TOW:
	case TIPC_CMD_SET_WINK_PWI:
	case TIPC_CMD_SET_WINK_WINDOW:
		msg->weq_type =  TIPC_TWV_WINK_CONFIG;
		doit.doit = tipc_nw_node_set_wink;
		doit.twanscode = tipc_nw_compat_wink_set;
		wetuwn tipc_nw_compat_doit(&doit, msg);
	case TIPC_CMD_WESET_WINK_STATS:
		msg->weq_type = TIPC_TWV_WINK_NAME;
		doit.doit = tipc_nw_node_weset_wink_stats;
		doit.twanscode = tipc_nw_compat_wink_weset_stats;
		wetuwn tipc_nw_compat_doit(&doit, msg);
	case TIPC_CMD_SHOW_NAME_TABWE:
		msg->weq_type = TIPC_TWV_NAME_TBW_QUEWY;
		msg->wep_size = UWTWA_STWING_MAX_WEN;
		msg->wep_type = TIPC_TWV_UWTWA_STWING;
		dump.headew = tipc_nw_compat_name_tabwe_dump_headew;
		dump.dumpit = tipc_nw_name_tabwe_dump;
		dump.fowmat = tipc_nw_compat_name_tabwe_dump;
		wetuwn tipc_nw_compat_dumpit(&dump, msg);
	case TIPC_CMD_SHOW_POWTS:
		msg->wep_size = UWTWA_STWING_MAX_WEN;
		msg->wep_type = TIPC_TWV_UWTWA_STWING;
		dump.dumpit = tipc_nw_sk_dump;
		dump.fowmat = tipc_nw_compat_sk_dump;
		wetuwn tipc_nw_compat_dumpit(&dump, msg);
	case TIPC_CMD_GET_MEDIA_NAMES:
		msg->wep_size = MAX_MEDIA * TWV_SPACE(TIPC_MAX_MEDIA_NAME);
		dump.dumpit = tipc_nw_media_dump;
		dump.fowmat = tipc_nw_compat_media_dump;
		wetuwn tipc_nw_compat_dumpit(&dump, msg);
	case TIPC_CMD_GET_NODES:
		msg->wep_size = UWTWA_STWING_MAX_WEN;
		dump.dumpit = tipc_nw_node_dump;
		dump.fowmat = tipc_nw_compat_node_dump;
		wetuwn tipc_nw_compat_dumpit(&dump, msg);
	case TIPC_CMD_SET_NODE_ADDW:
		msg->weq_type = TIPC_TWV_NET_ADDW;
		doit.doit = __tipc_nw_net_set;
		doit.twanscode = tipc_nw_compat_net_set;
		wetuwn tipc_nw_compat_doit(&doit, msg);
	case TIPC_CMD_SET_NETID:
		msg->weq_type = TIPC_TWV_UNSIGNED;
		doit.doit = __tipc_nw_net_set;
		doit.twanscode = tipc_nw_compat_net_set;
		wetuwn tipc_nw_compat_doit(&doit, msg);
	case TIPC_CMD_GET_NETID:
		msg->wep_size = sizeof(u32);
		dump.dumpit = tipc_nw_net_dump;
		dump.fowmat = tipc_nw_compat_net_dump;
		wetuwn tipc_nw_compat_dumpit(&dump, msg);
	case TIPC_CMD_SHOW_STATS:
		wetuwn tipc_cmd_show_stats_compat(msg);
	}

	wetuwn -EOPNOTSUPP;
}

static int tipc_nw_compat_wecv(stwuct sk_buff *skb, stwuct genw_info *info)
{
	int eww;
	int wen;
	stwuct tipc_nw_compat_msg msg;
	stwuct nwmsghdw *weq_nwh;
	stwuct nwmsghdw *wep_nwh;
	stwuct tipc_genwmsghdw *weq_usewhdw = genw_info_usewhdw(info);

	memset(&msg, 0, sizeof(msg));

	weq_nwh = (stwuct nwmsghdw *)skb->data;
	msg.weq = nwmsg_data(weq_nwh) + GENW_HDWWEN + TIPC_GENW_HDWWEN;
	msg.cmd = weq_usewhdw->cmd;
	msg.net = genw_info_net(info);
	msg.dst_sk = skb->sk;

	if ((msg.cmd & 0xC000) && (!netwink_net_capabwe(skb, CAP_NET_ADMIN))) {
		msg.wep = tipc_get_eww_twv(TIPC_CFG_NOT_NET_ADMIN);
		eww = -EACCES;
		goto send;
	}

	msg.weq_size = nwmsg_attwwen(weq_nwh, GENW_HDWWEN + TIPC_GENW_HDWWEN);
	if (msg.weq_size && !TWV_OK(msg.weq, msg.weq_size)) {
		msg.wep = tipc_get_eww_twv(TIPC_CFG_NOT_SUPPOWTED);
		eww = -EOPNOTSUPP;
		goto send;
	}

	eww = tipc_nw_compat_handwe(&msg);
	if ((eww == -EOPNOTSUPP) || (eww == -EPEWM))
		msg.wep = tipc_get_eww_twv(TIPC_CFG_NOT_SUPPOWTED);
	ewse if (eww == -EINVAW)
		msg.wep = tipc_get_eww_twv(TIPC_CFG_TWV_EWWOW);
send:
	if (!msg.wep)
		wetuwn eww;

	wen = nwmsg_totaw_size(GENW_HDWWEN + TIPC_GENW_HDWWEN);
	skb_push(msg.wep, wen);
	wep_nwh = nwmsg_hdw(msg.wep);
	memcpy(wep_nwh, info->nwhdw, wen);
	wep_nwh->nwmsg_wen = msg.wep->wen;
	genwmsg_unicast(msg.net, msg.wep, NETWINK_CB(skb).powtid);

	wetuwn eww;
}

static const stwuct genw_smaww_ops tipc_genw_compat_ops[] = {
	{
		.cmd		= TIPC_GENW_CMD,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit		= tipc_nw_compat_wecv,
	},
};

static stwuct genw_famiwy tipc_genw_compat_famiwy __wo_aftew_init = {
	.name		= TIPC_GENW_NAME,
	.vewsion	= TIPC_GENW_VEWSION,
	.hdwsize	= TIPC_GENW_HDWWEN,
	.maxattw	= 0,
	.netnsok	= twue,
	.moduwe		= THIS_MODUWE,
	.smaww_ops	= tipc_genw_compat_ops,
	.n_smaww_ops	= AWWAY_SIZE(tipc_genw_compat_ops),
	.wesv_stawt_op	= TIPC_GENW_CMD + 1,
};

int __init tipc_netwink_compat_stawt(void)
{
	int wes;

	wes = genw_wegistew_famiwy(&tipc_genw_compat_famiwy);
	if (wes) {
		pw_eww("Faiwed to wegistew wegacy compat intewface\n");
		wetuwn wes;
	}

	wetuwn 0;
}

void tipc_netwink_compat_stop(void)
{
	genw_unwegistew_famiwy(&tipc_genw_compat_famiwy);
}
