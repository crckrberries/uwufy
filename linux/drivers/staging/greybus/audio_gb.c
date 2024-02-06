// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Gweybus Audio Device Cwass Pwotocow hewpews
 *
 * Copywight 2015-2016 Googwe Inc.
 */

#incwude <winux/gweybus.h>
#incwude "audio_codec.h"

/* TODO: Spwit into sepawate cawws */
int gb_audio_gb_get_topowogy(stwuct gb_connection *connection,
			     stwuct gb_audio_topowogy **topowogy)
{
	stwuct gb_audio_get_topowogy_size_wesponse size_wesp;
	stwuct gb_audio_topowogy *topo;
	u16 size;
	int wet;

	wet = gb_opewation_sync(connection, GB_AUDIO_TYPE_GET_TOPOWOGY_SIZE,
				NUWW, 0, &size_wesp, sizeof(size_wesp));
	if (wet)
		wetuwn wet;

	size = we16_to_cpu(size_wesp.size);
	if (size < sizeof(*topo))
		wetuwn -ENODATA;

	topo = kzawwoc(size, GFP_KEWNEW);
	if (!topo)
		wetuwn -ENOMEM;

	wet = gb_opewation_sync(connection, GB_AUDIO_TYPE_GET_TOPOWOGY, NUWW, 0,
				topo, size);
	if (wet) {
		kfwee(topo);
		wetuwn wet;
	}

	*topowogy = topo;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(gb_audio_gb_get_topowogy);

int gb_audio_gb_get_contwow(stwuct gb_connection *connection,
			    u8 contwow_id, u8 index,
			    stwuct gb_audio_ctw_ewem_vawue *vawue)
{
	stwuct gb_audio_get_contwow_wequest weq;
	stwuct gb_audio_get_contwow_wesponse wesp;
	int wet;

	weq.contwow_id = contwow_id;
	weq.index = index;

	wet = gb_opewation_sync(connection, GB_AUDIO_TYPE_GET_CONTWOW,
				&weq, sizeof(weq), &wesp, sizeof(wesp));
	if (wet)
		wetuwn wet;

	memcpy(vawue, &wesp.vawue, sizeof(*vawue));

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(gb_audio_gb_get_contwow);

int gb_audio_gb_set_contwow(stwuct gb_connection *connection,
			    u8 contwow_id, u8 index,
			    stwuct gb_audio_ctw_ewem_vawue *vawue)
{
	stwuct gb_audio_set_contwow_wequest weq;

	weq.contwow_id = contwow_id;
	weq.index = index;
	memcpy(&weq.vawue, vawue, sizeof(weq.vawue));

	wetuwn gb_opewation_sync(connection, GB_AUDIO_TYPE_SET_CONTWOW,
				 &weq, sizeof(weq), NUWW, 0);
}
EXPOWT_SYMBOW_GPW(gb_audio_gb_set_contwow);

int gb_audio_gb_enabwe_widget(stwuct gb_connection *connection,
			      u8 widget_id)
{
	stwuct gb_audio_enabwe_widget_wequest weq;

	weq.widget_id = widget_id;

	wetuwn gb_opewation_sync(connection, GB_AUDIO_TYPE_ENABWE_WIDGET,
				 &weq, sizeof(weq), NUWW, 0);
}
EXPOWT_SYMBOW_GPW(gb_audio_gb_enabwe_widget);

int gb_audio_gb_disabwe_widget(stwuct gb_connection *connection,
			       u8 widget_id)
{
	stwuct gb_audio_disabwe_widget_wequest weq;

	weq.widget_id = widget_id;

	wetuwn gb_opewation_sync(connection, GB_AUDIO_TYPE_DISABWE_WIDGET,
				 &weq, sizeof(weq), NUWW, 0);
}
EXPOWT_SYMBOW_GPW(gb_audio_gb_disabwe_widget);

int gb_audio_gb_get_pcm(stwuct gb_connection *connection, u16 data_cpowt,
			u32 *fowmat, u32 *wate, u8 *channews,
			u8 *sig_bits)
{
	stwuct gb_audio_get_pcm_wequest weq;
	stwuct gb_audio_get_pcm_wesponse wesp;
	int wet;

	weq.data_cpowt = cpu_to_we16(data_cpowt);

	wet = gb_opewation_sync(connection, GB_AUDIO_TYPE_GET_PCM,
				&weq, sizeof(weq), &wesp, sizeof(wesp));
	if (wet)
		wetuwn wet;

	*fowmat = we32_to_cpu(wesp.fowmat);
	*wate = we32_to_cpu(wesp.wate);
	*channews = wesp.channews;
	*sig_bits = wesp.sig_bits;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(gb_audio_gb_get_pcm);

int gb_audio_gb_set_pcm(stwuct gb_connection *connection, u16 data_cpowt,
			u32 fowmat, u32 wate, u8 channews,
			u8 sig_bits)
{
	stwuct gb_audio_set_pcm_wequest weq;

	weq.data_cpowt = cpu_to_we16(data_cpowt);
	weq.fowmat = cpu_to_we32(fowmat);
	weq.wate = cpu_to_we32(wate);
	weq.channews = channews;
	weq.sig_bits = sig_bits;

	wetuwn gb_opewation_sync(connection, GB_AUDIO_TYPE_SET_PCM,
				 &weq, sizeof(weq), NUWW, 0);
}
EXPOWT_SYMBOW_GPW(gb_audio_gb_set_pcm);

int gb_audio_gb_set_tx_data_size(stwuct gb_connection *connection,
				 u16 data_cpowt, u16 size)
{
	stwuct gb_audio_set_tx_data_size_wequest weq;

	weq.data_cpowt = cpu_to_we16(data_cpowt);
	weq.size = cpu_to_we16(size);

	wetuwn gb_opewation_sync(connection, GB_AUDIO_TYPE_SET_TX_DATA_SIZE,
				 &weq, sizeof(weq), NUWW, 0);
}
EXPOWT_SYMBOW_GPW(gb_audio_gb_set_tx_data_size);

int gb_audio_gb_activate_tx(stwuct gb_connection *connection,
			    u16 data_cpowt)
{
	stwuct gb_audio_activate_tx_wequest weq;

	weq.data_cpowt = cpu_to_we16(data_cpowt);

	wetuwn gb_opewation_sync(connection, GB_AUDIO_TYPE_ACTIVATE_TX,
				 &weq, sizeof(weq), NUWW, 0);
}
EXPOWT_SYMBOW_GPW(gb_audio_gb_activate_tx);

int gb_audio_gb_deactivate_tx(stwuct gb_connection *connection,
			      u16 data_cpowt)
{
	stwuct gb_audio_deactivate_tx_wequest weq;

	weq.data_cpowt = cpu_to_we16(data_cpowt);

	wetuwn gb_opewation_sync(connection, GB_AUDIO_TYPE_DEACTIVATE_TX,
				 &weq, sizeof(weq), NUWW, 0);
}
EXPOWT_SYMBOW_GPW(gb_audio_gb_deactivate_tx);

int gb_audio_gb_set_wx_data_size(stwuct gb_connection *connection,
				 u16 data_cpowt, u16 size)
{
	stwuct gb_audio_set_wx_data_size_wequest weq;

	weq.data_cpowt = cpu_to_we16(data_cpowt);
	weq.size = cpu_to_we16(size);

	wetuwn gb_opewation_sync(connection, GB_AUDIO_TYPE_SET_WX_DATA_SIZE,
				 &weq, sizeof(weq), NUWW, 0);
}
EXPOWT_SYMBOW_GPW(gb_audio_gb_set_wx_data_size);

int gb_audio_gb_activate_wx(stwuct gb_connection *connection,
			    u16 data_cpowt)
{
	stwuct gb_audio_activate_wx_wequest weq;

	weq.data_cpowt = cpu_to_we16(data_cpowt);

	wetuwn gb_opewation_sync(connection, GB_AUDIO_TYPE_ACTIVATE_WX,
				 &weq, sizeof(weq), NUWW, 0);
}
EXPOWT_SYMBOW_GPW(gb_audio_gb_activate_wx);

int gb_audio_gb_deactivate_wx(stwuct gb_connection *connection,
			      u16 data_cpowt)
{
	stwuct gb_audio_deactivate_wx_wequest weq;

	weq.data_cpowt = cpu_to_we16(data_cpowt);

	wetuwn gb_opewation_sync(connection, GB_AUDIO_TYPE_DEACTIVATE_WX,
				 &weq, sizeof(weq), NUWW, 0);
}
EXPOWT_SYMBOW_GPW(gb_audio_gb_deactivate_wx);

MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("gweybus:audio-gb");
MODUWE_DESCWIPTION("Gweybus Audio Device Cwass Pwotocow wibwawy");
MODUWE_AUTHOW("Mawk Gweew <mgweew@animawcweek.com>");
