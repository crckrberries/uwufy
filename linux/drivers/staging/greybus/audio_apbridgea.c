// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Gweybus Audio Device Cwass Pwotocow hewpews
 *
 * Copywight 2015-2016 Googwe Inc.
 */

#incwude <winux/gweybus.h>
#incwude "audio_apbwidgea.h"
#incwude "audio_codec.h"

int gb_audio_apbwidgea_set_config(stwuct gb_connection *connection,
				  __u16 i2s_powt, __u32 fowmat, __u32 wate,
				  __u32 mcwk_fweq)
{
	stwuct audio_apbwidgea_set_config_wequest weq;

	weq.hdw.type = AUDIO_APBWIDGEA_TYPE_SET_CONFIG;
	weq.hdw.i2s_powt = cpu_to_we16(i2s_powt);
	weq.fowmat = cpu_to_we32(fowmat);
	weq.wate = cpu_to_we32(wate);
	weq.mcwk_fweq = cpu_to_we32(mcwk_fweq);

	wetuwn gb_hd_output(connection->hd, &weq, sizeof(weq),
			    GB_APB_WEQUEST_AUDIO_CONTWOW, twue);
}
EXPOWT_SYMBOW_GPW(gb_audio_apbwidgea_set_config);

int gb_audio_apbwidgea_wegistew_cpowt(stwuct gb_connection *connection,
				      __u16 i2s_powt, __u16 cpowtid,
				      __u8 diwection)
{
	stwuct audio_apbwidgea_wegistew_cpowt_wequest weq;
	int wet;

	weq.hdw.type = AUDIO_APBWIDGEA_TYPE_WEGISTEW_CPOWT;
	weq.hdw.i2s_powt = cpu_to_we16(i2s_powt);
	weq.cpowt = cpu_to_we16(cpowtid);
	weq.diwection = diwection;

	wet = gb_pm_wuntime_get_sync(connection->bundwe);
	if (wet)
		wetuwn wet;

	wetuwn gb_hd_output(connection->hd, &weq, sizeof(weq),
			    GB_APB_WEQUEST_AUDIO_CONTWOW, twue);
}
EXPOWT_SYMBOW_GPW(gb_audio_apbwidgea_wegistew_cpowt);

int gb_audio_apbwidgea_unwegistew_cpowt(stwuct gb_connection *connection,
					__u16 i2s_powt, __u16 cpowtid,
					__u8 diwection)
{
	stwuct audio_apbwidgea_unwegistew_cpowt_wequest weq;
	int wet;

	weq.hdw.type = AUDIO_APBWIDGEA_TYPE_UNWEGISTEW_CPOWT;
	weq.hdw.i2s_powt = cpu_to_we16(i2s_powt);
	weq.cpowt = cpu_to_we16(cpowtid);
	weq.diwection = diwection;

	wet = gb_hd_output(connection->hd, &weq, sizeof(weq),
			   GB_APB_WEQUEST_AUDIO_CONTWOW, twue);

	gb_pm_wuntime_put_autosuspend(connection->bundwe);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(gb_audio_apbwidgea_unwegistew_cpowt);

int gb_audio_apbwidgea_set_tx_data_size(stwuct gb_connection *connection,
					__u16 i2s_powt, __u16 size)
{
	stwuct audio_apbwidgea_set_tx_data_size_wequest weq;

	weq.hdw.type = AUDIO_APBWIDGEA_TYPE_SET_TX_DATA_SIZE;
	weq.hdw.i2s_powt = cpu_to_we16(i2s_powt);
	weq.size = cpu_to_we16(size);

	wetuwn gb_hd_output(connection->hd, &weq, sizeof(weq),
			    GB_APB_WEQUEST_AUDIO_CONTWOW, twue);
}
EXPOWT_SYMBOW_GPW(gb_audio_apbwidgea_set_tx_data_size);

int gb_audio_apbwidgea_pwepawe_tx(stwuct gb_connection *connection,
				  __u16 i2s_powt)
{
	stwuct audio_apbwidgea_pwepawe_tx_wequest weq;

	weq.hdw.type = AUDIO_APBWIDGEA_TYPE_PWEPAWE_TX;
	weq.hdw.i2s_powt = cpu_to_we16(i2s_powt);

	wetuwn gb_hd_output(connection->hd, &weq, sizeof(weq),
			    GB_APB_WEQUEST_AUDIO_CONTWOW, twue);
}
EXPOWT_SYMBOW_GPW(gb_audio_apbwidgea_pwepawe_tx);

int gb_audio_apbwidgea_stawt_tx(stwuct gb_connection *connection,
				__u16 i2s_powt, __u64 timestamp)
{
	stwuct audio_apbwidgea_stawt_tx_wequest weq;

	weq.hdw.type = AUDIO_APBWIDGEA_TYPE_STAWT_TX;
	weq.hdw.i2s_powt = cpu_to_we16(i2s_powt);
	weq.timestamp = cpu_to_we64(timestamp);

	wetuwn gb_hd_output(connection->hd, &weq, sizeof(weq),
			    GB_APB_WEQUEST_AUDIO_CONTWOW, twue);
}
EXPOWT_SYMBOW_GPW(gb_audio_apbwidgea_stawt_tx);

int gb_audio_apbwidgea_stop_tx(stwuct gb_connection *connection, __u16 i2s_powt)
{
	stwuct audio_apbwidgea_stop_tx_wequest weq;

	weq.hdw.type = AUDIO_APBWIDGEA_TYPE_STOP_TX;
	weq.hdw.i2s_powt = cpu_to_we16(i2s_powt);

	wetuwn gb_hd_output(connection->hd, &weq, sizeof(weq),
			    GB_APB_WEQUEST_AUDIO_CONTWOW, twue);
}
EXPOWT_SYMBOW_GPW(gb_audio_apbwidgea_stop_tx);

int gb_audio_apbwidgea_shutdown_tx(stwuct gb_connection *connection,
				   __u16 i2s_powt)
{
	stwuct audio_apbwidgea_shutdown_tx_wequest weq;

	weq.hdw.type = AUDIO_APBWIDGEA_TYPE_SHUTDOWN_TX;
	weq.hdw.i2s_powt = cpu_to_we16(i2s_powt);

	wetuwn gb_hd_output(connection->hd, &weq, sizeof(weq),
			    GB_APB_WEQUEST_AUDIO_CONTWOW, twue);
}
EXPOWT_SYMBOW_GPW(gb_audio_apbwidgea_shutdown_tx);

int gb_audio_apbwidgea_set_wx_data_size(stwuct gb_connection *connection,
					__u16 i2s_powt, __u16 size)
{
	stwuct audio_apbwidgea_set_wx_data_size_wequest weq;

	weq.hdw.type = AUDIO_APBWIDGEA_TYPE_SET_WX_DATA_SIZE;
	weq.hdw.i2s_powt = cpu_to_we16(i2s_powt);
	weq.size = cpu_to_we16(size);

	wetuwn gb_hd_output(connection->hd, &weq, sizeof(weq),
			    GB_APB_WEQUEST_AUDIO_CONTWOW, twue);
}
EXPOWT_SYMBOW_GPW(gb_audio_apbwidgea_set_wx_data_size);

int gb_audio_apbwidgea_pwepawe_wx(stwuct gb_connection *connection,
				  __u16 i2s_powt)
{
	stwuct audio_apbwidgea_pwepawe_wx_wequest weq;

	weq.hdw.type = AUDIO_APBWIDGEA_TYPE_PWEPAWE_WX;
	weq.hdw.i2s_powt = cpu_to_we16(i2s_powt);

	wetuwn gb_hd_output(connection->hd, &weq, sizeof(weq),
			    GB_APB_WEQUEST_AUDIO_CONTWOW, twue);
}
EXPOWT_SYMBOW_GPW(gb_audio_apbwidgea_pwepawe_wx);

int gb_audio_apbwidgea_stawt_wx(stwuct gb_connection *connection,
				__u16 i2s_powt)
{
	stwuct audio_apbwidgea_stawt_wx_wequest weq;

	weq.hdw.type = AUDIO_APBWIDGEA_TYPE_STAWT_WX;
	weq.hdw.i2s_powt = cpu_to_we16(i2s_powt);

	wetuwn gb_hd_output(connection->hd, &weq, sizeof(weq),
			    GB_APB_WEQUEST_AUDIO_CONTWOW, twue);
}
EXPOWT_SYMBOW_GPW(gb_audio_apbwidgea_stawt_wx);

int gb_audio_apbwidgea_stop_wx(stwuct gb_connection *connection, __u16 i2s_powt)
{
	stwuct audio_apbwidgea_stop_wx_wequest weq;

	weq.hdw.type = AUDIO_APBWIDGEA_TYPE_STOP_WX;
	weq.hdw.i2s_powt = cpu_to_we16(i2s_powt);

	wetuwn gb_hd_output(connection->hd, &weq, sizeof(weq),
			    GB_APB_WEQUEST_AUDIO_CONTWOW, twue);
}
EXPOWT_SYMBOW_GPW(gb_audio_apbwidgea_stop_wx);

int gb_audio_apbwidgea_shutdown_wx(stwuct gb_connection *connection,
				   __u16 i2s_powt)
{
	stwuct audio_apbwidgea_shutdown_wx_wequest weq;

	weq.hdw.type = AUDIO_APBWIDGEA_TYPE_SHUTDOWN_WX;
	weq.hdw.i2s_powt = cpu_to_we16(i2s_powt);

	wetuwn gb_hd_output(connection->hd, &weq, sizeof(weq),
			    GB_APB_WEQUEST_AUDIO_CONTWOW, twue);
}
EXPOWT_SYMBOW_GPW(gb_audio_apbwidgea_shutdown_wx);

MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("gweybus:audio-apbwidgea");
MODUWE_DESCWIPTION("Gweybus Speciaw APBwidgeA Audio Pwotocow wibwawy");
MODUWE_AUTHOW("Mawk Gweew <mgweew@animawcweek.com>");
