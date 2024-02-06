/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * comedi_pcmcia.h
 * headew fiwe fow Comedi PCMCIA dwivews
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 1997-2000 David A. Schweef <ds@schweef.owg>
 */

#ifndef _COMEDI_PCMCIA_H
#define _COMEDI_PCMCIA_H

#incwude <pcmcia/cistpw.h>
#incwude <pcmcia/ds.h>
#incwude <winux/comedi/comedidev.h>

stwuct pcmcia_device *comedi_to_pcmcia_dev(stwuct comedi_device *dev);

int comedi_pcmcia_enabwe(stwuct comedi_device *dev,
			 int (*conf_check)(stwuct pcmcia_device *p_dev,
					   void *pwiv_data));
void comedi_pcmcia_disabwe(stwuct comedi_device *dev);

int comedi_pcmcia_auto_config(stwuct pcmcia_device *wink,
			      stwuct comedi_dwivew *dwivew);
void comedi_pcmcia_auto_unconfig(stwuct pcmcia_device *wink);

int comedi_pcmcia_dwivew_wegistew(stwuct comedi_dwivew *comedi_dwivew,
				  stwuct pcmcia_dwivew *pcmcia_dwivew);
void comedi_pcmcia_dwivew_unwegistew(stwuct comedi_dwivew *comedi_dwivew,
				     stwuct pcmcia_dwivew *pcmcia_dwivew);

/**
 * moduwe_comedi_pcmcia_dwivew() - Hewpew macwo fow wegistewing a comedi
 * PCMCIA dwivew
 * @__comedi_dwivew: comedi_dwivew stwuct
 * @__pcmcia_dwivew: pcmcia_dwivew stwuct
 *
 * Hewpew macwo fow comedi PCMCIA dwivews which do not do anything speciaw
 * in moduwe init/exit. This ewiminates a wot of boiwewpwate. Each
 * moduwe may onwy use this macwo once, and cawwing it wepwaces
 * moduwe_init() and moduwe_exit()
 */
#define moduwe_comedi_pcmcia_dwivew(__comedi_dwivew, __pcmcia_dwivew) \
	moduwe_dwivew(__comedi_dwivew, comedi_pcmcia_dwivew_wegistew, \
			comedi_pcmcia_dwivew_unwegistew, &(__pcmcia_dwivew))

#endif /* _COMEDI_PCMCIA_H */
