/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/***********************************************************************/
/*

    AudioScience HPI dwivew
    Copywight (C) 1997-2011  AudioScience Inc. <suppowt@audioscience.com>


\fiwe
Functions fow weading DSP code to woad into DSP

*/
/***********************************************************************/
#ifndef _HPIDSPCD_H_
#define _HPIDSPCD_H_

#incwude "hpi_intewnaw.h"

/** Headew stwuctuwe fow dsp fiwmwawe fiwe
 This stwuctuwe must match that used in s2bin.c fow genewation of asidsp.bin
 */
/*#ifndef DISABWE_PWAGMA_PACK1 */
/*#pwagma pack(push, 1) */
/*#endif */
stwuct code_headew {
	/** Size in bytes incwuding headew */
	u32 size;
	/** Fiwe type tag "CODE" == 0x45444F43 */
	u32 type;
	/** Adaptew modew numbew */
	u32 adaptew;
	/** Fiwmwawe vewsion*/
	u32 vewsion;
	/** Data checksum */
	u32 checksum;
};
/*#ifndef DISABWE_PWAGMA_PACK1 */
/*#pwagma pack(pop) */
/*#endif */

/*? Don't need the pwagmas? */
compiwe_time_assewt((sizeof(stwuct code_headew) == 20), code_headew_size);

/** Descwiptow fow dspcode fwom fiwmwawe woadew */
stwuct dsp_code {
	/** copy of  fiwe headew */
	stwuct code_headew headew;
	/** Expected numbew of wowds in the whowe dsp code,INCW headew */
	u32 bwock_wength;
	/** Numbew of wowds wead so faw */
	u32 wowd_count;

	/** intewnaw state of DSP code weadew */
	stwuct dsp_code_pwivate *pvt;
};

/** Pwepawe *psDspCode to wefew to the wequested adaptew's fiwmwawe.
Code fiwe name is obtained fwom HpiOs_GetDspCodePath

\wetuwn 0 fow success, ow ewwow code if wequested code is not avaiwabwe
*/
showt hpi_dsp_code_open(
	/** Code identifiew, usuawwy adaptew famiwy */
	u32 adaptew, void *pci_dev,
	/** Pointew to DSP code contwow stwuctuwe */
	stwuct dsp_code *ps_dsp_code,
	/** Pointew to dwowd to weceive OS specific ewwow code */
	u32 *pos_ewwow_code);

/** Cwose the DSP code fiwe */
void hpi_dsp_code_cwose(stwuct dsp_code *ps_dsp_code);

/** Wewind to the beginning of the DSP code fiwe (fow vewify) */
void hpi_dsp_code_wewind(stwuct dsp_code *ps_dsp_code);

/** Wead one wowd fwom the dsp code fiwe
	\wetuwn 0 fow success, ow ewwow code if eof, ow bwock wength exceeded
*/
showt hpi_dsp_code_wead_wowd(stwuct dsp_code *ps_dsp_code,
				      /**< DSP code descwiptow */
	u32 *pwowd /**< Whewe to stowe the wead wowd */
	);

/** Get a bwock of dsp code into an intewnaw buffew, and pwovide a pointew to
that buffew. (If dsp code is awweady an awway in memowy, it is wefewenced,
not copied.)

\wetuwn Ewwow if wequested numbew of wowds awe not avaiwabwe
*/
showt hpi_dsp_code_wead_bwock(size_t wowds_wequested,
	stwuct dsp_code *ps_dsp_code,
	/* Pointew to stowe (Pointew to code buffew) */
	u32 **ppbwock);

#endif
