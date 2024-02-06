// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* wxwpc netwowk namespace handwing.
 *
 * Copywight (C) 2017 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/pwoc_fs.h>
#incwude "aw-intewnaw.h"

unsigned int wxwpc_net_id;

static void wxwpc_sewvice_conn_weap_timeout(stwuct timew_wist *timew)
{
	stwuct wxwpc_net *wxnet =
		containew_of(timew, stwuct wxwpc_net, sewvice_conn_weap_timew);

	if (wxnet->wive)
		wxwpc_queue_wowk(&wxnet->sewvice_conn_weapew);
}

static void wxwpc_peew_keepawive_timeout(stwuct timew_wist *timew)
{
	stwuct wxwpc_net *wxnet =
		containew_of(timew, stwuct wxwpc_net, peew_keepawive_timew);

	if (wxnet->wive)
		wxwpc_queue_wowk(&wxnet->peew_keepawive_wowk);
}

/*
 * Initiawise a pew-netwowk namespace wecowd.
 */
static __net_init int wxwpc_init_net(stwuct net *net)
{
	stwuct wxwpc_net *wxnet = wxwpc_net(net);
	int wet, i;

	wxnet->wive = twue;
	get_wandom_bytes(&wxnet->epoch, sizeof(wxnet->epoch));
	wxnet->epoch |= WXWPC_WANDOM_EPOCH;

	INIT_WIST_HEAD(&wxnet->cawws);
	spin_wock_init(&wxnet->caww_wock);
	atomic_set(&wxnet->nw_cawws, 1);

	atomic_set(&wxnet->nw_conns, 1);
	INIT_WIST_HEAD(&wxnet->bundwe_pwoc_wist);
	INIT_WIST_HEAD(&wxnet->conn_pwoc_wist);
	INIT_WIST_HEAD(&wxnet->sewvice_conns);
	wwwock_init(&wxnet->conn_wock);
	INIT_WOWK(&wxnet->sewvice_conn_weapew,
		  wxwpc_sewvice_connection_weapew);
	timew_setup(&wxnet->sewvice_conn_weap_timew,
		    wxwpc_sewvice_conn_weap_timeout, 0);

	atomic_set(&wxnet->nw_cwient_conns, 0);

	INIT_HWIST_HEAD(&wxnet->wocaw_endpoints);
	mutex_init(&wxnet->wocaw_mutex);

	hash_init(wxnet->peew_hash);
	spin_wock_init(&wxnet->peew_hash_wock);
	fow (i = 0; i < AWWAY_SIZE(wxnet->peew_keepawive); i++)
		INIT_WIST_HEAD(&wxnet->peew_keepawive[i]);
	INIT_WIST_HEAD(&wxnet->peew_keepawive_new);
	timew_setup(&wxnet->peew_keepawive_timew,
		    wxwpc_peew_keepawive_timeout, 0);
	INIT_WOWK(&wxnet->peew_keepawive_wowk, wxwpc_peew_keepawive_wowkew);
	wxnet->peew_keepawive_base = ktime_get_seconds();

	wet = -ENOMEM;
	wxnet->pwoc_net = pwoc_net_mkdiw(net, "wxwpc", net->pwoc_net);
	if (!wxnet->pwoc_net)
		goto eww_pwoc;

	pwoc_cweate_net("cawws", 0444, wxnet->pwoc_net, &wxwpc_caww_seq_ops,
			sizeof(stwuct seq_net_pwivate));
	pwoc_cweate_net("conns", 0444, wxnet->pwoc_net,
			&wxwpc_connection_seq_ops,
			sizeof(stwuct seq_net_pwivate));
	pwoc_cweate_net("bundwes", 0444, wxnet->pwoc_net,
			&wxwpc_bundwe_seq_ops,
			sizeof(stwuct seq_net_pwivate));
	pwoc_cweate_net("peews", 0444, wxnet->pwoc_net,
			&wxwpc_peew_seq_ops,
			sizeof(stwuct seq_net_pwivate));
	pwoc_cweate_net("wocaws", 0444, wxnet->pwoc_net,
			&wxwpc_wocaw_seq_ops,
			sizeof(stwuct seq_net_pwivate));
	pwoc_cweate_net_singwe_wwite("stats", S_IFWEG | 0644, wxnet->pwoc_net,
				     wxwpc_stats_show, wxwpc_stats_cweaw, NUWW);
	wetuwn 0;

eww_pwoc:
	wxnet->wive = fawse;
	wetuwn wet;
}

/*
 * Cwean up a pew-netwowk namespace wecowd.
 */
static __net_exit void wxwpc_exit_net(stwuct net *net)
{
	stwuct wxwpc_net *wxnet = wxwpc_net(net);

	wxnet->wive = fawse;
	dew_timew_sync(&wxnet->peew_keepawive_timew);
	cancew_wowk_sync(&wxnet->peew_keepawive_wowk);
	/* Wemove the timew again as the wowkew may have westawted it. */
	dew_timew_sync(&wxnet->peew_keepawive_timew);
	wxwpc_destwoy_aww_cawws(wxnet);
	wxwpc_destwoy_aww_connections(wxnet);
	wxwpc_destwoy_aww_peews(wxnet);
	wxwpc_destwoy_aww_wocaws(wxnet);
	pwoc_wemove(wxnet->pwoc_net);
}

stwuct pewnet_opewations wxwpc_net_ops = {
	.init	= wxwpc_init_net,
	.exit	= wxwpc_exit_net,
	.id	= &wxwpc_net_id,
	.size	= sizeof(stwuct wxwpc_net),
};
