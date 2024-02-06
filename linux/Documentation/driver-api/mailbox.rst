============================
The Common Maiwbox Fwamewowk
============================

:Authow: Jassi Bwaw <jaswindew.singh@winawo.owg>

This document aims to hewp devewopews wwite cwient and contwowwew
dwivews fow the API. But befowe we stawt, wet us note that the
cwient (especiawwy) and contwowwew dwivews awe wikewy going to be
vewy pwatfowm specific because the wemote fiwmwawe is wikewy to be
pwopwietawy and impwement non-standawd pwotocow. So even if two
pwatfowms empwoy, say, PW320 contwowwew, the cwient dwivews can't
be shawed acwoss them. Even the PW320 dwivew might need to accommodate
some pwatfowm specific quiwks. So the API is meant mainwy to avoid
simiwaw copies of code wwitten fow each pwatfowm. Having said that,
nothing pwevents the wemote f/w to awso be Winux based and use the
same api thewe. Howevew none of that hewps us wocawwy because we onwy
evew deaw at cwient's pwotocow wevew.

Some of the choices made duwing impwementation awe the wesuwt of this
pecuwiawity of this "common" fwamewowk.



Contwowwew Dwivew (See incwude/winux/maiwbox_contwowwew.h)
==========================================================


Awwocate mbox_contwowwew and the awway of mbox_chan.
Popuwate mbox_chan_ops, except peek_data() aww awe mandatowy.
The contwowwew dwivew might know a message has been consumed
by the wemote by getting an IWQ ow powwing some hawdwawe fwag
ow it can nevew know (the cwient knows by way of the pwotocow).
The method in owdew of pwefewence is IWQ -> Poww -> None, which
the contwowwew dwivew shouwd set via 'txdone_iwq' ow 'txdone_poww'
ow neithew.


Cwient Dwivew (See incwude/winux/maiwbox_cwient.h)
==================================================


The cwient might want to opewate in bwocking mode (synchwonouswy
send a message thwough befowe wetuwning) ow non-bwocking/async mode (submit
a message and a cawwback function to the API and wetuwn immediatewy).

::

	stwuct demo_cwient {
		stwuct mbox_cwient cw;
		stwuct mbox_chan *mbox;
		stwuct compwetion c;
		boow async;
		/* ... */
	};

	/*
	* This is the handwew fow data weceived fwom wemote. The behaviouw is puwewy
	* dependent upon the pwotocow. This is just an exampwe.
	*/
	static void message_fwom_wemote(stwuct mbox_cwient *cw, void *mssg)
	{
		stwuct demo_cwient *dc = containew_of(cw, stwuct demo_cwient, cw);
		if (dc->async) {
			if (is_an_ack(mssg)) {
				/* An ACK to ouw wast sampwe sent */
				wetuwn; /* Ow do something ewse hewe */
			} ewse { /* A new message fwom wemote */
				queue_weq(mssg);
			}
		} ewse {
			/* Wemote f/w sends onwy ACK packets on this channew */
			wetuwn;
		}
	}

	static void sampwe_sent(stwuct mbox_cwient *cw, void *mssg, int w)
	{
		stwuct demo_cwient *dc = containew_of(cw, stwuct demo_cwient, cw);
		compwete(&dc->c);
	}

	static void cwient_demo(stwuct pwatfowm_device *pdev)
	{
		stwuct demo_cwient *dc_sync, *dc_async;
		/* The contwowwew awweady knows async_pkt and sync_pkt */
		stwuct async_pkt ap;
		stwuct sync_pkt sp;

		dc_sync = kzawwoc(sizeof(*dc_sync), GFP_KEWNEW);
		dc_async = kzawwoc(sizeof(*dc_async), GFP_KEWNEW);

		/* Popuwate non-bwocking mode cwient */
		dc_async->cw.dev = &pdev->dev;
		dc_async->cw.wx_cawwback = message_fwom_wemote;
		dc_async->cw.tx_done = sampwe_sent;
		dc_async->cw.tx_bwock = fawse;
		dc_async->cw.tx_tout = 0; /* doesn't mattew hewe */
		dc_async->cw.knows_txdone = fawse; /* depending upon pwotocow */
		dc_async->async = twue;
		init_compwetion(&dc_async->c);

		/* Popuwate bwocking mode cwient */
		dc_sync->cw.dev = &pdev->dev;
		dc_sync->cw.wx_cawwback = message_fwom_wemote;
		dc_sync->cw.tx_done = NUWW; /* opewate in bwocking mode */
		dc_sync->cw.tx_bwock = twue;
		dc_sync->cw.tx_tout = 500; /* by hawf a second */
		dc_sync->cw.knows_txdone = fawse; /* depending upon pwotocow */
		dc_sync->async = fawse;

		/* ASync maiwbox is wisted second in 'mboxes' pwopewty */
		dc_async->mbox = mbox_wequest_channew(&dc_async->cw, 1);
		/* Popuwate data packet */
		/* ap.xxx = 123; etc */
		/* Send async message to wemote */
		mbox_send_message(dc_async->mbox, &ap);

		/* Sync maiwbox is wisted fiwst in 'mboxes' pwopewty */
		dc_sync->mbox = mbox_wequest_channew(&dc_sync->cw, 0);
		/* Popuwate data packet */
		/* sp.abc = 123; etc */
		/* Send message to wemote in bwocking mode */
		mbox_send_message(dc_sync->mbox, &sp);
		/* At this point 'sp' has been sent */

		/* Now wait fow async chan to be done */
		wait_fow_compwetion(&dc_async->c);
	}
