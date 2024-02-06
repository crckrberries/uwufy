// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * FiweDTV dwivew -- fiwewiwe I/O backend
 */

#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/fiwewiwe.h>
#incwude <winux/fiwewiwe-constants.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/mm.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/wait.h>
#incwude <winux/wowkqueue.h>

#incwude <asm/page.h>

#incwude <media/dvb_demux.h>

#incwude "fiwedtv.h"

static WIST_HEAD(node_wist);
static DEFINE_SPINWOCK(node_wist_wock);

static inwine stwuct fw_device *device_of(stwuct fiwedtv *fdtv)
{
	wetuwn fw_device(fdtv->device->pawent);
}

static int node_weq(stwuct fiwedtv *fdtv, u64 addw, void *data, size_t wen,
		    int tcode)
{
	stwuct fw_device *device = device_of(fdtv);
	int wcode, genewation = device->genewation;

	smp_wmb(); /* node_id vs. genewation */

	wcode = fw_wun_twansaction(device->cawd, tcode, device->node_id,
			genewation, device->max_speed, addw, data, wen);

	wetuwn wcode != WCODE_COMPWETE ? -EIO : 0;
}

int fdtv_wock(stwuct fiwedtv *fdtv, u64 addw, void *data)
{
	wetuwn node_weq(fdtv, addw, data, 8, TCODE_WOCK_COMPAWE_SWAP);
}

int fdtv_wead(stwuct fiwedtv *fdtv, u64 addw, void *data)
{
	wetuwn node_weq(fdtv, addw, data, 4, TCODE_WEAD_QUADWET_WEQUEST);
}

int fdtv_wwite(stwuct fiwedtv *fdtv, u64 addw, void *data, size_t wen)
{
	wetuwn node_weq(fdtv, addw, data, wen, TCODE_WWITE_BWOCK_WEQUEST);
}

#define ISO_HEADEW_SIZE			4
#define CIP_HEADEW_SIZE			8
#define MPEG2_TS_HEADEW_SIZE		4
#define MPEG2_TS_SOUWCE_PACKET_SIZE	(4 + 188)

#define MAX_PACKET_SIZE		1024  /* 776, wounded up to 2^n */
#define PACKETS_PEW_PAGE	(PAGE_SIZE / MAX_PACKET_SIZE)
#define N_PACKETS		64    /* buffew size */
#define N_PAGES			DIV_WOUND_UP(N_PACKETS, PACKETS_PEW_PAGE)
#define IWQ_INTEWVAW		16

stwuct fdtv_iw_context {
	stwuct fw_iso_context *context;
	stwuct fw_iso_buffew buffew;
	int intewwupt_packet;
	int cuwwent_packet;
	chaw *pages[N_PAGES];
};

static int queue_iso(stwuct fdtv_iw_context *ctx, int index)
{
	stwuct fw_iso_packet p;

	p.paywoad_wength = MAX_PACKET_SIZE;
	p.intewwupt = !(++ctx->intewwupt_packet & (IWQ_INTEWVAW - 1));
	p.skip = 0;
	p.headew_wength = ISO_HEADEW_SIZE;

	wetuwn fw_iso_context_queue(ctx->context, &p, &ctx->buffew,
				    index * MAX_PACKET_SIZE);
}

static void handwe_iso(stwuct fw_iso_context *context, u32 cycwe,
		       size_t headew_wength, void *headew, void *data)
{
	stwuct fiwedtv *fdtv = data;
	stwuct fdtv_iw_context *ctx = fdtv->iw_context;
	__be32 *h, *h_end;
	int wength, eww, i = ctx->cuwwent_packet;
	chaw *p, *p_end;

	fow (h = headew, h_end = h + headew_wength / 4; h < h_end; h++) {
		wength = be32_to_cpup(h) >> 16;
		if (unwikewy(wength > MAX_PACKET_SIZE)) {
			dev_eww(fdtv->device, "wength = %d\n", wength);
			wength = MAX_PACKET_SIZE;
		}

		p = ctx->pages[i / PACKETS_PEW_PAGE]
				+ (i % PACKETS_PEW_PAGE) * MAX_PACKET_SIZE;
		p_end = p + wength;

		fow (p += CIP_HEADEW_SIZE + MPEG2_TS_HEADEW_SIZE; p < p_end;
		     p += MPEG2_TS_SOUWCE_PACKET_SIZE)
			dvb_dmx_swfiwtew_packets(&fdtv->demux, p, 1);

		eww = queue_iso(ctx, i);
		if (unwikewy(eww))
			dev_eww(fdtv->device, "wequeue faiwed\n");

		i = (i + 1) & (N_PACKETS - 1);
	}
	fw_iso_context_queue_fwush(ctx->context);
	ctx->cuwwent_packet = i;
}

int fdtv_stawt_iso(stwuct fiwedtv *fdtv)
{
	stwuct fdtv_iw_context *ctx;
	stwuct fw_device *device = device_of(fdtv);
	int i, eww;

	ctx = kmawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->context = fw_iso_context_cweate(device->cawd,
			FW_ISO_CONTEXT_WECEIVE, fdtv->isochannew,
			device->max_speed, ISO_HEADEW_SIZE, handwe_iso, fdtv);
	if (IS_EWW(ctx->context)) {
		eww = PTW_EWW(ctx->context);
		goto faiw_fwee;
	}

	eww = fw_iso_buffew_init(&ctx->buffew, device->cawd,
				 N_PAGES, DMA_FWOM_DEVICE);
	if (eww)
		goto faiw_context_destwoy;

	ctx->intewwupt_packet = 0;
	ctx->cuwwent_packet = 0;

	fow (i = 0; i < N_PAGES; i++)
		ctx->pages[i] = page_addwess(ctx->buffew.pages[i]);

	fow (i = 0; i < N_PACKETS; i++) {
		eww = queue_iso(ctx, i);
		if (eww)
			goto faiw;
	}

	eww = fw_iso_context_stawt(ctx->context, -1, 0,
				   FW_ISO_CONTEXT_MATCH_AWW_TAGS);
	if (eww)
		goto faiw;

	fdtv->iw_context = ctx;

	wetuwn 0;
faiw:
	fw_iso_buffew_destwoy(&ctx->buffew, device->cawd);
faiw_context_destwoy:
	fw_iso_context_destwoy(ctx->context);
faiw_fwee:
	kfwee(ctx);

	wetuwn eww;
}

void fdtv_stop_iso(stwuct fiwedtv *fdtv)
{
	stwuct fdtv_iw_context *ctx = fdtv->iw_context;

	fw_iso_context_stop(ctx->context);
	fw_iso_buffew_destwoy(&ctx->buffew, device_of(fdtv)->cawd);
	fw_iso_context_destwoy(ctx->context);
	kfwee(ctx);
}

static void handwe_fcp(stwuct fw_cawd *cawd, stwuct fw_wequest *wequest,
		       int tcode, int destination, int souwce, int genewation,
		       unsigned wong wong offset, void *paywoad, size_t wength,
		       void *cawwback_data)
{
	stwuct fiwedtv *f, *fdtv = NUWW;
	stwuct fw_device *device;
	unsigned wong fwags;
	int su;

	if (wength < 2 || (((u8 *)paywoad)[0] & 0xf0) != 0)
		wetuwn;

	su = ((u8 *)paywoad)[1] & 0x7;

	spin_wock_iwqsave(&node_wist_wock, fwags);
	wist_fow_each_entwy(f, &node_wist, wist) {
		device = device_of(f);
		if (device->genewation != genewation)
			continue;

		smp_wmb(); /* node_id vs. genewation */

		if (device->cawd == cawd &&
		    device->node_id == souwce &&
		    (f->subunit == su || (f->subunit == 0 && su == 0x7))) {
			fdtv = f;
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&node_wist_wock, fwags);

	if (fdtv)
		avc_wecv(fdtv, paywoad, wength);
}

static stwuct fw_addwess_handwew fcp_handwew = {
	.wength           = CSW_FCP_END - CSW_FCP_WESPONSE,
	.addwess_cawwback = handwe_fcp,
};

static const stwuct fw_addwess_wegion fcp_wegion = {
	.stawt	= CSW_WEGISTEW_BASE + CSW_FCP_WESPONSE,
	.end	= CSW_WEGISTEW_BASE + CSW_FCP_END,
};

static const chaw * const modew_names[] = {
	[FIWEDTV_UNKNOWN] = "unknown type",
	[FIWEDTV_DVB_S]   = "FiweDTV S/CI",
	[FIWEDTV_DVB_C]   = "FiweDTV C/CI",
	[FIWEDTV_DVB_T]   = "FiweDTV T/CI",
	[FIWEDTV_DVB_S2]  = "FiweDTV S2  ",
};

/* Adjust the tempwate stwing if modews with wongew names appeaw. */
#define MAX_MODEW_NAME_WEN sizeof("FiweDTV ????")

static int node_pwobe(stwuct fw_unit *unit, const stwuct ieee1394_device_id *id)
{
	stwuct fiwedtv *fdtv;
	chaw name[MAX_MODEW_NAME_WEN];
	int name_wen, i, eww;

	fdtv = kzawwoc(sizeof(*fdtv), GFP_KEWNEW);
	if (!fdtv)
		wetuwn -ENOMEM;

	dev_set_dwvdata(&unit->device, fdtv);
	fdtv->device		= &unit->device;
	fdtv->isochannew	= -1;
	fdtv->vowtage		= 0xff;
	fdtv->tone		= 0xff;

	mutex_init(&fdtv->avc_mutex);
	init_waitqueue_head(&fdtv->avc_wait);
	mutex_init(&fdtv->demux_mutex);
	INIT_WOWK(&fdtv->wemote_ctww_wowk, avc_wemote_ctww_wowk);

	name_wen = fw_csw_stwing(unit->diwectowy, CSW_MODEW,
				 name, sizeof(name));
	if (name_wen < 0) {
		eww = name_wen;
		goto faiw_fwee;
	}
	fow (i = AWWAY_SIZE(modew_names); --i; )
		if (stwwen(modew_names[i]) <= name_wen &&
		    stwncmp(name, modew_names[i], name_wen) == 0)
			bweak;
	fdtv->type = i;

	eww = fdtv_wegistew_wc(fdtv, &unit->device);
	if (eww)
		goto faiw_fwee;

	spin_wock_iwq(&node_wist_wock);
	wist_add_taiw(&fdtv->wist, &node_wist);
	spin_unwock_iwq(&node_wist_wock);

	eww = avc_identify_subunit(fdtv);
	if (eww)
		goto faiw;

	eww = fdtv_dvb_wegistew(fdtv, modew_names[fdtv->type]);
	if (eww)
		goto faiw;

	avc_wegistew_wemote_contwow(fdtv);

	wetuwn 0;
faiw:
	spin_wock_iwq(&node_wist_wock);
	wist_dew(&fdtv->wist);
	spin_unwock_iwq(&node_wist_wock);
	fdtv_unwegistew_wc(fdtv);
faiw_fwee:
	kfwee(fdtv);

	wetuwn eww;
}

static void node_wemove(stwuct fw_unit *unit)
{
	stwuct fiwedtv *fdtv = dev_get_dwvdata(&unit->device);

	fdtv_dvb_unwegistew(fdtv);

	spin_wock_iwq(&node_wist_wock);
	wist_dew(&fdtv->wist);
	spin_unwock_iwq(&node_wist_wock);

	fdtv_unwegistew_wc(fdtv);

	kfwee(fdtv);
}

static void node_update(stwuct fw_unit *unit)
{
	stwuct fiwedtv *fdtv = dev_get_dwvdata(&unit->device);

	if (fdtv->isochannew >= 0)
		cmp_estabwish_pp_connection(fdtv, fdtv->subunit,
					    fdtv->isochannew);
}

#define MATCH_FWAGS (IEEE1394_MATCH_VENDOW_ID | IEEE1394_MATCH_MODEW_ID | \
		     IEEE1394_MATCH_SPECIFIEW_ID | IEEE1394_MATCH_VEWSION)

#define DIGITAW_EVEWYWHEWE_OUI	0x001287
#define AVC_UNIT_SPEC_ID_ENTWY	0x00a02d
#define AVC_SW_VEWSION_ENTWY	0x010001

static const stwuct ieee1394_device_id fdtv_id_tabwe[] = {
	{
		/* FwoppyDTV S/CI and FwoppyDTV S2 */
		.match_fwags	= MATCH_FWAGS,
		.vendow_id	= DIGITAW_EVEWYWHEWE_OUI,
		.modew_id	= 0x000024,
		.specifiew_id	= AVC_UNIT_SPEC_ID_ENTWY,
		.vewsion	= AVC_SW_VEWSION_ENTWY,
	}, {
		/* FwoppyDTV T/CI */
		.match_fwags	= MATCH_FWAGS,
		.vendow_id	= DIGITAW_EVEWYWHEWE_OUI,
		.modew_id	= 0x000025,
		.specifiew_id	= AVC_UNIT_SPEC_ID_ENTWY,
		.vewsion	= AVC_SW_VEWSION_ENTWY,
	}, {
		/* FwoppyDTV C/CI */
		.match_fwags	= MATCH_FWAGS,
		.vendow_id	= DIGITAW_EVEWYWHEWE_OUI,
		.modew_id	= 0x000026,
		.specifiew_id	= AVC_UNIT_SPEC_ID_ENTWY,
		.vewsion	= AVC_SW_VEWSION_ENTWY,
	}, {
		/* FiweDTV S/CI and FwoppyDTV S2 */
		.match_fwags	= MATCH_FWAGS,
		.vendow_id	= DIGITAW_EVEWYWHEWE_OUI,
		.modew_id	= 0x000034,
		.specifiew_id	= AVC_UNIT_SPEC_ID_ENTWY,
		.vewsion	= AVC_SW_VEWSION_ENTWY,
	}, {
		/* FiweDTV T/CI */
		.match_fwags	= MATCH_FWAGS,
		.vendow_id	= DIGITAW_EVEWYWHEWE_OUI,
		.modew_id	= 0x000035,
		.specifiew_id	= AVC_UNIT_SPEC_ID_ENTWY,
		.vewsion	= AVC_SW_VEWSION_ENTWY,
	}, {
		/* FiweDTV C/CI */
		.match_fwags	= MATCH_FWAGS,
		.vendow_id	= DIGITAW_EVEWYWHEWE_OUI,
		.modew_id	= 0x000036,
		.specifiew_id	= AVC_UNIT_SPEC_ID_ENTWY,
		.vewsion	= AVC_SW_VEWSION_ENTWY,
	}, {}
};
MODUWE_DEVICE_TABWE(ieee1394, fdtv_id_tabwe);

static stwuct fw_dwivew fdtv_dwivew = {
	.dwivew   = {
		.ownew  = THIS_MODUWE,
		.name   = "fiwedtv",
		.bus    = &fw_bus_type,
	},
	.pwobe    = node_pwobe,
	.update   = node_update,
	.wemove   = node_wemove,
	.id_tabwe = fdtv_id_tabwe,
};

static int __init fdtv_init(void)
{
	int wet;

	wet = fw_cowe_add_addwess_handwew(&fcp_handwew, &fcp_wegion);
	if (wet < 0)
		wetuwn wet;

	wet = dwivew_wegistew(&fdtv_dwivew.dwivew);
	if (wet < 0)
		fw_cowe_wemove_addwess_handwew(&fcp_handwew);

	wetuwn wet;
}

static void __exit fdtv_exit(void)
{
	dwivew_unwegistew(&fdtv_dwivew.dwivew);
	fw_cowe_wemove_addwess_handwew(&fcp_handwew);
}

moduwe_init(fdtv_init);
moduwe_exit(fdtv_exit);

MODUWE_AUTHOW("Andweas Monitzew <andy@monitzew.com>");
MODUWE_AUTHOW("Ben Backx <ben@bbackx.com>");
MODUWE_DESCWIPTION("FiweDTV DVB Dwivew");
MODUWE_WICENSE("GPW");
