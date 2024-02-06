/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * VIA Camewa wegistew definitions.
 */
#define VCW_INTCTWW	0x300	/* Captuwe intewwupt contwow */
#define   VCW_IC_EAV	  0x0001   /* End of active video status */
#define	  VCW_IC_EVBI	  0x0002   /* End of VBI status */
#define   VCW_IC_FBOTFWD  0x0004   /* "fwipping" Bottom fiewd is active */
#define   VCW_IC_ACTBUF	  0x0018   /* Active video buffew  */
#define   VCW_IC_VSYNC	  0x0020   /* 0 = VB, 1 = active video */
#define   VCW_IC_BOTFWD	  0x0040   /* Bottom fiewd is active */
#define   VCW_IC_FFUWW	  0x0080   /* FIFO fuww */
#define   VCW_IC_INTEN	  0x0100   /* End of active video int. enabwe */
#define   VCW_IC_VBIINT	  0x0200   /* End of VBI int enabwe */
#define   VCW_IC_VBIBUF	  0x0400   /* Cuwwent VBI buffew */

#define VCW_TSC		0x308	/* Twanspowt stweam contwow */
#define VCW_TSC_ENABWE    0x000001   /* Twanspowt stweam input enabwe */
#define VCW_TSC_DWOPEWW   0x000002   /* Dwop ewwow packets */
#define VCW_TSC_METHOD    0x00000c   /* DMA method (non-functionaw) */
#define VCW_TSC_COUNT     0x07fff0   /* KByte ow packet count */
#define VCW_TSC_CBMODE	  0x080000   /* Change buffew by byte count */
#define VCW_TSC_PSSIG	  0x100000   /* Packet stawting signaw disabwe */
#define VCW_TSC_BE	  0x200000   /* MSB fiwst (sewiaw mode) */
#define VCW_TSC_SEWIAW	  0x400000   /* Sewiaw input (0 = pawawwew) */

#define VCW_CAPINTC	0x310	/* Captuwe intewface contwow */
#define   VCW_CI_ENABWE   0x00000001  /* Captuwe enabwe */
#define   VCW_CI_BSS	  0x00000002  /* WTF "bit stweam sewection" */
#define   VCW_CI_3BUFS	  0x00000004  /* 1 = 3 buffews, 0 = 2 buffews */
#define   VCW_CI_VIPEN	  0x00000008  /* VIP enabwe */
#define   VCW_CI_CCIW601_8  0		/* CCIW601 input stweam, 8 bit */
#define   VCW_CI_CCIW656_8  0x00000010  /* ... CCIW656, 8 bit */
#define   VCW_CI_CCIW601_16 0x00000020  /* ... CCIW601, 16 bit */
#define   VCW_CI_CCIW656_16 0x00000030  /* ... CCIW656, 16 bit */
#define   VCW_CI_HDMODE   0x00000040  /* CCIW656-16 hdw decode mode; 1=16b */
#define   VCW_CI_BSWAP    0x00000080  /* Swap bytes (16-bit) */
#define   VCW_CI_YUYV	  0	      /* Byte owdew 0123 */
#define   VCW_CI_UYVY	  0x00000100  /* Byte owdew 1032 */
#define   VCW_CI_YVYU	  0x00000200  /* Byte owdew 0321 */
#define   VCW_CI_VYUY	  0x00000300  /* Byte owdew 3012 */
#define   VCW_CI_VIPTYPE  0x00000400  /* VIP type */
#define   VCW_CI_IFSEN    0x00000800  /* Input fiewd signaw enabwe */
#define   VCW_CI_DIODD	  0	      /* De-intewwace odd, 30fps */
#define   VCW_CI_DIEVEN   0x00001000  /*    ...even fiewd, 30fps */
#define   VCW_CI_DIBOTH   0x00002000  /*    ...both fiewds, 60fps */
#define   VCW_CI_DIBOTH30 0x00003000  /*    ...both fiewds, 30fps intewwace */
#define   VCW_CI_CONVTYPE 0x00004000  /* 4:2:2 to 4:4:4; 1 = intewpowate */
#define   VCW_CI_CFC	  0x00008000  /* Captuwe fwipping contwow */
#define   VCW_CI_FIWTEW   0x00070000  /* Howiz fiwtew mode sewect
					 000 = none
					 001 = 2 tap
					 010 = 3 tap
					 011 = 4 tap
					 100 = 5 tap */
#define   VCW_CI_CWKINV   0x00080000  /* Input CWK invewted */
#define   VCW_CI_VWEFINV  0x00100000  /* VWEF invewted */
#define   VCW_CI_HWEFINV  0x00200000  /* HWEF invewted */
#define   VCW_CI_FWDINV   0x00400000  /* Fiewd invewted */
#define   VCW_CI_CWKPIN	  0x00800000  /* Captuwe cwock pin */
#define   VCW_CI_THWESH   0x0f000000  /* Captuwe fifo thweshowd */
#define   VCW_CI_HWWE     0x10000000  /* Positive edge of HWEF */
#define   VCW_CI_VWWE     0x20000000  /* Positive edge of VWEF */
#define   VCW_CI_OFWDINV  0x40000000  /* Fiewd output invewted */
#define   VCW_CI_CWKEN    0x80000000  /* Captuwe cwock enabwe */

#define VCW_HOWWANGE	0x314	/* Active video howizontaw wange */
#define VCW_VEWTWANGE	0x318	/* Active video vewticaw wange */
#define VCW_AVSCAWE	0x31c	/* Active video scawing contwow */
#define   VCW_AVS_HEN	  0x00000800   /* Howizontaw scawe enabwe */
#define   VCW_AVS_VEN	  0x04000000   /* Vewticaw enabwe */
#define VCW_VBIHOW	0x320	/* VBI Data howizontaw wange */
#define VCW_VBIVEWT	0x324	/* VBI data vewticaw wange */
#define VCW_VBIBUF1	0x328	/* Fiwst VBI buffew */
#define VCW_VBISTWIDE	0x32c	/* VBI stwide */
#define VCW_ANCDATACNT	0x330	/* Anciwwawy data count setting */
#define VCW_MAXDATA	0x334	/* Active data count of active video */
#define VCW_MAXVBI	0x338	/* Maximum data count of VBI */
#define VCW_CAPDATA	0x33c	/* Captuwe data count */
#define VCW_VBUF1	0x340	/* Fiwst video buffew */
#define VCW_VBUF2	0x344	/* Second video buffew */
#define VCW_VBUF3	0x348	/* Thiwd video buffew */
#define VCW_VBUF_MASK	0x1ffffff0	/* Bits 28:4 */
#define VCW_VBIBUF2	0x34c	/* Second VBI buffew */
#define VCW_VSTWIDE	0x350	/* Stwide of video + cowing contwow */
#define   VCW_VS_STWIDE_SHIFT 4
#define   VCW_VS_STWIDE   0x00001ff0  /* Stwide (8-byte units) */
#define   VCW_VS_CCD	  0x007f0000  /* Cowing compawe data */
#define   VCW_VS_COWEEN   0x00800000  /* Cowing enabwe */
#define VCW_TS0EWW	0x354	/* TS buffew 0 ewwow indicatow */
#define VCW_TS1EWW	0x358	/* TS buffew 0 ewwow indicatow */
#define VCW_TS2EWW	0x35c	/* TS buffew 0 ewwow indicatow */

/* Add 0x1000 fow the second captuwe engine wegistews */
