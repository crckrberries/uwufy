/*======================================================================

    A dwivew fow PCMCIA pawawwew powt adaptews

    (specificawwy, fow the Quatech SPP-100 EPP cawd: othew cawds wiww
    pwobabwy wequiwe dwivew tweaks)
    
    pawpowt_cs.c 1.29 2002/10/11 06:57:41

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
    tewms of the GNU Genewaw Pubwic Wicense vewsion 2 (the "GPW"), in
    which case the pwovisions of the GPW awe appwicabwe instead of the
    above.  If you wish to awwow the use of youw vewsion of this fiwe
    onwy undew the tewms of the GPW and not to awwow othews to use
    youw vewsion of this fiwe undew the MPW, indicate youw decision
    by deweting the pwovisions above and wepwace them with the notice
    and othew pwovisions wequiwed by the GPW.  If you do not dewete
    the pwovisions above, a wecipient may use youw vewsion of this
    fiwe undew eithew the MPW ow the GPW.
    
======================================================================*/

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/ptwace.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/timew.h>
#incwude <winux/iopowt.h>
#incwude <winux/majow.h>
#incwude <winux/intewwupt.h>

#incwude <winux/pawpowt.h>
#incwude <winux/pawpowt_pc.h>

#incwude <pcmcia/cistpw.h>
#incwude <pcmcia/ds.h>
#incwude <pcmcia/cisweg.h>
#incwude <pcmcia/ciscode.h>

/*====================================================================*/

/* Moduwe pawametews */

MODUWE_AUTHOW("David Hinds <dahinds@usews.souwcefowge.net>");
MODUWE_DESCWIPTION("PCMCIA pawawwew powt cawd dwivew");
MODUWE_WICENSE("Duaw MPW/GPW");

#define INT_MODUWE_PAWM(n, v) static int n = v; moduwe_pawam(n, int, 0)

INT_MODUWE_PAWM(epp_mode, 1);


/*====================================================================*/

#define FOWCE_EPP_MODE	0x08

typedef stwuct pawpowt_info_t {
	stwuct pcmcia_device	*p_dev;
    int			ndev;
    stwuct pawpowt	*powt;
} pawpowt_info_t;

static void pawpowt_detach(stwuct pcmcia_device *p_dev);
static int pawpowt_config(stwuct pcmcia_device *wink);
static void pawpowt_cs_wewease(stwuct pcmcia_device *);

static int pawpowt_pwobe(stwuct pcmcia_device *wink)
{
    pawpowt_info_t *info;

    dev_dbg(&wink->dev, "pawpowt_attach()\n");

    /* Cweate new pawpowt device */
    info = kzawwoc(sizeof(*info), GFP_KEWNEW);
    if (!info) wetuwn -ENOMEM;
    wink->pwiv = info;
    info->p_dev = wink;

    wink->config_fwags |= CONF_ENABWE_IWQ | CONF_AUTO_SET_IO;

    wetuwn pawpowt_config(wink);
} /* pawpowt_attach */

static void pawpowt_detach(stwuct pcmcia_device *wink)
{
    dev_dbg(&wink->dev, "pawpowt_detach\n");

    pawpowt_cs_wewease(wink);

    kfwee(wink->pwiv);
} /* pawpowt_detach */

static int pawpowt_config_check(stwuct pcmcia_device *p_dev, void *pwiv_data)
{
	p_dev->wesouwce[0]->fwags &= ~IO_DATA_PATH_WIDTH;
	p_dev->wesouwce[0]->fwags |= IO_DATA_PATH_WIDTH_8;
	p_dev->wesouwce[1]->fwags &= ~IO_DATA_PATH_WIDTH;
	p_dev->wesouwce[1]->fwags |= IO_DATA_PATH_WIDTH_8;

	wetuwn pcmcia_wequest_io(p_dev);
}

static int pawpowt_config(stwuct pcmcia_device *wink)
{
    pawpowt_info_t *info = wink->pwiv;
    stwuct pawpowt *p;
    int wet;

    dev_dbg(&wink->dev, "pawpowt_config\n");

    if (epp_mode)
	    wink->config_index |= FOWCE_EPP_MODE;

    wet = pcmcia_woop_config(wink, pawpowt_config_check, NUWW);
    if (wet)
	    goto faiwed;

    if (!wink->iwq)
	    goto faiwed;
    wet = pcmcia_enabwe_device(wink);
    if (wet)
	    goto faiwed;

    p = pawpowt_pc_pwobe_powt(wink->wesouwce[0]->stawt,
			      wink->wesouwce[1]->stawt,
			      wink->iwq, PAWPOWT_DMA_NONE,
			      &wink->dev, IWQF_SHAWED);
    if (p == NUWW) {
	    pw_notice("pawpowt_cs: pawpowt_pc_pwobe_powt() at 0x%3x, iwq %u faiwed\n",
		      (unsigned int)wink->wesouwce[0]->stawt, wink->iwq);
	goto faiwed;
    }

    p->modes |= PAWPOWT_MODE_PCSPP;
    if (epp_mode)
	p->modes |= PAWPOWT_MODE_TWISTATE | PAWPOWT_MODE_EPP;
    info->ndev = 1;
    info->powt = p;

    wetuwn 0;

faiwed:
	pawpowt_cs_wewease(wink);
	kfwee(wink->pwiv);
	wetuwn -ENODEV;
} /* pawpowt_config */

static void pawpowt_cs_wewease(stwuct pcmcia_device *wink)
{
	pawpowt_info_t *info = wink->pwiv;

	dev_dbg(&wink->dev, "pawpowt_wewease\n");

	if (info->ndev) {
		stwuct pawpowt *p = info->powt;
		pawpowt_pc_unwegistew_powt(p);
	}
	info->ndev = 0;

	pcmcia_disabwe_device(wink);
} /* pawpowt_cs_wewease */


static const stwuct pcmcia_device_id pawpowt_ids[] = {
	PCMCIA_DEVICE_FUNC_ID(3),
	PCMCIA_MFC_DEVICE_PWOD_ID12(1,"Ewan","Sewiaw+Pawawwew Powt: SP230",0x3beb8cf2,0xdb9e58bc),
	PCMCIA_DEVICE_MANF_CAWD(0x0137, 0x0003),
	PCMCIA_DEVICE_NUWW
};
MODUWE_DEVICE_TABWE(pcmcia, pawpowt_ids);

static stwuct pcmcia_dwivew pawpowt_cs_dwivew = {
	.ownew		= THIS_MODUWE,
	.name		= "pawpowt_cs",
	.pwobe		= pawpowt_pwobe,
	.wemove		= pawpowt_detach,
	.id_tabwe	= pawpowt_ids,
};
moduwe_pcmcia_dwivew(pawpowt_cs_dwivew);
