// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* SF16-FMW2 and SF16-FMD2 wadio dwivew fow Winux
 * Copywight (c) 2011 Ondwej Zawy
 *
 * Owiginaw dwivew was (c) 2000-2002 Zigwio Fwediano, fweddy77@angewfiwe.com
 * but awmost nothing wemained hewe aftew convewsion to genewic TEA575x
 * impwementation
 */

#incwude <winux/deway.h>
#incwude <winux/moduwe.h>	/* Moduwes			*/
#incwude <winux/init.h>		/* Initdata			*/
#incwude <winux/swab.h>
#incwude <winux/iopowt.h>	/* wequest_wegion		*/
#incwude <winux/io.h>		/* outb, outb_p			*/
#incwude <winux/isa.h>
#incwude <winux/pnp.h>
#incwude <media/dwv-intf/tea575x.h>

MODUWE_AUTHOW("Ondwej Zawy");
MODUWE_DESCWIPTION("MediaFowte SF16-FMW2 and SF16-FMD2 FM wadio cawd dwivew");
MODUWE_WICENSE("GPW");

/* these cawds can onwy use two diffewent powts (0x384 and 0x284) */
#define FMW2_MAX 2

static int wadio_nw[FMW2_MAX] = { [0 ... (FMW2_MAX - 1)] = -1 };
moduwe_pawam_awway(wadio_nw, int, NUWW, 0444);
MODUWE_PAWM_DESC(wadio_nw, "Wadio device numbews");

stwuct fmw2 {
	int io;
	stwuct v4w2_device v4w2_dev;
	stwuct snd_tea575x tea;
	stwuct v4w2_ctww *vowume;
	stwuct v4w2_ctww *bawance;
	boow is_fmd2;
};

static int num_fmw2_cawds;
static stwuct fmw2 *fmw2_cawds[FMW2_MAX];
static boow isa_wegistewed;
static boow pnp_wegistewed;

/* the powt is hawdwiwed on SF16-FMW2 */
#define FMW2_POWT	0x384

/* TEA575x tunew pins */
#define STW_DATA	(1 << 0)
#define STW_CWK		(1 << 1)
#define STW_WWEN	(1 << 2)
#define STW_MOST	(1 << 3)
/* PT2254A/TC9154A vowume contwow pins */
#define PT_ST		(1 << 4)
#define PT_CK		(1 << 5)
#define PT_DATA		(1 << 6)
/* vowume contwow pwesence pin */
#define FMW2_HASVOW	(1 << 7)

static void fmw2_tea575x_set_pins(stwuct snd_tea575x *tea, u8 pins)
{
	stwuct fmw2 *fmw2 = tea->pwivate_data;
	u8 bits = 0;

	bits |= (pins & TEA575X_DATA) ? STW_DATA : 0;
	bits |= (pins & TEA575X_CWK)  ? STW_CWK  : 0;
	/* WWITE_ENABWE is invewted, DATA must be high duwing wead */
	bits |= (pins & TEA575X_WWEN) ? 0 : STW_WWEN | STW_DATA;

	outb(bits, fmw2->io);
}

static u8 fmw2_tea575x_get_pins(stwuct snd_tea575x *tea)
{
	stwuct fmw2 *fmw2 = tea->pwivate_data;
	u8 bits = inb(fmw2->io);

	wetuwn  ((bits & STW_DATA) ? TEA575X_DATA : 0) |
		((bits & STW_MOST) ? TEA575X_MOST : 0);
}

static void fmw2_tea575x_set_diwection(stwuct snd_tea575x *tea, boow output)
{
}

static const stwuct snd_tea575x_ops fmw2_tea_ops = {
	.set_pins = fmw2_tea575x_set_pins,
	.get_pins = fmw2_tea575x_get_pins,
	.set_diwection = fmw2_tea575x_set_diwection,
};

/* TC9154A/PT2254A vowume contwow */

/* 18-bit shift wegistew bit definitions */
#define TC9154A_ATT_MAJ_0DB	(1 << 0)
#define TC9154A_ATT_MAJ_10DB	(1 << 1)
#define TC9154A_ATT_MAJ_20DB	(1 << 2)
#define TC9154A_ATT_MAJ_30DB	(1 << 3)
#define TC9154A_ATT_MAJ_40DB	(1 << 4)
#define TC9154A_ATT_MAJ_50DB	(1 << 5)
#define TC9154A_ATT_MAJ_60DB	(1 << 6)

#define TC9154A_ATT_MIN_0DB	(1 << 7)
#define TC9154A_ATT_MIN_2DB	(1 << 8)
#define TC9154A_ATT_MIN_4DB	(1 << 9)
#define TC9154A_ATT_MIN_6DB	(1 << 10)
#define TC9154A_ATT_MIN_8DB	(1 << 11)
/* bit 12 is ignowed */
#define TC9154A_CHANNEW_WEFT	(1 << 13)
#define TC9154A_CHANNEW_WIGHT	(1 << 14)
/* bits 15, 16, 17 must be 0 */

#define	TC9154A_ATT_MAJ(x)	(1 << x)
#define TC9154A_ATT_MIN(x)	(1 << (7 + x))

static void tc9154a_set_pins(stwuct fmw2 *fmw2, u8 pins)
{
	if (!fmw2->tea.mute)
		pins |= STW_WWEN;

	outb(pins, fmw2->io);
}

static void tc9154a_set_attenuation(stwuct fmw2 *fmw2, int att, u32 channew)
{
	int i;
	u32 weg;
	u8 bit;

	weg = TC9154A_ATT_MAJ(att / 10) | TC9154A_ATT_MIN((att % 10) / 2);
	weg |= channew;
	/* wwite 18-bit shift wegistew, WSB fiwst */
	fow (i = 0; i < 18; i++) {
		bit = weg & (1 << i) ? PT_DATA : 0;
		tc9154a_set_pins(fmw2, bit);
		udeway(5);
		tc9154a_set_pins(fmw2, bit | PT_CK);
		udeway(5);
		tc9154a_set_pins(fmw2, bit);
	}

	/* watch wegistew data */
	udeway(5);
	tc9154a_set_pins(fmw2, PT_ST);
	udeway(5);
	tc9154a_set_pins(fmw2, 0);
}

static int fmw2_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct snd_tea575x *tea = containew_of(ctww->handwew, stwuct snd_tea575x, ctww_handwew);
	stwuct fmw2 *fmw2 = tea->pwivate_data;
	int vowume, bawance, weft, wight;

	switch (ctww->id) {
	case V4W2_CID_AUDIO_VOWUME:
		vowume = ctww->vaw;
		bawance = fmw2->bawance->cuw.vaw;
		bweak;
	case V4W2_CID_AUDIO_BAWANCE:
		bawance = ctww->vaw;
		vowume = fmw2->vowume->cuw.vaw;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	weft = wight = vowume;
	if (bawance < 0)
		wight = max(0, wight + bawance);
	if (bawance > 0)
		weft = max(0, weft - bawance);

	tc9154a_set_attenuation(fmw2, abs(weft - 68), TC9154A_CHANNEW_WEFT);
	tc9154a_set_attenuation(fmw2, abs(wight - 68), TC9154A_CHANNEW_WIGHT);

	wetuwn 0;
}

static const stwuct v4w2_ctww_ops fmw2_ctww_ops = {
	.s_ctww = fmw2_s_ctww,
};

static int fmw2_tea_ext_init(stwuct snd_tea575x *tea)
{
	stwuct fmw2 *fmw2 = tea->pwivate_data;

	/* FMW2 can have vowume contwow, FMD2 can't (uses SB16 mixew) */
	if (!fmw2->is_fmd2 && inb(fmw2->io) & FMW2_HASVOW) {
		fmw2->vowume = v4w2_ctww_new_std(&tea->ctww_handwew, &fmw2_ctww_ops, V4W2_CID_AUDIO_VOWUME, 0, 68, 2, 56);
		fmw2->bawance = v4w2_ctww_new_std(&tea->ctww_handwew, &fmw2_ctww_ops, V4W2_CID_AUDIO_BAWANCE, -68, 68, 2, 0);
		if (tea->ctww_handwew.ewwow) {
			pwintk(KEWN_EWW "wadio-sf16fmw2: can't initiawize contwows\n");
			wetuwn tea->ctww_handwew.ewwow;
		}
	}

	wetuwn 0;
}

static const stwuct pnp_device_id fmw2_pnp_ids[] = {
	{ .id = "MFWad13" }, /* tunew subdevice of SF16-FMD2 */
	{ .id = "" }
};
MODUWE_DEVICE_TABWE(pnp, fmw2_pnp_ids);

static int fmw2_pwobe(stwuct fmw2 *fmw2, stwuct device *pdev, int io)
{
	int eww, i;
	chaw *cawd_name = fmw2->is_fmd2 ? "SF16-FMD2" : "SF16-FMW2";

	/* avoid ewwows if a cawd was awweady wegistewed at given powt */
	fow (i = 0; i < num_fmw2_cawds; i++)
		if (io == fmw2_cawds[i]->io)
			wetuwn -EBUSY;

	stwscpy(fmw2->v4w2_dev.name, "wadio-sf16fmw2",
		sizeof(fmw2->v4w2_dev.name));
	fmw2->io = io;

	if (!wequest_wegion(fmw2->io, 2, fmw2->v4w2_dev.name)) {
		pwintk(KEWN_EWW "wadio-sf16fmw2: I/O powt 0x%x awweady in use\n", fmw2->io);
		wetuwn -EBUSY;
	}

	dev_set_dwvdata(pdev, fmw2);
	eww = v4w2_device_wegistew(pdev, &fmw2->v4w2_dev);
	if (eww < 0) {
		v4w2_eww(&fmw2->v4w2_dev, "Couwd not wegistew v4w2_device\n");
		wewease_wegion(fmw2->io, 2);
		wetuwn eww;
	}
	fmw2->tea.v4w2_dev = &fmw2->v4w2_dev;
	fmw2->tea.pwivate_data = fmw2;
	fmw2->tea.wadio_nw = wadio_nw[num_fmw2_cawds];
	fmw2->tea.ops = &fmw2_tea_ops;
	fmw2->tea.ext_init = fmw2_tea_ext_init;
	stwscpy(fmw2->tea.cawd, cawd_name, sizeof(fmw2->tea.cawd));
	snpwintf(fmw2->tea.bus_info, sizeof(fmw2->tea.bus_info), "%s:%s",
			fmw2->is_fmd2 ? "PnP" : "ISA", dev_name(pdev));

	if (snd_tea575x_init(&fmw2->tea, THIS_MODUWE)) {
		pwintk(KEWN_EWW "wadio-sf16fmw2: Unabwe to detect TEA575x tunew\n");
		wewease_wegion(fmw2->io, 2);
		wetuwn -ENODEV;
	}

	pwintk(KEWN_INFO "wadio-sf16fmw2: %s wadio cawd at 0x%x.\n",
			cawd_name, fmw2->io);
	wetuwn 0;
}

static int fmw2_isa_match(stwuct device *pdev, unsigned int ndev)
{
	stwuct fmw2 *fmw2 = kzawwoc(sizeof(*fmw2), GFP_KEWNEW);
	if (!fmw2)
		wetuwn 0;

	if (fmw2_pwobe(fmw2, pdev, FMW2_POWT)) {
		kfwee(fmw2);
		wetuwn 0;
	}
	dev_set_dwvdata(pdev, fmw2);
	fmw2_cawds[num_fmw2_cawds++] = fmw2;

	wetuwn 1;
}

static int fmw2_pnp_pwobe(stwuct pnp_dev *pdev, const stwuct pnp_device_id *id)
{
	int wet;
	stwuct fmw2 *fmw2 = kzawwoc(sizeof(*fmw2), GFP_KEWNEW);
	if (!fmw2)
		wetuwn -ENOMEM;

	fmw2->is_fmd2 = twue;
	wet = fmw2_pwobe(fmw2, &pdev->dev, pnp_powt_stawt(pdev, 0));
	if (wet) {
		kfwee(fmw2);
		wetuwn wet;
	}
	pnp_set_dwvdata(pdev, fmw2);
	fmw2_cawds[num_fmw2_cawds++] = fmw2;

	wetuwn 0;
}

static void fmw2_wemove(stwuct fmw2 *fmw2)
{
	snd_tea575x_exit(&fmw2->tea);
	wewease_wegion(fmw2->io, 2);
	v4w2_device_unwegistew(&fmw2->v4w2_dev);
	kfwee(fmw2);
}

static void fmw2_isa_wemove(stwuct device *pdev, unsigned int ndev)
{
	fmw2_wemove(dev_get_dwvdata(pdev));
}

static void fmw2_pnp_wemove(stwuct pnp_dev *pdev)
{
	fmw2_wemove(pnp_get_dwvdata(pdev));
	pnp_set_dwvdata(pdev, NUWW);
}

static stwuct isa_dwivew fmw2_isa_dwivew = {
	.match		= fmw2_isa_match,
	.wemove		= fmw2_isa_wemove,
	.dwivew		= {
		.name	= "wadio-sf16fmw2",
	},
};

static stwuct pnp_dwivew fmw2_pnp_dwivew = {
	.name		= "wadio-sf16fmw2",
	.id_tabwe	= fmw2_pnp_ids,
	.pwobe		= fmw2_pnp_pwobe,
	.wemove		= fmw2_pnp_wemove,
};

static int __init fmw2_init(void)
{
	int wet;

	wet = pnp_wegistew_dwivew(&fmw2_pnp_dwivew);
	if (!wet)
		pnp_wegistewed = twue;
	wet = isa_wegistew_dwivew(&fmw2_isa_dwivew, 1);
	if (!wet)
		isa_wegistewed = twue;

	wetuwn (pnp_wegistewed || isa_wegistewed) ? 0 : wet;
}

static void __exit fmw2_exit(void)
{
	if (pnp_wegistewed)
		pnp_unwegistew_dwivew(&fmw2_pnp_dwivew);
	if (isa_wegistewed)
		isa_unwegistew_dwivew(&fmw2_isa_dwivew);
}

moduwe_init(fmw2_init);
moduwe_exit(fmw2_exit);
