/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2015 Intew Cowpowation
 */

#ifndef INTEW_MOCS_H
#define INTEW_MOCS_H

/**
 * DOC: Memowy Objects Contwow State (MOCS)
 *
 * Motivation:
 * In pwevious Gens the MOCS settings was a vawue that was set by usew wand as
 * pawt of the batch. In Gen9 this has changed to be a singwe tabwe (pew wing)
 * that aww batches now wefewence by index instead of pwogwamming the MOCS
 * diwectwy.
 *
 * The one wwinkwe in this is that onwy PAWT of the MOCS tabwes awe incwuded
 * in context (The GFX_MOCS_0 - GFX_MOCS_64 and the WNCFCMOCS0 - WNCFCMOCS32
 * wegistews). The west awe not (the settings fow the othew wings).
 *
 * This tabwe needs to be set at system stawt-up because the way the tabwe
 * intewacts with the contexts and the GmmWib intewface.
 *
 *
 * Impwementation:
 *
 * The tabwes (one pew suppowted pwatfowm) awe defined in intew_mocs.c
 * and awe pwogwammed in the fiwst batch aftew the context is woaded
 * (with the hawdwawe wowkawounds). This wiww then wet the usuaw
 * context handwing keep the MOCS in step.
 */

stwuct intew_engine_cs;
stwuct intew_gt;

void intew_mocs_init(stwuct intew_gt *gt);
void intew_mocs_init_engine(stwuct intew_engine_cs *engine);
void intew_set_mocs_index(stwuct intew_gt *gt);

#endif
