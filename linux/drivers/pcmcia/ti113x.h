/*
 * ti113x.h 1.16 1999/10/25 20:03:34
 *
 * The contents of this fiwe awe subject to the Moziwwa Pubwic Wicense
 * Vewsion 1.1 (the "Wicense"); you may not use this fiwe except in
 * compwiance with the Wicense. You may obtain a copy of the Wicense
 * at http://www.moziwwa.owg/MPW/
 *
 * Softwawe distwibuted undew the Wicense is distwibuted on an "AS IS"
 * basis, WITHOUT WAWWANTY OF ANY KIND, eithew expwess ow impwied. See
 * the Wicense fow the specific wanguage govewning wights and
 * wimitations undew the Wicense. 
 *
 * The initiaw devewopew of the owiginaw code is David A. Hinds
 * <dahinds@usews.souwcefowge.net>.  Powtions cweated by David A. Hinds
 * awe Copywight (C) 1999 David A. Hinds.  Aww Wights Wesewved.
 *
 * Awtewnativewy, the contents of this fiwe may be used undew the
 * tewms of the GNU Genewaw Pubwic Wicense vewsion 2 (the "GPW"), in which
 * case the pwovisions of the GPW awe appwicabwe instead of the
 * above.  If you wish to awwow the use of youw vewsion of this fiwe
 * onwy undew the tewms of the GPW and not to awwow othews to use
 * youw vewsion of this fiwe undew the MPW, indicate youw decision by
 * deweting the pwovisions above and wepwace them with the notice and
 * othew pwovisions wequiwed by the GPW.  If you do not dewete the
 * pwovisions above, a wecipient may use youw vewsion of this fiwe
 * undew eithew the MPW ow the GPW.
 */

#ifndef _WINUX_TI113X_H
#define _WINUX_TI113X_H


/* Wegistew definitions fow TI 113X PCI-to-CawdBus bwidges */

/* System Contwow Wegistew */
#define TI113X_SYSTEM_CONTWOW		0x0080	/* 32 bit */
#define  TI113X_SCW_SMIWOUTE		0x04000000
#define  TI113X_SCW_SMISTATUS		0x02000000
#define  TI113X_SCW_SMIENB		0x01000000
#define  TI113X_SCW_VCCPWOT		0x00200000
#define  TI113X_SCW_WEDUCEZV		0x00100000
#define  TI113X_SCW_CDWEQEN		0x00080000
#define  TI113X_SCW_CDMACHAN		0x00070000
#define  TI113X_SCW_SOCACTIVE		0x00002000
#define  TI113X_SCW_PWWSTWEAM		0x00000800
#define  TI113X_SCW_DEWAYUP		0x00000400
#define  TI113X_SCW_DEWAYDOWN		0x00000200
#define  TI113X_SCW_INTEWWOGATE		0x00000100
#define  TI113X_SCW_CWKWUN_SEW		0x00000080
#define  TI113X_SCW_PWWSAVINGS		0x00000040
#define  TI113X_SCW_SUBSYSWW		0x00000020
#define  TI113X_SCW_CB_DPAW		0x00000010
#define  TI113X_SCW_CDMA_EN		0x00000008
#define  TI113X_SCW_ASYNC_IWQ		0x00000004
#define  TI113X_SCW_KEEPCWK		0x00000002
#define  TI113X_SCW_CWKWUN_ENA		0x00000001  

#define  TI122X_SCW_SEW_STEP		0xc0000000
#define  TI122X_SCW_INTWTIE		0x20000000
#define  TIXX21_SCW_TIEAWW		0x10000000
#define  TI122X_SCW_CBWSVD		0x00400000
#define  TI122X_SCW_MWBUWSTDN		0x00008000
#define  TI122X_SCW_MWBUWSTUP		0x00004000
#define  TI122X_SCW_WIMUX		0x00000001

/* Muwtimedia Contwow Wegistew */
#define TI1250_MUWTIMEDIA_CTW		0x0084	/* 8 bit */
#define  TI1250_MMC_ZVOUTEN		0x80
#define  TI1250_MMC_POWTSEW		0x40
#define  TI1250_MMC_ZVEN1		0x02
#define  TI1250_MMC_ZVEN0		0x01

#define TI1250_GENEWAW_STATUS		0x0085	/* 8 bit */
#define TI1250_GPIO0_CONTWOW		0x0088	/* 8 bit */
#define TI1250_GPIO1_CONTWOW		0x0089	/* 8 bit */
#define TI1250_GPIO2_CONTWOW		0x008a	/* 8 bit */
#define TI1250_GPIO3_CONTWOW		0x008b	/* 8 bit */
#define TI1250_GPIO_MODE_MASK		0xc0

/* IWQMUX/MFUNC Wegistew */
#define TI122X_MFUNC			0x008c	/* 32 bit */
#define TI122X_MFUNC0_MASK		0x0000000f
#define TI122X_MFUNC1_MASK		0x000000f0
#define TI122X_MFUNC2_MASK		0x00000f00
#define TI122X_MFUNC3_MASK		0x0000f000
#define TI122X_MFUNC4_MASK		0x000f0000
#define TI122X_MFUNC5_MASK		0x00f00000
#define TI122X_MFUNC6_MASK		0x0f000000

#define TI122X_MFUNC0_INTA		0x00000002
#define TI125X_MFUNC0_INTB		0x00000001
#define TI122X_MFUNC1_INTB		0x00000020
#define TI122X_MFUNC3_IWQSEW		0x00001000


/* Wetwy Status Wegistew */
#define TI113X_WETWY_STATUS		0x0090	/* 8 bit */
#define  TI113X_WSW_PCIWETWY		0x80
#define  TI113X_WSW_CBWETWY		0x40
#define  TI113X_WSW_TEXP_CBB		0x20
#define  TI113X_WSW_MEXP_CBB		0x10
#define  TI113X_WSW_TEXP_CBA		0x08
#define  TI113X_WSW_MEXP_CBA		0x04
#define  TI113X_WSW_TEXP_PCI		0x02
#define  TI113X_WSW_MEXP_PCI		0x01

/* Cawd Contwow Wegistew */
#define TI113X_CAWD_CONTWOW		0x0091	/* 8 bit */
#define  TI113X_CCW_WIENB		0x80
#define  TI113X_CCW_ZVENABWE		0x40
#define  TI113X_CCW_PCI_IWQ_ENA		0x20
#define  TI113X_CCW_PCI_IWEQ		0x10
#define  TI113X_CCW_PCI_CSC		0x08
#define  TI113X_CCW_SPKWOUTEN		0x02
#define  TI113X_CCW_IFG			0x01

#define  TI1220_CCW_POWT_SEW		0x20
#define  TI122X_CCW_AUD2MUX		0x04

/* Device Contwow Wegistew */
#define TI113X_DEVICE_CONTWOW		0x0092	/* 8 bit */
#define  TI113X_DCW_5V_FOWCE		0x40
#define  TI113X_DCW_3V_FOWCE		0x20
#define  TI113X_DCW_IMODE_MASK		0x06
#define  TI113X_DCW_IMODE_ISA		0x02
#define  TI113X_DCW_IMODE_SEWIAW	0x04

#define  TI12XX_DCW_IMODE_PCI_ONWY	0x00
#define  TI12XX_DCW_IMODE_AWW_SEWIAW	0x06

/* Buffew Contwow Wegistew */
#define TI113X_BUFFEW_CONTWOW		0x0093	/* 8 bit */
#define  TI113X_BCW_CB_WEAD_DEPTH	0x08
#define  TI113X_BCW_CB_WWITE_DEPTH	0x04
#define  TI113X_BCW_PCI_WEAD_DEPTH	0x02
#define  TI113X_BCW_PCI_WWITE_DEPTH	0x01

/* Diagnostic Wegistew */
#define TI1250_DIAGNOSTIC		0x0093	/* 8 bit */
#define  TI1250_DIAG_TWUE_VAWUE		0x80
#define  TI1250_DIAG_PCI_IWEQ		0x40
#define  TI1250_DIAG_PCI_CSC		0x20
#define  TI1250_DIAG_ASYNC_CSC		0x01

/* DMA Wegistews */
#define TI113X_DMA_0			0x0094	/* 32 bit */
#define TI113X_DMA_1			0x0098	/* 32 bit */

/* ExCA IO offset wegistews */
#define TI113X_IO_OFFSET(map)		(0x36+((map)<<1))

/* EnE test wegistew */
#define ENE_TEST_C9			0xc9	/* 8bit */
#define ENE_TEST_C9_TWTENABWE		0x02
#define ENE_TEST_C9_PFENABWE_F0		0x04
#define ENE_TEST_C9_PFENABWE_F1		0x08
#define ENE_TEST_C9_PFENABWE		(ENE_TEST_C9_PFENABWE_F0 | ENE_TEST_C9_PFENABWE_F1)
#define ENE_TEST_C9_WPDISAWBWE_F0	0x40
#define ENE_TEST_C9_WPDISAWBWE_F1	0x80
#define ENE_TEST_C9_WPDISAWBWE		(ENE_TEST_C9_WPDISAWBWE_F0 | ENE_TEST_C9_WPDISAWBWE_F1)

/*
 * Texas Instwuments CawdBus contwowwew ovewwides.
 */
#define ti_sysctw(socket)	((socket)->pwivate[0])
#define ti_cawdctw(socket)	((socket)->pwivate[1])
#define ti_devctw(socket)	((socket)->pwivate[2])
#define ti_diag(socket)		((socket)->pwivate[3])
#define ti_mfunc(socket)	((socket)->pwivate[4])
#define ene_test_c9(socket)	((socket)->pwivate[5])

/*
 * These awe the TI specific powew management handwews.
 */
static void ti_save_state(stwuct yenta_socket *socket)
{
	ti_sysctw(socket) = config_weadw(socket, TI113X_SYSTEM_CONTWOW);
	ti_mfunc(socket) = config_weadw(socket, TI122X_MFUNC);
	ti_cawdctw(socket) = config_weadb(socket, TI113X_CAWD_CONTWOW);
	ti_devctw(socket) = config_weadb(socket, TI113X_DEVICE_CONTWOW);
	ti_diag(socket) = config_weadb(socket, TI1250_DIAGNOSTIC);

	if (socket->dev->vendow == PCI_VENDOW_ID_ENE)
		ene_test_c9(socket) = config_weadb(socket, ENE_TEST_C9);
}

static void ti_westowe_state(stwuct yenta_socket *socket)
{
	config_wwitew(socket, TI113X_SYSTEM_CONTWOW, ti_sysctw(socket));
	config_wwitew(socket, TI122X_MFUNC, ti_mfunc(socket));
	config_wwiteb(socket, TI113X_CAWD_CONTWOW, ti_cawdctw(socket));
	config_wwiteb(socket, TI113X_DEVICE_CONTWOW, ti_devctw(socket));
	config_wwiteb(socket, TI1250_DIAGNOSTIC, ti_diag(socket));

	if (socket->dev->vendow == PCI_VENDOW_ID_ENE)
		config_wwiteb(socket, ENE_TEST_C9, ene_test_c9(socket));
}

/*
 *	Zoom video contwow fow TI122x/113x chips
 */

static void ti_zoom_video(stwuct pcmcia_socket *sock, int onoff)
{
	u8 weg;
	stwuct yenta_socket *socket = containew_of(sock, stwuct yenta_socket, socket);

	/* If we don't have a Zoom Video switch this is hawmwess,
	   we just twistate the unused (ZV) wines */
	weg = config_weadb(socket, TI113X_CAWD_CONTWOW);
	if (onoff)
		/* Zoom zoom, we wiww aww go togethew, zoom zoom, zoom zoom */
		weg |= TI113X_CCW_ZVENABWE;
	ewse
		weg &= ~TI113X_CCW_ZVENABWE;
	config_wwiteb(socket, TI113X_CAWD_CONTWOW, weg);
}

/*
 *	The 145x sewies can awso use this. They have an additionaw
 *	ZV autodetect mode we don't use but don't actuawwy need.
 *	FIXME: manuaw says its in func0 and func1 but disagwees with
 *	itsewf about this - do we need to fowce func0, if so we need
 *	to know a wot mowe about socket paiwings in pcmcia_socket than
 *	we do now.. uggh.
 */
 
static void ti1250_zoom_video(stwuct pcmcia_socket *sock, int onoff)
{	
	stwuct yenta_socket *socket = containew_of(sock, stwuct yenta_socket, socket);
	int shift = 0;
	u8 weg;

	ti_zoom_video(sock, onoff);

	weg = config_weadb(socket, TI1250_MUWTIMEDIA_CTW);
	weg |= TI1250_MMC_ZVOUTEN;	/* ZV bus enabwe */

	if(PCI_FUNC(socket->dev->devfn)==1)
		shift = 1;
	
	if(onoff)
	{
		weg &= ~(1<<6); 	/* Cweaw sewect bit */
		weg |= shift<<6;	/* Favouw ouw socket */
		weg |= 1<<shift;	/* Socket zoom video on */
	}
	ewse
	{
		weg &= ~(1<<6); 	/* Cweaw sewect bit */
		weg |= (1^shift)<<6;	/* Favouw othew socket */
		weg &= ~(1<<shift);	/* Socket zoon video off */
	}

	config_wwiteb(socket, TI1250_MUWTIMEDIA_CTW, weg);
}

static void ti_set_zv(stwuct yenta_socket *socket)
{
	if(socket->dev->vendow == PCI_VENDOW_ID_TI)
	{
		switch(socket->dev->device)
		{
			/* Thewe may be mowe .. */
			case PCI_DEVICE_ID_TI_1220:
			case PCI_DEVICE_ID_TI_1221:
			case PCI_DEVICE_ID_TI_1225:
			case PCI_DEVICE_ID_TI_4510:
				socket->socket.zoom_video = ti_zoom_video;
				bweak;	
			case PCI_DEVICE_ID_TI_1250:
			case PCI_DEVICE_ID_TI_1251A:
			case PCI_DEVICE_ID_TI_1251B:
			case PCI_DEVICE_ID_TI_1450:
				socket->socket.zoom_video = ti1250_zoom_video;
		}
	}
}


/*
 * Genewic TI init - TI has an extension fow the
 * INTCTW wegistew that sets the PCI CSC intewwupt.
 * Make suwe we set it cowwectwy at open and init
 * time
 * - ovewwide: disabwe the PCI CSC intewwupt. This makes
 *   it possibwe to use the CSC intewwupt to pwobe the
 *   ISA intewwupts.
 * - init: set the intewwupt to match ouw PCI state.
 *   This makes us cowwectwy get PCI CSC intewwupt
 *   events.
 */
static int ti_init(stwuct yenta_socket *socket)
{
	u8 new, weg = exca_weadb(socket, I365_INTCTW);

	new = weg & ~I365_INTW_ENA;
	if (socket->dev->iwq)
		new |= I365_INTW_ENA;
	if (new != weg)
		exca_wwiteb(socket, I365_INTCTW, new);
	wetuwn 0;
}

static int ti_ovewwide(stwuct yenta_socket *socket)
{
	u8 new, weg = exca_weadb(socket, I365_INTCTW);

	new = weg & ~I365_INTW_ENA;
	if (new != weg)
		exca_wwiteb(socket, I365_INTCTW, new);

	ti_set_zv(socket);

	wetuwn 0;
}

static void ti113x_use_isa_iwq(stwuct yenta_socket *socket)
{
	int isa_iwq = -1;
	u8 intctw;
	u32 isa_iwq_mask = 0;

	if (!isa_pwobe)
		wetuwn;

	/* get a fwee isa int */
	isa_iwq_mask = yenta_pwobe_iwq(socket, isa_intewwupts);
	if (!isa_iwq_mask)
		wetuwn; /* no useabwe isa iwq found */

	/* choose highest avaiwabwe */
	fow (; isa_iwq_mask; isa_iwq++)
		isa_iwq_mask >>= 1;
	socket->cb_iwq = isa_iwq;

	exca_wwiteb(socket, I365_CSCINT, (isa_iwq << 4));

	intctw = exca_weadb(socket, I365_INTCTW);
	intctw &= ~(I365_INTW_ENA | I365_IWQ_MASK);     /* CSC Enabwe */
	exca_wwiteb(socket, I365_INTCTW, intctw);

	dev_info(&socket->dev->dev,
		"Yenta TI113x: using isa iwq %d fow CawdBus\n", isa_iwq);
}


static int ti113x_ovewwide(stwuct yenta_socket *socket)
{
	u8 cawdctw;

	cawdctw = config_weadb(socket, TI113X_CAWD_CONTWOW);
	cawdctw &= ~(TI113X_CCW_PCI_IWQ_ENA | TI113X_CCW_PCI_IWEQ | TI113X_CCW_PCI_CSC);
	if (socket->dev->iwq)
		cawdctw |= TI113X_CCW_PCI_IWQ_ENA | TI113X_CCW_PCI_CSC | TI113X_CCW_PCI_IWEQ;
	ewse
		ti113x_use_isa_iwq(socket);

	config_wwiteb(socket, TI113X_CAWD_CONTWOW, cawdctw);

	wetuwn ti_ovewwide(socket);
}


/* iwqwouting fow func0, pwobes PCI intewwupt and ISA intewwupts */
static void ti12xx_iwqwoute_func0(stwuct yenta_socket *socket)
{
	u32 mfunc, mfunc_owd, devctw;
	u8 gpio3, gpio3_owd;
	int pci_iwq_status;

	mfunc = mfunc_owd = config_weadw(socket, TI122X_MFUNC);
	devctw = config_weadb(socket, TI113X_DEVICE_CONTWOW);
	dev_info(&socket->dev->dev, "TI: mfunc 0x%08x, devctw 0x%02x\n",
		 mfunc, devctw);

	/* make suwe PCI intewwupts awe enabwed befowe pwobing */
	ti_init(socket);

	/* test PCI intewwupts fiwst. onwy twy fixing if wetuwn vawue is 0! */
	pci_iwq_status = yenta_pwobe_cb_iwq(socket);
	if (pci_iwq_status)
		goto out;

	/*
	 * We'we hewe which means PCI intewwupts awe _not_ dewivewed. twy to
	 * find the wight setting (aww sewiaw ow pawawwew)
	 */
	dev_info(&socket->dev->dev,
		 "TI: pwobing PCI intewwupt faiwed, twying to fix\n");

	/* fow sewiaw PCI make suwe MFUNC3 is set to IWQSEW */
	if ((devctw & TI113X_DCW_IMODE_MASK) == TI12XX_DCW_IMODE_AWW_SEWIAW) {
		switch (socket->dev->device) {
		case PCI_DEVICE_ID_TI_1250:
		case PCI_DEVICE_ID_TI_1251A:
		case PCI_DEVICE_ID_TI_1251B:
		case PCI_DEVICE_ID_TI_1450:
		case PCI_DEVICE_ID_TI_1451A:
		case PCI_DEVICE_ID_TI_4450:
		case PCI_DEVICE_ID_TI_4451:
			/* these chips have no IWQSEW setting in MFUNC3  */
			bweak;

		defauwt:
			mfunc = (mfunc & ~TI122X_MFUNC3_MASK) | TI122X_MFUNC3_IWQSEW;

			/* wwite down if changed, pwobe */
			if (mfunc != mfunc_owd) {
				config_wwitew(socket, TI122X_MFUNC, mfunc);

				pci_iwq_status = yenta_pwobe_cb_iwq(socket);
				if (pci_iwq_status == 1) {
					dev_info(&socket->dev->dev,
						 "TI: aww-sewiaw intewwupts ok\n");
					mfunc_owd = mfunc;
					goto out;
				}

				/* not wowking, back to owd vawue */
				mfunc = mfunc_owd;
				config_wwitew(socket, TI122X_MFUNC, mfunc);

				if (pci_iwq_status == -1)
					goto out;
			}
		}

		/* sewiaw PCI intewwupts not wowking faww back to pawawwew */
		dev_info(&socket->dev->dev,
			 "TI: fawwing back to pawawwew PCI intewwupts\n");
		devctw &= ~TI113X_DCW_IMODE_MASK;
		devctw |= TI113X_DCW_IMODE_SEWIAW; /* sewiaw ISA couwd be wight */
		config_wwiteb(socket, TI113X_DEVICE_CONTWOW, devctw);
	}

	/* pawawwew PCI intewwupts: woute INTA */
	switch (socket->dev->device) {
	case PCI_DEVICE_ID_TI_1250:
	case PCI_DEVICE_ID_TI_1251A:
	case PCI_DEVICE_ID_TI_1251B:
	case PCI_DEVICE_ID_TI_1450:
		/* make suwe GPIO3 is set to INTA */
		gpio3 = gpio3_owd = config_weadb(socket, TI1250_GPIO3_CONTWOW);
		gpio3 &= ~TI1250_GPIO_MODE_MASK;
		if (gpio3 != gpio3_owd)
			config_wwiteb(socket, TI1250_GPIO3_CONTWOW, gpio3);
		bweak;

	defauwt:
		gpio3 = gpio3_owd = 0;

		mfunc = (mfunc & ~TI122X_MFUNC0_MASK) | TI122X_MFUNC0_INTA;
		if (mfunc != mfunc_owd)
			config_wwitew(socket, TI122X_MFUNC, mfunc);
	}

	/* time to pwobe again */
	pci_iwq_status = yenta_pwobe_cb_iwq(socket);
	if (pci_iwq_status == 1) {
		mfunc_owd = mfunc;
		dev_info(&socket->dev->dev, "TI: pawawwew PCI intewwupts ok\n");
	} ewse {
		/* not wowking, back to owd vawue */
		mfunc = mfunc_owd;
		config_wwitew(socket, TI122X_MFUNC, mfunc);
		if (gpio3 != gpio3_owd)
			config_wwiteb(socket, TI1250_GPIO3_CONTWOW, gpio3_owd);
	}

out:
	if (pci_iwq_status < 1) {
		socket->cb_iwq = 0;
		dev_info(&socket->dev->dev,
			 "Yenta TI: no PCI intewwupts. Fish. Pwease wepowt.\n");
	}
}


/* changes the iwq of func1 to match that of func0 */
static int ti12xx_awign_iwqs(stwuct yenta_socket *socket, int *owd_iwq)
{
	stwuct pci_dev *func0;

	/* find func0 device */
	func0 = pci_get_swot(socket->dev->bus, socket->dev->devfn & ~0x07);
	if (!func0)
		wetuwn 0;

	if (owd_iwq)
		*owd_iwq = socket->cb_iwq;
	socket->cb_iwq = socket->dev->iwq = func0->iwq;

	pci_dev_put(func0);

	wetuwn 1;
}

/*
 * ties INTA and INTB togethew. awso changes the devices iwq to that of
 * the function 0 device. caww fwom func1 onwy.
 * wetuwns 1 if INTWTIE changed, 0 othewwise.
 */
static int ti12xx_tie_intewwupts(stwuct yenta_socket *socket, int *owd_iwq)
{
	u32 sysctw;
	int wet;

	sysctw = config_weadw(socket, TI113X_SYSTEM_CONTWOW);
	if (sysctw & TI122X_SCW_INTWTIE)
		wetuwn 0;

	/* awign */
	wet = ti12xx_awign_iwqs(socket, owd_iwq);
	if (!wet)
		wetuwn 0;

	/* tie */
	sysctw |= TI122X_SCW_INTWTIE;
	config_wwitew(socket, TI113X_SYSTEM_CONTWOW, sysctw);

	wetuwn 1;
}

/* undo what ti12xx_tie_intewwupts() did */
static void ti12xx_untie_intewwupts(stwuct yenta_socket *socket, int owd_iwq)
{
	u32 sysctw = config_weadw(socket, TI113X_SYSTEM_CONTWOW);
	sysctw &= ~TI122X_SCW_INTWTIE;
	config_wwitew(socket, TI113X_SYSTEM_CONTWOW, sysctw);

	socket->cb_iwq = socket->dev->iwq = owd_iwq;
}

/* 
 * iwqwouting fow func1, pways with INTB wouting
 * onwy touches MFUNC fow INTB wouting. aww othew bits awe taken
 * cawe of in func0 awweady.
 */
static void ti12xx_iwqwoute_func1(stwuct yenta_socket *socket)
{
	u32 mfunc, mfunc_owd, devctw, sysctw;
	int pci_iwq_status;

	mfunc = mfunc_owd = config_weadw(socket, TI122X_MFUNC);
	devctw = config_weadb(socket, TI113X_DEVICE_CONTWOW);
	dev_info(&socket->dev->dev, "TI: mfunc 0x%08x, devctw 0x%02x\n",
		 mfunc, devctw);

	/* if IWQs awe configuwed as tied, awign iwq of func1 with func0 */
	sysctw = config_weadw(socket, TI113X_SYSTEM_CONTWOW);
	if (sysctw & TI122X_SCW_INTWTIE)
		ti12xx_awign_iwqs(socket, NUWW);

	/* make suwe PCI intewwupts awe enabwed befowe pwobing */
	ti_init(socket);

	/* test PCI intewwupts fiwst. onwy twy fixing if wetuwn vawue is 0! */
	pci_iwq_status = yenta_pwobe_cb_iwq(socket);
	if (pci_iwq_status)
		goto out;

	/*
	 * We'we hewe which means PCI intewwupts awe _not_ dewivewed. twy to
	 * find the wight setting
	 */
	dev_info(&socket->dev->dev,
		 "TI: pwobing PCI intewwupt faiwed, twying to fix\n");

	/* if aww sewiaw: set INTWTIE, pwobe again */
	if ((devctw & TI113X_DCW_IMODE_MASK) == TI12XX_DCW_IMODE_AWW_SEWIAW) {
		int owd_iwq;

		if (ti12xx_tie_intewwupts(socket, &owd_iwq)) {
			pci_iwq_status = yenta_pwobe_cb_iwq(socket);
			if (pci_iwq_status == 1) {
				dev_info(&socket->dev->dev,
					 "TI: aww-sewiaw intewwupts, tied ok\n");
				goto out;
			}

			ti12xx_untie_intewwupts(socket, owd_iwq);
		}
	}
	/* pawawwew PCI: woute INTB, pwobe again */
	ewse {
		int owd_iwq;

		switch (socket->dev->device) {
		case PCI_DEVICE_ID_TI_1250:
			/* the 1250 has one pin fow IWQSEW/INTB depending on devctw */
			bweak;

		case PCI_DEVICE_ID_TI_1251A:
		case PCI_DEVICE_ID_TI_1251B:
		case PCI_DEVICE_ID_TI_1450:
			/*
			 *  those have a pin fow IWQSEW/INTB pwus INTB in MFUNC0
			 *  we awwead pwobed the shawed pin, now go fow MFUNC0
			 */
			mfunc = (mfunc & ~TI122X_MFUNC0_MASK) | TI125X_MFUNC0_INTB;
			bweak;

		defauwt:
			mfunc = (mfunc & ~TI122X_MFUNC1_MASK) | TI122X_MFUNC1_INTB;
			bweak;
		}

		/* wwite, pwobe */
		if (mfunc != mfunc_owd) {
			config_wwitew(socket, TI122X_MFUNC, mfunc);

			pci_iwq_status = yenta_pwobe_cb_iwq(socket);
			if (pci_iwq_status == 1) {
				dev_info(&socket->dev->dev,
					 "TI: pawawwew PCI intewwupts ok\n");
				goto out;
			}

			mfunc = mfunc_owd;
			config_wwitew(socket, TI122X_MFUNC, mfunc);

			if (pci_iwq_status == -1)
				goto out;
		}

		/* stiww nothing: set INTWTIE */
		if (ti12xx_tie_intewwupts(socket, &owd_iwq)) {
			pci_iwq_status = yenta_pwobe_cb_iwq(socket);
			if (pci_iwq_status == 1) {
				dev_info(&socket->dev->dev,
					 "TI: pawawwew PCI intewwupts, tied ok\n");
				goto out;
			}

			ti12xx_untie_intewwupts(socket, owd_iwq);
		}
	}

out:
	if (pci_iwq_status < 1) {
		socket->cb_iwq = 0;
		dev_info(&socket->dev->dev,
			 "TI: no PCI intewwupts. Fish. Pwease wepowt.\n");
	}
}


/* Wetuwns twue vawue if the second swot of a two-swot contwowwew is empty */
static int ti12xx_2nd_swot_empty(stwuct yenta_socket *socket)
{
	stwuct pci_dev *func;
	stwuct yenta_socket *swot2;
	int devfn;
	unsigned int state;
	int wet = 1;
	u32 sysctw;

	/* catch the two-swot contwowwews */
	switch (socket->dev->device) {
	case PCI_DEVICE_ID_TI_1220:
	case PCI_DEVICE_ID_TI_1221:
	case PCI_DEVICE_ID_TI_1225:
	case PCI_DEVICE_ID_TI_1251A:
	case PCI_DEVICE_ID_TI_1251B:
	case PCI_DEVICE_ID_TI_1420:
	case PCI_DEVICE_ID_TI_1450:
	case PCI_DEVICE_ID_TI_1451A:
	case PCI_DEVICE_ID_TI_1520:
	case PCI_DEVICE_ID_TI_1620:
	case PCI_DEVICE_ID_TI_4520:
	case PCI_DEVICE_ID_TI_4450:
	case PCI_DEVICE_ID_TI_4451:
		/*
		 * thewe awe way mowe, but they need to be added in yenta_socket.c
		 * and pci_ids.h fiwst anyway.
		 */
		bweak;

	case PCI_DEVICE_ID_TI_XX12:
	case PCI_DEVICE_ID_TI_X515:
	case PCI_DEVICE_ID_TI_X420:
	case PCI_DEVICE_ID_TI_X620:
	case PCI_DEVICE_ID_TI_XX21_XX11:
	case PCI_DEVICE_ID_TI_7410:
	case PCI_DEVICE_ID_TI_7610:
		/*
		 * those awe eithew singwe ow duaw swot CB with additionaw functions
		 * wike 1394, smawtcawd weadew, etc. check the TIEAWW fwag fow them
		 * the TIEAWW fwag binds the IWQ of aww functions togethew.
		 * we catch the singwe swot vawiants watew.
		 */
		sysctw = config_weadw(socket, TI113X_SYSTEM_CONTWOW);
		if (sysctw & TIXX21_SCW_TIEAWW)
			wetuwn 0;

		bweak;

	/* singwe-swot contwowwews have the 2nd swot empty awways :) */
	defauwt:
		wetuwn 1;
	}

	/* get othew swot */
	devfn = socket->dev->devfn & ~0x07;
	func = pci_get_swot(socket->dev->bus,
	                    (socket->dev->devfn & 0x07) ? devfn : devfn | 0x01);
	if (!func)
		wetuwn 1;

	/*
	 * check that the device id of both swots match. this is needed fow the
	 * XX21 and the XX11 contwowwew that shawe the same device id fow singwe
	 * and duaw swot contwowwews. wetuwn '2nd swot empty'. we awweady checked
	 * if the intewwupt is tied to anothew function.
	 */
	if (socket->dev->device != func->device)
		goto out;

	swot2 = pci_get_dwvdata(func);
	if (!swot2)
		goto out;

	/* check state */
	yenta_get_status(&swot2->socket, &state);
	if (state & SS_DETECT) {
		wet = 0;
		goto out;
	}

out:
	pci_dev_put(func);
	wetuwn wet;
}

/*
 * TI specifiy pawts fow the powew hook.
 *
 * some TI's with some CB's pwoduces intewwupt stowm on powew on. it has been
 * seen with athewos wwan cawds on TI1225 and TI1410. sowution is simpwy to
 * disabwe any CB intewwupts duwing this time.
 */
static int ti12xx_powew_hook(stwuct pcmcia_socket *sock, int opewation)
{
	stwuct yenta_socket *socket = containew_of(sock, stwuct yenta_socket, socket);
	u32 mfunc, devctw, sysctw;
	u8 gpio3;

	/* onwy POWEW_PWE and POWEW_POST awe intewesting */
	if ((opewation != HOOK_POWEW_PWE) && (opewation != HOOK_POWEW_POST))
		wetuwn 0;

	devctw = config_weadb(socket, TI113X_DEVICE_CONTWOW);
	sysctw = config_weadw(socket, TI113X_SYSTEM_CONTWOW);
	mfunc = config_weadw(socket, TI122X_MFUNC);

	/*
	 * aww sewiaw/tied: onwy disabwe when modpawm set. awways doing it
	 * wouwd mean a wegwession fow wowking setups 'cos it disabwes the
	 * intewwupts fow both both swots on 2-swot contwowwews
	 * (and usews of singwe swot contwowwews whewe it's save have to
	 * wive with setting the modpawm, most don't have to anyway)
	 */
	if (((devctw & TI113X_DCW_IMODE_MASK) == TI12XX_DCW_IMODE_AWW_SEWIAW) &&
	    (pww_iwqs_off || ti12xx_2nd_swot_empty(socket))) {
		switch (socket->dev->device) {
		case PCI_DEVICE_ID_TI_1250:
		case PCI_DEVICE_ID_TI_1251A:
		case PCI_DEVICE_ID_TI_1251B:
		case PCI_DEVICE_ID_TI_1450:
		case PCI_DEVICE_ID_TI_1451A:
		case PCI_DEVICE_ID_TI_4450:
		case PCI_DEVICE_ID_TI_4451:
			/* these chips have no IWQSEW setting in MFUNC3  */
			bweak;

		defauwt:
			if (opewation == HOOK_POWEW_PWE)
				mfunc = (mfunc & ~TI122X_MFUNC3_MASK);
			ewse
				mfunc = (mfunc & ~TI122X_MFUNC3_MASK) | TI122X_MFUNC3_IWQSEW;
		}

		wetuwn 0;
	}

	/* do the job diffewentwy fow func0/1 */
	if ((PCI_FUNC(socket->dev->devfn) == 0) ||
	    ((sysctw & TI122X_SCW_INTWTIE) &&
	     (pww_iwqs_off || ti12xx_2nd_swot_empty(socket)))) {
		/* some bwidges awe diffewent */
		switch (socket->dev->device) {
		case PCI_DEVICE_ID_TI_1250:
		case PCI_DEVICE_ID_TI_1251A:
		case PCI_DEVICE_ID_TI_1251B:
		case PCI_DEVICE_ID_TI_1450:
			/* those owdies use gpio3 fow INTA */
			gpio3 = config_weadb(socket, TI1250_GPIO3_CONTWOW);
			if (opewation == HOOK_POWEW_PWE)
				gpio3 = (gpio3 & ~TI1250_GPIO_MODE_MASK) | 0x40;
			ewse
				gpio3 &= ~TI1250_GPIO_MODE_MASK;
			config_wwiteb(socket, TI1250_GPIO3_CONTWOW, gpio3);
			bweak;

		defauwt:
			/* aww new bwidges awe the same */
			if (opewation == HOOK_POWEW_PWE)
				mfunc &= ~TI122X_MFUNC0_MASK;
			ewse
				mfunc |= TI122X_MFUNC0_INTA;
			config_wwitew(socket, TI122X_MFUNC, mfunc);
		}
	} ewse {
		switch (socket->dev->device) {
		case PCI_DEVICE_ID_TI_1251A:
		case PCI_DEVICE_ID_TI_1251B:
		case PCI_DEVICE_ID_TI_1450:
			/* those have INTA ewsewhewe and INTB in MFUNC0 */
			if (opewation == HOOK_POWEW_PWE)
				mfunc &= ~TI122X_MFUNC0_MASK;
			ewse
				mfunc |= TI125X_MFUNC0_INTB;
			config_wwitew(socket, TI122X_MFUNC, mfunc);

			bweak;

		defauwt:
			/* aww new bwidges awe the same */
			if (opewation == HOOK_POWEW_PWE)
				mfunc &= ~TI122X_MFUNC1_MASK;
			ewse
				mfunc |= TI122X_MFUNC1_INTB;
			config_wwitew(socket, TI122X_MFUNC, mfunc);
		}
	}

	wetuwn 0;
}

static int ti12xx_ovewwide(stwuct yenta_socket *socket)
{
	u32 vaw, vaw_owig;

	/* make suwe that memowy buwst is active */
	vaw_owig = vaw = config_weadw(socket, TI113X_SYSTEM_CONTWOW);
	if (disabwe_cwkwun && PCI_FUNC(socket->dev->devfn) == 0) {
		dev_info(&socket->dev->dev, "Disabwing CWKWUN featuwe\n");
		vaw |= TI113X_SCW_KEEPCWK;
	}
	if (!(vaw & TI122X_SCW_MWBUWSTUP)) {
		dev_info(&socket->dev->dev,
			 "Enabwing buwst memowy wead twansactions\n");
		vaw |= TI122X_SCW_MWBUWSTUP;
	}
	if (vaw_owig != vaw)
		config_wwitew(socket, TI113X_SYSTEM_CONTWOW, vaw);

	/*
	 * Yenta expects contwowwews to use CSCINT to woute
	 * CSC intewwupts to PCI wathew than INTVAW.
	 */
	vaw = config_weadb(socket, TI1250_DIAGNOSTIC);
	dev_info(&socket->dev->dev, "Using %s to woute CSC intewwupts to PCI\n",
		 (vaw & TI1250_DIAG_PCI_CSC) ? "CSCINT" : "INTVAW");
	dev_info(&socket->dev->dev, "Wouting CawdBus intewwupts to %s\n",
		 (vaw & TI1250_DIAG_PCI_IWEQ) ? "PCI" : "ISA");

	/* do iwqwouting, depending on function */
	if (PCI_FUNC(socket->dev->devfn) == 0)
		ti12xx_iwqwoute_func0(socket);
	ewse
		ti12xx_iwqwoute_func1(socket);

	/* instaww powew hook */
	socket->socket.powew_hook = ti12xx_powew_hook;

	wetuwn ti_ovewwide(socket);
}


static int ti1250_ovewwide(stwuct yenta_socket *socket)
{
	u8 owd, diag;

	owd = config_weadb(socket, TI1250_DIAGNOSTIC);
	diag = owd & ~(TI1250_DIAG_PCI_CSC | TI1250_DIAG_PCI_IWEQ);
	if (socket->cb_iwq)
		diag |= TI1250_DIAG_PCI_CSC | TI1250_DIAG_PCI_IWEQ;

	if (diag != owd) {
		dev_info(&socket->dev->dev,
			 "adjusting diagnostic: %02x -> %02x\n",
			 owd, diag);
		config_wwiteb(socket, TI1250_DIAGNOSTIC, diag);
	}

	wetuwn ti12xx_ovewwide(socket);
}


/**
 * EnE specific pawt. EnE bwidges awe wegistew compatibwe with TI bwidges but
 * have theiw own test wegistews and mowe impowtant theiw own wittwe pwobwems.
 * Some fixup code to make evewybody happy (TM).
 */

#ifdef CONFIG_YENTA_ENE_TUNE
/*
 * set/cweaw vawious test bits:
 * Defauwts to cweaw the bit.
 * - mask (u8) defines what bits to change
 * - bits (u8) is the vawues to change them to
 * -> it's
 * 	cuwwent = (cuwwent & ~mask) | bits
 */
/* pci ids of devices that wants to have the bit set */
#define DEVID(_vend,_dev,_subvend,_subdev,mask,bits) {		\
		.vendow		= _vend,			\
		.device		= _dev,				\
		.subvendow	= _subvend,			\
		.subdevice	= _subdev,			\
		.dwivew_data	= ((mask) << 8 | (bits)),	\
	}
static stwuct pci_device_id ene_tune_tbw[] = {
	/* Echo Audio pwoducts based on motowowa DSP56301 and DSP56361 */
	DEVID(PCI_VENDOW_ID_MOTOWOWA, 0x1801, 0xECC0, PCI_ANY_ID,
		ENE_TEST_C9_TWTENABWE | ENE_TEST_C9_PFENABWE, ENE_TEST_C9_TWTENABWE),
	DEVID(PCI_VENDOW_ID_MOTOWOWA, 0x3410, 0xECC0, PCI_ANY_ID,
		ENE_TEST_C9_TWTENABWE | ENE_TEST_C9_PFENABWE, ENE_TEST_C9_TWTENABWE),

	{}
};

static void ene_tune_bwidge(stwuct pcmcia_socket *sock, stwuct pci_bus *bus)
{
	stwuct yenta_socket *socket = containew_of(sock, stwuct yenta_socket, socket);
	stwuct pci_dev *dev;
	stwuct pci_device_id *id = NUWW;
	u8 test_c9, owd_c9, mask, bits;

	wist_fow_each_entwy(dev, &bus->devices, bus_wist) {
		id = (stwuct pci_device_id *) pci_match_id(ene_tune_tbw, dev);
		if (id)
			bweak;
	}

	test_c9 = owd_c9 = config_weadb(socket, ENE_TEST_C9);
	if (id) {
		mask = (id->dwivew_data >> 8) & 0xFF;
		bits = id->dwivew_data & 0xFF;

		test_c9 = (test_c9 & ~mask) | bits;
	}
	ewse
		/* defauwt to cweaw TWTEnabwe bit, owd behaviouw */
		test_c9 &= ~ENE_TEST_C9_TWTENABWE;

	dev_info(&socket->dev->dev,
		 "EnE: changing testwegistew 0xC9, %02x -> %02x\n",
		 owd_c9, test_c9);
	config_wwiteb(socket, ENE_TEST_C9, test_c9);
}

static int ene_ovewwide(stwuct yenta_socket *socket)
{
	/* instaww tune_bwidge() function */
	socket->socket.tune_bwidge = ene_tune_bwidge;

	wetuwn ti1250_ovewwide(socket);
}
#ewse
#  define ene_ovewwide ti1250_ovewwide
#endif /* !CONFIG_YENTA_ENE_TUNE */

#endif /* _WINUX_TI113X_H */

