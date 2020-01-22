#include <algorithm>
#include <ib/IBStreamingService.hpp>
#include <util/Configuration.hpp>
#include <market_data/BarSettings.hpp>


namespace ib
{

IBStreamingService::IBStreamingService()
{
   // grab connection information from configuration
   util::Configuration* conf = util::Configuration::GetInstance();
   ibWrapper = std::make_shared<IBWrapper>( conf->GetIBHost(), conf->GetIBPort(), conf->GetIBStreamingConnectionId() );
   ConnectionStatus currStatus = ibWrapper->GetConnectionStatus();
   int counter = 0;
   while (currStatus != ConnectionStatus::CONNECTED && counter < 30)
   {
      if (currStatus == ConnectionStatus::DISCONNECTED)
         break;
      std::this_thread::sleep_for( std::chrono::milliseconds(500));
      currStatus = ibWrapper->GetConnectionStatus();
      counter++;
   }
   if (currStatus != ConnectionStatus::CONNECTED)
      throw IBException("Unable to connect");
}

template<class T>
void IBStreamingService::GetTimeAndSales(tf::Contract contract, std::function<void(market_data::TickMessage<T>)> func)
{
   // convert TickMessage to market_data::tick_message
   auto conv_func = [&func](const ib::TickMessage& ib_msg) {
      market_data::TickType md_type = IBTickTypeToMDTickType(ib_msg.tickType);
      switch (md_type)
      {
         case (market_data::TickType::BID):
         case (market_data::TickType::ASK):
         case (market_data::TickType::LAST):
            func(market_data::TickMessage<double>(md_type, ib_msg.d));
            break;
         case market_data::TickType::VOLUME:
            func(market_data::TickMessage<long>(md_type, ib_msg.l));
            break;
         case market_data::TickType::TEXT:
            func(market_data::TickMessage<std::string>(md_type, ib_msg.msg));
         break;
      }
   };
   Contract ib_contract;

   ibWrapper->SubscribeToTickData(ib_contract, conv_func );
}

} // namespace ib