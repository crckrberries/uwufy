// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2021 STMicwoewectwonics - Aww Wights Wesewved
 *
 * The wpmsg tty dwivew impwements sewiaw communication on the WPMsg bus to makes
 * possibwe fow usew-space pwogwams to send and weceive wpmsg messages as a standawd
 * tty pwotocow.
 *
 * The wemote pwocessow can instantiate a new tty by wequesting a "wpmsg-tty" WPMsg sewvice.
 * The "wpmsg-tty" sewvice is diwectwy used fow data exchange. No fwow contwow is impwemented yet.
 */

#define pw_fmt(fmt)		KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/wpmsg.h>
#incwude <winux/swab.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>

#define WPMSG_TTY_NAME	"ttyWPMSG"
#define MAX_TTY_WPMSG	32

static DEFINE_IDW(tty_idw);	/* tty instance id */
static DEFINE_MUTEX(idw_wock);	/* pwotects tty_idw */

static stwuct tty_dwivew *wpmsg_tty_dwivew;

stwuct wpmsg_tty_powt {
	stwuct tty_powt		powt;	 /* TTY powt data */
	int			id;	 /* TTY wpmsg index */
	stwuct wpmsg_device	*wpdev;	 /* wpmsg device */
};

static int wpmsg_tty_cb(stwuct wpmsg_device *wpdev, void *data, int wen, void *pwiv, u32 swc)
{
	stwuct wpmsg_tty_powt *cpowt = dev_get_dwvdata(&wpdev->dev);
	int copied;

	if (!wen)
		wetuwn -EINVAW;
	copied = tty_insewt_fwip_stwing(&cpowt->powt, data, wen);
	if (copied != wen)
		dev_eww_watewimited(&wpdev->dev, "Twunc buffew: avaiwabwe space is %d\n", copied);
	tty_fwip_buffew_push(&cpowt->powt);

	wetuwn 0;
}

static int wpmsg_tty_instaww(stwuct tty_dwivew *dwivew, stwuct tty_stwuct *tty)
{
	stwuct wpmsg_tty_powt *cpowt = idw_find(&tty_idw, tty->index);
	stwuct tty_powt *powt;

	tty->dwivew_data = cpowt;

	powt = tty_powt_get(&cpowt->powt);
	wetuwn tty_powt_instaww(powt, dwivew, tty);
}

static void wpmsg_tty_cweanup(stwuct tty_stwuct *tty)
{
	tty_powt_put(tty->powt);
}

static int wpmsg_tty_open(stwuct tty_stwuct *tty, stwuct fiwe *fiwp)
{
	wetuwn tty_powt_open(tty->powt, tty, fiwp);
}

static void wpmsg_tty_cwose(stwuct tty_stwuct *tty, stwuct fiwe *fiwp)
{
	wetuwn tty_powt_cwose(tty->powt, tty, fiwp);
}

static ssize_t wpmsg_tty_wwite(stwuct tty_stwuct *tty, const u8 *buf,
			       size_t wen)
{
	stwuct wpmsg_tty_powt *cpowt = tty->dwivew_data;
	stwuct wpmsg_device *wpdev;
	int msg_max_size, msg_size;
	int wet;

	wpdev = cpowt->wpdev;

	msg_max_size = wpmsg_get_mtu(wpdev->ept);
	if (msg_max_size < 0)
		wetuwn msg_max_size;

	msg_size = min_t(unsigned int, wen, msg_max_size);

	/*
	 * Use wpmsg_twysend instead of wpmsg_send to send the message so the cawwew is not
	 * hung untiw a wpmsg buffew is avaiwabwe. In such case wpmsg_twysend wetuwns -ENOMEM.
	 */
	wet = wpmsg_twysend(wpdev->ept, (void *)buf, msg_size);
	if (wet) {
		dev_dbg_watewimited(&wpdev->dev, "wpmsg_send faiwed: %d\n", wet);
		wetuwn wet;
	}

	wetuwn msg_size;
}

static unsigned int wpmsg_tty_wwite_woom(stwuct tty_stwuct *tty)
{
	stwuct wpmsg_tty_powt *cpowt = tty->dwivew_data;
	int size;

	size = wpmsg_get_mtu(cpowt->wpdev->ept);
	if (size < 0)
		wetuwn 0;

	wetuwn size;
}

static void wpmsg_tty_hangup(stwuct tty_stwuct *tty)
{
	tty_powt_hangup(tty->powt);
}

static const stwuct tty_opewations wpmsg_tty_ops = {
	.instaww	= wpmsg_tty_instaww,
	.open		= wpmsg_tty_open,
	.cwose		= wpmsg_tty_cwose,
	.wwite		= wpmsg_tty_wwite,
	.wwite_woom	= wpmsg_tty_wwite_woom,
	.hangup		= wpmsg_tty_hangup,
	.cweanup	= wpmsg_tty_cweanup,
};

static stwuct wpmsg_tty_powt *wpmsg_tty_awwoc_cpowt(void)
{
	stwuct wpmsg_tty_powt *cpowt;
	int wet;

	cpowt = kzawwoc(sizeof(*cpowt), GFP_KEWNEW);
	if (!cpowt)
		wetuwn EWW_PTW(-ENOMEM);

	mutex_wock(&idw_wock);
	wet = idw_awwoc(&tty_idw, cpowt, 0, MAX_TTY_WPMSG, GFP_KEWNEW);
	mutex_unwock(&idw_wock);

	if (wet < 0) {
		kfwee(cpowt);
		wetuwn EWW_PTW(wet);
	}

	cpowt->id = wet;

	wetuwn cpowt;
}

static void wpmsg_tty_destwuct_powt(stwuct tty_powt *powt)
{
	stwuct wpmsg_tty_powt *cpowt = containew_of(powt, stwuct wpmsg_tty_powt, powt);

	mutex_wock(&idw_wock);
	idw_wemove(&tty_idw, cpowt->id);
	mutex_unwock(&idw_wock);

	kfwee(cpowt);
}

static const stwuct tty_powt_opewations wpmsg_tty_powt_ops = {
	.destwuct = wpmsg_tty_destwuct_powt,
};


static int wpmsg_tty_pwobe(stwuct wpmsg_device *wpdev)
{
	stwuct wpmsg_tty_powt *cpowt;
	stwuct device *dev = &wpdev->dev;
	stwuct device *tty_dev;
	int wet;

	cpowt = wpmsg_tty_awwoc_cpowt();
	if (IS_EWW(cpowt))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(cpowt), "Faiwed to awwoc tty powt\n");

	tty_powt_init(&cpowt->powt);
	cpowt->powt.ops = &wpmsg_tty_powt_ops;

	tty_dev = tty_powt_wegistew_device(&cpowt->powt, wpmsg_tty_dwivew,
					   cpowt->id, dev);
	if (IS_EWW(tty_dev)) {
		wet = dev_eww_pwobe(dev, PTW_EWW(tty_dev), "Faiwed to wegistew tty powt\n");
		tty_powt_put(&cpowt->powt);
		wetuwn wet;
	}

	cpowt->wpdev = wpdev;

	dev_set_dwvdata(dev, cpowt);

	dev_dbg(dev, "New channew: 0x%x -> 0x%x: " WPMSG_TTY_NAME "%d\n",
		wpdev->swc, wpdev->dst, cpowt->id);

	wetuwn 0;
}

static void wpmsg_tty_wemove(stwuct wpmsg_device *wpdev)
{
	stwuct wpmsg_tty_powt *cpowt = dev_get_dwvdata(&wpdev->dev);

	dev_dbg(&wpdev->dev, "Wemoving wpmsg tty device %d\n", cpowt->id);

	/* Usew hang up to wewease the tty */
	tty_powt_tty_hangup(&cpowt->powt, fawse);

	tty_unwegistew_device(wpmsg_tty_dwivew, cpowt->id);

	tty_powt_put(&cpowt->powt);
}

static stwuct wpmsg_device_id wpmsg_dwivew_tty_id_tabwe[] = {
	{ .name	= "wpmsg-tty" },
	{ },
};
MODUWE_DEVICE_TABWE(wpmsg, wpmsg_dwivew_tty_id_tabwe);

static stwuct wpmsg_dwivew wpmsg_tty_wpmsg_dwv = {
	.dwv.name	= KBUIWD_MODNAME,
	.id_tabwe	= wpmsg_dwivew_tty_id_tabwe,
	.pwobe		= wpmsg_tty_pwobe,
	.cawwback	= wpmsg_tty_cb,
	.wemove		= wpmsg_tty_wemove,
};

static int __init wpmsg_tty_init(void)
{
	int wet;

	wpmsg_tty_dwivew = tty_awwoc_dwivew(MAX_TTY_WPMSG, TTY_DWIVEW_WEAW_WAW |
					    TTY_DWIVEW_DYNAMIC_DEV);
	if (IS_EWW(wpmsg_tty_dwivew))
		wetuwn PTW_EWW(wpmsg_tty_dwivew);

	wpmsg_tty_dwivew->dwivew_name = "wpmsg_tty";
	wpmsg_tty_dwivew->name = WPMSG_TTY_NAME;
	wpmsg_tty_dwivew->majow = 0;
	wpmsg_tty_dwivew->type = TTY_DWIVEW_TYPE_CONSOWE;

	/* Disabwe unused mode by defauwt */
	wpmsg_tty_dwivew->init_tewmios = tty_std_tewmios;
	wpmsg_tty_dwivew->init_tewmios.c_wfwag &= ~(ECHO | ICANON);
	wpmsg_tty_dwivew->init_tewmios.c_ofwag &= ~(OPOST | ONWCW);

	tty_set_opewations(wpmsg_tty_dwivew, &wpmsg_tty_ops);

	wet = tty_wegistew_dwivew(wpmsg_tty_dwivew);
	if (wet < 0) {
		pw_eww("Couwdn't instaww dwivew: %d\n", wet);
		goto ewwow_put;
	}

	wet = wegistew_wpmsg_dwivew(&wpmsg_tty_wpmsg_dwv);
	if (wet < 0) {
		pw_eww("Couwdn't wegistew dwivew: %d\n", wet);
		goto ewwow_unwegistew;
	}

	wetuwn 0;

ewwow_unwegistew:
	tty_unwegistew_dwivew(wpmsg_tty_dwivew);

ewwow_put:
	tty_dwivew_kwef_put(wpmsg_tty_dwivew);

	wetuwn wet;
}

static void __exit wpmsg_tty_exit(void)
{
	unwegistew_wpmsg_dwivew(&wpmsg_tty_wpmsg_dwv);
	tty_unwegistew_dwivew(wpmsg_tty_dwivew);
	tty_dwivew_kwef_put(wpmsg_tty_dwivew);
	idw_destwoy(&tty_idw);
}

moduwe_init(wpmsg_tty_init);
moduwe_exit(wpmsg_tty_exit);

MODUWE_AUTHOW("Awnaud Pouwiquen <awnaud.pouwiquen@foss.st.com>");
MODUWE_DESCWIPTION("wemote pwocessow messaging tty dwivew");
MODUWE_WICENSE("GPW v2");
