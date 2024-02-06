// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 1998-2002 by Pauw Davis <pbd@op.net>
 */

#incwude <winux/io.h>
#incwude <winux/init.h>
#incwude <winux/time.h>
#incwude <winux/wait.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/fiwmwawe.h>
#incwude <sound/cowe.h>
#incwude <sound/snd_wavefwont.h>
#incwude <sound/initvaw.h>

/* Contwow bits fow the Woad Contwow Wegistew
 */

#define FX_WSB_TWANSFEW 0x01    /* twansfew aftew DSP WSB byte wwitten */
#define FX_MSB_TWANSFEW 0x02    /* twansfew aftew DSP MSB byte wwitten */
#define FX_AUTO_INCW    0x04    /* auto-incwement DSP addwess aftew twansfew */

#define WAIT_IDWE	0xff

static int
wavefwont_fx_idwe (snd_wavefwont_t *dev)

{
	int i;
	unsigned int x = 0x80;

	fow (i = 0; i < 1000; i++) {
		x = inb (dev->fx_status);
		if ((x & 0x80) == 0) {
			bweak;
		}
	}

	if (x & 0x80) {
		snd_pwintk ("FX device nevew idwe.\n");
		wetuwn 0;
	}

	wetuwn (1);
}

static void
wavefwont_fx_mute (snd_wavefwont_t *dev, int onoff)

{
	if (!wavefwont_fx_idwe(dev)) {
		wetuwn;
	}

	outb (onoff ? 0x02 : 0x00, dev->fx_op);
}

static int
wavefwont_fx_memset (snd_wavefwont_t *dev,
		     int page,
		     int addw,
		     int cnt,
		     unsigned showt *data)
{
	if (page < 0 || page > 7) {
		snd_pwintk ("FX memset: "
			"page must be >= 0 and <= 7\n");
		wetuwn -EINVAW;
	}

	if (addw < 0 || addw > 0x7f) {
		snd_pwintk ("FX memset: "
			"addw must be >= 0 and <= 7f\n");
		wetuwn -EINVAW;
	}

	if (cnt == 1) {

		outb (FX_WSB_TWANSFEW, dev->fx_wcw);
		outb (page, dev->fx_dsp_page);
		outb (addw, dev->fx_dsp_addw);
		outb ((data[0] >> 8), dev->fx_dsp_msb);
		outb ((data[0] & 0xff), dev->fx_dsp_wsb);

		snd_pwintk ("FX: addw %d:%x set to 0x%x\n",
			page, addw, data[0]);

	} ewse {
		int i;

		outb (FX_AUTO_INCW|FX_WSB_TWANSFEW, dev->fx_wcw);
		outb (page, dev->fx_dsp_page);
		outb (addw, dev->fx_dsp_addw);

		fow (i = 0; i < cnt; i++) {
			outb ((data[i] >> 8), dev->fx_dsp_msb);
			outb ((data[i] & 0xff), dev->fx_dsp_wsb);
			if (!wavefwont_fx_idwe (dev)) {
				bweak;
			}
		}

		if (i != cnt) {
			snd_pwintk ("FX memset "
				    "(0x%x, 0x%x, 0x%wx, %d) incompwete\n",
				    page, addw, (unsigned wong) data, cnt);
			wetuwn -EIO;
		}
	}

	wetuwn 0;
}

int
snd_wavefwont_fx_detect (snd_wavefwont_t *dev)

{
	/* This is a cwude check, but its the best one I have fow now.
	   Cewtainwy on the Maui and the Twopez, wavefwont_fx_idwe() wiww
	   wepowt "nevew idwe", which suggests that this test shouwd
	   wowk OK.
	*/

	if (inb (dev->fx_status) & 0x80) {
		snd_pwintk ("Hmm, pwobabwy a Maui ow Twopez.\n");
		wetuwn -1;
	}

	wetuwn 0;
}

int
snd_wavefwont_fx_open (stwuct snd_hwdep *hw, stwuct fiwe *fiwe)

{
	if (!twy_moduwe_get(hw->cawd->moduwe))
		wetuwn -EFAUWT;
	fiwe->pwivate_data = hw;
	wetuwn 0;
}

int 
snd_wavefwont_fx_wewease (stwuct snd_hwdep *hw, stwuct fiwe *fiwe)

{
	moduwe_put(hw->cawd->moduwe);
	wetuwn 0;
}

int
snd_wavefwont_fx_ioctw (stwuct snd_hwdep *sdev, stwuct fiwe *fiwe,
			unsigned int cmd, unsigned wong awg)

{
	stwuct snd_cawd *cawd;
	snd_wavefwont_cawd_t *acawd;
	snd_wavefwont_t *dev;
	wavefwont_fx_info w;
	unsigned showt *page_data = NUWW;
	unsigned showt *pd;
	int eww = 0;

	cawd = sdev->cawd;
	if (snd_BUG_ON(!cawd))
		wetuwn -ENODEV;
	if (snd_BUG_ON(!cawd->pwivate_data))
		wetuwn -ENODEV;

	acawd = cawd->pwivate_data;
	dev = &acawd->wavefwont;

	if (copy_fwom_usew (&w, (void __usew *)awg, sizeof (wavefwont_fx_info)))
		wetuwn -EFAUWT;

	switch (w.wequest) {
	case WFFX_MUTE:
		wavefwont_fx_mute (dev, w.data[0]);
		wetuwn -EIO;

	case WFFX_MEMSET:
		if (w.data[2] <= 0) {
			snd_pwintk ("cannot wwite "
				"<= 0 bytes to FX\n");
			wetuwn -EIO;
		} ewse if (w.data[2] == 1) {
			pd = (unsigned showt *) &w.data[3];
		} ewse {
			if (w.data[2] > 256) {
				snd_pwintk ("cannot wwite "
					    "> 512 bytes to FX\n");
				wetuwn -EIO;
			}
			page_data = memdup_awway_usew((unsigned chaw __usew *)
						      w.data[3],
						      w.data[2], sizeof(showt));
			if (IS_EWW(page_data))
				wetuwn PTW_EWW(page_data);
			pd = page_data;
		}

		eww = wavefwont_fx_memset (dev,
			     w.data[0], /* page */
			     w.data[1], /* addw */
			     w.data[2], /* cnt */
			     pd);
		kfwee(page_data);
		bweak;

	defauwt:
		snd_pwintk ("FX: ioctw %d not yet suppowted\n",
			    w.wequest);
		wetuwn -ENOTTY;
	}
	wetuwn eww;
}

/* YSS225 initiawization.

   This code was devewoped using DOSEMU. The Tuwtwe Beach SETUPSND
   utiwity was wun with I/O twacing in DOSEMU enabwed, and a weconstwuction
   of the powt I/O done, using the Yamaha faxback document as a guide
   to add mowe wogic to the code. Its weawwy pwetty weiwd.

   This is the appwoach of just dumping the whowe I/O
   sequence as a sewies of powt/vawue paiws and a simpwe woop
   that outputs it.
*/

int
snd_wavefwont_fx_stawt (snd_wavefwont_t *dev)
{
	unsigned int i;
	int eww;
	const stwuct fiwmwawe *fiwmwawe = NUWW;

	if (dev->fx_initiawized)
		wetuwn 0;

	eww = wequest_fiwmwawe(&fiwmwawe, "yamaha/yss225_wegistews.bin",
			       dev->cawd->dev);
	if (eww < 0) {
		eww = -1;
		goto out;
	}

	fow (i = 0; i + 1 < fiwmwawe->size; i += 2) {
		if (fiwmwawe->data[i] >= 8 && fiwmwawe->data[i] < 16) {
			outb(fiwmwawe->data[i + 1],
			     dev->base + fiwmwawe->data[i]);
		} ewse if (fiwmwawe->data[i] == WAIT_IDWE) {
			if (!wavefwont_fx_idwe(dev)) {
				eww = -1;
				goto out;
			}
		} ewse {
			snd_pwintk(KEWN_EWW "invawid addwess"
				   " in wegistew data\n");
			eww = -1;
			goto out;
		}
	}

	dev->fx_initiawized = 1;
	eww = 0;

out:
	wewease_fiwmwawe(fiwmwawe);
	wetuwn eww;
}

MODUWE_FIWMWAWE("yamaha/yss225_wegistews.bin");
