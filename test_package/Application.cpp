/* Copyright (C) Novofina Ltd., Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <iostream>
#include <math.h>

#ifdef _MSC_VER
#pragma warning( disable : 4503 4355 4786 )
#else
#include <quickfix/config.h>
#endif

#include <quickfix/FixValues.h>
#include <quickfix/Session.h>

#include "Application.h"

void Application::onLogon(const FIX::SessionID& sessionID)
{

}

void Application::onLogout(const FIX::SessionID& sessionID)
{

}

void Application::fromApp(const FIX::Message& message, const FIX::SessionID& sessionID)
throw ( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType)
{
    crack(message, sessionID);
}

void Application::toApp(FIX::Message& message, const FIX::SessionID& sessionID)
throw ( FIX::DoNotSend)
{
    try
    {
        FIX::PossDupFlag possDupFlag;
        message.getHeader().getField(possDupFlag);
        if (possDupFlag) throw FIX::DoNotSend();
    }
    catch (FIX::FieldNotFound&)
    {
    }
}


void Application::onNew(const FIX42::ExecutionReport& message)
{
    FIX::Symbol symbol;
    if (message.isSet(symbol)) message.get(symbol);

    FIX::ClOrdID clOrdID;
    if (message.isSet(clOrdID)) message.get(clOrdID);

    FIX::OrdType ordType;
    if (message.isSet(ordType)) message.get(ordType);

    FIX::Price price;
    FIX::StopPx StopPx;
    
    if (ordType == FIX::OrdType_LIMIT)
    {
        if (message.isSet(price)) message.get(price);
    }
    else if (ordType == FIX::OrdType_STOP)
    {
        if (message.isSet(StopPx)) message.get(StopPx);
    }
    else if (ordType == FIX::OrdType_MARKET)
    {

    }

    FIX::OrderQty orderQty;
    if (message.isSet(orderQty))
        message.get(orderQty);

    message.toString();
}

void Application::onReplace(const FIX42::ExecutionReport& message)
{
    FIX::Symbol symbol;
    if (message.isSet(symbol))
        message.get(symbol);
    FIX::OrigClOrdID origClOrdID;
    if (message.isSet(origClOrdID))
        message.get(origClOrdID);
    FIX::ClOrdID clOrdID;
    if (message.isSet(clOrdID))
        message.get(clOrdID);
    FIX::Price price;
    if (message.isSet(price))
        message.get(price);
    FIX::OrderQty orderQty;
    if (message.isSet(orderQty))
        message.get(orderQty);
}

void Application::onCanceled(const FIX42::ExecutionReport& message)
{
    FIX::Symbol symbol;
    if (message.isSet(symbol))
        message.get(symbol);
    FIX::OrigClOrdID origClOrdID;
    if (message.isSet(origClOrdID))
        message.get(origClOrdID);
    FIX::Price price;
    if (message.isSet(price))
        message.get(price);
    FIX::OrderQty orderQty;
    if (message.isSet(orderQty))
        message.get(orderQty);
}

void Application::onFilled(const FIX42::ExecutionReport& message, bool partial)
{
    FIX::Symbol symbol;
    if (message.isSet(symbol))
        message.get(symbol);
    FIX::OrigClOrdID origClOrdID;
    if (message.isSet(origClOrdID))
        message.get(origClOrdID);
    FIX::LastPx lastPx;
    if (message.isSet(lastPx))
        message.get(lastPx);
    FIX::LastShares lastShares;
    if (message.isSet(lastShares))
        message.get(lastShares);
    FIX::CumQty cumQty;
    if (message.isSet(cumQty))
        message.get(cumQty);

}

void Application::onOther(const FIX42::ExecutionReport& message)
{
    FIX::Symbol symbol;
    if (message.isSet(symbol))
        message.get(symbol);
    FIX::OrigClOrdID origClOrdID;
    if (message.isSet(origClOrdID))
        message.get(origClOrdID);
    FIX::Price price;
    if (message.isSet(price))
        message.get(price);
    FIX::OrderQty orderQty;
    if (message.isSet(orderQty))
        message.get(orderQty);
}


void Application::onMessage(const FIX42::ExecutionReport& message, const FIX::SessionID&)
{

FIX::ClOrdID clOrdID;
    message.get(clOrdID);

    FIX::OrdStatus ordStatus;    
    if (message.isSet(ordStatus))
        message.get(ordStatus);

    FIX::CumQty cumQty;
    message.get(cumQty);
    FIX::LastPx lastPx;
    message.get(lastPx);
    FIX::LastShares lastShares;
    message.get(lastShares);
    FIX::OrderQty orderQty;
    message.get(orderQty);
    FIX::OrdType ordType;
    message.get(ordType);

    FIX::Price price;
    if (message.isSet(price))
        message.get(price);

    FIX::Side side;
    message.get(side);
    FIX::Symbol symbol;
    message.get(symbol);
    FIX::LeavesQty leavesQty;
    message.get(leavesQty);
    FIX::ExecTransType execTransType;
    message.get(execTransType);



    FIX::OrigClOrdID origClOrdID;

    if (message.isSet(origClOrdID))
        message.get(origClOrdID);
}

void Application::onMessage(const FIX42::OrderCancelReject&, const FIX::SessionID&) {
}


