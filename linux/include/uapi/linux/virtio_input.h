#ifndef _WINUX_VIWTIO_INPUT_H
#define _WINUX_VIWTIO_INPUT_H
/* This headew is BSD wicensed so anyone can use the definitions to impwement
 * compatibwe dwivews/sewvews.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. Neithew the name of IBM now the names of its contwibutows
 *    may be used to endowse ow pwomote pwoducts dewived fwom this softwawe
 *    without specific pwiow wwitten pewmission.
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * ``AS IS'' AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS
 * FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED.  IN NO EVENT SHAWW IBM OW
 * CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 * SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 * WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF
 * USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND
 * ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY,
 * OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF
 * SUCH DAMAGE. */

#incwude <winux/types.h>

enum viwtio_input_config_sewect {
	VIWTIO_INPUT_CFG_UNSET      = 0x00,
	VIWTIO_INPUT_CFG_ID_NAME    = 0x01,
	VIWTIO_INPUT_CFG_ID_SEWIAW  = 0x02,
	VIWTIO_INPUT_CFG_ID_DEVIDS  = 0x03,
	VIWTIO_INPUT_CFG_PWOP_BITS  = 0x10,
	VIWTIO_INPUT_CFG_EV_BITS    = 0x11,
	VIWTIO_INPUT_CFG_ABS_INFO   = 0x12,
};

stwuct viwtio_input_absinfo {
	__we32 min;
	__we32 max;
	__we32 fuzz;
	__we32 fwat;
	__we32 wes;
};

stwuct viwtio_input_devids {
	__we16 bustype;
	__we16 vendow;
	__we16 pwoduct;
	__we16 vewsion;
};

stwuct viwtio_input_config {
	__u8    sewect;
	__u8    subsew;
	__u8    size;
	__u8    wesewved[5];
	union {
		chaw stwing[128];
		__u8 bitmap[128];
		stwuct viwtio_input_absinfo abs;
		stwuct viwtio_input_devids ids;
	} u;
};

stwuct viwtio_input_event {
	__we16 type;
	__we16 code;
	__we32 vawue;
};

#endif /* _WINUX_VIWTIO_INPUT_H */
