#include "ast.hpp"

static void spaces(int indent) {
    for (int i = 0; i < indent; ++i)
        std::cout << "  ";
}

NumberNode::NumberNode(double value) : value(value) {}

void NumberNode::print(int indent) const {
    spaces(indent);
    std::cout << "Number: " << value << '\n';
}

VariableNode::VariableNode(const std::string& name) : name(name) {}

void VariableNode::print(int indent) const {
    spaces(indent);
    std::cout << "Variable: " << name << '\n';
}

BinaryNode::BinaryNode(const std::string& op, NodePtr left, NodePtr right)
    : op(op), left(left), right(right) {}

void BinaryNode::print(int indent) const {
    spaces(indent);
    std::cout << "Binary: " << op << '\n';

    left->print(indent + 1);
    right->print(indent + 1);
}

DeclarationNode::DeclarationNode(
    const std::string& type,
    const std::string& name,
    NodePtr value
) : type(type), name(name), value(value) {}

void DeclarationNode::print(int indent) const {
    spaces(indent);
    std::cout << "Declaration: " << type << " " << name << '\n';

    if (value)
        value->print(indent + 1);
}

AssignmentNode::AssignmentNode(const std::string& name, NodePtr value)
    : name(name), value(value) {}

void AssignmentNode::print(int indent) const {
    spaces(indent);
    std::cout << "Assignment: " << name << '\n';

    value->print(indent + 1);
}

ReturnNode::ReturnNode(NodePtr value) : value(value) {}

void ReturnNode::print(int indent) const {
    spaces(indent);
    std::cout << "Return\n";

    value->print(indent + 1);
}

void BlockNode::add(NodePtr statement) {
    statements.push_back(statement);
}

void BlockNode::print(int indent) const {
    spaces(indent);
    std::cout << "Block\n";

    for (const auto& statement : statements)
        statement->print(indent + 1);
}

void ProgramNode::add(NodePtr statement) {
    statements.push_back(statement);
}

void ProgramNode::print(int indent) const {
    spaces(indent);
    std::cout << "Program\n";

    for (const auto& statement : statements)
        statement->print(indent + 1);
}
