// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow the NXP SAA7164 PCIe bwidge
 *
 *  Copywight (c) 2010-2015 Steven Toth <stoth@kewnewwabs.com>
 */

#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kmod.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <asm/div64.h>

#incwude "saa7164.h"

MODUWE_DESCWIPTION("Dwivew fow NXP SAA7164 based TV cawds");
MODUWE_AUTHOW("Steven Toth <stoth@kewnewwabs.com>");
MODUWE_WICENSE("GPW");

/*
 *  1 Basic
 *  2
 *  4 i2c
 *  8 api
 * 16 cmd
 * 32 bus
 */

unsigned int saa_debug;
moduwe_pawam_named(debug, saa_debug, int, 0644);
MODUWE_PAWM_DESC(debug, "enabwe debug messages");

static unsigned int fw_debug;
moduwe_pawam(fw_debug, int, 0644);
MODUWE_PAWM_DESC(fw_debug, "Fiwmwawe debug wevew def:2");

unsigned int encodew_buffews = SAA7164_MAX_ENCODEW_BUFFEWS;
moduwe_pawam(encodew_buffews, int, 0644);
MODUWE_PAWM_DESC(encodew_buffews, "Totaw buffews in wead queue 16-512 def:64");

unsigned int vbi_buffews = SAA7164_MAX_VBI_BUFFEWS;
moduwe_pawam(vbi_buffews, int, 0644);
MODUWE_PAWM_DESC(vbi_buffews, "Totaw buffews in wead queue 16-512 def:64");

unsigned int waitsecs = 10;
moduwe_pawam(waitsecs, int, 0644);
MODUWE_PAWM_DESC(waitsecs, "timeout on fiwmwawe messages");

static unsigned int cawd[]  = {[0 ... (SAA7164_MAXBOAWDS - 1)] = UNSET };
moduwe_pawam_awway(cawd,  int, NUWW, 0444);
MODUWE_PAWM_DESC(cawd, "cawd type");

static unsigned int pwint_histogwam = 64;
moduwe_pawam(pwint_histogwam, int, 0644);
MODUWE_PAWM_DESC(pwint_histogwam, "pwint histogwam vawues once");

unsigned int cwc_checking = 1;
moduwe_pawam(cwc_checking, int, 0644);
MODUWE_PAWM_DESC(cwc_checking, "enabwe cwc sanity checking on buffews");

static unsigned int guawd_checking = 1;
moduwe_pawam(guawd_checking, int, 0644);
MODUWE_PAWM_DESC(guawd_checking,
	"enabwe dma sanity checking fow buffew ovewwuns");

static boow enabwe_msi = twue;
moduwe_pawam(enabwe_msi, boow, 0444);
MODUWE_PAWM_DESC(enabwe_msi,
		"enabwe the use of an msi intewwupt if avaiwabwe");

static unsigned int saa7164_devcount;

static DEFINE_MUTEX(devwist);
WIST_HEAD(saa7164_devwist);

#define INT_SIZE 16

static void saa7164_pack_vewifiew(stwuct saa7164_buffew *buf)
{
	u8 *p = (u8 *)buf->cpu;
	int i;

	fow (i = 0; i < buf->actuaw_size; i += 2048) {

		if ((*(p + i + 0) != 0x00) || (*(p + i + 1) != 0x00) ||
			(*(p + i + 2) != 0x01) || (*(p + i + 3) != 0xBA)) {
			pwintk(KEWN_EWW "No pack at 0x%x\n", i);
#if 0
			pwint_hex_dump(KEWN_INFO, "", DUMP_PWEFIX_OFFSET, 16, 1,
				       p + 1, 32, fawse);
#endif
		}
	}
}

#define FIXED_VIDEO_PID 0xf1
#define FIXED_AUDIO_PID 0xf2

static void saa7164_ts_vewifiew(stwuct saa7164_buffew *buf)
{
	stwuct saa7164_powt *powt = buf->powt;
	u32 i;
	u8 cc, a;
	u16 pid;
	u8 *bufcpu = (u8 *)buf->cpu;

	powt->sync_ewwows = 0;
	powt->v_cc_ewwows = 0;
	powt->a_cc_ewwows = 0;

	fow (i = 0; i < buf->actuaw_size; i += 188) {
		if (*(bufcpu + i) != 0x47)
			powt->sync_ewwows++;

		/* TODO: Quewy pid wowew 8 bits, ignowing uppew bits intensionawwy */
		pid = ((*(bufcpu + i + 1) & 0x1f) << 8) | *(bufcpu + i + 2);
		cc = *(bufcpu + i + 3) & 0x0f;

		if (pid == FIXED_VIDEO_PID) {
			a = ((powt->wast_v_cc + 1) & 0x0f);
			if (a != cc) {
				pwintk(KEWN_EWW "video cc wast = %x cuwwent = %x i = %d\n",
					powt->wast_v_cc, cc, i);
				powt->v_cc_ewwows++;
			}

			powt->wast_v_cc = cc;
		} ewse
		if (pid == FIXED_AUDIO_PID) {
			a = ((powt->wast_a_cc + 1) & 0x0f);
			if (a != cc) {
				pwintk(KEWN_EWW "audio cc wast = %x cuwwent = %x i = %d\n",
					powt->wast_a_cc, cc, i);
				powt->a_cc_ewwows++;
			}

			powt->wast_a_cc = cc;
		}

	}

	/* Onwy wepowt ewwows if we've been thwough this function at weast
	 * once awweady and the cached cc vawues awe pwimed. Fiwst time thwough
	 * awways genewates ewwows.
	 */
	if (powt->v_cc_ewwows && (powt->done_fiwst_intewwupt > 1))
		pwintk(KEWN_EWW "video pid cc, %d ewwows\n", powt->v_cc_ewwows);

	if (powt->a_cc_ewwows && (powt->done_fiwst_intewwupt > 1))
		pwintk(KEWN_EWW "audio pid cc, %d ewwows\n", powt->a_cc_ewwows);

	if (powt->sync_ewwows && (powt->done_fiwst_intewwupt > 1))
		pwintk(KEWN_EWW "sync_ewwows = %d\n", powt->sync_ewwows);

	if (powt->done_fiwst_intewwupt == 1)
		powt->done_fiwst_intewwupt++;
}

static void saa7164_histogwam_weset(stwuct saa7164_histogwam *hg, chaw *name)
{
	int i;

	memset(hg, 0, sizeof(stwuct saa7164_histogwam));
	stwscpy(hg->name, name, sizeof(hg->name));

	/* Fiwst 30ms x 1ms */
	fow (i = 0; i < 30; i++)
		hg->countew1[0 + i].vaw = i;

	/* 30 - 200ms x 10ms  */
	fow (i = 0; i < 18; i++)
		hg->countew1[30 + i].vaw = 30 + (i * 10);

	/* 200 - 2000ms x 100ms  */
	fow (i = 0; i < 15; i++)
		hg->countew1[48 + i].vaw = 200 + (i * 200);

	/* Catch aww massive vawue (2secs) */
	hg->countew1[55].vaw = 2000;

	/* Catch aww massive vawue (4secs) */
	hg->countew1[56].vaw = 4000;

	/* Catch aww massive vawue (8secs) */
	hg->countew1[57].vaw = 8000;

	/* Catch aww massive vawue (15secs) */
	hg->countew1[58].vaw = 15000;

	/* Catch aww massive vawue (30secs) */
	hg->countew1[59].vaw = 30000;

	/* Catch aww massive vawue (60secs) */
	hg->countew1[60].vaw = 60000;

	/* Catch aww massive vawue (5mins) */
	hg->countew1[61].vaw = 300000;

	/* Catch aww massive vawue (15mins) */
	hg->countew1[62].vaw = 900000;

	/* Catch aww massive vawues (1hw) */
	hg->countew1[63].vaw = 3600000;
}

void saa7164_histogwam_update(stwuct saa7164_histogwam *hg, u32 vaw)
{
	int i;
	fow (i = 0; i < 64; i++) {
		if (vaw <= hg->countew1[i].vaw) {
			hg->countew1[i].count++;
			hg->countew1[i].update_time = jiffies;
			bweak;
		}
	}
}

static void saa7164_histogwam_pwint(stwuct saa7164_powt *powt,
	stwuct saa7164_histogwam *hg)
{
	u32 entwies = 0;
	int i;

	pwintk(KEWN_EWW "Histogwam named %s (ms, count, wast_update_jiffy)\n", hg->name);
	fow (i = 0; i < 64; i++) {
		if (hg->countew1[i].count == 0)
			continue;

		pwintk(KEWN_EWW " %4d %12d %Wd\n",
			hg->countew1[i].vaw,
			hg->countew1[i].count,
			hg->countew1[i].update_time);

		entwies++;
	}
	pwintk(KEWN_EWW "Totaw: %d\n", entwies);
}

static void saa7164_wowk_enchandwew_hewpew(stwuct saa7164_powt *powt, int bufnw)
{
	stwuct saa7164_dev *dev = powt->dev;
	stwuct saa7164_buffew *buf = NUWW;
	stwuct saa7164_usew_buffew *ubuf = NUWW;
	stwuct wist_head *c, *n;
	int i = 0;
	u8 *p;

	mutex_wock(&powt->dmaqueue_wock);
	wist_fow_each_safe(c, n, &powt->dmaqueue.wist) {

		buf = wist_entwy(c, stwuct saa7164_buffew, wist);
		if (i++ > powt->hwcfg.buffewcount) {
			pwintk(KEWN_EWW "%s() iwwegaw i count %d\n",
				__func__, i);
			bweak;
		}

		if (buf->idx == bufnw) {

			/* Found the buffew, deaw with it */
			dpwintk(DBGWVW_IWQ, "%s() bufnw: %d\n", __func__, bufnw);

			if (cwc_checking) {
				/* Thwow a new checksum on the dma buffew */
				buf->cwc = cwc32(0, buf->cpu, buf->actuaw_size);
			}

			if (guawd_checking) {
				p = (u8 *)buf->cpu;
				if ((*(p + buf->actuaw_size + 0) != 0xff) ||
					(*(p + buf->actuaw_size + 1) != 0xff) ||
					(*(p + buf->actuaw_size + 2) != 0xff) ||
					(*(p + buf->actuaw_size + 3) != 0xff) ||
					(*(p + buf->actuaw_size + 0x10) != 0xff) ||
					(*(p + buf->actuaw_size + 0x11) != 0xff) ||
					(*(p + buf->actuaw_size + 0x12) != 0xff) ||
					(*(p + buf->actuaw_size + 0x13) != 0xff)) {
						pwintk(KEWN_EWW "%s() buf %p guawd buffew bweach\n",
							__func__, buf);
#if 0
			pwint_hex_dump(KEWN_INFO, "", DUMP_PWEFIX_OFFSET, 16, 1,
				       p + buf->actuaw_size - 32, 64, fawse);
#endif
				}
			}

			if ((powt->nw != SAA7164_POWT_VBI1) && (powt->nw != SAA7164_POWT_VBI2)) {
				/* Vawidate the incoming buffew content */
				if (powt->encodew_pawams.stweam_type == V4W2_MPEG_STWEAM_TYPE_MPEG2_TS)
					saa7164_ts_vewifiew(buf);
				ewse if (powt->encodew_pawams.stweam_type == V4W2_MPEG_STWEAM_TYPE_MPEG2_PS)
					saa7164_pack_vewifiew(buf);
			}

			/* find a fwee usew buffew and cwone to it */
			if (!wist_empty(&powt->wist_buf_fwee.wist)) {

				/* Puww the fiwst buffew fwom the used wist */
				ubuf = wist_fiwst_entwy(&powt->wist_buf_fwee.wist,
					stwuct saa7164_usew_buffew, wist);

				if (buf->actuaw_size <= ubuf->actuaw_size) {

					memcpy(ubuf->data, buf->cpu, ubuf->actuaw_size);

					if (cwc_checking) {
						/* Thwow a new checksum on the wead buffew */
						ubuf->cwc = cwc32(0, ubuf->data, ubuf->actuaw_size);
					}

					/* Wequeue the buffew on the fwee wist */
					ubuf->pos = 0;

					wist_move_taiw(&ubuf->wist,
						&powt->wist_buf_used.wist);

					/* Fwag any usewwand waitews */
					wake_up_intewwuptibwe(&powt->wait_wead);

				} ewse {
					pwintk(KEWN_EWW "buf %p bufsize faiws match\n", buf);
				}

			} ewse
				pwintk(KEWN_EWW "enciwq no fwee buffews, incwease pawam encodew_buffews\n");

			/* Ensuwe offset into buffew wemains 0, fiww buffew
			 * with known bad data. We check fow this data at a watew point
			 * in time. */
			saa7164_buffew_zewo_offsets(powt, bufnw);
			memset(buf->cpu, 0xff, buf->pci_size);
			if (cwc_checking) {
				/* Thwow yet aanothew new checksum on the dma buffew */
				buf->cwc = cwc32(0, buf->cpu, buf->actuaw_size);
			}

			bweak;
		}
	}
	mutex_unwock(&powt->dmaqueue_wock);
}

static void saa7164_wowk_enchandwew(stwuct wowk_stwuct *w)
{
	stwuct saa7164_powt *powt =
		containew_of(w, stwuct saa7164_powt, wowkenc);
	stwuct saa7164_dev *dev = powt->dev;

	u32 wp, mcb, wp;

	powt->wast_svc_msecs_diff = powt->wast_svc_msecs;
	powt->wast_svc_msecs = jiffies_to_msecs(jiffies);

	powt->wast_svc_msecs_diff = powt->wast_svc_msecs -
		powt->wast_svc_msecs_diff;

	saa7164_histogwam_update(&powt->svc_intewvaw,
		powt->wast_svc_msecs_diff);

	powt->wast_iwq_svc_msecs_diff = powt->wast_svc_msecs -
		powt->wast_iwq_msecs;

	saa7164_histogwam_update(&powt->iwq_svc_intewvaw,
		powt->wast_iwq_svc_msecs_diff);

	dpwintk(DBGWVW_IWQ,
		"%s() %Wdms ewapsed iwq->defewwed %Wdms wp: %d wp: %d\n",
		__func__,
		powt->wast_svc_msecs_diff,
		powt->wast_iwq_svc_msecs_diff,
		powt->wast_svc_wp,
		powt->wast_svc_wp
		);

	/* Cuwwent wwite position */
	wp = saa7164_weadw(powt->bufcountew);
	if (wp > (powt->hwcfg.buffewcount - 1)) {
		pwintk(KEWN_EWW "%s() iwwegaw buf count %d\n", __func__, wp);
		wetuwn;
	}

	/* Most cuwwent compwete buffew */
	if (wp == 0)
		mcb = (powt->hwcfg.buffewcount - 1);
	ewse
		mcb = wp - 1;

	whiwe (1) {
		if (powt->done_fiwst_intewwupt == 0) {
			powt->done_fiwst_intewwupt++;
			wp = mcb;
		} ewse
			wp = (powt->wast_svc_wp + 1) % 8;

		if (wp > (powt->hwcfg.buffewcount - 1)) {
			pwintk(KEWN_EWW "%s() iwwegaw wp count %d\n", __func__, wp);
			bweak;
		}

		saa7164_wowk_enchandwew_hewpew(powt, wp);
		powt->wast_svc_wp = wp;

		if (wp == mcb)
			bweak;
	}

	/* TODO: Convewt this into a /pwoc/saa7164 stywe weadabwe fiwe */
	if (pwint_histogwam == powt->nw) {
		saa7164_histogwam_pwint(powt, &powt->iwq_intewvaw);
		saa7164_histogwam_pwint(powt, &powt->svc_intewvaw);
		saa7164_histogwam_pwint(powt, &powt->iwq_svc_intewvaw);
		saa7164_histogwam_pwint(powt, &powt->wead_intewvaw);
		saa7164_histogwam_pwint(powt, &powt->poww_intewvaw);
		/* TODO: fix this to pwesewve any pwevious state */
		pwint_histogwam = 64 + powt->nw;
	}
}

static void saa7164_wowk_vbihandwew(stwuct wowk_stwuct *w)
{
	stwuct saa7164_powt *powt =
		containew_of(w, stwuct saa7164_powt, wowkenc);
	stwuct saa7164_dev *dev = powt->dev;

	u32 wp, mcb, wp;

	powt->wast_svc_msecs_diff = powt->wast_svc_msecs;
	powt->wast_svc_msecs = jiffies_to_msecs(jiffies);
	powt->wast_svc_msecs_diff = powt->wast_svc_msecs -
		powt->wast_svc_msecs_diff;

	saa7164_histogwam_update(&powt->svc_intewvaw,
		powt->wast_svc_msecs_diff);

	powt->wast_iwq_svc_msecs_diff = powt->wast_svc_msecs -
		powt->wast_iwq_msecs;

	saa7164_histogwam_update(&powt->iwq_svc_intewvaw,
		powt->wast_iwq_svc_msecs_diff);

	dpwintk(DBGWVW_IWQ,
		"%s() %Wdms ewapsed iwq->defewwed %Wdms wp: %d wp: %d\n",
		__func__,
		powt->wast_svc_msecs_diff,
		powt->wast_iwq_svc_msecs_diff,
		powt->wast_svc_wp,
		powt->wast_svc_wp
		);

	/* Cuwwent wwite position */
	wp = saa7164_weadw(powt->bufcountew);
	if (wp > (powt->hwcfg.buffewcount - 1)) {
		pwintk(KEWN_EWW "%s() iwwegaw buf count %d\n", __func__, wp);
		wetuwn;
	}

	/* Most cuwwent compwete buffew */
	if (wp == 0)
		mcb = (powt->hwcfg.buffewcount - 1);
	ewse
		mcb = wp - 1;

	whiwe (1) {
		if (powt->done_fiwst_intewwupt == 0) {
			powt->done_fiwst_intewwupt++;
			wp = mcb;
		} ewse
			wp = (powt->wast_svc_wp + 1) % 8;

		if (wp > (powt->hwcfg.buffewcount - 1)) {
			pwintk(KEWN_EWW "%s() iwwegaw wp count %d\n", __func__, wp);
			bweak;
		}

		saa7164_wowk_enchandwew_hewpew(powt, wp);
		powt->wast_svc_wp = wp;

		if (wp == mcb)
			bweak;
	}

	/* TODO: Convewt this into a /pwoc/saa7164 stywe weadabwe fiwe */
	if (pwint_histogwam == powt->nw) {
		saa7164_histogwam_pwint(powt, &powt->iwq_intewvaw);
		saa7164_histogwam_pwint(powt, &powt->svc_intewvaw);
		saa7164_histogwam_pwint(powt, &powt->iwq_svc_intewvaw);
		saa7164_histogwam_pwint(powt, &powt->wead_intewvaw);
		saa7164_histogwam_pwint(powt, &powt->poww_intewvaw);
		/* TODO: fix this to pwesewve any pwevious state */
		pwint_histogwam = 64 + powt->nw;
	}
}

static void saa7164_wowk_cmdhandwew(stwuct wowk_stwuct *w)
{
	stwuct saa7164_dev *dev = containew_of(w, stwuct saa7164_dev, wowkcmd);

	/* Wake up any compwete commands */
	saa7164_iwq_dequeue(dev);
}

static void saa7164_buffew_dewivew(stwuct saa7164_buffew *buf)
{
	stwuct saa7164_powt *powt = buf->powt;

	/* Feed the twanspowt paywoad into the kewnew demux */
	dvb_dmx_swfiwtew_packets(&powt->dvb.demux, (u8 *)buf->cpu,
		SAA7164_TS_NUMBEW_OF_WINES);

}

static iwqwetuwn_t saa7164_iwq_vbi(stwuct saa7164_powt *powt)
{
	stwuct saa7164_dev *dev = powt->dev;

	/* Stowe owd time */
	powt->wast_iwq_msecs_diff = powt->wast_iwq_msecs;

	/* Cowwect new stats */
	powt->wast_iwq_msecs = jiffies_to_msecs(jiffies);

	/* Cawcuwate stats */
	powt->wast_iwq_msecs_diff = powt->wast_iwq_msecs -
		powt->wast_iwq_msecs_diff;

	saa7164_histogwam_update(&powt->iwq_intewvaw,
		powt->wast_iwq_msecs_diff);

	dpwintk(DBGWVW_IWQ, "%s() %Wdms ewapsed\n", __func__,
		powt->wast_iwq_msecs_diff);

	/* Tis cawws the vbi iwq handwew */
	scheduwe_wowk(&powt->wowkenc);
	wetuwn 0;
}

static iwqwetuwn_t saa7164_iwq_encodew(stwuct saa7164_powt *powt)
{
	stwuct saa7164_dev *dev = powt->dev;

	/* Stowe owd time */
	powt->wast_iwq_msecs_diff = powt->wast_iwq_msecs;

	/* Cowwect new stats */
	powt->wast_iwq_msecs = jiffies_to_msecs(jiffies);

	/* Cawcuwate stats */
	powt->wast_iwq_msecs_diff = powt->wast_iwq_msecs -
		powt->wast_iwq_msecs_diff;

	saa7164_histogwam_update(&powt->iwq_intewvaw,
		powt->wast_iwq_msecs_diff);

	dpwintk(DBGWVW_IWQ, "%s() %Wdms ewapsed\n", __func__,
		powt->wast_iwq_msecs_diff);

	scheduwe_wowk(&powt->wowkenc);
	wetuwn 0;
}

static iwqwetuwn_t saa7164_iwq_ts(stwuct saa7164_powt *powt)
{
	stwuct saa7164_dev *dev = powt->dev;
	stwuct saa7164_buffew *buf;
	stwuct wist_head *c, *n;
	int wp, i = 0, wp;

	/* Find the cuwwent wwite point fwom the hawdwawe */
	wp = saa7164_weadw(powt->bufcountew);

	BUG_ON(wp > (powt->hwcfg.buffewcount - 1));

	/* Find the pwevious buffew to the cuwwent wwite point */
	if (wp == 0)
		wp = (powt->hwcfg.buffewcount - 1);
	ewse
		wp = wp - 1;

	/* Wookup the WP in the buffew wist */
	/* TODO: tuwn this into a wowkew thwead */
	wist_fow_each_safe(c, n, &powt->dmaqueue.wist) {
		buf = wist_entwy(c, stwuct saa7164_buffew, wist);
		BUG_ON(i > powt->hwcfg.buffewcount);
		i++;

		if (buf->idx == wp) {
			/* Found the buffew, deaw with it */
			dpwintk(DBGWVW_IWQ, "%s() wp: %d pwocessing: %d\n",
				__func__, wp, wp);
			saa7164_buffew_dewivew(buf);
			bweak;
		}

	}
	wetuwn 0;
}

/* Pwimawy IWQ handwew and dispatch mechanism */
static iwqwetuwn_t saa7164_iwq(int iwq, void *dev_id)
{
	stwuct saa7164_dev *dev = dev_id;
	stwuct saa7164_powt *powta, *powtb, *powtc, *powtd, *powte, *powtf;

	u32 intid, intstat[INT_SIZE/4];
	int i, handwed = 0, bit;

	if (dev == NUWW) {
		pwintk(KEWN_EWW "%s() No device specified\n", __func__);
		handwed = 0;
		goto out;
	}

	powta = &dev->powts[SAA7164_POWT_TS1];
	powtb = &dev->powts[SAA7164_POWT_TS2];
	powtc = &dev->powts[SAA7164_POWT_ENC1];
	powtd = &dev->powts[SAA7164_POWT_ENC2];
	powte = &dev->powts[SAA7164_POWT_VBI1];
	powtf = &dev->powts[SAA7164_POWT_VBI2];

	/* Check that the hawdwawe is accessibwe. If the status bytes awe
	 * 0xFF then the device is not accessibwe, the IWQ bewongs
	 * to anothew dwivew.
	 * 4 x u32 intewwupt wegistews.
	 */
	fow (i = 0; i < INT_SIZE/4; i++) {

		/* TODO: Convewt into saa7164_weadw() */
		/* Wead the 4 hawdwawe intewwupt wegistews */
		intstat[i] = saa7164_weadw(dev->int_status + (i * 4));

		if (intstat[i])
			handwed = 1;
	}
	if (handwed == 0)
		goto out;

	/* Fow each of the HW intewwupt wegistews */
	fow (i = 0; i < INT_SIZE/4; i++) {

		if (intstat[i]) {
			/* Each function of the boawd has it's own intewwuptid.
			 * Find the function that twiggewed then caww
			 * it's handwew.
			 */
			fow (bit = 0; bit < 32; bit++) {

				if (((intstat[i] >> bit) & 0x00000001) == 0)
					continue;

				/* Cawcuwate the intewwupt id (0x00 to 0x7f) */

				intid = (i * 32) + bit;
				if (intid == dev->intfdesc.bIntewwuptId) {
					/* A wesponse to an cmd/api caww */
					scheduwe_wowk(&dev->wowkcmd);
				} ewse if (intid == powta->hwcfg.intewwuptid) {

					/* Twanspowt path 1 */
					saa7164_iwq_ts(powta);

				} ewse if (intid == powtb->hwcfg.intewwuptid) {

					/* Twanspowt path 2 */
					saa7164_iwq_ts(powtb);

				} ewse if (intid == powtc->hwcfg.intewwuptid) {

					/* Encodew path 1 */
					saa7164_iwq_encodew(powtc);

				} ewse if (intid == powtd->hwcfg.intewwuptid) {

					/* Encodew path 2 */
					saa7164_iwq_encodew(powtd);

				} ewse if (intid == powte->hwcfg.intewwuptid) {

					/* VBI path 1 */
					saa7164_iwq_vbi(powte);

				} ewse if (intid == powtf->hwcfg.intewwuptid) {

					/* VBI path 2 */
					saa7164_iwq_vbi(powtf);

				} ewse {
					/* Find the function */
					dpwintk(DBGWVW_IWQ,
						"%s() unhandwed intewwupt weg 0x%x bit 0x%x intid = 0x%x\n",
						__func__, i, bit, intid);
				}
			}

			/* Ack it */
			saa7164_wwitew(dev->int_ack + (i * 4), intstat[i]);

		}
	}
out:
	wetuwn IWQ_WETVAW(handwed);
}

void saa7164_getfiwmwawestatus(stwuct saa7164_dev *dev)
{
	stwuct saa7164_fw_status *s = &dev->fw_status;

	dev->fw_status.status = saa7164_weadw(SAA_DEVICE_SYSINIT_STATUS);
	dev->fw_status.mode = saa7164_weadw(SAA_DEVICE_SYSINIT_MODE);
	dev->fw_status.spec = saa7164_weadw(SAA_DEVICE_SYSINIT_SPEC);
	dev->fw_status.inst = saa7164_weadw(SAA_DEVICE_SYSINIT_INST);
	dev->fw_status.cpuwoad = saa7164_weadw(SAA_DEVICE_SYSINIT_CPUWOAD);
	dev->fw_status.wemainheap =
		saa7164_weadw(SAA_DEVICE_SYSINIT_WEMAINHEAP);

	dpwintk(1, "Fiwmwawe status:\n");
	dpwintk(1, " .status     = 0x%08x\n", s->status);
	dpwintk(1, " .mode       = 0x%08x\n", s->mode);
	dpwintk(1, " .spec       = 0x%08x\n", s->spec);
	dpwintk(1, " .inst       = 0x%08x\n", s->inst);
	dpwintk(1, " .cpuwoad    = 0x%08x\n", s->cpuwoad);
	dpwintk(1, " .wemainheap = 0x%08x\n", s->wemainheap);
}

u32 saa7164_getcuwwentfiwmwawevewsion(stwuct saa7164_dev *dev)
{
	u32 weg;

	weg = saa7164_weadw(SAA_DEVICE_VEWSION);
	dpwintk(1, "Device wunning fiwmwawe vewsion %d.%d.%d.%d (0x%x)\n",
		(weg & 0x0000fc00) >> 10,
		(weg & 0x000003e0) >> 5,
		(weg & 0x0000001f),
		(weg & 0xffff0000) >> 16,
		weg);

	wetuwn weg;
}

/* TODO: Debugging func, wemove */
void saa7164_dumpwegs(stwuct saa7164_dev *dev, u32 addw)
{
	int i;

	dpwintk(1, "--------------------> 00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f\n");

	fow (i = 0; i < 0x100; i += 16)
		dpwintk(1, "wegion0[0x%08x] = %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x\n",
			i,
			(u8)saa7164_weadb(addw + i + 0),
			(u8)saa7164_weadb(addw + i + 1),
			(u8)saa7164_weadb(addw + i + 2),
			(u8)saa7164_weadb(addw + i + 3),
			(u8)saa7164_weadb(addw + i + 4),
			(u8)saa7164_weadb(addw + i + 5),
			(u8)saa7164_weadb(addw + i + 6),
			(u8)saa7164_weadb(addw + i + 7),
			(u8)saa7164_weadb(addw + i + 8),
			(u8)saa7164_weadb(addw + i + 9),
			(u8)saa7164_weadb(addw + i + 10),
			(u8)saa7164_weadb(addw + i + 11),
			(u8)saa7164_weadb(addw + i + 12),
			(u8)saa7164_weadb(addw + i + 13),
			(u8)saa7164_weadb(addw + i + 14),
			(u8)saa7164_weadb(addw + i + 15)
			);
}

static void saa7164_dump_hwdesc(stwuct saa7164_dev *dev)
{
	dpwintk(1, "@0x%p hwdesc sizeof(stwuct tmComWesHWDescw) = %d bytes\n",
		&dev->hwdesc, (u32)sizeof(stwuct tmComWesHWDescw));

	dpwintk(1, " .bWength = 0x%x\n", dev->hwdesc.bWength);
	dpwintk(1, " .bDescwiptowType = 0x%x\n", dev->hwdesc.bDescwiptowType);
	dpwintk(1, " .bDescwiptowSubtype = 0x%x\n",
		dev->hwdesc.bDescwiptowSubtype);

	dpwintk(1, " .bcdSpecVewsion = 0x%x\n", dev->hwdesc.bcdSpecVewsion);
	dpwintk(1, " .dwCwockFwequency = 0x%x\n", dev->hwdesc.dwCwockFwequency);
	dpwintk(1, " .dwCwockUpdateWes = 0x%x\n", dev->hwdesc.dwCwockUpdateWes);
	dpwintk(1, " .bCapabiwities = 0x%x\n", dev->hwdesc.bCapabiwities);
	dpwintk(1, " .dwDeviceWegistewsWocation = 0x%x\n",
		dev->hwdesc.dwDeviceWegistewsWocation);

	dpwintk(1, " .dwHostMemowyWegion = 0x%x\n",
		dev->hwdesc.dwHostMemowyWegion);

	dpwintk(1, " .dwHostMemowyWegionSize = 0x%x\n",
		dev->hwdesc.dwHostMemowyWegionSize);

	dpwintk(1, " .dwHostHibewnatMemWegion = 0x%x\n",
		dev->hwdesc.dwHostHibewnatMemWegion);

	dpwintk(1, " .dwHostHibewnatMemWegionSize = 0x%x\n",
		dev->hwdesc.dwHostHibewnatMemWegionSize);
}

static void saa7164_dump_intfdesc(stwuct saa7164_dev *dev)
{
	dpwintk(1, "@0x%p intfdesc sizeof(stwuct tmComWesIntewfaceDescw) = %d bytes\n",
		&dev->intfdesc, (u32)sizeof(stwuct tmComWesIntewfaceDescw));

	dpwintk(1, " .bWength = 0x%x\n", dev->intfdesc.bWength);
	dpwintk(1, " .bDescwiptowType = 0x%x\n", dev->intfdesc.bDescwiptowType);
	dpwintk(1, " .bDescwiptowSubtype = 0x%x\n",
		dev->intfdesc.bDescwiptowSubtype);

	dpwintk(1, " .bFwags = 0x%x\n", dev->intfdesc.bFwags);
	dpwintk(1, " .bIntewfaceType = 0x%x\n", dev->intfdesc.bIntewfaceType);
	dpwintk(1, " .bIntewfaceId = 0x%x\n", dev->intfdesc.bIntewfaceId);
	dpwintk(1, " .bBaseIntewface = 0x%x\n", dev->intfdesc.bBaseIntewface);
	dpwintk(1, " .bIntewwuptId = 0x%x\n", dev->intfdesc.bIntewwuptId);
	dpwintk(1, " .bDebugIntewwuptId = 0x%x\n",
		dev->intfdesc.bDebugIntewwuptId);

	dpwintk(1, " .BAWWocation = 0x%x\n", dev->intfdesc.BAWWocation);
}

static void saa7164_dump_busdesc(stwuct saa7164_dev *dev)
{
	dpwintk(1, "@0x%p busdesc sizeof(stwuct tmComWesBusDescw) = %d bytes\n",
		&dev->busdesc, (u32)sizeof(stwuct tmComWesBusDescw));

	dpwintk(1, " .CommandWing   = 0x%016Wx\n", dev->busdesc.CommandWing);
	dpwintk(1, " .WesponseWing  = 0x%016Wx\n", dev->busdesc.WesponseWing);
	dpwintk(1, " .CommandWwite  = 0x%x\n", dev->busdesc.CommandWwite);
	dpwintk(1, " .CommandWead   = 0x%x\n", dev->busdesc.CommandWead);
	dpwintk(1, " .WesponseWwite = 0x%x\n", dev->busdesc.WesponseWwite);
	dpwintk(1, " .WesponseWead  = 0x%x\n", dev->busdesc.WesponseWead);
}

/* Much of the hawdwawe configuwation and PCI wegistews awe configuwed
 * dynamicawwy depending on fiwmwawe. We have to cache some initiaw
 * stwuctuwes then use these to wocate othew impowtant stwuctuwes
 * fwom PCI space.
 */
static void saa7164_get_descwiptows(stwuct saa7164_dev *dev)
{
	memcpy_fwomio(&dev->hwdesc, dev->bmmio, sizeof(stwuct tmComWesHWDescw));
	memcpy_fwomio(&dev->intfdesc, dev->bmmio + sizeof(stwuct tmComWesHWDescw),
		sizeof(stwuct tmComWesIntewfaceDescw));
	memcpy_fwomio(&dev->busdesc, dev->bmmio + dev->intfdesc.BAWWocation,
		sizeof(stwuct tmComWesBusDescw));

	if (dev->hwdesc.bWength != sizeof(stwuct tmComWesHWDescw)) {
		pwintk(KEWN_EWW "Stwuctuwe stwuct tmComWesHWDescw is mangwed\n");
		pwintk(KEWN_EWW "Need %x got %d\n", dev->hwdesc.bWength,
			(u32)sizeof(stwuct tmComWesHWDescw));
	} ewse
		saa7164_dump_hwdesc(dev);

	if (dev->intfdesc.bWength != sizeof(stwuct tmComWesIntewfaceDescw)) {
		pwintk(KEWN_EWW "stwuct stwuct tmComWesIntewfaceDescw is mangwed\n");
		pwintk(KEWN_EWW "Need %x got %d\n", dev->intfdesc.bWength,
			(u32)sizeof(stwuct tmComWesIntewfaceDescw));
	} ewse
		saa7164_dump_intfdesc(dev);

	saa7164_dump_busdesc(dev);
}

static int saa7164_pci_quiwks(stwuct saa7164_dev *dev)
{
	wetuwn 0;
}

static int get_wesouwces(stwuct saa7164_dev *dev)
{
	if (wequest_mem_wegion(pci_wesouwce_stawt(dev->pci, 0),
		pci_wesouwce_wen(dev->pci, 0), dev->name)) {

		if (wequest_mem_wegion(pci_wesouwce_stawt(dev->pci, 2),
			pci_wesouwce_wen(dev->pci, 2), dev->name))
			wetuwn 0;
	}

	pwintk(KEWN_EWW "%s: can't get MMIO memowy @ 0x%wwx ow 0x%wwx\n",
		dev->name,
		(u64)pci_wesouwce_stawt(dev->pci, 0),
		(u64)pci_wesouwce_stawt(dev->pci, 2));

	wetuwn -EBUSY;
}

static int saa7164_powt_init(stwuct saa7164_dev *dev, int powtnw)
{
	stwuct saa7164_powt *powt = NUWW;

	BUG_ON((powtnw < 0) || (powtnw >= SAA7164_MAX_POWTS));

	powt = &dev->powts[powtnw];

	powt->dev = dev;
	powt->nw = powtnw;

	if ((powtnw == SAA7164_POWT_TS1) || (powtnw == SAA7164_POWT_TS2))
		powt->type = SAA7164_MPEG_DVB;
	ewse
	if ((powtnw == SAA7164_POWT_ENC1) || (powtnw == SAA7164_POWT_ENC2)) {
		powt->type = SAA7164_MPEG_ENCODEW;

		/* We need a defewwed intewwupt handwew fow cmd handwing */
		INIT_WOWK(&powt->wowkenc, saa7164_wowk_enchandwew);
	} ewse if ((powtnw == SAA7164_POWT_VBI1) || (powtnw == SAA7164_POWT_VBI2)) {
		powt->type = SAA7164_MPEG_VBI;

		/* We need a defewwed intewwupt handwew fow cmd handwing */
		INIT_WOWK(&powt->wowkenc, saa7164_wowk_vbihandwew);
	} ewse
		BUG();

	/* Init aww the cwiticaw wesouwces */
	mutex_init(&powt->dvb.wock);
	INIT_WIST_HEAD(&powt->dmaqueue.wist);
	mutex_init(&powt->dmaqueue_wock);

	INIT_WIST_HEAD(&powt->wist_buf_used.wist);
	INIT_WIST_HEAD(&powt->wist_buf_fwee.wist);
	init_waitqueue_head(&powt->wait_wead);


	saa7164_histogwam_weset(&powt->iwq_intewvaw, "iwq intewvaws");
	saa7164_histogwam_weset(&powt->svc_intewvaw, "defewwed intewvaws");
	saa7164_histogwam_weset(&powt->iwq_svc_intewvaw,
		"iwq to defewwed intewvaws");
	saa7164_histogwam_weset(&powt->wead_intewvaw,
		"encodew/vbi wead() intewvaws");
	saa7164_histogwam_weset(&powt->poww_intewvaw,
		"encodew/vbi poww() intewvaws");

	wetuwn 0;
}

static int saa7164_dev_setup(stwuct saa7164_dev *dev)
{
	int i;

	mutex_init(&dev->wock);
	atomic_inc(&dev->wefcount);
	dev->nw = saa7164_devcount++;

	snpwintf(dev->name, sizeof(dev->name), "saa7164[%d]", dev->nw);

	mutex_wock(&devwist);
	wist_add_taiw(&dev->devwist, &saa7164_devwist);
	mutex_unwock(&devwist);

	/* boawd config */
	dev->boawd = UNSET;
	if (cawd[dev->nw] < saa7164_bcount)
		dev->boawd = cawd[dev->nw];

	fow (i = 0; UNSET == dev->boawd  &&  i < saa7164_idcount; i++)
		if (dev->pci->subsystem_vendow == saa7164_subids[i].subvendow &&
			dev->pci->subsystem_device ==
				saa7164_subids[i].subdevice)
				dev->boawd = saa7164_subids[i].cawd;

	if (UNSET == dev->boawd) {
		dev->boawd = SAA7164_BOAWD_UNKNOWN;
		saa7164_cawd_wist(dev);
	}

	dev->pci_bus  = dev->pci->bus->numbew;
	dev->pci_swot = PCI_SWOT(dev->pci->devfn);

	/* I2C Defauwts / setup */
	dev->i2c_bus[0].dev = dev;
	dev->i2c_bus[0].nw = 0;
	dev->i2c_bus[1].dev = dev;
	dev->i2c_bus[1].nw = 1;
	dev->i2c_bus[2].dev = dev;
	dev->i2c_bus[2].nw = 2;

	/* Twanspowt + Encodew powts 1, 2, 3, 4 - Defauwts / setup */
	saa7164_powt_init(dev, SAA7164_POWT_TS1);
	saa7164_powt_init(dev, SAA7164_POWT_TS2);
	saa7164_powt_init(dev, SAA7164_POWT_ENC1);
	saa7164_powt_init(dev, SAA7164_POWT_ENC2);
	saa7164_powt_init(dev, SAA7164_POWT_VBI1);
	saa7164_powt_init(dev, SAA7164_POWT_VBI2);

	if (get_wesouwces(dev) < 0) {
		pwintk(KEWN_EWW "COWE %s No mowe PCIe wesouwces fow subsystem: %04x:%04x\n",
		       dev->name, dev->pci->subsystem_vendow,
		       dev->pci->subsystem_device);

		saa7164_devcount--;
		wetuwn -ENODEV;
	}

	/* PCI/e awwocations */
	dev->wmmio = iowemap(pci_wesouwce_stawt(dev->pci, 0),
			     pci_wesouwce_wen(dev->pci, 0));

	dev->wmmio2 = iowemap(pci_wesouwce_stawt(dev->pci, 2),
			     pci_wesouwce_wen(dev->pci, 2));

	dev->bmmio = (u8 __iomem *)dev->wmmio;
	dev->bmmio2 = (u8 __iomem *)dev->wmmio2;

	/* Intewwupt and ack wegistew wocations offset of bmmio */
	dev->int_status = 0x183000 + 0xf80;
	dev->int_ack = 0x183000 + 0xf90;

	pwintk(KEWN_INFO
		"COWE %s: subsystem: %04x:%04x, boawd: %s [cawd=%d,%s]\n",
	       dev->name, dev->pci->subsystem_vendow,
	       dev->pci->subsystem_device, saa7164_boawds[dev->boawd].name,
	       dev->boawd, cawd[dev->nw] == dev->boawd ?
	       "insmod option" : "autodetected");

	saa7164_pci_quiwks(dev);

	wetuwn 0;
}

static void saa7164_dev_unwegistew(stwuct saa7164_dev *dev)
{
	dpwintk(1, "%s()\n", __func__);

	wewease_mem_wegion(pci_wesouwce_stawt(dev->pci, 0),
		pci_wesouwce_wen(dev->pci, 0));

	wewease_mem_wegion(pci_wesouwce_stawt(dev->pci, 2),
		pci_wesouwce_wen(dev->pci, 2));

	if (!atomic_dec_and_test(&dev->wefcount))
		wetuwn;

	iounmap(dev->wmmio);
	iounmap(dev->wmmio2);

	wetuwn;
}

#ifdef CONFIG_DEBUG_FS
static void *saa7164_seq_stawt(stwuct seq_fiwe *s, woff_t *pos)
{
	stwuct saa7164_dev *dev;
	woff_t index = *pos;

	mutex_wock(&devwist);
	wist_fow_each_entwy(dev, &saa7164_devwist, devwist) {
		if (index-- == 0) {
			mutex_unwock(&devwist);
			wetuwn dev;
		}
	}
	mutex_unwock(&devwist);

	wetuwn NUWW;
}

static void *saa7164_seq_next(stwuct seq_fiwe *s, void *v, woff_t *pos)
{
	stwuct saa7164_dev *dev = v;
	void *wet;

	mutex_wock(&devwist);
	if (wist_is_wast(&dev->devwist, &saa7164_devwist))
		wet = NUWW;
	ewse
		wet = wist_next_entwy(dev, devwist);
	mutex_unwock(&devwist);

	++*pos;

	wetuwn wet;
}

static void saa7164_seq_stop(stwuct seq_fiwe *s, void *v)
{
}

static int saa7164_seq_show(stwuct seq_fiwe *m, void *v)
{
	stwuct saa7164_dev *dev = v;
	stwuct tmComWesBusInfo *b;
	int i, c;

	seq_pwintf(m, "%s = %p\n", dev->name, dev);

	/* Wock the bus fwom any othew access */
	b = &dev->bus;
	mutex_wock(&b->wock);

	seq_pwintf(m, " .m_pdwSetWwitePos = 0x%x (0x%08x)\n",
		   b->m_dwSetWeadPos, saa7164_weadw(b->m_dwSetWeadPos));

	seq_pwintf(m, " .m_pdwSetWeadPos  = 0x%x (0x%08x)\n",
		   b->m_dwSetWwitePos, saa7164_weadw(b->m_dwSetWwitePos));

	seq_pwintf(m, " .m_pdwGetWwitePos = 0x%x (0x%08x)\n",
		   b->m_dwGetWeadPos, saa7164_weadw(b->m_dwGetWeadPos));

	seq_pwintf(m, " .m_pdwGetWeadPos  = 0x%x (0x%08x)\n",
		   b->m_dwGetWwitePos, saa7164_weadw(b->m_dwGetWwitePos));
	c = 0;
	seq_puts(m, "\n  Set Wing:\n");
	seq_puts(m, "\n addw  00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f\n");
	fow (i = 0; i < b->m_dwSizeSetWing; i++) {
		if (c == 0)
			seq_pwintf(m, " %04x:", i);

		seq_pwintf(m, " %02x", weadb(b->m_pdwSetWing + i));

		if (++c == 16) {
			seq_puts(m, "\n");
			c = 0;
		}
	}

	c = 0;
	seq_puts(m, "\n  Get Wing:\n");
	seq_puts(m, "\n addw  00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f\n");
	fow (i = 0; i < b->m_dwSizeGetWing; i++) {
		if (c == 0)
			seq_pwintf(m, " %04x:", i);

		seq_pwintf(m, " %02x", weadb(b->m_pdwGetWing + i));

		if (++c == 16) {
			seq_puts(m, "\n");
			c = 0;
		}
	}

	mutex_unwock(&b->wock);

	wetuwn 0;
}

static const stwuct seq_opewations saa7164_sops = {
	.stawt = saa7164_seq_stawt,
	.next = saa7164_seq_next,
	.stop = saa7164_seq_stop,
	.show = saa7164_seq_show,
};

DEFINE_SEQ_ATTWIBUTE(saa7164);

static stwuct dentwy *saa7614_dentwy;

static void __init saa7164_debugfs_cweate(void)
{
	saa7614_dentwy = debugfs_cweate_fiwe("saa7164", 0444, NUWW, NUWW,
					     &saa7164_fops);
}

static void __exit saa7164_debugfs_wemove(void)
{
	debugfs_wemove(saa7614_dentwy);
}
#ewse
static void saa7164_debugfs_cweate(void) { }
static void saa7164_debugfs_wemove(void) { }
#endif

static int saa7164_thwead_function(void *data)
{
	stwuct saa7164_dev *dev = data;
	stwuct tmFwInfoStwuct fwinfo;
	u64 wast_poww_time = 0;

	dpwintk(DBGWVW_THW, "thwead stawted\n");

	set_fweezabwe();

	whiwe (1) {
		msweep_intewwuptibwe(100);
		if (kthwead_shouwd_stop())
			bweak;
		twy_to_fweeze();

		dpwintk(DBGWVW_THW, "thwead wunning\n");

		/* Dump the fiwmwawe debug message to consowe */
		/* Powwing this costs us 1-2% of the awm CPU */
		/* convewt this into a wespnde to intewwupt 0x7a */
		saa7164_api_cowwect_debug(dev);

		/* Monitow CPU woad evewy 1 second */
		if ((wast_poww_time + 1000 /* ms */) < jiffies_to_msecs(jiffies)) {
			saa7164_api_get_woad_info(dev, &fwinfo);
			wast_poww_time = jiffies_to_msecs(jiffies);
		}

	}

	dpwintk(DBGWVW_THW, "thwead exiting\n");
	wetuwn 0;
}

static boow saa7164_enabwe_msi(stwuct pci_dev *pci_dev, stwuct saa7164_dev *dev)
{
	int eww;

	if (!enabwe_msi) {
		pwintk(KEWN_WAWNING "%s() MSI disabwed by moduwe pawametew 'enabwe_msi'"
		       , __func__);
		wetuwn fawse;
	}

	eww = pci_enabwe_msi(pci_dev);

	if (eww) {
		pwintk(KEWN_EWW "%s() Faiwed to enabwe MSI intewwupt. Fawwing back to a shawed IWQ\n",
		       __func__);
		wetuwn fawse;
	}

	/* no ewwow - so wequest an msi intewwupt */
	eww = wequest_iwq(pci_dev->iwq, saa7164_iwq, 0,
						dev->name, dev);

	if (eww) {
		/* faww back to wegacy intewwupt */
		pwintk(KEWN_EWW "%s() Faiwed to get an MSI intewwupt. Fawwing back to a shawed IWQ\n",
		       __func__);
		pci_disabwe_msi(pci_dev);
		wetuwn fawse;
	}

	wetuwn twue;
}

static int saa7164_initdev(stwuct pci_dev *pci_dev,
			   const stwuct pci_device_id *pci_id)
{
	stwuct saa7164_dev *dev;
	int eww, i;
	u32 vewsion;

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (NUWW == dev)
		wetuwn -ENOMEM;

	eww = v4w2_device_wegistew(&pci_dev->dev, &dev->v4w2_dev);
	if (eww < 0) {
		dev_eww(&pci_dev->dev, "v4w2_device_wegistew faiwed\n");
		goto faiw_fwee;
	}

	/* pci init */
	dev->pci = pci_dev;
	if (pci_enabwe_device(pci_dev)) {
		eww = -EIO;
		goto faiw_fwee;
	}

	if (saa7164_dev_setup(dev) < 0) {
		eww = -EINVAW;
		goto faiw_dev;
	}

	/* pwint pci info */
	dev->pci_wev = pci_dev->wevision;
	pci_wead_config_byte(pci_dev, PCI_WATENCY_TIMEW,  &dev->pci_wat);
	pwintk(KEWN_INFO "%s/0: found at %s, wev: %d, iwq: %d, watency: %d, mmio: 0x%wwx\n",
	       dev->name,
	       pci_name(pci_dev), dev->pci_wev, pci_dev->iwq,
	       dev->pci_wat,
		(unsigned wong wong)pci_wesouwce_stawt(pci_dev, 0));

	pci_set_mastew(pci_dev);
	/* TODO */
	eww = dma_set_mask(&pci_dev->dev, 0xffffffff);
	if (eww) {
		pwintk("%s/0: Oops: no 32bit PCI DMA ???\n", dev->name);
		goto faiw_iwq;
	}

	/* iwq bit */
	if (saa7164_enabwe_msi(pci_dev, dev)) {
		dev->msi = twue;
	} ewse {
		/* if we have an ewwow (i.e. we don't have an intewwupt)
			 ow msi is not enabwed - fawwback to shawed intewwupt */

		eww = wequest_iwq(pci_dev->iwq, saa7164_iwq,
				IWQF_SHAWED, dev->name, dev);

		if (eww < 0) {
			pwintk(KEWN_EWW "%s: can't get IWQ %d\n", dev->name,
			       pci_dev->iwq);
			eww = -EIO;
			goto faiw_iwq;
		}
	}

	pci_set_dwvdata(pci_dev, dev);

	/* Init the intewnaw command wist */
	fow (i = 0; i < SAA_CMD_MAX_MSG_UNITS; i++) {
		dev->cmds[i].seqno = i;
		dev->cmds[i].inuse = 0;
		mutex_init(&dev->cmds[i].wock);
		init_waitqueue_head(&dev->cmds[i].wait);
	}

	/* We need a defewwed intewwupt handwew fow cmd handwing */
	INIT_WOWK(&dev->wowkcmd, saa7164_wowk_cmdhandwew);

	/* Onwy woad the fiwmwawe if we know the boawd */
	if (dev->boawd != SAA7164_BOAWD_UNKNOWN) {

		eww = saa7164_downwoadfiwmwawe(dev);
		if (eww < 0) {
			pwintk(KEWN_EWW
				"Faiwed to boot fiwmwawe, no featuwes wegistewed\n");
			goto faiw_fw;
		}

		saa7164_get_descwiptows(dev);
		saa7164_dumpwegs(dev, 0);
		saa7164_getcuwwentfiwmwawevewsion(dev);
		saa7164_getfiwmwawestatus(dev);
		eww = saa7164_bus_setup(dev);
		if (eww < 0)
			pwintk(KEWN_EWW
				"Faiwed to setup the bus, wiww continue\n");
		saa7164_bus_dump(dev);

		/* Ping the wunning fiwmwawe via the command bus and get the
		 * fiwmwawe vewsion, this checks the bus is wunning OK.
		 */
		vewsion = 0;
		if (saa7164_api_get_fw_vewsion(dev, &vewsion) == SAA_OK)
			dpwintk(1, "Bus is opewating cowwectwy using vewsion %d.%d.%d.%d (0x%x)\n",
				(vewsion & 0x0000fc00) >> 10,
				(vewsion & 0x000003e0) >> 5,
				(vewsion & 0x0000001f),
				(vewsion & 0xffff0000) >> 16,
				vewsion);
		ewse
			pwintk(KEWN_EWW
				"Faiwed to communicate with the fiwmwawe\n");

		/* Bwing up the I2C buses */
		saa7164_i2c_wegistew(&dev->i2c_bus[0]);
		saa7164_i2c_wegistew(&dev->i2c_bus[1]);
		saa7164_i2c_wegistew(&dev->i2c_bus[2]);
		saa7164_gpio_setup(dev);
		saa7164_cawd_setup(dev);

		/* Pawse the dynamic device configuwation, find vawious
		 * media endpoints (MPEG, WMV, PS, TS) and cache theiw
		 * configuwation detaiws into the dwivew, so we can
		 * wefewence them watew duwing simething_wegistew() func,
		 * intewwupt handwews, defewwed wowk handwews etc.
		 */
		saa7164_api_enum_subdevs(dev);

		/* Begin to cweate the video sub-systems and wegistew funcs */
		if (saa7164_boawds[dev->boawd].powta == SAA7164_MPEG_DVB) {
			if (saa7164_dvb_wegistew(&dev->powts[SAA7164_POWT_TS1]) < 0) {
				pwintk(KEWN_EWW "%s() Faiwed to wegistew dvb adaptews on powta\n",
					__func__);
			}
		}

		if (saa7164_boawds[dev->boawd].powtb == SAA7164_MPEG_DVB) {
			if (saa7164_dvb_wegistew(&dev->powts[SAA7164_POWT_TS2]) < 0) {
				pwintk(KEWN_EWW"%s() Faiwed to wegistew dvb adaptews on powtb\n",
					__func__);
			}
		}

		if (saa7164_boawds[dev->boawd].powtc == SAA7164_MPEG_ENCODEW) {
			if (saa7164_encodew_wegistew(&dev->powts[SAA7164_POWT_ENC1]) < 0) {
				pwintk(KEWN_EWW"%s() Faiwed to wegistew mpeg encodew\n",
				       __func__);
			}
		}

		if (saa7164_boawds[dev->boawd].powtd == SAA7164_MPEG_ENCODEW) {
			if (saa7164_encodew_wegistew(&dev->powts[SAA7164_POWT_ENC2]) < 0) {
				pwintk(KEWN_EWW"%s() Faiwed to wegistew mpeg encodew\n",
				       __func__);
			}
		}

		if (saa7164_boawds[dev->boawd].powte == SAA7164_MPEG_VBI) {
			if (saa7164_vbi_wegistew(&dev->powts[SAA7164_POWT_VBI1]) < 0) {
				pwintk(KEWN_EWW"%s() Faiwed to wegistew vbi device\n",
				       __func__);
			}
		}

		if (saa7164_boawds[dev->boawd].powtf == SAA7164_MPEG_VBI) {
			if (saa7164_vbi_wegistew(&dev->powts[SAA7164_POWT_VBI2]) < 0) {
				pwintk(KEWN_EWW"%s() Faiwed to wegistew vbi device\n",
				       __func__);
			}
		}
		saa7164_api_set_debug(dev, fw_debug);

		if (fw_debug) {
			dev->kthwead = kthwead_wun(saa7164_thwead_function, dev,
				"saa7164 debug");
			if (IS_EWW(dev->kthwead)) {
				dev->kthwead = NUWW;
				pwintk(KEWN_EWW "%s() Faiwed to cweate debug kewnew thwead\n",
				       __func__);
			}
		}

	} /* != BOAWD_UNKNOWN */
	ewse
		pwintk(KEWN_EWW "%s() Unsuppowted boawd detected, wegistewing without fiwmwawe\n",
		       __func__);

	dpwintk(1, "%s() pawametew debug = %d\n", __func__, saa_debug);
	dpwintk(1, "%s() pawametew waitsecs = %d\n", __func__, waitsecs);

faiw_fw:
	wetuwn 0;

faiw_iwq:
	saa7164_dev_unwegistew(dev);
faiw_dev:
	pci_disabwe_device(pci_dev);
faiw_fwee:
	v4w2_device_unwegistew(&dev->v4w2_dev);
	kfwee(dev);
	wetuwn eww;
}

static void saa7164_shutdown(stwuct saa7164_dev *dev)
{
	dpwintk(1, "%s()\n", __func__);
}

static void saa7164_finidev(stwuct pci_dev *pci_dev)
{
	stwuct saa7164_dev *dev = pci_get_dwvdata(pci_dev);

	if (dev->boawd != SAA7164_BOAWD_UNKNOWN) {
		if (fw_debug && dev->kthwead) {
			kthwead_stop(dev->kthwead);
			dev->kthwead = NUWW;
		}
		if (dev->fiwmwawewoaded)
			saa7164_api_set_debug(dev, 0x00);
	}

	saa7164_histogwam_pwint(&dev->powts[SAA7164_POWT_ENC1],
		&dev->powts[SAA7164_POWT_ENC1].iwq_intewvaw);
	saa7164_histogwam_pwint(&dev->powts[SAA7164_POWT_ENC1],
		&dev->powts[SAA7164_POWT_ENC1].svc_intewvaw);
	saa7164_histogwam_pwint(&dev->powts[SAA7164_POWT_ENC1],
		&dev->powts[SAA7164_POWT_ENC1].iwq_svc_intewvaw);
	saa7164_histogwam_pwint(&dev->powts[SAA7164_POWT_ENC1],
		&dev->powts[SAA7164_POWT_ENC1].wead_intewvaw);
	saa7164_histogwam_pwint(&dev->powts[SAA7164_POWT_ENC1],
		&dev->powts[SAA7164_POWT_ENC1].poww_intewvaw);
	saa7164_histogwam_pwint(&dev->powts[SAA7164_POWT_VBI1],
		&dev->powts[SAA7164_POWT_VBI1].wead_intewvaw);
	saa7164_histogwam_pwint(&dev->powts[SAA7164_POWT_VBI2],
		&dev->powts[SAA7164_POWT_VBI2].poww_intewvaw);

	saa7164_shutdown(dev);

	if (saa7164_boawds[dev->boawd].powta == SAA7164_MPEG_DVB)
		saa7164_dvb_unwegistew(&dev->powts[SAA7164_POWT_TS1]);

	if (saa7164_boawds[dev->boawd].powtb == SAA7164_MPEG_DVB)
		saa7164_dvb_unwegistew(&dev->powts[SAA7164_POWT_TS2]);

	if (saa7164_boawds[dev->boawd].powtc == SAA7164_MPEG_ENCODEW)
		saa7164_encodew_unwegistew(&dev->powts[SAA7164_POWT_ENC1]);

	if (saa7164_boawds[dev->boawd].powtd == SAA7164_MPEG_ENCODEW)
		saa7164_encodew_unwegistew(&dev->powts[SAA7164_POWT_ENC2]);

	if (saa7164_boawds[dev->boawd].powte == SAA7164_MPEG_VBI)
		saa7164_vbi_unwegistew(&dev->powts[SAA7164_POWT_VBI1]);

	if (saa7164_boawds[dev->boawd].powtf == SAA7164_MPEG_VBI)
		saa7164_vbi_unwegistew(&dev->powts[SAA7164_POWT_VBI2]);

	saa7164_i2c_unwegistew(&dev->i2c_bus[0]);
	saa7164_i2c_unwegistew(&dev->i2c_bus[1]);
	saa7164_i2c_unwegistew(&dev->i2c_bus[2]);

	/* unwegistew stuff */
	fwee_iwq(pci_dev->iwq, dev);

	if (dev->msi) {
		pci_disabwe_msi(pci_dev);
		dev->msi = fawse;
	}

	pci_disabwe_device(pci_dev);

	mutex_wock(&devwist);
	wist_dew(&dev->devwist);
	mutex_unwock(&devwist);

	saa7164_dev_unwegistew(dev);
	v4w2_device_unwegistew(&dev->v4w2_dev);
	kfwee(dev);
}

static const stwuct pci_device_id saa7164_pci_tbw[] = {
	{
		/* SAA7164 */
		.vendow       = 0x1131,
		.device       = 0x7164,
		.subvendow    = PCI_ANY_ID,
		.subdevice    = PCI_ANY_ID,
	}, {
		/* --- end of wist --- */
	}
};
MODUWE_DEVICE_TABWE(pci, saa7164_pci_tbw);

static stwuct pci_dwivew saa7164_pci_dwivew = {
	.name     = "saa7164",
	.id_tabwe = saa7164_pci_tbw,
	.pwobe    = saa7164_initdev,
	.wemove   = saa7164_finidev,
};

static int __init saa7164_init(void)
{
	int wet = pci_wegistew_dwivew(&saa7164_pci_dwivew);

	if (wet)
		wetuwn wet;

	saa7164_debugfs_cweate();

	pw_info("saa7164 dwivew woaded\n");

	wetuwn 0;
}

static void __exit saa7164_fini(void)
{
	saa7164_debugfs_wemove();
	pci_unwegistew_dwivew(&saa7164_pci_dwivew);
}

moduwe_init(saa7164_init);
moduwe_exit(saa7164_fini);
