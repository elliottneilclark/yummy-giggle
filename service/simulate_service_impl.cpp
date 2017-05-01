#include "service/simulate_service_impl.h"

using namespace yg;
using namespace grpc;

Status SimulateServiceImpl::Simulate(grpc::ServerContext *context,
                                     const SimulateRequest *request,
                                     SimulateResponse *response) {
  return Status::OK;
}