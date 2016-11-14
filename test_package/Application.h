/* Copyright (C) Novofina Ltd., Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#ifndef TRADECLIENT_APPLICATION_H
#define TRADECLIENT_APPLICATION_H

#include <quickfix/Application.h>
#include <quickfix/Message.h>
#include <quickfix/MessageCracker.h>
#include <quickfix/Values.h>
#include <quickfix/Mutex.h>


#include <quickfix/fix42/NewOrderSingle.h>
#include <quickfix/fix42/ExecutionReport.h>
#include <quickfix/fix42/OrderCancelRequest.h>
#include <quickfix/fix42/OrderCancelReject.h>
#include <quickfix/fix42/OrderCancelReplaceRequest.h>

#include <queue>


const std::string STYLE_BOLD("\033[1m");
const std::string STYLE_INVERT("\033[7m");

const std::string FG_BLACK("\033[30m");
const std::string FG_RED("\033[31m");
const std::string FG_GREEN("\033[32m");
const std::string FG_YELLOW("\033[33m");
const std::string FG_BLUE("\033[34m");
const std::string FG_MAGENTA("\033[35m");
const std::string FG_CYAN("\033[36m");
const std::string FG_WHITE("\033[37m");

const std::string FG_DEFAULT("\033[39m");

const std::string BG_BLACK("\033[40m");
const std::string BG_RED("\033[41m");
const std::string BG_GREEN("\033[42m");
const std::string BG_YELLOW("\033[43m");
const std::string BG_BLUE("\033[44m");
const std::string BG_MAGENTA("\033[45m");
const std::string BG_CYAN("\033[46m");
const std::string BG_WHITE("\033[47m");

const std::string BG_DEFAULT("\033[49m");

const std::string STYLE_NORM("\033[0m"); 
                            
const std::string STYLE_RESET("\033[0;39;49m\n");


class Application :
      public FIX::Application,
      public FIX::MessageCracker
{
public:
  void run();

private:
  void onCreate( const FIX::SessionID& ) {}

  void onLogon( const FIX::SessionID& sessionID );

  void onLogout( const FIX::SessionID& sessionID );

  void toAdmin( FIX::Message&, const FIX::SessionID& ) {}

  void toApp( FIX::Message&, const FIX::SessionID& ) throw( FIX::DoNotSend );

  void fromAdmin( const FIX::Message&, const FIX::SessionID& )
  throw( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon ) {}

  void fromApp( const FIX::Message& message, const FIX::SessionID& sessionID )
  throw( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType );

  void onNew(const FIX42::ExecutionReport& message);
  void onReplace(const FIX42::ExecutionReport& message);
  void onCanceled(const FIX42::ExecutionReport& message);
  void onFilled(const FIX42::ExecutionReport& message, bool partial);
  void onOther(const FIX42::ExecutionReport& message);
  
  void onMessage( const FIX42::ExecutionReport&, const FIX::SessionID& );
  void onMessage( const FIX42::OrderCancelReject&, const FIX::SessionID& );

};

#endif
