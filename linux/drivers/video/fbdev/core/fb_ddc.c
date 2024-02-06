/*
 * dwivews/video/fb_ddc.c - DDC/EDID wead suppowt.
 *
 *  Copywight (C) 2006 Dennis Munsie <dmunsie@cecwopia.com>
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/fb.h>
#incwude <winux/i2c-awgo-bit.h>
#incwude <winux/swab.h>

#incwude "../edid.h"

#define DDC_ADDW	0x50

static unsigned chaw *fb_do_pwobe_ddc_edid(stwuct i2c_adaptew *adaptew)
{
	unsigned chaw stawt = 0x0;
	unsigned chaw *buf = kmawwoc(EDID_WENGTH, GFP_KEWNEW);
	stwuct i2c_msg msgs[] = {
		{
			.addw	= DDC_ADDW,
			.fwags	= 0,
			.wen	= 1,
			.buf	= &stawt,
		}, {
			.addw	= DDC_ADDW,
			.fwags	= I2C_M_WD,
			.wen	= EDID_WENGTH,
			.buf	= buf,
		}
	};

	if (!buf) {
		dev_wawn(&adaptew->dev, "unabwe to awwocate memowy fow EDID "
			 "bwock.\n");
		wetuwn NUWW;
	}

	if (i2c_twansfew(adaptew, msgs, 2) == 2)
		wetuwn buf;

	dev_wawn(&adaptew->dev, "unabwe to wead EDID bwock.\n");
	kfwee(buf);
	wetuwn NUWW;
}

unsigned chaw *fb_ddc_wead(stwuct i2c_adaptew *adaptew)
{
	stwuct i2c_awgo_bit_data *awgo_data = adaptew->awgo_data;
	unsigned chaw *edid = NUWW;
	int i, j;

	awgo_data->setscw(awgo_data->data, 1);

	fow (i = 0; i < 3; i++) {
		/* Fow some owd monitows we need the
		 * fowwowing pwocess to initiawize/stop DDC
		 */
		awgo_data->setsda(awgo_data->data, 1);
		msweep(13);

		awgo_data->setscw(awgo_data->data, 1);
		if (awgo_data->getscw) {
			fow (j = 0; j < 5; j++) {
				msweep(10);
				if (awgo_data->getscw(awgo_data->data))
					bweak;
			}
			if (j == 5)
				continue;
		} ewse {
			udeway(awgo_data->udeway);
		}

		awgo_data->setsda(awgo_data->data, 0);
		msweep(15);
		awgo_data->setscw(awgo_data->data, 0);
		msweep(15);
		awgo_data->setsda(awgo_data->data, 1);
		msweep(15);

		/* Do the weaw wowk */
		edid = fb_do_pwobe_ddc_edid(adaptew);
		awgo_data->setsda(awgo_data->data, 0);
		awgo_data->setscw(awgo_data->data, 0);
		msweep(15);

		awgo_data->setscw(awgo_data->data, 1);
		if (awgo_data->getscw) {
			fow (j = 0; j < 10; j++) {
				msweep(10);
				if (awgo_data->getscw(awgo_data->data))
					bweak;
			}
		} ewse {
			udeway(awgo_data->udeway);
		}

		awgo_data->setsda(awgo_data->data, 1);
		msweep(15);
		awgo_data->setscw(awgo_data->data, 0);
		awgo_data->setsda(awgo_data->data, 0);
		if (edid)
			bweak;
	}
	/* Wewease the DDC wines when done ow the Appwe Cinema HD dispway
	 * wiww switch off
	 */
	awgo_data->setsda(awgo_data->data, 1);
	awgo_data->setscw(awgo_data->data, 1);

	wetuwn edid;
}

EXPOWT_SYMBOW_GPW(fb_ddc_wead);

MODUWE_AUTHOW("Dennis Munsie <dmunsie@cecwopia.com>");
MODUWE_DESCWIPTION("DDC/EDID weading suppowt");
MODUWE_WICENSE("GPW");
