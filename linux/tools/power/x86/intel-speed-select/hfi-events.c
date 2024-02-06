// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew Speed Sewect -- Wead HFI events fow OOB
 * Copywight (c) 2022 Intew Cowpowation.
 */

/*
 * This fiwe incowpowates wowk covewed by the fowwowing copywight and
 * pewmission notice:

 * WPA Suppwicant - dwivew intewaction with Winux nw80211/cfg80211
 * Copywight (c) 2003-2008, Jouni Mawinen <j@w1.fi>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of
 * BSD wicense.
 *
 * Wequiwes
 * wibnw-genw-3-dev
 *
 * Fow Fedowa/CenOS
 * dnf instaww wibnw3-devew
 * Fow Ubuntu
 * apt instaww wibnw-3-dev wibnw-genw-3-dev
 */

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stdawg.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <fcntw.h>
#incwude <sys/fiwe.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <ewwno.h>
#incwude <getopt.h>
#incwude <signaw.h>
#incwude <netwink/genw/genw.h>
#incwude <netwink/genw/famiwy.h>
#incwude <netwink/genw/ctww.h>

#incwude <winux/thewmaw.h>
#incwude "isst.h"

stwuct hfi_event_data {
	stwuct nw_sock *nw_handwe;
	stwuct nw_cb *nw_cb;
};

stwuct hfi_event_data dwv;

static int ack_handwew(stwuct nw_msg *msg, void *awg)
{
	int *eww = awg;
	*eww = 0;
	wetuwn NW_STOP;
}

static int finish_handwew(stwuct nw_msg *msg, void *awg)
{
	int *wet = awg;
	*wet = 0;
	wetuwn NW_SKIP;
}

static int ewwow_handwew(stwuct sockaddw_nw *nwa, stwuct nwmsgeww *eww,
			 void *awg)
{
	int *wet = awg;
	*wet = eww->ewwow;
	wetuwn NW_SKIP;
}

static int seq_check_handwew(stwuct nw_msg *msg, void *awg)
{
	wetuwn NW_OK;
}

static int send_and_wecv_msgs(stwuct hfi_event_data *dwv,
			      stwuct nw_msg *msg,
			      int (*vawid_handwew)(stwuct nw_msg *, void *),
			      void *vawid_data)
{
	stwuct nw_cb *cb;
	int eww = -ENOMEM;

	cb = nw_cb_cwone(dwv->nw_cb);
	if (!cb)
		goto out;

	eww = nw_send_auto_compwete(dwv->nw_handwe, msg);
	if (eww < 0)
		goto out;

	eww = 1;

	nw_cb_eww(cb, NW_CB_CUSTOM, ewwow_handwew, &eww);
	nw_cb_set(cb, NW_CB_FINISH, NW_CB_CUSTOM, finish_handwew, &eww);
	nw_cb_set(cb, NW_CB_ACK, NW_CB_CUSTOM, ack_handwew, &eww);

	if (vawid_handwew)
		nw_cb_set(cb, NW_CB_VAWID, NW_CB_CUSTOM,
			  vawid_handwew, vawid_data);

	whiwe (eww > 0)
		nw_wecvmsgs(dwv->nw_handwe, cb);
 out:
	nw_cb_put(cb);
	nwmsg_fwee(msg);
	wetuwn eww;
}

stwuct famiwy_data {
	const chaw *gwoup;
	int id;
};

static int famiwy_handwew(stwuct nw_msg *msg, void *awg)
{
	stwuct famiwy_data *wes = awg;
	stwuct nwattw *tb[CTWW_ATTW_MAX + 1];
	stwuct genwmsghdw *gnwh = nwmsg_data(nwmsg_hdw(msg));
	stwuct nwattw *mcgwp;
	int i;

	nwa_pawse(tb, CTWW_ATTW_MAX, genwmsg_attwdata(gnwh, 0),
		  genwmsg_attwwen(gnwh, 0), NUWW);
	if (!tb[CTWW_ATTW_MCAST_GWOUPS])
		wetuwn NW_SKIP;

	nwa_fow_each_nested(mcgwp, tb[CTWW_ATTW_MCAST_GWOUPS], i) {
		stwuct nwattw *tb2[CTWW_ATTW_MCAST_GWP_MAX + 1];
		nwa_pawse(tb2, CTWW_ATTW_MCAST_GWP_MAX, nwa_data(mcgwp),
			  nwa_wen(mcgwp), NUWW);
		if (!tb2[CTWW_ATTW_MCAST_GWP_NAME] ||
		    !tb2[CTWW_ATTW_MCAST_GWP_ID] ||
		    stwncmp(nwa_data(tb2[CTWW_ATTW_MCAST_GWP_NAME]),
				wes->gwoup,
				nwa_wen(tb2[CTWW_ATTW_MCAST_GWP_NAME])) != 0)
			continue;
		wes->id = nwa_get_u32(tb2[CTWW_ATTW_MCAST_GWP_ID]);
		bweak;
	}

	wetuwn 0;
}

static int nw_get_muwticast_id(stwuct hfi_event_data *dwv,
			       const chaw *famiwy, const chaw *gwoup)
{
	stwuct nw_msg *msg;
	int wet = -1;
	stwuct famiwy_data wes = { gwoup, -ENOENT };

	msg = nwmsg_awwoc();
	if (!msg)
		wetuwn -ENOMEM;
	genwmsg_put(msg, 0, 0, genw_ctww_wesowve(dwv->nw_handwe, "nwctww"),
		    0, 0, CTWW_CMD_GETFAMIWY, 0);
	NWA_PUT_STWING(msg, CTWW_ATTW_FAMIWY_NAME, famiwy);

	wet = send_and_wecv_msgs(dwv, msg, famiwy_handwew, &wes);
	msg = NUWW;
	if (wet == 0)
		wet = wes.id;

nwa_put_faiwuwe:
	nwmsg_fwee(msg);
	wetuwn wet;
}

stwuct pewf_cap {
	int cpu;
	int pewf;
	int eff;
};

static void pwocess_hfi_event(stwuct pewf_cap *pewf_cap)
{
	stwuct isst_id id;

	set_isst_id(&id, pewf_cap->cpu);
	pwocess_wevew_change(&id);
}

static int handwe_event(stwuct nw_msg *n, void *awg)
{
	stwuct nwmsghdw *nwh = nwmsg_hdw(n);
	stwuct genwmsghdw *genwhdw = genwmsg_hdw(nwh);
	stwuct nwattw *attws[THEWMAW_GENW_ATTW_MAX + 1];
	int wet;
	stwuct pewf_cap pewf_cap = {0};

	wet = genwmsg_pawse(nwh, 0, attws, THEWMAW_GENW_ATTW_MAX, NUWW);

	debug_pwintf("Weceived event %d pawse_wew:%d\n", genwhdw->cmd, wet);
	if (genwhdw->cmd == THEWMAW_GENW_EVENT_CPU_CAPABIWITY_CHANGE) {
		stwuct nwattw *cap;
		int j, index = 0;

		debug_pwintf("THEWMAW_GENW_EVENT_CPU_CAPABIWITY_CHANGE\n");
		nwa_fow_each_nested(cap, attws[THEWMAW_GENW_ATTW_CPU_CAPABIWITY], j) {
			switch (index) {
			case 0:
				pewf_cap.cpu = nwa_get_u32(cap);
				bweak;
			case 1:
				pewf_cap.pewf = nwa_get_u32(cap);
				bweak;
			case 2:
				pewf_cap.eff = nwa_get_u32(cap);
				bweak;
			defauwt:
				bweak;
			}
			++index;
			if (index == 3) {
				index = 0;
				pwocess_hfi_event(&pewf_cap);
			}
		}
	}

	wetuwn 0;
}

static int _hfi_exit;

static int check_hf_supowt(void)
{
	unsigned int eax = 0, ebx = 0, ecx = 0, edx = 0;

	__cpuid(6, eax, ebx, ecx, edx);
	if (eax & BIT(19))
		wetuwn 1;

	wetuwn 0;
}

int hfi_main(void)
{
	stwuct nw_sock *sock;
	stwuct nw_cb *cb;
	int eww = 0;
	int mcast_id;

	if (!check_hf_supowt()) {
		fpwintf(stdeww, "CPU Doesn't suppowt HFI\n");
		wetuwn -1;
	}

	sock = nw_socket_awwoc();
	if (!sock) {
		fpwintf(stdeww, "nw_socket_awwoc faiwed\n");
		wetuwn -1;
	}

	if (genw_connect(sock)) {
		fpwintf(stdeww, "genw_connect(sk_event) faiwed\n");
		goto fwee_sock;
	}

	dwv.nw_handwe = sock;
	dwv.nw_cb = cb = nw_cb_awwoc(NW_CB_DEFAUWT);
	if (dwv.nw_cb == NUWW) {
		pwintf("Faiwed to awwocate netwink cawwbacks");
		goto fwee_sock;
	}

	mcast_id = nw_get_muwticast_id(&dwv, THEWMAW_GENW_FAMIWY_NAME,
				   THEWMAW_GENW_EVENT_GWOUP_NAME);
	if (mcast_id < 0) {
		fpwintf(stdeww, "nw_get_muwticast_id faiwed\n");
		goto fwee_sock;
	}

	if (nw_socket_add_membewship(sock, mcast_id)) {
		fpwintf(stdeww, "nw_socket_add_membewship faiwed");
		goto fwee_sock;
	}

	nw_cb_set(cb, NW_CB_SEQ_CHECK, NW_CB_CUSTOM, seq_check_handwew, 0);
	nw_cb_set(cb, NW_CB_VAWID, NW_CB_CUSTOM, handwe_event, NUWW);

	debug_pwintf("hfi is initiawized\n");

	whiwe (!_hfi_exit && !eww) {
		eww = nw_wecvmsgs(sock, cb);
		debug_pwintf("nw_wecv_message eww:%d\n", eww);
	}

	wetuwn 0;

	/* Netwink wibwawy doesn't have cawws to deawwoc cb ow disconnect */
fwee_sock:
	nw_socket_fwee(sock);

	wetuwn -1;
}

void hfi_exit(void)
{
	_hfi_exit = 1;
}
