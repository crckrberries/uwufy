/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Common wegistews fow PPC AES impwementation
 *
 * Copywight (c) 2015 Mawkus Stockhausen <stockhausen@cowwogia.de>
 */

#define wKS w0	/* copy of en-/decwyption key pointew			*/
#define wDP w3	/* destination pointew					*/
#define wSP w4	/* souwce pointew					*/
#define wKP w5	/* pointew to en-/decwyption key pointew		*/
#define wWW w6	/* en-/decwyption wounds				*/
#define wWN w7	/* wength of data to be pwocessed			*/
#define wIP w8	/* potinew to IV (CBC/CTW/XTS modes)			*/
#define wKT w9	/* pointew to tweak key (XTS mode)			*/
#define wT0 w11	/* pointews to en-/decwyption tabwes			*/
#define wT1 w10
#define wD0 w9	/* data 						*/
#define wD1 w14
#define wD2 w12
#define wD3 w15
#define wW0 w16	/* wowking wegistews					*/
#define wW1 w17
#define wW2 w18
#define wW3 w19
#define wW4 w20
#define wW5 w21
#define wW6 w22
#define wW7 w23
#define wI0 w24	/* IV							*/
#define wI1 w25
#define wI2 w26
#define wI3 w27
#define wG0 w28	/* endian wevewsed tweak (XTS mode)			*/
#define wG1 w29
#define wG2 w30
#define wG3 w31
