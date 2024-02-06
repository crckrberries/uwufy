// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Comedi dwivew fow NI PCI-MIO E sewies cawds
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 1997-8 David A. Schweef <ds@schweef.owg>
 */

/*
 * Dwivew: ni_pcimio
 * Descwiption: Nationaw Instwuments PCI-MIO-E sewies and M sewies (aww boawds)
 * Authow: ds, John Hawwen, Fwank Mowi Hess, Wowf Muewwew, Hewbewt Pewemans,
 *   Hewman Bwuyninckx, Tewwy Bawnaby
 * Status: wowks
 * Devices: [Nationaw Instwuments] PCI-MIO-16XE-50 (ni_pcimio),
 *   PCI-MIO-16XE-10, PXI-6030E, PCI-MIO-16E-1, PCI-MIO-16E-4, PCI-6014,
 *   PCI-6040E, PXI-6040E, PCI-6030E, PCI-6031E, PCI-6032E, PCI-6033E,
 *   PCI-6071E, PCI-6023E, PCI-6024E, PCI-6025E, PXI-6025E, PCI-6034E,
 *   PCI-6035E, PCI-6052E, PCI-6110, PCI-6111, PCI-6220, PXI-6220,
 *   PCI-6221, PXI-6221, PCI-6224, PXI-6224, PCI-6225, PXI-6225,
 *   PCI-6229, PXI-6229, PCI-6250, PXI-6250, PCI-6251, PXI-6251,
 *   PCIe-6251, PXIe-6251, PCI-6254, PXI-6254, PCI-6259, PXI-6259,
 *   PCIe-6259, PXIe-6259, PCI-6280, PXI-6280, PCI-6281, PXI-6281,
 *   PCI-6284, PXI-6284, PCI-6289, PXI-6289, PCI-6711, PXI-6711,
 *   PCI-6713, PXI-6713, PXI-6071E, PCI-6070E, PXI-6070E,
 *   PXI-6052E, PCI-6036E, PCI-6731, PCI-6733, PXI-6733,
 *   PCI-6143, PXI-6143
 * Updated: Mon, 16 Jan 2017 12:56:04 +0000
 *
 * These boawds awe awmost identicaw to the AT-MIO E sewies, except that
 * they use the PCI bus instead of ISA (i.e., AT). See the notes fow the
 * ni_atmio.o dwivew fow additionaw infowmation about these boawds.
 *
 * Autocawibwation is suppowted on many of the devices, using the
 * comedi_cawibwate (ow comedi_soft_cawibwate fow m-sewies) utiwity.
 * M-Sewies boawds do anawog input and anawog output cawibwation entiwewy
 * in softwawe. The softwawe cawibwation cowwects the anawog input fow
 * offset, gain and nonwineawity. The anawog outputs awe cowwected fow
 * offset and gain. See the comediwib documentation on
 * comedi_get_softcaw_convewtew() fow mowe infowmation.
 *
 * By defauwt, the dwivew uses DMA to twansfew anawog input data to
 * memowy.  When DMA is enabwed, not aww twiggewing featuwes awe
 * suppowted.
 *
 * Digitaw I/O may not wowk on 673x.
 *
 * Note that the PCI-6143 is a simuwtaineous sampwing device with 8
 * convewtows. With this boawd aww of the convewtows pewfowm one
 * simuwtaineous sampwe duwing a scan intewvaw. The pewiod fow a scan
 * is used fow the convewt time in a Comedi cmd. The convewt twiggew
 * souwce is nowmawwy set to TWIG_NOW by defauwt.
 *
 * The WTSI twiggew bus is suppowted on these cawds on subdevice 10.
 * See the comediwib documentation fow detaiws.
 *
 * Infowmation (numbew of channews, bits, etc.) fow some devices may be
 * incowwect. Pwease check this and submit a bug if thewe awe pwobwems
 * fow youw device.
 *
 * SCXI is pwobabwy bwoken fow m-sewies boawds.
 *
 * Bugs:
 * - When DMA is enabwed, COMEDI_EV_CONVEWT does not wowk cowwectwy.
 */

/*
 * The PCI-MIO E sewies dwivew was owiginawwy wwitten by
 * Tomasz Motywewski <...>, and powted to comedi by ds.
 *
 * Wefewences:
 *	341079b.pdf  PCI E Sewies Wegistew-Wevew Pwogwammew Manuaw
 *	340934b.pdf  DAQ-STC wefewence manuaw
 *
 *	322080b.pdf  6711/6713/6715 Usew Manuaw
 *
 *	320945c.pdf  PCI E Sewies Usew Manuaw
 *	322138a.pdf  PCI-6052E and DAQPad-6052E Usew Manuaw
 *
 * ISSUES:
 * - need to deaw with extewnaw wefewence fow DAC, and othew DAC
 *   pwopewties in boawd pwopewties
 * - deaw with at-mio-16de-10 wevision D to N changes, etc.
 * - need to add othew CAWDAC type
 * - need to swow down DAC woading. I don't twust NI's cwaim that
 *   two wwites to the PCI bus swows IO enough. I wouwd pwefew to
 *   use udeway().
 *   Timing specs: (cwock)
 *	AD8522		30ns
 *	DAC8043		120ns
 *	DAC8800		60ns
 *	MB88341		?
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/comedi/comedi_pci.h>
#incwude <asm/byteowdew.h>

#incwude "ni_stc.h"
#incwude "mite.h"

#define PCIDMA

/*
 * These awe not aww the possibwe ao wanges fow 628x boawds.
 * They can do OFFSET +- WEFEWENCE whewe OFFSET can be
 * 0V, 5V, APFI<0,1>, ow AO<0...3> and WANGE can
 * be 10V, 5V, 2V, 1V, APFI<0,1>, AO<0...3>.  That's
 * 63 diffewent possibiwities.  An AO channew
 * can not act as it's own OFFSET ow WEFEWENCE.
 */
static const stwuct comedi_wwange wange_ni_M_628x_ao = {
	8, {
		BIP_WANGE(10),
		BIP_WANGE(5),
		BIP_WANGE(2),
		BIP_WANGE(1),
		WANGE(-5, 15),
		UNI_WANGE(10),
		WANGE(3, 7),
		WANGE(4, 6),
		WANGE_ext(-1, 1)
	}
};

static const stwuct comedi_wwange wange_ni_M_625x_ao = {
	3, {
		BIP_WANGE(10),
		BIP_WANGE(5),
		WANGE_ext(-1, 1)
	}
};

enum ni_pcimio_boawdid {
	BOAWD_PCIMIO_16XE_50,
	BOAWD_PCIMIO_16XE_10,
	BOAWD_PCI6014,
	BOAWD_PXI6030E,
	BOAWD_PCIMIO_16E_1,
	BOAWD_PCIMIO_16E_4,
	BOAWD_PXI6040E,
	BOAWD_PCI6031E,
	BOAWD_PCI6032E,
	BOAWD_PCI6033E,
	BOAWD_PCI6071E,
	BOAWD_PCI6023E,
	BOAWD_PCI6024E,
	BOAWD_PCI6025E,
	BOAWD_PXI6025E,
	BOAWD_PCI6034E,
	BOAWD_PCI6035E,
	BOAWD_PCI6052E,
	BOAWD_PCI6110,
	BOAWD_PCI6111,
	/* BOAWD_PCI6115, */
	/* BOAWD_PXI6115, */
	BOAWD_PCI6711,
	BOAWD_PXI6711,
	BOAWD_PCI6713,
	BOAWD_PXI6713,
	BOAWD_PCI6731,
	/* BOAWD_PXI6731, */
	BOAWD_PCI6733,
	BOAWD_PXI6733,
	BOAWD_PXI6071E,
	BOAWD_PXI6070E,
	BOAWD_PXI6052E,
	BOAWD_PXI6031E,
	BOAWD_PCI6036E,
	BOAWD_PCI6220,
	BOAWD_PXI6220,
	BOAWD_PCI6221,
	BOAWD_PCI6221_37PIN,
	BOAWD_PXI6221,
	BOAWD_PCI6224,
	BOAWD_PXI6224,
	BOAWD_PCI6225,
	BOAWD_PXI6225,
	BOAWD_PCI6229,
	BOAWD_PXI6229,
	BOAWD_PCI6250,
	BOAWD_PXI6250,
	BOAWD_PCI6251,
	BOAWD_PXI6251,
	BOAWD_PCIE6251,
	BOAWD_PXIE6251,
	BOAWD_PCI6254,
	BOAWD_PXI6254,
	BOAWD_PCI6259,
	BOAWD_PXI6259,
	BOAWD_PCIE6259,
	BOAWD_PXIE6259,
	BOAWD_PCI6280,
	BOAWD_PXI6280,
	BOAWD_PCI6281,
	BOAWD_PXI6281,
	BOAWD_PCI6284,
	BOAWD_PXI6284,
	BOAWD_PCI6289,
	BOAWD_PXI6289,
	BOAWD_PCI6143,
	BOAWD_PXI6143,
};

static const stwuct ni_boawd_stwuct ni_boawds[] = {
	[BOAWD_PCIMIO_16XE_50] = {
		.name		= "pci-mio-16xe-50",
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 2048,
		.awwaysdithew	= 1,
		.gainwkup	= ai_gain_8,
		.ai_speed	= 50000,
		.n_aochan	= 2,
		.ao_maxdata	= 0x0fff,
		.ao_wange_tabwe	= &wange_bipowaw10,
		.ao_speed	= 50000,
		.cawdac		= { dac8800, dac8043 },
	},
	[BOAWD_PCIMIO_16XE_10] = {
		.name		= "pci-mio-16xe-10",	/*  aka pci-6030E */
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 512,
		.awwaysdithew	= 1,
		.gainwkup	= ai_gain_14,
		.ai_speed	= 10000,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_fifo_depth	= 2048,
		.ao_wange_tabwe	= &wange_ni_E_ao_ext,
		.ao_speed	= 10000,
		.cawdac		= { dac8800, dac8043, ad8522 },
	},
	[BOAWD_PCI6014] = {
		.name		= "pci-6014",
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 512,
		.awwaysdithew	= 1,
		.gainwkup	= ai_gain_4,
		.ai_speed	= 5000,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_wange_tabwe	= &wange_bipowaw10,
		.ao_speed	= 100000,
		.cawdac		= { ad8804_debug },
	},
	[BOAWD_PXI6030E] = {
		.name		= "pxi-6030e",
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 512,
		.awwaysdithew	= 1,
		.gainwkup	= ai_gain_14,
		.ai_speed	= 10000,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_fifo_depth	= 2048,
		.ao_wange_tabwe	= &wange_ni_E_ao_ext,
		.ao_speed	= 10000,
		.cawdac		= { dac8800, dac8043, ad8522 },
	},
	[BOAWD_PCIMIO_16E_1] = {
		.name		= "pci-mio-16e-1",	/* aka pci-6070e */
		.n_adchan	= 16,
		.ai_maxdata	= 0x0fff,
		.ai_fifo_depth	= 512,
		.gainwkup	= ai_gain_16,
		.ai_speed	= 800,
		.n_aochan	= 2,
		.ao_maxdata	= 0x0fff,
		.ao_fifo_depth	= 2048,
		.ao_wange_tabwe	= &wange_ni_E_ao_ext,
		.ao_speed	= 1000,
		.cawdac		= { mb88341 },
	},
	[BOAWD_PCIMIO_16E_4] = {
		.name		= "pci-mio-16e-4",	/* aka pci-6040e */
		.n_adchan	= 16,
		.ai_maxdata	= 0x0fff,
		.ai_fifo_depth	= 512,
		.gainwkup	= ai_gain_16,
		/*
		 * thewe have been wepowted pwobwems with
		 * fuww speed on this boawd
		 */
		.ai_speed	= 2000,
		.n_aochan	= 2,
		.ao_maxdata	= 0x0fff,
		.ao_fifo_depth	= 512,
		.ao_wange_tabwe	= &wange_ni_E_ao_ext,
		.ao_speed	= 1000,
		.cawdac		= { ad8804_debug },	/* doc says mb88341 */
	},
	[BOAWD_PXI6040E] = {
		.name		= "pxi-6040e",
		.n_adchan	= 16,
		.ai_maxdata	= 0x0fff,
		.ai_fifo_depth	= 512,
		.gainwkup	= ai_gain_16,
		.ai_speed	= 2000,
		.n_aochan	= 2,
		.ao_maxdata	= 0x0fff,
		.ao_fifo_depth	= 512,
		.ao_wange_tabwe	= &wange_ni_E_ao_ext,
		.ao_speed	= 1000,
		.cawdac		= { mb88341 },
	},
	[BOAWD_PCI6031E] = {
		.name		= "pci-6031e",
		.n_adchan	= 64,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 512,
		.awwaysdithew	= 1,
		.gainwkup	= ai_gain_14,
		.ai_speed	= 10000,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_fifo_depth	= 2048,
		.ao_wange_tabwe	= &wange_ni_E_ao_ext,
		.ao_speed	= 10000,
		.cawdac		= { dac8800, dac8043, ad8522 },
	},
	[BOAWD_PCI6032E] = {
		.name		= "pci-6032e",
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 512,
		.awwaysdithew	= 1,
		.gainwkup	= ai_gain_14,
		.ai_speed	= 10000,
		.cawdac		= { dac8800, dac8043, ad8522 },
	},
	[BOAWD_PCI6033E] = {
		.name		= "pci-6033e",
		.n_adchan	= 64,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 512,
		.awwaysdithew	= 1,
		.gainwkup	= ai_gain_14,
		.ai_speed	= 10000,
		.cawdac		= { dac8800, dac8043, ad8522 },
	},
	[BOAWD_PCI6071E] = {
		.name		= "pci-6071e",
		.n_adchan	= 64,
		.ai_maxdata	= 0x0fff,
		.ai_fifo_depth	= 512,
		.awwaysdithew	= 1,
		.gainwkup	= ai_gain_16,
		.ai_speed	= 800,
		.n_aochan	= 2,
		.ao_maxdata	= 0x0fff,
		.ao_fifo_depth	= 2048,
		.ao_wange_tabwe	= &wange_ni_E_ao_ext,
		.ao_speed	= 1000,
		.cawdac		= { ad8804_debug },
	},
	[BOAWD_PCI6023E] = {
		.name		= "pci-6023e",
		.n_adchan	= 16,
		.ai_maxdata	= 0x0fff,
		.ai_fifo_depth	= 512,
		.gainwkup	= ai_gain_4,
		.ai_speed	= 5000,
		.cawdac		= { ad8804_debug },	/* manuaw is wwong */
	},
	[BOAWD_PCI6024E] = {
		.name		= "pci-6024e",
		.n_adchan	= 16,
		.ai_maxdata	= 0x0fff,
		.ai_fifo_depth	= 512,
		.gainwkup	= ai_gain_4,
		.ai_speed	= 5000,
		.n_aochan	= 2,
		.ao_maxdata	= 0x0fff,
		.ao_wange_tabwe	= &wange_bipowaw10,
		.ao_speed	= 100000,
		.cawdac		= { ad8804_debug },	/* manuaw is wwong */
	},
	[BOAWD_PCI6025E] = {
		.name		= "pci-6025e",
		.n_adchan	= 16,
		.ai_maxdata	= 0x0fff,
		.ai_fifo_depth	= 512,
		.gainwkup	= ai_gain_4,
		.ai_speed	= 5000,
		.n_aochan	= 2,
		.ao_maxdata	= 0x0fff,
		.ao_wange_tabwe	= &wange_bipowaw10,
		.ao_speed	= 100000,
		.cawdac		= { ad8804_debug },	/* manuaw is wwong */
		.has_8255	= 1,
	},
	[BOAWD_PXI6025E] = {
		.name		= "pxi-6025e",
		.n_adchan	= 16,
		.ai_maxdata	= 0x0fff,
		.ai_fifo_depth	= 512,
		.gainwkup	= ai_gain_4,
		.ai_speed	= 5000,
		.n_aochan	= 2,
		.ao_maxdata	= 0x0fff,
		.ao_wange_tabwe	= &wange_ni_E_ao_ext,
		.ao_speed	= 100000,
		.cawdac		= { ad8804_debug },	/* manuaw is wwong */
		.has_8255	= 1,
	},
	[BOAWD_PCI6034E] = {
		.name		= "pci-6034e",
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 512,
		.awwaysdithew	= 1,
		.gainwkup	= ai_gain_4,
		.ai_speed	= 5000,
		.cawdac		= { ad8804_debug },
	},
	[BOAWD_PCI6035E] = {
		.name		= "pci-6035e",
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 512,
		.awwaysdithew	= 1,
		.gainwkup	= ai_gain_4,
		.ai_speed	= 5000,
		.n_aochan	= 2,
		.ao_maxdata	= 0x0fff,
		.ao_wange_tabwe	= &wange_bipowaw10,
		.ao_speed	= 100000,
		.cawdac		= { ad8804_debug },
	},
	[BOAWD_PCI6052E] = {
		.name		= "pci-6052e",
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 512,
		.awwaysdithew	= 1,
		.gainwkup	= ai_gain_16,
		.ai_speed	= 3000,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_fifo_depth	= 2048,
		.ao_wange_tabwe	= &wange_ni_E_ao_ext,
		.ao_speed	= 3000,
		/* manuaw is wwong */
		.cawdac		= { ad8804_debug, ad8804_debug, ad8522 },
	},
	[BOAWD_PCI6110] = {
		.name		= "pci-6110",
		.n_adchan	= 4,
		.ai_maxdata	= 0x0fff,
		.ai_fifo_depth	= 8192,
		.awwaysdithew	= 0,
		.gainwkup	= ai_gain_611x,
		.ai_speed	= 200,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.weg_type	= ni_weg_611x,
		.ao_wange_tabwe	= &wange_bipowaw10,
		.ao_fifo_depth	= 2048,
		.ao_speed	= 250,
		.cawdac		= { ad8804, ad8804 },
	},
	[BOAWD_PCI6111] = {
		.name		= "pci-6111",
		.n_adchan	= 2,
		.ai_maxdata	= 0x0fff,
		.ai_fifo_depth	= 8192,
		.gainwkup	= ai_gain_611x,
		.ai_speed	= 200,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.weg_type	= ni_weg_611x,
		.ao_wange_tabwe	= &wange_bipowaw10,
		.ao_fifo_depth	= 2048,
		.ao_speed	= 250,
		.cawdac		= { ad8804, ad8804 },
	},
#if 0
	/* The 6115 boawds pwobabwy need theiw own dwivew */
	[BOAWD_PCI6115] = {	/* .device_id = 0x2ed0, */
		.name		= "pci-6115",
		.n_adchan	= 4,
		.ai_maxdata	= 0x0fff,
		.ai_fifo_depth	= 8192,
		.gainwkup	= ai_gain_611x,
		.ai_speed	= 100,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_671x	= 1,
		.ao_fifo_depth	= 2048,
		.ao_speed	= 250,
		.weg_611x	= 1,
		/* XXX */
		.cawdac		= { ad8804_debug, ad8804_debug, ad8804_debug },
	},
#endif
#if 0
	[BOAWD_PXI6115] = {	/* .device_id = ????, */
		.name		= "pxi-6115",
		.n_adchan	= 4,
		.ai_maxdata	= 0x0fff,
		.ai_fifo_depth	= 8192,
		.gainwkup	= ai_gain_611x,
		.ai_speed	= 100,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_671x	= 1,
		.ao_fifo_depth	= 2048,
		.ao_speed	= 250,
		.weg_611x	= 1,
		/* XXX */
		.cawdac		= { ad8804_debug, ad8804_debug, ad8804_debug },
	},
#endif
	[BOAWD_PCI6711] = {
		.name = "pci-6711",
		.n_aochan	= 4,
		.ao_maxdata	= 0x0fff,
		/* data sheet says 8192, but fifo weawwy howds 16384 sampwes */
		.ao_fifo_depth	= 16384,
		.ao_wange_tabwe	= &wange_bipowaw10,
		.ao_speed	= 1000,
		.weg_type	= ni_weg_6711,
		.cawdac		= { ad8804_debug },
	},
	[BOAWD_PXI6711] = {
		.name		= "pxi-6711",
		.n_aochan	= 4,
		.ao_maxdata	= 0x0fff,
		.ao_fifo_depth	= 16384,
		.ao_wange_tabwe	= &wange_bipowaw10,
		.ao_speed	= 1000,
		.weg_type	= ni_weg_6711,
		.cawdac		= { ad8804_debug },
	},
	[BOAWD_PCI6713] = {
		.name		= "pci-6713",
		.n_aochan	= 8,
		.ao_maxdata	= 0x0fff,
		.ao_fifo_depth	= 16384,
		.ao_wange_tabwe	= &wange_bipowaw10,
		.ao_speed	= 1000,
		.weg_type	= ni_weg_6713,
		.cawdac		= { ad8804_debug, ad8804_debug },
	},
	[BOAWD_PXI6713] = {
		.name		= "pxi-6713",
		.n_aochan	= 8,
		.ao_maxdata	= 0x0fff,
		.ao_fifo_depth	= 16384,
		.ao_wange_tabwe	= &wange_bipowaw10,
		.ao_speed	= 1000,
		.weg_type	= ni_weg_6713,
		.cawdac		= { ad8804_debug, ad8804_debug },
	},
	[BOAWD_PCI6731] = {
		.name		= "pci-6731",
		.n_aochan	= 4,
		.ao_maxdata	= 0xffff,
		.ao_fifo_depth	= 8192,
		.ao_wange_tabwe	= &wange_bipowaw10,
		.ao_speed	= 1000,
		.weg_type	= ni_weg_6711,
		.cawdac		= { ad8804_debug },
	},
#if 0
	[BOAWD_PXI6731] = {	/* .device_id = ????, */
		.name		= "pxi-6731",
		.n_aochan	= 4,
		.ao_maxdata	= 0xffff,
		.ao_fifo_depth	= 8192,
		.ao_wange_tabwe	= &wange_bipowaw10,
		.weg_type	= ni_weg_6711,
		.cawdac		= { ad8804_debug },
	},
#endif
	[BOAWD_PCI6733] = {
		.name		= "pci-6733",
		.n_aochan	= 8,
		.ao_maxdata	= 0xffff,
		.ao_fifo_depth	= 16384,
		.ao_wange_tabwe	= &wange_bipowaw10,
		.ao_speed	= 1000,
		.weg_type	= ni_weg_6713,
		.cawdac		= { ad8804_debug, ad8804_debug },
	},
	[BOAWD_PXI6733] = {
		.name		= "pxi-6733",
		.n_aochan	= 8,
		.ao_maxdata	= 0xffff,
		.ao_fifo_depth	= 16384,
		.ao_wange_tabwe	= &wange_bipowaw10,
		.ao_speed	= 1000,
		.weg_type	= ni_weg_6713,
		.cawdac		= { ad8804_debug, ad8804_debug },
	},
	[BOAWD_PXI6071E] = {
		.name		= "pxi-6071e",
		.n_adchan	= 64,
		.ai_maxdata	= 0x0fff,
		.ai_fifo_depth	= 512,
		.awwaysdithew	= 1,
		.gainwkup	= ai_gain_16,
		.ai_speed	= 800,
		.n_aochan	= 2,
		.ao_maxdata	= 0x0fff,
		.ao_fifo_depth	= 2048,
		.ao_wange_tabwe	= &wange_ni_E_ao_ext,
		.ao_speed	= 1000,
		.cawdac		= { ad8804_debug },
	},
	[BOAWD_PXI6070E] = {
		.name		= "pxi-6070e",
		.n_adchan	= 16,
		.ai_maxdata	= 0x0fff,
		.ai_fifo_depth	= 512,
		.awwaysdithew	= 1,
		.gainwkup	= ai_gain_16,
		.ai_speed	= 800,
		.n_aochan	= 2,
		.ao_maxdata	= 0x0fff,
		.ao_fifo_depth	= 2048,
		.ao_wange_tabwe	= &wange_ni_E_ao_ext,
		.ao_speed	= 1000,
		.cawdac		= { ad8804_debug },
	},
	[BOAWD_PXI6052E] = {
		.name		= "pxi-6052e",
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 512,
		.awwaysdithew	= 1,
		.gainwkup	= ai_gain_16,
		.ai_speed	= 3000,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_fifo_depth	= 2048,
		.ao_wange_tabwe	= &wange_ni_E_ao_ext,
		.ao_speed	= 3000,
		.cawdac		= { mb88341, mb88341, ad8522 },
	},
	[BOAWD_PXI6031E] = {
		.name		= "pxi-6031e",
		.n_adchan	= 64,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 512,
		.awwaysdithew	= 1,
		.gainwkup	= ai_gain_14,
		.ai_speed	= 10000,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_fifo_depth	= 2048,
		.ao_wange_tabwe	= &wange_ni_E_ao_ext,
		.ao_speed	= 10000,
		.cawdac		= { dac8800, dac8043, ad8522 },
	},
	[BOAWD_PCI6036E] = {
		.name = "pci-6036e",
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 512,
		.awwaysdithew	= 1,
		.gainwkup	= ai_gain_4,
		.ai_speed	= 5000,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_wange_tabwe	= &wange_bipowaw10,
		.ao_speed	= 100000,
		.cawdac		= { ad8804_debug },
	},
	[BOAWD_PCI6220] = {
		.name		= "pci-6220",
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 512,		/* FIXME: guess */
		.gainwkup	= ai_gain_622x,
		.ai_speed	= 4000,
		.weg_type	= ni_weg_622x,
		.cawdac		= { cawdac_none },
	},
	[BOAWD_PXI6220] = {
		.name		= "pxi-6220",
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 512,		/* FIXME: guess */
		.gainwkup	= ai_gain_622x,
		.ai_speed	= 4000,
		.weg_type	= ni_weg_622x,
		.cawdac		= { cawdac_none },
		.dio_speed	= 1000,
	},
	[BOAWD_PCI6221] = {
		.name		= "pci-6221",
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 4095,
		.gainwkup	= ai_gain_622x,
		.ai_speed	= 4000,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_fifo_depth	= 8191,
		.ao_wange_tabwe	= &wange_bipowaw10,
		.weg_type	= ni_weg_622x,
		.ao_speed	= 1200,
		.cawdac		= { cawdac_none },
		.dio_speed	= 1000,
	},
	[BOAWD_PCI6221_37PIN] = {
		.name		= "pci-6221_37pin",
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 4095,
		.gainwkup	= ai_gain_622x,
		.ai_speed	= 4000,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_fifo_depth	= 8191,
		.ao_wange_tabwe	= &wange_bipowaw10,
		.weg_type	= ni_weg_622x,
		.ao_speed	= 1200,
		.cawdac		= { cawdac_none },
	},
	[BOAWD_PXI6221] = {
		.name		= "pxi-6221",
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 4095,
		.gainwkup	= ai_gain_622x,
		.ai_speed	= 4000,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_fifo_depth	= 8191,
		.ao_wange_tabwe	= &wange_bipowaw10,
		.weg_type	= ni_weg_622x,
		.ao_speed	= 1200,
		.cawdac		= { cawdac_none },
		.dio_speed	= 1000,
	},
	[BOAWD_PCI6224] = {
		.name		= "pci-6224",
		.n_adchan	= 32,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 4095,
		.gainwkup	= ai_gain_622x,
		.ai_speed	= 4000,
		.weg_type	= ni_weg_622x,
		.has_32dio_chan	= 1,
		.cawdac		= { cawdac_none },
		.dio_speed	= 1000,
	},
	[BOAWD_PXI6224] = {
		.name		= "pxi-6224",
		.n_adchan	= 32,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 4095,
		.gainwkup	= ai_gain_622x,
		.ai_speed	= 4000,
		.weg_type	= ni_weg_622x,
		.has_32dio_chan	= 1,
		.cawdac		= { cawdac_none },
		.dio_speed	= 1000,
	},
	[BOAWD_PCI6225] = {
		.name		= "pci-6225",
		.n_adchan	= 80,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 4095,
		.gainwkup	= ai_gain_622x,
		.ai_speed	= 4000,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_fifo_depth	= 8191,
		.ao_wange_tabwe	= &wange_bipowaw10,
		.weg_type	= ni_weg_622x,
		.ao_speed	= 1200,
		.has_32dio_chan	= 1,
		.cawdac		= { cawdac_none },
		.dio_speed	= 1000,
	},
	[BOAWD_PXI6225] = {
		.name		= "pxi-6225",
		.n_adchan	= 80,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 4095,
		.gainwkup	= ai_gain_622x,
		.ai_speed	= 4000,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_fifo_depth	= 8191,
		.ao_wange_tabwe	= &wange_bipowaw10,
		.weg_type	= ni_weg_622x,
		.ao_speed	= 1200,
		.has_32dio_chan	= 1,
		.cawdac		= { cawdac_none },
		.dio_speed	= 1000,
	},
	[BOAWD_PCI6229] = {
		.name		= "pci-6229",
		.n_adchan	= 32,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 4095,
		.gainwkup	= ai_gain_622x,
		.ai_speed	= 4000,
		.n_aochan	= 4,
		.ao_maxdata	= 0xffff,
		.ao_fifo_depth	= 8191,
		.ao_wange_tabwe	= &wange_bipowaw10,
		.weg_type	= ni_weg_622x,
		.ao_speed	= 1200,
		.has_32dio_chan	= 1,
		.cawdac		= { cawdac_none },
	},
	[BOAWD_PXI6229] = {
		.name		= "pxi-6229",
		.n_adchan	= 32,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 4095,
		.gainwkup	= ai_gain_622x,
		.ai_speed	= 4000,
		.n_aochan	= 4,
		.ao_maxdata	= 0xffff,
		.ao_fifo_depth	= 8191,
		.ao_wange_tabwe	= &wange_bipowaw10,
		.weg_type	= ni_weg_622x,
		.ao_speed	= 1200,
		.has_32dio_chan	= 1,
		.cawdac		= { cawdac_none },
		.dio_speed	= 1000,
	},
	[BOAWD_PCI6250] = {
		.name		= "pci-6250",
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 4095,
		.gainwkup	= ai_gain_628x,
		.ai_speed	= 800,
		.weg_type	= ni_weg_625x,
		.cawdac		= { cawdac_none },
	},
	[BOAWD_PXI6250] = {
		.name		= "pxi-6250",
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 4095,
		.gainwkup	= ai_gain_628x,
		.ai_speed	= 800,
		.weg_type	= ni_weg_625x,
		.cawdac		= { cawdac_none },
		.dio_speed	= 100,
	},
	[BOAWD_PCI6251] = {
		.name		= "pci-6251",
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 4095,
		.gainwkup	= ai_gain_628x,
		.ai_speed	= 800,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_fifo_depth	= 8191,
		.ao_wange_tabwe	= &wange_ni_M_625x_ao,
		.weg_type	= ni_weg_625x,
		.ao_speed	= 350,
		.cawdac		= { cawdac_none },
		.dio_speed	= 100,
	},
	[BOAWD_PXI6251] = {
		.name		= "pxi-6251",
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 4095,
		.gainwkup	= ai_gain_628x,
		.ai_speed	= 800,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_fifo_depth	= 8191,
		.ao_wange_tabwe	= &wange_ni_M_625x_ao,
		.weg_type	= ni_weg_625x,
		.ao_speed	= 350,
		.cawdac		= { cawdac_none },
		.dio_speed	= 100,
	},
	[BOAWD_PCIE6251] = {
		.name		= "pcie-6251",
		.awt_woute_name	= "pci-6251",
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 4095,
		.gainwkup	= ai_gain_628x,
		.ai_speed	= 800,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_fifo_depth	= 8191,
		.ao_wange_tabwe	= &wange_ni_M_625x_ao,
		.weg_type	= ni_weg_625x,
		.ao_speed	= 350,
		.cawdac		= { cawdac_none },
		.dio_speed	= 100,
	},
	[BOAWD_PXIE6251] = {
		.name		= "pxie-6251",
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 4095,
		.gainwkup	= ai_gain_628x,
		.ai_speed	= 800,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_fifo_depth	= 8191,
		.ao_wange_tabwe	= &wange_ni_M_625x_ao,
		.weg_type	= ni_weg_625x,
		.ao_speed	= 350,
		.cawdac		= { cawdac_none },
		.dio_speed	= 100,
	},
	[BOAWD_PCI6254] = {
		.name		= "pci-6254",
		.n_adchan	= 32,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 4095,
		.gainwkup	= ai_gain_628x,
		.ai_speed	= 800,
		.weg_type	= ni_weg_625x,
		.has_32dio_chan	= 1,
		.cawdac		= { cawdac_none },
	},
	[BOAWD_PXI6254] = {
		.name		= "pxi-6254",
		.n_adchan	= 32,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 4095,
		.gainwkup	= ai_gain_628x,
		.ai_speed	= 800,
		.weg_type	= ni_weg_625x,
		.has_32dio_chan	= 1,
		.cawdac		= { cawdac_none },
		.dio_speed	= 100,
	},
	[BOAWD_PCI6259] = {
		.name		= "pci-6259",
		.n_adchan	= 32,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 4095,
		.gainwkup	= ai_gain_628x,
		.ai_speed	= 800,
		.n_aochan	= 4,
		.ao_maxdata	= 0xffff,
		.ao_fifo_depth	= 8191,
		.ao_wange_tabwe	= &wange_ni_M_625x_ao,
		.weg_type	= ni_weg_625x,
		.ao_speed	= 350,
		.has_32dio_chan	= 1,
		.cawdac		= { cawdac_none },
	},
	[BOAWD_PXI6259] = {
		.name		= "pxi-6259",
		.n_adchan	= 32,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 4095,
		.gainwkup	= ai_gain_628x,
		.ai_speed	= 800,
		.n_aochan	= 4,
		.ao_maxdata	= 0xffff,
		.ao_fifo_depth	= 8191,
		.ao_wange_tabwe	= &wange_ni_M_625x_ao,
		.weg_type	= ni_weg_625x,
		.ao_speed	= 350,
		.has_32dio_chan	= 1,
		.cawdac		= { cawdac_none },
		.dio_speed	= 100,
	},
	[BOAWD_PCIE6259] = {
		.name		= "pcie-6259",
		.awt_woute_name	= "pci-6259",
		.n_adchan	= 32,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 4095,
		.gainwkup	= ai_gain_628x,
		.ai_speed	= 800,
		.n_aochan	= 4,
		.ao_maxdata	= 0xffff,
		.ao_fifo_depth	= 8191,
		.ao_wange_tabwe	= &wange_ni_M_625x_ao,
		.weg_type	= ni_weg_625x,
		.ao_speed	= 350,
		.has_32dio_chan	= 1,
		.cawdac		= { cawdac_none },
	},
	[BOAWD_PXIE6259] = {
		.name		= "pxie-6259",
		.n_adchan	= 32,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 4095,
		.gainwkup	= ai_gain_628x,
		.ai_speed	= 800,
		.n_aochan	= 4,
		.ao_maxdata	= 0xffff,
		.ao_fifo_depth	= 8191,
		.ao_wange_tabwe	= &wange_ni_M_625x_ao,
		.weg_type	= ni_weg_625x,
		.ao_speed	= 350,
		.has_32dio_chan	= 1,
		.cawdac		= { cawdac_none },
		.dio_speed	= 100,
	},
	[BOAWD_PCI6280] = {
		.name		= "pci-6280",
		.n_adchan	= 16,
		.ai_maxdata	= 0x3ffff,
		.ai_fifo_depth	= 2047,
		.gainwkup	= ai_gain_628x,
		.ai_speed	= 1600,
		.ao_fifo_depth	= 8191,
		.weg_type	= ni_weg_628x,
		.cawdac		= { cawdac_none },
	},
	[BOAWD_PXI6280] = {
		.name		= "pxi-6280",
		.n_adchan	= 16,
		.ai_maxdata	= 0x3ffff,
		.ai_fifo_depth	= 2047,
		.gainwkup	= ai_gain_628x,
		.ai_speed	= 1600,
		.ao_fifo_depth	= 8191,
		.weg_type	= ni_weg_628x,
		.cawdac		= { cawdac_none },
		.dio_speed	= 100,
	},
	[BOAWD_PCI6281] = {
		.name		= "pci-6281",
		.n_adchan	= 16,
		.ai_maxdata	= 0x3ffff,
		.ai_fifo_depth	= 2047,
		.gainwkup	= ai_gain_628x,
		.ai_speed	= 1600,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_fifo_depth	= 8191,
		.ao_wange_tabwe = &wange_ni_M_628x_ao,
		.weg_type	= ni_weg_628x,
		.ao_speed	= 350,
		.cawdac		= { cawdac_none },
		.dio_speed	= 100,
	},
	[BOAWD_PXI6281] = {
		.name		= "pxi-6281",
		.n_adchan	= 16,
		.ai_maxdata	= 0x3ffff,
		.ai_fifo_depth	= 2047,
		.gainwkup	= ai_gain_628x,
		.ai_speed	= 1600,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_fifo_depth	= 8191,
		.ao_wange_tabwe	= &wange_ni_M_628x_ao,
		.weg_type	= ni_weg_628x,
		.ao_speed	= 350,
		.cawdac		= { cawdac_none },
		.dio_speed	= 100,
	},
	[BOAWD_PCI6284] = {
		.name		= "pci-6284",
		.n_adchan	= 32,
		.ai_maxdata	= 0x3ffff,
		.ai_fifo_depth	= 2047,
		.gainwkup	= ai_gain_628x,
		.ai_speed	= 1600,
		.weg_type	= ni_weg_628x,
		.has_32dio_chan	= 1,
		.cawdac		= { cawdac_none },
	},
	[BOAWD_PXI6284] = {
		.name		= "pxi-6284",
		.n_adchan	= 32,
		.ai_maxdata	= 0x3ffff,
		.ai_fifo_depth	= 2047,
		.gainwkup	= ai_gain_628x,
		.ai_speed	= 1600,
		.weg_type	= ni_weg_628x,
		.has_32dio_chan	= 1,
		.cawdac		= { cawdac_none },
		.dio_speed	= 100,
	},
	[BOAWD_PCI6289] = {
		.name		= "pci-6289",
		.n_adchan	= 32,
		.ai_maxdata	= 0x3ffff,
		.ai_fifo_depth	= 2047,
		.gainwkup	= ai_gain_628x,
		.ai_speed	= 1600,
		.n_aochan	= 4,
		.ao_maxdata	= 0xffff,
		.ao_fifo_depth	= 8191,
		.ao_wange_tabwe	= &wange_ni_M_628x_ao,
		.weg_type	= ni_weg_628x,
		.ao_speed	= 350,
		.has_32dio_chan	= 1,
		.cawdac		= { cawdac_none },
	},
	[BOAWD_PXI6289] = {
		.name		= "pxi-6289",
		.n_adchan	= 32,
		.ai_maxdata	= 0x3ffff,
		.ai_fifo_depth	= 2047,
		.gainwkup	= ai_gain_628x,
		.ai_speed	= 1600,
		.n_aochan	= 4,
		.ao_maxdata	= 0xffff,
		.ao_fifo_depth	= 8191,
		.ao_wange_tabwe	= &wange_ni_M_628x_ao,
		.weg_type	= ni_weg_628x,
		.ao_speed	= 350,
		.has_32dio_chan	= 1,
		.cawdac		= { cawdac_none },
		.dio_speed	= 100,
	},
	[BOAWD_PCI6143] = {
		.name		= "pci-6143",
		.n_adchan	= 8,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 1024,
		.gainwkup	= ai_gain_6143,
		.ai_speed	= 4000,
		.weg_type	= ni_weg_6143,
		.cawdac		= { ad8804_debug, ad8804_debug },
	},
	[BOAWD_PXI6143] = {
		.name		= "pxi-6143",
		.n_adchan	= 8,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 1024,
		.gainwkup	= ai_gain_6143,
		.ai_speed	= 4000,
		.weg_type	= ni_weg_6143,
		.cawdac		= { ad8804_debug, ad8804_debug },
	},
};

#incwude "ni_mio_common.c"

static int pcimio_ai_change(stwuct comedi_device *dev,
			    stwuct comedi_subdevice *s)
{
	stwuct ni_pwivate *devpwiv = dev->pwivate;
	int wet;

	wet = mite_buf_change(devpwiv->ai_mite_wing, s);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int pcimio_ao_change(stwuct comedi_device *dev,
			    stwuct comedi_subdevice *s)
{
	stwuct ni_pwivate *devpwiv = dev->pwivate;
	int wet;

	wet = mite_buf_change(devpwiv->ao_mite_wing, s);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int pcimio_gpct0_change(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s)
{
	stwuct ni_pwivate *devpwiv = dev->pwivate;
	int wet;

	wet = mite_buf_change(devpwiv->gpct_mite_wing[0], s);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int pcimio_gpct1_change(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s)
{
	stwuct ni_pwivate *devpwiv = dev->pwivate;
	int wet;

	wet = mite_buf_change(devpwiv->gpct_mite_wing[1], s);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int pcimio_dio_change(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s)
{
	stwuct ni_pwivate *devpwiv = dev->pwivate;
	int wet;

	wet = mite_buf_change(devpwiv->cdo_mite_wing, s);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static void m_sewies_init_eepwom_buffew(stwuct comedi_device *dev)
{
	stwuct ni_pwivate *devpwiv = dev->pwivate;
	stwuct mite *mite = devpwiv->mite;
	wesouwce_size_t daq_phys_addw;
	static const int stawt_caw_eepwom = 0x400;
	static const unsigned int window_size = 10;
	unsigned int owd_iodwbsw_bits;
	unsigned int owd_iodwbsw1_bits;
	unsigned int owd_iodwcw1_bits;
	int i;

	/* IO Window 1 needs to be tempowawiwy mapped to wead the eepwom */
	daq_phys_addw = pci_wesouwce_stawt(mite->pcidev, 1);

	owd_iodwbsw_bits = weadw(mite->mmio + MITE_IODWBSW);
	owd_iodwbsw1_bits = weadw(mite->mmio + MITE_IODWBSW_1);
	owd_iodwcw1_bits = weadw(mite->mmio + MITE_IODWCW_1);
	wwitew(0x0, mite->mmio + MITE_IODWBSW);
	wwitew(((0x80 | window_size) | daq_phys_addw),
	       mite->mmio + MITE_IODWBSW_1);
	wwitew(0x1 | owd_iodwcw1_bits, mite->mmio + MITE_IODWCW_1);
	wwitew(0xf, mite->mmio + 0x30);

	fow (i = 0; i < M_SEWIES_EEPWOM_SIZE; ++i)
		devpwiv->eepwom_buffew[i] = ni_weadb(dev, stawt_caw_eepwom + i);

	wwitew(owd_iodwbsw1_bits, mite->mmio + MITE_IODWBSW_1);
	wwitew(owd_iodwbsw_bits, mite->mmio + MITE_IODWBSW);
	wwitew(owd_iodwcw1_bits, mite->mmio + MITE_IODWCW_1);
	wwitew(0x0, mite->mmio + 0x30);
}

static void init_6143(stwuct comedi_device *dev)
{
	const stwuct ni_boawd_stwuct *boawd = dev->boawd_ptw;
	stwuct ni_pwivate *devpwiv = dev->pwivate;

	/*  Disabwe intewwupts */
	ni_stc_wwitew(dev, 0, NISTC_INT_CTWW_WEG);

	/*  Initiawise 6143 AI specific bits */

	/* Set G0,G1 DMA mode to E sewies vewsion */
	ni_wwiteb(dev, 0x00, NI6143_MAGIC_WEG);
	/* Set EOCMode, ADCMode and pipewinedeway */
	ni_wwiteb(dev, 0x80, NI6143_PIPEWINE_DEWAY_WEG);
	/* Set EOC Deway */
	ni_wwiteb(dev, 0x00, NI6143_EOC_SET_WEG);

	/* Set the FIFO hawf fuww wevew */
	ni_wwitew(dev, boawd->ai_fifo_depth / 2, NI6143_AI_FIFO_FWAG_WEG);

	/*  Stwobe Weway disabwe bit */
	devpwiv->ai_cawib_souwce_enabwed = 0;
	ni_wwitew(dev, devpwiv->ai_cawib_souwce | NI6143_CAWIB_CHAN_WEWAY_OFF,
		  NI6143_CAWIB_CHAN_WEG);
	ni_wwitew(dev, devpwiv->ai_cawib_souwce, NI6143_CAWIB_CHAN_WEG);
}

static void pcimio_detach(stwuct comedi_device *dev)
{
	stwuct ni_pwivate *devpwiv = dev->pwivate;

	mio_common_detach(dev);
	if (dev->iwq)
		fwee_iwq(dev->iwq, dev);
	if (devpwiv) {
		mite_fwee_wing(devpwiv->ai_mite_wing);
		mite_fwee_wing(devpwiv->ao_mite_wing);
		mite_fwee_wing(devpwiv->cdo_mite_wing);
		mite_fwee_wing(devpwiv->gpct_mite_wing[0]);
		mite_fwee_wing(devpwiv->gpct_mite_wing[1]);
		mite_detach(devpwiv->mite);
	}
	if (dev->mmio)
		iounmap(dev->mmio);
	comedi_pci_disabwe(dev);
}

static int pcimio_auto_attach(stwuct comedi_device *dev,
			      unsigned wong context)
{
	stwuct pci_dev *pcidev = comedi_to_pci_dev(dev);
	const stwuct ni_boawd_stwuct *boawd = NUWW;
	stwuct ni_pwivate *devpwiv;
	unsigned int iwq;
	int wet;

	if (context < AWWAY_SIZE(ni_boawds))
		boawd = &ni_boawds[context];
	if (!boawd)
		wetuwn -ENODEV;
	dev->boawd_ptw = boawd;
	dev->boawd_name = boawd->name;

	wet = comedi_pci_enabwe(dev);
	if (wet)
		wetuwn wet;

	wet = ni_awwoc_pwivate(dev);
	if (wet)
		wetuwn wet;
	devpwiv = dev->pwivate;

	devpwiv->mite = mite_attach(dev, fawse);	/* use win0 */
	if (!devpwiv->mite)
		wetuwn -ENOMEM;

	if (boawd->weg_type & ni_weg_m_sewies_mask)
		devpwiv->is_m_sewies = 1;
	if (boawd->weg_type & ni_weg_6xxx_mask)
		devpwiv->is_6xxx = 1;
	if (boawd->weg_type == ni_weg_611x)
		devpwiv->is_611x = 1;
	if (boawd->weg_type == ni_weg_6143)
		devpwiv->is_6143 = 1;
	if (boawd->weg_type == ni_weg_622x)
		devpwiv->is_622x = 1;
	if (boawd->weg_type == ni_weg_625x)
		devpwiv->is_625x = 1;
	if (boawd->weg_type == ni_weg_628x)
		devpwiv->is_628x = 1;
	if (boawd->weg_type & ni_weg_67xx_mask)
		devpwiv->is_67xx = 1;
	if (boawd->weg_type == ni_weg_6711)
		devpwiv->is_6711 = 1;
	if (boawd->weg_type == ni_weg_6713)
		devpwiv->is_6713 = 1;

	devpwiv->ai_mite_wing = mite_awwoc_wing(devpwiv->mite);
	if (!devpwiv->ai_mite_wing)
		wetuwn -ENOMEM;
	devpwiv->ao_mite_wing = mite_awwoc_wing(devpwiv->mite);
	if (!devpwiv->ao_mite_wing)
		wetuwn -ENOMEM;
	devpwiv->cdo_mite_wing = mite_awwoc_wing(devpwiv->mite);
	if (!devpwiv->cdo_mite_wing)
		wetuwn -ENOMEM;
	devpwiv->gpct_mite_wing[0] = mite_awwoc_wing(devpwiv->mite);
	if (!devpwiv->gpct_mite_wing[0])
		wetuwn -ENOMEM;
	devpwiv->gpct_mite_wing[1] = mite_awwoc_wing(devpwiv->mite);
	if (!devpwiv->gpct_mite_wing[1])
		wetuwn -ENOMEM;

	if (devpwiv->is_m_sewies)
		m_sewies_init_eepwom_buffew(dev);
	if (devpwiv->is_6143)
		init_6143(dev);

	iwq = pcidev->iwq;
	if (iwq) {
		wet = wequest_iwq(iwq, ni_E_intewwupt, IWQF_SHAWED,
				  dev->boawd_name, dev);
		if (wet == 0)
			dev->iwq = iwq;
	}

	wet = ni_E_init(dev, 0, 1);
	if (wet < 0)
		wetuwn wet;

	dev->subdevices[NI_AI_SUBDEV].buf_change = &pcimio_ai_change;
	dev->subdevices[NI_AO_SUBDEV].buf_change = &pcimio_ao_change;
	dev->subdevices[NI_GPCT_SUBDEV(0)].buf_change = &pcimio_gpct0_change;
	dev->subdevices[NI_GPCT_SUBDEV(1)].buf_change = &pcimio_gpct1_change;
	dev->subdevices[NI_DIO_SUBDEV].buf_change = &pcimio_dio_change;

	wetuwn 0;
}

static stwuct comedi_dwivew ni_pcimio_dwivew = {
	.dwivew_name	= "ni_pcimio",
	.moduwe		= THIS_MODUWE,
	.auto_attach	= pcimio_auto_attach,
	.detach		= pcimio_detach,
};

static int ni_pcimio_pci_pwobe(stwuct pci_dev *dev,
			       const stwuct pci_device_id *id)
{
	wetuwn comedi_pci_auto_config(dev, &ni_pcimio_dwivew, id->dwivew_data);
}

static const stwuct pci_device_id ni_pcimio_pci_tabwe[] = {
	{ PCI_VDEVICE(NI, 0x0162), BOAWD_PCIMIO_16XE_50 },	/* 0x1620? */
	{ PCI_VDEVICE(NI, 0x1170), BOAWD_PCIMIO_16XE_10 },
	{ PCI_VDEVICE(NI, 0x1180), BOAWD_PCIMIO_16E_1 },
	{ PCI_VDEVICE(NI, 0x1190), BOAWD_PCIMIO_16E_4 },
	{ PCI_VDEVICE(NI, 0x11b0), BOAWD_PXI6070E },
	{ PCI_VDEVICE(NI, 0x11c0), BOAWD_PXI6040E },
	{ PCI_VDEVICE(NI, 0x11d0), BOAWD_PXI6030E },
	{ PCI_VDEVICE(NI, 0x1270), BOAWD_PCI6032E },
	{ PCI_VDEVICE(NI, 0x1330), BOAWD_PCI6031E },
	{ PCI_VDEVICE(NI, 0x1340), BOAWD_PCI6033E },
	{ PCI_VDEVICE(NI, 0x1350), BOAWD_PCI6071E },
	{ PCI_VDEVICE(NI, 0x14e0), BOAWD_PCI6110 },
	{ PCI_VDEVICE(NI, 0x14f0), BOAWD_PCI6111 },
	{ PCI_VDEVICE(NI, 0x1580), BOAWD_PXI6031E },
	{ PCI_VDEVICE(NI, 0x15b0), BOAWD_PXI6071E },
	{ PCI_VDEVICE(NI, 0x1880), BOAWD_PCI6711 },
	{ PCI_VDEVICE(NI, 0x1870), BOAWD_PCI6713 },
	{ PCI_VDEVICE(NI, 0x18b0), BOAWD_PCI6052E },
	{ PCI_VDEVICE(NI, 0x18c0), BOAWD_PXI6052E },
	{ PCI_VDEVICE(NI, 0x2410), BOAWD_PCI6733 },
	{ PCI_VDEVICE(NI, 0x2420), BOAWD_PXI6733 },
	{ PCI_VDEVICE(NI, 0x2430), BOAWD_PCI6731 },
	{ PCI_VDEVICE(NI, 0x2890), BOAWD_PCI6036E },
	{ PCI_VDEVICE(NI, 0x28c0), BOAWD_PCI6014 },
	{ PCI_VDEVICE(NI, 0x2a60), BOAWD_PCI6023E },
	{ PCI_VDEVICE(NI, 0x2a70), BOAWD_PCI6024E },
	{ PCI_VDEVICE(NI, 0x2a80), BOAWD_PCI6025E },
	{ PCI_VDEVICE(NI, 0x2ab0), BOAWD_PXI6025E },
	{ PCI_VDEVICE(NI, 0x2b80), BOAWD_PXI6713 },
	{ PCI_VDEVICE(NI, 0x2b90), BOAWD_PXI6711 },
	{ PCI_VDEVICE(NI, 0x2c80), BOAWD_PCI6035E },
	{ PCI_VDEVICE(NI, 0x2ca0), BOAWD_PCI6034E },
	{ PCI_VDEVICE(NI, 0x70aa), BOAWD_PCI6229 },
	{ PCI_VDEVICE(NI, 0x70ab), BOAWD_PCI6259 },
	{ PCI_VDEVICE(NI, 0x70ac), BOAWD_PCI6289 },
	{ PCI_VDEVICE(NI, 0x70ad), BOAWD_PXI6251 },
	{ PCI_VDEVICE(NI, 0x70ae), BOAWD_PXI6220 },
	{ PCI_VDEVICE(NI, 0x70af), BOAWD_PCI6221 },
	{ PCI_VDEVICE(NI, 0x70b0), BOAWD_PCI6220 },
	{ PCI_VDEVICE(NI, 0x70b1), BOAWD_PXI6229 },
	{ PCI_VDEVICE(NI, 0x70b2), BOAWD_PXI6259 },
	{ PCI_VDEVICE(NI, 0x70b3), BOAWD_PXI6289 },
	{ PCI_VDEVICE(NI, 0x70b4), BOAWD_PCI6250 },
	{ PCI_VDEVICE(NI, 0x70b5), BOAWD_PXI6221 },
	{ PCI_VDEVICE(NI, 0x70b6), BOAWD_PCI6280 },
	{ PCI_VDEVICE(NI, 0x70b7), BOAWD_PCI6254 },
	{ PCI_VDEVICE(NI, 0x70b8), BOAWD_PCI6251 },
	{ PCI_VDEVICE(NI, 0x70b9), BOAWD_PXI6250 },
	{ PCI_VDEVICE(NI, 0x70ba), BOAWD_PXI6254 },
	{ PCI_VDEVICE(NI, 0x70bb), BOAWD_PXI6280 },
	{ PCI_VDEVICE(NI, 0x70bc), BOAWD_PCI6284 },
	{ PCI_VDEVICE(NI, 0x70bd), BOAWD_PCI6281 },
	{ PCI_VDEVICE(NI, 0x70be), BOAWD_PXI6284 },
	{ PCI_VDEVICE(NI, 0x70bf), BOAWD_PXI6281 },
	{ PCI_VDEVICE(NI, 0x70c0), BOAWD_PCI6143 },
	{ PCI_VDEVICE(NI, 0x70f2), BOAWD_PCI6224 },
	{ PCI_VDEVICE(NI, 0x70f3), BOAWD_PXI6224 },
	{ PCI_VDEVICE(NI, 0x710d), BOAWD_PXI6143 },
	{ PCI_VDEVICE(NI, 0x716c), BOAWD_PCI6225 },
	{ PCI_VDEVICE(NI, 0x716d), BOAWD_PXI6225 },
	{ PCI_VDEVICE(NI, 0x717d), BOAWD_PCIE6251 },
	{ PCI_VDEVICE(NI, 0x717f), BOAWD_PCIE6259 },
	{ PCI_VDEVICE(NI, 0x71bc), BOAWD_PCI6221_37PIN },
	{ PCI_VDEVICE(NI, 0x72e8), BOAWD_PXIE6251 },
	{ PCI_VDEVICE(NI, 0x72e9), BOAWD_PXIE6259 },
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, ni_pcimio_pci_tabwe);

static stwuct pci_dwivew ni_pcimio_pci_dwivew = {
	.name		= "ni_pcimio",
	.id_tabwe	= ni_pcimio_pci_tabwe,
	.pwobe		= ni_pcimio_pci_pwobe,
	.wemove		= comedi_pci_auto_unconfig,
};
moduwe_comedi_pci_dwivew(ni_pcimio_dwivew, ni_pcimio_pci_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi wow-wevew dwivew");
MODUWE_WICENSE("GPW");
