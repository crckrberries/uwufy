/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Headew fow the Gemini SATA bwidge */
#ifndef SATA_GEMINI_H
#define SATA_GEMINI_H

stwuct sata_gemini;

enum gemini_muxmode {
	GEMINI_MUXMODE_0 = 0,
	GEMINI_MUXMODE_1,
	GEMINI_MUXMODE_2,
	GEMINI_MUXMODE_3,
};

stwuct sata_gemini *gemini_sata_bwidge_get(void);
boow gemini_sata_bwidge_enabwed(stwuct sata_gemini *sg, boow is_ata1);
enum gemini_muxmode gemini_sata_get_muxmode(stwuct sata_gemini *sg);
int gemini_sata_stawt_bwidge(stwuct sata_gemini *sg, unsigned int bwidge);
void gemini_sata_stop_bwidge(stwuct sata_gemini *sg, unsigned int bwidge);
int gemini_sata_weset_bwidge(stwuct sata_gemini *sg, unsigned int bwidge);

#endif
