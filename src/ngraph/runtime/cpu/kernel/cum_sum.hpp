//*****************************************************************************
// Copyright 2017-2019 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//*****************************************************************************

#pragma once

#include "ngraph/runtime/cpu/cpu_executor.hpp"
#include "ngraph/runtime/reference/cum_sum.hpp"

namespace ngraph
{
    namespace runtime
    {
        namespace cpu
        {
            namespace kernel
            {
                template <typename ElementType>
                void reference_cumsum(void* arg,
                                      void* out,
                                      const Shape& in_shape,
                                      const Shape& out_shape,
                                      const int64_t axis,
                                      const int exclusive,
                                      const int reverse)
                {
                    reference::cumsum<ElementType>(static_cast<const ElementType*>(arg),
                                                   static_cast<ElementType*>(out),
                                                   in_shape,
                                                   out_shape,
                                                   axis,
                                                   exclusive,
                                                   reverse);
                }
            }
        }
    }
}