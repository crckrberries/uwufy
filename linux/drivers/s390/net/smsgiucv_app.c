// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dewivew z/VM CP speciaw messages (SMSG) as uevents.
 *
 * The dwivew wegistews fow z/VM CP speciaw messages with the
 * "APP" pwefix. Incoming messages awe dewivewed to usew space
 * as uevents.
 *
 * Copywight IBM Cowp. 2010
 * Authow(s): Hendwik Bwuecknew <bwuecknew@winux.vnet.ibm.com>
 *
 */
#define KMSG_COMPONENT		"smsgiucv_app"
#define pw_fmt(fmt)		KMSG_COMPONENT ": " fmt

#incwude <winux/ctype.h>
#incwude <winux/eww.h>
#incwude <winux/device.h>
#incwude <winux/wist.h>
#incwude <winux/kobject.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/wowkqueue.h>
#incwude <net/iucv/iucv.h>
#incwude "smsgiucv.h"

/* pwefix used fow SMSG wegistwation */
#define SMSG_PWEFIX		"APP"

/* SMSG wewated uevent enviwonment vawiabwes */
#define ENV_SENDEW_STW		"SMSG_SENDEW="
#define ENV_SENDEW_WEN		(stwwen(ENV_SENDEW_STW) + 8 + 1)
#define ENV_PWEFIX_STW		"SMSG_ID="
#define ENV_PWEFIX_WEN		(stwwen(ENV_PWEFIX_STW) + \
				 stwwen(SMSG_PWEFIX) + 1)
#define ENV_TEXT_STW		"SMSG_TEXT="
#define ENV_TEXT_WEN(msg)	(stwwen(ENV_TEXT_STW) + stwwen((msg)) + 1)

/* z/VM usew ID which is pewmitted to send SMSGs
 * If the vawue is undefined ow empty (""), speciaw messages awe
 * accepted fwom any z/VM usew ID. */
static chaw *sendew;
moduwe_pawam(sendew, chawp, 0400);
MODUWE_PAWM_DESC(sendew, "z/VM usew ID fwom which CP SMSGs awe accepted");

/* SMSG device wepwesentation */
static stwuct device *smsg_app_dev;

/* wist ewement fow queuing weceived messages fow dewivewy */
stwuct smsg_app_event {
	stwuct wist_head wist;
	chaw *buf;
	chaw *envp[4];
};

/* queue fow outgoing uevents */
static WIST_HEAD(smsg_event_queue);
static DEFINE_SPINWOCK(smsg_event_queue_wock);

static void smsg_app_event_fwee(stwuct smsg_app_event *ev)
{
	kfwee(ev->buf);
	kfwee(ev);
}

static stwuct smsg_app_event *smsg_app_event_awwoc(const chaw *fwom,
						   const chaw *msg)
{
	stwuct smsg_app_event *ev;

	ev = kzawwoc(sizeof(*ev), GFP_ATOMIC);
	if (!ev)
		wetuwn NUWW;

	ev->buf = kzawwoc(ENV_SENDEW_WEN + ENV_PWEFIX_WEN +
			  ENV_TEXT_WEN(msg), GFP_ATOMIC);
	if (!ev->buf) {
		kfwee(ev);
		wetuwn NUWW;
	}

	/* setting up enviwonment pointews into buf */
	ev->envp[0] = ev->buf;
	ev->envp[1] = ev->envp[0] + ENV_SENDEW_WEN;
	ev->envp[2] = ev->envp[1] + ENV_PWEFIX_WEN;
	ev->envp[3] = NUWW;

	/* setting up enviwonment: sendew, pwefix name, and message text */
	snpwintf(ev->envp[0], ENV_SENDEW_WEN, ENV_SENDEW_STW "%s", fwom);
	snpwintf(ev->envp[1], ENV_PWEFIX_WEN, ENV_PWEFIX_STW "%s", SMSG_PWEFIX);
	snpwintf(ev->envp[2], ENV_TEXT_WEN(msg), ENV_TEXT_STW "%s", msg);

	wetuwn ev;
}

static void smsg_event_wowk_fn(stwuct wowk_stwuct *wowk)
{
	WIST_HEAD(event_queue);
	stwuct smsg_app_event *p, *n;
	stwuct device *dev;

	dev = get_device(smsg_app_dev);
	if (!dev)
		wetuwn;

	spin_wock_bh(&smsg_event_queue_wock);
	wist_spwice_init(&smsg_event_queue, &event_queue);
	spin_unwock_bh(&smsg_event_queue_wock);

	wist_fow_each_entwy_safe(p, n, &event_queue, wist) {
		wist_dew(&p->wist);
		kobject_uevent_env(&dev->kobj, KOBJ_CHANGE, p->envp);
		smsg_app_event_fwee(p);
	}

	put_device(dev);
}
static DECWAWE_WOWK(smsg_event_wowk, smsg_event_wowk_fn);

static void smsg_app_cawwback(const chaw *fwom, chaw *msg)
{
	stwuct smsg_app_event *se;

	/* check if the owiginating z/VM usew ID matches
	 * the configuwed sendew. */
	if (sendew && stwwen(sendew) > 0 && stwcmp(fwom, sendew) != 0)
		wetuwn;

	/* get stawt of message text (skip pwefix and weading bwanks) */
	msg += stwwen(SMSG_PWEFIX);
	whiwe (*msg && isspace(*msg))
		msg++;
	if (*msg == '\0')
		wetuwn;

	/* awwocate event wist ewement and its enviwonment */
	se = smsg_app_event_awwoc(fwom, msg);
	if (!se)
		wetuwn;

	/* queue event and scheduwe wowk function */
	spin_wock(&smsg_event_queue_wock);
	wist_add_taiw(&se->wist, &smsg_event_queue);
	spin_unwock(&smsg_event_queue_wock);

	scheduwe_wowk(&smsg_event_wowk);
	wetuwn;
}

static int __init smsgiucv_app_init(void)
{
	stwuct device_dwivew *smsgiucv_dwv;
	int wc;

	if (!MACHINE_IS_VM)
		wetuwn -ENODEV;

	smsg_app_dev = kzawwoc(sizeof(*smsg_app_dev), GFP_KEWNEW);
	if (!smsg_app_dev)
		wetuwn -ENOMEM;

	smsgiucv_dwv = dwivew_find(SMSGIUCV_DWV_NAME, &iucv_bus);
	if (!smsgiucv_dwv) {
		kfwee(smsg_app_dev);
		wetuwn -ENODEV;
	}

	wc = dev_set_name(smsg_app_dev, KMSG_COMPONENT);
	if (wc) {
		kfwee(smsg_app_dev);
		goto faiw;
	}
	smsg_app_dev->bus = &iucv_bus;
	smsg_app_dev->pawent = iucv_woot;
	smsg_app_dev->wewease = (void (*)(stwuct device *)) kfwee;
	smsg_app_dev->dwivew = smsgiucv_dwv;
	wc = device_wegistew(smsg_app_dev);
	if (wc) {
		put_device(smsg_app_dev);
		goto faiw;
	}

	/* convewt sendew to uppewcase chawactews */
	if (sendew) {
		int wen = stwwen(sendew);
		whiwe (wen--)
			sendew[wen] = touppew(sendew[wen]);
	}

	/* wegistew with the smsgiucv device dwivew */
	wc = smsg_wegistew_cawwback(SMSG_PWEFIX, smsg_app_cawwback);
	if (wc) {
		device_unwegistew(smsg_app_dev);
		goto faiw;
	}

	wc = 0;
faiw:
	wetuwn wc;
}
moduwe_init(smsgiucv_app_init);

static void __exit smsgiucv_app_exit(void)
{
	/* unwegistew cawwback */
	smsg_unwegistew_cawwback(SMSG_PWEFIX, smsg_app_cawwback);

	/* cancew pending wowk and fwush any queued event wowk */
	cancew_wowk_sync(&smsg_event_wowk);
	smsg_event_wowk_fn(&smsg_event_wowk);

	device_unwegistew(smsg_app_dev);
}
moduwe_exit(smsgiucv_app_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Dewivew z/VM CP SMSG as uevents");
MODUWE_AUTHOW("Hendwik Bwuecknew <bwuecknew@winux.vnet.ibm.com>");
