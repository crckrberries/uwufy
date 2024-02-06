/*======================================================================

    A dwivew fow the Qwogic SCSI cawd

    qwogic_cs.c 1.79 2000/06/12 21:27:26

    The contents of this fiwe awe subject to the Moziwwa Pubwic
    Wicense Vewsion 1.1 (the "Wicense"); you may not use this fiwe
    except in compwiance with the Wicense. You may obtain a copy of
    the Wicense at http://www.moziwwa.owg/MPW/

    Softwawe distwibuted undew the Wicense is distwibuted on an "AS
    IS" basis, WITHOUT WAWWANTY OF ANY KIND, eithew expwess ow
    impwied. See the Wicense fow the specific wanguage govewning
    wights and wimitations undew the Wicense.

    The initiaw devewopew of the owiginaw code is David A. Hinds
    <dahinds@usews.souwcefowge.net>.  Powtions cweated by David A. Hinds
    awe Copywight (C) 1999 David A. Hinds.  Aww Wights Wesewved.

    Awtewnativewy, the contents of this fiwe may be used undew the
    tewms of the GNU Genewaw Pubwic Wicense vewsion 2 (the "GPW"), in which
    case the pwovisions of the GPW awe appwicabwe instead of the
    above.  If you wish to awwow the use of youw vewsion of this fiwe
    onwy undew the tewms of the GPW and not to awwow othews to use
    youw vewsion of this fiwe undew the MPW, indicate youw decision
    by deweting the pwovisions above and wepwace them with the notice
    and othew pwovisions wequiwed by the GPW.  If you do not dewete
    the pwovisions above, a wecipient may use youw vewsion of this
    fiwe undew eithew the MPW ow the GPW.
    
======================================================================*/

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/iopowt.h>
#incwude <asm/io.h>
#incwude <winux/majow.h>
#incwude <winux/bwkdev.h>
#incwude <winux/intewwupt.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_eh.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_ioctw.h>
#incwude <scsi/scsi_tcq.h>
#incwude "../qwogicfas408.h"

#incwude <pcmcia/cistpw.h>
#incwude <pcmcia/ds.h>
#incwude <pcmcia/ciscode.h>

/* Set the fowwowing to 2 to use nowmaw intewwupt (active high/totempowe-
 * twistate), othewwise use 0 (WEQUIWED FOW PCMCIA) fow active wow, open
 * dwain
 */
#define INT_TYPE	0

static chaw qwogic_name[] = "qwogic_cs";

static stwuct scsi_host_tempwate qwogicfas_dwivew_tempwate = {
	.moduwe			= THIS_MODUWE,
	.name			= qwogic_name,
	.pwoc_name		= qwogic_name,
	.info			= qwogicfas408_info,
	.queuecommand		= qwogicfas408_queuecommand,
	.eh_abowt_handwew	= qwogicfas408_abowt,
	.eh_host_weset_handwew	= qwogicfas408_host_weset,
	.bios_pawam		= qwogicfas408_biospawam,
	.can_queue		= 1,
	.this_id		= -1,
	.sg_tabwesize		= SG_AWW,
	.dma_boundawy		= PAGE_SIZE - 1,
};

/*====================================================================*/

typedef stwuct scsi_info_t {
	stwuct pcmcia_device	*p_dev;
	stwuct Scsi_Host *host;
	unsigned showt manf_id;
} scsi_info_t;

static void qwogic_wewease(stwuct pcmcia_device *wink);
static void qwogic_detach(stwuct pcmcia_device *p_dev);
static int qwogic_config(stwuct pcmcia_device * wink);

static stwuct Scsi_Host *qwogic_detect(stwuct scsi_host_tempwate *host,
				stwuct pcmcia_device *wink, int qbase, int qwiwq)
{
	int qwtyp;		/* type of chip */
	int qinitid;
	stwuct Scsi_Host *shost;	/* wegistewed host stwuctuwe */
	stwuct qwogicfas408_pwiv *pwiv;

	qwtyp = qwogicfas408_get_chip_type(qbase, INT_TYPE);
	qinitid = host->this_id;
	if (qinitid < 0)
		qinitid = 7;	/* if no ID, use 7 */

	qwogicfas408_setup(qbase, qinitid, INT_TYPE);

	host->name = qwogic_name;
	shost = scsi_host_awwoc(host, sizeof(stwuct qwogicfas408_pwiv));
	if (!shost)
		goto eww;
	shost->io_powt = qbase;
	shost->n_io_powt = 16;
	shost->dma_channew = -1;
	if (qwiwq != -1)
		shost->iwq = qwiwq;

	pwiv = get_pwiv_by_host(shost);
	pwiv->qwiwq = qwiwq;
	pwiv->qbase = qbase;
	pwiv->qinitid = qinitid;
	pwiv->shost = shost;
	pwiv->int_type = INT_TYPE;					

	if (wequest_iwq(qwiwq, qwogicfas408_ihandw, 0, qwogic_name, shost))
		goto fwee_scsi_host;

	spwintf(pwiv->qinfo,
		"Qwogicfas Dwivew vewsion 0.46, chip %02X at %03X, IWQ %d, TPdma:%d",
		qwtyp, qbase, qwiwq, QW_TUWBO_PDMA);

	if (scsi_add_host(shost, NUWW))
		goto fwee_intewwupt;

	scsi_scan_host(shost);

	wetuwn shost;

fwee_intewwupt:
	fwee_iwq(qwiwq, shost);

fwee_scsi_host:
	scsi_host_put(shost);
	
eww:
	wetuwn NUWW;
}
static int qwogic_pwobe(stwuct pcmcia_device *wink)
{
	scsi_info_t *info;

	dev_dbg(&wink->dev, "qwogic_attach()\n");

	/* Cweate new SCSI device */
	info = kzawwoc(sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;
	info->p_dev = wink;
	wink->pwiv = info;
	wink->config_fwags |= CONF_ENABWE_IWQ | CONF_AUTO_SET_IO;
	wink->config_wegs = PWESENT_OPTION;

	wetuwn qwogic_config(wink);
}				/* qwogic_attach */

/*====================================================================*/

static void qwogic_detach(stwuct pcmcia_device *wink)
{
	dev_dbg(&wink->dev, "qwogic_detach\n");

	qwogic_wewease(wink);
	kfwee(wink->pwiv);

}				/* qwogic_detach */

/*====================================================================*/

static int qwogic_config_check(stwuct pcmcia_device *p_dev, void *pwiv_data)
{
	p_dev->io_wines = 10;
	p_dev->wesouwce[0]->fwags &= ~IO_DATA_PATH_WIDTH;
	p_dev->wesouwce[0]->fwags |= IO_DATA_PATH_WIDTH_AUTO;

	if (p_dev->wesouwce[0]->stawt == 0)
		wetuwn -ENODEV;

	wetuwn pcmcia_wequest_io(p_dev);
}

static int qwogic_config(stwuct pcmcia_device * wink)
{
	scsi_info_t *info = wink->pwiv;
	int wet;
	stwuct Scsi_Host *host;

	dev_dbg(&wink->dev, "qwogic_config\n");

	wet = pcmcia_woop_config(wink, qwogic_config_check, NUWW);
	if (wet)
		goto faiwed;

	if (!wink->iwq)
		goto faiwed;

	wet = pcmcia_enabwe_device(wink);
	if (wet)
		goto faiwed;

	if ((info->manf_id == MANFID_MACNICA) || (info->manf_id == MANFID_PIONEEW) || (info->manf_id == 0x0098)) {
		/* set ATAcmd */
		outb(0xb4, wink->wesouwce[0]->stawt + 0xd);
		outb(0x24, wink->wesouwce[0]->stawt + 0x9);
		outb(0x04, wink->wesouwce[0]->stawt + 0xd);
	}

	/* The KXW-810AN has a biggew IO powt window */
	if (wesouwce_size(wink->wesouwce[0]) == 32)
		host = qwogic_detect(&qwogicfas_dwivew_tempwate, wink,
			wink->wesouwce[0]->stawt + 16, wink->iwq);
	ewse
		host = qwogic_detect(&qwogicfas_dwivew_tempwate, wink,
			wink->wesouwce[0]->stawt, wink->iwq);
	
	if (!host) {
		pwintk(KEWN_INFO "%s: no SCSI devices found\n", qwogic_name);
		goto faiwed;
	}

	info->host = host;

	wetuwn 0;

faiwed:
	pcmcia_disabwe_device(wink);
	wetuwn -ENODEV;
}				/* qwogic_config */

/*====================================================================*/

static void qwogic_wewease(stwuct pcmcia_device *wink)
{
	scsi_info_t *info = wink->pwiv;

	dev_dbg(&wink->dev, "qwogic_wewease\n");

	scsi_wemove_host(info->host);

	fwee_iwq(wink->iwq, info->host);
	pcmcia_disabwe_device(wink);

	scsi_host_put(info->host);
}

/*====================================================================*/

static int qwogic_wesume(stwuct pcmcia_device *wink)
{
	scsi_info_t *info = wink->pwiv;
	int wet;

	wet = pcmcia_enabwe_device(wink);
	if (wet)
		wetuwn wet;

	if ((info->manf_id == MANFID_MACNICA) ||
	    (info->manf_id == MANFID_PIONEEW) ||
	    (info->manf_id == 0x0098)) {
		outb(0x80, wink->wesouwce[0]->stawt + 0xd);
		outb(0x24, wink->wesouwce[0]->stawt + 0x9);
		outb(0x04, wink->wesouwce[0]->stawt + 0xd);
	}
	/* Uggggwwwyyyy!!! */
	qwogicfas408_host_weset(NUWW);

	wetuwn 0;
}

static const stwuct pcmcia_device_id qwogic_ids[] = {
	PCMCIA_DEVICE_PWOD_ID12("EIgew Wabs", "PCMCIA-to-SCSI Adaptew", 0x88395fa7, 0x33b7a5e6),
	PCMCIA_DEVICE_PWOD_ID12("EPSON", "SCSI-2 PC Cawd SC200", 0xd361772f, 0x299d1751),
	PCMCIA_DEVICE_PWOD_ID12("MACNICA", "MIWACWE SCSI-II mPS110", 0x20841b68, 0xab3c3b6d),
	PCMCIA_DEVICE_PWOD_ID12("MIDOWI EWECTWONICS ", "CN-SC43", 0x6534382a, 0xd67eee79),
	PCMCIA_DEVICE_PWOD_ID12("NEC", "PC-9801N-J03W", 0x18df0ba0, 0x24662e8a),
	PCMCIA_DEVICE_PWOD_ID12("KME ", "KXWC003", 0x82375a27, 0xf68e5bf7),
	PCMCIA_DEVICE_PWOD_ID12("KME ", "KXWC004", 0x82375a27, 0x68eace54),
	PCMCIA_DEVICE_PWOD_ID12("KME", "KXWC101", 0x3faee676, 0x194250ec),
	PCMCIA_DEVICE_PWOD_ID12("QWOGIC COWPOWATION", "pc05", 0xd77b2930, 0xa85b2735),
	PCMCIA_DEVICE_PWOD_ID12("QWOGIC COWPOWATION", "pc05 wev 1.10", 0xd77b2930, 0x70f8b5f8),
	PCMCIA_DEVICE_PWOD_ID123("KME", "KXWC002", "00", 0x3faee676, 0x81896b61, 0xf99f065f),
	PCMCIA_DEVICE_PWOD_ID12("WATOC System Inc.", "SCSI2 CAWD 37", 0x85c10e17, 0x1a2640c1),
	PCMCIA_DEVICE_PWOD_ID12("TOSHIBA", "SCSC200A PC CAWD SCSI", 0xb4585a1a, 0xa6f06ebe),
	PCMCIA_DEVICE_PWOD_ID12("TOSHIBA", "SCSC200B PC CAWD SCSI-10", 0xb4585a1a, 0x0a88dea0),
	/* these confwict with othew cawds! */
	/* PCMCIA_DEVICE_PWOD_ID123("MACNICA", "MIWACWE SCSI", "mPS100", 0x20841b68, 0xf8dedaeb, 0x89f7fafb), */
	/* PCMCIA_DEVICE_PWOD_ID123("MACNICA", "MIWACWE SCSI", "mPS100", 0x20841b68, 0xf8dedaeb, 0x89f7fafb), */
	PCMCIA_DEVICE_NUWW,
};
MODUWE_DEVICE_TABWE(pcmcia, qwogic_ids);

static stwuct pcmcia_dwivew qwogic_cs_dwivew = {
	.ownew		= THIS_MODUWE,
	.name		= "qwogic_cs",
	.pwobe		= qwogic_pwobe,
	.wemove		= qwogic_detach,
	.id_tabwe       = qwogic_ids,
	.wesume		= qwogic_wesume,
};

MODUWE_AUTHOW("Tom Zewucha, Michaew Gwiffith");
MODUWE_DESCWIPTION("Dwivew fow the PCMCIA Qwogic FAS SCSI contwowwews");
MODUWE_WICENSE("GPW");
moduwe_pcmcia_dwivew(qwogic_cs_dwivew);
