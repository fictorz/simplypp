/*
 * Copyright (c) 2023-2024 AWL-E. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _SILKROAD_ALGORITHM_ALGORITHMMANAGER_H_
#define _SILKROAD_ALGORITHM_ALGORITHMMANAGER_H_

#include <functional>
#include <memory>
#include <string>

#include "../asdk/generic/ErrorCodes.h"

namespace algorithm {

using asdk::generic::AWLEStatus;

class AlgorithmManager  {
public:
    explicit AlgorithmManager();
    virtual ~AlgorithmManager() = default;

    void dispatch(std::string topic, std::string payload, AWLEStatus &status);
};

} // namespace algorithm

#endif // _ALGORITHM_ALGORITHMMANAGER_H_