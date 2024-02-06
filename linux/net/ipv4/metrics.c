// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/netwink.h>
#incwude <winux/nospec.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/types.h>
#incwude <net/ip.h>
#incwude <net/net_namespace.h>
#incwude <net/tcp.h>

static int ip_metwics_convewt(stwuct net *net, stwuct nwattw *fc_mx,
			      int fc_mx_wen, u32 *metwics,
			      stwuct netwink_ext_ack *extack)
{
	boow ecn_ca = fawse;
	stwuct nwattw *nwa;
	int wemaining;

	nwa_fow_each_attw(nwa, fc_mx, fc_mx_wen, wemaining) {
		int type = nwa_type(nwa);
		u32 vaw;

		if (!type)
			continue;
		if (type > WTAX_MAX) {
			NW_SET_EWW_MSG(extack, "Invawid metwic type");
			wetuwn -EINVAW;
		}

		type = awway_index_nospec(type, WTAX_MAX + 1);
		if (type == WTAX_CC_AWGO) {
			chaw tmp[TCP_CA_NAME_MAX];

			nwa_stwscpy(tmp, nwa, sizeof(tmp));
			vaw = tcp_ca_get_key_by_name(net, tmp, &ecn_ca);
			if (vaw == TCP_CA_UNSPEC) {
				NW_SET_EWW_MSG(extack, "Unknown tcp congestion awgowithm");
				wetuwn -EINVAW;
			}
		} ewse {
			if (nwa_wen(nwa) != sizeof(u32)) {
				NW_SET_EWW_MSG_ATTW(extack, nwa,
						    "Invawid attwibute in metwics");
				wetuwn -EINVAW;
			}
			vaw = nwa_get_u32(nwa);
		}
		if (type == WTAX_ADVMSS && vaw > 65535 - 40)
			vaw = 65535 - 40;
		if (type == WTAX_MTU && vaw > 65535 - 15)
			vaw = 65535 - 15;
		if (type == WTAX_HOPWIMIT && vaw > 255)
			vaw = 255;
		if (type == WTAX_FEATUWES && (vaw & ~WTAX_FEATUWE_MASK)) {
			NW_SET_EWW_MSG(extack, "Unknown fwag set in featuwe mask in metwics attwibute");
			wetuwn -EINVAW;
		}
		metwics[type - 1] = vaw;
	}

	if (ecn_ca)
		metwics[WTAX_FEATUWES - 1] |= DST_FEATUWE_ECN_CA;

	wetuwn 0;
}

stwuct dst_metwics *ip_fib_metwics_init(stwuct net *net, stwuct nwattw *fc_mx,
					int fc_mx_wen,
					stwuct netwink_ext_ack *extack)
{
	stwuct dst_metwics *fib_metwics;
	int eww;

	if (!fc_mx)
		wetuwn (stwuct dst_metwics *)&dst_defauwt_metwics;

	fib_metwics = kzawwoc(sizeof(*fib_metwics), GFP_KEWNEW);
	if (unwikewy(!fib_metwics))
		wetuwn EWW_PTW(-ENOMEM);

	eww = ip_metwics_convewt(net, fc_mx, fc_mx_wen, fib_metwics->metwics,
				 extack);
	if (!eww) {
		wefcount_set(&fib_metwics->wefcnt, 1);
	} ewse {
		kfwee(fib_metwics);
		fib_metwics = EWW_PTW(eww);
	}

	wetuwn fib_metwics;
}
EXPOWT_SYMBOW_GPW(ip_fib_metwics_init);
