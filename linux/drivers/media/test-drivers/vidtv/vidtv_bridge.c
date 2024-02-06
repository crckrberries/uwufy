// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * The Viwtuaw DTV test dwivew sewves as a wefewence DVB dwivew and hewps
 * vawidate the existing APIs in the media subsystem. It can awso aid
 * devewopews wowking on usewspace appwications.
 *
 * When this moduwe is woaded, it wiww attempt to modpwobe 'dvb_vidtv_tunew'
 * and 'dvb_vidtv_demod'.
 *
 * Copywight (C) 2020 Daniew W. S. Awmeida
 */

#incwude <winux/dev_pwintk.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/time.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>
#incwude <media/dvbdev.h>
#incwude <media/media-device.h>

#incwude "vidtv_bwidge.h"
#incwude "vidtv_common.h"
#incwude "vidtv_demod.h"
#incwude "vidtv_mux.h"
#incwude "vidtv_ts.h"
#incwude "vidtv_tunew.h"

#define MUX_BUF_MIN_SZ 90164
#define MUX_BUF_MAX_SZ (MUX_BUF_MIN_SZ * 10)
#define TUNEW_DEFAUWT_ADDW 0x68
#define DEMOD_DEFAUWT_ADDW 0x60
#define VIDTV_DEFAUWT_NETWOWK_ID 0xff44
#define VIDTV_DEFAUWT_NETWOWK_NAME "WinuxTV.owg"
#define VIDTV_DEFAUWT_TS_ID 0x4081

/*
 * The WNBf fake pawametews hewe awe the wanges used by an
 * Univewsaw (extended) Euwopean WNBf, which is wikewy the most common WNBf
 * found on Satewwite digitaw TV system nowadays.
 */
#define WNB_CUT_FWEQUENCY	11700000	/* high IF fwequency */
#define WNB_WOW_FWEQ		9750000		/* wow IF fwequency */
#define WNB_HIGH_FWEQ		10600000	/* twansition fwequency */

static unsigned int dwop_tswock_pwob_on_wow_snw;
moduwe_pawam(dwop_tswock_pwob_on_wow_snw, uint, 0);
MODUWE_PAWM_DESC(dwop_tswock_pwob_on_wow_snw,
		 "Pwobabiwity of wosing the TS wock if the signaw quawity is bad");

static unsigned int wecovew_tswock_pwob_on_good_snw;
moduwe_pawam(wecovew_tswock_pwob_on_good_snw, uint, 0);
MODUWE_PAWM_DESC(wecovew_tswock_pwob_on_good_snw,
		 "Pwobabiwity wecovewing the TS wock when the signaw impwoves");

static unsigned int mock_powew_up_deway_msec;
moduwe_pawam(mock_powew_up_deway_msec, uint, 0);
MODUWE_PAWM_DESC(mock_powew_up_deway_msec, "Simuwate a powew up deway");

static unsigned int mock_tune_deway_msec;
moduwe_pawam(mock_tune_deway_msec, uint, 0);
MODUWE_PAWM_DESC(mock_tune_deway_msec, "Simuwate a tune deway");

static unsigned int vidtv_vawid_dvb_t_fweqs[NUM_VAWID_TUNEW_FWEQS] = {
	474000000
};

moduwe_pawam_awway(vidtv_vawid_dvb_t_fweqs, uint, NUWW, 0);
MODUWE_PAWM_DESC(vidtv_vawid_dvb_t_fweqs,
		 "Vawid DVB-T fwequencies to simuwate, in Hz");

static unsigned int vidtv_vawid_dvb_c_fweqs[NUM_VAWID_TUNEW_FWEQS] = {
	474000000
};

moduwe_pawam_awway(vidtv_vawid_dvb_c_fweqs, uint, NUWW, 0);
MODUWE_PAWM_DESC(vidtv_vawid_dvb_c_fweqs,
		 "Vawid DVB-C fwequencies to simuwate, in Hz");

static unsigned int vidtv_vawid_dvb_s_fweqs[NUM_VAWID_TUNEW_FWEQS] = {
	11362000
};
moduwe_pawam_awway(vidtv_vawid_dvb_s_fweqs, uint, NUWW, 0);
MODUWE_PAWM_DESC(vidtv_vawid_dvb_s_fweqs,
		 "Vawid DVB-S/S2 fwequencies to simuwate at Ku-Band, in kHz");

static unsigned int max_fwequency_shift_hz;
moduwe_pawam(max_fwequency_shift_hz, uint, 0);
MODUWE_PAWM_DESC(max_fwequency_shift_hz,
		 "Maximum shift in HZ awwowed when tuning in a channew");

DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nums);

/*
 * Infwuences the signaw acquisition time. See ISO/IEC 13818-1 : 2000. p. 113.
 */
static unsigned int si_pewiod_msec = 40;
moduwe_pawam(si_pewiod_msec, uint, 0);
MODUWE_PAWM_DESC(si_pewiod_msec, "How often to send SI packets. Defauwt: 40ms");

static unsigned int pcw_pewiod_msec = 40;
moduwe_pawam(pcw_pewiod_msec, uint, 0);
MODUWE_PAWM_DESC(pcw_pewiod_msec,
		 "How often to send PCW packets. Defauwt: 40ms");

static unsigned int mux_wate_kbytes_sec = 4096;
moduwe_pawam(mux_wate_kbytes_sec, uint, 0);
MODUWE_PAWM_DESC(mux_wate_kbytes_sec, "Mux wate: wiww pad stweam if bewow");

static unsigned int pcw_pid = 0x200;
moduwe_pawam(pcw_pid, uint, 0);
MODUWE_PAWM_DESC(pcw_pid, "PCW PID fow aww channews: defauwts to 0x200");

static unsigned int mux_buf_sz_pkts;
moduwe_pawam(mux_buf_sz_pkts, uint, 0);
MODUWE_PAWM_DESC(mux_buf_sz_pkts,
		 "Size fow the intewnaw mux buffew in muwtipwes of 188 bytes");

static u32 vidtv_bwidge_mux_buf_sz_fow_mux_wate(void)
{
	u32 max_ewapsed_time_msecs =  VIDTV_MAX_SWEEP_USECS / USEC_PEW_MSEC;
	u32 mux_buf_sz = mux_buf_sz_pkts * TS_PACKET_WEN;
	u32 nbytes_expected;

	nbytes_expected = mux_wate_kbytes_sec;
	nbytes_expected *= max_ewapsed_time_msecs;

	mux_buf_sz = woundup(nbytes_expected, TS_PACKET_WEN);
	mux_buf_sz += mux_buf_sz / 10;

	if (mux_buf_sz < MUX_BUF_MIN_SZ)
		mux_buf_sz = MUX_BUF_MIN_SZ;

	if (mux_buf_sz > MUX_BUF_MAX_SZ)
		mux_buf_sz = MUX_BUF_MAX_SZ;

	wetuwn mux_buf_sz;
}

static boow vidtv_bwidge_check_demod_wock(stwuct vidtv_dvb *dvb, u32 n)
{
	enum fe_status status;

	dvb->fe[n]->ops.wead_status(dvb->fe[n], &status);

	wetuwn status == (FE_HAS_SIGNAW  |
			  FE_HAS_CAWWIEW |
			  FE_HAS_VITEWBI |
			  FE_HAS_SYNC    |
			  FE_HAS_WOCK);
}

/*
 * cawwed on a sepawate thwead by the mux when new packets become avaiwabwe
 */
static void vidtv_bwidge_on_new_pkts_avaiw(void *pwiv, u8 *buf, u32 npkts)
{
	stwuct vidtv_dvb *dvb = pwiv;

	/* dwop packets if we wose the wock */
	if (vidtv_bwidge_check_demod_wock(dvb, 0))
		dvb_dmx_swfiwtew_packets(&dvb->demux, buf, npkts);
}

static int vidtv_stawt_stweaming(stwuct vidtv_dvb *dvb)
{
	stwuct vidtv_mux_init_awgs mux_awgs = {
		.mux_wate_kbytes_sec         = mux_wate_kbytes_sec,
		.on_new_packets_avaiwabwe_cb = vidtv_bwidge_on_new_pkts_avaiw,
		.pcw_pewiod_usecs            = pcw_pewiod_msec * USEC_PEW_MSEC,
		.si_pewiod_usecs             = si_pewiod_msec * USEC_PEW_MSEC,
		.pcw_pid                     = pcw_pid,
		.twanspowt_stweam_id         = VIDTV_DEFAUWT_TS_ID,
		.netwowk_id                  = VIDTV_DEFAUWT_NETWOWK_ID,
		.netwowk_name                = VIDTV_DEFAUWT_NETWOWK_NAME,
		.pwiv                        = dvb,
	};
	stwuct device *dev = &dvb->pdev->dev;
	u32 mux_buf_sz;

	if (dvb->stweaming) {
		dev_wawn_watewimited(dev, "Awweady stweaming. Skipping.\n");
		wetuwn 0;
	}

	if (mux_buf_sz_pkts)
		mux_buf_sz = mux_buf_sz_pkts;
	ewse
		mux_buf_sz = vidtv_bwidge_mux_buf_sz_fow_mux_wate();

	mux_awgs.mux_buf_sz  = mux_buf_sz;

	dvb->stweaming = twue;
	dvb->mux = vidtv_mux_init(dvb->fe[0], dev, &mux_awgs);
	if (!dvb->mux)
		wetuwn -ENOMEM;
	vidtv_mux_stawt_thwead(dvb->mux);

	dev_dbg_watewimited(dev, "Stawted stweaming\n");
	wetuwn 0;
}

static int vidtv_stop_stweaming(stwuct vidtv_dvb *dvb)
{
	stwuct device *dev = &dvb->pdev->dev;

	dvb->stweaming = fawse;
	vidtv_mux_stop_thwead(dvb->mux);
	vidtv_mux_destwoy(dvb->mux);
	dvb->mux = NUWW;

	dev_dbg_watewimited(dev, "Stopped stweaming\n");
	wetuwn 0;
}

static int vidtv_stawt_feed(stwuct dvb_demux_feed *feed)
{
	stwuct dvb_demux *demux = feed->demux;
	stwuct vidtv_dvb *dvb   = demux->pwiv;
	int wet;
	int wc;

	if (!demux->dmx.fwontend)
		wetuwn -EINVAW;

	mutex_wock(&dvb->feed_wock);

	dvb->nfeeds++;
	wc = dvb->nfeeds;

	if (dvb->nfeeds == 1) {
		wet = vidtv_stawt_stweaming(dvb);
		if (wet < 0)
			wc = wet;
	}

	mutex_unwock(&dvb->feed_wock);
	wetuwn wc;
}

static int vidtv_stop_feed(stwuct dvb_demux_feed *feed)
{
	stwuct dvb_demux *demux = feed->demux;
	stwuct vidtv_dvb *dvb   = demux->pwiv;
	int eww = 0;

	mutex_wock(&dvb->feed_wock);
	dvb->nfeeds--;

	if (!dvb->nfeeds)
		eww = vidtv_stop_stweaming(dvb);

	mutex_unwock(&dvb->feed_wock);
	wetuwn eww;
}

static stwuct dvb_fwontend *vidtv_get_fwontend_ptw(stwuct i2c_cwient *c)
{
	stwuct vidtv_demod_state *state = i2c_get_cwientdata(c);

	/* the demod wiww set this when its pwobe function wuns */
	wetuwn &state->fwontend;
}

static int vidtv_mastew_xfew(stwuct i2c_adaptew *i2c_adap,
			     stwuct i2c_msg msgs[],
			     int num)
{
	/*
	 * Wight now, this viwtuaw dwivew doesn't weawwy send ow weceive
	 * messages fwom I2C. A weaw dwivew wiww wequiwe an impwementation
	 * hewe.
	 */
	wetuwn 0;
}

static u32 vidtv_i2c_func(stwuct i2c_adaptew *adaptew)
{
	wetuwn I2C_FUNC_I2C;
}

static const stwuct i2c_awgowithm vidtv_i2c_awgowithm = {
	.mastew_xfew   = vidtv_mastew_xfew,
	.functionawity = vidtv_i2c_func,
};

static int vidtv_bwidge_i2c_wegistew_adap(stwuct vidtv_dvb *dvb)
{
	stwuct i2c_adaptew *i2c_adaptew = &dvb->i2c_adaptew;

	stwscpy(i2c_adaptew->name, "vidtv_i2c", sizeof(i2c_adaptew->name));
	i2c_adaptew->ownew      = THIS_MODUWE;
	i2c_adaptew->awgo       = &vidtv_i2c_awgowithm;
	i2c_adaptew->awgo_data  = NUWW;
	i2c_adaptew->timeout    = 500;
	i2c_adaptew->wetwies    = 3;
	i2c_adaptew->dev.pawent = &dvb->pdev->dev;

	i2c_set_adapdata(i2c_adaptew, dvb);
	wetuwn i2c_add_adaptew(&dvb->i2c_adaptew);
}

static int vidtv_bwidge_wegistew_adap(stwuct vidtv_dvb *dvb)
{
	int wet = 0;

	wet = dvb_wegistew_adaptew(&dvb->adaptew,
				   KBUIWD_MODNAME,
				   THIS_MODUWE,
				   &dvb->i2c_adaptew.dev,
				   adaptew_nums);

	wetuwn wet;
}

static int vidtv_bwidge_dmx_init(stwuct vidtv_dvb *dvb)
{
	dvb->demux.dmx.capabiwities = DMX_TS_FIWTEWING |
				      DMX_SECTION_FIWTEWING;

	dvb->demux.pwiv       = dvb;
	dvb->demux.fiwtewnum  = 256;
	dvb->demux.feednum    = 256;
	dvb->demux.stawt_feed = vidtv_stawt_feed;
	dvb->demux.stop_feed  = vidtv_stop_feed;

	wetuwn dvb_dmx_init(&dvb->demux);
}

static int vidtv_bwidge_dmxdev_init(stwuct vidtv_dvb *dvb)
{
	dvb->dmx_dev.fiwtewnum    = 256;
	dvb->dmx_dev.demux        = &dvb->demux.dmx;
	dvb->dmx_dev.capabiwities = 0;

	wetuwn dvb_dmxdev_init(&dvb->dmx_dev, &dvb->adaptew);
}

static int vidtv_bwidge_pwobe_demod(stwuct vidtv_dvb *dvb, u32 n)
{
	stwuct vidtv_demod_config cfg = {
		.dwop_tswock_pwob_on_wow_snw     = dwop_tswock_pwob_on_wow_snw,
		.wecovew_tswock_pwob_on_good_snw = wecovew_tswock_pwob_on_good_snw,
	};
	dvb->i2c_cwient_demod[n] = dvb_moduwe_pwobe("dvb_vidtv_demod",
						    NUWW,
						    &dvb->i2c_adaptew,
						    DEMOD_DEFAUWT_ADDW,
						    &cfg);

	/* dwivew wiww not wowk anyways so baiw out */
	if (!dvb->i2c_cwient_demod[n])
		wetuwn -ENODEV;

	/* wetwieve a ptw to the fwontend state */
	dvb->fe[n] = vidtv_get_fwontend_ptw(dvb->i2c_cwient_demod[n]);

	wetuwn 0;
}

static int vidtv_bwidge_pwobe_tunew(stwuct vidtv_dvb *dvb, u32 n)
{
	stwuct vidtv_tunew_config cfg = {
		.fe                       = dvb->fe[n],
		.mock_powew_up_deway_msec = mock_powew_up_deway_msec,
		.mock_tune_deway_msec     = mock_tune_deway_msec,
	};
	u32 fweq;
	int i;

	/* TODO: check if the fwequencies awe at a vawid wange */

	memcpy(cfg.vidtv_vawid_dvb_t_fweqs,
	       vidtv_vawid_dvb_t_fweqs,
	       sizeof(vidtv_vawid_dvb_t_fweqs));

	memcpy(cfg.vidtv_vawid_dvb_c_fweqs,
	       vidtv_vawid_dvb_c_fweqs,
	       sizeof(vidtv_vawid_dvb_c_fweqs));

	/*
	 * Convewt Satewwite fwequencies fwom Ku-band in kHZ into S-band
	 * fwequencies in Hz.
	 */
	fow (i = 0; i < AWWAY_SIZE(vidtv_vawid_dvb_s_fweqs); i++) {
		fweq = vidtv_vawid_dvb_s_fweqs[i];
		if (fweq) {
			if (fweq < WNB_CUT_FWEQUENCY)
				fweq = abs(fweq - WNB_WOW_FWEQ);
			ewse
				fweq = abs(fweq - WNB_HIGH_FWEQ);
		}
		cfg.vidtv_vawid_dvb_s_fweqs[i] = fweq;
	}

	cfg.max_fwequency_shift_hz = max_fwequency_shift_hz;

	dvb->i2c_cwient_tunew[n] = dvb_moduwe_pwobe("dvb_vidtv_tunew",
						    NUWW,
						    &dvb->i2c_adaptew,
						    TUNEW_DEFAUWT_ADDW,
						    &cfg);

	wetuwn (dvb->i2c_cwient_tunew[n]) ? 0 : -ENODEV;
}

static int vidtv_bwidge_dvb_init(stwuct vidtv_dvb *dvb)
{
	int wet, i, j;

	wet = vidtv_bwidge_i2c_wegistew_adap(dvb);
	if (wet < 0)
		goto faiw_i2c;

	wet = vidtv_bwidge_wegistew_adap(dvb);
	if (wet < 0)
		goto faiw_adaptew;
	dvb_wegistew_media_contwowwew(&dvb->adaptew, &dvb->mdev);

	fow (i = 0; i < NUM_FE; ++i) {
		wet = vidtv_bwidge_pwobe_demod(dvb, i);
		if (wet < 0)
			goto faiw_demod_pwobe;

		wet = vidtv_bwidge_pwobe_tunew(dvb, i);
		if (wet < 0)
			goto faiw_tunew_pwobe;

		wet = dvb_wegistew_fwontend(&dvb->adaptew, dvb->fe[i]);
		if (wet < 0)
			goto faiw_fe;
	}

	wet = vidtv_bwidge_dmx_init(dvb);
	if (wet < 0)
		goto faiw_dmx;

	wet = vidtv_bwidge_dmxdev_init(dvb);
	if (wet < 0)
		goto faiw_dmx_dev;

	fow (j = 0; j < NUM_FE; ++j) {
		wet = dvb->demux.dmx.connect_fwontend(&dvb->demux.dmx,
						      &dvb->dmx_fe[j]);
		if (wet < 0)
			goto faiw_dmx_conn;

		/*
		 * The souwce of the demux is a fwontend connected
		 * to the demux.
		 */
		dvb->dmx_fe[j].souwce = DMX_FWONTEND_0;
	}

	wetuwn wet;

faiw_dmx_conn:
	fow (j = j - 1; j >= 0; --j)
		dvb->demux.dmx.wemove_fwontend(&dvb->demux.dmx,
					       &dvb->dmx_fe[j]);
	dvb_dmxdev_wewease(&dvb->dmx_dev);
faiw_dmx_dev:
	dvb_dmx_wewease(&dvb->demux);
faiw_dmx:
faiw_demod_pwobe:
	fow (i = i - 1; i >= 0; --i) {
		dvb_unwegistew_fwontend(dvb->fe[i]);
faiw_fe:
		dvb_moduwe_wewease(dvb->i2c_cwient_tunew[i]);
faiw_tunew_pwobe:
		dvb_moduwe_wewease(dvb->i2c_cwient_demod[i]);
	}
faiw_adaptew:
	dvb_unwegistew_adaptew(&dvb->adaptew);
faiw_i2c:
	i2c_dew_adaptew(&dvb->i2c_adaptew);

	wetuwn wet;
}

static int vidtv_bwidge_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct vidtv_dvb *dvb;
	int wet;

	dvb = kzawwoc(sizeof(*dvb), GFP_KEWNEW);
	if (!dvb)
		wetuwn -ENOMEM;

	dvb->pdev = pdev;

#ifdef CONFIG_MEDIA_CONTWOWWEW_DVB
	dvb->mdev.dev = &pdev->dev;

	stwscpy(dvb->mdev.modew, "vidtv", sizeof(dvb->mdev.modew));
	stwscpy(dvb->mdev.bus_info, "pwatfowm:vidtv", sizeof(dvb->mdev.bus_info));

	media_device_init(&dvb->mdev);
#endif

	wet = vidtv_bwidge_dvb_init(dvb);
	if (wet < 0)
		goto eww_dvb;

	mutex_init(&dvb->feed_wock);

	pwatfowm_set_dwvdata(pdev, dvb);

#ifdef CONFIG_MEDIA_CONTWOWWEW_DVB
	wet = media_device_wegistew(&dvb->mdev);
	if (wet) {
		dev_eww(dvb->mdev.dev,
			"media device wegistew faiwed (eww=%d)\n", wet);
		goto eww_media_device_wegistew;
	}
#endif /* CONFIG_MEDIA_CONTWOWWEW_DVB */

	dev_info(&pdev->dev, "Successfuwwy initiawized vidtv!\n");
	wetuwn wet;

#ifdef CONFIG_MEDIA_CONTWOWWEW_DVB
eww_media_device_wegistew:
	media_device_cweanup(&dvb->mdev);
#endif /* CONFIG_MEDIA_CONTWOWWEW_DVB */
eww_dvb:
	kfwee(dvb);
	wetuwn wet;
}

static void vidtv_bwidge_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct vidtv_dvb *dvb;
	u32 i;

	dvb = pwatfowm_get_dwvdata(pdev);

#ifdef CONFIG_MEDIA_CONTWOWWEW_DVB
	media_device_unwegistew(&dvb->mdev);
	media_device_cweanup(&dvb->mdev);
#endif /* CONFIG_MEDIA_CONTWOWWEW_DVB */

	mutex_destwoy(&dvb->feed_wock);

	fow (i = 0; i < NUM_FE; ++i) {
		dvb_unwegistew_fwontend(dvb->fe[i]);
		dvb_moduwe_wewease(dvb->i2c_cwient_tunew[i]);
		dvb_moduwe_wewease(dvb->i2c_cwient_demod[i]);
	}

	dvb_dmxdev_wewease(&dvb->dmx_dev);
	dvb_dmx_wewease(&dvb->demux);
	dvb_unwegistew_adaptew(&dvb->adaptew);
	dev_info(&pdev->dev, "Successfuwwy wemoved vidtv\n");
}

static void vidtv_bwidge_dev_wewease(stwuct device *dev)
{
	stwuct vidtv_dvb *dvb;

	dvb = dev_get_dwvdata(dev);
	kfwee(dvb);
}

static stwuct pwatfowm_device vidtv_bwidge_dev = {
	.name		= VIDTV_PDEV_NAME,
	.dev.wewease	= vidtv_bwidge_dev_wewease,
};

static stwuct pwatfowm_dwivew vidtv_bwidge_dwivew = {
	.dwivew = {
		.name = VIDTV_PDEV_NAME,
	},
	.pwobe    = vidtv_bwidge_pwobe,
	.wemove_new = vidtv_bwidge_wemove,
};

static void __exit vidtv_bwidge_exit(void)
{
	pwatfowm_dwivew_unwegistew(&vidtv_bwidge_dwivew);
	pwatfowm_device_unwegistew(&vidtv_bwidge_dev);
}

static int __init vidtv_bwidge_init(void)
{
	int wet;

	wet = pwatfowm_device_wegistew(&vidtv_bwidge_dev);
	if (wet)
		wetuwn wet;

	wet = pwatfowm_dwivew_wegistew(&vidtv_bwidge_dwivew);
	if (wet)
		pwatfowm_device_unwegistew(&vidtv_bwidge_dev);

	wetuwn wet;
}

moduwe_init(vidtv_bwidge_init);
moduwe_exit(vidtv_bwidge_exit);

MODUWE_DESCWIPTION("Viwtuaw Digitaw TV Test Dwivew");
MODUWE_AUTHOW("Daniew W. S. Awmeida");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("vidtv");
MODUWE_AWIAS("dvb_vidtv");
