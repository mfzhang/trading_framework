#pragma once

#include <memory>
#include <ib/IBWrapper.h>
#include <risk_management/AccountService.hpp>
#include <risk_management/Order.hpp>

namespace ib
{

class IBAccountService : public risk_management::AccountService<IBAccountService>
{
   public:
   IBAccountService();
   std::vector<risk_management::Order> GetOpenOrders(uint16_t accountId);
   private:
   std::shared_ptr<ib::IBWrapper> ibWrapper = nullptr;
};

} // namespace ib