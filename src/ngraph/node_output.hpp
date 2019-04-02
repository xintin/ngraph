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

// TODO: rename to output.hpp

#include "ngraph/descriptor/input.hpp"
#include "ngraph/node.hpp"

namespace ngraph
{
    /// \brief A handle for one of a node's outputs.
    class Output
    {
    public:
        /// \brief Constructs a Output.
        /// \param node A pointer to the node for the output handle.
        /// \param index The index of the output.
        Output(Node* node, size_t index)
            : m_node(node)
            , m_index(index)
        {
        }

        /// \brief Constructs a Output.
        /// \param node A `shared_ptr` to the node for the output handle.
        /// \param index The index of the output.
        ///
        /// TODO: Make a plan to deprecate this.
        Output(const std::shared_ptr<Node>& node, size_t index)
            : m_node(node.get())
            , m_index(index)
        {
        }

        /// \brief Constructs a Output, referencing the zeroth output of the node.
        /// \param node A `shared_ptr` to the node for the output handle.
        template <typename T>
        Output(const std::shared_ptr<T>& node)
            : Output(node, 0)
        {
        }

        /// \return A pointer to the node referred to by this output handle.
        Node* get_node() const { return m_node; }
        /// \return A `shared_ptr` to the node referred to by this output handle.
        ///
        /// TODO: Make a plan to deprecate this.
        std::shared_ptr<Node> get_node_shared_ptr() const { return m_node->shared_from_this(); }
        /// \return The index of the output referred to by this output handle.
        size_t get_index() const { return m_index; }
        /// \return The element type of the output referred to by this output handle.
        const element::Type& get_element_type() const
        {
            return m_node->get_output_element_type(m_index);
        }
        /// \return The shape of the output referred to by this output handle.
        const Shape& get_shape() const { return m_node->get_output_shape(m_index); }
        /// \return The partial shape of the output referred to by this output handle.
        const PartialShape& get_partial_shape() const
        {
            return m_node->get_output_partial_shape(m_index);
        }

        /// \return A set containing handles for all inputs targeted by the output referenced by
        ///        this output handle.
        std::set<Input> get_target_inputs() const;

        /// \brief Removes a target input from the output referenced by this output handle.
        /// \param target_input The target input to remove.
        void remove_target_input(const Input& target_input) const;

        bool operator==(const Output& other) const
        {
            return m_node == other.m_node && m_index == other.m_index;
        }
        bool operator!=(const Output& other) const
        {
            return m_node != other.m_node || m_index != other.m_index;
        }
        bool operator<(const Output& other) const
        {
            return m_node < other.m_node || (m_node == other.m_node && m_index < other.m_index);
        }
        bool operator>(const Output& other) const
        {
            return m_node > other.m_node || (m_node == other.m_node && m_index > other.m_index);
        }
        bool operator<=(const Output& other) const
        {
            return m_node <= other.m_node || (m_node == other.m_node && m_index <= other.m_index);
        }
        bool operator>=(const Output& other) const
        {
            return m_node >= other.m_node || (m_node == other.m_node && m_index >= other.m_index);
        }

    private:
        Node* const m_node;
        const size_t m_index;
    };
} // namespace ngraph
