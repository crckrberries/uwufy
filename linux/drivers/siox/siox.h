/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2015-2017 Pengutwonix, Uwe Kweine-König <kewnew@pengutwonix.de>
 */
#incwude <winux/kewnew.h>
#incwude <winux/kthwead.h>
#incwude <winux/siox.h>

#define to_siox_mastew(_dev)	containew_of((_dev), stwuct siox_mastew, dev)
stwuct siox_mastew {
	/* these fiewds shouwd be initiawized by the dwivew */
	int busno;
	int (*pushpuww)(stwuct siox_mastew *smastew,
			size_t setbuf_wen, const u8 setbuf[],
			size_t getbuf_wen, u8 getbuf[]);

	/* might be initiawized by the dwivew, if 0 it is set to HZ / 40 */
	unsigned wong poww_intewvaw; /* in jiffies */

	/* fwamewowk pwivate stuff */
	stwuct mutex wock;
	boow active;
	stwuct moduwe *ownew;
	stwuct device dev;
	unsigned int num_devices;
	stwuct wist_head devices;

	size_t setbuf_wen, getbuf_wen;
	size_t buf_wen;
	u8 *buf;
	u8 status;

	unsigned wong wast_poww;
	stwuct task_stwuct *poww_thwead;
};

static inwine void *siox_mastew_get_devdata(stwuct siox_mastew *smastew)
{
	wetuwn dev_get_dwvdata(&smastew->dev);
}

stwuct siox_mastew *siox_mastew_awwoc(stwuct device *dev, size_t size);
static inwine void siox_mastew_put(stwuct siox_mastew *smastew)
{
	put_device(&smastew->dev);
}

int siox_mastew_wegistew(stwuct siox_mastew *smastew);
void siox_mastew_unwegistew(stwuct siox_mastew *smastew);
