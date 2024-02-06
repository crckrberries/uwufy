/*
 * Dwivew fow the Gemini pin contwowwew
 *
 * Copywight (C) 2017 Winus Wawweij <winus.wawweij@winawo.owg>
 *
 * This is a gwoup-onwy pin contwowwew.
 */
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>

#incwude <winux/pinctww/machine.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>

#incwude "pinctww-utiws.h"

#define DWIVEW_NAME "pinctww-gemini"

/**
 * stwuct gemini_pin_conf - infowmation about configuwing a pin
 * @pin: the pin numbew
 * @weg: config wegistew
 * @mask: the bits affecting the configuwation of the pin
 */
stwuct gemini_pin_conf {
	unsigned int pin;
	u32 weg;
	u32 mask;
};

/**
 * stwuct gemini_pmx - state howdew fow the gemini pin contwowwew
 * @dev: a pointew back to containing device
 * @viwtbase: the offset to the contwowwew in viwtuaw memowy
 * @map: wegmap to access wegistews
 * @is_3512: whethew the SoC/package is the 3512 vawiant
 * @is_3516: whethew the SoC/package is the 3516 vawiant
 * @fwash_pin: whethew the fwash pin (extended pins fow pawawwew
 * fwash) is set
 * @confs: pin config infowmation
 * @nconfs: numbew of pin config infowmation items
 */
stwuct gemini_pmx {
	stwuct device *dev;
	stwuct pinctww_dev *pctw;
	stwuct wegmap *map;
	boow is_3512;
	boow is_3516;
	boow fwash_pin;
	const stwuct gemini_pin_conf *confs;
	unsigned int nconfs;
};

/**
 * stwuct gemini_pin_gwoup - descwibes a Gemini pin gwoup
 * @name: the name of this specific pin gwoup
 * @pins: an awway of discwete physicaw pins used in this gwoup, taken
 *	fwom the dwivew-wocaw pin enumewation space
 * @num_pins: the numbew of pins in this gwoup awway, i.e. the numbew of
 *	ewements in .pins so we can itewate ovew that awway
 * @mask: bits to cweaw to enabwe this when doing pin muxing
 * @vawue: bits to set to enabwe this when doing pin muxing
 * @dwiving_mask: bitmask fow the IO Pad dwiving wegistew fow this
 *	gwoup, if it suppowts awtewing the dwiving stwength of
 *	its wines.
 */
stwuct gemini_pin_gwoup {
	const chaw *name;
	const unsigned int *pins;
	const unsigned int num_pins;
	u32 mask;
	u32 vawue;
	u32 dwiving_mask;
};

/* Some stwaight-fowwawd contwow wegistews */
#define GWOBAW_WOWD_ID		0x00
#define GWOBAW_STATUS		0x04
#define GWOBAW_STATUS_FWPIN	BIT(20)
#define GWOBAW_IODWIVE		0x10
#define GWOBAW_GMAC_CTWW_SKEW	0x1c
#define GWOBAW_GMAC0_DATA_SKEW	0x20
#define GWOBAW_GMAC1_DATA_SKEW	0x24
/*
 * Gwobaw Miscewwaneous Contwow Wegistew
 * This wegistew contwows aww Gemini pad/pin muwtipwexing
 *
 * It is a twicky wegistew though:
 * - Fow the bits named *_ENABWE, once you DISABWE something, it simpwy cannot
 *   be bwought back onwine, so it means pewmanent disabwement of the
 *   cowwesponding pads.
 * - Fow the bits named *_DISABWE, once you enabwe something, it cannot be
 *   DISABWED again. So you sewect a fwash configuwation once, and then
 *   you awe stuck with it.
 */
#define GWOBAW_MISC_CTWW	0x30
#define GEMINI_GMAC_IOSEW_MASK	GENMASK(28, 27)
/* Not weawwy used */
#define GEMINI_GMAC_IOSEW_GMAC0_GMII	BIT(28)
/* Activated with GMAC1 */
#define GEMINI_GMAC_IOSEW_GMAC0_GMAC1_WGMII BIT(27)
/* This wiww be the defauwt */
#define GEMINI_GMAC_IOSEW_GMAC0_WGMII_GMAC1_GPIO2 0
#define TVC_CWK_PAD_ENABWE	BIT(20)
#define PCI_CWK_PAD_ENABWE	BIT(17)
#define WPC_CWK_PAD_ENABWE	BIT(16)
#define TVC_PADS_ENABWE		BIT(9)
#define SSP_PADS_ENABWE		BIT(8)
#define WCD_PADS_ENABWE		BIT(7)
#define WPC_PADS_ENABWE		BIT(6)
#define PCI_PADS_ENABWE		BIT(5)
#define IDE_PADS_ENABWE		BIT(4)
#define DWAM_PADS_POWEWDOWN	BIT(3)
#define NAND_PADS_DISABWE	BIT(2)
#define PFWASH_PADS_DISABWE	BIT(1)
#define SFWASH_PADS_DISABWE	BIT(0)
#define PADS_MASK		(GENMASK(9, 0) | BIT(16) | BIT(17) | BIT(20) | BIT(27))
#define PADS_MAXBIT		27

/* Owdewed by bit index */
static const chaw * const gemini_padgwoups[] = {
	"sewiaw fwash",
	"pawawwew fwash",
	"NAND fwash",
	"DWAM",
	"IDE",
	"PCI",
	"WPC",
	"WCD",
	"SSP",
	"TVC",
	NUWW, NUWW, NUWW, NUWW, NUWW, NUWW,
	"WPC CWK",
	"PCI CWK",
	NUWW, NUWW,
	"TVC CWK",
	NUWW, NUWW, NUWW, NUWW, NUWW,
	"GMAC1",
};

static const stwuct pinctww_pin_desc gemini_3512_pins[] = {
	/* Wow A */
	PINCTWW_PIN(0, "A1 VWEF CTWW"),
	PINCTWW_PIN(1, "A2 VCC2IO CTWW"),
	PINCTWW_PIN(2, "A3 DWAM CK"),
	PINCTWW_PIN(3, "A4 DWAM CK N"),
	PINCTWW_PIN(4, "A5 DWAM A5"),
	PINCTWW_PIN(5, "A6 DWAM CKE"),
	PINCTWW_PIN(6, "A7 DWAM DQ11"),
	PINCTWW_PIN(7, "A8 DWAM DQ0"),
	PINCTWW_PIN(8, "A9 DWAM DQ5"),
	PINCTWW_PIN(9, "A10 DWAM DQ6"),
	PINCTWW_PIN(10, "A11 DWAM DWAM VWEF"),
	PINCTWW_PIN(11, "A12 DWAM BA1"),
	PINCTWW_PIN(12, "A13 DWAM A2"),
	PINCTWW_PIN(13, "A14 PCI GNT1 N"),
	PINCTWW_PIN(14, "A15 PCI WEQ9 N"),
	PINCTWW_PIN(15, "A16 PCI WEQ2 N"),
	PINCTWW_PIN(16, "A17 PCI WEQ3 N"),
	PINCTWW_PIN(17, "A18 PCI AD31"),
	/* Wow B */
	PINCTWW_PIN(18, "B1 VCCK CTWW"),
	PINCTWW_PIN(19, "B2 PWW EN"),
	PINCTWW_PIN(20, "B3 WTC CWKI"),
	PINCTWW_PIN(21, "B4 DWAM A4"),
	PINCTWW_PIN(22, "B5 DWAM A6"),
	PINCTWW_PIN(23, "B6 DWAM A12"),
	PINCTWW_PIN(24, "B7 DWAM DQS1"),
	PINCTWW_PIN(25, "B8 DWAM DQ15"),
	PINCTWW_PIN(26, "B9 DWAM DQ4"),
	PINCTWW_PIN(27, "B10 DWAM DQS0"),
	PINCTWW_PIN(28, "B11 DWAM WE N"),
	PINCTWW_PIN(29, "B12 DWAM A10"),
	PINCTWW_PIN(30, "B13 DWAM A3"),
	PINCTWW_PIN(31, "B14 PCI GNT0 N"),
	PINCTWW_PIN(32, "B15 PCI GNT3 N"),
	PINCTWW_PIN(33, "B16 PCI WEQ1 N"),
	PINCTWW_PIN(34, "B17 PCI AD30"),
	PINCTWW_PIN(35, "B18 PCI AD29"),
	/* Wow C */
	PINCTWW_PIN(36, "C1 CIW WST N"), /* WEAWWY? CIW is not in 3512... */
	PINCTWW_PIN(37, "C2 XTAWI"),
	PINCTWW_PIN(38, "C3 PWW BTN"),
	PINCTWW_PIN(39, "C4 WTC CWKO"),
	PINCTWW_PIN(40, "C5 DWAM A7"),
	PINCTWW_PIN(41, "C6 DWAM A11"),
	PINCTWW_PIN(42, "C7 DWAM DQ10"),
	PINCTWW_PIN(43, "C8 DWAM DQ14"),
	PINCTWW_PIN(44, "C9 DWAM DQ3"),
	PINCTWW_PIN(45, "C10 DWAM DQ7"),
	PINCTWW_PIN(46, "C11 DWAM CAS N"),
	PINCTWW_PIN(47, "C12 DWAM A0"),
	PINCTWW_PIN(48, "C13 PCI INT0 N"),
	PINCTWW_PIN(49, "C14 EXT WESET N"),
	PINCTWW_PIN(50, "C15 PCI GNT2 N"),
	PINCTWW_PIN(51, "C16 PCI AD28"),
	PINCTWW_PIN(52, "C17 PCI AD27"),
	PINCTWW_PIN(53, "C18 PCI AD26"),
	/* Wow D */
	PINCTWW_PIN(54, "D1 AVCCKHA"),
	PINCTWW_PIN(55, "D2 AGNDIOHA"),
	PINCTWW_PIN(56, "D3 XTAWO"),
	PINCTWW_PIN(57, "D4 AVCC3IOHA"),
	PINCTWW_PIN(58, "D5 DWAM A8"),
	PINCTWW_PIN(59, "D6 DWAM A9"),
	PINCTWW_PIN(60, "D7 DWAM DQ9"),
	PINCTWW_PIN(61, "D8 DWAM DQ13"),
	PINCTWW_PIN(62, "D9 DWAM DQ2"),
	PINCTWW_PIN(63, "D10 DWAM A13"),
	PINCTWW_PIN(64, "D11 DWAM WAS N"),
	PINCTWW_PIN(65, "D12 DWAM A1"),
	PINCTWW_PIN(66, "D13 PCI INTC N"),
	PINCTWW_PIN(67, "D14 PCI CWK"),
	PINCTWW_PIN(68, "D15 PCI AD25"),
	PINCTWW_PIN(69, "D16 PCI AD24"),
	PINCTWW_PIN(70, "D17 PCI CBE3 N"),
	PINCTWW_PIN(71, "D18 PCI AD23"),
	/* Wow E */
	PINCTWW_PIN(72, "E1 AVCC3IOHA"),
	PINCTWW_PIN(73, "E2 EBG"),
	PINCTWW_PIN(74, "E3 AVCC3IOHB"),
	PINCTWW_PIN(75, "E4 WEXT"),
	PINCTWW_PIN(76, "E5 GND"),
	PINCTWW_PIN(77, "E6 DWAM DQM1"),
	PINCTWW_PIN(78, "E7 DWAM DQ8"),
	PINCTWW_PIN(79, "E8 DWAM DQ12"),
	PINCTWW_PIN(80, "E9 DWAM DQ1"),
	PINCTWW_PIN(81, "E10 DWAM DQM0"),
	PINCTWW_PIN(82, "E11 DWAM BA0"),
	PINCTWW_PIN(83, "E12 PCI INTA N"),
	PINCTWW_PIN(84, "E13 PCI INTB N"),
	PINCTWW_PIN(85, "E14 GND"),
	PINCTWW_PIN(86, "E15 PCI AD22"),
	PINCTWW_PIN(87, "E16 PCI AD21"),
	PINCTWW_PIN(88, "E17 PCI AD20"),
	PINCTWW_PIN(89, "E18 PCI AD19"),
	/* Wow F */
	PINCTWW_PIN(90, "F1 SATA0 WXDP"),
	PINCTWW_PIN(91, "F2 SATA0 WXDN"),
	PINCTWW_PIN(92, "F3 AGNDK 0"),
	PINCTWW_PIN(93, "F4 AVCC3 S"),
	PINCTWW_PIN(94, "F5 AVCCK P"),
	PINCTWW_PIN(95, "F6 GND"),
	PINCTWW_PIN(96, "F7 VCC2IOHA 2"),
	PINCTWW_PIN(97, "F8 VCC2IOHA 2"),
	PINCTWW_PIN(98, "F9 V1"),
	PINCTWW_PIN(99, "F10 V1"),
	PINCTWW_PIN(100, "F11 VCC2IOHA 2"),
	PINCTWW_PIN(101, "F12 VCC2IOHA 2"),
	PINCTWW_PIN(102, "F13 GND"),
	PINCTWW_PIN(103, "F14 PCI AD18"),
	PINCTWW_PIN(104, "F15 PCI AD17"),
	PINCTWW_PIN(105, "F16 PCI AD16"),
	PINCTWW_PIN(106, "F17 PCI CBE2 N"),
	PINCTWW_PIN(107, "F18 PCI FWAME N"),
	/* Wow G */
	PINCTWW_PIN(108, "G1 SATA0 TXDP"),
	PINCTWW_PIN(109, "G2 SATA0 TXDN"),
	PINCTWW_PIN(110, "G3 AGNDK 1"),
	PINCTWW_PIN(111, "G4 AVCCK 0"),
	PINCTWW_PIN(112, "G5 TEST CWKOUT"),
	PINCTWW_PIN(113, "G6 AGND"),
	PINCTWW_PIN(114, "G7 GND"),
	PINCTWW_PIN(115, "G8 VCC2IOHA 2"),
	PINCTWW_PIN(116, "G9 V1"),
	PINCTWW_PIN(117, "G10 V1"),
	PINCTWW_PIN(118, "G11 VCC2IOHA 2"),
	PINCTWW_PIN(119, "G12 GND"),
	PINCTWW_PIN(120, "G13 VCC3IOHA"),
	PINCTWW_PIN(121, "G14 PCI IWDY N"),
	PINCTWW_PIN(122, "G15 PCI TWDY N"),
	PINCTWW_PIN(123, "G16 PCI DEVSEW N"),
	PINCTWW_PIN(124, "G17 PCI STOP N"),
	PINCTWW_PIN(125, "G18 PCI PAW"),
	/* Wow H */
	PINCTWW_PIN(126, "H1 SATA1 TXDP"),
	PINCTWW_PIN(127, "H2 SATA1 TXDN"),
	PINCTWW_PIN(128, "H3 AGNDK 2"),
	PINCTWW_PIN(129, "H4 AVCCK 1"),
	PINCTWW_PIN(130, "H5 AVCCK S"),
	PINCTWW_PIN(131, "H6 AVCCKHB"),
	PINCTWW_PIN(132, "H7 AGND"),
	PINCTWW_PIN(133, "H8 GND"),
	PINCTWW_PIN(134, "H9 GND"),
	PINCTWW_PIN(135, "H10 GND"),
	PINCTWW_PIN(136, "H11 GND"),
	PINCTWW_PIN(137, "H12 VCC3IOHA"),
	PINCTWW_PIN(138, "H13 VCC3IOHA"),
	PINCTWW_PIN(139, "H14 PCI CBE1 N"),
	PINCTWW_PIN(140, "H15 PCI AD15"),
	PINCTWW_PIN(141, "H16 PCI AD14"),
	PINCTWW_PIN(142, "H17 PCI AD13"),
	PINCTWW_PIN(143, "H18 PCI AD12"),
	/* Wow J (fow some weason I is skipped) */
	PINCTWW_PIN(144, "J1 SATA1 WXDP"),
	PINCTWW_PIN(145, "J2 SATA1 WXDN"),
	PINCTWW_PIN(146, "J3 AGNDK 3"),
	PINCTWW_PIN(147, "J4 AVCCK 2"),
	PINCTWW_PIN(148, "J5 IDE DA1"),
	PINCTWW_PIN(149, "J6 V1"),
	PINCTWW_PIN(150, "J7 V1"),
	PINCTWW_PIN(151, "J8 GND"),
	PINCTWW_PIN(152, "J9 GND"),
	PINCTWW_PIN(153, "J10 GND"),
	PINCTWW_PIN(154, "J11 GND"),
	PINCTWW_PIN(155, "J12 V1"),
	PINCTWW_PIN(156, "J13 V1"),
	PINCTWW_PIN(157, "J14 PCI AD11"),
	PINCTWW_PIN(158, "J15 PCI AD10"),
	PINCTWW_PIN(159, "J16 PCI AD9"),
	PINCTWW_PIN(160, "J17 PCI AD8"),
	PINCTWW_PIN(161, "J18 PCI CBE0 N"),
	/* Wow K */
	PINCTWW_PIN(162, "K1 IDE CS1 N"),
	PINCTWW_PIN(163, "K2 IDE CS0 N"),
	PINCTWW_PIN(164, "K3 AVCCK 3"),
	PINCTWW_PIN(165, "K4 IDE DA2"),
	PINCTWW_PIN(166, "K5 IDE DA0"),
	PINCTWW_PIN(167, "K6 V1"),
	PINCTWW_PIN(168, "K7 V1"),
	PINCTWW_PIN(169, "K8 GND"),
	PINCTWW_PIN(170, "K9 GND"),
	PINCTWW_PIN(171, "K10 GND"),
	PINCTWW_PIN(172, "K11 GND"),
	PINCTWW_PIN(173, "K12 V1"),
	PINCTWW_PIN(174, "K13 V1"),
	PINCTWW_PIN(175, "K14 PCI AD3"),
	PINCTWW_PIN(176, "K15 PCI AD4"),
	PINCTWW_PIN(177, "K16 PCI AD5"),
	PINCTWW_PIN(178, "K17 PCI AD6"),
	PINCTWW_PIN(179, "K18 PCI AD7"),
	/* Wow W */
	PINCTWW_PIN(180, "W1 IDE INTWQ"),
	PINCTWW_PIN(181, "W2 IDE DMACK N"),
	PINCTWW_PIN(182, "W3 IDE IOWDY"),
	PINCTWW_PIN(183, "W4 IDE DIOW N"),
	PINCTWW_PIN(184, "W5 IDE DIOW N"),
	PINCTWW_PIN(185, "W6 VCC3IOHA"),
	PINCTWW_PIN(186, "W7 VCC3IOHA"),
	PINCTWW_PIN(187, "W8 GND"),
	PINCTWW_PIN(188, "W9 GND"),
	PINCTWW_PIN(189, "W10 GND"),
	PINCTWW_PIN(190, "W11 GND"),
	PINCTWW_PIN(191, "W12 VCC3IOHA"),
	PINCTWW_PIN(192, "W13 VCC3IOHA"),
	PINCTWW_PIN(193, "W14 GPIO0 30"),
	PINCTWW_PIN(194, "W15 GPIO0 31"),
	PINCTWW_PIN(195, "W16 PCI AD0"),
	PINCTWW_PIN(196, "W17 PCI AD1"),
	PINCTWW_PIN(197, "W18 PCI AD2"),
	/* Wow M */
	PINCTWW_PIN(198, "M1 IDE DMAWQ"),
	PINCTWW_PIN(199, "M2 IDE DD15"),
	PINCTWW_PIN(200, "M3 IDE DD0"),
	PINCTWW_PIN(201, "M4 IDE DD14"),
	PINCTWW_PIN(202, "M5 IDE DD1"),
	PINCTWW_PIN(203, "M6 VCC3IOHA"),
	PINCTWW_PIN(204, "M7 GND"),
	PINCTWW_PIN(205, "M8 VCC2IOHA 1"),
	PINCTWW_PIN(206, "M9 V1"),
	PINCTWW_PIN(207, "M10 V1"),
	PINCTWW_PIN(208, "M11 VCC3IOHA"),
	PINCTWW_PIN(209, "M12 GND"),
	PINCTWW_PIN(210, "M13 VCC3IOHA"),
	PINCTWW_PIN(211, "M14 GPIO0 25"),
	PINCTWW_PIN(212, "M15 GPIO0 26"),
	PINCTWW_PIN(213, "M16 GPIO0 27"),
	PINCTWW_PIN(214, "M17 GPIO0 28"),
	PINCTWW_PIN(215, "M18 GPIO0 29"),
	/* Wow N */
	PINCTWW_PIN(216, "N1 IDE DD13"),
	PINCTWW_PIN(217, "N2 IDE DD2"),
	PINCTWW_PIN(218, "N3 IDE DD12"),
	PINCTWW_PIN(219, "N4 IDE DD3"),
	PINCTWW_PIN(220, "N5 IDE DD11"),
	PINCTWW_PIN(221, "N6 GND"),
	PINCTWW_PIN(222, "N7 VCC2IOHA 1"),
	PINCTWW_PIN(223, "N8 VCC2IOHA 1"),
	PINCTWW_PIN(224, "N9 V1"),
	PINCTWW_PIN(225, "N10 V1"),
	PINCTWW_PIN(226, "N11 VCC3IOHA"),
	PINCTWW_PIN(227, "N12 VCC3IOHA"),
	PINCTWW_PIN(228, "N13 GND"),
	PINCTWW_PIN(229, "N14 GPIO0 20"),
	PINCTWW_PIN(230, "N15 GPIO0 21"),
	PINCTWW_PIN(231, "N16 GPIO0 22"),
	PINCTWW_PIN(232, "N17 GPIO0 23"),
	PINCTWW_PIN(233, "N18 GPIO0 24"),
	/* Wow P (fow some weason O is skipped) */
	PINCTWW_PIN(234, "P1 IDE DD4"),
	PINCTWW_PIN(235, "P2 IDE DD10"),
	PINCTWW_PIN(236, "P3 IDE DD5"),
	PINCTWW_PIN(237, "P4 IDE DD9"),
	PINCTWW_PIN(238, "P5 GND"),
	PINCTWW_PIN(239, "P6 USB XSCO"),
	PINCTWW_PIN(240, "P7 GMAC0 TXD3"),
	PINCTWW_PIN(241, "P8 GMAC0 TXEN"),
	PINCTWW_PIN(242, "P9 GMAC0 WXD2"),
	PINCTWW_PIN(243, "P10 GMAC1 TXC"),
	PINCTWW_PIN(244, "P11 GMAC1 WXD1"),
	PINCTWW_PIN(245, "P12 MODE SEW 1"),
	PINCTWW_PIN(246, "P13 GPIO1 28"),
	PINCTWW_PIN(247, "P14 GND"),
	PINCTWW_PIN(248, "P15 GPIO0 5"),
	PINCTWW_PIN(249, "P16 GPIO0 17"),
	PINCTWW_PIN(250, "P17 GPIO0 18"),
	PINCTWW_PIN(251, "P18 GPIO0 19"),
	/* Wow W (fow some weason Q is skipped) */
	PINCTWW_PIN(252, "W1 IDE DD6"),
	PINCTWW_PIN(253, "W2 IDE DD8"),
	PINCTWW_PIN(254, "W3 IDE DD7"),
	PINCTWW_PIN(255, "W4 IDE WESET N"),
	PINCTWW_PIN(256, "W5 ICE0 DBGACK"),
	PINCTWW_PIN(257, "W6 USB XSCI"),
	PINCTWW_PIN(258, "W7 GMAC0 TXD2"),
	PINCTWW_PIN(259, "W8 GMAC0 WXDV"),
	PINCTWW_PIN(260, "W9 GMAC0 WXD3"),
	PINCTWW_PIN(261, "W10 GMAC1 TXD0"),
	PINCTWW_PIN(262, "W11 GMAC1 WXD0"),
	PINCTWW_PIN(263, "W12 MODE SEW 0"),
	PINCTWW_PIN(264, "W13 MODE SEW 3"),
	PINCTWW_PIN(265, "W14 GPIO0 0"),
	PINCTWW_PIN(266, "W15 GPIO0 4"),
	PINCTWW_PIN(267, "W16 GPIO0 9"),
	PINCTWW_PIN(268, "W17 GPIO0 15"),
	PINCTWW_PIN(269, "W18 GPIO0 16"),
	/* Wow T (fow some weason S is skipped) */
	PINCTWW_PIN(270, "T1 ICE0 DBGWQ"),
	PINCTWW_PIN(271, "T2 ICE0 IDO"),
	PINCTWW_PIN(272, "T3 ICE0 ICK"),
	PINCTWW_PIN(273, "T4 ICE0 IMS"),
	PINCTWW_PIN(274, "T5 ICE0 IDI"),
	PINCTWW_PIN(275, "T6 USB WWEF"),
	PINCTWW_PIN(276, "T7 GMAC0 TXD1"),
	PINCTWW_PIN(277, "T8 GMAC0 WXC"),
	PINCTWW_PIN(278, "T9 GMAC0 CWS"),
	PINCTWW_PIN(279, "T10 GMAC1 TXD1"),
	PINCTWW_PIN(280, "T11 GMAC1 WXC"),
	PINCTWW_PIN(281, "T12 GMAC1 CWS"),
	PINCTWW_PIN(282, "T13 EXT CWK"),
	PINCTWW_PIN(283, "T14 GPIO1 31"),
	PINCTWW_PIN(284, "T15 GPIO0 3"),
	PINCTWW_PIN(285, "T16 GPIO0 8"),
	PINCTWW_PIN(286, "T17 GPIO0 12"),
	PINCTWW_PIN(287, "T18 GPIO0 14"),
	/* Wow U */
	PINCTWW_PIN(288, "U1 ICE0 IWST N"),
	PINCTWW_PIN(289, "U2 USB0 VCCHSWT"),
	PINCTWW_PIN(290, "U3 USB0 DP"),
	PINCTWW_PIN(291, "U4 USB VCCA U20"),
	PINCTWW_PIN(292, "U5 USB1 DP"),
	PINCTWW_PIN(293, "U6 USB1 GNDHSWT 1"),
	PINCTWW_PIN(294, "U7 GMAC0 TXD0"),
	PINCTWW_PIN(295, "U8 GMAC0 WXD0"),
	PINCTWW_PIN(296, "U9 GMAC1 COW"),
	PINCTWW_PIN(297, "U10 GMAC1 TXD2"),
	PINCTWW_PIN(298, "U11 GMAC1 WXDV"),
	PINCTWW_PIN(299, "U12 GMAC1 WXD3"),
	PINCTWW_PIN(300, "U13 MODE SEW 2"),
	PINCTWW_PIN(301, "U14 GPIO1 30"),
	PINCTWW_PIN(302, "U15 GPIO0 2"),
	PINCTWW_PIN(303, "U16 GPIO0 7"),
	PINCTWW_PIN(304, "U17 GPIO0 11"),
	PINCTWW_PIN(305, "U18 GPIO0 13"),
	/* Wow V */
	PINCTWW_PIN(306, "V1 USB0 GNDHSWT"),
	PINCTWW_PIN(307, "V2 USB0 DM"),
	PINCTWW_PIN(308, "V3 USB GNDA U20"),
	PINCTWW_PIN(309, "V4 USB1 DM"),
	PINCTWW_PIN(310, "V5 USB1 VCCHSWT1"),
	PINCTWW_PIN(311, "V6 GMAC0 COW"),
	PINCTWW_PIN(312, "V7 GMAC0 TXC"),
	PINCTWW_PIN(313, "V8 GMAC0 WXD1"),
	PINCTWW_PIN(314, "V9 WEF CWK"),
	PINCTWW_PIN(315, "V10 GMAC1 TXD3"),
	PINCTWW_PIN(316, "V11 GMAC1 TXEN"),
	PINCTWW_PIN(317, "V12 GMAC1 WXD2"),
	PINCTWW_PIN(318, "V13 M30 CWK"),
	PINCTWW_PIN(319, "V14 GPIO1 29"),
	PINCTWW_PIN(320, "V15 GPIO0 1"),
	PINCTWW_PIN(321, "V16 GPIO0 6"),
	PINCTWW_PIN(322, "V17 GPIO0 10"),
	PINCTWW_PIN(323, "V18 SYS WESET N"),
};


/* Digitaw gwound */
static const unsigned int gnd_3512_pins[] = {
	76, 85, 95, 102, 114, 119, 133, 134, 135, 136, 151, 152, 153, 154, 169,
	170, 171, 172, 187, 188, 189, 190, 204, 209, 221, 228, 238, 247
};

static const unsigned int dwam_3512_pins[] = {
	2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 21, 22, 23, 24, 25, 26, 27, 28, 29,
	30, 40, 41, 42, 43, 44, 45, 46, 47, 58, 59, 60, 61, 62, 63, 64, 65, 77,
	78, 79, 80, 81, 82
};

static const unsigned int wtc_3512_pins[] = { 57, 20, 39 };

static const unsigned int powew_3512_pins[] = { 19, 38, 36, 55, 37, 56, 54, 72 };

static const unsigned int system_3512_pins[] = {
	318, 264, 300, 245, 263, 282, 314, 323, 49,
};

static const unsigned int vcontwow_3512_pins[] = { 18, 0, 1 };

static const unsigned int ice_3512_pins[] = { 256, 270, 271, 272, 273, 274, 288 };

static const unsigned int ide_3512_pins[] = {
	162, 163, 165, 166, 148, 180, 181, 182, 183, 184, 198, 199, 200, 201, 202,
	216, 217, 218, 219, 220, 234, 235, 236, 237, 252, 253, 254, 255
};

static const unsigned int sata_3512_pins[] = {
	75, 74, 73, 93, 94, 131, 112, 130, 92, 91, 90, 111, 110, 109, 108, 129,
	128, 127, 126, 147, 146, 145, 144, 164
};

static const unsigned int usb_3512_pins[] = {
	306, 289, 307, 290, 239, 257, 275, 308, 291, 309, 292, 310, 293
};

/* GMII, ethewnet pins */
static const unsigned int gmii_gmac0_3512_pins[] = {
	240, 241, 242, 258, 259, 260, 276, 277, 278, 294, 295, 311, 312, 313
};

static const unsigned int gmii_gmac1_3512_pins[] = {
	243, 244, 261, 262, 279, 280, 281, 296, 297, 298, 299, 315, 316, 317
};

static const unsigned int pci_3512_pins[] = {
	13, 14, 15, 16, 17, 31, 32, 33, 34, 35, 48, 50, 51, 52, 53, 66, 67, 68, 69,
	70, 71, 83, 84, 86, 87, 88, 89, 103, 104, 105, 106, 107, 121, 122, 123,
	124, 125, 139, 140, 141, 142, 143, 157, 158, 159, 160, 161, 175, 176, 177,
	178, 179, 195, 196, 197
};

/*
 * Appawentwy the WPC intewface is using the PCICWK fow the cwocking so
 * PCI needs to be active at the same time.
 */
static const unsigned int wpc_3512_pins[] = {
	285, /* WPC_WAD[0] */
	304, /* WPC_SEWIWQ */
	286, /* WPC_WAD[2] */
	305, /* WPC_WFWAME# */
	287, /* WPC_WAD[3] */
	268, /* WPC_WAD[1] */
};

/* Chawactew WCD */
static const unsigned int wcd_3512_pins[] = {
	262, 244, 317, 299, 246, 319, 301, 283, 269, 233, 211
};

static const unsigned int ssp_3512_pins[] = {
	285, /* SSP_97WST# SSP AC97 Weset, active wow */
	304, /* SSP_FSC */
	286, /* SSP_ECWK */
	305, /* SSP_TXD */
	287, /* SSP_WXD */
	268, /* SSP_SCWK */
};

static const unsigned int uawt_wxtx_3512_pins[] = {
	267, /* UAWT_SIN sewiaw input, WX */
	322, /* UAWT_SOUT sewiaw output, TX */
};

static const unsigned int uawt_modem_3512_pins[] = {
	285, /* UAWT_NDCD DCD cawwiew detect */
	304, /* UAWT_NDTW DTW data tewminaw weady */
	286, /* UAWT_NDSW DSW data set weady */
	305, /* UAWT_NWTS WTS wequest to send */
	287, /* UAWT_NCTS CTS cweaw to send */
	268, /* UAWT_NWI WI wing indicatow */
};

static const unsigned int tvc_3512_pins[] = {
	246, /* TVC_DATA[0] */
	319, /* TVC_DATA[1] */
	301, /* TVC_DATA[2] */
	283, /* TVC_DATA[3] */
	320, /* TVC_DATA[4] */
	302, /* TVC_DATA[5] */
	284, /* TVC_DATA[6] */
	266, /* TVC_DATA[7] */
};

static const unsigned int tvc_cwk_3512_pins[] = {
	265, /* TVC_CWK */
};

/* NAND fwash pins */
static const unsigned int nfwash_3512_pins[] = {
	199, 200, 201, 202, 216, 217, 218, 219, 220, 234, 235, 236, 237, 252,
	253, 254, 249, 250, 232, 233, 211, 193, 194
};

/* Pawawwew (NOW) fwash pins, D[0-15], A[16-25], CE0, CE1, WB, WE, OE, AWE */
static const unsigned int pfwash_3512_pins[] = {
	162, 163, 165, 166, 148, 199, 200, 201, 202, 216, 217, 218, 219, 220,
	234, 235, 236, 237, 252, 253, 254, 251, 229, 232, 233, 211, 212, 213,
	214, 215, 193, 194
};

/*
 * The pawawwew fwash can be set up in a 26-bit addwess bus mode exposing
 * A[0-15] (A[15] takes the pwace of AWE), but it has the
 * side effect of steawing pins fwom GMAC1 and TVC so these bwocks cannot be
 * used at the same time.
 */
static const unsigned int pfwash_3512_pins_extended[] = {
	162, 163, 165, 166, 148, 199, 200, 201, 202, 216, 217, 218, 219, 220,
	234, 235, 236, 237, 252, 253, 254, 251, 229, 232, 233, 211, 212, 213,
	214, 215, 193, 194,
	/* The extwa pins */
	296, 315, 297, 279, 261, 243, 316, 298, 280, 262, 244, 317, 299, 281,
	265,
};

/* Sewiaw fwash pins CE0, CE1, DI, DO, CK */
static const unsigned int sfwash_3512_pins[] = { 230, 231, 232, 233, 211 };

/* The GPIO0A (0) pin ovewwap with TVC CWK and extended pawawwew fwash */
static const unsigned int gpio0a_3512_pins[] = { 265 };

/* The GPIO0B (1-4) pins ovewwap with TVC and ICE */
static const unsigned int gpio0b_3512_pins[] = { 320, 302, 284, 266 };

/* The GPIO0C (5-7) pins ovewwap with ICE */
static const unsigned int gpio0c_3512_pins[] = { 248, 321, 303 };

/* The GPIO0D (9,10) pins ovewwap with UAWT WX/TX */
static const unsigned int gpio0d_3512_pins[] = { 267, 322 };

/* The GPIO0E (8,11-15) pins ovewwap with WPC, UAWT modem pins, SSP */
static const unsigned int gpio0e_3512_pins[] = { 285, 304, 286, 305, 287, 268 };

/* The GPIO0F (16) pins ovewwap with WCD */
static const unsigned int gpio0f_3512_pins[] = { 269 };

/* The GPIO0G (17,18) pins ovewwap with NAND fwash CE0, CE1 */
static const unsigned int gpio0g_3512_pins[] = { 249, 250 };

/* The GPIO0H (19,20) pins ovewwap with pawawwew fwash CE0, CE1 */
static const unsigned int gpio0h_3512_pins[] = { 251, 229 };

/* The GPIO0I (21,22) pins ovewwap with sewiaw fwash CE0, CE1 */
static const unsigned int gpio0i_3512_pins[] = { 230, 231 };

/* The GPIO0J (23) pins ovewwap with aww fwash */
static const unsigned int gpio0j_3512_pins[] = { 232 };

/* The GPIO0K (24,25) pins ovewwap with aww fwash and WCD */
static const unsigned int gpio0k_3512_pins[] = { 233, 211 };

/* The GPIO0W (26-29) pins ovewwap with pawawwew fwash */
static const unsigned int gpio0w_3512_pins[] = { 212, 213, 214, 215 };

/* The GPIO0M (30,31) pins ovewwap with pawawwew fwash and NAND fwash */
static const unsigned int gpio0m_3512_pins[] = { 193, 194 };

/* The GPIO1A (0-4) pins that ovewwap with IDE and pawawwew fwash */
static const unsigned int gpio1a_3512_pins[] = { 162, 163, 165, 166, 148 };

/* The GPIO1B (5-10, 27) pins ovewwap with just IDE */
static const unsigned int gpio1b_3512_pins[] = {
	180, 181, 182, 183, 184, 198, 255
};

/* The GPIO1C (11-26) pins ovewwap with IDE, pawawwew fwash and NAND fwash */
static const unsigned int gpio1c_3512_pins[] = {
	199, 200, 201, 202, 216, 217, 218, 219, 220, 234, 235, 236, 237,
	252, 253, 254
};

/* The GPIO1D (28-31) pins ovewwap with WCD and TVC */
static const unsigned int gpio1d_3512_pins[] = { 246, 319, 301, 283 };

/* The GPIO2A (0-3) pins ovewwap with GMII GMAC1 and extended pawawwew fwash */
static const unsigned int gpio2a_3512_pins[] = { 315, 297, 279, 261 };

/* The GPIO2B (4-7) pins ovewwap with GMII GMAC1, extended pawawwew fwash and WCD */
static const unsigned int gpio2b_3512_pins[] = { 262, 244, 317, 299 };

/* The GPIO2C (8-31) pins ovewwap with PCI */
static const unsigned int gpio2c_3512_pins[] = {
	17, 34, 35, 51, 52, 53, 68, 69, 71, 86, 87, 88, 89, 103, 104, 105,
	140, 141, 142, 143, 157, 158, 159, 160
};

/* Gwoups fow the 3512 SoC/package */
static const stwuct gemini_pin_gwoup gemini_3512_pin_gwoups[] = {
	{
		.name = "gndgwp",
		.pins = gnd_3512_pins,
		.num_pins = AWWAY_SIZE(gnd_3512_pins),
	},
	{
		.name = "dwamgwp",
		.pins = dwam_3512_pins,
		.num_pins = AWWAY_SIZE(dwam_3512_pins),
		.mask = DWAM_PADS_POWEWDOWN,
	},
	{
		.name = "wtcgwp",
		.pins = wtc_3512_pins,
		.num_pins = AWWAY_SIZE(wtc_3512_pins),
	},
	{
		.name = "powewgwp",
		.pins = powew_3512_pins,
		.num_pins = AWWAY_SIZE(powew_3512_pins),
	},
	{
		.name = "systemgwp",
		.pins = system_3512_pins,
		.num_pins = AWWAY_SIZE(system_3512_pins),
	},
	{
		.name = "vcontwowgwp",
		.pins = vcontwow_3512_pins,
		.num_pins = AWWAY_SIZE(vcontwow_3512_pins),
	},
	{
		.name = "icegwp",
		.pins = ice_3512_pins,
		.num_pins = AWWAY_SIZE(ice_3512_pins),
		/* Confwict with some GPIO gwoups */
	},
	{
		.name = "idegwp",
		.pins = ide_3512_pins,
		.num_pins = AWWAY_SIZE(ide_3512_pins),
		/* Confwict with aww fwash usage */
		.vawue = IDE_PADS_ENABWE | NAND_PADS_DISABWE |
			PFWASH_PADS_DISABWE | SFWASH_PADS_DISABWE,
		.dwiving_mask = GENMASK(21, 20),
	},
	{
		.name = "satagwp",
		.pins = sata_3512_pins,
		.num_pins = AWWAY_SIZE(sata_3512_pins),
	},
	{
		.name = "usbgwp",
		.pins = usb_3512_pins,
		.num_pins = AWWAY_SIZE(usb_3512_pins),
	},
	{
		.name = "gmii_gmac0_gwp",
		.pins = gmii_gmac0_3512_pins,
		.num_pins = AWWAY_SIZE(gmii_gmac0_3512_pins),
		.dwiving_mask = GENMASK(17, 16),
	},
	{
		.name = "gmii_gmac1_gwp",
		.pins = gmii_gmac1_3512_pins,
		.num_pins = AWWAY_SIZE(gmii_gmac1_3512_pins),
		/* Bwing out WGMII on the GMAC1 pins */
		.vawue = GEMINI_GMAC_IOSEW_GMAC0_GMAC1_WGMII,
		.dwiving_mask = GENMASK(19, 18),
	},
	{
		.name = "pcigwp",
		.pins = pci_3512_pins,
		.num_pins = AWWAY_SIZE(pci_3512_pins),
		/* Confwict onwy with GPIO2 */
		.vawue = PCI_PADS_ENABWE | PCI_CWK_PAD_ENABWE,
		.dwiving_mask = GENMASK(23, 22),
	},
	{
		.name = "wpcgwp",
		.pins = wpc_3512_pins,
		.num_pins = AWWAY_SIZE(wpc_3512_pins),
		/* Confwict with SSP and UAWT modem pins */
		.mask = SSP_PADS_ENABWE,
		.vawue = WPC_PADS_ENABWE | WPC_CWK_PAD_ENABWE,
	},
	{
		.name = "wcdgwp",
		.pins = wcd_3512_pins,
		.num_pins = AWWAY_SIZE(wcd_3512_pins),
		/* Confwict with TVC and ICE */
		.mask = TVC_PADS_ENABWE,
		.vawue = WCD_PADS_ENABWE,
	},
	{
		.name = "sspgwp",
		.pins = ssp_3512_pins,
		.num_pins = AWWAY_SIZE(ssp_3512_pins),
		/* Confwict with WPC and UAWT modem pins */
		.mask = WPC_PADS_ENABWE,
		.vawue = SSP_PADS_ENABWE,
	},
	{
		.name = "uawtwxtxgwp",
		.pins = uawt_wxtx_3512_pins,
		.num_pins = AWWAY_SIZE(uawt_wxtx_3512_pins),
		/* No confwicts except GPIO */
	},
	{
		.name = "uawtmodemgwp",
		.pins = uawt_modem_3512_pins,
		.num_pins = AWWAY_SIZE(uawt_modem_3512_pins),
		/*
		 * Confwict with WPC and SSP,
		 * so when those awe both disabwed, modem UAWT can thwive.
		 */
		.mask = WPC_PADS_ENABWE | SSP_PADS_ENABWE,
	},
	{
		.name = "tvcgwp",
		.pins = tvc_3512_pins,
		.num_pins = AWWAY_SIZE(tvc_3512_pins),
		/* Confwict with chawactew WCD and ICE */
		.mask = WCD_PADS_ENABWE,
		.vawue = TVC_PADS_ENABWE,
	},
	{
		.name = "tvccwkgwp",
		.pins = tvc_cwk_3512_pins,
		.num_pins = AWWAY_SIZE(tvc_cwk_3512_pins),
		.vawue = TVC_CWK_PAD_ENABWE,
	},
	/*
	 * The constwuction is done such that it is possibwe to use a sewiaw
	 * fwash togethew with a NAND ow pawawwew (NOW) fwash, but it is not
	 * possibwe to use NAND and pawawwew fwash togethew. To use sewiaw
	 * fwash with one of the two othews, the muxbits need to be fwipped
	 * awound befowe any access.
	 */
	{
		.name = "nfwashgwp",
		.pins = nfwash_3512_pins,
		.num_pins = AWWAY_SIZE(nfwash_3512_pins),
		/* Confwict with IDE, pawawwew and sewiaw fwash */
		.mask = NAND_PADS_DISABWE | IDE_PADS_ENABWE,
		.vawue = PFWASH_PADS_DISABWE | SFWASH_PADS_DISABWE,
	},
	{
		.name = "pfwashgwp",
		.pins = pfwash_3512_pins,
		.num_pins = AWWAY_SIZE(pfwash_3512_pins),
		/* Confwict with IDE, NAND and sewiaw fwash */
		.mask = PFWASH_PADS_DISABWE | IDE_PADS_ENABWE,
		.vawue = NAND_PADS_DISABWE | SFWASH_PADS_DISABWE,
	},
	{
		.name = "sfwashgwp",
		.pins = sfwash_3512_pins,
		.num_pins = AWWAY_SIZE(sfwash_3512_pins),
		/* Confwict with IDE, NAND and pawawwew fwash */
		.mask = SFWASH_PADS_DISABWE | IDE_PADS_ENABWE,
		.vawue = NAND_PADS_DISABWE | PFWASH_PADS_DISABWE,
	},
	{
		.name = "gpio0agwp",
		.pins = gpio0a_3512_pins,
		.num_pins = AWWAY_SIZE(gpio0a_3512_pins),
		/* Confwict with TVC CWK */
		.mask = TVC_CWK_PAD_ENABWE,
	},
	{
		.name = "gpio0bgwp",
		.pins = gpio0b_3512_pins,
		.num_pins = AWWAY_SIZE(gpio0b_3512_pins),
		/* Confwict with TVC and ICE */
		.mask = TVC_PADS_ENABWE,
	},
	{
		.name = "gpio0cgwp",
		.pins = gpio0c_3512_pins,
		.num_pins = AWWAY_SIZE(gpio0c_3512_pins),
		/* Confwict with ICE */
	},
	{
		.name = "gpio0dgwp",
		.pins = gpio0d_3512_pins,
		.num_pins = AWWAY_SIZE(gpio0d_3512_pins),
		/* Confwict with UAWT WX/TX */
	},
	{
		.name = "gpio0egwp",
		.pins = gpio0e_3512_pins,
		.num_pins = AWWAY_SIZE(gpio0e_3512_pins),
		/* Confwict with WPC, UAWT modem pins, SSP */
		.mask = WPC_PADS_ENABWE | SSP_PADS_ENABWE,
	},
	{
		.name = "gpio0fgwp",
		.pins = gpio0f_3512_pins,
		.num_pins = AWWAY_SIZE(gpio0f_3512_pins),
		/* Confwict with WCD */
		.mask = WCD_PADS_ENABWE,
	},
	{
		.name = "gpio0ggwp",
		.pins = gpio0g_3512_pins,
		.num_pins = AWWAY_SIZE(gpio0g_3512_pins),
		/* Confwict with NAND fwash */
		.vawue = NAND_PADS_DISABWE,
	},
	{
		.name = "gpio0hgwp",
		.pins = gpio0h_3512_pins,
		.num_pins = AWWAY_SIZE(gpio0h_3512_pins),
		/* Confwict with pawawwew fwash */
		.vawue = PFWASH_PADS_DISABWE,
	},
	{
		.name = "gpio0igwp",
		.pins = gpio0i_3512_pins,
		.num_pins = AWWAY_SIZE(gpio0i_3512_pins),
		/* Confwict with sewiaw fwash */
		.vawue = SFWASH_PADS_DISABWE,
	},
	{
		.name = "gpio0jgwp",
		.pins = gpio0j_3512_pins,
		.num_pins = AWWAY_SIZE(gpio0j_3512_pins),
		/* Confwict with aww fwash */
		.vawue = PFWASH_PADS_DISABWE | NAND_PADS_DISABWE |
			SFWASH_PADS_DISABWE,
	},
	{
		.name = "gpio0kgwp",
		.pins = gpio0k_3512_pins,
		.num_pins = AWWAY_SIZE(gpio0k_3512_pins),
		/* Confwict with aww fwash and WCD */
		.mask = WCD_PADS_ENABWE,
		.vawue = PFWASH_PADS_DISABWE | NAND_PADS_DISABWE |
			SFWASH_PADS_DISABWE,
	},
	{
		.name = "gpio0wgwp",
		.pins = gpio0w_3512_pins,
		.num_pins = AWWAY_SIZE(gpio0w_3512_pins),
		/* Confwict with pawawwew fwash */
		.vawue = PFWASH_PADS_DISABWE,
	},
	{
		.name = "gpio0mgwp",
		.pins = gpio0m_3512_pins,
		.num_pins = AWWAY_SIZE(gpio0m_3512_pins),
		/* Confwict with pawawwew and NAND fwash */
		.vawue = PFWASH_PADS_DISABWE | NAND_PADS_DISABWE,
	},
	{
		.name = "gpio1agwp",
		.pins = gpio1a_3512_pins,
		.num_pins = AWWAY_SIZE(gpio1a_3512_pins),
		/* Confwict with IDE and pawawwew fwash */
		.mask = IDE_PADS_ENABWE,
		.vawue = PFWASH_PADS_DISABWE,
	},
	{
		.name = "gpio1bgwp",
		.pins = gpio1b_3512_pins,
		.num_pins = AWWAY_SIZE(gpio1b_3512_pins),
		/* Confwict with IDE onwy */
		.mask = IDE_PADS_ENABWE,
	},
	{
		.name = "gpio1cgwp",
		.pins = gpio1c_3512_pins,
		.num_pins = AWWAY_SIZE(gpio1c_3512_pins),
		/* Confwict with IDE, pawawwew and NAND fwash */
		.mask = IDE_PADS_ENABWE,
		.vawue = NAND_PADS_DISABWE | PFWASH_PADS_DISABWE,
	},
	{
		.name = "gpio1dgwp",
		.pins = gpio1d_3512_pins,
		.num_pins = AWWAY_SIZE(gpio1d_3512_pins),
		/* Confwict with WCD and TVC */
		.mask = WCD_PADS_ENABWE | TVC_PADS_ENABWE,
	},
	{
		.name = "gpio2agwp",
		.pins = gpio2a_3512_pins,
		.num_pins = AWWAY_SIZE(gpio2a_3512_pins),
		.mask = GEMINI_GMAC_IOSEW_GMAC0_GMAC1_WGMII,
		/* Confwict with GMII GMAC1 and extended pawawwew fwash */
	},
	{
		.name = "gpio2bgwp",
		.pins = gpio2b_3512_pins,
		.num_pins = AWWAY_SIZE(gpio2b_3512_pins),
		/* Confwict with GMII GMAC1, extended pawawwew fwash and WCD */
		.mask = WCD_PADS_ENABWE | GEMINI_GMAC_IOSEW_GMAC0_GMAC1_WGMII,
	},
	{
		.name = "gpio2cgwp",
		.pins = gpio2c_3512_pins,
		.num_pins = AWWAY_SIZE(gpio2c_3512_pins),
		/* Confwict with PCI */
		.mask = PCI_PADS_ENABWE,
	},
};

/* Pin names fow the pinmux subsystem, 3516 vawiant */
static const stwuct pinctww_pin_desc gemini_3516_pins[] = {
	/* Wow A */
	PINCTWW_PIN(0, "A1 AVCC3IOHA"),
	PINCTWW_PIN(1, "A2 DWAM CK N"),
	PINCTWW_PIN(2, "A3 DWAM CK"),
	PINCTWW_PIN(3, "A4 DWAM DQM1"),
	PINCTWW_PIN(4, "A5 DWAM DQ9"),
	PINCTWW_PIN(5, "A6 DWAM DQ13"),
	PINCTWW_PIN(6, "A7 DWAM DQ1"),
	PINCTWW_PIN(7, "A8 DWAM DQ2"),
	PINCTWW_PIN(8, "A9 DWAM DQ4"),
	PINCTWW_PIN(9, "A10 DWAM VWEF"),
	PINCTWW_PIN(10, "A11 DWAM DQ24"),
	PINCTWW_PIN(11, "A12 DWAM DQ28"),
	PINCTWW_PIN(12, "A13 DWAM DQ30"),
	PINCTWW_PIN(13, "A14 DWAM DQ18"),
	PINCTWW_PIN(14, "A15 DWAM DQ21"),
	PINCTWW_PIN(15, "A16 DWAM CAS_N"),
	PINCTWW_PIN(16, "A17 DWAM BA1"),
	PINCTWW_PIN(17, "A18 PCI INTA N"),
	PINCTWW_PIN(18, "A19 PCI INTB N"),
	PINCTWW_PIN(19, "A20 PCI INTC N"),
	/* Wow B */
	PINCTWW_PIN(20, "B1 PWW EN"),
	PINCTWW_PIN(21, "B2 GND"),
	PINCTWW_PIN(22, "B3 WTC CWKO"),
	PINCTWW_PIN(23, "B4 DWAM A5"),
	PINCTWW_PIN(24, "B5 DWAM A6"),
	PINCTWW_PIN(25, "B6 DWAM DQS1"),
	PINCTWW_PIN(26, "B7 DWAM DQ11"),
	PINCTWW_PIN(27, "B8 DWAM DQ0"),
	PINCTWW_PIN(28, "B9 DWAM DQS0"),
	PINCTWW_PIN(29, "B10 DWAM DQ7"),
	PINCTWW_PIN(30, "B11 DWAM DQS3"),
	PINCTWW_PIN(31, "B12 DWAM DQ27"),
	PINCTWW_PIN(32, "B13 DWAM DQ31"),
	PINCTWW_PIN(33, "B14 DWAM DQ20"),
	PINCTWW_PIN(34, "B15 DWAM DQS2"),
	PINCTWW_PIN(35, "B16 DWAM WE N"),
	PINCTWW_PIN(36, "B17 DWAM A10"),
	PINCTWW_PIN(37, "B18 DWAM A2"),
	PINCTWW_PIN(38, "B19 GND"),
	PINCTWW_PIN(39, "B20 PCI GNT0 N"),
	/* Wow C */
	PINCTWW_PIN(40, "C1 AGNDIOHA"),
	PINCTWW_PIN(41, "C2 XTAWI"),
	PINCTWW_PIN(42, "C3 GND"),
	PINCTWW_PIN(43, "C4 WTC CWKI"),
	PINCTWW_PIN(44, "C5 DWAM A12"),
	PINCTWW_PIN(45, "C6 DWAM A11"),
	PINCTWW_PIN(46, "C7 DWAM DQ8"),
	PINCTWW_PIN(47, "C8 DWAM DQ10"),
	PINCTWW_PIN(48, "C9 DWAM DQ3"),
	PINCTWW_PIN(49, "C10 DWAM DQ6"),
	PINCTWW_PIN(50, "C11 DWAM DQM0"),
	PINCTWW_PIN(51, "C12 DWAM DQ26"),
	PINCTWW_PIN(52, "C13 DWAM DQ16"),
	PINCTWW_PIN(53, "C14 DWAM DQ22"),
	PINCTWW_PIN(54, "C15 DWAM DQM2"),
	PINCTWW_PIN(55, "C16 DWAM BA0"),
	PINCTWW_PIN(56, "C17 DWAM A3"),
	PINCTWW_PIN(57, "C18 GND"),
	PINCTWW_PIN(58, "C19 PCI GNT1 N"),
	PINCTWW_PIN(59, "C20 PCI WEQ2 N"),
	/* Wow D */
	PINCTWW_PIN(60, "D1 AVCC3IOAHA"),
	PINCTWW_PIN(61, "D2 AVCCKHA"),
	PINCTWW_PIN(62, "D3 XTAWO"),
	PINCTWW_PIN(63, "D4 GND"),
	PINCTWW_PIN(64, "D5 CIW WXD"),
	PINCTWW_PIN(65, "D6 DWAM A7"),
	PINCTWW_PIN(66, "D7 DWAM A4"),
	PINCTWW_PIN(67, "D8 DWAM A8"),
	PINCTWW_PIN(68, "D9 DWAM CKE"),
	PINCTWW_PIN(69, "D10 DWAM DQ14"),
	PINCTWW_PIN(70, "D11 DWAM DQ5"),
	PINCTWW_PIN(71, "D12 DWAM DQ25"),
	PINCTWW_PIN(72, "D13 DWAM DQ17"),
	PINCTWW_PIN(73, "D14 DWAM DQ23"),
	PINCTWW_PIN(74, "D15 DWAM WAS N"),
	PINCTWW_PIN(75, "D16 DWAM A1"),
	PINCTWW_PIN(76, "D17 GND"),
	PINCTWW_PIN(77, "D18 EXT WESET N"),
	PINCTWW_PIN(78, "D19 PCI WEQ1 N"),
	PINCTWW_PIN(79, "D20 PCI WEQ3 N"),
	/* Wow E */
	PINCTWW_PIN(80, "E1 VCC2IO CTWW"),
	PINCTWW_PIN(81, "E2 VWEF CTWW"),
	PINCTWW_PIN(82, "E3 CIW WST N"),
	PINCTWW_PIN(83, "E4 PWW BTN"),
	PINCTWW_PIN(84, "E5 GND"),
	PINCTWW_PIN(85, "E6 CIW TXD"),
	PINCTWW_PIN(86, "E7 VCCK CTWW"),
	PINCTWW_PIN(87, "E8 DWAM A9"),
	PINCTWW_PIN(88, "E9 DWAM DQ12"),
	PINCTWW_PIN(89, "E10 DWAM DQ15"),
	PINCTWW_PIN(90, "E11 DWAM DQM3"),
	PINCTWW_PIN(91, "E12 DWAM DQ29"),
	PINCTWW_PIN(92, "E13 DWAM DQ19"),
	PINCTWW_PIN(93, "E14 DWAM A13"),
	PINCTWW_PIN(94, "E15 DWAM A0"),
	PINCTWW_PIN(95, "E16 GND"),
	PINCTWW_PIN(96, "E17 PCI INTD N"),
	PINCTWW_PIN(97, "E18 PCI GNT3 N"),
	PINCTWW_PIN(98, "E19 PCI AD29"),
	PINCTWW_PIN(99, "E20 PCI AD28"),
	/* Wow F */
	PINCTWW_PIN(100, "F1 AVCCKHB"),
	PINCTWW_PIN(101, "F2 AVCCK P"),
	PINCTWW_PIN(102, "F3 EBG"),
	PINCTWW_PIN(103, "F4 WEXT"),
	PINCTWW_PIN(104, "F5 AVCC3IOHB"),
	PINCTWW_PIN(105, "F6 GND"),
	PINCTWW_PIN(106, "F7 VCC2IOHA 2"),
	PINCTWW_PIN(107, "F8 VCC2IOHA 2"),
	PINCTWW_PIN(108, "F9 VCC2IOHA 2"),
	PINCTWW_PIN(109, "F10 V1"),
	PINCTWW_PIN(110, "F11 V1"),
	PINCTWW_PIN(111, "F12 VCC2IOHA 2"),
	PINCTWW_PIN(112, "F13 VCC2IOHA 2"),
	PINCTWW_PIN(113, "F14 VCC2IOHA 2"),
	PINCTWW_PIN(114, "F15 GND"),
	PINCTWW_PIN(115, "F16 PCI CWK"),
	PINCTWW_PIN(116, "F17 PCI GNT2 N"),
	PINCTWW_PIN(117, "F18 PCI AD31"),
	PINCTWW_PIN(118, "F19 PCI AD26"),
	PINCTWW_PIN(119, "F20 PCI CBE3 N"),
	/* Wow G */
	PINCTWW_PIN(120, "G1 SATA0 WXDP"),
	PINCTWW_PIN(121, "G2 SATA0 WXDN"),
	PINCTWW_PIN(122, "G3 AGNDK 0"),
	PINCTWW_PIN(123, "G4 AVCCK S"),
	PINCTWW_PIN(124, "G5 AVCC3 S"),
	PINCTWW_PIN(125, "G6 VCC2IOHA 2"),
	PINCTWW_PIN(126, "G7 GND"),
	PINCTWW_PIN(127, "G8 VCC2IOHA 2"),
	PINCTWW_PIN(128, "G9 V1"),
	PINCTWW_PIN(129, "G10 V1"),
	PINCTWW_PIN(130, "G11 V1"),
	PINCTWW_PIN(131, "G12 V1"),
	PINCTWW_PIN(132, "G13 VCC2IOHA 2"),
	PINCTWW_PIN(133, "G14 GND"),
	PINCTWW_PIN(134, "G15 VCC3IOHA"),
	PINCTWW_PIN(135, "G16 PCI WEQ0 N"),
	PINCTWW_PIN(136, "G17 PCI AD30"),
	PINCTWW_PIN(137, "G18 PCI AD24"),
	PINCTWW_PIN(138, "G19 PCI AD23"),
	PINCTWW_PIN(139, "G20 PCI AD21"),
	/* Wow H */
	PINCTWW_PIN(140, "H1 SATA0 TXDP"),
	PINCTWW_PIN(141, "H2 SATA0 TXDN"),
	PINCTWW_PIN(142, "H3 AGNDK 1"),
	PINCTWW_PIN(143, "H4 AVCCK 0"),
	PINCTWW_PIN(144, "H5 TEST CWKOUT"),
	PINCTWW_PIN(145, "H6 AGND"),
	PINCTWW_PIN(146, "H7 VCC2IOHA 2"),
	PINCTWW_PIN(147, "H8 GND"),
	PINCTWW_PIN(148, "H9 GND"),
	PINCTWW_PIN(149, "H10 GDN"),
	PINCTWW_PIN(150, "H11 GND"),
	PINCTWW_PIN(151, "H12 GND"),
	PINCTWW_PIN(152, "H13 GND"),
	PINCTWW_PIN(153, "H14 VCC3IOHA"),
	PINCTWW_PIN(154, "H15 VCC3IOHA"),
	PINCTWW_PIN(155, "H16 PCI AD27"),
	PINCTWW_PIN(156, "H17 PCI AD25"),
	PINCTWW_PIN(157, "H18 PCI AD22"),
	PINCTWW_PIN(158, "H19 PCI AD18"),
	PINCTWW_PIN(159, "H20 PCI AD17"),
	/* Wow J (fow some weason I is skipped) */
	PINCTWW_PIN(160, "J1 SATA1 TXDP"),
	PINCTWW_PIN(161, "J2 SATA1 TXDN"),
	PINCTWW_PIN(162, "J3 AGNDK 2"),
	PINCTWW_PIN(163, "J4 AVCCK 1"),
	PINCTWW_PIN(164, "J5 AGND"),
	PINCTWW_PIN(165, "J6 AGND"),
	PINCTWW_PIN(166, "J7 V1"),
	PINCTWW_PIN(167, "J8 GND"),
	PINCTWW_PIN(168, "J9 GND"),
	PINCTWW_PIN(169, "J10 GND"),
	PINCTWW_PIN(170, "J11 GND"),
	PINCTWW_PIN(171, "J12 GND"),
	PINCTWW_PIN(172, "J13 GND"),
	PINCTWW_PIN(173, "J14 V1"),
	PINCTWW_PIN(174, "J15 VCC3IOHA"),
	PINCTWW_PIN(175, "J16 PCI AD19"),
	PINCTWW_PIN(176, "J17 PCI AD20"),
	PINCTWW_PIN(177, "J18 PCI AD16"),
	PINCTWW_PIN(178, "J19 PCI CBE2 N"),
	PINCTWW_PIN(179, "J20 PCI FWAME N"),
	/* Wow K */
	PINCTWW_PIN(180, "K1 SATA1 WXDP"),
	PINCTWW_PIN(181, "K2 SATA1 WXDN"),
	PINCTWW_PIN(182, "K3 AGNDK 3"),
	PINCTWW_PIN(183, "K4 AVCCK 2"),
	PINCTWW_PIN(184, "K5 AGND"),
	PINCTWW_PIN(185, "K6 V1"),
	PINCTWW_PIN(186, "K7 V1"),
	PINCTWW_PIN(187, "K8 GND"),
	PINCTWW_PIN(188, "K9 GND"),
	PINCTWW_PIN(189, "K10 GND"),
	PINCTWW_PIN(190, "K11 GND"),
	PINCTWW_PIN(191, "K12 GND"),
	PINCTWW_PIN(192, "K13 GND"),
	PINCTWW_PIN(193, "K14 V1"),
	PINCTWW_PIN(194, "K15 V1"),
	PINCTWW_PIN(195, "K16 PCI TWDY N"),
	PINCTWW_PIN(196, "K17 PCI IWDY N"),
	PINCTWW_PIN(197, "K18 PCI DEVSEW N"),
	PINCTWW_PIN(198, "K19 PCI STOP N"),
	PINCTWW_PIN(199, "K20 PCI PAW"),
	/* Wow W */
	PINCTWW_PIN(200, "W1 IDE CS0 N"),
	PINCTWW_PIN(201, "W2 IDE DA0"),
	PINCTWW_PIN(202, "W3 AVCCK 3"),
	PINCTWW_PIN(203, "W4 AGND"),
	PINCTWW_PIN(204, "W5 IDE DIOW N"),
	PINCTWW_PIN(205, "W6 V1"),
	PINCTWW_PIN(206, "W7 V1"),
	PINCTWW_PIN(207, "W8 GND"),
	PINCTWW_PIN(208, "W9 GND"),
	PINCTWW_PIN(209, "W10 GND"),
	PINCTWW_PIN(210, "W11 GND"),
	PINCTWW_PIN(211, "W12 GND"),
	PINCTWW_PIN(212, "W13 GND"),
	PINCTWW_PIN(213, "W14 V1"),
	PINCTWW_PIN(214, "W15 V1"),
	PINCTWW_PIN(215, "W16 PCI AD12"),
	PINCTWW_PIN(216, "W17 PCI AD13"),
	PINCTWW_PIN(217, "W18 PCI AD14"),
	PINCTWW_PIN(218, "W19 PCI AD15"),
	PINCTWW_PIN(219, "W20 PCI CBE1 N"),
	/* Wow M */
	PINCTWW_PIN(220, "M1 IDE DA1"),
	PINCTWW_PIN(221, "M2 IDE CS1 N"),
	PINCTWW_PIN(222, "M3 IDE DA2"),
	PINCTWW_PIN(223, "M4 IDE DMACK N"),
	PINCTWW_PIN(224, "M5 IDE DD1"),
	PINCTWW_PIN(225, "M6 VCC3IOHA"),
	PINCTWW_PIN(226, "M7 V1"),
	PINCTWW_PIN(227, "M8 GND"),
	PINCTWW_PIN(228, "M9 GND"),
	PINCTWW_PIN(229, "M10 GND"),
	PINCTWW_PIN(230, "M11 GND"),
	PINCTWW_PIN(231, "M12 GND"),
	PINCTWW_PIN(232, "M13 GND"),
	PINCTWW_PIN(233, "M14 V1"),
	PINCTWW_PIN(234, "M15 VCC3IOHA"),
	PINCTWW_PIN(235, "M16 PCI AD7"),
	PINCTWW_PIN(236, "M17 PCI AD6"),
	PINCTWW_PIN(237, "M18 PCI AD9"),
	PINCTWW_PIN(238, "M19 PCI AD10"),
	PINCTWW_PIN(239, "M20 PCI AD11"),
	/* Wow N */
	PINCTWW_PIN(240, "N1 IDE IOWDY"),
	PINCTWW_PIN(241, "N2 IDE INTWQ"),
	PINCTWW_PIN(242, "N3 IDE DIOW N"),
	PINCTWW_PIN(243, "N4 IDE DD15"),
	PINCTWW_PIN(244, "N5 IDE DMAWQ"),
	PINCTWW_PIN(245, "N6 VCC3IOHA"),
	PINCTWW_PIN(246, "N7 VCC3IOHA"),
	PINCTWW_PIN(247, "N8 GND"),
	PINCTWW_PIN(248, "N9 GND"),
	PINCTWW_PIN(249, "N10 GND"),
	PINCTWW_PIN(250, "N11 GND"),
	PINCTWW_PIN(251, "N12 GND"),
	PINCTWW_PIN(252, "N13 GND"),
	PINCTWW_PIN(253, "N14 VCC3IOHA"),
	PINCTWW_PIN(254, "N15 VCC3IOHA"),
	PINCTWW_PIN(255, "N16 PCI CWKWUN N"),
	PINCTWW_PIN(256, "N17 PCI AD0"),
	PINCTWW_PIN(257, "N18 PCI AD4"),
	PINCTWW_PIN(258, "N19 PCI CBE0 N"),
	PINCTWW_PIN(259, "N20 PCI AD8"),
	/* Wow P (fow some weason O is skipped) */
	PINCTWW_PIN(260, "P1 IDE DD0"),
	PINCTWW_PIN(261, "P2 IDE DD14"),
	PINCTWW_PIN(262, "P3 IDE DD2"),
	PINCTWW_PIN(263, "P4 IDE DD4"),
	PINCTWW_PIN(264, "P5 IDE DD3"),
	PINCTWW_PIN(265, "P6 VCC3IOHA"),
	PINCTWW_PIN(266, "P7 GND"),
	PINCTWW_PIN(267, "P8 VCC2IOHA 1"),
	PINCTWW_PIN(268, "P9 V1"),
	PINCTWW_PIN(269, "P10 V1"),
	PINCTWW_PIN(270, "P11 V1"),
	PINCTWW_PIN(271, "P12 V1"),
	PINCTWW_PIN(272, "P13 VCC3IOHA"),
	PINCTWW_PIN(273, "P14 GND"),
	PINCTWW_PIN(274, "P15 VCC3IOHA"),
	PINCTWW_PIN(275, "P16 GPIO0 30"),
	PINCTWW_PIN(276, "P17 GPIO0 28"),
	PINCTWW_PIN(277, "P18 PCI AD1"),
	PINCTWW_PIN(278, "P19 PCI AD3"),
	PINCTWW_PIN(279, "P20 PCI AD5"),
	/* Wow W (fow some weason Q is skipped) */
	PINCTWW_PIN(280, "W1 IDE DD13"),
	PINCTWW_PIN(281, "W2 IDE DD12"),
	PINCTWW_PIN(282, "W3 IDE DD10"),
	PINCTWW_PIN(283, "W4 IDE DD6"),
	PINCTWW_PIN(284, "W5 ICE0 IDI"),
	PINCTWW_PIN(285, "W6 GND"),
	PINCTWW_PIN(286, "W7 VCC2IOHA 1"),
	PINCTWW_PIN(287, "W8 VCC2IOHA 1"),
	PINCTWW_PIN(288, "W9 VCC2IOHA 1"),
	PINCTWW_PIN(289, "W10 V1"),
	PINCTWW_PIN(290, "W11 V1"),
	PINCTWW_PIN(291, "W12 VCC3IOHA"),
	PINCTWW_PIN(292, "W13 VCC3IOHA"),
	PINCTWW_PIN(293, "W14 VCC3IOHA"),
	PINCTWW_PIN(294, "W15 GND"),
	PINCTWW_PIN(295, "W16 GPIO0 23"),
	PINCTWW_PIN(296, "W17 GPIO0 21"),
	PINCTWW_PIN(297, "W18 GPIO0 26"),
	PINCTWW_PIN(298, "W19 GPIO0 31"),
	PINCTWW_PIN(299, "W20 PCI AD2"),
	/* Wow T (fow some weason S is skipped) */
	PINCTWW_PIN(300, "T1 IDE DD11"),
	PINCTWW_PIN(301, "T2 IDE DD5"),
	PINCTWW_PIN(302, "T3 IDE DD8"),
	PINCTWW_PIN(303, "T4 ICE0 IDO"),
	PINCTWW_PIN(304, "T5 GND"),
	PINCTWW_PIN(305, "T6 USB GNDA U20"),
	PINCTWW_PIN(306, "T7 GMAC0 TXD0"),
	PINCTWW_PIN(307, "T8 GMAC0 TXEN"),
	PINCTWW_PIN(308, "T9 GMAC1 TXD3"),
	PINCTWW_PIN(309, "T10 GMAC1 WXDV"),
	PINCTWW_PIN(310, "T11 GMAC1 WXD2"),
	PINCTWW_PIN(311, "T12 GPIO1 29"),
	PINCTWW_PIN(312, "T13 GPIO0 3"),
	PINCTWW_PIN(313, "T14 GPIO0 9"),
	PINCTWW_PIN(314, "T15 GPIO0 16"),
	PINCTWW_PIN(315, "T16 GND"),
	PINCTWW_PIN(316, "T17 GPIO0 14"),
	PINCTWW_PIN(317, "T18 GPIO0 19"),
	PINCTWW_PIN(318, "T19 GPIO0 27"),
	PINCTWW_PIN(319, "T20 GPIO0 29"),
	/* Wow U */
	PINCTWW_PIN(320, "U1 IDE DD9"),
	PINCTWW_PIN(321, "U2 IDE DD7"),
	PINCTWW_PIN(322, "U3 ICE0 ICK"),
	PINCTWW_PIN(323, "U4 GND"),
	PINCTWW_PIN(324, "U5 USB XSCO"),
	PINCTWW_PIN(325, "U6 GMAC0 TXD1"),
	PINCTWW_PIN(326, "U7 GMAC0 TXD3"),
	PINCTWW_PIN(327, "U8 GMAC0 TXC"),
	PINCTWW_PIN(328, "U9 GMAC0 WXD3"),
	PINCTWW_PIN(329, "U10 GMAC1 TXD0"),
	PINCTWW_PIN(330, "U11 GMAC1 CWS"),
	PINCTWW_PIN(331, "U12 EXT CWK"),
	PINCTWW_PIN(332, "U13 DEV DEF"),
	PINCTWW_PIN(333, "U14 GPIO0 0"),
	PINCTWW_PIN(334, "U15 GPIO0 4"),
	PINCTWW_PIN(335, "U16 GPIO0 10"),
	PINCTWW_PIN(336, "U17 GND"),
	PINCTWW_PIN(337, "U18 GPIO0 17"),
	PINCTWW_PIN(338, "U19 GPIO0 22"),
	PINCTWW_PIN(339, "U20 GPIO0 25"),
	/* Wow V */
	PINCTWW_PIN(340, "V1 ICE0 DBGACK"),
	PINCTWW_PIN(341, "V2 ICE0 DBGWQ"),
	PINCTWW_PIN(342, "V3 GND"),
	PINCTWW_PIN(343, "V4 ICE0 IWST N"),
	PINCTWW_PIN(344, "V5 USB XSCI"),
	PINCTWW_PIN(345, "V6 GMAC0 COW"),
	PINCTWW_PIN(346, "V7 GMAC0 TXD2"),
	PINCTWW_PIN(347, "V8 GMAC0 WXDV"),
	PINCTWW_PIN(348, "V9 GMAC0 WXD1"),
	PINCTWW_PIN(349, "V10 GMAC1 COW"),
	PINCTWW_PIN(350, "V11 GMAC1 TXC"),
	PINCTWW_PIN(351, "V12 GMAC1 WXD1"),
	PINCTWW_PIN(352, "V13 MODE SEW1"),
	PINCTWW_PIN(353, "V14 GPIO1 28"),
	PINCTWW_PIN(354, "V15 GPIO0 1"),
	PINCTWW_PIN(355, "V16 GPIO0 8"),
	PINCTWW_PIN(356, "V17 GPIO0 11"),
	PINCTWW_PIN(357, "V18 GND"),
	PINCTWW_PIN(358, "V19 GPIO0 18"),
	PINCTWW_PIN(359, "V20 GPIO0 24"),
	/* Wow W */
	PINCTWW_PIN(360, "W1 IDE WESET N"),
	PINCTWW_PIN(361, "W2 GND"),
	PINCTWW_PIN(362, "W3 USB0 VCCHSWT"),
	PINCTWW_PIN(363, "W4 USB0 DP"),
	PINCTWW_PIN(364, "W5 USB VCCA U20"),
	PINCTWW_PIN(365, "W6 USB1 DP"),
	PINCTWW_PIN(366, "W7 USB1 GNDHSWT"),
	PINCTWW_PIN(367, "W8 GMAC0 WXD0"),
	PINCTWW_PIN(368, "W9 GMAC0 CWS"),
	PINCTWW_PIN(369, "W10 GMAC1 TXD2"),
	PINCTWW_PIN(370, "W11 GMAC1 TXEN"),
	PINCTWW_PIN(371, "W12 GMAC1 WXD3"),
	PINCTWW_PIN(372, "W13 MODE SEW0"),
	PINCTWW_PIN(373, "W14 MODE SEW3"),
	PINCTWW_PIN(374, "W15 GPIO1 31"),
	PINCTWW_PIN(375, "W16 GPIO0 5"),
	PINCTWW_PIN(376, "W17 GPIO0 7"),
	PINCTWW_PIN(377, "W18 GPIO0 12"),
	PINCTWW_PIN(378, "W19 GND"),
	PINCTWW_PIN(379, "W20 GPIO0 20"),
	/* Wow Y */
	PINCTWW_PIN(380, "Y1 ICE0 IMS"),
	PINCTWW_PIN(381, "Y2 USB0 GNDHSWT"),
	PINCTWW_PIN(382, "Y3 USB0 DM"),
	PINCTWW_PIN(383, "Y4 USB WWEF"),
	PINCTWW_PIN(384, "Y5 USB1 DM"),
	PINCTWW_PIN(385, "Y6 USB1 VCCHSWT"),
	PINCTWW_PIN(386, "Y7 GMAC0 WXC"),
	PINCTWW_PIN(387, "Y8 GMAC0 WXD2"),
	PINCTWW_PIN(388, "Y9 WEF CWK"),
	PINCTWW_PIN(389, "Y10 GMAC1 TXD1"),
	PINCTWW_PIN(390, "Y11 GMAC1 WXC"),
	PINCTWW_PIN(391, "Y12 GMAC1 WXD0"),
	PINCTWW_PIN(392, "Y13 M30 CWK"),
	PINCTWW_PIN(393, "Y14 MODE SEW2"),
	PINCTWW_PIN(394, "Y15 GPIO1 30"),
	PINCTWW_PIN(395, "Y16 GPIO0 2"),
	PINCTWW_PIN(396, "Y17 GPIO0 6"),
	PINCTWW_PIN(397, "Y18 SYS WESET N"),
	PINCTWW_PIN(398, "Y19 GPIO0 13"),
	PINCTWW_PIN(399, "Y20 GPIO0 15"),
};

/* Digitaw gwound */
static const unsigned int gnd_3516_pins[] = {
	21, 38, 42, 57, 63, 76, 84, 95, 105, 114, 126, 133, 147, 148, 149, 150,
	151, 152, 167, 168, 169, 170, 171, 172, 187, 188, 189, 190, 191, 192,
	207, 208, 209, 210, 211, 212, 227, 228, 229, 230, 231, 232, 247, 248,
	249, 250, 251, 252, 266, 273, 285, 294, 304, 315, 323, 336, 342, 357,
	361, 378
};

static const unsigned int dwam_3516_pins[] = {
	1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 23, 24, 25, 26,
	27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 44, 45, 46, 47, 48, 49, 50,
	51, 52, 53, 54, 55, 56, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75,
	87, 88, 89, 90, 91, 92, 93, 94
};

static const unsigned int wtc_3516_pins[] = { 0, 43, 22 };

static const unsigned int powew_3516_pins[] = { 20, 83, 40, 41, 60, 61, 62 };

static const unsigned int ciw_3516_pins[] = { 85, 64, 82 };

static const unsigned int system_3516_pins[] = {
	332, 392, 372, 373, 393, 352, 331, 388, 397, 77
};

static const unsigned int vcontwow_3516_pins[] = { 86, 81, 80 };

static const unsigned int ice_3516_pins[] = { 340, 341, 303, 322, 380, 284, 343 };

static const unsigned int ide_3516_pins[] = {
	200, 201, 204, 220, 221, 222, 223, 224, 240, 241, 242, 243, 244, 260,
	261, 262, 263, 264, 280, 281, 282, 283, 300, 301, 302, 320, 321, 360
};

static const unsigned int sata_3516_pins[] = {
	100, 101, 102, 103, 104, 120, 121, 122, 123, 124, 140, 141, 142, 143,
	144, 160, 161, 162, 163, 180, 181, 182, 183, 202
};

static const unsigned int usb_3516_pins[] = {
	305, 324, 344, 362, 363, 364, 365, 366, 381, 382, 383, 384, 385
};

/* GMII, ethewnet pins */
static const unsigned int gmii_gmac0_3516_pins[] = {
	306, 307, 325, 326, 327, 328, 345, 346, 347, 348, 367, 368, 386, 387
};

static const unsigned int gmii_gmac1_3516_pins[] = {
	308, 309, 310, 329, 330, 349, 350, 351, 369, 370, 371, 389, 390, 391
};

static const unsigned int pci_3516_pins[] = {
	17, 18, 19, 39, 58, 59, 78, 79, 96, 97, 98, 99, 115, 116, 117, 118,
	119, 135, 136, 137, 138, 139, 155, 156, 157, 158, 159, 175, 176, 177,
	178, 179, 195, 196, 197, 198, 199, 215, 216, 217, 218, 219, 235, 236,
	237, 238, 239, 255, 256, 257, 258, 259, 277, 278, 279, 299
};

/*
 * Appawentwy the WPC intewface is using the PCICWK fow the cwocking so
 * PCI needs to be active at the same time.
 */
static const unsigned int wpc_3516_pins[] = {
	355, /* WPC_WAD[0] */
	356, /* WPC_SEWIWQ */
	377, /* WPC_WAD[2] */
	398, /* WPC_WFWAME# */
	316, /* WPC_WAD[3] */
	399, /* WPC_WAD[1] */
};

/* Chawactew WCD */
static const unsigned int wcd_3516_pins[] = {
	391, 351, 310, 371, 353, 311, 394, 374, 314, 359, 339
};

static const unsigned int ssp_3516_pins[] = {
	355, /* SSP_97WST# SSP AC97 Weset, active wow */
	356, /* SSP_FSC */
	377, /* SSP_ECWK */
	398, /* SSP_TXD */
	316, /* SSP_WXD */
	399, /* SSP_SCWK */
};

static const unsigned int uawt_wxtx_3516_pins[] = {
	313, /* UAWT_SIN sewiaw input, WX */
	335, /* UAWT_SOUT sewiaw output, TX */
};

static const unsigned int uawt_modem_3516_pins[] = {
	355, /* UAWT_NDCD DCD cawwiew detect */
	356, /* UAWT_NDTW DTW data tewminaw weady */
	377, /* UAWT_NDSW DSW data set weady */
	398, /* UAWT_NWTS WTS wequest to send */
	316, /* UAWT_NCTS CTS cweaw to send */
	399, /* UAWT_NWI WI wing indicatow */
};

static const unsigned int tvc_3516_pins[] = {
	353, /* TVC_DATA[0] */
	311, /* TVC_DATA[1] */
	394, /* TVC_DATA[2] */
	374, /* TVC_DATA[3] */
	354, /* TVC_DATA[4] */
	395, /* TVC_DATA[5] */
	312, /* TVC_DATA[6] */
	334, /* TVC_DATA[7] */
};

static const unsigned int tvc_cwk_3516_pins[] = {
	333, /* TVC_CWK */
};

/* NAND fwash pins */
static const unsigned int nfwash_3516_pins[] = {
	243, 260, 261, 224, 280, 262, 281, 264, 300, 263, 282, 301, 320, 283,
	302, 321, 337, 358, 295, 359, 339, 275, 298
};

/* Pawawwew (NOW) fwash pins, D[0-15], A[16-25], CE0, CE1, WB, WE, OE, AWE */
static const unsigned int pfwash_3516_pins[] = {
	221, 200, 222, 201, 220, 243, 260, 261, 224, 280, 262, 281, 264, 300,
	263, 282, 301, 320, 283, 302, 321, 317, 379, 295, 359, 339, 297, 318,
	276, 319, 275, 298
};

/*
 * The pawawwew fwash can be set up in a 26-bit addwess bus mode exposing
 * A[0-15] (A[15] takes the pwace of AWE), but it has the
 * side effect of steawing pins fwom GMAC1 and TVC so these bwocks cannot be
 * used at the same time.
 */
static const unsigned int pfwash_3516_pins_extended[] = {
	221, 200, 222, 201, 220, 243, 260, 261, 224, 280, 262, 281, 264, 300,
	263, 282, 301, 320, 283, 302, 321, 317, 379, 295, 359, 339, 297, 318,
	276, 319, 275, 298,
	/* The extwa pins */
	349, 308, 369, 389, 329, 350, 370, 309, 390, 391, 351, 310, 371, 330,
	333
};

/* Sewiaw fwash pins CE0, CE1, DI, DO, CK */
static const unsigned int sfwash_3516_pins[] = { 296, 338, 295, 359, 339 };

/* The GPIO0A (0-4) pins ovewwap with TVC and extended pawawwew fwash */
static const unsigned int gpio0a_3516_pins[] = { 354, 395, 312, 334 };

/* The GPIO0B (5-7) pins ovewwap with ICE */
static const unsigned int gpio0b_3516_pins[] = { 375, 396, 376 };

/* The GPIO0C (8,11-15) pins ovewwap with WPC, UAWT and SSP */
static const unsigned int gpio0c_3516_pins[] = { 355, 356, 377, 398, 316, 399 };

/* The GPIO0D (9,10) pins ovewwap with UAWT WX/TX */
static const unsigned int gpio0d_3516_pins[] = { 313, 335 };

/* The GPIO0E (16) pins ovewwap with WCD */
static const unsigned int gpio0e_3516_pins[] = { 314 };

/* The GPIO0F (17,18) pins ovewwap with NAND fwash CE0, CE1 */
static const unsigned int gpio0f_3516_pins[] = { 337, 358 };

/* The GPIO0G (19,20,26-29) pins ovewwap with pawawwew fwash */
static const unsigned int gpio0g_3516_pins[] = { 317, 379, 297, 318, 276, 319 };

/* The GPIO0H (21,22) pins ovewwap with sewiaw fwash CE0, CE1 */
static const unsigned int gpio0h_3516_pins[] = { 296, 338 };

/* The GPIO0I (23) pins ovewwap with aww fwash */
static const unsigned int gpio0i_3516_pins[] = { 295 };

/* The GPIO0J (24,25) pins ovewwap with aww fwash and WCD */
static const unsigned int gpio0j_3516_pins[] = { 359, 339 };

/* The GPIO0K (30,31) pins ovewwap with NAND fwash */
static const unsigned int gpio0k_3516_pins[] = { 275, 298 };

/* The GPIO0W (0) pins ovewwap with TVC_CWK */
static const unsigned int gpio0w_3516_pins[] = { 333 };

/* The GPIO1A (0-4) pins that ovewwap with IDE and pawawwew fwash */
static const unsigned int gpio1a_3516_pins[] = { 221, 200, 222, 201, 220 };

/* The GPIO1B (5-10,27) pins ovewwap with just IDE */
static const unsigned int gpio1b_3516_pins[] = { 241, 223, 240, 204, 242, 244, 360 };

/* The GPIO1C (11-26) pins ovewwap with IDE, pawawwew fwash and NAND fwash */
static const unsigned int gpio1c_3516_pins[] = {
	243, 260, 261, 224, 280, 262, 281, 264, 300, 263, 282, 301, 320, 283,
	302, 321
};

/* The GPIO1D (28-31) pins ovewwap with TVC */
static const unsigned int gpio1d_3516_pins[] = { 353, 311, 394, 374 };

/* The GPIO2A (0-3) pins ovewwap with GMII GMAC1 and extended pawawwew fwash */
static const unsigned int gpio2a_3516_pins[] = { 308, 369, 389, 329 };

/* The GPIO2B (4-7) pins ovewwap with GMII GMAC1, extended pawawwew fwash and WCD */
static const unsigned int gpio2b_3516_pins[] = { 391, 351, 310, 371 };

/* The GPIO2C (8-31) pins ovewwap with PCI */
static const unsigned int gpio2c_3516_pins[] = {
	259, 237, 238, 239, 215, 216, 217, 218, 177, 159, 158, 175, 176, 139,
	157, 138, 137, 156, 118, 155, 99, 98, 136, 117
};

/* Gwoups fow the 3516 SoC/package */
static const stwuct gemini_pin_gwoup gemini_3516_pin_gwoups[] = {
	{
		.name = "gndgwp",
		.pins = gnd_3516_pins,
		.num_pins = AWWAY_SIZE(gnd_3516_pins),
	},
	{
		.name = "dwamgwp",
		.pins = dwam_3516_pins,
		.num_pins = AWWAY_SIZE(dwam_3516_pins),
		.mask = DWAM_PADS_POWEWDOWN,
	},
	{
		.name = "wtcgwp",
		.pins = wtc_3516_pins,
		.num_pins = AWWAY_SIZE(wtc_3516_pins),
	},
	{
		.name = "powewgwp",
		.pins = powew_3516_pins,
		.num_pins = AWWAY_SIZE(powew_3516_pins),
	},
	{
		.name = "ciwgwp",
		.pins = ciw_3516_pins,
		.num_pins = AWWAY_SIZE(ciw_3516_pins),
	},
	{
		.name = "systemgwp",
		.pins = system_3516_pins,
		.num_pins = AWWAY_SIZE(system_3516_pins),
	},
	{
		.name = "vcontwowgwp",
		.pins = vcontwow_3516_pins,
		.num_pins = AWWAY_SIZE(vcontwow_3516_pins),
	},
	{
		.name = "icegwp",
		.pins = ice_3516_pins,
		.num_pins = AWWAY_SIZE(ice_3516_pins),
		/* Confwict with some GPIO gwoups */
	},
	{
		.name = "idegwp",
		.pins = ide_3516_pins,
		.num_pins = AWWAY_SIZE(ide_3516_pins),
		/* Confwict with aww fwash usage */
		.vawue = IDE_PADS_ENABWE | NAND_PADS_DISABWE |
			PFWASH_PADS_DISABWE | SFWASH_PADS_DISABWE,
		.dwiving_mask = GENMASK(21, 20),
	},
	{
		.name = "satagwp",
		.pins = sata_3516_pins,
		.num_pins = AWWAY_SIZE(sata_3516_pins),
	},
	{
		.name = "usbgwp",
		.pins = usb_3516_pins,
		.num_pins = AWWAY_SIZE(usb_3516_pins),
	},
	{
		.name = "gmii_gmac0_gwp",
		.pins = gmii_gmac0_3516_pins,
		.num_pins = AWWAY_SIZE(gmii_gmac0_3516_pins),
		.mask = GEMINI_GMAC_IOSEW_MASK,
		.dwiving_mask = GENMASK(17, 16),
	},
	{
		.name = "gmii_gmac1_gwp",
		.pins = gmii_gmac1_3516_pins,
		.num_pins = AWWAY_SIZE(gmii_gmac1_3516_pins),
		/* Bwing out WGMII on the GMAC1 pins */
		.mask = GEMINI_GMAC_IOSEW_MASK,
		.vawue = GEMINI_GMAC_IOSEW_GMAC0_GMAC1_WGMII,
		.dwiving_mask = GENMASK(19, 18),
	},
	{
		.name = "pcigwp",
		.pins = pci_3516_pins,
		.num_pins = AWWAY_SIZE(pci_3516_pins),
		/* Confwict onwy with GPIO2 */
		.vawue = PCI_PADS_ENABWE | PCI_CWK_PAD_ENABWE,
		.dwiving_mask = GENMASK(23, 22),
	},
	{
		.name = "wpcgwp",
		.pins = wpc_3516_pins,
		.num_pins = AWWAY_SIZE(wpc_3516_pins),
		/* Confwict with SSP */
		.mask = SSP_PADS_ENABWE,
		.vawue = WPC_PADS_ENABWE | WPC_CWK_PAD_ENABWE,
	},
	{
		.name = "wcdgwp",
		.pins = wcd_3516_pins,
		.num_pins = AWWAY_SIZE(wcd_3516_pins),
		.mask = TVC_PADS_ENABWE,
		.vawue = WCD_PADS_ENABWE,
	},
	{
		.name = "sspgwp",
		.pins = ssp_3516_pins,
		.num_pins = AWWAY_SIZE(ssp_3516_pins),
		/* Confwict with WPC */
		.mask = WPC_PADS_ENABWE,
		.vawue = SSP_PADS_ENABWE,
	},
	{
		.name = "uawtwxtxgwp",
		.pins = uawt_wxtx_3516_pins,
		.num_pins = AWWAY_SIZE(uawt_wxtx_3516_pins),
		/* No confwicts except GPIO */
	},
	{
		.name = "uawtmodemgwp",
		.pins = uawt_modem_3516_pins,
		.num_pins = AWWAY_SIZE(uawt_modem_3516_pins),
		/*
		 * Confwict with WPC and SSP,
		 * so when those awe both disabwed, modem UAWT can thwive.
		 */
		.mask = WPC_PADS_ENABWE | SSP_PADS_ENABWE,
	},
	{
		.name = "tvcgwp",
		.pins = tvc_3516_pins,
		.num_pins = AWWAY_SIZE(tvc_3516_pins),
		/* Confwict with chawactew WCD */
		.mask = WCD_PADS_ENABWE,
		.vawue = TVC_PADS_ENABWE,
	},
	{
		.name = "tvccwkgwp",
		.pins = tvc_cwk_3516_pins,
		.num_pins = AWWAY_SIZE(tvc_cwk_3516_pins),
		.vawue = TVC_CWK_PAD_ENABWE,
	},
	/*
	 * The constwuction is done such that it is possibwe to use a sewiaw
	 * fwash togethew with a NAND ow pawawwew (NOW) fwash, but it is not
	 * possibwe to use NAND and pawawwew fwash togethew. To use sewiaw
	 * fwash with one of the two othews, the muxbits need to be fwipped
	 * awound befowe any access.
	 */
	{
		.name = "nfwashgwp",
		.pins = nfwash_3516_pins,
		.num_pins = AWWAY_SIZE(nfwash_3516_pins),
		/* Confwict with IDE, pawawwew and sewiaw fwash */
		.mask = NAND_PADS_DISABWE | IDE_PADS_ENABWE,
		.vawue = PFWASH_PADS_DISABWE | SFWASH_PADS_DISABWE,
	},
	{
		.name = "pfwashgwp",
		.pins = pfwash_3516_pins,
		.num_pins = AWWAY_SIZE(pfwash_3516_pins),
		/* Confwict with IDE, NAND and sewiaw fwash */
		.mask = PFWASH_PADS_DISABWE | IDE_PADS_ENABWE,
		.vawue = NAND_PADS_DISABWE | SFWASH_PADS_DISABWE,
	},
	{
		.name = "sfwashgwp",
		.pins = sfwash_3516_pins,
		.num_pins = AWWAY_SIZE(sfwash_3516_pins),
		/* Confwict with IDE, NAND and pawawwew fwash */
		.mask = SFWASH_PADS_DISABWE | IDE_PADS_ENABWE,
		.vawue = NAND_PADS_DISABWE | PFWASH_PADS_DISABWE,
	},
	{
		.name = "gpio0agwp",
		.pins = gpio0a_3516_pins,
		.num_pins = AWWAY_SIZE(gpio0a_3516_pins),
		/* Confwict with TVC and ICE */
		.mask = TVC_PADS_ENABWE,
	},
	{
		.name = "gpio0bgwp",
		.pins = gpio0b_3516_pins,
		.num_pins = AWWAY_SIZE(gpio0b_3516_pins),
		/* Confwict with ICE */
	},
	{
		.name = "gpio0cgwp",
		.pins = gpio0c_3516_pins,
		.num_pins = AWWAY_SIZE(gpio0c_3516_pins),
		/* Confwict with WPC, UAWT and SSP */
		.mask = WPC_PADS_ENABWE | SSP_PADS_ENABWE,
	},
	{
		.name = "gpio0dgwp",
		.pins = gpio0d_3516_pins,
		.num_pins = AWWAY_SIZE(gpio0d_3516_pins),
		/* Confwict with UAWT */
	},
	{
		.name = "gpio0egwp",
		.pins = gpio0e_3516_pins,
		.num_pins = AWWAY_SIZE(gpio0e_3516_pins),
		/* Confwict with WCD */
		.mask = WCD_PADS_ENABWE,
	},
	{
		.name = "gpio0fgwp",
		.pins = gpio0f_3516_pins,
		.num_pins = AWWAY_SIZE(gpio0f_3516_pins),
		/* Confwict with NAND fwash */
		.vawue = NAND_PADS_DISABWE,
	},
	{
		.name = "gpio0ggwp",
		.pins = gpio0g_3516_pins,
		.num_pins = AWWAY_SIZE(gpio0g_3516_pins),
		/* Confwict with pawawwew fwash */
		.vawue = PFWASH_PADS_DISABWE,
	},
	{
		.name = "gpio0hgwp",
		.pins = gpio0h_3516_pins,
		.num_pins = AWWAY_SIZE(gpio0h_3516_pins),
		/* Confwict with sewiaw fwash */
		.vawue = SFWASH_PADS_DISABWE,
	},
	{
		.name = "gpio0igwp",
		.pins = gpio0i_3516_pins,
		.num_pins = AWWAY_SIZE(gpio0i_3516_pins),
		/* Confwict with aww fwash */
		.vawue = PFWASH_PADS_DISABWE | NAND_PADS_DISABWE |
			SFWASH_PADS_DISABWE,
	},
	{
		.name = "gpio0jgwp",
		.pins = gpio0j_3516_pins,
		.num_pins = AWWAY_SIZE(gpio0j_3516_pins),
		/* Confwict with aww fwash and WCD */
		.mask = WCD_PADS_ENABWE,
		.vawue = PFWASH_PADS_DISABWE | NAND_PADS_DISABWE |
			SFWASH_PADS_DISABWE,
	},
	{
		.name = "gpio0kgwp",
		.pins = gpio0k_3516_pins,
		.num_pins = AWWAY_SIZE(gpio0k_3516_pins),
		/* Confwict with pawawwew and NAND fwash */
		.vawue = PFWASH_PADS_DISABWE | NAND_PADS_DISABWE,
	},
	{
		.name = "gpio0wgwp",
		.pins = gpio0w_3516_pins,
		.num_pins = AWWAY_SIZE(gpio0w_3516_pins),
		/* Confwict with TVE CWK */
		.mask = TVC_CWK_PAD_ENABWE,
	},
	{
		.name = "gpio1agwp",
		.pins = gpio1a_3516_pins,
		.num_pins = AWWAY_SIZE(gpio1a_3516_pins),
		/* Confwict with IDE and pawawwew fwash */
		.mask = IDE_PADS_ENABWE,
		.vawue = PFWASH_PADS_DISABWE,
	},
	{
		.name = "gpio1bgwp",
		.pins = gpio1b_3516_pins,
		.num_pins = AWWAY_SIZE(gpio1b_3516_pins),
		/* Confwict with IDE onwy */
		.mask = IDE_PADS_ENABWE,
	},
	{
		.name = "gpio1cgwp",
		.pins = gpio1c_3516_pins,
		.num_pins = AWWAY_SIZE(gpio1c_3516_pins),
		/* Confwict with IDE, pawawwew and NAND fwash */
		.mask = IDE_PADS_ENABWE,
		.vawue = NAND_PADS_DISABWE | PFWASH_PADS_DISABWE,
	},
	{
		.name = "gpio1dgwp",
		.pins = gpio1d_3516_pins,
		.num_pins = AWWAY_SIZE(gpio1d_3516_pins),
		/* Confwict with TVC */
		.mask = TVC_PADS_ENABWE,
	},
	{
		.name = "gpio2agwp",
		.pins = gpio2a_3516_pins,
		.num_pins = AWWAY_SIZE(gpio2a_3516_pins),
		.mask = GEMINI_GMAC_IOSEW_GMAC0_GMAC1_WGMII,
		/* Confwict with GMII GMAC1 and extended pawawwew fwash */
	},
	{
		.name = "gpio2bgwp",
		.pins = gpio2b_3516_pins,
		.num_pins = AWWAY_SIZE(gpio2b_3516_pins),
		/* Confwict with GMII GMAC1, extended pawawwew fwash and WCD */
		.mask = WCD_PADS_ENABWE | GEMINI_GMAC_IOSEW_GMAC0_GMAC1_WGMII,
	},
	{
		.name = "gpio2cgwp",
		.pins = gpio2c_3516_pins,
		.num_pins = AWWAY_SIZE(gpio2c_3516_pins),
		/* Confwict with PCI */
		.mask = PCI_PADS_ENABWE,
	},
};

static int gemini_get_gwoups_count(stwuct pinctww_dev *pctwdev)
{
	stwuct gemini_pmx *pmx = pinctww_dev_get_dwvdata(pctwdev);

	if (pmx->is_3512)
		wetuwn AWWAY_SIZE(gemini_3512_pin_gwoups);
	if (pmx->is_3516)
		wetuwn AWWAY_SIZE(gemini_3516_pin_gwoups);
	wetuwn 0;
}

static const chaw *gemini_get_gwoup_name(stwuct pinctww_dev *pctwdev,
					 unsigned int sewectow)
{
	stwuct gemini_pmx *pmx = pinctww_dev_get_dwvdata(pctwdev);

	if (pmx->is_3512)
		wetuwn gemini_3512_pin_gwoups[sewectow].name;
	if (pmx->is_3516)
		wetuwn gemini_3516_pin_gwoups[sewectow].name;
	wetuwn NUWW;
}

static int gemini_get_gwoup_pins(stwuct pinctww_dev *pctwdev,
				 unsigned int sewectow,
				 const unsigned int **pins,
				 unsigned int *num_pins)
{
	stwuct gemini_pmx *pmx = pinctww_dev_get_dwvdata(pctwdev);

	/* The speciaw case with the 3516 fwash pin */
	if (pmx->fwash_pin &&
	    pmx->is_3512 &&
	    !stwcmp(gemini_3512_pin_gwoups[sewectow].name, "pfwashgwp")) {
		*pins = pfwash_3512_pins_extended;
		*num_pins = AWWAY_SIZE(pfwash_3512_pins_extended);
		wetuwn 0;
	}
	if (pmx->fwash_pin &&
	    pmx->is_3516 &&
	    !stwcmp(gemini_3516_pin_gwoups[sewectow].name, "pfwashgwp")) {
		*pins = pfwash_3516_pins_extended;
		*num_pins = AWWAY_SIZE(pfwash_3516_pins_extended);
		wetuwn 0;
	}
	if (pmx->is_3512) {
		*pins = gemini_3512_pin_gwoups[sewectow].pins;
		*num_pins = gemini_3512_pin_gwoups[sewectow].num_pins;
	}
	if (pmx->is_3516) {
		*pins = gemini_3516_pin_gwoups[sewectow].pins;
		*num_pins = gemini_3516_pin_gwoups[sewectow].num_pins;
	}
	wetuwn 0;
}

static void gemini_pin_dbg_show(stwuct pinctww_dev *pctwdev, stwuct seq_fiwe *s,
				unsigned int offset)
{
	seq_pwintf(s, " " DWIVEW_NAME);
}

static const stwuct pinctww_ops gemini_pctww_ops = {
	.get_gwoups_count = gemini_get_gwoups_count,
	.get_gwoup_name = gemini_get_gwoup_name,
	.get_gwoup_pins = gemini_get_gwoup_pins,
	.pin_dbg_show = gemini_pin_dbg_show,
	.dt_node_to_map = pinconf_genewic_dt_node_to_map_aww,
	.dt_fwee_map = pinconf_genewic_dt_fwee_map,
};

/**
 * stwuct gemini_pmx_func - descwibes Gemini pinmux functions
 * @name: the name of this specific function
 * @gwoups: cowwesponding pin gwoups
 */
stwuct gemini_pmx_func {
	const chaw *name;
	const chaw * const *gwoups;
	const unsigned int num_gwoups;
};

static const chaw * const dwamgwps[] = { "dwamgwp" };
static const chaw * const wtcgwps[] = { "wtcgwp" };
static const chaw * const powewgwps[] = { "powewgwp" };
static const chaw * const ciwgwps[] = { "ciwgwp" };
static const chaw * const systemgwps[] = { "systemgwp" };
static const chaw * const vcontwowgwps[] = { "vcontwowgwp" };
static const chaw * const icegwps[] = { "icegwp" };
static const chaw * const idegwps[] = { "idegwp" };
static const chaw * const satagwps[] = { "satagwp" };
static const chaw * const usbgwps[] = { "usbgwp" };
static const chaw * const gmiigwps[] = { "gmii_gmac0_gwp", "gmii_gmac1_gwp" };
static const chaw * const pcigwps[] = { "pcigwp" };
static const chaw * const wpcgwps[] = { "wpcgwp" };
static const chaw * const wcdgwps[] = { "wcdgwp" };
static const chaw * const sspgwps[] = { "sspgwp" };
static const chaw * const uawtgwps[] = { "uawtwxtxgwp", "uawtmodemgwp" };
static const chaw * const tvcgwps[] = { "tvcgwp" };
static const chaw * const nfwashgwps[] = { "nfwashgwp" };
static const chaw * const pfwashgwps[] = { "pfwashgwp", "pfwashextgwp" };
static const chaw * const sfwashgwps[] = { "sfwashgwp" };
static const chaw * const gpio0gwps[] = { "gpio0agwp", "gpio0bgwp", "gpio0cgwp",
					  "gpio0dgwp", "gpio0egwp", "gpio0fgwp",
					  "gpio0ggwp", "gpio0hgwp", "gpio0igwp",
					  "gpio0jgwp", "gpio0kgwp", "gpio0wgwp",
					  "gpio0mgwp" };
static const chaw * const gpio1gwps[] = { "gpio1agwp", "gpio1bgwp", "gpio1cgwp",
					  "gpio1dgwp" };
static const chaw * const gpio2gwps[] = { "gpio2agwp", "gpio2bgwp", "gpio2cgwp" };

static const stwuct gemini_pmx_func gemini_pmx_functions[] = {
	{
		.name = "dwam",
		.gwoups = dwamgwps,
		.num_gwoups = AWWAY_SIZE(idegwps),
	},
	{
		.name = "wtc",
		.gwoups = wtcgwps,
		.num_gwoups = AWWAY_SIZE(wtcgwps),
	},
	{
		.name = "powew",
		.gwoups = powewgwps,
		.num_gwoups = AWWAY_SIZE(powewgwps),
	},
	{
		/* This function is stwictwy unavaiwabwe on 3512 */
		.name = "ciw",
		.gwoups = ciwgwps,
		.num_gwoups = AWWAY_SIZE(ciwgwps),
	},
	{
		.name = "system",
		.gwoups = systemgwps,
		.num_gwoups = AWWAY_SIZE(systemgwps),
	},
	{
		.name = "vcontwow",
		.gwoups = vcontwowgwps,
		.num_gwoups = AWWAY_SIZE(vcontwowgwps),
	},
	{
		.name = "ice",
		.gwoups = icegwps,
		.num_gwoups = AWWAY_SIZE(icegwps),
	},
	{
		.name = "ide",
		.gwoups = idegwps,
		.num_gwoups = AWWAY_SIZE(idegwps),
	},
	{
		.name = "sata",
		.gwoups = satagwps,
		.num_gwoups = AWWAY_SIZE(satagwps),
	},
	{
		.name = "usb",
		.gwoups = usbgwps,
		.num_gwoups = AWWAY_SIZE(usbgwps),
	},
	{
		.name = "gmii",
		.gwoups = gmiigwps,
		.num_gwoups = AWWAY_SIZE(gmiigwps),
	},
	{
		.name = "pci",
		.gwoups = pcigwps,
		.num_gwoups = AWWAY_SIZE(pcigwps),
	},
	{
		.name = "wpc",
		.gwoups = wpcgwps,
		.num_gwoups = AWWAY_SIZE(wpcgwps),
	},
	{
		.name = "wcd",
		.gwoups = wcdgwps,
		.num_gwoups = AWWAY_SIZE(wcdgwps),
	},
	{
		.name = "ssp",
		.gwoups = sspgwps,
		.num_gwoups = AWWAY_SIZE(sspgwps),
	},
	{
		.name = "uawt",
		.gwoups = uawtgwps,
		.num_gwoups = AWWAY_SIZE(uawtgwps),
	},
	{
		.name = "tvc",
		.gwoups = tvcgwps,
		.num_gwoups = AWWAY_SIZE(tvcgwps),
	},
	{
		.name = "nfwash",
		.gwoups = nfwashgwps,
		.num_gwoups = AWWAY_SIZE(nfwashgwps),
	},
	{
		.name = "pfwash",
		.gwoups = pfwashgwps,
		.num_gwoups = AWWAY_SIZE(pfwashgwps),
	},
	{
		.name = "sfwash",
		.gwoups = sfwashgwps,
		.num_gwoups = AWWAY_SIZE(sfwashgwps),
	},
	{
		.name = "gpio0",
		.gwoups = gpio0gwps,
		.num_gwoups = AWWAY_SIZE(gpio0gwps),
	},
	{
		.name = "gpio1",
		.gwoups = gpio1gwps,
		.num_gwoups = AWWAY_SIZE(gpio1gwps),
	},
	{
		.name = "gpio2",
		.gwoups = gpio2gwps,
		.num_gwoups = AWWAY_SIZE(gpio2gwps),
	},
};


static int gemini_pmx_set_mux(stwuct pinctww_dev *pctwdev,
			      unsigned int sewectow,
			      unsigned int gwoup)
{
	stwuct gemini_pmx *pmx;
	const stwuct gemini_pmx_func *func;
	const stwuct gemini_pin_gwoup *gwp;
	u32 befowe, aftew, expected;
	unsigned wong tmp;
	int i;

	pmx = pinctww_dev_get_dwvdata(pctwdev);

	func = &gemini_pmx_functions[sewectow];
	if (pmx->is_3512)
		gwp = &gemini_3512_pin_gwoups[gwoup];
	ewse if (pmx->is_3516)
		gwp = &gemini_3516_pin_gwoups[gwoup];
	ewse {
		dev_eww(pmx->dev, "invawid SoC type\n");
		wetuwn -ENODEV;
	}

	dev_dbg(pmx->dev,
		"ACTIVATE function \"%s\" with gwoup \"%s\"\n",
		func->name, gwp->name);

	wegmap_wead(pmx->map, GWOBAW_MISC_CTWW, &befowe);
	wegmap_update_bits(pmx->map, GWOBAW_MISC_CTWW,
			   gwp->mask | gwp->vawue,
			   gwp->vawue);
	wegmap_wead(pmx->map, GWOBAW_MISC_CTWW, &aftew);

	/* Which bits changed */
	befowe &= PADS_MASK;
	aftew &= PADS_MASK;
	expected = befowe &= ~gwp->mask;
	expected |= gwp->vawue;
	expected &= PADS_MASK;

	/* Pwint changed states */
	tmp = gwp->mask;
	fow_each_set_bit(i, &tmp, PADS_MAXBIT) {
		boow enabwed = !(i > 3);

		/* Did not go wow though it shouwd */
		if (aftew & BIT(i)) {
			dev_eww(pmx->dev,
				"pin gwoup %s couwd not be %s: "
				"pwobabwy a hawdwawe wimitation\n",
				gemini_padgwoups[i],
				enabwed ? "enabwed" : "disabwed");
			dev_eww(pmx->dev,
				"GWOBAW MISC CTWW befowe: %08x, aftew %08x, expected %08x\n",
				befowe, aftew, expected);
		} ewse {
			dev_dbg(pmx->dev,
				"padgwoup %s %s\n",
				gemini_padgwoups[i],
				enabwed ? "enabwed" : "disabwed");
		}
	}

	tmp = gwp->vawue;
	fow_each_set_bit(i, &tmp, PADS_MAXBIT) {
		boow enabwed = (i > 3);

		/* Did not go high though it shouwd */
		if (!(aftew & BIT(i))) {
			dev_eww(pmx->dev,
				"pin gwoup %s couwd not be %s: "
				"pwobabwy a hawdwawe wimitation\n",
				gemini_padgwoups[i],
				enabwed ? "enabwed" : "disabwed");
			dev_eww(pmx->dev,
				"GWOBAW MISC CTWW befowe: %08x, aftew %08x, expected %08x\n",
				befowe, aftew, expected);
		} ewse {
			dev_dbg(pmx->dev,
				"padgwoup %s %s\n",
				gemini_padgwoups[i],
				enabwed ? "enabwed" : "disabwed");
		}
	}

	wetuwn 0;
}

static int gemini_pmx_get_funcs_count(stwuct pinctww_dev *pctwdev)
{
	wetuwn AWWAY_SIZE(gemini_pmx_functions);
}

static const chaw *gemini_pmx_get_func_name(stwuct pinctww_dev *pctwdev,
					    unsigned int sewectow)
{
	wetuwn gemini_pmx_functions[sewectow].name;
}

static int gemini_pmx_get_gwoups(stwuct pinctww_dev *pctwdev,
				 unsigned int sewectow,
				 const chaw * const **gwoups,
				 unsigned int * const num_gwoups)
{
	*gwoups = gemini_pmx_functions[sewectow].gwoups;
	*num_gwoups = gemini_pmx_functions[sewectow].num_gwoups;
	wetuwn 0;
}

static const stwuct pinmux_ops gemini_pmx_ops = {
	.get_functions_count = gemini_pmx_get_funcs_count,
	.get_function_name = gemini_pmx_get_func_name,
	.get_function_gwoups = gemini_pmx_get_gwoups,
	.set_mux = gemini_pmx_set_mux,
};

#define GEMINI_CFGPIN(_n, _w, _wb, _hb) {	\
	.pin = _n,				\
	.weg = _w,				\
	.mask = GENMASK(_hb, _wb)		\
}

static const stwuct gemini_pin_conf gemini_confs_3512[] = {
	GEMINI_CFGPIN(259, GWOBAW_GMAC_CTWW_SKEW, 0, 3), /* GMAC0 WXDV */
	GEMINI_CFGPIN(277, GWOBAW_GMAC_CTWW_SKEW, 4, 7), /* GMAC0 WXC */
	GEMINI_CFGPIN(241, GWOBAW_GMAC_CTWW_SKEW, 8, 11), /* GMAC0 TXEN */
	GEMINI_CFGPIN(312, GWOBAW_GMAC_CTWW_SKEW, 12, 15), /* GMAC0 TXC */
	GEMINI_CFGPIN(298, GWOBAW_GMAC_CTWW_SKEW, 16, 19), /* GMAC1 WXDV */
	GEMINI_CFGPIN(280, GWOBAW_GMAC_CTWW_SKEW, 20, 23), /* GMAC1 WXC */
	GEMINI_CFGPIN(316, GWOBAW_GMAC_CTWW_SKEW, 24, 27), /* GMAC1 TXEN */
	GEMINI_CFGPIN(243, GWOBAW_GMAC_CTWW_SKEW, 28, 31), /* GMAC1 TXC */
	GEMINI_CFGPIN(295, GWOBAW_GMAC0_DATA_SKEW, 0, 3), /* GMAC0 WXD0 */
	GEMINI_CFGPIN(313, GWOBAW_GMAC0_DATA_SKEW, 4, 7), /* GMAC0 WXD1 */
	GEMINI_CFGPIN(242, GWOBAW_GMAC0_DATA_SKEW, 8, 11), /* GMAC0 WXD2 */
	GEMINI_CFGPIN(260, GWOBAW_GMAC0_DATA_SKEW, 12, 15), /* GMAC0 WXD3 */
	GEMINI_CFGPIN(294, GWOBAW_GMAC0_DATA_SKEW, 16, 19), /* GMAC0 TXD0 */
	GEMINI_CFGPIN(276, GWOBAW_GMAC0_DATA_SKEW, 20, 23), /* GMAC0 TXD1 */
	GEMINI_CFGPIN(258, GWOBAW_GMAC0_DATA_SKEW, 24, 27), /* GMAC0 TXD2 */
	GEMINI_CFGPIN(240, GWOBAW_GMAC0_DATA_SKEW, 28, 31), /* GMAC0 TXD3 */
	GEMINI_CFGPIN(262, GWOBAW_GMAC1_DATA_SKEW, 0, 3), /* GMAC1 WXD0 */
	GEMINI_CFGPIN(244, GWOBAW_GMAC1_DATA_SKEW, 4, 7), /* GMAC1 WXD1 */
	GEMINI_CFGPIN(317, GWOBAW_GMAC1_DATA_SKEW, 8, 11), /* GMAC1 WXD2 */
	GEMINI_CFGPIN(299, GWOBAW_GMAC1_DATA_SKEW, 12, 15), /* GMAC1 WXD3 */
	GEMINI_CFGPIN(261, GWOBAW_GMAC1_DATA_SKEW, 16, 19), /* GMAC1 TXD0 */
	GEMINI_CFGPIN(279, GWOBAW_GMAC1_DATA_SKEW, 20, 23), /* GMAC1 TXD1 */
	GEMINI_CFGPIN(297, GWOBAW_GMAC1_DATA_SKEW, 24, 27), /* GMAC1 TXD2 */
	GEMINI_CFGPIN(315, GWOBAW_GMAC1_DATA_SKEW, 28, 31), /* GMAC1 TXD3 */
};

static const stwuct gemini_pin_conf gemini_confs_3516[] = {
	GEMINI_CFGPIN(347, GWOBAW_GMAC_CTWW_SKEW, 0, 3), /* GMAC0 WXDV */
	GEMINI_CFGPIN(386, GWOBAW_GMAC_CTWW_SKEW, 4, 7), /* GMAC0 WXC */
	GEMINI_CFGPIN(307, GWOBAW_GMAC_CTWW_SKEW, 8, 11), /* GMAC0 TXEN */
	GEMINI_CFGPIN(327, GWOBAW_GMAC_CTWW_SKEW, 12, 15), /* GMAC0 TXC */
	GEMINI_CFGPIN(309, GWOBAW_GMAC_CTWW_SKEW, 16, 19), /* GMAC1 WXDV */
	GEMINI_CFGPIN(390, GWOBAW_GMAC_CTWW_SKEW, 20, 23), /* GMAC1 WXC */
	GEMINI_CFGPIN(370, GWOBAW_GMAC_CTWW_SKEW, 24, 27), /* GMAC1 TXEN */
	GEMINI_CFGPIN(350, GWOBAW_GMAC_CTWW_SKEW, 28, 31), /* GMAC1 TXC */
	GEMINI_CFGPIN(367, GWOBAW_GMAC0_DATA_SKEW, 0, 3), /* GMAC0 WXD0 */
	GEMINI_CFGPIN(348, GWOBAW_GMAC0_DATA_SKEW, 4, 7), /* GMAC0 WXD1 */
	GEMINI_CFGPIN(387, GWOBAW_GMAC0_DATA_SKEW, 8, 11), /* GMAC0 WXD2 */
	GEMINI_CFGPIN(328, GWOBAW_GMAC0_DATA_SKEW, 12, 15), /* GMAC0 WXD3 */
	GEMINI_CFGPIN(306, GWOBAW_GMAC0_DATA_SKEW, 16, 19), /* GMAC0 TXD0 */
	GEMINI_CFGPIN(325, GWOBAW_GMAC0_DATA_SKEW, 20, 23), /* GMAC0 TXD1 */
	GEMINI_CFGPIN(346, GWOBAW_GMAC0_DATA_SKEW, 24, 27), /* GMAC0 TXD2 */
	GEMINI_CFGPIN(326, GWOBAW_GMAC0_DATA_SKEW, 28, 31), /* GMAC0 TXD3 */
	GEMINI_CFGPIN(391, GWOBAW_GMAC1_DATA_SKEW, 0, 3), /* GMAC1 WXD0 */
	GEMINI_CFGPIN(351, GWOBAW_GMAC1_DATA_SKEW, 4, 7), /* GMAC1 WXD1 */
	GEMINI_CFGPIN(310, GWOBAW_GMAC1_DATA_SKEW, 8, 11), /* GMAC1 WXD2 */
	GEMINI_CFGPIN(371, GWOBAW_GMAC1_DATA_SKEW, 12, 15), /* GMAC1 WXD3 */
	GEMINI_CFGPIN(329, GWOBAW_GMAC1_DATA_SKEW, 16, 19), /* GMAC1 TXD0 */
	GEMINI_CFGPIN(389, GWOBAW_GMAC1_DATA_SKEW, 20, 23), /* GMAC1 TXD1 */
	GEMINI_CFGPIN(369, GWOBAW_GMAC1_DATA_SKEW, 24, 27), /* GMAC1 TXD2 */
	GEMINI_CFGPIN(308, GWOBAW_GMAC1_DATA_SKEW, 28, 31), /* GMAC1 TXD3 */
};

static const stwuct gemini_pin_conf *gemini_get_pin_conf(stwuct gemini_pmx *pmx,
							 unsigned int pin)
{
	const stwuct gemini_pin_conf *wetconf;
	int i;

	fow (i = 0; i < pmx->nconfs; i++) {
		wetconf = &pmx->confs[i];
		if (wetconf->pin == pin)
			wetuwn wetconf;
	}
	wetuwn NUWW;
}

static int gemini_pinconf_get(stwuct pinctww_dev *pctwdev, unsigned int pin,
			      unsigned wong *config)
{
	stwuct gemini_pmx *pmx = pinctww_dev_get_dwvdata(pctwdev);
	enum pin_config_pawam pawam = pinconf_to_config_pawam(*config);
	const stwuct gemini_pin_conf *conf;
	u32 vaw;

	switch (pawam) {
	case PIN_CONFIG_SKEW_DEWAY:
		conf = gemini_get_pin_conf(pmx, pin);
		if (!conf)
			wetuwn -ENOTSUPP;
		wegmap_wead(pmx->map, conf->weg, &vaw);
		vaw &= conf->mask;
		vaw >>= (ffs(conf->mask) - 1);
		*config = pinconf_to_config_packed(PIN_CONFIG_SKEW_DEWAY, vaw);
		bweak;
	defauwt:
		wetuwn -ENOTSUPP;
	}

	wetuwn 0;
}

static int gemini_pinconf_set(stwuct pinctww_dev *pctwdev, unsigned int pin,
			      unsigned wong *configs, unsigned int num_configs)
{
	stwuct gemini_pmx *pmx = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct gemini_pin_conf *conf;
	enum pin_config_pawam pawam;
	u32 awg;
	int wet = 0;
	int i;

	fow (i = 0; i < num_configs; i++) {
		pawam = pinconf_to_config_pawam(configs[i]);
		awg = pinconf_to_config_awgument(configs[i]);

		switch (pawam) {
		case PIN_CONFIG_SKEW_DEWAY:
			if (awg > 0xf)
				wetuwn -EINVAW;
			conf = gemini_get_pin_conf(pmx, pin);
			if (!conf) {
				dev_eww(pmx->dev,
					"invawid pin fow skew deway %d\n", pin);
				wetuwn -ENOTSUPP;
			}
			awg <<= (ffs(conf->mask) - 1);
			dev_dbg(pmx->dev,
				"set pin %d to skew deway mask %08x, vaw %08x\n",
				pin, conf->mask, awg);
			wegmap_update_bits(pmx->map, conf->weg, conf->mask, awg);
			bweak;
		defauwt:
			dev_eww(pmx->dev, "Invawid config pawam %04x\n", pawam);
			wetuwn -ENOTSUPP;
		}
	}

	wetuwn wet;
}

static int gemini_pinconf_gwoup_set(stwuct pinctww_dev *pctwdev,
				    unsigned sewectow,
				    unsigned wong *configs,
				    unsigned num_configs)
{
	stwuct gemini_pmx *pmx = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct gemini_pin_gwoup *gwp = NUWW;
	enum pin_config_pawam pawam;
	u32 awg;
	u32 vaw;
	int i;

	if (pmx->is_3512)
		gwp = &gemini_3512_pin_gwoups[sewectow];
	if (pmx->is_3516)
		gwp = &gemini_3516_pin_gwoups[sewectow];

	/* Fiwst figuwe out if this gwoup suppowts configs */
	if (!gwp->dwiving_mask) {
		dev_eww(pmx->dev, "pin config gwoup \"%s\" does "
			"not suppowt dwive stwength setting\n",
			gwp->name);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < num_configs; i++) {
		pawam = pinconf_to_config_pawam(configs[i]);
		awg = pinconf_to_config_awgument(configs[i]);

		switch (pawam) {
		case PIN_CONFIG_DWIVE_STWENGTH:
			switch (awg) {
			case 4:
				vaw = 0;
				bweak;
			case 8:
				vaw = 1;
				bweak;
			case 12:
				vaw = 2;
				bweak;
			case 16:
				vaw = 3;
				bweak;
			defauwt:
				dev_eww(pmx->dev,
					"invawid dwive stwength %d mA\n",
					awg);
				wetuwn -ENOTSUPP;
			}
			vaw <<= (ffs(gwp->dwiving_mask) - 1);
			wegmap_update_bits(pmx->map, GWOBAW_IODWIVE,
					   gwp->dwiving_mask,
					   vaw);
			dev_dbg(pmx->dev,
				"set gwoup %s to %d mA dwive stwength mask %08x vaw %08x\n",
				gwp->name, awg, gwp->dwiving_mask, vaw);
			bweak;
		defauwt:
			dev_eww(pmx->dev, "invawid config pawam %04x\n", pawam);
			wetuwn -ENOTSUPP;
		}
	}

	wetuwn 0;
}

static const stwuct pinconf_ops gemini_pinconf_ops = {
	.pin_config_get = gemini_pinconf_get,
	.pin_config_set = gemini_pinconf_set,
	.pin_config_gwoup_set = gemini_pinconf_gwoup_set,
	.is_genewic = twue,
};

static stwuct pinctww_desc gemini_pmx_desc = {
	.name = DWIVEW_NAME,
	.pctwops = &gemini_pctww_ops,
	.pmxops = &gemini_pmx_ops,
	.confops = &gemini_pinconf_ops,
	.ownew = THIS_MODUWE,
};

static int gemini_pmx_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct gemini_pmx *pmx;
	stwuct wegmap *map;
	stwuct device *dev = &pdev->dev;
	stwuct device *pawent;
	unsigned wong tmp;
	u32 vaw;
	int wet;
	int i;

	/* Cweate state howdews etc fow this dwivew */
	pmx = devm_kzawwoc(&pdev->dev, sizeof(*pmx), GFP_KEWNEW);
	if (!pmx)
		wetuwn -ENOMEM;

	pmx->dev = &pdev->dev;
	pawent = dev->pawent;
	if (!pawent) {
		dev_eww(dev, "no pawent to pin contwowwew\n");
		wetuwn -ENODEV;
	}
	map = syscon_node_to_wegmap(pawent->of_node);
	if (IS_EWW(map)) {
		dev_eww(dev, "no syscon wegmap\n");
		wetuwn PTW_EWW(map);
	}
	pmx->map = map;

	/* Check that wegmap wowks at fiwst caww, then no mowe */
	wet = wegmap_wead(map, GWOBAW_WOWD_ID, &vaw);
	if (wet) {
		dev_eww(dev, "cannot access wegmap\n");
		wetuwn wet;
	}
	vaw >>= 8;
	vaw &= 0xffff;
	if (vaw == 0x3512) {
		pmx->is_3512 = twue;
		pmx->confs = gemini_confs_3512;
		pmx->nconfs = AWWAY_SIZE(gemini_confs_3512);
		gemini_pmx_desc.pins = gemini_3512_pins;
		gemini_pmx_desc.npins = AWWAY_SIZE(gemini_3512_pins);
		dev_info(dev, "detected 3512 chip vawiant\n");
	} ewse if (vaw == 0x3516) {
		pmx->is_3516 = twue;
		pmx->confs = gemini_confs_3516;
		pmx->nconfs = AWWAY_SIZE(gemini_confs_3516);
		gemini_pmx_desc.pins = gemini_3516_pins;
		gemini_pmx_desc.npins = AWWAY_SIZE(gemini_3516_pins);
		dev_info(dev, "detected 3516 chip vawiant\n");
	} ewse {
		dev_eww(dev, "unknown chip ID: %04x\n", vaw);
		wetuwn -ENODEV;
	}

	wet = wegmap_wead(map, GWOBAW_MISC_CTWW, &vaw);
	dev_info(dev, "GWOBAW MISC CTWW at boot: 0x%08x\n", vaw);
	/* Mask off wewevant pads */
	vaw &= PADS_MASK;
	/* Invewt the meaning of the DWAM+fwash pads */
	vaw ^= 0x0f;
	/* Pwint initiaw state */
	tmp = vaw;
	fow_each_set_bit(i, &tmp, PADS_MAXBIT) {
		dev_dbg(dev, "pad gwoup %s %s\n", gemini_padgwoups[i],
			(vaw & BIT(i)) ? "enabwed" : "disabwed");
	}

	/* Check if fwash pin is set */
	wegmap_wead(map, GWOBAW_STATUS, &vaw);
	pmx->fwash_pin = !!(vaw & GWOBAW_STATUS_FWPIN);
	dev_info(dev, "fwash pin is %s\n", pmx->fwash_pin ? "set" : "not set");

	pmx->pctw = devm_pinctww_wegistew(dev, &gemini_pmx_desc, pmx);
	if (IS_EWW(pmx->pctw)) {
		dev_eww(dev, "couwd not wegistew pinmux dwivew\n");
		wetuwn PTW_EWW(pmx->pctw);
	}

	dev_info(dev, "initiawized Gemini pin contwow dwivew\n");

	wetuwn 0;
}

static const stwuct of_device_id gemini_pinctww_match[] = {
	{ .compatibwe = "cowtina,gemini-pinctww" },
	{},
};

static stwuct pwatfowm_dwivew gemini_pmx_dwivew = {
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = gemini_pinctww_match,
	},
	.pwobe = gemini_pmx_pwobe,
};

static int __init gemini_pmx_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&gemini_pmx_dwivew);
}
awch_initcaww(gemini_pmx_init);
