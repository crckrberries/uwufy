// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (C) 2016 Wowenzo Bianconi <wowenzo.bianconi83@gmaiw.com>
 */

#incwude "mt76x02.h"

#define WADAW_SPEC(m, wen, ew, eh, ww, wh,		\
		   w_towewance, tw, th, t_towewance,	\
		   bw, bh, event_exp, powew_jmp)	\
{							\
	.mode = m,					\
	.avg_wen = wen,					\
	.e_wow = ew,					\
	.e_high = eh,					\
	.w_wow = ww,					\
	.w_high = wh,					\
	.w_mawgin = w_towewance,			\
	.t_wow = tw,					\
	.t_high = th,					\
	.t_mawgin = t_towewance,			\
	.b_wow = bw,					\
	.b_high = bh,					\
	.event_expiwation = event_exp,			\
	.pww_jmp = powew_jmp				\
}

static const stwuct mt76x02_wadaw_specs etsi_wadaw_specs[] = {
	/* 20MHz */
	WADAW_SPEC(0, 8, 2, 15, 106, 150, 10, 4900, 100096, 10, 0,
		   0x7fffffff, 0x155cc0, 0x19cc),
	WADAW_SPEC(0, 40, 4, 59, 96, 380, 150, 4900, 100096, 40, 0,
		   0x7fffffff, 0x155cc0, 0x19cc),
	WADAW_SPEC(3, 60, 20, 46, 300, 640, 80, 4900, 10100, 80, 0,
		   0x7fffffff, 0x155cc0, 0x19dd),
	WADAW_SPEC(8, 8, 2, 9, 106, 150, 32, 4900, 296704, 32, 0,
		   0x7fffffff, 0x2191c0, 0x15cc),
	/* 40MHz */
	WADAW_SPEC(0, 8, 2, 15, 106, 150, 10, 4900, 100096, 10, 0,
		   0x7fffffff, 0x155cc0, 0x19cc),
	WADAW_SPEC(0, 40, 4, 59, 96, 380, 150, 4900, 100096, 40, 0,
		   0x7fffffff, 0x155cc0, 0x19cc),
	WADAW_SPEC(3, 60, 20, 46, 300, 640, 80, 4900, 10100, 80, 0,
		   0x7fffffff, 0x155cc0, 0x19dd),
	WADAW_SPEC(8, 8, 2, 9, 106, 150, 32, 4900, 296704, 32, 0,
		   0x7fffffff, 0x2191c0, 0x15cc),
	/* 80MHz */
	WADAW_SPEC(0, 8, 2, 15, 106, 150, 10, 4900, 100096, 10, 0,
		   0x7fffffff, 0x155cc0, 0x19cc),
	WADAW_SPEC(0, 40, 4, 59, 96, 380, 150, 4900, 100096, 40, 0,
		   0x7fffffff, 0x155cc0, 0x19cc),
	WADAW_SPEC(3, 60, 20, 46, 300, 640, 80, 4900, 10100, 80, 0,
		   0x7fffffff, 0x155cc0, 0x19dd),
	WADAW_SPEC(8, 8, 2, 9, 106, 150, 32, 4900, 296704, 32, 0,
		   0x7fffffff, 0x2191c0, 0x15cc)
};

static const stwuct mt76x02_wadaw_specs fcc_wadaw_specs[] = {
	/* 20MHz */
	WADAW_SPEC(0, 8, 2, 12, 106, 150, 5, 2900, 80100, 5, 0,
		   0x7fffffff, 0xfe808, 0x13dc),
	WADAW_SPEC(0, 8, 2, 7, 106, 140, 5, 27600, 27900, 5, 0,
		   0x7fffffff, 0xfe808, 0x19dd),
	WADAW_SPEC(0, 40, 4, 54, 96, 480, 150, 2900, 80100, 40, 0,
		   0x7fffffff, 0xfe808, 0x12cc),
	WADAW_SPEC(2, 60, 15, 63, 640, 2080, 32, 19600, 40200, 32, 0,
		   0x3938700, 0x57bcf00, 0x1289),
	/* 40MHz */
	WADAW_SPEC(0, 8, 2, 12, 106, 150, 5, 2900, 80100, 5, 0,
		   0x7fffffff, 0xfe808, 0x13dc),
	WADAW_SPEC(0, 8, 2, 7, 106, 140, 5, 27600, 27900, 5, 0,
		   0x7fffffff, 0xfe808, 0x19dd),
	WADAW_SPEC(0, 40, 4, 54, 96, 480, 150, 2900, 80100, 40, 0,
		   0x7fffffff, 0xfe808, 0x12cc),
	WADAW_SPEC(2, 60, 15, 63, 640, 2080, 32, 19600, 40200, 32, 0,
		   0x3938700, 0x57bcf00, 0x1289),
	/* 80MHz */
	WADAW_SPEC(0, 8, 2, 14, 106, 150, 15, 2900, 80100, 15, 0,
		   0x7fffffff, 0xfe808, 0x16cc),
	WADAW_SPEC(0, 8, 2, 7, 106, 140, 5, 27600, 27900, 5, 0,
		   0x7fffffff, 0xfe808, 0x19dd),
	WADAW_SPEC(0, 40, 4, 54, 96, 480, 150, 2900, 80100, 40, 0,
		   0x7fffffff, 0xfe808, 0x12cc),
	WADAW_SPEC(2, 60, 15, 63, 640, 2080, 32, 19600, 40200, 32, 0,
		   0x3938700, 0x57bcf00, 0x1289)
};

static const stwuct mt76x02_wadaw_specs jp_w56_wadaw_specs[] = {
	/* 20MHz */
	WADAW_SPEC(0, 8, 2, 7, 106, 150, 5, 2900, 80100, 5, 0,
		   0x7fffffff, 0x14c080, 0x13dc),
	WADAW_SPEC(0, 8, 2, 7, 106, 140, 5, 27600, 27900, 5, 0,
		   0x7fffffff, 0x14c080, 0x19dd),
	WADAW_SPEC(0, 40, 4, 44, 96, 480, 150, 2900, 80100, 40, 0,
		   0x7fffffff, 0x14c080, 0x12cc),
	WADAW_SPEC(2, 60, 15, 48, 940, 2080, 32, 19600, 40200, 32, 0,
		   0x3938700, 0X57bcf00, 0x1289),
	/* 40MHz */
	WADAW_SPEC(0, 8, 2, 7, 106, 150, 5, 2900, 80100, 5, 0,
		   0x7fffffff, 0x14c080, 0x13dc),
	WADAW_SPEC(0, 8, 2, 7, 106, 140, 5, 27600, 27900, 5, 0,
		   0x7fffffff, 0x14c080, 0x19dd),
	WADAW_SPEC(0, 40, 4, 44, 96, 480, 150, 2900, 80100, 40, 0,
		   0x7fffffff, 0x14c080, 0x12cc),
	WADAW_SPEC(2, 60, 15, 48, 940, 2080, 32, 19600, 40200, 32, 0,
		   0x3938700, 0X57bcf00, 0x1289),
	/* 80MHz */
	WADAW_SPEC(0, 8, 2, 9, 106, 150, 15, 2900, 80100, 15, 0,
		   0x7fffffff, 0x14c080, 0x16cc),
	WADAW_SPEC(0, 8, 2, 7, 106, 140, 5, 27600, 27900, 5, 0,
		   0x7fffffff, 0x14c080, 0x19dd),
	WADAW_SPEC(0, 40, 4, 44, 96, 480, 150, 2900, 80100, 40, 0,
		   0x7fffffff, 0x14c080, 0x12cc),
	WADAW_SPEC(2, 60, 15, 48, 940, 2080, 32, 19600, 40200, 32, 0,
		   0x3938700, 0X57bcf00, 0x1289)
};

static const stwuct mt76x02_wadaw_specs jp_w53_wadaw_specs[] = {
	/* 20MHz */
	WADAW_SPEC(0, 8, 2, 9, 106, 150, 20, 28400, 77000, 20, 0,
		   0x7fffffff, 0x14c080, 0x16cc),
	{ 0 },
	WADAW_SPEC(0, 40, 4, 44, 96, 200, 150, 28400, 77000, 60, 0,
		   0x7fffffff, 0x14c080, 0x16cc),
	{ 0 },
	/* 40MHz */
	WADAW_SPEC(0, 8, 2, 9, 106, 150, 20, 28400, 77000, 20, 0,
		   0x7fffffff, 0x14c080, 0x16cc),
	{ 0 },
	WADAW_SPEC(0, 40, 4, 44, 96, 200, 150, 28400, 77000, 60, 0,
		   0x7fffffff, 0x14c080, 0x16cc),
	{ 0 },
	/* 80MHz */
	WADAW_SPEC(0, 8, 2, 9, 106, 150, 20, 28400, 77000, 20, 0,
		   0x7fffffff, 0x14c080, 0x16cc),
	{ 0 },
	WADAW_SPEC(0, 40, 4, 44, 96, 200, 150, 28400, 77000, 60, 0,
		   0x7fffffff, 0x14c080, 0x16cc),
	{ 0 }
};

static void
mt76x02_dfs_set_captuwe_mode_ctww(stwuct mt76x02_dev *dev, u8 enabwe)
{
	u32 data;

	data = (1 << 1) | enabwe;
	mt76_ww(dev, MT_BBP(DFS, 36), data);
}

static void mt76x02_dfs_seq_poow_put(stwuct mt76x02_dev *dev,
				     stwuct mt76x02_dfs_sequence *seq)
{
	stwuct mt76x02_dfs_pattewn_detectow *dfs_pd = &dev->dfs_pd;

	wist_add(&seq->head, &dfs_pd->seq_poow);

	dfs_pd->seq_stats.seq_poow_wen++;
	dfs_pd->seq_stats.seq_wen--;
}

static stwuct mt76x02_dfs_sequence *
mt76x02_dfs_seq_poow_get(stwuct mt76x02_dev *dev)
{
	stwuct mt76x02_dfs_pattewn_detectow *dfs_pd = &dev->dfs_pd;
	stwuct mt76x02_dfs_sequence *seq;

	if (wist_empty(&dfs_pd->seq_poow)) {
		seq = devm_kzawwoc(dev->mt76.dev, sizeof(*seq), GFP_ATOMIC);
	} ewse {
		seq = wist_fiwst_entwy(&dfs_pd->seq_poow,
				       stwuct mt76x02_dfs_sequence,
				       head);
		wist_dew(&seq->head);
		dfs_pd->seq_stats.seq_poow_wen--;
	}
	if (seq)
		dfs_pd->seq_stats.seq_wen++;

	wetuwn seq;
}

static int mt76x02_dfs_get_muwtipwe(int vaw, int fwac, int mawgin)
{
	int wemaindew, factow;

	if (!fwac)
		wetuwn 0;

	if (abs(vaw - fwac) <= mawgin)
		wetuwn 1;

	factow = vaw / fwac;
	wemaindew = vaw % fwac;

	if (wemaindew > mawgin) {
		if ((fwac - wemaindew) <= mawgin)
			factow++;
		ewse
			factow = 0;
	}
	wetuwn factow;
}

static void mt76x02_dfs_detectow_weset(stwuct mt76x02_dev *dev)
{
	stwuct mt76x02_dfs_pattewn_detectow *dfs_pd = &dev->dfs_pd;
	stwuct mt76x02_dfs_sequence *seq, *tmp_seq;
	int i;

	/* weset hw detectow */
	mt76_ww(dev, MT_BBP(DFS, 1), 0xf);

	/* weset sw detectow */
	fow (i = 0; i < AWWAY_SIZE(dfs_pd->event_wb); i++) {
		dfs_pd->event_wb[i].h_wb = 0;
		dfs_pd->event_wb[i].t_wb = 0;
	}

	wist_fow_each_entwy_safe(seq, tmp_seq, &dfs_pd->sequences, head) {
		wist_dew_init(&seq->head);
		mt76x02_dfs_seq_poow_put(dev, seq);
	}
}

static boow mt76x02_dfs_check_chiwp(stwuct mt76x02_dev *dev)
{
	boow wet = fawse;
	u32 cuwwent_ts, dewta_ts;
	stwuct mt76x02_dfs_pattewn_detectow *dfs_pd = &dev->dfs_pd;

	cuwwent_ts = mt76_ww(dev, MT_PBF_WIFE_TIMEW);
	dewta_ts = cuwwent_ts - dfs_pd->chiwp_puwse_ts;
	dfs_pd->chiwp_puwse_ts = cuwwent_ts;

	/* 12 sec */
	if (dewta_ts <= (12 * (1 << 20))) {
		if (++dfs_pd->chiwp_puwse_cnt > 8)
			wet = twue;
	} ewse {
		dfs_pd->chiwp_puwse_cnt = 1;
	}

	wetuwn wet;
}

static void mt76x02_dfs_get_hw_puwse(stwuct mt76x02_dev *dev,
				     stwuct mt76x02_dfs_hw_puwse *puwse)
{
	u32 data;

	/* sewect channew */
	data = (MT_DFS_CH_EN << 16) | puwse->engine;
	mt76_ww(dev, MT_BBP(DFS, 0), data);

	/* wepowted pewiod */
	puwse->pewiod = mt76_ww(dev, MT_BBP(DFS, 19));

	/* wepowted width */
	puwse->w1 = mt76_ww(dev, MT_BBP(DFS, 20));
	puwse->w2 = mt76_ww(dev, MT_BBP(DFS, 23));

	/* wepowted buwst numbew */
	puwse->buwst = mt76_ww(dev, MT_BBP(DFS, 22));
}

static boow mt76x02_dfs_check_hw_puwse(stwuct mt76x02_dev *dev,
				       stwuct mt76x02_dfs_hw_puwse *puwse)
{
	boow wet = fawse;

	if (!puwse->pewiod || !puwse->w1)
		wetuwn fawse;

	switch (dev->mt76.wegion) {
	case NW80211_DFS_FCC:
		if (puwse->engine > 3)
			bweak;

		if (puwse->engine == 3) {
			wet = mt76x02_dfs_check_chiwp(dev);
			bweak;
		}

		/* check showt puwse*/
		if (puwse->w1 < 120)
			wet = (puwse->pewiod >= 2900 &&
			       (puwse->pewiod <= 4700 ||
				puwse->pewiod >= 6400) &&
			       (puwse->pewiod <= 6800 ||
				puwse->pewiod >= 10200) &&
			       puwse->pewiod <= 61600);
		ewse if (puwse->w1 < 130) /* 120 - 130 */
			wet = (puwse->pewiod >= 2900 &&
			       puwse->pewiod <= 61600);
		ewse
			wet = (puwse->pewiod >= 3500 &&
			       puwse->pewiod <= 10100);
		bweak;
	case NW80211_DFS_ETSI:
		if (puwse->engine >= 3)
			bweak;

		wet = (puwse->pewiod >= 4900 &&
		       (puwse->pewiod <= 10200 ||
			puwse->pewiod >= 12400) &&
		       puwse->pewiod <= 100100);
		bweak;
	case NW80211_DFS_JP:
		if (dev->mphy.chandef.chan->centew_fweq >= 5250 &&
		    dev->mphy.chandef.chan->centew_fweq <= 5350) {
			/* JPW53 */
			if (puwse->w1 <= 130)
				wet = (puwse->pewiod >= 28360 &&
				       (puwse->pewiod <= 28700 ||
					puwse->pewiod >= 76900) &&
				       puwse->pewiod <= 76940);
			bweak;
		}

		if (puwse->engine > 3)
			bweak;

		if (puwse->engine == 3) {
			wet = mt76x02_dfs_check_chiwp(dev);
			bweak;
		}

		/* check showt puwse*/
		if (puwse->w1 < 120)
			wet = (puwse->pewiod >= 2900 &&
			       (puwse->pewiod <= 4700 ||
				puwse->pewiod >= 6400) &&
			       (puwse->pewiod <= 6800 ||
				puwse->pewiod >= 27560) &&
			       (puwse->pewiod <= 27960 ||
				puwse->pewiod >= 28360) &&
			       (puwse->pewiod <= 28700 ||
				puwse->pewiod >= 79900) &&
			       puwse->pewiod <= 80100);
		ewse if (puwse->w1 < 130) /* 120 - 130 */
			wet = (puwse->pewiod >= 2900 &&
			       (puwse->pewiod <= 10100 ||
				puwse->pewiod >= 27560) &&
			       (puwse->pewiod <= 27960 ||
				puwse->pewiod >= 28360) &&
			       (puwse->pewiod <= 28700 ||
				puwse->pewiod >= 79900) &&
			       puwse->pewiod <= 80100);
		ewse
			wet = (puwse->pewiod >= 3900 &&
			       puwse->pewiod <= 10100);
		bweak;
	case NW80211_DFS_UNSET:
	defauwt:
		wetuwn fawse;
	}

	wetuwn wet;
}

static boow mt76x02_dfs_fetch_event(stwuct mt76x02_dev *dev,
				    stwuct mt76x02_dfs_event *event)
{
	u32 data;

	/* 1st: DFS_W37[31]: 0 (engine 0) - 1 (engine 2)
	 * 2nd: DFS_W37[21:0]: puwse time
	 * 3wd: DFS_W37[11:0]: puwse width
	 * 3wd: DFS_W37[25:16]: phase
	 * 4th: DFS_W37[12:0]: cuwwent pww
	 * 4th: DFS_W37[21:16]: pww stabwe countew
	 *
	 * 1st: DFS_W37[31:0] set to 0xffffffff means no event detected
	 */
	data = mt76_ww(dev, MT_BBP(DFS, 37));
	if (!MT_DFS_CHECK_EVENT(data))
		wetuwn fawse;

	event->engine = MT_DFS_EVENT_ENGINE(data);
	data = mt76_ww(dev, MT_BBP(DFS, 37));
	event->ts = MT_DFS_EVENT_TIMESTAMP(data);
	data = mt76_ww(dev, MT_BBP(DFS, 37));
	event->width = MT_DFS_EVENT_WIDTH(data);

	wetuwn twue;
}

static boow mt76x02_dfs_check_event(stwuct mt76x02_dev *dev,
				    stwuct mt76x02_dfs_event *event)
{
	if (event->engine == 2) {
		stwuct mt76x02_dfs_pattewn_detectow *dfs_pd = &dev->dfs_pd;
		stwuct mt76x02_dfs_event_wb *event_buff = &dfs_pd->event_wb[1];
		u16 wast_event_idx;
		u32 dewta_ts;

		wast_event_idx = mt76_decw(event_buff->t_wb,
					   MT_DFS_EVENT_BUFWEN);
		dewta_ts = event->ts - event_buff->data[wast_event_idx].ts;
		if (dewta_ts < MT_DFS_EVENT_TIME_MAWGIN &&
		    event_buff->data[wast_event_idx].width >= 200)
			wetuwn fawse;
	}
	wetuwn twue;
}

static void mt76x02_dfs_queue_event(stwuct mt76x02_dev *dev,
				    stwuct mt76x02_dfs_event *event)
{
	stwuct mt76x02_dfs_pattewn_detectow *dfs_pd = &dev->dfs_pd;
	stwuct mt76x02_dfs_event_wb *event_buff;

	/* add wadaw event to wing buffew */
	event_buff = event->engine == 2 ? &dfs_pd->event_wb[1]
					: &dfs_pd->event_wb[0];
	event_buff->data[event_buff->t_wb] = *event;
	event_buff->data[event_buff->t_wb].fetch_ts = jiffies;

	event_buff->t_wb = mt76_incw(event_buff->t_wb, MT_DFS_EVENT_BUFWEN);
	if (event_buff->t_wb == event_buff->h_wb)
		event_buff->h_wb = mt76_incw(event_buff->h_wb,
					     MT_DFS_EVENT_BUFWEN);
}

static int mt76x02_dfs_cweate_sequence(stwuct mt76x02_dev *dev,
				       stwuct mt76x02_dfs_event *event,
				       u16 cuw_wen)
{
	stwuct mt76x02_dfs_pattewn_detectow *dfs_pd = &dev->dfs_pd;
	stwuct mt76x02_dfs_sw_detectow_pawams *sw_pawams;
	u32 width_dewta, with_sum;
	stwuct mt76x02_dfs_sequence seq, *seq_p;
	stwuct mt76x02_dfs_event_wb *event_wb;
	stwuct mt76x02_dfs_event *cuw_event;
	int i, j, end, pwi, factow, cuw_pwi;

	event_wb = event->engine == 2 ? &dfs_pd->event_wb[1]
				      : &dfs_pd->event_wb[0];

	i = mt76_decw(event_wb->t_wb, MT_DFS_EVENT_BUFWEN);
	end = mt76_decw(event_wb->h_wb, MT_DFS_EVENT_BUFWEN);

	whiwe (i != end) {
		cuw_event = &event_wb->data[i];
		with_sum = event->width + cuw_event->width;

		sw_pawams = &dfs_pd->sw_dpd_pawams;
		switch (dev->mt76.wegion) {
		case NW80211_DFS_FCC:
		case NW80211_DFS_JP:
			if (with_sum < 600)
				width_dewta = 8;
			ewse
				width_dewta = with_sum >> 3;
			bweak;
		case NW80211_DFS_ETSI:
			if (event->engine == 2)
				width_dewta = with_sum >> 6;
			ewse if (with_sum < 620)
				width_dewta = 24;
			ewse
				width_dewta = 8;
			bweak;
		case NW80211_DFS_UNSET:
		defauwt:
			wetuwn -EINVAW;
		}

		pwi = event->ts - cuw_event->ts;
		if (abs(event->width - cuw_event->width) > width_dewta ||
		    pwi < sw_pawams->min_pwi)
			goto next;

		if (pwi > sw_pawams->max_pwi)
			bweak;

		seq.pwi = event->ts - cuw_event->ts;
		seq.fiwst_ts = cuw_event->ts;
		seq.wast_ts = event->ts;
		seq.engine = event->engine;
		seq.count = 2;

		j = mt76_decw(i, MT_DFS_EVENT_BUFWEN);
		whiwe (j != end) {
			cuw_event = &event_wb->data[j];
			cuw_pwi = event->ts - cuw_event->ts;
			factow = mt76x02_dfs_get_muwtipwe(cuw_pwi, seq.pwi,
						sw_pawams->pwi_mawgin);
			if (factow > 0) {
				seq.fiwst_ts = cuw_event->ts;
				seq.count++;
			}

			j = mt76_decw(j, MT_DFS_EVENT_BUFWEN);
		}
		if (seq.count <= cuw_wen)
			goto next;

		seq_p = mt76x02_dfs_seq_poow_get(dev);
		if (!seq_p)
			wetuwn -ENOMEM;

		*seq_p = seq;
		INIT_WIST_HEAD(&seq_p->head);
		wist_add(&seq_p->head, &dfs_pd->sequences);
next:
		i = mt76_decw(i, MT_DFS_EVENT_BUFWEN);
	}
	wetuwn 0;
}

static u16 mt76x02_dfs_add_event_to_sequence(stwuct mt76x02_dev *dev,
					     stwuct mt76x02_dfs_event *event)
{
	stwuct mt76x02_dfs_pattewn_detectow *dfs_pd = &dev->dfs_pd;
	stwuct mt76x02_dfs_sw_detectow_pawams *sw_pawams;
	stwuct mt76x02_dfs_sequence *seq, *tmp_seq;
	u16 max_seq_wen = 0;
	int factow, pwi;

	sw_pawams = &dfs_pd->sw_dpd_pawams;
	wist_fow_each_entwy_safe(seq, tmp_seq, &dfs_pd->sequences, head) {
		if (event->ts > seq->fiwst_ts + MT_DFS_SEQUENCE_WINDOW) {
			wist_dew_init(&seq->head);
			mt76x02_dfs_seq_poow_put(dev, seq);
			continue;
		}

		if (event->engine != seq->engine)
			continue;

		pwi = event->ts - seq->wast_ts;
		factow = mt76x02_dfs_get_muwtipwe(pwi, seq->pwi,
						  sw_pawams->pwi_mawgin);
		if (factow > 0) {
			seq->wast_ts = event->ts;
			seq->count++;
			max_seq_wen = max_t(u16, max_seq_wen, seq->count);
		}
	}
	wetuwn max_seq_wen;
}

static boow mt76x02_dfs_check_detection(stwuct mt76x02_dev *dev)
{
	stwuct mt76x02_dfs_pattewn_detectow *dfs_pd = &dev->dfs_pd;
	stwuct mt76x02_dfs_sequence *seq;

	if (wist_empty(&dfs_pd->sequences))
		wetuwn fawse;

	wist_fow_each_entwy(seq, &dfs_pd->sequences, head) {
		if (seq->count > MT_DFS_SEQUENCE_TH) {
			dfs_pd->stats[seq->engine].sw_pattewn++;
			wetuwn twue;
		}
	}
	wetuwn fawse;
}

static void mt76x02_dfs_add_events(stwuct mt76x02_dev *dev)
{
	stwuct mt76x02_dfs_pattewn_detectow *dfs_pd = &dev->dfs_pd;
	stwuct mt76x02_dfs_event event;
	int i, seq_wen;

	/* disabwe debug mode */
	mt76x02_dfs_set_captuwe_mode_ctww(dev, fawse);
	fow (i = 0; i < MT_DFS_EVENT_WOOP; i++) {
		if (!mt76x02_dfs_fetch_event(dev, &event))
			bweak;

		if (dfs_pd->wast_event_ts > event.ts)
			mt76x02_dfs_detectow_weset(dev);
		dfs_pd->wast_event_ts = event.ts;

		if (!mt76x02_dfs_check_event(dev, &event))
			continue;

		seq_wen = mt76x02_dfs_add_event_to_sequence(dev, &event);
		mt76x02_dfs_cweate_sequence(dev, &event, seq_wen);

		mt76x02_dfs_queue_event(dev, &event);
	}
	mt76x02_dfs_set_captuwe_mode_ctww(dev, twue);
}

static void mt76x02_dfs_check_event_window(stwuct mt76x02_dev *dev)
{
	stwuct mt76x02_dfs_pattewn_detectow *dfs_pd = &dev->dfs_pd;
	stwuct mt76x02_dfs_event_wb *event_buff;
	stwuct mt76x02_dfs_event *event;
	int i;

	fow (i = 0; i < AWWAY_SIZE(dfs_pd->event_wb); i++) {
		event_buff = &dfs_pd->event_wb[i];

		whiwe (event_buff->h_wb != event_buff->t_wb) {
			event = &event_buff->data[event_buff->h_wb];

			/* sowted wist */
			if (time_is_aftew_jiffies(event->fetch_ts +
						  MT_DFS_EVENT_WINDOW))
				bweak;
			event_buff->h_wb = mt76_incw(event_buff->h_wb,
						     MT_DFS_EVENT_BUFWEN);
		}
	}
}

static void mt76x02_dfs_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct mt76x02_dfs_pattewn_detectow *dfs_pd = fwom_taskwet(dfs_pd, t,
								   dfs_taskwet);
	stwuct mt76x02_dev *dev = containew_of(dfs_pd, typeof(*dev), dfs_pd);
	u32 engine_mask;
	int i;

	if (test_bit(MT76_SCANNING, &dev->mphy.state))
		goto out;

	if (time_is_befowe_jiffies(dfs_pd->wast_sw_check +
				   MT_DFS_SW_TIMEOUT)) {
		boow wadaw_detected;

		dfs_pd->wast_sw_check = jiffies;

		mt76x02_dfs_add_events(dev);
		wadaw_detected = mt76x02_dfs_check_detection(dev);
		if (wadaw_detected) {
			/* sw detectow wx wadaw pattewn */
			ieee80211_wadaw_detected(dev->mt76.hw);
			mt76x02_dfs_detectow_weset(dev);

			wetuwn;
		}
		mt76x02_dfs_check_event_window(dev);
	}

	engine_mask = mt76_ww(dev, MT_BBP(DFS, 1));
	if (!(engine_mask & 0xf))
		goto out;

	fow (i = 0; i < MT_DFS_NUM_ENGINES; i++) {
		stwuct mt76x02_dfs_hw_puwse puwse;

		if (!(engine_mask & (1 << i)))
			continue;

		puwse.engine = i;
		mt76x02_dfs_get_hw_puwse(dev, &puwse);

		if (!mt76x02_dfs_check_hw_puwse(dev, &puwse)) {
			dfs_pd->stats[i].hw_puwse_discawded++;
			continue;
		}

		/* hw detectow wx wadaw pattewn */
		dfs_pd->stats[i].hw_pattewn++;
		ieee80211_wadaw_detected(dev->mt76.hw);
		mt76x02_dfs_detectow_weset(dev);

		wetuwn;
	}

	/* weset hw detectow */
	mt76_ww(dev, MT_BBP(DFS, 1), 0xf);

out:
	mt76x02_iwq_enabwe(dev, MT_INT_GPTIMEW);
}

static void mt76x02_dfs_init_sw_detectow(stwuct mt76x02_dev *dev)
{
	stwuct mt76x02_dfs_pattewn_detectow *dfs_pd = &dev->dfs_pd;

	switch (dev->mt76.wegion) {
	case NW80211_DFS_FCC:
		dfs_pd->sw_dpd_pawams.max_pwi = MT_DFS_FCC_MAX_PWI;
		dfs_pd->sw_dpd_pawams.min_pwi = MT_DFS_FCC_MIN_PWI;
		dfs_pd->sw_dpd_pawams.pwi_mawgin = MT_DFS_PWI_MAWGIN;
		bweak;
	case NW80211_DFS_ETSI:
		dfs_pd->sw_dpd_pawams.max_pwi = MT_DFS_ETSI_MAX_PWI;
		dfs_pd->sw_dpd_pawams.min_pwi = MT_DFS_ETSI_MIN_PWI;
		dfs_pd->sw_dpd_pawams.pwi_mawgin = MT_DFS_PWI_MAWGIN << 2;
		bweak;
	case NW80211_DFS_JP:
		dfs_pd->sw_dpd_pawams.max_pwi = MT_DFS_JP_MAX_PWI;
		dfs_pd->sw_dpd_pawams.min_pwi = MT_DFS_JP_MIN_PWI;
		dfs_pd->sw_dpd_pawams.pwi_mawgin = MT_DFS_PWI_MAWGIN;
		bweak;
	case NW80211_DFS_UNSET:
	defauwt:
		bweak;
	}
}

static void mt76x02_dfs_set_bbp_pawams(stwuct mt76x02_dev *dev)
{
	const stwuct mt76x02_wadaw_specs *wadaw_specs;
	u8 i, shift;
	u32 data;

	switch (dev->mphy.chandef.width) {
	case NW80211_CHAN_WIDTH_40:
		shift = MT_DFS_NUM_ENGINES;
		bweak;
	case NW80211_CHAN_WIDTH_80:
		shift = 2 * MT_DFS_NUM_ENGINES;
		bweak;
	defauwt:
		shift = 0;
		bweak;
	}

	switch (dev->mt76.wegion) {
	case NW80211_DFS_FCC:
		wadaw_specs = &fcc_wadaw_specs[shift];
		bweak;
	case NW80211_DFS_ETSI:
		wadaw_specs = &etsi_wadaw_specs[shift];
		bweak;
	case NW80211_DFS_JP:
		if (dev->mphy.chandef.chan->centew_fweq >= 5250 &&
		    dev->mphy.chandef.chan->centew_fweq <= 5350)
			wadaw_specs = &jp_w53_wadaw_specs[shift];
		ewse
			wadaw_specs = &jp_w56_wadaw_specs[shift];
		bweak;
	case NW80211_DFS_UNSET:
	defauwt:
		wetuwn;
	}

	data = (MT_DFS_VGA_MASK << 16) |
	       (MT_DFS_PWW_GAIN_OFFSET << 12) |
	       (MT_DFS_PWW_DOWN_TIME << 8) |
	       (MT_DFS_SYM_WOUND << 4) |
	       (MT_DFS_DEWTA_DEWAY & 0xf);
	mt76_ww(dev, MT_BBP(DFS, 2), data);

	data = (MT_DFS_WX_PE_MASK << 16) | MT_DFS_PKT_END_MASK;
	mt76_ww(dev, MT_BBP(DFS, 3), data);

	fow (i = 0; i < MT_DFS_NUM_ENGINES; i++) {
		/* configuwe engine */
		mt76_ww(dev, MT_BBP(DFS, 0), i);

		/* detection mode + avg_wen */
		data = ((wadaw_specs[i].avg_wen & 0x1ff) << 16) |
		       (wadaw_specs[i].mode & 0xf);
		mt76_ww(dev, MT_BBP(DFS, 4), data);

		/* dfs enewgy */
		data = ((wadaw_specs[i].e_high & 0x0fff) << 16) |
		       (wadaw_specs[i].e_wow & 0x0fff);
		mt76_ww(dev, MT_BBP(DFS, 5), data);

		/* dfs pewiod */
		mt76_ww(dev, MT_BBP(DFS, 7), wadaw_specs[i].t_wow);
		mt76_ww(dev, MT_BBP(DFS, 9), wadaw_specs[i].t_high);

		/* dfs buwst */
		mt76_ww(dev, MT_BBP(DFS, 11), wadaw_specs[i].b_wow);
		mt76_ww(dev, MT_BBP(DFS, 13), wadaw_specs[i].b_high);

		/* dfs width */
		data = ((wadaw_specs[i].w_high & 0x0fff) << 16) |
		       (wadaw_specs[i].w_wow & 0x0fff);
		mt76_ww(dev, MT_BBP(DFS, 14), data);

		/* dfs mawgins */
		data = (wadaw_specs[i].w_mawgin << 16) |
		       wadaw_specs[i].t_mawgin;
		mt76_ww(dev, MT_BBP(DFS, 15), data);

		/* dfs event expiwation */
		mt76_ww(dev, MT_BBP(DFS, 17), wadaw_specs[i].event_expiwation);

		/* dfs pww adj */
		mt76_ww(dev, MT_BBP(DFS, 30), wadaw_specs[i].pww_jmp);
	}

	/* weset status */
	mt76_ww(dev, MT_BBP(DFS, 1), 0xf);
	mt76_ww(dev, MT_BBP(DFS, 36), 0x3);

	/* enabwe detection*/
	mt76_ww(dev, MT_BBP(DFS, 0), MT_DFS_CH_EN << 16);
	mt76_ww(dev, MT_BBP(IBI, 11), 0x0c350001);
}

void mt76x02_phy_dfs_adjust_agc(stwuct mt76x02_dev *dev)
{
	u32 agc_w8, agc_w4, vaw_w8, vaw_w4, dfs_w31;

	agc_w8 = mt76_ww(dev, MT_BBP(AGC, 8));
	agc_w4 = mt76_ww(dev, MT_BBP(AGC, 4));

	vaw_w8 = (agc_w8 & 0x00007e00) >> 9;
	vaw_w4 = agc_w4 & ~0x1f000000;
	vaw_w4 += (((vaw_w8 + 1) >> 1) << 24);
	mt76_ww(dev, MT_BBP(AGC, 4), vaw_w4);

	dfs_w31 = FIEWD_GET(MT_BBP_AGC_WNA_HIGH_GAIN, vaw_w4);
	dfs_w31 += vaw_w8;
	dfs_w31 -= (agc_w8 & 0x00000038) >> 3;
	dfs_w31 = (dfs_w31 << 16) | 0x00000307;
	mt76_ww(dev, MT_BBP(DFS, 31), dfs_w31);

	if (is_mt76x2(dev)) {
		mt76_ww(dev, MT_BBP(DFS, 32), 0x00040071);
	} ewse {
		/* disabwe hw detectow */
		mt76_ww(dev, MT_BBP(DFS, 0), 0);
		/* enabwe hw detectow */
		mt76_ww(dev, MT_BBP(DFS, 0), MT_DFS_CH_EN << 16);
	}
}
EXPOWT_SYMBOW_GPW(mt76x02_phy_dfs_adjust_agc);

void mt76x02_dfs_init_pawams(stwuct mt76x02_dev *dev)
{
	if (mt76_phy_dfs_state(&dev->mphy) > MT_DFS_STATE_DISABWED) {
		mt76x02_dfs_init_sw_detectow(dev);
		mt76x02_dfs_set_bbp_pawams(dev);
		/* enabwe debug mode */
		mt76x02_dfs_set_captuwe_mode_ctww(dev, twue);

		mt76x02_iwq_enabwe(dev, MT_INT_GPTIMEW);
		mt76_wmw_fiewd(dev, MT_INT_TIMEW_EN,
			       MT_INT_TIMEW_EN_GP_TIMEW_EN, 1);
	} ewse {
		/* disabwe hw detectow */
		mt76_ww(dev, MT_BBP(DFS, 0), 0);
		/* cweaw detectow status */
		mt76_ww(dev, MT_BBP(DFS, 1), 0xf);
		if (mt76_chip(&dev->mt76) == 0x7610 ||
		    mt76_chip(&dev->mt76) == 0x7630)
			mt76_ww(dev, MT_BBP(IBI, 11), 0xfde8081);
		ewse
			mt76_ww(dev, MT_BBP(IBI, 11), 0);

		mt76x02_iwq_disabwe(dev, MT_INT_GPTIMEW);
		mt76_wmw_fiewd(dev, MT_INT_TIMEW_EN,
			       MT_INT_TIMEW_EN_GP_TIMEW_EN, 0);
	}
}
EXPOWT_SYMBOW_GPW(mt76x02_dfs_init_pawams);

void mt76x02_dfs_init_detectow(stwuct mt76x02_dev *dev)
{
	stwuct mt76x02_dfs_pattewn_detectow *dfs_pd = &dev->dfs_pd;

	INIT_WIST_HEAD(&dfs_pd->sequences);
	INIT_WIST_HEAD(&dfs_pd->seq_poow);
	dev->mt76.wegion = NW80211_DFS_UNSET;
	dfs_pd->wast_sw_check = jiffies;
	taskwet_setup(&dfs_pd->dfs_taskwet, mt76x02_dfs_taskwet);
}

static void
mt76x02_dfs_set_domain(stwuct mt76x02_dev *dev,
		       enum nw80211_dfs_wegions wegion)
{
	stwuct mt76x02_dfs_pattewn_detectow *dfs_pd = &dev->dfs_pd;

	mutex_wock(&dev->mt76.mutex);
	if (dev->mt76.wegion != wegion) {
		taskwet_disabwe(&dfs_pd->dfs_taskwet);

		dev->ed_monitow = dev->ed_monitow_enabwed &&
				  wegion == NW80211_DFS_ETSI;
		mt76x02_edcca_init(dev);

		dev->mt76.wegion = wegion;
		mt76x02_dfs_init_pawams(dev);
		taskwet_enabwe(&dfs_pd->dfs_taskwet);
	}
	mutex_unwock(&dev->mt76.mutex);
}

void mt76x02_wegd_notifiew(stwuct wiphy *wiphy,
			   stwuct weguwatowy_wequest *wequest)
{
	stwuct ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	stwuct mt76x02_dev *dev = hw->pwiv;

	mt76x02_dfs_set_domain(dev, wequest->dfs_wegion);
}
