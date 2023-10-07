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

#include "hazelcast/client/serialization/serialization.h"

#include "named_dto.h"
#include "../compact_helper.h"

namespace hazelcast {
namespace client {
namespace test {
namespace compact {

struct inner_dto
{
    std::optional<std::vector<bool>> bools;
    std::optional<std::vector<int8_t>> bytes;
    std::optional<std::vector<int16_t>> shorts;
    std::optional<std::vector<int32_t>> ints;
    std::optional<std::vector<int64_t>> longs;
    std::optional<std::vector<float>> floats;
    std::optional<std::vector<double>> doubles;
    std::optional<std::vector<std::optional<std::string>>> strings;
    std::optional<std::vector<std::optional<named_dto>>> nn;
    std::optional<std::vector<std::optional<big_decimal>>> bigDecimals;
    std::optional<std::vector<std::optional<local_time>>> localTimes;
    std::optional<std::vector<std::optional<local_date>>> localDates;
    std::optional<std::vector<std::optional<local_date_time>>>
      localDateTimes;
    std::optional<std::vector<std::optional<offset_date_time>>>
      offsetDateTimes;
    std::optional<std::vector<std::optional<bool>>> nullableBools;
    std::optional<std::vector<std::optional<int8_t>>> nullableBytes;
    std::optional<std::vector<std::optional<int16_t>>> nullableShorts;
    std::optional<std::vector<std::optional<int32_t>>> nullableInts;
    std::optional<std::vector<std::optional<int64_t>>> nullableLongs;
    std::optional<std::vector<std::optional<float>>> nullableFloats;
    std::optional<std::vector<std::optional<double>>> nullableDoubles;
};

bool
operator==(const inner_dto& lhs, const inner_dto& rhs)
{
    return lhs.bools == rhs.bools && lhs.bytes == rhs.bytes &&
           lhs.shorts == rhs.shorts && lhs.ints == rhs.ints &&
           lhs.longs == rhs.longs && lhs.floats == rhs.floats &&
           lhs.doubles == rhs.doubles && lhs.strings == rhs.strings &&
           lhs.nn == rhs.nn && lhs.bigDecimals == rhs.bigDecimals &&
           lhs.localTimes == rhs.localTimes &&
           lhs.localDates == rhs.localDates &&
           lhs.localDateTimes == rhs.localDateTimes &&
           lhs.offsetDateTimes == rhs.offsetDateTimes &&
           lhs.nullableBools == rhs.nullableBools &&
           lhs.nullableBytes == rhs.nullableBytes &&
           lhs.nullableShorts == rhs.nullableShorts &&
           lhs.nullableInts == rhs.nullableInts &&
           lhs.nullableLongs == rhs.nullableLongs &&
           lhs.nullableFloats == rhs.nullableFloats &&
           lhs.nullableDoubles == rhs.nullableDoubles;
}

inner_dto
create_inner_dto()
{
    return inner_dto{
        std::make_optional<std::vector<bool>>({ true, false }),
        std::make_optional<std::vector<int8_t>>({ 0, 1, 2 }),
        std::make_optional<std::vector<int16_t>>({ 3, 4, 5 }),
        std::make_optional<std::vector<int32_t>>({ 9, 8, 7, 6 }),
        std::make_optional<std::vector<int64_t>>({ 0, 1, 5, 7, 9, 11 }),
        std::make_optional<std::vector<float>>({ 0.6543f, -3.56f, 45.67f }),
        std::make_optional<std::vector<double>>(
          { 456.456, 789.789, 321.321 }),
        std::make_optional<std::vector<std::optional<std::string>>>(
          { std::make_optional<std::string>("test"), std::nullopt }),
        std::make_optional<std::vector<std::optional<named_dto>>>(
          { std::make_optional(
              named_dto{ std::make_optional<std::string>("test"), 1 }),
            std::nullopt }),
        std::make_optional<
          std::vector<std::optional<hazelcast::client::big_decimal>>>(
          { std::make_optional(hazelcast::client::big_decimal{
              boost::multiprecision::cpp_int{ "12345" }, 0 }),
            std::make_optional(hazelcast::client::big_decimal{
              boost::multiprecision::cpp_int{ "123456" }, 0 }) }),
        std::make_optional<
          std::vector<std::optional<hazelcast::client::local_time>>>(
          { std::make_optional(current_time()),
            std::nullopt,
            std::make_optional(current_time()) }),
        std::make_optional<
          std::vector<std::optional<hazelcast::client::local_date>>>(
          { std::make_optional(current_date()),
            std::nullopt,
            std::make_optional(current_date()) }),
        std::make_optional<
          std::vector<std::optional<hazelcast::client::local_date_time>>>(
          { std::make_optional(current_timestamp()), std::nullopt }),
        std::make_optional<
          std::vector<std::optional<hazelcast::client::offset_date_time>>>(
          { std::make_optional(current_timestamp_with_timezone()) }),
        std::make_optional<std::vector<std::optional<bool>>>(
          { std::make_optional(true),
            std::make_optional(false),
            std::nullopt }),
        std::make_optional<std::vector<std::optional<int8_t>>>(
          { std::make_optional<int8_t>(0),
            std::make_optional<int8_t>(1),
            std::make_optional<int8_t>(2),
            std::nullopt }),
        std::make_optional<std::vector<std::optional<int16_t>>>(
          { std::make_optional<int16_t>(3),
            std::make_optional<int16_t>(4),
            std::make_optional<int16_t>(5),
            std::nullopt }),
        std::make_optional<std::vector<std::optional<int32_t>>>(
          { std::make_optional<int32_t>(9),
            std::make_optional<int32_t>(8),
            std::make_optional<int32_t>(7),
            std::make_optional<int32_t>(6),
            std::nullopt }),
        std::make_optional<std::vector<std::optional<int64_t>>>(
          { std::make_optional<int64_t>(0),
            std::make_optional<int64_t>(1),
            std::make_optional<int64_t>(5),
            std::make_optional<int64_t>(7),
            std::nullopt }),
        std::make_optional<std::vector<std::optional<float>>>(
          { std::make_optional(0.6543f),
            std::make_optional(-3.56f),
            std::make_optional(45.67f),
            std::nullopt }),
        std::make_optional<std::vector<std::optional<double>>>(
          { std::make_optional(456.456),
            std::make_optional(789.789),
            std::make_optional(321.321),
            std::nullopt }),
    };
}

} // namespace compact
} // namespace test

namespace serialization {

template<>
struct hz_serializer<test::compact::inner_dto>
  : public compact::compact_serializer
{
    static void write(const test::compact::inner_dto& object,
                      compact::compact_writer& writer)
    {
        writer.write_array_of_boolean("bools", object.bools);
        writer.write_array_of_int8("bytes", object.bytes);
        writer.write_array_of_int16("shorts", object.shorts);
        writer.write_array_of_int32("ints", object.ints);
        writer.write_array_of_int64("longs", object.longs);
        writer.write_array_of_float32("floats", object.floats);
        writer.write_array_of_float64("doubles", object.doubles);
        writer.write_array_of_string("strings", object.strings);
        writer.write_array_of_decimal("bigDecimals", object.bigDecimals);
        writer.write_array_of_time("localTimes", object.localTimes);
        writer.write_array_of_date("localDates", object.localDates);
        writer.write_array_of_timestamp("localDateTimes",
                                        object.localDateTimes);
        writer.write_array_of_timestamp_with_timezone("offsetDateTimes",
                                                      object.offsetDateTimes);
        writer.write_array_of_compact("nn", object.nn);
        writer.write_array_of_nullable_boolean("nullableBools",
                                               object.nullableBools);
        writer.write_array_of_nullable_int8("nullableBytes",
                                            object.nullableBytes);
        writer.write_array_of_nullable_int16("nullableShorts",
                                             object.nullableShorts);
        writer.write_array_of_nullable_int32("nullableInts",
                                             object.nullableInts);
        writer.write_array_of_nullable_int64("nullableLongs",
                                             object.nullableLongs);
        writer.write_array_of_nullable_float32("nullableFloats",
                                               object.nullableFloats);
        writer.write_array_of_nullable_float64("nullableDoubles",
                                               object.nullableDoubles);
    }

    static test::compact::inner_dto read(compact::compact_reader& reader)
    {
        test::compact::inner_dto object;
        object.bools = reader.read_array_of_boolean("bools");
        object.bytes = reader.read_array_of_int8("bytes");
        object.shorts = reader.read_array_of_int16("shorts");
        object.ints = reader.read_array_of_int32("ints");
        object.longs = reader.read_array_of_int64("longs");
        object.floats = reader.read_array_of_float32("floats");
        object.doubles = reader.read_array_of_float64("doubles");
        object.strings = reader.read_array_of_string("strings");
        object.bigDecimals = reader.read_array_of_decimal("bigDecimals");
        object.localTimes = reader.read_array_of_time("localTimes");
        object.localDates = reader.read_array_of_date("localDates");
        object.localDateTimes =
          reader.read_array_of_timestamp("localDateTimes");
        object.offsetDateTimes =
          reader.read_array_of_timestamp_with_timezone("offsetDateTimes");
        object.nn =
          reader.read_array_of_compact<test::compact::named_dto>("nn");
        object.nullableBools =
          reader.read_array_of_nullable_boolean("nullableBools");
        object.nullableBytes =
          reader.read_array_of_nullable_int8("nullableBytes");
        object.nullableShorts =
          reader.read_array_of_nullable_int16("nullableShorts");
        object.nullableInts =
          reader.read_array_of_nullable_int32("nullableInts");
        object.nullableLongs =
          reader.read_array_of_nullable_int64("nullableLongs");
        object.nullableFloats =
          reader.read_array_of_nullable_float32("nullableFloats");
        object.nullableDoubles =
          reader.read_array_of_nullable_float64("nullableDoubles");
        return object;
    }

    static std::string type_name() { return "inner"; }
};

} // namespace serialization
} // namespace client
} // namespace hazelcast
