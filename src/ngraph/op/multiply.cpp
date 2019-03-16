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

#include "ngraph/op/multiply.hpp"

using namespace std;
using namespace ngraph;

op::Multiply::Multiply(const NodeOutput& arg0, const NodeOutput& arg1)
    : BinaryElementwiseArithmetic("Multiply", arg0, arg1)
{
    constructor_validate_and_infer_types();
}

shared_ptr<Node>
    op::Multiply::copy_with_new_source_outputs(const OutputVector& new_source_outputs) const
{
    check_new_source_outputs_count(this, new_source_outputs);
    return make_shared<Multiply>(new_source_outputs.at(0), new_source_outputs.at(1));
}

void op::Multiply::generate_adjoints(autodiff::Adjoints& adjoints, const OutputVector& deltas)
{
    auto delta = deltas.at(0);

    auto x = get_input_source_output(0);
    auto y = get_input_source_output(1);

    adjoints.add_output_delta(x, delta * y);
    adjoints.add_output_delta(y, x * delta);
}

shared_ptr<Node> ngraph::operator*(const NodeOutput& arg0, const NodeOutput& arg1)
{
    return make_shared<op::Multiply>(arg0, arg1);
}
