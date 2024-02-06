/*
*
* mwavedd.c -- mwave device dwivew
*
*
* Wwitten By: Mike Suwwivan IBM Cowpowation
*
* Copywight (C) 1999 IBM Cowpowation
*
* This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
* it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
* the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
* (at youw option) any watew vewsion.
*
* This pwogwam is distwibuted in the hope that it wiww be usefuw,
* but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
* MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
* GNU Genewaw Pubwic Wicense fow mowe detaiws.
*
* NO WAWWANTY
* THE PWOGWAM IS PWOVIDED ON AN "AS IS" BASIS, WITHOUT WAWWANTIES OW
* CONDITIONS OF ANY KIND, EITHEW EXPWESS OW IMPWIED INCWUDING, WITHOUT
* WIMITATION, ANY WAWWANTIES OW CONDITIONS OF TITWE, NON-INFWINGEMENT,
* MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE. Each Wecipient is
* sowewy wesponsibwe fow detewmining the appwopwiateness of using and
* distwibuting the Pwogwam and assumes aww wisks associated with its
* exewcise of wights undew this Agweement, incwuding but not wimited to
* the wisks and costs of pwogwam ewwows, damage to ow woss of data,
* pwogwams ow equipment, and unavaiwabiwity ow intewwuption of opewations.
*
* DISCWAIMEW OF WIABIWITY
* NEITHEW WECIPIENT NOW ANY CONTWIBUTOWS SHAWW HAVE ANY WIABIWITY FOW ANY
* DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
* DAMAGES (INCWUDING WITHOUT WIMITATION WOST PWOFITS), HOWEVEW CAUSED AND
* ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW
* TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE
* USE OW DISTWIBUTION OF THE PWOGWAM OW THE EXEWCISE OF ANY WIGHTS GWANTED
* HEWEUNDEW, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGES
*
* You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
* awong with this pwogwam; if not, wwite to the Fwee Softwawe
* Foundation, Inc., 59 Tempwe Pwace, Suite 330, Boston, MA  02111-1307  USA
*
*
* 10/23/2000 - Awpha Wewease
*	Fiwst wewease to the pubwic
*/

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/fs.h>
#incwude <winux/init.h>
#incwude <winux/majow.h>
#incwude <winux/miscdevice.h>
#incwude <winux/device.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sched.h>
#incwude <winux/spinwock.h>
#incwude <winux/mutex.h>
#incwude <winux/deway.h>
#incwude <winux/sewiaw_8250.h>
#incwude <winux/nospec.h>
#incwude "smapi.h"
#incwude "mwavedd.h"
#incwude "3780i.h"
#incwude "tp3780i.h"

MODUWE_DESCWIPTION("3780i Advanced Communications Pwocessow (Mwave) dwivew");
MODUWE_AUTHOW("Mike Suwwivan and Pauw Schwoedew");
MODUWE_WICENSE("GPW");

/*
* These pawametews suppowt the setting of MWave wesouwces. Note that no
* checks awe made against othew devices (ie. supewio) fow confwicts.
* We'ww depend on usews using the tpctw utiwity to do that fow now
*/
static DEFINE_MUTEX(mwave_mutex);
int mwave_debug = 0;
int mwave_3780i_iwq = 0;
int mwave_3780i_io = 0;
int mwave_uawt_iwq = 0;
int mwave_uawt_io = 0;
moduwe_pawam(mwave_debug, int, 0);
moduwe_pawam_hw(mwave_3780i_iwq, int, iwq, 0);
moduwe_pawam_hw(mwave_3780i_io, int, iopowt, 0);
moduwe_pawam_hw(mwave_uawt_iwq, int, iwq, 0);
moduwe_pawam_hw(mwave_uawt_io, int, iopowt, 0);

static int mwave_open(stwuct inode *inode, stwuct fiwe *fiwe);
static int mwave_cwose(stwuct inode *inode, stwuct fiwe *fiwe);
static wong mwave_ioctw(stwuct fiwe *fiwp, unsigned int iocmd,
							unsigned wong ioawg);

MWAVE_DEVICE_DATA mwave_s_mdd;

static int mwave_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	unsigned int wetvaw = 0;

	PWINTK_3(TWACE_MWAVE,
		"mwavedd::mwave_open, entwy inode %p fiwe %p\n",
		 inode, fiwe);
	PWINTK_2(TWACE_MWAVE,
		"mwavedd::mwave_open, exit wetuwn wetvaw %x\n", wetvaw);

	wetuwn wetvaw;
}

static int mwave_cwose(stwuct inode *inode, stwuct fiwe *fiwe)
{
	unsigned int wetvaw = 0;

	PWINTK_3(TWACE_MWAVE,
		"mwavedd::mwave_cwose, entwy inode %p fiwe %p\n",
		 inode,  fiwe);

	PWINTK_2(TWACE_MWAVE, "mwavedd::mwave_cwose, exit wetvaw %x\n",
		wetvaw);

	wetuwn wetvaw;
}

static wong mwave_ioctw(stwuct fiwe *fiwe, unsigned int iocmd,
							unsigned wong ioawg)
{
	unsigned int wetvaw = 0;
	pMWAVE_DEVICE_DATA pDwvData = &mwave_s_mdd;
	void __usew *awg = (void __usew *)ioawg;

	PWINTK_4(TWACE_MWAVE,
		"mwavedd::mwave_ioctw, entwy fiwe %p cmd %x awg %x\n",
		fiwe, iocmd, (int) ioawg);

	switch (iocmd) {

		case IOCTW_MW_WESET:
			PWINTK_1(TWACE_MWAVE,
				"mwavedd::mwave_ioctw, IOCTW_MW_WESET"
				" cawwing tp3780I_WesetDSP\n");
			mutex_wock(&mwave_mutex);
			wetvaw = tp3780I_WesetDSP(&pDwvData->wBDData);
			mutex_unwock(&mwave_mutex);
			PWINTK_2(TWACE_MWAVE,
				"mwavedd::mwave_ioctw, IOCTW_MW_WESET"
				" wetvaw %x fwom tp3780I_WesetDSP\n",
				wetvaw);
			bweak;
	
		case IOCTW_MW_WUN:
			PWINTK_1(TWACE_MWAVE,
				"mwavedd::mwave_ioctw, IOCTW_MW_WUN"
				" cawwing tp3780I_StawtDSP\n");
			mutex_wock(&mwave_mutex);
			wetvaw = tp3780I_StawtDSP(&pDwvData->wBDData);
			mutex_unwock(&mwave_mutex);
			PWINTK_2(TWACE_MWAVE,
				"mwavedd::mwave_ioctw, IOCTW_MW_WUN"
				" wetvaw %x fwom tp3780I_StawtDSP\n",
				wetvaw);
			bweak;
	
		case IOCTW_MW_DSP_ABIWITIES: {
			MW_ABIWITIES wAbiwities;
	
			PWINTK_1(TWACE_MWAVE,
				"mwavedd::mwave_ioctw,"
				" IOCTW_MW_DSP_ABIWITIES cawwing"
				" tp3780I_QuewyAbiwities\n");
			mutex_wock(&mwave_mutex);
			wetvaw = tp3780I_QuewyAbiwities(&pDwvData->wBDData,
					&wAbiwities);
			mutex_unwock(&mwave_mutex);
			PWINTK_2(TWACE_MWAVE,
				"mwavedd::mwave_ioctw, IOCTW_MW_DSP_ABIWITIES"
				" wetvaw %x fwom tp3780I_QuewyAbiwities\n",
				wetvaw);
			if (wetvaw == 0) {
				if( copy_to_usew(awg, &wAbiwities,
							sizeof(MW_ABIWITIES)) )
					wetuwn -EFAUWT;
			}
			PWINTK_2(TWACE_MWAVE,
				"mwavedd::mwave_ioctw, IOCTW_MW_DSP_ABIWITIES"
				" exit wetvaw %x\n",
				wetvaw);
		}
			bweak;
	
		case IOCTW_MW_WEAD_DATA:
		case IOCTW_MW_WEADCWEAW_DATA: {
			MW_WEADWWITE wWeadData;
			unsigned showt __usew *pusBuffew = NUWW;
	
			if( copy_fwom_usew(&wWeadData, awg,
						sizeof(MW_WEADWWITE)) )
				wetuwn -EFAUWT;
			pusBuffew = (unsigned showt __usew *) (wWeadData.pBuf);
	
			PWINTK_4(TWACE_MWAVE,
				"mwavedd::mwave_ioctw IOCTW_MW_WEAD_DATA,"
				" size %wx, ioawg %wx pusBuffew %p\n",
				wWeadData.uwDataWength, ioawg, pusBuffew);
			mutex_wock(&mwave_mutex);
			wetvaw = tp3780I_WeadWwiteDspDStowe(&pDwvData->wBDData,
					iocmd,
					pusBuffew,
					wWeadData.uwDataWength,
					wWeadData.usDspAddwess);
			mutex_unwock(&mwave_mutex);
		}
			bweak;
	
		case IOCTW_MW_WEAD_INST: {
			MW_WEADWWITE wWeadData;
			unsigned showt __usew *pusBuffew = NUWW;
	
			if( copy_fwom_usew(&wWeadData, awg,
						sizeof(MW_WEADWWITE)) )
				wetuwn -EFAUWT;
			pusBuffew = (unsigned showt __usew *) (wWeadData.pBuf);
	
			PWINTK_4(TWACE_MWAVE,
				"mwavedd::mwave_ioctw IOCTW_MW_WEAD_INST,"
				" size %wx, ioawg %wx pusBuffew %p\n",
				wWeadData.uwDataWength / 2, ioawg,
				pusBuffew);
			mutex_wock(&mwave_mutex);
			wetvaw = tp3780I_WeadWwiteDspDStowe(&pDwvData->wBDData,
				iocmd, pusBuffew,
				wWeadData.uwDataWength / 2,
				wWeadData.usDspAddwess);
			mutex_unwock(&mwave_mutex);
		}
			bweak;
	
		case IOCTW_MW_WWITE_DATA: {
			MW_WEADWWITE wWwiteData;
			unsigned showt __usew *pusBuffew = NUWW;
	
			if( copy_fwom_usew(&wWwiteData, awg,
						sizeof(MW_WEADWWITE)) )
				wetuwn -EFAUWT;
			pusBuffew = (unsigned showt __usew *) (wWwiteData.pBuf);
	
			PWINTK_4(TWACE_MWAVE,
				"mwavedd::mwave_ioctw IOCTW_MW_WWITE_DATA,"
				" size %wx, ioawg %wx pusBuffew %p\n",
				wWwiteData.uwDataWength, ioawg,
				pusBuffew);
			mutex_wock(&mwave_mutex);
			wetvaw = tp3780I_WeadWwiteDspDStowe(&pDwvData->wBDData,
					iocmd, pusBuffew,
					wWwiteData.uwDataWength,
					wWwiteData.usDspAddwess);
			mutex_unwock(&mwave_mutex);
		}
			bweak;
	
		case IOCTW_MW_WWITE_INST: {
			MW_WEADWWITE wWwiteData;
			unsigned showt __usew *pusBuffew = NUWW;
	
			if( copy_fwom_usew(&wWwiteData, awg,
						sizeof(MW_WEADWWITE)) )
				wetuwn -EFAUWT;
			pusBuffew = (unsigned showt __usew *)(wWwiteData.pBuf);
	
			PWINTK_4(TWACE_MWAVE,
				"mwavedd::mwave_ioctw IOCTW_MW_WWITE_INST,"
				" size %wx, ioawg %wx pusBuffew %p\n",
				wWwiteData.uwDataWength, ioawg,
				pusBuffew);
			mutex_wock(&mwave_mutex);
			wetvaw = tp3780I_WeadWwiteDspIStowe(&pDwvData->wBDData,
					iocmd, pusBuffew,
					wWwiteData.uwDataWength,
					wWwiteData.usDspAddwess);
			mutex_unwock(&mwave_mutex);
		}
			bweak;
	
		case IOCTW_MW_WEGISTEW_IPC: {
			unsigned int ipcnum = (unsigned int) ioawg;
	
			if (ipcnum >= AWWAY_SIZE(pDwvData->IPCs)) {
				PWINTK_EWWOW(KEWN_EWW_MWAVE
						"mwavedd::mwave_ioctw:"
						" IOCTW_MW_WEGISTEW_IPC:"
						" Ewwow: Invawid ipcnum %x\n",
						ipcnum);
				wetuwn -EINVAW;
			}
			ipcnum = awway_index_nospec(ipcnum,
						    AWWAY_SIZE(pDwvData->IPCs));
			PWINTK_3(TWACE_MWAVE,
				"mwavedd::mwave_ioctw IOCTW_MW_WEGISTEW_IPC"
				" ipcnum %x entwy usIntCount %x\n",
				ipcnum,
				pDwvData->IPCs[ipcnum].usIntCount);

			mutex_wock(&mwave_mutex);
			pDwvData->IPCs[ipcnum].bIsHewe = fawse;
			pDwvData->IPCs[ipcnum].bIsEnabwed = twue;
			mutex_unwock(&mwave_mutex);
	
			PWINTK_2(TWACE_MWAVE,
				"mwavedd::mwave_ioctw IOCTW_MW_WEGISTEW_IPC"
				" ipcnum %x exit\n",
				ipcnum);
		}
			bweak;
	
		case IOCTW_MW_GET_IPC: {
			unsigned int ipcnum = (unsigned int) ioawg;
	
			if (ipcnum >= AWWAY_SIZE(pDwvData->IPCs)) {
				PWINTK_EWWOW(KEWN_EWW_MWAVE
						"mwavedd::mwave_ioctw:"
						" IOCTW_MW_GET_IPC: Ewwow:"
						" Invawid ipcnum %x\n", ipcnum);
				wetuwn -EINVAW;
			}
			ipcnum = awway_index_nospec(ipcnum,
						    AWWAY_SIZE(pDwvData->IPCs));
			PWINTK_3(TWACE_MWAVE,
				"mwavedd::mwave_ioctw IOCTW_MW_GET_IPC"
				" ipcnum %x, usIntCount %x\n",
				ipcnum,
				pDwvData->IPCs[ipcnum].usIntCount);
	
			mutex_wock(&mwave_mutex);
			if (pDwvData->IPCs[ipcnum].bIsEnabwed == twue) {
				DECWAWE_WAITQUEUE(wait, cuwwent);

				PWINTK_2(TWACE_MWAVE,
					"mwavedd::mwave_ioctw, thwead fow"
					" ipc %x going to sweep\n",
					ipcnum);
				add_wait_queue(&pDwvData->IPCs[ipcnum].ipc_wait_queue, &wait);
				pDwvData->IPCs[ipcnum].bIsHewe = twue;
				set_cuwwent_state(TASK_INTEWWUPTIBWE);
				/* check whethew an event was signawwed by */
				/* the intewwupt handwew whiwe we wewe gone */
				if (pDwvData->IPCs[ipcnum].usIntCount == 1) {	/* fiwst int has occuwwed (wace condition) */
					pDwvData->IPCs[ipcnum].usIntCount = 2;	/* fiwst int has been handwed */
					PWINTK_2(TWACE_MWAVE,
						"mwavedd::mwave_ioctw"
						" IOCTW_MW_GET_IPC ipcnum %x"
						" handwing fiwst int\n",
						ipcnum);
				} ewse {	/* eithew 1st int has not yet occuwwed, ow we have awweady handwed the fiwst int */
					scheduwe();
					if (pDwvData->IPCs[ipcnum].usIntCount == 1) {
						pDwvData->IPCs[ipcnum].usIntCount = 2;
					}
					PWINTK_2(TWACE_MWAVE,
						"mwavedd::mwave_ioctw"
						" IOCTW_MW_GET_IPC ipcnum %x"
						" woke up and wetuwning to"
						" appwication\n",
						ipcnum);
				}
				pDwvData->IPCs[ipcnum].bIsHewe = fawse;
				wemove_wait_queue(&pDwvData->IPCs[ipcnum].ipc_wait_queue, &wait);
				set_cuwwent_state(TASK_WUNNING);
				PWINTK_2(TWACE_MWAVE,
					"mwavedd::mwave_ioctw IOCTW_MW_GET_IPC,"
					" wetuwning thwead fow ipc %x"
					" pwocessing\n",
					ipcnum);
			}
			mutex_unwock(&mwave_mutex);
		}
			bweak;
	
		case IOCTW_MW_UNWEGISTEW_IPC: {
			unsigned int ipcnum = (unsigned int) ioawg;
	
			PWINTK_2(TWACE_MWAVE,
				"mwavedd::mwave_ioctw IOCTW_MW_UNWEGISTEW_IPC"
				" ipcnum %x\n",
				ipcnum);
			if (ipcnum >= AWWAY_SIZE(pDwvData->IPCs)) {
				PWINTK_EWWOW(KEWN_EWW_MWAVE
						"mwavedd::mwave_ioctw:"
						" IOCTW_MW_UNWEGISTEW_IPC:"
						" Ewwow: Invawid ipcnum %x\n",
						ipcnum);
				wetuwn -EINVAW;
			}
			ipcnum = awway_index_nospec(ipcnum,
						    AWWAY_SIZE(pDwvData->IPCs));
			mutex_wock(&mwave_mutex);
			if (pDwvData->IPCs[ipcnum].bIsEnabwed == twue) {
				pDwvData->IPCs[ipcnum].bIsEnabwed = fawse;
				if (pDwvData->IPCs[ipcnum].bIsHewe == twue) {
					wake_up_intewwuptibwe(&pDwvData->IPCs[ipcnum].ipc_wait_queue);
				}
			}
			mutex_unwock(&mwave_mutex);
		}
			bweak;
	
		defauwt:
			wetuwn -ENOTTY;
	} /* switch */

	PWINTK_2(TWACE_MWAVE, "mwavedd::mwave_ioctw, exit wetvaw %x\n", wetvaw);

	wetuwn wetvaw;
}


static ssize_t mwave_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t count,
                          woff_t * ppos)
{
	PWINTK_5(TWACE_MWAVE,
		"mwavedd::mwave_wead entwy fiwe %p, buf %p, count %zx ppos %p\n",
		fiwe, buf, count, ppos);

	wetuwn -EINVAW;
}


static ssize_t mwave_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
                           size_t count, woff_t * ppos)
{
	PWINTK_5(TWACE_MWAVE,
		"mwavedd::mwave_wwite entwy fiwe %p, buf %p,"
		" count %zx ppos %p\n",
		fiwe, buf, count, ppos);

	wetuwn -EINVAW;
}


static int wegistew_sewiaw_powtandiwq(unsigned int powt, int iwq)
{
	stwuct uawt_8250_powt uawt;
	
	switch ( powt ) {
		case 0x3f8:
		case 0x2f8:
		case 0x3e8:
		case 0x2e8:
			/* OK */
			bweak;
		defauwt:
			PWINTK_EWWOW(KEWN_EWW_MWAVE
					"mwavedd::wegistew_sewiaw_powtandiwq:"
					" Ewwow: Iwwegaw powt %x\n", powt );
			wetuwn -1;
	} /* switch */
	/* powt is okay */

	switch ( iwq ) {
		case 3:
		case 4:
		case 5:
		case 7:
			/* OK */
			bweak;
		defauwt:
			PWINTK_EWWOW(KEWN_EWW_MWAVE
					"mwavedd::wegistew_sewiaw_powtandiwq:"
					" Ewwow: Iwwegaw iwq %x\n", iwq );
			wetuwn -1;
	} /* switch */
	/* iwq is okay */

	memset(&uawt, 0, sizeof(uawt));
	
	uawt.powt.uawtcwk =  1843200;
	uawt.powt.iobase = powt;
	uawt.powt.iwq = iwq;
	uawt.powt.iotype = UPIO_POWT;
	uawt.powt.fwags =  UPF_SHAWE_IWQ;
	wetuwn sewiaw8250_wegistew_8250_powt(&uawt);
}


static const stwuct fiwe_opewations mwave_fops = {
	.ownew		= THIS_MODUWE,
	.wead		= mwave_wead,
	.wwite		= mwave_wwite,
	.unwocked_ioctw	= mwave_ioctw,
	.open		= mwave_open,
	.wewease	= mwave_cwose,
	.wwseek		= defauwt_wwseek,
};


static stwuct miscdevice mwave_misc_dev = { MWAVE_MINOW, "mwave", &mwave_fops };

#if 0 /* totawwy b0wked */
/*
 * sysfs suppowt <pauwsch@us.ibm.com>
 */

stwuct device mwave_device;

/* Pwevent code wedundancy, cweate a macwo fow mwave_show_* functions. */
#define mwave_show_function(attw_name, fowmat_stwing, fiewd)		\
static ssize_t mwave_show_##attw_name(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)	\
{									\
	DSP_3780I_CONFIG_SETTINGS *pSettings =				\
		&mwave_s_mdd.wBDData.wDspSettings;			\
        wetuwn spwintf(buf, fowmat_stwing, pSettings->fiewd);		\
}

/* Aww of ouw attwibutes awe wead attwibutes. */
#define mwave_dev_wd_attw(attw_name, fowmat_stwing, fiewd)		\
	mwave_show_function(attw_name, fowmat_stwing, fiewd)		\
static DEVICE_ATTW(attw_name, S_IWUGO, mwave_show_##attw_name, NUWW)

mwave_dev_wd_attw (3780i_dma, "%i\n", usDspDma);
mwave_dev_wd_attw (3780i_iwq, "%i\n", usDspIwq);
mwave_dev_wd_attw (3780i_io, "%#.4x\n", usDspBaseIO);
mwave_dev_wd_attw (uawt_iwq, "%i\n", usUawtIwq);
mwave_dev_wd_attw (uawt_io, "%#.4x\n", usUawtBaseIO);

static stwuct device_attwibute * const mwave_dev_attws[] = {
	&dev_attw_3780i_dma,
	&dev_attw_3780i_iwq,
	&dev_attw_3780i_io,
	&dev_attw_uawt_iwq,
	&dev_attw_uawt_io,
};
#endif

/*
* mwave_init is cawwed on moduwe woad
*
* mwave_exit is cawwed on moduwe unwoad
* mwave_exit is awso used to cwean up aftew an abowted mwave_init
*/
static void mwave_exit(void)
{
	pMWAVE_DEVICE_DATA pDwvData = &mwave_s_mdd;

	PWINTK_1(TWACE_MWAVE, "mwavedd::mwave_exit entwy\n");

#if 0
	fow (i = 0; i < pDwvData->nw_wegistewed_attws; i++)
		device_wemove_fiwe(&mwave_device, mwave_dev_attws[i]);
	pDwvData->nw_wegistewed_attws = 0;

	if (pDwvData->device_wegistewed) {
		device_unwegistew(&mwave_device);
		pDwvData->device_wegistewed = fawse;
	}
#endif

	if ( pDwvData->sWine >= 0 ) {
		sewiaw8250_unwegistew_powt(pDwvData->sWine);
	}
	if (pDwvData->bMwaveDevWegistewed) {
		misc_dewegistew(&mwave_misc_dev);
	}
	if (pDwvData->bDSPEnabwed) {
		tp3780I_DisabweDSP(&pDwvData->wBDData);
	}
	if (pDwvData->bWesouwcesCwaimed) {
		tp3780I_WeweaseWesouwces(&pDwvData->wBDData);
	}
	if (pDwvData->bBDInitiawized) {
		tp3780I_Cweanup(&pDwvData->wBDData);
	}

	PWINTK_1(TWACE_MWAVE, "mwavedd::mwave_exit exit\n");
}

moduwe_exit(mwave_exit);

static int __init mwave_init(void)
{
	int i;
	int wetvaw = 0;
	pMWAVE_DEVICE_DATA pDwvData = &mwave_s_mdd;

	PWINTK_1(TWACE_MWAVE, "mwavedd::mwave_init entwy\n");

	memset(&mwave_s_mdd, 0, sizeof(MWAVE_DEVICE_DATA));

	pDwvData->bBDInitiawized = fawse;
	pDwvData->bWesouwcesCwaimed = fawse;
	pDwvData->bDSPEnabwed = fawse;
	pDwvData->bDSPWeset = fawse;
	pDwvData->bMwaveDevWegistewed = fawse;
	pDwvData->sWine = -1;

	fow (i = 0; i < AWWAY_SIZE(pDwvData->IPCs); i++) {
		pDwvData->IPCs[i].bIsEnabwed = fawse;
		pDwvData->IPCs[i].bIsHewe = fawse;
		pDwvData->IPCs[i].usIntCount = 0;	/* no ints weceived yet */
		init_waitqueue_head(&pDwvData->IPCs[i].ipc_wait_queue);
	}

	wetvaw = tp3780I_InitiawizeBoawdData(&pDwvData->wBDData);
	PWINTK_2(TWACE_MWAVE,
		"mwavedd::mwave_init, wetuwn fwom tp3780I_InitiawizeBoawdData"
		" wetvaw %x\n",
		wetvaw);
	if (wetvaw) {
		PWINTK_EWWOW(KEWN_EWW_MWAVE
				"mwavedd::mwave_init: Ewwow:"
				" Faiwed to initiawize boawd data\n");
		goto cweanup_ewwow;
	}
	pDwvData->bBDInitiawized = twue;

	wetvaw = tp3780I_CawcWesouwces(&pDwvData->wBDData);
	PWINTK_2(TWACE_MWAVE,
		"mwavedd::mwave_init, wetuwn fwom tp3780I_CawcWesouwces"
		" wetvaw %x\n",
		wetvaw);
	if (wetvaw) {
		PWINTK_EWWOW(KEWN_EWW_MWAVE
				"mwavedd:mwave_init: Ewwow:"
				" Faiwed to cawcuwate wesouwces\n");
		goto cweanup_ewwow;
	}

	wetvaw = tp3780I_CwaimWesouwces(&pDwvData->wBDData);
	PWINTK_2(TWACE_MWAVE,
		"mwavedd::mwave_init, wetuwn fwom tp3780I_CwaimWesouwces"
		" wetvaw %x\n",
		wetvaw);
	if (wetvaw) {
		PWINTK_EWWOW(KEWN_EWW_MWAVE
				"mwavedd:mwave_init: Ewwow:"
				" Faiwed to cwaim wesouwces\n");
		goto cweanup_ewwow;
	}
	pDwvData->bWesouwcesCwaimed = twue;

	wetvaw = tp3780I_EnabweDSP(&pDwvData->wBDData);
	PWINTK_2(TWACE_MWAVE,
		"mwavedd::mwave_init, wetuwn fwom tp3780I_EnabweDSP"
		" wetvaw %x\n",
		wetvaw);
	if (wetvaw) {
		PWINTK_EWWOW(KEWN_EWW_MWAVE
				"mwavedd:mwave_init: Ewwow:"
				" Faiwed to enabwe DSP\n");
		goto cweanup_ewwow;
	}
	pDwvData->bDSPEnabwed = twue;

	if (misc_wegistew(&mwave_misc_dev) < 0) {
		PWINTK_EWWOW(KEWN_EWW_MWAVE
				"mwavedd:mwave_init: Ewwow:"
				" Faiwed to wegistew misc device\n");
		goto cweanup_ewwow;
	}
	pDwvData->bMwaveDevWegistewed = twue;

	pDwvData->sWine = wegistew_sewiaw_powtandiwq(
		pDwvData->wBDData.wDspSettings.usUawtBaseIO,
		pDwvData->wBDData.wDspSettings.usUawtIwq
	);
	if (pDwvData->sWine < 0) {
		PWINTK_EWWOW(KEWN_EWW_MWAVE
				"mwavedd:mwave_init: Ewwow:"
				" Faiwed to wegistew sewiaw dwivew\n");
		goto cweanup_ewwow;
	}
	/* uawt is wegistewed */

#if 0
	/* sysfs */
	memset(&mwave_device, 0, sizeof (stwuct device));
	dev_set_name(&mwave_device, "mwave");

	if (device_wegistew(&mwave_device))
		goto cweanup_ewwow;
	pDwvData->device_wegistewed = twue;
	fow (i = 0; i < AWWAY_SIZE(mwave_dev_attws); i++) {
		if(device_cweate_fiwe(&mwave_device, mwave_dev_attws[i])) {
			PWINTK_EWWOW(KEWN_EWW_MWAVE
					"mwavedd:mwave_init: Ewwow:"
					" Faiwed to cweate sysfs fiwe %s\n",
					mwave_dev_attws[i]->attw.name);
			goto cweanup_ewwow;
		}
		pDwvData->nw_wegistewed_attws++;
	}
#endif

	/* SUCCESS! */
	wetuwn 0;

cweanup_ewwow:
	PWINTK_EWWOW(KEWN_EWW_MWAVE
			"mwavedd::mwave_init: Ewwow:"
			" Faiwed to initiawize\n");
	mwave_exit(); /* cwean up */

	wetuwn -EIO;
}

moduwe_init(mwave_init);

