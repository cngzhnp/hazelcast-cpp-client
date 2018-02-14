/*
 * Copyright (c) 2008-2018, Hazelcast, Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */



#include "hazelcast/client/protocol/codec/LockIsLockedByCurrentThreadCodec.h"
#include "hazelcast/client/exception/UnexpectedMessageTypeException.h"

namespace hazelcast {
    namespace client {
        namespace protocol {
            namespace codec {
                const LockMessageType LockIsLockedByCurrentThreadCodec::RequestParameters::TYPE = HZ_LOCK_ISLOCKEDBYCURRENTTHREAD;
                const bool LockIsLockedByCurrentThreadCodec::RequestParameters::RETRYABLE = true;
                const int32_t LockIsLockedByCurrentThreadCodec::ResponseParameters::TYPE = 101;
                std::auto_ptr<ClientMessage> LockIsLockedByCurrentThreadCodec::RequestParameters::encode(
                        const std::string &name, 
                        int64_t threadId) {
                    int32_t requiredDataSize = calculateDataSize(name, threadId);
                    std::auto_ptr<ClientMessage> clientMessage = ClientMessage::createForEncode(requiredDataSize);
                    clientMessage->setMessageType((uint16_t)LockIsLockedByCurrentThreadCodec::RequestParameters::TYPE);
                    clientMessage->setRetryable(RETRYABLE);
                    clientMessage->set(name);
                    clientMessage->set(threadId);
                    clientMessage->updateFrameLength();
                    return clientMessage;
                }

                int32_t LockIsLockedByCurrentThreadCodec::RequestParameters::calculateDataSize(
                        const std::string &name, 
                        int64_t threadId) {
                    int32_t dataSize = ClientMessage::HEADER_SIZE;
                    dataSize += ClientMessage::calculateDataSize(name);
                    dataSize += ClientMessage::calculateDataSize(threadId);
                    return dataSize;
                }

                LockIsLockedByCurrentThreadCodec::ResponseParameters::ResponseParameters(ClientMessage &clientMessage) {
                    if (TYPE != clientMessage.getMessageType()) {
                        throw exception::UnexpectedMessageTypeException("LockIsLockedByCurrentThreadCodec::ResponseParameters::decode", clientMessage.getMessageType(), TYPE);
                    }

                    response = clientMessage.get<bool >();
                }

                LockIsLockedByCurrentThreadCodec::ResponseParameters LockIsLockedByCurrentThreadCodec::ResponseParameters::decode(ClientMessage &clientMessage) {
                    return LockIsLockedByCurrentThreadCodec::ResponseParameters(clientMessage);
                }

                LockIsLockedByCurrentThreadCodec::ResponseParameters::ResponseParameters(const LockIsLockedByCurrentThreadCodec::ResponseParameters &rhs) {
                        response = rhs.response;
                }
                //************************ EVENTS END **************************************************************************//

            }
        }
    }
}

