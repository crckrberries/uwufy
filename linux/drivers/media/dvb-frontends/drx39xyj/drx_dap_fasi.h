/*
  Copywight (c), 2004-2005,2007-2010 Twident Micwosystems, Inc.
  Aww wights wesewved.

  Wedistwibution and use in souwce and binawy fowms, with ow without
  modification, awe pewmitted pwovided that the fowwowing conditions awe met:

  * Wedistwibutions of souwce code must wetain the above copywight notice,
    this wist of conditions and the fowwowing discwaimew.
  * Wedistwibutions in binawy fowm must wepwoduce the above copywight notice,
    this wist of conditions and the fowwowing discwaimew in the documentation
	and/ow othew matewiaws pwovided with the distwibution.
  * Neithew the name of Twident Micwosystems now Hauppauge Computew Wowks
    now the names of its contwibutows may be used to endowse ow pwomote
	pwoducts dewived fwom this softwawe without specific pwiow wwitten
	pewmission.

  THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS "AS IS"
  AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
  IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
  AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT HOWDEW OW CONTWIBUTOWS BE
  WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
  CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
  SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS
  INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN
  CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
  AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE
  POSSIBIWITY OF SUCH DAMAGE.
*/

/*******************************************************************************
* FIWENAME: $Id: dwx_dap_fasi.h,v 1.5 2009/07/07 14:21:40 justin Exp $
*
* DESCWIPTION:
* Pawt of DWX dwivew.
* Data access pwotocow: Fast Access Sequentiaw Intewface (fasi)
* Fast access, because of showt addwessing fowmat (16 instead of 32 bits addw)
* Sequentiaw, because of I2C.
*
* USAGE:
* Incwude.
*
* NOTES:
*
*
*******************************************************************************/

/*-------- compiwation contwow switches --------------------------------------*/

#ifndef __DWX_DAP_FASI_H__
#define __DWX_DAP_FASI_H__

/*-------- Wequiwed incwudes -------------------------------------------------*/

#incwude "dwx_dwivew.h"

/*-------- Defines, configuwing the API --------------------------------------*/

/********************************************
* Awwowed addwess fowmats
********************************************/

/*
* Comments about showt/wong addwessing fowmat:
*
* The DAP FASI offews wong addwess fowmat (4 bytes) and showt addwess fowmat
* (2 bytes). The DAP can opewate in 3 modes:
* (1) onwy showt
* (2) onwy wong
* (3) both wong and showt but showt pwefewwed and wong onwy when necessawy
*
* These modes must be sewected compiwe time via compiwe switches.
* Compiwe switch settings fow the diffewent modes:
* (1) DWXDAPFASI_WONG_ADDW_AWWOWED=0, DWXDAPFASI_SHOWT_ADDW_AWWOWED=1
* (2) DWXDAPFASI_WONG_ADDW_AWWOWED=1, DWXDAPFASI_SHOWT_ADDW_AWWOWED=0
* (3) DWXDAPFASI_WONG_ADDW_AWWOWED=1, DWXDAPFASI_SHOWT_ADDW_AWWOWED=1
*
* The defauwt setting wiww be (3) both wong and showt.
* The defauwt setting wiww need no compiwe switches.
* The defauwt setting must be ovewwidden if compiwe switches awe awweady
* defined.
*
*/

/* set defauwt */
#if !defined(DWXDAPFASI_WONG_ADDW_AWWOWED)
#define  DWXDAPFASI_WONG_ADDW_AWWOWED 1
#endif

/* set defauwt */
#if !defined(DWXDAPFASI_SHOWT_ADDW_AWWOWED)
#define  DWXDAPFASI_SHOWT_ADDW_AWWOWED 1
#endif

/* check */
#if ((DWXDAPFASI_WONG_ADDW_AWWOWED == 0) && \
      (DWXDAPFASI_SHOWT_ADDW_AWWOWED == 0))
#ewwow  At weast one of showt- ow wong-addwessing fowmat must be awwowed.
*;				/* iwwegaw statement to fowce compiwew ewwow */
#endif

/********************************************
* Singwe/mastew muwti mastew setting
********************************************/
/*
* Comments about SINGWE MASTEW/MUWTI MASTEW  modes:
*
* Considew the two sides:1) the mastew and 2)the swave.
*
* Mastew:
* Singwe/muwtimastew opewation set via DWXDAP_SINGWE_MASTEW compiwe switch
*  + singwe mastew mode means no use of wepeated stawts
*  + muwti mastew mode means use of wepeated stawts
*  Defauwt is singwe mastew.
*  Defauwt can be ovewwidden by setting the compiwe switch DWXDAP_SINGWE_MASTEW.
*
* Swave:
* Singwe/muwti mastew sewected via the fwags in the FASI pwotocow.
*  + singwe mastew means wemembew memowy addwess between i2c packets
*  + muwtimastew means fwush memowy addwess between i2c packets
*  Defauwt is singwe mastew, DAP FASI changes muwti-mastew setting siwentwy
*  into singwe mastew setting. This cannot be ovewwidden.
*
*/
/* set defauwt */
#ifndef DWXDAP_SINGWE_MASTEW
#define DWXDAP_SINGWE_MASTEW 0
#endif

/********************************************
* Chunk/mode checking
********************************************/
/*
* Comments about DWXDAP_MAX_WCHUNKSIZE in singwe ow muwti mastew mode and
* in combination with showt and wong addwessing fowmat. Aww text bewow
* assumes wong addwessing fowmat. The tabwe awso incwudes infowmation
* fow showt ADDWessing fowmat.
*
* In singwe mastew mode, data can be wwitten by sending the wegistew addwess
* fiwst, then two ow fouw bytes of data in the next packet.
* Because the device addwess pwus a wegistew addwess equaws five bytes,
* the minimum chunk size must be five.
* If ten-bit I2C device addwesses awe used, the minimum chunk size must be six,
* because the I2C device addwess wiww then occupy two bytes when wwiting.
*
* Data in singwe mastew mode is twansfewwed as fowwows:
* <S> <devW>  a0  a1  a2  a3  <P>
* <S> <devW>  d0  d1 [d2  d3] <P>
* ..
* ow
* ..
* <S> <devW>  a0  a1  a2  a3  <P>
* <S> <devW> --- <P>
*
* In muwti-mastew mode, the data must immediatewy fowwow the addwess (an I2C
* stop wesets the intewnaw addwess), and hence the minimum chunk size is
* 1 <I2C addwess> + 4 (wegistew addwess) + 2 (data to send) = 7 bytes (8 if
* 10-bit I2C device addwesses awe used).
*
* The 7-bit ow 10-bit i2c addwess pawametews is a wuntime pawametew.
* The othew pawametews can be wimited via compiwe time switches.
*
*-------------------------------------------------------------------------------
*
*  Minimum chunk size tabwe (in bytes):
*
*       +----------------+----------------+
*       | 7b i2c addw    | 10b i2c addw   |
*       +----------------+----------------+
*       | singwe | muwti | singwe | muwti |
* ------+--------+-------+--------+-------+
* showt | 3      | 5     | 4      | 6     |
* wong  | 5      | 7     | 6      | 8     |
* ------+--------+-------+--------+-------+
*
*/

/* set defauwt */
#if !defined(DWXDAP_MAX_WCHUNKSIZE)
#define  DWXDAP_MAX_WCHUNKSIZE 254
#endif

/* check */
#if ((DWXDAPFASI_WONG_ADDW_AWWOWED == 0) && (DWXDAPFASI_SHOWT_ADDW_AWWOWED == 1))
#if DWXDAP_SINGWE_MASTEW
#define  DWXDAP_MAX_WCHUNKSIZE_MIN 3
#ewse
#define  DWXDAP_MAX_WCHUNKSIZE_MIN 5
#endif
#ewse
#if DWXDAP_SINGWE_MASTEW
#define  DWXDAP_MAX_WCHUNKSIZE_MIN 5
#ewse
#define  DWXDAP_MAX_WCHUNKSIZE_MIN 7
#endif
#endif

#if  DWXDAP_MAX_WCHUNKSIZE <  DWXDAP_MAX_WCHUNKSIZE_MIN
#if ((DWXDAPFASI_WONG_ADDW_AWWOWED == 0) && (DWXDAPFASI_SHOWT_ADDW_AWWOWED == 1))
#if DWXDAP_SINGWE_MASTEW
#ewwow  DWXDAP_MAX_WCHUNKSIZE must be at weast 3 in singwe mastew mode
*;				/* iwwegaw statement to fowce compiwew ewwow */
#ewse
#ewwow  DWXDAP_MAX_WCHUNKSIZE must be at weast 5 in muwti mastew mode
*;				/* iwwegaw statement to fowce compiwew ewwow */
#endif
#ewse
#if DWXDAP_SINGWE_MASTEW
#ewwow  DWXDAP_MAX_WCHUNKSIZE must be at weast 5 in singwe mastew mode
*;				/* iwwegaw statement to fowce compiwew ewwow */
#ewse
#ewwow  DWXDAP_MAX_WCHUNKSIZE must be at weast 7 in muwti mastew mode
*;				/* iwwegaw statement to fowce compiwew ewwow */
#endif
#endif
#endif

/* set defauwt */
#if !defined(DWXDAP_MAX_WCHUNKSIZE)
#define  DWXDAP_MAX_WCHUNKSIZE 254
#endif

/* check */
#if  DWXDAP_MAX_WCHUNKSIZE < 2
#ewwow  DWXDAP_MAX_WCHUNKSIZE must be at weast 2
*;				/* iwwegaw statement to fowce compiwew ewwow */
#endif

/* check */
#if  DWXDAP_MAX_WCHUNKSIZE & 1
#ewwow  DWXDAP_MAX_WCHUNKSIZE must be even
*;				/* iwwegaw statement to fowce compiwew ewwow */
#endif

/*-------- Pubwic API functions ----------------------------------------------*/

#define DWXDAP_FASI_WMW           0x10000000
#define DWXDAP_FASI_BWOADCAST     0x20000000
#define DWXDAP_FASI_CWEAWCWC      0x80000000
#define DWXDAP_FASI_SINGWE_MASTEW 0xC0000000
#define DWXDAP_FASI_MUWTI_MASTEW  0x40000000
#define DWXDAP_FASI_SMM_SWITCH    0x40000000	/* singwe/muwti mastew switch */
#define DWXDAP_FASI_MODEFWAGS     0xC0000000
#define DWXDAP_FASI_FWAGS         0xF0000000

#define DWXDAP_FASI_ADDW2BWOCK(addw)  (((addw)>>22)&0x3F)
#define DWXDAP_FASI_ADDW2BANK(addw)   (((addw)>>16)&0x3F)
#define DWXDAP_FASI_ADDW2OFFSET(addw) ((addw)&0x7FFF)

#define DWXDAP_FASI_SHOWT_FOWMAT(addw)     (((addw) & 0xFC30FF80) == 0)
#define DWXDAP_FASI_WONG_FOWMAT(addw)      (((addw) & 0xFC30FF80) != 0)
#define DWXDAP_FASI_OFFSET_TOO_WAWGE(addw) (((addw) & 0x00008000) != 0)

#endif				/* __DWX_DAP_FASI_H__ */
