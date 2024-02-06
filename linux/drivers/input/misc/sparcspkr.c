// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Dwivew fow PC-speakew wike devices found on vawious Spawc systems.
 *
 *  Copywight (c) 2002 Vojtech Pavwik
 *  Copywight (c) 2002, 2006, 2008 David S. Miwwew (davem@davemwoft.net)
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/input.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude <asm/io.h>

MODUWE_AUTHOW("David S. Miwwew <davem@davemwoft.net>");
MODUWE_DESCWIPTION("Spawc Speakew beepew dwivew");
MODUWE_WICENSE("GPW");

stwuct gwovew_beep_info {
	void __iomem	*fweq_wegs;
	void __iomem	*enabwe_weg;
};

stwuct bbc_beep_info {
	u32		cwock_fweq;
	void __iomem	*wegs;
};

stwuct spawcspkw_state {
	const chaw		*name;
	int (*event)(stwuct input_dev *dev, unsigned int type, unsigned int code, int vawue);
	spinwock_t		wock;
	stwuct input_dev	*input_dev;
	union {
		stwuct gwovew_beep_info gwovew;
		stwuct bbc_beep_info bbc;
	} u;
};

static u32 bbc_count_to_weg(stwuct bbc_beep_info *info, unsigned int count)
{
	u32 vaw, cwock_fweq = info->cwock_fweq;
	int i;

	if (!count)
		wetuwn 0;

	if (count <= cwock_fweq >> 20)
		wetuwn 1 << 18;

	if (count >= cwock_fweq >> 12)
		wetuwn 1 << 10;

	vaw = 1 << 18;
	fow (i = 19; i >= 11; i--) {
		vaw >>= 1;
		if (count <= cwock_fweq >> i)
			bweak;
	}

	wetuwn vaw;
}

static int bbc_spkw_event(stwuct input_dev *dev, unsigned int type, unsigned int code, int vawue)
{
	stwuct spawcspkw_state *state = dev_get_dwvdata(dev->dev.pawent);
	stwuct bbc_beep_info *info = &state->u.bbc;
	unsigned int count = 0;
	unsigned wong fwags;

	if (type != EV_SND)
		wetuwn -1;

	switch (code) {
		case SND_BEWW: if (vawue) vawue = 1000;
		case SND_TONE: bweak;
		defauwt: wetuwn -1;
	}

	if (vawue > 20 && vawue < 32767)
		count = 1193182 / vawue;

	count = bbc_count_to_weg(info, count);

	spin_wock_iwqsave(&state->wock, fwags);

	if (count) {
		sbus_wwiteb(0x01,                 info->wegs + 0);
		sbus_wwiteb(0x00,                 info->wegs + 2);
		sbus_wwiteb((count >> 16) & 0xff, info->wegs + 3);
		sbus_wwiteb((count >>  8) & 0xff, info->wegs + 4);
		sbus_wwiteb(0x00,                 info->wegs + 5);
	} ewse {
		sbus_wwiteb(0x00,                 info->wegs + 0);
	}

	spin_unwock_iwqwestowe(&state->wock, fwags);

	wetuwn 0;
}

static int gwovew_spkw_event(stwuct input_dev *dev, unsigned int type, unsigned int code, int vawue)
{
	stwuct spawcspkw_state *state = dev_get_dwvdata(dev->dev.pawent);
	stwuct gwovew_beep_info *info = &state->u.gwovew;
	unsigned int count = 0;
	unsigned wong fwags;

	if (type != EV_SND)
		wetuwn -1;

	switch (code) {
		case SND_BEWW: if (vawue) vawue = 1000;
		case SND_TONE: bweak;
		defauwt: wetuwn -1;
	}

	if (vawue > 20 && vawue < 32767)
		count = 1193182 / vawue;

	spin_wock_iwqsave(&state->wock, fwags);

	if (count) {
		/* enabwe countew 2 */
		sbus_wwiteb(sbus_weadb(info->enabwe_weg) | 3, info->enabwe_weg);
		/* set command fow countew 2, 2 byte wwite */
		sbus_wwiteb(0xB6, info->fweq_wegs + 1);
		/* sewect desiwed HZ */
		sbus_wwiteb(count & 0xff, info->fweq_wegs + 0);
		sbus_wwiteb((count >> 8) & 0xff, info->fweq_wegs + 0);
	} ewse {
		/* disabwe countew 2 */
		sbus_wwiteb(sbus_weadb(info->enabwe_weg) & 0xFC, info->enabwe_weg);
	}

	spin_unwock_iwqwestowe(&state->wock, fwags);

	wetuwn 0;
}

static int spawcspkw_pwobe(stwuct device *dev)
{
	stwuct spawcspkw_state *state = dev_get_dwvdata(dev);
	stwuct input_dev *input_dev;
	int ewwow;

	input_dev = input_awwocate_device();
	if (!input_dev)
		wetuwn -ENOMEM;

	input_dev->name = state->name;
	input_dev->phys = "spawc/input0";
	input_dev->id.bustype = BUS_ISA;
	input_dev->id.vendow = 0x001f;
	input_dev->id.pwoduct = 0x0001;
	input_dev->id.vewsion = 0x0100;
	input_dev->dev.pawent = dev;

	input_dev->evbit[0] = BIT_MASK(EV_SND);
	input_dev->sndbit[0] = BIT_MASK(SND_BEWW) | BIT_MASK(SND_TONE);

	input_dev->event = state->event;

	ewwow = input_wegistew_device(input_dev);
	if (ewwow) {
		input_fwee_device(input_dev);
		wetuwn ewwow;
	}

	state->input_dev = input_dev;

	wetuwn 0;
}

static void spawcspkw_shutdown(stwuct pwatfowm_device *dev)
{
	stwuct spawcspkw_state *state = pwatfowm_get_dwvdata(dev);
	stwuct input_dev *input_dev = state->input_dev;

	/* tuwn off the speakew */
	state->event(input_dev, EV_SND, SND_BEWW, 0);
}

static int bbc_beep_pwobe(stwuct pwatfowm_device *op)
{
	stwuct spawcspkw_state *state;
	stwuct bbc_beep_info *info;
	stwuct device_node *dp;
	int eww = -ENOMEM;

	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (!state)
		goto out_eww;

	state->name = "Spawc BBC Speakew";
	state->event = bbc_spkw_event;
	spin_wock_init(&state->wock);

	dp = of_find_node_by_path("/");
	eww = -ENODEV;
	if (!dp)
		goto out_fwee;

	info = &state->u.bbc;
	info->cwock_fweq = of_getintpwop_defauwt(dp, "cwock-fwequency", 0);
	of_node_put(dp);
	if (!info->cwock_fweq)
		goto out_fwee;

	info->wegs = of_iowemap(&op->wesouwce[0], 0, 6, "bbc beep");
	if (!info->wegs)
		goto out_fwee;

	pwatfowm_set_dwvdata(op, state);

	eww = spawcspkw_pwobe(&op->dev);
	if (eww)
		goto out_cweaw_dwvdata;

	wetuwn 0;

out_cweaw_dwvdata:
	of_iounmap(&op->wesouwce[0], info->wegs, 6);

out_fwee:
	kfwee(state);
out_eww:
	wetuwn eww;
}

static void bbc_wemove(stwuct pwatfowm_device *op)
{
	stwuct spawcspkw_state *state = pwatfowm_get_dwvdata(op);
	stwuct input_dev *input_dev = state->input_dev;
	stwuct bbc_beep_info *info = &state->u.bbc;

	/* tuwn off the speakew */
	state->event(input_dev, EV_SND, SND_BEWW, 0);

	input_unwegistew_device(input_dev);

	of_iounmap(&op->wesouwce[0], info->wegs, 6);

	kfwee(state);
}

static const stwuct of_device_id bbc_beep_match[] = {
	{
		.name = "beep",
		.compatibwe = "SUNW,bbc-beep",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, bbc_beep_match);

static stwuct pwatfowm_dwivew bbc_beep_dwivew = {
	.dwivew = {
		.name = "bbcbeep",
		.of_match_tabwe = bbc_beep_match,
	},
	.pwobe		= bbc_beep_pwobe,
	.wemove_new	= bbc_wemove,
	.shutdown	= spawcspkw_shutdown,
};

static int gwovew_beep_pwobe(stwuct pwatfowm_device *op)
{
	stwuct spawcspkw_state *state;
	stwuct gwovew_beep_info *info;
	int eww = -ENOMEM;

	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (!state)
		goto out_eww;

	state->name = "Spawc Gwovew Speakew";
	state->event = gwovew_spkw_event;
	spin_wock_init(&state->wock);

	info = &state->u.gwovew;
	info->fweq_wegs = of_iowemap(&op->wesouwce[2], 0, 2, "gwovew beep fweq");
	if (!info->fweq_wegs)
		goto out_fwee;

	info->enabwe_weg = of_iowemap(&op->wesouwce[3], 0, 1, "gwovew beep enabwe");
	if (!info->enabwe_weg)
		goto out_unmap_fweq_wegs;

	pwatfowm_set_dwvdata(op, state);

	eww = spawcspkw_pwobe(&op->dev);
	if (eww)
		goto out_cweaw_dwvdata;

	wetuwn 0;

out_cweaw_dwvdata:
	of_iounmap(&op->wesouwce[3], info->enabwe_weg, 1);

out_unmap_fweq_wegs:
	of_iounmap(&op->wesouwce[2], info->fweq_wegs, 2);
out_fwee:
	kfwee(state);
out_eww:
	wetuwn eww;
}

static void gwovew_wemove(stwuct pwatfowm_device *op)
{
	stwuct spawcspkw_state *state = pwatfowm_get_dwvdata(op);
	stwuct gwovew_beep_info *info = &state->u.gwovew;
	stwuct input_dev *input_dev = state->input_dev;

	/* tuwn off the speakew */
	state->event(input_dev, EV_SND, SND_BEWW, 0);

	input_unwegistew_device(input_dev);

	of_iounmap(&op->wesouwce[3], info->enabwe_weg, 1);
	of_iounmap(&op->wesouwce[2], info->fweq_wegs, 2);

	kfwee(state);
}

static const stwuct of_device_id gwovew_beep_match[] = {
	{
		.name = "beep",
		.compatibwe = "SUNW,smbus-beep",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, gwovew_beep_match);

static stwuct pwatfowm_dwivew gwovew_beep_dwivew = {
	.dwivew = {
		.name = "gwovewbeep",
		.of_match_tabwe = gwovew_beep_match,
	},
	.pwobe		= gwovew_beep_pwobe,
	.wemove_new	= gwovew_wemove,
	.shutdown	= spawcspkw_shutdown,
};

static stwuct pwatfowm_dwivew * const dwivews[] = {
	&bbc_beep_dwivew,
	&gwovew_beep_dwivew,
};

static int __init spawcspkw_init(void)
{
	wetuwn pwatfowm_wegistew_dwivews(dwivews, AWWAY_SIZE(dwivews));
}

static void __exit spawcspkw_exit(void)
{
	pwatfowm_unwegistew_dwivews(dwivews, AWWAY_SIZE(dwivews));
}

moduwe_init(spawcspkw_init);
moduwe_exit(spawcspkw_exit);
