/**********************************************************************************
** Copyright � 2008 Broadcom
**
** This program  is the  proprietary software  of Broadcom  Corporation and/or  its
** licensors, and may only be used, duplicated, modified or distributed pursuant to
** the  terms and  conditions of  a separate,  written license  agreement executed
** between you and Broadcom (an "Authorized  License").  Except as set forth in  an
** Authorized License, Broadcom  grants no license  (express or implied),  right to
** use, or waiver of any kind with respect to the Software, and Broadcom  expressly
** reserves all rights in and to the Software and all intellectual property  rights
** therein.  IF YOU HAVE NO AUTHORIZED LICENSE, THEN YOU HAVE NO RIGHT TO USE  THIS
** SOFTWARE IN ANY WAY, AND SHOULD IMMEDIATELY NOTIFY BROADCOM AND DISCONTINUE  ALL
** USE OF THE SOFTWARE.
**
** Except as expressly set forth in the Authorized License,
**
** 1.      This  program,  including  its  structure,  sequence  and  organization,
** constitutes  the valuable  trade secrets  of Broadcom,  and you  shall use  all
** reasonable  efforts to  protect the  confidentiality thereof,  and to  use this
** information only  in connection  with your  use of  Broadcom integrated  circuit
** products.
**
** 2.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS  IS"
** AND  WITH  ALL  FAULTS  AND  BROADCOM  MAKES  NO  PROMISES,  REPRESENTATIONS  OR
** WARRANTIES, EITHER EXPRESS,  IMPLIED, STATUTORY, OR  OTHERWISE, WITH RESPECT  TO
** THE SOFTWARE.  BROADCOM SPECIFICALLY DISCLAIMS ANY AND ALL IMPLIED WARRANTIES OF
** TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR PURPOSE,  LACK
** OF  VIRUSES,  ACCURACY OR  COMPLETENESS,  QUIET ENJOYMENT,  QUIET  POSSESSION OR
** CORRESPONDENCE TO DESCRIPTION. YOU ASSUME THE ENTIRE RISK ARISING OUT OF USE  OR
** PERFORMANCE OF THE SOFTWARE.
**
** 3.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL BROADCOM OR ITS
** LICENSORS BE  LIABLE FOR  (i) CONSEQUENTIAL,  INCIDENTAL, SPECIAL,  INDIRECT, OR
** EXEMPLARY DAMAGES WHATSOEVER ARISING OUT OF  OR IN ANY WAY RELATING TO  YOUR USE
** OF OR INABILITY  TO USE THE  SOFTWARE EVEN IF  BROADCOM HAS BEEN  ADVISED OF THE
** POSSIBILITY OF SUCH DAMAGES; OR (ii) ANY AMOUNT IN EXCESS OF THE AMOUNT ACTUALLY
** PAID FOR THE SOFTWARE ITSELF OR U.S. $1, WHICHEVER IS GREATER. THESE LIMITATIONS
** SHALL APPLY  NOTWITHSTANDING ANY  FAILURE OF  ESSENTIAL PURPOSE  OF ANY  LIMITED
** REMEDY.
***********************************************************************************/

/***********************************************************************************
**
**    Description:
**
**      This file contains the configuration verification logic for cmgrCfg.h.
**
***********************************************************************************/

#ifndef __CMGR_CFG_CHK__H__INCLUDED__
#define __CMGR_CFG_CHK__H__INCLUDED__


#if !CMGRCFG_THREAD_STACK
#   error CMGRCFG_THREAD_STACK value must be set
#endif

#if ( CMGRCFG_THREAD_SLEEP < 50 )
#   error CMGRCFG_THREAD_SLEEP cannot be less than 50 msec
#endif

#if !CMGRCFG_THREAD_QDEPTH
#   error CMGRCFG_THREAD_QDEPTH cannot be NULL!
#endif

#if ( CMGRCFG_USER_MAX < 1 )
#   error CMGRCFG_USER_MAX must be at least 1
#endif

#if ( CMGRCFG_STATE_MAX < 2 )
#   error CMGRCFG_STATE_MAX must be at least 2
#endif

#if ( CMGRCFG_EVENT_MAX < 2 )
#   error CMGRCFG_EVENT_MAX must be at least 2
#endif

#if ( CMGRCFG_MEDSES_MAX < 1 )
#   error CMGRCFG_MEDSES_MAX must be at least 1
#endif

#if ( CMGRCFG_SRVSES_MAX < 2 )
#   error CMGRCFG_SRVSES_MAX must be at least 2
#endif

#if ( CMGRCFG_AUTOCALL_MAX < 2 )
#   error CMGRCFG_AUTOCALL_MAX must be at least 2
#endif

#if ( CMGRCFG_CFG_PROFILE < CMGRCFG_CFG_PROFILE_RFC3261 )
#   error CMGRCFG_CFG_PROFILE is invalid.
#endif
#if ( CMGRCFG_CFG_PROFILE > CMGRCFG_CFG_PROFILE_CUSTOM )
#   error CMGRCFG_CFG_PROFILE is invalid.
#endif

#if ( CMGRCFG_CFG_PROFILE == CMGRCFG_CFG_PROFILE_IMS ) && \
    ( !CMGRCFG_OUTBOUND_KEEP_ALIVE )
#   error CMGRCFG_OUTBOUND_KEEP_ALIVE must be enabled with CMGRCFG_CFG_PROFILE_IMS
#endif

#endif /* __CMGR_CFG_CHK__H__INCLUDED__ */
