#include <iostream>
#include <string>
#include <cmath>

class Expr_node {
public:
    Expr_node() = default;

    virtual double eval() const = 0;

    virtual std::string to_string() const = 0;

    virtual ~Expr_node() = default;

    Expr_node(const Expr_node &) = delete;

    Expr_node &operator=(const Expr_node &) = delete;
};

class Number_node : public Expr_node {
    friend Number_node *make_number(double);

    double value;

    Number_node(double val) {
        value = val;
    }

    double eval() const override {
        return value;
    }

    std::string to_string() const override {
        if (value < 0)
            return "(" + std::to_string(value) + ")";
        else
            return std::to_string(value);
    }
};

inline Number_node *make_number(double value) {
    return new Number_node(value);
}

class Negation_node : public Expr_node {
    friend Negation_node *make_negation(Expr_node *);

    Expr_node *operand;

    Negation_node(Expr_node *node) {
        operand = node;
    }

    double eval() const override {
        return -operand->eval();
    }

    std::string to_string() const override {
        return "(-" + operand->to_string() + ")";
    }

    ~Negation_node() override {
        delete operand;
    }
};

inline Negation_node *make_negation(Expr_node *node) {
    return new Negation_node(node);
}

class Binary_node : public Expr_node {
protected:
    Expr_node *lhs, *rhs;

    Binary_node(Expr_node *node_l, Expr_node *node_r) {
        lhs = node_l;
        rhs = node_r;
    }

    ~Binary_node() override {
        delete lhs;
        delete rhs;
    }
};

class Plus_node : public Binary_node {
    friend Plus_node *make_plus(Expr_node *, Expr_node *);

    Plus_node(Expr_node *node_l, Expr_node *node_r) : Binary_node(node_l, node_r) {}

    double eval() const override {
        return lhs->eval() + rhs->eval();
    }

    std::string to_string() const override {
        return "(" + lhs->to_string() + " + " + rhs->to_string() + ")";
    }
};

inline Plus_node *make_plus(Expr_node *node_l, Expr_node *node_r) {
    return new Plus_node(node_l, node_r);
}

class Minus_node : public Binary_node {
    friend Minus_node *make_minus(Expr_node *, Expr_node *);

    Minus_node(Expr_node *node_l, Expr_node *node_r) : Binary_node(node_l, node_r) {}

    double eval() const override {
        return lhs->eval() - rhs->eval();
    }

    std::string to_string() const override {
        return "(" + lhs->to_string() + " - " + rhs->to_string() + ")";
    }
};

inline Minus_node *make_minus(Expr_node *node_l, Expr_node *node_r) {
    return new Minus_node(node_l, node_r);
}

class Multiply_node : public Binary_node {
    friend Multiply_node *make_multiply(Expr_node *, Expr_node *);

    Multiply_node(Expr_node *node_l, Expr_node *node_r) : Binary_node(node_l, node_r) {}

    double eval() const override {
        return lhs->eval() * rhs->eval();
    }

    std::string to_string() const override {
        return "(" + lhs->to_string() + " * " + rhs->to_string() + ")";
    }
};

inline Multiply_node *make_multiply(Expr_node *node_l, Expr_node *node_r) {
    return new Multiply_node(node_l, node_r);
}

class Divide_node : public Binary_node {
    friend Divide_node *make_divide(Expr_node *, Expr_node *);

    Divide_node(Expr_node *node_l, Expr_node *node_r) : Binary_node(node_l, node_r) {}

    double eval() const override {
        return lhs->eval() / rhs->eval();
    }

    std::string to_string() const override {
        return "(" + lhs->to_string() + " / " + rhs->to_string() + ")";
    }
};

inline Divide_node *make_divide(Expr_node *node_l, Expr_node *node_r) {
    return new Divide_node(node_l, node_r);
}

class IMS_node : public Expr_node {
public:
    Expr_node *operand;

    IMS_node(Expr_node *node) {
        operand = node;
    }

    ~IMS_node() override {
        delete operand;
    }
};

class Sin_node : public IMS_node {
    friend Sin_node *make_sin(Expr_node *);

    Sin_node(Expr_node *node) : IMS_node(node) {}

    double eval() const override {
        return sin(operand->eval());
    }

    std::string to_string() const override {
        if (operand->to_string()[0] == '(')
            return "sin" + operand->to_string();
        else
            return "sin(" + operand->to_string() + ")";
    }
};

inline Sin_node *make_sin(Expr_node *node) {
    return new Sin_node(node);
}

class Cos_node : public IMS_node {
    friend Cos_node *make_cos(Expr_node *);

    Cos_node(Expr_node *node) : IMS_node(node) {}

    double eval() const override {
        return cos(operand->eval());
    }

    std::string to_string() const override {
        if (operand->to_string()[0] == '(')
            return "cos" + operand->to_string();
        else
            return "cos(" + operand->to_string() + ")";
    }
};

inline Cos_node *make_cos(Expr_node *node) {
    return new Cos_node(node);
}

class Tan_node : public IMS_node {
    friend Tan_node *make_tan(Expr_node *);

    Tan_node(Expr_node *node) : IMS_node(node) {}

    double eval() const override {
        return tan(operand->eval());
    }

    std::string to_string() const override {
        if (operand->to_string()[0] == '(')
            return "tan" + operand->to_string();
        else
            return "tan(" + operand->to_string() + ")";
    }
};

inline Tan_node *make_tan(Expr_node *node) {
    return new Tan_node(node);
}

class Log_node : public IMS_node {
    friend Log_node *make_log(Expr_node *);

    Log_node(Expr_node *node) : IMS_node(node) {}

    double eval() const override {
        return log(operand->eval());
    }

    std::string to_string() const override {
        if (operand->to_string()[0] == '(')
            return "log" + operand->to_string();
        else
            return "log(" + operand->to_string() + ")";
    }
};

inline Log_node *make_log(Expr_node *node) {
    return new Log_node(node);
}

class Exp_node : public IMS_node {
    friend Exp_node *make_exp(Expr_node *);

    Exp_node(Expr_node *node) : IMS_node(node) {}

    double eval() const override {
        return exp(operand->eval());
    }

    std::string to_string() const override {
        if (operand->to_string()[0] == '(')
            return "exp" + operand->to_string();
        else
            return "exp(" + operand->to_string() + ")";
    }
};

inline Exp_node *make_exp(Expr_node *node) {
    return new Exp_node(node);
}

int main() {
    Expr_node *expr_tree = make_divide(
            make_plus(make_number(3), make_multiply(make_number(4), make_number(5))),
            make_number(6));
    std::cout << expr_tree->eval() << std::endl;
    std::cout << expr_tree->to_string() << std::endl;
    delete expr_tree;
    Expr_node *bonus_tree =
            make_plus(make_exp(make_sin(make_number(3))), make_number(1));
    std::cout << bonus_tree->eval() << std::endl;
    std::cout << bonus_tree->to_string() << std::endl;
    delete bonus_tree;
    return 0;
}