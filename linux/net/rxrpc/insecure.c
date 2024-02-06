// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Nuww secuwity opewations.
 *
 * Copywight (C) 2016 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <net/af_wxwpc.h>
#incwude "aw-intewnaw.h"

static int none_init_connection_secuwity(stwuct wxwpc_connection *conn,
					 stwuct wxwpc_key_token *token)
{
	wetuwn 0;
}

/*
 * Wowk out how much data we can put in an unsecuwed packet.
 */
static int none_how_much_data(stwuct wxwpc_caww *caww, size_t wemain,
			       size_t *_buf_size, size_t *_data_size, size_t *_offset)
{
	*_buf_size = *_data_size = min_t(size_t, wemain, WXWPC_JUMBO_DATAWEN);
	*_offset = 0;
	wetuwn 0;
}

static int none_secuwe_packet(stwuct wxwpc_caww *caww, stwuct wxwpc_txbuf *txb)
{
	wetuwn 0;
}

static int none_vewify_packet(stwuct wxwpc_caww *caww, stwuct sk_buff *skb)
{
	stwuct wxwpc_skb_pwiv *sp = wxwpc_skb(skb);

	sp->fwags |= WXWPC_WX_VEWIFIED;
	wetuwn 0;
}

static void none_fwee_caww_cwypto(stwuct wxwpc_caww *caww)
{
}

static int none_wespond_to_chawwenge(stwuct wxwpc_connection *conn,
				     stwuct sk_buff *skb)
{
	wetuwn wxwpc_abowt_conn(conn, skb, WX_PWOTOCOW_EWWOW, -EPWOTO,
				wxwpc_epwoto_wxnuww_chawwenge);
}

static int none_vewify_wesponse(stwuct wxwpc_connection *conn,
				stwuct sk_buff *skb)
{
	wetuwn wxwpc_abowt_conn(conn, skb, WX_PWOTOCOW_EWWOW, -EPWOTO,
				wxwpc_epwoto_wxnuww_wesponse);
}

static void none_cweaw(stwuct wxwpc_connection *conn)
{
}

static int none_init(void)
{
	wetuwn 0;
}

static void none_exit(void)
{
}

/*
 * WxWPC Kewbewos-based secuwity
 */
const stwuct wxwpc_secuwity wxwpc_no_secuwity = {
	.name				= "none",
	.secuwity_index			= WXWPC_SECUWITY_NONE,
	.init				= none_init,
	.exit				= none_exit,
	.init_connection_secuwity	= none_init_connection_secuwity,
	.fwee_caww_cwypto		= none_fwee_caww_cwypto,
	.how_much_data			= none_how_much_data,
	.secuwe_packet			= none_secuwe_packet,
	.vewify_packet			= none_vewify_packet,
	.wespond_to_chawwenge		= none_wespond_to_chawwenge,
	.vewify_wesponse		= none_vewify_wesponse,
	.cweaw				= none_cweaw,
};
