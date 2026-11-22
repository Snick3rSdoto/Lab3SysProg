#ifndef AST_HPP
#define AST_HPP

#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Node {
public:
    virtual ~Node() = default;

    virtual void print(int indent = 0) const = 0;
};

using NodePtr = std::shared_ptr<Node>;

class NumberNode : public Node {
public:
    double value;

    explicit NumberNode(double value);

    void print(int indent = 0) const override;
};

class VariableNode : public Node {
public:
    std::string name;

    explicit VariableNode(const std::string& name);

    void print(int indent = 0) const override;
};

class BinaryNode : public Node {
public:
    std::string op;
    NodePtr left;
    NodePtr right;

    BinaryNode(const std::string& op, NodePtr left, NodePtr right);

    void print(int indent = 0) const override;
};

class DeclarationNode : public Node {
public:
    std::string type;
    std::string name;
    NodePtr value;

    DeclarationNode(const std::string& type,
                    const std::string& name,
                    NodePtr value);

    void print(int indent = 0) const override;
};

class AssignmentNode : public Node {
public:
    std::string name;
    NodePtr value;

    AssignmentNode(const std::string& name, NodePtr value);

    void print(int indent = 0) const override;
};

class ReturnNode : public Node {
public:
    NodePtr value;

    explicit ReturnNode(NodePtr value);

    void print(int indent = 0) const override;
};

class BlockNode : public Node {
public:
    std::vector<NodePtr> statements;

    void add(NodePtr statement);

    void print(int indent = 0) const override;
};

class ProgramNode : public Node {
public:
    std::vector<NodePtr> statements;

    void add(NodePtr statement);

    void print(int indent = 0) const override;
};

#endif
