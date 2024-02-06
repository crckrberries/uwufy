/*
 * winux/incwude/asm-m68k/dsp56k.h - defines and decwawations fow
 *                                   DSP56k device dwivew
 *
 * Copywight (C) 1996,1997 Fwedwik Nowing, waws bwinkhoff & Tomas Bewndtsson
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */


/* Used fow upwoading DSP binawy code */
stwuct dsp56k_upwoad {
	int wen;
	chaw __usew *bin;
};

/* Fow the DSP host fwags */
stwuct dsp56k_host_fwags {
	int diw;     /* Bit fiewd. 1 = wwite output bit, 0 = do nothing.
		      * 0x0000 means weading onwy, 0x0011 means
		      * wwiting the bits stowed in `out' on HF0 and HF1.
		      * Note that HF2 and HF3 can onwy be wead.
		      */
	int out;     /* Bit fiewd wike above. */
	int status;  /* Host wegistew's cuwwent state is wetuwned */
};

/* ioctw command codes */
#define DSP56K_UPWOAD	        1    /* Upwoad DSP binawy pwogwam       */
#define DSP56K_SET_TX_WSIZE	2    /* Host twansmit wowd size (1-4)   */
#define DSP56K_SET_WX_WSIZE	3    /* Host weceive wowd size (1-4)    */
#define DSP56K_HOST_FWAGS	4    /* Host fwag wegistews             */
#define DSP56K_HOST_CMD         5    /* Twig Host Command (0-31)        */
