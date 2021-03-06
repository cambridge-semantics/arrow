// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#pragma once

#include <memory>
#include <utility>

#include "arrow/result.h"
#include "arrow/type.h"

namespace arrow {
namespace util {

enum DivideOrMultiply {
  MULTIPLY,
  DIVIDE,
};

// TimestampType -> TimestampType
static std::pair<DivideOrMultiply, int64_t> kTimestampConversionTable[4][4] = {
    // TimestampType::SECOND
    {{MULTIPLY, 1}, {MULTIPLY, 1000}, {MULTIPLY, 1000000}, {MULTIPLY, 1000000000}},
    // TimestampType::MILLI
    {{DIVIDE, 1000}, {MULTIPLY, 1}, {MULTIPLY, 1000}, {MULTIPLY, 1000000}},
    // TimestampType::MICRO
    {{DIVIDE, 1000000}, {DIVIDE, 1000}, {MULTIPLY, 1}, {MULTIPLY, 1000}},
    // TimestampType::NANO
    {{DIVIDE, 1000000000}, {DIVIDE, 1000000}, {DIVIDE, 1000}, {MULTIPLY, 1}},
};

// Converts a Timestamp value into another Timestamp value.
//
// This function takes care of properly transforming from one unit to another.
//
// \param[in] in the input type. Must be TimestampType.
// \param[in] out the output type. Must be TimestampType.
// \param[in] value the input value.
//
// \return The converted value, or an error.
ARROW_EXPORT Result<int64_t> ConvertTimestampValue(const std::shared_ptr<DataType>& in,
                                                   const std::shared_ptr<DataType>& out,
                                                   int64_t value);
}  // namespace util
}  // namespace arrow
