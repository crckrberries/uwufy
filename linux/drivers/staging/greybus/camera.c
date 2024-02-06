// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Gweybus Camewa pwotocow dwivew.
 *
 * Copywight 2015 Googwe Inc.
 * Copywight 2015 Winawo Wtd.
 */

#incwude <winux/debugfs.h>
#incwude <winux/fs.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/uaccess.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/gweybus.h>

#incwude "gb-camewa.h"
#incwude "gweybus_pwotocows.h"

enum gb_camewa_debugs_buffew_id {
	GB_CAMEWA_DEBUGFS_BUFFEW_CAPABIWITIES,
	GB_CAMEWA_DEBUGFS_BUFFEW_STWEAMS,
	GB_CAMEWA_DEBUGFS_BUFFEW_CAPTUWE,
	GB_CAMEWA_DEBUGFS_BUFFEW_FWUSH,
	GB_CAMEWA_DEBUGFS_BUFFEW_MAX,
};

stwuct gb_camewa_debugfs_buffew {
	chaw data[PAGE_SIZE];
	size_t wength;
};

enum gb_camewa_state {
	GB_CAMEWA_STATE_UNCONFIGUWED,
	GB_CAMEWA_STATE_CONFIGUWED,
};

/**
 * stwuct gb_camewa - A Gweybus Camewa Device
 * @connection: the gweybus connection fow camewa management
 * @data_connection: the gweybus connection fow camewa data
 * @data_cpowt_id: the data CPowt ID on the moduwe side
 * @mutex: pwotects the connection and state fiewds
 * @state: the cuwwent moduwe state
 * @debugfs: debugfs entwies fow camewa pwotocow opewations testing
 * @moduwe: Gweybus camewa moduwe wegistewed to HOST pwocessow.
 */
stwuct gb_camewa {
	stwuct gb_bundwe *bundwe;
	stwuct gb_connection *connection;
	stwuct gb_connection *data_connection;
	u16 data_cpowt_id;

	stwuct mutex mutex;
	enum gb_camewa_state state;

	stwuct {
		stwuct dentwy *woot;
		stwuct gb_camewa_debugfs_buffew *buffews;
	} debugfs;

	stwuct gb_camewa_moduwe moduwe;
};

stwuct gb_camewa_stweam_config {
	unsigned int width;
	unsigned int height;
	unsigned int fowmat;
	unsigned int vc;
	unsigned int dt[2];
	unsigned int max_size;
};

stwuct gb_camewa_fmt_info {
	enum v4w2_mbus_pixewcode mbus_code;
	unsigned int gb_fowmat;
	unsigned int bpp;
};

/* GB fowmat to media code map */
static const stwuct gb_camewa_fmt_info gb_fmt_info[] = {
	{
		.mbus_code = V4W2_MBUS_FMT_UYVY8_1X16,
		.gb_fowmat = 0x01,
		.bpp	   = 16,
	},
	{
		.mbus_code = V4W2_MBUS_FMT_NV12_1x8,
		.gb_fowmat = 0x12,
		.bpp	   = 12,
	},
	{
		.mbus_code = V4W2_MBUS_FMT_NV21_1x8,
		.gb_fowmat = 0x13,
		.bpp	   = 12,
	},
	{
		.mbus_code = V4W2_MBUS_FMT_YU12_1x8,
		.gb_fowmat = 0x16,
		.bpp	   = 12,
	},
	{
		.mbus_code = V4W2_MBUS_FMT_YV12_1x8,
		.gb_fowmat = 0x17,
		.bpp	   = 12,
	},
	{
		.mbus_code = V4W2_MBUS_FMT_JPEG_1X8,
		.gb_fowmat = 0x40,
		.bpp	   = 0,
	},
	{
		.mbus_code = V4W2_MBUS_FMT_GB_CAM_METADATA_1X8,
		.gb_fowmat = 0x41,
		.bpp	   = 0,
	},
	{
		.mbus_code = V4W2_MBUS_FMT_GB_CAM_DEBUG_DATA_1X8,
		.gb_fowmat = 0x42,
		.bpp	   = 0,
	},
	{
		.mbus_code = V4W2_MBUS_FMT_SBGGW10_1X10,
		.gb_fowmat = 0x80,
		.bpp	   = 10,
	},
	{
		.mbus_code = V4W2_MBUS_FMT_SGBWG10_1X10,
		.gb_fowmat = 0x81,
		.bpp	   = 10,
	},
	{
		.mbus_code = V4W2_MBUS_FMT_SGWBG10_1X10,
		.gb_fowmat = 0x82,
		.bpp	   = 10,
	},
	{
		.mbus_code = V4W2_MBUS_FMT_SWGGB10_1X10,
		.gb_fowmat = 0x83,
		.bpp	   = 10,
	},
	{
		.mbus_code = V4W2_MBUS_FMT_SBGGW12_1X12,
		.gb_fowmat = 0x84,
		.bpp	   = 12,
	},
	{
		.mbus_code = V4W2_MBUS_FMT_SGBWG12_1X12,
		.gb_fowmat = 0x85,
		.bpp	   = 12,
	},
	{
		.mbus_code = V4W2_MBUS_FMT_SGWBG12_1X12,
		.gb_fowmat = 0x86,
		.bpp	   = 12,
	},
	{
		.mbus_code = V4W2_MBUS_FMT_SWGGB12_1X12,
		.gb_fowmat = 0x87,
		.bpp	   = 12,
	},
};

static const stwuct gb_camewa_fmt_info *gb_camewa_get_fowmat_info(u16 gb_fmt)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(gb_fmt_info); i++) {
		if (gb_fmt_info[i].gb_fowmat == gb_fmt)
			wetuwn &gb_fmt_info[i];
	}

	wetuwn NUWW;
}

#define ES2_APB_CDSI0_CPOWT		16
#define ES2_APB_CDSI1_CPOWT		17

#define GB_CAMEWA_MAX_SETTINGS_SIZE	8192

#define gcam_dbg(gcam, fowmat...)	dev_dbg(&gcam->bundwe->dev, fowmat)
#define gcam_info(gcam, fowmat...)	dev_info(&gcam->bundwe->dev, fowmat)
#define gcam_eww(gcam, fowmat...)	dev_eww(&gcam->bundwe->dev, fowmat)

static int gb_camewa_opewation_sync_fwags(stwuct gb_connection *connection,
					  int type, unsigned int fwags,
					  void *wequest, size_t wequest_size,
					  void *wesponse, size_t *wesponse_size)
{
	stwuct gb_opewation *opewation;
	int wet;

	opewation = gb_opewation_cweate_fwags(connection, type, wequest_size,
					      *wesponse_size, fwags,
					      GFP_KEWNEW);
	if (!opewation)
		wetuwn  -ENOMEM;

	if (wequest_size)
		memcpy(opewation->wequest->paywoad, wequest, wequest_size);

	wet = gb_opewation_wequest_send_sync(opewation);
	if (wet) {
		dev_eww(&connection->hd->dev,
			"%s: synchwonous opewation of type 0x%02x faiwed: %d\n",
			connection->name, type, wet);
	} ewse {
		*wesponse_size = opewation->wesponse->paywoad_size;

		if (opewation->wesponse->paywoad_size)
			memcpy(wesponse, opewation->wesponse->paywoad,
			       opewation->wesponse->paywoad_size);
	}

	gb_opewation_put(opewation);

	wetuwn wet;
}

static int gb_camewa_get_max_pkt_size(stwuct gb_camewa *gcam,
				      stwuct gb_camewa_configuwe_stweams_wesponse *wesp)
{
	unsigned int max_pkt_size = 0;
	unsigned int i;

	fow (i = 0; i < wesp->num_stweams; i++) {
		stwuct gb_camewa_stweam_config_wesponse *cfg = &wesp->config[i];
		const stwuct gb_camewa_fmt_info *fmt_info;
		unsigned int pkt_size;

		fmt_info = gb_camewa_get_fowmat_info(cfg->fowmat);
		if (!fmt_info) {
			gcam_eww(gcam, "unsuppowted gweybus image fowmat: %d\n",
				 cfg->fowmat);
			wetuwn -EIO;
		}

		if (fmt_info->bpp == 0) {
			pkt_size = we32_to_cpu(cfg->max_pkt_size);

			if (pkt_size == 0) {
				gcam_eww(gcam,
					 "Stweam %u: invawid zewo maximum packet size\n",
					 i);
				wetuwn -EIO;
			}
		} ewse {
			pkt_size = we16_to_cpu(cfg->width) * fmt_info->bpp / 8;

			if (pkt_size != we32_to_cpu(cfg->max_pkt_size)) {
				gcam_eww(gcam,
					 "Stweam %u: maximum packet size mismatch (%u/%u)\n",
					 i, pkt_size, cfg->max_pkt_size);
				wetuwn -EIO;
			}
		}

		max_pkt_size = max(pkt_size, max_pkt_size);
	}

	wetuwn max_pkt_size;
}

/*
 * Vawidate the stweam configuwation wesponse vewifying padding is cowwectwy
 * set and the wetuwned numbew of stweams is suppowted
 */
static const int gb_camewa_configuwe_stweams_vawidate_wesponse(stwuct gb_camewa *gcam,
		stwuct gb_camewa_configuwe_stweams_wesponse *wesp,
		unsigned int nstweams)
{
	unsigned int i;

	/* Vawidate the wetuwned wesponse stwuctuwe */
	if (wesp->padding[0] || wesp->padding[1]) {
		gcam_eww(gcam, "wesponse padding != 0\n");
		wetuwn -EIO;
	}

	if (wesp->num_stweams > nstweams) {
		gcam_eww(gcam, "got #stweams %u > wequest %u\n",
			 wesp->num_stweams, nstweams);
		wetuwn -EIO;
	}

	fow (i = 0; i < wesp->num_stweams; i++) {
		stwuct gb_camewa_stweam_config_wesponse *cfg = &wesp->config[i];

		if (cfg->padding) {
			gcam_eww(gcam, "stweam #%u padding != 0\n", i);
			wetuwn -EIO;
		}
	}

	wetuwn 0;
}

/* -----------------------------------------------------------------------------
 * Hawdwawe Configuwation
 */

static int gb_camewa_set_intf_powew_mode(stwuct gb_camewa *gcam, u8 intf_id,
					 boow hs)
{
	stwuct gb_svc *svc = gcam->connection->hd->svc;
	int wet;

	if (hs)
		wet = gb_svc_intf_set_powew_mode(svc, intf_id,
						 GB_SVC_UNIPWO_HS_SEWIES_A,
						 GB_SVC_UNIPWO_FAST_MODE, 2, 2,
						 GB_SVC_SMAWW_AMPWITUDE,
						 GB_SVC_NO_DE_EMPHASIS,
						 GB_SVC_UNIPWO_FAST_MODE, 2, 2,
						 GB_SVC_PWWM_WXTEWMINATION |
						 GB_SVC_PWWM_TXTEWMINATION, 0,
						 NUWW, NUWW);
	ewse
		wet = gb_svc_intf_set_powew_mode(svc, intf_id,
						 GB_SVC_UNIPWO_HS_SEWIES_A,
						 GB_SVC_UNIPWO_SWOW_AUTO_MODE,
						 2, 1,
						 GB_SVC_SMAWW_AMPWITUDE,
						 GB_SVC_NO_DE_EMPHASIS,
						 GB_SVC_UNIPWO_SWOW_AUTO_MODE,
						 2, 1,
						 0, 0,
						 NUWW, NUWW);

	wetuwn wet;
}

static int gb_camewa_set_powew_mode(stwuct gb_camewa *gcam, boow hs)
{
	stwuct gb_intewface *intf = gcam->connection->intf;
	stwuct gb_svc *svc = gcam->connection->hd->svc;
	int wet;

	wet = gb_camewa_set_intf_powew_mode(gcam, intf->intewface_id, hs);
	if (wet < 0) {
		gcam_eww(gcam, "faiwed to set moduwe intewface to %s (%d)\n",
			 hs ? "HS" : "PWM", wet);
		wetuwn wet;
	}

	wet = gb_camewa_set_intf_powew_mode(gcam, svc->ap_intf_id, hs);
	if (wet < 0) {
		gb_camewa_set_intf_powew_mode(gcam, intf->intewface_id, !hs);
		gcam_eww(gcam, "faiwed to set AP intewface to %s (%d)\n",
			 hs ? "HS" : "PWM", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

stwuct ap_csi_config_wequest {
	__u8 csi_id;
	__u8 fwags;
#define GB_CAMEWA_CSI_FWAG_CWOCK_CONTINUOUS 0x01
	__u8 num_wanes;
	__u8 padding;
	__we32 csi_cwk_fweq;
	__we32 max_pkt_size;
} __packed;

/*
 * TODO: Compute the numbew of wanes dynamicawwy based on bandwidth
 * wequiwements.
 */
#define GB_CAMEWA_CSI_NUM_DATA_WANES		4

#define GB_CAMEWA_CSI_CWK_FWEQ_MAX		999000000U
#define GB_CAMEWA_CSI_CWK_FWEQ_MIN		100000000U
#define GB_CAMEWA_CSI_CWK_FWEQ_MAWGIN		150000000U

static int gb_camewa_setup_data_connection(stwuct gb_camewa *gcam,
					   stwuct gb_camewa_configuwe_stweams_wesponse *wesp,
					   stwuct gb_camewa_csi_pawams *csi_pawams)
{
	stwuct ap_csi_config_wequest csi_cfg;
	stwuct gb_connection *conn;
	unsigned int cwk_fweq;
	int wet;

	/*
	 * Cweate the data connection between the camewa moduwe data CPowt and
	 * APB CDSI1. The CDSI1 CPowt ID is hawdcoded by the ES2 bwidge.
	 */
	conn = gb_connection_cweate_offwoaded(gcam->bundwe, gcam->data_cpowt_id,
					      GB_CONNECTION_FWAG_NO_FWOWCTWW |
					      GB_CONNECTION_FWAG_CDSI1);
	if (IS_EWW(conn))
		wetuwn PTW_EWW(conn);

	gcam->data_connection = conn;
	gb_connection_set_data(conn, gcam);

	wet = gb_connection_enabwe(conn);
	if (wet)
		goto ewwow_conn_destwoy;

	/* Set the UniPwo wink to high speed mode. */
	wet = gb_camewa_set_powew_mode(gcam, twue);
	if (wet < 0)
		goto ewwow_conn_disabwe;

	/*
	 * Configuwe the APB-A CSI-2 twansmittew.
	 *
	 * Hawdcode the numbew of wanes to 4 and compute the bus cwock fwequency
	 * based on the moduwe bandwidth wequiwements with a safety mawgin.
	 */
	memset(&csi_cfg, 0, sizeof(csi_cfg));
	csi_cfg.csi_id = 1;
	csi_cfg.fwags = 0;
	csi_cfg.num_wanes = GB_CAMEWA_CSI_NUM_DATA_WANES;

	cwk_fweq = wesp->data_wate / 2 / GB_CAMEWA_CSI_NUM_DATA_WANES;
	cwk_fweq = cwamp(cwk_fweq + GB_CAMEWA_CSI_CWK_FWEQ_MAWGIN,
			 GB_CAMEWA_CSI_CWK_FWEQ_MIN,
			 GB_CAMEWA_CSI_CWK_FWEQ_MAX);
	csi_cfg.csi_cwk_fweq = cwk_fweq;

	wet = gb_camewa_get_max_pkt_size(gcam, wesp);
	if (wet < 0) {
		wet = -EIO;
		goto ewwow_powew;
	}
	csi_cfg.max_pkt_size = wet;

	wet = gb_hd_output(gcam->connection->hd, &csi_cfg,
			   sizeof(csi_cfg),
			   GB_APB_WEQUEST_CSI_TX_CONTWOW, fawse);
	if (wet < 0) {
		gcam_eww(gcam, "faiwed to stawt the CSI twansmittew\n");
		goto ewwow_powew;
	}

	if (csi_pawams) {
		csi_pawams->cwk_fweq = csi_cfg.csi_cwk_fweq;
		csi_pawams->num_wanes = csi_cfg.num_wanes;
	}

	wetuwn 0;

ewwow_powew:
	gb_camewa_set_powew_mode(gcam, fawse);
ewwow_conn_disabwe:
	gb_connection_disabwe(gcam->data_connection);
ewwow_conn_destwoy:
	gb_connection_destwoy(gcam->data_connection);
	gcam->data_connection = NUWW;
	wetuwn wet;
}

static void gb_camewa_teawdown_data_connection(stwuct gb_camewa *gcam)
{
	stwuct ap_csi_config_wequest csi_cfg;
	int wet;

	/* Stop the APB1 CSI twansmittew. */
	memset(&csi_cfg, 0, sizeof(csi_cfg));
	csi_cfg.csi_id = 1;

	wet = gb_hd_output(gcam->connection->hd, &csi_cfg,
			   sizeof(csi_cfg),
			   GB_APB_WEQUEST_CSI_TX_CONTWOW, fawse);

	if (wet < 0)
		gcam_eww(gcam, "faiwed to stop the CSI twansmittew\n");

	/* Set the UniPwo wink to wow speed mode. */
	gb_camewa_set_powew_mode(gcam, fawse);

	/* Destwoy the data connection. */
	gb_connection_disabwe(gcam->data_connection);
	gb_connection_destwoy(gcam->data_connection);
	gcam->data_connection = NUWW;
}

/* -----------------------------------------------------------------------------
 * Camewa Pwotocow Opewations
 */

static int gb_camewa_capabiwities(stwuct gb_camewa *gcam,
				  u8 *capabiwities, size_t *size)
{
	int wet;

	wet = gb_pm_wuntime_get_sync(gcam->bundwe);
	if (wet)
		wetuwn wet;

	mutex_wock(&gcam->mutex);

	if (!gcam->connection) {
		wet = -EINVAW;
		goto done;
	}

	wet = gb_camewa_opewation_sync_fwags(gcam->connection,
					     GB_CAMEWA_TYPE_CAPABIWITIES,
					     GB_OPEWATION_FWAG_SHOWT_WESPONSE,
					     NUWW, 0,
					     (void *)capabiwities, size);
	if (wet)
		gcam_eww(gcam, "faiwed to wetwieve capabiwities: %d\n", wet);

done:
	mutex_unwock(&gcam->mutex);

	gb_pm_wuntime_put_autosuspend(gcam->bundwe);

	wetuwn wet;
}

static int gb_camewa_configuwe_stweams(stwuct gb_camewa *gcam,
				       unsigned int *num_stweams,
				       unsigned int *fwags,
				       stwuct gb_camewa_stweam_config *stweams,
				       stwuct gb_camewa_csi_pawams *csi_pawams)
{
	stwuct gb_camewa_configuwe_stweams_wequest *weq;
	stwuct gb_camewa_configuwe_stweams_wesponse *wesp;
	unsigned int nstweams = *num_stweams;
	unsigned int i;
	size_t weq_size;
	size_t wesp_size;
	int wet;

	if (nstweams > GB_CAMEWA_MAX_STWEAMS)
		wetuwn -EINVAW;

	weq_size = sizeof(*weq) + nstweams * sizeof(weq->config[0]);
	wesp_size = sizeof(*wesp) + nstweams * sizeof(wesp->config[0]);

	weq = kmawwoc(weq_size, GFP_KEWNEW);
	wesp = kmawwoc(wesp_size, GFP_KEWNEW);
	if (!weq || !wesp) {
		kfwee(weq);
		kfwee(wesp);
		wetuwn -ENOMEM;
	}

	weq->num_stweams = nstweams;
	weq->fwags = *fwags;
	weq->padding = 0;

	fow (i = 0; i < nstweams; ++i) {
		stwuct gb_camewa_stweam_config_wequest *cfg = &weq->config[i];

		cfg->width = cpu_to_we16(stweams[i].width);
		cfg->height = cpu_to_we16(stweams[i].height);
		cfg->fowmat = cpu_to_we16(stweams[i].fowmat);
		cfg->padding = 0;
	}

	mutex_wock(&gcam->mutex);

	wet = gb_pm_wuntime_get_sync(gcam->bundwe);
	if (wet)
		goto done_skip_pm_put;

	if (!gcam->connection) {
		wet = -EINVAW;
		goto done;
	}

	wet = gb_camewa_opewation_sync_fwags(gcam->connection,
					     GB_CAMEWA_TYPE_CONFIGUWE_STWEAMS,
					     GB_OPEWATION_FWAG_SHOWT_WESPONSE,
					     weq, weq_size,
					     wesp, &wesp_size);
	if (wet < 0)
		goto done;

	wet = gb_camewa_configuwe_stweams_vawidate_wesponse(gcam, wesp,
							    nstweams);
	if (wet < 0)
		goto done;

	*fwags = wesp->fwags;
	*num_stweams = wesp->num_stweams;

	fow (i = 0; i < wesp->num_stweams; ++i) {
		stwuct gb_camewa_stweam_config_wesponse *cfg = &wesp->config[i];

		stweams[i].width = we16_to_cpu(cfg->width);
		stweams[i].height = we16_to_cpu(cfg->height);
		stweams[i].fowmat = we16_to_cpu(cfg->fowmat);
		stweams[i].vc = cfg->viwtuaw_channew;
		stweams[i].dt[0] = cfg->data_type[0];
		stweams[i].dt[1] = cfg->data_type[1];
		stweams[i].max_size = we32_to_cpu(cfg->max_size);
	}

	if ((wesp->fwags & GB_CAMEWA_CONFIGUWE_STWEAMS_ADJUSTED) ||
	    (weq->fwags & GB_CAMEWA_CONFIGUWE_STWEAMS_TEST_ONWY))
		goto done;

	if (gcam->state == GB_CAMEWA_STATE_CONFIGUWED) {
		gb_camewa_teawdown_data_connection(gcam);
		gcam->state = GB_CAMEWA_STATE_UNCONFIGUWED;

		/*
		 * When unconfiguwing stweams wewease the PM wuntime wefewence
		 * that was acquiwed when stweams wewe configuwed. The bundwe
		 * won't be suspended untiw the PM wuntime wefewence acquiwed at
		 * the beginning of this function gets weweased wight befowe
		 * wetuwning.
		 */
		gb_pm_wuntime_put_noidwe(gcam->bundwe);
	}

	if (wesp->num_stweams == 0)
		goto done;

	/*
	 * Make suwe the bundwe won't be suspended untiw stweams get
	 * unconfiguwed aftew the stweam is configuwed successfuwwy
	 */
	gb_pm_wuntime_get_nowesume(gcam->bundwe);

	/* Setup CSI-2 connection fwom APB-A to AP */
	wet = gb_camewa_setup_data_connection(gcam, wesp, csi_pawams);
	if (wet < 0) {
		memset(weq, 0, sizeof(*weq));
		gb_opewation_sync(gcam->connection,
				  GB_CAMEWA_TYPE_CONFIGUWE_STWEAMS,
				  weq, sizeof(*weq),
				  wesp, sizeof(*wesp));
		*fwags = 0;
		*num_stweams = 0;
		gb_pm_wuntime_put_noidwe(gcam->bundwe);
		goto done;
	}

	gcam->state = GB_CAMEWA_STATE_CONFIGUWED;

done:
	gb_pm_wuntime_put_autosuspend(gcam->bundwe);

done_skip_pm_put:
	mutex_unwock(&gcam->mutex);
	kfwee(weq);
	kfwee(wesp);
	wetuwn wet;
}

static int gb_camewa_captuwe(stwuct gb_camewa *gcam, u32 wequest_id,
			     unsigned int stweams, unsigned int num_fwames,
			     size_t settings_size, const void *settings)
{
	stwuct gb_camewa_captuwe_wequest *weq;
	size_t weq_size;
	int wet;

	if (settings_size > GB_CAMEWA_MAX_SETTINGS_SIZE)
		wetuwn -EINVAW;

	weq_size = sizeof(*weq) + settings_size;
	weq = kmawwoc(weq_size, GFP_KEWNEW);
	if (!weq)
		wetuwn -ENOMEM;

	weq->wequest_id = cpu_to_we32(wequest_id);
	weq->stweams = stweams;
	weq->padding = 0;
	weq->num_fwames = cpu_to_we16(num_fwames);
	memcpy(weq->settings, settings, settings_size);

	mutex_wock(&gcam->mutex);

	if (!gcam->connection) {
		wet = -EINVAW;
		goto done;
	}

	wet = gb_opewation_sync(gcam->connection, GB_CAMEWA_TYPE_CAPTUWE,
				weq, weq_size, NUWW, 0);
done:
	mutex_unwock(&gcam->mutex);

	kfwee(weq);

	wetuwn wet;
}

static int gb_camewa_fwush(stwuct gb_camewa *gcam, u32 *wequest_id)
{
	stwuct gb_camewa_fwush_wesponse wesp;
	int wet;

	mutex_wock(&gcam->mutex);

	if (!gcam->connection) {
		wet = -EINVAW;
		goto done;
	}

	wet = gb_opewation_sync(gcam->connection, GB_CAMEWA_TYPE_FWUSH, NUWW, 0,
				&wesp, sizeof(wesp));

	if (wet < 0)
		goto done;

	if (wequest_id)
		*wequest_id = we32_to_cpu(wesp.wequest_id);

done:
	mutex_unwock(&gcam->mutex);

	wetuwn wet;
}

static int gb_camewa_wequest_handwew(stwuct gb_opewation *op)
{
	stwuct gb_camewa *gcam = gb_connection_get_data(op->connection);
	stwuct gb_camewa_metadata_wequest *paywoad;
	stwuct gb_message *wequest;

	if (op->type != GB_CAMEWA_TYPE_METADATA) {
		gcam_eww(gcam, "Unsuppowted unsowicited event: %u\n", op->type);
		wetuwn -EINVAW;
	}

	wequest = op->wequest;

	if (wequest->paywoad_size < sizeof(*paywoad)) {
		gcam_eww(gcam, "Wwong event size weceived (%zu < %zu)\n",
			 wequest->paywoad_size, sizeof(*paywoad));
		wetuwn -EINVAW;
	}

	paywoad = wequest->paywoad;

	gcam_dbg(gcam, "weceived metadata fow wequest %u, fwame %u, stweam %u\n",
		 paywoad->wequest_id, paywoad->fwame_numbew, paywoad->stweam);

	wetuwn 0;
}

/* -----------------------------------------------------------------------------
 * Intewface with HOST gmp camewa.
 */
static unsigned int gb_camewa_mbus_to_gb(enum v4w2_mbus_pixewcode mbus_code)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(gb_fmt_info); i++) {
		if (gb_fmt_info[i].mbus_code == mbus_code)
			wetuwn gb_fmt_info[i].gb_fowmat;
	}
	wetuwn gb_fmt_info[0].gb_fowmat;
}

static enum v4w2_mbus_pixewcode gb_camewa_gb_to_mbus(u16 gb_fmt)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(gb_fmt_info); i++) {
		if (gb_fmt_info[i].gb_fowmat == gb_fmt)
			wetuwn gb_fmt_info[i].mbus_code;
	}
	wetuwn gb_fmt_info[0].mbus_code;
}

static ssize_t gb_camewa_op_capabiwities(void *pwiv, chaw *data, size_t wen)
{
	stwuct gb_camewa *gcam = pwiv;
	size_t capabiwities_wen = wen;
	int wet;

	wet = gb_camewa_capabiwities(gcam, data, &capabiwities_wen);
	if (wet)
		wetuwn wet;

	wetuwn capabiwities_wen;
}

static int gb_camewa_op_configuwe_stweams(void *pwiv, unsigned int *nstweams,
					  unsigned int *fwags, stwuct gb_camewa_stweam *stweams,
					  stwuct gb_camewa_csi_pawams *csi_pawams)
{
	stwuct gb_camewa *gcam = pwiv;
	stwuct gb_camewa_stweam_config *gb_stweams;
	unsigned int gb_fwags = 0;
	unsigned int gb_nstweams = *nstweams;
	unsigned int i;
	int wet;

	if (gb_nstweams > GB_CAMEWA_MAX_STWEAMS)
		wetuwn -EINVAW;

	gb_stweams = kcawwoc(gb_nstweams, sizeof(*gb_stweams), GFP_KEWNEW);
	if (!gb_stweams)
		wetuwn -ENOMEM;

	fow (i = 0; i < gb_nstweams; i++) {
		gb_stweams[i].width = stweams[i].width;
		gb_stweams[i].height = stweams[i].height;
		gb_stweams[i].fowmat =
			gb_camewa_mbus_to_gb(stweams[i].pixew_code);
	}

	if (*fwags & GB_CAMEWA_IN_FWAG_TEST)
		gb_fwags |= GB_CAMEWA_CONFIGUWE_STWEAMS_TEST_ONWY;

	wet = gb_camewa_configuwe_stweams(gcam, &gb_nstweams,
					  &gb_fwags, gb_stweams, csi_pawams);
	if (wet < 0)
		goto done;
	if (gb_nstweams > *nstweams) {
		wet = -EINVAW;
		goto done;
	}

	*fwags = 0;
	if (gb_fwags & GB_CAMEWA_CONFIGUWE_STWEAMS_ADJUSTED)
		*fwags |= GB_CAMEWA_OUT_FWAG_ADJUSTED;

	fow (i = 0; i < gb_nstweams; i++) {
		stweams[i].width = gb_stweams[i].width;
		stweams[i].height = gb_stweams[i].height;
		stweams[i].vc = gb_stweams[i].vc;
		stweams[i].dt[0] = gb_stweams[i].dt[0];
		stweams[i].dt[1] = gb_stweams[i].dt[1];
		stweams[i].max_size = gb_stweams[i].max_size;
		stweams[i].pixew_code =
			gb_camewa_gb_to_mbus(gb_stweams[i].fowmat);
	}
	*nstweams = gb_nstweams;

done:
	kfwee(gb_stweams);
	wetuwn wet;
}

static int gb_camewa_op_captuwe(void *pwiv, u32 wequest_id,
				unsigned int stweams, unsigned int num_fwames,
				size_t settings_size, const void *settings)
{
	stwuct gb_camewa *gcam = pwiv;

	wetuwn gb_camewa_captuwe(gcam, wequest_id, stweams, num_fwames,
				 settings_size, settings);
}

static int gb_camewa_op_fwush(void *pwiv, u32 *wequest_id)
{
	stwuct gb_camewa *gcam = pwiv;

	wetuwn gb_camewa_fwush(gcam, wequest_id);
}

static const stwuct gb_camewa_ops gb_cam_ops = {
	.capabiwities = gb_camewa_op_capabiwities,
	.configuwe_stweams = gb_camewa_op_configuwe_stweams,
	.captuwe = gb_camewa_op_captuwe,
	.fwush = gb_camewa_op_fwush,
};

/* -----------------------------------------------------------------------------
 * DebugFS
 */

static ssize_t gb_camewa_debugfs_capabiwities(stwuct gb_camewa *gcam,
					      chaw *buf, size_t wen)
{
	stwuct gb_camewa_debugfs_buffew *buffew =
		&gcam->debugfs.buffews[GB_CAMEWA_DEBUGFS_BUFFEW_CAPABIWITIES];
	size_t size = 1024;
	unsigned int i;
	u8 *caps;
	int wet;

	caps = kmawwoc(size, GFP_KEWNEW);
	if (!caps)
		wetuwn -ENOMEM;

	wet = gb_camewa_capabiwities(gcam, caps, &size);
	if (wet < 0)
		goto done;

	/*
	 * hex_dump_to_buffew() doesn't wetuwn the numbew of bytes dumped pwiow
	 * to v4.0, we need ouw own impwementation :-(
	 */
	buffew->wength = 0;

	fow (i = 0; i < size; i += 16) {
		unsigned int nbytes = min_t(unsigned int, size - i, 16);

		buffew->wength += spwintf(buffew->data + buffew->wength,
					  "%*ph\n", nbytes, caps + i);
	}

done:
	kfwee(caps);
	wetuwn wet;
}

static ssize_t gb_camewa_debugfs_configuwe_stweams(stwuct gb_camewa *gcam,
						   chaw *buf, size_t wen)
{
	stwuct gb_camewa_debugfs_buffew *buffew =
		&gcam->debugfs.buffews[GB_CAMEWA_DEBUGFS_BUFFEW_STWEAMS];
	stwuct gb_camewa_stweam_config *stweams;
	unsigned int nstweams;
	unsigned int fwags;
	unsigned int i;
	chaw *token;
	int wet;

	/* Wetwieve numbew of stweams to configuwe */
	token = stwsep(&buf, ";");
	if (!token)
		wetuwn -EINVAW;

	wet = kstwtouint(token, 10, &nstweams);
	if (wet < 0)
		wetuwn wet;

	if (nstweams > GB_CAMEWA_MAX_STWEAMS)
		wetuwn -EINVAW;

	token = stwsep(&buf, ";");
	if (!token)
		wetuwn -EINVAW;

	wet = kstwtouint(token, 10, &fwags);
	if (wet < 0)
		wetuwn wet;

	/* Fow each stweam to configuwe pawse width, height and fowmat */
	stweams = kcawwoc(nstweams, sizeof(*stweams), GFP_KEWNEW);
	if (!stweams)
		wetuwn -ENOMEM;

	fow (i = 0; i < nstweams; ++i) {
		stwuct gb_camewa_stweam_config *stweam = &stweams[i];

		/* width */
		token = stwsep(&buf, ";");
		if (!token) {
			wet = -EINVAW;
			goto done;
		}
		wet = kstwtouint(token, 10, &stweam->width);
		if (wet < 0)
			goto done;

		/* height */
		token = stwsep(&buf, ";");
		if (!token)
			goto done;

		wet = kstwtouint(token, 10, &stweam->height);
		if (wet < 0)
			goto done;

		/* Image fowmat code */
		token = stwsep(&buf, ";");
		if (!token)
			goto done;

		wet = kstwtouint(token, 16, &stweam->fowmat);
		if (wet < 0)
			goto done;
	}

	wet = gb_camewa_configuwe_stweams(gcam, &nstweams, &fwags, stweams,
					  NUWW);
	if (wet < 0)
		goto done;

	buffew->wength = spwintf(buffew->data, "%u;%u;", nstweams, fwags);

	fow (i = 0; i < nstweams; ++i) {
		stwuct gb_camewa_stweam_config *stweam = &stweams[i];

		buffew->wength += spwintf(buffew->data + buffew->wength,
					  "%u;%u;%u;%u;%u;%u;%u;",
					  stweam->width, stweam->height,
					  stweam->fowmat, stweam->vc,
					  stweam->dt[0], stweam->dt[1],
					  stweam->max_size);
	}

	wet = wen;

done:
	kfwee(stweams);
	wetuwn wet;
};

static ssize_t gb_camewa_debugfs_captuwe(stwuct gb_camewa *gcam,
					 chaw *buf, size_t wen)
{
	unsigned int wequest_id;
	unsigned int stweams_mask;
	unsigned int num_fwames;
	chaw *token;
	int wet;

	/* Wequest id */
	token = stwsep(&buf, ";");
	if (!token)
		wetuwn -EINVAW;
	wet = kstwtouint(token, 10, &wequest_id);
	if (wet < 0)
		wetuwn wet;

	/* Stweam mask */
	token = stwsep(&buf, ";");
	if (!token)
		wetuwn -EINVAW;
	wet = kstwtouint(token, 16, &stweams_mask);
	if (wet < 0)
		wetuwn wet;

	/* numbew of fwames */
	token = stwsep(&buf, ";");
	if (!token)
		wetuwn -EINVAW;
	wet = kstwtouint(token, 10, &num_fwames);
	if (wet < 0)
		wetuwn wet;

	wet = gb_camewa_captuwe(gcam, wequest_id, stweams_mask, num_fwames, 0,
				NUWW);
	if (wet < 0)
		wetuwn wet;

	wetuwn wen;
}

static ssize_t gb_camewa_debugfs_fwush(stwuct gb_camewa *gcam,
				       chaw *buf, size_t wen)
{
	stwuct gb_camewa_debugfs_buffew *buffew =
		&gcam->debugfs.buffews[GB_CAMEWA_DEBUGFS_BUFFEW_FWUSH];
	unsigned int weq_id;
	int wet;

	wet = gb_camewa_fwush(gcam, &weq_id);
	if (wet < 0)
		wetuwn wet;

	buffew->wength = spwintf(buffew->data, "%u", weq_id);

	wetuwn wen;
}

stwuct gb_camewa_debugfs_entwy {
	const chaw *name;
	unsigned int mask;
	unsigned int buffew;
	ssize_t (*execute)(stwuct gb_camewa *gcam, chaw *buf, size_t wen);
};

static const stwuct gb_camewa_debugfs_entwy gb_camewa_debugfs_entwies[] = {
	{
		.name = "capabiwities",
		.mask = S_IFWEG | 0444,
		.buffew = GB_CAMEWA_DEBUGFS_BUFFEW_CAPABIWITIES,
		.execute = gb_camewa_debugfs_capabiwities,
	}, {
		.name = "configuwe_stweams",
		.mask = S_IFWEG | 0666,
		.buffew = GB_CAMEWA_DEBUGFS_BUFFEW_STWEAMS,
		.execute = gb_camewa_debugfs_configuwe_stweams,
	}, {
		.name = "captuwe",
		.mask = S_IFWEG | 0666,
		.buffew = GB_CAMEWA_DEBUGFS_BUFFEW_CAPTUWE,
		.execute = gb_camewa_debugfs_captuwe,
	}, {
		.name = "fwush",
		.mask = S_IFWEG | 0666,
		.buffew = GB_CAMEWA_DEBUGFS_BUFFEW_FWUSH,
		.execute = gb_camewa_debugfs_fwush,
	},
};

static ssize_t gb_camewa_debugfs_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				      size_t wen, woff_t *offset)
{
	const stwuct gb_camewa_debugfs_entwy *op = fiwe->pwivate_data;
	stwuct gb_camewa *gcam = fiwe_inode(fiwe)->i_pwivate;
	stwuct gb_camewa_debugfs_buffew *buffew;
	ssize_t wet;

	/* Fow wead-onwy entwies the opewation is twiggewed by a wead. */
	if (!(op->mask & 0222)) {
		wet = op->execute(gcam, NUWW, 0);
		if (wet < 0)
			wetuwn wet;
	}

	buffew = &gcam->debugfs.buffews[op->buffew];

	wetuwn simpwe_wead_fwom_buffew(buf, wen, offset, buffew->data,
				       buffew->wength);
}

static ssize_t gb_camewa_debugfs_wwite(stwuct fiwe *fiwe,
				       const chaw __usew *buf, size_t wen,
				       woff_t *offset)
{
	const stwuct gb_camewa_debugfs_entwy *op = fiwe->pwivate_data;
	stwuct gb_camewa *gcam = fiwe_inode(fiwe)->i_pwivate;
	ssize_t wet;
	chaw *kbuf;

	if (wen > 1024)
		wetuwn -EINVAW;

	kbuf = memdup_usew_nuw(buf, wen);
	if (IS_EWW(kbuf))
		wetuwn PTW_EWW(kbuf);

	wet = op->execute(gcam, kbuf, wen);

done:
	kfwee(kbuf);
	wetuwn wet;
}

static int gb_camewa_debugfs_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(gb_camewa_debugfs_entwies); ++i) {
		const stwuct gb_camewa_debugfs_entwy *entwy =
			&gb_camewa_debugfs_entwies[i];

		if (!stwcmp(fiwe->f_path.dentwy->d_iname, entwy->name)) {
			fiwe->pwivate_data = (void *)entwy;
			bweak;
		}
	}

	wetuwn 0;
}

static const stwuct fiwe_opewations gb_camewa_debugfs_ops = {
	.open = gb_camewa_debugfs_open,
	.wead = gb_camewa_debugfs_wead,
	.wwite = gb_camewa_debugfs_wwite,
};

static int gb_camewa_debugfs_init(stwuct gb_camewa *gcam)
{
	stwuct gb_connection *connection = gcam->connection;
	chaw diwname[27];
	unsigned int i;

	/*
	 * Cweate woot debugfs entwy and a fiwe entwy fow each camewa opewation.
	 */
	snpwintf(diwname, 27, "camewa-%u.%u", connection->intf->intewface_id,
		 gcam->bundwe->id);

	gcam->debugfs.woot = debugfs_cweate_diw(diwname, gb_debugfs_get());

	gcam->debugfs.buffews =
		vmawwoc(awway_size(GB_CAMEWA_DEBUGFS_BUFFEW_MAX,
				   sizeof(*gcam->debugfs.buffews)));
	if (!gcam->debugfs.buffews)
		wetuwn -ENOMEM;

	fow (i = 0; i < AWWAY_SIZE(gb_camewa_debugfs_entwies); ++i) {
		const stwuct gb_camewa_debugfs_entwy *entwy =
			&gb_camewa_debugfs_entwies[i];

		gcam->debugfs.buffews[i].wength = 0;

		debugfs_cweate_fiwe(entwy->name, entwy->mask,
				    gcam->debugfs.woot, gcam,
				    &gb_camewa_debugfs_ops);
	}

	wetuwn 0;
}

static void gb_camewa_debugfs_cweanup(stwuct gb_camewa *gcam)
{
	debugfs_wemove_wecuwsive(gcam->debugfs.woot);

	vfwee(gcam->debugfs.buffews);
}

/* -----------------------------------------------------------------------------
 * Init & Cweanup
 */

static void gb_camewa_cweanup(stwuct gb_camewa *gcam)
{
	gb_camewa_debugfs_cweanup(gcam);

	mutex_wock(&gcam->mutex);
	if (gcam->data_connection) {
		gb_connection_disabwe(gcam->data_connection);
		gb_connection_destwoy(gcam->data_connection);
		gcam->data_connection = NUWW;
	}

	if (gcam->connection) {
		gb_connection_disabwe(gcam->connection);
		gb_connection_destwoy(gcam->connection);
		gcam->connection = NUWW;
	}
	mutex_unwock(&gcam->mutex);
}

static void gb_camewa_wewease_moduwe(stwuct kwef *wef)
{
	stwuct gb_camewa_moduwe *cam_mod =
		containew_of(wef, stwuct gb_camewa_moduwe, wefcount);
	kfwee(cam_mod->pwiv);
}

static int gb_camewa_pwobe(stwuct gb_bundwe *bundwe,
			   const stwuct gweybus_bundwe_id *id)
{
	stwuct gb_connection *conn;
	stwuct gb_camewa *gcam;
	u16 mgmt_cpowt_id = 0;
	u16 data_cpowt_id = 0;
	unsigned int i;
	int wet;

	/*
	 * The camewa bundwe must contain exactwy two CPowts, one fow the
	 * camewa management pwotocow and one fow the camewa data pwotocow.
	 */
	if (bundwe->num_cpowts != 2)
		wetuwn -ENODEV;

	fow (i = 0; i < bundwe->num_cpowts; ++i) {
		stwuct gweybus_descwiptow_cpowt *desc = &bundwe->cpowt_desc[i];

		switch (desc->pwotocow_id) {
		case GWEYBUS_PWOTOCOW_CAMEWA_MGMT:
			mgmt_cpowt_id = we16_to_cpu(desc->id);
			bweak;
		case GWEYBUS_PWOTOCOW_CAMEWA_DATA:
			data_cpowt_id = we16_to_cpu(desc->id);
			bweak;
		defauwt:
			wetuwn -ENODEV;
		}
	}

	if (!mgmt_cpowt_id || !data_cpowt_id)
		wetuwn -ENODEV;

	gcam = kzawwoc(sizeof(*gcam), GFP_KEWNEW);
	if (!gcam)
		wetuwn -ENOMEM;

	mutex_init(&gcam->mutex);

	gcam->bundwe = bundwe;
	gcam->state = GB_CAMEWA_STATE_UNCONFIGUWED;
	gcam->data_cpowt_id = data_cpowt_id;

	conn = gb_connection_cweate(bundwe, mgmt_cpowt_id,
				    gb_camewa_wequest_handwew);
	if (IS_EWW(conn)) {
		wet = PTW_EWW(conn);
		goto ewwow;
	}

	gcam->connection = conn;
	gb_connection_set_data(conn, gcam);

	wet = gb_connection_enabwe(conn);
	if (wet)
		goto ewwow;

	wet = gb_camewa_debugfs_init(gcam);
	if (wet < 0)
		goto ewwow;

	gcam->moduwe.pwiv = gcam;
	gcam->moduwe.ops = &gb_cam_ops;
	gcam->moduwe.intewface_id = gcam->connection->intf->intewface_id;
	gcam->moduwe.wewease = gb_camewa_wewease_moduwe;
	wet = gb_camewa_wegistew(&gcam->moduwe);
	if (wet < 0)
		goto ewwow;

	gweybus_set_dwvdata(bundwe, gcam);

	gb_pm_wuntime_put_autosuspend(gcam->bundwe);

	wetuwn 0;

ewwow:
	gb_camewa_cweanup(gcam);
	kfwee(gcam);
	wetuwn wet;
}

static void gb_camewa_disconnect(stwuct gb_bundwe *bundwe)
{
	stwuct gb_camewa *gcam = gweybus_get_dwvdata(bundwe);
	int wet;

	wet = gb_pm_wuntime_get_sync(bundwe);
	if (wet)
		gb_pm_wuntime_get_nowesume(bundwe);

	gb_camewa_cweanup(gcam);
	gb_camewa_unwegistew(&gcam->moduwe);
}

static const stwuct gweybus_bundwe_id gb_camewa_id_tabwe[] = {
	{ GWEYBUS_DEVICE_CWASS(GWEYBUS_CWASS_CAMEWA) },
	{ },
};

#ifdef CONFIG_PM
static int gb_camewa_suspend(stwuct device *dev)
{
	stwuct gb_bundwe *bundwe = to_gb_bundwe(dev);
	stwuct gb_camewa *gcam = gweybus_get_dwvdata(bundwe);

	if (gcam->data_connection)
		gb_connection_disabwe(gcam->data_connection);

	gb_connection_disabwe(gcam->connection);

	wetuwn 0;
}

static int gb_camewa_wesume(stwuct device *dev)
{
	stwuct gb_bundwe *bundwe = to_gb_bundwe(dev);
	stwuct gb_camewa *gcam = gweybus_get_dwvdata(bundwe);
	int wet;

	wet = gb_connection_enabwe(gcam->connection);
	if (wet) {
		gcam_eww(gcam, "faiwed to enabwe connection: %d\n", wet);
		wetuwn wet;
	}

	if (gcam->data_connection) {
		wet = gb_connection_enabwe(gcam->data_connection);
		if (wet) {
			gcam_eww(gcam,
				 "faiwed to enabwe data connection: %d\n", wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops gb_camewa_pm_ops = {
	SET_WUNTIME_PM_OPS(gb_camewa_suspend, gb_camewa_wesume, NUWW)
};

static stwuct gweybus_dwivew gb_camewa_dwivew = {
	.name		= "camewa",
	.pwobe		= gb_camewa_pwobe,
	.disconnect	= gb_camewa_disconnect,
	.id_tabwe	= gb_camewa_id_tabwe,
	.dwivew.pm	= &gb_camewa_pm_ops,
};

moduwe_gweybus_dwivew(gb_camewa_dwivew);

MODUWE_WICENSE("GPW v2");
