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

#include "ngraph/axis_set.hpp"
#include "ngraph/op/op.hpp"
#include "ngraph/op/util/arithmetic_reduction.hpp"

namespace ngraph
{
    namespace op
    {
        namespace v0
        {
            // clang-format off
            /// \brief Tensor cumulative sum operation.
            ///
            /// Compute the cumulative sum of the input tensor along the axis specified.
            ///
            /// ## Parameters
            ///
            /// |                      | Description                              							   |
            /// | -------------------- | --------------------------------------------------------------------------------------------------|		
            /// | `exclusive`          | If set to 1 will return exclusive sum in which the top element is not included. 		   |
	    ///	|		       | In other terms, if set to 1, the j-th output element would be the sum of the first (j-1) elements.|. 
	    ///	|		       | Otherwise, it would be the sum of the first j elements.  					   |
            ///
            /// |                      | Description                                        |
            /// | -------------------- | -------------------------------------------------- |
            /// | `reverse`            | if set to 1, performs the sum in reverse direction |
            ///
            /// ## Inputs
            ///
            /// |       | Description                                            |
            /// | ----- | ------------------------------------------------------ |
            /// | `arg` | An input tensor of any shape and numeric element type. |
            ///
            /// |       | Description                                                     |
            /// | ----- | --------------------------------------------------------------- |
            /// | `axis`| An axis position along which cumulative sum must be performed.  |
            ///
	    /// ## Output
            ///
            /// | Description                                                                         |
            /// | ------------------------------------------------------------------------------------|
            /// | Output tensor of the same type as `arg` with cumulative sums of the arg's elements  |
	    //
	    // clang-format off
            class CumSum : public util::ArithmeticReduction
            {
            public:
                NGRAPH_API
                static constexpr NodeTypeInfo type_info{ "CumSum", 0 };
                const NodeTypeInfo& get_type_info() const override { return type_info; }
                /// \brief Constructs a cumulative summation operation.
                CumSum() = default;
                
		/// \brief Constructs a cumulative summation operation.
                ///
                /// \param arg The tensor to be summed.
                /// \param axis The axis position along which cumulative sum must be performed.
                CumSum(const Output<Node>& arg, const Output<Node>& axis);

                virtual std::shared_ptr<Node>
                    copy_with_new_args(const NodeVector& new_args) const override;

                /// \return The default value for CumSum.
                virtual std::shared_ptr<Node> get_default_value() const override;

            protected:
                virtual void generate_adjoints(autodiff::Adjoints& adjoints,
                    const NodeVector& deltas) override;
            };
        }
        // default opset version
        using v0::CumSum;
    }
}
