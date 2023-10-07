/*
 * Copyright (c) 2008-2023, Hazelcast, Inc. All Rights Reserved.
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

#pragma once

#include "hazelcast/client/serialization/generic_record.h"

#include "../../TestHelperFunctions.h"

namespace hazelcast {
namespace client {
namespace test {
namespace compact {

inline serialization::generic_record::generic_record
create_generic_record(const std::string& type_name = random_string())
{
    using namespace serialization::generic_record;

    generic_record nested = generic_record_builder{ "nested_" + type_name }
                              .set_boolean("nested_boolean", true)
                              .build();
    return generic_record_builder{ type_name }
      .set_int32("id", 1)
      .set_boolean("boolean", true)
      .set_int8("int8", 8)
      .set_int16("int16", 16)
      .set_int32("int32", 32)
      .set_int64("int64", 64)
      .set_float32("float32", 32.32f)
      .set_float64("float64", 64.64)
      .set_nullable_boolean("nullable_boolean", true)
      .set_nullable_boolean("nullable_boolean_null", std::nullopt)
      .set_nullable_int8("nullable_int8", 88)
      .set_nullable_int8("nullable_int8_null", std::nullopt)
      .set_nullable_int16("nullable_int16", 1616)
      .set_nullable_int16("nullable_int16_null", std::nullopt)
      .set_nullable_int32("nullable_int32", 3232)
      .set_nullable_int32("nullable_int32_null", std::nullopt)
      .set_nullable_int64("nullable_int64", 6464)
      .set_nullable_int64("nullable_int64_null", std::nullopt)
      .set_nullable_float32("nullable_float32", 3232.3232f)
      .set_nullable_float32("nullable_float32_null", std::nullopt)
      .set_nullable_float64("nullable_float64", 6464.6464)
      .set_nullable_float64("nullable_float64_null", std::nullopt)
      .set_string("string", "a_text")
      .set_string("string_null", std::nullopt)
      .set_generic_record("generic_record", nested)
      .set_generic_record("generic_record_null", std::nullopt)
      .set_decimal("decimal", big_decimal{ 14, 10 })
      .set_decimal("decimal_null", std::nullopt)
      .set_time("time", local_time{ 19, 52, 10, 123456789 })
      .set_time("time_null", std::nullopt)
      .set_date("date", local_date{ 2023, 2, 6 }) // Sad times :(
      .set_date("date_null", std::nullopt)
      .set_timestamp("timestamp",
                     local_date_time{ { 2023, 2, 6 }, { 9, 2, 8, 123456789 } })
      .set_timestamp("timestamp_null", std::nullopt)
      .set_timestamp_with_timezone(
        "timestamp_with_timezone",
        offset_date_time{ { { 2023, 2, 6 }, { 19, 52, 10, 123456789 } }, 5000 })
      .set_timestamp_with_timezone("timestamp_with_timezone_null", std::nullopt)
      .set_array_of_boolean("array_of_boolean",
                            std::vector<bool>{ true, false })
      .set_array_of_boolean("array_of_boolean_null", std::nullopt)
      .set_array_of_int8("array_of_int8", std::vector<int8_t>{ 8, 9 })
      .set_array_of_int8("array_of_int8_null", std::nullopt)
      .set_array_of_int16("array_of_int16", std::vector<int16_t>{ 16, 17 })
      .set_array_of_int16("array_of_int16_null", std::nullopt)
      .set_array_of_int32("array_of_int32", std::vector<int32_t>{ 32, 33 })
      .set_array_of_int32("array_of_int32_null", std::nullopt)
      .set_array_of_int64("array_of_int64", std::vector<int64_t>{ 64, 65 })
      .set_array_of_int64("array_of_int64_null", std::nullopt)
      .set_array_of_float32("array_of_float32",
                            std::vector<float>{ 32.32f, 33.33f })
      .set_array_of_float32("array_of_float32_null", std::nullopt)
      .set_array_of_float64("array_of_float64",
                            std::vector<double>{ 64.64, 65.65 })
      .set_array_of_float64("array_of_float64_null", std::nullopt)
      .set_array_of_nullable_boolean(
        "array_of_nullable_boolean",
        std::vector<std::optional<bool>>{ std::optional<bool>{ true },
                                            std::optional<bool>{ false },
                                            std::nullopt })
      .set_array_of_nullable_boolean("array_of_nullable_boolean_null",
                                     std::nullopt)
      .set_array_of_nullable_int8(
        "array_of_nullable_int8",
        std::vector<std::optional<int8_t>>{ std::optional<int8_t>{ 88 },
                                              std::optional<int8_t>{ 89 },
                                              std::nullopt })
      .set_array_of_nullable_int8("array_of_nullable_int8_null", std::nullopt)
      .set_array_of_nullable_int16(
        "array_of_nullable_int16",
        std::vector<std::optional<int16_t>>{ std::optional<int16_t>{ 1616 },
                                               std::optional<int16_t>{ 1717 },
                                               std::nullopt })
      .set_array_of_nullable_int16("array_of_nullable_int16_null", std::nullopt)
      .set_array_of_nullable_int32(
        "array_of_nullable_int32",
        std::vector<std::optional<int32_t>>{ std::optional<int32_t>{ 3232 },
                                               std::optional<int32_t>{ 3333 },
                                               std::nullopt })
      .set_array_of_nullable_int32("array_of_nullable_int32_null", std::nullopt)
      .set_array_of_nullable_int64(
        "array_of_nullable_int64",
        std::vector<std::optional<int64_t>>{ std::optional<int64_t>{ 6464 },
                                               std::optional<int64_t>{ 6565 },
                                               std::nullopt })
      .set_array_of_nullable_int64("array_of_nullable_int64_null", std::nullopt)
      .set_array_of_nullable_float32("array_of_nullable_float32",
                                     std::vector<std::optional<float>>{
                                       std::optional<float>{ 3232.3232f },
                                       std::optional<float>{ 3333.3333f },
                                       std::nullopt })
      .set_array_of_nullable_float32("array_of_nullable_float32_null",
                                     std::nullopt)
      .set_array_of_nullable_float64("array_of_nullable_float64",
                                     std::vector<std::optional<double>>{
                                       std::optional<double>{ 6464.6464 },
                                       std::optional<double>{ 6565.6565 },
                                       std::nullopt })
      .set_array_of_nullable_float64("array_of_nullable_float64_null",
                                     std::nullopt)
      .set_array_of_string("array_of_string",
                           std::vector<std::optional<std::string>>{
                             std::optional<std::string>{ "str1" },
                             std::optional<std::string>{ "str2" },
                             std::nullopt })
      .set_array_of_string("array_of_string_null", std::nullopt)
      .set_array_of_decimal(
        "array_of_decimal",
        std::vector<std::optional<big_decimal>>{
          std::optional<big_decimal>{ big_decimal{ 14, 10 } }, std::nullopt })
      .set_array_of_decimal("array_of_decimal_null", std::nullopt)
      .set_array_of_time(
        "array_of_time",
        std::vector<std::optional<local_time>>{
          std::optional<local_time>{ local_time{ 19, 52, 10, 123456789 } },
          std::nullopt })
      .set_array_of_time("array_of_time_null", std::nullopt)
      .set_array_of_date(
        "array_of_date",
        std::vector<std::optional<local_date>>{
          std::optional<local_date>{ local_date{ 2023, 2, 6 } },
          std::nullopt })
      .set_array_of_date("array_of_date_null", std::nullopt)
      .set_array_of_timestamp(
        "array_of_timestamp",
        std::vector<std::optional<local_date_time>>{
          std::optional<local_date_time>{
            local_date_time{ { 2023, 2, 6 }, { 19, 52, 10, 123456789 } } },
          std::nullopt })
      .set_array_of_timestamp("array_of_timestamp_null", std::nullopt)
      .set_array_of_timestamp_with_timezone(
        "array_of_timestamp_with_timezone",
        std::vector<std::optional<offset_date_time>>{
          std::optional<offset_date_time>{ offset_date_time{
            { { 2023, 2, 6 }, { 19, 52, 10, 123456789 } }, 5000 } },
          std::nullopt })
      .set_array_of_timestamp_with_timezone(
        "array_of_timestamp_with_timezone_null", std::nullopt)
      .set_array_of_generic_record(
        "array_of_generic_record",
        std::vector<std::optional<generic_record>>{
          std::optional<generic_record>{ nested }, std::nullopt })
      .set_array_of_generic_record("array_of_generic_record_null", std::nullopt)
      .build();
}

} // namespace compact
} // namespace test
} // namespace client
} // namespace hazelcast