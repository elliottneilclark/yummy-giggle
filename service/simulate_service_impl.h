#include "proto/simulate.grpc.pb.h"

namespace yg {
class SimulateServiceImpl final : public Simulate::Service {
  grpc::Status Simulate(grpc::ServerContext *context,
                        const SimulateRequest *request,
                        SimulateResponse *response) override;
};
}  // namespace yg