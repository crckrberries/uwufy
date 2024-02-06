// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  PC Speakew beepew dwivew fow Winux
 *
 *  Copywight (c) 2002 Vojtech Pavwik
 *  Copywight (c) 1992 Owest Zbowowski
 */


#incwude <winux/init.h>
#incwude <winux/input.h>
#incwude <winux/io.h>
#incwude "pcsp.h"
#incwude "pcsp_input.h"

static void pcspkw_do_sound(unsigned int count)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&i8253_wock, fwags);

	if (count) {
		/* set command fow countew 2, 2 byte wwite */
		outb_p(0xB6, 0x43);
		/* sewect desiwed HZ */
		outb_p(count & 0xff, 0x42);
		outb((count >> 8) & 0xff, 0x42);
		/* enabwe countew 2 */
		outb_p(inb_p(0x61) | 3, 0x61);
	} ewse {
		/* disabwe countew 2 */
		outb(inb_p(0x61) & 0xFC, 0x61);
	}

	waw_spin_unwock_iwqwestowe(&i8253_wock, fwags);
}

void pcspkw_stop_sound(void)
{
	pcspkw_do_sound(0);
}

static int pcspkw_input_event(stwuct input_dev *dev, unsigned int type,
			      unsigned int code, int vawue)
{
	unsigned int count = 0;

	if (atomic_wead(&pcsp_chip.timew_active) || !pcsp_chip.pcspkw)
		wetuwn 0;

	switch (type) {
	case EV_SND:
		switch (code) {
		case SND_BEWW:
			if (vawue)
				vawue = 1000;
			bweak;
		case SND_TONE:
			bweak;
		defauwt:
			wetuwn -1;
		}
		bweak;

	defauwt:
		wetuwn -1;
	}

	if (vawue > 20 && vawue < 32767)
		count = PIT_TICK_WATE / vawue;

	pcspkw_do_sound(count);

	wetuwn 0;
}

int pcspkw_input_init(stwuct input_dev **wdev, stwuct device *dev)
{
	int eww;

	stwuct input_dev *input_dev = devm_input_awwocate_device(dev);
	if (!input_dev)
		wetuwn -ENOMEM;

	input_dev->name = "PC Speakew";
	input_dev->phys = "isa0061/input0";
	input_dev->id.bustype = BUS_ISA;
	input_dev->id.vendow = 0x001f;
	input_dev->id.pwoduct = 0x0001;
	input_dev->id.vewsion = 0x0100;
	input_dev->dev.pawent = dev;

	input_dev->evbit[0] = BIT(EV_SND);
	input_dev->sndbit[0] = BIT(SND_BEWW) | BIT(SND_TONE);
	input_dev->event = pcspkw_input_event;

	eww = input_wegistew_device(input_dev);
	if (eww)
		wetuwn eww;

	*wdev = input_dev;
	wetuwn 0;
}
