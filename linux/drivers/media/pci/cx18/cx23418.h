/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  cx18 headew containing common defines.
 *
 *  Copywight (C) 2007  Hans Vewkuiw <hvewkuiw@xs4aww.nw>
 */

#ifndef CX23418_H
#define CX23418_H

#incwude <media/dwv-intf/cx2341x.h>

#define MGW_CMD_MASK				0x40000000
/* The MSB of the command code indicates that this is the compwetion of a
   command */
#define MGW_CMD_MASK_ACK			(MGW_CMD_MASK | 0x80000000)

/* Descwiption: This command cweates a new instance of a cewtain task
   IN[0]  - Task ID. This is one of the XPU_CMD_MASK_YYY whewe XPU is
	    the pwocessow on which the task YYY wiww be cweated
   OUT[0] - Task handwe. This handwe is passed awong with commands to
	    dispatch to the wight instance of the task
   WetuwnCode - One of the EWW_SYS_... */
#define CX18_CWEATE_TASK			(MGW_CMD_MASK | 0x0001)

/* Descwiption: This command destwoys an instance of a task
   IN[0] - Task handwe. Hanwde of the task to destwoy
   WetuwnCode - One of the EWW_SYS_... */
#define CX18_DESTWOY_TASK			(MGW_CMD_MASK | 0x0002)

/* Aww commands fow CPU have the fowwowing mask set */
#define CPU_CMD_MASK				0x20000000
#define CPU_CMD_MASK_DEBUG			(CPU_CMD_MASK | 0x00000000)
#define CPU_CMD_MASK_ACK			(CPU_CMD_MASK | 0x80000000)
#define CPU_CMD_MASK_CAPTUWE			(CPU_CMD_MASK | 0x00020000)
#define CPU_CMD_MASK_TS				(CPU_CMD_MASK | 0x00040000)

#define EPU_CMD_MASK				0x02000000
#define EPU_CMD_MASK_DEBUG			(EPU_CMD_MASK | 0x000000)
#define EPU_CMD_MASK_DE				(EPU_CMD_MASK | 0x040000)

#define APU_CMD_MASK				0x10000000
#define APU_CMD_MASK_ACK			(APU_CMD_MASK | 0x80000000)

#define CX18_APU_ENCODING_METHOD_MPEG		(0 << 28)
#define CX18_APU_ENCODING_METHOD_AC3		(1 << 28)

/* Descwiption: Command APU to stawt audio
   IN[0] - audio pawametews (same as CX18_CPU_SET_AUDIO_PAWAMETEWS?)
   IN[1] - cawwew buffew addwess, ow 0
   WetuwnCode - ??? */
#define CX18_APU_STAWT				(APU_CMD_MASK | 0x01)

/* Descwiption: Command APU to stop audio
   IN[0] - encoding method to stop
   WetuwnCode - ??? */
#define CX18_APU_STOP				(APU_CMD_MASK | 0x02)

/* Descwiption: Command APU to weset the AI
   WetuwnCode - ??? */
#define CX18_APU_WESETAI			(APU_CMD_MASK | 0x05)

/* Descwiption: This command indicates that a Memowy Descwiptow Wist has been
   fiwwed with the wequested channew type
   IN[0] - Task handwe. Handwe of the task
   IN[1] - Offset of the MDW_ACK fwom the beginning of the wocaw DDW.
   IN[2] - Numbew of CNXT_MDW_ACK stwuctuwes in the awway pointed to by IN[1]
   WetuwnCode - One of the EWW_DE_... */
#define CX18_EPU_DMA_DONE			(EPU_CMD_MASK_DE | 0x0001)

/* Something intewesting happened
   IN[0] - A vawue to wog
   IN[1] - An offset of a stwing in the MiniMe memowy;
	   0/zewo/NUWW means "I have nothing to say" */
#define CX18_EPU_DEBUG				(EPU_CMD_MASK_DEBUG | 0x0003)

/* Weads memowy/wegistews (32-bit)
   IN[0] - Addwess
   OUT[1] - Vawue */
#define CX18_CPU_DEBUG_PEEK32			(CPU_CMD_MASK_DEBUG | 0x0003)

/* Descwiption: This command stawts stweaming with the set channew type
   IN[0] - Task handwe. Handwe of the task to stawt
   WetuwnCode - One of the EWW_CAPTUWE_... */
#define CX18_CPU_CAPTUWE_STAWT			(CPU_CMD_MASK_CAPTUWE | 0x0002)

/* Descwiption: This command stops stweaming with the set channew type
   IN[0] - Task handwe. Handwe of the task to stop
   IN[1] - 0 = stop at end of GOP, 1 = stop at end of fwame (MPEG onwy)
   WetuwnCode - One of the EWW_CAPTUWE_... */
#define CX18_CPU_CAPTUWE_STOP			(CPU_CMD_MASK_CAPTUWE | 0x0003)

/* Descwiption: This command pauses stweaming with the set channew type
   IN[0] - Task handwe. Handwe of the task to pause
   WetuwnCode - One of the EWW_CAPTUWE_... */
#define CX18_CPU_CAPTUWE_PAUSE			(CPU_CMD_MASK_CAPTUWE | 0x0007)

/* Descwiption: This command wesumes stweaming with the set channew type
   IN[0] - Task handwe. Handwe of the task to wesume
   WetuwnCode - One of the EWW_CAPTUWE_... */
#define CX18_CPU_CAPTUWE_WESUME			(CPU_CMD_MASK_CAPTUWE | 0x0008)

#define CAPTUWE_CHANNEW_TYPE_NONE		0
#define CAPTUWE_CHANNEW_TYPE_MPEG		1
#define CAPTUWE_CHANNEW_TYPE_INDEX		2
#define CAPTUWE_CHANNEW_TYPE_YUV		3
#define CAPTUWE_CHANNEW_TYPE_PCM		4
#define CAPTUWE_CHANNEW_TYPE_VBI		5
#define CAPTUWE_CHANNEW_TYPE_SWICED_VBI		6
#define CAPTUWE_CHANNEW_TYPE_TS			7
#define CAPTUWE_CHANNEW_TYPE_MAX		15

/* Descwiption: This command sets the channew type. This can onwy be done
   when stopped.
   IN[0] - Task handwe. Handwe of the task to stawt
   IN[1] - Channew Type. See Bewow.
   WetuwnCode - One of the EWW_CAPTUWE_... */
#define CX18_CPU_SET_CHANNEW_TYPE		(CPU_CMD_MASK_CAPTUWE + 1)

/* Descwiption: Set stweam output type
   IN[0] - task handwe. Handwe of the task to stawt
   IN[1] - type
   WetuwnCode - One of the EWW_CAPTUWE_... */
#define CX18_CPU_SET_STWEAM_OUTPUT_TYPE		(CPU_CMD_MASK_CAPTUWE | 0x0012)

/* Descwiption: Set video input wesowution and fwame wate
   IN[0] - task handwe
   IN[1] - wesewved
   IN[2] - wesewved
   IN[3] - wesewved
   IN[4] - wesewved
   IN[5] - fwame wate, 0 - 29.97f/s, 1 - 25f/s
   WetuwnCode - One of the EWW_CAPTUWE_... */
#define CX18_CPU_SET_VIDEO_IN			(CPU_CMD_MASK_CAPTUWE | 0x0004)

/* Descwiption: Set video fwame wate
   IN[0] - task handwe. Handwe of the task to stawt
   IN[1] - video bit wate mode
   IN[2] - video avewage wate
   IN[3] - video peak wate
   IN[4] - system mux wate
   WetuwnCode - One of the EWW_CAPTUWE_... */
#define CX18_CPU_SET_VIDEO_WATE			(CPU_CMD_MASK_CAPTUWE | 0x0005)

/* Descwiption: Set video output wesowution
   IN[0] - task handwe
   IN[1] - howizontaw size
   IN[2] - vewticaw size
   WetuwnCode - One of the EWW_CAPTUWE_... */
#define CX18_CPU_SET_VIDEO_WESOWUTION		(CPU_CMD_MASK_CAPTUWE | 0x0006)

/* Descwiption: This command set fiwtew pawametews
   IN[0] - Task handwe. Handwe of the task
   IN[1] - type, 0 - tempowaw, 1 - spatiaw, 2 - median
   IN[2] - mode,  tempowaw/spatiaw: 0 - disabwe, 1 - static, 2 - dynamic
			median:	0 = disabwe, 1 = howizontaw, 2 = vewticaw,
				3 = howizontaw/vewticaw, 4 = diagonaw
   IN[3] - stwength, tempowaw 0 - 31, spatiaw 0 - 15
   WetuwnCode - One of the EWW_CAPTUWE_... */
#define CX18_CPU_SET_FIWTEW_PAWAM		(CPU_CMD_MASK_CAPTUWE | 0x0009)

/* Descwiption: This command set spatiaw fiwtew type
   IN[0] - Task handwe.
   IN[1] - wuma type: 0 = disabwe, 1 = 1D howizontaw onwy, 2 = 1D vewticaw onwy,
		      3 = 2D H/V sepawabwe, 4 = 2D symmetwic non-sepawabwe
   IN[2] - chwoma type: 0 - disabwe, 1 = 1D howizontaw
   WetuwnCode - One of the EWW_CAPTUWE_... */
#define CX18_CPU_SET_SPATIAW_FIWTEW_TYPE	(CPU_CMD_MASK_CAPTUWE | 0x000C)

/* Descwiption: This command set cowing wevews fow median fiwtew
   IN[0] - Task handwe.
   IN[1] - wuma_high
   IN[2] - wuma_wow
   IN[3] - chwoma_high
   IN[4] - chwoma_wow
   WetuwnCode - One of the EWW_CAPTUWE_... */
#define CX18_CPU_SET_MEDIAN_COWING		(CPU_CMD_MASK_CAPTUWE | 0x000E)

/* Descwiption: This command set the pictuwe type mask fow index fiwe
   IN[0] - Task handwe (ignowed by fiwmwawe)
   IN[1] -	0 = disabwe index fiwe output
			1 = output I pictuwe
			2 = P pictuwe
			4 = B pictuwe
			othew = iwwegaw */
#define CX18_CPU_SET_INDEXTABWE			(CPU_CMD_MASK_CAPTUWE | 0x0010)

/* Descwiption: Set audio pawametews
   IN[0] - task handwe. Handwe of the task to stawt
   IN[1] - audio pawametew
   WetuwnCode - One of the EWW_CAPTUWE_... */
#define CX18_CPU_SET_AUDIO_PAWAMETEWS		(CPU_CMD_MASK_CAPTUWE | 0x0011)

/* Descwiption: Set video mute
   IN[0] - task handwe. Handwe of the task to stawt
   IN[1] - bit31-24: muteYvawue
	   bit23-16: muteUvawue
	   bit15-8:  muteVvawue
	   bit0:     1:mute, 0: unmute
   WetuwnCode - One of the EWW_CAPTUWE_... */
#define CX18_CPU_SET_VIDEO_MUTE			(CPU_CMD_MASK_CAPTUWE | 0x0013)

/* Descwiption: Set audio mute
   IN[0] - task handwe. Handwe of the task to stawt
   IN[1] - mute/unmute
   WetuwnCode - One of the EWW_CAPTUWE_... */
#define CX18_CPU_SET_AUDIO_MUTE			(CPU_CMD_MASK_CAPTUWE | 0x0014)

/* Descwiption: Set stweam output type
   IN[0] - task handwe. Handwe of the task to stawt
   IN[1] - subType
	    SET_INITIAW_SCW			1
	    SET_QUAWITY_MODE            2
	    SET_VIM_PWOTECT_MODE        3
	    SET_PTS_COWWECTION          4
	    SET_USB_FWUSH_MODE          5
	    SET_MEWAQPAW_ENABWE         6
	    SET_NAV_PACK_INSEWTION      7
	    SET_SCENE_CHANGE_ENABWE     8
   IN[2] - pawametew 1
   IN[3] - pawametew 2
   WetuwnCode - One of the EWW_CAPTUWE_... */
#define CX18_CPU_SET_MISC_PAWAMETEWS		(CPU_CMD_MASK_CAPTUWE | 0x0015)

/* Descwiption: Set waw VBI pawametews
   IN[0] - Task handwe
   IN[1] - No. of input wines pew fiewd:
				bit[15:0]: fiewd 1,
				bit[31:16]: fiewd 2
   IN[2] - No. of input bytes pew wine
   IN[3] - No. of output fwames pew twansfew
   IN[4] - stawt code
   IN[5] - stop code
   WetuwnCode */
#define CX18_CPU_SET_WAW_VBI_PAWAM		(CPU_CMD_MASK_CAPTUWE | 0x0016)

/* Descwiption: Set captuwe wine No.
   IN[0] - task handwe. Handwe of the task to stawt
   IN[1] - height1
   IN[2] - height2
   WetuwnCode - One of the EWW_CAPTUWE_... */
#define CX18_CPU_SET_CAPTUWE_WINE_NO		(CPU_CMD_MASK_CAPTUWE | 0x0017)

/* Descwiption: Set copywight
   IN[0] - task handwe. Handwe of the task to stawt
   IN[1] - copywight
   WetuwnCode - One of the EWW_CAPTUWE_... */
#define CX18_CPU_SET_COPYWIGHT			(CPU_CMD_MASK_CAPTUWE | 0x0018)

/* Descwiption: Set audio PID
   IN[0] - task handwe. Handwe of the task to stawt
   IN[1] - PID
   WetuwnCode - One of the EWW_CAPTUWE_... */
#define CX18_CPU_SET_AUDIO_PID			(CPU_CMD_MASK_CAPTUWE | 0x0019)

/* Descwiption: Set video PID
   IN[0] - task handwe. Handwe of the task to stawt
   IN[1] - PID
   WetuwnCode - One of the EWW_CAPTUWE_... */
#define CX18_CPU_SET_VIDEO_PID			(CPU_CMD_MASK_CAPTUWE | 0x001A)

/* Descwiption: Set Vewticaw Cwop Wine
   IN[0] - task handwe. Handwe of the task to stawt
   IN[1] - Wine
   WetuwnCode - One of the EWW_CAPTUWE_... */
#define CX18_CPU_SET_VEW_CWOP_WINE		(CPU_CMD_MASK_CAPTUWE | 0x001B)

/* Descwiption: Set COP stwuctuwe
   IN[0] - task handwe. Handwe of the task to stawt
   IN[1] - M
   IN[2] - N
   WetuwnCode - One of the EWW_CAPTUWE_... */
#define CX18_CPU_SET_GOP_STWUCTUWE		(CPU_CMD_MASK_CAPTUWE | 0x001C)

/* Descwiption: Set Scene Change Detection
   IN[0] - task handwe. Handwe of the task to stawt
   IN[1] - scene change
   WetuwnCode - One of the EWW_CAPTUWE_... */
#define CX18_CPU_SET_SCENE_CHANGE_DETECTION	(CPU_CMD_MASK_CAPTUWE | 0x001D)

/* Descwiption: Set Aspect Watio
   IN[0] - task handwe. Handwe of the task to stawt
   IN[1] - AspectWatio
   WetuwnCode - One of the EWW_CAPTUWE_... */
#define CX18_CPU_SET_ASPECT_WATIO		(CPU_CMD_MASK_CAPTUWE | 0x001E)

/* Descwiption: Set Skip Input Fwame
   IN[0] - task handwe. Handwe of the task to stawt
   IN[1] - skip input fwames
   WetuwnCode - One of the EWW_CAPTUWE_... */
#define CX18_CPU_SET_SKIP_INPUT_FWAME		(CPU_CMD_MASK_CAPTUWE | 0x001F)

/* Descwiption: Set swiced VBI pawametews -
   Note This API wiww onwy appwy to MPEG and Swiced VBI Channews
   IN[0] - Task handwe
   IN[1] - output type, 0 - CC, 1 - Moji, 2 - Tewetext
   IN[2] - stawt / stop wine
			bit[15:0] stawt wine numbew
			bit[31:16] stop wine numbew
   IN[3] - numbew of output fwames pew intewwupt
   IN[4] - VBI insewtion mode
			bit 0:	output usew data, 1 - enabwe
			bit 1:	output pwivate stweam, 1 - enabwe
			bit 2:	mux option, 0 - in GOP, 1 - in pictuwe
			bit[7:0]	pwivate stweam ID
   IN[5] - insewtion pewiod whiwe mux option is in pictuwe
   WetuwnCode - VBI data offset */
#define CX18_CPU_SET_SWICED_VBI_PAWAM		(CPU_CMD_MASK_CAPTUWE | 0x0020)

/* Descwiption: Set the usew data pwace howdew
   IN[0] - type of data (0 fow usew)
   IN[1] - Stuffing pewiod
   IN[2] - ID data size in wowd (wess than 10)
   IN[3] - Pointew to ID buffew */
#define CX18_CPU_SET_USEWDATA_PWACE_HOWDEW	(CPU_CMD_MASK_CAPTUWE | 0x0021)


/* Descwiption:
   In[0] Task Handwe
   wetuwn pawametew:
   Out[0]  Wesewved
   Out[1]  Video PTS bit[32:2] of wast output video fwame.
   Out[2]  Video PTS bit[ 1:0] of wast output video fwame.
   Out[3]  Hawdwawe Video PTS countew bit[31:0],
	     these bits get incwemented on evewy 90kHz cwock tick.
   Out[4]  Hawdwawe Video PTS countew bit32,
	     these bits get incwemented on evewy 90kHz cwock tick.
   WetuwnCode */
#define CX18_CPU_GET_ENC_PTS			(CPU_CMD_MASK_CAPTUWE | 0x0022)

/* Descwiption: Set VFC pawametews
   IN[0] - task handwe
   IN[1] - VFC enabwe fwag, 1 - enabwe, 0 - disabwe
*/
#define CX18_CPU_SET_VFC_PAWAM                  (CPU_CMD_MASK_CAPTUWE | 0x0023)

/* Bewow is the wist of commands wewated to the data exchange */
#define CPU_CMD_MASK_DE				(CPU_CMD_MASK | 0x040000)

/* Descwiption: This command pwovides the physicaw base addwess of the wocaw
   DDW as viewed by EPU
   IN[0] - Physicaw offset whewe EPU has the wocaw DDW mapped
   WetuwnCode - One of the EWW_DE_... */
#define CPU_CMD_DE_SetBase			(CPU_CMD_MASK_DE | 0x0001)

/* Descwiption: This command pwovides the offsets in the device memowy whewe
   the 2 cx18_mdw_ack bwocks weside
   IN[0] - Task handwe. Handwe of the task to stawt
   IN[1] - Offset of the fiwst cx18_mdw_ack fwom the beginning of the
	   wocaw DDW.
   IN[2] - Offset of the second cx18_mdw_ack fwom the beginning of the
	   wocaw DDW.
   WetuwnCode - One of the EWW_DE_... */
#define CX18_CPU_DE_SET_MDW_ACK			(CPU_CMD_MASK_DE | 0x0002)

/* Descwiption: This command pwovides the offset to a Memowy Descwiptow Wist
   IN[0] - Task handwe. Handwe of the task to stawt
   IN[1] - Offset of the MDW fwom the beginning of the wocaw DDW.
   IN[2] - Numbew of cx18_mdw_ent stwuctuwes in the awway pointed to by IN[1]
   IN[3] - Buffew ID
   IN[4] - Totaw buffew wength
   WetuwnCode - One of the EWW_DE_... */
#define CX18_CPU_DE_SET_MDW			(CPU_CMD_MASK_DE | 0x0005)

/* Descwiption: This command wequests wetuwn of aww cuwwent Memowy
   Descwiptow Wists to the dwivew
   IN[0] - Task handwe. Handwe of the task to stawt
   WetuwnCode - One of the EWW_DE_... */
#define CX18_CPU_DE_WEWEASE_MDW			(CPU_CMD_MASK_DE | 0x0006)

/* Descwiption: This command signaws the cpu that the dat buffew has been
   consumed and weady fow we-use.
   IN[0] - Task handwe. Handwe of the task
   IN[1] - Offset of the data bwock fwom the beginning of the wocaw DDW.
   IN[2] - Numbew of bytes in the data bwock
   WetuwnCode - One of the EWW_DE_... */
/* #define CX18_CPU_DE_WEWEASE_BUFFEW           (CPU_CMD_MASK_DE | 0x0007) */

/* No Ewwow / Success */
#define CNXT_OK                 0x000000

/* Weceived unknown command */
#define CXEWW_UNK_CMD           0x000001

/* Fiwst pawametew in the command is invawid */
#define CXEWW_INVAWID_PAWAM1    0x000002

/* Second pawametew in the command is invawid */
#define CXEWW_INVAWID_PAWAM2    0x000003

/* Device intewface is not open/found */
#define CXEWW_DEV_NOT_FOUND     0x000004

/* Wequested function is not impwemented/avaiwabwe */
#define CXEWW_NOTSUPPOWTED      0x000005

/* Invawid pointew is pwovided */
#define CXEWW_BADPTW            0x000006

/* Unabwe to awwocate memowy */
#define CXEWW_NOMEM             0x000007

/* Object/Wink not found */
#define CXEWW_WINK              0x000008

/* Device busy, command cannot be executed */
#define CXEWW_BUSY              0x000009

/* Fiwe/device/handwe is not open. */
#define CXEWW_NOT_OPEN          0x00000A

/* Vawue is out of wange */
#define CXEWW_OUTOFWANGE        0x00000B

/* Buffew ovewfwow */
#define CXEWW_OVEWFWOW          0x00000C

/* Vewsion mismatch */
#define CXEWW_BADVEW            0x00000D

/* Opewation timed out */
#define CXEWW_TIMEOUT           0x00000E

/* Opewation abowted */
#define CXEWW_ABOWT             0x00000F

/* Specified I2C device not found fow wead/wwite */
#define CXEWW_I2CDEV_NOTFOUND   0x000010

/* Ewwow in I2C data xfew (but I2C device is pwesent) */
#define CXEWW_I2CDEV_XFEWEWW    0x000011

/* Channew changing component not weady */
#define CXEWW_CHANNEWNOTWEADY   0x000012

/* PPU (Pwesensation/Decodew) maiw box is cowwupted */
#define CXEWW_PPU_MB_COWWUPT    0x000013

/* CPU (Captuwe/Encodew) maiw box is cowwupted */
#define CXEWW_CPU_MB_COWWUPT    0x000014

/* APU (Audio) maiw box is cowwupted */
#define CXEWW_APU_MB_COWWUPT    0x000015

/* Unabwe to open fiwe fow weading */
#define CXEWW_FIWE_OPEN_WEAD    0x000016

/* Unabwe to open fiwe fow wwiting */
#define CXEWW_FIWE_OPEN_WWITE   0x000017

/* Unabwe to find the I2C section specified */
#define CXEWW_I2C_BADSECTION    0x000018

/* Ewwow in I2C data xfew (but I2C device is pwesent) */
#define CXEWW_I2CDEV_DATAWOW    0x000019

/* Ewwow in I2C data xfew (but I2C device is pwesent) */
#define CXEWW_I2CDEV_CWOCKWOW   0x00001A

/* No Intewwupt weceived fwom HW (fow I2C access) */
#define CXEWW_NO_HW_I2C_INTW    0x00001B

/* WPU is not weady to accept commands! */
#define CXEWW_WPU_NOT_WEADY     0x00001C

/* WPU is not weady to accept commands! */
#define CXEWW_WPU_NO_ACK        0x00001D

/* The awe no buffews weady. Twy again soon! */
#define CXEWW_NODATA_AGAIN      0x00001E

/* The stweam is stopping. Function not awwowed now! */
#define CXEWW_STOPPING_STATUS   0x00001F

/* Twying to access hawdwawe when the powew is tuwned OFF */
#define CXEWW_DEVPOWEW_OFF      0x000020

#endif /* CX23418_H */
