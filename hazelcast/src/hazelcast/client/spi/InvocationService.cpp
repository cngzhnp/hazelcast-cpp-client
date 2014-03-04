//
// Created by sancar koyunlu on 5/23/13.
// Copyright (c) 2013 hazelcast. All rights reserved.


#include "hazelcast/client/spi/InvocationService.h"
#include "hazelcast/client/spi/ClusterService.h"
#include "hazelcast/client/spi/PartitionService.h"
#include "hazelcast/client/impl/PortableRequest.h"
#include "hazelcast/client/connection/ConnectionManager.h"
#include "hazelcast/client/connection/CallPromise.h"
#include "hazelcast/client/ClientConfig.h"
#include "hazelcast/client/spi/ClientContext.h"

namespace hazelcast {
    namespace client {
        namespace spi {
            InvocationService::InvocationService(spi::ClientContext &clientContext)
            : clientContext(clientContext) {

            }

            void InvocationService::start() {
                redoOperation = clientContext.getClientConfig().isRedoOperation();
            }

            boost::shared_future<serialization::pimpl::Data> InvocationService::invokeOnRandomTarget(const impl::PortableRequest *request) {
                std::auto_ptr<const impl::PortableRequest> managedRequest(request);
                boost::shared_ptr<connection::Connection> connection = clientContext.getConnectionManager().getRandomConnection(RETRY_COUNT);
                return doSend(managedRequest, std::auto_ptr<impl::BaseEventHandler>(NULL), connection);
            };

            boost::shared_future<serialization::pimpl::Data> InvocationService::invokeOnKeyOwner(const impl::PortableRequest *request, int partitionId) {
                boost::shared_ptr<Address> owner = clientContext.getPartitionService().getPartitionOwner(partitionId);
                if (owner.get() != NULL) {
                    return invokeOnTarget(request, *owner);
                }
                return invokeOnRandomTarget(request);
            };

            boost::shared_future<serialization::pimpl::Data> InvocationService::invokeOnTarget(const impl::PortableRequest *request, const Address &address) {
                std::auto_ptr<const impl::PortableRequest> managedRequest(request);
                boost::shared_ptr<connection::Connection> connection = clientContext.getConnectionManager().getOrConnect(address, RETRY_COUNT);
                return doSend(managedRequest, std::auto_ptr<impl::BaseEventHandler>(NULL), connection);
            };

            boost::shared_future<serialization::pimpl::Data> InvocationService::invokeOnRandomTarget(const impl::PortableRequest *request, impl::BaseEventHandler *eventHandler) {
                std::auto_ptr<const impl::PortableRequest> managedRequest(request);
                std::auto_ptr<impl::BaseEventHandler> managedEventHandler(eventHandler);
                boost::shared_ptr<connection::Connection> connection = clientContext.getConnectionManager().getRandomConnection(RETRY_COUNT);
                return doSend(managedRequest, managedEventHandler, connection);
            }

            boost::shared_future<serialization::pimpl::Data> InvocationService::invokeOnTarget(const impl::PortableRequest *request, impl::BaseEventHandler *eventHandler, const Address &address) {
                std::auto_ptr<const impl::PortableRequest> managedRequest(request);
                std::auto_ptr<impl::BaseEventHandler> managedEventHandler(eventHandler);
                boost::shared_ptr<connection::Connection> connection = clientContext.getConnectionManager().getOrConnect(address, RETRY_COUNT);
                return doSend(managedRequest, managedEventHandler, connection);
            }

            boost::shared_future<serialization::pimpl::Data> InvocationService::invokeOnKeyOwner(const impl::PortableRequest *request, impl::BaseEventHandler *handler, int partitionId) {
                boost::shared_ptr<Address> owner = clientContext.getPartitionService().getPartitionOwner(partitionId);
                if (owner.get() != NULL) {
                    return invokeOnTarget(request, handler, *owner);
                }
                return invokeOnRandomTarget(request, handler);
            }

            boost::shared_future<serialization::pimpl::Data> InvocationService::invokeOnConnection(const impl::PortableRequest *request, boost::shared_ptr<connection::Connection> connection) {
                std::auto_ptr<const impl::PortableRequest> managedRequest(request);
                return doSend(managedRequest, std::auto_ptr<impl::BaseEventHandler>(NULL), connection);
            }

            bool InvocationService::isRedoOperation() const {
                return redoOperation;
            }

            boost::shared_future<serialization::pimpl::Data> InvocationService::doSend(std::auto_ptr<const impl::PortableRequest> request, std::auto_ptr<impl::BaseEventHandler> eventHandler, boost::shared_ptr<connection::Connection> connection) {
                boost::shared_ptr<connection::CallPromise> promise(new connection::CallPromise());
                promise->setRequest(request);
                promise->setEventHandler(eventHandler);
                connection->registerAndEnqueue(promise);
                return promise->getFuture();
            }

        }
    }
}