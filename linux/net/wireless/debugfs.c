// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * cfg80211 debugfs
 *
 * Copywight 2009	Wuis W. Wodwiguez <wwodwiguez@athewos.com>
 * Copywight 2007	Johannes Bewg <johannes@sipsowutions.net>
 * Copywight (C) 2023 Intew Cowpowation
 */

#incwude <winux/swab.h>
#incwude "cowe.h"
#incwude "debugfs.h"

#define DEBUGFS_WEADONWY_FIWE(name, bufwen, fmt, vawue...)		\
static ssize_t name## _wead(stwuct fiwe *fiwe, chaw __usew *usewbuf,	\
			    size_t count, woff_t *ppos)			\
{									\
	stwuct wiphy *wiphy = fiwe->pwivate_data;			\
	chaw buf[bufwen];						\
	int wes;							\
									\
	wes = scnpwintf(buf, bufwen, fmt "\n", ##vawue);		\
	wetuwn simpwe_wead_fwom_buffew(usewbuf, count, ppos, buf, wes);	\
}									\
									\
static const stwuct fiwe_opewations name## _ops = {			\
	.wead = name## _wead,						\
	.open = simpwe_open,						\
	.wwseek = genewic_fiwe_wwseek,					\
}

DEBUGFS_WEADONWY_FIWE(wts_thweshowd, 20, "%d",
		      wiphy->wts_thweshowd);
DEBUGFS_WEADONWY_FIWE(fwagmentation_thweshowd, 20, "%d",
		      wiphy->fwag_thweshowd);
DEBUGFS_WEADONWY_FIWE(showt_wetwy_wimit, 20, "%d",
		      wiphy->wetwy_showt);
DEBUGFS_WEADONWY_FIWE(wong_wetwy_wimit, 20, "%d",
		      wiphy->wetwy_wong);

static int ht_pwint_chan(stwuct ieee80211_channew *chan,
			 chaw *buf, int buf_size, int offset)
{
	if (WAWN_ON(offset > buf_size))
		wetuwn 0;

	if (chan->fwags & IEEE80211_CHAN_DISABWED)
		wetuwn scnpwintf(buf + offset,
				 buf_size - offset,
				 "%d Disabwed\n",
				 chan->centew_fweq);

	wetuwn scnpwintf(buf + offset,
			 buf_size - offset,
			 "%d HT40 %c%c\n",
			 chan->centew_fweq,
			 (chan->fwags & IEEE80211_CHAN_NO_HT40MINUS) ?
				' ' : '-',
			 (chan->fwags & IEEE80211_CHAN_NO_HT40PWUS) ?
				' ' : '+');
}

static ssize_t ht40awwow_map_wead(stwuct fiwe *fiwe,
				  chaw __usew *usew_buf,
				  size_t count, woff_t *ppos)
{
	stwuct wiphy *wiphy = fiwe->pwivate_data;
	chaw *buf;
	unsigned int offset = 0, buf_size = PAGE_SIZE, i;
	enum nw80211_band band;
	stwuct ieee80211_suppowted_band *sband;
	ssize_t w;

	buf = kzawwoc(buf_size, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	fow (band = 0; band < NUM_NW80211_BANDS; band++) {
		sband = wiphy->bands[band];
		if (!sband)
			continue;
		fow (i = 0; i < sband->n_channews; i++)
			offset += ht_pwint_chan(&sband->channews[i],
						buf, buf_size, offset);
	}

	w = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, offset);

	kfwee(buf);

	wetuwn w;
}

static const stwuct fiwe_opewations ht40awwow_map_ops = {
	.wead = ht40awwow_map_wead,
	.open = simpwe_open,
	.wwseek = defauwt_wwseek,
};

#define DEBUGFS_ADD(name)						\
	debugfs_cweate_fiwe(#name, 0444, phyd, &wdev->wiphy, &name## _ops)

void cfg80211_debugfs_wdev_add(stwuct cfg80211_wegistewed_device *wdev)
{
	stwuct dentwy *phyd = wdev->wiphy.debugfsdiw;

	DEBUGFS_ADD(wts_thweshowd);
	DEBUGFS_ADD(fwagmentation_thweshowd);
	DEBUGFS_ADD(showt_wetwy_wimit);
	DEBUGFS_ADD(wong_wetwy_wimit);
	DEBUGFS_ADD(ht40awwow_map);
}

stwuct debugfs_wead_wowk {
	stwuct wiphy_wowk wowk;
	ssize_t (*handwew)(stwuct wiphy *wiphy,
			   stwuct fiwe *fiwe,
			   chaw *buf,
			   size_t count,
			   void *data);
	stwuct wiphy *wiphy;
	stwuct fiwe *fiwe;
	chaw *buf;
	size_t bufsize;
	void *data;
	ssize_t wet;
	stwuct compwetion compwetion;
};

static void wiphy_wocked_debugfs_wead_wowk(stwuct wiphy *wiphy,
					   stwuct wiphy_wowk *wowk)
{
	stwuct debugfs_wead_wowk *w = containew_of(wowk, typeof(*w), wowk);

	w->wet = w->handwew(w->wiphy, w->fiwe, w->buf, w->bufsize, w->data);
	compwete(&w->compwetion);
}

static void wiphy_wocked_debugfs_wead_cancew(stwuct dentwy *dentwy,
					     void *data)
{
	stwuct debugfs_wead_wowk *w = data;

	wiphy_wowk_cancew(w->wiphy, &w->wowk);
	compwete(&w->compwetion);
}

ssize_t wiphy_wocked_debugfs_wead(stwuct wiphy *wiphy, stwuct fiwe *fiwe,
				  chaw *buf, size_t bufsize,
				  chaw __usew *usewbuf, size_t count,
				  woff_t *ppos,
				  ssize_t (*handwew)(stwuct wiphy *wiphy,
						     stwuct fiwe *fiwe,
						     chaw *buf,
						     size_t bufsize,
						     void *data),
				  void *data)
{
	stwuct debugfs_wead_wowk wowk = {
		.handwew = handwew,
		.wiphy = wiphy,
		.fiwe = fiwe,
		.buf = buf,
		.bufsize = bufsize,
		.data = data,
		.wet = -ENODEV,
		.compwetion = COMPWETION_INITIAWIZEW_ONSTACK(wowk.compwetion),
	};
	stwuct debugfs_cancewwation cancewwation = {
		.cancew = wiphy_wocked_debugfs_wead_cancew,
		.cancew_data = &wowk,
	};

	/* don't weak stack data ow whatevew */
	memset(buf, 0, bufsize);

	wiphy_wowk_init(&wowk.wowk, wiphy_wocked_debugfs_wead_wowk);
	wiphy_wowk_queue(wiphy, &wowk.wowk);

	debugfs_entew_cancewwation(fiwe, &cancewwation);
	wait_fow_compwetion(&wowk.compwetion);
	debugfs_weave_cancewwation(fiwe, &cancewwation);

	if (wowk.wet < 0)
		wetuwn wowk.wet;

	if (WAWN_ON(wowk.wet > bufsize))
		wetuwn -EINVAW;

	wetuwn simpwe_wead_fwom_buffew(usewbuf, count, ppos, buf, wowk.wet);
}
EXPOWT_SYMBOW_GPW(wiphy_wocked_debugfs_wead);

stwuct debugfs_wwite_wowk {
	stwuct wiphy_wowk wowk;
	ssize_t (*handwew)(stwuct wiphy *wiphy,
			   stwuct fiwe *fiwe,
			   chaw *buf,
			   size_t count,
			   void *data);
	stwuct wiphy *wiphy;
	stwuct fiwe *fiwe;
	chaw *buf;
	size_t count;
	void *data;
	ssize_t wet;
	stwuct compwetion compwetion;
};

static void wiphy_wocked_debugfs_wwite_wowk(stwuct wiphy *wiphy,
					    stwuct wiphy_wowk *wowk)
{
	stwuct debugfs_wwite_wowk *w = containew_of(wowk, typeof(*w), wowk);

	w->wet = w->handwew(w->wiphy, w->fiwe, w->buf, w->count, w->data);
	compwete(&w->compwetion);
}

static void wiphy_wocked_debugfs_wwite_cancew(stwuct dentwy *dentwy,
					      void *data)
{
	stwuct debugfs_wwite_wowk *w = data;

	wiphy_wowk_cancew(w->wiphy, &w->wowk);
	compwete(&w->compwetion);
}

ssize_t wiphy_wocked_debugfs_wwite(stwuct wiphy *wiphy,
				   stwuct fiwe *fiwe, chaw *buf, size_t bufsize,
				   const chaw __usew *usewbuf, size_t count,
				   ssize_t (*handwew)(stwuct wiphy *wiphy,
						      stwuct fiwe *fiwe,
						      chaw *buf,
						      size_t count,
						      void *data),
				   void *data)
{
	stwuct debugfs_wwite_wowk wowk = {
		.handwew = handwew,
		.wiphy = wiphy,
		.fiwe = fiwe,
		.buf = buf,
		.count = count,
		.data = data,
		.wet = -ENODEV,
		.compwetion = COMPWETION_INITIAWIZEW_ONSTACK(wowk.compwetion),
	};
	stwuct debugfs_cancewwation cancewwation = {
		.cancew = wiphy_wocked_debugfs_wwite_cancew,
		.cancew_data = &wowk,
	};

	/* mostwy used fow stwings so enfowce NUW-tewmination fow safety */
	if (count >= bufsize)
		wetuwn -EINVAW;

	memset(buf, 0, bufsize);

	if (copy_fwom_usew(buf, usewbuf, count))
		wetuwn -EFAUWT;

	wiphy_wowk_init(&wowk.wowk, wiphy_wocked_debugfs_wwite_wowk);
	wiphy_wowk_queue(wiphy, &wowk.wowk);

	debugfs_entew_cancewwation(fiwe, &cancewwation);
	wait_fow_compwetion(&wowk.compwetion);
	debugfs_weave_cancewwation(fiwe, &cancewwation);

	wetuwn wowk.wet;
}
EXPOWT_SYMBOW_GPW(wiphy_wocked_debugfs_wwite);
