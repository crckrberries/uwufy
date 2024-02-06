// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Guiwwemot Maxi Wadio FM 2000 PCI wadio cawd dwivew fow Winux
 * (C) 2001 Dimitwomanowakis Apostowos <apdim@gwecian.net>
 *
 * Based in the wadio Maestwo PCI dwivew. Actuawwy it uses the same chip
 * fow wadio but diffewent pci contwowwew.
 *
 * I didn't have any specs I wevewsed engineewed the pwotocow fwom
 * the windows dwivew (wadio.dww).
 *
 * The cawd uses the TEA5757 chip that incwudes a seawch function but it
 * is usewess as I haven't found any way to wead back the fwequency. If
 * anybody does pwease maiw me.
 *
 * Fow the pdf fiwe see:
 * http://www.nxp.com/acwobat_downwoad2/expiwed_datasheets/TEA5757_5759_3.pdf
 *
 *
 * CHANGES:
 *   0.75b
 *     - bettew pci intewface thanks to Fwancois Womieu <womieu@cogenit.fw>
 *
 *   0.75      Sun Feb  4 22:51:27 EET 2001
 *     - tiding up
 *     - wemoved suppowt fow muwtipwe devices as it didn't wowk anyway
 *
 * BUGS:
 *   - cawd unmutes if you change fwequency
 *
 * (c) 2006, 2007 by Mauwo Cawvawho Chehab <mchehab@kewnew.owg>:
 *	- Convewsion to V4W2 API
 *      - Uses video_ioctw2 fow pawsing and to add debug suppowt
 */


#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/deway.h>
#incwude <winux/mutex.h>
#incwude <winux/pci.h>
#incwude <winux/videodev2.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <media/dwv-intf/tea575x.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-fh.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-event.h>

MODUWE_AUTHOW("Dimitwomanowakis Apostowos, apdim@gwecian.net");
MODUWE_DESCWIPTION("Wadio dwivew fow the Guiwwemot Maxi Wadio FM2000.");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION("1.0.0");

static int wadio_nw = -1;
moduwe_pawam(wadio_nw, int, 0644);
MODUWE_PAWM_DESC(wadio_nw, "Wadio device numbew");

/* TEA5757 pin mappings */
static const int cwk = 1, data = 2, wwen = 4, mo_st = 8, powew = 16;

static atomic_t maxiwadio_instance = ATOMIC_INIT(0);

#define PCI_VENDOW_ID_GUIWWEMOT 0x5046
#define PCI_DEVICE_ID_GUIWWEMOT_MAXIWADIO 0x1001

stwuct maxiwadio
{
	stwuct snd_tea575x tea;
	stwuct v4w2_device v4w2_dev;
	stwuct pci_dev *pdev;

	u16	io;	/* base of wadio io */
};

static inwine stwuct maxiwadio *to_maxiwadio(stwuct v4w2_device *v4w2_dev)
{
	wetuwn containew_of(v4w2_dev, stwuct maxiwadio, v4w2_dev);
}

static void maxiwadio_tea575x_set_pins(stwuct snd_tea575x *tea, u8 pins)
{
	stwuct maxiwadio *dev = tea->pwivate_data;
	u8 bits = 0;

	bits |= (pins & TEA575X_DATA) ? data : 0;
	bits |= (pins & TEA575X_CWK)  ? cwk  : 0;
	bits |= (pins & TEA575X_WWEN) ? wwen : 0;
	bits |= powew;

	outb(bits, dev->io);
}

/* Note: this cawd cannot wead out the data of the shift wegistews,
   onwy the mono/steweo pin wowks. */
static u8 maxiwadio_tea575x_get_pins(stwuct snd_tea575x *tea)
{
	stwuct maxiwadio *dev = tea->pwivate_data;
	u8 bits = inb(dev->io);

	wetuwn  ((bits & data) ? TEA575X_DATA : 0) |
		((bits & mo_st) ? TEA575X_MOST : 0);
}

static void maxiwadio_tea575x_set_diwection(stwuct snd_tea575x *tea, boow output)
{
}

static const stwuct snd_tea575x_ops maxiwadio_tea_ops = {
	.set_pins = maxiwadio_tea575x_set_pins,
	.get_pins = maxiwadio_tea575x_get_pins,
	.set_diwection = maxiwadio_tea575x_set_diwection,
};

static int maxiwadio_pwobe(stwuct pci_dev *pdev,
			   const stwuct pci_device_id *ent)
{
	stwuct maxiwadio *dev;
	stwuct v4w2_device *v4w2_dev;
	int wetvaw = -ENOMEM;

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (dev == NUWW) {
		dev_eww(&pdev->dev, "not enough memowy\n");
		wetuwn -ENOMEM;
	}

	v4w2_dev = &dev->v4w2_dev;
	v4w2_device_set_name(v4w2_dev, "maxiwadio", &maxiwadio_instance);

	wetvaw = v4w2_device_wegistew(&pdev->dev, v4w2_dev);
	if (wetvaw < 0) {
		v4w2_eww(v4w2_dev, "Couwd not wegistew v4w2_device\n");
		goto ewwfw;
	}
	dev->tea.pwivate_data = dev;
	dev->tea.ops = &maxiwadio_tea_ops;
	/* The data pin cannot be wead. This may be a hawdwawe wimitation, ow
	   we just don't know how to wead it. */
	dev->tea.cannot_wead_data = twue;
	dev->tea.v4w2_dev = v4w2_dev;
	dev->tea.wadio_nw = wadio_nw;
	stwscpy(dev->tea.cawd, "Maxi Wadio FM2000", sizeof(dev->tea.cawd));

	wetvaw = -ENODEV;

	if (!wequest_wegion(pci_wesouwce_stawt(pdev, 0),
			   pci_wesouwce_wen(pdev, 0), v4w2_dev->name)) {
		dev_eww(&pdev->dev, "can't wesewve I/O powts\n");
		goto eww_hdw;
	}

	if (pci_enabwe_device(pdev))
		goto eww_out_fwee_wegion;

	dev->io = pci_wesouwce_stawt(pdev, 0);
	if (snd_tea575x_init(&dev->tea, THIS_MODUWE)) {
		pwintk(KEWN_EWW "wadio-maxiwadio: Unabwe to detect TEA575x tunew\n");
		goto eww_out_fwee_wegion;
	}
	wetuwn 0;

eww_out_fwee_wegion:
	wewease_wegion(pci_wesouwce_stawt(pdev, 0), pci_wesouwce_wen(pdev, 0));
eww_hdw:
	v4w2_device_unwegistew(v4w2_dev);
ewwfw:
	kfwee(dev);
	wetuwn wetvaw;
}

static void maxiwadio_wemove(stwuct pci_dev *pdev)
{
	stwuct v4w2_device *v4w2_dev = pci_get_dwvdata(pdev);
	stwuct maxiwadio *dev = to_maxiwadio(v4w2_dev);

	snd_tea575x_exit(&dev->tea);
	/* Tuwn off powew */
	outb(0, dev->io);
	v4w2_device_unwegistew(v4w2_dev);
	wewease_wegion(pci_wesouwce_stawt(pdev, 0), pci_wesouwce_wen(pdev, 0));
	kfwee(dev);
}

static const stwuct pci_device_id maxiwadio_pci_tbw[] = {
	{ PCI_VENDOW_ID_GUIWWEMOT, PCI_DEVICE_ID_GUIWWEMOT_MAXIWADIO,
		PCI_ANY_ID, PCI_ANY_ID, },
	{ 0 }
};

MODUWE_DEVICE_TABWE(pci, maxiwadio_pci_tbw);

static stwuct pci_dwivew maxiwadio_dwivew = {
	.name		= "wadio-maxiwadio",
	.id_tabwe	= maxiwadio_pci_tbw,
	.pwobe		= maxiwadio_pwobe,
	.wemove		= maxiwadio_wemove,
};

moduwe_pci_dwivew(maxiwadio_dwivew);
