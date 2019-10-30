//==============================================================================
//==============================================================================
//
//              Copyright(c) 2008 Media5 Corporation ("Media5")
//
//  NOTICE:
//   This document contains information that is confidential and proprietary to
//   Media5.
//
//   Media5 reserves all rights to this document as well as to the Intellectual
//   Property of the document and the technology and know-how that it includes
//   and represents.
//
//   This publication cannot be reproduced, neither in whole nor in part, in any
//   form whatsoever without prior written approval by Media5.
//
//   Media5 reserves the right to revise this publication and make changes at
//   any time and without the obligation to notify any person and/or entity of
//   such revisions and/or changes.
//
//==============================================================================
//==============================================================================
#ifndef MXG_IUAIMPPPAGERECEIVERMGR_H
//M5T_INTERNAL_USE_BEGIN
#define MXG_IUAIMPPPAGERECEIVERMGR_H

//==============================================================================
//====  INCLUDES + FORWARD DECLARATIONS  =======================================
//==============================================================================


//-- M5T Global definitions
//---------------------------
#ifndef MXG_MXCONFIG_H
#include "Config/MxConfig.h"
#endif


MX_NAMESPACE_START(MXD_GNS)


//-- Forward Declarations
//-------------------------
class IEComUnknown;
class IUaImppPageReceiver;
class CSipMessageBody;


//==============================================================================
//====  CONSTANTS + DEFINES  ===================================================
//==============================================================================

//M5T_INTERNAL_USE_END

//==============================================================================
//====  NEW TYPE DEFINITIONS  ==================================================
//==============================================================================

//==============================================================================
//== Class: IUaImppPageReceiverMgr
//========================================
//<GROUP TID_PACKAGE_UAIMPP_CLASSES>
//
// Summary:
//   This interface defines the events that the IUaImppPageReceiver component
//   reports.
//
// Description:
//  This interface defines the events that the IUaImppPageReceiver component
//  reports.
//
// Location:
//   SceUaImpp/IUaImppPageReceiverMgr.h
//
// See Also:
//   IUaImppPageReceiver, IUaImppPageSender
//
//==============================================================================
class IUaImppPageReceiverMgr
{
//-- Friend Declarations
//------------------------


//-- Published Interface
//------------------------
public:

    //==========================================================================
    //==
    //==  EvMessageReceived
    //==
    //==========================================================================
    //
    //  Summary:
    //      Reports that an IM message was received.
    //
    //  Parameters:
    //    pComponent:
    //      The Page Receiver instance reporting this event.
    //
    //    opqTransaction:
    //      A transaction identifier generated by the page receiver handling
    //      this request. The application must use this identifier to answer the
    //      request through IUaImppPageReceiver::SendResponse.
    //
    //    rPayload:
    //      The actual payload, in CSipMessageBody format.
    //
    //    pAdditionalParameters:
    //      Additional parameters associated with this incoming request. Can be
    //      NULL if no additional parameters are present.
    //
    //      This returned parameter is an ECOM object. The application can query
    //      for specific event interfaces on this object to access the
    //      additional event information.
    //
    //      If it is NULL, it means no additional information was available.
    //
    //  Description:
    //      Reports that an IM message was received. Upon receiving this event,
    //      the application should try to interpret the payload and it should
    //      send a response to the request as soon as possible.
    //
    //  See Also:
    //      IUaImppPageReceiver::SendResponse
    //
    //==========================================================================
    virtual void EvMessageReceived(IN IUaImppPageReceiver* pComponent,
                                   IN mxt_opaque opqTransaction,
                                   IN const CSipMessageBody& rPayload,
                                   IN IEComUnknown* pAdditionalParameters) = 0;


//M5T_INTERNAL_USE_BEGIN

//-- Hidden Methods
//-------------------
protected:
    //-- << Constructors / Destructors / Operators >>
    //-------------------------------------------------

    // Summary:
    //  Default Constructor.
    //-----------------------
    IUaImppPageReceiverMgr(){};

    // Summary:
    //  Destructor.
    //--------------
    virtual ~IUaImppPageReceiverMgr(){};


private:
    //-- << Deactivated Constructors / Destructors / Operators >>
    //-------------------------------------------------------------

    // Summary:
    //  Copy Constructor.
    //--------------------
    IUaImppPageReceiverMgr(IN const IUaImppPageReceiverMgr& rSrc);

    // Summary:
    //  Assignment Operator.
    //-----------------------
    IUaImppPageReceiverMgr& operator=(IN const IUaImppPageReceiverMgr& rSrc);


//-- Hidden Data Members
//------------------------
protected:
private:

    //M5T_INTERNAL_USE_END

};


//==============================================================================
//====  INLINE METHODS  ========================================================
//==============================================================================


MX_NAMESPACE_END(MXD_GNS)


#endif //-- #ifndef MXG_IUAIMPPPAGERECEIVERMGR_H

