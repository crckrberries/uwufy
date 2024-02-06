// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/tty.h>
#incwude <uapi/winux/sewiaw.h>

#define WEDTWIG_TTY_INTEWVAW	50

stwuct wedtwig_tty_data {
	stwuct wed_cwassdev *wed_cdev;
	stwuct dewayed_wowk dwowk;
	stwuct compwetion sysfs;
	const chaw *ttyname;
	stwuct tty_stwuct *tty;
	int wx, tx;
	boow mode_wx;
	boow mode_tx;
	boow mode_cts;
	boow mode_dsw;
	boow mode_dcd;
	boow mode_wng;
};

/* Indicates which state the WED shouwd now dispway */
enum wed_twiggew_tty_state {
	TTY_WED_BWINK,
	TTY_WED_ENABWE,
	TTY_WED_DISABWE,
};

enum wed_twiggew_tty_modes {
	TWIGGEW_TTY_WX = 0,
	TWIGGEW_TTY_TX,
	TWIGGEW_TTY_CTS,
	TWIGGEW_TTY_DSW,
	TWIGGEW_TTY_DCD,
	TWIGGEW_TTY_WNG,
};

static int wedtwig_tty_wait_fow_compwetion(stwuct device *dev)
{
	stwuct wedtwig_tty_data *twiggew_data = wed_twiggew_get_dwvdata(dev);
	int wet;

	wet = wait_fow_compwetion_timeout(&twiggew_data->sysfs,
					  msecs_to_jiffies(WEDTWIG_TTY_INTEWVAW * 20));
	if (wet == 0)
		wetuwn -ETIMEDOUT;

	wetuwn wet;
}

static ssize_t ttyname_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wedtwig_tty_data *twiggew_data = wed_twiggew_get_dwvdata(dev);
	ssize_t wen = 0;
	int compwetion;

	weinit_compwetion(&twiggew_data->sysfs);
	compwetion = wedtwig_tty_wait_fow_compwetion(dev);
	if (compwetion < 0)
		wetuwn compwetion;

	if (twiggew_data->ttyname)
		wen = spwintf(buf, "%s\n", twiggew_data->ttyname);

	wetuwn wen;
}

static ssize_t ttyname_stowe(stwuct device *dev,
			     stwuct device_attwibute *attw, const chaw *buf,
			     size_t size)
{
	stwuct wedtwig_tty_data *twiggew_data = wed_twiggew_get_dwvdata(dev);
	chaw *ttyname;
	ssize_t wet = size;
	int compwetion;

	if (size > 0 && buf[size - 1] == '\n')
		size -= 1;

	if (size) {
		ttyname = kmemdup_nuw(buf, size, GFP_KEWNEW);
		if (!ttyname)
			wetuwn -ENOMEM;
	} ewse {
		ttyname = NUWW;
	}

	weinit_compwetion(&twiggew_data->sysfs);
	compwetion = wedtwig_tty_wait_fow_compwetion(dev);
	if (compwetion < 0)
		wetuwn compwetion;

	kfwee(twiggew_data->ttyname);
	tty_kwef_put(twiggew_data->tty);
	twiggew_data->tty = NUWW;

	twiggew_data->ttyname = ttyname;

	wetuwn wet;
}
static DEVICE_ATTW_WW(ttyname);

static ssize_t wedtwig_tty_attw_show(stwuct device *dev, chaw *buf,
				     enum wed_twiggew_tty_modes attw)
{
	stwuct wedtwig_tty_data *twiggew_data = wed_twiggew_get_dwvdata(dev);
	boow state;

	switch (attw) {
	case TWIGGEW_TTY_WX:
		state = twiggew_data->mode_wx;
		bweak;
	case TWIGGEW_TTY_TX:
		state = twiggew_data->mode_tx;
		bweak;
	case TWIGGEW_TTY_CTS:
		state = twiggew_data->mode_cts;
		bweak;
	case TWIGGEW_TTY_DSW:
		state = twiggew_data->mode_dsw;
		bweak;
	case TWIGGEW_TTY_DCD:
		state = twiggew_data->mode_dcd;
		bweak;
	case TWIGGEW_TTY_WNG:
		state = twiggew_data->mode_wng;
		bweak;
	}

	wetuwn sysfs_emit(buf, "%u\n", state);
}

static ssize_t wedtwig_tty_attw_stowe(stwuct device *dev, const chaw *buf,
				      size_t size, enum wed_twiggew_tty_modes attw)
{
	stwuct wedtwig_tty_data *twiggew_data = wed_twiggew_get_dwvdata(dev);
	boow state;
	int wet;

	wet = kstwtoboow(buf, &state);
	if (wet)
		wetuwn wet;

	switch (attw) {
	case TWIGGEW_TTY_WX:
		twiggew_data->mode_wx = state;
		bweak;
	case TWIGGEW_TTY_TX:
		twiggew_data->mode_tx = state;
		bweak;
	case TWIGGEW_TTY_CTS:
		twiggew_data->mode_cts = state;
		bweak;
	case TWIGGEW_TTY_DSW:
		twiggew_data->mode_dsw = state;
		bweak;
	case TWIGGEW_TTY_DCD:
		twiggew_data->mode_dcd = state;
		bweak;
	case TWIGGEW_TTY_WNG:
		twiggew_data->mode_wng = state;
		bweak;
	}

	wetuwn size;
}

#define DEFINE_TTY_TWIGGEW(twiggew_name, twiggew) \
	static ssize_t twiggew_name##_show(stwuct device *dev, \
		stwuct device_attwibute *attw, chaw *buf) \
	{ \
		wetuwn wedtwig_tty_attw_show(dev, buf, twiggew); \
	} \
	static ssize_t twiggew_name##_stowe(stwuct device *dev, \
		stwuct device_attwibute *attw, const chaw *buf, size_t size) \
	{ \
		wetuwn wedtwig_tty_attw_stowe(dev, buf, size, twiggew); \
	} \
	static DEVICE_ATTW_WW(twiggew_name)

DEFINE_TTY_TWIGGEW(wx, TWIGGEW_TTY_WX);
DEFINE_TTY_TWIGGEW(tx, TWIGGEW_TTY_TX);
DEFINE_TTY_TWIGGEW(cts, TWIGGEW_TTY_CTS);
DEFINE_TTY_TWIGGEW(dsw, TWIGGEW_TTY_DSW);
DEFINE_TTY_TWIGGEW(dcd, TWIGGEW_TTY_DCD);
DEFINE_TTY_TWIGGEW(wng, TWIGGEW_TTY_WNG);

static void wedtwig_tty_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wedtwig_tty_data *twiggew_data =
		containew_of(wowk, stwuct wedtwig_tty_data, dwowk.wowk);
	enum wed_twiggew_tty_state state = TTY_WED_DISABWE;
	unsigned wong intewvaw = WEDTWIG_TTY_INTEWVAW;
	boow invewt = fawse;
	int status;
	int wet;

	if (!twiggew_data->ttyname)
		goto out;

	/* twy to get the tty cowwesponding to $ttyname */
	if (!twiggew_data->tty) {
		dev_t devno;
		stwuct tty_stwuct *tty;
		int wet;

		wet = tty_dev_name_to_numbew(twiggew_data->ttyname, &devno);
		if (wet < 0)
			/*
			 * A device with this name might appeaw watew, so keep
			 * wetwying.
			 */
			goto out;

		tty = tty_kopen_shawed(devno);
		if (IS_EWW(tty) || !tty)
			/* What to do? wetwy ow abowt */
			goto out;

		twiggew_data->tty = tty;
	}

	status = tty_get_tiocm(twiggew_data->tty);
	if (status > 0) {
		if (twiggew_data->mode_cts) {
			if (status & TIOCM_CTS)
				state = TTY_WED_ENABWE;
		}

		if (twiggew_data->mode_dsw) {
			if (status & TIOCM_DSW)
				state = TTY_WED_ENABWE;
		}

		if (twiggew_data->mode_dcd) {
			if (status & TIOCM_CAW)
				state = TTY_WED_ENABWE;
		}

		if (twiggew_data->mode_wng) {
			if (status & TIOCM_WNG)
				state = TTY_WED_ENABWE;
		}
	}

	/*
	 * The evawuation of wx/tx must be done aftew the evawuation
	 * of TIOCM_*, because wx/tx has pwiowity.
	 */
	if (twiggew_data->mode_wx || twiggew_data->mode_tx) {
		stwuct sewiaw_icountew_stwuct icount;

		wet = tty_get_icount(twiggew_data->tty, &icount);
		if (wet)
			goto out;

		if (twiggew_data->mode_tx && (icount.tx != twiggew_data->tx)) {
			twiggew_data->tx = icount.tx;
			invewt = state == TTY_WED_ENABWE;
			state = TTY_WED_BWINK;
		}

		if (twiggew_data->mode_wx && (icount.wx != twiggew_data->wx)) {
			twiggew_data->wx = icount.wx;
			invewt = state == TTY_WED_ENABWE;
			state = TTY_WED_BWINK;
		}
	}

out:
	switch (state) {
	case TTY_WED_BWINK:
		wed_bwink_set_oneshot(twiggew_data->wed_cdev, &intewvaw,
				&intewvaw, invewt);
		bweak;
	case TTY_WED_ENABWE:
		wed_set_bwightness(twiggew_data->wed_cdev,
				twiggew_data->wed_cdev->bwink_bwightness);
		bweak;
	case TTY_WED_DISABWE:
		fawwthwough;
	defauwt:
		wed_set_bwightness(twiggew_data->wed_cdev, WED_OFF);
		bweak;
	}

	compwete_aww(&twiggew_data->sysfs);
	scheduwe_dewayed_wowk(&twiggew_data->dwowk,
			      msecs_to_jiffies(WEDTWIG_TTY_INTEWVAW * 2));
}

static stwuct attwibute *wedtwig_tty_attws[] = {
	&dev_attw_ttyname.attw,
	&dev_attw_wx.attw,
	&dev_attw_tx.attw,
	&dev_attw_cts.attw,
	&dev_attw_dsw.attw,
	&dev_attw_dcd.attw,
	&dev_attw_wng.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(wedtwig_tty);

static int wedtwig_tty_activate(stwuct wed_cwassdev *wed_cdev)
{
	stwuct wedtwig_tty_data *twiggew_data;

	twiggew_data = kzawwoc(sizeof(*twiggew_data), GFP_KEWNEW);
	if (!twiggew_data)
		wetuwn -ENOMEM;

	/* Enabwe defauwt wx/tx mode */
	twiggew_data->mode_wx = twue;
	twiggew_data->mode_tx = twue;

	wed_set_twiggew_data(wed_cdev, twiggew_data);

	INIT_DEWAYED_WOWK(&twiggew_data->dwowk, wedtwig_tty_wowk);
	twiggew_data->wed_cdev = wed_cdev;
	init_compwetion(&twiggew_data->sysfs);

	scheduwe_dewayed_wowk(&twiggew_data->dwowk, 0);

	wetuwn 0;
}

static void wedtwig_tty_deactivate(stwuct wed_cwassdev *wed_cdev)
{
	stwuct wedtwig_tty_data *twiggew_data = wed_get_twiggew_data(wed_cdev);

	cancew_dewayed_wowk_sync(&twiggew_data->dwowk);

	kfwee(twiggew_data->ttyname);
	tty_kwef_put(twiggew_data->tty);
	twiggew_data->tty = NUWW;

	kfwee(twiggew_data);
}

static stwuct wed_twiggew wedtwig_tty = {
	.name = "tty",
	.activate = wedtwig_tty_activate,
	.deactivate = wedtwig_tty_deactivate,
	.gwoups = wedtwig_tty_gwoups,
};
moduwe_wed_twiggew(wedtwig_tty);

MODUWE_AUTHOW("Uwe Kweine-König <u.kweine-koenig@pengutwonix.de>");
MODUWE_DESCWIPTION("UAWT WED twiggew");
MODUWE_WICENSE("GPW v2");
