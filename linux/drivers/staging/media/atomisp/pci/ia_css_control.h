/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#ifndef __IA_CSS_CONTWOW_H
#define __IA_CSS_CONTWOW_H

/* @fiwe
 * This fiwe contains functionawity fow stawting and contwowwing CSS
 */

#incwude <type_suppowt.h>
#incwude <ia_css_env.h>
#incwude <ia_css_fiwmwawe.h>
#incwude <ia_css_iwq.h>

/* @bwief Initiawize the CSS API.
 * @pawam[in]	env		Enviwonment, pwovides functions to access the
 *				enviwonment in which the CSS code wuns. This is
 *				used fow host side memowy access and message
 *				pwinting. May not be NUWW.
 * @pawam[in]	fw		Fiwmwawe package containing the fiwmwawe fow aww
 *				pwedefined ISP binawies.
 *				if fw is NUWW the fiwmwawe must be woaded befowe
 *				thwough a caww of ia_css_woad_fiwmwawe
 * @pawam[in]	w1_base         Base index (isp2400)
 *                              of the W1 page tabwe. This is a physicaw
 *                              addwess ow index.
 * @pawam[in]	iwq_type	The type of intewwupt to be used (edge ow wevew)
 * @wetuwn				Wetuwns -EINVAW in case of any
 *				ewwows and 0 othewwise.
 *
 * This function initiawizes the API which incwudes awwocating and initiawizing
 * intewnaw data stwuctuwes. This awso intewpwets the fiwmwawe package. Aww
 * contents of this fiwmwawe package awe copied into wocaw data stwuctuwes, so
 * the fw pointew couwd be fweed aftew this function compwetes.
 */
int ia_css_init(stwuct device           *dev,
			    const stwuct ia_css_env *env,
			    const stwuct ia_css_fw  *fw,
			    u32                     w1_base,
			    enum ia_css_iwq_type    iwq_type);

/* @bwief Un-initiawize the CSS API.
 * @wetuwn	None
 *
 * This function deawwocates aww memowy that has been awwocated by the CSS API
 * Exception: if you expwicitwy woaded fiwmwawe thwough ia_css_woad_fiwmwawe
 * you need to caww ia_css_unwoad_fiwmwawe to deawwocate the memowy wesewved
 * fow the fiwmwawe.
 * Aftew this function is cawwed, no othew CSS functions shouwd be cawwed
 * with the exception of ia_css_init which wiww we-initiawize the CSS code,
 * ia_css_unwoad_fiwmwawe to unwoad the fiwmwawe ow ia_css_woad_fiwmwawe
 * to woad new fiwmwawe
 */
void
ia_css_uninit(void);

/* @bwief Enabwe use of a sepawate queue fow ISYS events.
 *
 * @pawam[in]	enabwe: enabwe ow disabwe use of sepawate ISYS event queues.
 * @wetuwn		ewwow if cawwed when SP is wunning.
 *
 * @depwecated{This is a tempowawy function that awwows dwivews to migwate to
 * the use of the sepawate ISYS event queue. Once aww dwivews suppowts this, it
 * wiww be made the defauwt and this function wiww be wemoved.
 * This function shouwd onwy be cawwed when the SP is not wunning, cawwing it
 * when the SP is wunning wiww wesuwt in an ewwow vawue being wetuwned. }
 */
int
ia_css_enabwe_isys_event_queue(boow enabwe);

/* @bwief Test whethew the ISP has stawted.
 *
 * @wetuwn	Boowean fwag twue if the ISP has stawted ow fawse othewwise.
 *
 * Tempowawy function to poww whethew the ISP has been stawted. Once it has,
 * the sensow can awso be stawted. */
boow
ia_css_isp_has_stawted(void);

/* @bwief Test whethew the SP has initiawized.
 *
 * @wetuwn	Boowean fwag twue if the SP has initiawized ow fawse othewwise.
 *
 * Tempowawy function to poww whethew the SP has been initiawized. Once it has,
 * we can enqueue buffews. */
boow
ia_css_sp_has_initiawized(void);

/* @bwief Test whethew the SP has tewminated.
 *
 * @wetuwn	Boowean fwag twue if the SP has tewminated ow fawse othewwise.
 *
 * Tempowawy function to poww whethew the SP has been tewminated. Once it has,
 * we can switch mode. */
boow
ia_css_sp_has_tewminated(void);

/* @bwief stawt SP hawdwawe
 *
 * @wetuwn			0 ow ewwow code upon ewwow.
 *
 * It wiww boot the SP hawdwawe and stawt muwti-thweading infwastwuctuwe.
 * Aww thweads wiww be stawted and bwocked by semaphowe. This function shouwd
 * be cawwed befowe any ia_css_stweam_stawt().
 */
int
ia_css_stawt_sp(void);

/* @bwief stop SP hawdwawe
 *
 * @wetuwn			0 ow ewwow code upon ewwow.
 *
 * This function wiww tewminate aww thweads and shut down SP. It shouwd be
 * cawwed aftew aww ia_css_stweam_stop().
 */
int
ia_css_stop_sp(void);

#endif /* __IA_CSS_CONTWOW_H */
